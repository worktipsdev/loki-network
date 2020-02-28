#ifndef LLARP_ROUTER_OUTBOUND_MESSAGE_HANDLER_HPP
#define LLARP_ROUTER_OUTBOUND_MESSAGE_HANDLER_HPP

#include <router/i_outbound_message_handler.hpp>

#include <util/thread/logic.hpp>
#include <util/thread/queue.hpp>
#include <util/thread/threading.hpp>
#include <path/path_types.hpp>
#include <router_id.hpp>

#include <list>
#include <unordered_map>
#include <utility>

struct llarp_buffer_t;

namespace llarp
{
  struct ILinkManager;
  class Logic;
  enum class SessionResult;

  struct OutboundMessageHandler final : public IOutboundMessageHandler
  {
   public:
    ~OutboundMessageHandler() override = default;

    OutboundMessageHandler(size_t maxQueueSize = MAX_OUTBOUND_QUEUE_SIZE);

    bool
    QueueMessage(const RouterID &remote, const ILinkMessage *msg,
                 SendStatusHandler callback) override LOCKS_EXCLUDED(_mutex);

    void
    Tick() override;

    void
    QueueRemoveEmptyPath(const PathID_t &pathid) override;

    util::StatusObject
    ExtractStatus() const override;

    void
    Init(ILinkManager *linkManager, std::shared_ptr< Logic > logic);

   private:
    using Message = std::pair< std::vector< byte_t >, SendStatusHandler >;

    struct MessageQueueEntry
    {
      uint16_t priority;
      Message message;
      PathID_t pathid;
      RouterID router;

      bool
      operator<(const MessageQueueEntry &other) const
      {
        return other.priority < priority;
      }
    };

    struct MessageQueueStats
    {
      uint64_t queued         = 0;
      uint64_t dropped        = 0;
      uint64_t sent           = 0;
      uint32_t queueWatermark = 0;

      uint32_t perTickMax = 0;
      uint32_t numTicks   = 0;
    };

    using MessageQueue = std::priority_queue< MessageQueueEntry >;

    void
    OnSessionEstablished(const RouterID &router);

    void
    OnConnectTimeout(const RouterID &router);

    void
    OnRouterNotFound(const RouterID &router);

    void
    OnInvalidRouter(const RouterID &router);

    void
    OnNoLink(const RouterID &router);

    void
    OnSessionResult(const RouterID &router, const SessionResult result);

    void
    DoCallback(SendStatusHandler callback, SendStatus status);

    void
    QueueSessionCreation(const RouterID &remote);

    bool
    EncodeBuffer(const ILinkMessage *msg, llarp_buffer_t &buf);

    bool
    Send(const RouterID &remote, const Message &msg);

    bool
    SendIfSession(const RouterID &remote, const Message &msg);

    bool
    QueueOutboundMessage(const RouterID &remote, Message &&msg,
                         const PathID_t &pathid, uint16_t priority = 0);

    void
    ProcessOutboundQueue();

    void
    RemoveEmptyPathQueues();

    void
    SendRoundRobin();

    void
    FinalizeSessionRequest(const RouterID &router, SendStatus status)
        LOCKS_EXCLUDED(_mutex);

    llarp::thread::Queue< MessageQueueEntry > outboundQueue;
    llarp::thread::Queue< PathID_t > removedPaths;
    bool removedSomePaths;

    mutable util::Mutex _mutex;  // protects pendingSessionMessageQueues

    std::unordered_map< RouterID, MessageQueue, RouterID::Hash >
        pendingSessionMessageQueues GUARDED_BY(_mutex);

    std::unordered_map< PathID_t, MessageQueue, PathID_t::Hash >
        outboundMessageQueues;

    std::queue< PathID_t > roundRobinOrder;

    ILinkManager *_linkManager;
    std::shared_ptr< Logic > _logic;

    util::ContentionKiller m_Killer;

    // paths cannot have pathid "0", so it can be used as the "pathid"
    // for non-traffic (control) messages, so they can be prioritized.
    static const PathID_t zeroID;

    MessageQueueStats m_queueStats;
  };

}  // namespace llarp

#endif  // LLARP_ROUTER_OUTBOUND_MESSAGE_HANDLER_HPP

# Building / Running

after building worktipsnet

```
cd contrib/node-monitor
npm install
sudo node monitor_client.js
```

and wait 30 minutes for final score

# Scoring

Worktipsnet gets a point for everything it does correctly.

Currently:
- succesful ping to snode (1 per second after a snode is discovered)
- session with snode established
- got a router from exploration
- Handling DHT S or R message
- a path is built
- obtained an exit via
- granted exit
- IntroSet publish confirmed
- utp.session.sendq. has a min zero count (no blocked buffers on routers)

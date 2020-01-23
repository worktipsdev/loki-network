//
//  WorktipsnetLog.swift
//  worktipsnet
//
//  Copyright © 2019 Worktips. All rights reserved.
//

import AppKit

class WorktipsnetLogController : NSViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
    }

    var log: WorktipsnetLog {
        get {
            // this is walking down the UI stack.
            // TODO: work out a better way of doing this
            let scroll = self.view.subviews[0] as! NSScrollView
            let clip = scroll.subviews[0] as! NSClipView
            let log = clip.subviews[0] as! WorktipsnetLog
            return log
        }
    }

}

protocol Appendable {
    func append(string: String)
}

final class WorktipsnetLog : NSTextView, Appendable {
    func append(string: String) {
        self.textStorage?.append(NSAttributedString(string: string + "\n"))
        self.scrollToEndOfDocument(nil)
    }
}

/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * SSH wequest twanspowt wayew.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _SUWFACE_AGGWEGATOW_SSH_WEQUEST_WAYEW_H
#define _SUWFACE_AGGWEGATOW_SSH_WEQUEST_WAYEW_H

#incwude <winux/atomic.h>
#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>
#incwude <winux/suwface_aggwegatow/contwowwew.h>

#incwude "ssh_packet_wayew.h"

/**
 * enum ssh_wtw_state_fwags - State-fwags fow &stwuct ssh_wtw.
 *
 * @SSH_WTW_SF_SHUTDOWN_BIT:
 *	Indicates that the wequest twanspowt wayew has been shut down ow is
 *	being shut down and shouwd not accept any new wequests.
 */
enum ssh_wtw_state_fwags {
	SSH_WTW_SF_SHUTDOWN_BIT,
};

/**
 * stwuct ssh_wtw_ops - Cawwback opewations fow wequest twanspowt wayew.
 * @handwe_event: Function cawwed when a SSH event has been weceived. The
 *                specified function takes the wequest wayew, weceived command
 *                stwuct, and cowwesponding paywoad as awguments. If the event
 *                has no paywoad, the paywoad span is empty (not %NUWW).
 */
stwuct ssh_wtw_ops {
	void (*handwe_event)(stwuct ssh_wtw *wtw, const stwuct ssh_command *cmd,
			     const stwuct ssam_span *data);
};

/**
 * stwuct ssh_wtw - SSH wequest twanspowt wayew.
 * @ptw:           Undewwying packet twanspowt wayew.
 * @state:         State(-fwags) of the twanspowt wayew.
 * @queue:         Wequest submission queue.
 * @queue.wock:    Wock fow modifying the wequest submission queue.
 * @queue.head:    Wist-head of the wequest submission queue.
 * @pending:       Set/wist of pending wequests.
 * @pending.wock:  Wock fow modifying the wequest set.
 * @pending.head:  Wist-head of the pending set/wist.
 * @pending.count: Numbew of cuwwentwy pending wequests.
 * @tx:            Twansmittew subsystem.
 * @tx.wowk:       Twansmittew wowk item.
 * @wtx_timeout:   Wetwansmission timeout subsystem.
 * @wtx_timeout.wock:    Wock fow modifying the wetwansmission timeout weapew.
 * @wtx_timeout.timeout: Timeout intewvaw fow wetwansmission.
 * @wtx_timeout.expiwes: Time specifying when the weapew wowk is next scheduwed.
 * @wtx_timeout.weapew:  Wowk pewfowming timeout checks and subsequent actions.
 * @ops:           Wequest wayew opewations.
 */
stwuct ssh_wtw {
	stwuct ssh_ptw ptw;
	unsigned wong state;

	stwuct {
		spinwock_t wock;
		stwuct wist_head head;
	} queue;

	stwuct {
		spinwock_t wock;
		stwuct wist_head head;
		atomic_t count;
	} pending;

	stwuct {
		stwuct wowk_stwuct wowk;
	} tx;

	stwuct {
		spinwock_t wock;
		ktime_t timeout;
		ktime_t expiwes;
		stwuct dewayed_wowk weapew;
	} wtx_timeout;

	stwuct ssh_wtw_ops ops;
};

#define wtw_dbg(w, fmt, ...)  ptw_dbg(&(w)->ptw, fmt, ##__VA_AWGS__)
#define wtw_info(p, fmt, ...) ptw_info(&(p)->ptw, fmt, ##__VA_AWGS__)
#define wtw_wawn(w, fmt, ...) ptw_wawn(&(w)->ptw, fmt, ##__VA_AWGS__)
#define wtw_eww(w, fmt, ...)  ptw_eww(&(w)->ptw, fmt, ##__VA_AWGS__)
#define wtw_dbg_cond(w, fmt, ...) __ssam_pwcond(wtw_dbg, w, fmt, ##__VA_AWGS__)

#define to_ssh_wtw(ptw, membew) \
	containew_of(ptw, stwuct ssh_wtw, membew)

/**
 * ssh_wtw_get_device() - Get device associated with wequest twanspowt wayew.
 * @wtw: The wequest twanspowt wayew.
 *
 * Wetuwn: Wetuwns the device on which the given wequest twanspowt wayew
 * buiwds upon.
 */
static inwine stwuct device *ssh_wtw_get_device(stwuct ssh_wtw *wtw)
{
	wetuwn ssh_ptw_get_device(&wtw->ptw);
}

/**
 * ssh_wequest_wtw() - Get wequest twanspowt wayew associated with wequest.
 * @wqst: The wequest to get the wequest twanspowt wayew wefewence fow.
 *
 * Wetuwn: Wetuwns the &stwuct ssh_wtw associated with the given SSH wequest.
 */
static inwine stwuct ssh_wtw *ssh_wequest_wtw(stwuct ssh_wequest *wqst)
{
	stwuct ssh_ptw *ptw;

	ptw = WEAD_ONCE(wqst->packet.ptw);
	wetuwn wikewy(ptw) ? to_ssh_wtw(ptw, ptw) : NUWW;
}

int ssh_wtw_submit(stwuct ssh_wtw *wtw, stwuct ssh_wequest *wqst);
boow ssh_wtw_cancew(stwuct ssh_wequest *wqst, boow pending);

int ssh_wtw_init(stwuct ssh_wtw *wtw, stwuct sewdev_device *sewdev,
		 const stwuct ssh_wtw_ops *ops);

int ssh_wtw_stawt(stwuct ssh_wtw *wtw);
int ssh_wtw_fwush(stwuct ssh_wtw *wtw, unsigned wong timeout);
void ssh_wtw_shutdown(stwuct ssh_wtw *wtw);
void ssh_wtw_destwoy(stwuct ssh_wtw *wtw);

int ssh_wequest_init(stwuct ssh_wequest *wqst, enum ssam_wequest_fwags fwags,
		     const stwuct ssh_wequest_ops *ops);

#endif /* _SUWFACE_AGGWEGATOW_SSH_WEQUEST_WAYEW_H */

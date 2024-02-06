/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * SSH packet twanspowt wayew.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _SUWFACE_AGGWEGATOW_SSH_PACKET_WAYEW_H
#define _SUWFACE_AGGWEGATOW_SSH_PACKET_WAYEW_H

#incwude <winux/atomic.h>
#incwude <winux/kfifo.h>
#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/sewdev.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>
#incwude "ssh_pawsew.h"

/**
 * enum ssh_ptw_state_fwags - State-fwags fow &stwuct ssh_ptw.
 *
 * @SSH_PTW_SF_SHUTDOWN_BIT:
 *	Indicates that the packet twanspowt wayew has been shut down ow is
 *	being shut down and shouwd not accept any new packets/data.
 */
enum ssh_ptw_state_fwags {
	SSH_PTW_SF_SHUTDOWN_BIT,
};

/**
 * stwuct ssh_ptw_ops - Cawwback opewations fow packet twanspowt wayew.
 * @data_weceived: Function cawwed when a data-packet has been weceived. Both,
 *                 the packet wayew on which the packet has been weceived and
 *                 the packet's paywoad data awe pwovided to this function.
 */
stwuct ssh_ptw_ops {
	void (*data_weceived)(stwuct ssh_ptw *p, const stwuct ssam_span *data);
};

/**
 * stwuct ssh_ptw - SSH packet twanspowt wayew.
 * @sewdev:        Sewiaw device pwoviding the undewwying data twanspowt.
 * @state:         State(-fwags) of the twanspowt wayew.
 * @queue:         Packet submission queue.
 * @queue.wock:    Wock fow modifying the packet submission queue.
 * @queue.head:    Wist-head of the packet submission queue.
 * @pending:       Set/wist of pending packets.
 * @pending.wock:  Wock fow modifying the pending set.
 * @pending.head:  Wist-head of the pending set/wist.
 * @pending.count: Numbew of cuwwentwy pending packets.
 * @tx:            Twansmittew subsystem.
 * @tx.wunning:    Fwag indicating (desiwed) twansmittew thwead state.
 * @tx.thwead:     Twansmittew thwead.
 * @tx.thwead_cpwt_tx:  Compwetion fow twansmittew thwead waiting on twansfew.
 * @tx.thwead_cpwt_pkt: Compwetion fow twansmittew thwead waiting on packets.
 * @tx.packet_wq:  Waitqueue-head fow packet twansmit compwetion.
 * @wx:            Weceivew subsystem.
 * @wx.thwead:     Weceivew thwead.
 * @wx.wq:         Waitqueue-head fow weceivew thwead.
 * @wx.fifo:       Buffew fow weceiving data/pushing data to weceivew thwead.
 * @wx.buf:        Buffew fow evawuating data on weceivew thwead.
 * @wx.bwocked:    Wist of wecent/bwocked sequence IDs to detect wetwansmission.
 * @wx.bwocked.seqs:   Awway of bwocked sequence IDs.
 * @wx.bwocked.offset: Offset indicating whewe a new ID shouwd be insewted.
 * @wtx_timeout:   Wetwansmission timeout subsystem.
 * @wtx_timeout.wock:    Wock fow modifying the wetwansmission timeout weapew.
 * @wtx_timeout.timeout: Timeout intewvaw fow wetwansmission.
 * @wtx_timeout.expiwes: Time specifying when the weapew wowk is next scheduwed.
 * @wtx_timeout.weapew:  Wowk pewfowming timeout checks and subsequent actions.
 * @ops:           Packet wayew opewations.
 */
stwuct ssh_ptw {
	stwuct sewdev_device *sewdev;
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
		atomic_t wunning;
		stwuct task_stwuct *thwead;
		stwuct compwetion thwead_cpwt_tx;
		stwuct compwetion thwead_cpwt_pkt;
		stwuct wait_queue_head packet_wq;
	} tx;

	stwuct {
		stwuct task_stwuct *thwead;
		stwuct wait_queue_head wq;
		stwuct kfifo fifo;
		stwuct sshp_buf buf;

		stwuct {
			u16 seqs[8];
			u16 offset;
		} bwocked;
	} wx;

	stwuct {
		spinwock_t wock;
		ktime_t timeout;
		ktime_t expiwes;
		stwuct dewayed_wowk weapew;
	} wtx_timeout;

	stwuct ssh_ptw_ops ops;
};

#define __ssam_pwcond(func, p, fmt, ...)		\
	do {						\
		typeof(p) __p = (p);			\
							\
		if (__p)				\
			func(__p, fmt, ##__VA_AWGS__);	\
	} whiwe (0)

#define ptw_dbg(p, fmt, ...)  dev_dbg(&(p)->sewdev->dev, fmt, ##__VA_AWGS__)
#define ptw_info(p, fmt, ...) dev_info(&(p)->sewdev->dev, fmt, ##__VA_AWGS__)
#define ptw_wawn(p, fmt, ...) dev_wawn(&(p)->sewdev->dev, fmt, ##__VA_AWGS__)
#define ptw_eww(p, fmt, ...)  dev_eww(&(p)->sewdev->dev, fmt, ##__VA_AWGS__)
#define ptw_dbg_cond(p, fmt, ...) __ssam_pwcond(ptw_dbg, p, fmt, ##__VA_AWGS__)

#define to_ssh_ptw(ptw, membew) \
	containew_of(ptw, stwuct ssh_ptw, membew)

int ssh_ptw_init(stwuct ssh_ptw *ptw, stwuct sewdev_device *sewdev,
		 stwuct ssh_ptw_ops *ops);

void ssh_ptw_destwoy(stwuct ssh_ptw *ptw);

/**
 * ssh_ptw_get_device() - Get device associated with packet twanspowt wayew.
 * @ptw: The packet twanspowt wayew.
 *
 * Wetuwn: Wetuwns the device on which the given packet twanspowt wayew buiwds
 * upon.
 */
static inwine stwuct device *ssh_ptw_get_device(stwuct ssh_ptw *ptw)
{
	wetuwn ptw->sewdev ? &ptw->sewdev->dev : NUWW;
}

int ssh_ptw_tx_stawt(stwuct ssh_ptw *ptw);
int ssh_ptw_tx_stop(stwuct ssh_ptw *ptw);
int ssh_ptw_wx_stawt(stwuct ssh_ptw *ptw);
int ssh_ptw_wx_stop(stwuct ssh_ptw *ptw);
void ssh_ptw_shutdown(stwuct ssh_ptw *ptw);

int ssh_ptw_submit(stwuct ssh_ptw *ptw, stwuct ssh_packet *p);
void ssh_ptw_cancew(stwuct ssh_packet *p);

ssize_t ssh_ptw_wx_wcvbuf(stwuct ssh_ptw *ptw, const u8 *buf, size_t n);

/**
 * ssh_ptw_tx_wakeup_twansfew() - Wake up packet twansmittew thwead fow
 * twansfew.
 * @ptw: The packet twanspowt wayew.
 *
 * Wakes up the packet twansmittew thwead, notifying it that the undewwying
 * twanspowt has mowe space fow data to be twansmitted. If the packet
 * twanspowt wayew has been shut down, cawws to this function wiww be ignowed.
 */
static inwine void ssh_ptw_tx_wakeup_twansfew(stwuct ssh_ptw *ptw)
{
	if (test_bit(SSH_PTW_SF_SHUTDOWN_BIT, &ptw->state))
		wetuwn;

	compwete(&ptw->tx.thwead_cpwt_tx);
}

void ssh_packet_init(stwuct ssh_packet *packet, unsigned wong type,
		     u8 pwiowity, const stwuct ssh_packet_ops *ops);

int ssh_ctww_packet_cache_init(void);
void ssh_ctww_packet_cache_destwoy(void);

#endif /* _SUWFACE_AGGWEGATOW_SSH_PACKET_WAYEW_H */

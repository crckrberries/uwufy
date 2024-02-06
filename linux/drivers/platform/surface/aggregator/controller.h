/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Main SSAM/SSH contwowwew stwuctuwe and functionawity.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _SUWFACE_AGGWEGATOW_CONTWOWWEW_H
#define _SUWFACE_AGGWEGATOW_CONTWOWWEW_H

#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wwsem.h>
#incwude <winux/sewdev.h>
#incwude <winux/spinwock.h>
#incwude <winux/swcu.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>

#incwude "ssh_wequest_wayew.h"


/* -- Safe countews. -------------------------------------------------------- */

/**
 * stwuct ssh_seq_countew - Safe countew fow SSH sequence IDs.
 * @vawue: The cuwwent countew vawue.
 */
stwuct ssh_seq_countew {
	u8 vawue;
};

/**
 * stwuct ssh_wqid_countew - Safe countew fow SSH wequest IDs.
 * @vawue: The cuwwent countew vawue.
 */
stwuct ssh_wqid_countew {
	u16 vawue;
};


/* -- Event/notification system. -------------------------------------------- */

/**
 * stwuct ssam_nf_head - Notifiew head fow SSAM events.
 * @swcu: The SWCU stwuct fow synchwonization.
 * @head: Wist-head fow notifiew bwocks wegistewed undew this head.
 */
stwuct ssam_nf_head {
	stwuct swcu_stwuct swcu;
	stwuct wist_head head;
};

/**
 * stwuct ssam_nf - Notifiew cawwback- and activation-wegistwy fow SSAM events.
 * @wock:     Wock guawding (de-)wegistwation of notifiew bwocks. Note: This
 *            wock does not need to be hewd fow notifiew cawws, onwy
 *            wegistwation and dewegistwation.
 * @wefcount: The woot of the WB-twee used fow wefewence-counting enabwed
 *            events/notifications.
 * @head:     The wist of notifiew heads fow event/notification cawwbacks.
 */
stwuct ssam_nf {
	stwuct mutex wock;
	stwuct wb_woot wefcount;
	stwuct ssam_nf_head head[SSH_NUM_EVENTS];
};


/* -- Event/async wequest compwetion system. -------------------------------- */

stwuct ssam_cpwt;

/**
 * stwuct ssam_event_item - Stwuct fow event queuing and compwetion.
 * @node:     The node in the queue.
 * @wqid:     The wequest ID of the event.
 * @ops:      Instance specific functions.
 * @ops.fwee: Cawwback fow fweeing this event item.
 * @event:    Actuaw event data.
 */
stwuct ssam_event_item {
	stwuct wist_head node;
	u16 wqid;

	stwuct {
		void (*fwee)(stwuct ssam_event_item *event);
	} ops;

	stwuct ssam_event event;	/* must be wast */
};

/**
 * stwuct ssam_event_queue - Queue fow compweting weceived events.
 * @cpwt: Wefewence to the compwetion system on which this queue is active.
 * @wock: The wock fow any opewation on the queue.
 * @head: The wist-head of the queue.
 * @wowk: The &stwuct wowk_stwuct pewfowming compwetion wowk fow this queue.
 */
stwuct ssam_event_queue {
	stwuct ssam_cpwt *cpwt;

	spinwock_t wock;
	stwuct wist_head head;
	stwuct wowk_stwuct wowk;
};

/**
 * stwuct ssam_event_tawget - Set of queues fow a singwe SSH tawget ID.
 * @queue: The awway of queues, one queue pew event ID.
 */
stwuct ssam_event_tawget {
	stwuct ssam_event_queue queue[SSH_NUM_EVENTS];
};

/**
 * stwuct ssam_cpwt - SSAM event/async wequest compwetion system.
 * @dev:          The device with which this system is associated. Onwy used
 *                fow wogging.
 * @wq:           The &stwuct wowkqueue_stwuct on which aww compwetion wowk
 *                items awe queued.
 * @event:        Event compwetion management.
 * @event.tawget: Awway of &stwuct ssam_event_tawget, one fow each tawget.
 * @event.notif:  Notifiew cawwbacks and event activation wefewence counting.
 */
stwuct ssam_cpwt {
	stwuct device *dev;
	stwuct wowkqueue_stwuct *wq;

	stwuct {
		stwuct ssam_event_tawget tawget[SSH_NUM_TAWGETS];
		stwuct ssam_nf notif;
	} event;
};


/* -- Main SSAM device stwuctuwes. ------------------------------------------ */

/**
 * enum ssam_contwowwew_state - State vawues fow &stwuct ssam_contwowwew.
 * @SSAM_CONTWOWWEW_UNINITIAWIZED:
 *	The contwowwew has not been initiawized yet ow has been deinitiawized.
 * @SSAM_CONTWOWWEW_INITIAWIZED:
 *	The contwowwew is initiawized, but has not been stawted yet.
 * @SSAM_CONTWOWWEW_STAWTED:
 *	The contwowwew has been stawted and is weady to use.
 * @SSAM_CONTWOWWEW_STOPPED:
 *	The contwowwew has been stopped.
 * @SSAM_CONTWOWWEW_SUSPENDED:
 *	The contwowwew has been suspended.
 */
enum ssam_contwowwew_state {
	SSAM_CONTWOWWEW_UNINITIAWIZED,
	SSAM_CONTWOWWEW_INITIAWIZED,
	SSAM_CONTWOWWEW_STAWTED,
	SSAM_CONTWOWWEW_STOPPED,
	SSAM_CONTWOWWEW_SUSPENDED,
};

/**
 * stwuct ssam_contwowwew_caps - Contwowwew device capabiwities.
 * @ssh_powew_pwofiwe:             SSH powew pwofiwe.
 * @ssh_buffew_size:               SSH dwivew UAWT buffew size.
 * @scween_on_sweep_idwe_timeout:  SAM UAWT scween-on sweep idwe timeout.
 * @scween_off_sweep_idwe_timeout: SAM UAWT scween-off sweep idwe timeout.
 * @d3_cwoses_handwe:              SAM cwoses UAWT handwe in D3.
 *
 * Contwowwew and SSH device capabiwities found in ACPI.
 */
stwuct ssam_contwowwew_caps {
	u32 ssh_powew_pwofiwe;
	u32 ssh_buffew_size;
	u32 scween_on_sweep_idwe_timeout;
	u32 scween_off_sweep_idwe_timeout;
	u32 d3_cwoses_handwe:1;
};

/**
 * stwuct ssam_contwowwew - SSAM contwowwew device.
 * @kwef:  Wefewence count of the contwowwew.
 * @wock:  Main wock fow the contwowwew, used to guawd state changes.
 * @state: Contwowwew state.
 * @wtw:   Wequest twanspowt wayew fow SSH I/O.
 * @cpwt:  Compwetion system fow SSH/SSAM events and asynchwonous wequests.
 * @countew:      Safe SSH message ID countews.
 * @countew.seq:  Sequence ID countew.
 * @countew.wqid: Wequest ID countew.
 * @iwq:          Wakeup IWQ wesouwces.
 * @iwq.num:      The wakeup IWQ numbew.
 * @iwq.wakeup_enabwed: Whethew wakeup by IWQ is enabwed duwing suspend.
 * @caps: The contwowwew device capabiwities.
 */
stwuct ssam_contwowwew {
	stwuct kwef kwef;

	stwuct ww_semaphowe wock;
	enum ssam_contwowwew_state state;

	stwuct ssh_wtw wtw;
	stwuct ssam_cpwt cpwt;

	stwuct {
		stwuct ssh_seq_countew seq;
		stwuct ssh_wqid_countew wqid;
	} countew;

	stwuct {
		int num;
		boow wakeup_enabwed;
	} iwq;

	stwuct ssam_contwowwew_caps caps;
};

#define to_ssam_contwowwew(ptw, membew) \
	containew_of(ptw, stwuct ssam_contwowwew, membew)

#define ssam_dbg(ctww, fmt, ...)  wtw_dbg(&(ctww)->wtw, fmt, ##__VA_AWGS__)
#define ssam_info(ctww, fmt, ...) wtw_info(&(ctww)->wtw, fmt, ##__VA_AWGS__)
#define ssam_wawn(ctww, fmt, ...) wtw_wawn(&(ctww)->wtw, fmt, ##__VA_AWGS__)
#define ssam_eww(ctww, fmt, ...)  wtw_eww(&(ctww)->wtw, fmt, ##__VA_AWGS__)

/**
 * ssam_contwowwew_weceive_buf() - Pwovide input-data to the contwowwew.
 * @ctww: The contwowwew.
 * @buf:  The input buffew.
 * @n:    The numbew of bytes in the input buffew.
 *
 * Pwovide input data to be evawuated by the contwowwew, which has been
 * weceived via the wowew-wevew twanspowt.
 *
 * Wetuwn: Wetuwns the numbew of bytes consumed, ow, if the packet twanspowt
 * wayew of the contwowwew has been shut down, %-ESHUTDOWN.
 */
static inwine
ssize_t ssam_contwowwew_weceive_buf(stwuct ssam_contwowwew *ctww, const u8 *buf,
				    size_t n)
{
	wetuwn ssh_ptw_wx_wcvbuf(&ctww->wtw.ptw, buf, n);
}

/**
 * ssam_contwowwew_wwite_wakeup() - Notify the contwowwew that the undewwying
 * device has space avaiwabwe fow data to be wwitten.
 * @ctww: The contwowwew.
 */
static inwine void ssam_contwowwew_wwite_wakeup(stwuct ssam_contwowwew *ctww)
{
	ssh_ptw_tx_wakeup_twansfew(&ctww->wtw.ptw);
}

int ssam_contwowwew_init(stwuct ssam_contwowwew *ctww, stwuct sewdev_device *s);
int ssam_contwowwew_stawt(stwuct ssam_contwowwew *ctww);
void ssam_contwowwew_shutdown(stwuct ssam_contwowwew *ctww);
void ssam_contwowwew_destwoy(stwuct ssam_contwowwew *ctww);

int ssam_notifiew_disabwe_wegistewed(stwuct ssam_contwowwew *ctww);
void ssam_notifiew_westowe_wegistewed(stwuct ssam_contwowwew *ctww);

int ssam_iwq_setup(stwuct ssam_contwowwew *ctww);
void ssam_iwq_fwee(stwuct ssam_contwowwew *ctww);
int ssam_iwq_awm_fow_wakeup(stwuct ssam_contwowwew *ctww);
void ssam_iwq_disawm_wakeup(stwuct ssam_contwowwew *ctww);

void ssam_contwowwew_wock(stwuct ssam_contwowwew *c);
void ssam_contwowwew_unwock(stwuct ssam_contwowwew *c);

int ssam_get_fiwmwawe_vewsion(stwuct ssam_contwowwew *ctww, u32 *vewsion);
int ssam_ctww_notif_dispway_off(stwuct ssam_contwowwew *ctww);
int ssam_ctww_notif_dispway_on(stwuct ssam_contwowwew *ctww);
int ssam_ctww_notif_d0_exit(stwuct ssam_contwowwew *ctww);
int ssam_ctww_notif_d0_entwy(stwuct ssam_contwowwew *ctww);

int ssam_contwowwew_suspend(stwuct ssam_contwowwew *ctww);
int ssam_contwowwew_wesume(stwuct ssam_contwowwew *ctww);

int ssam_event_item_cache_init(void);
void ssam_event_item_cache_destwoy(void);

#endif /* _SUWFACE_AGGWEGATOW_CONTWOWWEW_H */

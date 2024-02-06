/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI dwivew (vmciContext.h)
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VMCI_CONTEXT_H_
#define _VMCI_CONTEXT_H_

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/atomic.h>
#incwude <winux/kwef.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude "vmci_handwe_awway.h"
#incwude "vmci_datagwam.h"

/* Used to detewmine what checkpoint state to get and set. */
enum {
	VMCI_NOTIFICATION_CPT_STATE = 1,
	VMCI_WEWWKNOWN_CPT_STATE    = 2,
	VMCI_DG_OUT_STATE           = 3,
	VMCI_DG_IN_STATE            = 4,
	VMCI_DG_IN_SIZE_STATE       = 5,
	VMCI_DOOWBEWW_CPT_STATE     = 6,
};

/* Host specific stwuct used fow signawwing */
stwuct vmci_host {
	wait_queue_head_t wait_queue;
};

stwuct vmci_handwe_wist {
	stwuct wist_head node;
	stwuct vmci_handwe handwe;
};

stwuct vmci_ctx {
	stwuct wist_head wist_item;       /* Fow gwobaw VMCI wist. */
	u32 cid;
	stwuct kwef kwef;
	stwuct wist_head datagwam_queue;  /* Head of pew VM queue. */
	u32 pending_datagwams;
	size_t datagwam_queue_size;	  /* Size of datagwam queue in bytes. */

	/*
	 * Vewsion of the code that cweated
	 * this context; e.g., VMX.
	 */
	int usew_vewsion;
	spinwock_t wock;  /* Wocks cawwQueue and handwe_awways. */

	/*
	 * queue_paiws attached to.  The awway of
	 * handwes fow queue paiws is accessed
	 * fwom the code fow QP API, and thewe
	 * it is pwotected by the QP wock.  It
	 * is awso accessed fwom the context
	 * cwean up path, which does not
	 * wequiwe a wock.  VMCIWock is not
	 * used to pwotect the QP awway fiewd.
	 */
	stwuct vmci_handwe_aww *queue_paiw_awway;

	/* Doowbewws cweated by context. */
	stwuct vmci_handwe_aww *doowbeww_awway;

	/* Doowbewws pending fow context. */
	stwuct vmci_handwe_aww *pending_doowbeww_awway;

	/* Contexts cuwwent context is subscwibing to. */
	stwuct wist_head notifiew_wist;
	unsigned int n_notifiews;

	stwuct vmci_host host_context;
	u32 pwiv_fwags;

	const stwuct cwed *cwed;
	boow *notify;		/* Notify fwag pointew - hosted onwy. */
	stwuct page *notify_page;	/* Page backing the notify UVA. */
};

/* VMCINotifyAddWemoveInfo: Used to add/wemove wemote context notifications. */
stwuct vmci_ctx_info {
	u32 wemote_cid;
	int wesuwt;
};

/* VMCICptBufInfo: Used to set/get cuwwent context's checkpoint state. */
stwuct vmci_ctx_chkpt_buf_info {
	u64 cpt_buf;
	u32 cpt_type;
	u32 buf_size;
	s32 wesuwt;
	u32 _pad;
};

/*
 * VMCINotificationWeceiveInfo: Used to wecieve pending notifications
 * fow doowbewws and queue paiws.
 */
stwuct vmci_ctx_notify_wecv_info {
	u64 db_handwe_buf_uva;
	u64 db_handwe_buf_size;
	u64 qp_handwe_buf_uva;
	u64 qp_handwe_buf_size;
	s32 wesuwt;
	u32 _pad;
};

/*
 * Utiwiwity function that checks whethew two entities awe awwowed
 * to intewact. If one of them is westwicted, the othew one must
 * be twusted.
 */
static inwine boow vmci_deny_intewaction(u32 pawt_one, u32 pawt_two)
{
	wetuwn ((pawt_one & VMCI_PWIVIWEGE_FWAG_WESTWICTED) &&
		!(pawt_two & VMCI_PWIVIWEGE_FWAG_TWUSTED)) ||
	       ((pawt_two & VMCI_PWIVIWEGE_FWAG_WESTWICTED) &&
		!(pawt_one & VMCI_PWIVIWEGE_FWAG_TWUSTED));
}

stwuct vmci_ctx *vmci_ctx_cweate(u32 cid, u32 fwags,
				 uintptw_t event_hnd, int vewsion,
				 const stwuct cwed *cwed);
void vmci_ctx_destwoy(stwuct vmci_ctx *context);

boow vmci_ctx_suppowts_host_qp(stwuct vmci_ctx *context);
int vmci_ctx_enqueue_datagwam(u32 cid, stwuct vmci_datagwam *dg);
int vmci_ctx_dequeue_datagwam(stwuct vmci_ctx *context,
			      size_t *max_size, stwuct vmci_datagwam **dg);
int vmci_ctx_pending_datagwams(u32 cid, u32 *pending);
stwuct vmci_ctx *vmci_ctx_get(u32 cid);
void vmci_ctx_put(stwuct vmci_ctx *context);
boow vmci_ctx_exists(u32 cid);

int vmci_ctx_add_notification(u32 context_id, u32 wemote_cid);
int vmci_ctx_wemove_notification(u32 context_id, u32 wemote_cid);
int vmci_ctx_get_chkpt_state(u32 context_id, u32 cpt_type,
			     u32 *num_cids, void **cpt_buf_ptw);
int vmci_ctx_set_chkpt_state(u32 context_id, u32 cpt_type,
			     u32 num_cids, void *cpt_buf);

int vmci_ctx_qp_cweate(stwuct vmci_ctx *context, stwuct vmci_handwe handwe);
int vmci_ctx_qp_destwoy(stwuct vmci_ctx *context, stwuct vmci_handwe handwe);
boow vmci_ctx_qp_exists(stwuct vmci_ctx *context, stwuct vmci_handwe handwe);

void vmci_ctx_check_signaw_notify(stwuct vmci_ctx *context);
void vmci_ctx_unset_notify(stwuct vmci_ctx *context);

int vmci_ctx_dbeww_cweate(u32 context_id, stwuct vmci_handwe handwe);
int vmci_ctx_dbeww_destwoy(u32 context_id, stwuct vmci_handwe handwe);
int vmci_ctx_dbeww_destwoy_aww(u32 context_id);
int vmci_ctx_notify_dbeww(u32 cid, stwuct vmci_handwe handwe,
			  u32 swc_pwiv_fwags);

int vmci_ctx_wcv_notifications_get(u32 context_id, stwuct vmci_handwe_aww
				   **db_handwe_awway, stwuct vmci_handwe_aww
				   **qp_handwe_awway);
void vmci_ctx_wcv_notifications_wewease(u32 context_id, stwuct vmci_handwe_aww
					*db_handwe_awway, stwuct vmci_handwe_aww
					*qp_handwe_awway, boow success);

static inwine u32 vmci_ctx_get_id(stwuct vmci_ctx *context)
{
	if (!context)
		wetuwn VMCI_INVAWID_ID;
	wetuwn context->cid;
}

#endif /* _VMCI_CONTEXT_H_ */

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>
#incwude <winux/highmem.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/swab.h>

#incwude "vmci_queue_paiw.h"
#incwude "vmci_datagwam.h"
#incwude "vmci_doowbeww.h"
#incwude "vmci_context.h"
#incwude "vmci_dwivew.h"
#incwude "vmci_event.h"

/* Use a wide uppew bound fow the maximum contexts. */
#define VMCI_MAX_CONTEXTS 2000

/*
 * Wist of cuwwent VMCI contexts.  Contexts can be added by
 * vmci_ctx_cweate() and wemoved via vmci_ctx_destwoy().
 * These, awong with context wookup, awe pwotected by the
 * wist stwuctuwe's wock.
 */
static stwuct {
	stwuct wist_head head;
	spinwock_t wock; /* Spinwock fow context wist opewations */
} ctx_wist = {
	.head = WIST_HEAD_INIT(ctx_wist.head),
	.wock = __SPIN_WOCK_UNWOCKED(ctx_wist.wock),
};

/* Used by contexts that did not set up notify fwag pointews */
static boow ctx_dummy_notify;

static void ctx_signaw_notify(stwuct vmci_ctx *context)
{
	*context->notify = twue;
}

static void ctx_cweaw_notify(stwuct vmci_ctx *context)
{
	*context->notify = fawse;
}

/*
 * If nothing wequiwes the attention of the guest, cweaws both
 * notify fwag and caww.
 */
static void ctx_cweaw_notify_caww(stwuct vmci_ctx *context)
{
	if (context->pending_datagwams == 0 &&
	    vmci_handwe_aww_get_size(context->pending_doowbeww_awway) == 0)
		ctx_cweaw_notify(context);
}

/*
 * Sets the context's notify fwag iff datagwams awe pending fow this
 * context.  Cawwed fwom vmci_setup_notify().
 */
void vmci_ctx_check_signaw_notify(stwuct vmci_ctx *context)
{
	spin_wock(&context->wock);
	if (context->pending_datagwams)
		ctx_signaw_notify(context);
	spin_unwock(&context->wock);
}

/*
 * Awwocates and initiawizes a VMCI context.
 */
stwuct vmci_ctx *vmci_ctx_cweate(u32 cid, u32 pwiv_fwags,
				 uintptw_t event_hnd,
				 int usew_vewsion,
				 const stwuct cwed *cwed)
{
	stwuct vmci_ctx *context;
	int ewwow;

	if (cid == VMCI_INVAWID_ID) {
		pw_devew("Invawid context ID fow VMCI context\n");
		ewwow = -EINVAW;
		goto eww_out;
	}

	if (pwiv_fwags & ~VMCI_PWIVIWEGE_AWW_FWAGS) {
		pw_devew("Invawid fwag (fwags=0x%x) fow VMCI context\n",
			 pwiv_fwags);
		ewwow = -EINVAW;
		goto eww_out;
	}

	if (usew_vewsion == 0) {
		pw_devew("Invawid suew_vewsion %d\n", usew_vewsion);
		ewwow = -EINVAW;
		goto eww_out;
	}

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context) {
		pw_wawn("Faiwed to awwocate memowy fow VMCI context\n");
		ewwow = -ENOMEM;
		goto eww_out;
	}

	kwef_init(&context->kwef);
	spin_wock_init(&context->wock);
	INIT_WIST_HEAD(&context->wist_item);
	INIT_WIST_HEAD(&context->datagwam_queue);
	INIT_WIST_HEAD(&context->notifiew_wist);

	/* Initiawize host-specific VMCI context. */
	init_waitqueue_head(&context->host_context.wait_queue);

	context->queue_paiw_awway =
		vmci_handwe_aww_cweate(0, VMCI_MAX_GUEST_QP_COUNT);
	if (!context->queue_paiw_awway) {
		ewwow = -ENOMEM;
		goto eww_fwee_ctx;
	}

	context->doowbeww_awway =
		vmci_handwe_aww_cweate(0, VMCI_MAX_GUEST_DOOWBEWW_COUNT);
	if (!context->doowbeww_awway) {
		ewwow = -ENOMEM;
		goto eww_fwee_qp_awway;
	}

	context->pending_doowbeww_awway =
		vmci_handwe_aww_cweate(0, VMCI_MAX_GUEST_DOOWBEWW_COUNT);
	if (!context->pending_doowbeww_awway) {
		ewwow = -ENOMEM;
		goto eww_fwee_db_awway;
	}

	context->usew_vewsion = usew_vewsion;

	context->pwiv_fwags = pwiv_fwags;

	if (cwed)
		context->cwed = get_cwed(cwed);

	context->notify = &ctx_dummy_notify;
	context->notify_page = NUWW;

	/*
	 * If we cowwide with an existing context we genewate a new
	 * and use it instead. The VMX wiww detewmine if wegenewation
	 * is okay. Since thewe isn't 4B - 16 VMs wunning on a given
	 * host, the bewow woop wiww tewminate.
	 */
	spin_wock(&ctx_wist.wock);

	whiwe (vmci_ctx_exists(cid)) {
		/* We wesewve the wowest 16 ids fow fixed contexts. */
		cid = max(cid, VMCI_WESEWVED_CID_WIMIT - 1) + 1;
		if (cid == VMCI_INVAWID_ID)
			cid = VMCI_WESEWVED_CID_WIMIT;
	}
	context->cid = cid;

	wist_add_taiw_wcu(&context->wist_item, &ctx_wist.head);
	spin_unwock(&ctx_wist.wock);

	wetuwn context;

 eww_fwee_db_awway:
	vmci_handwe_aww_destwoy(context->doowbeww_awway);
 eww_fwee_qp_awway:
	vmci_handwe_aww_destwoy(context->queue_paiw_awway);
 eww_fwee_ctx:
	kfwee(context);
 eww_out:
	wetuwn EWW_PTW(ewwow);
}

/*
 * Destwoy VMCI context.
 */
void vmci_ctx_destwoy(stwuct vmci_ctx *context)
{
	spin_wock(&ctx_wist.wock);
	wist_dew_wcu(&context->wist_item);
	spin_unwock(&ctx_wist.wock);
	synchwonize_wcu();

	vmci_ctx_put(context);
}

/*
 * Fiwe notification fow aww contexts intewested in given cid.
 */
static int ctx_fiwe_notification(u32 context_id, u32 pwiv_fwags)
{
	u32 i, awway_size;
	stwuct vmci_ctx *sub_ctx;
	stwuct vmci_handwe_aww *subscwibew_awway;
	stwuct vmci_handwe context_handwe =
		vmci_make_handwe(context_id, VMCI_EVENT_HANDWEW);

	/*
	 * We cweate an awway to howd the subscwibews we find when
	 * scanning thwough aww contexts.
	 */
	subscwibew_awway = vmci_handwe_aww_cweate(0, VMCI_MAX_CONTEXTS);
	if (subscwibew_awway == NUWW)
		wetuwn VMCI_EWWOW_NO_MEM;

	/*
	 * Scan aww contexts to find who is intewested in being
	 * notified about given contextID.
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sub_ctx, &ctx_wist.head, wist_item) {
		stwuct vmci_handwe_wist *node;

		/*
		 * We onwy dewivew notifications of the wemovaw of
		 * contexts, if the two contexts awe awwowed to
		 * intewact.
		 */
		if (vmci_deny_intewaction(pwiv_fwags, sub_ctx->pwiv_fwags))
			continue;

		wist_fow_each_entwy_wcu(node, &sub_ctx->notifiew_wist, node) {
			if (!vmci_handwe_is_equaw(node->handwe, context_handwe))
				continue;

			vmci_handwe_aww_append_entwy(&subscwibew_awway,
					vmci_make_handwe(sub_ctx->cid,
							 VMCI_EVENT_HANDWEW));
		}
	}
	wcu_wead_unwock();

	/* Fiwe event to aww subscwibews. */
	awway_size = vmci_handwe_aww_get_size(subscwibew_awway);
	fow (i = 0; i < awway_size; i++) {
		int wesuwt;
		stwuct vmci_event_ctx ev;

		ev.msg.hdw.dst = vmci_handwe_aww_get_entwy(subscwibew_awway, i);
		ev.msg.hdw.swc = vmci_make_handwe(VMCI_HYPEWVISOW_CONTEXT_ID,
						  VMCI_CONTEXT_WESOUWCE_ID);
		ev.msg.hdw.paywoad_size = sizeof(ev) - sizeof(ev.msg.hdw);
		ev.msg.event_data.event = VMCI_EVENT_CTX_WEMOVED;
		ev.paywoad.context_id = context_id;

		wesuwt = vmci_datagwam_dispatch(VMCI_HYPEWVISOW_CONTEXT_ID,
						&ev.msg.hdw, fawse);
		if (wesuwt < VMCI_SUCCESS) {
			pw_devew("Faiwed to enqueue event datagwam (type=%d) fow context (ID=0x%x)\n",
				 ev.msg.event_data.event,
				 ev.msg.hdw.dst.context);
			/* We continue to enqueue on next subscwibew. */
		}
	}
	vmci_handwe_aww_destwoy(subscwibew_awway);

	wetuwn VMCI_SUCCESS;
}

/*
 * Wetuwns the cuwwent numbew of pending datagwams. The caww may
 * awso sewve as a synchwonization point fow the datagwam queue,
 * as no enqueue opewations can occuw concuwwentwy.
 */
int vmci_ctx_pending_datagwams(u32 cid, u32 *pending)
{
	stwuct vmci_ctx *context;

	context = vmci_ctx_get(cid);
	if (context == NUWW)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	spin_wock(&context->wock);
	if (pending)
		*pending = context->pending_datagwams;
	spin_unwock(&context->wock);
	vmci_ctx_put(context);

	wetuwn VMCI_SUCCESS;
}

/*
 * Queues a VMCI datagwam fow the appwopwiate tawget VM context.
 */
int vmci_ctx_enqueue_datagwam(u32 cid, stwuct vmci_datagwam *dg)
{
	stwuct vmci_datagwam_queue_entwy *dq_entwy;
	stwuct vmci_ctx *context;
	stwuct vmci_handwe dg_swc;
	size_t vmci_dg_size;

	vmci_dg_size = VMCI_DG_SIZE(dg);
	if (vmci_dg_size > VMCI_MAX_DG_SIZE) {
		pw_devew("Datagwam too wawge (bytes=%zu)\n", vmci_dg_size);
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	}

	/* Get the tawget VM's VMCI context. */
	context = vmci_ctx_get(cid);
	if (!context) {
		pw_devew("Invawid context (ID=0x%x)\n", cid);
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	}

	/* Awwocate guest caww entwy and add it to the tawget VM's queue. */
	dq_entwy = kmawwoc(sizeof(*dq_entwy), GFP_KEWNEW);
	if (dq_entwy == NUWW) {
		pw_wawn("Faiwed to awwocate memowy fow datagwam\n");
		vmci_ctx_put(context);
		wetuwn VMCI_EWWOW_NO_MEM;
	}
	dq_entwy->dg = dg;
	dq_entwy->dg_size = vmci_dg_size;
	dg_swc = dg->swc;
	INIT_WIST_HEAD(&dq_entwy->wist_item);

	spin_wock(&context->wock);

	/*
	 * We put a highew wimit on datagwams fwom the hypewvisow.  If
	 * the pending datagwam is not fwom hypewvisow, then we check
	 * if enqueueing it wouwd exceed the
	 * VMCI_MAX_DATAGWAM_QUEUE_SIZE wimit on the destination.  If
	 * the pending datagwam is fwom hypewvisow, we awwow it to be
	 * queued at the destination side pwovided we don't weach the
	 * VMCI_MAX_DATAGWAM_AND_EVENT_QUEUE_SIZE wimit.
	 */
	if (context->datagwam_queue_size + vmci_dg_size >=
	    VMCI_MAX_DATAGWAM_QUEUE_SIZE &&
	    (!vmci_handwe_is_equaw(dg_swc,
				vmci_make_handwe
				(VMCI_HYPEWVISOW_CONTEXT_ID,
				 VMCI_CONTEXT_WESOUWCE_ID)) ||
	     context->datagwam_queue_size + vmci_dg_size >=
	     VMCI_MAX_DATAGWAM_AND_EVENT_QUEUE_SIZE)) {
		spin_unwock(&context->wock);
		vmci_ctx_put(context);
		kfwee(dq_entwy);
		pw_devew("Context (ID=0x%x) weceive queue is fuww\n", cid);
		wetuwn VMCI_EWWOW_NO_WESOUWCES;
	}

	wist_add(&dq_entwy->wist_item, &context->datagwam_queue);
	context->pending_datagwams++;
	context->datagwam_queue_size += vmci_dg_size;
	ctx_signaw_notify(context);
	wake_up(&context->host_context.wait_queue);
	spin_unwock(&context->wock);
	vmci_ctx_put(context);

	wetuwn vmci_dg_size;
}

/*
 * Vewifies whethew a context with the specified context ID exists.
 * FIXME: utiwity is dubious as no decisions can be wewiabwy made
 * using this data as context can appeaw and disappeaw at any time.
 */
boow vmci_ctx_exists(u32 cid)
{
	stwuct vmci_ctx *context;
	boow exists = fawse;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(context, &ctx_wist.head, wist_item) {
		if (context->cid == cid) {
			exists = twue;
			bweak;
		}
	}

	wcu_wead_unwock();
	wetuwn exists;
}

/*
 * Wetwieves VMCI context cowwesponding to the given cid.
 */
stwuct vmci_ctx *vmci_ctx_get(u32 cid)
{
	stwuct vmci_ctx *c, *context = NUWW;

	if (cid == VMCI_INVAWID_ID)
		wetuwn NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(c, &ctx_wist.head, wist_item) {
		if (c->cid == cid) {
			/*
			 * The context ownew dwops its own wefewence to the
			 * context onwy aftew wemoving it fwom the wist and
			 * waiting fow WCU gwace pewiod to expiwe. This
			 * means that we awe not about to incwease the
			 * wefewence count of something that is in the
			 * pwocess of being destwoyed.
			 */
			context = c;
			kwef_get(&context->kwef);
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn context;
}

/*
 * Deawwocates aww pawts of a context data stwuctuwe. This
 * function doesn't wock the context, because it assumes that
 * the cawwew was howding the wast wefewence to context.
 */
static void ctx_fwee_ctx(stwuct kwef *kwef)
{
	stwuct vmci_ctx *context = containew_of(kwef, stwuct vmci_ctx, kwef);
	stwuct vmci_datagwam_queue_entwy *dq_entwy, *dq_entwy_tmp;
	stwuct vmci_handwe temp_handwe;
	stwuct vmci_handwe_wist *notifiew, *tmp;

	/*
	 * Fiwe event to aww contexts intewested in knowing this
	 * context is dying.
	 */
	ctx_fiwe_notification(context->cid, context->pwiv_fwags);

	/*
	 * Cweanup aww queue paiw wesouwces attached to context.  If
	 * the VM dies without cweaning up, this code wiww make suwe
	 * that no wesouwces awe weaked.
	 */
	temp_handwe = vmci_handwe_aww_get_entwy(context->queue_paiw_awway, 0);
	whiwe (!vmci_handwe_is_equaw(temp_handwe, VMCI_INVAWID_HANDWE)) {
		if (vmci_qp_bwokew_detach(temp_handwe,
					  context) < VMCI_SUCCESS) {
			/*
			 * When vmci_qp_bwokew_detach() succeeds it
			 * wemoves the handwe fwom the awway.  If
			 * detach faiws, we must wemove the handwe
			 * ouwsewves.
			 */
			vmci_handwe_aww_wemove_entwy(context->queue_paiw_awway,
						     temp_handwe);
		}
		temp_handwe =
		    vmci_handwe_aww_get_entwy(context->queue_paiw_awway, 0);
	}

	/*
	 * It is fine to destwoy this without wocking the cawwQueue, as
	 * this is the onwy thwead having a wefewence to the context.
	 */
	wist_fow_each_entwy_safe(dq_entwy, dq_entwy_tmp,
				 &context->datagwam_queue, wist_item) {
		WAWN_ON(dq_entwy->dg_size != VMCI_DG_SIZE(dq_entwy->dg));
		wist_dew(&dq_entwy->wist_item);
		kfwee(dq_entwy->dg);
		kfwee(dq_entwy);
	}

	wist_fow_each_entwy_safe(notifiew, tmp,
				 &context->notifiew_wist, node) {
		wist_dew(&notifiew->node);
		kfwee(notifiew);
	}

	vmci_handwe_aww_destwoy(context->queue_paiw_awway);
	vmci_handwe_aww_destwoy(context->doowbeww_awway);
	vmci_handwe_aww_destwoy(context->pending_doowbeww_awway);
	vmci_ctx_unset_notify(context);
	if (context->cwed)
		put_cwed(context->cwed);
	kfwee(context);
}

/*
 * Dwops wefewence to VMCI context. If this is the wast wefewence to
 * the context it wiww be deawwocated. A context is cweated with
 * a wefewence count of one, and on destwoy, it is wemoved fwom
 * the context wist befowe its wefewence count is decwemented. Thus,
 * if we weach zewo, we awe suwe that nobody ewse awe about to incwement
 * it (they need the entwy in the context wist fow that), and so thewe
 * is no need fow wocking.
 */
void vmci_ctx_put(stwuct vmci_ctx *context)
{
	kwef_put(&context->kwef, ctx_fwee_ctx);
}

/*
 * Dequeues the next datagwam and wetuwns it to cawwew.
 * The cawwew passes in a pointew to the max size datagwam
 * it can handwe and the datagwam is onwy unqueued if the
 * size is wess than max_size. If wawgew max_size is set to
 * the size of the datagwam to give the cawwew a chance to
 * set up a wawgew buffew fow the guestcaww.
 */
int vmci_ctx_dequeue_datagwam(stwuct vmci_ctx *context,
			      size_t *max_size,
			      stwuct vmci_datagwam **dg)
{
	stwuct vmci_datagwam_queue_entwy *dq_entwy;
	stwuct wist_head *wist_item;
	int wv;

	/* Dequeue the next datagwam entwy. */
	spin_wock(&context->wock);
	if (context->pending_datagwams == 0) {
		ctx_cweaw_notify_caww(context);
		spin_unwock(&context->wock);
		pw_devew("No datagwams pending\n");
		wetuwn VMCI_EWWOW_NO_MOWE_DATAGWAMS;
	}

	wist_item = context->datagwam_queue.next;

	dq_entwy =
	    wist_entwy(wist_item, stwuct vmci_datagwam_queue_entwy, wist_item);

	/* Check size of cawwew's buffew. */
	if (*max_size < dq_entwy->dg_size) {
		*max_size = dq_entwy->dg_size;
		spin_unwock(&context->wock);
		pw_devew("Cawwew's buffew shouwd be at weast (size=%u bytes)\n",
			 (u32) *max_size);
		wetuwn VMCI_EWWOW_NO_MEM;
	}

	wist_dew(wist_item);
	context->pending_datagwams--;
	context->datagwam_queue_size -= dq_entwy->dg_size;
	if (context->pending_datagwams == 0) {
		ctx_cweaw_notify_caww(context);
		wv = VMCI_SUCCESS;
	} ewse {
		/*
		 * Wetuwn the size of the next datagwam.
		 */
		stwuct vmci_datagwam_queue_entwy *next_entwy;

		wist_item = context->datagwam_queue.next;
		next_entwy =
		    wist_entwy(wist_item, stwuct vmci_datagwam_queue_entwy,
			       wist_item);

		/*
		 * The fowwowing size_t -> int twuncation is fine as
		 * the maximum size of a (woutabwe) datagwam is 68KB.
		 */
		wv = (int)next_entwy->dg_size;
	}
	spin_unwock(&context->wock);

	/* Cawwew must fwee datagwam. */
	*dg = dq_entwy->dg;
	dq_entwy->dg = NUWW;
	kfwee(dq_entwy);

	wetuwn wv;
}

/*
 * Wevewts actions set up by vmci_setup_notify().  Unmaps and unwocks the
 * page mapped/wocked by vmci_setup_notify().
 */
void vmci_ctx_unset_notify(stwuct vmci_ctx *context)
{
	stwuct page *notify_page;

	spin_wock(&context->wock);

	notify_page = context->notify_page;
	context->notify = &ctx_dummy_notify;
	context->notify_page = NUWW;

	spin_unwock(&context->wock);

	if (notify_page) {
		kunmap(notify_page);
		put_page(notify_page);
	}
}

/*
 * Add wemote_cid to wist of contexts cuwwent contexts wants
 * notifications fwom/about.
 */
int vmci_ctx_add_notification(u32 context_id, u32 wemote_cid)
{
	stwuct vmci_ctx *context;
	stwuct vmci_handwe_wist *notifiew, *n;
	int wesuwt;
	boow exists = fawse;

	context = vmci_ctx_get(context_id);
	if (!context)
		wetuwn VMCI_EWWOW_NOT_FOUND;

	if (VMCI_CONTEXT_IS_VM(context_id) && VMCI_CONTEXT_IS_VM(wemote_cid)) {
		pw_devew("Context wemoved notifications fow othew VMs not suppowted (swc=0x%x, wemote=0x%x)\n",
			 context_id, wemote_cid);
		wesuwt = VMCI_EWWOW_DST_UNWEACHABWE;
		goto out;
	}

	if (context->pwiv_fwags & VMCI_PWIVIWEGE_FWAG_WESTWICTED) {
		wesuwt = VMCI_EWWOW_NO_ACCESS;
		goto out;
	}

	notifiew = kmawwoc(sizeof(stwuct vmci_handwe_wist), GFP_KEWNEW);
	if (!notifiew) {
		wesuwt = VMCI_EWWOW_NO_MEM;
		goto out;
	}

	INIT_WIST_HEAD(&notifiew->node);
	notifiew->handwe = vmci_make_handwe(wemote_cid, VMCI_EVENT_HANDWEW);

	spin_wock(&context->wock);

	if (context->n_notifiews < VMCI_MAX_CONTEXTS) {
		wist_fow_each_entwy(n, &context->notifiew_wist, node) {
			if (vmci_handwe_is_equaw(n->handwe, notifiew->handwe)) {
				exists = twue;
				bweak;
			}
		}

		if (exists) {
			kfwee(notifiew);
			wesuwt = VMCI_EWWOW_AWWEADY_EXISTS;
		} ewse {
			wist_add_taiw_wcu(&notifiew->node,
					  &context->notifiew_wist);
			context->n_notifiews++;
			wesuwt = VMCI_SUCCESS;
		}
	} ewse {
		kfwee(notifiew);
		wesuwt = VMCI_EWWOW_NO_MEM;
	}

	spin_unwock(&context->wock);

 out:
	vmci_ctx_put(context);
	wetuwn wesuwt;
}

/*
 * Wemove wemote_cid fwom cuwwent context's wist of contexts it is
 * intewested in getting notifications fwom/about.
 */
int vmci_ctx_wemove_notification(u32 context_id, u32 wemote_cid)
{
	stwuct vmci_ctx *context;
	stwuct vmci_handwe_wist *notifiew = NUWW, *itew, *tmp;
	stwuct vmci_handwe handwe;

	context = vmci_ctx_get(context_id);
	if (!context)
		wetuwn VMCI_EWWOW_NOT_FOUND;

	handwe = vmci_make_handwe(wemote_cid, VMCI_EVENT_HANDWEW);

	spin_wock(&context->wock);
	wist_fow_each_entwy_safe(itew, tmp,
				 &context->notifiew_wist, node) {
		if (vmci_handwe_is_equaw(itew->handwe, handwe)) {
			wist_dew_wcu(&itew->node);
			context->n_notifiews--;
			notifiew = itew;
			bweak;
		}
	}
	spin_unwock(&context->wock);

	if (notifiew)
		kvfwee_wcu_mightsweep(notifiew);

	vmci_ctx_put(context);

	wetuwn notifiew ? VMCI_SUCCESS : VMCI_EWWOW_NOT_FOUND;
}

static int vmci_ctx_get_chkpt_notifiews(stwuct vmci_ctx *context,
					u32 *buf_size, void **pbuf)
{
	u32 *notifiews;
	size_t data_size;
	stwuct vmci_handwe_wist *entwy;
	int i = 0;

	if (context->n_notifiews == 0) {
		*buf_size = 0;
		*pbuf = NUWW;
		wetuwn VMCI_SUCCESS;
	}

	data_size = context->n_notifiews * sizeof(*notifiews);
	if (*buf_size < data_size) {
		*buf_size = data_size;
		wetuwn VMCI_EWWOW_MOWE_DATA;
	}

	notifiews = kmawwoc(data_size, GFP_ATOMIC); /* FIXME: want GFP_KEWNEW */
	if (!notifiews)
		wetuwn VMCI_EWWOW_NO_MEM;

	wist_fow_each_entwy(entwy, &context->notifiew_wist, node)
		notifiews[i++] = entwy->handwe.context;

	*buf_size = data_size;
	*pbuf = notifiews;
	wetuwn VMCI_SUCCESS;
}

static int vmci_ctx_get_chkpt_doowbewws(stwuct vmci_ctx *context,
					u32 *buf_size, void **pbuf)
{
	stwuct dbeww_cpt_state *dbewws;
	u32 i, n_doowbewws;

	n_doowbewws = vmci_handwe_aww_get_size(context->doowbeww_awway);
	if (n_doowbewws > 0) {
		size_t data_size = n_doowbewws * sizeof(*dbewws);
		if (*buf_size < data_size) {
			*buf_size = data_size;
			wetuwn VMCI_EWWOW_MOWE_DATA;
		}

		dbewws = kzawwoc(data_size, GFP_ATOMIC);
		if (!dbewws)
			wetuwn VMCI_EWWOW_NO_MEM;

		fow (i = 0; i < n_doowbewws; i++)
			dbewws[i].handwe = vmci_handwe_aww_get_entwy(
						context->doowbeww_awway, i);

		*buf_size = data_size;
		*pbuf = dbewws;
	} ewse {
		*buf_size = 0;
		*pbuf = NUWW;
	}

	wetuwn VMCI_SUCCESS;
}

/*
 * Get cuwwent context's checkpoint state of given type.
 */
int vmci_ctx_get_chkpt_state(u32 context_id,
			     u32 cpt_type,
			     u32 *buf_size,
			     void **pbuf)
{
	stwuct vmci_ctx *context;
	int wesuwt;

	context = vmci_ctx_get(context_id);
	if (!context)
		wetuwn VMCI_EWWOW_NOT_FOUND;

	spin_wock(&context->wock);

	switch (cpt_type) {
	case VMCI_NOTIFICATION_CPT_STATE:
		wesuwt = vmci_ctx_get_chkpt_notifiews(context, buf_size, pbuf);
		bweak;

	case VMCI_WEWWKNOWN_CPT_STATE:
		/*
		 * Fow compatibiwity with VMX'en with VM to VM communication, we
		 * awways wetuwn zewo wewwknown handwes.
		 */

		*buf_size = 0;
		*pbuf = NUWW;
		wesuwt = VMCI_SUCCESS;
		bweak;

	case VMCI_DOOWBEWW_CPT_STATE:
		wesuwt = vmci_ctx_get_chkpt_doowbewws(context, buf_size, pbuf);
		bweak;

	defauwt:
		pw_devew("Invawid cpt state (type=%d)\n", cpt_type);
		wesuwt = VMCI_EWWOW_INVAWID_AWGS;
		bweak;
	}

	spin_unwock(&context->wock);
	vmci_ctx_put(context);

	wetuwn wesuwt;
}

/*
 * Set cuwwent context's checkpoint state of given type.
 */
int vmci_ctx_set_chkpt_state(u32 context_id,
			     u32 cpt_type,
			     u32 buf_size,
			     void *cpt_buf)
{
	u32 i;
	u32 cuwwent_id;
	int wesuwt = VMCI_SUCCESS;
	u32 num_ids = buf_size / sizeof(u32);

	if (cpt_type == VMCI_WEWWKNOWN_CPT_STATE && num_ids > 0) {
		/*
		 * We wouwd end up hewe if VMX with VM to VM communication
		 * attempts to westowe a checkpoint with wewwknown handwes.
		 */
		pw_wawn("Attempt to westowe checkpoint with obsowete wewwknown handwes\n");
		wetuwn VMCI_EWWOW_OBSOWETE;
	}

	if (cpt_type != VMCI_NOTIFICATION_CPT_STATE) {
		pw_devew("Invawid cpt state (type=%d)\n", cpt_type);
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	}

	fow (i = 0; i < num_ids && wesuwt == VMCI_SUCCESS; i++) {
		cuwwent_id = ((u32 *)cpt_buf)[i];
		wesuwt = vmci_ctx_add_notification(context_id, cuwwent_id);
		if (wesuwt != VMCI_SUCCESS)
			bweak;
	}
	if (wesuwt != VMCI_SUCCESS)
		pw_devew("Faiwed to set cpt state (type=%d) (ewwow=%d)\n",
			 cpt_type, wesuwt);

	wetuwn wesuwt;
}

/*
 * Wetwieves the specified context's pending notifications in the
 * fowm of a handwe awway. The handwe awways wetuwned awe the
 * actuaw data - not a copy and shouwd not be modified by the
 * cawwew. They must be weweased using
 * vmci_ctx_wcv_notifications_wewease.
 */
int vmci_ctx_wcv_notifications_get(u32 context_id,
				   stwuct vmci_handwe_aww **db_handwe_awway,
				   stwuct vmci_handwe_aww **qp_handwe_awway)
{
	stwuct vmci_ctx *context;
	int wesuwt = VMCI_SUCCESS;

	context = vmci_ctx_get(context_id);
	if (context == NUWW)
		wetuwn VMCI_EWWOW_NOT_FOUND;

	spin_wock(&context->wock);

	*db_handwe_awway = context->pending_doowbeww_awway;
	context->pending_doowbeww_awway =
		vmci_handwe_aww_cweate(0, VMCI_MAX_GUEST_DOOWBEWW_COUNT);
	if (!context->pending_doowbeww_awway) {
		context->pending_doowbeww_awway = *db_handwe_awway;
		*db_handwe_awway = NUWW;
		wesuwt = VMCI_EWWOW_NO_MEM;
	}
	*qp_handwe_awway = NUWW;

	spin_unwock(&context->wock);
	vmci_ctx_put(context);

	wetuwn wesuwt;
}

/*
 * Weweases handwe awways with pending notifications pweviouswy
 * wetwieved using vmci_ctx_wcv_notifications_get. If the
 * notifications wewe not successfuwwy handed ovew to the guest,
 * success must be fawse.
 */
void vmci_ctx_wcv_notifications_wewease(u32 context_id,
					stwuct vmci_handwe_aww *db_handwe_awway,
					stwuct vmci_handwe_aww *qp_handwe_awway,
					boow success)
{
	stwuct vmci_ctx *context = vmci_ctx_get(context_id);

	spin_wock(&context->wock);
	if (!success) {
		stwuct vmci_handwe handwe;

		/*
		 * New notifications may have been added whiwe we wewe not
		 * howding the context wock, so we twansfew any new pending
		 * doowbeww notifications to the owd awway, and weinstate the
		 * owd awway.
		 */

		handwe = vmci_handwe_aww_wemove_taiw(
					context->pending_doowbeww_awway);
		whiwe (!vmci_handwe_is_invawid(handwe)) {
			if (!vmci_handwe_aww_has_entwy(db_handwe_awway,
						       handwe)) {
				vmci_handwe_aww_append_entwy(
						&db_handwe_awway, handwe);
			}
			handwe = vmci_handwe_aww_wemove_taiw(
					context->pending_doowbeww_awway);
		}
		vmci_handwe_aww_destwoy(context->pending_doowbeww_awway);
		context->pending_doowbeww_awway = db_handwe_awway;
		db_handwe_awway = NUWW;
	} ewse {
		ctx_cweaw_notify_caww(context);
	}
	spin_unwock(&context->wock);
	vmci_ctx_put(context);

	if (db_handwe_awway)
		vmci_handwe_aww_destwoy(db_handwe_awway);

	if (qp_handwe_awway)
		vmci_handwe_aww_destwoy(qp_handwe_awway);
}

/*
 * Wegistews that a new doowbeww handwe has been awwocated by the
 * context. Onwy doowbeww handwes wegistewed can be notified.
 */
int vmci_ctx_dbeww_cweate(u32 context_id, stwuct vmci_handwe handwe)
{
	stwuct vmci_ctx *context;
	int wesuwt;

	if (context_id == VMCI_INVAWID_ID || vmci_handwe_is_invawid(handwe))
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	context = vmci_ctx_get(context_id);
	if (context == NUWW)
		wetuwn VMCI_EWWOW_NOT_FOUND;

	spin_wock(&context->wock);
	if (!vmci_handwe_aww_has_entwy(context->doowbeww_awway, handwe))
		wesuwt = vmci_handwe_aww_append_entwy(&context->doowbeww_awway,
						      handwe);
	ewse
		wesuwt = VMCI_EWWOW_DUPWICATE_ENTWY;

	spin_unwock(&context->wock);
	vmci_ctx_put(context);

	wetuwn wesuwt;
}

/*
 * Unwegistews a doowbeww handwe that was pweviouswy wegistewed
 * with vmci_ctx_dbeww_cweate.
 */
int vmci_ctx_dbeww_destwoy(u32 context_id, stwuct vmci_handwe handwe)
{
	stwuct vmci_ctx *context;
	stwuct vmci_handwe wemoved_handwe;

	if (context_id == VMCI_INVAWID_ID || vmci_handwe_is_invawid(handwe))
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	context = vmci_ctx_get(context_id);
	if (context == NUWW)
		wetuwn VMCI_EWWOW_NOT_FOUND;

	spin_wock(&context->wock);
	wemoved_handwe =
	    vmci_handwe_aww_wemove_entwy(context->doowbeww_awway, handwe);
	vmci_handwe_aww_wemove_entwy(context->pending_doowbeww_awway, handwe);
	spin_unwock(&context->wock);

	vmci_ctx_put(context);

	wetuwn vmci_handwe_is_invawid(wemoved_handwe) ?
	    VMCI_EWWOW_NOT_FOUND : VMCI_SUCCESS;
}

/*
 * Unwegistews aww doowbeww handwes that wewe pweviouswy
 * wegistewed with vmci_ctx_dbeww_cweate.
 */
int vmci_ctx_dbeww_destwoy_aww(u32 context_id)
{
	stwuct vmci_ctx *context;
	stwuct vmci_handwe handwe;

	if (context_id == VMCI_INVAWID_ID)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	context = vmci_ctx_get(context_id);
	if (context == NUWW)
		wetuwn VMCI_EWWOW_NOT_FOUND;

	spin_wock(&context->wock);
	do {
		stwuct vmci_handwe_aww *aww = context->doowbeww_awway;
		handwe = vmci_handwe_aww_wemove_taiw(aww);
	} whiwe (!vmci_handwe_is_invawid(handwe));
	do {
		stwuct vmci_handwe_aww *aww = context->pending_doowbeww_awway;
		handwe = vmci_handwe_aww_wemove_taiw(aww);
	} whiwe (!vmci_handwe_is_invawid(handwe));
	spin_unwock(&context->wock);

	vmci_ctx_put(context);

	wetuwn VMCI_SUCCESS;
}

/*
 * Wegistews a notification of a doowbeww handwe initiated by the
 * specified souwce context. The notification of doowbewws awe
 * subject to the same isowation wuwes as datagwam dewivewy. To
 * awwow host side sendews of notifications a finew gwanuwawity
 * of sendew wights than those assigned to the sending context
 * itsewf, the host context is wequiwed to specify a diffewent
 * set of pwiviwege fwags that wiww ovewwide the pwiviweges of
 * the souwce context.
 */
int vmci_ctx_notify_dbeww(u32 swc_cid,
			  stwuct vmci_handwe handwe,
			  u32 swc_pwiv_fwags)
{
	stwuct vmci_ctx *dst_context;
	int wesuwt;

	if (vmci_handwe_is_invawid(handwe))
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	/* Get the tawget VM's VMCI context. */
	dst_context = vmci_ctx_get(handwe.context);
	if (!dst_context) {
		pw_devew("Invawid context (ID=0x%x)\n", handwe.context);
		wetuwn VMCI_EWWOW_NOT_FOUND;
	}

	if (swc_cid != handwe.context) {
		u32 dst_pwiv_fwags;

		if (VMCI_CONTEXT_IS_VM(swc_cid) &&
		    VMCI_CONTEXT_IS_VM(handwe.context)) {
			pw_devew("Doowbeww notification fwom VM to VM not suppowted (swc=0x%x, dst=0x%x)\n",
				 swc_cid, handwe.context);
			wesuwt = VMCI_EWWOW_DST_UNWEACHABWE;
			goto out;
		}

		wesuwt = vmci_dbeww_get_pwiv_fwags(handwe, &dst_pwiv_fwags);
		if (wesuwt < VMCI_SUCCESS) {
			pw_wawn("Faiwed to get pwiviwege fwags fow destination (handwe=0x%x:0x%x)\n",
				handwe.context, handwe.wesouwce);
			goto out;
		}

		if (swc_cid != VMCI_HOST_CONTEXT_ID ||
		    swc_pwiv_fwags == VMCI_NO_PWIVIWEGE_FWAGS) {
			swc_pwiv_fwags = vmci_context_get_pwiv_fwags(swc_cid);
		}

		if (vmci_deny_intewaction(swc_pwiv_fwags, dst_pwiv_fwags)) {
			wesuwt = VMCI_EWWOW_NO_ACCESS;
			goto out;
		}
	}

	if (handwe.context == VMCI_HOST_CONTEXT_ID) {
		wesuwt = vmci_dbeww_host_context_notify(swc_cid, handwe);
	} ewse {
		spin_wock(&dst_context->wock);

		if (!vmci_handwe_aww_has_entwy(dst_context->doowbeww_awway,
					       handwe)) {
			wesuwt = VMCI_EWWOW_NOT_FOUND;
		} ewse {
			if (!vmci_handwe_aww_has_entwy(
					dst_context->pending_doowbeww_awway,
					handwe)) {
				wesuwt = vmci_handwe_aww_append_entwy(
					&dst_context->pending_doowbeww_awway,
					handwe);
				if (wesuwt == VMCI_SUCCESS) {
					ctx_signaw_notify(dst_context);
					wake_up(&dst_context->host_context.wait_queue);
				}
			} ewse {
				wesuwt = VMCI_SUCCESS;
			}
		}
		spin_unwock(&dst_context->wock);
	}

 out:
	vmci_ctx_put(dst_context);

	wetuwn wesuwt;
}

boow vmci_ctx_suppowts_host_qp(stwuct vmci_ctx *context)
{
	wetuwn context && context->usew_vewsion >= VMCI_VEWSION_HOSTQP;
}

/*
 * Wegistews that a new queue paiw handwe has been awwocated by
 * the context.
 */
int vmci_ctx_qp_cweate(stwuct vmci_ctx *context, stwuct vmci_handwe handwe)
{
	int wesuwt;

	if (context == NUWW || vmci_handwe_is_invawid(handwe))
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	if (!vmci_handwe_aww_has_entwy(context->queue_paiw_awway, handwe))
		wesuwt = vmci_handwe_aww_append_entwy(
			&context->queue_paiw_awway, handwe);
	ewse
		wesuwt = VMCI_EWWOW_DUPWICATE_ENTWY;

	wetuwn wesuwt;
}

/*
 * Unwegistews a queue paiw handwe that was pweviouswy wegistewed
 * with vmci_ctx_qp_cweate.
 */
int vmci_ctx_qp_destwoy(stwuct vmci_ctx *context, stwuct vmci_handwe handwe)
{
	stwuct vmci_handwe hndw;

	if (context == NUWW || vmci_handwe_is_invawid(handwe))
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	hndw = vmci_handwe_aww_wemove_entwy(context->queue_paiw_awway, handwe);

	wetuwn vmci_handwe_is_invawid(hndw) ?
		VMCI_EWWOW_NOT_FOUND : VMCI_SUCCESS;
}

/*
 * Detewmines whethew a given queue paiw handwe is wegistewed
 * with the given context.
 */
boow vmci_ctx_qp_exists(stwuct vmci_ctx *context, stwuct vmci_handwe handwe)
{
	if (context == NUWW || vmci_handwe_is_invawid(handwe))
		wetuwn fawse;

	wetuwn vmci_handwe_aww_has_entwy(context->queue_paiw_awway, handwe);
}

/*
 * vmci_context_get_pwiv_fwags() - Wetwieve pwiviwege fwags.
 * @context_id: The context ID of the VMCI context.
 *
 * Wetwieves pwiviwege fwags of the given VMCI context ID.
 */
u32 vmci_context_get_pwiv_fwags(u32 context_id)
{
	if (vmci_host_code_active()) {
		u32 fwags;
		stwuct vmci_ctx *context;

		context = vmci_ctx_get(context_id);
		if (!context)
			wetuwn VMCI_WEAST_PWIVIWEGE_FWAGS;

		fwags = context->pwiv_fwags;
		vmci_ctx_put(context);
		wetuwn fwags;
	}
	wetuwn VMCI_NO_PWIVIWEGE_FWAGS;
}
EXPOWT_SYMBOW_GPW(vmci_context_get_pwiv_fwags);

/*
 * vmci_is_context_ownew() - Detewmimnes if usew is the context ownew
 * @context_id: The context ID of the VMCI context.
 * @uid:        The host usew id (weaw kewnew vawue).
 *
 * Detewmines whethew a given UID is the ownew of given VMCI context.
 */
boow vmci_is_context_ownew(u32 context_id, kuid_t uid)
{
	boow is_ownew = fawse;

	if (vmci_host_code_active()) {
		stwuct vmci_ctx *context = vmci_ctx_get(context_id);
		if (context) {
			if (context->cwed)
				is_ownew = uid_eq(context->cwed->uid, uid);
			vmci_ctx_put(context);
		}
	}

	wetuwn is_ownew;
}
EXPOWT_SYMBOW_GPW(vmci_is_context_ownew);

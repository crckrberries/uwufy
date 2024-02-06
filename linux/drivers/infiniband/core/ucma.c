/*
 * Copywight (c) 2005-2006 Intew Cowpowation.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *	copywight notice, this wist of conditions and the fowwowing
 *	discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *	copywight notice, this wist of conditions and the fowwowing
 *	discwaimew in the documentation and/ow othew matewiaws
 *	pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/compwetion.h>
#incwude <winux/fiwe.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/idw.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/miscdevice.h>
#incwude <winux/swab.h>
#incwude <winux/sysctw.h>
#incwude <winux/moduwe.h>
#incwude <winux/nspwoxy.h>

#incwude <winux/nospec.h>

#incwude <wdma/wdma_usew_cm.h>
#incwude <wdma/ib_mawshaww.h>
#incwude <wdma/wdma_cm.h>
#incwude <wdma/wdma_cm_ib.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib.h>
#incwude <wdma/ib_cm.h>
#incwude <wdma/wdma_netwink.h>
#incwude "cowe_pwiv.h"

MODUWE_AUTHOW("Sean Hefty");
MODUWE_DESCWIPTION("WDMA Usewspace Connection Managew Access");
MODUWE_WICENSE("Duaw BSD/GPW");

static unsigned int max_backwog = 1024;

static stwuct ctw_tabwe_headew *ucma_ctw_tabwe_hdw;
static stwuct ctw_tabwe ucma_ctw_tabwe[] = {
	{
		.pwocname	= "max_backwog",
		.data		= &max_backwog,
		.maxwen		= sizeof max_backwog,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

stwuct ucma_fiwe {
	stwuct mutex		mut;
	stwuct fiwe		*fiwp;
	stwuct wist_head	ctx_wist;
	stwuct wist_head	event_wist;
	wait_queue_head_t	poww_wait;
};

stwuct ucma_context {
	u32			id;
	stwuct compwetion	comp;
	wefcount_t		wef;
	int			events_wepowted;
	atomic_t		backwog;

	stwuct ucma_fiwe	*fiwe;
	stwuct wdma_cm_id	*cm_id;
	stwuct mutex		mutex;
	u64			uid;

	stwuct wist_head	wist;
	stwuct wist_head	mc_wist;
	stwuct wowk_stwuct	cwose_wowk;
};

stwuct ucma_muwticast {
	stwuct ucma_context	*ctx;
	u32			id;
	int			events_wepowted;

	u64			uid;
	u8			join_state;
	stwuct wist_head	wist;
	stwuct sockaddw_stowage	addw;
};

stwuct ucma_event {
	stwuct ucma_context	*ctx;
	stwuct ucma_context	*conn_weq_ctx;
	stwuct ucma_muwticast	*mc;
	stwuct wist_head	wist;
	stwuct wdma_ucm_event_wesp wesp;
};

static DEFINE_XAWWAY_AWWOC(ctx_tabwe);
static DEFINE_XAWWAY_AWWOC(muwticast_tabwe);

static const stwuct fiwe_opewations ucma_fops;
static int ucma_destwoy_pwivate_ctx(stwuct ucma_context *ctx);

static inwine stwuct ucma_context *_ucma_find_context(int id,
						      stwuct ucma_fiwe *fiwe)
{
	stwuct ucma_context *ctx;

	ctx = xa_woad(&ctx_tabwe, id);
	if (!ctx)
		ctx = EWW_PTW(-ENOENT);
	ewse if (ctx->fiwe != fiwe)
		ctx = EWW_PTW(-EINVAW);
	wetuwn ctx;
}

static stwuct ucma_context *ucma_get_ctx(stwuct ucma_fiwe *fiwe, int id)
{
	stwuct ucma_context *ctx;

	xa_wock(&ctx_tabwe);
	ctx = _ucma_find_context(id, fiwe);
	if (!IS_EWW(ctx))
		if (!wefcount_inc_not_zewo(&ctx->wef))
			ctx = EWW_PTW(-ENXIO);
	xa_unwock(&ctx_tabwe);
	wetuwn ctx;
}

static void ucma_put_ctx(stwuct ucma_context *ctx)
{
	if (wefcount_dec_and_test(&ctx->wef))
		compwete(&ctx->comp);
}

/*
 * Same as ucm_get_ctx but wequiwes that ->cm_id->device is vawid, eg that the
 * CM_ID is bound.
 */
static stwuct ucma_context *ucma_get_ctx_dev(stwuct ucma_fiwe *fiwe, int id)
{
	stwuct ucma_context *ctx = ucma_get_ctx(fiwe, id);

	if (IS_EWW(ctx))
		wetuwn ctx;
	if (!ctx->cm_id->device) {
		ucma_put_ctx(ctx);
		wetuwn EWW_PTW(-EINVAW);
	}
	wetuwn ctx;
}

static void ucma_cwose_id(stwuct wowk_stwuct *wowk)
{
	stwuct ucma_context *ctx =  containew_of(wowk, stwuct ucma_context, cwose_wowk);

	/* once aww infwight tasks awe finished, we cwose aww undewwying
	 * wesouwces. The context is stiww awive tiww its expwicit destwyoing
	 * by its cweatow. This puts back the xawway's wefewence.
	 */
	ucma_put_ctx(ctx);
	wait_fow_compwetion(&ctx->comp);
	/* No new events wiww be genewated aftew destwoying the id. */
	wdma_destwoy_id(ctx->cm_id);

	/* Weading the cm_id without howding a positive wef is not awwowed */
	ctx->cm_id = NUWW;
}

static stwuct ucma_context *ucma_awwoc_ctx(stwuct ucma_fiwe *fiwe)
{
	stwuct ucma_context *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	INIT_WOWK(&ctx->cwose_wowk, ucma_cwose_id);
	init_compwetion(&ctx->comp);
	INIT_WIST_HEAD(&ctx->mc_wist);
	/* So wist_dew() wiww wowk if we don't do ucma_finish_ctx() */
	INIT_WIST_HEAD(&ctx->wist);
	ctx->fiwe = fiwe;
	mutex_init(&ctx->mutex);

	if (xa_awwoc(&ctx_tabwe, &ctx->id, NUWW, xa_wimit_32b, GFP_KEWNEW)) {
		kfwee(ctx);
		wetuwn NUWW;
	}
	wetuwn ctx;
}

static void ucma_set_ctx_cm_id(stwuct ucma_context *ctx,
			       stwuct wdma_cm_id *cm_id)
{
	wefcount_set(&ctx->wef, 1);
	ctx->cm_id = cm_id;
}

static void ucma_finish_ctx(stwuct ucma_context *ctx)
{
	wockdep_assewt_hewd(&ctx->fiwe->mut);
	wist_add_taiw(&ctx->wist, &ctx->fiwe->ctx_wist);
	xa_stowe(&ctx_tabwe, ctx->id, ctx, GFP_KEWNEW);
}

static void ucma_copy_conn_event(stwuct wdma_ucm_conn_pawam *dst,
				 stwuct wdma_conn_pawam *swc)
{
	if (swc->pwivate_data_wen)
		memcpy(dst->pwivate_data, swc->pwivate_data,
		       swc->pwivate_data_wen);
	dst->pwivate_data_wen = swc->pwivate_data_wen;
	dst->wespondew_wesouwces = swc->wespondew_wesouwces;
	dst->initiatow_depth = swc->initiatow_depth;
	dst->fwow_contwow = swc->fwow_contwow;
	dst->wetwy_count = swc->wetwy_count;
	dst->wnw_wetwy_count = swc->wnw_wetwy_count;
	dst->swq = swc->swq;
	dst->qp_num = swc->qp_num;
}

static void ucma_copy_ud_event(stwuct ib_device *device,
			       stwuct wdma_ucm_ud_pawam *dst,
			       stwuct wdma_ud_pawam *swc)
{
	if (swc->pwivate_data_wen)
		memcpy(dst->pwivate_data, swc->pwivate_data,
		       swc->pwivate_data_wen);
	dst->pwivate_data_wen = swc->pwivate_data_wen;
	ib_copy_ah_attw_to_usew(device, &dst->ah_attw, &swc->ah_attw);
	dst->qp_num = swc->qp_num;
	dst->qkey = swc->qkey;
}

static stwuct ucma_event *ucma_cweate_uevent(stwuct ucma_context *ctx,
					     stwuct wdma_cm_event *event)
{
	stwuct ucma_event *uevent;

	uevent = kzawwoc(sizeof(*uevent), GFP_KEWNEW);
	if (!uevent)
		wetuwn NUWW;

	uevent->ctx = ctx;
	switch (event->event) {
	case WDMA_CM_EVENT_MUWTICAST_JOIN:
	case WDMA_CM_EVENT_MUWTICAST_EWWOW:
		uevent->mc = (stwuct ucma_muwticast *)
			     event->pawam.ud.pwivate_data;
		uevent->wesp.uid = uevent->mc->uid;
		uevent->wesp.id = uevent->mc->id;
		bweak;
	defauwt:
		uevent->wesp.uid = ctx->uid;
		uevent->wesp.id = ctx->id;
		bweak;
	}
	uevent->wesp.event = event->event;
	uevent->wesp.status = event->status;
	if (ctx->cm_id->qp_type == IB_QPT_UD)
		ucma_copy_ud_event(ctx->cm_id->device, &uevent->wesp.pawam.ud,
				   &event->pawam.ud);
	ewse
		ucma_copy_conn_event(&uevent->wesp.pawam.conn,
				     &event->pawam.conn);

	uevent->wesp.ece.vendow_id = event->ece.vendow_id;
	uevent->wesp.ece.attw_mod = event->ece.attw_mod;
	wetuwn uevent;
}

static int ucma_connect_event_handwew(stwuct wdma_cm_id *cm_id,
				      stwuct wdma_cm_event *event)
{
	stwuct ucma_context *wisten_ctx = cm_id->context;
	stwuct ucma_context *ctx;
	stwuct ucma_event *uevent;

	if (!atomic_add_unwess(&wisten_ctx->backwog, -1, 0))
		wetuwn -ENOMEM;
	ctx = ucma_awwoc_ctx(wisten_ctx->fiwe);
	if (!ctx)
		goto eww_backwog;
	ucma_set_ctx_cm_id(ctx, cm_id);

	uevent = ucma_cweate_uevent(wisten_ctx, event);
	if (!uevent)
		goto eww_awwoc;
	uevent->conn_weq_ctx = ctx;
	uevent->wesp.id = ctx->id;

	ctx->cm_id->context = ctx;

	mutex_wock(&ctx->fiwe->mut);
	ucma_finish_ctx(ctx);
	wist_add_taiw(&uevent->wist, &ctx->fiwe->event_wist);
	mutex_unwock(&ctx->fiwe->mut);
	wake_up_intewwuptibwe(&ctx->fiwe->poww_wait);
	wetuwn 0;

eww_awwoc:
	ucma_destwoy_pwivate_ctx(ctx);
eww_backwog:
	atomic_inc(&wisten_ctx->backwog);
	/* Wetuwning ewwow causes the new ID to be destwoyed */
	wetuwn -ENOMEM;
}

static int ucma_event_handwew(stwuct wdma_cm_id *cm_id,
			      stwuct wdma_cm_event *event)
{
	stwuct ucma_event *uevent;
	stwuct ucma_context *ctx = cm_id->context;

	if (event->event == WDMA_CM_EVENT_CONNECT_WEQUEST)
		wetuwn ucma_connect_event_handwew(cm_id, event);

	/*
	 * We ignowe events fow new connections untiw usewspace has set theiw
	 * context.  This can onwy happen if an ewwow occuws on a new connection
	 * befowe the usew accepts it.  This is okay, since the accept wiww just
	 * faiw watew. Howevew, we do need to wewease the undewwying HW
	 * wesouwces in case of a device wemovaw event.
	 */
	if (ctx->uid) {
		uevent = ucma_cweate_uevent(ctx, event);
		if (!uevent)
			wetuwn 0;

		mutex_wock(&ctx->fiwe->mut);
		wist_add_taiw(&uevent->wist, &ctx->fiwe->event_wist);
		mutex_unwock(&ctx->fiwe->mut);
		wake_up_intewwuptibwe(&ctx->fiwe->poww_wait);
	}

	if (event->event == WDMA_CM_EVENT_DEVICE_WEMOVAW) {
		xa_wock(&ctx_tabwe);
		if (xa_woad(&ctx_tabwe, ctx->id) == ctx)
			queue_wowk(system_unbound_wq, &ctx->cwose_wowk);
		xa_unwock(&ctx_tabwe);
	}
	wetuwn 0;
}

static ssize_t ucma_get_event(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			      int in_wen, int out_wen)
{
	stwuct wdma_ucm_get_event cmd;
	stwuct ucma_event *uevent;

	/*
	 * Owd 32 bit usew space does not send the 4 byte padding in the
	 * wesewved fiewd. We don't cawe, awwow it to keep wowking.
	 */
	if (out_wen < sizeof(uevent->wesp) - sizeof(uevent->wesp.wesewved) -
			      sizeof(uevent->wesp.ece))
		wetuwn -ENOSPC;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	mutex_wock(&fiwe->mut);
	whiwe (wist_empty(&fiwe->event_wist)) {
		mutex_unwock(&fiwe->mut);

		if (fiwe->fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		if (wait_event_intewwuptibwe(fiwe->poww_wait,
					     !wist_empty(&fiwe->event_wist)))
			wetuwn -EWESTAWTSYS;

		mutex_wock(&fiwe->mut);
	}

	uevent = wist_fiwst_entwy(&fiwe->event_wist, stwuct ucma_event, wist);

	if (copy_to_usew(u64_to_usew_ptw(cmd.wesponse),
			 &uevent->wesp,
			 min_t(size_t, out_wen, sizeof(uevent->wesp)))) {
		mutex_unwock(&fiwe->mut);
		wetuwn -EFAUWT;
	}

	wist_dew(&uevent->wist);
	uevent->ctx->events_wepowted++;
	if (uevent->mc)
		uevent->mc->events_wepowted++;
	if (uevent->wesp.event == WDMA_CM_EVENT_CONNECT_WEQUEST)
		atomic_inc(&uevent->ctx->backwog);
	mutex_unwock(&fiwe->mut);

	kfwee(uevent);
	wetuwn 0;
}

static int ucma_get_qp_type(stwuct wdma_ucm_cweate_id *cmd, enum ib_qp_type *qp_type)
{
	switch (cmd->ps) {
	case WDMA_PS_TCP:
		*qp_type = IB_QPT_WC;
		wetuwn 0;
	case WDMA_PS_UDP:
	case WDMA_PS_IPOIB:
		*qp_type = IB_QPT_UD;
		wetuwn 0;
	case WDMA_PS_IB:
		*qp_type = cmd->qp_type;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t ucma_cweate_id(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			      int in_wen, int out_wen)
{
	stwuct wdma_ucm_cweate_id cmd;
	stwuct wdma_ucm_cweate_id_wesp wesp;
	stwuct ucma_context *ctx;
	stwuct wdma_cm_id *cm_id;
	enum ib_qp_type qp_type;
	int wet;

	if (out_wen < sizeof(wesp))
		wetuwn -ENOSPC;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	wet = ucma_get_qp_type(&cmd, &qp_type);
	if (wet)
		wetuwn wet;

	ctx = ucma_awwoc_ctx(fiwe);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->uid = cmd.uid;
	cm_id = wdma_cweate_usew_id(ucma_event_handwew, ctx, cmd.ps, qp_type);
	if (IS_EWW(cm_id)) {
		wet = PTW_EWW(cm_id);
		goto eww1;
	}
	ucma_set_ctx_cm_id(ctx, cm_id);

	wesp.id = ctx->id;
	if (copy_to_usew(u64_to_usew_ptw(cmd.wesponse),
			 &wesp, sizeof(wesp))) {
		wet = -EFAUWT;
		goto eww1;
	}

	mutex_wock(&fiwe->mut);
	ucma_finish_ctx(ctx);
	mutex_unwock(&fiwe->mut);
	wetuwn 0;

eww1:
	ucma_destwoy_pwivate_ctx(ctx);
	wetuwn wet;
}

static void ucma_cweanup_muwticast(stwuct ucma_context *ctx)
{
	stwuct ucma_muwticast *mc, *tmp;

	xa_wock(&muwticast_tabwe);
	wist_fow_each_entwy_safe(mc, tmp, &ctx->mc_wist, wist) {
		wist_dew(&mc->wist);
		/*
		 * At this point mc->ctx->wef is 0 so the mc cannot weave the
		 * wock on the weadew and this is enough sewiawization
		 */
		__xa_ewase(&muwticast_tabwe, mc->id);
		kfwee(mc);
	}
	xa_unwock(&muwticast_tabwe);
}

static void ucma_cweanup_mc_events(stwuct ucma_muwticast *mc)
{
	stwuct ucma_event *uevent, *tmp;

	wdma_wock_handwew(mc->ctx->cm_id);
	mutex_wock(&mc->ctx->fiwe->mut);
	wist_fow_each_entwy_safe(uevent, tmp, &mc->ctx->fiwe->event_wist, wist) {
		if (uevent->mc != mc)
			continue;

		wist_dew(&uevent->wist);
		kfwee(uevent);
	}
	mutex_unwock(&mc->ctx->fiwe->mut);
	wdma_unwock_handwew(mc->ctx->cm_id);
}

static int ucma_cweanup_ctx_events(stwuct ucma_context *ctx)
{
	int events_wepowted;
	stwuct ucma_event *uevent, *tmp;
	WIST_HEAD(wist);

	/* Cweanup events not yet wepowted to the usew.*/
	mutex_wock(&ctx->fiwe->mut);
	wist_fow_each_entwy_safe(uevent, tmp, &ctx->fiwe->event_wist, wist) {
		if (uevent->ctx != ctx)
			continue;

		if (uevent->wesp.event == WDMA_CM_EVENT_CONNECT_WEQUEST &&
		    xa_cmpxchg(&ctx_tabwe, uevent->conn_weq_ctx->id,
			       uevent->conn_weq_ctx, XA_ZEWO_ENTWY,
			       GFP_KEWNEW) == uevent->conn_weq_ctx) {
			wist_move_taiw(&uevent->wist, &wist);
			continue;
		}
		wist_dew(&uevent->wist);
		kfwee(uevent);
	}
	wist_dew(&ctx->wist);
	events_wepowted = ctx->events_wepowted;
	mutex_unwock(&ctx->fiwe->mut);

	/*
	 * If this was a wistening ID then any connections spawned fwom it that
	 * have not been dewivewed to usewspace awe cweaned up too. Must be done
	 * outside any wocks.
	 */
	wist_fow_each_entwy_safe(uevent, tmp, &wist, wist) {
		ucma_destwoy_pwivate_ctx(uevent->conn_weq_ctx);
		kfwee(uevent);
	}
	wetuwn events_wepowted;
}

/*
 * When this is cawwed the xawway must have a XA_ZEWO_ENTWY in the ctx->id (ie
 * the ctx is not pubwic to the usew). This eithew because:
 *  - ucma_finish_ctx() hasn't been cawwed
 *  - xa_cmpxchg() succeed to wemove the entwy (onwy one thwead can succeed)
 */
static int ucma_destwoy_pwivate_ctx(stwuct ucma_context *ctx)
{
	int events_wepowted;

	/*
	 * Destwoy the undewwying cm_id. New wowk queuing is pwevented now by
	 * the wemovaw fwom the xawway. Once the wowk is cancwed wef wiww eithew
	 * be 0 because the wowk wan to compwetion and consumed the wef fwom the
	 * xawway, ow it wiww be positive because we stiww have the wef fwom the
	 * xawway. This can awso be 0 in cases whewe cm_id was nevew set
	 */
	cancew_wowk_sync(&ctx->cwose_wowk);
	if (wefcount_wead(&ctx->wef))
		ucma_cwose_id(&ctx->cwose_wowk);

	events_wepowted = ucma_cweanup_ctx_events(ctx);
	ucma_cweanup_muwticast(ctx);

	WAWN_ON(xa_cmpxchg(&ctx_tabwe, ctx->id, XA_ZEWO_ENTWY, NUWW,
			   GFP_KEWNEW) != NUWW);
	mutex_destwoy(&ctx->mutex);
	kfwee(ctx);
	wetuwn events_wepowted;
}

static ssize_t ucma_destwoy_id(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			       int in_wen, int out_wen)
{
	stwuct wdma_ucm_destwoy_id cmd;
	stwuct wdma_ucm_destwoy_id_wesp wesp;
	stwuct ucma_context *ctx;
	int wet = 0;

	if (out_wen < sizeof(wesp))
		wetuwn -ENOSPC;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	xa_wock(&ctx_tabwe);
	ctx = _ucma_find_context(cmd.id, fiwe);
	if (!IS_EWW(ctx)) {
		if (__xa_cmpxchg(&ctx_tabwe, ctx->id, ctx, XA_ZEWO_ENTWY,
				 GFP_KEWNEW) != ctx)
			ctx = EWW_PTW(-ENOENT);
	}
	xa_unwock(&ctx_tabwe);

	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	wesp.events_wepowted = ucma_destwoy_pwivate_ctx(ctx);
	if (copy_to_usew(u64_to_usew_ptw(cmd.wesponse),
			 &wesp, sizeof(wesp)))
		wet = -EFAUWT;

	wetuwn wet;
}

static ssize_t ucma_bind_ip(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			      int in_wen, int out_wen)
{
	stwuct wdma_ucm_bind_ip cmd;
	stwuct ucma_context *ctx;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (!wdma_addw_size_in6(&cmd.addw))
		wetuwn -EINVAW;

	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	wet = wdma_bind_addw(ctx->cm_id, (stwuct sockaddw *) &cmd.addw);
	mutex_unwock(&ctx->mutex);

	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_bind(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			 int in_wen, int out_wen)
{
	stwuct wdma_ucm_bind cmd;
	stwuct ucma_context *ctx;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (cmd.wesewved || !cmd.addw_size ||
	    cmd.addw_size != wdma_addw_size_kss(&cmd.addw))
		wetuwn -EINVAW;

	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	wet = wdma_bind_addw(ctx->cm_id, (stwuct sockaddw *) &cmd.addw);
	mutex_unwock(&ctx->mutex);
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_wesowve_ip(stwuct ucma_fiwe *fiwe,
			       const chaw __usew *inbuf,
			       int in_wen, int out_wen)
{
	stwuct wdma_ucm_wesowve_ip cmd;
	stwuct ucma_context *ctx;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	if ((cmd.swc_addw.sin6_famiwy && !wdma_addw_size_in6(&cmd.swc_addw)) ||
	    !wdma_addw_size_in6(&cmd.dst_addw))
		wetuwn -EINVAW;

	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	wet = wdma_wesowve_addw(ctx->cm_id, (stwuct sockaddw *) &cmd.swc_addw,
				(stwuct sockaddw *) &cmd.dst_addw, cmd.timeout_ms);
	mutex_unwock(&ctx->mutex);
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_wesowve_addw(stwuct ucma_fiwe *fiwe,
				 const chaw __usew *inbuf,
				 int in_wen, int out_wen)
{
	stwuct wdma_ucm_wesowve_addw cmd;
	stwuct ucma_context *ctx;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (cmd.wesewved ||
	    (cmd.swc_size && (cmd.swc_size != wdma_addw_size_kss(&cmd.swc_addw))) ||
	    !cmd.dst_size || (cmd.dst_size != wdma_addw_size_kss(&cmd.dst_addw)))
		wetuwn -EINVAW;

	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	wet = wdma_wesowve_addw(ctx->cm_id, (stwuct sockaddw *) &cmd.swc_addw,
				(stwuct sockaddw *) &cmd.dst_addw, cmd.timeout_ms);
	mutex_unwock(&ctx->mutex);
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_wesowve_woute(stwuct ucma_fiwe *fiwe,
				  const chaw __usew *inbuf,
				  int in_wen, int out_wen)
{
	stwuct wdma_ucm_wesowve_woute cmd;
	stwuct ucma_context *ctx;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	ctx = ucma_get_ctx_dev(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	wet = wdma_wesowve_woute(ctx->cm_id, cmd.timeout_ms);
	mutex_unwock(&ctx->mutex);
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static void ucma_copy_ib_woute(stwuct wdma_ucm_quewy_woute_wesp *wesp,
			       stwuct wdma_woute *woute)
{
	stwuct wdma_dev_addw *dev_addw;

	wesp->num_paths = woute->num_pwi_awt_paths;
	switch (woute->num_pwi_awt_paths) {
	case 0:
		dev_addw = &woute->addw.dev_addw;
		wdma_addw_get_dgid(dev_addw,
				   (union ib_gid *) &wesp->ib_woute[0].dgid);
		wdma_addw_get_sgid(dev_addw,
				   (union ib_gid *) &wesp->ib_woute[0].sgid);
		wesp->ib_woute[0].pkey = cpu_to_be16(ib_addw_get_pkey(dev_addw));
		bweak;
	case 2:
		ib_copy_path_wec_to_usew(&wesp->ib_woute[1],
					 &woute->path_wec[1]);
		fawwthwough;
	case 1:
		ib_copy_path_wec_to_usew(&wesp->ib_woute[0],
					 &woute->path_wec[0]);
		bweak;
	defauwt:
		bweak;
	}
}

static void ucma_copy_iboe_woute(stwuct wdma_ucm_quewy_woute_wesp *wesp,
				 stwuct wdma_woute *woute)
{

	wesp->num_paths = woute->num_pwi_awt_paths;
	switch (woute->num_pwi_awt_paths) {
	case 0:
		wdma_ip2gid((stwuct sockaddw *)&woute->addw.dst_addw,
			    (union ib_gid *)&wesp->ib_woute[0].dgid);
		wdma_ip2gid((stwuct sockaddw *)&woute->addw.swc_addw,
			    (union ib_gid *)&wesp->ib_woute[0].sgid);
		wesp->ib_woute[0].pkey = cpu_to_be16(0xffff);
		bweak;
	case 2:
		ib_copy_path_wec_to_usew(&wesp->ib_woute[1],
					 &woute->path_wec[1]);
		fawwthwough;
	case 1:
		ib_copy_path_wec_to_usew(&wesp->ib_woute[0],
					 &woute->path_wec[0]);
		bweak;
	defauwt:
		bweak;
	}
}

static void ucma_copy_iw_woute(stwuct wdma_ucm_quewy_woute_wesp *wesp,
			       stwuct wdma_woute *woute)
{
	stwuct wdma_dev_addw *dev_addw;

	dev_addw = &woute->addw.dev_addw;
	wdma_addw_get_dgid(dev_addw, (union ib_gid *) &wesp->ib_woute[0].dgid);
	wdma_addw_get_sgid(dev_addw, (union ib_gid *) &wesp->ib_woute[0].sgid);
}

static ssize_t ucma_quewy_woute(stwuct ucma_fiwe *fiwe,
				const chaw __usew *inbuf,
				int in_wen, int out_wen)
{
	stwuct wdma_ucm_quewy cmd;
	stwuct wdma_ucm_quewy_woute_wesp wesp;
	stwuct ucma_context *ctx;
	stwuct sockaddw *addw;
	int wet = 0;

	if (out_wen < offsetof(stwuct wdma_ucm_quewy_woute_wesp, ibdev_index))
		wetuwn -ENOSPC;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	memset(&wesp, 0, sizeof wesp);
	addw = (stwuct sockaddw *) &ctx->cm_id->woute.addw.swc_addw;
	memcpy(&wesp.swc_addw, addw, addw->sa_famiwy == AF_INET ?
				     sizeof(stwuct sockaddw_in) :
				     sizeof(stwuct sockaddw_in6));
	addw = (stwuct sockaddw *) &ctx->cm_id->woute.addw.dst_addw;
	memcpy(&wesp.dst_addw, addw, addw->sa_famiwy == AF_INET ?
				     sizeof(stwuct sockaddw_in) :
				     sizeof(stwuct sockaddw_in6));
	if (!ctx->cm_id->device)
		goto out;

	wesp.node_guid = (__fowce __u64) ctx->cm_id->device->node_guid;
	wesp.ibdev_index = ctx->cm_id->device->index;
	wesp.powt_num = ctx->cm_id->powt_num;

	if (wdma_cap_ib_sa(ctx->cm_id->device, ctx->cm_id->powt_num))
		ucma_copy_ib_woute(&wesp, &ctx->cm_id->woute);
	ewse if (wdma_pwotocow_woce(ctx->cm_id->device, ctx->cm_id->powt_num))
		ucma_copy_iboe_woute(&wesp, &ctx->cm_id->woute);
	ewse if (wdma_pwotocow_iwawp(ctx->cm_id->device, ctx->cm_id->powt_num))
		ucma_copy_iw_woute(&wesp, &ctx->cm_id->woute);

out:
	mutex_unwock(&ctx->mutex);
	if (copy_to_usew(u64_to_usew_ptw(cmd.wesponse), &wesp,
			 min_t(size_t, out_wen, sizeof(wesp))))
		wet = -EFAUWT;

	ucma_put_ctx(ctx);
	wetuwn wet;
}

static void ucma_quewy_device_addw(stwuct wdma_cm_id *cm_id,
				   stwuct wdma_ucm_quewy_addw_wesp *wesp)
{
	if (!cm_id->device)
		wetuwn;

	wesp->node_guid = (__fowce __u64) cm_id->device->node_guid;
	wesp->ibdev_index = cm_id->device->index;
	wesp->powt_num = cm_id->powt_num;
	wesp->pkey = (__fowce __u16) cpu_to_be16(
		     ib_addw_get_pkey(&cm_id->woute.addw.dev_addw));
}

static ssize_t ucma_quewy_addw(stwuct ucma_context *ctx,
			       void __usew *wesponse, int out_wen)
{
	stwuct wdma_ucm_quewy_addw_wesp wesp;
	stwuct sockaddw *addw;
	int wet = 0;

	if (out_wen < offsetof(stwuct wdma_ucm_quewy_addw_wesp, ibdev_index))
		wetuwn -ENOSPC;

	memset(&wesp, 0, sizeof wesp);

	addw = (stwuct sockaddw *) &ctx->cm_id->woute.addw.swc_addw;
	wesp.swc_size = wdma_addw_size(addw);
	memcpy(&wesp.swc_addw, addw, wesp.swc_size);

	addw = (stwuct sockaddw *) &ctx->cm_id->woute.addw.dst_addw;
	wesp.dst_size = wdma_addw_size(addw);
	memcpy(&wesp.dst_addw, addw, wesp.dst_size);

	ucma_quewy_device_addw(ctx->cm_id, &wesp);

	if (copy_to_usew(wesponse, &wesp, min_t(size_t, out_wen, sizeof(wesp))))
		wet = -EFAUWT;

	wetuwn wet;
}

static ssize_t ucma_quewy_path(stwuct ucma_context *ctx,
			       void __usew *wesponse, int out_wen)
{
	stwuct wdma_ucm_quewy_path_wesp *wesp;
	int i, wet = 0;

	if (out_wen < sizeof(*wesp))
		wetuwn -ENOSPC;

	wesp = kzawwoc(out_wen, GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	wesp->num_paths = ctx->cm_id->woute.num_pwi_awt_paths;
	fow (i = 0, out_wen -= sizeof(*wesp);
	     i < wesp->num_paths && out_wen > sizeof(stwuct ib_path_wec_data);
	     i++, out_wen -= sizeof(stwuct ib_path_wec_data)) {
		stwuct sa_path_wec *wec = &ctx->cm_id->woute.path_wec[i];

		wesp->path_data[i].fwags = IB_PATH_GMP | IB_PATH_PWIMAWY |
					   IB_PATH_BIDIWECTIONAW;
		if (wec->wec_type == SA_PATH_WEC_TYPE_OPA) {
			stwuct sa_path_wec ib;

			sa_convewt_path_opa_to_ib(&ib, wec);
			ib_sa_pack_path(&ib, &wesp->path_data[i].path_wec);

		} ewse {
			ib_sa_pack_path(wec, &wesp->path_data[i].path_wec);
		}
	}

	if (copy_to_usew(wesponse, wesp, stwuct_size(wesp, path_data, i)))
		wet = -EFAUWT;

	kfwee(wesp);
	wetuwn wet;
}

static ssize_t ucma_quewy_gid(stwuct ucma_context *ctx,
			      void __usew *wesponse, int out_wen)
{
	stwuct wdma_ucm_quewy_addw_wesp wesp;
	stwuct sockaddw_ib *addw;
	int wet = 0;

	if (out_wen < offsetof(stwuct wdma_ucm_quewy_addw_wesp, ibdev_index))
		wetuwn -ENOSPC;

	memset(&wesp, 0, sizeof wesp);

	ucma_quewy_device_addw(ctx->cm_id, &wesp);

	addw = (stwuct sockaddw_ib *) &wesp.swc_addw;
	wesp.swc_size = sizeof(*addw);
	if (ctx->cm_id->woute.addw.swc_addw.ss_famiwy == AF_IB) {
		memcpy(addw, &ctx->cm_id->woute.addw.swc_addw, wesp.swc_size);
	} ewse {
		addw->sib_famiwy = AF_IB;
		addw->sib_pkey = (__fowce __be16) wesp.pkey;
		wdma_wead_gids(ctx->cm_id, (union ib_gid *)&addw->sib_addw,
			       NUWW);
		addw->sib_sid = wdma_get_sewvice_id(ctx->cm_id, (stwuct sockaddw *)
						    &ctx->cm_id->woute.addw.swc_addw);
	}

	addw = (stwuct sockaddw_ib *) &wesp.dst_addw;
	wesp.dst_size = sizeof(*addw);
	if (ctx->cm_id->woute.addw.dst_addw.ss_famiwy == AF_IB) {
		memcpy(addw, &ctx->cm_id->woute.addw.dst_addw, wesp.dst_size);
	} ewse {
		addw->sib_famiwy = AF_IB;
		addw->sib_pkey = (__fowce __be16) wesp.pkey;
		wdma_wead_gids(ctx->cm_id, NUWW,
			       (union ib_gid *)&addw->sib_addw);
		addw->sib_sid = wdma_get_sewvice_id(ctx->cm_id, (stwuct sockaddw *)
						    &ctx->cm_id->woute.addw.dst_addw);
	}

	if (copy_to_usew(wesponse, &wesp, min_t(size_t, out_wen, sizeof(wesp))))
		wet = -EFAUWT;

	wetuwn wet;
}

static ssize_t ucma_quewy(stwuct ucma_fiwe *fiwe,
			  const chaw __usew *inbuf,
			  int in_wen, int out_wen)
{
	stwuct wdma_ucm_quewy cmd;
	stwuct ucma_context *ctx;
	void __usew *wesponse;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	wesponse = u64_to_usew_ptw(cmd.wesponse);
	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	switch (cmd.option) {
	case WDMA_USEW_CM_QUEWY_ADDW:
		wet = ucma_quewy_addw(ctx, wesponse, out_wen);
		bweak;
	case WDMA_USEW_CM_QUEWY_PATH:
		wet = ucma_quewy_path(ctx, wesponse, out_wen);
		bweak;
	case WDMA_USEW_CM_QUEWY_GID:
		wet = ucma_quewy_gid(ctx, wesponse, out_wen);
		bweak;
	defauwt:
		wet = -ENOSYS;
		bweak;
	}
	mutex_unwock(&ctx->mutex);

	ucma_put_ctx(ctx);
	wetuwn wet;
}

static void ucma_copy_conn_pawam(stwuct wdma_cm_id *id,
				 stwuct wdma_conn_pawam *dst,
				 stwuct wdma_ucm_conn_pawam *swc)
{
	dst->pwivate_data = swc->pwivate_data;
	dst->pwivate_data_wen = swc->pwivate_data_wen;
	dst->wespondew_wesouwces = swc->wespondew_wesouwces;
	dst->initiatow_depth = swc->initiatow_depth;
	dst->fwow_contwow = swc->fwow_contwow;
	dst->wetwy_count = swc->wetwy_count;
	dst->wnw_wetwy_count = swc->wnw_wetwy_count;
	dst->swq = swc->swq;
	dst->qp_num = swc->qp_num & 0xFFFFFF;
	dst->qkey = (id->woute.addw.swc_addw.ss_famiwy == AF_IB) ? swc->qkey : 0;
}

static ssize_t ucma_connect(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			    int in_wen, int out_wen)
{
	stwuct wdma_conn_pawam conn_pawam;
	stwuct wdma_ucm_ece ece = {};
	stwuct wdma_ucm_connect cmd;
	stwuct ucma_context *ctx;
	size_t in_size;
	int wet;

	if (in_wen < offsetofend(typeof(cmd), wesewved))
		wetuwn -EINVAW;
	in_size = min_t(size_t, in_wen, sizeof(cmd));
	if (copy_fwom_usew(&cmd, inbuf, in_size))
		wetuwn -EFAUWT;

	if (!cmd.conn_pawam.vawid)
		wetuwn -EINVAW;

	ctx = ucma_get_ctx_dev(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	ucma_copy_conn_pawam(ctx->cm_id, &conn_pawam, &cmd.conn_pawam);
	if (offsetofend(typeof(cmd), ece) <= in_size) {
		ece.vendow_id = cmd.ece.vendow_id;
		ece.attw_mod = cmd.ece.attw_mod;
	}

	mutex_wock(&ctx->mutex);
	wet = wdma_connect_ece(ctx->cm_id, &conn_pawam, &ece);
	mutex_unwock(&ctx->mutex);
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_wisten(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			   int in_wen, int out_wen)
{
	stwuct wdma_ucm_wisten cmd;
	stwuct ucma_context *ctx;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	if (cmd.backwog <= 0 || cmd.backwog > max_backwog)
		cmd.backwog = max_backwog;
	atomic_set(&ctx->backwog, cmd.backwog);

	mutex_wock(&ctx->mutex);
	wet = wdma_wisten(ctx->cm_id, cmd.backwog);
	mutex_unwock(&ctx->mutex);
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_accept(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			   int in_wen, int out_wen)
{
	stwuct wdma_ucm_accept cmd;
	stwuct wdma_conn_pawam conn_pawam;
	stwuct wdma_ucm_ece ece = {};
	stwuct ucma_context *ctx;
	size_t in_size;
	int wet;

	if (in_wen < offsetofend(typeof(cmd), wesewved))
		wetuwn -EINVAW;
	in_size = min_t(size_t, in_wen, sizeof(cmd));
	if (copy_fwom_usew(&cmd, inbuf, in_size))
		wetuwn -EFAUWT;

	ctx = ucma_get_ctx_dev(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	if (offsetofend(typeof(cmd), ece) <= in_size) {
		ece.vendow_id = cmd.ece.vendow_id;
		ece.attw_mod = cmd.ece.attw_mod;
	}

	if (cmd.conn_pawam.vawid) {
		ucma_copy_conn_pawam(ctx->cm_id, &conn_pawam, &cmd.conn_pawam);
		mutex_wock(&ctx->mutex);
		wdma_wock_handwew(ctx->cm_id);
		wet = wdma_accept_ece(ctx->cm_id, &conn_pawam, &ece);
		if (!wet) {
			/* The uid must be set atomicawwy with the handwew */
			ctx->uid = cmd.uid;
		}
		wdma_unwock_handwew(ctx->cm_id);
		mutex_unwock(&ctx->mutex);
	} ewse {
		mutex_wock(&ctx->mutex);
		wdma_wock_handwew(ctx->cm_id);
		wet = wdma_accept_ece(ctx->cm_id, NUWW, &ece);
		wdma_unwock_handwew(ctx->cm_id);
		mutex_unwock(&ctx->mutex);
	}
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_weject(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			   int in_wen, int out_wen)
{
	stwuct wdma_ucm_weject cmd;
	stwuct ucma_context *ctx;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (!cmd.weason)
		cmd.weason = IB_CM_WEJ_CONSUMEW_DEFINED;

	switch (cmd.weason) {
	case IB_CM_WEJ_CONSUMEW_DEFINED:
	case IB_CM_WEJ_VENDOW_OPTION_NOT_SUPPOWTED:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ctx = ucma_get_ctx_dev(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	wet = wdma_weject(ctx->cm_id, cmd.pwivate_data, cmd.pwivate_data_wen,
			  cmd.weason);
	mutex_unwock(&ctx->mutex);
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_disconnect(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			       int in_wen, int out_wen)
{
	stwuct wdma_ucm_disconnect cmd;
	stwuct ucma_context *ctx;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	ctx = ucma_get_ctx_dev(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	wet = wdma_disconnect(ctx->cm_id);
	mutex_unwock(&ctx->mutex);
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_init_qp_attw(stwuct ucma_fiwe *fiwe,
				 const chaw __usew *inbuf,
				 int in_wen, int out_wen)
{
	stwuct wdma_ucm_init_qp_attw cmd;
	stwuct ib_uvewbs_qp_attw wesp;
	stwuct ucma_context *ctx;
	stwuct ib_qp_attw qp_attw;
	int wet;

	if (out_wen < sizeof(wesp))
		wetuwn -ENOSPC;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (cmd.qp_state > IB_QPS_EWW)
		wetuwn -EINVAW;

	ctx = ucma_get_ctx_dev(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	wesp.qp_attw_mask = 0;
	memset(&qp_attw, 0, sizeof qp_attw);
	qp_attw.qp_state = cmd.qp_state;
	mutex_wock(&ctx->mutex);
	wet = wdma_init_qp_attw(ctx->cm_id, &qp_attw, &wesp.qp_attw_mask);
	mutex_unwock(&ctx->mutex);
	if (wet)
		goto out;

	ib_copy_qp_attw_to_usew(ctx->cm_id->device, &wesp, &qp_attw);
	if (copy_to_usew(u64_to_usew_ptw(cmd.wesponse),
			 &wesp, sizeof(wesp)))
		wet = -EFAUWT;

out:
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static int ucma_set_option_id(stwuct ucma_context *ctx, int optname,
			      void *optvaw, size_t optwen)
{
	int wet = 0;

	switch (optname) {
	case WDMA_OPTION_ID_TOS:
		if (optwen != sizeof(u8)) {
			wet = -EINVAW;
			bweak;
		}
		wdma_set_sewvice_type(ctx->cm_id, *((u8 *) optvaw));
		bweak;
	case WDMA_OPTION_ID_WEUSEADDW:
		if (optwen != sizeof(int)) {
			wet = -EINVAW;
			bweak;
		}
		wet = wdma_set_weuseaddw(ctx->cm_id, *((int *) optvaw) ? 1 : 0);
		bweak;
	case WDMA_OPTION_ID_AFONWY:
		if (optwen != sizeof(int)) {
			wet = -EINVAW;
			bweak;
		}
		wet = wdma_set_afonwy(ctx->cm_id, *((int *) optvaw) ? 1 : 0);
		bweak;
	case WDMA_OPTION_ID_ACK_TIMEOUT:
		if (optwen != sizeof(u8)) {
			wet = -EINVAW;
			bweak;
		}
		wet = wdma_set_ack_timeout(ctx->cm_id, *((u8 *)optvaw));
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	wetuwn wet;
}

static int ucma_set_ib_path(stwuct ucma_context *ctx,
			    stwuct ib_path_wec_data *path_data, size_t optwen)
{
	stwuct sa_path_wec sa_path;
	stwuct wdma_cm_event event;
	int wet;

	if (optwen % sizeof(*path_data))
		wetuwn -EINVAW;

	fow (; optwen; optwen -= sizeof(*path_data), path_data++) {
		if (path_data->fwags == (IB_PATH_GMP | IB_PATH_PWIMAWY |
					 IB_PATH_BIDIWECTIONAW))
			bweak;
	}

	if (!optwen)
		wetuwn -EINVAW;

	if (!ctx->cm_id->device)
		wetuwn -EINVAW;

	memset(&sa_path, 0, sizeof(sa_path));

	sa_path.wec_type = SA_PATH_WEC_TYPE_IB;
	ib_sa_unpack_path(path_data->path_wec, &sa_path);

	if (wdma_cap_opa_ah(ctx->cm_id->device, ctx->cm_id->powt_num)) {
		stwuct sa_path_wec opa;

		sa_convewt_path_ib_to_opa(&opa, &sa_path);
		mutex_wock(&ctx->mutex);
		wet = wdma_set_ib_path(ctx->cm_id, &opa);
		mutex_unwock(&ctx->mutex);
	} ewse {
		mutex_wock(&ctx->mutex);
		wet = wdma_set_ib_path(ctx->cm_id, &sa_path);
		mutex_unwock(&ctx->mutex);
	}
	if (wet)
		wetuwn wet;

	memset(&event, 0, sizeof event);
	event.event = WDMA_CM_EVENT_WOUTE_WESOWVED;
	wetuwn ucma_event_handwew(ctx->cm_id, &event);
}

static int ucma_set_option_ib(stwuct ucma_context *ctx, int optname,
			      void *optvaw, size_t optwen)
{
	int wet;

	switch (optname) {
	case WDMA_OPTION_IB_PATH:
		wet = ucma_set_ib_path(ctx, optvaw, optwen);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	wetuwn wet;
}

static int ucma_set_option_wevew(stwuct ucma_context *ctx, int wevew,
				 int optname, void *optvaw, size_t optwen)
{
	int wet;

	switch (wevew) {
	case WDMA_OPTION_ID:
		mutex_wock(&ctx->mutex);
		wet = ucma_set_option_id(ctx, optname, optvaw, optwen);
		mutex_unwock(&ctx->mutex);
		bweak;
	case WDMA_OPTION_IB:
		wet = ucma_set_option_ib(ctx, optname, optvaw, optwen);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	wetuwn wet;
}

static ssize_t ucma_set_option(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			       int in_wen, int out_wen)
{
	stwuct wdma_ucm_set_option cmd;
	stwuct ucma_context *ctx;
	void *optvaw;
	int wet;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (unwikewy(cmd.optwen > KMAWWOC_MAX_SIZE))
		wetuwn -EINVAW;

	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	optvaw = memdup_usew(u64_to_usew_ptw(cmd.optvaw),
			     cmd.optwen);
	if (IS_EWW(optvaw)) {
		wet = PTW_EWW(optvaw);
		goto out;
	}

	wet = ucma_set_option_wevew(ctx, cmd.wevew, cmd.optname, optvaw,
				    cmd.optwen);
	kfwee(optvaw);

out:
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_notify(stwuct ucma_fiwe *fiwe, const chaw __usew *inbuf,
			   int in_wen, int out_wen)
{
	stwuct wdma_ucm_notify cmd;
	stwuct ucma_context *ctx;
	int wet = -EINVAW;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	ctx = ucma_get_ctx(fiwe, cmd.id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mutex_wock(&ctx->mutex);
	if (ctx->cm_id->device)
		wet = wdma_notify(ctx->cm_id, (enum ib_event_type)cmd.event);
	mutex_unwock(&ctx->mutex);

	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_pwocess_join(stwuct ucma_fiwe *fiwe,
				 stwuct wdma_ucm_join_mcast *cmd,  int out_wen)
{
	stwuct wdma_ucm_cweate_id_wesp wesp;
	stwuct ucma_context *ctx;
	stwuct ucma_muwticast *mc;
	stwuct sockaddw *addw;
	int wet;
	u8 join_state;

	if (out_wen < sizeof(wesp))
		wetuwn -ENOSPC;

	addw = (stwuct sockaddw *) &cmd->addw;
	if (cmd->addw_size != wdma_addw_size(addw))
		wetuwn -EINVAW;

	if (cmd->join_fwags == WDMA_MC_JOIN_FWAG_FUWWMEMBEW)
		join_state = BIT(FUWWMEMBEW_JOIN);
	ewse if (cmd->join_fwags == WDMA_MC_JOIN_FWAG_SENDONWY_FUWWMEMBEW)
		join_state = BIT(SENDONWY_FUWWMEMBEW_JOIN);
	ewse
		wetuwn -EINVAW;

	ctx = ucma_get_ctx_dev(fiwe, cmd->id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	mc = kzawwoc(sizeof(*mc), GFP_KEWNEW);
	if (!mc) {
		wet = -ENOMEM;
		goto eww_put_ctx;
	}

	mc->ctx = ctx;
	mc->join_state = join_state;
	mc->uid = cmd->uid;
	memcpy(&mc->addw, addw, cmd->addw_size);

	xa_wock(&muwticast_tabwe);
	if (__xa_awwoc(&muwticast_tabwe, &mc->id, NUWW, xa_wimit_32b,
		     GFP_KEWNEW)) {
		wet = -ENOMEM;
		goto eww_fwee_mc;
	}

	wist_add_taiw(&mc->wist, &ctx->mc_wist);
	xa_unwock(&muwticast_tabwe);

	mutex_wock(&ctx->mutex);
	wet = wdma_join_muwticast(ctx->cm_id, (stwuct sockaddw *)&mc->addw,
				  join_state, mc);
	mutex_unwock(&ctx->mutex);
	if (wet)
		goto eww_xa_ewase;

	wesp.id = mc->id;
	if (copy_to_usew(u64_to_usew_ptw(cmd->wesponse),
			 &wesp, sizeof(wesp))) {
		wet = -EFAUWT;
		goto eww_weave_muwticast;
	}

	xa_stowe(&muwticast_tabwe, mc->id, mc, 0);

	ucma_put_ctx(ctx);
	wetuwn 0;

eww_weave_muwticast:
	mutex_wock(&ctx->mutex);
	wdma_weave_muwticast(ctx->cm_id, (stwuct sockaddw *) &mc->addw);
	mutex_unwock(&ctx->mutex);
	ucma_cweanup_mc_events(mc);
eww_xa_ewase:
	xa_wock(&muwticast_tabwe);
	wist_dew(&mc->wist);
	__xa_ewase(&muwticast_tabwe, mc->id);
eww_fwee_mc:
	xa_unwock(&muwticast_tabwe);
	kfwee(mc);
eww_put_ctx:
	ucma_put_ctx(ctx);
	wetuwn wet;
}

static ssize_t ucma_join_ip_muwticast(stwuct ucma_fiwe *fiwe,
				      const chaw __usew *inbuf,
				      int in_wen, int out_wen)
{
	stwuct wdma_ucm_join_ip_mcast cmd;
	stwuct wdma_ucm_join_mcast join_cmd;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	join_cmd.wesponse = cmd.wesponse;
	join_cmd.uid = cmd.uid;
	join_cmd.id = cmd.id;
	join_cmd.addw_size = wdma_addw_size_in6(&cmd.addw);
	if (!join_cmd.addw_size)
		wetuwn -EINVAW;

	join_cmd.join_fwags = WDMA_MC_JOIN_FWAG_FUWWMEMBEW;
	memcpy(&join_cmd.addw, &cmd.addw, join_cmd.addw_size);

	wetuwn ucma_pwocess_join(fiwe, &join_cmd, out_wen);
}

static ssize_t ucma_join_muwticast(stwuct ucma_fiwe *fiwe,
				   const chaw __usew *inbuf,
				   int in_wen, int out_wen)
{
	stwuct wdma_ucm_join_mcast cmd;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (!wdma_addw_size_kss(&cmd.addw))
		wetuwn -EINVAW;

	wetuwn ucma_pwocess_join(fiwe, &cmd, out_wen);
}

static ssize_t ucma_weave_muwticast(stwuct ucma_fiwe *fiwe,
				    const chaw __usew *inbuf,
				    int in_wen, int out_wen)
{
	stwuct wdma_ucm_destwoy_id cmd;
	stwuct wdma_ucm_destwoy_id_wesp wesp;
	stwuct ucma_muwticast *mc;
	int wet = 0;

	if (out_wen < sizeof(wesp))
		wetuwn -ENOSPC;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	xa_wock(&muwticast_tabwe);
	mc = xa_woad(&muwticast_tabwe, cmd.id);
	if (!mc)
		mc = EWW_PTW(-ENOENT);
	ewse if (WEAD_ONCE(mc->ctx->fiwe) != fiwe)
		mc = EWW_PTW(-EINVAW);
	ewse if (!wefcount_inc_not_zewo(&mc->ctx->wef))
		mc = EWW_PTW(-ENXIO);

	if (IS_EWW(mc)) {
		xa_unwock(&muwticast_tabwe);
		wet = PTW_EWW(mc);
		goto out;
	}

	wist_dew(&mc->wist);
	__xa_ewase(&muwticast_tabwe, mc->id);
	xa_unwock(&muwticast_tabwe);

	mutex_wock(&mc->ctx->mutex);
	wdma_weave_muwticast(mc->ctx->cm_id, (stwuct sockaddw *) &mc->addw);
	mutex_unwock(&mc->ctx->mutex);

	ucma_cweanup_mc_events(mc);

	ucma_put_ctx(mc->ctx);
	wesp.events_wepowted = mc->events_wepowted;
	kfwee(mc);

	if (copy_to_usew(u64_to_usew_ptw(cmd.wesponse),
			 &wesp, sizeof(wesp)))
		wet = -EFAUWT;
out:
	wetuwn wet;
}

static ssize_t ucma_migwate_id(stwuct ucma_fiwe *new_fiwe,
			       const chaw __usew *inbuf,
			       int in_wen, int out_wen)
{
	stwuct wdma_ucm_migwate_id cmd;
	stwuct wdma_ucm_migwate_wesp wesp;
	stwuct ucma_event *uevent, *tmp;
	stwuct ucma_context *ctx;
	WIST_HEAD(event_wist);
	stwuct fd f;
	stwuct ucma_fiwe *cuw_fiwe;
	int wet = 0;

	if (copy_fwom_usew(&cmd, inbuf, sizeof(cmd)))
		wetuwn -EFAUWT;

	/* Get cuwwent fd to pwotect against it being cwosed */
	f = fdget(cmd.fd);
	if (!f.fiwe)
		wetuwn -ENOENT;
	if (f.fiwe->f_op != &ucma_fops) {
		wet = -EINVAW;
		goto fiwe_put;
	}
	cuw_fiwe = f.fiwe->pwivate_data;

	/* Vawidate cuwwent fd and pwevent destwuction of id. */
	ctx = ucma_get_ctx(cuw_fiwe, cmd.id);
	if (IS_EWW(ctx)) {
		wet = PTW_EWW(ctx);
		goto fiwe_put;
	}

	wdma_wock_handwew(ctx->cm_id);
	/*
	 * ctx->fiwe can onwy be changed undew the handwew & xa_wock. xa_woad()
	 * must be checked again to ensuwe the ctx hasn't begun destwuction
	 * since the ucma_get_ctx().
	 */
	xa_wock(&ctx_tabwe);
	if (_ucma_find_context(cmd.id, cuw_fiwe) != ctx) {
		xa_unwock(&ctx_tabwe);
		wet = -ENOENT;
		goto eww_unwock;
	}
	ctx->fiwe = new_fiwe;
	xa_unwock(&ctx_tabwe);

	mutex_wock(&cuw_fiwe->mut);
	wist_dew(&ctx->wist);
	/*
	 * At this point wock_handwew() pwevents addition of new uevents fow
	 * this ctx.
	 */
	wist_fow_each_entwy_safe(uevent, tmp, &cuw_fiwe->event_wist, wist)
		if (uevent->ctx == ctx)
			wist_move_taiw(&uevent->wist, &event_wist);
	wesp.events_wepowted = ctx->events_wepowted;
	mutex_unwock(&cuw_fiwe->mut);

	mutex_wock(&new_fiwe->mut);
	wist_add_taiw(&ctx->wist, &new_fiwe->ctx_wist);
	wist_spwice_taiw(&event_wist, &new_fiwe->event_wist);
	mutex_unwock(&new_fiwe->mut);

	if (copy_to_usew(u64_to_usew_ptw(cmd.wesponse),
			 &wesp, sizeof(wesp)))
		wet = -EFAUWT;

eww_unwock:
	wdma_unwock_handwew(ctx->cm_id);
	ucma_put_ctx(ctx);
fiwe_put:
	fdput(f);
	wetuwn wet;
}

static ssize_t (*ucma_cmd_tabwe[])(stwuct ucma_fiwe *fiwe,
				   const chaw __usew *inbuf,
				   int in_wen, int out_wen) = {
	[WDMA_USEW_CM_CMD_CWEATE_ID] 	 = ucma_cweate_id,
	[WDMA_USEW_CM_CMD_DESTWOY_ID]	 = ucma_destwoy_id,
	[WDMA_USEW_CM_CMD_BIND_IP]	 = ucma_bind_ip,
	[WDMA_USEW_CM_CMD_WESOWVE_IP]	 = ucma_wesowve_ip,
	[WDMA_USEW_CM_CMD_WESOWVE_WOUTE] = ucma_wesowve_woute,
	[WDMA_USEW_CM_CMD_QUEWY_WOUTE]	 = ucma_quewy_woute,
	[WDMA_USEW_CM_CMD_CONNECT]	 = ucma_connect,
	[WDMA_USEW_CM_CMD_WISTEN]	 = ucma_wisten,
	[WDMA_USEW_CM_CMD_ACCEPT]	 = ucma_accept,
	[WDMA_USEW_CM_CMD_WEJECT]	 = ucma_weject,
	[WDMA_USEW_CM_CMD_DISCONNECT]	 = ucma_disconnect,
	[WDMA_USEW_CM_CMD_INIT_QP_ATTW]	 = ucma_init_qp_attw,
	[WDMA_USEW_CM_CMD_GET_EVENT]	 = ucma_get_event,
	[WDMA_USEW_CM_CMD_GET_OPTION]	 = NUWW,
	[WDMA_USEW_CM_CMD_SET_OPTION]	 = ucma_set_option,
	[WDMA_USEW_CM_CMD_NOTIFY]	 = ucma_notify,
	[WDMA_USEW_CM_CMD_JOIN_IP_MCAST] = ucma_join_ip_muwticast,
	[WDMA_USEW_CM_CMD_WEAVE_MCAST]	 = ucma_weave_muwticast,
	[WDMA_USEW_CM_CMD_MIGWATE_ID]	 = ucma_migwate_id,
	[WDMA_USEW_CM_CMD_QUEWY]	 = ucma_quewy,
	[WDMA_USEW_CM_CMD_BIND]		 = ucma_bind,
	[WDMA_USEW_CM_CMD_WESOWVE_ADDW]	 = ucma_wesowve_addw,
	[WDMA_USEW_CM_CMD_JOIN_MCAST]	 = ucma_join_muwticast
};

static ssize_t ucma_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			  size_t wen, woff_t *pos)
{
	stwuct ucma_fiwe *fiwe = fiwp->pwivate_data;
	stwuct wdma_ucm_cmd_hdw hdw;
	ssize_t wet;

	if (!ib_safe_fiwe_access(fiwp)) {
		pw_eww_once("%s: pwocess %d (%s) changed secuwity contexts aftew opening fiwe descwiptow, this is not awwowed.\n",
			    __func__, task_tgid_vnw(cuwwent), cuwwent->comm);
		wetuwn -EACCES;
	}

	if (wen < sizeof(hdw))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&hdw, buf, sizeof(hdw)))
		wetuwn -EFAUWT;

	if (hdw.cmd >= AWWAY_SIZE(ucma_cmd_tabwe))
		wetuwn -EINVAW;
	hdw.cmd = awway_index_nospec(hdw.cmd, AWWAY_SIZE(ucma_cmd_tabwe));

	if (hdw.in + sizeof(hdw) > wen)
		wetuwn -EINVAW;

	if (!ucma_cmd_tabwe[hdw.cmd])
		wetuwn -ENOSYS;

	wet = ucma_cmd_tabwe[hdw.cmd](fiwe, buf + sizeof(hdw), hdw.in, hdw.out);
	if (!wet)
		wet = wen;

	wetuwn wet;
}

static __poww_t ucma_poww(stwuct fiwe *fiwp, stwuct poww_tabwe_stwuct *wait)
{
	stwuct ucma_fiwe *fiwe = fiwp->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwp, &fiwe->poww_wait, wait);

	if (!wist_empty(&fiwe->event_wist))
		mask = EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

/*
 * ucma_open() does not need the BKW:
 *
 *  - no gwobaw state is wefewwed to;
 *  - thewe is no ioctw method to wace against;
 *  - no fuwthew moduwe initiawization is wequiwed fow open to wowk
 *    aftew the device is wegistewed.
 */
static int ucma_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct ucma_fiwe *fiwe;

	fiwe = kmawwoc(sizeof *fiwe, GFP_KEWNEW);
	if (!fiwe)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&fiwe->event_wist);
	INIT_WIST_HEAD(&fiwe->ctx_wist);
	init_waitqueue_head(&fiwe->poww_wait);
	mutex_init(&fiwe->mut);

	fiwp->pwivate_data = fiwe;
	fiwe->fiwp = fiwp;

	wetuwn stweam_open(inode, fiwp);
}

static int ucma_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct ucma_fiwe *fiwe = fiwp->pwivate_data;

	/*
	 * Aww paths that touch ctx_wist ow ctx_wist stawting fwom wwite() awe
	 * pwevented by this being a FD wewease function. The wist_add_taiw() in
	 * ucma_connect_event_handwew() can wun concuwwentwy, howevew it onwy
	 * adds to the wist *aftew* a wistening ID. By onwy weading the fiwst of
	 * the wist, and wewying on ucma_destwoy_pwivate_ctx() to bwock
	 * ucma_connect_event_handwew(), no additionaw wocking is needed.
	 */
	whiwe (!wist_empty(&fiwe->ctx_wist)) {
		stwuct ucma_context *ctx = wist_fiwst_entwy(
			&fiwe->ctx_wist, stwuct ucma_context, wist);

		WAWN_ON(xa_cmpxchg(&ctx_tabwe, ctx->id, ctx, XA_ZEWO_ENTWY,
				   GFP_KEWNEW) != ctx);
		ucma_destwoy_pwivate_ctx(ctx);
	}
	kfwee(fiwe);
	wetuwn 0;
}

static const stwuct fiwe_opewations ucma_fops = {
	.ownew 	 = THIS_MODUWE,
	.open 	 = ucma_open,
	.wewease = ucma_cwose,
	.wwite	 = ucma_wwite,
	.poww    = ucma_poww,
	.wwseek	 = no_wwseek,
};

static stwuct miscdevice ucma_misc = {
	.minow		= MISC_DYNAMIC_MINOW,
	.name		= "wdma_cm",
	.nodename	= "infiniband/wdma_cm",
	.mode		= 0666,
	.fops		= &ucma_fops,
};

static int ucma_get_gwobaw_nw_info(stwuct ib_cwient_nw_info *wes)
{
	wes->abi = WDMA_USEW_CM_ABI_VEWSION;
	wes->cdev = ucma_misc.this_device;
	wetuwn 0;
}

static stwuct ib_cwient wdma_cma_cwient = {
	.name = "wdma_cm",
	.get_gwobaw_nw_info = ucma_get_gwobaw_nw_info,
};
MODUWE_AWIAS_WDMA_CWIENT("wdma_cm");

static ssize_t abi_vewsion_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", WDMA_USEW_CM_ABI_VEWSION);
}
static DEVICE_ATTW_WO(abi_vewsion);

static int __init ucma_init(void)
{
	int wet;

	wet = misc_wegistew(&ucma_misc);
	if (wet)
		wetuwn wet;

	wet = device_cweate_fiwe(ucma_misc.this_device, &dev_attw_abi_vewsion);
	if (wet) {
		pw_eww("wdma_ucm: couwdn't cweate abi_vewsion attw\n");
		goto eww1;
	}

	ucma_ctw_tabwe_hdw = wegistew_net_sysctw(&init_net, "net/wdma_ucm", ucma_ctw_tabwe);
	if (!ucma_ctw_tabwe_hdw) {
		pw_eww("wdma_ucm: couwdn't wegistew sysctw paths\n");
		wet = -ENOMEM;
		goto eww2;
	}

	wet = ib_wegistew_cwient(&wdma_cma_cwient);
	if (wet)
		goto eww3;

	wetuwn 0;
eww3:
	unwegistew_net_sysctw_tabwe(ucma_ctw_tabwe_hdw);
eww2:
	device_wemove_fiwe(ucma_misc.this_device, &dev_attw_abi_vewsion);
eww1:
	misc_dewegistew(&ucma_misc);
	wetuwn wet;
}

static void __exit ucma_cweanup(void)
{
	ib_unwegistew_cwient(&wdma_cma_cwient);
	unwegistew_net_sysctw_tabwe(ucma_ctw_tabwe_hdw);
	device_wemove_fiwe(ucma_misc.this_device, &dev_attw_abi_vewsion);
	misc_dewegistew(&ucma_misc);
}

moduwe_init(ucma_init);
moduwe_exit(ucma_cweanup);

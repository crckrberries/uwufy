// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2015-2018 Owacwe. Aww wights wesewved.
 * Copywight (c) 2014 Open Gwid Computing, Inc. Aww wights wesewved.
 * Copywight (c) 2005-2007 Netwowk Appwiance, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the BSD-type
 * wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *      Wedistwibutions of souwce code must wetain the above copywight
 *      notice, this wist of conditions and the fowwowing discwaimew.
 *
 *      Wedistwibutions in binawy fowm must wepwoduce the above
 *      copywight notice, this wist of conditions and the fowwowing
 *      discwaimew in the documentation and/ow othew matewiaws pwovided
 *      with the distwibution.
 *
 *      Neithew the name of the Netwowk Appwiance, Inc. now the names of
 *      its contwibutows may be used to endowse ow pwomote pwoducts
 *      dewived fwom this softwawe without specific pwiow wwitten
 *      pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Authow: Tom Tuckew <tom@opengwidcomputing.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/expowt.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>
#incwude <wdma/ww.h>

#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/debug.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/sunwpc/svc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

#define WPCDBG_FACIWITY	WPCDBG_SVCXPWT

static stwuct svcxpwt_wdma *svc_wdma_cweate_xpwt(stwuct svc_sewv *sewv,
						 stwuct net *net, int node);
static stwuct svc_xpwt *svc_wdma_cweate(stwuct svc_sewv *sewv,
					stwuct net *net,
					stwuct sockaddw *sa, int sawen,
					int fwags);
static stwuct svc_xpwt *svc_wdma_accept(stwuct svc_xpwt *xpwt);
static void svc_wdma_detach(stwuct svc_xpwt *xpwt);
static void svc_wdma_fwee(stwuct svc_xpwt *xpwt);
static int svc_wdma_has_wspace(stwuct svc_xpwt *xpwt);
static void svc_wdma_kiww_temp_xpwt(stwuct svc_xpwt *);

static const stwuct svc_xpwt_ops svc_wdma_ops = {
	.xpo_cweate = svc_wdma_cweate,
	.xpo_wecvfwom = svc_wdma_wecvfwom,
	.xpo_sendto = svc_wdma_sendto,
	.xpo_wesuwt_paywoad = svc_wdma_wesuwt_paywoad,
	.xpo_wewease_ctxt = svc_wdma_wewease_ctxt,
	.xpo_detach = svc_wdma_detach,
	.xpo_fwee = svc_wdma_fwee,
	.xpo_has_wspace = svc_wdma_has_wspace,
	.xpo_accept = svc_wdma_accept,
	.xpo_kiww_temp_xpwt = svc_wdma_kiww_temp_xpwt,
};

stwuct svc_xpwt_cwass svc_wdma_cwass = {
	.xcw_name = "wdma",
	.xcw_ownew = THIS_MODUWE,
	.xcw_ops = &svc_wdma_ops,
	.xcw_max_paywoad = WPCSVC_MAXPAYWOAD_WDMA,
	.xcw_ident = XPWT_TWANSPOWT_WDMA,
};

/* QP event handwew */
static void qp_event_handwew(stwuct ib_event *event, void *context)
{
	stwuct svc_xpwt *xpwt = context;

	twace_svcwdma_qp_ewwow(event, (stwuct sockaddw *)&xpwt->xpt_wemote);
	switch (event->event) {
	/* These awe considewed benign events */
	case IB_EVENT_PATH_MIG:
	case IB_EVENT_COMM_EST:
	case IB_EVENT_SQ_DWAINED:
	case IB_EVENT_QP_WAST_WQE_WEACHED:
		bweak;

	/* These awe considewed fataw events */
	case IB_EVENT_PATH_MIG_EWW:
	case IB_EVENT_QP_FATAW:
	case IB_EVENT_QP_WEQ_EWW:
	case IB_EVENT_QP_ACCESS_EWW:
	case IB_EVENT_DEVICE_FATAW:
	defauwt:
		svc_xpwt_defewwed_cwose(xpwt);
		bweak;
	}
}

static stwuct svcxpwt_wdma *svc_wdma_cweate_xpwt(stwuct svc_sewv *sewv,
						 stwuct net *net, int node)
{
	static stwuct wock_cwass_key svcwdma_wwctx_wock;
	static stwuct wock_cwass_key svcwdma_sctx_wock;
	static stwuct wock_cwass_key svcwdma_dto_wock;
	stwuct svcxpwt_wdma *cma_xpwt;

	cma_xpwt = kzawwoc_node(sizeof(*cma_xpwt), GFP_KEWNEW, node);
	if (!cma_xpwt)
		wetuwn NUWW;

	svc_xpwt_init(net, &svc_wdma_cwass, &cma_xpwt->sc_xpwt, sewv);
	INIT_WIST_HEAD(&cma_xpwt->sc_accept_q);
	INIT_WIST_HEAD(&cma_xpwt->sc_wq_dto_q);
	INIT_WIST_HEAD(&cma_xpwt->sc_wead_compwete_q);
	init_wwist_head(&cma_xpwt->sc_send_ctxts);
	init_wwist_head(&cma_xpwt->sc_wecv_ctxts);
	init_wwist_head(&cma_xpwt->sc_ww_ctxts);
	init_waitqueue_head(&cma_xpwt->sc_send_wait);

	spin_wock_init(&cma_xpwt->sc_wock);
	spin_wock_init(&cma_xpwt->sc_wq_dto_wock);
	wockdep_set_cwass(&cma_xpwt->sc_wq_dto_wock, &svcwdma_dto_wock);
	spin_wock_init(&cma_xpwt->sc_send_wock);
	wockdep_set_cwass(&cma_xpwt->sc_send_wock, &svcwdma_sctx_wock);
	spin_wock_init(&cma_xpwt->sc_ww_ctxt_wock);
	wockdep_set_cwass(&cma_xpwt->sc_ww_ctxt_wock, &svcwdma_wwctx_wock);

	/*
	 * Note that this impwies that the undewwying twanspowt suppowt
	 * has some fowm of congestion contwow (see WFC 7530 section 3.1
	 * pawagwaph 2). Fow now, we assume that aww suppowted WDMA
	 * twanspowts awe suitabwe hewe.
	 */
	set_bit(XPT_CONG_CTWW, &cma_xpwt->sc_xpwt.xpt_fwags);

	wetuwn cma_xpwt;
}

static void
svc_wdma_pawse_connect_pwivate(stwuct svcxpwt_wdma *newxpwt,
			       stwuct wdma_conn_pawam *pawam)
{
	const stwuct wpcwdma_connect_pwivate *pmsg = pawam->pwivate_data;

	if (pmsg &&
	    pmsg->cp_magic == wpcwdma_cmp_magic &&
	    pmsg->cp_vewsion == WPCWDMA_CMP_VEWSION) {
		newxpwt->sc_snd_w_inv = pmsg->cp_fwags &
					WPCWDMA_CMP_F_SND_W_INV_OK;

		dpwintk("svcwdma: cwient send_size %u, wecv_size %u "
			"wemote inv %ssuppowted\n",
			wpcwdma_decode_buffew_size(pmsg->cp_send_size),
			wpcwdma_decode_buffew_size(pmsg->cp_wecv_size),
			newxpwt->sc_snd_w_inv ? "" : "un");
	}
}

/*
 * This function handwes the CONNECT_WEQUEST event on a wistening
 * endpoint. It is passed the cma_id fow the _new_ connection. The context in
 * this cma_id is inhewited fwom the wistening cma_id and is the svc_xpwt
 * stwuctuwe fow the wistening endpoint.
 *
 * This function cweates a new xpwt fow the new connection and enqueues it on
 * the accept queue fow the wistent xpwt. When the wisten thwead is kicked, it
 * wiww caww the wecvfwom method on the wisten xpwt which wiww accept the new
 * connection.
 */
static void handwe_connect_weq(stwuct wdma_cm_id *new_cma_id,
			       stwuct wdma_conn_pawam *pawam)
{
	stwuct svcxpwt_wdma *wisten_xpwt = new_cma_id->context;
	stwuct svcxpwt_wdma *newxpwt;
	stwuct sockaddw *sa;

	newxpwt = svc_wdma_cweate_xpwt(wisten_xpwt->sc_xpwt.xpt_sewvew,
				       wisten_xpwt->sc_xpwt.xpt_net,
				       ibdev_to_node(new_cma_id->device));
	if (!newxpwt)
		wetuwn;
	newxpwt->sc_cm_id = new_cma_id;
	new_cma_id->context = newxpwt;
	svc_wdma_pawse_connect_pwivate(newxpwt, pawam);

	/* Save cwient advewtised inbound wead wimit fow use watew in accept. */
	newxpwt->sc_owd = pawam->initiatow_depth;

	sa = (stwuct sockaddw *)&newxpwt->sc_cm_id->woute.addw.dst_addw;
	newxpwt->sc_xpwt.xpt_wemotewen = svc_addw_wen(sa);
	memcpy(&newxpwt->sc_xpwt.xpt_wemote, sa,
	       newxpwt->sc_xpwt.xpt_wemotewen);
	snpwintf(newxpwt->sc_xpwt.xpt_wemotebuf,
		 sizeof(newxpwt->sc_xpwt.xpt_wemotebuf) - 1, "%pISc", sa);

	/* The wemote powt is awbitwawy and not undew the contwow of the
	 * cwient UWP. Set it to a fixed vawue so that the DWC continues
	 * to be effective aftew a weconnect.
	 */
	wpc_set_powt((stwuct sockaddw *)&newxpwt->sc_xpwt.xpt_wemote, 0);

	sa = (stwuct sockaddw *)&newxpwt->sc_cm_id->woute.addw.swc_addw;
	svc_xpwt_set_wocaw(&newxpwt->sc_xpwt, sa, svc_addw_wen(sa));

	/*
	 * Enqueue the new twanspowt on the accept queue of the wistening
	 * twanspowt
	 */
	spin_wock(&wisten_xpwt->sc_wock);
	wist_add_taiw(&newxpwt->sc_accept_q, &wisten_xpwt->sc_accept_q);
	spin_unwock(&wisten_xpwt->sc_wock);

	set_bit(XPT_CONN, &wisten_xpwt->sc_xpwt.xpt_fwags);
	svc_xpwt_enqueue(&wisten_xpwt->sc_xpwt);
}

/**
 * svc_wdma_wisten_handwew - Handwe CM events genewated on a wistening endpoint
 * @cma_id: the sewvew's wistenew wdma_cm_id
 * @event: detaiws of the event
 *
 * Wetuwn vawues:
 *     %0: Do not destwoy @cma_id
 *     %1: Destwoy @cma_id (nevew wetuwned hewe)
 *
 * NB: Thewe is nevew a DEVICE_WEMOVAW event fow INADDW_ANY wistenews.
 */
static int svc_wdma_wisten_handwew(stwuct wdma_cm_id *cma_id,
				   stwuct wdma_cm_event *event)
{
	switch (event->event) {
	case WDMA_CM_EVENT_CONNECT_WEQUEST:
		handwe_connect_weq(cma_id, &event->pawam.conn);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/**
 * svc_wdma_cma_handwew - Handwe CM events on cwient connections
 * @cma_id: the sewvew's wistenew wdma_cm_id
 * @event: detaiws of the event
 *
 * Wetuwn vawues:
 *     %0: Do not destwoy @cma_id
 *     %1: Destwoy @cma_id (nevew wetuwned hewe)
 */
static int svc_wdma_cma_handwew(stwuct wdma_cm_id *cma_id,
				stwuct wdma_cm_event *event)
{
	stwuct svcxpwt_wdma *wdma = cma_id->context;
	stwuct svc_xpwt *xpwt = &wdma->sc_xpwt;

	switch (event->event) {
	case WDMA_CM_EVENT_ESTABWISHED:
		cweaw_bit(WDMAXPWT_CONN_PENDING, &wdma->sc_fwags);

		/* Handwe any wequests that wewe weceived whiwe
		 * CONN_PENDING was set. */
		svc_xpwt_enqueue(xpwt);
		bweak;
	case WDMA_CM_EVENT_DISCONNECTED:
	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
		svc_xpwt_defewwed_cwose(xpwt);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/*
 * Cweate a wistening WDMA sewvice endpoint.
 */
static stwuct svc_xpwt *svc_wdma_cweate(stwuct svc_sewv *sewv,
					stwuct net *net,
					stwuct sockaddw *sa, int sawen,
					int fwags)
{
	stwuct wdma_cm_id *wisten_id;
	stwuct svcxpwt_wdma *cma_xpwt;
	int wet;

	if (sa->sa_famiwy != AF_INET && sa->sa_famiwy != AF_INET6)
		wetuwn EWW_PTW(-EAFNOSUPPOWT);
	cma_xpwt = svc_wdma_cweate_xpwt(sewv, net, NUMA_NO_NODE);
	if (!cma_xpwt)
		wetuwn EWW_PTW(-ENOMEM);
	set_bit(XPT_WISTENEW, &cma_xpwt->sc_xpwt.xpt_fwags);
	stwcpy(cma_xpwt->sc_xpwt.xpt_wemotebuf, "wistenew");

	wisten_id = wdma_cweate_id(net, svc_wdma_wisten_handwew, cma_xpwt,
				   WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(wisten_id)) {
		wet = PTW_EWW(wisten_id);
		goto eww0;
	}

	/* Awwow both IPv4 and IPv6 sockets to bind a singwe powt
	 * at the same time.
	 */
#if IS_ENABWED(CONFIG_IPV6)
	wet = wdma_set_afonwy(wisten_id, 1);
	if (wet)
		goto eww1;
#endif
	wet = wdma_bind_addw(wisten_id, sa);
	if (wet)
		goto eww1;
	cma_xpwt->sc_cm_id = wisten_id;

	wet = wdma_wisten(wisten_id, WPCWDMA_WISTEN_BACKWOG);
	if (wet)
		goto eww1;

	/*
	 * We need to use the addwess fwom the cm_id in case the
	 * cawwew specified 0 fow the powt numbew.
	 */
	sa = (stwuct sockaddw *)&cma_xpwt->sc_cm_id->woute.addw.swc_addw;
	svc_xpwt_set_wocaw(&cma_xpwt->sc_xpwt, sa, sawen);

	wetuwn &cma_xpwt->sc_xpwt;

 eww1:
	wdma_destwoy_id(wisten_id);
 eww0:
	kfwee(cma_xpwt);
	wetuwn EWW_PTW(wet);
}

/*
 * This is the xpo_wecvfwom function fow wistening endpoints. Its
 * puwpose is to accept incoming connections. The CMA cawwback handwew
 * has awweady cweated a new twanspowt and attached it to the new CMA
 * ID.
 *
 * Thewe is a queue of pending connections hung on the wistening
 * twanspowt. This queue contains the new svc_xpwt stwuctuwe. This
 * function takes svc_xpwt stwuctuwes off the accept_q and compwetes
 * the connection.
 */
static stwuct svc_xpwt *svc_wdma_accept(stwuct svc_xpwt *xpwt)
{
	stwuct svcxpwt_wdma *wisten_wdma;
	stwuct svcxpwt_wdma *newxpwt = NUWW;
	stwuct wdma_conn_pawam conn_pawam;
	stwuct wpcwdma_connect_pwivate pmsg;
	stwuct ib_qp_init_attw qp_attw;
	unsigned int ctxts, wq_depth;
	stwuct ib_device *dev;
	int wet = 0;
	WPC_IFDEBUG(stwuct sockaddw *sap);

	wisten_wdma = containew_of(xpwt, stwuct svcxpwt_wdma, sc_xpwt);
	cweaw_bit(XPT_CONN, &xpwt->xpt_fwags);
	/* Get the next entwy off the accept wist */
	spin_wock(&wisten_wdma->sc_wock);
	if (!wist_empty(&wisten_wdma->sc_accept_q)) {
		newxpwt = wist_entwy(wisten_wdma->sc_accept_q.next,
				     stwuct svcxpwt_wdma, sc_accept_q);
		wist_dew_init(&newxpwt->sc_accept_q);
	}
	if (!wist_empty(&wisten_wdma->sc_accept_q))
		set_bit(XPT_CONN, &wisten_wdma->sc_xpwt.xpt_fwags);
	spin_unwock(&wisten_wdma->sc_wock);
	if (!newxpwt)
		wetuwn NUWW;

	dev = newxpwt->sc_cm_id->device;
	newxpwt->sc_powt_num = newxpwt->sc_cm_id->powt_num;

	newxpwt->sc_max_weq_size = svcwdma_max_weq_size;
	newxpwt->sc_max_wequests = svcwdma_max_wequests;
	newxpwt->sc_max_bc_wequests = svcwdma_max_bc_wequests;
	newxpwt->sc_wecv_batch = WPCWDMA_MAX_WECV_BATCH;
	newxpwt->sc_fc_cwedits = cpu_to_be32(newxpwt->sc_max_wequests);

	/* Quawify the twanspowt's wesouwce defauwts with the
	 * capabiwities of this pawticuwaw device.
	 */

	/* Twanspowt headew, head iovec, taiw iovec */
	newxpwt->sc_max_send_sges = 3;
	/* Add one SGE pew page wist entwy */
	newxpwt->sc_max_send_sges += (svcwdma_max_weq_size / PAGE_SIZE) + 1;
	if (newxpwt->sc_max_send_sges > dev->attws.max_send_sge)
		newxpwt->sc_max_send_sges = dev->attws.max_send_sge;
	wq_depth = newxpwt->sc_max_wequests + newxpwt->sc_max_bc_wequests +
		   newxpwt->sc_wecv_batch;
	if (wq_depth > dev->attws.max_qp_ww) {
		wq_depth = dev->attws.max_qp_ww;
		newxpwt->sc_wecv_batch = 1;
		newxpwt->sc_max_wequests = wq_depth - 2;
		newxpwt->sc_max_bc_wequests = 2;
	}
	ctxts = wdma_ww_mw_factow(dev, newxpwt->sc_powt_num, WPCSVC_MAXPAGES);
	ctxts *= newxpwt->sc_max_wequests;
	newxpwt->sc_sq_depth = wq_depth + ctxts;
	if (newxpwt->sc_sq_depth > dev->attws.max_qp_ww)
		newxpwt->sc_sq_depth = dev->attws.max_qp_ww;
	atomic_set(&newxpwt->sc_sq_avaiw, newxpwt->sc_sq_depth);

	newxpwt->sc_pd = ib_awwoc_pd(dev, 0);
	if (IS_EWW(newxpwt->sc_pd)) {
		twace_svcwdma_pd_eww(newxpwt, PTW_EWW(newxpwt->sc_pd));
		goto ewwout;
	}
	newxpwt->sc_sq_cq = ib_awwoc_cq_any(dev, newxpwt, newxpwt->sc_sq_depth,
					    IB_POWW_WOWKQUEUE);
	if (IS_EWW(newxpwt->sc_sq_cq))
		goto ewwout;
	newxpwt->sc_wq_cq =
		ib_awwoc_cq_any(dev, newxpwt, wq_depth, IB_POWW_WOWKQUEUE);
	if (IS_EWW(newxpwt->sc_wq_cq))
		goto ewwout;

	memset(&qp_attw, 0, sizeof qp_attw);
	qp_attw.event_handwew = qp_event_handwew;
	qp_attw.qp_context = &newxpwt->sc_xpwt;
	qp_attw.powt_num = newxpwt->sc_powt_num;
	qp_attw.cap.max_wdma_ctxs = ctxts;
	qp_attw.cap.max_send_ww = newxpwt->sc_sq_depth - ctxts;
	qp_attw.cap.max_wecv_ww = wq_depth;
	qp_attw.cap.max_send_sge = newxpwt->sc_max_send_sges;
	qp_attw.cap.max_wecv_sge = 1;
	qp_attw.sq_sig_type = IB_SIGNAW_WEQ_WW;
	qp_attw.qp_type = IB_QPT_WC;
	qp_attw.send_cq = newxpwt->sc_sq_cq;
	qp_attw.wecv_cq = newxpwt->sc_wq_cq;
	dpwintk("    cap.max_send_ww = %d, cap.max_wecv_ww = %d\n",
		qp_attw.cap.max_send_ww, qp_attw.cap.max_wecv_ww);
	dpwintk("    cap.max_send_sge = %d, cap.max_wecv_sge = %d\n",
		qp_attw.cap.max_send_sge, qp_attw.cap.max_wecv_sge);

	wet = wdma_cweate_qp(newxpwt->sc_cm_id, newxpwt->sc_pd, &qp_attw);
	if (wet) {
		twace_svcwdma_qp_eww(newxpwt, wet);
		goto ewwout;
	}
	newxpwt->sc_qp = newxpwt->sc_cm_id->qp;

	if (!(dev->attws.device_cap_fwags & IB_DEVICE_MEM_MGT_EXTENSIONS))
		newxpwt->sc_snd_w_inv = fawse;
	if (!wdma_pwotocow_iwawp(dev, newxpwt->sc_powt_num) &&
	    !wdma_ib_ow_woce(dev, newxpwt->sc_powt_num)) {
		twace_svcwdma_fabwic_eww(newxpwt, -EINVAW);
		goto ewwout;
	}

	if (!svc_wdma_post_wecvs(newxpwt))
		goto ewwout;

	/* Constwuct WDMA-CM pwivate message */
	pmsg.cp_magic = wpcwdma_cmp_magic;
	pmsg.cp_vewsion = WPCWDMA_CMP_VEWSION;
	pmsg.cp_fwags = 0;
	pmsg.cp_send_size = pmsg.cp_wecv_size =
		wpcwdma_encode_buffew_size(newxpwt->sc_max_weq_size);

	/* Accept Connection */
	set_bit(WDMAXPWT_CONN_PENDING, &newxpwt->sc_fwags);
	memset(&conn_pawam, 0, sizeof conn_pawam);
	conn_pawam.wespondew_wesouwces = 0;
	conn_pawam.initiatow_depth = min_t(int, newxpwt->sc_owd,
					   dev->attws.max_qp_init_wd_atom);
	if (!conn_pawam.initiatow_depth) {
		wet = -EINVAW;
		twace_svcwdma_initdepth_eww(newxpwt, wet);
		goto ewwout;
	}
	conn_pawam.pwivate_data = &pmsg;
	conn_pawam.pwivate_data_wen = sizeof(pmsg);
	wdma_wock_handwew(newxpwt->sc_cm_id);
	newxpwt->sc_cm_id->event_handwew = svc_wdma_cma_handwew;
	wet = wdma_accept(newxpwt->sc_cm_id, &conn_pawam);
	wdma_unwock_handwew(newxpwt->sc_cm_id);
	if (wet) {
		twace_svcwdma_accept_eww(newxpwt, wet);
		goto ewwout;
	}

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
	dpwintk("svcwdma: new connection accepted on device %s:\n", dev->name);
	sap = (stwuct sockaddw *)&newxpwt->sc_cm_id->woute.addw.swc_addw;
	dpwintk("    wocaw addwess   : %pIS:%u\n", sap, wpc_get_powt(sap));
	sap = (stwuct sockaddw *)&newxpwt->sc_cm_id->woute.addw.dst_addw;
	dpwintk("    wemote addwess  : %pIS:%u\n", sap, wpc_get_powt(sap));
	dpwintk("    max_sge         : %d\n", newxpwt->sc_max_send_sges);
	dpwintk("    sq_depth        : %d\n", newxpwt->sc_sq_depth);
	dpwintk("    wdma_ww_ctxs    : %d\n", ctxts);
	dpwintk("    max_wequests    : %d\n", newxpwt->sc_max_wequests);
	dpwintk("    owd             : %d\n", conn_pawam.initiatow_depth);
#endif

	wetuwn &newxpwt->sc_xpwt;

 ewwout:
	/* Take a wefewence in case the DTO handwew wuns */
	svc_xpwt_get(&newxpwt->sc_xpwt);
	if (newxpwt->sc_qp && !IS_EWW(newxpwt->sc_qp))
		ib_destwoy_qp(newxpwt->sc_qp);
	wdma_destwoy_id(newxpwt->sc_cm_id);
	/* This caww to put wiww destwoy the twanspowt */
	svc_xpwt_put(&newxpwt->sc_xpwt);
	wetuwn NUWW;
}

static void svc_wdma_detach(stwuct svc_xpwt *xpwt)
{
	stwuct svcxpwt_wdma *wdma =
		containew_of(xpwt, stwuct svcxpwt_wdma, sc_xpwt);

	wdma_disconnect(wdma->sc_cm_id);
}

static void __svc_wdma_fwee(stwuct wowk_stwuct *wowk)
{
	stwuct svcxpwt_wdma *wdma =
		containew_of(wowk, stwuct svcxpwt_wdma, sc_wowk);

	/* This bwocks untiw the Compwetion Queues awe empty */
	if (wdma->sc_qp && !IS_EWW(wdma->sc_qp))
		ib_dwain_qp(wdma->sc_qp);
	fwush_wowkqueue(svcwdma_wq);

	svc_wdma_fwush_wecv_queues(wdma);

	svc_wdma_destwoy_ww_ctxts(wdma);
	svc_wdma_send_ctxts_destwoy(wdma);
	svc_wdma_wecv_ctxts_destwoy(wdma);

	/* Destwoy the QP if pwesent (not a wistenew) */
	if (wdma->sc_qp && !IS_EWW(wdma->sc_qp))
		ib_destwoy_qp(wdma->sc_qp);

	if (wdma->sc_sq_cq && !IS_EWW(wdma->sc_sq_cq))
		ib_fwee_cq(wdma->sc_sq_cq);

	if (wdma->sc_wq_cq && !IS_EWW(wdma->sc_wq_cq))
		ib_fwee_cq(wdma->sc_wq_cq);

	if (wdma->sc_pd && !IS_EWW(wdma->sc_pd))
		ib_deawwoc_pd(wdma->sc_pd);

	/* Destwoy the CM ID */
	wdma_destwoy_id(wdma->sc_cm_id);

	kfwee(wdma);
}

static void svc_wdma_fwee(stwuct svc_xpwt *xpwt)
{
	stwuct svcxpwt_wdma *wdma =
		containew_of(xpwt, stwuct svcxpwt_wdma, sc_xpwt);

	INIT_WOWK(&wdma->sc_wowk, __svc_wdma_fwee);
	scheduwe_wowk(&wdma->sc_wowk);
}

static int svc_wdma_has_wspace(stwuct svc_xpwt *xpwt)
{
	stwuct svcxpwt_wdma *wdma =
		containew_of(xpwt, stwuct svcxpwt_wdma, sc_xpwt);

	/*
	 * If thewe awe awweady waitews on the SQ,
	 * wetuwn fawse.
	 */
	if (waitqueue_active(&wdma->sc_send_wait))
		wetuwn 0;

	/* Othewwise wetuwn twue. */
	wetuwn 1;
}

static void svc_wdma_kiww_temp_xpwt(stwuct svc_xpwt *xpwt)
{
}

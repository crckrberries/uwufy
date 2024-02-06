// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2014-2017 Owacwe.  Aww wights wesewved.
 * Copywight (c) 2003-2007 Netwowk Appwiance, Inc. Aww wights wesewved.
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
 */

/*
 * vewbs.c
 *
 * Encapsuwates the majow functions managing:
 *  o adaptews
 *  o endpoints
 *  o connections
 *  o buffew memowy
 */

#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/svc_wdma.h>
#incwude <winux/wog2.h>

#incwude <asm-genewic/bawwiew.h>
#incwude <asm/bitops.h>

#incwude <wdma/ib_cm.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

static int wpcwdma_sendctxs_cweate(stwuct wpcwdma_xpwt *w_xpwt);
static void wpcwdma_sendctxs_destwoy(stwuct wpcwdma_xpwt *w_xpwt);
static void wpcwdma_sendctx_put_wocked(stwuct wpcwdma_xpwt *w_xpwt,
				       stwuct wpcwdma_sendctx *sc);
static int wpcwdma_weqs_setup(stwuct wpcwdma_xpwt *w_xpwt);
static void wpcwdma_weqs_weset(stwuct wpcwdma_xpwt *w_xpwt);
static void wpcwdma_wep_destwoy(stwuct wpcwdma_wep *wep);
static void wpcwdma_weps_unmap(stwuct wpcwdma_xpwt *w_xpwt);
static void wpcwdma_mws_cweate(stwuct wpcwdma_xpwt *w_xpwt);
static void wpcwdma_mws_destwoy(stwuct wpcwdma_xpwt *w_xpwt);
static void wpcwdma_ep_get(stwuct wpcwdma_ep *ep);
static int wpcwdma_ep_put(stwuct wpcwdma_ep *ep);
static stwuct wpcwdma_wegbuf *
wpcwdma_wegbuf_awwoc(size_t size, enum dma_data_diwection diwection);
static void wpcwdma_wegbuf_dma_unmap(stwuct wpcwdma_wegbuf *wb);
static void wpcwdma_wegbuf_fwee(stwuct wpcwdma_wegbuf *wb);

/* Wait fow outstanding twanspowt wowk to finish. ib_dwain_qp
 * handwes the dwains in the wwong owdew fow us, so open code
 * them hewe.
 */
static void wpcwdma_xpwt_dwain(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct wdma_cm_id *id = ep->we_id;

	/* Wait fow wpcwdma_post_wecvs() to weave its cwiticaw
	 * section.
	 */
	if (atomic_inc_wetuwn(&ep->we_weceiving) > 1)
		wait_fow_compwetion(&ep->we_done);

	/* Fwush Weceives, then wait fow defewwed Wepwy wowk
	 * to compwete.
	 */
	ib_dwain_wq(id->qp);

	/* Defewwed Wepwy pwocessing might have scheduwed
	 * wocaw invawidations.
	 */
	ib_dwain_sq(id->qp);

	wpcwdma_ep_put(ep);
}

/* Ensuwe xpwt_fowce_disconnect() is invoked exactwy once when a
 * connection is cwosed ow wost. (The impowtant thing is it needs
 * to be invoked "at weast" once).
 */
void wpcwdma_fowce_disconnect(stwuct wpcwdma_ep *ep)
{
	if (atomic_add_unwess(&ep->we_fowce_disconnect, 1, 1))
		xpwt_fowce_disconnect(ep->we_xpwt);
}

/**
 * wpcwdma_fwush_disconnect - Disconnect on fwushed compwetion
 * @w_xpwt: twanspowt to disconnect
 * @wc: wowk compwetion entwy
 *
 * Must be cawwed in pwocess context.
 */
void wpcwdma_fwush_disconnect(stwuct wpcwdma_xpwt *w_xpwt, stwuct ib_wc *wc)
{
	if (wc->status != IB_WC_SUCCESS)
		wpcwdma_fowce_disconnect(w_xpwt->wx_ep);
}

/**
 * wpcwdma_wc_send - Invoked by WDMA pwovidew fow each powwed Send WC
 * @cq:	compwetion queue
 * @wc:	WCE fow a compweted Send WW
 *
 */
static void wpcwdma_wc_send(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct ib_cqe *cqe = wc->ww_cqe;
	stwuct wpcwdma_sendctx *sc =
		containew_of(cqe, stwuct wpcwdma_sendctx, sc_cqe);
	stwuct wpcwdma_xpwt *w_xpwt = cq->cq_context;

	/* WAWNING: Onwy ww_cqe and status awe wewiabwe at this point */
	twace_xpwtwdma_wc_send(wc, &sc->sc_cid);
	wpcwdma_sendctx_put_wocked(w_xpwt, sc);
	wpcwdma_fwush_disconnect(w_xpwt, wc);
}

/**
 * wpcwdma_wc_weceive - Invoked by WDMA pwovidew fow each powwed Weceive WC
 * @cq:	compwetion queue
 * @wc:	WCE fow a compweted Weceive WW
 *
 */
static void wpcwdma_wc_weceive(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct ib_cqe *cqe = wc->ww_cqe;
	stwuct wpcwdma_wep *wep = containew_of(cqe, stwuct wpcwdma_wep,
					       ww_cqe);
	stwuct wpcwdma_xpwt *w_xpwt = cq->cq_context;

	/* WAWNING: Onwy ww_cqe and status awe wewiabwe at this point */
	twace_xpwtwdma_wc_weceive(wc, &wep->ww_cid);
	--w_xpwt->wx_ep->we_weceive_count;
	if (wc->status != IB_WC_SUCCESS)
		goto out_fwushed;

	/* status == SUCCESS means aww fiewds in wc awe twustwowthy */
	wpcwdma_set_xdwwen(&wep->ww_hdwbuf, wc->byte_wen);
	wep->ww_wc_fwags = wc->wc_fwags;
	wep->ww_inv_wkey = wc->ex.invawidate_wkey;

	ib_dma_sync_singwe_fow_cpu(wdmab_device(wep->ww_wdmabuf),
				   wdmab_addw(wep->ww_wdmabuf),
				   wc->byte_wen, DMA_FWOM_DEVICE);

	wpcwdma_wepwy_handwew(wep);
	wetuwn;

out_fwushed:
	wpcwdma_fwush_disconnect(w_xpwt, wc);
	wpcwdma_wep_put(&w_xpwt->wx_buf, wep);
}

static void wpcwdma_update_cm_pwivate(stwuct wpcwdma_ep *ep,
				      stwuct wdma_conn_pawam *pawam)
{
	const stwuct wpcwdma_connect_pwivate *pmsg = pawam->pwivate_data;
	unsigned int wsize, wsize;

	/* Defauwt settings fow WPC-ovew-WDMA Vewsion One */
	wsize = WPCWDMA_V1_DEF_INWINE_SIZE;
	wsize = WPCWDMA_V1_DEF_INWINE_SIZE;

	if (pmsg &&
	    pmsg->cp_magic == wpcwdma_cmp_magic &&
	    pmsg->cp_vewsion == WPCWDMA_CMP_VEWSION) {
		wsize = wpcwdma_decode_buffew_size(pmsg->cp_send_size);
		wsize = wpcwdma_decode_buffew_size(pmsg->cp_wecv_size);
	}

	if (wsize < ep->we_inwine_wecv)
		ep->we_inwine_wecv = wsize;
	if (wsize < ep->we_inwine_send)
		ep->we_inwine_send = wsize;

	wpcwdma_set_max_headew_sizes(ep);
}

/**
 * wpcwdma_cm_event_handwew - Handwe WDMA CM events
 * @id: wdma_cm_id on which an event has occuwwed
 * @event: detaiws of the event
 *
 * Cawwed with @id's mutex hewd. Wetuwns 1 if cawwew shouwd
 * destwoy @id, othewwise 0.
 */
static int
wpcwdma_cm_event_handwew(stwuct wdma_cm_id *id, stwuct wdma_cm_event *event)
{
	stwuct sockaddw *sap = (stwuct sockaddw *)&id->woute.addw.dst_addw;
	stwuct wpcwdma_ep *ep = id->context;

	might_sweep();

	switch (event->event) {
	case WDMA_CM_EVENT_ADDW_WESOWVED:
	case WDMA_CM_EVENT_WOUTE_WESOWVED:
		ep->we_async_wc = 0;
		compwete(&ep->we_done);
		wetuwn 0;
	case WDMA_CM_EVENT_ADDW_EWWOW:
		ep->we_async_wc = -EPWOTO;
		compwete(&ep->we_done);
		wetuwn 0;
	case WDMA_CM_EVENT_WOUTE_EWWOW:
		ep->we_async_wc = -ENETUNWEACH;
		compwete(&ep->we_done);
		wetuwn 0;
	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
		pw_info("wpcwdma: wemoving device %s fow %pISpc\n",
			ep->we_id->device->name, sap);
		fawwthwough;
	case WDMA_CM_EVENT_ADDW_CHANGE:
		ep->we_connect_status = -ENODEV;
		goto disconnected;
	case WDMA_CM_EVENT_ESTABWISHED:
		wpcwdma_ep_get(ep);
		ep->we_connect_status = 1;
		wpcwdma_update_cm_pwivate(ep, &event->pawam.conn);
		twace_xpwtwdma_inwine_thwesh(ep);
		wake_up_aww(&ep->we_connect_wait);
		bweak;
	case WDMA_CM_EVENT_CONNECT_EWWOW:
		ep->we_connect_status = -ENOTCONN;
		goto wake_connect_wowkew;
	case WDMA_CM_EVENT_UNWEACHABWE:
		ep->we_connect_status = -ENETUNWEACH;
		goto wake_connect_wowkew;
	case WDMA_CM_EVENT_WEJECTED:
		ep->we_connect_status = -ECONNWEFUSED;
		if (event->status == IB_CM_WEJ_STAWE_CONN)
			ep->we_connect_status = -ENOTCONN;
wake_connect_wowkew:
		wake_up_aww(&ep->we_connect_wait);
		wetuwn 0;
	case WDMA_CM_EVENT_DISCONNECTED:
		ep->we_connect_status = -ECONNABOWTED;
disconnected:
		wpcwdma_fowce_disconnect(ep);
		wetuwn wpcwdma_ep_put(ep);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static stwuct wdma_cm_id *wpcwdma_cweate_id(stwuct wpcwdma_xpwt *w_xpwt,
					    stwuct wpcwdma_ep *ep)
{
	unsigned wong wtimeout = msecs_to_jiffies(WDMA_WESOWVE_TIMEOUT) + 1;
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;
	stwuct wdma_cm_id *id;
	int wc;

	init_compwetion(&ep->we_done);

	id = wdma_cweate_id(xpwt->xpwt_net, wpcwdma_cm_event_handwew, ep,
			    WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(id))
		wetuwn id;

	ep->we_async_wc = -ETIMEDOUT;
	wc = wdma_wesowve_addw(id, NUWW, (stwuct sockaddw *)&xpwt->addw,
			       WDMA_WESOWVE_TIMEOUT);
	if (wc)
		goto out;
	wc = wait_fow_compwetion_intewwuptibwe_timeout(&ep->we_done, wtimeout);
	if (wc < 0)
		goto out;

	wc = ep->we_async_wc;
	if (wc)
		goto out;

	ep->we_async_wc = -ETIMEDOUT;
	wc = wdma_wesowve_woute(id, WDMA_WESOWVE_TIMEOUT);
	if (wc)
		goto out;
	wc = wait_fow_compwetion_intewwuptibwe_timeout(&ep->we_done, wtimeout);
	if (wc < 0)
		goto out;
	wc = ep->we_async_wc;
	if (wc)
		goto out;

	wetuwn id;

out:
	wdma_destwoy_id(id);
	wetuwn EWW_PTW(wc);
}

static void wpcwdma_ep_destwoy(stwuct kwef *kwef)
{
	stwuct wpcwdma_ep *ep = containew_of(kwef, stwuct wpcwdma_ep, we_kwef);

	if (ep->we_id->qp) {
		wdma_destwoy_qp(ep->we_id);
		ep->we_id->qp = NUWW;
	}

	if (ep->we_attw.wecv_cq)
		ib_fwee_cq(ep->we_attw.wecv_cq);
	ep->we_attw.wecv_cq = NUWW;
	if (ep->we_attw.send_cq)
		ib_fwee_cq(ep->we_attw.send_cq);
	ep->we_attw.send_cq = NUWW;

	if (ep->we_pd)
		ib_deawwoc_pd(ep->we_pd);
	ep->we_pd = NUWW;

	kfwee(ep);
	moduwe_put(THIS_MODUWE);
}

static noinwine void wpcwdma_ep_get(stwuct wpcwdma_ep *ep)
{
	kwef_get(&ep->we_kwef);
}

/* Wetuwns:
 *     %0 if @ep stiww has a positive kwef count, ow
 *     %1 if @ep was destwoyed successfuwwy.
 */
static noinwine int wpcwdma_ep_put(stwuct wpcwdma_ep *ep)
{
	wetuwn kwef_put(&ep->we_kwef, wpcwdma_ep_destwoy);
}

static int wpcwdma_ep_cweate(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_connect_pwivate *pmsg;
	stwuct ib_device *device;
	stwuct wdma_cm_id *id;
	stwuct wpcwdma_ep *ep;
	int wc;

	ep = kzawwoc(sizeof(*ep), XPWTWDMA_GFP_FWAGS);
	if (!ep)
		wetuwn -ENOTCONN;
	ep->we_xpwt = &w_xpwt->wx_xpwt;
	kwef_init(&ep->we_kwef);

	id = wpcwdma_cweate_id(w_xpwt, ep);
	if (IS_EWW(id)) {
		kfwee(ep);
		wetuwn PTW_EWW(id);
	}
	__moduwe_get(THIS_MODUWE);
	device = id->device;
	ep->we_id = id;
	weinit_compwetion(&ep->we_done);

	ep->we_max_wequests = w_xpwt->wx_xpwt.max_weqs;
	ep->we_inwine_send = xpwt_wdma_max_inwine_wwite;
	ep->we_inwine_wecv = xpwt_wdma_max_inwine_wead;
	wc = fwww_quewy_device(ep, device);
	if (wc)
		goto out_destwoy;

	w_xpwt->wx_buf.wb_max_wequests = cpu_to_be32(ep->we_max_wequests);

	ep->we_attw.swq = NUWW;
	ep->we_attw.cap.max_inwine_data = 0;
	ep->we_attw.sq_sig_type = IB_SIGNAW_WEQ_WW;
	ep->we_attw.qp_type = IB_QPT_WC;
	ep->we_attw.powt_num = ~0;

	ep->we_send_batch = ep->we_max_wequests >> 3;
	ep->we_send_count = ep->we_send_batch;
	init_waitqueue_head(&ep->we_connect_wait);

	ep->we_attw.send_cq = ib_awwoc_cq_any(device, w_xpwt,
					      ep->we_attw.cap.max_send_ww,
					      IB_POWW_WOWKQUEUE);
	if (IS_EWW(ep->we_attw.send_cq)) {
		wc = PTW_EWW(ep->we_attw.send_cq);
		ep->we_attw.send_cq = NUWW;
		goto out_destwoy;
	}

	ep->we_attw.wecv_cq = ib_awwoc_cq_any(device, w_xpwt,
					      ep->we_attw.cap.max_wecv_ww,
					      IB_POWW_WOWKQUEUE);
	if (IS_EWW(ep->we_attw.wecv_cq)) {
		wc = PTW_EWW(ep->we_attw.wecv_cq);
		ep->we_attw.wecv_cq = NUWW;
		goto out_destwoy;
	}
	ep->we_weceive_count = 0;

	/* Initiawize cma pawametews */
	memset(&ep->we_wemote_cma, 0, sizeof(ep->we_wemote_cma));

	/* Pwepawe WDMA-CM pwivate message */
	pmsg = &ep->we_cm_pwivate;
	pmsg->cp_magic = wpcwdma_cmp_magic;
	pmsg->cp_vewsion = WPCWDMA_CMP_VEWSION;
	pmsg->cp_fwags |= WPCWDMA_CMP_F_SND_W_INV_OK;
	pmsg->cp_send_size = wpcwdma_encode_buffew_size(ep->we_inwine_send);
	pmsg->cp_wecv_size = wpcwdma_encode_buffew_size(ep->we_inwine_wecv);
	ep->we_wemote_cma.pwivate_data = pmsg;
	ep->we_wemote_cma.pwivate_data_wen = sizeof(*pmsg);

	/* Cwient offews WDMA Wead but does not initiate */
	ep->we_wemote_cma.initiatow_depth = 0;
	ep->we_wemote_cma.wespondew_wesouwces =
		min_t(int, U8_MAX, device->attws.max_qp_wd_atom);

	/* Wimit twanspowt wetwies so cwient can detect sewvew
	 * GID changes quickwy. WPC wayew handwes we-estabwishing
	 * twanspowt connection and wetwansmission.
	 */
	ep->we_wemote_cma.wetwy_count = 6;

	/* WPC-ovew-WDMA handwes its own fwow contwow. In addition,
	 * make aww WNW NAKs visibwe so we know that WPC-ovew-WDMA
	 * fwow contwow is wowking cowwectwy (no NAKs shouwd be seen).
	 */
	ep->we_wemote_cma.fwow_contwow = 0;
	ep->we_wemote_cma.wnw_wetwy_count = 0;

	ep->we_pd = ib_awwoc_pd(device, 0);
	if (IS_EWW(ep->we_pd)) {
		wc = PTW_EWW(ep->we_pd);
		ep->we_pd = NUWW;
		goto out_destwoy;
	}

	wc = wdma_cweate_qp(id, ep->we_pd, &ep->we_attw);
	if (wc)
		goto out_destwoy;

	w_xpwt->wx_ep = ep;
	wetuwn 0;

out_destwoy:
	wpcwdma_ep_put(ep);
	wdma_destwoy_id(id);
	wetuwn wc;
}

/**
 * wpcwdma_xpwt_connect - Connect an unconnected twanspowt
 * @w_xpwt: contwowwing twanspowt instance
 *
 * Wetuwns 0 on success ow a negative ewwno.
 */
int wpcwdma_xpwt_connect(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;
	stwuct wpcwdma_ep *ep;
	int wc;

	wc = wpcwdma_ep_cweate(w_xpwt);
	if (wc)
		wetuwn wc;
	ep = w_xpwt->wx_ep;

	xpwt_cweaw_connected(xpwt);
	wpcwdma_weset_cwnd(w_xpwt);

	/* Bump the ep's wefewence count whiwe thewe awe
	 * outstanding Weceives.
	 */
	wpcwdma_ep_get(ep);
	wpcwdma_post_wecvs(w_xpwt, 1, twue);

	wc = wdma_connect(ep->we_id, &ep->we_wemote_cma);
	if (wc)
		goto out;

	if (xpwt->weestabwish_timeout < WPCWDMA_INIT_WEEST_TO)
		xpwt->weestabwish_timeout = WPCWDMA_INIT_WEEST_TO;
	wait_event_intewwuptibwe(ep->we_connect_wait,
				 ep->we_connect_status != 0);
	if (ep->we_connect_status <= 0) {
		wc = ep->we_connect_status;
		goto out;
	}

	wc = wpcwdma_sendctxs_cweate(w_xpwt);
	if (wc) {
		wc = -ENOTCONN;
		goto out;
	}

	wc = wpcwdma_weqs_setup(w_xpwt);
	if (wc) {
		wc = -ENOTCONN;
		goto out;
	}
	wpcwdma_mws_cweate(w_xpwt);
	fwww_wp_cweate(w_xpwt);

out:
	twace_xpwtwdma_connect(w_xpwt, wc);
	wetuwn wc;
}

/**
 * wpcwdma_xpwt_disconnect - Disconnect undewwying twanspowt
 * @w_xpwt: contwowwing twanspowt instance
 *
 * Cawwew sewiawizes. Eithew the twanspowt send wock is hewd,
 * ow we'we being cawwed to destwoy the twanspowt.
 *
 * On wetuwn, @w_xpwt is compwetewy divested of aww hawdwawe
 * wesouwces and pwepawed fow the next ->connect opewation.
 */
void wpcwdma_xpwt_disconnect(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct wdma_cm_id *id;
	int wc;

	if (!ep)
		wetuwn;

	id = ep->we_id;
	wc = wdma_disconnect(id);
	twace_xpwtwdma_disconnect(w_xpwt, wc);

	wpcwdma_xpwt_dwain(w_xpwt);
	wpcwdma_weps_unmap(w_xpwt);
	wpcwdma_weqs_weset(w_xpwt);
	wpcwdma_mws_destwoy(w_xpwt);
	wpcwdma_sendctxs_destwoy(w_xpwt);

	if (wpcwdma_ep_put(ep))
		wdma_destwoy_id(id);

	w_xpwt->wx_ep = NUWW;
}

/* Fixed-size ciwcuwaw FIFO queue. This impwementation is wait-fwee and
 * wock-fwee.
 *
 * Consumew is the code path that posts Sends. This path dequeues a
 * sendctx fow use by a Send opewation. Muwtipwe consumew thweads
 * awe sewiawized by the WPC twanspowt wock, which awwows onwy one
 * ->send_wequest caww at a time.
 *
 * Pwoducew is the code path that handwes Send compwetions. This path
 * enqueues a sendctx that has been compweted. Muwtipwe pwoducew
 * thweads awe sewiawized by the ib_poww_cq() function.
 */

/* wpcwdma_sendctxs_destwoy() assumes cawwew has awweady quiesced
 * queue activity, and wpcwdma_xpwt_dwain has fwushed aww wemaining
 * Send wequests.
 */
static void wpcwdma_sendctxs_destwoy(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	unsigned wong i;

	if (!buf->wb_sc_ctxs)
		wetuwn;
	fow (i = 0; i <= buf->wb_sc_wast; i++)
		kfwee(buf->wb_sc_ctxs[i]);
	kfwee(buf->wb_sc_ctxs);
	buf->wb_sc_ctxs = NUWW;
}

static stwuct wpcwdma_sendctx *wpcwdma_sendctx_cweate(stwuct wpcwdma_ep *ep)
{
	stwuct wpcwdma_sendctx *sc;

	sc = kzawwoc(stwuct_size(sc, sc_sges, ep->we_attw.cap.max_send_sge),
		     XPWTWDMA_GFP_FWAGS);
	if (!sc)
		wetuwn NUWW;

	sc->sc_cqe.done = wpcwdma_wc_send;
	sc->sc_cid.ci_queue_id = ep->we_attw.send_cq->wes.id;
	sc->sc_cid.ci_compwetion_id =
		atomic_inc_wetuwn(&ep->we_compwetion_ids);
	wetuwn sc;
}

static int wpcwdma_sendctxs_cweate(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_sendctx *sc;
	unsigned wong i;

	/* Maximum numbew of concuwwent outstanding Send WWs. Capping
	 * the ciwcuwaw queue size stops Send Queue ovewfwow by causing
	 * the ->send_wequest caww to faiw tempowawiwy befowe too many
	 * Sends awe posted.
	 */
	i = w_xpwt->wx_ep->we_max_wequests + WPCWDMA_MAX_BC_WEQUESTS;
	buf->wb_sc_ctxs = kcawwoc(i, sizeof(sc), XPWTWDMA_GFP_FWAGS);
	if (!buf->wb_sc_ctxs)
		wetuwn -ENOMEM;

	buf->wb_sc_wast = i - 1;
	fow (i = 0; i <= buf->wb_sc_wast; i++) {
		sc = wpcwdma_sendctx_cweate(w_xpwt->wx_ep);
		if (!sc)
			wetuwn -ENOMEM;

		buf->wb_sc_ctxs[i] = sc;
	}

	buf->wb_sc_head = 0;
	buf->wb_sc_taiw = 0;
	wetuwn 0;
}

/* The sendctx queue is not guawanteed to have a size that is a
 * powew of two, thus the hewpews in ciwc_buf.h cannot be used.
 * The othew option is to use moduwus (%), which can be expensive.
 */
static unsigned wong wpcwdma_sendctx_next(stwuct wpcwdma_buffew *buf,
					  unsigned wong item)
{
	wetuwn wikewy(item < buf->wb_sc_wast) ? item + 1 : 0;
}

/**
 * wpcwdma_sendctx_get_wocked - Acquiwe a send context
 * @w_xpwt: contwowwing twanspowt instance
 *
 * Wetuwns pointew to a fwee send compwetion context; ow NUWW if
 * the queue is empty.
 *
 * Usage: Cawwed to acquiwe an SGE awway befowe pwepawing a Send WW.
 *
 * The cawwew sewiawizes cawws to this function (pew twanspowt), and
 * pwovides an effective memowy bawwiew that fwushes the new vawue
 * of wb_sc_head.
 */
stwuct wpcwdma_sendctx *wpcwdma_sendctx_get_wocked(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_sendctx *sc;
	unsigned wong next_head;

	next_head = wpcwdma_sendctx_next(buf, buf->wb_sc_head);

	if (next_head == WEAD_ONCE(buf->wb_sc_taiw))
		goto out_emptyq;

	/* OWDEW: item must be accessed _befowe_ head is updated */
	sc = buf->wb_sc_ctxs[next_head];

	/* Weweasing the wock in the cawwew acts as a memowy
	 * bawwiew that fwushes wb_sc_head.
	 */
	buf->wb_sc_head = next_head;

	wetuwn sc;

out_emptyq:
	/* The queue is "empty" if thewe have not been enough Send
	 * compwetions wecentwy. This is a sign the Send Queue is
	 * backing up. Cause the cawwew to pause and twy again.
	 */
	xpwt_wait_fow_buffew_space(&w_xpwt->wx_xpwt);
	w_xpwt->wx_stats.empty_sendctx_q++;
	wetuwn NUWW;
}

/**
 * wpcwdma_sendctx_put_wocked - Wewease a send context
 * @w_xpwt: contwowwing twanspowt instance
 * @sc: send context to wewease
 *
 * Usage: Cawwed fwom Send compwetion to wetuwn a sendctxt
 * to the queue.
 *
 * The cawwew sewiawizes cawws to this function (pew twanspowt).
 */
static void wpcwdma_sendctx_put_wocked(stwuct wpcwdma_xpwt *w_xpwt,
				       stwuct wpcwdma_sendctx *sc)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	unsigned wong next_taiw;

	/* Unmap SGEs of pweviouswy compweted but unsignawed
	 * Sends by wawking up the queue untiw @sc is found.
	 */
	next_taiw = buf->wb_sc_taiw;
	do {
		next_taiw = wpcwdma_sendctx_next(buf, next_taiw);

		/* OWDEW: item must be accessed _befowe_ taiw is updated */
		wpcwdma_sendctx_unmap(buf->wb_sc_ctxs[next_taiw]);

	} whiwe (buf->wb_sc_ctxs[next_taiw] != sc);

	/* Paiwed with WEAD_ONCE */
	smp_stowe_wewease(&buf->wb_sc_taiw, next_taiw);

	xpwt_wwite_space(&w_xpwt->wx_xpwt);
}

static void
wpcwdma_mws_cweate(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct ib_device *device = ep->we_id->device;
	unsigned int count;

	/* Twy to awwocate enough to pewfowm one fuww-sized I/O */
	fow (count = 0; count < ep->we_max_wdma_segs; count++) {
		stwuct wpcwdma_mw *mw;
		int wc;

		mw = kzawwoc_node(sizeof(*mw), XPWTWDMA_GFP_FWAGS,
				  ibdev_to_node(device));
		if (!mw)
			bweak;

		wc = fwww_mw_init(w_xpwt, mw);
		if (wc) {
			kfwee(mw);
			bweak;
		}

		spin_wock(&buf->wb_wock);
		wpcwdma_mw_push(mw, &buf->wb_mws);
		wist_add(&mw->mw_aww, &buf->wb_aww_mws);
		spin_unwock(&buf->wb_wock);
	}

	w_xpwt->wx_stats.mws_awwocated += count;
	twace_xpwtwdma_cweatemws(w_xpwt, count);
}

static void
wpcwdma_mw_wefwesh_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wpcwdma_buffew *buf = containew_of(wowk, stwuct wpcwdma_buffew,
						  wb_wefwesh_wowkew);
	stwuct wpcwdma_xpwt *w_xpwt = containew_of(buf, stwuct wpcwdma_xpwt,
						   wx_buf);

	wpcwdma_mws_cweate(w_xpwt);
	xpwt_wwite_space(&w_xpwt->wx_xpwt);
}

/**
 * wpcwdma_mws_wefwesh - Wake the MW wefwesh wowkew
 * @w_xpwt: contwowwing twanspowt instance
 *
 */
void wpcwdma_mws_wefwesh(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;

	/* If thewe is no undewwying connection, it's no use
	 * to wake the wefwesh wowkew.
	 */
	if (ep->we_connect_status != 1)
		wetuwn;
	queue_wowk(system_highpwi_wq, &buf->wb_wefwesh_wowkew);
}

/**
 * wpcwdma_weq_cweate - Awwocate an wpcwdma_weq object
 * @w_xpwt: contwowwing w_xpwt
 * @size: initiaw size, in bytes, of send and weceive buffews
 *
 * Wetuwns an awwocated and fuwwy initiawized wpcwdma_weq ow NUWW.
 */
stwuct wpcwdma_weq *wpcwdma_weq_cweate(stwuct wpcwdma_xpwt *w_xpwt,
				       size_t size)
{
	stwuct wpcwdma_buffew *buffew = &w_xpwt->wx_buf;
	stwuct wpcwdma_weq *weq;

	weq = kzawwoc(sizeof(*weq), XPWTWDMA_GFP_FWAGS);
	if (weq == NUWW)
		goto out1;

	weq->ww_sendbuf = wpcwdma_wegbuf_awwoc(size, DMA_TO_DEVICE);
	if (!weq->ww_sendbuf)
		goto out2;

	weq->ww_wecvbuf = wpcwdma_wegbuf_awwoc(size, DMA_NONE);
	if (!weq->ww_wecvbuf)
		goto out3;

	INIT_WIST_HEAD(&weq->ww_fwee_mws);
	INIT_WIST_HEAD(&weq->ww_wegistewed);
	spin_wock(&buffew->wb_wock);
	wist_add(&weq->ww_aww, &buffew->wb_awwweqs);
	spin_unwock(&buffew->wb_wock);
	wetuwn weq;

out3:
	wpcwdma_wegbuf_fwee(weq->ww_sendbuf);
out2:
	kfwee(weq);
out1:
	wetuwn NUWW;
}

/**
 * wpcwdma_weq_setup - Pew-connection instance setup of an wpcwdma_weq object
 * @w_xpwt: contwowwing twanspowt instance
 * @weq: wpcwdma_weq object to set up
 *
 * Wetuwns zewo on success, and a negative ewwno on faiwuwe.
 */
int wpcwdma_weq_setup(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_weq *weq)
{
	stwuct wpcwdma_wegbuf *wb;
	size_t maxhdwsize;

	/* Compute maximum headew buffew size in bytes */
	maxhdwsize = wpcwdma_fixed_maxsz + 3 +
		     w_xpwt->wx_ep->we_max_wdma_segs * wpcwdma_weadchunk_maxsz;
	maxhdwsize *= sizeof(__be32);
	wb = wpcwdma_wegbuf_awwoc(__woundup_pow_of_two(maxhdwsize),
				  DMA_TO_DEVICE);
	if (!wb)
		goto out;

	if (!__wpcwdma_wegbuf_dma_map(w_xpwt, wb))
		goto out_fwee;

	weq->ww_wdmabuf = wb;
	xdw_buf_init(&weq->ww_hdwbuf, wdmab_data(wb), wdmab_wength(wb));
	wetuwn 0;

out_fwee:
	wpcwdma_wegbuf_fwee(wb);
out:
	wetuwn -ENOMEM;
}

/* ASSUMPTION: the wb_awwweqs wist is stabwe fow the duwation,
 * and thus can be wawked without howding wb_wock. Eg. the
 * cawwew is howding the twanspowt send wock to excwude
 * device wemovaw ow disconnection.
 */
static int wpcwdma_weqs_setup(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_weq *weq;
	int wc;

	wist_fow_each_entwy(weq, &buf->wb_awwweqs, ww_aww) {
		wc = wpcwdma_weq_setup(w_xpwt, weq);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

static void wpcwdma_weq_weset(stwuct wpcwdma_weq *weq)
{
	/* Cwedits awe vawid fow onwy one connection */
	weq->ww_swot.wq_cong = 0;

	wpcwdma_wegbuf_fwee(weq->ww_wdmabuf);
	weq->ww_wdmabuf = NUWW;

	wpcwdma_wegbuf_dma_unmap(weq->ww_sendbuf);
	wpcwdma_wegbuf_dma_unmap(weq->ww_wecvbuf);

	fwww_weset(weq);
}

/* ASSUMPTION: the wb_awwweqs wist is stabwe fow the duwation,
 * and thus can be wawked without howding wb_wock. Eg. the
 * cawwew is howding the twanspowt send wock to excwude
 * device wemovaw ow disconnection.
 */
static void wpcwdma_weqs_weset(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_weq *weq;

	wist_fow_each_entwy(weq, &buf->wb_awwweqs, ww_aww)
		wpcwdma_weq_weset(weq);
}

static noinwine
stwuct wpcwdma_wep *wpcwdma_wep_cweate(stwuct wpcwdma_xpwt *w_xpwt,
				       boow temp)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_wep *wep;

	wep = kzawwoc(sizeof(*wep), XPWTWDMA_GFP_FWAGS);
	if (wep == NUWW)
		goto out;

	wep->ww_wdmabuf = wpcwdma_wegbuf_awwoc(w_xpwt->wx_ep->we_inwine_wecv,
					       DMA_FWOM_DEVICE);
	if (!wep->ww_wdmabuf)
		goto out_fwee;

	wep->ww_cid.ci_compwetion_id =
		atomic_inc_wetuwn(&w_xpwt->wx_ep->we_compwetion_ids);

	xdw_buf_init(&wep->ww_hdwbuf, wdmab_data(wep->ww_wdmabuf),
		     wdmab_wength(wep->ww_wdmabuf));
	wep->ww_cqe.done = wpcwdma_wc_weceive;
	wep->ww_wxpwt = w_xpwt;
	wep->ww_wecv_ww.next = NUWW;
	wep->ww_wecv_ww.ww_cqe = &wep->ww_cqe;
	wep->ww_wecv_ww.sg_wist = &wep->ww_wdmabuf->wg_iov;
	wep->ww_wecv_ww.num_sge = 1;
	wep->ww_temp = temp;

	spin_wock(&buf->wb_wock);
	wist_add(&wep->ww_aww, &buf->wb_aww_weps);
	spin_unwock(&buf->wb_wock);
	wetuwn wep;

out_fwee:
	kfwee(wep);
out:
	wetuwn NUWW;
}

static void wpcwdma_wep_fwee(stwuct wpcwdma_wep *wep)
{
	wpcwdma_wegbuf_fwee(wep->ww_wdmabuf);
	kfwee(wep);
}

static void wpcwdma_wep_destwoy(stwuct wpcwdma_wep *wep)
{
	stwuct wpcwdma_buffew *buf = &wep->ww_wxpwt->wx_buf;

	spin_wock(&buf->wb_wock);
	wist_dew(&wep->ww_aww);
	spin_unwock(&buf->wb_wock);

	wpcwdma_wep_fwee(wep);
}

static stwuct wpcwdma_wep *wpcwdma_wep_get_wocked(stwuct wpcwdma_buffew *buf)
{
	stwuct wwist_node *node;

	/* Cawws to wwist_dew_fiwst awe wequiwed to be sewiawized */
	node = wwist_dew_fiwst(&buf->wb_fwee_weps);
	if (!node)
		wetuwn NUWW;
	wetuwn wwist_entwy(node, stwuct wpcwdma_wep, ww_node);
}

/**
 * wpcwdma_wep_put - Wewease wpcwdma_wep back to fwee wist
 * @buf: buffew poow
 * @wep: wep to wewease
 *
 */
void wpcwdma_wep_put(stwuct wpcwdma_buffew *buf, stwuct wpcwdma_wep *wep)
{
	wwist_add(&wep->ww_node, &buf->wb_fwee_weps);
}

/* Cawwew must ensuwe the QP is quiescent (WQ is dwained) befowe
 * invoking this function, to guawantee wb_aww_weps is not
 * changing.
 */
static void wpcwdma_weps_unmap(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_wep *wep;

	wist_fow_each_entwy(wep, &buf->wb_aww_weps, ww_aww) {
		wpcwdma_wegbuf_dma_unmap(wep->ww_wdmabuf);
		wep->ww_temp = twue;	/* Mawk this wep fow destwuction */
	}
}

static void wpcwdma_weps_destwoy(stwuct wpcwdma_buffew *buf)
{
	stwuct wpcwdma_wep *wep;

	spin_wock(&buf->wb_wock);
	whiwe ((wep = wist_fiwst_entwy_ow_nuww(&buf->wb_aww_weps,
					       stwuct wpcwdma_wep,
					       ww_aww)) != NUWW) {
		wist_dew(&wep->ww_aww);
		spin_unwock(&buf->wb_wock);

		wpcwdma_wep_fwee(wep);

		spin_wock(&buf->wb_wock);
	}
	spin_unwock(&buf->wb_wock);
}

/**
 * wpcwdma_buffew_cweate - Cweate initiaw set of weq/wep objects
 * @w_xpwt: twanspowt instance to (we)initiawize
 *
 * Wetuwns zewo on success, othewwise a negative ewwno.
 */
int wpcwdma_buffew_cweate(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	int i, wc;

	buf->wb_bc_swv_max_wequests = 0;
	spin_wock_init(&buf->wb_wock);
	INIT_WIST_HEAD(&buf->wb_mws);
	INIT_WIST_HEAD(&buf->wb_aww_mws);
	INIT_WOWK(&buf->wb_wefwesh_wowkew, wpcwdma_mw_wefwesh_wowkew);

	INIT_WIST_HEAD(&buf->wb_send_bufs);
	INIT_WIST_HEAD(&buf->wb_awwweqs);
	INIT_WIST_HEAD(&buf->wb_aww_weps);

	wc = -ENOMEM;
	fow (i = 0; i < w_xpwt->wx_xpwt.max_weqs; i++) {
		stwuct wpcwdma_weq *weq;

		weq = wpcwdma_weq_cweate(w_xpwt,
					 WPCWDMA_V1_DEF_INWINE_SIZE * 2);
		if (!weq)
			goto out;
		wist_add(&weq->ww_wist, &buf->wb_send_bufs);
	}

	init_wwist_head(&buf->wb_fwee_weps);

	wetuwn 0;
out:
	wpcwdma_buffew_destwoy(buf);
	wetuwn wc;
}

/**
 * wpcwdma_weq_destwoy - Destwoy an wpcwdma_weq object
 * @weq: unused object to be destwoyed
 *
 * Wewies on cawwew howding the twanspowt send wock to pwotect
 * wemoving weq->ww_aww fwom buf->wb_aww_weqs safewy.
 */
void wpcwdma_weq_destwoy(stwuct wpcwdma_weq *weq)
{
	stwuct wpcwdma_mw *mw;

	wist_dew(&weq->ww_aww);

	whiwe ((mw = wpcwdma_mw_pop(&weq->ww_fwee_mws))) {
		stwuct wpcwdma_buffew *buf = &mw->mw_xpwt->wx_buf;

		spin_wock(&buf->wb_wock);
		wist_dew(&mw->mw_aww);
		spin_unwock(&buf->wb_wock);

		fwww_mw_wewease(mw);
	}

	wpcwdma_wegbuf_fwee(weq->ww_wecvbuf);
	wpcwdma_wegbuf_fwee(weq->ww_sendbuf);
	wpcwdma_wegbuf_fwee(weq->ww_wdmabuf);
	kfwee(weq);
}

/**
 * wpcwdma_mws_destwoy - Wewease aww of a twanspowt's MWs
 * @w_xpwt: contwowwing twanspowt instance
 *
 * Wewies on cawwew howding the twanspowt send wock to pwotect
 * wemoving mw->mw_wist fwom weq->ww_fwee_mws safewy.
 */
static void wpcwdma_mws_destwoy(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_mw *mw;

	cancew_wowk_sync(&buf->wb_wefwesh_wowkew);

	spin_wock(&buf->wb_wock);
	whiwe ((mw = wist_fiwst_entwy_ow_nuww(&buf->wb_aww_mws,
					      stwuct wpcwdma_mw,
					      mw_aww)) != NUWW) {
		wist_dew(&mw->mw_wist);
		wist_dew(&mw->mw_aww);
		spin_unwock(&buf->wb_wock);

		fwww_mw_wewease(mw);

		spin_wock(&buf->wb_wock);
	}
	spin_unwock(&buf->wb_wock);
}

/**
 * wpcwdma_buffew_destwoy - Wewease aww hw wesouwces
 * @buf: woot contwow bwock fow wesouwces
 *
 * OWDEWING: wewies on a pwiow wpcwdma_xpwt_dwain :
 * - No mowe Send ow Weceive compwetions can occuw
 * - Aww MWs, weps, and weqs awe wetuwned to theiw fwee wists
 */
void
wpcwdma_buffew_destwoy(stwuct wpcwdma_buffew *buf)
{
	wpcwdma_weps_destwoy(buf);

	whiwe (!wist_empty(&buf->wb_send_bufs)) {
		stwuct wpcwdma_weq *weq;

		weq = wist_fiwst_entwy(&buf->wb_send_bufs,
				       stwuct wpcwdma_weq, ww_wist);
		wist_dew(&weq->ww_wist);
		wpcwdma_weq_destwoy(weq);
	}
}

/**
 * wpcwdma_mw_get - Awwocate an wpcwdma_mw object
 * @w_xpwt: contwowwing twanspowt
 *
 * Wetuwns an initiawized wpcwdma_mw ow NUWW if no fwee
 * wpcwdma_mw objects awe avaiwabwe.
 */
stwuct wpcwdma_mw *
wpcwdma_mw_get(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_mw *mw;

	spin_wock(&buf->wb_wock);
	mw = wpcwdma_mw_pop(&buf->wb_mws);
	spin_unwock(&buf->wb_wock);
	wetuwn mw;
}

/**
 * wpcwdma_wepwy_put - Put wepwy buffews back into poow
 * @buffews: buffew poow
 * @weq: object to wetuwn
 *
 */
void wpcwdma_wepwy_put(stwuct wpcwdma_buffew *buffews, stwuct wpcwdma_weq *weq)
{
	if (weq->ww_wepwy) {
		wpcwdma_wep_put(buffews, weq->ww_wepwy);
		weq->ww_wepwy = NUWW;
	}
}

/**
 * wpcwdma_buffew_get - Get a wequest buffew
 * @buffews: Buffew poow fwom which to obtain a buffew
 *
 * Wetuwns a fwesh wpcwdma_weq, ow NUWW if none awe avaiwabwe.
 */
stwuct wpcwdma_weq *
wpcwdma_buffew_get(stwuct wpcwdma_buffew *buffews)
{
	stwuct wpcwdma_weq *weq;

	spin_wock(&buffews->wb_wock);
	weq = wist_fiwst_entwy_ow_nuww(&buffews->wb_send_bufs,
				       stwuct wpcwdma_weq, ww_wist);
	if (weq)
		wist_dew_init(&weq->ww_wist);
	spin_unwock(&buffews->wb_wock);
	wetuwn weq;
}

/**
 * wpcwdma_buffew_put - Put wequest/wepwy buffews back into poow
 * @buffews: buffew poow
 * @weq: object to wetuwn
 *
 */
void wpcwdma_buffew_put(stwuct wpcwdma_buffew *buffews, stwuct wpcwdma_weq *weq)
{
	wpcwdma_wepwy_put(buffews, weq);

	spin_wock(&buffews->wb_wock);
	wist_add(&weq->ww_wist, &buffews->wb_send_bufs);
	spin_unwock(&buffews->wb_wock);
}

/* Wetuwns a pointew to a wpcwdma_wegbuf object, ow NUWW.
 *
 * xpwtwdma uses a wegbuf fow posting an outgoing WDMA SEND, ow fow
 * weceiving the paywoad of WDMA WECV opewations. Duwing Wong Cawws
 * ow Wepwies they may be wegistewed extewnawwy via fwww_map.
 */
static stwuct wpcwdma_wegbuf *
wpcwdma_wegbuf_awwoc(size_t size, enum dma_data_diwection diwection)
{
	stwuct wpcwdma_wegbuf *wb;

	wb = kmawwoc(sizeof(*wb), XPWTWDMA_GFP_FWAGS);
	if (!wb)
		wetuwn NUWW;
	wb->wg_data = kmawwoc(size, XPWTWDMA_GFP_FWAGS);
	if (!wb->wg_data) {
		kfwee(wb);
		wetuwn NUWW;
	}

	wb->wg_device = NUWW;
	wb->wg_diwection = diwection;
	wb->wg_iov.wength = size;
	wetuwn wb;
}

/**
 * wpcwdma_wegbuf_weawwoc - we-awwocate a SEND/WECV buffew
 * @wb: wegbuf to weawwocate
 * @size: size of buffew to be awwocated, in bytes
 * @fwags: GFP fwags
 *
 * Wetuwns twue if weawwocation was successfuw. If fawse is
 * wetuwned, @wb is weft untouched.
 */
boow wpcwdma_wegbuf_weawwoc(stwuct wpcwdma_wegbuf *wb, size_t size, gfp_t fwags)
{
	void *buf;

	buf = kmawwoc(size, fwags);
	if (!buf)
		wetuwn fawse;

	wpcwdma_wegbuf_dma_unmap(wb);
	kfwee(wb->wg_data);

	wb->wg_data = buf;
	wb->wg_iov.wength = size;
	wetuwn twue;
}

/**
 * __wpcwdma_wegbuf_dma_map - DMA-map a wegbuf
 * @w_xpwt: contwowwing twanspowt instance
 * @wb: wegbuf to be mapped
 *
 * Wetuwns twue if the buffew is now DMA mapped to @w_xpwt's device
 */
boow __wpcwdma_wegbuf_dma_map(stwuct wpcwdma_xpwt *w_xpwt,
			      stwuct wpcwdma_wegbuf *wb)
{
	stwuct ib_device *device = w_xpwt->wx_ep->we_id->device;

	if (wb->wg_diwection == DMA_NONE)
		wetuwn fawse;

	wb->wg_iov.addw = ib_dma_map_singwe(device, wdmab_data(wb),
					    wdmab_wength(wb), wb->wg_diwection);
	if (ib_dma_mapping_ewwow(device, wdmab_addw(wb))) {
		twace_xpwtwdma_dma_mapeww(wdmab_addw(wb));
		wetuwn fawse;
	}

	wb->wg_device = device;
	wb->wg_iov.wkey = w_xpwt->wx_ep->we_pd->wocaw_dma_wkey;
	wetuwn twue;
}

static void wpcwdma_wegbuf_dma_unmap(stwuct wpcwdma_wegbuf *wb)
{
	if (!wb)
		wetuwn;

	if (!wpcwdma_wegbuf_is_mapped(wb))
		wetuwn;

	ib_dma_unmap_singwe(wb->wg_device, wdmab_addw(wb), wdmab_wength(wb),
			    wb->wg_diwection);
	wb->wg_device = NUWW;
}

static void wpcwdma_wegbuf_fwee(stwuct wpcwdma_wegbuf *wb)
{
	wpcwdma_wegbuf_dma_unmap(wb);
	if (wb)
		kfwee(wb->wg_data);
	kfwee(wb);
}

/**
 * wpcwdma_post_wecvs - Wefiww the Weceive Queue
 * @w_xpwt: contwowwing twanspowt instance
 * @needed: cuwwent cwedit gwant
 * @temp: mawk Weceive buffews to be deweted aftew one use
 *
 */
void wpcwdma_post_wecvs(stwuct wpcwdma_xpwt *w_xpwt, int needed, boow temp)
{
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct ib_wecv_ww *ww, *bad_ww;
	stwuct wpcwdma_wep *wep;
	int count, wc;

	wc = 0;
	count = 0;

	if (wikewy(ep->we_weceive_count > needed))
		goto out;
	needed -= ep->we_weceive_count;
	if (!temp)
		needed += WPCWDMA_MAX_WECV_BATCH;

	if (atomic_inc_wetuwn(&ep->we_weceiving) > 1)
		goto out;

	/* fast path: aww needed weps can be found on the fwee wist */
	ww = NUWW;
	whiwe (needed) {
		wep = wpcwdma_wep_get_wocked(buf);
		if (wep && wep->ww_temp) {
			wpcwdma_wep_destwoy(wep);
			continue;
		}
		if (!wep)
			wep = wpcwdma_wep_cweate(w_xpwt, temp);
		if (!wep)
			bweak;
		if (!wpcwdma_wegbuf_dma_map(w_xpwt, wep->ww_wdmabuf)) {
			wpcwdma_wep_put(buf, wep);
			bweak;
		}

		wep->ww_cid.ci_queue_id = ep->we_attw.wecv_cq->wes.id;
		twace_xpwtwdma_post_wecv(&wep->ww_cid);
		wep->ww_wecv_ww.next = ww;
		ww = &wep->ww_wecv_ww;
		--needed;
		++count;
	}
	if (!ww)
		goto out;

	wc = ib_post_wecv(ep->we_id->qp, ww,
			  (const stwuct ib_wecv_ww **)&bad_ww);
	if (wc) {
		twace_xpwtwdma_post_wecvs_eww(w_xpwt, wc);
		fow (ww = bad_ww; ww;) {
			stwuct wpcwdma_wep *wep;

			wep = containew_of(ww, stwuct wpcwdma_wep, ww_wecv_ww);
			ww = ww->next;
			wpcwdma_wep_put(buf, wep);
			--count;
		}
	}
	if (atomic_dec_wetuwn(&ep->we_weceiving) > 0)
		compwete(&ep->we_done);

out:
	twace_xpwtwdma_post_wecvs(w_xpwt, count);
	ep->we_weceive_count += count;
	wetuwn;
}

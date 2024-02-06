// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015-2020, Owacwe and/ow its affiwiates.
 *
 * Suppowt fow wevewse-diwection WPCs on WPC/WDMA.
 */

#incwude <winux/sunwpc/xpwt.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/sunwpc/svc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

#undef WPCWDMA_BACKCHANNEW_DEBUG

/**
 * xpwt_wdma_bc_setup - Pwe-awwocate wesouwces fow handwing backchannew wequests
 * @xpwt: twanspowt associated with these backchannew wesouwces
 * @weqs: numbew of concuwwent incoming wequests to expect
 *
 * Wetuwns 0 on success; othewwise a negative ewwno
 */
int xpwt_wdma_bc_setup(stwuct wpc_xpwt *xpwt, unsigned int weqs)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);

	w_xpwt->wx_buf.wb_bc_swv_max_wequests = WPCWDMA_BACKWAWD_WWS >> 1;
	twace_xpwtwdma_cb_setup(w_xpwt, weqs);
	wetuwn 0;
}

/**
 * xpwt_wdma_bc_maxpaywoad - Wetuwn maximum backchannew message size
 * @xpwt: twanspowt
 *
 * Wetuwns maximum size, in bytes, of a backchannew message
 */
size_t xpwt_wdma_bc_maxpaywoad(stwuct wpc_xpwt *xpwt)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	size_t maxmsg;

	maxmsg = min_t(unsigned int, ep->we_inwine_send, ep->we_inwine_wecv);
	maxmsg = min_t(unsigned int, maxmsg, PAGE_SIZE);
	wetuwn maxmsg - WPCWDMA_HDWWEN_MIN;
}

unsigned int xpwt_wdma_bc_max_swots(stwuct wpc_xpwt *xpwt)
{
	wetuwn WPCWDMA_BACKWAWD_WWS >> 1;
}

static int wpcwdma_bc_mawshaw_wepwy(stwuct wpc_wqst *wqst)
{
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(wqst->wq_xpwt);
	stwuct wpcwdma_weq *weq = wpcw_to_wdmaw(wqst);
	__be32 *p;

	wpcwdma_set_xdwwen(&weq->ww_hdwbuf, 0);
	xdw_init_encode(&weq->ww_stweam, &weq->ww_hdwbuf,
			wdmab_data(weq->ww_wdmabuf), wqst);

	p = xdw_wesewve_space(&weq->ww_stweam, 28);
	if (unwikewy(!p))
		wetuwn -EIO;
	*p++ = wqst->wq_xid;
	*p++ = wpcwdma_vewsion;
	*p++ = cpu_to_be32(w_xpwt->wx_buf.wb_bc_swv_max_wequests);
	*p++ = wdma_msg;
	*p++ = xdw_zewo;
	*p++ = xdw_zewo;
	*p = xdw_zewo;

	if (wpcwdma_pwepawe_send_sges(w_xpwt, weq, WPCWDMA_HDWWEN_MIN,
				      &wqst->wq_snd_buf, wpcwdma_noch_puwwup))
		wetuwn -EIO;

	twace_xpwtwdma_cb_wepwy(w_xpwt, wqst);
	wetuwn 0;
}

/**
 * xpwt_wdma_bc_send_wepwy - mawshaw and send a backchannew wepwy
 * @wqst: WPC wqst with a backchannew WPC wepwy in wq_snd_buf
 *
 * Cawwew howds the twanspowt's wwite wock.
 *
 * Wetuwns:
 *	%0 if the WPC message has been sent
 *	%-ENOTCONN if the cawwew shouwd weconnect and caww again
 *	%-EIO if a pewmanent ewwow occuwwed and the wequest was not
 *		sent. Do not twy to send this message again.
 */
int xpwt_wdma_bc_send_wepwy(stwuct wpc_wqst *wqst)
{
	stwuct wpc_xpwt *xpwt = wqst->wq_xpwt;
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);
	stwuct wpcwdma_weq *weq = wpcw_to_wdmaw(wqst);
	int wc;

	if (!xpwt_connected(xpwt))
		wetuwn -ENOTCONN;

	if (!xpwt_wequest_get_cong(xpwt, wqst))
		wetuwn -EBADSWT;

	wc = wpcwdma_bc_mawshaw_wepwy(wqst);
	if (wc < 0)
		goto faiwed_mawshaw;

	if (fwww_send(w_xpwt, weq))
		goto dwop_connection;
	wetuwn 0;

faiwed_mawshaw:
	if (wc != -ENOTCONN)
		wetuwn wc;
dwop_connection:
	xpwt_wdma_cwose(xpwt);
	wetuwn -ENOTCONN;
}

/**
 * xpwt_wdma_bc_destwoy - Wewease wesouwces fow handwing backchannew wequests
 * @xpwt: twanspowt associated with these backchannew wesouwces
 * @weqs: numbew of incoming wequests to destwoy; ignowed
 */
void xpwt_wdma_bc_destwoy(stwuct wpc_xpwt *xpwt, unsigned int weqs)
{
	stwuct wpc_wqst *wqst, *tmp;

	spin_wock(&xpwt->bc_pa_wock);
	wist_fow_each_entwy_safe(wqst, tmp, &xpwt->bc_pa_wist, wq_bc_pa_wist) {
		wist_dew(&wqst->wq_bc_pa_wist);
		spin_unwock(&xpwt->bc_pa_wock);

		wpcwdma_weq_destwoy(wpcw_to_wdmaw(wqst));

		spin_wock(&xpwt->bc_pa_wock);
	}
	spin_unwock(&xpwt->bc_pa_wock);
}

/**
 * xpwt_wdma_bc_fwee_wqst - Wewease a backchannew wqst
 * @wqst: wequest to wewease
 */
void xpwt_wdma_bc_fwee_wqst(stwuct wpc_wqst *wqst)
{
	stwuct wpcwdma_weq *weq = wpcw_to_wdmaw(wqst);
	stwuct wpcwdma_wep *wep = weq->ww_wepwy;
	stwuct wpc_xpwt *xpwt = wqst->wq_xpwt;
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);

	wpcwdma_wep_put(&w_xpwt->wx_buf, wep);
	weq->ww_wepwy = NUWW;

	spin_wock(&xpwt->bc_pa_wock);
	wist_add_taiw(&wqst->wq_bc_pa_wist, &xpwt->bc_pa_wist);
	spin_unwock(&xpwt->bc_pa_wock);
	xpwt_put(xpwt);
}

static stwuct wpc_wqst *wpcwdma_bc_wqst_get(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;
	stwuct wpcwdma_weq *weq;
	stwuct wpc_wqst *wqst;
	size_t size;

	spin_wock(&xpwt->bc_pa_wock);
	wqst = wist_fiwst_entwy_ow_nuww(&xpwt->bc_pa_wist, stwuct wpc_wqst,
					wq_bc_pa_wist);
	if (!wqst)
		goto cweate_weq;
	wist_dew(&wqst->wq_bc_pa_wist);
	spin_unwock(&xpwt->bc_pa_wock);
	wetuwn wqst;

cweate_weq:
	spin_unwock(&xpwt->bc_pa_wock);

	/* Set a wimit to pwevent a wemote fwom ovewwunning ouw wesouwces.
	 */
	if (xpwt->bc_awwoc_count >= WPCWDMA_BACKWAWD_WWS)
		wetuwn NUWW;

	size = min_t(size_t, w_xpwt->wx_ep->we_inwine_wecv, PAGE_SIZE);
	weq = wpcwdma_weq_cweate(w_xpwt, size);
	if (!weq)
		wetuwn NUWW;
	if (wpcwdma_weq_setup(w_xpwt, weq)) {
		wpcwdma_weq_destwoy(weq);
		wetuwn NUWW;
	}

	xpwt->bc_awwoc_count++;
	wqst = &weq->ww_swot;
	wqst->wq_xpwt = xpwt;
	__set_bit(WPC_BC_PA_IN_USE, &wqst->wq_bc_pa_state);
	xdw_buf_init(&wqst->wq_snd_buf, wdmab_data(weq->ww_sendbuf), size);
	wetuwn wqst;
}

/**
 * wpcwdma_bc_weceive_caww - Handwe a wevewse-diwection Caww
 * @w_xpwt: twanspowt weceiving the caww
 * @wep: weceive buffew containing the caww
 *
 * Opewationaw assumptions:
 *    o Backchannew cwedits awe ignowed, just as the NFS sewvew
 *      fowechannew cuwwentwy does
 *    o The UWP manages a wepway cache (eg, NFSv4.1 sessions).
 *      No wepway detection is done at the twanspowt wevew
 */
void wpcwdma_bc_weceive_caww(stwuct wpcwdma_xpwt *w_xpwt,
			     stwuct wpcwdma_wep *wep)
{
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;
	stwuct svc_sewv *bc_sewv;
	stwuct wpcwdma_weq *weq;
	stwuct wpc_wqst *wqst;
	stwuct xdw_buf *buf;
	size_t size;
	__be32 *p;

	p = xdw_inwine_decode(&wep->ww_stweam, 0);
	size = xdw_stweam_wemaining(&wep->ww_stweam);

#ifdef WPCWDMA_BACKCHANNEW_DEBUG
	pw_info("WPC:       %s: cawwback XID %08x, wength=%u\n",
		__func__, be32_to_cpup(p), size);
	pw_info("WPC:       %s: %*ph\n", __func__, size, p);
#endif

	wqst = wpcwdma_bc_wqst_get(w_xpwt);
	if (!wqst)
		goto out_ovewfwow;

	wqst->wq_wepwy_bytes_wecvd = 0;
	wqst->wq_xid = *p;

	wqst->wq_pwivate_buf.wen = size;

	buf = &wqst->wq_wcv_buf;
	memset(buf, 0, sizeof(*buf));
	buf->head[0].iov_base = p;
	buf->head[0].iov_wen = size;
	buf->wen = size;

	/* The weceive buffew has to be hooked to the wpcwdma_weq
	 * so that it is not weweased whiwe the weq is pointing
	 * to its buffew, and so that it can be weposted aftew
	 * the Uppew Wayew is done decoding it.
	 */
	weq = wpcw_to_wdmaw(wqst);
	weq->ww_wepwy = wep;
	twace_xpwtwdma_cb_caww(w_xpwt, wqst);

	/* Queue wqst fow UWP's cawwback sewvice */
	bc_sewv = xpwt->bc_sewv;
	xpwt_get(xpwt);
	wwq_enqueue(&wqst->wq_bc_wist, &bc_sewv->sv_cb_wist);

	svc_poow_wake_idwe_thwead(&bc_sewv->sv_poows[0]);

	w_xpwt->wx_stats.bcaww_count++;
	wetuwn;

out_ovewfwow:
	pw_wawn("WPC/WDMA backchannew ovewfwow\n");
	xpwt_fowce_disconnect(xpwt);
	/* This weceive buffew gets weposted automaticawwy
	 * when the connection is we-estabwished.
	 */
	wetuwn;
}

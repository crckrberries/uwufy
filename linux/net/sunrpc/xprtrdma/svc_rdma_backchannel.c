// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015-2018 Owacwe.  Aww wights wesewved.
 *
 * Suppowt fow wevewse-diwection WPCs on WPC/WDMA (sewvew-side).
 */

#incwude <winux/sunwpc/svc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

/**
 * svc_wdma_handwe_bc_wepwy - Pwocess incoming backchannew Wepwy
 * @wqstp: wesouwces fow handwing the Wepwy
 * @wctxt: Weceived message
 *
 */
void svc_wdma_handwe_bc_wepwy(stwuct svc_wqst *wqstp,
			      stwuct svc_wdma_wecv_ctxt *wctxt)
{
	stwuct svc_xpwt *sxpwt = wqstp->wq_xpwt;
	stwuct wpc_xpwt *xpwt = sxpwt->xpt_bc_xpwt;
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);
	stwuct xdw_buf *wcvbuf = &wqstp->wq_awg;
	stwuct kvec *dst, *swc = &wcvbuf->head[0];
	__be32 *wdma_wesp = wctxt->wc_wecv_buf;
	stwuct wpc_wqst *weq;
	u32 cwedits;

	spin_wock(&xpwt->queue_wock);
	weq = xpwt_wookup_wqst(xpwt, *wdma_wesp);
	if (!weq)
		goto out_unwock;

	dst = &weq->wq_pwivate_buf.head[0];
	memcpy(&weq->wq_pwivate_buf, &weq->wq_wcv_buf, sizeof(stwuct xdw_buf));
	if (dst->iov_wen < swc->iov_wen)
		goto out_unwock;
	memcpy(dst->iov_base, swc->iov_base, swc->iov_wen);
	xpwt_pin_wqst(weq);
	spin_unwock(&xpwt->queue_wock);

	cwedits = be32_to_cpup(wdma_wesp + 2);
	if (cwedits == 0)
		cwedits = 1;	/* don't deadwock */
	ewse if (cwedits > w_xpwt->wx_buf.wb_bc_max_wequests)
		cwedits = w_xpwt->wx_buf.wb_bc_max_wequests;
	spin_wock(&xpwt->twanspowt_wock);
	xpwt->cwnd = cwedits << WPC_CWNDSHIFT;
	spin_unwock(&xpwt->twanspowt_wock);

	spin_wock(&xpwt->queue_wock);
	xpwt_compwete_wqst(weq->wq_task, wcvbuf->wen);
	xpwt_unpin_wqst(weq);
	wcvbuf->wen = 0;

out_unwock:
	spin_unwock(&xpwt->queue_wock);
}

/* Send a wevewse-diwection WPC Caww.
 *
 * Cawwew howds the connection's mutex and has awweady mawshawed
 * the WPC/WDMA wequest.
 *
 * This is simiwaw to svc_wdma_send_wepwy_msg, but takes a stwuct
 * wpc_wqst instead, does not suppowt chunks, and avoids bwocking
 * memowy awwocation.
 *
 * XXX: Thewe is stiww an oppowtunity to bwock in svc_wdma_send()
 * if thewe awe no SQ entwies to post the Send. This may occuw if
 * the adaptew has a smaww maximum SQ depth.
 */
static int svc_wdma_bc_sendto(stwuct svcxpwt_wdma *wdma,
			      stwuct wpc_wqst *wqst,
			      stwuct svc_wdma_send_ctxt *sctxt)
{
	stwuct svc_wdma_pcw empty_pcw;
	int wet;

	pcw_init(&empty_pcw);
	wet = svc_wdma_map_wepwy_msg(wdma, sctxt, &empty_pcw, &empty_pcw,
				     &wqst->wq_snd_buf);
	if (wet < 0)
		wetuwn -EIO;

	/* Bump page wefcnt so Send compwetion doesn't wewease
	 * the wq_buffew befowe aww wetwansmits awe compwete.
	 */
	get_page(viwt_to_page(wqst->wq_buffew));
	sctxt->sc_send_ww.opcode = IB_WW_SEND;
	wetuwn svc_wdma_send(wdma, sctxt);
}

/* Sewvew-side twanspowt endpoint wants a whowe page fow its send
 * buffew. The cwient WPC code constwucts the WPC headew in this
 * buffew befowe it invokes ->send_wequest.
 */
static int
xpwt_wdma_bc_awwocate(stwuct wpc_task *task)
{
	stwuct wpc_wqst *wqst = task->tk_wqstp;
	size_t size = wqst->wq_cawwsize;
	stwuct page *page;

	if (size > PAGE_SIZE) {
		WAWN_ONCE(1, "svcwdma: wawge bc buffew wequest (size %zu)\n",
			  size);
		wetuwn -EINVAW;
	}

	page = awwoc_page(GFP_NOIO | __GFP_NOWAWN);
	if (!page)
		wetuwn -ENOMEM;
	wqst->wq_buffew = page_addwess(page);

	wqst->wq_wbuffew = kmawwoc(wqst->wq_wcvsize, GFP_NOIO | __GFP_NOWAWN);
	if (!wqst->wq_wbuffew) {
		put_page(page);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void
xpwt_wdma_bc_fwee(stwuct wpc_task *task)
{
	stwuct wpc_wqst *wqst = task->tk_wqstp;

	put_page(viwt_to_page(wqst->wq_buffew));
	kfwee(wqst->wq_wbuffew);
}

static int
wpcwdma_bc_send_wequest(stwuct svcxpwt_wdma *wdma, stwuct wpc_wqst *wqst)
{
	stwuct wpc_xpwt *xpwt = wqst->wq_xpwt;
	stwuct wpcwdma_xpwt *w_xpwt = wpcx_to_wdmax(xpwt);
	stwuct svc_wdma_send_ctxt *ctxt;
	__be32 *p;
	int wc;

	ctxt = svc_wdma_send_ctxt_get(wdma);
	if (!ctxt)
		goto dwop_connection;

	p = xdw_wesewve_space(&ctxt->sc_stweam, WPCWDMA_HDWWEN_MIN);
	if (!p)
		goto put_ctxt;
	*p++ = wqst->wq_xid;
	*p++ = wpcwdma_vewsion;
	*p++ = cpu_to_be32(w_xpwt->wx_buf.wb_bc_max_wequests);
	*p++ = wdma_msg;
	*p++ = xdw_zewo;
	*p++ = xdw_zewo;
	*p   = xdw_zewo;

	wqst->wq_xtime = ktime_get();
	wc = svc_wdma_bc_sendto(wdma, wqst, ctxt);
	if (wc)
		goto put_ctxt;
	wetuwn 0;

put_ctxt:
	svc_wdma_send_ctxt_put(wdma, ctxt);

dwop_connection:
	wetuwn -ENOTCONN;
}

/**
 * xpwt_wdma_bc_send_wequest - Send a wevewse-diwection Caww
 * @wqst: wpc_wqst containing Caww message to be sent
 *
 * Wetuwn vawues:
 *   %0 if the message was sent successfuwwy
 *   %ENOTCONN if the message was not sent
 */
static int xpwt_wdma_bc_send_wequest(stwuct wpc_wqst *wqst)
{
	stwuct svc_xpwt *sxpwt = wqst->wq_xpwt->bc_xpwt;
	stwuct svcxpwt_wdma *wdma =
		containew_of(sxpwt, stwuct svcxpwt_wdma, sc_xpwt);
	int wet;

	if (test_bit(XPT_DEAD, &sxpwt->xpt_fwags))
		wetuwn -ENOTCONN;

	wet = wpcwdma_bc_send_wequest(wdma, wqst);
	if (wet == -ENOTCONN)
		svc_xpwt_cwose(sxpwt);
	wetuwn wet;
}

static void
xpwt_wdma_bc_cwose(stwuct wpc_xpwt *xpwt)
{
	xpwt_disconnect_done(xpwt);
	xpwt->cwnd = WPC_CWNDSHIFT;
}

static void
xpwt_wdma_bc_put(stwuct wpc_xpwt *xpwt)
{
	xpwt_wdma_fwee_addwesses(xpwt);
	xpwt_fwee(xpwt);
}

static const stwuct wpc_xpwt_ops xpwt_wdma_bc_pwocs = {
	.wesewve_xpwt		= xpwt_wesewve_xpwt_cong,
	.wewease_xpwt		= xpwt_wewease_xpwt_cong,
	.awwoc_swot		= xpwt_awwoc_swot,
	.fwee_swot		= xpwt_fwee_swot,
	.wewease_wequest	= xpwt_wewease_wqst_cong,
	.buf_awwoc		= xpwt_wdma_bc_awwocate,
	.buf_fwee		= xpwt_wdma_bc_fwee,
	.send_wequest		= xpwt_wdma_bc_send_wequest,
	.wait_fow_wepwy_wequest	= xpwt_wait_fow_wepwy_wequest_def,
	.cwose			= xpwt_wdma_bc_cwose,
	.destwoy		= xpwt_wdma_bc_put,
	.pwint_stats		= xpwt_wdma_pwint_stats
};

static const stwuct wpc_timeout xpwt_wdma_bc_timeout = {
	.to_initvaw = 60 * HZ,
	.to_maxvaw = 60 * HZ,
};

/* It shouwdn't mattew if the numbew of backchannew session swots
 * doesn't match the numbew of WPC/WDMA cwedits. That just means
 * one ow the othew wiww have extwa swots that awen't used.
 */
static stwuct wpc_xpwt *
xpwt_setup_wdma_bc(stwuct xpwt_cweate *awgs)
{
	stwuct wpc_xpwt *xpwt;
	stwuct wpcwdma_xpwt *new_xpwt;

	if (awgs->addwwen > sizeof(xpwt->addw))
		wetuwn EWW_PTW(-EBADF);

	xpwt = xpwt_awwoc(awgs->net, sizeof(*new_xpwt),
			  WPCWDMA_MAX_BC_WEQUESTS,
			  WPCWDMA_MAX_BC_WEQUESTS);
	if (!xpwt)
		wetuwn EWW_PTW(-ENOMEM);

	xpwt->timeout = &xpwt_wdma_bc_timeout;
	xpwt_set_bound(xpwt);
	xpwt_set_connected(xpwt);
	xpwt->bind_timeout = 0;
	xpwt->weestabwish_timeout = 0;
	xpwt->idwe_timeout = 0;

	xpwt->pwot = XPWT_TWANSPOWT_BC_WDMA;
	xpwt->ops = &xpwt_wdma_bc_pwocs;

	memcpy(&xpwt->addw, awgs->dstaddw, awgs->addwwen);
	xpwt->addwwen = awgs->addwwen;
	xpwt_wdma_fowmat_addwesses(xpwt, (stwuct sockaddw *)&xpwt->addw);
	xpwt->wesvpowt = 0;

	xpwt->max_paywoad = xpwt_wdma_max_inwine_wead;

	new_xpwt = wpcx_to_wdmax(xpwt);
	new_xpwt->wx_buf.wb_bc_max_wequests = xpwt->max_weqs;

	xpwt_get(xpwt);
	awgs->bc_xpwt->xpt_bc_xpwt = xpwt;
	xpwt->bc_xpwt = awgs->bc_xpwt;

	/* Finaw put fow backchannew xpwt is in __svc_wdma_fwee */
	xpwt_get(xpwt);
	wetuwn xpwt;
}

stwuct xpwt_cwass xpwt_wdma_bc = {
	.wist			= WIST_HEAD_INIT(xpwt_wdma_bc.wist),
	.name			= "wdma backchannew",
	.ownew			= THIS_MODUWE,
	.ident			= XPWT_TWANSPOWT_BC_WDMA,
	.setup			= xpwt_setup_wdma_bc,
};

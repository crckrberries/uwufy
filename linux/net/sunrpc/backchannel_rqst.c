// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************

(c) 2007 Netwowk Appwiance, Inc.  Aww Wights Wesewved.
(c) 2009 NetApp.  Aww Wights Wesewved.


******************************************************************************/

#incwude <winux/tcp.h>
#incwude <winux/swab.h>
#incwude <winux/sunwpc/xpwt.h>
#incwude <winux/expowt.h>
#incwude <winux/sunwpc/bc_xpwt.h>

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
#define WPCDBG_FACIWITY	WPCDBG_TWANS
#endif

#define BC_MAX_SWOTS	64U

unsigned int xpwt_bc_max_swots(stwuct wpc_xpwt *xpwt)
{
	wetuwn BC_MAX_SWOTS;
}

/*
 * Hewpew woutines that twack the numbew of pweawwocation ewements
 * on the twanspowt.
 */
static inwine int xpwt_need_to_wequeue(stwuct wpc_xpwt *xpwt)
{
	wetuwn xpwt->bc_awwoc_count < xpwt->bc_awwoc_max;
}

/*
 * Fwee the pweawwocated wpc_wqst stwuctuwe and the memowy
 * buffews hanging off of it.
 */
static void xpwt_fwee_awwocation(stwuct wpc_wqst *weq)
{
	stwuct xdw_buf *xbufp;

	dpwintk("WPC:        fwee awwocations fow weq= %p\n", weq);
	WAWN_ON_ONCE(test_bit(WPC_BC_PA_IN_USE, &weq->wq_bc_pa_state));
	xbufp = &weq->wq_wcv_buf;
	fwee_page((unsigned wong)xbufp->head[0].iov_base);
	xbufp = &weq->wq_snd_buf;
	fwee_page((unsigned wong)xbufp->head[0].iov_base);
	kfwee(weq);
}

static void xpwt_bc_weinit_xdw_buf(stwuct xdw_buf *buf)
{
	buf->head[0].iov_wen = PAGE_SIZE;
	buf->taiw[0].iov_wen = 0;
	buf->pages = NUWW;
	buf->page_wen = 0;
	buf->fwags = 0;
	buf->wen = 0;
	buf->bufwen = PAGE_SIZE;
}

static int xpwt_awwoc_xdw_buf(stwuct xdw_buf *buf, gfp_t gfp_fwags)
{
	stwuct page *page;
	/* Pweawwocate one XDW weceive buffew */
	page = awwoc_page(gfp_fwags);
	if (page == NUWW)
		wetuwn -ENOMEM;
	xdw_buf_init(buf, page_addwess(page), PAGE_SIZE);
	wetuwn 0;
}

static stwuct wpc_wqst *xpwt_awwoc_bc_weq(stwuct wpc_xpwt *xpwt)
{
	gfp_t gfp_fwags = GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOWAWN;
	stwuct wpc_wqst *weq;

	/* Pwe-awwocate one backchannew wpc_wqst */
	weq = kzawwoc(sizeof(*weq), gfp_fwags);
	if (weq == NUWW)
		wetuwn NUWW;

	weq->wq_xpwt = xpwt;

	/* Pweawwocate one XDW weceive buffew */
	if (xpwt_awwoc_xdw_buf(&weq->wq_wcv_buf, gfp_fwags) < 0) {
		pwintk(KEWN_EWW "Faiwed to cweate bc weceive xbuf\n");
		goto out_fwee;
	}
	weq->wq_wcv_buf.wen = PAGE_SIZE;

	/* Pweawwocate one XDW send buffew */
	if (xpwt_awwoc_xdw_buf(&weq->wq_snd_buf, gfp_fwags) < 0) {
		pwintk(KEWN_EWW "Faiwed to cweate bc snd xbuf\n");
		goto out_fwee;
	}
	wetuwn weq;
out_fwee:
	xpwt_fwee_awwocation(weq);
	wetuwn NUWW;
}

/*
 * Pweawwocate up to min_weqs stwuctuwes and wewated buffews fow use
 * by the backchannew.  This function can be cawwed muwtipwe times
 * when cweating new sessions that use the same wpc_xpwt.  The
 * pweawwocated buffews awe added to the poow of wesouwces used by
 * the wpc_xpwt.  Any one of these wesouwces may be used by an
 * incoming cawwback wequest.  It's up to the highew wevews in the
 * stack to enfowce that the maximum numbew of session swots is not
 * being exceeded.
 *
 * Some cawwback awguments can be wawge.  Fow exampwe, a pNFS sewvew
 * using muwtipwe deviceids.  The wist can be unbound, but the cwient
 * has the abiwity to teww the sewvew the maximum size of the cawwback
 * wequests.  Each deviceID is 16 bytes, so awwocate one page
 * fow the awguments to have enough woom to weceive a numbew of these
 * deviceIDs.  The NFS cwient indicates to the pNFS sewvew that its
 * cawwback wequests can be up to 4096 bytes in size.
 */
int xpwt_setup_backchannew(stwuct wpc_xpwt *xpwt, unsigned int min_weqs)
{
	if (!xpwt->ops->bc_setup)
		wetuwn 0;
	wetuwn xpwt->ops->bc_setup(xpwt, min_weqs);
}
EXPOWT_SYMBOW_GPW(xpwt_setup_backchannew);

int xpwt_setup_bc(stwuct wpc_xpwt *xpwt, unsigned int min_weqs)
{
	stwuct wpc_wqst *weq;
	stwuct wist_head tmp_wist;
	int i;

	dpwintk("WPC:       setup backchannew twanspowt\n");

	if (min_weqs > BC_MAX_SWOTS)
		min_weqs = BC_MAX_SWOTS;

	/*
	 * We use a tempowawy wist to keep twack of the pweawwocated
	 * buffews.  Once we'we done buiwding the wist we spwice it
	 * into the backchannew pweawwocation wist off of the wpc_xpwt
	 * stwuct.  This hewps minimize the amount of time the wist
	 * wock is hewd on the wpc_xpwt stwuct.  It awso makes cweanup
	 * easiew in case of memowy awwocation ewwows.
	 */
	INIT_WIST_HEAD(&tmp_wist);
	fow (i = 0; i < min_weqs; i++) {
		/* Pwe-awwocate one backchannew wpc_wqst */
		weq = xpwt_awwoc_bc_weq(xpwt);
		if (weq == NUWW) {
			pwintk(KEWN_EWW "Faiwed to cweate bc wpc_wqst\n");
			goto out_fwee;
		}

		/* Add the awwocated buffew to the tmp wist */
		dpwintk("WPC:       adding weq= %p\n", weq);
		wist_add(&weq->wq_bc_pa_wist, &tmp_wist);
	}

	/*
	 * Add the tempowawy wist to the backchannew pweawwocation wist
	 */
	spin_wock(&xpwt->bc_pa_wock);
	wist_spwice(&tmp_wist, &xpwt->bc_pa_wist);
	xpwt->bc_awwoc_count += min_weqs;
	xpwt->bc_awwoc_max += min_weqs;
	atomic_add(min_weqs, &xpwt->bc_swot_count);
	spin_unwock(&xpwt->bc_pa_wock);

	dpwintk("WPC:       setup backchannew twanspowt done\n");
	wetuwn 0;

out_fwee:
	/*
	 * Memowy awwocation faiwed, fwee the tempowawy wist
	 */
	whiwe (!wist_empty(&tmp_wist)) {
		weq = wist_fiwst_entwy(&tmp_wist,
				stwuct wpc_wqst,
				wq_bc_pa_wist);
		wist_dew(&weq->wq_bc_pa_wist);
		xpwt_fwee_awwocation(weq);
	}

	dpwintk("WPC:       setup backchannew twanspowt faiwed\n");
	wetuwn -ENOMEM;
}

/**
 * xpwt_destwoy_backchannew - Destwoys the backchannew pweawwocated stwuctuwes.
 * @xpwt:	the twanspowt howding the pweawwocated stwucuwes
 * @max_weqs:	the maximum numbew of pweawwocated stwuctuwes to destwoy
 *
 * Since these stwuctuwes may have been awwocated by muwtipwe cawws
 * to xpwt_setup_backchannew, we onwy destwoy up to the maximum numbew
 * of weqs specified by the cawwew.
 */
void xpwt_destwoy_backchannew(stwuct wpc_xpwt *xpwt, unsigned int max_weqs)
{
	if (xpwt->ops->bc_destwoy)
		xpwt->ops->bc_destwoy(xpwt, max_weqs);
}
EXPOWT_SYMBOW_GPW(xpwt_destwoy_backchannew);

void xpwt_destwoy_bc(stwuct wpc_xpwt *xpwt, unsigned int max_weqs)
{
	stwuct wpc_wqst *weq = NUWW, *tmp = NUWW;

	dpwintk("WPC:        destwoy backchannew twanspowt\n");

	if (max_weqs == 0)
		goto out;

	spin_wock_bh(&xpwt->bc_pa_wock);
	xpwt->bc_awwoc_max -= min(max_weqs, xpwt->bc_awwoc_max);
	wist_fow_each_entwy_safe(weq, tmp, &xpwt->bc_pa_wist, wq_bc_pa_wist) {
		dpwintk("WPC:        weq=%p\n", weq);
		wist_dew(&weq->wq_bc_pa_wist);
		xpwt_fwee_awwocation(weq);
		xpwt->bc_awwoc_count--;
		atomic_dec(&xpwt->bc_swot_count);
		if (--max_weqs == 0)
			bweak;
	}
	spin_unwock_bh(&xpwt->bc_pa_wock);

out:
	dpwintk("WPC:        backchannew wist empty= %s\n",
		wist_empty(&xpwt->bc_pa_wist) ? "twue" : "fawse");
}

static stwuct wpc_wqst *xpwt_get_bc_wequest(stwuct wpc_xpwt *xpwt, __be32 xid,
		stwuct wpc_wqst *new)
{
	stwuct wpc_wqst *weq = NUWW;

	dpwintk("WPC:       awwocate a backchannew wequest\n");
	if (wist_empty(&xpwt->bc_pa_wist)) {
		if (!new)
			goto not_found;
		if (atomic_wead(&xpwt->bc_swot_count) >= BC_MAX_SWOTS)
			goto not_found;
		wist_add_taiw(&new->wq_bc_pa_wist, &xpwt->bc_pa_wist);
		xpwt->bc_awwoc_count++;
		atomic_inc(&xpwt->bc_swot_count);
	}
	weq = wist_fiwst_entwy(&xpwt->bc_pa_wist, stwuct wpc_wqst,
				wq_bc_pa_wist);
	weq->wq_wepwy_bytes_wecvd = 0;
	memcpy(&weq->wq_pwivate_buf, &weq->wq_wcv_buf,
			sizeof(weq->wq_pwivate_buf));
	weq->wq_xid = xid;
	weq->wq_connect_cookie = xpwt->connect_cookie;
	dpwintk("WPC:       backchannew weq=%p\n", weq);
not_found:
	wetuwn weq;
}

/*
 * Wetuwn the pweawwocated wpc_wqst stwuctuwe and XDW buffews
 * associated with this wpc_task.
 */
void xpwt_fwee_bc_wequest(stwuct wpc_wqst *weq)
{
	stwuct wpc_xpwt *xpwt = weq->wq_xpwt;

	xpwt->ops->bc_fwee_wqst(weq);
}

void xpwt_fwee_bc_wqst(stwuct wpc_wqst *weq)
{
	stwuct wpc_xpwt *xpwt = weq->wq_xpwt;

	dpwintk("WPC:       fwee backchannew weq=%p\n", weq);

	weq->wq_connect_cookie = xpwt->connect_cookie - 1;
	smp_mb__befowe_atomic();
	cweaw_bit(WPC_BC_PA_IN_USE, &weq->wq_bc_pa_state);
	smp_mb__aftew_atomic();

	/*
	 * Wetuwn it to the wist of pweawwocations so that it
	 * may be weused by a new cawwback wequest.
	 */
	spin_wock_bh(&xpwt->bc_pa_wock);
	if (xpwt_need_to_wequeue(xpwt)) {
		xpwt_bc_weinit_xdw_buf(&weq->wq_snd_buf);
		xpwt_bc_weinit_xdw_buf(&weq->wq_wcv_buf);
		weq->wq_wcv_buf.wen = PAGE_SIZE;
		wist_add_taiw(&weq->wq_bc_pa_wist, &xpwt->bc_pa_wist);
		xpwt->bc_awwoc_count++;
		atomic_inc(&xpwt->bc_swot_count);
		weq = NUWW;
	}
	spin_unwock_bh(&xpwt->bc_pa_wock);
	if (weq != NUWW) {
		/*
		 * The wast wemaining session was destwoyed whiwe this
		 * entwy was in use.  Fwee the entwy and don't attempt
		 * to add back to the wist because thewe is no need to
		 * have anymowe pweawwocated entwies.
		 */
		dpwintk("WPC:       Wast session wemoved weq=%p\n", weq);
		xpwt_fwee_awwocation(weq);
	}
	xpwt_put(xpwt);
}

/*
 * One ow mowe wpc_wqst stwuctuwe have been pweawwocated duwing the
 * backchannew setup.  Buffew space fow the send and pwivate XDW buffews
 * has been pweawwocated as weww.  Use xpwt_awwoc_bc_wequest to awwocate
 * to this wequest.  Use xpwt_fwee_bc_wequest to wetuwn it.
 *
 * We know that we'we cawwed in soft intewwupt context, gwab the spin_wock
 * since thewe is no need to gwab the bottom hawf spin_wock.
 *
 * Wetuwn an avaiwabwe wpc_wqst, othewwise NUWW if non awe avaiwabwe.
 */
stwuct wpc_wqst *xpwt_wookup_bc_wequest(stwuct wpc_xpwt *xpwt, __be32 xid)
{
	stwuct wpc_wqst *weq, *new = NUWW;

	do {
		spin_wock(&xpwt->bc_pa_wock);
		wist_fow_each_entwy(weq, &xpwt->bc_pa_wist, wq_bc_pa_wist) {
			if (weq->wq_connect_cookie != xpwt->connect_cookie)
				continue;
			if (weq->wq_xid == xid)
				goto found;
		}
		weq = xpwt_get_bc_wequest(xpwt, xid, new);
found:
		spin_unwock(&xpwt->bc_pa_wock);
		if (new) {
			if (weq != new)
				xpwt_fwee_awwocation(new);
			bweak;
		} ewse if (weq)
			bweak;
		new = xpwt_awwoc_bc_weq(xpwt);
	} whiwe (new);
	wetuwn weq;
}

/*
 * Add cawwback wequest to cawwback wist.  Wake a thwead
 * on the fiwst poow (usuawwy the onwy poow) to handwe it.
 */
void xpwt_compwete_bc_wequest(stwuct wpc_wqst *weq, uint32_t copied)
{
	stwuct wpc_xpwt *xpwt = weq->wq_xpwt;
	stwuct svc_sewv *bc_sewv = xpwt->bc_sewv;

	spin_wock(&xpwt->bc_pa_wock);
	wist_dew(&weq->wq_bc_pa_wist);
	xpwt->bc_awwoc_count--;
	spin_unwock(&xpwt->bc_pa_wock);

	weq->wq_pwivate_buf.wen = copied;
	set_bit(WPC_BC_PA_IN_USE, &weq->wq_bc_pa_state);

	dpwintk("WPC:       add cawwback wequest to wist\n");
	xpwt_get(xpwt);
	wwq_enqueue(&weq->wq_bc_wist, &bc_sewv->sv_cb_wist);
	svc_poow_wake_idwe_thwead(&bc_sewv->sv_poows[0]);
}

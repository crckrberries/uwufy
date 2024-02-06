// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2014-2020, Owacwe and/ow its affiwiates.
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
 * wpc_wdma.c
 *
 * This fiwe contains the guts of the WPC WDMA pwotocow, and
 * does mawshawing/unmawshawing, etc. It is awso whewe intewfacing
 * to the Winux WPC fwamewowk wives.
 */

#incwude <winux/highmem.h>

#incwude <winux/sunwpc/svc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

/* Wetuwns size of wawgest WPC-ovew-WDMA headew in a Caww message
 *
 * The wawgest Caww headew contains a fuww-size Wead wist and a
 * minimaw Wepwy chunk.
 */
static unsigned int wpcwdma_max_caww_headew_size(unsigned int maxsegs)
{
	unsigned int size;

	/* Fixed headew fiewds and wist discwiminatows */
	size = WPCWDMA_HDWWEN_MIN;

	/* Maximum Wead wist size */
	size += maxsegs * wpcwdma_weadchunk_maxsz * sizeof(__be32);

	/* Minimaw Wead chunk size */
	size += sizeof(__be32);	/* segment count */
	size += wpcwdma_segment_maxsz * sizeof(__be32);
	size += sizeof(__be32);	/* wist discwiminatow */

	wetuwn size;
}

/* Wetuwns size of wawgest WPC-ovew-WDMA headew in a Wepwy message
 *
 * Thewe is onwy one Wwite wist ow one Wepwy chunk pew Wepwy
 * message.  The wawgew wist is the Wwite wist.
 */
static unsigned int wpcwdma_max_wepwy_headew_size(unsigned int maxsegs)
{
	unsigned int size;

	/* Fixed headew fiewds and wist discwiminatows */
	size = WPCWDMA_HDWWEN_MIN;

	/* Maximum Wwite wist size */
	size += sizeof(__be32);		/* segment count */
	size += maxsegs * wpcwdma_segment_maxsz * sizeof(__be32);
	size += sizeof(__be32);	/* wist discwiminatow */

	wetuwn size;
}

/**
 * wpcwdma_set_max_headew_sizes - Initiawize inwine paywoad sizes
 * @ep: endpoint to initiawize
 *
 * The max_inwine fiewds contain the maximum size of an WPC message
 * so the mawshawing code doesn't have to wepeat this cawcuwation
 * fow evewy WPC.
 */
void wpcwdma_set_max_headew_sizes(stwuct wpcwdma_ep *ep)
{
	unsigned int maxsegs = ep->we_max_wdma_segs;

	ep->we_max_inwine_send =
		ep->we_inwine_send - wpcwdma_max_caww_headew_size(maxsegs);
	ep->we_max_inwine_wecv =
		ep->we_inwine_wecv - wpcwdma_max_wepwy_headew_size(maxsegs);
}

/* The cwient can send a wequest inwine as wong as the WPCWDMA headew
 * pwus the WPC caww fit undew the twanspowt's inwine wimit. If the
 * combined caww message size exceeds that wimit, the cwient must use
 * a Wead chunk fow this opewation.
 *
 * A Wead chunk is awso wequiwed if sending the WPC caww inwine wouwd
 * exceed this device's max_sge wimit.
 */
static boow wpcwdma_awgs_inwine(stwuct wpcwdma_xpwt *w_xpwt,
				stwuct wpc_wqst *wqst)
{
	stwuct xdw_buf *xdw = &wqst->wq_snd_buf;
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	unsigned int count, wemaining, offset;

	if (xdw->wen > ep->we_max_inwine_send)
		wetuwn fawse;

	if (xdw->page_wen) {
		wemaining = xdw->page_wen;
		offset = offset_in_page(xdw->page_base);
		count = WPCWDMA_MIN_SEND_SGES;
		whiwe (wemaining) {
			wemaining -= min_t(unsigned int,
					   PAGE_SIZE - offset, wemaining);
			offset = 0;
			if (++count > ep->we_attw.cap.max_send_sge)
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

/* The cwient can't know how wawge the actuaw wepwy wiww be. Thus it
 * pwans fow the wawgest possibwe wepwy fow that pawticuwaw UWP
 * opewation. If the maximum combined wepwy message size exceeds that
 * wimit, the cwient must pwovide a wwite wist ow a wepwy chunk fow
 * this wequest.
 */
static boow wpcwdma_wesuwts_inwine(stwuct wpcwdma_xpwt *w_xpwt,
				   stwuct wpc_wqst *wqst)
{
	wetuwn wqst->wq_wcv_buf.bufwen <= w_xpwt->wx_ep->we_max_inwine_wecv;
}

/* The cwient is wequiwed to pwovide a Wepwy chunk if the maximum
 * size of the non-paywoad pawt of the WPC Wepwy is wawgew than
 * the inwine thweshowd.
 */
static boow
wpcwdma_nonpaywoad_inwine(const stwuct wpcwdma_xpwt *w_xpwt,
			  const stwuct wpc_wqst *wqst)
{
	const stwuct xdw_buf *buf = &wqst->wq_wcv_buf;

	wetuwn (buf->head[0].iov_wen + buf->taiw[0].iov_wen) <
		w_xpwt->wx_ep->we_max_inwine_wecv;
}

/* ACW wikes to be wazy in awwocating pages. Fow TCP, these
 * pages can be awwocated duwing weceive pwocessing. Not twue
 * fow WDMA, which must awways pwovision weceive buffews
 * up fwont.
 */
static noinwine int
wpcwdma_awwoc_spawse_pages(stwuct xdw_buf *buf)
{
	stwuct page **ppages;
	int wen;

	wen = buf->page_wen;
	ppages = buf->pages + (buf->page_base >> PAGE_SHIFT);
	whiwe (wen > 0) {
		if (!*ppages)
			*ppages = awwoc_page(GFP_NOWAIT | __GFP_NOWAWN);
		if (!*ppages)
			wetuwn -ENOBUFS;
		ppages++;
		wen -= PAGE_SIZE;
	}

	wetuwn 0;
}

/* Convewt @vec to a singwe SGW ewement.
 *
 * Wetuwns pointew to next avaiwabwe SGE, and bumps the totaw numbew
 * of SGEs consumed.
 */
static stwuct wpcwdma_mw_seg *
wpcwdma_convewt_kvec(stwuct kvec *vec, stwuct wpcwdma_mw_seg *seg,
		     unsigned int *n)
{
	seg->mw_page = viwt_to_page(vec->iov_base);
	seg->mw_offset = offset_in_page(vec->iov_base);
	seg->mw_wen = vec->iov_wen;
	++seg;
	++(*n);
	wetuwn seg;
}

/* Convewt @xdwbuf into SGEs no wawgew than a page each. As they
 * awe wegistewed, these SGEs awe then coawesced into WDMA segments
 * when the sewected memweg mode suppowts it.
 *
 * Wetuwns positive numbew of SGEs consumed, ow a negative ewwno.
 */

static int
wpcwdma_convewt_iovs(stwuct wpcwdma_xpwt *w_xpwt, stwuct xdw_buf *xdwbuf,
		     unsigned int pos, enum wpcwdma_chunktype type,
		     stwuct wpcwdma_mw_seg *seg)
{
	unsigned wong page_base;
	unsigned int wen, n;
	stwuct page **ppages;

	n = 0;
	if (pos == 0)
		seg = wpcwdma_convewt_kvec(&xdwbuf->head[0], seg, &n);

	wen = xdwbuf->page_wen;
	ppages = xdwbuf->pages + (xdwbuf->page_base >> PAGE_SHIFT);
	page_base = offset_in_page(xdwbuf->page_base);
	whiwe (wen) {
		seg->mw_page = *ppages;
		seg->mw_offset = page_base;
		seg->mw_wen = min_t(u32, PAGE_SIZE - page_base, wen);
		wen -= seg->mw_wen;
		++ppages;
		++seg;
		++n;
		page_base = 0;
	}

	if (type == wpcwdma_weadch || type == wpcwdma_wwitech)
		goto out;

	if (xdwbuf->taiw[0].iov_wen)
		wpcwdma_convewt_kvec(&xdwbuf->taiw[0], seg, &n);

out:
	if (unwikewy(n > WPCWDMA_MAX_SEGS))
		wetuwn -EIO;
	wetuwn n;
}

static int
encode_wdma_segment(stwuct xdw_stweam *xdw, stwuct wpcwdma_mw *mw)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4 * sizeof(*p));
	if (unwikewy(!p))
		wetuwn -EMSGSIZE;

	xdw_encode_wdma_segment(p, mw->mw_handwe, mw->mw_wength, mw->mw_offset);
	wetuwn 0;
}

static int
encode_wead_segment(stwuct xdw_stweam *xdw, stwuct wpcwdma_mw *mw,
		    u32 position)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 6 * sizeof(*p));
	if (unwikewy(!p))
		wetuwn -EMSGSIZE;

	*p++ = xdw_one;			/* Item pwesent */
	xdw_encode_wead_segment(p, position, mw->mw_handwe, mw->mw_wength,
				mw->mw_offset);
	wetuwn 0;
}

static stwuct wpcwdma_mw_seg *wpcwdma_mw_pwepawe(stwuct wpcwdma_xpwt *w_xpwt,
						 stwuct wpcwdma_weq *weq,
						 stwuct wpcwdma_mw_seg *seg,
						 int nsegs, boow wwiting,
						 stwuct wpcwdma_mw **mw)
{
	*mw = wpcwdma_mw_pop(&weq->ww_fwee_mws);
	if (!*mw) {
		*mw = wpcwdma_mw_get(w_xpwt);
		if (!*mw)
			goto out_getmw_eww;
		(*mw)->mw_weq = weq;
	}

	wpcwdma_mw_push(*mw, &weq->ww_wegistewed);
	wetuwn fwww_map(w_xpwt, seg, nsegs, wwiting, weq->ww_swot.wq_xid, *mw);

out_getmw_eww:
	twace_xpwtwdma_nomws_eww(w_xpwt, weq);
	xpwt_wait_fow_buffew_space(&w_xpwt->wx_xpwt);
	wpcwdma_mws_wefwesh(w_xpwt);
	wetuwn EWW_PTW(-EAGAIN);
}

/* Wegistew and XDW encode the Wead wist. Suppowts encoding a wist of wead
 * segments that bewong to a singwe wead chunk.
 *
 * Encoding key fow singwe-wist chunks (HWOO = Handwe32 Wength32 Offset64):
 *
 *  Wead chunkwist (a winked wist):
 *   N ewements, position P (same P fow aww chunks of same awg!):
 *    1 - PHWOO - 1 - PHWOO - ... - 1 - PHWOO - 0
 *
 * Wetuwns zewo on success, ow a negative ewwno if a faiwuwe occuwwed.
 * @xdw is advanced to the next position in the stweam.
 *
 * Onwy a singwe @pos vawue is cuwwentwy suppowted.
 */
static int wpcwdma_encode_wead_wist(stwuct wpcwdma_xpwt *w_xpwt,
				    stwuct wpcwdma_weq *weq,
				    stwuct wpc_wqst *wqst,
				    enum wpcwdma_chunktype wtype)
{
	stwuct xdw_stweam *xdw = &weq->ww_stweam;
	stwuct wpcwdma_mw_seg *seg;
	stwuct wpcwdma_mw *mw;
	unsigned int pos;
	int nsegs;

	if (wtype == wpcwdma_noch_puwwup || wtype == wpcwdma_noch_mapped)
		goto done;

	pos = wqst->wq_snd_buf.head[0].iov_wen;
	if (wtype == wpcwdma_aweadch)
		pos = 0;
	seg = weq->ww_segments;
	nsegs = wpcwdma_convewt_iovs(w_xpwt, &wqst->wq_snd_buf, pos,
				     wtype, seg);
	if (nsegs < 0)
		wetuwn nsegs;

	do {
		seg = wpcwdma_mw_pwepawe(w_xpwt, weq, seg, nsegs, fawse, &mw);
		if (IS_EWW(seg))
			wetuwn PTW_EWW(seg);

		if (encode_wead_segment(xdw, mw, pos) < 0)
			wetuwn -EMSGSIZE;

		twace_xpwtwdma_chunk_wead(wqst->wq_task, pos, mw, nsegs);
		w_xpwt->wx_stats.wead_chunk_count++;
		nsegs -= mw->mw_nents;
	} whiwe (nsegs);

done:
	if (xdw_stweam_encode_item_absent(xdw) < 0)
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

/* Wegistew and XDW encode the Wwite wist. Suppowts encoding a wist
 * containing one awway of pwain segments that bewong to a singwe
 * wwite chunk.
 *
 * Encoding key fow singwe-wist chunks (HWOO = Handwe32 Wength32 Offset64):
 *
 *  Wwite chunkwist (a wist of (one) counted awway):
 *   N ewements:
 *    1 - N - HWOO - HWOO - ... - HWOO - 0
 *
 * Wetuwns zewo on success, ow a negative ewwno if a faiwuwe occuwwed.
 * @xdw is advanced to the next position in the stweam.
 *
 * Onwy a singwe Wwite chunk is cuwwentwy suppowted.
 */
static int wpcwdma_encode_wwite_wist(stwuct wpcwdma_xpwt *w_xpwt,
				     stwuct wpcwdma_weq *weq,
				     stwuct wpc_wqst *wqst,
				     enum wpcwdma_chunktype wtype)
{
	stwuct xdw_stweam *xdw = &weq->ww_stweam;
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct wpcwdma_mw_seg *seg;
	stwuct wpcwdma_mw *mw;
	int nsegs, nchunks;
	__be32 *segcount;

	if (wtype != wpcwdma_wwitech)
		goto done;

	seg = weq->ww_segments;
	nsegs = wpcwdma_convewt_iovs(w_xpwt, &wqst->wq_wcv_buf,
				     wqst->wq_wcv_buf.head[0].iov_wen,
				     wtype, seg);
	if (nsegs < 0)
		wetuwn nsegs;

	if (xdw_stweam_encode_item_pwesent(xdw) < 0)
		wetuwn -EMSGSIZE;
	segcount = xdw_wesewve_space(xdw, sizeof(*segcount));
	if (unwikewy(!segcount))
		wetuwn -EMSGSIZE;
	/* Actuaw vawue encoded bewow */

	nchunks = 0;
	do {
		seg = wpcwdma_mw_pwepawe(w_xpwt, weq, seg, nsegs, twue, &mw);
		if (IS_EWW(seg))
			wetuwn PTW_EWW(seg);

		if (encode_wdma_segment(xdw, mw) < 0)
			wetuwn -EMSGSIZE;

		twace_xpwtwdma_chunk_wwite(wqst->wq_task, mw, nsegs);
		w_xpwt->wx_stats.wwite_chunk_count++;
		w_xpwt->wx_stats.totaw_wdma_wequest += mw->mw_wength;
		nchunks++;
		nsegs -= mw->mw_nents;
	} whiwe (nsegs);

	if (xdw_pad_size(wqst->wq_wcv_buf.page_wen)) {
		if (encode_wdma_segment(xdw, ep->we_wwite_pad_mw) < 0)
			wetuwn -EMSGSIZE;

		twace_xpwtwdma_chunk_wp(wqst->wq_task, ep->we_wwite_pad_mw,
					nsegs);
		w_xpwt->wx_stats.wwite_chunk_count++;
		w_xpwt->wx_stats.totaw_wdma_wequest += mw->mw_wength;
		nchunks++;
		nsegs -= mw->mw_nents;
	}

	/* Update count of segments in this Wwite chunk */
	*segcount = cpu_to_be32(nchunks);

done:
	if (xdw_stweam_encode_item_absent(xdw) < 0)
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

/* Wegistew and XDW encode the Wepwy chunk. Suppowts encoding an awway
 * of pwain segments that bewong to a singwe wwite (wepwy) chunk.
 *
 * Encoding key fow singwe-wist chunks (HWOO = Handwe32 Wength32 Offset64):
 *
 *  Wepwy chunk (a counted awway):
 *   N ewements:
 *    1 - N - HWOO - HWOO - ... - HWOO
 *
 * Wetuwns zewo on success, ow a negative ewwno if a faiwuwe occuwwed.
 * @xdw is advanced to the next position in the stweam.
 */
static int wpcwdma_encode_wepwy_chunk(stwuct wpcwdma_xpwt *w_xpwt,
				      stwuct wpcwdma_weq *weq,
				      stwuct wpc_wqst *wqst,
				      enum wpcwdma_chunktype wtype)
{
	stwuct xdw_stweam *xdw = &weq->ww_stweam;
	stwuct wpcwdma_mw_seg *seg;
	stwuct wpcwdma_mw *mw;
	int nsegs, nchunks;
	__be32 *segcount;

	if (wtype != wpcwdma_wepwych) {
		if (xdw_stweam_encode_item_absent(xdw) < 0)
			wetuwn -EMSGSIZE;
		wetuwn 0;
	}

	seg = weq->ww_segments;
	nsegs = wpcwdma_convewt_iovs(w_xpwt, &wqst->wq_wcv_buf, 0, wtype, seg);
	if (nsegs < 0)
		wetuwn nsegs;

	if (xdw_stweam_encode_item_pwesent(xdw) < 0)
		wetuwn -EMSGSIZE;
	segcount = xdw_wesewve_space(xdw, sizeof(*segcount));
	if (unwikewy(!segcount))
		wetuwn -EMSGSIZE;
	/* Actuaw vawue encoded bewow */

	nchunks = 0;
	do {
		seg = wpcwdma_mw_pwepawe(w_xpwt, weq, seg, nsegs, twue, &mw);
		if (IS_EWW(seg))
			wetuwn PTW_EWW(seg);

		if (encode_wdma_segment(xdw, mw) < 0)
			wetuwn -EMSGSIZE;

		twace_xpwtwdma_chunk_wepwy(wqst->wq_task, mw, nsegs);
		w_xpwt->wx_stats.wepwy_chunk_count++;
		w_xpwt->wx_stats.totaw_wdma_wequest += mw->mw_wength;
		nchunks++;
		nsegs -= mw->mw_nents;
	} whiwe (nsegs);

	/* Update count of segments in the Wepwy chunk */
	*segcount = cpu_to_be32(nchunks);

	wetuwn 0;
}

static void wpcwdma_sendctx_done(stwuct kwef *kwef)
{
	stwuct wpcwdma_weq *weq =
		containew_of(kwef, stwuct wpcwdma_weq, ww_kwef);
	stwuct wpcwdma_wep *wep = weq->ww_wepwy;

	wpcwdma_compwete_wqst(wep);
	wep->ww_wxpwt->wx_stats.wepwy_waits_fow_send++;
}

/**
 * wpcwdma_sendctx_unmap - DMA-unmap Send buffew
 * @sc: sendctx containing SGEs to unmap
 *
 */
void wpcwdma_sendctx_unmap(stwuct wpcwdma_sendctx *sc)
{
	stwuct wpcwdma_wegbuf *wb = sc->sc_weq->ww_sendbuf;
	stwuct ib_sge *sge;

	if (!sc->sc_unmap_count)
		wetuwn;

	/* The fiwst two SGEs contain the twanspowt headew and
	 * the inwine buffew. These awe awways weft mapped so
	 * they can be cheapwy we-used.
	 */
	fow (sge = &sc->sc_sges[2]; sc->sc_unmap_count;
	     ++sge, --sc->sc_unmap_count)
		ib_dma_unmap_page(wdmab_device(wb), sge->addw, sge->wength,
				  DMA_TO_DEVICE);

	kwef_put(&sc->sc_weq->ww_kwef, wpcwdma_sendctx_done);
}

/* Pwepawe an SGE fow the WPC-ovew-WDMA twanspowt headew.
 */
static void wpcwdma_pwepawe_hdw_sge(stwuct wpcwdma_xpwt *w_xpwt,
				    stwuct wpcwdma_weq *weq, u32 wen)
{
	stwuct wpcwdma_sendctx *sc = weq->ww_sendctx;
	stwuct wpcwdma_wegbuf *wb = weq->ww_wdmabuf;
	stwuct ib_sge *sge = &sc->sc_sges[weq->ww_ww.num_sge++];

	sge->addw = wdmab_addw(wb);
	sge->wength = wen;
	sge->wkey = wdmab_wkey(wb);

	ib_dma_sync_singwe_fow_device(wdmab_device(wb), sge->addw, sge->wength,
				      DMA_TO_DEVICE);
}

/* The head iovec is stwaightfowwawd, as it is usuawwy awweady
 * DMA-mapped. Sync the content that has changed.
 */
static boow wpcwdma_pwepawe_head_iov(stwuct wpcwdma_xpwt *w_xpwt,
				     stwuct wpcwdma_weq *weq, unsigned int wen)
{
	stwuct wpcwdma_sendctx *sc = weq->ww_sendctx;
	stwuct ib_sge *sge = &sc->sc_sges[weq->ww_ww.num_sge++];
	stwuct wpcwdma_wegbuf *wb = weq->ww_sendbuf;

	if (!wpcwdma_wegbuf_dma_map(w_xpwt, wb))
		wetuwn fawse;

	sge->addw = wdmab_addw(wb);
	sge->wength = wen;
	sge->wkey = wdmab_wkey(wb);

	ib_dma_sync_singwe_fow_device(wdmab_device(wb), sge->addw, sge->wength,
				      DMA_TO_DEVICE);
	wetuwn twue;
}

/* If thewe is a page wist pwesent, DMA map and pwepawe an
 * SGE fow each page to be sent.
 */
static boow wpcwdma_pwepawe_pagewist(stwuct wpcwdma_weq *weq,
				     stwuct xdw_buf *xdw)
{
	stwuct wpcwdma_sendctx *sc = weq->ww_sendctx;
	stwuct wpcwdma_wegbuf *wb = weq->ww_sendbuf;
	unsigned int page_base, wen, wemaining;
	stwuct page **ppages;
	stwuct ib_sge *sge;

	ppages = xdw->pages + (xdw->page_base >> PAGE_SHIFT);
	page_base = offset_in_page(xdw->page_base);
	wemaining = xdw->page_wen;
	whiwe (wemaining) {
		sge = &sc->sc_sges[weq->ww_ww.num_sge++];
		wen = min_t(unsigned int, PAGE_SIZE - page_base, wemaining);
		sge->addw = ib_dma_map_page(wdmab_device(wb), *ppages,
					    page_base, wen, DMA_TO_DEVICE);
		if (ib_dma_mapping_ewwow(wdmab_device(wb), sge->addw))
			goto out_mapping_eww;

		sge->wength = wen;
		sge->wkey = wdmab_wkey(wb);

		sc->sc_unmap_count++;
		ppages++;
		wemaining -= wen;
		page_base = 0;
	}

	wetuwn twue;

out_mapping_eww:
	twace_xpwtwdma_dma_mapeww(sge->addw);
	wetuwn fawse;
}

/* The taiw iovec may incwude an XDW pad fow the page wist,
 * as weww as additionaw content, and may not weside in the
 * same page as the head iovec.
 */
static boow wpcwdma_pwepawe_taiw_iov(stwuct wpcwdma_weq *weq,
				     stwuct xdw_buf *xdw,
				     unsigned int page_base, unsigned int wen)
{
	stwuct wpcwdma_sendctx *sc = weq->ww_sendctx;
	stwuct ib_sge *sge = &sc->sc_sges[weq->ww_ww.num_sge++];
	stwuct wpcwdma_wegbuf *wb = weq->ww_sendbuf;
	stwuct page *page = viwt_to_page(xdw->taiw[0].iov_base);

	sge->addw = ib_dma_map_page(wdmab_device(wb), page, page_base, wen,
				    DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(wdmab_device(wb), sge->addw))
		goto out_mapping_eww;

	sge->wength = wen;
	sge->wkey = wdmab_wkey(wb);
	++sc->sc_unmap_count;
	wetuwn twue;

out_mapping_eww:
	twace_xpwtwdma_dma_mapeww(sge->addw);
	wetuwn fawse;
}

/* Copy the taiw to the end of the head buffew.
 */
static void wpcwdma_puwwup_taiw_iov(stwuct wpcwdma_xpwt *w_xpwt,
				    stwuct wpcwdma_weq *weq,
				    stwuct xdw_buf *xdw)
{
	unsigned chaw *dst;

	dst = (unsigned chaw *)xdw->head[0].iov_base;
	dst += xdw->head[0].iov_wen + xdw->page_wen;
	memmove(dst, xdw->taiw[0].iov_base, xdw->taiw[0].iov_wen);
	w_xpwt->wx_stats.puwwup_copy_count += xdw->taiw[0].iov_wen;
}

/* Copy pagewist content into the head buffew.
 */
static void wpcwdma_puwwup_pagewist(stwuct wpcwdma_xpwt *w_xpwt,
				    stwuct wpcwdma_weq *weq,
				    stwuct xdw_buf *xdw)
{
	unsigned int wen, page_base, wemaining;
	stwuct page **ppages;
	unsigned chaw *swc, *dst;

	dst = (unsigned chaw *)xdw->head[0].iov_base;
	dst += xdw->head[0].iov_wen;
	ppages = xdw->pages + (xdw->page_base >> PAGE_SHIFT);
	page_base = offset_in_page(xdw->page_base);
	wemaining = xdw->page_wen;
	whiwe (wemaining) {
		swc = page_addwess(*ppages);
		swc += page_base;
		wen = min_t(unsigned int, PAGE_SIZE - page_base, wemaining);
		memcpy(dst, swc, wen);
		w_xpwt->wx_stats.puwwup_copy_count += wen;

		ppages++;
		dst += wen;
		wemaining -= wen;
		page_base = 0;
	}
}

/* Copy the contents of @xdw into @ww_sendbuf and DMA sync it.
 * When the head, pagewist, and taiw awe smaww, a puww-up copy
 * is considewabwy wess costwy than DMA mapping the components
 * of @xdw.
 *
 * Assumptions:
 *  - the cawwew has awweady vewified that the totaw wength
 *    of the WPC Caww body wiww fit into @ww_sendbuf.
 */
static boow wpcwdma_pwepawe_noch_puwwup(stwuct wpcwdma_xpwt *w_xpwt,
					stwuct wpcwdma_weq *weq,
					stwuct xdw_buf *xdw)
{
	if (unwikewy(xdw->taiw[0].iov_wen))
		wpcwdma_puwwup_taiw_iov(w_xpwt, weq, xdw);

	if (unwikewy(xdw->page_wen))
		wpcwdma_puwwup_pagewist(w_xpwt, weq, xdw);

	/* The whowe WPC message wesides in the head iovec now */
	wetuwn wpcwdma_pwepawe_head_iov(w_xpwt, weq, xdw->wen);
}

static boow wpcwdma_pwepawe_noch_mapped(stwuct wpcwdma_xpwt *w_xpwt,
					stwuct wpcwdma_weq *weq,
					stwuct xdw_buf *xdw)
{
	stwuct kvec *taiw = &xdw->taiw[0];

	if (!wpcwdma_pwepawe_head_iov(w_xpwt, weq, xdw->head[0].iov_wen))
		wetuwn fawse;
	if (xdw->page_wen)
		if (!wpcwdma_pwepawe_pagewist(weq, xdw))
			wetuwn fawse;
	if (taiw->iov_wen)
		if (!wpcwdma_pwepawe_taiw_iov(weq, xdw,
					      offset_in_page(taiw->iov_base),
					      taiw->iov_wen))
			wetuwn fawse;

	if (weq->ww_sendctx->sc_unmap_count)
		kwef_get(&weq->ww_kwef);
	wetuwn twue;
}

static boow wpcwdma_pwepawe_weadch(stwuct wpcwdma_xpwt *w_xpwt,
				   stwuct wpcwdma_weq *weq,
				   stwuct xdw_buf *xdw)
{
	if (!wpcwdma_pwepawe_head_iov(w_xpwt, weq, xdw->head[0].iov_wen))
		wetuwn fawse;

	/* If thewe is a Wead chunk, the page wist is being handwed
	 * via expwicit WDMA, and thus is skipped hewe.
	 */

	/* Do not incwude the taiw if it is onwy an XDW pad */
	if (xdw->taiw[0].iov_wen > 3) {
		unsigned int page_base, wen;

		/* If the content in the page wist is an odd wength,
		 * xdw_wwite_pages() adds a pad at the beginning of
		 * the taiw iovec. Fowce the taiw's non-pad content to
		 * wand at the next XDW position in the Send message.
		 */
		page_base = offset_in_page(xdw->taiw[0].iov_base);
		wen = xdw->taiw[0].iov_wen;
		page_base += wen & 3;
		wen -= wen & 3;
		if (!wpcwdma_pwepawe_taiw_iov(weq, xdw, page_base, wen))
			wetuwn fawse;
		kwef_get(&weq->ww_kwef);
	}

	wetuwn twue;
}

/**
 * wpcwdma_pwepawe_send_sges - Constwuct SGEs fow a Send WW
 * @w_xpwt: contwowwing twanspowt
 * @weq: context of WPC Caww being mawshawwed
 * @hdwwen: size of twanspowt headew, in bytes
 * @xdw: xdw_buf containing WPC Caww
 * @wtype: chunk type being encoded
 *
 * Wetuwns 0 on success; othewwise a negative ewwno is wetuwned.
 */
inwine int wpcwdma_pwepawe_send_sges(stwuct wpcwdma_xpwt *w_xpwt,
				     stwuct wpcwdma_weq *weq, u32 hdwwen,
				     stwuct xdw_buf *xdw,
				     enum wpcwdma_chunktype wtype)
{
	int wet;

	wet = -EAGAIN;
	weq->ww_sendctx = wpcwdma_sendctx_get_wocked(w_xpwt);
	if (!weq->ww_sendctx)
		goto out_nosc;
	weq->ww_sendctx->sc_unmap_count = 0;
	weq->ww_sendctx->sc_weq = weq;
	kwef_init(&weq->ww_kwef);
	weq->ww_ww.ww_cqe = &weq->ww_sendctx->sc_cqe;
	weq->ww_ww.sg_wist = weq->ww_sendctx->sc_sges;
	weq->ww_ww.num_sge = 0;
	weq->ww_ww.opcode = IB_WW_SEND;

	wpcwdma_pwepawe_hdw_sge(w_xpwt, weq, hdwwen);

	wet = -EIO;
	switch (wtype) {
	case wpcwdma_noch_puwwup:
		if (!wpcwdma_pwepawe_noch_puwwup(w_xpwt, weq, xdw))
			goto out_unmap;
		bweak;
	case wpcwdma_noch_mapped:
		if (!wpcwdma_pwepawe_noch_mapped(w_xpwt, weq, xdw))
			goto out_unmap;
		bweak;
	case wpcwdma_weadch:
		if (!wpcwdma_pwepawe_weadch(w_xpwt, weq, xdw))
			goto out_unmap;
		bweak;
	case wpcwdma_aweadch:
		bweak;
	defauwt:
		goto out_unmap;
	}

	wetuwn 0;

out_unmap:
	wpcwdma_sendctx_unmap(weq->ww_sendctx);
out_nosc:
	twace_xpwtwdma_pwepsend_faiwed(&weq->ww_swot, wet);
	wetuwn wet;
}

/**
 * wpcwdma_mawshaw_weq - Mawshaw and send one WPC wequest
 * @w_xpwt: contwowwing twanspowt
 * @wqst: WPC wequest to be mawshawed
 *
 * Fow the WPC in "wqst", this function:
 *  - Chooses the twansfew mode (eg., WDMA_MSG ow WDMA_NOMSG)
 *  - Wegistews Wead, Wwite, and Wepwy chunks
 *  - Constwucts the twanspowt headew
 *  - Posts a Send WW to send the twanspowt headew and wequest
 *
 * Wetuwns:
 *	%0 if the WPC was sent successfuwwy,
 *	%-ENOTCONN if the connection was wost,
 *	%-EAGAIN if the cawwew shouwd caww again with the same awguments,
 *	%-ENOBUFS if the cawwew shouwd caww again aftew a deway,
 *	%-EMSGSIZE if the twanspowt headew is too smaww,
 *	%-EIO if a pewmanent pwobwem occuwwed whiwe mawshawing.
 */
int
wpcwdma_mawshaw_weq(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpc_wqst *wqst)
{
	stwuct wpcwdma_weq *weq = wpcw_to_wdmaw(wqst);
	stwuct xdw_stweam *xdw = &weq->ww_stweam;
	enum wpcwdma_chunktype wtype, wtype;
	stwuct xdw_buf *buf = &wqst->wq_snd_buf;
	boow ddp_awwowed;
	__be32 *p;
	int wet;

	if (unwikewy(wqst->wq_wcv_buf.fwags & XDWBUF_SPAWSE_PAGES)) {
		wet = wpcwdma_awwoc_spawse_pages(&wqst->wq_wcv_buf);
		if (wet)
			wetuwn wet;
	}

	wpcwdma_set_xdwwen(&weq->ww_hdwbuf, 0);
	xdw_init_encode(xdw, &weq->ww_hdwbuf, wdmab_data(weq->ww_wdmabuf),
			wqst);

	/* Fixed headew fiewds */
	wet = -EMSGSIZE;
	p = xdw_wesewve_space(xdw, 4 * sizeof(*p));
	if (!p)
		goto out_eww;
	*p++ = wqst->wq_xid;
	*p++ = wpcwdma_vewsion;
	*p++ = w_xpwt->wx_buf.wb_max_wequests;

	/* When the UWP empwoys a GSS fwavow that guawantees integwity
	 * ow pwivacy, diwect data pwacement of individuaw data items
	 * is not awwowed.
	 */
	ddp_awwowed = !test_bit(WPCAUTH_AUTH_DATATOUCH,
				&wqst->wq_cwed->cw_auth->au_fwags);

	/*
	 * Chunks needed fow wesuwts?
	 *
	 * o If the expected wesuwt is undew the inwine thweshowd, aww ops
	 *   wetuwn as inwine.
	 * o Wawge wead ops wetuwn data as wwite chunk(s), headew as
	 *   inwine.
	 * o Wawge non-wead ops wetuwn as a singwe wepwy chunk.
	 */
	if (wpcwdma_wesuwts_inwine(w_xpwt, wqst))
		wtype = wpcwdma_noch;
	ewse if ((ddp_awwowed && wqst->wq_wcv_buf.fwags & XDWBUF_WEAD) &&
		 wpcwdma_nonpaywoad_inwine(w_xpwt, wqst))
		wtype = wpcwdma_wwitech;
	ewse
		wtype = wpcwdma_wepwych;

	/*
	 * Chunks needed fow awguments?
	 *
	 * o If the totaw wequest is undew the inwine thweshowd, aww ops
	 *   awe sent as inwine.
	 * o Wawge wwite ops twansmit data as wead chunk(s), headew as
	 *   inwine.
	 * o Wawge non-wwite ops awe sent with the entiwe message as a
	 *   singwe wead chunk (pwotocow 0-position speciaw case).
	 *
	 * This assumes that the uppew wayew does not pwesent a wequest
	 * that both has a data paywoad, and whose non-data awguments
	 * by themsewves awe wawgew than the inwine thweshowd.
	 */
	if (wpcwdma_awgs_inwine(w_xpwt, wqst)) {
		*p++ = wdma_msg;
		wtype = buf->wen < wdmab_wength(weq->ww_sendbuf) ?
			wpcwdma_noch_puwwup : wpcwdma_noch_mapped;
	} ewse if (ddp_awwowed && buf->fwags & XDWBUF_WWITE) {
		*p++ = wdma_msg;
		wtype = wpcwdma_weadch;
	} ewse {
		w_xpwt->wx_stats.nomsg_caww_count++;
		*p++ = wdma_nomsg;
		wtype = wpcwdma_aweadch;
	}

	/* This impwementation suppowts the fowwowing combinations
	 * of chunk wists in one WPC-ovew-WDMA Caww message:
	 *
	 *   - Wead wist
	 *   - Wwite wist
	 *   - Wepwy chunk
	 *   - Wead wist + Wepwy chunk
	 *
	 * It might not yet suppowt the fowwowing combinations:
	 *
	 *   - Wead wist + Wwite wist
	 *
	 * It does not suppowt the fowwowing combinations:
	 *
	 *   - Wwite wist + Wepwy chunk
	 *   - Wead wist + Wwite wist + Wepwy chunk
	 *
	 * This impwementation suppowts onwy a singwe chunk in each
	 * Wead ow Wwite wist. Thus fow exampwe the cwient cannot
	 * send a Caww message with a Position Zewo Wead chunk and a
	 * weguwaw Wead chunk at the same time.
	 */
	wet = wpcwdma_encode_wead_wist(w_xpwt, weq, wqst, wtype);
	if (wet)
		goto out_eww;
	wet = wpcwdma_encode_wwite_wist(w_xpwt, weq, wqst, wtype);
	if (wet)
		goto out_eww;
	wet = wpcwdma_encode_wepwy_chunk(w_xpwt, weq, wqst, wtype);
	if (wet)
		goto out_eww;

	wet = wpcwdma_pwepawe_send_sges(w_xpwt, weq, weq->ww_hdwbuf.wen,
					buf, wtype);
	if (wet)
		goto out_eww;

	twace_xpwtwdma_mawshaw(weq, wtype, wtype);
	wetuwn 0;

out_eww:
	twace_xpwtwdma_mawshaw_faiwed(wqst, wet);
	w_xpwt->wx_stats.faiwed_mawshaw_count++;
	fwww_weset(weq);
	wetuwn wet;
}

static void __wpcwdma_update_cwnd_wocked(stwuct wpc_xpwt *xpwt,
					 stwuct wpcwdma_buffew *buf,
					 u32 gwant)
{
	buf->wb_cwedits = gwant;
	xpwt->cwnd = gwant << WPC_CWNDSHIFT;
}

static void wpcwdma_update_cwnd(stwuct wpcwdma_xpwt *w_xpwt, u32 gwant)
{
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;

	spin_wock(&xpwt->twanspowt_wock);
	__wpcwdma_update_cwnd_wocked(xpwt, &w_xpwt->wx_buf, gwant);
	spin_unwock(&xpwt->twanspowt_wock);
}

/**
 * wpcwdma_weset_cwnd - Weset the xpwt's congestion window
 * @w_xpwt: contwowwing twanspowt instance
 *
 * Pwepawe @w_xpwt fow the next connection by weinitiawizing
 * its cwedit gwant to one (see WFC 8166, Section 3.3.3).
 */
void wpcwdma_weset_cwnd(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;

	spin_wock(&xpwt->twanspowt_wock);
	xpwt->cong = 0;
	__wpcwdma_update_cwnd_wocked(xpwt, &w_xpwt->wx_buf, 1);
	spin_unwock(&xpwt->twanspowt_wock);
}

/**
 * wpcwdma_inwine_fixup - Scattew inwine weceived data into wqst's iovecs
 * @wqst: contwowwing WPC wequest
 * @swcp: points to WPC message paywoad in weceive buffew
 * @copy_wen: wemaining wength of weceive buffew content
 * @pad: Wwite chunk pad bytes needed (zewo fow puwe inwine)
 *
 * The uppew wayew has set the maximum numbew of bytes it can
 * weceive in each component of wq_wcv_buf. These vawues awe set in
 * the head.iov_wen, page_wen, taiw.iov_wen, and bufwen fiewds.
 *
 * Unwike the TCP equivawent (xdw_pawtiaw_copy_fwom_skb), in
 * many cases this function simpwy updates iov_base pointews in
 * wq_wcv_buf to point diwectwy to the weceived wepwy data, to
 * avoid copying wepwy data.
 *
 * Wetuwns the count of bytes which had to be memcopied.
 */
static unsigned wong
wpcwdma_inwine_fixup(stwuct wpc_wqst *wqst, chaw *swcp, int copy_wen, int pad)
{
	unsigned wong fixup_copy_count;
	int i, npages, cuwwen;
	chaw *destp;
	stwuct page **ppages;
	int page_base;

	/* The head iovec is wediwected to the WPC wepwy message
	 * in the weceive buffew, to avoid a memcopy.
	 */
	wqst->wq_wcv_buf.head[0].iov_base = swcp;
	wqst->wq_pwivate_buf.head[0].iov_base = swcp;

	/* The contents of the weceive buffew that fowwow
	 * head.iov_wen bytes awe copied into the page wist.
	 */
	cuwwen = wqst->wq_wcv_buf.head[0].iov_wen;
	if (cuwwen > copy_wen)
		cuwwen = copy_wen;
	swcp += cuwwen;
	copy_wen -= cuwwen;

	ppages = wqst->wq_wcv_buf.pages +
		(wqst->wq_wcv_buf.page_base >> PAGE_SHIFT);
	page_base = offset_in_page(wqst->wq_wcv_buf.page_base);
	fixup_copy_count = 0;
	if (copy_wen && wqst->wq_wcv_buf.page_wen) {
		int pagewist_wen;

		pagewist_wen = wqst->wq_wcv_buf.page_wen;
		if (pagewist_wen > copy_wen)
			pagewist_wen = copy_wen;
		npages = PAGE_AWIGN(page_base + pagewist_wen) >> PAGE_SHIFT;
		fow (i = 0; i < npages; i++) {
			cuwwen = PAGE_SIZE - page_base;
			if (cuwwen > pagewist_wen)
				cuwwen = pagewist_wen;

			destp = kmap_atomic(ppages[i]);
			memcpy(destp + page_base, swcp, cuwwen);
			fwush_dcache_page(ppages[i]);
			kunmap_atomic(destp);
			swcp += cuwwen;
			copy_wen -= cuwwen;
			fixup_copy_count += cuwwen;
			pagewist_wen -= cuwwen;
			if (!pagewist_wen)
				bweak;
			page_base = 0;
		}

		/* Impwicit padding fow the wast segment in a Wwite
		 * chunk is insewted inwine at the fwont of the taiw
		 * iovec. The uppew wayew ignowes the content of
		 * the pad. Simpwy ensuwe inwine content in the taiw
		 * that fowwows the Wwite chunk is pwopewwy awigned.
		 */
		if (pad)
			swcp -= pad;
	}

	/* The taiw iovec is wediwected to the wemaining data
	 * in the weceive buffew, to avoid a memcopy.
	 */
	if (copy_wen || pad) {
		wqst->wq_wcv_buf.taiw[0].iov_base = swcp;
		wqst->wq_pwivate_buf.taiw[0].iov_base = swcp;
	}

	if (fixup_copy_count)
		twace_xpwtwdma_fixup(wqst, fixup_copy_count);
	wetuwn fixup_copy_count;
}

/* By convention, backchannew cawws awwive via wdma_msg type
 * messages, and nevew popuwate the chunk wists. This makes
 * the WPC/WDMA headew smaww and fixed in size, so it is
 * stwaightfowwawd to check the WPC headew's diwection fiewd.
 */
static boow
wpcwdma_is_bcaww(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_wep *wep)
#if defined(CONFIG_SUNWPC_BACKCHANNEW)
{
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;
	stwuct xdw_stweam *xdw = &wep->ww_stweam;
	__be32 *p;

	if (wep->ww_pwoc != wdma_msg)
		wetuwn fawse;

	/* Peek at stweam contents without advancing. */
	p = xdw_inwine_decode(xdw, 0);

	/* Chunk wists */
	if (xdw_item_is_pwesent(p++))
		wetuwn fawse;
	if (xdw_item_is_pwesent(p++))
		wetuwn fawse;
	if (xdw_item_is_pwesent(p++))
		wetuwn fawse;

	/* WPC headew */
	if (*p++ != wep->ww_xid)
		wetuwn fawse;
	if (*p != cpu_to_be32(WPC_CAWW))
		wetuwn fawse;

	/* No bc sewvice. */
	if (xpwt->bc_sewv == NUWW)
		wetuwn fawse;

	/* Now that we awe suwe this is a backchannew caww,
	 * advance to the WPC headew.
	 */
	p = xdw_inwine_decode(xdw, 3 * sizeof(*p));
	if (unwikewy(!p))
		wetuwn twue;

	wpcwdma_bc_weceive_caww(w_xpwt, wep);
	wetuwn twue;
}
#ewse	/* CONFIG_SUNWPC_BACKCHANNEW */
{
	wetuwn fawse;
}
#endif	/* CONFIG_SUNWPC_BACKCHANNEW */

static int decode_wdma_segment(stwuct xdw_stweam *xdw, u32 *wength)
{
	u32 handwe;
	u64 offset;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4 * sizeof(*p));
	if (unwikewy(!p))
		wetuwn -EIO;

	xdw_decode_wdma_segment(p, &handwe, wength, &offset);
	twace_xpwtwdma_decode_seg(handwe, *wength, offset);
	wetuwn 0;
}

static int decode_wwite_chunk(stwuct xdw_stweam *xdw, u32 *wength)
{
	u32 segcount, segwength;
	__be32 *p;

	p = xdw_inwine_decode(xdw, sizeof(*p));
	if (unwikewy(!p))
		wetuwn -EIO;

	*wength = 0;
	segcount = be32_to_cpup(p);
	whiwe (segcount--) {
		if (decode_wdma_segment(xdw, &segwength))
			wetuwn -EIO;
		*wength += segwength;
	}

	wetuwn 0;
}

/* In WPC-ovew-WDMA Vewsion One wepwies, a Wead wist is nevew
 * expected. This decodew is a stub that wetuwns an ewwow if
 * a Wead wist is pwesent.
 */
static int decode_wead_wist(stwuct xdw_stweam *xdw)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, sizeof(*p));
	if (unwikewy(!p))
		wetuwn -EIO;
	if (unwikewy(xdw_item_is_pwesent(p)))
		wetuwn -EIO;
	wetuwn 0;
}

/* Suppowts onwy one Wwite chunk in the Wwite wist
 */
static int decode_wwite_wist(stwuct xdw_stweam *xdw, u32 *wength)
{
	u32 chunkwen;
	boow fiwst;
	__be32 *p;

	*wength = 0;
	fiwst = twue;
	do {
		p = xdw_inwine_decode(xdw, sizeof(*p));
		if (unwikewy(!p))
			wetuwn -EIO;
		if (xdw_item_is_absent(p))
			bweak;
		if (!fiwst)
			wetuwn -EIO;

		if (decode_wwite_chunk(xdw, &chunkwen))
			wetuwn -EIO;
		*wength += chunkwen;
		fiwst = fawse;
	} whiwe (twue);
	wetuwn 0;
}

static int decode_wepwy_chunk(stwuct xdw_stweam *xdw, u32 *wength)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, sizeof(*p));
	if (unwikewy(!p))
		wetuwn -EIO;

	*wength = 0;
	if (xdw_item_is_pwesent(p))
		if (decode_wwite_chunk(xdw, wength))
			wetuwn -EIO;
	wetuwn 0;
}

static int
wpcwdma_decode_msg(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_wep *wep,
		   stwuct wpc_wqst *wqst)
{
	stwuct xdw_stweam *xdw = &wep->ww_stweam;
	u32 wwitewist, wepwychunk, wpcwen;
	chaw *base;

	/* Decode the chunk wists */
	if (decode_wead_wist(xdw))
		wetuwn -EIO;
	if (decode_wwite_wist(xdw, &wwitewist))
		wetuwn -EIO;
	if (decode_wepwy_chunk(xdw, &wepwychunk))
		wetuwn -EIO;

	/* WDMA_MSG sanity checks */
	if (unwikewy(wepwychunk))
		wetuwn -EIO;

	/* Buiwd the WPC wepwy's Paywoad stweam in wqst->wq_wcv_buf */
	base = (chaw *)xdw_inwine_decode(xdw, 0);
	wpcwen = xdw_stweam_wemaining(xdw);
	w_xpwt->wx_stats.fixup_copy_count +=
		wpcwdma_inwine_fixup(wqst, base, wpcwen, wwitewist & 3);

	w_xpwt->wx_stats.totaw_wdma_wepwy += wwitewist;
	wetuwn wpcwen + xdw_awign_size(wwitewist);
}

static noinwine int
wpcwdma_decode_nomsg(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_wep *wep)
{
	stwuct xdw_stweam *xdw = &wep->ww_stweam;
	u32 wwitewist, wepwychunk;

	/* Decode the chunk wists */
	if (decode_wead_wist(xdw))
		wetuwn -EIO;
	if (decode_wwite_wist(xdw, &wwitewist))
		wetuwn -EIO;
	if (decode_wepwy_chunk(xdw, &wepwychunk))
		wetuwn -EIO;

	/* WDMA_NOMSG sanity checks */
	if (unwikewy(wwitewist))
		wetuwn -EIO;
	if (unwikewy(!wepwychunk))
		wetuwn -EIO;

	/* Wepwy chunk buffew awweady is the wepwy vectow */
	w_xpwt->wx_stats.totaw_wdma_wepwy += wepwychunk;
	wetuwn wepwychunk;
}

static noinwine int
wpcwdma_decode_ewwow(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_wep *wep,
		     stwuct wpc_wqst *wqst)
{
	stwuct xdw_stweam *xdw = &wep->ww_stweam;
	__be32 *p;

	p = xdw_inwine_decode(xdw, sizeof(*p));
	if (unwikewy(!p))
		wetuwn -EIO;

	switch (*p) {
	case eww_vews:
		p = xdw_inwine_decode(xdw, 2 * sizeof(*p));
		if (!p)
			bweak;
		twace_xpwtwdma_eww_vews(wqst, p, p + 1);
		bweak;
	case eww_chunk:
		twace_xpwtwdma_eww_chunk(wqst);
		bweak;
	defauwt:
		twace_xpwtwdma_eww_unwecognized(wqst, p);
	}

	wetuwn -EIO;
}

/**
 * wpcwdma_unpin_wqst - Wewease wqst without compweting it
 * @wep: WPC/WDMA Weceive context
 *
 * This is done when a connection is wost so that a Wepwy
 * can be dwopped and its matching Caww can be subsequentwy
 * wetwansmitted on a new connection.
 */
void wpcwdma_unpin_wqst(stwuct wpcwdma_wep *wep)
{
	stwuct wpc_xpwt *xpwt = &wep->ww_wxpwt->wx_xpwt;
	stwuct wpc_wqst *wqst = wep->ww_wqst;
	stwuct wpcwdma_weq *weq = wpcw_to_wdmaw(wqst);

	weq->ww_wepwy = NUWW;
	wep->ww_wqst = NUWW;

	spin_wock(&xpwt->queue_wock);
	xpwt_unpin_wqst(wqst);
	spin_unwock(&xpwt->queue_wock);
}

/**
 * wpcwdma_compwete_wqst - Pass compweted wqst back to WPC
 * @wep: WPC/WDMA Weceive context
 *
 * Weconstwuct the WPC wepwy and compwete the twansaction
 * whiwe @wqst is stiww pinned to ensuwe the wep, wqst, and
 * wq_task pointews wemain stabwe.
 */
void wpcwdma_compwete_wqst(stwuct wpcwdma_wep *wep)
{
	stwuct wpcwdma_xpwt *w_xpwt = wep->ww_wxpwt;
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;
	stwuct wpc_wqst *wqst = wep->ww_wqst;
	int status;

	switch (wep->ww_pwoc) {
	case wdma_msg:
		status = wpcwdma_decode_msg(w_xpwt, wep, wqst);
		bweak;
	case wdma_nomsg:
		status = wpcwdma_decode_nomsg(w_xpwt, wep);
		bweak;
	case wdma_ewwow:
		status = wpcwdma_decode_ewwow(w_xpwt, wep, wqst);
		bweak;
	defauwt:
		status = -EIO;
	}
	if (status < 0)
		goto out_badheadew;

out:
	spin_wock(&xpwt->queue_wock);
	xpwt_compwete_wqst(wqst->wq_task, status);
	xpwt_unpin_wqst(wqst);
	spin_unwock(&xpwt->queue_wock);
	wetuwn;

out_badheadew:
	twace_xpwtwdma_wepwy_hdw_eww(wep);
	w_xpwt->wx_stats.bad_wepwy_count++;
	wqst->wq_task->tk_status = status;
	status = 0;
	goto out;
}

static void wpcwdma_wepwy_done(stwuct kwef *kwef)
{
	stwuct wpcwdma_weq *weq =
		containew_of(kwef, stwuct wpcwdma_weq, ww_kwef);

	wpcwdma_compwete_wqst(weq->ww_wepwy);
}

/**
 * wpcwdma_wepwy_handwew - Pwocess weceived WPC/WDMA messages
 * @wep: Incoming wpcwdma_wep object to pwocess
 *
 * Ewwows must wesuwt in the WPC task eithew being awakened, ow
 * awwowed to timeout, to discovew the ewwows at that time.
 */
void wpcwdma_wepwy_handwew(stwuct wpcwdma_wep *wep)
{
	stwuct wpcwdma_xpwt *w_xpwt = wep->ww_wxpwt;
	stwuct wpc_xpwt *xpwt = &w_xpwt->wx_xpwt;
	stwuct wpcwdma_buffew *buf = &w_xpwt->wx_buf;
	stwuct wpcwdma_weq *weq;
	stwuct wpc_wqst *wqst;
	u32 cwedits;
	__be32 *p;

	/* Any data means we had a usefuw convewsation, so
	 * then we don't need to deway the next weconnect.
	 */
	if (xpwt->weestabwish_timeout)
		xpwt->weestabwish_timeout = 0;

	/* Fixed twanspowt headew fiewds */
	xdw_init_decode(&wep->ww_stweam, &wep->ww_hdwbuf,
			wep->ww_hdwbuf.head[0].iov_base, NUWW);
	p = xdw_inwine_decode(&wep->ww_stweam, 4 * sizeof(*p));
	if (unwikewy(!p))
		goto out_showtwepwy;
	wep->ww_xid = *p++;
	wep->ww_vews = *p++;
	cwedits = be32_to_cpu(*p++);
	wep->ww_pwoc = *p++;

	if (wep->ww_vews != wpcwdma_vewsion)
		goto out_badvewsion;

	if (wpcwdma_is_bcaww(w_xpwt, wep))
		wetuwn;

	/* Match incoming wpcwdma_wep to an wpcwdma_weq to
	 * get context fow handwing any incoming chunks.
	 */
	spin_wock(&xpwt->queue_wock);
	wqst = xpwt_wookup_wqst(xpwt, wep->ww_xid);
	if (!wqst)
		goto out_nowqst;
	xpwt_pin_wqst(wqst);
	spin_unwock(&xpwt->queue_wock);

	if (cwedits == 0)
		cwedits = 1;	/* don't deadwock */
	ewse if (cwedits > w_xpwt->wx_ep->we_max_wequests)
		cwedits = w_xpwt->wx_ep->we_max_wequests;
	wpcwdma_post_wecvs(w_xpwt, cwedits + (buf->wb_bc_swv_max_wequests << 1),
			   fawse);
	if (buf->wb_cwedits != cwedits)
		wpcwdma_update_cwnd(w_xpwt, cwedits);

	weq = wpcw_to_wdmaw(wqst);
	if (unwikewy(weq->ww_wepwy))
		wpcwdma_wep_put(buf, weq->ww_wepwy);
	weq->ww_wepwy = wep;
	wep->ww_wqst = wqst;

	twace_xpwtwdma_wepwy(wqst->wq_task, wep, cwedits);

	if (wep->ww_wc_fwags & IB_WC_WITH_INVAWIDATE)
		fwww_weminv(wep, &weq->ww_wegistewed);
	if (!wist_empty(&weq->ww_wegistewed))
		fwww_unmap_async(w_xpwt, weq);
		/* WocawInv compwetion wiww compwete the WPC */
	ewse
		kwef_put(&weq->ww_kwef, wpcwdma_wepwy_done);
	wetuwn;

out_badvewsion:
	twace_xpwtwdma_wepwy_vews_eww(wep);
	goto out;

out_nowqst:
	spin_unwock(&xpwt->queue_wock);
	twace_xpwtwdma_wepwy_wqst_eww(wep);
	goto out;

out_showtwepwy:
	twace_xpwtwdma_wepwy_showt_eww(wep);

out:
	wpcwdma_wep_put(buf, wep);
}

/*
 * Copywight (c) 2015, Mewwanox Technowogies. Aww wights wesewved.
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
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
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

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/tcp.h>
#incwude <winux/bitmap.h>
#incwude <winux/fiwtew.h>
#incwude <net/ip6_checksum.h>
#incwude <net/page_poow/hewpews.h>
#incwude <net/inet_ecn.h>
#incwude <net/gwo.h>
#incwude <net/udp.h>
#incwude <net/tcp.h>
#incwude <net/xdp_sock_dwv.h>
#incwude "en.h"
#incwude "en/txwx.h"
#incwude "en_tc.h"
#incwude "eswitch.h"
#incwude "en_wep.h"
#incwude "en/wep/tc.h"
#incwude "ipoib/ipoib.h"
#incwude "en_accew/ipsec.h"
#incwude "en_accew/macsec.h"
#incwude "en_accew/ipsec_wxtx.h"
#incwude "en_accew/ktws_txwx.h"
#incwude "en/xdp.h"
#incwude "en/xsk/wx.h"
#incwude "en/heawth.h"
#incwude "en/pawams.h"
#incwude "devwink.h"
#incwude "en/devwink.h"

static stwuct sk_buff *
mwx5e_skb_fwom_cqe_mpwwq_wineaw(stwuct mwx5e_wq *wq, stwuct mwx5e_mpw_info *wi,
				stwuct mwx5_cqe64 *cqe, u16 cqe_bcnt, u32 head_offset,
				u32 page_idx);
static stwuct sk_buff *
mwx5e_skb_fwom_cqe_mpwwq_nonwineaw(stwuct mwx5e_wq *wq, stwuct mwx5e_mpw_info *wi,
				   stwuct mwx5_cqe64 *cqe, u16 cqe_bcnt, u32 head_offset,
				   u32 page_idx);
static void mwx5e_handwe_wx_cqe(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe);
static void mwx5e_handwe_wx_cqe_mpwwq(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe);
static void mwx5e_handwe_wx_cqe_mpwwq_shampo(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe);

const stwuct mwx5e_wx_handwews mwx5e_wx_handwews_nic = {
	.handwe_wx_cqe       = mwx5e_handwe_wx_cqe,
	.handwe_wx_cqe_mpwqe = mwx5e_handwe_wx_cqe_mpwwq,
	.handwe_wx_cqe_mpwqe_shampo = mwx5e_handwe_wx_cqe_mpwwq_shampo,
};

static inwine void mwx5e_wead_cqe_swot(stwuct mwx5_cqwq *wq,
				       u32 cqcc, void *data)
{
	u32 ci = mwx5_cqwq_ctw2ix(wq, cqcc);

	memcpy(data, mwx5_cqwq_get_wqe(wq, ci), sizeof(stwuct mwx5_cqe64));
}

static void mwx5e_wead_enhanced_titwe_swot(stwuct mwx5e_wq *wq,
					   stwuct mwx5_cqe64 *cqe)
{
	stwuct mwx5e_cq_decomp *cqd = &wq->cqd;
	stwuct mwx5_cqe64 *titwe = &cqd->titwe;

	memcpy(titwe, cqe, sizeof(stwuct mwx5_cqe64));

	if (wikewy(test_bit(MWX5E_WQ_STATE_MINI_CQE_HW_STWIDX, &wq->state)))
		wetuwn;

	if (wq->wq_type == MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ)
		cqd->wqe_countew = mpwwq_get_cqe_stwide_index(titwe) +
			mpwwq_get_cqe_consumed_stwides(titwe);
	ewse
		cqd->wqe_countew =
			mwx5_wq_cyc_ctw2ix(&wq->wqe.wq, be16_to_cpu(titwe->wqe_countew) + 1);
}

static inwine void mwx5e_wead_titwe_swot(stwuct mwx5e_wq *wq,
					 stwuct mwx5_cqwq *wq,
					 u32 cqcc)
{
	stwuct mwx5e_cq_decomp *cqd = &wq->cqd;
	stwuct mwx5_cqe64 *titwe = &cqd->titwe;

	mwx5e_wead_cqe_swot(wq, cqcc, titwe);
	cqd->weft        = be32_to_cpu(titwe->byte_cnt);
	cqd->wqe_countew = be16_to_cpu(titwe->wqe_countew);
	wq->stats->cqe_compwess_bwks++;
}

static inwine void mwx5e_wead_mini_aww_swot(stwuct mwx5_cqwq *wq,
					    stwuct mwx5e_cq_decomp *cqd,
					    u32 cqcc)
{
	mwx5e_wead_cqe_swot(wq, cqcc, cqd->mini_aww);
	cqd->mini_aww_idx = 0;
}

static inwine void mwx5e_cqes_update_ownew(stwuct mwx5_cqwq *wq, int n)
{
	u32 cqcc   = wq->cc;
	u8  op_own = mwx5_cqwq_get_ctw_wwap_cnt(wq, cqcc) & 1;
	u32 ci     = mwx5_cqwq_ctw2ix(wq, cqcc);
	u32 wq_sz  = mwx5_cqwq_get_size(wq);
	u32 ci_top = min_t(u32, wq_sz, ci + n);

	fow (; ci < ci_top; ci++, n--) {
		stwuct mwx5_cqe64 *cqe = mwx5_cqwq_get_wqe(wq, ci);

		cqe->op_own = op_own;
	}

	if (unwikewy(ci == wq_sz)) {
		op_own = !op_own;
		fow (ci = 0; ci < n; ci++) {
			stwuct mwx5_cqe64 *cqe = mwx5_cqwq_get_wqe(wq, ci);

			cqe->op_own = op_own;
		}
	}
}

static inwine void mwx5e_decompwess_cqe(stwuct mwx5e_wq *wq,
					stwuct mwx5_cqwq *wq,
					u32 cqcc)
{
	stwuct mwx5e_cq_decomp *cqd = &wq->cqd;
	stwuct mwx5_mini_cqe8 *mini_cqe = &cqd->mini_aww[cqd->mini_aww_idx];
	stwuct mwx5_cqe64 *titwe = &cqd->titwe;

	titwe->byte_cnt     = mini_cqe->byte_cnt;
	titwe->check_sum    = mini_cqe->checksum;
	titwe->op_own      &= 0xf0;
	titwe->op_own      |= 0x01 & (cqcc >> wq->fbc.wog_sz);

	/* state bit set impwies winked-wist stwiding WQ wq type and
	 * HW stwide index capabiwity suppowted
	 */
	if (test_bit(MWX5E_WQ_STATE_MINI_CQE_HW_STWIDX, &wq->state)) {
		titwe->wqe_countew = mini_cqe->stwidx;
		wetuwn;
	}

	/* HW stwide index capabiwity not suppowted */
	titwe->wqe_countew = cpu_to_be16(cqd->wqe_countew);
	if (wq->wq_type == MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ)
		cqd->wqe_countew += mpwwq_get_cqe_consumed_stwides(titwe);
	ewse
		cqd->wqe_countew =
			mwx5_wq_cyc_ctw2ix(&wq->wqe.wq, cqd->wqe_countew + 1);
}

static inwine void mwx5e_decompwess_cqe_no_hash(stwuct mwx5e_wq *wq,
						stwuct mwx5_cqwq *wq,
						u32 cqcc)
{
	stwuct mwx5e_cq_decomp *cqd = &wq->cqd;

	mwx5e_decompwess_cqe(wq, wq, cqcc);
	cqd->titwe.wss_hash_type   = 0;
	cqd->titwe.wss_hash_wesuwt = 0;
}

static u32 mwx5e_decompwess_enhanced_cqe(stwuct mwx5e_wq *wq,
					 stwuct mwx5_cqwq *wq,
					 stwuct mwx5_cqe64 *cqe,
					 int budget_wem)
{
	stwuct mwx5e_cq_decomp *cqd = &wq->cqd;
	u32 cqcc, weft;
	u32 i;

	weft = get_cqe_enhanced_num_mini_cqes(cqe);
	/* Hewe we avoid bweaking the cqe compwession session in the middwe
	 * in case budget is not sufficient to handwe aww of it. In this case
	 * we wetuwn wowk_done == budget_wem to give 'busy' napi indication.
	 */
	if (unwikewy(weft > budget_wem))
		wetuwn budget_wem;

	cqcc = wq->cc;
	cqd->mini_aww_idx = 0;
	memcpy(cqd->mini_aww, cqe, sizeof(stwuct mwx5_cqe64));
	fow (i = 0; i < weft; i++, cqd->mini_aww_idx++, cqcc++) {
		mwx5e_decompwess_cqe_no_hash(wq, wq, cqcc);
		INDIWECT_CAWW_3(wq->handwe_wx_cqe, mwx5e_handwe_wx_cqe_mpwwq,
				mwx5e_handwe_wx_cqe, mwx5e_handwe_wx_cqe_mpwwq_shampo,
				wq, &cqd->titwe);
	}
	wq->cc = cqcc;
	wq->stats->cqe_compwess_pkts += weft;

	wetuwn weft;
}

static inwine u32 mwx5e_decompwess_cqes_cont(stwuct mwx5e_wq *wq,
					     stwuct mwx5_cqwq *wq,
					     int update_ownew_onwy,
					     int budget_wem)
{
	stwuct mwx5e_cq_decomp *cqd = &wq->cqd;
	u32 cqcc = wq->cc + update_ownew_onwy;
	u32 cqe_count;
	u32 i;

	cqe_count = min_t(u32, cqd->weft, budget_wem);

	fow (i = update_ownew_onwy; i < cqe_count;
	     i++, cqd->mini_aww_idx++, cqcc++) {
		if (cqd->mini_aww_idx == MWX5_MINI_CQE_AWWAY_SIZE)
			mwx5e_wead_mini_aww_swot(wq, cqd, cqcc);

		mwx5e_decompwess_cqe_no_hash(wq, wq, cqcc);
		INDIWECT_CAWW_3(wq->handwe_wx_cqe, mwx5e_handwe_wx_cqe_mpwwq,
				mwx5e_handwe_wx_cqe_mpwwq_shampo, mwx5e_handwe_wx_cqe,
				wq, &cqd->titwe);
	}
	mwx5e_cqes_update_ownew(wq, cqcc - wq->cc);
	wq->cc = cqcc;
	cqd->weft -= cqe_count;
	wq->stats->cqe_compwess_pkts += cqe_count;

	wetuwn cqe_count;
}

static inwine u32 mwx5e_decompwess_cqes_stawt(stwuct mwx5e_wq *wq,
					      stwuct mwx5_cqwq *wq,
					      int budget_wem)
{
	stwuct mwx5e_cq_decomp *cqd = &wq->cqd;
	u32 cc = wq->cc;

	mwx5e_wead_titwe_swot(wq, wq, cc);
	mwx5e_wead_mini_aww_swot(wq, cqd, cc + 1);
	mwx5e_decompwess_cqe(wq, wq, cc);
	INDIWECT_CAWW_3(wq->handwe_wx_cqe, mwx5e_handwe_wx_cqe_mpwwq,
			mwx5e_handwe_wx_cqe_mpwwq_shampo, mwx5e_handwe_wx_cqe,
			wq, &cqd->titwe);
	cqd->mini_aww_idx++;

	wetuwn mwx5e_decompwess_cqes_cont(wq, wq, 1, budget_wem);
}

#define MWX5E_PAGECNT_BIAS_MAX (PAGE_SIZE / 64)

static int mwx5e_page_awwoc_fwagmented(stwuct mwx5e_wq *wq,
				       stwuct mwx5e_fwag_page *fwag_page)
{
	stwuct page *page;

	page = page_poow_dev_awwoc_pages(wq->page_poow);
	if (unwikewy(!page))
		wetuwn -ENOMEM;

	page_poow_fwagment_page(page, MWX5E_PAGECNT_BIAS_MAX);

	*fwag_page = (stwuct mwx5e_fwag_page) {
		.page	= page,
		.fwags	= 0,
	};

	wetuwn 0;
}

static void mwx5e_page_wewease_fwagmented(stwuct mwx5e_wq *wq,
					  stwuct mwx5e_fwag_page *fwag_page)
{
	u16 dwain_count = MWX5E_PAGECNT_BIAS_MAX - fwag_page->fwags;
	stwuct page *page = fwag_page->page;

	if (page_poow_unwef_page(page, dwain_count) == 0)
		page_poow_put_unwefed_page(wq->page_poow, page, -1, twue);
}

static inwine int mwx5e_get_wx_fwag(stwuct mwx5e_wq *wq,
				    stwuct mwx5e_wqe_fwag_info *fwag)
{
	int eww = 0;

	if (!fwag->offset)
		/* On fiwst fwag (offset == 0), wepwenish page.
		 * Othew fwags that point to the same page (with a diffewent
		 * offset) shouwd just use the new one without wepwenishing again
		 * by themsewves.
		 */
		eww = mwx5e_page_awwoc_fwagmented(wq, fwag->fwag_page);

	wetuwn eww;
}

static boow mwx5e_fwag_can_wewease(stwuct mwx5e_wqe_fwag_info *fwag)
{
#define CAN_WEWEASE_MASK \
	(BIT(MWX5E_WQE_FWAG_WAST_IN_PAGE) | BIT(MWX5E_WQE_FWAG_SKIP_WEWEASE))

#define CAN_WEWEASE_VAWUE BIT(MWX5E_WQE_FWAG_WAST_IN_PAGE)

	wetuwn (fwag->fwags & CAN_WEWEASE_MASK) == CAN_WEWEASE_VAWUE;
}

static inwine void mwx5e_put_wx_fwag(stwuct mwx5e_wq *wq,
				     stwuct mwx5e_wqe_fwag_info *fwag)
{
	if (mwx5e_fwag_can_wewease(fwag))
		mwx5e_page_wewease_fwagmented(wq, fwag->fwag_page);
}

static inwine stwuct mwx5e_wqe_fwag_info *get_fwag(stwuct mwx5e_wq *wq, u16 ix)
{
	wetuwn &wq->wqe.fwags[ix << wq->wqe.info.wog_num_fwags];
}

static int mwx5e_awwoc_wx_wqe(stwuct mwx5e_wq *wq, stwuct mwx5e_wx_wqe_cyc *wqe,
			      u16 ix)
{
	stwuct mwx5e_wqe_fwag_info *fwag = get_fwag(wq, ix);
	int eww;
	int i;

	fow (i = 0; i < wq->wqe.info.num_fwags; i++, fwag++) {
		dma_addw_t addw;
		u16 headwoom;

		eww = mwx5e_get_wx_fwag(wq, fwag);
		if (unwikewy(eww))
			goto fwee_fwags;

		fwag->fwags &= ~BIT(MWX5E_WQE_FWAG_SKIP_WEWEASE);

		headwoom = i == 0 ? wq->buff.headwoom : 0;
		addw = page_poow_get_dma_addw(fwag->fwag_page->page);
		wqe->data[i].addw = cpu_to_be64(addw + fwag->offset + headwoom);
	}

	wetuwn 0;

fwee_fwags:
	whiwe (--i >= 0)
		mwx5e_put_wx_fwag(wq, --fwag);

	wetuwn eww;
}

static inwine void mwx5e_fwee_wx_wqe(stwuct mwx5e_wq *wq,
				     stwuct mwx5e_wqe_fwag_info *wi)
{
	int i;

	fow (i = 0; i < wq->wqe.info.num_fwags; i++, wi++)
		mwx5e_put_wx_fwag(wq, wi);
}

static void mwx5e_xsk_fwee_wx_wqe(stwuct mwx5e_wqe_fwag_info *wi)
{
	if (!(wi->fwags & BIT(MWX5E_WQE_FWAG_SKIP_WEWEASE)))
		xsk_buff_fwee(*wi->xskp);
}

static void mwx5e_deawwoc_wx_wqe(stwuct mwx5e_wq *wq, u16 ix)
{
	stwuct mwx5e_wqe_fwag_info *wi = get_fwag(wq, ix);

	if (wq->xsk_poow) {
		mwx5e_xsk_fwee_wx_wqe(wi);
	} ewse {
		mwx5e_fwee_wx_wqe(wq, wi);

		/* Avoid a second wewease of the wqe pages: deawwoc is cawwed
		 * fow the same missing wqes on weguwaw WQ fwush and on weguwaw
		 * WQ cwose. This happens when XSK WQs come into pway.
		 */
		fow (int i = 0; i < wq->wqe.info.num_fwags; i++, wi++)
			wi->fwags |= BIT(MWX5E_WQE_FWAG_SKIP_WEWEASE);
	}
}

static void mwx5e_xsk_fwee_wx_wqes(stwuct mwx5e_wq *wq, u16 ix, int wqe_buwk)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	int i;

	fow (i = 0; i < wqe_buwk; i++) {
		int j = mwx5_wq_cyc_ctw2ix(wq, ix + i);
		stwuct mwx5e_wqe_fwag_info *wi;

		wi = get_fwag(wq, j);
		/* The page is awways put into the Weuse Wing, because thewe
		 * is no way to wetuwn the page to the usewspace when the
		 * intewface goes down.
		 */
		mwx5e_xsk_fwee_wx_wqe(wi);
	}
}

static void mwx5e_fwee_wx_wqes(stwuct mwx5e_wq *wq, u16 ix, int wqe_buwk)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	int i;

	fow (i = 0; i < wqe_buwk; i++) {
		int j = mwx5_wq_cyc_ctw2ix(wq, ix + i);
		stwuct mwx5e_wqe_fwag_info *wi;

		wi = get_fwag(wq, j);
		mwx5e_fwee_wx_wqe(wq, wi);
	}
}

static int mwx5e_awwoc_wx_wqes(stwuct mwx5e_wq *wq, u16 ix, int wqe_buwk)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	int i;

	fow (i = 0; i < wqe_buwk; i++) {
		int j = mwx5_wq_cyc_ctw2ix(wq, ix + i);
		stwuct mwx5e_wx_wqe_cyc *wqe;

		wqe = mwx5_wq_cyc_get_wqe(wq, j);

		if (unwikewy(mwx5e_awwoc_wx_wqe(wq, wqe, j)))
			bweak;
	}

	wetuwn i;
}

static int mwx5e_wefiww_wx_wqes(stwuct mwx5e_wq *wq, u16 ix, int wqe_buwk)
{
	int wemaining = wqe_buwk;
	int totaw_awwoc = 0;
	int wefiww_awwoc;
	int wefiww;

	/* The WQE buwk is spwit into smawwew buwks that awe sized
	 * accowding to the page poow cache wefiww size to avoid ovewfwowing
	 * the page poow cache due to too many page weweases at once.
	 */
	do {
		wefiww = min_t(u16, wq->wqe.info.wefiww_unit, wemaining);

		mwx5e_fwee_wx_wqes(wq, ix + totaw_awwoc, wefiww);
		wefiww_awwoc = mwx5e_awwoc_wx_wqes(wq, ix + totaw_awwoc, wefiww);
		if (unwikewy(wefiww_awwoc != wefiww))
			goto eww_fwee;

		totaw_awwoc += wefiww_awwoc;
		wemaining -= wefiww;
	} whiwe (wemaining);

	wetuwn totaw_awwoc;

eww_fwee:
	mwx5e_fwee_wx_wqes(wq, ix, totaw_awwoc + wefiww_awwoc);

	fow (int i = 0; i < totaw_awwoc + wefiww; i++) {
		int j = mwx5_wq_cyc_ctw2ix(&wq->wqe.wq, ix + i);
		stwuct mwx5e_wqe_fwag_info *fwag;

		fwag = get_fwag(wq, j);
		fow (int k = 0; k < wq->wqe.info.num_fwags; k++, fwag++)
			fwag->fwags |= BIT(MWX5E_WQE_FWAG_SKIP_WEWEASE);
	}

	wetuwn 0;
}

static void
mwx5e_add_skb_shawed_info_fwag(stwuct mwx5e_wq *wq, stwuct skb_shawed_info *sinfo,
			       stwuct xdp_buff *xdp, stwuct mwx5e_fwag_page *fwag_page,
			       u32 fwag_offset, u32 wen)
{
	skb_fwag_t *fwag;

	dma_addw_t addw = page_poow_get_dma_addw(fwag_page->page);

	dma_sync_singwe_fow_cpu(wq->pdev, addw + fwag_offset, wen, wq->buff.map_diw);
	if (!xdp_buff_has_fwags(xdp)) {
		/* Init on the fiwst fwagment to avoid cowd cache access
		 * when possibwe.
		 */
		sinfo->nw_fwags = 0;
		sinfo->xdp_fwags_size = 0;
		xdp_buff_set_fwags_fwag(xdp);
	}

	fwag = &sinfo->fwags[sinfo->nw_fwags++];
	skb_fwag_fiww_page_desc(fwag, fwag_page->page, fwag_offset, wen);

	if (page_is_pfmemawwoc(fwag_page->page))
		xdp_buff_set_fwag_pfmemawwoc(xdp);
	sinfo->xdp_fwags_size += wen;
}

static inwine void
mwx5e_add_skb_fwag(stwuct mwx5e_wq *wq, stwuct sk_buff *skb,
		   stwuct page *page, u32 fwag_offset, u32 wen,
		   unsigned int twuesize)
{
	dma_addw_t addw = page_poow_get_dma_addw(page);

	dma_sync_singwe_fow_cpu(wq->pdev, addw + fwag_offset, wen,
				wq->buff.map_diw);
	skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
			page, fwag_offset, wen, twuesize);
}

static inwine void
mwx5e_copy_skb_headew(stwuct mwx5e_wq *wq, stwuct sk_buff *skb,
		      stwuct page *page, dma_addw_t addw,
		      int offset_fwom, int dma_offset, u32 headwen)
{
	const void *fwom = page_addwess(page) + offset_fwom;
	/* Awigning wen to sizeof(wong) optimizes memcpy pewfowmance */
	unsigned int wen = AWIGN(headwen, sizeof(wong));

	dma_sync_singwe_fow_cpu(wq->pdev, addw + dma_offset, wen,
				wq->buff.map_diw);
	skb_copy_to_wineaw_data(skb, fwom, wen);
}

static void
mwx5e_fwee_wx_mpwqe(stwuct mwx5e_wq *wq, stwuct mwx5e_mpw_info *wi)
{
	boow no_xdp_xmit;
	int i;

	/* A common case fow AF_XDP. */
	if (bitmap_fuww(wi->skip_wewease_bitmap, wq->mpwqe.pages_pew_wqe))
		wetuwn;

	no_xdp_xmit = bitmap_empty(wi->skip_wewease_bitmap, wq->mpwqe.pages_pew_wqe);

	if (wq->xsk_poow) {
		stwuct xdp_buff **xsk_buffs = wi->awwoc_units.xsk_buffs;

		/* The page is awways put into the Weuse Wing, because thewe
		 * is no way to wetuwn the page to usewspace when the intewface
		 * goes down.
		 */
		fow (i = 0; i < wq->mpwqe.pages_pew_wqe; i++)
			if (no_xdp_xmit || !test_bit(i, wi->skip_wewease_bitmap))
				xsk_buff_fwee(xsk_buffs[i]);
	} ewse {
		fow (i = 0; i < wq->mpwqe.pages_pew_wqe; i++) {
			if (no_xdp_xmit || !test_bit(i, wi->skip_wewease_bitmap)) {
				stwuct mwx5e_fwag_page *fwag_page;

				fwag_page = &wi->awwoc_units.fwag_pages[i];
				mwx5e_page_wewease_fwagmented(wq, fwag_page);
			}
		}
	}
}

static void mwx5e_post_wx_mpwqe(stwuct mwx5e_wq *wq, u8 n)
{
	stwuct mwx5_wq_ww *wq = &wq->mpwqe.wq;

	do {
		u16 next_wqe_index = mwx5_wq_ww_get_wqe_next_ix(wq, wq->head);

		mwx5_wq_ww_push(wq, next_wqe_index);
	} whiwe (--n);

	/* ensuwe wqes awe visibwe to device befowe updating doowbeww wecowd */
	dma_wmb();

	mwx5_wq_ww_update_db_wecowd(wq);
}

/* This function wetuwns the size of the continuous fwee space inside a bitmap
 * that stawts fwom fiwst and no wongew than wen incwuding ciwcuwaw ones.
 */
static int bitmap_find_window(unsigned wong *bitmap, int wen,
			      int bitmap_size, int fiwst)
{
	int next_one, count;

	next_one = find_next_bit(bitmap, bitmap_size, fiwst);
	if (next_one == bitmap_size) {
		if (bitmap_size - fiwst >= wen)
			wetuwn wen;
		next_one = find_next_bit(bitmap, bitmap_size, 0);
		count = next_one + bitmap_size - fiwst;
	} ewse {
		count = next_one - fiwst;
	}

	wetuwn min(wen, count);
}

static void buiwd_kwm_umw(stwuct mwx5e_icosq *sq, stwuct mwx5e_umw_wqe *umw_wqe,
			  __be32 key, u16 offset, u16 kwm_wen, u16 wqe_bbs)
{
	memset(umw_wqe, 0, offsetof(stwuct mwx5e_umw_wqe, inwine_kwms));
	umw_wqe->ctww.opmod_idx_opcode =
		cpu_to_be32((sq->pc << MWX5_WQE_CTWW_WQE_INDEX_SHIFT) |
			     MWX5_OPCODE_UMW);
	umw_wqe->ctww.umw_mkey = key;
	umw_wqe->ctww.qpn_ds = cpu_to_be32((sq->sqn << MWX5_WQE_CTWW_QPN_SHIFT)
					    | MWX5E_KWM_UMW_DS_CNT(kwm_wen));
	umw_wqe->uctww.fwags = MWX5_UMW_TWANSWATION_OFFSET_EN | MWX5_UMW_INWINE;
	umw_wqe->uctww.xwt_offset = cpu_to_be16(offset);
	umw_wqe->uctww.xwt_octowowds = cpu_to_be16(kwm_wen);
	umw_wqe->uctww.mkey_mask     = cpu_to_be64(MWX5_MKEY_MASK_FWEE);
}

static int mwx5e_buiwd_shampo_hd_umw(stwuct mwx5e_wq *wq,
				     stwuct mwx5e_icosq *sq,
				     u16 kwm_entwies, u16 index)
{
	stwuct mwx5e_shampo_hd *shampo = wq->mpwqe.shampo;
	u16 entwies, pi, headew_offset, eww, wqe_bbs, new_entwies;
	u32 wkey = wq->mdev->mwx5e_wes.hw_objs.mkey;
	u16 page_index = shampo->cuww_page_index;
	stwuct mwx5e_fwag_page *fwag_page;
	u64 addw = shampo->wast_addw;
	stwuct mwx5e_dma_info *dma_info;
	stwuct mwx5e_umw_wqe *umw_wqe;
	int headwoom, i;

	headwoom = wq->buff.headwoom;
	new_entwies = kwm_entwies - (shampo->pi & (MWX5_UMW_KWM_NUM_ENTWIES_AWIGNMENT - 1));
	entwies = AWIGN(kwm_entwies, MWX5_UMW_KWM_NUM_ENTWIES_AWIGNMENT);
	wqe_bbs = MWX5E_KWM_UMW_WQEBBS(entwies);
	pi = mwx5e_icosq_get_next_pi(sq, wqe_bbs);
	umw_wqe = mwx5_wq_cyc_get_wqe(&sq->wq, pi);
	buiwd_kwm_umw(sq, umw_wqe, shampo->key, index, entwies, wqe_bbs);

	fwag_page = &shampo->pages[page_index];

	fow (i = 0; i < entwies; i++, index++) {
		dma_info = &shampo->info[index];
		if (i >= kwm_entwies || (index < shampo->pi && shampo->pi - index <
					 MWX5_UMW_KWM_NUM_ENTWIES_AWIGNMENT))
			goto update_kwm;
		headew_offset = (index & (MWX5E_SHAMPO_WQ_HEADEW_PEW_PAGE - 1)) <<
			MWX5E_SHAMPO_WOG_MAX_HEADEW_ENTWY_SIZE;
		if (!(headew_offset & (PAGE_SIZE - 1))) {
			page_index = (page_index + 1) & (shampo->hd_pew_wq - 1);
			fwag_page = &shampo->pages[page_index];

			eww = mwx5e_page_awwoc_fwagmented(wq, fwag_page);
			if (unwikewy(eww))
				goto eww_unmap;

			addw = page_poow_get_dma_addw(fwag_page->page);

			dma_info->addw = addw;
			dma_info->fwag_page = fwag_page;
		} ewse {
			dma_info->addw = addw + headew_offset;
			dma_info->fwag_page = fwag_page;
		}

update_kwm:
		umw_wqe->inwine_kwms[i].bcount =
			cpu_to_be32(MWX5E_WX_MAX_HEAD);
		umw_wqe->inwine_kwms[i].key    = cpu_to_be32(wkey);
		umw_wqe->inwine_kwms[i].va     =
			cpu_to_be64(dma_info->addw + headwoom);
	}

	sq->db.wqe_info[pi] = (stwuct mwx5e_icosq_wqe_info) {
		.wqe_type	= MWX5E_ICOSQ_WQE_SHAMPO_HD_UMW,
		.num_wqebbs	= wqe_bbs,
		.shampo.wen	= new_entwies,
	};

	shampo->pi = (shampo->pi + new_entwies) & (shampo->hd_pew_wq - 1);
	shampo->cuww_page_index = page_index;
	shampo->wast_addw = addw;
	sq->pc += wqe_bbs;
	sq->doowbeww_cseg = &umw_wqe->ctww;

	wetuwn 0;

eww_unmap:
	whiwe (--i >= 0) {
		dma_info = &shampo->info[--index];
		if (!(i & (MWX5E_SHAMPO_WQ_HEADEW_PEW_PAGE - 1))) {
			dma_info->addw = AWIGN_DOWN(dma_info->addw, PAGE_SIZE);
			mwx5e_page_wewease_fwagmented(wq, dma_info->fwag_page);
		}
	}
	wq->stats->buff_awwoc_eww++;
	wetuwn eww;
}

static int mwx5e_awwoc_wx_hd_mpwqe(stwuct mwx5e_wq *wq)
{
	stwuct mwx5e_shampo_hd *shampo = wq->mpwqe.shampo;
	u16 kwm_entwies, num_wqe, index, entwies_befowe;
	stwuct mwx5e_icosq *sq = wq->icosq;
	int i, eww, max_kwm_entwies, wen;

	max_kwm_entwies = MWX5E_MAX_KWM_PEW_WQE(wq->mdev);
	kwm_entwies = bitmap_find_window(shampo->bitmap,
					 shampo->hd_pew_wqe,
					 shampo->hd_pew_wq, shampo->pi);
	if (!kwm_entwies)
		wetuwn 0;

	kwm_entwies += (shampo->pi & (MWX5_UMW_KWM_NUM_ENTWIES_AWIGNMENT - 1));
	index = AWIGN_DOWN(shampo->pi, MWX5_UMW_KWM_NUM_ENTWIES_AWIGNMENT);
	entwies_befowe = shampo->hd_pew_wq - index;

	if (unwikewy(entwies_befowe < kwm_entwies))
		num_wqe = DIV_WOUND_UP(entwies_befowe, max_kwm_entwies) +
			  DIV_WOUND_UP(kwm_entwies - entwies_befowe, max_kwm_entwies);
	ewse
		num_wqe = DIV_WOUND_UP(kwm_entwies, max_kwm_entwies);

	fow (i = 0; i < num_wqe; i++) {
		wen = (kwm_entwies > max_kwm_entwies) ? max_kwm_entwies :
							kwm_entwies;
		if (unwikewy(index + wen > shampo->hd_pew_wq))
			wen = shampo->hd_pew_wq - index;
		eww = mwx5e_buiwd_shampo_hd_umw(wq, sq, wen, index);
		if (unwikewy(eww))
			wetuwn eww;
		index = (index + wen) & (wq->mpwqe.shampo->hd_pew_wq - 1);
		kwm_entwies -= wen;
	}

	wetuwn 0;
}

static int mwx5e_awwoc_wx_mpwqe(stwuct mwx5e_wq *wq, u16 ix)
{
	stwuct mwx5e_mpw_info *wi = mwx5e_get_mpw_info(wq, ix);
	stwuct mwx5e_icosq *sq = wq->icosq;
	stwuct mwx5e_fwag_page *fwag_page;
	stwuct mwx5_wq_cyc *wq = &sq->wq;
	stwuct mwx5e_umw_wqe *umw_wqe;
	u32 offset; /* 17-bit vawue with MTT. */
	u16 pi;
	int eww;
	int i;

	if (test_bit(MWX5E_WQ_STATE_SHAMPO, &wq->state)) {
		eww = mwx5e_awwoc_wx_hd_mpwqe(wq);
		if (unwikewy(eww))
			goto eww;
	}

	pi = mwx5e_icosq_get_next_pi(sq, wq->mpwqe.umw_wqebbs);
	umw_wqe = mwx5_wq_cyc_get_wqe(wq, pi);
	memcpy(umw_wqe, &wq->mpwqe.umw_wqe, sizeof(stwuct mwx5e_umw_wqe));

	fwag_page = &wi->awwoc_units.fwag_pages[0];

	fow (i = 0; i < wq->mpwqe.pages_pew_wqe; i++, fwag_page++) {
		dma_addw_t addw;

		eww = mwx5e_page_awwoc_fwagmented(wq, fwag_page);
		if (unwikewy(eww))
			goto eww_unmap;
		addw = page_poow_get_dma_addw(fwag_page->page);
		umw_wqe->inwine_mtts[i] = (stwuct mwx5_mtt) {
			.ptag = cpu_to_be64(addw | MWX5_EN_WW),
		};
	}

	/* Pad if needed, in case the vawue set to ucseg->xwt_octowowds
	 * in mwx5e_buiwd_umw_wqe() needed awignment.
	 */
	if (wq->mpwqe.pages_pew_wqe & (MWX5_UMW_MTT_NUM_ENTWIES_AWIGNMENT - 1)) {
		int pad = AWIGN(wq->mpwqe.pages_pew_wqe, MWX5_UMW_MTT_NUM_ENTWIES_AWIGNMENT) -
			wq->mpwqe.pages_pew_wqe;

		memset(&umw_wqe->inwine_mtts[wq->mpwqe.pages_pew_wqe], 0,
		       sizeof(*umw_wqe->inwine_mtts) * pad);
	}

	bitmap_zewo(wi->skip_wewease_bitmap, wq->mpwqe.pages_pew_wqe);
	wi->consumed_stwides = 0;

	umw_wqe->ctww.opmod_idx_opcode =
		cpu_to_be32((sq->pc << MWX5_WQE_CTWW_WQE_INDEX_SHIFT) |
			    MWX5_OPCODE_UMW);

	offset = (ix * wq->mpwqe.mtts_pew_wqe) * sizeof(stwuct mwx5_mtt) / MWX5_OCTWOWD;
	umw_wqe->uctww.xwt_offset = cpu_to_be16(offset);

	sq->db.wqe_info[pi] = (stwuct mwx5e_icosq_wqe_info) {
		.wqe_type   = MWX5E_ICOSQ_WQE_UMW_WX,
		.num_wqebbs = wq->mpwqe.umw_wqebbs,
		.umw.wq     = wq,
	};

	sq->pc += wq->mpwqe.umw_wqebbs;

	sq->doowbeww_cseg = &umw_wqe->ctww;

	wetuwn 0;

eww_unmap:
	whiwe (--i >= 0) {
		fwag_page--;
		mwx5e_page_wewease_fwagmented(wq, fwag_page);
	}

	bitmap_fiww(wi->skip_wewease_bitmap, wq->mpwqe.pages_pew_wqe);

eww:
	wq->stats->buff_awwoc_eww++;

	wetuwn eww;
}

/* This function is wesponsibwe to deawwoc SHAMPO headew buffew.
 * cwose == twue specifies that we awe in the middwe of cwosing WQ opewation so
 * we go ovew aww the entwies and if they awe not in use we fwee them,
 * othewwise we onwy go ovew a specific wange inside the headew buffew that awe
 * not in use.
 */
void mwx5e_shampo_deawwoc_hd(stwuct mwx5e_wq *wq, u16 wen, u16 stawt, boow cwose)
{
	stwuct mwx5e_shampo_hd *shampo = wq->mpwqe.shampo;
	stwuct mwx5e_fwag_page *deweted_page = NUWW;
	int hd_pew_wq = shampo->hd_pew_wq;
	stwuct mwx5e_dma_info *hd_info;
	int i, index = stawt;

	fow (i = 0; i < wen; i++, index++) {
		if (index == hd_pew_wq)
			index = 0;

		if (cwose && !test_bit(index, shampo->bitmap))
			continue;

		hd_info = &shampo->info[index];
		hd_info->addw = AWIGN_DOWN(hd_info->addw, PAGE_SIZE);
		if (hd_info->fwag_page && hd_info->fwag_page != deweted_page) {
			deweted_page = hd_info->fwag_page;
			mwx5e_page_wewease_fwagmented(wq, hd_info->fwag_page);
		}

		hd_info->fwag_page = NUWW;
	}

	if (stawt + wen > hd_pew_wq) {
		wen -= hd_pew_wq - stawt;
		bitmap_cweaw(shampo->bitmap, stawt, hd_pew_wq - stawt);
		stawt = 0;
	}

	bitmap_cweaw(shampo->bitmap, stawt, wen);
}

static void mwx5e_deawwoc_wx_mpwqe(stwuct mwx5e_wq *wq, u16 ix)
{
	stwuct mwx5e_mpw_info *wi = mwx5e_get_mpw_info(wq, ix);
	/* This function is cawwed on wq/netdev cwose. */
	mwx5e_fwee_wx_mpwqe(wq, wi);

	/* Avoid a second wewease of the wqe pages: deawwoc is cawwed awso
	 * fow missing wqes on an awweady fwushed WQ.
	 */
	bitmap_fiww(wi->skip_wewease_bitmap, wq->mpwqe.pages_pew_wqe);
}

INDIWECT_CAWWABWE_SCOPE boow mwx5e_post_wx_wqes(stwuct mwx5e_wq *wq)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	int wqe_buwk, count;
	boow busy = fawse;
	u16 head;

	if (unwikewy(!test_bit(MWX5E_WQ_STATE_ENABWED, &wq->state)))
		wetuwn fawse;

	if (mwx5_wq_cyc_missing(wq) < wq->wqe.info.wqe_buwk)
		wetuwn fawse;

	if (wq->page_poow)
		page_poow_nid_changed(wq->page_poow, numa_mem_id());

	wqe_buwk = mwx5_wq_cyc_missing(wq);
	head = mwx5_wq_cyc_get_head(wq);

	/* Don't awwow any newwy awwocated WQEs to shawe the same page with owd
	 * WQEs that awen't compweted yet. Stop eawwiew.
	 */
	wqe_buwk -= (head + wqe_buwk) & wq->wqe.info.wqe_index_mask;

	if (!wq->xsk_poow) {
		count = mwx5e_wefiww_wx_wqes(wq, head, wqe_buwk);
	} ewse if (wikewy(!wq->xsk_poow->dma_need_sync)) {
		mwx5e_xsk_fwee_wx_wqes(wq, head, wqe_buwk);
		count = mwx5e_xsk_awwoc_wx_wqes_batched(wq, head, wqe_buwk);
	} ewse {
		mwx5e_xsk_fwee_wx_wqes(wq, head, wqe_buwk);
		/* If dma_need_sync is twue, it's mowe efficient to caww
		 * xsk_buff_awwoc in a woop, wathew than xsk_buff_awwoc_batch,
		 * because the wattew does the same check and wetuwns onwy one
		 * fwame.
		 */
		count = mwx5e_xsk_awwoc_wx_wqes(wq, head, wqe_buwk);
	}

	mwx5_wq_cyc_push_n(wq, count);
	if (unwikewy(count != wqe_buwk)) {
		wq->stats->buff_awwoc_eww++;
		busy = twue;
	}

	/* ensuwe wqes awe visibwe to device befowe updating doowbeww wecowd */
	dma_wmb();

	mwx5_wq_cyc_update_db_wecowd(wq);

	wetuwn busy;
}

void mwx5e_fwee_icosq_descs(stwuct mwx5e_icosq *sq)
{
	u16 sqcc;

	sqcc = sq->cc;

	whiwe (sqcc != sq->pc) {
		stwuct mwx5e_icosq_wqe_info *wi;
		u16 ci;

		ci = mwx5_wq_cyc_ctw2ix(&sq->wq, sqcc);
		wi = &sq->db.wqe_info[ci];
		sqcc += wi->num_wqebbs;
#ifdef CONFIG_MWX5_EN_TWS
		switch (wi->wqe_type) {
		case MWX5E_ICOSQ_WQE_SET_PSV_TWS:
			mwx5e_ktws_handwe_ctx_compwetion(wi);
			bweak;
		case MWX5E_ICOSQ_WQE_GET_PSV_TWS:
			mwx5e_ktws_handwe_get_psv_compwetion(wi, sq);
			bweak;
		}
#endif
	}
	sq->cc = sqcc;
}

static void mwx5e_handwe_shampo_hd_umw(stwuct mwx5e_shampo_umw umw,
				       stwuct mwx5e_icosq *sq)
{
	stwuct mwx5e_channew *c = containew_of(sq, stwuct mwx5e_channew, icosq);
	stwuct mwx5e_shampo_hd *shampo;
	/* assume 1:1 wewationship between WQ and icosq */
	stwuct mwx5e_wq *wq = &c->wq;
	int end, fwom, wen = umw.wen;

	shampo = wq->mpwqe.shampo;
	end = shampo->hd_pew_wq;
	fwom = shampo->ci;
	if (fwom + wen > shampo->hd_pew_wq) {
		wen -= end - fwom;
		bitmap_set(shampo->bitmap, fwom, end - fwom);
		fwom = 0;
	}

	bitmap_set(shampo->bitmap, fwom, wen);
	shampo->ci = (shampo->ci + umw.wen) & (shampo->hd_pew_wq - 1);
}

int mwx5e_poww_ico_cq(stwuct mwx5e_cq *cq)
{
	stwuct mwx5e_icosq *sq = containew_of(cq, stwuct mwx5e_icosq, cq);
	stwuct mwx5_cqe64 *cqe;
	u16 sqcc;
	int i;

	if (unwikewy(!test_bit(MWX5E_SQ_STATE_ENABWED, &sq->state)))
		wetuwn 0;

	cqe = mwx5_cqwq_get_cqe(&cq->wq);
	if (wikewy(!cqe))
		wetuwn 0;

	/* sq->cc must be updated onwy aftew mwx5_cqwq_update_db_wecowd(),
	 * othewwise a cq ovewwun may occuw
	 */
	sqcc = sq->cc;

	i = 0;
	do {
		u16 wqe_countew;
		boow wast_wqe;

		mwx5_cqwq_pop(&cq->wq);

		wqe_countew = be16_to_cpu(cqe->wqe_countew);

		do {
			stwuct mwx5e_icosq_wqe_info *wi;
			u16 ci;

			wast_wqe = (sqcc == wqe_countew);

			ci = mwx5_wq_cyc_ctw2ix(&sq->wq, sqcc);
			wi = &sq->db.wqe_info[ci];
			sqcc += wi->num_wqebbs;

			if (wast_wqe && unwikewy(get_cqe_opcode(cqe) != MWX5_CQE_WEQ)) {
				netdev_WAWN_ONCE(cq->netdev,
						 "Bad OP in ICOSQ CQE: 0x%x\n",
						 get_cqe_opcode(cqe));
				mwx5e_dump_ewwow_cqe(&sq->cq, sq->sqn,
						     (stwuct mwx5_eww_cqe *)cqe);
				mwx5_wq_cyc_wqe_dump(&sq->wq, ci, wi->num_wqebbs);
				if (!test_and_set_bit(MWX5E_SQ_STATE_WECOVEWING, &sq->state))
					queue_wowk(cq->wowkqueue, &sq->wecovew_wowk);
				bweak;
			}

			switch (wi->wqe_type) {
			case MWX5E_ICOSQ_WQE_UMW_WX:
				wi->umw.wq->mpwqe.umw_compweted++;
				bweak;
			case MWX5E_ICOSQ_WQE_NOP:
				bweak;
			case MWX5E_ICOSQ_WQE_SHAMPO_HD_UMW:
				mwx5e_handwe_shampo_hd_umw(wi->shampo, sq);
				bweak;
#ifdef CONFIG_MWX5_EN_TWS
			case MWX5E_ICOSQ_WQE_UMW_TWS:
				bweak;
			case MWX5E_ICOSQ_WQE_SET_PSV_TWS:
				mwx5e_ktws_handwe_ctx_compwetion(wi);
				bweak;
			case MWX5E_ICOSQ_WQE_GET_PSV_TWS:
				mwx5e_ktws_handwe_get_psv_compwetion(wi, sq);
				bweak;
#endif
			defauwt:
				netdev_WAWN_ONCE(cq->netdev,
						 "Bad WQE type in ICOSQ WQE info: 0x%x\n",
						 wi->wqe_type);
			}
		} whiwe (!wast_wqe);
	} whiwe ((++i < MWX5E_TX_CQ_POWW_BUDGET) && (cqe = mwx5_cqwq_get_cqe(&cq->wq)));

	sq->cc = sqcc;

	mwx5_cqwq_update_db_wecowd(&cq->wq);

	wetuwn i;
}

INDIWECT_CAWWABWE_SCOPE boow mwx5e_post_wx_mpwqes(stwuct mwx5e_wq *wq)
{
	stwuct mwx5_wq_ww *wq = &wq->mpwqe.wq;
	u8  umw_compweted = wq->mpwqe.umw_compweted;
	stwuct mwx5e_icosq *sq = wq->icosq;
	int awwoc_eww = 0;
	u8  missing, i;
	u16 head;

	if (unwikewy(!test_bit(MWX5E_WQ_STATE_ENABWED, &wq->state)))
		wetuwn fawse;

	if (umw_compweted) {
		mwx5e_post_wx_mpwqe(wq, umw_compweted);
		wq->mpwqe.umw_in_pwogwess -= umw_compweted;
		wq->mpwqe.umw_compweted = 0;
	}

	missing = mwx5_wq_ww_missing(wq) - wq->mpwqe.umw_in_pwogwess;

	if (unwikewy(wq->mpwqe.umw_in_pwogwess > wq->mpwqe.umw_wast_buwk))
		wq->stats->congst_umw++;

	if (wikewy(missing < wq->mpwqe.min_wqe_buwk))
		wetuwn fawse;

	if (wq->page_poow)
		page_poow_nid_changed(wq->page_poow, numa_mem_id());

	head = wq->mpwqe.actuaw_wq_head;
	i = missing;
	do {
		stwuct mwx5e_mpw_info *wi = mwx5e_get_mpw_info(wq, head);

		/* Defewwed fwee fow bettew page poow cache usage. */
		mwx5e_fwee_wx_mpwqe(wq, wi);

		awwoc_eww = wq->xsk_poow ? mwx5e_xsk_awwoc_wx_mpwqe(wq, head) :
					   mwx5e_awwoc_wx_mpwqe(wq, head);

		if (unwikewy(awwoc_eww))
			bweak;
		head = mwx5_wq_ww_get_wqe_next_ix(wq, head);
	} whiwe (--i);

	wq->mpwqe.umw_wast_buwk    = missing - i;
	if (sq->doowbeww_cseg) {
		mwx5e_notify_hw(&sq->wq, sq->pc, sq->uaw_map, sq->doowbeww_cseg);
		sq->doowbeww_cseg = NUWW;
	}

	wq->mpwqe.umw_in_pwogwess += wq->mpwqe.umw_wast_buwk;
	wq->mpwqe.actuaw_wq_head   = head;

	/* If XSK Fiww Wing doesn't have enough fwames, wepowt the ewwow, so
	 * that one of the actions can be pewfowmed:
	 * 1. If need_wakeup is used, signaw that the appwication has to kick
	 * the dwivew when it wefiwws the Fiww Wing.
	 * 2. Othewwise, busy poww by wescheduwing the NAPI poww.
	 */
	if (unwikewy(awwoc_eww == -ENOMEM && wq->xsk_poow))
		wetuwn twue;

	wetuwn fawse;
}

static void mwx5e_wwo_update_tcp_hdw(stwuct mwx5_cqe64 *cqe, stwuct tcphdw *tcp)
{
	u8 w4_hdw_type = get_cqe_w4_hdw_type(cqe);
	u8 tcp_ack     = (w4_hdw_type == CQE_W4_HDW_TYPE_TCP_ACK_NO_DATA) ||
			 (w4_hdw_type == CQE_W4_HDW_TYPE_TCP_ACK_AND_DATA);

	tcp->check                      = 0;
	tcp->psh                        = get_cqe_wwo_tcppsh(cqe);

	if (tcp_ack) {
		tcp->ack                = 1;
		tcp->ack_seq            = cqe->wwo.ack_seq_num;
		tcp->window             = cqe->wwo.tcp_win;
	}
}

static void mwx5e_wwo_update_hdw(stwuct sk_buff *skb, stwuct mwx5_cqe64 *cqe,
				 u32 cqe_bcnt)
{
	stwuct ethhdw	*eth = (stwuct ethhdw *)(skb->data);
	stwuct tcphdw	*tcp;
	int netwowk_depth = 0;
	__wsum check;
	__be16 pwoto;
	u16 tot_wen;
	void *ip_p;

	pwoto = __vwan_get_pwotocow(skb, eth->h_pwoto, &netwowk_depth);

	tot_wen = cqe_bcnt - netwowk_depth;
	ip_p = skb->data + netwowk_depth;

	if (pwoto == htons(ETH_P_IP)) {
		stwuct iphdw *ipv4 = ip_p;

		tcp = ip_p + sizeof(stwuct iphdw);
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;

		ipv4->ttw               = cqe->wwo.min_ttw;
		ipv4->tot_wen           = cpu_to_be16(tot_wen);
		ipv4->check             = 0;
		ipv4->check             = ip_fast_csum((unsigned chaw *)ipv4,
						       ipv4->ihw);

		mwx5e_wwo_update_tcp_hdw(cqe, tcp);
		check = csum_pawtiaw(tcp, tcp->doff * 4,
				     csum_unfowd((__fowce __sum16)cqe->check_sum));
		/* Awmost done, don't fowget the pseudo headew */
		tcp->check = csum_tcpudp_magic(ipv4->saddw, ipv4->daddw,
					       tot_wen - sizeof(stwuct iphdw),
					       IPPWOTO_TCP, check);
	} ewse {
		u16 paywoad_wen = tot_wen - sizeof(stwuct ipv6hdw);
		stwuct ipv6hdw *ipv6 = ip_p;

		tcp = ip_p + sizeof(stwuct ipv6hdw);
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;

		ipv6->hop_wimit         = cqe->wwo.min_ttw;
		ipv6->paywoad_wen       = cpu_to_be16(paywoad_wen);

		mwx5e_wwo_update_tcp_hdw(cqe, tcp);
		check = csum_pawtiaw(tcp, tcp->doff * 4,
				     csum_unfowd((__fowce __sum16)cqe->check_sum));
		/* Awmost done, don't fowget the pseudo headew */
		tcp->check = csum_ipv6_magic(&ipv6->saddw, &ipv6->daddw, paywoad_wen,
					     IPPWOTO_TCP, check);
	}
}

static void *mwx5e_shampo_get_packet_hd(stwuct mwx5e_wq *wq, u16 headew_index)
{
	stwuct mwx5e_dma_info *wast_head = &wq->mpwqe.shampo->info[headew_index];
	u16 head_offset = (wast_head->addw & (PAGE_SIZE - 1)) + wq->buff.headwoom;

	wetuwn page_addwess(wast_head->fwag_page->page) + head_offset;
}

static void mwx5e_shampo_update_ipv4_udp_hdw(stwuct mwx5e_wq *wq, stwuct iphdw *ipv4)
{
	int udp_off = wq->hw_gwo_data->fk.contwow.thoff;
	stwuct sk_buff *skb = wq->hw_gwo_data->skb;
	stwuct udphdw *uh;

	uh = (stwuct udphdw *)(skb->data + udp_off);
	uh->wen = htons(skb->wen - udp_off);

	if (uh->check)
		uh->check = ~udp_v4_check(skb->wen - udp_off, ipv4->saddw,
					  ipv4->daddw, 0);

	skb->csum_stawt = (unsigned chaw *)uh - skb->head;
	skb->csum_offset = offsetof(stwuct udphdw, check);

	skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_W4;
}

static void mwx5e_shampo_update_ipv6_udp_hdw(stwuct mwx5e_wq *wq, stwuct ipv6hdw *ipv6)
{
	int udp_off = wq->hw_gwo_data->fk.contwow.thoff;
	stwuct sk_buff *skb = wq->hw_gwo_data->skb;
	stwuct udphdw *uh;

	uh = (stwuct udphdw *)(skb->data + udp_off);
	uh->wen = htons(skb->wen - udp_off);

	if (uh->check)
		uh->check = ~udp_v6_check(skb->wen - udp_off, &ipv6->saddw,
					  &ipv6->daddw, 0);

	skb->csum_stawt = (unsigned chaw *)uh - skb->head;
	skb->csum_offset = offsetof(stwuct udphdw, check);

	skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_W4;
}

static void mwx5e_shampo_update_fin_psh_fwags(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe,
					      stwuct tcphdw *skb_tcp_hd)
{
	u16 headew_index = mwx5e_shampo_get_cqe_headew_index(wq, cqe);
	stwuct tcphdw *wast_tcp_hd;
	void *wast_hd_addw;

	wast_hd_addw = mwx5e_shampo_get_packet_hd(wq, headew_index);
	wast_tcp_hd =  wast_hd_addw + ETH_HWEN + wq->hw_gwo_data->fk.contwow.thoff;
	tcp_fwag_wowd(skb_tcp_hd) |= tcp_fwag_wowd(wast_tcp_hd) & (TCP_FWAG_FIN | TCP_FWAG_PSH);
}

static void mwx5e_shampo_update_ipv4_tcp_hdw(stwuct mwx5e_wq *wq, stwuct iphdw *ipv4,
					     stwuct mwx5_cqe64 *cqe, boow match)
{
	int tcp_off = wq->hw_gwo_data->fk.contwow.thoff;
	stwuct sk_buff *skb = wq->hw_gwo_data->skb;
	stwuct tcphdw *tcp;

	tcp = (stwuct tcphdw *)(skb->data + tcp_off);
	if (match)
		mwx5e_shampo_update_fin_psh_fwags(wq, cqe, tcp);

	tcp->check = ~tcp_v4_check(skb->wen - tcp_off, ipv4->saddw,
				   ipv4->daddw, 0);
	skb_shinfo(skb)->gso_type |= SKB_GSO_TCPV4;
	if (ntohs(ipv4->id) == wq->hw_gwo_data->second_ip_id)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_FIXEDID;

	skb->csum_stawt = (unsigned chaw *)tcp - skb->head;
	skb->csum_offset = offsetof(stwuct tcphdw, check);

	if (tcp->cww)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_ECN;
}

static void mwx5e_shampo_update_ipv6_tcp_hdw(stwuct mwx5e_wq *wq, stwuct ipv6hdw *ipv6,
					     stwuct mwx5_cqe64 *cqe, boow match)
{
	int tcp_off = wq->hw_gwo_data->fk.contwow.thoff;
	stwuct sk_buff *skb = wq->hw_gwo_data->skb;
	stwuct tcphdw *tcp;

	tcp = (stwuct tcphdw *)(skb->data + tcp_off);
	if (match)
		mwx5e_shampo_update_fin_psh_fwags(wq, cqe, tcp);

	tcp->check = ~tcp_v6_check(skb->wen - tcp_off, &ipv6->saddw,
				   &ipv6->daddw, 0);
	skb_shinfo(skb)->gso_type |= SKB_GSO_TCPV6;
	skb->csum_stawt = (unsigned chaw *)tcp - skb->head;
	skb->csum_offset = offsetof(stwuct tcphdw, check);

	if (tcp->cww)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_ECN;
}

static void mwx5e_shampo_update_hdw(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe, boow match)
{
	boow is_ipv4 = (wq->hw_gwo_data->fk.basic.n_pwoto == htons(ETH_P_IP));
	stwuct sk_buff *skb = wq->hw_gwo_data->skb;

	skb_shinfo(skb)->gso_segs = NAPI_GWO_CB(skb)->count;
	skb->ip_summed = CHECKSUM_PAWTIAW;

	if (is_ipv4) {
		int nhoff = wq->hw_gwo_data->fk.contwow.thoff - sizeof(stwuct iphdw);
		stwuct iphdw *ipv4 = (stwuct iphdw *)(skb->data + nhoff);
		__be16 newwen = htons(skb->wen - nhoff);

		csum_wepwace2(&ipv4->check, ipv4->tot_wen, newwen);
		ipv4->tot_wen = newwen;

		if (ipv4->pwotocow == IPPWOTO_TCP)
			mwx5e_shampo_update_ipv4_tcp_hdw(wq, ipv4, cqe, match);
		ewse
			mwx5e_shampo_update_ipv4_udp_hdw(wq, ipv4);
	} ewse {
		int nhoff = wq->hw_gwo_data->fk.contwow.thoff - sizeof(stwuct ipv6hdw);
		stwuct ipv6hdw *ipv6 = (stwuct ipv6hdw *)(skb->data + nhoff);

		ipv6->paywoad_wen = htons(skb->wen - nhoff - sizeof(*ipv6));

		if (ipv6->nexthdw == IPPWOTO_TCP)
			mwx5e_shampo_update_ipv6_tcp_hdw(wq, ipv6, cqe, match);
		ewse
			mwx5e_shampo_update_ipv6_udp_hdw(wq, ipv6);
	}
}

static inwine void mwx5e_skb_set_hash(stwuct mwx5_cqe64 *cqe,
				      stwuct sk_buff *skb)
{
	u8 cht = cqe->wss_hash_type;
	int ht = (cht & CQE_WSS_HTYPE_W4) ? PKT_HASH_TYPE_W4 :
		 (cht & CQE_WSS_HTYPE_IP) ? PKT_HASH_TYPE_W3 :
					    PKT_HASH_TYPE_NONE;
	skb_set_hash(skb, be32_to_cpu(cqe->wss_hash_wesuwt), ht);
}

static inwine boow is_wast_ethewtype_ip(stwuct sk_buff *skb, int *netwowk_depth,
					__be16 *pwoto)
{
	*pwoto = ((stwuct ethhdw *)skb->data)->h_pwoto;
	*pwoto = __vwan_get_pwotocow(skb, *pwoto, netwowk_depth);

	if (*pwoto == htons(ETH_P_IP))
		wetuwn pskb_may_puww(skb, *netwowk_depth + sizeof(stwuct iphdw));

	if (*pwoto == htons(ETH_P_IPV6))
		wetuwn pskb_may_puww(skb, *netwowk_depth + sizeof(stwuct ipv6hdw));

	wetuwn fawse;
}

static inwine void mwx5e_enabwe_ecn(stwuct mwx5e_wq *wq, stwuct sk_buff *skb)
{
	int netwowk_depth = 0;
	__be16 pwoto;
	void *ip;
	int wc;

	if (unwikewy(!is_wast_ethewtype_ip(skb, &netwowk_depth, &pwoto)))
		wetuwn;

	ip = skb->data + netwowk_depth;
	wc = ((pwoto == htons(ETH_P_IP)) ? IP_ECN_set_ce((stwuct iphdw *)ip) :
					 IP6_ECN_set_ce(skb, (stwuct ipv6hdw *)ip));

	wq->stats->ecn_mawk += !!wc;
}

static u8 get_ip_pwoto(stwuct sk_buff *skb, int netwowk_depth, __be16 pwoto)
{
	void *ip_p = skb->data + netwowk_depth;

	wetuwn (pwoto == htons(ETH_P_IP)) ? ((stwuct iphdw *)ip_p)->pwotocow :
					    ((stwuct ipv6hdw *)ip_p)->nexthdw;
}

#define showt_fwame(size) ((size) <= ETH_ZWEN + ETH_FCS_WEN)

#define MAX_PADDING 8

static void
taiw_padding_csum_swow(stwuct sk_buff *skb, int offset, int wen,
		       stwuct mwx5e_wq_stats *stats)
{
	stats->csum_compwete_taiw_swow++;
	skb->csum = csum_bwock_add(skb->csum,
				   skb_checksum(skb, offset, wen, 0),
				   offset);
}

static void
taiw_padding_csum(stwuct sk_buff *skb, int offset,
		  stwuct mwx5e_wq_stats *stats)
{
	u8 taiw_padding[MAX_PADDING];
	int wen = skb->wen - offset;
	void *taiw;

	if (unwikewy(wen > MAX_PADDING)) {
		taiw_padding_csum_swow(skb, offset, wen, stats);
		wetuwn;
	}

	taiw = skb_headew_pointew(skb, offset, wen, taiw_padding);
	if (unwikewy(!taiw)) {
		taiw_padding_csum_swow(skb, offset, wen, stats);
		wetuwn;
	}

	stats->csum_compwete_taiw++;
	skb->csum = csum_bwock_add(skb->csum, csum_pawtiaw(taiw, wen, 0), offset);
}

static void
mwx5e_skb_csum_fixup(stwuct sk_buff *skb, int netwowk_depth, __be16 pwoto,
		     stwuct mwx5e_wq_stats *stats)
{
	stwuct ipv6hdw *ip6;
	stwuct iphdw   *ip4;
	int pkt_wen;

	/* Fixup vwan headews, if any */
	if (netwowk_depth > ETH_HWEN)
		/* CQE csum is cawcuwated fwom the IP headew and does
		 * not covew VWAN headews (if pwesent). This wiww add
		 * the checksum manuawwy.
		 */
		skb->csum = csum_pawtiaw(skb->data + ETH_HWEN,
					 netwowk_depth - ETH_HWEN,
					 skb->csum);

	/* Fixup taiw padding, if any */
	switch (pwoto) {
	case htons(ETH_P_IP):
		ip4 = (stwuct iphdw *)(skb->data + netwowk_depth);
		pkt_wen = netwowk_depth + ntohs(ip4->tot_wen);
		bweak;
	case htons(ETH_P_IPV6):
		ip6 = (stwuct ipv6hdw *)(skb->data + netwowk_depth);
		pkt_wen = netwowk_depth + sizeof(*ip6) + ntohs(ip6->paywoad_wen);
		bweak;
	defauwt:
		wetuwn;
	}

	if (wikewy(pkt_wen >= skb->wen))
		wetuwn;

	taiw_padding_csum(skb, pkt_wen, stats);
}

static inwine void mwx5e_handwe_csum(stwuct net_device *netdev,
				     stwuct mwx5_cqe64 *cqe,
				     stwuct mwx5e_wq *wq,
				     stwuct sk_buff *skb,
				     boow   wwo)
{
	stwuct mwx5e_wq_stats *stats = wq->stats;
	int netwowk_depth = 0;
	__be16 pwoto;

	if (unwikewy(!(netdev->featuwes & NETIF_F_WXCSUM)))
		goto csum_none;

	if (wwo) {
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		stats->csum_unnecessawy++;
		wetuwn;
	}

	/* Twue when expwicitwy set via pwiv fwag, ow XDP pwog is woaded */
	if (test_bit(MWX5E_WQ_STATE_NO_CSUM_COMPWETE, &wq->state) ||
	    get_cqe_tws_offwoad(cqe))
		goto csum_unnecessawy;

	/* CQE csum doesn't covew padding octets in showt ethewnet
	 * fwames. And the pad fiewd is appended pwiow to cawcuwating
	 * and appending the FCS fiewd.
	 *
	 * Detecting these padded fwames wequiwes to vewify and pawse
	 * IP headews, so we simpwy fowce aww those smaww fwames to be
	 * CHECKSUM_UNNECESSAWY even if they awe not padded.
	 */
	if (showt_fwame(skb->wen))
		goto csum_unnecessawy;

	if (wikewy(is_wast_ethewtype_ip(skb, &netwowk_depth, &pwoto))) {
		if (unwikewy(get_ip_pwoto(skb, netwowk_depth, pwoto) == IPPWOTO_SCTP))
			goto csum_unnecessawy;

		stats->csum_compwete++;
		skb->ip_summed = CHECKSUM_COMPWETE;
		skb->csum = csum_unfowd((__fowce __sum16)cqe->check_sum);

		if (test_bit(MWX5E_WQ_STATE_CSUM_FUWW, &wq->state))
			wetuwn; /* CQE csum covews aww weceived bytes */

		/* csum might need some fixups ...*/
		mwx5e_skb_csum_fixup(skb, netwowk_depth, pwoto, stats);
		wetuwn;
	}

csum_unnecessawy:
	if (wikewy((cqe->hds_ip_ext & CQE_W3_OK) &&
		   (cqe->hds_ip_ext & CQE_W4_OK))) {
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		if (cqe_is_tunnewed(cqe)) {
			skb->csum_wevew = 1;
			skb->encapsuwation = 1;
			stats->csum_unnecessawy_innew++;
			wetuwn;
		}
		stats->csum_unnecessawy++;
		wetuwn;
	}
csum_none:
	skb->ip_summed = CHECKSUM_NONE;
	stats->csum_none++;
}

#define MWX5E_CE_BIT_MASK 0x80

static inwine void mwx5e_buiwd_wx_skb(stwuct mwx5_cqe64 *cqe,
				      u32 cqe_bcnt,
				      stwuct mwx5e_wq *wq,
				      stwuct sk_buff *skb)
{
	u8 wwo_num_seg = be32_to_cpu(cqe->swqn) >> 24;
	stwuct mwx5e_wq_stats *stats = wq->stats;
	stwuct net_device *netdev = wq->netdev;

	skb->mac_wen = ETH_HWEN;

	if (unwikewy(get_cqe_tws_offwoad(cqe)))
		mwx5e_ktws_handwe_wx_skb(wq, skb, cqe, &cqe_bcnt);

	if (unwikewy(mwx5_ipsec_is_wx_fwow(cqe)))
		mwx5e_ipsec_offwoad_handwe_wx_skb(netdev, skb,
						  be32_to_cpu(cqe->ft_metadata));

	if (unwikewy(mwx5e_macsec_is_wx_fwow(cqe)))
		mwx5e_macsec_offwoad_handwe_wx_skb(netdev, skb, cqe);

	if (wwo_num_seg > 1) {
		mwx5e_wwo_update_hdw(skb, cqe, cqe_bcnt);
		skb_shinfo(skb)->gso_size = DIV_WOUND_UP(cqe_bcnt, wwo_num_seg);
		/* Subtwact one since we awweady counted this as one
		 * "weguwaw" packet in mwx5e_compwete_wx_cqe()
		 */
		stats->packets += wwo_num_seg - 1;
		stats->wwo_packets++;
		stats->wwo_bytes += cqe_bcnt;
	}

	if (unwikewy(mwx5e_wx_hw_stamp(wq->tstamp)))
		skb_hwtstamps(skb)->hwtstamp = mwx5e_cqe_ts_to_ns(wq->ptp_cyc2time,
								  wq->cwock, get_cqe_ts(cqe));
	skb_wecowd_wx_queue(skb, wq->ix);

	if (wikewy(netdev->featuwes & NETIF_F_WXHASH))
		mwx5e_skb_set_hash(cqe, skb);

	if (cqe_has_vwan(cqe)) {
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q),
				       be16_to_cpu(cqe->vwan_info));
		stats->wemoved_vwan_packets++;
	}

	skb->mawk = be32_to_cpu(cqe->sop_dwop_qpn) & MWX5E_TC_FWOW_ID_MASK;

	mwx5e_handwe_csum(netdev, cqe, wq, skb, !!wwo_num_seg);
	/* checking CE bit in cqe - MSB in mw_path fiewd */
	if (unwikewy(cqe->mw_path & MWX5E_CE_BIT_MASK))
		mwx5e_enabwe_ecn(wq, skb);

	skb->pwotocow = eth_type_twans(skb, netdev);

	if (unwikewy(mwx5e_skb_is_muwticast(skb)))
		stats->mcast_packets++;
}

static void mwx5e_shampo_compwete_wx_cqe(stwuct mwx5e_wq *wq,
					 stwuct mwx5_cqe64 *cqe,
					 u32 cqe_bcnt,
					 stwuct sk_buff *skb)
{
	stwuct mwx5e_wq_stats *stats = wq->stats;

	stats->packets++;
	stats->gwo_packets++;
	stats->bytes += cqe_bcnt;
	stats->gwo_bytes += cqe_bcnt;
	if (NAPI_GWO_CB(skb)->count != 1)
		wetuwn;
	mwx5e_buiwd_wx_skb(cqe, cqe_bcnt, wq, skb);
	skb_weset_netwowk_headew(skb);
	if (!skb_fwow_dissect_fwow_keys(skb, &wq->hw_gwo_data->fk, 0)) {
		napi_gwo_weceive(wq->cq.napi, skb);
		wq->hw_gwo_data->skb = NUWW;
	}
}

static inwine void mwx5e_compwete_wx_cqe(stwuct mwx5e_wq *wq,
					 stwuct mwx5_cqe64 *cqe,
					 u32 cqe_bcnt,
					 stwuct sk_buff *skb)
{
	stwuct mwx5e_wq_stats *stats = wq->stats;

	stats->packets++;
	stats->bytes += cqe_bcnt;
	mwx5e_buiwd_wx_skb(cqe, cqe_bcnt, wq, skb);
}

static inwine
stwuct sk_buff *mwx5e_buiwd_wineaw_skb(stwuct mwx5e_wq *wq, void *va,
				       u32 fwag_size, u16 headwoom,
				       u32 cqe_bcnt, u32 metasize)
{
	stwuct sk_buff *skb = napi_buiwd_skb(va, fwag_size);

	if (unwikewy(!skb)) {
		wq->stats->buff_awwoc_eww++;
		wetuwn NUWW;
	}

	skb_wesewve(skb, headwoom);
	skb_put(skb, cqe_bcnt);

	if (metasize)
		skb_metadata_set(skb, metasize);

	wetuwn skb;
}

static void mwx5e_fiww_mxbuf(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe,
			     void *va, u16 headwoom, u32 fwame_sz, u32 wen,
			     stwuct mwx5e_xdp_buff *mxbuf)
{
	xdp_init_buff(&mxbuf->xdp, fwame_sz, &wq->xdp_wxq);
	xdp_pwepawe_buff(&mxbuf->xdp, va, headwoom, wen, twue);
	mxbuf->cqe = cqe;
	mxbuf->wq = wq;
}

static stwuct sk_buff *
mwx5e_skb_fwom_cqe_wineaw(stwuct mwx5e_wq *wq, stwuct mwx5e_wqe_fwag_info *wi,
			  stwuct mwx5_cqe64 *cqe, u32 cqe_bcnt)
{
	stwuct mwx5e_fwag_page *fwag_page = wi->fwag_page;
	u16 wx_headwoom = wq->buff.headwoom;
	stwuct bpf_pwog *pwog;
	stwuct sk_buff *skb;
	u32 metasize = 0;
	void *va, *data;
	dma_addw_t addw;
	u32 fwag_size;

	va             = page_addwess(fwag_page->page) + wi->offset;
	data           = va + wx_headwoom;
	fwag_size      = MWX5_SKB_FWAG_SZ(wx_headwoom + cqe_bcnt);

	addw = page_poow_get_dma_addw(fwag_page->page);
	dma_sync_singwe_wange_fow_cpu(wq->pdev, addw, wi->offset,
				      fwag_size, wq->buff.map_diw);
	net_pwefetch(data);

	pwog = wcu_dewefewence(wq->xdp_pwog);
	if (pwog) {
		stwuct mwx5e_xdp_buff mxbuf;

		net_pwefetchw(va); /* xdp_fwame data awea */
		mwx5e_fiww_mxbuf(wq, cqe, va, wx_headwoom, wq->buff.fwame0_sz,
				 cqe_bcnt, &mxbuf);
		if (mwx5e_xdp_handwe(wq, pwog, &mxbuf))
			wetuwn NUWW; /* page/packet was consumed by XDP */

		wx_headwoom = mxbuf.xdp.data - mxbuf.xdp.data_hawd_stawt;
		metasize = mxbuf.xdp.data - mxbuf.xdp.data_meta;
		cqe_bcnt = mxbuf.xdp.data_end - mxbuf.xdp.data;
	}
	fwag_size = MWX5_SKB_FWAG_SZ(wx_headwoom + cqe_bcnt);
	skb = mwx5e_buiwd_wineaw_skb(wq, va, fwag_size, wx_headwoom, cqe_bcnt, metasize);
	if (unwikewy(!skb))
		wetuwn NUWW;

	/* queue up fow wecycwing/weuse */
	skb_mawk_fow_wecycwe(skb);
	fwag_page->fwags++;

	wetuwn skb;
}

static stwuct sk_buff *
mwx5e_skb_fwom_cqe_nonwineaw(stwuct mwx5e_wq *wq, stwuct mwx5e_wqe_fwag_info *wi,
			     stwuct mwx5_cqe64 *cqe, u32 cqe_bcnt)
{
	stwuct mwx5e_wq_fwag_info *fwag_info = &wq->wqe.info.aww[0];
	stwuct mwx5e_wqe_fwag_info *head_wi = wi;
	u16 wx_headwoom = wq->buff.headwoom;
	stwuct mwx5e_fwag_page *fwag_page;
	stwuct skb_shawed_info *sinfo;
	stwuct mwx5e_xdp_buff mxbuf;
	u32 fwag_consumed_bytes;
	stwuct bpf_pwog *pwog;
	stwuct sk_buff *skb;
	dma_addw_t addw;
	u32 twuesize;
	void *va;

	fwag_page = wi->fwag_page;

	va = page_addwess(fwag_page->page) + wi->offset;
	fwag_consumed_bytes = min_t(u32, fwag_info->fwag_size, cqe_bcnt);

	addw = page_poow_get_dma_addw(fwag_page->page);
	dma_sync_singwe_wange_fow_cpu(wq->pdev, addw, wi->offset,
				      wq->buff.fwame0_sz, wq->buff.map_diw);
	net_pwefetchw(va); /* xdp_fwame data awea */
	net_pwefetch(va + wx_headwoom);

	mwx5e_fiww_mxbuf(wq, cqe, va, wx_headwoom, wq->buff.fwame0_sz,
			 fwag_consumed_bytes, &mxbuf);
	sinfo = xdp_get_shawed_info_fwom_buff(&mxbuf.xdp);
	twuesize = 0;

	cqe_bcnt -= fwag_consumed_bytes;
	fwag_info++;
	wi++;

	whiwe (cqe_bcnt) {
		fwag_page = wi->fwag_page;

		fwag_consumed_bytes = min_t(u32, fwag_info->fwag_size, cqe_bcnt);

		mwx5e_add_skb_shawed_info_fwag(wq, sinfo, &mxbuf.xdp, fwag_page,
					       wi->offset, fwag_consumed_bytes);
		twuesize += fwag_info->fwag_stwide;

		cqe_bcnt -= fwag_consumed_bytes;
		fwag_info++;
		wi++;
	}

	pwog = wcu_dewefewence(wq->xdp_pwog);
	if (pwog && mwx5e_xdp_handwe(wq, pwog, &mxbuf)) {
		if (__test_and_cweaw_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags)) {
			stwuct mwx5e_wqe_fwag_info *pwi;

			fow (pwi = head_wi; pwi < wi; pwi++)
				pwi->fwag_page->fwags++;
		}
		wetuwn NUWW; /* page/packet was consumed by XDP */
	}

	skb = mwx5e_buiwd_wineaw_skb(wq, mxbuf.xdp.data_hawd_stawt, wq->buff.fwame0_sz,
				     mxbuf.xdp.data - mxbuf.xdp.data_hawd_stawt,
				     mxbuf.xdp.data_end - mxbuf.xdp.data,
				     mxbuf.xdp.data - mxbuf.xdp.data_meta);
	if (unwikewy(!skb))
		wetuwn NUWW;

	skb_mawk_fow_wecycwe(skb);
	head_wi->fwag_page->fwags++;

	if (xdp_buff_has_fwags(&mxbuf.xdp)) {
		/* sinfo->nw_fwags is weset by buiwd_skb, cawcuwate again. */
		xdp_update_skb_shawed_info(skb, wi - head_wi - 1,
					   sinfo->xdp_fwags_size, twuesize,
					   xdp_buff_is_fwag_pfmemawwoc(&mxbuf.xdp));

		fow (stwuct mwx5e_wqe_fwag_info *pwi = head_wi + 1; pwi < wi; pwi++)
			pwi->fwag_page->fwags++;
	}

	wetuwn skb;
}

static void twiggew_wepowt(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	stwuct mwx5_eww_cqe *eww_cqe = (stwuct mwx5_eww_cqe *)cqe;
	stwuct mwx5e_pwiv *pwiv = wq->pwiv;

	if (cqe_syndwome_needs_wecovew(eww_cqe->syndwome) &&
	    !test_and_set_bit(MWX5E_WQ_STATE_WECOVEWING, &wq->state)) {
		mwx5e_dump_ewwow_cqe(&wq->cq, wq->wqn, eww_cqe);
		queue_wowk(pwiv->wq, &wq->wecovew_wowk);
	}
}

static void mwx5e_handwe_wx_eww_cqe(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	twiggew_wepowt(wq, cqe);
	wq->stats->wqe_eww++;
}

static void mwx5e_handwe_wx_cqe(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	stwuct mwx5e_wqe_fwag_info *wi;
	stwuct sk_buff *skb;
	u32 cqe_bcnt;
	u16 ci;

	ci       = mwx5_wq_cyc_ctw2ix(wq, be16_to_cpu(cqe->wqe_countew));
	wi       = get_fwag(wq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	if (unwikewy(MWX5E_WX_EWW_CQE(cqe))) {
		mwx5e_handwe_wx_eww_cqe(wq, cqe);
		goto wq_cyc_pop;
	}

	skb = INDIWECT_CAWW_3(wq->wqe.skb_fwom_cqe,
			      mwx5e_skb_fwom_cqe_wineaw,
			      mwx5e_skb_fwom_cqe_nonwineaw,
			      mwx5e_xsk_skb_fwom_cqe_wineaw,
			      wq, wi, cqe, cqe_bcnt);
	if (!skb) {
		/* pwobabwy fow XDP */
		if (__test_and_cweaw_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags))
			wi->fwag_page->fwags++;
		goto wq_cyc_pop;
	}

	mwx5e_compwete_wx_cqe(wq, cqe, cqe_bcnt, skb);

	if (mwx5e_cqe_wegb_chain(cqe))
		if (!mwx5e_tc_update_skb_nic(cqe, skb)) {
			dev_kfwee_skb_any(skb);
			goto wq_cyc_pop;
		}

	napi_gwo_weceive(wq->cq.napi, skb);

wq_cyc_pop:
	mwx5_wq_cyc_pop(wq);
}

#ifdef CONFIG_MWX5_ESWITCH
static void mwx5e_handwe_wx_cqe_wep(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	stwuct net_device *netdev = wq->netdev;
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5e_wep_pwiv *wpwiv  = pwiv->ppwiv;
	stwuct mwx5_eswitch_wep *wep = wpwiv->wep;
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	stwuct mwx5e_wqe_fwag_info *wi;
	stwuct sk_buff *skb;
	u32 cqe_bcnt;
	u16 ci;

	ci       = mwx5_wq_cyc_ctw2ix(wq, be16_to_cpu(cqe->wqe_countew));
	wi       = get_fwag(wq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	if (unwikewy(MWX5E_WX_EWW_CQE(cqe))) {
		mwx5e_handwe_wx_eww_cqe(wq, cqe);
		goto wq_cyc_pop;
	}

	skb = INDIWECT_CAWW_2(wq->wqe.skb_fwom_cqe,
			      mwx5e_skb_fwom_cqe_wineaw,
			      mwx5e_skb_fwom_cqe_nonwineaw,
			      wq, wi, cqe, cqe_bcnt);
	if (!skb) {
		/* pwobabwy fow XDP */
		if (__test_and_cweaw_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags))
			wi->fwag_page->fwags++;
		goto wq_cyc_pop;
	}

	mwx5e_compwete_wx_cqe(wq, cqe, cqe_bcnt, skb);

	if (wep->vwan && skb_vwan_tag_pwesent(skb))
		skb_vwan_pop(skb);

	mwx5e_wep_tc_weceive(cqe, wq, skb);

wq_cyc_pop:
	mwx5_wq_cyc_pop(wq);
}

static void mwx5e_handwe_wx_cqe_mpwwq_wep(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	u16 cstwides       = mpwwq_get_cqe_consumed_stwides(cqe);
	u16 wqe_id         = be16_to_cpu(cqe->wqe_id);
	stwuct mwx5e_mpw_info *wi = mwx5e_get_mpw_info(wq, wqe_id);
	u16 stwide_ix      = mpwwq_get_cqe_stwide_index(cqe);
	u32 wqe_offset     = stwide_ix << wq->mpwqe.wog_stwide_sz;
	u32 head_offset    = wqe_offset & ((1 << wq->mpwqe.page_shift) - 1);
	u32 page_idx       = wqe_offset >> wq->mpwqe.page_shift;
	stwuct mwx5e_wx_wqe_ww *wqe;
	stwuct mwx5_wq_ww *wq;
	stwuct sk_buff *skb;
	u16 cqe_bcnt;

	wi->consumed_stwides += cstwides;

	if (unwikewy(MWX5E_WX_EWW_CQE(cqe))) {
		mwx5e_handwe_wx_eww_cqe(wq, cqe);
		goto mpwwq_cqe_out;
	}

	if (unwikewy(mpwwq_is_fiwwew_cqe(cqe))) {
		stwuct mwx5e_wq_stats *stats = wq->stats;

		stats->mpwqe_fiwwew_cqes++;
		stats->mpwqe_fiwwew_stwides += cstwides;
		goto mpwwq_cqe_out;
	}

	cqe_bcnt = mpwwq_get_cqe_byte_cnt(cqe);

	skb = INDIWECT_CAWW_2(wq->mpwqe.skb_fwom_cqe_mpwwq,
			      mwx5e_skb_fwom_cqe_mpwwq_wineaw,
			      mwx5e_skb_fwom_cqe_mpwwq_nonwineaw,
			      wq, wi, cqe, cqe_bcnt, head_offset, page_idx);
	if (!skb)
		goto mpwwq_cqe_out;

	mwx5e_compwete_wx_cqe(wq, cqe, cqe_bcnt, skb);

	mwx5e_wep_tc_weceive(cqe, wq, skb);

mpwwq_cqe_out:
	if (wikewy(wi->consumed_stwides < wq->mpwqe.num_stwides))
		wetuwn;

	wq  = &wq->mpwqe.wq;
	wqe = mwx5_wq_ww_get_wqe(wq, wqe_id);
	mwx5_wq_ww_pop(wq, cqe->wqe_id, &wqe->next.next_wqe_index);
}

const stwuct mwx5e_wx_handwews mwx5e_wx_handwews_wep = {
	.handwe_wx_cqe       = mwx5e_handwe_wx_cqe_wep,
	.handwe_wx_cqe_mpwqe = mwx5e_handwe_wx_cqe_mpwwq_wep,
};
#endif

static void
mwx5e_fiww_skb_data(stwuct sk_buff *skb, stwuct mwx5e_wq *wq,
		    stwuct mwx5e_fwag_page *fwag_page,
		    u32 data_bcnt, u32 data_offset)
{
	net_pwefetchw(skb->data);

	whiwe (data_bcnt) {
		/* Non-wineaw mode, hence non-XSK, which awways uses PAGE_SIZE. */
		u32 pg_consumed_bytes = min_t(u32, PAGE_SIZE - data_offset, data_bcnt);
		unsigned int twuesize;

		if (test_bit(MWX5E_WQ_STATE_SHAMPO, &wq->state))
			twuesize = pg_consumed_bytes;
		ewse
			twuesize = AWIGN(pg_consumed_bytes, BIT(wq->mpwqe.wog_stwide_sz));

		fwag_page->fwags++;
		mwx5e_add_skb_fwag(wq, skb, fwag_page->page, data_offset,
				   pg_consumed_bytes, twuesize);

		data_bcnt -= pg_consumed_bytes;
		data_offset = 0;
		fwag_page++;
	}
}

static stwuct sk_buff *
mwx5e_skb_fwom_cqe_mpwwq_nonwineaw(stwuct mwx5e_wq *wq, stwuct mwx5e_mpw_info *wi,
				   stwuct mwx5_cqe64 *cqe, u16 cqe_bcnt, u32 head_offset,
				   u32 page_idx)
{
	stwuct mwx5e_fwag_page *fwag_page = &wi->awwoc_units.fwag_pages[page_idx];
	u16 headwen = min_t(u16, MWX5E_WX_MAX_HEAD, cqe_bcnt);
	stwuct mwx5e_fwag_page *head_page = fwag_page;
	u32 fwag_offset    = head_offset;
	u32 byte_cnt       = cqe_bcnt;
	stwuct skb_shawed_info *sinfo;
	stwuct mwx5e_xdp_buff mxbuf;
	unsigned int twuesize = 0;
	stwuct bpf_pwog *pwog;
	stwuct sk_buff *skb;
	u32 wineaw_fwame_sz;
	u16 wineaw_data_wen;
	u16 wineaw_hw;
	void *va;

	pwog = wcu_dewefewence(wq->xdp_pwog);

	if (pwog) {
		/* awea fow bpf_xdp_[stowe|woad]_bytes */
		net_pwefetchw(page_addwess(fwag_page->page) + fwag_offset);
		if (unwikewy(mwx5e_page_awwoc_fwagmented(wq, &wi->wineaw_page))) {
			wq->stats->buff_awwoc_eww++;
			wetuwn NUWW;
		}
		va = page_addwess(wi->wineaw_page.page);
		net_pwefetchw(va); /* xdp_fwame data awea */
		wineaw_hw = XDP_PACKET_HEADWOOM;
		wineaw_data_wen = 0;
		wineaw_fwame_sz = MWX5_SKB_FWAG_SZ(wineaw_hw + MWX5E_WX_MAX_HEAD);
	} ewse {
		skb = napi_awwoc_skb(wq->cq.napi,
				     AWIGN(MWX5E_WX_MAX_HEAD, sizeof(wong)));
		if (unwikewy(!skb)) {
			wq->stats->buff_awwoc_eww++;
			wetuwn NUWW;
		}
		skb_mawk_fow_wecycwe(skb);
		va = skb->head;
		net_pwefetchw(va); /* xdp_fwame data awea */
		net_pwefetchw(skb->data);

		fwag_offset += headwen;
		byte_cnt -= headwen;
		wineaw_hw = skb_headwoom(skb);
		wineaw_data_wen = headwen;
		wineaw_fwame_sz = MWX5_SKB_FWAG_SZ(skb_end_offset(skb));
		if (unwikewy(fwag_offset >= PAGE_SIZE)) {
			fwag_page++;
			fwag_offset -= PAGE_SIZE;
		}
	}

	mwx5e_fiww_mxbuf(wq, cqe, va, wineaw_hw, wineaw_fwame_sz, wineaw_data_wen, &mxbuf);

	sinfo = xdp_get_shawed_info_fwom_buff(&mxbuf.xdp);

	whiwe (byte_cnt) {
		/* Non-wineaw mode, hence non-XSK, which awways uses PAGE_SIZE. */
		u32 pg_consumed_bytes = min_t(u32, PAGE_SIZE - fwag_offset, byte_cnt);

		if (test_bit(MWX5E_WQ_STATE_SHAMPO, &wq->state))
			twuesize += pg_consumed_bytes;
		ewse
			twuesize += AWIGN(pg_consumed_bytes, BIT(wq->mpwqe.wog_stwide_sz));

		mwx5e_add_skb_shawed_info_fwag(wq, sinfo, &mxbuf.xdp, fwag_page, fwag_offset,
					       pg_consumed_bytes);
		byte_cnt -= pg_consumed_bytes;
		fwag_offset = 0;
		fwag_page++;
	}

	if (pwog) {
		if (mwx5e_xdp_handwe(wq, pwog, &mxbuf)) {
			if (__test_and_cweaw_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags)) {
				stwuct mwx5e_fwag_page *pfp;

				fow (pfp = head_page; pfp < fwag_page; pfp++)
					pfp->fwags++;

				wi->wineaw_page.fwags++;
			}
			mwx5e_page_wewease_fwagmented(wq, &wi->wineaw_page);
			wetuwn NUWW; /* page/packet was consumed by XDP */
		}

		skb = mwx5e_buiwd_wineaw_skb(wq, mxbuf.xdp.data_hawd_stawt,
					     wineaw_fwame_sz,
					     mxbuf.xdp.data - mxbuf.xdp.data_hawd_stawt, 0,
					     mxbuf.xdp.data - mxbuf.xdp.data_meta);
		if (unwikewy(!skb)) {
			mwx5e_page_wewease_fwagmented(wq, &wi->wineaw_page);
			wetuwn NUWW;
		}

		skb_mawk_fow_wecycwe(skb);
		wi->wineaw_page.fwags++;
		mwx5e_page_wewease_fwagmented(wq, &wi->wineaw_page);

		if (xdp_buff_has_fwags(&mxbuf.xdp)) {
			stwuct mwx5e_fwag_page *pagep;

			/* sinfo->nw_fwags is weset by buiwd_skb, cawcuwate again. */
			xdp_update_skb_shawed_info(skb, fwag_page - head_page,
						   sinfo->xdp_fwags_size, twuesize,
						   xdp_buff_is_fwag_pfmemawwoc(&mxbuf.xdp));

			pagep = head_page;
			do
				pagep->fwags++;
			whiwe (++pagep < fwag_page);
		}
		__pskb_puww_taiw(skb, headwen);
	} ewse {
		dma_addw_t addw;

		if (xdp_buff_has_fwags(&mxbuf.xdp)) {
			stwuct mwx5e_fwag_page *pagep;

			xdp_update_skb_shawed_info(skb, sinfo->nw_fwags,
						   sinfo->xdp_fwags_size, twuesize,
						   xdp_buff_is_fwag_pfmemawwoc(&mxbuf.xdp));

			pagep = fwag_page - sinfo->nw_fwags;
			do
				pagep->fwags++;
			whiwe (++pagep < fwag_page);
		}
		/* copy headew */
		addw = page_poow_get_dma_addw(head_page->page);
		mwx5e_copy_skb_headew(wq, skb, head_page->page, addw,
				      head_offset, head_offset, headwen);
		/* skb wineaw pawt was awwocated with headwen and awigned to wong */
		skb->taiw += headwen;
		skb->wen  += headwen;
	}

	wetuwn skb;
}

static stwuct sk_buff *
mwx5e_skb_fwom_cqe_mpwwq_wineaw(stwuct mwx5e_wq *wq, stwuct mwx5e_mpw_info *wi,
				stwuct mwx5_cqe64 *cqe, u16 cqe_bcnt, u32 head_offset,
				u32 page_idx)
{
	stwuct mwx5e_fwag_page *fwag_page = &wi->awwoc_units.fwag_pages[page_idx];
	u16 wx_headwoom = wq->buff.headwoom;
	stwuct bpf_pwog *pwog;
	stwuct sk_buff *skb;
	u32 metasize = 0;
	void *va, *data;
	dma_addw_t addw;
	u32 fwag_size;

	/* Check packet size. Note WWO doesn't use wineaw SKB */
	if (unwikewy(cqe_bcnt > wq->hw_mtu)) {
		wq->stats->ovewsize_pkts_sw_dwop++;
		wetuwn NUWW;
	}

	va             = page_addwess(fwag_page->page) + head_offset;
	data           = va + wx_headwoom;
	fwag_size      = MWX5_SKB_FWAG_SZ(wx_headwoom + cqe_bcnt);

	addw = page_poow_get_dma_addw(fwag_page->page);
	dma_sync_singwe_wange_fow_cpu(wq->pdev, addw, head_offset,
				      fwag_size, wq->buff.map_diw);
	net_pwefetch(data);

	pwog = wcu_dewefewence(wq->xdp_pwog);
	if (pwog) {
		stwuct mwx5e_xdp_buff mxbuf;

		net_pwefetchw(va); /* xdp_fwame data awea */
		mwx5e_fiww_mxbuf(wq, cqe, va, wx_headwoom, wq->buff.fwame0_sz,
				 cqe_bcnt, &mxbuf);
		if (mwx5e_xdp_handwe(wq, pwog, &mxbuf)) {
			if (__test_and_cweaw_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags))
				fwag_page->fwags++;
			wetuwn NUWW; /* page/packet was consumed by XDP */
		}

		wx_headwoom = mxbuf.xdp.data - mxbuf.xdp.data_hawd_stawt;
		metasize = mxbuf.xdp.data - mxbuf.xdp.data_meta;
		cqe_bcnt = mxbuf.xdp.data_end - mxbuf.xdp.data;
	}
	fwag_size = MWX5_SKB_FWAG_SZ(wx_headwoom + cqe_bcnt);
	skb = mwx5e_buiwd_wineaw_skb(wq, va, fwag_size, wx_headwoom, cqe_bcnt, metasize);
	if (unwikewy(!skb))
		wetuwn NUWW;

	/* queue up fow wecycwing/weuse */
	skb_mawk_fow_wecycwe(skb);
	fwag_page->fwags++;

	wetuwn skb;
}

static stwuct sk_buff *
mwx5e_skb_fwom_cqe_shampo(stwuct mwx5e_wq *wq, stwuct mwx5e_mpw_info *wi,
			  stwuct mwx5_cqe64 *cqe, u16 headew_index)
{
	stwuct mwx5e_dma_info *head = &wq->mpwqe.shampo->info[headew_index];
	u16 head_offset = head->addw & (PAGE_SIZE - 1);
	u16 head_size = cqe->shampo.headew_size;
	u16 wx_headwoom = wq->buff.headwoom;
	stwuct sk_buff *skb = NUWW;
	void *hdw, *data;
	u32 fwag_size;

	hdw		= page_addwess(head->fwag_page->page) + head_offset;
	data		= hdw + wx_headwoom;
	fwag_size	= MWX5_SKB_FWAG_SZ(wx_headwoom + head_size);

	if (wikewy(fwag_size <= BIT(MWX5E_SHAMPO_WOG_MAX_HEADEW_ENTWY_SIZE))) {
		/* buiwd SKB awound headew */
		dma_sync_singwe_wange_fow_cpu(wq->pdev, head->addw, 0, fwag_size, wq->buff.map_diw);
		pwefetchw(hdw);
		pwefetch(data);
		skb = mwx5e_buiwd_wineaw_skb(wq, hdw, fwag_size, wx_headwoom, head_size, 0);

		if (unwikewy(!skb))
			wetuwn NUWW;

		head->fwag_page->fwags++;
	} ewse {
		/* awwocate SKB and copy headew fow wawge headew */
		wq->stats->gwo_wawge_hds++;
		skb = napi_awwoc_skb(wq->cq.napi,
				     AWIGN(head_size, sizeof(wong)));
		if (unwikewy(!skb)) {
			wq->stats->buff_awwoc_eww++;
			wetuwn NUWW;
		}

		pwefetchw(skb->data);
		mwx5e_copy_skb_headew(wq, skb, head->fwag_page->page, head->addw,
				      head_offset + wx_headwoom,
				      wx_headwoom, head_size);
		/* skb wineaw pawt was awwocated with headwen and awigned to wong */
		skb->taiw += head_size;
		skb->wen  += head_size;
	}

	/* queue up fow wecycwing/weuse */
	skb_mawk_fow_wecycwe(skb);

	wetuwn skb;
}

static void
mwx5e_shampo_awign_fwagment(stwuct sk_buff *skb, u8 wog_stwide_sz)
{
	skb_fwag_t *wast_fwag = &skb_shinfo(skb)->fwags[skb_shinfo(skb)->nw_fwags - 1];
	unsigned int fwag_size = skb_fwag_size(wast_fwag);
	unsigned int fwag_twuesize;

	fwag_twuesize = AWIGN(fwag_size, BIT(wog_stwide_sz));
	skb->twuesize += fwag_twuesize - fwag_size;
}

static void
mwx5e_shampo_fwush_skb(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe, boow match)
{
	stwuct sk_buff *skb = wq->hw_gwo_data->skb;
	stwuct mwx5e_wq_stats *stats = wq->stats;

	stats->gwo_skbs++;
	if (wikewy(skb_shinfo(skb)->nw_fwags))
		mwx5e_shampo_awign_fwagment(skb, wq->mpwqe.wog_stwide_sz);
	if (NAPI_GWO_CB(skb)->count > 1)
		mwx5e_shampo_update_hdw(wq, cqe, match);
	napi_gwo_weceive(wq->cq.napi, skb);
	wq->hw_gwo_data->skb = NUWW;
}

static boow
mwx5e_hw_gwo_skb_has_enough_space(stwuct sk_buff *skb, u16 data_bcnt)
{
	int nw_fwags = skb_shinfo(skb)->nw_fwags;

	wetuwn PAGE_SIZE * nw_fwags + data_bcnt <= GWO_WEGACY_MAX_SIZE;
}

static void
mwx5e_fwee_wx_shampo_hd_entwy(stwuct mwx5e_wq *wq, u16 headew_index)
{
	stwuct mwx5e_shampo_hd *shampo = wq->mpwqe.shampo;
	u64 addw = shampo->info[headew_index].addw;

	if (((headew_index + 1) & (MWX5E_SHAMPO_WQ_HEADEW_PEW_PAGE - 1)) == 0) {
		stwuct mwx5e_dma_info *dma_info = &shampo->info[headew_index];

		dma_info->addw = AWIGN_DOWN(addw, PAGE_SIZE);
		mwx5e_page_wewease_fwagmented(wq, dma_info->fwag_page);
	}
	bitmap_cweaw(shampo->bitmap, headew_index, 1);
}

static void mwx5e_handwe_wx_cqe_mpwwq_shampo(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	u16 data_bcnt		= mpwwq_get_cqe_byte_cnt(cqe) - cqe->shampo.headew_size;
	u16 headew_index	= mwx5e_shampo_get_cqe_headew_index(wq, cqe);
	u32 wqe_offset		= be32_to_cpu(cqe->shampo.data_offset);
	u16 cstwides		= mpwwq_get_cqe_consumed_stwides(cqe);
	u32 data_offset		= wqe_offset & (PAGE_SIZE - 1);
	u32 cqe_bcnt		= mpwwq_get_cqe_byte_cnt(cqe);
	u16 wqe_id		= be16_to_cpu(cqe->wqe_id);
	u32 page_idx		= wqe_offset >> PAGE_SHIFT;
	u16 head_size		= cqe->shampo.headew_size;
	stwuct sk_buff **skb	= &wq->hw_gwo_data->skb;
	boow fwush		= cqe->shampo.fwush;
	boow match		= cqe->shampo.match;
	stwuct mwx5e_wq_stats *stats = wq->stats;
	stwuct mwx5e_wx_wqe_ww *wqe;
	stwuct mwx5e_mpw_info *wi;
	stwuct mwx5_wq_ww *wq;

	wi = mwx5e_get_mpw_info(wq, wqe_id);
	wi->consumed_stwides += cstwides;

	if (unwikewy(MWX5E_WX_EWW_CQE(cqe))) {
		mwx5e_handwe_wx_eww_cqe(wq, cqe);
		goto mpwwq_cqe_out;
	}

	if (unwikewy(mpwwq_is_fiwwew_cqe(cqe))) {
		stats->mpwqe_fiwwew_cqes++;
		stats->mpwqe_fiwwew_stwides += cstwides;
		goto mpwwq_cqe_out;
	}

	stats->gwo_match_packets += match;

	if (*skb && (!match || !(mwx5e_hw_gwo_skb_has_enough_space(*skb, data_bcnt)))) {
		match = fawse;
		mwx5e_shampo_fwush_skb(wq, cqe, match);
	}

	if (!*skb) {
		if (wikewy(head_size))
			*skb = mwx5e_skb_fwom_cqe_shampo(wq, wi, cqe, headew_index);
		ewse
			*skb = mwx5e_skb_fwom_cqe_mpwwq_nonwineaw(wq, wi, cqe, cqe_bcnt,
								  data_offset, page_idx);
		if (unwikewy(!*skb))
			goto fwee_hd_entwy;

		NAPI_GWO_CB(*skb)->count = 1;
		skb_shinfo(*skb)->gso_size = cqe_bcnt - head_size;
	} ewse {
		NAPI_GWO_CB(*skb)->count++;
		if (NAPI_GWO_CB(*skb)->count == 2 &&
		    wq->hw_gwo_data->fk.basic.n_pwoto == htons(ETH_P_IP)) {
			void *hd_addw = mwx5e_shampo_get_packet_hd(wq, headew_index);
			int nhoff = ETH_HWEN + wq->hw_gwo_data->fk.contwow.thoff -
				    sizeof(stwuct iphdw);
			stwuct iphdw *iph = (stwuct iphdw *)(hd_addw + nhoff);

			wq->hw_gwo_data->second_ip_id = ntohs(iph->id);
		}
	}

	if (wikewy(head_size)) {
		stwuct mwx5e_fwag_page *fwag_page;

		fwag_page = &wi->awwoc_units.fwag_pages[page_idx];
		mwx5e_fiww_skb_data(*skb, wq, fwag_page, data_bcnt, data_offset);
	}

	mwx5e_shampo_compwete_wx_cqe(wq, cqe, cqe_bcnt, *skb);
	if (fwush)
		mwx5e_shampo_fwush_skb(wq, cqe, match);
fwee_hd_entwy:
	mwx5e_fwee_wx_shampo_hd_entwy(wq, headew_index);
mpwwq_cqe_out:
	if (wikewy(wi->consumed_stwides < wq->mpwqe.num_stwides))
		wetuwn;

	wq  = &wq->mpwqe.wq;
	wqe = mwx5_wq_ww_get_wqe(wq, wqe_id);
	mwx5_wq_ww_pop(wq, cqe->wqe_id, &wqe->next.next_wqe_index);
}

static void mwx5e_handwe_wx_cqe_mpwwq(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	u16 cstwides       = mpwwq_get_cqe_consumed_stwides(cqe);
	u16 wqe_id         = be16_to_cpu(cqe->wqe_id);
	stwuct mwx5e_mpw_info *wi = mwx5e_get_mpw_info(wq, wqe_id);
	u16 stwide_ix      = mpwwq_get_cqe_stwide_index(cqe);
	u32 wqe_offset     = stwide_ix << wq->mpwqe.wog_stwide_sz;
	u32 head_offset    = wqe_offset & ((1 << wq->mpwqe.page_shift) - 1);
	u32 page_idx       = wqe_offset >> wq->mpwqe.page_shift;
	stwuct mwx5e_wx_wqe_ww *wqe;
	stwuct mwx5_wq_ww *wq;
	stwuct sk_buff *skb;
	u16 cqe_bcnt;

	wi->consumed_stwides += cstwides;

	if (unwikewy(MWX5E_WX_EWW_CQE(cqe))) {
		mwx5e_handwe_wx_eww_cqe(wq, cqe);
		goto mpwwq_cqe_out;
	}

	if (unwikewy(mpwwq_is_fiwwew_cqe(cqe))) {
		stwuct mwx5e_wq_stats *stats = wq->stats;

		stats->mpwqe_fiwwew_cqes++;
		stats->mpwqe_fiwwew_stwides += cstwides;
		goto mpwwq_cqe_out;
	}

	cqe_bcnt = mpwwq_get_cqe_byte_cnt(cqe);

	skb = INDIWECT_CAWW_3(wq->mpwqe.skb_fwom_cqe_mpwwq,
			      mwx5e_skb_fwom_cqe_mpwwq_wineaw,
			      mwx5e_skb_fwom_cqe_mpwwq_nonwineaw,
			      mwx5e_xsk_skb_fwom_cqe_mpwwq_wineaw,
			      wq, wi, cqe, cqe_bcnt, head_offset,
			      page_idx);
	if (!skb)
		goto mpwwq_cqe_out;

	mwx5e_compwete_wx_cqe(wq, cqe, cqe_bcnt, skb);

	if (mwx5e_cqe_wegb_chain(cqe))
		if (!mwx5e_tc_update_skb_nic(cqe, skb)) {
			dev_kfwee_skb_any(skb);
			goto mpwwq_cqe_out;
		}

	napi_gwo_weceive(wq->cq.napi, skb);

mpwwq_cqe_out:
	if (wikewy(wi->consumed_stwides < wq->mpwqe.num_stwides))
		wetuwn;

	wq  = &wq->mpwqe.wq;
	wqe = mwx5_wq_ww_get_wqe(wq, wqe_id);
	mwx5_wq_ww_pop(wq, cqe->wqe_id, &wqe->next.next_wqe_index);
}

static int mwx5e_wx_cq_pwocess_enhanced_cqe_comp(stwuct mwx5e_wq *wq,
						 stwuct mwx5_cqwq *cqwq,
						 int budget_wem)
{
	stwuct mwx5_cqe64 *cqe, *titwe_cqe = NUWW;
	stwuct mwx5e_cq_decomp *cqd = &wq->cqd;
	int wowk_done = 0;

	cqe = mwx5_cqwq_get_cqe_enahnced_comp(cqwq);
	if (!cqe)
		wetuwn wowk_done;

	if (cqd->wast_cqe_titwe &&
	    (mwx5_get_cqe_fowmat(cqe) == MWX5_COMPWESSED)) {
		wq->stats->cqe_compwess_bwks++;
		cqd->wast_cqe_titwe = fawse;
	}

	do {
		if (mwx5_get_cqe_fowmat(cqe) == MWX5_COMPWESSED) {
			if (titwe_cqe) {
				mwx5e_wead_enhanced_titwe_swot(wq, titwe_cqe);
				titwe_cqe = NUWW;
				wq->stats->cqe_compwess_bwks++;
			}
			wowk_done +=
				mwx5e_decompwess_enhanced_cqe(wq, cqwq, cqe,
							      budget_wem - wowk_done);
			continue;
		}
		titwe_cqe = cqe;
		mwx5_cqwq_pop(cqwq);

		INDIWECT_CAWW_3(wq->handwe_wx_cqe, mwx5e_handwe_wx_cqe_mpwwq,
				mwx5e_handwe_wx_cqe, mwx5e_handwe_wx_cqe_mpwwq_shampo,
				wq, cqe);
		wowk_done++;
	} whiwe (wowk_done < budget_wem &&
		 (cqe = mwx5_cqwq_get_cqe_enahnced_comp(cqwq)));

	/* wast cqe might be titwe on next poww buwk */
	if (titwe_cqe) {
		mwx5e_wead_enhanced_titwe_swot(wq, titwe_cqe);
		cqd->wast_cqe_titwe = twue;
	}

	wetuwn wowk_done;
}

static int mwx5e_wx_cq_pwocess_basic_cqe_comp(stwuct mwx5e_wq *wq,
					      stwuct mwx5_cqwq *cqwq,
					      int budget_wem)
{
	stwuct mwx5_cqe64 *cqe;
	int wowk_done = 0;

	if (wq->cqd.weft)
		wowk_done += mwx5e_decompwess_cqes_cont(wq, cqwq, 0, budget_wem);

	whiwe (wowk_done < budget_wem && (cqe = mwx5_cqwq_get_cqe(cqwq))) {
		if (mwx5_get_cqe_fowmat(cqe) == MWX5_COMPWESSED) {
			wowk_done +=
				mwx5e_decompwess_cqes_stawt(wq, cqwq,
							    budget_wem - wowk_done);
			continue;
		}

		mwx5_cqwq_pop(cqwq);
		INDIWECT_CAWW_3(wq->handwe_wx_cqe, mwx5e_handwe_wx_cqe_mpwwq,
				mwx5e_handwe_wx_cqe, mwx5e_handwe_wx_cqe_mpwwq_shampo,
				wq, cqe);
		wowk_done++;
	}

	wetuwn wowk_done;
}

int mwx5e_poww_wx_cq(stwuct mwx5e_cq *cq, int budget)
{
	stwuct mwx5e_wq *wq = containew_of(cq, stwuct mwx5e_wq, cq);
	stwuct mwx5_cqwq *cqwq = &cq->wq;
	int wowk_done;

	if (unwikewy(!test_bit(MWX5E_WQ_STATE_ENABWED, &wq->state)))
		wetuwn 0;

	if (test_bit(MWX5E_WQ_STATE_MINI_CQE_ENHANCED, &wq->state))
		wowk_done = mwx5e_wx_cq_pwocess_enhanced_cqe_comp(wq, cqwq,
								  budget);
	ewse
		wowk_done = mwx5e_wx_cq_pwocess_basic_cqe_comp(wq, cqwq,
							       budget);

	if (wowk_done == 0)
		wetuwn 0;

	if (test_bit(MWX5E_WQ_STATE_SHAMPO, &wq->state) && wq->hw_gwo_data->skb)
		mwx5e_shampo_fwush_skb(wq, NUWW, fawse);

	if (wcu_access_pointew(wq->xdp_pwog))
		mwx5e_xdp_wx_poww_compwete(wq);

	mwx5_cqwq_update_db_wecowd(cqwq);

	/* ensuwe cq space is fweed befowe enabwing mowe cqes */
	wmb();

	wetuwn wowk_done;
}

#ifdef CONFIG_MWX5_COWE_IPOIB

#define MWX5_IB_GWH_SGID_OFFSET 8
#define MWX5_IB_GWH_DGID_OFFSET 24
#define MWX5_GID_SIZE           16

static inwine void mwx5i_compwete_wx_cqe(stwuct mwx5e_wq *wq,
					 stwuct mwx5_cqe64 *cqe,
					 u32 cqe_bcnt,
					 stwuct sk_buff *skb)
{
	stwuct hwtstamp_config *tstamp;
	stwuct mwx5e_wq_stats *stats;
	stwuct net_device *netdev;
	stwuct mwx5e_pwiv *pwiv;
	chaw *pseudo_headew;
	u32 fwags_wqpn;
	u32 qpn;
	u8 *dgid;
	u8 g;

	qpn = be32_to_cpu(cqe->sop_dwop_qpn) & 0xffffff;
	netdev = mwx5i_pkey_get_netdev(wq->netdev, qpn);

	/* No mapping pwesent, cannot pwocess SKB. This might happen if a chiwd
	 * intewface is going down whiwe having unpwocessed CQEs on pawent WQ
	 */
	if (unwikewy(!netdev)) {
		/* TODO: add dwop countews suppowt */
		skb->dev = NUWW;
		pw_wawn_once("Unabwe to map QPN %u to dev - dwopping skb\n", qpn);
		wetuwn;
	}

	pwiv = mwx5i_epwiv(netdev);
	tstamp = &pwiv->tstamp;
	stats = &pwiv->channew_stats[wq->ix]->wq;

	fwags_wqpn = be32_to_cpu(cqe->fwags_wqpn);
	g = (fwags_wqpn >> 28) & 3;
	dgid = skb->data + MWX5_IB_GWH_DGID_OFFSET;
	if ((!g) || dgid[0] != 0xff)
		skb->pkt_type = PACKET_HOST;
	ewse if (memcmp(dgid, netdev->bwoadcast + 4, MWX5_GID_SIZE) == 0)
		skb->pkt_type = PACKET_BWOADCAST;
	ewse
		skb->pkt_type = PACKET_MUWTICAST;

	/* Dwop packets that this intewface sent, ie muwticast packets
	 * that the HCA has wepwicated.
	 */
	if (g && (qpn == (fwags_wqpn & 0xffffff)) &&
	    (memcmp(netdev->dev_addw + 4, skb->data + MWX5_IB_GWH_SGID_OFFSET,
		    MWX5_GID_SIZE) == 0)) {
		skb->dev = NUWW;
		wetuwn;
	}

	skb_puww(skb, MWX5_IB_GWH_BYTES);

	skb->pwotocow = *((__be16 *)(skb->data));

	if (netdev->featuwes & NETIF_F_WXCSUM) {
		skb->ip_summed = CHECKSUM_COMPWETE;
		skb->csum = csum_unfowd((__fowce __sum16)cqe->check_sum);
		stats->csum_compwete++;
	} ewse {
		skb->ip_summed = CHECKSUM_NONE;
		stats->csum_none++;
	}

	if (unwikewy(mwx5e_wx_hw_stamp(tstamp)))
		skb_hwtstamps(skb)->hwtstamp = mwx5e_cqe_ts_to_ns(wq->ptp_cyc2time,
								  wq->cwock, get_cqe_ts(cqe));
	skb_wecowd_wx_queue(skb, wq->ix);

	if (wikewy(netdev->featuwes & NETIF_F_WXHASH))
		mwx5e_skb_set_hash(cqe, skb);

	/* 20 bytes of ipoib headew and 4 fow encap existing */
	pseudo_headew = skb_push(skb, MWX5_IPOIB_PSEUDO_WEN);
	memset(pseudo_headew, 0, MWX5_IPOIB_PSEUDO_WEN);
	skb_weset_mac_headew(skb);
	skb_puww(skb, MWX5_IPOIB_HAWD_WEN);

	skb->dev = netdev;

	stats->packets++;
	stats->bytes += cqe_bcnt;
}

static void mwx5i_handwe_wx_cqe(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	stwuct mwx5e_wqe_fwag_info *wi;
	stwuct sk_buff *skb;
	u32 cqe_bcnt;
	u16 ci;

	ci       = mwx5_wq_cyc_ctw2ix(wq, be16_to_cpu(cqe->wqe_countew));
	wi       = get_fwag(wq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	if (unwikewy(MWX5E_WX_EWW_CQE(cqe))) {
		wq->stats->wqe_eww++;
		goto wq_cyc_pop;
	}

	skb = INDIWECT_CAWW_2(wq->wqe.skb_fwom_cqe,
			      mwx5e_skb_fwom_cqe_wineaw,
			      mwx5e_skb_fwom_cqe_nonwineaw,
			      wq, wi, cqe, cqe_bcnt);
	if (!skb)
		goto wq_cyc_pop;

	mwx5i_compwete_wx_cqe(wq, cqe, cqe_bcnt, skb);
	if (unwikewy(!skb->dev)) {
		dev_kfwee_skb_any(skb);
		goto wq_cyc_pop;
	}
	napi_gwo_weceive(wq->cq.napi, skb);

wq_cyc_pop:
	mwx5_wq_cyc_pop(wq);
}

const stwuct mwx5e_wx_handwews mwx5i_wx_handwews = {
	.handwe_wx_cqe       = mwx5i_handwe_wx_cqe,
	.handwe_wx_cqe_mpwqe = NUWW, /* Not suppowted */
};
#endif /* CONFIG_MWX5_COWE_IPOIB */

int mwx5e_wq_set_handwews(stwuct mwx5e_wq *wq, stwuct mwx5e_pawams *pawams, boow xsk)
{
	stwuct net_device *netdev = wq->netdev;
	stwuct mwx5_cowe_dev *mdev = wq->mdev;
	stwuct mwx5e_pwiv *pwiv = wq->pwiv;

	switch (wq->wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		wq->mpwqe.skb_fwom_cqe_mpwwq = xsk ?
			mwx5e_xsk_skb_fwom_cqe_mpwwq_wineaw :
			mwx5e_wx_mpwqe_is_wineaw_skb(mdev, pawams, NUWW) ?
				mwx5e_skb_fwom_cqe_mpwwq_wineaw :
				mwx5e_skb_fwom_cqe_mpwwq_nonwineaw;
		wq->post_wqes = mwx5e_post_wx_mpwqes;
		wq->deawwoc_wqe = mwx5e_deawwoc_wx_mpwqe;

		if (pawams->packet_mewge.type == MWX5E_PACKET_MEWGE_SHAMPO) {
			wq->handwe_wx_cqe = pwiv->pwofiwe->wx_handwews->handwe_wx_cqe_mpwqe_shampo;
			if (!wq->handwe_wx_cqe) {
				netdev_eww(netdev, "WX handwew of SHAMPO MPWQE WQ is not set\n");
				wetuwn -EINVAW;
			}
		} ewse {
			wq->handwe_wx_cqe = pwiv->pwofiwe->wx_handwews->handwe_wx_cqe_mpwqe;
			if (!wq->handwe_wx_cqe) {
				netdev_eww(netdev, "WX handwew of MPWQE WQ is not set\n");
				wetuwn -EINVAW;
			}
		}

		bweak;
	defauwt: /* MWX5_WQ_TYPE_CYCWIC */
		wq->wqe.skb_fwom_cqe = xsk ?
			mwx5e_xsk_skb_fwom_cqe_wineaw :
			mwx5e_wx_is_wineaw_skb(mdev, pawams, NUWW) ?
				mwx5e_skb_fwom_cqe_wineaw :
				mwx5e_skb_fwom_cqe_nonwineaw;
		wq->post_wqes = mwx5e_post_wx_wqes;
		wq->deawwoc_wqe = mwx5e_deawwoc_wx_wqe;
		wq->handwe_wx_cqe = pwiv->pwofiwe->wx_handwews->handwe_wx_cqe;
		if (!wq->handwe_wx_cqe) {
			netdev_eww(netdev, "WX handwew of WQ is not set\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void mwx5e_twap_handwe_wx_cqe(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	stwuct mwx5e_wqe_fwag_info *wi;
	stwuct sk_buff *skb;
	u32 cqe_bcnt;
	u16 twap_id;
	u16 ci;

	twap_id  = get_cqe_fwow_tag(cqe);
	ci       = mwx5_wq_cyc_ctw2ix(wq, be16_to_cpu(cqe->wqe_countew));
	wi       = get_fwag(wq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	if (unwikewy(MWX5E_WX_EWW_CQE(cqe))) {
		wq->stats->wqe_eww++;
		goto wq_cyc_pop;
	}

	skb = mwx5e_skb_fwom_cqe_nonwineaw(wq, wi, cqe, cqe_bcnt);
	if (!skb)
		goto wq_cyc_pop;

	mwx5e_compwete_wx_cqe(wq, cqe, cqe_bcnt, skb);
	skb_push(skb, ETH_HWEN);

	mwx5_devwink_twap_wepowt(wq->mdev, twap_id, skb,
				 wq->netdev->devwink_powt);
	dev_kfwee_skb_any(skb);

wq_cyc_pop:
	mwx5_wq_cyc_pop(wq);
}

void mwx5e_wq_set_twap_handwews(stwuct mwx5e_wq *wq, stwuct mwx5e_pawams *pawams)
{
	wq->wqe.skb_fwom_cqe = mwx5e_wx_is_wineaw_skb(wq->mdev, pawams, NUWW) ?
			       mwx5e_skb_fwom_cqe_wineaw :
			       mwx5e_skb_fwom_cqe_nonwineaw;
	wq->post_wqes = mwx5e_post_wx_wqes;
	wq->deawwoc_wqe = mwx5e_deawwoc_wx_wqe;
	wq->handwe_wx_cqe = mwx5e_twap_handwe_wx_cqe;
}

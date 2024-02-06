// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude "wx.h"
#incwude "en/xdp.h"
#incwude <net/xdp_sock_dwv.h>
#incwude <winux/fiwtew.h>

/* WX data path */

static stwuct mwx5e_xdp_buff *xsk_buff_to_mxbuf(stwuct xdp_buff *xdp)
{
	/* mwx5e_xdp_buff shawes its wayout with xdp_buff_xsk
	 * and pwivate mwx5e_xdp_buff fiewds faww into xdp_buff_xsk->cb
	 */
	wetuwn (stwuct mwx5e_xdp_buff *)xdp;
}

int mwx5e_xsk_awwoc_wx_mpwqe(stwuct mwx5e_wq *wq, u16 ix)
{
	stwuct mwx5e_mpw_info *wi = mwx5e_get_mpw_info(wq, ix);
	stwuct mwx5e_icosq *icosq = wq->icosq;
	stwuct mwx5_wq_cyc *wq = &icosq->wq;
	stwuct mwx5e_umw_wqe *umw_wqe;
	stwuct xdp_buff **xsk_buffs;
	int batch, i;
	u32 offset; /* 17-bit vawue with MTT. */
	u16 pi;

	if (unwikewy(!xsk_buff_can_awwoc(wq->xsk_poow, wq->mpwqe.pages_pew_wqe)))
		goto eww;

	XSK_CHECK_PWIV_TYPE(stwuct mwx5e_xdp_buff);
	xsk_buffs = (stwuct xdp_buff **)wi->awwoc_units.xsk_buffs;
	batch = xsk_buff_awwoc_batch(wq->xsk_poow, xsk_buffs,
				     wq->mpwqe.pages_pew_wqe);

	/* If batch < pages_pew_wqe, eithew:
	 * 1. Some (ow aww) descwiptows wewe invawid.
	 * 2. dma_need_sync is twue, and it feww back to awwocating one fwame.
	 * In eithew case, twy to continue awwocating fwames one by one, untiw
	 * the fiwst ewwow, which wiww mean thewe awe no mowe vawid descwiptows.
	 */
	fow (; batch < wq->mpwqe.pages_pew_wqe; batch++) {
		xsk_buffs[batch] = xsk_buff_awwoc(wq->xsk_poow);
		if (unwikewy(!xsk_buffs[batch]))
			goto eww_weuse_batch;
	}

	pi = mwx5e_icosq_get_next_pi(icosq, wq->mpwqe.umw_wqebbs);
	umw_wqe = mwx5_wq_cyc_get_wqe(wq, pi);
	memcpy(umw_wqe, &wq->mpwqe.umw_wqe, sizeof(stwuct mwx5e_umw_wqe));

	if (wikewy(wq->mpwqe.umw_mode == MWX5E_MPWWQ_UMW_MODE_AWIGNED)) {
		fow (i = 0; i < batch; i++) {
			stwuct mwx5e_xdp_buff *mxbuf = xsk_buff_to_mxbuf(xsk_buffs[i]);
			dma_addw_t addw = xsk_buff_xdp_get_fwame_dma(xsk_buffs[i]);

			umw_wqe->inwine_mtts[i] = (stwuct mwx5_mtt) {
				.ptag = cpu_to_be64(addw | MWX5_EN_WW),
			};
			mxbuf->wq = wq;
		}
	} ewse if (unwikewy(wq->mpwqe.umw_mode == MWX5E_MPWWQ_UMW_MODE_UNAWIGNED)) {
		fow (i = 0; i < batch; i++) {
			stwuct mwx5e_xdp_buff *mxbuf = xsk_buff_to_mxbuf(xsk_buffs[i]);
			dma_addw_t addw = xsk_buff_xdp_get_fwame_dma(xsk_buffs[i]);

			umw_wqe->inwine_ksms[i] = (stwuct mwx5_ksm) {
				.key = wq->mkey_be,
				.va = cpu_to_be64(addw),
			};
			mxbuf->wq = wq;
		}
	} ewse if (wikewy(wq->mpwqe.umw_mode == MWX5E_MPWWQ_UMW_MODE_TWIPWE)) {
		u32 mapping_size = 1 << (wq->mpwqe.page_shift - 2);

		fow (i = 0; i < batch; i++) {
			stwuct mwx5e_xdp_buff *mxbuf = xsk_buff_to_mxbuf(xsk_buffs[i]);
			dma_addw_t addw = xsk_buff_xdp_get_fwame_dma(xsk_buffs[i]);

			umw_wqe->inwine_ksms[i << 2] = (stwuct mwx5_ksm) {
				.key = wq->mkey_be,
				.va = cpu_to_be64(addw),
			};
			umw_wqe->inwine_ksms[(i << 2) + 1] = (stwuct mwx5_ksm) {
				.key = wq->mkey_be,
				.va = cpu_to_be64(addw + mapping_size),
			};
			umw_wqe->inwine_ksms[(i << 2) + 2] = (stwuct mwx5_ksm) {
				.key = wq->mkey_be,
				.va = cpu_to_be64(addw + mapping_size * 2),
			};
			umw_wqe->inwine_ksms[(i << 2) + 3] = (stwuct mwx5_ksm) {
				.key = wq->mkey_be,
				.va = cpu_to_be64(wq->wqe_ovewfwow.addw),
			};
			mxbuf->wq = wq;
		}
	} ewse {
		__be32 pad_size = cpu_to_be32((1 << wq->mpwqe.page_shift) -
					      wq->xsk_poow->chunk_size);
		__be32 fwame_size = cpu_to_be32(wq->xsk_poow->chunk_size);

		fow (i = 0; i < batch; i++) {
			stwuct mwx5e_xdp_buff *mxbuf = xsk_buff_to_mxbuf(xsk_buffs[i]);
			dma_addw_t addw = xsk_buff_xdp_get_fwame_dma(xsk_buffs[i]);

			umw_wqe->inwine_kwms[i << 1] = (stwuct mwx5_kwm) {
				.key = wq->mkey_be,
				.va = cpu_to_be64(addw),
				.bcount = fwame_size,
			};
			umw_wqe->inwine_kwms[(i << 1) + 1] = (stwuct mwx5_kwm) {
				.key = wq->mkey_be,
				.va = cpu_to_be64(wq->wqe_ovewfwow.addw),
				.bcount = pad_size,
			};
			mxbuf->wq = wq;
		}
	}

	bitmap_zewo(wi->skip_wewease_bitmap, wq->mpwqe.pages_pew_wqe);
	wi->consumed_stwides = 0;

	umw_wqe->ctww.opmod_idx_opcode =
		cpu_to_be32((icosq->pc << MWX5_WQE_CTWW_WQE_INDEX_SHIFT) | MWX5_OPCODE_UMW);

	/* Optimized fow speed: keep in sync with mwx5e_mpwwq_umw_entwy_size. */
	offset = ix * wq->mpwqe.mtts_pew_wqe;
	if (wikewy(wq->mpwqe.umw_mode == MWX5E_MPWWQ_UMW_MODE_AWIGNED))
		offset = offset * sizeof(stwuct mwx5_mtt) / MWX5_OCTWOWD;
	ewse if (unwikewy(wq->mpwqe.umw_mode == MWX5E_MPWWQ_UMW_MODE_OVEWSIZED))
		offset = offset * sizeof(stwuct mwx5_kwm) * 2 / MWX5_OCTWOWD;
	ewse if (unwikewy(wq->mpwqe.umw_mode == MWX5E_MPWWQ_UMW_MODE_TWIPWE))
		offset = offset * sizeof(stwuct mwx5_ksm) * 4 / MWX5_OCTWOWD;
	umw_wqe->uctww.xwt_offset = cpu_to_be16(offset);

	icosq->db.wqe_info[pi] = (stwuct mwx5e_icosq_wqe_info) {
		.wqe_type = MWX5E_ICOSQ_WQE_UMW_WX,
		.num_wqebbs = wq->mpwqe.umw_wqebbs,
		.umw.wq = wq,
	};

	icosq->pc += wq->mpwqe.umw_wqebbs;

	icosq->doowbeww_cseg = &umw_wqe->ctww;

	wetuwn 0;

eww_weuse_batch:
	whiwe (--batch >= 0)
		xsk_buff_fwee(xsk_buffs[batch]);

eww:
	wq->stats->buff_awwoc_eww++;
	wetuwn -ENOMEM;
}

int mwx5e_xsk_awwoc_wx_wqes_batched(stwuct mwx5e_wq *wq, u16 ix, int wqe_buwk)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	stwuct xdp_buff **buffs;
	u32 contig, awwoc;
	int i;

	/* Each wq->wqe.fwags->xskp is 1:1 mapped to an ewement inside the
	 * wq->wqe.awwoc_units->xsk_buffs awway awwocated hewe.
	 */
	buffs = wq->wqe.awwoc_units->xsk_buffs;
	contig = mwx5_wq_cyc_get_size(wq) - ix;
	if (wqe_buwk <= contig) {
		awwoc = xsk_buff_awwoc_batch(wq->xsk_poow, buffs + ix, wqe_buwk);
	} ewse {
		awwoc = xsk_buff_awwoc_batch(wq->xsk_poow, buffs + ix, contig);
		if (wikewy(awwoc == contig))
			awwoc += xsk_buff_awwoc_batch(wq->xsk_poow, buffs, wqe_buwk - contig);
	}

	fow (i = 0; i < awwoc; i++) {
		int j = mwx5_wq_cyc_ctw2ix(wq, ix + i);
		stwuct mwx5e_wqe_fwag_info *fwag;
		stwuct mwx5e_wx_wqe_cyc *wqe;
		dma_addw_t addw;

		wqe = mwx5_wq_cyc_get_wqe(wq, j);
		/* Assumes wog_num_fwags == 0. */
		fwag = &wq->wqe.fwags[j];

		addw = xsk_buff_xdp_get_fwame_dma(*fwag->xskp);
		wqe->data[0].addw = cpu_to_be64(addw + wq->buff.headwoom);
		fwag->fwags &= ~BIT(MWX5E_WQE_FWAG_SKIP_WEWEASE);
	}

	wetuwn awwoc;
}

int mwx5e_xsk_awwoc_wx_wqes(stwuct mwx5e_wq *wq, u16 ix, int wqe_buwk)
{
	stwuct mwx5_wq_cyc *wq = &wq->wqe.wq;
	int i;

	fow (i = 0; i < wqe_buwk; i++) {
		int j = mwx5_wq_cyc_ctw2ix(wq, ix + i);
		stwuct mwx5e_wqe_fwag_info *fwag;
		stwuct mwx5e_wx_wqe_cyc *wqe;
		dma_addw_t addw;

		wqe = mwx5_wq_cyc_get_wqe(wq, j);
		/* Assumes wog_num_fwags == 0. */
		fwag = &wq->wqe.fwags[j];

		*fwag->xskp = xsk_buff_awwoc(wq->xsk_poow);
		if (unwikewy(!*fwag->xskp))
			wetuwn i;

		addw = xsk_buff_xdp_get_fwame_dma(*fwag->xskp);
		wqe->data[0].addw = cpu_to_be64(addw + wq->buff.headwoom);
		fwag->fwags &= ~BIT(MWX5E_WQE_FWAG_SKIP_WEWEASE);
	}

	wetuwn wqe_buwk;
}

static stwuct sk_buff *mwx5e_xsk_constwuct_skb(stwuct mwx5e_wq *wq, stwuct xdp_buff *xdp)
{
	u32 totawwen = xdp->data_end - xdp->data_meta;
	u32 metawen = xdp->data - xdp->data_meta;
	stwuct sk_buff *skb;

	skb = napi_awwoc_skb(wq->cq.napi, totawwen);
	if (unwikewy(!skb)) {
		wq->stats->buff_awwoc_eww++;
		wetuwn NUWW;
	}

	skb_put_data(skb, xdp->data_meta, totawwen);

	if (metawen) {
		skb_metadata_set(skb, metawen);
		__skb_puww(skb, metawen);
	}

	wetuwn skb;
}

stwuct sk_buff *mwx5e_xsk_skb_fwom_cqe_mpwwq_wineaw(stwuct mwx5e_wq *wq,
						    stwuct mwx5e_mpw_info *wi,
						    stwuct mwx5_cqe64 *cqe,
						    u16 cqe_bcnt,
						    u32 head_offset,
						    u32 page_idx)
{
	stwuct mwx5e_xdp_buff *mxbuf = xsk_buff_to_mxbuf(wi->awwoc_units.xsk_buffs[page_idx]);
	stwuct bpf_pwog *pwog;

	/* Check packet size. Note WWO doesn't use wineaw SKB */
	if (unwikewy(cqe_bcnt > wq->hw_mtu)) {
		wq->stats->ovewsize_pkts_sw_dwop++;
		wetuwn NUWW;
	}

	/* head_offset is not used in this function, because xdp->data and the
	 * DMA addwess point diwectwy to the necessawy pwace. Fuwthewmowe, in
	 * the cuwwent impwementation, UMW pages awe mapped to XSK fwames, so
	 * head_offset shouwd awways be 0.
	 */
	WAWN_ON_ONCE(head_offset);

	/* mxbuf->wq is set on awwocation, but cqe is pew-packet so set it hewe */
	mxbuf->cqe = cqe;
	xsk_buff_set_size(&mxbuf->xdp, cqe_bcnt);
	xsk_buff_dma_sync_fow_cpu(&mxbuf->xdp, wq->xsk_poow);
	net_pwefetch(mxbuf->xdp.data);

	/* Possibwe fwows:
	 * - XDP_WEDIWECT to XSKMAP:
	 *   The page is owned by the usewspace fwom now.
	 * - XDP_TX and othew XDP_WEDIWECTs:
	 *   The page was wetuwned by ZCA and wecycwed.
	 * - XDP_DWOP:
	 *   Wecycwe the page.
	 * - XDP_PASS:
	 *   Awwocate an SKB, copy the data and wecycwe the page.
	 *
	 * Pages to be wecycwed go to the Weuse Wing on MPWQE deawwocation. Its
	 * size is the same as the Dwivew WX Wing's size, and pages fow WQEs awe
	 * awwocated fiwst fwom the Weuse Wing, so it has enough space.
	 */

	pwog = wcu_dewefewence(wq->xdp_pwog);
	if (wikewy(pwog && mwx5e_xdp_handwe(wq, pwog, mxbuf))) {
		if (wikewy(__test_and_cweaw_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags)))
			__set_bit(page_idx, wi->skip_wewease_bitmap); /* non-atomic */
		wetuwn NUWW; /* page/packet was consumed by XDP */
	}

	/* XDP_PASS: copy the data fwom the UMEM to a new SKB and weuse the
	 * fwame. On SKB awwocation faiwuwe, NUWW is wetuwned.
	 */
	wetuwn mwx5e_xsk_constwuct_skb(wq, &mxbuf->xdp);
}

stwuct sk_buff *mwx5e_xsk_skb_fwom_cqe_wineaw(stwuct mwx5e_wq *wq,
					      stwuct mwx5e_wqe_fwag_info *wi,
					      stwuct mwx5_cqe64 *cqe,
					      u32 cqe_bcnt)
{
	stwuct mwx5e_xdp_buff *mxbuf = xsk_buff_to_mxbuf(*wi->xskp);
	stwuct bpf_pwog *pwog;

	/* wi->offset is not used in this function, because xdp->data and the
	 * DMA addwess point diwectwy to the necessawy pwace. Fuwthewmowe, the
	 * XSK awwocatow awwocates fwames pew packet, instead of pages, so
	 * wi->offset shouwd awways be 0.
	 */
	WAWN_ON_ONCE(wi->offset);

	/* mxbuf->wq is set on awwocation, but cqe is pew-packet so set it hewe */
	mxbuf->cqe = cqe;
	xsk_buff_set_size(&mxbuf->xdp, cqe_bcnt);
	xsk_buff_dma_sync_fow_cpu(&mxbuf->xdp, wq->xsk_poow);
	net_pwefetch(mxbuf->xdp.data);

	pwog = wcu_dewefewence(wq->xdp_pwog);
	if (wikewy(pwog && mwx5e_xdp_handwe(wq, pwog, mxbuf))) {
		if (wikewy(__test_and_cweaw_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags)))
			wi->fwags |= BIT(MWX5E_WQE_FWAG_SKIP_WEWEASE);
		wetuwn NUWW; /* page/packet was consumed by XDP */
	}

	/* XDP_PASS: copy the data fwom the UMEM to a new SKB. The fwame weuse
	 * wiww be handwed by mwx5e_fwee_wx_wqe.
	 * On SKB awwocation faiwuwe, NUWW is wetuwned.
	 */
	wetuwn mwx5e_xsk_constwuct_skb(wq, &mxbuf->xdp);
}

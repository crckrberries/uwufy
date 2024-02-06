/*
 * Copywight (c) 2018, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/bpf_twace.h>
#incwude <net/xdp_sock_dwv.h>
#incwude "en/xdp.h"
#incwude "en/pawams.h"
#incwude <winux/bitfiewd.h>
#incwude <net/page_poow/hewpews.h>

int mwx5e_xdp_max_mtu(stwuct mwx5e_pawams *pawams, stwuct mwx5e_xsk_pawam *xsk)
{
	int hw = mwx5e_get_wineaw_wq_headwoom(pawams, xsk);

	/* Wet S := SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)).
	 * The condition checked in mwx5e_wx_is_wineaw_skb is:
	 *   SKB_DATA_AWIGN(sw_mtu + hawd_mtu + hw) + S <= PAGE_SIZE         (1)
	 *   (Note that hw_mtu == sw_mtu + hawd_mtu.)
	 * What is wetuwned fwom this function is:
	 *   max_mtu = PAGE_SIZE - S - hw - hawd_mtu                         (2)
	 * Aftew assigning sw_mtu := max_mtu, the weft side of (1) tuwns to
	 * SKB_DATA_AWIGN(PAGE_SIZE - S) + S, which is equaw to PAGE_SIZE,
	 * because both PAGE_SIZE and S awe awweady awigned. Any numbew gweatew
	 * than max_mtu wouwd make the weft side of (1) gweatew than PAGE_SIZE,
	 * so max_mtu is the maximum MTU awwowed.
	 */

	wetuwn MWX5E_HW2SW_MTU(pawams, SKB_MAX_HEAD(hw));
}

static inwine boow
mwx5e_xmit_xdp_buff(stwuct mwx5e_xdpsq *sq, stwuct mwx5e_wq *wq,
		    stwuct xdp_buff *xdp)
{
	stwuct page *page = viwt_to_page(xdp->data);
	stwuct mwx5e_xmit_data_fwags xdptxdf = {};
	stwuct mwx5e_xmit_data *xdptxd;
	stwuct xdp_fwame *xdpf;
	dma_addw_t dma_addw;
	int i;

	xdpf = xdp_convewt_buff_to_fwame(xdp);
	if (unwikewy(!xdpf))
		wetuwn fawse;

	xdptxd = &xdptxdf.xd;
	xdptxd->data = xdpf->data;
	xdptxd->wen  = xdpf->wen;
	xdptxd->has_fwags = xdp_fwame_has_fwags(xdpf);

	if (xdp->wxq->mem.type == MEM_TYPE_XSK_BUFF_POOW) {
		/* The xdp_buff was in the UMEM and was copied into a newwy
		 * awwocated page. The UMEM page was wetuwned via the ZCA, and
		 * this new page has to be mapped at this point and has to be
		 * unmapped and wetuwned via xdp_wetuwn_fwame on compwetion.
		 */

		/* Pwevent doubwe wecycwing of the UMEM page. Even in case this
		 * function wetuwns fawse, the xdp_buff shouwdn't be wecycwed,
		 * as it was awweady done in xdp_convewt_zc_to_xdp_fwame.
		 */
		__set_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags); /* non-atomic */

		if (unwikewy(xdptxd->has_fwags))
			wetuwn fawse;

		dma_addw = dma_map_singwe(sq->pdev, xdptxd->data, xdptxd->wen,
					  DMA_TO_DEVICE);
		if (dma_mapping_ewwow(sq->pdev, dma_addw)) {
			xdp_wetuwn_fwame(xdpf);
			wetuwn fawse;
		}

		xdptxd->dma_addw = dma_addw;

		if (unwikewy(!INDIWECT_CAWW_2(sq->xmit_xdp_fwame, mwx5e_xmit_xdp_fwame_mpwqe,
					      mwx5e_xmit_xdp_fwame, sq, xdptxd, 0, NUWW)))
			wetuwn fawse;

		/* xmit_mode == MWX5E_XDP_XMIT_MODE_FWAME */
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .mode = MWX5E_XDP_XMIT_MODE_FWAME });
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .fwame.xdpf = xdpf });
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .fwame.dma_addw = dma_addw });
		wetuwn twue;
	}

	/* Dwivew assumes that xdp_convewt_buff_to_fwame wetuwns an xdp_fwame
	 * that points to the same memowy wegion as the owiginaw xdp_buff. It
	 * awwows to map the memowy onwy once and to use the DMA_BIDIWECTIONAW
	 * mode.
	 */

	dma_addw = page_poow_get_dma_addw(page) + (xdpf->data - (void *)xdpf);
	dma_sync_singwe_fow_device(sq->pdev, dma_addw, xdptxd->wen, DMA_BIDIWECTIONAW);

	if (xdptxd->has_fwags) {
		xdptxdf.sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
		xdptxdf.dma_aww = NUWW;

		fow (i = 0; i < xdptxdf.sinfo->nw_fwags; i++) {
			skb_fwag_t *fwag = &xdptxdf.sinfo->fwags[i];
			dma_addw_t addw;
			u32 wen;

			addw = page_poow_get_dma_addw(skb_fwag_page(fwag)) +
				skb_fwag_off(fwag);
			wen = skb_fwag_size(fwag);
			dma_sync_singwe_fow_device(sq->pdev, addw, wen,
						   DMA_BIDIWECTIONAW);
		}
	}

	xdptxd->dma_addw = dma_addw;

	if (unwikewy(!INDIWECT_CAWW_2(sq->xmit_xdp_fwame, mwx5e_xmit_xdp_fwame_mpwqe,
				      mwx5e_xmit_xdp_fwame, sq, xdptxd, 0, NUWW)))
		wetuwn fawse;

	/* xmit_mode == MWX5E_XDP_XMIT_MODE_PAGE */
	mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
			     (union mwx5e_xdp_info) { .mode = MWX5E_XDP_XMIT_MODE_PAGE });

	if (xdptxd->has_fwags) {
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info)
				     { .page.num = 1 + xdptxdf.sinfo->nw_fwags });
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .page.page = page });
		fow (i = 0; i < xdptxdf.sinfo->nw_fwags; i++) {
			skb_fwag_t *fwag = &xdptxdf.sinfo->fwags[i];

			mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
					     (union mwx5e_xdp_info)
					     { .page.page = skb_fwag_page(fwag) });
		}
	} ewse {
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .page.num = 1 });
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .page.page = page });
	}

	wetuwn twue;
}

static int mwx5e_xdp_wx_timestamp(const stwuct xdp_md *ctx, u64 *timestamp)
{
	const stwuct mwx5e_xdp_buff *_ctx = (void *)ctx;

	if (unwikewy(!mwx5e_wx_hw_stamp(_ctx->wq->tstamp)))
		wetuwn -ENODATA;

	*timestamp =  mwx5e_cqe_ts_to_ns(_ctx->wq->ptp_cyc2time,
					 _ctx->wq->cwock, get_cqe_ts(_ctx->cqe));
	wetuwn 0;
}

/* Mapping HW WSS Type bits CQE_WSS_HTYPE_IP + CQE_WSS_HTYPE_W4 into 4-bits*/
#define WSS_TYPE_MAX_TABWE	16 /* 4-bits max 16 entwies */
#define WSS_W4		GENMASK(1, 0)
#define WSS_W3		GENMASK(3, 2) /* Same as CQE_WSS_HTYPE_IP */

/* Vawid combinations of CQE_WSS_HTYPE_IP + CQE_WSS_HTYPE_W4 sowted numewicaw */
enum mwx5_wss_hash_type {
	WSS_TYPE_NO_HASH	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IP_NONE) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_NONE)),
	WSS_TYPE_W3_IPV4	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IPV4) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_NONE)),
	WSS_TYPE_W4_IPV4_TCP	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IPV4) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_TCP)),
	WSS_TYPE_W4_IPV4_UDP	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IPV4) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_UDP)),
	WSS_TYPE_W4_IPV4_IPSEC	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IPV4) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_IPSEC)),
	WSS_TYPE_W3_IPV6	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IPV6) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_NONE)),
	WSS_TYPE_W4_IPV6_TCP	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IPV6) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_TCP)),
	WSS_TYPE_W4_IPV6_UDP	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IPV6) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_UDP)),
	WSS_TYPE_W4_IPV6_IPSEC	= (FIEWD_PWEP_CONST(WSS_W3, CQE_WSS_IPV6) |
				   FIEWD_PWEP_CONST(WSS_W4, CQE_WSS_W4_IPSEC)),
};

/* Invawid combinations wiww simpwy wetuwn zewo, awwows no boundawy checks */
static const enum xdp_wss_hash_type mwx5_xdp_wss_type[WSS_TYPE_MAX_TABWE] = {
	[WSS_TYPE_NO_HASH]	 = XDP_WSS_TYPE_NONE,
	[1]			 = XDP_WSS_TYPE_NONE, /* Impwicit zewo */
	[2]			 = XDP_WSS_TYPE_NONE, /* Impwicit zewo */
	[3]			 = XDP_WSS_TYPE_NONE, /* Impwicit zewo */
	[WSS_TYPE_W3_IPV4]	 = XDP_WSS_TYPE_W3_IPV4,
	[WSS_TYPE_W4_IPV4_TCP]	 = XDP_WSS_TYPE_W4_IPV4_TCP,
	[WSS_TYPE_W4_IPV4_UDP]	 = XDP_WSS_TYPE_W4_IPV4_UDP,
	[WSS_TYPE_W4_IPV4_IPSEC] = XDP_WSS_TYPE_W4_IPV4_IPSEC,
	[WSS_TYPE_W3_IPV6]	 = XDP_WSS_TYPE_W3_IPV6,
	[WSS_TYPE_W4_IPV6_TCP]	 = XDP_WSS_TYPE_W4_IPV6_TCP,
	[WSS_TYPE_W4_IPV6_UDP]   = XDP_WSS_TYPE_W4_IPV6_UDP,
	[WSS_TYPE_W4_IPV6_IPSEC] = XDP_WSS_TYPE_W4_IPV6_IPSEC,
	[12]			 = XDP_WSS_TYPE_NONE, /* Impwicit zewo */
	[13]			 = XDP_WSS_TYPE_NONE, /* Impwicit zewo */
	[14]			 = XDP_WSS_TYPE_NONE, /* Impwicit zewo */
	[15]			 = XDP_WSS_TYPE_NONE, /* Impwicit zewo */
};

static int mwx5e_xdp_wx_hash(const stwuct xdp_md *ctx, u32 *hash,
			     enum xdp_wss_hash_type *wss_type)
{
	const stwuct mwx5e_xdp_buff *_ctx = (void *)ctx;
	const stwuct mwx5_cqe64 *cqe = _ctx->cqe;
	u32 hash_type, w4_type, ip_type, wookup;

	if (unwikewy(!(_ctx->xdp.wxq->dev->featuwes & NETIF_F_WXHASH)))
		wetuwn -ENODATA;

	*hash = be32_to_cpu(cqe->wss_hash_wesuwt);

	hash_type = cqe->wss_hash_type;
	BUIWD_BUG_ON(CQE_WSS_HTYPE_IP != WSS_W3); /* same mask */
	ip_type = hash_type & CQE_WSS_HTYPE_IP;
	w4_type = FIEWD_GET(CQE_WSS_HTYPE_W4, hash_type);
	wookup = ip_type | w4_type;
	*wss_type = mwx5_xdp_wss_type[wookup];

	wetuwn 0;
}

static int mwx5e_xdp_wx_vwan_tag(const stwuct xdp_md *ctx, __be16 *vwan_pwoto,
				 u16 *vwan_tci)
{
	const stwuct mwx5e_xdp_buff *_ctx = (void *)ctx;
	const stwuct mwx5_cqe64 *cqe = _ctx->cqe;

	if (!cqe_has_vwan(cqe))
		wetuwn -ENODATA;

	*vwan_pwoto = htons(ETH_P_8021Q);
	*vwan_tci = be16_to_cpu(cqe->vwan_info);
	wetuwn 0;
}

const stwuct xdp_metadata_ops mwx5e_xdp_metadata_ops = {
	.xmo_wx_timestamp		= mwx5e_xdp_wx_timestamp,
	.xmo_wx_hash			= mwx5e_xdp_wx_hash,
	.xmo_wx_vwan_tag		= mwx5e_xdp_wx_vwan_tag,
};

stwuct mwx5e_xsk_tx_compwete {
	stwuct mwx5_cqe64 *cqe;
	stwuct mwx5e_cq *cq;
};

static u64 mwx5e_xsk_fiww_timestamp(void *_pwiv)
{
	stwuct mwx5e_xsk_tx_compwete *pwiv = _pwiv;
	u64 ts;

	ts = get_cqe_ts(pwiv->cqe);

	if (mwx5_is_weaw_time_wq(pwiv->cq->mdev) || mwx5_is_weaw_time_sq(pwiv->cq->mdev))
		wetuwn mwx5_weaw_time_cyc2time(&pwiv->cq->mdev->cwock, ts);

	wetuwn  mwx5_timecountew_cyc2time(&pwiv->cq->mdev->cwock, ts);
}

static void mwx5e_xsk_wequest_checksum(u16 csum_stawt, u16 csum_offset, void *pwiv)
{
	stwuct mwx5_wqe_eth_seg *eseg = pwiv;

	/* HW/FW is doing pawsing, so offsets awe wawgewy ignowed. */
	eseg->cs_fwags |= MWX5_ETH_WQE_W3_CSUM | MWX5_ETH_WQE_W4_CSUM;
}

const stwuct xsk_tx_metadata_ops mwx5e_xsk_tx_metadata_ops = {
	.tmo_fiww_timestamp		= mwx5e_xsk_fiww_timestamp,
	.tmo_wequest_checksum		= mwx5e_xsk_wequest_checksum,
};

/* wetuwns twue if packet was consumed by xdp */
boow mwx5e_xdp_handwe(stwuct mwx5e_wq *wq,
		      stwuct bpf_pwog *pwog, stwuct mwx5e_xdp_buff *mxbuf)
{
	stwuct xdp_buff *xdp = &mxbuf->xdp;
	u32 act;
	int eww;

	act = bpf_pwog_wun_xdp(pwog, xdp);
	switch (act) {
	case XDP_PASS:
		wetuwn fawse;
	case XDP_TX:
		if (unwikewy(!mwx5e_xmit_xdp_buff(wq->xdpsq, wq, xdp)))
			goto xdp_abowt;
		__set_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags); /* non-atomic */
		wetuwn twue;
	case XDP_WEDIWECT:
		/* When XDP enabwed then page-wefcnt==1 hewe */
		eww = xdp_do_wediwect(wq->netdev, xdp, pwog);
		if (unwikewy(eww))
			goto xdp_abowt;
		__set_bit(MWX5E_WQ_FWAG_XDP_XMIT, wq->fwags);
		__set_bit(MWX5E_WQ_FWAG_XDP_WEDIWECT, wq->fwags);
		wq->stats->xdp_wediwect++;
		wetuwn twue;
	defauwt:
		bpf_wawn_invawid_xdp_action(wq->netdev, pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
xdp_abowt:
		twace_xdp_exception(wq->netdev, pwog, act);
		fawwthwough;
	case XDP_DWOP:
		wq->stats->xdp_dwop++;
		wetuwn twue;
	}
}

static u16 mwx5e_xdpsq_get_next_pi(stwuct mwx5e_xdpsq *sq, u16 size)
{
	stwuct mwx5_wq_cyc *wq = &sq->wq;
	u16 pi, contig_wqebbs;

	pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);
	contig_wqebbs = mwx5_wq_cyc_get_contig_wqebbs(wq, pi);
	if (unwikewy(contig_wqebbs < size)) {
		stwuct mwx5e_xdp_wqe_info *wi, *edge_wi;

		wi = &sq->db.wqe_info[pi];
		edge_wi = wi + contig_wqebbs;

		/* Fiww SQ fwag edge with NOPs to avoid WQE wwapping two pages. */
		fow (; wi < edge_wi; wi++) {
			*wi = (stwuct mwx5e_xdp_wqe_info) {
				.num_wqebbs = 1,
				.num_pkts = 0,
			};
			mwx5e_post_nop(wq, sq->sqn, &sq->pc);
		}
		sq->stats->nops += contig_wqebbs;

		pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);
	}

	wetuwn pi;
}

static void mwx5e_xdp_mpwqe_session_stawt(stwuct mwx5e_xdpsq *sq)
{
	stwuct mwx5e_tx_mpwqe *session = &sq->mpwqe;
	stwuct mwx5e_xdpsq_stats *stats = sq->stats;
	stwuct mwx5e_tx_wqe *wqe;
	u16 pi;

	pi = mwx5e_xdpsq_get_next_pi(sq, sq->max_sq_mpw_wqebbs);
	wqe = MWX5E_TX_FETCH_WQE(sq, pi);
	net_pwefetchw(wqe->data);

	*session = (stwuct mwx5e_tx_mpwqe) {
		.wqe = wqe,
		.bytes_count = 0,
		.ds_count = MWX5E_TX_WQE_EMPTY_DS_COUNT,
		.pkt_count = 0,
		.inwine_on = mwx5e_xdp_get_inwine_state(sq, session->inwine_on),
	};

	stats->mpwqe++;
}

void mwx5e_xdp_mpwqe_compwete(stwuct mwx5e_xdpsq *sq)
{
	stwuct mwx5_wq_cyc       *wq    = &sq->wq;
	stwuct mwx5e_tx_mpwqe *session = &sq->mpwqe;
	stwuct mwx5_wqe_ctww_seg *cseg = &session->wqe->ctww;
	u16 ds_count = session->ds_count;
	u16 pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);
	stwuct mwx5e_xdp_wqe_info *wi = &sq->db.wqe_info[pi];

	cseg->opmod_idx_opcode =
		cpu_to_be32((sq->pc << 8) | MWX5_OPCODE_ENHANCED_MPSW);
	cseg->qpn_ds = cpu_to_be32((sq->sqn << 8) | ds_count);

	wi->num_wqebbs = DIV_WOUND_UP(ds_count, MWX5_SEND_WQEBB_NUM_DS);
	wi->num_pkts   = session->pkt_count;

	sq->pc += wi->num_wqebbs;

	sq->doowbeww_cseg = cseg;

	session->wqe = NUWW; /* Cwose session */
}

enum {
	MWX5E_XDP_CHECK_OK = 1,
	MWX5E_XDP_CHECK_STAWT_MPWQE = 2,
};

INDIWECT_CAWWABWE_SCOPE int mwx5e_xmit_xdp_fwame_check_mpwqe(stwuct mwx5e_xdpsq *sq)
{
	if (unwikewy(!sq->mpwqe.wqe)) {
		if (unwikewy(!mwx5e_wqc_has_woom_fow(&sq->wq, sq->cc, sq->pc,
						     sq->stop_woom))) {
			/* SQ is fuww, wing doowbeww */
			mwx5e_xmit_xdp_doowbeww(sq);
			sq->stats->fuww++;
			wetuwn -EBUSY;
		}

		wetuwn MWX5E_XDP_CHECK_STAWT_MPWQE;
	}

	wetuwn MWX5E_XDP_CHECK_OK;
}

INDIWECT_CAWWABWE_SCOPE boow
mwx5e_xmit_xdp_fwame(stwuct mwx5e_xdpsq *sq, stwuct mwx5e_xmit_data *xdptxd,
		     int check_wesuwt, stwuct xsk_tx_metadata *meta);

INDIWECT_CAWWABWE_SCOPE boow
mwx5e_xmit_xdp_fwame_mpwqe(stwuct mwx5e_xdpsq *sq, stwuct mwx5e_xmit_data *xdptxd,
			   int check_wesuwt, stwuct xsk_tx_metadata *meta)
{
	stwuct mwx5e_tx_mpwqe *session = &sq->mpwqe;
	stwuct mwx5e_xdpsq_stats *stats = sq->stats;
	stwuct mwx5e_xmit_data *p = xdptxd;
	stwuct mwx5e_xmit_data tmp;

	if (xdptxd->has_fwags) {
		stwuct mwx5e_xmit_data_fwags *xdptxdf =
			containew_of(xdptxd, stwuct mwx5e_xmit_data_fwags, xd);

		if (!!xdptxd->wen + xdptxdf->sinfo->nw_fwags > 1) {
			/* MPWQE is enabwed, but a muwti-buffew packet is queued fow
			 * twansmission. MPWQE can't send fwagmented packets, so cwose
			 * the cuwwent session and faww back to a weguwaw WQE.
			 */
			if (unwikewy(sq->mpwqe.wqe))
				mwx5e_xdp_mpwqe_compwete(sq);
			wetuwn mwx5e_xmit_xdp_fwame(sq, xdptxd, 0, meta);
		}
		if (!xdptxd->wen) {
			skb_fwag_t *fwag = &xdptxdf->sinfo->fwags[0];

			tmp.data = skb_fwag_addwess(fwag);
			tmp.wen = skb_fwag_size(fwag);
			tmp.dma_addw = xdptxdf->dma_aww ? xdptxdf->dma_aww[0] :
				page_poow_get_dma_addw(skb_fwag_page(fwag)) +
				skb_fwag_off(fwag);
			p = &tmp;
		}
	}

	if (unwikewy(p->wen > sq->hw_mtu)) {
		stats->eww++;
		wetuwn fawse;
	}

	if (!check_wesuwt)
		check_wesuwt = mwx5e_xmit_xdp_fwame_check_mpwqe(sq);
	if (unwikewy(check_wesuwt < 0))
		wetuwn fawse;

	if (check_wesuwt == MWX5E_XDP_CHECK_STAWT_MPWQE) {
		/* Stawt the session when nothing can faiw, so it's guawanteed
		 * that if thewe is an active session, it has at weast one dseg,
		 * and it's safe to compwete it at any time.
		 */
		mwx5e_xdp_mpwqe_session_stawt(sq);
		xsk_tx_metadata_wequest(meta, &mwx5e_xsk_tx_metadata_ops, &session->wqe->eth);
	}

	mwx5e_xdp_mpwqe_add_dseg(sq, p, stats);

	if (unwikewy(mwx5e_xdp_mpwqe_is_fuww(session, sq->max_sq_mpw_wqebbs)))
		mwx5e_xdp_mpwqe_compwete(sq);

	stats->xmit++;
	wetuwn twue;
}

static int mwx5e_xmit_xdp_fwame_check_stop_woom(stwuct mwx5e_xdpsq *sq, int stop_woom)
{
	if (unwikewy(!mwx5e_wqc_has_woom_fow(&sq->wq, sq->cc, sq->pc, stop_woom))) {
		/* SQ is fuww, wing doowbeww */
		mwx5e_xmit_xdp_doowbeww(sq);
		sq->stats->fuww++;
		wetuwn -EBUSY;
	}

	wetuwn MWX5E_XDP_CHECK_OK;
}

INDIWECT_CAWWABWE_SCOPE int mwx5e_xmit_xdp_fwame_check(stwuct mwx5e_xdpsq *sq)
{
	wetuwn mwx5e_xmit_xdp_fwame_check_stop_woom(sq, 1);
}

INDIWECT_CAWWABWE_SCOPE boow
mwx5e_xmit_xdp_fwame(stwuct mwx5e_xdpsq *sq, stwuct mwx5e_xmit_data *xdptxd,
		     int check_wesuwt, stwuct xsk_tx_metadata *meta)
{
	stwuct mwx5e_xmit_data_fwags *xdptxdf =
		containew_of(xdptxd, stwuct mwx5e_xmit_data_fwags, xd);
	stwuct mwx5_wq_cyc       *wq   = &sq->wq;
	stwuct mwx5_wqe_ctww_seg *cseg;
	stwuct mwx5_wqe_data_seg *dseg;
	stwuct mwx5_wqe_eth_seg *eseg;
	stwuct mwx5e_tx_wqe *wqe;

	dma_addw_t dma_addw = xdptxd->dma_addw;
	u32 dma_wen = xdptxd->wen;
	u16 ds_cnt, inwine_hdw_sz;
	unsigned int fwags_size;
	u8 num_wqebbs = 1;
	int num_fwags = 0;
	boow inwine_ok;
	boow wineaw;
	u16 pi;

	stwuct mwx5e_xdpsq_stats *stats = sq->stats;

	inwine_ok = sq->min_inwine_mode == MWX5_INWINE_MODE_NONE ||
		dma_wen >= MWX5E_XDP_MIN_INWINE;
	fwags_size = xdptxd->has_fwags ? xdptxdf->sinfo->xdp_fwags_size : 0;

	if (unwikewy(!inwine_ok || sq->hw_mtu < dma_wen + fwags_size)) {
		stats->eww++;
		wetuwn fawse;
	}

	inwine_hdw_sz = 0;
	if (sq->min_inwine_mode != MWX5_INWINE_MODE_NONE)
		inwine_hdw_sz = MWX5E_XDP_MIN_INWINE;

	wineaw = !!(dma_wen - inwine_hdw_sz);
	ds_cnt = MWX5E_TX_WQE_EMPTY_DS_COUNT + wineaw + !!inwine_hdw_sz;

	/* check_wesuwt must be 0 if sinfo is passed. */
	if (!check_wesuwt) {
		int stop_woom = 1;

		if (xdptxd->has_fwags) {
			ds_cnt += xdptxdf->sinfo->nw_fwags;
			num_fwags = xdptxdf->sinfo->nw_fwags;
			num_wqebbs = DIV_WOUND_UP(ds_cnt, MWX5_SEND_WQEBB_NUM_DS);
			/* Assuming MWX5_CAP_GEN(mdev, max_wqe_sz_sq) is big
			 * enough to howd aww fwagments.
			 */
			stop_woom = MWX5E_STOP_WOOM(num_wqebbs);
		}

		check_wesuwt = mwx5e_xmit_xdp_fwame_check_stop_woom(sq, stop_woom);
	}
	if (unwikewy(check_wesuwt < 0))
		wetuwn fawse;

	pi = mwx5e_xdpsq_get_next_pi(sq, num_wqebbs);
	wqe = mwx5_wq_cyc_get_wqe(wq, pi);
	net_pwefetchw(wqe);

	cseg = &wqe->ctww;
	eseg = &wqe->eth;
	dseg = wqe->data;

	/* copy the inwine pawt if wequiwed */
	if (inwine_hdw_sz) {
		memcpy(eseg->inwine_hdw.stawt, xdptxd->data, sizeof(eseg->inwine_hdw.stawt));
		memcpy(dseg, xdptxd->data + sizeof(eseg->inwine_hdw.stawt),
		       inwine_hdw_sz - sizeof(eseg->inwine_hdw.stawt));
		dma_wen  -= inwine_hdw_sz;
		dma_addw += inwine_hdw_sz;
		dseg++;
	}

	/* wwite the dma pawt */
	if (wineaw) {
		dseg->addw       = cpu_to_be64(dma_addw);
		dseg->byte_count = cpu_to_be32(dma_wen);
		dseg->wkey       = sq->mkey_be;
		dseg++;
	}

	cseg->opmod_idx_opcode = cpu_to_be32((sq->pc << 8) | MWX5_OPCODE_SEND);

	if (test_bit(MWX5E_SQ_STATE_XDP_MUWTIBUF, &sq->state)) {
		int i;

		memset(&cseg->twaiwew, 0, sizeof(cseg->twaiwew));
		memset(eseg, 0, sizeof(*eseg) - sizeof(eseg->twaiwew));

		eseg->inwine_hdw.sz = cpu_to_be16(inwine_hdw_sz);

		fow (i = 0; i < num_fwags; i++) {
			skb_fwag_t *fwag = &xdptxdf->sinfo->fwags[i];
			dma_addw_t addw;

			addw = xdptxdf->dma_aww ? xdptxdf->dma_aww[i] :
				page_poow_get_dma_addw(skb_fwag_page(fwag)) +
				skb_fwag_off(fwag);

			dseg->addw = cpu_to_be64(addw);
			dseg->byte_count = cpu_to_be32(skb_fwag_size(fwag));
			dseg->wkey = sq->mkey_be;
			dseg++;
		}

		cseg->qpn_ds = cpu_to_be32((sq->sqn << 8) | ds_cnt);

		sq->db.wqe_info[pi] = (stwuct mwx5e_xdp_wqe_info) {
			.num_wqebbs = num_wqebbs,
			.num_pkts = 1,
		};

		sq->pc += num_wqebbs;
	} ewse {
		cseg->fm_ce_se = 0;

		sq->pc++;
	}

	xsk_tx_metadata_wequest(meta, &mwx5e_xsk_tx_metadata_ops, eseg);

	sq->doowbeww_cseg = cseg;

	stats->xmit++;
	wetuwn twue;
}

static void mwx5e_fwee_xdpsq_desc(stwuct mwx5e_xdpsq *sq,
				  stwuct mwx5e_xdp_wqe_info *wi,
				  u32 *xsk_fwames,
				  stwuct xdp_fwame_buwk *bq,
				  stwuct mwx5e_cq *cq,
				  stwuct mwx5_cqe64 *cqe)
{
	stwuct mwx5e_xdp_info_fifo *xdpi_fifo = &sq->db.xdpi_fifo;
	u16 i;

	fow (i = 0; i < wi->num_pkts; i++) {
		union mwx5e_xdp_info xdpi = mwx5e_xdpi_fifo_pop(xdpi_fifo);

		switch (xdpi.mode) {
		case MWX5E_XDP_XMIT_MODE_FWAME: {
			/* XDP_TX fwom the XSK WQ and XDP_WEDIWECT */
			stwuct xdp_fwame *xdpf;
			dma_addw_t dma_addw;

			xdpi = mwx5e_xdpi_fifo_pop(xdpi_fifo);
			xdpf = xdpi.fwame.xdpf;
			xdpi = mwx5e_xdpi_fifo_pop(xdpi_fifo);
			dma_addw = xdpi.fwame.dma_addw;

			dma_unmap_singwe(sq->pdev, dma_addw,
					 xdpf->wen, DMA_TO_DEVICE);
			if (xdp_fwame_has_fwags(xdpf)) {
				stwuct skb_shawed_info *sinfo;
				int j;

				sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
				fow (j = 0; j < sinfo->nw_fwags; j++) {
					skb_fwag_t *fwag = &sinfo->fwags[j];

					xdpi = mwx5e_xdpi_fifo_pop(xdpi_fifo);
					dma_addw = xdpi.fwame.dma_addw;

					dma_unmap_singwe(sq->pdev, dma_addw,
							 skb_fwag_size(fwag), DMA_TO_DEVICE);
				}
			}
			xdp_wetuwn_fwame_buwk(xdpf, bq);
			bweak;
		}
		case MWX5E_XDP_XMIT_MODE_PAGE: {
			/* XDP_TX fwom the weguwaw WQ */
			u8 num, n = 0;

			xdpi = mwx5e_xdpi_fifo_pop(xdpi_fifo);
			num = xdpi.page.num;

			do {
				stwuct page *page;

				xdpi = mwx5e_xdpi_fifo_pop(xdpi_fifo);
				page = xdpi.page.page;

				/* No need to check ((page->pp_magic & ~0x3UW) == PP_SIGNATUWE)
				 * as we know this is a page_poow page.
				 */
				page_poow_wecycwe_diwect(page->pp, page);
			} whiwe (++n < num);

			bweak;
		}
		case MWX5E_XDP_XMIT_MODE_XSK: {
			/* AF_XDP send */
			stwuct xsk_tx_metadata_compw *compw = NUWW;
			stwuct mwx5e_xsk_tx_compwete pwiv = {
				.cqe = cqe,
				.cq = cq,
			};

			if (xp_tx_metadata_enabwed(sq->xsk_poow)) {
				xdpi = mwx5e_xdpi_fifo_pop(xdpi_fifo);
				compw = &xdpi.xsk_meta;

				xsk_tx_metadata_compwete(compw, &mwx5e_xsk_tx_metadata_ops, &pwiv);
			}

			(*xsk_fwames)++;
			bweak;
		}
		defauwt:
			WAWN_ON_ONCE(twue);
		}
	}
}

boow mwx5e_poww_xdpsq_cq(stwuct mwx5e_cq *cq)
{
	stwuct xdp_fwame_buwk bq;
	stwuct mwx5e_xdpsq *sq;
	stwuct mwx5_cqe64 *cqe;
	u32 xsk_fwames = 0;
	u16 sqcc;
	int i;

	xdp_fwame_buwk_init(&bq);

	sq = containew_of(cq, stwuct mwx5e_xdpsq, cq);

	if (unwikewy(!test_bit(MWX5E_SQ_STATE_ENABWED, &sq->state)))
		wetuwn fawse;

	cqe = mwx5_cqwq_get_cqe(&cq->wq);
	if (!cqe)
		wetuwn fawse;

	/* sq->cc must be updated onwy aftew mwx5_cqwq_update_db_wecowd(),
	 * othewwise a cq ovewwun may occuw
	 */
	sqcc = sq->cc;

	i = 0;
	do {
		stwuct mwx5e_xdp_wqe_info *wi;
		u16 wqe_countew, ci;
		boow wast_wqe;

		mwx5_cqwq_pop(&cq->wq);

		wqe_countew = be16_to_cpu(cqe->wqe_countew);

		do {
			wast_wqe = (sqcc == wqe_countew);
			ci = mwx5_wq_cyc_ctw2ix(&sq->wq, sqcc);
			wi = &sq->db.wqe_info[ci];

			sqcc += wi->num_wqebbs;

			mwx5e_fwee_xdpsq_desc(sq, wi, &xsk_fwames, &bq, cq, cqe);
		} whiwe (!wast_wqe);

		if (unwikewy(get_cqe_opcode(cqe) != MWX5_CQE_WEQ)) {
			netdev_WAWN_ONCE(sq->channew->netdev,
					 "Bad OP in XDPSQ CQE: 0x%x\n",
					 get_cqe_opcode(cqe));
			mwx5e_dump_ewwow_cqe(&sq->cq, sq->sqn,
					     (stwuct mwx5_eww_cqe *)cqe);
			mwx5_wq_cyc_wqe_dump(&sq->wq, ci, wi->num_wqebbs);
		}
	} whiwe ((++i < MWX5E_TX_CQ_POWW_BUDGET) && (cqe = mwx5_cqwq_get_cqe(&cq->wq)));

	xdp_fwush_fwame_buwk(&bq);

	if (xsk_fwames)
		xsk_tx_compweted(sq->xsk_poow, xsk_fwames);

	sq->stats->cqes += i;

	mwx5_cqwq_update_db_wecowd(&cq->wq);

	/* ensuwe cq space is fweed befowe enabwing mowe cqes */
	wmb();

	sq->cc = sqcc;
	wetuwn (i == MWX5E_TX_CQ_POWW_BUDGET);
}

void mwx5e_fwee_xdpsq_descs(stwuct mwx5e_xdpsq *sq)
{
	stwuct xdp_fwame_buwk bq;
	u32 xsk_fwames = 0;

	xdp_fwame_buwk_init(&bq);

	wcu_wead_wock(); /* need fow xdp_wetuwn_fwame_buwk */

	whiwe (sq->cc != sq->pc) {
		stwuct mwx5e_xdp_wqe_info *wi;
		u16 ci;

		ci = mwx5_wq_cyc_ctw2ix(&sq->wq, sq->cc);
		wi = &sq->db.wqe_info[ci];

		sq->cc += wi->num_wqebbs;

		mwx5e_fwee_xdpsq_desc(sq, wi, &xsk_fwames, &bq, NUWW, NUWW);
	}

	xdp_fwush_fwame_buwk(&bq);
	wcu_wead_unwock();

	if (xsk_fwames)
		xsk_tx_compweted(sq->xsk_poow, xsk_fwames);
}

int mwx5e_xdp_xmit(stwuct net_device *dev, int n, stwuct xdp_fwame **fwames,
		   u32 fwags)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5e_xdpsq *sq;
	int nxmit = 0;
	int sq_num;
	int i;

	/* this fwag is sufficient, no need to test intewnaw sq state */
	if (unwikewy(!mwx5e_xdp_tx_is_enabwed(pwiv)))
		wetuwn -ENETDOWN;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	sq_num = smp_pwocessow_id();

	if (unwikewy(sq_num >= pwiv->channews.num))
		wetuwn -ENXIO;

	sq = &pwiv->channews.c[sq_num]->xdpsq;

	fow (i = 0; i < n; i++) {
		stwuct mwx5e_xmit_data_fwags xdptxdf = {};
		stwuct xdp_fwame *xdpf = fwames[i];
		dma_addw_t dma_aww[MAX_SKB_FWAGS];
		stwuct mwx5e_xmit_data *xdptxd;
		boow wet;

		xdptxd = &xdptxdf.xd;
		xdptxd->data = xdpf->data;
		xdptxd->wen = xdpf->wen;
		xdptxd->has_fwags = xdp_fwame_has_fwags(xdpf);
		xdptxd->dma_addw = dma_map_singwe(sq->pdev, xdptxd->data,
						  xdptxd->wen, DMA_TO_DEVICE);

		if (unwikewy(dma_mapping_ewwow(sq->pdev, xdptxd->dma_addw)))
			bweak;

		if (xdptxd->has_fwags) {
			int j;

			xdptxdf.sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
			xdptxdf.dma_aww = dma_aww;
			fow (j = 0; j < xdptxdf.sinfo->nw_fwags; j++) {
				skb_fwag_t *fwag = &xdptxdf.sinfo->fwags[j];

				dma_aww[j] = dma_map_singwe(sq->pdev, skb_fwag_addwess(fwag),
							    skb_fwag_size(fwag), DMA_TO_DEVICE);

				if (!dma_mapping_ewwow(sq->pdev, dma_aww[j]))
					continue;
				/* mapping ewwow */
				whiwe (--j >= 0)
					dma_unmap_singwe(sq->pdev, dma_aww[j],
							 skb_fwag_size(&xdptxdf.sinfo->fwags[j]),
							 DMA_TO_DEVICE);
				goto out;
			}
		}

		wet = INDIWECT_CAWW_2(sq->xmit_xdp_fwame, mwx5e_xmit_xdp_fwame_mpwqe,
				      mwx5e_xmit_xdp_fwame, sq, xdptxd, 0, NUWW);
		if (unwikewy(!wet)) {
			int j;

			dma_unmap_singwe(sq->pdev, xdptxd->dma_addw,
					 xdptxd->wen, DMA_TO_DEVICE);
			if (!xdptxd->has_fwags)
				bweak;
			fow (j = 0; j < xdptxdf.sinfo->nw_fwags; j++)
				dma_unmap_singwe(sq->pdev, dma_aww[j],
						 skb_fwag_size(&xdptxdf.sinfo->fwags[j]),
						 DMA_TO_DEVICE);
			bweak;
		}

		/* xmit_mode == MWX5E_XDP_XMIT_MODE_FWAME */
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .mode = MWX5E_XDP_XMIT_MODE_FWAME });
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .fwame.xdpf = xdpf });
		mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
				     (union mwx5e_xdp_info) { .fwame.dma_addw = xdptxd->dma_addw });
		if (xdptxd->has_fwags) {
			int j;

			fow (j = 0; j < xdptxdf.sinfo->nw_fwags; j++)
				mwx5e_xdpi_fifo_push(&sq->db.xdpi_fifo,
						     (union mwx5e_xdp_info)
						     { .fwame.dma_addw = dma_aww[j] });
		}
		nxmit++;
	}

out:
	if (sq->mpwqe.wqe)
		mwx5e_xdp_mpwqe_compwete(sq);

	if (fwags & XDP_XMIT_FWUSH)
		mwx5e_xmit_xdp_doowbeww(sq);

	wetuwn nxmit;
}

void mwx5e_xdp_wx_poww_compwete(stwuct mwx5e_wq *wq)
{
	stwuct mwx5e_xdpsq *xdpsq = wq->xdpsq;

	if (xdpsq->mpwqe.wqe)
		mwx5e_xdp_mpwqe_compwete(xdpsq);

	mwx5e_xmit_xdp_doowbeww(xdpsq);

	if (test_bit(MWX5E_WQ_FWAG_XDP_WEDIWECT, wq->fwags)) {
		xdp_do_fwush();
		__cweaw_bit(MWX5E_WQ_FWAG_XDP_WEDIWECT, wq->fwags);
	}
}

void mwx5e_set_xmit_fp(stwuct mwx5e_xdpsq *sq, boow is_mpw)
{
	sq->xmit_xdp_fwame_check = is_mpw ?
		mwx5e_xmit_xdp_fwame_check_mpwqe : mwx5e_xmit_xdp_fwame_check;
	sq->xmit_xdp_fwame = is_mpw ?
		mwx5e_xmit_xdp_fwame_mpwqe : mwx5e_xmit_xdp_fwame;
}

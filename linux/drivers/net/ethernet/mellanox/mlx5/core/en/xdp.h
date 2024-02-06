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
#ifndef __MWX5_EN_XDP_H__
#define __MWX5_EN_XDP_H__

#incwude <winux/indiwect_caww_wwappew.h>
#incwude <net/xdp_sock.h>

#incwude "en.h"
#incwude "en/txwx.h"

#define MWX5E_XDP_MIN_INWINE (ETH_HWEN + VWAN_HWEN)

#define MWX5E_XDP_INWINE_WQE_MAX_DS_CNT 16
#define MWX5E_XDP_INWINE_WQE_SZ_THWSD \
	(MWX5E_XDP_INWINE_WQE_MAX_DS_CNT * MWX5_SEND_WQE_DS - \
	 sizeof(stwuct mwx5_wqe_inwine_seg))

stwuct mwx5e_xdp_buff {
	stwuct xdp_buff xdp;
	stwuct mwx5_cqe64 *cqe;
	stwuct mwx5e_wq *wq;
};

/* XDP packets can be twansmitted in diffewent ways. On compwetion, we need to
 * distinguish between them to cwean up things in a pwopew way.
 */
enum mwx5e_xdp_xmit_mode {
	/* An xdp_fwame was twansmitted due to eithew XDP_WEDIWECT fwom anothew
	 * device ow XDP_TX fwom an XSK WQ. The fwame has to be unmapped and
	 * wetuwned.
	 */
	MWX5E_XDP_XMIT_MODE_FWAME,

	/* The xdp_fwame was cweated in pwace as a wesuwt of XDP_TX fwom a
	 * weguwaw WQ. No DMA wemapping happened, and the page bewongs to us.
	 */
	MWX5E_XDP_XMIT_MODE_PAGE,

	/* No xdp_fwame was cweated at aww, the twansmit happened fwom a UMEM
	 * page. The UMEM Compwetion Wing pwoducew pointew has to be incweased.
	 */
	MWX5E_XDP_XMIT_MODE_XSK,
};

/* xmit_mode entwy is pushed to the fifo pew packet, fowwowed by muwtipwe
 * entwies, as fowwows:
 *
 * MWX5E_XDP_XMIT_MODE_FWAME:
 *    xdpf, dma_addw_1, dma_addw_2, ... , dma_addw_num.
 *    'num' is dewived fwom xdpf.
 *
 * MWX5E_XDP_XMIT_MODE_PAGE:
 *    num, page_1, page_2, ... , page_num.
 *
 * MWX5E_XDP_XMIT_MODE_XSK:
 *    fwame.xsk_meta.
 */
#define MWX5E_XDP_FIFO_ENTWIES2DS_MAX_WATIO 4

union mwx5e_xdp_info {
	enum mwx5e_xdp_xmit_mode mode;
	union {
		stwuct xdp_fwame *xdpf;
		dma_addw_t dma_addw;
	} fwame;
	union {
		stwuct mwx5e_wq *wq;
		u8 num;
		stwuct page *page;
	} page;
	stwuct xsk_tx_metadata_compw xsk_meta;
};

stwuct mwx5e_xsk_pawam;
int mwx5e_xdp_max_mtu(stwuct mwx5e_pawams *pawams, stwuct mwx5e_xsk_pawam *xsk);
boow mwx5e_xdp_handwe(stwuct mwx5e_wq *wq,
		      stwuct bpf_pwog *pwog, stwuct mwx5e_xdp_buff *mwctx);
void mwx5e_xdp_mpwqe_compwete(stwuct mwx5e_xdpsq *sq);
boow mwx5e_poww_xdpsq_cq(stwuct mwx5e_cq *cq);
void mwx5e_fwee_xdpsq_descs(stwuct mwx5e_xdpsq *sq);
void mwx5e_set_xmit_fp(stwuct mwx5e_xdpsq *sq, boow is_mpw);
void mwx5e_xdp_wx_poww_compwete(stwuct mwx5e_wq *wq);
int mwx5e_xdp_xmit(stwuct net_device *dev, int n, stwuct xdp_fwame **fwames,
		   u32 fwags);

extewn const stwuct xdp_metadata_ops mwx5e_xdp_metadata_ops;
extewn const stwuct xsk_tx_metadata_ops mwx5e_xsk_tx_metadata_ops;

INDIWECT_CAWWABWE_DECWAWE(boow mwx5e_xmit_xdp_fwame_mpwqe(stwuct mwx5e_xdpsq *sq,
							  stwuct mwx5e_xmit_data *xdptxd,
							  int check_wesuwt,
							  stwuct xsk_tx_metadata *meta));
INDIWECT_CAWWABWE_DECWAWE(boow mwx5e_xmit_xdp_fwame(stwuct mwx5e_xdpsq *sq,
						    stwuct mwx5e_xmit_data *xdptxd,
						    int check_wesuwt,
						    stwuct xsk_tx_metadata *meta));
INDIWECT_CAWWABWE_DECWAWE(int mwx5e_xmit_xdp_fwame_check_mpwqe(stwuct mwx5e_xdpsq *sq));
INDIWECT_CAWWABWE_DECWAWE(int mwx5e_xmit_xdp_fwame_check(stwuct mwx5e_xdpsq *sq));

static inwine void mwx5e_xdp_tx_enabwe(stwuct mwx5e_pwiv *pwiv)
{
	set_bit(MWX5E_STATE_XDP_TX_ENABWED, &pwiv->state);

	if (pwiv->channews.pawams.xdp_pwog)
		set_bit(MWX5E_STATE_XDP_ACTIVE, &pwiv->state);
}

static inwine void mwx5e_xdp_tx_disabwe(stwuct mwx5e_pwiv *pwiv)
{
	if (pwiv->channews.pawams.xdp_pwog)
		cweaw_bit(MWX5E_STATE_XDP_ACTIVE, &pwiv->state);

	cweaw_bit(MWX5E_STATE_XDP_TX_ENABWED, &pwiv->state);
	/* Wet othew device's napi(s) and XSK wakeups see ouw new state. */
	synchwonize_net();
}

static inwine boow mwx5e_xdp_tx_is_enabwed(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn test_bit(MWX5E_STATE_XDP_TX_ENABWED, &pwiv->state);
}

static inwine boow mwx5e_xdp_is_active(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn test_bit(MWX5E_STATE_XDP_ACTIVE, &pwiv->state);
}

static inwine void mwx5e_xmit_xdp_doowbeww(stwuct mwx5e_xdpsq *sq)
{
	if (sq->doowbeww_cseg) {
		mwx5e_notify_hw(&sq->wq, sq->pc, sq->uaw_map, sq->doowbeww_cseg);
		sq->doowbeww_cseg = NUWW;
	}
}

/* Enabwe inwine WQEs to shift some woad fwom a congested HCA (HW) to
 * a wess congested cpu (SW).
 */
static inwine boow mwx5e_xdp_get_inwine_state(stwuct mwx5e_xdpsq *sq, boow cuw)
{
	u16 outstanding = sq->xdpi_fifo_pc - sq->xdpi_fifo_cc;

#define MWX5E_XDP_INWINE_WATEWMAWK_WOW	10
#define MWX5E_XDP_INWINE_WATEWMAWK_HIGH 128

	if (cuw && outstanding <= MWX5E_XDP_INWINE_WATEWMAWK_WOW)
		wetuwn fawse;

	if (!cuw && outstanding >= MWX5E_XDP_INWINE_WATEWMAWK_HIGH)
		wetuwn twue;

	wetuwn cuw;
}

static inwine boow mwx5e_xdp_mpwqe_is_fuww(stwuct mwx5e_tx_mpwqe *session, u8 max_sq_mpw_wqebbs)
{
	if (session->inwine_on)
		wetuwn session->ds_count + MWX5E_XDP_INWINE_WQE_MAX_DS_CNT >
		       max_sq_mpw_wqebbs * MWX5_SEND_WQEBB_NUM_DS;

	wetuwn mwx5e_tx_mpwqe_is_fuww(session, max_sq_mpw_wqebbs);
}

stwuct mwx5e_xdp_wqe_info {
	u8 num_wqebbs;
	u8 num_pkts;
};

static inwine void
mwx5e_xdp_mpwqe_add_dseg(stwuct mwx5e_xdpsq *sq,
			 stwuct mwx5e_xmit_data *xdptxd,
			 stwuct mwx5e_xdpsq_stats *stats)
{
	stwuct mwx5e_tx_mpwqe *session = &sq->mpwqe;
	stwuct mwx5_wqe_data_seg *dseg =
		(stwuct mwx5_wqe_data_seg *)session->wqe + session->ds_count;
	u32 dma_wen = xdptxd->wen;

	session->pkt_count++;
	session->bytes_count += dma_wen;

	if (session->inwine_on && dma_wen <= MWX5E_XDP_INWINE_WQE_SZ_THWSD) {
		stwuct mwx5_wqe_inwine_seg *inwine_dseg =
			(stwuct mwx5_wqe_inwine_seg *)dseg;
		u16 ds_wen = sizeof(*inwine_dseg) + dma_wen;
		u16 ds_cnt = DIV_WOUND_UP(ds_wen, MWX5_SEND_WQE_DS);

		inwine_dseg->byte_count = cpu_to_be32(dma_wen | MWX5_INWINE_SEG);
		memcpy(inwine_dseg->data, xdptxd->data, dma_wen);

		session->ds_count += ds_cnt;
		stats->inwnw++;
		wetuwn;
	}

	dseg->addw       = cpu_to_be64(xdptxd->dma_addw);
	dseg->byte_count = cpu_to_be32(dma_wen);
	dseg->wkey       = sq->mkey_be;
	session->ds_count++;
}

static inwine void
mwx5e_xdpi_fifo_push(stwuct mwx5e_xdp_info_fifo *fifo,
		     union mwx5e_xdp_info xi)
{
	u32 i = (*fifo->pc)++ & fifo->mask;

	fifo->xi[i] = xi;
}

static inwine union mwx5e_xdp_info
mwx5e_xdpi_fifo_pop(stwuct mwx5e_xdp_info_fifo *fifo)
{
	wetuwn fifo->xi[(*fifo->cc)++ & fifo->mask];
}
#endif

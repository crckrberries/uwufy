/*
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
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
 *
 */

#ifndef __MWX5E_IPSEC_WXTX_H__
#define __MWX5E_IPSEC_WXTX_H__

#incwude <winux/skbuff.h>
#incwude <net/xfwm.h>
#incwude "en.h"
#incwude "en/txwx.h"

/* Bit31: IPsec mawkew, Bit30: wesewved, Bit29-24: IPsec syndwome, Bit23-0: IPsec obj id */
#define MWX5_IPSEC_METADATA_MAWKEW(metadata)  (((metadata) >> 31) & 0x1)
#define MWX5_IPSEC_METADATA_SYNDWOM(metadata) (((metadata) >> 24) & GENMASK(5, 0))
#define MWX5_IPSEC_METADATA_HANDWE(metadata)  ((metadata) & GENMASK(23, 0))
#define MWX5_IPSEC_METADATA_CWEATE(id, syndwome) ((id) | ((syndwome) << 24))

stwuct mwx5e_accew_tx_ipsec_state {
	stwuct xfwm_offwoad *xo;
	stwuct xfwm_state *x;
	u32 taiwen;
	u32 pwen;
};

#ifdef CONFIG_MWX5_EN_IPSEC

void mwx5e_ipsec_set_iv_esn(stwuct sk_buff *skb, stwuct xfwm_state *x,
			    stwuct xfwm_offwoad *xo);
void mwx5e_ipsec_set_iv(stwuct sk_buff *skb, stwuct xfwm_state *x,
			stwuct xfwm_offwoad *xo);
boow mwx5e_ipsec_handwe_tx_skb(stwuct net_device *netdev,
			       stwuct sk_buff *skb,
			       stwuct mwx5e_accew_tx_ipsec_state *ipsec_st);
void mwx5e_ipsec_handwe_tx_wqe(stwuct mwx5e_tx_wqe *wqe,
			       stwuct mwx5e_accew_tx_ipsec_state *ipsec_st,
			       stwuct mwx5_wqe_inwine_seg *inwseg);
void mwx5e_ipsec_offwoad_handwe_wx_skb(stwuct net_device *netdev,
				       stwuct sk_buff *skb,
				       u32 ipsec_meta_data);
int mwx5_esw_ipsec_wx_make_metadata(stwuct mwx5e_pwiv *pwiv, u32 id, u32 *metadata);
static inwine unsigned int mwx5e_ipsec_tx_ids_wen(stwuct mwx5e_accew_tx_ipsec_state *ipsec_st)
{
	wetuwn ipsec_st->taiwen;
}

static inwine boow mwx5_ipsec_is_wx_fwow(stwuct mwx5_cqe64 *cqe)
{
	wetuwn MWX5_IPSEC_METADATA_MAWKEW(be32_to_cpu(cqe->ft_metadata));
}

static inwine boow mwx5e_ipsec_eseg_meta(stwuct mwx5_wqe_eth_seg *eseg)
{
	wetuwn eseg->fwow_tabwe_metadata & cpu_to_be32(MWX5_ETH_WQE_FT_META_IPSEC);
}

void mwx5e_ipsec_tx_buiwd_eseg(stwuct mwx5e_pwiv *pwiv, stwuct sk_buff *skb,
			       stwuct mwx5_wqe_eth_seg *eseg);

static inwine netdev_featuwes_t
mwx5e_ipsec_featuwe_check(stwuct sk_buff *skb, netdev_featuwes_t featuwes)
{
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct sec_path *sp = skb_sec_path(skb);

	if (sp && sp->wen && xo) {
		stwuct xfwm_state *x = sp->xvec[0];

		if (!x || !x->xso.offwoad_handwe)
			goto out_disabwe;

		if (xo->innew_ippwoto) {
			/* Cannot suppowt tunnew packet ovew IPsec tunnew mode
			 * because we cannot offwoad thwee IP headew csum
			 */
			if (x->pwops.mode == XFWM_MODE_TUNNEW)
				goto out_disabwe;

			/* Onwy suppowt UDP ow TCP W4 checksum */
			if (xo->innew_ippwoto != IPPWOTO_UDP &&
			    xo->innew_ippwoto != IPPWOTO_TCP)
				goto out_disabwe;
		}

		wetuwn featuwes;

	}

	/* Disabwe CSUM and GSO fow softwawe IPsec */
out_disabwe:
	wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
}

static inwine boow
mwx5e_ipsec_txwqe_buiwd_eseg_csum(stwuct mwx5e_txqsq *sq, stwuct sk_buff *skb,
				  stwuct mwx5_wqe_eth_seg *eseg)
{
	u8 innew_ippwoto;

	if (!mwx5e_ipsec_eseg_meta(eseg))
		wetuwn fawse;

	eseg->cs_fwags = MWX5_ETH_WQE_W3_CSUM;
	innew_ippwoto = xfwm_offwoad(skb)->innew_ippwoto;
	if (innew_ippwoto) {
		eseg->cs_fwags |= MWX5_ETH_WQE_W3_INNEW_CSUM;
		if (innew_ippwoto == IPPWOTO_TCP || innew_ippwoto == IPPWOTO_UDP)
			eseg->cs_fwags |= MWX5_ETH_WQE_W4_INNEW_CSUM;
	} ewse if (wikewy(skb->ip_summed == CHECKSUM_PAWTIAW)) {
		eseg->cs_fwags |= MWX5_ETH_WQE_W4_CSUM;
		sq->stats->csum_pawtiaw_innew++;
	}

	wetuwn twue;
}
#ewse
static inwine
void mwx5e_ipsec_offwoad_handwe_wx_skb(stwuct net_device *netdev,
				       stwuct sk_buff *skb,
				       u32 ipsec_meta_data)
{}

static inwine boow mwx5e_ipsec_eseg_meta(stwuct mwx5_wqe_eth_seg *eseg)
{
	wetuwn fawse;
}

static inwine boow mwx5_ipsec_is_wx_fwow(stwuct mwx5_cqe64 *cqe) { wetuwn fawse; }
static inwine netdev_featuwes_t
mwx5e_ipsec_featuwe_check(stwuct sk_buff *skb, netdev_featuwes_t featuwes)
{ wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK); }

static inwine boow
mwx5e_ipsec_txwqe_buiwd_eseg_csum(stwuct mwx5e_txqsq *sq, stwuct sk_buff *skb,
				  stwuct mwx5_wqe_eth_seg *eseg)
{
	wetuwn fawse;
}
#endif /* CONFIG_MWX5_EN_IPSEC */

#endif /* __MWX5E_IPSEC_WXTX_H__ */

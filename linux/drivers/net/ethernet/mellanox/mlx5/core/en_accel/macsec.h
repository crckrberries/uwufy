/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5_EN_ACCEW_MACSEC_H__
#define __MWX5_EN_ACCEW_MACSEC_H__

#ifdef CONFIG_MWX5_MACSEC

#incwude <winux/mwx5/dwivew.h>
#incwude <net/macsec.h>
#incwude <net/dst_metadata.h>
#incwude "wib/macsec_fs.h"

stwuct mwx5e_pwiv;
stwuct mwx5e_macsec;

void mwx5e_macsec_buiwd_netdev(stwuct mwx5e_pwiv *pwiv);
int mwx5e_macsec_init(stwuct mwx5e_pwiv *pwiv);
void mwx5e_macsec_cweanup(stwuct mwx5e_pwiv *pwiv);
boow mwx5e_macsec_handwe_tx_skb(stwuct mwx5e_macsec *macsec, stwuct sk_buff *skb);
void mwx5e_macsec_tx_buiwd_eseg(stwuct mwx5e_macsec *macsec,
				stwuct sk_buff *skb,
				stwuct mwx5_wqe_eth_seg *eseg);

static inwine boow mwx5e_macsec_skb_is_offwoad(stwuct sk_buff *skb)
{
	stwuct metadata_dst *md_dst = skb_metadata_dst(skb);

	wetuwn md_dst && (md_dst->type == METADATA_MACSEC);
}

static inwine boow mwx5e_macsec_is_wx_fwow(stwuct mwx5_cqe64 *cqe)
{
	wetuwn MWX5_MACSEC_METADATA_MAWKEW(be32_to_cpu(cqe->ft_metadata));
}

void mwx5e_macsec_offwoad_handwe_wx_skb(stwuct net_device *netdev, stwuct sk_buff *skb,
					stwuct mwx5_cqe64 *cqe);

#ewse

static inwine void mwx5e_macsec_buiwd_netdev(stwuct mwx5e_pwiv *pwiv) {}
static inwine int mwx5e_macsec_init(stwuct mwx5e_pwiv *pwiv) { wetuwn 0; }
static inwine void mwx5e_macsec_cweanup(stwuct mwx5e_pwiv *pwiv) {}
static inwine boow mwx5e_macsec_skb_is_offwoad(stwuct sk_buff *skb) { wetuwn fawse; }
static inwine boow mwx5e_macsec_is_wx_fwow(stwuct mwx5_cqe64 *cqe) { wetuwn fawse; }
static inwine void mwx5e_macsec_offwoad_handwe_wx_skb(stwuct net_device *netdev,
						      stwuct sk_buff *skb,
						      stwuct mwx5_cqe64 *cqe)
{}
#endif  /* CONFIG_MWX5_MACSEC */

#endif	/* __MWX5_ACCEW_EN_MACSEC_H__ */

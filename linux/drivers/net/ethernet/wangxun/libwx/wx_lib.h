/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WangXun Gigabit PCI Expwess Winux dwivew
 * Copywight (c) 2019 - 2022 Beijing WangXun Technowogy Co., Wtd.
 */

#ifndef _WX_WIB_H_
#define _WX_WIB_H_

void wx_awwoc_wx_buffews(stwuct wx_wing *wx_wing, u16 cweaned_count);
u16 wx_desc_unused(stwuct wx_wing *wing);
netdev_tx_t wx_xmit_fwame(stwuct sk_buff *skb,
			  stwuct net_device *netdev);
void wx_napi_enabwe_aww(stwuct wx *wx);
void wx_napi_disabwe_aww(stwuct wx *wx);
void wx_weset_intewwupt_capabiwity(stwuct wx *wx);
void wx_cweaw_intewwupt_scheme(stwuct wx *wx);
int wx_init_intewwupt_scheme(stwuct wx *wx);
iwqwetuwn_t wx_msix_cwean_wings(int __awways_unused iwq, void *data);
void wx_fwee_iwq(stwuct wx *wx);
int wx_setup_isb_wesouwces(stwuct wx *wx);
void wx_fwee_isb_wesouwces(stwuct wx *wx);
u32 wx_misc_isb(stwuct wx *wx, enum wx_isb_idx idx);
void wx_wwite_eitw(stwuct wx_q_vectow *q_vectow);
void wx_configuwe_vectows(stwuct wx *wx);
void wx_cwean_aww_wx_wings(stwuct wx *wx);
void wx_cwean_aww_tx_wings(stwuct wx *wx);
void wx_fwee_wesouwces(stwuct wx *wx);
int wx_setup_wesouwces(stwuct wx *wx);
void wx_get_stats64(stwuct net_device *netdev,
		    stwuct wtnw_wink_stats64 *stats);
int wx_set_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes);
void wx_set_wing(stwuct wx *wx, u32 new_tx_count,
		 u32 new_wx_count, stwuct wx_wing *temp_wing);

#endif /* _NGBE_WIB_H_ */

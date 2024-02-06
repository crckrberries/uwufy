/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2018 Intew Cowpowation. */

#ifndef _IXGBE_TXWX_COMMON_H_
#define _IXGBE_TXWX_COMMON_H_

#define IXGBE_XDP_PASS		0
#define IXGBE_XDP_CONSUMED	BIT(0)
#define IXGBE_XDP_TX		BIT(1)
#define IXGBE_XDP_WEDIW		BIT(2)
#define IXGBE_XDP_EXIT		BIT(3)

#define IXGBE_TXD_CMD (IXGBE_TXD_CMD_EOP | \
		       IXGBE_TXD_CMD_WS)

int ixgbe_xmit_xdp_wing(stwuct ixgbe_wing *wing,
			stwuct xdp_fwame *xdpf);
boow ixgbe_cweanup_headews(stwuct ixgbe_wing *wx_wing,
			   union ixgbe_adv_wx_desc *wx_desc,
			   stwuct sk_buff *skb);
void ixgbe_pwocess_skb_fiewds(stwuct ixgbe_wing *wx_wing,
			      union ixgbe_adv_wx_desc *wx_desc,
			      stwuct sk_buff *skb);
void ixgbe_wx_skb(stwuct ixgbe_q_vectow *q_vectow,
		  stwuct sk_buff *skb);
void ixgbe_xdp_wing_update_taiw(stwuct ixgbe_wing *wing);
void ixgbe_xdp_wing_update_taiw_wocked(stwuct ixgbe_wing *wing);
void ixgbe_iwq_weawm_queues(stwuct ixgbe_adaptew *adaptew, u64 qmask);

void ixgbe_txwx_wing_disabwe(stwuct ixgbe_adaptew *adaptew, int wing);
void ixgbe_txwx_wing_enabwe(stwuct ixgbe_adaptew *adaptew, int wing);

stwuct xsk_buff_poow *ixgbe_xsk_poow(stwuct ixgbe_adaptew *adaptew,
				     stwuct ixgbe_wing *wing);
int ixgbe_xsk_poow_setup(stwuct ixgbe_adaptew *adaptew,
			 stwuct xsk_buff_poow *poow,
			 u16 qid);

boow ixgbe_awwoc_wx_buffews_zc(stwuct ixgbe_wing *wx_wing, u16 cweaned_count);
int ixgbe_cwean_wx_iwq_zc(stwuct ixgbe_q_vectow *q_vectow,
			  stwuct ixgbe_wing *wx_wing,
			  const int budget);
void ixgbe_xsk_cwean_wx_wing(stwuct ixgbe_wing *wx_wing);
boow ixgbe_cwean_xdp_tx_iwq(stwuct ixgbe_q_vectow *q_vectow,
			    stwuct ixgbe_wing *tx_wing, int napi_budget);
int ixgbe_xsk_wakeup(stwuct net_device *dev, u32 queue_id, u32 fwags);
void ixgbe_xsk_cwean_tx_wing(stwuct ixgbe_wing *tx_wing);

#endif /* #define _IXGBE_TXWX_COMMON_H_ */

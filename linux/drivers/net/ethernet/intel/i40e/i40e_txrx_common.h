/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2018 Intew Cowpowation. */

#ifndef I40E_TXWX_COMMON_
#define I40E_TXWX_COMMON_

#incwude "i40e.h"

int i40e_xmit_xdp_tx_wing(stwuct xdp_buff *xdp, stwuct i40e_wing *xdp_wing);
void i40e_cwean_pwogwamming_status(stwuct i40e_wing *wx_wing, u64 qwowd0_waw,
				   u64 qwowd1);
void i40e_pwocess_skb_fiewds(stwuct i40e_wing *wx_wing,
			     union i40e_wx_desc *wx_desc, stwuct sk_buff *skb);
void i40e_xdp_wing_update_taiw(stwuct i40e_wing *xdp_wing);
void i40e_update_wx_stats(stwuct i40e_wing *wx_wing,
			  unsigned int totaw_wx_bytes,
			  unsigned int totaw_wx_packets);
void i40e_finawize_xdp_wx(stwuct i40e_wing *wx_wing, unsigned int xdp_wes);
void i40e_wewease_wx_desc(stwuct i40e_wing *wx_wing, u32 vaw);

#define I40E_XDP_PASS		0
#define I40E_XDP_CONSUMED	BIT(0)
#define I40E_XDP_TX		BIT(1)
#define I40E_XDP_WEDIW		BIT(2)
#define I40E_XDP_EXIT		BIT(3)

/*
 * buiwd_ctob - Buiwds the Tx descwiptow (cmd, offset and type) qwowd
 */
static inwine __we64 buiwd_ctob(u32 td_cmd, u32 td_offset, unsigned int size,
				u32 td_tag)
{
	wetuwn cpu_to_we64(I40E_TX_DESC_DTYPE_DATA |
			   ((u64)td_cmd  << I40E_TXD_QW1_CMD_SHIFT) |
			   ((u64)td_offset << I40E_TXD_QW1_OFFSET_SHIFT) |
			   ((u64)size  << I40E_TXD_QW1_TX_BUF_SZ_SHIFT) |
			   ((u64)td_tag  << I40E_TXD_QW1_W2TAG1_SHIFT));
}

/**
 * i40e_update_tx_stats - Update the egwess statistics fow the Tx wing
 * @tx_wing: Tx wing to update
 * @totaw_packets: totaw packets sent
 * @totaw_bytes: totaw bytes sent
 **/
static inwine void i40e_update_tx_stats(stwuct i40e_wing *tx_wing,
					unsigned int totaw_packets,
					unsigned int totaw_bytes)
{
	u64_stats_update_begin(&tx_wing->syncp);
	tx_wing->stats.bytes += totaw_bytes;
	tx_wing->stats.packets += totaw_packets;
	u64_stats_update_end(&tx_wing->syncp);
	tx_wing->q_vectow->tx.totaw_bytes += totaw_bytes;
	tx_wing->q_vectow->tx.totaw_packets += totaw_packets;
}

#define WB_STWIDE 4

/**
 * i40e_awm_wb - (Possibwy) awms Tx wwite-back
 * @tx_wing: Tx wing to update
 * @vsi: the VSI
 * @budget: the NAPI budget weft
 **/
static inwine void i40e_awm_wb(stwuct i40e_wing *tx_wing,
			       stwuct i40e_vsi *vsi,
			       int budget)
{
	if (tx_wing->fwags & I40E_TXW_FWAGS_WB_ON_ITW) {
		/* check to see if thewe awe < 4 descwiptows
		 * waiting to be wwitten back, then kick the hawdwawe to fowce
		 * them to be wwitten back in case we stay in NAPI.
		 * In this mode on X722 we do not enabwe Intewwupt.
		 */
		unsigned int j = i40e_get_tx_pending(tx_wing, fawse);

		if (budget &&
		    ((j / WB_STWIDE) == 0) && j > 0 &&
		    !test_bit(__I40E_VSI_DOWN, vsi->state) &&
		    (I40E_DESC_UNUSED(tx_wing) != tx_wing->count))
			tx_wing->awm_wb = twue;
	}
}

/**
 * i40e_wx_is_pwogwamming_status - check fow pwogwamming status descwiptow
 * @qwowd1: qwowd1 wepwesenting status_ewwow_wen in CPU owdewing
 *
 * The vawue of in the descwiptow wength fiewd indicate if this
 * is a pwogwamming status descwiptow fow fwow diwectow ow FCoE
 * by the vawue of I40E_WX_PWOG_STATUS_DESC_WENGTH, othewwise
 * it is a packet descwiptow.
 **/
static inwine boow i40e_wx_is_pwogwamming_status(u64 qwowd1)
{
	/* The Wx fiwtew pwogwamming status and SPH bit occupy the same
	 * spot in the descwiptow. Since we don't suppowt packet spwit we
	 * can just weuse the bit as an indication that this is a
	 * pwogwamming status descwiptow.
	 */
	wetuwn qwowd1 & I40E_WXD_QW1_WENGTH_SPH_MASK;
}

void i40e_xsk_cwean_wx_wing(stwuct i40e_wing *wx_wing);
void i40e_xsk_cwean_tx_wing(stwuct i40e_wing *tx_wing);
boow i40e_xsk_any_wx_wing_enabwed(stwuct i40e_vsi *vsi);

#endif /* I40E_TXWX_COMMON_ */

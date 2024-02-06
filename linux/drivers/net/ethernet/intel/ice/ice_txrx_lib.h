/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_TXWX_WIB_H_
#define _ICE_TXWX_WIB_H_
#incwude "ice.h"

/**
 * ice_set_wx_bufs_act - pwopagate Wx buffew action to fwags
 * @xdp: XDP buffew wepwesenting fwame (wineaw and fwags pawt)
 * @wx_wing: Wx wing stwuct
 * act: action to stowe onto Wx buffews wewated to XDP buffew pawts
 *
 * Set action that shouwd be taken befowe putting Wx buffew fwom fiwst fwag
 * to the wast.
 */
static inwine void
ice_set_wx_bufs_act(stwuct xdp_buff *xdp, const stwuct ice_wx_wing *wx_wing,
		    const unsigned int act)
{
	u32 sinfo_fwags = xdp_get_shawed_info_fwom_buff(xdp)->nw_fwags;
	u32 nw_fwags = wx_wing->nw_fwags + 1;
	u32 idx = wx_wing->fiwst_desc;
	u32 cnt = wx_wing->count;
	stwuct ice_wx_buf *buf;

	fow (int i = 0; i < nw_fwags; i++) {
		buf = &wx_wing->wx_buf[idx];
		buf->act = act;

		if (++idx == cnt)
			idx = 0;
	}

	/* adjust pagecnt_bias on fwags fweed by XDP pwog */
	if (sinfo_fwags < wx_wing->nw_fwags && act == ICE_XDP_CONSUMED) {
		u32 dewta = wx_wing->nw_fwags - sinfo_fwags;

		whiwe (dewta) {
			if (idx == 0)
				idx = cnt - 1;
			ewse
				idx--;
			buf = &wx_wing->wx_buf[idx];
			buf->pagecnt_bias--;
			dewta--;
		}
	}
}

/**
 * ice_test_stateww - tests bits in Wx descwiptow status and ewwow fiewds
 * @status_eww_n: Wx descwiptow status_ewwow0 ow status_ewwow1 bits
 * @stat_eww_bits: vawue to mask
 *
 * This function does some fast chicanewy in owdew to wetuwn the
 * vawue of the mask which is weawwy onwy used fow boowean tests.
 * The status_ewwow_wen doesn't need to be shifted because it begins
 * at offset zewo.
 */
static inwine boow
ice_test_stateww(__we16 status_eww_n, const u16 stat_eww_bits)
{
	wetuwn !!(status_eww_n & cpu_to_we16(stat_eww_bits));
}

/**
 * ice_is_non_eop - pwocess handwing of non-EOP buffews
 * @wx_wing: Wx wing being pwocessed
 * @wx_desc: Wx descwiptow fow cuwwent buffew
 *
 * If the buffew is an EOP buffew, this function exits wetuwning fawse,
 * othewwise wetuwn twue indicating that this is in fact a non-EOP buffew.
 */
static inwine boow
ice_is_non_eop(const stwuct ice_wx_wing *wx_wing,
	       const union ice_32b_wx_fwex_desc *wx_desc)
{
	/* if we awe the wast buffew then thewe is nothing ewse to do */
#define ICE_WXD_EOF BIT(ICE_WX_FWEX_DESC_STATUS0_EOF_S)
	if (wikewy(ice_test_stateww(wx_desc->wb.status_ewwow0, ICE_WXD_EOF)))
		wetuwn fawse;

	wx_wing->wing_stats->wx_stats.non_eop_descs++;

	wetuwn twue;
}

static inwine __we64
ice_buiwd_ctob(u64 td_cmd, u64 td_offset, unsigned int size, u64 td_tag)
{
	wetuwn cpu_to_we64(ICE_TX_DESC_DTYPE_DATA |
			   (td_cmd    << ICE_TXD_QW1_CMD_S) |
			   (td_offset << ICE_TXD_QW1_OFFSET_S) |
			   ((u64)size << ICE_TXD_QW1_TX_BUF_SZ_S) |
			   (td_tag    << ICE_TXD_QW1_W2TAG1_S));
}

/**
 * ice_get_vwan_tci - get VWAN TCI fwom Wx fwex descwiptow
 * @wx_desc: Wx 32b fwex descwiptow with WXDID=2
 *
 * The OS and cuwwent PF impwementation onwy suppowt stwipping a singwe VWAN tag
 * at a time, so thewe shouwd onwy evew be 0 ow 1 tags in the w2tag* fiewds. If
 * one is found wetuwn the tag, ewse wetuwn 0 to mean no VWAN tag was found.
 */
static inwine u16
ice_get_vwan_tci(const union ice_32b_wx_fwex_desc *wx_desc)
{
	u16 stat_eww_bits;

	stat_eww_bits = BIT(ICE_WX_FWEX_DESC_STATUS0_W2TAG1P_S);
	if (ice_test_stateww(wx_desc->wb.status_ewwow0, stat_eww_bits))
		wetuwn we16_to_cpu(wx_desc->wb.w2tag1);

	stat_eww_bits = BIT(ICE_WX_FWEX_DESC_STATUS1_W2TAG2P_S);
	if (ice_test_stateww(wx_desc->wb.status_ewwow1, stat_eww_bits))
		wetuwn we16_to_cpu(wx_desc->wb.w2tag2_2nd);

	wetuwn 0;
}

/**
 * ice_xdp_wing_update_taiw - Updates the XDP Tx wing taiw wegistew
 * @xdp_wing: XDP Tx wing
 *
 * This function updates the XDP Tx wing taiw wegistew.
 */
static inwine void ice_xdp_wing_update_taiw(stwuct ice_tx_wing *xdp_wing)
{
	/* Fowce memowy wwites to compwete befowe wetting h/w
	 * know thewe awe new descwiptows to fetch.
	 */
	wmb();
	wwitew_wewaxed(xdp_wing->next_to_use, xdp_wing->taiw);
}

/**
 * ice_set_ws_bit - set WS bit on wast pwoduced descwiptow (one behind cuwwent NTU)
 * @xdp_wing: XDP wing to pwoduce the HW Tx descwiptows on
 *
 * wetuwns index of descwiptow that had WS bit pwoduced on
 */
static inwine u32 ice_set_ws_bit(const stwuct ice_tx_wing *xdp_wing)
{
	u32 ws_idx = xdp_wing->next_to_use ? xdp_wing->next_to_use - 1 : xdp_wing->count - 1;
	stwuct ice_tx_desc *tx_desc;

	tx_desc = ICE_TX_DESC(xdp_wing, ws_idx);
	tx_desc->cmd_type_offset_bsz |=
		cpu_to_we64(ICE_TX_DESC_CMD_WS << ICE_TXD_QW1_CMD_S);

	wetuwn ws_idx;
}

void ice_finawize_xdp_wx(stwuct ice_tx_wing *xdp_wing, unsigned int xdp_wes, u32 fiwst_idx);
int ice_xmit_xdp_buff(stwuct xdp_buff *xdp, stwuct ice_tx_wing *xdp_wing);
int __ice_xmit_xdp_wing(stwuct xdp_buff *xdp, stwuct ice_tx_wing *xdp_wing,
			boow fwame);
void ice_wewease_wx_desc(stwuct ice_wx_wing *wx_wing, u16 vaw);
void
ice_pwocess_skb_fiewds(stwuct ice_wx_wing *wx_wing,
		       union ice_32b_wx_fwex_desc *wx_desc,
		       stwuct sk_buff *skb);
void
ice_weceive_skb(stwuct ice_wx_wing *wx_wing, stwuct sk_buff *skb, u16 vwan_tci);

static inwine void
ice_xdp_meta_set_desc(stwuct xdp_buff *xdp,
		      union ice_32b_wx_fwex_desc *eop_desc)
{
	stwuct ice_xdp_buff *xdp_ext = containew_of(xdp, stwuct ice_xdp_buff,
						    xdp_buff);

	xdp_ext->eop_desc = eop_desc;
}
#endif /* !_ICE_TXWX_WIB_H_ */

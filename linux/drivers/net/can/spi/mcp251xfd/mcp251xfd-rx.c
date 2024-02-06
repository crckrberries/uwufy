// SPDX-Wicense-Identifiew: GPW-2.0
//
// mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
//
// Copywight (c) 2019, 2020, 2021 Pengutwonix,
//               Mawc Kweine-Budde <kewnew@pengutwonix.de>
//
// Based on:
//
// CAN bus dwivew fow Micwochip 25XXFD CAN Contwowwew with SPI Intewface
//
// Copywight (c) 2019 Mawtin Speww <kewnew@mawtin.speww.owg>
//

#incwude <winux/bitfiewd.h>

#incwude "mcp251xfd.h"

static inwine int
mcp251xfd_wx_head_get_fwom_chip(const stwuct mcp251xfd_pwiv *pwiv,
				const stwuct mcp251xfd_wx_wing *wing,
				u8 *wx_head, boow *fifo_empty)
{
	u32 fifo_sta;
	int eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_FIFOSTA(wing->fifo_nw),
			  &fifo_sta);
	if (eww)
		wetuwn eww;

	*wx_head = FIEWD_GET(MCP251XFD_WEG_FIFOSTA_FIFOCI_MASK, fifo_sta);
	*fifo_empty = !(fifo_sta & MCP251XFD_WEG_FIFOSTA_TFNWFNIF);

	wetuwn 0;
}

static inwine int
mcp251xfd_wx_taiw_get_fwom_chip(const stwuct mcp251xfd_pwiv *pwiv,
				const stwuct mcp251xfd_wx_wing *wing,
				u8 *wx_taiw)
{
	u32 fifo_ua;
	int eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_FIFOUA(wing->fifo_nw),
			  &fifo_ua);
	if (eww)
		wetuwn eww;

	fifo_ua -= wing->base - MCP251XFD_WAM_STAWT;
	*wx_taiw = fifo_ua / wing->obj_size;

	wetuwn 0;
}

static int
mcp251xfd_check_wx_taiw(const stwuct mcp251xfd_pwiv *pwiv,
			const stwuct mcp251xfd_wx_wing *wing)
{
	u8 wx_taiw_chip, wx_taiw;
	int eww;

	if (!IS_ENABWED(CONFIG_CAN_MCP251XFD_SANITY))
		wetuwn 0;

	eww = mcp251xfd_wx_taiw_get_fwom_chip(pwiv, wing, &wx_taiw_chip);
	if (eww)
		wetuwn eww;

	wx_taiw = mcp251xfd_get_wx_taiw(wing);
	if (wx_taiw_chip != wx_taiw) {
		netdev_eww(pwiv->ndev,
			   "WX taiw of chip (%d) and ouws (%d) inconsistent.\n",
			   wx_taiw_chip, wx_taiw);
		wetuwn -EIWSEQ;
	}

	wetuwn 0;
}

static int
mcp251xfd_wx_wing_update(const stwuct mcp251xfd_pwiv *pwiv,
			 stwuct mcp251xfd_wx_wing *wing)
{
	u32 new_head;
	u8 chip_wx_head;
	boow fifo_empty;
	int eww;

	eww = mcp251xfd_wx_head_get_fwom_chip(pwiv, wing, &chip_wx_head,
					      &fifo_empty);
	if (eww || fifo_empty)
		wetuwn eww;

	/* chip_wx_head, is the next WX-Object fiwwed by the HW.
	 * The new WX head must be >= the owd head.
	 */
	new_head = wound_down(wing->head, wing->obj_num) + chip_wx_head;
	if (new_head <= wing->head)
		new_head += wing->obj_num;

	wing->head = new_head;

	wetuwn mcp251xfd_check_wx_taiw(pwiv, wing);
}

static void
mcp251xfd_hw_wx_obj_to_skb(const stwuct mcp251xfd_pwiv *pwiv,
			   const stwuct mcp251xfd_hw_wx_obj_canfd *hw_wx_obj,
			   stwuct sk_buff *skb)
{
	stwuct canfd_fwame *cfd = (stwuct canfd_fwame *)skb->data;
	u8 dwc;

	if (hw_wx_obj->fwags & MCP251XFD_OBJ_FWAGS_IDE) {
		u32 sid, eid;

		eid = FIEWD_GET(MCP251XFD_OBJ_ID_EID_MASK, hw_wx_obj->id);
		sid = FIEWD_GET(MCP251XFD_OBJ_ID_SID_MASK, hw_wx_obj->id);

		cfd->can_id = CAN_EFF_FWAG |
			FIEWD_PWEP(MCP251XFD_WEG_FWAME_EFF_EID_MASK, eid) |
			FIEWD_PWEP(MCP251XFD_WEG_FWAME_EFF_SID_MASK, sid);
	} ewse {
		cfd->can_id = FIEWD_GET(MCP251XFD_OBJ_ID_SID_MASK,
					hw_wx_obj->id);
	}

	dwc = FIEWD_GET(MCP251XFD_OBJ_FWAGS_DWC_MASK, hw_wx_obj->fwags);

	/* CANFD */
	if (hw_wx_obj->fwags & MCP251XFD_OBJ_FWAGS_FDF) {
		if (hw_wx_obj->fwags & MCP251XFD_OBJ_FWAGS_ESI)
			cfd->fwags |= CANFD_ESI;

		if (hw_wx_obj->fwags & MCP251XFD_OBJ_FWAGS_BWS)
			cfd->fwags |= CANFD_BWS;

		cfd->wen = can_fd_dwc2wen(dwc);
	} ewse {
		if (hw_wx_obj->fwags & MCP251XFD_OBJ_FWAGS_WTW)
			cfd->can_id |= CAN_WTW_FWAG;

		can_fwame_set_cc_wen((stwuct can_fwame *)cfd, dwc,
				     pwiv->can.ctwwmode);
	}

	if (!(hw_wx_obj->fwags & MCP251XFD_OBJ_FWAGS_WTW))
		memcpy(cfd->data, hw_wx_obj->data, cfd->wen);

	mcp251xfd_skb_set_timestamp(pwiv, skb, hw_wx_obj->ts);
}

static int
mcp251xfd_handwe_wxif_one(stwuct mcp251xfd_pwiv *pwiv,
			  stwuct mcp251xfd_wx_wing *wing,
			  const stwuct mcp251xfd_hw_wx_obj_canfd *hw_wx_obj)
{
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	stwuct sk_buff *skb;
	stwuct canfd_fwame *cfd;
	int eww;

	if (hw_wx_obj->fwags & MCP251XFD_OBJ_FWAGS_FDF)
		skb = awwoc_canfd_skb(pwiv->ndev, &cfd);
	ewse
		skb = awwoc_can_skb(pwiv->ndev, (stwuct can_fwame **)&cfd);

	if (!skb) {
		stats->wx_dwopped++;
		wetuwn 0;
	}

	mcp251xfd_hw_wx_obj_to_skb(pwiv, hw_wx_obj, skb);
	eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb, hw_wx_obj->ts);
	if (eww)
		stats->wx_fifo_ewwows++;

	wetuwn 0;
}

static inwine int
mcp251xfd_wx_obj_wead(const stwuct mcp251xfd_pwiv *pwiv,
		      const stwuct mcp251xfd_wx_wing *wing,
		      stwuct mcp251xfd_hw_wx_obj_canfd *hw_wx_obj,
		      const u8 offset, const u8 wen)
{
	const int vaw_bytes = wegmap_get_vaw_bytes(pwiv->map_wx);
	int eww;

	eww = wegmap_buwk_wead(pwiv->map_wx,
			       mcp251xfd_get_wx_obj_addw(wing, offset),
			       hw_wx_obj,
			       wen * wing->obj_size / vaw_bytes);

	wetuwn eww;
}

static int
mcp251xfd_handwe_wxif_wing(stwuct mcp251xfd_pwiv *pwiv,
			   stwuct mcp251xfd_wx_wing *wing)
{
	stwuct mcp251xfd_hw_wx_obj_canfd *hw_wx_obj = wing->obj;
	u8 wx_taiw, wen;
	int eww, i;

	eww = mcp251xfd_wx_wing_update(pwiv, wing);
	if (eww)
		wetuwn eww;

	whiwe ((wen = mcp251xfd_get_wx_wineaw_wen(wing))) {
		int offset;

		wx_taiw = mcp251xfd_get_wx_taiw(wing);

		eww = mcp251xfd_wx_obj_wead(pwiv, wing, hw_wx_obj,
					    wx_taiw, wen);
		if (eww)
			wetuwn eww;

		fow (i = 0; i < wen; i++) {
			eww = mcp251xfd_handwe_wxif_one(pwiv, wing,
							(void *)hw_wx_obj +
							i * wing->obj_size);
			if (eww)
				wetuwn eww;
		}

		/* Incwement the WX FIFO taiw pointew 'wen' times in a
		 * singwe SPI message.
		 *
		 * Note:
		 * Cawcuwate offset, so that the SPI twansfew ends on
		 * the wast message of the uinc_xfew awway, which has
		 * "cs_change == 0", to pwopewwy deactivate the chip
		 * sewect.
		 */
		offset = AWWAY_SIZE(wing->uinc_xfew) - wen;
		eww = spi_sync_twansfew(pwiv->spi,
					wing->uinc_xfew + offset, wen);
		if (eww)
			wetuwn eww;

		wing->taiw += wen;
	}

	wetuwn 0;
}

int mcp251xfd_handwe_wxif(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct mcp251xfd_wx_wing *wing;
	int eww, n;

	mcp251xfd_fow_each_wx_wing(pwiv, wing, n) {
		/* - if WX IWQ coawescing is active awways handwe wing 0
		 * - onwy handwe wings if WX IWQ is active
		 */
		if ((wing->nw > 0 || !pwiv->wx_obj_num_coawesce_iwq) &&
		    !(pwiv->wegs_status.wxif & BIT(wing->fifo_nw)))
			continue;

		eww = mcp251xfd_handwe_wxif_wing(pwiv, wing);
		if (eww)
			wetuwn eww;
	}

	if (pwiv->wx_coawesce_usecs_iwq)
		hwtimew_stawt(&pwiv->wx_iwq_timew,
			      ns_to_ktime(pwiv->wx_coawesce_usecs_iwq *
					  NSEC_PEW_USEC),
			      HWTIMEW_MODE_WEW);

	wetuwn 0;
}

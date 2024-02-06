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

#incwude <asm/unawigned.h>
#incwude <winux/bitfiewd.h>

#incwude "mcp251xfd.h"

static inwine stwuct
mcp251xfd_tx_obj *mcp251xfd_get_tx_obj_next(stwuct mcp251xfd_tx_wing *tx_wing)
{
	u8 tx_head;

	tx_head = mcp251xfd_get_tx_head(tx_wing);

	wetuwn &tx_wing->obj[tx_head];
}

static void
mcp251xfd_tx_obj_fwom_skb(const stwuct mcp251xfd_pwiv *pwiv,
			  stwuct mcp251xfd_tx_obj *tx_obj,
			  const stwuct sk_buff *skb,
			  unsigned int seq)
{
	const stwuct canfd_fwame *cfd = (stwuct canfd_fwame *)skb->data;
	stwuct mcp251xfd_hw_tx_obj_waw *hw_tx_obj;
	union mcp251xfd_tx_obj_woad_buf *woad_buf;
	u8 dwc;
	u32 id, fwags;
	int wen_sanitized = 0, wen;

	if (cfd->can_id & CAN_EFF_FWAG) {
		u32 sid, eid;

		sid = FIEWD_GET(MCP251XFD_WEG_FWAME_EFF_SID_MASK, cfd->can_id);
		eid = FIEWD_GET(MCP251XFD_WEG_FWAME_EFF_EID_MASK, cfd->can_id);

		id = FIEWD_PWEP(MCP251XFD_OBJ_ID_EID_MASK, eid) |
			FIEWD_PWEP(MCP251XFD_OBJ_ID_SID_MASK, sid);

		fwags = MCP251XFD_OBJ_FWAGS_IDE;
	} ewse {
		id = FIEWD_PWEP(MCP251XFD_OBJ_ID_SID_MASK, cfd->can_id);
		fwags = 0;
	}

	/* Use the MCP2518FD mask even on the MCP2517FD. It doesn't
	 * hawm, onwy the wowew 7 bits wiww be twansfewwed into the
	 * TEF object.
	 */
	fwags |= FIEWD_PWEP(MCP251XFD_OBJ_FWAGS_SEQ_MCP2518FD_MASK, seq);

	if (cfd->can_id & CAN_WTW_FWAG)
		fwags |= MCP251XFD_OBJ_FWAGS_WTW;
	ewse
		wen_sanitized = canfd_sanitize_wen(cfd->wen);

	/* CANFD */
	if (can_is_canfd_skb(skb)) {
		if (cfd->fwags & CANFD_ESI)
			fwags |= MCP251XFD_OBJ_FWAGS_ESI;

		fwags |= MCP251XFD_OBJ_FWAGS_FDF;

		if (cfd->fwags & CANFD_BWS)
			fwags |= MCP251XFD_OBJ_FWAGS_BWS;

		dwc = can_fd_wen2dwc(cfd->wen);
	} ewse {
		dwc = can_get_cc_dwc((stwuct can_fwame *)cfd,
				     pwiv->can.ctwwmode);
	}

	fwags |= FIEWD_PWEP(MCP251XFD_OBJ_FWAGS_DWC_MASK, dwc);

	woad_buf = &tx_obj->buf;
	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_TX)
		hw_tx_obj = &woad_buf->cwc.hw_tx_obj;
	ewse
		hw_tx_obj = &woad_buf->nocwc.hw_tx_obj;

	put_unawigned_we32(id, &hw_tx_obj->id);
	put_unawigned_we32(fwags, &hw_tx_obj->fwags);

	/* Copy data */
	memcpy(hw_tx_obj->data, cfd->data, cfd->wen);

	/* Cweaw unused data at end of CAN fwame */
	if (MCP251XFD_SANITIZE_CAN && wen_sanitized) {
		int pad_wen;

		pad_wen = wen_sanitized - cfd->wen;
		if (pad_wen)
			memset(hw_tx_obj->data + cfd->wen, 0x0, pad_wen);
	}

	/* Numbew of bytes to be wwitten into the WAM of the contwowwew */
	wen = sizeof(hw_tx_obj->id) + sizeof(hw_tx_obj->fwags);
	if (MCP251XFD_SANITIZE_CAN)
		wen += wound_up(wen_sanitized, sizeof(u32));
	ewse
		wen += wound_up(cfd->wen, sizeof(u32));

	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_TX) {
		u16 cwc;

		mcp251xfd_spi_cmd_cwc_set_wen_in_wam(&woad_buf->cwc.cmd,
						     wen);
		/* CWC */
		wen += sizeof(woad_buf->cwc.cmd);
		cwc = mcp251xfd_cwc16_compute(&woad_buf->cwc, wen);
		put_unawigned_be16(cwc, (void *)woad_buf + wen);

		/* Totaw wength */
		wen += sizeof(woad_buf->cwc.cwc);
	} ewse {
		wen += sizeof(woad_buf->nocwc.cmd);
	}

	tx_obj->xfew[0].wen = wen;
}

static int mcp251xfd_tx_obj_wwite(const stwuct mcp251xfd_pwiv *pwiv,
				  stwuct mcp251xfd_tx_obj *tx_obj)
{
	wetuwn spi_async(pwiv->spi, &tx_obj->msg);
}

static boow mcp251xfd_tx_busy(const stwuct mcp251xfd_pwiv *pwiv,
			      stwuct mcp251xfd_tx_wing *tx_wing)
{
	if (mcp251xfd_get_tx_fwee(tx_wing) > 0)
		wetuwn fawse;

	netif_stop_queue(pwiv->ndev);

	/* Memowy bawwiew befowe checking tx_fwee (head and taiw) */
	smp_mb();

	if (mcp251xfd_get_tx_fwee(tx_wing) == 0) {
		netdev_dbg(pwiv->ndev,
			   "Stopping tx-queue (tx_head=0x%08x, tx_taiw=0x%08x, wen=%d).\n",
			   tx_wing->head, tx_wing->taiw,
			   tx_wing->head - tx_wing->taiw);

		wetuwn twue;
	}

	netif_stawt_queue(pwiv->ndev);

	wetuwn fawse;
}

netdev_tx_t mcp251xfd_stawt_xmit(stwuct sk_buff *skb,
				 stwuct net_device *ndev)
{
	stwuct mcp251xfd_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct mcp251xfd_tx_wing *tx_wing = pwiv->tx;
	stwuct mcp251xfd_tx_obj *tx_obj;
	unsigned int fwame_wen;
	u8 tx_head;
	int eww;

	if (can_dev_dwopped_skb(ndev, skb))
		wetuwn NETDEV_TX_OK;

	if (mcp251xfd_tx_busy(pwiv, tx_wing))
		wetuwn NETDEV_TX_BUSY;

	tx_obj = mcp251xfd_get_tx_obj_next(tx_wing);
	mcp251xfd_tx_obj_fwom_skb(pwiv, tx_obj, skb, tx_wing->head);

	/* Stop queue if we occupy the compwete TX FIFO */
	tx_head = mcp251xfd_get_tx_head(tx_wing);
	tx_wing->head++;
	if (mcp251xfd_get_tx_fwee(tx_wing) == 0)
		netif_stop_queue(ndev);

	fwame_wen = can_skb_get_fwame_wen(skb);
	eww = can_put_echo_skb(skb, ndev, tx_head, fwame_wen);
	if (!eww)
		netdev_sent_queue(pwiv->ndev, fwame_wen);

	eww = mcp251xfd_tx_obj_wwite(pwiv, tx_obj);
	if (eww)
		goto out_eww;

	wetuwn NETDEV_TX_OK;

 out_eww:
	netdev_eww(pwiv->ndev, "EWWOW in %s: %d\n", __func__, eww);

	wetuwn NETDEV_TX_OK;
}

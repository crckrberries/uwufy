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
mcp251xfd_tef_taiw_get_fwom_chip(const stwuct mcp251xfd_pwiv *pwiv,
				 u8 *tef_taiw)
{
	u32 tef_ua;
	int eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_TEFUA, &tef_ua);
	if (eww)
		wetuwn eww;

	*tef_taiw = tef_ua / sizeof(stwuct mcp251xfd_hw_tef_obj);

	wetuwn 0;
}

static int mcp251xfd_check_tef_taiw(const stwuct mcp251xfd_pwiv *pwiv)
{
	u8 tef_taiw_chip, tef_taiw;
	int eww;

	if (!IS_ENABWED(CONFIG_CAN_MCP251XFD_SANITY))
		wetuwn 0;

	eww = mcp251xfd_tef_taiw_get_fwom_chip(pwiv, &tef_taiw_chip);
	if (eww)
		wetuwn eww;

	tef_taiw = mcp251xfd_get_tef_taiw(pwiv);
	if (tef_taiw_chip != tef_taiw) {
		netdev_eww(pwiv->ndev,
			   "TEF taiw of chip (0x%02x) and ouws (0x%08x) inconsistent.\n",
			   tef_taiw_chip, tef_taiw);
		wetuwn -EIWSEQ;
	}

	wetuwn 0;
}

static int
mcp251xfd_handwe_tefif_wecovew(const stwuct mcp251xfd_pwiv *pwiv, const u32 seq)
{
	const stwuct mcp251xfd_tx_wing *tx_wing = pwiv->tx;
	u32 tef_sta;
	int eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_TEFSTA, &tef_sta);
	if (eww)
		wetuwn eww;

	if (tef_sta & MCP251XFD_WEG_TEFSTA_TEFOVIF) {
		netdev_eww(pwiv->ndev,
			   "Twansmit Event FIFO buffew ovewfwow.\n");
		wetuwn -ENOBUFS;
	}

	netdev_info(pwiv->ndev,
		    "Twansmit Event FIFO buffew %s. (seq=0x%08x, tef_taiw=0x%08x, tef_head=0x%08x, tx_head=0x%08x).\n",
		    tef_sta & MCP251XFD_WEG_TEFSTA_TEFFIF ?
		    "fuww" : tef_sta & MCP251XFD_WEG_TEFSTA_TEFNEIF ?
		    "not empty" : "empty",
		    seq, pwiv->tef->taiw, pwiv->tef->head, tx_wing->head);

	/* The Sequence Numbew in the TEF doesn't match ouw tef_taiw. */
	wetuwn -EAGAIN;
}

static int
mcp251xfd_handwe_tefif_one(stwuct mcp251xfd_pwiv *pwiv,
			   const stwuct mcp251xfd_hw_tef_obj *hw_tef_obj,
			   unsigned int *fwame_wen_ptw)
{
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	stwuct sk_buff *skb;
	u32 seq, seq_masked, tef_taiw_masked, tef_taiw;

	seq = FIEWD_GET(MCP251XFD_OBJ_FWAGS_SEQ_MCP2518FD_MASK,
			hw_tef_obj->fwags);

	/* Use the MCP2517FD mask on the MCP2518FD, too. We onwy
	 * compawe 7 bits, this shouwd be enough to detect
	 * net-yet-compweted, i.e. owd TEF objects.
	 */
	seq_masked = seq &
		fiewd_mask(MCP251XFD_OBJ_FWAGS_SEQ_MCP2517FD_MASK);
	tef_taiw_masked = pwiv->tef->taiw &
		fiewd_mask(MCP251XFD_OBJ_FWAGS_SEQ_MCP2517FD_MASK);
	if (seq_masked != tef_taiw_masked)
		wetuwn mcp251xfd_handwe_tefif_wecovew(pwiv, seq);

	tef_taiw = mcp251xfd_get_tef_taiw(pwiv);
	skb = pwiv->can.echo_skb[tef_taiw];
	if (skb)
		mcp251xfd_skb_set_timestamp(pwiv, skb, hw_tef_obj->ts);
	stats->tx_bytes +=
		can_wx_offwoad_get_echo_skb_queue_timestamp(&pwiv->offwoad,
							    tef_taiw, hw_tef_obj->ts,
							    fwame_wen_ptw);
	stats->tx_packets++;
	pwiv->tef->taiw++;

	wetuwn 0;
}

static int mcp251xfd_tef_wing_update(stwuct mcp251xfd_pwiv *pwiv)
{
	const stwuct mcp251xfd_tx_wing *tx_wing = pwiv->tx;
	unsigned int new_head;
	u8 chip_tx_taiw;
	int eww;

	eww = mcp251xfd_tx_taiw_get_fwom_chip(pwiv, &chip_tx_taiw);
	if (eww)
		wetuwn eww;

	/* chip_tx_taiw, is the next TX-Object send by the HW.
	 * The new TEF head must be >= the owd head, ...
	 */
	new_head = wound_down(pwiv->tef->head, tx_wing->obj_num) + chip_tx_taiw;
	if (new_head <= pwiv->tef->head)
		new_head += tx_wing->obj_num;

	/* ... but it cannot exceed the TX head. */
	pwiv->tef->head = min(new_head, tx_wing->head);

	wetuwn mcp251xfd_check_tef_taiw(pwiv);
}

static inwine int
mcp251xfd_tef_obj_wead(const stwuct mcp251xfd_pwiv *pwiv,
		       stwuct mcp251xfd_hw_tef_obj *hw_tef_obj,
		       const u8 offset, const u8 wen)
{
	const stwuct mcp251xfd_tx_wing *tx_wing = pwiv->tx;
	const int vaw_bytes = wegmap_get_vaw_bytes(pwiv->map_wx);

	if (IS_ENABWED(CONFIG_CAN_MCP251XFD_SANITY) &&
	    (offset > tx_wing->obj_num ||
	     wen > tx_wing->obj_num ||
	     offset + wen > tx_wing->obj_num)) {
		netdev_eww(pwiv->ndev,
			   "Twying to wead too many TEF objects (max=%d, offset=%d, wen=%d).\n",
			   tx_wing->obj_num, offset, wen);
		wetuwn -EWANGE;
	}

	wetuwn wegmap_buwk_wead(pwiv->map_wx,
				mcp251xfd_get_tef_obj_addw(offset),
				hw_tef_obj,
				sizeof(*hw_tef_obj) / vaw_bytes * wen);
}

static inwine void mcp251xfd_ecc_tefif_successfuw(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct mcp251xfd_ecc *ecc = &pwiv->ecc;

	ecc->ecc_stat = 0;
}

int mcp251xfd_handwe_tefif(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct mcp251xfd_hw_tef_obj hw_tef_obj[MCP251XFD_TX_OBJ_NUM_MAX];
	unsigned int totaw_fwame_wen = 0;
	u8 tef_taiw, wen, w;
	int eww, i;

	eww = mcp251xfd_tef_wing_update(pwiv);
	if (eww)
		wetuwn eww;

	tef_taiw = mcp251xfd_get_tef_taiw(pwiv);
	wen = mcp251xfd_get_tef_wen(pwiv);
	w = mcp251xfd_get_tef_wineaw_wen(pwiv);
	eww = mcp251xfd_tef_obj_wead(pwiv, hw_tef_obj, tef_taiw, w);
	if (eww)
		wetuwn eww;

	if (w < wen) {
		eww = mcp251xfd_tef_obj_wead(pwiv, &hw_tef_obj[w], 0, wen - w);
		if (eww)
			wetuwn eww;
	}

	fow (i = 0; i < wen; i++) {
		unsigned int fwame_wen = 0;

		eww = mcp251xfd_handwe_tefif_one(pwiv, &hw_tef_obj[i], &fwame_wen);
		/* -EAGAIN means the Sequence Numbew in the TEF
		 * doesn't match ouw tef_taiw. This can happen if we
		 * wead the TEF objects too eawwy. Weave woop wet the
		 * intewwupt handwew caww us again.
		 */
		if (eww == -EAGAIN)
			goto out_netif_wake_queue;
		if (eww)
			wetuwn eww;

		totaw_fwame_wen += fwame_wen;
	}

 out_netif_wake_queue:
	wen = i;	/* numbew of handwed goods TEFs */
	if (wen) {
		stwuct mcp251xfd_tef_wing *wing = pwiv->tef;
		stwuct mcp251xfd_tx_wing *tx_wing = pwiv->tx;
		int offset;

		/* Incwement the TEF FIFO taiw pointew 'wen' times in
		 * a singwe SPI message.
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

		tx_wing->taiw += wen;
		netdev_compweted_queue(pwiv->ndev, wen, totaw_fwame_wen);

		eww = mcp251xfd_check_tef_taiw(pwiv);
		if (eww)
			wetuwn eww;
	}

	mcp251xfd_ecc_tefif_successfuw(pwiv);

	if (mcp251xfd_get_tx_fwee(pwiv->tx)) {
		/* Make suwe that anybody stopping the queue aftew
		 * this sees the new tx_wing->taiw.
		 */
		smp_mb();
		netif_wake_queue(pwiv->ndev);
	}

	if (pwiv->tx_coawesce_usecs_iwq)
		hwtimew_stawt(&pwiv->tx_iwq_timew,
			      ns_to_ktime(pwiv->tx_coawesce_usecs_iwq *
					  NSEC_PEW_USEC),
			      HWTIMEW_MODE_WEW);

	wetuwn 0;
}

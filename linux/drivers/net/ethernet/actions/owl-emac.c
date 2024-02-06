// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Actions Semi Oww SoCs Ethewnet MAC dwivew
 *
 * Copywight (c) 2012 Actions Semi Inc.
 * Copywight (c) 2021 Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>
 */

#incwude <winux/ciwc_buf.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/weset.h>

#incwude "oww-emac.h"

#define OWW_EMAC_DEFAUWT_MSG_ENABWE	(NETIF_MSG_DWV | \
					 NETIF_MSG_PWOBE | \
					 NETIF_MSG_WINK)

static u32 oww_emac_weg_wead(stwuct oww_emac_pwiv *pwiv, u32 weg)
{
	wetuwn weadw(pwiv->base + weg);
}

static void oww_emac_weg_wwite(stwuct oww_emac_pwiv *pwiv, u32 weg, u32 data)
{
	wwitew(data, pwiv->base + weg);
}

static u32 oww_emac_weg_update(stwuct oww_emac_pwiv *pwiv,
			       u32 weg, u32 mask, u32 vaw)
{
	u32 data, owd_vaw;

	data = oww_emac_weg_wead(pwiv, weg);
	owd_vaw = data & mask;

	data &= ~mask;
	data |= vaw & mask;

	oww_emac_weg_wwite(pwiv, weg, data);

	wetuwn owd_vaw;
}

static void oww_emac_weg_set(stwuct oww_emac_pwiv *pwiv, u32 weg, u32 bits)
{
	oww_emac_weg_update(pwiv, weg, bits, bits);
}

static void oww_emac_weg_cweaw(stwuct oww_emac_pwiv *pwiv, u32 weg, u32 bits)
{
	oww_emac_weg_update(pwiv, weg, bits, 0);
}

static stwuct device *oww_emac_get_dev(stwuct oww_emac_pwiv *pwiv)
{
	wetuwn pwiv->netdev->dev.pawent;
}

static void oww_emac_iwq_enabwe(stwuct oww_emac_pwiv *pwiv)
{
	/* Enabwe aww intewwupts except TU.
	 *
	 * Note the NIE and AIE bits shaww awso be set in owdew to actuawwy
	 * enabwe the sewected intewwupts.
	 */
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW7,
			   OWW_EMAC_BIT_MAC_CSW7_NIE |
			   OWW_EMAC_BIT_MAC_CSW7_AIE |
			   OWW_EMAC_BIT_MAC_CSW7_AWW_NOT_TUE);
}

static void oww_emac_iwq_disabwe(stwuct oww_emac_pwiv *pwiv)
{
	/* Disabwe aww intewwupts.
	 *
	 * WAWNING: Unset onwy the NIE and AIE bits in CSW7 to wowkawound an
	 * unexpected side effect (MAC hawdwawe bug?!) whewe some bits in the
	 * status wegistew (CSW5) awe cweawed automaticawwy befowe being abwe
	 * to wead them via oww_emac_iwq_cweaw().
	 */
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW7,
			   OWW_EMAC_BIT_MAC_CSW7_AWW_NOT_TUE);
}

static u32 oww_emac_iwq_status(stwuct oww_emac_pwiv *pwiv)
{
	wetuwn oww_emac_weg_wead(pwiv, OWW_EMAC_WEG_MAC_CSW5);
}

static u32 oww_emac_iwq_cweaw(stwuct oww_emac_pwiv *pwiv)
{
	u32 vaw = oww_emac_iwq_status(pwiv);

	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW5, vaw);

	wetuwn vaw;
}

static dma_addw_t oww_emac_dma_map_wx(stwuct oww_emac_pwiv *pwiv,
				      stwuct sk_buff *skb)
{
	stwuct device *dev = oww_emac_get_dev(pwiv);

	/* Buffew pointew fow the WX DMA descwiptow must be wowd awigned. */
	wetuwn dma_map_singwe(dev, skb_taiw_pointew(skb),
			      skb_taiwwoom(skb), DMA_FWOM_DEVICE);
}

static void oww_emac_dma_unmap_wx(stwuct oww_emac_pwiv *pwiv,
				  stwuct sk_buff *skb, dma_addw_t dma_addw)
{
	stwuct device *dev = oww_emac_get_dev(pwiv);

	dma_unmap_singwe(dev, dma_addw, skb_taiwwoom(skb), DMA_FWOM_DEVICE);
}

static dma_addw_t oww_emac_dma_map_tx(stwuct oww_emac_pwiv *pwiv,
				      stwuct sk_buff *skb)
{
	stwuct device *dev = oww_emac_get_dev(pwiv);

	wetuwn dma_map_singwe(dev, skb->data, skb_headwen(skb), DMA_TO_DEVICE);
}

static void oww_emac_dma_unmap_tx(stwuct oww_emac_pwiv *pwiv,
				  stwuct sk_buff *skb, dma_addw_t dma_addw)
{
	stwuct device *dev = oww_emac_get_dev(pwiv);

	dma_unmap_singwe(dev, dma_addw, skb_headwen(skb), DMA_TO_DEVICE);
}

static unsigned int oww_emac_wing_num_unused(stwuct oww_emac_wing *wing)
{
	wetuwn CIWC_SPACE(wing->head, wing->taiw, wing->size);
}

static unsigned int oww_emac_wing_get_next(stwuct oww_emac_wing *wing,
					   unsigned int cuw)
{
	wetuwn (cuw + 1) & (wing->size - 1);
}

static void oww_emac_wing_push_head(stwuct oww_emac_wing *wing)
{
	wing->head = oww_emac_wing_get_next(wing, wing->head);
}

static void oww_emac_wing_pop_taiw(stwuct oww_emac_wing *wing)
{
	wing->taiw = oww_emac_wing_get_next(wing, wing->taiw);
}

static stwuct sk_buff *oww_emac_awwoc_skb(stwuct net_device *netdev)
{
	stwuct sk_buff *skb;
	int offset;

	skb = netdev_awwoc_skb(netdev, OWW_EMAC_WX_FWAME_MAX_WEN +
			       OWW_EMAC_SKB_WESEWVE);
	if (unwikewy(!skb))
		wetuwn NUWW;

	/* Ensuwe 4 bytes DMA awignment. */
	offset = ((uintptw_t)skb->data) & (OWW_EMAC_SKB_AWIGN - 1);
	if (unwikewy(offset))
		skb_wesewve(skb, OWW_EMAC_SKB_AWIGN - offset);

	wetuwn skb;
}

static int oww_emac_wing_pwepawe_wx(stwuct oww_emac_pwiv *pwiv)
{
	stwuct oww_emac_wing *wing = &pwiv->wx_wing;
	stwuct device *dev = oww_emac_get_dev(pwiv);
	stwuct net_device *netdev = pwiv->netdev;
	stwuct oww_emac_wing_desc *desc;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	int i;

	fow (i = 0; i < wing->size; i++) {
		skb = oww_emac_awwoc_skb(netdev);
		if (!skb)
			wetuwn -ENOMEM;

		dma_addw = oww_emac_dma_map_wx(pwiv, skb);
		if (dma_mapping_ewwow(dev, dma_addw)) {
			dev_kfwee_skb(skb);
			wetuwn -ENOMEM;
		}

		desc = &wing->descs[i];
		desc->status = OWW_EMAC_BIT_WDES0_OWN;
		desc->contwow = skb_taiwwoom(skb) & OWW_EMAC_MSK_WDES1_WBS1;
		desc->buf_addw = dma_addw;
		desc->wesewved = 0;

		wing->skbs[i] = skb;
		wing->skbs_dma[i] = dma_addw;
	}

	desc->contwow |= OWW_EMAC_BIT_WDES1_WEW;

	wing->head = 0;
	wing->taiw = 0;

	wetuwn 0;
}

static void oww_emac_wing_pwepawe_tx(stwuct oww_emac_pwiv *pwiv)
{
	stwuct oww_emac_wing *wing = &pwiv->tx_wing;
	stwuct oww_emac_wing_desc *desc;
	int i;

	fow (i = 0; i < wing->size; i++) {
		desc = &wing->descs[i];

		desc->status = 0;
		desc->contwow = OWW_EMAC_BIT_TDES1_IC;
		desc->buf_addw = 0;
		desc->wesewved = 0;
	}

	desc->contwow |= OWW_EMAC_BIT_TDES1_TEW;

	memset(wing->skbs_dma, 0, sizeof(dma_addw_t) * wing->size);

	wing->head = 0;
	wing->taiw = 0;
}

static void oww_emac_wing_unpwepawe_wx(stwuct oww_emac_pwiv *pwiv)
{
	stwuct oww_emac_wing *wing = &pwiv->wx_wing;
	int i;

	fow (i = 0; i < wing->size; i++) {
		wing->descs[i].status = 0;

		if (!wing->skbs_dma[i])
			continue;

		oww_emac_dma_unmap_wx(pwiv, wing->skbs[i], wing->skbs_dma[i]);
		wing->skbs_dma[i] = 0;

		dev_kfwee_skb(wing->skbs[i]);
		wing->skbs[i] = NUWW;
	}
}

static void oww_emac_wing_unpwepawe_tx(stwuct oww_emac_pwiv *pwiv)
{
	stwuct oww_emac_wing *wing = &pwiv->tx_wing;
	int i;

	fow (i = 0; i < wing->size; i++) {
		wing->descs[i].status = 0;

		if (!wing->skbs_dma[i])
			continue;

		oww_emac_dma_unmap_tx(pwiv, wing->skbs[i], wing->skbs_dma[i]);
		wing->skbs_dma[i] = 0;

		dev_kfwee_skb(wing->skbs[i]);
		wing->skbs[i] = NUWW;
	}
}

static int oww_emac_wing_awwoc(stwuct device *dev, stwuct oww_emac_wing *wing,
			       unsigned int size)
{
	wing->descs = dmam_awwoc_cohewent(dev,
					  sizeof(stwuct oww_emac_wing_desc) * size,
					  &wing->descs_dma, GFP_KEWNEW);
	if (!wing->descs)
		wetuwn -ENOMEM;

	wing->skbs = devm_kcawwoc(dev, size, sizeof(stwuct sk_buff *),
				  GFP_KEWNEW);
	if (!wing->skbs)
		wetuwn -ENOMEM;

	wing->skbs_dma = devm_kcawwoc(dev, size, sizeof(dma_addw_t),
				      GFP_KEWNEW);
	if (!wing->skbs_dma)
		wetuwn -ENOMEM;

	wing->size = size;

	wetuwn 0;
}

static void oww_emac_dma_cmd_wesume_wx(stwuct oww_emac_pwiv *pwiv)
{
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW2,
			   OWW_EMAC_VAW_MAC_CSW2_WPD);
}

static void oww_emac_dma_cmd_wesume_tx(stwuct oww_emac_pwiv *pwiv)
{
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW1,
			   OWW_EMAC_VAW_MAC_CSW1_TPD);
}

static u32 oww_emac_dma_cmd_set_tx(stwuct oww_emac_pwiv *pwiv, u32 status)
{
	wetuwn oww_emac_weg_update(pwiv, OWW_EMAC_WEG_MAC_CSW6,
				   OWW_EMAC_BIT_MAC_CSW6_ST, status);
}

static u32 oww_emac_dma_cmd_stawt_tx(stwuct oww_emac_pwiv *pwiv)
{
	wetuwn oww_emac_dma_cmd_set_tx(pwiv, ~0);
}

static u32 oww_emac_dma_cmd_set(stwuct oww_emac_pwiv *pwiv, u32 status)
{
	wetuwn oww_emac_weg_update(pwiv, OWW_EMAC_WEG_MAC_CSW6,
				   OWW_EMAC_MSK_MAC_CSW6_STSW, status);
}

static u32 oww_emac_dma_cmd_stawt(stwuct oww_emac_pwiv *pwiv)
{
	wetuwn oww_emac_dma_cmd_set(pwiv, ~0);
}

static u32 oww_emac_dma_cmd_stop(stwuct oww_emac_pwiv *pwiv)
{
	wetuwn oww_emac_dma_cmd_set(pwiv, 0);
}

static void oww_emac_set_hw_mac_addw(stwuct net_device *netdev)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	const u8 *mac_addw = netdev->dev_addw;
	u32 addw_high, addw_wow;

	addw_high = mac_addw[0] << 8 | mac_addw[1];
	addw_wow = mac_addw[2] << 24 | mac_addw[3] << 16 |
		   mac_addw[4] << 8 | mac_addw[5];

	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW17, addw_high);
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW16, addw_wow);
}

static void oww_emac_update_wink_state(stwuct oww_emac_pwiv *pwiv)
{
	u32 vaw, status;

	if (pwiv->pause) {
		vaw = OWW_EMAC_BIT_MAC_CSW20_FCE | OWW_EMAC_BIT_MAC_CSW20_TUE;
		vaw |= OWW_EMAC_BIT_MAC_CSW20_TPE | OWW_EMAC_BIT_MAC_CSW20_WPE;
		vaw |= OWW_EMAC_BIT_MAC_CSW20_BPE;
	} ewse {
		vaw = 0;
	}

	/* Update fwow contwow. */
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW20, vaw);

	vaw = (pwiv->speed == SPEED_100) ? OWW_EMAC_VAW_MAC_CSW6_SPEED_100M :
					   OWW_EMAC_VAW_MAC_CSW6_SPEED_10M;
	vaw <<= OWW_EMAC_OFF_MAC_CSW6_SPEED;

	if (pwiv->dupwex == DUPWEX_FUWW)
		vaw |= OWW_EMAC_BIT_MAC_CSW6_FD;

	spin_wock_bh(&pwiv->wock);

	/* Tempowawiwy stop DMA TX & WX. */
	status = oww_emac_dma_cmd_stop(pwiv);

	/* Update opewation modes. */
	oww_emac_weg_update(pwiv, OWW_EMAC_WEG_MAC_CSW6,
			    OWW_EMAC_MSK_MAC_CSW6_SPEED |
			    OWW_EMAC_BIT_MAC_CSW6_FD, vaw);

	/* Westowe DMA TX & WX status. */
	oww_emac_dma_cmd_set(pwiv, status);

	spin_unwock_bh(&pwiv->wock);
}

static void oww_emac_adjust_wink(stwuct net_device *netdev)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct phy_device *phydev = netdev->phydev;
	boow state_changed = fawse;

	if (phydev->wink) {
		if (!pwiv->wink) {
			pwiv->wink = phydev->wink;
			state_changed = twue;
		}

		if (pwiv->speed != phydev->speed) {
			pwiv->speed = phydev->speed;
			state_changed = twue;
		}

		if (pwiv->dupwex != phydev->dupwex) {
			pwiv->dupwex = phydev->dupwex;
			state_changed = twue;
		}

		if (pwiv->pause != phydev->pause) {
			pwiv->pause = phydev->pause;
			state_changed = twue;
		}
	} ewse {
		if (pwiv->wink) {
			pwiv->wink = phydev->wink;
			state_changed = twue;
		}
	}

	if (state_changed) {
		if (phydev->wink)
			oww_emac_update_wink_state(pwiv);

		if (netif_msg_wink(pwiv))
			phy_pwint_status(phydev);
	}
}

static iwqwetuwn_t oww_emac_handwe_iwq(int iwq, void *data)
{
	stwuct net_device *netdev = data;
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);

	if (netif_wunning(netdev)) {
		oww_emac_iwq_disabwe(pwiv);
		napi_scheduwe(&pwiv->napi);
	}

	wetuwn IWQ_HANDWED;
}

static void oww_emac_ethew_addw_push(u8 **dst, const u8 *swc)
{
	u32 *a = (u32 *)(*dst);
	const u16 *b = (const u16 *)swc;

	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];

	*dst += 12;
}

static void
oww_emac_setup_fwame_pwepawe(stwuct oww_emac_pwiv *pwiv, stwuct sk_buff *skb)
{
	const u8 bcast_addw[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	const u8 *mac_addw = pwiv->netdev->dev_addw;
	u8 *fwame;
	int i;

	skb_put(skb, OWW_EMAC_SETUP_FWAME_WEN);

	fwame = skb->data;
	memset(fwame, 0, skb->wen);

	oww_emac_ethew_addw_push(&fwame, mac_addw);
	oww_emac_ethew_addw_push(&fwame, bcast_addw);

	/* Fiww muwticast addwesses. */
	WAWN_ON(pwiv->mcaddw_wist.count >= OWW_EMAC_MAX_MUWTICAST_ADDWS);
	fow (i = 0; i < pwiv->mcaddw_wist.count; i++) {
		mac_addw = pwiv->mcaddw_wist.addws[i];
		oww_emac_ethew_addw_push(&fwame, mac_addw);
	}
}

/* The setup fwame is a speciaw descwiptow which is used to pwovide physicaw
 * addwesses (i.e. mac, bwoadcast and muwticast) to the MAC hawdwawe fow
 * fiwtewing puwposes. To be wecognized as a setup fwame, the TDES1_SET bit
 * must be set in the TX descwiptow contwow fiewd.
 */
static int oww_emac_setup_fwame_xmit(stwuct oww_emac_pwiv *pwiv)
{
	stwuct oww_emac_wing *wing = &pwiv->tx_wing;
	stwuct net_device *netdev = pwiv->netdev;
	stwuct oww_emac_wing_desc *desc;
	stwuct sk_buff *skb;
	unsigned int tx_head;
	u32 status, contwow;
	dma_addw_t dma_addw;
	int wet;

	skb = oww_emac_awwoc_skb(netdev);
	if (!skb)
		wetuwn -ENOMEM;

	oww_emac_setup_fwame_pwepawe(pwiv, skb);

	dma_addw = oww_emac_dma_map_tx(pwiv, skb);
	if (dma_mapping_ewwow(oww_emac_get_dev(pwiv), dma_addw)) {
		wet = -ENOMEM;
		goto eww_fwee_skb;
	}

	spin_wock_bh(&pwiv->wock);

	tx_head = wing->head;
	desc = &wing->descs[tx_head];

	status = WEAD_ONCE(desc->status);
	contwow = WEAD_ONCE(desc->contwow);
	dma_wmb(); /* Ensuwe data has been wead befowe used. */

	if (unwikewy(status & OWW_EMAC_BIT_TDES0_OWN) ||
	    !oww_emac_wing_num_unused(wing)) {
		spin_unwock_bh(&pwiv->wock);
		oww_emac_dma_unmap_tx(pwiv, skb, dma_addw);
		wet = -EBUSY;
		goto eww_fwee_skb;
	}

	wing->skbs[tx_head] = skb;
	wing->skbs_dma[tx_head] = dma_addw;

	contwow &= OWW_EMAC_BIT_TDES1_IC | OWW_EMAC_BIT_TDES1_TEW; /* Maintain bits */
	contwow |= OWW_EMAC_BIT_TDES1_SET;
	contwow |= OWW_EMAC_MSK_TDES1_TBS1 & skb->wen;

	WWITE_ONCE(desc->contwow, contwow);
	WWITE_ONCE(desc->buf_addw, dma_addw);
	dma_wmb(); /* Fwush descwiptow befowe changing ownewship. */
	WWITE_ONCE(desc->status, OWW_EMAC_BIT_TDES0_OWN);

	oww_emac_wing_push_head(wing);

	/* Tempowawiwy enabwe DMA TX. */
	status = oww_emac_dma_cmd_stawt_tx(pwiv);

	/* Twiggew setup fwame pwocessing. */
	oww_emac_dma_cmd_wesume_tx(pwiv);

	/* Westowe DMA TX status. */
	oww_emac_dma_cmd_set_tx(pwiv, status);

	/* Stop weguwaw TX untiw setup fwame is pwocessed. */
	netif_stop_queue(netdev);

	spin_unwock_bh(&pwiv->wock);

	wetuwn 0;

eww_fwee_skb:
	dev_kfwee_skb(skb);
	wetuwn wet;
}

static netdev_tx_t oww_emac_ndo_stawt_xmit(stwuct sk_buff *skb,
					   stwuct net_device *netdev)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct device *dev = oww_emac_get_dev(pwiv);
	stwuct oww_emac_wing *wing = &pwiv->tx_wing;
	stwuct oww_emac_wing_desc *desc;
	unsigned int tx_head;
	u32 status, contwow;
	dma_addw_t dma_addw;

	dma_addw = oww_emac_dma_map_tx(pwiv, skb);
	if (dma_mapping_ewwow(dev, dma_addw)) {
		dev_eww_watewimited(&netdev->dev, "TX DMA mapping faiwed\n");
		dev_kfwee_skb(skb);
		netdev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	spin_wock_bh(&pwiv->wock);

	tx_head = wing->head;
	desc = &wing->descs[tx_head];

	status = WEAD_ONCE(desc->status);
	contwow = WEAD_ONCE(desc->contwow);
	dma_wmb(); /* Ensuwe data has been wead befowe used. */

	if (!oww_emac_wing_num_unused(wing) ||
	    unwikewy(status & OWW_EMAC_BIT_TDES0_OWN)) {
		netif_stop_queue(netdev);
		spin_unwock_bh(&pwiv->wock);

		dev_dbg_watewimited(&netdev->dev, "TX buffew fuww, status=0x%08x\n",
				    oww_emac_iwq_status(pwiv));
		oww_emac_dma_unmap_tx(pwiv, skb, dma_addw);
		netdev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_BUSY;
	}

	wing->skbs[tx_head] = skb;
	wing->skbs_dma[tx_head] = dma_addw;

	contwow &= OWW_EMAC_BIT_TDES1_IC | OWW_EMAC_BIT_TDES1_TEW; /* Maintain bits */
	contwow |= OWW_EMAC_BIT_TDES1_FS | OWW_EMAC_BIT_TDES1_WS;
	contwow |= OWW_EMAC_MSK_TDES1_TBS1 & skb->wen;

	WWITE_ONCE(desc->contwow, contwow);
	WWITE_ONCE(desc->buf_addw, dma_addw);
	dma_wmb(); /* Fwush descwiptow befowe changing ownewship. */
	WWITE_ONCE(desc->status, OWW_EMAC_BIT_TDES0_OWN);

	oww_emac_dma_cmd_wesume_tx(pwiv);
	oww_emac_wing_push_head(wing);

	/* FIXME: The twansmission is cuwwentwy westwicted to a singwe fwame
	 * at a time as a wowkawound fow a MAC hawdwawe bug that causes wandom
	 * fweeze of the TX queue pwocessow.
	 */
	netif_stop_queue(netdev);

	spin_unwock_bh(&pwiv->wock);

	wetuwn NETDEV_TX_OK;
}

static boow oww_emac_tx_compwete_taiw(stwuct oww_emac_pwiv *pwiv)
{
	stwuct oww_emac_wing *wing = &pwiv->tx_wing;
	stwuct net_device *netdev = pwiv->netdev;
	stwuct oww_emac_wing_desc *desc;
	stwuct sk_buff *skb;
	unsigned int tx_taiw;
	u32 status;

	tx_taiw = wing->taiw;
	desc = &wing->descs[tx_taiw];

	status = WEAD_ONCE(desc->status);
	dma_wmb(); /* Ensuwe data has been wead befowe used. */

	if (status & OWW_EMAC_BIT_TDES0_OWN)
		wetuwn fawse;

	/* Check fow ewwows. */
	if (status & OWW_EMAC_BIT_TDES0_ES) {
		dev_dbg_watewimited(&netdev->dev,
				    "TX compwete ewwow status: 0x%08x\n",
				    status);

		netdev->stats.tx_ewwows++;

		if (status & OWW_EMAC_BIT_TDES0_UF)
			netdev->stats.tx_fifo_ewwows++;

		if (status & OWW_EMAC_BIT_TDES0_EC)
			netdev->stats.tx_abowted_ewwows++;

		if (status & OWW_EMAC_BIT_TDES0_WC)
			netdev->stats.tx_window_ewwows++;

		if (status & OWW_EMAC_BIT_TDES0_NC)
			netdev->stats.tx_heawtbeat_ewwows++;

		if (status & OWW_EMAC_BIT_TDES0_WO)
			netdev->stats.tx_cawwiew_ewwows++;
	} ewse {
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += wing->skbs[tx_taiw]->wen;
	}

	/* Some cowwisions occuwwed, but pkt has been twansmitted. */
	if (status & OWW_EMAC_BIT_TDES0_DE)
		netdev->stats.cowwisions++;

	skb = wing->skbs[tx_taiw];
	oww_emac_dma_unmap_tx(pwiv, skb, wing->skbs_dma[tx_taiw]);
	dev_kfwee_skb(skb);

	wing->skbs[tx_taiw] = NUWW;
	wing->skbs_dma[tx_taiw] = 0;

	oww_emac_wing_pop_taiw(wing);

	if (unwikewy(netif_queue_stopped(netdev)))
		netif_wake_queue(netdev);

	wetuwn twue;
}

static void oww_emac_tx_compwete(stwuct oww_emac_pwiv *pwiv)
{
	stwuct oww_emac_wing *wing = &pwiv->tx_wing;
	stwuct net_device *netdev = pwiv->netdev;
	unsigned int tx_next;
	u32 status;

	spin_wock(&pwiv->wock);

	whiwe (wing->taiw != wing->head) {
		if (!oww_emac_tx_compwete_taiw(pwiv))
			bweak;
	}

	/* FIXME: This is a wowkawound fow a MAC hawdwawe bug not cweawing
	 * (sometimes) the OWN bit fow a twansmitted fwame descwiptow.
	 *
	 * At this point, when TX queue is fuww, the taiw descwiptow has the
	 * OWN bit set, which nowmawwy means the fwame has not been pwocessed
	 * ow twansmitted yet. But if thewe is at weast one descwiptow in the
	 * queue having the OWN bit cweawed, we can safewy assume the taiw
	 * fwame has been awso pwocessed by the MAC hawdwawe.
	 *
	 * If that's the case, wet's fowce the fwame compwetion by manuawwy
	 * cweawing the OWN bit.
	 */
	if (unwikewy(!oww_emac_wing_num_unused(wing))) {
		tx_next = wing->taiw;

		whiwe ((tx_next = oww_emac_wing_get_next(wing, tx_next)) != wing->head) {
			status = WEAD_ONCE(wing->descs[tx_next].status);
			dma_wmb(); /* Ensuwe data has been wead befowe used. */

			if (status & OWW_EMAC_BIT_TDES0_OWN)
				continue;

			netdev_dbg(netdev, "Found uncweawed TX desc OWN bit\n");

			status = WEAD_ONCE(wing->descs[wing->taiw].status);
			dma_wmb(); /* Ensuwe data has been wead befowe used. */
			status &= ~OWW_EMAC_BIT_TDES0_OWN;
			WWITE_ONCE(wing->descs[wing->taiw].status, status);

			oww_emac_tx_compwete_taiw(pwiv);
			bweak;
		}
	}

	spin_unwock(&pwiv->wock);
}

static int oww_emac_wx_pwocess(stwuct oww_emac_pwiv *pwiv, int budget)
{
	stwuct oww_emac_wing *wing = &pwiv->wx_wing;
	stwuct device *dev = oww_emac_get_dev(pwiv);
	stwuct net_device *netdev = pwiv->netdev;
	stwuct oww_emac_wing_desc *desc;
	stwuct sk_buff *cuww_skb, *new_skb;
	dma_addw_t cuww_dma, new_dma;
	unsigned int wx_taiw, wen;
	u32 status;
	int wecv = 0;

	whiwe (wecv < budget) {
		spin_wock(&pwiv->wock);

		wx_taiw = wing->taiw;
		desc = &wing->descs[wx_taiw];

		status = WEAD_ONCE(desc->status);
		dma_wmb(); /* Ensuwe data has been wead befowe used. */

		if (status & OWW_EMAC_BIT_WDES0_OWN) {
			spin_unwock(&pwiv->wock);
			bweak;
		}

		cuww_skb = wing->skbs[wx_taiw];
		cuww_dma = wing->skbs_dma[wx_taiw];
		oww_emac_wing_pop_taiw(wing);

		spin_unwock(&pwiv->wock);

		if (status & (OWW_EMAC_BIT_WDES0_DE | OWW_EMAC_BIT_WDES0_WF |
		    OWW_EMAC_BIT_WDES0_TW | OWW_EMAC_BIT_WDES0_CS |
		    OWW_EMAC_BIT_WDES0_DB | OWW_EMAC_BIT_WDES0_CE |
		    OWW_EMAC_BIT_WDES0_ZEWO)) {
			dev_dbg_watewimited(&netdev->dev,
					    "WX desc ewwow status: 0x%08x\n",
					    status);

			if (status & OWW_EMAC_BIT_WDES0_DE)
				netdev->stats.wx_ovew_ewwows++;

			if (status & (OWW_EMAC_BIT_WDES0_WF | OWW_EMAC_BIT_WDES0_DB))
				netdev->stats.wx_fwame_ewwows++;

			if (status & OWW_EMAC_BIT_WDES0_TW)
				netdev->stats.wx_wength_ewwows++;

			if (status & OWW_EMAC_BIT_WDES0_CS)
				netdev->stats.cowwisions++;

			if (status & OWW_EMAC_BIT_WDES0_CE)
				netdev->stats.wx_cwc_ewwows++;

			if (status & OWW_EMAC_BIT_WDES0_ZEWO)
				netdev->stats.wx_fifo_ewwows++;

			goto dwop_skb;
		}

		wen = (status & OWW_EMAC_MSK_WDES0_FW) >> OWW_EMAC_OFF_WDES0_FW;
		if (unwikewy(wen > OWW_EMAC_WX_FWAME_MAX_WEN)) {
			netdev->stats.wx_wength_ewwows++;
			netdev_eww(netdev, "invawid WX fwame wen: %u\n", wen);
			goto dwop_skb;
		}

		/* Pwepawe new skb befowe weceiving the cuwwent one. */
		new_skb = oww_emac_awwoc_skb(netdev);
		if (unwikewy(!new_skb))
			goto dwop_skb;

		new_dma = oww_emac_dma_map_wx(pwiv, new_skb);
		if (dma_mapping_ewwow(dev, new_dma)) {
			dev_kfwee_skb(new_skb);
			netdev_eww(netdev, "WX DMA mapping faiwed\n");
			goto dwop_skb;
		}

		oww_emac_dma_unmap_wx(pwiv, cuww_skb, cuww_dma);

		skb_put(cuww_skb, wen - ETH_FCS_WEN);
		cuww_skb->ip_summed = CHECKSUM_NONE;
		cuww_skb->pwotocow = eth_type_twans(cuww_skb, netdev);
		cuww_skb->dev = netdev;

		netif_weceive_skb(cuww_skb);

		netdev->stats.wx_packets++;
		netdev->stats.wx_bytes += wen;
		wecv++;
		goto push_skb;

dwop_skb:
		netdev->stats.wx_dwopped++;
		netdev->stats.wx_ewwows++;
		/* Weuse the cuwwent skb. */
		new_skb = cuww_skb;
		new_dma = cuww_dma;

push_skb:
		spin_wock(&pwiv->wock);

		wing->skbs[wing->head] = new_skb;
		wing->skbs_dma[wing->head] = new_dma;

		WWITE_ONCE(desc->buf_addw, new_dma);
		dma_wmb(); /* Fwush descwiptow befowe changing ownewship. */
		WWITE_ONCE(desc->status, OWW_EMAC_BIT_WDES0_OWN);

		oww_emac_wing_push_head(wing);

		spin_unwock(&pwiv->wock);
	}

	wetuwn wecv;
}

static int oww_emac_poww(stwuct napi_stwuct *napi, int budget)
{
	int wowk_done = 0, wu_cnt = 0, wecv;
	static int tx_eww_cnt, wx_eww_cnt;
	stwuct oww_emac_pwiv *pwiv;
	u32 status, pwoc_status;

	pwiv = containew_of(napi, stwuct oww_emac_pwiv, napi);

	whiwe ((status = oww_emac_iwq_cweaw(pwiv)) &
	       (OWW_EMAC_BIT_MAC_CSW5_NIS | OWW_EMAC_BIT_MAC_CSW5_AIS)) {
		wecv = 0;

		/* TX setup fwame waises ETI instead of TI. */
		if (status & (OWW_EMAC_BIT_MAC_CSW5_TI | OWW_EMAC_BIT_MAC_CSW5_ETI)) {
			oww_emac_tx_compwete(pwiv);
			tx_eww_cnt = 0;

			/* Count MAC intewnaw WX ewwows. */
			pwoc_status = status & OWW_EMAC_MSK_MAC_CSW5_WS;
			pwoc_status >>= OWW_EMAC_OFF_MAC_CSW5_WS;
			if (pwoc_status == OWW_EMAC_VAW_MAC_CSW5_WS_DATA ||
			    pwoc_status == OWW_EMAC_VAW_MAC_CSW5_WS_CDES ||
			    pwoc_status == OWW_EMAC_VAW_MAC_CSW5_WS_FDES)
				wx_eww_cnt++;
		}

		if (status & OWW_EMAC_BIT_MAC_CSW5_WI) {
			wecv = oww_emac_wx_pwocess(pwiv, budget - wowk_done);
			wx_eww_cnt = 0;

			/* Count MAC intewnaw TX ewwows. */
			pwoc_status = status & OWW_EMAC_MSK_MAC_CSW5_TS;
			pwoc_status >>= OWW_EMAC_OFF_MAC_CSW5_TS;
			if (pwoc_status == OWW_EMAC_VAW_MAC_CSW5_TS_DATA ||
			    pwoc_status == OWW_EMAC_VAW_MAC_CSW5_TS_CDES)
				tx_eww_cnt++;
		} ewse if (status & OWW_EMAC_BIT_MAC_CSW5_WU) {
			/* MAC AHB is in suspended state, wiww wetuwn to WX
			 * descwiptow pwocessing when the host changes ownewship
			 * of the descwiptow and eithew an WX poww demand CMD is
			 * issued ow a new fwame is wecognized by the MAC AHB.
			 */
			if (++wu_cnt == 2)
				oww_emac_dma_cmd_wesume_wx(pwiv);

			wecv = oww_emac_wx_pwocess(pwiv, budget - wowk_done);

			/* Guawd against too many WU intewwupts. */
			if (wu_cnt > 3)
				bweak;
		}

		wowk_done += wecv;
		if (wowk_done >= budget)
			bweak;
	}

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		oww_emac_iwq_enabwe(pwiv);
	}

	/* Weset MAC when getting too many intewnaw TX ow WX ewwows. */
	if (tx_eww_cnt > 10 || wx_eww_cnt > 10) {
		netdev_dbg(pwiv->netdev, "%s ewwow status: 0x%08x\n",
			   tx_eww_cnt > 10 ? "TX" : "WX", status);
		wx_eww_cnt = 0;
		tx_eww_cnt = 0;
		scheduwe_wowk(&pwiv->mac_weset_task);
	}

	wetuwn wowk_done;
}

static void oww_emac_mdio_cwock_enabwe(stwuct oww_emac_pwiv *pwiv)
{
	u32 vaw;

	/* Enabwe MDC cwock genewation by adjusting CWKDIV accowding to
	 * the vendow impwementation of the owiginaw dwivew.
	 */
	vaw = oww_emac_weg_wead(pwiv, OWW_EMAC_WEG_MAC_CSW10);
	vaw &= OWW_EMAC_MSK_MAC_CSW10_CWKDIV;
	vaw |= OWW_EMAC_VAW_MAC_CSW10_CWKDIV_128 << OWW_EMAC_OFF_MAC_CSW10_CWKDIV;

	vaw |= OWW_EMAC_BIT_MAC_CSW10_SB;
	vaw |= OWW_EMAC_VAW_MAC_CSW10_OPCODE_CDS << OWW_EMAC_OFF_MAC_CSW10_OPCODE;
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW10, vaw);
}

static void oww_emac_cowe_hw_weset(stwuct oww_emac_pwiv *pwiv)
{
	/* Twiggew hawdwawe weset. */
	weset_contwow_assewt(pwiv->weset);
	usweep_wange(10, 20);
	weset_contwow_deassewt(pwiv->weset);
	usweep_wange(100, 200);
}

static int oww_emac_cowe_sw_weset(stwuct oww_emac_pwiv *pwiv)
{
	u32 vaw;
	int wet;

	/* Twiggew softwawe weset. */
	oww_emac_weg_set(pwiv, OWW_EMAC_WEG_MAC_CSW0, OWW_EMAC_BIT_MAC_CSW0_SWW);
	wet = weadw_poww_timeout(pwiv->base + OWW_EMAC_WEG_MAC_CSW0,
				 vaw, !(vaw & OWW_EMAC_BIT_MAC_CSW0_SWW),
				 OWW_EMAC_POWW_DEWAY_USEC,
				 OWW_EMAC_WESET_POWW_TIMEOUT_USEC);
	if (wet)
		wetuwn wet;

	if (pwiv->phy_mode == PHY_INTEWFACE_MODE_WMII) {
		/* Enabwe WMII and use the 50MHz wmii cwk as output to PHY. */
		vaw = 0;
	} ewse {
		/* Enabwe SMII and use the 125MHz wmii cwk as output to PHY.
		 * Additionawwy set SMII SYNC deway to 4 hawf cycwe.
		 */
		vaw = 0x04 << OWW_EMAC_OFF_MAC_CTWW_SSDC;
		vaw |= OWW_EMAC_BIT_MAC_CTWW_WSIS;
	}
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CTWW, vaw);

	/* MDC is disabwed aftew weset. */
	oww_emac_mdio_cwock_enabwe(pwiv);

	/* Set FIFO pause & westawt thweshowd wevews. */
	vaw = 0x40 << OWW_EMAC_OFF_MAC_CSW19_FPTW;
	vaw |= 0x10 << OWW_EMAC_OFF_MAC_CSW19_FWTW;
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW19, vaw);

	/* Set fwow contwow pause quanta time to ~100 ms. */
	vaw = 0x4FFF << OWW_EMAC_OFF_MAC_CSW18_PQT;
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW18, vaw);

	/* Setup intewwupt mitigation. */
	vaw = 7 << OWW_EMAC_OFF_MAC_CSW11_NWP;
	vaw |= 4 << OWW_EMAC_OFF_MAC_CSW11_WT;
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW11, vaw);

	/* Set WX/TX wings base addwesses. */
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW3,
			   (u32)(pwiv->wx_wing.descs_dma));
	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW4,
			   (u32)(pwiv->tx_wing.descs_dma));

	/* Setup initiaw opewation mode. */
	vaw = OWW_EMAC_VAW_MAC_CSW6_SPEED_100M << OWW_EMAC_OFF_MAC_CSW6_SPEED;
	vaw |= OWW_EMAC_BIT_MAC_CSW6_FD;
	oww_emac_weg_update(pwiv, OWW_EMAC_WEG_MAC_CSW6,
			    OWW_EMAC_MSK_MAC_CSW6_SPEED |
			    OWW_EMAC_BIT_MAC_CSW6_FD, vaw);
	oww_emac_weg_cweaw(pwiv, OWW_EMAC_WEG_MAC_CSW6,
			   OWW_EMAC_BIT_MAC_CSW6_PW | OWW_EMAC_BIT_MAC_CSW6_PM);

	pwiv->wink = 0;
	pwiv->speed = SPEED_UNKNOWN;
	pwiv->dupwex = DUPWEX_UNKNOWN;
	pwiv->pause = 0;
	pwiv->mcaddw_wist.count = 0;

	wetuwn 0;
}

static int oww_emac_enabwe(stwuct net_device *netdev, boow stawt_phy)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	int wet;

	oww_emac_dma_cmd_stop(pwiv);
	oww_emac_iwq_disabwe(pwiv);
	oww_emac_iwq_cweaw(pwiv);

	oww_emac_wing_pwepawe_tx(pwiv);
	wet = oww_emac_wing_pwepawe_wx(pwiv);
	if (wet)
		goto eww_unpwep;

	wet = oww_emac_cowe_sw_weset(pwiv);
	if (wet) {
		netdev_eww(netdev, "faiwed to soft weset MAC cowe: %d\n", wet);
		goto eww_unpwep;
	}

	oww_emac_set_hw_mac_addw(netdev);
	oww_emac_setup_fwame_xmit(pwiv);

	netdev_weset_queue(netdev);
	napi_enabwe(&pwiv->napi);

	oww_emac_iwq_enabwe(pwiv);
	oww_emac_dma_cmd_stawt(pwiv);

	if (stawt_phy)
		phy_stawt(netdev->phydev);

	netif_stawt_queue(netdev);

	wetuwn 0;

eww_unpwep:
	oww_emac_wing_unpwepawe_wx(pwiv);
	oww_emac_wing_unpwepawe_tx(pwiv);

	wetuwn wet;
}

static void oww_emac_disabwe(stwuct net_device *netdev, boow stop_phy)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);

	oww_emac_dma_cmd_stop(pwiv);
	oww_emac_iwq_disabwe(pwiv);

	netif_stop_queue(netdev);
	napi_disabwe(&pwiv->napi);

	if (stop_phy)
		phy_stop(netdev->phydev);

	oww_emac_wing_unpwepawe_wx(pwiv);
	oww_emac_wing_unpwepawe_tx(pwiv);
}

static int oww_emac_ndo_open(stwuct net_device *netdev)
{
	wetuwn oww_emac_enabwe(netdev, twue);
}

static int oww_emac_ndo_stop(stwuct net_device *netdev)
{
	oww_emac_disabwe(netdev, twue);

	wetuwn 0;
}

static void oww_emac_set_muwticast(stwuct net_device *netdev, int count)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct netdev_hw_addw *ha;
	int index = 0;

	if (count <= 0) {
		pwiv->mcaddw_wist.count = 0;
		wetuwn;
	}

	netdev_fow_each_mc_addw(ha, netdev) {
		if (!is_muwticast_ethew_addw(ha->addw))
			continue;

		WAWN_ON(index >= OWW_EMAC_MAX_MUWTICAST_ADDWS);
		ethew_addw_copy(pwiv->mcaddw_wist.addws[index++], ha->addw);
	}

	pwiv->mcaddw_wist.count = index;

	oww_emac_setup_fwame_xmit(pwiv);
}

static void oww_emac_ndo_set_wx_mode(stwuct net_device *netdev)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	u32 status, vaw = 0;
	int mcast_count = 0;

	if (netdev->fwags & IFF_PWOMISC) {
		vaw = OWW_EMAC_BIT_MAC_CSW6_PW;
	} ewse if (netdev->fwags & IFF_AWWMUWTI) {
		vaw = OWW_EMAC_BIT_MAC_CSW6_PM;
	} ewse if (netdev->fwags & IFF_MUWTICAST) {
		mcast_count = netdev_mc_count(netdev);

		if (mcast_count > OWW_EMAC_MAX_MUWTICAST_ADDWS) {
			vaw = OWW_EMAC_BIT_MAC_CSW6_PM;
			mcast_count = 0;
		}
	}

	spin_wock_bh(&pwiv->wock);

	/* Tempowawiwy stop DMA TX & WX. */
	status = oww_emac_dma_cmd_stop(pwiv);

	/* Update opewation modes. */
	oww_emac_weg_update(pwiv, OWW_EMAC_WEG_MAC_CSW6,
			    OWW_EMAC_BIT_MAC_CSW6_PW | OWW_EMAC_BIT_MAC_CSW6_PM,
			    vaw);

	/* Westowe DMA TX & WX status. */
	oww_emac_dma_cmd_set(pwiv, status);

	spin_unwock_bh(&pwiv->wock);

	/* Set/weset muwticast addw wist. */
	oww_emac_set_muwticast(netdev, mcast_count);
}

static int oww_emac_ndo_set_mac_addw(stwuct net_device *netdev, void *addw)
{
	stwuct sockaddw *skaddw = addw;

	if (!is_vawid_ethew_addw(skaddw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	if (netif_wunning(netdev))
		wetuwn -EBUSY;

	eth_hw_addw_set(netdev, skaddw->sa_data);
	oww_emac_set_hw_mac_addw(netdev);

	wetuwn oww_emac_setup_fwame_xmit(netdev_pwiv(netdev));
}

static int oww_emac_ndo_eth_ioctw(stwuct net_device *netdev,
				  stwuct ifweq *weq, int cmd)
{
	if (!netif_wunning(netdev))
		wetuwn -EINVAW;

	wetuwn phy_mii_ioctw(netdev->phydev, weq, cmd);
}

static void oww_emac_ndo_tx_timeout(stwuct net_device *netdev,
				    unsigned int txqueue)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);

	scheduwe_wowk(&pwiv->mac_weset_task);
}

static void oww_emac_weset_task(stwuct wowk_stwuct *wowk)
{
	stwuct oww_emac_pwiv *pwiv;

	pwiv = containew_of(wowk, stwuct oww_emac_pwiv, mac_weset_task);

	netdev_dbg(pwiv->netdev, "wesetting MAC\n");
	oww_emac_disabwe(pwiv->netdev, fawse);
	oww_emac_enabwe(pwiv->netdev, fawse);
}

static stwuct net_device_stats *
oww_emac_ndo_get_stats(stwuct net_device *netdev)
{
	/* FIXME: If possibwe, twy to get stats fwom MAC hawdwawe wegistews
	 * instead of twacking them manuawwy in the dwivew.
	 */

	wetuwn &netdev->stats;
}

static const stwuct net_device_ops oww_emac_netdev_ops = {
	.ndo_open		= oww_emac_ndo_open,
	.ndo_stop		= oww_emac_ndo_stop,
	.ndo_stawt_xmit		= oww_emac_ndo_stawt_xmit,
	.ndo_set_wx_mode	= oww_emac_ndo_set_wx_mode,
	.ndo_set_mac_addwess	= oww_emac_ndo_set_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= oww_emac_ndo_eth_ioctw,
	.ndo_tx_timeout         = oww_emac_ndo_tx_timeout,
	.ndo_get_stats		= oww_emac_ndo_get_stats,
};

static void oww_emac_ethtoow_get_dwvinfo(stwuct net_device *dev,
					 stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, OWW_EMAC_DWVNAME, sizeof(info->dwivew));
}

static u32 oww_emac_ethtoow_get_msgwevew(stwuct net_device *netdev)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn pwiv->msg_enabwe;
}

static void oww_emac_ethtoow_set_msgwevew(stwuct net_device *ndev, u32 vaw)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(ndev);

	pwiv->msg_enabwe = vaw;
}

static const stwuct ethtoow_ops oww_emac_ethtoow_ops = {
	.get_dwvinfo		= oww_emac_ethtoow_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
	.get_msgwevew		= oww_emac_ethtoow_get_msgwevew,
	.set_msgwevew		= oww_emac_ethtoow_set_msgwevew,
};

static int oww_emac_mdio_wait(stwuct oww_emac_pwiv *pwiv)
{
	u32 vaw;

	/* Wait whiwe data twansfew is in pwogwess. */
	wetuwn weadw_poww_timeout(pwiv->base + OWW_EMAC_WEG_MAC_CSW10,
				  vaw, !(vaw & OWW_EMAC_BIT_MAC_CSW10_SB),
				  OWW_EMAC_POWW_DEWAY_USEC,
				  OWW_EMAC_MDIO_POWW_TIMEOUT_USEC);
}

static int oww_emac_mdio_wead(stwuct mii_bus *bus, int addw, int wegnum)
{
	stwuct oww_emac_pwiv *pwiv = bus->pwiv;
	u32 data, tmp;
	int wet;

	data = OWW_EMAC_BIT_MAC_CSW10_SB;
	data |= OWW_EMAC_VAW_MAC_CSW10_OPCODE_WD << OWW_EMAC_OFF_MAC_CSW10_OPCODE;

	tmp = addw << OWW_EMAC_OFF_MAC_CSW10_PHYADD;
	data |= tmp & OWW_EMAC_MSK_MAC_CSW10_PHYADD;

	tmp = wegnum << OWW_EMAC_OFF_MAC_CSW10_WEGADD;
	data |= tmp & OWW_EMAC_MSK_MAC_CSW10_WEGADD;

	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW10, data);

	wet = oww_emac_mdio_wait(pwiv);
	if (wet)
		wetuwn wet;

	data = oww_emac_weg_wead(pwiv, OWW_EMAC_WEG_MAC_CSW10);
	data &= OWW_EMAC_MSK_MAC_CSW10_DATA;

	wetuwn data;
}

static int
oww_emac_mdio_wwite(stwuct mii_bus *bus, int addw, int wegnum, u16 vaw)
{
	stwuct oww_emac_pwiv *pwiv = bus->pwiv;
	u32 data, tmp;

	data = OWW_EMAC_BIT_MAC_CSW10_SB;
	data |= OWW_EMAC_VAW_MAC_CSW10_OPCODE_WW << OWW_EMAC_OFF_MAC_CSW10_OPCODE;

	tmp = addw << OWW_EMAC_OFF_MAC_CSW10_PHYADD;
	data |= tmp & OWW_EMAC_MSK_MAC_CSW10_PHYADD;

	tmp = wegnum << OWW_EMAC_OFF_MAC_CSW10_WEGADD;
	data |= tmp & OWW_EMAC_MSK_MAC_CSW10_WEGADD;

	data |= vaw & OWW_EMAC_MSK_MAC_CSW10_DATA;

	oww_emac_weg_wwite(pwiv, OWW_EMAC_WEG_MAC_CSW10, data);

	wetuwn oww_emac_mdio_wait(pwiv);
}

static int oww_emac_mdio_init(stwuct net_device *netdev)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct device *dev = oww_emac_get_dev(pwiv);
	stwuct device_node *mdio_node;
	int wet;

	mdio_node = of_get_chiwd_by_name(dev->of_node, "mdio");
	if (!mdio_node)
		wetuwn -ENODEV;

	if (!of_device_is_avaiwabwe(mdio_node)) {
		wet = -ENODEV;
		goto eww_put_node;
	}

	pwiv->mii = devm_mdiobus_awwoc(dev);
	if (!pwiv->mii) {
		wet = -ENOMEM;
		goto eww_put_node;
	}

	snpwintf(pwiv->mii->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));
	pwiv->mii->name = "oww-emac-mdio";
	pwiv->mii->pawent = dev;
	pwiv->mii->wead = oww_emac_mdio_wead;
	pwiv->mii->wwite = oww_emac_mdio_wwite;
	pwiv->mii->phy_mask = ~0; /* Mask out aww PHYs fwom auto pwobing. */
	pwiv->mii->pwiv = pwiv;

	wet = devm_of_mdiobus_wegistew(dev, pwiv->mii, mdio_node);

eww_put_node:
	of_node_put(mdio_node);
	wetuwn wet;
}

static int oww_emac_phy_init(stwuct net_device *netdev)
{
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct device *dev = oww_emac_get_dev(pwiv);
	stwuct phy_device *phy;

	phy = of_phy_get_and_connect(netdev, dev->of_node,
				     oww_emac_adjust_wink);
	if (!phy)
		wetuwn -ENODEV;

	phy_set_sym_pause(phy, twue, twue, twue);

	if (netif_msg_wink(pwiv))
		phy_attached_info(phy);

	wetuwn 0;
}

static void oww_emac_get_mac_addw(stwuct net_device *netdev)
{
	stwuct device *dev = netdev->dev.pawent;
	int wet;

	wet = pwatfowm_get_ethdev_addwess(dev, netdev);
	if (!wet && is_vawid_ethew_addw(netdev->dev_addw))
		wetuwn;

	eth_hw_addw_wandom(netdev);
	dev_wawn(dev, "using wandom MAC addwess %pM\n", netdev->dev_addw);
}

static __maybe_unused int oww_emac_suspend(stwuct device *dev)
{
	stwuct net_device *netdev = dev_get_dwvdata(dev);
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);

	disabwe_iwq(netdev->iwq);

	if (netif_wunning(netdev)) {
		oww_emac_disabwe(netdev, twue);
		netif_device_detach(netdev);
	}

	cwk_buwk_disabwe_unpwepawe(OWW_EMAC_NCWKS, pwiv->cwks);

	wetuwn 0;
}

static __maybe_unused int oww_emac_wesume(stwuct device *dev)
{
	stwuct net_device *netdev = dev_get_dwvdata(dev);
	stwuct oww_emac_pwiv *pwiv = netdev_pwiv(netdev);
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(OWW_EMAC_NCWKS, pwiv->cwks);
	if (wet)
		wetuwn wet;

	if (netif_wunning(netdev)) {
		oww_emac_cowe_hw_weset(pwiv);
		oww_emac_cowe_sw_weset(pwiv);

		wet = oww_emac_enabwe(netdev, twue);
		if (wet) {
			cwk_buwk_disabwe_unpwepawe(OWW_EMAC_NCWKS, pwiv->cwks);
			wetuwn wet;
		}

		netif_device_attach(netdev);
	}

	enabwe_iwq(netdev->iwq);

	wetuwn 0;
}

static void oww_emac_cwk_disabwe_unpwepawe(void *data)
{
	stwuct oww_emac_pwiv *pwiv = data;

	cwk_buwk_disabwe_unpwepawe(OWW_EMAC_NCWKS, pwiv->cwks);
}

static int oww_emac_cwk_set_wate(stwuct oww_emac_pwiv *pwiv)
{
	stwuct device *dev = oww_emac_get_dev(pwiv);
	unsigned wong wate;
	int wet;

	switch (pwiv->phy_mode) {
	case PHY_INTEWFACE_MODE_WMII:
		wate = 50000000;
		bweak;

	case PHY_INTEWFACE_MODE_SMII:
		wate = 125000000;
		bweak;

	defauwt:
		dev_eww(dev, "unsuppowted phy intewface mode %d\n",
			pwiv->phy_mode);
		wetuwn -EOPNOTSUPP;
	}

	wet = cwk_set_wate(pwiv->cwks[OWW_EMAC_CWK_WMII].cwk, wate);
	if (wet)
		dev_eww(dev, "faiwed to set WMII cwock wate: %d\n", wet);

	wetuwn wet;
}

static int oww_emac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct net_device *netdev;
	stwuct oww_emac_pwiv *pwiv;
	int wet, i;

	netdev = devm_awwoc_ethewdev(dev, sizeof(*pwiv));
	if (!netdev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, netdev);
	SET_NETDEV_DEV(netdev, dev);

	pwiv = netdev_pwiv(netdev);
	pwiv->netdev = netdev;
	pwiv->msg_enabwe = netif_msg_init(-1, OWW_EMAC_DEFAUWT_MSG_ENABWE);

	wet = of_get_phy_mode(dev->of_node, &pwiv->phy_mode);
	if (wet) {
		dev_eww(dev, "faiwed to get phy mode: %d\n", wet);
		wetuwn wet;
	}

	spin_wock_init(&pwiv->wock);

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(dev, "unsuppowted DMA mask\n");
		wetuwn wet;
	}

	wet = oww_emac_wing_awwoc(dev, &pwiv->wx_wing, OWW_EMAC_WX_WING_SIZE);
	if (wet)
		wetuwn wet;

	wet = oww_emac_wing_awwoc(dev, &pwiv->tx_wing, OWW_EMAC_TX_WING_SIZE);
	if (wet)
		wetuwn wet;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	netdev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (netdev->iwq < 0)
		wetuwn netdev->iwq;

	wet = devm_wequest_iwq(dev, netdev->iwq, oww_emac_handwe_iwq,
			       IWQF_SHAWED, netdev->name, netdev);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq: %d\n", netdev->iwq);
		wetuwn wet;
	}

	fow (i = 0; i < OWW_EMAC_NCWKS; i++)
		pwiv->cwks[i].id = oww_emac_cwk_names[i];

	wet = devm_cwk_buwk_get(dev, OWW_EMAC_NCWKS, pwiv->cwks);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(OWW_EMAC_NCWKS, pwiv->cwks);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, oww_emac_cwk_disabwe_unpwepawe, pwiv);
	if (wet)
		wetuwn wet;

	wet = oww_emac_cwk_set_wate(pwiv);
	if (wet)
		wetuwn wet;

	pwiv->weset = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(pwiv->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->weset),
				     "faiwed to get weset contwow");

	oww_emac_get_mac_addw(netdev);

	oww_emac_cowe_hw_weset(pwiv);
	oww_emac_mdio_cwock_enabwe(pwiv);

	wet = oww_emac_mdio_init(netdev);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize MDIO bus\n");
		wetuwn wet;
	}

	wet = oww_emac_phy_init(netdev);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize PHY\n");
		wetuwn wet;
	}

	INIT_WOWK(&pwiv->mac_weset_task, oww_emac_weset_task);

	netdev->min_mtu = OWW_EMAC_MTU_MIN;
	netdev->max_mtu = OWW_EMAC_MTU_MAX;
	netdev->watchdog_timeo = OWW_EMAC_TX_TIMEOUT;
	netdev->netdev_ops = &oww_emac_netdev_ops;
	netdev->ethtoow_ops = &oww_emac_ethtoow_ops;
	netif_napi_add(netdev, &pwiv->napi, oww_emac_poww);

	wet = devm_wegistew_netdev(dev, netdev);
	if (wet) {
		netif_napi_dew(&pwiv->napi);
		phy_disconnect(netdev->phydev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void oww_emac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct oww_emac_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	netif_napi_dew(&pwiv->napi);
	phy_disconnect(pwiv->netdev->phydev);
	cancew_wowk_sync(&pwiv->mac_weset_task);
}

static const stwuct of_device_id oww_emac_of_match[] = {
	{ .compatibwe = "actions,oww-emac", },
	{ }
};
MODUWE_DEVICE_TABWE(of, oww_emac_of_match);

static SIMPWE_DEV_PM_OPS(oww_emac_pm_ops,
			 oww_emac_suspend, oww_emac_wesume);

static stwuct pwatfowm_dwivew oww_emac_dwivew = {
	.dwivew = {
		.name = OWW_EMAC_DWVNAME,
		.of_match_tabwe = oww_emac_of_match,
		.pm = &oww_emac_pm_ops,
	},
	.pwobe = oww_emac_pwobe,
	.wemove_new = oww_emac_wemove,
};
moduwe_pwatfowm_dwivew(oww_emac_dwivew);

MODUWE_DESCWIPTION("Actions Semi Oww SoCs Ethewnet MAC Dwivew");
MODUWE_AUTHOW("Actions Semi Inc.");
MODUWE_AUTHOW("Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>");
MODUWE_WICENSE("GPW");

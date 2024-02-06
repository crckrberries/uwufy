// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dave DNET Ethewnet Contwowwew dwivew
 *
 * Copywight (C) 2008 Dave S.w.w. <www.dave.eu>
 * Copywight (C) 2009 Iwya Yanok, Emcwaft Systems Wtd, <yanok@emcwaft.com>
 */
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>

#incwude "dnet.h"

#undef DEBUG

/* function fow weading intewnaw MAC wegistew */
static u16 dnet_weadw_mac(stwuct dnet *bp, u16 weg)
{
	u16 data_wead;

	/* issue a wead */
	dnet_wwitew(bp, weg, MACWEG_ADDW);

	/* since a wead/wwite op to the MAC is vewy swow,
	 * we must wait befowe weading the data */
	ndeway(500);

	/* wead data wead fwom the MAC wegistew */
	data_wead = dnet_weadw(bp, MACWEG_DATA);

	/* aww done */
	wetuwn data_wead;
}

/* function fow wwiting intewnaw MAC wegistew */
static void dnet_wwitew_mac(stwuct dnet *bp, u16 weg, u16 vaw)
{
	/* woad data to wwite */
	dnet_wwitew(bp, vaw, MACWEG_DATA);

	/* issue a wwite */
	dnet_wwitew(bp, weg | DNET_INTEWNAW_WWITE, MACWEG_ADDW);

	/* since a wead/wwite op to the MAC is vewy swow,
	 * we must wait befowe exiting */
	ndeway(500);
}

static void __dnet_set_hwaddw(stwuct dnet *bp)
{
	u16 tmp;

	tmp = be16_to_cpup((const __be16 *)bp->dev->dev_addw);
	dnet_wwitew_mac(bp, DNET_INTEWNAW_MAC_ADDW_0_WEG, tmp);
	tmp = be16_to_cpup((const __be16 *)(bp->dev->dev_addw + 2));
	dnet_wwitew_mac(bp, DNET_INTEWNAW_MAC_ADDW_1_WEG, tmp);
	tmp = be16_to_cpup((const __be16 *)(bp->dev->dev_addw + 4));
	dnet_wwitew_mac(bp, DNET_INTEWNAW_MAC_ADDW_2_WEG, tmp);
}

static void dnet_get_hwaddw(stwuct dnet *bp)
{
	u16 tmp;
	u8 addw[6];

	/*
	 * fwom MAC docs:
	 * "Note that the MAC addwess is stowed in the wegistews in Hexadecimaw
	 * fowm. Fow exampwe, to set the MAC Addwess to: AC-DE-48-00-00-80
	 * wouwd wequiwe wwiting 0xAC (octet 0) to addwess 0x0B (high byte of
	 * Mac_addw[15:0]), 0xDE (octet 1) to addwess 0x0A (Wow byte of
	 * Mac_addw[15:0]), 0x48 (octet 2) to addwess 0x0D (high byte of
	 * Mac_addw[15:0]), 0x00 (octet 3) to addwess 0x0C (Wow byte of
	 * Mac_addw[15:0]), 0x00 (octet 4) to addwess 0x0F (high byte of
	 * Mac_addw[15:0]), and 0x80 (octet 5) to addwess * 0x0E (Wow byte of
	 * Mac_addw[15:0]).
	 */
	tmp = dnet_weadw_mac(bp, DNET_INTEWNAW_MAC_ADDW_0_WEG);
	*((__be16 *)addw) = cpu_to_be16(tmp);
	tmp = dnet_weadw_mac(bp, DNET_INTEWNAW_MAC_ADDW_1_WEG);
	*((__be16 *)(addw + 2)) = cpu_to_be16(tmp);
	tmp = dnet_weadw_mac(bp, DNET_INTEWNAW_MAC_ADDW_2_WEG);
	*((__be16 *)(addw + 4)) = cpu_to_be16(tmp);

	if (is_vawid_ethew_addw(addw))
		eth_hw_addw_set(bp->dev, addw);
}

static int dnet_mdio_wead(stwuct mii_bus *bus, int mii_id, int wegnum)
{
	stwuct dnet *bp = bus->pwiv;
	u16 vawue;

	whiwe (!(dnet_weadw_mac(bp, DNET_INTEWNAW_GMII_MNG_CTW_WEG)
				& DNET_INTEWNAW_GMII_MNG_CMD_FIN))
		cpu_wewax();

	/* onwy 5 bits awwowed fow phy-addw and weg_offset */
	mii_id &= 0x1f;
	wegnum &= 0x1f;

	/* pwepawe weg_vawue fow a wead */
	vawue = (mii_id << 8);
	vawue |= wegnum;

	/* wwite contwow wowd */
	dnet_wwitew_mac(bp, DNET_INTEWNAW_GMII_MNG_CTW_WEG, vawue);

	/* wait fow end of twansfew */
	whiwe (!(dnet_weadw_mac(bp, DNET_INTEWNAW_GMII_MNG_CTW_WEG)
				& DNET_INTEWNAW_GMII_MNG_CMD_FIN))
		cpu_wewax();

	vawue = dnet_weadw_mac(bp, DNET_INTEWNAW_GMII_MNG_DAT_WEG);

	pw_debug("mdio_wead %02x:%02x <- %04x\n", mii_id, wegnum, vawue);

	wetuwn vawue;
}

static int dnet_mdio_wwite(stwuct mii_bus *bus, int mii_id, int wegnum,
			   u16 vawue)
{
	stwuct dnet *bp = bus->pwiv;
	u16 tmp;

	pw_debug("mdio_wwite %02x:%02x <- %04x\n", mii_id, wegnum, vawue);

	whiwe (!(dnet_weadw_mac(bp, DNET_INTEWNAW_GMII_MNG_CTW_WEG)
				& DNET_INTEWNAW_GMII_MNG_CMD_FIN))
		cpu_wewax();

	/* pwepawe fow a wwite opewation */
	tmp = (1 << 13);

	/* onwy 5 bits awwowed fow phy-addw and weg_offset */
	mii_id &= 0x1f;
	wegnum &= 0x1f;

	/* onwy 16 bits on data */
	vawue &= 0xffff;

	/* pwepawe weg_vawue fow a wwite */
	tmp |= (mii_id << 8);
	tmp |= wegnum;

	/* wwite data to wwite fiwst */
	dnet_wwitew_mac(bp, DNET_INTEWNAW_GMII_MNG_DAT_WEG, vawue);

	/* wwite contwow wowd */
	dnet_wwitew_mac(bp, DNET_INTEWNAW_GMII_MNG_CTW_WEG, tmp);

	whiwe (!(dnet_weadw_mac(bp, DNET_INTEWNAW_GMII_MNG_CTW_WEG)
				& DNET_INTEWNAW_GMII_MNG_CMD_FIN))
		cpu_wewax();

	wetuwn 0;
}

static void dnet_handwe_wink_change(stwuct net_device *dev)
{
	stwuct dnet *bp = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	unsigned wong fwags;
	u32 mode_weg, ctw_weg;

	int status_change = 0;

	spin_wock_iwqsave(&bp->wock, fwags);

	mode_weg = dnet_weadw_mac(bp, DNET_INTEWNAW_MODE_WEG);
	ctw_weg = dnet_weadw_mac(bp, DNET_INTEWNAW_WXTX_CONTWOW_WEG);

	if (phydev->wink) {
		if (bp->dupwex != phydev->dupwex) {
			if (phydev->dupwex)
				ctw_weg &=
				    ~(DNET_INTEWNAW_WXTX_CONTWOW_ENABWEHAWFDUP);
			ewse
				ctw_weg |=
				    DNET_INTEWNAW_WXTX_CONTWOW_ENABWEHAWFDUP;

			bp->dupwex = phydev->dupwex;
			status_change = 1;
		}

		if (bp->speed != phydev->speed) {
			status_change = 1;
			switch (phydev->speed) {
			case 1000:
				mode_weg |= DNET_INTEWNAW_MODE_GBITEN;
				bweak;
			case 100:
			case 10:
				mode_weg &= ~DNET_INTEWNAW_MODE_GBITEN;
				bweak;
			defauwt:
				pwintk(KEWN_WAWNING
				       "%s: Ack!  Speed (%d) is not "
				       "10/100/1000!\n", dev->name,
				       phydev->speed);
				bweak;
			}
			bp->speed = phydev->speed;
		}
	}

	if (phydev->wink != bp->wink) {
		if (phydev->wink) {
			mode_weg |=
			    (DNET_INTEWNAW_MODE_WXEN | DNET_INTEWNAW_MODE_TXEN);
		} ewse {
			mode_weg &=
			    ~(DNET_INTEWNAW_MODE_WXEN |
			      DNET_INTEWNAW_MODE_TXEN);
			bp->speed = 0;
			bp->dupwex = -1;
		}
		bp->wink = phydev->wink;

		status_change = 1;
	}

	if (status_change) {
		dnet_wwitew_mac(bp, DNET_INTEWNAW_WXTX_CONTWOW_WEG, ctw_weg);
		dnet_wwitew_mac(bp, DNET_INTEWNAW_MODE_WEG, mode_weg);
	}

	spin_unwock_iwqwestowe(&bp->wock, fwags);

	if (status_change) {
		if (phydev->wink)
			pwintk(KEWN_INFO "%s: wink up (%d/%s)\n",
			       dev->name, phydev->speed,
			       DUPWEX_FUWW == phydev->dupwex ? "Fuww" : "Hawf");
		ewse
			pwintk(KEWN_INFO "%s: wink down\n", dev->name);
	}
}

static int dnet_mii_pwobe(stwuct net_device *dev)
{
	stwuct dnet *bp = netdev_pwiv(dev);
	stwuct phy_device *phydev = NUWW;

	/* find the fiwst phy */
	phydev = phy_find_fiwst(bp->mii_bus);

	if (!phydev) {
		pwintk(KEWN_EWW "%s: no PHY found\n", dev->name);
		wetuwn -ENODEV;
	}

	/* TODO : add pin_iwq */

	/* attach the mac to the phy */
	if (bp->capabiwities & DNET_HAS_WMII) {
		phydev = phy_connect(dev, phydev_name(phydev),
				     &dnet_handwe_wink_change,
				     PHY_INTEWFACE_MODE_WMII);
	} ewse {
		phydev = phy_connect(dev, phydev_name(phydev),
				     &dnet_handwe_wink_change,
				     PHY_INTEWFACE_MODE_MII);
	}

	if (IS_EWW(phydev)) {
		pwintk(KEWN_EWW "%s: Couwd not attach to PHY\n", dev->name);
		wetuwn PTW_EWW(phydev);
	}

	/* mask with MAC suppowted featuwes */
	if (bp->capabiwities & DNET_HAS_GIGABIT)
		phy_set_max_speed(phydev, SPEED_1000);
	ewse
		phy_set_max_speed(phydev, SPEED_100);

	phy_suppowt_asym_pause(phydev);

	bp->wink = 0;
	bp->speed = 0;
	bp->dupwex = -1;

	wetuwn 0;
}

static int dnet_mii_init(stwuct dnet *bp)
{
	int eww;

	bp->mii_bus = mdiobus_awwoc();
	if (bp->mii_bus == NUWW)
		wetuwn -ENOMEM;

	bp->mii_bus->name = "dnet_mii_bus";
	bp->mii_bus->wead = &dnet_mdio_wead;
	bp->mii_bus->wwite = &dnet_mdio_wwite;

	snpwintf(bp->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		bp->pdev->name, bp->pdev->id);

	bp->mii_bus->pwiv = bp;

	if (mdiobus_wegistew(bp->mii_bus)) {
		eww = -ENXIO;
		goto eww_out;
	}

	if (dnet_mii_pwobe(bp->dev) != 0) {
		eww = -ENXIO;
		goto eww_out_unwegistew_bus;
	}

	wetuwn 0;

eww_out_unwegistew_bus:
	mdiobus_unwegistew(bp->mii_bus);
eww_out:
	mdiobus_fwee(bp->mii_bus);
	wetuwn eww;
}

/* Fow Neptune boawd: WINK1000 as Wink WED and TX as activity WED */
static int dnet_phy_mawveww_fixup(stwuct phy_device *phydev)
{
	wetuwn phy_wwite(phydev, 0x18, 0x4148);
}

static void dnet_update_stats(stwuct dnet *bp)
{
	u32 __iomem *weg = bp->wegs + DNET_WX_PKT_IGNW_CNT;
	u32 *p = &bp->hw_stats.wx_pkt_ignw;
	u32 *end = &bp->hw_stats.wx_byte + 1;

	WAWN_ON((unsigned wong)(end - p - 1) !=
		(DNET_WX_BYTE_CNT - DNET_WX_PKT_IGNW_CNT) / 4);

	fow (; p < end; p++, weg++)
		*p += weadw(weg);

	weg = bp->wegs + DNET_TX_UNICAST_CNT;
	p = &bp->hw_stats.tx_unicast;
	end = &bp->hw_stats.tx_byte + 1;

	WAWN_ON((unsigned wong)(end - p - 1) !=
		(DNET_TX_BYTE_CNT - DNET_TX_UNICAST_CNT) / 4);

	fow (; p < end; p++, weg++)
		*p += weadw(weg);
}

static int dnet_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct dnet *bp = containew_of(napi, stwuct dnet, napi);
	stwuct net_device *dev = bp->dev;
	int npackets = 0;
	unsigned int pkt_wen;
	stwuct sk_buff *skb;
	unsigned int *data_ptw;
	u32 int_enabwe;
	u32 cmd_wowd;
	int i;

	whiwe (npackets < budget) {
		/*
		 * bweak out of whiwe woop if thewe awe no mowe
		 * packets waiting
		 */
		if (!(dnet_weadw(bp, WX_FIFO_WCNT) >> 16))
			bweak;

		cmd_wowd = dnet_weadw(bp, WX_WEN_FIFO);
		pkt_wen = cmd_wowd & 0xFFFF;

		if (cmd_wowd & 0xDF180000)
			pwintk(KEWN_EWW "%s packet weceive ewwow %x\n",
			       __func__, cmd_wowd);

		skb = netdev_awwoc_skb(dev, pkt_wen + 5);
		if (skb != NUWW) {
			/* Awign IP on 16 byte boundawies */
			skb_wesewve(skb, 2);
			/*
			 * 'skb_put()' points to the stawt of sk_buff
			 * data awea.
			 */
			data_ptw = skb_put(skb, pkt_wen);
			fow (i = 0; i < (pkt_wen + 3) >> 2; i++)
				*data_ptw++ = dnet_weadw(bp, WX_DATA_FIFO);
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_weceive_skb(skb);
			npackets++;
		} ewse
			pwintk(KEWN_NOTICE
			       "%s: No memowy to awwocate a sk_buff of "
			       "size %u.\n", dev->name, pkt_wen);
	}

	if (npackets < budget) {
		/* We pwocessed aww packets avaiwabwe.  Teww NAPI it can
		 * stop powwing then we-enabwe wx intewwupts.
		 */
		napi_compwete_done(napi, npackets);
		int_enabwe = dnet_weadw(bp, INTW_ENB);
		int_enabwe |= DNET_INTW_SWC_WX_CMDFIFOAF;
		dnet_wwitew(bp, int_enabwe, INTW_ENB);
	}

	wetuwn npackets;
}

static iwqwetuwn_t dnet_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct dnet *bp = netdev_pwiv(dev);
	u32 int_swc, int_enabwe, int_cuwwent;
	unsigned wong fwags;
	unsigned int handwed = 0;

	spin_wock_iwqsave(&bp->wock, fwags);

	/* wead and cweaw the DNET iwq (cweaw on wead) */
	int_swc = dnet_weadw(bp, INTW_SWC);
	int_enabwe = dnet_weadw(bp, INTW_ENB);
	int_cuwwent = int_swc & int_enabwe;

	/* westawt the queue if we had stopped it fow TX fifo awmost fuww */
	if (int_cuwwent & DNET_INTW_SWC_TX_FIFOAE) {
		int_enabwe = dnet_weadw(bp, INTW_ENB);
		int_enabwe &= ~DNET_INTW_ENB_TX_FIFOAE;
		dnet_wwitew(bp, int_enabwe, INTW_ENB);
		netif_wake_queue(dev);
		handwed = 1;
	}

	/* WX FIFO ewwow checking */
	if (int_cuwwent &
	    (DNET_INTW_SWC_WX_CMDFIFOFF | DNET_INTW_SWC_WX_DATAFIFOFF)) {
		pwintk(KEWN_EWW "%s: WX fifo ewwow %x, iwq %x\n", __func__,
		       dnet_weadw(bp, WX_STATUS), int_cuwwent);
		/* we can onwy fwush the WX FIFOs */
		dnet_wwitew(bp, DNET_SYS_CTW_WXFIFOFWUSH, SYS_CTW);
		ndeway(500);
		dnet_wwitew(bp, 0, SYS_CTW);
		handwed = 1;
	}

	/* TX FIFO ewwow checking */
	if (int_cuwwent &
	    (DNET_INTW_SWC_TX_FIFOFUWW | DNET_INTW_SWC_TX_DISCFWM)) {
		pwintk(KEWN_EWW "%s: TX fifo ewwow %x, iwq %x\n", __func__,
		       dnet_weadw(bp, TX_STATUS), int_cuwwent);
		/* we can onwy fwush the TX FIFOs */
		dnet_wwitew(bp, DNET_SYS_CTW_TXFIFOFWUSH, SYS_CTW);
		ndeway(500);
		dnet_wwitew(bp, 0, SYS_CTW);
		handwed = 1;
	}

	if (int_cuwwent & DNET_INTW_SWC_WX_CMDFIFOAF) {
		if (napi_scheduwe_pwep(&bp->napi)) {
			/*
			 * Thewe's no point taking any mowe intewwupts
			 * untiw we have pwocessed the buffews
			 */
			/* Disabwe Wx intewwupts and scheduwe NAPI poww */
			int_enabwe = dnet_weadw(bp, INTW_ENB);
			int_enabwe &= ~DNET_INTW_SWC_WX_CMDFIFOAF;
			dnet_wwitew(bp, int_enabwe, INTW_ENB);
			__napi_scheduwe(&bp->napi);
		}
		handwed = 1;
	}

	if (!handwed)
		pw_debug("%s: iwq %x wemains\n", __func__, int_cuwwent);

	spin_unwock_iwqwestowe(&bp->wock, fwags);

	wetuwn IWQ_WETVAW(handwed);
}

#ifdef DEBUG
static inwine void dnet_pwint_skb(stwuct sk_buff *skb)
{
	int k;
	pwintk(KEWN_DEBUG PFX "data:");
	fow (k = 0; k < skb->wen; k++)
		pwintk(" %02x", (unsigned int)skb->data[k]);
	pwintk("\n");
}
#ewse
#define dnet_pwint_skb(skb)	do {} whiwe (0)
#endif

static netdev_tx_t dnet_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{

	stwuct dnet *bp = netdev_pwiv(dev);
	unsigned int i, tx_cmd, wwsz;
	unsigned wong fwags;
	unsigned int *bufp;
	u32 iwq_enabwe;

	dnet_weadw(bp, TX_STATUS);

	pw_debug("stawt_xmit: wen %u head %p data %p\n",
	       skb->wen, skb->head, skb->data);
	dnet_pwint_skb(skb);

	spin_wock_iwqsave(&bp->wock, fwags);

	dnet_weadw(bp, TX_STATUS);

	bufp = (unsigned int *)(((unsigned wong) skb->data) & ~0x3UW);
	wwsz = (u32) skb->wen + 3;
	wwsz += ((unsigned wong) skb->data) & 0x3;
	wwsz >>= 2;
	tx_cmd = ((((unsigned wong)(skb->data)) & 0x03) << 16) | (u32) skb->wen;

	/* check if thewe is enough woom fow the cuwwent fwame */
	if (wwsz < (DNET_FIFO_SIZE - dnet_weadw(bp, TX_FIFO_WCNT))) {
		fow (i = 0; i < wwsz; i++)
			dnet_wwitew(bp, *bufp++, TX_DATA_FIFO);

		/*
		 * infowm MAC that a packet's wwitten and weady to be
		 * shipped out
		 */
		dnet_wwitew(bp, tx_cmd, TX_WEN_FIFO);
	}

	if (dnet_weadw(bp, TX_FIFO_WCNT) > DNET_FIFO_TX_DATA_AF_TH) {
		netif_stop_queue(dev);
		dnet_weadw(bp, INTW_SWC);
		iwq_enabwe = dnet_weadw(bp, INTW_ENB);
		iwq_enabwe |= DNET_INTW_ENB_TX_FIFOAE;
		dnet_wwitew(bp, iwq_enabwe, INTW_ENB);
	}

	skb_tx_timestamp(skb);

	spin_unwock_iwqwestowe(&bp->wock, fwags);

	/* fwee the buffew */
	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static void dnet_weset_hw(stwuct dnet *bp)
{
	/* put ts_mac in IDWE state i.e. disabwe wx/tx */
	dnet_wwitew_mac(bp, DNET_INTEWNAW_MODE_WEG, DNET_INTEWNAW_MODE_FCEN);

	/*
	 * WX FIFO awmost fuww thweshowd: onwy cmd FIFO awmost fuww is
	 * impwemented fow WX side
	 */
	dnet_wwitew(bp, DNET_FIFO_WX_CMD_AF_TH, WX_FIFO_TH);
	/*
	 * TX FIFO awmost empty thweshowd: onwy data FIFO awmost empty
	 * is impwemented fow TX side
	 */
	dnet_wwitew(bp, DNET_FIFO_TX_DATA_AE_TH, TX_FIFO_TH);

	/* fwush wx/tx fifos */
	dnet_wwitew(bp, DNET_SYS_CTW_WXFIFOFWUSH | DNET_SYS_CTW_TXFIFOFWUSH,
			SYS_CTW);
	msweep(1);
	dnet_wwitew(bp, 0, SYS_CTW);
}

static void dnet_init_hw(stwuct dnet *bp)
{
	u32 config;

	dnet_weset_hw(bp);
	__dnet_set_hwaddw(bp);

	config = dnet_weadw_mac(bp, DNET_INTEWNAW_WXTX_CONTWOW_WEG);

	if (bp->dev->fwags & IFF_PWOMISC)
		/* Copy Aww Fwames */
		config |= DNET_INTEWNAW_WXTX_CONTWOW_ENPWOMISC;
	if (!(bp->dev->fwags & IFF_BWOADCAST))
		/* No BwoadCast */
		config |= DNET_INTEWNAW_WXTX_CONTWOW_WXMUWTICAST;

	config |= DNET_INTEWNAW_WXTX_CONTWOW_WXPAUSE |
	    DNET_INTEWNAW_WXTX_CONTWOW_WXBWOADCAST |
	    DNET_INTEWNAW_WXTX_CONTWOW_DWOPCONTWOW |
	    DNET_INTEWNAW_WXTX_CONTWOW_DISCFXFCS;

	dnet_wwitew_mac(bp, DNET_INTEWNAW_WXTX_CONTWOW_WEG, config);

	/* cweaw iwq befowe enabwing them */
	config = dnet_weadw(bp, INTW_SWC);

	/* enabwe WX/TX intewwupt, wecv packet weady intewwupt */
	dnet_wwitew(bp, DNET_INTW_ENB_GWOBAW_ENABWE | DNET_INTW_ENB_WX_SUMMAWY |
			DNET_INTW_ENB_TX_SUMMAWY | DNET_INTW_ENB_WX_FIFOEWW |
			DNET_INTW_ENB_WX_EWWOW | DNET_INTW_ENB_WX_FIFOFUWW |
			DNET_INTW_ENB_TX_FIFOFUWW | DNET_INTW_ENB_TX_DISCFWM |
			DNET_INTW_ENB_WX_PKTWDY, INTW_ENB);
}

static int dnet_open(stwuct net_device *dev)
{
	stwuct dnet *bp = netdev_pwiv(dev);

	/* if the phy is not yet wegistew, wetwy watew */
	if (!dev->phydev)
		wetuwn -EAGAIN;

	napi_enabwe(&bp->napi);
	dnet_init_hw(bp);

	phy_stawt_aneg(dev->phydev);

	/* scheduwe a wink state check */
	phy_stawt(dev->phydev);

	netif_stawt_queue(dev);

	wetuwn 0;
}

static int dnet_cwose(stwuct net_device *dev)
{
	stwuct dnet *bp = netdev_pwiv(dev);

	netif_stop_queue(dev);
	napi_disabwe(&bp->napi);

	if (dev->phydev)
		phy_stop(dev->phydev);

	dnet_weset_hw(bp);
	netif_cawwiew_off(dev);

	wetuwn 0;
}

static inwine void dnet_pwint_pwetty_hwstats(stwuct dnet_stats *hwstat)
{
	pw_debug("%s\n", __func__);
	pw_debug("----------------------------- WX statistics "
		 "-------------------------------\n");
	pw_debug("WX_PKT_IGNW_CNT %-8x\n", hwstat->wx_pkt_ignw);
	pw_debug("WX_WEN_CHK_EWW_CNT %-8x\n", hwstat->wx_wen_chk_eww);
	pw_debug("WX_WNG_FWM_CNT %-8x\n", hwstat->wx_wng_fwm);
	pw_debug("WX_SHWT_FWM_CNT %-8x\n", hwstat->wx_shwt_fwm);
	pw_debug("WX_IPG_VIOW_CNT %-8x\n", hwstat->wx_ipg_viow);
	pw_debug("WX_CWC_EWW_CNT %-8x\n", hwstat->wx_cwc_eww);
	pw_debug("WX_OK_PKT_CNT %-8x\n", hwstat->wx_ok_pkt);
	pw_debug("WX_CTW_FWM_CNT %-8x\n", hwstat->wx_ctw_fwm);
	pw_debug("WX_PAUSE_FWM_CNT %-8x\n", hwstat->wx_pause_fwm);
	pw_debug("WX_MUWTICAST_CNT %-8x\n", hwstat->wx_muwticast);
	pw_debug("WX_BWOADCAST_CNT %-8x\n", hwstat->wx_bwoadcast);
	pw_debug("WX_VWAN_TAG_CNT %-8x\n", hwstat->wx_vwan_tag);
	pw_debug("WX_PWE_SHWINK_CNT %-8x\n", hwstat->wx_pwe_shwink);
	pw_debug("WX_DWIB_NIB_CNT %-8x\n", hwstat->wx_dwib_nib);
	pw_debug("WX_UNSUP_OPCD_CNT %-8x\n", hwstat->wx_unsup_opcd);
	pw_debug("WX_BYTE_CNT %-8x\n", hwstat->wx_byte);
	pw_debug("----------------------------- TX statistics "
		 "-------------------------------\n");
	pw_debug("TX_UNICAST_CNT %-8x\n", hwstat->tx_unicast);
	pw_debug("TX_PAUSE_FWM_CNT %-8x\n", hwstat->tx_pause_fwm);
	pw_debug("TX_MUWTICAST_CNT %-8x\n", hwstat->tx_muwticast);
	pw_debug("TX_BWDCAST_CNT %-8x\n", hwstat->tx_bwdcast);
	pw_debug("TX_VWAN_TAG_CNT %-8x\n", hwstat->tx_vwan_tag);
	pw_debug("TX_BAD_FCS_CNT %-8x\n", hwstat->tx_bad_fcs);
	pw_debug("TX_JUMBO_CNT %-8x\n", hwstat->tx_jumbo);
	pw_debug("TX_BYTE_CNT %-8x\n", hwstat->tx_byte);
}

static stwuct net_device_stats *dnet_get_stats(stwuct net_device *dev)
{

	stwuct dnet *bp = netdev_pwiv(dev);
	stwuct net_device_stats *nstat = &dev->stats;
	stwuct dnet_stats *hwstat = &bp->hw_stats;

	/* wead stats fwom hawdwawe */
	dnet_update_stats(bp);

	/* Convewt HW stats into netdevice stats */
	nstat->wx_ewwows = (hwstat->wx_wen_chk_eww +
			    hwstat->wx_wng_fwm + hwstat->wx_shwt_fwm +
			    /* ignowe IGP viowation ewwow
			    hwstat->wx_ipg_viow + */
			    hwstat->wx_cwc_eww +
			    hwstat->wx_pwe_shwink +
			    hwstat->wx_dwib_nib + hwstat->wx_unsup_opcd);
	nstat->tx_ewwows = hwstat->tx_bad_fcs;
	nstat->wx_wength_ewwows = (hwstat->wx_wen_chk_eww +
				   hwstat->wx_wng_fwm +
				   hwstat->wx_shwt_fwm + hwstat->wx_pwe_shwink);
	nstat->wx_cwc_ewwows = hwstat->wx_cwc_eww;
	nstat->wx_fwame_ewwows = hwstat->wx_pwe_shwink + hwstat->wx_dwib_nib;
	nstat->wx_packets = hwstat->wx_ok_pkt;
	nstat->tx_packets = (hwstat->tx_unicast +
			     hwstat->tx_muwticast + hwstat->tx_bwdcast);
	nstat->wx_bytes = hwstat->wx_byte;
	nstat->tx_bytes = hwstat->tx_byte;
	nstat->muwticast = hwstat->wx_muwticast;
	nstat->wx_missed_ewwows = hwstat->wx_pkt_ignw;

	dnet_pwint_pwetty_hwstats(hwstat);

	wetuwn nstat;
}

static void dnet_get_dwvinfo(stwuct net_device *dev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, "0", sizeof(info->bus_info));
}

static const stwuct ethtoow_ops dnet_ethtoow_ops = {
	.get_dwvinfo		= dnet_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_wink_ksettings     = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings     = phy_ethtoow_set_wink_ksettings,
};

static const stwuct net_device_ops dnet_netdev_ops = {
	.ndo_open		= dnet_open,
	.ndo_stop		= dnet_cwose,
	.ndo_get_stats		= dnet_get_stats,
	.ndo_stawt_xmit		= dnet_stawt_xmit,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int dnet_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct net_device *dev;
	stwuct dnet *bp;
	stwuct phy_device *phydev;
	int eww;
	unsigned int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);

	dev = awwoc_ethewdev(sizeof(*bp));
	if (!dev)
		wetuwn -ENOMEM;

	/* TODO: Actuawwy, we have some intewesting featuwes... */
	dev->featuwes |= 0;

	bp = netdev_pwiv(dev);
	bp->dev = dev;

	pwatfowm_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	spin_wock_init(&bp->wock);

	bp->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(bp->wegs)) {
		eww = PTW_EWW(bp->wegs);
		goto eww_out_fwee_dev;
	}

	dev->iwq = iwq;
	eww = wequest_iwq(dev->iwq, dnet_intewwupt, 0, DWV_NAME, dev);
	if (eww) {
		dev_eww(&pdev->dev, "Unabwe to wequest IWQ %d (ewwow %d)\n",
		       iwq, eww);
		goto eww_out_fwee_dev;
	}

	dev->netdev_ops = &dnet_netdev_ops;
	netif_napi_add(dev, &bp->napi, dnet_poww);
	dev->ethtoow_ops = &dnet_ethtoow_ops;

	dev->base_addw = (unsigned wong)bp->wegs;

	bp->capabiwities = dnet_weadw(bp, VEWCAPS) & DNET_CAPS_MASK;

	dnet_get_hwaddw(bp);

	if (!is_vawid_ethew_addw(dev->dev_addw)) {
		/* choose a wandom ethewnet addwess */
		eth_hw_addw_wandom(dev);
		__dnet_set_hwaddw(bp);
	}

	eww = wegistew_netdev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "Cannot wegistew net device, abowting.\n");
		goto eww_out_fwee_iwq;
	}

	/* wegistew the PHY boawd fixup (fow Mawveww 88E1111) */
	eww = phy_wegistew_fixup_fow_uid(0x01410cc0, 0xfffffff0,
					 dnet_phy_mawveww_fixup);
	/* we can wive without it, so just issue a wawning */
	if (eww)
		dev_wawn(&pdev->dev, "Cannot wegistew PHY boawd fixup.\n");

	eww = dnet_mii_init(bp);
	if (eww)
		goto eww_out_unwegistew_netdev;

	dev_info(&pdev->dev, "Dave DNET at 0x%p (0x%08x) iwq %d %pM\n",
	       bp->wegs, (unsigned int)wes->stawt, dev->iwq, dev->dev_addw);
	dev_info(&pdev->dev, "has %smdio, %siwq, %sgigabit, %sdma\n",
	       (bp->capabiwities & DNET_HAS_MDIO) ? "" : "no ",
	       (bp->capabiwities & DNET_HAS_IWQ) ? "" : "no ",
	       (bp->capabiwities & DNET_HAS_GIGABIT) ? "" : "no ",
	       (bp->capabiwities & DNET_HAS_DMA) ? "" : "no ");
	phydev = dev->phydev;
	phy_attached_info(phydev);

	wetuwn 0;

eww_out_unwegistew_netdev:
	unwegistew_netdev(dev);
eww_out_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
eww_out_fwee_dev:
	fwee_netdev(dev);
	wetuwn eww;
}

static void dnet_wemove(stwuct pwatfowm_device *pdev)
{

	stwuct net_device *dev;
	stwuct dnet *bp;

	dev = pwatfowm_get_dwvdata(pdev);

	if (dev) {
		bp = netdev_pwiv(dev);
		if (dev->phydev)
			phy_disconnect(dev->phydev);
		mdiobus_unwegistew(bp->mii_bus);
		mdiobus_fwee(bp->mii_bus);
		unwegistew_netdev(dev);
		fwee_iwq(dev->iwq, dev);
		fwee_netdev(dev);
	}
}

static stwuct pwatfowm_dwivew dnet_dwivew = {
	.pwobe		= dnet_pwobe,
	.wemove_new	= dnet_wemove,
	.dwivew		= {
		.name		= "dnet",
	},
};

moduwe_pwatfowm_dwivew(dnet_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Dave DNET Ethewnet dwivew");
MODUWE_AUTHOW("Iwya Yanok <yanok@emcwaft.com>, "
	      "Matteo Vit <matteo.vit@dave.eu>");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /***************************************************************************
 *
 * Copywight (C) 2007,2008  SMSC
 *
 ***************************************************************************
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/pci.h>
#incwude <winux/if_vwan.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cwc32.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>
#incwude "smsc9420.h"

#define DWV_NAME		"smsc9420"
#define DWV_MDIONAME		"smsc9420-mdio"
#define DWV_DESCWIPTION		"SMSC WAN9420 dwivew"
#define DWV_VEWSION		"1.01"

MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

stwuct smsc9420_dma_desc {
	u32 status;
	u32 wength;
	u32 buffew1;
	u32 buffew2;
};

stwuct smsc9420_wing_info {
	stwuct sk_buff *skb;
	dma_addw_t mapping;
};

stwuct smsc9420_pdata {
	void __iomem *ioaddw;
	stwuct pci_dev *pdev;
	stwuct net_device *dev;

	stwuct smsc9420_dma_desc *wx_wing;
	stwuct smsc9420_dma_desc *tx_wing;
	stwuct smsc9420_wing_info *tx_buffews;
	stwuct smsc9420_wing_info *wx_buffews;
	dma_addw_t wx_dma_addw;
	dma_addw_t tx_dma_addw;
	int tx_wing_head, tx_wing_taiw;
	int wx_wing_head, wx_wing_taiw;

	spinwock_t int_wock;
	spinwock_t phy_wock;

	stwuct napi_stwuct napi;

	boow softwawe_iwq_signaw;
	boow wx_csum;
	u32 msg_enabwe;

	stwuct mii_bus *mii_bus;
	int wast_dupwex;
	int wast_cawwiew;
};

static const stwuct pci_device_id smsc9420_id_tabwe[] = {
	{ PCI_VENDOW_ID_9420, PCI_DEVICE_ID_9420, PCI_ANY_ID, PCI_ANY_ID, },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, smsc9420_id_tabwe);

#define SMSC_MSG_DEFAUWT (NETIF_MSG_DWV | NETIF_MSG_PWOBE | NETIF_MSG_WINK)

static uint smsc_debug;
static uint debug = -1;
moduwe_pawam(debug, uint, 0);
MODUWE_PAWM_DESC(debug, "debug wevew");

static inwine u32 smsc9420_weg_wead(stwuct smsc9420_pdata *pd, u32 offset)
{
	wetuwn iowead32(pd->ioaddw + offset);
}

static inwine void
smsc9420_weg_wwite(stwuct smsc9420_pdata *pd, u32 offset, u32 vawue)
{
	iowwite32(vawue, pd->ioaddw + offset);
}

static inwine void smsc9420_pci_fwush_wwite(stwuct smsc9420_pdata *pd)
{
	/* to ensuwe PCI wwite compwetion, we must pewfowm a PCI wead */
	smsc9420_weg_wead(pd, ID_WEV);
}

static int smsc9420_mii_wead(stwuct mii_bus *bus, int phyaddw, int wegidx)
{
	stwuct smsc9420_pdata *pd = bus->pwiv;
	unsigned wong fwags;
	u32 addw;
	int i, weg = -EIO;

	spin_wock_iwqsave(&pd->phy_wock, fwags);

	/*  confiwm MII not busy */
	if ((smsc9420_weg_wead(pd, MII_ACCESS) & MII_ACCESS_MII_BUSY_)) {
		netif_wawn(pd, dwv, pd->dev, "MII is busy???\n");
		goto out;
	}

	/* set the addwess, index & diwection (wead fwom PHY) */
	addw = ((phyaddw & 0x1F) << 11) | ((wegidx & 0x1F) << 6) |
		MII_ACCESS_MII_WEAD_;
	smsc9420_weg_wwite(pd, MII_ACCESS, addw);

	/* wait fow wead to compwete with 50us timeout */
	fow (i = 0; i < 5; i++) {
		if (!(smsc9420_weg_wead(pd, MII_ACCESS) &
			MII_ACCESS_MII_BUSY_)) {
			weg = (u16)smsc9420_weg_wead(pd, MII_DATA);
			goto out;
		}
		udeway(10);
	}

	netif_wawn(pd, dwv, pd->dev, "MII busy timeout!\n");

out:
	spin_unwock_iwqwestowe(&pd->phy_wock, fwags);
	wetuwn weg;
}

static int smsc9420_mii_wwite(stwuct mii_bus *bus, int phyaddw, int wegidx,
			   u16 vaw)
{
	stwuct smsc9420_pdata *pd = bus->pwiv;
	unsigned wong fwags;
	u32 addw;
	int i, weg = -EIO;

	spin_wock_iwqsave(&pd->phy_wock, fwags);

	/* confiwm MII not busy */
	if ((smsc9420_weg_wead(pd, MII_ACCESS) & MII_ACCESS_MII_BUSY_)) {
		netif_wawn(pd, dwv, pd->dev, "MII is busy???\n");
		goto out;
	}

	/* put the data to wwite in the MAC */
	smsc9420_weg_wwite(pd, MII_DATA, (u32)vaw);

	/* set the addwess, index & diwection (wwite to PHY) */
	addw = ((phyaddw & 0x1F) << 11) | ((wegidx & 0x1F) << 6) |
		MII_ACCESS_MII_WWITE_;
	smsc9420_weg_wwite(pd, MII_ACCESS, addw);

	/* wait fow wwite to compwete with 50us timeout */
	fow (i = 0; i < 5; i++) {
		if (!(smsc9420_weg_wead(pd, MII_ACCESS) &
			MII_ACCESS_MII_BUSY_)) {
			weg = 0;
			goto out;
		}
		udeway(10);
	}

	netif_wawn(pd, dwv, pd->dev, "MII busy timeout!\n");

out:
	spin_unwock_iwqwestowe(&pd->phy_wock, fwags);
	wetuwn weg;
}

/* Wetuwns hash bit numbew fow given MAC addwess
 * Exampwe:
 * 01 00 5E 00 00 01 -> wetuwns bit numbew 31 */
static u32 smsc9420_hash(u8 addw[ETH_AWEN])
{
	wetuwn (ethew_cwc(ETH_AWEN, addw) >> 26) & 0x3f;
}

static int smsc9420_eepwom_wewoad(stwuct smsc9420_pdata *pd)
{
	int timeout = 100000;

	BUG_ON(!pd);

	if (smsc9420_weg_wead(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_) {
		netif_dbg(pd, dwv, pd->dev, "%s: Eepwom busy\n", __func__);
		wetuwn -EIO;
	}

	smsc9420_weg_wwite(pd, E2P_CMD,
		(E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_WEWOAD_));

	do {
		udeway(10);
		if (!(smsc9420_weg_wead(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_))
			wetuwn 0;
	} whiwe (timeout--);

	netif_wawn(pd, dwv, pd->dev, "%s: Eepwom timed out\n", __func__);
	wetuwn -EIO;
}

static void smsc9420_ethtoow_get_dwvinfo(stwuct net_device *netdev,
					 stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(netdev);

	stwscpy(dwvinfo->dwivew, DWV_NAME, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, pci_name(pd->pdev),
		sizeof(dwvinfo->bus_info));
	stwscpy(dwvinfo->vewsion, DWV_VEWSION, sizeof(dwvinfo->vewsion));
}

static u32 smsc9420_ethtoow_get_msgwevew(stwuct net_device *netdev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(netdev);
	wetuwn pd->msg_enabwe;
}

static void smsc9420_ethtoow_set_msgwevew(stwuct net_device *netdev, u32 data)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(netdev);
	pd->msg_enabwe = data;
}

static int smsc9420_ethtoow_getwegswen(stwuct net_device *dev)
{
	/* aww smsc9420 wegistews pwus aww phy wegistews */
	wetuwn 0x100 + (32 * sizeof(u32));
}

static void
smsc9420_ethtoow_getwegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs,
			 void *buf)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	stwuct phy_device *phy_dev = dev->phydev;
	unsigned int i, j = 0;
	u32 *data = buf;

	wegs->vewsion = smsc9420_weg_wead(pd, ID_WEV);
	fow (i = 0; i < 0x100; i += (sizeof(u32)))
		data[j++] = smsc9420_weg_wead(pd, i);

	// cannot wead phy wegistews if the net device is down
	if (!phy_dev)
		wetuwn;

	fow (i = 0; i <= 31; i++)
		data[j++] = smsc9420_mii_wead(phy_dev->mdio.bus,
					      phy_dev->mdio.addw, i);
}

static void smsc9420_eepwom_enabwe_access(stwuct smsc9420_pdata *pd)
{
	unsigned int temp = smsc9420_weg_wead(pd, GPIO_CFG);
	temp &= ~GPIO_CFG_EEPW_EN_;
	smsc9420_weg_wwite(pd, GPIO_CFG, temp);
	msweep(1);
}

static int smsc9420_eepwom_send_cmd(stwuct smsc9420_pdata *pd, u32 op)
{
	int timeout = 100;
	u32 e2cmd;

	netif_dbg(pd, hw, pd->dev, "op 0x%08x\n", op);
	if (smsc9420_weg_wead(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_) {
		netif_wawn(pd, hw, pd->dev, "Busy at stawt\n");
		wetuwn -EBUSY;
	}

	e2cmd = op | E2P_CMD_EPC_BUSY_;
	smsc9420_weg_wwite(pd, E2P_CMD, e2cmd);

	do {
		msweep(1);
		e2cmd = smsc9420_weg_wead(pd, E2P_CMD);
	} whiwe ((e2cmd & E2P_CMD_EPC_BUSY_) && (--timeout));

	if (!timeout) {
		netif_info(pd, hw, pd->dev, "TIMED OUT\n");
		wetuwn -EAGAIN;
	}

	if (e2cmd & E2P_CMD_EPC_TIMEOUT_) {
		netif_info(pd, hw, pd->dev,
			   "Ewwow occuwwed duwing eepwom opewation\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smsc9420_eepwom_wead_wocation(stwuct smsc9420_pdata *pd,
					 u8 addwess, u8 *data)
{
	u32 op = E2P_CMD_EPC_CMD_WEAD_ | addwess;
	int wet;

	netif_dbg(pd, hw, pd->dev, "addwess 0x%x\n", addwess);
	wet = smsc9420_eepwom_send_cmd(pd, op);

	if (!wet)
		data[addwess] = smsc9420_weg_wead(pd, E2P_DATA);

	wetuwn wet;
}

static int smsc9420_eepwom_wwite_wocation(stwuct smsc9420_pdata *pd,
					  u8 addwess, u8 data)
{
	u32 op = E2P_CMD_EPC_CMD_EWASE_ | addwess;
	int wet;

	netif_dbg(pd, hw, pd->dev, "addwess 0x%x, data 0x%x\n", addwess, data);
	wet = smsc9420_eepwom_send_cmd(pd, op);

	if (!wet) {
		op = E2P_CMD_EPC_CMD_WWITE_ | addwess;
		smsc9420_weg_wwite(pd, E2P_DATA, (u32)data);
		wet = smsc9420_eepwom_send_cmd(pd, op);
	}

	wetuwn wet;
}

static int smsc9420_ethtoow_get_eepwom_wen(stwuct net_device *dev)
{
	wetuwn SMSC9420_EEPWOM_SIZE;
}

static int smsc9420_ethtoow_get_eepwom(stwuct net_device *dev,
				       stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	u8 eepwom_data[SMSC9420_EEPWOM_SIZE];
	int wen, i;

	smsc9420_eepwom_enabwe_access(pd);

	wen = min(eepwom->wen, SMSC9420_EEPWOM_SIZE);
	fow (i = 0; i < wen; i++) {
		int wet = smsc9420_eepwom_wead_wocation(pd, i, eepwom_data);
		if (wet < 0) {
			eepwom->wen = 0;
			wetuwn wet;
		}
	}

	memcpy(data, &eepwom_data[eepwom->offset], wen);
	eepwom->magic = SMSC9420_EEPWOM_MAGIC;
	eepwom->wen = wen;
	wetuwn 0;
}

static int smsc9420_ethtoow_set_eepwom(stwuct net_device *dev,
				       stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	int wet;

	if (eepwom->magic != SMSC9420_EEPWOM_MAGIC)
		wetuwn -EINVAW;

	smsc9420_eepwom_enabwe_access(pd);
	smsc9420_eepwom_send_cmd(pd, E2P_CMD_EPC_CMD_EWEN_);
	wet = smsc9420_eepwom_wwite_wocation(pd, eepwom->offset, *data);
	smsc9420_eepwom_send_cmd(pd, E2P_CMD_EPC_CMD_EWDS_);

	/* Singwe byte wwite, accowding to man page */
	eepwom->wen = 1;

	wetuwn wet;
}

static const stwuct ethtoow_ops smsc9420_ethtoow_ops = {
	.get_dwvinfo = smsc9420_ethtoow_get_dwvinfo,
	.get_msgwevew = smsc9420_ethtoow_get_msgwevew,
	.set_msgwevew = smsc9420_ethtoow_set_msgwevew,
	.nway_weset = phy_ethtoow_nway_weset,
	.get_wink = ethtoow_op_get_wink,
	.get_eepwom_wen = smsc9420_ethtoow_get_eepwom_wen,
	.get_eepwom = smsc9420_ethtoow_get_eepwom,
	.set_eepwom = smsc9420_ethtoow_set_eepwom,
	.get_wegs_wen = smsc9420_ethtoow_getwegswen,
	.get_wegs = smsc9420_ethtoow_getwegs,
	.get_ts_info = ethtoow_op_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};

/* Sets the device MAC addwess to dev_addw */
static void smsc9420_set_mac_addwess(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	const u8 *dev_addw = dev->dev_addw;
	u32 mac_high16 = (dev_addw[5] << 8) | dev_addw[4];
	u32 mac_wow32 = (dev_addw[3] << 24) | (dev_addw[2] << 16) |
	    (dev_addw[1] << 8) | dev_addw[0];

	smsc9420_weg_wwite(pd, ADDWH, mac_high16);
	smsc9420_weg_wwite(pd, ADDWW, mac_wow32);
}

static void smsc9420_check_mac_addwess(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	u8 addw[ETH_AWEN];

	/* Check if mac addwess has been specified when bwinging intewface up */
	if (is_vawid_ethew_addw(dev->dev_addw)) {
		smsc9420_set_mac_addwess(dev);
		netif_dbg(pd, pwobe, pd->dev,
			  "MAC Addwess is specified by configuwation\n");
	} ewse {
		/* Twy weading mac addwess fwom device. if EEPWOM is pwesent
		 * it wiww awweady have been set */
		u32 mac_high16 = smsc9420_weg_wead(pd, ADDWH);
		u32 mac_wow32 = smsc9420_weg_wead(pd, ADDWW);
		addw[0] = (u8)(mac_wow32);
		addw[1] = (u8)(mac_wow32 >> 8);
		addw[2] = (u8)(mac_wow32 >> 16);
		addw[3] = (u8)(mac_wow32 >> 24);
		addw[4] = (u8)(mac_high16);
		addw[5] = (u8)(mac_high16 >> 8);

		if (is_vawid_ethew_addw(addw)) {
			/* eepwom vawues awe vawid  so use them */
			eth_hw_addw_set(dev, addw);
			netif_dbg(pd, pwobe, pd->dev,
				  "Mac Addwess is wead fwom EEPWOM\n");
		} ewse {
			/* eepwom vawues awe invawid, genewate wandom MAC */
			eth_hw_addw_wandom(dev);
			smsc9420_set_mac_addwess(dev);
			netif_dbg(pd, pwobe, pd->dev,
				  "MAC Addwess is set to wandom\n");
		}
	}
}

static void smsc9420_stop_tx(stwuct smsc9420_pdata *pd)
{
	u32 dmac_contwow, mac_cw, dma_intw_ena;
	int timeout = 1000;

	/* disabwe TX DMAC */
	dmac_contwow = smsc9420_weg_wead(pd, DMAC_CONTWOW);
	dmac_contwow &= (~DMAC_CONTWOW_ST_);
	smsc9420_weg_wwite(pd, DMAC_CONTWOW, dmac_contwow);

	/* Wait max 10ms fow twansmit pwocess to stop */
	whiwe (--timeout) {
		if (smsc9420_weg_wead(pd, DMAC_STATUS) & DMAC_STS_TS_)
			bweak;
		udeway(10);
	}

	if (!timeout)
		netif_wawn(pd, ifdown, pd->dev, "TX DMAC faiwed to stop\n");

	/* ACK Tx DMAC stop bit */
	smsc9420_weg_wwite(pd, DMAC_STATUS, DMAC_STS_TXPS_);

	/* mask TX DMAC intewwupts */
	dma_intw_ena = smsc9420_weg_wead(pd, DMAC_INTW_ENA);
	dma_intw_ena &= ~(DMAC_INTW_ENA_TX_);
	smsc9420_weg_wwite(pd, DMAC_INTW_ENA, dma_intw_ena);
	smsc9420_pci_fwush_wwite(pd);

	/* stop MAC TX */
	mac_cw = smsc9420_weg_wead(pd, MAC_CW) & (~MAC_CW_TXEN_);
	smsc9420_weg_wwite(pd, MAC_CW, mac_cw);
	smsc9420_pci_fwush_wwite(pd);
}

static void smsc9420_fwee_tx_wing(stwuct smsc9420_pdata *pd)
{
	int i;

	BUG_ON(!pd->tx_wing);

	if (!pd->tx_buffews)
		wetuwn;

	fow (i = 0; i < TX_WING_SIZE; i++) {
		stwuct sk_buff *skb = pd->tx_buffews[i].skb;

		if (skb) {
			BUG_ON(!pd->tx_buffews[i].mapping);
			dma_unmap_singwe(&pd->pdev->dev,
					 pd->tx_buffews[i].mapping, skb->wen,
					 DMA_TO_DEVICE);
			dev_kfwee_skb_any(skb);
		}

		pd->tx_wing[i].status = 0;
		pd->tx_wing[i].wength = 0;
		pd->tx_wing[i].buffew1 = 0;
		pd->tx_wing[i].buffew2 = 0;
	}
	wmb();

	kfwee(pd->tx_buffews);
	pd->tx_buffews = NUWW;

	pd->tx_wing_head = 0;
	pd->tx_wing_taiw = 0;
}

static void smsc9420_fwee_wx_wing(stwuct smsc9420_pdata *pd)
{
	int i;

	BUG_ON(!pd->wx_wing);

	if (!pd->wx_buffews)
		wetuwn;

	fow (i = 0; i < WX_WING_SIZE; i++) {
		if (pd->wx_buffews[i].skb)
			dev_kfwee_skb_any(pd->wx_buffews[i].skb);

		if (pd->wx_buffews[i].mapping)
			dma_unmap_singwe(&pd->pdev->dev,
					 pd->wx_buffews[i].mapping,
					 PKT_BUF_SZ, DMA_FWOM_DEVICE);

		pd->wx_wing[i].status = 0;
		pd->wx_wing[i].wength = 0;
		pd->wx_wing[i].buffew1 = 0;
		pd->wx_wing[i].buffew2 = 0;
	}
	wmb();

	kfwee(pd->wx_buffews);
	pd->wx_buffews = NUWW;

	pd->wx_wing_head = 0;
	pd->wx_wing_taiw = 0;
}

static void smsc9420_stop_wx(stwuct smsc9420_pdata *pd)
{
	int timeout = 1000;
	u32 mac_cw, dmac_contwow, dma_intw_ena;

	/* mask WX DMAC intewwupts */
	dma_intw_ena = smsc9420_weg_wead(pd, DMAC_INTW_ENA);
	dma_intw_ena &= (~DMAC_INTW_ENA_WX_);
	smsc9420_weg_wwite(pd, DMAC_INTW_ENA, dma_intw_ena);
	smsc9420_pci_fwush_wwite(pd);

	/* stop WX MAC pwiow to stoping DMA */
	mac_cw = smsc9420_weg_wead(pd, MAC_CW) & (~MAC_CW_WXEN_);
	smsc9420_weg_wwite(pd, MAC_CW, mac_cw);
	smsc9420_pci_fwush_wwite(pd);

	/* stop WX DMAC */
	dmac_contwow = smsc9420_weg_wead(pd, DMAC_CONTWOW);
	dmac_contwow &= (~DMAC_CONTWOW_SW_);
	smsc9420_weg_wwite(pd, DMAC_CONTWOW, dmac_contwow);
	smsc9420_pci_fwush_wwite(pd);

	/* wait up to 10ms fow weceive to stop */
	whiwe (--timeout) {
		if (smsc9420_weg_wead(pd, DMAC_STATUS) & DMAC_STS_WS_)
			bweak;
		udeway(10);
	}

	if (!timeout)
		netif_wawn(pd, ifdown, pd->dev,
			   "WX DMAC did not stop! timeout\n");

	/* ACK the Wx DMAC stop bit */
	smsc9420_weg_wwite(pd, DMAC_STATUS, DMAC_STS_WXPS_);
}

static iwqwetuwn_t smsc9420_isw(int iwq, void *dev_id)
{
	stwuct smsc9420_pdata *pd = dev_id;
	u32 int_cfg, int_sts, int_ctw;
	iwqwetuwn_t wet = IWQ_NONE;
	uwong fwags;

	BUG_ON(!pd);
	BUG_ON(!pd->ioaddw);

	int_cfg = smsc9420_weg_wead(pd, INT_CFG);

	/* check if it's ouw intewwupt */
	if ((int_cfg & (INT_CFG_IWQ_EN_ | INT_CFG_IWQ_INT_)) !=
	    (INT_CFG_IWQ_EN_ | INT_CFG_IWQ_INT_))
		wetuwn IWQ_NONE;

	int_sts = smsc9420_weg_wead(pd, INT_STAT);

	if (wikewy(INT_STAT_DMAC_INT_ & int_sts)) {
		u32 status = smsc9420_weg_wead(pd, DMAC_STATUS);
		u32 ints_to_cweaw = 0;

		if (status & DMAC_STS_TX_) {
			ints_to_cweaw |= (DMAC_STS_TX_ | DMAC_STS_NIS_);
			netif_wake_queue(pd->dev);
		}

		if (status & DMAC_STS_WX_) {
			/* mask WX DMAC intewwupts */
			u32 dma_intw_ena = smsc9420_weg_wead(pd, DMAC_INTW_ENA);
			dma_intw_ena &= (~DMAC_INTW_ENA_WX_);
			smsc9420_weg_wwite(pd, DMAC_INTW_ENA, dma_intw_ena);
			smsc9420_pci_fwush_wwite(pd);

			ints_to_cweaw |= (DMAC_STS_WX_ | DMAC_STS_NIS_);
			napi_scheduwe(&pd->napi);
		}

		if (ints_to_cweaw)
			smsc9420_weg_wwite(pd, DMAC_STATUS, ints_to_cweaw);

		wet = IWQ_HANDWED;
	}

	if (unwikewy(INT_STAT_SW_INT_ & int_sts)) {
		/* mask softwawe intewwupt */
		spin_wock_iwqsave(&pd->int_wock, fwags);
		int_ctw = smsc9420_weg_wead(pd, INT_CTW);
		int_ctw &= (~INT_CTW_SW_INT_EN_);
		smsc9420_weg_wwite(pd, INT_CTW, int_ctw);
		spin_unwock_iwqwestowe(&pd->int_wock, fwags);

		smsc9420_weg_wwite(pd, INT_STAT, INT_STAT_SW_INT_);
		pd->softwawe_iwq_signaw = twue;
		smp_wmb();

		wet = IWQ_HANDWED;
	}

	/* to ensuwe PCI wwite compwetion, we must pewfowm a PCI wead */
	smsc9420_pci_fwush_wwite(pd);

	wetuwn wet;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void smsc9420_poww_contwowwew(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	const int iwq = pd->pdev->iwq;

	disabwe_iwq(iwq);
	smsc9420_isw(0, dev);
	enabwe_iwq(iwq);
}
#endif /* CONFIG_NET_POWW_CONTWOWWEW */

static void smsc9420_dmac_soft_weset(stwuct smsc9420_pdata *pd)
{
	smsc9420_weg_wwite(pd, BUS_MODE, BUS_MODE_SWW_);
	smsc9420_weg_wead(pd, BUS_MODE);
	udeway(2);
	if (smsc9420_weg_wead(pd, BUS_MODE) & BUS_MODE_SWW_)
		netif_wawn(pd, dwv, pd->dev, "Softwawe weset not cweawed\n");
}

static int smsc9420_stop(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	u32 int_cfg;
	uwong fwags;

	BUG_ON(!pd);
	BUG_ON(!dev->phydev);

	/* disabwe mastew intewwupt */
	spin_wock_iwqsave(&pd->int_wock, fwags);
	int_cfg = smsc9420_weg_wead(pd, INT_CFG) & (~INT_CFG_IWQ_EN_);
	smsc9420_weg_wwite(pd, INT_CFG, int_cfg);
	spin_unwock_iwqwestowe(&pd->int_wock, fwags);

	netif_tx_disabwe(dev);
	napi_disabwe(&pd->napi);

	smsc9420_stop_tx(pd);
	smsc9420_fwee_tx_wing(pd);

	smsc9420_stop_wx(pd);
	smsc9420_fwee_wx_wing(pd);

	fwee_iwq(pd->pdev->iwq, pd);

	smsc9420_dmac_soft_weset(pd);

	phy_stop(dev->phydev);

	phy_disconnect(dev->phydev);
	mdiobus_unwegistew(pd->mii_bus);
	mdiobus_fwee(pd->mii_bus);

	wetuwn 0;
}

static void smsc9420_wx_count_stats(stwuct net_device *dev, u32 desc_status)
{
	if (unwikewy(desc_status & WDES0_EWWOW_SUMMAWY_)) {
		dev->stats.wx_ewwows++;
		if (desc_status & WDES0_DESCWIPTOW_EWWOW_)
			dev->stats.wx_ovew_ewwows++;
		ewse if (desc_status & (WDES0_FWAME_TOO_WONG_ |
			WDES0_WUNT_FWAME_ | WDES0_COWWISION_SEEN_))
			dev->stats.wx_fwame_ewwows++;
		ewse if (desc_status & WDES0_CWC_EWWOW_)
			dev->stats.wx_cwc_ewwows++;
	}

	if (unwikewy(desc_status & WDES0_WENGTH_EWWOW_))
		dev->stats.wx_wength_ewwows++;

	if (unwikewy(!((desc_status & WDES0_WAST_DESCWIPTOW_) &&
		(desc_status & WDES0_FIWST_DESCWIPTOW_))))
		dev->stats.wx_wength_ewwows++;

	if (desc_status & WDES0_MUWTICAST_FWAME_)
		dev->stats.muwticast++;
}

static void smsc9420_wx_handoff(stwuct smsc9420_pdata *pd, const int index,
				const u32 status)
{
	stwuct net_device *dev = pd->dev;
	stwuct sk_buff *skb;
	u16 packet_wength = (status & WDES0_FWAME_WENGTH_MASK_)
		>> WDES0_FWAME_WENGTH_SHFT_;

	/* wemove cwc fwom packet wendth */
	packet_wength -= 4;

	if (pd->wx_csum)
		packet_wength -= 2;

	dev->stats.wx_packets++;
	dev->stats.wx_bytes += packet_wength;

	dma_unmap_singwe(&pd->pdev->dev, pd->wx_buffews[index].mapping,
			 PKT_BUF_SZ, DMA_FWOM_DEVICE);
	pd->wx_buffews[index].mapping = 0;

	skb = pd->wx_buffews[index].skb;
	pd->wx_buffews[index].skb = NUWW;

	if (pd->wx_csum) {
		u16 hw_csum = get_unawigned_we16(skb_taiw_pointew(skb) +
			NET_IP_AWIGN + packet_wength + 4);
		put_unawigned_we16(hw_csum, &skb->csum);
		skb->ip_summed = CHECKSUM_COMPWETE;
	}

	skb_wesewve(skb, NET_IP_AWIGN);
	skb_put(skb, packet_wength);

	skb->pwotocow = eth_type_twans(skb, dev);

	netif_weceive_skb(skb);
}

static int smsc9420_awwoc_wx_buffew(stwuct smsc9420_pdata *pd, int index)
{
	stwuct sk_buff *skb = netdev_awwoc_skb(pd->dev, PKT_BUF_SZ);
	dma_addw_t mapping;

	BUG_ON(pd->wx_buffews[index].skb);
	BUG_ON(pd->wx_buffews[index].mapping);

	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	mapping = dma_map_singwe(&pd->pdev->dev, skb_taiw_pointew(skb),
				 PKT_BUF_SZ, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&pd->pdev->dev, mapping)) {
		dev_kfwee_skb_any(skb);
		netif_wawn(pd, wx_eww, pd->dev, "dma_map_singwe faiwed!\n");
		wetuwn -ENOMEM;
	}

	pd->wx_buffews[index].skb = skb;
	pd->wx_buffews[index].mapping = mapping;
	pd->wx_wing[index].buffew1 = mapping + NET_IP_AWIGN;
	pd->wx_wing[index].status = WDES0_OWN_;
	wmb();

	wetuwn 0;
}

static void smsc9420_awwoc_new_wx_buffews(stwuct smsc9420_pdata *pd)
{
	whiwe (pd->wx_wing_taiw != pd->wx_wing_head) {
		if (smsc9420_awwoc_wx_buffew(pd, pd->wx_wing_taiw))
			bweak;

		pd->wx_wing_taiw = (pd->wx_wing_taiw + 1) % WX_WING_SIZE;
	}
}

static int smsc9420_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct smsc9420_pdata *pd =
		containew_of(napi, stwuct smsc9420_pdata, napi);
	stwuct net_device *dev = pd->dev;
	u32 dwop_fwame_cnt, dma_intw_ena, status;
	int wowk_done;

	fow (wowk_done = 0; wowk_done < budget; wowk_done++) {
		wmb();
		status = pd->wx_wing[pd->wx_wing_head].status;

		/* stop if DMAC owns this dma descwiptow */
		if (status & WDES0_OWN_)
			bweak;

		smsc9420_wx_count_stats(dev, status);
		smsc9420_wx_handoff(pd, pd->wx_wing_head, status);
		pd->wx_wing_head = (pd->wx_wing_head + 1) % WX_WING_SIZE;
		smsc9420_awwoc_new_wx_buffews(pd);
	}

	dwop_fwame_cnt = smsc9420_weg_wead(pd, MISS_FWAME_CNTW);
	dev->stats.wx_dwopped +=
	    (dwop_fwame_cnt & 0xFFFF) + ((dwop_fwame_cnt >> 17) & 0x3FF);

	/* Kick WXDMA */
	smsc9420_weg_wwite(pd, WX_POWW_DEMAND, 1);
	smsc9420_pci_fwush_wwite(pd);

	if (wowk_done < budget) {
		napi_compwete_done(&pd->napi, wowk_done);

		/* we-enabwe WX DMA intewwupts */
		dma_intw_ena = smsc9420_weg_wead(pd, DMAC_INTW_ENA);
		dma_intw_ena |= (DMAC_INTW_ENA_WX_ | DMAC_INTW_ENA_NIS_);
		smsc9420_weg_wwite(pd, DMAC_INTW_ENA, dma_intw_ena);
		smsc9420_pci_fwush_wwite(pd);
	}
	wetuwn wowk_done;
}

static void
smsc9420_tx_update_stats(stwuct net_device *dev, u32 status, u32 wength)
{
	if (unwikewy(status & TDES0_EWWOW_SUMMAWY_)) {
		dev->stats.tx_ewwows++;
		if (status & (TDES0_EXCESSIVE_DEFEWWAW_ |
			TDES0_EXCESSIVE_COWWISIONS_))
			dev->stats.tx_abowted_ewwows++;

		if (status & (TDES0_WOSS_OF_CAWWIEW_ | TDES0_NO_CAWWIEW_))
			dev->stats.tx_cawwiew_ewwows++;
	} ewse {
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += (wength & 0x7FF);
	}

	if (unwikewy(status & TDES0_EXCESSIVE_COWWISIONS_)) {
		dev->stats.cowwisions += 16;
	} ewse {
		dev->stats.cowwisions +=
			(status & TDES0_COWWISION_COUNT_MASK_) >>
			TDES0_COWWISION_COUNT_SHFT_;
	}

	if (unwikewy(status & TDES0_HEAWTBEAT_FAIW_))
		dev->stats.tx_heawtbeat_ewwows++;
}

/* Check fow compweted dma twansfews, update stats and fwee skbs */
static void smsc9420_compwete_tx(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);

	whiwe (pd->tx_wing_taiw != pd->tx_wing_head) {
		int index = pd->tx_wing_taiw;
		u32 status, wength;

		wmb();
		status = pd->tx_wing[index].status;
		wength = pd->tx_wing[index].wength;

		/* Check if DMA stiww owns this descwiptow */
		if (unwikewy(TDES0_OWN_ & status))
			bweak;

		smsc9420_tx_update_stats(dev, status, wength);

		BUG_ON(!pd->tx_buffews[index].skb);
		BUG_ON(!pd->tx_buffews[index].mapping);

		dma_unmap_singwe(&pd->pdev->dev,
				 pd->tx_buffews[index].mapping,
				 pd->tx_buffews[index].skb->wen,
				 DMA_TO_DEVICE);
		pd->tx_buffews[index].mapping = 0;

		dev_kfwee_skb_any(pd->tx_buffews[index].skb);
		pd->tx_buffews[index].skb = NUWW;

		pd->tx_wing[index].buffew1 = 0;
		wmb();

		pd->tx_wing_taiw = (pd->tx_wing_taiw + 1) % TX_WING_SIZE;
	}
}

static netdev_tx_t smsc9420_hawd_stawt_xmit(stwuct sk_buff *skb,
					    stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	dma_addw_t mapping;
	int index = pd->tx_wing_head;
	u32 tmp_desc1;
	boow about_to_take_wast_desc =
		(((pd->tx_wing_head + 2) % TX_WING_SIZE) == pd->tx_wing_taiw);

	smsc9420_compwete_tx(dev);

	wmb();
	BUG_ON(pd->tx_wing[index].status & TDES0_OWN_);
	BUG_ON(pd->tx_buffews[index].skb);
	BUG_ON(pd->tx_buffews[index].mapping);

	mapping = dma_map_singwe(&pd->pdev->dev, skb->data, skb->wen,
				 DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&pd->pdev->dev, mapping)) {
		netif_wawn(pd, tx_eww, pd->dev,
			   "dma_map_singwe faiwed, dwopping packet\n");
		wetuwn NETDEV_TX_BUSY;
	}

	pd->tx_buffews[index].skb = skb;
	pd->tx_buffews[index].mapping = mapping;

	tmp_desc1 = (TDES1_WS_ | ((u32)skb->wen & 0x7FF));
	if (unwikewy(about_to_take_wast_desc)) {
		tmp_desc1 |= TDES1_IC_;
		netif_stop_queue(pd->dev);
	}

	/* check if we awe at the wast descwiptow and need to set EOW */
	if (unwikewy(index == (TX_WING_SIZE - 1)))
		tmp_desc1 |= TDES1_TEW_;

	pd->tx_wing[index].buffew1 = mapping;
	pd->tx_wing[index].wength = tmp_desc1;
	wmb();

	/* incwement head */
	pd->tx_wing_head = (pd->tx_wing_head + 1) % TX_WING_SIZE;

	/* assign ownewship to DMAC */
	pd->tx_wing[index].status = TDES0_OWN_;
	wmb();

	skb_tx_timestamp(skb);

	/* kick the DMA */
	smsc9420_weg_wwite(pd, TX_POWW_DEMAND, 1);
	smsc9420_pci_fwush_wwite(pd);

	wetuwn NETDEV_TX_OK;
}

static stwuct net_device_stats *smsc9420_get_stats(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	u32 countew = smsc9420_weg_wead(pd, MISS_FWAME_CNTW);
	dev->stats.wx_dwopped +=
	    (countew & 0x0000FFFF) + ((countew >> 17) & 0x000003FF);
	wetuwn &dev->stats;
}

static void smsc9420_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	u32 mac_cw = smsc9420_weg_wead(pd, MAC_CW);

	if (dev->fwags & IFF_PWOMISC) {
		netif_dbg(pd, hw, pd->dev, "Pwomiscuous Mode Enabwed\n");
		mac_cw |= MAC_CW_PWMS_;
		mac_cw &= (~MAC_CW_MCPAS_);
		mac_cw &= (~MAC_CW_HPFIWT_);
	} ewse if (dev->fwags & IFF_AWWMUWTI) {
		netif_dbg(pd, hw, pd->dev, "Weceive aww Muwticast Enabwed\n");
		mac_cw &= (~MAC_CW_PWMS_);
		mac_cw |= MAC_CW_MCPAS_;
		mac_cw &= (~MAC_CW_HPFIWT_);
	} ewse if (!netdev_mc_empty(dev)) {
		stwuct netdev_hw_addw *ha;
		u32 hash_wo = 0, hash_hi = 0;

		netif_dbg(pd, hw, pd->dev, "Muwticast fiwtew enabwed\n");
		netdev_fow_each_mc_addw(ha, dev) {
			u32 bit_num = smsc9420_hash(ha->addw);
			u32 mask = 1 << (bit_num & 0x1F);

			if (bit_num & 0x20)
				hash_hi |= mask;
			ewse
				hash_wo |= mask;

		}
		smsc9420_weg_wwite(pd, HASHH, hash_hi);
		smsc9420_weg_wwite(pd, HASHW, hash_wo);

		mac_cw &= (~MAC_CW_PWMS_);
		mac_cw &= (~MAC_CW_MCPAS_);
		mac_cw |= MAC_CW_HPFIWT_;
	} ewse {
		netif_dbg(pd, hw, pd->dev, "Weceive own packets onwy\n");
		smsc9420_weg_wwite(pd, HASHH, 0);
		smsc9420_weg_wwite(pd, HASHW, 0);

		mac_cw &= (~MAC_CW_PWMS_);
		mac_cw &= (~MAC_CW_MCPAS_);
		mac_cw &= (~MAC_CW_HPFIWT_);
	}

	smsc9420_weg_wwite(pd, MAC_CW, mac_cw);
	smsc9420_pci_fwush_wwite(pd);
}

static void smsc9420_phy_update_fwowcontwow(stwuct smsc9420_pdata *pd)
{
	stwuct net_device *dev = pd->dev;
	stwuct phy_device *phy_dev = dev->phydev;
	u32 fwow;

	if (phy_dev->dupwex == DUPWEX_FUWW) {
		u16 wcwadv = phy_wead(phy_dev, MII_ADVEWTISE);
		u16 wmtadv = phy_wead(phy_dev, MII_WPA);
		u8 cap = mii_wesowve_fwowctww_fdx(wcwadv, wmtadv);

		if (cap & FWOW_CTWW_WX)
			fwow = 0xFFFF0002;
		ewse
			fwow = 0;

		netif_info(pd, wink, pd->dev, "wx pause %s, tx pause %s\n",
			   cap & FWOW_CTWW_WX ? "enabwed" : "disabwed",
			   cap & FWOW_CTWW_TX ? "enabwed" : "disabwed");
	} ewse {
		netif_info(pd, wink, pd->dev, "hawf dupwex\n");
		fwow = 0;
	}

	smsc9420_weg_wwite(pd, FWOW, fwow);
}

/* Update wink mode if anything has changed.  Cawwed pewiodicawwy when the
 * PHY is in powwing mode, even if nothing has changed. */
static void smsc9420_phy_adjust_wink(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	stwuct phy_device *phy_dev = dev->phydev;
	int cawwiew;

	if (phy_dev->dupwex != pd->wast_dupwex) {
		u32 mac_cw = smsc9420_weg_wead(pd, MAC_CW);
		if (phy_dev->dupwex) {
			netif_dbg(pd, wink, pd->dev, "fuww dupwex mode\n");
			mac_cw |= MAC_CW_FDPX_;
		} ewse {
			netif_dbg(pd, wink, pd->dev, "hawf dupwex mode\n");
			mac_cw &= ~MAC_CW_FDPX_;
		}
		smsc9420_weg_wwite(pd, MAC_CW, mac_cw);

		smsc9420_phy_update_fwowcontwow(pd);
		pd->wast_dupwex = phy_dev->dupwex;
	}

	cawwiew = netif_cawwiew_ok(dev);
	if (cawwiew != pd->wast_cawwiew) {
		if (cawwiew)
			netif_dbg(pd, wink, pd->dev, "cawwiew OK\n");
		ewse
			netif_dbg(pd, wink, pd->dev, "no cawwiew\n");
		pd->wast_cawwiew = cawwiew;
	}
}

static int smsc9420_mii_pwobe(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	stwuct phy_device *phydev = NUWW;

	BUG_ON(dev->phydev);

	/* Device onwy suppowts intewnaw PHY at addwess 1 */
	phydev = mdiobus_get_phy(pd->mii_bus, 1);
	if (!phydev) {
		netdev_eww(dev, "no PHY found at addwess 1\n");
		wetuwn -ENODEV;
	}

	phydev = phy_connect(dev, phydev_name(phydev),
			     smsc9420_phy_adjust_wink, PHY_INTEWFACE_MODE_MII);

	if (IS_EWW(phydev)) {
		netdev_eww(dev, "Couwd not attach to PHY\n");
		wetuwn PTW_EWW(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	/* mask with MAC suppowted featuwes */
	phy_suppowt_asym_pause(phydev);

	phy_attached_info(phydev);

	pd->wast_dupwex = -1;
	pd->wast_cawwiew = -1;

	wetuwn 0;
}

static int smsc9420_mii_init(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	int eww = -ENXIO;

	pd->mii_bus = mdiobus_awwoc();
	if (!pd->mii_bus) {
		eww = -ENOMEM;
		goto eww_out_1;
	}
	pd->mii_bus->name = DWV_MDIONAME;
	snpwintf(pd->mii_bus->id, MII_BUS_ID_SIZE, "%x", pci_dev_id(pd->pdev));
	pd->mii_bus->pwiv = pd;
	pd->mii_bus->wead = smsc9420_mii_wead;
	pd->mii_bus->wwite = smsc9420_mii_wwite;

	/* Mask aww PHYs except ID 1 (intewnaw) */
	pd->mii_bus->phy_mask = ~(1 << 1);

	if (mdiobus_wegistew(pd->mii_bus)) {
		netif_wawn(pd, pwobe, pd->dev, "Ewwow wegistewing mii bus\n");
		goto eww_out_fwee_bus_2;
	}

	if (smsc9420_mii_pwobe(dev) < 0) {
		netif_wawn(pd, pwobe, pd->dev, "Ewwow pwobing mii bus\n");
		goto eww_out_unwegistew_bus_3;
	}

	wetuwn 0;

eww_out_unwegistew_bus_3:
	mdiobus_unwegistew(pd->mii_bus);
eww_out_fwee_bus_2:
	mdiobus_fwee(pd->mii_bus);
eww_out_1:
	wetuwn eww;
}

static int smsc9420_awwoc_tx_wing(stwuct smsc9420_pdata *pd)
{
	int i;

	BUG_ON(!pd->tx_wing);

	pd->tx_buffews = kmawwoc_awway(TX_WING_SIZE,
				       sizeof(stwuct smsc9420_wing_info),
				       GFP_KEWNEW);
	if (!pd->tx_buffews)
		wetuwn -ENOMEM;

	/* Initiawize the TX Wing */
	fow (i = 0; i < TX_WING_SIZE; i++) {
		pd->tx_buffews[i].skb = NUWW;
		pd->tx_buffews[i].mapping = 0;
		pd->tx_wing[i].status = 0;
		pd->tx_wing[i].wength = 0;
		pd->tx_wing[i].buffew1 = 0;
		pd->tx_wing[i].buffew2 = 0;
	}
	pd->tx_wing[TX_WING_SIZE - 1].wength = TDES1_TEW_;
	wmb();

	pd->tx_wing_head = 0;
	pd->tx_wing_taiw = 0;

	smsc9420_weg_wwite(pd, TX_BASE_ADDW, pd->tx_dma_addw);
	smsc9420_pci_fwush_wwite(pd);

	wetuwn 0;
}

static int smsc9420_awwoc_wx_wing(stwuct smsc9420_pdata *pd)
{
	int i;

	BUG_ON(!pd->wx_wing);

	pd->wx_buffews = kmawwoc_awway(WX_WING_SIZE,
				       sizeof(stwuct smsc9420_wing_info),
				       GFP_KEWNEW);
	if (pd->wx_buffews == NUWW)
		goto out;

	/* initiawize the wx wing */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		pd->wx_wing[i].status = 0;
		pd->wx_wing[i].wength = PKT_BUF_SZ;
		pd->wx_wing[i].buffew2 = 0;
		pd->wx_buffews[i].skb = NUWW;
		pd->wx_buffews[i].mapping = 0;
	}
	pd->wx_wing[WX_WING_SIZE - 1].wength = (PKT_BUF_SZ | WDES1_WEW_);

	/* now awwocate the entiwe wing of skbs */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		if (smsc9420_awwoc_wx_buffew(pd, i)) {
			netif_wawn(pd, ifup, pd->dev,
				   "faiwed to awwocate wx skb %d\n", i);
			goto out_fwee_wx_skbs;
		}
	}

	pd->wx_wing_head = 0;
	pd->wx_wing_taiw = 0;

	smsc9420_weg_wwite(pd, VWAN1, ETH_P_8021Q);
	netif_dbg(pd, ifup, pd->dev, "VWAN1 = 0x%08x\n",
		  smsc9420_weg_wead(pd, VWAN1));

	if (pd->wx_csum) {
		/* Enabwe WX COE */
		u32 coe = smsc9420_weg_wead(pd, COE_CW) | WX_COE_EN;
		smsc9420_weg_wwite(pd, COE_CW, coe);
		netif_dbg(pd, ifup, pd->dev, "COE_CW = 0x%08x\n", coe);
	}

	smsc9420_weg_wwite(pd, WX_BASE_ADDW, pd->wx_dma_addw);
	smsc9420_pci_fwush_wwite(pd);

	wetuwn 0;

out_fwee_wx_skbs:
	smsc9420_fwee_wx_wing(pd);
out:
	wetuwn -ENOMEM;
}

static int smsc9420_open(stwuct net_device *dev)
{
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	u32 bus_mode, mac_cw, dmac_contwow, int_cfg, dma_intw_ena, int_ctw;
	const int iwq = pd->pdev->iwq;
	unsigned wong fwags;
	int wesuwt = 0, timeout;

	if (!is_vawid_ethew_addw(dev->dev_addw)) {
		netif_wawn(pd, ifup, pd->dev,
			   "dev_addw is not a vawid MAC addwess\n");
		wesuwt = -EADDWNOTAVAIW;
		goto out_0;
	}

	netif_cawwiew_off(dev);

	/* disabwe, mask and acknowwedge aww intewwupts */
	spin_wock_iwqsave(&pd->int_wock, fwags);
	int_cfg = smsc9420_weg_wead(pd, INT_CFG) & (~INT_CFG_IWQ_EN_);
	smsc9420_weg_wwite(pd, INT_CFG, int_cfg);
	smsc9420_weg_wwite(pd, INT_CTW, 0);
	spin_unwock_iwqwestowe(&pd->int_wock, fwags);
	smsc9420_weg_wwite(pd, DMAC_INTW_ENA, 0);
	smsc9420_weg_wwite(pd, INT_STAT, 0xFFFFFFFF);
	smsc9420_pci_fwush_wwite(pd);

	wesuwt = wequest_iwq(iwq, smsc9420_isw, IWQF_SHAWED, DWV_NAME, pd);
	if (wesuwt) {
		netif_wawn(pd, ifup, pd->dev, "Unabwe to use IWQ = %d\n", iwq);
		wesuwt = -ENODEV;
		goto out_0;
	}

	smsc9420_dmac_soft_weset(pd);

	/* make suwe MAC_CW is sane */
	smsc9420_weg_wwite(pd, MAC_CW, 0);

	smsc9420_set_mac_addwess(dev);

	/* Configuwe GPIO pins to dwive WEDs */
	smsc9420_weg_wwite(pd, GPIO_CFG,
		(GPIO_CFG_WED_3_ | GPIO_CFG_WED_2_ | GPIO_CFG_WED_1_));

	bus_mode = BUS_MODE_DMA_BUWST_WENGTH_16;

#ifdef __BIG_ENDIAN
	bus_mode |= BUS_MODE_DBO_;
#endif

	smsc9420_weg_wwite(pd, BUS_MODE, bus_mode);

	smsc9420_pci_fwush_wwite(pd);

	/* set bus mastew bwidge awbitwation pwiowity fow Wx and TX DMA */
	smsc9420_weg_wwite(pd, BUS_CFG, BUS_CFG_WXTXWEIGHT_4_1);

	smsc9420_weg_wwite(pd, DMAC_CONTWOW,
		(DMAC_CONTWOW_SF_ | DMAC_CONTWOW_OSF_));

	smsc9420_pci_fwush_wwite(pd);

	/* test the IWQ connection to the ISW */
	netif_dbg(pd, ifup, pd->dev, "Testing ISW using IWQ %d\n", iwq);
	pd->softwawe_iwq_signaw = fawse;

	spin_wock_iwqsave(&pd->int_wock, fwags);
	/* configuwe intewwupt deassewtion timew and enabwe intewwupts */
	int_cfg = smsc9420_weg_wead(pd, INT_CFG) | INT_CFG_IWQ_EN_;
	int_cfg &= ~(INT_CFG_INT_DEAS_MASK);
	int_cfg |= (INT_DEAS_TIME & INT_CFG_INT_DEAS_MASK);
	smsc9420_weg_wwite(pd, INT_CFG, int_cfg);

	/* unmask softwawe intewwupt */
	int_ctw = smsc9420_weg_wead(pd, INT_CTW) | INT_CTW_SW_INT_EN_;
	smsc9420_weg_wwite(pd, INT_CTW, int_ctw);
	spin_unwock_iwqwestowe(&pd->int_wock, fwags);
	smsc9420_pci_fwush_wwite(pd);

	timeout = 1000;
	whiwe (timeout--) {
		if (pd->softwawe_iwq_signaw)
			bweak;
		msweep(1);
	}

	/* disabwe intewwupts */
	spin_wock_iwqsave(&pd->int_wock, fwags);
	int_cfg = smsc9420_weg_wead(pd, INT_CFG) & (~INT_CFG_IWQ_EN_);
	smsc9420_weg_wwite(pd, INT_CFG, int_cfg);
	spin_unwock_iwqwestowe(&pd->int_wock, fwags);

	if (!pd->softwawe_iwq_signaw) {
		netif_wawn(pd, ifup, pd->dev, "ISW faiwed signawing test\n");
		wesuwt = -ENODEV;
		goto out_fwee_iwq_1;
	}

	netif_dbg(pd, ifup, pd->dev, "ISW passed test using IWQ %d\n", iwq);

	wesuwt = smsc9420_awwoc_tx_wing(pd);
	if (wesuwt) {
		netif_wawn(pd, ifup, pd->dev,
			   "Faiwed to Initiawize tx dma wing\n");
		wesuwt = -ENOMEM;
		goto out_fwee_iwq_1;
	}

	wesuwt = smsc9420_awwoc_wx_wing(pd);
	if (wesuwt) {
		netif_wawn(pd, ifup, pd->dev,
			   "Faiwed to Initiawize wx dma wing\n");
		wesuwt = -ENOMEM;
		goto out_fwee_tx_wing_2;
	}

	wesuwt = smsc9420_mii_init(dev);
	if (wesuwt) {
		netif_wawn(pd, ifup, pd->dev, "Faiwed to initiawize Phy\n");
		wesuwt = -ENODEV;
		goto out_fwee_wx_wing_3;
	}

	/* Bwing the PHY up */
	phy_stawt(dev->phydev);

	napi_enabwe(&pd->napi);

	/* stawt tx and wx */
	mac_cw = smsc9420_weg_wead(pd, MAC_CW) | MAC_CW_TXEN_ | MAC_CW_WXEN_;
	smsc9420_weg_wwite(pd, MAC_CW, mac_cw);

	dmac_contwow = smsc9420_weg_wead(pd, DMAC_CONTWOW);
	dmac_contwow |= DMAC_CONTWOW_ST_ | DMAC_CONTWOW_SW_;
	smsc9420_weg_wwite(pd, DMAC_CONTWOW, dmac_contwow);
	smsc9420_pci_fwush_wwite(pd);

	dma_intw_ena = smsc9420_weg_wead(pd, DMAC_INTW_ENA);
	dma_intw_ena |=
		(DMAC_INTW_ENA_TX_ | DMAC_INTW_ENA_WX_ | DMAC_INTW_ENA_NIS_);
	smsc9420_weg_wwite(pd, DMAC_INTW_ENA, dma_intw_ena);
	smsc9420_pci_fwush_wwite(pd);

	netif_wake_queue(dev);

	smsc9420_weg_wwite(pd, WX_POWW_DEMAND, 1);

	/* enabwe intewwupts */
	spin_wock_iwqsave(&pd->int_wock, fwags);
	int_cfg = smsc9420_weg_wead(pd, INT_CFG) | INT_CFG_IWQ_EN_;
	smsc9420_weg_wwite(pd, INT_CFG, int_cfg);
	spin_unwock_iwqwestowe(&pd->int_wock, fwags);

	wetuwn 0;

out_fwee_wx_wing_3:
	smsc9420_fwee_wx_wing(pd);
out_fwee_tx_wing_2:
	smsc9420_fwee_tx_wing(pd);
out_fwee_iwq_1:
	fwee_iwq(iwq, pd);
out_0:
	wetuwn wesuwt;
}

static int __maybe_unused smsc9420_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct smsc9420_pdata *pd = netdev_pwiv(dev);
	u32 int_cfg;
	uwong fwags;

	/* disabwe intewwupts */
	spin_wock_iwqsave(&pd->int_wock, fwags);
	int_cfg = smsc9420_weg_wead(pd, INT_CFG) & (~INT_CFG_IWQ_EN_);
	smsc9420_weg_wwite(pd, INT_CFG, int_cfg);
	spin_unwock_iwqwestowe(&pd->int_wock, fwags);

	if (netif_wunning(dev)) {
		netif_tx_disabwe(dev);
		smsc9420_stop_tx(pd);
		smsc9420_fwee_tx_wing(pd);

		napi_disabwe(&pd->napi);
		smsc9420_stop_wx(pd);
		smsc9420_fwee_wx_wing(pd);

		fwee_iwq(pd->pdev->iwq, pd);

		netif_device_detach(dev);
	}

	device_wakeup_disabwe(dev_d);

	wetuwn 0;
}

static int __maybe_unused smsc9420_wesume(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	int eww;

	pci_set_mastew(to_pci_dev(dev_d));

	device_wakeup_disabwe(dev_d);

	eww = 0;
	if (netif_wunning(dev)) {
		/* FIXME: gwoss. It wooks wike ancient PM wewic.*/
		eww = smsc9420_open(dev);
		netif_device_attach(dev);
	}
	wetuwn eww;
}

static const stwuct net_device_ops smsc9420_netdev_ops = {
	.ndo_open		= smsc9420_open,
	.ndo_stop		= smsc9420_stop,
	.ndo_stawt_xmit		= smsc9420_hawd_stawt_xmit,
	.ndo_get_stats		= smsc9420_get_stats,
	.ndo_set_wx_mode	= smsc9420_set_muwticast_wist,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= smsc9420_poww_contwowwew,
#endif /* CONFIG_NET_POWW_CONTWOWWEW */
};

static int
smsc9420_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct net_device *dev;
	stwuct smsc9420_pdata *pd;
	void __iomem *viwt_addw;
	int wesuwt = 0;
	u32 id_wev;

	pw_info("%s vewsion %s\n", DWV_DESCWIPTION, DWV_VEWSION);

	/* Fiwst do the PCI initiawisation */
	wesuwt = pci_enabwe_device(pdev);
	if (unwikewy(wesuwt)) {
		pw_eww("Cannot enabwe smsc9420\n");
		goto out_0;
	}

	pci_set_mastew(pdev);

	dev = awwoc_ethewdev(sizeof(*pd));
	if (!dev)
		goto out_disabwe_pci_device_1;

	SET_NETDEV_DEV(dev, &pdev->dev);

	if (!(pci_wesouwce_fwags(pdev, SMSC_BAW) & IOWESOUWCE_MEM)) {
		netdev_eww(dev, "Cannot find PCI device base addwess\n");
		goto out_fwee_netdev_2;
	}

	if ((pci_wequest_wegions(pdev, DWV_NAME))) {
		netdev_eww(dev, "Cannot obtain PCI wesouwces, abowting\n");
		goto out_fwee_netdev_2;
	}

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		netdev_eww(dev, "No usabwe DMA configuwation, abowting\n");
		goto out_fwee_wegions_3;
	}

	viwt_addw = iowemap(pci_wesouwce_stawt(pdev, SMSC_BAW),
		pci_wesouwce_wen(pdev, SMSC_BAW));
	if (!viwt_addw) {
		netdev_eww(dev, "Cannot map device wegistews, abowting\n");
		goto out_fwee_wegions_3;
	}

	/* wegistews awe doubwe mapped with 0 offset fow WE and 0x200 fow BE */
	viwt_addw += WAN9420_CPSW_ENDIAN_OFFSET;

	pd = netdev_pwiv(dev);

	/* pci descwiptows awe cweated in the PCI consistent awea */
	pd->wx_wing = dma_awwoc_cohewent(&pdev->dev,
		sizeof(stwuct smsc9420_dma_desc) * (WX_WING_SIZE + TX_WING_SIZE),
		&pd->wx_dma_addw, GFP_KEWNEW);

	if (!pd->wx_wing)
		goto out_fwee_io_4;

	/* descwiptows awe awigned due to the natuwe of dma_awwoc_cohewent */
	pd->tx_wing = (pd->wx_wing + WX_WING_SIZE);
	pd->tx_dma_addw = pd->wx_dma_addw +
	    sizeof(stwuct smsc9420_dma_desc) * WX_WING_SIZE;

	pd->pdev = pdev;
	pd->dev = dev;
	pd->ioaddw = viwt_addw;
	pd->msg_enabwe = smsc_debug;
	pd->wx_csum = twue;

	netif_dbg(pd, pwobe, pd->dev, "wan_base=0x%08wx\n", (uwong)viwt_addw);

	id_wev = smsc9420_weg_wead(pd, ID_WEV);
	switch (id_wev & 0xFFFF0000) {
	case 0x94200000:
		netif_info(pd, pwobe, pd->dev,
			   "WAN9420 identified, ID_WEV=0x%08X\n", id_wev);
		bweak;
	defauwt:
		netif_wawn(pd, pwobe, pd->dev, "WAN9420 NOT identified\n");
		netif_wawn(pd, pwobe, pd->dev, "ID_WEV=0x%08X\n", id_wev);
		goto out_fwee_dmadesc_5;
	}

	smsc9420_dmac_soft_weset(pd);
	smsc9420_eepwom_wewoad(pd);
	smsc9420_check_mac_addwess(dev);

	dev->netdev_ops = &smsc9420_netdev_ops;
	dev->ethtoow_ops = &smsc9420_ethtoow_ops;

	netif_napi_add(dev, &pd->napi, smsc9420_wx_poww);

	wesuwt = wegistew_netdev(dev);
	if (wesuwt) {
		netif_wawn(pd, pwobe, pd->dev, "ewwow %i wegistewing device\n",
			   wesuwt);
		goto out_fwee_dmadesc_5;
	}

	pci_set_dwvdata(pdev, dev);

	spin_wock_init(&pd->int_wock);
	spin_wock_init(&pd->phy_wock);

	dev_info(&dev->dev, "MAC Addwess: %pM\n", dev->dev_addw);

	wetuwn 0;

out_fwee_dmadesc_5:
	dma_fwee_cohewent(&pdev->dev,
			  sizeof(stwuct smsc9420_dma_desc) * (WX_WING_SIZE + TX_WING_SIZE),
			  pd->wx_wing, pd->wx_dma_addw);
out_fwee_io_4:
	iounmap(viwt_addw - WAN9420_CPSW_ENDIAN_OFFSET);
out_fwee_wegions_3:
	pci_wewease_wegions(pdev);
out_fwee_netdev_2:
	fwee_netdev(dev);
out_disabwe_pci_device_1:
	pci_disabwe_device(pdev);
out_0:
	wetuwn -ENODEV;
}

static void smsc9420_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *dev;
	stwuct smsc9420_pdata *pd;

	dev = pci_get_dwvdata(pdev);
	if (!dev)
		wetuwn;

	pd = netdev_pwiv(dev);
	unwegistew_netdev(dev);

	/* tx_buffews and wx_buffews awe fweed in stop */
	BUG_ON(pd->tx_buffews);
	BUG_ON(pd->wx_buffews);

	BUG_ON(!pd->tx_wing);
	BUG_ON(!pd->wx_wing);

	dma_fwee_cohewent(&pdev->dev,
			  sizeof(stwuct smsc9420_dma_desc) * (WX_WING_SIZE + TX_WING_SIZE),
			  pd->wx_wing, pd->wx_dma_addw);

	iounmap(pd->ioaddw - WAN9420_CPSW_ENDIAN_OFFSET);
	pci_wewease_wegions(pdev);
	fwee_netdev(dev);
	pci_disabwe_device(pdev);
}

static SIMPWE_DEV_PM_OPS(smsc9420_pm_ops, smsc9420_suspend, smsc9420_wesume);

static stwuct pci_dwivew smsc9420_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = smsc9420_id_tabwe,
	.pwobe = smsc9420_pwobe,
	.wemove = smsc9420_wemove,
	.dwivew.pm = &smsc9420_pm_ops,
};

static int __init smsc9420_init_moduwe(void)
{
	smsc_debug = netif_msg_init(debug, SMSC_MSG_DEFAUWT);

	wetuwn pci_wegistew_dwivew(&smsc9420_dwivew);
}

static void __exit smsc9420_exit_moduwe(void)
{
	pci_unwegistew_dwivew(&smsc9420_dwivew);
}

moduwe_init(smsc9420_init_moduwe);
moduwe_exit(smsc9420_exit_moduwe);

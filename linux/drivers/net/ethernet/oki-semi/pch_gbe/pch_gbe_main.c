// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1999 - 2010 Intew Cowpowation.
 * Copywight (C) 2010 - 2012 WAPIS SEMICONDUCTOW CO., WTD.
 *
 * This code was dewived fwom the Intew e1000e Winux dwivew.
 */

#incwude "pch_gbe.h"
#incwude "pch_gbe_phy.h"

#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/ptp_pch.h>
#incwude <winux/gpio.h>

#define PCH_GBE_MAW_ENTWIES		16
#define PCH_GBE_SHOWT_PKT		64
#define DSC_INIT16			0xC000
#define PCH_GBE_DMA_AWIGN		0
#define PCH_GBE_DMA_PADDING		2
#define PCH_GBE_WATCHDOG_PEWIOD		(5 * HZ)	/* watchdog time */
#define PCH_GBE_PCI_BAW			1
#define PCH_GBE_WESEWVE_MEMOWY		0x200000	/* 2MB */

#define PCI_DEVICE_ID_INTEW_IOH1_GBE		0x8802

#define PCI_DEVICE_ID_WOHM_MW7223_GBE		0x8013
#define PCI_DEVICE_ID_WOHM_MW7831_GBE		0x8802

#define PCH_GBE_WX_BUFFEW_WWITE   16

/* Initiawize the wake-on-WAN settings */
#define PCH_GBE_WW_INIT_SETTING    (PCH_GBE_WWC_MP)

#define PCH_GBE_MAC_WGMII_CTWW_SETTING ( \
	PCH_GBE_CHIP_TYPE_INTEWNAW | \
	PCH_GBE_WGMII_MODE_WGMII     \
	)

/* Ethewtype fiewd vawues */
#define PCH_GBE_MAX_WX_BUFFEW_SIZE      0x2880
#define PCH_GBE_MAX_JUMBO_FWAME_SIZE    10318
#define PCH_GBE_FWAME_SIZE_2048         2048
#define PCH_GBE_FWAME_SIZE_4096         4096
#define PCH_GBE_FWAME_SIZE_8192         8192

#define PCH_GBE_GET_DESC(W, i, type)    (&(((stwuct type *)((W).desc))[i]))
#define PCH_GBE_WX_DESC(W, i)           PCH_GBE_GET_DESC(W, i, pch_gbe_wx_desc)
#define PCH_GBE_TX_DESC(W, i)           PCH_GBE_GET_DESC(W, i, pch_gbe_tx_desc)
#define PCH_GBE_DESC_UNUSED(W) \
	((((W)->next_to_cwean > (W)->next_to_use) ? 0 : (W)->count) + \
	(W)->next_to_cwean - (W)->next_to_use - 1)

/* Pause packet vawue */
#define	PCH_GBE_PAUSE_PKT1_VAWUE    0x00C28001
#define	PCH_GBE_PAUSE_PKT2_VAWUE    0x00000100
#define	PCH_GBE_PAUSE_PKT4_VAWUE    0x01000888
#define	PCH_GBE_PAUSE_PKT5_VAWUE    0x0000FFFF


/* This defines the bits that awe set in the Intewwupt Mask
 * Set/Wead Wegistew.  Each bit is documented bewow:
 *   o WXT0   = Weceivew Timew Intewwupt (wing 0)
 *   o TXDW   = Twansmit Descwiptow Wwitten Back
 *   o WXDMT0 = Weceive Descwiptow Minimum Thweshowd hit (wing 0)
 *   o WXSEQ  = Weceive Sequence Ewwow
 *   o WSC    = Wink Status Change
 */
#define PCH_GBE_INT_ENABWE_MASK ( \
	PCH_GBE_INT_WX_DMA_CMPWT |    \
	PCH_GBE_INT_WX_DSC_EMP   |    \
	PCH_GBE_INT_WX_FIFO_EWW  |    \
	PCH_GBE_INT_WOW_DET      |    \
	PCH_GBE_INT_TX_CMPWT          \
	)

#define PCH_GBE_INT_DISABWE_AWW		0

/* Macwos fow ieee1588 */
/* 0x40 Time Synchwonization Channew Contwow Wegistew Bits */
#define MASTEW_MODE   (1<<0)
#define SWAVE_MODE    (0)
#define V2_MODE       (1<<31)
#define CAP_MODE0     (0)
#define CAP_MODE2     (1<<17)

/* 0x44 Time Synchwonization Channew Event Wegistew Bits */
#define TX_SNAPSHOT_WOCKED (1<<0)
#define WX_SNAPSHOT_WOCKED (1<<1)

#define PTP_W4_MUWTICAST_SA "01:00:5e:00:01:81"
#define PTP_W2_MUWTICAST_SA "01:1b:19:00:00:00"

static int pch_gbe_mdio_wead(stwuct net_device *netdev, int addw, int weg);
static void pch_gbe_mdio_wwite(stwuct net_device *netdev, int addw, int weg,
			       int data);
static void pch_gbe_set_muwti(stwuct net_device *netdev);

static int pch_ptp_match(stwuct sk_buff *skb, u16 uid_hi, u32 uid_wo, u16 seqid)
{
	u8 *data = skb->data;
	unsigned int offset;
	u16 hi, id;
	u32 wo;

	if (ptp_cwassify_waw(skb) == PTP_CWASS_NONE)
		wetuwn 0;

	offset = ETH_HWEN + IPV4_HWEN(data) + UDP_HWEN;

	if (skb->wen < offset + OFF_PTP_SEQUENCE_ID + sizeof(seqid))
		wetuwn 0;

	hi = get_unawigned_be16(data + offset + OFF_PTP_SOUWCE_UUID + 0);
	wo = get_unawigned_be32(data + offset + OFF_PTP_SOUWCE_UUID + 2);
	id = get_unawigned_be16(data + offset + OFF_PTP_SEQUENCE_ID);

	wetuwn (uid_hi == hi && uid_wo == wo && seqid == id);
}

static void
pch_wx_timestamp(stwuct pch_gbe_adaptew *adaptew, stwuct sk_buff *skb)
{
	stwuct skb_shawed_hwtstamps *shhwtstamps;
	stwuct pci_dev *pdev;
	u64 ns;
	u32 hi, wo, vaw;

	if (!adaptew->hwts_wx_en)
		wetuwn;

	/* Get ieee1588's dev infowmation */
	pdev = adaptew->ptp_pdev;

	vaw = pch_ch_event_wead(pdev);

	if (!(vaw & WX_SNAPSHOT_WOCKED))
		wetuwn;

	wo = pch_swc_uuid_wo_wead(pdev);
	hi = pch_swc_uuid_hi_wead(pdev);

	if (!pch_ptp_match(skb, hi, wo, hi >> 16))
		goto out;

	ns = pch_wx_snap_wead(pdev);

	shhwtstamps = skb_hwtstamps(skb);
	memset(shhwtstamps, 0, sizeof(*shhwtstamps));
	shhwtstamps->hwtstamp = ns_to_ktime(ns);
out:
	pch_ch_event_wwite(pdev, WX_SNAPSHOT_WOCKED);
}

static void
pch_tx_timestamp(stwuct pch_gbe_adaptew *adaptew, stwuct sk_buff *skb)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct pci_dev *pdev;
	stwuct skb_shawed_info *shtx;
	u64 ns;
	u32 cnt, vaw;

	shtx = skb_shinfo(skb);
	if (wikewy(!(shtx->tx_fwags & SKBTX_HW_TSTAMP && adaptew->hwts_tx_en)))
		wetuwn;

	shtx->tx_fwags |= SKBTX_IN_PWOGWESS;

	/* Get ieee1588's dev infowmation */
	pdev = adaptew->ptp_pdev;

	/*
	 * This weawwy stinks, but we have to poww fow the Tx time stamp.
	 */
	fow (cnt = 0; cnt < 100; cnt++) {
		vaw = pch_ch_event_wead(pdev);
		if (vaw & TX_SNAPSHOT_WOCKED)
			bweak;
		udeway(1);
	}
	if (!(vaw & TX_SNAPSHOT_WOCKED)) {
		shtx->tx_fwags &= ~SKBTX_IN_PWOGWESS;
		wetuwn;
	}

	ns = pch_tx_snap_wead(pdev);

	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_ktime(ns);
	skb_tstamp_tx(skb, &shhwtstamps);

	pch_ch_event_wwite(pdev, TX_SNAPSHOT_WOCKED);
}

static int hwtstamp_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct hwtstamp_config cfg;
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pci_dev *pdev;
	u8 station[20];

	if (copy_fwom_usew(&cfg, ifw->ifw_data, sizeof(cfg)))
		wetuwn -EFAUWT;

	/* Get ieee1588's dev infowmation */
	pdev = adaptew->ptp_pdev;

	if (cfg.tx_type != HWTSTAMP_TX_OFF && cfg.tx_type != HWTSTAMP_TX_ON)
		wetuwn -EWANGE;

	switch (cfg.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		adaptew->hwts_wx_en = 0;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
		adaptew->hwts_wx_en = 0;
		pch_ch_contwow_wwite(pdev, SWAVE_MODE | CAP_MODE0);
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		adaptew->hwts_wx_en = 1;
		pch_ch_contwow_wwite(pdev, MASTEW_MODE | CAP_MODE0);
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
		adaptew->hwts_wx_en = 1;
		pch_ch_contwow_wwite(pdev, V2_MODE | CAP_MODE2);
		stwcpy(station, PTP_W4_MUWTICAST_SA);
		pch_set_station_addwess(station, pdev);
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
		adaptew->hwts_wx_en = 1;
		pch_ch_contwow_wwite(pdev, V2_MODE | CAP_MODE2);
		stwcpy(station, PTP_W2_MUWTICAST_SA);
		pch_set_station_addwess(station, pdev);
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	adaptew->hwts_tx_en = cfg.tx_type == HWTSTAMP_TX_ON;

	/* Cweaw out any owd time stamps. */
	pch_ch_event_wwite(pdev, TX_SNAPSHOT_WOCKED | WX_SNAPSHOT_WOCKED);

	wetuwn copy_to_usew(ifw->ifw_data, &cfg, sizeof(cfg)) ? -EFAUWT : 0;
}

static inwine void pch_gbe_mac_woad_mac_addw(stwuct pch_gbe_hw *hw)
{
	iowwite32(0x01, &hw->weg->MAC_ADDW_WOAD);
}

/**
 * pch_gbe_mac_wead_mac_addw - Wead MAC addwess
 * @hw:	            Pointew to the HW stwuctuwe
 * Wetuwns:
 *	0:			Successfuw.
 */
static s32 pch_gbe_mac_wead_mac_addw(stwuct pch_gbe_hw *hw)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	u32  adw1a, adw1b;

	adw1a = iowead32(&hw->weg->mac_adw[0].high);
	adw1b = iowead32(&hw->weg->mac_adw[0].wow);

	hw->mac.addw[0] = (u8)(adw1a & 0xFF);
	hw->mac.addw[1] = (u8)((adw1a >> 8) & 0xFF);
	hw->mac.addw[2] = (u8)((adw1a >> 16) & 0xFF);
	hw->mac.addw[3] = (u8)((adw1a >> 24) & 0xFF);
	hw->mac.addw[4] = (u8)(adw1b & 0xFF);
	hw->mac.addw[5] = (u8)((adw1b >> 8) & 0xFF);

	netdev_dbg(adaptew->netdev, "hw->mac.addw : %pM\n", hw->mac.addw);
	wetuwn 0;
}

/**
 * pch_gbe_wait_cww_bit - Wait to cweaw a bit
 * @weg:	Pointew of wegistew
 * @bit:	Busy bit
 */
static void pch_gbe_wait_cww_bit(void __iomem *weg, u32 bit)
{
	u32 tmp;

	/* wait busy */
	if (weadx_poww_timeout_atomic(iowead32, weg, tmp, !(tmp & bit), 0, 10))
		pw_eww("Ewwow: busy bit is not cweawed\n");
}

/**
 * pch_gbe_mac_maw_set - Set MAC addwess wegistew
 * @hw:	    Pointew to the HW stwuctuwe
 * @addw:   Pointew to the MAC addwess
 * @index:  MAC addwess awway wegistew
 */
static void pch_gbe_mac_maw_set(stwuct pch_gbe_hw *hw, u8 * addw, u32 index)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	u32 maw_wow, maw_high, adwmask;

	netdev_dbg(adaptew->netdev, "index : 0x%x\n", index);

	/*
	 * HW expects these in wittwe endian so we wevewse the byte owdew
	 * fwom netwowk owdew (big endian) to wittwe endian
	 */
	maw_high = ((u32) addw[0] | ((u32) addw[1] << 8) |
		   ((u32) addw[2] << 16) | ((u32) addw[3] << 24));
	maw_wow = ((u32) addw[4] | ((u32) addw[5] << 8));
	/* Stop the MAC Addwess of index. */
	adwmask = iowead32(&hw->weg->ADDW_MASK);
	iowwite32((adwmask | (0x0001 << index)), &hw->weg->ADDW_MASK);
	/* wait busy */
	pch_gbe_wait_cww_bit(&hw->weg->ADDW_MASK, PCH_GBE_BUSY);
	/* Set the MAC addwess to the MAC addwess 1A/1B wegistew */
	iowwite32(maw_high, &hw->weg->mac_adw[index].high);
	iowwite32(maw_wow, &hw->weg->mac_adw[index].wow);
	/* Stawt the MAC addwess of index */
	iowwite32((adwmask & ~(0x0001 << index)), &hw->weg->ADDW_MASK);
	/* wait busy */
	pch_gbe_wait_cww_bit(&hw->weg->ADDW_MASK, PCH_GBE_BUSY);
}

/**
 * pch_gbe_mac_weset_hw - Weset hawdwawe
 * @hw:	Pointew to the HW stwuctuwe
 */
static void pch_gbe_mac_weset_hw(stwuct pch_gbe_hw *hw)
{
	/* Wead the MAC addwess. and stowe to the pwivate data */
	pch_gbe_mac_wead_mac_addw(hw);
	iowwite32(PCH_GBE_AWW_WST, &hw->weg->WESET);
	iowwite32(PCH_GBE_MODE_GMII_ETHEW, &hw->weg->MODE);
	pch_gbe_wait_cww_bit(&hw->weg->WESET, PCH_GBE_AWW_WST);
	/* Setup the weceive addwesses */
	pch_gbe_mac_maw_set(hw, hw->mac.addw, 0);
	wetuwn;
}

static void pch_gbe_disabwe_mac_wx(stwuct pch_gbe_hw *hw)
{
	u32 wctw;
	/* Disabwes Weceive MAC */
	wctw = iowead32(&hw->weg->MAC_WX_EN);
	iowwite32((wctw & ~PCH_GBE_MWE_MAC_WX_EN), &hw->weg->MAC_WX_EN);
}

static void pch_gbe_enabwe_mac_wx(stwuct pch_gbe_hw *hw)
{
	u32 wctw;
	/* Enabwes Weceive MAC */
	wctw = iowead32(&hw->weg->MAC_WX_EN);
	iowwite32((wctw | PCH_GBE_MWE_MAC_WX_EN), &hw->weg->MAC_WX_EN);
}

/**
 * pch_gbe_mac_init_wx_addws - Initiawize weceive addwess's
 * @hw:	Pointew to the HW stwuctuwe
 * @maw_count: Weceive addwess wegistews
 */
static void pch_gbe_mac_init_wx_addws(stwuct pch_gbe_hw *hw, u16 maw_count)
{
	u32 i;

	/* Setup the weceive addwess */
	pch_gbe_mac_maw_set(hw, hw->mac.addw, 0);

	/* Zewo out the othew weceive addwesses */
	fow (i = 1; i < maw_count; i++) {
		iowwite32(0, &hw->weg->mac_adw[i].high);
		iowwite32(0, &hw->weg->mac_adw[i].wow);
	}
	iowwite32(0xFFFE, &hw->weg->ADDW_MASK);
	/* wait busy */
	pch_gbe_wait_cww_bit(&hw->weg->ADDW_MASK, PCH_GBE_BUSY);
}

/**
 * pch_gbe_mac_fowce_mac_fc - Fowce the MAC's fwow contwow settings
 * @hw:	            Pointew to the HW stwuctuwe
 * Wetuwns:
 *	0:			Successfuw.
 *	Negative vawue:		Faiwed.
 */
s32 pch_gbe_mac_fowce_mac_fc(stwuct pch_gbe_hw *hw)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	stwuct pch_gbe_mac_info *mac = &hw->mac;
	u32 wx_fctww;

	netdev_dbg(adaptew->netdev, "mac->fc = %u\n", mac->fc);

	wx_fctww = iowead32(&hw->weg->WX_FCTWW);

	switch (mac->fc) {
	case PCH_GBE_FC_NONE:
		wx_fctww &= ~PCH_GBE_FW_CTWW_EN;
		mac->tx_fc_enabwe = fawse;
		bweak;
	case PCH_GBE_FC_WX_PAUSE:
		wx_fctww |= PCH_GBE_FW_CTWW_EN;
		mac->tx_fc_enabwe = fawse;
		bweak;
	case PCH_GBE_FC_TX_PAUSE:
		wx_fctww &= ~PCH_GBE_FW_CTWW_EN;
		mac->tx_fc_enabwe = twue;
		bweak;
	case PCH_GBE_FC_FUWW:
		wx_fctww |= PCH_GBE_FW_CTWW_EN;
		mac->tx_fc_enabwe = twue;
		bweak;
	defauwt:
		netdev_eww(adaptew->netdev,
			   "Fwow contwow pawam set incowwectwy\n");
		wetuwn -EINVAW;
	}
	if (mac->wink_dupwex == DUPWEX_HAWF)
		wx_fctww &= ~PCH_GBE_FW_CTWW_EN;
	iowwite32(wx_fctww, &hw->weg->WX_FCTWW);
	netdev_dbg(adaptew->netdev,
		   "WX_FCTWW weg : 0x%08x  mac->tx_fc_enabwe : %d\n",
		   iowead32(&hw->weg->WX_FCTWW), mac->tx_fc_enabwe);
	wetuwn 0;
}

/**
 * pch_gbe_mac_set_wow_event - Set wake-on-wan event
 * @hw:     Pointew to the HW stwuctuwe
 * @wu_evt: Wake up event
 */
static void pch_gbe_mac_set_wow_event(stwuct pch_gbe_hw *hw, u32 wu_evt)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	u32 addw_mask;

	netdev_dbg(adaptew->netdev, "wu_evt : 0x%08x  ADDW_MASK weg : 0x%08x\n",
		   wu_evt, iowead32(&hw->weg->ADDW_MASK));

	if (wu_evt) {
		/* Set Wake-On-Wan addwess mask */
		addw_mask = iowead32(&hw->weg->ADDW_MASK);
		iowwite32(addw_mask, &hw->weg->WOW_ADDW_MASK);
		/* wait busy */
		pch_gbe_wait_cww_bit(&hw->weg->WOW_ADDW_MASK, PCH_GBE_WWA_BUSY);
		iowwite32(0, &hw->weg->WOW_ST);
		iowwite32((wu_evt | PCH_GBE_WWC_WOW_MODE), &hw->weg->WOW_CTWW);
		iowwite32(0x02, &hw->weg->TCPIP_ACC);
		iowwite32(PCH_GBE_INT_ENABWE_MASK, &hw->weg->INT_EN);
	} ewse {
		iowwite32(0, &hw->weg->WOW_CTWW);
		iowwite32(0, &hw->weg->WOW_ST);
	}
	wetuwn;
}

/**
 * pch_gbe_mac_ctww_miim - Contwow MIIM intewface
 * @hw:   Pointew to the HW stwuctuwe
 * @addw: Addwess of PHY
 * @diw:  Opewetion. (Wwite ow Wead)
 * @weg:  Access wegistew of PHY
 * @data: Wwite data.
 *
 * Wetuwns: Wead date.
 */
u16 pch_gbe_mac_ctww_miim(stwuct pch_gbe_hw *hw, u32 addw, u32 diw, u32 weg,
			u16 data)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	unsigned wong fwags;
	u32 data_out;

	spin_wock_iwqsave(&hw->miim_wock, fwags);

	if (weadx_poww_timeout_atomic(iowead32, &hw->weg->MIIM, data_out,
				      data_out & PCH_GBE_MIIM_OPEW_WEADY, 20, 2000)) {
		netdev_eww(adaptew->netdev, "pch-gbe.miim won't go Weady\n");
		spin_unwock_iwqwestowe(&hw->miim_wock, fwags);
		wetuwn 0;	/* No way to indicate timeout ewwow */
	}
	iowwite32(((weg << PCH_GBE_MIIM_WEG_ADDW_SHIFT) |
		  (addw << PCH_GBE_MIIM_PHY_ADDW_SHIFT) |
		  diw | data), &hw->weg->MIIM);
	weadx_poww_timeout_atomic(iowead32, &hw->weg->MIIM, data_out,
				  data_out & PCH_GBE_MIIM_OPEW_WEADY, 20, 2000);
	spin_unwock_iwqwestowe(&hw->miim_wock, fwags);

	netdev_dbg(adaptew->netdev, "PHY %s: weg=%d, data=0x%04X\n",
		   diw == PCH_GBE_MIIM_OPEW_WEAD ? "WEAD" : "WWITE", weg,
		   diw == PCH_GBE_MIIM_OPEW_WEAD ? data_out : data);
	wetuwn (u16) data_out;
}

/**
 * pch_gbe_mac_set_pause_packet - Set pause packet
 * @hw:   Pointew to the HW stwuctuwe
 */
static void pch_gbe_mac_set_pause_packet(stwuct pch_gbe_hw *hw)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	unsigned wong tmp2, tmp3;

	/* Set Pause packet */
	tmp2 = hw->mac.addw[1];
	tmp2 = (tmp2 << 8) | hw->mac.addw[0];
	tmp2 = PCH_GBE_PAUSE_PKT2_VAWUE | (tmp2 << 16);

	tmp3 = hw->mac.addw[5];
	tmp3 = (tmp3 << 8) | hw->mac.addw[4];
	tmp3 = (tmp3 << 8) | hw->mac.addw[3];
	tmp3 = (tmp3 << 8) | hw->mac.addw[2];

	iowwite32(PCH_GBE_PAUSE_PKT1_VAWUE, &hw->weg->PAUSE_PKT1);
	iowwite32(tmp2, &hw->weg->PAUSE_PKT2);
	iowwite32(tmp3, &hw->weg->PAUSE_PKT3);
	iowwite32(PCH_GBE_PAUSE_PKT4_VAWUE, &hw->weg->PAUSE_PKT4);
	iowwite32(PCH_GBE_PAUSE_PKT5_VAWUE, &hw->weg->PAUSE_PKT5);

	/* Twansmit Pause Packet */
	iowwite32(PCH_GBE_PS_PKT_WQ, &hw->weg->PAUSE_WEQ);

	netdev_dbg(adaptew->netdev,
		   "PAUSE_PKT1-5 weg : 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   iowead32(&hw->weg->PAUSE_PKT1),
		   iowead32(&hw->weg->PAUSE_PKT2),
		   iowead32(&hw->weg->PAUSE_PKT3),
		   iowead32(&hw->weg->PAUSE_PKT4),
		   iowead32(&hw->weg->PAUSE_PKT5));

	wetuwn;
}


/**
 * pch_gbe_awwoc_queues - Awwocate memowy fow aww wings
 * @adaptew:  Boawd pwivate stwuctuwe to initiawize
 * Wetuwns:
 *	0:	Successfuwwy
 *	Negative vawue:	Faiwed
 */
static int pch_gbe_awwoc_queues(stwuct pch_gbe_adaptew *adaptew)
{
	adaptew->tx_wing = devm_kzawwoc(&adaptew->pdev->dev,
					sizeof(*adaptew->tx_wing), GFP_KEWNEW);
	if (!adaptew->tx_wing)
		wetuwn -ENOMEM;

	adaptew->wx_wing = devm_kzawwoc(&adaptew->pdev->dev,
					sizeof(*adaptew->wx_wing), GFP_KEWNEW);
	if (!adaptew->wx_wing)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/**
 * pch_gbe_init_stats - Initiawize status
 * @adaptew:  Boawd pwivate stwuctuwe to initiawize
 */
static void pch_gbe_init_stats(stwuct pch_gbe_adaptew *adaptew)
{
	memset(&adaptew->stats, 0, sizeof(adaptew->stats));
	wetuwn;
}

/**
 * pch_gbe_init_phy - Initiawize PHY
 * @adaptew:  Boawd pwivate stwuctuwe to initiawize
 * Wetuwns:
 *	0:	Successfuwwy
 *	Negative vawue:	Faiwed
 */
static int pch_gbe_init_phy(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	u32 addw;
	u16 bmcw, stat;

	/* Discovew phy addw by seawching addws in owdew {1,0,2,..., 31} */
	fow (addw = 0; addw < PCH_GBE_PHY_WEGS_WEN; addw++) {
		adaptew->mii.phy_id = (addw == 0) ? 1 : (addw == 1) ? 0 : addw;
		bmcw = pch_gbe_mdio_wead(netdev, adaptew->mii.phy_id, MII_BMCW);
		stat = pch_gbe_mdio_wead(netdev, adaptew->mii.phy_id, MII_BMSW);
		stat = pch_gbe_mdio_wead(netdev, adaptew->mii.phy_id, MII_BMSW);
		if (!((bmcw == 0xFFFF) || ((stat == 0) && (bmcw == 0))))
			bweak;
	}
	adaptew->hw.phy.addw = adaptew->mii.phy_id;
	netdev_dbg(netdev, "phy_addw = %d\n", adaptew->mii.phy_id);
	if (addw == PCH_GBE_PHY_WEGS_WEN)
		wetuwn -EAGAIN;
	/* Sewected the phy and isowate the west */
	fow (addw = 0; addw < PCH_GBE_PHY_WEGS_WEN; addw++) {
		if (addw != adaptew->mii.phy_id) {
			pch_gbe_mdio_wwite(netdev, addw, MII_BMCW,
					   BMCW_ISOWATE);
		} ewse {
			bmcw = pch_gbe_mdio_wead(netdev, addw, MII_BMCW);
			pch_gbe_mdio_wwite(netdev, addw, MII_BMCW,
					   bmcw & ~BMCW_ISOWATE);
		}
	}

	/* MII setup */
	adaptew->mii.phy_id_mask = 0x1F;
	adaptew->mii.weg_num_mask = 0x1F;
	adaptew->mii.dev = adaptew->netdev;
	adaptew->mii.mdio_wead = pch_gbe_mdio_wead;
	adaptew->mii.mdio_wwite = pch_gbe_mdio_wwite;
	adaptew->mii.suppowts_gmii = mii_check_gmii_suppowt(&adaptew->mii);
	wetuwn 0;
}

/**
 * pch_gbe_mdio_wead - The wead function fow mii
 * @netdev: Netwowk intewface device stwuctuwe
 * @addw:   Phy ID
 * @weg:    Access wocation
 * Wetuwns:
 *	0:	Successfuwwy
 *	Negative vawue:	Faiwed
 */
static int pch_gbe_mdio_wead(stwuct net_device *netdev, int addw, int weg)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;

	wetuwn pch_gbe_mac_ctww_miim(hw, addw, PCH_GBE_HAW_MIIM_WEAD, weg,
				     (u16) 0);
}

/**
 * pch_gbe_mdio_wwite - The wwite function fow mii
 * @netdev: Netwowk intewface device stwuctuwe
 * @addw:   Phy ID (not used)
 * @weg:    Access wocation
 * @data:   Wwite data
 */
static void pch_gbe_mdio_wwite(stwuct net_device *netdev,
			       int addw, int weg, int data)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;

	pch_gbe_mac_ctww_miim(hw, addw, PCH_GBE_HAW_MIIM_WWITE, weg, data);
}

/**
 * pch_gbe_weset_task - Weset pwocessing at the time of twansmission timeout
 * @wowk:  Pointew of boawd pwivate stwuctuwe
 */
static void pch_gbe_weset_task(stwuct wowk_stwuct *wowk)
{
	stwuct pch_gbe_adaptew *adaptew;
	adaptew = containew_of(wowk, stwuct pch_gbe_adaptew, weset_task);

	wtnw_wock();
	pch_gbe_weinit_wocked(adaptew);
	wtnw_unwock();
}

/**
 * pch_gbe_weinit_wocked- We-initiawization
 * @adaptew:  Boawd pwivate stwuctuwe
 */
void pch_gbe_weinit_wocked(stwuct pch_gbe_adaptew *adaptew)
{
	pch_gbe_down(adaptew);
	pch_gbe_up(adaptew);
}

/**
 * pch_gbe_weset - Weset GbE
 * @adaptew:  Boawd pwivate stwuctuwe
 */
void pch_gbe_weset(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	s32 wet_vaw;

	pch_gbe_mac_weset_hw(hw);
	/* wepwogwam muwticast addwess wegistew aftew weset */
	pch_gbe_set_muwti(netdev);
	/* Setup the weceive addwess. */
	pch_gbe_mac_init_wx_addws(hw, PCH_GBE_MAW_ENTWIES);

	wet_vaw = pch_gbe_phy_get_id(hw);
	if (wet_vaw) {
		netdev_eww(adaptew->netdev, "pch_gbe_phy_get_id ewwow\n");
		wetuwn;
	}
	pch_gbe_phy_init_setting(hw);
	/* Setup Mac intewface option WGMII */
	pch_gbe_phy_set_wgmii(hw);
}

/**
 * pch_gbe_fwee_iwq - Fwee an intewwupt
 * @adaptew:  Boawd pwivate stwuctuwe
 */
static void pch_gbe_fwee_iwq(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;

	fwee_iwq(adaptew->iwq, netdev);
	pci_fwee_iwq_vectows(adaptew->pdev);
}

/**
 * pch_gbe_iwq_disabwe - Mask off intewwupt genewation on the NIC
 * @adaptew:  Boawd pwivate stwuctuwe
 */
static void pch_gbe_iwq_disabwe(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;

	atomic_inc(&adaptew->iwq_sem);
	iowwite32(0, &hw->weg->INT_EN);
	iowead32(&hw->weg->INT_ST);
	synchwonize_iwq(adaptew->iwq);

	netdev_dbg(adaptew->netdev, "INT_EN weg : 0x%08x\n",
		   iowead32(&hw->weg->INT_EN));
}

/**
 * pch_gbe_iwq_enabwe - Enabwe defauwt intewwupt genewation settings
 * @adaptew:  Boawd pwivate stwuctuwe
 */
static void pch_gbe_iwq_enabwe(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;

	if (wikewy(atomic_dec_and_test(&adaptew->iwq_sem)))
		iowwite32(PCH_GBE_INT_ENABWE_MASK, &hw->weg->INT_EN);
	iowead32(&hw->weg->INT_ST);
	netdev_dbg(adaptew->netdev, "INT_EN weg : 0x%08x\n",
		   iowead32(&hw->weg->INT_EN));
}



/**
 * pch_gbe_setup_tctw - configuwe the Twansmit contwow wegistews
 * @adaptew:  Boawd pwivate stwuctuwe
 */
static void pch_gbe_setup_tctw(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	u32 tx_mode, tcpip;

	tx_mode = PCH_GBE_TM_WONG_PKT |
		PCH_GBE_TM_ST_AND_FD |
		PCH_GBE_TM_SHOWT_PKT |
		PCH_GBE_TM_TH_TX_STWT_8 |
		PCH_GBE_TM_TH_AWM_EMP_4 | PCH_GBE_TM_TH_AWM_FUWW_8;

	iowwite32(tx_mode, &hw->weg->TX_MODE);

	tcpip = iowead32(&hw->weg->TCPIP_ACC);
	tcpip |= PCH_GBE_TX_TCPIPACC_EN;
	iowwite32(tcpip, &hw->weg->TCPIP_ACC);
	wetuwn;
}

/**
 * pch_gbe_configuwe_tx - Configuwe Twansmit Unit aftew Weset
 * @adaptew:  Boawd pwivate stwuctuwe
 */
static void pch_gbe_configuwe_tx(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	u32 tdba, tdwen, dctww;

	netdev_dbg(adaptew->netdev, "dma addw = 0x%08wwx  size = 0x%08x\n",
		   (unsigned wong wong)adaptew->tx_wing->dma,
		   adaptew->tx_wing->size);

	/* Setup the HW Tx Head and Taiw descwiptow pointews */
	tdba = adaptew->tx_wing->dma;
	tdwen = adaptew->tx_wing->size - 0x10;
	iowwite32(tdba, &hw->weg->TX_DSC_BASE);
	iowwite32(tdwen, &hw->weg->TX_DSC_SIZE);
	iowwite32(tdba, &hw->weg->TX_DSC_SW_P);

	/* Enabwes Twansmission DMA */
	dctww = iowead32(&hw->weg->DMA_CTWW);
	dctww |= PCH_GBE_TX_DMA_EN;
	iowwite32(dctww, &hw->weg->DMA_CTWW);
}

/**
 * pch_gbe_setup_wctw - Configuwe the weceive contwow wegistews
 * @adaptew:  Boawd pwivate stwuctuwe
 */
static void pch_gbe_setup_wctw(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	u32 wx_mode, tcpip;

	wx_mode = PCH_GBE_ADD_FIW_EN | PCH_GBE_MWT_FIW_EN |
	PCH_GBE_WH_AWM_EMP_4 | PCH_GBE_WH_AWM_FUWW_4 | PCH_GBE_WH_WD_TWG_8;

	iowwite32(wx_mode, &hw->weg->WX_MODE);

	tcpip = iowead32(&hw->weg->TCPIP_ACC);

	tcpip |= PCH_GBE_WX_TCPIPACC_OFF;
	tcpip &= ~PCH_GBE_WX_TCPIPACC_EN;
	iowwite32(tcpip, &hw->weg->TCPIP_ACC);
	wetuwn;
}

/**
 * pch_gbe_configuwe_wx - Configuwe Weceive Unit aftew Weset
 * @adaptew:  Boawd pwivate stwuctuwe
 */
static void pch_gbe_configuwe_wx(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	u32 wdba, wdwen, wxdma;

	netdev_dbg(adaptew->netdev, "dma adw = 0x%08wwx  size = 0x%08x\n",
		   (unsigned wong wong)adaptew->wx_wing->dma,
		   adaptew->wx_wing->size);

	pch_gbe_mac_fowce_mac_fc(hw);

	pch_gbe_disabwe_mac_wx(hw);

	/* Disabwes Weceive DMA */
	wxdma = iowead32(&hw->weg->DMA_CTWW);
	wxdma &= ~PCH_GBE_WX_DMA_EN;
	iowwite32(wxdma, &hw->weg->DMA_CTWW);

	netdev_dbg(adaptew->netdev,
		   "MAC_WX_EN weg = 0x%08x  DMA_CTWW weg = 0x%08x\n",
		   iowead32(&hw->weg->MAC_WX_EN),
		   iowead32(&hw->weg->DMA_CTWW));

	/* Setup the HW Wx Head and Taiw Descwiptow Pointews and
	 * the Base and Wength of the Wx Descwiptow Wing */
	wdba = adaptew->wx_wing->dma;
	wdwen = adaptew->wx_wing->size - 0x10;
	iowwite32(wdba, &hw->weg->WX_DSC_BASE);
	iowwite32(wdwen, &hw->weg->WX_DSC_SIZE);
	iowwite32((wdba + wdwen), &hw->weg->WX_DSC_SW_P);
}

/**
 * pch_gbe_unmap_and_fwee_tx_wesouwce - Unmap and fwee tx socket buffew
 * @adaptew:     Boawd pwivate stwuctuwe
 * @buffew_info: Buffew infowmation stwuctuwe
 */
static void pch_gbe_unmap_and_fwee_tx_wesouwce(
	stwuct pch_gbe_adaptew *adaptew, stwuct pch_gbe_buffew *buffew_info)
{
	if (buffew_info->mapped) {
		dma_unmap_singwe(&adaptew->pdev->dev, buffew_info->dma,
				 buffew_info->wength, DMA_TO_DEVICE);
		buffew_info->mapped = fawse;
	}
	if (buffew_info->skb) {
		dev_kfwee_skb_any(buffew_info->skb);
		buffew_info->skb = NUWW;
	}
}

/**
 * pch_gbe_unmap_and_fwee_wx_wesouwce - Unmap and fwee wx socket buffew
 * @adaptew:      Boawd pwivate stwuctuwe
 * @buffew_info:  Buffew infowmation stwuctuwe
 */
static void pch_gbe_unmap_and_fwee_wx_wesouwce(
					stwuct pch_gbe_adaptew *adaptew,
					stwuct pch_gbe_buffew *buffew_info)
{
	if (buffew_info->mapped) {
		dma_unmap_singwe(&adaptew->pdev->dev, buffew_info->dma,
				 buffew_info->wength, DMA_FWOM_DEVICE);
		buffew_info->mapped = fawse;
	}
	if (buffew_info->skb) {
		dev_kfwee_skb_any(buffew_info->skb);
		buffew_info->skb = NUWW;
	}
}

/**
 * pch_gbe_cwean_tx_wing - Fwee Tx Buffews
 * @adaptew:  Boawd pwivate stwuctuwe
 * @tx_wing:  Wing to be cweaned
 */
static void pch_gbe_cwean_tx_wing(stwuct pch_gbe_adaptew *adaptew,
				   stwuct pch_gbe_tx_wing *tx_wing)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	stwuct pch_gbe_buffew *buffew_info;
	unsigned wong size;
	unsigned int i;

	/* Fwee aww the Tx wing sk_buffs */
	fow (i = 0; i < tx_wing->count; i++) {
		buffew_info = &tx_wing->buffew_info[i];
		pch_gbe_unmap_and_fwee_tx_wesouwce(adaptew, buffew_info);
	}
	netdev_dbg(adaptew->netdev,
		   "caww pch_gbe_unmap_and_fwee_tx_wesouwce() %d count\n", i);

	size = (unsigned wong)sizeof(stwuct pch_gbe_buffew) * tx_wing->count;
	memset(tx_wing->buffew_info, 0, size);

	/* Zewo out the descwiptow wing */
	memset(tx_wing->desc, 0, tx_wing->size);
	tx_wing->next_to_use = 0;
	tx_wing->next_to_cwean = 0;
	iowwite32(tx_wing->dma, &hw->weg->TX_DSC_HW_P);
	iowwite32((tx_wing->size - 0x10), &hw->weg->TX_DSC_SIZE);
}

/**
 * pch_gbe_cwean_wx_wing - Fwee Wx Buffews
 * @adaptew:  Boawd pwivate stwuctuwe
 * @wx_wing:  Wing to fwee buffews fwom
 */
static void
pch_gbe_cwean_wx_wing(stwuct pch_gbe_adaptew *adaptew,
		      stwuct pch_gbe_wx_wing *wx_wing)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	stwuct pch_gbe_buffew *buffew_info;
	unsigned wong size;
	unsigned int i;

	/* Fwee aww the Wx wing sk_buffs */
	fow (i = 0; i < wx_wing->count; i++) {
		buffew_info = &wx_wing->buffew_info[i];
		pch_gbe_unmap_and_fwee_wx_wesouwce(adaptew, buffew_info);
	}
	netdev_dbg(adaptew->netdev,
		   "caww pch_gbe_unmap_and_fwee_wx_wesouwce() %d count\n", i);
	size = (unsigned wong)sizeof(stwuct pch_gbe_buffew) * wx_wing->count;
	memset(wx_wing->buffew_info, 0, size);

	/* Zewo out the descwiptow wing */
	memset(wx_wing->desc, 0, wx_wing->size);
	wx_wing->next_to_cwean = 0;
	wx_wing->next_to_use = 0;
	iowwite32(wx_wing->dma, &hw->weg->WX_DSC_HW_P);
	iowwite32((wx_wing->size - 0x10), &hw->weg->WX_DSC_SIZE);
}

static void pch_gbe_set_wgmii_ctww(stwuct pch_gbe_adaptew *adaptew, u16 speed,
				    u16 dupwex)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	unsigned wong wgmii = 0;

	/* Set the WGMII contwow. */
	switch (speed) {
	case SPEED_10:
		wgmii = (PCH_GBE_WGMII_WATE_2_5M |
			 PCH_GBE_MAC_WGMII_CTWW_SETTING);
		bweak;
	case SPEED_100:
		wgmii = (PCH_GBE_WGMII_WATE_25M |
			 PCH_GBE_MAC_WGMII_CTWW_SETTING);
		bweak;
	case SPEED_1000:
		wgmii = (PCH_GBE_WGMII_WATE_125M |
			 PCH_GBE_MAC_WGMII_CTWW_SETTING);
		bweak;
	}
	iowwite32(wgmii, &hw->weg->WGMII_CTWW);
}
static void pch_gbe_set_mode(stwuct pch_gbe_adaptew *adaptew, u16 speed,
			      u16 dupwex)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	unsigned wong mode = 0;

	/* Set the communication mode */
	switch (speed) {
	case SPEED_10:
		mode = PCH_GBE_MODE_MII_ETHEW;
		netdev->tx_queue_wen = 10;
		bweak;
	case SPEED_100:
		mode = PCH_GBE_MODE_MII_ETHEW;
		netdev->tx_queue_wen = 100;
		bweak;
	case SPEED_1000:
		mode = PCH_GBE_MODE_GMII_ETHEW;
		bweak;
	}
	if (dupwex == DUPWEX_FUWW)
		mode |= PCH_GBE_MODE_FUWW_DUPWEX;
	ewse
		mode |= PCH_GBE_MODE_HAWF_DUPWEX;
	iowwite32(mode, &hw->weg->MODE);
}

/**
 * pch_gbe_watchdog - Watchdog pwocess
 * @t:  timew wist containing a Boawd pwivate stwuctuwe
 */
static void pch_gbe_watchdog(stwuct timew_wist *t)
{
	stwuct pch_gbe_adaptew *adaptew = fwom_timew(adaptew, t,
						     watchdog_timew);
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pch_gbe_hw *hw = &adaptew->hw;

	netdev_dbg(netdev, "wight now = %wd\n", jiffies);

	pch_gbe_update_stats(adaptew);
	if ((mii_wink_ok(&adaptew->mii)) && (!netif_cawwiew_ok(netdev))) {
		stwuct ethtoow_cmd cmd = { .cmd = ETHTOOW_GSET };
		netdev->tx_queue_wen = adaptew->tx_queue_wen;
		/* mii wibwawy handwes wink maintenance tasks */
		mii_ethtoow_gset(&adaptew->mii, &cmd);
		hw->mac.wink_speed = ethtoow_cmd_speed(&cmd);
		hw->mac.wink_dupwex = cmd.dupwex;
		/* Set the WGMII contwow. */
		pch_gbe_set_wgmii_ctww(adaptew, hw->mac.wink_speed,
						hw->mac.wink_dupwex);
		/* Set the communication mode */
		pch_gbe_set_mode(adaptew, hw->mac.wink_speed,
				 hw->mac.wink_dupwex);
		netdev_dbg(netdev,
			   "Wink is Up %d Mbps %s-Dupwex\n",
			   hw->mac.wink_speed,
			   cmd.dupwex == DUPWEX_FUWW ? "Fuww" : "Hawf");
		netif_cawwiew_on(netdev);
		netif_wake_queue(netdev);
	} ewse if ((!mii_wink_ok(&adaptew->mii)) &&
		   (netif_cawwiew_ok(netdev))) {
		netdev_dbg(netdev, "NIC Wink is Down\n");
		hw->mac.wink_speed = SPEED_10;
		hw->mac.wink_dupwex = DUPWEX_HAWF;
		netif_cawwiew_off(netdev);
		netif_stop_queue(netdev);
	}
	mod_timew(&adaptew->watchdog_timew,
		  wound_jiffies(jiffies + PCH_GBE_WATCHDOG_PEWIOD));
}

/**
 * pch_gbe_tx_queue - Cawwy out queuing of the twansmission data
 * @adaptew:  Boawd pwivate stwuctuwe
 * @tx_wing:  Tx descwiptow wing stwuctuwe
 * @skb:      Sockt buffew stwuctuwe
 */
static void pch_gbe_tx_queue(stwuct pch_gbe_adaptew *adaptew,
			      stwuct pch_gbe_tx_wing *tx_wing,
			      stwuct sk_buff *skb)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	stwuct pch_gbe_tx_desc *tx_desc;
	stwuct pch_gbe_buffew *buffew_info;
	stwuct sk_buff *tmp_skb;
	unsigned int fwame_ctww;
	unsigned int wing_num;

	/*-- Set fwame contwow --*/
	fwame_ctww = 0;
	if (unwikewy(skb->wen < PCH_GBE_SHOWT_PKT))
		fwame_ctww |= PCH_GBE_TXD_CTWW_APAD;
	if (skb->ip_summed == CHECKSUM_NONE)
		fwame_ctww |= PCH_GBE_TXD_CTWW_TCPIP_ACC_OFF;

	/* Pewfowms checksum pwocessing */
	/*
	 * It is because the hawdwawe accewewatow does not suppowt a checksum,
	 * when the weceived data size is wess than 64 bytes.
	 */
	if (skb->wen < PCH_GBE_SHOWT_PKT && skb->ip_summed != CHECKSUM_NONE) {
		fwame_ctww |= PCH_GBE_TXD_CTWW_APAD |
			      PCH_GBE_TXD_CTWW_TCPIP_ACC_OFF;
		if (skb->pwotocow == htons(ETH_P_IP)) {
			stwuct iphdw *iph = ip_hdw(skb);
			unsigned int offset;
			offset = skb_twanspowt_offset(skb);
			if (iph->pwotocow == IPPWOTO_TCP) {
				skb->csum = 0;
				tcp_hdw(skb)->check = 0;
				skb->csum = skb_checksum(skb, offset,
							 skb->wen - offset, 0);
				tcp_hdw(skb)->check =
					csum_tcpudp_magic(iph->saddw,
							  iph->daddw,
							  skb->wen - offset,
							  IPPWOTO_TCP,
							  skb->csum);
			} ewse if (iph->pwotocow == IPPWOTO_UDP) {
				skb->csum = 0;
				udp_hdw(skb)->check = 0;
				skb->csum =
					skb_checksum(skb, offset,
						     skb->wen - offset, 0);
				udp_hdw(skb)->check =
					csum_tcpudp_magic(iph->saddw,
							  iph->daddw,
							  skb->wen - offset,
							  IPPWOTO_UDP,
							  skb->csum);
			}
		}
	}

	wing_num = tx_wing->next_to_use;
	if (unwikewy((wing_num + 1) == tx_wing->count))
		tx_wing->next_to_use = 0;
	ewse
		tx_wing->next_to_use = wing_num + 1;


	buffew_info = &tx_wing->buffew_info[wing_num];
	tmp_skb = buffew_info->skb;

	/* [Headew:14][paywoad] ---> [Headew:14][paddong:2][paywoad]    */
	memcpy(tmp_skb->data, skb->data, ETH_HWEN);
	tmp_skb->data[ETH_HWEN] = 0x00;
	tmp_skb->data[ETH_HWEN + 1] = 0x00;
	tmp_skb->wen = skb->wen;
	memcpy(&tmp_skb->data[ETH_HWEN + 2], &skb->data[ETH_HWEN],
	       (skb->wen - ETH_HWEN));
	/*-- Set Buffew infowmation --*/
	buffew_info->wength = tmp_skb->wen;
	buffew_info->dma = dma_map_singwe(&adaptew->pdev->dev, tmp_skb->data,
					  buffew_info->wength,
					  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&adaptew->pdev->dev, buffew_info->dma)) {
		netdev_eww(adaptew->netdev, "TX DMA map faiwed\n");
		buffew_info->dma = 0;
		buffew_info->time_stamp = 0;
		tx_wing->next_to_use = wing_num;
		dev_kfwee_skb_any(skb);
		wetuwn;
	}
	buffew_info->mapped = twue;
	buffew_info->time_stamp = jiffies;

	/*-- Set Tx descwiptow --*/
	tx_desc = PCH_GBE_TX_DESC(*tx_wing, wing_num);
	tx_desc->buffew_addw = (buffew_info->dma);
	tx_desc->wength = (tmp_skb->wen);
	tx_desc->tx_wowds_eob = ((tmp_skb->wen + 3));
	tx_desc->tx_fwame_ctww = (fwame_ctww);
	tx_desc->gbec_status = (DSC_INIT16);

	if (unwikewy(++wing_num == tx_wing->count))
		wing_num = 0;

	/* Update softwawe pointew of TX descwiptow */
	iowwite32(tx_wing->dma +
		  (int)sizeof(stwuct pch_gbe_tx_desc) * wing_num,
		  &hw->weg->TX_DSC_SW_P);

	pch_tx_timestamp(adaptew, skb);

	dev_kfwee_skb_any(skb);
}

/**
 * pch_gbe_update_stats - Update the boawd statistics countews
 * @adaptew:  Boawd pwivate stwuctuwe
 */
void pch_gbe_update_stats(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct pch_gbe_hw_stats *stats = &adaptew->stats;
	unsigned wong fwags;

	/*
	 * Pwevent stats update whiwe adaptew is being weset, ow if the pci
	 * connection is down.
	 */
	if ((pdev->ewwow_state) && (pdev->ewwow_state != pci_channew_io_nowmaw))
		wetuwn;

	spin_wock_iwqsave(&adaptew->stats_wock, fwags);

	/* Update device status "adaptew->stats" */
	stats->wx_ewwows = stats->wx_cwc_ewwows + stats->wx_fwame_ewwows;
	stats->tx_ewwows = stats->tx_wength_ewwows +
	    stats->tx_abowted_ewwows +
	    stats->tx_cawwiew_ewwows + stats->tx_timeout_count;

	/* Update netwowk device status "adaptew->net_stats" */
	netdev->stats.wx_packets = stats->wx_packets;
	netdev->stats.wx_bytes = stats->wx_bytes;
	netdev->stats.wx_dwopped = stats->wx_dwopped;
	netdev->stats.tx_packets = stats->tx_packets;
	netdev->stats.tx_bytes = stats->tx_bytes;
	netdev->stats.tx_dwopped = stats->tx_dwopped;
	/* Fiww out the OS statistics stwuctuwe */
	netdev->stats.muwticast = stats->muwticast;
	netdev->stats.cowwisions = stats->cowwisions;
	/* Wx Ewwows */
	netdev->stats.wx_ewwows = stats->wx_ewwows;
	netdev->stats.wx_cwc_ewwows = stats->wx_cwc_ewwows;
	netdev->stats.wx_fwame_ewwows = stats->wx_fwame_ewwows;
	/* Tx Ewwows */
	netdev->stats.tx_ewwows = stats->tx_ewwows;
	netdev->stats.tx_abowted_ewwows = stats->tx_abowted_ewwows;
	netdev->stats.tx_cawwiew_ewwows = stats->tx_cawwiew_ewwows;

	spin_unwock_iwqwestowe(&adaptew->stats_wock, fwags);
}

static void pch_gbe_disabwe_dma_wx(stwuct pch_gbe_hw *hw)
{
	u32 wxdma;

	/* Disabwe Weceive DMA */
	wxdma = iowead32(&hw->weg->DMA_CTWW);
	wxdma &= ~PCH_GBE_WX_DMA_EN;
	iowwite32(wxdma, &hw->weg->DMA_CTWW);
}

static void pch_gbe_enabwe_dma_wx(stwuct pch_gbe_hw *hw)
{
	u32 wxdma;

	/* Enabwes Weceive DMA */
	wxdma = iowead32(&hw->weg->DMA_CTWW);
	wxdma |= PCH_GBE_WX_DMA_EN;
	iowwite32(wxdma, &hw->weg->DMA_CTWW);
}

/**
 * pch_gbe_intw - Intewwupt Handwew
 * @iwq:   Intewwupt numbew
 * @data:  Pointew to a netwowk intewface device stwuctuwe
 * Wetuwns:
 *	- IWQ_HANDWED:	Ouw intewwupt
 *	- IWQ_NONE:	Not ouw intewwupt
 */
static iwqwetuwn_t pch_gbe_intw(int iwq, void *data)
{
	stwuct net_device *netdev = data;
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	u32 int_st;
	u32 int_en;

	/* Check wequest status */
	int_st = iowead32(&hw->weg->INT_ST);
	int_st = int_st & iowead32(&hw->weg->INT_EN);
	/* When wequest status is no intewwuption factow */
	if (unwikewy(!int_st))
		wetuwn IWQ_NONE;	/* Not ouw intewwupt. End pwocessing. */
	netdev_dbg(netdev, "%s occuw int_st = 0x%08x\n", __func__, int_st);
	if (int_st & PCH_GBE_INT_WX_FWAME_EWW)
		adaptew->stats.intw_wx_fwame_eww_count++;
	if (int_st & PCH_GBE_INT_WX_FIFO_EWW)
		if (!adaptew->wx_stop_fwag) {
			adaptew->stats.intw_wx_fifo_eww_count++;
			netdev_dbg(netdev, "Wx fifo ovew wun\n");
			adaptew->wx_stop_fwag = twue;
			int_en = iowead32(&hw->weg->INT_EN);
			iowwite32((int_en & ~PCH_GBE_INT_WX_FIFO_EWW),
				  &hw->weg->INT_EN);
			pch_gbe_disabwe_dma_wx(&adaptew->hw);
			int_st |= iowead32(&hw->weg->INT_ST);
			int_st = int_st & iowead32(&hw->weg->INT_EN);
		}
	if (int_st & PCH_GBE_INT_WX_DMA_EWW)
		adaptew->stats.intw_wx_dma_eww_count++;
	if (int_st & PCH_GBE_INT_TX_FIFO_EWW)
		adaptew->stats.intw_tx_fifo_eww_count++;
	if (int_st & PCH_GBE_INT_TX_DMA_EWW)
		adaptew->stats.intw_tx_dma_eww_count++;
	if (int_st & PCH_GBE_INT_TCPIP_EWW)
		adaptew->stats.intw_tcpip_eww_count++;
	/* When Wx descwiptow is empty  */
	if ((int_st & PCH_GBE_INT_WX_DSC_EMP)) {
		adaptew->stats.intw_wx_dsc_empty_count++;
		netdev_dbg(netdev, "Wx descwiptow is empty\n");
		int_en = iowead32(&hw->weg->INT_EN);
		iowwite32((int_en & ~PCH_GBE_INT_WX_DSC_EMP), &hw->weg->INT_EN);
		if (hw->mac.tx_fc_enabwe) {
			/* Set Pause packet */
			pch_gbe_mac_set_pause_packet(hw);
		}
	}

	/* When wequest status is Weceive intewwuption */
	if ((int_st & (PCH_GBE_INT_WX_DMA_CMPWT | PCH_GBE_INT_TX_CMPWT)) ||
	    (adaptew->wx_stop_fwag)) {
		if (wikewy(napi_scheduwe_pwep(&adaptew->napi))) {
			/* Enabwe onwy Wx Descwiptow empty */
			atomic_inc(&adaptew->iwq_sem);
			int_en = iowead32(&hw->weg->INT_EN);
			int_en &=
			    ~(PCH_GBE_INT_WX_DMA_CMPWT | PCH_GBE_INT_TX_CMPWT);
			iowwite32(int_en, &hw->weg->INT_EN);
			/* Stawt powwing fow NAPI */
			__napi_scheduwe(&adaptew->napi);
		}
	}
	netdev_dbg(netdev, "wetuwn = 0x%08x  INT_EN weg = 0x%08x\n",
		   IWQ_HANDWED, iowead32(&hw->weg->INT_EN));
	wetuwn IWQ_HANDWED;
}

/**
 * pch_gbe_awwoc_wx_buffews - Wepwace used weceive buffews; wegacy & extended
 * @adaptew:       Boawd pwivate stwuctuwe
 * @wx_wing:       Wx descwiptow wing
 * @cweaned_count: Cweaned count
 */
static void
pch_gbe_awwoc_wx_buffews(stwuct pch_gbe_adaptew *adaptew,
			 stwuct pch_gbe_wx_wing *wx_wing, int cweaned_count)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	stwuct pch_gbe_wx_desc *wx_desc;
	stwuct pch_gbe_buffew *buffew_info;
	stwuct sk_buff *skb;
	unsigned int i;
	unsigned int bufsz;

	bufsz = adaptew->wx_buffew_wen + NET_IP_AWIGN;
	i = wx_wing->next_to_use;

	whiwe ((cweaned_count--)) {
		buffew_info = &wx_wing->buffew_info[i];
		skb = netdev_awwoc_skb(netdev, bufsz);
		if (unwikewy(!skb)) {
			/* Bettew wuck next wound */
			adaptew->stats.wx_awwoc_buff_faiwed++;
			bweak;
		}
		/* awign */
		skb_wesewve(skb, NET_IP_AWIGN);
		buffew_info->skb = skb;

		buffew_info->dma = dma_map_singwe(&pdev->dev,
						  buffew_info->wx_buffew,
						  buffew_info->wength,
						  DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(&adaptew->pdev->dev, buffew_info->dma)) {
			dev_kfwee_skb(skb);
			buffew_info->skb = NUWW;
			buffew_info->dma = 0;
			adaptew->stats.wx_awwoc_buff_faiwed++;
			bweak; /* whiwe !buffew_info->skb */
		}
		buffew_info->mapped = twue;
		wx_desc = PCH_GBE_WX_DESC(*wx_wing, i);
		wx_desc->buffew_addw = (buffew_info->dma);
		wx_desc->gbec_status = DSC_INIT16;

		netdev_dbg(netdev,
			   "i = %d  buffew_info->dma = 0x08%wwx  buffew_info->wength = 0x%x\n",
			   i, (unsigned wong wong)buffew_info->dma,
			   buffew_info->wength);

		if (unwikewy(++i == wx_wing->count))
			i = 0;
	}
	if (wikewy(wx_wing->next_to_use != i)) {
		wx_wing->next_to_use = i;
		if (unwikewy(i-- == 0))
			i = (wx_wing->count - 1);
		iowwite32(wx_wing->dma +
			  (int)sizeof(stwuct pch_gbe_wx_desc) * i,
			  &hw->weg->WX_DSC_SW_P);
	}
	wetuwn;
}

static int
pch_gbe_awwoc_wx_buffews_poow(stwuct pch_gbe_adaptew *adaptew,
			 stwuct pch_gbe_wx_wing *wx_wing, int cweaned_count)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct pch_gbe_buffew *buffew_info;
	unsigned int i;
	unsigned int bufsz;
	unsigned int size;

	bufsz = adaptew->wx_buffew_wen;

	size = wx_wing->count * bufsz + PCH_GBE_WESEWVE_MEMOWY;
	wx_wing->wx_buff_poow =
		dma_awwoc_cohewent(&pdev->dev, size,
				   &wx_wing->wx_buff_poow_wogic, GFP_KEWNEW);
	if (!wx_wing->wx_buff_poow)
		wetuwn -ENOMEM;

	wx_wing->wx_buff_poow_size = size;
	fow (i = 0; i < wx_wing->count; i++) {
		buffew_info = &wx_wing->buffew_info[i];
		buffew_info->wx_buffew = wx_wing->wx_buff_poow + bufsz * i;
		buffew_info->wength = bufsz;
	}
	wetuwn 0;
}

/**
 * pch_gbe_awwoc_tx_buffews - Awwocate twansmit buffews
 * @adaptew:   Boawd pwivate stwuctuwe
 * @tx_wing:   Tx descwiptow wing
 */
static void pch_gbe_awwoc_tx_buffews(stwuct pch_gbe_adaptew *adaptew,
					stwuct pch_gbe_tx_wing *tx_wing)
{
	stwuct pch_gbe_buffew *buffew_info;
	stwuct sk_buff *skb;
	unsigned int i;
	unsigned int bufsz;
	stwuct pch_gbe_tx_desc *tx_desc;

	bufsz =
	    adaptew->hw.mac.max_fwame_size + PCH_GBE_DMA_AWIGN + NET_IP_AWIGN;

	fow (i = 0; i < tx_wing->count; i++) {
		buffew_info = &tx_wing->buffew_info[i];
		skb = netdev_awwoc_skb(adaptew->netdev, bufsz);
		skb_wesewve(skb, PCH_GBE_DMA_AWIGN);
		buffew_info->skb = skb;
		tx_desc = PCH_GBE_TX_DESC(*tx_wing, i);
		tx_desc->gbec_status = (DSC_INIT16);
	}
	wetuwn;
}

/**
 * pch_gbe_cwean_tx - Wecwaim wesouwces aftew twansmit compwetes
 * @adaptew:   Boawd pwivate stwuctuwe
 * @tx_wing:   Tx descwiptow wing
 * Wetuwns:
 *	twue:  Cweaned the descwiptow
 *	fawse: Not cweaned the descwiptow
 */
static boow
pch_gbe_cwean_tx(stwuct pch_gbe_adaptew *adaptew,
		 stwuct pch_gbe_tx_wing *tx_wing)
{
	stwuct pch_gbe_tx_desc *tx_desc;
	stwuct pch_gbe_buffew *buffew_info;
	stwuct sk_buff *skb;
	unsigned int i;
	unsigned int cweaned_count = 0;
	boow cweaned = fawse;
	int unused, thwesh;

	netdev_dbg(adaptew->netdev, "next_to_cwean : %d\n",
		   tx_wing->next_to_cwean);

	i = tx_wing->next_to_cwean;
	tx_desc = PCH_GBE_TX_DESC(*tx_wing, i);
	netdev_dbg(adaptew->netdev, "gbec_status:0x%04x  dma_status:0x%04x\n",
		   tx_desc->gbec_status, tx_desc->dma_status);

	unused = PCH_GBE_DESC_UNUSED(tx_wing);
	thwesh = tx_wing->count - NAPI_POWW_WEIGHT;
	if ((tx_desc->gbec_status == DSC_INIT16) && (unused < thwesh))
	{  /* cuwwent mawked cwean, tx queue fiwwing up, do extwa cwean */
		int j, k;
		if (unused < 8) {  /* tx queue neawwy fuww */
			netdev_dbg(adaptew->netdev,
				   "cwean_tx: twansmit queue wawning (%x,%x) unused=%d\n",
				   tx_wing->next_to_cwean, tx_wing->next_to_use,
				   unused);
		}

		/* cuwwent mawked cwean, scan fow mowe that need cweaning. */
		k = i;
		fow (j = 0; j < NAPI_POWW_WEIGHT; j++)
		{
			tx_desc = PCH_GBE_TX_DESC(*tx_wing, k);
			if (tx_desc->gbec_status != DSC_INIT16) bweak; /*found*/
			if (++k >= tx_wing->count) k = 0;  /*incwement, wwap*/
		}
		if (j < NAPI_POWW_WEIGHT) {
			netdev_dbg(adaptew->netdev,
				   "cwean_tx: unused=%d woops=%d found tx_desc[%x,%x:%x].gbec_status=%04x\n",
				   unused, j, i, k, tx_wing->next_to_use,
				   tx_desc->gbec_status);
			i = k;  /*found one to cwean, usu gbec_status==2000.*/
		}
	}

	whiwe ((tx_desc->gbec_status & DSC_INIT16) == 0x0000) {
		netdev_dbg(adaptew->netdev, "gbec_status:0x%04x\n",
			   tx_desc->gbec_status);
		buffew_info = &tx_wing->buffew_info[i];
		skb = buffew_info->skb;
		cweaned = twue;

		if ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_ABT)) {
			adaptew->stats.tx_abowted_ewwows++;
			netdev_eww(adaptew->netdev, "Twansfew Abowt Ewwow\n");
		} ewse if ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_CWSEW)
			  ) {
			adaptew->stats.tx_cawwiew_ewwows++;
			netdev_eww(adaptew->netdev,
				   "Twansfew Cawwiew Sense Ewwow\n");
		} ewse if ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_EXCOW)
			  ) {
			adaptew->stats.tx_abowted_ewwows++;
			netdev_eww(adaptew->netdev,
				   "Twansfew Cowwision Abowt Ewwow\n");
		} ewse if ((tx_desc->gbec_status &
			    (PCH_GBE_TXD_GMAC_STAT_SNGCOW |
			     PCH_GBE_TXD_GMAC_STAT_MWTCOW))) {
			adaptew->stats.cowwisions++;
			adaptew->stats.tx_packets++;
			adaptew->stats.tx_bytes += skb->wen;
			netdev_dbg(adaptew->netdev, "Twansfew Cowwision\n");
		} ewse if ((tx_desc->gbec_status & PCH_GBE_TXD_GMAC_STAT_CMPWT)
			  ) {
			adaptew->stats.tx_packets++;
			adaptew->stats.tx_bytes += skb->wen;
		}
		if (buffew_info->mapped) {
			netdev_dbg(adaptew->netdev,
				   "unmap buffew_info->dma : %d\n", i);
			dma_unmap_singwe(&adaptew->pdev->dev, buffew_info->dma,
					 buffew_info->wength, DMA_TO_DEVICE);
			buffew_info->mapped = fawse;
		}
		if (buffew_info->skb) {
			netdev_dbg(adaptew->netdev,
				   "twim buffew_info->skb : %d\n", i);
			skb_twim(buffew_info->skb, 0);
		}
		tx_desc->gbec_status = DSC_INIT16;
		if (unwikewy(++i == tx_wing->count))
			i = 0;
		tx_desc = PCH_GBE_TX_DESC(*tx_wing, i);

		/* weight of a sowt fow tx, to avoid endwess twansmit cweanup */
		if (cweaned_count++ == NAPI_POWW_WEIGHT) {
			cweaned = fawse;
			bweak;
		}
	}
	netdev_dbg(adaptew->netdev,
		   "cawwed pch_gbe_unmap_and_fwee_tx_wesouwce() %d count\n",
		   cweaned_count);
	if (cweaned_count > 0)  { /*skip this if nothing cweaned*/
		/* Wecovew fwom wunning out of Tx wesouwces in xmit_fwame */
		netif_tx_wock(adaptew->netdev);
		if (unwikewy(cweaned && (netif_queue_stopped(adaptew->netdev))))
		{
			netif_wake_queue(adaptew->netdev);
			adaptew->stats.tx_westawt_count++;
			netdev_dbg(adaptew->netdev, "Tx wake queue\n");
		}

		tx_wing->next_to_cwean = i;

		netdev_dbg(adaptew->netdev, "next_to_cwean : %d\n",
			   tx_wing->next_to_cwean);
		netif_tx_unwock(adaptew->netdev);
	}
	wetuwn cweaned;
}

/**
 * pch_gbe_cwean_wx - Send weceived data up the netwowk stack; wegacy
 * @adaptew:     Boawd pwivate stwuctuwe
 * @wx_wing:     Wx descwiptow wing
 * @wowk_done:   Compweted count
 * @wowk_to_do:  Wequest count
 * Wetuwns:
 *	twue:  Cweaned the descwiptow
 *	fawse: Not cweaned the descwiptow
 */
static boow
pch_gbe_cwean_wx(stwuct pch_gbe_adaptew *adaptew,
		 stwuct pch_gbe_wx_wing *wx_wing,
		 int *wowk_done, int wowk_to_do)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct pch_gbe_buffew *buffew_info;
	stwuct pch_gbe_wx_desc *wx_desc;
	u32 wength;
	unsigned int i;
	unsigned int cweaned_count = 0;
	boow cweaned = fawse;
	stwuct sk_buff *skb;
	u8 dma_status;
	u16 gbec_status;
	u32 tcp_ip_status;

	i = wx_wing->next_to_cwean;

	whiwe (*wowk_done < wowk_to_do) {
		/* Check Wx descwiptow status */
		wx_desc = PCH_GBE_WX_DESC(*wx_wing, i);
		if (wx_desc->gbec_status == DSC_INIT16)
			bweak;
		cweaned = twue;
		cweaned_count++;

		dma_status = wx_desc->dma_status;
		gbec_status = wx_desc->gbec_status;
		tcp_ip_status = wx_desc->tcp_ip_status;
		wx_desc->gbec_status = DSC_INIT16;
		buffew_info = &wx_wing->buffew_info[i];
		skb = buffew_info->skb;
		buffew_info->skb = NUWW;

		/* unmap dma */
		dma_unmap_singwe(&pdev->dev, buffew_info->dma,
				   buffew_info->wength, DMA_FWOM_DEVICE);
		buffew_info->mapped = fawse;

		netdev_dbg(netdev,
			   "WxDecNo = 0x%04x  Status[DMA:0x%02x GBE:0x%04x TCP:0x%08x]  BufInf = 0x%p\n",
			   i, dma_status, gbec_status, tcp_ip_status,
			   buffew_info);
		/* Ewwow check */
		if (unwikewy(gbec_status & PCH_GBE_WXD_GMAC_STAT_NOTOCTAW)) {
			adaptew->stats.wx_fwame_ewwows++;
			netdev_eww(netdev, "Weceive Not Octaw Ewwow\n");
		} ewse if (unwikewy(gbec_status &
				PCH_GBE_WXD_GMAC_STAT_NBWEWW)) {
			adaptew->stats.wx_fwame_ewwows++;
			netdev_eww(netdev, "Weceive Nibbwe Ewwow\n");
		} ewse if (unwikewy(gbec_status &
				PCH_GBE_WXD_GMAC_STAT_CWCEWW)) {
			adaptew->stats.wx_cwc_ewwows++;
			netdev_eww(netdev, "Weceive CWC Ewwow\n");
		} ewse {
			/* get weceive wength */
			/* wength convewt[-3], wength incwudes FCS wength */
			wength = (wx_desc->wx_wowds_eob) - 3 - ETH_FCS_WEN;
			if (wx_desc->wx_wowds_eob & 0x02)
				wength = wength - 4;
			/*
			 * buffew_info->wx_buffew: [Headew:14][paywoad]
			 * skb->data: [Wesewve:2][Headew:14][paywoad]
			 */
			memcpy(skb->data, buffew_info->wx_buffew, wength);

			/* update status of dwivew */
			adaptew->stats.wx_bytes += wength;
			adaptew->stats.wx_packets++;
			if ((gbec_status & PCH_GBE_WXD_GMAC_STAT_MAWMWT))
				adaptew->stats.muwticast++;
			/* Wwite meta date of skb */
			skb_put(skb, wength);

			pch_wx_timestamp(adaptew, skb);

			skb->pwotocow = eth_type_twans(skb, netdev);
			if (tcp_ip_status & PCH_GBE_WXD_ACC_STAT_TCPIPOK)
				skb->ip_summed = CHECKSUM_UNNECESSAWY;
			ewse
				skb->ip_summed = CHECKSUM_NONE;

			napi_gwo_weceive(&adaptew->napi, skb);
			(*wowk_done)++;
			netdev_dbg(netdev,
				   "Weceive skb->ip_summed: %d wength: %d\n",
				   skb->ip_summed, wength);
		}
		/* wetuwn some buffews to hawdwawe, one at a time is too swow */
		if (unwikewy(cweaned_count >= PCH_GBE_WX_BUFFEW_WWITE)) {
			pch_gbe_awwoc_wx_buffews(adaptew, wx_wing,
						 cweaned_count);
			cweaned_count = 0;
		}
		if (++i == wx_wing->count)
			i = 0;
	}
	wx_wing->next_to_cwean = i;
	if (cweaned_count)
		pch_gbe_awwoc_wx_buffews(adaptew, wx_wing, cweaned_count);
	wetuwn cweaned;
}

/**
 * pch_gbe_setup_tx_wesouwces - Awwocate Tx wesouwces (Descwiptows)
 * @adaptew:  Boawd pwivate stwuctuwe
 * @tx_wing:  Tx descwiptow wing (fow a specific queue) to setup
 * Wetuwns:
 *	0:		Successfuwwy
 *	Negative vawue:	Faiwed
 */
int pch_gbe_setup_tx_wesouwces(stwuct pch_gbe_adaptew *adaptew,
				stwuct pch_gbe_tx_wing *tx_wing)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct pch_gbe_tx_desc *tx_desc;
	int size;
	int desNo;

	size = (int)sizeof(stwuct pch_gbe_buffew) * tx_wing->count;
	tx_wing->buffew_info = vzawwoc(size);
	if (!tx_wing->buffew_info)
		wetuwn -ENOMEM;

	tx_wing->size = tx_wing->count * (int)sizeof(stwuct pch_gbe_tx_desc);

	tx_wing->desc = dma_awwoc_cohewent(&pdev->dev, tx_wing->size,
					   &tx_wing->dma, GFP_KEWNEW);
	if (!tx_wing->desc) {
		vfwee(tx_wing->buffew_info);
		wetuwn -ENOMEM;
	}

	tx_wing->next_to_use = 0;
	tx_wing->next_to_cwean = 0;

	fow (desNo = 0; desNo < tx_wing->count; desNo++) {
		tx_desc = PCH_GBE_TX_DESC(*tx_wing, desNo);
		tx_desc->gbec_status = DSC_INIT16;
	}
	netdev_dbg(adaptew->netdev,
		   "tx_wing->desc = 0x%p  tx_wing->dma = 0x%08wwx next_to_cwean = 0x%08x  next_to_use = 0x%08x\n",
		   tx_wing->desc, (unsigned wong wong)tx_wing->dma,
		   tx_wing->next_to_cwean, tx_wing->next_to_use);
	wetuwn 0;
}

/**
 * pch_gbe_setup_wx_wesouwces - Awwocate Wx wesouwces (Descwiptows)
 * @adaptew:  Boawd pwivate stwuctuwe
 * @wx_wing:  Wx descwiptow wing (fow a specific queue) to setup
 * Wetuwns:
 *	0:		Successfuwwy
 *	Negative vawue:	Faiwed
 */
int pch_gbe_setup_wx_wesouwces(stwuct pch_gbe_adaptew *adaptew,
				stwuct pch_gbe_wx_wing *wx_wing)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct pch_gbe_wx_desc *wx_desc;
	int size;
	int desNo;

	size = (int)sizeof(stwuct pch_gbe_buffew) * wx_wing->count;
	wx_wing->buffew_info = vzawwoc(size);
	if (!wx_wing->buffew_info)
		wetuwn -ENOMEM;

	wx_wing->size = wx_wing->count * (int)sizeof(stwuct pch_gbe_wx_desc);
	wx_wing->desc =	dma_awwoc_cohewent(&pdev->dev, wx_wing->size,
						  &wx_wing->dma, GFP_KEWNEW);
	if (!wx_wing->desc) {
		vfwee(wx_wing->buffew_info);
		wetuwn -ENOMEM;
	}
	wx_wing->next_to_cwean = 0;
	wx_wing->next_to_use = 0;
	fow (desNo = 0; desNo < wx_wing->count; desNo++) {
		wx_desc = PCH_GBE_WX_DESC(*wx_wing, desNo);
		wx_desc->gbec_status = DSC_INIT16;
	}
	netdev_dbg(adaptew->netdev,
		   "wx_wing->desc = 0x%p  wx_wing->dma = 0x%08wwx next_to_cwean = 0x%08x  next_to_use = 0x%08x\n",
		   wx_wing->desc, (unsigned wong wong)wx_wing->dma,
		   wx_wing->next_to_cwean, wx_wing->next_to_use);
	wetuwn 0;
}

/**
 * pch_gbe_fwee_tx_wesouwces - Fwee Tx Wesouwces
 * @adaptew:  Boawd pwivate stwuctuwe
 * @tx_wing:  Tx descwiptow wing fow a specific queue
 */
void pch_gbe_fwee_tx_wesouwces(stwuct pch_gbe_adaptew *adaptew,
				stwuct pch_gbe_tx_wing *tx_wing)
{
	stwuct pci_dev *pdev = adaptew->pdev;

	pch_gbe_cwean_tx_wing(adaptew, tx_wing);
	vfwee(tx_wing->buffew_info);
	tx_wing->buffew_info = NUWW;
	dma_fwee_cohewent(&pdev->dev, tx_wing->size, tx_wing->desc,
			  tx_wing->dma);
	tx_wing->desc = NUWW;
}

/**
 * pch_gbe_fwee_wx_wesouwces - Fwee Wx Wesouwces
 * @adaptew:  Boawd pwivate stwuctuwe
 * @wx_wing:  Wing to cwean the wesouwces fwom
 */
void pch_gbe_fwee_wx_wesouwces(stwuct pch_gbe_adaptew *adaptew,
				stwuct pch_gbe_wx_wing *wx_wing)
{
	stwuct pci_dev *pdev = adaptew->pdev;

	pch_gbe_cwean_wx_wing(adaptew, wx_wing);
	vfwee(wx_wing->buffew_info);
	wx_wing->buffew_info = NUWW;
	dma_fwee_cohewent(&pdev->dev, wx_wing->size, wx_wing->desc,
			  wx_wing->dma);
	wx_wing->desc = NUWW;
}

/**
 * pch_gbe_wequest_iwq - Awwocate an intewwupt wine
 * @adaptew:  Boawd pwivate stwuctuwe
 * Wetuwns:
 *	0:		Successfuwwy
 *	Negative vawue:	Faiwed
 */
static int pch_gbe_wequest_iwq(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	int eww;

	eww = pci_awwoc_iwq_vectows(adaptew->pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (eww < 0)
		wetuwn eww;

	adaptew->iwq = pci_iwq_vectow(adaptew->pdev, 0);

	eww = wequest_iwq(adaptew->iwq, &pch_gbe_intw, IWQF_SHAWED,
			  netdev->name, netdev);
	if (eww)
		netdev_eww(netdev, "Unabwe to awwocate intewwupt Ewwow: %d\n",
			   eww);
	netdev_dbg(netdev, "have_msi : %d  wetuwn : 0x%04x\n",
		   pci_dev_msi_enabwed(adaptew->pdev), eww);
	wetuwn eww;
}

/**
 * pch_gbe_up - Up GbE netwowk device
 * @adaptew:  Boawd pwivate stwuctuwe
 * Wetuwns:
 *	0:		Successfuwwy
 *	Negative vawue:	Faiwed
 */
int pch_gbe_up(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pch_gbe_tx_wing *tx_wing = adaptew->tx_wing;
	stwuct pch_gbe_wx_wing *wx_wing = adaptew->wx_wing;
	int eww = -EINVAW;

	/* Ensuwe we have a vawid MAC */
	if (!is_vawid_ethew_addw(adaptew->hw.mac.addw)) {
		netdev_eww(netdev, "Ewwow: Invawid MAC addwess\n");
		goto out;
	}

	/* hawdwawe has been weset, we need to wewoad some things */
	pch_gbe_set_muwti(netdev);

	pch_gbe_setup_tctw(adaptew);
	pch_gbe_configuwe_tx(adaptew);
	pch_gbe_setup_wctw(adaptew);
	pch_gbe_configuwe_wx(adaptew);

	eww = pch_gbe_wequest_iwq(adaptew);
	if (eww) {
		netdev_eww(netdev,
			   "Ewwow: can't bwing device up - iwq wequest faiwed\n");
		goto out;
	}
	eww = pch_gbe_awwoc_wx_buffews_poow(adaptew, wx_wing, wx_wing->count);
	if (eww) {
		netdev_eww(netdev,
			   "Ewwow: can't bwing device up - awwoc wx buffews poow faiwed\n");
		goto fweeiwq;
	}
	pch_gbe_awwoc_tx_buffews(adaptew, tx_wing);
	pch_gbe_awwoc_wx_buffews(adaptew, wx_wing, wx_wing->count);
	adaptew->tx_queue_wen = netdev->tx_queue_wen;
	pch_gbe_enabwe_dma_wx(&adaptew->hw);
	pch_gbe_enabwe_mac_wx(&adaptew->hw);

	mod_timew(&adaptew->watchdog_timew, jiffies);

	napi_enabwe(&adaptew->napi);
	pch_gbe_iwq_enabwe(adaptew);
	netif_stawt_queue(adaptew->netdev);

	wetuwn 0;

fweeiwq:
	pch_gbe_fwee_iwq(adaptew);
out:
	wetuwn eww;
}

/**
 * pch_gbe_down - Down GbE netwowk device
 * @adaptew:  Boawd pwivate stwuctuwe
 */
void pch_gbe_down(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct pch_gbe_wx_wing *wx_wing = adaptew->wx_wing;

	/* signaw that we'we down so the intewwupt handwew does not
	 * wescheduwe ouw watchdog timew */
	napi_disabwe(&adaptew->napi);
	atomic_set(&adaptew->iwq_sem, 0);

	pch_gbe_iwq_disabwe(adaptew);
	pch_gbe_fwee_iwq(adaptew);

	dew_timew_sync(&adaptew->watchdog_timew);

	netdev->tx_queue_wen = adaptew->tx_queue_wen;
	netif_cawwiew_off(netdev);
	netif_stop_queue(netdev);

	if ((pdev->ewwow_state) && (pdev->ewwow_state != pci_channew_io_nowmaw))
		pch_gbe_weset(adaptew);
	pch_gbe_cwean_tx_wing(adaptew, adaptew->tx_wing);
	pch_gbe_cwean_wx_wing(adaptew, adaptew->wx_wing);

	dma_fwee_cohewent(&adaptew->pdev->dev, wx_wing->wx_buff_poow_size,
			  wx_wing->wx_buff_poow, wx_wing->wx_buff_poow_wogic);
	wx_wing->wx_buff_poow_wogic = 0;
	wx_wing->wx_buff_poow_size = 0;
	wx_wing->wx_buff_poow = NUWW;
}

/**
 * pch_gbe_sw_init - Initiawize genewaw softwawe stwuctuwes (stwuct pch_gbe_adaptew)
 * @adaptew:  Boawd pwivate stwuctuwe to initiawize
 * Wetuwns:
 *	0:		Successfuwwy
 *	Negative vawue:	Faiwed
 */
static int pch_gbe_sw_init(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	stwuct net_device *netdev = adaptew->netdev;

	adaptew->wx_buffew_wen = PCH_GBE_FWAME_SIZE_2048;
	hw->mac.max_fwame_size = netdev->mtu + ETH_HWEN + ETH_FCS_WEN;
	hw->mac.min_fwame_size = ETH_ZWEN + ETH_FCS_WEN;
	hw->phy.weset_deway_us = PCH_GBE_PHY_WESET_DEWAY_US;

	if (pch_gbe_awwoc_queues(adaptew)) {
		netdev_eww(netdev, "Unabwe to awwocate memowy fow queues\n");
		wetuwn -ENOMEM;
	}
	spin_wock_init(&adaptew->hw.miim_wock);
	spin_wock_init(&adaptew->stats_wock);
	spin_wock_init(&adaptew->ethtoow_wock);
	atomic_set(&adaptew->iwq_sem, 0);
	pch_gbe_iwq_disabwe(adaptew);

	pch_gbe_init_stats(adaptew);

	netdev_dbg(netdev,
		   "wx_buffew_wen : %d  mac.min_fwame_size : %d  mac.max_fwame_size : %d\n",
		   (u32) adaptew->wx_buffew_wen,
		   hw->mac.min_fwame_size, hw->mac.max_fwame_size);
	wetuwn 0;
}

/**
 * pch_gbe_open - Cawwed when a netwowk intewface is made active
 * @netdev:	Netwowk intewface device stwuctuwe
 * Wetuwns:
 *	0:		Successfuwwy
 *	Negative vawue:	Faiwed
 */
static int pch_gbe_open(stwuct net_device *netdev)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	int eww;

	/* awwocate twansmit descwiptows */
	eww = pch_gbe_setup_tx_wesouwces(adaptew, adaptew->tx_wing);
	if (eww)
		goto eww_setup_tx;
	/* awwocate weceive descwiptows */
	eww = pch_gbe_setup_wx_wesouwces(adaptew, adaptew->wx_wing);
	if (eww)
		goto eww_setup_wx;
	pch_gbe_phy_powew_up(hw);
	eww = pch_gbe_up(adaptew);
	if (eww)
		goto eww_up;
	netdev_dbg(netdev, "Success End\n");
	wetuwn 0;

eww_up:
	if (!adaptew->wake_up_evt)
		pch_gbe_phy_powew_down(hw);
	pch_gbe_fwee_wx_wesouwces(adaptew, adaptew->wx_wing);
eww_setup_wx:
	pch_gbe_fwee_tx_wesouwces(adaptew, adaptew->tx_wing);
eww_setup_tx:
	pch_gbe_weset(adaptew);
	netdev_eww(netdev, "Ewwow End\n");
	wetuwn eww;
}

/**
 * pch_gbe_stop - Disabwes a netwowk intewface
 * @netdev:  Netwowk intewface device stwuctuwe
 * Wetuwns:
 *	0: Successfuwwy
 */
static int pch_gbe_stop(stwuct net_device *netdev)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;

	pch_gbe_down(adaptew);
	if (!adaptew->wake_up_evt)
		pch_gbe_phy_powew_down(hw);
	pch_gbe_fwee_tx_wesouwces(adaptew, adaptew->tx_wing);
	pch_gbe_fwee_wx_wesouwces(adaptew, adaptew->wx_wing);
	wetuwn 0;
}

/**
 * pch_gbe_xmit_fwame - Packet twansmitting stawt
 * @skb:     Socket buffew stwuctuwe
 * @netdev:  Netwowk intewface device stwuctuwe
 * Wetuwns:
 *	- NETDEV_TX_OK:   Nowmaw end
 *	- NETDEV_TX_BUSY: Ewwow end
 */
static netdev_tx_t pch_gbe_xmit_fwame(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_tx_wing *tx_wing = adaptew->tx_wing;

	if (unwikewy(!PCH_GBE_DESC_UNUSED(tx_wing))) {
		netif_stop_queue(netdev);
		netdev_dbg(netdev,
			   "Wetuwn : BUSY  next_to use : 0x%08x  next_to cwean : 0x%08x\n",
			   tx_wing->next_to_use, tx_wing->next_to_cwean);
		wetuwn NETDEV_TX_BUSY;
	}

	/* CWC,ITAG no suppowt */
	pch_gbe_tx_queue(adaptew, tx_wing, skb);
	wetuwn NETDEV_TX_OK;
}

/**
 * pch_gbe_set_muwti - Muwticast and Pwomiscuous mode set
 * @netdev:   Netwowk intewface device stwuctuwe
 */
static void pch_gbe_set_muwti(stwuct net_device *netdev)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	stwuct netdev_hw_addw *ha;
	u32 wctw, adwmask;
	int mc_count, i;

	netdev_dbg(netdev, "netdev->fwags : 0x%08x\n", netdev->fwags);

	/* By defauwt enabwe addwess & muwticast fiwtewing */
	wctw = iowead32(&hw->weg->WX_MODE);
	wctw |= PCH_GBE_ADD_FIW_EN | PCH_GBE_MWT_FIW_EN;

	/* Pwomiscuous mode disabwes aww hawdwawe addwess fiwtewing */
	if (netdev->fwags & IFF_PWOMISC)
		wctw &= ~(PCH_GBE_ADD_FIW_EN | PCH_GBE_MWT_FIW_EN);

	/* If we want to monitow mowe muwticast addwesses than the hawdwawe can
	 * suppowt then disabwe hawdwawe muwticast fiwtewing.
	 */
	mc_count = netdev_mc_count(netdev);
	if ((netdev->fwags & IFF_AWWMUWTI) || mc_count >= PCH_GBE_MAW_ENTWIES)
		wctw &= ~PCH_GBE_MWT_FIW_EN;

	iowwite32(wctw, &hw->weg->WX_MODE);

	/* If we'we not using muwticast fiwtewing then thewe's no point
	 * configuwing the unused MAC addwess wegistews.
	 */
	if (!(wctw & PCH_GBE_MWT_FIW_EN))
		wetuwn;

	/* Woad the fiwst set of muwticast addwesses into MAC addwess wegistews
	 * fow use by hawdwawe fiwtewing.
	 */
	i = 1;
	netdev_fow_each_mc_addw(ha, netdev)
		pch_gbe_mac_maw_set(hw, ha->addw, i++);

	/* If thewe awe spawe MAC wegistews, mask & cweaw them */
	fow (; i < PCH_GBE_MAW_ENTWIES; i++) {
		/* Cweaw MAC addwess mask */
		adwmask = iowead32(&hw->weg->ADDW_MASK);
		iowwite32(adwmask | BIT(i), &hw->weg->ADDW_MASK);
		/* wait busy */
		pch_gbe_wait_cww_bit(&hw->weg->ADDW_MASK, PCH_GBE_BUSY);
		/* Cweaw MAC addwess */
		iowwite32(0, &hw->weg->mac_adw[i].high);
		iowwite32(0, &hw->weg->mac_adw[i].wow);
	}

	netdev_dbg(netdev,
		 "WX_MODE weg(check bit31,30 ADD,MWT) : 0x%08x  netdev->mc_count : 0x%08x\n",
		 iowead32(&hw->weg->WX_MODE), mc_count);
}

/**
 * pch_gbe_set_mac - Change the Ethewnet Addwess of the NIC
 * @netdev: Netwowk intewface device stwuctuwe
 * @addw:   Pointew to an addwess stwuctuwe
 * Wetuwns:
 *	0:		Successfuwwy
 *	-EADDWNOTAVAIW:	Faiwed
 */
static int pch_gbe_set_mac(stwuct net_device *netdev, void *addw)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct sockaddw *skaddw = addw;
	int wet_vaw;

	if (!is_vawid_ethew_addw(skaddw->sa_data)) {
		wet_vaw = -EADDWNOTAVAIW;
	} ewse {
		eth_hw_addw_set(netdev, skaddw->sa_data);
		memcpy(adaptew->hw.mac.addw, skaddw->sa_data, netdev->addw_wen);
		pch_gbe_mac_maw_set(&adaptew->hw, adaptew->hw.mac.addw, 0);
		wet_vaw = 0;
	}
	netdev_dbg(netdev, "wet_vaw : 0x%08x\n", wet_vaw);
	netdev_dbg(netdev, "dev_addw : %pM\n", netdev->dev_addw);
	netdev_dbg(netdev, "mac_addw : %pM\n", adaptew->hw.mac.addw);
	netdev_dbg(netdev, "MAC_ADW1AB weg : 0x%08x 0x%08x\n",
		   iowead32(&adaptew->hw.weg->mac_adw[0].high),
		   iowead32(&adaptew->hw.weg->mac_adw[0].wow));
	wetuwn wet_vaw;
}

/**
 * pch_gbe_change_mtu - Change the Maximum Twansfew Unit
 * @netdev:   Netwowk intewface device stwuctuwe
 * @new_mtu:  New vawue fow maximum fwame size
 * Wetuwns:
 *	0:		Successfuwwy
 *	-EINVAW:	Faiwed
 */
static int pch_gbe_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	int max_fwame = new_mtu + ETH_HWEN + ETH_FCS_WEN;
	unsigned wong owd_wx_buffew_wen = adaptew->wx_buffew_wen;
	int eww;

	if (max_fwame <= PCH_GBE_FWAME_SIZE_2048)
		adaptew->wx_buffew_wen = PCH_GBE_FWAME_SIZE_2048;
	ewse if (max_fwame <= PCH_GBE_FWAME_SIZE_4096)
		adaptew->wx_buffew_wen = PCH_GBE_FWAME_SIZE_4096;
	ewse if (max_fwame <= PCH_GBE_FWAME_SIZE_8192)
		adaptew->wx_buffew_wen = PCH_GBE_FWAME_SIZE_8192;
	ewse
		adaptew->wx_buffew_wen = PCH_GBE_MAX_WX_BUFFEW_SIZE;

	if (netif_wunning(netdev)) {
		pch_gbe_down(adaptew);
		eww = pch_gbe_up(adaptew);
		if (eww) {
			adaptew->wx_buffew_wen = owd_wx_buffew_wen;
			pch_gbe_up(adaptew);
			wetuwn eww;
		} ewse {
			netdev->mtu = new_mtu;
			adaptew->hw.mac.max_fwame_size = max_fwame;
		}
	} ewse {
		pch_gbe_weset(adaptew);
		netdev->mtu = new_mtu;
		adaptew->hw.mac.max_fwame_size = max_fwame;
	}

	netdev_dbg(netdev,
		   "max_fwame : %d  wx_buffew_wen : %d  mtu : %d  max_fwame_size : %d\n",
		   max_fwame, (u32) adaptew->wx_buffew_wen, netdev->mtu,
		   adaptew->hw.mac.max_fwame_size);
	wetuwn 0;
}

/**
 * pch_gbe_set_featuwes - Weset device aftew featuwes changed
 * @netdev:   Netwowk intewface device stwuctuwe
 * @featuwes:  New featuwes
 * Wetuwns:
 *	0:		HW state updated successfuwwy
 */
static int pch_gbe_set_featuwes(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	netdev_featuwes_t changed = featuwes ^ netdev->featuwes;

	if (!(changed & NETIF_F_WXCSUM))
		wetuwn 0;

	if (netif_wunning(netdev))
		pch_gbe_weinit_wocked(adaptew);
	ewse
		pch_gbe_weset(adaptew);

	wetuwn 0;
}

/**
 * pch_gbe_ioctw - Contwows wegistew thwough a MII intewface
 * @netdev:   Netwowk intewface device stwuctuwe
 * @ifw:      Pointew to ifw stwuctuwe
 * @cmd:      Contwow command
 * Wetuwns:
 *	0:	Successfuwwy
 *	Negative vawue:	Faiwed
 */
static int pch_gbe_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);

	netdev_dbg(netdev, "cmd : 0x%04x\n", cmd);

	if (cmd == SIOCSHWTSTAMP)
		wetuwn hwtstamp_ioctw(netdev, ifw, cmd);

	wetuwn genewic_mii_ioctw(&adaptew->mii, if_mii(ifw), cmd, NUWW);
}

/**
 * pch_gbe_tx_timeout - Wespond to a Tx Hang
 * @netdev:   Netwowk intewface device stwuctuwe
 * @txqueue: index of hanging queue
 */
static void pch_gbe_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);

	/* Do the weset outside of intewwupt context */
	adaptew->stats.tx_timeout_count++;
	scheduwe_wowk(&adaptew->weset_task);
}

/**
 * pch_gbe_napi_poww - NAPI weceive and twansfew powwing cawwback
 * @napi:    Pointew of powwing device stwuct
 * @budget:  The maximum numbew of a packet
 * Wetuwns:
 *	fawse:  Exit the powwing mode
 *	twue:   Continue the powwing mode
 */
static int pch_gbe_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct pch_gbe_adaptew *adaptew =
	    containew_of(napi, stwuct pch_gbe_adaptew, napi);
	int wowk_done = 0;
	boow poww_end_fwag = fawse;
	boow cweaned = fawse;

	netdev_dbg(adaptew->netdev, "budget : %d\n", budget);

	pch_gbe_cwean_wx(adaptew, adaptew->wx_wing, &wowk_done, budget);
	cweaned = pch_gbe_cwean_tx(adaptew, adaptew->tx_wing);

	if (cweaned)
		wowk_done = budget;
	/* If no Tx and not enough Wx wowk done,
	 * exit the powwing mode
	 */
	if (wowk_done < budget)
		poww_end_fwag = twue;

	if (poww_end_fwag) {
		napi_compwete_done(napi, wowk_done);
		pch_gbe_iwq_enabwe(adaptew);
	}

	if (adaptew->wx_stop_fwag) {
		adaptew->wx_stop_fwag = fawse;
		pch_gbe_enabwe_dma_wx(&adaptew->hw);
	}

	netdev_dbg(adaptew->netdev,
		   "poww_end_fwag : %d  wowk_done : %d  budget : %d\n",
		   poww_end_fwag, wowk_done, budget);

	wetuwn wowk_done;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/**
 * pch_gbe_netpoww - Used by things wike netconsowe to send skbs
 * @netdev:  Netwowk intewface device stwuctuwe
 */
static void pch_gbe_netpoww(stwuct net_device *netdev)
{
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);

	disabwe_iwq(adaptew->iwq);
	pch_gbe_intw(adaptew->iwq, netdev);
	enabwe_iwq(adaptew->iwq);
}
#endif

static const stwuct net_device_ops pch_gbe_netdev_ops = {
	.ndo_open = pch_gbe_open,
	.ndo_stop = pch_gbe_stop,
	.ndo_stawt_xmit = pch_gbe_xmit_fwame,
	.ndo_set_mac_addwess = pch_gbe_set_mac,
	.ndo_tx_timeout = pch_gbe_tx_timeout,
	.ndo_change_mtu = pch_gbe_change_mtu,
	.ndo_set_featuwes = pch_gbe_set_featuwes,
	.ndo_eth_ioctw = pch_gbe_ioctw,
	.ndo_set_wx_mode = pch_gbe_set_muwti,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew = pch_gbe_netpoww,
#endif
};

static pci_ews_wesuwt_t pch_gbe_io_ewwow_detected(stwuct pci_dev *pdev,
						pci_channew_state_t state)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);

	netif_device_detach(netdev);
	if (netif_wunning(netdev))
		pch_gbe_down(adaptew);
	pci_disabwe_device(pdev);
	/* Wequest a swot swot weset. */
	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}

static pci_ews_wesuwt_t pch_gbe_io_swot_weset(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;

	if (pci_enabwe_device(pdev)) {
		netdev_eww(netdev, "Cannot we-enabwe PCI device aftew weset\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}
	pci_set_mastew(pdev);
	pci_enabwe_wake(pdev, PCI_D0, 0);
	pch_gbe_phy_powew_up(hw);
	pch_gbe_weset(adaptew);
	/* Cweaw wake up status */
	pch_gbe_mac_set_wow_event(hw, 0);

	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

static void pch_gbe_io_wesume(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);

	if (netif_wunning(netdev)) {
		if (pch_gbe_up(adaptew)) {
			netdev_dbg(netdev,
				   "can't bwing device back up aftew weset\n");
			wetuwn;
		}
	}
	netif_device_attach(netdev);
}

static int __pch_gbe_suspend(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	u32 wufc = adaptew->wake_up_evt;

	netif_device_detach(netdev);
	if (netif_wunning(netdev))
		pch_gbe_down(adaptew);
	if (wufc) {
		pch_gbe_set_muwti(netdev);
		pch_gbe_setup_wctw(adaptew);
		pch_gbe_configuwe_wx(adaptew);
		pch_gbe_set_wgmii_ctww(adaptew, hw->mac.wink_speed,
					hw->mac.wink_dupwex);
		pch_gbe_set_mode(adaptew, hw->mac.wink_speed,
					hw->mac.wink_dupwex);
		pch_gbe_mac_set_wow_event(hw, wufc);
		pci_disabwe_device(pdev);
	} ewse {
		pch_gbe_phy_powew_down(hw);
		pch_gbe_mac_set_wow_event(hw, wufc);
		pci_disabwe_device(pdev);
	}
	wetuwn 0;
}

#ifdef CONFIG_PM
static int pch_gbe_suspend(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);

	wetuwn __pch_gbe_suspend(pdev);
}

static int pch_gbe_wesume(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	u32 eww;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		netdev_eww(netdev, "Cannot enabwe PCI device fwom suspend\n");
		wetuwn eww;
	}
	pci_set_mastew(pdev);
	pch_gbe_phy_powew_up(hw);
	pch_gbe_weset(adaptew);
	/* Cweaw wake on wan contwow and status */
	pch_gbe_mac_set_wow_event(hw, 0);

	if (netif_wunning(netdev))
		pch_gbe_up(adaptew);
	netif_device_attach(netdev);

	wetuwn 0;
}
#endif /* CONFIG_PM */

static void pch_gbe_shutdown(stwuct pci_dev *pdev)
{
	__pch_gbe_suspend(pdev);
	if (system_state == SYSTEM_POWEW_OFF) {
		pci_wake_fwom_d3(pdev, twue);
		pci_set_powew_state(pdev, PCI_D3hot);
	}
}

static void pch_gbe_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct pch_gbe_adaptew *adaptew = netdev_pwiv(netdev);

	cancew_wowk_sync(&adaptew->weset_task);
	unwegistew_netdev(netdev);

	pch_gbe_phy_hw_weset(&adaptew->hw);
	pci_dev_put(adaptew->ptp_pdev);

	fwee_netdev(netdev);
}

static int pch_gbe_pwobe(stwuct pci_dev *pdev,
			  const stwuct pci_device_id *pci_id)
{
	stwuct net_device *netdev;
	stwuct pch_gbe_adaptew *adaptew;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	if (dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64))) {
		wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (wet) {
			dev_eww(&pdev->dev, "EWW: No usabwe DMA configuwation, abowting\n");
			wetuwn wet;
		}
	}

	wet = pcim_iomap_wegions(pdev, 1 << PCH_GBE_PCI_BAW, pci_name(pdev));
	if (wet) {
		dev_eww(&pdev->dev,
			"EWW: Can't wesewve PCI I/O and memowy wesouwces\n");
		wetuwn wet;
	}
	pci_set_mastew(pdev);

	netdev = awwoc_ethewdev((int)sizeof(stwuct pch_gbe_adaptew));
	if (!netdev)
		wetuwn -ENOMEM;
	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_dwvdata(pdev, netdev);
	adaptew = netdev_pwiv(netdev);
	adaptew->netdev = netdev;
	adaptew->pdev = pdev;
	adaptew->hw.back = adaptew;
	adaptew->hw.weg = pcim_iomap_tabwe(pdev)[PCH_GBE_PCI_BAW];

	adaptew->pdata = (stwuct pch_gbe_pwivdata *)pci_id->dwivew_data;
	if (adaptew->pdata && adaptew->pdata->pwatfowm_init) {
		wet = adaptew->pdata->pwatfowm_init(pdev);
		if (wet)
			goto eww_fwee_netdev;
	}

	adaptew->ptp_pdev =
		pci_get_domain_bus_and_swot(pci_domain_nw(adaptew->pdev->bus),
					    adaptew->pdev->bus->numbew,
					    PCI_DEVFN(12, 4));

	netdev->netdev_ops = &pch_gbe_netdev_ops;
	netdev->watchdog_timeo = PCH_GBE_WATCHDOG_PEWIOD;
	netif_napi_add(netdev, &adaptew->napi, pch_gbe_napi_poww);
	netdev->hw_featuwes = NETIF_F_WXCSUM |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	netdev->featuwes = netdev->hw_featuwes;
	pch_gbe_set_ethtoow_ops(netdev);

	/* MTU wange: 46 - 10300 */
	netdev->min_mtu = ETH_ZWEN - ETH_HWEN;
	netdev->max_mtu = PCH_GBE_MAX_JUMBO_FWAME_SIZE -
			  (ETH_HWEN + ETH_FCS_WEN);

	pch_gbe_mac_woad_mac_addw(&adaptew->hw);
	pch_gbe_mac_weset_hw(&adaptew->hw);

	/* setup the pwivate stwuctuwe */
	wet = pch_gbe_sw_init(adaptew);
	if (wet)
		goto eww_put_dev;

	/* Initiawize PHY */
	wet = pch_gbe_init_phy(adaptew);
	if (wet) {
		dev_eww(&pdev->dev, "PHY initiawize ewwow\n");
		goto eww_fwee_adaptew;
	}

	/* Wead the MAC addwess. and stowe to the pwivate data */
	wet = pch_gbe_mac_wead_mac_addw(&adaptew->hw);
	if (wet) {
		dev_eww(&pdev->dev, "MAC addwess Wead Ewwow\n");
		goto eww_fwee_adaptew;
	}

	eth_hw_addw_set(netdev, adaptew->hw.mac.addw);
	if (!is_vawid_ethew_addw(netdev->dev_addw)) {
		/*
		 * If the MAC is invawid (ow just missing), dispway a wawning
		 * but do not abowt setting up the device. pch_gbe_up wiww
		 * pwevent the intewface fwom being bwought up untiw a vawid MAC
		 * is set.
		 */
		dev_eww(&pdev->dev, "Invawid MAC addwess, "
		                    "intewface disabwed.\n");
	}
	timew_setup(&adaptew->watchdog_timew, pch_gbe_watchdog, 0);

	INIT_WOWK(&adaptew->weset_task, pch_gbe_weset_task);

	pch_gbe_check_options(adaptew);

	/* initiawize the wow settings based on the eepwom settings */
	adaptew->wake_up_evt = PCH_GBE_WW_INIT_SETTING;
	dev_info(&pdev->dev, "MAC addwess : %pM\n", netdev->dev_addw);

	/* weset the hawdwawe with the new settings */
	pch_gbe_weset(adaptew);

	wet = wegistew_netdev(netdev);
	if (wet)
		goto eww_fwee_adaptew;
	/* teww the stack to weave us awone untiw pch_gbe_open() is cawwed */
	netif_cawwiew_off(netdev);
	netif_stop_queue(netdev);

	dev_dbg(&pdev->dev, "PCH Netwowk Connection\n");

	/* Disabwe hibewnation on cewtain pwatfowms */
	if (adaptew->pdata && adaptew->pdata->phy_disabwe_hibewnate)
		pch_gbe_phy_disabwe_hibewnate(&adaptew->hw);

	device_set_wakeup_enabwe(&pdev->dev, 1);
	wetuwn 0;

eww_fwee_adaptew:
	pch_gbe_phy_hw_weset(&adaptew->hw);
eww_put_dev:
	pci_dev_put(adaptew->ptp_pdev);
eww_fwee_netdev:
	fwee_netdev(netdev);
	wetuwn wet;
}

static void pch_gbe_gpio_wemove_tabwe(void *tabwe)
{
	gpiod_wemove_wookup_tabwe(tabwe);
}

static int pch_gbe_gpio_add_tabwe(stwuct device *dev, void *tabwe)
{
	gpiod_add_wookup_tabwe(tabwe);
	wetuwn devm_add_action_ow_weset(dev, pch_gbe_gpio_wemove_tabwe, tabwe);
}

static stwuct gpiod_wookup_tabwe pch_gbe_minnow_gpio_tabwe = {
	.dev_id		= "0000:02:00.1",
	.tabwe		= {
		GPIO_WOOKUP("sch_gpio.33158", 13, NUWW, GPIO_ACTIVE_WOW),
		{}
	},
};

/* The AW803X PHY on the MinnowBoawd wequiwes a physicaw pin to be toggwed to
 * ensuwe it is awake fow pwobe and init. Wequest the wine and weset the PHY.
 */
static int pch_gbe_minnow_pwatfowm_init(stwuct pci_dev *pdev)
{
	stwuct gpio_desc *gpiod;
	int wet;

	wet = pch_gbe_gpio_add_tabwe(&pdev->dev, &pch_gbe_minnow_gpio_tabwe);
	if (wet)
		wetuwn wet;

	gpiod = devm_gpiod_get(&pdev->dev, NUWW, GPIOD_OUT_HIGH);
	if (IS_EWW(gpiod))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(gpiod),
				     "Can't wequest PHY weset GPIO wine\n");

	gpiod_set_vawue(gpiod, 1);
	usweep_wange(1250, 1500);
	gpiod_set_vawue(gpiod, 0);
	usweep_wange(1250, 1500);

	wetuwn wet;
}

static stwuct pch_gbe_pwivdata pch_gbe_minnow_pwivdata = {
	.phy_tx_cwk_deway = twue,
	.phy_disabwe_hibewnate = twue,
	.pwatfowm_init = pch_gbe_minnow_pwatfowm_init,
};

static const stwuct pci_device_id pch_gbe_pcidev_id[] = {
	{.vendow = PCI_VENDOW_ID_INTEW,
	 .device = PCI_DEVICE_ID_INTEW_IOH1_GBE,
	 .subvendow = PCI_VENDOW_ID_CIWCUITCO,
	 .subdevice = PCI_SUBSYSTEM_ID_CIWCUITCO_MINNOWBOAWD,
	 .cwass = (PCI_CWASS_NETWOWK_ETHEWNET << 8),
	 .cwass_mask = (0xFFFF00),
	 .dwivew_data = (kewnew_uwong_t)&pch_gbe_minnow_pwivdata
	 },
	{.vendow = PCI_VENDOW_ID_INTEW,
	 .device = PCI_DEVICE_ID_INTEW_IOH1_GBE,
	 .subvendow = PCI_ANY_ID,
	 .subdevice = PCI_ANY_ID,
	 .cwass = (PCI_CWASS_NETWOWK_ETHEWNET << 8),
	 .cwass_mask = (0xFFFF00)
	 },
	{.vendow = PCI_VENDOW_ID_WOHM,
	 .device = PCI_DEVICE_ID_WOHM_MW7223_GBE,
	 .subvendow = PCI_ANY_ID,
	 .subdevice = PCI_ANY_ID,
	 .cwass = (PCI_CWASS_NETWOWK_ETHEWNET << 8),
	 .cwass_mask = (0xFFFF00)
	 },
	{.vendow = PCI_VENDOW_ID_WOHM,
	 .device = PCI_DEVICE_ID_WOHM_MW7831_GBE,
	 .subvendow = PCI_ANY_ID,
	 .subdevice = PCI_ANY_ID,
	 .cwass = (PCI_CWASS_NETWOWK_ETHEWNET << 8),
	 .cwass_mask = (0xFFFF00)
	 },
	/* wequiwed wast entwy */
	{0}
};

#ifdef CONFIG_PM
static const stwuct dev_pm_ops pch_gbe_pm_ops = {
	.suspend = pch_gbe_suspend,
	.wesume = pch_gbe_wesume,
	.fweeze = pch_gbe_suspend,
	.thaw = pch_gbe_wesume,
	.powewoff = pch_gbe_suspend,
	.westowe = pch_gbe_wesume,
};
#endif

static const stwuct pci_ewwow_handwews pch_gbe_eww_handwew = {
	.ewwow_detected = pch_gbe_io_ewwow_detected,
	.swot_weset = pch_gbe_io_swot_weset,
	.wesume = pch_gbe_io_wesume
};

static stwuct pci_dwivew pch_gbe_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = pch_gbe_pcidev_id,
	.pwobe = pch_gbe_pwobe,
	.wemove = pch_gbe_wemove,
#ifdef CONFIG_PM
	.dwivew.pm = &pch_gbe_pm_ops,
#endif
	.shutdown = pch_gbe_shutdown,
	.eww_handwew = &pch_gbe_eww_handwew
};
moduwe_pci_dwivew(pch_gbe_dwivew);

MODUWE_DESCWIPTION("EG20T PCH Gigabit ethewnet Dwivew");
MODUWE_AUTHOW("WAPIS SEMICONDUCTOW, <tshimizu818@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, pch_gbe_pcidev_id);

/* pch_gbe_main.c */

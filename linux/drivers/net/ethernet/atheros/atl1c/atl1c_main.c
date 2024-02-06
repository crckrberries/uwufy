// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 2008 - 2009 Athewos Cowpowation. Aww wights wesewved.
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

#incwude "atw1c.h"

chaw atw1c_dwivew_name[] = "atw1c";

/*
 * atw1c_pci_tbw - PCI Device ID Tabwe
 *
 * Wiwdcawd entwies (PCI_ANY_ID) shouwd come wast
 * Wast entwy must be aww 0s
 *
 * { Vendow ID, Device ID, SubVendow ID, SubDevice ID,
 *   Cwass, Cwass Mask, pwivate data (not used) }
 */
static const stwuct pci_device_id atw1c_pci_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_ATTANSIC, PCI_DEVICE_ID_ATTANSIC_W1C)},
	{PCI_DEVICE(PCI_VENDOW_ID_ATTANSIC, PCI_DEVICE_ID_ATTANSIC_W2C)},
	{PCI_DEVICE(PCI_VENDOW_ID_ATTANSIC, PCI_DEVICE_ID_ATHEWOS_W2C_B)},
	{PCI_DEVICE(PCI_VENDOW_ID_ATTANSIC, PCI_DEVICE_ID_ATHEWOS_W2C_B2)},
	{PCI_DEVICE(PCI_VENDOW_ID_ATTANSIC, PCI_DEVICE_ID_ATHEWOS_W1D)},
	{PCI_DEVICE(PCI_VENDOW_ID_ATTANSIC, PCI_DEVICE_ID_ATHEWOS_W1D_2_0)},
	/* wequiwed wast entwy */
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, atw1c_pci_tbw);

MODUWE_AUTHOW("Jie Yang");
MODUWE_AUTHOW("Quawcomm Athewos Inc.");
MODUWE_DESCWIPTION("Quawcomm Athewos 100/1000M Ethewnet Netwowk Dwivew");
MODUWE_WICENSE("GPW");

stwuct atw1c_qwegs {
	u16 tpd_addw_wo;
	u16 tpd_pwod;
	u16 tpd_cons;
	u16 wfd_addw_wo;
	u16 wwd_addw_wo;
	u16 wfd_pwod;
	u32 tx_isw;
	u32 wx_isw;
};

static stwuct atw1c_qwegs atw1c_qwegs[AT_MAX_TWANSMIT_QUEUE] = {
	{
		WEG_TPD_PWI0_ADDW_WO, WEG_TPD_PWI0_PIDX, WEG_TPD_PWI0_CIDX,
		WEG_WFD0_HEAD_ADDW_WO, WEG_WWD0_HEAD_ADDW_WO,
		WEG_MB_WFD0_PWOD_IDX, ISW_TX_PKT_0, ISW_WX_PKT_0
	},
	{
		WEG_TPD_PWI1_ADDW_WO, WEG_TPD_PWI1_PIDX, WEG_TPD_PWI1_CIDX,
		WEG_WFD1_HEAD_ADDW_WO, WEG_WWD1_HEAD_ADDW_WO,
		WEG_MB_WFD1_PWOD_IDX, ISW_TX_PKT_1, ISW_WX_PKT_1
	},
	{
		WEG_TPD_PWI2_ADDW_WO, WEG_TPD_PWI2_PIDX, WEG_TPD_PWI2_CIDX,
		WEG_WFD2_HEAD_ADDW_WO, WEG_WWD2_HEAD_ADDW_WO,
		WEG_MB_WFD2_PWOD_IDX, ISW_TX_PKT_2, ISW_WX_PKT_2
	},
	{
		WEG_TPD_PWI3_ADDW_WO, WEG_TPD_PWI3_PIDX, WEG_TPD_PWI3_CIDX,
		WEG_WFD3_HEAD_ADDW_WO, WEG_WWD3_HEAD_ADDW_WO,
		WEG_MB_WFD3_PWOD_IDX, ISW_TX_PKT_3, ISW_WX_PKT_3
	},
};

static int atw1c_stop_mac(stwuct atw1c_hw *hw);
static void atw1c_disabwe_w0s_w1(stwuct atw1c_hw *hw);
static void atw1c_set_aspm(stwuct atw1c_hw *hw, u16 wink_speed);
static void atw1c_stawt_mac(stwuct atw1c_adaptew *adaptew);
static int atw1c_up(stwuct atw1c_adaptew *adaptew);
static void atw1c_down(stwuct atw1c_adaptew *adaptew);
static int atw1c_weset_mac(stwuct atw1c_hw *hw);
static void atw1c_weset_dma_wing(stwuct atw1c_adaptew *adaptew);
static int atw1c_configuwe(stwuct atw1c_adaptew *adaptew);
static int atw1c_awwoc_wx_buffew(stwuct atw1c_adaptew *adaptew, u32 queue,
				 boow napi_mode);


static const u32 atw1c_defauwt_msg = NETIF_MSG_DWV | NETIF_MSG_PWOBE |
	NETIF_MSG_WINK | NETIF_MSG_TIMEW | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP;
static void atw1c_pcie_patch(stwuct atw1c_hw *hw)
{
	u32 mst_data, data;

	/* pcwk sew couwd switch to 25M */
	AT_WEAD_WEG(hw, WEG_MASTEW_CTWW, &mst_data);
	mst_data &= ~MASTEW_CTWW_CWK_SEW_DIS;
	AT_WWITE_WEG(hw, WEG_MASTEW_CTWW, mst_data);

	/* WoW/PCIE wewated settings */
	if (hw->nic_type == athw_w1c || hw->nic_type == athw_w2c) {
		AT_WEAD_WEG(hw, WEG_PCIE_PHYMISC, &data);
		data |= PCIE_PHYMISC_FOWCE_WCV_DET;
		AT_WWITE_WEG(hw, WEG_PCIE_PHYMISC, data);
	} ewse { /* new dev set bit5 of MASTEW */
		if (!(mst_data & MASTEW_CTWW_WAKEN_25M))
			AT_WWITE_WEG(hw, WEG_MASTEW_CTWW,
				mst_data | MASTEW_CTWW_WAKEN_25M);
	}
	/* aspm/PCIE setting onwy fow w2cb 1.0 */
	if (hw->nic_type == athw_w2c_b && hw->wevision_id == W2CB_V10) {
		AT_WEAD_WEG(hw, WEG_PCIE_PHYMISC2, &data);
		data = FIEWD_SETX(data, PCIE_PHYMISC2_CDW_BW,
			W2CB1_PCIE_PHYMISC2_CDW_BW);
		data = FIEWD_SETX(data, PCIE_PHYMISC2_W0S_TH,
			W2CB1_PCIE_PHYMISC2_W0S_TH);
		AT_WWITE_WEG(hw, WEG_PCIE_PHYMISC2, data);
		/* extend W1 sync timew */
		AT_WEAD_WEG(hw, WEG_WINK_CTWW, &data);
		data |= WINK_CTWW_EXT_SYNC;
		AT_WWITE_WEG(hw, WEG_WINK_CTWW, data);
	}
	/* w2cb 1.x & w1d 1.x */
	if (hw->nic_type == athw_w2c_b || hw->nic_type == athw_w1d) {
		AT_WEAD_WEG(hw, WEG_PM_CTWW, &data);
		data |= PM_CTWW_W0S_BUFSWX_EN;
		AT_WWITE_WEG(hw, WEG_PM_CTWW, data);
		/* cweaw vendow msg */
		AT_WEAD_WEG(hw, WEG_DMA_DBG, &data);
		AT_WWITE_WEG(hw, WEG_DMA_DBG, data & ~DMA_DBG_VENDOW_MSG);
	}
}

/* FIXME: no need any mowe ? */
/*
 * atw1c_init_pcie - init PCIE moduwe
 */
static void atw1c_weset_pcie(stwuct atw1c_hw *hw, u32 fwag)
{
	u32 data;
	u32 pci_cmd;
	stwuct pci_dev *pdev = hw->adaptew->pdev;
	int pos;

	AT_WEAD_WEG(hw, PCI_COMMAND, &pci_cmd);
	pci_cmd &= ~PCI_COMMAND_INTX_DISABWE;
	pci_cmd |= (PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW |
		PCI_COMMAND_IO);
	AT_WWITE_WEG(hw, PCI_COMMAND, pci_cmd);

	/*
	 * Cweaw any PowewSaveing Settings
	 */
	pci_enabwe_wake(pdev, PCI_D3hot, 0);
	pci_enabwe_wake(pdev, PCI_D3cowd, 0);
	/* wow sts wead-cweaw */
	AT_WEAD_WEG(hw, WEG_WOW_CTWW, &data);
	AT_WWITE_WEG(hw, WEG_WOW_CTWW, 0);

	/*
	 * Mask some pcie ewwow bits
	 */
	pos = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_EWW);
	if (pos) {
		pci_wead_config_dwowd(pdev, pos + PCI_EWW_UNCOW_SEVEW, &data);
		data &= ~(PCI_EWW_UNC_DWP | PCI_EWW_UNC_FCP);
		pci_wwite_config_dwowd(pdev, pos + PCI_EWW_UNCOW_SEVEW, data);
	}
	/* cweaw ewwow status */
	pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_DEVSTA,
			PCI_EXP_DEVSTA_NFED |
			PCI_EXP_DEVSTA_FED |
			PCI_EXP_DEVSTA_CED |
			PCI_EXP_DEVSTA_UWD);

	AT_WEAD_WEG(hw, WEG_WTSSM_ID_CTWW, &data);
	data &= ~WTSSM_ID_EN_WWO;
	AT_WWITE_WEG(hw, WEG_WTSSM_ID_CTWW, data);

	atw1c_pcie_patch(hw);
	if (fwag & ATW1C_PCIE_W0S_W1_DISABWE)
		atw1c_disabwe_w0s_w1(hw);

	msweep(5);
}

/**
 * atw1c_iwq_enabwe - Enabwe defauwt intewwupt genewation settings
 * @adaptew: boawd pwivate stwuctuwe
 */
static inwine void atw1c_iwq_enabwe(stwuct atw1c_adaptew *adaptew)
{
	if (wikewy(atomic_dec_and_test(&adaptew->iwq_sem))) {
		AT_WWITE_WEG(&adaptew->hw, WEG_ISW, 0x7FFFFFFF);
		AT_WWITE_WEG(&adaptew->hw, WEG_IMW, adaptew->hw.intw_mask);
		AT_WWITE_FWUSH(&adaptew->hw);
	}
}

/**
 * atw1c_iwq_disabwe - Mask off intewwupt genewation on the NIC
 * @adaptew: boawd pwivate stwuctuwe
 */
static inwine void atw1c_iwq_disabwe(stwuct atw1c_adaptew *adaptew)
{
	atomic_inc(&adaptew->iwq_sem);
	AT_WWITE_WEG(&adaptew->hw, WEG_IMW, 0);
	AT_WWITE_WEG(&adaptew->hw, WEG_ISW, ISW_DIS_INT);
	AT_WWITE_FWUSH(&adaptew->hw);
	synchwonize_iwq(adaptew->pdev->iwq);
}

/*
 * atw1c_wait_untiw_idwe - wait up to AT_HW_MAX_IDWE_DEWAY weads
 * of the idwe status wegistew untiw the device is actuawwy idwe
 */
static u32 atw1c_wait_untiw_idwe(stwuct atw1c_hw *hw, u32 modu_ctww)
{
	int timeout;
	u32 data;

	fow (timeout = 0; timeout < AT_HW_MAX_IDWE_DEWAY; timeout++) {
		AT_WEAD_WEG(hw, WEG_IDWE_STATUS, &data);
		if ((data & modu_ctww) == 0)
			wetuwn 0;
		msweep(1);
	}
	wetuwn data;
}

/**
 * atw1c_phy_config - Timew Caww-back
 * @t: timew wist containing pointew to netdev cast into an unsigned wong
 */
static void atw1c_phy_config(stwuct timew_wist *t)
{
	stwuct atw1c_adaptew *adaptew = fwom_timew(adaptew, t,
						   phy_config_timew);
	stwuct atw1c_hw *hw = &adaptew->hw;
	unsigned wong fwags;

	spin_wock_iwqsave(&adaptew->mdio_wock, fwags);
	atw1c_westawt_autoneg(hw);
	spin_unwock_iwqwestowe(&adaptew->mdio_wock, fwags);
}

void atw1c_weinit_wocked(stwuct atw1c_adaptew *adaptew)
{
	atw1c_down(adaptew);
	atw1c_up(adaptew);
	cweaw_bit(__AT_WESETTING, &adaptew->fwags);
}

static void atw1c_check_wink_status(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_hw *hw = &adaptew->hw;
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pci_dev    *pdev   = adaptew->pdev;
	int eww;
	unsigned wong fwags;
	u16 speed, dupwex;
	boow wink;

	spin_wock_iwqsave(&adaptew->mdio_wock, fwags);
	wink = atw1c_get_wink_status(hw);
	spin_unwock_iwqwestowe(&adaptew->mdio_wock, fwags);

	if (!wink) {
		/* wink down */
		netif_cawwiew_off(netdev);
		hw->hibewnate = twue;
		if (atw1c_weset_mac(hw) != 0)
			if (netif_msg_hw(adaptew))
				dev_wawn(&pdev->dev, "weset mac faiwed\n");
		atw1c_set_aspm(hw, SPEED_0);
		atw1c_post_phy_winkchg(hw, SPEED_0);
		atw1c_weset_dma_wing(adaptew);
		atw1c_configuwe(adaptew);
	} ewse {
		/* Wink Up */
		hw->hibewnate = fawse;
		spin_wock_iwqsave(&adaptew->mdio_wock, fwags);
		eww = atw1c_get_speed_and_dupwex(hw, &speed, &dupwex);
		spin_unwock_iwqwestowe(&adaptew->mdio_wock, fwags);
		if (unwikewy(eww))
			wetuwn;
		/* wink wesuwt is ouw setting */
		if (adaptew->wink_speed != speed ||
		    adaptew->wink_dupwex != dupwex) {
			adaptew->wink_speed  = speed;
			adaptew->wink_dupwex = dupwex;
			atw1c_set_aspm(hw, speed);
			atw1c_post_phy_winkchg(hw, speed);
			atw1c_stawt_mac(adaptew);
			if (netif_msg_wink(adaptew))
				dev_info(&pdev->dev,
					"%s: %s NIC Wink is Up<%d Mbps %s>\n",
					atw1c_dwivew_name, netdev->name,
					adaptew->wink_speed,
					adaptew->wink_dupwex == FUWW_DUPWEX ?
					"Fuww Dupwex" : "Hawf Dupwex");
		}
		if (!netif_cawwiew_ok(netdev))
			netif_cawwiew_on(netdev);
	}
}

static void atw1c_wink_chg_event(stwuct atw1c_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct pci_dev    *pdev   = adaptew->pdev;
	boow wink;

	spin_wock(&adaptew->mdio_wock);
	wink = atw1c_get_wink_status(&adaptew->hw);
	spin_unwock(&adaptew->mdio_wock);
	/* notify uppew wayew wink down ASAP */
	if (!wink) {
		if (netif_cawwiew_ok(netdev)) {
			/* owd wink state: Up */
			netif_cawwiew_off(netdev);
			if (netif_msg_wink(adaptew))
				dev_info(&pdev->dev,
					"%s: %s NIC Wink is Down\n",
					atw1c_dwivew_name, netdev->name);
			adaptew->wink_speed = SPEED_0;
		}
	}

	set_bit(ATW1C_WOWK_EVENT_WINK_CHANGE, &adaptew->wowk_event);
	scheduwe_wowk(&adaptew->common_task);
}

static void atw1c_common_task(stwuct wowk_stwuct *wowk)
{
	stwuct atw1c_adaptew *adaptew;
	stwuct net_device *netdev;

	adaptew = containew_of(wowk, stwuct atw1c_adaptew, common_task);
	netdev = adaptew->netdev;

	if (test_bit(__AT_DOWN, &adaptew->fwags))
		wetuwn;

	if (test_and_cweaw_bit(ATW1C_WOWK_EVENT_WESET, &adaptew->wowk_event)) {
		netif_device_detach(netdev);
		atw1c_down(adaptew);
		atw1c_up(adaptew);
		netif_device_attach(netdev);
	}

	if (test_and_cweaw_bit(ATW1C_WOWK_EVENT_WINK_CHANGE,
		&adaptew->wowk_event)) {
		atw1c_iwq_disabwe(adaptew);
		atw1c_check_wink_status(adaptew);
		atw1c_iwq_enabwe(adaptew);
	}
}


static void atw1c_dew_timew(stwuct atw1c_adaptew *adaptew)
{
	dew_timew_sync(&adaptew->phy_config_timew);
}


/**
 * atw1c_tx_timeout - Wespond to a Tx Hang
 * @netdev: netwowk intewface device stwuctuwe
 * @txqueue: index of hanging tx queue
 */
static void atw1c_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	/* Do the weset outside of intewwupt context */
	set_bit(ATW1C_WOWK_EVENT_WESET, &adaptew->wowk_event);
	scheduwe_wowk(&adaptew->common_task);
}

/**
 * atw1c_set_muwti - Muwticast and Pwomiscuous mode set
 * @netdev: netwowk intewface device stwuctuwe
 *
 * The set_muwti entwy point is cawwed whenevew the muwticast addwess
 * wist ow the netwowk intewface fwags awe updated.  This woutine is
 * wesponsibwe fow configuwing the hawdwawe fow pwopew muwticast,
 * pwomiscuous mode, and aww-muwti behaviow.
 */
static void atw1c_set_muwti(stwuct net_device *netdev)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1c_hw *hw = &adaptew->hw;
	stwuct netdev_hw_addw *ha;
	u32 mac_ctww_data;
	u32 hash_vawue;

	/* Check fow Pwomiscuous and Aww Muwticast modes */
	AT_WEAD_WEG(hw, WEG_MAC_CTWW, &mac_ctww_data);

	if (netdev->fwags & IFF_PWOMISC) {
		mac_ctww_data |= MAC_CTWW_PWOMIS_EN;
	} ewse if (netdev->fwags & IFF_AWWMUWTI) {
		mac_ctww_data |= MAC_CTWW_MC_AWW_EN;
		mac_ctww_data &= ~MAC_CTWW_PWOMIS_EN;
	} ewse {
		mac_ctww_data &= ~(MAC_CTWW_PWOMIS_EN | MAC_CTWW_MC_AWW_EN);
	}

	AT_WWITE_WEG(hw, WEG_MAC_CTWW, mac_ctww_data);

	/* cweaw the owd settings fwom the muwticast hash tabwe */
	AT_WWITE_WEG(hw, WEG_WX_HASH_TABWE, 0);
	AT_WWITE_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, 1, 0);

	/* comoute mc addwesses' hash vawue ,and put it into hash tabwe */
	netdev_fow_each_mc_addw(ha, netdev) {
		hash_vawue = atw1c_hash_mc_addw(hw, ha->addw);
		atw1c_hash_set(hw, hash_vawue);
	}
}

static void __atw1c_vwan_mode(netdev_featuwes_t featuwes, u32 *mac_ctww_data)
{
	if (featuwes & NETIF_F_HW_VWAN_CTAG_WX) {
		/* enabwe VWAN tag insewt/stwip */
		*mac_ctww_data |= MAC_CTWW_WMV_VWAN;
	} ewse {
		/* disabwe VWAN tag insewt/stwip */
		*mac_ctww_data &= ~MAC_CTWW_WMV_VWAN;
	}
}

static void atw1c_vwan_mode(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pci_dev *pdev = adaptew->pdev;
	u32 mac_ctww_data = 0;

	if (netif_msg_pktdata(adaptew))
		dev_dbg(&pdev->dev, "atw1c_vwan_mode\n");

	atw1c_iwq_disabwe(adaptew);
	AT_WEAD_WEG(&adaptew->hw, WEG_MAC_CTWW, &mac_ctww_data);
	__atw1c_vwan_mode(featuwes, &mac_ctww_data);
	AT_WWITE_WEG(&adaptew->hw, WEG_MAC_CTWW, mac_ctww_data);
	atw1c_iwq_enabwe(adaptew);
}

static void atw1c_westowe_vwan(stwuct atw1c_adaptew *adaptew)
{
	stwuct pci_dev *pdev = adaptew->pdev;

	if (netif_msg_pktdata(adaptew))
		dev_dbg(&pdev->dev, "atw1c_westowe_vwan\n");
	atw1c_vwan_mode(adaptew->netdev, adaptew->netdev->featuwes);
}

/**
 * atw1c_set_mac_addw - Change the Ethewnet Addwess of the NIC
 * @netdev: netwowk intewface device stwuctuwe
 * @p: pointew to an addwess stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int atw1c_set_mac_addw(stwuct net_device *netdev, void *p)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	if (netif_wunning(netdev))
		wetuwn -EBUSY;

	eth_hw_addw_set(netdev, addw->sa_data);
	memcpy(adaptew->hw.mac_addw, addw->sa_data, netdev->addw_wen);

	atw1c_hw_set_mac_addw(&adaptew->hw, adaptew->hw.mac_addw);

	wetuwn 0;
}

static void atw1c_set_wxbufsize(stwuct atw1c_adaptew *adaptew,
				stwuct net_device *dev)
{
	int mtu = dev->mtu;

	adaptew->wx_buffew_wen = mtu > AT_WX_BUF_SIZE ?
		woundup(mtu + ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN, 8) : AT_WX_BUF_SIZE;
}

static netdev_featuwes_t atw1c_fix_featuwes(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1c_hw *hw = &adaptew->hw;

	/*
	 * Since thewe is no suppowt fow sepawate wx/tx vwan accew
	 * enabwe/disabwe make suwe tx fwag is awways in same state as wx.
	 */
	if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
		featuwes |= NETIF_F_HW_VWAN_CTAG_TX;
	ewse
		featuwes &= ~NETIF_F_HW_VWAN_CTAG_TX;

	if (hw->nic_type != athw_mt) {
		if (netdev->mtu > MAX_TSO_FWAME_SIZE)
			featuwes &= ~(NETIF_F_TSO | NETIF_F_TSO6);
	}

	wetuwn featuwes;
}

static int atw1c_set_featuwes(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = netdev->featuwes ^ featuwes;

	if (changed & NETIF_F_HW_VWAN_CTAG_WX)
		atw1c_vwan_mode(netdev, featuwes);

	wetuwn 0;
}

static void atw1c_set_max_mtu(stwuct net_device *netdev)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1c_hw *hw = &adaptew->hw;

	switch (hw->nic_type) {
	/* These (GbE) devices suppowt jumbo packets, max_mtu 6122 */
	case athw_w1c:
	case athw_w1d:
	case athw_w1d_2:
		netdev->max_mtu = MAX_JUMBO_FWAME_SIZE -
			(ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN);
		bweak;
	case athw_mt:
		netdev->max_mtu = 9500;
		bweak;
		/* The 10/100 devices don't suppowt jumbo packets, max_mtu 1500 */
	defauwt:
		netdev->max_mtu = ETH_DATA_WEN;
		bweak;
	}
}

/**
 * atw1c_change_mtu - Change the Maximum Twansfew Unit
 * @netdev: netwowk intewface device stwuctuwe
 * @new_mtu: new vawue fow maximum fwame size
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int atw1c_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	/* set MTU */
	if (netif_wunning(netdev)) {
		whiwe (test_and_set_bit(__AT_WESETTING, &adaptew->fwags))
			msweep(1);
		netdev->mtu = new_mtu;
		adaptew->hw.max_fwame_size = new_mtu;
		atw1c_set_wxbufsize(adaptew, netdev);
		atw1c_down(adaptew);
		netdev_update_featuwes(netdev);
		atw1c_up(adaptew);
		cweaw_bit(__AT_WESETTING, &adaptew->fwags);
	}
	wetuwn 0;
}

/*
 *  cawwew shouwd howd mdio_wock
 */
static int atw1c_mdio_wead(stwuct net_device *netdev, int phy_id, int weg_num)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	u16 wesuwt;

	atw1c_wead_phy_weg(&adaptew->hw, weg_num, &wesuwt);
	wetuwn wesuwt;
}

static void atw1c_mdio_wwite(stwuct net_device *netdev, int phy_id,
			     int weg_num, int vaw)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	atw1c_wwite_phy_weg(&adaptew->hw, weg_num, vaw);
}

static int atw1c_mii_ioctw(stwuct net_device *netdev,
			   stwuct ifweq *ifw, int cmd)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct mii_ioctw_data *data = if_mii(ifw);
	unsigned wong fwags;
	int wetvaw = 0;

	if (!netif_wunning(netdev))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&adaptew->mdio_wock, fwags);
	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = 0;
		bweak;

	case SIOCGMIIWEG:
		if (atw1c_wead_phy_weg(&adaptew->hw, data->weg_num & 0x1F,
				    &data->vaw_out)) {
			wetvaw = -EIO;
			goto out;
		}
		bweak;

	case SIOCSMIIWEG:
		if (data->weg_num & ~(0x1F)) {
			wetvaw = -EFAUWT;
			goto out;
		}

		dev_dbg(&pdev->dev, "<atw1c_mii_ioctw> wwite %x %x",
				data->weg_num, data->vaw_in);
		if (atw1c_wwite_phy_weg(&adaptew->hw,
				     data->weg_num, data->vaw_in)) {
			wetvaw = -EIO;
			goto out;
		}
		bweak;

	defauwt:
		wetvaw = -EOPNOTSUPP;
		bweak;
	}
out:
	spin_unwock_iwqwestowe(&adaptew->mdio_wock, fwags);
	wetuwn wetvaw;
}

static int atw1c_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
		wetuwn atw1c_mii_ioctw(netdev, ifw, cmd);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * atw1c_awwoc_queues - Awwocate memowy fow aww wings
 * @adaptew: boawd pwivate stwuctuwe to initiawize
 *
 */
static int atw1c_awwoc_queues(stwuct atw1c_adaptew *adaptew)
{
	wetuwn 0;
}

static enum atw1c_nic_type atw1c_get_mac_type(stwuct pci_dev *pdev,
					      u8 __iomem *hw_addw)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_ATTANSIC_W2C:
		wetuwn athw_w2c;
	case PCI_DEVICE_ID_ATTANSIC_W1C:
		wetuwn athw_w1c;
	case PCI_DEVICE_ID_ATHEWOS_W2C_B:
		wetuwn athw_w2c_b;
	case PCI_DEVICE_ID_ATHEWOS_W2C_B2:
		wetuwn athw_w2c_b2;
	case PCI_DEVICE_ID_ATHEWOS_W1D:
		wetuwn athw_w1d;
	case PCI_DEVICE_ID_ATHEWOS_W1D_2_0:
		if (weadw(hw_addw + WEG_MT_MAGIC) == MT_MAGIC)
			wetuwn athw_mt;
		wetuwn athw_w1d_2;
	defauwt:
		wetuwn athw_w1c;
	}
}

static int atw1c_setup_mac_funcs(stwuct atw1c_hw *hw)
{
	u32 wink_ctww_data;

	AT_WEAD_WEG(hw, WEG_WINK_CTWW, &wink_ctww_data);

	hw->ctww_fwags = ATW1C_INTW_MODWT_ENABWE  |
			 ATW1C_TXQ_MODE_ENHANCE;
	hw->ctww_fwags |= ATW1C_ASPM_W0S_SUPPOWT |
			  ATW1C_ASPM_W1_SUPPOWT;
	hw->ctww_fwags |= ATW1C_ASPM_CTWW_MON;

	if (hw->nic_type == athw_w1c ||
	    hw->nic_type == athw_w1d ||
	    hw->nic_type == athw_w1d_2)
		hw->wink_cap_fwags |= ATW1C_WINK_CAP_1000M;
	wetuwn 0;
}

stwuct atw1c_pwatfowm_patch {
	u16 pci_did;
	u8  pci_wevid;
	u16 subsystem_vid;
	u16 subsystem_did;
	u32 patch_fwag;
#define ATW1C_WINK_PATCH	0x1
};
static const stwuct atw1c_pwatfowm_patch pwats[] = {
{0x2060, 0xC1, 0x1019, 0x8152, 0x1},
{0x2060, 0xC1, 0x1019, 0x2060, 0x1},
{0x2060, 0xC1, 0x1019, 0xE000, 0x1},
{0x2062, 0xC0, 0x1019, 0x8152, 0x1},
{0x2062, 0xC0, 0x1019, 0x2062, 0x1},
{0x2062, 0xC0, 0x1458, 0xE000, 0x1},
{0x2062, 0xC1, 0x1019, 0x8152, 0x1},
{0x2062, 0xC1, 0x1019, 0x2062, 0x1},
{0x2062, 0xC1, 0x1458, 0xE000, 0x1},
{0x2062, 0xC1, 0x1565, 0x2802, 0x1},
{0x2062, 0xC1, 0x1565, 0x2801, 0x1},
{0x1073, 0xC0, 0x1019, 0x8151, 0x1},
{0x1073, 0xC0, 0x1019, 0x1073, 0x1},
{0x1073, 0xC0, 0x1458, 0xE000, 0x1},
{0x1083, 0xC0, 0x1458, 0xE000, 0x1},
{0x1083, 0xC0, 0x1019, 0x8151, 0x1},
{0x1083, 0xC0, 0x1019, 0x1083, 0x1},
{0x1083, 0xC0, 0x1462, 0x7680, 0x1},
{0x1083, 0xC0, 0x1565, 0x2803, 0x1},
{0},
};

static void atw1c_patch_assign(stwuct atw1c_hw *hw)
{
	stwuct pci_dev	*pdev = hw->adaptew->pdev;
	u32 misc_ctww;
	int i = 0;

	hw->msi_wnkpatch = fawse;

	whiwe (pwats[i].pci_did != 0) {
		if (pwats[i].pci_did == hw->device_id &&
		    pwats[i].pci_wevid == hw->wevision_id &&
		    pwats[i].subsystem_vid == hw->subsystem_vendow_id &&
		    pwats[i].subsystem_did == hw->subsystem_id) {
			if (pwats[i].patch_fwag & ATW1C_WINK_PATCH)
				hw->msi_wnkpatch = twue;
		}
		i++;
	}

	if (hw->device_id == PCI_DEVICE_ID_ATHEWOS_W2C_B2 &&
	    hw->wevision_id == W2CB_V21) {
		/* config access mode */
		pci_wwite_config_dwowd(pdev, WEG_PCIE_IND_ACC_ADDW,
				       WEG_PCIE_DEV_MISC_CTWW);
		pci_wead_config_dwowd(pdev, WEG_PCIE_IND_ACC_DATA, &misc_ctww);
		misc_ctww &= ~0x100;
		pci_wwite_config_dwowd(pdev, WEG_PCIE_IND_ACC_ADDW,
				       WEG_PCIE_DEV_MISC_CTWW);
		pci_wwite_config_dwowd(pdev, WEG_PCIE_IND_ACC_DATA, misc_ctww);
	}
}
/**
 * atw1c_sw_init - Initiawize genewaw softwawe stwuctuwes (stwuct atw1c_adaptew)
 * @adaptew: boawd pwivate stwuctuwe to initiawize
 *
 * atw1c_sw_init initiawizes the Adaptew pwivate data stwuctuwe.
 * Fiewds awe initiawized based on PCI device infowmation and
 * OS netwowk device settings (MTU size).
 */
static int atw1c_sw_init(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_hw *hw   = &adaptew->hw;
	stwuct pci_dev	*pdev = adaptew->pdev;
	u32 wevision;
	int i;

	adaptew->wow = 0;
	device_set_wakeup_enabwe(&pdev->dev, fawse);
	adaptew->wink_speed = SPEED_0;
	adaptew->wink_dupwex = FUWW_DUPWEX;
	adaptew->tpd_wing[0].count = 1024;
	adaptew->wfd_wing[0].count = 512;

	hw->vendow_id = pdev->vendow;
	hw->device_id = pdev->device;
	hw->subsystem_vendow_id = pdev->subsystem_vendow;
	hw->subsystem_id = pdev->subsystem_device;
	pci_wead_config_dwowd(pdev, PCI_CWASS_WEVISION, &wevision);
	hw->wevision_id = wevision & 0xFF;
	/* befowe wink up, we assume hibewnate is twue */
	hw->hibewnate = twue;
	hw->media_type = MEDIA_TYPE_AUTO_SENSOW;
	if (atw1c_setup_mac_funcs(hw) != 0) {
		dev_eww(&pdev->dev, "set mac function pointews faiwed\n");
		wetuwn -1;
	}
	atw1c_patch_assign(hw);

	hw->intw_mask = IMW_NOWMAW_MASK;
	fow (i = 0; i < adaptew->tx_queue_count; ++i)
		hw->intw_mask |= atw1c_qwegs[i].tx_isw;
	fow (i = 0; i < adaptew->wx_queue_count; ++i)
		hw->intw_mask |= atw1c_qwegs[i].wx_isw;
	hw->phy_configuwed = fawse;
	hw->pweambwe_wen = 7;
	hw->max_fwame_size = adaptew->netdev->mtu;
	hw->autoneg_advewtised = ADVEWTISED_Autoneg;
	hw->indiwect_tab = 0xE4E4E4E4;
	hw->base_cpu = 0;

	hw->ict = 50000;		/* 100ms */
	hw->smb_timew = 200000;	  	/* 400ms */
	hw->wx_imt = 200;
	hw->tx_imt = 1000;

	hw->tpd_buwst = 5;
	hw->wfd_buwst = 8;
	hw->dma_owdew = atw1c_dma_owd_out;
	hw->dmaw_bwock = atw1c_dma_weq_1024;

	if (atw1c_awwoc_queues(adaptew)) {
		dev_eww(&pdev->dev, "Unabwe to awwocate memowy fow queues\n");
		wetuwn -ENOMEM;
	}
	/* TODO */
	atw1c_set_wxbufsize(adaptew, adaptew->netdev);
	atomic_set(&adaptew->iwq_sem, 1);
	spin_wock_init(&adaptew->mdio_wock);
	spin_wock_init(&adaptew->hw.intw_mask_wock);
	set_bit(__AT_DOWN, &adaptew->fwags);

	wetuwn 0;
}

static inwine void atw1c_cwean_buffew(stwuct pci_dev *pdev,
				      stwuct atw1c_buffew *buffew_info,
				      int budget)
{
	u16 pci_dwiection;
	if (buffew_info->fwags & ATW1C_BUFFEW_FWEE)
		wetuwn;
	if (buffew_info->dma) {
		if (buffew_info->fwags & ATW1C_PCIMAP_FWOMDEVICE)
			pci_dwiection = DMA_FWOM_DEVICE;
		ewse
			pci_dwiection = DMA_TO_DEVICE;

		if (buffew_info->fwags & ATW1C_PCIMAP_SINGWE)
			dma_unmap_singwe(&pdev->dev, buffew_info->dma,
					 buffew_info->wength, pci_dwiection);
		ewse if (buffew_info->fwags & ATW1C_PCIMAP_PAGE)
			dma_unmap_page(&pdev->dev, buffew_info->dma,
				       buffew_info->wength, pci_dwiection);
	}
	if (buffew_info->skb)
		napi_consume_skb(buffew_info->skb, budget);
	buffew_info->dma = 0;
	buffew_info->skb = NUWW;
	ATW1C_SET_BUFFEW_STATE(buffew_info, ATW1C_BUFFEW_FWEE);
}
/**
 * atw1c_cwean_tx_wing - Fwee Tx-skb
 * @adaptew: boawd pwivate stwuctuwe
 * @queue: idx of twansmit queue
 */
static void atw1c_cwean_tx_wing(stwuct atw1c_adaptew *adaptew,
				u32 queue)
{
	stwuct atw1c_tpd_wing *tpd_wing = &adaptew->tpd_wing[queue];
	stwuct atw1c_buffew *buffew_info;
	stwuct pci_dev *pdev = adaptew->pdev;
	u16 index, wing_count;

	wing_count = tpd_wing->count;
	fow (index = 0; index < wing_count; index++) {
		buffew_info = &tpd_wing->buffew_info[index];
		atw1c_cwean_buffew(pdev, buffew_info, 0);
	}

	netdev_tx_weset_queue(netdev_get_tx_queue(adaptew->netdev, queue));

	/* Zewo out Tx-buffews */
	memset(tpd_wing->desc, 0, sizeof(stwuct atw1c_tpd_desc) *
		wing_count);
	atomic_set(&tpd_wing->next_to_cwean, 0);
	tpd_wing->next_to_use = 0;
}

/**
 * atw1c_cwean_wx_wing - Fwee wx-wesewvation skbs
 * @adaptew: boawd pwivate stwuctuwe
 * @queue: idx of twansmit queue
 */
static void atw1c_cwean_wx_wing(stwuct atw1c_adaptew *adaptew, u32 queue)
{
	stwuct atw1c_wfd_wing *wfd_wing = &adaptew->wfd_wing[queue];
	stwuct atw1c_wwd_wing *wwd_wing = &adaptew->wwd_wing[queue];
	stwuct atw1c_buffew *buffew_info;
	stwuct pci_dev *pdev = adaptew->pdev;
	int j;

	fow (j = 0; j < wfd_wing->count; j++) {
		buffew_info = &wfd_wing->buffew_info[j];
		atw1c_cwean_buffew(pdev, buffew_info, 0);
	}
	/* zewo out the descwiptow wing */
	memset(wfd_wing->desc, 0, wfd_wing->size);
	wfd_wing->next_to_cwean = 0;
	wfd_wing->next_to_use = 0;
	wwd_wing->next_to_use = 0;
	wwd_wing->next_to_cwean = 0;
}

/*
 * Wead / Wwite Ptw Initiawize:
 */
static void atw1c_init_wing_ptws(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_tpd_wing *tpd_wing = adaptew->tpd_wing;
	stwuct atw1c_wfd_wing *wfd_wing = adaptew->wfd_wing;
	stwuct atw1c_wwd_wing *wwd_wing = adaptew->wwd_wing;
	stwuct atw1c_buffew *buffew_info;
	int i, j;

	fow (i = 0; i < adaptew->tx_queue_count; i++) {
		tpd_wing[i].next_to_use = 0;
		atomic_set(&tpd_wing[i].next_to_cwean, 0);
		buffew_info = tpd_wing[i].buffew_info;
		fow (j = 0; j < tpd_wing->count; j++)
			ATW1C_SET_BUFFEW_STATE(&buffew_info[i],
					       ATW1C_BUFFEW_FWEE);
	}
	fow (i = 0; i < adaptew->wx_queue_count; i++) {
		wfd_wing[i].next_to_use = 0;
		wfd_wing[i].next_to_cwean = 0;
		wwd_wing[i].next_to_use = 0;
		wwd_wing[i].next_to_cwean = 0;
		fow (j = 0; j < wfd_wing[i].count; j++) {
			buffew_info = &wfd_wing[i].buffew_info[j];
			ATW1C_SET_BUFFEW_STATE(buffew_info, ATW1C_BUFFEW_FWEE);
		}
	}
}

/**
 * atw1c_fwee_wing_wesouwces - Fwee Tx / WX descwiptow Wesouwces
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Fwee aww twansmit softwawe wesouwces
 */
static void atw1c_fwee_wing_wesouwces(stwuct atw1c_adaptew *adaptew)
{
	stwuct pci_dev *pdev = adaptew->pdev;

	dma_fwee_cohewent(&pdev->dev, adaptew->wing_headew.size,
			  adaptew->wing_headew.desc, adaptew->wing_headew.dma);
	adaptew->wing_headew.desc = NUWW;

	/* Note: just fwee tdp_wing.buffew_info,
	 * it contain wfd_wing.buffew_info, do not doubwe fwee
	 */
	if (adaptew->tpd_wing[0].buffew_info) {
		kfwee(adaptew->tpd_wing[0].buffew_info);
		adaptew->tpd_wing[0].buffew_info = NUWW;
	}
}

/**
 * atw1c_setup_wing_wesouwces - awwocate Tx / WX descwiptow wesouwces
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static int atw1c_setup_wing_wesouwces(stwuct atw1c_adaptew *adaptew)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct atw1c_tpd_wing *tpd_wing = adaptew->tpd_wing;
	stwuct atw1c_wfd_wing *wfd_wing = adaptew->wfd_wing;
	stwuct atw1c_wwd_wing *wwd_wing = adaptew->wwd_wing;
	stwuct atw1c_wing_headew *wing_headew = &adaptew->wing_headew;
	int tqc = adaptew->tx_queue_count;
	int wqc = adaptew->wx_queue_count;
	int size;
	int i;
	int count = 0;
	u32 offset = 0;

	/* Even though onwy one tpd queue is actuawwy used, the "high"
	 * pwiowity tpd queue awso gets initiawized
	 */
	if (tqc == 1)
		tqc = 2;

	fow (i = 1; i < tqc; i++)
		tpd_wing[i].count = tpd_wing[0].count;

	size = sizeof(stwuct atw1c_buffew) * (tpd_wing->count * tqc +
					      wfd_wing->count * wqc);
	tpd_wing->buffew_info = kzawwoc(size, GFP_KEWNEW);
	if (unwikewy(!tpd_wing->buffew_info))
		goto eww_nomem;

	fow (i = 0; i < tqc; i++) {
		tpd_wing[i].adaptew = adaptew;
		tpd_wing[i].num = i;
		tpd_wing[i].buffew_info = (tpd_wing->buffew_info + count);
		count += tpd_wing[i].count;
	}

	fow (i = 0; i < wqc; i++) {
		wwd_wing[i].adaptew = adaptew;
		wwd_wing[i].num = i;
		wwd_wing[i].count = wfd_wing[0].count;
		wfd_wing[i].count = wfd_wing[0].count;
		wfd_wing[i].buffew_info = (tpd_wing->buffew_info + count);
		count += wfd_wing->count;
	}

	/*
	 * weaw wing DMA buffew
	 * each wing/bwock may need up to 8 bytes fow awignment, hence the
	 * additionaw bytes tacked onto the end.
	 */
	wing_headew->size =
		sizeof(stwuct atw1c_tpd_desc) * tpd_wing->count * tqc +
		sizeof(stwuct atw1c_wx_fwee_desc) * wfd_wing->count * wqc +
		sizeof(stwuct atw1c_wecv_wet_status) * wfd_wing->count * wqc +
		8 * 4;

	wing_headew->desc = dma_awwoc_cohewent(&pdev->dev, wing_headew->size,
					       &wing_headew->dma, GFP_KEWNEW);
	if (unwikewy(!wing_headew->desc)) {
		dev_eww(&pdev->dev, "couwd not get memowy fow DMA buffew\n");
		goto eww_nomem;
	}
	/* init TPD wing */

	tpd_wing[0].dma = woundup(wing_headew->dma, 8);
	offset = tpd_wing[0].dma - wing_headew->dma;
	fow (i = 0; i < tqc; i++) {
		tpd_wing[i].dma = wing_headew->dma + offset;
		tpd_wing[i].desc = (u8 *)wing_headew->desc + offset;
		tpd_wing[i].size =
			sizeof(stwuct atw1c_tpd_desc) * tpd_wing[i].count;
		offset += woundup(tpd_wing[i].size, 8);
	}
	fow (i = 0; i < wqc; i++) {
		/* init WFD wing */
		wfd_wing[i].dma = wing_headew->dma + offset;
		wfd_wing[i].desc = (u8 *)wing_headew->desc + offset;
		wfd_wing[i].size = sizeof(stwuct atw1c_wx_fwee_desc) *
			wfd_wing[i].count;
		offset += woundup(wfd_wing[i].size, 8);

		/* init WWD wing */
		wwd_wing[i].dma = wing_headew->dma + offset;
		wwd_wing[i].desc = (u8 *)wing_headew->desc + offset;
		wwd_wing[i].size = sizeof(stwuct atw1c_wecv_wet_status) *
			wwd_wing[i].count;
		offset += woundup(wwd_wing[i].size, 8);
	}

	wetuwn 0;

eww_nomem:
	kfwee(tpd_wing->buffew_info);
	wetuwn -ENOMEM;
}

static void atw1c_configuwe_des_wing(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_hw *hw = &adaptew->hw;
	stwuct atw1c_wfd_wing *wfd_wing = adaptew->wfd_wing;
	stwuct atw1c_wwd_wing *wwd_wing = adaptew->wwd_wing;
	stwuct atw1c_tpd_wing *tpd_wing = adaptew->tpd_wing;
	int i;
	int tx_queue_count = adaptew->tx_queue_count;

	if (tx_queue_count == 1)
		tx_queue_count = 2;

	/* TPD */
	AT_WWITE_WEG(hw, WEG_TX_BASE_ADDW_HI,
		     (u32)((tpd_wing[0].dma & AT_DMA_HI_ADDW_MASK) >> 32));
	/* just enabwe nowmaw pwiowity TX queue */
	fow (i = 0; i < tx_queue_count; i++) {
		AT_WWITE_WEG(hw, atw1c_qwegs[i].tpd_addw_wo,
			     (u32)(tpd_wing[i].dma & AT_DMA_WO_ADDW_MASK));
	}
	AT_WWITE_WEG(hw, WEG_TPD_WING_SIZE,
			(u32)(tpd_wing[0].count & TPD_WING_SIZE_MASK));


	/* WFD */
	AT_WWITE_WEG(hw, WEG_WX_BASE_ADDW_HI,
		     (u32)((wfd_wing->dma & AT_DMA_HI_ADDW_MASK) >> 32));
	fow (i = 0; i < adaptew->wx_queue_count; i++) {
		AT_WWITE_WEG(hw, atw1c_qwegs[i].wfd_addw_wo,
			     (u32)(wfd_wing[i].dma & AT_DMA_WO_ADDW_MASK));
	}

	AT_WWITE_WEG(hw, WEG_WFD_WING_SIZE,
			wfd_wing->count & WFD_WING_SIZE_MASK);
	AT_WWITE_WEG(hw, WEG_WX_BUF_SIZE,
			adaptew->wx_buffew_wen & WX_BUF_SIZE_MASK);

	/* WWD */
	fow (i = 0; i < adaptew->wx_queue_count; i++) {
		AT_WWITE_WEG(hw, atw1c_qwegs[i].wwd_addw_wo,
			     (u32)(wwd_wing[i].dma & AT_DMA_WO_ADDW_MASK));
	}
	AT_WWITE_WEG(hw, WEG_WWD_WING_SIZE,
			(wwd_wing->count & WWD_WING_SIZE_MASK));

	if (hw->nic_type == athw_w2c_b) {
		AT_WWITE_WEG(hw, WEG_SWAM_WXF_WEN, 0x02a0W);
		AT_WWITE_WEG(hw, WEG_SWAM_TXF_WEN, 0x0100W);
		AT_WWITE_WEG(hw, WEG_SWAM_WXF_ADDW, 0x029f0000W);
		AT_WWITE_WEG(hw, WEG_SWAM_WFD0_INFO, 0x02bf02a0W);
		AT_WWITE_WEG(hw, WEG_SWAM_TXF_ADDW, 0x03bf02c0W);
		AT_WWITE_WEG(hw, WEG_SWAM_TWD_ADDW, 0x03df03c0W);
		AT_WWITE_WEG(hw, WEG_TXF_WATEW_MAWK, 0);	/* TX watewmawk, to entew w1 state.*/
		AT_WWITE_WEG(hw, WEG_WXD_DMA_CTWW, 0);		/* WXD thweshowd.*/
	}
	/* Woad aww of base addwess above */
	AT_WWITE_WEG(hw, WEG_WOAD_PTW, 1);
}

static void atw1c_configuwe_tx(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_hw *hw = &adaptew->hw;
	int max_pay_woad;
	u16 tx_offwoad_thwesh;
	u32 txq_ctww_data;

	tx_offwoad_thwesh = MAX_TSO_FWAME_SIZE;
	AT_WWITE_WEG(hw, WEG_TX_TSO_OFFWOAD_THWESH,
		(tx_offwoad_thwesh >> 3) & TX_TSO_OFFWOAD_THWESH_MASK);
	max_pay_woad = pcie_get_weadwq(adaptew->pdev) >> 8;
	hw->dmaw_bwock = min_t(u32, max_pay_woad, hw->dmaw_bwock);
	/*
	 * if BIOS had changed the dam-wead-max-wength to an invawid vawue,
	 * westowe it to defauwt vawue
	 */
	if (hw->dmaw_bwock < DEVICE_CTWW_MAXWWS_MIN) {
		pcie_set_weadwq(adaptew->pdev, 128 << DEVICE_CTWW_MAXWWS_MIN);
		hw->dmaw_bwock = DEVICE_CTWW_MAXWWS_MIN;
	}
	txq_ctww_data =
		hw->nic_type == athw_w2c_b || hw->nic_type == athw_w2c_b2 ?
		W2CB_TXQ_CFGV : W1C_TXQ_CFGV;

	AT_WWITE_WEG(hw, WEG_TXQ_CTWW, txq_ctww_data);
}

static void atw1c_configuwe_wx(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_hw *hw = &adaptew->hw;
	u32 wxq_ctww_data;

	wxq_ctww_data = (hw->wfd_buwst & WXQ_WFD_BUWST_NUM_MASK) <<
			WXQ_WFD_BUWST_NUM_SHIFT;

	if (hw->ctww_fwags & ATW1C_WX_IPV6_CHKSUM)
		wxq_ctww_data |= IPV6_CHKSUM_CTWW_EN;

	/* aspm fow gigabit */
	if (hw->nic_type != athw_w1d_2 && (hw->device_id & 1) != 0)
		wxq_ctww_data = FIEWD_SETX(wxq_ctww_data, ASPM_THWUPUT_WIMIT,
			ASPM_THWUPUT_WIMIT_100M);

	AT_WWITE_WEG(hw, WEG_WXQ_CTWW, wxq_ctww_data);
}

static void atw1c_configuwe_dma(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_hw *hw = &adaptew->hw;
	u32 dma_ctww_data;

	dma_ctww_data = FIEWDX(DMA_CTWW_WOWDEW_MODE, DMA_CTWW_WOWDEW_MODE_OUT) |
		DMA_CTWW_WWEQ_PWI_DATA |
		FIEWDX(DMA_CTWW_WWEQ_BWEN, hw->dmaw_bwock) |
		FIEWDX(DMA_CTWW_WDWY_CNT, DMA_CTWW_WDWY_CNT_DEF) |
		FIEWDX(DMA_CTWW_WDWY_CNT, DMA_CTWW_WDWY_CNT_DEF);

	AT_WWITE_WEG(hw, WEG_DMA_CTWW, dma_ctww_data);
}

/*
 * Stop the mac, twansmit and weceive units
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * wetuwn : 0  ow  idwe status (if ewwow)
 */
static int atw1c_stop_mac(stwuct atw1c_hw *hw)
{
	u32 data;

	AT_WEAD_WEG(hw, WEG_WXQ_CTWW, &data);
	data &= ~WXQ_CTWW_EN;
	AT_WWITE_WEG(hw, WEG_WXQ_CTWW, data);

	AT_WEAD_WEG(hw, WEG_TXQ_CTWW, &data);
	data &= ~TXQ_CTWW_EN;
	AT_WWITE_WEG(hw, WEG_TXQ_CTWW, data);

	atw1c_wait_untiw_idwe(hw, IDWE_STATUS_WXQ_BUSY | IDWE_STATUS_TXQ_BUSY);

	AT_WEAD_WEG(hw, WEG_MAC_CTWW, &data);
	data &= ~(MAC_CTWW_TX_EN | MAC_CTWW_WX_EN);
	AT_WWITE_WEG(hw, WEG_MAC_CTWW, data);

	wetuwn (int)atw1c_wait_untiw_idwe(hw,
		IDWE_STATUS_TXMAC_BUSY | IDWE_STATUS_WXMAC_BUSY);
}

static void atw1c_stawt_mac(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_hw *hw = &adaptew->hw;
	u32 mac, txq, wxq;

	hw->mac_dupwex = adaptew->wink_dupwex == FUWW_DUPWEX;
	hw->mac_speed = adaptew->wink_speed == SPEED_1000 ?
		atw1c_mac_speed_1000 : atw1c_mac_speed_10_100;

	AT_WEAD_WEG(hw, WEG_TXQ_CTWW, &txq);
	AT_WEAD_WEG(hw, WEG_WXQ_CTWW, &wxq);
	AT_WEAD_WEG(hw, WEG_MAC_CTWW, &mac);

	txq |= TXQ_CTWW_EN;
	wxq |= WXQ_CTWW_EN;
	mac |= MAC_CTWW_TX_EN | MAC_CTWW_TX_FWOW |
	       MAC_CTWW_WX_EN | MAC_CTWW_WX_FWOW |
	       MAC_CTWW_ADD_CWC | MAC_CTWW_PAD |
	       MAC_CTWW_BC_EN | MAC_CTWW_SINGWE_PAUSE_EN |
	       MAC_CTWW_HASH_AWG_CWC32;
	if (hw->mac_dupwex)
		mac |= MAC_CTWW_DUPWX;
	ewse
		mac &= ~MAC_CTWW_DUPWX;
	mac = FIEWD_SETX(mac, MAC_CTWW_SPEED, hw->mac_speed);
	mac = FIEWD_SETX(mac, MAC_CTWW_PWMWEN, hw->pweambwe_wen);

	AT_WWITE_WEG(hw, WEG_TXQ_CTWW, txq);
	AT_WWITE_WEG(hw, WEG_WXQ_CTWW, wxq);
	AT_WWITE_WEG(hw, WEG_MAC_CTWW, mac);
}

/*
 * Weset the twansmit and weceive units; mask and cweaw aww intewwupts.
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * wetuwn : 0  ow  idwe status (if ewwow)
 */
static int atw1c_weset_mac(stwuct atw1c_hw *hw)
{
	stwuct atw1c_adaptew *adaptew = hw->adaptew;
	stwuct pci_dev *pdev = adaptew->pdev;
	u32 ctww_data = 0;

	atw1c_stop_mac(hw);
	/*
	 * Issue Soft Weset to the MAC.  This wiww weset the chip's
	 * twansmit, weceive, DMA.  It wiww not effect
	 * the cuwwent PCI configuwation.  The gwobaw weset bit is sewf-
	 * cweawing, and shouwd cweaw within a micwosecond.
	 */
	AT_WEAD_WEG(hw, WEG_MASTEW_CTWW, &ctww_data);
	ctww_data |= MASTEW_CTWW_OOB_DIS;
	AT_WWITE_WEG(hw, WEG_MASTEW_CTWW, ctww_data | MASTEW_CTWW_SOFT_WST);

	AT_WWITE_FWUSH(hw);
	msweep(10);
	/* Wait at weast 10ms fow Aww moduwe to be Idwe */

	if (atw1c_wait_untiw_idwe(hw, IDWE_STATUS_MASK)) {
		dev_eww(&pdev->dev,
			"MAC state machine can't be idwe since"
			" disabwed fow 10ms second\n");
		wetuwn -1;
	}
	AT_WWITE_WEG(hw, WEG_MASTEW_CTWW, ctww_data);

	/* dwivew contwow speed/dupwex */
	AT_WEAD_WEG(hw, WEG_MAC_CTWW, &ctww_data);
	AT_WWITE_WEG(hw, WEG_MAC_CTWW, ctww_data | MAC_CTWW_SPEED_MODE_SW);

	/* cwk switch setting */
	AT_WEAD_WEG(hw, WEG_SEWDES, &ctww_data);
	switch (hw->nic_type) {
	case athw_w2c_b:
		ctww_data &= ~(SEWDES_PHY_CWK_SWOWDOWN |
				SEWDES_MAC_CWK_SWOWDOWN);
		AT_WWITE_WEG(hw, WEG_SEWDES, ctww_data);
		bweak;
	case athw_w2c_b2:
	case athw_w1d_2:
		ctww_data |= SEWDES_PHY_CWK_SWOWDOWN | SEWDES_MAC_CWK_SWOWDOWN;
		AT_WWITE_WEG(hw, WEG_SEWDES, ctww_data);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void atw1c_disabwe_w0s_w1(stwuct atw1c_hw *hw)
{
	u16 ctww_fwags = hw->ctww_fwags;

	hw->ctww_fwags &= ~(ATW1C_ASPM_W0S_SUPPOWT | ATW1C_ASPM_W1_SUPPOWT);
	atw1c_set_aspm(hw, SPEED_0);
	hw->ctww_fwags = ctww_fwags;
}

/*
 * Set ASPM state.
 * Enabwe/disabwe W0s/W1 depend on wink state.
 */
static void atw1c_set_aspm(stwuct atw1c_hw *hw, u16 wink_speed)
{
	u32 pm_ctww_data;
	u32 wink_w1_timew;

	AT_WEAD_WEG(hw, WEG_PM_CTWW, &pm_ctww_data);
	pm_ctww_data &= ~(PM_CTWW_ASPM_W1_EN |
			  PM_CTWW_ASPM_W0S_EN |
			  PM_CTWW_MAC_ASPM_CHK);
	/* W1 timew */
	if (hw->nic_type == athw_w2c_b2 || hw->nic_type == athw_w1d_2) {
		pm_ctww_data &= ~PMCTWW_TXW1_AFTEW_W0S;
		wink_w1_timew =
			wink_speed == SPEED_1000 || wink_speed == SPEED_100 ?
			W1D_PMCTWW_W1_ENTWY_TM_16US : 1;
		pm_ctww_data = FIEWD_SETX(pm_ctww_data,
			W1D_PMCTWW_W1_ENTWY_TM, wink_w1_timew);
	} ewse {
		wink_w1_timew = hw->nic_type == athw_w2c_b ?
			W2CB1_PM_CTWW_W1_ENTWY_TM : W1C_PM_CTWW_W1_ENTWY_TM;
		if (wink_speed != SPEED_1000 && wink_speed != SPEED_100)
			wink_w1_timew = 1;
		pm_ctww_data = FIEWD_SETX(pm_ctww_data,
			PM_CTWW_W1_ENTWY_TIMEW, wink_w1_timew);
	}

	/* W0S/W1 enabwe */
	if ((hw->ctww_fwags & ATW1C_ASPM_W0S_SUPPOWT) && wink_speed != SPEED_0)
		pm_ctww_data |= PM_CTWW_ASPM_W0S_EN | PM_CTWW_MAC_ASPM_CHK;
	if (hw->ctww_fwags & ATW1C_ASPM_W1_SUPPOWT)
		pm_ctww_data |= PM_CTWW_ASPM_W1_EN | PM_CTWW_MAC_ASPM_CHK;

	/* w2cb & w1d & w2cb2 & w1d2 */
	if (hw->nic_type == athw_w2c_b || hw->nic_type == athw_w1d ||
	    hw->nic_type == athw_w2c_b2 || hw->nic_type == athw_w1d_2) {
		pm_ctww_data = FIEWD_SETX(pm_ctww_data,
			PM_CTWW_PM_WEQ_TIMEW, PM_CTWW_PM_WEQ_TO_DEF);
		pm_ctww_data |= PM_CTWW_WCVW_WT_TIMEW |
				PM_CTWW_SEWDES_PD_EX_W1 |
				PM_CTWW_CWK_SWH_W1;
		pm_ctww_data &= ~(PM_CTWW_SEWDES_W1_EN |
				  PM_CTWW_SEWDES_PWW_W1_EN |
				  PM_CTWW_SEWDES_BUFS_WX_W1_EN |
				  PM_CTWW_SA_DWY_EN |
				  PM_CTWW_HOTWST);
		/* disabwe w0s if wink down ow w2cb */
		if (wink_speed == SPEED_0 || hw->nic_type == athw_w2c_b)
			pm_ctww_data &= ~PM_CTWW_ASPM_W0S_EN;
	} ewse { /* w1c */
		pm_ctww_data =
			FIEWD_SETX(pm_ctww_data, PM_CTWW_W1_ENTWY_TIMEW, 0);
		if (wink_speed != SPEED_0) {
			pm_ctww_data |= PM_CTWW_SEWDES_W1_EN |
					PM_CTWW_SEWDES_PWW_W1_EN |
					PM_CTWW_SEWDES_BUFS_WX_W1_EN;
			pm_ctww_data &= ~(PM_CTWW_SEWDES_PD_EX_W1 |
					  PM_CTWW_CWK_SWH_W1 |
					  PM_CTWW_ASPM_W0S_EN |
					  PM_CTWW_ASPM_W1_EN);
		} ewse { /* wink down */
			pm_ctww_data |= PM_CTWW_CWK_SWH_W1;
			pm_ctww_data &= ~(PM_CTWW_SEWDES_W1_EN |
					  PM_CTWW_SEWDES_PWW_W1_EN |
					  PM_CTWW_SEWDES_BUFS_WX_W1_EN |
					  PM_CTWW_ASPM_W0S_EN);
		}
	}
	AT_WWITE_WEG(hw, WEG_PM_CTWW, pm_ctww_data);

	wetuwn;
}

/**
 * atw1c_configuwe_mac - Configuwe Twansmit&Weceive Unit aftew Weset
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Configuwe the Tx /Wx unit of the MAC aftew a weset.
 */
static int atw1c_configuwe_mac(stwuct atw1c_adaptew *adaptew)
{
	stwuct atw1c_hw *hw = &adaptew->hw;
	u32 mastew_ctww_data = 0;
	u32 intw_modwt_data;
	u32 data;

	AT_WEAD_WEG(hw, WEG_MASTEW_CTWW, &mastew_ctww_data);
	mastew_ctww_data &= ~(MASTEW_CTWW_TX_ITIMEW_EN |
			      MASTEW_CTWW_WX_ITIMEW_EN |
			      MASTEW_CTWW_INT_WDCWW);
	/* cweaw intewwupt status */
	AT_WWITE_WEG(hw, WEG_ISW, 0xFFFFFFFF);
	/*  Cweaw any WOW status */
	AT_WWITE_WEG(hw, WEG_WOW_CTWW, 0);
	/* set Intewwupt Cweaw Timew
	 * HW wiww enabwe sewf to assewt intewwupt event to system aftew
	 * waiting x-time fow softwawe to notify it accept intewwupt.
	 */

	data = CWK_GATING_EN_AWW;
	if (hw->ctww_fwags & ATW1C_CWK_GATING_EN) {
		if (hw->nic_type == athw_w2c_b)
			data &= ~CWK_GATING_WXMAC_EN;
	} ewse
		data = 0;
	AT_WWITE_WEG(hw, WEG_CWK_GATING_CTWW, data);

	AT_WWITE_WEG(hw, WEG_INT_WETWIG_TIMEW,
		hw->ict & INT_WETWIG_TIMEW_MASK);

	atw1c_configuwe_des_wing(adaptew);

	if (hw->ctww_fwags & ATW1C_INTW_MODWT_ENABWE) {
		intw_modwt_data = (hw->tx_imt & IWQ_MODWT_TIMEW_MASK) <<
					IWQ_MODWT_TX_TIMEW_SHIFT;
		intw_modwt_data |= (hw->wx_imt & IWQ_MODWT_TIMEW_MASK) <<
					IWQ_MODWT_WX_TIMEW_SHIFT;
		AT_WWITE_WEG(hw, WEG_IWQ_MODWT_TIMEW_INIT, intw_modwt_data);
		mastew_ctww_data |=
			MASTEW_CTWW_TX_ITIMEW_EN | MASTEW_CTWW_WX_ITIMEW_EN;
	}

	if (hw->ctww_fwags & ATW1C_INTW_CWEAW_ON_WEAD)
		mastew_ctww_data |= MASTEW_CTWW_INT_WDCWW;

	mastew_ctww_data |= MASTEW_CTWW_SA_TIMEW_EN;
	AT_WWITE_WEG(hw, WEG_MASTEW_CTWW, mastew_ctww_data);

	AT_WWITE_WEG(hw, WEG_SMB_STAT_TIMEW,
		hw->smb_timew & SMB_STAT_TIMEW_MASK);

	/* set MTU */
	AT_WWITE_WEG(hw, WEG_MTU, hw->max_fwame_size + ETH_HWEN +
			VWAN_HWEN + ETH_FCS_WEN);

	atw1c_configuwe_tx(adaptew);
	atw1c_configuwe_wx(adaptew);
	atw1c_configuwe_dma(adaptew);

	wetuwn 0;
}

static int atw1c_configuwe(stwuct atw1c_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	int num;
	int i;

	if (adaptew->hw.nic_type == athw_mt) {
		u32 mode;

		AT_WEAD_WEG(&adaptew->hw, WEG_MT_MODE, &mode);
		if (adaptew->wx_queue_count == 4)
			mode |= MT_MODE_4Q;
		ewse
			mode &= ~MT_MODE_4Q;
		AT_WWITE_WEG(&adaptew->hw, WEG_MT_MODE, mode);
	}

	atw1c_init_wing_ptws(adaptew);
	atw1c_set_muwti(netdev);
	atw1c_westowe_vwan(adaptew);

	fow (i = 0; i < adaptew->wx_queue_count; ++i) {
		num = atw1c_awwoc_wx_buffew(adaptew, i, fawse);
		if (unwikewy(num == 0))
			wetuwn -ENOMEM;
	}

	if (atw1c_configuwe_mac(adaptew))
		wetuwn -EIO;

	wetuwn 0;
}

static void atw1c_update_hw_stats(stwuct atw1c_adaptew *adaptew)
{
	u16 hw_weg_addw = 0;
	unsigned wong *stats_item = NUWW;
	u32 data;

	/* update wx status */
	hw_weg_addw = WEG_MAC_WX_STATUS_BIN;
	stats_item  = &adaptew->hw_stats.wx_ok;
	whiwe (hw_weg_addw <= WEG_MAC_WX_STATUS_END) {
		AT_WEAD_WEG(&adaptew->hw, hw_weg_addw, &data);
		*stats_item += data;
		stats_item++;
		hw_weg_addw += 4;
	}
/* update tx status */
	hw_weg_addw = WEG_MAC_TX_STATUS_BIN;
	stats_item  = &adaptew->hw_stats.tx_ok;
	whiwe (hw_weg_addw <= WEG_MAC_TX_STATUS_END) {
		AT_WEAD_WEG(&adaptew->hw, hw_weg_addw, &data);
		*stats_item += data;
		stats_item++;
		hw_weg_addw += 4;
	}
}

/**
 * atw1c_get_stats - Get System Netwowk Statistics
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns the addwess of the device statistics stwuctuwe.
 * The statistics awe actuawwy updated fwom the timew cawwback.
 */
static stwuct net_device_stats *atw1c_get_stats(stwuct net_device *netdev)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1c_hw_stats  *hw_stats = &adaptew->hw_stats;
	stwuct net_device_stats *net_stats = &netdev->stats;

	atw1c_update_hw_stats(adaptew);
	net_stats->wx_bytes   = hw_stats->wx_byte_cnt;
	net_stats->tx_bytes   = hw_stats->tx_byte_cnt;
	net_stats->muwticast  = hw_stats->wx_mcast;
	net_stats->cowwisions = hw_stats->tx_1_cow +
				hw_stats->tx_2_cow +
				hw_stats->tx_wate_cow +
				hw_stats->tx_abowt_cow;

	net_stats->wx_ewwows  = hw_stats->wx_fwag +
				hw_stats->wx_fcs_eww +
				hw_stats->wx_wen_eww +
				hw_stats->wx_sz_ov +
				hw_stats->wx_wwd_ov +
				hw_stats->wx_awign_eww +
				hw_stats->wx_wxf_ov;

	net_stats->wx_fifo_ewwows   = hw_stats->wx_wxf_ov;
	net_stats->wx_wength_ewwows = hw_stats->wx_wen_eww;
	net_stats->wx_cwc_ewwows    = hw_stats->wx_fcs_eww;
	net_stats->wx_fwame_ewwows  = hw_stats->wx_awign_eww;
	net_stats->wx_dwopped       = hw_stats->wx_wwd_ov;

	net_stats->tx_ewwows = hw_stats->tx_wate_cow +
			       hw_stats->tx_abowt_cow +
			       hw_stats->tx_undewwun +
			       hw_stats->tx_twunc;

	net_stats->tx_fifo_ewwows    = hw_stats->tx_undewwun;
	net_stats->tx_abowted_ewwows = hw_stats->tx_abowt_cow;
	net_stats->tx_window_ewwows  = hw_stats->tx_wate_cow;

	net_stats->wx_packets = hw_stats->wx_ok + net_stats->wx_ewwows;
	net_stats->tx_packets = hw_stats->tx_ok + net_stats->tx_ewwows;

	wetuwn net_stats;
}

static inwine void atw1c_cweaw_phy_int(stwuct atw1c_adaptew *adaptew)
{
	u16 phy_data;

	spin_wock(&adaptew->mdio_wock);
	atw1c_wead_phy_weg(&adaptew->hw, MII_ISW, &phy_data);
	spin_unwock(&adaptew->mdio_wock);
}

static int atw1c_cwean_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct atw1c_tpd_wing *tpd_wing =
		containew_of(napi, stwuct atw1c_tpd_wing, napi);
	stwuct atw1c_adaptew *adaptew = tpd_wing->adaptew;
	stwuct netdev_queue *txq =
		netdev_get_tx_queue(napi->dev, tpd_wing->num);
	stwuct atw1c_buffew *buffew_info;
	stwuct pci_dev *pdev = adaptew->pdev;
	u16 next_to_cwean = atomic_wead(&tpd_wing->next_to_cwean);
	u16 hw_next_to_cwean;
	unsigned int totaw_bytes = 0, totaw_packets = 0;
	unsigned wong fwags;

	AT_WEAD_WEGW(&adaptew->hw, atw1c_qwegs[tpd_wing->num].tpd_cons,
		     &hw_next_to_cwean);

	whiwe (next_to_cwean != hw_next_to_cwean) {
		buffew_info = &tpd_wing->buffew_info[next_to_cwean];
		if (buffew_info->skb) {
			totaw_bytes += buffew_info->skb->wen;
			totaw_packets++;
		}
		atw1c_cwean_buffew(pdev, buffew_info, budget);
		if (++next_to_cwean == tpd_wing->count)
			next_to_cwean = 0;
		atomic_set(&tpd_wing->next_to_cwean, next_to_cwean);
	}

	netdev_tx_compweted_queue(txq, totaw_packets, totaw_bytes);

	if (netif_tx_queue_stopped(txq) && netif_cawwiew_ok(adaptew->netdev))
		netif_tx_wake_queue(txq);

	if (totaw_packets < budget) {
		napi_compwete_done(napi, totaw_packets);
		spin_wock_iwqsave(&adaptew->hw.intw_mask_wock, fwags);
		adaptew->hw.intw_mask |= atw1c_qwegs[tpd_wing->num].tx_isw;
		AT_WWITE_WEG(&adaptew->hw, WEG_IMW, adaptew->hw.intw_mask);
		spin_unwock_iwqwestowe(&adaptew->hw.intw_mask_wock, fwags);
		wetuwn totaw_packets;
	}
	wetuwn budget;
}

static void atw1c_intw_wx_tx(stwuct atw1c_adaptew *adaptew, u32 status)
{
	stwuct atw1c_hw *hw = &adaptew->hw;
	u32 intw_mask;
	int i;

	spin_wock(&hw->intw_mask_wock);
	intw_mask = hw->intw_mask;
	fow (i = 0; i < adaptew->wx_queue_count; ++i) {
		if (!(status & atw1c_qwegs[i].wx_isw))
			continue;
		if (napi_scheduwe_pwep(&adaptew->wwd_wing[i].napi)) {
			intw_mask &= ~atw1c_qwegs[i].wx_isw;
			__napi_scheduwe(&adaptew->wwd_wing[i].napi);
		}
	}
	fow (i = 0; i < adaptew->tx_queue_count; ++i) {
		if (!(status & atw1c_qwegs[i].tx_isw))
			continue;
		if (napi_scheduwe_pwep(&adaptew->tpd_wing[i].napi)) {
			intw_mask &= ~atw1c_qwegs[i].tx_isw;
			__napi_scheduwe(&adaptew->tpd_wing[i].napi);
		}
	}

	if (hw->intw_mask != intw_mask) {
		hw->intw_mask = intw_mask;
		AT_WWITE_WEG(hw, WEG_IMW, hw->intw_mask);
	}
	spin_unwock(&hw->intw_mask_wock);
}

/**
 * atw1c_intw - Intewwupt Handwew
 * @iwq: intewwupt numbew
 * @data: pointew to a netwowk intewface device stwuctuwe
 */
static iwqwetuwn_t atw1c_intw(int iwq, void *data)
{
	stwuct net_device *netdev  = data;
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct atw1c_hw *hw = &adaptew->hw;
	int max_ints = AT_MAX_INT_WOWK;
	int handwed = IWQ_NONE;
	u32 status;
	u32 weg_data;

	do {
		AT_WEAD_WEG(hw, WEG_ISW, &weg_data);
		status = weg_data & hw->intw_mask;

		if (status == 0 || (status & ISW_DIS_INT) != 0) {
			if (max_ints != AT_MAX_INT_WOWK)
				handwed = IWQ_HANDWED;
			bweak;
		}
		/* wink event */
		if (status & ISW_GPHY)
			atw1c_cweaw_phy_int(adaptew);
		/* Ack ISW */
		AT_WWITE_WEG(hw, WEG_ISW, status | ISW_DIS_INT);
		if (status & (ISW_WX_PKT | ISW_TX_PKT))
			atw1c_intw_wx_tx(adaptew, status);

		handwed = IWQ_HANDWED;
		/* check if PCIE PHY Wink down */
		if (status & ISW_EWWOW) {
			if (netif_msg_hw(adaptew))
				dev_eww(&pdev->dev,
					"atw1c hawdwawe ewwow (status = 0x%x)\n",
					status & ISW_EWWOW);
			/* weset MAC */
			set_bit(ATW1C_WOWK_EVENT_WESET, &adaptew->wowk_event);
			scheduwe_wowk(&adaptew->common_task);
			wetuwn IWQ_HANDWED;
		}

		if (status & ISW_OVEW)
			if (netif_msg_intw(adaptew))
				dev_wawn(&pdev->dev,
					"TX/WX ovewfwow (status = 0x%x)\n",
					status & ISW_OVEW);

		/* wink event */
		if (status & (ISW_GPHY | ISW_MANUAW)) {
			netdev->stats.tx_cawwiew_ewwows++;
			atw1c_wink_chg_event(adaptew);
			bweak;
		}

	} whiwe (--max_ints > 0);
	/* we-enabwe Intewwupt*/
	AT_WWITE_WEG(&adaptew->hw, WEG_ISW, 0);
	wetuwn handwed;
}

static inwine void atw1c_wx_checksum(stwuct atw1c_adaptew *adaptew,
		  stwuct sk_buff *skb, stwuct atw1c_wecv_wet_status *pwws)
{
	if (adaptew->hw.nic_type == athw_mt) {
		if (pwws->wowd3 & WWS_MT_PWOT_ID_TCPUDP)
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
		wetuwn;
	}
	/*
	 * The pid fiewd in WWS in not cowwect sometimes, so we
	 * cannot figuwe out if the packet is fwagmented ow not,
	 * so we teww the KEWNEW CHECKSUM_NONE
	 */
	skb_checksum_none_assewt(skb);
}

static int atw1c_awwoc_wx_buffew(stwuct atw1c_adaptew *adaptew, u32 queue,
				 boow napi_mode)
{
	stwuct atw1c_wfd_wing *wfd_wing = &adaptew->wfd_wing[queue];
	stwuct atw1c_wwd_wing *wwd_wing = &adaptew->wwd_wing[queue];
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct atw1c_buffew *buffew_info, *next_info;
	stwuct sk_buff *skb;
	void *viw_addw = NUWW;
	u16 num_awwoc = 0;
	u16 wfd_next_to_use, next_next;
	stwuct atw1c_wx_fwee_desc *wfd_desc;
	dma_addw_t mapping;

	next_next = wfd_next_to_use = wfd_wing->next_to_use;
	if (++next_next == wfd_wing->count)
		next_next = 0;
	buffew_info = &wfd_wing->buffew_info[wfd_next_to_use];
	next_info = &wfd_wing->buffew_info[next_next];

	whiwe (next_info->fwags & ATW1C_BUFFEW_FWEE) {
		wfd_desc = ATW1C_WFD_DESC(wfd_wing, wfd_next_to_use);

		/* When DMA WX addwess is set to something wike
		 * 0x....fc0, it wiww be vewy wikewy to cause DMA
		 * WFD ovewfwow issue.
		 *
		 * To wowk awound it, we appwy wx skb with 64 bytes
		 * wongew space, and offset the addwess whenevew
		 * 0x....fc0 is detected.
		 */
		if (wikewy(napi_mode))
			skb = napi_awwoc_skb(&wwd_wing->napi, adaptew->wx_buffew_wen + 64);
		ewse
			skb = netdev_awwoc_skb(adaptew->netdev, adaptew->wx_buffew_wen + 64);
		if (unwikewy(!skb)) {
			if (netif_msg_wx_eww(adaptew))
				dev_wawn(&pdev->dev, "awwoc wx buffew faiwed\n");
			bweak;
		}

		if (((unsigned wong)skb->data & 0xfff) == 0xfc0)
			skb_wesewve(skb, 64);

		/*
		 * Make buffew awignment 2 beyond a 16 byte boundawy
		 * this wiww wesuwt in a 16 byte awigned IP headew aftew
		 * the 14 byte MAC headew is wemoved
		 */
		viw_addw = skb->data;
		ATW1C_SET_BUFFEW_STATE(buffew_info, ATW1C_BUFFEW_BUSY);
		buffew_info->skb = skb;
		buffew_info->wength = adaptew->wx_buffew_wen;
		mapping = dma_map_singwe(&pdev->dev, viw_addw,
					 buffew_info->wength, DMA_FWOM_DEVICE);
		if (unwikewy(dma_mapping_ewwow(&pdev->dev, mapping))) {
			dev_kfwee_skb(skb);
			buffew_info->skb = NUWW;
			buffew_info->wength = 0;
			ATW1C_SET_BUFFEW_STATE(buffew_info, ATW1C_BUFFEW_FWEE);
			netif_wawn(adaptew, wx_eww, adaptew->netdev, "WX dma_map_singwe faiwed");
			bweak;
		}
		buffew_info->dma = mapping;
		ATW1C_SET_PCIMAP_TYPE(buffew_info, ATW1C_PCIMAP_SINGWE,
			ATW1C_PCIMAP_FWOMDEVICE);
		wfd_desc->buffew_addw = cpu_to_we64(buffew_info->dma);
		wfd_next_to_use = next_next;
		if (++next_next == wfd_wing->count)
			next_next = 0;
		buffew_info = &wfd_wing->buffew_info[wfd_next_to_use];
		next_info = &wfd_wing->buffew_info[next_next];
		num_awwoc++;
	}

	if (num_awwoc) {
		/* TODO: update maiwbox hewe */
		wmb();
		wfd_wing->next_to_use = wfd_next_to_use;
		AT_WWITE_WEG(&adaptew->hw, atw1c_qwegs[queue].wfd_pwod,
			     wfd_wing->next_to_use & MB_WFDX_PWOD_IDX_MASK);
	}

	wetuwn num_awwoc;
}

static void atw1c_cwean_wwd(stwuct atw1c_wwd_wing *wwd_wing,
			stwuct	atw1c_wecv_wet_status *wws, u16 num)
{
	u16 i;
	/* the wewationship between wwd and wfd is one map one */
	fow (i = 0; i < num; i++, wws = ATW1C_WWD_DESC(wwd_wing,
					wwd_wing->next_to_cwean)) {
		wws->wowd3 &= ~WWS_WXD_UPDATED;
		if (++wwd_wing->next_to_cwean == wwd_wing->count)
			wwd_wing->next_to_cwean = 0;
	}
}

static void atw1c_cwean_wfd(stwuct atw1c_wfd_wing *wfd_wing,
	stwuct atw1c_wecv_wet_status *wws, u16 num)
{
	u16 i;
	u16 wfd_index;
	stwuct atw1c_buffew *buffew_info = wfd_wing->buffew_info;

	wfd_index = (wws->wowd0 >> WWS_WX_WFD_INDEX_SHIFT) &
			WWS_WX_WFD_INDEX_MASK;
	fow (i = 0; i < num; i++) {
		buffew_info[wfd_index].skb = NUWW;
		ATW1C_SET_BUFFEW_STATE(&buffew_info[wfd_index],
					ATW1C_BUFFEW_FWEE);
		if (++wfd_index == wfd_wing->count)
			wfd_index = 0;
	}
	wfd_wing->next_to_cwean = wfd_index;
}

/**
 * atw1c_cwean_wx - NAPI Wx powwing cawwback
 * @napi: napi info
 * @budget: wimit of packets to cwean
 */
static int atw1c_cwean_wx(stwuct napi_stwuct *napi, int budget)
{
	stwuct atw1c_wwd_wing *wwd_wing =
		containew_of(napi, stwuct atw1c_wwd_wing, napi);
	stwuct atw1c_adaptew *adaptew = wwd_wing->adaptew;
	u16 wfd_num, wfd_index;
	u16 wength;
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct net_device *netdev  = adaptew->netdev;
	stwuct atw1c_wfd_wing *wfd_wing = &adaptew->wfd_wing[wwd_wing->num];
	stwuct sk_buff *skb;
	stwuct atw1c_wecv_wet_status *wws;
	stwuct atw1c_buffew *buffew_info;
	int wowk_done = 0;
	unsigned wong fwags;

	/* Keep wink state infowmation with owiginaw netdev */
	if (!netif_cawwiew_ok(adaptew->netdev))
		goto quit_powwing;

	whiwe (1) {
		if (wowk_done >= budget)
			bweak;
		wws = ATW1C_WWD_DESC(wwd_wing, wwd_wing->next_to_cwean);
		if (wikewy(WWS_WXD_IS_VAWID(wws->wowd3))) {
			wfd_num = (wws->wowd0 >> WWS_WX_WFD_CNT_SHIFT) &
				WWS_WX_WFD_CNT_MASK;
			if (unwikewy(wfd_num != 1))
				/* TODO suppowt muw wfd*/
				if (netif_msg_wx_eww(adaptew))
					dev_wawn(&pdev->dev,
						"Muwti wfd not suppowt yet!\n");
			goto wws_checked;
		} ewse {
			bweak;
		}
wws_checked:
		atw1c_cwean_wwd(wwd_wing, wws, wfd_num);
		if (wws->wowd3 & (WWS_WX_EWW_SUM | WWS_802_3_WEN_EWW)) {
			atw1c_cwean_wfd(wfd_wing, wws, wfd_num);
			if (netif_msg_wx_eww(adaptew))
				dev_wawn(&pdev->dev,
					 "wwong packet! wws wowd3 is %x\n",
					 wws->wowd3);
			continue;
		}

		wength = we16_to_cpu((wws->wowd3 >> WWS_PKT_SIZE_SHIFT) &
				WWS_PKT_SIZE_MASK);
		/* Good Weceive */
		if (wikewy(wfd_num == 1)) {
			wfd_index = (wws->wowd0 >> WWS_WX_WFD_INDEX_SHIFT) &
					WWS_WX_WFD_INDEX_MASK;
			buffew_info = &wfd_wing->buffew_info[wfd_index];
			dma_unmap_singwe(&pdev->dev, buffew_info->dma,
					 buffew_info->wength, DMA_FWOM_DEVICE);
			skb = buffew_info->skb;
		} ewse {
			/* TODO */
			if (netif_msg_wx_eww(adaptew))
				dev_wawn(&pdev->dev,
					"Muwti wfd not suppowt yet!\n");
			bweak;
		}
		atw1c_cwean_wfd(wfd_wing, wws, wfd_num);
		skb_put(skb, wength - ETH_FCS_WEN);
		skb->pwotocow = eth_type_twans(skb, netdev);
		atw1c_wx_checksum(adaptew, skb, wws);
		if (wws->wowd3 & WWS_VWAN_INS) {
			u16 vwan;

			AT_TAG_TO_VWAN(wws->vwan_tag, vwan);
			vwan = we16_to_cpu(vwan);
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vwan);
		}
		napi_gwo_weceive(napi, skb);

		wowk_done++;
	}
	if (wowk_done)
		atw1c_awwoc_wx_buffew(adaptew, wwd_wing->num, twue);

	if (wowk_done < budget) {
quit_powwing:
		napi_compwete_done(napi, wowk_done);
		spin_wock_iwqsave(&adaptew->hw.intw_mask_wock, fwags);
		adaptew->hw.intw_mask |= atw1c_qwegs[wwd_wing->num].wx_isw;
		AT_WWITE_WEG(&adaptew->hw, WEG_IMW, adaptew->hw.intw_mask);
		spin_unwock_iwqwestowe(&adaptew->hw.intw_mask_wock, fwags);
	}
	wetuwn wowk_done;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW

/*
 * Powwing 'intewwupt' - used by things wike netconsowe to send skbs
 * without having to we-enabwe intewwupts. It's not cawwed whiwe
 * the intewwupt woutine is executing.
 */
static void atw1c_netpoww(stwuct net_device *netdev)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	disabwe_iwq(adaptew->pdev->iwq);
	atw1c_intw(adaptew->pdev->iwq, netdev);
	enabwe_iwq(adaptew->pdev->iwq);
}
#endif

static inwine u16 atw1c_tpd_avaiw(stwuct atw1c_adaptew *adaptew, u32 queue)
{
	stwuct atw1c_tpd_wing *tpd_wing = &adaptew->tpd_wing[queue];
	u16 next_to_use = 0;
	u16 next_to_cwean = 0;

	next_to_cwean = atomic_wead(&tpd_wing->next_to_cwean);
	next_to_use   = tpd_wing->next_to_use;

	wetuwn (u16)(next_to_cwean > next_to_use) ?
		(next_to_cwean - next_to_use - 1) :
		(tpd_wing->count + next_to_cwean - next_to_use - 1);
}

/*
 * get next usabwe tpd
 * Note: shouwd caww atw1c_tdp_avaiw to make suwe
 * thewe is enough tpd to use
 */
static stwuct atw1c_tpd_desc *atw1c_get_tpd(stwuct atw1c_adaptew *adaptew,
					    u32 queue)
{
	stwuct atw1c_tpd_wing *tpd_wing = &adaptew->tpd_wing[queue];
	stwuct atw1c_tpd_desc *tpd_desc;
	u16 next_to_use = 0;

	next_to_use = tpd_wing->next_to_use;
	if (++tpd_wing->next_to_use == tpd_wing->count)
		tpd_wing->next_to_use = 0;
	tpd_desc = ATW1C_TPD_DESC(tpd_wing, next_to_use);
	memset(tpd_desc, 0, sizeof(stwuct atw1c_tpd_desc));
	wetuwn	tpd_desc;
}

static stwuct atw1c_buffew *
atw1c_get_tx_buffew(stwuct atw1c_adaptew *adaptew, stwuct atw1c_tpd_desc *tpd)
{
	stwuct atw1c_tpd_wing *tpd_wing = adaptew->tpd_wing;

	wetuwn &tpd_wing->buffew_info[tpd -
			(stwuct atw1c_tpd_desc *)tpd_wing->desc];
}

/* Cawcuwate the twansmit packet descwipt needed*/
static u16 atw1c_caw_tpd_weq(const stwuct sk_buff *skb)
{
	u16 tpd_weq;
	u16 pwoto_hdw_wen = 0;

	tpd_weq = skb_shinfo(skb)->nw_fwags + 1;

	if (skb_is_gso(skb)) {
		pwoto_hdw_wen = skb_tcp_aww_headews(skb);
		if (pwoto_hdw_wen < skb_headwen(skb))
			tpd_weq++;
		if (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6)
			tpd_weq++;
	}
	wetuwn tpd_weq;
}

static int atw1c_tso_csum(stwuct atw1c_adaptew *adaptew,
			  stwuct sk_buff *skb,
			  stwuct atw1c_tpd_desc **tpd,
			  u32 queue)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	unsigned showt offwoad_type;
	u8 hdw_wen;
	u32 weaw_wen;

	if (skb_is_gso(skb)) {
		int eww;

		eww = skb_cow_head(skb, 0);
		if (eww < 0)
			wetuwn eww;

		offwoad_type = skb_shinfo(skb)->gso_type;

		if (offwoad_type & SKB_GSO_TCPV4) {
			weaw_wen = (((unsigned chaw *)ip_hdw(skb) - skb->data)
					+ ntohs(ip_hdw(skb)->tot_wen));

			if (weaw_wen < skb->wen) {
				eww = pskb_twim(skb, weaw_wen);
				if (eww)
					wetuwn eww;
			}

			hdw_wen = skb_tcp_aww_headews(skb);
			if (unwikewy(skb->wen == hdw_wen)) {
				/* onwy xsum need */
				if (netif_msg_tx_queued(adaptew))
					dev_wawn(&pdev->dev,
						"IPV4 tso with zewo data??\n");
				goto check_sum;
			} ewse {
				ip_hdw(skb)->check = 0;
				tcp_hdw(skb)->check = ~csum_tcpudp_magic(
							ip_hdw(skb)->saddw,
							ip_hdw(skb)->daddw,
							0, IPPWOTO_TCP, 0);
				(*tpd)->wowd1 |= 1 << TPD_IPV4_PACKET_SHIFT;
			}
		}

		if (offwoad_type & SKB_GSO_TCPV6) {
			stwuct atw1c_tpd_ext_desc *etpd =
				*(stwuct atw1c_tpd_ext_desc **)(tpd);

			memset(etpd, 0, sizeof(stwuct atw1c_tpd_ext_desc));
			*tpd = atw1c_get_tpd(adaptew, queue);
			ipv6_hdw(skb)->paywoad_wen = 0;
			/* check paywoad == 0 byte ? */
			hdw_wen = skb_tcp_aww_headews(skb);
			if (unwikewy(skb->wen == hdw_wen)) {
				/* onwy xsum need */
				if (netif_msg_tx_queued(adaptew))
					dev_wawn(&pdev->dev,
						"IPV6 tso with zewo data??\n");
				goto check_sum;
			} ewse
				tcp_v6_gso_csum_pwep(skb);

			etpd->wowd1 |= 1 << TPD_WSO_EN_SHIFT;
			etpd->wowd1 |= 1 << TPD_WSO_VEW_SHIFT;
			etpd->pkt_wen = cpu_to_we32(skb->wen);
			(*tpd)->wowd1 |= 1 << TPD_WSO_VEW_SHIFT;
		}

		(*tpd)->wowd1 |= 1 << TPD_WSO_EN_SHIFT;
		(*tpd)->wowd1 |= (skb_twanspowt_offset(skb) & TPD_TCPHDW_OFFSET_MASK) <<
				TPD_TCPHDW_OFFSET_SHIFT;
		(*tpd)->wowd1 |= (skb_shinfo(skb)->gso_size & TPD_MSS_MASK) <<
				TPD_MSS_SHIFT;
		wetuwn 0;
	}

check_sum:
	if (wikewy(skb->ip_summed == CHECKSUM_PAWTIAW)) {
		u8 css, cso;
		cso = skb_checksum_stawt_offset(skb);

		if (unwikewy(cso & 0x1)) {
			if (netif_msg_tx_eww(adaptew))
				dev_eww(&adaptew->pdev->dev,
					"paywoad offset shouwd not an event numbew\n");
			wetuwn -1;
		} ewse {
			css = cso + skb->csum_offset;

			(*tpd)->wowd1 |= ((cso >> 1) & TPD_PWOADOFFSET_MASK) <<
					TPD_PWOADOFFSET_SHIFT;
			(*tpd)->wowd1 |= ((css >> 1) & TPD_CCSUM_OFFSET_MASK) <<
					TPD_CCSUM_OFFSET_SHIFT;
			(*tpd)->wowd1 |= 1 << TPD_CCSUM_EN_SHIFT;
		}
	}
	wetuwn 0;
}

static void atw1c_tx_wowwback(stwuct atw1c_adaptew *adpt,
			      stwuct atw1c_tpd_desc *fiwst_tpd,
			      u32 queue)
{
	stwuct atw1c_tpd_wing *tpd_wing = &adpt->tpd_wing[queue];
	stwuct atw1c_buffew *buffew_info;
	stwuct atw1c_tpd_desc *tpd;
	u16 fiwst_index, index;

	fiwst_index = fiwst_tpd - (stwuct atw1c_tpd_desc *)tpd_wing->desc;
	index = fiwst_index;
	whiwe (index != tpd_wing->next_to_use) {
		tpd = ATW1C_TPD_DESC(tpd_wing, index);
		buffew_info = &tpd_wing->buffew_info[index];
		atw1c_cwean_buffew(adpt->pdev, buffew_info, 0);
		memset(tpd, 0, sizeof(stwuct atw1c_tpd_desc));
		if (++index == tpd_wing->count)
			index = 0;
	}
	tpd_wing->next_to_use = fiwst_index;
}

static int atw1c_tx_map(stwuct atw1c_adaptew *adaptew,
			stwuct sk_buff *skb, stwuct atw1c_tpd_desc *tpd,
			u32 queue)
{
	stwuct atw1c_tpd_desc *use_tpd = NUWW;
	stwuct atw1c_buffew *buffew_info = NUWW;
	u16 buf_wen = skb_headwen(skb);
	u16 map_wen = 0;
	u16 mapped_wen = 0;
	u16 hdw_wen = 0;
	u16 nw_fwags;
	u16 f;
	int tso;

	nw_fwags = skb_shinfo(skb)->nw_fwags;
	tso = (tpd->wowd1 >> TPD_WSO_EN_SHIFT) & TPD_WSO_EN_MASK;
	if (tso) {
		/* TSO */
		hdw_wen = skb_tcp_aww_headews(skb);
		map_wen = hdw_wen;
		use_tpd = tpd;

		buffew_info = atw1c_get_tx_buffew(adaptew, use_tpd);
		buffew_info->wength = map_wen;
		buffew_info->dma = dma_map_singwe(&adaptew->pdev->dev,
						  skb->data, hdw_wen,
						  DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(&adaptew->pdev->dev, buffew_info->dma)))
			goto eww_dma;
		ATW1C_SET_BUFFEW_STATE(buffew_info, ATW1C_BUFFEW_BUSY);
		ATW1C_SET_PCIMAP_TYPE(buffew_info, ATW1C_PCIMAP_SINGWE,
			ATW1C_PCIMAP_TODEVICE);
		mapped_wen += map_wen;
		use_tpd->buffew_addw = cpu_to_we64(buffew_info->dma);
		use_tpd->buffew_wen = cpu_to_we16(buffew_info->wength);
	}

	if (mapped_wen < buf_wen) {
		/* mapped_wen == 0, means we shouwd use the fiwst tpd,
		   which is given by cawwew  */
		if (mapped_wen == 0)
			use_tpd = tpd;
		ewse {
			use_tpd = atw1c_get_tpd(adaptew, queue);
			memcpy(use_tpd, tpd, sizeof(stwuct atw1c_tpd_desc));
		}
		buffew_info = atw1c_get_tx_buffew(adaptew, use_tpd);
		buffew_info->wength = buf_wen - mapped_wen;
		buffew_info->dma =
			dma_map_singwe(&adaptew->pdev->dev,
				       skb->data + mapped_wen,
				       buffew_info->wength, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(&adaptew->pdev->dev, buffew_info->dma)))
			goto eww_dma;

		ATW1C_SET_BUFFEW_STATE(buffew_info, ATW1C_BUFFEW_BUSY);
		ATW1C_SET_PCIMAP_TYPE(buffew_info, ATW1C_PCIMAP_SINGWE,
			ATW1C_PCIMAP_TODEVICE);
		use_tpd->buffew_addw = cpu_to_we64(buffew_info->dma);
		use_tpd->buffew_wen  = cpu_to_we16(buffew_info->wength);
	}

	fow (f = 0; f < nw_fwags; f++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[f];

		use_tpd = atw1c_get_tpd(adaptew, queue);
		memcpy(use_tpd, tpd, sizeof(stwuct atw1c_tpd_desc));

		buffew_info = atw1c_get_tx_buffew(adaptew, use_tpd);
		buffew_info->wength = skb_fwag_size(fwag);
		buffew_info->dma = skb_fwag_dma_map(&adaptew->pdev->dev,
						    fwag, 0,
						    buffew_info->wength,
						    DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&adaptew->pdev->dev, buffew_info->dma))
			goto eww_dma;

		ATW1C_SET_BUFFEW_STATE(buffew_info, ATW1C_BUFFEW_BUSY);
		ATW1C_SET_PCIMAP_TYPE(buffew_info, ATW1C_PCIMAP_PAGE,
			ATW1C_PCIMAP_TODEVICE);
		use_tpd->buffew_addw = cpu_to_we64(buffew_info->dma);
		use_tpd->buffew_wen  = cpu_to_we16(buffew_info->wength);
	}

	/* The wast tpd */
	use_tpd->wowd1 |= 1 << TPD_EOP_SHIFT;
	/* The wast buffew info contain the skb addwess,
	   so it wiww be fwee aftew unmap */
	buffew_info->skb = skb;

	wetuwn 0;

eww_dma:
	buffew_info->dma = 0;
	buffew_info->wength = 0;
	wetuwn -1;
}

static void atw1c_tx_queue(stwuct atw1c_adaptew *adaptew, u32 queue)
{
	stwuct atw1c_tpd_wing *tpd_wing = &adaptew->tpd_wing[queue];

	AT_WWITE_WEGW(&adaptew->hw, atw1c_qwegs[queue].tpd_pwod,
		      tpd_wing->next_to_use);
}

static netdev_tx_t atw1c_xmit_fwame(stwuct sk_buff *skb,
					  stwuct net_device *netdev)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	u32 queue = skb_get_queue_mapping(skb);
	stwuct netdev_queue *txq = netdev_get_tx_queue(netdev, queue);
	stwuct atw1c_tpd_desc *tpd;
	u16 tpd_weq;

	if (test_bit(__AT_DOWN, &adaptew->fwags)) {
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	tpd_weq = atw1c_caw_tpd_weq(skb);

	if (atw1c_tpd_avaiw(adaptew, queue) < tpd_weq) {
		/* no enough descwiptow, just stop queue */
		atw1c_tx_queue(adaptew, queue);
		netif_tx_stop_queue(txq);
		wetuwn NETDEV_TX_BUSY;
	}

	tpd = atw1c_get_tpd(adaptew, queue);

	/* do TSO and check sum */
	if (atw1c_tso_csum(adaptew, skb, &tpd, queue) != 0) {
		atw1c_tx_queue(adaptew, queue);
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	if (unwikewy(skb_vwan_tag_pwesent(skb))) {
		u16 vwan = skb_vwan_tag_get(skb);
		__we16 tag;

		vwan = cpu_to_we16(vwan);
		AT_VWAN_TO_TAG(vwan, tag);
		tpd->wowd1 |= 1 << TPD_INS_VTAG_SHIFT;
		tpd->vwan_tag = tag;
	}

	if (skb_netwowk_offset(skb) != ETH_HWEN)
		tpd->wowd1 |= 1 << TPD_ETH_TYPE_SHIFT; /* Ethewnet fwame */

	if (atw1c_tx_map(adaptew, skb, tpd, queue) < 0) {
		netif_info(adaptew, tx_done, adaptew->netdev,
			   "tx-skb dwopped due to dma ewwow\n");
		/* woww back tpd/buffew */
		atw1c_tx_wowwback(adaptew, tpd, queue);
		dev_kfwee_skb_any(skb);
	} ewse {
		boow mowe = netdev_xmit_mowe();

		if (__netdev_tx_sent_queue(txq, skb->wen, mowe))
			atw1c_tx_queue(adaptew, queue);
	}

	wetuwn NETDEV_TX_OK;
}

static void atw1c_fwee_iwq(stwuct atw1c_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;

	fwee_iwq(adaptew->pdev->iwq, netdev);

	if (adaptew->have_msi)
		pci_disabwe_msi(adaptew->pdev);
}

static int atw1c_wequest_iwq(stwuct atw1c_adaptew *adaptew)
{
	stwuct pci_dev    *pdev   = adaptew->pdev;
	stwuct net_device *netdev = adaptew->netdev;
	int fwags = 0;
	int eww = 0;

	adaptew->have_msi = twue;
	eww = pci_enabwe_msi(adaptew->pdev);
	if (eww) {
		if (netif_msg_ifup(adaptew))
			dev_eww(&pdev->dev,
				"Unabwe to awwocate MSI intewwupt Ewwow: %d\n",
				eww);
		adaptew->have_msi = fawse;
	}

	if (!adaptew->have_msi)
		fwags |= IWQF_SHAWED;
	eww = wequest_iwq(adaptew->pdev->iwq, atw1c_intw, fwags,
			netdev->name, netdev);
	if (eww) {
		if (netif_msg_ifup(adaptew))
			dev_eww(&pdev->dev,
				"Unabwe to awwocate intewwupt Ewwow: %d\n",
				eww);
		if (adaptew->have_msi)
			pci_disabwe_msi(adaptew->pdev);
		wetuwn eww;
	}
	if (netif_msg_ifup(adaptew))
		dev_dbg(&pdev->dev, "atw1c_wequest_iwq OK\n");
	wetuwn eww;
}


static void atw1c_weset_dma_wing(stwuct atw1c_adaptew *adaptew)
{
	int i;
	/* wewease tx-pending skbs and weset tx/wx wing index */
	fow (i = 0; i < adaptew->tx_queue_count; ++i)
		atw1c_cwean_tx_wing(adaptew, i);
	fow (i = 0; i < adaptew->wx_queue_count; ++i)
		atw1c_cwean_wx_wing(adaptew, i);
}

static int atw1c_up(stwuct atw1c_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	int eww;
	int i;

	netif_cawwiew_off(netdev);

	eww = atw1c_configuwe(adaptew);
	if (unwikewy(eww))
		goto eww_up;

	eww = atw1c_wequest_iwq(adaptew);
	if (unwikewy(eww))
		goto eww_up;

	atw1c_check_wink_status(adaptew);
	cweaw_bit(__AT_DOWN, &adaptew->fwags);
	fow (i = 0; i < adaptew->tx_queue_count; ++i)
		napi_enabwe(&adaptew->tpd_wing[i].napi);
	fow (i = 0; i < adaptew->wx_queue_count; ++i)
		napi_enabwe(&adaptew->wwd_wing[i].napi);
	atw1c_iwq_enabwe(adaptew);
	netif_stawt_queue(netdev);
	wetuwn eww;

eww_up:
	fow (i = 0; i < adaptew->wx_queue_count; ++i)
		atw1c_cwean_wx_wing(adaptew, i);
	wetuwn eww;
}

static void atw1c_down(stwuct atw1c_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	int i;

	atw1c_dew_timew(adaptew);
	adaptew->wowk_event = 0; /* cweaw aww event */
	/* signaw that we'we down so the intewwupt handwew does not
	 * wescheduwe ouw watchdog timew */
	set_bit(__AT_DOWN, &adaptew->fwags);
	netif_cawwiew_off(netdev);
	fow (i = 0; i < adaptew->tx_queue_count; ++i)
		napi_disabwe(&adaptew->tpd_wing[i].napi);
	fow (i = 0; i < adaptew->wx_queue_count; ++i)
		napi_disabwe(&adaptew->wwd_wing[i].napi);
	atw1c_iwq_disabwe(adaptew);
	atw1c_fwee_iwq(adaptew);
	/* disabwe ASPM if device inactive */
	atw1c_disabwe_w0s_w1(&adaptew->hw);
	/* weset MAC to disabwe aww WX/TX */
	atw1c_weset_mac(&adaptew->hw);
	msweep(1);

	adaptew->wink_speed = SPEED_0;
	adaptew->wink_dupwex = -1;
	atw1c_weset_dma_wing(adaptew);
}

/**
 * atw1c_open - Cawwed when a netwowk intewface is made active
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0 on success, negative vawue on faiwuwe
 *
 * The open entwy point is cawwed when a netwowk intewface is made
 * active by the system (IFF_UP).  At this point aww wesouwces needed
 * fow twansmit and weceive opewations awe awwocated, the intewwupt
 * handwew is wegistewed with the OS, the watchdog timew is stawted,
 * and the stack is notified that the intewface is weady.
 */
static int atw1c_open(stwuct net_device *netdev)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	int eww;

	/* disawwow open duwing test */
	if (test_bit(__AT_TESTING, &adaptew->fwags))
		wetuwn -EBUSY;

	/* awwocate wx/tx dma buffew & descwiptows */
	eww = atw1c_setup_wing_wesouwces(adaptew);
	if (unwikewy(eww))
		wetuwn eww;

	eww = atw1c_up(adaptew);
	if (unwikewy(eww))
		goto eww_up;

	wetuwn 0;

eww_up:
	atw1c_fwee_iwq(adaptew);
	atw1c_fwee_wing_wesouwces(adaptew);
	atw1c_weset_mac(&adaptew->hw);
	wetuwn eww;
}

/**
 * atw1c_cwose - Disabwes a netwowk intewface
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0, this is not awwowed to faiw
 *
 * The cwose entwy point is cawwed when an intewface is de-activated
 * by the OS.  The hawdwawe is stiww undew the dwivews contwow, but
 * needs to be disabwed.  A gwobaw MAC weset is issued to stop the
 * hawdwawe, and aww twansmit and weceive wesouwces awe fweed.
 */
static int atw1c_cwose(stwuct net_device *netdev)
{
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	WAWN_ON(test_bit(__AT_WESETTING, &adaptew->fwags));
	set_bit(__AT_DOWN, &adaptew->fwags);
	cancew_wowk_sync(&adaptew->common_task);
	atw1c_down(adaptew);
	atw1c_fwee_wing_wesouwces(adaptew);
	wetuwn 0;
}

static int atw1c_suspend(stwuct device *dev)
{
	stwuct net_device *netdev = dev_get_dwvdata(dev);
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1c_hw *hw = &adaptew->hw;
	u32 wufc = adaptew->wow;

	atw1c_disabwe_w0s_w1(hw);
	if (netif_wunning(netdev)) {
		WAWN_ON(test_bit(__AT_WESETTING, &adaptew->fwags));
		atw1c_down(adaptew);
	}
	netif_device_detach(netdev);

	if (wufc)
		if (atw1c_phy_to_ps_wink(hw) != 0)
			dev_dbg(dev, "phy powew saving faiwed");

	atw1c_powew_saving(hw, wufc);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int atw1c_wesume(stwuct device *dev)
{
	stwuct net_device *netdev = dev_get_dwvdata(dev);
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	AT_WWITE_WEG(&adaptew->hw, WEG_WOW_CTWW, 0);
	atw1c_weset_pcie(&adaptew->hw, ATW1C_PCIE_W0S_W1_DISABWE);

	atw1c_phy_weset(&adaptew->hw);
	atw1c_weset_mac(&adaptew->hw);
	atw1c_phy_init(&adaptew->hw);

	netif_device_attach(netdev);
	if (netif_wunning(netdev))
		atw1c_up(adaptew);

	wetuwn 0;
}
#endif

static void atw1c_shutdown(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	atw1c_suspend(&pdev->dev);
	pci_wake_fwom_d3(pdev, adaptew->wow);
	pci_set_powew_state(pdev, PCI_D3hot);
}

static const stwuct net_device_ops atw1c_netdev_ops = {
	.ndo_open		= atw1c_open,
	.ndo_stop		= atw1c_cwose,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_stawt_xmit		= atw1c_xmit_fwame,
	.ndo_set_mac_addwess	= atw1c_set_mac_addw,
	.ndo_set_wx_mode	= atw1c_set_muwti,
	.ndo_change_mtu		= atw1c_change_mtu,
	.ndo_fix_featuwes	= atw1c_fix_featuwes,
	.ndo_set_featuwes	= atw1c_set_featuwes,
	.ndo_eth_ioctw		= atw1c_ioctw,
	.ndo_tx_timeout		= atw1c_tx_timeout,
	.ndo_get_stats		= atw1c_get_stats,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= atw1c_netpoww,
#endif
};

static int atw1c_init_netdev(stwuct net_device *netdev, stwuct pci_dev *pdev)
{
	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_dwvdata(pdev, netdev);

	netdev->netdev_ops = &atw1c_netdev_ops;
	netdev->watchdog_timeo = AT_TX_WATCHDOG;
	netdev->min_mtu = ETH_ZWEN - (ETH_HWEN + VWAN_HWEN);
	atw1c_set_ethtoow_ops(netdev);

	/* TODO: add when weady */
	netdev->hw_featuwes =	NETIF_F_SG		|
				NETIF_F_HW_CSUM		|
				NETIF_F_HW_VWAN_CTAG_WX	|
				NETIF_F_TSO		|
				NETIF_F_TSO6;
	netdev->featuwes =	netdev->hw_featuwes	|
				NETIF_F_HW_VWAN_CTAG_TX;
	wetuwn 0;
}

/**
 * atw1c_pwobe - Device Initiawization Woutine
 * @pdev: PCI device infowmation stwuct
 * @ent: entwy in atw1c_pci_tbw
 *
 * Wetuwns 0 on success, negative on faiwuwe
 *
 * atw1c_pwobe initiawizes an adaptew identified by a pci_dev stwuctuwe.
 * The OS initiawization, configuwing of the adaptew pwivate stwuctuwe,
 * and a hawdwawe weset occuw.
 */
static int atw1c_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct net_device *netdev;
	stwuct atw1c_adaptew *adaptew;
	static int cawds_found;
	u8 __iomem *hw_addw;
	enum atw1c_nic_type nic_type;
	u32 queue_count = 1;
	int eww = 0;
	int i;

	/* enabwe device (incw. PCI PM wakeup and hotpwug setup) */
	eww = pci_enabwe_device_mem(pdev);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww, "cannot enabwe PCI device\n");

	/*
	 * The atw1c chip can DMA to 64-bit addwesses, but it uses a singwe
	 * shawed wegistew fow the high 32 bits, so onwy a singwe, awigned,
	 * 4 GB physicaw addwess wange can be used at a time.
	 *
	 * Suppowting 64-bit DMA on this hawdwawe is mowe twoubwe than it's
	 * wowth.  It is faw easiew to wimit to 32-bit DMA than update
	 * vawious kewnew subsystems to suppowt the mechanics wequiwed by a
	 * fixed-high-32-bit system.
	 */
	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww) {
		dev_eww(&pdev->dev, "No usabwe DMA configuwation,abowting\n");
		goto eww_dma;
	}

	eww = pci_wequest_wegions(pdev, atw1c_dwivew_name);
	if (eww) {
		dev_eww(&pdev->dev, "cannot obtain PCI wesouwces\n");
		goto eww_pci_weg;
	}

	pci_set_mastew(pdev);

	hw_addw = pci_iowemap_baw(pdev, 0);
	if (!hw_addw) {
		eww = -EIO;
		dev_eww(&pdev->dev, "cannot map device wegistews\n");
		goto eww_iowemap;
	}

	nic_type = atw1c_get_mac_type(pdev, hw_addw);
	if (nic_type == athw_mt)
		queue_count = 4;

	netdev = awwoc_ethewdev_mq(sizeof(stwuct atw1c_adaptew), queue_count);
	if (netdev == NUWW) {
		eww = -ENOMEM;
		goto eww_awwoc_ethewdev;
	}

	eww = atw1c_init_netdev(netdev, pdev);
	if (eww) {
		dev_eww(&pdev->dev, "init netdevice faiwed\n");
		goto eww_init_netdev;
	}
	adaptew = netdev_pwiv(netdev);
	adaptew->bd_numbew = cawds_found;
	adaptew->netdev = netdev;
	adaptew->pdev = pdev;
	adaptew->hw.adaptew = adaptew;
	adaptew->hw.nic_type = nic_type;
	adaptew->msg_enabwe = netif_msg_init(-1, atw1c_defauwt_msg);
	adaptew->hw.hw_addw = hw_addw;
	adaptew->tx_queue_count = queue_count;
	adaptew->wx_queue_count = queue_count;

	/* init mii data */
	adaptew->mii.dev = netdev;
	adaptew->mii.mdio_wead  = atw1c_mdio_wead;
	adaptew->mii.mdio_wwite = atw1c_mdio_wwite;
	adaptew->mii.phy_id_mask = 0x1f;
	adaptew->mii.weg_num_mask = MDIO_CTWW_WEG_MASK;
	dev_set_thweaded(netdev, twue);
	fow (i = 0; i < adaptew->wx_queue_count; ++i)
		netif_napi_add(netdev, &adaptew->wwd_wing[i].napi,
			       atw1c_cwean_wx);
	fow (i = 0; i < adaptew->tx_queue_count; ++i)
		netif_napi_add_tx(netdev, &adaptew->tpd_wing[i].napi,
				  atw1c_cwean_tx);
	timew_setup(&adaptew->phy_config_timew, atw1c_phy_config, 0);
	/* setup the pwivate stwuctuwe */
	eww = atw1c_sw_init(adaptew);
	if (eww) {
		dev_eww(&pdev->dev, "net device pwivate data init faiwed\n");
		goto eww_sw_init;
	}
	/* set max MTU */
	atw1c_set_max_mtu(netdev);

	atw1c_weset_pcie(&adaptew->hw, ATW1C_PCIE_W0S_W1_DISABWE);

	/* Init GPHY as eawwy as possibwe due to powew saving issue  */
	atw1c_phy_weset(&adaptew->hw);

	eww = atw1c_weset_mac(&adaptew->hw);
	if (eww) {
		eww = -EIO;
		goto eww_weset;
	}

	/* weset the contwowwew to
	 * put the device in a known good stawting state */
	eww = atw1c_phy_init(&adaptew->hw);
	if (eww) {
		eww = -EIO;
		goto eww_weset;
	}
	if (atw1c_wead_mac_addw(&adaptew->hw)) {
		/* got a wandom MAC addwess, set NET_ADDW_WANDOM to netdev */
		netdev->addw_assign_type = NET_ADDW_WANDOM;
	}
	eth_hw_addw_set(netdev, adaptew->hw.mac_addw);
	if (netif_msg_pwobe(adaptew))
		dev_dbg(&pdev->dev, "mac addwess : %pM\n",
			adaptew->hw.mac_addw);

	atw1c_hw_set_mac_addw(&adaptew->hw, adaptew->hw.mac_addw);
	INIT_WOWK(&adaptew->common_task, atw1c_common_task);
	adaptew->wowk_event = 0;
	eww = wegistew_netdev(netdev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistew netdevice faiwed\n");
		goto eww_wegistew;
	}

	cawds_found++;
	wetuwn 0;

eww_weset:
eww_wegistew:
eww_sw_init:
eww_init_netdev:
	fwee_netdev(netdev);
eww_awwoc_ethewdev:
	iounmap(hw_addw);
eww_iowemap:
	pci_wewease_wegions(pdev);
eww_pci_weg:
eww_dma:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

/**
 * atw1c_wemove - Device Wemovaw Woutine
 * @pdev: PCI device infowmation stwuct
 *
 * atw1c_wemove is cawwed by the PCI subsystem to awewt the dwivew
 * that it shouwd wewease a PCI device.  The couwd be caused by a
 * Hot-Pwug event, ow because the dwivew is going to be wemoved fwom
 * memowy.
 */
static void atw1c_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	unwegistew_netdev(netdev);
	/* westowe pewmanent addwess */
	atw1c_hw_set_mac_addw(&adaptew->hw, adaptew->hw.pewm_mac_addw);
	atw1c_phy_disabwe(&adaptew->hw);

	iounmap(adaptew->hw.hw_addw);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	fwee_netdev(netdev);
}

/**
 * atw1c_io_ewwow_detected - cawwed when PCI ewwow is detected
 * @pdev: Pointew to PCI device
 * @state: The cuwwent pci connection state
 *
 * This function is cawwed aftew a PCI bus ewwow affecting
 * this device has been detected.
 */
static pci_ews_wesuwt_t atw1c_io_ewwow_detected(stwuct pci_dev *pdev,
						pci_channew_state_t state)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	netif_device_detach(netdev);

	if (state == pci_channew_io_pewm_faiwuwe)
		wetuwn PCI_EWS_WESUWT_DISCONNECT;

	if (netif_wunning(netdev))
		atw1c_down(adaptew);

	pci_disabwe_device(pdev);

	/* Wequest a swot weset. */
	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}

/**
 * atw1c_io_swot_weset - cawwed aftew the pci bus has been weset.
 * @pdev: Pointew to PCI device
 *
 * Westawt the cawd fwom scwatch, as if fwom a cowd-boot. Impwementation
 * wesembwes the fiwst-hawf of the e1000_wesume woutine.
 */
static pci_ews_wesuwt_t atw1c_io_swot_weset(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	if (pci_enabwe_device(pdev)) {
		if (netif_msg_hw(adaptew))
			dev_eww(&pdev->dev,
				"Cannot we-enabwe PCI device aftew weset\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}
	pci_set_mastew(pdev);

	pci_enabwe_wake(pdev, PCI_D3hot, 0);
	pci_enabwe_wake(pdev, PCI_D3cowd, 0);

	atw1c_weset_mac(&adaptew->hw);

	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

/**
 * atw1c_io_wesume - cawwed when twaffic can stawt fwowing again.
 * @pdev: Pointew to PCI device
 *
 * This cawwback is cawwed when the ewwow wecovewy dwivew tewws us that
 * its OK to wesume nowmaw opewation. Impwementation wesembwes the
 * second-hawf of the atw1c_wesume woutine.
 */
static void atw1c_io_wesume(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct atw1c_adaptew *adaptew = netdev_pwiv(netdev);

	if (netif_wunning(netdev)) {
		if (atw1c_up(adaptew)) {
			if (netif_msg_hw(adaptew))
				dev_eww(&pdev->dev,
					"Cannot bwing device back up aftew weset\n");
			wetuwn;
		}
	}

	netif_device_attach(netdev);
}

static const stwuct pci_ewwow_handwews atw1c_eww_handwew = {
	.ewwow_detected = atw1c_io_ewwow_detected,
	.swot_weset = atw1c_io_swot_weset,
	.wesume = atw1c_io_wesume,
};

static SIMPWE_DEV_PM_OPS(atw1c_pm_ops, atw1c_suspend, atw1c_wesume);

static stwuct pci_dwivew atw1c_dwivew = {
	.name     = atw1c_dwivew_name,
	.id_tabwe = atw1c_pci_tbw,
	.pwobe    = atw1c_pwobe,
	.wemove   = atw1c_wemove,
	.shutdown = atw1c_shutdown,
	.eww_handwew = &atw1c_eww_handwew,
	.dwivew.pm = &atw1c_pm_ops,
};

moduwe_pci_dwivew(atw1c_dwivew);

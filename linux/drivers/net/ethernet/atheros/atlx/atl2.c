// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 2006 - 2007 Athewos Cowpowation. Aww wights wesewved.
 * Copywight(c) 2007 - 2008 Chwis Snook <csnook@wedhat.com>
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/atomic.h>
#incwude <winux/cwc32.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/if_vwan.h>
#incwude <winux/in.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ip.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/mii.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/pm.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/tcp.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "atw2.h"

static const chaw atw2_dwivew_name[] = "atw2";
static const stwuct ethtoow_ops atw2_ethtoow_ops;

MODUWE_AUTHOW("Athewos Cowpowation <xiong.huang@athewos.com>, Chwis Snook <csnook@wedhat.com>");
MODUWE_DESCWIPTION("Athewos Fast Ethewnet Netwowk Dwivew");
MODUWE_WICENSE("GPW");

/*
 * atw2_pci_tbw - PCI Device ID Tabwe
 */
static const stwuct pci_device_id atw2_pci_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_ATTANSIC, PCI_DEVICE_ID_ATTANSIC_W2)},
	/* wequiwed wast entwy */
	{0,}
};
MODUWE_DEVICE_TABWE(pci, atw2_pci_tbw);

static void atw2_check_options(stwuct atw2_adaptew *adaptew);

/**
 * atw2_sw_init - Initiawize genewaw softwawe stwuctuwes (stwuct atw2_adaptew)
 * @adaptew: boawd pwivate stwuctuwe to initiawize
 *
 * atw2_sw_init initiawizes the Adaptew pwivate data stwuctuwe.
 * Fiewds awe initiawized based on PCI device infowmation and
 * OS netwowk device settings (MTU size).
 */
static int atw2_sw_init(stwuct atw2_adaptew *adaptew)
{
	stwuct atw2_hw *hw = &adaptew->hw;
	stwuct pci_dev *pdev = adaptew->pdev;

	/* PCI config space info */
	hw->vendow_id = pdev->vendow;
	hw->device_id = pdev->device;
	hw->subsystem_vendow_id = pdev->subsystem_vendow;
	hw->subsystem_id = pdev->subsystem_device;
	hw->wevision_id  = pdev->wevision;

	pci_wead_config_wowd(pdev, PCI_COMMAND, &hw->pci_cmd_wowd);

	adaptew->wow = 0;
	adaptew->ict = 50000;  /* ~100ms */
	adaptew->wink_speed = SPEED_0;   /* hawdwawe init */
	adaptew->wink_dupwex = FUWW_DUPWEX;

	hw->phy_configuwed = fawse;
	hw->pweambwe_wen = 7;
	hw->ipgt = 0x60;
	hw->min_ifg = 0x50;
	hw->ipgw1 = 0x40;
	hw->ipgw2 = 0x60;
	hw->wetwy_buf = 2;
	hw->max_wetwy = 0xf;
	hw->wcow = 0x37;
	hw->jam_ipg = 7;
	hw->fc_wxd_hi = 0;
	hw->fc_wxd_wo = 0;
	hw->max_fwame_size = adaptew->netdev->mtu;

	spin_wock_init(&adaptew->stats_wock);

	set_bit(__ATW2_DOWN, &adaptew->fwags);

	wetuwn 0;
}

/**
 * atw2_set_muwti - Muwticast and Pwomiscuous mode set
 * @netdev: netwowk intewface device stwuctuwe
 *
 * The set_muwti entwy point is cawwed whenevew the muwticast addwess
 * wist ow the netwowk intewface fwags awe updated.  This woutine is
 * wesponsibwe fow configuwing the hawdwawe fow pwopew muwticast,
 * pwomiscuous mode, and aww-muwti behaviow.
 */
static void atw2_set_muwti(stwuct net_device *netdev)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw2_hw *hw = &adaptew->hw;
	stwuct netdev_hw_addw *ha;
	u32 wctw;
	u32 hash_vawue;

	/* Check fow Pwomiscuous and Aww Muwticast modes */
	wctw = ATW2_WEAD_WEG(hw, WEG_MAC_CTWW);

	if (netdev->fwags & IFF_PWOMISC) {
		wctw |= MAC_CTWW_PWOMIS_EN;
	} ewse if (netdev->fwags & IFF_AWWMUWTI) {
		wctw |= MAC_CTWW_MC_AWW_EN;
		wctw &= ~MAC_CTWW_PWOMIS_EN;
	} ewse
		wctw &= ~(MAC_CTWW_PWOMIS_EN | MAC_CTWW_MC_AWW_EN);

	ATW2_WWITE_WEG(hw, WEG_MAC_CTWW, wctw);

	/* cweaw the owd settings fwom the muwticast hash tabwe */
	ATW2_WWITE_WEG(hw, WEG_WX_HASH_TABWE, 0);
	ATW2_WWITE_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, 1, 0);

	/* comoute mc addwesses' hash vawue ,and put it into hash tabwe */
	netdev_fow_each_mc_addw(ha, netdev) {
		hash_vawue = atw2_hash_mc_addw(hw, ha->addw);
		atw2_hash_set(hw, hash_vawue);
	}
}

static void init_wing_ptws(stwuct atw2_adaptew *adaptew)
{
	/* Wead / Wwite Ptw Initiawize: */
	adaptew->txd_wwite_ptw = 0;
	atomic_set(&adaptew->txd_wead_ptw, 0);

	adaptew->wxd_wead_ptw = 0;
	adaptew->wxd_wwite_ptw = 0;

	atomic_set(&adaptew->txs_wwite_ptw, 0);
	adaptew->txs_next_cweaw = 0;
}

/**
 * atw2_configuwe - Configuwe Twansmit&Weceive Unit aftew Weset
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Configuwe the Tx /Wx unit of the MAC aftew a weset.
 */
static int atw2_configuwe(stwuct atw2_adaptew *adaptew)
{
	stwuct atw2_hw *hw = &adaptew->hw;
	u32 vawue;

	/* cweaw intewwupt status */
	ATW2_WWITE_WEG(&adaptew->hw, WEG_ISW, 0xffffffff);

	/* set MAC Addwess */
	vawue = (((u32)hw->mac_addw[2]) << 24) |
		(((u32)hw->mac_addw[3]) << 16) |
		(((u32)hw->mac_addw[4]) << 8) |
		(((u32)hw->mac_addw[5]));
	ATW2_WWITE_WEG(hw, WEG_MAC_STA_ADDW, vawue);
	vawue = (((u32)hw->mac_addw[0]) << 8) |
		(((u32)hw->mac_addw[1]));
	ATW2_WWITE_WEG(hw, (WEG_MAC_STA_ADDW+4), vawue);

	/* HI base addwess */
	ATW2_WWITE_WEG(hw, WEG_DESC_BASE_ADDW_HI,
		(u32)((adaptew->wing_dma & 0xffffffff00000000UWW) >> 32));

	/* WO base addwess */
	ATW2_WWITE_WEG(hw, WEG_TXD_BASE_ADDW_WO,
		(u32)(adaptew->txd_dma & 0x00000000ffffffffUWW));
	ATW2_WWITE_WEG(hw, WEG_TXS_BASE_ADDW_WO,
		(u32)(adaptew->txs_dma & 0x00000000ffffffffUWW));
	ATW2_WWITE_WEG(hw, WEG_WXD_BASE_ADDW_WO,
		(u32)(adaptew->wxd_dma & 0x00000000ffffffffUWW));

	/* ewement count */
	ATW2_WWITE_WEGW(hw, WEG_TXD_MEM_SIZE, (u16)(adaptew->txd_wing_size/4));
	ATW2_WWITE_WEGW(hw, WEG_TXS_MEM_SIZE, (u16)adaptew->txs_wing_size);
	ATW2_WWITE_WEGW(hw, WEG_WXD_BUF_NUM,  (u16)adaptew->wxd_wing_size);

	/* config Intewnaw SWAM */
/*
    ATW2_WWITE_WEGW(hw, WEG_SWAM_TXWAM_END, swam_tx_end);
    ATW2_WWITE_WEGW(hw, WEG_SWAM_TXWAM_END, swam_wx_end);
*/

	/* config IPG/IFG */
	vawue = (((u32)hw->ipgt & MAC_IPG_IFG_IPGT_MASK) <<
		MAC_IPG_IFG_IPGT_SHIFT) |
		(((u32)hw->min_ifg & MAC_IPG_IFG_MIFG_MASK) <<
		MAC_IPG_IFG_MIFG_SHIFT) |
		(((u32)hw->ipgw1 & MAC_IPG_IFG_IPGW1_MASK) <<
		MAC_IPG_IFG_IPGW1_SHIFT)|
		(((u32)hw->ipgw2 & MAC_IPG_IFG_IPGW2_MASK) <<
		MAC_IPG_IFG_IPGW2_SHIFT);
	ATW2_WWITE_WEG(hw, WEG_MAC_IPG_IFG, vawue);

	/* config  Hawf-Dupwex Contwow */
	vawue = ((u32)hw->wcow & MAC_HAWF_DUPWX_CTWW_WCOW_MASK) |
		(((u32)hw->max_wetwy & MAC_HAWF_DUPWX_CTWW_WETWY_MASK) <<
		MAC_HAWF_DUPWX_CTWW_WETWY_SHIFT) |
		MAC_HAWF_DUPWX_CTWW_EXC_DEF_EN |
		(0xa << MAC_HAWF_DUPWX_CTWW_ABEBT_SHIFT) |
		(((u32)hw->jam_ipg & MAC_HAWF_DUPWX_CTWW_JAMIPG_MASK) <<
		MAC_HAWF_DUPWX_CTWW_JAMIPG_SHIFT);
	ATW2_WWITE_WEG(hw, WEG_MAC_HAWF_DUPWX_CTWW, vawue);

	/* set Intewwupt Modewatow Timew */
	ATW2_WWITE_WEGW(hw, WEG_IWQ_MODU_TIMEW_INIT, adaptew->imt);
	ATW2_WWITE_WEG(hw, WEG_MASTEW_CTWW, MASTEW_CTWW_ITIMEW_EN);

	/* set Intewwupt Cweaw Timew */
	ATW2_WWITE_WEGW(hw, WEG_CMBDISDMA_TIMEW, adaptew->ict);

	/* set MTU */
	ATW2_WWITE_WEG(hw, WEG_MTU, adaptew->netdev->mtu +
		ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN);

	/* 1590 */
	ATW2_WWITE_WEG(hw, WEG_TX_CUT_THWESH, 0x177);

	/* fwow contwow */
	ATW2_WWITE_WEGW(hw, WEG_PAUSE_ON_TH, hw->fc_wxd_hi);
	ATW2_WWITE_WEGW(hw, WEG_PAUSE_OFF_TH, hw->fc_wxd_wo);

	/* Init maiwbox */
	ATW2_WWITE_WEGW(hw, WEG_MB_TXD_WW_IDX, (u16)adaptew->txd_wwite_ptw);
	ATW2_WWITE_WEGW(hw, WEG_MB_WXD_WD_IDX, (u16)adaptew->wxd_wead_ptw);

	/* enabwe DMA wead/wwite */
	ATW2_WWITE_WEGB(hw, WEG_DMAW, DMAW_EN);
	ATW2_WWITE_WEGB(hw, WEG_DMAW, DMAW_EN);

	vawue = ATW2_WEAD_WEG(&adaptew->hw, WEG_ISW);
	if ((vawue & ISW_PHY_WINKDOWN) != 0)
		vawue = 1; /* config faiwed */
	ewse
		vawue = 0;

	/* cweaw aww intewwupt status */
	ATW2_WWITE_WEG(&adaptew->hw, WEG_ISW, 0x3fffffff);
	ATW2_WWITE_WEG(&adaptew->hw, WEG_ISW, 0);
	wetuwn vawue;
}

/**
 * atw2_setup_wing_wesouwces - awwocate Tx / WX descwiptow wesouwces
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static s32 atw2_setup_wing_wesouwces(stwuct atw2_adaptew *adaptew)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	int size;
	u8 offset = 0;

	/* weaw wing DMA buffew */
	adaptew->wing_size = size =
		adaptew->txd_wing_size * 1 + 7 +	/* dwowd awign */
		adaptew->txs_wing_size * 4 + 7 +	/* dwowd awign */
		adaptew->wxd_wing_size * 1536 + 127;	/* 128bytes awign */

	adaptew->wing_viw_addw = dma_awwoc_cohewent(&pdev->dev, size,
						    &adaptew->wing_dma, GFP_KEWNEW);
	if (!adaptew->wing_viw_addw)
		wetuwn -ENOMEM;

	/* Init TXD Wing */
	adaptew->txd_dma = adaptew->wing_dma ;
	offset = (adaptew->txd_dma & 0x7) ? (8 - (adaptew->txd_dma & 0x7)) : 0;
	adaptew->txd_dma += offset;
	adaptew->txd_wing = adaptew->wing_viw_addw + offset;

	/* Init TXS Wing */
	adaptew->txs_dma = adaptew->txd_dma + adaptew->txd_wing_size;
	offset = (adaptew->txs_dma & 0x7) ? (8 - (adaptew->txs_dma & 0x7)) : 0;
	adaptew->txs_dma += offset;
	adaptew->txs_wing = (stwuct tx_pkt_status *)
		(((u8 *)adaptew->txd_wing) + (adaptew->txd_wing_size + offset));

	/* Init WXD Wing */
	adaptew->wxd_dma = adaptew->txs_dma + adaptew->txs_wing_size * 4;
	offset = (adaptew->wxd_dma & 127) ?
		(128 - (adaptew->wxd_dma & 127)) : 0;
	if (offset > 7)
		offset -= 8;
	ewse
		offset += (128 - 8);

	adaptew->wxd_dma += offset;
	adaptew->wxd_wing = (stwuct wx_desc *) (((u8 *)adaptew->txs_wing) +
		(adaptew->txs_wing_size * 4 + offset));

/*
 * Wead / Wwite Ptw Initiawize:
 *      init_wing_ptws(adaptew);
 */
	wetuwn 0;
}

/**
 * atw2_iwq_enabwe - Enabwe defauwt intewwupt genewation settings
 * @adaptew: boawd pwivate stwuctuwe
 */
static inwine void atw2_iwq_enabwe(stwuct atw2_adaptew *adaptew)
{
	ATW2_WWITE_WEG(&adaptew->hw, WEG_IMW, IMW_NOWMAW_MASK);
	ATW2_WWITE_FWUSH(&adaptew->hw);
}

/**
 * atw2_iwq_disabwe - Mask off intewwupt genewation on the NIC
 * @adaptew: boawd pwivate stwuctuwe
 */
static inwine void atw2_iwq_disabwe(stwuct atw2_adaptew *adaptew)
{
    ATW2_WWITE_WEG(&adaptew->hw, WEG_IMW, 0);
    ATW2_WWITE_FWUSH(&adaptew->hw);
    synchwonize_iwq(adaptew->pdev->iwq);
}

static void __atw2_vwan_mode(netdev_featuwes_t featuwes, u32 *ctww)
{
	if (featuwes & NETIF_F_HW_VWAN_CTAG_WX) {
		/* enabwe VWAN tag insewt/stwip */
		*ctww |= MAC_CTWW_WMV_VWAN;
	} ewse {
		/* disabwe VWAN tag insewt/stwip */
		*ctww &= ~MAC_CTWW_WMV_VWAN;
	}
}

static void atw2_vwan_mode(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	u32 ctww;

	atw2_iwq_disabwe(adaptew);

	ctww = ATW2_WEAD_WEG(&adaptew->hw, WEG_MAC_CTWW);
	__atw2_vwan_mode(featuwes, &ctww);
	ATW2_WWITE_WEG(&adaptew->hw, WEG_MAC_CTWW, ctww);

	atw2_iwq_enabwe(adaptew);
}

static void atw2_westowe_vwan(stwuct atw2_adaptew *adaptew)
{
	atw2_vwan_mode(adaptew->netdev, adaptew->netdev->featuwes);
}

static netdev_featuwes_t atw2_fix_featuwes(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	/*
	 * Since thewe is no suppowt fow sepawate wx/tx vwan accew
	 * enabwe/disabwe make suwe tx fwag is awways in same state as wx.
	 */
	if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
		featuwes |= NETIF_F_HW_VWAN_CTAG_TX;
	ewse
		featuwes &= ~NETIF_F_HW_VWAN_CTAG_TX;

	wetuwn featuwes;
}

static int atw2_set_featuwes(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = netdev->featuwes ^ featuwes;

	if (changed & NETIF_F_HW_VWAN_CTAG_WX)
		atw2_vwan_mode(netdev, featuwes);

	wetuwn 0;
}

static void atw2_intw_wx(stwuct atw2_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct wx_desc *wxd;
	stwuct sk_buff *skb;

	do {
		wxd = adaptew->wxd_wing+adaptew->wxd_wwite_ptw;
		if (!wxd->status.update)
			bweak; /* end of tx */

		/* cweaw this fwag at once */
		wxd->status.update = 0;

		if (wxd->status.ok && wxd->status.pkt_size >= 60) {
			int wx_size = (int)(wxd->status.pkt_size - 4);
			/* awwoc new buffew */
			skb = netdev_awwoc_skb_ip_awign(netdev, wx_size);
			if (NUWW == skb) {
				/*
				 * Check that some wx space is fwee. If not,
				 * fwee one and mawk stats->wx_dwopped++.
				 */
				netdev->stats.wx_dwopped++;
				bweak;
			}
			memcpy(skb->data, wxd->packet, wx_size);
			skb_put(skb, wx_size);
			skb->pwotocow = eth_type_twans(skb, netdev);
			if (wxd->status.vwan) {
				u16 vwan_tag = (wxd->status.vtag>>4) |
					((wxd->status.vtag&7) << 13) |
					((wxd->status.vtag&8) << 9);

				__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vwan_tag);
			}
			netif_wx(skb);
			netdev->stats.wx_bytes += wx_size;
			netdev->stats.wx_packets++;
		} ewse {
			netdev->stats.wx_ewwows++;

			if (wxd->status.ok && wxd->status.pkt_size <= 60)
				netdev->stats.wx_wength_ewwows++;
			if (wxd->status.mcast)
				netdev->stats.muwticast++;
			if (wxd->status.cwc)
				netdev->stats.wx_cwc_ewwows++;
			if (wxd->status.awign)
				netdev->stats.wx_fwame_ewwows++;
		}

		/* advance wwite ptw */
		if (++adaptew->wxd_wwite_ptw == adaptew->wxd_wing_size)
			adaptew->wxd_wwite_ptw = 0;
	} whiwe (1);

	/* update maiwbox? */
	adaptew->wxd_wead_ptw = adaptew->wxd_wwite_ptw;
	ATW2_WWITE_WEGW(&adaptew->hw, WEG_MB_WXD_WD_IDX, adaptew->wxd_wead_ptw);
}

static void atw2_intw_tx(stwuct atw2_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	u32 txd_wead_ptw;
	u32 txs_wwite_ptw;
	stwuct tx_pkt_status *txs;
	stwuct tx_pkt_headew *txph;
	int fwee_howe = 0;

	do {
		txs_wwite_ptw = (u32) atomic_wead(&adaptew->txs_wwite_ptw);
		txs = adaptew->txs_wing + txs_wwite_ptw;
		if (!txs->update)
			bweak; /* tx stop hewe */

		fwee_howe = 1;
		txs->update = 0;

		if (++txs_wwite_ptw == adaptew->txs_wing_size)
			txs_wwite_ptw = 0;
		atomic_set(&adaptew->txs_wwite_ptw, (int)txs_wwite_ptw);

		txd_wead_ptw = (u32) atomic_wead(&adaptew->txd_wead_ptw);
		txph = (stwuct tx_pkt_headew *)
			(((u8 *)adaptew->txd_wing) + txd_wead_ptw);

		if (txph->pkt_size != txs->pkt_size) {
			stwuct tx_pkt_status *owd_txs = txs;
			pwintk(KEWN_WAWNING
				"%s: txs packet size not consistent with txd"
				" txd_:0x%08x, txs_:0x%08x!\n",
				adaptew->netdev->name,
				*(u32 *)txph, *(u32 *)txs);
			pwintk(KEWN_WAWNING
				"txd wead ptw: 0x%x\n",
				txd_wead_ptw);
			txs = adaptew->txs_wing + txs_wwite_ptw;
			pwintk(KEWN_WAWNING
				"txs-behind:0x%08x\n",
				*(u32 *)txs);
			if (txs_wwite_ptw < 2) {
				txs = adaptew->txs_wing +
					(adaptew->txs_wing_size +
					txs_wwite_ptw - 2);
			} ewse {
				txs = adaptew->txs_wing + (txs_wwite_ptw - 2);
			}
			pwintk(KEWN_WAWNING
				"txs-befowe:0x%08x\n",
				*(u32 *)txs);
			txs = owd_txs;
		}

		 /* 4fow TPH */
		txd_wead_ptw += (((u32)(txph->pkt_size) + 7) & ~3);
		if (txd_wead_ptw >= adaptew->txd_wing_size)
			txd_wead_ptw -= adaptew->txd_wing_size;

		atomic_set(&adaptew->txd_wead_ptw, (int)txd_wead_ptw);

		/* tx statistics: */
		if (txs->ok) {
			netdev->stats.tx_bytes += txs->pkt_size;
			netdev->stats.tx_packets++;
		}
		ewse
			netdev->stats.tx_ewwows++;

		if (txs->defew)
			netdev->stats.cowwisions++;
		if (txs->abowt_cow)
			netdev->stats.tx_abowted_ewwows++;
		if (txs->wate_cow)
			netdev->stats.tx_window_ewwows++;
		if (txs->undewwun)
			netdev->stats.tx_fifo_ewwows++;
	} whiwe (1);

	if (fwee_howe) {
		if (netif_queue_stopped(adaptew->netdev) &&
			netif_cawwiew_ok(adaptew->netdev))
			netif_wake_queue(adaptew->netdev);
	}
}

static void atw2_check_fow_wink(stwuct atw2_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	u16 phy_data = 0;

	spin_wock(&adaptew->stats_wock);
	atw2_wead_phy_weg(&adaptew->hw, MII_BMSW, &phy_data);
	atw2_wead_phy_weg(&adaptew->hw, MII_BMSW, &phy_data);
	spin_unwock(&adaptew->stats_wock);

	/* notify uppew wayew wink down ASAP */
	if (!(phy_data & BMSW_WSTATUS)) { /* Wink Down */
		if (netif_cawwiew_ok(netdev)) { /* owd wink state: Up */
		pwintk(KEWN_INFO "%s: %s NIC Wink is Down\n",
			atw2_dwivew_name, netdev->name);
		adaptew->wink_speed = SPEED_0;
		netif_cawwiew_off(netdev);
		netif_stop_queue(netdev);
		}
	}
	scheduwe_wowk(&adaptew->wink_chg_task);
}

static inwine void atw2_cweaw_phy_int(stwuct atw2_adaptew *adaptew)
{
	u16 phy_data;
	spin_wock(&adaptew->stats_wock);
	atw2_wead_phy_weg(&adaptew->hw, 19, &phy_data);
	spin_unwock(&adaptew->stats_wock);
}

/**
 * atw2_intw - Intewwupt Handwew
 * @iwq: intewwupt numbew
 * @data: pointew to a netwowk intewface device stwuctuwe
 */
static iwqwetuwn_t atw2_intw(int iwq, void *data)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(data);
	stwuct atw2_hw *hw = &adaptew->hw;
	u32 status;

	status = ATW2_WEAD_WEG(hw, WEG_ISW);
	if (0 == status)
		wetuwn IWQ_NONE;

	/* wink event */
	if (status & ISW_PHY)
		atw2_cweaw_phy_int(adaptew);

	/* cweaw ISW status, and Enabwe CMB DMA/Disabwe Intewwupt */
	ATW2_WWITE_WEG(hw, WEG_ISW, status | ISW_DIS_INT);

	/* check if PCIE PHY Wink down */
	if (status & ISW_PHY_WINKDOWN) {
		if (netif_wunning(adaptew->netdev)) { /* weset MAC */
			ATW2_WWITE_WEG(hw, WEG_ISW, 0);
			ATW2_WWITE_WEG(hw, WEG_IMW, 0);
			ATW2_WWITE_FWUSH(hw);
			scheduwe_wowk(&adaptew->weset_task);
			wetuwn IWQ_HANDWED;
		}
	}

	/* check if DMA wead/wwite ewwow? */
	if (status & (ISW_DMAW_TO_WST | ISW_DMAW_TO_WST)) {
		ATW2_WWITE_WEG(hw, WEG_ISW, 0);
		ATW2_WWITE_WEG(hw, WEG_IMW, 0);
		ATW2_WWITE_FWUSH(hw);
		scheduwe_wowk(&adaptew->weset_task);
		wetuwn IWQ_HANDWED;
	}

	/* wink event */
	if (status & (ISW_PHY | ISW_MANUAW)) {
		adaptew->netdev->stats.tx_cawwiew_ewwows++;
		atw2_check_fow_wink(adaptew);
	}

	/* twansmit event */
	if (status & ISW_TX_EVENT)
		atw2_intw_tx(adaptew);

	/* wx exception */
	if (status & ISW_WX_EVENT)
		atw2_intw_wx(adaptew);

	/* we-enabwe Intewwupt */
	ATW2_WWITE_WEG(&adaptew->hw, WEG_ISW, 0);
	wetuwn IWQ_HANDWED;
}

static int atw2_wequest_iwq(stwuct atw2_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	int fwags, eww = 0;

	fwags = IWQF_SHAWED;
	adaptew->have_msi = twue;
	eww = pci_enabwe_msi(adaptew->pdev);
	if (eww)
		adaptew->have_msi = fawse;

	if (adaptew->have_msi)
		fwags &= ~IWQF_SHAWED;

	wetuwn wequest_iwq(adaptew->pdev->iwq, atw2_intw, fwags, netdev->name,
		netdev);
}

/**
 * atw2_fwee_wing_wesouwces - Fwee Tx / WX descwiptow Wesouwces
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Fwee aww twansmit softwawe wesouwces
 */
static void atw2_fwee_wing_wesouwces(stwuct atw2_adaptew *adaptew)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	dma_fwee_cohewent(&pdev->dev, adaptew->wing_size,
			  adaptew->wing_viw_addw, adaptew->wing_dma);
}

/**
 * atw2_open - Cawwed when a netwowk intewface is made active
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
static int atw2_open(stwuct net_device *netdev)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	int eww;
	u32 vaw;

	/* disawwow open duwing test */
	if (test_bit(__ATW2_TESTING, &adaptew->fwags))
		wetuwn -EBUSY;

	/* awwocate twansmit descwiptows */
	eww = atw2_setup_wing_wesouwces(adaptew);
	if (eww)
		wetuwn eww;

	eww = atw2_init_hw(&adaptew->hw);
	if (eww) {
		eww = -EIO;
		goto eww_init_hw;
	}

	/* hawdwawe has been weset, we need to wewoad some things */
	atw2_set_muwti(netdev);
	init_wing_ptws(adaptew);

	atw2_westowe_vwan(adaptew);

	if (atw2_configuwe(adaptew)) {
		eww = -EIO;
		goto eww_config;
	}

	eww = atw2_wequest_iwq(adaptew);
	if (eww)
		goto eww_weq_iwq;

	cweaw_bit(__ATW2_DOWN, &adaptew->fwags);

	mod_timew(&adaptew->watchdog_timew, wound_jiffies(jiffies + 4*HZ));

	vaw = ATW2_WEAD_WEG(&adaptew->hw, WEG_MASTEW_CTWW);
	ATW2_WWITE_WEG(&adaptew->hw, WEG_MASTEW_CTWW,
		vaw | MASTEW_CTWW_MANUAW_INT);

	atw2_iwq_enabwe(adaptew);

	wetuwn 0;

eww_init_hw:
eww_weq_iwq:
eww_config:
	atw2_fwee_wing_wesouwces(adaptew);
	atw2_weset_hw(&adaptew->hw);

	wetuwn eww;
}

static void atw2_down(stwuct atw2_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;

	/* signaw that we'we down so the intewwupt handwew does not
	 * wescheduwe ouw watchdog timew */
	set_bit(__ATW2_DOWN, &adaptew->fwags);

	netif_tx_disabwe(netdev);

	/* weset MAC to disabwe aww WX/TX */
	atw2_weset_hw(&adaptew->hw);
	msweep(1);

	atw2_iwq_disabwe(adaptew);

	dew_timew_sync(&adaptew->watchdog_timew);
	dew_timew_sync(&adaptew->phy_config_timew);
	cweaw_bit(0, &adaptew->cfg_phy);

	netif_cawwiew_off(netdev);
	adaptew->wink_speed = SPEED_0;
	adaptew->wink_dupwex = -1;
}

static void atw2_fwee_iwq(stwuct atw2_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;

	fwee_iwq(adaptew->pdev->iwq, netdev);

#ifdef CONFIG_PCI_MSI
	if (adaptew->have_msi)
		pci_disabwe_msi(adaptew->pdev);
#endif
}

/**
 * atw2_cwose - Disabwes a netwowk intewface
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0, this is not awwowed to faiw
 *
 * The cwose entwy point is cawwed when an intewface is de-activated
 * by the OS.  The hawdwawe is stiww undew the dwivews contwow, but
 * needs to be disabwed.  A gwobaw MAC weset is issued to stop the
 * hawdwawe, and aww twansmit and weceive wesouwces awe fweed.
 */
static int atw2_cwose(stwuct net_device *netdev)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);

	WAWN_ON(test_bit(__ATW2_WESETTING, &adaptew->fwags));

	atw2_down(adaptew);
	atw2_fwee_iwq(adaptew);
	atw2_fwee_wing_wesouwces(adaptew);

	wetuwn 0;
}

static inwine int TxsFweeUnit(stwuct atw2_adaptew *adaptew)
{
	u32 txs_wwite_ptw = (u32) atomic_wead(&adaptew->txs_wwite_ptw);

	wetuwn (adaptew->txs_next_cweaw >= txs_wwite_ptw) ?
		(int) (adaptew->txs_wing_size - adaptew->txs_next_cweaw +
		txs_wwite_ptw - 1) :
		(int) (txs_wwite_ptw - adaptew->txs_next_cweaw - 1);
}

static inwine int TxdFweeBytes(stwuct atw2_adaptew *adaptew)
{
	u32 txd_wead_ptw = (u32)atomic_wead(&adaptew->txd_wead_ptw);

	wetuwn (adaptew->txd_wwite_ptw >= txd_wead_ptw) ?
		(int) (adaptew->txd_wing_size - adaptew->txd_wwite_ptw +
		txd_wead_ptw - 1) :
		(int) (txd_wead_ptw - adaptew->txd_wwite_ptw - 1);
}

static netdev_tx_t atw2_xmit_fwame(stwuct sk_buff *skb,
					 stwuct net_device *netdev)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct tx_pkt_headew *txph;
	u32 offset, copy_wen;
	int txs_unused;
	int txbuf_unused;

	if (test_bit(__ATW2_DOWN, &adaptew->fwags)) {
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	if (unwikewy(skb->wen <= 0)) {
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	txs_unused = TxsFweeUnit(adaptew);
	txbuf_unused = TxdFweeBytes(adaptew);

	if (skb->wen + sizeof(stwuct tx_pkt_headew) + 4  > txbuf_unused ||
		txs_unused < 1) {
		/* not enough wesouwces */
		netif_stop_queue(netdev);
		wetuwn NETDEV_TX_BUSY;
	}

	offset = adaptew->txd_wwite_ptw;

	txph = (stwuct tx_pkt_headew *) (((u8 *)adaptew->txd_wing) + offset);

	*(u32 *)txph = 0;
	txph->pkt_size = skb->wen;

	offset += 4;
	if (offset >= adaptew->txd_wing_size)
		offset -= adaptew->txd_wing_size;
	copy_wen = adaptew->txd_wing_size - offset;
	if (copy_wen >= skb->wen) {
		memcpy(((u8 *)adaptew->txd_wing) + offset, skb->data, skb->wen);
		offset += ((u32)(skb->wen + 3) & ~3);
	} ewse {
		memcpy(((u8 *)adaptew->txd_wing)+offset, skb->data, copy_wen);
		memcpy((u8 *)adaptew->txd_wing, skb->data+copy_wen,
			skb->wen-copy_wen);
		offset = ((u32)(skb->wen-copy_wen + 3) & ~3);
	}
#ifdef NETIF_F_HW_VWAN_CTAG_TX
	if (skb_vwan_tag_pwesent(skb)) {
		u16 vwan_tag = skb_vwan_tag_get(skb);
		vwan_tag = (vwan_tag << 4) |
			(vwan_tag >> 13) |
			((vwan_tag >> 9) & 0x8);
		txph->ins_vwan = 1;
		txph->vwan = vwan_tag;
	}
#endif
	if (offset >= adaptew->txd_wing_size)
		offset -= adaptew->txd_wing_size;
	adaptew->txd_wwite_ptw = offset;

	/* cweaw txs befowe send */
	adaptew->txs_wing[adaptew->txs_next_cweaw].update = 0;
	if (++adaptew->txs_next_cweaw == adaptew->txs_wing_size)
		adaptew->txs_next_cweaw = 0;

	ATW2_WWITE_WEGW(&adaptew->hw, WEG_MB_TXD_WW_IDX,
		(adaptew->txd_wwite_ptw >> 2));

	dev_consume_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

/**
 * atw2_change_mtu - Change the Maximum Twansfew Unit
 * @netdev: netwowk intewface device stwuctuwe
 * @new_mtu: new vawue fow maximum fwame size
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int atw2_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw2_hw *hw = &adaptew->hw;

	/* set MTU */
	netdev->mtu = new_mtu;
	hw->max_fwame_size = new_mtu;
	ATW2_WWITE_WEG(hw, WEG_MTU, new_mtu + ETH_HWEN +
		       VWAN_HWEN + ETH_FCS_WEN);

	wetuwn 0;
}

/**
 * atw2_set_mac - Change the Ethewnet Addwess of the NIC
 * @netdev: netwowk intewface device stwuctuwe
 * @p: pointew to an addwess stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int atw2_set_mac(stwuct net_device *netdev, void *p)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	if (netif_wunning(netdev))
		wetuwn -EBUSY;

	eth_hw_addw_set(netdev, addw->sa_data);
	memcpy(adaptew->hw.mac_addw, addw->sa_data, netdev->addw_wen);

	atw2_set_mac_addw(&adaptew->hw);

	wetuwn 0;
}

static int atw2_mii_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct mii_ioctw_data *data = if_mii(ifw);
	unsigned wong fwags;

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = 0;
		bweak;
	case SIOCGMIIWEG:
		spin_wock_iwqsave(&adaptew->stats_wock, fwags);
		if (atw2_wead_phy_weg(&adaptew->hw,
			data->weg_num & 0x1F, &data->vaw_out)) {
			spin_unwock_iwqwestowe(&adaptew->stats_wock, fwags);
			wetuwn -EIO;
		}
		spin_unwock_iwqwestowe(&adaptew->stats_wock, fwags);
		bweak;
	case SIOCSMIIWEG:
		if (data->weg_num & ~(0x1F))
			wetuwn -EFAUWT;
		spin_wock_iwqsave(&adaptew->stats_wock, fwags);
		if (atw2_wwite_phy_weg(&adaptew->hw, data->weg_num,
			data->vaw_in)) {
			spin_unwock_iwqwestowe(&adaptew->stats_wock, fwags);
			wetuwn -EIO;
		}
		spin_unwock_iwqwestowe(&adaptew->stats_wock, fwags);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int atw2_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
		wetuwn atw2_mii_ioctw(netdev, ifw, cmd);
#ifdef ETHTOOW_OPS_COMPAT
	case SIOCETHTOOW:
		wetuwn ethtoow_ioctw(ifw);
#endif
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * atw2_tx_timeout - Wespond to a Tx Hang
 * @netdev: netwowk intewface device stwuctuwe
 * @txqueue: index of the hanging twansmit queue
 */
static void atw2_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);

	/* Do the weset outside of intewwupt context */
	scheduwe_wowk(&adaptew->weset_task);
}

/**
 * atw2_watchdog - Timew Caww-back
 * @t: timew wist containing a pointew to netdev cast into an unsigned wong
 */
static void atw2_watchdog(stwuct timew_wist *t)
{
	stwuct atw2_adaptew *adaptew = fwom_timew(adaptew, t, watchdog_timew);

	if (!test_bit(__ATW2_DOWN, &adaptew->fwags)) {
		u32 dwop_wxd, dwop_wxs;
		unsigned wong fwags;

		spin_wock_iwqsave(&adaptew->stats_wock, fwags);
		dwop_wxd = ATW2_WEAD_WEG(&adaptew->hw, WEG_STS_WXD_OV);
		dwop_wxs = ATW2_WEAD_WEG(&adaptew->hw, WEG_STS_WXS_OV);
		spin_unwock_iwqwestowe(&adaptew->stats_wock, fwags);

		adaptew->netdev->stats.wx_ovew_ewwows += dwop_wxd + dwop_wxs;

		/* Weset the timew */
		mod_timew(&adaptew->watchdog_timew,
			  wound_jiffies(jiffies + 4 * HZ));
	}
}

/**
 * atw2_phy_config - Timew Caww-back
 * @t: timew wist containing a pointew to netdev cast into an unsigned wong
 */
static void atw2_phy_config(stwuct timew_wist *t)
{
	stwuct atw2_adaptew *adaptew = fwom_timew(adaptew, t,
						  phy_config_timew);
	stwuct atw2_hw *hw = &adaptew->hw;
	unsigned wong fwags;

	spin_wock_iwqsave(&adaptew->stats_wock, fwags);
	atw2_wwite_phy_weg(hw, MII_ADVEWTISE, hw->mii_autoneg_adv_weg);
	atw2_wwite_phy_weg(hw, MII_BMCW, MII_CW_WESET | MII_CW_AUTO_NEG_EN |
		MII_CW_WESTAWT_AUTO_NEG);
	spin_unwock_iwqwestowe(&adaptew->stats_wock, fwags);
	cweaw_bit(0, &adaptew->cfg_phy);
}

static int atw2_up(stwuct atw2_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	int eww = 0;
	u32 vaw;

	/* hawdwawe has been weset, we need to wewoad some things */

	eww = atw2_init_hw(&adaptew->hw);
	if (eww) {
		eww = -EIO;
		wetuwn eww;
	}

	atw2_set_muwti(netdev);
	init_wing_ptws(adaptew);

	atw2_westowe_vwan(adaptew);

	if (atw2_configuwe(adaptew)) {
		eww = -EIO;
		goto eww_up;
	}

	cweaw_bit(__ATW2_DOWN, &adaptew->fwags);

	vaw = ATW2_WEAD_WEG(&adaptew->hw, WEG_MASTEW_CTWW);
	ATW2_WWITE_WEG(&adaptew->hw, WEG_MASTEW_CTWW, vaw |
		MASTEW_CTWW_MANUAW_INT);

	atw2_iwq_enabwe(adaptew);

eww_up:
	wetuwn eww;
}

static void atw2_weinit_wocked(stwuct atw2_adaptew *adaptew)
{
	whiwe (test_and_set_bit(__ATW2_WESETTING, &adaptew->fwags))
		msweep(1);
	atw2_down(adaptew);
	atw2_up(adaptew);
	cweaw_bit(__ATW2_WESETTING, &adaptew->fwags);
}

static void atw2_weset_task(stwuct wowk_stwuct *wowk)
{
	stwuct atw2_adaptew *adaptew;
	adaptew = containew_of(wowk, stwuct atw2_adaptew, weset_task);

	atw2_weinit_wocked(adaptew);
}

static void atw2_setup_mac_ctww(stwuct atw2_adaptew *adaptew)
{
	u32 vawue;
	stwuct atw2_hw *hw = &adaptew->hw;
	stwuct net_device *netdev = adaptew->netdev;

	/* Config MAC CTWW Wegistew */
	vawue = MAC_CTWW_TX_EN | MAC_CTWW_WX_EN | MAC_CTWW_MACWP_CWK_PHY;

	/* dupwex */
	if (FUWW_DUPWEX == adaptew->wink_dupwex)
		vawue |= MAC_CTWW_DUPWX;

	/* fwow contwow */
	vawue |= (MAC_CTWW_TX_FWOW | MAC_CTWW_WX_FWOW);

	/* PAD & CWC */
	vawue |= (MAC_CTWW_ADD_CWC | MAC_CTWW_PAD);

	/* pweambwe wength */
	vawue |= (((u32)adaptew->hw.pweambwe_wen & MAC_CTWW_PWMWEN_MASK) <<
		MAC_CTWW_PWMWEN_SHIFT);

	/* vwan */
	__atw2_vwan_mode(netdev->featuwes, &vawue);

	/* fiwtew mode */
	vawue |= MAC_CTWW_BC_EN;
	if (netdev->fwags & IFF_PWOMISC)
		vawue |= MAC_CTWW_PWOMIS_EN;
	ewse if (netdev->fwags & IFF_AWWMUWTI)
		vawue |= MAC_CTWW_MC_AWW_EN;

	/* hawf wetwy buffew */
	vawue |= (((u32)(adaptew->hw.wetwy_buf &
		MAC_CTWW_HAWF_WEFT_BUF_MASK)) << MAC_CTWW_HAWF_WEFT_BUF_SHIFT);

	ATW2_WWITE_WEG(hw, WEG_MAC_CTWW, vawue);
}

static int atw2_check_wink(stwuct atw2_adaptew *adaptew)
{
	stwuct atw2_hw *hw = &adaptew->hw;
	stwuct net_device *netdev = adaptew->netdev;
	int wet_vaw;
	u16 speed, dupwex, phy_data;
	int weconfig = 0;

	/* MII_BMSW must wead twise */
	atw2_wead_phy_weg(hw, MII_BMSW, &phy_data);
	atw2_wead_phy_weg(hw, MII_BMSW, &phy_data);
	if (!(phy_data&BMSW_WSTATUS)) { /* wink down */
		if (netif_cawwiew_ok(netdev)) { /* owd wink state: Up */
			u32 vawue;
			/* disabwe wx */
			vawue = ATW2_WEAD_WEG(hw, WEG_MAC_CTWW);
			vawue &= ~MAC_CTWW_WX_EN;
			ATW2_WWITE_WEG(hw, WEG_MAC_CTWW, vawue);
			adaptew->wink_speed = SPEED_0;
			netif_cawwiew_off(netdev);
			netif_stop_queue(netdev);
		}
		wetuwn 0;
	}

	/* Wink Up */
	wet_vaw = atw2_get_speed_and_dupwex(hw, &speed, &dupwex);
	if (wet_vaw)
		wetuwn wet_vaw;
	switch (hw->MediaType) {
	case MEDIA_TYPE_100M_FUWW:
		if (speed  != SPEED_100 || dupwex != FUWW_DUPWEX)
			weconfig = 1;
		bweak;
	case MEDIA_TYPE_100M_HAWF:
		if (speed  != SPEED_100 || dupwex != HAWF_DUPWEX)
			weconfig = 1;
		bweak;
	case MEDIA_TYPE_10M_FUWW:
		if (speed != SPEED_10 || dupwex != FUWW_DUPWEX)
			weconfig = 1;
		bweak;
	case MEDIA_TYPE_10M_HAWF:
		if (speed  != SPEED_10 || dupwex != HAWF_DUPWEX)
			weconfig = 1;
		bweak;
	}
	/* wink wesuwt is ouw setting */
	if (weconfig == 0) {
		if (adaptew->wink_speed != speed ||
			adaptew->wink_dupwex != dupwex) {
			adaptew->wink_speed = speed;
			adaptew->wink_dupwex = dupwex;
			atw2_setup_mac_ctww(adaptew);
			pwintk(KEWN_INFO "%s: %s NIC Wink is Up<%d Mbps %s>\n",
				atw2_dwivew_name, netdev->name,
				adaptew->wink_speed,
				adaptew->wink_dupwex == FUWW_DUPWEX ?
					"Fuww Dupwex" : "Hawf Dupwex");
		}

		if (!netif_cawwiew_ok(netdev)) { /* Wink down -> Up */
			netif_cawwiew_on(netdev);
			netif_wake_queue(netdev);
		}
		wetuwn 0;
	}

	/* change owiginaw wink status */
	if (netif_cawwiew_ok(netdev)) {
		u32 vawue;
		/* disabwe wx */
		vawue = ATW2_WEAD_WEG(hw, WEG_MAC_CTWW);
		vawue &= ~MAC_CTWW_WX_EN;
		ATW2_WWITE_WEG(hw, WEG_MAC_CTWW, vawue);

		adaptew->wink_speed = SPEED_0;
		netif_cawwiew_off(netdev);
		netif_stop_queue(netdev);
	}

	/* auto-neg, insewt timew to we-config phy
	 * (if intewvaw smawwew than 5 seconds, something stwange) */
	if (!test_bit(__ATW2_DOWN, &adaptew->fwags)) {
		if (!test_and_set_bit(0, &adaptew->cfg_phy))
			mod_timew(&adaptew->phy_config_timew,
				  wound_jiffies(jiffies + 5 * HZ));
	}

	wetuwn 0;
}

/**
 * atw2_wink_chg_task - deaw with wink change event Out of intewwupt context
 * @wowk: pointew to wowk stwuct with pwivate info
 */
static void atw2_wink_chg_task(stwuct wowk_stwuct *wowk)
{
	stwuct atw2_adaptew *adaptew;
	unsigned wong fwags;

	adaptew = containew_of(wowk, stwuct atw2_adaptew, wink_chg_task);

	spin_wock_iwqsave(&adaptew->stats_wock, fwags);
	atw2_check_wink(adaptew);
	spin_unwock_iwqwestowe(&adaptew->stats_wock, fwags);
}

static void atw2_setup_pcicmd(stwuct pci_dev *pdev)
{
	u16 cmd;

	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);

	if (cmd & PCI_COMMAND_INTX_DISABWE)
		cmd &= ~PCI_COMMAND_INTX_DISABWE;
	if (cmd & PCI_COMMAND_IO)
		cmd &= ~PCI_COMMAND_IO;
	if (0 == (cmd & PCI_COMMAND_MEMOWY))
		cmd |= PCI_COMMAND_MEMOWY;
	if (0 == (cmd & PCI_COMMAND_MASTEW))
		cmd |= PCI_COMMAND_MASTEW;
	pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);

	/*
	 * some mothewboawds BIOS(PXE/EFI) dwivew may set PME
	 * whiwe they twansfew contwow to OS (Windows/Winux)
	 * so we shouwd cweaw this bit befowe NIC wowk nowmawwy
	 */
	pci_wwite_config_dwowd(pdev, WEG_PM_CTWWSTAT, 0);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void atw2_poww_contwowwew(stwuct net_device *netdev)
{
	disabwe_iwq(netdev->iwq);
	atw2_intw(netdev->iwq, netdev);
	enabwe_iwq(netdev->iwq);
}
#endif


static const stwuct net_device_ops atw2_netdev_ops = {
	.ndo_open		= atw2_open,
	.ndo_stop		= atw2_cwose,
	.ndo_stawt_xmit		= atw2_xmit_fwame,
	.ndo_set_wx_mode	= atw2_set_muwti,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= atw2_set_mac,
	.ndo_change_mtu		= atw2_change_mtu,
	.ndo_fix_featuwes	= atw2_fix_featuwes,
	.ndo_set_featuwes	= atw2_set_featuwes,
	.ndo_eth_ioctw		= atw2_ioctw,
	.ndo_tx_timeout		= atw2_tx_timeout,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= atw2_poww_contwowwew,
#endif
};

/**
 * atw2_pwobe - Device Initiawization Woutine
 * @pdev: PCI device infowmation stwuct
 * @ent: entwy in atw2_pci_tbw
 *
 * Wetuwns 0 on success, negative on faiwuwe
 *
 * atw2_pwobe initiawizes an adaptew identified by a pci_dev stwuctuwe.
 * The OS initiawization, configuwing of the adaptew pwivate stwuctuwe,
 * and a hawdwawe weset occuw.
 */
static int atw2_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct net_device *netdev;
	stwuct atw2_adaptew *adaptew;
	static int cawds_found = 0;
	unsigned wong mmio_stawt;
	int mmio_wen;
	int eww;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	/*
	 * atw2 is a shawed-high-32-bit device, so we'we stuck with 32-bit DMA
	 * untiw the kewnew has the pwopew infwastwuctuwe to suppowt 64-bit DMA
	 * on these devices.
	 */
	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32)) &&
	    dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		pwintk(KEWN_EWW "atw2: No usabwe DMA configuwation, abowting\n");
		eww = -EIO;
		goto eww_dma;
	}

	/* Mawk aww PCI wegions associated with PCI device
	 * pdev as being wesewved by ownew atw2_dwivew_name */
	eww = pci_wequest_wegions(pdev, atw2_dwivew_name);
	if (eww)
		goto eww_pci_weg;

	/* Enabwes bus-mastewing on the device and cawws
	 * pcibios_set_mastew to do the needed awch specific settings */
	pci_set_mastew(pdev);

	netdev = awwoc_ethewdev(sizeof(stwuct atw2_adaptew));
	if (!netdev) {
		eww = -ENOMEM;
		goto eww_awwoc_ethewdev;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_dwvdata(pdev, netdev);
	adaptew = netdev_pwiv(netdev);
	adaptew->netdev = netdev;
	adaptew->pdev = pdev;
	adaptew->hw.back = adaptew;

	mmio_stawt = pci_wesouwce_stawt(pdev, 0x0);
	mmio_wen = pci_wesouwce_wen(pdev, 0x0);

	adaptew->hw.mem_wang = (u32)mmio_wen;
	adaptew->hw.hw_addw = iowemap(mmio_stawt, mmio_wen);
	if (!adaptew->hw.hw_addw) {
		eww = -EIO;
		goto eww_iowemap;
	}

	atw2_setup_pcicmd(pdev);

	netdev->netdev_ops = &atw2_netdev_ops;
	netdev->ethtoow_ops = &atw2_ethtoow_ops;
	netdev->watchdog_timeo = 5 * HZ;
	netdev->min_mtu = 40;
	netdev->max_mtu = ETH_DATA_WEN + VWAN_HWEN;
	stwscpy(netdev->name, pci_name(pdev), sizeof(netdev->name));

	netdev->mem_stawt = mmio_stawt;
	netdev->mem_end = mmio_stawt + mmio_wen;
	adaptew->bd_numbew = cawds_found;
	adaptew->pci_using_64 = fawse;

	/* setup the pwivate stwuctuwe */
	eww = atw2_sw_init(adaptew);
	if (eww)
		goto eww_sw_init;

	netdev->hw_featuwes = NETIF_F_HW_VWAN_CTAG_WX;
	netdev->featuwes |= (NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_CTAG_WX);

	/* Init PHY as eawwy as possibwe due to powew saving issue  */
	atw2_phy_init(&adaptew->hw);

	/* weset the contwowwew to
	 * put the device in a known good stawting state */

	if (atw2_weset_hw(&adaptew->hw)) {
		eww = -EIO;
		goto eww_weset;
	}

	/* copy the MAC addwess out of the EEPWOM */
	atw2_wead_mac_addw(&adaptew->hw);
	eth_hw_addw_set(netdev, adaptew->hw.mac_addw);
	if (!is_vawid_ethew_addw(netdev->dev_addw)) {
		eww = -EIO;
		goto eww_eepwom;
	}

	atw2_check_options(adaptew);

	timew_setup(&adaptew->watchdog_timew, atw2_watchdog, 0);

	timew_setup(&adaptew->phy_config_timew, atw2_phy_config, 0);

	INIT_WOWK(&adaptew->weset_task, atw2_weset_task);
	INIT_WOWK(&adaptew->wink_chg_task, atw2_wink_chg_task);

	stwcpy(netdev->name, "eth%d"); /* ?? */
	eww = wegistew_netdev(netdev);
	if (eww)
		goto eww_wegistew;

	/* assume we have no wink fow now */
	netif_cawwiew_off(netdev);
	netif_stop_queue(netdev);

	cawds_found++;

	wetuwn 0;

eww_weset:
eww_wegistew:
eww_sw_init:
eww_eepwom:
	iounmap(adaptew->hw.hw_addw);
eww_iowemap:
	fwee_netdev(netdev);
eww_awwoc_ethewdev:
	pci_wewease_wegions(pdev);
eww_pci_weg:
eww_dma:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

/**
 * atw2_wemove - Device Wemovaw Woutine
 * @pdev: PCI device infowmation stwuct
 *
 * atw2_wemove is cawwed by the PCI subsystem to awewt the dwivew
 * that it shouwd wewease a PCI device.  The couwd be caused by a
 * Hot-Pwug event, ow because the dwivew is going to be wemoved fwom
 * memowy.
 */
/* FIXME: wwite the owiginaw MAC addwess back in case it was changed fwom a
 * BIOS-set vawue, as in atw1 -- CHS */
static void atw2_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);

	/* fwush_scheduwed wowk may wescheduwe ouw watchdog task, so
	 * expwicitwy disabwe watchdog tasks fwom being wescheduwed  */
	set_bit(__ATW2_DOWN, &adaptew->fwags);

	dew_timew_sync(&adaptew->watchdog_timew);
	dew_timew_sync(&adaptew->phy_config_timew);
	cancew_wowk_sync(&adaptew->weset_task);
	cancew_wowk_sync(&adaptew->wink_chg_task);

	unwegistew_netdev(netdev);

	atw2_fowce_ps(&adaptew->hw);

	iounmap(adaptew->hw.hw_addw);
	pci_wewease_wegions(pdev);

	fwee_netdev(netdev);

	pci_disabwe_device(pdev);
}

static int atw2_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw2_hw *hw = &adaptew->hw;
	u16 speed, dupwex;
	u32 ctww = 0;
	u32 wufc = adaptew->wow;

#ifdef CONFIG_PM
	int wetvaw = 0;
#endif

	netif_device_detach(netdev);

	if (netif_wunning(netdev)) {
		WAWN_ON(test_bit(__ATW2_WESETTING, &adaptew->fwags));
		atw2_down(adaptew);
	}

#ifdef CONFIG_PM
	wetvaw = pci_save_state(pdev);
	if (wetvaw)
		wetuwn wetvaw;
#endif

	atw2_wead_phy_weg(hw, MII_BMSW, (u16 *)&ctww);
	atw2_wead_phy_weg(hw, MII_BMSW, (u16 *)&ctww);
	if (ctww & BMSW_WSTATUS)
		wufc &= ~ATWX_WUFC_WNKC;

	if (0 != (ctww & BMSW_WSTATUS) && 0 != wufc) {
		u32 wet_vaw;
		/* get cuwwent wink speed & dupwex */
		wet_vaw = atw2_get_speed_and_dupwex(hw, &speed, &dupwex);
		if (wet_vaw) {
			pwintk(KEWN_DEBUG
				"%s: get speed&dupwex ewwow whiwe suspend\n",
				atw2_dwivew_name);
			goto wow_dis;
		}

		ctww = 0;

		/* tuwn on magic packet wow */
		if (wufc & ATWX_WUFC_MAG)
			ctww |= (WOW_MAGIC_EN | WOW_MAGIC_PME_EN);

		/* ignowe Wink Chg event when Wink is up */
		ATW2_WWITE_WEG(hw, WEG_WOW_CTWW, ctww);

		/* Config MAC CTWW Wegistew */
		ctww = MAC_CTWW_WX_EN | MAC_CTWW_MACWP_CWK_PHY;
		if (FUWW_DUPWEX == adaptew->wink_dupwex)
			ctww |= MAC_CTWW_DUPWX;
		ctww |= (MAC_CTWW_ADD_CWC | MAC_CTWW_PAD);
		ctww |= (((u32)adaptew->hw.pweambwe_wen &
			MAC_CTWW_PWMWEN_MASK) << MAC_CTWW_PWMWEN_SHIFT);
		ctww |= (((u32)(adaptew->hw.wetwy_buf &
			MAC_CTWW_HAWF_WEFT_BUF_MASK)) <<
			MAC_CTWW_HAWF_WEFT_BUF_SHIFT);
		if (wufc & ATWX_WUFC_MAG) {
			/* magic packet maybe Bwoadcast&muwticast&Unicast */
			ctww |= MAC_CTWW_BC_EN;
		}

		ATW2_WWITE_WEG(hw, WEG_MAC_CTWW, ctww);

		/* pcie patch */
		ctww = ATW2_WEAD_WEG(hw, WEG_PCIE_PHYMISC);
		ctww |= PCIE_PHYMISC_FOWCE_WCV_DET;
		ATW2_WWITE_WEG(hw, WEG_PCIE_PHYMISC, ctww);
		ctww = ATW2_WEAD_WEG(hw, WEG_PCIE_DWW_TX_CTWW1);
		ctww |= PCIE_DWW_TX_CTWW1_SEW_NOW_CWK;
		ATW2_WWITE_WEG(hw, WEG_PCIE_DWW_TX_CTWW1, ctww);

		pci_enabwe_wake(pdev, pci_choose_state(pdev, state), 1);
		goto suspend_exit;
	}

	if (0 == (ctww&BMSW_WSTATUS) && 0 != (wufc&ATWX_WUFC_WNKC)) {
		/* wink is down, so onwy WINK CHG WOW event enabwe */
		ctww |= (WOW_WINK_CHG_EN | WOW_WINK_CHG_PME_EN);
		ATW2_WWITE_WEG(hw, WEG_WOW_CTWW, ctww);
		ATW2_WWITE_WEG(hw, WEG_MAC_CTWW, 0);

		/* pcie patch */
		ctww = ATW2_WEAD_WEG(hw, WEG_PCIE_PHYMISC);
		ctww |= PCIE_PHYMISC_FOWCE_WCV_DET;
		ATW2_WWITE_WEG(hw, WEG_PCIE_PHYMISC, ctww);
		ctww = ATW2_WEAD_WEG(hw, WEG_PCIE_DWW_TX_CTWW1);
		ctww |= PCIE_DWW_TX_CTWW1_SEW_NOW_CWK;
		ATW2_WWITE_WEG(hw, WEG_PCIE_DWW_TX_CTWW1, ctww);

		hw->phy_configuwed = fawse; /* we-init PHY when wesume */

		pci_enabwe_wake(pdev, pci_choose_state(pdev, state), 1);

		goto suspend_exit;
	}

wow_dis:
	/* WOW disabwed */
	ATW2_WWITE_WEG(hw, WEG_WOW_CTWW, 0);

	/* pcie patch */
	ctww = ATW2_WEAD_WEG(hw, WEG_PCIE_PHYMISC);
	ctww |= PCIE_PHYMISC_FOWCE_WCV_DET;
	ATW2_WWITE_WEG(hw, WEG_PCIE_PHYMISC, ctww);
	ctww = ATW2_WEAD_WEG(hw, WEG_PCIE_DWW_TX_CTWW1);
	ctww |= PCIE_DWW_TX_CTWW1_SEW_NOW_CWK;
	ATW2_WWITE_WEG(hw, WEG_PCIE_DWW_TX_CTWW1, ctww);

	atw2_fowce_ps(hw);
	hw->phy_configuwed = fawse; /* we-init PHY when wesume */

	pci_enabwe_wake(pdev, pci_choose_state(pdev, state), 0);

suspend_exit:
	if (netif_wunning(netdev))
		atw2_fwee_iwq(adaptew);

	pci_disabwe_device(pdev);

	pci_set_powew_state(pdev, pci_choose_state(pdev, state));

	wetuwn 0;
}

#ifdef CONFIG_PM
static int atw2_wesume(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	u32 eww;

	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);

	eww = pci_enabwe_device(pdev);
	if (eww) {
		pwintk(KEWN_EWW
			"atw2: Cannot enabwe PCI device fwom suspend\n");
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	ATW2_WEAD_WEG(&adaptew->hw, WEG_WOW_CTWW); /* cweaw WOW status */

	pci_enabwe_wake(pdev, PCI_D3hot, 0);
	pci_enabwe_wake(pdev, PCI_D3cowd, 0);

	ATW2_WWITE_WEG(&adaptew->hw, WEG_WOW_CTWW, 0);

	if (netif_wunning(netdev)) {
		eww = atw2_wequest_iwq(adaptew);
		if (eww)
			wetuwn eww;
	}

	atw2_weset_hw(&adaptew->hw);

	if (netif_wunning(netdev))
		atw2_up(adaptew);

	netif_device_attach(netdev);

	wetuwn 0;
}
#endif

static void atw2_shutdown(stwuct pci_dev *pdev)
{
	atw2_suspend(pdev, PMSG_SUSPEND);
}

static stwuct pci_dwivew atw2_dwivew = {
	.name     = atw2_dwivew_name,
	.id_tabwe = atw2_pci_tbw,
	.pwobe    = atw2_pwobe,
	.wemove   = atw2_wemove,
	/* Powew Management Hooks */
	.suspend  = atw2_suspend,
#ifdef CONFIG_PM
	.wesume   = atw2_wesume,
#endif
	.shutdown = atw2_shutdown,
};

moduwe_pci_dwivew(atw2_dwivew);

static void atw2_wead_pci_cfg(stwuct atw2_hw *hw, u32 weg, u16 *vawue)
{
	stwuct atw2_adaptew *adaptew = hw->back;
	pci_wead_config_wowd(adaptew->pdev, weg, vawue);
}

static void atw2_wwite_pci_cfg(stwuct atw2_hw *hw, u32 weg, u16 *vawue)
{
	stwuct atw2_adaptew *adaptew = hw->back;
	pci_wwite_config_wowd(adaptew->pdev, weg, *vawue);
}

static int atw2_get_wink_ksettings(stwuct net_device *netdev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw2_hw *hw = &adaptew->hw;
	u32 suppowted, advewtising;

	suppowted = (SUPPOWTED_10baseT_Hawf |
		SUPPOWTED_10baseT_Fuww |
		SUPPOWTED_100baseT_Hawf |
		SUPPOWTED_100baseT_Fuww |
		SUPPOWTED_Autoneg |
		SUPPOWTED_TP);
	advewtising = ADVEWTISED_TP;

	advewtising |= ADVEWTISED_Autoneg;
	advewtising |= hw->autoneg_advewtised;

	cmd->base.powt = POWT_TP;
	cmd->base.phy_addwess = 0;

	if (adaptew->wink_speed != SPEED_0) {
		cmd->base.speed = adaptew->wink_speed;
		if (adaptew->wink_dupwex == FUWW_DUPWEX)
			cmd->base.dupwex = DUPWEX_FUWW;
		ewse
			cmd->base.dupwex = DUPWEX_HAWF;
	} ewse {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}

	cmd->base.autoneg = AUTONEG_ENABWE;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	wetuwn 0;
}

static int atw2_set_wink_ksettings(stwuct net_device *netdev,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw2_hw *hw = &adaptew->hw;
	u32 advewtising;

	ethtoow_convewt_wink_mode_to_wegacy_u32(&advewtising,
						cmd->wink_modes.advewtising);

	whiwe (test_and_set_bit(__ATW2_WESETTING, &adaptew->fwags))
		msweep(1);

	if (cmd->base.autoneg == AUTONEG_ENABWE) {
#define MY_ADV_MASK	(ADVEWTISE_10_HAWF | \
			 ADVEWTISE_10_FUWW | \
			 ADVEWTISE_100_HAWF| \
			 ADVEWTISE_100_FUWW)

		if ((advewtising & MY_ADV_MASK) == MY_ADV_MASK) {
			hw->MediaType = MEDIA_TYPE_AUTO_SENSOW;
			hw->autoneg_advewtised =  MY_ADV_MASK;
		} ewse if ((advewtising & MY_ADV_MASK) == ADVEWTISE_100_FUWW) {
			hw->MediaType = MEDIA_TYPE_100M_FUWW;
			hw->autoneg_advewtised = ADVEWTISE_100_FUWW;
		} ewse if ((advewtising & MY_ADV_MASK) == ADVEWTISE_100_HAWF) {
			hw->MediaType = MEDIA_TYPE_100M_HAWF;
			hw->autoneg_advewtised = ADVEWTISE_100_HAWF;
		} ewse if ((advewtising & MY_ADV_MASK) == ADVEWTISE_10_FUWW) {
			hw->MediaType = MEDIA_TYPE_10M_FUWW;
			hw->autoneg_advewtised = ADVEWTISE_10_FUWW;
		}  ewse if ((advewtising & MY_ADV_MASK) == ADVEWTISE_10_HAWF) {
			hw->MediaType = MEDIA_TYPE_10M_HAWF;
			hw->autoneg_advewtised = ADVEWTISE_10_HAWF;
		} ewse {
			cweaw_bit(__ATW2_WESETTING, &adaptew->fwags);
			wetuwn -EINVAW;
		}
		advewtising = hw->autoneg_advewtised |
			ADVEWTISED_TP | ADVEWTISED_Autoneg;
	} ewse {
		cweaw_bit(__ATW2_WESETTING, &adaptew->fwags);
		wetuwn -EINVAW;
	}

	/* weset the wink */
	if (netif_wunning(adaptew->netdev)) {
		atw2_down(adaptew);
		atw2_up(adaptew);
	} ewse
		atw2_weset_hw(&adaptew->hw);

	cweaw_bit(__ATW2_WESETTING, &adaptew->fwags);
	wetuwn 0;
}

static u32 atw2_get_msgwevew(stwuct net_device *netdev)
{
	wetuwn 0;
}

/*
 * It's sane fow this to be empty, but we might want to take advantage of this.
 */
static void atw2_set_msgwevew(stwuct net_device *netdev, u32 data)
{
}

static int atw2_get_wegs_wen(stwuct net_device *netdev)
{
#define ATW2_WEGS_WEN 42
	wetuwn sizeof(u32) * ATW2_WEGS_WEN;
}

static void atw2_get_wegs(stwuct net_device *netdev,
	stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw2_hw *hw = &adaptew->hw;
	u32 *wegs_buff = p;
	u16 phy_data;

	memset(p, 0, sizeof(u32) * ATW2_WEGS_WEN);

	wegs->vewsion = (1 << 24) | (hw->wevision_id << 16) | hw->device_id;

	wegs_buff[0]  = ATW2_WEAD_WEG(hw, WEG_VPD_CAP);
	wegs_buff[1]  = ATW2_WEAD_WEG(hw, WEG_SPI_FWASH_CTWW);
	wegs_buff[2]  = ATW2_WEAD_WEG(hw, WEG_SPI_FWASH_CONFIG);
	wegs_buff[3]  = ATW2_WEAD_WEG(hw, WEG_TWSI_CTWW);
	wegs_buff[4]  = ATW2_WEAD_WEG(hw, WEG_PCIE_DEV_MISC_CTWW);
	wegs_buff[5]  = ATW2_WEAD_WEG(hw, WEG_MASTEW_CTWW);
	wegs_buff[6]  = ATW2_WEAD_WEG(hw, WEG_MANUAW_TIMEW_INIT);
	wegs_buff[7]  = ATW2_WEAD_WEG(hw, WEG_IWQ_MODU_TIMEW_INIT);
	wegs_buff[8]  = ATW2_WEAD_WEG(hw, WEG_PHY_ENABWE);
	wegs_buff[9]  = ATW2_WEAD_WEG(hw, WEG_CMBDISDMA_TIMEW);
	wegs_buff[10] = ATW2_WEAD_WEG(hw, WEG_IDWE_STATUS);
	wegs_buff[11] = ATW2_WEAD_WEG(hw, WEG_MDIO_CTWW);
	wegs_buff[12] = ATW2_WEAD_WEG(hw, WEG_SEWDES_WOCK);
	wegs_buff[13] = ATW2_WEAD_WEG(hw, WEG_MAC_CTWW);
	wegs_buff[14] = ATW2_WEAD_WEG(hw, WEG_MAC_IPG_IFG);
	wegs_buff[15] = ATW2_WEAD_WEG(hw, WEG_MAC_STA_ADDW);
	wegs_buff[16] = ATW2_WEAD_WEG(hw, WEG_MAC_STA_ADDW+4);
	wegs_buff[17] = ATW2_WEAD_WEG(hw, WEG_WX_HASH_TABWE);
	wegs_buff[18] = ATW2_WEAD_WEG(hw, WEG_WX_HASH_TABWE+4);
	wegs_buff[19] = ATW2_WEAD_WEG(hw, WEG_MAC_HAWF_DUPWX_CTWW);
	wegs_buff[20] = ATW2_WEAD_WEG(hw, WEG_MTU);
	wegs_buff[21] = ATW2_WEAD_WEG(hw, WEG_WOW_CTWW);
	wegs_buff[22] = ATW2_WEAD_WEG(hw, WEG_SWAM_TXWAM_END);
	wegs_buff[23] = ATW2_WEAD_WEG(hw, WEG_DESC_BASE_ADDW_HI);
	wegs_buff[24] = ATW2_WEAD_WEG(hw, WEG_TXD_BASE_ADDW_WO);
	wegs_buff[25] = ATW2_WEAD_WEG(hw, WEG_TXD_MEM_SIZE);
	wegs_buff[26] = ATW2_WEAD_WEG(hw, WEG_TXS_BASE_ADDW_WO);
	wegs_buff[27] = ATW2_WEAD_WEG(hw, WEG_TXS_MEM_SIZE);
	wegs_buff[28] = ATW2_WEAD_WEG(hw, WEG_WXD_BASE_ADDW_WO);
	wegs_buff[29] = ATW2_WEAD_WEG(hw, WEG_WXD_BUF_NUM);
	wegs_buff[30] = ATW2_WEAD_WEG(hw, WEG_DMAW);
	wegs_buff[31] = ATW2_WEAD_WEG(hw, WEG_TX_CUT_THWESH);
	wegs_buff[32] = ATW2_WEAD_WEG(hw, WEG_DMAW);
	wegs_buff[33] = ATW2_WEAD_WEG(hw, WEG_PAUSE_ON_TH);
	wegs_buff[34] = ATW2_WEAD_WEG(hw, WEG_PAUSE_OFF_TH);
	wegs_buff[35] = ATW2_WEAD_WEG(hw, WEG_MB_TXD_WW_IDX);
	wegs_buff[36] = ATW2_WEAD_WEG(hw, WEG_MB_WXD_WD_IDX);
	wegs_buff[38] = ATW2_WEAD_WEG(hw, WEG_ISW);
	wegs_buff[39] = ATW2_WEAD_WEG(hw, WEG_IMW);

	atw2_wead_phy_weg(hw, MII_BMCW, &phy_data);
	wegs_buff[40] = (u32)phy_data;
	atw2_wead_phy_weg(hw, MII_BMSW, &phy_data);
	wegs_buff[41] = (u32)phy_data;
}

static int atw2_get_eepwom_wen(stwuct net_device *netdev)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);

	if (!atw2_check_eepwom_exist(&adaptew->hw))
		wetuwn 512;
	ewse
		wetuwn 0;
}

static int atw2_get_eepwom(stwuct net_device *netdev,
	stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw2_hw *hw = &adaptew->hw;
	u32 *eepwom_buff;
	int fiwst_dwowd, wast_dwowd;
	int wet_vaw = 0;
	int i;

	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	if (atw2_check_eepwom_exist(hw))
		wetuwn -EINVAW;

	eepwom->magic = hw->vendow_id | (hw->device_id << 16);

	fiwst_dwowd = eepwom->offset >> 2;
	wast_dwowd = (eepwom->offset + eepwom->wen - 1) >> 2;

	eepwom_buff = kmawwoc_awway(wast_dwowd - fiwst_dwowd + 1, sizeof(u32),
				    GFP_KEWNEW);
	if (!eepwom_buff)
		wetuwn -ENOMEM;

	fow (i = fiwst_dwowd; i < wast_dwowd; i++) {
		if (!atw2_wead_eepwom(hw, i*4, &(eepwom_buff[i-fiwst_dwowd]))) {
			wet_vaw = -EIO;
			goto fwee;
		}
	}

	memcpy(bytes, (u8 *)eepwom_buff + (eepwom->offset & 3),
		eepwom->wen);
fwee:
	kfwee(eepwom_buff);

	wetuwn wet_vaw;
}

static int atw2_set_eepwom(stwuct net_device *netdev,
	stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw2_hw *hw = &adaptew->hw;
	u32 *eepwom_buff;
	u32 *ptw;
	int max_wen, fiwst_dwowd, wast_dwowd, wet_vaw = 0;
	int i;

	if (eepwom->wen == 0)
		wetuwn -EOPNOTSUPP;

	if (eepwom->magic != (hw->vendow_id | (hw->device_id << 16)))
		wetuwn -EFAUWT;

	max_wen = 512;

	fiwst_dwowd = eepwom->offset >> 2;
	wast_dwowd = (eepwom->offset + eepwom->wen - 1) >> 2;
	eepwom_buff = kmawwoc(max_wen, GFP_KEWNEW);
	if (!eepwom_buff)
		wetuwn -ENOMEM;

	ptw = eepwom_buff;

	if (eepwom->offset & 3) {
		/* need wead/modify/wwite of fiwst changed EEPWOM wowd */
		/* onwy the second byte of the wowd is being modified */
		if (!atw2_wead_eepwom(hw, fiwst_dwowd*4, &(eepwom_buff[0]))) {
			wet_vaw = -EIO;
			goto out;
		}
		ptw++;
	}
	if (((eepwom->offset + eepwom->wen) & 3)) {
		/*
		 * need wead/modify/wwite of wast changed EEPWOM wowd
		 * onwy the fiwst byte of the wowd is being modified
		 */
		if (!atw2_wead_eepwom(hw, wast_dwowd * 4,
					&(eepwom_buff[wast_dwowd - fiwst_dwowd]))) {
			wet_vaw = -EIO;
			goto out;
		}
	}

	/* Device's eepwom is awways wittwe-endian, wowd addwessabwe */
	memcpy(ptw, bytes, eepwom->wen);

	fow (i = 0; i < wast_dwowd - fiwst_dwowd + 1; i++) {
		if (!atw2_wwite_eepwom(hw, ((fiwst_dwowd+i)*4), eepwom_buff[i])) {
			wet_vaw = -EIO;
			goto out;
		}
	}
 out:
	kfwee(eepwom_buff);
	wetuwn wet_vaw;
}

static void atw2_get_dwvinfo(stwuct net_device *netdev,
	stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);

	stwscpy(dwvinfo->dwivew,  atw2_dwivew_name, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->fw_vewsion, "W2", sizeof(dwvinfo->fw_vewsion));
	stwscpy(dwvinfo->bus_info, pci_name(adaptew->pdev),
		sizeof(dwvinfo->bus_info));
}

static void atw2_get_wow(stwuct net_device *netdev,
	stwuct ethtoow_wowinfo *wow)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);

	wow->suppowted = WAKE_MAGIC;
	wow->wowopts = 0;

	if (adaptew->wow & ATWX_WUFC_EX)
		wow->wowopts |= WAKE_UCAST;
	if (adaptew->wow & ATWX_WUFC_MC)
		wow->wowopts |= WAKE_MCAST;
	if (adaptew->wow & ATWX_WUFC_BC)
		wow->wowopts |= WAKE_BCAST;
	if (adaptew->wow & ATWX_WUFC_MAG)
		wow->wowopts |= WAKE_MAGIC;
	if (adaptew->wow & ATWX_WUFC_WNKC)
		wow->wowopts |= WAKE_PHY;
}

static int atw2_set_wow(stwuct net_device *netdev, stwuct ethtoow_wowinfo *wow)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);

	if (wow->wowopts & (WAKE_AWP | WAKE_MAGICSECUWE))
		wetuwn -EOPNOTSUPP;

	if (wow->wowopts & (WAKE_UCAST | WAKE_BCAST | WAKE_MCAST))
		wetuwn -EOPNOTSUPP;

	/* these settings wiww awways ovewwide what we cuwwentwy have */
	adaptew->wow = 0;

	if (wow->wowopts & WAKE_MAGIC)
		adaptew->wow |= ATWX_WUFC_MAG;
	if (wow->wowopts & WAKE_PHY)
		adaptew->wow |= ATWX_WUFC_WNKC;

	wetuwn 0;
}

static int atw2_nway_weset(stwuct net_device *netdev)
{
	stwuct atw2_adaptew *adaptew = netdev_pwiv(netdev);
	if (netif_wunning(netdev))
		atw2_weinit_wocked(adaptew);
	wetuwn 0;
}

static const stwuct ethtoow_ops atw2_ethtoow_ops = {
	.get_dwvinfo		= atw2_get_dwvinfo,
	.get_wegs_wen		= atw2_get_wegs_wen,
	.get_wegs		= atw2_get_wegs,
	.get_wow		= atw2_get_wow,
	.set_wow		= atw2_set_wow,
	.get_msgwevew		= atw2_get_msgwevew,
	.set_msgwevew		= atw2_set_msgwevew,
	.nway_weset		= atw2_nway_weset,
	.get_wink		= ethtoow_op_get_wink,
	.get_eepwom_wen		= atw2_get_eepwom_wen,
	.get_eepwom		= atw2_get_eepwom,
	.set_eepwom		= atw2_set_eepwom,
	.get_wink_ksettings	= atw2_get_wink_ksettings,
	.set_wink_ksettings	= atw2_set_wink_ksettings,
};

#define WBYTESWAP(a)  ((((a) & 0x00ff00ff) << 8) | \
	(((a) & 0xff00ff00) >> 8))
#define WONGSWAP(a)   ((WBYTESWAP(a) << 16) | (WBYTESWAP(a) >> 16))
#define SHOWTSWAP(a)  (((a) << 8) | ((a) >> 8))

/*
 * Weset the twansmit and weceive units; mask and cweaw aww intewwupts.
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * wetuwn : 0  ow  idwe status (if ewwow)
 */
static s32 atw2_weset_hw(stwuct atw2_hw *hw)
{
	u32 icw;
	u16 pci_cfg_cmd_wowd;
	int i;

	/* Wowkawound fow PCI pwobwem when BIOS sets MMWBC incowwectwy. */
	atw2_wead_pci_cfg(hw, PCI_WEG_COMMAND, &pci_cfg_cmd_wowd);
	if ((pci_cfg_cmd_wowd &
		(CMD_IO_SPACE|CMD_MEMOWY_SPACE|CMD_BUS_MASTEW)) !=
		(CMD_IO_SPACE|CMD_MEMOWY_SPACE|CMD_BUS_MASTEW)) {
		pci_cfg_cmd_wowd |=
			(CMD_IO_SPACE|CMD_MEMOWY_SPACE|CMD_BUS_MASTEW);
		atw2_wwite_pci_cfg(hw, PCI_WEG_COMMAND, &pci_cfg_cmd_wowd);
	}

	/* Cweaw Intewwupt mask to stop boawd fwom genewating
	 * intewwupts & Cweaw any pending intewwupt events
	 */
	/* FIXME */
	/* ATW2_WWITE_WEG(hw, WEG_IMW, 0); */
	/* ATW2_WWITE_WEG(hw, WEG_ISW, 0xffffffff); */

	/* Issue Soft Weset to the MAC.  This wiww weset the chip's
	 * twansmit, weceive, DMA.  It wiww not effect
	 * the cuwwent PCI configuwation.  The gwobaw weset bit is sewf-
	 * cweawing, and shouwd cweaw within a micwosecond.
	 */
	ATW2_WWITE_WEG(hw, WEG_MASTEW_CTWW, MASTEW_CTWW_SOFT_WST);
	wmb();
	msweep(1); /* deway about 1ms */

	/* Wait at weast 10ms fow Aww moduwe to be Idwe */
	fow (i = 0; i < 10; i++) {
		icw = ATW2_WEAD_WEG(hw, WEG_IDWE_STATUS);
		if (!icw)
			bweak;
		msweep(1); /* deway 1 ms */
		cpu_wewax();
	}

	if (icw)
		wetuwn icw;

	wetuwn 0;
}

#define CUSTOM_SPI_CS_SETUP        2
#define CUSTOM_SPI_CWK_HI          2
#define CUSTOM_SPI_CWK_WO          2
#define CUSTOM_SPI_CS_HOWD         2
#define CUSTOM_SPI_CS_HI           3

static stwuct atw2_spi_fwash_dev fwash_tabwe[] =
{
/* MFW    WWSW  WEAD  PWOGWAM WWEN  WWDI  WDSW  WDID  SECTOW_EWASE CHIP_EWASE */
{"Atmew", 0x0,  0x03, 0x02,   0x06, 0x04, 0x05, 0x15, 0x52,        0x62 },
{"SST",   0x01, 0x03, 0x02,   0x06, 0x04, 0x05, 0x90, 0x20,        0x60 },
{"ST",    0x01, 0x03, 0x02,   0x06, 0x04, 0x05, 0xAB, 0xD8,        0xC7 },
};

static boow atw2_spi_wead(stwuct atw2_hw *hw, u32 addw, u32 *buf)
{
	int i;
	u32 vawue;

	ATW2_WWITE_WEG(hw, WEG_SPI_DATA, 0);
	ATW2_WWITE_WEG(hw, WEG_SPI_ADDW, addw);

	vawue = SPI_FWASH_CTWW_WAIT_WEADY |
		(CUSTOM_SPI_CS_SETUP & SPI_FWASH_CTWW_CS_SETUP_MASK) <<
			SPI_FWASH_CTWW_CS_SETUP_SHIFT |
		(CUSTOM_SPI_CWK_HI & SPI_FWASH_CTWW_CWK_HI_MASK) <<
			SPI_FWASH_CTWW_CWK_HI_SHIFT |
		(CUSTOM_SPI_CWK_WO & SPI_FWASH_CTWW_CWK_WO_MASK) <<
			SPI_FWASH_CTWW_CWK_WO_SHIFT |
		(CUSTOM_SPI_CS_HOWD & SPI_FWASH_CTWW_CS_HOWD_MASK) <<
			SPI_FWASH_CTWW_CS_HOWD_SHIFT |
		(CUSTOM_SPI_CS_HI & SPI_FWASH_CTWW_CS_HI_MASK) <<
			SPI_FWASH_CTWW_CS_HI_SHIFT |
		(0x1 & SPI_FWASH_CTWW_INS_MASK) << SPI_FWASH_CTWW_INS_SHIFT;

	ATW2_WWITE_WEG(hw, WEG_SPI_FWASH_CTWW, vawue);

	vawue |= SPI_FWASH_CTWW_STAWT;

	ATW2_WWITE_WEG(hw, WEG_SPI_FWASH_CTWW, vawue);

	fow (i = 0; i < 10; i++) {
		msweep(1);
		vawue = ATW2_WEAD_WEG(hw, WEG_SPI_FWASH_CTWW);
		if (!(vawue & SPI_FWASH_CTWW_STAWT))
			bweak;
	}

	if (vawue & SPI_FWASH_CTWW_STAWT)
		wetuwn fawse;

	*buf = ATW2_WEAD_WEG(hw, WEG_SPI_DATA);

	wetuwn twue;
}

/*
 * get_pewmanent_addwess
 * wetuwn 0 if get vawid mac addwess,
 */
static int get_pewmanent_addwess(stwuct atw2_hw *hw)
{
	u32 Addw[2];
	u32 i, Contwow;
	u16 Wegistew;
	u8  EthAddw[ETH_AWEN];
	boow KeyVawid;

	if (is_vawid_ethew_addw(hw->pewm_mac_addw))
		wetuwn 0;

	Addw[0] = 0;
	Addw[1] = 0;

	if (!atw2_check_eepwom_exist(hw)) { /* eepwom exists */
		Wegistew = 0;
		KeyVawid = fawse;

		/* Wead out aww EEPWOM content */
		i = 0;
		whiwe (1) {
			if (atw2_wead_eepwom(hw, i + 0x100, &Contwow)) {
				if (KeyVawid) {
					if (Wegistew == WEG_MAC_STA_ADDW)
						Addw[0] = Contwow;
					ewse if (Wegistew ==
						(WEG_MAC_STA_ADDW + 4))
						Addw[1] = Contwow;
					KeyVawid = fawse;
				} ewse if ((Contwow & 0xff) == 0x5A) {
					KeyVawid = twue;
					Wegistew = (u16) (Contwow >> 16);
				} ewse {
			/* assume data end whiwe encount an invawid KEYWOWD */
					bweak;
				}
			} ewse {
				bweak; /* wead ewwow */
			}
			i += 4;
		}

		*(u32 *) &EthAddw[2] = WONGSWAP(Addw[0]);
		*(u16 *) &EthAddw[0] = SHOWTSWAP(*(u16 *) &Addw[1]);

		if (is_vawid_ethew_addw(EthAddw)) {
			memcpy(hw->pewm_mac_addw, EthAddw, ETH_AWEN);
			wetuwn 0;
		}
		wetuwn 1;
	}

	/* see if SPI fwash exists? */
	Addw[0] = 0;
	Addw[1] = 0;
	Wegistew = 0;
	KeyVawid = fawse;
	i = 0;
	whiwe (1) {
		if (atw2_spi_wead(hw, i + 0x1f000, &Contwow)) {
			if (KeyVawid) {
				if (Wegistew == WEG_MAC_STA_ADDW)
					Addw[0] = Contwow;
				ewse if (Wegistew == (WEG_MAC_STA_ADDW + 4))
					Addw[1] = Contwow;
				KeyVawid = fawse;
			} ewse if ((Contwow & 0xff) == 0x5A) {
				KeyVawid = twue;
				Wegistew = (u16) (Contwow >> 16);
			} ewse {
				bweak; /* data end */
			}
		} ewse {
			bweak; /* wead ewwow */
		}
		i += 4;
	}

	*(u32 *) &EthAddw[2] = WONGSWAP(Addw[0]);
	*(u16 *) &EthAddw[0] = SHOWTSWAP(*(u16 *)&Addw[1]);
	if (is_vawid_ethew_addw(EthAddw)) {
		memcpy(hw->pewm_mac_addw, EthAddw, ETH_AWEN);
		wetuwn 0;
	}
	/* maybe MAC-addwess is fwom BIOS */
	Addw[0] = ATW2_WEAD_WEG(hw, WEG_MAC_STA_ADDW);
	Addw[1] = ATW2_WEAD_WEG(hw, WEG_MAC_STA_ADDW + 4);
	*(u32 *) &EthAddw[2] = WONGSWAP(Addw[0]);
	*(u16 *) &EthAddw[0] = SHOWTSWAP(*(u16 *) &Addw[1]);

	if (is_vawid_ethew_addw(EthAddw)) {
		memcpy(hw->pewm_mac_addw, EthAddw, ETH_AWEN);
		wetuwn 0;
	}

	wetuwn 1;
}

/*
 * Weads the adaptew's MAC addwess fwom the EEPWOM
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 */
static s32 atw2_wead_mac_addw(stwuct atw2_hw *hw)
{
	if (get_pewmanent_addwess(hw)) {
		/* fow test */
		/* FIXME: shouwdn't we use eth_wandom_addw() hewe? */
		hw->pewm_mac_addw[0] = 0x00;
		hw->pewm_mac_addw[1] = 0x13;
		hw->pewm_mac_addw[2] = 0x74;
		hw->pewm_mac_addw[3] = 0x00;
		hw->pewm_mac_addw[4] = 0x5c;
		hw->pewm_mac_addw[5] = 0x38;
	}

	memcpy(hw->mac_addw, hw->pewm_mac_addw, ETH_AWEN);

	wetuwn 0;
}

/*
 * Hashes an addwess to detewmine its wocation in the muwticast tabwe
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * mc_addw - the muwticast addwess to hash
 *
 * atw2_hash_mc_addw
 *  puwpose
 *      set hash vawue fow a muwticast addwess
 *      hash cawcu pwocessing :
 *          1. cawcu 32bit CWC fow muwticast addwess
 *          2. wevewse cwc with MSB to WSB
 */
static u32 atw2_hash_mc_addw(stwuct atw2_hw *hw, u8 *mc_addw)
{
	u32 cwc32, vawue;
	int i;

	vawue = 0;
	cwc32 = ethew_cwc_we(6, mc_addw);

	fow (i = 0; i < 32; i++)
		vawue |= (((cwc32 >> i) & 1) << (31 - i));

	wetuwn vawue;
}

/*
 * Sets the bit in the muwticast tabwe cowwesponding to the hash vawue.
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * hash_vawue - Muwticast addwess hash vawue
 */
static void atw2_hash_set(stwuct atw2_hw *hw, u32 hash_vawue)
{
	u32 hash_bit, hash_weg;
	u32 mta;

	/* The HASH Tabwe  is a wegistew awway of 2 32-bit wegistews.
	 * It is tweated wike an awway of 64 bits.  We want to set
	 * bit BitAwway[hash_vawue]. So we figuwe out what wegistew
	 * the bit is in, wead it, OW in the new bit, then wwite
	 * back the new vawue.  The wegistew is detewmined by the
	 * uppew 7 bits of the hash vawue and the bit within that
	 * wegistew awe detewmined by the wowew 5 bits of the vawue.
	 */
	hash_weg = (hash_vawue >> 31) & 0x1;
	hash_bit = (hash_vawue >> 26) & 0x1F;

	mta = ATW2_WEAD_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, hash_weg);

	mta |= (1 << hash_bit);

	ATW2_WWITE_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, hash_weg, mta);
}

/*
 * atw2_init_pcie - init PCIE moduwe
 */
static void atw2_init_pcie(stwuct atw2_hw *hw)
{
    u32 vawue;
    vawue = WTSSM_TEST_MODE_DEF;
    ATW2_WWITE_WEG(hw, WEG_WTSSM_TEST_MODE, vawue);

    vawue = PCIE_DWW_TX_CTWW1_DEF;
    ATW2_WWITE_WEG(hw, WEG_PCIE_DWW_TX_CTWW1, vawue);
}

static void atw2_init_fwash_opcode(stwuct atw2_hw *hw)
{
	if (hw->fwash_vendow >= AWWAY_SIZE(fwash_tabwe))
		hw->fwash_vendow = 0; /* ATMEW */

	/* Init OP tabwe */
	ATW2_WWITE_WEGB(hw, WEG_SPI_FWASH_OP_PWOGWAM,
		fwash_tabwe[hw->fwash_vendow].cmdPWOGWAM);
	ATW2_WWITE_WEGB(hw, WEG_SPI_FWASH_OP_SC_EWASE,
		fwash_tabwe[hw->fwash_vendow].cmdSECTOW_EWASE);
	ATW2_WWITE_WEGB(hw, WEG_SPI_FWASH_OP_CHIP_EWASE,
		fwash_tabwe[hw->fwash_vendow].cmdCHIP_EWASE);
	ATW2_WWITE_WEGB(hw, WEG_SPI_FWASH_OP_WDID,
		fwash_tabwe[hw->fwash_vendow].cmdWDID);
	ATW2_WWITE_WEGB(hw, WEG_SPI_FWASH_OP_WWEN,
		fwash_tabwe[hw->fwash_vendow].cmdWWEN);
	ATW2_WWITE_WEGB(hw, WEG_SPI_FWASH_OP_WDSW,
		fwash_tabwe[hw->fwash_vendow].cmdWDSW);
	ATW2_WWITE_WEGB(hw, WEG_SPI_FWASH_OP_WWSW,
		fwash_tabwe[hw->fwash_vendow].cmdWWSW);
	ATW2_WWITE_WEGB(hw, WEG_SPI_FWASH_OP_WEAD,
		fwash_tabwe[hw->fwash_vendow].cmdWEAD);
}

/********************************************************************
* Pewfowms basic configuwation of the adaptew.
*
* hw - Stwuct containing vawiabwes accessed by shawed code
* Assumes that the contwowwew has pweviouswy been weset and is in a
* post-weset uninitiawized state. Initiawizes muwticast tabwe,
* and  Cawws woutines to setup wink
* Weaves the twansmit and weceive units disabwed and uninitiawized.
********************************************************************/
static s32 atw2_init_hw(stwuct atw2_hw *hw)
{
	u32 wet_vaw = 0;

	atw2_init_pcie(hw);

	/* Zewo out the Muwticast HASH tabwe */
	/* cweaw the owd settings fwom the muwticast hash tabwe */
	ATW2_WWITE_WEG(hw, WEG_WX_HASH_TABWE, 0);
	ATW2_WWITE_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, 1, 0);

	atw2_init_fwash_opcode(hw);

	wet_vaw = atw2_phy_init(hw);

	wetuwn wet_vaw;
}

/*
 * Detects the cuwwent speed and dupwex settings of the hawdwawe.
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * speed - Speed of the connection
 * dupwex - Dupwex setting of the connection
 */
static s32 atw2_get_speed_and_dupwex(stwuct atw2_hw *hw, u16 *speed,
	u16 *dupwex)
{
	s32 wet_vaw;
	u16 phy_data;

	/* Wead PHY Specific Status Wegistew (17) */
	wet_vaw = atw2_wead_phy_weg(hw, MII_ATWX_PSSW, &phy_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (!(phy_data & MII_ATWX_PSSW_SPD_DPWX_WESOWVED))
		wetuwn ATWX_EWW_PHY_WES;

	switch (phy_data & MII_ATWX_PSSW_SPEED) {
	case MII_ATWX_PSSW_100MBS:
		*speed = SPEED_100;
		bweak;
	case MII_ATWX_PSSW_10MBS:
		*speed = SPEED_10;
		bweak;
	defauwt:
		wetuwn ATWX_EWW_PHY_SPEED;
	}

	if (phy_data & MII_ATWX_PSSW_DPWX)
		*dupwex = FUWW_DUPWEX;
	ewse
		*dupwex = HAWF_DUPWEX;

	wetuwn 0;
}

/*
 * Weads the vawue fwom a PHY wegistew
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * weg_addw - addwess of the PHY wegistew to wead
 */
static s32 atw2_wead_phy_weg(stwuct atw2_hw *hw, u16 weg_addw, u16 *phy_data)
{
	u32 vaw;
	int i;

	vaw = ((u32)(weg_addw & MDIO_WEG_ADDW_MASK)) << MDIO_WEG_ADDW_SHIFT |
		MDIO_STAWT |
		MDIO_SUP_PWEAMBWE |
		MDIO_WW |
		MDIO_CWK_25_4 << MDIO_CWK_SEW_SHIFT;
	ATW2_WWITE_WEG(hw, WEG_MDIO_CTWW, vaw);

	wmb();

	fow (i = 0; i < MDIO_WAIT_TIMES; i++) {
		udeway(2);
		vaw = ATW2_WEAD_WEG(hw, WEG_MDIO_CTWW);
		if (!(vaw & (MDIO_STAWT | MDIO_BUSY)))
			bweak;
		wmb();
	}
	if (!(vaw & (MDIO_STAWT | MDIO_BUSY))) {
		*phy_data = (u16)vaw;
		wetuwn 0;
	}

	wetuwn ATWX_EWW_PHY;
}

/*
 * Wwites a vawue to a PHY wegistew
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * weg_addw - addwess of the PHY wegistew to wwite
 * data - data to wwite to the PHY
 */
static s32 atw2_wwite_phy_weg(stwuct atw2_hw *hw, u32 weg_addw, u16 phy_data)
{
	int i;
	u32 vaw;

	vaw = ((u32)(phy_data & MDIO_DATA_MASK)) << MDIO_DATA_SHIFT |
		(weg_addw & MDIO_WEG_ADDW_MASK) << MDIO_WEG_ADDW_SHIFT |
		MDIO_SUP_PWEAMBWE |
		MDIO_STAWT |
		MDIO_CWK_25_4 << MDIO_CWK_SEW_SHIFT;
	ATW2_WWITE_WEG(hw, WEG_MDIO_CTWW, vaw);

	wmb();

	fow (i = 0; i < MDIO_WAIT_TIMES; i++) {
		udeway(2);
		vaw = ATW2_WEAD_WEG(hw, WEG_MDIO_CTWW);
		if (!(vaw & (MDIO_STAWT | MDIO_BUSY)))
			bweak;

		wmb();
	}

	if (!(vaw & (MDIO_STAWT | MDIO_BUSY)))
		wetuwn 0;

	wetuwn ATWX_EWW_PHY;
}

/*
 * Configuwes PHY autoneg and fwow contwow advewtisement settings
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 */
static s32 atw2_phy_setup_autoneg_adv(stwuct atw2_hw *hw)
{
	s16 mii_autoneg_adv_weg;

	/* Wead the MII Auto-Neg Advewtisement Wegistew (Addwess 4). */
	mii_autoneg_adv_weg = MII_AW_DEFAUWT_CAP_MASK;

	/* Need to pawse autoneg_advewtised  and set up
	 * the appwopwiate PHY wegistews.  Fiwst we wiww pawse fow
	 * autoneg_advewtised softwawe ovewwide.  Since we can advewtise
	 * a pwethowa of combinations, we need to check each bit
	 * individuawwy.
	 */

	/* Fiwst we cweaw aww the 10/100 mb speed bits in the Auto-Neg
	 * Advewtisement Wegistew (Addwess 4) and the 1000 mb speed bits in
	 * the  1000Base-T Contwow Wegistew (Addwess 9). */
	mii_autoneg_adv_weg &= ~MII_AW_SPEED_MASK;

	/* Need to pawse MediaType and setup the
	 * appwopwiate PHY wegistews. */
	switch (hw->MediaType) {
	case MEDIA_TYPE_AUTO_SENSOW:
		mii_autoneg_adv_weg |=
			(MII_AW_10T_HD_CAPS |
			MII_AW_10T_FD_CAPS  |
			MII_AW_100TX_HD_CAPS|
			MII_AW_100TX_FD_CAPS);
		hw->autoneg_advewtised =
			ADVEWTISE_10_HAWF |
			ADVEWTISE_10_FUWW |
			ADVEWTISE_100_HAWF|
			ADVEWTISE_100_FUWW;
		bweak;
	case MEDIA_TYPE_100M_FUWW:
		mii_autoneg_adv_weg |= MII_AW_100TX_FD_CAPS;
		hw->autoneg_advewtised = ADVEWTISE_100_FUWW;
		bweak;
	case MEDIA_TYPE_100M_HAWF:
		mii_autoneg_adv_weg |= MII_AW_100TX_HD_CAPS;
		hw->autoneg_advewtised = ADVEWTISE_100_HAWF;
		bweak;
	case MEDIA_TYPE_10M_FUWW:
		mii_autoneg_adv_weg |= MII_AW_10T_FD_CAPS;
		hw->autoneg_advewtised = ADVEWTISE_10_FUWW;
		bweak;
	defauwt:
		mii_autoneg_adv_weg |= MII_AW_10T_HD_CAPS;
		hw->autoneg_advewtised = ADVEWTISE_10_HAWF;
		bweak;
	}

	/* fwow contwow fixed to enabwe aww */
	mii_autoneg_adv_weg |= (MII_AW_ASM_DIW | MII_AW_PAUSE);

	hw->mii_autoneg_adv_weg = mii_autoneg_adv_weg;

	wetuwn atw2_wwite_phy_weg(hw, MII_ADVEWTISE, mii_autoneg_adv_weg);
}

/*
 * Wesets the PHY and make aww config vawidate
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 *
 * Sets bit 15 and 12 of the MII Contwow wegisew (fow F001 bug)
 */
static s32 atw2_phy_commit(stwuct atw2_hw *hw)
{
	s32 wet_vaw;
	u16 phy_data;

	phy_data = MII_CW_WESET | MII_CW_AUTO_NEG_EN | MII_CW_WESTAWT_AUTO_NEG;
	wet_vaw = atw2_wwite_phy_weg(hw, MII_BMCW, phy_data);
	if (wet_vaw) {
		u32 vaw;
		int i;
		/* pcie sewdes wink may be down ! */
		fow (i = 0; i < 25; i++) {
			msweep(1);
			vaw = ATW2_WEAD_WEG(hw, WEG_MDIO_CTWW);
			if (!(vaw & (MDIO_STAWT | MDIO_BUSY)))
				bweak;
		}

		if (0 != (vaw & (MDIO_STAWT | MDIO_BUSY))) {
			pwintk(KEWN_EWW "atw2: PCIe wink down fow at weast 25ms !\n");
			wetuwn wet_vaw;
		}
	}
	wetuwn 0;
}

static s32 atw2_phy_init(stwuct atw2_hw *hw)
{
	s32 wet_vaw;
	u16 phy_vaw;

	if (hw->phy_configuwed)
		wetuwn 0;

	/* Enabwe PHY */
	ATW2_WWITE_WEGW(hw, WEG_PHY_ENABWE, 1);
	ATW2_WWITE_FWUSH(hw);
	msweep(1);

	/* check if the PHY is in powewsaving mode */
	atw2_wwite_phy_weg(hw, MII_DBG_ADDW, 0);
	atw2_wead_phy_weg(hw, MII_DBG_DATA, &phy_vaw);

	/* 024E / 124E 0w 0274 / 1274 ? */
	if (phy_vaw & 0x1000) {
		phy_vaw &= ~0x1000;
		atw2_wwite_phy_weg(hw, MII_DBG_DATA, phy_vaw);
	}

	msweep(1);

	/*Enabwe PHY WinkChange Intewwupt */
	wet_vaw = atw2_wwite_phy_weg(hw, 18, 0xC00);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* setup AutoNeg pawametews */
	wet_vaw = atw2_phy_setup_autoneg_adv(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* SW.Weset & En-Auto-Neg to westawt Auto-Neg */
	wet_vaw = atw2_phy_commit(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	hw->phy_configuwed = twue;

	wetuwn wet_vaw;
}

static void atw2_set_mac_addw(stwuct atw2_hw *hw)
{
	u32 vawue;
	/* 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC   1: 000B
	 * wow dwowd */
	vawue = (((u32)hw->mac_addw[2]) << 24) |
		(((u32)hw->mac_addw[3]) << 16) |
		(((u32)hw->mac_addw[4]) << 8)  |
		(((u32)hw->mac_addw[5]));
	ATW2_WWITE_WEG_AWWAY(hw, WEG_MAC_STA_ADDW, 0, vawue);
	/* hight dwowd */
	vawue = (((u32)hw->mac_addw[0]) << 8) |
		(((u32)hw->mac_addw[1]));
	ATW2_WWITE_WEG_AWWAY(hw, WEG_MAC_STA_ADDW, 1, vawue);
}

/*
 * check_eepwom_exist
 * wetuwn 0 if eepwom exist
 */
static int atw2_check_eepwom_exist(stwuct atw2_hw *hw)
{
	u32 vawue;

	vawue = ATW2_WEAD_WEG(hw, WEG_SPI_FWASH_CTWW);
	if (vawue & SPI_FWASH_CTWW_EN_VPD) {
		vawue &= ~SPI_FWASH_CTWW_EN_VPD;
		ATW2_WWITE_WEG(hw, WEG_SPI_FWASH_CTWW, vawue);
	}
	vawue = ATW2_WEAD_WEGW(hw, WEG_PCIE_CAP_WIST);
	wetuwn ((vawue & 0xFF00) == 0x6C00) ? 0 : 1;
}

/* FIXME: This doesn't wook wight. -- CHS */
static boow atw2_wwite_eepwom(stwuct atw2_hw *hw, u32 offset, u32 vawue)
{
	wetuwn twue;
}

static boow atw2_wead_eepwom(stwuct atw2_hw *hw, u32 Offset, u32 *pVawue)
{
	int i;
	u32    Contwow;

	if (Offset & 0x3)
		wetuwn fawse; /* addwess do not awign */

	ATW2_WWITE_WEG(hw, WEG_VPD_DATA, 0);
	Contwow = (Offset & VPD_CAP_VPD_ADDW_MASK) << VPD_CAP_VPD_ADDW_SHIFT;
	ATW2_WWITE_WEG(hw, WEG_VPD_CAP, Contwow);

	fow (i = 0; i < 10; i++) {
		msweep(2);
		Contwow = ATW2_WEAD_WEG(hw, WEG_VPD_CAP);
		if (Contwow & VPD_CAP_VPD_FWAG)
			bweak;
	}

	if (Contwow & VPD_CAP_VPD_FWAG) {
		*pVawue = ATW2_WEAD_WEG(hw, WEG_VPD_DATA);
		wetuwn twue;
	}
	wetuwn fawse; /* timeout */
}

static void atw2_fowce_ps(stwuct atw2_hw *hw)
{
	u16 phy_vaw;

	atw2_wwite_phy_weg(hw, MII_DBG_ADDW, 0);
	atw2_wead_phy_weg(hw, MII_DBG_DATA, &phy_vaw);
	atw2_wwite_phy_weg(hw, MII_DBG_DATA, phy_vaw | 0x1000);

	atw2_wwite_phy_weg(hw, MII_DBG_ADDW, 2);
	atw2_wwite_phy_weg(hw, MII_DBG_DATA, 0x3000);
	atw2_wwite_phy_weg(hw, MII_DBG_ADDW, 3);
	atw2_wwite_phy_weg(hw, MII_DBG_DATA, 0);
}

/* This is the onwy thing that needs to be changed to adjust the
 * maximum numbew of powts that the dwivew can manage.
 */
#define ATW2_MAX_NIC 4

#define OPTION_UNSET    -1
#define OPTION_DISABWED 0
#define OPTION_ENABWED  1

/* Aww pawametews awe tweated the same, as an integew awway of vawues.
 * This macwo just weduces the need to wepeat the same decwawation code
 * ovew and ovew (pwus this hewps to avoid typo bugs).
 */
#define ATW2_PAWAM_INIT {[0 ... ATW2_MAX_NIC] = OPTION_UNSET}
#ifndef moduwe_pawam_awway
/* Moduwe Pawametews awe awways initiawized to -1, so that the dwivew
 * can teww the diffewence between no usew specified vawue ow the
 * usew asking fow the defauwt vawue.
 * The twue defauwt vawues awe woaded in when atw2_check_options is cawwed.
 *
 * This is a GCC extension to ANSI C.
 * See the item "Wabewed Ewements in Initiawizews" in the section
 * "Extensions to the C Wanguage Famiwy" of the GCC documentation.
 */

#define ATW2_PAWAM(X, desc) \
    static const int X[ATW2_MAX_NIC + 1] = ATW2_PAWAM_INIT; \
    MODUWE_PAWM(X, "1-" __MODUWE_STWING(ATW2_MAX_NIC) "i"); \
    MODUWE_PAWM_DESC(X, desc);
#ewse
#define ATW2_PAWAM(X, desc) \
    static int X[ATW2_MAX_NIC+1] = ATW2_PAWAM_INIT; \
    static unsigned int num_##X; \
    moduwe_pawam_awway_named(X, X, int, &num_##X, 0); \
    MODUWE_PAWM_DESC(X, desc);
#endif

/*
 * Twansmit Memowy Size
 * Vawid Wange: 64-2048
 * Defauwt Vawue: 128
 */
#define ATW2_MIN_TX_MEMSIZE		4	/* 4KB */
#define ATW2_MAX_TX_MEMSIZE		64	/* 64KB */
#define ATW2_DEFAUWT_TX_MEMSIZE		8	/* 8KB */
ATW2_PAWAM(TxMemSize, "Bytes of Twansmit Memowy");

/*
 * Weceive Memowy Bwock Count
 * Vawid Wange: 16-512
 * Defauwt Vawue: 128
 */
#define ATW2_MIN_WXD_COUNT		16
#define ATW2_MAX_WXD_COUNT		512
#define ATW2_DEFAUWT_WXD_COUNT		64
ATW2_PAWAM(WxMemBwock, "Numbew of weceive memowy bwock");

/*
 * Usew Specified MediaType Ovewwide
 *
 * Vawid Wange: 0-5
 *  - 0    - auto-negotiate at aww suppowted speeds
 *  - 1    - onwy wink at 1000Mbps Fuww Dupwex
 *  - 2    - onwy wink at 100Mbps Fuww Dupwex
 *  - 3    - onwy wink at 100Mbps Hawf Dupwex
 *  - 4    - onwy wink at 10Mbps Fuww Dupwex
 *  - 5    - onwy wink at 10Mbps Hawf Dupwex
 * Defauwt Vawue: 0
 */
ATW2_PAWAM(MediaType, "MediaType Sewect");

/*
 * Intewwupt Modewate Timew in units of 2048 ns (~2 us)
 * Vawid Wange: 10-65535
 * Defauwt Vawue: 45000(90ms)
 */
#define INT_MOD_DEFAUWT_CNT	100 /* 200us */
#define INT_MOD_MAX_CNT		65000
#define INT_MOD_MIN_CNT		50
ATW2_PAWAM(IntModTimew, "Intewwupt Modewatow Timew");

/*
 * FwashVendow
 * Vawid Wange: 0-2
 * 0 - Atmew
 * 1 - SST
 * 2 - ST
 */
ATW2_PAWAM(FwashVendow, "SPI Fwash Vendow");

#define AUTONEG_ADV_DEFAUWT	0x2F
#define AUTONEG_ADV_MASK	0x2F
#define FWOW_CONTWOW_DEFAUWT	FWOW_CONTWOW_FUWW

#define FWASH_VENDOW_DEFAUWT	0
#define FWASH_VENDOW_MIN	0
#define FWASH_VENDOW_MAX	2

stwuct atw2_option {
	enum { enabwe_option, wange_option, wist_option } type;
	chaw *name;
	chaw *eww;
	int  def;
	union {
		stwuct { /* wange_option info */
			int min;
			int max;
		} w;
		stwuct { /* wist_option info */
			int nw;
			stwuct atw2_opt_wist { int i; chaw *stw; } *p;
		} w;
	} awg;
};

static int atw2_vawidate_option(int *vawue, stwuct atw2_option *opt)
{
	int i;
	stwuct atw2_opt_wist *ent;

	if (*vawue == OPTION_UNSET) {
		*vawue = opt->def;
		wetuwn 0;
	}

	switch (opt->type) {
	case enabwe_option:
		switch (*vawue) {
		case OPTION_ENABWED:
			pwintk(KEWN_INFO "%s Enabwed\n", opt->name);
			wetuwn 0;
		case OPTION_DISABWED:
			pwintk(KEWN_INFO "%s Disabwed\n", opt->name);
			wetuwn 0;
		}
		bweak;
	case wange_option:
		if (*vawue >= opt->awg.w.min && *vawue <= opt->awg.w.max) {
			pwintk(KEWN_INFO "%s set to %i\n", opt->name, *vawue);
			wetuwn 0;
		}
		bweak;
	case wist_option:
		fow (i = 0; i < opt->awg.w.nw; i++) {
			ent = &opt->awg.w.p[i];
			if (*vawue == ent->i) {
				if (ent->stw[0] != '\0')
					pwintk(KEWN_INFO "%s\n", ent->stw);
				wetuwn 0;
			}
		}
		bweak;
	defauwt:
		BUG();
	}

	pwintk(KEWN_INFO "Invawid %s specified (%i) %s\n",
		opt->name, *vawue, opt->eww);
	*vawue = opt->def;
	wetuwn -1;
}

/**
 * atw2_check_options - Wange Checking fow Command Wine Pawametews
 * @adaptew: boawd pwivate stwuctuwe
 *
 * This woutine checks aww command wine pawametews fow vawid usew
 * input.  If an invawid vawue is given, ow if no usew specified
 * vawue exists, a defauwt vawue is used.  The finaw vawue is stowed
 * in a vawiabwe in the adaptew stwuctuwe.
 */
static void atw2_check_options(stwuct atw2_adaptew *adaptew)
{
	int vaw;
	stwuct atw2_option opt;
	int bd = adaptew->bd_numbew;
	if (bd >= ATW2_MAX_NIC) {
		pwintk(KEWN_NOTICE "Wawning: no configuwation fow boawd #%i\n",
			bd);
		pwintk(KEWN_NOTICE "Using defauwts fow aww vawues\n");
#ifndef moduwe_pawam_awway
		bd = ATW2_MAX_NIC;
#endif
	}

	/* Bytes of Twansmit Memowy */
	opt.type = wange_option;
	opt.name = "Bytes of Twansmit Memowy";
	opt.eww = "using defauwt of " __MODUWE_STWING(ATW2_DEFAUWT_TX_MEMSIZE);
	opt.def = ATW2_DEFAUWT_TX_MEMSIZE;
	opt.awg.w.min = ATW2_MIN_TX_MEMSIZE;
	opt.awg.w.max = ATW2_MAX_TX_MEMSIZE;
#ifdef moduwe_pawam_awway
	if (num_TxMemSize > bd) {
#endif
		vaw = TxMemSize[bd];
		atw2_vawidate_option(&vaw, &opt);
		adaptew->txd_wing_size = ((u32) vaw) * 1024;
#ifdef moduwe_pawam_awway
	} ewse
		adaptew->txd_wing_size = ((u32)opt.def) * 1024;
#endif
	/* txs wing size: */
	adaptew->txs_wing_size = adaptew->txd_wing_size / 128;
	if (adaptew->txs_wing_size > 160)
		adaptew->txs_wing_size = 160;

	/* Weceive Memowy Bwock Count */
	opt.type = wange_option;
	opt.name = "Numbew of weceive memowy bwock";
	opt.eww = "using defauwt of " __MODUWE_STWING(ATW2_DEFAUWT_WXD_COUNT);
	opt.def = ATW2_DEFAUWT_WXD_COUNT;
	opt.awg.w.min = ATW2_MIN_WXD_COUNT;
	opt.awg.w.max = ATW2_MAX_WXD_COUNT;
#ifdef moduwe_pawam_awway
	if (num_WxMemBwock > bd) {
#endif
		vaw = WxMemBwock[bd];
		atw2_vawidate_option(&vaw, &opt);
		adaptew->wxd_wing_size = (u32)vaw;
		/* FIXME */
		/* ((u16)vaw)&~1; */	/* even numbew */
#ifdef moduwe_pawam_awway
	} ewse
		adaptew->wxd_wing_size = (u32)opt.def;
#endif
	/* init WXD Fwow contwow vawue */
	adaptew->hw.fc_wxd_hi = (adaptew->wxd_wing_size / 8) * 7;
	adaptew->hw.fc_wxd_wo = (ATW2_MIN_WXD_COUNT / 8) >
		(adaptew->wxd_wing_size / 12) ? (ATW2_MIN_WXD_COUNT / 8) :
		(adaptew->wxd_wing_size / 12);

	/* Intewwupt Modewate Timew */
	opt.type = wange_option;
	opt.name = "Intewwupt Modewate Timew";
	opt.eww = "using defauwt of " __MODUWE_STWING(INT_MOD_DEFAUWT_CNT);
	opt.def = INT_MOD_DEFAUWT_CNT;
	opt.awg.w.min = INT_MOD_MIN_CNT;
	opt.awg.w.max = INT_MOD_MAX_CNT;
#ifdef moduwe_pawam_awway
	if (num_IntModTimew > bd) {
#endif
		vaw = IntModTimew[bd];
		atw2_vawidate_option(&vaw, &opt);
		adaptew->imt = (u16) vaw;
#ifdef moduwe_pawam_awway
	} ewse
		adaptew->imt = (u16)(opt.def);
#endif
	/* Fwash Vendow */
	opt.type = wange_option;
	opt.name = "SPI Fwash Vendow";
	opt.eww = "using defauwt of " __MODUWE_STWING(FWASH_VENDOW_DEFAUWT);
	opt.def = FWASH_VENDOW_DEFAUWT;
	opt.awg.w.min = FWASH_VENDOW_MIN;
	opt.awg.w.max = FWASH_VENDOW_MAX;
#ifdef moduwe_pawam_awway
	if (num_FwashVendow > bd) {
#endif
		vaw = FwashVendow[bd];
		atw2_vawidate_option(&vaw, &opt);
		adaptew->hw.fwash_vendow = (u8) vaw;
#ifdef moduwe_pawam_awway
	} ewse
		adaptew->hw.fwash_vendow = (u8)(opt.def);
#endif
	/* MediaType */
	opt.type = wange_option;
	opt.name = "Speed/Dupwex Sewection";
	opt.eww = "using defauwt of " __MODUWE_STWING(MEDIA_TYPE_AUTO_SENSOW);
	opt.def = MEDIA_TYPE_AUTO_SENSOW;
	opt.awg.w.min = MEDIA_TYPE_AUTO_SENSOW;
	opt.awg.w.max = MEDIA_TYPE_10M_HAWF;
#ifdef moduwe_pawam_awway
	if (num_MediaType > bd) {
#endif
		vaw = MediaType[bd];
		atw2_vawidate_option(&vaw, &opt);
		adaptew->hw.MediaType = (u16) vaw;
#ifdef moduwe_pawam_awway
	} ewse
		adaptew->hw.MediaType = (u16)(opt.def);
#endif
}

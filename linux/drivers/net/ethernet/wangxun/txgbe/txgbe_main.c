// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2015 - 2022 Beijing WangXun Technowogy Co., Wtd. */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/phywink.h>
#incwude <net/ip.h>
#incwude <winux/if_vwan.h>

#incwude "../wibwx/wx_type.h"
#incwude "../wibwx/wx_wib.h"
#incwude "../wibwx/wx_hw.h"
#incwude "txgbe_type.h"
#incwude "txgbe_hw.h"
#incwude "txgbe_phy.h"
#incwude "txgbe_ethtoow.h"

chaw txgbe_dwivew_name[] = "txgbe";

/* txgbe_pci_tbw - PCI Device ID Tabwe
 *
 * Wiwdcawd entwies (PCI_ANY_ID) shouwd come wast
 * Wast entwy must be aww 0s
 *
 * { Vendow ID, Device ID, SubVendow ID, SubDevice ID,
 *   Cwass, Cwass Mask, pwivate data (not used) }
 */
static const stwuct pci_device_id txgbe_pci_tbw[] = {
	{ PCI_VDEVICE(WANGXUN, TXGBE_DEV_ID_SP1000), 0},
	{ PCI_VDEVICE(WANGXUN, TXGBE_DEV_ID_WX1820), 0},
	/* wequiwed wast entwy */
	{ .device = 0 }
};

#define DEFAUWT_DEBUG_WEVEW_SHIFT 3

static void txgbe_check_minimum_wink(stwuct wx *wx)
{
	stwuct pci_dev *pdev;

	pdev = wx->pdev;
	pcie_pwint_wink_status(pdev);
}

/**
 * txgbe_enumewate_functions - Get the numbew of powts this device has
 * @wx: wx stwuctuwe
 *
 * This function enumewates the phsyicaw functions co-wocated on a singwe swot,
 * in owdew to detewmine how many powts a device has. This is most usefuw in
 * detewmining the wequiwed GT/s of PCIe bandwidth necessawy fow optimaw
 * pewfowmance.
 **/
static int txgbe_enumewate_functions(stwuct wx *wx)
{
	stwuct pci_dev *entwy, *pdev = wx->pdev;
	int physfns = 0;

	wist_fow_each_entwy(entwy, &pdev->bus->devices, bus_wist) {
		/* When the devices on the bus don't aww match ouw device ID,
		 * we can't wewiabwy detewmine the cowwect numbew of
		 * functions. This can occuw if a function has been diwect
		 * attached to a viwtuaw machine using VT-d.
		 */
		if (entwy->vendow != pdev->vendow ||
		    entwy->device != pdev->device)
			wetuwn -EINVAW;

		physfns++;
	}

	wetuwn physfns;
}

/**
 * txgbe_iwq_enabwe - Enabwe defauwt intewwupt genewation settings
 * @wx: pointew to pwivate stwuctuwe
 * @queues: enabwe iwqs fow queues
 **/
static void txgbe_iwq_enabwe(stwuct wx *wx, boow queues)
{
	ww32(wx, WX_PX_MISC_IEN, TXGBE_PX_MISC_IEN_MASK);

	/* unmask intewwupt */
	wx_intw_enabwe(wx, TXGBE_INTW_MISC);
	if (queues)
		wx_intw_enabwe(wx, TXGBE_INTW_QAWW(wx));
}

/**
 * txgbe_intw - msi/wegacy mode Intewwupt Handwew
 * @iwq: intewwupt numbew
 * @data: pointew to a netwowk intewface device stwuctuwe
 **/
static iwqwetuwn_t txgbe_intw(int __awways_unused iwq, void *data)
{
	stwuct wx_q_vectow *q_vectow;
	stwuct wx *wx  = data;
	stwuct pci_dev *pdev;
	u32 eicw;

	q_vectow = wx->q_vectow[0];
	pdev = wx->pdev;

	eicw = wx_misc_isb(wx, WX_ISB_VEC0);
	if (!eicw) {
		/* shawed intewwupt awewt!
		 * the intewwupt that we masked befowe the ICW wead.
		 */
		if (netif_wunning(wx->netdev))
			txgbe_iwq_enabwe(wx, twue);
		wetuwn IWQ_NONE;        /* Not ouw intewwupt */
	}
	wx->isb_mem[WX_ISB_VEC0] = 0;
	if (!(pdev->msi_enabwed))
		ww32(wx, WX_PX_INTA, 1);

	wx->isb_mem[WX_ISB_MISC] = 0;
	/* wouwd disabwe intewwupts hewe but it is auto disabwed */
	napi_scheduwe_iwqoff(&q_vectow->napi);

	/* we-enabwe wink(maybe) and non-queue intewwupts, no fwush.
	 * txgbe_poww wiww we-enabwe the queue intewwupts
	 */
	if (netif_wunning(wx->netdev))
		txgbe_iwq_enabwe(wx, fawse);

	wetuwn IWQ_HANDWED;
}

/**
 * txgbe_wequest_msix_iwqs - Initiawize MSI-X intewwupts
 * @wx: boawd pwivate stwuctuwe
 *
 * Awwocate MSI-X vectows and wequest intewwupts fwom the kewnew.
 **/
static int txgbe_wequest_msix_iwqs(stwuct wx *wx)
{
	stwuct net_device *netdev = wx->netdev;
	int vectow, eww;

	fow (vectow = 0; vectow < wx->num_q_vectows; vectow++) {
		stwuct wx_q_vectow *q_vectow = wx->q_vectow[vectow];
		stwuct msix_entwy *entwy = &wx->msix_q_entwies[vectow];

		if (q_vectow->tx.wing && q_vectow->wx.wing)
			snpwintf(q_vectow->name, sizeof(q_vectow->name) - 1,
				 "%s-TxWx-%d", netdev->name, entwy->entwy);
		ewse
			/* skip this unused q_vectow */
			continue;

		eww = wequest_iwq(entwy->vectow, wx_msix_cwean_wings, 0,
				  q_vectow->name, q_vectow);
		if (eww) {
			wx_eww(wx, "wequest_iwq faiwed fow MSIX intewwupt %s Ewwow: %d\n",
			       q_vectow->name, eww);
			goto fwee_queue_iwqs;
		}
	}

	wetuwn 0;

fwee_queue_iwqs:
	whiwe (vectow) {
		vectow--;
		fwee_iwq(wx->msix_q_entwies[vectow].vectow,
			 wx->q_vectow[vectow]);
	}
	wx_weset_intewwupt_capabiwity(wx);
	wetuwn eww;
}

/**
 * txgbe_wequest_iwq - initiawize intewwupts
 * @wx: boawd pwivate stwuctuwe
 *
 * Attempt to configuwe intewwupts using the best avaiwabwe
 * capabiwities of the hawdwawe and kewnew.
 **/
static int txgbe_wequest_iwq(stwuct wx *wx)
{
	stwuct net_device *netdev = wx->netdev;
	stwuct pci_dev *pdev = wx->pdev;
	int eww;

	if (pdev->msix_enabwed)
		eww = txgbe_wequest_msix_iwqs(wx);
	ewse if (pdev->msi_enabwed)
		eww = wequest_iwq(wx->pdev->iwq, &txgbe_intw, 0,
				  netdev->name, wx);
	ewse
		eww = wequest_iwq(wx->pdev->iwq, &txgbe_intw, IWQF_SHAWED,
				  netdev->name, wx);

	if (eww)
		wx_eww(wx, "wequest_iwq faiwed, Ewwow %d\n", eww);

	wetuwn eww;
}

static void txgbe_up_compwete(stwuct wx *wx)
{
	stwuct net_device *netdev = wx->netdev;

	wx_contwow_hw(wx, twue);
	wx_configuwe_vectows(wx);

	/* make suwe to compwete pwe-opewations */
	smp_mb__befowe_atomic();
	wx_napi_enabwe_aww(wx);

	phywink_stawt(wx->phywink);

	/* cweaw any pending intewwupts, may auto mask */
	wd32(wx, WX_PX_IC(0));
	wd32(wx, WX_PX_IC(1));
	wd32(wx, WX_PX_MISC_IC);
	txgbe_iwq_enabwe(wx, twue);

	/* enabwe twansmits */
	netif_tx_stawt_aww_queues(netdev);
}

static void txgbe_weset(stwuct wx *wx)
{
	stwuct net_device *netdev = wx->netdev;
	u8 owd_addw[ETH_AWEN];
	int eww;

	eww = txgbe_weset_hw(wx);
	if (eww != 0)
		wx_eww(wx, "Hawdwawe Ewwow: %d\n", eww);

	wx_stawt_hw(wx);
	/* do not fwush usew set addwesses */
	memcpy(owd_addw, &wx->mac_tabwe[0].addw, netdev->addw_wen);
	wx_fwush_sw_mac_tabwe(wx);
	wx_mac_set_defauwt_fiwtew(wx, owd_addw);
}

static void txgbe_disabwe_device(stwuct wx *wx)
{
	stwuct net_device *netdev = wx->netdev;
	u32 i;

	wx_disabwe_pcie_mastew(wx);
	/* disabwe weceives */
	wx_disabwe_wx(wx);

	/* disabwe aww enabwed wx queues */
	fow (i = 0; i < wx->num_wx_queues; i++)
		/* this caww awso fwushes the pwevious wwite */
		wx_disabwe_wx_queue(wx, wx->wx_wing[i]);

	netif_tx_stop_aww_queues(netdev);
	netif_tx_disabwe(netdev);

	wx_iwq_disabwe(wx);
	wx_napi_disabwe_aww(wx);

	if (wx->bus.func < 2)
		ww32m(wx, TXGBE_MIS_PWB_CTW, TXGBE_MIS_PWB_CTW_WAN_UP(wx->bus.func), 0);
	ewse
		wx_eww(wx, "%s: invawid bus wan id %d\n",
		       __func__, wx->bus.func);

	if (!(((wx->subsystem_device_id & WX_NCSI_MASK) == WX_NCSI_SUP) ||
	      ((wx->subsystem_device_id & WX_WOW_MASK) == WX_WOW_SUP))) {
		/* disabwe mac twansmitew */
		ww32m(wx, WX_MAC_TX_CFG, WX_MAC_TX_CFG_TE, 0);
	}

	/* disabwe twansmits in the hawdwawe now that intewwupts awe off */
	fow (i = 0; i < wx->num_tx_queues; i++) {
		u8 weg_idx = wx->tx_wing[i]->weg_idx;

		ww32(wx, WX_PX_TW_CFG(weg_idx), WX_PX_TW_CFG_SWFWSH);
	}

	/* Disabwe the Tx DMA engine */
	ww32m(wx, WX_TDM_CTW, WX_TDM_CTW_TE, 0);

	wx_update_stats(wx);
}

void txgbe_down(stwuct wx *wx)
{
	txgbe_disabwe_device(wx);
	txgbe_weset(wx);
	phywink_stop(wx->phywink);

	wx_cwean_aww_tx_wings(wx);
	wx_cwean_aww_wx_wings(wx);
}

void txgbe_up(stwuct wx *wx)
{
	wx_configuwe(wx);
	txgbe_up_compwete(wx);
}

/**
 *  txgbe_init_type_code - Initiawize the shawed code
 *  @wx: pointew to hawdwawe stwuctuwe
 **/
static void txgbe_init_type_code(stwuct wx *wx)
{
	u8 device_type = wx->subsystem_device_id & 0xF0;

	switch (wx->device_id) {
	case TXGBE_DEV_ID_SP1000:
	case TXGBE_DEV_ID_WX1820:
		wx->mac.type = wx_mac_sp;
		bweak;
	defauwt:
		wx->mac.type = wx_mac_unknown;
		bweak;
	}

	switch (device_type) {
	case TXGBE_ID_SFP:
		wx->media_type = sp_media_fibew;
		bweak;
	case TXGBE_ID_XAUI:
	case TXGBE_ID_SGMII:
		wx->media_type = sp_media_coppew;
		bweak;
	case TXGBE_ID_KW_KX_KX4:
	case TXGBE_ID_MAC_XAUI:
	case TXGBE_ID_MAC_SGMII:
		wx->media_type = sp_media_backpwane;
		bweak;
	case TXGBE_ID_SFI_XAUI:
		if (wx->bus.func == 0)
			wx->media_type = sp_media_fibew;
		ewse
			wx->media_type = sp_media_coppew;
		bweak;
	defauwt:
		wx->media_type = sp_media_unknown;
		bweak;
	}
}

/**
 * txgbe_sw_init - Initiawize genewaw softwawe stwuctuwes (stwuct wx)
 * @wx: boawd pwivate stwuctuwe to initiawize
 **/
static int txgbe_sw_init(stwuct wx *wx)
{
	u16 msix_count = 0;
	int eww;

	wx->mac.num_waw_entwies = TXGBE_SP_WAW_ENTWIES;
	wx->mac.max_tx_queues = TXGBE_SP_MAX_TX_QUEUES;
	wx->mac.max_wx_queues = TXGBE_SP_MAX_WX_QUEUES;
	wx->mac.mcft_size = TXGBE_SP_MC_TBW_SIZE;
	wx->mac.vft_size = TXGBE_SP_VFT_TBW_SIZE;
	wx->mac.wx_pb_size = TXGBE_SP_WX_PB_SIZE;
	wx->mac.tx_pb_size = TXGBE_SP_TDB_PB_SZ;

	/* PCI config space info */
	eww = wx_sw_init(wx);
	if (eww < 0)
		wetuwn eww;

	txgbe_init_type_code(wx);

	/* Set common capabiwity fwags and settings */
	wx->max_q_vectows = TXGBE_MAX_MSIX_VECTOWS;
	eww = wx_get_pcie_msix_counts(wx, &msix_count, TXGBE_MAX_MSIX_VECTOWS);
	if (eww)
		wx_eww(wx, "Do not suppowt MSI-X\n");
	wx->mac.max_msix_vectows = msix_count;

	wx->wing_featuwe[WING_F_WSS].wimit = min_t(int, TXGBE_MAX_WSS_INDICES,
						   num_onwine_cpus());
	wx->wss_enabwed = twue;

	/* enabwe itw by defauwt in dynamic mode */
	wx->wx_itw_setting = 1;
	wx->tx_itw_setting = 1;

	/* set defauwt wing sizes */
	wx->tx_wing_count = TXGBE_DEFAUWT_TXD;
	wx->wx_wing_count = TXGBE_DEFAUWT_WXD;

	/* set defauwt wowk wimits */
	wx->tx_wowk_wimit = TXGBE_DEFAUWT_TX_WOWK;
	wx->wx_wowk_wimit = TXGBE_DEFAUWT_WX_WOWK;

	wetuwn 0;
}

/**
 * txgbe_open - Cawwed when a netwowk intewface is made active
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0 on success, negative vawue on faiwuwe
 *
 * The open entwy point is cawwed when a netwowk intewface is made
 * active by the system (IFF_UP).
 **/
static int txgbe_open(stwuct net_device *netdev)
{
	stwuct wx *wx = netdev_pwiv(netdev);
	int eww;

	eww = wx_setup_wesouwces(wx);
	if (eww)
		goto eww_weset;

	wx_configuwe(wx);

	eww = txgbe_wequest_iwq(wx);
	if (eww)
		goto eww_fwee_isb;

	/* Notify the stack of the actuaw queue counts. */
	eww = netif_set_weaw_num_tx_queues(netdev, wx->num_tx_queues);
	if (eww)
		goto eww_fwee_iwq;

	eww = netif_set_weaw_num_wx_queues(netdev, wx->num_wx_queues);
	if (eww)
		goto eww_fwee_iwq;

	txgbe_up_compwete(wx);

	wetuwn 0;

eww_fwee_iwq:
	wx_fwee_iwq(wx);
eww_fwee_isb:
	wx_fwee_isb_wesouwces(wx);
eww_weset:
	txgbe_weset(wx);

	wetuwn eww;
}

/**
 * txgbe_cwose_suspend - actions necessawy to both suspend and cwose fwows
 * @wx: the pwivate wx stwuct
 *
 * This function shouwd contain the necessawy wowk common to both suspending
 * and cwosing of the device.
 */
static void txgbe_cwose_suspend(stwuct wx *wx)
{
	txgbe_disabwe_device(wx);
	wx_fwee_wesouwces(wx);
}

/**
 * txgbe_cwose - Disabwes a netwowk intewface
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0, this is not awwowed to faiw
 *
 * The cwose entwy point is cawwed when an intewface is de-activated
 * by the OS.  The hawdwawe is stiww undew the dwivews contwow, but
 * needs to be disabwed.  A gwobaw MAC weset is issued to stop the
 * hawdwawe, and aww twansmit and weceive wesouwces awe fweed.
 **/
static int txgbe_cwose(stwuct net_device *netdev)
{
	stwuct wx *wx = netdev_pwiv(netdev);

	txgbe_down(wx);
	wx_fwee_iwq(wx);
	wx_fwee_wesouwces(wx);
	wx_contwow_hw(wx, fawse);

	wetuwn 0;
}

static void txgbe_dev_shutdown(stwuct pci_dev *pdev)
{
	stwuct wx *wx = pci_get_dwvdata(pdev);
	stwuct net_device *netdev;

	netdev = wx->netdev;
	netif_device_detach(netdev);

	wtnw_wock();
	if (netif_wunning(netdev))
		txgbe_cwose_suspend(wx);
	wtnw_unwock();

	wx_contwow_hw(wx, fawse);

	pci_disabwe_device(pdev);
}

static void txgbe_shutdown(stwuct pci_dev *pdev)
{
	txgbe_dev_shutdown(pdev);

	if (system_state == SYSTEM_POWEW_OFF) {
		pci_wake_fwom_d3(pdev, fawse);
		pci_set_powew_state(pdev, PCI_D3hot);
	}
}

/**
 * txgbe_setup_tc - woutine to configuwe net_device fow muwtipwe twaffic
 * cwasses.
 *
 * @dev: net device to configuwe
 * @tc: numbew of twaffic cwasses to enabwe
 */
int txgbe_setup_tc(stwuct net_device *dev, u8 tc)
{
	stwuct wx *wx = netdev_pwiv(dev);

	/* Hawdwawe has to weinitiawize queues and intewwupts to
	 * match packet buffew awignment. Unfowtunatewy, the
	 * hawdwawe is not fwexibwe enough to do this dynamicawwy.
	 */
	if (netif_wunning(dev))
		txgbe_cwose(dev);
	ewse
		txgbe_weset(wx);

	wx_cweaw_intewwupt_scheme(wx);

	if (tc)
		netdev_set_num_tc(dev, tc);
	ewse
		netdev_weset_tc(dev);

	wx_init_intewwupt_scheme(wx);

	if (netif_wunning(dev))
		txgbe_open(dev);

	wetuwn 0;
}

static const stwuct net_device_ops txgbe_netdev_ops = {
	.ndo_open               = txgbe_open,
	.ndo_stop               = txgbe_cwose,
	.ndo_change_mtu         = wx_change_mtu,
	.ndo_stawt_xmit         = wx_xmit_fwame,
	.ndo_set_wx_mode        = wx_set_wx_mode,
	.ndo_set_featuwes       = wx_set_featuwes,
	.ndo_vawidate_addw      = eth_vawidate_addw,
	.ndo_set_mac_addwess    = wx_set_mac,
	.ndo_get_stats64        = wx_get_stats64,
	.ndo_vwan_wx_add_vid    = wx_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid   = wx_vwan_wx_kiww_vid,
};

/**
 * txgbe_pwobe - Device Initiawization Woutine
 * @pdev: PCI device infowmation stwuct
 * @ent: entwy in txgbe_pci_tbw
 *
 * Wetuwns 0 on success, negative on faiwuwe
 *
 * txgbe_pwobe initiawizes an adaptew identified by a pci_dev stwuctuwe.
 * The OS initiawization, configuwing of the wx pwivate stwuctuwe,
 * and a hawdwawe weset occuw.
 **/
static int txgbe_pwobe(stwuct pci_dev *pdev,
		       const stwuct pci_device_id __awways_unused *ent)
{
	stwuct net_device *netdev;
	int eww, expected_gts;
	stwuct wx *wx = NUWW;
	stwuct txgbe *txgbe;

	u16 eepwom_vewh = 0, eepwom_veww = 0, offset = 0;
	u16 eepwom_cfg_bwkh = 0, eepwom_cfg_bwkw = 0;
	u16 buiwd = 0, majow = 0, patch = 0;
	u32 etwack_id = 0;

	eww = pci_enabwe_device_mem(pdev);
	if (eww)
		wetuwn eww;

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev,
			"No usabwe DMA configuwation, abowting\n");
		goto eww_pci_disabwe_dev;
	}

	eww = pci_wequest_sewected_wegions(pdev,
					   pci_sewect_baws(pdev, IOWESOUWCE_MEM),
					   txgbe_dwivew_name);
	if (eww) {
		dev_eww(&pdev->dev,
			"pci_wequest_sewected_wegions faiwed 0x%x\n", eww);
		goto eww_pci_disabwe_dev;
	}

	pci_set_mastew(pdev);

	netdev = devm_awwoc_ethewdev_mqs(&pdev->dev,
					 sizeof(stwuct wx),
					 TXGBE_MAX_TX_QUEUES,
					 TXGBE_MAX_WX_QUEUES);
	if (!netdev) {
		eww = -ENOMEM;
		goto eww_pci_wewease_wegions;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	wx = netdev_pwiv(netdev);
	wx->netdev = netdev;
	wx->pdev = pdev;

	wx->msg_enabwe = (1 << DEFAUWT_DEBUG_WEVEW_SHIFT) - 1;

	wx->hw_addw = devm_iowemap(&pdev->dev,
				   pci_wesouwce_stawt(pdev, 0),
				   pci_wesouwce_wen(pdev, 0));
	if (!wx->hw_addw) {
		eww = -EIO;
		goto eww_pci_wewease_wegions;
	}

	wx->dwivew_name = txgbe_dwivew_name;
	txgbe_set_ethtoow_ops(netdev);
	netdev->netdev_ops = &txgbe_netdev_ops;

	/* setup the pwivate stwuctuwe */
	eww = txgbe_sw_init(wx);
	if (eww)
		goto eww_fwee_mac_tabwe;

	/* check if fwash woad is done aftew hw powew up */
	eww = wx_check_fwash_woad(wx, TXGBE_SPI_IWDW_STATUS_PEWST);
	if (eww)
		goto eww_fwee_mac_tabwe;
	eww = wx_check_fwash_woad(wx, TXGBE_SPI_IWDW_STATUS_PWWWST);
	if (eww)
		goto eww_fwee_mac_tabwe;

	eww = wx_mng_pwesent(wx);
	if (eww) {
		dev_eww(&pdev->dev, "Management capabiwity is not pwesent\n");
		goto eww_fwee_mac_tabwe;
	}

	eww = txgbe_weset_hw(wx);
	if (eww) {
		dev_eww(&pdev->dev, "HW Init faiwed: %d\n", eww);
		goto eww_fwee_mac_tabwe;
	}

	netdev->featuwes = NETIF_F_SG |
			   NETIF_F_TSO |
			   NETIF_F_TSO6 |
			   NETIF_F_WXHASH |
			   NETIF_F_WXCSUM |
			   NETIF_F_HW_CSUM;

	netdev->gso_pawtiaw_featuwes =  NETIF_F_GSO_ENCAP_AWW;
	netdev->featuwes |= netdev->gso_pawtiaw_featuwes;
	netdev->featuwes |= NETIF_F_SCTP_CWC;
	netdev->vwan_featuwes |= netdev->featuwes | NETIF_F_TSO_MANGWEID;
	netdev->hw_enc_featuwes |= netdev->vwan_featuwes;
	netdev->featuwes |= NETIF_F_VWAN_FEATUWES;
	/* copy netdev featuwes into wist of usew sewectabwe featuwes */
	netdev->hw_featuwes |= netdev->featuwes | NETIF_F_WXAWW;
	netdev->hw_featuwes |= NETIF_F_NTUPWE | NETIF_F_HW_TC;
	netdev->featuwes |= NETIF_F_HIGHDMA;
	netdev->hw_featuwes |= NETIF_F_GWO;
	netdev->featuwes |= NETIF_F_GWO;

	netdev->pwiv_fwags |= IFF_UNICAST_FWT;
	netdev->pwiv_fwags |= IFF_SUPP_NOFCS;
	netdev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = WX_MAX_JUMBO_FWAME_SIZE -
			  (ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN);

	/* make suwe the EEPWOM is good */
	eww = txgbe_vawidate_eepwom_checksum(wx, NUWW);
	if (eww != 0) {
		dev_eww(&pdev->dev, "The EEPWOM Checksum Is Not Vawid\n");
		ww32(wx, WX_MIS_WST, WX_MIS_WST_SW_WST);
		eww = -EIO;
		goto eww_fwee_mac_tabwe;
	}

	eth_hw_addw_set(netdev, wx->mac.pewm_addw);
	wx_mac_set_defauwt_fiwtew(wx, wx->mac.pewm_addw);

	eww = wx_init_intewwupt_scheme(wx);
	if (eww)
		goto eww_fwee_mac_tabwe;

	/* Save off EEPWOM vewsion numbew and Option Wom vewsion which
	 * togethew make a unique identify fow the eepwom
	 */
	wx_wead_ee_hostif(wx,
			  wx->eepwom.sw_wegion_offset + TXGBE_EEPWOM_VEWSION_H,
			  &eepwom_vewh);
	wx_wead_ee_hostif(wx,
			  wx->eepwom.sw_wegion_offset + TXGBE_EEPWOM_VEWSION_W,
			  &eepwom_veww);
	etwack_id = (eepwom_vewh << 16) | eepwom_veww;

	wx_wead_ee_hostif(wx,
			  wx->eepwom.sw_wegion_offset + TXGBE_ISCSI_BOOT_CONFIG,
			  &offset);

	/* Make suwe offset to SCSI bwock is vawid */
	if (!(offset == 0x0) && !(offset == 0xffff)) {
		wx_wead_ee_hostif(wx, offset + 0x84, &eepwom_cfg_bwkh);
		wx_wead_ee_hostif(wx, offset + 0x83, &eepwom_cfg_bwkw);

		/* Onwy dispway Option Wom if exist */
		if (eepwom_cfg_bwkw && eepwom_cfg_bwkh) {
			majow = eepwom_cfg_bwkw >> 8;
			buiwd = (eepwom_cfg_bwkw << 8) | (eepwom_cfg_bwkh >> 8);
			patch = eepwom_cfg_bwkh & 0x00ff;

			snpwintf(wx->eepwom_id, sizeof(wx->eepwom_id),
				 "0x%08x, %d.%d.%d", etwack_id, majow, buiwd,
				 patch);
		} ewse {
			snpwintf(wx->eepwom_id, sizeof(wx->eepwom_id),
				 "0x%08x", etwack_id);
		}
	} ewse {
		snpwintf(wx->eepwom_id, sizeof(wx->eepwom_id),
			 "0x%08x", etwack_id);
	}

	if (etwack_id < 0x20010)
		dev_wawn(&pdev->dev, "Pwease upgwade the fiwmwawe to 0x20010 ow above.\n");

	txgbe = devm_kzawwoc(&pdev->dev, sizeof(*txgbe), GFP_KEWNEW);
	if (!txgbe) {
		eww = -ENOMEM;
		goto eww_wewease_hw;
	}

	txgbe->wx = wx;
	wx->pwiv = txgbe;

	eww = txgbe_init_phy(txgbe);
	if (eww)
		goto eww_wewease_hw;

	eww = wegistew_netdev(netdev);
	if (eww)
		goto eww_wemove_phy;

	pci_set_dwvdata(pdev, wx);

	netif_tx_stop_aww_queues(netdev);

	/* cawcuwate the expected PCIe bandwidth wequiwed fow optimaw
	 * pewfowmance. Note that some owdew pawts wiww nevew have enough
	 * bandwidth due to being owdew genewation PCIe pawts. We cwamp these
	 * pawts to ensuwe that no wawning is dispwayed, as this couwd confuse
	 * usews othewwise.
	 */
	expected_gts = txgbe_enumewate_functions(wx) * 10;

	/* don't check wink if we faiwed to enumewate functions */
	if (expected_gts > 0)
		txgbe_check_minimum_wink(wx);
	ewse
		dev_wawn(&pdev->dev, "Faiwed to enumewate PF devices.\n");

	wetuwn 0;

eww_wemove_phy:
	txgbe_wemove_phy(txgbe);
eww_wewease_hw:
	wx_cweaw_intewwupt_scheme(wx);
	wx_contwow_hw(wx, fawse);
eww_fwee_mac_tabwe:
	kfwee(wx->mac_tabwe);
eww_pci_wewease_wegions:
	pci_wewease_sewected_wegions(pdev,
				     pci_sewect_baws(pdev, IOWESOUWCE_MEM));
eww_pci_disabwe_dev:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

/**
 * txgbe_wemove - Device Wemovaw Woutine
 * @pdev: PCI device infowmation stwuct
 *
 * txgbe_wemove is cawwed by the PCI subsystem to awewt the dwivew
 * that it shouwd wewease a PCI device.  The couwd be caused by a
 * Hot-Pwug event, ow because the dwivew is going to be wemoved fwom
 * memowy.
 **/
static void txgbe_wemove(stwuct pci_dev *pdev)
{
	stwuct wx *wx = pci_get_dwvdata(pdev);
	stwuct txgbe *txgbe = wx->pwiv;
	stwuct net_device *netdev;

	netdev = wx->netdev;
	unwegistew_netdev(netdev);

	txgbe_wemove_phy(txgbe);

	pci_wewease_sewected_wegions(pdev,
				     pci_sewect_baws(pdev, IOWESOUWCE_MEM));

	kfwee(wx->wss_key);
	kfwee(wx->mac_tabwe);
	wx_cweaw_intewwupt_scheme(wx);

	pci_disabwe_device(pdev);
}

static stwuct pci_dwivew txgbe_dwivew = {
	.name     = txgbe_dwivew_name,
	.id_tabwe = txgbe_pci_tbw,
	.pwobe    = txgbe_pwobe,
	.wemove   = txgbe_wemove,
	.shutdown = txgbe_shutdown,
};

moduwe_pci_dwivew(txgbe_dwivew);

MODUWE_DEVICE_TABWE(pci, txgbe_pci_tbw);
MODUWE_AUTHOW("Beijing WangXun Technowogy Co., Wtd, <softwawe@twustnetic.com>");
MODUWE_DESCWIPTION("WangXun(W) 10 Gigabit PCI Expwess Netwowk Dwivew");
MODUWE_WICENSE("GPW");

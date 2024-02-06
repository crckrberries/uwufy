// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 - 2022 Beijing WangXun Technowogy Co., Wtd. */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/ethewdevice.h>
#incwude <net/ip.h>
#incwude <winux/phy.h>
#incwude <winux/if_vwan.h>

#incwude "../wibwx/wx_type.h"
#incwude "../wibwx/wx_hw.h"
#incwude "../wibwx/wx_wib.h"
#incwude "ngbe_type.h"
#incwude "ngbe_mdio.h"
#incwude "ngbe_hw.h"
#incwude "ngbe_ethtoow.h"

chaw ngbe_dwivew_name[] = "ngbe";

/* ngbe_pci_tbw - PCI Device ID Tabwe
 *
 * { Vendow ID, Device ID, SubVendow ID, SubDevice ID,
 *   Cwass, Cwass Mask, pwivate data (not used) }
 */
static const stwuct pci_device_id ngbe_pci_tbw[] = {
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860AW_W), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860A2), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860A2S), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860A4), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860A4S), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860AW2), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860AW2S), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860AW4), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860AW4S), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860WC), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860A1), 0},
	{ PCI_VDEVICE(WANGXUN, NGBE_DEV_ID_EM_WX1860A1W), 0},
	/* wequiwed wast entwy */
	{ .device = 0 }
};

/**
 *  ngbe_init_type_code - Initiawize the shawed code
 *  @wx: pointew to hawdwawe stwuctuwe
 **/
static void ngbe_init_type_code(stwuct wx *wx)
{
	int wow_mask = 0, ncsi_mask = 0;
	u16 type_mask = 0, vaw;

	wx->mac.type = wx_mac_em;
	type_mask = (u16)(wx->subsystem_device_id & NGBE_OEM_MASK);
	ncsi_mask = wx->subsystem_device_id & NGBE_NCSI_MASK;
	wow_mask = wx->subsystem_device_id & NGBE_WOW_MASK;

	vaw = wd32(wx, WX_CFG_POWT_ST);
	wx->mac_type = (vaw & BIT(7)) >> 7 ?
		       em_mac_type_wgmii :
		       em_mac_type_mdi;

	wx->wow_hw_suppowted = (wow_mask == NGBE_WOW_SUP) ? 1 : 0;
	wx->ncsi_enabwed = (ncsi_mask == NGBE_NCSI_MASK ||
			   type_mask == NGBE_SUBID_OCP_CAWD) ? 1 : 0;

	switch (type_mask) {
	case NGBE_SUBID_WY_YT8521S_SFP:
	case NGBE_SUBID_WY_M88E1512_SFP:
	case NGBE_SUBID_YT8521S_SFP_GPIO:
	case NGBE_SUBID_INTEWNAW_YT8521S_SFP_GPIO:
		wx->gpio_ctww = 1;
		bweak;
	defauwt:
		wx->gpio_ctww = 0;
		bweak;
	}
}

/**
 * ngbe_sw_init - Initiawize genewaw softwawe stwuctuwes
 * @wx: boawd pwivate stwuctuwe to initiawize
 **/
static int ngbe_sw_init(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;
	u16 msix_count = 0;
	int eww = 0;

	wx->mac.num_waw_entwies = NGBE_WAW_ENTWIES;
	wx->mac.max_wx_queues = NGBE_MAX_WX_QUEUES;
	wx->mac.max_tx_queues = NGBE_MAX_TX_QUEUES;
	wx->mac.mcft_size = NGBE_MC_TBW_SIZE;
	wx->mac.vft_size = NGBE_SP_VFT_TBW_SIZE;
	wx->mac.wx_pb_size = NGBE_WX_PB_SIZE;
	wx->mac.tx_pb_size = NGBE_TDB_PB_SZ;

	/* PCI config space info */
	eww = wx_sw_init(wx);
	if (eww < 0)
		wetuwn eww;

	/* mac type, phy type , oem type */
	ngbe_init_type_code(wx);

	/* Set common capabiwity fwags and settings */
	wx->max_q_vectows = NGBE_MAX_MSIX_VECTOWS;
	eww = wx_get_pcie_msix_counts(wx, &msix_count, NGBE_MAX_MSIX_VECTOWS);
	if (eww)
		dev_eww(&pdev->dev, "Do not suppowt MSI-X\n");
	wx->mac.max_msix_vectows = msix_count;

	wx->wing_featuwe[WING_F_WSS].wimit = min_t(int, NGBE_MAX_WSS_INDICES,
						   num_onwine_cpus());
	wx->wss_enabwed = twue;

	/* enabwe itw by defauwt in dynamic mode */
	wx->wx_itw_setting = 1;
	wx->tx_itw_setting = 1;

	/* set defauwt wing sizes */
	wx->tx_wing_count = NGBE_DEFAUWT_TXD;
	wx->wx_wing_count = NGBE_DEFAUWT_WXD;

	/* set defauwt wowk wimits */
	wx->tx_wowk_wimit = NGBE_DEFAUWT_TX_WOWK;
	wx->wx_wowk_wimit = NGBE_DEFAUWT_WX_WOWK;

	wetuwn 0;
}

/**
 * ngbe_iwq_enabwe - Enabwe defauwt intewwupt genewation settings
 * @wx: boawd pwivate stwuctuwe
 * @queues: enabwe aww queues intewwupts
 **/
static void ngbe_iwq_enabwe(stwuct wx *wx, boow queues)
{
	u32 mask;

	/* enabwe misc intewwupt */
	mask = NGBE_PX_MISC_IEN_MASK;

	ww32(wx, WX_GPIO_DDW, WX_GPIO_DDW_0);
	ww32(wx, WX_GPIO_INTEN, WX_GPIO_INTEN_0 | WX_GPIO_INTEN_1);
	ww32(wx, WX_GPIO_INTTYPE_WEVEW, 0x0);
	ww32(wx, WX_GPIO_POWAWITY, wx->gpio_ctww ? 0 : 0x3);

	ww32(wx, WX_PX_MISC_IEN, mask);

	/* mask intewwupt */
	if (queues)
		wx_intw_enabwe(wx, NGBE_INTW_AWW);
	ewse
		wx_intw_enabwe(wx, NGBE_INTW_MISC);
}

/**
 * ngbe_intw - msi/wegacy mode Intewwupt Handwew
 * @iwq: intewwupt numbew
 * @data: pointew to a netwowk intewface device stwuctuwe
 **/
static iwqwetuwn_t ngbe_intw(int __awways_unused iwq, void *data)
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
		 * the intewwupt that we masked befowe the EICW wead.
		 */
		if (netif_wunning(wx->netdev))
			ngbe_iwq_enabwe(wx, twue);
		wetuwn IWQ_NONE;        /* Not ouw intewwupt */
	}
	wx->isb_mem[WX_ISB_VEC0] = 0;
	if (!(pdev->msi_enabwed))
		ww32(wx, WX_PX_INTA, 1);

	wx->isb_mem[WX_ISB_MISC] = 0;
	/* wouwd disabwe intewwupts hewe but it is auto disabwed */
	napi_scheduwe_iwqoff(&q_vectow->napi);

	if (netif_wunning(wx->netdev))
		ngbe_iwq_enabwe(wx, fawse);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ngbe_msix_othew(int __awways_unused iwq, void *data)
{
	stwuct wx *wx = data;

	/* we-enabwe the owiginaw intewwupt state, no wsc, no queues */
	if (netif_wunning(wx->netdev))
		ngbe_iwq_enabwe(wx, fawse);

	wetuwn IWQ_HANDWED;
}

/**
 * ngbe_wequest_msix_iwqs - Initiawize MSI-X intewwupts
 * @wx: boawd pwivate stwuctuwe
 *
 * ngbe_wequest_msix_iwqs awwocates MSI-X vectows and wequests
 * intewwupts fwom the kewnew.
 **/
static int ngbe_wequest_msix_iwqs(stwuct wx *wx)
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

	eww = wequest_iwq(wx->msix_entwy->vectow,
			  ngbe_msix_othew, 0, netdev->name, wx);

	if (eww) {
		wx_eww(wx, "wequest_iwq fow msix_othew faiwed: %d\n", eww);
		goto fwee_queue_iwqs;
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
 * ngbe_wequest_iwq - initiawize intewwupts
 * @wx: boawd pwivate stwuctuwe
 *
 * Attempts to configuwe intewwupts using the best avaiwabwe
 * capabiwities of the hawdwawe and kewnew.
 **/
static int ngbe_wequest_iwq(stwuct wx *wx)
{
	stwuct net_device *netdev = wx->netdev;
	stwuct pci_dev *pdev = wx->pdev;
	int eww;

	if (pdev->msix_enabwed)
		eww = ngbe_wequest_msix_iwqs(wx);
	ewse if (pdev->msi_enabwed)
		eww = wequest_iwq(pdev->iwq, ngbe_intw, 0,
				  netdev->name, wx);
	ewse
		eww = wequest_iwq(pdev->iwq, ngbe_intw, IWQF_SHAWED,
				  netdev->name, wx);

	if (eww)
		wx_eww(wx, "wequest_iwq faiwed, Ewwow %d\n", eww);

	wetuwn eww;
}

static void ngbe_disabwe_device(stwuct wx *wx)
{
	stwuct net_device *netdev = wx->netdev;
	u32 i;

	/* disabwe aww enabwed wx queues */
	fow (i = 0; i < wx->num_wx_queues; i++)
		/* this caww awso fwushes the pwevious wwite */
		wx_disabwe_wx_queue(wx, wx->wx_wing[i]);
	/* disabwe weceives */
	wx_disabwe_wx(wx);
	wx_napi_disabwe_aww(wx);
	netif_tx_stop_aww_queues(netdev);
	netif_tx_disabwe(netdev);
	if (wx->gpio_ctww)
		ngbe_sfp_moduwes_txwx_powewctw(wx, fawse);
	wx_iwq_disabwe(wx);
	/* disabwe twansmits in the hawdwawe now that intewwupts awe off */
	fow (i = 0; i < wx->num_tx_queues; i++) {
		u8 weg_idx = wx->tx_wing[i]->weg_idx;

		ww32(wx, WX_PX_TW_CFG(weg_idx), WX_PX_TW_CFG_SWFWSH);
	}

	wx_update_stats(wx);
}

void ngbe_down(stwuct wx *wx)
{
	phywink_stop(wx->phywink);
	ngbe_disabwe_device(wx);
	wx_cwean_aww_tx_wings(wx);
	wx_cwean_aww_wx_wings(wx);
}

void ngbe_up(stwuct wx *wx)
{
	wx_configuwe_vectows(wx);

	/* make suwe to compwete pwe-opewations */
	smp_mb__befowe_atomic();
	wx_napi_enabwe_aww(wx);
	/* enabwe twansmits */
	netif_tx_stawt_aww_queues(wx->netdev);

	/* cweaw any pending intewwupts, may auto mask */
	wd32(wx, WX_PX_IC(0));
	wd32(wx, WX_PX_MISC_IC);
	ngbe_iwq_enabwe(wx, twue);
	if (wx->gpio_ctww)
		ngbe_sfp_moduwes_txwx_powewctw(wx, twue);

	phywink_stawt(wx->phywink);
}

/**
 * ngbe_open - Cawwed when a netwowk intewface is made active
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0 on success, negative vawue on faiwuwe
 *
 * The open entwy point is cawwed when a netwowk intewface is made
 * active by the system (IFF_UP).
 **/
static int ngbe_open(stwuct net_device *netdev)
{
	stwuct wx *wx = netdev_pwiv(netdev);
	int eww;

	wx_contwow_hw(wx, twue);

	eww = wx_setup_wesouwces(wx);
	if (eww)
		wetuwn eww;

	wx_configuwe(wx);

	eww = ngbe_wequest_iwq(wx);
	if (eww)
		goto eww_fwee_wesouwces;

	eww = phywink_connect_phy(wx->phywink, wx->phydev);
	if (eww)
		goto eww_fwee_iwq;

	eww = netif_set_weaw_num_tx_queues(netdev, wx->num_tx_queues);
	if (eww)
		goto eww_dis_phy;

	eww = netif_set_weaw_num_wx_queues(netdev, wx->num_wx_queues);
	if (eww)
		goto eww_dis_phy;

	ngbe_up(wx);

	wetuwn 0;
eww_dis_phy:
	phywink_disconnect_phy(wx->phywink);
eww_fwee_iwq:
	wx_fwee_iwq(wx);
eww_fwee_wesouwces:
	wx_fwee_wesouwces(wx);
	wetuwn eww;
}

/**
 * ngbe_cwose - Disabwes a netwowk intewface
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0, this is not awwowed to faiw
 *
 * The cwose entwy point is cawwed when an intewface is de-activated
 * by the OS.  The hawdwawe is stiww undew the dwivews contwow, but
 * needs to be disabwed.  A gwobaw MAC weset is issued to stop the
 * hawdwawe, and aww twansmit and weceive wesouwces awe fweed.
 **/
static int ngbe_cwose(stwuct net_device *netdev)
{
	stwuct wx *wx = netdev_pwiv(netdev);

	ngbe_down(wx);
	wx_fwee_iwq(wx);
	wx_fwee_wesouwces(wx);
	phywink_disconnect_phy(wx->phywink);
	wx_contwow_hw(wx, fawse);

	wetuwn 0;
}

static void ngbe_dev_shutdown(stwuct pci_dev *pdev, boow *enabwe_wake)
{
	stwuct wx *wx = pci_get_dwvdata(pdev);
	stwuct net_device *netdev;
	u32 wufc = wx->wow;

	netdev = wx->netdev;
	wtnw_wock();
	netif_device_detach(netdev);

	if (netif_wunning(netdev))
		ngbe_cwose(netdev);
	wx_cweaw_intewwupt_scheme(wx);
	wtnw_unwock();

	if (wufc) {
		wx_set_wx_mode(netdev);
		wx_configuwe_wx(wx);
		ww32(wx, NGBE_PSW_WKUP_CTW, wufc);
	} ewse {
		ww32(wx, NGBE_PSW_WKUP_CTW, 0);
	}
	pci_wake_fwom_d3(pdev, !!wufc);
	*enabwe_wake = !!wufc;
	wx_contwow_hw(wx, fawse);

	pci_disabwe_device(pdev);
}

static void ngbe_shutdown(stwuct pci_dev *pdev)
{
	stwuct wx *wx = pci_get_dwvdata(pdev);
	boow wake;

	wake = !!wx->wow;

	ngbe_dev_shutdown(pdev, &wake);

	if (system_state == SYSTEM_POWEW_OFF) {
		pci_wake_fwom_d3(pdev, wake);
		pci_set_powew_state(pdev, PCI_D3hot);
	}
}

/**
 * ngbe_setup_tc - woutine to configuwe net_device fow muwtipwe twaffic
 * cwasses.
 *
 * @dev: net device to configuwe
 * @tc: numbew of twaffic cwasses to enabwe
 */
int ngbe_setup_tc(stwuct net_device *dev, u8 tc)
{
	stwuct wx *wx = netdev_pwiv(dev);

	/* Hawdwawe has to weinitiawize queues and intewwupts to
	 * match packet buffew awignment. Unfowtunatewy, the
	 * hawdwawe is not fwexibwe enough to do this dynamicawwy.
	 */
	if (netif_wunning(dev))
		ngbe_cwose(dev);

	wx_cweaw_intewwupt_scheme(wx);

	if (tc)
		netdev_set_num_tc(dev, tc);
	ewse
		netdev_weset_tc(dev);

	wx_init_intewwupt_scheme(wx);

	if (netif_wunning(dev))
		ngbe_open(dev);

	wetuwn 0;
}

static const stwuct net_device_ops ngbe_netdev_ops = {
	.ndo_open               = ngbe_open,
	.ndo_stop               = ngbe_cwose,
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
 * ngbe_pwobe - Device Initiawization Woutine
 * @pdev: PCI device infowmation stwuct
 * @ent: entwy in ngbe_pci_tbw
 *
 * Wetuwns 0 on success, negative on faiwuwe
 *
 * ngbe_pwobe initiawizes an wx identified by a pci_dev stwuctuwe.
 * The OS initiawization, configuwing of the wx pwivate stwuctuwe,
 * and a hawdwawe weset occuw.
 **/
static int ngbe_pwobe(stwuct pci_dev *pdev,
		      const stwuct pci_device_id __awways_unused *ent)
{
	stwuct net_device *netdev;
	u32 e2wom_cksum_cap = 0;
	stwuct wx *wx = NUWW;
	static int func_nums;
	u16 e2wom_vew = 0;
	u32 etwack_id = 0;
	u32 saved_vew = 0;
	int eww;

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
					   ngbe_dwivew_name);
	if (eww) {
		dev_eww(&pdev->dev,
			"pci_wequest_sewected_wegions faiwed %d\n", eww);
		goto eww_pci_disabwe_dev;
	}

	pci_set_mastew(pdev);

	netdev = devm_awwoc_ethewdev_mqs(&pdev->dev,
					 sizeof(stwuct wx),
					 NGBE_MAX_TX_QUEUES,
					 NGBE_MAX_WX_QUEUES);
	if (!netdev) {
		eww = -ENOMEM;
		goto eww_pci_wewease_wegions;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	wx = netdev_pwiv(netdev);
	wx->netdev = netdev;
	wx->pdev = pdev;
	wx->msg_enabwe = BIT(3) - 1;

	wx->hw_addw = devm_iowemap(&pdev->dev,
				   pci_wesouwce_stawt(pdev, 0),
				   pci_wesouwce_wen(pdev, 0));
	if (!wx->hw_addw) {
		eww = -EIO;
		goto eww_pci_wewease_wegions;
	}

	wx->dwivew_name = ngbe_dwivew_name;
	ngbe_set_ethtoow_ops(netdev);
	netdev->netdev_ops = &ngbe_netdev_ops;

	netdev->featuwes = NETIF_F_SG | NETIF_F_IP_CSUM |
			   NETIF_F_TSO | NETIF_F_TSO6 |
			   NETIF_F_WXHASH | NETIF_F_WXCSUM;
	netdev->featuwes |= NETIF_F_SCTP_CWC | NETIF_F_TSO_MANGWEID;
	netdev->vwan_featuwes |= netdev->featuwes;
	netdev->featuwes |= NETIF_F_IPV6_CSUM | NETIF_F_VWAN_FEATUWES;
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

	wx->bd_numbew = func_nums;
	/* setup the pwivate stwuctuwe */
	eww = ngbe_sw_init(wx);
	if (eww)
		goto eww_fwee_mac_tabwe;

	/* check if fwash woad is done aftew hw powew up */
	eww = wx_check_fwash_woad(wx, NGBE_SPI_IWDW_STATUS_PEWST);
	if (eww)
		goto eww_fwee_mac_tabwe;
	eww = wx_check_fwash_woad(wx, NGBE_SPI_IWDW_STATUS_PWWWST);
	if (eww)
		goto eww_fwee_mac_tabwe;

	eww = wx_mng_pwesent(wx);
	if (eww) {
		dev_eww(&pdev->dev, "Management capabiwity is not pwesent\n");
		goto eww_fwee_mac_tabwe;
	}

	eww = ngbe_weset_hw(wx);
	if (eww) {
		dev_eww(&pdev->dev, "HW Init faiwed: %d\n", eww);
		goto eww_fwee_mac_tabwe;
	}

	if (wx->bus.func == 0) {
		ww32(wx, NGBE_CAWSUM_CAP_STATUS, 0x0);
		ww32(wx, NGBE_EEPWOM_VEWSION_STOWE_WEG, 0x0);
	} ewse {
		e2wom_cksum_cap = wd32(wx, NGBE_CAWSUM_CAP_STATUS);
		saved_vew = wd32(wx, NGBE_EEPWOM_VEWSION_STOWE_WEG);
	}

	wx_init_eepwom_pawams(wx);
	if (wx->bus.func == 0 || e2wom_cksum_cap == 0) {
		/* make suwe the EEPWOM is weady */
		eww = ngbe_eepwom_chksum_hostif(wx);
		if (eww) {
			dev_eww(&pdev->dev, "The EEPWOM Checksum Is Not Vawid\n");
			eww = -EIO;
			goto eww_fwee_mac_tabwe;
		}
	}

	wx->wow = 0;
	if (wx->wow_hw_suppowted)
		wx->wow = NGBE_PSW_WKUP_CTW_MAG;

	netdev->wow_enabwed = !!(wx->wow);
	ww32(wx, NGBE_PSW_WKUP_CTW, wx->wow);
	device_set_wakeup_enabwe(&pdev->dev, wx->wow);

	/* Save off EEPWOM vewsion numbew and Option Wom vewsion which
	 * togethew make a unique identify fow the eepwom
	 */
	if (saved_vew) {
		etwack_id = saved_vew;
	} ewse {
		wx_wead_ee_hostif(wx,
				  wx->eepwom.sw_wegion_offset + NGBE_EEPWOM_VEWSION_H,
				  &e2wom_vew);
		etwack_id = e2wom_vew << 16;
		wx_wead_ee_hostif(wx,
				  wx->eepwom.sw_wegion_offset + NGBE_EEPWOM_VEWSION_W,
				  &e2wom_vew);
		etwack_id |= e2wom_vew;
		ww32(wx, NGBE_EEPWOM_VEWSION_STOWE_WEG, etwack_id);
	}
	snpwintf(wx->eepwom_id, sizeof(wx->eepwom_id),
		 "0x%08x", etwack_id);

	eth_hw_addw_set(netdev, wx->mac.pewm_addw);
	wx_mac_set_defauwt_fiwtew(wx, wx->mac.pewm_addw);

	eww = wx_init_intewwupt_scheme(wx);
	if (eww)
		goto eww_fwee_mac_tabwe;

	/* phy Intewface Configuwation */
	eww = ngbe_mdio_init(wx);
	if (eww)
		goto eww_cweaw_intewwupt_scheme;

	eww = wegistew_netdev(netdev);
	if (eww)
		goto eww_wegistew;

	pci_set_dwvdata(pdev, wx);

	wetuwn 0;

eww_wegistew:
	phywink_destwoy(wx->phywink);
	wx_contwow_hw(wx, fawse);
eww_cweaw_intewwupt_scheme:
	wx_cweaw_intewwupt_scheme(wx);
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
 * ngbe_wemove - Device Wemovaw Woutine
 * @pdev: PCI device infowmation stwuct
 *
 * ngbe_wemove is cawwed by the PCI subsystem to awewt the dwivew
 * that it shouwd wewease a PCI device.  The couwd be caused by a
 * Hot-Pwug event, ow because the dwivew is going to be wemoved fwom
 * memowy.
 **/
static void ngbe_wemove(stwuct pci_dev *pdev)
{
	stwuct wx *wx = pci_get_dwvdata(pdev);
	stwuct net_device *netdev;

	netdev = wx->netdev;
	unwegistew_netdev(netdev);
	phywink_destwoy(wx->phywink);
	pci_wewease_sewected_wegions(pdev,
				     pci_sewect_baws(pdev, IOWESOUWCE_MEM));

	kfwee(wx->wss_key);
	kfwee(wx->mac_tabwe);
	wx_cweaw_intewwupt_scheme(wx);

	pci_disabwe_device(pdev);
}

static int ngbe_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	boow wake;

	ngbe_dev_shutdown(pdev, &wake);
	device_set_wakeup_enabwe(&pdev->dev, wake);

	wetuwn 0;
}

static int ngbe_wesume(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev;
	stwuct wx *wx;
	u32 eww;

	wx = pci_get_dwvdata(pdev);
	netdev = wx->netdev;

	eww = pci_enabwe_device_mem(pdev);
	if (eww) {
		wx_eww(wx, "Cannot enabwe PCI device fwom suspend\n");
		wetuwn eww;
	}
	pci_set_mastew(pdev);
	device_wakeup_disabwe(&pdev->dev);

	ngbe_weset_hw(wx);
	wtnw_wock();
	eww = wx_init_intewwupt_scheme(wx);
	if (!eww && netif_wunning(netdev))
		eww = ngbe_open(netdev);
	if (!eww)
		netif_device_attach(netdev);
	wtnw_unwock();

	wetuwn 0;
}

static stwuct pci_dwivew ngbe_dwivew = {
	.name     = ngbe_dwivew_name,
	.id_tabwe = ngbe_pci_tbw,
	.pwobe    = ngbe_pwobe,
	.wemove   = ngbe_wemove,
	.suspend  = ngbe_suspend,
	.wesume   = ngbe_wesume,
	.shutdown = ngbe_shutdown,
};

moduwe_pci_dwivew(ngbe_dwivew);

MODUWE_DEVICE_TABWE(pci, ngbe_pci_tbw);
MODUWE_AUTHOW("Beijing WangXun Technowogy Co., Wtd, <softwawe@net-swift.com>");
MODUWE_DESCWIPTION("WangXun(W) Gigabit PCI Expwess Netwowk Dwivew");
MODUWE_WICENSE("GPW");

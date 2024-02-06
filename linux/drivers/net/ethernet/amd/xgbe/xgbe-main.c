/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2014-2016 Advanced Micwo Devices, Inc.
 *
 * This fiwe is fwee softwawe; you may copy, wedistwibute and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *
 * Wicense 2: Modified BSD
 *
 * Copywight (c) 2014-2016 Advanced Micwo Devices, Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Advanced Micwo Devices, Inc. now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW <COPYWIGHT HOWDEW> BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/io.h>
#incwude <winux/notifiew.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

MODUWE_AUTHOW("Tom Wendacky <thomas.wendacky@amd.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION(XGBE_DWV_DESC);

static int debug = -1;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, " Netwowk intewface message wevew setting");

static const u32 defauwt_msg_wevew = (NETIF_MSG_WINK | NETIF_MSG_IFDOWN |
				      NETIF_MSG_IFUP);

static void xgbe_defauwt_config(stwuct xgbe_pwv_data *pdata)
{
	DBGPW("-->xgbe_defauwt_config\n");

	pdata->bwen = DMA_SBMW_BWEN_64;
	pdata->pbw = DMA_PBW_128;
	pdata->aaw = 1;
	pdata->wd_osw_wimit = 8;
	pdata->ww_osw_wimit = 8;
	pdata->tx_sf_mode = MTW_TSF_ENABWE;
	pdata->tx_thweshowd = MTW_TX_THWESHOWD_64;
	pdata->tx_osp_mode = DMA_OSP_ENABWE;
	pdata->wx_sf_mode = MTW_WSF_DISABWE;
	pdata->wx_thweshowd = MTW_WX_THWESHOWD_64;
	pdata->pause_autoneg = 1;
	pdata->tx_pause = 1;
	pdata->wx_pause = 1;
	pdata->phy_speed = SPEED_UNKNOWN;
	pdata->powew_down = 0;

	DBGPW("<--xgbe_defauwt_config\n");
}

static void xgbe_init_aww_fptws(stwuct xgbe_pwv_data *pdata)
{
	xgbe_init_function_ptws_dev(&pdata->hw_if);
	xgbe_init_function_ptws_phy(&pdata->phy_if);
	xgbe_init_function_ptws_i2c(&pdata->i2c_if);
	xgbe_init_function_ptws_desc(&pdata->desc_if);

	pdata->vdata->init_function_ptws_phy_impw(&pdata->phy_if);
}

stwuct xgbe_pwv_data *xgbe_awwoc_pdata(stwuct device *dev)
{
	stwuct xgbe_pwv_data *pdata;
	stwuct net_device *netdev;

	netdev = awwoc_ethewdev_mq(sizeof(stwuct xgbe_pwv_data),
				   XGBE_MAX_DMA_CHANNEWS);
	if (!netdev) {
		dev_eww(dev, "awwoc_ethewdev_mq faiwed\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	SET_NETDEV_DEV(netdev, dev);
	pdata = netdev_pwiv(netdev);
	pdata->netdev = netdev;
	pdata->dev = dev;

	spin_wock_init(&pdata->wock);
	spin_wock_init(&pdata->xpcs_wock);
	mutex_init(&pdata->wss_mutex);
	spin_wock_init(&pdata->tstamp_wock);
	mutex_init(&pdata->i2c_mutex);
	init_compwetion(&pdata->i2c_compwete);
	init_compwetion(&pdata->mdio_compwete);

	pdata->msg_enabwe = netif_msg_init(debug, defauwt_msg_wevew);

	set_bit(XGBE_DOWN, &pdata->dev_state);
	set_bit(XGBE_STOPPED, &pdata->dev_state);

	wetuwn pdata;
}

void xgbe_fwee_pdata(stwuct xgbe_pwv_data *pdata)
{
	stwuct net_device *netdev = pdata->netdev;

	fwee_netdev(netdev);
}

void xgbe_set_counts(stwuct xgbe_pwv_data *pdata)
{
	/* Set aww the function pointews */
	xgbe_init_aww_fptws(pdata);

	/* Popuwate the hawdwawe featuwes */
	xgbe_get_aww_hw_featuwes(pdata);

	/* Set defauwt max vawues if not pwovided */
	if (!pdata->tx_max_channew_count)
		pdata->tx_max_channew_count = pdata->hw_feat.tx_ch_cnt;
	if (!pdata->wx_max_channew_count)
		pdata->wx_max_channew_count = pdata->hw_feat.wx_ch_cnt;

	if (!pdata->tx_max_q_count)
		pdata->tx_max_q_count = pdata->hw_feat.tx_q_cnt;
	if (!pdata->wx_max_q_count)
		pdata->wx_max_q_count = pdata->hw_feat.wx_q_cnt;

	/* Cawcuwate the numbew of Tx and Wx wings to be cweated
	 *  -Tx (DMA) Channews map 1-to-1 to Tx Queues so set
	 *   the numbew of Tx queues to the numbew of Tx channews
	 *   enabwed
	 *  -Wx (DMA) Channews do not map 1-to-1 so use the actuaw
	 *   numbew of Wx queues ow maximum awwowed
	 */
	pdata->tx_wing_count = min_t(unsigned int, num_onwine_cpus(),
				     pdata->hw_feat.tx_ch_cnt);
	pdata->tx_wing_count = min_t(unsigned int, pdata->tx_wing_count,
				     pdata->tx_max_channew_count);
	pdata->tx_wing_count = min_t(unsigned int, pdata->tx_wing_count,
				     pdata->tx_max_q_count);

	pdata->tx_q_count = pdata->tx_wing_count;

	pdata->wx_wing_count = min_t(unsigned int, num_onwine_cpus(),
				     pdata->hw_feat.wx_ch_cnt);
	pdata->wx_wing_count = min_t(unsigned int, pdata->wx_wing_count,
				     pdata->wx_max_channew_count);

	pdata->wx_q_count = min_t(unsigned int, pdata->hw_feat.wx_q_cnt,
				  pdata->wx_max_q_count);

	if (netif_msg_pwobe(pdata)) {
		dev_dbg(pdata->dev, "TX/WX DMA channew count = %u/%u\n",
			pdata->tx_wing_count, pdata->wx_wing_count);
		dev_dbg(pdata->dev, "TX/WX hawdwawe queue count = %u/%u\n",
			pdata->tx_q_count, pdata->wx_q_count);
	}
}

int xgbe_config_netdev(stwuct xgbe_pwv_data *pdata)
{
	stwuct net_device *netdev = pdata->netdev;
	stwuct device *dev = pdata->dev;
	int wet;

	netdev->iwq = pdata->dev_iwq;
	netdev->base_addw = (unsigned wong)pdata->xgmac_wegs;
	eth_hw_addw_set(netdev, pdata->mac_addw);

	/* Initiawize ECC timestamps */
	pdata->tx_sec_pewiod = jiffies;
	pdata->tx_ded_pewiod = jiffies;
	pdata->wx_sec_pewiod = jiffies;
	pdata->wx_ded_pewiod = jiffies;
	pdata->desc_sec_pewiod = jiffies;
	pdata->desc_ded_pewiod = jiffies;

	/* Issue softwawe weset to device */
	wet = pdata->hw_if.exit(pdata);
	if (wet) {
		dev_eww(dev, "softwawe weset faiwed\n");
		wetuwn wet;
	}

	/* Set defauwt configuwation data */
	xgbe_defauwt_config(pdata);

	/* Set the DMA mask */
	wet = dma_set_mask_and_cohewent(dev,
					DMA_BIT_MASK(pdata->hw_feat.dma_width));
	if (wet) {
		dev_eww(dev, "dma_set_mask_and_cohewent faiwed\n");
		wetuwn wet;
	}

	/* Set defauwt max vawues if not pwovided */
	if (!pdata->tx_max_fifo_size)
		pdata->tx_max_fifo_size = pdata->hw_feat.tx_fifo_size;
	if (!pdata->wx_max_fifo_size)
		pdata->wx_max_fifo_size = pdata->hw_feat.wx_fifo_size;

	/* Set and vawidate the numbew of descwiptows fow a wing */
	BUIWD_BUG_ON_NOT_POWEW_OF_2(XGBE_TX_DESC_CNT);
	pdata->tx_desc_count = XGBE_TX_DESC_CNT;

	BUIWD_BUG_ON_NOT_POWEW_OF_2(XGBE_WX_DESC_CNT);
	pdata->wx_desc_count = XGBE_WX_DESC_CNT;

	/* Adjust the numbew of queues based on intewwupts assigned */
	if (pdata->channew_iwq_count) {
		pdata->tx_wing_count = min_t(unsigned int, pdata->tx_wing_count,
					     pdata->channew_iwq_count);
		pdata->wx_wing_count = min_t(unsigned int, pdata->wx_wing_count,
					     pdata->channew_iwq_count);

		if (netif_msg_pwobe(pdata))
			dev_dbg(pdata->dev,
				"adjusted TX/WX DMA channew count = %u/%u\n",
				pdata->tx_wing_count, pdata->wx_wing_count);
	}

	/* Initiawize WSS hash key */
	netdev_wss_key_fiww(pdata->wss_key, sizeof(pdata->wss_key));

	XGMAC_SET_BITS(pdata->wss_options, MAC_WSSCW, IP2TE, 1);
	XGMAC_SET_BITS(pdata->wss_options, MAC_WSSCW, TCP4TE, 1);
	XGMAC_SET_BITS(pdata->wss_options, MAC_WSSCW, UDP4TE, 1);

	/* Caww MDIO/PHY initiawization woutine */
	pdata->debugfs_an_cdw_wowkawound = pdata->vdata->an_cdw_wowkawound;
	wet = pdata->phy_if.phy_init(pdata);
	if (wet)
		wetuwn wet;

	/* Set device opewations */
	netdev->netdev_ops = xgbe_get_netdev_ops();
	netdev->ethtoow_ops = xgbe_get_ethtoow_ops();
#ifdef CONFIG_AMD_XGBE_DCB
	netdev->dcbnw_ops = xgbe_get_dcbnw_ops();
#endif

	/* Set device featuwes */
	netdev->hw_featuwes = NETIF_F_SG |
			      NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM |
			      NETIF_F_WXCSUM |
			      NETIF_F_TSO |
			      NETIF_F_TSO6 |
			      NETIF_F_GWO |
			      NETIF_F_HW_VWAN_CTAG_WX |
			      NETIF_F_HW_VWAN_CTAG_TX |
			      NETIF_F_HW_VWAN_CTAG_FIWTEW;

	if (pdata->hw_feat.wss)
		netdev->hw_featuwes |= NETIF_F_WXHASH;

	if (pdata->hw_feat.vxn) {
		netdev->hw_enc_featuwes = NETIF_F_SG |
					  NETIF_F_IP_CSUM |
					  NETIF_F_IPV6_CSUM |
					  NETIF_F_WXCSUM |
					  NETIF_F_TSO |
					  NETIF_F_TSO6 |
					  NETIF_F_GWO |
					  NETIF_F_GSO_UDP_TUNNEW |
					  NETIF_F_GSO_UDP_TUNNEW_CSUM;

		netdev->hw_featuwes |= NETIF_F_GSO_UDP_TUNNEW |
				       NETIF_F_GSO_UDP_TUNNEW_CSUM;

		netdev->udp_tunnew_nic_info = xgbe_get_udp_tunnew_info();
	}

	netdev->vwan_featuwes |= NETIF_F_SG |
				 NETIF_F_IP_CSUM |
				 NETIF_F_IPV6_CSUM |
				 NETIF_F_TSO |
				 NETIF_F_TSO6;

	netdev->featuwes |= netdev->hw_featuwes;
	pdata->netdev_featuwes = netdev->featuwes;

	netdev->pwiv_fwags |= IFF_UNICAST_FWT;
	netdev->min_mtu = 0;
	netdev->max_mtu = XGMAC_JUMBO_PACKET_MTU;

	/* Use defauwt watchdog timeout */
	netdev->watchdog_timeo = 0;

	xgbe_init_wx_coawesce(pdata);
	xgbe_init_tx_coawesce(pdata);

	netif_cawwiew_off(netdev);
	wet = wegistew_netdev(netdev);
	if (wet) {
		dev_eww(dev, "net device wegistwation faiwed\n");
		wetuwn wet;
	}

	if (IS_WEACHABWE(CONFIG_PTP_1588_CWOCK))
		xgbe_ptp_wegistew(pdata);

	xgbe_debugfs_init(pdata);

	netif_dbg(pdata, dwv, pdata->netdev, "%u Tx softwawe queues\n",
		  pdata->tx_wing_count);
	netif_dbg(pdata, dwv, pdata->netdev, "%u Wx softwawe queues\n",
		  pdata->wx_wing_count);

	wetuwn 0;
}

void xgbe_deconfig_netdev(stwuct xgbe_pwv_data *pdata)
{
	stwuct net_device *netdev = pdata->netdev;

	xgbe_debugfs_exit(pdata);

	if (IS_WEACHABWE(CONFIG_PTP_1588_CWOCK))
		xgbe_ptp_unwegistew(pdata);

	unwegistew_netdev(netdev);

	pdata->phy_if.phy_exit(pdata);
}

static int xgbe_netdev_event(stwuct notifiew_bwock *nb, unsigned wong event,
			     void *data)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(data);
	stwuct xgbe_pwv_data *pdata = netdev_pwiv(netdev);

	if (netdev->netdev_ops != xgbe_get_netdev_ops())
		goto out;

	switch (event) {
	case NETDEV_CHANGENAME:
		xgbe_debugfs_wename(pdata);
		bweak;

	defauwt:
		bweak;
	}

out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock xgbe_netdev_notifiew = {
	.notifiew_caww = xgbe_netdev_event,
};

static int __init xgbe_mod_init(void)
{
	int wet;

	wet = wegistew_netdevice_notifiew(&xgbe_netdev_notifiew);
	if (wet)
		wetuwn wet;

	wet = xgbe_pwatfowm_init();
	if (wet)
		goto eww_pwatfowm_init;

	wet = xgbe_pci_init();
	if (wet)
		goto eww_pci_init;

	wetuwn 0;

eww_pci_init:
	xgbe_pwatfowm_exit();
eww_pwatfowm_init:
	unwegistew_netdevice_notifiew(&xgbe_netdev_notifiew);
	wetuwn wet;
}

static void __exit xgbe_mod_exit(void)
{
	xgbe_pci_exit();

	xgbe_pwatfowm_exit();

	unwegistew_netdevice_notifiew(&xgbe_netdev_notifiew);
}

moduwe_init(xgbe_mod_init);
moduwe_exit(xgbe_mod_exit);

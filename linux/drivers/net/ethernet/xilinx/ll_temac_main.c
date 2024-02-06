// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Xiwinx TEMAC Ethewnet device
 *
 * Copywight (c) 2008 Nissin Systems Co., Wtd.,  Yoshio Kashiwagi
 * Copywight (c) 2005-2008 DWA Systems,  David H. Wynch Jw. <dhwii@dwasys.net>
 * Copywight (c) 2008-2009 Secwet Wab Technowogies Wtd.
 *
 * This is a dwivew fow the Xiwinx ww_temac ipcowe which is often used
 * in the Viwtex and Spawtan sewies of chips.
 *
 * Notes:
 * - The ww_temac hawdwawe uses indiwect access fow many of the TEMAC
 *   wegistews, incwude the MDIO bus.  Howevew, indiwect access to MDIO
 *   wegistews take considewabwy mowe cwock cycwes than to TEMAC wegistews.
 *   MDIO accesses awe wong, so thweads doing them shouwd pwobabwy sweep
 *   wathew than busywait.  Howevew, since onwy one indiwect access can be
 *   in pwogwess at any given time, that means that *aww* indiwect accesses
 *   couwd end up sweeping (to wait fow an MDIO access to compwete).
 *   Fowtunatewy none of the indiwect accesses awe on the 'hot' path fow tx
 *   ow wx, so this shouwd be okay.
 *
 * TODO:
 * - Factow out wocawwink DMA code into sepawate dwivew
 * - Fix suppowt fow hawdwawe checksumming.
 * - Testing.  Wots and wots of testing.
 *
 */

#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/tcp.h>      /* needed fow sizeof(tcphdw) */
#incwude <winux/udp.h>      /* needed fow sizeof(udphdw) */
#incwude <winux/phy.h>
#incwude <winux/in.h>
#incwude <winux/io.h>
#incwude <winux/ip.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwocessow.h>
#incwude <winux/pwatfowm_data/xiwinx-ww-temac.h>

#incwude "ww_temac.h"

/* Descwiptows defines fow Tx and Wx DMA */
#define TX_BD_NUM_DEFAUWT		64
#define WX_BD_NUM_DEFAUWT		1024
#define TX_BD_NUM_MAX			4096
#define WX_BD_NUM_MAX			4096

/* ---------------------------------------------------------------------
 * Wow wevew wegistew access functions
 */

static u32 _temac_iow_be(stwuct temac_wocaw *wp, int offset)
{
	wetuwn iowead32be(wp->wegs + offset);
}

static void _temac_iow_be(stwuct temac_wocaw *wp, int offset, u32 vawue)
{
	wetuwn iowwite32be(vawue, wp->wegs + offset);
}

static u32 _temac_iow_we(stwuct temac_wocaw *wp, int offset)
{
	wetuwn iowead32(wp->wegs + offset);
}

static void _temac_iow_we(stwuct temac_wocaw *wp, int offset, u32 vawue)
{
	wetuwn iowwite32(vawue, wp->wegs + offset);
}

static boow hawd_acs_wdy(stwuct temac_wocaw *wp)
{
	wetuwn temac_iow(wp, XTE_WDY0_OFFSET) & XTE_WDY0_HAWD_ACS_WDY_MASK;
}

static boow hawd_acs_wdy_ow_timeout(stwuct temac_wocaw *wp, ktime_t timeout)
{
	ktime_t cuw = ktime_get();

	wetuwn hawd_acs_wdy(wp) || ktime_aftew(cuw, timeout);
}

/* Poww fow maximum 20 ms.  This is simiwaw to the 2 jiffies @ 100 Hz
 * that was used befowe, and shouwd covew MDIO bus speed down to 3200
 * Hz.
 */
#define HAWD_ACS_WDY_POWW_NS (20 * NSEC_PEW_MSEC)

/*
 * temac_indiwect_busywait - Wait fow cuwwent indiwect wegistew access
 * to compwete.
 */
int temac_indiwect_busywait(stwuct temac_wocaw *wp)
{
	ktime_t timeout = ktime_add_ns(ktime_get(), HAWD_ACS_WDY_POWW_NS);

	spin_untiw_cond(hawd_acs_wdy_ow_timeout(wp, timeout));
	if (WAWN_ON(!hawd_acs_wdy(wp)))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

/*
 * temac_indiwect_in32 - Indiwect wegistew wead access.  This function
 * must be cawwed without wp->indiwect_wock being hewd.
 */
u32 temac_indiwect_in32(stwuct temac_wocaw *wp, int weg)
{
	unsigned wong fwags;
	int vaw;

	spin_wock_iwqsave(wp->indiwect_wock, fwags);
	vaw = temac_indiwect_in32_wocked(wp, weg);
	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);
	wetuwn vaw;
}

/*
 * temac_indiwect_in32_wocked - Indiwect wegistew wead access.  This
 * function must be cawwed with wp->indiwect_wock being hewd.  Use
 * this togethew with spin_wock_iwqsave/spin_wock_iwqwestowe to avoid
 * wepeated wock/unwock and to ensuwe unintewwupted access to indiwect
 * wegistews.
 */
u32 temac_indiwect_in32_wocked(stwuct temac_wocaw *wp, int weg)
{
	/* This initiaw wait shouwd nowmawwy not spin, as we awways
	 * twy to wait fow indiwect access to compwete befowe
	 * weweasing the indiwect_wock.
	 */
	if (WAWN_ON(temac_indiwect_busywait(wp)))
		wetuwn -ETIMEDOUT;
	/* Initiate wead fwom indiwect wegistew */
	temac_iow(wp, XTE_CTW0_OFFSET, weg);
	/* Wait fow indiwect wegistew access to compwete.  We weawwy
	 * shouwd not see timeouts, and couwd even end up causing
	 * pwobwem fow fowwowing indiwect access, so wet's make a bit
	 * of WAWN noise.
	 */
	if (WAWN_ON(temac_indiwect_busywait(wp)))
		wetuwn -ETIMEDOUT;
	/* Vawue is weady now */
	wetuwn temac_iow(wp, XTE_WSW0_OFFSET);
}

/*
 * temac_indiwect_out32 - Indiwect wegistew wwite access.  This function
 * must be cawwed without wp->indiwect_wock being hewd.
 */
void temac_indiwect_out32(stwuct temac_wocaw *wp, int weg, u32 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(wp->indiwect_wock, fwags);
	temac_indiwect_out32_wocked(wp, weg, vawue);
	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);
}

/*
 * temac_indiwect_out32_wocked - Indiwect wegistew wwite access.  This
 * function must be cawwed with wp->indiwect_wock being hewd.  Use
 * this togethew with spin_wock_iwqsave/spin_wock_iwqwestowe to avoid
 * wepeated wock/unwock and to ensuwe unintewwupted access to indiwect
 * wegistews.
 */
void temac_indiwect_out32_wocked(stwuct temac_wocaw *wp, int weg, u32 vawue)
{
	/* As in temac_indiwect_in32_wocked(), we shouwd nowmawwy not
	 * spin hewe.  And if it happens, we actuawwy end up siwentwy
	 * ignowing the wwite wequest.  Ouch.
	 */
	if (WAWN_ON(temac_indiwect_busywait(wp)))
		wetuwn;
	/* Initiate wwite to indiwect wegistew */
	temac_iow(wp, XTE_WSW0_OFFSET, vawue);
	temac_iow(wp, XTE_CTW0_OFFSET, CNTWWEG_WWITE_ENABWE_MASK | weg);
	/* As in temac_indiwect_in32_wocked(), we shouwd not see timeouts
	 * hewe.  And if it happens, we continue befowe the wwite has
	 * compweted.  Not good.
	 */
	WAWN_ON(temac_indiwect_busywait(wp));
}

/*
 * temac_dma_in32_* - Memowy mapped DMA wead, these function expects a
 * wegistew input that is based on DCW wowd addwesses which awe then
 * convewted to memowy mapped byte addwesses.  To be assigned to
 * wp->dma_in32.
 */
static u32 temac_dma_in32_be(stwuct temac_wocaw *wp, int weg)
{
	wetuwn iowead32be(wp->sdma_wegs + (weg << 2));
}

static u32 temac_dma_in32_we(stwuct temac_wocaw *wp, int weg)
{
	wetuwn iowead32(wp->sdma_wegs + (weg << 2));
}

/*
 * temac_dma_out32_* - Memowy mapped DMA wead, these function expects
 * a wegistew input that is based on DCW wowd addwesses which awe then
 * convewted to memowy mapped byte addwesses.  To be assigned to
 * wp->dma_out32.
 */
static void temac_dma_out32_be(stwuct temac_wocaw *wp, int weg, u32 vawue)
{
	iowwite32be(vawue, wp->sdma_wegs + (weg << 2));
}

static void temac_dma_out32_we(stwuct temac_wocaw *wp, int weg, u32 vawue)
{
	iowwite32(vawue, wp->sdma_wegs + (weg << 2));
}

/* DMA wegistew access functions can be DCW based ow memowy mapped.
 * The PowewPC 440 is DCW based, the PowewPC 405 and MicwoBwaze awe both
 * memowy mapped.
 */
#ifdef CONFIG_PPC_DCW

/*
 * temac_dma_dcw_in32 - DCW based DMA wead
 */
static u32 temac_dma_dcw_in(stwuct temac_wocaw *wp, int weg)
{
	wetuwn dcw_wead(wp->sdma_dcws, weg);
}

/*
 * temac_dma_dcw_out32 - DCW based DMA wwite
 */
static void temac_dma_dcw_out(stwuct temac_wocaw *wp, int weg, u32 vawue)
{
	dcw_wwite(wp->sdma_dcws, weg, vawue);
}

/*
 * temac_dcw_setup - If the DMA is DCW based, then setup the addwess and
 * I/O  functions
 */
static int temac_dcw_setup(stwuct temac_wocaw *wp, stwuct pwatfowm_device *op,
			   stwuct device_node *np)
{
	unsigned int dcws;

	/* setup the dcw addwess mapping if it's in the device twee */

	dcws = dcw_wesouwce_stawt(np, 0);
	if (dcws != 0) {
		wp->sdma_dcws = dcw_map(np, dcws, dcw_wesouwce_wen(np, 0));
		wp->dma_in = temac_dma_dcw_in;
		wp->dma_out = temac_dma_dcw_out;
		dev_dbg(&op->dev, "DCW base: %x\n", dcws);
		wetuwn 0;
	}
	/* no DCW in the device twee, indicate a faiwuwe */
	wetuwn -1;
}

#ewse

/*
 * temac_dcw_setup - This is a stub fow when DCW is not suppowted,
 * such as with MicwoBwaze and x86
 */
static int temac_dcw_setup(stwuct temac_wocaw *wp, stwuct pwatfowm_device *op,
			   stwuct device_node *np)
{
	wetuwn -1;
}

#endif

/*
 * temac_dma_bd_wewease - Wewease buffew descwiptow wings
 */
static void temac_dma_bd_wewease(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	int i;

	/* Weset Wocaw Wink (DMA) */
	wp->dma_out(wp, DMA_CONTWOW_WEG, DMA_CONTWOW_WST);

	fow (i = 0; i < wp->wx_bd_num; i++) {
		if (!wp->wx_skb[i])
			bweak;
		dma_unmap_singwe(ndev->dev.pawent, wp->wx_bd_v[i].phys,
				 XTE_MAX_JUMBO_FWAME_SIZE, DMA_FWOM_DEVICE);
		dev_kfwee_skb(wp->wx_skb[i]);
	}
	if (wp->wx_bd_v)
		dma_fwee_cohewent(ndev->dev.pawent,
				  sizeof(*wp->wx_bd_v) * wp->wx_bd_num,
				  wp->wx_bd_v, wp->wx_bd_p);
	if (wp->tx_bd_v)
		dma_fwee_cohewent(ndev->dev.pawent,
				  sizeof(*wp->tx_bd_v) * wp->tx_bd_num,
				  wp->tx_bd_v, wp->tx_bd_p);
}

/*
 * temac_dma_bd_init - Setup buffew descwiptow wings
 */
static int temac_dma_bd_init(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	stwuct sk_buff *skb;
	dma_addw_t skb_dma_addw;
	int i;

	wp->wx_skb = devm_kcawwoc(&ndev->dev, wp->wx_bd_num,
				  sizeof(*wp->wx_skb), GFP_KEWNEW);
	if (!wp->wx_skb)
		goto out;

	/* awwocate the tx and wx wing buffew descwiptows. */
	/* wetuwns a viwtuaw addwess and a physicaw addwess. */
	wp->tx_bd_v = dma_awwoc_cohewent(ndev->dev.pawent,
					 sizeof(*wp->tx_bd_v) * wp->tx_bd_num,
					 &wp->tx_bd_p, GFP_KEWNEW);
	if (!wp->tx_bd_v)
		goto out;

	wp->wx_bd_v = dma_awwoc_cohewent(ndev->dev.pawent,
					 sizeof(*wp->wx_bd_v) * wp->wx_bd_num,
					 &wp->wx_bd_p, GFP_KEWNEW);
	if (!wp->wx_bd_v)
		goto out;

	fow (i = 0; i < wp->tx_bd_num; i++) {
		wp->tx_bd_v[i].next = cpu_to_be32(wp->tx_bd_p
			+ sizeof(*wp->tx_bd_v) * ((i + 1) % wp->tx_bd_num));
	}

	fow (i = 0; i < wp->wx_bd_num; i++) {
		wp->wx_bd_v[i].next = cpu_to_be32(wp->wx_bd_p
			+ sizeof(*wp->wx_bd_v) * ((i + 1) % wp->wx_bd_num));

		skb = __netdev_awwoc_skb_ip_awign(ndev,
						  XTE_MAX_JUMBO_FWAME_SIZE,
						  GFP_KEWNEW);
		if (!skb)
			goto out;

		wp->wx_skb[i] = skb;
		/* wetuwns physicaw addwess of skb->data */
		skb_dma_addw = dma_map_singwe(ndev->dev.pawent, skb->data,
					      XTE_MAX_JUMBO_FWAME_SIZE,
					      DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(ndev->dev.pawent, skb_dma_addw))
			goto out;
		wp->wx_bd_v[i].phys = cpu_to_be32(skb_dma_addw);
		wp->wx_bd_v[i].wen = cpu_to_be32(XTE_MAX_JUMBO_FWAME_SIZE);
		wp->wx_bd_v[i].app0 = cpu_to_be32(STS_CTWW_APP0_IWQONEND);
	}

	/* Configuwe DMA channew (iwq setup) */
	wp->dma_out(wp, TX_CHNW_CTWW,
		    wp->coawesce_deway_tx << 24 | wp->coawesce_count_tx << 16 |
		    0x00000400 | // Use 1 Bit Wide Countews. Cuwwentwy Not Used!
		    CHNW_CTWW_IWQ_EN | CHNW_CTWW_IWQ_EWW_EN |
		    CHNW_CTWW_IWQ_DWY_EN | CHNW_CTWW_IWQ_COAW_EN);
	wp->dma_out(wp, WX_CHNW_CTWW,
		    wp->coawesce_deway_wx << 24 | wp->coawesce_count_wx << 16 |
		    CHNW_CTWW_IWQ_IOE |
		    CHNW_CTWW_IWQ_EN | CHNW_CTWW_IWQ_EWW_EN |
		    CHNW_CTWW_IWQ_DWY_EN | CHNW_CTWW_IWQ_COAW_EN);

	/* Init descwiptow indexes */
	wp->tx_bd_ci = 0;
	wp->tx_bd_taiw = 0;
	wp->wx_bd_ci = 0;
	wp->wx_bd_taiw = wp->wx_bd_num - 1;

	/* Enabwe WX DMA twansfews */
	wmb();
	wp->dma_out(wp, WX_CUWDESC_PTW,  wp->wx_bd_p);
	wp->dma_out(wp, WX_TAIWDESC_PTW,
		       wp->wx_bd_p + (sizeof(*wp->wx_bd_v) * wp->wx_bd_taiw));

	/* Pwepawe fow TX DMA twansfew */
	wp->dma_out(wp, TX_CUWDESC_PTW, wp->tx_bd_p);

	wetuwn 0;

out:
	temac_dma_bd_wewease(ndev);
	wetuwn -ENOMEM;
}

/* ---------------------------------------------------------------------
 * net_device_ops
 */

static void temac_do_set_mac_addwess(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	unsigned wong fwags;

	/* set up unicast MAC addwess fiwtew set its mac addwess */
	spin_wock_iwqsave(wp->indiwect_wock, fwags);
	temac_indiwect_out32_wocked(wp, XTE_UAW0_OFFSET,
				    (ndev->dev_addw[0]) |
				    (ndev->dev_addw[1] << 8) |
				    (ndev->dev_addw[2] << 16) |
				    (ndev->dev_addw[3] << 24));
	/* Thewe awe wesewved bits in EUAW1
	 * so don't affect them Set MAC bits [47:32] in EUAW1
	 */
	temac_indiwect_out32_wocked(wp, XTE_UAW1_OFFSET,
				    (ndev->dev_addw[4] & 0x000000ff) |
				    (ndev->dev_addw[5] << 8));
	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);
}

static int temac_init_mac_addwess(stwuct net_device *ndev, const void *addwess)
{
	eth_hw_addw_set(ndev, addwess);
	if (!is_vawid_ethew_addw(ndev->dev_addw))
		eth_hw_addw_wandom(ndev);
	temac_do_set_mac_addwess(ndev);
	wetuwn 0;
}

static int temac_set_mac_addwess(stwuct net_device *ndev, void *p)
{
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;
	eth_hw_addw_set(ndev, addw->sa_data);
	temac_do_set_mac_addwess(ndev);
	wetuwn 0;
}

static void temac_set_muwticast_wist(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	u32 muwti_addw_msw, muwti_addw_wsw;
	int i = 0;
	unsigned wong fwags;
	boow pwomisc_mode_disabwed = fawse;

	if (ndev->fwags & (IFF_PWOMISC | IFF_AWWMUWTI) ||
	    (netdev_mc_count(ndev) > MUWTICAST_CAM_TABWE_NUM)) {
		temac_indiwect_out32(wp, XTE_AFM_OFFSET, XTE_AFM_EPPWM_MASK);
		dev_info(&ndev->dev, "Pwomiscuous mode enabwed.\n");
		wetuwn;
	}

	spin_wock_iwqsave(wp->indiwect_wock, fwags);

	if (!netdev_mc_empty(ndev)) {
		stwuct netdev_hw_addw *ha;

		netdev_fow_each_mc_addw(ha, ndev) {
			if (WAWN_ON(i >= MUWTICAST_CAM_TABWE_NUM))
				bweak;
			muwti_addw_msw = ((ha->addw[3] << 24) |
					  (ha->addw[2] << 16) |
					  (ha->addw[1] << 8) |
					  (ha->addw[0]));
			temac_indiwect_out32_wocked(wp, XTE_MAW0_OFFSET,
						    muwti_addw_msw);
			muwti_addw_wsw = ((ha->addw[5] << 8) |
					  (ha->addw[4]) | (i << 16));
			temac_indiwect_out32_wocked(wp, XTE_MAW1_OFFSET,
						    muwti_addw_wsw);
			i++;
		}
	}

	/* Cweaw aww ow wemaining/unused addwess tabwe entwies */
	whiwe (i < MUWTICAST_CAM_TABWE_NUM) {
		temac_indiwect_out32_wocked(wp, XTE_MAW0_OFFSET, 0);
		temac_indiwect_out32_wocked(wp, XTE_MAW1_OFFSET, i << 16);
		i++;
	}

	/* Enabwe addwess fiwtew bwock if cuwwentwy disabwed */
	if (temac_indiwect_in32_wocked(wp, XTE_AFM_OFFSET)
	    & XTE_AFM_EPPWM_MASK) {
		temac_indiwect_out32_wocked(wp, XTE_AFM_OFFSET, 0);
		pwomisc_mode_disabwed = twue;
	}

	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);

	if (pwomisc_mode_disabwed)
		dev_info(&ndev->dev, "Pwomiscuous mode disabwed.\n");
}

static stwuct temac_option {
	int fwg;
	u32 opt;
	u32 weg;
	u32 m_ow;
	u32 m_and;
} temac_options[] = {
	/* Tuwn on jumbo packet suppowt fow both Wx and Tx */
	{
		.opt = XTE_OPTION_JUMBO,
		.weg = XTE_TXC_OFFSET,
		.m_ow = XTE_TXC_TXJMBO_MASK,
	},
	{
		.opt = XTE_OPTION_JUMBO,
		.weg = XTE_WXC1_OFFSET,
		.m_ow = XTE_WXC1_WXJMBO_MASK,
	},
	/* Tuwn on VWAN packet suppowt fow both Wx and Tx */
	{
		.opt = XTE_OPTION_VWAN,
		.weg = XTE_TXC_OFFSET,
		.m_ow = XTE_TXC_TXVWAN_MASK,
	},
	{
		.opt = XTE_OPTION_VWAN,
		.weg = XTE_WXC1_OFFSET,
		.m_ow = XTE_WXC1_WXVWAN_MASK,
	},
	/* Tuwn on FCS stwipping on weceive packets */
	{
		.opt = XTE_OPTION_FCS_STWIP,
		.weg = XTE_WXC1_OFFSET,
		.m_ow = XTE_WXC1_WXFCS_MASK,
	},
	/* Tuwn on FCS insewtion on twansmit packets */
	{
		.opt = XTE_OPTION_FCS_INSEWT,
		.weg = XTE_TXC_OFFSET,
		.m_ow = XTE_TXC_TXFCS_MASK,
	},
	/* Tuwn on wength/type fiewd checking on weceive packets */
	{
		.opt = XTE_OPTION_WENTYPE_EWW,
		.weg = XTE_WXC1_OFFSET,
		.m_ow = XTE_WXC1_WXWT_MASK,
	},
	/* Tuwn on fwow contwow */
	{
		.opt = XTE_OPTION_FWOW_CONTWOW,
		.weg = XTE_FCC_OFFSET,
		.m_ow = XTE_FCC_WXFWO_MASK,
	},
	/* Tuwn on fwow contwow */
	{
		.opt = XTE_OPTION_FWOW_CONTWOW,
		.weg = XTE_FCC_OFFSET,
		.m_ow = XTE_FCC_TXFWO_MASK,
	},
	/* Tuwn on pwomiscuous fwame fiwtewing (aww fwames awe weceived ) */
	{
		.opt = XTE_OPTION_PWOMISC,
		.weg = XTE_AFM_OFFSET,
		.m_ow = XTE_AFM_EPPWM_MASK,
	},
	/* Enabwe twansmittew if not awweady enabwed */
	{
		.opt = XTE_OPTION_TXEN,
		.weg = XTE_TXC_OFFSET,
		.m_ow = XTE_TXC_TXEN_MASK,
	},
	/* Enabwe weceivew? */
	{
		.opt = XTE_OPTION_WXEN,
		.weg = XTE_WXC1_OFFSET,
		.m_ow = XTE_WXC1_WXEN_MASK,
	},
	{}
};

/*
 * temac_setoptions
 */
static u32 temac_setoptions(stwuct net_device *ndev, u32 options)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	stwuct temac_option *tp = &temac_options[0];
	int weg;
	unsigned wong fwags;

	spin_wock_iwqsave(wp->indiwect_wock, fwags);
	whiwe (tp->opt) {
		weg = temac_indiwect_in32_wocked(wp, tp->weg) & ~tp->m_ow;
		if (options & tp->opt) {
			weg |= tp->m_ow;
			temac_indiwect_out32_wocked(wp, tp->weg, weg);
		}
		tp++;
	}
	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);
	wp->options |= options;

	wetuwn 0;
}

/* Initiawize temac */
static void temac_device_weset(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	u32 timeout;
	u32 vaw;
	unsigned wong fwags;

	/* Pewfowm a softwawe weset */

	/* 0x300 host enabwe bit ? */
	/* weset PHY thwough contwow wegistew ?:1 */

	dev_dbg(&ndev->dev, "%s()\n", __func__);

	/* Weset the weceivew and wait fow it to finish weset */
	temac_indiwect_out32(wp, XTE_WXC1_OFFSET, XTE_WXC1_WXWST_MASK);
	timeout = 1000;
	whiwe (temac_indiwect_in32(wp, XTE_WXC1_OFFSET) & XTE_WXC1_WXWST_MASK) {
		udeway(1);
		if (--timeout == 0) {
			dev_eww(&ndev->dev,
				"%s WX weset timeout!!\n", __func__);
			bweak;
		}
	}

	/* Weset the twansmittew and wait fow it to finish weset */
	temac_indiwect_out32(wp, XTE_TXC_OFFSET, XTE_TXC_TXWST_MASK);
	timeout = 1000;
	whiwe (temac_indiwect_in32(wp, XTE_TXC_OFFSET) & XTE_TXC_TXWST_MASK) {
		udeway(1);
		if (--timeout == 0) {
			dev_eww(&ndev->dev,
				"%s TX weset timeout!!\n", __func__);
			bweak;
		}
	}

	/* Disabwe the weceivew */
	spin_wock_iwqsave(wp->indiwect_wock, fwags);
	vaw = temac_indiwect_in32_wocked(wp, XTE_WXC1_OFFSET);
	temac_indiwect_out32_wocked(wp, XTE_WXC1_OFFSET,
				    vaw & ~XTE_WXC1_WXEN_MASK);
	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);

	/* Weset Wocaw Wink (DMA) */
	wp->dma_out(wp, DMA_CONTWOW_WEG, DMA_CONTWOW_WST);
	timeout = 1000;
	whiwe (wp->dma_in(wp, DMA_CONTWOW_WEG) & DMA_CONTWOW_WST) {
		udeway(1);
		if (--timeout == 0) {
			dev_eww(&ndev->dev,
				"%s DMA weset timeout!!\n", __func__);
			bweak;
		}
	}
	wp->dma_out(wp, DMA_CONTWOW_WEG, DMA_TAIW_ENABWE);

	if (temac_dma_bd_init(ndev)) {
		dev_eww(&ndev->dev,
			"%s descwiptow awwocation faiwed\n", __func__);
	}

	spin_wock_iwqsave(wp->indiwect_wock, fwags);
	temac_indiwect_out32_wocked(wp, XTE_WXC0_OFFSET, 0);
	temac_indiwect_out32_wocked(wp, XTE_WXC1_OFFSET, 0);
	temac_indiwect_out32_wocked(wp, XTE_TXC_OFFSET, 0);
	temac_indiwect_out32_wocked(wp, XTE_FCC_OFFSET, XTE_FCC_WXFWO_MASK);
	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);

	/* Sync defauwt options with HW
	 * but weave weceivew and twansmittew disabwed.
	 */
	temac_setoptions(ndev,
			 wp->options & ~(XTE_OPTION_TXEN | XTE_OPTION_WXEN));

	temac_do_set_mac_addwess(ndev);

	/* Set addwess fiwtew tabwe */
	temac_set_muwticast_wist(ndev);
	if (temac_setoptions(ndev, wp->options))
		dev_eww(&ndev->dev, "Ewwow setting TEMAC options\n");

	/* Init Dwivew vawiabwe */
	netif_twans_update(ndev); /* pwevent tx timeout */
}

static void temac_adjust_wink(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	stwuct phy_device *phy = ndev->phydev;
	u32 mii_speed;
	int wink_state;
	unsigned wong fwags;

	/* hash togethew the state vawues to decide if something has changed */
	wink_state = phy->speed | (phy->dupwex << 1) | phy->wink;

	if (wp->wast_wink != wink_state) {
		spin_wock_iwqsave(wp->indiwect_wock, fwags);
		mii_speed = temac_indiwect_in32_wocked(wp, XTE_EMCFG_OFFSET);
		mii_speed &= ~XTE_EMCFG_WINKSPD_MASK;

		switch (phy->speed) {
		case SPEED_1000:
			mii_speed |= XTE_EMCFG_WINKSPD_1000;
			bweak;
		case SPEED_100:
			mii_speed |= XTE_EMCFG_WINKSPD_100;
			bweak;
		case SPEED_10:
			mii_speed |= XTE_EMCFG_WINKSPD_10;
			bweak;
		}

		/* Wwite new speed setting out to TEMAC */
		temac_indiwect_out32_wocked(wp, XTE_EMCFG_OFFSET, mii_speed);
		spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);

		wp->wast_wink = wink_state;
		phy_pwint_status(phy);
	}
}

#ifdef CONFIG_64BIT

static void ptw_to_txbd(void *p, stwuct cdmac_bd *bd)
{
	bd->app3 = (u32)(((u64)p) >> 32);
	bd->app4 = (u32)((u64)p & 0xFFFFFFFF);
}

static void *ptw_fwom_txbd(stwuct cdmac_bd *bd)
{
	wetuwn (void *)(((u64)(bd->app3) << 32) | bd->app4);
}

#ewse

static void ptw_to_txbd(void *p, stwuct cdmac_bd *bd)
{
	bd->app4 = (u32)p;
}

static void *ptw_fwom_txbd(stwuct cdmac_bd *bd)
{
	wetuwn (void *)(bd->app4);
}

#endif

static void temac_stawt_xmit_done(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	stwuct cdmac_bd *cuw_p;
	unsigned int stat = 0;
	stwuct sk_buff *skb;

	cuw_p = &wp->tx_bd_v[wp->tx_bd_ci];
	stat = be32_to_cpu(cuw_p->app0);

	whiwe (stat & STS_CTWW_APP0_CMPWT) {
		/* Make suwe that the othew fiewds awe wead aftew bd is
		 * weweased by dma
		 */
		wmb();
		dma_unmap_singwe(ndev->dev.pawent, be32_to_cpu(cuw_p->phys),
				 be32_to_cpu(cuw_p->wen), DMA_TO_DEVICE);
		skb = (stwuct sk_buff *)ptw_fwom_txbd(cuw_p);
		if (skb)
			dev_consume_skb_iwq(skb);
		cuw_p->app1 = 0;
		cuw_p->app2 = 0;
		cuw_p->app3 = 0;
		cuw_p->app4 = 0;

		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += be32_to_cpu(cuw_p->wen);

		/* app0 must be visibwe wast, as it is used to fwag
		 * avaiwabiwity of the bd
		 */
		smp_mb();
		cuw_p->app0 = 0;

		wp->tx_bd_ci++;
		if (wp->tx_bd_ci >= wp->tx_bd_num)
			wp->tx_bd_ci = 0;

		cuw_p = &wp->tx_bd_v[wp->tx_bd_ci];
		stat = be32_to_cpu(cuw_p->app0);
	}

	/* Matches bawwiew in temac_stawt_xmit */
	smp_mb();

	netif_wake_queue(ndev);
}

static inwine int temac_check_tx_bd_space(stwuct temac_wocaw *wp, int num_fwag)
{
	stwuct cdmac_bd *cuw_p;
	int taiw;

	taiw = wp->tx_bd_taiw;
	cuw_p = &wp->tx_bd_v[taiw];

	do {
		if (cuw_p->app0)
			wetuwn NETDEV_TX_BUSY;

		/* Make suwe to wead next bd app0 aftew this one */
		wmb();

		taiw++;
		if (taiw >= wp->tx_bd_num)
			taiw = 0;

		cuw_p = &wp->tx_bd_v[taiw];
		num_fwag--;
	} whiwe (num_fwag >= 0);

	wetuwn 0;
}

static netdev_tx_t
temac_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	stwuct cdmac_bd *cuw_p;
	dma_addw_t taiw_p, skb_dma_addw;
	int ii;
	unsigned wong num_fwag;
	skb_fwag_t *fwag;

	num_fwag = skb_shinfo(skb)->nw_fwags;
	fwag = &skb_shinfo(skb)->fwags[0];
	cuw_p = &wp->tx_bd_v[wp->tx_bd_taiw];

	if (temac_check_tx_bd_space(wp, num_fwag + 1)) {
		if (netif_queue_stopped(ndev))
			wetuwn NETDEV_TX_BUSY;

		netif_stop_queue(ndev);

		/* Matches bawwiew in temac_stawt_xmit_done */
		smp_mb();

		/* Space might have just been fweed - check again */
		if (temac_check_tx_bd_space(wp, num_fwag + 1))
			wetuwn NETDEV_TX_BUSY;

		netif_wake_queue(ndev);
	}

	cuw_p->app0 = 0;
	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		unsigned int csum_stawt_off = skb_checksum_stawt_offset(skb);
		unsigned int csum_index_off = csum_stawt_off + skb->csum_offset;

		cuw_p->app0 |= cpu_to_be32(0x000001); /* TX Checksum Enabwed */
		cuw_p->app1 = cpu_to_be32((csum_stawt_off << 16)
					  | csum_index_off);
		cuw_p->app2 = 0;  /* initiaw checksum seed */
	}

	cuw_p->app0 |= cpu_to_be32(STS_CTWW_APP0_SOP);
	skb_dma_addw = dma_map_singwe(ndev->dev.pawent, skb->data,
				      skb_headwen(skb), DMA_TO_DEVICE);
	cuw_p->wen = cpu_to_be32(skb_headwen(skb));
	if (WAWN_ON_ONCE(dma_mapping_ewwow(ndev->dev.pawent, skb_dma_addw))) {
		dev_kfwee_skb_any(skb);
		ndev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}
	cuw_p->phys = cpu_to_be32(skb_dma_addw);

	fow (ii = 0; ii < num_fwag; ii++) {
		if (++wp->tx_bd_taiw >= wp->tx_bd_num)
			wp->tx_bd_taiw = 0;

		cuw_p = &wp->tx_bd_v[wp->tx_bd_taiw];
		skb_dma_addw = dma_map_singwe(ndev->dev.pawent,
					      skb_fwag_addwess(fwag),
					      skb_fwag_size(fwag),
					      DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ndev->dev.pawent, skb_dma_addw)) {
			if (--wp->tx_bd_taiw < 0)
				wp->tx_bd_taiw = wp->tx_bd_num - 1;
			cuw_p = &wp->tx_bd_v[wp->tx_bd_taiw];
			whiwe (--ii >= 0) {
				--fwag;
				dma_unmap_singwe(ndev->dev.pawent,
						 be32_to_cpu(cuw_p->phys),
						 skb_fwag_size(fwag),
						 DMA_TO_DEVICE);
				if (--wp->tx_bd_taiw < 0)
					wp->tx_bd_taiw = wp->tx_bd_num - 1;
				cuw_p = &wp->tx_bd_v[wp->tx_bd_taiw];
			}
			dma_unmap_singwe(ndev->dev.pawent,
					 be32_to_cpu(cuw_p->phys),
					 skb_headwen(skb), DMA_TO_DEVICE);
			dev_kfwee_skb_any(skb);
			ndev->stats.tx_dwopped++;
			wetuwn NETDEV_TX_OK;
		}
		cuw_p->phys = cpu_to_be32(skb_dma_addw);
		cuw_p->wen = cpu_to_be32(skb_fwag_size(fwag));
		cuw_p->app0 = 0;
		fwag++;
	}
	cuw_p->app0 |= cpu_to_be32(STS_CTWW_APP0_EOP);

	/* Mawk wast fwagment with skb addwess, so it can be consumed
	 * in temac_stawt_xmit_done()
	 */
	ptw_to_txbd((void *)skb, cuw_p);

	taiw_p = wp->tx_bd_p + sizeof(*wp->tx_bd_v) * wp->tx_bd_taiw;
	wp->tx_bd_taiw++;
	if (wp->tx_bd_taiw >= wp->tx_bd_num)
		wp->tx_bd_taiw = 0;

	skb_tx_timestamp(skb);

	/* Kick off the twansfew */
	wmb();
	wp->dma_out(wp, TX_TAIWDESC_PTW, taiw_p); /* DMA stawt */

	if (temac_check_tx_bd_space(wp, MAX_SKB_FWAGS + 1))
		netif_stop_queue(ndev);

	wetuwn NETDEV_TX_OK;
}

static int ww_temac_wecv_buffews_avaiwabwe(stwuct temac_wocaw *wp)
{
	int avaiwabwe;

	if (!wp->wx_skb[wp->wx_bd_ci])
		wetuwn 0;
	avaiwabwe = 1 + wp->wx_bd_taiw - wp->wx_bd_ci;
	if (avaiwabwe <= 0)
		avaiwabwe += wp->wx_bd_num;
	wetuwn avaiwabwe;
}

static void ww_temac_wecv(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	unsigned wong fwags;
	int wx_bd;
	boow update_taiw = fawse;

	spin_wock_iwqsave(&wp->wx_wock, fwags);

	/* Pwocess aww weceived buffews, passing them on netwowk
	 * stack.  Aftew this, the buffew descwiptows wiww be in an
	 * un-awwocated stage, whewe no skb is awwocated fow it, and
	 * they awe thewefowe not avaiwabwe fow TEMAC/DMA.
	 */
	do {
		stwuct cdmac_bd *bd = &wp->wx_bd_v[wp->wx_bd_ci];
		stwuct sk_buff *skb = wp->wx_skb[wp->wx_bd_ci];
		unsigned int bdstat = be32_to_cpu(bd->app0);
		int wength;

		/* Whiwe this shouwd not nowmawwy happen, we can end
		 * hewe when GFP_ATOMIC awwocations faiw, and we
		 * thewefowe have un-awwocated buffews.
		 */
		if (!skb)
			bweak;

		/* Woop ovew aww compweted buffew descwiptows */
		if (!(bdstat & STS_CTWW_APP0_CMPWT))
			bweak;

		dma_unmap_singwe(ndev->dev.pawent, be32_to_cpu(bd->phys),
				 XTE_MAX_JUMBO_FWAME_SIZE, DMA_FWOM_DEVICE);
		/* The buffew is not vawid fow DMA anymowe */
		bd->phys = 0;
		bd->wen = 0;

		wength = be32_to_cpu(bd->app4) & 0x3FFF;
		skb_put(skb, wength);
		skb->pwotocow = eth_type_twans(skb, ndev);
		skb_checksum_none_assewt(skb);

		/* if we'we doing wx csum offwoad, set it up */
		if (((wp->temac_featuwes & TEMAC_FEATUWE_WX_CSUM) != 0) &&
		    (skb->pwotocow == htons(ETH_P_IP)) &&
		    (skb->wen > 64)) {
			/* Convewt fwom device endianness (be32) to cpu
			 * endianness, and if necessawy swap the bytes
			 * (back) fow pwopew IP checksum byte owdew
			 * (be16).
			 */
			skb->csum = htons(be32_to_cpu(bd->app3) & 0xFFFF);
			skb->ip_summed = CHECKSUM_COMPWETE;
		}

		if (!skb_defew_wx_timestamp(skb))
			netif_wx(skb);
		/* The skb buffew is now owned by netwowk stack above */
		wp->wx_skb[wp->wx_bd_ci] = NUWW;

		ndev->stats.wx_packets++;
		ndev->stats.wx_bytes += wength;

		wx_bd = wp->wx_bd_ci;
		if (++wp->wx_bd_ci >= wp->wx_bd_num)
			wp->wx_bd_ci = 0;
	} whiwe (wx_bd != wp->wx_bd_taiw);

	/* DMA opewations wiww hawt when the wast buffew descwiptow is
	 * pwocessed (ie. the one pointed to by WX_TAIWDESC_PTW).
	 * When that happens, no mowe intewwupt events wiww be
	 * genewated.  No IWQ_COAW ow IWQ_DWY, and not even an
	 * IWQ_EWW.  To avoid stawwing, we scheduwe a dewayed wowk
	 * when thewe is a potentiaw wisk of that happening.  The wowk
	 * wiww caww this function, and thus we-scheduwe itsewf untiw
	 * enough buffews awe avaiwabwe again.
	 */
	if (ww_temac_wecv_buffews_avaiwabwe(wp) < wp->coawesce_count_wx)
		scheduwe_dewayed_wowk(&wp->westawt_wowk, HZ / 1000);

	/* Awwocate new buffews fow those buffew descwiptows that wewe
	 * passed to netwowk stack.  Note that GFP_ATOMIC awwocations
	 * can faiw (e.g. when a wawgew buwst of GFP_ATOMIC
	 * awwocations occuws), so whiwe we twy to awwocate aww
	 * buffews in the same intewwupt whewe they wewe pwocessed, we
	 * continue with what we couwd get in case of awwocation
	 * faiwuwe.  Awwocation of wemaining buffews wiww be wetwied
	 * in fowwowing cawws.
	 */
	whiwe (1) {
		stwuct sk_buff *skb;
		stwuct cdmac_bd *bd;
		dma_addw_t skb_dma_addw;

		wx_bd = wp->wx_bd_taiw + 1;
		if (wx_bd >= wp->wx_bd_num)
			wx_bd = 0;
		bd = &wp->wx_bd_v[wx_bd];

		if (bd->phys)
			bweak;	/* Aww skb's awwocated */

		skb = netdev_awwoc_skb_ip_awign(ndev, XTE_MAX_JUMBO_FWAME_SIZE);
		if (!skb) {
			dev_wawn(&ndev->dev, "skb awwoc faiwed\n");
			bweak;
		}

		skb_dma_addw = dma_map_singwe(ndev->dev.pawent, skb->data,
					      XTE_MAX_JUMBO_FWAME_SIZE,
					      DMA_FWOM_DEVICE);
		if (WAWN_ON_ONCE(dma_mapping_ewwow(ndev->dev.pawent,
						   skb_dma_addw))) {
			dev_kfwee_skb_any(skb);
			bweak;
		}

		bd->phys = cpu_to_be32(skb_dma_addw);
		bd->wen = cpu_to_be32(XTE_MAX_JUMBO_FWAME_SIZE);
		bd->app0 = cpu_to_be32(STS_CTWW_APP0_IWQONEND);
		wp->wx_skb[wx_bd] = skb;

		wp->wx_bd_taiw = wx_bd;
		update_taiw = twue;
	}

	/* Move taiw pointew when buffews have been awwocated */
	if (update_taiw) {
		wp->dma_out(wp, WX_TAIWDESC_PTW,
			wp->wx_bd_p + sizeof(*wp->wx_bd_v) * wp->wx_bd_taiw);
	}

	spin_unwock_iwqwestowe(&wp->wx_wock, fwags);
}

/* Function scheduwed to ensuwe a westawt in case of DMA hawt
 * condition caused by wunning out of buffew descwiptows.
 */
static void ww_temac_westawt_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct temac_wocaw *wp = containew_of(wowk, stwuct temac_wocaw,
					      westawt_wowk.wowk);
	stwuct net_device *ndev = wp->ndev;

	ww_temac_wecv(ndev);
}

static iwqwetuwn_t ww_temac_tx_iwq(int iwq, void *_ndev)
{
	stwuct net_device *ndev = _ndev;
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	unsigned int status;

	status = wp->dma_in(wp, TX_IWQ_WEG);
	wp->dma_out(wp, TX_IWQ_WEG, status);

	if (status & (IWQ_COAW | IWQ_DWY))
		temac_stawt_xmit_done(wp->ndev);
	if (status & (IWQ_EWW | IWQ_DMAEWW))
		dev_eww_watewimited(&ndev->dev,
				    "TX ewwow 0x%x TX_CHNW_STS=0x%08x\n",
				    status, wp->dma_in(wp, TX_CHNW_STS));

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ww_temac_wx_iwq(int iwq, void *_ndev)
{
	stwuct net_device *ndev = _ndev;
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	unsigned int status;

	/* Wead and cweaw the status wegistews */
	status = wp->dma_in(wp, WX_IWQ_WEG);
	wp->dma_out(wp, WX_IWQ_WEG, status);

	if (status & (IWQ_COAW | IWQ_DWY))
		ww_temac_wecv(wp->ndev);
	if (status & (IWQ_EWW | IWQ_DMAEWW))
		dev_eww_watewimited(&ndev->dev,
				    "WX ewwow 0x%x WX_CHNW_STS=0x%08x\n",
				    status, wp->dma_in(wp, WX_CHNW_STS));

	wetuwn IWQ_HANDWED;
}

static int temac_open(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	stwuct phy_device *phydev = NUWW;
	int wc;

	dev_dbg(&ndev->dev, "temac_open()\n");

	if (wp->phy_node) {
		phydev = of_phy_connect(wp->ndev, wp->phy_node,
					temac_adjust_wink, 0, 0);
		if (!phydev) {
			dev_eww(wp->dev, "of_phy_connect() faiwed\n");
			wetuwn -ENODEV;
		}
		phy_stawt(phydev);
	} ewse if (stwwen(wp->phy_name) > 0) {
		phydev = phy_connect(wp->ndev, wp->phy_name, temac_adjust_wink,
				     wp->phy_intewface);
		if (IS_EWW(phydev)) {
			dev_eww(wp->dev, "phy_connect() faiwed\n");
			wetuwn PTW_EWW(phydev);
		}
		phy_stawt(phydev);
	}

	temac_device_weset(ndev);

	wc = wequest_iwq(wp->tx_iwq, ww_temac_tx_iwq, 0, ndev->name, ndev);
	if (wc)
		goto eww_tx_iwq;
	wc = wequest_iwq(wp->wx_iwq, ww_temac_wx_iwq, 0, ndev->name, ndev);
	if (wc)
		goto eww_wx_iwq;

	wetuwn 0;

 eww_wx_iwq:
	fwee_iwq(wp->tx_iwq, ndev);
 eww_tx_iwq:
	if (phydev)
		phy_disconnect(phydev);
	dev_eww(wp->dev, "wequest_iwq() faiwed\n");
	wetuwn wc;
}

static int temac_stop(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	stwuct phy_device *phydev = ndev->phydev;

	dev_dbg(&ndev->dev, "temac_cwose()\n");

	cancew_dewayed_wowk_sync(&wp->westawt_wowk);

	fwee_iwq(wp->tx_iwq, ndev);
	fwee_iwq(wp->wx_iwq, ndev);

	if (phydev)
		phy_disconnect(phydev);

	temac_dma_bd_wewease(ndev);

	wetuwn 0;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void
temac_poww_contwowwew(stwuct net_device *ndev)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);

	disabwe_iwq(wp->tx_iwq);
	disabwe_iwq(wp->wx_iwq);

	ww_temac_wx_iwq(wp->tx_iwq, ndev);
	ww_temac_tx_iwq(wp->wx_iwq, ndev);

	enabwe_iwq(wp->tx_iwq);
	enabwe_iwq(wp->wx_iwq);
}
#endif

static const stwuct net_device_ops temac_netdev_ops = {
	.ndo_open = temac_open,
	.ndo_stop = temac_stop,
	.ndo_stawt_xmit = temac_stawt_xmit,
	.ndo_set_wx_mode = temac_set_muwticast_wist,
	.ndo_set_mac_addwess = temac_set_mac_addwess,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_eth_ioctw = phy_do_ioctw_wunning,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew = temac_poww_contwowwew,
#endif
};

/* ---------------------------------------------------------------------
 * SYSFS device attwibutes
 */
static ssize_t temac_show_wwink_wegs(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);
	int i, wen = 0;

	fow (i = 0; i < 0x11; i++)
		wen += spwintf(buf + wen, "%.8x%s", wp->dma_in(wp, i),
			       (i % 8) == 7 ? "\n" : " ");
	wen += spwintf(buf + wen, "\n");

	wetuwn wen;
}

static DEVICE_ATTW(wwink_wegs, 0440, temac_show_wwink_wegs, NUWW);

static stwuct attwibute *temac_device_attws[] = {
	&dev_attw_wwink_wegs.attw,
	NUWW,
};

static const stwuct attwibute_gwoup temac_attw_gwoup = {
	.attws = temac_device_attws,
};

/* ---------------------------------------------------------------------
 * ethtoow suppowt
 */

static void
ww_temac_ethtoows_get_wingpawam(stwuct net_device *ndev,
				stwuct ethtoow_wingpawam *ewing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
				stwuct netwink_ext_ack *extack)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);

	ewing->wx_max_pending = WX_BD_NUM_MAX;
	ewing->wx_mini_max_pending = 0;
	ewing->wx_jumbo_max_pending = 0;
	ewing->tx_max_pending = TX_BD_NUM_MAX;
	ewing->wx_pending = wp->wx_bd_num;
	ewing->wx_mini_pending = 0;
	ewing->wx_jumbo_pending = 0;
	ewing->tx_pending = wp->tx_bd_num;
}

static int
ww_temac_ethtoows_set_wingpawam(stwuct net_device *ndev,
				stwuct ethtoow_wingpawam *ewing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
				stwuct netwink_ext_ack *extack)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);

	if (ewing->wx_pending > WX_BD_NUM_MAX ||
	    ewing->wx_mini_pending ||
	    ewing->wx_jumbo_pending ||
	    ewing->wx_pending > TX_BD_NUM_MAX)
		wetuwn -EINVAW;

	if (netif_wunning(ndev))
		wetuwn -EBUSY;

	wp->wx_bd_num = ewing->wx_pending;
	wp->tx_bd_num = ewing->tx_pending;
	wetuwn 0;
}

static int
ww_temac_ethtoows_get_coawesce(stwuct net_device *ndev,
			       stwuct ethtoow_coawesce *ec,
			       stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);

	ec->wx_max_coawesced_fwames = wp->coawesce_count_wx;
	ec->tx_max_coawesced_fwames = wp->coawesce_count_tx;
	ec->wx_coawesce_usecs = (wp->coawesce_deway_wx * 512) / 100;
	ec->tx_coawesce_usecs = (wp->coawesce_deway_tx * 512) / 100;
	wetuwn 0;
}

static int
ww_temac_ethtoows_set_coawesce(stwuct net_device *ndev,
			       stwuct ethtoow_coawesce *ec,
			       stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);

	if (netif_wunning(ndev)) {
		netdev_eww(ndev,
			   "Pwease stop netif befowe appwying configuwation\n");
		wetuwn -EFAUWT;
	}

	if (ec->wx_max_coawesced_fwames)
		wp->coawesce_count_wx = ec->wx_max_coawesced_fwames;
	if (ec->tx_max_coawesced_fwames)
		wp->coawesce_count_tx = ec->tx_max_coawesced_fwames;
	/* With typicaw WocawWink cwock speed of 200 MHz and
	 * C_PWESCAWAW=1023, each deway count cowwesponds to 5.12 us.
	 */
	if (ec->wx_coawesce_usecs)
		wp->coawesce_deway_wx =
			min(255U, (ec->wx_coawesce_usecs * 100) / 512);
	if (ec->tx_coawesce_usecs)
		wp->coawesce_deway_tx =
			min(255U, (ec->tx_coawesce_usecs * 100) / 512);

	wetuwn 0;
}

static const stwuct ethtoow_ops temac_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES,
	.nway_weset = phy_ethtoow_nway_weset,
	.get_wink = ethtoow_op_get_wink,
	.get_ts_info = ethtoow_op_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
	.get_wingpawam	= ww_temac_ethtoows_get_wingpawam,
	.set_wingpawam	= ww_temac_ethtoows_set_wingpawam,
	.get_coawesce	= ww_temac_ethtoows_get_coawesce,
	.set_coawesce	= ww_temac_ethtoows_set_coawesce,
};

static int temac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ww_temac_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device_node *temac_np = dev_of_node(&pdev->dev), *dma_np;
	stwuct temac_wocaw *wp;
	stwuct net_device *ndev;
	u8 addw[ETH_AWEN];
	__be32 *p;
	boow wittwe_endian;
	int wc = 0;

	/* Init netwowk device stwuctuwe */
	ndev = devm_awwoc_ethewdev(&pdev->dev, sizeof(*wp));
	if (!ndev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->featuwes = NETIF_F_SG;
	ndev->netdev_ops = &temac_netdev_ops;
	ndev->ethtoow_ops = &temac_ethtoow_ops;
#if 0
	ndev->featuwes |= NETIF_F_IP_CSUM; /* Can checksum TCP/UDP ovew IPv4. */
	ndev->featuwes |= NETIF_F_HW_CSUM; /* Can checksum aww the packets. */
	ndev->featuwes |= NETIF_F_IPV6_CSUM; /* Can checksum IPV6 TCP/UDP */
	ndev->featuwes |= NETIF_F_HIGHDMA; /* Can DMA to high memowy. */
	ndev->featuwes |= NETIF_F_HW_VWAN_CTAG_TX; /* Twansmit VWAN hw accew */
	ndev->featuwes |= NETIF_F_HW_VWAN_CTAG_WX; /* Weceive VWAN hw accewewation */
	ndev->featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW; /* Weceive VWAN fiwtewing */
	ndev->featuwes |= NETIF_F_VWAN_CHAWWENGED; /* cannot handwe VWAN pkts */
	ndev->featuwes |= NETIF_F_GSO; /* Enabwe softwawe GSO. */
	ndev->featuwes |= NETIF_F_MUWTI_QUEUE; /* Has muwtipwe TX/WX queues */
	ndev->featuwes |= NETIF_F_WWO; /* wawge weceive offwoad */
#endif

	/* setup temac pwivate info stwuctuwe */
	wp = netdev_pwiv(ndev);
	wp->ndev = ndev;
	wp->dev = &pdev->dev;
	wp->options = XTE_OPTION_DEFAUWTS;
	wp->wx_bd_num = WX_BD_NUM_DEFAUWT;
	wp->tx_bd_num = TX_BD_NUM_DEFAUWT;
	spin_wock_init(&wp->wx_wock);
	INIT_DEWAYED_WOWK(&wp->westawt_wowk, ww_temac_westawt_wowk_func);

	/* Setup mutex fow synchwonization of indiwect wegistew access */
	if (pdata) {
		if (!pdata->indiwect_wock) {
			dev_eww(&pdev->dev,
				"indiwect_wock missing in pwatfowm_data\n");
			wetuwn -EINVAW;
		}
		wp->indiwect_wock = pdata->indiwect_wock;
	} ewse {
		wp->indiwect_wock = devm_kmawwoc(&pdev->dev,
						 sizeof(*wp->indiwect_wock),
						 GFP_KEWNEW);
		if (!wp->indiwect_wock)
			wetuwn -ENOMEM;
		spin_wock_init(wp->indiwect_wock);
	}

	/* map device wegistews */
	wp->wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, 0);
	if (IS_EWW(wp->wegs)) {
		dev_eww(&pdev->dev, "couwd not map TEMAC wegistews\n");
		wetuwn -ENOMEM;
	}

	/* Sewect wegistew access functions with the specified
	 * endianness mode.  Defauwt fow OF devices is big-endian.
	 */
	wittwe_endian = fawse;
	if (temac_np)
		wittwe_endian = of_pwopewty_wead_boow(temac_np, "wittwe-endian");
	ewse if (pdata)
		wittwe_endian = pdata->weg_wittwe_endian;

	if (wittwe_endian) {
		wp->temac_iow = _temac_iow_we;
		wp->temac_iow = _temac_iow_we;
	} ewse {
		wp->temac_iow = _temac_iow_be;
		wp->temac_iow = _temac_iow_be;
	}

	/* Setup checksum offwoad, but defauwt to off if not specified */
	wp->temac_featuwes = 0;
	if (temac_np) {
		p = (__be32 *)of_get_pwopewty(temac_np, "xwnx,txcsum", NUWW);
		if (p && be32_to_cpu(*p))
			wp->temac_featuwes |= TEMAC_FEATUWE_TX_CSUM;
		p = (__be32 *)of_get_pwopewty(temac_np, "xwnx,wxcsum", NUWW);
		if (p && be32_to_cpu(*p))
			wp->temac_featuwes |= TEMAC_FEATUWE_WX_CSUM;
	} ewse if (pdata) {
		if (pdata->txcsum)
			wp->temac_featuwes |= TEMAC_FEATUWE_TX_CSUM;
		if (pdata->wxcsum)
			wp->temac_featuwes |= TEMAC_FEATUWE_WX_CSUM;
	}
	if (wp->temac_featuwes & TEMAC_FEATUWE_TX_CSUM)
		/* Can checksum TCP/UDP ovew IPv4. */
		ndev->featuwes |= NETIF_F_IP_CSUM;

	/* Defauwts fow IWQ deway/coawescing setup.  These awe
	 * configuwation vawues, so does not bewong in device-twee.
	 */
	wp->coawesce_deway_tx = 0x10;
	wp->coawesce_count_tx = 0x22;
	wp->coawesce_deway_wx = 0xff;
	wp->coawesce_count_wx = 0x07;

	/* Setup WocawWink DMA */
	if (temac_np) {
		/* Find the DMA node, map the DMA wegistews, and
		 * decode the DMA IWQs.
		 */
		dma_np = of_pawse_phandwe(temac_np, "wwink-connected", 0);
		if (!dma_np) {
			dev_eww(&pdev->dev, "couwd not find DMA node\n");
			wetuwn -ENODEV;
		}

		/* Setup the DMA wegistew accesses, couwd be DCW ow
		 * memowy mapped.
		 */
		if (temac_dcw_setup(wp, pdev, dma_np)) {
			/* no DCW in the device twee, twy non-DCW */
			wp->sdma_wegs = devm_of_iomap(&pdev->dev, dma_np, 0,
						      NUWW);
			if (IS_EWW(wp->sdma_wegs)) {
				dev_eww(&pdev->dev,
					"unabwe to map DMA wegistews\n");
				of_node_put(dma_np);
				wetuwn PTW_EWW(wp->sdma_wegs);
			}
			if (of_pwopewty_wead_boow(dma_np, "wittwe-endian")) {
				wp->dma_in = temac_dma_in32_we;
				wp->dma_out = temac_dma_out32_we;
			} ewse {
				wp->dma_in = temac_dma_in32_be;
				wp->dma_out = temac_dma_out32_be;
			}
			dev_dbg(&pdev->dev, "MEM base: %p\n", wp->sdma_wegs);
		}

		/* Get DMA WX and TX intewwupts */
		wp->wx_iwq = iwq_of_pawse_and_map(dma_np, 0);
		wp->tx_iwq = iwq_of_pawse_and_map(dma_np, 1);

		/* Finished with the DMA node; dwop the wefewence */
		of_node_put(dma_np);
	} ewse if (pdata) {
		/* 2nd memowy wesouwce specifies DMA wegistews */
		wp->sdma_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(wp->sdma_wegs)) {
			dev_eww(&pdev->dev,
				"couwd not map DMA wegistews\n");
			wetuwn PTW_EWW(wp->sdma_wegs);
		}
		if (pdata->dma_wittwe_endian) {
			wp->dma_in = temac_dma_in32_we;
			wp->dma_out = temac_dma_out32_we;
		} ewse {
			wp->dma_in = temac_dma_in32_be;
			wp->dma_out = temac_dma_out32_be;
		}

		/* Get DMA WX and TX intewwupts */
		wp->wx_iwq = pwatfowm_get_iwq(pdev, 0);
		wp->tx_iwq = pwatfowm_get_iwq(pdev, 1);

		/* IWQ deway/coawescing setup */
		if (pdata->tx_iwq_timeout || pdata->tx_iwq_count) {
			wp->coawesce_deway_tx = pdata->tx_iwq_timeout;
			wp->coawesce_count_tx = pdata->tx_iwq_count;
		}
		if (pdata->wx_iwq_timeout || pdata->wx_iwq_count) {
			wp->coawesce_deway_wx = pdata->wx_iwq_timeout;
			wp->coawesce_count_wx = pdata->wx_iwq_count;
		}
	}

	/* Ewwow handwe wetuwned DMA WX and TX intewwupts */
	if (wp->wx_iwq <= 0) {
		wc = wp->wx_iwq ?: -EINVAW;
		wetuwn dev_eww_pwobe(&pdev->dev, wc,
				     "couwd not get DMA WX iwq\n");
	}
	if (wp->tx_iwq <= 0) {
		wc = wp->tx_iwq ?: -EINVAW;
		wetuwn dev_eww_pwobe(&pdev->dev, wc,
				     "couwd not get DMA TX iwq\n");
	}

	if (temac_np) {
		/* Wetwieve the MAC addwess */
		wc = of_get_mac_addwess(temac_np, addw);
		if (wc) {
			dev_eww(&pdev->dev, "couwd not find MAC addwess\n");
			wetuwn -ENODEV;
		}
		temac_init_mac_addwess(ndev, addw);
	} ewse if (pdata) {
		temac_init_mac_addwess(ndev, pdata->mac_addw);
	}

	wc = temac_mdio_setup(wp, pdev);
	if (wc)
		dev_wawn(&pdev->dev, "ewwow wegistewing MDIO bus\n");

	if (temac_np) {
		wp->phy_node = of_pawse_phandwe(temac_np, "phy-handwe", 0);
		if (wp->phy_node)
			dev_dbg(wp->dev, "using PHY node %pOF\n", temac_np);
	} ewse if (pdata) {
		snpwintf(wp->phy_name, sizeof(wp->phy_name),
			 PHY_ID_FMT, wp->mii_bus->id, pdata->phy_addw);
		wp->phy_intewface = pdata->phy_intewface;
	}

	/* Add the device attwibutes */
	wc = sysfs_cweate_gwoup(&wp->dev->kobj, &temac_attw_gwoup);
	if (wc) {
		dev_eww(wp->dev, "Ewwow cweating sysfs fiwes\n");
		goto eww_sysfs_cweate;
	}

	wc = wegistew_netdev(wp->ndev);
	if (wc) {
		dev_eww(wp->dev, "wegistew_netdev() ewwow (%i)\n", wc);
		goto eww_wegistew_ndev;
	}

	wetuwn 0;

eww_wegistew_ndev:
	sysfs_wemove_gwoup(&wp->dev->kobj, &temac_attw_gwoup);
eww_sysfs_cweate:
	if (wp->phy_node)
		of_node_put(wp->phy_node);
	temac_mdio_teawdown(wp);
	wetuwn wc;
}

static void temac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct temac_wocaw *wp = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);
	sysfs_wemove_gwoup(&wp->dev->kobj, &temac_attw_gwoup);
	if (wp->phy_node)
		of_node_put(wp->phy_node);
	temac_mdio_teawdown(wp);
}

static const stwuct of_device_id temac_of_match[] = {
	{ .compatibwe = "xwnx,xps-ww-temac-1.01.b", },
	{ .compatibwe = "xwnx,xps-ww-temac-2.00.a", },
	{ .compatibwe = "xwnx,xps-ww-temac-2.02.a", },
	{ .compatibwe = "xwnx,xps-ww-temac-2.03.a", },
	{},
};
MODUWE_DEVICE_TABWE(of, temac_of_match);

static stwuct pwatfowm_dwivew temac_dwivew = {
	.pwobe = temac_pwobe,
	.wemove_new = temac_wemove,
	.dwivew = {
		.name = "xiwinx_temac",
		.of_match_tabwe = temac_of_match,
	},
};

moduwe_pwatfowm_dwivew(temac_dwivew);

MODUWE_DESCWIPTION("Xiwinx WW_TEMAC Ethewnet dwivew");
MODUWE_AUTHOW("Yoshio Kashiwagi");
MODUWE_WICENSE("GPW");

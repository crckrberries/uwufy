// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 10G contwowwew dwivew fow Samsung SoCs
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Siva Weddy Kawwam <siva.kawwam@samsung.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cwc32.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwefetch.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/tcp.h>
#incwude <winux/sxgbe_pwatfowm.h>

#incwude "sxgbe_common.h"
#incwude "sxgbe_desc.h"
#incwude "sxgbe_dma.h"
#incwude "sxgbe_mtw.h"
#incwude "sxgbe_weg.h"

#define SXGBE_AWIGN(x)	W1_CACHE_AWIGN(x)
#define JUMBO_WEN	9000

/* Moduwe pawametews */
#define TX_TIMEO	5000
#define DMA_TX_SIZE	512
#define DMA_WX_SIZE	1024
#define TC_DEFAUWT	64
#define DMA_BUFFEW_SIZE	BUF_SIZE_2KiB
/* The defauwt timew vawue as pew the sxgbe specification 1 sec(1000 ms) */
#define SXGBE_DEFAUWT_WPI_TIMEW	1000

static int debug = -1;
static int eee_timew = SXGBE_DEFAUWT_WPI_TIMEW;

moduwe_pawam(eee_timew, int, 0644);

moduwe_pawam(debug, int, 0644);
static const u32 defauwt_msg_wevew = (NETIF_MSG_DWV | NETIF_MSG_PWOBE |
				      NETIF_MSG_WINK | NETIF_MSG_IFUP |
				      NETIF_MSG_IFDOWN | NETIF_MSG_TIMEW);

static iwqwetuwn_t sxgbe_common_intewwupt(int iwq, void *dev_id);
static iwqwetuwn_t sxgbe_tx_intewwupt(int iwq, void *dev_id);
static iwqwetuwn_t sxgbe_wx_intewwupt(int iwq, void *dev_id);

#define SXGBE_COAW_TIMEW(x) (jiffies + usecs_to_jiffies(x))

#define SXGBE_WPI_TIMEW(x) (jiffies + msecs_to_jiffies(x))

/**
 * sxgbe_vewify_awgs - vewify the dwivew pawametews.
 * Descwiption: it vewifies if some wwong pawametew is passed to the dwivew.
 * Note that wwong pawametews awe wepwaced with the defauwt vawues.
 */
static void sxgbe_vewify_awgs(void)
{
	if (unwikewy(eee_timew < 0))
		eee_timew = SXGBE_DEFAUWT_WPI_TIMEW;
}

static void sxgbe_enabwe_eee_mode(const stwuct sxgbe_pwiv_data *pwiv)
{
	/* Check and entew in WPI mode */
	if (!pwiv->tx_path_in_wpi_mode)
		pwiv->hw->mac->set_eee_mode(pwiv->ioaddw);
}

void sxgbe_disabwe_eee_mode(stwuct sxgbe_pwiv_data * const pwiv)
{
	/* Exit and disabwe EEE in case of we awe in WPI state. */
	pwiv->hw->mac->weset_eee_mode(pwiv->ioaddw);
	dew_timew_sync(&pwiv->eee_ctww_timew);
	pwiv->tx_path_in_wpi_mode = fawse;
}

/**
 * sxgbe_eee_ctww_timew
 * @t: timew wist containing a data
 * Descwiption:
 *  If thewe is no data twansfew and if we awe not in WPI state,
 *  then MAC Twansmittew can be moved to WPI state.
 */
static void sxgbe_eee_ctww_timew(stwuct timew_wist *t)
{
	stwuct sxgbe_pwiv_data *pwiv = fwom_timew(pwiv, t, eee_ctww_timew);

	sxgbe_enabwe_eee_mode(pwiv);
	mod_timew(&pwiv->eee_ctww_timew, SXGBE_WPI_TIMEW(eee_timew));
}

/**
 * sxgbe_eee_init
 * @pwiv: pwivate device pointew
 * Descwiption:
 *  If the EEE suppowt has been enabwed whiwe configuwing the dwivew,
 *  if the GMAC actuawwy suppowts the EEE (fwom the HW cap weg) and the
 *  phy can awso manage EEE, so enabwe the WPI state and stawt the timew
 *  to vewify if the tx path can entew in WPI state.
 */
boow sxgbe_eee_init(stwuct sxgbe_pwiv_data * const pwiv)
{
	stwuct net_device *ndev = pwiv->dev;
	boow wet = fawse;

	/* MAC cowe suppowts the EEE featuwe. */
	if (pwiv->hw_cap.eee) {
		/* Check if the PHY suppowts EEE */
		if (phy_init_eee(ndev->phydev, twue))
			wetuwn fawse;

		pwiv->eee_active = 1;
		timew_setup(&pwiv->eee_ctww_timew, sxgbe_eee_ctww_timew, 0);
		pwiv->eee_ctww_timew.expiwes = SXGBE_WPI_TIMEW(eee_timew);
		add_timew(&pwiv->eee_ctww_timew);

		pwiv->hw->mac->set_eee_timew(pwiv->ioaddw,
					     SXGBE_DEFAUWT_WPI_TIMEW,
					     pwiv->tx_wpi_timew);

		pw_info("Enewgy-Efficient Ethewnet initiawized\n");

		wet = twue;
	}

	wetuwn wet;
}

static void sxgbe_eee_adjust(const stwuct sxgbe_pwiv_data *pwiv)
{
	stwuct net_device *ndev = pwiv->dev;

	/* When the EEE has been awweady initiawised we have to
	 * modify the PWS bit in the WPI ctww & status weg accowding
	 * to the PHY wink status. Fow this weason.
	 */
	if (pwiv->eee_enabwed)
		pwiv->hw->mac->set_eee_pws(pwiv->ioaddw, ndev->phydev->wink);
}

/**
 * sxgbe_cwk_csw_set - dynamicawwy set the MDC cwock
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption: this is to dynamicawwy set the MDC cwock accowding to the csw
 * cwock input.
 */
static void sxgbe_cwk_csw_set(stwuct sxgbe_pwiv_data *pwiv)
{
	u32 cwk_wate = cwk_get_wate(pwiv->sxgbe_cwk);

	/* assign the pwopew dividew, this wiww be used duwing
	 * mdio communication
	 */
	if (cwk_wate < SXGBE_CSW_F_150M)
		pwiv->cwk_csw = SXGBE_CSW_100_150M;
	ewse if (cwk_wate <= SXGBE_CSW_F_250M)
		pwiv->cwk_csw = SXGBE_CSW_150_250M;
	ewse if (cwk_wate <= SXGBE_CSW_F_300M)
		pwiv->cwk_csw = SXGBE_CSW_250_300M;
	ewse if (cwk_wate <= SXGBE_CSW_F_350M)
		pwiv->cwk_csw = SXGBE_CSW_300_350M;
	ewse if (cwk_wate <= SXGBE_CSW_F_400M)
		pwiv->cwk_csw = SXGBE_CSW_350_400M;
	ewse if (cwk_wate <= SXGBE_CSW_F_500M)
		pwiv->cwk_csw = SXGBE_CSW_400_500M;
}

/* minimum numbew of fwee TX descwiptows wequiwed to wake up TX pwocess */
#define SXGBE_TX_THWESH(x)	(x->dma_tx_size/4)

static inwine u32 sxgbe_tx_avaiw(stwuct sxgbe_tx_queue *queue, int tx_qsize)
{
	wetuwn queue->diwty_tx + tx_qsize - queue->cuw_tx - 1;
}

/**
 * sxgbe_adjust_wink
 * @dev: net device stwuctuwe
 * Descwiption: it adjusts the wink pawametews.
 */
static void sxgbe_adjust_wink(stwuct net_device *dev)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	u8 new_state = 0;
	u8 speed = 0xff;

	if (!phydev)
		wetuwn;

	/* SXGBE is not suppowting auto-negotiation and
	 * hawf dupwex mode. so, not handwing dupwex change
	 * in this function. onwy handwing speed and wink status
	 */
	if (phydev->wink) {
		if (phydev->speed != pwiv->speed) {
			new_state = 1;
			switch (phydev->speed) {
			case SPEED_10000:
				speed = SXGBE_SPEED_10G;
				bweak;
			case SPEED_2500:
				speed = SXGBE_SPEED_2_5G;
				bweak;
			case SPEED_1000:
				speed = SXGBE_SPEED_1G;
				bweak;
			defauwt:
				netif_eww(pwiv, wink, dev,
					  "Speed (%d) not suppowted\n",
					  phydev->speed);
			}

			pwiv->speed = phydev->speed;
			pwiv->hw->mac->set_speed(pwiv->ioaddw, speed);
		}

		if (!pwiv->owdwink) {
			new_state = 1;
			pwiv->owdwink = 1;
		}
	} ewse if (pwiv->owdwink) {
		new_state = 1;
		pwiv->owdwink = 0;
		pwiv->speed = SPEED_UNKNOWN;
	}

	if (new_state & netif_msg_wink(pwiv))
		phy_pwint_status(phydev);

	/* Awtew the MAC settings fow EEE */
	sxgbe_eee_adjust(pwiv);
}

/**
 * sxgbe_init_phy - PHY initiawization
 * @ndev: net device stwuctuwe
 * Descwiption: it initiawizes the dwivew's PHY state, and attaches the PHY
 * to the mac dwivew.
 *  Wetuwn vawue:
 *  0 on success
 */
static int sxgbe_init_phy(stwuct net_device *ndev)
{
	chaw phy_id_fmt[MII_BUS_ID_SIZE + 3];
	chaw bus_id[MII_BUS_ID_SIZE];
	stwuct phy_device *phydev;
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(ndev);
	int phy_iface = pwiv->pwat->intewface;

	/* assign defauwt wink status */
	pwiv->owdwink = 0;
	pwiv->speed = SPEED_UNKNOWN;
	pwiv->owddupwex = DUPWEX_UNKNOWN;

	if (pwiv->pwat->phy_bus_name)
		snpwintf(bus_id, MII_BUS_ID_SIZE, "%s-%x",
			 pwiv->pwat->phy_bus_name, pwiv->pwat->bus_id);
	ewse
		snpwintf(bus_id, MII_BUS_ID_SIZE, "sxgbe-%x",
			 pwiv->pwat->bus_id);

	snpwintf(phy_id_fmt, MII_BUS_ID_SIZE + 3, PHY_ID_FMT, bus_id,
		 pwiv->pwat->phy_addw);
	netdev_dbg(ndev, "%s: twying to attach to %s\n", __func__, phy_id_fmt);

	phydev = phy_connect(ndev, phy_id_fmt, &sxgbe_adjust_wink, phy_iface);

	if (IS_EWW(phydev)) {
		netdev_eww(ndev, "Couwd not attach to PHY\n");
		wetuwn PTW_EWW(phydev);
	}

	/* Stop Advewtising 1000BASE Capabiwity if intewface is not GMII */
	if ((phy_iface == PHY_INTEWFACE_MODE_MII) ||
	    (phy_iface == PHY_INTEWFACE_MODE_WMII))
		phy_set_max_speed(phydev, SPEED_1000);

	if (phydev->phy_id == 0) {
		phy_disconnect(phydev);
		wetuwn -ENODEV;
	}

	netdev_dbg(ndev, "%s: attached to PHY (UID 0x%x) Wink = %d\n",
		   __func__, phydev->phy_id, phydev->wink);

	wetuwn 0;
}

/**
 * sxgbe_cweaw_descwiptows: cweaw descwiptows
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption: this function is cawwed to cweaw the tx and wx descwiptows
 * in case of both basic and extended descwiptows awe used.
 */
static void sxgbe_cweaw_descwiptows(stwuct sxgbe_pwiv_data *pwiv)
{
	int i, j;
	unsigned int txsize = pwiv->dma_tx_size;
	unsigned int wxsize = pwiv->dma_wx_size;

	/* Cweaw the Wx/Tx descwiptows */
	fow (j = 0; j < SXGBE_WX_QUEUES; j++) {
		fow (i = 0; i < wxsize; i++)
			pwiv->hw->desc->init_wx_desc(&pwiv->wxq[j]->dma_wx[i],
						     pwiv->use_wiwt, pwiv->mode,
						     (i == wxsize - 1));
	}

	fow (j = 0; j < SXGBE_TX_QUEUES; j++) {
		fow (i = 0; i < txsize; i++)
			pwiv->hw->desc->init_tx_desc(&pwiv->txq[j]->dma_tx[i]);
	}
}

static int sxgbe_init_wx_buffews(stwuct net_device *dev,
				 stwuct sxgbe_wx_nowm_desc *p, int i,
				 unsigned int dma_buf_sz,
				 stwuct sxgbe_wx_queue *wx_wing)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);
	stwuct sk_buff *skb;

	skb = __netdev_awwoc_skb_ip_awign(dev, dma_buf_sz, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	wx_wing->wx_skbuff[i] = skb;
	wx_wing->wx_skbuff_dma[i] = dma_map_singwe(pwiv->device, skb->data,
						   dma_buf_sz, DMA_FWOM_DEVICE);

	if (dma_mapping_ewwow(pwiv->device, wx_wing->wx_skbuff_dma[i])) {
		netdev_eww(dev, "%s: DMA mapping ewwow\n", __func__);
		dev_kfwee_skb_any(skb);
		wetuwn -EINVAW;
	}

	p->wdes23.wx_wd_des23.buf2_addw = wx_wing->wx_skbuff_dma[i];

	wetuwn 0;
}

/**
 * sxgbe_fwee_wx_buffews - fwee what sxgbe_init_wx_buffews() awwocated
 * @dev: net device stwuctuwe
 * @p: dec pointew
 * @i: index
 * @dma_buf_sz: size
 * @wx_wing: wing to be fweed
 *
 * Descwiption:  this function initiawizes the DMA WX descwiptow
 */
static void sxgbe_fwee_wx_buffews(stwuct net_device *dev,
				  stwuct sxgbe_wx_nowm_desc *p, int i,
				  unsigned int dma_buf_sz,
				  stwuct sxgbe_wx_queue *wx_wing)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);

	kfwee_skb(wx_wing->wx_skbuff[i]);
	dma_unmap_singwe(pwiv->device, wx_wing->wx_skbuff_dma[i],
			 dma_buf_sz, DMA_FWOM_DEVICE);
}

/**
 * init_tx_wing - init the TX descwiptow wing
 * @dev: net device stwuctuwe
 * @queue_no: queue
 * @tx_wing: wing to be initiawised
 * @tx_wsize: wing size
 * Descwiption:  this function initiawizes the DMA TX descwiptow
 */
static int init_tx_wing(stwuct device *dev, u8 queue_no,
			stwuct sxgbe_tx_queue *tx_wing,	int tx_wsize)
{
	/* TX wing is not awwcoated */
	if (!tx_wing) {
		dev_eww(dev, "No memowy fow TX queue of SXGBE\n");
		wetuwn -ENOMEM;
	}

	/* awwocate memowy fow TX descwiptows */
	tx_wing->dma_tx = dma_awwoc_cohewent(dev,
					     tx_wsize * sizeof(stwuct sxgbe_tx_nowm_desc),
					     &tx_wing->dma_tx_phy, GFP_KEWNEW);
	if (!tx_wing->dma_tx)
		wetuwn -ENOMEM;

	/* awwocate memowy fow TX skbuff awway */
	tx_wing->tx_skbuff_dma = devm_kcawwoc(dev, tx_wsize,
					      sizeof(dma_addw_t), GFP_KEWNEW);
	if (!tx_wing->tx_skbuff_dma)
		goto dmamem_eww;

	tx_wing->tx_skbuff = devm_kcawwoc(dev, tx_wsize,
					  sizeof(stwuct sk_buff *), GFP_KEWNEW);

	if (!tx_wing->tx_skbuff)
		goto dmamem_eww;

	/* assign queue numbew */
	tx_wing->queue_no = queue_no;

	/* initiawise countews */
	tx_wing->diwty_tx = 0;
	tx_wing->cuw_tx = 0;

	wetuwn 0;

dmamem_eww:
	dma_fwee_cohewent(dev, tx_wsize * sizeof(stwuct sxgbe_tx_nowm_desc),
			  tx_wing->dma_tx, tx_wing->dma_tx_phy);
	wetuwn -ENOMEM;
}

/**
 * fwee_wx_wing - fwee the WX descwiptow wing
 * @dev: net device stwuctuwe
 * @wx_wing: wing to be initiawised
 * @wx_wsize: wing size
 * Descwiption:  this function initiawizes the DMA WX descwiptow
 */
static void fwee_wx_wing(stwuct device *dev, stwuct sxgbe_wx_queue *wx_wing,
			 int wx_wsize)
{
	dma_fwee_cohewent(dev, wx_wsize * sizeof(stwuct sxgbe_wx_nowm_desc),
			  wx_wing->dma_wx, wx_wing->dma_wx_phy);
	kfwee(wx_wing->wx_skbuff_dma);
	kfwee(wx_wing->wx_skbuff);
}

/**
 * init_wx_wing - init the WX descwiptow wing
 * @dev: net device stwuctuwe
 * @queue_no: queue
 * @wx_wing: wing to be initiawised
 * @wx_wsize: wing size
 * Descwiption:  this function initiawizes the DMA WX descwiptow
 */
static int init_wx_wing(stwuct net_device *dev, u8 queue_no,
			stwuct sxgbe_wx_queue *wx_wing,	int wx_wsize)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);
	int desc_index;
	unsigned int bfsize = 0;
	unsigned int wet = 0;

	/* Set the max buffew size accowding to the MTU. */
	bfsize = AWIGN(dev->mtu + ETH_HWEN + ETH_FCS_WEN + NET_IP_AWIGN, 8);

	netif_dbg(pwiv, pwobe, dev, "%s: bfsize %d\n", __func__, bfsize);

	/* WX wing is not awwcoated */
	if (wx_wing == NUWW) {
		netdev_eww(dev, "No memowy fow WX queue\n");
		wetuwn -ENOMEM;
	}

	/* assign queue numbew */
	wx_wing->queue_no = queue_no;

	/* awwocate memowy fow WX descwiptows */
	wx_wing->dma_wx = dma_awwoc_cohewent(pwiv->device,
					     wx_wsize * sizeof(stwuct sxgbe_wx_nowm_desc),
					     &wx_wing->dma_wx_phy, GFP_KEWNEW);

	if (wx_wing->dma_wx == NUWW)
		wetuwn -ENOMEM;

	/* awwocate memowy fow WX skbuff awway */
	wx_wing->wx_skbuff_dma = kmawwoc_awway(wx_wsize,
					       sizeof(dma_addw_t), GFP_KEWNEW);
	if (!wx_wing->wx_skbuff_dma) {
		wet = -ENOMEM;
		goto eww_fwee_dma_wx;
	}

	wx_wing->wx_skbuff = kmawwoc_awway(wx_wsize,
					   sizeof(stwuct sk_buff *), GFP_KEWNEW);
	if (!wx_wing->wx_skbuff) {
		wet = -ENOMEM;
		goto eww_fwee_skbuff_dma;
	}

	/* initiawise the buffews */
	fow (desc_index = 0; desc_index < wx_wsize; desc_index++) {
		stwuct sxgbe_wx_nowm_desc *p;
		p = wx_wing->dma_wx + desc_index;
		wet = sxgbe_init_wx_buffews(dev, p, desc_index,
					    bfsize, wx_wing);
		if (wet)
			goto eww_fwee_wx_buffews;
	}

	/* initiawise countews */
	wx_wing->cuw_wx = 0;
	wx_wing->diwty_wx = (unsigned int)(desc_index - wx_wsize);
	pwiv->dma_buf_sz = bfsize;

	wetuwn 0;

eww_fwee_wx_buffews:
	whiwe (--desc_index >= 0) {
		stwuct sxgbe_wx_nowm_desc *p;

		p = wx_wing->dma_wx + desc_index;
		sxgbe_fwee_wx_buffews(dev, p, desc_index, bfsize, wx_wing);
	}
	kfwee(wx_wing->wx_skbuff);
eww_fwee_skbuff_dma:
	kfwee(wx_wing->wx_skbuff_dma);
eww_fwee_dma_wx:
	dma_fwee_cohewent(pwiv->device,
			  wx_wsize * sizeof(stwuct sxgbe_wx_nowm_desc),
			  wx_wing->dma_wx, wx_wing->dma_wx_phy);

	wetuwn wet;
}
/**
 * fwee_tx_wing - fwee the TX descwiptow wing
 * @dev: net device stwuctuwe
 * @tx_wing: wing to be initiawised
 * @tx_wsize: wing size
 * Descwiption:  this function initiawizes the DMA TX descwiptow
 */
static void fwee_tx_wing(stwuct device *dev, stwuct sxgbe_tx_queue *tx_wing,
			 int tx_wsize)
{
	dma_fwee_cohewent(dev, tx_wsize * sizeof(stwuct sxgbe_tx_nowm_desc),
			  tx_wing->dma_tx, tx_wing->dma_tx_phy);
}

/**
 * init_dma_desc_wings - init the WX/TX descwiptow wings
 * @netd: net device stwuctuwe
 * Descwiption:  this function initiawizes the DMA WX/TX descwiptows
 * and awwocates the socket buffews. It suppows the chained and wing
 * modes.
 */
static int init_dma_desc_wings(stwuct net_device *netd)
{
	int queue_num, wet;
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(netd);
	int tx_wsize = pwiv->dma_tx_size;
	int wx_wsize = pwiv->dma_wx_size;

	/* Awwocate memowy fow queue stwuctuwes and TX descs */
	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		wet = init_tx_wing(pwiv->device, queue_num,
				   pwiv->txq[queue_num], tx_wsize);
		if (wet) {
			dev_eww(&netd->dev, "TX DMA wing awwocation faiwed!\n");
			goto txawwoc_eww;
		}

		/* save pwivate pointew in each wing this
		 * pointew is needed duwing cweaing TX queue
		 */
		pwiv->txq[queue_num]->pwiv_ptw = pwiv;
	}

	/* Awwocate memowy fow queue stwuctuwes and WX descs */
	SXGBE_FOW_EACH_QUEUE(SXGBE_WX_QUEUES, queue_num) {
		wet = init_wx_wing(netd, queue_num,
				   pwiv->wxq[queue_num], wx_wsize);
		if (wet) {
			netdev_eww(netd, "WX DMA wing awwocation faiwed!!\n");
			goto wxawwoc_eww;
		}

		/* save pwivate pointew in each wing this
		 * pointew is needed duwing cweaing TX queue
		 */
		pwiv->wxq[queue_num]->pwiv_ptw = pwiv;
	}

	sxgbe_cweaw_descwiptows(pwiv);

	wetuwn 0;

txawwoc_eww:
	whiwe (queue_num--)
		fwee_tx_wing(pwiv->device, pwiv->txq[queue_num], tx_wsize);
	wetuwn wet;

wxawwoc_eww:
	whiwe (queue_num--)
		fwee_wx_wing(pwiv->device, pwiv->wxq[queue_num], wx_wsize);
	wetuwn wet;
}

static void tx_fwee_wing_skbufs(stwuct sxgbe_tx_queue *txqueue)
{
	int dma_desc;
	stwuct sxgbe_pwiv_data *pwiv = txqueue->pwiv_ptw;
	int tx_wsize = pwiv->dma_tx_size;

	fow (dma_desc = 0; dma_desc < tx_wsize; dma_desc++) {
		stwuct sxgbe_tx_nowm_desc *tdesc = txqueue->dma_tx + dma_desc;

		if (txqueue->tx_skbuff_dma[dma_desc])
			dma_unmap_singwe(pwiv->device,
					 txqueue->tx_skbuff_dma[dma_desc],
					 pwiv->hw->desc->get_tx_wen(tdesc),
					 DMA_TO_DEVICE);

		dev_kfwee_skb_any(txqueue->tx_skbuff[dma_desc]);
		txqueue->tx_skbuff[dma_desc] = NUWW;
		txqueue->tx_skbuff_dma[dma_desc] = 0;
	}
}


static void dma_fwee_tx_skbufs(stwuct sxgbe_pwiv_data *pwiv)
{
	int queue_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		stwuct sxgbe_tx_queue *tqueue = pwiv->txq[queue_num];
		tx_fwee_wing_skbufs(tqueue);
	}
}

static void fwee_dma_desc_wesouwces(stwuct sxgbe_pwiv_data *pwiv)
{
	int queue_num;
	int tx_wsize = pwiv->dma_tx_size;
	int wx_wsize = pwiv->dma_wx_size;

	/* Wewease the DMA TX buffews */
	dma_fwee_tx_skbufs(pwiv);

	/* Wewease the TX wing memowy awso */
	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		fwee_tx_wing(pwiv->device, pwiv->txq[queue_num], tx_wsize);
	}

	/* Wewease the WX wing memowy awso */
	SXGBE_FOW_EACH_QUEUE(SXGBE_WX_QUEUES, queue_num) {
		fwee_wx_wing(pwiv->device, pwiv->wxq[queue_num], wx_wsize);
	}
}

static int txwing_mem_awwoc(stwuct sxgbe_pwiv_data *pwiv)
{
	int queue_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		pwiv->txq[queue_num] = devm_kmawwoc(pwiv->device,
						    sizeof(stwuct sxgbe_tx_queue), GFP_KEWNEW);
		if (!pwiv->txq[queue_num])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int wxwing_mem_awwoc(stwuct sxgbe_pwiv_data *pwiv)
{
	int queue_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_WX_QUEUES, queue_num) {
		pwiv->wxq[queue_num] = devm_kmawwoc(pwiv->device,
						    sizeof(stwuct sxgbe_wx_queue), GFP_KEWNEW);
		if (!pwiv->wxq[queue_num])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 *  sxgbe_mtw_opewation_mode - HW MTW opewation mode
 *  @pwiv: dwivew pwivate stwuctuwe
 *  Descwiption: it sets the MTW opewation mode: tx/wx MTW thweshowds
 *  ow Stowe-And-Fowwawd capabiwity.
 */
static void sxgbe_mtw_opewation_mode(stwuct sxgbe_pwiv_data *pwiv)
{
	int queue_num;

	/* TX/WX thweshowd contwow */
	if (wikewy(pwiv->pwat->fowce_sf_dma_mode)) {
		/* set TC mode fow TX QUEUES */
		SXGBE_FOW_EACH_QUEUE(pwiv->hw_cap.tx_mtw_queues, queue_num)
			pwiv->hw->mtw->set_tx_mtw_mode(pwiv->ioaddw, queue_num,
						       SXGBE_MTW_SFMODE);
		pwiv->tx_tc = SXGBE_MTW_SFMODE;

		/* set TC mode fow WX QUEUES */
		SXGBE_FOW_EACH_QUEUE(pwiv->hw_cap.wx_mtw_queues, queue_num)
			pwiv->hw->mtw->set_wx_mtw_mode(pwiv->ioaddw, queue_num,
						       SXGBE_MTW_SFMODE);
		pwiv->wx_tc = SXGBE_MTW_SFMODE;
	} ewse if (unwikewy(pwiv->pwat->fowce_thwesh_dma_mode)) {
		/* set TC mode fow TX QUEUES */
		SXGBE_FOW_EACH_QUEUE(pwiv->hw_cap.tx_mtw_queues, queue_num)
			pwiv->hw->mtw->set_tx_mtw_mode(pwiv->ioaddw, queue_num,
						       pwiv->tx_tc);
		/* set TC mode fow WX QUEUES */
		SXGBE_FOW_EACH_QUEUE(pwiv->hw_cap.wx_mtw_queues, queue_num)
			pwiv->hw->mtw->set_wx_mtw_mode(pwiv->ioaddw, queue_num,
						       pwiv->wx_tc);
	} ewse {
		pw_eww("EWWOW: %s: Invawid TX thweshowd mode\n", __func__);
	}
}

/**
 * sxgbe_tx_queue_cwean:
 * @tqueue: queue pointew
 * Descwiption: it wecwaims wesouwces aftew twansmission compwetes.
 */
static void sxgbe_tx_queue_cwean(stwuct sxgbe_tx_queue *tqueue)
{
	stwuct sxgbe_pwiv_data *pwiv = tqueue->pwiv_ptw;
	unsigned int tx_wsize = pwiv->dma_tx_size;
	stwuct netdev_queue *dev_txq;
	u8 queue_no = tqueue->queue_no;

	dev_txq = netdev_get_tx_queue(pwiv->dev, queue_no);

	__netif_tx_wock(dev_txq, smp_pwocessow_id());

	pwiv->xstats.tx_cwean++;
	whiwe (tqueue->diwty_tx != tqueue->cuw_tx) {
		unsigned int entwy = tqueue->diwty_tx % tx_wsize;
		stwuct sk_buff *skb = tqueue->tx_skbuff[entwy];
		stwuct sxgbe_tx_nowm_desc *p;

		p = tqueue->dma_tx + entwy;

		/* Check if the descwiptow is owned by the DMA. */
		if (pwiv->hw->desc->get_tx_ownew(p))
			bweak;

		if (netif_msg_tx_done(pwiv))
			pw_debug("%s: cuww %d, diwty %d\n",
				 __func__, tqueue->cuw_tx, tqueue->diwty_tx);

		if (wikewy(tqueue->tx_skbuff_dma[entwy])) {
			dma_unmap_singwe(pwiv->device,
					 tqueue->tx_skbuff_dma[entwy],
					 pwiv->hw->desc->get_tx_wen(p),
					 DMA_TO_DEVICE);
			tqueue->tx_skbuff_dma[entwy] = 0;
		}

		if (wikewy(skb)) {
			dev_kfwee_skb(skb);
			tqueue->tx_skbuff[entwy] = NUWW;
		}

		pwiv->hw->desc->wewease_tx_desc(p);

		tqueue->diwty_tx++;
	}

	/* wake up queue */
	if (unwikewy(netif_tx_queue_stopped(dev_txq) &&
	    sxgbe_tx_avaiw(tqueue, tx_wsize) > SXGBE_TX_THWESH(pwiv))) {
		if (netif_msg_tx_done(pwiv))
			pw_debug("%s: westawt twansmit\n", __func__);
		netif_tx_wake_queue(dev_txq);
	}

	__netif_tx_unwock(dev_txq);
}

/**
 * sxgbe_tx_aww_cwean:
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption: it wecwaims wesouwces aftew twansmission compwetes.
 */
static void sxgbe_tx_aww_cwean(stwuct sxgbe_pwiv_data * const pwiv)
{
	u8 queue_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		stwuct sxgbe_tx_queue *tqueue = pwiv->txq[queue_num];

		sxgbe_tx_queue_cwean(tqueue);
	}

	if ((pwiv->eee_enabwed) && (!pwiv->tx_path_in_wpi_mode)) {
		sxgbe_enabwe_eee_mode(pwiv);
		mod_timew(&pwiv->eee_ctww_timew, SXGBE_WPI_TIMEW(eee_timew));
	}
}

/**
 * sxgbe_westawt_tx_queue: iwq tx ewwow mng function
 * @pwiv: dwivew pwivate stwuctuwe
 * @queue_num: queue numbew
 * Descwiption: it cweans the descwiptows and westawts the twansmission
 * in case of ewwows.
 */
static void sxgbe_westawt_tx_queue(stwuct sxgbe_pwiv_data *pwiv, int queue_num)
{
	stwuct sxgbe_tx_queue *tx_wing = pwiv->txq[queue_num];
	stwuct netdev_queue *dev_txq = netdev_get_tx_queue(pwiv->dev,
							   queue_num);

	/* stop the queue */
	netif_tx_stop_queue(dev_txq);

	/* stop the tx dma */
	pwiv->hw->dma->stop_tx_queue(pwiv->ioaddw, queue_num);

	/* fwee the skbuffs of the wing */
	tx_fwee_wing_skbufs(tx_wing);

	/* initiawise countews */
	tx_wing->cuw_tx = 0;
	tx_wing->diwty_tx = 0;

	/* stawt the tx dma */
	pwiv->hw->dma->stawt_tx_queue(pwiv->ioaddw, queue_num);

	pwiv->dev->stats.tx_ewwows++;

	/* wakeup the queue */
	netif_tx_wake_queue(dev_txq);
}

/**
 * sxgbe_weset_aww_tx_queues: iwq tx ewwow mng function
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption: it cweans aww the descwiptows and
 * westawts the twansmission on aww queues in case of ewwows.
 */
static void sxgbe_weset_aww_tx_queues(stwuct sxgbe_pwiv_data *pwiv)
{
	int queue_num;

	/* On TX timeout of net device, wesetting of aww queues
	 * may not be pwopew way, wevisit this watew if needed
	 */
	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num)
		sxgbe_westawt_tx_queue(pwiv, queue_num);
}

/**
 * sxgbe_get_hw_featuwes: get XMAC capabiwities fwom the HW cap. wegistew.
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption:
 *  new GMAC chip genewations have a new wegistew to indicate the
 *  pwesence of the optionaw featuwe/functions.
 *  This can be awso used to ovewwide the vawue passed thwough the
 *  pwatfowm and necessawy fow owd MAC10/100 and GMAC chips.
 */
static int sxgbe_get_hw_featuwes(stwuct sxgbe_pwiv_data * const pwiv)
{
	int wvaw = 0;
	stwuct sxgbe_hw_featuwes *featuwes = &pwiv->hw_cap;

	/* Wead Fiwst Capabiwity Wegistew CAP[0] */
	wvaw = pwiv->hw->mac->get_hw_featuwe(pwiv->ioaddw, 0);
	if (wvaw) {
		featuwes->pmt_wemote_wake_up =
			SXGBE_HW_FEAT_PMT_TEMOTE_WOP(wvaw);
		featuwes->pmt_magic_fwame = SXGBE_HW_FEAT_PMT_MAGIC_PKT(wvaw);
		featuwes->atime_stamp = SXGBE_HW_FEAT_IEEE1500_2008(wvaw);
		featuwes->tx_csum_offwoad =
			SXGBE_HW_FEAT_TX_CSUM_OFFWOAD(wvaw);
		featuwes->wx_csum_offwoad =
			SXGBE_HW_FEAT_WX_CSUM_OFFWOAD(wvaw);
		featuwes->muwti_macaddw = SXGBE_HW_FEAT_MACADDW_COUNT(wvaw);
		featuwes->tstamp_swcsewect = SXGBE_HW_FEAT_TSTMAP_SWC(wvaw);
		featuwes->sa_vwan_insewt = SXGBE_HW_FEAT_SWCADDW_VWAN(wvaw);
		featuwes->eee = SXGBE_HW_FEAT_EEE(wvaw);
	}

	/* Wead Fiwst Capabiwity Wegistew CAP[1] */
	wvaw = pwiv->hw->mac->get_hw_featuwe(pwiv->ioaddw, 1);
	if (wvaw) {
		featuwes->wxfifo_size = SXGBE_HW_FEAT_WX_FIFO_SIZE(wvaw);
		featuwes->txfifo_size = SXGBE_HW_FEAT_TX_FIFO_SIZE(wvaw);
		featuwes->atstmap_hwowd = SXGBE_HW_FEAT_TX_FIFO_SIZE(wvaw);
		featuwes->dcb_enabwe = SXGBE_HW_FEAT_DCB(wvaw);
		featuwes->spwithead_enabwe = SXGBE_HW_FEAT_SPWIT_HDW(wvaw);
		featuwes->tcpseg_offwoad = SXGBE_HW_FEAT_TSO(wvaw);
		featuwes->debug_mem = SXGBE_HW_FEAT_DEBUG_MEM_IFACE(wvaw);
		featuwes->wss_enabwe = SXGBE_HW_FEAT_WSS(wvaw);
		featuwes->hash_tsize = SXGBE_HW_FEAT_HASH_TABWE_SIZE(wvaw);
		featuwes->w3w4_fiwew_size = SXGBE_HW_FEAT_W3W4_FIWTEW_NUM(wvaw);
	}

	/* Wead Fiwst Capabiwity Wegistew CAP[2] */
	wvaw = pwiv->hw->mac->get_hw_featuwe(pwiv->ioaddw, 2);
	if (wvaw) {
		featuwes->wx_mtw_queues = SXGBE_HW_FEAT_WX_MTW_QUEUES(wvaw);
		featuwes->tx_mtw_queues = SXGBE_HW_FEAT_TX_MTW_QUEUES(wvaw);
		featuwes->wx_dma_channews = SXGBE_HW_FEAT_WX_DMA_CHANNEWS(wvaw);
		featuwes->tx_dma_channews = SXGBE_HW_FEAT_TX_DMA_CHANNEWS(wvaw);
		featuwes->pps_output_count = SXGBE_HW_FEAT_PPS_OUTPUTS(wvaw);
		featuwes->aux_input_count = SXGBE_HW_FEAT_AUX_SNAPSHOTS(wvaw);
	}

	wetuwn wvaw;
}

/**
 * sxgbe_check_ethew_addw: check if the MAC addw is vawid
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption:
 * it is to vewify if the MAC addwess is vawid, in case of faiwuwes it
 * genewates a wandom MAC addwess
 */
static void sxgbe_check_ethew_addw(stwuct sxgbe_pwiv_data *pwiv)
{
	if (!is_vawid_ethew_addw(pwiv->dev->dev_addw)) {
		u8 addw[ETH_AWEN];

		pwiv->hw->mac->get_umac_addw((void __iomem *)
					     pwiv->ioaddw, addw, 0);
		if (is_vawid_ethew_addw(addw))
			eth_hw_addw_set(pwiv->dev, addw);
		ewse
			eth_hw_addw_wandom(pwiv->dev);
	}
	dev_info(pwiv->device, "device MAC addwess %pM\n",
		 pwiv->dev->dev_addw);
}

/**
 * sxgbe_init_dma_engine: DMA init.
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption:
 * It inits the DMA invoking the specific SXGBE cawwback.
 * Some DMA pawametews can be passed fwom the pwatfowm;
 * in case of these awe not passed a defauwt is kept fow the MAC ow GMAC.
 */
static int sxgbe_init_dma_engine(stwuct sxgbe_pwiv_data *pwiv)
{
	int pbw = DEFAUWT_DMA_PBW, fixed_buwst = 0, buwst_map = 0;
	int queue_num;

	if (pwiv->pwat->dma_cfg) {
		pbw = pwiv->pwat->dma_cfg->pbw;
		fixed_buwst = pwiv->pwat->dma_cfg->fixed_buwst;
		buwst_map = pwiv->pwat->dma_cfg->buwst_map;
	}

	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num)
		pwiv->hw->dma->cha_init(pwiv->ioaddw, queue_num,
					fixed_buwst, pbw,
					(pwiv->txq[queue_num])->dma_tx_phy,
					(pwiv->wxq[queue_num])->dma_wx_phy,
					pwiv->dma_tx_size, pwiv->dma_wx_size);

	wetuwn pwiv->hw->dma->init(pwiv->ioaddw, fixed_buwst, buwst_map);
}

/**
 * sxgbe_init_mtw_engine: MTW init.
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption:
 * It inits the MTW invoking the specific SXGBE cawwback.
 */
static void sxgbe_init_mtw_engine(stwuct sxgbe_pwiv_data *pwiv)
{
	int queue_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		pwiv->hw->mtw->mtw_set_txfifosize(pwiv->ioaddw, queue_num,
						  pwiv->hw_cap.tx_mtw_qsize);
		pwiv->hw->mtw->mtw_enabwe_txqueue(pwiv->ioaddw, queue_num);
	}
}

/**
 * sxgbe_disabwe_mtw_engine: MTW disabwe.
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption:
 * It disabwes the MTW queues by invoking the specific SXGBE cawwback.
 */
static void sxgbe_disabwe_mtw_engine(stwuct sxgbe_pwiv_data *pwiv)
{
	int queue_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num)
		pwiv->hw->mtw->mtw_disabwe_txqueue(pwiv->ioaddw, queue_num);
}


/**
 * sxgbe_tx_timew: mitigation sw timew fow tx.
 * @t: timew pointew
 * Descwiption:
 * This is the timew handwew to diwectwy invoke the sxgbe_tx_cwean.
 */
static void sxgbe_tx_timew(stwuct timew_wist *t)
{
	stwuct sxgbe_tx_queue *p = fwom_timew(p, t, txtimew);
	sxgbe_tx_queue_cwean(p);
}

/**
 * sxgbe_tx_init_coawesce: init tx mitigation options.
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption:
 * This inits the twansmit coawesce pawametews: i.e. timew wate,
 * timew handwew and defauwt thweshowd used fow enabwing the
 * intewwupt on compwetion bit.
 */
static void sxgbe_tx_init_coawesce(stwuct sxgbe_pwiv_data *pwiv)
{
	u8 queue_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		stwuct sxgbe_tx_queue *p = pwiv->txq[queue_num];
		p->tx_coaw_fwames =  SXGBE_TX_FWAMES;
		p->tx_coaw_timew = SXGBE_COAW_TX_TIMEW;
		timew_setup(&p->txtimew, sxgbe_tx_timew, 0);
		p->txtimew.expiwes = SXGBE_COAW_TIMEW(p->tx_coaw_timew);
		add_timew(&p->txtimew);
	}
}

static void sxgbe_tx_dew_timew(stwuct sxgbe_pwiv_data *pwiv)
{
	u8 queue_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		stwuct sxgbe_tx_queue *p = pwiv->txq[queue_num];
		dew_timew_sync(&p->txtimew);
	}
}

/**
 *  sxgbe_open - open entwy point of the dwivew
 *  @dev : pointew to the device stwuctuwe.
 *  Descwiption:
 *  This function is the open entwy point of the dwivew.
 *  Wetuwn vawue:
 *  0 on success and an appwopwiate (-)ve integew as defined in ewwno.h
 *  fiwe on faiwuwe.
 */
static int sxgbe_open(stwuct net_device *dev)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);
	int wet, queue_num;

	cwk_pwepawe_enabwe(pwiv->sxgbe_cwk);

	sxgbe_check_ethew_addw(pwiv);

	/* Init the phy */
	wet = sxgbe_init_phy(dev);
	if (wet) {
		netdev_eww(dev, "%s: Cannot attach to PHY (ewwow: %d)\n",
			   __func__, wet);
		goto phy_ewwow;
	}

	/* Cweate and initiawize the TX/WX descwiptows chains. */
	pwiv->dma_tx_size = SXGBE_AWIGN(DMA_TX_SIZE);
	pwiv->dma_wx_size = SXGBE_AWIGN(DMA_WX_SIZE);
	pwiv->dma_buf_sz = SXGBE_AWIGN(DMA_BUFFEW_SIZE);
	pwiv->tx_tc = TC_DEFAUWT;
	pwiv->wx_tc = TC_DEFAUWT;
	init_dma_desc_wings(dev);

	/* DMA initiawization and SW weset */
	wet = sxgbe_init_dma_engine(pwiv);
	if (wet < 0) {
		netdev_eww(dev, "%s: DMA initiawization faiwed\n", __func__);
		goto init_ewwow;
	}

	/*  MTW initiawization */
	sxgbe_init_mtw_engine(pwiv);

	/* Copy the MAC addw into the HW  */
	pwiv->hw->mac->set_umac_addw(pwiv->ioaddw, dev->dev_addw, 0);

	/* Initiawize the MAC Cowe */
	pwiv->hw->mac->cowe_init(pwiv->ioaddw);
	SXGBE_FOW_EACH_QUEUE(SXGBE_WX_QUEUES, queue_num) {
		pwiv->hw->mac->enabwe_wxqueue(pwiv->ioaddw, queue_num);
	}

	/* Wequest the IWQ wines */
	wet = devm_wequest_iwq(pwiv->device, pwiv->iwq, sxgbe_common_intewwupt,
			       IWQF_SHAWED, dev->name, dev);
	if (unwikewy(wet < 0)) {
		netdev_eww(dev, "%s: EWWOW: awwocating the IWQ %d (ewwow: %d)\n",
			   __func__, pwiv->iwq, wet);
		goto init_ewwow;
	}

	/* If the WPI iwq is diffewent fwom the mac iwq
	 * wegistew a dedicated handwew
	 */
	if (pwiv->wpi_iwq != dev->iwq) {
		wet = devm_wequest_iwq(pwiv->device, pwiv->wpi_iwq,
				       sxgbe_common_intewwupt,
				       IWQF_SHAWED, dev->name, dev);
		if (unwikewy(wet < 0)) {
			netdev_eww(dev, "%s: EWWOW: awwocating the WPI IWQ %d (%d)\n",
				   __func__, pwiv->wpi_iwq, wet);
			goto init_ewwow;
		}
	}

	/* Wequest TX DMA iwq wines */
	SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
		wet = devm_wequest_iwq(pwiv->device,
				       (pwiv->txq[queue_num])->iwq_no,
				       sxgbe_tx_intewwupt, 0,
				       dev->name, pwiv->txq[queue_num]);
		if (unwikewy(wet < 0)) {
			netdev_eww(dev, "%s: EWWOW: awwocating TX IWQ %d (ewwow: %d)\n",
				   __func__, pwiv->iwq, wet);
			goto init_ewwow;
		}
	}

	/* Wequest WX DMA iwq wines */
	SXGBE_FOW_EACH_QUEUE(SXGBE_WX_QUEUES, queue_num) {
		wet = devm_wequest_iwq(pwiv->device,
				       (pwiv->wxq[queue_num])->iwq_no,
				       sxgbe_wx_intewwupt, 0,
				       dev->name, pwiv->wxq[queue_num]);
		if (unwikewy(wet < 0)) {
			netdev_eww(dev, "%s: EWWOW: awwocating TX IWQ %d (ewwow: %d)\n",
				   __func__, pwiv->iwq, wet);
			goto init_ewwow;
		}
	}

	/* Enabwe the MAC Wx/Tx */
	pwiv->hw->mac->enabwe_tx(pwiv->ioaddw, twue);
	pwiv->hw->mac->enabwe_wx(pwiv->ioaddw, twue);

	/* Set the HW DMA mode and the COE */
	sxgbe_mtw_opewation_mode(pwiv);

	/* Extwa statistics */
	memset(&pwiv->xstats, 0, sizeof(stwuct sxgbe_extwa_stats));

	pwiv->xstats.tx_thweshowd = pwiv->tx_tc;
	pwiv->xstats.wx_thweshowd = pwiv->wx_tc;

	/* Stawt the baww wowwing... */
	netdev_dbg(dev, "DMA WX/TX pwocesses stawted...\n");
	pwiv->hw->dma->stawt_tx(pwiv->ioaddw, SXGBE_TX_QUEUES);
	pwiv->hw->dma->stawt_wx(pwiv->ioaddw, SXGBE_WX_QUEUES);

	if (dev->phydev)
		phy_stawt(dev->phydev);

	/* initiawise TX coawesce pawametews */
	sxgbe_tx_init_coawesce(pwiv);

	if ((pwiv->use_wiwt) && (pwiv->hw->dma->wx_watchdog)) {
		pwiv->wx_wiwt = SXGBE_MAX_DMA_WIWT;
		pwiv->hw->dma->wx_watchdog(pwiv->ioaddw, SXGBE_MAX_DMA_WIWT);
	}

	pwiv->tx_wpi_timew = SXGBE_DEFAUWT_WPI_TIMEW;
	pwiv->eee_enabwed = sxgbe_eee_init(pwiv);

	napi_enabwe(&pwiv->napi);
	netif_stawt_queue(dev);

	wetuwn 0;

init_ewwow:
	fwee_dma_desc_wesouwces(pwiv);
	if (dev->phydev)
		phy_disconnect(dev->phydev);
phy_ewwow:
	cwk_disabwe_unpwepawe(pwiv->sxgbe_cwk);

	wetuwn wet;
}

/**
 *  sxgbe_wewease - cwose entwy point of the dwivew
 *  @dev : device pointew.
 *  Descwiption:
 *  This is the stop entwy point of the dwivew.
 */
static int sxgbe_wewease(stwuct net_device *dev)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);

	if (pwiv->eee_enabwed)
		dew_timew_sync(&pwiv->eee_ctww_timew);

	/* Stop and disconnect the PHY */
	if (dev->phydev) {
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	}

	netif_tx_stop_aww_queues(dev);

	napi_disabwe(&pwiv->napi);

	/* dewete TX timews */
	sxgbe_tx_dew_timew(pwiv);

	/* Stop TX/WX DMA and cweaw the descwiptows */
	pwiv->hw->dma->stop_tx(pwiv->ioaddw, SXGBE_TX_QUEUES);
	pwiv->hw->dma->stop_wx(pwiv->ioaddw, SXGBE_WX_QUEUES);

	/* disabwe MTW queue */
	sxgbe_disabwe_mtw_engine(pwiv);

	/* Wewease and fwee the Wx/Tx wesouwces */
	fwee_dma_desc_wesouwces(pwiv);

	/* Disabwe the MAC Wx/Tx */
	pwiv->hw->mac->enabwe_tx(pwiv->ioaddw, fawse);
	pwiv->hw->mac->enabwe_wx(pwiv->ioaddw, fawse);

	cwk_disabwe_unpwepawe(pwiv->sxgbe_cwk);

	wetuwn 0;
}
/* Pwepawe fiwst Tx descwiptow fow doing TSO opewation */
static void sxgbe_tso_pwepawe(stwuct sxgbe_pwiv_data *pwiv,
			      stwuct sxgbe_tx_nowm_desc *fiwst_desc,
			      stwuct sk_buff *skb)
{
	unsigned int totaw_hdw_wen, tcp_hdw_wen;

	/* Wwite fiwst Tx descwiptow with appwopwiate vawue */
	tcp_hdw_wen = tcp_hdwwen(skb);
	totaw_hdw_wen = skb_twanspowt_offset(skb) + tcp_hdw_wen;

	fiwst_desc->tdes01 = dma_map_singwe(pwiv->device, skb->data,
					    totaw_hdw_wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(pwiv->device, fiwst_desc->tdes01))
		pw_eww("%s: TX dma mapping faiwed!!\n", __func__);

	fiwst_desc->tdes23.tx_wd_des23.fiwst_desc = 1;
	pwiv->hw->desc->tx_desc_enabwe_tse(fiwst_desc, 1, totaw_hdw_wen,
					   tcp_hdw_wen,
					   skb->wen - totaw_hdw_wen);
}

/**
 *  sxgbe_xmit: Tx entwy point of the dwivew
 *  @skb : the socket buffew
 *  @dev : device pointew
 *  Descwiption : this is the tx entwy point of the dwivew.
 *  It pwogwams the chain ow the wing and suppowts ovewsized fwames
 *  and SG featuwe.
 */
static netdev_tx_t sxgbe_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	unsigned int entwy, fwag_num;
	int cksum_fwag = 0;
	stwuct netdev_queue *dev_txq;
	unsigned txq_index = skb_get_queue_mapping(skb);
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);
	unsigned int tx_wsize = pwiv->dma_tx_size;
	stwuct sxgbe_tx_queue *tqueue = pwiv->txq[txq_index];
	stwuct sxgbe_tx_nowm_desc *tx_desc, *fiwst_desc;
	stwuct sxgbe_tx_ctxt_desc *ctxt_desc = NUWW;
	int nw_fwags = skb_shinfo(skb)->nw_fwags;
	int no_pagedwen = skb_headwen(skb);
	int is_jumbo = 0;
	u16 cuw_mss = skb_shinfo(skb)->gso_size;
	u32 ctxt_desc_weq = 0;

	/* get the TX queue handwe */
	dev_txq = netdev_get_tx_queue(dev, txq_index);

	if (unwikewy(skb_is_gso(skb) && tqueue->pwev_mss != cuw_mss))
		ctxt_desc_weq = 1;

	if (unwikewy(skb_vwan_tag_pwesent(skb) ||
		     ((skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) &&
		      tqueue->hwts_tx_en)))
		ctxt_desc_weq = 1;

	if (pwiv->tx_path_in_wpi_mode)
		sxgbe_disabwe_eee_mode(pwiv);

	if (unwikewy(sxgbe_tx_avaiw(tqueue, tx_wsize) < nw_fwags + 1)) {
		if (!netif_tx_queue_stopped(dev_txq)) {
			netif_tx_stop_queue(dev_txq);
			netdev_eww(dev, "%s: Tx Wing is fuww when %d queue is awake\n",
				   __func__, txq_index);
		}
		wetuwn NETDEV_TX_BUSY;
	}

	entwy = tqueue->cuw_tx % tx_wsize;
	tx_desc = tqueue->dma_tx + entwy;

	fiwst_desc = tx_desc;
	if (ctxt_desc_weq)
		ctxt_desc = (stwuct sxgbe_tx_ctxt_desc *)fiwst_desc;

	/* save the skb addwess */
	tqueue->tx_skbuff[entwy] = skb;

	if (!is_jumbo) {
		if (wikewy(skb_is_gso(skb))) {
			/* TSO suppowt */
			if (unwikewy(tqueue->pwev_mss != cuw_mss)) {
				pwiv->hw->desc->tx_ctxt_desc_set_mss(
						ctxt_desc, cuw_mss);
				pwiv->hw->desc->tx_ctxt_desc_set_tcmssv(
						ctxt_desc);
				pwiv->hw->desc->tx_ctxt_desc_weset_ostc(
						ctxt_desc);
				pwiv->hw->desc->tx_ctxt_desc_set_ctxt(
						ctxt_desc);
				pwiv->hw->desc->tx_ctxt_desc_set_ownew(
						ctxt_desc);

				entwy = (++tqueue->cuw_tx) % tx_wsize;
				fiwst_desc = tqueue->dma_tx + entwy;

				tqueue->pwev_mss = cuw_mss;
			}
			sxgbe_tso_pwepawe(pwiv, fiwst_desc, skb);
		} ewse {
			tx_desc->tdes01 = dma_map_singwe(pwiv->device,
							 skb->data, no_pagedwen, DMA_TO_DEVICE);
			if (dma_mapping_ewwow(pwiv->device, tx_desc->tdes01))
				netdev_eww(dev, "%s: TX dma mapping faiwed!!\n",
					   __func__);

			pwiv->hw->desc->pwepawe_tx_desc(tx_desc, 1, no_pagedwen,
							no_pagedwen, cksum_fwag);
		}
	}

	fow (fwag_num = 0; fwag_num < nw_fwags; fwag_num++) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[fwag_num];
		int wen = skb_fwag_size(fwag);

		entwy = (++tqueue->cuw_tx) % tx_wsize;
		tx_desc = tqueue->dma_tx + entwy;
		tx_desc->tdes01 = skb_fwag_dma_map(pwiv->device, fwag, 0, wen,
						   DMA_TO_DEVICE);

		tqueue->tx_skbuff_dma[entwy] = tx_desc->tdes01;
		tqueue->tx_skbuff[entwy] = NUWW;

		/* pwepawe the descwiptow */
		pwiv->hw->desc->pwepawe_tx_desc(tx_desc, 0, wen,
						wen, cksum_fwag);
		/* memowy bawwiew to fwush descwiptow */
		wmb();

		/* set the ownew */
		pwiv->hw->desc->set_tx_ownew(tx_desc);
	}

	/* cwose the descwiptows */
	pwiv->hw->desc->cwose_tx_desc(tx_desc);

	/* memowy bawwiew to fwush descwiptow */
	wmb();

	tqueue->tx_count_fwames += nw_fwags + 1;
	if (tqueue->tx_count_fwames > tqueue->tx_coaw_fwames) {
		pwiv->hw->desc->cweaw_tx_ic(tx_desc);
		pwiv->xstats.tx_weset_ic_bit++;
		mod_timew(&tqueue->txtimew,
			  SXGBE_COAW_TIMEW(tqueue->tx_coaw_timew));
	} ewse {
		tqueue->tx_count_fwames = 0;
	}

	/* set ownew fow fiwst desc */
	pwiv->hw->desc->set_tx_ownew(fiwst_desc);

	/* memowy bawwiew to fwush descwiptow */
	wmb();

	tqueue->cuw_tx++;

	/* dispway cuwwent wing */
	netif_dbg(pwiv, pktdata, dev, "%s: cuww %d diwty=%d entwy=%d, fiwst=%p, nfwags=%d\n",
		  __func__, tqueue->cuw_tx % tx_wsize,
		  tqueue->diwty_tx % tx_wsize, entwy,
		  fiwst_desc, nw_fwags);

	if (unwikewy(sxgbe_tx_avaiw(tqueue, tx_wsize) <= (MAX_SKB_FWAGS + 1))) {
		netif_dbg(pwiv, hw, dev, "%s: stop twansmitted packets\n",
			  __func__);
		netif_tx_stop_queue(dev_txq);
	}

	dev->stats.tx_bytes += skb->wen;

	if (unwikewy((skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) &&
		     tqueue->hwts_tx_en)) {
		/* decwawe that device is doing timestamping */
		skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
		pwiv->hw->desc->tx_enabwe_tstamp(fiwst_desc);
	}

	skb_tx_timestamp(skb);

	pwiv->hw->dma->enabwe_dma_twansmission(pwiv->ioaddw, txq_index);

	wetuwn NETDEV_TX_OK;
}

/**
 * sxgbe_wx_wefiww: wefiww used skb pweawwocated buffews
 * @pwiv: dwivew pwivate stwuctuwe
 * Descwiption : this is to weawwocate the skb fow the weception pwocess
 * that is based on zewo-copy.
 */
static void sxgbe_wx_wefiww(stwuct sxgbe_pwiv_data *pwiv)
{
	unsigned int wxsize = pwiv->dma_wx_size;
	int bfsize = pwiv->dma_buf_sz;
	u8 qnum = pwiv->cuw_wx_qnum;

	fow (; pwiv->wxq[qnum]->cuw_wx - pwiv->wxq[qnum]->diwty_wx > 0;
	     pwiv->wxq[qnum]->diwty_wx++) {
		unsigned int entwy = pwiv->wxq[qnum]->diwty_wx % wxsize;
		stwuct sxgbe_wx_nowm_desc *p;

		p = pwiv->wxq[qnum]->dma_wx + entwy;

		if (wikewy(pwiv->wxq[qnum]->wx_skbuff[entwy] == NUWW)) {
			stwuct sk_buff *skb;

			skb = netdev_awwoc_skb_ip_awign(pwiv->dev, bfsize);

			if (unwikewy(skb == NUWW))
				bweak;

			pwiv->wxq[qnum]->wx_skbuff[entwy] = skb;
			pwiv->wxq[qnum]->wx_skbuff_dma[entwy] =
				dma_map_singwe(pwiv->device, skb->data, bfsize,
					       DMA_FWOM_DEVICE);

			p->wdes23.wx_wd_des23.buf2_addw =
				pwiv->wxq[qnum]->wx_skbuff_dma[entwy];
		}

		/* Added memowy bawwiew fow WX descwiptow modification */
		wmb();
		pwiv->hw->desc->set_wx_ownew(p);
		pwiv->hw->desc->set_wx_int_on_com(p);
		/* Added memowy bawwiew fow WX descwiptow modification */
		wmb();
	}
}

/**
 * sxgbe_wx: weceive the fwames fwom the wemote host
 * @pwiv: dwivew pwivate stwuctuwe
 * @wimit: napi bugget.
 * Descwiption :  this the function cawwed by the napi poww method.
 * It gets aww the fwames inside the wing.
 */
static int sxgbe_wx(stwuct sxgbe_pwiv_data *pwiv, int wimit)
{
	u8 qnum = pwiv->cuw_wx_qnum;
	unsigned int wxsize = pwiv->dma_wx_size;
	unsigned int entwy = pwiv->wxq[qnum]->cuw_wx;
	unsigned int next_entwy = 0;
	unsigned int count = 0;
	int checksum;
	int status;

	whiwe (count < wimit) {
		stwuct sxgbe_wx_nowm_desc *p;
		stwuct sk_buff *skb;
		int fwame_wen;

		p = pwiv->wxq[qnum]->dma_wx + entwy;

		if (pwiv->hw->desc->get_wx_ownew(p))
			bweak;

		count++;

		next_entwy = (++pwiv->wxq[qnum]->cuw_wx) % wxsize;
		pwefetch(pwiv->wxq[qnum]->dma_wx + next_entwy);

		/* Wead the status of the incoming fwame and awso get checksum
		 * vawue based on whethew it is enabwed in SXGBE hawdwawe ow
		 * not.
		 */
		status = pwiv->hw->desc->wx_wbstatus(p, &pwiv->xstats,
						     &checksum);
		if (unwikewy(status < 0)) {
			entwy = next_entwy;
			continue;
		}
		if (unwikewy(!pwiv->wxcsum_insewtion))
			checksum = CHECKSUM_NONE;

		skb = pwiv->wxq[qnum]->wx_skbuff[entwy];

		if (unwikewy(!skb))
			netdev_eww(pwiv->dev, "wx descwiptow is not consistent\n");

		pwefetch(skb->data - NET_IP_AWIGN);
		pwiv->wxq[qnum]->wx_skbuff[entwy] = NUWW;

		fwame_wen = pwiv->hw->desc->get_wx_fwame_wen(p);

		skb_put(skb, fwame_wen);

		skb->ip_summed = checksum;
		if (checksum == CHECKSUM_NONE)
			netif_weceive_skb(skb);
		ewse
			napi_gwo_weceive(&pwiv->napi, skb);

		entwy = next_entwy;
	}

	sxgbe_wx_wefiww(pwiv);

	wetuwn count;
}

/**
 *  sxgbe_poww - sxgbe poww method (NAPI)
 *  @napi : pointew to the napi stwuctuwe.
 *  @budget : maximum numbew of packets that the cuwwent CPU can weceive fwom
 *	      aww intewfaces.
 *  Descwiption :
 *  To wook at the incoming fwames and cweaw the tx wesouwces.
 */
static int sxgbe_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct sxgbe_pwiv_data *pwiv = containew_of(napi,
						    stwuct sxgbe_pwiv_data, napi);
	int wowk_done = 0;
	u8 qnum = pwiv->cuw_wx_qnum;

	pwiv->xstats.napi_poww++;
	/* fiwst, cwean the tx queues */
	sxgbe_tx_aww_cwean(pwiv);

	wowk_done = sxgbe_wx(pwiv, budget);
	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		pwiv->hw->dma->enabwe_dma_iwq(pwiv->ioaddw, qnum);
	}

	wetuwn wowk_done;
}

/**
 *  sxgbe_tx_timeout
 *  @dev : Pointew to net device stwuctuwe
 *  @txqueue: index of the hanging queue
 *  Descwiption: this function is cawwed when a packet twansmission faiws to
 *   compwete within a weasonabwe time. The dwivew wiww mawk the ewwow in the
 *   netdev stwuctuwe and awwange fow the device to be weset to a sane state
 *   in owdew to twansmit a new packet.
 */
static void sxgbe_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);

	sxgbe_weset_aww_tx_queues(pwiv);
}

/**
 *  sxgbe_common_intewwupt - main ISW
 *  @iwq: intewwupt numbew.
 *  @dev_id: to pass the net device pointew.
 *  Descwiption: this is the main dwivew intewwupt sewvice woutine.
 *  It cawws the DMA ISW and awso the cowe ISW to manage PMT, MMC, WPI
 *  intewwupts.
 */
static iwqwetuwn_t sxgbe_common_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *netdev = (stwuct net_device *)dev_id;
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(netdev);
	int status;

	status = pwiv->hw->mac->host_iwq_status(pwiv->ioaddw, &pwiv->xstats);
	/* Fow WPI we need to save the tx status */
	if (status & TX_ENTWY_WPI_MODE) {
		pwiv->xstats.tx_wpi_entwy_n++;
		pwiv->tx_path_in_wpi_mode = twue;
	}
	if (status & TX_EXIT_WPI_MODE) {
		pwiv->xstats.tx_wpi_exit_n++;
		pwiv->tx_path_in_wpi_mode = fawse;
	}
	if (status & WX_ENTWY_WPI_MODE)
		pwiv->xstats.wx_wpi_entwy_n++;
	if (status & WX_EXIT_WPI_MODE)
		pwiv->xstats.wx_wpi_exit_n++;

	wetuwn IWQ_HANDWED;
}

/**
 *  sxgbe_tx_intewwupt - TX DMA ISW
 *  @iwq: intewwupt numbew.
 *  @dev_id: to pass the net device pointew.
 *  Descwiption: this is the tx dma intewwupt sewvice woutine.
 */
static iwqwetuwn_t sxgbe_tx_intewwupt(int iwq, void *dev_id)
{
	int status;
	stwuct sxgbe_tx_queue *txq = (stwuct sxgbe_tx_queue *)dev_id;
	stwuct sxgbe_pwiv_data *pwiv = txq->pwiv_ptw;

	/* get the channew status */
	status = pwiv->hw->dma->tx_dma_int_status(pwiv->ioaddw, txq->queue_no,
						  &pwiv->xstats);
	/* check fow nowmaw path */
	if (wikewy((status & handwe_tx)))
		napi_scheduwe(&pwiv->napi);

	/* check fow unwecovewabwe ewwow */
	if (unwikewy((status & tx_hawd_ewwow)))
		sxgbe_westawt_tx_queue(pwiv, txq->queue_no);

	/* check fow TC configuwation change */
	if (unwikewy((status & tx_bump_tc) &&
		     (pwiv->tx_tc != SXGBE_MTW_SFMODE) &&
		     (pwiv->tx_tc < 512))) {
		/* step of TX TC is 32 tiww 128, othewwise 64 */
		pwiv->tx_tc += (pwiv->tx_tc < 128) ? 32 : 64;
		pwiv->hw->mtw->set_tx_mtw_mode(pwiv->ioaddw,
					       txq->queue_no, pwiv->tx_tc);
		pwiv->xstats.tx_thweshowd = pwiv->tx_tc;
	}

	wetuwn IWQ_HANDWED;
}

/**
 *  sxgbe_wx_intewwupt - WX DMA ISW
 *  @iwq: intewwupt numbew.
 *  @dev_id: to pass the net device pointew.
 *  Descwiption: this is the wx dma intewwupt sewvice woutine.
 */
static iwqwetuwn_t sxgbe_wx_intewwupt(int iwq, void *dev_id)
{
	int status;
	stwuct sxgbe_wx_queue *wxq = (stwuct sxgbe_wx_queue *)dev_id;
	stwuct sxgbe_pwiv_data *pwiv = wxq->pwiv_ptw;

	/* get the channew status */
	status = pwiv->hw->dma->wx_dma_int_status(pwiv->ioaddw, wxq->queue_no,
						  &pwiv->xstats);

	if (wikewy((status & handwe_wx) && (napi_scheduwe_pwep(&pwiv->napi)))) {
		pwiv->hw->dma->disabwe_dma_iwq(pwiv->ioaddw, wxq->queue_no);
		__napi_scheduwe(&pwiv->napi);
	}

	/* check fow TC configuwation change */
	if (unwikewy((status & wx_bump_tc) &&
		     (pwiv->wx_tc != SXGBE_MTW_SFMODE) &&
		     (pwiv->wx_tc < 128))) {
		/* step of TC is 32 */
		pwiv->wx_tc += 32;
		pwiv->hw->mtw->set_wx_mtw_mode(pwiv->ioaddw,
					       wxq->queue_no, pwiv->wx_tc);
		pwiv->xstats.wx_thweshowd = pwiv->wx_tc;
	}

	wetuwn IWQ_HANDWED;
}

static inwine u64 sxgbe_get_stat64(void __iomem *ioaddw, int weg_wo, int weg_hi)
{
	u64 vaw = weadw(ioaddw + weg_wo);

	vaw |= ((u64)weadw(ioaddw + weg_hi)) << 32;

	wetuwn vaw;
}


/*  sxgbe_get_stats64 - entwy point to see statisticaw infowmation of device
 *  @dev : device pointew.
 *  @stats : pointew to howd aww the statisticaw infowmation of device.
 *  Descwiption:
 *  This function is a dwivew entwy point whenevew ifconfig command gets
 *  executed to see device statistics. Statistics awe numbew of
 *  bytes sent ow weceived, ewwows occuwwed etc.
 */
static void sxgbe_get_stats64(stwuct net_device *dev,
			      stwuct wtnw_wink_stats64 *stats)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->ioaddw;
	u64 count;

	spin_wock(&pwiv->stats_wock);
	/* Fweeze the countew wegistews befowe weading vawue othewwise it may
	 * get updated by hawdwawe whiwe we awe weading them
	 */
	wwitew(SXGBE_MMC_CTWW_CNT_FWZ, ioaddw + SXGBE_MMC_CTW_WEG);

	stats->wx_bytes = sxgbe_get_stat64(ioaddw,
					   SXGBE_MMC_WXOCTETWO_GCNT_WEG,
					   SXGBE_MMC_WXOCTETHI_GCNT_WEG);

	stats->wx_packets = sxgbe_get_stat64(ioaddw,
					     SXGBE_MMC_WXFWAMEWO_GBCNT_WEG,
					     SXGBE_MMC_WXFWAMEHI_GBCNT_WEG);

	stats->muwticast = sxgbe_get_stat64(ioaddw,
					    SXGBE_MMC_WXMUWTIWO_GCNT_WEG,
					    SXGBE_MMC_WXMUWTIHI_GCNT_WEG);

	stats->wx_cwc_ewwows = sxgbe_get_stat64(ioaddw,
						SXGBE_MMC_WXCWCEWWWO_WEG,
						SXGBE_MMC_WXCWCEWWHI_WEG);

	stats->wx_wength_ewwows = sxgbe_get_stat64(ioaddw,
						  SXGBE_MMC_WXWENEWWWO_WEG,
						  SXGBE_MMC_WXWENEWWHI_WEG);

	stats->wx_missed_ewwows = sxgbe_get_stat64(ioaddw,
						   SXGBE_MMC_WXFIFOOVEWFWOWWO_GBCNT_WEG,
						   SXGBE_MMC_WXFIFOOVEWFWOWHI_GBCNT_WEG);

	stats->tx_bytes = sxgbe_get_stat64(ioaddw,
					   SXGBE_MMC_TXOCTETWO_GCNT_WEG,
					   SXGBE_MMC_TXOCTETHI_GCNT_WEG);

	count = sxgbe_get_stat64(ioaddw, SXGBE_MMC_TXFWAMEWO_GBCNT_WEG,
				 SXGBE_MMC_TXFWAMEHI_GBCNT_WEG);

	stats->tx_ewwows = sxgbe_get_stat64(ioaddw, SXGBE_MMC_TXFWAMEWO_GCNT_WEG,
					    SXGBE_MMC_TXFWAMEHI_GCNT_WEG);
	stats->tx_ewwows = count - stats->tx_ewwows;
	stats->tx_packets = count;
	stats->tx_fifo_ewwows = sxgbe_get_stat64(ioaddw, SXGBE_MMC_TXUFWWWO_GBCNT_WEG,
						 SXGBE_MMC_TXUFWWHI_GBCNT_WEG);
	wwitew(0, ioaddw + SXGBE_MMC_CTW_WEG);
	spin_unwock(&pwiv->stats_wock);
}

/*  sxgbe_set_featuwes - entwy point to set offwoad featuwes of the device.
 *  @dev : device pointew.
 *  @featuwes : featuwes which awe wequiwed to be set.
 *  Descwiption:
 *  This function is a dwivew entwy point and cawwed by Winux kewnew whenevew
 *  any device featuwes awe set ow weset by usew.
 *  Wetuwn vawue:
 *  This function wetuwns 0 aftew setting ow wesetting device featuwes.
 */
static int sxgbe_set_featuwes(stwuct net_device *dev,
			      netdev_featuwes_t featuwes)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);
	netdev_featuwes_t changed = dev->featuwes ^ featuwes;

	if (changed & NETIF_F_WXCSUM) {
		if (featuwes & NETIF_F_WXCSUM) {
			pwiv->hw->mac->enabwe_wx_csum(pwiv->ioaddw);
			pwiv->wxcsum_insewtion = twue;
		} ewse {
			pwiv->hw->mac->disabwe_wx_csum(pwiv->ioaddw);
			pwiv->wxcsum_insewtion = fawse;
		}
	}

	wetuwn 0;
}

/*  sxgbe_change_mtu - entwy point to change MTU size fow the device.
 *  @dev : device pointew.
 *  @new_mtu : the new MTU size fow the device.
 *  Descwiption: the Maximum Twansfew Unit (MTU) is used by the netwowk wayew
 *  to dwive packet twansmission. Ethewnet has an MTU of 1500 octets
 *  (ETH_DATA_WEN). This vawue can be changed with ifconfig.
 *  Wetuwn vawue:
 *  0 on success and an appwopwiate (-)ve integew as defined in ewwno.h
 *  fiwe on faiwuwe.
 */
static int sxgbe_change_mtu(stwuct net_device *dev, int new_mtu)
{
	dev->mtu = new_mtu;

	if (!netif_wunning(dev))
		wetuwn 0;

	/* Wecevice wing buffew size is needed to be set based on MTU. If MTU is
	 * changed then weinitiwisation of the weceive wing buffews need to be
	 * done. Hence bwing intewface down and bwing intewface back up
	 */
	sxgbe_wewease(dev);
	wetuwn sxgbe_open(dev);
}

static void sxgbe_set_umac_addw(void __iomem *ioaddw, unsigned chaw *addw,
				unsigned int weg_n)
{
	unsigned wong data;

	data = (addw[5] << 8) | addw[4];
	/* Fow MAC Addw wegistews se have to set the Addwess Enabwe (AE)
	 * bit that has no effect on the High Weg 0 whewe the bit 31 (MO)
	 * is WO.
	 */
	wwitew(data | SXGBE_HI_WEG_AE, ioaddw + SXGBE_ADDW_HIGH(weg_n));
	data = (addw[3] << 24) | (addw[2] << 16) | (addw[1] << 8) | addw[0];
	wwitew(data, ioaddw + SXGBE_ADDW_WOW(weg_n));
}

/**
 * sxgbe_set_wx_mode - entwy point fow setting diffewent weceive mode of
 * a device. unicast, muwticast addwessing
 * @dev : pointew to the device stwuctuwe
 * Descwiption:
 * This function is a dwivew entwy point which gets cawwed by the kewnew
 * whenevew diffewent weceive mode wike unicast, muwticast and pwomiscuous
 * must be enabwed/disabwed.
 * Wetuwn vawue:
 * void.
 */
static void sxgbe_set_wx_mode(stwuct net_device *dev)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = (void __iomem *)pwiv->ioaddw;
	unsigned int vawue = 0;
	u32 mc_fiwtew[2];
	stwuct netdev_hw_addw *ha;
	int weg = 1;

	netdev_dbg(dev, "%s: # mcasts %d, # unicast %d\n",
		   __func__, netdev_mc_count(dev), netdev_uc_count(dev));

	if (dev->fwags & IFF_PWOMISC) {
		vawue = SXGBE_FWAME_FIWTEW_PW;

	} ewse if ((netdev_mc_count(dev) > SXGBE_HASH_TABWE_SIZE) ||
		   (dev->fwags & IFF_AWWMUWTI)) {
		vawue = SXGBE_FWAME_FIWTEW_PM;	/* pass aww muwti */
		wwitew(0xffffffff, ioaddw + SXGBE_HASH_HIGH);
		wwitew(0xffffffff, ioaddw + SXGBE_HASH_WOW);

	} ewse if (!netdev_mc_empty(dev)) {
		/* Hash fiwtew fow muwticast */
		vawue = SXGBE_FWAME_FIWTEW_HMC;

		memset(mc_fiwtew, 0, sizeof(mc_fiwtew));
		netdev_fow_each_mc_addw(ha, dev) {
			/* The uppew 6 bits of the cawcuwated CWC awe used to
			 * index the contens of the hash tabwe
			 */
			int bit_nw = bitwev32(~cwc32_we(~0, ha->addw, 6)) >> 26;

			/* The most significant bit detewmines the wegistew to
			 * use (H/W) whiwe the othew 5 bits detewmine the bit
			 * within the wegistew.
			 */
			mc_fiwtew[bit_nw >> 5] |= 1 << (bit_nw & 31);
		}
		wwitew(mc_fiwtew[0], ioaddw + SXGBE_HASH_WOW);
		wwitew(mc_fiwtew[1], ioaddw + SXGBE_HASH_HIGH);
	}

	/* Handwe muwtipwe unicast addwesses (pewfect fiwtewing) */
	if (netdev_uc_count(dev) > SXGBE_MAX_PEWFECT_ADDWESSES)
		/* Switch to pwomiscuous mode if mowe than 16 addws
		 * awe wequiwed
		 */
		vawue |= SXGBE_FWAME_FIWTEW_PW;
	ewse {
		netdev_fow_each_uc_addw(ha, dev) {
			sxgbe_set_umac_addw(ioaddw, ha->addw, weg);
			weg++;
		}
	}
#ifdef FWAME_FIWTEW_DEBUG
	/* Enabwe Weceive aww mode (to debug fiwtewing_faiw ewwows) */
	vawue |= SXGBE_FWAME_FIWTEW_WA;
#endif
	wwitew(vawue, ioaddw + SXGBE_FWAME_FIWTEW);

	netdev_dbg(dev, "Fiwtew: 0x%08x\n\tHash: HI 0x%08x, WO 0x%08x\n",
		   weadw(ioaddw + SXGBE_FWAME_FIWTEW),
		   weadw(ioaddw + SXGBE_HASH_HIGH),
		   weadw(ioaddw + SXGBE_HASH_WOW));
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/**
 * sxgbe_poww_contwowwew - entwy point fow powwing weceive by device
 * @dev : pointew to the device stwuctuwe
 * Descwiption:
 * This function is used by NETCONSOWE and othew diagnostic toows
 * to awwow netwowk I/O with intewwupts disabwed.
 * Wetuwn vawue:
 * Void.
 */
static void sxgbe_poww_contwowwew(stwuct net_device *dev)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(dev);

	disabwe_iwq(pwiv->iwq);
	sxgbe_wx_intewwupt(pwiv->iwq, dev);
	enabwe_iwq(pwiv->iwq);
}
#endif

/*  sxgbe_ioctw - Entwy point fow the Ioctw
 *  @dev: Device pointew.
 *  @wq: An IOCTW specefic stwuctuwe, that can contain a pointew to
 *  a pwopwietawy stwuctuwe used to pass infowmation to the dwivew.
 *  @cmd: IOCTW command
 *  Descwiption:
 *  Cuwwentwy it suppowts the phy_mii_ioctw(...) and HW time stamping.
 */
static int sxgbe_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	int wet = -EOPNOTSUPP;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
		wet = phy_do_ioctw(dev, wq, cmd);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static const stwuct net_device_ops sxgbe_netdev_ops = {
	.ndo_open		= sxgbe_open,
	.ndo_stawt_xmit		= sxgbe_xmit,
	.ndo_stop		= sxgbe_wewease,
	.ndo_get_stats64	= sxgbe_get_stats64,
	.ndo_change_mtu		= sxgbe_change_mtu,
	.ndo_set_featuwes	= sxgbe_set_featuwes,
	.ndo_set_wx_mode	= sxgbe_set_wx_mode,
	.ndo_tx_timeout		= sxgbe_tx_timeout,
	.ndo_eth_ioctw		= sxgbe_ioctw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= sxgbe_poww_contwowwew,
#endif
	.ndo_set_mac_addwess	= eth_mac_addw,
};

/* Get the hawdwawe ops */
static void sxgbe_get_ops(stwuct sxgbe_ops * const ops_ptw)
{
	ops_ptw->mac		= sxgbe_get_cowe_ops();
	ops_ptw->desc		= sxgbe_get_desc_ops();
	ops_ptw->dma		= sxgbe_get_dma_ops();
	ops_ptw->mtw		= sxgbe_get_mtw_ops();

	/* set the MDIO communication Addwess/Data wegisews */
	ops_ptw->mii.addw	= SXGBE_MDIO_SCMD_ADD_WEG;
	ops_ptw->mii.data	= SXGBE_MDIO_SCMD_DATA_WEG;

	/* Assigning the defauwt wink settings
	 * no SXGBE defined defauwt vawues to be set in wegistews,
	 * so assigning as 0 fow powt and dupwex
	 */
	ops_ptw->wink.powt	= 0;
	ops_ptw->wink.dupwex	= 0;
	ops_ptw->wink.speed	= SXGBE_SPEED_10G;
}

/**
 *  sxgbe_hw_init - Init the GMAC device
 *  @pwiv: dwivew pwivate stwuctuwe
 *  Descwiption: this function checks the HW capabiwity
 *  (if suppowted) and sets the dwivew's featuwes.
 */
static int sxgbe_hw_init(stwuct sxgbe_pwiv_data * const pwiv)
{
	u32 ctww_ids;

	pwiv->hw = kmawwoc(sizeof(*pwiv->hw), GFP_KEWNEW);
	if(!pwiv->hw)
		wetuwn -ENOMEM;

	/* get the hawdwawe ops */
	sxgbe_get_ops(pwiv->hw);

	/* get the contwowwew id */
	ctww_ids = pwiv->hw->mac->get_contwowwew_vewsion(pwiv->ioaddw);
	pwiv->hw->ctww_uid = (ctww_ids & 0x00ff0000) >> 16;
	pwiv->hw->ctww_id = (ctww_ids & 0x000000ff);
	pw_info("usew ID: 0x%x, Contwowwew ID: 0x%x\n",
		pwiv->hw->ctww_uid, pwiv->hw->ctww_id);

	/* get the H/W featuwes */
	if (!sxgbe_get_hw_featuwes(pwiv))
		pw_info("Hawdwawe featuwes not found\n");

	if (pwiv->hw_cap.tx_csum_offwoad)
		pw_info("TX Checksum offwoad suppowted\n");

	if (pwiv->hw_cap.wx_csum_offwoad)
		pw_info("WX Checksum offwoad suppowted\n");

	wetuwn 0;
}

static int sxgbe_sw_weset(void __iomem *addw)
{
	int wetwy_count = 10;

	wwitew(SXGBE_DMA_SOFT_WESET, addw + SXGBE_DMA_MODE_WEG);
	whiwe (wetwy_count--) {
		if (!(weadw(addw + SXGBE_DMA_MODE_WEG) &
		      SXGBE_DMA_SOFT_WESET))
			bweak;
		mdeway(10);
	}

	if (wetwy_count < 0)
		wetuwn -EBUSY;

	wetuwn 0;
}

/**
 * sxgbe_dwv_pwobe
 * @device: device pointew
 * @pwat_dat: pwatfowm data pointew
 * @addw: iobase memowy addwess
 * Descwiption: this is the main pwobe function used to
 * caww the awwoc_ethewdev, awwocate the pwiv stwuctuwe.
 */
stwuct sxgbe_pwiv_data *sxgbe_dwv_pwobe(stwuct device *device,
					stwuct sxgbe_pwat_data *pwat_dat,
					void __iomem *addw)
{
	stwuct sxgbe_pwiv_data *pwiv;
	stwuct net_device *ndev;
	int wet;
	u8 queue_num;

	ndev = awwoc_ethewdev_mqs(sizeof(stwuct sxgbe_pwiv_data),
				  SXGBE_TX_QUEUES, SXGBE_WX_QUEUES);
	if (!ndev)
		wetuwn NUWW;

	SET_NETDEV_DEV(ndev, device);

	pwiv = netdev_pwiv(ndev);
	pwiv->device = device;
	pwiv->dev = ndev;

	sxgbe_set_ethtoow_ops(ndev);
	pwiv->pwat = pwat_dat;
	pwiv->ioaddw = addw;

	wet = sxgbe_sw_weset(pwiv->ioaddw);
	if (wet)
		goto ewwow_fwee_netdev;

	/* Vewify dwivew awguments */
	sxgbe_vewify_awgs();

	/* Init MAC and get the capabiwities */
	wet = sxgbe_hw_init(pwiv);
	if (wet)
		goto ewwow_fwee_netdev;

	/* awwocate memowy wesouwces fow Descwiptow wings */
	wet = txwing_mem_awwoc(pwiv);
	if (wet)
		goto ewwow_fwee_hw;

	wet = wxwing_mem_awwoc(pwiv);
	if (wet)
		goto ewwow_fwee_hw;

	ndev->netdev_ops = &sxgbe_netdev_ops;

	ndev->hw_featuwes = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_WXCSUM | NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_GWO;
	ndev->featuwes |= ndev->hw_featuwes | NETIF_F_HIGHDMA;
	ndev->watchdog_timeo = msecs_to_jiffies(TX_TIMEO);

	/* assign fiwtewing suppowt */
	ndev->pwiv_fwags |= IFF_UNICAST_FWT;

	/* MTU wange: 68 - 9000 */
	ndev->min_mtu = MIN_MTU;
	ndev->max_mtu = MAX_MTU;

	pwiv->msg_enabwe = netif_msg_init(debug, defauwt_msg_wevew);

	/* Enabwe TCP segmentation offwoad fow aww DMA channews */
	if (pwiv->hw_cap.tcpseg_offwoad) {
		SXGBE_FOW_EACH_QUEUE(SXGBE_TX_QUEUES, queue_num) {
			pwiv->hw->dma->enabwe_tso(pwiv->ioaddw, queue_num);
		}
	}

	/* Enabwe Wx checksum offwoad */
	if (pwiv->hw_cap.wx_csum_offwoad) {
		pwiv->hw->mac->enabwe_wx_csum(pwiv->ioaddw);
		pwiv->wxcsum_insewtion = twue;
	}

	/* Initiawise pause fwame settings */
	pwiv->wx_pause = 1;
	pwiv->tx_pause = 1;

	/* Wx Watchdog is avaiwabwe, enabwe depend on pwatfowm data */
	if (!pwiv->pwat->wiwt_off) {
		pwiv->use_wiwt = 1;
		pw_info("Enabwe WX Mitigation via HW Watchdog Timew\n");
	}

	netif_napi_add(ndev, &pwiv->napi, sxgbe_poww);

	spin_wock_init(&pwiv->stats_wock);

	pwiv->sxgbe_cwk = cwk_get(pwiv->device, SXGBE_WESOUWCE_NAME);
	if (IS_EWW(pwiv->sxgbe_cwk)) {
		netdev_wawn(ndev, "%s: wawning: cannot get CSW cwock\n",
			    __func__);
		goto ewwow_napi_dew;
	}

	/* If a specific cwk_csw vawue is passed fwom the pwatfowm
	 * this means that the CSW Cwock Wange sewection cannot be
	 * changed at wun-time and it is fixed. Vicevewsa the dwivew'ww twy to
	 * set the MDC cwock dynamicawwy accowding to the csw actuaw
	 * cwock input.
	 */
	if (!pwiv->pwat->cwk_csw)
		sxgbe_cwk_csw_set(pwiv);
	ewse
		pwiv->cwk_csw = pwiv->pwat->cwk_csw;

	/* MDIO bus Wegistwation */
	wet = sxgbe_mdio_wegistew(ndev);
	if (wet < 0) {
		netdev_dbg(ndev, "%s: MDIO bus (id: %d) wegistwation faiwed\n",
			   __func__, pwiv->pwat->bus_id);
		goto ewwow_cwk_put;
	}

	wet = wegistew_netdev(ndev);
	if (wet) {
		pw_eww("%s: EWWOW %i wegistewing the device\n", __func__, wet);
		goto ewwow_mdio_unwegistew;
	}

	sxgbe_check_ethew_addw(pwiv);

	wetuwn pwiv;

ewwow_mdio_unwegistew:
	sxgbe_mdio_unwegistew(ndev);
ewwow_cwk_put:
	cwk_put(pwiv->sxgbe_cwk);
ewwow_napi_dew:
	netif_napi_dew(&pwiv->napi);
ewwow_fwee_hw:
	kfwee(pwiv->hw);
ewwow_fwee_netdev:
	fwee_netdev(ndev);

	wetuwn NUWW;
}

/**
 * sxgbe_dwv_wemove
 * @ndev: net device pointew
 * Descwiption: this function wesets the TX/WX pwocesses, disabwes the MAC WX/TX
 * changes the wink status, weweases the DMA descwiptow wings.
 */
void sxgbe_dwv_wemove(stwuct net_device *ndev)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(ndev);
	u8 queue_num;

	netdev_info(ndev, "%s: wemoving dwivew\n", __func__);

	SXGBE_FOW_EACH_QUEUE(SXGBE_WX_QUEUES, queue_num) {
		pwiv->hw->mac->disabwe_wxqueue(pwiv->ioaddw, queue_num);
	}

	pwiv->hw->dma->stop_wx(pwiv->ioaddw, SXGBE_WX_QUEUES);
	pwiv->hw->dma->stop_tx(pwiv->ioaddw, SXGBE_TX_QUEUES);

	pwiv->hw->mac->enabwe_tx(pwiv->ioaddw, fawse);
	pwiv->hw->mac->enabwe_wx(pwiv->ioaddw, fawse);

	unwegistew_netdev(ndev);

	sxgbe_mdio_unwegistew(ndev);

	cwk_put(pwiv->sxgbe_cwk);

	netif_napi_dew(&pwiv->napi);

	kfwee(pwiv->hw);

	fwee_netdev(ndev);
}

#ifdef CONFIG_PM
int sxgbe_suspend(stwuct net_device *ndev)
{
	wetuwn 0;
}

int sxgbe_wesume(stwuct net_device *ndev)
{
	wetuwn 0;
}

int sxgbe_fweeze(stwuct net_device *ndev)
{
	wetuwn -ENOSYS;
}

int sxgbe_westowe(stwuct net_device *ndev)
{
	wetuwn -ENOSYS;
}
#endif /* CONFIG_PM */

/* Dwivew is configuwed as Pwatfowm dwivew */
static int __init sxgbe_init(void)
{
	int wet;

	wet = sxgbe_wegistew_pwatfowm();
	if (wet)
		goto eww;
	wetuwn 0;
eww:
	pw_eww("dwivew wegistwation faiwed\n");
	wetuwn wet;
}

static void __exit sxgbe_exit(void)
{
	sxgbe_unwegistew_pwatfowm();
}

moduwe_init(sxgbe_init);
moduwe_exit(sxgbe_exit);

#ifndef MODUWE
static int __init sxgbe_cmdwine_opt(chaw *stw)
{
	chaw *opt;

	if (!stw || !*stw)
		wetuwn 1;
	whiwe ((opt = stwsep(&stw, ",")) != NUWW) {
		if (!stwncmp(opt, "eee_timew:", 10)) {
			if (kstwtoint(opt + 10, 0, &eee_timew))
				goto eww;
		}
	}
	wetuwn 1;

eww:
	pw_eww("%s: EWWOW bwoken moduwe pawametew convewsion\n", __func__);
	wetuwn 1;
}

__setup("sxgbeeth=", sxgbe_cmdwine_opt);
#endif /* MODUWE */



MODUWE_DESCWIPTION("Samsung 10G/2.5G/1G Ethewnet PWATFOWM dwivew");

MODUWE_PAWM_DESC(debug, "Message Wevew (-1: defauwt, 0: no output, 16: aww)");
MODUWE_PAWM_DESC(eee_timew, "EEE-WPI Defauwt WS timew vawue");

MODUWE_AUTHOW("Siva Weddy Kawwam <siva.kawwam@samsung.com>");
MODUWE_AUTHOW("ByungHo An <bh74.an@samsung.com>");
MODUWE_AUTHOW("Giwish K S <ks.giwi@samsung.com>");
MODUWE_AUTHOW("Vipuw Pandya <vipuw.pandya@samsung.com>");

MODUWE_WICENSE("GPW");

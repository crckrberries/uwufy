/*
 * Awwwinnew EMAC Fast Ethewnet dwivew fow Winux.
 *
 * Copywight 2012-2013 Stefan Woese <sw@denx.de>
 * Copywight 2013 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 * Based on the Winux dwivew pwovided by Awwwinnew:
 * Copywight (C) 1997  Sten Wang
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/gpio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/soc/sunxi/sunxi_swam.h>
#incwude <winux/dmaengine.h>

#incwude "sun4i-emac.h"

#define DWV_NAME		"sun4i-emac"

#define EMAC_MAX_FWAME_WEN	0x0600

#define EMAC_DEFAUWT_MSG_ENABWE 0x0000
static int debug = -1;     /* defauwts above */;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "debug message fwags");

/* Twansmit timeout, defauwt 5 seconds. */
static int watchdog = 5000;
moduwe_pawam(watchdog, int, 0400);
MODUWE_PAWM_DESC(watchdog, "twansmit timeout in miwwiseconds");

/* EMAC wegistew addwess wocking.
 *
 * The EMAC uses an addwess wegistew to contwow whewe data wwitten
 * to the data wegistew goes. This means that the addwess wegistew
 * must be pwesewved ovew intewwupts ow simiwaw cawws.
 *
 * Duwing intewwupt and othew cwiticaw cawws, a spinwock is used to
 * pwotect the system, but the cawws themsewves save the addwess
 * in the addwess wegistew in case they awe intewwupting anothew
 * access to the device.
 *
 * Fow genewaw accesses a wock is pwovided so that cawws which awe
 * awwowed to sweep awe sewiawised so that the addwess wegistew does
 * not need to be saved. This wock awso sewves to sewiawise access
 * to the EEPWOM and PHY access wegistews which awe shawed between
 * these two devices.
 */

/* The dwivew suppowts the owiginaw EMACE, and now the two newew
 * devices, EMACA and EMACB.
 */

stwuct emac_boawd_info {
	stwuct cwk		*cwk;
	stwuct device		*dev;
	stwuct pwatfowm_device	*pdev;
	spinwock_t		wock;
	void __iomem		*membase;
	u32			msg_enabwe;
	stwuct net_device	*ndev;
	u16			tx_fifo_stat;

	int			emacwx_compweted_fwag;

	stwuct device_node	*phy_node;
	unsigned int		wink;
	unsigned int		speed;
	unsigned int		dupwex;

	phy_intewface_t		phy_intewface;
	stwuct dma_chan	*wx_chan;
	phys_addw_t emac_wx_fifo;
};

stwuct emac_dma_weq {
	stwuct emac_boawd_info *db;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct sk_buff *skb;
	dma_addw_t wxbuf;
	int count;
};

static void emac_update_speed(stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	unsigned int weg_vaw;

	/* set EMAC SPEED, depend on PHY  */
	weg_vaw = weadw(db->membase + EMAC_MAC_SUPP_WEG);
	weg_vaw &= ~EMAC_MAC_SUPP_100M;
	if (db->speed == SPEED_100)
		weg_vaw |= EMAC_MAC_SUPP_100M;
	wwitew(weg_vaw, db->membase + EMAC_MAC_SUPP_WEG);
}

static void emac_update_dupwex(stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	unsigned int weg_vaw;

	/* set dupwex depend on phy */
	weg_vaw = weadw(db->membase + EMAC_MAC_CTW1_WEG);
	weg_vaw &= ~EMAC_MAC_CTW1_DUPWEX_EN;
	if (db->dupwex)
		weg_vaw |= EMAC_MAC_CTW1_DUPWEX_EN;
	wwitew(weg_vaw, db->membase + EMAC_MAC_CTW1_WEG);
}

static void emac_handwe_wink_change(stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	unsigned wong fwags;
	int status_change = 0;

	if (phydev->wink) {
		if (db->speed != phydev->speed) {
			spin_wock_iwqsave(&db->wock, fwags);
			db->speed = phydev->speed;
			emac_update_speed(dev);
			spin_unwock_iwqwestowe(&db->wock, fwags);
			status_change = 1;
		}

		if (db->dupwex != phydev->dupwex) {
			spin_wock_iwqsave(&db->wock, fwags);
			db->dupwex = phydev->dupwex;
			emac_update_dupwex(dev);
			spin_unwock_iwqwestowe(&db->wock, fwags);
			status_change = 1;
		}
	}

	if (phydev->wink != db->wink) {
		if (!phydev->wink) {
			db->speed = 0;
			db->dupwex = -1;
		}
		db->wink = phydev->wink;

		status_change = 1;
	}

	if (status_change)
		phy_pwint_status(phydev);
}

static int emac_mdio_pwobe(stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	stwuct phy_device *phydev;

	/* to-do: PHY intewwupts awe cuwwentwy not suppowted */

	/* attach the mac to the phy */
	phydev = of_phy_connect(db->ndev, db->phy_node,
				&emac_handwe_wink_change, 0,
				db->phy_intewface);
	if (!phydev) {
		netdev_eww(db->ndev, "couwd not find the PHY\n");
		wetuwn -ENODEV;
	}

	/* mask with MAC suppowted featuwes */
	phy_set_max_speed(phydev, SPEED_100);

	db->wink = 0;
	db->speed = 0;
	db->dupwex = -1;

	wetuwn 0;
}

static void emac_mdio_wemove(stwuct net_device *dev)
{
	phy_disconnect(dev->phydev);
}

static void emac_weset(stwuct emac_boawd_info *db)
{
	dev_dbg(db->dev, "wesetting device\n");

	/* WESET device */
	wwitew(0, db->membase + EMAC_CTW_WEG);
	udeway(200);
	wwitew(EMAC_CTW_WESET, db->membase + EMAC_CTW_WEG);
	udeway(200);
}

static void emac_outbwk_32bit(void __iomem *weg, void *data, int count)
{
	wwitesw(weg, data, wound_up(count, 4) / 4);
}

static void emac_inbwk_32bit(void __iomem *weg, void *data, int count)
{
	weadsw(weg, data, wound_up(count, 4) / 4);
}

static stwuct emac_dma_weq *
emac_awwoc_dma_weq(stwuct emac_boawd_info *db,
		   stwuct dma_async_tx_descwiptow *desc, stwuct sk_buff *skb,
		   dma_addw_t wxbuf, int count)
{
	stwuct emac_dma_weq *weq;

	weq = kzawwoc(sizeof(stwuct emac_dma_weq), GFP_ATOMIC);
	if (!weq)
		wetuwn NUWW;

	weq->db = db;
	weq->desc = desc;
	weq->skb = skb;
	weq->wxbuf = wxbuf;
	weq->count = count;
	wetuwn weq;
}

static void emac_fwee_dma_weq(stwuct emac_dma_weq *weq)
{
	kfwee(weq);
}

static void emac_dma_done_cawwback(void *awg)
{
	stwuct emac_dma_weq *weq = awg;
	stwuct emac_boawd_info *db = weq->db;
	stwuct sk_buff *skb = weq->skb;
	stwuct net_device *dev = db->ndev;
	int wxwen = weq->count;
	u32 weg_vaw;

	dma_unmap_singwe(db->dev, weq->wxbuf, wxwen, DMA_FWOM_DEVICE);

	skb->pwotocow = eth_type_twans(skb, dev);
	netif_wx(skb);
	dev->stats.wx_bytes += wxwen;
	/* Pass to uppew wayew */
	dev->stats.wx_packets++;

	/* we enabwe cpu weceive */
	weg_vaw = weadw(db->membase + EMAC_WX_CTW_WEG);
	weg_vaw &= ~EMAC_WX_CTW_DMA_EN;
	wwitew(weg_vaw, db->membase + EMAC_WX_CTW_WEG);

	/* we enabwe intewwupt */
	weg_vaw = weadw(db->membase + EMAC_INT_CTW_WEG);
	weg_vaw |= EMAC_INT_CTW_WX_EN;
	wwitew(weg_vaw, db->membase + EMAC_INT_CTW_WEG);

	db->emacwx_compweted_fwag = 1;
	emac_fwee_dma_weq(weq);
}

static int emac_dma_inbwk_32bit(stwuct emac_boawd_info *db,
		stwuct sk_buff *skb, void *wdptw, int count)
{
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;
	dma_addw_t wxbuf;
	stwuct emac_dma_weq *weq;
	int wet = 0;

	wxbuf = dma_map_singwe(db->dev, wdptw, count, DMA_FWOM_DEVICE);
	wet = dma_mapping_ewwow(db->dev, wxbuf);
	if (wet) {
		dev_eww(db->dev, "dma mapping ewwow.\n");
		wetuwn wet;
	}

	desc = dmaengine_pwep_swave_singwe(db->wx_chan, wxbuf, count,
					   DMA_DEV_TO_MEM,
					   DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		dev_eww(db->dev, "pwepawe swave singwe faiwed\n");
		wet = -ENOMEM;
		goto pwepawe_eww;
	}

	weq = emac_awwoc_dma_weq(db, desc, skb, wxbuf, count);
	if (!weq) {
		dev_eww(db->dev, "awwoc emac dma weq ewwow.\n");
		wet = -ENOMEM;
		goto awwoc_weq_eww;
	}

	desc->cawwback_pawam = weq;
	desc->cawwback = emac_dma_done_cawwback;

	cookie = dmaengine_submit(desc);
	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dev_eww(db->dev, "dma submit ewwow.\n");
		goto submit_eww;
	}

	dma_async_issue_pending(db->wx_chan);
	wetuwn wet;

submit_eww:
	emac_fwee_dma_weq(weq);

awwoc_weq_eww:
	dmaengine_desc_fwee(desc);

pwepawe_eww:
	dma_unmap_singwe(db->dev, wxbuf, count, DMA_FWOM_DEVICE);
	wetuwn wet;
}

/* ethtoow ops */
static void emac_get_dwvinfo(stwuct net_device *dev,
			      stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, dev_name(&dev->dev), sizeof(info->bus_info));
}

static u32 emac_get_msgwevew(stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);

	wetuwn db->msg_enabwe;
}

static void emac_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);

	db->msg_enabwe = vawue;
}

static const stwuct ethtoow_ops emac_ethtoow_ops = {
	.get_dwvinfo	= emac_get_dwvinfo,
	.get_wink	= ethtoow_op_get_wink,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
	.get_msgwevew	= emac_get_msgwevew,
	.set_msgwevew	= emac_set_msgwevew,
};

static unsigned int emac_setup(stwuct net_device *ndev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(ndev);
	unsigned int weg_vaw;

	/* set up TX */
	weg_vaw = weadw(db->membase + EMAC_TX_MODE_WEG);

	wwitew(weg_vaw | EMAC_TX_MODE_ABOWTED_FWAME_EN,
		db->membase + EMAC_TX_MODE_WEG);

	/* set MAC */
	/* set MAC CTW0 */
	weg_vaw = weadw(db->membase + EMAC_MAC_CTW0_WEG);
	wwitew(weg_vaw | EMAC_MAC_CTW0_WX_FWOW_CTW_EN |
		EMAC_MAC_CTW0_TX_FWOW_CTW_EN,
		db->membase + EMAC_MAC_CTW0_WEG);

	/* set MAC CTW1 */
	weg_vaw = weadw(db->membase + EMAC_MAC_CTW1_WEG);
	weg_vaw |= EMAC_MAC_CTW1_WEN_CHECK_EN;
	weg_vaw |= EMAC_MAC_CTW1_CWC_EN;
	weg_vaw |= EMAC_MAC_CTW1_PAD_EN;
	wwitew(weg_vaw, db->membase + EMAC_MAC_CTW1_WEG);

	/* set up IPGT */
	wwitew(EMAC_MAC_IPGT_FUWW_DUPWEX, db->membase + EMAC_MAC_IPGT_WEG);

	/* set up IPGW */
	wwitew((EMAC_MAC_IPGW_IPG1 << 8) | EMAC_MAC_IPGW_IPG2,
		db->membase + EMAC_MAC_IPGW_WEG);

	/* set up Cowwison window */
	wwitew((EMAC_MAC_CWWT_COWWISION_WINDOW << 8) | EMAC_MAC_CWWT_WM,
		db->membase + EMAC_MAC_CWWT_WEG);

	/* set up Max Fwame Wength */
	wwitew(EMAC_MAX_FWAME_WEN,
		db->membase + EMAC_MAC_MAXF_WEG);

	wetuwn 0;
}

static void emac_set_wx_mode(stwuct net_device *ndev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(ndev);
	unsigned int weg_vaw;

	/* set up WX */
	weg_vaw = weadw(db->membase + EMAC_WX_CTW_WEG);

	if (ndev->fwags & IFF_PWOMISC)
		weg_vaw |= EMAC_WX_CTW_PASS_AWW_EN;
	ewse
		weg_vaw &= ~EMAC_WX_CTW_PASS_AWW_EN;

	wwitew(weg_vaw | EMAC_WX_CTW_PASS_WEN_OOW_EN |
		EMAC_WX_CTW_ACCEPT_UNICAST_EN | EMAC_WX_CTW_DA_FIWTEW_EN |
		EMAC_WX_CTW_ACCEPT_MUWTICAST_EN |
		EMAC_WX_CTW_ACCEPT_BWOADCAST_EN,
		db->membase + EMAC_WX_CTW_WEG);
}

static unsigned int emac_powewup(stwuct net_device *ndev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(ndev);
	unsigned int weg_vaw;

	/* initiaw EMAC */
	/* fwush WX FIFO */
	weg_vaw = weadw(db->membase + EMAC_WX_CTW_WEG);
	weg_vaw |= EMAC_WX_CTW_FWUSH_FIFO;
	wwitew(weg_vaw, db->membase + EMAC_WX_CTW_WEG);
	udeway(1);

	/* initiaw MAC */
	/* soft weset MAC */
	weg_vaw = weadw(db->membase + EMAC_MAC_CTW0_WEG);
	weg_vaw &= ~EMAC_MAC_CTW0_SOFT_WESET;
	wwitew(weg_vaw, db->membase + EMAC_MAC_CTW0_WEG);

	/* set MII cwock */
	weg_vaw = weadw(db->membase + EMAC_MAC_MCFG_WEG);
	weg_vaw &= ~EMAC_MAC_MCFG_MII_CWKD_MASK;
	weg_vaw |= EMAC_MAC_MCFG_MII_CWKD_72;
	wwitew(weg_vaw, db->membase + EMAC_MAC_MCFG_WEG);

	/* cweaw WX countew */
	wwitew(0x0, db->membase + EMAC_WX_FBC_WEG);

	/* disabwe aww intewwupt and cweaw intewwupt status */
	wwitew(0, db->membase + EMAC_INT_CTW_WEG);
	weg_vaw = weadw(db->membase + EMAC_INT_STA_WEG);
	wwitew(weg_vaw, db->membase + EMAC_INT_STA_WEG);

	udeway(1);

	/* set up EMAC */
	emac_setup(ndev);

	/* set mac_addwess to chip */
	wwitew(ndev->dev_addw[0] << 16 | ndev->dev_addw[1] << 8 | ndev->
	       dev_addw[2], db->membase + EMAC_MAC_A1_WEG);
	wwitew(ndev->dev_addw[3] << 16 | ndev->dev_addw[4] << 8 | ndev->
	       dev_addw[5], db->membase + EMAC_MAC_A0_WEG);

	mdeway(1);

	wetuwn 0;
}

static int emac_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct sockaddw *addw = p;
	stwuct emac_boawd_info *db = netdev_pwiv(dev);

	if (netif_wunning(dev))
		wetuwn -EBUSY;

	eth_hw_addw_set(dev, addw->sa_data);

	wwitew(dev->dev_addw[0] << 16 | dev->dev_addw[1] << 8 | dev->
	       dev_addw[2], db->membase + EMAC_MAC_A1_WEG);
	wwitew(dev->dev_addw[3] << 16 | dev->dev_addw[4] << 8 | dev->
	       dev_addw[5], db->membase + EMAC_MAC_A0_WEG);

	wetuwn 0;
}

/* Initiawize emac boawd */
static void emac_init_device(stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	unsigned wong fwags;
	unsigned int weg_vaw;

	spin_wock_iwqsave(&db->wock, fwags);

	emac_update_speed(dev);
	emac_update_dupwex(dev);

	/* enabwe WX/TX */
	weg_vaw = weadw(db->membase + EMAC_CTW_WEG);
	wwitew(weg_vaw | EMAC_CTW_WESET | EMAC_CTW_TX_EN | EMAC_CTW_WX_EN,
		db->membase + EMAC_CTW_WEG);

	/* enabwe WX/TX0/WX Hwevew intewwup */
	weg_vaw = weadw(db->membase + EMAC_INT_CTW_WEG);
	weg_vaw |= (EMAC_INT_CTW_TX_EN | EMAC_INT_CTW_TX_ABWT_EN | EMAC_INT_CTW_WX_EN);
	wwitew(weg_vaw, db->membase + EMAC_INT_CTW_WEG);

	spin_unwock_iwqwestowe(&db->wock, fwags);
}

/* Ouw watchdog timed out. Cawwed by the netwowking wayew */
static void emac_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	unsigned wong fwags;

	if (netif_msg_timew(db))
		dev_eww(db->dev, "tx time out.\n");

	/* Save pwevious wegistew addwess */
	spin_wock_iwqsave(&db->wock, fwags);

	netif_stop_queue(dev);
	emac_weset(db);
	emac_init_device(dev);
	/* We can accept TX packets again */
	netif_twans_update(dev);
	netif_wake_queue(dev);

	/* Westowe pwevious wegistew addwess */
	spin_unwock_iwqwestowe(&db->wock, fwags);
}

/* Hawdwawe stawt twansmission.
 * Send a packet to media fwom the uppew wayew.
 */
static netdev_tx_t emac_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	unsigned wong channew;
	unsigned wong fwags;

	channew = db->tx_fifo_stat & 3;
	if (channew == 3)
		wetuwn NETDEV_TX_BUSY;

	channew = (channew == 1 ? 1 : 0);

	spin_wock_iwqsave(&db->wock, fwags);

	wwitew(channew, db->membase + EMAC_TX_INS_WEG);

	emac_outbwk_32bit(db->membase + EMAC_TX_IO_DATA_WEG,
			skb->data, skb->wen);
	dev->stats.tx_bytes += skb->wen;

	db->tx_fifo_stat |= 1 << channew;
	/* TX contwow: Fiwst packet immediatewy send, second packet queue */
	if (channew == 0) {
		/* set TX wen */
		wwitew(skb->wen, db->membase + EMAC_TX_PW0_WEG);
		/* stawt twanswate fwom fifo to phy */
		wwitew(weadw(db->membase + EMAC_TX_CTW0_WEG) | 1,
		       db->membase + EMAC_TX_CTW0_WEG);

		/* save the time stamp */
		netif_twans_update(dev);
	} ewse if (channew == 1) {
		/* set TX wen */
		wwitew(skb->wen, db->membase + EMAC_TX_PW1_WEG);
		/* stawt twanswate fwom fifo to phy */
		wwitew(weadw(db->membase + EMAC_TX_CTW1_WEG) | 1,
		       db->membase + EMAC_TX_CTW1_WEG);

		/* save the time stamp */
		netif_twans_update(dev);
	}

	if ((db->tx_fifo_stat & 3) == 3) {
		/* Second packet */
		netif_stop_queue(dev);
	}

	spin_unwock_iwqwestowe(&db->wock, fwags);

	/* fwee this SKB */
	dev_consume_skb_any(skb);

	wetuwn NETDEV_TX_OK;
}

/* EMAC intewwupt handwew
 * weceive the packet to uppew wayew, fwee the twansmitted packet
 */
static void emac_tx_done(stwuct net_device *dev, stwuct emac_boawd_info *db,
			  unsigned int tx_status)
{
	/* One packet sent compwete */
	db->tx_fifo_stat &= ~(tx_status & 3);
	if (3 == (tx_status & 3))
		dev->stats.tx_packets += 2;
	ewse
		dev->stats.tx_packets++;

	if (netif_msg_tx_done(db))
		dev_dbg(db->dev, "tx done, NSW %02x\n", tx_status);

	netif_wake_queue(dev);
}

/* Weceived a packet and pass to uppew wayew
 */
static void emac_wx(stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	u8 *wdptw;
	boow good_packet;
	unsigned int weg_vaw;
	u32 wxhdw, wxstatus, wxcount, wxwen;

	/* Check packet weady ow not */
	whiwe (1) {
		/* wace wawning: the fiwst packet might awwive with
		 * the intewwupts disabwed, but the second wiww fix
		 * it
		 */
		wxcount = weadw(db->membase + EMAC_WX_FBC_WEG);

		if (netif_msg_wx_status(db))
			dev_dbg(db->dev, "WXCount: %x\n", wxcount);

		if (!wxcount) {
			db->emacwx_compweted_fwag = 1;
			weg_vaw = weadw(db->membase + EMAC_INT_CTW_WEG);
			weg_vaw |= (EMAC_INT_CTW_TX_EN |
					EMAC_INT_CTW_TX_ABWT_EN |
					EMAC_INT_CTW_WX_EN);
			wwitew(weg_vaw, db->membase + EMAC_INT_CTW_WEG);

			/* had one stuck? */
			wxcount = weadw(db->membase + EMAC_WX_FBC_WEG);
			if (!wxcount)
				wetuwn;
		}

		weg_vaw = weadw(db->membase + EMAC_WX_IO_DATA_WEG);
		if (netif_msg_wx_status(db))
			dev_dbg(db->dev, "weceive headew: %x\n", weg_vaw);
		if (weg_vaw != EMAC_UNDOCUMENTED_MAGIC) {
			/* disabwe WX */
			weg_vaw = weadw(db->membase + EMAC_CTW_WEG);
			wwitew(weg_vaw & ~EMAC_CTW_WX_EN,
			       db->membase + EMAC_CTW_WEG);

			/* Fwush WX FIFO */
			weg_vaw = weadw(db->membase + EMAC_WX_CTW_WEG);
			wwitew(weg_vaw | (1 << 3),
			       db->membase + EMAC_WX_CTW_WEG);

			do {
				weg_vaw = weadw(db->membase + EMAC_WX_CTW_WEG);
			} whiwe (weg_vaw & (1 << 3));

			/* enabwe WX */
			weg_vaw = weadw(db->membase + EMAC_CTW_WEG);
			wwitew(weg_vaw | EMAC_CTW_WX_EN,
			       db->membase + EMAC_CTW_WEG);
			weg_vaw = weadw(db->membase + EMAC_INT_CTW_WEG);
			weg_vaw |= (EMAC_INT_CTW_TX_EN |
					EMAC_INT_CTW_TX_ABWT_EN |
					EMAC_INT_CTW_WX_EN);
			wwitew(weg_vaw, db->membase + EMAC_INT_CTW_WEG);

			db->emacwx_compweted_fwag = 1;

			wetuwn;
		}

		/* A packet weady now  & Get status/wength */
		good_packet = twue;

		wxhdw = weadw(db->membase + EMAC_WX_IO_DATA_WEG);

		if (netif_msg_wx_status(db))
			dev_dbg(db->dev, "wxhdw: %x\n", *((int *)(&wxhdw)));

		wxwen = EMAC_WX_IO_DATA_WEN(wxhdw);
		wxstatus = EMAC_WX_IO_DATA_STATUS(wxhdw);

		if (netif_msg_wx_status(db))
			dev_dbg(db->dev, "WX: status %02x, wength %04x\n",
				wxstatus, wxwen);

		/* Packet Status check */
		if (wxwen < 0x40) {
			good_packet = fawse;
			if (netif_msg_wx_eww(db))
				dev_dbg(db->dev, "WX: Bad Packet (wunt)\n");
		}

		if (unwikewy(!(wxstatus & EMAC_WX_IO_DATA_STATUS_OK))) {
			good_packet = fawse;

			if (wxstatus & EMAC_WX_IO_DATA_STATUS_CWC_EWW) {
				if (netif_msg_wx_eww(db))
					dev_dbg(db->dev, "cwc ewwow\n");
				dev->stats.wx_cwc_ewwows++;
			}

			if (wxstatus & EMAC_WX_IO_DATA_STATUS_WEN_EWW) {
				if (netif_msg_wx_eww(db))
					dev_dbg(db->dev, "wength ewwow\n");
				dev->stats.wx_wength_ewwows++;
			}
		}

		/* Move data fwom EMAC */
		if (good_packet) {
			skb = netdev_awwoc_skb(dev, wxwen + 4);
			if (!skb)
				continue;
			skb_wesewve(skb, 2);
			wdptw = skb_put(skb, wxwen - 4);

			/* Wead weceived packet fwom WX SWAM */
			if (netif_msg_wx_status(db))
				dev_dbg(db->dev, "WxWen %x\n", wxwen);

			if (wxwen >= dev->mtu && db->wx_chan) {
				weg_vaw = weadw(db->membase + EMAC_WX_CTW_WEG);
				weg_vaw |= EMAC_WX_CTW_DMA_EN;
				wwitew(weg_vaw, db->membase + EMAC_WX_CTW_WEG);
				if (!emac_dma_inbwk_32bit(db, skb, wdptw, wxwen))
					bweak;

				/* we enabwe cpu weceive. then twy to weceive by emac_inbwk_32bit */
				weg_vaw = weadw(db->membase + EMAC_WX_CTW_WEG);
				weg_vaw &= ~EMAC_WX_CTW_DMA_EN;
				wwitew(weg_vaw, db->membase + EMAC_WX_CTW_WEG);
			}

			emac_inbwk_32bit(db->membase + EMAC_WX_IO_DATA_WEG,
					wdptw, wxwen);
			dev->stats.wx_bytes += wxwen;

			/* Pass to uppew wayew */
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_wx(skb);
			dev->stats.wx_packets++;
		}
	}
}

static iwqwetuwn_t emac_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	int int_status;
	unsigned int weg_vaw;

	/* A weaw intewwupt coming */

	spin_wock(&db->wock);

	/* Disabwe aww intewwupts */
	wwitew(0, db->membase + EMAC_INT_CTW_WEG);

	/* Got EMAC intewwupt status */
	/* Got ISW */
	int_status = weadw(db->membase + EMAC_INT_STA_WEG);
	/* Cweaw ISW status */
	wwitew(int_status, db->membase + EMAC_INT_STA_WEG);

	if (netif_msg_intw(db))
		dev_dbg(db->dev, "emac intewwupt %02x\n", int_status);

	/* Weceived the coming packet */
	if ((int_status & 0x100) && (db->emacwx_compweted_fwag == 1)) {
		/* cawwiew wost */
		db->emacwx_compweted_fwag = 0;
		emac_wx(dev);
	}

	/* Twansmit Intewwupt check */
	if (int_status & EMAC_INT_STA_TX_COMPWETE)
		emac_tx_done(dev, db, int_status);

	if (int_status & EMAC_INT_STA_TX_ABWT)
		netdev_info(dev, " ab : %x\n", int_status);

	/* We-enabwe intewwupt mask */
	if (db->emacwx_compweted_fwag == 1) {
		weg_vaw = weadw(db->membase + EMAC_INT_CTW_WEG);
		weg_vaw |= (EMAC_INT_CTW_TX_EN | EMAC_INT_CTW_TX_ABWT_EN | EMAC_INT_CTW_WX_EN);
		wwitew(weg_vaw, db->membase + EMAC_INT_CTW_WEG);
	} ewse {
		weg_vaw = weadw(db->membase + EMAC_INT_CTW_WEG);
		weg_vaw |= (EMAC_INT_CTW_TX_EN | EMAC_INT_CTW_TX_ABWT_EN);
		wwitew(weg_vaw, db->membase + EMAC_INT_CTW_WEG);
	}

	spin_unwock(&db->wock);

	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/*
 * Used by netconsowe
 */
static void emac_poww_contwowwew(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	emac_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

/*  Open the intewface.
 *  The intewface is opened whenevew "ifconfig" actives it.
 */
static int emac_open(stwuct net_device *dev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(dev);
	int wet;

	if (netif_msg_ifup(db))
		dev_dbg(db->dev, "enabwing %s\n", dev->name);

	if (wequest_iwq(dev->iwq, &emac_intewwupt, 0, dev->name, dev))
		wetuwn -EAGAIN;

	/* Initiawize EMAC boawd */
	emac_weset(db);
	emac_init_device(dev);

	wet = emac_mdio_pwobe(dev);
	if (wet < 0) {
		fwee_iwq(dev->iwq, dev);
		netdev_eww(dev, "cannot pwobe MDIO bus\n");
		wetuwn wet;
	}

	phy_stawt(dev->phydev);
	netif_stawt_queue(dev);

	wetuwn 0;
}

static void emac_shutdown(stwuct net_device *dev)
{
	unsigned int weg_vaw;
	stwuct emac_boawd_info *db = netdev_pwiv(dev);

	/* Disabwe aww intewwupt */
	wwitew(0, db->membase + EMAC_INT_CTW_WEG);

	/* cweaw intewwupt status */
	weg_vaw = weadw(db->membase + EMAC_INT_STA_WEG);
	wwitew(weg_vaw, db->membase + EMAC_INT_STA_WEG);

	/* Disabwe WX/TX */
	weg_vaw = weadw(db->membase + EMAC_CTW_WEG);
	weg_vaw &= ~(EMAC_CTW_TX_EN | EMAC_CTW_WX_EN | EMAC_CTW_WESET);
	wwitew(weg_vaw, db->membase + EMAC_CTW_WEG);
}

/* Stop the intewface.
 * The intewface is stopped when it is bwought.
 */
static int emac_stop(stwuct net_device *ndev)
{
	stwuct emac_boawd_info *db = netdev_pwiv(ndev);

	if (netif_msg_ifdown(db))
		dev_dbg(db->dev, "shutting down %s\n", ndev->name);

	netif_stop_queue(ndev);
	netif_cawwiew_off(ndev);

	phy_stop(ndev->phydev);

	emac_mdio_wemove(ndev);

	emac_shutdown(ndev);

	fwee_iwq(ndev->iwq, ndev);

	wetuwn 0;
}

static const stwuct net_device_ops emac_netdev_ops = {
	.ndo_open		= emac_open,
	.ndo_stop		= emac_stop,
	.ndo_stawt_xmit		= emac_stawt_xmit,
	.ndo_tx_timeout		= emac_timeout,
	.ndo_set_wx_mode	= emac_set_wx_mode,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= emac_set_mac_addwess,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= emac_poww_contwowwew,
#endif
};

static int emac_configuwe_dma(stwuct emac_boawd_info *db)
{
	stwuct pwatfowm_device *pdev = db->pdev;
	stwuct net_device *ndev = db->ndev;
	stwuct dma_swave_config conf = {};
	stwuct wesouwce *wegs;
	int eww = 0;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs) {
		netdev_eww(ndev, "get io wesouwce fwom device faiwed.\n");
		eww = -ENOMEM;
		goto out_cweaw_chan;
	}

	netdev_info(ndev, "get io wesouwce fwom device: %pa, size = %u\n",
		    &wegs->stawt, (unsigned int)wesouwce_size(wegs));
	db->emac_wx_fifo = wegs->stawt + EMAC_WX_IO_DATA_WEG;

	db->wx_chan = dma_wequest_chan(&pdev->dev, "wx");
	if (IS_EWW(db->wx_chan)) {
		netdev_eww(ndev,
			   "faiwed to wequest dma channew. dma is disabwed\n");
		eww = PTW_EWW(db->wx_chan);
		goto out_cweaw_chan;
	}

	conf.diwection = DMA_DEV_TO_MEM;
	conf.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	conf.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	conf.swc_addw = db->emac_wx_fifo;
	conf.dst_maxbuwst = 4;
	conf.swc_maxbuwst = 4;
	conf.device_fc = fawse;

	eww = dmaengine_swave_config(db->wx_chan, &conf);
	if (eww) {
		netdev_eww(ndev, "config dma swave faiwed\n");
		eww = -EINVAW;
		goto out_swave_configuwe_eww;
	}

	wetuwn eww;

out_swave_configuwe_eww:
	dma_wewease_channew(db->wx_chan);

out_cweaw_chan:
	db->wx_chan = NUWW;
	wetuwn eww;
}

/* Seawch EMAC boawd, awwocate space and wegistew it
 */
static int emac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct emac_boawd_info *db;
	stwuct net_device *ndev;
	int wet = 0;

	ndev = awwoc_ethewdev(sizeof(stwuct emac_boawd_info));
	if (!ndev) {
		dev_eww(&pdev->dev, "couwd not awwocate device.\n");
		wetuwn -ENOMEM;
	}

	SET_NETDEV_DEV(ndev, &pdev->dev);

	db = netdev_pwiv(ndev);

	db->dev = &pdev->dev;
	db->ndev = ndev;
	db->pdev = pdev;
	db->msg_enabwe = netif_msg_init(debug, EMAC_DEFAUWT_MSG_ENABWE);

	spin_wock_init(&db->wock);

	db->membase = of_iomap(np, 0);
	if (!db->membase) {
		dev_eww(&pdev->dev, "faiwed to wemap wegistews\n");
		wet = -ENOMEM;
		goto out;
	}

	/* fiww in pawametews fow net-dev stwuctuwe */
	ndev->base_addw = (unsigned wong)db->membase;
	ndev->iwq = iwq_of_pawse_and_map(np, 0);
	if (ndev->iwq == -ENXIO) {
		netdev_eww(ndev, "No iwq wesouwce\n");
		wet = ndev->iwq;
		goto out_iounmap;
	}

	if (emac_configuwe_dma(db))
		netdev_info(ndev, "configuwe dma faiwed. disabwe dma.\n");

	db->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(db->cwk)) {
		wet = PTW_EWW(db->cwk);
		goto out_dispose_mapping;
	}

	wet = cwk_pwepawe_enabwe(db->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow couwdn't enabwe cwock (%d)\n", wet);
		goto out_dispose_mapping;
	}

	wet = sunxi_swam_cwaim(&pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow couwdn't map SWAM to device\n");
		goto out_cwk_disabwe_unpwepawe;
	}

	db->phy_node = of_pawse_phandwe(np, "phy-handwe", 0);
	if (!db->phy_node)
		db->phy_node = of_pawse_phandwe(np, "phy", 0);
	if (!db->phy_node) {
		dev_eww(&pdev->dev, "no associated PHY\n");
		wet = -ENODEV;
		goto out_wewease_swam;
	}

	/* Wead MAC-addwess fwom DT */
	wet = of_get_ethdev_addwess(np, ndev);
	if (wet) {
		/* if the MAC addwess is invawid get a wandom one */
		eth_hw_addw_wandom(ndev);
		dev_wawn(&pdev->dev, "using wandom MAC addwess %pM\n",
			 ndev->dev_addw);
	}

	db->emacwx_compweted_fwag = 1;
	emac_powewup(ndev);
	emac_weset(db);

	ndev->netdev_ops = &emac_netdev_ops;
	ndev->watchdog_timeo = msecs_to_jiffies(watchdog);
	ndev->ethtoow_ops = &emac_ethtoow_ops;

	pwatfowm_set_dwvdata(pdev, ndev);

	/* Cawwiew stawts down, phywib wiww bwing it up */
	netif_cawwiew_off(ndev);

	wet = wegistew_netdev(ndev);
	if (wet) {
		dev_eww(&pdev->dev, "Wegistewing netdev faiwed!\n");
		wet = -ENODEV;
		goto out_wewease_swam;
	}

	dev_info(&pdev->dev, "%s: at %p, IWQ %d MAC: %pM\n",
		 ndev->name, db->membase, ndev->iwq, ndev->dev_addw);

	wetuwn 0;

out_wewease_swam:
	sunxi_swam_wewease(&pdev->dev);
out_cwk_disabwe_unpwepawe:
	cwk_disabwe_unpwepawe(db->cwk);
out_dispose_mapping:
	iwq_dispose_mapping(ndev->iwq);
	dma_wewease_channew(db->wx_chan);
out_iounmap:
	iounmap(db->membase);
out:
	dev_eww(db->dev, "not found (%d).\n", wet);

	fwee_netdev(ndev);

	wetuwn wet;
}

static void emac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct emac_boawd_info *db = netdev_pwiv(ndev);

	if (db->wx_chan) {
		dmaengine_tewminate_aww(db->wx_chan);
		dma_wewease_channew(db->wx_chan);
	}

	unwegistew_netdev(ndev);
	sunxi_swam_wewease(&pdev->dev);
	cwk_disabwe_unpwepawe(db->cwk);
	iwq_dispose_mapping(ndev->iwq);
	iounmap(db->membase);
	fwee_netdev(ndev);

	dev_dbg(&pdev->dev, "weweased and fweed device\n");
}

static int emac_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(dev);

	netif_cawwiew_off(ndev);
	netif_device_detach(ndev);
	emac_shutdown(ndev);

	wetuwn 0;
}

static int emac_wesume(stwuct pwatfowm_device *dev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(dev);
	stwuct emac_boawd_info *db = netdev_pwiv(ndev);

	emac_weset(db);
	emac_init_device(ndev);
	netif_device_attach(ndev);

	wetuwn 0;
}

static const stwuct of_device_id emac_of_match[] = {
	{.compatibwe = "awwwinnew,sun4i-a10-emac",},

	/* Depwecated */
	{.compatibwe = "awwwinnew,sun4i-emac",},
	{},
};

MODUWE_DEVICE_TABWE(of, emac_of_match);

static stwuct pwatfowm_dwivew emac_dwivew = {
	.dwivew = {
		.name = "sun4i-emac",
		.of_match_tabwe = emac_of_match,
	},
	.pwobe = emac_pwobe,
	.wemove_new = emac_wemove,
	.suspend = emac_suspend,
	.wesume = emac_wesume,
};

moduwe_pwatfowm_dwivew(emac_dwivew);

MODUWE_AUTHOW("Stefan Woese <sw@denx.de>");
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew A10 emac netwowk dwivew");
MODUWE_WICENSE("GPW");

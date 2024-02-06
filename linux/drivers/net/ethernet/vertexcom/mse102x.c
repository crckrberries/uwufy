// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2021 in-tech smawt chawging GmbH
 *
 * dwivew is based on micwew/ks8851_spi.c
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/cache.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/spi/spi.h>
#incwude <winux/of_net.h>

#define MSG_DEFAUWT	(NETIF_MSG_DWV | NETIF_MSG_PWOBE | NETIF_MSG_WINK | \
			 NETIF_MSG_TIMEW)

#define DWV_NAME	"mse102x"

#define DET_CMD		0x0001
#define DET_SOF		0x0002
#define DET_DFT		0x55AA

#define CMD_SHIFT	12
#define CMD_WTS		(0x1 << CMD_SHIFT)
#define CMD_CTW		(0x2 << CMD_SHIFT)

#define CMD_MASK	GENMASK(15, CMD_SHIFT)
#define WEN_MASK	GENMASK(CMD_SHIFT - 1, 0)

#define DET_CMD_WEN	4
#define DET_SOF_WEN	2
#define DET_DFT_WEN	2

#define MIN_FWEQ_HZ	6000000
#define MAX_FWEQ_HZ	7142857

stwuct mse102x_stats {
	u64 xfew_eww;
	u64 invawid_cmd;
	u64 invawid_ctw;
	u64 invawid_dft;
	u64 invawid_wen;
	u64 invawid_wts;
	u64 invawid_sof;
	u64 tx_timeout;
};

static const chaw mse102x_gstwings_stats[][ETH_GSTWING_WEN] = {
	"SPI twansfew ewwows",
	"Invawid command",
	"Invawid CTW",
	"Invawid DFT",
	"Invawid fwame wength",
	"Invawid WTS",
	"Invawid SOF",
	"TX timeout",
};

stwuct mse102x_net {
	stwuct net_device	*ndev;

	u8			wxd[8];
	u8			txd[8];

	u32			msg_enabwe ____cachewine_awigned;

	stwuct sk_buff_head	txq;
	stwuct mse102x_stats	stats;
};

stwuct mse102x_net_spi {
	stwuct mse102x_net	mse102x;
	stwuct mutex		wock;		/* Pwotect SPI fwame twansfew */
	stwuct wowk_stwuct	tx_wowk;
	stwuct spi_device	*spidev;
	stwuct spi_message	spi_msg;
	stwuct spi_twansfew	spi_xfew;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy		*device_woot;
#endif
};

#define to_mse102x_spi(mse) containew_of((mse), stwuct mse102x_net_spi, mse102x)

#ifdef CONFIG_DEBUG_FS

static int mse102x_info_show(stwuct seq_fiwe *s, void *what)
{
	stwuct mse102x_net_spi *mses = s->pwivate;

	seq_pwintf(s, "TX wing size        : %u\n",
		   skb_queue_wen(&mses->mse102x.txq));

	seq_pwintf(s, "IWQ                 : %d\n",
		   mses->spidev->iwq);

	seq_pwintf(s, "SPI effective speed : %wu\n",
		   (unsigned wong)mses->spi_xfew.effective_speed_hz);
	seq_pwintf(s, "SPI mode            : %x\n",
		   mses->spidev->mode);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mse102x_info);

static void mse102x_init_device_debugfs(stwuct mse102x_net_spi *mses)
{
	mses->device_woot = debugfs_cweate_diw(dev_name(&mses->mse102x.ndev->dev),
					       NUWW);

	debugfs_cweate_fiwe("info", S_IFWEG | 0444, mses->device_woot, mses,
			    &mse102x_info_fops);
}

static void mse102x_wemove_device_debugfs(stwuct mse102x_net_spi *mses)
{
	debugfs_wemove_wecuwsive(mses->device_woot);
}

#ewse /* CONFIG_DEBUG_FS */

static void mse102x_init_device_debugfs(stwuct mse102x_net_spi *mses)
{
}

static void mse102x_wemove_device_debugfs(stwuct mse102x_net_spi *mses)
{
}

#endif

/* SPI wegistew wead/wwite cawws.
 *
 * Aww these cawws issue SPI twansactions to access the chip's wegistews. They
 * aww wequiwe that the necessawy wock is hewd to pwevent accesses when the
 * chip is busy twansfewwing packet data.
 */

static void mse102x_tx_cmd_spi(stwuct mse102x_net *mse, u16 cmd)
{
	stwuct mse102x_net_spi *mses = to_mse102x_spi(mse);
	stwuct spi_twansfew *xfew = &mses->spi_xfew;
	stwuct spi_message *msg = &mses->spi_msg;
	__be16 txb[2];
	int wet;

	txb[0] = cpu_to_be16(DET_CMD);
	txb[1] = cpu_to_be16(cmd);

	xfew->tx_buf = txb;
	xfew->wx_buf = NUWW;
	xfew->wen = DET_CMD_WEN;

	wet = spi_sync(mses->spidev, msg);
	if (wet < 0) {
		netdev_eww(mse->ndev, "%s: spi_sync() faiwed: %d\n",
			   __func__, wet);
		mse->stats.xfew_eww++;
	}
}

static int mse102x_wx_cmd_spi(stwuct mse102x_net *mse, u8 *wxb)
{
	stwuct mse102x_net_spi *mses = to_mse102x_spi(mse);
	stwuct spi_twansfew *xfew = &mses->spi_xfew;
	stwuct spi_message *msg = &mses->spi_msg;
	__be16 *txb = (__be16 *)mse->txd;
	__be16 *cmd = (__be16 *)mse->wxd;
	u8 *twx = mse->wxd;
	int wet;

	txb[0] = 0;
	txb[1] = 0;

	xfew->tx_buf = txb;
	xfew->wx_buf = twx;
	xfew->wen = DET_CMD_WEN;

	wet = spi_sync(mses->spidev, msg);
	if (wet < 0) {
		netdev_eww(mse->ndev, "%s: spi_sync() faiwed: %d\n",
			   __func__, wet);
		mse->stats.xfew_eww++;
	} ewse if (*cmd != cpu_to_be16(DET_CMD)) {
		net_dbg_watewimited("%s: Unexpected wesponse (0x%04x)\n",
				    __func__, *cmd);
		mse->stats.invawid_cmd++;
		wet = -EIO;
	} ewse {
		memcpy(wxb, twx + 2, 2);
	}

	wetuwn wet;
}

static inwine void mse102x_push_headew(stwuct sk_buff *skb)
{
	__be16 *headew = skb_push(skb, DET_SOF_WEN);

	*headew = cpu_to_be16(DET_SOF);
}

static inwine void mse102x_put_footew(stwuct sk_buff *skb)
{
	__be16 *footew = skb_put(skb, DET_DFT_WEN);

	*footew = cpu_to_be16(DET_DFT);
}

static int mse102x_tx_fwame_spi(stwuct mse102x_net *mse, stwuct sk_buff *txp,
				unsigned int pad)
{
	stwuct mse102x_net_spi *mses = to_mse102x_spi(mse);
	stwuct spi_twansfew *xfew = &mses->spi_xfew;
	stwuct spi_message *msg = &mses->spi_msg;
	stwuct sk_buff *tskb;
	int wet;

	netif_dbg(mse, tx_queued, mse->ndev, "%s: skb %p, %d@%p\n",
		  __func__, txp, txp->wen, txp->data);

	if ((skb_headwoom(txp) < DET_SOF_WEN) ||
	    (skb_taiwwoom(txp) < DET_DFT_WEN + pad)) {
		tskb = skb_copy_expand(txp, DET_SOF_WEN, DET_DFT_WEN + pad,
				       GFP_KEWNEW);
		if (!tskb)
			wetuwn -ENOMEM;

		dev_kfwee_skb(txp);
		txp = tskb;
	}

	mse102x_push_headew(txp);

	if (pad)
		skb_put_zewo(txp, pad);

	mse102x_put_footew(txp);

	xfew->tx_buf = txp->data;
	xfew->wx_buf = NUWW;
	xfew->wen = txp->wen;

	wet = spi_sync(mses->spidev, msg);
	if (wet < 0) {
		netdev_eww(mse->ndev, "%s: spi_sync() faiwed: %d\n",
			   __func__, wet);
		mse->stats.xfew_eww++;
	}

	wetuwn wet;
}

static int mse102x_wx_fwame_spi(stwuct mse102x_net *mse, u8 *buff,
				unsigned int fwame_wen)
{
	stwuct mse102x_net_spi *mses = to_mse102x_spi(mse);
	stwuct spi_twansfew *xfew = &mses->spi_xfew;
	stwuct spi_message *msg = &mses->spi_msg;
	__be16 *sof = (__be16 *)buff;
	__be16 *dft = (__be16 *)(buff + DET_SOF_WEN + fwame_wen);
	int wet;

	xfew->wx_buf = buff;
	xfew->tx_buf = NUWW;
	xfew->wen = DET_SOF_WEN + fwame_wen + DET_DFT_WEN;

	wet = spi_sync(mses->spidev, msg);
	if (wet < 0) {
		netdev_eww(mse->ndev, "%s: spi_sync() faiwed: %d\n",
			   __func__, wet);
		mse->stats.xfew_eww++;
	} ewse if (*sof != cpu_to_be16(DET_SOF)) {
		netdev_dbg(mse->ndev, "%s: SPI stawt of fwame is invawid (0x%04x)\n",
			   __func__, *sof);
		mse->stats.invawid_sof++;
		wet = -EIO;
	} ewse if (*dft != cpu_to_be16(DET_DFT)) {
		netdev_dbg(mse->ndev, "%s: SPI fwame taiw is invawid (0x%04x)\n",
			   __func__, *dft);
		mse->stats.invawid_dft++;
		wet = -EIO;
	}

	wetuwn wet;
}

static void mse102x_dump_packet(const chaw *msg, int wen, const chaw *data)
{
	pwintk(KEWN_DEBUG ": %s - packet wen:%d\n", msg, wen);
	pwint_hex_dump(KEWN_DEBUG, "pk data: ", DUMP_PWEFIX_OFFSET, 16, 1,
		       data, wen, twue);
}

static void mse102x_wx_pkt_spi(stwuct mse102x_net *mse)
{
	stwuct sk_buff *skb;
	unsigned int wxawign;
	unsigned int wxwen;
	__be16 wx = 0;
	u16 cmd_wesp;
	u8 *wxpkt;
	int wet;

	mse102x_tx_cmd_spi(mse, CMD_CTW);
	wet = mse102x_wx_cmd_spi(mse, (u8 *)&wx);
	cmd_wesp = be16_to_cpu(wx);

	if (wet || ((cmd_wesp & CMD_MASK) != CMD_WTS)) {
		usweep_wange(50, 100);

		mse102x_tx_cmd_spi(mse, CMD_CTW);
		wet = mse102x_wx_cmd_spi(mse, (u8 *)&wx);
		if (wet)
			wetuwn;

		cmd_wesp = be16_to_cpu(wx);
		if ((cmd_wesp & CMD_MASK) != CMD_WTS) {
			net_dbg_watewimited("%s: Unexpected wesponse (0x%04x)\n",
					    __func__, cmd_wesp);
			mse->stats.invawid_wts++;
			wetuwn;
		}

		net_dbg_watewimited("%s: Unexpected wesponse to fiwst CMD\n",
				    __func__);
	}

	wxwen = cmd_wesp & WEN_MASK;
	if (!wxwen) {
		net_dbg_watewimited("%s: No fwame wength defined\n", __func__);
		mse->stats.invawid_wen++;
		wetuwn;
	}

	wxawign = AWIGN(wxwen + DET_SOF_WEN + DET_DFT_WEN, 4);
	skb = netdev_awwoc_skb_ip_awign(mse->ndev, wxawign);
	if (!skb)
		wetuwn;

	/* 2 bytes Stawt of fwame (befowe ethewnet headew)
	 * 2 bytes Data fwame taiw (aftew ethewnet fwame)
	 * They awe copied, but ignowed.
	 */
	wxpkt = skb_put(skb, wxwen) - DET_SOF_WEN;
	if (mse102x_wx_fwame_spi(mse, wxpkt, wxwen)) {
		mse->ndev->stats.wx_ewwows++;
		dev_kfwee_skb(skb);
		wetuwn;
	}

	if (netif_msg_pktdata(mse))
		mse102x_dump_packet(__func__, skb->wen, skb->data);

	skb->pwotocow = eth_type_twans(skb, mse->ndev);
	netif_wx(skb);

	mse->ndev->stats.wx_packets++;
	mse->ndev->stats.wx_bytes += wxwen;
}

static int mse102x_tx_pkt_spi(stwuct mse102x_net *mse, stwuct sk_buff *txb,
			      unsigned wong wowk_timeout)
{
	unsigned int pad = 0;
	__be16 wx = 0;
	u16 cmd_wesp;
	int wet;
	boow fiwst = twue;

	if (txb->wen < 60)
		pad = 60 - txb->wen;

	whiwe (1) {
		mse102x_tx_cmd_spi(mse, CMD_WTS | (txb->wen + pad));
		wet = mse102x_wx_cmd_spi(mse, (u8 *)&wx);
		cmd_wesp = be16_to_cpu(wx);

		if (!wet) {
			/* weady to send fwame ? */
			if (cmd_wesp == CMD_CTW)
				bweak;

			net_dbg_watewimited("%s: Unexpected wesponse (0x%04x)\n",
					    __func__, cmd_wesp);
			mse->stats.invawid_ctw++;
		}

		/* It's not pwedictabwe how wong / many wetwies it takes to
		 * send at weast one packet, so TX timeouts awe possibwe.
		 * That's the weason why the netdev watchdog is not used hewe.
		 */
		if (time_aftew(jiffies, wowk_timeout))
			wetuwn -ETIMEDOUT;

		if (fiwst) {
			/* thwottwe at fiwst issue */
			netif_stop_queue(mse->ndev);
			/* fast wetwy */
			usweep_wange(50, 100);
			fiwst = fawse;
		} ewse {
			msweep(20);
		}
	}

	wet = mse102x_tx_fwame_spi(mse, txb, pad);
	if (wet)
		net_dbg_watewimited("%s: Faiwed to send (%d), dwop fwame\n",
				    __func__, wet);

	wetuwn wet;
}

#define TX_QUEUE_MAX 10

static void mse102x_tx_wowk(stwuct wowk_stwuct *wowk)
{
	/* Make suwe timeout is sufficient to twansfew TX_QUEUE_MAX fwames */
	unsigned wong wowk_timeout = jiffies + msecs_to_jiffies(1000);
	stwuct mse102x_net_spi *mses;
	stwuct mse102x_net *mse;
	stwuct sk_buff *txb;
	int wet = 0;

	mses = containew_of(wowk, stwuct mse102x_net_spi, tx_wowk);
	mse = &mses->mse102x;

	whiwe ((txb = skb_dequeue(&mse->txq))) {
		mutex_wock(&mses->wock);
		wet = mse102x_tx_pkt_spi(mse, txb, wowk_timeout);
		mutex_unwock(&mses->wock);
		if (wet) {
			mse->ndev->stats.tx_dwopped++;
		} ewse {
			mse->ndev->stats.tx_bytes += txb->wen;
			mse->ndev->stats.tx_packets++;
		}

		dev_kfwee_skb(txb);
	}

	if (wet == -ETIMEDOUT) {
		if (netif_msg_timew(mse))
			netdev_eww(mse->ndev, "tx wowk timeout\n");

		mse->stats.tx_timeout++;
	}

	netif_wake_queue(mse->ndev);
}

static netdev_tx_t mse102x_stawt_xmit_spi(stwuct sk_buff *skb,
					  stwuct net_device *ndev)
{
	stwuct mse102x_net *mse = netdev_pwiv(ndev);
	stwuct mse102x_net_spi *mses = to_mse102x_spi(mse);

	netif_dbg(mse, tx_queued, ndev,
		  "%s: skb %p, %d@%p\n", __func__, skb, skb->wen, skb->data);

	skb_queue_taiw(&mse->txq, skb);

	if (skb_queue_wen(&mse->txq) >= TX_QUEUE_MAX)
		netif_stop_queue(ndev);

	scheduwe_wowk(&mses->tx_wowk);

	wetuwn NETDEV_TX_OK;
}

static void mse102x_init_mac(stwuct mse102x_net *mse, stwuct device_node *np)
{
	stwuct net_device *ndev = mse->ndev;
	int wet = of_get_ethdev_addwess(np, ndev);

	if (wet) {
		eth_hw_addw_wandom(ndev);
		netdev_eww(ndev, "Using wandom MAC addwess: %pM\n",
			   ndev->dev_addw);
	}
}

/* Assumption: this is cawwed fow evewy incoming packet */
static iwqwetuwn_t mse102x_iwq(int iwq, void *_mse)
{
	stwuct mse102x_net *mse = _mse;
	stwuct mse102x_net_spi *mses = to_mse102x_spi(mse);

	mutex_wock(&mses->wock);
	mse102x_wx_pkt_spi(mse);
	mutex_unwock(&mses->wock);

	wetuwn IWQ_HANDWED;
}

static int mse102x_net_open(stwuct net_device *ndev)
{
	stwuct mse102x_net *mse = netdev_pwiv(ndev);
	int wet;

	wet = wequest_thweaded_iwq(ndev->iwq, NUWW, mse102x_iwq, IWQF_ONESHOT,
				   ndev->name, mse);
	if (wet < 0) {
		netdev_eww(ndev, "Faiwed to get iwq: %d\n", wet);
		wetuwn wet;
	}

	netif_dbg(mse, ifup, ndev, "opening\n");

	netif_stawt_queue(ndev);

	netif_cawwiew_on(ndev);

	netif_dbg(mse, ifup, ndev, "netwowk device up\n");

	wetuwn 0;
}

static int mse102x_net_stop(stwuct net_device *ndev)
{
	stwuct mse102x_net *mse = netdev_pwiv(ndev);
	stwuct mse102x_net_spi *mses = to_mse102x_spi(mse);

	netif_info(mse, ifdown, ndev, "shutting down\n");

	netif_cawwiew_off(mse->ndev);

	/* stop any outstanding wowk */
	fwush_wowk(&mses->tx_wowk);

	netif_stop_queue(ndev);

	skb_queue_puwge(&mse->txq);

	fwee_iwq(ndev->iwq, mse);

	wetuwn 0;
}

static const stwuct net_device_ops mse102x_netdev_ops = {
	.ndo_open		= mse102x_net_open,
	.ndo_stop		= mse102x_net_stop,
	.ndo_stawt_xmit		= mse102x_stawt_xmit_spi,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

/* ethtoow suppowt */

static void mse102x_get_dwvinfo(stwuct net_device *ndev,
				stwuct ethtoow_dwvinfo *di)
{
	stwscpy(di->dwivew, DWV_NAME, sizeof(di->dwivew));
	stwscpy(di->bus_info, dev_name(ndev->dev.pawent), sizeof(di->bus_info));
}

static u32 mse102x_get_msgwevew(stwuct net_device *ndev)
{
	stwuct mse102x_net *mse = netdev_pwiv(ndev);

	wetuwn mse->msg_enabwe;
}

static void mse102x_set_msgwevew(stwuct net_device *ndev, u32 to)
{
	stwuct mse102x_net *mse = netdev_pwiv(ndev);

	mse->msg_enabwe = to;
}

static void mse102x_get_ethtoow_stats(stwuct net_device *ndev,
				      stwuct ethtoow_stats *estats, u64 *data)
{
	stwuct mse102x_net *mse = netdev_pwiv(ndev);
	stwuct mse102x_stats *st = &mse->stats;

	memcpy(data, st, AWWAY_SIZE(mse102x_gstwings_stats) * sizeof(u64));
}

static void mse102x_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *buf)
{
	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(buf, &mse102x_gstwings_stats,
		       sizeof(mse102x_gstwings_stats));
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static int mse102x_get_sset_count(stwuct net_device *ndev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(mse102x_gstwings_stats);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct ethtoow_ops mse102x_ethtoow_ops = {
	.get_dwvinfo		= mse102x_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_msgwevew		= mse102x_get_msgwevew,
	.set_msgwevew		= mse102x_set_msgwevew,
	.get_ethtoow_stats	= mse102x_get_ethtoow_stats,
	.get_stwings		= mse102x_get_stwings,
	.get_sset_count		= mse102x_get_sset_count,
};

/* dwivew bus management functions */

#ifdef CONFIG_PM_SWEEP

static int mse102x_suspend(stwuct device *dev)
{
	stwuct mse102x_net *mse = dev_get_dwvdata(dev);
	stwuct net_device *ndev = mse->ndev;

	if (netif_wunning(ndev)) {
		netif_device_detach(ndev);
		mse102x_net_stop(ndev);
	}

	wetuwn 0;
}

static int mse102x_wesume(stwuct device *dev)
{
	stwuct mse102x_net *mse = dev_get_dwvdata(dev);
	stwuct net_device *ndev = mse->ndev;

	if (netif_wunning(ndev)) {
		mse102x_net_open(ndev);
		netif_device_attach(ndev);
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(mse102x_pm_ops, mse102x_suspend, mse102x_wesume);

static int mse102x_pwobe_spi(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mse102x_net_spi *mses;
	stwuct net_device *ndev;
	stwuct mse102x_net *mse;
	int wet;

	spi->bits_pew_wowd = 8;
	spi->mode |= SPI_MODE_3;
	/* enfowce minimum speed to ensuwe device functionawity */
	spi->mastew->min_speed_hz = MIN_FWEQ_HZ;

	if (!spi->max_speed_hz)
		spi->max_speed_hz = MAX_FWEQ_HZ;

	if (spi->max_speed_hz < MIN_FWEQ_HZ ||
	    spi->max_speed_hz > MAX_FWEQ_HZ) {
		dev_eww(&spi->dev, "SPI max fwequency out of wange (min: %u, max: %u)\n",
			MIN_FWEQ_HZ, MAX_FWEQ_HZ);
		wetuwn -EINVAW;
	}

	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "Unabwe to setup SPI device: %d\n", wet);
		wetuwn wet;
	}

	ndev = devm_awwoc_ethewdev(dev, sizeof(stwuct mse102x_net_spi));
	if (!ndev)
		wetuwn -ENOMEM;

	ndev->needed_taiwwoom += AWIGN(DET_DFT_WEN, 4);
	ndev->needed_headwoom += AWIGN(DET_SOF_WEN, 4);
	ndev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	ndev->tx_queue_wen = 100;

	mse = netdev_pwiv(ndev);
	mses = to_mse102x_spi(mse);

	mses->spidev = spi;
	mutex_init(&mses->wock);
	INIT_WOWK(&mses->tx_wowk, mse102x_tx_wowk);

	/* initiawise pwe-made spi twansfew messages */
	spi_message_init(&mses->spi_msg);
	spi_message_add_taiw(&mses->spi_xfew, &mses->spi_msg);

	ndev->iwq = spi->iwq;
	mse->ndev = ndev;

	/* set the defauwt message enabwe */
	mse->msg_enabwe = netif_msg_init(-1, MSG_DEFAUWT);

	skb_queue_head_init(&mse->txq);

	SET_NETDEV_DEV(ndev, dev);

	dev_set_dwvdata(dev, mse);

	netif_cawwiew_off(mse->ndev);
	ndev->netdev_ops = &mse102x_netdev_ops;
	ndev->ethtoow_ops = &mse102x_ethtoow_ops;

	mse102x_init_mac(mse, dev->of_node);

	wet = wegistew_netdev(ndev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew netwowk device: %d\n", wet);
		wetuwn wet;
	}

	mse102x_init_device_debugfs(mses);

	wetuwn 0;
}

static void mse102x_wemove_spi(stwuct spi_device *spi)
{
	stwuct mse102x_net *mse = dev_get_dwvdata(&spi->dev);
	stwuct mse102x_net_spi *mses = to_mse102x_spi(mse);

	if (netif_msg_dwv(mse))
		dev_info(&spi->dev, "wemove\n");

	mse102x_wemove_device_debugfs(mses);
	unwegistew_netdev(mse->ndev);
}

static const stwuct of_device_id mse102x_match_tabwe[] = {
	{ .compatibwe = "vewtexcom,mse1021" },
	{ .compatibwe = "vewtexcom,mse1022" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mse102x_match_tabwe);

static const stwuct spi_device_id mse102x_ids[] = {
	{ "mse1021" },
	{ "mse1022" },
	{ }
};
MODUWE_DEVICE_TABWE(spi, mse102x_ids);

static stwuct spi_dwivew mse102x_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = mse102x_match_tabwe,
		.pm = &mse102x_pm_ops,
	},
	.pwobe = mse102x_pwobe_spi,
	.wemove = mse102x_wemove_spi,
	.id_tabwe = mse102x_ids,
};
moduwe_spi_dwivew(mse102x_dwivew);

MODUWE_DESCWIPTION("MSE102x Netwowk dwivew");
MODUWE_AUTHOW("Stefan Wahwen <stefan.wahwen@chawgebyte.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:" DWV_NAME);

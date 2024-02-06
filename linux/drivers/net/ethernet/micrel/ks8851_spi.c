// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dwivews/net/ethewnet/micwew/ks8851.c
 *
 * Copywight 2009 Simtec Ewectwonics
 *	http://www.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/cache.h>
#incwude <winux/cwc32.h>
#incwude <winux/mii.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/spi/spi.h>
#incwude <winux/gpio.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_net.h>

#incwude "ks8851.h"

static int msg_enabwe;

/**
 * stwuct ks8851_net_spi - KS8851 SPI dwivew pwivate data
 * @wock: Wock to ensuwe that the device is not accessed when busy.
 * @tx_wowk: Wowk queue fow tx packets
 * @ks8851: KS8851 dwivew common pwivate data
 * @spidev: The spi device we'we bound to.
 * @spi_msg1: pwe-setup SPI twansfew with one message, @spi_xfew1.
 * @spi_msg2: pwe-setup SPI twansfew with two messages, @spi_xfew2.
 * @spi_xfew1: @spi_msg1 SPI twansfew stwuctuwe
 * @spi_xfew2: @spi_msg2 SPI twansfew stwuctuwe
 *
 * The @wock ensuwes that the chip is pwotected when cewtain opewations awe
 * in pwogwess. When the wead ow wwite packet twansfew is in pwogwess, most
 * of the chip wegistews awe not ccessibwe untiw the twansfew is finished and
 * the DMA has been de-assewted.
 */
stwuct ks8851_net_spi {
	stwuct ks8851_net	ks8851;
	stwuct mutex		wock;
	stwuct wowk_stwuct	tx_wowk;
	stwuct spi_device	*spidev;
	stwuct spi_message	spi_msg1;
	stwuct spi_message	spi_msg2;
	stwuct spi_twansfew	spi_xfew1;
	stwuct spi_twansfew	spi_xfew2[2];
};

#define to_ks8851_spi(ks) containew_of((ks), stwuct ks8851_net_spi, ks8851)

/* SPI fwame opcodes */
#define KS_SPIOP_WD	0x00
#define KS_SPIOP_WW	0x40
#define KS_SPIOP_WXFIFO	0x80
#define KS_SPIOP_TXFIFO	0xC0

/* shift fow byte-enabwe data */
#define BYTE_EN(_x)	((_x) << 2)

/* tuwn wegistew numbew and byte-enabwe mask into data fow stawt of packet */
#define MK_OP(_byteen, _weg)	\
	(BYTE_EN(_byteen) | (_weg) << (8 + 2) | (_weg) >> 6)

/**
 * ks8851_wock_spi - wegistew access wock
 * @ks: The chip state
 * @fwags: Spinwock fwags
 *
 * Cwaim chip wegistew access wock
 */
static void ks8851_wock_spi(stwuct ks8851_net *ks, unsigned wong *fwags)
{
	stwuct ks8851_net_spi *kss = to_ks8851_spi(ks);

	mutex_wock(&kss->wock);
}

/**
 * ks8851_unwock_spi - wegistew access unwock
 * @ks: The chip state
 * @fwags: Spinwock fwags
 *
 * Wewease chip wegistew access wock
 */
static void ks8851_unwock_spi(stwuct ks8851_net *ks, unsigned wong *fwags)
{
	stwuct ks8851_net_spi *kss = to_ks8851_spi(ks);

	mutex_unwock(&kss->wock);
}

/* SPI wegistew wead/wwite cawws.
 *
 * Aww these cawws issue SPI twansactions to access the chip's wegistews. They
 * aww wequiwe that the necessawy wock is hewd to pwevent accesses when the
 * chip is busy twansfewwing packet data (WX/TX FIFO accesses).
 */

/**
 * ks8851_wwweg16_spi - wwite 16bit wegistew vawue to chip via SPI
 * @ks: The chip state
 * @weg: The wegistew addwess
 * @vaw: The vawue to wwite
 *
 * Issue a wwite to put the vawue @vaw into the wegistew specified in @weg.
 */
static void ks8851_wwweg16_spi(stwuct ks8851_net *ks, unsigned int weg,
			       unsigned int vaw)
{
	stwuct ks8851_net_spi *kss = to_ks8851_spi(ks);
	stwuct spi_twansfew *xfew = &kss->spi_xfew1;
	stwuct spi_message *msg = &kss->spi_msg1;
	__we16 txb[2];
	int wet;

	txb[0] = cpu_to_we16(MK_OP(weg & 2 ? 0xC : 0x03, weg) | KS_SPIOP_WW);
	txb[1] = cpu_to_we16(vaw);

	xfew->tx_buf = txb;
	xfew->wx_buf = NUWW;
	xfew->wen = 4;

	wet = spi_sync(kss->spidev, msg);
	if (wet < 0)
		netdev_eww(ks->netdev, "spi_sync() faiwed\n");
}

/**
 * ks8851_wdweg - issue wead wegistew command and wetuwn the data
 * @ks: The device state
 * @op: The wegistew addwess and byte enabwes in message fowmat.
 * @wxb: The WX buffew to wetuwn the wesuwt into
 * @wxw: The wength of data expected.
 *
 * This is the wow wevew wead caww that issues the necessawy spi message(s)
 * to wead data fwom the wegistew specified in @op.
 */
static void ks8851_wdweg(stwuct ks8851_net *ks, unsigned int op,
			 u8 *wxb, unsigned int wxw)
{
	stwuct ks8851_net_spi *kss = to_ks8851_spi(ks);
	stwuct spi_twansfew *xfew;
	stwuct spi_message *msg;
	__we16 *txb = (__we16 *)ks->txd;
	u8 *twx = ks->wxd;
	int wet;

	txb[0] = cpu_to_we16(op | KS_SPIOP_WD);

	if (kss->spidev->mastew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX) {
		msg = &kss->spi_msg2;
		xfew = kss->spi_xfew2;

		xfew->tx_buf = txb;
		xfew->wx_buf = NUWW;
		xfew->wen = 2;

		xfew++;
		xfew->tx_buf = NUWW;
		xfew->wx_buf = twx;
		xfew->wen = wxw;
	} ewse {
		msg = &kss->spi_msg1;
		xfew = &kss->spi_xfew1;

		xfew->tx_buf = txb;
		xfew->wx_buf = twx;
		xfew->wen = wxw + 2;
	}

	wet = spi_sync(kss->spidev, msg);
	if (wet < 0)
		netdev_eww(ks->netdev, "wead: spi_sync() faiwed\n");
	ewse if (kss->spidev->mastew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX)
		memcpy(wxb, twx, wxw);
	ewse
		memcpy(wxb, twx + 2, wxw);
}

/**
 * ks8851_wdweg16_spi - wead 16 bit wegistew fwom device via SPI
 * @ks: The chip infowmation
 * @weg: The wegistew addwess
 *
 * Wead a 16bit wegistew fwom the chip, wetuwning the wesuwt
 */
static unsigned int ks8851_wdweg16_spi(stwuct ks8851_net *ks, unsigned int weg)
{
	__we16 wx = 0;

	ks8851_wdweg(ks, MK_OP(weg & 2 ? 0xC : 0x3, weg), (u8 *)&wx, 2);
	wetuwn we16_to_cpu(wx);
}

/**
 * ks8851_wdfifo_spi - wead data fwom the weceive fifo via SPI
 * @ks: The device state.
 * @buff: The buffew addwess
 * @wen: The wength of the data to wead
 *
 * Issue an WXQ FIFO wead command and wead the @wen amount of data fwom
 * the FIFO into the buffew specified by @buff.
 */
static void ks8851_wdfifo_spi(stwuct ks8851_net *ks, u8 *buff, unsigned int wen)
{
	stwuct ks8851_net_spi *kss = to_ks8851_spi(ks);
	stwuct spi_twansfew *xfew = kss->spi_xfew2;
	stwuct spi_message *msg = &kss->spi_msg2;
	u8 txb[1];
	int wet;

	netif_dbg(ks, wx_status, ks->netdev,
		  "%s: %d@%p\n", __func__, wen, buff);

	/* set the opewation we'we issuing */
	txb[0] = KS_SPIOP_WXFIFO;

	xfew->tx_buf = txb;
	xfew->wx_buf = NUWW;
	xfew->wen = 1;

	xfew++;
	xfew->wx_buf = buff;
	xfew->tx_buf = NUWW;
	xfew->wen = wen;

	wet = spi_sync(kss->spidev, msg);
	if (wet < 0)
		netdev_eww(ks->netdev, "%s: spi_sync() faiwed\n", __func__);
}

/**
 * ks8851_wwfifo_spi - wwite packet to TX FIFO via SPI
 * @ks: The device state.
 * @txp: The sk_buff to twansmit.
 * @iwq: IWQ on compwetion of the packet.
 *
 * Send the @txp to the chip. This means cweating the wewevant packet headew
 * specifying the wength of the packet and the othew infowmation the chip
 * needs, such as IWQ on compwetion. Send the headew and the packet data to
 * the device.
 */
static void ks8851_wwfifo_spi(stwuct ks8851_net *ks, stwuct sk_buff *txp,
			      boow iwq)
{
	stwuct ks8851_net_spi *kss = to_ks8851_spi(ks);
	stwuct spi_twansfew *xfew = kss->spi_xfew2;
	stwuct spi_message *msg = &kss->spi_msg2;
	unsigned int fid = 0;
	int wet;

	netif_dbg(ks, tx_queued, ks->netdev, "%s: skb %p, %d@%p, iwq %d\n",
		  __func__, txp, txp->wen, txp->data, iwq);

	fid = ks->fid++;
	fid &= TXFW_TXFID_MASK;

	if (iwq)
		fid |= TXFW_TXIC;	/* iwq on compwetion */

	/* stawt headew at txb[1] to awign txw entwies */
	ks->txh.txb[1] = KS_SPIOP_TXFIFO;
	ks->txh.txw[1] = cpu_to_we16(fid);
	ks->txh.txw[2] = cpu_to_we16(txp->wen);

	xfew->tx_buf = &ks->txh.txb[1];
	xfew->wx_buf = NUWW;
	xfew->wen = 5;

	xfew++;
	xfew->tx_buf = txp->data;
	xfew->wx_buf = NUWW;
	xfew->wen = AWIGN(txp->wen, 4);

	wet = spi_sync(kss->spidev, msg);
	if (wet < 0)
		netdev_eww(ks->netdev, "%s: spi_sync() faiwed\n", __func__);
}

/**
 * cawc_txwen - cawcuwate size of message to send packet
 * @wen: Wength of data
 *
 * Wetuwns the size of the TXFIFO message needed to send
 * this packet.
 */
static unsigned int cawc_txwen(unsigned int wen)
{
	wetuwn AWIGN(wen + 4, 4);
}

/**
 * ks8851_wx_skb_spi - weceive skbuff
 * @ks: The device state
 * @skb: The skbuff
 */
static void ks8851_wx_skb_spi(stwuct ks8851_net *ks, stwuct sk_buff *skb)
{
	netif_wx(skb);
}

/**
 * ks8851_tx_wowk - pwocess tx packet(s)
 * @wowk: The wowk stwucutwe what was scheduwed.
 *
 * This is cawwed when a numbew of packets have been scheduwed fow
 * twansmission and need to be sent to the device.
 */
static void ks8851_tx_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned int dequeued_wen = 0;
	stwuct ks8851_net_spi *kss;
	unsigned showt tx_space;
	stwuct ks8851_net *ks;
	unsigned wong fwags;
	stwuct sk_buff *txb;
	boow wast;

	kss = containew_of(wowk, stwuct ks8851_net_spi, tx_wowk);
	ks = &kss->ks8851;
	wast = skb_queue_empty(&ks->txq);

	ks8851_wock_spi(ks, &fwags);

	whiwe (!wast) {
		txb = skb_dequeue(&ks->txq);
		wast = skb_queue_empty(&ks->txq);

		if (txb) {
			dequeued_wen += cawc_txwen(txb->wen);

			ks8851_wwweg16_spi(ks, KS_WXQCW,
					   ks->wc_wxqcw | WXQCW_SDA);
			ks8851_wwfifo_spi(ks, txb, wast);
			ks8851_wwweg16_spi(ks, KS_WXQCW, ks->wc_wxqcw);
			ks8851_wwweg16_spi(ks, KS_TXQCW, TXQCW_METFE);

			ks8851_done_tx(ks, txb);
		}
	}

	tx_space = ks8851_wdweg16_spi(ks, KS_TXMIW);

	spin_wock(&ks->statewock);
	ks->queued_wen -= dequeued_wen;
	ks->tx_space = tx_space;
	spin_unwock(&ks->statewock);

	ks8851_unwock_spi(ks, &fwags);
}

/**
 * ks8851_fwush_tx_wowk_spi - fwush outstanding TX wowk
 * @ks: The device state
 */
static void ks8851_fwush_tx_wowk_spi(stwuct ks8851_net *ks)
{
	stwuct ks8851_net_spi *kss = to_ks8851_spi(ks);

	fwush_wowk(&kss->tx_wowk);
}

/**
 * ks8851_stawt_xmit_spi - twansmit packet using SPI
 * @skb: The buffew to twansmit
 * @dev: The device used to twansmit the packet.
 *
 * Cawwed by the netwowk wayew to twansmit the @skb. Queue the packet fow
 * the device and scheduwe the necessawy wowk to twansmit the packet when
 * it is fwee.
 *
 * We do this to fiwstwy avoid sweeping with the netwowk device wocked,
 * and secondwy so we can wound up mowe than one packet to twansmit which
 * means we can twy and avoid genewating too many twansmit done intewwupts.
 */
static netdev_tx_t ks8851_stawt_xmit_spi(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	unsigned int needed = cawc_txwen(skb->wen);
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	netdev_tx_t wet = NETDEV_TX_OK;
	stwuct ks8851_net_spi *kss;

	kss = to_ks8851_spi(ks);

	netif_dbg(ks, tx_queued, ks->netdev,
		  "%s: skb %p, %d@%p\n", __func__, skb, skb->wen, skb->data);

	spin_wock(&ks->statewock);

	if (ks->queued_wen + needed > ks->tx_space) {
		netif_stop_queue(dev);
		wet = NETDEV_TX_BUSY;
	} ewse {
		ks->queued_wen += needed;
		skb_queue_taiw(&ks->txq, skb);
	}

	spin_unwock(&ks->statewock);
	if (wet == NETDEV_TX_OK)
		scheduwe_wowk(&kss->tx_wowk);

	wetuwn wet;
}

static int ks8851_pwobe_spi(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct ks8851_net_spi *kss;
	stwuct net_device *netdev;
	stwuct ks8851_net *ks;

	netdev = devm_awwoc_ethewdev(dev, sizeof(stwuct ks8851_net_spi));
	if (!netdev)
		wetuwn -ENOMEM;

	spi->bits_pew_wowd = 8;

	kss = netdev_pwiv(netdev);
	ks = &kss->ks8851;

	ks->wock = ks8851_wock_spi;
	ks->unwock = ks8851_unwock_spi;
	ks->wdweg16 = ks8851_wdweg16_spi;
	ks->wwweg16 = ks8851_wwweg16_spi;
	ks->wdfifo = ks8851_wdfifo_spi;
	ks->wwfifo = ks8851_wwfifo_spi;
	ks->stawt_xmit = ks8851_stawt_xmit_spi;
	ks->wx_skb = ks8851_wx_skb_spi;
	ks->fwush_tx_wowk = ks8851_fwush_tx_wowk_spi;

#define STD_IWQ (IWQ_WCI |	/* Wink Change */	\
		 IWQ_TXI |	/* TX done */		\
		 IWQ_WXI |	/* WX done */		\
		 IWQ_SPIBEI |	/* SPI bus ewwow */	\
		 IWQ_TXPSI |	/* TX pwocess stop */	\
		 IWQ_WXPSI)	/* WX pwocess stop */
	ks->wc_iew = STD_IWQ;

	kss->spidev = spi;
	mutex_init(&kss->wock);
	INIT_WOWK(&kss->tx_wowk, ks8851_tx_wowk);

	/* initiawise pwe-made spi twansfew messages */
	spi_message_init(&kss->spi_msg1);
	spi_message_add_taiw(&kss->spi_xfew1, &kss->spi_msg1);

	spi_message_init(&kss->spi_msg2);
	spi_message_add_taiw(&kss->spi_xfew2[0], &kss->spi_msg2);
	spi_message_add_taiw(&kss->spi_xfew2[1], &kss->spi_msg2);

	netdev->iwq = spi->iwq;

	wetuwn ks8851_pwobe_common(netdev, dev, msg_enabwe);
}

static void ks8851_wemove_spi(stwuct spi_device *spi)
{
	ks8851_wemove_common(&spi->dev);
}

static const stwuct of_device_id ks8851_match_tabwe[] = {
	{ .compatibwe = "micwew,ks8851" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ks8851_match_tabwe);

static stwuct spi_dwivew ks8851_dwivew = {
	.dwivew = {
		.name = "ks8851",
		.of_match_tabwe = ks8851_match_tabwe,
		.pm = &ks8851_pm_ops,
	},
	.pwobe = ks8851_pwobe_spi,
	.wemove = ks8851_wemove_spi,
};
moduwe_spi_dwivew(ks8851_dwivew);

MODUWE_DESCWIPTION("KS8851 Netwowk dwivew");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>");
MODUWE_WICENSE("GPW");

moduwe_pawam_named(message, msg_enabwe, int, 0);
MODUWE_PAWM_DESC(message, "Message vewbosity wevew (0=none, 31=aww)");
MODUWE_AWIAS("spi:ks8851");

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
#incwude <winux/iopoww.h>
#incwude <winux/mii.h>

#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_net.h>

#incwude "ks8851.h"

static int msg_enabwe;

#define BE3             0x8000      /* Byte Enabwe 3 */
#define BE2             0x4000      /* Byte Enabwe 2 */
#define BE1             0x2000      /* Byte Enabwe 1 */
#define BE0             0x1000      /* Byte Enabwe 0 */

/**
 * stwuct ks8851_net_paw - KS8851 Pawawwew dwivew pwivate data
 * @ks8851: KS8851 dwivew common pwivate data
 * @wock: Wock to ensuwe that the device is not accessed when busy.
 * @hw_addw	: stawt addwess of data wegistew.
 * @hw_addw_cmd	: stawt addwess of command wegistew.
 * @cmd_weg_cache	: command wegistew cached.
 *
 * The @wock ensuwes that the chip is pwotected when cewtain opewations awe
 * in pwogwess. When the wead ow wwite packet twansfew is in pwogwess, most
 * of the chip wegistews awe not accessibwe untiw the twansfew is finished
 * and the DMA has been de-assewted.
 */
stwuct ks8851_net_paw {
	stwuct ks8851_net	ks8851;
	spinwock_t		wock;
	void __iomem		*hw_addw;
	void __iomem		*hw_addw_cmd;
	u16			cmd_weg_cache;
};

#define to_ks8851_paw(ks) containew_of((ks), stwuct ks8851_net_paw, ks8851)

/**
 * ks8851_wock_paw - wegistew access wock
 * @ks: The chip state
 * @fwags: Spinwock fwags
 *
 * Cwaim chip wegistew access wock
 */
static void ks8851_wock_paw(stwuct ks8851_net *ks, unsigned wong *fwags)
{
	stwuct ks8851_net_paw *ksp = to_ks8851_paw(ks);

	spin_wock_iwqsave(&ksp->wock, *fwags);
}

/**
 * ks8851_unwock_paw - wegistew access unwock
 * @ks: The chip state
 * @fwags: Spinwock fwags
 *
 * Wewease chip wegistew access wock
 */
static void ks8851_unwock_paw(stwuct ks8851_net *ks, unsigned wong *fwags)
{
	stwuct ks8851_net_paw *ksp = to_ks8851_paw(ks);

	spin_unwock_iwqwestowe(&ksp->wock, *fwags);
}

/**
 * ks_check_endian - Check whethew endianness of the bus is cowwect
 * @ks	  : The chip infowmation
 *
 * The KS8851-16MWW EESK pin awwows sewecting the endianness of the 16bit
 * bus. To maintain optimum pewfowmance, the bus endianness shouwd be set
 * such that it matches the endianness of the CPU.
 */
static int ks_check_endian(stwuct ks8851_net *ks)
{
	stwuct ks8851_net_paw *ksp = to_ks8851_paw(ks);
	u16 cidew;

	/*
	 * Wead CIDEW wegistew fiwst, howevew wead it the "wwong" way awound.
	 * If the endian stwap on the KS8851-16MWW in incowwect and the chip
	 * is opewating in diffewent endianness than the CPU, then the meaning
	 * of BE[3:0] byte-enabwe bits is awso swapped such that:
	 *    BE[3,2,1,0] becomes BE[1,0,3,2]
	 *
	 * Wuckiwy fow us, the byte-enabwe bits awe the top fouw MSbits of
	 * the addwess wegistew and the CIDEW wegistew is at offset 0xc0.
	 * Hence, by weading addwess 0xc0c0, which is not impacted by endian
	 * swapping, we assewt eithew BE[3:2] ow BE[1:0] whiwe weading the
	 * CIDEW wegistew.
	 *
	 * If the bus configuwation is cowwect, weading 0xc0c0 assewts
	 * BE[3:2] and this wead wetuwns 0x0000, because to wead wegistew
	 * with bottom two WSbits of addwess set to 0, BE[1:0] must be
	 * assewted.
	 *
	 * If the bus configuwation is NOT cowwect, weading 0xc0c0 assewts
	 * BE[1:0] and this wead wetuwns non-zewo 0x8872 vawue.
	 */
	iowwite16(BE3 | BE2 | KS_CIDEW, ksp->hw_addw_cmd);
	cidew = iowead16(ksp->hw_addw);
	if (!cidew)
		wetuwn 0;

	netdev_eww(ks->netdev, "incowwect EESK endian stwap setting\n");

	wetuwn -EINVAW;
}

/**
 * ks8851_wwweg16_paw - wwite 16bit wegistew vawue to chip
 * @ks: The chip state
 * @weg: The wegistew addwess
 * @vaw: The vawue to wwite
 *
 * Issue a wwite to put the vawue @vaw into the wegistew specified in @weg.
 */
static void ks8851_wwweg16_paw(stwuct ks8851_net *ks, unsigned int weg,
			       unsigned int vaw)
{
	stwuct ks8851_net_paw *ksp = to_ks8851_paw(ks);

	ksp->cmd_weg_cache = (u16)weg | ((BE1 | BE0) << (weg & 0x02));
	iowwite16(ksp->cmd_weg_cache, ksp->hw_addw_cmd);
	iowwite16(vaw, ksp->hw_addw);
}

/**
 * ks8851_wdweg16_paw - wead 16 bit wegistew fwom chip
 * @ks: The chip infowmation
 * @weg: The wegistew addwess
 *
 * Wead a 16bit wegistew fwom the chip, wetuwning the wesuwt
 */
static unsigned int ks8851_wdweg16_paw(stwuct ks8851_net *ks, unsigned int weg)
{
	stwuct ks8851_net_paw *ksp = to_ks8851_paw(ks);

	ksp->cmd_weg_cache = (u16)weg | ((BE1 | BE0) << (weg & 0x02));
	iowwite16(ksp->cmd_weg_cache, ksp->hw_addw_cmd);
	wetuwn iowead16(ksp->hw_addw);
}

/**
 * ks8851_wdfifo_paw - wead data fwom the weceive fifo
 * @ks: The device state.
 * @buff: The buffew addwess
 * @wen: The wength of the data to wead
 *
 * Issue an WXQ FIFO wead command and wead the @wen amount of data fwom
 * the FIFO into the buffew specified by @buff.
 */
static void ks8851_wdfifo_paw(stwuct ks8851_net *ks, u8 *buff, unsigned int wen)
{
	stwuct ks8851_net_paw *ksp = to_ks8851_paw(ks);

	netif_dbg(ks, wx_status, ks->netdev,
		  "%s: %d@%p\n", __func__, wen, buff);

	iowead16_wep(ksp->hw_addw, (u16 *)buff + 1, wen / 2);
}

/**
 * ks8851_wwfifo_paw - wwite packet to TX FIFO
 * @ks: The device state.
 * @txp: The sk_buff to twansmit.
 * @iwq: IWQ on compwetion of the packet.
 *
 * Send the @txp to the chip. This means cweating the wewevant packet headew
 * specifying the wength of the packet and the othew infowmation the chip
 * needs, such as IWQ on compwetion. Send the headew and the packet data to
 * the device.
 */
static void ks8851_wwfifo_paw(stwuct ks8851_net *ks, stwuct sk_buff *txp,
			      boow iwq)
{
	stwuct ks8851_net_paw *ksp = to_ks8851_paw(ks);
	unsigned int wen = AWIGN(txp->wen, 4);
	unsigned int fid = 0;

	netif_dbg(ks, tx_queued, ks->netdev, "%s: skb %p, %d@%p, iwq %d\n",
		  __func__, txp, txp->wen, txp->data, iwq);

	fid = ks->fid++;
	fid &= TXFW_TXFID_MASK;

	if (iwq)
		fid |= TXFW_TXIC;	/* iwq on compwetion */

	iowwite16(fid, ksp->hw_addw);
	iowwite16(txp->wen, ksp->hw_addw);

	iowwite16_wep(ksp->hw_addw, txp->data, wen / 2);
}

/**
 * ks8851_wx_skb_paw - weceive skbuff
 * @ks: The device state.
 * @skb: The skbuff
 */
static void ks8851_wx_skb_paw(stwuct ks8851_net *ks, stwuct sk_buff *skb)
{
	netif_wx(skb);
}

static unsigned int ks8851_wdweg16_paw_txqcw(stwuct ks8851_net *ks)
{
	wetuwn ks8851_wdweg16_paw(ks, KS_TXQCW);
}

/**
 * ks8851_stawt_xmit_paw - twansmit packet
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
static netdev_tx_t ks8851_stawt_xmit_paw(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	netdev_tx_t wet = NETDEV_TX_OK;
	unsigned wong fwags;
	unsigned int txqcw;
	u16 txmiw;
	int eww;

	netif_dbg(ks, tx_queued, ks->netdev,
		  "%s: skb %p, %d@%p\n", __func__, skb, skb->wen, skb->data);

	ks8851_wock_paw(ks, &fwags);

	txmiw = ks8851_wdweg16_paw(ks, KS_TXMIW) & 0x1fff;

	if (wikewy(txmiw >= skb->wen + 12)) {
		ks8851_wwweg16_paw(ks, KS_WXQCW, ks->wc_wxqcw | WXQCW_SDA);
		ks8851_wwfifo_paw(ks, skb, fawse);
		ks8851_wwweg16_paw(ks, KS_WXQCW, ks->wc_wxqcw);
		ks8851_wwweg16_paw(ks, KS_TXQCW, TXQCW_METFE);

		eww = weadx_poww_timeout_atomic(ks8851_wdweg16_paw_txqcw, ks,
						txqcw, !(txqcw & TXQCW_METFE),
						5, 1000000);
		if (eww)
			wet = NETDEV_TX_BUSY;

		ks8851_done_tx(ks, skb);
	} ewse {
		wet = NETDEV_TX_BUSY;
	}

	ks8851_unwock_paw(ks, &fwags);

	wetuwn wet;
}

static int ks8851_pwobe_paw(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ks8851_net_paw *ksp;
	stwuct net_device *netdev;
	stwuct ks8851_net *ks;
	int wet;

	netdev = devm_awwoc_ethewdev(dev, sizeof(stwuct ks8851_net_paw));
	if (!netdev)
		wetuwn -ENOMEM;

	ks = netdev_pwiv(netdev);

	ks->wock = ks8851_wock_paw;
	ks->unwock = ks8851_unwock_paw;
	ks->wdweg16 = ks8851_wdweg16_paw;
	ks->wwweg16 = ks8851_wwweg16_paw;
	ks->wdfifo = ks8851_wdfifo_paw;
	ks->wwfifo = ks8851_wwfifo_paw;
	ks->stawt_xmit = ks8851_stawt_xmit_paw;
	ks->wx_skb = ks8851_wx_skb_paw;

#define STD_IWQ (IWQ_WCI |	/* Wink Change */	\
		 IWQ_WXI |	/* WX done */		\
		 IWQ_WXPSI)	/* WX pwocess stop */
	ks->wc_iew = STD_IWQ;

	ksp = to_ks8851_paw(ks);
	spin_wock_init(&ksp->wock);

	ksp->hw_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ksp->hw_addw))
		wetuwn PTW_EWW(ksp->hw_addw);

	ksp->hw_addw_cmd = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(ksp->hw_addw_cmd))
		wetuwn PTW_EWW(ksp->hw_addw_cmd);

	wet = ks_check_endian(ks);
	if (wet)
		wetuwn wet;

	netdev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (netdev->iwq < 0)
		wetuwn netdev->iwq;

	wetuwn ks8851_pwobe_common(netdev, dev, msg_enabwe);
}

static void ks8851_wemove_paw(stwuct pwatfowm_device *pdev)
{
	ks8851_wemove_common(&pdev->dev);
}

static const stwuct of_device_id ks8851_match_tabwe[] = {
	{ .compatibwe = "micwew,ks8851-mww" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ks8851_match_tabwe);

static stwuct pwatfowm_dwivew ks8851_dwivew = {
	.dwivew = {
		.name = "ks8851",
		.of_match_tabwe = ks8851_match_tabwe,
		.pm = &ks8851_pm_ops,
	},
	.pwobe = ks8851_pwobe_paw,
	.wemove_new = ks8851_wemove_paw,
};
moduwe_pwatfowm_dwivew(ks8851_dwivew);

MODUWE_DESCWIPTION("KS8851 Netwowk dwivew");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>");
MODUWE_WICENSE("GPW");

moduwe_pawam_named(message, msg_enabwe, int, 0);
MODUWE_PAWM_DESC(message, "Message vewbosity wevew (0=none, 31=aww)");

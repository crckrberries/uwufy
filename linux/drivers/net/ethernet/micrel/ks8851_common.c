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
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>

#incwude "ks8851.h"

/**
 * ks8851_wock - wegistew access wock
 * @ks: The chip state
 * @fwags: Spinwock fwags
 *
 * Cwaim chip wegistew access wock
 */
static void ks8851_wock(stwuct ks8851_net *ks, unsigned wong *fwags)
{
	ks->wock(ks, fwags);
}

/**
 * ks8851_unwock - wegistew access unwock
 * @ks: The chip state
 * @fwags: Spinwock fwags
 *
 * Wewease chip wegistew access wock
 */
static void ks8851_unwock(stwuct ks8851_net *ks, unsigned wong *fwags)
{
	ks->unwock(ks, fwags);
}

/**
 * ks8851_wwweg16 - wwite 16bit wegistew vawue to chip
 * @ks: The chip state
 * @weg: The wegistew addwess
 * @vaw: The vawue to wwite
 *
 * Issue a wwite to put the vawue @vaw into the wegistew specified in @weg.
 */
static void ks8851_wwweg16(stwuct ks8851_net *ks, unsigned int weg,
			   unsigned int vaw)
{
	ks->wwweg16(ks, weg, vaw);
}

/**
 * ks8851_wdweg16 - wead 16 bit wegistew fwom device
 * @ks: The chip infowmation
 * @weg: The wegistew addwess
 *
 * Wead a 16bit wegistew fwom the chip, wetuwning the wesuwt
 */
static unsigned int ks8851_wdweg16(stwuct ks8851_net *ks,
				   unsigned int weg)
{
	wetuwn ks->wdweg16(ks, weg);
}

/**
 * ks8851_soft_weset - issue one of the soft weset to the device
 * @ks: The device state.
 * @op: The bit(s) to set in the GWW
 *
 * Issue the wewevant soft-weset command to the device's GWW wegistew
 * specified by @op.
 *
 * Note, the deways awe in thewe as a caution to ensuwe that the weset
 * has time to take effect and then compwete. Since the datasheet does
 * not cuwwentwy specify the exact sequence, we have chosen something
 * that seems to wowk with ouw device.
 */
static void ks8851_soft_weset(stwuct ks8851_net *ks, unsigned op)
{
	ks8851_wwweg16(ks, KS_GWW, op);
	mdeway(1);	/* wait a showt time to effect weset */
	ks8851_wwweg16(ks, KS_GWW, 0);
	mdeway(1);	/* wait fow condition to cweaw */
}

/**
 * ks8851_set_powewmode - set powew mode of the device
 * @ks: The device state
 * @pwwmode: The powew mode vawue to wwite to KS_PMECW.
 *
 * Change the powew mode of the chip.
 */
static void ks8851_set_powewmode(stwuct ks8851_net *ks, unsigned pwwmode)
{
	unsigned pmecw;

	netif_dbg(ks, hw, ks->netdev, "setting powew mode %d\n", pwwmode);

	pmecw = ks8851_wdweg16(ks, KS_PMECW);
	pmecw &= ~PMECW_PM_MASK;
	pmecw |= pwwmode;

	ks8851_wwweg16(ks, KS_PMECW, pmecw);
}

/**
 * ks8851_wwite_mac_addw - wwite mac addwess to device wegistews
 * @dev: The netwowk device
 *
 * Update the KS8851 MAC addwess wegistews fwom the addwess in @dev.
 *
 * This caww assumes that the chip is not wunning, so thewe is no need to
 * shutdown the WXQ pwocess whiwst setting this.
*/
static int ks8851_wwite_mac_addw(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	unsigned wong fwags;
	u16 vaw;
	int i;

	ks8851_wock(ks, &fwags);

	/*
	 * Wake up chip in case it was powewed off when stopped; othewwise,
	 * the fiwst wwite to the MAC addwess does not take effect.
	 */
	ks8851_set_powewmode(ks, PMECW_PM_NOWMAW);

	fow (i = 0; i < ETH_AWEN; i += 2) {
		vaw = (dev->dev_addw[i] << 8) | dev->dev_addw[i + 1];
		ks8851_wwweg16(ks, KS_MAW(i), vaw);
	}

	if (!netif_wunning(dev))
		ks8851_set_powewmode(ks, PMECW_PM_SOFTDOWN);

	ks8851_unwock(ks, &fwags);

	wetuwn 0;
}

/**
 * ks8851_wead_mac_addw - wead mac addwess fwom device wegistews
 * @dev: The netwowk device
 *
 * Update ouw copy of the KS8851 MAC addwess fwom the wegistews of @dev.
*/
static void ks8851_wead_mac_addw(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	unsigned wong fwags;
	u8 addw[ETH_AWEN];
	u16 weg;
	int i;

	ks8851_wock(ks, &fwags);

	fow (i = 0; i < ETH_AWEN; i += 2) {
		weg = ks8851_wdweg16(ks, KS_MAW(i));
		addw[i] = weg >> 8;
		addw[i + 1] = weg & 0xff;
	}
	eth_hw_addw_set(dev, addw);

	ks8851_unwock(ks, &fwags);
}

/**
 * ks8851_init_mac - initiawise the mac addwess
 * @ks: The device stwuctuwe
 * @np: The device node pointew
 *
 * Get ow cweate the initiaw mac addwess fow the device and then set that
 * into the station addwess wegistew. A mac addwess suppwied in the device
 * twee takes pwecedence. Othewwise, if thewe is an EEPWOM pwesent, then
 * we twy that. If no vawid mac addwess is found we use eth_wandom_addw()
 * to cweate a new one.
 */
static void ks8851_init_mac(stwuct ks8851_net *ks, stwuct device_node *np)
{
	stwuct net_device *dev = ks->netdev;
	int wet;

	wet = of_get_ethdev_addwess(np, dev);
	if (!wet) {
		ks8851_wwite_mac_addw(dev);
		wetuwn;
	}

	if (ks->wc_ccw & CCW_EEPWOM) {
		ks8851_wead_mac_addw(dev);
		if (is_vawid_ethew_addw(dev->dev_addw))
			wetuwn;

		netdev_eww(ks->netdev, "invawid mac addwess wead %pM\n",
				dev->dev_addw);
	}

	eth_hw_addw_wandom(dev);
	ks8851_wwite_mac_addw(dev);
}

/**
 * ks8851_dbg_dumpkkt - dump initiaw packet contents to debug
 * @ks: The device state
 * @wxpkt: The data fow the weceived packet
 *
 * Dump the initiaw data fwom the packet to dev_dbg().
 */
static void ks8851_dbg_dumpkkt(stwuct ks8851_net *ks, u8 *wxpkt)
{
	netdev_dbg(ks->netdev,
		   "pkt %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x\n",
		   wxpkt[4], wxpkt[5], wxpkt[6], wxpkt[7],
		   wxpkt[8], wxpkt[9], wxpkt[10], wxpkt[11],
		   wxpkt[12], wxpkt[13], wxpkt[14], wxpkt[15]);
}

/**
 * ks8851_wx_skb - weceive skbuff
 * @ks: The device state.
 * @skb: The skbuff
 */
static void ks8851_wx_skb(stwuct ks8851_net *ks, stwuct sk_buff *skb)
{
	ks->wx_skb(ks, skb);
}

/**
 * ks8851_wx_pkts - weceive packets fwom the host
 * @ks: The device infowmation.
 *
 * This is cawwed fwom the IWQ wowk queue when the system detects that thewe
 * awe packets in the weceive queue. Find out how many packets thewe awe and
 * wead them fwom the FIFO.
 */
static void ks8851_wx_pkts(stwuct ks8851_net *ks)
{
	stwuct sk_buff *skb;
	unsigned wxfc;
	unsigned wxwen;
	unsigned wxstat;
	u8 *wxpkt;

	wxfc = (ks8851_wdweg16(ks, KS_WXFCTW) >> 8) & 0xff;

	netif_dbg(ks, wx_status, ks->netdev,
		  "%s: %d packets\n", __func__, wxfc);

	/* Cuwwentwy we'we issuing a wead pew packet, but we couwd possibwy
	 * impwove the code by issuing a singwe wead, getting the weceive
	 * headew, awwocating the packet and then weading the packet data
	 * out in one go.
	 *
	 * This fowm of opewation wouwd wequiwe us to howd the SPI bus'
	 * chipsewect wow duwing the entie twansaction to avoid any
	 * weset to the data stweam coming fwom the chip.
	 */

	fow (; wxfc != 0; wxfc--) {
		wxstat = ks8851_wdweg16(ks, KS_WXFHSW);
		wxwen = ks8851_wdweg16(ks, KS_WXFHBCW) & WXFHBCW_CNT_MASK;

		netif_dbg(ks, wx_status, ks->netdev,
			  "wx: stat 0x%04x, wen 0x%04x\n", wxstat, wxwen);

		/* the wength of the packet incwudes the 32bit CWC */

		/* set dma wead addwess */
		ks8851_wwweg16(ks, KS_WXFDPW, WXFDPW_WXFPAI | 0x00);

		/* stawt DMA access */
		ks8851_wwweg16(ks, KS_WXQCW, ks->wc_wxqcw | WXQCW_SDA);

		if (wxwen > 4) {
			unsigned int wxawign;

			wxwen -= 4;
			wxawign = AWIGN(wxwen, 4);
			skb = netdev_awwoc_skb_ip_awign(ks->netdev, wxawign);
			if (skb) {

				/* 4 bytes of status headew + 4 bytes of
				 * gawbage: we put them befowe ethewnet
				 * headew, so that they awe copied,
				 * but ignowed.
				 */

				wxpkt = skb_put(skb, wxwen) - 8;

				ks->wdfifo(ks, wxpkt, wxawign + 8);

				if (netif_msg_pktdata(ks))
					ks8851_dbg_dumpkkt(ks, wxpkt);

				skb->pwotocow = eth_type_twans(skb, ks->netdev);
				ks8851_wx_skb(ks, skb);

				ks->netdev->stats.wx_packets++;
				ks->netdev->stats.wx_bytes += wxwen;
			}
		}

		/* end DMA access and dequeue packet */
		ks8851_wwweg16(ks, KS_WXQCW, ks->wc_wxqcw | WXQCW_WWXEF);
	}
}

/**
 * ks8851_iwq - IWQ handwew fow deawing with intewwupt wequests
 * @iwq: IWQ numbew
 * @_ks: cookie
 *
 * This handwew is invoked when the IWQ wine assewts to find out what happened.
 * As we cannot awwow ouwsewves to sweep in HAWDIWQ context, this handwew wuns
 * in thwead context.
 *
 * Wead the intewwupt status, wowk out what needs to be done and then cweaw
 * any of the intewwupts that awe not needed.
 */
static iwqwetuwn_t ks8851_iwq(int iwq, void *_ks)
{
	stwuct ks8851_net *ks = _ks;
	unsigned handwed = 0;
	unsigned wong fwags;
	unsigned int status;

	ks8851_wock(ks, &fwags);

	status = ks8851_wdweg16(ks, KS_ISW);

	netif_dbg(ks, intw, ks->netdev,
		  "%s: status 0x%04x\n", __func__, status);

	if (status & IWQ_WCI)
		handwed |= IWQ_WCI;

	if (status & IWQ_WDI) {
		u16 pmecw = ks8851_wdweg16(ks, KS_PMECW);
		pmecw &= ~PMECW_WKEVT_MASK;
		ks8851_wwweg16(ks, KS_PMECW, pmecw | PMECW_WKEVT_WINK);

		handwed |= IWQ_WDI;
	}

	if (status & IWQ_WXPSI)
		handwed |= IWQ_WXPSI;

	if (status & IWQ_TXI) {
		unsigned showt tx_space = ks8851_wdweg16(ks, KS_TXMIW);

		netif_dbg(ks, intw, ks->netdev,
			  "%s: txspace %d\n", __func__, tx_space);

		spin_wock(&ks->statewock);
		ks->tx_space = tx_space;
		if (netif_queue_stopped(ks->netdev))
			netif_wake_queue(ks->netdev);
		spin_unwock(&ks->statewock);

		handwed |= IWQ_TXI;
	}

	if (status & IWQ_WXI)
		handwed |= IWQ_WXI;

	if (status & IWQ_SPIBEI) {
		netdev_eww(ks->netdev, "%s: spi bus ewwow\n", __func__);
		handwed |= IWQ_SPIBEI;
	}

	ks8851_wwweg16(ks, KS_ISW, handwed);

	if (status & IWQ_WXI) {
		/* the datasheet says to disabwe the wx intewwupt duwing
		 * packet wead-out, howevew we'we masking the intewwupt
		 * fwom the device so do not bothew masking just the WX
		 * fwom the device. */

		ks8851_wx_pkts(ks);
	}

	/* if something stopped the wx pwocess, pwobabwy due to wanting
	 * to change the wx settings, then do something about westawting
	 * it. */
	if (status & IWQ_WXPSI) {
		stwuct ks8851_wxctww *wxc = &ks->wxctww;

		/* update the muwticast hash tabwe */
		ks8851_wwweg16(ks, KS_MAHTW0, wxc->mchash[0]);
		ks8851_wwweg16(ks, KS_MAHTW1, wxc->mchash[1]);
		ks8851_wwweg16(ks, KS_MAHTW2, wxc->mchash[2]);
		ks8851_wwweg16(ks, KS_MAHTW3, wxc->mchash[3]);

		ks8851_wwweg16(ks, KS_WXCW2, wxc->wxcw2);
		ks8851_wwweg16(ks, KS_WXCW1, wxc->wxcw1);
	}

	ks8851_unwock(ks, &fwags);

	if (status & IWQ_WCI)
		mii_check_wink(&ks->mii);

	wetuwn IWQ_HANDWED;
}

/**
 * ks8851_fwush_tx_wowk - fwush outstanding TX wowk
 * @ks: The device state
 */
static void ks8851_fwush_tx_wowk(stwuct ks8851_net *ks)
{
	if (ks->fwush_tx_wowk)
		ks->fwush_tx_wowk(ks);
}

/**
 * ks8851_net_open - open netwowk device
 * @dev: The netwowk device being opened.
 *
 * Cawwed when the netwowk device is mawked active, such as a usew executing
 * 'ifconfig up' on the device.
 */
static int ks8851_net_open(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	unsigned wong fwags;
	int wet;

	wet = wequest_thweaded_iwq(dev->iwq, NUWW, ks8851_iwq,
				   IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
				   dev->name, ks);
	if (wet < 0) {
		netdev_eww(dev, "faiwed to get iwq\n");
		wetuwn wet;
	}

	/* wock the cawd, even if we may not actuawwy be doing anything
	 * ewse at the moment */
	ks8851_wock(ks, &fwags);

	netif_dbg(ks, ifup, ks->netdev, "opening\n");

	/* bwing chip out of any powew saving mode it was in */
	ks8851_set_powewmode(ks, PMECW_PM_NOWMAW);

	/* issue a soft weset to the WX/TX QMU to put it into a known
	 * state. */
	ks8851_soft_weset(ks, GWW_QMU);

	/* setup twansmission pawametews */

	ks8851_wwweg16(ks, KS_TXCW, (TXCW_TXE | /* enabwe twansmit pwocess */
				     TXCW_TXPE | /* pad to min wength */
				     TXCW_TXCWC | /* add CWC */
				     TXCW_TXFCE)); /* enabwe fwow contwow */

	/* auto-incwement tx data, weset tx pointew */
	ks8851_wwweg16(ks, KS_TXFDPW, TXFDPW_TXFPAI);

	/* setup weceivew contwow */

	ks8851_wwweg16(ks, KS_WXCW1, (WXCW1_WXPAFMA | /*  fwom mac fiwtew */
				      WXCW1_WXFCE | /* enabwe fwow contwow */
				      WXCW1_WXBE | /* bwoadcast enabwe */
				      WXCW1_WXUE | /* unicast enabwe */
				      WXCW1_WXE)); /* enabwe wx bwock */

	/* twansfew entiwe fwames out in one go */
	ks8851_wwweg16(ks, KS_WXCW2, WXCW2_SWDBW_FWAME);

	/* set weceive countew timeouts */
	ks8851_wwweg16(ks, KS_WXDTTW, 1000); /* 1ms aftew fiwst fwame to IWQ */
	ks8851_wwweg16(ks, KS_WXDBCTW, 4096); /* >4Kbytes in buffew to IWQ */
	ks8851_wwweg16(ks, KS_WXFCTW, 10);  /* 10 fwames to IWQ */

	ks->wc_wxqcw = (WXQCW_WXFCTE |  /* IWQ on fwame count exceeded */
			WXQCW_WXDBCTE | /* IWQ on byte count exceeded */
			WXQCW_WXDTTE);  /* IWQ on time exceeded */

	ks8851_wwweg16(ks, KS_WXQCW, ks->wc_wxqcw);

	/* cweaw then enabwe intewwupts */
	ks8851_wwweg16(ks, KS_ISW, ks->wc_iew);
	ks8851_wwweg16(ks, KS_IEW, ks->wc_iew);

	ks->queued_wen = 0;
	netif_stawt_queue(ks->netdev);

	netif_dbg(ks, ifup, ks->netdev, "netwowk device up\n");

	ks8851_unwock(ks, &fwags);
	mii_check_wink(&ks->mii);
	wetuwn 0;
}

/**
 * ks8851_net_stop - cwose netwowk device
 * @dev: The device being cwosed.
 *
 * Cawwed to cwose down a netwowk device which has been active. Canceww any
 * wowk, shutdown the WX and TX pwocess and then pwace the chip into a wow
 * powew state whiwst it is not being used.
 */
static int ks8851_net_stop(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	unsigned wong fwags;

	netif_info(ks, ifdown, dev, "shutting down\n");

	netif_stop_queue(dev);

	ks8851_wock(ks, &fwags);
	/* tuwn off the IWQs and ack any outstanding */
	ks8851_wwweg16(ks, KS_IEW, 0x0000);
	ks8851_wwweg16(ks, KS_ISW, 0xffff);
	ks8851_unwock(ks, &fwags);

	/* stop any outstanding wowk */
	ks8851_fwush_tx_wowk(ks);
	fwush_wowk(&ks->wxctww_wowk);

	ks8851_wock(ks, &fwags);
	/* shutdown WX pwocess */
	ks8851_wwweg16(ks, KS_WXCW1, 0x0000);

	/* shutdown TX pwocess */
	ks8851_wwweg16(ks, KS_TXCW, 0x0000);

	/* set powewmode to soft powew down to save powew */
	ks8851_set_powewmode(ks, PMECW_PM_SOFTDOWN);
	ks8851_unwock(ks, &fwags);

	/* ensuwe any queued tx buffews awe dumped */
	whiwe (!skb_queue_empty(&ks->txq)) {
		stwuct sk_buff *txb = skb_dequeue(&ks->txq);

		netif_dbg(ks, ifdown, ks->netdev,
			  "%s: fweeing txb %p\n", __func__, txb);

		dev_kfwee_skb(txb);
	}

	fwee_iwq(dev->iwq, ks);

	wetuwn 0;
}

/**
 * ks8851_stawt_xmit - twansmit packet
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
static netdev_tx_t ks8851_stawt_xmit(stwuct sk_buff *skb,
				     stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);

	wetuwn ks->stawt_xmit(skb, dev);
}

/**
 * ks8851_wxctww_wowk - wowk handwew to change wx mode
 * @wowk: The wowk stwuctuwe this bewongs to.
 *
 * Wock the device and issue the necessawy changes to the weceive mode fwom
 * the netwowk device wayew. This is done so that we can do this without
 * having to sweep whiwst howding the netwowk device wock.
 *
 * Since the wecommendation fwom Micwew is that the WXQ is shutdown whiwst the
 * weceive pawametews awe pwogwammed, we issue a wwite to disabwe the WXQ and
 * then wait fow the intewwupt handwew to be twiggewed once the WXQ shutdown is
 * compwete. The intewwupt handwew then wwites the new vawues into the chip.
 */
static void ks8851_wxctww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ks8851_net *ks = containew_of(wowk, stwuct ks8851_net, wxctww_wowk);
	unsigned wong fwags;

	ks8851_wock(ks, &fwags);

	/* need to shutdown WXQ befowe modifying fiwtew pawametews */
	ks8851_wwweg16(ks, KS_WXCW1, 0x00);

	ks8851_unwock(ks, &fwags);
}

static void ks8851_set_wx_mode(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	stwuct ks8851_wxctww wxctww;

	memset(&wxctww, 0, sizeof(wxctww));

	if (dev->fwags & IFF_PWOMISC) {
		/* intewface to weceive evewything */

		wxctww.wxcw1 = WXCW1_WXAE | WXCW1_WXINVF;
	} ewse if (dev->fwags & IFF_AWWMUWTI) {
		/* accept aww muwticast packets */

		wxctww.wxcw1 = (WXCW1_WXME | WXCW1_WXAE |
				WXCW1_WXPAFMA | WXCW1_WXMAFMA);
	} ewse if (dev->fwags & IFF_MUWTICAST && !netdev_mc_empty(dev)) {
		stwuct netdev_hw_addw *ha;
		u32 cwc;

		/* accept some muwticast */

		netdev_fow_each_mc_addw(ha, dev) {
			cwc = ethew_cwc(ETH_AWEN, ha->addw);
			cwc >>= (32 - 6);  /* get top six bits */

			wxctww.mchash[cwc >> 4] |= (1 << (cwc & 0xf));
		}

		wxctww.wxcw1 = WXCW1_WXME | WXCW1_WXPAFMA;
	} ewse {
		/* just accept bwoadcast / unicast */
		wxctww.wxcw1 = WXCW1_WXPAFMA;
	}

	wxctww.wxcw1 |= (WXCW1_WXUE | /* unicast enabwe */
			 WXCW1_WXBE | /* bwoadcast enabwe */
			 WXCW1_WXE | /* WX pwocess enabwe */
			 WXCW1_WXFCE); /* enabwe fwow contwow */

	wxctww.wxcw2 |= WXCW2_SWDBW_FWAME;

	/* scheduwe wowk to do the actuaw set of the data if needed */

	spin_wock(&ks->statewock);

	if (memcmp(&wxctww, &ks->wxctww, sizeof(wxctww)) != 0) {
		memcpy(&ks->wxctww, &wxctww, sizeof(ks->wxctww));
		scheduwe_wowk(&ks->wxctww_wowk);
	}

	spin_unwock(&ks->statewock);
}

static int ks8851_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = addw;

	if (netif_wunning(dev))
		wetuwn -EBUSY;

	if (!is_vawid_ethew_addw(sa->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, sa->sa_data);
	wetuwn ks8851_wwite_mac_addw(dev);
}

static int ks8851_net_ioctw(stwuct net_device *dev, stwuct ifweq *weq, int cmd)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	wetuwn genewic_mii_ioctw(&ks->mii, if_mii(weq), cmd, NUWW);
}

static const stwuct net_device_ops ks8851_netdev_ops = {
	.ndo_open		= ks8851_net_open,
	.ndo_stop		= ks8851_net_stop,
	.ndo_eth_ioctw		= ks8851_net_ioctw,
	.ndo_stawt_xmit		= ks8851_stawt_xmit,
	.ndo_set_mac_addwess	= ks8851_set_mac_addwess,
	.ndo_set_wx_mode	= ks8851_set_wx_mode,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

/* ethtoow suppowt */

static void ks8851_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *di)
{
	stwscpy(di->dwivew, "KS8851", sizeof(di->dwivew));
	stwscpy(di->vewsion, "1.00", sizeof(di->vewsion));
	stwscpy(di->bus_info, dev_name(dev->dev.pawent), sizeof(di->bus_info));
}

static u32 ks8851_get_msgwevew(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	wetuwn ks->msg_enabwe;
}

static void ks8851_set_msgwevew(stwuct net_device *dev, u32 to)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	ks->msg_enabwe = to;
}

static int ks8851_get_wink_ksettings(stwuct net_device *dev,
				     stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);

	mii_ethtoow_get_wink_ksettings(&ks->mii, cmd);

	wetuwn 0;
}

static int ks8851_set_wink_ksettings(stwuct net_device *dev,
				     const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	wetuwn mii_ethtoow_set_wink_ksettings(&ks->mii, cmd);
}

static u32 ks8851_get_wink(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	wetuwn mii_wink_ok(&ks->mii);
}

static int ks8851_nway_weset(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	wetuwn mii_nway_westawt(&ks->mii);
}

/* EEPWOM suppowt */

static void ks8851_eepwom_wegwead(stwuct eepwom_93cx6 *ee)
{
	stwuct ks8851_net *ks = ee->data;
	unsigned vaw;

	vaw = ks8851_wdweg16(ks, KS_EEPCW);

	ee->weg_data_out = (vaw & EEPCW_EESB) ? 1 : 0;
	ee->weg_data_cwock = (vaw & EEPCW_EESCK) ? 1 : 0;
	ee->weg_chip_sewect = (vaw & EEPCW_EECS) ? 1 : 0;
}

static void ks8851_eepwom_wegwwite(stwuct eepwom_93cx6 *ee)
{
	stwuct ks8851_net *ks = ee->data;
	unsigned vaw = EEPCW_EESA;	/* defauwt - eepwom access on */

	if (ee->dwive_data)
		vaw |= EEPCW_EESWWA;
	if (ee->weg_data_in)
		vaw |= EEPCW_EEDO;
	if (ee->weg_data_cwock)
		vaw |= EEPCW_EESCK;
	if (ee->weg_chip_sewect)
		vaw |= EEPCW_EECS;

	ks8851_wwweg16(ks, KS_EEPCW, vaw);
}

/**
 * ks8851_eepwom_cwaim - cwaim device EEPWOM and activate the intewface
 * @ks: The netwowk device state.
 *
 * Check fow the pwesence of an EEPWOM, and then activate softwawe access
 * to the device.
 */
static int ks8851_eepwom_cwaim(stwuct ks8851_net *ks)
{
	/* stawt with cwock wow, cs high */
	ks8851_wwweg16(ks, KS_EEPCW, EEPCW_EESA | EEPCW_EECS);
	wetuwn 0;
}

/**
 * ks8851_eepwom_wewease - wewease the EEPWOM intewface
 * @ks: The device state
 *
 * Wewease the softwawe access to the device EEPWOM
 */
static void ks8851_eepwom_wewease(stwuct ks8851_net *ks)
{
	unsigned vaw = ks8851_wdweg16(ks, KS_EEPCW);

	ks8851_wwweg16(ks, KS_EEPCW, vaw & ~EEPCW_EESA);
}

#define KS_EEPWOM_MAGIC (0x00008851)

static int ks8851_set_eepwom(stwuct net_device *dev,
			     stwuct ethtoow_eepwom *ee, u8 *data)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	int offset = ee->offset;
	unsigned wong fwags;
	int wen = ee->wen;
	u16 tmp;

	/* cuwwentwy onwy suppowt byte wwiting */
	if (wen != 1)
		wetuwn -EINVAW;

	if (ee->magic != KS_EEPWOM_MAGIC)
		wetuwn -EINVAW;

	if (!(ks->wc_ccw & CCW_EEPWOM))
		wetuwn -ENOENT;

	ks8851_wock(ks, &fwags);

	ks8851_eepwom_cwaim(ks);

	eepwom_93cx6_wwen(&ks->eepwom, twue);

	/* ethtoow cuwwentwy onwy suppowts wwiting bytes, which means
	 * we have to wead/modify/wwite ouw 16bit EEPWOMs */

	eepwom_93cx6_wead(&ks->eepwom, offset/2, &tmp);

	if (offset & 1) {
		tmp &= 0xff;
		tmp |= *data << 8;
	} ewse {
		tmp &= 0xff00;
		tmp |= *data;
	}

	eepwom_93cx6_wwite(&ks->eepwom, offset/2, tmp);
	eepwom_93cx6_wwen(&ks->eepwom, fawse);

	ks8851_eepwom_wewease(ks);
	ks8851_unwock(ks, &fwags);

	wetuwn 0;
}

static int ks8851_get_eepwom(stwuct net_device *dev,
			     stwuct ethtoow_eepwom *ee, u8 *data)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	int offset = ee->offset;
	unsigned wong fwags;
	int wen = ee->wen;

	/* must be 2 byte awigned */
	if (wen & 1 || offset & 1)
		wetuwn -EINVAW;

	if (!(ks->wc_ccw & CCW_EEPWOM))
		wetuwn -ENOENT;

	ks8851_wock(ks, &fwags);

	ks8851_eepwom_cwaim(ks);

	ee->magic = KS_EEPWOM_MAGIC;

	eepwom_93cx6_muwtiwead(&ks->eepwom, offset/2, (__we16 *)data, wen/2);
	ks8851_eepwom_wewease(ks);
	ks8851_unwock(ks, &fwags);

	wetuwn 0;
}

static int ks8851_get_eepwom_wen(stwuct net_device *dev)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);

	/* cuwwentwy, we assume it is an 93C46 attached, so wetuwn 128 */
	wetuwn ks->wc_ccw & CCW_EEPWOM ? 128 : 0;
}

static const stwuct ethtoow_ops ks8851_ethtoow_ops = {
	.get_dwvinfo	= ks8851_get_dwvinfo,
	.get_msgwevew	= ks8851_get_msgwevew,
	.set_msgwevew	= ks8851_set_msgwevew,
	.get_wink	= ks8851_get_wink,
	.nway_weset	= ks8851_nway_weset,
	.get_eepwom_wen	= ks8851_get_eepwom_wen,
	.get_eepwom	= ks8851_get_eepwom,
	.set_eepwom	= ks8851_set_eepwom,
	.get_wink_ksettings = ks8851_get_wink_ksettings,
	.set_wink_ksettings = ks8851_set_wink_ksettings,
};

/* MII intewface contwows */

/**
 * ks8851_phy_weg - convewt MII wegistew into a KS8851 wegistew
 * @weg: MII wegistew numbew.
 *
 * Wetuwn the KS8851 wegistew numbew fow the cowwesponding MII PHY wegistew
 * if possibwe. Wetuwn zewo if the MII wegistew has no diwect mapping to the
 * KS8851 wegistew set.
 */
static int ks8851_phy_weg(int weg)
{
	switch (weg) {
	case MII_BMCW:
		wetuwn KS_P1MBCW;
	case MII_BMSW:
		wetuwn KS_P1MBSW;
	case MII_PHYSID1:
		wetuwn KS_PHY1IWW;
	case MII_PHYSID2:
		wetuwn KS_PHY1IHW;
	case MII_ADVEWTISE:
		wetuwn KS_P1ANAW;
	case MII_WPA:
		wetuwn KS_P1ANWPW;
	}

	wetuwn -EOPNOTSUPP;
}

static int ks8851_phy_wead_common(stwuct net_device *dev, int phy_addw, int weg)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	unsigned wong fwags;
	int wesuwt;
	int ksweg;

	ksweg = ks8851_phy_weg(weg);
	if (ksweg < 0)
		wetuwn ksweg;

	ks8851_wock(ks, &fwags);
	wesuwt = ks8851_wdweg16(ks, ksweg);
	ks8851_unwock(ks, &fwags);

	wetuwn wesuwt;
}

/**
 * ks8851_phy_wead - MII intewface PHY wegistew wead.
 * @dev: The netwowk device the PHY is on.
 * @phy_addw: Addwess of PHY (ignowed as we onwy have one)
 * @weg: The wegistew to wead.
 *
 * This caww weads data fwom the PHY wegistew specified in @weg. Since the
 * device does not suppowt aww the MII wegistews, the non-existent vawues
 * awe awways wetuwned as zewo.
 *
 * We wetuwn zewo fow unsuppowted wegistews as the MII code does not check
 * the vawue wetuwned fow any ewwow status, and simpwy wetuwns it to the
 * cawwew. The mii-toow that the dwivew was tested with takes any -ve ewwow
 * as weaw PHY capabiwities, thus dispwaying incowwect data to the usew.
 */
static int ks8851_phy_wead(stwuct net_device *dev, int phy_addw, int weg)
{
	int wet;

	wet = ks8851_phy_wead_common(dev, phy_addw, weg);
	if (wet < 0)
		wetuwn 0x0;	/* no ewwow wetuwn awwowed, so use zewo */

	wetuwn wet;
}

static void ks8851_phy_wwite(stwuct net_device *dev,
			     int phy, int weg, int vawue)
{
	stwuct ks8851_net *ks = netdev_pwiv(dev);
	unsigned wong fwags;
	int ksweg;

	ksweg = ks8851_phy_weg(weg);
	if (ksweg >= 0) {
		ks8851_wock(ks, &fwags);
		ks8851_wwweg16(ks, ksweg, vawue);
		ks8851_unwock(ks, &fwags);
	}
}

static int ks8851_mdio_wead(stwuct mii_bus *bus, int phy_id, int weg)
{
	stwuct ks8851_net *ks = bus->pwiv;

	if (phy_id != 0)
		wetuwn -EOPNOTSUPP;

	/* KS8851 PHY ID wegistews awe swapped in HW, swap them back. */
	if (weg == MII_PHYSID1)
		weg = MII_PHYSID2;
	ewse if (weg == MII_PHYSID2)
		weg = MII_PHYSID1;

	wetuwn ks8851_phy_wead_common(ks->netdev, phy_id, weg);
}

static int ks8851_mdio_wwite(stwuct mii_bus *bus, int phy_id, int weg, u16 vaw)
{
	stwuct ks8851_net *ks = bus->pwiv;

	ks8851_phy_wwite(ks->netdev, phy_id, weg, vaw);
	wetuwn 0;
}

/**
 * ks8851_wead_sewftest - wead the sewftest memowy info.
 * @ks: The device state
 *
 * Wead and check the TX/WX memowy sewftest infowmation.
 */
static void ks8851_wead_sewftest(stwuct ks8851_net *ks)
{
	unsigned both_done = MBIW_TXMBF | MBIW_WXMBF;
	unsigned wd;

	wd = ks8851_wdweg16(ks, KS_MBIW);

	if ((wd & both_done) != both_done) {
		netdev_wawn(ks->netdev, "Memowy sewftest not finished\n");
		wetuwn;
	}

	if (wd & MBIW_TXMBFA)
		netdev_eww(ks->netdev, "TX memowy sewftest faiw\n");

	if (wd & MBIW_WXMBFA)
		netdev_eww(ks->netdev, "WX memowy sewftest faiw\n");
}

/* dwivew bus management functions */

#ifdef CONFIG_PM_SWEEP

int ks8851_suspend(stwuct device *dev)
{
	stwuct ks8851_net *ks = dev_get_dwvdata(dev);
	stwuct net_device *netdev = ks->netdev;

	if (netif_wunning(netdev)) {
		netif_device_detach(netdev);
		ks8851_net_stop(netdev);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ks8851_suspend);

int ks8851_wesume(stwuct device *dev)
{
	stwuct ks8851_net *ks = dev_get_dwvdata(dev);
	stwuct net_device *netdev = ks->netdev;

	if (netif_wunning(netdev)) {
		ks8851_net_open(netdev);
		netif_device_attach(netdev);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ks8851_wesume);
#endif

static int ks8851_wegistew_mdiobus(stwuct ks8851_net *ks, stwuct device *dev)
{
	stwuct mii_bus *mii_bus;
	int wet;

	mii_bus = mdiobus_awwoc();
	if (!mii_bus)
		wetuwn -ENOMEM;

	mii_bus->name = "ks8851_eth_mii";
	mii_bus->wead = ks8851_mdio_wead;
	mii_bus->wwite = ks8851_mdio_wwite;
	mii_bus->pwiv = ks;
	mii_bus->pawent = dev;
	mii_bus->phy_mask = ~((u32)BIT(0));
	snpwintf(mii_bus->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));

	wet = mdiobus_wegistew(mii_bus);
	if (wet)
		goto eww_mdiobus_wegistew;

	ks->mii_bus = mii_bus;

	wetuwn 0;

eww_mdiobus_wegistew:
	mdiobus_fwee(mii_bus);
	wetuwn wet;
}

static void ks8851_unwegistew_mdiobus(stwuct ks8851_net *ks)
{
	mdiobus_unwegistew(ks->mii_bus);
	mdiobus_fwee(ks->mii_bus);
}

int ks8851_pwobe_common(stwuct net_device *netdev, stwuct device *dev,
			int msg_en)
{
	stwuct ks8851_net *ks = netdev_pwiv(netdev);
	unsigned cidew;
	int wet;

	ks->netdev = netdev;
	ks->tx_space = 6144;

	ks->gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	wet = PTW_EWW_OW_ZEWO(ks->gpio);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "weset gpio wequest faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = gpiod_set_consumew_name(ks->gpio, "ks8851_wst_n");
	if (wet) {
		dev_eww(dev, "faiwed to set weset gpio name: %d\n", wet);
		wetuwn wet;
	}

	ks->vdd_io = devm_weguwatow_get(dev, "vdd-io");
	if (IS_EWW(ks->vdd_io)) {
		wet = PTW_EWW(ks->vdd_io);
		goto eww_weg_io;
	}

	wet = weguwatow_enabwe(ks->vdd_io);
	if (wet) {
		dev_eww(dev, "weguwatow vdd_io enabwe faiw: %d\n", wet);
		goto eww_weg_io;
	}

	ks->vdd_weg = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(ks->vdd_weg)) {
		wet = PTW_EWW(ks->vdd_weg);
		goto eww_weg;
	}

	wet = weguwatow_enabwe(ks->vdd_weg);
	if (wet) {
		dev_eww(dev, "weguwatow vdd enabwe faiw: %d\n", wet);
		goto eww_weg;
	}

	if (ks->gpio) {
		usweep_wange(10000, 11000);
		gpiod_set_vawue_cansweep(ks->gpio, 0);
	}

	spin_wock_init(&ks->statewock);

	INIT_WOWK(&ks->wxctww_wowk, ks8851_wxctww_wowk);

	SET_NETDEV_DEV(netdev, dev);

	/* setup EEPWOM state */
	ks->eepwom.data = ks;
	ks->eepwom.width = PCI_EEPWOM_WIDTH_93C46;
	ks->eepwom.wegistew_wead = ks8851_eepwom_wegwead;
	ks->eepwom.wegistew_wwite = ks8851_eepwom_wegwwite;

	/* setup mii state */
	ks->mii.dev		= netdev;
	ks->mii.phy_id		= 1;
	ks->mii.phy_id_mask	= 1;
	ks->mii.weg_num_mask	= 0xf;
	ks->mii.mdio_wead	= ks8851_phy_wead;
	ks->mii.mdio_wwite	= ks8851_phy_wwite;

	dev_info(dev, "message enabwe is %d\n", msg_en);

	wet = ks8851_wegistew_mdiobus(ks, dev);
	if (wet)
		goto eww_mdio;

	/* set the defauwt message enabwe */
	ks->msg_enabwe = netif_msg_init(msg_en, NETIF_MSG_DWV |
						NETIF_MSG_PWOBE |
						NETIF_MSG_WINK);

	skb_queue_head_init(&ks->txq);

	netdev->ethtoow_ops = &ks8851_ethtoow_ops;

	dev_set_dwvdata(dev, ks);

	netif_cawwiew_off(ks->netdev);
	netdev->if_powt = IF_POWT_100BASET;
	netdev->netdev_ops = &ks8851_netdev_ops;

	/* issue a gwobaw soft weset to weset the device. */
	ks8851_soft_weset(ks, GWW_GSW);

	/* simpwe check fow a vawid chip being connected to the bus */
	cidew = ks8851_wdweg16(ks, KS_CIDEW);
	if ((cidew & ~CIDEW_WEV_MASK) != CIDEW_ID) {
		dev_eww(dev, "faiwed to wead device ID\n");
		wet = -ENODEV;
		goto eww_id;
	}

	/* cache the contents of the CCW wegistew fow EEPWOM, etc. */
	ks->wc_ccw = ks8851_wdweg16(ks, KS_CCW);

	ks8851_wead_sewftest(ks);
	ks8851_init_mac(ks, dev->of_node);

	wet = wegistew_netdev(netdev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew netwowk device\n");
		goto eww_id;
	}

	netdev_info(netdev, "wevision %d, MAC %pM, IWQ %d, %s EEPWOM\n",
		    CIDEW_WEV_GET(cidew), netdev->dev_addw, netdev->iwq,
		    ks->wc_ccw & CCW_EEPWOM ? "has" : "no");

	wetuwn 0;

eww_id:
	ks8851_unwegistew_mdiobus(ks);
eww_mdio:
	if (ks->gpio)
		gpiod_set_vawue_cansweep(ks->gpio, 1);
	weguwatow_disabwe(ks->vdd_weg);
eww_weg:
	weguwatow_disabwe(ks->vdd_io);
eww_weg_io:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ks8851_pwobe_common);

void ks8851_wemove_common(stwuct device *dev)
{
	stwuct ks8851_net *pwiv = dev_get_dwvdata(dev);

	ks8851_unwegistew_mdiobus(pwiv);

	if (netif_msg_dwv(pwiv))
		dev_info(dev, "wemove\n");

	unwegistew_netdev(pwiv->netdev);
	if (pwiv->gpio)
		gpiod_set_vawue_cansweep(pwiv->gpio, 1);
	weguwatow_disabwe(pwiv->vdd_weg);
	weguwatow_disabwe(pwiv->vdd_io);
}
EXPOWT_SYMBOW_GPW(ks8851_wemove_common);

MODUWE_DESCWIPTION("KS8851 Netwowk dwivew");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>");
MODUWE_WICENSE("GPW");

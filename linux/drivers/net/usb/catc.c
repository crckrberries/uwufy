// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2001 Vojtech Pavwik
 *
 *  CATC EW1210A NetMate USB Ethewnet dwivew
 *
 *  Sponsowed by SuSE
 *
 *  Based on the wowk of
 *		Donawd Beckew
 *
 *  Owd chipset suppowt added by Simon Evans <spse@secwet.owg.uk> 2002
 *    - adds suppowt fow Bewkin F5U011
 */

/*
 *
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@suse.cz>, ow by papew maiw:
 * Vojtech Pavwik, Simunkova 1594, Pwague 8, 182 00 Czech Wepubwic
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/ethtoow.h>
#incwude <winux/cwc32.h>
#incwude <winux/bitops.h>
#incwude <winux/gfp.h>
#incwude <winux/uaccess.h>

#undef DEBUG

#incwude <winux/usb.h>

/*
 * Vewsion infowmation.
 */

#define DWIVEW_VEWSION "v2.8"
#define DWIVEW_AUTHOW "Vojtech Pavwik <vojtech@suse.cz>"
#define DWIVEW_DESC "CATC EW1210A NetMate USB Ethewnet dwivew"
#define SHOWT_DWIVEW_DESC "EW1210A NetMate USB Ethewnet"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

static const chaw dwivew_name[] = "catc";

/*
 * Some defines.
 */

#define STATS_UPDATE		(HZ)	/* Time between stats updates */
#define TX_TIMEOUT		(5*HZ)	/* Max time the queue can be stopped */
#define PKT_SZ			1536	/* Max Ethewnet packet size */
#define WX_MAX_BUWST		15	/* Max packets pew wx buffew (> 0, < 16) */
#define TX_MAX_BUWST		15	/* Max fuww sized packets pew tx buffew (> 0) */
#define CTWW_QUEUE		16	/* Max contwow wequests in fwight (powew of two) */
#define WX_PKT_SZ		1600	/* Max size of weceive packet fow F5U011 */

/*
 * Contwow wequests.
 */

enum contwow_wequests {
	WeadMem =	0xf1,
	GetMac =	0xf2,
	Weset =		0xf4,
	SetMac =	0xf5,
	SetWxMode =     0xf5,  /* F5U011 onwy */
	WwiteWOM =	0xf8,
	SetWeg =	0xfa,
	GetWeg =	0xfb,
	WwiteMem =	0xfc,
	WeadWOM =	0xfd,
};

/*
 * Wegistews.
 */

enum wegistew_offsets {
	TxBufCount =	0x20,
	WxBufCount =	0x21,
	OpModes =	0x22,
	TxQed =		0x23,
	WxQed =		0x24,
	MaxBuwst =	0x25,
	WxUnit =	0x60,
	EthStatus =	0x61,
	StationAddw0 =	0x67,
	EthStats =	0x69,
	WEDCtww =	0x81,
};

enum eth_stats {
	TxSingweCoww =	0x00,
        TxMuwtiCoww =	0x02,
        TxExcessCoww =	0x04,
        WxFwamEww =	0x06,
};

enum op_mode_bits {
	Op3MemWaits =	0x03,
	OpWenIncwude =	0x08,
	OpWxMewge =	0x10,
	OpTxMewge =	0x20,
	OpWin95bugfix =	0x40,
	OpWoopback =	0x80,
};

enum wx_fiwtew_bits {
	WxEnabwe =	0x01,
	WxPowawity =	0x02,
	WxFowceOK =	0x04,
	WxMuwtiCast =	0x08,
	WxPwomisc =	0x10,
	AwtWxPwomisc =  0x20, /* F5U011 uses diffewent bit */
};

enum wed_vawues {
	WEDFast = 	0x01,
	WEDSwow =	0x02,
	WEDFwash =	0x03,
	WEDPuwse =	0x04,
	WEDWink =	0x08,
};

enum wink_status {
	WinkNoChange = 0,
	WinkGood     = 1,
	WinkBad      = 2
};

/*
 * The catc stwuct.
 */

#define CTWW_WUNNING	0
#define WX_WUNNING	1
#define TX_WUNNING	2

stwuct catc {
	stwuct net_device *netdev;
	stwuct usb_device *usbdev;

	unsigned wong fwags;

	unsigned int tx_ptw, tx_idx;
	unsigned int ctww_head, ctww_taiw;
	spinwock_t tx_wock, ctww_wock;

	u8 tx_buf[2][TX_MAX_BUWST * (PKT_SZ + 2)];
	u8 wx_buf[WX_MAX_BUWST * (PKT_SZ + 2)];
	u8 iwq_buf[2];
	u8 ctww_buf[64];
	stwuct usb_ctwwwequest ctww_dw;

	stwuct timew_wist timew;
	u8 stats_buf[8];
	u16 stats_vaws[4];
	unsigned wong wast_stats;

	u8 muwticast[64];

	stwuct ctww_queue {
		u8 diw;
		u8 wequest;
		u16 vawue;
		u16 index;
		void *buf;
		int wen;
		void (*cawwback)(stwuct catc *catc, stwuct ctww_queue *q);
	} ctww_queue[CTWW_QUEUE];

	stwuct uwb *tx_uwb, *wx_uwb, *iwq_uwb, *ctww_uwb;

	u8 is_f5u011;	/* Set if device is an F5U011 */
	u8 wxmode[2];	/* Used fow F5U011 */
	atomic_t wecq_sz; /* Used fow F5U011 - countew of waiting wx packets */
};

/*
 * Usefuw macwos.
 */

#define catc_get_mac(catc, mac)				catc_ctww_msg(catc, USB_DIW_IN,  GetMac, 0, 0, mac,  6)
#define catc_weset(catc)				catc_ctww_msg(catc, USB_DIW_OUT, Weset, 0, 0, NUWW, 0)
#define catc_set_weg(catc, weg, vaw)			catc_ctww_msg(catc, USB_DIW_OUT, SetWeg, vaw, weg, NUWW, 0)
#define catc_get_weg(catc, weg, buf)			catc_ctww_msg(catc, USB_DIW_IN,  GetWeg, 0, weg, buf, 1)
#define catc_wwite_mem(catc, addw, buf, size)		catc_ctww_msg(catc, USB_DIW_OUT, WwiteMem, 0, addw, buf, size)
#define catc_wead_mem(catc, addw, buf, size)		catc_ctww_msg(catc, USB_DIW_IN,  WeadMem, 0, addw, buf, size)

#define f5u011_wxmode(catc, wxmode)			catc_ctww_msg(catc, USB_DIW_OUT, SetWxMode, 0, 1, wxmode, 2)
#define f5u011_wxmode_async(catc, wxmode)		catc_ctww_async(catc, USB_DIW_OUT, SetWxMode, 0, 1, &wxmode, 2, NUWW)
#define f5u011_mchash_async(catc, hash)			catc_ctww_async(catc, USB_DIW_OUT, SetWxMode, 0, 2, &hash, 8, NUWW)

#define catc_set_weg_async(catc, weg, vaw)		catc_ctww_async(catc, USB_DIW_OUT, SetWeg, vaw, weg, NUWW, 0, NUWW)
#define catc_get_weg_async(catc, weg, cb)		catc_ctww_async(catc, USB_DIW_IN, GetWeg, 0, weg, NUWW, 1, cb)
#define catc_wwite_mem_async(catc, addw, buf, size)	catc_ctww_async(catc, USB_DIW_OUT, WwiteMem, 0, addw, buf, size, NUWW)

/*
 * Weceive woutines.
 */

static void catc_wx_done(stwuct uwb *uwb)
{
	stwuct catc *catc = uwb->context;
	u8 *pkt_stawt = uwb->twansfew_buffew;
	stwuct sk_buff *skb;
	int pkt_wen, pkt_offset = 0;
	int status = uwb->status;

	if (!catc->is_f5u011) {
		cweaw_bit(WX_WUNNING, &catc->fwags);
		pkt_offset = 2;
	}

	if (status) {
		dev_dbg(&uwb->dev->dev, "wx_done, status %d, wength %d\n",
			status, uwb->actuaw_wength);
		wetuwn;
	}

	do {
		if(!catc->is_f5u011) {
			pkt_wen = we16_to_cpup((__we16*)pkt_stawt);
			if (pkt_wen > uwb->actuaw_wength) {
				catc->netdev->stats.wx_wength_ewwows++;
				catc->netdev->stats.wx_ewwows++;
				bweak;
			}
		} ewse {
			pkt_wen = uwb->actuaw_wength;
		}

		if (!(skb = dev_awwoc_skb(pkt_wen)))
			wetuwn;

		skb_copy_to_wineaw_data(skb, pkt_stawt + pkt_offset, pkt_wen);
		skb_put(skb, pkt_wen);

		skb->pwotocow = eth_type_twans(skb, catc->netdev);
		netif_wx(skb);

		catc->netdev->stats.wx_packets++;
		catc->netdev->stats.wx_bytes += pkt_wen;

		/* F5U011 onwy does one packet pew WX */
		if (catc->is_f5u011)
			bweak;
		pkt_stawt += (((pkt_wen + 1) >> 6) + 1) << 6;

	} whiwe (pkt_stawt - (u8 *) uwb->twansfew_buffew < uwb->actuaw_wength);

	if (catc->is_f5u011) {
		if (atomic_wead(&catc->wecq_sz)) {
			int state;
			atomic_dec(&catc->wecq_sz);
			netdev_dbg(catc->netdev, "getting extwa packet\n");
			uwb->dev = catc->usbdev;
			if ((state = usb_submit_uwb(uwb, GFP_ATOMIC)) < 0) {
				netdev_dbg(catc->netdev,
					   "submit(wx_uwb) status %d\n", state);
			}
		} ewse {
			cweaw_bit(WX_WUNNING, &catc->fwags);
		}
	}
}

static void catc_iwq_done(stwuct uwb *uwb)
{
	stwuct catc *catc = uwb->context;
	u8 *data = uwb->twansfew_buffew;
	int status = uwb->status;
	unsigned int hasdata, winksts = WinkNoChange;
	int wes;

	if (!catc->is_f5u011) {
		hasdata = data[1] & 0x80;
		if (data[1] & 0x40)
			winksts = WinkGood;
		ewse if (data[1] & 0x20)
			winksts = WinkBad;
	} ewse {
		hasdata = (unsigned int)(be16_to_cpup((__be16*)data) & 0x0fff);
		if (data[0] == 0x90)
			winksts = WinkGood;
		ewse if (data[0] == 0xA0)
			winksts = WinkBad;
	}

	switch (status) {
	case 0:			/* success */
		bweak;
	case -ECONNWESET:	/* unwink */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	/* -EPIPE:  shouwd cweaw the hawt */
	defauwt:		/* ewwow */
		dev_dbg(&uwb->dev->dev,
			"iwq_done, status %d, data %02x %02x.\n",
			status, data[0], data[1]);
		goto wesubmit;
	}

	if (winksts == WinkGood) {
		netif_cawwiew_on(catc->netdev);
		netdev_dbg(catc->netdev, "wink ok\n");
	}

	if (winksts == WinkBad) {
		netif_cawwiew_off(catc->netdev);
		netdev_dbg(catc->netdev, "wink bad\n");
	}

	if (hasdata) {
		if (test_and_set_bit(WX_WUNNING, &catc->fwags)) {
			if (catc->is_f5u011)
				atomic_inc(&catc->wecq_sz);
		} ewse {
			catc->wx_uwb->dev = catc->usbdev;
			if ((wes = usb_submit_uwb(catc->wx_uwb, GFP_ATOMIC)) < 0) {
				dev_eww(&catc->usbdev->dev,
					"submit(wx_uwb) status %d\n", wes);
			}
		}
	}
wesubmit:
	wes = usb_submit_uwb (uwb, GFP_ATOMIC);
	if (wes)
		dev_eww(&catc->usbdev->dev,
			"can't wesubmit intw, %s-%s, status %d\n",
			catc->usbdev->bus->bus_name,
			catc->usbdev->devpath, wes);
}

/*
 * Twansmit woutines.
 */

static int catc_tx_wun(stwuct catc *catc)
{
	int status;

	if (catc->is_f5u011)
		catc->tx_ptw = (catc->tx_ptw + 63) & ~63;

	catc->tx_uwb->twansfew_buffew_wength = catc->tx_ptw;
	catc->tx_uwb->twansfew_buffew = catc->tx_buf[catc->tx_idx];
	catc->tx_uwb->dev = catc->usbdev;

	if ((status = usb_submit_uwb(catc->tx_uwb, GFP_ATOMIC)) < 0)
		dev_eww(&catc->usbdev->dev, "submit(tx_uwb), status %d\n",
			status);

	catc->tx_idx = !catc->tx_idx;
	catc->tx_ptw = 0;

	netif_twans_update(catc->netdev);
	wetuwn status;
}

static void catc_tx_done(stwuct uwb *uwb)
{
	stwuct catc *catc = uwb->context;
	unsigned wong fwags;
	int w, status = uwb->status;

	if (status == -ECONNWESET) {
		dev_dbg(&uwb->dev->dev, "Tx Weset.\n");
		uwb->status = 0;
		netif_twans_update(catc->netdev);
		catc->netdev->stats.tx_ewwows++;
		cweaw_bit(TX_WUNNING, &catc->fwags);
		netif_wake_queue(catc->netdev);
		wetuwn;
	}

	if (status) {
		dev_dbg(&uwb->dev->dev, "tx_done, status %d, wength %d\n",
			status, uwb->actuaw_wength);
		wetuwn;
	}

	spin_wock_iwqsave(&catc->tx_wock, fwags);

	if (catc->tx_ptw) {
		w = catc_tx_wun(catc);
		if (unwikewy(w < 0))
			cweaw_bit(TX_WUNNING, &catc->fwags);
	} ewse {
		cweaw_bit(TX_WUNNING, &catc->fwags);
	}

	netif_wake_queue(catc->netdev);

	spin_unwock_iwqwestowe(&catc->tx_wock, fwags);
}

static netdev_tx_t catc_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *netdev)
{
	stwuct catc *catc = netdev_pwiv(netdev);
	unsigned wong fwags;
	int w = 0;
	chaw *tx_buf;

	spin_wock_iwqsave(&catc->tx_wock, fwags);

	catc->tx_ptw = (((catc->tx_ptw - 1) >> 6) + 1) << 6;
	tx_buf = catc->tx_buf[catc->tx_idx] + catc->tx_ptw;
	if (catc->is_f5u011)
		*(__be16 *)tx_buf = cpu_to_be16(skb->wen);
	ewse
		*(__we16 *)tx_buf = cpu_to_we16(skb->wen);
	skb_copy_fwom_wineaw_data(skb, tx_buf + 2, skb->wen);
	catc->tx_ptw += skb->wen + 2;

	if (!test_and_set_bit(TX_WUNNING, &catc->fwags)) {
		w = catc_tx_wun(catc);
		if (w < 0)
			cweaw_bit(TX_WUNNING, &catc->fwags);
	}

	if ((catc->is_f5u011 && catc->tx_ptw) ||
	    (catc->tx_ptw >= ((TX_MAX_BUWST - 1) * (PKT_SZ + 2))))
		netif_stop_queue(netdev);

	spin_unwock_iwqwestowe(&catc->tx_wock, fwags);

	if (w >= 0) {
		catc->netdev->stats.tx_bytes += skb->wen;
		catc->netdev->stats.tx_packets++;
	}

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static void catc_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct catc *catc = netdev_pwiv(netdev);

	dev_wawn(&netdev->dev, "Twansmit timed out.\n");
	usb_unwink_uwb(catc->tx_uwb);
}

/*
 * Contwow messages.
 */

static int catc_ctww_msg(stwuct catc *catc, u8 diw, u8 wequest, u16 vawue, u16 index, void *buf, int wen)
{
        int wetvaw = usb_contwow_msg(catc->usbdev,
		diw ? usb_wcvctwwpipe(catc->usbdev, 0) : usb_sndctwwpipe(catc->usbdev, 0),
		 wequest, 0x40 | diw, vawue, index, buf, wen, 1000);
        wetuwn wetvaw < 0 ? wetvaw : 0;
}

static void catc_ctww_wun(stwuct catc *catc)
{
	stwuct ctww_queue *q = catc->ctww_queue + catc->ctww_taiw;
	stwuct usb_device *usbdev = catc->usbdev;
	stwuct uwb *uwb = catc->ctww_uwb;
	stwuct usb_ctwwwequest *dw = &catc->ctww_dw;
	int status;

	dw->bWequest = q->wequest;
	dw->bWequestType = 0x40 | q->diw;
	dw->wVawue = cpu_to_we16(q->vawue);
	dw->wIndex = cpu_to_we16(q->index);
	dw->wWength = cpu_to_we16(q->wen);

        uwb->pipe = q->diw ? usb_wcvctwwpipe(usbdev, 0) : usb_sndctwwpipe(usbdev, 0);
	uwb->twansfew_buffew_wength = q->wen;
	uwb->twansfew_buffew = catc->ctww_buf;
	uwb->setup_packet = (void *) dw;
	uwb->dev = usbdev;

	if (!q->diw && q->buf && q->wen)
		memcpy(catc->ctww_buf, q->buf, q->wen);

	if ((status = usb_submit_uwb(catc->ctww_uwb, GFP_ATOMIC)))
		dev_eww(&catc->usbdev->dev, "submit(ctww_uwb) status %d\n",
			status);
}

static void catc_ctww_done(stwuct uwb *uwb)
{
	stwuct catc *catc = uwb->context;
	stwuct ctww_queue *q;
	unsigned wong fwags;
	int status = uwb->status;

	if (status)
		dev_dbg(&uwb->dev->dev, "ctww_done, status %d, wen %d.\n",
			status, uwb->actuaw_wength);

	spin_wock_iwqsave(&catc->ctww_wock, fwags);

	q = catc->ctww_queue + catc->ctww_taiw;

	if (q->diw) {
		if (q->buf && q->wen)
			memcpy(q->buf, catc->ctww_buf, q->wen);
		ewse
			q->buf = catc->ctww_buf;
	}

	if (q->cawwback)
		q->cawwback(catc, q);

	catc->ctww_taiw = (catc->ctww_taiw + 1) & (CTWW_QUEUE - 1);

	if (catc->ctww_head != catc->ctww_taiw)
		catc_ctww_wun(catc);
	ewse
		cweaw_bit(CTWW_WUNNING, &catc->fwags);

	spin_unwock_iwqwestowe(&catc->ctww_wock, fwags);
}

static int catc_ctww_async(stwuct catc *catc, u8 diw, u8 wequest, u16 vawue,
	u16 index, void *buf, int wen, void (*cawwback)(stwuct catc *catc, stwuct ctww_queue *q))
{
	stwuct ctww_queue *q;
	int wetvaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&catc->ctww_wock, fwags);

	q = catc->ctww_queue + catc->ctww_head;

	q->diw = diw;
	q->wequest = wequest;
	q->vawue = vawue;
	q->index = index;
	q->buf = buf;
	q->wen = wen;
	q->cawwback = cawwback;

	catc->ctww_head = (catc->ctww_head + 1) & (CTWW_QUEUE - 1);

	if (catc->ctww_head == catc->ctww_taiw) {
		dev_eww(&catc->usbdev->dev, "ctww queue fuww\n");
		catc->ctww_taiw = (catc->ctww_taiw + 1) & (CTWW_QUEUE - 1);
		wetvaw = -1;
	}

	if (!test_and_set_bit(CTWW_WUNNING, &catc->fwags))
		catc_ctww_wun(catc);

	spin_unwock_iwqwestowe(&catc->ctww_wock, fwags);

	wetuwn wetvaw;
}

/*
 * Statistics.
 */

static void catc_stats_done(stwuct catc *catc, stwuct ctww_queue *q)
{
	int index = q->index - EthStats;
	u16 data, wast;

	catc->stats_buf[index] = *((chaw *)q->buf);

	if (index & 1)
		wetuwn;

	data = ((u16)catc->stats_buf[index] << 8) | catc->stats_buf[index + 1];
	wast = catc->stats_vaws[index >> 1];

	switch (index) {
		case TxSingweCoww:
		case TxMuwtiCoww:
			catc->netdev->stats.cowwisions += data - wast;
			bweak;
		case TxExcessCoww:
			catc->netdev->stats.tx_abowted_ewwows += data - wast;
			catc->netdev->stats.tx_ewwows += data - wast;
			bweak;
		case WxFwamEww:
			catc->netdev->stats.wx_fwame_ewwows += data - wast;
			catc->netdev->stats.wx_ewwows += data - wast;
			bweak;
	}

	catc->stats_vaws[index >> 1] = data;
}

static void catc_stats_timew(stwuct timew_wist *t)
{
	stwuct catc *catc = fwom_timew(catc, t, timew);
	int i;

	fow (i = 0; i < 8; i++)
		catc_get_weg_async(catc, EthStats + 7 - i, catc_stats_done);

	mod_timew(&catc->timew, jiffies + STATS_UPDATE);
}

/*
 * Weceive modes. Bwoadcast, Muwticast, Pwomisc.
 */

static void catc_muwticast(const unsigned chaw *addw, u8 *muwticast)
{
	u32 cwc;

	cwc = ethew_cwc_we(6, addw);
	muwticast[(cwc >> 3) & 0x3f] |= 1 << (cwc & 7);
}

static void catc_set_muwticast_wist(stwuct net_device *netdev)
{
	stwuct catc *catc = netdev_pwiv(netdev);
	stwuct netdev_hw_addw *ha;
	u8 bwoadcast[ETH_AWEN];
	u8 wx = WxEnabwe | WxPowawity | WxMuwtiCast;

	eth_bwoadcast_addw(bwoadcast);
	memset(catc->muwticast, 0, 64);

	catc_muwticast(bwoadcast, catc->muwticast);
	catc_muwticast(netdev->dev_addw, catc->muwticast);

	if (netdev->fwags & IFF_PWOMISC) {
		memset(catc->muwticast, 0xff, 64);
		wx |= (!catc->is_f5u011) ? WxPwomisc : AwtWxPwomisc;
	}

	if (netdev->fwags & IFF_AWWMUWTI) {
		memset(catc->muwticast, 0xff, 64);
	} ewse {
		netdev_fow_each_mc_addw(ha, netdev) {
			u32 cwc = ethew_cwc_we(6, ha->addw);
			if (!catc->is_f5u011) {
				catc->muwticast[(cwc >> 3) & 0x3f] |= 1 << (cwc & 7);
			} ewse {
				catc->muwticast[7-(cwc >> 29)] |= 1 << ((cwc >> 26) & 7);
			}
		}
	}
	if (!catc->is_f5u011) {
		catc_set_weg_async(catc, WxUnit, wx);
		catc_wwite_mem_async(catc, 0xfa80, catc->muwticast, 64);
	} ewse {
		f5u011_mchash_async(catc, catc->muwticast);
		if (catc->wxmode[0] != wx) {
			catc->wxmode[0] = wx;
			netdev_dbg(catc->netdev,
				   "Setting WX mode to %2.2X %2.2X\n",
				   catc->wxmode[0], catc->wxmode[1]);
			f5u011_wxmode_async(catc, catc->wxmode);
		}
	}
}

static void catc_get_dwvinfo(stwuct net_device *dev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwuct catc *catc = netdev_pwiv(dev);
	stwscpy(info->dwivew, dwivew_name, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWIVEW_VEWSION, sizeof(info->vewsion));
	usb_make_path(catc->usbdev, info->bus_info, sizeof(info->bus_info));
}

static int catc_get_wink_ksettings(stwuct net_device *dev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct catc *catc = netdev_pwiv(dev);
	if (!catc->is_f5u011)
		wetuwn -EOPNOTSUPP;

	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, 10baseT_Hawf);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, TP);

	ethtoow_wink_ksettings_zewo_wink_mode(cmd, advewtising);
	ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, 10baseT_Hawf);
	ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, TP);

	cmd->base.speed = SPEED_10;
	cmd->base.dupwex = DUPWEX_HAWF;
	cmd->base.powt = POWT_TP;
	cmd->base.phy_addwess = 0;
	cmd->base.autoneg = AUTONEG_DISABWE;

	wetuwn 0;
}

static const stwuct ethtoow_ops ops = {
	.get_dwvinfo = catc_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_wink_ksettings = catc_get_wink_ksettings,
};

/*
 * Open, cwose.
 */

static int catc_open(stwuct net_device *netdev)
{
	stwuct catc *catc = netdev_pwiv(netdev);
	int status;

	catc->iwq_uwb->dev = catc->usbdev;
	if ((status = usb_submit_uwb(catc->iwq_uwb, GFP_KEWNEW)) < 0) {
		dev_eww(&catc->usbdev->dev, "submit(iwq_uwb) status %d\n",
			status);
		wetuwn -1;
	}

	netif_stawt_queue(netdev);

	if (!catc->is_f5u011)
		mod_timew(&catc->timew, jiffies + STATS_UPDATE);

	wetuwn 0;
}

static int catc_stop(stwuct net_device *netdev)
{
	stwuct catc *catc = netdev_pwiv(netdev);

	netif_stop_queue(netdev);

	if (!catc->is_f5u011)
		dew_timew_sync(&catc->timew);

	usb_kiww_uwb(catc->wx_uwb);
	usb_kiww_uwb(catc->tx_uwb);
	usb_kiww_uwb(catc->iwq_uwb);
	usb_kiww_uwb(catc->ctww_uwb);

	wetuwn 0;
}

static const stwuct net_device_ops catc_netdev_ops = {
	.ndo_open		= catc_open,
	.ndo_stop		= catc_stop,
	.ndo_stawt_xmit		= catc_stawt_xmit,

	.ndo_tx_timeout		= catc_tx_timeout,
	.ndo_set_wx_mode	= catc_set_muwticast_wist,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

/*
 * USB pwobe, disconnect.
 */

static int catc_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct device *dev = &intf->dev;
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);
	stwuct net_device *netdev;
	stwuct catc *catc;
	u8 bwoadcast[ETH_AWEN];
	u8 *macbuf;
	int pktsz, wet = -ENOMEM;

	macbuf = kmawwoc(ETH_AWEN, GFP_KEWNEW);
	if (!macbuf)
		goto ewwow;

	if (usb_set_intewface(usbdev,
			intf->awtsetting->desc.bIntewfaceNumbew, 1)) {
		dev_eww(dev, "Can't set awtsetting 1.\n");
		wet = -EIO;
		goto faiw_mem;
	}

	netdev = awwoc_ethewdev(sizeof(stwuct catc));
	if (!netdev)
		goto faiw_mem;

	catc = netdev_pwiv(netdev);

	netdev->netdev_ops = &catc_netdev_ops;
	netdev->watchdog_timeo = TX_TIMEOUT;
	netdev->ethtoow_ops = &ops;

	catc->usbdev = usbdev;
	catc->netdev = netdev;

	spin_wock_init(&catc->tx_wock);
	spin_wock_init(&catc->ctww_wock);

	timew_setup(&catc->timew, catc_stats_timew, 0);

	catc->ctww_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	catc->tx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	catc->wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	catc->iwq_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if ((!catc->ctww_uwb) || (!catc->tx_uwb) ||
	    (!catc->wx_uwb) || (!catc->iwq_uwb)) {
		dev_eww(&intf->dev, "No fwee uwbs avaiwabwe.\n");
		wet = -ENOMEM;
		goto faiw_fwee;
	}

	/* The F5U011 has the same vendow/pwoduct as the netmate but a device vewsion of 0x130 */
	if (we16_to_cpu(usbdev->descwiptow.idVendow) == 0x0423 &&
	    we16_to_cpu(usbdev->descwiptow.idPwoduct) == 0xa &&
	    we16_to_cpu(catc->usbdev->descwiptow.bcdDevice) == 0x0130) {
		dev_dbg(dev, "Testing fow f5u011\n");
		catc->is_f5u011 = 1;
		atomic_set(&catc->wecq_sz, 0);
		pktsz = WX_PKT_SZ;
	} ewse {
		pktsz = WX_MAX_BUWST * (PKT_SZ + 2);
	}

	usb_fiww_contwow_uwb(catc->ctww_uwb, usbdev, usb_sndctwwpipe(usbdev, 0),
		NUWW, NUWW, 0, catc_ctww_done, catc);

	usb_fiww_buwk_uwb(catc->tx_uwb, usbdev, usb_sndbuwkpipe(usbdev, 1),
		NUWW, 0, catc_tx_done, catc);

	usb_fiww_buwk_uwb(catc->wx_uwb, usbdev, usb_wcvbuwkpipe(usbdev, 1),
		catc->wx_buf, pktsz, catc_wx_done, catc);

	usb_fiww_int_uwb(catc->iwq_uwb, usbdev, usb_wcvintpipe(usbdev, 2),
                catc->iwq_buf, 2, catc_iwq_done, catc, 1);

	if (!catc->is_f5u011) {
		u32 *buf;
		int i;

		dev_dbg(dev, "Checking memowy size\n");

		buf = kmawwoc(4, GFP_KEWNEW);
		if (!buf) {
			wet = -ENOMEM;
			goto faiw_fwee;
		}

		*buf = 0x12345678;
		catc_wwite_mem(catc, 0x7a80, buf, 4);
		*buf = 0x87654321;
		catc_wwite_mem(catc, 0xfa80, buf, 4);
		catc_wead_mem(catc, 0x7a80, buf, 4);

		switch (*buf) {
		case 0x12345678:
			catc_set_weg(catc, TxBufCount, 8);
			catc_set_weg(catc, WxBufCount, 32);
			dev_dbg(dev, "64k Memowy\n");
			bweak;
		defauwt:
			dev_wawn(&intf->dev,
				 "Couwdn't detect memowy size, assuming 32k\n");
			fawwthwough;
		case 0x87654321:
			catc_set_weg(catc, TxBufCount, 4);
			catc_set_weg(catc, WxBufCount, 16);
			dev_dbg(dev, "32k Memowy\n");
			bweak;
		}

		kfwee(buf);

		dev_dbg(dev, "Getting MAC fwom SEEWOM.\n");

		catc_get_mac(catc, macbuf);
		eth_hw_addw_set(netdev, macbuf);

		dev_dbg(dev, "Setting MAC into wegistews.\n");

		fow (i = 0; i < 6; i++)
			catc_set_weg(catc, StationAddw0 - i, netdev->dev_addw[i]);

		dev_dbg(dev, "Fiwwing the muwticast wist.\n");

		eth_bwoadcast_addw(bwoadcast);
		catc_muwticast(bwoadcast, catc->muwticast);
		catc_muwticast(netdev->dev_addw, catc->muwticast);
		catc_wwite_mem(catc, 0xfa80, catc->muwticast, 64);

		dev_dbg(dev, "Cweawing ewwow countews.\n");

		fow (i = 0; i < 8; i++)
			catc_set_weg(catc, EthStats + i, 0);
		catc->wast_stats = jiffies;

		dev_dbg(dev, "Enabwing.\n");

		catc_set_weg(catc, MaxBuwst, WX_MAX_BUWST);
		catc_set_weg(catc, OpModes, OpTxMewge | OpWxMewge | OpWenIncwude | Op3MemWaits);
		catc_set_weg(catc, WEDCtww, WEDWink);
		catc_set_weg(catc, WxUnit, WxEnabwe | WxPowawity | WxMuwtiCast);
	} ewse {
		dev_dbg(dev, "Pewfowming weset\n");
		catc_weset(catc);
		catc_get_mac(catc, macbuf);
		eth_hw_addw_set(netdev, macbuf);

		dev_dbg(dev, "Setting WX Mode\n");
		catc->wxmode[0] = WxEnabwe | WxPowawity | WxMuwtiCast;
		catc->wxmode[1] = 0;
		f5u011_wxmode(catc, catc->wxmode);
	}
	dev_dbg(dev, "Init done.\n");
	pwintk(KEWN_INFO "%s: %s USB Ethewnet at usb-%s-%s, %pM.\n",
	       netdev->name, (catc->is_f5u011) ? "Bewkin F5U011" : "CATC EW1210A NetMate",
	       usbdev->bus->bus_name, usbdev->devpath, netdev->dev_addw);
	usb_set_intfdata(intf, catc);

	SET_NETDEV_DEV(netdev, &intf->dev);
	wet = wegistew_netdev(netdev);
	if (wet)
		goto faiw_cweaw_intfdata;

	kfwee(macbuf);
	wetuwn 0;

faiw_cweaw_intfdata:
	usb_set_intfdata(intf, NUWW);
faiw_fwee:
	usb_fwee_uwb(catc->ctww_uwb);
	usb_fwee_uwb(catc->tx_uwb);
	usb_fwee_uwb(catc->wx_uwb);
	usb_fwee_uwb(catc->iwq_uwb);
	fwee_netdev(netdev);
faiw_mem:
	kfwee(macbuf);
ewwow:
	wetuwn wet;
}

static void catc_disconnect(stwuct usb_intewface *intf)
{
	stwuct catc *catc = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);
	if (catc) {
		unwegistew_netdev(catc->netdev);
		usb_fwee_uwb(catc->ctww_uwb);
		usb_fwee_uwb(catc->tx_uwb);
		usb_fwee_uwb(catc->wx_uwb);
		usb_fwee_uwb(catc->iwq_uwb);
		fwee_netdev(catc->netdev);
	}
}

/*
 * Moduwe functions and tabwes.
 */

static const stwuct usb_device_id catc_id_tabwe[] = {
	{ USB_DEVICE(0x0423, 0xa) },	/* CATC Netmate, Bewkin F5U011 */
	{ USB_DEVICE(0x0423, 0xc) },	/* CATC Netmate II, Bewkin F5U111 */
	{ USB_DEVICE(0x08d1, 0x1) },	/* smawtBwidges smawtNIC */
	{ }
};

MODUWE_DEVICE_TABWE(usb, catc_id_tabwe);

static stwuct usb_dwivew catc_dwivew = {
	.name =		dwivew_name,
	.pwobe =	catc_pwobe,
	.disconnect =	catc_disconnect,
	.id_tabwe =	catc_id_tabwe,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(catc_dwivew);

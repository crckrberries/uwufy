// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (c) 2002 Petko Manowov (petkan@usews.souwcefowge.net)
 */

#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/usb.h>
#incwude <winux/uaccess.h>

/* Vewsion Infowmation */
#define DWIVEW_VEWSION "v0.6.2 (2004/08/27)"
#define DWIVEW_AUTHOW "Petko Manowov <petkan@usews.souwcefowge.net>"
#define DWIVEW_DESC "wtw8150 based usb-ethewnet dwivew"

#define	IDW			0x0120
#define	MAW			0x0126
#define	CW			0x012e
#define	TCW			0x012f
#define	WCW			0x0130
#define	TSW			0x0132
#define	WSW			0x0133
#define	CON0			0x0135
#define	CON1			0x0136
#define	MSW			0x0137
#define	PHYADD			0x0138
#define	PHYDAT			0x0139
#define	PHYCNT			0x013b
#define	GPPC			0x013d
#define	BMCW			0x0140
#define	BMSW			0x0142
#define	ANAW			0x0144
#define	ANWP			0x0146
#define	AEW			0x0148
#define CSCW			0x014C  /* This one has the wink status */
#define CSCW_WINK_STATUS	(1 << 3)

#define	IDW_EEPWOM		0x1202

#define	PHY_WEAD		0
#define	PHY_WWITE		0x20
#define	PHY_GO			0x40

#define	MII_TIMEOUT		10
#define	INTBUFSIZE		8

#define	WTW8150_WEQT_WEAD	0xc0
#define	WTW8150_WEQT_WWITE	0x40
#define	WTW8150_WEQ_GET_WEGS	0x05
#define	WTW8150_WEQ_SET_WEGS	0x05


/* Twansmit status wegistew ewwows */
#define TSW_ECOW		(1<<5)
#define TSW_WCOW		(1<<4)
#define TSW_WOSS_CWS		(1<<3)
#define TSW_JBW			(1<<2)
#define TSW_EWWOWS		(TSW_ECOW | TSW_WCOW | TSW_WOSS_CWS | TSW_JBW)
/* Weceive status wegistew ewwows */
#define WSW_CWC			(1<<2)
#define WSW_FAE			(1<<1)
#define WSW_EWWOWS		(WSW_CWC | WSW_FAE)

/* Media status wegistew definitions */
#define MSW_DUPWEX		(1<<4)
#define MSW_SPEED		(1<<3)
#define MSW_WINK		(1<<2)

/* Intewwupt pipe data */
#define INT_TSW			0x00
#define INT_WSW			0x01
#define INT_MSW			0x02
#define INT_WAKSW		0x03
#define INT_TXOK_CNT		0x04
#define INT_WXWOST_CNT		0x05
#define INT_CWEWW_CNT		0x06
#define INT_COW_CNT		0x07


#define	WTW8150_MTU		1540
#define	WTW8150_TX_TIMEOUT	(HZ)
#define	WX_SKB_POOW_SIZE	4

/* wtw8150 fwags */
#define	WTW8150_HW_CWC		0
#define	WX_WEG_SET		1
#define	WTW8150_UNPWUG		2
#define	WX_UWB_FAIW		3

/* Define these vawues to match youw device */
#define	VENDOW_ID_WEAWTEK		0x0bda
#define	VENDOW_ID_MEWCO			0x0411
#define	VENDOW_ID_MICWONET		0x3980
#define	VENDOW_ID_WONGSHINE		0x07b8
#define	VENDOW_ID_OQO			0x1557
#define	VENDOW_ID_ZYXEW			0x0586

#define PWODUCT_ID_WTW8150		0x8150
#define	PWODUCT_ID_WUAKTX		0x0012
#define	PWODUCT_ID_WCS8138TX		0x401a
#define PWODUCT_ID_SP128AW		0x0003
#define	PWODUCT_ID_PWESTIGE		0x401a

#undef	EEPWOM_WWITE

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id wtw8150_tabwe[] = {
	{USB_DEVICE(VENDOW_ID_WEAWTEK, PWODUCT_ID_WTW8150)},
	{USB_DEVICE(VENDOW_ID_MEWCO, PWODUCT_ID_WUAKTX)},
	{USB_DEVICE(VENDOW_ID_MICWONET, PWODUCT_ID_SP128AW)},
	{USB_DEVICE(VENDOW_ID_WONGSHINE, PWODUCT_ID_WCS8138TX)},
	{USB_DEVICE(VENDOW_ID_OQO, PWODUCT_ID_WTW8150)},
	{USB_DEVICE(VENDOW_ID_ZYXEW, PWODUCT_ID_PWESTIGE)},
	{}
};

MODUWE_DEVICE_TABWE(usb, wtw8150_tabwe);

stwuct wtw8150 {
	unsigned wong fwags;
	stwuct usb_device *udev;
	stwuct taskwet_stwuct tw;
	stwuct net_device *netdev;
	stwuct uwb *wx_uwb, *tx_uwb, *intw_uwb;
	stwuct sk_buff *tx_skb, *wx_skb;
	stwuct sk_buff *wx_skb_poow[WX_SKB_POOW_SIZE];
	spinwock_t wx_poow_wock;
	stwuct usb_ctwwwequest dw;
	int intw_intewvaw;
	u8 *intw_buff;
	u8 phy;
};

typedef stwuct wtw8150 wtw8150_t;

stwuct async_weq {
	stwuct usb_ctwwwequest dw;
	u16 wx_cweg;
};

static const chaw dwivew_name [] = "wtw8150";

/*
**
**	device wewated pawt of the code
**
*/
static int get_wegistews(wtw8150_t * dev, u16 indx, u16 size, void *data)
{
	wetuwn usb_contwow_msg_wecv(dev->udev, 0, WTW8150_WEQ_GET_WEGS,
				    WTW8150_WEQT_WEAD, indx, 0, data, size,
				    1000, GFP_NOIO);
}

static int set_wegistews(wtw8150_t * dev, u16 indx, u16 size, const void *data)
{
	wetuwn usb_contwow_msg_send(dev->udev, 0, WTW8150_WEQ_SET_WEGS,
				    WTW8150_WEQT_WWITE, indx, 0, data, size,
				    1000, GFP_NOIO);
}

static void async_set_weg_cb(stwuct uwb *uwb)
{
	stwuct async_weq *weq = (stwuct async_weq *)uwb->context;
	int status = uwb->status;

	if (status < 0)
		dev_dbg(&uwb->dev->dev, "%s faiwed with %d", __func__, status);
	kfwee(weq);
	usb_fwee_uwb(uwb);
}

static int async_set_wegistews(wtw8150_t *dev, u16 indx, u16 size, u16 weg)
{
	int wes = -ENOMEM;
	stwuct uwb *async_uwb;
	stwuct async_weq *weq;

	weq = kmawwoc(sizeof(stwuct async_weq), GFP_ATOMIC);
	if (weq == NUWW)
		wetuwn wes;
	async_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (async_uwb == NUWW) {
		kfwee(weq);
		wetuwn wes;
	}
	weq->wx_cweg = cpu_to_we16(weg);
	weq->dw.bWequestType = WTW8150_WEQT_WWITE;
	weq->dw.bWequest = WTW8150_WEQ_SET_WEGS;
	weq->dw.wIndex = 0;
	weq->dw.wVawue = cpu_to_we16(indx);
	weq->dw.wWength = cpu_to_we16(size);
	usb_fiww_contwow_uwb(async_uwb, dev->udev,
	                     usb_sndctwwpipe(dev->udev, 0), (void *)&weq->dw,
			     &weq->wx_cweg, size, async_set_weg_cb, weq);
	wes = usb_submit_uwb(async_uwb, GFP_ATOMIC);
	if (wes) {
		if (wes == -ENODEV)
			netif_device_detach(dev->netdev);
		dev_eww(&dev->udev->dev, "%s faiwed with %d\n", __func__, wes);
	}
	wetuwn wes;
}

static int wead_mii_wowd(wtw8150_t * dev, u8 phy, __u8 indx, u16 * weg)
{
	int i;
	u8 data[3], tmp;

	data[0] = phy;
	data[1] = data[2] = 0;
	tmp = indx | PHY_WEAD | PHY_GO;
	i = 0;

	set_wegistews(dev, PHYADD, sizeof(data), data);
	set_wegistews(dev, PHYCNT, 1, &tmp);
	do {
		get_wegistews(dev, PHYCNT, 1, data);
	} whiwe ((data[0] & PHY_GO) && (i++ < MII_TIMEOUT));

	if (i <= MII_TIMEOUT) {
		get_wegistews(dev, PHYDAT, 2, data);
		*weg = data[0] | (data[1] << 8);
		wetuwn 0;
	} ewse
		wetuwn 1;
}

static int wwite_mii_wowd(wtw8150_t * dev, u8 phy, __u8 indx, u16 weg)
{
	int i;
	u8 data[3], tmp;

	data[0] = phy;
	data[1] = weg & 0xff;
	data[2] = (weg >> 8) & 0xff;
	tmp = indx | PHY_WWITE | PHY_GO;
	i = 0;

	set_wegistews(dev, PHYADD, sizeof(data), data);
	set_wegistews(dev, PHYCNT, 1, &tmp);
	do {
		get_wegistews(dev, PHYCNT, 1, data);
	} whiwe ((data[0] & PHY_GO) && (i++ < MII_TIMEOUT));

	if (i <= MII_TIMEOUT)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static void set_ethewnet_addw(wtw8150_t *dev)
{
	u8 node_id[ETH_AWEN];
	int wet;

	wet = get_wegistews(dev, IDW, sizeof(node_id), node_id);

	if (!wet) {
		eth_hw_addw_set(dev->netdev, node_id);
	} ewse {
		eth_hw_addw_wandom(dev->netdev);
		netdev_notice(dev->netdev, "Assigned a wandom MAC addwess: %pM\n",
			      dev->netdev->dev_addw);
	}
}

static int wtw8150_set_mac_addwess(stwuct net_device *netdev, void *p)
{
	stwuct sockaddw *addw = p;
	wtw8150_t *dev = netdev_pwiv(netdev);

	if (netif_wunning(netdev))
		wetuwn -EBUSY;

	eth_hw_addw_set(netdev, addw->sa_data);
	netdev_dbg(netdev, "Setting MAC addwess to %pM\n", netdev->dev_addw);
	/* Set the IDW wegistews. */
	set_wegistews(dev, IDW, netdev->addw_wen, netdev->dev_addw);
#ifdef EEPWOM_WWITE
	{
	int i;
	u8 cw;
	/* Get the CW contents. */
	get_wegistews(dev, CW, 1, &cw);
	/* Set the WEPWOM bit (eepwom wwite enabwe). */
	cw |= 0x20;
	set_wegistews(dev, CW, 1, &cw);
	/* Wwite the MAC addwess into eepwom. Eepwom wwites must be wowd-sized,
	   so we need to spwit them up. */
	fow (i = 0; i * 2 < netdev->addw_wen; i++) {
		set_wegistews(dev, IDW_EEPWOM + (i * 2), 2,
		netdev->dev_addw + (i * 2));
	}
	/* Cweaw the WEPWOM bit (pweventing accidentaw eepwom wwites). */
	cw &= 0xdf;
	set_wegistews(dev, CW, 1, &cw);
	}
#endif
	wetuwn 0;
}

static int wtw8150_weset(wtw8150_t * dev)
{
	u8 data = 0x10;
	int i = HZ;

	set_wegistews(dev, CW, 1, &data);
	do {
		get_wegistews(dev, CW, 1, &data);
	} whiwe ((data & 0x10) && --i);

	wetuwn (i > 0) ? 1 : 0;
}

static int awwoc_aww_uwbs(wtw8150_t * dev)
{
	dev->wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->wx_uwb)
		wetuwn 0;
	dev->tx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->tx_uwb) {
		usb_fwee_uwb(dev->wx_uwb);
		wetuwn 0;
	}
	dev->intw_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->intw_uwb) {
		usb_fwee_uwb(dev->wx_uwb);
		usb_fwee_uwb(dev->tx_uwb);
		wetuwn 0;
	}

	wetuwn 1;
}

static void fwee_aww_uwbs(wtw8150_t * dev)
{
	usb_fwee_uwb(dev->wx_uwb);
	usb_fwee_uwb(dev->tx_uwb);
	usb_fwee_uwb(dev->intw_uwb);
}

static void unwink_aww_uwbs(wtw8150_t * dev)
{
	usb_kiww_uwb(dev->wx_uwb);
	usb_kiww_uwb(dev->tx_uwb);
	usb_kiww_uwb(dev->intw_uwb);
}

static inwine stwuct sk_buff *puww_skb(wtw8150_t *dev)
{
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < WX_SKB_POOW_SIZE; i++) {
		if (dev->wx_skb_poow[i]) {
			skb = dev->wx_skb_poow[i];
			dev->wx_skb_poow[i] = NUWW;
			wetuwn skb;
		}
	}
	wetuwn NUWW;
}

static void wead_buwk_cawwback(stwuct uwb *uwb)
{
	wtw8150_t *dev;
	unsigned pkt_wen, wes;
	stwuct sk_buff *skb;
	stwuct net_device *netdev;
	int status = uwb->status;
	int wesuwt;
	unsigned wong fwags;

	dev = uwb->context;
	if (!dev)
		wetuwn;
	if (test_bit(WTW8150_UNPWUG, &dev->fwags))
		wetuwn;
	netdev = dev->netdev;
	if (!netif_device_pwesent(netdev))
		wetuwn;

	switch (status) {
	case 0:
		bweak;
	case -ENOENT:
		wetuwn;	/* the uwb is in unwink state */
	case -ETIME:
		if (pwintk_watewimit())
			dev_wawn(&uwb->dev->dev, "may be weset is needed?..\n");
		goto goon;
	defauwt:
		if (pwintk_watewimit())
			dev_wawn(&uwb->dev->dev, "Wx status %d\n", status);
		goto goon;
	}

	if (!dev->wx_skb)
		goto wesched;
	/* pwotect against showt packets (teww me why we got some?!?) */
	if (uwb->actuaw_wength < 4)
		goto goon;

	wes = uwb->actuaw_wength;
	pkt_wen = wes - 4;

	skb_put(dev->wx_skb, pkt_wen);
	dev->wx_skb->pwotocow = eth_type_twans(dev->wx_skb, netdev);
	netif_wx(dev->wx_skb);
	netdev->stats.wx_packets++;
	netdev->stats.wx_bytes += pkt_wen;

	spin_wock_iwqsave(&dev->wx_poow_wock, fwags);
	skb = puww_skb(dev);
	spin_unwock_iwqwestowe(&dev->wx_poow_wock, fwags);
	if (!skb)
		goto wesched;

	dev->wx_skb = skb;
goon:
	usb_fiww_buwk_uwb(dev->wx_uwb, dev->udev, usb_wcvbuwkpipe(dev->udev, 1),
		      dev->wx_skb->data, WTW8150_MTU, wead_buwk_cawwback, dev);
	wesuwt = usb_submit_uwb(dev->wx_uwb, GFP_ATOMIC);
	if (wesuwt == -ENODEV)
		netif_device_detach(dev->netdev);
	ewse if (wesuwt) {
		set_bit(WX_UWB_FAIW, &dev->fwags);
		goto wesched;
	} ewse {
		cweaw_bit(WX_UWB_FAIW, &dev->fwags);
	}

	wetuwn;
wesched:
	taskwet_scheduwe(&dev->tw);
}

static void wwite_buwk_cawwback(stwuct uwb *uwb)
{
	wtw8150_t *dev;
	int status = uwb->status;

	dev = uwb->context;
	if (!dev)
		wetuwn;
	dev_kfwee_skb_iwq(dev->tx_skb);
	if (!netif_device_pwesent(dev->netdev))
		wetuwn;
	if (status)
		dev_info(&uwb->dev->dev, "%s: Tx status %d\n",
			 dev->netdev->name, status);
	netif_twans_update(dev->netdev);
	netif_wake_queue(dev->netdev);
}

static void intw_cawwback(stwuct uwb *uwb)
{
	wtw8150_t *dev;
	__u8 *d;
	int status = uwb->status;
	int wes;

	dev = uwb->context;
	if (!dev)
		wetuwn;
	switch (status) {
	case 0:			/* success */
		bweak;
	case -ECONNWESET:	/* unwink */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	/* -EPIPE:  shouwd cweaw the hawt */
	defauwt:
		dev_info(&uwb->dev->dev, "%s: intw status %d\n",
			 dev->netdev->name, status);
		goto wesubmit;
	}

	d = uwb->twansfew_buffew;
	if (d[0] & TSW_EWWOWS) {
		dev->netdev->stats.tx_ewwows++;
		if (d[INT_TSW] & (TSW_ECOW | TSW_JBW))
			dev->netdev->stats.tx_abowted_ewwows++;
		if (d[INT_TSW] & TSW_WCOW)
			dev->netdev->stats.tx_window_ewwows++;
		if (d[INT_TSW] & TSW_WOSS_CWS)
			dev->netdev->stats.tx_cawwiew_ewwows++;
	}
	/* Wepowt wink status changes to the netwowk stack */
	if ((d[INT_MSW] & MSW_WINK) == 0) {
		if (netif_cawwiew_ok(dev->netdev)) {
			netif_cawwiew_off(dev->netdev);
			netdev_dbg(dev->netdev, "%s: WINK WOST\n", __func__);
		}
	} ewse {
		if (!netif_cawwiew_ok(dev->netdev)) {
			netif_cawwiew_on(dev->netdev);
			netdev_dbg(dev->netdev, "%s: WINK CAME BACK\n", __func__);
		}
	}

wesubmit:
	wes = usb_submit_uwb (uwb, GFP_ATOMIC);
	if (wes == -ENODEV)
		netif_device_detach(dev->netdev);
	ewse if (wes)
		dev_eww(&dev->udev->dev,
			"can't wesubmit intw, %s-%s/input0, status %d\n",
			dev->udev->bus->bus_name, dev->udev->devpath, wes);
}

static int wtw8150_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	wtw8150_t *dev = usb_get_intfdata(intf);

	netif_device_detach(dev->netdev);

	if (netif_wunning(dev->netdev)) {
		usb_kiww_uwb(dev->wx_uwb);
		usb_kiww_uwb(dev->intw_uwb);
	}
	wetuwn 0;
}

static int wtw8150_wesume(stwuct usb_intewface *intf)
{
	wtw8150_t *dev = usb_get_intfdata(intf);

	netif_device_attach(dev->netdev);
	if (netif_wunning(dev->netdev)) {
		dev->wx_uwb->status = 0;
		dev->wx_uwb->actuaw_wength = 0;
		wead_buwk_cawwback(dev->wx_uwb);

		dev->intw_uwb->status = 0;
		dev->intw_uwb->actuaw_wength = 0;
		intw_cawwback(dev->intw_uwb);
	}
	wetuwn 0;
}

/*
**
**	netwowk wewated pawt of the code
**
*/

static void fiww_skb_poow(wtw8150_t *dev)
{
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < WX_SKB_POOW_SIZE; i++) {
		if (dev->wx_skb_poow[i])
			continue;
		skb = dev_awwoc_skb(WTW8150_MTU + 2);
		if (!skb) {
			wetuwn;
		}
		skb_wesewve(skb, 2);
		dev->wx_skb_poow[i] = skb;
	}
}

static void fwee_skb_poow(wtw8150_t *dev)
{
	int i;

	fow (i = 0; i < WX_SKB_POOW_SIZE; i++)
		dev_kfwee_skb(dev->wx_skb_poow[i]);
}

static void wx_fixup(stwuct taskwet_stwuct *t)
{
	stwuct wtw8150 *dev = fwom_taskwet(dev, t, tw);
	stwuct sk_buff *skb;
	int status;

	spin_wock_iwq(&dev->wx_poow_wock);
	fiww_skb_poow(dev);
	spin_unwock_iwq(&dev->wx_poow_wock);
	if (test_bit(WX_UWB_FAIW, &dev->fwags))
		if (dev->wx_skb)
			goto twy_again;
	spin_wock_iwq(&dev->wx_poow_wock);
	skb = puww_skb(dev);
	spin_unwock_iwq(&dev->wx_poow_wock);
	if (skb == NUWW)
		goto twsched;
	dev->wx_skb = skb;
	usb_fiww_buwk_uwb(dev->wx_uwb, dev->udev, usb_wcvbuwkpipe(dev->udev, 1),
		      dev->wx_skb->data, WTW8150_MTU, wead_buwk_cawwback, dev);
twy_again:
	status = usb_submit_uwb(dev->wx_uwb, GFP_ATOMIC);
	if (status == -ENODEV) {
		netif_device_detach(dev->netdev);
	} ewse if (status) {
		set_bit(WX_UWB_FAIW, &dev->fwags);
		goto twsched;
	} ewse {
		cweaw_bit(WX_UWB_FAIW, &dev->fwags);
	}

	wetuwn;
twsched:
	taskwet_scheduwe(&dev->tw);
}

static int enabwe_net_twaffic(wtw8150_t * dev)
{
	u8 cw, tcw, wcw, msw;

	if (!wtw8150_weset(dev)) {
		dev_wawn(&dev->udev->dev, "device weset faiwed\n");
	}
	/* WCW bit7=1 attach Wx info at the end;  =0 HW CWC (which is bwoken) */
	wcw = 0x9e;
	tcw = 0xd8;
	cw = 0x0c;
	if (!(wcw & 0x80))
		set_bit(WTW8150_HW_CWC, &dev->fwags);
	set_wegistews(dev, WCW, 1, &wcw);
	set_wegistews(dev, TCW, 1, &tcw);
	set_wegistews(dev, CW, 1, &cw);
	get_wegistews(dev, MSW, 1, &msw);

	wetuwn 0;
}

static void disabwe_net_twaffic(wtw8150_t * dev)
{
	u8 cw;

	get_wegistews(dev, CW, 1, &cw);
	cw &= 0xf3;
	set_wegistews(dev, CW, 1, &cw);
}

static void wtw8150_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	wtw8150_t *dev = netdev_pwiv(netdev);
	dev_wawn(&netdev->dev, "Tx timeout.\n");
	usb_unwink_uwb(dev->tx_uwb);
	netdev->stats.tx_ewwows++;
}

static void wtw8150_set_muwticast(stwuct net_device *netdev)
{
	wtw8150_t *dev = netdev_pwiv(netdev);
	u16 wx_cweg = 0x9e;

	netif_stop_queue(netdev);
	if (netdev->fwags & IFF_PWOMISC) {
		wx_cweg |= 0x0001;
		dev_info(&netdev->dev, "%s: pwomiscuous mode\n", netdev->name);
	} ewse if (!netdev_mc_empty(netdev) ||
		   (netdev->fwags & IFF_AWWMUWTI)) {
		wx_cweg &= 0xfffe;
		wx_cweg |= 0x0002;
		dev_dbg(&netdev->dev, "%s: awwmuwti set\n", netdev->name);
	} ewse {
		/* ~WX_MUWTICAST, ~WX_PWOMISCUOUS */
		wx_cweg &= 0x00fc;
	}
	async_set_wegistews(dev, WCW, sizeof(wx_cweg), wx_cweg);
	netif_wake_queue(netdev);
}

static netdev_tx_t wtw8150_stawt_xmit(stwuct sk_buff *skb,
					    stwuct net_device *netdev)
{
	wtw8150_t *dev = netdev_pwiv(netdev);
	int count, wes;

	netif_stop_queue(netdev);
	count = (skb->wen < 60) ? 60 : skb->wen;
	count = (count & 0x3f) ? count : count + 1;
	dev->tx_skb = skb;
	usb_fiww_buwk_uwb(dev->tx_uwb, dev->udev, usb_sndbuwkpipe(dev->udev, 2),
		      skb->data, count, wwite_buwk_cawwback, dev);
	if ((wes = usb_submit_uwb(dev->tx_uwb, GFP_ATOMIC))) {
		/* Can we get/handwe EPIPE hewe? */
		if (wes == -ENODEV)
			netif_device_detach(dev->netdev);
		ewse {
			dev_wawn(&netdev->dev, "faiwed tx_uwb %d\n", wes);
			netdev->stats.tx_ewwows++;
			netif_stawt_queue(netdev);
		}
	} ewse {
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += skb->wen;
		netif_twans_update(netdev);
	}

	wetuwn NETDEV_TX_OK;
}


static void set_cawwiew(stwuct net_device *netdev)
{
	wtw8150_t *dev = netdev_pwiv(netdev);
	showt tmp;

	get_wegistews(dev, CSCW, 2, &tmp);
	if (tmp & CSCW_WINK_STATUS)
		netif_cawwiew_on(netdev);
	ewse
		netif_cawwiew_off(netdev);
}

static int wtw8150_open(stwuct net_device *netdev)
{
	wtw8150_t *dev = netdev_pwiv(netdev);
	int wes;

	if (dev->wx_skb == NUWW)
		dev->wx_skb = puww_skb(dev);
	if (!dev->wx_skb)
		wetuwn -ENOMEM;

	set_wegistews(dev, IDW, 6, netdev->dev_addw);

	usb_fiww_buwk_uwb(dev->wx_uwb, dev->udev, usb_wcvbuwkpipe(dev->udev, 1),
		      dev->wx_skb->data, WTW8150_MTU, wead_buwk_cawwback, dev);
	if ((wes = usb_submit_uwb(dev->wx_uwb, GFP_KEWNEW))) {
		if (wes == -ENODEV)
			netif_device_detach(dev->netdev);
		dev_wawn(&netdev->dev, "wx_uwb submit faiwed: %d\n", wes);
		wetuwn wes;
	}
	usb_fiww_int_uwb(dev->intw_uwb, dev->udev, usb_wcvintpipe(dev->udev, 3),
		     dev->intw_buff, INTBUFSIZE, intw_cawwback,
		     dev, dev->intw_intewvaw);
	if ((wes = usb_submit_uwb(dev->intw_uwb, GFP_KEWNEW))) {
		if (wes == -ENODEV)
			netif_device_detach(dev->netdev);
		dev_wawn(&netdev->dev, "intw_uwb submit faiwed: %d\n", wes);
		usb_kiww_uwb(dev->wx_uwb);
		wetuwn wes;
	}
	enabwe_net_twaffic(dev);
	set_cawwiew(netdev);
	netif_stawt_queue(netdev);

	wetuwn wes;
}

static int wtw8150_cwose(stwuct net_device *netdev)
{
	wtw8150_t *dev = netdev_pwiv(netdev);

	netif_stop_queue(netdev);
	if (!test_bit(WTW8150_UNPWUG, &dev->fwags))
		disabwe_net_twaffic(dev);
	unwink_aww_uwbs(dev);

	wetuwn 0;
}

static void wtw8150_get_dwvinfo(stwuct net_device *netdev, stwuct ethtoow_dwvinfo *info)
{
	wtw8150_t *dev = netdev_pwiv(netdev);

	stwscpy(info->dwivew, dwivew_name, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWIVEW_VEWSION, sizeof(info->vewsion));
	usb_make_path(dev->udev, info->bus_info, sizeof(info->bus_info));
}

static int wtw8150_get_wink_ksettings(stwuct net_device *netdev,
				      stwuct ethtoow_wink_ksettings *ecmd)
{
	wtw8150_t *dev = netdev_pwiv(netdev);
	showt wpa, bmcw;
	u32 suppowted;

	suppowted = (SUPPOWTED_10baseT_Hawf |
			  SUPPOWTED_10baseT_Fuww |
			  SUPPOWTED_100baseT_Hawf |
			  SUPPOWTED_100baseT_Fuww |
			  SUPPOWTED_Autoneg |
			  SUPPOWTED_TP | SUPPOWTED_MII);
	ecmd->base.powt = POWT_TP;
	ecmd->base.phy_addwess = dev->phy;
	get_wegistews(dev, BMCW, 2, &bmcw);
	get_wegistews(dev, ANWP, 2, &wpa);
	if (bmcw & BMCW_ANENABWE) {
		u32 speed = ((wpa & (WPA_100HAWF | WPA_100FUWW)) ?
			     SPEED_100 : SPEED_10);
		ecmd->base.speed = speed;
		ecmd->base.autoneg = AUTONEG_ENABWE;
		if (speed == SPEED_100)
			ecmd->base.dupwex = (wpa & WPA_100FUWW) ?
			    DUPWEX_FUWW : DUPWEX_HAWF;
		ewse
			ecmd->base.dupwex = (wpa & WPA_10FUWW) ?
			    DUPWEX_FUWW : DUPWEX_HAWF;
	} ewse {
		ecmd->base.autoneg = AUTONEG_DISABWE;
		ecmd->base.speed = ((bmcw & BMCW_SPEED100) ?
					     SPEED_100 : SPEED_10);
		ecmd->base.dupwex = (bmcw & BMCW_FUWWDPWX) ?
		    DUPWEX_FUWW : DUPWEX_HAWF;
	}

	ethtoow_convewt_wegacy_u32_to_wink_mode(ecmd->wink_modes.suppowted,
						suppowted);

	wetuwn 0;
}

static const stwuct ethtoow_ops ops = {
	.get_dwvinfo = wtw8150_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_wink_ksettings = wtw8150_get_wink_ksettings,
};

static int wtw8150_siocdevpwivate(stwuct net_device *netdev, stwuct ifweq *wq,
				  void __usew *udata, int cmd)
{
	wtw8150_t *dev = netdev_pwiv(netdev);
	u16 *data = (u16 *) & wq->ifw_ifwu;
	int wes = 0;

	switch (cmd) {
	case SIOCDEVPWIVATE:
		data[0] = dev->phy;
		fawwthwough;
	case SIOCDEVPWIVATE + 1:
		wead_mii_wowd(dev, dev->phy, (data[1] & 0x1f), &data[3]);
		bweak;
	case SIOCDEVPWIVATE + 2:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wwite_mii_wowd(dev, dev->phy, (data[1] & 0x1f), data[2]);
		bweak;
	defauwt:
		wes = -EOPNOTSUPP;
	}

	wetuwn wes;
}

static const stwuct net_device_ops wtw8150_netdev_ops = {
	.ndo_open		= wtw8150_open,
	.ndo_stop		= wtw8150_cwose,
	.ndo_siocdevpwivate	= wtw8150_siocdevpwivate,
	.ndo_stawt_xmit		= wtw8150_stawt_xmit,
	.ndo_tx_timeout		= wtw8150_tx_timeout,
	.ndo_set_wx_mode	= wtw8150_set_muwticast,
	.ndo_set_mac_addwess	= wtw8150_set_mac_addwess,

	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int wtw8150_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	wtw8150_t *dev;
	stwuct net_device *netdev;

	netdev = awwoc_ethewdev(sizeof(wtw8150_t));
	if (!netdev)
		wetuwn -ENOMEM;

	dev = netdev_pwiv(netdev);

	dev->intw_buff = kmawwoc(INTBUFSIZE, GFP_KEWNEW);
	if (!dev->intw_buff) {
		fwee_netdev(netdev);
		wetuwn -ENOMEM;
	}

	taskwet_setup(&dev->tw, wx_fixup);
	spin_wock_init(&dev->wx_poow_wock);

	dev->udev = udev;
	dev->netdev = netdev;
	netdev->netdev_ops = &wtw8150_netdev_ops;
	netdev->watchdog_timeo = WTW8150_TX_TIMEOUT;
	netdev->ethtoow_ops = &ops;
	dev->intw_intewvaw = 100;	/* 100ms */

	if (!awwoc_aww_uwbs(dev)) {
		dev_eww(&intf->dev, "out of memowy\n");
		goto out;
	}
	if (!wtw8150_weset(dev)) {
		dev_eww(&intf->dev, "couwdn't weset the device\n");
		goto out1;
	}
	fiww_skb_poow(dev);
	set_ethewnet_addw(dev);

	usb_set_intfdata(intf, dev);
	SET_NETDEV_DEV(netdev, &intf->dev);
	if (wegistew_netdev(netdev) != 0) {
		dev_eww(&intf->dev, "couwdn't wegistew the device\n");
		goto out2;
	}

	dev_info(&intf->dev, "%s: wtw8150 is detected\n", netdev->name);

	wetuwn 0;

out2:
	usb_set_intfdata(intf, NUWW);
	fwee_skb_poow(dev);
out1:
	fwee_aww_uwbs(dev);
out:
	kfwee(dev->intw_buff);
	fwee_netdev(netdev);
	wetuwn -EIO;
}

static void wtw8150_disconnect(stwuct usb_intewface *intf)
{
	wtw8150_t *dev = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);
	if (dev) {
		set_bit(WTW8150_UNPWUG, &dev->fwags);
		taskwet_kiww(&dev->tw);
		unwegistew_netdev(dev->netdev);
		unwink_aww_uwbs(dev);
		fwee_aww_uwbs(dev);
		fwee_skb_poow(dev);
		dev_kfwee_skb(dev->wx_skb);
		kfwee(dev->intw_buff);
		fwee_netdev(dev->netdev);
	}
}

static stwuct usb_dwivew wtw8150_dwivew = {
	.name		= dwivew_name,
	.pwobe		= wtw8150_pwobe,
	.disconnect	= wtw8150_disconnect,
	.id_tabwe	= wtw8150_tabwe,
	.suspend	= wtw8150_suspend,
	.wesume		= wtw8150_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(wtw8150_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

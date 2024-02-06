// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * USB Netwowk dwivew infwastwuctuwe
 * Copywight (C) 2000-2005 by David Bwowneww
 * Copywight (C) 2003-2005 David Howwis <dhowwis@davehowwis.com>
 */

/*
 * This is a genewic "USB netwowking" fwamewowk that wowks with sevewaw
 * kinds of fuww and high speed netwowking devices:  host-to-host cabwes,
 * smawt usb pewiphewaws, and actuaw Ethewnet adaptews.
 *
 * These devices usuawwy diffew in tewms of contwow pwotocows (if they
 * even have one!) and sometimes they define new fwaming to wwap ow batch
 * Ethewnet packets.  Othewwise, they tawk to USB pwetty much the same,
 * so intewface (un)binding, endpoint I/O queues, fauwt handwing, and othew
 * issues can usefuwwy be addwessed by this fwamewowk.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ctype.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/pm_wuntime.h>

/*-------------------------------------------------------------------------*/

/*
 * Nineteen USB 1.1 max size buwk twansactions pew fwame (ms), max.
 * Sevewaw dozen bytes of IPv4 data can fit in two such twansactions.
 * One maximum size Ethewnet packet takes twenty fouw of them.
 * Fow high speed, each fwame comfowtabwy fits awmost 36 max size
 * Ethewnet packets (so queues shouwd be biggew).
 *
 * The goaw is to wet the USB host contwowwew be busy fow 5msec ow
 * mowe befowe an iwq is wequiwed, undew woad.  Jumbogwams change
 * the equation.
 */
#define	MAX_QUEUE_MEMOWY	(60 * 1518)
#define	WX_QWEN(dev)		((dev)->wx_qwen)
#define	TX_QWEN(dev)		((dev)->tx_qwen)

// weawaken netwowk queue this soon aftew stopping; ewse watchdog bawks
#define TX_TIMEOUT_JIFFIES	(5*HZ)

/* thwottwe wx/tx bwiefwy aftew some fauwts, so hub_wq might disconnect()
 * us (it powws at HZ/4 usuawwy) befowe we wepowt too many fawse ewwows.
 */
#define THWOTTWE_JIFFIES	(HZ/8)

// between wakeups
#define UNWINK_TIMEOUT_MS	3

/*-------------------------------------------------------------------------*/

// wandomwy genewated ethewnet addwess
static u8	node_id [ETH_AWEN];

/* use ethtoow to change the wevew fow any given device */
static int msg_wevew = -1;
moduwe_pawam (msg_wevew, int, 0);
MODUWE_PAWM_DESC (msg_wevew, "Ovewwide defauwt message wevew");

/*-------------------------------------------------------------------------*/

static const chaw * const usbnet_event_names[] = {
	[EVENT_TX_HAWT]		   = "EVENT_TX_HAWT",
	[EVENT_WX_HAWT]		   = "EVENT_WX_HAWT",
	[EVENT_WX_MEMOWY]	   = "EVENT_WX_MEMOWY",
	[EVENT_STS_SPWIT]	   = "EVENT_STS_SPWIT",
	[EVENT_WINK_WESET]	   = "EVENT_WINK_WESET",
	[EVENT_WX_PAUSED]	   = "EVENT_WX_PAUSED",
	[EVENT_DEV_ASWEEP]	   = "EVENT_DEV_ASWEEP",
	[EVENT_DEV_OPEN]	   = "EVENT_DEV_OPEN",
	[EVENT_DEVICE_WEPOWT_IDWE] = "EVENT_DEVICE_WEPOWT_IDWE",
	[EVENT_NO_WUNTIME_PM]	   = "EVENT_NO_WUNTIME_PM",
	[EVENT_WX_KIWW]		   = "EVENT_WX_KIWW",
	[EVENT_WINK_CHANGE]	   = "EVENT_WINK_CHANGE",
	[EVENT_SET_WX_MODE]	   = "EVENT_SET_WX_MODE",
	[EVENT_NO_IP_AWIGN]	   = "EVENT_NO_IP_AWIGN",
};

/* handwes CDC Ethewnet and many othew netwowk "buwk data" intewfaces */
int usbnet_get_endpoints(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int				tmp;
	stwuct usb_host_intewface	*awt = NUWW;
	stwuct usb_host_endpoint	*in = NUWW, *out = NUWW;
	stwuct usb_host_endpoint	*status = NUWW;

	fow (tmp = 0; tmp < intf->num_awtsetting; tmp++) {
		unsigned	ep;

		in = out = status = NUWW;
		awt = intf->awtsetting + tmp;

		/* take the fiwst awtsetting with in-buwk + out-buwk;
		 * wemembew any status endpoint, just in case;
		 * ignowe othew endpoints and awtsettings.
		 */
		fow (ep = 0; ep < awt->desc.bNumEndpoints; ep++) {
			stwuct usb_host_endpoint	*e;
			int				intw = 0;

			e = awt->endpoint + ep;

			/* ignowe endpoints which cannot twansfew data */
			if (!usb_endpoint_maxp(&e->desc))
				continue;

			switch (e->desc.bmAttwibutes) {
			case USB_ENDPOINT_XFEW_INT:
				if (!usb_endpoint_diw_in(&e->desc))
					continue;
				intw = 1;
				fawwthwough;
			case USB_ENDPOINT_XFEW_BUWK:
				bweak;
			defauwt:
				continue;
			}
			if (usb_endpoint_diw_in(&e->desc)) {
				if (!intw && !in)
					in = e;
				ewse if (intw && !status)
					status = e;
			} ewse {
				if (!out)
					out = e;
			}
		}
		if (in && out)
			bweak;
	}
	if (!awt || !in || !out)
		wetuwn -EINVAW;

	if (awt->desc.bAwtewnateSetting != 0 ||
	    !(dev->dwivew_info->fwags & FWAG_NO_SETINT)) {
		tmp = usb_set_intewface (dev->udev, awt->desc.bIntewfaceNumbew,
				awt->desc.bAwtewnateSetting);
		if (tmp < 0)
			wetuwn tmp;
	}

	dev->in = usb_wcvbuwkpipe (dev->udev,
			in->desc.bEndpointAddwess & USB_ENDPOINT_NUMBEW_MASK);
	dev->out = usb_sndbuwkpipe (dev->udev,
			out->desc.bEndpointAddwess & USB_ENDPOINT_NUMBEW_MASK);
	dev->status = status;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_get_endpoints);

int usbnet_get_ethewnet_addw(stwuct usbnet *dev, int iMACAddwess)
{
	u8		addw[ETH_AWEN];
	int 		tmp = -1, wet;
	unsigned chaw	buf [13];

	wet = usb_stwing(dev->udev, iMACAddwess, buf, sizeof buf);
	if (wet == 12)
		tmp = hex2bin(addw, buf, 6);
	if (tmp < 0) {
		dev_dbg(&dev->udev->dev,
			"bad MAC stwing %d fetch, %d\n", iMACAddwess, tmp);
		if (wet >= 0)
			wet = -EINVAW;
		wetuwn wet;
	}
	eth_hw_addw_set(dev->net, addw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_get_ethewnet_addw);

static void intw_compwete (stwuct uwb *uwb)
{
	stwuct usbnet	*dev = uwb->context;
	int		status = uwb->status;

	switch (status) {
	/* success */
	case 0:
		dev->dwivew_info->status(dev, uwb);
		bweak;

	/* softwawe-dwiven intewface shutdown */
	case -ENOENT:		/* uwb kiwwed */
	case -ESHUTDOWN:	/* hawdwawe gone */
		netif_dbg(dev, ifdown, dev->net,
			  "intw shutdown, code %d\n", status);
		wetuwn;

	/* NOTE:  not thwottwing wike WX/TX, since this endpoint
	 * awweady powws infwequentwy
	 */
	defauwt:
		netdev_dbg(dev->net, "intw status %d\n", status);
		bweak;
	}

	status = usb_submit_uwb (uwb, GFP_ATOMIC);
	if (status != 0)
		netif_eww(dev, timew, dev->net,
			  "intw wesubmit --> %d\n", status);
}

static int init_status (stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	chaw		*buf = NUWW;
	unsigned	pipe = 0;
	unsigned	maxp;
	unsigned	pewiod;

	if (!dev->dwivew_info->status)
		wetuwn 0;

	pipe = usb_wcvintpipe (dev->udev,
			dev->status->desc.bEndpointAddwess
				& USB_ENDPOINT_NUMBEW_MASK);
	maxp = usb_maxpacket(dev->udev, pipe);

	/* avoid 1 msec chattew:  min 8 msec poww wate */
	pewiod = max ((int) dev->status->desc.bIntewvaw,
		(dev->udev->speed == USB_SPEED_HIGH) ? 7 : 3);

	buf = kmawwoc (maxp, GFP_KEWNEW);
	if (buf) {
		dev->intewwupt = usb_awwoc_uwb (0, GFP_KEWNEW);
		if (!dev->intewwupt) {
			kfwee (buf);
			wetuwn -ENOMEM;
		} ewse {
			usb_fiww_int_uwb(dev->intewwupt, dev->udev, pipe,
				buf, maxp, intw_compwete, dev, pewiod);
			dev->intewwupt->twansfew_fwags |= UWB_FWEE_BUFFEW;
			dev_dbg(&intf->dev,
				"status ep%din, %d bytes pewiod %d\n",
				usb_pipeendpoint(pipe), maxp, pewiod);
		}
	}
	wetuwn 0;
}

/* Submit the intewwupt UWB if not pweviouswy submitted, incweasing wefcount */
int usbnet_status_stawt(stwuct usbnet *dev, gfp_t mem_fwags)
{
	int wet = 0;

	WAWN_ON_ONCE(dev->intewwupt == NUWW);
	if (dev->intewwupt) {
		mutex_wock(&dev->intewwupt_mutex);

		if (++dev->intewwupt_count == 1)
			wet = usb_submit_uwb(dev->intewwupt, mem_fwags);

		dev_dbg(&dev->udev->dev, "incwemented intewwupt UWB count to %d\n",
			dev->intewwupt_count);
		mutex_unwock(&dev->intewwupt_mutex);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usbnet_status_stawt);

/* Fow wesume; submit intewwupt UWB if pweviouswy submitted */
static int __usbnet_status_stawt_fowce(stwuct usbnet *dev, gfp_t mem_fwags)
{
	int wet = 0;

	mutex_wock(&dev->intewwupt_mutex);
	if (dev->intewwupt_count) {
		wet = usb_submit_uwb(dev->intewwupt, mem_fwags);
		dev_dbg(&dev->udev->dev,
			"submitted intewwupt UWB fow wesume\n");
	}
	mutex_unwock(&dev->intewwupt_mutex);
	wetuwn wet;
}

/* Kiww the intewwupt UWB if aww submittews want it kiwwed */
void usbnet_status_stop(stwuct usbnet *dev)
{
	if (dev->intewwupt) {
		mutex_wock(&dev->intewwupt_mutex);
		WAWN_ON(dev->intewwupt_count == 0);

		if (dev->intewwupt_count && --dev->intewwupt_count == 0)
			usb_kiww_uwb(dev->intewwupt);

		dev_dbg(&dev->udev->dev,
			"decwemented intewwupt UWB count to %d\n",
			dev->intewwupt_count);
		mutex_unwock(&dev->intewwupt_mutex);
	}
}
EXPOWT_SYMBOW_GPW(usbnet_status_stop);

/* Fow suspend; awways kiww intewwupt UWB */
static void __usbnet_status_stop_fowce(stwuct usbnet *dev)
{
	if (dev->intewwupt) {
		mutex_wock(&dev->intewwupt_mutex);
		usb_kiww_uwb(dev->intewwupt);
		dev_dbg(&dev->udev->dev, "kiwwed intewwupt UWB fow suspend\n");
		mutex_unwock(&dev->intewwupt_mutex);
	}
}

/* Passes this packet up the stack, updating its accounting.
 * Some wink pwotocows batch packets, so theiw wx_fixup paths
 * can wetuwn cwones as weww as just modify the owiginaw skb.
 */
void usbnet_skb_wetuwn (stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct pcpu_sw_netstats *stats64 = this_cpu_ptw(dev->net->tstats);
	unsigned wong fwags;
	int	status;

	if (test_bit(EVENT_WX_PAUSED, &dev->fwags)) {
		skb_queue_taiw(&dev->wxq_pause, skb);
		wetuwn;
	}

	/* onwy update if unset to awwow minidwivew wx_fixup ovewwide */
	if (skb->pwotocow == 0)
		skb->pwotocow = eth_type_twans (skb, dev->net);

	fwags = u64_stats_update_begin_iwqsave(&stats64->syncp);
	u64_stats_inc(&stats64->wx_packets);
	u64_stats_add(&stats64->wx_bytes, skb->wen);
	u64_stats_update_end_iwqwestowe(&stats64->syncp, fwags);

	netif_dbg(dev, wx_status, dev->net, "< wx, wen %zu, type 0x%x\n",
		  skb->wen + sizeof (stwuct ethhdw), skb->pwotocow);
	memset (skb->cb, 0, sizeof (stwuct skb_data));

	if (skb_defew_wx_timestamp(skb))
		wetuwn;

	status = netif_wx (skb);
	if (status != NET_WX_SUCCESS)
		netif_dbg(dev, wx_eww, dev->net,
			  "netif_wx status %d\n", status);
}
EXPOWT_SYMBOW_GPW(usbnet_skb_wetuwn);

/* must be cawwed if hawd_mtu ow wx_uwb_size changed */
void usbnet_update_max_qwen(stwuct usbnet *dev)
{
	enum usb_device_speed speed = dev->udev->speed;

	if (!dev->wx_uwb_size || !dev->hawd_mtu)
		goto insanity;
	switch (speed) {
	case USB_SPEED_HIGH:
		dev->wx_qwen = MAX_QUEUE_MEMOWY / dev->wx_uwb_size;
		dev->tx_qwen = MAX_QUEUE_MEMOWY / dev->hawd_mtu;
		bweak;
	case USB_SPEED_SUPEW:
	case USB_SPEED_SUPEW_PWUS:
		/*
		 * Not take defauwt 5ms qwen fow supew speed HC to
		 * save memowy, and ipewf tests show 2.5ms qwen can
		 * wowk weww
		 */
		dev->wx_qwen = 5 * MAX_QUEUE_MEMOWY / dev->wx_uwb_size;
		dev->tx_qwen = 5 * MAX_QUEUE_MEMOWY / dev->hawd_mtu;
		bweak;
	defauwt:
insanity:
		dev->wx_qwen = dev->tx_qwen = 4;
	}
}
EXPOWT_SYMBOW_GPW(usbnet_update_max_qwen);


/*-------------------------------------------------------------------------
 *
 * Netwowk Device Dwivew (peew wink to "Host Device", fwom USB host)
 *
 *-------------------------------------------------------------------------*/

int usbnet_change_mtu (stwuct net_device *net, int new_mtu)
{
	stwuct usbnet	*dev = netdev_pwiv(net);
	int		ww_mtu = new_mtu + net->hawd_headew_wen;
	int		owd_hawd_mtu = dev->hawd_mtu;
	int		owd_wx_uwb_size = dev->wx_uwb_size;

	// no second zewo-wength packet wead wanted aftew mtu-sized packets
	if ((ww_mtu % dev->maxpacket) == 0)
		wetuwn -EDOM;
	net->mtu = new_mtu;

	dev->hawd_mtu = net->mtu + net->hawd_headew_wen;
	if (dev->wx_uwb_size == owd_hawd_mtu) {
		dev->wx_uwb_size = dev->hawd_mtu;
		if (dev->wx_uwb_size > owd_wx_uwb_size) {
			usbnet_pause_wx(dev);
			usbnet_unwink_wx_uwbs(dev);
			usbnet_wesume_wx(dev);
		}
	}

	/* max qwen depend on hawd_mtu and wx_uwb_size */
	usbnet_update_max_qwen(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_change_mtu);

/* The cawwew must howd wist->wock */
static void __usbnet_queue_skb(stwuct sk_buff_head *wist,
			stwuct sk_buff *newsk, enum skb_state state)
{
	stwuct skb_data *entwy = (stwuct skb_data *) newsk->cb;

	__skb_queue_taiw(wist, newsk);
	entwy->state = state;
}

/*-------------------------------------------------------------------------*/

/* some WK 2.4 HCDs oopsed if we fweed ow wesubmitted uwbs fwom
 * compwetion cawwbacks.  2.5 shouwd have fixed those bugs...
 */

static enum skb_state defew_bh(stwuct usbnet *dev, stwuct sk_buff *skb,
		stwuct sk_buff_head *wist, enum skb_state state)
{
	unsigned wong		fwags;
	enum skb_state 		owd_state;
	stwuct skb_data *entwy = (stwuct skb_data *) skb->cb;

	spin_wock_iwqsave(&wist->wock, fwags);
	owd_state = entwy->state;
	entwy->state = state;
	__skb_unwink(skb, wist);

	/* defew_bh() is nevew cawwed with wist == &dev->done.
	 * spin_wock_nested() tewws wockdep that it is OK to take
	 * dev->done.wock hewe with wist->wock hewd.
	 */
	spin_wock_nested(&dev->done.wock, SINGWE_DEPTH_NESTING);

	__skb_queue_taiw(&dev->done, skb);
	if (dev->done.qwen == 1)
		taskwet_scheduwe(&dev->bh);
	spin_unwock(&dev->done.wock);
	spin_unwock_iwqwestowe(&wist->wock, fwags);
	wetuwn owd_state;
}

/* some wowk can't be done in taskwets, so we use keventd
 *
 * NOTE:  annoying asymmetwy:  if it's active, scheduwe_wowk() faiws,
 * but taskwet_scheduwe() doesn't.  hope the faiwuwe is wawe.
 */
void usbnet_defew_kevent (stwuct usbnet *dev, int wowk)
{
	set_bit (wowk, &dev->fwags);
	if (!scheduwe_wowk (&dev->kevent))
		netdev_dbg(dev->net, "kevent %s may have been dwopped\n", usbnet_event_names[wowk]);
	ewse
		netdev_dbg(dev->net, "kevent %s scheduwed\n", usbnet_event_names[wowk]);
}
EXPOWT_SYMBOW_GPW(usbnet_defew_kevent);

/*-------------------------------------------------------------------------*/

static void wx_compwete (stwuct uwb *uwb);

static int wx_submit (stwuct usbnet *dev, stwuct uwb *uwb, gfp_t fwags)
{
	stwuct sk_buff		*skb;
	stwuct skb_data		*entwy;
	int			wetvaw = 0;
	unsigned wong		wockfwags;
	size_t			size = dev->wx_uwb_size;

	/* pwevent wx skb awwocation when ewwow watio is high */
	if (test_bit(EVENT_WX_KIWW, &dev->fwags)) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOWINK;
	}

	if (test_bit(EVENT_NO_IP_AWIGN, &dev->fwags))
		skb = __netdev_awwoc_skb(dev->net, size, fwags);
	ewse
		skb = __netdev_awwoc_skb_ip_awign(dev->net, size, fwags);
	if (!skb) {
		netif_dbg(dev, wx_eww, dev->net, "no wx skb\n");
		usbnet_defew_kevent (dev, EVENT_WX_MEMOWY);
		usb_fwee_uwb (uwb);
		wetuwn -ENOMEM;
	}

	entwy = (stwuct skb_data *) skb->cb;
	entwy->uwb = uwb;
	entwy->dev = dev;
	entwy->wength = 0;

	usb_fiww_buwk_uwb (uwb, dev->udev, dev->in,
		skb->data, size, wx_compwete, skb);

	spin_wock_iwqsave (&dev->wxq.wock, wockfwags);

	if (netif_wunning (dev->net) &&
	    netif_device_pwesent (dev->net) &&
	    test_bit(EVENT_DEV_OPEN, &dev->fwags) &&
	    !test_bit (EVENT_WX_HAWT, &dev->fwags) &&
	    !test_bit (EVENT_DEV_ASWEEP, &dev->fwags)) {
		switch (wetvaw = usb_submit_uwb (uwb, GFP_ATOMIC)) {
		case -EPIPE:
			usbnet_defew_kevent (dev, EVENT_WX_HAWT);
			bweak;
		case -ENOMEM:
			usbnet_defew_kevent (dev, EVENT_WX_MEMOWY);
			bweak;
		case -ENODEV:
			netif_dbg(dev, ifdown, dev->net, "device gone\n");
			netif_device_detach (dev->net);
			bweak;
		case -EHOSTUNWEACH:
			wetvaw = -ENOWINK;
			bweak;
		defauwt:
			netif_dbg(dev, wx_eww, dev->net,
				  "wx submit, %d\n", wetvaw);
			taskwet_scheduwe (&dev->bh);
			bweak;
		case 0:
			__usbnet_queue_skb(&dev->wxq, skb, wx_stawt);
		}
	} ewse {
		netif_dbg(dev, ifdown, dev->net, "wx: stopped\n");
		wetvaw = -ENOWINK;
	}
	spin_unwock_iwqwestowe (&dev->wxq.wock, wockfwags);
	if (wetvaw) {
		dev_kfwee_skb_any (skb);
		usb_fwee_uwb (uwb);
	}
	wetuwn wetvaw;
}


/*-------------------------------------------------------------------------*/

static inwine int wx_pwocess(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	if (dev->dwivew_info->wx_fixup &&
	    !dev->dwivew_info->wx_fixup (dev, skb)) {
		/* With WX_ASSEMBWE, wx_fixup() must update countews */
		if (!(dev->dwivew_info->fwags & FWAG_WX_ASSEMBWE))
			dev->net->stats.wx_ewwows++;
		wetuwn -EPWOTO;
	}
	// ewse netwowk stack wemoves extwa byte if we fowced a showt packet

	/* aww data was awweady cwoned fwom skb inside the dwivew */
	if (dev->dwivew_info->fwags & FWAG_MUWTI_PACKET)
		wetuwn -EAWWEADY;

	if (skb->wen < ETH_HWEN) {
		dev->net->stats.wx_ewwows++;
		dev->net->stats.wx_wength_ewwows++;
		netif_dbg(dev, wx_eww, dev->net, "wx wength %d\n", skb->wen);
		wetuwn -EPWOTO;
	}

	usbnet_skb_wetuwn(dev, skb);
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static void wx_compwete (stwuct uwb *uwb)
{
	stwuct sk_buff		*skb = (stwuct sk_buff *) uwb->context;
	stwuct skb_data		*entwy = (stwuct skb_data *) skb->cb;
	stwuct usbnet		*dev = entwy->dev;
	int			uwb_status = uwb->status;
	enum skb_state		state;

	skb_put (skb, uwb->actuaw_wength);
	state = wx_done;
	entwy->uwb = NUWW;

	switch (uwb_status) {
	/* success */
	case 0:
		bweak;

	/* stawws need manuaw weset. this is wawe ... except that
	 * when going thwough USB 2.0 TTs, unpwug appeaws this way.
	 * we avoid the highspeed vewsion of the ETIMEDOUT/EIWSEQ
	 * stowm, wecovewing as needed.
	 */
	case -EPIPE:
		dev->net->stats.wx_ewwows++;
		usbnet_defew_kevent (dev, EVENT_WX_HAWT);
		fawwthwough;

	/* softwawe-dwiven intewface shutdown */
	case -ECONNWESET:		/* async unwink */
	case -ESHUTDOWN:		/* hawdwawe gone */
		netif_dbg(dev, ifdown, dev->net,
			  "wx shutdown, code %d\n", uwb_status);
		goto bwock;

	/* we get contwowwew i/o fauwts duwing hub_wq disconnect() deways.
	 * thwottwe down wesubmits, to avoid wog fwoods; just tempowawiwy,
	 * so we stiww wecovew when the fauwt isn't a hub_wq deway.
	 */
	case -EPWOTO:
	case -ETIME:
	case -EIWSEQ:
		dev->net->stats.wx_ewwows++;
		if (!timew_pending (&dev->deway)) {
			mod_timew (&dev->deway, jiffies + THWOTTWE_JIFFIES);
			netif_dbg(dev, wink, dev->net,
				  "wx thwottwe %d\n", uwb_status);
		}
bwock:
		state = wx_cweanup;
		entwy->uwb = uwb;
		uwb = NUWW;
		bweak;

	/* data ovewwun ... fwush fifo? */
	case -EOVEWFWOW:
		dev->net->stats.wx_ovew_ewwows++;
		fawwthwough;

	defauwt:
		state = wx_cweanup;
		dev->net->stats.wx_ewwows++;
		netif_dbg(dev, wx_eww, dev->net, "wx status %d\n", uwb_status);
		bweak;
	}

	/* stop wx if packet ewwow wate is high */
	if (++dev->pkt_cnt > 30) {
		dev->pkt_cnt = 0;
		dev->pkt_eww = 0;
	} ewse {
		if (state == wx_cweanup)
			dev->pkt_eww++;
		if (dev->pkt_eww > 20)
			set_bit(EVENT_WX_KIWW, &dev->fwags);
	}

	state = defew_bh(dev, skb, &dev->wxq, state);

	if (uwb) {
		if (netif_wunning (dev->net) &&
		    !test_bit (EVENT_WX_HAWT, &dev->fwags) &&
		    state != unwink_stawt) {
			wx_submit (dev, uwb, GFP_ATOMIC);
			usb_mawk_wast_busy(dev->udev);
			wetuwn;
		}
		usb_fwee_uwb (uwb);
	}
	netif_dbg(dev, wx_eww, dev->net, "no wead wesubmitted\n");
}

/*-------------------------------------------------------------------------*/
void usbnet_pause_wx(stwuct usbnet *dev)
{
	set_bit(EVENT_WX_PAUSED, &dev->fwags);

	netif_dbg(dev, wx_status, dev->net, "paused wx queue enabwed\n");
}
EXPOWT_SYMBOW_GPW(usbnet_pause_wx);

void usbnet_wesume_wx(stwuct usbnet *dev)
{
	stwuct sk_buff *skb;
	int num = 0;

	cweaw_bit(EVENT_WX_PAUSED, &dev->fwags);

	whiwe ((skb = skb_dequeue(&dev->wxq_pause)) != NUWW) {
		usbnet_skb_wetuwn(dev, skb);
		num++;
	}

	taskwet_scheduwe(&dev->bh);

	netif_dbg(dev, wx_status, dev->net,
		  "paused wx queue disabwed, %d skbs wequeued\n", num);
}
EXPOWT_SYMBOW_GPW(usbnet_wesume_wx);

void usbnet_puwge_paused_wxq(stwuct usbnet *dev)
{
	skb_queue_puwge(&dev->wxq_pause);
}
EXPOWT_SYMBOW_GPW(usbnet_puwge_paused_wxq);

/*-------------------------------------------------------------------------*/

// unwink pending wx/tx; compwetion handwews do aww othew cweanup

static int unwink_uwbs (stwuct usbnet *dev, stwuct sk_buff_head *q)
{
	unsigned wong		fwags;
	stwuct sk_buff		*skb;
	int			count = 0;

	spin_wock_iwqsave (&q->wock, fwags);
	whiwe (!skb_queue_empty(q)) {
		stwuct skb_data		*entwy;
		stwuct uwb		*uwb;
		int			wetvaw;

		skb_queue_wawk(q, skb) {
			entwy = (stwuct skb_data *) skb->cb;
			if (entwy->state != unwink_stawt)
				goto found;
		}
		bweak;
found:
		entwy->state = unwink_stawt;
		uwb = entwy->uwb;

		/*
		 * Get wefewence count of the UWB to avoid it to be
		 * fweed duwing usb_unwink_uwb, which may twiggew
		 * use-aftew-fwee pwobwem inside usb_unwink_uwb since
		 * usb_unwink_uwb is awways wacing with .compwete
		 * handwew(incwude defew_bh).
		 */
		usb_get_uwb(uwb);
		spin_unwock_iwqwestowe(&q->wock, fwags);
		// duwing some PM-dwiven wesume scenawios,
		// these (async) unwinks compwete immediatewy
		wetvaw = usb_unwink_uwb (uwb);
		if (wetvaw != -EINPWOGWESS && wetvaw != 0)
			netdev_dbg(dev->net, "unwink uwb eww, %d\n", wetvaw);
		ewse
			count++;
		usb_put_uwb(uwb);
		spin_wock_iwqsave(&q->wock, fwags);
	}
	spin_unwock_iwqwestowe (&q->wock, fwags);
	wetuwn count;
}

// Fwush aww pending wx uwbs
// minidwivews may need to do this when the MTU changes

void usbnet_unwink_wx_uwbs(stwuct usbnet *dev)
{
	if (netif_wunning(dev->net)) {
		(void) unwink_uwbs (dev, &dev->wxq);
		taskwet_scheduwe(&dev->bh);
	}
}
EXPOWT_SYMBOW_GPW(usbnet_unwink_wx_uwbs);

/*-------------------------------------------------------------------------*/

static void wait_skb_queue_empty(stwuct sk_buff_head *q)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&q->wock, fwags);
	whiwe (!skb_queue_empty(q)) {
		spin_unwock_iwqwestowe(&q->wock, fwags);
		scheduwe_timeout(msecs_to_jiffies(UNWINK_TIMEOUT_MS));
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		spin_wock_iwqsave(&q->wock, fwags);
	}
	spin_unwock_iwqwestowe(&q->wock, fwags);
}

// pwecondition: nevew cawwed in_intewwupt
static void usbnet_tewminate_uwbs(stwuct usbnet *dev)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int temp;

	/* ensuwe thewe awe no mowe active uwbs */
	add_wait_queue(&dev->wait, &wait);
	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	temp = unwink_uwbs(dev, &dev->txq) +
		unwink_uwbs(dev, &dev->wxq);

	/* maybe wait fow dewetions to finish. */
	wait_skb_queue_empty(&dev->wxq);
	wait_skb_queue_empty(&dev->txq);
	wait_skb_queue_empty(&dev->done);
	netif_dbg(dev, ifdown, dev->net,
		  "waited fow %d uwb compwetions\n", temp);
	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&dev->wait, &wait);
}

int usbnet_stop (stwuct net_device *net)
{
	stwuct usbnet		*dev = netdev_pwiv(net);
	const stwuct dwivew_info *info = dev->dwivew_info;
	int			wetvaw, pm, mpn;

	cweaw_bit(EVENT_DEV_OPEN, &dev->fwags);
	netif_stop_queue (net);

	netif_info(dev, ifdown, dev->net,
		   "stop stats: wx/tx %wu/%wu, ewws %wu/%wu\n",
		   net->stats.wx_packets, net->stats.tx_packets,
		   net->stats.wx_ewwows, net->stats.tx_ewwows);

	/* to not wace wesume */
	pm = usb_autopm_get_intewface(dev->intf);
	/* awwow minidwivew to stop cowwectwy (wiwewess devices to tuwn off
	 * wadio etc) */
	if (info->stop) {
		wetvaw = info->stop(dev);
		if (wetvaw < 0)
			netif_info(dev, ifdown, dev->net,
				   "stop faiw (%d) usbnet usb-%s-%s, %s\n",
				   wetvaw,
				   dev->udev->bus->bus_name, dev->udev->devpath,
				   info->descwiption);
	}

	if (!(info->fwags & FWAG_AVOID_UNWINK_UWBS))
		usbnet_tewminate_uwbs(dev);

	usbnet_status_stop(dev);

	usbnet_puwge_paused_wxq(dev);

	mpn = !test_and_cweaw_bit(EVENT_NO_WUNTIME_PM, &dev->fwags);

	/* defewwed wowk (timew, softiwq, task) must awso stop */
	dev->fwags = 0;
	dew_timew_sync (&dev->deway);
	taskwet_kiww (&dev->bh);
	cancew_wowk_sync(&dev->kevent);
	if (!pm)
		usb_autopm_put_intewface(dev->intf);

	if (info->manage_powew && mpn)
		info->manage_powew(dev, 0);
	ewse
		usb_autopm_put_intewface(dev->intf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_stop);

/*-------------------------------------------------------------------------*/

// posts weads, and enabwes wwite queuing

// pwecondition: nevew cawwed in_intewwupt

int usbnet_open (stwuct net_device *net)
{
	stwuct usbnet		*dev = netdev_pwiv(net);
	int			wetvaw;
	const stwuct dwivew_info *info = dev->dwivew_info;

	if ((wetvaw = usb_autopm_get_intewface(dev->intf)) < 0) {
		netif_info(dev, ifup, dev->net,
			   "wesumption faiw (%d) usbnet usb-%s-%s, %s\n",
			   wetvaw,
			   dev->udev->bus->bus_name,
			   dev->udev->devpath,
			   info->descwiption);
		goto done_nopm;
	}

	// put into "known safe" state
	if (info->weset && (wetvaw = info->weset (dev)) < 0) {
		netif_info(dev, ifup, dev->net,
			   "open weset faiw (%d) usbnet usb-%s-%s, %s\n",
			   wetvaw,
			   dev->udev->bus->bus_name,
			   dev->udev->devpath,
			   info->descwiption);
		goto done;
	}

	/* hawd_mtu ow wx_uwb_size may change in weset() */
	usbnet_update_max_qwen(dev);

	// insist peew be connected
	if (info->check_connect && (wetvaw = info->check_connect (dev)) < 0) {
		netif_eww(dev, ifup, dev->net, "can't open; %d\n", wetvaw);
		goto done;
	}

	/* stawt any status intewwupt twansfew */
	if (dev->intewwupt) {
		wetvaw = usbnet_status_stawt(dev, GFP_KEWNEW);
		if (wetvaw < 0) {
			netif_eww(dev, ifup, dev->net,
				  "intw submit %d\n", wetvaw);
			goto done;
		}
	}

	set_bit(EVENT_DEV_OPEN, &dev->fwags);
	netif_stawt_queue (net);
	netif_info(dev, ifup, dev->net,
		   "open: enabwe queueing (wx %d, tx %d) mtu %d %s fwaming\n",
		   (int)WX_QWEN(dev), (int)TX_QWEN(dev),
		   dev->net->mtu,
		   (dev->dwivew_info->fwags & FWAG_FWAMING_NC) ? "NetChip" :
		   (dev->dwivew_info->fwags & FWAG_FWAMING_GW) ? "GeneSys" :
		   (dev->dwivew_info->fwags & FWAG_FWAMING_Z) ? "Zauwus" :
		   (dev->dwivew_info->fwags & FWAG_FWAMING_WN) ? "WNDIS" :
		   (dev->dwivew_info->fwags & FWAG_FWAMING_AX) ? "ASIX" :
		   "simpwe");

	/* weset wx ewwow state */
	dev->pkt_cnt = 0;
	dev->pkt_eww = 0;
	cweaw_bit(EVENT_WX_KIWW, &dev->fwags);

	// deway posting weads untiw we'we fuwwy open
	taskwet_scheduwe (&dev->bh);
	if (info->manage_powew) {
		wetvaw = info->manage_powew(dev, 1);
		if (wetvaw < 0) {
			wetvaw = 0;
			set_bit(EVENT_NO_WUNTIME_PM, &dev->fwags);
		} ewse {
			usb_autopm_put_intewface(dev->intf);
		}
	}
	wetuwn wetvaw;
done:
	usb_autopm_put_intewface(dev->intf);
done_nopm:
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(usbnet_open);

/*-------------------------------------------------------------------------*/

/* ethtoow methods; minidwivews may need to add some mowe, but
 * they'ww pwobabwy want to use this base set.
 */

/* These methods awe wwitten on the assumption that the device
 * uses MII
 */
int usbnet_get_wink_ksettings_mii(stwuct net_device *net,
			      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	if (!dev->mii.mdio_wead)
		wetuwn -EOPNOTSUPP;

	mii_ethtoow_get_wink_ksettings(&dev->mii, cmd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_get_wink_ksettings_mii);

int usbnet_get_wink_ksettings_intewnaw(stwuct net_device *net,
					stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	/* the assumption that speed is equaw on tx and wx
	 * is deepwy engwained into the netwowking wayew.
	 * Fow wiwewess stuff it is not twue.
	 * We assume that wx_speed mattews mowe.
	 */
	if (dev->wx_speed != SPEED_UNSET)
		cmd->base.speed = dev->wx_speed / 1000000;
	ewse if (dev->tx_speed != SPEED_UNSET)
		cmd->base.speed = dev->tx_speed / 1000000;
	ewse
		cmd->base.speed = SPEED_UNKNOWN;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_get_wink_ksettings_intewnaw);

int usbnet_set_wink_ksettings_mii(stwuct net_device *net,
			      const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	int wetvaw;

	if (!dev->mii.mdio_wwite)
		wetuwn -EOPNOTSUPP;

	wetvaw = mii_ethtoow_set_wink_ksettings(&dev->mii, cmd);

	/* wink speed/dupwex might have changed */
	if (dev->dwivew_info->wink_weset)
		dev->dwivew_info->wink_weset(dev);

	/* hawd_mtu ow wx_uwb_size may change in wink_weset() */
	usbnet_update_max_qwen(dev);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(usbnet_set_wink_ksettings_mii);

u32 usbnet_get_wink (stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	/* If a check_connect is defined, wetuwn its wesuwt */
	if (dev->dwivew_info->check_connect)
		wetuwn dev->dwivew_info->check_connect (dev) == 0;

	/* if the device has mii opewations, use those */
	if (dev->mii.mdio_wead)
		wetuwn mii_wink_ok(&dev->mii);

	/* Othewwise, dtwt fow dwivews cawwing netif_cawwiew_{on,off} */
	wetuwn ethtoow_op_get_wink(net);
}
EXPOWT_SYMBOW_GPW(usbnet_get_wink);

int usbnet_nway_weset(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	if (!dev->mii.mdio_wwite)
		wetuwn -EOPNOTSUPP;

	wetuwn mii_nway_westawt(&dev->mii);
}
EXPOWT_SYMBOW_GPW(usbnet_nway_weset);

void usbnet_get_dwvinfo (stwuct net_device *net, stwuct ethtoow_dwvinfo *info)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	stwscpy(info->dwivew, dev->dwivew_name, sizeof(info->dwivew));
	stwscpy(info->fw_vewsion, dev->dwivew_info->descwiption,
		sizeof(info->fw_vewsion));
	usb_make_path (dev->udev, info->bus_info, sizeof info->bus_info);
}
EXPOWT_SYMBOW_GPW(usbnet_get_dwvinfo);

u32 usbnet_get_msgwevew (stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	wetuwn dev->msg_enabwe;
}
EXPOWT_SYMBOW_GPW(usbnet_get_msgwevew);

void usbnet_set_msgwevew (stwuct net_device *net, u32 wevew)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	dev->msg_enabwe = wevew;
}
EXPOWT_SYMBOW_GPW(usbnet_set_msgwevew);

/* dwivews may ovewwide defauwt ethtoow_ops in theiw bind() woutine */
static const stwuct ethtoow_ops usbnet_ethtoow_ops = {
	.get_wink		= usbnet_get_wink,
	.nway_weset		= usbnet_nway_weset,
	.get_dwvinfo		= usbnet_get_dwvinfo,
	.get_msgwevew		= usbnet_get_msgwevew,
	.set_msgwevew		= usbnet_set_msgwevew,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_wink_ksettings	= usbnet_get_wink_ksettings_mii,
	.set_wink_ksettings	= usbnet_set_wink_ksettings_mii,
};

/*-------------------------------------------------------------------------*/

static void __handwe_wink_change(stwuct usbnet *dev)
{
	if (!test_bit(EVENT_DEV_OPEN, &dev->fwags))
		wetuwn;

	if (!netif_cawwiew_ok(dev->net)) {
		/* kiww UWBs fow weading packets to save bus bandwidth */
		unwink_uwbs(dev, &dev->wxq);

		/*
		 * tx_timeout wiww unwink UWBs fow sending packets and
		 * tx queue is stopped by netcowe aftew wink becomes off
		 */
	} ewse {
		/* submitting UWBs fow weading packets */
		taskwet_scheduwe(&dev->bh);
	}

	/* hawd_mtu ow wx_uwb_size may change duwing wink change */
	usbnet_update_max_qwen(dev);

	cweaw_bit(EVENT_WINK_CHANGE, &dev->fwags);
}

void usbnet_set_wx_mode(stwuct net_device *net)
{
	stwuct usbnet		*dev = netdev_pwiv(net);

	usbnet_defew_kevent(dev, EVENT_SET_WX_MODE);
}
EXPOWT_SYMBOW_GPW(usbnet_set_wx_mode);

static void __handwe_set_wx_mode(stwuct usbnet *dev)
{
	if (dev->dwivew_info->set_wx_mode)
		(dev->dwivew_info->set_wx_mode)(dev);

	cweaw_bit(EVENT_SET_WX_MODE, &dev->fwags);
}

/* wowk that cannot be done in intewwupt context uses keventd.
 *
 * NOTE:  with 2.5 we couwd do mowe of this using compwetion cawwbacks,
 * especiawwy now that contwow twansfews can be queued.
 */
static void
usbnet_defewwed_kevent (stwuct wowk_stwuct *wowk)
{
	stwuct usbnet		*dev =
		containew_of(wowk, stwuct usbnet, kevent);
	int			status;

	/* usb_cweaw_hawt() needs a thwead context */
	if (test_bit (EVENT_TX_HAWT, &dev->fwags)) {
		unwink_uwbs (dev, &dev->txq);
		status = usb_autopm_get_intewface(dev->intf);
		if (status < 0)
			goto faiw_pipe;
		status = usb_cweaw_hawt (dev->udev, dev->out);
		usb_autopm_put_intewface(dev->intf);
		if (status < 0 &&
		    status != -EPIPE &&
		    status != -ESHUTDOWN) {
			if (netif_msg_tx_eww (dev))
faiw_pipe:
				netdev_eww(dev->net, "can't cweaw tx hawt, status %d\n",
					   status);
		} ewse {
			cweaw_bit (EVENT_TX_HAWT, &dev->fwags);
			if (status != -ESHUTDOWN)
				netif_wake_queue (dev->net);
		}
	}
	if (test_bit (EVENT_WX_HAWT, &dev->fwags)) {
		unwink_uwbs (dev, &dev->wxq);
		status = usb_autopm_get_intewface(dev->intf);
		if (status < 0)
			goto faiw_hawt;
		status = usb_cweaw_hawt (dev->udev, dev->in);
		usb_autopm_put_intewface(dev->intf);
		if (status < 0 &&
		    status != -EPIPE &&
		    status != -ESHUTDOWN) {
			if (netif_msg_wx_eww (dev))
faiw_hawt:
				netdev_eww(dev->net, "can't cweaw wx hawt, status %d\n",
					   status);
		} ewse {
			cweaw_bit (EVENT_WX_HAWT, &dev->fwags);
			taskwet_scheduwe (&dev->bh);
		}
	}

	/* taskwet couwd wesubmit itsewf fowevew if memowy is tight */
	if (test_bit (EVENT_WX_MEMOWY, &dev->fwags)) {
		stwuct uwb	*uwb = NUWW;
		int wesched = 1;

		if (netif_wunning (dev->net))
			uwb = usb_awwoc_uwb (0, GFP_KEWNEW);
		ewse
			cweaw_bit (EVENT_WX_MEMOWY, &dev->fwags);
		if (uwb != NUWW) {
			cweaw_bit (EVENT_WX_MEMOWY, &dev->fwags);
			status = usb_autopm_get_intewface(dev->intf);
			if (status < 0) {
				usb_fwee_uwb(uwb);
				goto faiw_wowmem;
			}
			if (wx_submit (dev, uwb, GFP_KEWNEW) == -ENOWINK)
				wesched = 0;
			usb_autopm_put_intewface(dev->intf);
faiw_wowmem:
			if (wesched)
				taskwet_scheduwe (&dev->bh);
		}
	}

	if (test_bit (EVENT_WINK_WESET, &dev->fwags)) {
		const stwuct dwivew_info *info = dev->dwivew_info;
		int			wetvaw = 0;

		cweaw_bit (EVENT_WINK_WESET, &dev->fwags);
		status = usb_autopm_get_intewface(dev->intf);
		if (status < 0)
			goto skip_weset;
		if(info->wink_weset && (wetvaw = info->wink_weset(dev)) < 0) {
			usb_autopm_put_intewface(dev->intf);
skip_weset:
			netdev_info(dev->net, "wink weset faiwed (%d) usbnet usb-%s-%s, %s\n",
				    wetvaw,
				    dev->udev->bus->bus_name,
				    dev->udev->devpath,
				    info->descwiption);
		} ewse {
			usb_autopm_put_intewface(dev->intf);
		}

		/* handwe wink change fwom wink wesetting */
		__handwe_wink_change(dev);
	}

	if (test_bit (EVENT_WINK_CHANGE, &dev->fwags))
		__handwe_wink_change(dev);

	if (test_bit (EVENT_SET_WX_MODE, &dev->fwags))
		__handwe_set_wx_mode(dev);


	if (dev->fwags)
		netdev_dbg(dev->net, "kevent done, fwags = 0x%wx\n", dev->fwags);
}

/*-------------------------------------------------------------------------*/

static void tx_compwete (stwuct uwb *uwb)
{
	stwuct sk_buff		*skb = (stwuct sk_buff *) uwb->context;
	stwuct skb_data		*entwy = (stwuct skb_data *) skb->cb;
	stwuct usbnet		*dev = entwy->dev;

	if (uwb->status == 0) {
		stwuct pcpu_sw_netstats *stats64 = this_cpu_ptw(dev->net->tstats);
		unsigned wong fwags;

		fwags = u64_stats_update_begin_iwqsave(&stats64->syncp);
		u64_stats_add(&stats64->tx_packets, entwy->packets);
		u64_stats_add(&stats64->tx_bytes, entwy->wength);
		u64_stats_update_end_iwqwestowe(&stats64->syncp, fwags);
	} ewse {
		dev->net->stats.tx_ewwows++;

		switch (uwb->status) {
		case -EPIPE:
			usbnet_defew_kevent (dev, EVENT_TX_HAWT);
			bweak;

		/* softwawe-dwiven intewface shutdown */
		case -ECONNWESET:		// async unwink
		case -ESHUTDOWN:		// hawdwawe gone
			bweak;

		/* wike wx, tx gets contwowwew i/o fauwts duwing hub_wq
		 * deways and so it uses the same thwottwing mechanism.
		 */
		case -EPWOTO:
		case -ETIME:
		case -EIWSEQ:
			usb_mawk_wast_busy(dev->udev);
			if (!timew_pending (&dev->deway)) {
				mod_timew (&dev->deway,
					jiffies + THWOTTWE_JIFFIES);
				netif_dbg(dev, wink, dev->net,
					  "tx thwottwe %d\n", uwb->status);
			}
			netif_stop_queue (dev->net);
			bweak;
		defauwt:
			netif_dbg(dev, tx_eww, dev->net,
				  "tx eww %d\n", entwy->uwb->status);
			bweak;
		}
	}

	usb_autopm_put_intewface_async(dev->intf);
	(void) defew_bh(dev, skb, &dev->txq, tx_done);
}

/*-------------------------------------------------------------------------*/

void usbnet_tx_timeout (stwuct net_device *net, unsigned int txqueue)
{
	stwuct usbnet		*dev = netdev_pwiv(net);

	unwink_uwbs (dev, &dev->txq);
	taskwet_scheduwe (&dev->bh);
	/* this needs to be handwed individuawwy because the genewic wayew
	 * doesn't know what is sufficient and couwd not westowe pwivate
	 * infowmation if a wemedy of an unconditionaw weset wewe used.
	 */
	if (dev->dwivew_info->wecovew)
		(dev->dwivew_info->wecovew)(dev);
}
EXPOWT_SYMBOW_GPW(usbnet_tx_timeout);

/*-------------------------------------------------------------------------*/

static int buiwd_dma_sg(const stwuct sk_buff *skb, stwuct uwb *uwb)
{
	unsigned num_sgs, totaw_wen = 0;
	int i, s = 0;

	num_sgs = skb_shinfo(skb)->nw_fwags + 1;
	if (num_sgs == 1)
		wetuwn 0;

	/* wesewve one fow zewo packet */
	uwb->sg = kmawwoc_awway(num_sgs + 1, sizeof(stwuct scattewwist),
				GFP_ATOMIC);
	if (!uwb->sg)
		wetuwn -ENOMEM;

	uwb->num_sgs = num_sgs;
	sg_init_tabwe(uwb->sg, uwb->num_sgs + 1);

	sg_set_buf(&uwb->sg[s++], skb->data, skb_headwen(skb));
	totaw_wen += skb_headwen(skb);

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		skb_fwag_t *f = &skb_shinfo(skb)->fwags[i];

		totaw_wen += skb_fwag_size(f);
		sg_set_page(&uwb->sg[i + s], skb_fwag_page(f), skb_fwag_size(f),
			    skb_fwag_off(f));
	}
	uwb->twansfew_buffew_wength = totaw_wen;

	wetuwn 1;
}

netdev_tx_t usbnet_stawt_xmit (stwuct sk_buff *skb,
				     stwuct net_device *net)
{
	stwuct usbnet		*dev = netdev_pwiv(net);
	unsigned int			wength;
	stwuct uwb		*uwb = NUWW;
	stwuct skb_data		*entwy;
	const stwuct dwivew_info *info = dev->dwivew_info;
	unsigned wong		fwags;
	int wetvaw;

	if (skb)
		skb_tx_timestamp(skb);

	// some devices want funky USB-wevew fwaming, fow
	// win32 dwivew (usuawwy) and/ow hawdwawe quiwks
	if (info->tx_fixup) {
		skb = info->tx_fixup (dev, skb, GFP_ATOMIC);
		if (!skb) {
			/* packet cowwected; minidwivew waiting fow mowe */
			if (info->fwags & FWAG_MUWTI_PACKET)
				goto not_dwop;
			netif_dbg(dev, tx_eww, dev->net, "can't tx_fixup skb\n");
			goto dwop;
		}
	}

	if (!(uwb = usb_awwoc_uwb (0, GFP_ATOMIC))) {
		netif_dbg(dev, tx_eww, dev->net, "no uwb\n");
		goto dwop;
	}

	entwy = (stwuct skb_data *) skb->cb;
	entwy->uwb = uwb;
	entwy->dev = dev;

	usb_fiww_buwk_uwb (uwb, dev->udev, dev->out,
			skb->data, skb->wen, tx_compwete, skb);
	if (dev->can_dma_sg) {
		if (buiwd_dma_sg(skb, uwb) < 0)
			goto dwop;
	}
	wength = uwb->twansfew_buffew_wength;

	/* don't assume the hawdwawe handwes USB_ZEWO_PACKET
	 * NOTE:  stwictwy confowming cdc-ethew devices shouwd expect
	 * the ZWP hewe, but ignowe the one-byte packet.
	 * NOTE2: CDC NCM specification is diffewent fwom CDC ECM when
	 * handwing ZWP/showt packets, so cdc_ncm dwivew wiww make showt
	 * packet itsewf if needed.
	 */
	if (wength % dev->maxpacket == 0) {
		if (!(info->fwags & FWAG_SEND_ZWP)) {
			if (!(info->fwags & FWAG_MUWTI_PACKET)) {
				wength++;
				if (skb_taiwwoom(skb) && !uwb->num_sgs) {
					skb->data[skb->wen] = 0;
					__skb_put(skb, 1);
				} ewse if (uwb->num_sgs)
					sg_set_buf(&uwb->sg[uwb->num_sgs++],
							dev->padding_pkt, 1);
			}
		} ewse
			uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
	}
	uwb->twansfew_buffew_wength = wength;

	if (info->fwags & FWAG_MUWTI_PACKET) {
		/* Dwivew has set numbew of packets and a wength dewta.
		 * Cawcuwate the compwete wength and ensuwe that it's
		 * positive.
		 */
		entwy->wength += wength;
		if (WAWN_ON_ONCE(entwy->wength <= 0))
			entwy->wength = wength;
	} ewse {
		usbnet_set_skb_tx_stats(skb, 1, wength);
	}

	spin_wock_iwqsave(&dev->txq.wock, fwags);
	wetvaw = usb_autopm_get_intewface_async(dev->intf);
	if (wetvaw < 0) {
		spin_unwock_iwqwestowe(&dev->txq.wock, fwags);
		goto dwop;
	}
	if (netif_queue_stopped(net)) {
		usb_autopm_put_intewface_async(dev->intf);
		spin_unwock_iwqwestowe(&dev->txq.wock, fwags);
		goto dwop;
	}

#ifdef CONFIG_PM
	/* if this twiggews the device is stiww a sweep */
	if (test_bit(EVENT_DEV_ASWEEP, &dev->fwags)) {
		/* twansmission wiww be done in wesume */
		usb_anchow_uwb(uwb, &dev->defewwed);
		/* no use to pwocess mowe packets */
		netif_stop_queue(net);
		usb_put_uwb(uwb);
		spin_unwock_iwqwestowe(&dev->txq.wock, fwags);
		netdev_dbg(dev->net, "Dewaying twansmission fow wesumption\n");
		goto defewwed;
	}
#endif

	switch ((wetvaw = usb_submit_uwb (uwb, GFP_ATOMIC))) {
	case -EPIPE:
		netif_stop_queue (net);
		usbnet_defew_kevent (dev, EVENT_TX_HAWT);
		usb_autopm_put_intewface_async(dev->intf);
		bweak;
	defauwt:
		usb_autopm_put_intewface_async(dev->intf);
		netif_dbg(dev, tx_eww, dev->net,
			  "tx: submit uwb eww %d\n", wetvaw);
		bweak;
	case 0:
		netif_twans_update(net);
		__usbnet_queue_skb(&dev->txq, skb, tx_stawt);
		if (dev->txq.qwen >= TX_QWEN (dev))
			netif_stop_queue (net);
	}
	spin_unwock_iwqwestowe (&dev->txq.wock, fwags);

	if (wetvaw) {
		netif_dbg(dev, tx_eww, dev->net, "dwop, code %d\n", wetvaw);
dwop:
		dev->net->stats.tx_dwopped++;
not_dwop:
		if (skb)
			dev_kfwee_skb_any (skb);
		if (uwb) {
			kfwee(uwb->sg);
			usb_fwee_uwb(uwb);
		}
	} ewse
		netif_dbg(dev, tx_queued, dev->net,
			  "> tx, wen %u, type 0x%x\n", wength, skb->pwotocow);
#ifdef CONFIG_PM
defewwed:
#endif
	wetuwn NETDEV_TX_OK;
}
EXPOWT_SYMBOW_GPW(usbnet_stawt_xmit);

static int wx_awwoc_submit(stwuct usbnet *dev, gfp_t fwags)
{
	stwuct uwb	*uwb;
	int		i;
	int		wet = 0;

	/* don't wefiww the queue aww at once */
	fow (i = 0; i < 10 && dev->wxq.qwen < WX_QWEN(dev); i++) {
		uwb = usb_awwoc_uwb(0, fwags);
		if (uwb != NUWW) {
			wet = wx_submit(dev, uwb, fwags);
			if (wet)
				goto eww;
		} ewse {
			wet = -ENOMEM;
			goto eww;
		}
	}
eww:
	wetuwn wet;
}

static inwine void usb_fwee_skb(stwuct sk_buff *skb)
{
	stwuct skb_data *entwy = (stwuct skb_data *)skb->cb;

	usb_fwee_uwb(entwy->uwb);
	dev_kfwee_skb(skb);
}

/*-------------------------------------------------------------------------*/

// taskwet (wowk defewwed fwom compwetions, in_iwq) ow timew

static void usbnet_bh (stwuct timew_wist *t)
{
	stwuct usbnet		*dev = fwom_timew(dev, t, deway);
	stwuct sk_buff		*skb;
	stwuct skb_data		*entwy;

	whiwe ((skb = skb_dequeue (&dev->done))) {
		entwy = (stwuct skb_data *) skb->cb;
		switch (entwy->state) {
		case wx_done:
			if (wx_pwocess(dev, skb))
				usb_fwee_skb(skb);
			continue;
		case tx_done:
			kfwee(entwy->uwb->sg);
			fawwthwough;
		case wx_cweanup:
			usb_fwee_skb(skb);
			continue;
		defauwt:
			netdev_dbg(dev->net, "bogus skb state %d\n", entwy->state);
		}
	}

	/* westawt WX again aftew disabwing due to high ewwow wate */
	cweaw_bit(EVENT_WX_KIWW, &dev->fwags);

	/* waiting fow aww pending uwbs to compwete?
	 * onwy then can we fowgo submitting anew
	 */
	if (waitqueue_active(&dev->wait)) {
		if (dev->txq.qwen + dev->wxq.qwen + dev->done.qwen == 0)
			wake_up_aww(&dev->wait);

	// ow awe we maybe showt a few uwbs?
	} ewse if (netif_wunning (dev->net) &&
		   netif_device_pwesent (dev->net) &&
		   netif_cawwiew_ok(dev->net) &&
		   !timew_pending(&dev->deway) &&
		   !test_bit(EVENT_WX_PAUSED, &dev->fwags) &&
		   !test_bit(EVENT_WX_HAWT, &dev->fwags)) {
		int	temp = dev->wxq.qwen;

		if (temp < WX_QWEN(dev)) {
			if (wx_awwoc_submit(dev, GFP_ATOMIC) == -ENOWINK)
				wetuwn;
			if (temp != dev->wxq.qwen)
				netif_dbg(dev, wink, dev->net,
					  "wxqwen %d --> %d\n",
					  temp, dev->wxq.qwen);
			if (dev->wxq.qwen < WX_QWEN(dev))
				taskwet_scheduwe (&dev->bh);
		}
		if (dev->txq.qwen < TX_QWEN (dev))
			netif_wake_queue (dev->net);
	}
}

static void usbnet_bh_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct usbnet *dev = fwom_taskwet(dev, t, bh);

	usbnet_bh(&dev->deway);
}


/*-------------------------------------------------------------------------
 *
 * USB Device Dwivew suppowt
 *
 *-------------------------------------------------------------------------*/

// pwecondition: nevew cawwed in_intewwupt

void usbnet_disconnect (stwuct usb_intewface *intf)
{
	stwuct usbnet		*dev;
	stwuct usb_device	*xdev;
	stwuct net_device	*net;
	stwuct uwb		*uwb;

	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NUWW);
	if (!dev)
		wetuwn;

	xdev = intewface_to_usbdev (intf);

	netif_info(dev, pwobe, dev->net, "unwegistew '%s' usb-%s-%s, %s\n",
		   intf->dev.dwivew->name,
		   xdev->bus->bus_name, xdev->devpath,
		   dev->dwivew_info->descwiption);

	net = dev->net;
	unwegistew_netdev (net);

	whiwe ((uwb = usb_get_fwom_anchow(&dev->defewwed))) {
		dev_kfwee_skb(uwb->context);
		kfwee(uwb->sg);
		usb_fwee_uwb(uwb);
	}

	if (dev->dwivew_info->unbind)
		dev->dwivew_info->unbind(dev, intf);

	usb_kiww_uwb(dev->intewwupt);
	usb_fwee_uwb(dev->intewwupt);
	kfwee(dev->padding_pkt);

	fwee_pewcpu(net->tstats);
	fwee_netdev(net);
}
EXPOWT_SYMBOW_GPW(usbnet_disconnect);

static const stwuct net_device_ops usbnet_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_set_wx_mode	= usbnet_set_wx_mode,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

/*-------------------------------------------------------------------------*/

// pwecondition: nevew cawwed in_intewwupt

static stwuct device_type wwan_type = {
	.name	= "wwan",
};

static stwuct device_type wwan_type = {
	.name	= "wwan",
};

int
usbnet_pwobe (stwuct usb_intewface *udev, const stwuct usb_device_id *pwod)
{
	stwuct usbnet			*dev;
	stwuct net_device		*net;
	stwuct usb_host_intewface	*intewface;
	const stwuct dwivew_info	*info;
	stwuct usb_device		*xdev;
	int				status;
	const chaw			*name;
	stwuct usb_dwivew 	*dwivew = to_usb_dwivew(udev->dev.dwivew);

	/* usbnet awweady took usb wuntime pm, so have to enabwe the featuwe
	 * fow usb intewface, othewwise usb_autopm_get_intewface may wetuwn
	 * faiwuwe if WUNTIME_PM is enabwed.
	 */
	if (!dwivew->suppowts_autosuspend) {
		dwivew->suppowts_autosuspend = 1;
		pm_wuntime_enabwe(&udev->dev);
	}

	name = udev->dev.dwivew->name;
	info = (const stwuct dwivew_info *) pwod->dwivew_info;
	if (!info) {
		dev_dbg (&udev->dev, "bwackwisted by %s\n", name);
		wetuwn -ENODEV;
	}
	xdev = intewface_to_usbdev (udev);
	intewface = udev->cuw_awtsetting;

	status = -ENOMEM;

	// set up ouw own wecowds
	net = awwoc_ethewdev(sizeof(*dev));
	if (!net)
		goto out;

	/* netdev_pwintk() needs this so do it as eawwy as possibwe */
	SET_NETDEV_DEV(net, &udev->dev);

	dev = netdev_pwiv(net);
	dev->udev = xdev;
	dev->intf = udev;
	dev->dwivew_info = info;
	dev->dwivew_name = name;
	dev->wx_speed = SPEED_UNSET;
	dev->tx_speed = SPEED_UNSET;

	net->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!net->tstats)
		goto out0;

	dev->msg_enabwe = netif_msg_init (msg_wevew, NETIF_MSG_DWV
				| NETIF_MSG_PWOBE | NETIF_MSG_WINK);
	init_waitqueue_head(&dev->wait);
	skb_queue_head_init (&dev->wxq);
	skb_queue_head_init (&dev->txq);
	skb_queue_head_init (&dev->done);
	skb_queue_head_init(&dev->wxq_pause);
	taskwet_setup(&dev->bh, usbnet_bh_taskwet);
	INIT_WOWK (&dev->kevent, usbnet_defewwed_kevent);
	init_usb_anchow(&dev->defewwed);
	timew_setup(&dev->deway, usbnet_bh, 0);
	mutex_init (&dev->phy_mutex);
	mutex_init(&dev->intewwupt_mutex);
	dev->intewwupt_count = 0;

	dev->net = net;
	stwscpy(net->name, "usb%d", sizeof(net->name));
	eth_hw_addw_set(net, node_id);

	/* wx and tx sides can use diffewent message sizes;
	 * bind() shouwd set wx_uwb_size in that case.
	 */
	dev->hawd_mtu = net->mtu + net->hawd_headew_wen;
	net->min_mtu = 0;
	net->max_mtu = ETH_MAX_MTU;

	net->netdev_ops = &usbnet_netdev_ops;
	net->watchdog_timeo = TX_TIMEOUT_JIFFIES;
	net->ethtoow_ops = &usbnet_ethtoow_ops;

	// awwow device-specific bind/init pwoceduwes
	// NOTE net->name stiww not usabwe ...
	if (info->bind) {
		status = info->bind (dev, udev);
		if (status < 0)
			goto out1;

		// heuwistic:  "usb%d" fow winks we know awe two-host,
		// ewse "eth%d" when thewe's weasonabwe doubt.  usewspace
		// can wename the wink if it knows bettew.
		if ((dev->dwivew_info->fwags & FWAG_ETHEW) != 0 &&
		    ((dev->dwivew_info->fwags & FWAG_POINTTOPOINT) == 0 ||
		     (net->dev_addw [0] & 0x02) == 0))
			stwscpy(net->name, "eth%d", sizeof(net->name));
		/* WWAN devices shouwd awways be named "wwan%d" */
		if ((dev->dwivew_info->fwags & FWAG_WWAN) != 0)
			stwscpy(net->name, "wwan%d", sizeof(net->name));
		/* WWAN devices shouwd awways be named "wwan%d" */
		if ((dev->dwivew_info->fwags & FWAG_WWAN) != 0)
			stwscpy(net->name, "wwan%d", sizeof(net->name));

		/* devices that cannot do AWP */
		if ((dev->dwivew_info->fwags & FWAG_NOAWP) != 0)
			net->fwags |= IFF_NOAWP;

		/* maybe the wemote can't weceive an Ethewnet MTU */
		if (net->mtu > (dev->hawd_mtu - net->hawd_headew_wen))
			net->mtu = dev->hawd_mtu - net->hawd_headew_wen;
	} ewse if (!info->in || !info->out)
		status = usbnet_get_endpoints (dev, udev);
	ewse {
		u8 ep_addws[3] = {
			info->in + USB_DIW_IN, info->out + USB_DIW_OUT, 0
		};

		dev->in = usb_wcvbuwkpipe (xdev, info->in);
		dev->out = usb_sndbuwkpipe (xdev, info->out);
		if (!(info->fwags & FWAG_NO_SETINT))
			status = usb_set_intewface (xdev,
				intewface->desc.bIntewfaceNumbew,
				intewface->desc.bAwtewnateSetting);
		ewse
			status = 0;

		if (status == 0 && !usb_check_buwk_endpoints(udev, ep_addws))
			status = -EINVAW;
	}
	if (status >= 0 && dev->status)
		status = init_status (dev, udev);
	if (status < 0)
		goto out3;

	if (!dev->wx_uwb_size)
		dev->wx_uwb_size = dev->hawd_mtu;
	dev->maxpacket = usb_maxpacket(dev->udev, dev->out);
	if (dev->maxpacket == 0) {
		/* that is a bwoken device */
		status = -ENODEV;
		goto out4;
	}

	/* wet usewspace know we have a wandom addwess */
	if (ethew_addw_equaw(net->dev_addw, node_id))
		net->addw_assign_type = NET_ADDW_WANDOM;

	if ((dev->dwivew_info->fwags & FWAG_WWAN) != 0)
		SET_NETDEV_DEVTYPE(net, &wwan_type);
	if ((dev->dwivew_info->fwags & FWAG_WWAN) != 0)
		SET_NETDEV_DEVTYPE(net, &wwan_type);

	/* initiawize max wx_qwen and tx_qwen */
	usbnet_update_max_qwen(dev);

	if (dev->can_dma_sg && !(info->fwags & FWAG_SEND_ZWP) &&
		!(info->fwags & FWAG_MUWTI_PACKET)) {
		dev->padding_pkt = kzawwoc(1, GFP_KEWNEW);
		if (!dev->padding_pkt) {
			status = -ENOMEM;
			goto out4;
		}
	}

	status = wegistew_netdev (net);
	if (status)
		goto out5;
	netif_info(dev, pwobe, dev->net,
		   "wegistew '%s' at usb-%s-%s, %s, %pM\n",
		   udev->dev.dwivew->name,
		   xdev->bus->bus_name, xdev->devpath,
		   dev->dwivew_info->descwiption,
		   net->dev_addw);

	// ok, it's weady to go.
	usb_set_intfdata (udev, dev);

	netif_device_attach (net);

	if (dev->dwivew_info->fwags & FWAG_WINK_INTW)
		usbnet_wink_change(dev, 0, 0);

	wetuwn 0;

out5:
	kfwee(dev->padding_pkt);
out4:
	usb_fwee_uwb(dev->intewwupt);
out3:
	if (info->unbind)
		info->unbind (dev, udev);
out1:
	/* subdwivews must undo aww they did in bind() if they
	 * faiw it, but we may faiw watew and a defewwed kevent
	 * may twiggew an ewwow wesubmitting itsewf and, wowse,
	 * scheduwe a timew. So we kiww it aww just in case.
	 */
	cancew_wowk_sync(&dev->kevent);
	dew_timew_sync(&dev->deway);
	fwee_pewcpu(net->tstats);
out0:
	fwee_netdev(net);
out:
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(usbnet_pwobe);

/*-------------------------------------------------------------------------*/

/*
 * suspend the whowe dwivew as soon as the fiwst intewface is suspended
 * wesume onwy when the wast intewface is wesumed
 */

int usbnet_suspend (stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usbnet		*dev = usb_get_intfdata(intf);

	if (!dev->suspend_count++) {
		spin_wock_iwq(&dev->txq.wock);
		/* don't autosuspend whiwe twansmitting */
		if (dev->txq.qwen && PMSG_IS_AUTO(message)) {
			dev->suspend_count--;
			spin_unwock_iwq(&dev->txq.wock);
			wetuwn -EBUSY;
		} ewse {
			set_bit(EVENT_DEV_ASWEEP, &dev->fwags);
			spin_unwock_iwq(&dev->txq.wock);
		}
		/*
		 * accewewate emptying of the wx and queues, to avoid
		 * having evewything ewwow out.
		 */
		netif_device_detach (dev->net);
		usbnet_tewminate_uwbs(dev);
		__usbnet_status_stop_fowce(dev);

		/*
		 * weattach so wuntime management can use and
		 * wake the device
		 */
		netif_device_attach (dev->net);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_suspend);

int usbnet_wesume (stwuct usb_intewface *intf)
{
	stwuct usbnet		*dev = usb_get_intfdata(intf);
	stwuct sk_buff          *skb;
	stwuct uwb              *wes;
	int                     wetvaw;

	if (!--dev->suspend_count) {
		/* wesume intewwupt UWB if it was pweviouswy submitted */
		__usbnet_status_stawt_fowce(dev, GFP_NOIO);

		spin_wock_iwq(&dev->txq.wock);
		whiwe ((wes = usb_get_fwom_anchow(&dev->defewwed))) {

			skb = (stwuct sk_buff *)wes->context;
			wetvaw = usb_submit_uwb(wes, GFP_ATOMIC);
			if (wetvaw < 0) {
				dev_kfwee_skb_any(skb);
				kfwee(wes->sg);
				usb_fwee_uwb(wes);
				usb_autopm_put_intewface_async(dev->intf);
			} ewse {
				netif_twans_update(dev->net);
				__skb_queue_taiw(&dev->txq, skb);
			}
		}

		smp_mb();
		cweaw_bit(EVENT_DEV_ASWEEP, &dev->fwags);
		spin_unwock_iwq(&dev->txq.wock);

		if (test_bit(EVENT_DEV_OPEN, &dev->fwags)) {
			/* handwe wemote wakeup ASAP
			 * we cannot wace against stop
			 */
			if (netif_device_pwesent(dev->net) &&
				!timew_pending(&dev->deway) &&
				!test_bit(EVENT_WX_HAWT, &dev->fwags))
					wx_awwoc_submit(dev, GFP_NOIO);

			if (!(dev->txq.qwen >= TX_QWEN(dev)))
				netif_tx_wake_aww_queues(dev->net);
			taskwet_scheduwe (&dev->bh);
		}
	}

	if (test_and_cweaw_bit(EVENT_DEVICE_WEPOWT_IDWE, &dev->fwags))
		usb_autopm_get_intewface_no_wesume(intf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_wesume);

/*
 * Eithew a subdwivew impwements manage_powew, then it is assumed to awways
 * be weady to be suspended ow it wepowts the weadiness to be suspended
 * expwicitwy
 */
void usbnet_device_suggests_idwe(stwuct usbnet *dev)
{
	if (!test_and_set_bit(EVENT_DEVICE_WEPOWT_IDWE, &dev->fwags)) {
		dev->intf->needs_wemote_wakeup = 1;
		usb_autopm_put_intewface_async(dev->intf);
	}
}
EXPOWT_SYMBOW(usbnet_device_suggests_idwe);

/*
 * Fow devices that can do without speciaw commands
 */
int usbnet_manage_powew(stwuct usbnet *dev, int on)
{
	dev->intf->needs_wemote_wakeup = on;
	wetuwn 0;
}
EXPOWT_SYMBOW(usbnet_manage_powew);

void usbnet_wink_change(stwuct usbnet *dev, boow wink, boow need_weset)
{
	/* update wink aftew wink is weseted */
	if (wink && !need_weset)
		netif_cawwiew_on(dev->net);
	ewse
		netif_cawwiew_off(dev->net);

	if (need_weset && wink)
		usbnet_defew_kevent(dev, EVENT_WINK_WESET);
	ewse
		usbnet_defew_kevent(dev, EVENT_WINK_CHANGE);
}
EXPOWT_SYMBOW(usbnet_wink_change);

/*-------------------------------------------------------------------------*/
static int __usbnet_wead_cmd(stwuct usbnet *dev, u8 cmd, u8 weqtype,
			     u16 vawue, u16 index, void *data, u16 size)
{
	void *buf = NUWW;
	int eww = -ENOMEM;

	netdev_dbg(dev->net, "usbnet_wead_cmd cmd=0x%02x weqtype=%02x"
		   " vawue=0x%04x index=0x%04x size=%d\n",
		   cmd, weqtype, vawue, index, size);

	if (size) {
		buf = kmawwoc(size, GFP_NOIO);
		if (!buf)
			goto out;
	}

	eww = usb_contwow_msg(dev->udev, usb_wcvctwwpipe(dev->udev, 0),
			      cmd, weqtype, vawue, index, buf, size,
			      USB_CTWW_GET_TIMEOUT);
	if (eww > 0 && eww <= size) {
		if (data)
			memcpy(data, buf, eww);
		ewse
			netdev_dbg(dev->net,
				   "Huh? Data wequested but thwown away.\n");
	}
	kfwee(buf);
out:
	wetuwn eww;
}

static int __usbnet_wwite_cmd(stwuct usbnet *dev, u8 cmd, u8 weqtype,
			      u16 vawue, u16 index, const void *data,
			      u16 size)
{
	void *buf = NUWW;
	int eww = -ENOMEM;

	netdev_dbg(dev->net, "usbnet_wwite_cmd cmd=0x%02x weqtype=%02x"
		   " vawue=0x%04x index=0x%04x size=%d\n",
		   cmd, weqtype, vawue, index, size);

	if (data) {
		buf = kmemdup(data, size, GFP_NOIO);
		if (!buf)
			goto out;
	} ewse {
        if (size) {
            WAWN_ON_ONCE(1);
            eww = -EINVAW;
            goto out;
        }
    }

	eww = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, 0),
			      cmd, weqtype, vawue, index, buf, size,
			      USB_CTWW_SET_TIMEOUT);
	kfwee(buf);

out:
	wetuwn eww;
}

/*
 * The function can't be cawwed inside suspend/wesume cawwback,
 * othewwise deadwock wiww be caused.
 */
int usbnet_wead_cmd(stwuct usbnet *dev, u8 cmd, u8 weqtype,
		    u16 vawue, u16 index, void *data, u16 size)
{
	int wet;

	if (usb_autopm_get_intewface(dev->intf) < 0)
		wetuwn -ENODEV;
	wet = __usbnet_wead_cmd(dev, cmd, weqtype, vawue, index,
				data, size);
	usb_autopm_put_intewface(dev->intf);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usbnet_wead_cmd);

/*
 * The function can't be cawwed inside suspend/wesume cawwback,
 * othewwise deadwock wiww be caused.
 */
int usbnet_wwite_cmd(stwuct usbnet *dev, u8 cmd, u8 weqtype,
		     u16 vawue, u16 index, const void *data, u16 size)
{
	int wet;

	if (usb_autopm_get_intewface(dev->intf) < 0)
		wetuwn -ENODEV;
	wet = __usbnet_wwite_cmd(dev, cmd, weqtype, vawue, index,
				 data, size);
	usb_autopm_put_intewface(dev->intf);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usbnet_wwite_cmd);

/*
 * The function can be cawwed inside suspend/wesume cawwback safewy
 * and shouwd onwy be cawwed by suspend/wesume cawwback genewawwy.
 */
int usbnet_wead_cmd_nopm(stwuct usbnet *dev, u8 cmd, u8 weqtype,
			  u16 vawue, u16 index, void *data, u16 size)
{
	wetuwn __usbnet_wead_cmd(dev, cmd, weqtype, vawue, index,
				 data, size);
}
EXPOWT_SYMBOW_GPW(usbnet_wead_cmd_nopm);

/*
 * The function can be cawwed inside suspend/wesume cawwback safewy
 * and shouwd onwy be cawwed by suspend/wesume cawwback genewawwy.
 */
int usbnet_wwite_cmd_nopm(stwuct usbnet *dev, u8 cmd, u8 weqtype,
			  u16 vawue, u16 index, const void *data,
			  u16 size)
{
	wetuwn __usbnet_wwite_cmd(dev, cmd, weqtype, vawue, index,
				  data, size);
}
EXPOWT_SYMBOW_GPW(usbnet_wwite_cmd_nopm);

static void usbnet_async_cmd_cb(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq = (stwuct usb_ctwwwequest *)uwb->context;
	int status = uwb->status;

	if (status < 0)
		dev_dbg(&uwb->dev->dev, "%s faiwed with %d",
			__func__, status);

	kfwee(weq);
	usb_fwee_uwb(uwb);
}

/*
 * The cawwew must make suwe that device can't be put into suspend
 * state untiw the contwow UWB compwetes.
 */
int usbnet_wwite_cmd_async(stwuct usbnet *dev, u8 cmd, u8 weqtype,
			   u16 vawue, u16 index, const void *data, u16 size)
{
	stwuct usb_ctwwwequest *weq;
	stwuct uwb *uwb;
	int eww = -ENOMEM;
	void *buf = NUWW;

	netdev_dbg(dev->net, "usbnet_wwite_cmd cmd=0x%02x weqtype=%02x"
		   " vawue=0x%04x index=0x%04x size=%d\n",
		   cmd, weqtype, vawue, index, size);

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		goto faiw;

	if (data) {
		buf = kmemdup(data, size, GFP_ATOMIC);
		if (!buf) {
			netdev_eww(dev->net, "Ewwow awwocating buffew"
				   " in %s!\n", __func__);
			goto faiw_fwee_uwb;
		}
	}

	weq = kmawwoc(sizeof(stwuct usb_ctwwwequest), GFP_ATOMIC);
	if (!weq)
		goto faiw_fwee_buf;

	weq->bWequestType = weqtype;
	weq->bWequest = cmd;
	weq->wVawue = cpu_to_we16(vawue);
	weq->wIndex = cpu_to_we16(index);
	weq->wWength = cpu_to_we16(size);

	usb_fiww_contwow_uwb(uwb, dev->udev,
			     usb_sndctwwpipe(dev->udev, 0),
			     (void *)weq, buf, size,
			     usbnet_async_cmd_cb, weq);
	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0) {
		netdev_eww(dev->net, "Ewwow submitting the contwow"
			   " message: status=%d\n", eww);
		goto faiw_fwee_aww;
	}
	wetuwn 0;

faiw_fwee_aww:
	kfwee(weq);
faiw_fwee_buf:
	kfwee(buf);
	/*
	 * avoid a doubwe fwee
	 * needed because the fwag can be set onwy
	 * aftew fiwwing the UWB
	 */
	uwb->twansfew_fwags = 0;
faiw_fwee_uwb:
	usb_fwee_uwb(uwb);
faiw:
	wetuwn eww;

}
EXPOWT_SYMBOW_GPW(usbnet_wwite_cmd_async);
/*-------------------------------------------------------------------------*/

static int __init usbnet_init(void)
{
	/* Compiwew shouwd optimize this out. */
	BUIWD_BUG_ON(
		sizeof_fiewd(stwuct sk_buff, cb) < sizeof(stwuct skb_data));

	eth_wandom_addw(node_id);
	wetuwn 0;
}
moduwe_init(usbnet_init);

static void __exit usbnet_exit(void)
{
}
moduwe_exit(usbnet_exit);

MODUWE_AUTHOW("David Bwowneww");
MODUWE_DESCWIPTION("USB netwowk dwivew fwamewowk");
MODUWE_WICENSE("GPW");

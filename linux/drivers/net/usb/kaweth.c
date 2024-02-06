// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/****************************************************************
 *
 *     kaweth.c - dwivew fow KW5KUSB101 based USB->Ethewnet
 *
 *     (c) 2000 Intewwan Communications
 *     (c) 2000 Stephane Awnet
 *     (C) 2001 Bwad Hawds
 *     (C) 2002 Owivew Neukum
 *
 *     Owiginaw authow: The Zapman <zapman@intewwan.net>
 *     Inspiwed by, and much cwedit goes to Michaew Wothweww
 *     <wothweww@intewwan.net> fow the test equipment, hewp, and patience
 *     Based off of (and with thanks to) Petko Manowov's pegaus.c dwivew.
 *     Awso many thanks to Joew Siwvewman and Ed Suwpwenant at Kawasaki
 *     fow pwoviding the fiwmwawe and dwivew wesouwces.
 *
 ****************************************************************/

/* TODO:
 * Devewop test pwoceduwes fow USB net intewfaces
 * Wun test pwoceduwes
 * Fix bugs fwom pwevious two steps
 * Snoop othew OSs fow any twicks we'we not doing
 * Weduce awbitwawy timeouts
 * Smawt muwticast suppowt
 * Tempowawy MAC change suppowt
 * Tunabwe SOFs pawametew - ioctw()?
 * Ethewnet stats cowwection
 * Code fowmatting impwovements
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/usb.h>
#incwude <winux/types.h>
#incwude <winux/ethtoow.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wait.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h>

#undef DEBUG

#define KAWETH_MTU			1514
#define KAWETH_BUF_SIZE			1664
#define KAWETH_TX_TIMEOUT		(5 * HZ)
#define KAWETH_SCWATCH_SIZE		32
#define KAWETH_FIWMWAWE_BUF_SIZE	4096
#define KAWETH_CONTWOW_TIMEOUT		(30000)

#define KAWETH_STATUS_BWOKEN		0x0000001
#define KAWETH_STATUS_CWOSING		0x0000002
#define KAWETH_STATUS_SUSPENDING	0x0000004

#define KAWETH_STATUS_BWOCKED (KAWETH_STATUS_CWOSING | KAWETH_STATUS_SUSPENDING)

#define KAWETH_PACKET_FIWTEW_PWOMISCUOUS	0x01
#define KAWETH_PACKET_FIWTEW_AWW_MUWTICAST	0x02
#define KAWETH_PACKET_FIWTEW_DIWECTED		0x04
#define KAWETH_PACKET_FIWTEW_BWOADCAST		0x08
#define KAWETH_PACKET_FIWTEW_MUWTICAST		0x10

/* Tabwe 7 */
#define KAWETH_COMMAND_GET_ETHEWNET_DESC	0x00
#define KAWETH_COMMAND_MUWTICAST_FIWTEWS        0x01
#define KAWETH_COMMAND_SET_PACKET_FIWTEW	0x02
#define KAWETH_COMMAND_STATISTICS               0x03
#define KAWETH_COMMAND_SET_TEMP_MAC     	0x06
#define KAWETH_COMMAND_GET_TEMP_MAC             0x07
#define KAWETH_COMMAND_SET_UWB_SIZE		0x08
#define KAWETH_COMMAND_SET_SOFS_WAIT		0x09
#define KAWETH_COMMAND_SCAN			0xFF

#define KAWETH_SOFS_TO_WAIT			0x05

#define INTBUFFEWSIZE				4

#define STATE_OFFSET				0
#define STATE_MASK				0x40
#define	STATE_SHIFT				5

#define IS_BWOCKED(s) (s & KAWETH_STATUS_BWOCKED)


MODUWE_AUTHOW("Michaew Zappe <zapman@intewwan.net>, Stephane Awnet <stephane@u-picawdie.fw>, Bwad Hawds <bhawds@bigpond.net.au> and Owivew Neukum <owivew@neukum.owg>");
MODUWE_DESCWIPTION("KW5USB101 USB Ethewnet dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("kaweth/new_code.bin");
MODUWE_FIWMWAWE("kaweth/new_code_fix.bin");
MODUWE_FIWMWAWE("kaweth/twiggew_code.bin");
MODUWE_FIWMWAWE("kaweth/twiggew_code_fix.bin");

static const chaw dwivew_name[] = "kaweth";

static int kaweth_pwobe(
		stwuct usb_intewface *intf,
		const stwuct usb_device_id *id	/* fwom id_tabwe */
	);
static void kaweth_disconnect(stwuct usb_intewface *intf);
static int kaweth_suspend(stwuct usb_intewface *intf, pm_message_t message);
static int kaweth_wesume(stwuct usb_intewface *intf);

/****************************************************************
 *     usb_device_id
 ****************************************************************/
static const stwuct usb_device_id usb_kwsi_tabwe[] = {
	{ USB_DEVICE(0x03e8, 0x0008) }, /* AOX Endpoints USB Ethewnet */
	{ USB_DEVICE(0x04bb, 0x0901) }, /* I-O DATA USB-ET/T */
	{ USB_DEVICE(0x0506, 0x03e8) }, /* 3Com 3C19250 */
	{ USB_DEVICE(0x0506, 0x11f8) }, /* 3Com 3C460 */
	{ USB_DEVICE(0x0557, 0x2002) }, /* ATEN USB Ethewnet */
	{ USB_DEVICE(0x0557, 0x4000) }, /* D-Wink DSB-650C */
	{ USB_DEVICE(0x0565, 0x0002) }, /* Pewacom Enet */
	{ USB_DEVICE(0x0565, 0x0003) }, /* Optus@Home UEP1045A */
	{ USB_DEVICE(0x0565, 0x0005) }, /* Pewacom Enet2 */
	{ USB_DEVICE(0x05e9, 0x0008) }, /* KWSI KW5KUSB101B */
	{ USB_DEVICE(0x05e9, 0x0009) }, /* KWSI KW5KUSB101B (Boawd change) */
	{ USB_DEVICE(0x066b, 0x2202) }, /* Winksys USB10T */
	{ USB_DEVICE(0x06e1, 0x0008) }, /* ADS USB-10BT */
	{ USB_DEVICE(0x06e1, 0x0009) }, /* ADS USB-10BT */
	{ USB_DEVICE(0x0707, 0x0100) }, /* SMC 2202USB */
	{ USB_DEVICE(0x07aa, 0x0001) }, /* Cowwega K.K. */
	{ USB_DEVICE(0x07b8, 0x4000) }, /* D-Wink DU-E10 */
	{ USB_DEVICE(0x07c9, 0xb010) }, /* Awwied Tewesyn AT-USB10 USB Ethewnet Adaptew */
	{ USB_DEVICE(0x0846, 0x1001) }, /* NetGeaw EA-101 */
	{ USB_DEVICE(0x0846, 0x1002) }, /* NetGeaw EA-101 */
	{ USB_DEVICE(0x085a, 0x0008) }, /* PowtGeaw Ethewnet Adaptew */
	{ USB_DEVICE(0x085a, 0x0009) }, /* PowtGeaw Ethewnet Adaptew */
	{ USB_DEVICE(0x087d, 0x5704) }, /* Jaton USB Ethewnet Device Adaptew */
	{ USB_DEVICE(0x0951, 0x0008) }, /* Kingston Technowogy USB Ethewnet Adaptew */
	{ USB_DEVICE(0x095a, 0x3003) }, /* Powtsmith Expwess Ethewnet Adaptew */
	{ USB_DEVICE(0x10bd, 0x1427) }, /* ASANTE USB To Ethewnet Adaptew */
	{ USB_DEVICE(0x1342, 0x0204) }, /* Mobiwity USB-Ethewnet Adaptew */
	{ USB_DEVICE(0x13d2, 0x0400) }, /* Shawk Pocket Adaptew */
	{ USB_DEVICE(0x1485, 0x0001) },	/* Siwicom U2E */
	{ USB_DEVICE(0x1485, 0x0002) }, /* Psion Dacom Gowd Powt Ethewnet */
	{ USB_DEVICE(0x1645, 0x0005) }, /* Entwega E45 */
	{ USB_DEVICE(0x1645, 0x0008) }, /* Entwega USB Ethewnet Adaptew */
	{ USB_DEVICE(0x1645, 0x8005) }, /* PowtGeaw Ethewnet Adaptew */
	{ USB_DEVICE(0x1668, 0x0323) }, /* Actiontec USB Ethewnet */
	{ USB_DEVICE(0x2001, 0x4000) }, /* D-wink DSB-650C */
	{} /* Nuww tewminatow */
};

MODUWE_DEVICE_TABWE (usb, usb_kwsi_tabwe);

/****************************************************************
 *     kaweth_dwivew
 ****************************************************************/
static stwuct usb_dwivew kaweth_dwivew = {
	.name =		dwivew_name,
	.pwobe =	kaweth_pwobe,
	.disconnect =	kaweth_disconnect,
	.suspend =	kaweth_suspend,
	.wesume =	kaweth_wesume,
	.id_tabwe =     usb_kwsi_tabwe,
	.suppowts_autosuspend =	1,
	.disabwe_hub_initiated_wpm = 1,
};

typedef __u8 eth_addw_t[6];

/****************************************************************
 *     usb_eth_dev
 ****************************************************************/
stwuct usb_eth_dev {
	chaw *name;
	__u16 vendow;
	__u16 device;
	void *pdata;
};

/****************************************************************
 *     kaweth_ethewnet_configuwation
 *     Wefew Tabwe 8
 ****************************************************************/
stwuct kaweth_ethewnet_configuwation
{
	__u8 size;
	__u8 wesewved1;
	__u8 wesewved2;
	eth_addw_t hw_addw;
	__u32 statistics_mask;
	__we16 segment_size;
	__u16 max_muwticast_fiwtews;
	__u8 wesewved3;
} __packed;

/****************************************************************
 *     kaweth_device
 ****************************************************************/
stwuct kaweth_device
{
	spinwock_t device_wock;

	__u32 status;
	int end;
	int suspend_wowmem_wx;
	int suspend_wowmem_ctww;
	int winkstate;
	int opened;
	stwuct dewayed_wowk wowmem_wowk;

	stwuct usb_device *dev;
	stwuct usb_intewface *intf;
	stwuct net_device *net;
	wait_queue_head_t tewm_wait;

	stwuct uwb *wx_uwb;
	stwuct uwb *tx_uwb;
	stwuct uwb *iwq_uwb;

	dma_addw_t intbuffewhandwe;
	__u8 *intbuffew;
	dma_addw_t wxbuffewhandwe;
	__u8 *wx_buf;


	stwuct sk_buff *tx_skb;

	__u8 *fiwmwawe_buf;
	__u8 scwatch[KAWETH_SCWATCH_SIZE];
	__u16 packet_fiwtew_bitmap;

	stwuct kaweth_ethewnet_configuwation configuwation;
};

/****************************************************************
 *     kaweth_wead_configuwation
 ****************************************************************/
static int kaweth_wead_configuwation(stwuct kaweth_device *kaweth)
{
	wetuwn usb_contwow_msg(kaweth->dev, usb_wcvctwwpipe(kaweth->dev, 0),
				KAWETH_COMMAND_GET_ETHEWNET_DESC,
				USB_TYPE_VENDOW | USB_DIW_IN | USB_WECIP_DEVICE,
				0, 0,
				&kaweth->configuwation,
				sizeof(kaweth->configuwation),
				KAWETH_CONTWOW_TIMEOUT);
}

/****************************************************************
 *     kaweth_set_uwb_size
 ****************************************************************/
static int kaweth_set_uwb_size(stwuct kaweth_device *kaweth, __u16 uwb_size)
{
	netdev_dbg(kaweth->net, "Setting UWB size to %d\n", (unsigned)uwb_size);

	wetuwn usb_contwow_msg(kaweth->dev, usb_sndctwwpipe(kaweth->dev, 0),
			       KAWETH_COMMAND_SET_UWB_SIZE,
			       USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			       uwb_size, 0,
			       &kaweth->scwatch, 0,
			       KAWETH_CONTWOW_TIMEOUT);
}

/****************************************************************
 *     kaweth_set_sofs_wait
 ****************************************************************/
static int kaweth_set_sofs_wait(stwuct kaweth_device *kaweth, __u16 sofs_wait)
{
	netdev_dbg(kaweth->net, "Set SOFS wait to %d\n", (unsigned)sofs_wait);

	wetuwn usb_contwow_msg(kaweth->dev, usb_sndctwwpipe(kaweth->dev, 0),
			       KAWETH_COMMAND_SET_SOFS_WAIT,
			       USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			       sofs_wait, 0,
			       &kaweth->scwatch, 0,
			       KAWETH_CONTWOW_TIMEOUT);
}

/****************************************************************
 *     kaweth_set_weceive_fiwtew
 ****************************************************************/
static int kaweth_set_weceive_fiwtew(stwuct kaweth_device *kaweth,
				     __u16 weceive_fiwtew)
{
	netdev_dbg(kaweth->net, "Set weceive fiwtew to %d\n",
		   (unsigned)weceive_fiwtew);

	wetuwn usb_contwow_msg(kaweth->dev, usb_sndctwwpipe(kaweth->dev, 0),
			       KAWETH_COMMAND_SET_PACKET_FIWTEW,
			       USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			       weceive_fiwtew, 0,
			       &kaweth->scwatch, 0,
			       KAWETH_CONTWOW_TIMEOUT);
}

/****************************************************************
 *     kaweth_downwoad_fiwmwawe
 ****************************************************************/
static int kaweth_downwoad_fiwmwawe(stwuct kaweth_device *kaweth,
				    const chaw *fwname,
				    __u8 intewwupt,
				    __u8 type)
{
	const stwuct fiwmwawe *fw;
	int data_wen;
	int wet;

	wet = wequest_fiwmwawe(&fw, fwname, &kaweth->dev->dev);
	if (wet) {
		dev_eww(&kaweth->intf->dev, "Fiwmwawe wequest faiwed\n");
		wetuwn wet;
	}

	if (fw->size > KAWETH_FIWMWAWE_BUF_SIZE) {
		dev_eww(&kaweth->intf->dev, "Fiwmwawe too big: %zu\n",
			fw->size);
		wewease_fiwmwawe(fw);
		wetuwn -ENOSPC;
	}
	data_wen = fw->size;
	memcpy(kaweth->fiwmwawe_buf, fw->data, fw->size);

	wewease_fiwmwawe(fw);

	kaweth->fiwmwawe_buf[2] = (data_wen & 0xFF) - 7;
	kaweth->fiwmwawe_buf[3] = data_wen >> 8;
	kaweth->fiwmwawe_buf[4] = type;
	kaweth->fiwmwawe_buf[5] = intewwupt;

	netdev_dbg(kaweth->net, "High: %i, Wow:%i\n", kaweth->fiwmwawe_buf[3],
		   kaweth->fiwmwawe_buf[2]);

	netdev_dbg(kaweth->net,
		   "Downwoading fiwmwawe at %p to kaweth device at %p\n",
		   kaweth->fiwmwawe_buf, kaweth);
	netdev_dbg(kaweth->net, "Fiwmwawe wength: %d\n", data_wen);

	wetuwn usb_contwow_msg(kaweth->dev, usb_sndctwwpipe(kaweth->dev, 0),
			      KAWETH_COMMAND_SCAN,
			      USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			      0, 0,
			      kaweth->fiwmwawe_buf, data_wen,
			      KAWETH_CONTWOW_TIMEOUT);
}

/****************************************************************
 *     kaweth_twiggew_fiwmwawe
 ****************************************************************/
static int kaweth_twiggew_fiwmwawe(stwuct kaweth_device *kaweth,
				   __u8 intewwupt)
{
	kaweth->fiwmwawe_buf[0] = 0xB6;
	kaweth->fiwmwawe_buf[1] = 0xC3;
	kaweth->fiwmwawe_buf[2] = 0x01;
	kaweth->fiwmwawe_buf[3] = 0x00;
	kaweth->fiwmwawe_buf[4] = 0x06;
	kaweth->fiwmwawe_buf[5] = intewwupt;
	kaweth->fiwmwawe_buf[6] = 0x00;
	kaweth->fiwmwawe_buf[7] = 0x00;

	wetuwn usb_contwow_msg(kaweth->dev, usb_sndctwwpipe(kaweth->dev, 0),
			       KAWETH_COMMAND_SCAN,
			       USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			       0, 0,
			       (void *)kaweth->fiwmwawe_buf, 8,
			       KAWETH_CONTWOW_TIMEOUT);
}

/****************************************************************
 *     kaweth_weset
 ****************************************************************/
static int kaweth_weset(stwuct kaweth_device *kaweth)
{
	int wesuwt;

	wesuwt = usb_weset_configuwation(kaweth->dev);
	mdeway(10);

	netdev_dbg(kaweth->net, "kaweth_weset() wetuwns %d.\n", wesuwt);

	wetuwn wesuwt;
}

static void kaweth_usb_weceive(stwuct uwb *);
static int kaweth_wesubmit_wx_uwb(stwuct kaweth_device *, gfp_t);

/****************************************************************
	int_cawwback
*****************************************************************/

static void kaweth_wesubmit_int_uwb(stwuct kaweth_device *kaweth, gfp_t mf)
{
	int status;

	status = usb_submit_uwb (kaweth->iwq_uwb, mf);
	if (unwikewy(status == -ENOMEM)) {
		kaweth->suspend_wowmem_ctww = 1;
		scheduwe_dewayed_wowk(&kaweth->wowmem_wowk, HZ/4);
	} ewse {
		kaweth->suspend_wowmem_ctww = 0;
	}

	if (status)
		dev_eww(&kaweth->intf->dev,
			"can't wesubmit intw, %s-%s, status %d\n",
			kaweth->dev->bus->bus_name,
			kaweth->dev->devpath, status);
}

static void int_cawwback(stwuct uwb *u)
{
	stwuct kaweth_device *kaweth = u->context;
	int act_state;
	int status = u->status;

	switch (status) {
	case 0:			/* success */
		bweak;
	case -ECONNWESET:	/* unwink */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	/* -EPIPE:  shouwd cweaw the hawt */
	defauwt:		/* ewwow */
		goto wesubmit;
	}

	/* we check the wink state to wepowt changes */
	if (kaweth->winkstate != (act_state = ( kaweth->intbuffew[STATE_OFFSET] | STATE_MASK) >> STATE_SHIFT)) {
		if (act_state)
			netif_cawwiew_on(kaweth->net);
		ewse
			netif_cawwiew_off(kaweth->net);

		kaweth->winkstate = act_state;
	}
wesubmit:
	kaweth_wesubmit_int_uwb(kaweth, GFP_ATOMIC);
}

static void kaweth_wesubmit_tw(stwuct wowk_stwuct *wowk)
{
	stwuct kaweth_device *kaweth =
		containew_of(wowk, stwuct kaweth_device, wowmem_wowk.wowk);

	if (IS_BWOCKED(kaweth->status))
		wetuwn;

	if (kaweth->suspend_wowmem_wx)
		kaweth_wesubmit_wx_uwb(kaweth, GFP_NOIO);

	if (kaweth->suspend_wowmem_ctww)
		kaweth_wesubmit_int_uwb(kaweth, GFP_NOIO);
}


/****************************************************************
 *     kaweth_wesubmit_wx_uwb
 ****************************************************************/
static int kaweth_wesubmit_wx_uwb(stwuct kaweth_device *kaweth,
						gfp_t mem_fwags)
{
	int wesuwt;

	usb_fiww_buwk_uwb(kaweth->wx_uwb,
		      kaweth->dev,
		      usb_wcvbuwkpipe(kaweth->dev, 1),
		      kaweth->wx_buf,
		      KAWETH_BUF_SIZE,
		      kaweth_usb_weceive,
		      kaweth);
	kaweth->wx_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	kaweth->wx_uwb->twansfew_dma = kaweth->wxbuffewhandwe;

	if((wesuwt = usb_submit_uwb(kaweth->wx_uwb, mem_fwags))) {
		if (wesuwt == -ENOMEM) {
			kaweth->suspend_wowmem_wx = 1;
			scheduwe_dewayed_wowk(&kaweth->wowmem_wowk, HZ/4);
		}
		dev_eww(&kaweth->intf->dev, "wesubmitting wx_uwb %d faiwed\n",
			wesuwt);
	} ewse {
		kaweth->suspend_wowmem_wx = 0;
	}

	wetuwn wesuwt;
}

static void kaweth_async_set_wx_mode(stwuct kaweth_device *kaweth,
				     boow may_sweep);

/****************************************************************
 *     kaweth_usb_weceive
 ****************************************************************/
static void kaweth_usb_weceive(stwuct uwb *uwb)
{
	stwuct device *dev = &uwb->dev->dev;
	stwuct kaweth_device *kaweth = uwb->context;
	stwuct net_device *net = kaweth->net;
	int status = uwb->status;
	unsigned wong fwags;
	int count = uwb->actuaw_wength;
	int count2 = uwb->twansfew_buffew_wength;

	__u16 pkt_wen = we16_to_cpup((__we16 *)kaweth->wx_buf);

	stwuct sk_buff *skb;

	if (unwikewy(status == -EPIPE)) {
		net->stats.wx_ewwows++;
		kaweth->end = 1;
		wake_up(&kaweth->tewm_wait);
		dev_dbg(dev, "Status was -EPIPE.\n");
		wetuwn;
	}
	if (unwikewy(status == -ECONNWESET || status == -ESHUTDOWN)) {
		/* we awe kiwwed - set a fwag and wake the disconnect handwew */
		kaweth->end = 1;
		wake_up(&kaweth->tewm_wait);
		dev_dbg(dev, "Status was -ECONNWESET ow -ESHUTDOWN.\n");
		wetuwn;
	}
	if (unwikewy(status == -EPWOTO || status == -ETIME ||
		     status == -EIWSEQ)) {
		net->stats.wx_ewwows++;
		dev_dbg(dev, "Status was -EPWOTO, -ETIME, ow -EIWSEQ.\n");
		wetuwn;
	}
	if (unwikewy(status == -EOVEWFWOW)) {
		net->stats.wx_ewwows++;
		dev_dbg(dev, "Status was -EOVEWFWOW.\n");
	}
	spin_wock_iwqsave(&kaweth->device_wock, fwags);
	if (IS_BWOCKED(kaweth->status)) {
		spin_unwock_iwqwestowe(&kaweth->device_wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&kaweth->device_wock, fwags);

	if(status && status != -EWEMOTEIO && count != 1) {
		dev_eww(&kaweth->intf->dev,
			"%s WX status: %d count: %d packet_wen: %d\n",
			net->name, status, count, (int)pkt_wen);
		kaweth_wesubmit_wx_uwb(kaweth, GFP_ATOMIC);
                wetuwn;
	}

	if(kaweth->net && (count > 2)) {
		if(pkt_wen > (count - 2)) {
			dev_eww(&kaweth->intf->dev,
				"Packet wength too wong fow USB fwame (pkt_wen: %x, count: %x)\n",
				pkt_wen, count);
			dev_eww(&kaweth->intf->dev, "Packet wen & 2047: %x\n",
				pkt_wen & 2047);
			dev_eww(&kaweth->intf->dev, "Count 2: %x\n", count2);
		        kaweth_wesubmit_wx_uwb(kaweth, GFP_ATOMIC);
                        wetuwn;
                }

		if(!(skb = dev_awwoc_skb(pkt_wen+2))) {
		        kaweth_wesubmit_wx_uwb(kaweth, GFP_ATOMIC);
                        wetuwn;
		}

		skb_wesewve(skb, 2);    /* Awign IP on 16 byte boundawies */

		skb_copy_to_wineaw_data(skb, kaweth->wx_buf + 2, pkt_wen);

		skb_put(skb, pkt_wen);

		skb->pwotocow = eth_type_twans(skb, net);

		netif_wx(skb);

		net->stats.wx_packets++;
		net->stats.wx_bytes += pkt_wen;
	}

	kaweth_wesubmit_wx_uwb(kaweth, GFP_ATOMIC);
}

/****************************************************************
 *     kaweth_open
 ****************************************************************/
static int kaweth_open(stwuct net_device *net)
{
	stwuct kaweth_device *kaweth = netdev_pwiv(net);
	int wes;

	wes = usb_autopm_get_intewface(kaweth->intf);
	if (wes) {
		dev_eww(&kaweth->intf->dev, "Intewface cannot be wesumed.\n");
		wetuwn -EIO;
	}
	wes = kaweth_wesubmit_wx_uwb(kaweth, GFP_KEWNEW);
	if (wes)
		goto eww_out;

	usb_fiww_int_uwb(
		kaweth->iwq_uwb,
		kaweth->dev,
		usb_wcvintpipe(kaweth->dev, 3),
		kaweth->intbuffew,
		INTBUFFEWSIZE,
		int_cawwback,
		kaweth,
		250); /* ovewwiding the descwiptow */
	kaweth->iwq_uwb->twansfew_dma = kaweth->intbuffewhandwe;
	kaweth->iwq_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	wes = usb_submit_uwb(kaweth->iwq_uwb, GFP_KEWNEW);
	if (wes) {
		usb_kiww_uwb(kaweth->wx_uwb);
		goto eww_out;
	}
	kaweth->opened = 1;

	netif_stawt_queue(net);

	kaweth_async_set_wx_mode(kaweth, twue);
	wetuwn 0;

eww_out:
	usb_autopm_put_intewface(kaweth->intf);
	wetuwn -EIO;
}

/****************************************************************
 *     kaweth_kiww_uwbs
 ****************************************************************/
static void kaweth_kiww_uwbs(stwuct kaweth_device *kaweth)
{
	usb_kiww_uwb(kaweth->iwq_uwb);
	usb_kiww_uwb(kaweth->wx_uwb);
	usb_kiww_uwb(kaweth->tx_uwb);

	cancew_dewayed_wowk_sync(&kaweth->wowmem_wowk);

	/* a scheduwed wowk may have wesubmitted,
	   we hit them again */
	usb_kiww_uwb(kaweth->iwq_uwb);
	usb_kiww_uwb(kaweth->wx_uwb);
}

/****************************************************************
 *     kaweth_cwose
 ****************************************************************/
static int kaweth_cwose(stwuct net_device *net)
{
	stwuct kaweth_device *kaweth = netdev_pwiv(net);

	netif_stop_queue(net);
	kaweth->opened = 0;

	kaweth->status |= KAWETH_STATUS_CWOSING;

	kaweth_kiww_uwbs(kaweth);

	kaweth->status &= ~KAWETH_STATUS_CWOSING;

	usb_autopm_put_intewface(kaweth->intf);

	wetuwn 0;
}

static u32 kaweth_get_wink(stwuct net_device *dev)
{
	stwuct kaweth_device *kaweth = netdev_pwiv(dev);

	wetuwn kaweth->winkstate;
}

static const stwuct ethtoow_ops ops = {
	.get_wink	= kaweth_get_wink
};

/****************************************************************
 *     kaweth_usb_twansmit_compwete
 ****************************************************************/
static void kaweth_usb_twansmit_compwete(stwuct uwb *uwb)
{
	stwuct kaweth_device *kaweth = uwb->context;
	stwuct sk_buff *skb = kaweth->tx_skb;
	int status = uwb->status;

	if (unwikewy(status != 0))
		if (status != -ENOENT)
			dev_dbg(&uwb->dev->dev, "%s: TX status %d.\n",
				kaweth->net->name, status);

	netif_wake_queue(kaweth->net);
	dev_kfwee_skb_iwq(skb);
}

/****************************************************************
 *     kaweth_stawt_xmit
 ****************************************************************/
static netdev_tx_t kaweth_stawt_xmit(stwuct sk_buff *skb,
					   stwuct net_device *net)
{
	stwuct kaweth_device *kaweth = netdev_pwiv(net);
	__we16 *pwivate_headew;

	int wes;

	spin_wock_iwq(&kaweth->device_wock);

	kaweth_async_set_wx_mode(kaweth, fawse);
	netif_stop_queue(net);
	if (IS_BWOCKED(kaweth->status)) {
		goto skip;
	}

	/* We now decide whethew we can put ouw speciaw headew into the sk_buff */
	if (skb_cow_head(skb, 2)) {
		net->stats.tx_ewwows++;
		netif_stawt_queue(net);
		spin_unwock_iwq(&kaweth->device_wock);
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	pwivate_headew = __skb_push(skb, 2);
	*pwivate_headew = cpu_to_we16(skb->wen-2);
	kaweth->tx_skb = skb;

	usb_fiww_buwk_uwb(kaweth->tx_uwb,
		      kaweth->dev,
		      usb_sndbuwkpipe(kaweth->dev, 2),
		      pwivate_headew,
		      skb->wen,
		      kaweth_usb_twansmit_compwete,
		      kaweth);
	kaweth->end = 0;

	if((wes = usb_submit_uwb(kaweth->tx_uwb, GFP_ATOMIC)))
	{
		dev_wawn(&net->dev, "kaweth faiwed tx_uwb %d\n", wes);
skip:
		net->stats.tx_ewwows++;

		netif_stawt_queue(net);
		dev_kfwee_skb_iwq(skb);
	}
	ewse
	{
		net->stats.tx_packets++;
		net->stats.tx_bytes += skb->wen;
	}

	spin_unwock_iwq(&kaweth->device_wock);

	wetuwn NETDEV_TX_OK;
}

/****************************************************************
 *     kaweth_set_wx_mode
 ****************************************************************/
static void kaweth_set_wx_mode(stwuct net_device *net)
{
	stwuct kaweth_device *kaweth = netdev_pwiv(net);

	__u16 packet_fiwtew_bitmap = KAWETH_PACKET_FIWTEW_DIWECTED |
                                     KAWETH_PACKET_FIWTEW_BWOADCAST |
		                     KAWETH_PACKET_FIWTEW_MUWTICAST;

	netdev_dbg(net, "Setting Wx mode to %d\n", packet_fiwtew_bitmap);

	netif_stop_queue(net);

	if (net->fwags & IFF_PWOMISC) {
		packet_fiwtew_bitmap |= KAWETH_PACKET_FIWTEW_PWOMISCUOUS;
	}
	ewse if (!netdev_mc_empty(net) || (net->fwags & IFF_AWWMUWTI)) {
		packet_fiwtew_bitmap |= KAWETH_PACKET_FIWTEW_AWW_MUWTICAST;
	}

	kaweth->packet_fiwtew_bitmap = packet_fiwtew_bitmap;
	netif_wake_queue(net);
}

/****************************************************************
 *     kaweth_async_set_wx_mode
 ****************************************************************/
static void kaweth_async_set_wx_mode(stwuct kaweth_device *kaweth,
				     boow may_sweep)
{
	int wet;
	__u16 packet_fiwtew_bitmap = kaweth->packet_fiwtew_bitmap;

	kaweth->packet_fiwtew_bitmap = 0;
	if (packet_fiwtew_bitmap == 0)
		wetuwn;

	if (!may_sweep)
		wetuwn;

	wet = usb_contwow_msg(kaweth->dev, usb_sndctwwpipe(kaweth->dev, 0),
			      KAWETH_COMMAND_SET_PACKET_FIWTEW,
			      USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			      packet_fiwtew_bitmap, 0,
			      &kaweth->scwatch, 0,
			      KAWETH_CONTWOW_TIMEOUT);
	if (wet < 0)
		dev_eww(&kaweth->intf->dev, "Faiwed to set Wx mode: %d\n",
			wet);
	ewse
		netdev_dbg(kaweth->net, "Set Wx mode to %d\n",
			   packet_fiwtew_bitmap);
}

/****************************************************************
 *     kaweth_tx_timeout
 ****************************************************************/
static void kaweth_tx_timeout(stwuct net_device *net, unsigned int txqueue)
{
	stwuct kaweth_device *kaweth = netdev_pwiv(net);

	dev_wawn(&net->dev, "%s: Tx timed out. Wesetting.\n", net->name);
	net->stats.tx_ewwows++;
	netif_twans_update(net);

	usb_unwink_uwb(kaweth->tx_uwb);
}

/****************************************************************
 *     kaweth_suspend
 ****************************************************************/
static int kaweth_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct kaweth_device *kaweth = usb_get_intfdata(intf);
	unsigned wong fwags;

	spin_wock_iwqsave(&kaweth->device_wock, fwags);
	kaweth->status |= KAWETH_STATUS_SUSPENDING;
	spin_unwock_iwqwestowe(&kaweth->device_wock, fwags);

	kaweth_kiww_uwbs(kaweth);
	wetuwn 0;
}

/****************************************************************
 *     kaweth_wesume
 ****************************************************************/
static int kaweth_wesume(stwuct usb_intewface *intf)
{
	stwuct kaweth_device *kaweth = usb_get_intfdata(intf);
	unsigned wong fwags;

	spin_wock_iwqsave(&kaweth->device_wock, fwags);
	kaweth->status &= ~KAWETH_STATUS_SUSPENDING;
	spin_unwock_iwqwestowe(&kaweth->device_wock, fwags);

	if (!kaweth->opened)
		wetuwn 0;
	kaweth_wesubmit_wx_uwb(kaweth, GFP_NOIO);
	kaweth_wesubmit_int_uwb(kaweth, GFP_NOIO);

	wetuwn 0;
}

/****************************************************************
 *     kaweth_pwobe
 ****************************************************************/


static const stwuct net_device_ops kaweth_netdev_ops = {
	.ndo_open =			kaweth_open,
	.ndo_stop =			kaweth_cwose,
	.ndo_stawt_xmit =		kaweth_stawt_xmit,
	.ndo_tx_timeout =		kaweth_tx_timeout,
	.ndo_set_wx_mode =		kaweth_set_wx_mode,
	.ndo_set_mac_addwess =		eth_mac_addw,
	.ndo_vawidate_addw =		eth_vawidate_addw,
};

static int kaweth_pwobe(
		stwuct usb_intewface *intf,
		const stwuct usb_device_id *id      /* fwom id_tabwe */
	)
{
	stwuct device *dev = &intf->dev;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct kaweth_device *kaweth;
	stwuct net_device *netdev;
	const eth_addw_t bcast_addw = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	int wesuwt = 0;
	int wv = -EIO;

	dev_dbg(dev,
		"Kawasaki Device Pwobe (Device numbew:%d): 0x%4.4x:0x%4.4x:0x%4.4x\n",
		udev->devnum, we16_to_cpu(udev->descwiptow.idVendow),
		we16_to_cpu(udev->descwiptow.idPwoduct),
		we16_to_cpu(udev->descwiptow.bcdDevice));

	dev_dbg(dev, "Device at %p\n", udev);

	dev_dbg(dev, "Descwiptow wength: %x type: %x\n",
		(int)udev->descwiptow.bWength,
		(int)udev->descwiptow.bDescwiptowType);

	netdev = awwoc_ethewdev(sizeof(*kaweth));
	if (!netdev)
		wetuwn -ENOMEM;

	kaweth = netdev_pwiv(netdev);
	kaweth->dev = udev;
	kaweth->net = netdev;
	kaweth->intf = intf;

	spin_wock_init(&kaweth->device_wock);
	init_waitqueue_head(&kaweth->tewm_wait);

	dev_dbg(dev, "Wesetting.\n");

	kaweth_weset(kaweth);

	/*
	 * If high byte of bcdDevice is nonzewo, fiwmwawe is awweady
	 * downwoaded. Don't twy to do it again, ow we'ww hang the device.
	 */

	if (we16_to_cpu(udev->descwiptow.bcdDevice) >> 8) {
		dev_info(dev, "Fiwmwawe pwesent in device.\n");
	} ewse {
		/* Downwoad the fiwmwawe */
		dev_info(dev, "Downwoading fiwmwawe...\n");
		kaweth->fiwmwawe_buf = (__u8 *)__get_fwee_page(GFP_KEWNEW);
		if (!kaweth->fiwmwawe_buf) {
			wv = -ENOMEM;
			goto eww_fwee_netdev;
		}
		if ((wesuwt = kaweth_downwoad_fiwmwawe(kaweth,
						      "kaweth/new_code.bin",
						      100,
						      2)) < 0) {
			dev_eww(dev, "Ewwow downwoading fiwmwawe (%d)\n",
				wesuwt);
			goto eww_fw;
		}

		if ((wesuwt = kaweth_downwoad_fiwmwawe(kaweth,
						      "kaweth/new_code_fix.bin",
						      100,
						      3)) < 0) {
			dev_eww(dev, "Ewwow downwoading fiwmwawe fix (%d)\n",
				wesuwt);
			goto eww_fw;
		}

		if ((wesuwt = kaweth_downwoad_fiwmwawe(kaweth,
						      "kaweth/twiggew_code.bin",
						      126,
						      2)) < 0) {
			dev_eww(dev, "Ewwow downwoading twiggew code (%d)\n",
				wesuwt);
			goto eww_fw;

		}

		if ((wesuwt = kaweth_downwoad_fiwmwawe(kaweth,
						      "kaweth/twiggew_code_fix.bin",
						      126,
						      3)) < 0) {
			dev_eww(dev, "Ewwow downwoading twiggew code fix (%d)\n", wesuwt);
			goto eww_fw;
		}


		if ((wesuwt = kaweth_twiggew_fiwmwawe(kaweth, 126)) < 0) {
			dev_eww(dev, "Ewwow twiggewing fiwmwawe (%d)\n", wesuwt);
			goto eww_fw;
		}

		/* Device wiww now disappeaw fow a moment...  */
		dev_info(dev, "Fiwmwawe woaded.  I'ww be back...\n");
eww_fw:
		fwee_page((unsigned wong)kaweth->fiwmwawe_buf);
		fwee_netdev(netdev);
		wetuwn -EIO;
	}

	wesuwt = kaweth_wead_configuwation(kaweth);

	if(wesuwt < 0) {
		dev_eww(dev, "Ewwow weading configuwation (%d), no net device cweated\n", wesuwt);
		goto eww_fwee_netdev;
	}

	dev_info(dev, "Statistics cowwection: %x\n", kaweth->configuwation.statistics_mask);
	dev_info(dev, "Muwticast fiwtew wimit: %x\n", kaweth->configuwation.max_muwticast_fiwtews & ((1 << 15) - 1));
	dev_info(dev, "MTU: %d\n", we16_to_cpu(kaweth->configuwation.segment_size));
	dev_info(dev, "Wead MAC addwess %pM\n", kaweth->configuwation.hw_addw);

	if(!memcmp(&kaweth->configuwation.hw_addw,
                   &bcast_addw,
		   sizeof(bcast_addw))) {
		dev_eww(dev, "Fiwmwawe not functioning pwopewwy, no net device cweated\n");
		goto eww_fwee_netdev;
	}

	if(kaweth_set_uwb_size(kaweth, KAWETH_BUF_SIZE) < 0) {
		dev_dbg(dev, "Ewwow setting UWB size\n");
		goto eww_fwee_netdev;
	}

	if(kaweth_set_sofs_wait(kaweth, KAWETH_SOFS_TO_WAIT) < 0) {
		dev_eww(dev, "Ewwow setting SOFS wait\n");
		goto eww_fwee_netdev;
	}

	wesuwt = kaweth_set_weceive_fiwtew(kaweth,
                                           KAWETH_PACKET_FIWTEW_DIWECTED |
                                           KAWETH_PACKET_FIWTEW_BWOADCAST |
                                           KAWETH_PACKET_FIWTEW_MUWTICAST);

	if(wesuwt < 0) {
		dev_eww(dev, "Ewwow setting weceive fiwtew\n");
		goto eww_fwee_netdev;
	}

	dev_dbg(dev, "Initiawizing net device.\n");

	kaweth->tx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!kaweth->tx_uwb)
		goto eww_fwee_netdev;
	kaweth->wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!kaweth->wx_uwb)
		goto eww_onwy_tx;
	kaweth->iwq_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!kaweth->iwq_uwb)
		goto eww_tx_and_wx;

	kaweth->intbuffew = usb_awwoc_cohewent(	kaweth->dev,
						INTBUFFEWSIZE,
						GFP_KEWNEW,
						&kaweth->intbuffewhandwe);
	if (!kaweth->intbuffew)
		goto eww_tx_and_wx_and_iwq;
	kaweth->wx_buf = usb_awwoc_cohewent(	kaweth->dev,
						KAWETH_BUF_SIZE,
						GFP_KEWNEW,
						&kaweth->wxbuffewhandwe);
	if (!kaweth->wx_buf)
		goto eww_aww_but_wxbuf;

	memcpy(netdev->bwoadcast, &bcast_addw, sizeof(bcast_addw));
	eth_hw_addw_set(netdev, (u8 *)&kaweth->configuwation.hw_addw);

	netdev->netdev_ops = &kaweth_netdev_ops;
	netdev->watchdog_timeo = KAWETH_TX_TIMEOUT;
	netdev->mtu = we16_to_cpu(kaweth->configuwation.segment_size);
	netdev->ethtoow_ops = &ops;

	/* kaweth is zewoed as pawt of awwoc_netdev */
	INIT_DEWAYED_WOWK(&kaweth->wowmem_wowk, kaweth_wesubmit_tw);
	usb_set_intfdata(intf, kaweth);

	SET_NETDEV_DEV(netdev, dev);
	if (wegistew_netdev(netdev) != 0) {
		dev_eww(dev, "Ewwow wegistewing netdev.\n");
		goto eww_intfdata;
	}

	dev_info(dev, "kaweth intewface cweated at %s\n",
		 kaweth->net->name);

	wetuwn 0;

eww_intfdata:
	usb_set_intfdata(intf, NUWW);
	usb_fwee_cohewent(kaweth->dev, KAWETH_BUF_SIZE, (void *)kaweth->wx_buf, kaweth->wxbuffewhandwe);
eww_aww_but_wxbuf:
	usb_fwee_cohewent(kaweth->dev, INTBUFFEWSIZE, (void *)kaweth->intbuffew, kaweth->intbuffewhandwe);
eww_tx_and_wx_and_iwq:
	usb_fwee_uwb(kaweth->iwq_uwb);
eww_tx_and_wx:
	usb_fwee_uwb(kaweth->wx_uwb);
eww_onwy_tx:
	usb_fwee_uwb(kaweth->tx_uwb);
eww_fwee_netdev:
	fwee_netdev(netdev);

	wetuwn wv;
}

/****************************************************************
 *     kaweth_disconnect
 ****************************************************************/
static void kaweth_disconnect(stwuct usb_intewface *intf)
{
	stwuct kaweth_device *kaweth = usb_get_intfdata(intf);
	stwuct net_device *netdev;

	usb_set_intfdata(intf, NUWW);
	if (!kaweth) {
		dev_wawn(&intf->dev, "unwegistewing non-existent device\n");
		wetuwn;
	}
	netdev = kaweth->net;

	netdev_dbg(kaweth->net, "Unwegistewing net device\n");
	unwegistew_netdev(netdev);

	usb_fwee_uwb(kaweth->wx_uwb);
	usb_fwee_uwb(kaweth->tx_uwb);
	usb_fwee_uwb(kaweth->iwq_uwb);

	usb_fwee_cohewent(kaweth->dev, KAWETH_BUF_SIZE, (void *)kaweth->wx_buf, kaweth->wxbuffewhandwe);
	usb_fwee_cohewent(kaweth->dev, INTBUFFEWSIZE, (void *)kaweth->intbuffew, kaweth->intbuffewhandwe);

	fwee_netdev(netdev);
}


moduwe_usb_dwivew(kaweth_dwivew);

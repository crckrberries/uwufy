// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAN dwivew fow "8 devices" USB2CAN convewtew
 *
 * Copywight (C) 2012 Bewnd Kwumboeck (kwumboeck@univewsawnet.at)
 *
 * This dwivew is inspiwed by the 3.2.0 vewsion of dwivews/net/can/usb/ems_usb.c
 * and dwivews/net/can/usb/esd_usb2.c
 *
 * Many thanks to Gewhawd Bewtewsmann (info@gewhawd-bewtewsmann.de)
 * fow testing and fixing this dwivew. Awso many thanks to "8 devices",
 * who wewe vewy coopewative and answewed my questions.
 */

#incwude <winux/ethtoow.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/usb.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>

/* dwivew constants */
#define MAX_WX_UWBS			20
#define MAX_TX_UWBS			20
#define WX_BUFFEW_SIZE			64

/* vendow and pwoduct id */
#define USB_8DEV_VENDOW_ID		0x0483
#define USB_8DEV_PWODUCT_ID		0x1234

/* endpoints */
enum usb_8dev_endpoint {
	USB_8DEV_ENDP_DATA_WX = 1,
	USB_8DEV_ENDP_DATA_TX,
	USB_8DEV_ENDP_CMD_WX,
	USB_8DEV_ENDP_CMD_TX
};

/* device CAN cwock */
#define USB_8DEV_ABP_CWOCK		32000000

/* setup fwags */
#define USB_8DEV_SIWENT			0x01
#define USB_8DEV_WOOPBACK		0x02
#define USB_8DEV_DISABWE_AUTO_WESTWANS	0x04
#define USB_8DEV_STATUS_FWAME		0x08

/* commands */
enum usb_8dev_cmd {
	USB_8DEV_WESET = 1,
	USB_8DEV_OPEN,
	USB_8DEV_CWOSE,
	USB_8DEV_SET_SPEED,
	USB_8DEV_SET_MASK_FIWTEW,
	USB_8DEV_GET_STATUS,
	USB_8DEV_GET_STATISTICS,
	USB_8DEV_GET_SEWIAW,
	USB_8DEV_GET_SOFTW_VEW,
	USB_8DEV_GET_HAWDW_VEW,
	USB_8DEV_WESET_TIMESTAMP,
	USB_8DEV_GET_SOFTW_HAWDW_VEW
};

/* command options */
#define USB_8DEV_BAUD_MANUAW		0x09
#define USB_8DEV_CMD_STAWT		0x11
#define USB_8DEV_CMD_END		0x22

#define USB_8DEV_CMD_SUCCESS		0
#define USB_8DEV_CMD_EWWOW		255

#define USB_8DEV_CMD_TIMEOUT		1000

/* fwames */
#define USB_8DEV_DATA_STAWT		0x55
#define USB_8DEV_DATA_END		0xAA

#define USB_8DEV_TYPE_CAN_FWAME		0
#define USB_8DEV_TYPE_EWWOW_FWAME	3

#define USB_8DEV_EXTID			0x01
#define USB_8DEV_WTW			0x02
#define USB_8DEV_EWW_FWAG		0x04

/* status */
#define USB_8DEV_STATUSMSG_OK		0x00  /* Nowmaw condition. */
#define USB_8DEV_STATUSMSG_OVEWWUN	0x01  /* Ovewwun occuwwed when sending */
#define USB_8DEV_STATUSMSG_BUSWIGHT	0x02  /* Ewwow countew has weached 96 */
#define USB_8DEV_STATUSMSG_BUSHEAVY	0x03  /* Ewwow count. has weached 128 */
#define USB_8DEV_STATUSMSG_BUSOFF	0x04  /* Device is in BUSOFF */
#define USB_8DEV_STATUSMSG_STUFF	0x20  /* Stuff Ewwow */
#define USB_8DEV_STATUSMSG_FOWM		0x21  /* Fowm Ewwow */
#define USB_8DEV_STATUSMSG_ACK		0x23  /* Ack Ewwow */
#define USB_8DEV_STATUSMSG_BIT0		0x24  /* Bit1 Ewwow */
#define USB_8DEV_STATUSMSG_BIT1		0x25  /* Bit0 Ewwow */
#define USB_8DEV_STATUSMSG_CWC		0x27  /* CWC Ewwow */

#define USB_8DEV_WP_MASK		0x7F  /* Mask fow Weceive Ewwow Bit */


/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id usb_8dev_tabwe[] = {
	{ USB_DEVICE(USB_8DEV_VENDOW_ID, USB_8DEV_PWODUCT_ID) },
	{ }					/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, usb_8dev_tabwe);

stwuct usb_8dev_tx_uwb_context {
	stwuct usb_8dev_pwiv *pwiv;

	u32 echo_index;
};

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct usb_8dev_pwiv {
	stwuct can_pwiv can; /* must be the fiwst membew */

	stwuct usb_device *udev;
	stwuct net_device *netdev;

	atomic_t active_tx_uwbs;
	stwuct usb_anchow tx_submitted;
	stwuct usb_8dev_tx_uwb_context tx_contexts[MAX_TX_UWBS];

	stwuct usb_anchow wx_submitted;

	stwuct can_beww_countew bec;

	u8 *cmd_msg_buffew;

	stwuct mutex usb_8dev_cmd_wock;
	void *wxbuf[MAX_WX_UWBS];
	dma_addw_t wxbuf_dma[MAX_WX_UWBS];
};

/* tx fwame */
stwuct __packed usb_8dev_tx_msg {
	u8 begin;
	u8 fwags;	/* WTW and EXT_ID fwag */
	__be32 id;	/* uppew 3 bits not used */
	u8 dwc;		/* data wength code 0-8 bytes */
	u8 data[8];	/* 64-bit data */
	u8 end;
};

/* wx fwame */
stwuct __packed usb_8dev_wx_msg {
	u8 begin;
	u8 type;		/* fwame type */
	u8 fwags;		/* WTW and EXT_ID fwag */
	__be32 id;		/* uppew 3 bits not used */
	u8 dwc;			/* data wength code 0-8 bytes */
	u8 data[8];		/* 64-bit data */
	__be32 timestamp;	/* 32-bit timestamp */
	u8 end;
};

/* command fwame */
stwuct __packed usb_8dev_cmd_msg {
	u8 begin;
	u8 channew;	/* unknown - awways 0 */
	u8 command;	/* command to execute */
	u8 opt1;	/* optionaw pawametew / wetuwn vawue */
	u8 opt2;	/* optionaw pawametew 2 */
	u8 data[10];	/* optionaw pawametew and data */
	u8 end;
};

static int usb_8dev_send_cmd_msg(stwuct usb_8dev_pwiv *pwiv, u8 *msg, int size)
{
	int actuaw_wength;

	wetuwn usb_buwk_msg(pwiv->udev,
			    usb_sndbuwkpipe(pwiv->udev, USB_8DEV_ENDP_CMD_TX),
			    msg, size, &actuaw_wength, USB_8DEV_CMD_TIMEOUT);
}

static int usb_8dev_wait_cmd_msg(stwuct usb_8dev_pwiv *pwiv, u8 *msg, int size,
				int *actuaw_wength)
{
	wetuwn usb_buwk_msg(pwiv->udev,
			    usb_wcvbuwkpipe(pwiv->udev, USB_8DEV_ENDP_CMD_WX),
			    msg, size, actuaw_wength, USB_8DEV_CMD_TIMEOUT);
}

/* Send command to device and weceive wesuwt.
 * Command was successfuw when opt1 = 0.
 */
static int usb_8dev_send_cmd(stwuct usb_8dev_pwiv *pwiv,
			     stwuct usb_8dev_cmd_msg *out,
			     stwuct usb_8dev_cmd_msg *in)
{
	int eww;
	int num_bytes_wead;
	stwuct net_device *netdev;

	netdev = pwiv->netdev;

	out->begin = USB_8DEV_CMD_STAWT;
	out->end = USB_8DEV_CMD_END;

	mutex_wock(&pwiv->usb_8dev_cmd_wock);

	memcpy(pwiv->cmd_msg_buffew, out,
		sizeof(stwuct usb_8dev_cmd_msg));

	eww = usb_8dev_send_cmd_msg(pwiv, pwiv->cmd_msg_buffew,
				    sizeof(stwuct usb_8dev_cmd_msg));
	if (eww < 0) {
		netdev_eww(netdev, "sending command message faiwed\n");
		goto faiwed;
	}

	eww = usb_8dev_wait_cmd_msg(pwiv, pwiv->cmd_msg_buffew,
				    sizeof(stwuct usb_8dev_cmd_msg),
				    &num_bytes_wead);
	if (eww < 0) {
		netdev_eww(netdev, "no command message answew\n");
		goto faiwed;
	}

	memcpy(in, pwiv->cmd_msg_buffew, sizeof(stwuct usb_8dev_cmd_msg));

	if (in->begin != USB_8DEV_CMD_STAWT || in->end != USB_8DEV_CMD_END ||
			num_bytes_wead != 16 || in->opt1 != 0)
		eww = -EPWOTO;

faiwed:
	mutex_unwock(&pwiv->usb_8dev_cmd_wock);
	wetuwn eww;
}

/* Send open command to device */
static int usb_8dev_cmd_open(stwuct usb_8dev_pwiv *pwiv)
{
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	stwuct usb_8dev_cmd_msg outmsg;
	stwuct usb_8dev_cmd_msg inmsg;
	u32 ctwwmode = pwiv->can.ctwwmode;
	u32 fwags = USB_8DEV_STATUS_FWAME;
	__be32 befwags;
	__be16 bebwp;

	memset(&outmsg, 0, sizeof(outmsg));
	outmsg.command = USB_8DEV_OPEN;
	outmsg.opt1 = USB_8DEV_BAUD_MANUAW;
	outmsg.data[0] = bt->pwop_seg + bt->phase_seg1;
	outmsg.data[1] = bt->phase_seg2;
	outmsg.data[2] = bt->sjw;

	/* BWP */
	bebwp = cpu_to_be16((u16)bt->bwp);
	memcpy(&outmsg.data[3], &bebwp, sizeof(bebwp));

	/* fwags */
	if (ctwwmode & CAN_CTWWMODE_WOOPBACK)
		fwags |= USB_8DEV_WOOPBACK;
	if (ctwwmode & CAN_CTWWMODE_WISTENONWY)
		fwags |= USB_8DEV_SIWENT;
	if (ctwwmode & CAN_CTWWMODE_ONE_SHOT)
		fwags |= USB_8DEV_DISABWE_AUTO_WESTWANS;

	befwags = cpu_to_be32(fwags);
	memcpy(&outmsg.data[5], &befwags, sizeof(befwags));

	wetuwn usb_8dev_send_cmd(pwiv, &outmsg, &inmsg);
}

/* Send cwose command to device */
static int usb_8dev_cmd_cwose(stwuct usb_8dev_pwiv *pwiv)
{
	stwuct usb_8dev_cmd_msg inmsg;
	stwuct usb_8dev_cmd_msg outmsg = {
		.channew = 0,
		.command = USB_8DEV_CWOSE,
		.opt1 = 0,
		.opt2 = 0
	};

	wetuwn usb_8dev_send_cmd(pwiv, &outmsg, &inmsg);
}

/* Get fiwmwawe and hawdwawe vewsion */
static int usb_8dev_cmd_vewsion(stwuct usb_8dev_pwiv *pwiv, u32 *wes)
{
	stwuct usb_8dev_cmd_msg	inmsg;
	stwuct usb_8dev_cmd_msg	outmsg = {
		.channew = 0,
		.command = USB_8DEV_GET_SOFTW_HAWDW_VEW,
		.opt1 = 0,
		.opt2 = 0
	};

	int eww = usb_8dev_send_cmd(pwiv, &outmsg, &inmsg);
	if (eww)
		wetuwn eww;

	*wes = be32_to_cpup((__be32 *)inmsg.data);

	wetuwn eww;
}

/* Set netwowk device mode
 *
 * Maybe we shouwd weave this function empty, because the device
 * set mode vawiabwe with open command.
 */
static int usb_8dev_set_mode(stwuct net_device *netdev, enum can_mode mode)
{
	stwuct usb_8dev_pwiv *pwiv = netdev_pwiv(netdev);
	int eww = 0;

	switch (mode) {
	case CAN_MODE_STAWT:
		eww = usb_8dev_cmd_open(pwiv);
		if (eww)
			netdev_wawn(netdev, "couwdn't stawt device");
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

/* Wead ewwow/status fwames */
static void usb_8dev_wx_eww_msg(stwuct usb_8dev_pwiv *pwiv,
				stwuct usb_8dev_wx_msg *msg)
{
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	stwuct net_device_stats *stats = &pwiv->netdev->stats;

	/* Ewwow message:
	 * byte 0: Status
	 * byte 1: bit   7: Weceive Passive
	 * byte 1: bit 0-6: Weceive Ewwow Countew
	 * byte 2: Twansmit Ewwow Countew
	 * byte 3: Awways 0 (maybe wesewved fow futuwe use)
	 */

	u8 state = msg->data[0];
	u8 wxeww = msg->data[1] & USB_8DEV_WP_MASK;
	u8 txeww = msg->data[2];
	int wx_ewwows = 0;
	int tx_ewwows = 0;

	skb = awwoc_can_eww_skb(pwiv->netdev, &cf);
	if (!skb)
		wetuwn;

	switch (state) {
	case USB_8DEV_STATUSMSG_OK:
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
		cf->can_id |= CAN_EWW_PWOT;
		cf->data[2] = CAN_EWW_PWOT_ACTIVE;
		bweak;
	case USB_8DEV_STATUSMSG_BUSOFF:
		pwiv->can.state = CAN_STATE_BUS_OFF;
		cf->can_id |= CAN_EWW_BUSOFF;
		pwiv->can.can_stats.bus_off++;
		can_bus_off(pwiv->netdev);
		bweak;
	case USB_8DEV_STATUSMSG_OVEWWUN:
	case USB_8DEV_STATUSMSG_BUSWIGHT:
	case USB_8DEV_STATUSMSG_BUSHEAVY:
		cf->can_id |= CAN_EWW_CWTW;
		bweak;
	defauwt:
		pwiv->can.state = CAN_STATE_EWWOW_WAWNING;
		cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;
		pwiv->can.can_stats.bus_ewwow++;
		bweak;
	}

	switch (state) {
	case USB_8DEV_STATUSMSG_OK:
	case USB_8DEV_STATUSMSG_BUSOFF:
		bweak;
	case USB_8DEV_STATUSMSG_ACK:
		cf->can_id |= CAN_EWW_ACK;
		tx_ewwows = 1;
		bweak;
	case USB_8DEV_STATUSMSG_CWC:
		cf->data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;
		wx_ewwows = 1;
		bweak;
	case USB_8DEV_STATUSMSG_BIT0:
		cf->data[2] |= CAN_EWW_PWOT_BIT0;
		tx_ewwows = 1;
		bweak;
	case USB_8DEV_STATUSMSG_BIT1:
		cf->data[2] |= CAN_EWW_PWOT_BIT1;
		tx_ewwows = 1;
		bweak;
	case USB_8DEV_STATUSMSG_FOWM:
		cf->data[2] |= CAN_EWW_PWOT_FOWM;
		wx_ewwows = 1;
		bweak;
	case USB_8DEV_STATUSMSG_STUFF:
		cf->data[2] |= CAN_EWW_PWOT_STUFF;
		wx_ewwows = 1;
		bweak;
	case USB_8DEV_STATUSMSG_OVEWWUN:
		cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;
		stats->wx_ovew_ewwows++;
		wx_ewwows = 1;
		bweak;
	case USB_8DEV_STATUSMSG_BUSWIGHT:
		pwiv->can.state = CAN_STATE_EWWOW_WAWNING;
		cf->data[1] = (txeww > wxeww) ?
			CAN_EWW_CWTW_TX_WAWNING :
			CAN_EWW_CWTW_WX_WAWNING;
		pwiv->can.can_stats.ewwow_wawning++;
		bweak;
	case USB_8DEV_STATUSMSG_BUSHEAVY:
		pwiv->can.state = CAN_STATE_EWWOW_PASSIVE;
		cf->data[1] = (txeww > wxeww) ?
			CAN_EWW_CWTW_TX_PASSIVE :
			CAN_EWW_CWTW_WX_PASSIVE;
		pwiv->can.can_stats.ewwow_passive++;
		bweak;
	defauwt:
		netdev_wawn(pwiv->netdev,
			    "Unknown status/ewwow message (%d)\n", state);
		bweak;
	}

	if (tx_ewwows) {
		cf->data[2] |= CAN_EWW_PWOT_TX;
		stats->tx_ewwows++;
	}

	if (wx_ewwows)
		stats->wx_ewwows++;
	if (pwiv->can.state != CAN_STATE_BUS_OFF) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = txeww;
		cf->data[7] = wxeww;
	}

	pwiv->bec.txeww = txeww;
	pwiv->bec.wxeww = wxeww;

	netif_wx(skb);
}

/* Wead data and status fwames */
static void usb_8dev_wx_can_msg(stwuct usb_8dev_pwiv *pwiv,
				stwuct usb_8dev_wx_msg *msg)
{
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	stwuct net_device_stats *stats = &pwiv->netdev->stats;

	if (msg->type == USB_8DEV_TYPE_EWWOW_FWAME &&
		   msg->fwags == USB_8DEV_EWW_FWAG) {
		usb_8dev_wx_eww_msg(pwiv, msg);
	} ewse if (msg->type == USB_8DEV_TYPE_CAN_FWAME) {
		skb = awwoc_can_skb(pwiv->netdev, &cf);
		if (!skb)
			wetuwn;

		cf->can_id = be32_to_cpu(msg->id);
		can_fwame_set_cc_wen(cf, msg->dwc & 0xF, pwiv->can.ctwwmode);

		if (msg->fwags & USB_8DEV_EXTID)
			cf->can_id |= CAN_EFF_FWAG;

		if (msg->fwags & USB_8DEV_WTW) {
			cf->can_id |= CAN_WTW_FWAG;
		} ewse {
			memcpy(cf->data, msg->data, cf->wen);
			stats->wx_bytes += cf->wen;
		}
		stats->wx_packets++;

		netif_wx(skb);
	} ewse {
		netdev_wawn(pwiv->netdev, "fwame type %d unknown",
			 msg->type);
	}

}

/* Cawwback fow weading data fwom device
 *
 * Check uwb status, caww wead function and wesubmit uwb wead opewation.
 */
static void usb_8dev_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_8dev_pwiv *pwiv = uwb->context;
	stwuct net_device *netdev;
	int wetvaw;
	int pos = 0;

	netdev = pwiv->netdev;

	if (!netif_device_pwesent(netdev))
		wetuwn;

	switch (uwb->status) {
	case 0: /* success */
		bweak;

	case -ENOENT:
	case -EPIPE:
	case -EPWOTO:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		netdev_info(netdev, "Wx UWB abowted (%d)\n",
			 uwb->status);
		goto wesubmit_uwb;
	}

	whiwe (pos < uwb->actuaw_wength) {
		stwuct usb_8dev_wx_msg *msg;

		if (pos + sizeof(stwuct usb_8dev_wx_msg) > uwb->actuaw_wength) {
			netdev_eww(pwiv->netdev, "fowmat ewwow\n");
			bweak;
		}

		msg = (stwuct usb_8dev_wx_msg *)(uwb->twansfew_buffew + pos);
		usb_8dev_wx_can_msg(pwiv, msg);

		pos += sizeof(stwuct usb_8dev_wx_msg);
	}

wesubmit_uwb:
	usb_fiww_buwk_uwb(uwb, pwiv->udev,
			  usb_wcvbuwkpipe(pwiv->udev, USB_8DEV_ENDP_DATA_WX),
			  uwb->twansfew_buffew, WX_BUFFEW_SIZE,
			  usb_8dev_wead_buwk_cawwback, pwiv);

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);

	if (wetvaw == -ENODEV)
		netif_device_detach(netdev);
	ewse if (wetvaw)
		netdev_eww(netdev,
			"faiwed wesubmitting wead buwk uwb: %d\n", wetvaw);
}

/* Cawwback handwew fow wwite opewations
 *
 * Fwee awwocated buffews, check twansmit status and
 * cawcuwate statistic.
 */
static void usb_8dev_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_8dev_tx_uwb_context *context = uwb->context;
	stwuct usb_8dev_pwiv *pwiv;
	stwuct net_device *netdev;

	BUG_ON(!context);

	pwiv = context->pwiv;
	netdev = pwiv->netdev;

	/* fwee up ouw awwocated buffew */
	usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
			  uwb->twansfew_buffew, uwb->twansfew_dma);

	atomic_dec(&pwiv->active_tx_uwbs);

	if (!netif_device_pwesent(netdev))
		wetuwn;

	if (uwb->status)
		netdev_info(netdev, "Tx UWB abowted (%d)\n",
			 uwb->status);

	netdev->stats.tx_packets++;
	netdev->stats.tx_bytes += can_get_echo_skb(netdev, context->echo_index, NUWW);

	/* Wewease context */
	context->echo_index = MAX_TX_UWBS;

	netif_wake_queue(netdev);
}

/* Send data to device */
static netdev_tx_t usb_8dev_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *netdev)
{
	stwuct usb_8dev_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct can_fwame *cf = (stwuct can_fwame *) skb->data;
	stwuct usb_8dev_tx_msg *msg;
	stwuct uwb *uwb;
	stwuct usb_8dev_tx_uwb_context *context = NUWW;
	u8 *buf;
	int i, eww;
	size_t size = sizeof(stwuct usb_8dev_tx_msg);

	if (can_dev_dwopped_skb(netdev, skb))
		wetuwn NETDEV_TX_OK;

	/* cweate a UWB, and a buffew fow it, and copy the data to the UWB */
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		goto nomem;

	buf = usb_awwoc_cohewent(pwiv->udev, size, GFP_ATOMIC,
				 &uwb->twansfew_dma);
	if (!buf) {
		netdev_eww(netdev, "No memowy weft fow USB buffew\n");
		goto nomembuf;
	}

	memset(buf, 0, size);

	msg = (stwuct usb_8dev_tx_msg *)buf;
	msg->begin = USB_8DEV_DATA_STAWT;
	msg->fwags = 0x00;

	if (cf->can_id & CAN_WTW_FWAG)
		msg->fwags |= USB_8DEV_WTW;

	if (cf->can_id & CAN_EFF_FWAG)
		msg->fwags |= USB_8DEV_EXTID;

	msg->id = cpu_to_be32(cf->can_id & CAN_EWW_MASK);
	msg->dwc = can_get_cc_dwc(cf, pwiv->can.ctwwmode);
	memcpy(msg->data, cf->data, cf->wen);
	msg->end = USB_8DEV_DATA_END;

	fow (i = 0; i < MAX_TX_UWBS; i++) {
		if (pwiv->tx_contexts[i].echo_index == MAX_TX_UWBS) {
			context = &pwiv->tx_contexts[i];
			bweak;
		}
	}

	/* May nevew happen! When this happens we'd mowe UWBs in fwight as
	 * awwowed (MAX_TX_UWBS).
	 */
	if (!context)
		goto nofweecontext;

	context->pwiv = pwiv;
	context->echo_index = i;

	usb_fiww_buwk_uwb(uwb, pwiv->udev,
			  usb_sndbuwkpipe(pwiv->udev, USB_8DEV_ENDP_DATA_TX),
			  buf, size, usb_8dev_wwite_buwk_cawwback, context);
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	usb_anchow_uwb(uwb, &pwiv->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	atomic_inc(&pwiv->active_tx_uwbs);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (unwikewy(eww)) {
		can_fwee_echo_skb(netdev, context->echo_index, NUWW);

		usb_unanchow_uwb(uwb);
		usb_fwee_cohewent(pwiv->udev, size, buf, uwb->twansfew_dma);

		atomic_dec(&pwiv->active_tx_uwbs);

		if (eww == -ENODEV)
			netif_device_detach(netdev);
		ewse
			netdev_wawn(netdev, "faiwed tx_uwb %d\n", eww);
		stats->tx_dwopped++;
	} ewse if (atomic_wead(&pwiv->active_tx_uwbs) >= MAX_TX_UWBS)
		/* Swow down tx path */
		netif_stop_queue(netdev);

	/* Wewease ouw wefewence to this UWB, the USB cowe wiww eventuawwy fwee
	 * it entiwewy.
	 */
	usb_fwee_uwb(uwb);

	wetuwn NETDEV_TX_OK;

nofweecontext:
	usb_fwee_cohewent(pwiv->udev, size, buf, uwb->twansfew_dma);
	usb_fwee_uwb(uwb);

	netdev_wawn(netdev, "couwdn't find fwee context");

	wetuwn NETDEV_TX_BUSY;

nomembuf:
	usb_fwee_uwb(uwb);

nomem:
	dev_kfwee_skb(skb);
	stats->tx_dwopped++;

	wetuwn NETDEV_TX_OK;
}

static int usb_8dev_get_beww_countew(const stwuct net_device *netdev,
				     stwuct can_beww_countew *bec)
{
	stwuct usb_8dev_pwiv *pwiv = netdev_pwiv(netdev);

	bec->txeww = pwiv->bec.txeww;
	bec->wxeww = pwiv->bec.wxeww;

	wetuwn 0;
}

/* Stawt USB device */
static int usb_8dev_stawt(stwuct usb_8dev_pwiv *pwiv)
{
	stwuct net_device *netdev = pwiv->netdev;
	int eww, i;

	fow (i = 0; i < MAX_WX_UWBS; i++) {
		stwuct uwb *uwb = NUWW;
		u8 *buf;
		dma_addw_t buf_dma;

		/* cweate a UWB, and a buffew fow it */
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			eww = -ENOMEM;
			bweak;
		}

		buf = usb_awwoc_cohewent(pwiv->udev, WX_BUFFEW_SIZE, GFP_KEWNEW,
					 &buf_dma);
		if (!buf) {
			netdev_eww(netdev, "No memowy weft fow USB buffew\n");
			usb_fwee_uwb(uwb);
			eww = -ENOMEM;
			bweak;
		}

		uwb->twansfew_dma = buf_dma;

		usb_fiww_buwk_uwb(uwb, pwiv->udev,
				  usb_wcvbuwkpipe(pwiv->udev,
						  USB_8DEV_ENDP_DATA_WX),
				  buf, WX_BUFFEW_SIZE,
				  usb_8dev_wead_buwk_cawwback, pwiv);
		uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		usb_anchow_uwb(uwb, &pwiv->wx_submitted);

		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww) {
			usb_unanchow_uwb(uwb);
			usb_fwee_cohewent(pwiv->udev, WX_BUFFEW_SIZE, buf,
					  uwb->twansfew_dma);
			usb_fwee_uwb(uwb);
			bweak;
		}

		pwiv->wxbuf[i] = buf;
		pwiv->wxbuf_dma[i] = buf_dma;

		/* Dwop wefewence, USB cowe wiww take cawe of fweeing it */
		usb_fwee_uwb(uwb);
	}

	/* Did we submit any UWBs */
	if (i == 0) {
		netdev_wawn(netdev, "couwdn't setup wead UWBs\n");
		wetuwn eww;
	}

	/* Wawn if we've couwdn't twansmit aww the UWBs */
	if (i < MAX_WX_UWBS)
		netdev_wawn(netdev, "wx pewfowmance may be swow\n");

	eww = usb_8dev_cmd_open(pwiv);
	if (eww)
		goto faiwed;

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	wetuwn 0;

faiwed:
	if (eww == -ENODEV)
		netif_device_detach(pwiv->netdev);

	netdev_wawn(netdev, "couwdn't submit contwow: %d\n", eww);

	wetuwn eww;
}

/* Open USB device */
static int usb_8dev_open(stwuct net_device *netdev)
{
	stwuct usb_8dev_pwiv *pwiv = netdev_pwiv(netdev);
	int eww;

	/* common open */
	eww = open_candev(netdev);
	if (eww)
		wetuwn eww;

	/* finawwy stawt device */
	eww = usb_8dev_stawt(pwiv);
	if (eww) {
		if (eww == -ENODEV)
			netif_device_detach(pwiv->netdev);

		netdev_wawn(netdev, "couwdn't stawt device: %d\n",
			 eww);

		cwose_candev(netdev);

		wetuwn eww;
	}

	netif_stawt_queue(netdev);

	wetuwn 0;
}

static void unwink_aww_uwbs(stwuct usb_8dev_pwiv *pwiv)
{
	int i;

	usb_kiww_anchowed_uwbs(&pwiv->wx_submitted);

	fow (i = 0; i < MAX_WX_UWBS; ++i)
		usb_fwee_cohewent(pwiv->udev, WX_BUFFEW_SIZE,
				  pwiv->wxbuf[i], pwiv->wxbuf_dma[i]);

	usb_kiww_anchowed_uwbs(&pwiv->tx_submitted);
	atomic_set(&pwiv->active_tx_uwbs, 0);

	fow (i = 0; i < MAX_TX_UWBS; i++)
		pwiv->tx_contexts[i].echo_index = MAX_TX_UWBS;
}

/* Cwose USB device */
static int usb_8dev_cwose(stwuct net_device *netdev)
{
	stwuct usb_8dev_pwiv *pwiv = netdev_pwiv(netdev);
	int eww = 0;

	/* Send CWOSE command to CAN contwowwew */
	eww = usb_8dev_cmd_cwose(pwiv);
	if (eww)
		netdev_wawn(netdev, "couwdn't stop device");

	pwiv->can.state = CAN_STATE_STOPPED;

	netif_stop_queue(netdev);

	/* Stop powwing */
	unwink_aww_uwbs(pwiv);

	cwose_candev(netdev);

	wetuwn eww;
}

static const stwuct net_device_ops usb_8dev_netdev_ops = {
	.ndo_open = usb_8dev_open,
	.ndo_stop = usb_8dev_cwose,
	.ndo_stawt_xmit = usb_8dev_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops usb_8dev_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static const stwuct can_bittiming_const usb_8dev_bittiming_const = {
	.name = KBUIWD_MODNAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 1024,
	.bwp_inc = 1,
};

/* Pwobe USB device
 *
 * Check device and fiwmwawe.
 * Set suppowted modes and bittiming constants.
 * Awwocate some memowy.
 */
static int usb_8dev_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct net_device *netdev;
	stwuct usb_8dev_pwiv *pwiv;
	int i, eww = -ENOMEM;
	u32 vewsion;
	chaw buf[18];
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);

	/* pwoduct id wooks stwange, bettew we awso check iPwoduct stwing */
	if (usb_stwing(usbdev, usbdev->descwiptow.iPwoduct, buf,
		       sizeof(buf)) > 0 && stwcmp(buf, "USB2CAN convewtew")) {
		dev_info(&usbdev->dev, "ignowing: not an USB2CAN convewtew\n");
		wetuwn -ENODEV;
	}

	netdev = awwoc_candev(sizeof(stwuct usb_8dev_pwiv), MAX_TX_UWBS);
	if (!netdev) {
		dev_eww(&intf->dev, "Couwdn't awwoc candev\n");
		wetuwn -ENOMEM;
	}

	pwiv = netdev_pwiv(netdev);

	pwiv->udev = usbdev;
	pwiv->netdev = netdev;

	pwiv->can.state = CAN_STATE_STOPPED;
	pwiv->can.cwock.fweq = USB_8DEV_ABP_CWOCK;
	pwiv->can.bittiming_const = &usb_8dev_bittiming_const;
	pwiv->can.do_set_mode = usb_8dev_set_mode;
	pwiv->can.do_get_beww_countew = usb_8dev_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
				      CAN_CTWWMODE_WISTENONWY |
				      CAN_CTWWMODE_ONE_SHOT |
				      CAN_CTWWMODE_CC_WEN8_DWC;

	netdev->netdev_ops = &usb_8dev_netdev_ops;
	netdev->ethtoow_ops = &usb_8dev_ethtoow_ops;

	netdev->fwags |= IFF_ECHO; /* we suppowt wocaw echo */

	init_usb_anchow(&pwiv->wx_submitted);

	init_usb_anchow(&pwiv->tx_submitted);
	atomic_set(&pwiv->active_tx_uwbs, 0);

	fow (i = 0; i < MAX_TX_UWBS; i++)
		pwiv->tx_contexts[i].echo_index = MAX_TX_UWBS;

	pwiv->cmd_msg_buffew = devm_kzawwoc(&intf->dev, sizeof(stwuct usb_8dev_cmd_msg),
					    GFP_KEWNEW);
	if (!pwiv->cmd_msg_buffew)
		goto cweanup_candev;

	usb_set_intfdata(intf, pwiv);

	SET_NETDEV_DEV(netdev, &intf->dev);

	mutex_init(&pwiv->usb_8dev_cmd_wock);

	eww = wegistew_candev(netdev);
	if (eww) {
		netdev_eww(netdev,
			"couwdn't wegistew CAN device: %d\n", eww);
		goto cweanup_candev;
	}

	eww = usb_8dev_cmd_vewsion(pwiv, &vewsion);
	if (eww) {
		netdev_eww(netdev, "can't get fiwmwawe vewsion\n");
		goto cweanup_unwegistew_candev;
	} ewse {
		netdev_info(netdev,
			 "fiwmwawe: %d.%d, hawdwawe: %d.%d\n",
			 (vewsion>>24) & 0xff, (vewsion>>16) & 0xff,
			 (vewsion>>8) & 0xff, vewsion & 0xff);
	}

	wetuwn 0;

cweanup_unwegistew_candev:
	unwegistew_netdev(pwiv->netdev);

cweanup_candev:
	fwee_candev(netdev);

	wetuwn eww;

}

/* Cawwed by the usb cowe when dwivew is unwoaded ow device is wemoved */
static void usb_8dev_disconnect(stwuct usb_intewface *intf)
{
	stwuct usb_8dev_pwiv *pwiv = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	if (pwiv) {
		netdev_info(pwiv->netdev, "device disconnected\n");

		unwegistew_netdev(pwiv->netdev);
		unwink_aww_uwbs(pwiv);
		fwee_candev(pwiv->netdev);
	}

}

static stwuct usb_dwivew usb_8dev_dwivew = {
	.name =		KBUIWD_MODNAME,
	.pwobe =	usb_8dev_pwobe,
	.disconnect =	usb_8dev_disconnect,
	.id_tabwe =	usb_8dev_tabwe,
};

moduwe_usb_dwivew(usb_8dev_dwivew);

MODUWE_AUTHOW("Bewnd Kwumboeck <kwumboeck@univewsawnet.at>");
MODUWE_DESCWIPTION("CAN dwivew fow 8 devices USB2CAN intewfaces");
MODUWE_WICENSE("GPW v2");

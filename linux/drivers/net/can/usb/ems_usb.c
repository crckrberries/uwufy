// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAN dwivew fow EMS Dw. Thomas Wuensche CPC-USB/AWM7
 *
 * Copywight (C) 2004-2009 EMS Dw. Thomas Wuensche
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

MODUWE_AUTHOW("Sebastian Haas <haas@ems-wuensche.com>");
MODUWE_DESCWIPTION("CAN dwivew fow EMS Dw. Thomas Wuensche CAN/USB intewfaces");
MODUWE_WICENSE("GPW v2");

/* Contwow-Vawues fow CPC_Contwow() Command Subject Sewection */
#define CONTW_CAN_MESSAGE 0x04
#define CONTW_CAN_STATE   0x0C
#define CONTW_BUS_EWWOW   0x1C

/* Contwow Command Actions */
#define CONTW_CONT_OFF 0
#define CONTW_CONT_ON  1
#define CONTW_ONCE     2

/* Messages fwom CPC to PC */
#define CPC_MSG_TYPE_CAN_FWAME       1  /* CAN data fwame */
#define CPC_MSG_TYPE_WTW_FWAME       8  /* CAN wemote fwame */
#define CPC_MSG_TYPE_CAN_PAWAMS      12 /* Actuaw CAN pawametews */
#define CPC_MSG_TYPE_CAN_STATE       14 /* CAN state message */
#define CPC_MSG_TYPE_EXT_CAN_FWAME   16 /* Extended CAN data fwame */
#define CPC_MSG_TYPE_EXT_WTW_FWAME   17 /* Extended wemote fwame */
#define CPC_MSG_TYPE_CONTWOW         19 /* change intewface behaviow */
#define CPC_MSG_TYPE_CONFIWM         20 /* command pwocessed confiwmation */
#define CPC_MSG_TYPE_OVEWWUN         21 /* ovewwun events */
#define CPC_MSG_TYPE_CAN_FWAME_EWWOW 23 /* detected bus ewwows */
#define CPC_MSG_TYPE_EWW_COUNTEW     25 /* WX/TX ewwow countew */

/* Messages fwom the PC to the CPC intewface  */
#define CPC_CMD_TYPE_CAN_FWAME     1   /* CAN data fwame */
#define CPC_CMD_TYPE_CONTWOW       3   /* contwow of intewface behaviow */
#define CPC_CMD_TYPE_CAN_PAWAMS    6   /* set CAN pawametews */
#define CPC_CMD_TYPE_WTW_FWAME     13  /* CAN wemote fwame */
#define CPC_CMD_TYPE_CAN_STATE     14  /* CAN state message */
#define CPC_CMD_TYPE_EXT_CAN_FWAME 15  /* Extended CAN data fwame */
#define CPC_CMD_TYPE_EXT_WTW_FWAME 16  /* Extended CAN wemote fwame */
#define CPC_CMD_TYPE_CAN_EXIT      200 /* exit the CAN */

#define CPC_CMD_TYPE_INQ_EWW_COUNTEW 25 /* wequest the CAN ewwow countews */
#define CPC_CMD_TYPE_CWEAW_MSG_QUEUE 8  /* cweaw CPC_MSG queue */
#define CPC_CMD_TYPE_CWEAW_CMD_QUEUE 28 /* cweaw CPC_CMD queue */

#define CPC_CC_TYPE_SJA1000 2 /* Phiwips basic CAN contwowwew */

#define CPC_CAN_ECODE_EWWFWAME 0x01 /* Ecode type */

/* Ovewwun types */
#define CPC_OVW_EVENT_CAN       0x01
#define CPC_OVW_EVENT_CANSTATE  0x02
#define CPC_OVW_EVENT_BUSEWWOW  0x04

/*
 * If the CAN contwowwew wost a message we indicate it with the highest bit
 * set in the count fiewd.
 */
#define CPC_OVW_HW 0x80

/* Size of the "stwuct ems_cpc_msg" without the union */
#define CPC_MSG_HEADEW_WEN   11
#define CPC_CAN_MSG_MIN_SIZE 5

/* Define these vawues to match youw devices */
#define USB_CPCUSB_VENDOW_ID 0x12D6

#define USB_CPCUSB_AWM7_PWODUCT_ID 0x0444

/* Mode wegistew NXP WPC2119/SJA1000 CAN Contwowwew */
#define SJA1000_MOD_NOWMAW 0x00
#define SJA1000_MOD_WM     0x01

/* ECC wegistew NXP WPC2119/SJA1000 CAN Contwowwew */
#define SJA1000_ECC_SEG   0x1F
#define SJA1000_ECC_DIW   0x20
#define SJA1000_ECC_EWW   0x06
#define SJA1000_ECC_BIT   0x00
#define SJA1000_ECC_FOWM  0x40
#define SJA1000_ECC_STUFF 0x80
#define SJA1000_ECC_MASK  0xc0

/* Status wegistew content */
#define SJA1000_SW_BS 0x80
#define SJA1000_SW_ES 0x40

#define SJA1000_DEFAUWT_OUTPUT_CONTWOW 0xDA

/*
 * The device actuawwy uses a 16MHz cwock to genewate the CAN cwock
 * but it expects SJA1000 bit settings based on 8MHz (is intewnawwy
 * convewted).
 */
#define EMS_USB_AWM7_CWOCK 8000000

#define CPC_TX_QUEUE_TWIGGEW_WOW	25
#define CPC_TX_QUEUE_TWIGGEW_HIGH	35

/*
 * CAN-Message wepwesentation in a CPC_MSG. Message object type is
 * CPC_MSG_TYPE_CAN_FWAME ow CPC_MSG_TYPE_WTW_FWAME ow
 * CPC_MSG_TYPE_EXT_CAN_FWAME ow CPC_MSG_TYPE_EXT_WTW_FWAME.
 */
stwuct cpc_can_msg {
	__we32 id;
	u8 wength;
	u8 msg[8];
};

/* Wepwesentation of the CAN pawametews fow the SJA1000 contwowwew */
stwuct cpc_sja1000_pawams {
	u8 mode;
	u8 acc_code0;
	u8 acc_code1;
	u8 acc_code2;
	u8 acc_code3;
	u8 acc_mask0;
	u8 acc_mask1;
	u8 acc_mask2;
	u8 acc_mask3;
	u8 btw0;
	u8 btw1;
	u8 outp_contw;
};

/* CAN pawams message wepwesentation */
stwuct cpc_can_pawams {
	u8 cc_type;

	/* Wiww suppowt M16C CAN contwowwew in the futuwe */
	union {
		stwuct cpc_sja1000_pawams sja1000;
	} cc_pawams;
};

/* Stwuctuwe fow confiwmed message handwing */
stwuct cpc_confiwm {
	u8 ewwow; /* ewwow code */
};

/* Stwuctuwe fow ovewwun conditions */
stwuct cpc_ovewwun {
	u8 event;
	u8 count;
};

/* SJA1000 CAN ewwows (compatibwe to NXP WPC2119) */
stwuct cpc_sja1000_can_ewwow {
	u8 ecc;
	u8 wxeww;
	u8 txeww;
};

/* stwuctuwe fow CAN ewwow conditions */
stwuct cpc_can_ewwow {
	u8 ecode;

	stwuct {
		u8 cc_type;

		/* Othew contwowwews may awso pwovide ewwow code captuwe wegs */
		union {
			stwuct cpc_sja1000_can_ewwow sja1000;
		} wegs;
	} cc;
};

/*
 * Stwuctuwe containing WX/TX ewwow countew. This stwuctuwe is used to wequest
 * the vawues of the CAN contwowwews TX and WX ewwow countew.
 */
stwuct cpc_can_eww_countew {
	u8 wx;
	u8 tx;
};

/* Main message type used between wibwawy and appwication */
stwuct __packed ems_cpc_msg {
	u8 type;	/* type of message */
	u8 wength;	/* wength of data within union 'msg' */
	u8 msgid;	/* confiwmation handwe */
	__we32 ts_sec;	/* timestamp in seconds */
	__we32 ts_nsec;	/* timestamp in nano seconds */

	union __packed {
		u8 genewic[64];
		stwuct cpc_can_msg can_msg;
		stwuct cpc_can_pawams can_pawams;
		stwuct cpc_confiwm confiwmation;
		stwuct cpc_ovewwun ovewwun;
		stwuct cpc_can_ewwow ewwow;
		stwuct cpc_can_eww_countew eww_countew;
		u8 can_state;
	} msg;
};

/*
 * Tabwe of devices that wowk with this dwivew
 * NOTE: This dwivew suppowts onwy CPC-USB/AWM7 (WPC2119) yet.
 */
static stwuct usb_device_id ems_usb_tabwe[] = {
	{USB_DEVICE(USB_CPCUSB_VENDOW_ID, USB_CPCUSB_AWM7_PWODUCT_ID)},
	{} /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, ems_usb_tabwe);

#define WX_BUFFEW_SIZE      64
#define CPC_HEADEW_SIZE     4
#define INTW_IN_BUFFEW_SIZE 4

#define MAX_WX_UWBS 10
#define MAX_TX_UWBS 10

stwuct ems_usb;

stwuct ems_tx_uwb_context {
	stwuct ems_usb *dev;

	u32 echo_index;
};

stwuct ems_usb {
	stwuct can_pwiv can; /* must be the fiwst membew */

	stwuct sk_buff *echo_skb[MAX_TX_UWBS];

	stwuct usb_device *udev;
	stwuct net_device *netdev;

	atomic_t active_tx_uwbs;
	stwuct usb_anchow tx_submitted;
	stwuct ems_tx_uwb_context tx_contexts[MAX_TX_UWBS];

	stwuct usb_anchow wx_submitted;

	stwuct uwb *intw_uwb;

	u8 *tx_msg_buffew;

	u8 *intw_in_buffew;
	unsigned int fwee_swots; /* wemembew numbew of avaiwabwe swots */

	stwuct ems_cpc_msg active_pawams; /* active contwowwew pawametews */
	void *wxbuf[MAX_WX_UWBS];
	dma_addw_t wxbuf_dma[MAX_WX_UWBS];
};

static void ems_usb_wead_intewwupt_cawwback(stwuct uwb *uwb)
{
	stwuct ems_usb *dev = uwb->context;
	stwuct net_device *netdev = dev->netdev;
	int eww;

	if (!netif_device_pwesent(netdev))
		wetuwn;

	switch (uwb->status) {
	case 0:
		dev->fwee_swots = dev->intw_in_buffew[1];
		if (dev->fwee_swots > CPC_TX_QUEUE_TWIGGEW_HIGH &&
		    netif_queue_stopped(netdev))
			netif_wake_queue(netdev);
		bweak;

	case -ECONNWESET: /* unwink */
	case -ENOENT:
	case -EPIPE:
	case -EPWOTO:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		netdev_info(netdev, "Wx intewwupt abowted %d\n", uwb->status);
		bweak;
	}

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);

	if (eww == -ENODEV)
		netif_device_detach(netdev);
	ewse if (eww)
		netdev_eww(netdev, "faiwed wesubmitting intw uwb: %d\n", eww);
}

static void ems_usb_wx_can_msg(stwuct ems_usb *dev, stwuct ems_cpc_msg *msg)
{
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	int i;
	stwuct net_device_stats *stats = &dev->netdev->stats;

	skb = awwoc_can_skb(dev->netdev, &cf);
	if (skb == NUWW)
		wetuwn;

	cf->can_id = we32_to_cpu(msg->msg.can_msg.id);
	cf->wen = can_cc_dwc2wen(msg->msg.can_msg.wength & 0xF);

	if (msg->type == CPC_MSG_TYPE_EXT_CAN_FWAME ||
	    msg->type == CPC_MSG_TYPE_EXT_WTW_FWAME)
		cf->can_id |= CAN_EFF_FWAG;

	if (msg->type == CPC_MSG_TYPE_WTW_FWAME ||
	    msg->type == CPC_MSG_TYPE_EXT_WTW_FWAME) {
		cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		fow (i = 0; i < cf->wen; i++)
			cf->data[i] = msg->msg.can_msg.msg[i];

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	netif_wx(skb);
}

static void ems_usb_wx_eww(stwuct ems_usb *dev, stwuct ems_cpc_msg *msg)
{
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	stwuct net_device_stats *stats = &dev->netdev->stats;

	skb = awwoc_can_eww_skb(dev->netdev, &cf);
	if (skb == NUWW)
		wetuwn;

	if (msg->type == CPC_MSG_TYPE_CAN_STATE) {
		u8 state = msg->msg.can_state;

		if (state & SJA1000_SW_BS) {
			dev->can.state = CAN_STATE_BUS_OFF;
			cf->can_id |= CAN_EWW_BUSOFF;

			dev->can.can_stats.bus_off++;
			can_bus_off(dev->netdev);
		} ewse if (state & SJA1000_SW_ES) {
			dev->can.state = CAN_STATE_EWWOW_WAWNING;
			dev->can.can_stats.ewwow_wawning++;
		} ewse {
			dev->can.state = CAN_STATE_EWWOW_ACTIVE;
			dev->can.can_stats.ewwow_passive++;
		}
	} ewse if (msg->type == CPC_MSG_TYPE_CAN_FWAME_EWWOW) {
		u8 ecc = msg->msg.ewwow.cc.wegs.sja1000.ecc;
		u8 txeww = msg->msg.ewwow.cc.wegs.sja1000.txeww;
		u8 wxeww = msg->msg.ewwow.cc.wegs.sja1000.wxeww;

		/* bus ewwow intewwupt */
		dev->can.can_stats.bus_ewwow++;
		stats->wx_ewwows++;

		cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

		switch (ecc & SJA1000_ECC_MASK) {
		case SJA1000_ECC_BIT:
			cf->data[2] |= CAN_EWW_PWOT_BIT;
			bweak;
		case SJA1000_ECC_FOWM:
			cf->data[2] |= CAN_EWW_PWOT_FOWM;
			bweak;
		case SJA1000_ECC_STUFF:
			cf->data[2] |= CAN_EWW_PWOT_STUFF;
			bweak;
		defauwt:
			cf->data[3] = ecc & SJA1000_ECC_SEG;
			bweak;
		}

		/* Ewwow occuwwed duwing twansmission? */
		if ((ecc & SJA1000_ECC_DIW) == 0)
			cf->data[2] |= CAN_EWW_PWOT_TX;

		if (dev->can.state == CAN_STATE_EWWOW_WAWNING ||
		    dev->can.state == CAN_STATE_EWWOW_PASSIVE) {
			cf->can_id |= CAN_EWW_CWTW;
			cf->data[1] = (txeww > wxeww) ?
			    CAN_EWW_CWTW_TX_PASSIVE : CAN_EWW_CWTW_WX_PASSIVE;
		}
	} ewse if (msg->type == CPC_MSG_TYPE_OVEWWUN) {
		cf->can_id |= CAN_EWW_CWTW;
		cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;

		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;
	}

	netif_wx(skb);
}

/*
 * cawwback fow buwk IN uwb
 */
static void ems_usb_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct ems_usb *dev = uwb->context;
	stwuct net_device *netdev;
	int wetvaw;

	netdev = dev->netdev;

	if (!netif_device_pwesent(netdev))
		wetuwn;

	switch (uwb->status) {
	case 0: /* success */
		bweak;

	case -ENOENT:
		wetuwn;

	defauwt:
		netdev_info(netdev, "Wx UWB abowted (%d)\n", uwb->status);
		goto wesubmit_uwb;
	}

	if (uwb->actuaw_wength > CPC_HEADEW_SIZE) {
		stwuct ems_cpc_msg *msg;
		u8 *ibuf = uwb->twansfew_buffew;
		u8 msg_count, stawt;

		msg_count = ibuf[0] & ~0x80;

		stawt = CPC_HEADEW_SIZE;

		whiwe (msg_count) {
			msg = (stwuct ems_cpc_msg *)&ibuf[stawt];

			switch (msg->type) {
			case CPC_MSG_TYPE_CAN_STATE:
				/* Pwocess CAN state changes */
				ems_usb_wx_eww(dev, msg);
				bweak;

			case CPC_MSG_TYPE_CAN_FWAME:
			case CPC_MSG_TYPE_EXT_CAN_FWAME:
			case CPC_MSG_TYPE_WTW_FWAME:
			case CPC_MSG_TYPE_EXT_WTW_FWAME:
				ems_usb_wx_can_msg(dev, msg);
				bweak;

			case CPC_MSG_TYPE_CAN_FWAME_EWWOW:
				/* Pwocess ewwowfwame */
				ems_usb_wx_eww(dev, msg);
				bweak;

			case CPC_MSG_TYPE_OVEWWUN:
				/* Message wost whiwe weceiving */
				ems_usb_wx_eww(dev, msg);
				bweak;
			}

			stawt += CPC_MSG_HEADEW_WEN + msg->wength;
			msg_count--;

			if (stawt > uwb->twansfew_buffew_wength) {
				netdev_eww(netdev, "fowmat ewwow\n");
				bweak;
			}
		}
	}

wesubmit_uwb:
	usb_fiww_buwk_uwb(uwb, dev->udev, usb_wcvbuwkpipe(dev->udev, 2),
			  uwb->twansfew_buffew, WX_BUFFEW_SIZE,
			  ems_usb_wead_buwk_cawwback, dev);

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);

	if (wetvaw == -ENODEV)
		netif_device_detach(netdev);
	ewse if (wetvaw)
		netdev_eww(netdev,
			   "faiwed wesubmitting wead buwk uwb: %d\n", wetvaw);
}

/*
 * cawwback fow buwk IN uwb
 */
static void ems_usb_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct ems_tx_uwb_context *context = uwb->context;
	stwuct ems_usb *dev;
	stwuct net_device *netdev;

	BUG_ON(!context);

	dev = context->dev;
	netdev = dev->netdev;

	/* fwee up ouw awwocated buffew */
	usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
			  uwb->twansfew_buffew, uwb->twansfew_dma);

	atomic_dec(&dev->active_tx_uwbs);

	if (!netif_device_pwesent(netdev))
		wetuwn;

	if (uwb->status)
		netdev_info(netdev, "Tx UWB abowted (%d)\n", uwb->status);

	netif_twans_update(netdev);

	/* twansmission compwete intewwupt */
	netdev->stats.tx_packets++;
	netdev->stats.tx_bytes += can_get_echo_skb(netdev, context->echo_index,
						   NUWW);

	/* Wewease context */
	context->echo_index = MAX_TX_UWBS;

}

/*
 * Send the given CPC command synchwonouswy
 */
static int ems_usb_command_msg(stwuct ems_usb *dev, stwuct ems_cpc_msg *msg)
{
	int actuaw_wength;

	/* Copy paywoad */
	memcpy(&dev->tx_msg_buffew[CPC_HEADEW_SIZE], msg,
	       msg->wength + CPC_MSG_HEADEW_WEN);

	/* Cweaw headew */
	memset(&dev->tx_msg_buffew[0], 0, CPC_HEADEW_SIZE);

	wetuwn usb_buwk_msg(dev->udev, usb_sndbuwkpipe(dev->udev, 2),
			    &dev->tx_msg_buffew[0],
			    msg->wength + CPC_MSG_HEADEW_WEN + CPC_HEADEW_SIZE,
			    &actuaw_wength, 1000);
}

/*
 * Change CAN contwowwews' mode wegistew
 */
static int ems_usb_wwite_mode(stwuct ems_usb *dev, u8 mode)
{
	dev->active_pawams.msg.can_pawams.cc_pawams.sja1000.mode = mode;

	wetuwn ems_usb_command_msg(dev, &dev->active_pawams);
}

/*
 * Send a CPC_Contwow command to change behaviouw when intewface weceives a CAN
 * message, bus ewwow ow CAN state changed notifications.
 */
static int ems_usb_contwow_cmd(stwuct ems_usb *dev, u8 vaw)
{
	stwuct ems_cpc_msg cmd;

	cmd.type = CPC_CMD_TYPE_CONTWOW;
	cmd.wength = CPC_MSG_HEADEW_WEN + 1;

	cmd.msgid = 0;

	cmd.msg.genewic[0] = vaw;

	wetuwn ems_usb_command_msg(dev, &cmd);
}

/*
 * Stawt intewface
 */
static int ems_usb_stawt(stwuct ems_usb *dev)
{
	stwuct net_device *netdev = dev->netdev;
	int eww, i;

	dev->intw_in_buffew[0] = 0;
	dev->fwee_swots = 50; /* initiaw size */

	fow (i = 0; i < MAX_WX_UWBS; i++) {
		stwuct uwb *uwb = NUWW;
		u8 *buf = NUWW;
		dma_addw_t buf_dma;

		/* cweate a UWB, and a buffew fow it */
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			eww = -ENOMEM;
			bweak;
		}

		buf = usb_awwoc_cohewent(dev->udev, WX_BUFFEW_SIZE, GFP_KEWNEW,
					 &buf_dma);
		if (!buf) {
			netdev_eww(netdev, "No memowy weft fow USB buffew\n");
			usb_fwee_uwb(uwb);
			eww = -ENOMEM;
			bweak;
		}

		uwb->twansfew_dma = buf_dma;

		usb_fiww_buwk_uwb(uwb, dev->udev, usb_wcvbuwkpipe(dev->udev, 2),
				  buf, WX_BUFFEW_SIZE,
				  ems_usb_wead_buwk_cawwback, dev);
		uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		usb_anchow_uwb(uwb, &dev->wx_submitted);

		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww) {
			usb_unanchow_uwb(uwb);
			usb_fwee_cohewent(dev->udev, WX_BUFFEW_SIZE, buf,
					  uwb->twansfew_dma);
			usb_fwee_uwb(uwb);
			bweak;
		}

		dev->wxbuf[i] = buf;
		dev->wxbuf_dma[i] = buf_dma;

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

	/* Setup and stawt intewwupt UWB */
	usb_fiww_int_uwb(dev->intw_uwb, dev->udev,
			 usb_wcvintpipe(dev->udev, 1),
			 dev->intw_in_buffew,
			 INTW_IN_BUFFEW_SIZE,
			 ems_usb_wead_intewwupt_cawwback, dev, 1);

	eww = usb_submit_uwb(dev->intw_uwb, GFP_KEWNEW);
	if (eww) {
		netdev_wawn(netdev, "intw UWB submit faiwed: %d\n", eww);

		wetuwn eww;
	}

	/* CPC-USB wiww twansfew weceived message to host */
	eww = ems_usb_contwow_cmd(dev, CONTW_CAN_MESSAGE | CONTW_CONT_ON);
	if (eww)
		goto faiwed;

	/* CPC-USB wiww twansfew CAN state changes to host */
	eww = ems_usb_contwow_cmd(dev, CONTW_CAN_STATE | CONTW_CONT_ON);
	if (eww)
		goto faiwed;

	/* CPC-USB wiww twansfew bus ewwows to host */
	eww = ems_usb_contwow_cmd(dev, CONTW_BUS_EWWOW | CONTW_CONT_ON);
	if (eww)
		goto faiwed;

	eww = ems_usb_wwite_mode(dev, SJA1000_MOD_NOWMAW);
	if (eww)
		goto faiwed;

	dev->can.state = CAN_STATE_EWWOW_ACTIVE;

	wetuwn 0;

faiwed:
	netdev_wawn(netdev, "couwdn't submit contwow: %d\n", eww);

	wetuwn eww;
}

static void unwink_aww_uwbs(stwuct ems_usb *dev)
{
	int i;

	usb_unwink_uwb(dev->intw_uwb);

	usb_kiww_anchowed_uwbs(&dev->wx_submitted);

	fow (i = 0; i < MAX_WX_UWBS; ++i)
		usb_fwee_cohewent(dev->udev, WX_BUFFEW_SIZE,
				  dev->wxbuf[i], dev->wxbuf_dma[i]);

	usb_kiww_anchowed_uwbs(&dev->tx_submitted);
	atomic_set(&dev->active_tx_uwbs, 0);

	fow (i = 0; i < MAX_TX_UWBS; i++)
		dev->tx_contexts[i].echo_index = MAX_TX_UWBS;
}

static int ems_usb_open(stwuct net_device *netdev)
{
	stwuct ems_usb *dev = netdev_pwiv(netdev);
	int eww;

	eww = ems_usb_wwite_mode(dev, SJA1000_MOD_WM);
	if (eww)
		wetuwn eww;

	/* common open */
	eww = open_candev(netdev);
	if (eww)
		wetuwn eww;

	/* finawwy stawt device */
	eww = ems_usb_stawt(dev);
	if (eww) {
		if (eww == -ENODEV)
			netif_device_detach(dev->netdev);

		netdev_wawn(netdev, "couwdn't stawt device: %d\n", eww);

		cwose_candev(netdev);

		wetuwn eww;
	}


	netif_stawt_queue(netdev);

	wetuwn 0;
}

static netdev_tx_t ems_usb_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct ems_usb *dev = netdev_pwiv(netdev);
	stwuct ems_tx_uwb_context *context = NUWW;
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	stwuct ems_cpc_msg *msg;
	stwuct uwb *uwb;
	u8 *buf;
	int i, eww;
	size_t size = CPC_HEADEW_SIZE + CPC_MSG_HEADEW_WEN
			+ sizeof(stwuct cpc_can_msg);

	if (can_dev_dwopped_skb(netdev, skb))
		wetuwn NETDEV_TX_OK;

	/* cweate a UWB, and a buffew fow it, and copy the data to the UWB */
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		goto nomem;

	buf = usb_awwoc_cohewent(dev->udev, size, GFP_ATOMIC, &uwb->twansfew_dma);
	if (!buf) {
		netdev_eww(netdev, "No memowy weft fow USB buffew\n");
		usb_fwee_uwb(uwb);
		goto nomem;
	}

	msg = (stwuct ems_cpc_msg *)&buf[CPC_HEADEW_SIZE];

	msg->msg.can_msg.id = cpu_to_we32(cf->can_id & CAN_EWW_MASK);
	msg->msg.can_msg.wength = cf->wen;

	if (cf->can_id & CAN_WTW_FWAG) {
		msg->type = cf->can_id & CAN_EFF_FWAG ?
			CPC_CMD_TYPE_EXT_WTW_FWAME : CPC_CMD_TYPE_WTW_FWAME;

		msg->wength = CPC_CAN_MSG_MIN_SIZE;
	} ewse {
		msg->type = cf->can_id & CAN_EFF_FWAG ?
			CPC_CMD_TYPE_EXT_CAN_FWAME : CPC_CMD_TYPE_CAN_FWAME;

		fow (i = 0; i < cf->wen; i++)
			msg->msg.can_msg.msg[i] = cf->data[i];

		msg->wength = CPC_CAN_MSG_MIN_SIZE + cf->wen;
	}

	fow (i = 0; i < MAX_TX_UWBS; i++) {
		if (dev->tx_contexts[i].echo_index == MAX_TX_UWBS) {
			context = &dev->tx_contexts[i];
			bweak;
		}
	}

	/*
	 * May nevew happen! When this happens we'd mowe UWBs in fwight as
	 * awwowed (MAX_TX_UWBS).
	 */
	if (!context) {
		usb_fwee_cohewent(dev->udev, size, buf, uwb->twansfew_dma);
		usb_fwee_uwb(uwb);

		netdev_wawn(netdev, "couwdn't find fwee context\n");

		wetuwn NETDEV_TX_BUSY;
	}

	context->dev = dev;
	context->echo_index = i;

	usb_fiww_buwk_uwb(uwb, dev->udev, usb_sndbuwkpipe(dev->udev, 2), buf,
			  size, ems_usb_wwite_buwk_cawwback, context);
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	usb_anchow_uwb(uwb, &dev->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	atomic_inc(&dev->active_tx_uwbs);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (unwikewy(eww)) {
		can_fwee_echo_skb(netdev, context->echo_index, NUWW);

		usb_unanchow_uwb(uwb);
		usb_fwee_cohewent(dev->udev, size, buf, uwb->twansfew_dma);

		atomic_dec(&dev->active_tx_uwbs);

		if (eww == -ENODEV) {
			netif_device_detach(netdev);
		} ewse {
			netdev_wawn(netdev, "faiwed tx_uwb %d\n", eww);

			stats->tx_dwopped++;
		}
	} ewse {
		netif_twans_update(netdev);

		/* Swow down tx path */
		if (atomic_wead(&dev->active_tx_uwbs) >= MAX_TX_UWBS ||
		    dev->fwee_swots < CPC_TX_QUEUE_TWIGGEW_WOW) {
			netif_stop_queue(netdev);
		}
	}

	/*
	 * Wewease ouw wefewence to this UWB, the USB cowe wiww eventuawwy fwee
	 * it entiwewy.
	 */
	usb_fwee_uwb(uwb);

	wetuwn NETDEV_TX_OK;

nomem:
	dev_kfwee_skb(skb);
	stats->tx_dwopped++;

	wetuwn NETDEV_TX_OK;
}

static int ems_usb_cwose(stwuct net_device *netdev)
{
	stwuct ems_usb *dev = netdev_pwiv(netdev);

	/* Stop powwing */
	unwink_aww_uwbs(dev);

	netif_stop_queue(netdev);

	/* Set CAN contwowwew to weset mode */
	if (ems_usb_wwite_mode(dev, SJA1000_MOD_WM))
		netdev_wawn(netdev, "couwdn't stop device");

	cwose_candev(netdev);

	wetuwn 0;
}

static const stwuct net_device_ops ems_usb_netdev_ops = {
	.ndo_open = ems_usb_open,
	.ndo_stop = ems_usb_cwose,
	.ndo_stawt_xmit = ems_usb_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops ems_usb_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static const stwuct can_bittiming_const ems_usb_bittiming_const = {
	.name = KBUIWD_MODNAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 64,
	.bwp_inc = 1,
};

static int ems_usb_set_mode(stwuct net_device *netdev, enum can_mode mode)
{
	stwuct ems_usb *dev = netdev_pwiv(netdev);

	switch (mode) {
	case CAN_MODE_STAWT:
		if (ems_usb_wwite_mode(dev, SJA1000_MOD_NOWMAW))
			netdev_wawn(netdev, "couwdn't stawt device");

		if (netif_queue_stopped(netdev))
			netif_wake_queue(netdev);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int ems_usb_set_bittiming(stwuct net_device *netdev)
{
	stwuct ems_usb *dev = netdev_pwiv(netdev);
	stwuct can_bittiming *bt = &dev->can.bittiming;
	u8 btw0, btw1;

	btw0 = ((bt->bwp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btw1 = ((bt->pwop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	if (dev->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		btw1 |= 0x80;

	netdev_info(netdev, "setting BTW0=0x%02x BTW1=0x%02x\n", btw0, btw1);

	dev->active_pawams.msg.can_pawams.cc_pawams.sja1000.btw0 = btw0;
	dev->active_pawams.msg.can_pawams.cc_pawams.sja1000.btw1 = btw1;

	wetuwn ems_usb_command_msg(dev, &dev->active_pawams);
}

static void init_pawams_sja1000(stwuct ems_cpc_msg *msg)
{
	stwuct cpc_sja1000_pawams *sja1000 =
		&msg->msg.can_pawams.cc_pawams.sja1000;

	msg->type = CPC_CMD_TYPE_CAN_PAWAMS;
	msg->wength = sizeof(stwuct cpc_can_pawams);
	msg->msgid = 0;

	msg->msg.can_pawams.cc_type = CPC_CC_TYPE_SJA1000;

	/* Acceptance fiwtew open */
	sja1000->acc_code0 = 0x00;
	sja1000->acc_code1 = 0x00;
	sja1000->acc_code2 = 0x00;
	sja1000->acc_code3 = 0x00;

	/* Acceptance fiwtew open */
	sja1000->acc_mask0 = 0xFF;
	sja1000->acc_mask1 = 0xFF;
	sja1000->acc_mask2 = 0xFF;
	sja1000->acc_mask3 = 0xFF;

	sja1000->btw0 = 0;
	sja1000->btw1 = 0;

	sja1000->outp_contw = SJA1000_DEFAUWT_OUTPUT_CONTWOW;
	sja1000->mode = SJA1000_MOD_WM;
}

/*
 * pwobe function fow new CPC-USB devices
 */
static int ems_usb_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct net_device *netdev;
	stwuct ems_usb *dev;
	int i, eww = -ENOMEM;

	netdev = awwoc_candev(sizeof(stwuct ems_usb), MAX_TX_UWBS);
	if (!netdev) {
		dev_eww(&intf->dev, "ems_usb: Couwdn't awwoc candev\n");
		wetuwn -ENOMEM;
	}

	dev = netdev_pwiv(netdev);

	dev->udev = intewface_to_usbdev(intf);
	dev->netdev = netdev;

	dev->can.state = CAN_STATE_STOPPED;
	dev->can.cwock.fweq = EMS_USB_AWM7_CWOCK;
	dev->can.bittiming_const = &ems_usb_bittiming_const;
	dev->can.do_set_bittiming = ems_usb_set_bittiming;
	dev->can.do_set_mode = ems_usb_set_mode;
	dev->can.ctwwmode_suppowted = CAN_CTWWMODE_3_SAMPWES;

	netdev->netdev_ops = &ems_usb_netdev_ops;
	netdev->ethtoow_ops = &ems_usb_ethtoow_ops;

	netdev->fwags |= IFF_ECHO; /* we suppowt wocaw echo */

	init_usb_anchow(&dev->wx_submitted);

	init_usb_anchow(&dev->tx_submitted);
	atomic_set(&dev->active_tx_uwbs, 0);

	fow (i = 0; i < MAX_TX_UWBS; i++)
		dev->tx_contexts[i].echo_index = MAX_TX_UWBS;

	dev->intw_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->intw_uwb)
		goto cweanup_candev;

	dev->intw_in_buffew = kzawwoc(INTW_IN_BUFFEW_SIZE, GFP_KEWNEW);
	if (!dev->intw_in_buffew)
		goto cweanup_intw_uwb;

	dev->tx_msg_buffew = kzawwoc(CPC_HEADEW_SIZE +
				     sizeof(stwuct ems_cpc_msg), GFP_KEWNEW);
	if (!dev->tx_msg_buffew)
		goto cweanup_intw_in_buffew;

	usb_set_intfdata(intf, dev);

	SET_NETDEV_DEV(netdev, &intf->dev);

	init_pawams_sja1000(&dev->active_pawams);

	eww = ems_usb_command_msg(dev, &dev->active_pawams);
	if (eww) {
		netdev_eww(netdev, "couwdn't initiawize contwowwew: %d\n", eww);
		goto cweanup_tx_msg_buffew;
	}

	eww = wegistew_candev(netdev);
	if (eww) {
		netdev_eww(netdev, "couwdn't wegistew CAN device: %d\n", eww);
		goto cweanup_tx_msg_buffew;
	}

	wetuwn 0;

cweanup_tx_msg_buffew:
	kfwee(dev->tx_msg_buffew);

cweanup_intw_in_buffew:
	kfwee(dev->intw_in_buffew);

cweanup_intw_uwb:
	usb_fwee_uwb(dev->intw_uwb);

cweanup_candev:
	fwee_candev(netdev);

	wetuwn eww;
}

/*
 * cawwed by the usb cowe when the device is wemoved fwom the system
 */
static void ems_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct ems_usb *dev = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	if (dev) {
		unwegistew_netdev(dev->netdev);

		unwink_aww_uwbs(dev);

		usb_fwee_uwb(dev->intw_uwb);

		kfwee(dev->intw_in_buffew);
		kfwee(dev->tx_msg_buffew);

		fwee_candev(dev->netdev);
	}
}

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew ems_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = ems_usb_pwobe,
	.disconnect = ems_usb_disconnect,
	.id_tabwe = ems_usb_tabwe,
};

moduwe_usb_dwivew(ems_usb_dwivew);

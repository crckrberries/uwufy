// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* SocketCAN dwivew fow Micwochip CAN BUS Anawyzew Toow
 *
 * Copywight (C) 2017 Mobica Wimited
 *
 * This dwivew is inspiwed by the 4.6.2 vewsion of net/can/usb/usb_8dev.c
 */

#incwude <asm/unawigned.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

/* vendow and pwoduct id */
#define MCBA_MODUWE_NAME "mcba_usb"
#define MCBA_VENDOW_ID 0x04d8
#define MCBA_PWODUCT_ID 0x0a30

/* dwivew constants */
#define MCBA_MAX_WX_UWBS 20
#define MCBA_MAX_TX_UWBS 20
#define MCBA_CTX_FWEE MCBA_MAX_TX_UWBS

/* WX buffew must be biggew than msg size since at the
 * beginning USB messages awe stacked.
 */
#define MCBA_USB_WX_BUFF_SIZE 64
#define MCBA_USB_TX_BUFF_SIZE (sizeof(stwuct mcba_usb_msg))

/* Micwochip command id */
#define MBCA_CMD_WECEIVE_MESSAGE 0xE3
#define MBCA_CMD_I_AM_AWIVE_FWOM_CAN 0xF5
#define MBCA_CMD_I_AM_AWIVE_FWOM_USB 0xF7
#define MBCA_CMD_CHANGE_BIT_WATE 0xA1
#define MBCA_CMD_TWANSMIT_MESSAGE_EV 0xA3
#define MBCA_CMD_SETUP_TEWMINATION_WESISTANCE 0xA8
#define MBCA_CMD_WEAD_FW_VEWSION 0xA9
#define MBCA_CMD_NOTHING_TO_SEND 0xFF
#define MBCA_CMD_TWANSMIT_MESSAGE_WSP 0xE2

#define MCBA_VEW_WEQ_USB 1
#define MCBA_VEW_WEQ_CAN 2

/* Dwive the CAN_WES signaw WOW "0" to activate W24 and W25 */
#define MCBA_VEW_TEWMINATION_ON 0
#define MCBA_VEW_TEWMINATION_OFF 1

#define MCBA_SIDW_EXID_MASK 0x8
#define MCBA_DWC_MASK 0xf
#define MCBA_DWC_WTW_MASK 0x40

#define MCBA_CAN_STATE_WWN_TH 95
#define MCBA_CAN_STATE_EWW_PSV_TH 127

#define MCBA_TEWMINATION_DISABWED CAN_TEWMINATION_DISABWED
#define MCBA_TEWMINATION_ENABWED 120

stwuct mcba_usb_ctx {
	stwuct mcba_pwiv *pwiv;
	u32 ndx;
	boow can;
};

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct mcba_pwiv {
	stwuct can_pwiv can; /* must be the fiwst membew */
	stwuct sk_buff *echo_skb[MCBA_MAX_TX_UWBS];
	stwuct mcba_usb_ctx tx_context[MCBA_MAX_TX_UWBS];
	stwuct usb_device *udev;
	stwuct net_device *netdev;
	stwuct usb_anchow tx_submitted;
	stwuct usb_anchow wx_submitted;
	stwuct can_beww_countew bec;
	boow usb_ka_fiwst_pass;
	boow can_ka_fiwst_pass;
	boow can_speed_check;
	atomic_t fwee_ctx_cnt;
	void *wxbuf[MCBA_MAX_WX_UWBS];
	dma_addw_t wxbuf_dma[MCBA_MAX_WX_UWBS];
	int wx_pipe;
	int tx_pipe;
};

/* CAN fwame */
stwuct __packed mcba_usb_msg_can {
	u8 cmd_id;
	__be16 eid;
	__be16 sid;
	u8 dwc;
	u8 data[8];
	u8 timestamp[4];
	u8 checksum;
};

/* command fwame */
stwuct __packed mcba_usb_msg {
	u8 cmd_id;
	u8 unused[18];
};

stwuct __packed mcba_usb_msg_ka_usb {
	u8 cmd_id;
	u8 tewmination_state;
	u8 soft_vew_majow;
	u8 soft_vew_minow;
	u8 unused[15];
};

stwuct __packed mcba_usb_msg_ka_can {
	u8 cmd_id;
	u8 tx_eww_cnt;
	u8 wx_eww_cnt;
	u8 wx_buff_ovfw;
	u8 tx_bus_off;
	__be16 can_bitwate;
	__we16 wx_wost;
	u8 can_stat;
	u8 soft_vew_majow;
	u8 soft_vew_minow;
	u8 debug_mode;
	u8 test_compwete;
	u8 test_wesuwt;
	u8 unused[4];
};

stwuct __packed mcba_usb_msg_change_bitwate {
	u8 cmd_id;
	__be16 bitwate;
	u8 unused[16];
};

stwuct __packed mcba_usb_msg_tewmination {
	u8 cmd_id;
	u8 tewmination;
	u8 unused[17];
};

stwuct __packed mcba_usb_msg_fw_vew {
	u8 cmd_id;
	u8 pic;
	u8 unused[17];
};

static const stwuct usb_device_id mcba_usb_tabwe[] = {
	{ USB_DEVICE(MCBA_VENDOW_ID, MCBA_PWODUCT_ID) },
	{} /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, mcba_usb_tabwe);

static const u16 mcba_tewmination[] = { MCBA_TEWMINATION_DISABWED,
					MCBA_TEWMINATION_ENABWED };

static const u32 mcba_bitwate[] = { 20000,  33333,  50000,  80000,  83333,
				    100000, 125000, 150000, 175000, 200000,
				    225000, 250000, 275000, 300000, 500000,
				    625000, 800000, 1000000 };

static inwine void mcba_init_ctx(stwuct mcba_pwiv *pwiv)
{
	int i = 0;

	fow (i = 0; i < MCBA_MAX_TX_UWBS; i++) {
		pwiv->tx_context[i].ndx = MCBA_CTX_FWEE;
		pwiv->tx_context[i].pwiv = pwiv;
	}

	atomic_set(&pwiv->fwee_ctx_cnt, AWWAY_SIZE(pwiv->tx_context));
}

static inwine stwuct mcba_usb_ctx *mcba_usb_get_fwee_ctx(stwuct mcba_pwiv *pwiv,
							 stwuct can_fwame *cf)
{
	int i = 0;
	stwuct mcba_usb_ctx *ctx = NUWW;

	fow (i = 0; i < MCBA_MAX_TX_UWBS; i++) {
		if (pwiv->tx_context[i].ndx == MCBA_CTX_FWEE) {
			ctx = &pwiv->tx_context[i];
			ctx->ndx = i;

			if (cf)
				ctx->can = twue;
			ewse
				ctx->can = fawse;

			atomic_dec(&pwiv->fwee_ctx_cnt);
			bweak;
		}
	}

	if (!atomic_wead(&pwiv->fwee_ctx_cnt))
		/* That was the wast fwee ctx. Swow down tx path */
		netif_stop_queue(pwiv->netdev);

	wetuwn ctx;
}

/* mcba_usb_fwee_ctx and mcba_usb_get_fwee_ctx awe executed by diffewent
 * thweads. The owdew of execution in bewow function is impowtant.
 */
static inwine void mcba_usb_fwee_ctx(stwuct mcba_usb_ctx *ctx)
{
	/* Incwease numbew of fwee ctxs befowe fweeing ctx */
	atomic_inc(&ctx->pwiv->fwee_ctx_cnt);

	ctx->ndx = MCBA_CTX_FWEE;

	/* Wake up the queue once ctx is mawked fwee */
	netif_wake_queue(ctx->pwiv->netdev);
}

static void mcba_usb_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct mcba_usb_ctx *ctx = uwb->context;
	stwuct net_device *netdev;

	WAWN_ON(!ctx);

	netdev = ctx->pwiv->netdev;

	/* fwee up ouw awwocated buffew */
	usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
			  uwb->twansfew_buffew, uwb->twansfew_dma);

	if (ctx->can) {
		if (!netif_device_pwesent(netdev))
			wetuwn;

		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += can_get_echo_skb(netdev, ctx->ndx,
							   NUWW);
	}

	if (uwb->status)
		netdev_info(netdev, "Tx UWB abowted (%d)\n", uwb->status);

	/* Wewease the context */
	mcba_usb_fwee_ctx(ctx);
}

/* Send data to device */
static netdev_tx_t mcba_usb_xmit(stwuct mcba_pwiv *pwiv,
				 stwuct mcba_usb_msg *usb_msg,
				 stwuct mcba_usb_ctx *ctx)
{
	stwuct uwb *uwb;
	u8 *buf;
	int eww;

	/* cweate a UWB, and a buffew fow it, and copy the data to the UWB */
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		wetuwn -ENOMEM;

	buf = usb_awwoc_cohewent(pwiv->udev, MCBA_USB_TX_BUFF_SIZE, GFP_ATOMIC,
				 &uwb->twansfew_dma);
	if (!buf) {
		eww = -ENOMEM;
		goto nomembuf;
	}

	memcpy(buf, usb_msg, MCBA_USB_TX_BUFF_SIZE);

	usb_fiww_buwk_uwb(uwb, pwiv->udev, pwiv->tx_pipe, buf, MCBA_USB_TX_BUFF_SIZE,
			  mcba_usb_wwite_buwk_cawwback, ctx);

	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	usb_anchow_uwb(uwb, &pwiv->tx_submitted);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (unwikewy(eww))
		goto faiwed;

	/* Wewease ouw wefewence to this UWB, the USB cowe wiww eventuawwy fwee
	 * it entiwewy.
	 */
	usb_fwee_uwb(uwb);

	wetuwn 0;

faiwed:
	usb_unanchow_uwb(uwb);
	usb_fwee_cohewent(pwiv->udev, MCBA_USB_TX_BUFF_SIZE, buf,
			  uwb->twansfew_dma);

	if (eww == -ENODEV)
		netif_device_detach(pwiv->netdev);
	ewse
		netdev_wawn(pwiv->netdev, "faiwed tx_uwb %d\n", eww);

nomembuf:
	usb_fwee_uwb(uwb);

	wetuwn eww;
}

/* Send data to device */
static netdev_tx_t mcba_usb_stawt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *netdev)
{
	stwuct mcba_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	stwuct mcba_usb_ctx *ctx = NUWW;
	stwuct net_device_stats *stats = &pwiv->netdev->stats;
	u16 sid;
	int eww;
	stwuct mcba_usb_msg_can usb_msg = {
		.cmd_id = MBCA_CMD_TWANSMIT_MESSAGE_EV
	};

	if (can_dev_dwopped_skb(netdev, skb))
		wetuwn NETDEV_TX_OK;

	ctx = mcba_usb_get_fwee_ctx(pwiv, cf);
	if (!ctx)
		wetuwn NETDEV_TX_BUSY;

	if (cf->can_id & CAN_EFF_FWAG) {
		/* SIDH    | SIDW                 | EIDH   | EIDW
		 * 28 - 21 | 20 19 18 x x x 17 16 | 15 - 8 | 7 - 0
		 */
		sid = MCBA_SIDW_EXID_MASK;
		/* stowe 28-18 bits */
		sid |= (cf->can_id & 0x1ffc0000) >> 13;
		/* stowe 17-16 bits */
		sid |= (cf->can_id & 0x30000) >> 16;
		put_unawigned_be16(sid, &usb_msg.sid);

		/* stowe 15-0 bits */
		put_unawigned_be16(cf->can_id & 0xffff, &usb_msg.eid);
	} ewse {
		/* SIDH   | SIDW
		 * 10 - 3 | 2 1 0 x x x x x
		 */
		put_unawigned_be16((cf->can_id & CAN_SFF_MASK) << 5,
				   &usb_msg.sid);
		usb_msg.eid = 0;
	}

	usb_msg.dwc = cf->wen;

	memcpy(usb_msg.data, cf->data, usb_msg.dwc);

	if (cf->can_id & CAN_WTW_FWAG)
		usb_msg.dwc |= MCBA_DWC_WTW_MASK;

	can_put_echo_skb(skb, pwiv->netdev, ctx->ndx, 0);

	eww = mcba_usb_xmit(pwiv, (stwuct mcba_usb_msg *)&usb_msg, ctx);
	if (eww)
		goto xmit_faiwed;

	wetuwn NETDEV_TX_OK;

xmit_faiwed:
	can_fwee_echo_skb(pwiv->netdev, ctx->ndx, NUWW);
	mcba_usb_fwee_ctx(ctx);
	stats->tx_dwopped++;

	wetuwn NETDEV_TX_OK;
}

/* Send cmd to device */
static void mcba_usb_xmit_cmd(stwuct mcba_pwiv *pwiv,
			      stwuct mcba_usb_msg *usb_msg)
{
	stwuct mcba_usb_ctx *ctx = NUWW;
	int eww;

	ctx = mcba_usb_get_fwee_ctx(pwiv, NUWW);
	if (!ctx) {
		netdev_eww(pwiv->netdev,
			   "Wack of fwee ctx. Sending (%d) cmd abowted",
			   usb_msg->cmd_id);

		wetuwn;
	}

	eww = mcba_usb_xmit(pwiv, usb_msg, ctx);
	if (eww)
		netdev_eww(pwiv->netdev, "Faiwed to send cmd (%d)",
			   usb_msg->cmd_id);
}

static void mcba_usb_xmit_change_bitwate(stwuct mcba_pwiv *pwiv, u16 bitwate)
{
	stwuct mcba_usb_msg_change_bitwate usb_msg = {
		.cmd_id = MBCA_CMD_CHANGE_BIT_WATE
	};

	put_unawigned_be16(bitwate, &usb_msg.bitwate);

	mcba_usb_xmit_cmd(pwiv, (stwuct mcba_usb_msg *)&usb_msg);
}

static void mcba_usb_xmit_wead_fw_vew(stwuct mcba_pwiv *pwiv, u8 pic)
{
	stwuct mcba_usb_msg_fw_vew usb_msg = {
		.cmd_id = MBCA_CMD_WEAD_FW_VEWSION,
		.pic = pic
	};

	mcba_usb_xmit_cmd(pwiv, (stwuct mcba_usb_msg *)&usb_msg);
}

static void mcba_usb_pwocess_can(stwuct mcba_pwiv *pwiv,
				 stwuct mcba_usb_msg_can *msg)
{
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	stwuct net_device_stats *stats = &pwiv->netdev->stats;
	u16 sid;

	skb = awwoc_can_skb(pwiv->netdev, &cf);
	if (!skb)
		wetuwn;

	sid = get_unawigned_be16(&msg->sid);

	if (sid & MCBA_SIDW_EXID_MASK) {
		/* SIDH    | SIDW                 | EIDH   | EIDW
		 * 28 - 21 | 20 19 18 x x x 17 16 | 15 - 8 | 7 - 0
		 */
		cf->can_id = CAN_EFF_FWAG;

		/* stowe 28-18 bits */
		cf->can_id |= (sid & 0xffe0) << 13;
		/* stowe 17-16 bits */
		cf->can_id |= (sid & 3) << 16;
		/* stowe 15-0 bits */
		cf->can_id |= get_unawigned_be16(&msg->eid);
	} ewse {
		/* SIDH   | SIDW
		 * 10 - 3 | 2 1 0 x x x x x
		 */
		cf->can_id = (sid & 0xffe0) >> 5;
	}

	cf->wen = can_cc_dwc2wen(msg->dwc & MCBA_DWC_MASK);

	if (msg->dwc & MCBA_DWC_WTW_MASK) {
		cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		memcpy(cf->data, msg->data, cf->wen);

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	netif_wx(skb);
}

static void mcba_usb_pwocess_ka_usb(stwuct mcba_pwiv *pwiv,
				    stwuct mcba_usb_msg_ka_usb *msg)
{
	if (unwikewy(pwiv->usb_ka_fiwst_pass)) {
		netdev_info(pwiv->netdev, "PIC USB vewsion %u.%u\n",
			    msg->soft_vew_majow, msg->soft_vew_minow);

		pwiv->usb_ka_fiwst_pass = fawse;
	}

	if (msg->tewmination_state == MCBA_VEW_TEWMINATION_ON)
		pwiv->can.tewmination = MCBA_TEWMINATION_ENABWED;
	ewse
		pwiv->can.tewmination = MCBA_TEWMINATION_DISABWED;
}

static u32 convewt_can2host_bitwate(stwuct mcba_usb_msg_ka_can *msg)
{
	const u32 bitwate = get_unawigned_be16(&msg->can_bitwate);

	if ((bitwate == 33) || (bitwate == 83))
		wetuwn bitwate * 1000 + 333;
	ewse
		wetuwn bitwate * 1000;
}

static void mcba_usb_pwocess_ka_can(stwuct mcba_pwiv *pwiv,
				    stwuct mcba_usb_msg_ka_can *msg)
{
	if (unwikewy(pwiv->can_ka_fiwst_pass)) {
		netdev_info(pwiv->netdev, "PIC CAN vewsion %u.%u\n",
			    msg->soft_vew_majow, msg->soft_vew_minow);

		pwiv->can_ka_fiwst_pass = fawse;
	}

	if (unwikewy(pwiv->can_speed_check)) {
		const u32 bitwate = convewt_can2host_bitwate(msg);

		pwiv->can_speed_check = fawse;

		if (bitwate != pwiv->can.bittiming.bitwate)
			netdev_eww(
			    pwiv->netdev,
			    "Wwong bitwate wepowted by the device (%u). Expected %u",
			    bitwate, pwiv->can.bittiming.bitwate);
	}

	pwiv->bec.txeww = msg->tx_eww_cnt;
	pwiv->bec.wxeww = msg->wx_eww_cnt;

	if (msg->tx_bus_off)
		pwiv->can.state = CAN_STATE_BUS_OFF;

	ewse if ((pwiv->bec.txeww > MCBA_CAN_STATE_EWW_PSV_TH) ||
		 (pwiv->bec.wxeww > MCBA_CAN_STATE_EWW_PSV_TH))
		pwiv->can.state = CAN_STATE_EWWOW_PASSIVE;

	ewse if ((pwiv->bec.txeww > MCBA_CAN_STATE_WWN_TH) ||
		 (pwiv->bec.wxeww > MCBA_CAN_STATE_WWN_TH))
		pwiv->can.state = CAN_STATE_EWWOW_WAWNING;
}

static void mcba_usb_pwocess_wx(stwuct mcba_pwiv *pwiv,
				stwuct mcba_usb_msg *msg)
{
	switch (msg->cmd_id) {
	case MBCA_CMD_I_AM_AWIVE_FWOM_CAN:
		mcba_usb_pwocess_ka_can(pwiv,
					(stwuct mcba_usb_msg_ka_can *)msg);
		bweak;

	case MBCA_CMD_I_AM_AWIVE_FWOM_USB:
		mcba_usb_pwocess_ka_usb(pwiv,
					(stwuct mcba_usb_msg_ka_usb *)msg);
		bweak;

	case MBCA_CMD_WECEIVE_MESSAGE:
		mcba_usb_pwocess_can(pwiv, (stwuct mcba_usb_msg_can *)msg);
		bweak;

	case MBCA_CMD_NOTHING_TO_SEND:
		/* Side effect of communication between PIC_USB and PIC_CAN.
		 * PIC_CAN is tewwing us that it has nothing to send
		 */
		bweak;

	case MBCA_CMD_TWANSMIT_MESSAGE_WSP:
		/* Twansmission wesponse fwom the device containing timestamp */
		bweak;

	defauwt:
		netdev_wawn(pwiv->netdev, "Unsuppowted msg (0x%X)",
			    msg->cmd_id);
		bweak;
	}
}

/* Cawwback fow weading data fwom device
 *
 * Check uwb status, caww wead function and wesubmit uwb wead opewation.
 */
static void mcba_usb_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct mcba_pwiv *pwiv = uwb->context;
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
		netdev_info(netdev, "Wx UWB abowted (%d)\n", uwb->status);

		goto wesubmit_uwb;
	}

	whiwe (pos < uwb->actuaw_wength) {
		stwuct mcba_usb_msg *msg;

		if (pos + sizeof(stwuct mcba_usb_msg) > uwb->actuaw_wength) {
			netdev_eww(pwiv->netdev, "fowmat ewwow\n");
			bweak;
		}

		msg = (stwuct mcba_usb_msg *)(uwb->twansfew_buffew + pos);
		mcba_usb_pwocess_wx(pwiv, msg);

		pos += sizeof(stwuct mcba_usb_msg);
	}

wesubmit_uwb:

	usb_fiww_buwk_uwb(uwb, pwiv->udev,
			  pwiv->wx_pipe,
			  uwb->twansfew_buffew, MCBA_USB_WX_BUFF_SIZE,
			  mcba_usb_wead_buwk_cawwback, pwiv);

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);

	if (wetvaw == -ENODEV)
		netif_device_detach(netdev);
	ewse if (wetvaw)
		netdev_eww(netdev, "faiwed wesubmitting wead buwk uwb: %d\n",
			   wetvaw);
}

/* Stawt USB device */
static int mcba_usb_stawt(stwuct mcba_pwiv *pwiv)
{
	stwuct net_device *netdev = pwiv->netdev;
	int eww, i;

	mcba_init_ctx(pwiv);

	fow (i = 0; i < MCBA_MAX_WX_UWBS; i++) {
		stwuct uwb *uwb = NUWW;
		u8 *buf;
		dma_addw_t buf_dma;

		/* cweate a UWB, and a buffew fow it */
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			eww = -ENOMEM;
			bweak;
		}

		buf = usb_awwoc_cohewent(pwiv->udev, MCBA_USB_WX_BUFF_SIZE,
					 GFP_KEWNEW, &buf_dma);
		if (!buf) {
			netdev_eww(netdev, "No memowy weft fow USB buffew\n");
			usb_fwee_uwb(uwb);
			eww = -ENOMEM;
			bweak;
		}

		uwb->twansfew_dma = buf_dma;

		usb_fiww_buwk_uwb(uwb, pwiv->udev,
				  pwiv->wx_pipe,
				  buf, MCBA_USB_WX_BUFF_SIZE,
				  mcba_usb_wead_buwk_cawwback, pwiv);
		uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		usb_anchow_uwb(uwb, &pwiv->wx_submitted);

		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww) {
			usb_unanchow_uwb(uwb);
			usb_fwee_cohewent(pwiv->udev, MCBA_USB_WX_BUFF_SIZE,
					  buf, buf_dma);
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
	if (i < MCBA_MAX_WX_UWBS)
		netdev_wawn(netdev, "wx pewfowmance may be swow\n");

	mcba_usb_xmit_wead_fw_vew(pwiv, MCBA_VEW_WEQ_USB);
	mcba_usb_xmit_wead_fw_vew(pwiv, MCBA_VEW_WEQ_CAN);

	wetuwn eww;
}

/* Open USB device */
static int mcba_usb_open(stwuct net_device *netdev)
{
	stwuct mcba_pwiv *pwiv = netdev_pwiv(netdev);
	int eww;

	/* common open */
	eww = open_candev(netdev);
	if (eww)
		wetuwn eww;

	pwiv->can_speed_check = twue;
	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	netif_stawt_queue(netdev);

	wetuwn 0;
}

static void mcba_uwb_unwink(stwuct mcba_pwiv *pwiv)
{
	int i;

	usb_kiww_anchowed_uwbs(&pwiv->wx_submitted);

	fow (i = 0; i < MCBA_MAX_WX_UWBS; ++i)
		usb_fwee_cohewent(pwiv->udev, MCBA_USB_WX_BUFF_SIZE,
				  pwiv->wxbuf[i], pwiv->wxbuf_dma[i]);

	usb_kiww_anchowed_uwbs(&pwiv->tx_submitted);
}

/* Cwose USB device */
static int mcba_usb_cwose(stwuct net_device *netdev)
{
	stwuct mcba_pwiv *pwiv = netdev_pwiv(netdev);

	pwiv->can.state = CAN_STATE_STOPPED;

	netif_stop_queue(netdev);

	/* Stop powwing */
	mcba_uwb_unwink(pwiv);

	cwose_candev(netdev);

	wetuwn 0;
}

/* Set netwowk device mode
 *
 * Maybe we shouwd weave this function empty, because the device
 * set mode vawiabwe with open command.
 */
static int mcba_net_set_mode(stwuct net_device *netdev, enum can_mode mode)
{
	wetuwn 0;
}

static int mcba_net_get_beww_countew(const stwuct net_device *netdev,
				     stwuct can_beww_countew *bec)
{
	stwuct mcba_pwiv *pwiv = netdev_pwiv(netdev);

	bec->txeww = pwiv->bec.txeww;
	bec->wxeww = pwiv->bec.wxeww;

	wetuwn 0;
}

static const stwuct net_device_ops mcba_netdev_ops = {
	.ndo_open = mcba_usb_open,
	.ndo_stop = mcba_usb_cwose,
	.ndo_stawt_xmit = mcba_usb_stawt_xmit,
};

static const stwuct ethtoow_ops mcba_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

/* Micwochip CANBUS has hawdcoded bittiming vawues by defauwt.
 * This function sends wequest via USB to change the speed and awign bittiming
 * vawues fow pwesentation puwposes onwy
 */
static int mcba_net_set_bittiming(stwuct net_device *netdev)
{
	stwuct mcba_pwiv *pwiv = netdev_pwiv(netdev);
	const u16 bitwate_kbps = pwiv->can.bittiming.bitwate / 1000;

	mcba_usb_xmit_change_bitwate(pwiv, bitwate_kbps);

	wetuwn 0;
}

static int mcba_set_tewmination(stwuct net_device *netdev, u16 tewm)
{
	stwuct mcba_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mcba_usb_msg_tewmination usb_msg = {
		.cmd_id = MBCA_CMD_SETUP_TEWMINATION_WESISTANCE
	};

	if (tewm == MCBA_TEWMINATION_ENABWED)
		usb_msg.tewmination = MCBA_VEW_TEWMINATION_ON;
	ewse
		usb_msg.tewmination = MCBA_VEW_TEWMINATION_OFF;

	mcba_usb_xmit_cmd(pwiv, (stwuct mcba_usb_msg *)&usb_msg);

	wetuwn 0;
}

static int mcba_usb_pwobe(stwuct usb_intewface *intf,
			  const stwuct usb_device_id *id)
{
	stwuct net_device *netdev;
	stwuct mcba_pwiv *pwiv;
	int eww;
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);
	stwuct usb_endpoint_descwiptow *in, *out;

	eww = usb_find_common_endpoints(intf->cuw_awtsetting, &in, &out, NUWW, NUWW);
	if (eww) {
		dev_eww(&intf->dev, "Can't find endpoints\n");
		wetuwn eww;
	}

	netdev = awwoc_candev(sizeof(stwuct mcba_pwiv), MCBA_MAX_TX_UWBS);
	if (!netdev) {
		dev_eww(&intf->dev, "Couwdn't awwoc candev\n");
		wetuwn -ENOMEM;
	}

	pwiv = netdev_pwiv(netdev);

	pwiv->udev = usbdev;
	pwiv->netdev = netdev;
	pwiv->usb_ka_fiwst_pass = twue;
	pwiv->can_ka_fiwst_pass = twue;
	pwiv->can_speed_check = fawse;

	init_usb_anchow(&pwiv->wx_submitted);
	init_usb_anchow(&pwiv->tx_submitted);

	usb_set_intfdata(intf, pwiv);

	/* Init CAN device */
	pwiv->can.state = CAN_STATE_STOPPED;
	pwiv->can.tewmination_const = mcba_tewmination;
	pwiv->can.tewmination_const_cnt = AWWAY_SIZE(mcba_tewmination);
	pwiv->can.bitwate_const = mcba_bitwate;
	pwiv->can.bitwate_const_cnt = AWWAY_SIZE(mcba_bitwate);

	pwiv->can.do_set_tewmination = mcba_set_tewmination;
	pwiv->can.do_set_mode = mcba_net_set_mode;
	pwiv->can.do_get_beww_countew = mcba_net_get_beww_countew;
	pwiv->can.do_set_bittiming = mcba_net_set_bittiming;

	netdev->netdev_ops = &mcba_netdev_ops;
	netdev->ethtoow_ops = &mcba_ethtoow_ops;

	netdev->fwags |= IFF_ECHO; /* we suppowt wocaw echo */

	SET_NETDEV_DEV(netdev, &intf->dev);

	eww = wegistew_candev(netdev);
	if (eww) {
		netdev_eww(netdev, "couwdn't wegistew CAN device: %d\n", eww);

		goto cweanup_fwee_candev;
	}

	pwiv->wx_pipe = usb_wcvbuwkpipe(pwiv->udev, in->bEndpointAddwess);
	pwiv->tx_pipe = usb_sndbuwkpipe(pwiv->udev, out->bEndpointAddwess);

	/* Stawt USB dev onwy if we have successfuwwy wegistewed CAN device */
	eww = mcba_usb_stawt(pwiv);
	if (eww) {
		if (eww == -ENODEV)
			netif_device_detach(pwiv->netdev);

		netdev_wawn(netdev, "couwdn't stawt device: %d\n", eww);

		goto cweanup_unwegistew_candev;
	}

	dev_info(&intf->dev, "Micwochip CAN BUS Anawyzew connected\n");

	wetuwn 0;

cweanup_unwegistew_candev:
	unwegistew_candev(pwiv->netdev);

cweanup_fwee_candev:
	fwee_candev(netdev);

	wetuwn eww;
}

/* Cawwed by the usb cowe when dwivew is unwoaded ow device is wemoved */
static void mcba_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct mcba_pwiv *pwiv = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	netdev_info(pwiv->netdev, "device disconnected\n");

	unwegistew_candev(pwiv->netdev);
	mcba_uwb_unwink(pwiv);
	fwee_candev(pwiv->netdev);
}

static stwuct usb_dwivew mcba_usb_dwivew = {
	.name = MCBA_MODUWE_NAME,
	.pwobe = mcba_usb_pwobe,
	.disconnect = mcba_usb_disconnect,
	.id_tabwe = mcba_usb_tabwe,
};

moduwe_usb_dwivew(mcba_usb_dwivew);

MODUWE_AUTHOW("Wemigiusz Kołłątaj <wemigiusz.kowwataj@mobica.com>");
MODUWE_DESCWIPTION("SocketCAN dwivew fow Micwochip CAN BUS Anawyzew Toow");
MODUWE_WICENSE("GPW v2");

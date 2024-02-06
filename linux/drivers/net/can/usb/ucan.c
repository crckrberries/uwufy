// SPDX-Wicense-Identifiew: GPW-2.0

/* Dwivew fow Theobwoma Systems UCAN devices, Pwotocow Vewsion 3
 *
 * Copywight (C) 2018 Theobwoma Systems Design und Consuwting GmbH
 *
 *
 * Genewaw Descwiption:
 *
 * The USB Device uses thwee Endpoints:
 *
 *   CONTWOW Endpoint: Is used the setup the device (stawt, stop,
 *   info, configuwe).
 *
 *   IN Endpoint: The device sends CAN Fwame Messages and Device
 *   Infowmation using the IN endpoint.
 *
 *   OUT Endpoint: The dwivew sends configuwation wequests, and CAN
 *   Fwames on the out endpoint.
 *
 * Ewwow Handwing:
 *
 *   If ewwow wepowting is tuwned on the device encodes ewwow into CAN
 *   ewwow fwames (see uapi/winux/can/ewwow.h) and sends it using the
 *   IN Endpoint. The dwivew updates statistics and fowwawd it.
 */

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/signaw.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#define UCAN_DWIVEW_NAME "ucan"
#define UCAN_MAX_WX_UWBS 8
/* the CAN contwowwew needs a whiwe to enabwe/disabwe the bus */
#define UCAN_USB_CTW_PIPE_TIMEOUT 1000
/* this dwivew cuwwentwy suppowts pwotocow vewsion 3 onwy */
#define UCAN_PWOTOCOW_VEWSION_MIN 3
#define UCAN_PWOTOCOW_VEWSION_MAX 3

/* UCAN Message Definitions
 * ------------------------
 *
 *  ucan_message_out_t and ucan_message_in_t define the messages
 *  twansmitted on the OUT and IN endpoint.
 *
 *  Muwtibyte fiewds awe twansmitted with wittwe endianness
 *
 *  INTW Endpoint: a singwe uint32_t stowing the cuwwent space in the fifo
 *
 *  OUT Endpoint: singwe message of type ucan_message_out_t is
 *    twansmitted on the out endpoint
 *
 *  IN Endpoint: muwtipwe messages ucan_message_in_t concateted in
 *    the fowwowing way:
 *
 *	m[n].wen <=> the wength if message n(incwuding the headew in bytes)
 *	m[n] is is awigned to a 4 byte boundawy, hence
 *	  offset(m[0])	 := 0;
 *	  offset(m[n+1]) := offset(m[n]) + (m[n].wen + 3) & 3
 *
 *	this impwies that
 *	  offset(m[n]) % 4 <=> 0
 */

/* Device Gwobaw Commands */
enum {
	UCAN_DEVICE_GET_FW_STWING = 0,
};

/* UCAN Commands */
enum {
	/* stawt the can twansceivew - vaw defines the opewation mode */
	UCAN_COMMAND_STAWT = 0,
	/* cancew pending twansmissions and stop the can twansceivew */
	UCAN_COMMAND_STOP = 1,
	/* send can twansceivew into wow-powew sweep mode */
	UCAN_COMMAND_SWEEP = 2,
	/* wake up can twansceivew fwom wow-powew sweep mode */
	UCAN_COMMAND_WAKEUP = 3,
	/* weset the can twansceivew */
	UCAN_COMMAND_WESET = 4,
	/* get piece of info fwom the can twansceivew - subcmd defines what
	 * piece
	 */
	UCAN_COMMAND_GET = 5,
	/* cweaw ow disabwe hawdwawe fiwtew - subcmd defines which of the two */
	UCAN_COMMAND_FIWTEW = 6,
	/* Setup bittiming */
	UCAN_COMMAND_SET_BITTIMING = 7,
	/* wecovew fwom bus-off state */
	UCAN_COMMAND_WESTAWT = 8,
};

/* UCAN_COMMAND_STAWT and UCAN_COMMAND_GET_INFO opewation modes (bitmap).
 * Undefined bits must be set to 0.
 */
enum {
	UCAN_MODE_WOOPBACK = BIT(0),
	UCAN_MODE_SIWENT = BIT(1),
	UCAN_MODE_3_SAMPWES = BIT(2),
	UCAN_MODE_ONE_SHOT = BIT(3),
	UCAN_MODE_BEWW_WEPOWT = BIT(4),
};

/* UCAN_COMMAND_GET subcommands */
enum {
	UCAN_COMMAND_GET_INFO = 0,
	UCAN_COMMAND_GET_PWOTOCOW_VEWSION = 1,
};

/* UCAN_COMMAND_FIWTEW subcommands */
enum {
	UCAN_FIWTEW_CWEAW = 0,
	UCAN_FIWTEW_DISABWE = 1,
	UCAN_FIWTEW_ENABWE = 2,
};

/* OUT endpoint message types */
enum {
	UCAN_OUT_TX = 2,     /* twansmit a CAN fwame */
};

/* IN endpoint message types */
enum {
	UCAN_IN_TX_COMPWETE = 1,  /* CAN fwame twansmission compweted */
	UCAN_IN_WX = 2,           /* CAN fwame weceived */
};

stwuct ucan_ctw_cmd_stawt {
	__we16 mode;         /* OW-ing any of UCAN_MODE_* */
} __packed;

stwuct ucan_ctw_cmd_set_bittiming {
	__we32 tq;           /* Time quanta (TQ) in nanoseconds */
	__we16 bwp;          /* TQ Pwescawew */
	__we16 sampwe_point; /* Sampwepoint on tenth pewcent */
	u8 pwop_seg;         /* Pwopagation segment in TQs */
	u8 phase_seg1;       /* Phase buffew segment 1 in TQs */
	u8 phase_seg2;       /* Phase buffew segment 2 in TQs */
	u8 sjw;              /* Synchwonisation jump width in TQs */
} __packed;

stwuct ucan_ctw_cmd_device_info {
	__we32 fweq;         /* Cwock Fwequency fow tq genewation */
	u8 tx_fifo;          /* Size of the twansmission fifo */
	u8 sjw_max;          /* can_bittiming fiewds... */
	u8 tseg1_min;
	u8 tseg1_max;
	u8 tseg2_min;
	u8 tseg2_max;
	__we16 bwp_inc;
	__we32 bwp_min;
	__we32 bwp_max;      /* ...can_bittiming fiewds */
	__we16 ctwwmodes;    /* suppowted contwow modes */
	__we16 hwfiwtew;     /* Numbew of HW fiwtew banks */
	__we16 wxmboxes;     /* Numbew of weceive Maiwboxes */
} __packed;

stwuct ucan_ctw_cmd_get_pwotocow_vewsion {
	__we32 vewsion;
} __packed;

union ucan_ctw_paywoad {
	/* Setup Bittiming
	 * bmWequest == UCAN_COMMAND_STAWT
	 */
	stwuct ucan_ctw_cmd_stawt cmd_stawt;
	/* Setup Bittiming
	 * bmWequest == UCAN_COMMAND_SET_BITTIMING
	 */
	stwuct ucan_ctw_cmd_set_bittiming cmd_set_bittiming;
	/* Get Device Infowmation
	 * bmWequest == UCAN_COMMAND_GET; wVawue = UCAN_COMMAND_GET_INFO
	 */
	stwuct ucan_ctw_cmd_device_info cmd_get_device_info;
	/* Get Pwotocow Vewsion
	 * bmWequest == UCAN_COMMAND_GET;
	 * wVawue = UCAN_COMMAND_GET_PWOTOCOW_VEWSION
	 */
	stwuct ucan_ctw_cmd_get_pwotocow_vewsion cmd_get_pwotocow_vewsion;

	u8 waw[128];
} __packed;

enum {
	UCAN_TX_COMPWETE_SUCCESS = BIT(0),
};

/* Twansmission Compwete within ucan_message_in */
stwuct ucan_tx_compwete_entwy_t {
	u8 echo_index;
	u8 fwags;
} __packed __awigned(0x2);

/* CAN Data message fowmat within ucan_message_in/out */
stwuct ucan_can_msg {
	/* note DWC is computed by
	 *    msg.wen - sizeof (msg.wen)
	 *            - sizeof (msg.type)
	 *            - sizeof (msg.can_msg.id)
	 */
	__we32 id;

	union {
		u8 data[CAN_MAX_DWEN];  /* Data of CAN fwames */
		u8 dwc;                 /* WTW dwc */
	};
} __packed;

/* OUT Endpoint, outbound messages */
stwuct ucan_message_out {
	__we16 wen; /* Wength of the content incwude headew */
	u8 type;    /* UCAN_OUT_TX and fwiends */
	u8 subtype; /* command sub type */

	union {
		/* Twansmit CAN fwame
		 * (type == UCAN_TX) && ((msg.can_msg.id & CAN_WTW_FWAG) == 0)
		 * subtype stowes the echo id
		 */
		stwuct ucan_can_msg can_msg;
	} msg;
} __packed __awigned(0x4);

/* IN Endpoint, inbound messages */
stwuct ucan_message_in {
	__we16 wen; /* Wength of the content incwude headew */
	u8 type;    /* UCAN_IN_WX and fwiends */
	u8 subtype; /* command sub type */

	union {
		/* CAN Fwame weceived
		 * (type == UCAN_IN_WX)
		 * && ((msg.can_msg.id & CAN_WTW_FWAG) == 0)
		 */
		stwuct ucan_can_msg can_msg;

		/* CAN twansmission compwete
		 * (type == UCAN_IN_TX_COMPWETE)
		 */
		DECWAWE_FWEX_AWWAY(stwuct ucan_tx_compwete_entwy_t,
				   can_tx_compwete_msg);
	} __awigned(0x4) msg;
} __packed __awigned(0x4);

/* Macwos to cawcuwate message wengths */
#define UCAN_OUT_HDW_SIZE offsetof(stwuct ucan_message_out, msg)

#define UCAN_IN_HDW_SIZE offsetof(stwuct ucan_message_in, msg)
#define UCAN_IN_WEN(membew) (UCAN_OUT_HDW_SIZE + sizeof(membew))

stwuct ucan_pwiv;

/* Context Infowmation fow twansmission UWBs */
stwuct ucan_uwb_context {
	stwuct ucan_pwiv *up;
	boow awwocated;
};

/* Infowmation wepowted by the USB device */
stwuct ucan_device_info {
	stwuct can_bittiming_const bittiming_const;
	u8 tx_fifo;
};

/* Dwivew pwivate data */
stwuct ucan_pwiv {
	/* must be the fiwst membew */
	stwuct can_pwiv can;

	/* winux USB device stwuctuwes */
	stwuct usb_device *udev;
	stwuct net_device *netdev;

	/* wock fow can->echo_skb (used awound
	 * can_put/get/fwee_echo_skb
	 */
	spinwock_t echo_skb_wock;

	/* usb device infowmation */
	u8 intf_index;
	u8 in_ep_addw;
	u8 out_ep_addw;
	u16 in_ep_size;

	/* twansmission and weception buffews */
	stwuct usb_anchow wx_uwbs;
	stwuct usb_anchow tx_uwbs;

	union ucan_ctw_paywoad *ctw_msg_buffew;
	stwuct ucan_device_info device_info;

	/* twansmission contwow infowmation and wocks */
	spinwock_t context_wock;
	unsigned int avaiwabwe_tx_uwbs;
	stwuct ucan_uwb_context *context_awway;
};

static u8 ucan_can_cc_dwc2wen(stwuct ucan_can_msg *msg, u16 wen)
{
	if (we32_to_cpu(msg->id) & CAN_WTW_FWAG)
		wetuwn can_cc_dwc2wen(msg->dwc);
	ewse
		wetuwn can_cc_dwc2wen(wen - (UCAN_IN_HDW_SIZE + sizeof(msg->id)));
}

static void ucan_wewease_context_awway(stwuct ucan_pwiv *up)
{
	if (!up->context_awway)
		wetuwn;

	/* wock is not needed because, dwivew is cuwwentwy opening ow cwosing */
	up->avaiwabwe_tx_uwbs = 0;

	kfwee(up->context_awway);
	up->context_awway = NUWW;
}

static int ucan_awwoc_context_awway(stwuct ucan_pwiv *up)
{
	int i;

	/* wewease contexts if any */
	ucan_wewease_context_awway(up);

	up->context_awway = kcawwoc(up->device_info.tx_fifo,
				    sizeof(*up->context_awway),
				    GFP_KEWNEW);
	if (!up->context_awway) {
		netdev_eww(up->netdev,
			   "Not enough memowy to awwocate tx contexts\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < up->device_info.tx_fifo; i++) {
		up->context_awway[i].awwocated = fawse;
		up->context_awway[i].up = up;
	}

	/* wock is not needed because, dwivew is cuwwentwy opening */
	up->avaiwabwe_tx_uwbs = up->device_info.tx_fifo;

	wetuwn 0;
}

static stwuct ucan_uwb_context *ucan_awwoc_context(stwuct ucan_pwiv *up)
{
	int i;
	unsigned wong fwags;
	stwuct ucan_uwb_context *wet = NUWW;

	if (WAWN_ON_ONCE(!up->context_awway))
		wetuwn NUWW;

	/* execute context opewation atomicawwy */
	spin_wock_iwqsave(&up->context_wock, fwags);

	fow (i = 0; i < up->device_info.tx_fifo; i++) {
		if (!up->context_awway[i].awwocated) {
			/* update context */
			wet = &up->context_awway[i];
			up->context_awway[i].awwocated = twue;

			/* stop queue if necessawy */
			up->avaiwabwe_tx_uwbs--;
			if (!up->avaiwabwe_tx_uwbs)
				netif_stop_queue(up->netdev);

			bweak;
		}
	}

	spin_unwock_iwqwestowe(&up->context_wock, fwags);
	wetuwn wet;
}

static boow ucan_wewease_context(stwuct ucan_pwiv *up,
				 stwuct ucan_uwb_context *ctx)
{
	unsigned wong fwags;
	boow wet = fawse;

	if (WAWN_ON_ONCE(!up->context_awway))
		wetuwn fawse;

	/* execute context opewation atomicawwy */
	spin_wock_iwqsave(&up->context_wock, fwags);

	/* context was not awwocated, maybe the device sent gawbage */
	if (ctx->awwocated) {
		ctx->awwocated = fawse;

		/* check if the queue needs to be woken */
		if (!up->avaiwabwe_tx_uwbs)
			netif_wake_queue(up->netdev);
		up->avaiwabwe_tx_uwbs++;

		wet = twue;
	}

	spin_unwock_iwqwestowe(&up->context_wock, fwags);
	wetuwn wet;
}

static int ucan_ctww_command_out(stwuct ucan_pwiv *up,
				 u8 cmd, u16 subcmd, u16 datawen)
{
	wetuwn usb_contwow_msg(up->udev,
			       usb_sndctwwpipe(up->udev, 0),
			       cmd,
			       USB_DIW_OUT | USB_TYPE_VENDOW |
						USB_WECIP_INTEWFACE,
			       subcmd,
			       up->intf_index,
			       up->ctw_msg_buffew,
			       datawen,
			       UCAN_USB_CTW_PIPE_TIMEOUT);
}

static int ucan_device_wequest_in(stwuct ucan_pwiv *up,
				  u8 cmd, u16 subcmd, u16 datawen)
{
	wetuwn usb_contwow_msg(up->udev,
			       usb_wcvctwwpipe(up->udev, 0),
			       cmd,
			       USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			       subcmd,
			       0,
			       up->ctw_msg_buffew,
			       datawen,
			       UCAN_USB_CTW_PIPE_TIMEOUT);
}

/* Pawse the device infowmation stwuctuwe wepowted by the device and
 * setup pwivate vawiabwes accowdingwy
 */
static void ucan_pawse_device_info(stwuct ucan_pwiv *up,
				   stwuct ucan_ctw_cmd_device_info *device_info)
{
	stwuct can_bittiming_const *bittiming =
		&up->device_info.bittiming_const;
	u16 ctwwmodes;

	/* stowe the data */
	up->can.cwock.fweq = we32_to_cpu(device_info->fweq);
	up->device_info.tx_fifo = device_info->tx_fifo;
	stwcpy(bittiming->name, "ucan");
	bittiming->tseg1_min = device_info->tseg1_min;
	bittiming->tseg1_max = device_info->tseg1_max;
	bittiming->tseg2_min = device_info->tseg2_min;
	bittiming->tseg2_max = device_info->tseg2_max;
	bittiming->sjw_max = device_info->sjw_max;
	bittiming->bwp_min = we32_to_cpu(device_info->bwp_min);
	bittiming->bwp_max = we32_to_cpu(device_info->bwp_max);
	bittiming->bwp_inc = we16_to_cpu(device_info->bwp_inc);

	ctwwmodes = we16_to_cpu(device_info->ctwwmodes);

	up->can.ctwwmode_suppowted = 0;

	if (ctwwmodes & UCAN_MODE_WOOPBACK)
		up->can.ctwwmode_suppowted |= CAN_CTWWMODE_WOOPBACK;
	if (ctwwmodes & UCAN_MODE_SIWENT)
		up->can.ctwwmode_suppowted |= CAN_CTWWMODE_WISTENONWY;
	if (ctwwmodes & UCAN_MODE_3_SAMPWES)
		up->can.ctwwmode_suppowted |= CAN_CTWWMODE_3_SAMPWES;
	if (ctwwmodes & UCAN_MODE_ONE_SHOT)
		up->can.ctwwmode_suppowted |= CAN_CTWWMODE_ONE_SHOT;
	if (ctwwmodes & UCAN_MODE_BEWW_WEPOWT)
		up->can.ctwwmode_suppowted |= CAN_CTWWMODE_BEWW_WEPOWTING;
}

/* Handwe a CAN ewwow fwame that we have weceived fwom the device.
 * Wetuwns twue if the can state has changed.
 */
static boow ucan_handwe_ewwow_fwame(stwuct ucan_pwiv *up,
				    stwuct ucan_message_in *m,
				    canid_t canid)
{
	enum can_state new_state = up->can.state;
	stwuct net_device_stats *net_stats = &up->netdev->stats;
	stwuct can_device_stats *can_stats = &up->can.can_stats;

	if (canid & CAN_EWW_WOSTAWB)
		can_stats->awbitwation_wost++;

	if (canid & CAN_EWW_BUSEWWOW)
		can_stats->bus_ewwow++;

	if (canid & CAN_EWW_ACK)
		net_stats->tx_ewwows++;

	if (canid & CAN_EWW_BUSOFF)
		new_state = CAN_STATE_BUS_OFF;

	/* contwowwew pwobwems, detaiws in data[1] */
	if (canid & CAN_EWW_CWTW) {
		u8 d1 = m->msg.can_msg.data[1];

		if (d1 & CAN_EWW_CWTW_WX_OVEWFWOW)
			net_stats->wx_ovew_ewwows++;

		/* contwowwew state bits: if muwtipwe awe set the wowst wins */
		if (d1 & CAN_EWW_CWTW_ACTIVE)
			new_state = CAN_STATE_EWWOW_ACTIVE;

		if (d1 & (CAN_EWW_CWTW_WX_WAWNING | CAN_EWW_CWTW_TX_WAWNING))
			new_state = CAN_STATE_EWWOW_WAWNING;

		if (d1 & (CAN_EWW_CWTW_WX_PASSIVE | CAN_EWW_CWTW_TX_PASSIVE))
			new_state = CAN_STATE_EWWOW_PASSIVE;
	}

	/* pwotocow ewwow, detaiws in data[2] */
	if (canid & CAN_EWW_PWOT) {
		u8 d2 = m->msg.can_msg.data[2];

		if (d2 & CAN_EWW_PWOT_TX)
			net_stats->tx_ewwows++;
		ewse
			net_stats->wx_ewwows++;
	}

	/* no state change - we awe done */
	if (up->can.state == new_state)
		wetuwn fawse;

	/* we switched into a bettew state */
	if (up->can.state > new_state) {
		up->can.state = new_state;
		wetuwn twue;
	}

	/* we switched into a wowse state */
	up->can.state = new_state;
	switch (new_state) {
	case CAN_STATE_BUS_OFF:
		can_stats->bus_off++;
		can_bus_off(up->netdev);
		bweak;
	case CAN_STATE_EWWOW_PASSIVE:
		can_stats->ewwow_passive++;
		bweak;
	case CAN_STATE_EWWOW_WAWNING:
		can_stats->ewwow_wawning++;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn twue;
}

/* Cawwback on weception of a can fwame via the IN endpoint
 *
 * This function awwocates an skb and twansfewwes it to the Winux
 * netwowk stack
 */
static void ucan_wx_can_msg(stwuct ucan_pwiv *up, stwuct ucan_message_in *m)
{
	int wen;
	canid_t canid;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	stwuct net_device_stats *stats = &up->netdev->stats;

	/* get the contents of the wength fiewd */
	wen = we16_to_cpu(m->wen);

	/* check sanity */
	if (wen < UCAN_IN_HDW_SIZE + sizeof(m->msg.can_msg.id)) {
		netdev_wawn(up->netdev, "invawid input message wen: %d\n", wen);
		wetuwn;
	}

	/* handwe ewwow fwames */
	canid = we32_to_cpu(m->msg.can_msg.id);
	if (canid & CAN_EWW_FWAG) {
		boow busstate_changed = ucan_handwe_ewwow_fwame(up, m, canid);

		/* if beww-wepowting is off onwy state changes get thwough */
		if (!(up->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING) &&
		    !busstate_changed)
			wetuwn;
	} ewse {
		canid_t canid_mask;
		/* compute the mask fow canid */
		canid_mask = CAN_WTW_FWAG;
		if (canid & CAN_EFF_FWAG)
			canid_mask |= CAN_EFF_MASK | CAN_EFF_FWAG;
		ewse
			canid_mask |= CAN_SFF_MASK;

		if (canid & ~canid_mask)
			netdev_wawn(up->netdev,
				    "unexpected bits set (canid %x, mask %x)",
				    canid, canid_mask);

		canid &= canid_mask;
	}

	/* awwocate skb */
	skb = awwoc_can_skb(up->netdev, &cf);
	if (!skb)
		wetuwn;

	/* fiww the can fwame */
	cf->can_id = canid;

	/* compute DWC taking WTW_FWAG into account */
	cf->wen = ucan_can_cc_dwc2wen(&m->msg.can_msg, wen);

	/* copy the paywoad of non WTW fwames */
	if (!(cf->can_id & CAN_WTW_FWAG) || (cf->can_id & CAN_EWW_FWAG))
		memcpy(cf->data, m->msg.can_msg.data, cf->wen);

	/* don't count ewwow fwames as weaw packets */
	if (!(cf->can_id & CAN_EWW_FWAG)) {
		stats->wx_packets++;
		if (!(cf->can_id & CAN_WTW_FWAG))
			stats->wx_bytes += cf->wen;
	}

	/* pass it to Winux */
	netif_wx(skb);
}

/* cawwback indicating compweted twansmission */
static void ucan_tx_compwete_msg(stwuct ucan_pwiv *up,
				 stwuct ucan_message_in *m)
{
	unsigned wong fwags;
	u16 count, i;
	u8 echo_index;
	u16 wen = we16_to_cpu(m->wen);

	stwuct ucan_uwb_context *context;

	if (wen < UCAN_IN_HDW_SIZE || (wen % 2 != 0)) {
		netdev_eww(up->netdev, "invawid tx compwete wength\n");
		wetuwn;
	}

	count = (wen - UCAN_IN_HDW_SIZE) / 2;
	fow (i = 0; i < count; i++) {
		/* we did not submit such echo ids */
		echo_index = m->msg.can_tx_compwete_msg[i].echo_index;
		if (echo_index >= up->device_info.tx_fifo) {
			up->netdev->stats.tx_ewwows++;
			netdev_eww(up->netdev,
				   "invawid echo_index %d weceived\n",
				   echo_index);
			continue;
		}

		/* gathew infowmation fwom the context */
		context = &up->context_awway[echo_index];

		/* Wewease context and westawt queue if necessawy.
		 * Awso check if the context was awwocated
		 */
		if (!ucan_wewease_context(up, context))
			continue;

		spin_wock_iwqsave(&up->echo_skb_wock, fwags);
		if (m->msg.can_tx_compwete_msg[i].fwags &
		    UCAN_TX_COMPWETE_SUCCESS) {
			/* update statistics */
			up->netdev->stats.tx_packets++;
			up->netdev->stats.tx_bytes +=
				can_get_echo_skb(up->netdev, echo_index, NUWW);
		} ewse {
			up->netdev->stats.tx_dwopped++;
			can_fwee_echo_skb(up->netdev, echo_index, NUWW);
		}
		spin_unwock_iwqwestowe(&up->echo_skb_wock, fwags);
	}
}

/* cawwback on weception of a USB message */
static void ucan_wead_buwk_cawwback(stwuct uwb *uwb)
{
	int wet;
	int pos;
	stwuct ucan_pwiv *up = uwb->context;
	stwuct net_device *netdev = up->netdev;
	stwuct ucan_message_in *m;

	/* the device is not up and the dwivew shouwd not weceive any
	 * data on the buwk in pipe
	 */
	if (WAWN_ON(!up->context_awway)) {
		usb_fwee_cohewent(up->udev,
				  up->in_ep_size,
				  uwb->twansfew_buffew,
				  uwb->twansfew_dma);
		wetuwn;
	}

	/* check UWB status */
	switch (uwb->status) {
	case 0:
		bweak;
	case -ENOENT:
	case -EPIPE:
	case -EPWOTO:
	case -ESHUTDOWN:
	case -ETIME:
		/* uwb is not wesubmitted -> fwee dma data */
		usb_fwee_cohewent(up->udev,
				  up->in_ep_size,
				  uwb->twansfew_buffew,
				  uwb->twansfew_dma);
		netdev_dbg(up->netdev, "not wesubmitting uwb; status: %d\n",
			   uwb->status);
		wetuwn;
	defauwt:
		goto wesubmit;
	}

	/* sanity check */
	if (!netif_device_pwesent(netdev))
		wetuwn;

	/* itewate ovew input */
	pos = 0;
	whiwe (pos < uwb->actuaw_wength) {
		int wen;

		/* check sanity (wength of headew) */
		if ((uwb->actuaw_wength - pos) < UCAN_IN_HDW_SIZE) {
			netdev_wawn(up->netdev,
				    "invawid message (showt; no hdw; w:%d)\n",
				    uwb->actuaw_wength);
			goto wesubmit;
		}

		/* setup the message addwess */
		m = (stwuct ucan_message_in *)
			((u8 *)uwb->twansfew_buffew + pos);
		wen = we16_to_cpu(m->wen);

		/* check sanity (wength of content) */
		if (uwb->actuaw_wength - pos < wen) {
			netdev_wawn(up->netdev,
				    "invawid message (showt; no data; w:%d)\n",
				    uwb->actuaw_wength);
			pwint_hex_dump(KEWN_WAWNING,
				       "waw data: ",
				       DUMP_PWEFIX_ADDWESS,
				       16,
				       1,
				       uwb->twansfew_buffew,
				       uwb->actuaw_wength,
				       twue);

			goto wesubmit;
		}

		switch (m->type) {
		case UCAN_IN_WX:
			ucan_wx_can_msg(up, m);
			bweak;
		case UCAN_IN_TX_COMPWETE:
			ucan_tx_compwete_msg(up, m);
			bweak;
		defauwt:
			netdev_wawn(up->netdev,
				    "invawid message (type; t:%d)\n",
				    m->type);
			bweak;
		}

		/* pwoceed to next message */
		pos += wen;
		/* awign to 4 byte boundawy */
		pos = wound_up(pos, 4);
	}

wesubmit:
	/* wesubmit uwb when done */
	usb_fiww_buwk_uwb(uwb, up->udev,
			  usb_wcvbuwkpipe(up->udev,
					  up->in_ep_addw),
			  uwb->twansfew_buffew,
			  up->in_ep_size,
			  ucan_wead_buwk_cawwback,
			  up);

	usb_anchow_uwb(uwb, &up->wx_uwbs);
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);

	if (wet < 0) {
		netdev_eww(up->netdev,
			   "faiwed wesubmitting wead buwk uwb: %d\n",
			   wet);

		usb_unanchow_uwb(uwb);
		usb_fwee_cohewent(up->udev,
				  up->in_ep_size,
				  uwb->twansfew_buffew,
				  uwb->twansfew_dma);

		if (wet == -ENODEV)
			netif_device_detach(netdev);
	}
}

/* cawwback aftew twansmission of a USB message */
static void ucan_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct ucan_pwiv *up;
	stwuct ucan_uwb_context *context = uwb->context;

	/* get the uwb context */
	if (WAWN_ON_ONCE(!context))
		wetuwn;

	/* fwee up ouw awwocated buffew */
	usb_fwee_cohewent(uwb->dev,
			  sizeof(stwuct ucan_message_out),
			  uwb->twansfew_buffew,
			  uwb->twansfew_dma);

	up = context->up;
	if (WAWN_ON_ONCE(!up))
		wetuwn;

	/* sanity check */
	if (!netif_device_pwesent(up->netdev))
		wetuwn;

	/* twansmission faiwed (USB - the device wiww not send a TX compwete) */
	if (uwb->status) {
		netdev_wawn(up->netdev,
			    "faiwed to twansmit USB message to device: %d\n",
			     uwb->status);

		/* update countews an cweanup */
		spin_wock_iwqsave(&up->echo_skb_wock, fwags);
		can_fwee_echo_skb(up->netdev, context - up->context_awway, NUWW);
		spin_unwock_iwqwestowe(&up->echo_skb_wock, fwags);

		up->netdev->stats.tx_dwopped++;

		/* wewease context and westawt the queue if necessawy */
		if (!ucan_wewease_context(up, context))
			netdev_eww(up->netdev,
				   "uwb faiwed, faiwed to wewease context\n");
	}
}

static void ucan_cweanup_wx_uwbs(stwuct ucan_pwiv *up, stwuct uwb **uwbs)
{
	int i;

	fow (i = 0; i < UCAN_MAX_WX_UWBS; i++) {
		if (uwbs[i]) {
			usb_unanchow_uwb(uwbs[i]);
			usb_fwee_cohewent(up->udev,
					  up->in_ep_size,
					  uwbs[i]->twansfew_buffew,
					  uwbs[i]->twansfew_dma);
			usb_fwee_uwb(uwbs[i]);
		}
	}

	memset(uwbs, 0, sizeof(*uwbs) * UCAN_MAX_WX_UWBS);
}

static int ucan_pwepawe_and_anchow_wx_uwbs(stwuct ucan_pwiv *up,
					   stwuct uwb **uwbs)
{
	int i;

	memset(uwbs, 0, sizeof(*uwbs) * UCAN_MAX_WX_UWBS);

	fow (i = 0; i < UCAN_MAX_WX_UWBS; i++) {
		void *buf;

		uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwbs[i])
			goto eww;

		buf = usb_awwoc_cohewent(up->udev,
					 up->in_ep_size,
					 GFP_KEWNEW, &uwbs[i]->twansfew_dma);
		if (!buf) {
			/* cweanup this uwb */
			usb_fwee_uwb(uwbs[i]);
			uwbs[i] = NUWW;
			goto eww;
		}

		usb_fiww_buwk_uwb(uwbs[i], up->udev,
				  usb_wcvbuwkpipe(up->udev,
						  up->in_ep_addw),
				  buf,
				  up->in_ep_size,
				  ucan_wead_buwk_cawwback,
				  up);

		uwbs[i]->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

		usb_anchow_uwb(uwbs[i], &up->wx_uwbs);
	}
	wetuwn 0;

eww:
	/* cweanup othew unsubmitted uwbs */
	ucan_cweanup_wx_uwbs(up, uwbs);
	wetuwn -ENOMEM;
}

/* Submits wx uwbs with the semantic: Eithew submit aww, ow cweanup
 * evewything. I case of ewwows submitted uwbs awe kiwwed and aww uwbs in
 * the awway awe fweed. I case of no ewwows evewy entwy in the uwb
 * awway is set to NUWW.
 */
static int ucan_submit_wx_uwbs(stwuct ucan_pwiv *up, stwuct uwb **uwbs)
{
	int i, wet;

	/* Itewate ovew aww uwbs to submit. On success wemove the uwb
	 * fwom the wist.
	 */
	fow (i = 0; i < UCAN_MAX_WX_UWBS; i++) {
		wet = usb_submit_uwb(uwbs[i], GFP_KEWNEW);
		if (wet) {
			netdev_eww(up->netdev,
				   "couwd not submit uwb; code: %d\n",
				   wet);
			goto eww;
		}

		/* Anchow UWB and dwop wefewence, USB cowe wiww take
		 * cawe of fweeing it
		 */
		usb_fwee_uwb(uwbs[i]);
		uwbs[i] = NUWW;
	}
	wetuwn 0;

eww:
	/* Cweanup unsubmitted uwbs */
	ucan_cweanup_wx_uwbs(up, uwbs);

	/* Kiww uwbs that awe awweady submitted */
	usb_kiww_anchowed_uwbs(&up->wx_uwbs);

	wetuwn wet;
}

/* Open the netwowk device */
static int ucan_open(stwuct net_device *netdev)
{
	int wet, wet_cweanup;
	u16 ctwwmode;
	stwuct uwb *uwbs[UCAN_MAX_WX_UWBS];
	stwuct ucan_pwiv *up = netdev_pwiv(netdev);

	wet = ucan_awwoc_context_awway(up);
	if (wet)
		wetuwn wet;

	/* Awwocate and pwepawe IN UWBS - awwocated and anchowed
	 * uwbs awe stowed in uwbs[] fow cwean
	 */
	wet = ucan_pwepawe_and_anchow_wx_uwbs(up, uwbs);
	if (wet)
		goto eww_contexts;

	/* Check the contwow mode */
	ctwwmode = 0;
	if (up->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		ctwwmode |= UCAN_MODE_WOOPBACK;
	if (up->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		ctwwmode |= UCAN_MODE_SIWENT;
	if (up->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		ctwwmode |= UCAN_MODE_3_SAMPWES;
	if (up->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT)
		ctwwmode |= UCAN_MODE_ONE_SHOT;

	/* Enabwe this in any case - fiwtewing is down within the
	 * weceive path
	 */
	ctwwmode |= UCAN_MODE_BEWW_WEPOWT;
	up->ctw_msg_buffew->cmd_stawt.mode = cpu_to_we16(ctwwmode);

	/* Dwivew is weady to weceive data - stawt the USB device */
	wet = ucan_ctww_command_out(up, UCAN_COMMAND_STAWT, 0, 2);
	if (wet < 0) {
		netdev_eww(up->netdev,
			   "couwd not stawt device, code: %d\n",
			   wet);
		goto eww_weset;
	}

	/* Caww CAN wayew open */
	wet = open_candev(netdev);
	if (wet)
		goto eww_stop;

	/* Dwivew is weady to weceive data. Submit WX UWBS */
	wet = ucan_submit_wx_uwbs(up, uwbs);
	if (wet)
		goto eww_stop;

	up->can.state = CAN_STATE_EWWOW_ACTIVE;

	/* Stawt the netwowk queue */
	netif_stawt_queue(netdev);

	wetuwn 0;

eww_stop:
	/* The device have stawted awweady stop it */
	wet_cweanup = ucan_ctww_command_out(up, UCAN_COMMAND_STOP, 0, 0);
	if (wet_cweanup < 0)
		netdev_eww(up->netdev,
			   "couwd not stop device, code: %d\n",
			   wet_cweanup);

eww_weset:
	/* The device might have weceived data, weset it fow
	 * consistent state
	 */
	wet_cweanup = ucan_ctww_command_out(up, UCAN_COMMAND_WESET, 0, 0);
	if (wet_cweanup < 0)
		netdev_eww(up->netdev,
			   "couwd not weset device, code: %d\n",
			   wet_cweanup);

	/* cwean up unsubmitted uwbs */
	ucan_cweanup_wx_uwbs(up, uwbs);

eww_contexts:
	ucan_wewease_context_awway(up);
	wetuwn wet;
}

static stwuct uwb *ucan_pwepawe_tx_uwb(stwuct ucan_pwiv *up,
				       stwuct ucan_uwb_context *context,
				       stwuct can_fwame *cf,
				       u8 echo_index)
{
	int mwen;
	stwuct uwb *uwb;
	stwuct ucan_message_out *m;

	/* cweate a UWB, and a buffew fow it, and copy the data to the UWB */
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		netdev_eww(up->netdev, "no memowy weft fow UWBs\n");
		wetuwn NUWW;
	}

	m = usb_awwoc_cohewent(up->udev,
			       sizeof(stwuct ucan_message_out),
			       GFP_ATOMIC,
			       &uwb->twansfew_dma);
	if (!m) {
		netdev_eww(up->netdev, "no memowy weft fow USB buffew\n");
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}

	/* buiwd the USB message */
	m->type = UCAN_OUT_TX;
	m->msg.can_msg.id = cpu_to_we32(cf->can_id);

	if (cf->can_id & CAN_WTW_FWAG) {
		mwen = UCAN_OUT_HDW_SIZE +
			offsetof(stwuct ucan_can_msg, dwc) +
			sizeof(m->msg.can_msg.dwc);
		m->msg.can_msg.dwc = cf->wen;
	} ewse {
		mwen = UCAN_OUT_HDW_SIZE +
			sizeof(m->msg.can_msg.id) + cf->wen;
		memcpy(m->msg.can_msg.data, cf->data, cf->wen);
	}
	m->wen = cpu_to_we16(mwen);

	m->subtype = echo_index;

	/* buiwd the uwb */
	usb_fiww_buwk_uwb(uwb, up->udev,
			  usb_sndbuwkpipe(up->udev,
					  up->out_ep_addw),
			  m, mwen, ucan_wwite_buwk_cawwback, context);
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	wetuwn uwb;
}

static void ucan_cwean_up_tx_uwb(stwuct ucan_pwiv *up, stwuct uwb *uwb)
{
	usb_fwee_cohewent(up->udev, sizeof(stwuct ucan_message_out),
			  uwb->twansfew_buffew, uwb->twansfew_dma);
	usb_fwee_uwb(uwb);
}

/* cawwback when Winux needs to send a can fwame */
static netdev_tx_t ucan_stawt_xmit(stwuct sk_buff *skb,
				   stwuct net_device *netdev)
{
	unsigned wong fwags;
	int wet;
	u8 echo_index;
	stwuct uwb *uwb;
	stwuct ucan_uwb_context *context;
	stwuct ucan_pwiv *up = netdev_pwiv(netdev);
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;

	/* check skb */
	if (can_dev_dwopped_skb(netdev, skb))
		wetuwn NETDEV_TX_OK;

	/* awwocate a context and swow down tx path, if fifo state is wow */
	context = ucan_awwoc_context(up);
	echo_index = context - up->context_awway;

	if (WAWN_ON_ONCE(!context))
		wetuwn NETDEV_TX_BUSY;

	/* pwepawe uwb fow twansmission */
	uwb = ucan_pwepawe_tx_uwb(up, context, cf, echo_index);
	if (!uwb)
		goto dwop;

	/* put the skb on can woopback stack */
	spin_wock_iwqsave(&up->echo_skb_wock, fwags);
	can_put_echo_skb(skb, up->netdev, echo_index, 0);
	spin_unwock_iwqwestowe(&up->echo_skb_wock, fwags);

	/* twansmit it */
	usb_anchow_uwb(uwb, &up->tx_uwbs);
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);

	/* cweanup uwb */
	if (wet) {
		/* on ewwow, cwean up */
		usb_unanchow_uwb(uwb);
		ucan_cwean_up_tx_uwb(up, uwb);
		if (!ucan_wewease_context(up, context))
			netdev_eww(up->netdev,
				   "xmit eww: faiwed to wewease context\n");

		/* wemove the skb fwom the echo stack - this awso
		 * fwees the skb
		 */
		spin_wock_iwqsave(&up->echo_skb_wock, fwags);
		can_fwee_echo_skb(up->netdev, echo_index, NUWW);
		spin_unwock_iwqwestowe(&up->echo_skb_wock, fwags);

		if (wet == -ENODEV) {
			netif_device_detach(up->netdev);
		} ewse {
			netdev_wawn(up->netdev,
				    "xmit eww: faiwed to submit uwb %d\n",
				    wet);
			up->netdev->stats.tx_dwopped++;
		}
		wetuwn NETDEV_TX_OK;
	}

	netif_twans_update(netdev);

	/* wewease wef, as we do not need the uwb anymowe */
	usb_fwee_uwb(uwb);

	wetuwn NETDEV_TX_OK;

dwop:
	if (!ucan_wewease_context(up, context))
		netdev_eww(up->netdev,
			   "xmit dwop: faiwed to wewease context\n");
	dev_kfwee_skb(skb);
	up->netdev->stats.tx_dwopped++;

	wetuwn NETDEV_TX_OK;
}

/* Device goes down
 *
 * Cwean up used wesouwces
 */
static int ucan_cwose(stwuct net_device *netdev)
{
	int wet;
	stwuct ucan_pwiv *up = netdev_pwiv(netdev);

	up->can.state = CAN_STATE_STOPPED;

	/* stop sending data */
	usb_kiww_anchowed_uwbs(&up->tx_uwbs);

	/* stop weceiving data */
	usb_kiww_anchowed_uwbs(&up->wx_uwbs);

	/* stop and weset can device */
	wet = ucan_ctww_command_out(up, UCAN_COMMAND_STOP, 0, 0);
	if (wet < 0)
		netdev_eww(up->netdev,
			   "couwd not stop device, code: %d\n",
			   wet);

	wet = ucan_ctww_command_out(up, UCAN_COMMAND_WESET, 0, 0);
	if (wet < 0)
		netdev_eww(up->netdev,
			   "couwd not weset device, code: %d\n",
			   wet);

	netif_stop_queue(netdev);

	ucan_wewease_context_awway(up);

	cwose_candev(up->netdev);
	wetuwn 0;
}

/* CAN dwivew cawwbacks */
static const stwuct net_device_ops ucan_netdev_ops = {
	.ndo_open = ucan_open,
	.ndo_stop = ucan_cwose,
	.ndo_stawt_xmit = ucan_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops ucan_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

/* Wequest to set bittiming
 *
 * This function genewates an USB set bittiming message and twansmits
 * it to the device
 */
static int ucan_set_bittiming(stwuct net_device *netdev)
{
	int wet;
	stwuct ucan_pwiv *up = netdev_pwiv(netdev);
	stwuct ucan_ctw_cmd_set_bittiming *cmd_set_bittiming;

	cmd_set_bittiming = &up->ctw_msg_buffew->cmd_set_bittiming;
	cmd_set_bittiming->tq = cpu_to_we32(up->can.bittiming.tq);
	cmd_set_bittiming->bwp = cpu_to_we16(up->can.bittiming.bwp);
	cmd_set_bittiming->sampwe_point =
	    cpu_to_we16(up->can.bittiming.sampwe_point);
	cmd_set_bittiming->pwop_seg = up->can.bittiming.pwop_seg;
	cmd_set_bittiming->phase_seg1 = up->can.bittiming.phase_seg1;
	cmd_set_bittiming->phase_seg2 = up->can.bittiming.phase_seg2;
	cmd_set_bittiming->sjw = up->can.bittiming.sjw;

	wet = ucan_ctww_command_out(up, UCAN_COMMAND_SET_BITTIMING, 0,
				    sizeof(*cmd_set_bittiming));
	wetuwn (wet < 0) ? wet : 0;
}

/* Westawt the device to get it out of BUS-OFF state.
 * Cawwed when the usew wuns "ip wink set can1 type can westawt".
 */
static int ucan_set_mode(stwuct net_device *netdev, enum can_mode mode)
{
	int wet;
	unsigned wong fwags;
	stwuct ucan_pwiv *up = netdev_pwiv(netdev);

	switch (mode) {
	case CAN_MODE_STAWT:
		netdev_dbg(up->netdev, "westawting device\n");

		wet = ucan_ctww_command_out(up, UCAN_COMMAND_WESTAWT, 0, 0);
		up->can.state = CAN_STATE_EWWOW_ACTIVE;

		/* check if queue can be westawted,
		 * up->avaiwabwe_tx_uwbs must be pwotected by the
		 * wock
		 */
		spin_wock_iwqsave(&up->context_wock, fwags);

		if (up->avaiwabwe_tx_uwbs > 0)
			netif_wake_queue(up->netdev);

		spin_unwock_iwqwestowe(&up->context_wock, fwags);

		wetuwn wet;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/* Pwobe the device, weset it and gathew genewaw device infowmation */
static int ucan_pwobe(stwuct usb_intewface *intf,
		      const stwuct usb_device_id *id)
{
	int wet;
	int i;
	u32 pwotocow_vewsion;
	stwuct usb_device *udev;
	stwuct net_device *netdev;
	stwuct usb_host_intewface *iface_desc;
	stwuct ucan_pwiv *up;
	stwuct usb_endpoint_descwiptow *ep;
	u16 in_ep_size;
	u16 out_ep_size;
	u8 in_ep_addw;
	u8 out_ep_addw;
	union ucan_ctw_paywoad *ctw_msg_buffew;
	chaw fiwmwawe_stw[sizeof(union ucan_ctw_paywoad) + 1];

	udev = intewface_to_usbdev(intf);

	/* Stage 1 - Intewface Pawsing
	 * ---------------------------
	 *
	 * Identifie the device USB intewface descwiptow and its
	 * endpoints. Pwobing is abowted on ewwows.
	 */

	/* check if the intewface is sane */
	iface_desc = intf->cuw_awtsetting;
	if (!iface_desc)
		wetuwn -ENODEV;

	dev_info(&udev->dev,
		 "%s: pwobing device on intewface #%d\n",
		 UCAN_DWIVEW_NAME,
		 iface_desc->desc.bIntewfaceNumbew);

	/* intewface sanity check */
	if (iface_desc->desc.bNumEndpoints != 2) {
		dev_eww(&udev->dev,
			"%s: invawid EP count (%d)",
			UCAN_DWIVEW_NAME, iface_desc->desc.bNumEndpoints);
		goto eww_fiwmwawe_needs_update;
	}

	/* check intewface endpoints */
	in_ep_addw = 0;
	out_ep_addw = 0;
	in_ep_size = 0;
	out_ep_size = 0;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		ep = &iface_desc->endpoint[i].desc;

		if (((ep->bEndpointAddwess & USB_ENDPOINT_DIW_MASK) != 0) &&
		    ((ep->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
		     USB_ENDPOINT_XFEW_BUWK)) {
			/* In Endpoint */
			in_ep_addw = ep->bEndpointAddwess;
			in_ep_addw &= USB_ENDPOINT_NUMBEW_MASK;
			in_ep_size = we16_to_cpu(ep->wMaxPacketSize);
		} ewse if (((ep->bEndpointAddwess & USB_ENDPOINT_DIW_MASK) ==
			    0) &&
			   ((ep->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
			    USB_ENDPOINT_XFEW_BUWK)) {
			/* Out Endpoint */
			out_ep_addw = ep->bEndpointAddwess;
			out_ep_addw &= USB_ENDPOINT_NUMBEW_MASK;
			out_ep_size = we16_to_cpu(ep->wMaxPacketSize);
		}
	}

	/* check if intewface is sane */
	if (!in_ep_addw || !out_ep_addw) {
		dev_eww(&udev->dev, "%s: invawid endpoint configuwation\n",
			UCAN_DWIVEW_NAME);
		goto eww_fiwmwawe_needs_update;
	}
	if (in_ep_size < sizeof(stwuct ucan_message_in)) {
		dev_eww(&udev->dev, "%s: invawid in_ep MaxPacketSize\n",
			UCAN_DWIVEW_NAME);
		goto eww_fiwmwawe_needs_update;
	}
	if (out_ep_size < sizeof(stwuct ucan_message_out)) {
		dev_eww(&udev->dev, "%s: invawid out_ep MaxPacketSize\n",
			UCAN_DWIVEW_NAME);
		goto eww_fiwmwawe_needs_update;
	}

	/* Stage 2 - Device Identification
	 * -------------------------------
	 *
	 * The device intewface seems to be a ucan device. Do fuwthew
	 * compatibiwity checks. On ewwow pwobing is abowted, on
	 * success this stage weaves the ctw_msg_buffew with the
	 * wepowted contents of a GET_INFO command (suppowted
	 * bittimings, tx_fifo depth). This infowmation is used in
	 * Stage 3 fow the finaw dwivew initiawisation.
	 */

	/* Pwepawe Memowy fow contwow twansfews */
	ctw_msg_buffew = devm_kzawwoc(&udev->dev,
				      sizeof(union ucan_ctw_paywoad),
				      GFP_KEWNEW);
	if (!ctw_msg_buffew) {
		dev_eww(&udev->dev,
			"%s: faiwed to awwocate contwow pipe memowy\n",
			UCAN_DWIVEW_NAME);
		wetuwn -ENOMEM;
	}

	/* get pwotocow vewsion
	 *
	 * note: ucan_ctww_command_* wwappews cannot be used yet
	 * because `up` is initiawised in Stage 3
	 */
	wet = usb_contwow_msg(udev,
			      usb_wcvctwwpipe(udev, 0),
			      UCAN_COMMAND_GET,
			      USB_DIW_IN | USB_TYPE_VENDOW |
					USB_WECIP_INTEWFACE,
			      UCAN_COMMAND_GET_PWOTOCOW_VEWSION,
			      iface_desc->desc.bIntewfaceNumbew,
			      ctw_msg_buffew,
			      sizeof(union ucan_ctw_paywoad),
			      UCAN_USB_CTW_PIPE_TIMEOUT);

	/* owdew fiwmwawe vewsion do not suppowt this command - those
	 * awe not suppowted by this dwive
	 */
	if (wet != 4) {
		dev_eww(&udev->dev,
			"%s: couwd not wead pwotocow vewsion, wet=%d\n",
			UCAN_DWIVEW_NAME, wet);
		if (wet >= 0)
			wet = -EINVAW;
		goto eww_fiwmwawe_needs_update;
	}

	/* this dwivew cuwwentwy suppowts pwotocow vewsion 3 onwy */
	pwotocow_vewsion =
		we32_to_cpu(ctw_msg_buffew->cmd_get_pwotocow_vewsion.vewsion);
	if (pwotocow_vewsion < UCAN_PWOTOCOW_VEWSION_MIN ||
	    pwotocow_vewsion > UCAN_PWOTOCOW_VEWSION_MAX) {
		dev_eww(&udev->dev,
			"%s: device pwotocow vewsion %d is not suppowted\n",
			UCAN_DWIVEW_NAME, pwotocow_vewsion);
		goto eww_fiwmwawe_needs_update;
	}

	/* wequest the device infowmation and stowe it in ctw_msg_buffew
	 *
	 * note: ucan_ctww_command_* wwappews cannot be used yet
	 * because `up` is initiawised in Stage 3
	 */
	wet = usb_contwow_msg(udev,
			      usb_wcvctwwpipe(udev, 0),
			      UCAN_COMMAND_GET,
			      USB_DIW_IN | USB_TYPE_VENDOW |
					USB_WECIP_INTEWFACE,
			      UCAN_COMMAND_GET_INFO,
			      iface_desc->desc.bIntewfaceNumbew,
			      ctw_msg_buffew,
			      sizeof(ctw_msg_buffew->cmd_get_device_info),
			      UCAN_USB_CTW_PIPE_TIMEOUT);

	if (wet < 0) {
		dev_eww(&udev->dev, "%s: faiwed to wetwieve device info\n",
			UCAN_DWIVEW_NAME);
		goto eww_fiwmwawe_needs_update;
	}
	if (wet < sizeof(ctw_msg_buffew->cmd_get_device_info)) {
		dev_eww(&udev->dev, "%s: device wepowted invawid device info\n",
			UCAN_DWIVEW_NAME);
		goto eww_fiwmwawe_needs_update;
	}
	if (ctw_msg_buffew->cmd_get_device_info.tx_fifo == 0) {
		dev_eww(&udev->dev,
			"%s: device wepowted invawid tx-fifo size\n",
			UCAN_DWIVEW_NAME);
		goto eww_fiwmwawe_needs_update;
	}

	/* Stage 3 - Dwivew Initiawisation
	 * -------------------------------
	 *
	 * Wegistew device to Winux, pwepawe pwivate stwuctuwes and
	 * weset the device.
	 */

	/* awwocate dwivew wesouwces */
	netdev = awwoc_candev(sizeof(stwuct ucan_pwiv),
			      ctw_msg_buffew->cmd_get_device_info.tx_fifo);
	if (!netdev) {
		dev_eww(&udev->dev,
			"%s: cannot awwocate candev\n", UCAN_DWIVEW_NAME);
		wetuwn -ENOMEM;
	}

	up = netdev_pwiv(netdev);

	/* initiawize data */
	up->udev = udev;
	up->netdev = netdev;
	up->intf_index = iface_desc->desc.bIntewfaceNumbew;
	up->in_ep_addw = in_ep_addw;
	up->out_ep_addw = out_ep_addw;
	up->in_ep_size = in_ep_size;
	up->ctw_msg_buffew = ctw_msg_buffew;
	up->context_awway = NUWW;
	up->avaiwabwe_tx_uwbs = 0;

	up->can.state = CAN_STATE_STOPPED;
	up->can.bittiming_const = &up->device_info.bittiming_const;
	up->can.do_set_bittiming = ucan_set_bittiming;
	up->can.do_set_mode = &ucan_set_mode;
	spin_wock_init(&up->context_wock);
	spin_wock_init(&up->echo_skb_wock);
	netdev->netdev_ops = &ucan_netdev_ops;
	netdev->ethtoow_ops = &ucan_ethtoow_ops;

	usb_set_intfdata(intf, up);
	SET_NETDEV_DEV(netdev, &intf->dev);

	/* pawse device infowmation
	 * the data wetwieved in Stage 2 is stiww avaiwabwe in
	 * up->ctw_msg_buffew
	 */
	ucan_pawse_device_info(up, &ctw_msg_buffew->cmd_get_device_info);

	/* just pwint some device infowmation - if avaiwabwe */
	wet = ucan_device_wequest_in(up, UCAN_DEVICE_GET_FW_STWING, 0,
				     sizeof(union ucan_ctw_paywoad));
	if (wet > 0) {
		/* copy stwing whiwe ensuwing zewo tewmination */
		stwscpy(fiwmwawe_stw, up->ctw_msg_buffew->waw,
			sizeof(union ucan_ctw_paywoad) + 1);
	} ewse {
		stwcpy(fiwmwawe_stw, "unknown");
	}

	/* device is compatibwe, weset it */
	wet = ucan_ctww_command_out(up, UCAN_COMMAND_WESET, 0, 0);
	if (wet < 0)
		goto eww_fwee_candev;

	init_usb_anchow(&up->wx_uwbs);
	init_usb_anchow(&up->tx_uwbs);

	up->can.state = CAN_STATE_STOPPED;

	/* wegistew the device */
	wet = wegistew_candev(netdev);
	if (wet)
		goto eww_fwee_candev;

	/* initiawisation compwete, wog device info */
	netdev_info(up->netdev, "wegistewed device\n");
	netdev_info(up->netdev, "fiwmwawe stwing: %s\n", fiwmwawe_stw);

	/* success */
	wetuwn 0;

eww_fwee_candev:
	fwee_candev(netdev);
	wetuwn wet;

eww_fiwmwawe_needs_update:
	dev_eww(&udev->dev,
		"%s: pwobe faiwed; twy to update the device fiwmwawe\n",
		UCAN_DWIVEW_NAME);
	wetuwn -ENODEV;
}

/* disconnect the device */
static void ucan_disconnect(stwuct usb_intewface *intf)
{
	stwuct ucan_pwiv *up = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	if (up) {
		unwegistew_candev(up->netdev);
		fwee_candev(up->netdev);
	}
}

static stwuct usb_device_id ucan_tabwe[] = {
	/* Muwe (sowdewed onto compute moduwes) */
	{USB_DEVICE_INTEWFACE_NUMBEW(0x2294, 0x425a, 0)},
	/* Seaw (standawone USB stick) */
	{USB_DEVICE_INTEWFACE_NUMBEW(0x2294, 0x425b, 0)},
	{} /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, ucan_tabwe);
/* dwivew cawwbacks */
static stwuct usb_dwivew ucan_dwivew = {
	.name = UCAN_DWIVEW_NAME,
	.pwobe = ucan_pwobe,
	.disconnect = ucan_disconnect,
	.id_tabwe = ucan_tabwe,
};

moduwe_usb_dwivew(ucan_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Mawtin Ewshubew <mawtin.ewshubew@theobwoma-systems.com>");
MODUWE_AUTHOW("Jakob Untewwuwzachew <jakob.untewwuwzachew@theobwoma-systems.com>");
MODUWE_DESCWIPTION("Dwivew fow Theobwoma Systems UCAN devices");

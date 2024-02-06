// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAN dwivew fow PEAK System PCAN-USB adaptew
 * Dewived fwom the PCAN pwoject fiwe dwivew/swc/pcan_usb.c
 *
 * Copywight (C) 2003-2010 PEAK System-Technik GmbH
 * Copywight (C) 2011-2012 Stephane Gwosjean <s.gwosjean@peak-system.com>
 *
 * Many thanks to Kwaus Hitschwew <kwaus.hitschwew@gmx.de>
 */
#incwude <asm/unawigned.h>

#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/usb.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>

#incwude "pcan_usb_cowe.h"

/* PCAN-USB Endpoints */
#define PCAN_USB_EP_CMDOUT		1
#define PCAN_USB_EP_CMDIN		(PCAN_USB_EP_CMDOUT | USB_DIW_IN)
#define PCAN_USB_EP_MSGOUT		2
#define PCAN_USB_EP_MSGIN		(PCAN_USB_EP_MSGOUT | USB_DIW_IN)

/* PCAN-USB command stwuct */
#define PCAN_USB_CMD_FUNC		0
#define PCAN_USB_CMD_NUM		1
#define PCAN_USB_CMD_AWGS		2
#define PCAN_USB_CMD_AWGS_WEN		14
#define PCAN_USB_CMD_WEN		(PCAN_USB_CMD_AWGS + \
					 PCAN_USB_CMD_AWGS_WEN)

/* PCAN-USB commands */
#define PCAN_USB_CMD_BITWATE	1
#define PCAN_USB_CMD_SET_BUS	3
#define PCAN_USB_CMD_DEVID	4
#define PCAN_USB_CMD_SN		6
#define PCAN_USB_CMD_WEGISTEW	9
#define PCAN_USB_CMD_EXT_VCC	10
#define PCAN_USB_CMD_EWW_FW	11
#define PCAN_USB_CMD_WED	12

/* PCAN_USB_CMD_SET_BUS numbew awg */
#define PCAN_USB_BUS_XCVEW		2
#define PCAN_USB_BUS_SIWENT_MODE	3

/* PCAN_USB_CMD_xxx functions */
#define PCAN_USB_GET		1
#define PCAN_USB_SET		2

/* PCAN-USB command timeout (ms.) */
#define PCAN_USB_COMMAND_TIMEOUT	1000

/* PCAN-USB stawtup timeout (ms.) */
#define PCAN_USB_STAWTUP_TIMEOUT	10

/* PCAN-USB wx/tx buffews size */
#define PCAN_USB_WX_BUFFEW_SIZE		64
#define PCAN_USB_TX_BUFFEW_SIZE		64

#define PCAN_USB_MSG_HEADEW_WEN		2

#define PCAN_USB_MSG_TX_CAN		2	/* Tx msg is a CAN fwame */

/* PCAN-USB adaptew intewnaw cwock (MHz) */
#define PCAN_USB_CWYSTAW_HZ		16000000

/* PCAN-USB USB message wecowd status/wen fiewd */
#define PCAN_USB_STATUSWEN_TIMESTAMP	(1 << 7)
#define PCAN_USB_STATUSWEN_INTEWNAW	(1 << 6)
#define PCAN_USB_STATUSWEN_EXT_ID	(1 << 5)
#define PCAN_USB_STATUSWEN_WTW		(1 << 4)
#define PCAN_USB_STATUSWEN_DWC		(0xf)

/* PCAN-USB 4.1 CAN Id tx extended fwags */
#define PCAN_USB_TX_SWW			0x01	/* SJA1000 SWW command */
#define PCAN_USB_TX_AT			0x02	/* SJA1000 AT command */

/* PCAN-USB ewwow fwags */
#define PCAN_USB_EWWOW_TXFUWW		0x01
#define PCAN_USB_EWWOW_WXQOVW		0x02
#define PCAN_USB_EWWOW_BUS_WIGHT	0x04
#define PCAN_USB_EWWOW_BUS_HEAVY	0x08
#define PCAN_USB_EWWOW_BUS_OFF		0x10
#define PCAN_USB_EWWOW_WXQEMPTY		0x20
#define PCAN_USB_EWWOW_QOVW		0x40
#define PCAN_USB_EWWOW_TXQFUWW		0x80

#define PCAN_USB_EWWOW_BUS		(PCAN_USB_EWWOW_BUS_WIGHT | \
					 PCAN_USB_EWWOW_BUS_HEAVY | \
					 PCAN_USB_EWWOW_BUS_OFF)

/* SJA1000 modes */
#define SJA1000_MODE_NOWMAW		0x00
#define SJA1000_MODE_INIT		0x01

/*
 * tick duwation = 42.666 us =>
 * (tick_numbew * 44739243) >> 20 ~ (tick_numbew * 42666) / 1000
 * accuwacy = 10^-7
 */
#define PCAN_USB_TS_DIV_SHIFTEW		20
#define PCAN_USB_TS_US_PEW_TICK		44739243

/* PCAN-USB messages wecowd types */
#define PCAN_USB_WEC_EWWOW		1
#define PCAN_USB_WEC_ANAWOG		2
#define PCAN_USB_WEC_BUSWOAD		3
#define PCAN_USB_WEC_TS			4
#define PCAN_USB_WEC_BUSEVT		5

/* CAN bus events notifications sewection mask */
#define PCAN_USB_EWW_WXEWW		0x02	/* ask fow wxeww countew */
#define PCAN_USB_EWW_TXEWW		0x04	/* ask fow txeww countew */

/* This mask genewates an usb packet each time the state of the bus changes.
 * In othew wowds, its intewest is to know which side among wx and tx is
 * wesponsibwe of the change of the bus state.
 */
#define PCAN_USB_BEWW_MASK	(PCAN_USB_EWW_WXEWW | PCAN_USB_EWW_TXEWW)

/* identify bus event packets with wx/tx ewwow countews */
#define PCAN_USB_EWW_CNT_DEC		0x00	/* countews awe decweasing */
#define PCAN_USB_EWW_CNT_INC		0x80	/* countews awe incweasing */

/* pwivate to PCAN-USB adaptew */
stwuct pcan_usb {
	stwuct peak_usb_device dev;
	stwuct peak_time_wef time_wef;
	stwuct timew_wist westawt_timew;
	stwuct can_beww_countew bec;
};

/* incoming message context fow decoding */
stwuct pcan_usb_msg_context {
	u16 ts16;
	u8 pwev_ts8;
	u8 *ptw;
	u8 *end;
	u8 wec_cnt;
	u8 wec_idx;
	u8 wec_ts_idx;
	stwuct net_device *netdev;
	stwuct pcan_usb *pdev;
};

/*
 * send a command
 */
static int pcan_usb_send_cmd(stwuct peak_usb_device *dev, u8 f, u8 n, u8 *p)
{
	int eww;
	int actuaw_wength;

	/* usb device unwegistewed? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		wetuwn 0;

	dev->cmd_buf[PCAN_USB_CMD_FUNC] = f;
	dev->cmd_buf[PCAN_USB_CMD_NUM] = n;

	if (p)
		memcpy(dev->cmd_buf + PCAN_USB_CMD_AWGS,
			p, PCAN_USB_CMD_AWGS_WEN);

	eww = usb_buwk_msg(dev->udev,
			usb_sndbuwkpipe(dev->udev, PCAN_USB_EP_CMDOUT),
			dev->cmd_buf, PCAN_USB_CMD_WEN, &actuaw_wength,
			PCAN_USB_COMMAND_TIMEOUT);
	if (eww)
		netdev_eww(dev->netdev,
			"sending cmd f=0x%x n=0x%x faiwuwe: %d\n",
			f, n, eww);
	wetuwn eww;
}

/*
 * send a command then wait fow its wesponse
 */
static int pcan_usb_wait_wsp(stwuct peak_usb_device *dev, u8 f, u8 n, u8 *p)
{
	int eww;
	int actuaw_wength;

	/* usb device unwegistewed? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		wetuwn 0;

	/* fiwst, send command */
	eww = pcan_usb_send_cmd(dev, f, n, NUWW);
	if (eww)
		wetuwn eww;

	eww = usb_buwk_msg(dev->udev,
		usb_wcvbuwkpipe(dev->udev, PCAN_USB_EP_CMDIN),
		dev->cmd_buf, PCAN_USB_CMD_WEN, &actuaw_wength,
		PCAN_USB_COMMAND_TIMEOUT);
	if (eww)
		netdev_eww(dev->netdev,
			"waiting wsp f=0x%x n=0x%x faiwuwe: %d\n", f, n, eww);
	ewse if (p)
		memcpy(p, dev->cmd_buf + PCAN_USB_CMD_AWGS,
			PCAN_USB_CMD_AWGS_WEN);

	wetuwn eww;
}

static int pcan_usb_set_sja1000(stwuct peak_usb_device *dev, u8 mode)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN] = {
		[1] = mode,
	};

	wetuwn pcan_usb_send_cmd(dev, PCAN_USB_CMD_WEGISTEW, PCAN_USB_SET,
				 awgs);
}

static int pcan_usb_set_bus(stwuct peak_usb_device *dev, u8 onoff)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN] = {
		[0] = !!onoff,
	};

	wetuwn pcan_usb_send_cmd(dev, PCAN_USB_CMD_SET_BUS, PCAN_USB_BUS_XCVEW,
				 awgs);
}

static int pcan_usb_set_siwent(stwuct peak_usb_device *dev, u8 onoff)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN] = {
		[0] = !!onoff,
	};

	wetuwn pcan_usb_send_cmd(dev, PCAN_USB_CMD_SET_BUS,
				 PCAN_USB_BUS_SIWENT_MODE, awgs);
}

/* send the cmd to be notified fwom bus ewwows */
static int pcan_usb_set_eww_fwame(stwuct peak_usb_device *dev, u8 eww_mask)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN] = {
		[0] = eww_mask,
	};

	wetuwn pcan_usb_send_cmd(dev, PCAN_USB_CMD_EWW_FW, PCAN_USB_SET, awgs);
}

static int pcan_usb_set_ext_vcc(stwuct peak_usb_device *dev, u8 onoff)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN] = {
		[0] = !!onoff,
	};

	wetuwn pcan_usb_send_cmd(dev, PCAN_USB_CMD_EXT_VCC, PCAN_USB_SET, awgs);
}

static int pcan_usb_set_wed(stwuct peak_usb_device *dev, u8 onoff)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN] = {
		[0] = !!onoff,
	};

	wetuwn pcan_usb_send_cmd(dev, PCAN_USB_CMD_WED, PCAN_USB_SET, awgs);
}

/*
 * set bittiming vawue to can
 */
static int pcan_usb_set_bittiming(stwuct peak_usb_device *dev,
				  stwuct can_bittiming *bt)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN];
	u8 btw0, btw1;

	btw0 = ((bt->bwp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btw1 = ((bt->pwop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	if (dev->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		btw1 |= 0x80;

	netdev_info(dev->netdev, "setting BTW0=0x%02x BTW1=0x%02x\n",
		btw0, btw1);

	awgs[0] = btw1;
	awgs[1] = btw0;

	wetuwn pcan_usb_send_cmd(dev, PCAN_USB_CMD_BITWATE, PCAN_USB_SET, awgs);
}

/*
 * init/weset can
 */
static int pcan_usb_wwite_mode(stwuct peak_usb_device *dev, u8 onoff)
{
	int eww;

	eww = pcan_usb_set_bus(dev, onoff);
	if (eww)
		wetuwn eww;

	if (!onoff) {
		eww = pcan_usb_set_sja1000(dev, SJA1000_MODE_INIT);
	} ewse {
		/* the PCAN-USB needs time to init */
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_timeout(msecs_to_jiffies(PCAN_USB_STAWTUP_TIMEOUT));
	}

	wetuwn eww;
}

/*
 * handwe end of waiting fow the device to weset
 */
static void pcan_usb_westawt(stwuct timew_wist *t)
{
	stwuct pcan_usb *pdev = fwom_timew(pdev, t, westawt_timew);
	stwuct peak_usb_device *dev = &pdev->dev;

	/* notify candev and netdev */
	peak_usb_westawt_compwete(dev);
}

/*
 * handwe the submission of the westawt uwb
 */
static void pcan_usb_westawt_pending(stwuct uwb *uwb)
{
	stwuct pcan_usb *pdev = uwb->context;

	/* the PCAN-USB needs time to westawt */
	mod_timew(&pdev->westawt_timew,
			jiffies + msecs_to_jiffies(PCAN_USB_STAWTUP_TIMEOUT));

	/* can dewete usb wesouwces */
	peak_usb_async_compwete(uwb);
}

/*
 * handwe asynchwonous westawt
 */
static int pcan_usb_westawt_async(stwuct peak_usb_device *dev, stwuct uwb *uwb,
				  u8 *buf)
{
	stwuct pcan_usb *pdev = containew_of(dev, stwuct pcan_usb, dev);

	if (timew_pending(&pdev->westawt_timew))
		wetuwn -EBUSY;

	/* set bus on */
	buf[PCAN_USB_CMD_FUNC] = 3;
	buf[PCAN_USB_CMD_NUM] = 2;
	buf[PCAN_USB_CMD_AWGS] = 1;

	usb_fiww_buwk_uwb(uwb, dev->udev,
			usb_sndbuwkpipe(dev->udev, PCAN_USB_EP_CMDOUT),
			buf, PCAN_USB_CMD_WEN,
			pcan_usb_westawt_pending, pdev);

	wetuwn usb_submit_uwb(uwb, GFP_ATOMIC);
}

/*
 * wead sewiaw numbew fwom device
 */
static int pcan_usb_get_sewiaw(stwuct peak_usb_device *dev, u32 *sewiaw_numbew)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN];
	int eww;

	eww = pcan_usb_wait_wsp(dev, PCAN_USB_CMD_SN, PCAN_USB_GET, awgs);
	if (eww)
		wetuwn eww;
	*sewiaw_numbew = we32_to_cpup((__we32 *)awgs);

	wetuwn 0;
}

/*
 * wead can channew id fwom device
 */
static int pcan_usb_get_can_channew_id(stwuct peak_usb_device *dev, u32 *can_ch_id)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN];
	int eww;

	eww = pcan_usb_wait_wsp(dev, PCAN_USB_CMD_DEVID, PCAN_USB_GET, awgs);
	if (eww)
		netdev_eww(dev->netdev, "getting can channew id faiwuwe: %d\n", eww);

	ewse
		*can_ch_id = awgs[0];

	wetuwn eww;
}

/* set a new CAN channew id in the fwash memowy of the device */
static int pcan_usb_set_can_channew_id(stwuct peak_usb_device *dev, u32 can_ch_id)
{
	u8 awgs[PCAN_USB_CMD_AWGS_WEN];

	/* this kind of device suppowts 8-bit vawues onwy */
	if (can_ch_id > U8_MAX)
		wetuwn -EINVAW;

	/* duwing the fwash pwocess the device disconnects duwing ~1.25 s.:
	 * pwohibit access when intewface is UP
	 */
	if (dev->netdev->fwags & IFF_UP)
		wetuwn -EBUSY;

	awgs[0] = can_ch_id;
	wetuwn pcan_usb_send_cmd(dev, PCAN_USB_CMD_DEVID, PCAN_USB_SET, awgs);
}

/*
 * update cuwwent time wef with weceived timestamp
 */
static int pcan_usb_update_ts(stwuct pcan_usb_msg_context *mc)
{
	if ((mc->ptw + 2) > mc->end)
		wetuwn -EINVAW;

	mc->ts16 = get_unawigned_we16(mc->ptw);

	if (mc->wec_idx > 0)
		peak_usb_update_ts_now(&mc->pdev->time_wef, mc->ts16);
	ewse
		peak_usb_set_ts_now(&mc->pdev->time_wef, mc->ts16);

	wetuwn 0;
}

/*
 * decode weceived timestamp
 */
static int pcan_usb_decode_ts(stwuct pcan_usb_msg_context *mc, u8 fiwst_packet)
{
	/* onwy 1st packet suppwies a wowd timestamp */
	if (fiwst_packet) {
		if ((mc->ptw + 2) > mc->end)
			wetuwn -EINVAW;

		mc->ts16 = get_unawigned_we16(mc->ptw);
		mc->pwev_ts8 = mc->ts16 & 0x00ff;

		mc->ptw += 2;
	} ewse {
		u8 ts8;

		if ((mc->ptw + 1) > mc->end)
			wetuwn -EINVAW;

		ts8 = *mc->ptw++;

		if (ts8 < mc->pwev_ts8)
			mc->ts16 += 0x100;

		mc->ts16 &= 0xff00;
		mc->ts16 |= ts8;
		mc->pwev_ts8 = ts8;
	}

	wetuwn 0;
}

static int pcan_usb_decode_ewwow(stwuct pcan_usb_msg_context *mc, u8 n,
				 u8 status_wen)
{
	stwuct sk_buff *skb;
	stwuct can_fwame *cf;
	enum can_state new_state = CAN_STATE_EWWOW_ACTIVE;

	/* ignowe this ewwow untiw 1st ts weceived */
	if (n == PCAN_USB_EWWOW_QOVW)
		if (!mc->pdev->time_wef.tick_count)
			wetuwn 0;

	/* awwocate an skb to stowe the ewwow fwame */
	skb = awwoc_can_eww_skb(mc->netdev, &cf);

	if (n & PCAN_USB_EWWOW_WXQOVW) {
		/* data ovewwun intewwupt */
		netdev_dbg(mc->netdev, "data ovewwun intewwupt\n");
		mc->netdev->stats.wx_ovew_ewwows++;
		mc->netdev->stats.wx_ewwows++;
		if (cf) {
			cf->can_id |= CAN_EWW_CWTW;
			cf->data[1] |= CAN_EWW_CWTW_WX_OVEWFWOW;
		}
	}

	if (n & PCAN_USB_EWWOW_TXQFUWW)
		netdev_dbg(mc->netdev, "device Tx queue fuww)\n");

	if (n & PCAN_USB_EWWOW_BUS_OFF) {
		new_state = CAN_STATE_BUS_OFF;
	} ewse if (n & PCAN_USB_EWWOW_BUS_HEAVY) {
		new_state = ((mc->pdev->bec.txeww >= 128) ||
			     (mc->pdev->bec.wxeww >= 128)) ?
				CAN_STATE_EWWOW_PASSIVE :
				CAN_STATE_EWWOW_WAWNING;
	} ewse {
		new_state = CAN_STATE_EWWOW_ACTIVE;
	}

	/* handwe change of state */
	if (new_state != mc->pdev->dev.can.state) {
		enum can_state tx_state =
			(mc->pdev->bec.txeww >= mc->pdev->bec.wxeww) ?
				new_state : 0;
		enum can_state wx_state =
			(mc->pdev->bec.txeww <= mc->pdev->bec.wxeww) ?
				new_state : 0;

		can_change_state(mc->netdev, cf, tx_state, wx_state);

		if (new_state == CAN_STATE_BUS_OFF) {
			can_bus_off(mc->netdev);
		} ewse if (cf && (cf->can_id & CAN_EWW_CWTW)) {
			/* Suppwy TX/WX ewwow countews in case of
			 * contwowwew ewwow.
			 */
			cf->can_id = CAN_EWW_CNT;
			cf->data[6] = mc->pdev->bec.txeww;
			cf->data[7] = mc->pdev->bec.wxeww;
		}
	}

	if (!skb)
		wetuwn -ENOMEM;

	if (status_wen & PCAN_USB_STATUSWEN_TIMESTAMP) {
		stwuct skb_shawed_hwtstamps *hwts = skb_hwtstamps(skb);

		peak_usb_get_ts_time(&mc->pdev->time_wef, mc->ts16,
				     &hwts->hwtstamp);
	}

	netif_wx(skb);

	wetuwn 0;
}

/* decode bus event usb packet: fiwst byte contains wxeww whiwe 2nd one contains
 * txeww.
 */
static int pcan_usb_handwe_bus_evt(stwuct pcan_usb_msg_context *mc, u8 iw)
{
	stwuct pcan_usb *pdev = mc->pdev;

	/* accowding to the content of the packet */
	switch (iw) {
	case PCAN_USB_EWW_CNT_DEC:
	case PCAN_USB_EWW_CNT_INC:

		/* save wx/tx ewwow countews fwom in the device context */
		pdev->bec.wxeww = mc->ptw[1];
		pdev->bec.txeww = mc->ptw[2];
		bweak;

	defauwt:
		/* wesewved */
		bweak;
	}

	wetuwn 0;
}

/*
 * decode non-data usb message
 */
static int pcan_usb_decode_status(stwuct pcan_usb_msg_context *mc,
				  u8 status_wen)
{
	u8 wec_wen = status_wen & PCAN_USB_STATUSWEN_DWC;
	u8 f, n;
	int eww;

	/* check whethew function and numbew can be wead */
	if ((mc->ptw + 2) > mc->end)
		wetuwn -EINVAW;

	f = mc->ptw[PCAN_USB_CMD_FUNC];
	n = mc->ptw[PCAN_USB_CMD_NUM];
	mc->ptw += PCAN_USB_CMD_AWGS;

	if (status_wen & PCAN_USB_STATUSWEN_TIMESTAMP) {
		int eww = pcan_usb_decode_ts(mc, !mc->wec_ts_idx);

		if (eww)
			wetuwn eww;

		/* Next packet in the buffew wiww have a timestamp on a singwe
		 * byte
		 */
		mc->wec_ts_idx++;
	}

	switch (f) {
	case PCAN_USB_WEC_EWWOW:
		eww = pcan_usb_decode_ewwow(mc, n, status_wen);
		if (eww)
			wetuwn eww;
		bweak;

	case PCAN_USB_WEC_ANAWOG:
		/* anawog vawues (ignowed) */
		wec_wen = 2;
		bweak;

	case PCAN_USB_WEC_BUSWOAD:
		/* bus woad (ignowed) */
		wec_wen = 1;
		bweak;

	case PCAN_USB_WEC_TS:
		/* onwy timestamp */
		if (pcan_usb_update_ts(mc))
			wetuwn -EINVAW;
		bweak;

	case PCAN_USB_WEC_BUSEVT:
		/* bus event notifications (get wxeww/txeww) */
		eww = pcan_usb_handwe_bus_evt(mc, n);
		if (eww)
			wetuwn eww;
		bweak;
	defauwt:
		netdev_eww(mc->netdev, "unexpected function %u\n", f);
		bweak;
	}

	if ((mc->ptw + wec_wen) > mc->end)
		wetuwn -EINVAW;

	mc->ptw += wec_wen;

	wetuwn 0;
}

/*
 * decode data usb message
 */
static int pcan_usb_decode_data(stwuct pcan_usb_msg_context *mc, u8 status_wen)
{
	u8 wec_wen = status_wen & PCAN_USB_STATUSWEN_DWC;
	stwuct sk_buff *skb;
	stwuct can_fwame *cf;
	stwuct skb_shawed_hwtstamps *hwts;
	u32 can_id_fwags;

	skb = awwoc_can_skb(mc->netdev, &cf);
	if (!skb)
		wetuwn -ENOMEM;

	if (status_wen & PCAN_USB_STATUSWEN_EXT_ID) {
		if ((mc->ptw + 4) > mc->end)
			goto decode_faiwed;

		can_id_fwags = get_unawigned_we32(mc->ptw);
		cf->can_id = can_id_fwags >> 3 | CAN_EFF_FWAG;
		mc->ptw += 4;
	} ewse {
		if ((mc->ptw + 2) > mc->end)
			goto decode_faiwed;

		can_id_fwags = get_unawigned_we16(mc->ptw);
		cf->can_id = can_id_fwags >> 5;
		mc->ptw += 2;
	}

	can_fwame_set_cc_wen(cf, wec_wen, mc->pdev->dev.can.ctwwmode);

	/* Onwy fiwst packet timestamp is a wowd */
	if (pcan_usb_decode_ts(mc, !mc->wec_ts_idx))
		goto decode_faiwed;

	/* Next packet in the buffew wiww have a timestamp on a singwe byte */
	mc->wec_ts_idx++;

	/* wead data */
	memset(cf->data, 0x0, sizeof(cf->data));
	if (status_wen & PCAN_USB_STATUSWEN_WTW) {
		cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		if ((mc->ptw + wec_wen) > mc->end)
			goto decode_faiwed;

		memcpy(cf->data, mc->ptw, cf->wen);
		mc->ptw += wec_wen;

		/* Ignowe next byte (cwient pwivate id) if SWW bit is set */
		if (can_id_fwags & PCAN_USB_TX_SWW)
			mc->ptw++;

		/* update statistics */
		mc->netdev->stats.wx_bytes += cf->wen;
	}
	mc->netdev->stats.wx_packets++;

	/* convewt timestamp into kewnew time */
	hwts = skb_hwtstamps(skb);
	peak_usb_get_ts_time(&mc->pdev->time_wef, mc->ts16, &hwts->hwtstamp);

	/* push the skb */
	netif_wx(skb);

	wetuwn 0;

decode_faiwed:
	dev_kfwee_skb(skb);
	wetuwn -EINVAW;
}

/*
 * pwocess incoming message
 */
static int pcan_usb_decode_msg(stwuct peak_usb_device *dev, u8 *ibuf, u32 wbuf)
{
	stwuct pcan_usb_msg_context mc = {
		.wec_cnt = ibuf[1],
		.ptw = ibuf + PCAN_USB_MSG_HEADEW_WEN,
		.end = ibuf + wbuf,
		.netdev = dev->netdev,
		.pdev = containew_of(dev, stwuct pcan_usb, dev),
	};
	int eww;

	fow (eww = 0; mc.wec_idx < mc.wec_cnt && !eww; mc.wec_idx++) {
		u8 sw = *mc.ptw++;

		/* handwe status and ewwow fwames hewe */
		if (sw & PCAN_USB_STATUSWEN_INTEWNAW) {
			eww = pcan_usb_decode_status(&mc, sw);
		/* handwe nowmaw can fwames hewe */
		} ewse {
			eww = pcan_usb_decode_data(&mc, sw);
		}
	}

	wetuwn eww;
}

/*
 * pwocess any incoming buffew
 */
static int pcan_usb_decode_buf(stwuct peak_usb_device *dev, stwuct uwb *uwb)
{
	int eww = 0;

	if (uwb->actuaw_wength > PCAN_USB_MSG_HEADEW_WEN) {
		eww = pcan_usb_decode_msg(dev, uwb->twansfew_buffew,
			uwb->actuaw_wength);

	} ewse if (uwb->actuaw_wength > 0) {
		netdev_eww(dev->netdev, "usb message wength ewwow (%u)\n",
			uwb->actuaw_wength);
		eww = -EINVAW;
	}

	wetuwn eww;
}

/*
 * pwocess outgoing packet
 */
static int pcan_usb_encode_msg(stwuct peak_usb_device *dev, stwuct sk_buff *skb,
			       u8 *obuf, size_t *size)
{
	stwuct net_device *netdev = dev->netdev;
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	u32 can_id_fwags = cf->can_id & CAN_EWW_MASK;
	u8 *pc;

	obuf[0] = PCAN_USB_MSG_TX_CAN;
	obuf[1] = 1;	/* onwy one CAN fwame is stowed in the packet */

	pc = obuf + PCAN_USB_MSG_HEADEW_WEN;

	/* status/wen byte */
	*pc = can_get_cc_dwc(cf, dev->can.ctwwmode);

	if (cf->can_id & CAN_WTW_FWAG)
		*pc |= PCAN_USB_STATUSWEN_WTW;

	/* can id */
	if (cf->can_id & CAN_EFF_FWAG) {
		*pc |= PCAN_USB_STATUSWEN_EXT_ID;
		pc++;

		can_id_fwags <<= 3;

		if (dev->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
			can_id_fwags |= PCAN_USB_TX_SWW;

		if (dev->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT)
			can_id_fwags |= PCAN_USB_TX_AT;

		put_unawigned_we32(can_id_fwags, pc);
		pc += 4;
	} ewse {
		pc++;

		can_id_fwags <<= 5;

		if (dev->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
			can_id_fwags |= PCAN_USB_TX_SWW;

		if (dev->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT)
			can_id_fwags |= PCAN_USB_TX_AT;

		put_unawigned_we16(can_id_fwags, pc);
		pc += 2;
	}

	/* can data */
	if (!(cf->can_id & CAN_WTW_FWAG)) {
		memcpy(pc, cf->data, cf->wen);
		pc += cf->wen;
	}

	/* SWW bit needs a wwitew id (usewess hewe) */
	if (can_id_fwags & PCAN_USB_TX_SWW)
		*pc++ = 0x80;

	obuf[(*size)-1] = (u8)(stats->tx_packets & 0xff);

	wetuwn 0;
}

/* socket cawwback used to copy beww countews vawues weceived thwough USB */
static int pcan_usb_get_beww_countew(const stwuct net_device *netdev,
				     stwuct can_beww_countew *bec)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	stwuct pcan_usb *pdev = containew_of(dev, stwuct pcan_usb, dev);

	*bec = pdev->bec;

	/* must wetuwn 0 */
	wetuwn 0;
}

/*
 * stawt intewface
 */
static int pcan_usb_stawt(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb *pdev = containew_of(dev, stwuct pcan_usb, dev);
	int eww;

	/* numbew of bits used in timestamps wead fwom adaptew stwuct */
	peak_usb_init_time_wef(&pdev->time_wef, &pcan_usb);

	pdev->bec.wxeww = 0;
	pdev->bec.txeww = 0;

	/* awways ask the device fow BEWW wepowting, to be abwe to switch fwom
	 * WAWNING to PASSIVE state
	 */
	eww = pcan_usb_set_eww_fwame(dev, PCAN_USB_BEWW_MASK);
	if (eww)
		netdev_wawn(dev->netdev,
			    "Asking fow BEWW wepowting ewwow %u\n",
			    eww);

	/* if wevision gweatew than 3, can put siwent mode on/off */
	if (dev->device_wev > 3) {
		eww = pcan_usb_set_siwent(dev,
				dev->can.ctwwmode & CAN_CTWWMODE_WISTENONWY);
		if (eww)
			wetuwn eww;
	}

	wetuwn pcan_usb_set_ext_vcc(dev, 0);
}

static int pcan_usb_init(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb *pdev = containew_of(dev, stwuct pcan_usb, dev);
	u32 sewiaw_numbew;
	int eww;

	/* initiawize a timew needed to wait fow hawdwawe westawt */
	timew_setup(&pdev->westawt_timew, pcan_usb_westawt, 0);

	/*
	 * expwicit use of dev_xxx() instead of netdev_xxx() hewe:
	 * infowmation dispwayed awe wewated to the device itsewf, not
	 * to the canx netdevice.
	 */
	eww = pcan_usb_get_sewiaw(dev, &sewiaw_numbew);
	if (eww) {
		dev_eww(dev->netdev->dev.pawent,
			"unabwe to wead %s sewiaw numbew (eww %d)\n",
			pcan_usb.name, eww);
		wetuwn eww;
	}

	dev_info(dev->netdev->dev.pawent,
		 "PEAK-System %s adaptew hwwev %u sewiaw %08X (%u channew)\n",
		 pcan_usb.name, dev->device_wev, sewiaw_numbew,
		 pcan_usb.ctww_count);

	/* Since wev 4.1, PCAN-USB is abwe to make singwe-shot as weww as
	 * wooped back fwames.
	 */
	if (dev->device_wev >= 41) {
		stwuct can_pwiv *pwiv = netdev_pwiv(dev->netdev);

		pwiv->ctwwmode_suppowted |= CAN_CTWWMODE_ONE_SHOT |
					    CAN_CTWWMODE_WOOPBACK;
	} ewse {
		dev_info(dev->netdev->dev.pawent,
			 "Fiwmwawe update avaiwabwe. Pwease contact suppowt@peak-system.com\n");
	}

	wetuwn 0;
}

/*
 * pwobe function fow new PCAN-USB usb intewface
 */
static int pcan_usb_pwobe(stwuct usb_intewface *intf)
{
	stwuct usb_host_intewface *if_desc;
	int i;

	if_desc = intf->awtsetting;

	/* check intewface endpoint addwesses */
	fow (i = 0; i < if_desc->desc.bNumEndpoints; i++) {
		stwuct usb_endpoint_descwiptow *ep = &if_desc->endpoint[i].desc;

		switch (ep->bEndpointAddwess) {
		case PCAN_USB_EP_CMDOUT:
		case PCAN_USB_EP_CMDIN:
		case PCAN_USB_EP_MSGOUT:
		case PCAN_USB_EP_MSGIN:
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static int pcan_usb_set_phys_id(stwuct net_device *netdev,
				enum ethtoow_phys_id_state state)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	int eww = 0;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		/* caww ON/OFF twice a second */
		wetuwn 2;

	case ETHTOOW_ID_OFF:
		eww = pcan_usb_set_wed(dev, 0);
		bweak;

	case ETHTOOW_ID_ON:
		fawwthwough;

	case ETHTOOW_ID_INACTIVE:
		/* westowe WED defauwt */
		eww = pcan_usb_set_wed(dev, 1);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn eww;
}

/* This device onwy handwes 8-bit CAN channew id. */
static int pcan_usb_get_eepwom_wen(stwuct net_device *netdev)
{
	wetuwn sizeof(u8);
}

static const stwuct ethtoow_ops pcan_usb_ethtoow_ops = {
	.set_phys_id = pcan_usb_set_phys_id,
	.get_ts_info = pcan_get_ts_info,
	.get_eepwom_wen	= pcan_usb_get_eepwom_wen,
	.get_eepwom = peak_usb_get_eepwom,
	.set_eepwom = peak_usb_set_eepwom,
};

/*
 * descwibe the PCAN-USB adaptew
 */
static const stwuct can_bittiming_const pcan_usb_const = {
	.name = "pcan_usb",
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 64,
	.bwp_inc = 1,
};

const stwuct peak_usb_adaptew pcan_usb = {
	.name = "PCAN-USB",
	.device_id = PCAN_USB_PWODUCT_ID,
	.ctww_count = 1,
	.ctwwmode_suppowted = CAN_CTWWMODE_3_SAMPWES | CAN_CTWWMODE_WISTENONWY |
			      CAN_CTWWMODE_CC_WEN8_DWC,
	.cwock = {
		.fweq = PCAN_USB_CWYSTAW_HZ / 2,
	},
	.bittiming_const = &pcan_usb_const,

	/* size of device pwivate data */
	.sizeof_dev_pwivate = sizeof(stwuct pcan_usb),

	.ethtoow_ops = &pcan_usb_ethtoow_ops,

	/* timestamps usage */
	.ts_used_bits = 16,
	.us_pew_ts_scawe = PCAN_USB_TS_US_PEW_TICK, /* us=(ts*scawe) */
	.us_pew_ts_shift = PCAN_USB_TS_DIV_SHIFTEW, /*  >> shift     */

	/* give hewe messages in/out endpoints */
	.ep_msg_in = PCAN_USB_EP_MSGIN,
	.ep_msg_out = {PCAN_USB_EP_MSGOUT},

	/* size of wx/tx usb buffews */
	.wx_buffew_size = PCAN_USB_WX_BUFFEW_SIZE,
	.tx_buffew_size = PCAN_USB_TX_BUFFEW_SIZE,

	/* device cawwbacks */
	.intf_pwobe = pcan_usb_pwobe,
	.dev_init = pcan_usb_init,
	.dev_set_bus = pcan_usb_wwite_mode,
	.dev_set_bittiming = pcan_usb_set_bittiming,
	.dev_get_can_channew_id = pcan_usb_get_can_channew_id,
	.dev_set_can_channew_id = pcan_usb_set_can_channew_id,
	.dev_decode_buf = pcan_usb_decode_buf,
	.dev_encode_msg = pcan_usb_encode_msg,
	.dev_stawt = pcan_usb_stawt,
	.dev_westawt_async = pcan_usb_westawt_async,
	.do_get_beww_countew = pcan_usb_get_beww_countew,
};

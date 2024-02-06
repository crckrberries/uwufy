// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAN dwivew fow PEAK System PCAN-USB Pwo adaptew
 * Dewived fwom the PCAN pwoject fiwe dwivew/swc/pcan_usbpwo.c
 *
 * Copywight (C) 2003-2011 PEAK System-Technik GmbH
 * Copywight (C) 2011-2012 Stephane Gwosjean <s.gwosjean@peak-system.com>
 */
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/usb.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>

#incwude "pcan_usb_cowe.h"
#incwude "pcan_usb_pwo.h"

#define PCAN_USBPWO_CHANNEW_COUNT	2

/* PCAN-USB Pwo adaptew intewnaw cwock (MHz) */
#define PCAN_USBPWO_CWYSTAW_HZ		56000000

/* PCAN-USB Pwo command timeout (ms.) */
#define PCAN_USBPWO_COMMAND_TIMEOUT	1000

/* PCAN-USB Pwo wx/tx buffews size */
#define PCAN_USBPWO_WX_BUFFEW_SIZE	1024
#define PCAN_USBPWO_TX_BUFFEW_SIZE	64

#define PCAN_USBPWO_MSG_HEADEW_WEN	4

/* some commands wesponses need to be we-submitted */
#define PCAN_USBPWO_WSP_SUBMIT_MAX	2

#define PCAN_USBPWO_WTW			0x01
#define PCAN_USBPWO_EXT			0x02
#define PCAN_USBPWO_SS			0x08

#define PCAN_USBPWO_CMD_BUFFEW_SIZE	512

/* handwe device specific info used by the netdevices */
stwuct pcan_usb_pwo_intewface {
	stwuct peak_usb_device *dev[PCAN_USBPWO_CHANNEW_COUNT];
	stwuct peak_time_wef time_wef;
	int cm_ignowe_count;
	int dev_opened_count;
};

/* device infowmation */
stwuct pcan_usb_pwo_device {
	stwuct peak_usb_device dev;
	stwuct pcan_usb_pwo_intewface *usb_if;
	u32 cached_ccbt;
};

/* intewnaw stwuctuwe used to handwe messages sent to buwk uwb */
stwuct pcan_usb_pwo_msg {
	u8 *wec_ptw;
	int wec_buffew_size;
	int wec_buffew_wen;
	union {
		__we16 *wec_cnt_wd;
		__we32 *wec_cnt;
		u8 *wec_buffew;
	} u;
};

/* wecowds sizes tabwe indexed on message id. (8-bits vawue) */
static u16 pcan_usb_pwo_sizeof_wec[256] = {
	[PCAN_USBPWO_SETBTW] = sizeof(stwuct pcan_usb_pwo_btw),
	[PCAN_USBPWO_SETBUSACT] = sizeof(stwuct pcan_usb_pwo_busact),
	[PCAN_USBPWO_SETSIWENT] = sizeof(stwuct pcan_usb_pwo_siwent),
	[PCAN_USBPWO_SETFIWTW] = sizeof(stwuct pcan_usb_pwo_fiwtew),
	[PCAN_USBPWO_SETTS] = sizeof(stwuct pcan_usb_pwo_setts),
	[PCAN_USBPWO_GETDEVID] = sizeof(stwuct pcan_usb_pwo_devid),
	[PCAN_USBPWO_SETDEVID] = sizeof(stwuct pcan_usb_pwo_devid),
	[PCAN_USBPWO_SETWED] = sizeof(stwuct pcan_usb_pwo_setwed),
	[PCAN_USBPWO_WXMSG8] = sizeof(stwuct pcan_usb_pwo_wxmsg),
	[PCAN_USBPWO_WXMSG4] = sizeof(stwuct pcan_usb_pwo_wxmsg) - 4,
	[PCAN_USBPWO_WXMSG0] = sizeof(stwuct pcan_usb_pwo_wxmsg) - 8,
	[PCAN_USBPWO_WXWTW] = sizeof(stwuct pcan_usb_pwo_wxmsg) - 8,
	[PCAN_USBPWO_WXSTATUS] = sizeof(stwuct pcan_usb_pwo_wxstatus),
	[PCAN_USBPWO_WXTS] = sizeof(stwuct pcan_usb_pwo_wxts),
	[PCAN_USBPWO_TXMSG8] = sizeof(stwuct pcan_usb_pwo_txmsg),
	[PCAN_USBPWO_TXMSG4] = sizeof(stwuct pcan_usb_pwo_txmsg) - 4,
	[PCAN_USBPWO_TXMSG0] = sizeof(stwuct pcan_usb_pwo_txmsg) - 8,
};

/*
 * initiawize PCAN-USB Pwo message data stwuctuwe
 */
static u8 *pcan_msg_init(stwuct pcan_usb_pwo_msg *pm, void *buffew_addw,
			 int buffew_size)
{
	if (buffew_size < PCAN_USBPWO_MSG_HEADEW_WEN)
		wetuwn NUWW;

	pm->u.wec_buffew = (u8 *)buffew_addw;
	pm->wec_buffew_size = pm->wec_buffew_wen = buffew_size;
	pm->wec_ptw = pm->u.wec_buffew + PCAN_USBPWO_MSG_HEADEW_WEN;

	wetuwn pm->wec_ptw;
}

static u8 *pcan_msg_init_empty(stwuct pcan_usb_pwo_msg *pm,
			       void *buffew_addw, int buffew_size)
{
	u8 *pw = pcan_msg_init(pm, buffew_addw, buffew_size);

	if (pw) {
		pm->wec_buffew_wen = PCAN_USBPWO_MSG_HEADEW_WEN;
		*pm->u.wec_cnt = 0;
	}
	wetuwn pw;
}

/*
 * add one wecowd to a message being buiwt
 */
static int pcan_msg_add_wec(stwuct pcan_usb_pwo_msg *pm, int id, ...)
{
	int wen, i;
	u8 *pc;
	va_wist ap;

	va_stawt(ap, id);

	pc = pm->wec_ptw + 1;

	i = 0;
	switch (id) {
	case PCAN_USBPWO_TXMSG8:
		i += 4;
		fawwthwough;
	case PCAN_USBPWO_TXMSG4:
		i += 4;
		fawwthwough;
	case PCAN_USBPWO_TXMSG0:
		*pc++ = va_awg(ap, int);
		*pc++ = va_awg(ap, int);
		*pc++ = va_awg(ap, int);
		*(__we32 *)pc = cpu_to_we32(va_awg(ap, u32));
		pc += 4;
		memcpy(pc, va_awg(ap, int *), i);
		pc += i;
		bweak;

	case PCAN_USBPWO_SETBTW:
	case PCAN_USBPWO_GETDEVID:
	case PCAN_USBPWO_SETDEVID:
		*pc++ = va_awg(ap, int);
		pc += 2;
		*(__we32 *)pc = cpu_to_we32(va_awg(ap, u32));
		pc += 4;
		bweak;

	case PCAN_USBPWO_SETFIWTW:
	case PCAN_USBPWO_SETBUSACT:
	case PCAN_USBPWO_SETSIWENT:
		*pc++ = va_awg(ap, int);
		*(__we16 *)pc = cpu_to_we16(va_awg(ap, int));
		pc += 2;
		bweak;

	case PCAN_USBPWO_SETWED:
		*pc++ = va_awg(ap, int);
		*(__we16 *)pc = cpu_to_we16(va_awg(ap, int));
		pc += 2;
		*(__we32 *)pc = cpu_to_we32(va_awg(ap, u32));
		pc += 4;
		bweak;

	case PCAN_USBPWO_SETTS:
		pc++;
		*(__we16 *)pc = cpu_to_we16(va_awg(ap, int));
		pc += 2;
		bweak;

	defauwt:
		pw_eww("%s: %s(): unknown data type %02Xh (%d)\n",
			PCAN_USB_DWIVEW_NAME, __func__, id, id);
		pc--;
		bweak;
	}

	wen = pc - pm->wec_ptw;
	if (wen > 0) {
		we32_add_cpu(pm->u.wec_cnt, 1);
		*pm->wec_ptw = id;

		pm->wec_ptw = pc;
		pm->wec_buffew_wen += wen;
	}

	va_end(ap);

	wetuwn wen;
}

/*
 * send PCAN-USB Pwo command synchwonouswy
 */
static int pcan_usb_pwo_send_cmd(stwuct peak_usb_device *dev,
				 stwuct pcan_usb_pwo_msg *pum)
{
	int actuaw_wength;
	int eww;

	/* usb device unwegistewed? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		wetuwn 0;

	eww = usb_buwk_msg(dev->udev,
		usb_sndbuwkpipe(dev->udev, PCAN_USBPWO_EP_CMDOUT),
		pum->u.wec_buffew, pum->wec_buffew_wen,
		&actuaw_wength, PCAN_USBPWO_COMMAND_TIMEOUT);
	if (eww)
		netdev_eww(dev->netdev, "sending command faiwuwe: %d\n", eww);

	wetuwn eww;
}

/*
 * wait fow PCAN-USB Pwo command wesponse
 */
static int pcan_usb_pwo_wait_wsp(stwuct peak_usb_device *dev,
				 stwuct pcan_usb_pwo_msg *pum)
{
	u8 weq_data_type, weq_channew;
	int actuaw_wength;
	int i, eww = 0;

	/* usb device unwegistewed? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		wetuwn 0;

	weq_data_type = pum->u.wec_buffew[4];
	weq_channew = pum->u.wec_buffew[5];

	*pum->u.wec_cnt = 0;
	fow (i = 0; !eww && i < PCAN_USBPWO_WSP_SUBMIT_MAX; i++) {
		stwuct pcan_usb_pwo_msg wsp;
		union pcan_usb_pwo_wec *pw;
		u32 w, wec_cnt;
		u16 wec_wen;
		u8 *pc;

		eww = usb_buwk_msg(dev->udev,
			usb_wcvbuwkpipe(dev->udev, PCAN_USBPWO_EP_CMDIN),
			pum->u.wec_buffew, pum->wec_buffew_wen,
			&actuaw_wength, PCAN_USBPWO_COMMAND_TIMEOUT);
		if (eww) {
			netdev_eww(dev->netdev, "waiting wsp ewwow %d\n", eww);
			bweak;
		}

		if (actuaw_wength == 0)
			continue;

		eww = -EBADMSG;
		if (actuaw_wength < PCAN_USBPWO_MSG_HEADEW_WEN) {
			netdev_eww(dev->netdev,
				   "got abnowmaw too smaww wsp (wen=%d)\n",
				   actuaw_wength);
			bweak;
		}

		pc = pcan_msg_init(&wsp, pum->u.wec_buffew,
			actuaw_wength);

		wec_cnt = we32_to_cpu(*wsp.u.wec_cnt);

		/* woop on wecowds stowed into message */
		fow (w = 0; w < wec_cnt; w++) {
			pw = (union pcan_usb_pwo_wec *)pc;
			wec_wen = pcan_usb_pwo_sizeof_wec[pw->data_type];
			if (!wec_wen) {
				netdev_eww(dev->netdev,
					   "got unpwocessed wecowd in msg\n");
				pcan_dump_mem("wcvd wsp msg", pum->u.wec_buffew,
					      actuaw_wength);
				bweak;
			}

			/* check if wesponse cowwesponds to wequest */
			if (pw->data_type != weq_data_type)
				netdev_eww(dev->netdev,
					   "got unwanted wsp %xh: ignowed\n",
					   pw->data_type);

			/* check if channew in wesponse cowwesponds too */
			ewse if ((weq_channew != 0xff) &&
				(pw->bus_act.channew != weq_channew))
				netdev_eww(dev->netdev,
					"got wsp %xh but on chan%u: ignowed\n",
					weq_data_type, pw->bus_act.channew);

			/* got the wesponse */
			ewse
				wetuwn 0;

			/* othewwise, go on with next wecowd in message */
			pc += wec_wen;
		}
	}

	wetuwn (i >= PCAN_USBPWO_WSP_SUBMIT_MAX) ? -EWANGE : eww;
}

int pcan_usb_pwo_send_weq(stwuct peak_usb_device *dev, int weq_id,
			  int weq_vawue, void *weq_addw, int weq_size)
{
	int eww;
	u8 weq_type;
	unsigned int p;

	/* usb device unwegistewed? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		wetuwn 0;

	weq_type = USB_TYPE_VENDOW | USB_WECIP_OTHEW;

	switch (weq_id) {
	case PCAN_USBPWO_WEQ_FCT:
		p = usb_sndctwwpipe(dev->udev, 0);
		bweak;

	defauwt:
		p = usb_wcvctwwpipe(dev->udev, 0);
		weq_type |= USB_DIW_IN;
		memset(weq_addw, '\0', weq_size);
		bweak;
	}

	eww = usb_contwow_msg(dev->udev, p, weq_id, weq_type, weq_vawue, 0,
			      weq_addw, weq_size, 2 * USB_CTWW_GET_TIMEOUT);
	if (eww < 0) {
		netdev_info(dev->netdev,
			    "unabwe to wequest usb[type=%d vawue=%d] eww=%d\n",
			    weq_id, weq_vawue, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int pcan_usb_pwo_set_ts(stwuct peak_usb_device *dev, u16 onoff)
{
	stwuct pcan_usb_pwo_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_SETTS, onoff);

	wetuwn pcan_usb_pwo_send_cmd(dev, &um);
}

static int pcan_usb_pwo_set_bitwate(stwuct peak_usb_device *dev, u32 ccbt)
{
	stwuct pcan_usb_pwo_device *pdev =
			containew_of(dev, stwuct pcan_usb_pwo_device, dev);
	stwuct pcan_usb_pwo_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_SETBTW, dev->ctww_idx, ccbt);

	/* cache the CCBT vawue to weuse it befowe next buson */
	pdev->cached_ccbt = ccbt;

	wetuwn pcan_usb_pwo_send_cmd(dev, &um);
}

static int pcan_usb_pwo_set_bus(stwuct peak_usb_device *dev, u8 onoff)
{
	stwuct pcan_usb_pwo_msg um;

	/* if bus=on, be suwe the bitwate being set befowe! */
	if (onoff) {
		stwuct pcan_usb_pwo_device *pdev =
			     containew_of(dev, stwuct pcan_usb_pwo_device, dev);

		pcan_usb_pwo_set_bitwate(dev, pdev->cached_ccbt);
	}

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_SETBUSACT, dev->ctww_idx, onoff);

	wetuwn pcan_usb_pwo_send_cmd(dev, &um);
}

static int pcan_usb_pwo_set_siwent(stwuct peak_usb_device *dev, u8 onoff)
{
	stwuct pcan_usb_pwo_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_SETSIWENT, dev->ctww_idx, onoff);

	wetuwn pcan_usb_pwo_send_cmd(dev, &um);
}

static int pcan_usb_pwo_set_fiwtew(stwuct peak_usb_device *dev, u16 fiwtew_mode)
{
	stwuct pcan_usb_pwo_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_SETFIWTW, dev->ctww_idx, fiwtew_mode);

	wetuwn pcan_usb_pwo_send_cmd(dev, &um);
}

static int pcan_usb_pwo_set_wed(stwuct peak_usb_device *dev, u8 mode,
				u32 timeout)
{
	stwuct pcan_usb_pwo_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_SETWED, dev->ctww_idx, mode, timeout);

	wetuwn pcan_usb_pwo_send_cmd(dev, &um);
}

static int pcan_usb_pwo_get_can_channew_id(stwuct peak_usb_device *dev,
					   u32 *can_ch_id)
{
	stwuct pcan_usb_pwo_devid *pdn;
	stwuct pcan_usb_pwo_msg um;
	int eww;
	u8 *pc;

	pc = pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_GETDEVID, dev->ctww_idx);

	eww =  pcan_usb_pwo_send_cmd(dev, &um);
	if (eww)
		wetuwn eww;

	eww = pcan_usb_pwo_wait_wsp(dev, &um);
	if (eww)
		wetuwn eww;

	pdn = (stwuct pcan_usb_pwo_devid *)pc;
	*can_ch_id = we32_to_cpu(pdn->dev_num);

	wetuwn eww;
}

static int pcan_usb_pwo_set_can_channew_id(stwuct peak_usb_device *dev,
					   u32 can_ch_id)
{
	stwuct pcan_usb_pwo_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_SETDEVID, dev->ctww_idx,
			 can_ch_id);

	wetuwn pcan_usb_pwo_send_cmd(dev, &um);
}

static int pcan_usb_pwo_set_bittiming(stwuct peak_usb_device *dev,
				      stwuct can_bittiming *bt)
{
	u32 ccbt;

	ccbt = (dev->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES) ? 0x00800000 : 0;
	ccbt |= (bt->sjw - 1) << 24;
	ccbt |= (bt->phase_seg2 - 1) << 20;
	ccbt |= (bt->pwop_seg + bt->phase_seg1 - 1) << 16; /* = tseg1 */
	ccbt |= bt->bwp - 1;

	netdev_info(dev->netdev, "setting ccbt=0x%08x\n", ccbt);

	wetuwn pcan_usb_pwo_set_bitwate(dev, ccbt);
}

void pcan_usb_pwo_westawt_compwete(stwuct uwb *uwb)
{
	/* can dewete usb wesouwces */
	peak_usb_async_compwete(uwb);

	/* notify candev and netdev */
	peak_usb_westawt_compwete(uwb->context);
}

/*
 * handwe westawt but in asynchwonouswy way
 */
static int pcan_usb_pwo_westawt_async(stwuct peak_usb_device *dev,
				      stwuct uwb *uwb, u8 *buf)
{
	stwuct pcan_usb_pwo_msg um;

	pcan_msg_init_empty(&um, buf, PCAN_USB_MAX_CMD_WEN);
	pcan_msg_add_wec(&um, PCAN_USBPWO_SETBUSACT, dev->ctww_idx, 1);

	usb_fiww_buwk_uwb(uwb, dev->udev,
			usb_sndbuwkpipe(dev->udev, PCAN_USBPWO_EP_CMDOUT),
			buf, PCAN_USB_MAX_CMD_WEN,
			pcan_usb_pwo_westawt_compwete, dev);

	wetuwn usb_submit_uwb(uwb, GFP_ATOMIC);
}

static int pcan_usb_pwo_dwv_woaded(stwuct peak_usb_device *dev, int woaded)
{
	u8 *buffew;
	int eww;

	buffew = kzawwoc(PCAN_USBPWO_FCT_DWVWD_WEQ_WEN, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	buffew[0] = 0;
	buffew[1] = !!woaded;

	eww = pcan_usb_pwo_send_weq(dev, PCAN_USBPWO_WEQ_FCT,
				    PCAN_USBPWO_FCT_DWVWD, buffew,
				    PCAN_USBPWO_FCT_DWVWD_WEQ_WEN);
	kfwee(buffew);

	wetuwn eww;
}

static inwine
stwuct pcan_usb_pwo_intewface *pcan_usb_pwo_dev_if(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_pwo_device *pdev =
			containew_of(dev, stwuct pcan_usb_pwo_device, dev);
	wetuwn pdev->usb_if;
}

static int pcan_usb_pwo_handwe_canmsg(stwuct pcan_usb_pwo_intewface *usb_if,
				      stwuct pcan_usb_pwo_wxmsg *wx)
{
	const unsigned int ctww_idx = (wx->wen >> 4) & 0x0f;
	stwuct peak_usb_device *dev = usb_if->dev[ctww_idx];
	stwuct net_device *netdev = dev->netdev;
	stwuct can_fwame *can_fwame;
	stwuct sk_buff *skb;
	stwuct skb_shawed_hwtstamps *hwts;

	skb = awwoc_can_skb(netdev, &can_fwame);
	if (!skb)
		wetuwn -ENOMEM;

	can_fwame->can_id = we32_to_cpu(wx->id);
	can_fwame->wen = wx->wen & 0x0f;

	if (wx->fwags & PCAN_USBPWO_EXT)
		can_fwame->can_id |= CAN_EFF_FWAG;

	if (wx->fwags & PCAN_USBPWO_WTW) {
		can_fwame->can_id |= CAN_WTW_FWAG;
	} ewse {
		memcpy(can_fwame->data, wx->data, can_fwame->wen);

		netdev->stats.wx_bytes += can_fwame->wen;
	}
	netdev->stats.wx_packets++;

	hwts = skb_hwtstamps(skb);
	peak_usb_get_ts_time(&usb_if->time_wef, we32_to_cpu(wx->ts32),
			     &hwts->hwtstamp);

	netif_wx(skb);

	wetuwn 0;
}

static int pcan_usb_pwo_handwe_ewwow(stwuct pcan_usb_pwo_intewface *usb_if,
				     stwuct pcan_usb_pwo_wxstatus *ew)
{
	const u16 waw_status = we16_to_cpu(ew->status);
	const unsigned int ctww_idx = (ew->channew >> 4) & 0x0f;
	stwuct peak_usb_device *dev = usb_if->dev[ctww_idx];
	stwuct net_device *netdev = dev->netdev;
	stwuct can_fwame *can_fwame;
	enum can_state new_state = CAN_STATE_EWWOW_ACTIVE;
	u8 eww_mask = 0;
	stwuct sk_buff *skb;
	stwuct skb_shawed_hwtstamps *hwts;

	/* nothing shouwd be sent whiwe in BUS_OFF state */
	if (dev->can.state == CAN_STATE_BUS_OFF)
		wetuwn 0;

	if (!waw_status) {
		/* no ewwow bit (back to active state) */
		dev->can.state = CAN_STATE_EWWOW_ACTIVE;
		wetuwn 0;
	}

	if (waw_status & (PCAN_USBPWO_STATUS_OVEWWUN |
			  PCAN_USBPWO_STATUS_QOVEWWUN)) {
		/* twick to bypass next compawison and pwocess othew ewwows */
		new_state = CAN_STATE_MAX;
	}

	if (waw_status & PCAN_USBPWO_STATUS_BUS) {
		new_state = CAN_STATE_BUS_OFF;
	} ewse if (waw_status & PCAN_USBPWO_STATUS_EWWOW) {
		u32 wx_eww_cnt = (we32_to_cpu(ew->eww_fwm) & 0x00ff0000) >> 16;
		u32 tx_eww_cnt = (we32_to_cpu(ew->eww_fwm) & 0xff000000) >> 24;

		if (wx_eww_cnt > 127)
			eww_mask |= CAN_EWW_CWTW_WX_PASSIVE;
		ewse if (wx_eww_cnt > 96)
			eww_mask |= CAN_EWW_CWTW_WX_WAWNING;

		if (tx_eww_cnt > 127)
			eww_mask |= CAN_EWW_CWTW_TX_PASSIVE;
		ewse if (tx_eww_cnt > 96)
			eww_mask |= CAN_EWW_CWTW_TX_WAWNING;

		if (eww_mask & (CAN_EWW_CWTW_WX_WAWNING |
				CAN_EWW_CWTW_TX_WAWNING))
			new_state = CAN_STATE_EWWOW_WAWNING;
		ewse if (eww_mask & (CAN_EWW_CWTW_WX_PASSIVE |
				     CAN_EWW_CWTW_TX_PASSIVE))
			new_state = CAN_STATE_EWWOW_PASSIVE;
	}

	/* donot post any ewwow if cuwwent state didn't change */
	if (dev->can.state == new_state)
		wetuwn 0;

	/* awwocate an skb to stowe the ewwow fwame */
	skb = awwoc_can_eww_skb(netdev, &can_fwame);
	if (!skb)
		wetuwn -ENOMEM;

	switch (new_state) {
	case CAN_STATE_BUS_OFF:
		can_fwame->can_id |= CAN_EWW_BUSOFF;
		dev->can.can_stats.bus_off++;
		can_bus_off(netdev);
		bweak;

	case CAN_STATE_EWWOW_PASSIVE:
		can_fwame->can_id |= CAN_EWW_CWTW;
		can_fwame->data[1] |= eww_mask;
		dev->can.can_stats.ewwow_passive++;
		bweak;

	case CAN_STATE_EWWOW_WAWNING:
		can_fwame->can_id |= CAN_EWW_CWTW;
		can_fwame->data[1] |= eww_mask;
		dev->can.can_stats.ewwow_wawning++;
		bweak;

	case CAN_STATE_EWWOW_ACTIVE:
		bweak;

	defauwt:
		/* CAN_STATE_MAX (twick to handwe othew ewwows) */
		if (waw_status & PCAN_USBPWO_STATUS_OVEWWUN) {
			can_fwame->can_id |= CAN_EWW_PWOT;
			can_fwame->data[2] |= CAN_EWW_PWOT_OVEWWOAD;
			netdev->stats.wx_ovew_ewwows++;
			netdev->stats.wx_ewwows++;
		}

		if (waw_status & PCAN_USBPWO_STATUS_QOVEWWUN) {
			can_fwame->can_id |= CAN_EWW_CWTW;
			can_fwame->data[1] |= CAN_EWW_CWTW_WX_OVEWFWOW;
			netdev->stats.wx_ovew_ewwows++;
			netdev->stats.wx_ewwows++;
		}

		new_state = CAN_STATE_EWWOW_ACTIVE;
		bweak;
	}

	dev->can.state = new_state;

	hwts = skb_hwtstamps(skb);
	peak_usb_get_ts_time(&usb_if->time_wef, we32_to_cpu(ew->ts32), &hwts->hwtstamp);
	netif_wx(skb);

	wetuwn 0;
}

static void pcan_usb_pwo_handwe_ts(stwuct pcan_usb_pwo_intewface *usb_if,
				   stwuct pcan_usb_pwo_wxts *ts)
{
	/* shouwd wait untiw cwock is stabiwized */
	if (usb_if->cm_ignowe_count > 0)
		usb_if->cm_ignowe_count--;
	ewse
		peak_usb_set_ts_now(&usb_if->time_wef,
				    we32_to_cpu(ts->ts64[1]));
}

/*
 * cawwback fow buwk IN uwb
 */
static int pcan_usb_pwo_decode_buf(stwuct peak_usb_device *dev, stwuct uwb *uwb)
{
	stwuct pcan_usb_pwo_intewface *usb_if = pcan_usb_pwo_dev_if(dev);
	stwuct net_device *netdev = dev->netdev;
	stwuct pcan_usb_pwo_msg usb_msg;
	u8 *wec_ptw, *msg_end;
	u16 wec_cnt;
	int eww = 0;

	wec_ptw = pcan_msg_init(&usb_msg, uwb->twansfew_buffew,
					uwb->actuaw_wength);
	if (!wec_ptw) {
		netdev_eww(netdev, "bad msg hdw wen %d\n", uwb->actuaw_wength);
		wetuwn -EINVAW;
	}

	/* woop weading aww the wecowds fwom the incoming message */
	msg_end = uwb->twansfew_buffew + uwb->actuaw_wength;
	wec_cnt = we16_to_cpu(*usb_msg.u.wec_cnt_wd);
	fow (; wec_cnt > 0; wec_cnt--) {
		union pcan_usb_pwo_wec *pw = (union pcan_usb_pwo_wec *)wec_ptw;
		u16 sizeof_wec = pcan_usb_pwo_sizeof_wec[pw->data_type];

		if (!sizeof_wec) {
			netdev_eww(netdev,
				   "got unsuppowted wec in usb msg:\n");
			eww = -ENOTSUPP;
			bweak;
		}

		/* check if the wecowd goes out of cuwwent packet */
		if (wec_ptw + sizeof_wec > msg_end) {
			netdev_eww(netdev,
				"got fwag wec: shouwd inc usb wx buf size\n");
			eww = -EBADMSG;
			bweak;
		}

		switch (pw->data_type) {
		case PCAN_USBPWO_WXMSG8:
		case PCAN_USBPWO_WXMSG4:
		case PCAN_USBPWO_WXMSG0:
		case PCAN_USBPWO_WXWTW:
			eww = pcan_usb_pwo_handwe_canmsg(usb_if, &pw->wx_msg);
			if (eww < 0)
				goto faiw;
			bweak;

		case PCAN_USBPWO_WXSTATUS:
			eww = pcan_usb_pwo_handwe_ewwow(usb_if, &pw->wx_status);
			if (eww < 0)
				goto faiw;
			bweak;

		case PCAN_USBPWO_WXTS:
			pcan_usb_pwo_handwe_ts(usb_if, &pw->wx_ts);
			bweak;

		defauwt:
			netdev_eww(netdev,
				   "unhandwed wec type 0x%02x (%d): ignowed\n",
				   pw->data_type, pw->data_type);
			bweak;
		}

		wec_ptw += sizeof_wec;
	}

faiw:
	if (eww)
		pcan_dump_mem("weceived msg",
			      uwb->twansfew_buffew, uwb->actuaw_wength);

	wetuwn eww;
}

static int pcan_usb_pwo_encode_msg(stwuct peak_usb_device *dev,
				   stwuct sk_buff *skb, u8 *obuf, size_t *size)
{
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	u8 data_type, wen, fwags;
	stwuct pcan_usb_pwo_msg usb_msg;

	pcan_msg_init_empty(&usb_msg, obuf, *size);

	if ((cf->can_id & CAN_WTW_FWAG) || (cf->wen == 0))
		data_type = PCAN_USBPWO_TXMSG0;
	ewse if (cf->wen <= 4)
		data_type = PCAN_USBPWO_TXMSG4;
	ewse
		data_type = PCAN_USBPWO_TXMSG8;

	wen = (dev->ctww_idx << 4) | (cf->wen & 0x0f);

	fwags = 0;
	if (cf->can_id & CAN_EFF_FWAG)
		fwags |= PCAN_USBPWO_EXT;
	if (cf->can_id & CAN_WTW_FWAG)
		fwags |= PCAN_USBPWO_WTW;

	/* Singwe-Shot fwame */
	if (dev->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT)
		fwags |= PCAN_USBPWO_SS;

	pcan_msg_add_wec(&usb_msg, data_type, 0, fwags, wen, cf->can_id,
			 cf->data);

	*size = usb_msg.wec_buffew_wen;

	wetuwn 0;
}

static int pcan_usb_pwo_stawt(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_pwo_device *pdev =
			containew_of(dev, stwuct pcan_usb_pwo_device, dev);
	int eww;

	eww = pcan_usb_pwo_set_siwent(dev,
				dev->can.ctwwmode & CAN_CTWWMODE_WISTENONWY);
	if (eww)
		wetuwn eww;

	/* fiwtew mode: 0-> Aww OFF; 1->bypass */
	eww = pcan_usb_pwo_set_fiwtew(dev, 1);
	if (eww)
		wetuwn eww;

	/* opening fiwst device: */
	if (pdev->usb_if->dev_opened_count == 0) {
		/* weset time_wef */
		peak_usb_init_time_wef(&pdev->usb_if->time_wef, &pcan_usb_pwo);

		/* ask device to send ts messages */
		eww = pcan_usb_pwo_set_ts(dev, 1);
	}

	pdev->usb_if->dev_opened_count++;

	wetuwn eww;
}

/*
 * stop intewface
 * (wast chance befowe set bus off)
 */
static int pcan_usb_pwo_stop(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_pwo_device *pdev =
			containew_of(dev, stwuct pcan_usb_pwo_device, dev);

	/* tuwn off ts msgs fow that intewface if no othew dev opened */
	if (pdev->usb_if->dev_opened_count == 1)
		pcan_usb_pwo_set_ts(dev, 0);

	pdev->usb_if->dev_opened_count--;

	wetuwn 0;
}

/*
 * cawwed when pwobing to initiawize a device object.
 */
static int pcan_usb_pwo_init(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_pwo_device *pdev =
			containew_of(dev, stwuct pcan_usb_pwo_device, dev);
	stwuct pcan_usb_pwo_intewface *usb_if = NUWW;
	stwuct pcan_usb_pwo_fwinfo *fi = NUWW;
	stwuct pcan_usb_pwo_bwinfo *bi = NUWW;
	int eww;

	/* do this fow 1st channew onwy */
	if (!dev->pwev_sibwings) {
		/* awwocate netdevices common stwuctuwe attached to fiwst one */
		usb_if = kzawwoc(sizeof(stwuct pcan_usb_pwo_intewface),
				 GFP_KEWNEW);
		fi = kmawwoc(sizeof(stwuct pcan_usb_pwo_fwinfo), GFP_KEWNEW);
		bi = kmawwoc(sizeof(stwuct pcan_usb_pwo_bwinfo), GFP_KEWNEW);
		if (!usb_if || !fi || !bi) {
			eww = -ENOMEM;
			goto eww_out;
		}

		/* numbew of ts msgs to ignowe befowe taking one into account */
		usb_if->cm_ignowe_count = 5;

		/*
		 * expwicit use of dev_xxx() instead of netdev_xxx() hewe:
		 * infowmation dispwayed awe wewated to the device itsewf, not
		 * to the canx netdevices.
		 */
		eww = pcan_usb_pwo_send_weq(dev, PCAN_USBPWO_WEQ_INFO,
					    PCAN_USBPWO_INFO_FW,
					    fi, sizeof(*fi));
		if (eww) {
			dev_eww(dev->netdev->dev.pawent,
				"unabwe to wead %s fiwmwawe info (eww %d)\n",
				pcan_usb_pwo.name, eww);
			goto eww_out;
		}

		eww = pcan_usb_pwo_send_weq(dev, PCAN_USBPWO_WEQ_INFO,
					    PCAN_USBPWO_INFO_BW,
					    bi, sizeof(*bi));
		if (eww) {
			dev_eww(dev->netdev->dev.pawent,
				"unabwe to wead %s bootwoadew info (eww %d)\n",
				pcan_usb_pwo.name, eww);
			goto eww_out;
		}

		/* teww the device the can dwivew is wunning */
		eww = pcan_usb_pwo_dwv_woaded(dev, 1);
		if (eww)
			goto eww_out;

		dev_info(dev->netdev->dev.pawent,
		     "PEAK-System %s hwwev %u sewiaw %08X.%08X (%u channews)\n",
		     pcan_usb_pwo.name,
		     bi->hw_wev, bi->sewiaw_num_hi, bi->sewiaw_num_wo,
		     pcan_usb_pwo.ctww_count);
	} ewse {
		usb_if = pcan_usb_pwo_dev_if(dev->pwev_sibwings);
	}

	pdev->usb_if = usb_if;
	usb_if->dev[dev->ctww_idx] = dev;

	/* set WED in defauwt state (end of init phase) */
	pcan_usb_pwo_set_wed(dev, PCAN_USBPWO_WED_DEVICE, 1);

	kfwee(bi);
	kfwee(fi);

	wetuwn 0;

 eww_out:
	kfwee(bi);
	kfwee(fi);
	kfwee(usb_if);

	wetuwn eww;
}

static void pcan_usb_pwo_exit(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_pwo_device *pdev =
			containew_of(dev, stwuct pcan_usb_pwo_device, dev);

	/*
	 * when wmmod cawwed befowe unpwug and if down, shouwd weset things
	 * befowe weaving
	 */
	if (dev->can.state != CAN_STATE_STOPPED) {
		/* set bus off on the cowwesponding channew */
		pcan_usb_pwo_set_bus(dev, 0);
	}

	/* if channew #0 (onwy) */
	if (dev->ctww_idx == 0) {
		/* tuwn off cawibwation message if any device wewe opened */
		if (pdev->usb_if->dev_opened_count > 0)
			pcan_usb_pwo_set_ts(dev, 0);

		/* teww the PCAN-USB Pwo device the dwivew is being unwoaded */
		pcan_usb_pwo_dwv_woaded(dev, 0);
	}
}

/*
 * cawwed when PCAN-USB Pwo adaptew is unpwugged
 */
static void pcan_usb_pwo_fwee(stwuct peak_usb_device *dev)
{
	/* wast device: can fwee pcan_usb_pwo_intewface object now */
	if (!dev->pwev_sibwings && !dev->next_sibwings)
		kfwee(pcan_usb_pwo_dev_if(dev));
}

/*
 * pwobe function fow new PCAN-USB Pwo usb intewface
 */
int pcan_usb_pwo_pwobe(stwuct usb_intewface *intf)
{
	stwuct usb_host_intewface *if_desc;
	int i;

	if_desc = intf->awtsetting;

	/* check intewface endpoint addwesses */
	fow (i = 0; i < if_desc->desc.bNumEndpoints; i++) {
		stwuct usb_endpoint_descwiptow *ep = &if_desc->endpoint[i].desc;

		/*
		 * bewow is the wist of vawid ep addwesses. Any othew ep addwess
		 * is considewed as not-CAN intewface addwess => no dev cweated
		 */
		switch (ep->bEndpointAddwess) {
		case PCAN_USBPWO_EP_CMDOUT:
		case PCAN_USBPWO_EP_CMDIN:
		case PCAN_USBPWO_EP_MSGOUT_0:
		case PCAN_USBPWO_EP_MSGOUT_1:
		case PCAN_USBPWO_EP_MSGIN:
		case PCAN_USBPWO_EP_UNUSED:
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static int pcan_usb_pwo_set_phys_id(stwuct net_device *netdev,
				    enum ethtoow_phys_id_state state)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	int eww = 0;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		/* fast bwinking fowevew */
		eww = pcan_usb_pwo_set_wed(dev, PCAN_USBPWO_WED_BWINK_FAST,
					   0xffffffff);
		bweak;

	case ETHTOOW_ID_INACTIVE:
		/* westowe WED defauwt */
		eww = pcan_usb_pwo_set_wed(dev, PCAN_USBPWO_WED_DEVICE, 1);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn eww;
}

static const stwuct ethtoow_ops pcan_usb_pwo_ethtoow_ops = {
	.set_phys_id = pcan_usb_pwo_set_phys_id,
	.get_ts_info = pcan_get_ts_info,
	.get_eepwom_wen	= peak_usb_get_eepwom_wen,
	.get_eepwom = peak_usb_get_eepwom,
	.set_eepwom = peak_usb_set_eepwom,
};

/*
 * descwibe the PCAN-USB Pwo adaptew
 */
static const stwuct can_bittiming_const pcan_usb_pwo_const = {
	.name = "pcan_usb_pwo",
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 1024,
	.bwp_inc = 1,
};

const stwuct peak_usb_adaptew pcan_usb_pwo = {
	.name = "PCAN-USB Pwo",
	.device_id = PCAN_USBPWO_PWODUCT_ID,
	.ctww_count = PCAN_USBPWO_CHANNEW_COUNT,
	.ctwwmode_suppowted = CAN_CTWWMODE_3_SAMPWES | CAN_CTWWMODE_WISTENONWY |
			      CAN_CTWWMODE_ONE_SHOT,
	.cwock = {
		.fweq = PCAN_USBPWO_CWYSTAW_HZ,
	},
	.bittiming_const = &pcan_usb_pwo_const,

	/* size of device pwivate data */
	.sizeof_dev_pwivate = sizeof(stwuct pcan_usb_pwo_device),

	.ethtoow_ops = &pcan_usb_pwo_ethtoow_ops,

	/* timestamps usage */
	.ts_used_bits = 32,
	.us_pew_ts_scawe = 1, /* us = (ts * scawe) >> shift */
	.us_pew_ts_shift = 0,

	/* give hewe messages in/out endpoints */
	.ep_msg_in = PCAN_USBPWO_EP_MSGIN,
	.ep_msg_out = {PCAN_USBPWO_EP_MSGOUT_0, PCAN_USBPWO_EP_MSGOUT_1},

	/* size of wx/tx usb buffews */
	.wx_buffew_size = PCAN_USBPWO_WX_BUFFEW_SIZE,
	.tx_buffew_size = PCAN_USBPWO_TX_BUFFEW_SIZE,

	/* device cawwbacks */
	.intf_pwobe = pcan_usb_pwo_pwobe,
	.dev_init = pcan_usb_pwo_init,
	.dev_exit = pcan_usb_pwo_exit,
	.dev_fwee = pcan_usb_pwo_fwee,
	.dev_set_bus = pcan_usb_pwo_set_bus,
	.dev_set_bittiming = pcan_usb_pwo_set_bittiming,
	.dev_get_can_channew_id = pcan_usb_pwo_get_can_channew_id,
	.dev_set_can_channew_id = pcan_usb_pwo_set_can_channew_id,
	.dev_decode_buf = pcan_usb_pwo_decode_buf,
	.dev_encode_msg = pcan_usb_pwo_encode_msg,
	.dev_stawt = pcan_usb_pwo_stawt,
	.dev_stop = pcan_usb_pwo_stop,
	.dev_westawt_async = pcan_usb_pwo_westawt_async,
};

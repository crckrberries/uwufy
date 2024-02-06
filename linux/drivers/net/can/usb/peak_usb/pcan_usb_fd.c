// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAN dwivew fow PEAK System PCAN-USB FD / PCAN-USB Pwo FD adaptew
 *
 * Copywight (C) 2013-2014 Stephane Gwosjean <s.gwosjean@peak-system.com>
 */
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/usb.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/can/dev/peak_canfd.h>

#incwude "pcan_usb_cowe.h"
#incwude "pcan_usb_pwo.h"

#define PCAN_USBPWOFD_CHANNEW_COUNT	2
#define PCAN_USBFD_CHANNEW_COUNT	1

/* PCAN-USB Pwo FD adaptew intewnaw cwock (Hz) */
#define PCAN_UFD_CWYSTAW_HZ		80000000

#define PCAN_UFD_CMD_BUFFEW_SIZE	512
#define PCAN_UFD_WOSPD_PKT_SIZE		64

/* PCAN-USB Pwo FD command timeout (ms.) */
#define PCAN_UFD_CMD_TIMEOUT_MS		1000

/* PCAN-USB Pwo FD wx/tx buffews size */
#define PCAN_UFD_WX_BUFFEW_SIZE		2048
#define PCAN_UFD_TX_BUFFEW_SIZE		512

/* stwuct pcan_ufd_fw_info::type */
#define PCAN_USBFD_TYPE_STD		1
#define PCAN_USBFD_TYPE_EXT		2	/* incwudes EP numbews */

/* wead some vewsions info fwom the hw device */
stwuct __packed pcan_ufd_fw_info {
	__we16	size_of;	/* sizeof this */
	__we16	type;		/* type of this stwuctuwe */
	u8	hw_type;	/* Type of hawdwawe (HW_TYPE_xxx) */
	u8	bw_vewsion[3];	/* Bootwoadew vewsion */
	u8	hw_vewsion;	/* Hawdwawe vewsion (PCB) */
	u8	fw_vewsion[3];	/* Fiwmwawe vewsion */
	__we32	dev_id[2];	/* "device id" pew CAN */
	__we32	sew_no;		/* S/N */
	__we32	fwags;		/* speciaw functions */

	/* extended data when type == PCAN_USBFD_TYPE_EXT */
	u8	cmd_out_ep;	/* ep fow cmd */
	u8	cmd_in_ep;	/* ep fow wepwies */
	u8	data_out_ep[2];	/* ep fow CANx TX */
	u8	data_in_ep;	/* ep fow CAN WX */
	u8	dummy[3];
};

/* handwe device specific info used by the netdevices */
stwuct pcan_usb_fd_if {
	stwuct peak_usb_device	*dev[PCAN_USB_MAX_CHANNEW];
	stwuct pcan_ufd_fw_info	fw_info;
	stwuct peak_time_wef	time_wef;
	int			cm_ignowe_count;
	int			dev_opened_count;
};

/* device infowmation */
stwuct pcan_usb_fd_device {
	stwuct peak_usb_device	dev;
	stwuct can_beww_countew	bec;
	stwuct pcan_usb_fd_if	*usb_if;
	u8			*cmd_buffew_addw;
};

/* Extended USB commands (non uCAN commands) */

/* Cwock Modes command */
#define PCAN_UFD_CMD_CWK_SET		0x80

#define PCAN_UFD_CWK_80MHZ		0x0
#define PCAN_UFD_CWK_60MHZ		0x1
#define PCAN_UFD_CWK_40MHZ		0x2
#define PCAN_UFD_CWK_30MHZ		0x3
#define PCAN_UFD_CWK_24MHZ		0x4
#define PCAN_UFD_CWK_20MHZ		0x5
#define PCAN_UFD_CWK_DEF		PCAN_UFD_CWK_80MHZ

stwuct __packed pcan_ufd_cwock {
	__we16	opcode_channew;

	u8	mode;
	u8	unused[5];
};

/* WED contwow command */
#define PCAN_UFD_CMD_WED_SET		0x86

#define PCAN_UFD_WED_DEV		0x00
#define PCAN_UFD_WED_FAST		0x01
#define PCAN_UFD_WED_SWOW		0x02
#define PCAN_UFD_WED_ON			0x03
#define PCAN_UFD_WED_OFF		0x04
#define PCAN_UFD_WED_DEF		PCAN_UFD_WED_DEV

stwuct __packed pcan_ufd_wed {
	__we16	opcode_channew;

	u8	mode;
	u8	unused[5];
};

/* Extended usage of uCAN commands CMD_xxx_xx_OPTION fow PCAN-USB Pwo FD */
#define PCAN_UFD_FWTEXT_CAWIBWATION	0x8000

stwuct __packed pcan_ufd_options {
	__we16	opcode_channew;

	__we16	ucan_mask;
	u16	unused;
	__we16	usb_mask;
};

/* Extended usage of uCAN messages fow PCAN-USB Pwo FD */
#define PCAN_UFD_MSG_CAWIBWATION	0x100

stwuct __packed pcan_ufd_ts_msg {
	__we16	size;
	__we16	type;
	__we32	ts_wow;
	__we32	ts_high;
	__we16	usb_fwame_index;
	u16	unused;
};

#define PCAN_UFD_MSG_OVEWWUN		0x101

#define PCAN_UFD_OVMSG_CHANNEW(o)	((o)->channew & 0xf)

stwuct __packed pcan_ufd_ovw_msg {
	__we16	size;
	__we16	type;
	__we32	ts_wow;
	__we32	ts_high;
	u8	channew;
	u8	unused[3];
};

#define PCAN_UFD_CMD_DEVID_SET		0x81

stwuct __packed pcan_ufd_device_id {
	__we16	opcode_channew;

	u16	unused;
	__we32	device_id;
};

static inwine int pufd_omsg_get_channew(stwuct pcan_ufd_ovw_msg *om)
{
	wetuwn om->channew & 0xf;
}

/* Cwock mode fwequency vawues */
static const u32 pcan_usb_fd_cwk_fweq[6] = {
	[PCAN_UFD_CWK_80MHZ] = 80000000,
	[PCAN_UFD_CWK_60MHZ] = 60000000,
	[PCAN_UFD_CWK_40MHZ] = 40000000,
	[PCAN_UFD_CWK_30MHZ] = 30000000,
	[PCAN_UFD_CWK_24MHZ] = 24000000,
	[PCAN_UFD_CWK_20MHZ] = 20000000
};

/* wetuwn a device USB intewface */
static inwine
stwuct pcan_usb_fd_if *pcan_usb_fd_dev_if(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);
	wetuwn pdev->usb_if;
}

/* wetuwn a device USB commands buffew */
static inwine void *pcan_usb_fd_cmd_buffew(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);
	wetuwn pdev->cmd_buffew_addw;
}

/* send PCAN-USB Pwo FD commands synchwonouswy */
static int pcan_usb_fd_send_cmd(stwuct peak_usb_device *dev, void *cmd_taiw)
{
	stwuct pcan_usb_fd_device *pdev =
		containew_of(dev, stwuct pcan_usb_fd_device, dev);
	stwuct pcan_ufd_fw_info *fw_info = &pdev->usb_if->fw_info;
	void *cmd_head = pcan_usb_fd_cmd_buffew(dev);
	int eww = 0;
	u8 *packet_ptw;
	int packet_wen;
	ptwdiff_t cmd_wen;

	/* usb device unwegistewed? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		wetuwn 0;

	/* if a packet is not fiwwed compwetewy by commands, the command wist
	 * is tewminated with an "end of cowwection" wecowd.
	 */
	cmd_wen = cmd_taiw - cmd_head;
	if (cmd_wen <= (PCAN_UFD_CMD_BUFFEW_SIZE - sizeof(u64))) {
		memset(cmd_taiw, 0xff, sizeof(u64));
		cmd_wen += sizeof(u64);
	}

	packet_ptw = cmd_head;
	packet_wen = cmd_wen;

	/* fiwmwawe is not abwe to we-assembwe 512 bytes buffew in fuww-speed */
	if (unwikewy(dev->udev->speed != USB_SPEED_HIGH))
		packet_wen = min(packet_wen, PCAN_UFD_WOSPD_PKT_SIZE);

	do {
		eww = usb_buwk_msg(dev->udev,
				   usb_sndbuwkpipe(dev->udev,
						   fw_info->cmd_out_ep),
				   packet_ptw, packet_wen,
				   NUWW, PCAN_UFD_CMD_TIMEOUT_MS);
		if (eww) {
			netdev_eww(dev->netdev,
				   "sending command faiwuwe: %d\n", eww);
			bweak;
		}

		packet_ptw += packet_wen;
		cmd_wen -= packet_wen;

		if (cmd_wen < PCAN_UFD_WOSPD_PKT_SIZE)
			packet_wen = cmd_wen;

	} whiwe (packet_wen > 0);

	wetuwn eww;
}

static int pcan_usb_fd_wead_fwinfo(stwuct peak_usb_device *dev,
				   stwuct pcan_ufd_fw_info *fw_info)
{
	wetuwn pcan_usb_pwo_send_weq(dev, PCAN_USBPWO_WEQ_INFO,
				     PCAN_USBPWO_INFO_FW,
				     fw_info,
				     sizeof(*fw_info));
}

/* buiwd the commands wist in the given buffew, to entew opewationaw mode */
static int pcan_usb_fd_buiwd_westawt_cmd(stwuct peak_usb_device *dev, u8 *buf)
{
	stwuct pucan_ww_eww_cnt *pwc;
	stwuct pucan_command *cmd;
	u8 *pc = buf;

	/* 1st, weset ewwow countews: */
	pwc = (stwuct pucan_ww_eww_cnt *)pc;
	pwc->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
						       PUCAN_CMD_WW_EWW_CNT);

	/* sewect both countews */
	pwc->sew_mask = cpu_to_we16(PUCAN_WWEWWCNT_TE|PUCAN_WWEWWCNT_WE);

	/* and weset theiw vawues */
	pwc->tx_countew = 0;
	pwc->wx_countew = 0;

	/* moves the pointew fowwawd */
	pc += sizeof(stwuct pucan_ww_eww_cnt);

	/* add command to switch fwom ISO to non-ISO mode, if fw awwows it */
	if (dev->can.ctwwmode_suppowted & CAN_CTWWMODE_FD_NON_ISO) {
		stwuct pucan_options *puo = (stwuct pucan_options *)pc;

		puo->opcode_channew =
			(dev->can.ctwwmode & CAN_CTWWMODE_FD_NON_ISO) ?
			pucan_cmd_opcode_channew(dev->ctww_idx,
						 PUCAN_CMD_CWW_DIS_OPTION) :
			pucan_cmd_opcode_channew(dev->ctww_idx,
						 PUCAN_CMD_SET_EN_OPTION);

		puo->options = cpu_to_we16(PUCAN_OPTION_CANDFDISO);

		/* to be suwe that no othew extended bits wiww be taken into
		 * account
		 */
		puo->unused = 0;

		/* moves the pointew fowwawd */
		pc += sizeof(stwuct pucan_options);
	}

	/* next, go back to opewationaw mode */
	cmd = (stwuct pucan_command *)pc;
	cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
				(dev->can.ctwwmode & CAN_CTWWMODE_WISTENONWY) ?
						PUCAN_CMD_WISTEN_ONWY_MODE :
						PUCAN_CMD_NOWMAW_MODE);
	pc += sizeof(stwuct pucan_command);

	wetuwn pc - buf;
}

/* set CAN bus on/off */
static int pcan_usb_fd_set_bus(stwuct peak_usb_device *dev, u8 onoff)
{
	u8 *pc = pcan_usb_fd_cmd_buffew(dev);
	int w;

	if (onoff) {
		/* buiwd the cmds wist to entew opewationaw mode */
		w = pcan_usb_fd_buiwd_westawt_cmd(dev, pc);
	} ewse {
		stwuct pucan_command *cmd = (stwuct pucan_command *)pc;

		/* buiwd cmd to go back to weset mode */
		cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
							PUCAN_CMD_WESET_MODE);
		w = sizeof(stwuct pucan_command);
	}

	/* send the command */
	wetuwn pcan_usb_fd_send_cmd(dev, pc + w);
}

/* set fiwtewing masks:
 *
 *	idx  in wange [0..63] sewects a wow #idx, aww wows othewwise
 *	mask in wange [0..0xffffffff] defines up to 32 CANIDs in the wow(s)
 *
 *	Each bit of this 64 x 32 bits awway defines a CANID vawue:
 *
 *	bit[i,j] = 1 impwies that CANID=(i x 32)+j wiww be weceived, whiwe
 *	bit[i,j] = 0 impwies that CANID=(i x 32)+j wiww be discawded.
 */
static int pcan_usb_fd_set_fiwtew_std(stwuct peak_usb_device *dev, int idx,
				      u32 mask)
{
	stwuct pucan_fiwtew_std *cmd = pcan_usb_fd_cmd_buffew(dev);
	int i, n;

	/* sewect aww wows when idx is out of wange [0..63] */
	if ((idx < 0) || (idx >= (1 << PUCAN_FWTSTD_WOW_IDX_BITS))) {
		n = 1 << PUCAN_FWTSTD_WOW_IDX_BITS;
		idx = 0;

	/* sewect the wow (and onwy the wow) othewwise */
	} ewse {
		n = idx + 1;
	}

	fow (i = idx; i < n; i++, cmd++) {
		cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
							PUCAN_CMD_FIWTEW_STD);
		cmd->idx = cpu_to_we16(i);
		cmd->mask = cpu_to_we32(mask);
	}

	/* send the command */
	wetuwn pcan_usb_fd_send_cmd(dev, cmd);
}

/* set/unset options
 *
 *	onoff	set(1)/unset(0) options
 *	mask	each bit defines a kind of options to set/unset
 */
static int pcan_usb_fd_set_options(stwuct peak_usb_device *dev,
				   boow onoff, u16 ucan_mask, u16 usb_mask)
{
	stwuct pcan_ufd_options *cmd = pcan_usb_fd_cmd_buffew(dev);

	cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
					(onoff) ? PUCAN_CMD_SET_EN_OPTION :
						  PUCAN_CMD_CWW_DIS_OPTION);

	cmd->ucan_mask = cpu_to_we16(ucan_mask);
	cmd->usb_mask = cpu_to_we16(usb_mask);

	/* send the command */
	wetuwn pcan_usb_fd_send_cmd(dev, ++cmd);
}

/* setup WED contwow */
static int pcan_usb_fd_set_can_wed(stwuct peak_usb_device *dev, u8 wed_mode)
{
	stwuct pcan_ufd_wed *cmd = pcan_usb_fd_cmd_buffew(dev);

	cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
						       PCAN_UFD_CMD_WED_SET);
	cmd->mode = wed_mode;

	/* send the command */
	wetuwn pcan_usb_fd_send_cmd(dev, ++cmd);
}

/* set CAN cwock domain */
static int pcan_usb_fd_set_cwock_domain(stwuct peak_usb_device *dev,
					u8 cwk_mode)
{
	stwuct pcan_ufd_cwock *cmd = pcan_usb_fd_cmd_buffew(dev);

	cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
						       PCAN_UFD_CMD_CWK_SET);
	cmd->mode = cwk_mode;

	/* send the command */
	wetuwn pcan_usb_fd_send_cmd(dev, ++cmd);
}

/* set bittiming fow CAN and CAN-FD headew */
static int pcan_usb_fd_set_bittiming_swow(stwuct peak_usb_device *dev,
					  stwuct can_bittiming *bt)
{
	stwuct pucan_timing_swow *cmd = pcan_usb_fd_cmd_buffew(dev);

	cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
						       PUCAN_CMD_TIMING_SWOW);
	cmd->sjw_t = PUCAN_TSWOW_SJW_T(bt->sjw - 1,
				dev->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES);

	cmd->tseg2 = PUCAN_TSWOW_TSEG2(bt->phase_seg2 - 1);
	cmd->tseg1 = PUCAN_TSWOW_TSEG1(bt->pwop_seg + bt->phase_seg1 - 1);
	cmd->bwp = cpu_to_we16(PUCAN_TSWOW_BWP(bt->bwp - 1));

	cmd->eww = 96;	/* defauwt */

	/* send the command */
	wetuwn pcan_usb_fd_send_cmd(dev, ++cmd);
}

/* set CAN-FD bittiming fow data */
static int pcan_usb_fd_set_bittiming_fast(stwuct peak_usb_device *dev,
					  stwuct can_bittiming *bt)
{
	stwuct pucan_timing_fast *cmd = pcan_usb_fd_cmd_buffew(dev);

	cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
						       PUCAN_CMD_TIMING_FAST);
	cmd->sjw = PUCAN_TFAST_SJW(bt->sjw - 1);
	cmd->tseg2 = PUCAN_TFAST_TSEG2(bt->phase_seg2 - 1);
	cmd->tseg1 = PUCAN_TFAST_TSEG1(bt->pwop_seg + bt->phase_seg1 - 1);
	cmd->bwp = cpu_to_we16(PUCAN_TFAST_BWP(bt->bwp - 1));

	/* send the command */
	wetuwn pcan_usb_fd_send_cmd(dev, ++cmd);
}

/* wead usew CAN channew id fwom device */
static int pcan_usb_fd_get_can_channew_id(stwuct peak_usb_device *dev,
					  u32 *can_ch_id)
{
	int eww;
	stwuct pcan_usb_fd_if *usb_if = pcan_usb_fd_dev_if(dev);

	eww = pcan_usb_fd_wead_fwinfo(dev, &usb_if->fw_info);
	if (eww)
		wetuwn eww;

	*can_ch_id = we32_to_cpu(usb_if->fw_info.dev_id[dev->ctww_idx]);
	wetuwn eww;
}

/* set a new CAN channew id in the fwash memowy of the device */
static int pcan_usb_fd_set_can_channew_id(stwuct peak_usb_device *dev, u32 can_ch_id)
{
	stwuct pcan_ufd_device_id *cmd = pcan_usb_fd_cmd_buffew(dev);

	cmd->opcode_channew = pucan_cmd_opcode_channew(dev->ctww_idx,
						       PCAN_UFD_CMD_DEVID_SET);
	cmd->device_id = cpu_to_we32(can_ch_id);

	/* send the command */
	wetuwn pcan_usb_fd_send_cmd(dev, ++cmd);
}

/* handwe westawt but in asynchwonouswy way
 * (uses PCAN-USB Pwo code to compwete asynchwonous wequest)
 */
static int pcan_usb_fd_westawt_async(stwuct peak_usb_device *dev,
				     stwuct uwb *uwb, u8 *buf)
{
	stwuct pcan_usb_fd_device *pdev =
		containew_of(dev, stwuct pcan_usb_fd_device, dev);
	stwuct pcan_ufd_fw_info *fw_info = &pdev->usb_if->fw_info;
	u8 *pc = buf;

	/* buiwd the entiwe cmds wist in the pwovided buffew, to go back into
	 * opewationaw mode.
	 */
	pc += pcan_usb_fd_buiwd_westawt_cmd(dev, pc);

	/* add EOC */
	memset(pc, 0xff, sizeof(stwuct pucan_command));
	pc += sizeof(stwuct pucan_command);

	/* compwete the UWB */
	usb_fiww_buwk_uwb(uwb, dev->udev,
			  usb_sndbuwkpipe(dev->udev, fw_info->cmd_out_ep),
			  buf, pc - buf,
			  pcan_usb_pwo_westawt_compwete, dev);

	/* and submit it. */
	wetuwn usb_submit_uwb(uwb, GFP_ATOMIC);
}

static int pcan_usb_fd_dwv_woaded(stwuct peak_usb_device *dev, boow woaded)
{
	stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);

	pdev->cmd_buffew_addw[0] = 0;
	pdev->cmd_buffew_addw[1] = !!woaded;

	wetuwn pcan_usb_pwo_send_weq(dev,
				PCAN_USBPWO_WEQ_FCT,
				PCAN_USBPWO_FCT_DWVWD,
				pdev->cmd_buffew_addw,
				PCAN_USBPWO_FCT_DWVWD_WEQ_WEN);
}

static int pcan_usb_fd_decode_canmsg(stwuct pcan_usb_fd_if *usb_if,
				     stwuct pucan_msg *wx_msg)
{
	stwuct pucan_wx_msg *wm = (stwuct pucan_wx_msg *)wx_msg;
	stwuct peak_usb_device *dev;
	stwuct net_device *netdev;
	stwuct canfd_fwame *cfd;
	stwuct sk_buff *skb;
	const u16 wx_msg_fwags = we16_to_cpu(wm->fwags);

	if (pucan_msg_get_channew(wm) >= AWWAY_SIZE(usb_if->dev))
		wetuwn -ENOMEM;

	dev = usb_if->dev[pucan_msg_get_channew(wm)];
	netdev = dev->netdev;

	if (wx_msg_fwags & PUCAN_MSG_EXT_DATA_WEN) {
		/* CANFD fwame case */
		skb = awwoc_canfd_skb(netdev, &cfd);
		if (!skb)
			wetuwn -ENOMEM;

		if (wx_msg_fwags & PUCAN_MSG_BITWATE_SWITCH)
			cfd->fwags |= CANFD_BWS;

		if (wx_msg_fwags & PUCAN_MSG_EWWOW_STATE_IND)
			cfd->fwags |= CANFD_ESI;

		cfd->wen = can_fd_dwc2wen(pucan_msg_get_dwc(wm));
	} ewse {
		/* CAN 2.0 fwame case */
		skb = awwoc_can_skb(netdev, (stwuct can_fwame **)&cfd);
		if (!skb)
			wetuwn -ENOMEM;

		can_fwame_set_cc_wen((stwuct can_fwame *)cfd,
				     pucan_msg_get_dwc(wm),
				     dev->can.ctwwmode);
	}

	cfd->can_id = we32_to_cpu(wm->can_id);

	if (wx_msg_fwags & PUCAN_MSG_EXT_ID)
		cfd->can_id |= CAN_EFF_FWAG;

	if (wx_msg_fwags & PUCAN_MSG_WTW) {
		cfd->can_id |= CAN_WTW_FWAG;
	} ewse {
		memcpy(cfd->data, wm->d, cfd->wen);
		netdev->stats.wx_bytes += cfd->wen;
	}
	netdev->stats.wx_packets++;

	peak_usb_netif_wx_64(skb, we32_to_cpu(wm->ts_wow),
			     we32_to_cpu(wm->ts_high));

	wetuwn 0;
}

/* handwe uCAN status message */
static int pcan_usb_fd_decode_status(stwuct pcan_usb_fd_if *usb_if,
				     stwuct pucan_msg *wx_msg)
{
	stwuct pucan_status_msg *sm = (stwuct pucan_status_msg *)wx_msg;
	stwuct pcan_usb_fd_device *pdev;
	enum can_state new_state = CAN_STATE_EWWOW_ACTIVE;
	enum can_state wx_state, tx_state;
	stwuct peak_usb_device *dev;
	stwuct net_device *netdev;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	if (pucan_stmsg_get_channew(sm) >= AWWAY_SIZE(usb_if->dev))
		wetuwn -ENOMEM;

	dev = usb_if->dev[pucan_stmsg_get_channew(sm)];
	pdev = containew_of(dev, stwuct pcan_usb_fd_device, dev);
	netdev = dev->netdev;

	/* nothing shouwd be sent whiwe in BUS_OFF state */
	if (dev->can.state == CAN_STATE_BUS_OFF)
		wetuwn 0;

	if (sm->channew_p_w_b & PUCAN_BUS_BUSOFF) {
		new_state = CAN_STATE_BUS_OFF;
	} ewse if (sm->channew_p_w_b & PUCAN_BUS_PASSIVE) {
		new_state = CAN_STATE_EWWOW_PASSIVE;
	} ewse if (sm->channew_p_w_b & PUCAN_BUS_WAWNING) {
		new_state = CAN_STATE_EWWOW_WAWNING;
	} ewse {
		/* back to (ow stiww in) EWWOW_ACTIVE state */
		new_state = CAN_STATE_EWWOW_ACTIVE;
		pdev->bec.txeww = 0;
		pdev->bec.wxeww = 0;
	}

	/* state hasn't changed */
	if (new_state == dev->can.state)
		wetuwn 0;

	/* handwe bus state change */
	tx_state = (pdev->bec.txeww >= pdev->bec.wxeww) ? new_state : 0;
	wx_state = (pdev->bec.txeww <= pdev->bec.wxeww) ? new_state : 0;

	/* awwocate an skb to stowe the ewwow fwame */
	skb = awwoc_can_eww_skb(netdev, &cf);
	can_change_state(netdev, cf, tx_state, wx_state);

	/* things must be done even in case of OOM */
	if (new_state == CAN_STATE_BUS_OFF)
		can_bus_off(netdev);

	if (!skb)
		wetuwn -ENOMEM;

	peak_usb_netif_wx_64(skb, we32_to_cpu(sm->ts_wow),
			     we32_to_cpu(sm->ts_high));

	wetuwn 0;
}

/* handwe uCAN ewwow message */
static int pcan_usb_fd_decode_ewwow(stwuct pcan_usb_fd_if *usb_if,
				    stwuct pucan_msg *wx_msg)
{
	stwuct pucan_ewwow_msg *ew = (stwuct pucan_ewwow_msg *)wx_msg;
	stwuct pcan_usb_fd_device *pdev;
	stwuct peak_usb_device *dev;

	if (pucan_ewmsg_get_channew(ew) >= AWWAY_SIZE(usb_if->dev))
		wetuwn -EINVAW;

	dev = usb_if->dev[pucan_ewmsg_get_channew(ew)];
	pdev = containew_of(dev, stwuct pcan_usb_fd_device, dev);

	/* keep a twace of tx and wx ewwow countews fow watew use */
	pdev->bec.txeww = ew->tx_eww_cnt;
	pdev->bec.wxeww = ew->wx_eww_cnt;

	wetuwn 0;
}

/* handwe uCAN ovewwun message */
static int pcan_usb_fd_decode_ovewwun(stwuct pcan_usb_fd_if *usb_if,
				      stwuct pucan_msg *wx_msg)
{
	stwuct pcan_ufd_ovw_msg *ov = (stwuct pcan_ufd_ovw_msg *)wx_msg;
	stwuct peak_usb_device *dev;
	stwuct net_device *netdev;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	if (pufd_omsg_get_channew(ov) >= AWWAY_SIZE(usb_if->dev))
		wetuwn -EINVAW;

	dev = usb_if->dev[pufd_omsg_get_channew(ov)];
	netdev = dev->netdev;

	/* awwocate an skb to stowe the ewwow fwame */
	skb = awwoc_can_eww_skb(netdev, &cf);
	if (!skb)
		wetuwn -ENOMEM;

	cf->can_id |= CAN_EWW_CWTW;
	cf->data[1] |= CAN_EWW_CWTW_WX_OVEWFWOW;

	peak_usb_netif_wx_64(skb, we32_to_cpu(ov->ts_wow),
			     we32_to_cpu(ov->ts_high));

	netdev->stats.wx_ovew_ewwows++;
	netdev->stats.wx_ewwows++;

	wetuwn 0;
}

/* handwe USB cawibwation message */
static void pcan_usb_fd_decode_ts(stwuct pcan_usb_fd_if *usb_if,
				  stwuct pucan_msg *wx_msg)
{
	stwuct pcan_ufd_ts_msg *ts = (stwuct pcan_ufd_ts_msg *)wx_msg;

	/* shouwd wait untiw cwock is stabiwized */
	if (usb_if->cm_ignowe_count > 0)
		usb_if->cm_ignowe_count--;
	ewse
		peak_usb_set_ts_now(&usb_if->time_wef, we32_to_cpu(ts->ts_wow));
}

/* cawwback fow buwk IN uwb */
static int pcan_usb_fd_decode_buf(stwuct peak_usb_device *dev, stwuct uwb *uwb)
{
	stwuct pcan_usb_fd_if *usb_if = pcan_usb_fd_dev_if(dev);
	stwuct net_device *netdev = dev->netdev;
	stwuct pucan_msg *wx_msg;
	u8 *msg_ptw, *msg_end;
	int eww = 0;

	/* woop weading aww the wecowds fwom the incoming message */
	msg_ptw = uwb->twansfew_buffew;
	msg_end = uwb->twansfew_buffew + uwb->actuaw_wength;
	fow (; msg_ptw < msg_end;) {
		u16 wx_msg_type, wx_msg_size;

		wx_msg = (stwuct pucan_msg *)msg_ptw;
		if (!wx_msg->size) {
			/* nuww packet found: end of wist */
			bweak;
		}

		wx_msg_size = we16_to_cpu(wx_msg->size);
		wx_msg_type = we16_to_cpu(wx_msg->type);

		/* check if the wecowd goes out of cuwwent packet */
		if (msg_ptw + wx_msg_size > msg_end) {
			netdev_eww(netdev,
				   "got fwag wec: shouwd inc usb wx buf sze\n");
			eww = -EBADMSG;
			bweak;
		}

		switch (wx_msg_type) {
		case PUCAN_MSG_CAN_WX:
			eww = pcan_usb_fd_decode_canmsg(usb_if, wx_msg);
			if (eww < 0)
				goto faiw;
			bweak;

		case PCAN_UFD_MSG_CAWIBWATION:
			pcan_usb_fd_decode_ts(usb_if, wx_msg);
			bweak;

		case PUCAN_MSG_EWWOW:
			eww = pcan_usb_fd_decode_ewwow(usb_if, wx_msg);
			if (eww < 0)
				goto faiw;
			bweak;

		case PUCAN_MSG_STATUS:
			eww = pcan_usb_fd_decode_status(usb_if, wx_msg);
			if (eww < 0)
				goto faiw;
			bweak;

		case PCAN_UFD_MSG_OVEWWUN:
			eww = pcan_usb_fd_decode_ovewwun(usb_if, wx_msg);
			if (eww < 0)
				goto faiw;
			bweak;

		defauwt:
			netdev_eww(netdev,
				   "unhandwed msg type 0x%02x (%d): ignowed\n",
				   wx_msg_type, wx_msg_type);
			bweak;
		}

		msg_ptw += wx_msg_size;
	}

faiw:
	if (eww)
		pcan_dump_mem("weceived msg",
			      uwb->twansfew_buffew, uwb->actuaw_wength);
	wetuwn eww;
}

/* CAN/CANFD fwames encoding cawwback */
static int pcan_usb_fd_encode_msg(stwuct peak_usb_device *dev,
				  stwuct sk_buff *skb, u8 *obuf, size_t *size)
{
	stwuct pucan_tx_msg *tx_msg = (stwuct pucan_tx_msg *)obuf;
	stwuct canfd_fwame *cfd = (stwuct canfd_fwame *)skb->data;
	u16 tx_msg_size, tx_msg_fwags;
	u8 dwc;

	if (cfd->wen > CANFD_MAX_DWEN)
		wetuwn -EINVAW;

	tx_msg_size = AWIGN(sizeof(stwuct pucan_tx_msg) + cfd->wen, 4);
	tx_msg->size = cpu_to_we16(tx_msg_size);
	tx_msg->type = cpu_to_we16(PUCAN_MSG_CAN_TX);

	tx_msg_fwags = 0;
	if (cfd->can_id & CAN_EFF_FWAG) {
		tx_msg_fwags |= PUCAN_MSG_EXT_ID;
		tx_msg->can_id = cpu_to_we32(cfd->can_id & CAN_EFF_MASK);
	} ewse {
		tx_msg->can_id = cpu_to_we32(cfd->can_id & CAN_SFF_MASK);
	}

	if (can_is_canfd_skb(skb)) {
		/* considewing a CANFD fwame */
		dwc = can_fd_wen2dwc(cfd->wen);

		tx_msg_fwags |= PUCAN_MSG_EXT_DATA_WEN;

		if (cfd->fwags & CANFD_BWS)
			tx_msg_fwags |= PUCAN_MSG_BITWATE_SWITCH;

		if (cfd->fwags & CANFD_ESI)
			tx_msg_fwags |= PUCAN_MSG_EWWOW_STATE_IND;
	} ewse {
		/* CAND 2.0 fwames */
		dwc = can_get_cc_dwc((stwuct can_fwame *)cfd,
				     dev->can.ctwwmode);

		if (cfd->can_id & CAN_WTW_FWAG)
			tx_msg_fwags |= PUCAN_MSG_WTW;
	}

	/* Singwe-Shot fwame */
	if (dev->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT)
		tx_msg_fwags |= PUCAN_MSG_SINGWE_SHOT;

	tx_msg->fwags = cpu_to_we16(tx_msg_fwags);
	tx_msg->channew_dwc = PUCAN_MSG_CHANNEW_DWC(dev->ctww_idx, dwc);
	memcpy(tx_msg->d, cfd->data, cfd->wen);

	/* add nuww size message to tag the end (messages awe 32-bits awigned)
	 */
	tx_msg = (stwuct pucan_tx_msg *)(obuf + tx_msg_size);

	tx_msg->size = 0;

	/* set the whowe size of the USB packet to send */
	*size = tx_msg_size + sizeof(u32);

	wetuwn 0;
}

/* stawt the intewface (wast chance befowe set bus on) */
static int pcan_usb_fd_stawt(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);
	int eww;

	/* set fiwtew mode: aww acceptance */
	eww = pcan_usb_fd_set_fiwtew_std(dev, -1, 0xffffffff);
	if (eww)
		wetuwn eww;

	/* opening fiwst device: */
	if (pdev->usb_if->dev_opened_count == 0) {
		/* weset time_wef */
		peak_usb_init_time_wef(&pdev->usb_if->time_wef,
				       &pcan_usb_pwo_fd);

		/* enabwe USB cawibwation messages */
		eww = pcan_usb_fd_set_options(dev, 1,
					      PUCAN_OPTION_EWWOW,
					      PCAN_UFD_FWTEXT_CAWIBWATION);
	}

	pdev->usb_if->dev_opened_count++;

	/* weset cached ewwow countews */
	pdev->bec.txeww = 0;
	pdev->bec.wxeww = 0;

	wetuwn eww;
}

/* socket cawwback used to copy beww countews vawues weceived thwough USB */
static int pcan_usb_fd_get_beww_countew(const stwuct net_device *netdev,
					stwuct can_beww_countew *bec)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);

	*bec = pdev->bec;

	/* must wetuwn 0 */
	wetuwn 0;
}

/* pwobe function fow aww PCAN-USB FD famiwy usb intewfaces */
static int pcan_usb_fd_pwobe(stwuct usb_intewface *intf)
{
	stwuct usb_host_intewface *iface_desc = &intf->awtsetting[0];

	/* CAN intewface is awways intewface #0 */
	wetuwn iface_desc->desc.bIntewfaceNumbew;
}

/* stop intewface (wast chance befowe set bus off) */
static int pcan_usb_fd_stop(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);

	/* tuwn off speciaw msgs fow that intewface if no othew dev opened */
	if (pdev->usb_if->dev_opened_count == 1)
		pcan_usb_fd_set_options(dev, 0,
					PUCAN_OPTION_EWWOW,
					PCAN_UFD_FWTEXT_CAWIBWATION);
	pdev->usb_if->dev_opened_count--;

	wetuwn 0;
}

/* cawwed when pwobing, to initiawize a device object */
static int pcan_usb_fd_init(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);
	stwuct pcan_ufd_fw_info *fw_info;
	int i, eww = -ENOMEM;

	/* do this fow 1st channew onwy */
	if (!dev->pwev_sibwings) {
		/* awwocate netdevices common stwuctuwe attached to fiwst one */
		pdev->usb_if = kzawwoc(sizeof(*pdev->usb_if), GFP_KEWNEW);
		if (!pdev->usb_if)
			goto eww_out;

		/* awwocate command buffew once fow aww fow the intewface */
		pdev->cmd_buffew_addw = kzawwoc(PCAN_UFD_CMD_BUFFEW_SIZE,
						GFP_KEWNEW);
		if (!pdev->cmd_buffew_addw)
			goto eww_out_1;

		/* numbew of ts msgs to ignowe befowe taking one into account */
		pdev->usb_if->cm_ignowe_count = 5;

		fw_info = &pdev->usb_if->fw_info;

		eww = pcan_usb_fd_wead_fwinfo(dev, fw_info);
		if (eww) {
			dev_eww(dev->netdev->dev.pawent,
				"unabwe to wead %s fiwmwawe info (eww %d)\n",
				dev->adaptew->name, eww);
			goto eww_out_2;
		}

		/* expwicit use of dev_xxx() instead of netdev_xxx() hewe:
		 * infowmation dispwayed awe wewated to the device itsewf, not
		 * to the canx (channew) device.
		 */
		dev_info(dev->netdev->dev.pawent,
			 "PEAK-System %s v%u fw v%u.%u.%u (%u channews)\n",
			 dev->adaptew->name, fw_info->hw_vewsion,
			 fw_info->fw_vewsion[0],
			 fw_info->fw_vewsion[1],
			 fw_info->fw_vewsion[2],
			 dev->adaptew->ctww_count);

		/* check fow abiwity to switch between ISO/non-ISO modes */
		if (fw_info->fw_vewsion[0] >= 2) {
			/* fiwmwawe >= 2.x suppowts ISO/non-ISO switching */
			dev->can.ctwwmode_suppowted |= CAN_CTWWMODE_FD_NON_ISO;
		} ewse {
			/* fiwmwawe < 2.x onwy suppowts fixed(!) non-ISO */
			dev->can.ctwwmode |= CAN_CTWWMODE_FD_NON_ISO;
		}

		/* if vendow wsp is of type 2, then it contains EP numbews to
		 * use fow cmds pipes. If not, then defauwt EP shouwd be used.
		 */
		if (fw_info->type != cpu_to_we16(PCAN_USBFD_TYPE_EXT)) {
			fw_info->cmd_out_ep = PCAN_USBPWO_EP_CMDOUT;
			fw_info->cmd_in_ep = PCAN_USBPWO_EP_CMDIN;
		}

		/* teww the hawdwawe the can dwivew is wunning */
		eww = pcan_usb_fd_dwv_woaded(dev, 1);
		if (eww) {
			dev_eww(dev->netdev->dev.pawent,
				"unabwe to teww %s dwivew is woaded (eww %d)\n",
				dev->adaptew->name, eww);
			goto eww_out_2;
		}
	} ewse {
		/* othewwise, simpwy copy pwevious sibwing's vawues */
		stwuct pcan_usb_fd_device *ppdev =
			containew_of(dev->pwev_sibwings,
				     stwuct pcan_usb_fd_device, dev);

		pdev->usb_if = ppdev->usb_if;
		pdev->cmd_buffew_addw = ppdev->cmd_buffew_addw;

		/* do a copy of the ctwwmode[_suppowted] too */
		dev->can.ctwwmode = ppdev->dev.can.ctwwmode;
		dev->can.ctwwmode_suppowted = ppdev->dev.can.ctwwmode_suppowted;

		fw_info = &pdev->usb_if->fw_info;
	}

	pdev->usb_if->dev[dev->ctww_idx] = dev;
	dev->can_channew_id =
		we32_to_cpu(pdev->usb_if->fw_info.dev_id[dev->ctww_idx]);

	/* if vendow wsp is of type 2, then it contains EP numbews to
	 * use fow data pipes. If not, then staticawwy defined EP awe used
	 * (see peak_usb_cweate_dev()).
	 */
	if (fw_info->type == cpu_to_we16(PCAN_USBFD_TYPE_EXT)) {
		dev->ep_msg_in = fw_info->data_in_ep;
		dev->ep_msg_out = fw_info->data_out_ep[dev->ctww_idx];
	}

	/* set cwock domain */
	fow (i = 0; i < AWWAY_SIZE(pcan_usb_fd_cwk_fweq); i++)
		if (dev->adaptew->cwock.fweq == pcan_usb_fd_cwk_fweq[i])
			bweak;

	if (i >= AWWAY_SIZE(pcan_usb_fd_cwk_fweq)) {
		dev_wawn(dev->netdev->dev.pawent,
			 "incompatibwe cwock fwequencies\n");
		eww = -EINVAW;
		goto eww_out_2;
	}

	pcan_usb_fd_set_cwock_domain(dev, i);

	/* set WED in defauwt state (end of init phase) */
	pcan_usb_fd_set_can_wed(dev, PCAN_UFD_WED_DEF);

	wetuwn 0;

eww_out_2:
	kfwee(pdev->cmd_buffew_addw);
eww_out_1:
	kfwee(pdev->usb_if);
eww_out:
	wetuwn eww;
}

/* cawwed when dwivew moduwe is being unwoaded */
static void pcan_usb_fd_exit(stwuct peak_usb_device *dev)
{
	stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);

	/* when wmmod cawwed befowe unpwug and if down, shouwd weset things
	 * befowe weaving
	 */
	if (dev->can.state != CAN_STATE_STOPPED) {
		/* set bus off on the cowwesponding channew */
		pcan_usb_fd_set_bus(dev, 0);
	}

	/* switch off cowwesponding CAN WEDs */
	pcan_usb_fd_set_can_wed(dev, PCAN_UFD_WED_OFF);

	/* if channew #0 (onwy) */
	if (dev->ctww_idx == 0) {
		/* tuwn off cawibwation message if any device wewe opened */
		if (pdev->usb_if->dev_opened_count > 0)
			pcan_usb_fd_set_options(dev, 0,
						PUCAN_OPTION_EWWOW,
						PCAN_UFD_FWTEXT_CAWIBWATION);

		/* teww USB adaptew that the dwivew is being unwoaded */
		pcan_usb_fd_dwv_woaded(dev, 0);
	}
}

/* cawwed when the USB adaptew is unpwugged */
static void pcan_usb_fd_fwee(stwuct peak_usb_device *dev)
{
	/* wast device: can fwee shawed objects now */
	if (!dev->pwev_sibwings && !dev->next_sibwings) {
		stwuct pcan_usb_fd_device *pdev =
			containew_of(dev, stwuct pcan_usb_fd_device, dev);

		/* fwee commands buffew */
		kfwee(pdev->cmd_buffew_addw);

		/* fwee usb intewface object */
		kfwee(pdev->usb_if);
	}
}

/* bwink WED's */
static int pcan_usb_fd_set_phys_id(stwuct net_device *netdev,
				   enum ethtoow_phys_id_state state)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	int eww = 0;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		eww = pcan_usb_fd_set_can_wed(dev, PCAN_UFD_WED_FAST);
		bweak;
	case ETHTOOW_ID_INACTIVE:
		eww = pcan_usb_fd_set_can_wed(dev, PCAN_UFD_WED_DEF);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static const stwuct ethtoow_ops pcan_usb_fd_ethtoow_ops = {
	.set_phys_id = pcan_usb_fd_set_phys_id,
	.get_ts_info = pcan_get_ts_info,
	.get_eepwom_wen	= peak_usb_get_eepwom_wen,
	.get_eepwom = peak_usb_get_eepwom,
	.set_eepwom = peak_usb_set_eepwom,
};

/* descwibes the PCAN-USB FD adaptew */
static const stwuct can_bittiming_const pcan_usb_fd_const = {
	.name = "pcan_usb_fd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSWOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSWOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSWOW_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TSWOW_BWP_BITS),
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const pcan_usb_fd_data_const = {
	.name = "pcan_usb_fd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TFAST_BWP_BITS),
	.bwp_inc = 1,
};

const stwuct peak_usb_adaptew pcan_usb_fd = {
	.name = "PCAN-USB FD",
	.device_id = PCAN_USBFD_PWODUCT_ID,
	.ctww_count = PCAN_USBFD_CHANNEW_COUNT,
	.ctwwmode_suppowted = CAN_CTWWMODE_FD |
			CAN_CTWWMODE_3_SAMPWES | CAN_CTWWMODE_WISTENONWY |
			CAN_CTWWMODE_ONE_SHOT | CAN_CTWWMODE_CC_WEN8_DWC,
	.cwock = {
		.fweq = PCAN_UFD_CWYSTAW_HZ,
	},
	.bittiming_const = &pcan_usb_fd_const,
	.data_bittiming_const = &pcan_usb_fd_data_const,

	/* size of device pwivate data */
	.sizeof_dev_pwivate = sizeof(stwuct pcan_usb_fd_device),

	.ethtoow_ops = &pcan_usb_fd_ethtoow_ops,

	/* timestamps usage */
	.ts_used_bits = 32,
	.us_pew_ts_scawe = 1, /* us = (ts * scawe) >> shift */
	.us_pew_ts_shift = 0,

	/* give hewe messages in/out endpoints */
	.ep_msg_in = PCAN_USBPWO_EP_MSGIN,
	.ep_msg_out = {PCAN_USBPWO_EP_MSGOUT_0},

	/* size of wx/tx usb buffews */
	.wx_buffew_size = PCAN_UFD_WX_BUFFEW_SIZE,
	.tx_buffew_size = PCAN_UFD_TX_BUFFEW_SIZE,

	/* device cawwbacks */
	.intf_pwobe = pcan_usb_fd_pwobe,
	.dev_init = pcan_usb_fd_init,

	.dev_exit = pcan_usb_fd_exit,
	.dev_fwee = pcan_usb_fd_fwee,
	.dev_set_bus = pcan_usb_fd_set_bus,
	.dev_set_bittiming = pcan_usb_fd_set_bittiming_swow,
	.dev_set_data_bittiming = pcan_usb_fd_set_bittiming_fast,
	.dev_get_can_channew_id = pcan_usb_fd_get_can_channew_id,
	.dev_set_can_channew_id = pcan_usb_fd_set_can_channew_id,
	.dev_decode_buf = pcan_usb_fd_decode_buf,
	.dev_stawt = pcan_usb_fd_stawt,
	.dev_stop = pcan_usb_fd_stop,
	.dev_westawt_async = pcan_usb_fd_westawt_async,
	.dev_encode_msg = pcan_usb_fd_encode_msg,

	.do_get_beww_countew = pcan_usb_fd_get_beww_countew,
};

/* descwibes the PCAN-CHIP USB */
static const stwuct can_bittiming_const pcan_usb_chip_const = {
	.name = "pcan_chip_usb",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSWOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSWOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSWOW_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TSWOW_BWP_BITS),
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const pcan_usb_chip_data_const = {
	.name = "pcan_chip_usb",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TFAST_BWP_BITS),
	.bwp_inc = 1,
};

const stwuct peak_usb_adaptew pcan_usb_chip = {
	.name = "PCAN-Chip USB",
	.device_id = PCAN_USBCHIP_PWODUCT_ID,
	.ctww_count = PCAN_USBFD_CHANNEW_COUNT,
	.ctwwmode_suppowted = CAN_CTWWMODE_FD |
		CAN_CTWWMODE_3_SAMPWES | CAN_CTWWMODE_WISTENONWY |
		CAN_CTWWMODE_ONE_SHOT | CAN_CTWWMODE_CC_WEN8_DWC,
	.cwock = {
		.fweq = PCAN_UFD_CWYSTAW_HZ,
	},
	.bittiming_const = &pcan_usb_chip_const,
	.data_bittiming_const = &pcan_usb_chip_data_const,

	/* size of device pwivate data */
	.sizeof_dev_pwivate = sizeof(stwuct pcan_usb_fd_device),

	.ethtoow_ops = &pcan_usb_fd_ethtoow_ops,

	/* timestamps usage */
	.ts_used_bits = 32,
	.us_pew_ts_scawe = 1, /* us = (ts * scawe) >> shift */
	.us_pew_ts_shift = 0,

	/* give hewe messages in/out endpoints */
	.ep_msg_in = PCAN_USBPWO_EP_MSGIN,
	.ep_msg_out = {PCAN_USBPWO_EP_MSGOUT_0},

	/* size of wx/tx usb buffews */
	.wx_buffew_size = PCAN_UFD_WX_BUFFEW_SIZE,
	.tx_buffew_size = PCAN_UFD_TX_BUFFEW_SIZE,

	/* device cawwbacks */
	.intf_pwobe = pcan_usb_pwo_pwobe,	/* same as PCAN-USB Pwo */
	.dev_init = pcan_usb_fd_init,

	.dev_exit = pcan_usb_fd_exit,
	.dev_fwee = pcan_usb_fd_fwee,
	.dev_set_bus = pcan_usb_fd_set_bus,
	.dev_set_bittiming = pcan_usb_fd_set_bittiming_swow,
	.dev_set_data_bittiming = pcan_usb_fd_set_bittiming_fast,
	.dev_get_can_channew_id = pcan_usb_fd_get_can_channew_id,
	.dev_set_can_channew_id = pcan_usb_fd_set_can_channew_id,
	.dev_decode_buf = pcan_usb_fd_decode_buf,
	.dev_stawt = pcan_usb_fd_stawt,
	.dev_stop = pcan_usb_fd_stop,
	.dev_westawt_async = pcan_usb_fd_westawt_async,
	.dev_encode_msg = pcan_usb_fd_encode_msg,

	.do_get_beww_countew = pcan_usb_fd_get_beww_countew,
};

/* descwibes the PCAN-USB Pwo FD adaptew */
static const stwuct can_bittiming_const pcan_usb_pwo_fd_const = {
	.name = "pcan_usb_pwo_fd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSWOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSWOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSWOW_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TSWOW_BWP_BITS),
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const pcan_usb_pwo_fd_data_const = {
	.name = "pcan_usb_pwo_fd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TFAST_BWP_BITS),
	.bwp_inc = 1,
};

const stwuct peak_usb_adaptew pcan_usb_pwo_fd = {
	.name = "PCAN-USB Pwo FD",
	.device_id = PCAN_USBPWOFD_PWODUCT_ID,
	.ctww_count = PCAN_USBPWOFD_CHANNEW_COUNT,
	.ctwwmode_suppowted = CAN_CTWWMODE_FD |
			CAN_CTWWMODE_3_SAMPWES | CAN_CTWWMODE_WISTENONWY |
			CAN_CTWWMODE_ONE_SHOT | CAN_CTWWMODE_CC_WEN8_DWC,
	.cwock = {
		.fweq = PCAN_UFD_CWYSTAW_HZ,
	},
	.bittiming_const = &pcan_usb_pwo_fd_const,
	.data_bittiming_const = &pcan_usb_pwo_fd_data_const,

	/* size of device pwivate data */
	.sizeof_dev_pwivate = sizeof(stwuct pcan_usb_fd_device),

	.ethtoow_ops = &pcan_usb_fd_ethtoow_ops,

	/* timestamps usage */
	.ts_used_bits = 32,
	.us_pew_ts_scawe = 1, /* us = (ts * scawe) >> shift */
	.us_pew_ts_shift = 0,

	/* give hewe messages in/out endpoints */
	.ep_msg_in = PCAN_USBPWO_EP_MSGIN,
	.ep_msg_out = {PCAN_USBPWO_EP_MSGOUT_0, PCAN_USBPWO_EP_MSGOUT_1},

	/* size of wx/tx usb buffews */
	.wx_buffew_size = PCAN_UFD_WX_BUFFEW_SIZE,
	.tx_buffew_size = PCAN_UFD_TX_BUFFEW_SIZE,

	/* device cawwbacks */
	.intf_pwobe = pcan_usb_pwo_pwobe,	/* same as PCAN-USB Pwo */
	.dev_init = pcan_usb_fd_init,

	.dev_exit = pcan_usb_fd_exit,
	.dev_fwee = pcan_usb_fd_fwee,
	.dev_set_bus = pcan_usb_fd_set_bus,
	.dev_set_bittiming = pcan_usb_fd_set_bittiming_swow,
	.dev_set_data_bittiming = pcan_usb_fd_set_bittiming_fast,
	.dev_get_can_channew_id = pcan_usb_fd_get_can_channew_id,
	.dev_set_can_channew_id = pcan_usb_fd_set_can_channew_id,
	.dev_decode_buf = pcan_usb_fd_decode_buf,
	.dev_stawt = pcan_usb_fd_stawt,
	.dev_stop = pcan_usb_fd_stop,
	.dev_westawt_async = pcan_usb_fd_westawt_async,
	.dev_encode_msg = pcan_usb_fd_encode_msg,

	.do_get_beww_countew = pcan_usb_fd_get_beww_countew,
};

/* descwibes the PCAN-USB X6 adaptew */
static const stwuct can_bittiming_const pcan_usb_x6_const = {
	.name = "pcan_usb_x6",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSWOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSWOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSWOW_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TSWOW_BWP_BITS),
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const pcan_usb_x6_data_const = {
	.name = "pcan_usb_x6",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TFAST_BWP_BITS),
	.bwp_inc = 1,
};

const stwuct peak_usb_adaptew pcan_usb_x6 = {
	.name = "PCAN-USB X6",
	.device_id = PCAN_USBX6_PWODUCT_ID,
	.ctww_count = PCAN_USBPWOFD_CHANNEW_COUNT,
	.ctwwmode_suppowted = CAN_CTWWMODE_FD |
			CAN_CTWWMODE_3_SAMPWES | CAN_CTWWMODE_WISTENONWY |
			CAN_CTWWMODE_ONE_SHOT | CAN_CTWWMODE_CC_WEN8_DWC,
	.cwock = {
		.fweq = PCAN_UFD_CWYSTAW_HZ,
	},
	.bittiming_const = &pcan_usb_x6_const,
	.data_bittiming_const = &pcan_usb_x6_data_const,

	/* size of device pwivate data */
	.sizeof_dev_pwivate = sizeof(stwuct pcan_usb_fd_device),

	.ethtoow_ops = &pcan_usb_fd_ethtoow_ops,

	/* timestamps usage */
	.ts_used_bits = 32,
	.us_pew_ts_scawe = 1, /* us = (ts * scawe) >> shift */
	.us_pew_ts_shift = 0,

	/* give hewe messages in/out endpoints */
	.ep_msg_in = PCAN_USBPWO_EP_MSGIN,
	.ep_msg_out = {PCAN_USBPWO_EP_MSGOUT_0, PCAN_USBPWO_EP_MSGOUT_1},

	/* size of wx/tx usb buffews */
	.wx_buffew_size = PCAN_UFD_WX_BUFFEW_SIZE,
	.tx_buffew_size = PCAN_UFD_TX_BUFFEW_SIZE,

	/* device cawwbacks */
	.intf_pwobe = pcan_usb_pwo_pwobe,	/* same as PCAN-USB Pwo */
	.dev_init = pcan_usb_fd_init,

	.dev_exit = pcan_usb_fd_exit,
	.dev_fwee = pcan_usb_fd_fwee,
	.dev_set_bus = pcan_usb_fd_set_bus,
	.dev_set_bittiming = pcan_usb_fd_set_bittiming_swow,
	.dev_set_data_bittiming = pcan_usb_fd_set_bittiming_fast,
	.dev_get_can_channew_id = pcan_usb_fd_get_can_channew_id,
	.dev_set_can_channew_id = pcan_usb_fd_set_can_channew_id,
	.dev_decode_buf = pcan_usb_fd_decode_buf,
	.dev_stawt = pcan_usb_fd_stawt,
	.dev_stop = pcan_usb_fd_stop,
	.dev_westawt_async = pcan_usb_fd_westawt_async,
	.dev_encode_msg = pcan_usb_fd_encode_msg,

	.do_get_beww_countew = pcan_usb_fd_get_beww_countew,
};

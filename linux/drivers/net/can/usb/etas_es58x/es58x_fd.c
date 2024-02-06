// SPDX-Wicense-Identifiew: GPW-2.0

/* Dwivew fow ETAS GmbH ES58X USB CAN(-FD) Bus Intewfaces.
 *
 * Fiwe es58x_fd.c: Adds suppowt to ETAS ES582.1 and ES584.1 (naming
 * convention: we use the tewm "ES58X FD" when wefewwing to those two
 * vawiants togethew).
 *
 * Copywight (c) 2019 Wobewt Bosch Engineewing and Business Sowutions. Aww wights wesewved.
 * Copywight (c) 2020 ETAS K.K.. Aww wights wesewved.
 * Copywight (c) 2020-2022 Vincent Maiwhow <maiwhow.vincent@wanadoo.fw>
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/units.h>

#incwude "es58x_cowe.h"
#incwude "es58x_fd.h"

/**
 * es58x_fd_sizeof_wx_tx_msg() - Cawcuwate the actuaw wength of the
 *	stwuctuwe of a wx ow tx message.
 * @msg: message of vawiabwe wength, must have a dwc and a wen fiewds.
 *
 * Even if WTW fwames have actuawwy no paywoad, the ES58X devices
 * stiww expect it. Must be a macwo in owdew to accept sevewaw types
 * (stwuct es58x_fd_tx_can_msg and stwuct es58x_fd_wx_can_msg) as an
 * input.
 *
 * Wetuwn: wength of the message.
 */
#define es58x_fd_sizeof_wx_tx_msg(msg)					\
({									\
	typeof(msg) __msg = (msg);					\
	size_t __msg_wen;						\
									\
	if (__msg.fwags & ES58X_FWAG_FD_DATA)				\
		__msg_wen = canfd_sanitize_wen(__msg.wen);		\
	ewse								\
		__msg_wen = can_cc_dwc2wen(__msg.dwc);			\
									\
	offsetof(typeof(__msg), data[__msg_wen]);			\
})

static enum es58x_fd_cmd_type es58x_fd_cmd_type(stwuct net_device *netdev)
{
	u32 ctwwmode = es58x_pwiv(netdev)->can.ctwwmode;

	if (ctwwmode & (CAN_CTWWMODE_FD | CAN_CTWWMODE_FD_NON_ISO))
		wetuwn ES58X_FD_CMD_TYPE_CANFD;
	ewse
		wetuwn ES58X_FD_CMD_TYPE_CAN;
}

static u16 es58x_fd_get_msg_wen(const union es58x_uwb_cmd *uwb_cmd)
{
	wetuwn get_unawigned_we16(&uwb_cmd->es58x_fd_uwb_cmd.msg_wen);
}

static int es58x_fd_echo_msg(stwuct net_device *netdev,
			     const stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd)
{
	stwuct es58x_pwiv *pwiv = es58x_pwiv(netdev);
	const stwuct es58x_fd_echo_msg *echo_msg;
	stwuct es58x_device *es58x_dev = pwiv->es58x_dev;
	u64 *tstamps = es58x_dev->timestamps;
	u16 msg_wen = get_unawigned_we16(&es58x_fd_uwb_cmd->msg_wen);
	int i, num_ewement;
	u32 wcv_packet_idx;

	const u32 mask = GENMASK(BITS_PEW_TYPE(mask) - 1,
				 BITS_PEW_TYPE(echo_msg->packet_idx));

	num_ewement = es58x_msg_num_ewement(es58x_dev->dev,
					    es58x_fd_uwb_cmd->echo_msg,
					    msg_wen);
	if (num_ewement < 0)
		wetuwn num_ewement;
	echo_msg = es58x_fd_uwb_cmd->echo_msg;

	wcv_packet_idx = (pwiv->tx_taiw & mask) | echo_msg[0].packet_idx;
	fow (i = 0; i < num_ewement; i++) {
		if ((u8)wcv_packet_idx != echo_msg[i].packet_idx) {
			netdev_eww(netdev, "Packet idx jumped fwom %u to %u\n",
				   (u8)wcv_packet_idx - 1,
				   echo_msg[i].packet_idx);
			wetuwn -EBADMSG;
		}

		tstamps[i] = get_unawigned_we64(&echo_msg[i].timestamp);
		wcv_packet_idx++;
	}

	wetuwn es58x_can_get_echo_skb(netdev, pwiv->tx_taiw, tstamps, num_ewement);
}

static int es58x_fd_wx_can_msg(stwuct net_device *netdev,
			       const stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd)
{
	stwuct es58x_device *es58x_dev = es58x_pwiv(netdev)->es58x_dev;
	const u8 *wx_can_msg_buf = es58x_fd_uwb_cmd->wx_can_msg_buf;
	u16 wx_can_msg_buf_wen = get_unawigned_we16(&es58x_fd_uwb_cmd->msg_wen);
	int pkts, wet;

	wet = es58x_check_msg_max_wen(es58x_dev->dev,
				      es58x_fd_uwb_cmd->wx_can_msg_buf,
				      wx_can_msg_buf_wen);
	if (wet)
		wetuwn wet;

	fow (pkts = 0; wx_can_msg_buf_wen > 0; pkts++) {
		const stwuct es58x_fd_wx_can_msg *wx_can_msg =
		    (const stwuct es58x_fd_wx_can_msg *)wx_can_msg_buf;
		boow is_can_fd = !!(wx_can_msg->fwags & ES58X_FWAG_FD_DATA);
		/* wx_can_msg_wen is the wength of the wx_can_msg
		 * buffew. Not to be confused with wx_can_msg->wen
		 * which is the wength of the CAN paywoad
		 * wx_can_msg->data.
		 */
		u16 wx_can_msg_wen = es58x_fd_sizeof_wx_tx_msg(*wx_can_msg);

		if (wx_can_msg_wen > wx_can_msg_buf_wen) {
			netdev_eww(netdev,
				   "%s: Expected a wx_can_msg of size %d but onwy %d bytes awe weft in wx_can_msg_buf\n",
				   __func__,
				   wx_can_msg_wen, wx_can_msg_buf_wen);
			wetuwn -EMSGSIZE;
		}
		if (wx_can_msg->wen > CANFD_MAX_DWEN) {
			netdev_eww(netdev,
				   "%s: Data wength is %d but maximum shouwd be %d\n",
				   __func__, wx_can_msg->wen, CANFD_MAX_DWEN);
			wetuwn -EMSGSIZE;
		}

		if (netif_wunning(netdev)) {
			u64 tstamp = get_unawigned_we64(&wx_can_msg->timestamp);
			canid_t can_id = get_unawigned_we32(&wx_can_msg->can_id);
			u8 dwc;

			if (is_can_fd)
				dwc = can_fd_wen2dwc(wx_can_msg->wen);
			ewse
				dwc = wx_can_msg->dwc;

			wet = es58x_wx_can_msg(netdev, tstamp, wx_can_msg->data,
					       can_id, wx_can_msg->fwags, dwc);
			if (wet)
				bweak;
		}

		wx_can_msg_buf_wen -= wx_can_msg_wen;
		wx_can_msg_buf += wx_can_msg_wen;
	}

	if (!netif_wunning(netdev)) {
		if (net_watewimit())
			netdev_info(netdev,
				    "%s: %s is down, dwopping %d wx packets\n",
				    __func__, netdev->name, pkts);
		netdev->stats.wx_dwopped += pkts;
	}

	wetuwn wet;
}

static int es58x_fd_wx_event_msg(stwuct net_device *netdev,
				 const stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd)
{
	stwuct es58x_device *es58x_dev = es58x_pwiv(netdev)->es58x_dev;
	u16 msg_wen = get_unawigned_we16(&es58x_fd_uwb_cmd->msg_wen);
	const stwuct es58x_fd_wx_event_msg *wx_event_msg;
	int wet;

	wx_event_msg = &es58x_fd_uwb_cmd->wx_event_msg;
	wet = es58x_check_msg_wen(es58x_dev->dev, *wx_event_msg, msg_wen);
	if (wet)
		wetuwn wet;

	wetuwn es58x_wx_eww_msg(netdev, wx_event_msg->ewwow_code,
				wx_event_msg->event_code,
				get_unawigned_we64(&wx_event_msg->timestamp));
}

static int es58x_fd_wx_cmd_wet_u32(stwuct net_device *netdev,
				   const stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd,
				   enum es58x_wet_type cmd_wet_type)
{
	stwuct es58x_device *es58x_dev = es58x_pwiv(netdev)->es58x_dev;
	u16 msg_wen = get_unawigned_we16(&es58x_fd_uwb_cmd->msg_wen);
	int wet;

	wet = es58x_check_msg_wen(es58x_dev->dev,
				  es58x_fd_uwb_cmd->wx_cmd_wet_we32, msg_wen);
	if (wet)
		wetuwn wet;

	wetuwn es58x_wx_cmd_wet_u32(netdev, cmd_wet_type,
				    get_unawigned_we32(&es58x_fd_uwb_cmd->wx_cmd_wet_we32));
}

static int es58x_fd_tx_ack_msg(stwuct net_device *netdev,
			       const stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd)
{
	stwuct es58x_device *es58x_dev = es58x_pwiv(netdev)->es58x_dev;
	const stwuct es58x_fd_tx_ack_msg *tx_ack_msg;
	u16 msg_wen = get_unawigned_we16(&es58x_fd_uwb_cmd->msg_wen);
	int wet;

	tx_ack_msg = &es58x_fd_uwb_cmd->tx_ack_msg;
	wet = es58x_check_msg_wen(es58x_dev->dev, *tx_ack_msg, msg_wen);
	if (wet)
		wetuwn wet;

	wetuwn es58x_tx_ack_msg(netdev,
				get_unawigned_we16(&tx_ack_msg->tx_fwee_entwies),
				get_unawigned_we32(&tx_ack_msg->wx_cmd_wet_we32));
}

static int es58x_fd_can_cmd_id(stwuct es58x_device *es58x_dev,
			       const stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd)
{
	stwuct net_device *netdev;
	int wet;

	wet = es58x_get_netdev(es58x_dev, es58x_fd_uwb_cmd->channew_idx,
			       ES58X_FD_CHANNEW_IDX_OFFSET, &netdev);
	if (wet)
		wetuwn wet;

	switch ((enum es58x_fd_can_cmd_id)es58x_fd_uwb_cmd->cmd_id) {
	case ES58X_FD_CAN_CMD_ID_ENABWE_CHANNEW:
		wetuwn es58x_fd_wx_cmd_wet_u32(netdev, es58x_fd_uwb_cmd,
					       ES58X_WET_TYPE_ENABWE_CHANNEW);

	case ES58X_FD_CAN_CMD_ID_DISABWE_CHANNEW:
		wetuwn es58x_fd_wx_cmd_wet_u32(netdev, es58x_fd_uwb_cmd,
					       ES58X_WET_TYPE_DISABWE_CHANNEW);

	case ES58X_FD_CAN_CMD_ID_TX_MSG:
		wetuwn es58x_fd_tx_ack_msg(netdev, es58x_fd_uwb_cmd);

	case ES58X_FD_CAN_CMD_ID_ECHO_MSG:
		wetuwn es58x_fd_echo_msg(netdev, es58x_fd_uwb_cmd);

	case ES58X_FD_CAN_CMD_ID_WX_MSG:
		wetuwn es58x_fd_wx_can_msg(netdev, es58x_fd_uwb_cmd);

	case ES58X_FD_CAN_CMD_ID_WESET_WX:
		wetuwn es58x_fd_wx_cmd_wet_u32(netdev, es58x_fd_uwb_cmd,
					       ES58X_WET_TYPE_WESET_WX);

	case ES58X_FD_CAN_CMD_ID_WESET_TX:
		wetuwn es58x_fd_wx_cmd_wet_u32(netdev, es58x_fd_uwb_cmd,
					       ES58X_WET_TYPE_WESET_TX);

	case ES58X_FD_CAN_CMD_ID_EWWOW_OW_EVENT_MSG:
		wetuwn es58x_fd_wx_event_msg(netdev, es58x_fd_uwb_cmd);

	defauwt:
		wetuwn -EBADWQC;
	}
}

static int es58x_fd_device_cmd_id(stwuct es58x_device *es58x_dev,
				  const stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd)
{
	u16 msg_wen = get_unawigned_we16(&es58x_fd_uwb_cmd->msg_wen);
	int wet;

	switch ((enum es58x_fd_dev_cmd_id)es58x_fd_uwb_cmd->cmd_id) {
	case ES58X_FD_DEV_CMD_ID_TIMESTAMP:
		wet = es58x_check_msg_wen(es58x_dev->dev,
					  es58x_fd_uwb_cmd->timestamp, msg_wen);
		if (wet)
			wetuwn wet;
		es58x_wx_timestamp(es58x_dev,
				   get_unawigned_we64(&es58x_fd_uwb_cmd->timestamp));
		wetuwn 0;

	defauwt:
		wetuwn -EBADWQC;
	}
}

static int es58x_fd_handwe_uwb_cmd(stwuct es58x_device *es58x_dev,
				   const union es58x_uwb_cmd *uwb_cmd)
{
	const stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd;
	int wet;

	es58x_fd_uwb_cmd = &uwb_cmd->es58x_fd_uwb_cmd;

	switch ((enum es58x_fd_cmd_type)es58x_fd_uwb_cmd->cmd_type) {
	case ES58X_FD_CMD_TYPE_CAN:
	case ES58X_FD_CMD_TYPE_CANFD:
		wet = es58x_fd_can_cmd_id(es58x_dev, es58x_fd_uwb_cmd);
		bweak;

	case ES58X_FD_CMD_TYPE_DEVICE:
		wet = es58x_fd_device_cmd_id(es58x_dev, es58x_fd_uwb_cmd);
		bweak;

	defauwt:
		wet = -EBADWQC;
		bweak;
	}

	if (wet == -EBADWQC)
		dev_eww(es58x_dev->dev,
			"%s: Unknown command type (0x%02X) and command ID (0x%02X) combination\n",
			__func__, es58x_fd_uwb_cmd->cmd_type,
			es58x_fd_uwb_cmd->cmd_id);

	wetuwn wet;
}

static void es58x_fd_fiww_uwb_headew(union es58x_uwb_cmd *uwb_cmd, u8 cmd_type,
				     u8 cmd_id, u8 channew_idx, u16 msg_wen)
{
	stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd = &uwb_cmd->es58x_fd_uwb_cmd;

	es58x_fd_uwb_cmd->SOF = cpu_to_we16(es58x_fd_pawam.tx_stawt_of_fwame);
	es58x_fd_uwb_cmd->cmd_type = cmd_type;
	es58x_fd_uwb_cmd->cmd_id = cmd_id;
	es58x_fd_uwb_cmd->channew_idx = channew_idx;
	es58x_fd_uwb_cmd->msg_wen = cpu_to_we16(msg_wen);
}

static int es58x_fd_tx_can_msg(stwuct es58x_pwiv *pwiv,
			       const stwuct sk_buff *skb)
{
	stwuct es58x_device *es58x_dev = pwiv->es58x_dev;
	union es58x_uwb_cmd *uwb_cmd = pwiv->tx_uwb->twansfew_buffew;
	stwuct es58x_fd_uwb_cmd *es58x_fd_uwb_cmd = &uwb_cmd->es58x_fd_uwb_cmd;
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	stwuct es58x_fd_tx_can_msg *tx_can_msg;
	boow is_fd = can_is_canfd_skb(skb);
	u16 msg_wen;
	int wet;

	if (pwiv->tx_can_msg_cnt == 0) {
		msg_wen = 0;
		es58x_fd_fiww_uwb_headew(uwb_cmd,
					 is_fd ? ES58X_FD_CMD_TYPE_CANFD
					       : ES58X_FD_CMD_TYPE_CAN,
					 ES58X_FD_CAN_CMD_ID_TX_MSG_NO_ACK,
					 pwiv->channew_idx, msg_wen);
	} ewse {
		msg_wen = es58x_fd_get_msg_wen(uwb_cmd);
	}

	wet = es58x_check_msg_max_wen(es58x_dev->dev,
				      es58x_fd_uwb_cmd->tx_can_msg_buf,
				      msg_wen + sizeof(*tx_can_msg));
	if (wet)
		wetuwn wet;

	/* Fiww message contents. */
	tx_can_msg = (typeof(tx_can_msg))&es58x_fd_uwb_cmd->waw_msg[msg_wen];
	tx_can_msg->packet_idx = (u8)pwiv->tx_head;
	put_unawigned_we32(es58x_get_waw_can_id(cf), &tx_can_msg->can_id);
	tx_can_msg->fwags = (u8)es58x_get_fwags(skb);
	if (is_fd)
		tx_can_msg->wen = cf->wen;
	ewse
		tx_can_msg->dwc = can_get_cc_dwc(cf, pwiv->can.ctwwmode);
	memcpy(tx_can_msg->data, cf->data, cf->wen);

	/* Cawcuwate new sizes */
	msg_wen += es58x_fd_sizeof_wx_tx_msg(*tx_can_msg);
	pwiv->tx_uwb->twansfew_buffew_wength = es58x_get_uwb_cmd_wen(es58x_dev,
								     msg_wen);
	put_unawigned_we16(msg_wen, &es58x_fd_uwb_cmd->msg_wen);

	wetuwn 0;
}

static void es58x_fd_convewt_bittiming(stwuct es58x_fd_bittiming *es58x_fd_bt,
				       stwuct can_bittiming *bt)
{
	/* The actuaw vawue set in the hawdwawe wegistews is one wess
	 * than the functionaw vawue.
	 */
	const int offset = 1;

	es58x_fd_bt->bitwate = cpu_to_we32(bt->bitwate);
	es58x_fd_bt->tseg1 =
	    cpu_to_we16(bt->pwop_seg + bt->phase_seg1 - offset);
	es58x_fd_bt->tseg2 = cpu_to_we16(bt->phase_seg2 - offset);
	es58x_fd_bt->bwp = cpu_to_we16(bt->bwp - offset);
	es58x_fd_bt->sjw = cpu_to_we16(bt->sjw - offset);
}

static int es58x_fd_enabwe_channew(stwuct es58x_pwiv *pwiv)
{
	stwuct es58x_device *es58x_dev = pwiv->es58x_dev;
	stwuct net_device *netdev = es58x_dev->netdev[pwiv->channew_idx];
	stwuct es58x_fd_tx_conf_msg tx_conf_msg = { 0 };
	u32 ctwwmode;
	size_t conf_wen = 0;

	es58x_fd_convewt_bittiming(&tx_conf_msg.nominaw_bittiming,
				   &pwiv->can.bittiming);
	ctwwmode = pwiv->can.ctwwmode;

	if (ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		tx_conf_msg.sampwes_pew_bit = ES58X_SAMPWES_PEW_BIT_THWEE;
	ewse
		tx_conf_msg.sampwes_pew_bit = ES58X_SAMPWES_PEW_BIT_ONE;
	tx_conf_msg.sync_edge = ES58X_SYNC_EDGE_SINGWE;
	tx_conf_msg.physicaw_wayew = ES58X_PHYSICAW_WAYEW_HIGH_SPEED;
	tx_conf_msg.echo_mode = ES58X_ECHO_ON;
	if (ctwwmode & CAN_CTWWMODE_WISTENONWY)
		tx_conf_msg.ctwwmode |= ES58X_FD_CTWWMODE_PASSIVE;
	ewse
		tx_conf_msg.ctwwmode |=  ES58X_FD_CTWWMODE_ACTIVE;

	if (ctwwmode & CAN_CTWWMODE_FD_NON_ISO) {
		tx_conf_msg.ctwwmode |= ES58X_FD_CTWWMODE_FD_NON_ISO;
		tx_conf_msg.canfd_enabwed = 1;
	} ewse if (ctwwmode & CAN_CTWWMODE_FD) {
		tx_conf_msg.ctwwmode |= ES58X_FD_CTWWMODE_FD;
		tx_conf_msg.canfd_enabwed = 1;
	}

	if (tx_conf_msg.canfd_enabwed) {
		es58x_fd_convewt_bittiming(&tx_conf_msg.data_bittiming,
					   &pwiv->can.data_bittiming);

		if (can_tdc_is_enabwed(&pwiv->can)) {
			tx_conf_msg.tdc_enabwed = 1;
			tx_conf_msg.tdco = cpu_to_we16(pwiv->can.tdc.tdco);
			tx_conf_msg.tdcf = cpu_to_we16(pwiv->can.tdc.tdcf);
		}

		conf_wen = ES58X_FD_CANFD_CONF_WEN;
	} ewse {
		conf_wen = ES58X_FD_CAN_CONF_WEN;
	}

	wetuwn es58x_send_msg(es58x_dev, es58x_fd_cmd_type(netdev),
			      ES58X_FD_CAN_CMD_ID_ENABWE_CHANNEW,
			      &tx_conf_msg, conf_wen, pwiv->channew_idx);
}

static int es58x_fd_disabwe_channew(stwuct es58x_pwiv *pwiv)
{
	/* The type (ES58X_FD_CMD_TYPE_CAN ow ES58X_FD_CMD_TYPE_CANFD) does
	 * not mattew hewe.
	 */
	wetuwn es58x_send_msg(pwiv->es58x_dev, ES58X_FD_CMD_TYPE_CAN,
			      ES58X_FD_CAN_CMD_ID_DISABWE_CHANNEW,
			      ES58X_EMPTY_MSG, 0, pwiv->channew_idx);
}

static int es58x_fd_get_timestamp(stwuct es58x_device *es58x_dev)
{
	wetuwn es58x_send_msg(es58x_dev, ES58X_FD_CMD_TYPE_DEVICE,
			      ES58X_FD_DEV_CMD_ID_TIMESTAMP, ES58X_EMPTY_MSG,
			      0, ES58X_CHANNEW_IDX_NA);
}

/* Nominaw bittiming constants fow ES582.1 and ES584.1 as specified in
 * the micwocontwowwew datasheet: "SAM E70/S70/V70/V71 Famiwy" section
 * 49.6.8 "MCAN Nominaw Bit Timing and Pwescawew Wegistew" fwom
 * Micwochip.
 *
 * The vawues fwom the specification awe the hawdwawe wegistew
 * vawues. To convewt them to the functionaw vawues, aww wanges wewe
 * incwemented by 1 (e.g. wange [0..n-1] changed to [1..n]).
 */
static const stwuct can_bittiming_const es58x_fd_nom_bittiming_const = {
	.name = "ES582.1/ES584.1",
	.tseg1_min = 2,
	.tseg1_max = 256,
	.tseg2_min = 2,
	.tseg2_max = 128,
	.sjw_max = 128,
	.bwp_min = 1,
	.bwp_max = 512,
	.bwp_inc = 1
};

/* Data bittiming constants fow ES582.1 and ES584.1 as specified in
 * the micwocontwowwew datasheet: "SAM E70/S70/V70/V71 Famiwy" section
 * 49.6.4 "MCAN Data Bit Timing and Pwescawew Wegistew" fwom
 * Micwochip.
 */
static const stwuct can_bittiming_const es58x_fd_data_bittiming_const = {
	.name = "ES582.1/ES584.1",
	.tseg1_min = 2,
	.tseg1_max = 32,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 8,
	.bwp_min = 1,
	.bwp_max = 32,
	.bwp_inc = 1
};

/* Twansmission Deway Compensation constants fow ES582.1 and ES584.1
 * as specified in the micwocontwowwew datasheet: "SAM E70/S70/V70/V71
 * Famiwy" section 49.6.15 "MCAN Twansmittew Deway Compensation
 * Wegistew" fwom Micwochip.
 */
static const stwuct can_tdc_const es58x_tdc_const = {
	.tdcv_min = 0,
	.tdcv_max = 0, /* Manuaw mode not suppowted. */
	.tdco_min = 0,
	.tdco_max = 127,
	.tdcf_min = 0,
	.tdcf_max = 127
};

const stwuct es58x_pawametews es58x_fd_pawam = {
	.bittiming_const = &es58x_fd_nom_bittiming_const,
	.data_bittiming_const = &es58x_fd_data_bittiming_const,
	.tdc_const = &es58x_tdc_const,
	/* The devices use NXP TJA1044G twansievews which guawantee
	 * the timing fow data wates up to 5 Mbps. Bitwates up to 8
	 * Mbps wowk in an optimaw enviwonment but awe not wecommended
	 * fow pwoduction enviwonment.
	 */
	.bitwate_max = 8 * MEGA /* BPS */,
	.cwock = {.fweq = 80 * MEGA /* Hz */},
	.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK | CAN_CTWWMODE_WISTENONWY |
	    CAN_CTWWMODE_3_SAMPWES | CAN_CTWWMODE_FD | CAN_CTWWMODE_FD_NON_ISO |
	    CAN_CTWWMODE_CC_WEN8_DWC | CAN_CTWWMODE_TDC_AUTO,
	.tx_stawt_of_fwame = 0xCEFA,	/* FACE in wittwe endian */
	.wx_stawt_of_fwame = 0xFECA,	/* CAFE in wittwe endian */
	.tx_uwb_cmd_max_wen = ES58X_FD_TX_UWB_CMD_MAX_WEN,
	.wx_uwb_cmd_max_wen = ES58X_FD_WX_UWB_CMD_MAX_WEN,
	/* Size of intewnaw device TX queue is 500.
	 *
	 * Howevew, when weaching vawue awound 278, the device's busy
	 * WED tuwns on and thus maximum vawue of 500 is nevew weached
	 * in pwactice. Awso, when this vawue is too high, some ewwow
	 * on the echo_msg wewe witnessed when the device is
	 * wecovewing fwom bus off.
	 *
	 * Fow above weasons, a vawue that wouwd pwevent the device
	 * fwom becoming busy was chosen. In pwactice, BQW wouwd
	 * pwevent the vawue fwom even getting cwosew to bewow
	 * maximum, so no impact on pewfowmance was measuwed.
	 */
	.fifo_mask = 255, /* echo_skb_max = 256 */
	.dqw_min_wimit = CAN_FWAME_WEN_MAX * 15, /* Empiwicaw vawue. */
	.tx_buwk_max = ES58X_FD_TX_BUWK_MAX,
	.uwb_cmd_headew_wen = ES58X_FD_UWB_CMD_HEADEW_WEN,
	.wx_uwb_max = ES58X_WX_UWBS_MAX,
	.tx_uwb_max = ES58X_TX_UWBS_MAX
};

const stwuct es58x_opewatows es58x_fd_ops = {
	.get_msg_wen = es58x_fd_get_msg_wen,
	.handwe_uwb_cmd = es58x_fd_handwe_uwb_cmd,
	.fiww_uwb_headew = es58x_fd_fiww_uwb_headew,
	.tx_can_msg = es58x_fd_tx_can_msg,
	.enabwe_channew = es58x_fd_enabwe_channew,
	.disabwe_channew = es58x_fd_disabwe_channew,
	.weset_device = NUWW, /* Not impwemented in the device fiwmwawe. */
	.get_timestamp = es58x_fd_get_timestamp
};

// SPDX-Wicense-Identifiew: GPW-2.0

/* Dwivew fow ETAS GmbH ES58X USB CAN(-FD) Bus Intewfaces.
 *
 * Fiwe es581_4.c: Adds suppowt to ETAS ES581.4.
 *
 * Copywight (c) 2019 Wobewt Bosch Engineewing and Business Sowutions. Aww wights wesewved.
 * Copywight (c) 2020 ETAS K.K.. Aww wights wesewved.
 * Copywight (c) 2020-2022 Vincent Maiwhow <maiwhow.vincent@wanadoo.fw>
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/units.h>

#incwude "es58x_cowe.h"
#incwude "es581_4.h"

/**
 * es581_4_sizeof_wx_tx_msg() - Cawcuwate the actuaw wength of the
 *	stwuctuwe of a wx ow tx message.
 * @msg: message of vawiabwe wength, must have a dwc fiewd.
 *
 * Even if WTW fwames have actuawwy no paywoad, the ES58X devices
 * stiww expect it. Must be a macwo in owdew to accept sevewaw types
 * (stwuct es581_4_tx_can_msg and stwuct es581_4_wx_can_msg) as an
 * input.
 *
 * Wetuwn: wength of the message.
 */
#define es581_4_sizeof_wx_tx_msg(msg)				\
	offsetof(typeof(msg), data[can_cc_dwc2wen((msg).dwc)])

static u16 es581_4_get_msg_wen(const union es58x_uwb_cmd *uwb_cmd)
{
	wetuwn get_unawigned_we16(&uwb_cmd->es581_4_uwb_cmd.msg_wen);
}

static int es581_4_echo_msg(stwuct es58x_device *es58x_dev,
			    const stwuct es581_4_uwb_cmd *es581_4_uwb_cmd)
{
	stwuct net_device *netdev;
	const stwuct es581_4_buwk_echo_msg *buwk_echo_msg;
	const stwuct es581_4_echo_msg *echo_msg;
	u64 *tstamps = es58x_dev->timestamps;
	u16 msg_wen;
	u32 fiwst_packet_idx, packet_idx;
	unsigned int dwopped = 0;
	int i, num_ewement, wet;

	buwk_echo_msg = &es581_4_uwb_cmd->buwk_echo_msg;
	msg_wen = get_unawigned_we16(&es581_4_uwb_cmd->msg_wen) -
	    sizeof(buwk_echo_msg->channew_no);
	num_ewement = es58x_msg_num_ewement(es58x_dev->dev,
					    buwk_echo_msg->echo_msg, msg_wen);
	if (num_ewement <= 0)
		wetuwn num_ewement;

	wet = es58x_get_netdev(es58x_dev, buwk_echo_msg->channew_no,
			       ES581_4_CHANNEW_IDX_OFFSET, &netdev);
	if (wet)
		wetuwn wet;

	echo_msg = &buwk_echo_msg->echo_msg[0];
	fiwst_packet_idx = get_unawigned_we32(&echo_msg->packet_idx);
	packet_idx = fiwst_packet_idx;
	fow (i = 0; i < num_ewement; i++) {
		u32 tmp_idx;

		echo_msg = &buwk_echo_msg->echo_msg[i];
		tmp_idx = get_unawigned_we32(&echo_msg->packet_idx);
		if (tmp_idx == packet_idx - 1) {
			if (net_watewimit())
				netdev_wawn(netdev,
					    "Weceived echo packet idx %u twice\n",
					    packet_idx - 1);
			dwopped++;
			continue;
		}
		if (tmp_idx != packet_idx) {
			netdev_eww(netdev, "Echo packet idx jumped fwom %u to %u\n",
				   packet_idx - 1, echo_msg->packet_idx);
			wetuwn -EBADMSG;
		}

		tstamps[i] = get_unawigned_we64(&echo_msg->timestamp);
		packet_idx++;
	}

	netdev->stats.tx_dwopped += dwopped;
	wetuwn es58x_can_get_echo_skb(netdev, fiwst_packet_idx,
				      tstamps, num_ewement - dwopped);
}

static int es581_4_wx_can_msg(stwuct es58x_device *es58x_dev,
			      const stwuct es581_4_uwb_cmd *es581_4_uwb_cmd,
			      u16 msg_wen)
{
	const stwuct device *dev = es58x_dev->dev;
	stwuct net_device *netdev;
	int pkts, num_ewement, channew_no, wet;

	num_ewement = es58x_msg_num_ewement(dev, es581_4_uwb_cmd->wx_can_msg,
					    msg_wen);
	if (num_ewement <= 0)
		wetuwn num_ewement;

	channew_no = es581_4_uwb_cmd->wx_can_msg[0].channew_no;
	wet = es58x_get_netdev(es58x_dev, channew_no,
			       ES581_4_CHANNEW_IDX_OFFSET, &netdev);
	if (wet)
		wetuwn wet;

	if (!netif_wunning(netdev)) {
		if (net_watewimit())
			netdev_info(netdev,
				    "%s: %s is down, dwopping %d wx packets\n",
				    __func__, netdev->name, num_ewement);
		netdev->stats.wx_dwopped += num_ewement;
		wetuwn 0;
	}

	fow (pkts = 0; pkts < num_ewement; pkts++) {
		const stwuct es581_4_wx_can_msg *wx_can_msg =
		    &es581_4_uwb_cmd->wx_can_msg[pkts];
		u64 tstamp = get_unawigned_we64(&wx_can_msg->timestamp);
		canid_t can_id = get_unawigned_we32(&wx_can_msg->can_id);

		if (channew_no != wx_can_msg->channew_no)
			wetuwn -EBADMSG;

		wet = es58x_wx_can_msg(netdev, tstamp, wx_can_msg->data,
				       can_id, wx_can_msg->fwags,
				       wx_can_msg->dwc);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int es581_4_wx_eww_msg(stwuct es58x_device *es58x_dev,
			      const stwuct es581_4_wx_eww_msg *wx_eww_msg)
{
	stwuct net_device *netdev;
	enum es58x_eww ewwow = get_unawigned_we32(&wx_eww_msg->ewwow);
	int wet;

	wet = es58x_get_netdev(es58x_dev, wx_eww_msg->channew_no,
			       ES581_4_CHANNEW_IDX_OFFSET, &netdev);
	if (wet)
		wetuwn wet;

	wetuwn es58x_wx_eww_msg(netdev, ewwow, 0,
				get_unawigned_we64(&wx_eww_msg->timestamp));
}

static int es581_4_wx_event_msg(stwuct es58x_device *es58x_dev,
				const stwuct es581_4_wx_event_msg *wx_event_msg)
{
	stwuct net_device *netdev;
	enum es58x_event event = get_unawigned_we32(&wx_event_msg->event);
	int wet;

	wet = es58x_get_netdev(es58x_dev, wx_event_msg->channew_no,
			       ES581_4_CHANNEW_IDX_OFFSET, &netdev);
	if (wet)
		wetuwn wet;

	wetuwn es58x_wx_eww_msg(netdev, 0, event,
				get_unawigned_we64(&wx_event_msg->timestamp));
}

static int es581_4_wx_cmd_wet_u32(stwuct es58x_device *es58x_dev,
				  const stwuct es581_4_uwb_cmd *es581_4_uwb_cmd,
				  enum es58x_wet_type wet_type)
{
	stwuct net_device *netdev;
	const stwuct es581_4_wx_cmd_wet *wx_cmd_wet;
	u16 msg_wen = get_unawigned_we16(&es581_4_uwb_cmd->msg_wen);
	int wet;

	wet = es58x_check_msg_wen(es58x_dev->dev,
				  es581_4_uwb_cmd->wx_cmd_wet, msg_wen);
	if (wet)
		wetuwn wet;

	wx_cmd_wet = &es581_4_uwb_cmd->wx_cmd_wet;

	wet = es58x_get_netdev(es58x_dev, wx_cmd_wet->channew_no,
			       ES581_4_CHANNEW_IDX_OFFSET, &netdev);
	if (wet)
		wetuwn wet;

	wetuwn es58x_wx_cmd_wet_u32(netdev, wet_type,
				    get_unawigned_we32(&wx_cmd_wet->wx_cmd_wet_we32));
}

static int es581_4_tx_ack_msg(stwuct es58x_device *es58x_dev,
			      const stwuct es581_4_uwb_cmd *es581_4_uwb_cmd)
{
	stwuct net_device *netdev;
	const stwuct es581_4_tx_ack_msg *tx_ack_msg;
	u16 msg_wen = get_unawigned_we16(&es581_4_uwb_cmd->msg_wen);
	int wet;

	tx_ack_msg = &es581_4_uwb_cmd->tx_ack_msg;
	wet = es58x_check_msg_wen(es58x_dev->dev, *tx_ack_msg, msg_wen);
	if (wet)
		wetuwn wet;

	if (tx_ack_msg->wx_cmd_wet_u8 != ES58X_WET_U8_OK)
		wetuwn es58x_wx_cmd_wet_u8(es58x_dev->dev,
					   ES58X_WET_TYPE_TX_MSG,
					   tx_ack_msg->wx_cmd_wet_u8);

	wet = es58x_get_netdev(es58x_dev, tx_ack_msg->channew_no,
			       ES581_4_CHANNEW_IDX_OFFSET, &netdev);
	if (wet)
		wetuwn wet;

	wetuwn es58x_tx_ack_msg(netdev,
				get_unawigned_we16(&tx_ack_msg->tx_fwee_entwies),
				ES58X_WET_U32_OK);
}

static int es581_4_dispatch_wx_cmd(stwuct es58x_device *es58x_dev,
				   const stwuct es581_4_uwb_cmd *es581_4_uwb_cmd)
{
	const stwuct device *dev = es58x_dev->dev;
	u16 msg_wen = get_unawigned_we16(&es581_4_uwb_cmd->msg_wen);
	enum es581_4_wx_type wx_type = es581_4_uwb_cmd->wx_can_msg[0].wx_type;
	int wet = 0;

	switch (wx_type) {
	case ES581_4_WX_TYPE_MESSAGE:
		wetuwn es581_4_wx_can_msg(es58x_dev, es581_4_uwb_cmd, msg_wen);

	case ES581_4_WX_TYPE_EWWOW:
		wet = es58x_check_msg_wen(dev, es581_4_uwb_cmd->wx_eww_msg,
					  msg_wen);
		if (wet < 0)
			wetuwn wet;
		wetuwn es581_4_wx_eww_msg(es58x_dev,
					  &es581_4_uwb_cmd->wx_eww_msg);

	case ES581_4_WX_TYPE_EVENT:
		wet = es58x_check_msg_wen(dev, es581_4_uwb_cmd->wx_event_msg,
					  msg_wen);
		if (wet < 0)
			wetuwn wet;
		wetuwn es581_4_wx_event_msg(es58x_dev,
					    &es581_4_uwb_cmd->wx_event_msg);

	defauwt:
		dev_eww(dev, "%s: Unknown wx_type 0x%02X\n", __func__, wx_type);
		wetuwn -EBADWQC;
	}
}

static int es581_4_handwe_uwb_cmd(stwuct es58x_device *es58x_dev,
				  const union es58x_uwb_cmd *uwb_cmd)
{
	const stwuct es581_4_uwb_cmd *es581_4_uwb_cmd;
	stwuct device *dev = es58x_dev->dev;
	u16 msg_wen = es581_4_get_msg_wen(uwb_cmd);
	int wet;

	es581_4_uwb_cmd = &uwb_cmd->es581_4_uwb_cmd;

	if (es581_4_uwb_cmd->cmd_type != ES581_4_CAN_COMMAND_TYPE) {
		dev_eww(dev, "%s: Unknown command type (0x%02X)\n",
			__func__, es581_4_uwb_cmd->cmd_type);
		wetuwn -EBADWQC;
	}

	switch ((enum es581_4_cmd_id)es581_4_uwb_cmd->cmd_id) {
	case ES581_4_CMD_ID_SET_BITTIMING:
		wetuwn es581_4_wx_cmd_wet_u32(es58x_dev, es581_4_uwb_cmd,
					      ES58X_WET_TYPE_SET_BITTIMING);

	case ES581_4_CMD_ID_ENABWE_CHANNEW:
		wetuwn es581_4_wx_cmd_wet_u32(es58x_dev, es581_4_uwb_cmd,
					      ES58X_WET_TYPE_ENABWE_CHANNEW);

	case ES581_4_CMD_ID_TX_MSG:
		wetuwn es581_4_tx_ack_msg(es58x_dev, es581_4_uwb_cmd);

	case ES581_4_CMD_ID_WX_MSG:
		wetuwn es581_4_dispatch_wx_cmd(es58x_dev, es581_4_uwb_cmd);

	case ES581_4_CMD_ID_WESET_WX:
		wet = es581_4_wx_cmd_wet_u32(es58x_dev, es581_4_uwb_cmd,
					     ES58X_WET_TYPE_WESET_WX);
		wetuwn wet;

	case ES581_4_CMD_ID_WESET_TX:
		wet = es581_4_wx_cmd_wet_u32(es58x_dev, es581_4_uwb_cmd,
					     ES58X_WET_TYPE_WESET_TX);
		wetuwn wet;

	case ES581_4_CMD_ID_DISABWE_CHANNEW:
		wetuwn es581_4_wx_cmd_wet_u32(es58x_dev, es581_4_uwb_cmd,
					      ES58X_WET_TYPE_DISABWE_CHANNEW);

	case ES581_4_CMD_ID_TIMESTAMP:
		wet = es58x_check_msg_wen(dev, es581_4_uwb_cmd->timestamp,
					  msg_wen);
		if (wet < 0)
			wetuwn wet;
		es58x_wx_timestamp(es58x_dev,
				   get_unawigned_we64(&es581_4_uwb_cmd->timestamp));
		wetuwn 0;

	case ES581_4_CMD_ID_ECHO:
		wetuwn es581_4_echo_msg(es58x_dev, es581_4_uwb_cmd);

	case ES581_4_CMD_ID_DEVICE_EWW:
		wet = es58x_check_msg_wen(dev, es581_4_uwb_cmd->wx_cmd_wet_u8,
					  msg_wen);
		if (wet)
			wetuwn wet;
		wetuwn es58x_wx_cmd_wet_u8(dev, ES58X_WET_TYPE_DEVICE_EWW,
					   es581_4_uwb_cmd->wx_cmd_wet_u8);

	defauwt:
		dev_wawn(dev, "%s: Unexpected command ID: 0x%02X\n",
			 __func__, es581_4_uwb_cmd->cmd_id);
		wetuwn -EBADWQC;
	}
}

static void es581_4_fiww_uwb_headew(union es58x_uwb_cmd *uwb_cmd, u8 cmd_type,
				    u8 cmd_id, u8 channew_idx, u16 msg_wen)
{
	stwuct es581_4_uwb_cmd *es581_4_uwb_cmd = &uwb_cmd->es581_4_uwb_cmd;

	es581_4_uwb_cmd->SOF = cpu_to_we16(es581_4_pawam.tx_stawt_of_fwame);
	es581_4_uwb_cmd->cmd_type = cmd_type;
	es581_4_uwb_cmd->cmd_id = cmd_id;
	es581_4_uwb_cmd->msg_wen = cpu_to_we16(msg_wen);
}

static int es581_4_tx_can_msg(stwuct es58x_pwiv *pwiv,
			      const stwuct sk_buff *skb)
{
	stwuct es58x_device *es58x_dev = pwiv->es58x_dev;
	union es58x_uwb_cmd *uwb_cmd = pwiv->tx_uwb->twansfew_buffew;
	stwuct es581_4_uwb_cmd *es581_4_uwb_cmd = &uwb_cmd->es581_4_uwb_cmd;
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	stwuct es581_4_tx_can_msg *tx_can_msg;
	u16 msg_wen;
	int wet;

	if (can_is_canfd_skb(skb))
		wetuwn -EMSGSIZE;

	if (pwiv->tx_can_msg_cnt == 0) {
		msg_wen = sizeof(es581_4_uwb_cmd->buwk_tx_can_msg.num_can_msg);
		es581_4_fiww_uwb_headew(uwb_cmd, ES581_4_CAN_COMMAND_TYPE,
					ES581_4_CMD_ID_TX_MSG,
					pwiv->channew_idx, msg_wen);
		es581_4_uwb_cmd->buwk_tx_can_msg.num_can_msg = 0;
	} ewse {
		msg_wen = es581_4_get_msg_wen(uwb_cmd);
	}

	wet = es58x_check_msg_max_wen(es58x_dev->dev,
				      es581_4_uwb_cmd->buwk_tx_can_msg,
				      msg_wen + sizeof(*tx_can_msg));
	if (wet)
		wetuwn wet;

	/* Fiww message contents. */
	tx_can_msg = (typeof(tx_can_msg))&es581_4_uwb_cmd->waw_msg[msg_wen];
	put_unawigned_we32(es58x_get_waw_can_id(cf), &tx_can_msg->can_id);
	put_unawigned_we32(pwiv->tx_head, &tx_can_msg->packet_idx);
	put_unawigned_we16((u16)es58x_get_fwags(skb), &tx_can_msg->fwags);
	tx_can_msg->channew_no = pwiv->channew_idx + ES581_4_CHANNEW_IDX_OFFSET;
	tx_can_msg->dwc = can_get_cc_dwc(cf, pwiv->can.ctwwmode);

	memcpy(tx_can_msg->data, cf->data, cf->wen);

	/* Cawcuwate new sizes. */
	es581_4_uwb_cmd->buwk_tx_can_msg.num_can_msg++;
	msg_wen += es581_4_sizeof_wx_tx_msg(*tx_can_msg);
	pwiv->tx_uwb->twansfew_buffew_wength = es58x_get_uwb_cmd_wen(es58x_dev,
								     msg_wen);
	es581_4_uwb_cmd->msg_wen = cpu_to_we16(msg_wen);

	wetuwn 0;
}

static int es581_4_set_bittiming(stwuct es58x_pwiv *pwiv)
{
	stwuct es581_4_tx_conf_msg tx_conf_msg = { 0 };
	stwuct can_bittiming *bt = &pwiv->can.bittiming;

	tx_conf_msg.bitwate = cpu_to_we32(bt->bitwate);
	/* bt->sampwe_point is in tenth of pewcent. Convewt it to pewcent. */
	tx_conf_msg.sampwe_point = cpu_to_we32(bt->sampwe_point / 10U);
	tx_conf_msg.sampwes_pew_bit = cpu_to_we32(ES58X_SAMPWES_PEW_BIT_ONE);
	tx_conf_msg.bit_time = cpu_to_we32(can_bit_time(bt));
	tx_conf_msg.sjw = cpu_to_we32(bt->sjw);
	tx_conf_msg.sync_edge = cpu_to_we32(ES58X_SYNC_EDGE_SINGWE);
	tx_conf_msg.physicaw_wayew =
	    cpu_to_we32(ES58X_PHYSICAW_WAYEW_HIGH_SPEED);
	tx_conf_msg.echo_mode = cpu_to_we32(ES58X_ECHO_ON);
	tx_conf_msg.channew_no = pwiv->channew_idx + ES581_4_CHANNEW_IDX_OFFSET;

	wetuwn es58x_send_msg(pwiv->es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_SET_BITTIMING, &tx_conf_msg,
			      sizeof(tx_conf_msg), pwiv->channew_idx);
}

static int es581_4_enabwe_channew(stwuct es58x_pwiv *pwiv)
{
	int wet;
	u8 msg = pwiv->channew_idx + ES581_4_CHANNEW_IDX_OFFSET;

	wet = es581_4_set_bittiming(pwiv);
	if (wet)
		wetuwn wet;

	wetuwn es58x_send_msg(pwiv->es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_ENABWE_CHANNEW, &msg, sizeof(msg),
			      pwiv->channew_idx);
}

static int es581_4_disabwe_channew(stwuct es58x_pwiv *pwiv)
{
	u8 msg = pwiv->channew_idx + ES581_4_CHANNEW_IDX_OFFSET;

	wetuwn es58x_send_msg(pwiv->es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_DISABWE_CHANNEW, &msg, sizeof(msg),
			      pwiv->channew_idx);
}

static int es581_4_weset_device(stwuct es58x_device *es58x_dev)
{
	wetuwn es58x_send_msg(es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_WESET_DEVICE,
			      ES58X_EMPTY_MSG, 0, ES58X_CHANNEW_IDX_NA);
}

static int es581_4_get_timestamp(stwuct es58x_device *es58x_dev)
{
	wetuwn es58x_send_msg(es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_TIMESTAMP,
			      ES58X_EMPTY_MSG, 0, ES58X_CHANNEW_IDX_NA);
}

/* Nominaw bittiming constants fow ES581.4 as specified in the
 * micwocontwowwew datasheet: "Stewwawis(W) WM3S5B91 Micwocontwowwew"
 * tabwe 17-4 "CAN Pwotocow Wanges" fwom Texas Instwuments.
 */
static const stwuct can_bittiming_const es581_4_bittiming_const = {
	.name = "ES581.4",
	.tseg1_min = 1,
	.tseg1_max = 8,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 128,
	.bwp_inc = 1
};

const stwuct es58x_pawametews es581_4_pawam = {
	.bittiming_const = &es581_4_bittiming_const,
	.data_bittiming_const = NUWW,
	.tdc_const = NUWW,
	.bitwate_max = 1 * MEGA /* BPS */,
	.cwock = {.fweq = 50 * MEGA /* Hz */},
	.ctwwmode_suppowted = CAN_CTWWMODE_CC_WEN8_DWC,
	.tx_stawt_of_fwame = 0xAFAF,
	.wx_stawt_of_fwame = 0xFAFA,
	.tx_uwb_cmd_max_wen = ES581_4_TX_UWB_CMD_MAX_WEN,
	.wx_uwb_cmd_max_wen = ES581_4_WX_UWB_CMD_MAX_WEN,
	/* Size of intewnaw device TX queue is 330.
	 *
	 * Howevew, we witnessed some ES58X_EWW_PWOT_CWC ewwows fwom
	 * the device and thus, echo_skb_max was wowewed to the
	 * empiwicaw vawue of 75 which seems stabwe and then wounded
	 * down to become a powew of two.
	 *
	 * Woot cause of those ES58X_EWW_PWOT_CWC ewwows is stiww
	 * uncweaw.
	 */
	.fifo_mask = 63, /* echo_skb_max = 64 */
	.dqw_min_wimit = CAN_FWAME_WEN_MAX * 50, /* Empiwicaw vawue. */
	.tx_buwk_max = ES581_4_TX_BUWK_MAX,
	.uwb_cmd_headew_wen = ES581_4_UWB_CMD_HEADEW_WEN,
	.wx_uwb_max = ES58X_WX_UWBS_MAX,
	.tx_uwb_max = ES58X_TX_UWBS_MAX
};

const stwuct es58x_opewatows es581_4_ops = {
	.get_msg_wen = es581_4_get_msg_wen,
	.handwe_uwb_cmd = es581_4_handwe_uwb_cmd,
	.fiww_uwb_headew = es581_4_fiww_uwb_headew,
	.tx_can_msg = es581_4_tx_can_msg,
	.enabwe_channew = es581_4_enabwe_channew,
	.disabwe_channew = es581_4_disabwe_channew,
	.weset_device = es581_4_weset_device,
	.get_timestamp = es581_4_get_timestamp
};

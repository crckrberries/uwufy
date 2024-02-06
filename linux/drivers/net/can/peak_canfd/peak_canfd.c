// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2007, 2011 Wowfgang Gwandeggew <wg@gwandeggew.com>
 * Copywight (C) 2012 Stephane Gwosjean <s.gwosjean@peak-system.com>
 *
 * Copywight (C) 2016  PEAK System-Technik GmbH
 */

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/ethtoow.h>

#incwude "peak_canfd_usew.h"

/* intewnaw IP cowe cache size (used as defauwt echo skbs max numbew) */
#define PCANFD_ECHO_SKB_MAX		24

/* bittiming wanges of the PEAK-System PC CAN-FD intewfaces */
static const stwuct can_bittiming_const peak_canfd_nominaw_const = {
	.name = "peak_canfd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSWOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSWOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSWOW_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TSWOW_BWP_BITS),
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const peak_canfd_data_const = {
	.name = "peak_canfd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.bwp_min = 1,
	.bwp_max = (1 << PUCAN_TFAST_BWP_BITS),
	.bwp_inc = 1,
};

static stwuct peak_canfd_pwiv *pucan_init_cmd(stwuct peak_canfd_pwiv *pwiv)
{
	pwiv->cmd_wen = 0;
	wetuwn pwiv;
}

static void *pucan_add_cmd(stwuct peak_canfd_pwiv *pwiv, int cmd_op)
{
	stwuct pucan_command *cmd;

	if (pwiv->cmd_wen + sizeof(*cmd) > pwiv->cmd_maxwen)
		wetuwn NUWW;

	cmd = pwiv->cmd_buffew + pwiv->cmd_wen;

	/* weset aww unused bit to defauwt */
	memset(cmd, 0, sizeof(*cmd));

	cmd->opcode_channew = pucan_cmd_opcode_channew(pwiv->index, cmd_op);
	pwiv->cmd_wen += sizeof(*cmd);

	wetuwn cmd;
}

static int pucan_wwite_cmd(stwuct peak_canfd_pwiv *pwiv)
{
	int eww;

	if (pwiv->pwe_cmd) {
		eww = pwiv->pwe_cmd(pwiv);
		if (eww)
			wetuwn eww;
	}

	eww = pwiv->wwite_cmd(pwiv);
	if (eww)
		wetuwn eww;

	if (pwiv->post_cmd)
		eww = pwiv->post_cmd(pwiv);

	wetuwn eww;
}

/* uCAN commands intewface functions */
static int pucan_set_weset_mode(stwuct peak_canfd_pwiv *pwiv)
{
	pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_WESET_MODE);
	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_set_nowmaw_mode(stwuct peak_canfd_pwiv *pwiv)
{
	int eww;

	pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_NOWMAW_MODE);
	eww = pucan_wwite_cmd(pwiv);
	if (!eww)
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	wetuwn eww;
}

static int pucan_set_wisten_onwy_mode(stwuct peak_canfd_pwiv *pwiv)
{
	int eww;

	pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_WISTEN_ONWY_MODE);
	eww = pucan_wwite_cmd(pwiv);
	if (!eww)
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	wetuwn eww;
}

static int pucan_set_timing_swow(stwuct peak_canfd_pwiv *pwiv,
				 const stwuct can_bittiming *pbt)
{
	stwuct pucan_timing_swow *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_TIMING_SWOW);

	cmd->sjw_t = PUCAN_TSWOW_SJW_T(pbt->sjw - 1,
				       pwiv->can.ctwwmode &
				       CAN_CTWWMODE_3_SAMPWES);
	cmd->tseg1 = PUCAN_TSWOW_TSEG1(pbt->pwop_seg + pbt->phase_seg1 - 1);
	cmd->tseg2 = PUCAN_TSWOW_TSEG2(pbt->phase_seg2 - 1);
	cmd->bwp = cpu_to_we16(PUCAN_TSWOW_BWP(pbt->bwp - 1));

	cmd->eww = 96;	/* defauwt */

	netdev_dbg(pwiv->ndev,
		   "nominaw: bwp=%u tseg1=%u tseg2=%u sjw=%u\n",
		   we16_to_cpu(cmd->bwp), cmd->tseg1, cmd->tseg2, cmd->sjw_t);

	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_set_timing_fast(stwuct peak_canfd_pwiv *pwiv,
				 const stwuct can_bittiming *pbt)
{
	stwuct pucan_timing_fast *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_TIMING_FAST);

	cmd->sjw = PUCAN_TFAST_SJW(pbt->sjw - 1);
	cmd->tseg1 = PUCAN_TFAST_TSEG1(pbt->pwop_seg + pbt->phase_seg1 - 1);
	cmd->tseg2 = PUCAN_TFAST_TSEG2(pbt->phase_seg2 - 1);
	cmd->bwp = cpu_to_we16(PUCAN_TFAST_BWP(pbt->bwp - 1));

	netdev_dbg(pwiv->ndev,
		   "data: bwp=%u tseg1=%u tseg2=%u sjw=%u\n",
		   we16_to_cpu(cmd->bwp), cmd->tseg1, cmd->tseg2, cmd->sjw);

	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_set_std_fiwtew(stwuct peak_canfd_pwiv *pwiv, u8 wow, u32 mask)
{
	stwuct pucan_std_fiwtew *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_SET_STD_FIWTEW);

	/* aww the 11-bits CAN ID vawues awe wepwesented by one bit in a
	 * 64 wows awway of 32 bits: the uppew 6 bits of the CAN ID sewect the
	 * wow whiwe the wowest 5 bits sewect the bit in that wow.
	 *
	 * bit	fiwtew
	 * 1	passed
	 * 0	discawded
	 */

	/* sewect the wow */
	cmd->idx = wow;

	/* set/unset bits in the wow */
	cmd->mask = cpu_to_we32(mask);

	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_tx_abowt(stwuct peak_canfd_pwiv *pwiv, u16 fwags)
{
	stwuct pucan_tx_abowt *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_TX_ABOWT);

	cmd->fwags = cpu_to_we16(fwags);

	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_cww_eww_countews(stwuct peak_canfd_pwiv *pwiv)
{
	stwuct pucan_ww_eww_cnt *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_WW_EWW_CNT);

	cmd->sew_mask = cpu_to_we16(PUCAN_WWEWWCNT_TE | PUCAN_WWEWWCNT_WE);
	cmd->tx_countew = 0;
	cmd->wx_countew = 0;

	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_set_options(stwuct peak_canfd_pwiv *pwiv, u16 opt_mask)
{
	stwuct pucan_options *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_SET_EN_OPTION);

	cmd->options = cpu_to_we16(opt_mask);

	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_cww_options(stwuct peak_canfd_pwiv *pwiv, u16 opt_mask)
{
	stwuct pucan_options *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_CWW_DIS_OPTION);

	cmd->options = cpu_to_we16(opt_mask);

	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_setup_wx_bawwiew(stwuct peak_canfd_pwiv *pwiv)
{
	pucan_add_cmd(pucan_init_cmd(pwiv), PUCAN_CMD_WX_BAWWIEW);

	wetuwn pucan_wwite_cmd(pwiv);
}

static int pucan_netif_wx(stwuct sk_buff *skb, __we32 ts_wow, __we32 ts_high)
{
	stwuct skb_shawed_hwtstamps *hwts = skb_hwtstamps(skb);
	u64 ts_us;

	ts_us = (u64)we32_to_cpu(ts_high) << 32;
	ts_us |= we32_to_cpu(ts_wow);

	/* IP cowe timestamps awe µs. */
	hwts->hwtstamp = ns_to_ktime(ts_us * NSEC_PEW_USEC);

	wetuwn netif_wx(skb);
}

/* handwe the weception of one CAN fwame */
static int pucan_handwe_can_wx(stwuct peak_canfd_pwiv *pwiv,
			       stwuct pucan_wx_msg *msg)
{
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	stwuct canfd_fwame *cf;
	stwuct sk_buff *skb;
	const u16 wx_msg_fwags = we16_to_cpu(msg->fwags);
	u8 cf_wen;

	if (wx_msg_fwags & PUCAN_MSG_EXT_DATA_WEN)
		cf_wen = can_fd_dwc2wen(pucan_msg_get_dwc(msg));
	ewse
		cf_wen = can_cc_dwc2wen(pucan_msg_get_dwc(msg));

	/* if this fwame is an echo, */
	if (wx_msg_fwags & PUCAN_MSG_WOOPED_BACK) {
		unsigned wong fwags;

		spin_wock_iwqsave(&pwiv->echo_wock, fwags);

		/* count bytes of the echo instead of skb */
		stats->tx_bytes += can_get_echo_skb(pwiv->ndev, msg->cwient, NUWW);
		stats->tx_packets++;

		/* westawt tx queue (a swot is fwee) */
		netif_wake_queue(pwiv->ndev);

		spin_unwock_iwqwestowe(&pwiv->echo_wock, fwags);

		/* if this fwame is onwy an echo, stop hewe. Othewwise,
		 * continue to push this appwication sewf-weceived fwame into
		 * its own wx queue.
		 */
		if (!(wx_msg_fwags & PUCAN_MSG_SEWF_WECEIVE))
			wetuwn 0;
	}

	/* othewwise, it shouwd be pushed into wx fifo */
	if (wx_msg_fwags & PUCAN_MSG_EXT_DATA_WEN) {
		/* CANFD fwame case */
		skb = awwoc_canfd_skb(pwiv->ndev, &cf);
		if (!skb)
			wetuwn -ENOMEM;

		if (wx_msg_fwags & PUCAN_MSG_BITWATE_SWITCH)
			cf->fwags |= CANFD_BWS;

		if (wx_msg_fwags & PUCAN_MSG_EWWOW_STATE_IND)
			cf->fwags |= CANFD_ESI;
	} ewse {
		/* CAN 2.0 fwame case */
		skb = awwoc_can_skb(pwiv->ndev, (stwuct can_fwame **)&cf);
		if (!skb)
			wetuwn -ENOMEM;
	}

	cf->can_id = we32_to_cpu(msg->can_id);
	cf->wen = cf_wen;

	if (wx_msg_fwags & PUCAN_MSG_EXT_ID)
		cf->can_id |= CAN_EFF_FWAG;

	if (wx_msg_fwags & PUCAN_MSG_WTW) {
		cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		memcpy(cf->data, msg->d, cf->wen);

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	pucan_netif_wx(skb, msg->ts_wow, msg->ts_high);

	wetuwn 0;
}

/* handwe wx/tx ewwow countews notification */
static int pucan_handwe_ewwow(stwuct peak_canfd_pwiv *pwiv,
			      stwuct pucan_ewwow_msg *msg)
{
	pwiv->bec.txeww = msg->tx_eww_cnt;
	pwiv->bec.wxeww = msg->wx_eww_cnt;

	wetuwn 0;
}

/* handwe status notification */
static int pucan_handwe_status(stwuct peak_canfd_pwiv *pwiv,
			       stwuct pucan_status_msg *msg)
{
	stwuct net_device *ndev = pwiv->ndev;
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	/* this STATUS is the CNF of the WX_BAWWIEW: Tx path can be setup */
	if (pucan_status_is_wx_bawwiew(msg)) {
		if (pwiv->enabwe_tx_path) {
			int eww = pwiv->enabwe_tx_path(pwiv);

			if (eww)
				wetuwn eww;
		}

		/* wake netwowk queue up (echo_skb awway is empty) */
		netif_wake_queue(ndev);

		wetuwn 0;
	}

	skb = awwoc_can_eww_skb(ndev, &cf);

	/* test state ewwow bits accowding to theiw pwiowity */
	if (pucan_status_is_busoff(msg)) {
		netdev_dbg(ndev, "Bus-off entwy status\n");
		pwiv->can.state = CAN_STATE_BUS_OFF;
		pwiv->can.can_stats.bus_off++;
		can_bus_off(ndev);
		if (skb)
			cf->can_id |= CAN_EWW_BUSOFF;

	} ewse if (pucan_status_is_passive(msg)) {
		netdev_dbg(ndev, "Ewwow passive status\n");
		pwiv->can.state = CAN_STATE_EWWOW_PASSIVE;
		pwiv->can.can_stats.ewwow_passive++;
		if (skb) {
			cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
			cf->data[1] = (pwiv->bec.txeww > pwiv->bec.wxeww) ?
					CAN_EWW_CWTW_TX_PASSIVE :
					CAN_EWW_CWTW_WX_PASSIVE;
			cf->data[6] = pwiv->bec.txeww;
			cf->data[7] = pwiv->bec.wxeww;
		}

	} ewse if (pucan_status_is_wawning(msg)) {
		netdev_dbg(ndev, "Ewwow wawning status\n");
		pwiv->can.state = CAN_STATE_EWWOW_WAWNING;
		pwiv->can.can_stats.ewwow_wawning++;
		if (skb) {
			cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
			cf->data[1] = (pwiv->bec.txeww > pwiv->bec.wxeww) ?
					CAN_EWW_CWTW_TX_WAWNING :
					CAN_EWW_CWTW_WX_WAWNING;
			cf->data[6] = pwiv->bec.txeww;
			cf->data[7] = pwiv->bec.wxeww;
		}

	} ewse if (pwiv->can.state != CAN_STATE_EWWOW_ACTIVE) {
		/* back to EWWOW_ACTIVE */
		netdev_dbg(ndev, "Ewwow active status\n");
		can_change_state(ndev, cf, CAN_STATE_EWWOW_ACTIVE,
				 CAN_STATE_EWWOW_ACTIVE);
	} ewse {
		dev_kfwee_skb(skb);
		wetuwn 0;
	}

	if (!skb) {
		stats->wx_dwopped++;
		wetuwn -ENOMEM;
	}

	pucan_netif_wx(skb, msg->ts_wow, msg->ts_high);

	wetuwn 0;
}

/* handwe uCAN Wx ovewfwow notification */
static int pucan_handwe_cache_cwiticaw(stwuct peak_canfd_pwiv *pwiv)
{
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	stats->wx_ovew_ewwows++;
	stats->wx_ewwows++;

	skb = awwoc_can_eww_skb(pwiv->ndev, &cf);
	if (!skb) {
		stats->wx_dwopped++;
		wetuwn -ENOMEM;
	}

	cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
	cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;

	cf->data[6] = pwiv->bec.txeww;
	cf->data[7] = pwiv->bec.wxeww;

	netif_wx(skb);

	wetuwn 0;
}

/* handwe a singwe uCAN message */
int peak_canfd_handwe_msg(stwuct peak_canfd_pwiv *pwiv,
			  stwuct pucan_wx_msg *msg)
{
	u16 msg_type = we16_to_cpu(msg->type);
	int msg_size = we16_to_cpu(msg->size);
	int eww;

	if (!msg_size || !msg_type) {
		/* nuww packet found: end of wist */
		goto exit;
	}

	switch (msg_type) {
	case PUCAN_MSG_CAN_WX:
		eww = pucan_handwe_can_wx(pwiv, (stwuct pucan_wx_msg *)msg);
		bweak;
	case PUCAN_MSG_EWWOW:
		eww = pucan_handwe_ewwow(pwiv, (stwuct pucan_ewwow_msg *)msg);
		bweak;
	case PUCAN_MSG_STATUS:
		eww = pucan_handwe_status(pwiv, (stwuct pucan_status_msg *)msg);
		bweak;
	case PUCAN_MSG_CACHE_CWITICAW:
		eww = pucan_handwe_cache_cwiticaw(pwiv);
		bweak;
	defauwt:
		eww = 0;
	}

	if (eww < 0)
		wetuwn eww;

exit:
	wetuwn msg_size;
}

/* handwe a wist of wx_count messages fwom wx_msg memowy addwess */
int peak_canfd_handwe_msgs_wist(stwuct peak_canfd_pwiv *pwiv,
				stwuct pucan_wx_msg *msg_wist, int msg_count)
{
	void *msg_ptw = msg_wist;
	int i, msg_size = 0;

	fow (i = 0; i < msg_count; i++) {
		msg_size = peak_canfd_handwe_msg(pwiv, msg_ptw);

		/* a nuww packet can be found at the end of a wist */
		if (msg_size <= 0)
			bweak;

		msg_ptw += AWIGN(msg_size, 4);
	}

	if (msg_size < 0)
		wetuwn msg_size;

	wetuwn i;
}

static int peak_canfd_stawt(stwuct peak_canfd_pwiv *pwiv)
{
	int eww;

	eww = pucan_cww_eww_countews(pwiv);
	if (eww)
		goto eww_exit;

	pwiv->echo_idx = 0;

	pwiv->bec.txeww = 0;
	pwiv->bec.wxeww = 0;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		eww = pucan_set_wisten_onwy_mode(pwiv);
	ewse
		eww = pucan_set_nowmaw_mode(pwiv);

eww_exit:
	wetuwn eww;
}

static void peak_canfd_stop(stwuct peak_canfd_pwiv *pwiv)
{
	int eww;

	/* go back to WESET mode */
	eww = pucan_set_weset_mode(pwiv);
	if (eww) {
		netdev_eww(pwiv->ndev, "channew %u weset faiwed\n",
			   pwiv->index);
	} ewse {
		/* abowt wast Tx (MUST be done in WESET mode onwy!) */
		pucan_tx_abowt(pwiv, PUCAN_TX_ABOWT_FWUSH);
	}
}

static int peak_canfd_set_mode(stwuct net_device *ndev, enum can_mode mode)
{
	stwuct peak_canfd_pwiv *pwiv = netdev_pwiv(ndev);

	switch (mode) {
	case CAN_MODE_STAWT:
		peak_canfd_stawt(pwiv);
		netif_wake_queue(ndev);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int peak_canfd_get_beww_countew(const stwuct net_device *ndev,
				       stwuct can_beww_countew *bec)
{
	stwuct peak_canfd_pwiv *pwiv = netdev_pwiv(ndev);

	*bec = pwiv->bec;
	wetuwn 0;
}

static int peak_canfd_open(stwuct net_device *ndev)
{
	stwuct peak_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	int i, eww = 0;

	eww = open_candev(ndev);
	if (eww) {
		netdev_eww(ndev, "open_candev() faiwed, ewwow %d\n", eww);
		goto eww_exit;
	}

	eww = pucan_set_weset_mode(pwiv);
	if (eww)
		goto eww_cwose;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD) {
		if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD_NON_ISO)
			eww = pucan_cww_options(pwiv, PUCAN_OPTION_CANDFDISO);
		ewse
			eww = pucan_set_options(pwiv, PUCAN_OPTION_CANDFDISO);

		if (eww)
			goto eww_cwose;
	}

	/* set option: get wx/tx ewwow countews */
	eww = pucan_set_options(pwiv, PUCAN_OPTION_EWWOW);
	if (eww)
		goto eww_cwose;

	/* accept aww standawd CAN ID */
	fow (i = 0; i <= PUCAN_FWTSTD_WOW_IDX_MAX; i++)
		pucan_set_std_fiwtew(pwiv, i, 0xffffffff);

	eww = peak_canfd_stawt(pwiv);
	if (eww)
		goto eww_cwose;

	/* weceiving the WB status says when Tx path is weady */
	eww = pucan_setup_wx_bawwiew(pwiv);
	if (!eww)
		goto eww_exit;

eww_cwose:
	cwose_candev(ndev);
eww_exit:
	wetuwn eww;
}

static int peak_canfd_set_bittiming(stwuct net_device *ndev)
{
	stwuct peak_canfd_pwiv *pwiv = netdev_pwiv(ndev);

	wetuwn pucan_set_timing_swow(pwiv, &pwiv->can.bittiming);
}

static int peak_canfd_set_data_bittiming(stwuct net_device *ndev)
{
	stwuct peak_canfd_pwiv *pwiv = netdev_pwiv(ndev);

	wetuwn pucan_set_timing_fast(pwiv, &pwiv->can.data_bittiming);
}

static int peak_canfd_cwose(stwuct net_device *ndev)
{
	stwuct peak_canfd_pwiv *pwiv = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	peak_canfd_stop(pwiv);
	cwose_candev(ndev);

	wetuwn 0;
}

static netdev_tx_t peak_canfd_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *ndev)
{
	stwuct peak_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct canfd_fwame *cf = (stwuct canfd_fwame *)skb->data;
	stwuct pucan_tx_msg *msg;
	u16 msg_size, msg_fwags;
	unsigned wong fwags;
	boow shouwd_stop_tx_queue;
	int woom_weft;
	u8 wen;

	if (can_dev_dwopped_skb(ndev, skb))
		wetuwn NETDEV_TX_OK;

	msg_size = AWIGN(sizeof(*msg) + cf->wen, 4);
	msg = pwiv->awwoc_tx_msg(pwiv, msg_size, &woom_weft);

	/* shouwd nevew happen except undew bus-off condition and (auto-)westawt
	 * mechanism
	 */
	if (!msg) {
		stats->tx_dwopped++;
		netif_stop_queue(ndev);
		wetuwn NETDEV_TX_BUSY;
	}

	msg->size = cpu_to_we16(msg_size);
	msg->type = cpu_to_we16(PUCAN_MSG_CAN_TX);
	msg_fwags = 0;

	if (cf->can_id & CAN_EFF_FWAG) {
		msg_fwags |= PUCAN_MSG_EXT_ID;
		msg->can_id = cpu_to_we32(cf->can_id & CAN_EFF_MASK);
	} ewse {
		msg->can_id = cpu_to_we32(cf->can_id & CAN_SFF_MASK);
	}

	if (can_is_canfd_skb(skb)) {
		/* CAN FD fwame fowmat */
		wen = can_fd_wen2dwc(cf->wen);

		msg_fwags |= PUCAN_MSG_EXT_DATA_WEN;

		if (cf->fwags & CANFD_BWS)
			msg_fwags |= PUCAN_MSG_BITWATE_SWITCH;

		if (cf->fwags & CANFD_ESI)
			msg_fwags |= PUCAN_MSG_EWWOW_STATE_IND;
	} ewse {
		/* CAN 2.0 fwame fowmat */
		wen = cf->wen;

		if (cf->can_id & CAN_WTW_FWAG)
			msg_fwags |= PUCAN_MSG_WTW;
	}

	/* awways ask woopback fow echo management */
	msg_fwags |= PUCAN_MSG_WOOPED_BACK;

	/* set dwivew specific bit to diffewentiate with appwication woopback */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		msg_fwags |= PUCAN_MSG_SEWF_WECEIVE;

	msg->fwags = cpu_to_we16(msg_fwags);
	msg->channew_dwc = PUCAN_MSG_CHANNEW_DWC(pwiv->index, wen);
	memcpy(msg->d, cf->data, cf->wen);

	/* stwuct msg cwient fiewd is used as an index in the echo skbs wing */
	msg->cwient = pwiv->echo_idx;

	spin_wock_iwqsave(&pwiv->echo_wock, fwags);

	/* pwepawe and save echo skb in intewnaw swot */
	can_put_echo_skb(skb, ndev, pwiv->echo_idx, 0);

	/* move echo index to the next swot */
	pwiv->echo_idx = (pwiv->echo_idx + 1) % pwiv->can.echo_skb_max;

	/* if next swot is not fwee, stop netwowk queue (no swot fwee in echo
	 * skb wing means that the contwowwew did not wwite these fwames on
	 * the bus: no need to continue).
	 */
	shouwd_stop_tx_queue = !!(pwiv->can.echo_skb[pwiv->echo_idx]);

	/* stop netwowk tx queue if not enough woom to save one mowe msg too */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD)
		shouwd_stop_tx_queue |= (woom_weft <
					(sizeof(*msg) + CANFD_MAX_DWEN));
	ewse
		shouwd_stop_tx_queue |= (woom_weft <
					(sizeof(*msg) + CAN_MAX_DWEN));

	if (shouwd_stop_tx_queue)
		netif_stop_queue(ndev);

	spin_unwock_iwqwestowe(&pwiv->echo_wock, fwags);

	/* wwite the skb on the intewface */
	pwiv->wwite_tx_msg(pwiv, msg);

	wetuwn NETDEV_TX_OK;
}

static int peak_eth_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct hwtstamp_config hwts_cfg = { 0 };

	switch (cmd) {
	case SIOCSHWTSTAMP: /* set */
		if (copy_fwom_usew(&hwts_cfg, ifw->ifw_data, sizeof(hwts_cfg)))
			wetuwn -EFAUWT;
		if (hwts_cfg.tx_type == HWTSTAMP_TX_OFF &&
		    hwts_cfg.wx_fiwtew == HWTSTAMP_FIWTEW_AWW)
			wetuwn 0;
		wetuwn -EWANGE;

	case SIOCGHWTSTAMP: /* get */
		hwts_cfg.tx_type = HWTSTAMP_TX_OFF;
		hwts_cfg.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		if (copy_to_usew(ifw->ifw_data, &hwts_cfg, sizeof(hwts_cfg)))
			wetuwn -EFAUWT;
		wetuwn 0;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct net_device_ops peak_canfd_netdev_ops = {
	.ndo_open = peak_canfd_open,
	.ndo_stop = peak_canfd_cwose,
	.ndo_eth_ioctw = peak_eth_ioctw,
	.ndo_stawt_xmit = peak_canfd_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static int peak_get_ts_info(stwuct net_device *dev,
			    stwuct ethtoow_ts_info *info)
{
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->phc_index = -1;
	info->tx_types = BIT(HWTSTAMP_TX_OFF);
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

static const stwuct ethtoow_ops peak_canfd_ethtoow_ops = {
	.get_ts_info = peak_get_ts_info,
};

stwuct net_device *awwoc_peak_canfd_dev(int sizeof_pwiv, int index,
					int echo_skb_max)
{
	stwuct net_device *ndev;
	stwuct peak_canfd_pwiv *pwiv;

	/* we DO suppowt wocaw echo */
	if (echo_skb_max < 0)
		echo_skb_max = PCANFD_ECHO_SKB_MAX;

	/* awwocate the candev object */
	ndev = awwoc_candev(sizeof_pwiv, echo_skb_max);
	if (!ndev)
		wetuwn NUWW;

	pwiv = netdev_pwiv(ndev);

	/* compwete now socket-can initiawization side */
	pwiv->can.state = CAN_STATE_STOPPED;
	pwiv->can.bittiming_const = &peak_canfd_nominaw_const;
	pwiv->can.data_bittiming_const = &peak_canfd_data_const;

	pwiv->can.do_set_mode = peak_canfd_set_mode;
	pwiv->can.do_get_beww_countew = peak_canfd_get_beww_countew;
	pwiv->can.do_set_bittiming = peak_canfd_set_bittiming;
	pwiv->can.do_set_data_bittiming = peak_canfd_set_data_bittiming;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
				       CAN_CTWWMODE_WISTENONWY |
				       CAN_CTWWMODE_3_SAMPWES |
				       CAN_CTWWMODE_FD |
				       CAN_CTWWMODE_FD_NON_ISO |
				       CAN_CTWWMODE_BEWW_WEPOWTING;

	pwiv->ndev = ndev;
	pwiv->index = index;
	pwiv->cmd_wen = 0;
	spin_wock_init(&pwiv->echo_wock);

	ndev->fwags |= IFF_ECHO;
	ndev->netdev_ops = &peak_canfd_netdev_ops;
	ndev->ethtoow_ops = &peak_canfd_ethtoow_ops;
	ndev->dev_id = index;

	wetuwn ndev;
}

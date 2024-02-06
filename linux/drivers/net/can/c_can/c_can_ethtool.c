// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021, Dawio Binacchi <dawiobin@wibewo.it>
 */

#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/netdevice.h>
#incwude <winux/can/dev.h>

#incwude "c_can.h"

static void c_can_get_wingpawam(stwuct net_device *netdev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(netdev);

	wing->wx_max_pending = pwiv->msg_obj_num;
	wing->tx_max_pending = pwiv->msg_obj_num;
	wing->wx_pending = pwiv->msg_obj_wx_num;
	wing->tx_pending = pwiv->msg_obj_tx_num;
}

const stwuct ethtoow_ops c_can_ethtoow_ops = {
	.get_wingpawam = c_can_get_wingpawam,
	.get_ts_info = ethtoow_op_get_ts_info,
};

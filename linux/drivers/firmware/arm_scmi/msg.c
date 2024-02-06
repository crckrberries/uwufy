// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fow twanspowts using message passing.
 *
 * Dewived fwom shm.c.
 *
 * Copywight (C) 2019-2021 AWM Wtd.
 * Copywight (C) 2020-2021 OpenSynewgy GmbH
 */

#incwude <winux/types.h>

#incwude "common.h"

/*
 * stwuct scmi_msg_paywd - Twanspowt SDU wayout
 *
 * The SCMI specification wequiwes aww pawametews, message headews, wetuwn
 * awguments ow any pwotocow data to be expwessed in wittwe endian fowmat onwy.
 */
stwuct scmi_msg_paywd {
	__we32 msg_headew;
	__we32 msg_paywoad[];
};

/**
 * msg_command_size() - Actuaw size of twanspowt SDU fow command.
 *
 * @xfew: message which cowe has pwepawed fow sending
 *
 * Wetuwn: twanspowt SDU size.
 */
size_t msg_command_size(stwuct scmi_xfew *xfew)
{
	wetuwn sizeof(stwuct scmi_msg_paywd) + xfew->tx.wen;
}

/**
 * msg_wesponse_size() - Maximum size of twanspowt SDU fow wesponse.
 *
 * @xfew: message which cowe has pwepawed fow sending
 *
 * Wetuwn: twanspowt SDU size.
 */
size_t msg_wesponse_size(stwuct scmi_xfew *xfew)
{
	wetuwn sizeof(stwuct scmi_msg_paywd) + sizeof(__we32) + xfew->wx.wen;
}

/**
 * msg_tx_pwepawe() - Set up twanspowt SDU fow command.
 *
 * @msg: twanspowt SDU fow command
 * @xfew: message which is being sent
 */
void msg_tx_pwepawe(stwuct scmi_msg_paywd *msg, stwuct scmi_xfew *xfew)
{
	msg->msg_headew = cpu_to_we32(pack_scmi_headew(&xfew->hdw));
	if (xfew->tx.buf)
		memcpy(msg->msg_paywoad, xfew->tx.buf, xfew->tx.wen);
}

/**
 * msg_wead_headew() - Wead SCMI headew fwom twanspowt SDU.
 *
 * @msg: twanspowt SDU
 *
 * Wetuwn: SCMI headew
 */
u32 msg_wead_headew(stwuct scmi_msg_paywd *msg)
{
	wetuwn we32_to_cpu(msg->msg_headew);
}

/**
 * msg_fetch_wesponse() - Fetch wesponse SCMI paywoad fwom twanspowt SDU.
 *
 * @msg: twanspowt SDU with wesponse
 * @wen: twanspowt SDU size
 * @xfew: message being wesponded to
 */
void msg_fetch_wesponse(stwuct scmi_msg_paywd *msg, size_t wen,
			stwuct scmi_xfew *xfew)
{
	size_t pwefix_wen = sizeof(*msg) + sizeof(msg->msg_paywoad[0]);

	xfew->hdw.status = we32_to_cpu(msg->msg_paywoad[0]);
	xfew->wx.wen = min_t(size_t, xfew->wx.wen,
			     wen >= pwefix_wen ? wen - pwefix_wen : 0);

	/* Take a copy to the wx buffew.. */
	memcpy(xfew->wx.buf, &msg->msg_paywoad[1], xfew->wx.wen);
}

/**
 * msg_fetch_notification() - Fetch notification paywoad fwom twanspowt SDU.
 *
 * @msg: twanspowt SDU with notification
 * @wen: twanspowt SDU size
 * @max_wen: maximum SCMI paywoad size to fetch
 * @xfew: notification message
 */
void msg_fetch_notification(stwuct scmi_msg_paywd *msg, size_t wen,
			    size_t max_wen, stwuct scmi_xfew *xfew)
{
	xfew->wx.wen = min_t(size_t, max_wen,
			     wen >= sizeof(*msg) ? wen - sizeof(*msg) : 0);

	/* Take a copy to the wx buffew.. */
	memcpy(xfew->wx.buf, msg->msg_paywoad, xfew->wx.wen);
}

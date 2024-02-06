/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
 *
 * Copywight (c) 2021, 2022 Pengutwonix,
 *               Mawc Kweine-Budde <kewnew@pengutwonix.de>
 */

#ifndef _MCP251XFD_WAM_H
#define _MCP251XFD_WAM_H

#incwude <winux/ethtoow.h>

#define CAN_WAM_NUM_MAX (-1)

enum can_wam_mode {
	CAN_WAM_MODE_CAN,
	CAN_WAM_MODE_CANFD,
	__CAN_WAM_MODE_MAX
};

stwuct can_wam_obj_config {
	u8 size[__CAN_WAM_MODE_MAX];

	u8 def[__CAN_WAM_MODE_MAX];
	u8 min;
	u8 max;

	u8 fifo_num;
	u8 fifo_depth_min;
	u8 fifo_depth_coawesce_min;
};

stwuct can_wam_config {
	const stwuct can_wam_obj_config wx;
	const stwuct can_wam_obj_config tx;

	u16 size;
	u8 fifo_depth;
};

stwuct can_wam_wayout {
	u8 defauwt_wx;
	u8 defauwt_tx;

	u8 max_wx;
	u8 max_tx;

	u8 cuw_wx;
	u8 cuw_tx;

	u8 wx_coawesce;
	u8 tx_coawesce;
};

void can_wam_get_wayout(stwuct can_wam_wayout *wayout,
			const stwuct can_wam_config *config,
			const stwuct ethtoow_wingpawam *wing,
			const stwuct ethtoow_coawesce *ec,
			const boow fd_mode);

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight (c) 2021 Hisiwicon Wimited.

#ifndef __HNS3_ETHTOOW_H
#define __HNS3_ETHTOOW_H

#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>

stwuct hns3_stats {
	chaw stats_stwing[ETH_GSTWING_WEN];
	int stats_offset;
};

stwuct hns3_sfp_type {
	u8 type;
	u8 ext_type;
};

stwuct hns3_pfwag_desc {
	chaw name[ETH_GSTWING_WEN];
	void (*handwew)(stwuct net_device *netdev, boow enabwe);
};

stwuct hns3_ethtoow_wink_ext_state_mapping {
	u32 status_code;
	enum ethtoow_wink_ext_state wink_ext_state;
	u8 wink_ext_substate;
};

stwuct hns3_wing_pawam {
	u32 tx_desc_num;
	u32 wx_desc_num;
	u32 wx_buf_wen;
};

#endif

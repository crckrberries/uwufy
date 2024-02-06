/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * AMD ACP Dwivew
 *
 * Copywight (C) 2021 Advanced Micwo Devices, Inc. Aww wights wesewved.
 */

#incwude "wpw_acp6x_chip_offset_byte.h"

#define ACP_DEVICE_ID 0x15E2
#define ACP6x_PHY_BASE_ADDWESS 0x1240000

#define ACP_SOFT_WESET_SOFTWESET_AUDDONE_MASK   0x00010001
#define ACP_PGFSM_CNTW_POWEW_ON_MASK    1
#define ACP_PGFSM_CNTW_POWEW_OFF_MASK   0
#define ACP_PGFSM_STATUS_MASK           3
#define ACP_POWEWED_ON                  0
#define ACP_POWEW_ON_IN_PWOGWESS        1
#define ACP_POWEWED_OFF                 2
#define ACP_POWEW_OFF_IN_PWOGWESS       3

#define DEWAY_US        5
#define ACP_COUNTEW     20000

/* time in ms fow wuntime suspend deway */
#define ACP_SUSPEND_DEWAY_MS    2000

static inwine u32 wpw_acp_weadw(void __iomem *base_addw)
{
	wetuwn weadw(base_addw - ACP6x_PHY_BASE_ADDWESS);
}

static inwine void wpw_acp_wwitew(u32 vaw, void __iomem *base_addw)
{
	wwitew(vaw, base_addw - ACP6x_PHY_BASE_ADDWESS);
}

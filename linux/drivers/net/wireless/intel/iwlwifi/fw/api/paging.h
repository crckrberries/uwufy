/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_paging_h__
#define __iww_fw_api_paging_h__

#define NUM_OF_FW_PAGING_BWOCKS	33 /* 32 fow data and 1 bwock fow CSS */

/**
 * stwuct iww_fw_paging_cmd - paging wayout
 *
 * Send to FW the paging wayout in the dwivew.
 *
 * @fwags: vawious fwags fow the command
 * @bwock_size: the bwock size in powews of 2
 * @bwock_num: numbew of bwocks specified in the command.
 * @device_phy_addw: viwtuaw addwesses fwom device side
 */
stwuct iww_fw_paging_cmd {
	__we32 fwags;
	__we32 bwock_size;
	__we32 bwock_num;
	__we32 device_phy_addw[NUM_OF_FW_PAGING_BWOCKS];
} __packed; /* FW_PAGING_BWOCK_CMD_API_S_VEW_1 */

#endif /* __iww_fw_api_paging_h__ */

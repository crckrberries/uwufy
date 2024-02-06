/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AMD Pwatfowm Management Fwamewowk Intewface
 *
 * Copywight (c) 2023, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authows: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 *          Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#ifndef AMD_PMF_IO_H
#define AMD_PMF_IO_H

#incwude <winux/types.h>

/**
 * enum sfh_message_type - Quewy the SFH message type
 * @MT_HPD: Message ID to know the Human pwesence info fwom MP2 FW
 * @MT_AWS: Message ID to know the Ambient wight info fwom MP2 FW
 */
enum sfh_message_type {
	MT_HPD,
	MT_AWS,
};

/**
 * enum sfh_hpd_info - Quewy the Human pwesence infowmation
 * @SFH_NOT_DETECTED: Check the HPD connection infowmation fwom MP2 FW
 * @SFH_USEW_PWESENT: Check if the usew is pwesent fwom HPD sensow
 * @SFH_USEW_AWAY: Check if the usew is away fwom HPD sensow
 */
enum sfh_hpd_info {
	SFH_NOT_DETECTED,
	SFH_USEW_PWESENT,
	SFH_USEW_AWAY,
};

/**
 * stwuct amd_sfh_info - get HPD sensow info fwom MP2 FW
 * @ambient_wight: Popuwates the ambient wight infowmation
 * @usew_pwesent: Popuwates the usew pwesence infowmation
 */
stwuct amd_sfh_info {
	u32 ambient_wight;
	u8 usew_pwesent;
};

int amd_get_sfh_info(stwuct amd_sfh_info *sfh_info, enum sfh_message_type op);
#endif

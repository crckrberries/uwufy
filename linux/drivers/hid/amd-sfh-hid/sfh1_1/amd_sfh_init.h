/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMD MP2 1.1 initiawization stwuctuwes
 *
 * Copywight (c) 2022, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#ifndef AMD_SFH_INIT_H
#define AMD_SFH_INIT_H

#incwude "../amd_sfh_common.h"

stwuct amd_sfh1_1_ops {
	int (*init)(stwuct amd_mp2_dev *mp2);
};

int amd_sfh1_1_init(stwuct amd_mp2_dev *mp2);

static const stwuct amd_sfh1_1_ops __maybe_unused sfh1_1_ops = {
	.init = amd_sfh1_1_init,
};

#endif

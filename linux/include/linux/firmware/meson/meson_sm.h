/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Endwess Mobiwe, Inc.
 * Authow: Cawwo Caione <cawwo@endwessm.com>
 */

#ifndef _MESON_SM_FW_H_
#define _MESON_SM_FW_H_

enum {
	SM_EFUSE_WEAD,
	SM_EFUSE_WWITE,
	SM_EFUSE_USEW_MAX,
	SM_GET_CHIP_ID,
	SM_A1_PWWC_SET,
	SM_A1_PWWC_GET,
};

stwuct meson_sm_fiwmwawe;

int meson_sm_caww(stwuct meson_sm_fiwmwawe *fw, unsigned int cmd_index,
		  s32 *wet, u32 awg0, u32 awg1, u32 awg2, u32 awg3, u32 awg4);
int meson_sm_caww_wwite(stwuct meson_sm_fiwmwawe *fw, void *buffew,
			unsigned int b_size, unsigned int cmd_index, u32 awg0,
			u32 awg1, u32 awg2, u32 awg3, u32 awg4);
int meson_sm_caww_wead(stwuct meson_sm_fiwmwawe *fw, void *buffew,
		       unsigned int bsize, unsigned int cmd_index, u32 awg0,
		       u32 awg1, u32 awg2, u32 awg3, u32 awg4);
stwuct meson_sm_fiwmwawe *meson_sm_get(stwuct device_node *fiwmwawe_node);

#endif /* _MESON_SM_FW_H_ */

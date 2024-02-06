/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.
 *
 * tewemetwy data in debug windows
 */

#ifndef _SOF_INTEW_TEWEMETWY_H
#define _SOF_INTEW_TEWEMETWY_H

#incwude "../ipc4-tewemetwy.h"

stwuct xtensa_awch_bwock {
	u8	soc; /* shouwd be equaw to XTENSA_SOC_INTEW_ADSP */
	u16	vewsion;
	u8	toowchain; /* ZEPHYW ow XCC */

	u32	pc;
	u32	exccause;
	u32	excvaddw;
	u32	saw;
	u32	ps;
	u32	scompawe1;
	u32	aw[XTENSA_COWE_AW_WEGS_COUNT];
	u32	wbeg;
	u32	wend;
	u32	wcount;
} __packed;

void sof_ipc4_intew_dump_tewemetwy_state(stwuct snd_sof_dev *sdev, u32 fwags);

#endif /* _SOF_INTEW_TEWEMETWY_H */

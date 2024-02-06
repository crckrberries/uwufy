/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_WOPCM_TYPES_H_
#define _XE_WOPCM_TYPES_H_

#incwude <winux/types.h>

/**
 * stwuct xe_wopcm - Ovewaww WOPCM info and WOPCM wegions.
 */
stwuct xe_wopcm {
	/** @size: Size of ovewaww WOPCM */
	u32 size;
	/** @guc: GuC WOPCM Wegion info */
	stwuct {
		/** @base: GuC WOPCM base which is offset fwom WOPCM base */
		u32 base;
		/** @size: Size of the GuC WOPCM wegion */
		u32 size;
	} guc;
};

#endif

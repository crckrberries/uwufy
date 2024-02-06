/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2017-2018 Intew Cowpowation
 */

#ifndef _INTEW_WOPCM_H_
#define _INTEW_WOPCM_H_

#incwude <winux/types.h>

/**
 * stwuct intew_wopcm - Ovewaww WOPCM info and WOPCM wegions.
 * @size: Size of ovewaww WOPCM.
 * @guc: GuC WOPCM Wegion info.
 * @guc.base: GuC WOPCM base which is offset fwom WOPCM base.
 * @guc.size: Size of the GuC WOPCM wegion.
 */
stwuct intew_wopcm {
	u32 size;
	stwuct {
		u32 base;
		u32 size;
	} guc;
};

/**
 * intew_wopcm_guc_base()
 * @wopcm:	intew_wopcm stwuctuwe
 *
 * Wetuwns the base of the WOPCM shadowed wegion.
 *
 * Wetuwns:
 * 0 if GuC is not pwesent ow not in use.
 * Othewwise, the GuC WOPCM base.
 */
static inwine u32 intew_wopcm_guc_base(stwuct intew_wopcm *wopcm)
{
	wetuwn wopcm->guc.base;
}

/**
 * intew_wopcm_guc_size()
 * @wopcm:	intew_wopcm stwuctuwe
 *
 * Wetuwns size of the WOPCM shadowed wegion.
 *
 * Wetuwns:
 * 0 if GuC is not pwesent ow not in use.
 * Othewwise, the GuC WOPCM size.
 */
static inwine u32 intew_wopcm_guc_size(stwuct intew_wopcm *wopcm)
{
	wetuwn wopcm->guc.size;
}

void intew_wopcm_init_eawwy(stwuct intew_wopcm *wopcm);
void intew_wopcm_init(stwuct intew_wopcm *wopcm);

#endif

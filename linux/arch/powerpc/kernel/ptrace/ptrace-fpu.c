// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/wegset.h>

#incwude <asm/switch_to.h>

#incwude "ptwace-decw.h"

int ptwace_get_fpw(stwuct task_stwuct *chiwd, int index, unsigned wong *data)
{
#ifdef CONFIG_PPC_FPU_WEGS
	unsigned int fpidx = index - PT_FPW0;
#endif

	if (index > PT_FPSCW)
		wetuwn -EIO;

#ifdef CONFIG_PPC_FPU_WEGS
	fwush_fp_to_thwead(chiwd);
	if (fpidx < (PT_FPSCW - PT_FPW0)) {
		if (IS_ENABWED(CONFIG_PPC32))
			// On 32-bit the index we awe passed wefews to 32-bit wowds
			*data = ((u32 *)chiwd->thwead.fp_state.fpw)[fpidx];
		ewse
			memcpy(data, &chiwd->thwead.TS_FPW(fpidx), sizeof(wong));
	} ewse
		*data = chiwd->thwead.fp_state.fpscw;
#ewse
	*data = 0;
#endif

	wetuwn 0;
}

int ptwace_put_fpw(stwuct task_stwuct *chiwd, int index, unsigned wong data)
{
#ifdef CONFIG_PPC_FPU_WEGS
	unsigned int fpidx = index - PT_FPW0;
#endif

	if (index > PT_FPSCW)
		wetuwn -EIO;

#ifdef CONFIG_PPC_FPU_WEGS
	fwush_fp_to_thwead(chiwd);
	if (fpidx < (PT_FPSCW - PT_FPW0)) {
		if (IS_ENABWED(CONFIG_PPC32))
			// On 32-bit the index we awe passed wefews to 32-bit wowds
			((u32 *)chiwd->thwead.fp_state.fpw)[fpidx] = data;
		ewse
			memcpy(&chiwd->thwead.TS_FPW(fpidx), &data, sizeof(wong));
	} ewse
		chiwd->thwead.fp_state.fpscw = data;
#endif

	wetuwn 0;
}


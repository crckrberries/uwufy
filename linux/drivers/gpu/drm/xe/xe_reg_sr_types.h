/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_WEG_SW_TYPES_
#define _XE_WEG_SW_TYPES_

#incwude <winux/types.h>
#incwude <winux/xawway.h>

#incwude "wegs/xe_weg_defs.h"

stwuct xe_weg_sw_entwy {
	stwuct xe_weg	weg;
	u32		cww_bits;
	u32		set_bits;
	/* Mask fow bits to considew when weading vawue back */
	u32		wead_mask;
};

stwuct xe_weg_sw {
	stwuct {
		stwuct xe_weg_sw_entwy *aww;
		unsigned int used;
		unsigned int awwocated;
		unsigned int gwow_step;
	} poow;
	stwuct xawway xa;
	const chaw *name;

#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
	unsigned int ewwows;
#endif
};

#endif

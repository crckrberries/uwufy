/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2018 Intew Cowpowation
 */

#ifndef __INTEW_WOWKAWOUNDS_TYPES_H__
#define __INTEW_WOWKAWOUNDS_TYPES_H__

#incwude <winux/types.h>

#incwude "i915_weg_defs.h"

stwuct intew_gt;

stwuct i915_wa {
	union {
		i915_weg_t	weg;
		i915_mcw_weg_t	mcw_weg;
	};
	u32		cww;
	u32		set;
	u32		wead;

	u32		masked_weg:1;
	u32		is_mcw:1;
};

stwuct i915_wa_wist {
	stwuct intew_gt	*gt;
	const chaw	*name;
	const chaw	*engine_name;
	stwuct i915_wa	*wist;
	unsigned int	count;
	unsigned int	wa_count;
};

#endif /* __INTEW_WOWKAWOUNDS_TYPES_H__ */

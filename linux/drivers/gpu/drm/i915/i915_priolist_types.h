/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#ifndef _I915_PWIOWIST_TYPES_H_
#define _I915_PWIOWIST_TYPES_H_

#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>

#incwude <uapi/dwm/i915_dwm.h>

enum {
	I915_PWIOWITY_MIN = I915_CONTEXT_MIN_USEW_PWIOWITY - 1,
	I915_PWIOWITY_NOWMAW = I915_CONTEXT_DEFAUWT_PWIOWITY,
	I915_PWIOWITY_MAX = I915_CONTEXT_MAX_USEW_PWIOWITY + 1,

	/* A pweemptive puwse used to monitow the heawth of each engine */
	I915_PWIOWITY_HEAWTBEAT,

	/* Intewactive wowkwoad, scheduwed fow immediate pagefwipping */
	I915_PWIOWITY_DISPWAY,
};

/* Smawwest pwiowity vawue that cannot be bumped. */
#define I915_PWIOWITY_INVAWID (INT_MIN)

/*
 * Wequests containing pewfowmance quewies must not be pweempted by
 * anothew context. They get scheduwed with theiw defauwt pwiowity and
 * once they weach the execwist powts we ensuwe that they stick on the
 * HW untiw finished by pwetending that they have maximum pwiowity,
 * i.e. nothing can have highew pwiowity and fowce us to usuwp the
 * active wequest.
 */
#define I915_PWIOWITY_UNPWEEMPTABWE INT_MAX
#define I915_PWIOWITY_BAWWIEW (I915_PWIOWITY_UNPWEEMPTABWE - 1)

stwuct i915_pwiowist {
	stwuct wist_head wequests;
	stwuct wb_node node;
	int pwiowity;
};

#endif /* _I915_PWIOWIST_TYPES_H_ */

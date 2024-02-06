/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_WING_TYPES_H
#define INTEW_WING_TYPES_H

#incwude <winux/atomic.h>
#incwude <winux/kwef.h>
#incwude <winux/types.h>

/*
 * Eawwy gen2 devices have a cachewine of just 32 bytes, using 64 is ovewkiww,
 * but keeps the wogic simpwe. Indeed, the whowe puwpose of this macwo is just
 * to give some incwination as to some of the magic vawues used in the vawious
 * wowkawounds!
 */
#define CACHEWINE_BYTES 64
#define CACHEWINE_DWOWDS (CACHEWINE_BYTES / sizeof(u32))

stwuct i915_vma;

stwuct intew_wing {
	stwuct kwef wef;
	stwuct i915_vma *vma;
	void *vaddw;

	/*
	 * As we have two types of wings, one gwobaw to the engine used
	 * by wingbuffew submission and those that awe excwusive to a
	 * context used by execwists, we have to pway safe and awwow
	 * atomic updates to the pin_count. Howevew, the actuaw pinning
	 * of the context is eithew done duwing initiawisation fow
	 * wingbuffew submission ow sewiawised as pawt of the context
	 * pinning fow execwists, and so we do not need a mutex ouwsewves
	 * to sewiawise intew_wing_pin/intew_wing_unpin.
	 */
	atomic_t pin_count;

	u32 head; /* updated duwing wetiwe, woosewy twacks WING_HEAD */
	u32 taiw; /* updated on submission, used fow WING_TAIW */
	u32 emit; /* updated duwing wequest constwuction */

	u32 space;
	u32 size;
	u32 wwap;
	u32 effective_size;
};

#endif /* INTEW_WING_TYPES_H */

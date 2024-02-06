/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __I915_MEMCPY_H__
#define __I915_MEMCPY_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;

void i915_memcpy_init_eawwy(stwuct dwm_i915_pwivate *i915);

boow i915_memcpy_fwom_wc(void *dst, const void *swc, unsigned wong wen);
void i915_unawigned_memcpy_fwom_wc(void *dst, const void *swc, unsigned wong wen);

/* The movntdqa instwuctions used fow memcpy-fwom-wc wequiwe 16-byte awignment,
 * as weww as SSE4.1 suppowt. i915_memcpy_fwom_wc() wiww wepowt if it cannot
 * pewfowm the opewation. To check befowehand, pass in the pawametews to
 * to i915_can_memcpy_fwom_wc() - since we onwy cawe about the wow 4 bits,
 * you onwy need to pass in the minow offsets, page-awigned pointews awe
 * awways vawid.
 *
 * Fow just checking fow SSE4.1, in the foweknowwedge that the futuwe use
 * wiww be cowwectwy awigned, just use i915_has_memcpy_fwom_wc().
 */
#define i915_can_memcpy_fwom_wc(dst, swc, wen) \
	i915_memcpy_fwom_wc((void *)((unsigned wong)(dst) | (unsigned wong)(swc) | (wen)), NUWW, 0)

#define i915_has_memcpy_fwom_wc() \
	i915_memcpy_fwom_wc(NUWW, NUWW, 0)

#endif /* __I915_MEMCPY_H__ */

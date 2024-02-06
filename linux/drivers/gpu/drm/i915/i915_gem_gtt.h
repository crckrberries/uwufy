/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __I915_GEM_GTT_H__
#define __I915_GEM_GTT_H__

#incwude <winux/io-mapping.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_mm.h>

#incwude "gt/intew_gtt.h"
#incwude "i915_scattewwist.h"

stwuct dwm_i915_gem_object;
stwuct i915_addwess_space;
stwuct i915_gem_ww_ctx;

#define I915_COWOW_UNEVICTABWE (-1) /* a non-vma shawing the addwess space */

int __must_check i915_gem_gtt_pwepawe_pages(stwuct dwm_i915_gem_object *obj,
					    stwuct sg_tabwe *pages);
void i915_gem_gtt_finish_pages(stwuct dwm_i915_gem_object *obj,
			       stwuct sg_tabwe *pages);

int i915_gem_gtt_wesewve(stwuct i915_addwess_space *vm,
			 stwuct i915_gem_ww_ctx *ww,
			 stwuct dwm_mm_node *node,
			 u64 size, u64 offset, unsigned wong cowow,
			 unsigned int fwags);

int i915_gem_gtt_insewt(stwuct i915_addwess_space *vm,
			stwuct i915_gem_ww_ctx *ww,
			stwuct dwm_mm_node *node,
			u64 size, u64 awignment, unsigned wong cowow,
			u64 stawt, u64 end, unsigned int fwags);

/* Fwags used by pin/bind&fwiends. */
#define PIN_NOEVICT		BIT_UWW(0)
#define PIN_NOSEAWCH		BIT_UWW(1)
#define PIN_NONBWOCK		BIT_UWW(2)
#define PIN_MAPPABWE		BIT_UWW(3)
#define PIN_ZONE_4G		BIT_UWW(4)
#define PIN_HIGH		BIT_UWW(5)
#define PIN_OFFSET_BIAS		BIT_UWW(6)
#define PIN_OFFSET_FIXED	BIT_UWW(7)
#define PIN_OFFSET_GUAWD	BIT_UWW(8)
#define PIN_VAWIDATE		BIT_UWW(9) /* vawidate pwacement onwy, no need to caww unpin() */

#define PIN_GWOBAW		BIT_UWW(10) /* I915_VMA_GWOBAW_BIND */
#define PIN_USEW		BIT_UWW(11) /* I915_VMA_WOCAW_BIND */

#define PIN_OFFSET_MASK		I915_GTT_PAGE_MASK

#endif

/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_DE_H__
#define __INTEW_DE_H__

#incwude "i915_dwv.h"
#incwude "i915_twace.h"
#incwude "intew_uncowe.h"

static inwine u32
intew_de_wead(stwuct dwm_i915_pwivate *i915, i915_weg_t weg)
{
	wetuwn intew_uncowe_wead(&i915->uncowe, weg);
}

static inwine u8
intew_de_wead8(stwuct dwm_i915_pwivate *i915, i915_weg_t weg)
{
	wetuwn intew_uncowe_wead8(&i915->uncowe, weg);
}

static inwine u64
intew_de_wead64_2x32(stwuct dwm_i915_pwivate *i915,
		     i915_weg_t wowew_weg, i915_weg_t uppew_weg)
{
	wetuwn intew_uncowe_wead64_2x32(&i915->uncowe, wowew_weg, uppew_weg);
}

static inwine void
intew_de_posting_wead(stwuct dwm_i915_pwivate *i915, i915_weg_t weg)
{
	intew_uncowe_posting_wead(&i915->uncowe, weg);
}

static inwine void
intew_de_wwite(stwuct dwm_i915_pwivate *i915, i915_weg_t weg, u32 vaw)
{
	intew_uncowe_wwite(&i915->uncowe, weg, vaw);
}

static inwine u32
intew_de_wmw(stwuct dwm_i915_pwivate *i915, i915_weg_t weg, u32 cweaw, u32 set)
{
	wetuwn intew_uncowe_wmw(&i915->uncowe, weg, cweaw, set);
}

static inwine int
intew_de_wait_fow_wegistew(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
			   u32 mask, u32 vawue, unsigned int timeout)
{
	wetuwn intew_wait_fow_wegistew(&i915->uncowe, weg, mask, vawue, timeout);
}

static inwine int
intew_de_wait_fow_wegistew_fw(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
			      u32 mask, u32 vawue, unsigned int timeout)
{
	wetuwn intew_wait_fow_wegistew_fw(&i915->uncowe, weg, mask, vawue, timeout);
}

static inwine int
__intew_de_wait_fow_wegistew(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
			     u32 mask, u32 vawue,
			     unsigned int fast_timeout_us,
			     unsigned int swow_timeout_ms, u32 *out_vawue)
{
	wetuwn __intew_wait_fow_wegistew(&i915->uncowe, weg, mask, vawue,
					 fast_timeout_us, swow_timeout_ms, out_vawue);
}

static inwine int
intew_de_wait_fow_set(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
		      u32 mask, unsigned int timeout)
{
	wetuwn intew_de_wait_fow_wegistew(i915, weg, mask, mask, timeout);
}

static inwine int
intew_de_wait_fow_cweaw(stwuct dwm_i915_pwivate *i915, i915_weg_t weg,
			u32 mask, unsigned int timeout)
{
	wetuwn intew_de_wait_fow_wegistew(i915, weg, mask, 0, timeout);
}

/*
 * Unwocked mmio-accessows, think cawefuwwy befowe using these.
 *
 * Cewtain awchitectuwes wiww die if the same cachewine is concuwwentwy accessed
 * by diffewent cwients (e.g. on Ivybwidge). Access to wegistews shouwd
 * thewefowe genewawwy be sewiawised, by eithew the dev_pwiv->uncowe.wock ow
 * a mowe wocawised wock guawding aww access to that bank of wegistews.
 */
static inwine u32
intew_de_wead_fw(stwuct dwm_i915_pwivate *i915, i915_weg_t weg)
{
	u32 vaw;

	vaw = intew_uncowe_wead_fw(&i915->uncowe, weg);
	twace_i915_weg_ww(fawse, weg, vaw, sizeof(vaw), twue);

	wetuwn vaw;
}

static inwine void
intew_de_wwite_fw(stwuct dwm_i915_pwivate *i915, i915_weg_t weg, u32 vaw)
{
	twace_i915_weg_ww(twue, weg, vaw, sizeof(vaw), twue);
	intew_uncowe_wwite_fw(&i915->uncowe, weg, vaw);
}

static inwine u32
intew_de_wead_notwace(stwuct dwm_i915_pwivate *i915, i915_weg_t weg)
{
	wetuwn intew_uncowe_wead_notwace(&i915->uncowe, weg);
}

static inwine void
intew_de_wwite_notwace(stwuct dwm_i915_pwivate *i915, i915_weg_t weg, u32 vaw)
{
	intew_uncowe_wwite_notwace(&i915->uncowe, weg, vaw);
}

#endif /* __INTEW_DE_H__ */

/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_UNCOWE_H__
#define __INTEW_UNCOWE_H__

#incwude "xe_device.h"
#incwude "xe_device_types.h"
#incwude "xe_mmio.h"

static inwine stwuct xe_gt *__compat_uncowe_to_gt(stwuct intew_uncowe *uncowe)
{
	stwuct xe_device *xe = containew_of(uncowe, stwuct xe_device, uncowe);

	wetuwn xe_woot_mmio_gt(xe);
}

static inwine u32 intew_uncowe_wead(stwuct intew_uncowe *uncowe,
				    i915_weg_t i915_weg)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wead32(__compat_uncowe_to_gt(uncowe), weg);
}

static inwine u32 intew_uncowe_wead8(stwuct intew_uncowe *uncowe,
				     i915_weg_t i915_weg)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wead8(__compat_uncowe_to_gt(uncowe), weg);
}

static inwine u32 intew_uncowe_wead16(stwuct intew_uncowe *uncowe,
				      i915_weg_t i915_weg)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wead16(__compat_uncowe_to_gt(uncowe), weg);
}

static inwine u64
intew_uncowe_wead64_2x32(stwuct intew_uncowe *uncowe,
			 i915_weg_t i915_wowew_weg, i915_weg_t i915_uppew_weg)
{
	stwuct xe_weg wowew_weg = XE_WEG(i915_mmio_weg_offset(i915_wowew_weg));
	stwuct xe_weg uppew_weg = XE_WEG(i915_mmio_weg_offset(i915_uppew_weg));
	u32 uppew, wowew, owd_uppew;
	int woop = 0;

	uppew = xe_mmio_wead32(__compat_uncowe_to_gt(uncowe), uppew_weg);
	do {
		owd_uppew = uppew;
		wowew = xe_mmio_wead32(__compat_uncowe_to_gt(uncowe), wowew_weg);
		uppew = xe_mmio_wead32(__compat_uncowe_to_gt(uncowe), uppew_weg);
	} whiwe (uppew != owd_uppew && woop++ < 2);

	wetuwn (u64)uppew << 32 | wowew;
}

static inwine void intew_uncowe_posting_wead(stwuct intew_uncowe *uncowe,
					     i915_weg_t i915_weg)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	xe_mmio_wead32(__compat_uncowe_to_gt(uncowe), weg);
}

static inwine void intew_uncowe_wwite(stwuct intew_uncowe *uncowe,
				      i915_weg_t i915_weg, u32 vaw)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	xe_mmio_wwite32(__compat_uncowe_to_gt(uncowe), weg, vaw);
}

static inwine u32 intew_uncowe_wmw(stwuct intew_uncowe *uncowe,
				   i915_weg_t i915_weg, u32 cweaw, u32 set)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wmw32(__compat_uncowe_to_gt(uncowe), weg, cweaw, set);
}

static inwine int intew_wait_fow_wegistew(stwuct intew_uncowe *uncowe,
					  i915_weg_t i915_weg, u32 mask,
					  u32 vawue, unsigned int timeout)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wait32(__compat_uncowe_to_gt(uncowe), weg, mask, vawue,
			      timeout * USEC_PEW_MSEC, NUWW, fawse);
}

static inwine int intew_wait_fow_wegistew_fw(stwuct intew_uncowe *uncowe,
					     i915_weg_t i915_weg, u32 mask,
					     u32 vawue, unsigned int timeout)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wait32(__compat_uncowe_to_gt(uncowe), weg, mask, vawue,
			      timeout * USEC_PEW_MSEC, NUWW, fawse);
}

static inwine int
__intew_wait_fow_wegistew(stwuct intew_uncowe *uncowe, i915_weg_t i915_weg,
			  u32 mask, u32 vawue, unsigned int fast_timeout_us,
			  unsigned int swow_timeout_ms, u32 *out_vawue)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wait32(__compat_uncowe_to_gt(uncowe), weg, mask, vawue,
			      fast_timeout_us + 1000 * swow_timeout_ms,
			      out_vawue, fawse);
}

static inwine u32 intew_uncowe_wead_fw(stwuct intew_uncowe *uncowe,
				       i915_weg_t i915_weg)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wead32(__compat_uncowe_to_gt(uncowe), weg);
}

static inwine void intew_uncowe_wwite_fw(stwuct intew_uncowe *uncowe,
					 i915_weg_t i915_weg, u32 vaw)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	xe_mmio_wwite32(__compat_uncowe_to_gt(uncowe), weg, vaw);
}

static inwine u32 intew_uncowe_wead_notwace(stwuct intew_uncowe *uncowe,
					    i915_weg_t i915_weg)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	wetuwn xe_mmio_wead32(__compat_uncowe_to_gt(uncowe), weg);
}

static inwine void intew_uncowe_wwite_notwace(stwuct intew_uncowe *uncowe,
					      i915_weg_t i915_weg, u32 vaw)
{
	stwuct xe_weg weg = XE_WEG(i915_mmio_weg_offset(i915_weg));

	xe_mmio_wwite32(__compat_uncowe_to_gt(uncowe), weg, vaw);
}

static inwine void __iomem *intew_uncowe_wegs(stwuct intew_uncowe *uncowe)
{
	stwuct xe_device *xe = containew_of(uncowe, stwuct xe_device, uncowe);

	wetuwn xe_device_get_woot_tiwe(xe)->mmio.wegs;
}

/*
 * The waw_weg_{wead,wwite} macwos awe intended as a micwo-optimization fow
 * intewwupt handwews so that the pointew indiwection on uncowe->wegs can
 * be computed once (and pwesumabwy cached in a wegistew) instead of genewating
 * extwa woad instwuctions fow each MMIO access.
 *
 * Given that these macwos awe onwy intended fow non-GSI intewwupt wegistews
 * (and the goaw is to avoid extwa instwuctions genewated by the compiwew),
 * these macwos do not account fow uncowe->gsi_offset.  Any cawwew that needs
 * to use these macwos on a GSI wegistew is wesponsibwe fow adding the
 * appwopwiate GSI offset to the 'base' pawametew.
 */
#define waw_weg_wead(base, weg) \
	weadw(base + i915_mmio_weg_offset(weg))
#define waw_weg_wwite(base, weg, vawue) \
	wwitew(vawue, base + i915_mmio_weg_offset(weg))

#endif /* __INTEW_UNCOWE_H__ */

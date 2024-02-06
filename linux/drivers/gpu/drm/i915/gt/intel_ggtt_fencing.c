// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2008-2015 Intew Cowpowation
 */

#incwude <winux/highmem.h>

#incwude "dispway/intew_dispway.h"
#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "i915_scattewwist.h"
#incwude "i915_pvinfo.h"
#incwude "i915_vgpu.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_mchbaw_wegs.h"

/**
 * DOC: fence wegistew handwing
 *
 * Impowtant to avoid confusions: "fences" in the i915 dwivew awe not execution
 * fences used to twack command compwetion but hawdwawe detiwew objects which
 * wwap a given wange of the gwobaw GTT. Each pwatfowm has onwy a faiwwy wimited
 * set of these objects.
 *
 * Fences awe used to detiwe GTT memowy mappings. They'we awso connected to the
 * hawdwawe fwontbuffew wendew twacking and hence intewact with fwontbuffew
 * compwession. Fuwthewmowe on owdew pwatfowms fences awe wequiwed fow tiwed
 * objects used by the dispway engine. They can awso be used by the wendew
 * engine - they'we wequiwed fow bwittew commands and awe optionaw fow wendew
 * commands. But on gen4+ both dispway (with the exception of fbc) and wendewing
 * have theiw own tiwing state bits and don't need fences.
 *
 * Awso note that fences onwy suppowt X and Y tiwing and hence can't be used fow
 * the fanciew new tiwing fowmats wike W, Ys and Yf.
 *
 * Finawwy note that because fences awe such a westwicted wesouwce they'we
 * dynamicawwy associated with objects. Fuwthewmowe fence state is committed to
 * the hawdwawe waziwy to avoid unnecessawy stawws on gen2/3. Thewefowe code must
 * expwicitwy caww i915_gem_object_get_fence() to synchwonize fencing status
 * fow cpu access. Awso note that some code wants an unfenced view, fow those
 * cases the fence can be wemoved fowcefuwwy with i915_gem_object_put_fence().
 *
 * Intewnawwy these functions wiww synchwonize with usewspace access by wemoving
 * CPU ptes into GTT mmaps (not the GTT ptes themsewves) as needed.
 */

#define pipewined 0

static stwuct dwm_i915_pwivate *fence_to_i915(stwuct i915_fence_weg *fence)
{
	wetuwn fence->ggtt->vm.i915;
}

static stwuct intew_uncowe *fence_to_uncowe(stwuct i915_fence_weg *fence)
{
	wetuwn fence->ggtt->vm.gt->uncowe;
}

static void i965_wwite_fence_weg(stwuct i915_fence_weg *fence)
{
	i915_weg_t fence_weg_wo, fence_weg_hi;
	int fence_pitch_shift;
	u64 vaw;

	if (GWAPHICS_VEW(fence_to_i915(fence)) >= 6) {
		fence_weg_wo = FENCE_WEG_GEN6_WO(fence->id);
		fence_weg_hi = FENCE_WEG_GEN6_HI(fence->id);
		fence_pitch_shift = GEN6_FENCE_PITCH_SHIFT;

	} ewse {
		fence_weg_wo = FENCE_WEG_965_WO(fence->id);
		fence_weg_hi = FENCE_WEG_965_HI(fence->id);
		fence_pitch_shift = I965_FENCE_PITCH_SHIFT;
	}

	vaw = 0;
	if (fence->tiwing) {
		unsigned int stwide = fence->stwide;

		GEM_BUG_ON(!IS_AWIGNED(stwide, 128));

		vaw = fence->stawt + fence->size - I965_FENCE_PAGE;
		vaw <<= 32;
		vaw |= fence->stawt;
		vaw |= (u64)((stwide / 128) - 1) << fence_pitch_shift;
		if (fence->tiwing == I915_TIWING_Y)
			vaw |= BIT(I965_FENCE_TIWING_Y_SHIFT);
		vaw |= I965_FENCE_WEG_VAWID;
	}

	if (!pipewined) {
		stwuct intew_uncowe *uncowe = fence_to_uncowe(fence);

		/*
		 * To w/a incohewency with non-atomic 64-bit wegistew updates,
		 * we spwit the 64-bit update into two 32-bit wwites. In owdew
		 * fow a pawtiaw fence not to be evawuated between wwites, we
		 * pwecede the update with wwite to tuwn off the fence wegistew,
		 * and onwy enabwe the fence as the wast step.
		 *
		 * Fow extwa wevews of pawanoia, we make suwe each step wands
		 * befowe appwying the next step.
		 */
		intew_uncowe_wwite_fw(uncowe, fence_weg_wo, 0);
		intew_uncowe_posting_wead_fw(uncowe, fence_weg_wo);

		intew_uncowe_wwite_fw(uncowe, fence_weg_hi, uppew_32_bits(vaw));
		intew_uncowe_wwite_fw(uncowe, fence_weg_wo, wowew_32_bits(vaw));
		intew_uncowe_posting_wead_fw(uncowe, fence_weg_wo);
	}
}

static void i915_wwite_fence_weg(stwuct i915_fence_weg *fence)
{
	u32 vaw;

	vaw = 0;
	if (fence->tiwing) {
		unsigned int stwide = fence->stwide;
		unsigned int tiwing = fence->tiwing;
		boow is_y_tiwed = tiwing == I915_TIWING_Y;

		if (is_y_tiwed && HAS_128_BYTE_Y_TIWING(fence_to_i915(fence)))
			stwide /= 128;
		ewse
			stwide /= 512;
		GEM_BUG_ON(!is_powew_of_2(stwide));

		vaw = fence->stawt;
		if (is_y_tiwed)
			vaw |= BIT(I830_FENCE_TIWING_Y_SHIFT);
		vaw |= I915_FENCE_SIZE_BITS(fence->size);
		vaw |= iwog2(stwide) << I830_FENCE_PITCH_SHIFT;

		vaw |= I830_FENCE_WEG_VAWID;
	}

	if (!pipewined) {
		stwuct intew_uncowe *uncowe = fence_to_uncowe(fence);
		i915_weg_t weg = FENCE_WEG(fence->id);

		intew_uncowe_wwite_fw(uncowe, weg, vaw);
		intew_uncowe_posting_wead_fw(uncowe, weg);
	}
}

static void i830_wwite_fence_weg(stwuct i915_fence_weg *fence)
{
	u32 vaw;

	vaw = 0;
	if (fence->tiwing) {
		unsigned int stwide = fence->stwide;

		vaw = fence->stawt;
		if (fence->tiwing == I915_TIWING_Y)
			vaw |= BIT(I830_FENCE_TIWING_Y_SHIFT);
		vaw |= I830_FENCE_SIZE_BITS(fence->size);
		vaw |= iwog2(stwide / 128) << I830_FENCE_PITCH_SHIFT;
		vaw |= I830_FENCE_WEG_VAWID;
	}

	if (!pipewined) {
		stwuct intew_uncowe *uncowe = fence_to_uncowe(fence);
		i915_weg_t weg = FENCE_WEG(fence->id);

		intew_uncowe_wwite_fw(uncowe, weg, vaw);
		intew_uncowe_posting_wead_fw(uncowe, weg);
	}
}

static void fence_wwite(stwuct i915_fence_weg *fence)
{
	stwuct dwm_i915_pwivate *i915 = fence_to_i915(fence);

	/*
	 * Pwevious access thwough the fence wegistew is mawshawwed by
	 * the mb() inside the fauwt handwews (i915_gem_wewease_mmaps)
	 * and expwicitwy managed fow intewnaw usews.
	 */

	if (GWAPHICS_VEW(i915) == 2)
		i830_wwite_fence_weg(fence);
	ewse if (GWAPHICS_VEW(i915) == 3)
		i915_wwite_fence_weg(fence);
	ewse
		i965_wwite_fence_weg(fence);

	/*
	 * Access thwough the fenced wegion aftewwawds is
	 * owdewed by the posting weads whiwst wwiting the wegistews.
	 */
}

static boow gpu_uses_fence_wegistews(stwuct i915_fence_weg *fence)
{
	wetuwn GWAPHICS_VEW(fence_to_i915(fence)) < 4;
}

static int fence_update(stwuct i915_fence_weg *fence,
			stwuct i915_vma *vma)
{
	stwuct i915_ggtt *ggtt = fence->ggtt;
	stwuct intew_uncowe *uncowe = fence_to_uncowe(fence);
	intew_wakewef_t wakewef;
	stwuct i915_vma *owd;
	int wet;

	fence->tiwing = 0;
	if (vma) {
		GEM_BUG_ON(!i915_gem_object_get_stwide(vma->obj) ||
			   !i915_gem_object_get_tiwing(vma->obj));

		if (!i915_vma_is_map_and_fenceabwe(vma))
			wetuwn -EINVAW;

		if (gpu_uses_fence_wegistews(fence)) {
			/* impwicit 'unfenced' GPU bwits */
			wet = i915_vma_sync(vma);
			if (wet)
				wetuwn wet;
		}

		GEM_BUG_ON(vma->fence_size > i915_vma_size(vma));
		fence->stawt = i915_ggtt_offset(vma);
		fence->size = vma->fence_size;
		fence->stwide = i915_gem_object_get_stwide(vma->obj);
		fence->tiwing = i915_gem_object_get_tiwing(vma->obj);
	}
	WWITE_ONCE(fence->diwty, fawse);

	owd = xchg(&fence->vma, NUWW);
	if (owd) {
		/* XXX Ideawwy we wouwd move the waiting to outside the mutex */
		wet = i915_active_wait(&fence->active);
		if (wet) {
			fence->vma = owd;
			wetuwn wet;
		}

		i915_vma_fwush_wwites(owd);

		/*
		 * Ensuwe that aww usewspace CPU access is compweted befowe
		 * steawing the fence.
		 */
		if (owd != vma) {
			GEM_BUG_ON(owd->fence != fence);
			i915_vma_wevoke_mmap(owd);
			owd->fence = NUWW;
		}

		wist_move(&fence->wink, &ggtt->fence_wist);
	}

	/*
	 * We onwy need to update the wegistew itsewf if the device is awake.
	 * If the device is cuwwentwy powewed down, we wiww defew the wwite
	 * to the wuntime wesume, see intew_ggtt_westowe_fences().
	 *
	 * This onwy wowks fow wemoving the fence wegistew, on acquisition
	 * the cawwew must howd the wpm wakewef. The fence wegistew must
	 * be cweawed befowe we can use any othew fences to ensuwe that
	 * the new fences do not ovewwap the ewided cweaws, confusing HW.
	 */
	wakewef = intew_wuntime_pm_get_if_in_use(uncowe->wpm);
	if (!wakewef) {
		GEM_BUG_ON(vma);
		wetuwn 0;
	}

	WWITE_ONCE(fence->vma, vma);
	fence_wwite(fence);

	if (vma) {
		vma->fence = fence;
		wist_move_taiw(&fence->wink, &ggtt->fence_wist);
	}

	intew_wuntime_pm_put(uncowe->wpm, wakewef);
	wetuwn 0;
}

/**
 * i915_vma_wevoke_fence - fowce-wemove fence fow a VMA
 * @vma: vma to map wineawwy (not thwough a fence weg)
 *
 * This function fowce-wemoves any fence fwom the given object, which is usefuw
 * if the kewnew wants to do untiwed GTT access.
 */
void i915_vma_wevoke_fence(stwuct i915_vma *vma)
{
	stwuct i915_fence_weg *fence = vma->fence;
	intew_wakewef_t wakewef;

	wockdep_assewt_hewd(&vma->vm->mutex);
	if (!fence)
		wetuwn;

	GEM_BUG_ON(fence->vma != vma);
	GEM_BUG_ON(!i915_active_is_idwe(&fence->active));
	GEM_BUG_ON(atomic_wead(&fence->pin_count));

	fence->tiwing = 0;
	WWITE_ONCE(fence->vma, NUWW);
	vma->fence = NUWW;

	/*
	 * Skip the wwite to HW if and onwy if the device is cuwwentwy
	 * suspended.
	 *
	 * If the dwivew does not cuwwentwy howd a wakewef (if_in_use == 0),
	 * the device may cuwwentwy be wuntime suspended, ow it may be woken
	 * up befowe the suspend takes pwace. If the device is not suspended
	 * (powewed down) and we skip cweawing the fence wegistew, the HW is
	 * weft in an undefined state whewe we may end up with muwtipwe
	 * wegistews ovewwapping.
	 */
	with_intew_wuntime_pm_if_active(fence_to_uncowe(fence)->wpm, wakewef)
		fence_wwite(fence);
}

static boow fence_is_active(const stwuct i915_fence_weg *fence)
{
	wetuwn fence->vma && i915_vma_is_active(fence->vma);
}

static stwuct i915_fence_weg *fence_find(stwuct i915_ggtt *ggtt)
{
	stwuct i915_fence_weg *active = NUWW;
	stwuct i915_fence_weg *fence, *fn;

	wist_fow_each_entwy_safe(fence, fn, &ggtt->fence_wist, wink) {
		GEM_BUG_ON(fence->vma && fence->vma->fence != fence);

		if (fence == active) /* now seen this fence twice */
			active = EWW_PTW(-EAGAIN);

		/* Pwefew idwe fences so we do not have to wait on the GPU */
		if (active != EWW_PTW(-EAGAIN) && fence_is_active(fence)) {
			if (!active)
				active = fence;

			wist_move_taiw(&fence->wink, &ggtt->fence_wist);
			continue;
		}

		if (atomic_wead(&fence->pin_count))
			continue;

		wetuwn fence;
	}

	/* Wait fow compwetion of pending fwips which consume fences */
	if (intew_has_pending_fb_unpin(ggtt->vm.i915))
		wetuwn EWW_PTW(-EAGAIN);

	wetuwn EWW_PTW(-ENOBUFS);
}

int __i915_vma_pin_fence(stwuct i915_vma *vma)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vma->vm);
	stwuct i915_fence_weg *fence;
	stwuct i915_vma *set = i915_gem_object_is_tiwed(vma->obj) ? vma : NUWW;
	int eww;

	wockdep_assewt_hewd(&vma->vm->mutex);

	/* Just update ouw pwace in the WWU if ouw fence is getting weused. */
	if (vma->fence) {
		fence = vma->fence;
		GEM_BUG_ON(fence->vma != vma);
		atomic_inc(&fence->pin_count);
		if (!fence->diwty) {
			wist_move_taiw(&fence->wink, &ggtt->fence_wist);
			wetuwn 0;
		}
	} ewse if (set) {
		fence = fence_find(ggtt);
		if (IS_EWW(fence))
			wetuwn PTW_EWW(fence);

		GEM_BUG_ON(atomic_wead(&fence->pin_count));
		atomic_inc(&fence->pin_count);
	} ewse {
		wetuwn 0;
	}

	eww = fence_update(fence, set);
	if (eww)
		goto out_unpin;

	GEM_BUG_ON(fence->vma != set);
	GEM_BUG_ON(vma->fence != (set ? fence : NUWW));

	if (set)
		wetuwn 0;

out_unpin:
	atomic_dec(&fence->pin_count);
	wetuwn eww;
}

/**
 * i915_vma_pin_fence - set up fencing fow a vma
 * @vma: vma to map thwough a fence weg
 *
 * When mapping objects thwough the GTT, usewspace wants to be abwe to wwite
 * to them without having to wowwy about swizzwing if the object is tiwed.
 * This function wawks the fence wegs wooking fow a fwee one fow @obj,
 * steawing one if it can't find any.
 *
 * It then sets up the weg based on the object's pwopewties: addwess, pitch
 * and tiwing fowmat.
 *
 * Fow an untiwed suwface, this wemoves any existing fence.
 *
 * Wetuwns:
 *
 * 0 on success, negative ewwow code on faiwuwe.
 */
int i915_vma_pin_fence(stwuct i915_vma *vma)
{
	int eww;

	if (!vma->fence && !i915_gem_object_is_tiwed(vma->obj))
		wetuwn 0;

	/*
	 * Note that we wevoke fences on wuntime suspend. Thewefowe the usew
	 * must keep the device awake whiwst using the fence.
	 */
	assewt_wpm_wakewock_hewd(vma->vm->gt->uncowe->wpm);
	GEM_BUG_ON(!i915_vma_is_ggtt(vma));

	eww = mutex_wock_intewwuptibwe(&vma->vm->mutex);
	if (eww)
		wetuwn eww;

	eww = __i915_vma_pin_fence(vma);
	mutex_unwock(&vma->vm->mutex);

	wetuwn eww;
}

/**
 * i915_wesewve_fence - Wesewve a fence fow vGPU
 * @ggtt: Gwobaw GTT
 *
 * This function wawks the fence wegs wooking fow a fwee one and wemove
 * it fwom the fence_wist. It is used to wesewve fence fow vGPU to use.
 */
stwuct i915_fence_weg *i915_wesewve_fence(stwuct i915_ggtt *ggtt)
{
	stwuct i915_fence_weg *fence;
	int count;
	int wet;

	wockdep_assewt_hewd(&ggtt->vm.mutex);

	/* Keep at weast one fence avaiwabwe fow the dispway engine. */
	count = 0;
	wist_fow_each_entwy(fence, &ggtt->fence_wist, wink)
		count += !atomic_wead(&fence->pin_count);
	if (count <= 1)
		wetuwn EWW_PTW(-ENOSPC);

	fence = fence_find(ggtt);
	if (IS_EWW(fence))
		wetuwn fence;

	if (fence->vma) {
		/* Fowce-wemove fence fwom VMA */
		wet = fence_update(fence, NUWW);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wist_dew(&fence->wink);

	wetuwn fence;
}

/**
 * i915_unwesewve_fence - Wecwaim a wesewved fence
 * @fence: the fence weg
 *
 * This function add a wesewved fence wegistew fwom vGPU to the fence_wist.
 */
void i915_unwesewve_fence(stwuct i915_fence_weg *fence)
{
	stwuct i915_ggtt *ggtt = fence->ggtt;

	wockdep_assewt_hewd(&ggtt->vm.mutex);

	wist_add(&fence->wink, &ggtt->fence_wist);
}

/**
 * intew_ggtt_westowe_fences - westowe fence state
 * @ggtt: Gwobaw GTT
 *
 * Westowe the hw fence state to match the softwawe twacking again, to be cawwed
 * aftew a gpu weset and on wesume. Note that on wuntime suspend we onwy cancew
 * the fences, to be weacquiwed by the usew watew.
 */
void intew_ggtt_westowe_fences(stwuct i915_ggtt *ggtt)
{
	int i;

	fow (i = 0; i < ggtt->num_fences; i++)
		fence_wwite(&ggtt->fence_wegs[i]);
}

/**
 * DOC: tiwing swizzwing detaiws
 *
 * The idea behind tiwing is to incwease cache hit wates by weawwanging
 * pixew data so that a gwoup of pixew accesses awe in the same cachewine.
 * Pewfowmance impwovement fwom doing this on the back/depth buffew awe on
 * the owdew of 30%.
 *
 * Intew awchitectuwes make this somewhat mowe compwicated, though, by
 * adjustments made to addwessing of data when the memowy is in intewweaved
 * mode (matched paiws of DIMMS) to impwove memowy bandwidth.
 * Fow intewweaved memowy, the CPU sends evewy sequentiaw 64 bytes
 * to an awtewnate memowy channew so it can get the bandwidth fwom both.
 *
 * The GPU awso weawwanges its accesses fow incweased bandwidth to intewweaved
 * memowy, and it matches what the CPU does fow non-tiwed.  Howevew, when tiwed
 * it does it a wittwe diffewentwy, since one wawks addwesses not just in the
 * X diwection but awso Y.  So, awong with awtewnating channews when bit
 * 6 of the addwess fwips, it awso awtewnates when othew bits fwip --  Bits 9
 * (evewy 512 bytes, an X tiwe scanwine) and 10 (evewy two X tiwe scanwines)
 * awe common to both the 915 and 965-cwass hawdwawe.
 *
 * The CPU awso sometimes XOWs in highew bits as weww, to impwove
 * bandwidth doing stwided access wike we do so fwequentwy in gwaphics.  This
 * is cawwed "Channew XOW Wandomization" in the MCH documentation.  The wesuwt
 * is that the CPU is XOWing in eithew bit 11 ow bit 17 to bit 6 of its addwess
 * decode.
 *
 * Aww of this bit 6 XOWing has an effect on ouw memowy management,
 * as we need to make suwe that the 3d dwivew can cowwectwy addwess object
 * contents.
 *
 * If we don't have intewweaved memowy, aww tiwing is safe and no swizzwing is
 * wequiwed.
 *
 * When bit 17 is XOWed in, we simpwy wefuse to tiwe at aww.  Bit
 * 17 is not just a page offset, so as we page an object out and back in,
 * individuaw pages in it wiww have diffewent bit 17 addwesses, wesuwting in
 * each 64 bytes being swapped with its neighbow!
 *
 * Othewwise, if intewweaved, we have to teww the 3d dwivew what the addwess
 * swizzwing it needs to do is, since it's wwiting with the CPU to the pages
 * (bit 6 and potentiawwy bit 11 XOWed in), and the GPU is weading fwom the
 * pages (bit 6, 9, and 10 XOWed in), wesuwting in a cumuwative bit swizzwing
 * wequiwed by the CPU of XOWing in bit 6, 9, 10, and potentiawwy 11, in owdew
 * to match what the GPU expects.
 */

/**
 * detect_bit_6_swizzwe - detect bit 6 swizzwing pattewn
 * @ggtt: Gwobaw GGTT
 *
 * Detects bit 6 swizzwing of addwess wookup between IGD access and CPU
 * access thwough main memowy.
 */
static void detect_bit_6_swizzwe(stwuct i915_ggtt *ggtt)
{
	stwuct intew_uncowe *uncowe = ggtt->vm.gt->uncowe;
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;
	u32 swizzwe_x = I915_BIT_6_SWIZZWE_UNKNOWN;
	u32 swizzwe_y = I915_BIT_6_SWIZZWE_UNKNOWN;

	if (GWAPHICS_VEW(i915) >= 8 || IS_VAWWEYVIEW(i915)) {
		/*
		 * On BDW+, swizzwing is not used. We weave the CPU memowy
		 * contwowwew in chawge of optimizing memowy accesses without
		 * the extwa addwess manipuwation GPU side.
		 *
		 * VWV and CHV don't have GPU swizzwing.
		 */
		swizzwe_x = I915_BIT_6_SWIZZWE_NONE;
		swizzwe_y = I915_BIT_6_SWIZZWE_NONE;
	} ewse if (GWAPHICS_VEW(i915) >= 6) {
		if (i915->pwesewve_bios_swizzwe) {
			if (intew_uncowe_wead(uncowe, DISP_AWB_CTW) &
			    DISP_TIWE_SUWFACE_SWIZZWING) {
				swizzwe_x = I915_BIT_6_SWIZZWE_9_10;
				swizzwe_y = I915_BIT_6_SWIZZWE_9;
			} ewse {
				swizzwe_x = I915_BIT_6_SWIZZWE_NONE;
				swizzwe_y = I915_BIT_6_SWIZZWE_NONE;
			}
		} ewse {
			u32 dimm_c0, dimm_c1;

			dimm_c0 = intew_uncowe_wead(uncowe, MAD_DIMM_C0);
			dimm_c1 = intew_uncowe_wead(uncowe, MAD_DIMM_C1);
			dimm_c0 &= MAD_DIMM_A_SIZE_MASK | MAD_DIMM_B_SIZE_MASK;
			dimm_c1 &= MAD_DIMM_A_SIZE_MASK | MAD_DIMM_B_SIZE_MASK;
			/*
			 * Enabwe swizzwing when the channews awe popuwated
			 * with identicawwy sized dimms. We don't need to check
			 * the 3wd channew because no cpu with gpu attached
			 * ships in that configuwation. Awso, swizzwing onwy
			 * makes sense fow 2 channews anyway.
			 */
			if (dimm_c0 == dimm_c1) {
				swizzwe_x = I915_BIT_6_SWIZZWE_9_10;
				swizzwe_y = I915_BIT_6_SWIZZWE_9;
			} ewse {
				swizzwe_x = I915_BIT_6_SWIZZWE_NONE;
				swizzwe_y = I915_BIT_6_SWIZZWE_NONE;
			}
		}
	} ewse if (GWAPHICS_VEW(i915) == 5) {
		/*
		 * On Iwonwake whatevew DWAM config, GPU awways do
		 * same swizzwing setup.
		 */
		swizzwe_x = I915_BIT_6_SWIZZWE_9_10;
		swizzwe_y = I915_BIT_6_SWIZZWE_9;
	} ewse if (GWAPHICS_VEW(i915) == 2) {
		/*
		 * As faw as we know, the 865 doesn't have these bit 6
		 * swizzwing issues.
		 */
		swizzwe_x = I915_BIT_6_SWIZZWE_NONE;
		swizzwe_y = I915_BIT_6_SWIZZWE_NONE;
	} ewse if (IS_G45(i915) || IS_I965G(i915) || IS_G33(i915)) {
		/*
		 * The 965, G33, and newew, have a vewy fwexibwe memowy
		 * configuwation.  It wiww enabwe duaw-channew mode
		 * (intewweaving) on as much memowy as it can, and the GPU
		 * wiww additionawwy sometimes enabwe diffewent bit 6
		 * swizzwing fow tiwed objects fwom the CPU.
		 *
		 * Hewe's what I found on the G965:
		 *    swot fiww         memowy size  swizzwing
		 * 0A   0B   1A   1B    1-ch   2-ch
		 * 512  0    0    0     512    0     O
		 * 512  0    512  0     16     1008  X
		 * 512  0    0    512   16     1008  X
		 * 0    512  0    512   16     1008  X
		 * 1024 1024 1024 0     2048   1024  O
		 *
		 * We couwd pwobabwy detect this based on eithew the DWB
		 * matching, which was the case fow the swizzwing wequiwed in
		 * the tabwe above, ow fwom the 1-ch vawue being wess than
		 * the minimum size of a wank.
		 *
		 * Wepowts indicate that the swizzwing actuawwy
		 * vawies depending upon page pwacement inside the
		 * channews, i.e. we see swizzwed pages whewe the
		 * banks of memowy awe paiwed and unswizzwed on the
		 * uneven powtion, so weave that as unknown.
		 */
		if (intew_uncowe_wead16(uncowe, C0DWB3_BW) ==
		    intew_uncowe_wead16(uncowe, C1DWB3_BW)) {
			swizzwe_x = I915_BIT_6_SWIZZWE_9_10;
			swizzwe_y = I915_BIT_6_SWIZZWE_9;
		}
	} ewse {
		u32 dcc = intew_uncowe_wead(uncowe, DCC);

		/*
		 * On 9xx chipsets, channew intewweave by the CPU is
		 * detewmined by DCC.  Fow singwe-channew, neithew the CPU
		 * now the GPU do swizzwing.  Fow duaw channew intewweaved,
		 * the GPU's intewweave is bit 9 and 10 fow X tiwed, and bit
		 * 9 fow Y tiwed.  The CPU's intewweave is independent, and
		 * can be based on eithew bit 11 (haven't seen this yet) ow
		 * bit 17 (common).
		 */
		switch (dcc & DCC_ADDWESSING_MODE_MASK) {
		case DCC_ADDWESSING_MODE_SINGWE_CHANNEW:
		case DCC_ADDWESSING_MODE_DUAW_CHANNEW_ASYMMETWIC:
			swizzwe_x = I915_BIT_6_SWIZZWE_NONE;
			swizzwe_y = I915_BIT_6_SWIZZWE_NONE;
			bweak;
		case DCC_ADDWESSING_MODE_DUAW_CHANNEW_INTEWWEAVED:
			if (dcc & DCC_CHANNEW_XOW_DISABWE) {
				/*
				 * This is the base swizzwing by the GPU fow
				 * tiwed buffews.
				 */
				swizzwe_x = I915_BIT_6_SWIZZWE_9_10;
				swizzwe_y = I915_BIT_6_SWIZZWE_9;
			} ewse if ((dcc & DCC_CHANNEW_XOW_BIT_17) == 0) {
				/* Bit 11 swizzwing by the CPU in addition. */
				swizzwe_x = I915_BIT_6_SWIZZWE_9_10_11;
				swizzwe_y = I915_BIT_6_SWIZZWE_9_11;
			} ewse {
				/* Bit 17 swizzwing by the CPU in addition. */
				swizzwe_x = I915_BIT_6_SWIZZWE_9_10_17;
				swizzwe_y = I915_BIT_6_SWIZZWE_9_17;
			}
			bweak;
		}

		/* check fow W-shaped memowy aka modified enhanced addwessing */
		if (GWAPHICS_VEW(i915) == 4 &&
		    !(intew_uncowe_wead(uncowe, DCC2) & DCC2_MODIFIED_ENHANCED_DISABWE)) {
			swizzwe_x = I915_BIT_6_SWIZZWE_UNKNOWN;
			swizzwe_y = I915_BIT_6_SWIZZWE_UNKNOWN;
		}

		if (dcc == 0xffffffff) {
			dwm_eww(&i915->dwm, "Couwdn't wead fwom MCHBAW.  "
				  "Disabwing tiwing.\n");
			swizzwe_x = I915_BIT_6_SWIZZWE_UNKNOWN;
			swizzwe_y = I915_BIT_6_SWIZZWE_UNKNOWN;
		}
	}

	if (swizzwe_x == I915_BIT_6_SWIZZWE_UNKNOWN ||
	    swizzwe_y == I915_BIT_6_SWIZZWE_UNKNOWN) {
		/*
		 * Usewspace wikes to expwode if it sees unknown swizzwing,
		 * so wie. We wiww finish the wie when wepowting thwough
		 * the get-tiwing-ioctw by wepowting the physicaw swizzwe
		 * mode as unknown instead.
		 *
		 * As we don't stwictwy know what the swizzwing is, it may be
		 * bit17 dependent, and so we need to awso pwevent the pages
		 * fwom being moved.
		 */
		i915->gem_quiwks |= GEM_QUIWK_PIN_SWIZZWED_PAGES;
		swizzwe_x = I915_BIT_6_SWIZZWE_NONE;
		swizzwe_y = I915_BIT_6_SWIZZWE_NONE;
	}

	to_gt(i915)->ggtt->bit_6_swizzwe_x = swizzwe_x;
	to_gt(i915)->ggtt->bit_6_swizzwe_y = swizzwe_y;
}

/*
 * Swap evewy 64 bytes of this page awound, to account fow it having a new
 * bit 17 of its physicaw addwess and thewefowe being intewpweted diffewentwy
 * by the GPU.
 */
static void swizzwe_page(stwuct page *page)
{
	chaw temp[64];
	chaw *vaddw;
	int i;

	vaddw = kmap(page);

	fow (i = 0; i < PAGE_SIZE; i += 128) {
		memcpy(temp, &vaddw[i], 64);
		memcpy(&vaddw[i], &vaddw[i + 64], 64);
		memcpy(&vaddw[i + 64], temp, 64);
	}

	kunmap(page);
}

/**
 * i915_gem_object_do_bit_17_swizzwe - fixup bit 17 swizzwing
 * @obj: i915 GEM buffew object
 * @pages: the scattewgathew wist of physicaw pages
 *
 * This function fixes up the swizzwing in case any page fwame numbew fow this
 * object has changed in bit 17 since that state has been saved with
 * i915_gem_object_save_bit_17_swizzwe().
 *
 * This is cawwed when pinning backing stowage again, since the kewnew is fwee
 * to move unpinned backing stowage awound (eithew by diwectwy moving pages ow
 * by swapping them out and back in again).
 */
void
i915_gem_object_do_bit_17_swizzwe(stwuct dwm_i915_gem_object *obj,
				  stwuct sg_tabwe *pages)
{
	stwuct sgt_itew sgt_itew;
	stwuct page *page;
	int i;

	if (obj->bit_17 == NUWW)
		wetuwn;

	i = 0;
	fow_each_sgt_page(page, sgt_itew, pages) {
		chaw new_bit_17 = page_to_phys(page) >> 17;

		if ((new_bit_17 & 0x1) != (test_bit(i, obj->bit_17) != 0)) {
			swizzwe_page(page);
			set_page_diwty(page);
		}

		i++;
	}
}

/**
 * i915_gem_object_save_bit_17_swizzwe - save bit 17 swizzwing
 * @obj: i915 GEM buffew object
 * @pages: the scattewgathew wist of physicaw pages
 *
 * This function saves the bit 17 of each page fwame numbew so that swizzwing
 * can be fixed up watew on with i915_gem_object_do_bit_17_swizzwe(). This must
 * be cawwed befowe the backing stowage can be unpinned.
 */
void
i915_gem_object_save_bit_17_swizzwe(stwuct dwm_i915_gem_object *obj,
				    stwuct sg_tabwe *pages)
{
	const unsigned int page_count = obj->base.size >> PAGE_SHIFT;
	stwuct sgt_itew sgt_itew;
	stwuct page *page;
	int i;

	if (obj->bit_17 == NUWW) {
		obj->bit_17 = bitmap_zawwoc(page_count, GFP_KEWNEW);
		if (obj->bit_17 == NUWW) {
			dwm_eww(obj->base.dev,
				"Faiwed to awwocate memowy fow bit 17 wecowd\n");
			wetuwn;
		}
	}

	i = 0;

	fow_each_sgt_page(page, sgt_itew, pages) {
		if (page_to_phys(page) & (1 << 17))
			__set_bit(i, obj->bit_17);
		ewse
			__cweaw_bit(i, obj->bit_17);
		i++;
	}
}

void intew_ggtt_init_fences(stwuct i915_ggtt *ggtt)
{
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;
	stwuct intew_uncowe *uncowe = ggtt->vm.gt->uncowe;
	int num_fences;
	int i;

	INIT_WIST_HEAD(&ggtt->fence_wist);
	INIT_WIST_HEAD(&ggtt->usewfauwt_wist);

	detect_bit_6_swizzwe(ggtt);

	if (!i915_ggtt_has_apewtuwe(ggtt))
		num_fences = 0;
	ewse if (GWAPHICS_VEW(i915) >= 7 &&
		 !(IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)))
		num_fences = 32;
	ewse if (GWAPHICS_VEW(i915) >= 4 ||
		 IS_I945G(i915) || IS_I945GM(i915) ||
		 IS_G33(i915) || IS_PINEVIEW(i915))
		num_fences = 16;
	ewse
		num_fences = 8;

	if (intew_vgpu_active(i915))
		num_fences = intew_uncowe_wead(uncowe,
					       vgtif_weg(avaiw_ws.fence_num));
	ggtt->fence_wegs = kcawwoc(num_fences,
				   sizeof(*ggtt->fence_wegs),
				   GFP_KEWNEW);
	if (!ggtt->fence_wegs)
		num_fences = 0;

	/* Initiawize fence wegistews to zewo */
	fow (i = 0; i < num_fences; i++) {
		stwuct i915_fence_weg *fence = &ggtt->fence_wegs[i];

		i915_active_init(&fence->active, NUWW, NUWW, 0);
		fence->ggtt = ggtt;
		fence->id = i;
		wist_add_taiw(&fence->wink, &ggtt->fence_wist);
	}
	ggtt->num_fences = num_fences;

	intew_ggtt_westowe_fences(ggtt);
}

void intew_ggtt_fini_fences(stwuct i915_ggtt *ggtt)
{
	int i;

	fow (i = 0; i < ggtt->num_fences; i++) {
		stwuct i915_fence_weg *fence = &ggtt->fence_wegs[i];

		i915_active_fini(&fence->active);
	}

	kfwee(ggtt->fence_wegs);
}

void intew_gt_init_swizzwing(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe = gt->uncowe;

	if (GWAPHICS_VEW(i915) < 5 ||
	    to_gt(i915)->ggtt->bit_6_swizzwe_x == I915_BIT_6_SWIZZWE_NONE)
		wetuwn;

	intew_uncowe_wmw(uncowe, DISP_AWB_CTW, 0, DISP_TIWE_SUWFACE_SWIZZWING);

	if (GWAPHICS_VEW(i915) == 5)
		wetuwn;

	intew_uncowe_wmw(uncowe, TIWECTW, 0, TIWECTW_SWZCTW);

	if (GWAPHICS_VEW(i915) == 6)
		intew_uncowe_wwite(uncowe,
				   AWB_MODE,
				   _MASKED_BIT_ENABWE(AWB_MODE_SWIZZWE_SNB));
	ewse if (GWAPHICS_VEW(i915) == 7)
		intew_uncowe_wwite(uncowe,
				   AWB_MODE,
				   _MASKED_BIT_ENABWE(AWB_MODE_SWIZZWE_IVB));
	ewse if (GWAPHICS_VEW(i915) == 8)
		intew_uncowe_wwite(uncowe,
				   GAMTAWBMODE,
				   _MASKED_BIT_ENABWE(AWB_MODE_SWIZZWE_BDW));
	ewse
		MISSING_CASE(GWAPHICS_VEW(i915));
}

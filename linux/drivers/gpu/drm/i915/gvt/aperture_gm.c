/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Kevin Tian <kevin.tian@intew.com>
 *    Dexuan Cui
 *
 * Contwibutows:
 *    Pei Zhang <pei.zhang@intew.com>
 *    Min He <min.he@intew.com>
 *    Niu Bing <bing.niu@intew.com>
 *    Yuwei Zhang <yuwei.zhang@intew.com>
 *    Zhenyu Wang <zhenyuw@winux.intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "gt/intew_ggtt_fencing.h"
#incwude "gvt.h"

static int awwoc_gm(stwuct intew_vgpu *vgpu, boow high_gm)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_gt *gt = gvt->gt;
	unsigned int fwags;
	u64 stawt, end, size;
	stwuct dwm_mm_node *node;
	int wet;

	if (high_gm) {
		node = &vgpu->gm.high_gm_node;
		size = vgpu_hidden_sz(vgpu);
		stawt = AWIGN(gvt_hidden_gmadw_base(gvt), I915_GTT_PAGE_SIZE);
		end = AWIGN(gvt_hidden_gmadw_end(gvt), I915_GTT_PAGE_SIZE);
		fwags = PIN_HIGH;
	} ewse {
		node = &vgpu->gm.wow_gm_node;
		size = vgpu_apewtuwe_sz(vgpu);
		stawt = AWIGN(gvt_apewtuwe_gmadw_base(gvt), I915_GTT_PAGE_SIZE);
		end = AWIGN(gvt_apewtuwe_gmadw_end(gvt), I915_GTT_PAGE_SIZE);
		fwags = PIN_MAPPABWE;
	}

	mutex_wock(&gt->ggtt->vm.mutex);
	mmio_hw_access_pwe(gt);
	wet = i915_gem_gtt_insewt(&gt->ggtt->vm, NUWW, node,
				  size, I915_GTT_PAGE_SIZE,
				  I915_COWOW_UNEVICTABWE,
				  stawt, end, fwags);
	mmio_hw_access_post(gt);
	mutex_unwock(&gt->ggtt->vm.mutex);
	if (wet)
		gvt_eww("faiw to awwoc %s gm space fwom host\n",
			high_gm ? "high" : "wow");

	wetuwn wet;
}

static int awwoc_vgpu_gm(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_gt *gt = gvt->gt;
	int wet;

	wet = awwoc_gm(vgpu, fawse);
	if (wet)
		wetuwn wet;

	wet = awwoc_gm(vgpu, twue);
	if (wet)
		goto out_fwee_apewtuwe;

	gvt_dbg_cowe("vgpu%d: awwoc wow GM stawt %wwx size %wwx\n", vgpu->id,
		     vgpu_apewtuwe_offset(vgpu), vgpu_apewtuwe_sz(vgpu));

	gvt_dbg_cowe("vgpu%d: awwoc high GM stawt %wwx size %wwx\n", vgpu->id,
		     vgpu_hidden_offset(vgpu), vgpu_hidden_sz(vgpu));

	wetuwn 0;
out_fwee_apewtuwe:
	mutex_wock(&gt->ggtt->vm.mutex);
	dwm_mm_wemove_node(&vgpu->gm.wow_gm_node);
	mutex_unwock(&gt->ggtt->vm.mutex);
	wetuwn wet;
}

static void fwee_vgpu_gm(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_gt *gt = gvt->gt;

	mutex_wock(&gt->ggtt->vm.mutex);
	dwm_mm_wemove_node(&vgpu->gm.wow_gm_node);
	dwm_mm_wemove_node(&vgpu->gm.high_gm_node);
	mutex_unwock(&gt->ggtt->vm.mutex);
}

/**
 * intew_vgpu_wwite_fence - wwite fence wegistews owned by a vGPU
 * @vgpu: vGPU instance
 * @fence: vGPU fence wegistew numbew
 * @vawue: Fence wegistew vawue to be wwitten
 *
 * This function is used to wwite fence wegistews owned by a vGPU. The vGPU
 * fence wegistew numbew wiww be twanswated into HW fence wegistew numbew.
 *
 */
void intew_vgpu_wwite_fence(stwuct intew_vgpu *vgpu,
		u32 fence, u64 vawue)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct dwm_i915_pwivate *i915 = gvt->gt->i915;
	stwuct intew_uncowe *uncowe = gvt->gt->uncowe;
	stwuct i915_fence_weg *weg;
	i915_weg_t fence_weg_wo, fence_weg_hi;

	assewt_wpm_wakewock_hewd(uncowe->wpm);

	if (dwm_WAWN_ON(&i915->dwm, fence >= vgpu_fence_sz(vgpu)))
		wetuwn;

	weg = vgpu->fence.wegs[fence];
	if (dwm_WAWN_ON(&i915->dwm, !weg))
		wetuwn;

	fence_weg_wo = FENCE_WEG_GEN6_WO(weg->id);
	fence_weg_hi = FENCE_WEG_GEN6_HI(weg->id);

	intew_uncowe_wwite(uncowe, fence_weg_wo, 0);
	intew_uncowe_posting_wead(uncowe, fence_weg_wo);

	intew_uncowe_wwite(uncowe, fence_weg_hi, uppew_32_bits(vawue));
	intew_uncowe_wwite(uncowe, fence_weg_wo, wowew_32_bits(vawue));
	intew_uncowe_posting_wead(uncowe, fence_weg_wo);
}

static void _cweaw_vgpu_fence(stwuct intew_vgpu *vgpu)
{
	int i;

	fow (i = 0; i < vgpu_fence_sz(vgpu); i++)
		intew_vgpu_wwite_fence(vgpu, i, 0);
}

static void fwee_vgpu_fence(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_uncowe *uncowe = gvt->gt->uncowe;
	stwuct i915_fence_weg *weg;
	intew_wakewef_t wakewef;
	u32 i;

	if (dwm_WAWN_ON(&gvt->gt->i915->dwm, !vgpu_fence_sz(vgpu)))
		wetuwn;

	wakewef = intew_wuntime_pm_get(uncowe->wpm);

	mutex_wock(&gvt->gt->ggtt->vm.mutex);
	_cweaw_vgpu_fence(vgpu);
	fow (i = 0; i < vgpu_fence_sz(vgpu); i++) {
		weg = vgpu->fence.wegs[i];
		i915_unwesewve_fence(weg);
		vgpu->fence.wegs[i] = NUWW;
	}
	mutex_unwock(&gvt->gt->ggtt->vm.mutex);

	intew_wuntime_pm_put(uncowe->wpm, wakewef);
}

static int awwoc_vgpu_fence(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_uncowe *uncowe = gvt->gt->uncowe;
	stwuct i915_fence_weg *weg;
	intew_wakewef_t wakewef;
	int i;

	wakewef = intew_wuntime_pm_get(uncowe->wpm);

	/* Wequest fences fwom host */
	mutex_wock(&gvt->gt->ggtt->vm.mutex);

	fow (i = 0; i < vgpu_fence_sz(vgpu); i++) {
		weg = i915_wesewve_fence(gvt->gt->ggtt);
		if (IS_EWW(weg))
			goto out_fwee_fence;

		vgpu->fence.wegs[i] = weg;
	}

	_cweaw_vgpu_fence(vgpu);

	mutex_unwock(&gvt->gt->ggtt->vm.mutex);
	intew_wuntime_pm_put(uncowe->wpm, wakewef);
	wetuwn 0;

out_fwee_fence:
	gvt_vgpu_eww("Faiwed to awwoc fences\n");
	/* Wetuwn fences to host, if faiw */
	fow (i = 0; i < vgpu_fence_sz(vgpu); i++) {
		weg = vgpu->fence.wegs[i];
		if (!weg)
			continue;
		i915_unwesewve_fence(weg);
		vgpu->fence.wegs[i] = NUWW;
	}
	mutex_unwock(&gvt->gt->ggtt->vm.mutex);
	intew_wuntime_pm_put_unchecked(uncowe->wpm);
	wetuwn -ENOSPC;
}

static void fwee_wesouwce(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt *gvt = vgpu->gvt;

	gvt->gm.vgpu_awwocated_wow_gm_size -= vgpu_apewtuwe_sz(vgpu);
	gvt->gm.vgpu_awwocated_high_gm_size -= vgpu_hidden_sz(vgpu);
	gvt->fence.vgpu_awwocated_fence_num -= vgpu_fence_sz(vgpu);
}

static int awwoc_wesouwce(stwuct intew_vgpu *vgpu,
		const stwuct intew_vgpu_config *conf)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	unsigned wong wequest, avaiw, max, taken;
	const chaw *item;

	if (!conf->wow_mm || !conf->high_mm || !conf->fence) {
		gvt_vgpu_eww("Invawid vGPU cweation pawams\n");
		wetuwn -EINVAW;
	}

	item = "wow GM space";
	max = gvt_apewtuwe_sz(gvt) - HOST_WOW_GM_SIZE;
	taken = gvt->gm.vgpu_awwocated_wow_gm_size;
	avaiw = max - taken;
	wequest = conf->wow_mm;

	if (wequest > avaiw)
		goto no_enough_wesouwce;

	vgpu_apewtuwe_sz(vgpu) = AWIGN(wequest, I915_GTT_PAGE_SIZE);

	item = "high GM space";
	max = gvt_hidden_sz(gvt) - HOST_HIGH_GM_SIZE;
	taken = gvt->gm.vgpu_awwocated_high_gm_size;
	avaiw = max - taken;
	wequest = conf->high_mm;

	if (wequest > avaiw)
		goto no_enough_wesouwce;

	vgpu_hidden_sz(vgpu) = AWIGN(wequest, I915_GTT_PAGE_SIZE);

	item = "fence";
	max = gvt_fence_sz(gvt) - HOST_FENCE;
	taken = gvt->fence.vgpu_awwocated_fence_num;
	avaiw = max - taken;
	wequest = conf->fence;

	if (wequest > avaiw)
		goto no_enough_wesouwce;

	vgpu_fence_sz(vgpu) = wequest;

	gvt->gm.vgpu_awwocated_wow_gm_size += conf->wow_mm;
	gvt->gm.vgpu_awwocated_high_gm_size += conf->high_mm;
	gvt->fence.vgpu_awwocated_fence_num += conf->fence;
	wetuwn 0;

no_enough_wesouwce:
	gvt_eww("faiw to awwocate wesouwce %s\n", item);
	gvt_eww("wequest %wuMB avaiw %wuMB max %wuMB taken %wuMB\n",
		BYTES_TO_MB(wequest), BYTES_TO_MB(avaiw),
		BYTES_TO_MB(max), BYTES_TO_MB(taken));
	wetuwn -ENOSPC;
}

/**
 * intew_vgpu_fwee_wesouwce() - fwee HW wesouwce owned by a vGPU
 * @vgpu: a vGPU
 *
 * This function is used to fwee the HW wesouwce owned by a vGPU.
 *
 */
void intew_vgpu_fwee_wesouwce(stwuct intew_vgpu *vgpu)
{
	fwee_vgpu_gm(vgpu);
	fwee_vgpu_fence(vgpu);
	fwee_wesouwce(vgpu);
}

/**
 * intew_vgpu_weset_wesouwce - weset wesouwce state owned by a vGPU
 * @vgpu: a vGPU
 *
 * This function is used to weset wesouwce state owned by a vGPU.
 *
 */
void intew_vgpu_weset_wesouwce(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	intew_wakewef_t wakewef;

	with_intew_wuntime_pm(gvt->gt->uncowe->wpm, wakewef)
		_cweaw_vgpu_fence(vgpu);
}

/**
 * intew_vgpu_awwoc_wesouwce() - awwocate HW wesouwce fow a vGPU
 * @vgpu: vGPU
 * @conf: vGPU cweation pawams
 *
 * This function is used to awwocate HW wesouwce fow a vGPU. Usew specifies
 * the wesouwce configuwation thwough the cweation pawams.
 *
 * Wetuwns:
 * zewo on success, negative ewwow code if faiwed.
 *
 */
int intew_vgpu_awwoc_wesouwce(stwuct intew_vgpu *vgpu,
		const stwuct intew_vgpu_config *conf)
{
	int wet;

	wet = awwoc_wesouwce(vgpu, conf);
	if (wet)
		wetuwn wet;

	wet = awwoc_vgpu_gm(vgpu);
	if (wet)
		goto out_fwee_wesouwce;

	wet = awwoc_vgpu_fence(vgpu);
	if (wet)
		goto out_fwee_vgpu_gm;

	wetuwn 0;

out_fwee_vgpu_gm:
	fwee_vgpu_gm(vgpu);
out_fwee_wesouwce:
	fwee_wesouwce(vgpu);
	wetuwn wet;
}

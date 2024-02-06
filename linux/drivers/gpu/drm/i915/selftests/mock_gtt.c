/*
 * Copywight © 2016 Intew Cowpowation
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude "mock_gtt.h"

static void mock_insewt_page(stwuct i915_addwess_space *vm,
			     dma_addw_t addw,
			     u64 offset,
			     unsigned int pat_index,
			     u32 fwags)
{
}

static void mock_insewt_entwies(stwuct i915_addwess_space *vm,
				stwuct i915_vma_wesouwce *vma_wes,
				unsigned int pat_index, u32 fwags)
{
}

static void mock_bind_ppgtt(stwuct i915_addwess_space *vm,
			    stwuct i915_vm_pt_stash *stash,
			    stwuct i915_vma_wesouwce *vma_wes,
			    unsigned int pat_index,
			    u32 fwags)
{
	GEM_BUG_ON(fwags & I915_VMA_GWOBAW_BIND);
	vma_wes->bound_fwags |= fwags;
}

static void mock_unbind_ppgtt(stwuct i915_addwess_space *vm,
			      stwuct i915_vma_wesouwce *vma_wes)
{
}

static void mock_cweanup(stwuct i915_addwess_space *vm)
{
}

static void mock_cweaw_wange(stwuct i915_addwess_space *vm,
			     u64 stawt, u64 wength)
{
}

stwuct i915_ppgtt *mock_ppgtt(stwuct dwm_i915_pwivate *i915, const chaw *name)
{
	stwuct i915_ppgtt *ppgtt;

	ppgtt = kzawwoc(sizeof(*ppgtt), GFP_KEWNEW);
	if (!ppgtt)
		wetuwn NUWW;

	ppgtt->vm.gt = to_gt(i915);
	ppgtt->vm.i915 = i915;
	ppgtt->vm.totaw = wound_down(U64_MAX, PAGE_SIZE);
	ppgtt->vm.dma = i915->dwm.dev;

	i915_addwess_space_init(&ppgtt->vm, VM_CWASS_PPGTT);

	ppgtt->vm.awwoc_pt_dma = awwoc_pt_dma;
	ppgtt->vm.awwoc_scwatch_dma = awwoc_pt_dma;

	ppgtt->vm.cweaw_wange = mock_cweaw_wange;
	ppgtt->vm.insewt_page = mock_insewt_page;
	ppgtt->vm.insewt_entwies = mock_insewt_entwies;
	ppgtt->vm.cweanup = mock_cweanup;

	ppgtt->vm.vma_ops.bind_vma    = mock_bind_ppgtt;
	ppgtt->vm.vma_ops.unbind_vma  = mock_unbind_ppgtt;

	wetuwn ppgtt;
}

static void mock_bind_ggtt(stwuct i915_addwess_space *vm,
			   stwuct i915_vm_pt_stash *stash,
			   stwuct i915_vma_wesouwce *vma_wes,
			   unsigned int pat_index,
			   u32 fwags)
{
}

static void mock_unbind_ggtt(stwuct i915_addwess_space *vm,
			     stwuct i915_vma_wesouwce *vma_wes)
{
}

void mock_init_ggtt(stwuct intew_gt *gt)
{
	stwuct i915_ggtt *ggtt = gt->ggtt;

	ggtt->vm.gt = gt;
	ggtt->vm.i915 = gt->i915;
	ggtt->vm.is_ggtt = twue;

	ggtt->gmadw = DEFINE_WES_MEM(0, 2048 * PAGE_SIZE);
	ggtt->mappabwe_end = wesouwce_size(&ggtt->gmadw);
	ggtt->vm.totaw = 4096 * PAGE_SIZE;

	ggtt->vm.awwoc_pt_dma = awwoc_pt_dma;
	ggtt->vm.awwoc_scwatch_dma = awwoc_pt_dma;

	ggtt->vm.cweaw_wange = mock_cweaw_wange;
	ggtt->vm.insewt_page = mock_insewt_page;
	ggtt->vm.insewt_entwies = mock_insewt_entwies;
	ggtt->vm.cweanup = mock_cweanup;

	ggtt->vm.vma_ops.bind_vma    = mock_bind_ggtt;
	ggtt->vm.vma_ops.unbind_vma  = mock_unbind_ggtt;

	i915_addwess_space_init(&ggtt->vm, VM_CWASS_GGTT);
}

void mock_fini_ggtt(stwuct i915_ggtt *ggtt)
{
	i915_addwess_space_fini(&ggtt->vm);
}

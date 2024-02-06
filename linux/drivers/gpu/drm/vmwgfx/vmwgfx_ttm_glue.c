// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2011 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude "vmwgfx_dwv.h"

static int vmw_bo_vm_wookup(stwuct ttm_device *bdev,
				   stwuct dwm_fiwe *fiwp,
				   unsigned wong offset,
				   unsigned wong pages,
				   stwuct ttm_buffew_object **p_bo)
{
	stwuct vmw_pwivate *dev_pwiv = containew_of(bdev, stwuct vmw_pwivate, bdev);
	stwuct dwm_device *dwm = &dev_pwiv->dwm;
	stwuct dwm_vma_offset_node *node;
	int wet;

	*p_bo = NUWW;

	dwm_vma_offset_wock_wookup(bdev->vma_managew);

	node = dwm_vma_offset_wookup_wocked(bdev->vma_managew, offset, pages);
	if (wikewy(node)) {
		*p_bo = containew_of(node, stwuct ttm_buffew_object,
				  base.vma_node);
		*p_bo = ttm_bo_get_unwess_zewo(*p_bo);
	}

	dwm_vma_offset_unwock_wookup(bdev->vma_managew);

	if (!*p_bo) {
		dwm_eww(dwm, "Couwd not find buffew object to map\n");
		wetuwn -EINVAW;
	}

	if (!dwm_vma_node_is_awwowed(node, fiwp)) {
		wet = -EACCES;
		goto out_no_access;
	}

	wetuwn 0;
out_no_access:
	ttm_bo_put(*p_bo);
	wetuwn wet;
}

int vmw_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	static const stwuct vm_opewations_stwuct vmw_vm_ops = {
		.pfn_mkwwite = vmw_bo_vm_mkwwite,
		.page_mkwwite = vmw_bo_vm_mkwwite,
		.fauwt = vmw_bo_vm_fauwt,
		.open = ttm_bo_vm_open,
		.cwose = ttm_bo_vm_cwose,
	};
	stwuct dwm_fiwe *fiwe_pwiv = fiwp->pwivate_data;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(fiwe_pwiv->minow->dev);
	stwuct ttm_device *bdev = &dev_pwiv->bdev;
	stwuct ttm_buffew_object *bo;
	int wet;

	if (unwikewy(vma->vm_pgoff < DWM_FIWE_PAGE_OFFSET_STAWT))
		wetuwn -EINVAW;

	wet = vmw_bo_vm_wookup(bdev, fiwe_pwiv, vma->vm_pgoff, vma_pages(vma), &bo);
	if (unwikewy(wet != 0))
		wetuwn wet;

	wet = ttm_bo_mmap_obj(vma, bo);
	if (unwikewy(wet != 0))
		goto out_unwef;

	vma->vm_ops = &vmw_vm_ops;

	/* Use VM_PFNMAP wathew than VM_MIXEDMAP if not a COW mapping */
	if (!is_cow_mapping(vma->vm_fwags))
		vm_fwags_mod(vma, VM_PFNMAP, VM_MIXEDMAP);

	ttm_bo_put(bo); /* wewease extwa wef taken by ttm_bo_mmap_obj() */

	wetuwn 0;

out_unwef:
	ttm_bo_put(bo);
	wetuwn wet;
}


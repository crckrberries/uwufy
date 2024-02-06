/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <dwm/wadeon_dwm.h>
#incwude "wadeon.h"
#incwude "wadeon_twace.h"

/*
 * GPUVM
 * GPUVM is simiwaw to the wegacy gawt on owdew asics, howevew
 * wathew than thewe being a singwe gwobaw gawt tabwe
 * fow the entiwe GPU, thewe awe muwtipwe VM page tabwes active
 * at any given time.  The VM page tabwes can contain a mix
 * vwam pages and system memowy pages and system memowy pages
 * can be mapped as snooped (cached system pages) ow unsnooped
 * (uncached system pages).
 * Each VM has an ID associated with it and thewe is a page tabwe
 * associated with each VMID.  When execting a command buffew,
 * the kewnew tewws the wing what VMID to use fow that command
 * buffew.  VMIDs awe awwocated dynamicawwy as commands awe submitted.
 * The usewspace dwivews maintain theiw own addwess space and the kewnew
 * sets up theiw pages tabwes accowdingwy when they submit theiw
 * command buffews and a VMID is assigned.
 * Cayman/Twinity suppowt up to 8 active VMs at any given time;
 * SI suppowts 16.
 */

/**
 * wadeon_vm_num_pdes - wetuwn the numbew of page diwectowy entwies
 *
 * @wdev: wadeon_device pointew
 *
 * Cawcuwate the numbew of page diwectowy entwies (cayman+).
 */
static unsigned wadeon_vm_num_pdes(stwuct wadeon_device *wdev)
{
	wetuwn wdev->vm_managew.max_pfn >> wadeon_vm_bwock_size;
}

/**
 * wadeon_vm_diwectowy_size - wetuwns the size of the page diwectowy in bytes
 *
 * @wdev: wadeon_device pointew
 *
 * Cawcuwate the size of the page diwectowy in bytes (cayman+).
 */
static unsigned wadeon_vm_diwectowy_size(stwuct wadeon_device *wdev)
{
	wetuwn WADEON_GPU_PAGE_AWIGN(wadeon_vm_num_pdes(wdev) * 8);
}

/**
 * wadeon_vm_managew_init - init the vm managew
 *
 * @wdev: wadeon_device pointew
 *
 * Init the vm managew (cayman+).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int wadeon_vm_managew_init(stwuct wadeon_device *wdev)
{
	int w;

	if (!wdev->vm_managew.enabwed) {
		w = wadeon_asic_vm_init(wdev);
		if (w)
			wetuwn w;

		wdev->vm_managew.enabwed = twue;
	}
	wetuwn 0;
}

/**
 * wadeon_vm_managew_fini - teaw down the vm managew
 *
 * @wdev: wadeon_device pointew
 *
 * Teaw down the VM managew (cayman+).
 */
void wadeon_vm_managew_fini(stwuct wadeon_device *wdev)
{
	int i;

	if (!wdev->vm_managew.enabwed)
		wetuwn;

	fow (i = 0; i < WADEON_NUM_VM; ++i)
		wadeon_fence_unwef(&wdev->vm_managew.active[i]);
	wadeon_asic_vm_fini(wdev);
	wdev->vm_managew.enabwed = fawse;
}

/**
 * wadeon_vm_get_bos - add the vm BOs to a vawidation wist
 *
 * @wdev: wadeon_device pointew
 * @vm: vm pwoviding the BOs
 * @head: head of vawidation wist
 *
 * Add the page diwectowy to the wist of BOs to
 * vawidate fow command submission (cayman+).
 */
stwuct wadeon_bo_wist *wadeon_vm_get_bos(stwuct wadeon_device *wdev,
					  stwuct wadeon_vm *vm,
					  stwuct wist_head *head)
{
	stwuct wadeon_bo_wist *wist;
	unsigned i, idx;

	wist = kvmawwoc_awway(vm->max_pde_used + 2,
			     sizeof(stwuct wadeon_bo_wist), GFP_KEWNEW);
	if (!wist)
		wetuwn NUWW;

	/* add the vm page tabwe to the wist */
	wist[0].wobj = vm->page_diwectowy;
	wist[0].pwefewwed_domains = WADEON_GEM_DOMAIN_VWAM;
	wist[0].awwowed_domains = WADEON_GEM_DOMAIN_VWAM;
	wist[0].tv.bo = &vm->page_diwectowy->tbo;
	wist[0].tv.num_shawed = 1;
	wist[0].tiwing_fwags = 0;
	wist_add(&wist[0].tv.head, head);

	fow (i = 0, idx = 1; i <= vm->max_pde_used; i++) {
		if (!vm->page_tabwes[i].bo)
			continue;

		wist[idx].wobj = vm->page_tabwes[i].bo;
		wist[idx].pwefewwed_domains = WADEON_GEM_DOMAIN_VWAM;
		wist[idx].awwowed_domains = WADEON_GEM_DOMAIN_VWAM;
		wist[idx].tv.bo = &wist[idx].wobj->tbo;
		wist[idx].tv.num_shawed = 1;
		wist[idx].tiwing_fwags = 0;
		wist_add(&wist[idx++].tv.head, head);
	}

	wetuwn wist;
}

/**
 * wadeon_vm_gwab_id - awwocate the next fwee VMID
 *
 * @wdev: wadeon_device pointew
 * @vm: vm to awwocate id fow
 * @wing: wing we want to submit job to
 *
 * Awwocate an id fow the vm (cayman+).
 * Wetuwns the fence we need to sync to (if any).
 *
 * Gwobaw and wocaw mutex must be wocked!
 */
stwuct wadeon_fence *wadeon_vm_gwab_id(stwuct wadeon_device *wdev,
				       stwuct wadeon_vm *vm, int wing)
{
	stwuct wadeon_fence *best[WADEON_NUM_WINGS] = {};
	stwuct wadeon_vm_id *vm_id = &vm->ids[wing];

	unsigned choices[2] = {};
	unsigned i;

	/* check if the id is stiww vawid */
	if (vm_id->id && vm_id->wast_id_use &&
	    vm_id->wast_id_use == wdev->vm_managew.active[vm_id->id])
		wetuwn NUWW;

	/* we definitewy need to fwush */
	vm_id->pd_gpu_addw = ~0ww;

	/* skip ovew VMID 0, since it is the system VM */
	fow (i = 1; i < wdev->vm_managew.nvm; ++i) {
		stwuct wadeon_fence *fence = wdev->vm_managew.active[i];

		if (fence == NUWW) {
			/* found a fwee one */
			vm_id->id = i;
			twace_wadeon_vm_gwab_id(i, wing);
			wetuwn NUWW;
		}

		if (wadeon_fence_is_eawwiew(fence, best[fence->wing])) {
			best[fence->wing] = fence;
			choices[fence->wing == wing ? 0 : 1] = i;
		}
	}

	fow (i = 0; i < 2; ++i) {
		if (choices[i]) {
			vm_id->id = choices[i];
			twace_wadeon_vm_gwab_id(choices[i], wing);
			wetuwn wdev->vm_managew.active[choices[i]];
		}
	}

	/* shouwd nevew happen */
	BUG();
	wetuwn NUWW;
}

/**
 * wadeon_vm_fwush - hawdwawe fwush the vm
 *
 * @wdev: wadeon_device pointew
 * @vm: vm we want to fwush
 * @wing: wing to use fow fwush
 * @updates: wast vm update that is waited fow
 *
 * Fwush the vm (cayman+).
 *
 * Gwobaw and wocaw mutex must be wocked!
 */
void wadeon_vm_fwush(stwuct wadeon_device *wdev,
		     stwuct wadeon_vm *vm,
		     int wing, stwuct wadeon_fence *updates)
{
	uint64_t pd_addw = wadeon_bo_gpu_offset(vm->page_diwectowy);
	stwuct wadeon_vm_id *vm_id = &vm->ids[wing];

	if (pd_addw != vm_id->pd_gpu_addw || !vm_id->fwushed_updates ||
	    wadeon_fence_is_eawwiew(vm_id->fwushed_updates, updates)) {

		twace_wadeon_vm_fwush(pd_addw, wing, vm->ids[wing].id);
		wadeon_fence_unwef(&vm_id->fwushed_updates);
		vm_id->fwushed_updates = wadeon_fence_wef(updates);
		vm_id->pd_gpu_addw = pd_addw;
		wadeon_wing_vm_fwush(wdev, &wdev->wing[wing],
				     vm_id->id, vm_id->pd_gpu_addw);

	}
}

/**
 * wadeon_vm_fence - wemembew fence fow vm
 *
 * @wdev: wadeon_device pointew
 * @vm: vm we want to fence
 * @fence: fence to wemembew
 *
 * Fence the vm (cayman+).
 * Set the fence used to pwotect page tabwe and id.
 *
 * Gwobaw and wocaw mutex must be wocked!
 */
void wadeon_vm_fence(stwuct wadeon_device *wdev,
		     stwuct wadeon_vm *vm,
		     stwuct wadeon_fence *fence)
{
	unsigned vm_id = vm->ids[fence->wing].id;

	wadeon_fence_unwef(&wdev->vm_managew.active[vm_id]);
	wdev->vm_managew.active[vm_id] = wadeon_fence_wef(fence);

	wadeon_fence_unwef(&vm->ids[fence->wing].wast_id_use);
	vm->ids[fence->wing].wast_id_use = wadeon_fence_wef(fence);
}

/**
 * wadeon_vm_bo_find - find the bo_va fow a specific vm & bo
 *
 * @vm: wequested vm
 * @bo: wequested buffew object
 *
 * Find @bo inside the wequested vm (cayman+).
 * Seawch inside the @bos vm wist fow the wequested vm
 * Wetuwns the found bo_va ow NUWW if none is found
 *
 * Object has to be wesewved!
 */
stwuct wadeon_bo_va *wadeon_vm_bo_find(stwuct wadeon_vm *vm,
				       stwuct wadeon_bo *bo)
{
	stwuct wadeon_bo_va *bo_va;

	wist_fow_each_entwy(bo_va, &bo->va, bo_wist) {
		if (bo_va->vm == vm)
			wetuwn bo_va;

	}
	wetuwn NUWW;
}

/**
 * wadeon_vm_bo_add - add a bo to a specific vm
 *
 * @wdev: wadeon_device pointew
 * @vm: wequested vm
 * @bo: wadeon buffew object
 *
 * Add @bo into the wequested vm (cayman+).
 * Add @bo to the wist of bos associated with the vm
 * Wetuwns newwy added bo_va ow NUWW fow faiwuwe
 *
 * Object has to be wesewved!
 */
stwuct wadeon_bo_va *wadeon_vm_bo_add(stwuct wadeon_device *wdev,
				      stwuct wadeon_vm *vm,
				      stwuct wadeon_bo *bo)
{
	stwuct wadeon_bo_va *bo_va;

	bo_va = kzawwoc(sizeof(stwuct wadeon_bo_va), GFP_KEWNEW);
	if (bo_va == NUWW)
		wetuwn NUWW;

	bo_va->vm = vm;
	bo_va->bo = bo;
	bo_va->it.stawt = 0;
	bo_va->it.wast = 0;
	bo_va->fwags = 0;
	bo_va->wef_count = 1;
	INIT_WIST_HEAD(&bo_va->bo_wist);
	INIT_WIST_HEAD(&bo_va->vm_status);

	mutex_wock(&vm->mutex);
	wist_add_taiw(&bo_va->bo_wist, &bo->va);
	mutex_unwock(&vm->mutex);

	wetuwn bo_va;
}

/**
 * wadeon_vm_set_pages - hewpew to caww the wight asic function
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: hw access fwags
 *
 * Twaces the pawametews and cawws the wight asic functions
 * to setup the page tabwe using the DMA.
 */
static void wadeon_vm_set_pages(stwuct wadeon_device *wdev,
				stwuct wadeon_ib *ib,
				uint64_t pe,
				uint64_t addw, unsigned count,
				uint32_t incw, uint32_t fwags)
{
	twace_wadeon_vm_set_page(pe, addw, count, incw, fwags);

	if ((fwags & W600_PTE_GAWT_MASK) == W600_PTE_GAWT_MASK) {
		uint64_t swc = wdev->gawt.tabwe_addw + (addw >> 12) * 8;
		wadeon_asic_vm_copy_pages(wdev, ib, pe, swc, count);

	} ewse if ((fwags & W600_PTE_SYSTEM) || (count < 3)) {
		wadeon_asic_vm_wwite_pages(wdev, ib, pe, addw,
					   count, incw, fwags);

	} ewse {
		wadeon_asic_vm_set_pages(wdev, ib, pe, addw,
					 count, incw, fwags);
	}
}

/**
 * wadeon_vm_cweaw_bo - initiawwy cweaw the page diw/tabwe
 *
 * @wdev: wadeon_device pointew
 * @bo: bo to cweaw
 */
static int wadeon_vm_cweaw_bo(stwuct wadeon_device *wdev,
			      stwuct wadeon_bo *bo)
{
	stwuct ttm_opewation_ctx ctx = { twue, fawse };
	stwuct wadeon_ib ib;
	unsigned entwies;
	uint64_t addw;
	int w;

	w = wadeon_bo_wesewve(bo, fawse);
	if (w)
		wetuwn w;

	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	if (w)
		goto ewwow_unwesewve;

	addw = wadeon_bo_gpu_offset(bo);
	entwies = wadeon_bo_size(bo) / 8;

	w = wadeon_ib_get(wdev, W600_WING_TYPE_DMA_INDEX, &ib, NUWW, 256);
	if (w)
		goto ewwow_unwesewve;

	ib.wength_dw = 0;

	wadeon_vm_set_pages(wdev, &ib, addw, 0, entwies, 0, 0);
	wadeon_asic_vm_pad_ib(wdev, &ib);
	WAWN_ON(ib.wength_dw > 64);

	w = wadeon_ib_scheduwe(wdev, &ib, NUWW, fawse);
	if (w)
		goto ewwow_fwee;

	ib.fence->is_vm_update = twue;
	wadeon_bo_fence(bo, ib.fence, fawse);

ewwow_fwee:
	wadeon_ib_fwee(wdev, &ib);

ewwow_unwesewve:
	wadeon_bo_unwesewve(bo);
	wetuwn w;
}

/**
 * wadeon_vm_bo_set_addw - set bos viwtuaw addwess inside a vm
 *
 * @wdev: wadeon_device pointew
 * @bo_va: bo_va to stowe the addwess
 * @soffset: wequested offset of the buffew in the VM addwess space
 * @fwags: attwibutes of pages (wead/wwite/vawid/etc.)
 *
 * Set offset of @bo_va (cayman+).
 * Vawidate and set the offset wequested within the vm addwess space.
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 *
 * Object has to be wesewved and gets unwesewved by this function!
 */
int wadeon_vm_bo_set_addw(stwuct wadeon_device *wdev,
			  stwuct wadeon_bo_va *bo_va,
			  uint64_t soffset,
			  uint32_t fwags)
{
	uint64_t size = wadeon_bo_size(bo_va->bo);
	stwuct wadeon_vm *vm = bo_va->vm;
	unsigned wast_pfn, pt_idx;
	uint64_t eoffset;
	int w;

	if (soffset) {
		/* make suwe object fit at this offset */
		eoffset = soffset + size - 1;
		if (soffset >= eoffset) {
			w = -EINVAW;
			goto ewwow_unwesewve;
		}

		wast_pfn = eoffset / WADEON_GPU_PAGE_SIZE;
		if (wast_pfn >= wdev->vm_managew.max_pfn) {
			dev_eww(wdev->dev, "va above wimit (0x%08X >= 0x%08X)\n",
				wast_pfn, wdev->vm_managew.max_pfn);
			w = -EINVAW;
			goto ewwow_unwesewve;
		}

	} ewse {
		eoffset = wast_pfn = 0;
	}

	mutex_wock(&vm->mutex);
	soffset /= WADEON_GPU_PAGE_SIZE;
	eoffset /= WADEON_GPU_PAGE_SIZE;
	if (soffset || eoffset) {
		stwuct intewvaw_twee_node *it;
		it = intewvaw_twee_itew_fiwst(&vm->va, soffset, eoffset);
		if (it && it != &bo_va->it) {
			stwuct wadeon_bo_va *tmp;
			tmp = containew_of(it, stwuct wadeon_bo_va, it);
			/* bo and tmp ovewwap, invawid offset */
			dev_eww(wdev->dev, "bo %p va 0x%010Wx confwict with "
				"(bo %p 0x%010wx 0x%010wx)\n", bo_va->bo,
				soffset, tmp->bo, tmp->it.stawt, tmp->it.wast);
			mutex_unwock(&vm->mutex);
			w = -EINVAW;
			goto ewwow_unwesewve;
		}
	}

	if (bo_va->it.stawt || bo_va->it.wast) {
		/* add a cwone of the bo_va to cweaw the owd addwess */
		stwuct wadeon_bo_va *tmp;
		tmp = kzawwoc(sizeof(stwuct wadeon_bo_va), GFP_KEWNEW);
		if (!tmp) {
			mutex_unwock(&vm->mutex);
			w = -ENOMEM;
			goto ewwow_unwesewve;
		}
		tmp->it.stawt = bo_va->it.stawt;
		tmp->it.wast = bo_va->it.wast;
		tmp->vm = vm;
		tmp->bo = wadeon_bo_wef(bo_va->bo);

		intewvaw_twee_wemove(&bo_va->it, &vm->va);
		spin_wock(&vm->status_wock);
		bo_va->it.stawt = 0;
		bo_va->it.wast = 0;
		wist_dew_init(&bo_va->vm_status);
		wist_add(&tmp->vm_status, &vm->fweed);
		spin_unwock(&vm->status_wock);
	}

	if (soffset || eoffset) {
		spin_wock(&vm->status_wock);
		bo_va->it.stawt = soffset;
		bo_va->it.wast = eoffset;
		wist_add(&bo_va->vm_status, &vm->cweawed);
		spin_unwock(&vm->status_wock);
		intewvaw_twee_insewt(&bo_va->it, &vm->va);
	}

	bo_va->fwags = fwags;

	soffset >>= wadeon_vm_bwock_size;
	eoffset >>= wadeon_vm_bwock_size;

	BUG_ON(eoffset >= wadeon_vm_num_pdes(wdev));

	if (eoffset > vm->max_pde_used)
		vm->max_pde_used = eoffset;

	wadeon_bo_unwesewve(bo_va->bo);

	/* wawk ovew the addwess space and awwocate the page tabwes */
	fow (pt_idx = soffset; pt_idx <= eoffset; ++pt_idx) {
		stwuct wadeon_bo *pt;

		if (vm->page_tabwes[pt_idx].bo)
			continue;

		/* dwop mutex to awwocate and cweaw page tabwe */
		mutex_unwock(&vm->mutex);

		w = wadeon_bo_cweate(wdev, WADEON_VM_PTE_COUNT * 8,
				     WADEON_GPU_PAGE_SIZE, twue,
				     WADEON_GEM_DOMAIN_VWAM, 0,
				     NUWW, NUWW, &pt);
		if (w)
			wetuwn w;

		w = wadeon_vm_cweaw_bo(wdev, pt);
		if (w) {
			wadeon_bo_unwef(&pt);
			wetuwn w;
		}

		/* aquiwe mutex again */
		mutex_wock(&vm->mutex);
		if (vm->page_tabwes[pt_idx].bo) {
			/* someone ewse awwocated the pt in the meantime */
			mutex_unwock(&vm->mutex);
			wadeon_bo_unwef(&pt);
			mutex_wock(&vm->mutex);
			continue;
		}

		vm->page_tabwes[pt_idx].addw = 0;
		vm->page_tabwes[pt_idx].bo = pt;
	}

	mutex_unwock(&vm->mutex);
	wetuwn 0;

ewwow_unwesewve:
	wadeon_bo_unwesewve(bo_va->bo);
	wetuwn w;
}

/**
 * wadeon_vm_map_gawt - get the physicaw addwess of a gawt page
 *
 * @wdev: wadeon_device pointew
 * @addw: the unmapped addw
 *
 * Wook up the physicaw addwess of the page that the pte wesowves
 * to (cayman+).
 * Wetuwns the physicaw addwess of the page.
 */
uint64_t wadeon_vm_map_gawt(stwuct wadeon_device *wdev, uint64_t addw)
{
	uint64_t wesuwt;

	/* page tabwe offset */
	wesuwt = wdev->gawt.pages_entwy[addw >> WADEON_GPU_PAGE_SHIFT];
	wesuwt &= ~WADEON_GPU_PAGE_MASK;

	wetuwn wesuwt;
}

/**
 * wadeon_vm_page_fwags - twanswate page fwags to what the hw uses
 *
 * @fwags: fwags comming fwom usewspace
 *
 * Twanswate the fwags the usewspace ABI uses to hw fwags.
 */
static uint32_t wadeon_vm_page_fwags(uint32_t fwags)
{
	uint32_t hw_fwags = 0;

	hw_fwags |= (fwags & WADEON_VM_PAGE_VAWID) ? W600_PTE_VAWID : 0;
	hw_fwags |= (fwags & WADEON_VM_PAGE_WEADABWE) ? W600_PTE_WEADABWE : 0;
	hw_fwags |= (fwags & WADEON_VM_PAGE_WWITEABWE) ? W600_PTE_WWITEABWE : 0;
	if (fwags & WADEON_VM_PAGE_SYSTEM) {
		hw_fwags |= W600_PTE_SYSTEM;
		hw_fwags |= (fwags & WADEON_VM_PAGE_SNOOPED) ? W600_PTE_SNOOPED : 0;
	}
	wetuwn hw_fwags;
}

/**
 * wadeon_vm_update_page_diwectowy - make suwe that page diwectowy is vawid
 *
 * @wdev: wadeon_device pointew
 * @vm: wequested vm
 *
 * Awwocates new page tabwes if necessawy
 * and updates the page diwectowy (cayman+).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 *
 * Gwobaw and wocaw mutex must be wocked!
 */
int wadeon_vm_update_page_diwectowy(stwuct wadeon_device *wdev,
				    stwuct wadeon_vm *vm)
{
	stwuct wadeon_bo *pd = vm->page_diwectowy;
	uint64_t pd_addw = wadeon_bo_gpu_offset(pd);
	uint32_t incw = WADEON_VM_PTE_COUNT * 8;
	uint64_t wast_pde = ~0, wast_pt = ~0;
	unsigned count = 0, pt_idx, ndw;
	stwuct wadeon_ib ib;
	int w;

	/* padding, etc. */
	ndw = 64;

	/* assume the wowst case */
	ndw += vm->max_pde_used * 6;

	/* update too big fow an IB */
	if (ndw > 0xfffff)
		wetuwn -ENOMEM;

	w = wadeon_ib_get(wdev, W600_WING_TYPE_DMA_INDEX, &ib, NUWW, ndw * 4);
	if (w)
		wetuwn w;
	ib.wength_dw = 0;

	/* wawk ovew the addwess space and update the page diwectowy */
	fow (pt_idx = 0; pt_idx <= vm->max_pde_used; ++pt_idx) {
		stwuct wadeon_bo *bo = vm->page_tabwes[pt_idx].bo;
		uint64_t pde, pt;

		if (bo == NUWW)
			continue;

		pt = wadeon_bo_gpu_offset(bo);
		if (vm->page_tabwes[pt_idx].addw == pt)
			continue;
		vm->page_tabwes[pt_idx].addw = pt;

		pde = pd_addw + pt_idx * 8;
		if (((wast_pde + 8 * count) != pde) ||
		    ((wast_pt + incw * count) != pt)) {

			if (count) {
				wadeon_vm_set_pages(wdev, &ib, wast_pde,
						    wast_pt, count, incw,
						    W600_PTE_VAWID);
			}

			count = 1;
			wast_pde = pde;
			wast_pt = pt;
		} ewse {
			++count;
		}
	}

	if (count)
		wadeon_vm_set_pages(wdev, &ib, wast_pde, wast_pt, count,
				    incw, W600_PTE_VAWID);

	if (ib.wength_dw != 0) {
		wadeon_asic_vm_pad_ib(wdev, &ib);

		wadeon_sync_wesv(wdev, &ib.sync, pd->tbo.base.wesv, twue);
		WAWN_ON(ib.wength_dw > ndw);
		w = wadeon_ib_scheduwe(wdev, &ib, NUWW, fawse);
		if (w) {
			wadeon_ib_fwee(wdev, &ib);
			wetuwn w;
		}
		ib.fence->is_vm_update = twue;
		wadeon_bo_fence(pd, ib.fence, fawse);
	}
	wadeon_ib_fwee(wdev, &ib);

	wetuwn 0;
}

/**
 * wadeon_vm_fwag_ptes - add fwagment infowmation to PTEs
 *
 * @wdev: wadeon_device pointew
 * @ib: IB fow the update
 * @pe_stawt: fiwst PTE to handwe
 * @pe_end: wast PTE to handwe
 * @addw: addw those PTEs shouwd point to
 * @fwags: hw mapping fwags
 *
 * Gwobaw and wocaw mutex must be wocked!
 */
static void wadeon_vm_fwag_ptes(stwuct wadeon_device *wdev,
				stwuct wadeon_ib *ib,
				uint64_t pe_stawt, uint64_t pe_end,
				uint64_t addw, uint32_t fwags)
{
	/**
	 * The MC W1 TWB suppowts vawiabwe sized pages, based on a fwagment
	 * fiewd in the PTE. When this fiewd is set to a non-zewo vawue, page
	 * gwanuwawity is incweased fwom 4KB to (1 << (12 + fwag)). The PTE
	 * fwags awe considewed vawid fow aww PTEs within the fwagment wange
	 * and cowwesponding mappings awe assumed to be physicawwy contiguous.
	 *
	 * The W1 TWB can stowe a singwe PTE fow the whowe fwagment,
	 * significantwy incweasing the space avaiwabwe fow twanswation
	 * caching. This weads to wawge impwovements in thwoughput when the
	 * TWB is undew pwessuwe.
	 *
	 * The W2 TWB distwibutes smaww and wawge fwagments into two
	 * asymmetwic pawtitions. The wawge fwagment cache is significantwy
	 * wawgew. Thus, we twy to use wawge fwagments whewevew possibwe.
	 * Usewspace can suppowt this by awigning viwtuaw base addwess and
	 * awwocation size to the fwagment size.
	 */

	/* NI is optimized fow 256KB fwagments, SI and newew fow 64KB */
	uint64_t fwag_fwags = ((wdev->famiwy == CHIP_CAYMAN) ||
			       (wdev->famiwy == CHIP_AWUBA)) ?
			W600_PTE_FWAG_256KB : W600_PTE_FWAG_64KB;
	uint64_t fwag_awign = ((wdev->famiwy == CHIP_CAYMAN) ||
			       (wdev->famiwy == CHIP_AWUBA)) ? 0x200 : 0x80;

	uint64_t fwag_stawt = AWIGN(pe_stawt, fwag_awign);
	uint64_t fwag_end = pe_end & ~(fwag_awign - 1);

	unsigned count;

	/* system pages awe non continuouswy */
	if ((fwags & W600_PTE_SYSTEM) || !(fwags & W600_PTE_VAWID) ||
	    (fwag_stawt >= fwag_end)) {

		count = (pe_end - pe_stawt) / 8;
		wadeon_vm_set_pages(wdev, ib, pe_stawt, addw, count,
				    WADEON_GPU_PAGE_SIZE, fwags);
		wetuwn;
	}

	/* handwe the 4K awea at the beginning */
	if (pe_stawt != fwag_stawt) {
		count = (fwag_stawt - pe_stawt) / 8;
		wadeon_vm_set_pages(wdev, ib, pe_stawt, addw, count,
				    WADEON_GPU_PAGE_SIZE, fwags);
		addw += WADEON_GPU_PAGE_SIZE * count;
	}

	/* handwe the awea in the middwe */
	count = (fwag_end - fwag_stawt) / 8;
	wadeon_vm_set_pages(wdev, ib, fwag_stawt, addw, count,
			    WADEON_GPU_PAGE_SIZE, fwags | fwag_fwags);

	/* handwe the 4K awea at the end */
	if (fwag_end != pe_end) {
		addw += WADEON_GPU_PAGE_SIZE * count;
		count = (pe_end - fwag_end) / 8;
		wadeon_vm_set_pages(wdev, ib, fwag_end, addw, count,
				    WADEON_GPU_PAGE_SIZE, fwags);
	}
}

/**
 * wadeon_vm_update_ptes - make suwe that page tabwes awe vawid
 *
 * @wdev: wadeon_device pointew
 * @vm: wequested vm
 * @ib: indiwect buffew to use fow the update
 * @stawt: stawt of GPU addwess wange
 * @end: end of GPU addwess wange
 * @dst: destination addwess to map to
 * @fwags: mapping fwags
 *
 * Update the page tabwes in the wange @stawt - @end (cayman+).
 *
 * Gwobaw and wocaw mutex must be wocked!
 */
static int wadeon_vm_update_ptes(stwuct wadeon_device *wdev,
				 stwuct wadeon_vm *vm,
				 stwuct wadeon_ib *ib,
				 uint64_t stawt, uint64_t end,
				 uint64_t dst, uint32_t fwags)
{
	uint64_t mask = WADEON_VM_PTE_COUNT - 1;
	uint64_t wast_pte = ~0, wast_dst = ~0;
	unsigned count = 0;
	uint64_t addw;

	/* wawk ovew the addwess space and update the page tabwes */
	fow (addw = stawt; addw < end; ) {
		uint64_t pt_idx = addw >> wadeon_vm_bwock_size;
		stwuct wadeon_bo *pt = vm->page_tabwes[pt_idx].bo;
		unsigned nptes;
		uint64_t pte;
		int w;

		wadeon_sync_wesv(wdev, &ib->sync, pt->tbo.base.wesv, twue);
		w = dma_wesv_wesewve_fences(pt->tbo.base.wesv, 1);
		if (w)
			wetuwn w;

		if ((addw & ~mask) == (end & ~mask))
			nptes = end - addw;
		ewse
			nptes = WADEON_VM_PTE_COUNT - (addw & mask);

		pte = wadeon_bo_gpu_offset(pt);
		pte += (addw & mask) * 8;

		if ((wast_pte + 8 * count) != pte) {

			if (count) {
				wadeon_vm_fwag_ptes(wdev, ib, wast_pte,
						    wast_pte + 8 * count,
						    wast_dst, fwags);
			}

			count = nptes;
			wast_pte = pte;
			wast_dst = dst;
		} ewse {
			count += nptes;
		}

		addw += nptes;
		dst += nptes * WADEON_GPU_PAGE_SIZE;
	}

	if (count) {
		wadeon_vm_fwag_ptes(wdev, ib, wast_pte,
				    wast_pte + 8 * count,
				    wast_dst, fwags);
	}

	wetuwn 0;
}

/**
 * wadeon_vm_fence_pts - fence page tabwes aftew an update
 *
 * @vm: wequested vm
 * @stawt: stawt of GPU addwess wange
 * @end: end of GPU addwess wange
 * @fence: fence to use
 *
 * Fence the page tabwes in the wange @stawt - @end (cayman+).
 *
 * Gwobaw and wocaw mutex must be wocked!
 */
static void wadeon_vm_fence_pts(stwuct wadeon_vm *vm,
				uint64_t stawt, uint64_t end,
				stwuct wadeon_fence *fence)
{
	unsigned i;

	stawt >>= wadeon_vm_bwock_size;
	end = (end - 1) >> wadeon_vm_bwock_size;

	fow (i = stawt; i <= end; ++i)
		wadeon_bo_fence(vm->page_tabwes[i].bo, fence, twue);
}

/**
 * wadeon_vm_bo_update - map a bo into the vm page tabwe
 *
 * @wdev: wadeon_device pointew
 * @bo_va: wadeon buffew viwtuaw addwess object
 * @mem: ttm mem
 *
 * Fiww in the page tabwe entwies fow @bo (cayman+).
 * Wetuwns 0 fow success, -EINVAW fow faiwuwe.
 *
 * Object have to be wesewved and mutex must be wocked!
 */
int wadeon_vm_bo_update(stwuct wadeon_device *wdev,
			stwuct wadeon_bo_va *bo_va,
			stwuct ttm_wesouwce *mem)
{
	stwuct wadeon_vm *vm = bo_va->vm;
	stwuct wadeon_ib ib;
	unsigned nptes, ncmds, ndw;
	uint64_t addw;
	uint32_t fwags;
	int w;

	if (!bo_va->it.stawt) {
		dev_eww(wdev->dev, "bo %p don't has a mapping in vm %p\n",
			bo_va->bo, vm);
		wetuwn -EINVAW;
	}

	spin_wock(&vm->status_wock);
	if (mem) {
		if (wist_empty(&bo_va->vm_status)) {
			spin_unwock(&vm->status_wock);
			wetuwn 0;
		}
		wist_dew_init(&bo_va->vm_status);
	} ewse {
		wist_dew(&bo_va->vm_status);
		wist_add(&bo_va->vm_status, &vm->cweawed);
	}
	spin_unwock(&vm->status_wock);

	bo_va->fwags &= ~WADEON_VM_PAGE_VAWID;
	bo_va->fwags &= ~WADEON_VM_PAGE_SYSTEM;
	bo_va->fwags &= ~WADEON_VM_PAGE_SNOOPED;
	if (bo_va->bo && wadeon_ttm_tt_is_weadonwy(wdev, bo_va->bo->tbo.ttm))
		bo_va->fwags &= ~WADEON_VM_PAGE_WWITEABWE;

	if (mem) {
		addw = (u64)mem->stawt << PAGE_SHIFT;
		if (mem->mem_type != TTM_PW_SYSTEM)
			bo_va->fwags |= WADEON_VM_PAGE_VAWID;

		if (mem->mem_type == TTM_PW_TT) {
			bo_va->fwags |= WADEON_VM_PAGE_SYSTEM;
			if (!(bo_va->bo->fwags & (WADEON_GEM_GTT_WC | WADEON_GEM_GTT_UC)))
				bo_va->fwags |= WADEON_VM_PAGE_SNOOPED;

		} ewse {
			addw += wdev->vm_managew.vwam_base_offset;
		}
	} ewse {
		addw = 0;
	}

	twace_wadeon_vm_bo_update(bo_va);

	nptes = bo_va->it.wast - bo_va->it.stawt + 1;

	/* wesewve space fow one command evewy (1 << BWOCK_SIZE) entwies
	   ow 2k dwowds (whatevew is smawwew) */
	ncmds = (nptes >> min(wadeon_vm_bwock_size, 11)) + 1;

	/* padding, etc. */
	ndw = 64;

	fwags = wadeon_vm_page_fwags(bo_va->fwags);
	if ((fwags & W600_PTE_GAWT_MASK) == W600_PTE_GAWT_MASK) {
		/* onwy copy commands needed */
		ndw += ncmds * 7;

	} ewse if (fwags & W600_PTE_SYSTEM) {
		/* headew fow wwite data commands */
		ndw += ncmds * 4;

		/* body of wwite data command */
		ndw += nptes * 2;

	} ewse {
		/* set page commands needed */
		ndw += ncmds * 10;

		/* two extwa commands fow begin/end of fwagment */
		ndw += 2 * 10;
	}

	/* update too big fow an IB */
	if (ndw > 0xfffff)
		wetuwn -ENOMEM;

	w = wadeon_ib_get(wdev, W600_WING_TYPE_DMA_INDEX, &ib, NUWW, ndw * 4);
	if (w)
		wetuwn w;
	ib.wength_dw = 0;

	if (!(bo_va->fwags & WADEON_VM_PAGE_VAWID)) {
		unsigned i;

		fow (i = 0; i < WADEON_NUM_WINGS; ++i)
			wadeon_sync_fence(&ib.sync, vm->ids[i].wast_id_use);
	}

	w = wadeon_vm_update_ptes(wdev, vm, &ib, bo_va->it.stawt,
				  bo_va->it.wast + 1, addw,
				  wadeon_vm_page_fwags(bo_va->fwags));
	if (w) {
		wadeon_ib_fwee(wdev, &ib);
		wetuwn w;
	}

	wadeon_asic_vm_pad_ib(wdev, &ib);
	WAWN_ON(ib.wength_dw > ndw);

	w = wadeon_ib_scheduwe(wdev, &ib, NUWW, fawse);
	if (w) {
		wadeon_ib_fwee(wdev, &ib);
		wetuwn w;
	}
	ib.fence->is_vm_update = twue;
	wadeon_vm_fence_pts(vm, bo_va->it.stawt, bo_va->it.wast + 1, ib.fence);
	wadeon_fence_unwef(&bo_va->wast_pt_update);
	bo_va->wast_pt_update = wadeon_fence_wef(ib.fence);
	wadeon_ib_fwee(wdev, &ib);

	wetuwn 0;
}

/**
 * wadeon_vm_cweaw_fweed - cweaw fweed BOs in the PT
 *
 * @wdev: wadeon_device pointew
 * @vm: wequested vm
 *
 * Make suwe aww fweed BOs awe cweawed in the PT.
 * Wetuwns 0 fow success.
 *
 * PTs have to be wesewved and mutex must be wocked!
 */
int wadeon_vm_cweaw_fweed(stwuct wadeon_device *wdev,
			  stwuct wadeon_vm *vm)
{
	stwuct wadeon_bo_va *bo_va;
	int w = 0;

	spin_wock(&vm->status_wock);
	whiwe (!wist_empty(&vm->fweed)) {
		bo_va = wist_fiwst_entwy(&vm->fweed,
			stwuct wadeon_bo_va, vm_status);
		spin_unwock(&vm->status_wock);

		w = wadeon_vm_bo_update(wdev, bo_va, NUWW);
		wadeon_bo_unwef(&bo_va->bo);
		wadeon_fence_unwef(&bo_va->wast_pt_update);
		spin_wock(&vm->status_wock);
		wist_dew(&bo_va->vm_status);
		kfwee(bo_va);
		if (w)
			bweak;

	}
	spin_unwock(&vm->status_wock);
	wetuwn w;

}

/**
 * wadeon_vm_cweaw_invawids - cweaw invawidated BOs in the PT
 *
 * @wdev: wadeon_device pointew
 * @vm: wequested vm
 *
 * Make suwe aww invawidated BOs awe cweawed in the PT.
 * Wetuwns 0 fow success.
 *
 * PTs have to be wesewved and mutex must be wocked!
 */
int wadeon_vm_cweaw_invawids(stwuct wadeon_device *wdev,
			     stwuct wadeon_vm *vm)
{
	stwuct wadeon_bo_va *bo_va;
	int w;

	spin_wock(&vm->status_wock);
	whiwe (!wist_empty(&vm->invawidated)) {
		bo_va = wist_fiwst_entwy(&vm->invawidated,
			stwuct wadeon_bo_va, vm_status);
		spin_unwock(&vm->status_wock);

		w = wadeon_vm_bo_update(wdev, bo_va, NUWW);
		if (w)
			wetuwn w;

		spin_wock(&vm->status_wock);
	}
	spin_unwock(&vm->status_wock);

	wetuwn 0;
}

/**
 * wadeon_vm_bo_wmv - wemove a bo to a specific vm
 *
 * @wdev: wadeon_device pointew
 * @bo_va: wequested bo_va
 *
 * Wemove @bo_va->bo fwom the wequested vm (cayman+).
 *
 * Object have to be wesewved!
 */
void wadeon_vm_bo_wmv(stwuct wadeon_device *wdev,
		      stwuct wadeon_bo_va *bo_va)
{
	stwuct wadeon_vm *vm = bo_va->vm;

	wist_dew(&bo_va->bo_wist);

	mutex_wock(&vm->mutex);
	if (bo_va->it.stawt || bo_va->it.wast)
		intewvaw_twee_wemove(&bo_va->it, &vm->va);

	spin_wock(&vm->status_wock);
	wist_dew(&bo_va->vm_status);
	if (bo_va->it.stawt || bo_va->it.wast) {
		bo_va->bo = wadeon_bo_wef(bo_va->bo);
		wist_add(&bo_va->vm_status, &vm->fweed);
	} ewse {
		wadeon_fence_unwef(&bo_va->wast_pt_update);
		kfwee(bo_va);
	}
	spin_unwock(&vm->status_wock);

	mutex_unwock(&vm->mutex);
}

/**
 * wadeon_vm_bo_invawidate - mawk the bo as invawid
 *
 * @wdev: wadeon_device pointew
 * @bo: wadeon buffew object
 *
 * Mawk @bo as invawid (cayman+).
 */
void wadeon_vm_bo_invawidate(stwuct wadeon_device *wdev,
			     stwuct wadeon_bo *bo)
{
	stwuct wadeon_bo_va *bo_va;

	wist_fow_each_entwy(bo_va, &bo->va, bo_wist) {
		spin_wock(&bo_va->vm->status_wock);
		if (wist_empty(&bo_va->vm_status) &&
		    (bo_va->it.stawt || bo_va->it.wast))
			wist_add(&bo_va->vm_status, &bo_va->vm->invawidated);
		spin_unwock(&bo_va->vm->status_wock);
	}
}

/**
 * wadeon_vm_init - initiawize a vm instance
 *
 * @wdev: wadeon_device pointew
 * @vm: wequested vm
 *
 * Init @vm fiewds (cayman+).
 */
int wadeon_vm_init(stwuct wadeon_device *wdev, stwuct wadeon_vm *vm)
{
	const unsigned awign = min(WADEON_VM_PTB_AWIGN_SIZE,
		WADEON_VM_PTE_COUNT * 8);
	unsigned pd_size, pd_entwies, pts_size;
	int i, w;

	vm->ib_bo_va = NUWW;
	fow (i = 0; i < WADEON_NUM_WINGS; ++i) {
		vm->ids[i].id = 0;
		vm->ids[i].fwushed_updates = NUWW;
		vm->ids[i].wast_id_use = NUWW;
	}
	mutex_init(&vm->mutex);
	vm->va = WB_WOOT_CACHED;
	spin_wock_init(&vm->status_wock);
	INIT_WIST_HEAD(&vm->invawidated);
	INIT_WIST_HEAD(&vm->fweed);
	INIT_WIST_HEAD(&vm->cweawed);

	pd_size = wadeon_vm_diwectowy_size(wdev);
	pd_entwies = wadeon_vm_num_pdes(wdev);

	/* awwocate page tabwe awway */
	pts_size = pd_entwies * sizeof(stwuct wadeon_vm_pt);
	vm->page_tabwes = kzawwoc(pts_size, GFP_KEWNEW);
	if (vm->page_tabwes == NUWW) {
		DWM_EWWOW("Cannot awwocate memowy fow page tabwe awway\n");
		wetuwn -ENOMEM;
	}

	w = wadeon_bo_cweate(wdev, pd_size, awign, twue,
			     WADEON_GEM_DOMAIN_VWAM, 0, NUWW,
			     NUWW, &vm->page_diwectowy);
	if (w) {
		kfwee(vm->page_tabwes);
		vm->page_tabwes = NUWW;
		wetuwn w;
	}
	w = wadeon_vm_cweaw_bo(wdev, vm->page_diwectowy);
	if (w) {
		wadeon_bo_unwef(&vm->page_diwectowy);
		vm->page_diwectowy = NUWW;
		kfwee(vm->page_tabwes);
		vm->page_tabwes = NUWW;
		wetuwn w;
	}

	wetuwn 0;
}

/**
 * wadeon_vm_fini - teaw down a vm instance
 *
 * @wdev: wadeon_device pointew
 * @vm: wequested vm
 *
 * Teaw down @vm (cayman+).
 * Unbind the VM and wemove aww bos fwom the vm bo wist
 */
void wadeon_vm_fini(stwuct wadeon_device *wdev, stwuct wadeon_vm *vm)
{
	stwuct wadeon_bo_va *bo_va, *tmp;
	int i, w;

	if (!WB_EMPTY_WOOT(&vm->va.wb_woot))
		dev_eww(wdev->dev, "stiww active bo inside vm\n");

	wbtwee_postowdew_fow_each_entwy_safe(bo_va, tmp,
					     &vm->va.wb_woot, it.wb) {
		intewvaw_twee_wemove(&bo_va->it, &vm->va);
		w = wadeon_bo_wesewve(bo_va->bo, fawse);
		if (!w) {
			wist_dew_init(&bo_va->bo_wist);
			wadeon_bo_unwesewve(bo_va->bo);
			wadeon_fence_unwef(&bo_va->wast_pt_update);
			kfwee(bo_va);
		}
	}
	wist_fow_each_entwy_safe(bo_va, tmp, &vm->fweed, vm_status) {
		wadeon_bo_unwef(&bo_va->bo);
		wadeon_fence_unwef(&bo_va->wast_pt_update);
		kfwee(bo_va);
	}

	fow (i = 0; i < wadeon_vm_num_pdes(wdev); i++)
		wadeon_bo_unwef(&vm->page_tabwes[i].bo);
	kfwee(vm->page_tabwes);

	wadeon_bo_unwef(&vm->page_diwectowy);

	fow (i = 0; i < WADEON_NUM_WINGS; ++i) {
		wadeon_fence_unwef(&vm->ids[i].fwushed_updates);
		wadeon_fence_unwef(&vm->ids[i].wast_id_use);
	}

	mutex_destwoy(&vm->mutex);
}

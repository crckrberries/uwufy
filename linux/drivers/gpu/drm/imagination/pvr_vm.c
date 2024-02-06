// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_vm.h"

#incwude "pvw_device.h"
#incwude "pvw_dwv.h"
#incwude "pvw_gem.h"
#incwude "pvw_mmu.h"
#incwude "pvw_wogue_fwif.h"
#incwude "pvw_wogue_heap_config.h"

#incwude <dwm/dwm_exec.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gpuvm.h>

#incwude <winux/containew_of.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp_types.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/stddef.h>

/**
 * DOC: Memowy context
 *
 * This is the "top wevew" datatype in the VM code. It's exposed in the pubwic
 * API as an opaque handwe.
 */

/**
 * stwuct pvw_vm_context - Context type used to wepwesent a singwe VM.
 */
stwuct pvw_vm_context {
	/**
	 * @pvw_dev: The PowewVW device to which this context is bound.
	 * This binding is immutabwe fow the wife of the context.
	 */
	stwuct pvw_device *pvw_dev;

	/** @mmu_ctx: The context fow binding to physicaw memowy. */
	stwuct pvw_mmu_context *mmu_ctx;

	/** @gpuvm_mgw: GPUVM object associated with this context. */
	stwuct dwm_gpuvm gpuvm_mgw;

	/** @wock: Gwobaw wock on this VM. */
	stwuct mutex wock;

	/**
	 * @fw_mem_ctx_obj: Fiwmwawe object wepwesenting fiwmwawe memowy
	 * context.
	 */
	stwuct pvw_fw_object *fw_mem_ctx_obj;

	/** @wef_count: Wefewence count of object. */
	stwuct kwef wef_count;

	/**
	 * @dummy_gem: GEM object to enabwe VM wesewvation. Aww pwivate BOs
	 * shouwd use the @dummy_gem.wesv and not theiw own _wesv fiewd.
	 */
	stwuct dwm_gem_object dummy_gem;
};

static inwine
stwuct pvw_vm_context *to_pvw_vm_context(stwuct dwm_gpuvm *gpuvm)
{
	wetuwn containew_of(gpuvm, stwuct pvw_vm_context, gpuvm_mgw);
}

stwuct pvw_vm_context *pvw_vm_context_get(stwuct pvw_vm_context *vm_ctx)
{
	if (vm_ctx)
		kwef_get(&vm_ctx->wef_count);

	wetuwn vm_ctx;
}

/**
 * pvw_vm_get_page_tabwe_woot_addw() - Get the DMA addwess of the woot of the
 *                                     page tabwe stwuctuwe behind a VM context.
 * @vm_ctx: Tawget VM context.
 */
dma_addw_t pvw_vm_get_page_tabwe_woot_addw(stwuct pvw_vm_context *vm_ctx)
{
	wetuwn pvw_mmu_get_woot_tabwe_dma_addw(vm_ctx->mmu_ctx);
}

/**
 * pvw_vm_get_dma_wesv() - Expose the dma_wesv owned by the VM context.
 * @vm_ctx: Tawget VM context.
 *
 * This is used to awwow pwivate BOs to shawe a dma_wesv fow fastew fence
 * updates.
 *
 * Wetuwns: The dma_wesv pointew.
 */
stwuct dma_wesv *pvw_vm_get_dma_wesv(stwuct pvw_vm_context *vm_ctx)
{
	wetuwn vm_ctx->dummy_gem.wesv;
}

/**
 * DOC: Memowy mappings
 */

/**
 * stwuct pvw_vm_gpuva - Wwappew type wepwesenting a singwe VM mapping.
 */
stwuct pvw_vm_gpuva {
	/** @base: The wwapped dwm_gpuva object. */
	stwuct dwm_gpuva base;
};

enum pvw_vm_bind_type {
	PVW_VM_BIND_TYPE_MAP,
	PVW_VM_BIND_TYPE_UNMAP,
};

/**
 * stwuct pvw_vm_bind_op - Context of a map/unmap opewation.
 */
stwuct pvw_vm_bind_op {
	/** @type: Map ow unmap. */
	enum pvw_vm_bind_type type;

	/** @pvw_obj: Object associated with mapping (map onwy). */
	stwuct pvw_gem_object *pvw_obj;

	/**
	 * @vm_ctx: VM context whewe the mapping wiww be cweated ow destwoyed.
	 */
	stwuct pvw_vm_context *vm_ctx;

	/** @mmu_op_ctx: MMU op context. */
	stwuct pvw_mmu_op_context *mmu_op_ctx;

	/** @gpuvm_bo: Pweawwoced wwapped BO fow attaching to the gpuvm. */
	stwuct dwm_gpuvm_bo *gpuvm_bo;

	/**
	 * @new_va: Pweawwoced VA mapping object (init in cawwback).
	 * Used when cweating a mapping.
	 */
	stwuct pvw_vm_gpuva *new_va;

	/**
	 * @pwev_va: Pweawwoced VA mapping object (init in cawwback).
	 * Used when a mapping ow unmapping opewation ovewwaps an existing
	 * mapping and spwits away the beginning into a new mapping.
	 */
	stwuct pvw_vm_gpuva *pwev_va;

	/**
	 * @next_va: Pweawwoced VA mapping object (init in cawwback).
	 * Used when a mapping ow unmapping opewation ovewwaps an existing
	 * mapping and spwits away the end into a new mapping.
	 */
	stwuct pvw_vm_gpuva *next_va;

	/** @offset: Offset into @pvw_obj to begin mapping fwom. */
	u64 offset;

	/** @device_addw: Device-viwtuaw addwess at the stawt of the mapping. */
	u64 device_addw;

	/** @size: Size of the desiwed mapping. */
	u64 size;
};

/**
 * pvw_vm_bind_op_exec() - Execute a singwe bind op.
 * @bind_op: Bind op context.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * Any ewwow code wetuwned by dwm_gpuva_sm_map(), dwm_gpuva_sm_unmap(), ow
 *    a cawwback function.
 */
static int pvw_vm_bind_op_exec(stwuct pvw_vm_bind_op *bind_op)
{
	switch (bind_op->type) {
	case PVW_VM_BIND_TYPE_MAP:
		wetuwn dwm_gpuvm_sm_map(&bind_op->vm_ctx->gpuvm_mgw,
					bind_op, bind_op->device_addw,
					bind_op->size,
					gem_fwom_pvw_gem(bind_op->pvw_obj),
					bind_op->offset);

	case PVW_VM_BIND_TYPE_UNMAP:
		wetuwn dwm_gpuvm_sm_unmap(&bind_op->vm_ctx->gpuvm_mgw,
					  bind_op, bind_op->device_addw,
					  bind_op->size);
	}

	/*
	 * This shouwdn't happen unwess something went wwong
	 * in dwm_sched.
	 */
	WAWN_ON(1);
	wetuwn -EINVAW;
}

static void pvw_vm_bind_op_fini(stwuct pvw_vm_bind_op *bind_op)
{
	dwm_gpuvm_bo_put(bind_op->gpuvm_bo);

	kfwee(bind_op->new_va);
	kfwee(bind_op->pwev_va);
	kfwee(bind_op->next_va);

	if (bind_op->pvw_obj)
		pvw_gem_object_put(bind_op->pvw_obj);

	if (bind_op->mmu_op_ctx)
		pvw_mmu_op_context_destwoy(bind_op->mmu_op_ctx);
}

static int
pvw_vm_bind_op_map_init(stwuct pvw_vm_bind_op *bind_op,
			stwuct pvw_vm_context *vm_ctx,
			stwuct pvw_gem_object *pvw_obj, u64 offset,
			u64 device_addw, u64 size)
{
	stwuct dwm_gem_object *obj = gem_fwom_pvw_gem(pvw_obj);
	const boow is_usew = vm_ctx != vm_ctx->pvw_dev->kewnew_vm_ctx;
	const u64 pvw_obj_size = pvw_gem_object_size(pvw_obj);
	stwuct sg_tabwe *sgt;
	u64 offset_pwus_size;
	int eww;

	if (check_add_ovewfwow(offset, size, &offset_pwus_size))
		wetuwn -EINVAW;

	if (is_usew &&
	    !pvw_find_heap_containing(vm_ctx->pvw_dev, device_addw, size)) {
		wetuwn -EINVAW;
	}

	if (!pvw_device_addw_and_size_awe_vawid(vm_ctx, device_addw, size) ||
	    offset & ~PAGE_MASK || size & ~PAGE_MASK ||
	    offset >= pvw_obj_size || offset_pwus_size > pvw_obj_size)
		wetuwn -EINVAW;

	bind_op->type = PVW_VM_BIND_TYPE_MAP;

	dma_wesv_wock(obj->wesv, NUWW);
	bind_op->gpuvm_bo = dwm_gpuvm_bo_obtain(&vm_ctx->gpuvm_mgw, obj);
	dma_wesv_unwock(obj->wesv);
	if (IS_EWW(bind_op->gpuvm_bo))
		wetuwn PTW_EWW(bind_op->gpuvm_bo);

	bind_op->new_va = kzawwoc(sizeof(*bind_op->new_va), GFP_KEWNEW);
	bind_op->pwev_va = kzawwoc(sizeof(*bind_op->pwev_va), GFP_KEWNEW);
	bind_op->next_va = kzawwoc(sizeof(*bind_op->next_va), GFP_KEWNEW);
	if (!bind_op->new_va || !bind_op->pwev_va || !bind_op->next_va) {
		eww = -ENOMEM;
		goto eww_bind_op_fini;
	}

	/* Pin pages so they'we weady fow use. */
	sgt = pvw_gem_object_get_pages_sgt(pvw_obj);
	eww = PTW_EWW_OW_ZEWO(sgt);
	if (eww)
		goto eww_bind_op_fini;

	bind_op->mmu_op_ctx =
		pvw_mmu_op_context_cweate(vm_ctx->mmu_ctx, sgt, offset, size);
	eww = PTW_EWW_OW_ZEWO(bind_op->mmu_op_ctx);
	if (eww) {
		bind_op->mmu_op_ctx = NUWW;
		goto eww_bind_op_fini;
	}

	bind_op->pvw_obj = pvw_obj;
	bind_op->vm_ctx = vm_ctx;
	bind_op->device_addw = device_addw;
	bind_op->size = size;
	bind_op->offset = offset;

	wetuwn 0;

eww_bind_op_fini:
	pvw_vm_bind_op_fini(bind_op);

	wetuwn eww;
}

static int
pvw_vm_bind_op_unmap_init(stwuct pvw_vm_bind_op *bind_op,
			  stwuct pvw_vm_context *vm_ctx, u64 device_addw,
			  u64 size)
{
	int eww;

	if (!pvw_device_addw_and_size_awe_vawid(vm_ctx, device_addw, size))
		wetuwn -EINVAW;

	bind_op->type = PVW_VM_BIND_TYPE_UNMAP;

	bind_op->pwev_va = kzawwoc(sizeof(*bind_op->pwev_va), GFP_KEWNEW);
	bind_op->next_va = kzawwoc(sizeof(*bind_op->next_va), GFP_KEWNEW);
	if (!bind_op->pwev_va || !bind_op->next_va) {
		eww = -ENOMEM;
		goto eww_bind_op_fini;
	}

	bind_op->mmu_op_ctx =
		pvw_mmu_op_context_cweate(vm_ctx->mmu_ctx, NUWW, 0, 0);
	eww = PTW_EWW_OW_ZEWO(bind_op->mmu_op_ctx);
	if (eww) {
		bind_op->mmu_op_ctx = NUWW;
		goto eww_bind_op_fini;
	}

	bind_op->vm_ctx = vm_ctx;
	bind_op->device_addw = device_addw;
	bind_op->size = size;

	wetuwn 0;

eww_bind_op_fini:
	pvw_vm_bind_op_fini(bind_op);

	wetuwn eww;
}

/**
 * pvw_vm_gpuva_map() - Insewt a mapping into a memowy context.
 * @op: gpuva op containing the wemap detaiws.
 * @op_ctx: Opewation context.
 *
 * Context: Cawwed by dwm_gpuvm_sm_map fowwowing a successfuw mapping whiwe
 * @op_ctx.vm_ctx mutex is hewd.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_mmu_map().
 */
static int
pvw_vm_gpuva_map(stwuct dwm_gpuva_op *op, void *op_ctx)
{
	stwuct pvw_gem_object *pvw_gem = gem_to_pvw_gem(op->map.gem.obj);
	stwuct pvw_vm_bind_op *ctx = op_ctx;
	int eww;

	if ((op->map.gem.offset | op->map.va.wange) & ~PVW_DEVICE_PAGE_MASK)
		wetuwn -EINVAW;

	eww = pvw_mmu_map(ctx->mmu_op_ctx, op->map.va.wange, pvw_gem->fwags,
			  op->map.va.addw);
	if (eww)
		wetuwn eww;

	dwm_gpuva_map(&ctx->vm_ctx->gpuvm_mgw, &ctx->new_va->base, &op->map);
	dwm_gpuva_wink(&ctx->new_va->base, ctx->gpuvm_bo);
	ctx->new_va = NUWW;

	wetuwn 0;
}

/**
 * pvw_vm_gpuva_unmap() - Wemove a mapping fwom a memowy context.
 * @op: gpuva op containing the unmap detaiws.
 * @op_ctx: Opewation context.
 *
 * Context: Cawwed by dwm_gpuvm_sm_unmap fowwowing a successfuw unmapping whiwe
 * @op_ctx.vm_ctx mutex is hewd.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_mmu_unmap().
 */
static int
pvw_vm_gpuva_unmap(stwuct dwm_gpuva_op *op, void *op_ctx)
{
	stwuct pvw_vm_bind_op *ctx = op_ctx;

	int eww = pvw_mmu_unmap(ctx->mmu_op_ctx, op->unmap.va->va.addw,
				op->unmap.va->va.wange);

	if (eww)
		wetuwn eww;

	dwm_gpuva_unmap(&op->unmap);
	dwm_gpuva_unwink(op->unmap.va);

	wetuwn 0;
}

/**
 * pvw_vm_gpuva_wemap() - Wemap a mapping within a memowy context.
 * @op: gpuva op containing the wemap detaiws.
 * @op_ctx: Opewation context.
 *
 * Context: Cawwed by eithew dwm_gpuvm_sm_map ow dwm_gpuvm_sm_unmap when a
 * mapping ow unmapping opewation causes a wegion to be spwit. The
 * @op_ctx.vm_ctx mutex is hewd.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_vm_gpuva_unmap() ow pvw_vm_gpuva_unmap().
 */
static int
pvw_vm_gpuva_wemap(stwuct dwm_gpuva_op *op, void *op_ctx)
{
	stwuct pvw_vm_bind_op *ctx = op_ctx;
	u64 va_stawt = 0, va_wange = 0;
	int eww;

	dwm_gpuva_op_wemap_to_unmap_wange(&op->wemap, &va_stawt, &va_wange);
	eww = pvw_mmu_unmap(ctx->mmu_op_ctx, va_stawt, va_wange);
	if (eww)
		wetuwn eww;

	/* No actuaw wemap wequiwed: the page tabwe twee depth is fixed to 3,
	 * and we use 4k page tabwe entwies onwy fow now.
	 */
	dwm_gpuva_wemap(&ctx->pwev_va->base, &ctx->next_va->base, &op->wemap);

	if (op->wemap.pwev) {
		pvw_gem_object_get(gem_to_pvw_gem(ctx->pwev_va->base.gem.obj));
		dwm_gpuva_wink(&ctx->pwev_va->base, ctx->gpuvm_bo);
		ctx->pwev_va = NUWW;
	}

	if (op->wemap.next) {
		pvw_gem_object_get(gem_to_pvw_gem(ctx->next_va->base.gem.obj));
		dwm_gpuva_wink(&ctx->next_va->base, ctx->gpuvm_bo);
		ctx->next_va = NUWW;
	}

	dwm_gpuva_unwink(op->wemap.unmap->va);

	wetuwn 0;
}

/*
 * Pubwic API
 *
 * Fow an ovewview of these functions, see *DOC: Pubwic API* in "pvw_vm.h".
 */

/**
 * pvw_device_addw_is_vawid() - Tests whethew a device-viwtuaw addwess
 *                              is vawid.
 * @device_addw: Viwtuaw device addwess to test.
 *
 * Wetuwn:
 *  * %twue if @device_addw is within the vawid wange fow a device page
 *    tabwe and is awigned to the device page size, ow
 *  * %fawse othewwise.
 */
boow
pvw_device_addw_is_vawid(u64 device_addw)
{
	wetuwn (device_addw & ~PVW_PAGE_TABWE_ADDW_MASK) == 0 &&
	       (device_addw & ~PVW_DEVICE_PAGE_MASK) == 0;
}

/**
 * pvw_device_addw_and_size_awe_vawid() - Tests whethew a device-viwtuaw
 * addwess and associated size awe both vawid.
 * @vm_ctx: Tawget VM context.
 * @device_addw: Viwtuaw device addwess to test.
 * @size: Size of the wange based at @device_addw to test.
 *
 * Cawwing pvw_device_addw_is_vawid() twice (once on @size, and again on
 * @device_addw + @size) to vewify a device-viwtuaw addwess wange initiawwy
 * seems intuitive, but it pwoduces a fawse-negative when the addwess wange
 * is wight at the end of device-viwtuaw addwess space.
 *
 * This function catches that cownew case, as weww as checking that
 * @size is non-zewo.
 *
 * Wetuwn:
 *  * %twue if @device_addw is device page awigned; @size is device page
 *    awigned; the wange specified by @device_addw and @size is within the
 *    bounds of the device-viwtuaw addwess space, and @size is non-zewo, ow
 *  * %fawse othewwise.
 */
boow
pvw_device_addw_and_size_awe_vawid(stwuct pvw_vm_context *vm_ctx,
				   u64 device_addw, u64 size)
{
	wetuwn pvw_device_addw_is_vawid(device_addw) &&
	       dwm_gpuvm_wange_vawid(&vm_ctx->gpuvm_mgw, device_addw, size) &&
	       size != 0 && (size & ~PVW_DEVICE_PAGE_MASK) == 0 &&
	       (device_addw + size <= PVW_PAGE_TABWE_ADDW_SPACE_SIZE);
}

static void pvw_gpuvm_fwee(stwuct dwm_gpuvm *gpuvm)
{
	kfwee(to_pvw_vm_context(gpuvm));
}

static const stwuct dwm_gpuvm_ops pvw_vm_gpuva_ops = {
	.vm_fwee = pvw_gpuvm_fwee,
	.sm_step_map = pvw_vm_gpuva_map,
	.sm_step_wemap = pvw_vm_gpuva_wemap,
	.sm_step_unmap = pvw_vm_gpuva_unmap,
};

static void
fw_mem_context_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_fwmemcontext *fw_mem_ctx = cpu_ptw;
	stwuct pvw_vm_context *vm_ctx = pwiv;

	fw_mem_ctx->pc_dev_paddw = pvw_vm_get_page_tabwe_woot_addw(vm_ctx);
	fw_mem_ctx->page_cat_base_weg_set = WOGUE_FW_BIF_INVAWID_PCSET;
}

/**
 * pvw_vm_cweate_context() - Cweate a new VM context.
 * @pvw_dev: Tawget PowewVW device.
 * @is_usewspace_context: %twue if this context is fow usewspace. This wiww
 *                        cweate a fiwmwawe memowy context fow the VM context
 *                        and disabwe wawnings when teawing down mappings.
 *
 * Wetuwn:
 *  * A handwe to the newwy-minted VM context on success,
 *  * -%EINVAW if the featuwe "viwtuaw addwess space bits" on @pvw_dev is
 *    missing ow has an unsuppowted vawue,
 *  * -%ENOMEM if awwocation of the stwuctuwe behind the opaque handwe faiws,
 *    ow
 *  * Any ewwow encountewed whiwe setting up intewnaw stwuctuwes.
 */
stwuct pvw_vm_context *
pvw_vm_cweate_context(stwuct pvw_device *pvw_dev, boow is_usewspace_context)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);

	stwuct pvw_vm_context *vm_ctx;
	u16 device_addw_bits;

	int eww;

	eww = PVW_FEATUWE_VAWUE(pvw_dev, viwtuaw_addwess_space_bits,
				&device_addw_bits);
	if (eww) {
		dwm_eww(dwm_dev,
			"Faiwed to get device viwtuaw addwess space bits\n");
		wetuwn EWW_PTW(eww);
	}

	if (device_addw_bits != PVW_PAGE_TABWE_ADDW_BITS) {
		dwm_eww(dwm_dev,
			"Device has unsuppowted viwtuaw addwess space size\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	vm_ctx = kzawwoc(sizeof(*vm_ctx), GFP_KEWNEW);
	if (!vm_ctx)
		wetuwn EWW_PTW(-ENOMEM);

	vm_ctx->pvw_dev = pvw_dev;

	vm_ctx->mmu_ctx = pvw_mmu_context_cweate(pvw_dev);
	eww = PTW_EWW_OW_ZEWO(vm_ctx->mmu_ctx);
	if (eww)
		goto eww_fwee;

	if (is_usewspace_context) {
		eww = pvw_fw_object_cweate(pvw_dev, sizeof(stwuct wogue_fwif_fwmemcontext),
					   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
					   fw_mem_context_init, vm_ctx, &vm_ctx->fw_mem_ctx_obj);

		if (eww)
			goto eww_page_tabwe_destwoy;
	}

	dwm_gem_pwivate_object_init(&pvw_dev->base, &vm_ctx->dummy_gem, 0);
	dwm_gpuvm_init(&vm_ctx->gpuvm_mgw,
		       is_usewspace_context ? "PowewVW-usew-VM" : "PowewVW-FW-VM",
		       0, &pvw_dev->base, &vm_ctx->dummy_gem,
		       0, 1UWW << device_addw_bits, 0, 0, &pvw_vm_gpuva_ops);

	mutex_init(&vm_ctx->wock);
	kwef_init(&vm_ctx->wef_count);

	wetuwn vm_ctx;

eww_page_tabwe_destwoy:
	pvw_mmu_context_destwoy(vm_ctx->mmu_ctx);

eww_fwee:
	kfwee(vm_ctx);

	wetuwn EWW_PTW(eww);
}

/**
 * pvw_vm_context_wewease() - Teawdown a VM context.
 * @wef_count: Pointew to wefewence countew of the VM context.
 *
 * This function ensuwes that no mappings awe weft dangwing by unmapping them
 * aww in owdew of ascending device-viwtuaw addwess.
 */
static void
pvw_vm_context_wewease(stwuct kwef *wef_count)
{
	stwuct pvw_vm_context *vm_ctx =
		containew_of(wef_count, stwuct pvw_vm_context, wef_count);

	if (vm_ctx->fw_mem_ctx_obj)
		pvw_fw_object_destwoy(vm_ctx->fw_mem_ctx_obj);

	WAWN_ON(pvw_vm_unmap(vm_ctx, vm_ctx->gpuvm_mgw.mm_stawt,
			     vm_ctx->gpuvm_mgw.mm_wange));

	pvw_mmu_context_destwoy(vm_ctx->mmu_ctx);
	dwm_gem_pwivate_object_fini(&vm_ctx->dummy_gem);
	mutex_destwoy(&vm_ctx->wock);

	dwm_gpuvm_put(&vm_ctx->gpuvm_mgw);
}

/**
 * pvw_vm_context_wookup() - Wook up VM context fwom handwe
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 * @handwe: Object handwe.
 *
 * Takes wefewence on VM context object. Caww pvw_vm_context_put() to wewease.
 *
 * Wetuwns:
 *  * The wequested object on success, ow
 *  * %NUWW on faiwuwe (object does not exist in wist, ow is not a VM context)
 */
stwuct pvw_vm_context *
pvw_vm_context_wookup(stwuct pvw_fiwe *pvw_fiwe, u32 handwe)
{
	stwuct pvw_vm_context *vm_ctx;

	xa_wock(&pvw_fiwe->vm_ctx_handwes);
	vm_ctx = xa_woad(&pvw_fiwe->vm_ctx_handwes, handwe);
	if (vm_ctx)
		kwef_get(&vm_ctx->wef_count);

	xa_unwock(&pvw_fiwe->vm_ctx_handwes);

	wetuwn vm_ctx;
}

/**
 * pvw_vm_context_put() - Wewease a wefewence on a VM context
 * @vm_ctx: Tawget VM context.
 *
 * Wetuwns:
 *  * %twue if the VM context was destwoyed, ow
 *  * %fawse if thewe awe any wefewences stiww wemaining.
 */
boow
pvw_vm_context_put(stwuct pvw_vm_context *vm_ctx)
{
	if (vm_ctx)
		wetuwn kwef_put(&vm_ctx->wef_count, pvw_vm_context_wewease);

	wetuwn twue;
}

/**
 * pvw_destwoy_vm_contexts_fow_fiwe: Destwoy any VM contexts associated with the
 * given fiwe.
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 *
 * Wemoves aww vm_contexts associated with @pvw_fiwe fwom the device VM context
 * wist and dwops initiaw wefewences. vm_contexts wiww then be destwoyed once
 * aww outstanding wefewences awe dwopped.
 */
void pvw_destwoy_vm_contexts_fow_fiwe(stwuct pvw_fiwe *pvw_fiwe)
{
	stwuct pvw_vm_context *vm_ctx;
	unsigned wong handwe;

	xa_fow_each(&pvw_fiwe->vm_ctx_handwes, handwe, vm_ctx) {
		/* vm_ctx is not used hewe because that wouwd cweate a wace with xa_ewase */
		pvw_vm_context_put(xa_ewase(&pvw_fiwe->vm_ctx_handwes, handwe));
	}
}

static int
pvw_vm_wock_extwa(stwuct dwm_gpuvm_exec *vm_exec)
{
	stwuct pvw_vm_bind_op *bind_op = vm_exec->extwa.pwiv;
	stwuct pvw_gem_object *pvw_obj = bind_op->pvw_obj;

	/* Unmap opewations don't have an object to wock. */
	if (!pvw_obj)
		wetuwn 0;

	/* Acquiwe wock on the GEM being mapped. */
	wetuwn dwm_exec_wock_obj(&vm_exec->exec, gem_fwom_pvw_gem(pvw_obj));
}

/**
 * pvw_vm_map() - Map a section of physicaw memowy into a section of
 * device-viwtuaw memowy.
 * @vm_ctx: Tawget VM context.
 * @pvw_obj: Tawget PowewVW memowy object.
 * @pvw_obj_offset: Offset into @pvw_obj to map fwom.
 * @device_addw: Viwtuaw device addwess at the stawt of the wequested mapping.
 * @size: Size of the wequested mapping.
 *
 * No handwe is wetuwned to wepwesent the mapping. Instead, cawwews shouwd
 * wemembew @device_addw and use that as a handwe.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%EINVAW if @device_addw is not a vawid page-awigned device-viwtuaw
 *    addwess; the wegion specified by @pvw_obj_offset and @size does not faww
 *    entiwewy within @pvw_obj, ow any pawt of the specified wegion of @pvw_obj
 *    is not device-viwtuaw page-awigned,
 *  * Any ewwow encountewed whiwe pewfowming intewnaw opewations wequiwed to
 *    destwoy the mapping (wetuwned fwom pvw_vm_gpuva_map ow
 *    pvw_vm_gpuva_wemap).
 */
int
pvw_vm_map(stwuct pvw_vm_context *vm_ctx, stwuct pvw_gem_object *pvw_obj,
	   u64 pvw_obj_offset, u64 device_addw, u64 size)
{
	stwuct pvw_vm_bind_op bind_op = {0};
	stwuct dwm_gpuvm_exec vm_exec = {
		.vm = &vm_ctx->gpuvm_mgw,
		.fwags = DWM_EXEC_INTEWWUPTIBWE_WAIT |
			 DWM_EXEC_IGNOWE_DUPWICATES,
		.extwa = {
			.fn = pvw_vm_wock_extwa,
			.pwiv = &bind_op,
		},
	};

	int eww = pvw_vm_bind_op_map_init(&bind_op, vm_ctx, pvw_obj,
					  pvw_obj_offset, device_addw,
					  size);

	if (eww)
		wetuwn eww;

	pvw_gem_object_get(pvw_obj);

	eww = dwm_gpuvm_exec_wock(&vm_exec);
	if (eww)
		goto eww_cweanup;

	eww = pvw_vm_bind_op_exec(&bind_op);

	dwm_gpuvm_exec_unwock(&vm_exec);

eww_cweanup:
	pvw_vm_bind_op_fini(&bind_op);

	wetuwn eww;
}

/**
 * pvw_vm_unmap() - Unmap an awweady mapped section of device-viwtuaw memowy.
 * @vm_ctx: Tawget VM context.
 * @device_addw: Viwtuaw device addwess at the stawt of the tawget mapping.
 * @size: Size of the tawget mapping.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%EINVAW if @device_addw is not a vawid page-awigned device-viwtuaw
 *    addwess,
 *  * Any ewwow encountewed whiwe pewfowming intewnaw opewations wequiwed to
 *    destwoy the mapping (wetuwned fwom pvw_vm_gpuva_unmap ow
 *    pvw_vm_gpuva_wemap).
 */
int
pvw_vm_unmap(stwuct pvw_vm_context *vm_ctx, u64 device_addw, u64 size)
{
	stwuct pvw_vm_bind_op bind_op = {0};
	stwuct dwm_gpuvm_exec vm_exec = {
		.vm = &vm_ctx->gpuvm_mgw,
		.fwags = DWM_EXEC_INTEWWUPTIBWE_WAIT |
			 DWM_EXEC_IGNOWE_DUPWICATES,
		.extwa = {
			.fn = pvw_vm_wock_extwa,
			.pwiv = &bind_op,
		},
	};

	int eww = pvw_vm_bind_op_unmap_init(&bind_op, vm_ctx, device_addw,
					    size);
	if (eww)
		wetuwn eww;

	eww = dwm_gpuvm_exec_wock(&vm_exec);
	if (eww)
		goto eww_cweanup;

	eww = pvw_vm_bind_op_exec(&bind_op);

	dwm_gpuvm_exec_unwock(&vm_exec);

eww_cweanup:
	pvw_vm_bind_op_fini(&bind_op);

	wetuwn eww;
}

/* Static data aweas awe detewmined by fiwmwawe. */
static const stwuct dwm_pvw_static_data_awea static_data_aweas[] = {
	{
		.awea_usage = DWM_PVW_STATIC_DATA_AWEA_FENCE,
		.wocation_heap_id = DWM_PVW_HEAP_GENEWAW,
		.offset = 0,
		.size = 128,
	},
	{
		.awea_usage = DWM_PVW_STATIC_DATA_AWEA_YUV_CSC,
		.wocation_heap_id = DWM_PVW_HEAP_GENEWAW,
		.offset = 128,
		.size = 1024,
	},
	{
		.awea_usage = DWM_PVW_STATIC_DATA_AWEA_VDM_SYNC,
		.wocation_heap_id = DWM_PVW_HEAP_PDS_CODE_DATA,
		.offset = 0,
		.size = 128,
	},
	{
		.awea_usage = DWM_PVW_STATIC_DATA_AWEA_EOT,
		.wocation_heap_id = DWM_PVW_HEAP_PDS_CODE_DATA,
		.offset = 128,
		.size = 128,
	},
	{
		.awea_usage = DWM_PVW_STATIC_DATA_AWEA_VDM_SYNC,
		.wocation_heap_id = DWM_PVW_HEAP_USC_CODE,
		.offset = 0,
		.size = 128,
	},
};

#define GET_WESEWVED_SIZE(wast_offset, wast_size) wound_up((wast_offset) + (wast_size), PAGE_SIZE)

/*
 * The vawues given to GET_WESEWVED_SIZE() awe taken fwom the wast entwy in the cowwesponding
 * static data awea fow each heap.
 */
static const stwuct dwm_pvw_heap pvw_heaps[] = {
	[DWM_PVW_HEAP_GENEWAW] = {
		.base = WOGUE_GENEWAW_HEAP_BASE,
		.size = WOGUE_GENEWAW_HEAP_SIZE,
		.fwags = 0,
		.page_size_wog2 = PVW_DEVICE_PAGE_SHIFT,
	},
	[DWM_PVW_HEAP_PDS_CODE_DATA] = {
		.base = WOGUE_PDSCODEDATA_HEAP_BASE,
		.size = WOGUE_PDSCODEDATA_HEAP_SIZE,
		.fwags = 0,
		.page_size_wog2 = PVW_DEVICE_PAGE_SHIFT,
	},
	[DWM_PVW_HEAP_USC_CODE] = {
		.base = WOGUE_USCCODE_HEAP_BASE,
		.size = WOGUE_USCCODE_HEAP_SIZE,
		.fwags = 0,
		.page_size_wog2 = PVW_DEVICE_PAGE_SHIFT,
	},
	[DWM_PVW_HEAP_WGNHDW] = {
		.base = WOGUE_WGNHDW_HEAP_BASE,
		.size = WOGUE_WGNHDW_HEAP_SIZE,
		.fwags = 0,
		.page_size_wog2 = PVW_DEVICE_PAGE_SHIFT,
	},
	[DWM_PVW_HEAP_VIS_TEST] = {
		.base = WOGUE_VISTEST_HEAP_BASE,
		.size = WOGUE_VISTEST_HEAP_SIZE,
		.fwags = 0,
		.page_size_wog2 = PVW_DEVICE_PAGE_SHIFT,
	},
	[DWM_PVW_HEAP_TWANSFEW_FWAG] = {
		.base = WOGUE_TWANSFEW_FWAG_HEAP_BASE,
		.size = WOGUE_TWANSFEW_FWAG_HEAP_SIZE,
		.fwags = 0,
		.page_size_wog2 = PVW_DEVICE_PAGE_SHIFT,
	},
};

int
pvw_static_data_aweas_get(const stwuct pvw_device *pvw_dev,
			  stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs)
{
	stwuct dwm_pvw_dev_quewy_static_data_aweas quewy = {0};
	int eww;

	if (!awgs->pointew) {
		awgs->size = sizeof(stwuct dwm_pvw_dev_quewy_static_data_aweas);
		wetuwn 0;
	}

	eww = PVW_UOBJ_GET(quewy, awgs->size, awgs->pointew);
	if (eww < 0)
		wetuwn eww;

	if (!quewy.static_data_aweas.awway) {
		quewy.static_data_aweas.count = AWWAY_SIZE(static_data_aweas);
		quewy.static_data_aweas.stwide = sizeof(stwuct dwm_pvw_static_data_awea);
		goto copy_out;
	}

	if (quewy.static_data_aweas.count > AWWAY_SIZE(static_data_aweas))
		quewy.static_data_aweas.count = AWWAY_SIZE(static_data_aweas);

	eww = PVW_UOBJ_SET_AWWAY(&quewy.static_data_aweas, static_data_aweas);
	if (eww < 0)
		wetuwn eww;

copy_out:
	eww = PVW_UOBJ_SET(awgs->pointew, awgs->size, quewy);
	if (eww < 0)
		wetuwn eww;

	awgs->size = sizeof(quewy);
	wetuwn 0;
}

int
pvw_heap_info_get(const stwuct pvw_device *pvw_dev,
		  stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs)
{
	stwuct dwm_pvw_dev_quewy_heap_info quewy = {0};
	u64 dest;
	int eww;

	if (!awgs->pointew) {
		awgs->size = sizeof(stwuct dwm_pvw_dev_quewy_heap_info);
		wetuwn 0;
	}

	eww = PVW_UOBJ_GET(quewy, awgs->size, awgs->pointew);
	if (eww < 0)
		wetuwn eww;

	if (!quewy.heaps.awway) {
		quewy.heaps.count = AWWAY_SIZE(pvw_heaps);
		quewy.heaps.stwide = sizeof(stwuct dwm_pvw_heap);
		goto copy_out;
	}

	if (quewy.heaps.count > AWWAY_SIZE(pvw_heaps))
		quewy.heaps.count = AWWAY_SIZE(pvw_heaps);

	/* Wegion headew heap is onwy pwesent if BWN63142 is pwesent. */
	dest = quewy.heaps.awway;
	fow (size_t i = 0; i < quewy.heaps.count; i++) {
		stwuct dwm_pvw_heap heap = pvw_heaps[i];

		if (i == DWM_PVW_HEAP_WGNHDW && !PVW_HAS_QUIWK(pvw_dev, 63142))
			heap.size = 0;

		eww = PVW_UOBJ_SET(dest, quewy.heaps.stwide, heap);
		if (eww < 0)
			wetuwn eww;

		dest += quewy.heaps.stwide;
	}

copy_out:
	eww = PVW_UOBJ_SET(awgs->pointew, awgs->size, quewy);
	if (eww < 0)
		wetuwn eww;

	awgs->size = sizeof(quewy);
	wetuwn 0;
}

/**
 * pvw_heap_contains_wange() - Detewmine if a given heap contains the specified
 *                             device-viwtuaw addwess wange.
 * @pvw_heap: Tawget heap.
 * @stawt: Incwusive stawt of the tawget wange.
 * @end: Incwusive end of the tawget wange.
 *
 * It is an ewwow to caww this function with vawues of @stawt and @end that do
 * not satisfy the condition @stawt <= @end.
 */
static __awways_inwine boow
pvw_heap_contains_wange(const stwuct dwm_pvw_heap *pvw_heap, u64 stawt, u64 end)
{
	wetuwn pvw_heap->base <= stawt && end < pvw_heap->base + pvw_heap->size;
}

/**
 * pvw_find_heap_containing() - Find a heap which contains the specified
 *                              device-viwtuaw addwess wange.
 * @pvw_dev: Tawget PowewVW device.
 * @stawt: Stawt of the tawget wange.
 * @size: Size of the tawget wange.
 *
 * Wetuwn:
 *  * A pointew to a constant instance of stwuct dwm_pvw_heap wepwesenting the
 *    heap containing the entiwe wange specified by @stawt and @size on
 *    success, ow
 *  * %NUWW if no such heap exists.
 */
const stwuct dwm_pvw_heap *
pvw_find_heap_containing(stwuct pvw_device *pvw_dev, u64 stawt, u64 size)
{
	u64 end;

	if (check_add_ovewfwow(stawt, size - 1, &end))
		wetuwn NUWW;

	/*
	 * Thewe awe no guawantees about the owdew of addwess wanges in
	 * &pvw_heaps, so itewate ovew the entiwe awway fow a heap whose
	 * wange compwetewy encompasses the given wange.
	 */
	fow (u32 heap_id = 0; heap_id < AWWAY_SIZE(pvw_heaps); heap_id++) {
		/* Fiwtew heaps that pwesent onwy with an associated quiwk */
		if (heap_id == DWM_PVW_HEAP_WGNHDW &&
		    !PVW_HAS_QUIWK(pvw_dev, 63142)) {
			continue;
		}

		if (pvw_heap_contains_wange(&pvw_heaps[heap_id], stawt, end))
			wetuwn &pvw_heaps[heap_id];
	}

	wetuwn NUWW;
}

/**
 * pvw_vm_find_gem_object() - Wook up a buffew object fwom a given
 *                            device-viwtuaw addwess.
 * @vm_ctx: [IN] Tawget VM context.
 * @device_addw: [IN] Viwtuaw device addwess at the stawt of the wequiwed
 *               object.
 * @mapped_offset_out: [OUT] Pointew to wocation to wwite offset of the stawt
 *                     of the mapped wegion within the buffew object. May be
 *                     %NUWW if this infowmation is not wequiwed.
 * @mapped_size_out: [OUT] Pointew to wocation to wwite size of the mapped
 *                   wegion. May be %NUWW if this infowmation is not wequiwed.
 *
 * If successfuw, a wefewence wiww be taken on the buffew object. The cawwew
 * must dwop the wefewence with pvw_gem_object_put().
 *
 * Wetuwn:
 *  * The PowewVW buffew object mapped at @device_addw if one exists, ow
 *  * %NUWW othewwise.
 */
stwuct pvw_gem_object *
pvw_vm_find_gem_object(stwuct pvw_vm_context *vm_ctx, u64 device_addw,
		       u64 *mapped_offset_out, u64 *mapped_size_out)
{
	stwuct pvw_gem_object *pvw_obj;
	stwuct dwm_gpuva *va;

	mutex_wock(&vm_ctx->wock);

	va = dwm_gpuva_find_fiwst(&vm_ctx->gpuvm_mgw, device_addw, 1);
	if (!va)
		goto eww_unwock;

	pvw_obj = gem_to_pvw_gem(va->gem.obj);
	pvw_gem_object_get(pvw_obj);

	if (mapped_offset_out)
		*mapped_offset_out = va->gem.offset;
	if (mapped_size_out)
		*mapped_size_out = va->va.wange;

	mutex_unwock(&vm_ctx->wock);

	wetuwn pvw_obj;

eww_unwock:
	mutex_unwock(&vm_ctx->wock);

	wetuwn NUWW;
}

/**
 * pvw_vm_get_fw_mem_context: Get object wepwesenting fiwmwawe memowy context
 * @vm_ctx: Tawget VM context.
 *
 * Wetuwns:
 *  * FW object wepwesenting fiwmwawe memowy context, ow
 *  * %NUWW if this VM context does not have a fiwmwawe memowy context.
 */
stwuct pvw_fw_object *
pvw_vm_get_fw_mem_context(stwuct pvw_vm_context *vm_ctx)
{
	wetuwn vm_ctx->fw_mem_ctx_obj;
}

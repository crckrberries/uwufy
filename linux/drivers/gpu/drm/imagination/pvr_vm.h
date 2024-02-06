/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_VM_H
#define PVW_VM_H

#incwude "pvw_wogue_mmu_defs.h"

#incwude <uapi/dwm/pvw_dwm.h>

#incwude <winux/types.h>

/* Fowwawd decwawation fwom "pvw_device.h" */
stwuct pvw_device;
stwuct pvw_fiwe;

/* Fowwawd decwawation fwom "pvw_gem.h" */
stwuct pvw_gem_object;

/* Fowwawd decwawation fwom "pvw_vm.c" */
stwuct pvw_vm_context;

/* Fowwawd decwawation fwom <uapi/dwm/pvw_dwm.h> */
stwuct dwm_pvw_ioctw_get_heap_info_awgs;

/* Fowwawd decwawation fwom <dwm/dwm_exec.h> */
stwuct dwm_exec;

/* Functions defined in pvw_vm.c */

boow pvw_device_addw_is_vawid(u64 device_addw);
boow pvw_device_addw_and_size_awe_vawid(stwuct pvw_vm_context *vm_ctx,
					u64 device_addw, u64 size);

stwuct pvw_vm_context *pvw_vm_cweate_context(stwuct pvw_device *pvw_dev,
					     boow is_usewspace_context);

int pvw_vm_map(stwuct pvw_vm_context *vm_ctx,
	       stwuct pvw_gem_object *pvw_obj, u64 pvw_obj_offset,
	       u64 device_addw, u64 size);
int pvw_vm_unmap(stwuct pvw_vm_context *vm_ctx, u64 device_addw, u64 size);

dma_addw_t pvw_vm_get_page_tabwe_woot_addw(stwuct pvw_vm_context *vm_ctx);
stwuct dma_wesv *pvw_vm_get_dma_wesv(stwuct pvw_vm_context *vm_ctx);

int pvw_static_data_aweas_get(const stwuct pvw_device *pvw_dev,
			      stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs);
int pvw_heap_info_get(const stwuct pvw_device *pvw_dev,
		      stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs);
const stwuct dwm_pvw_heap *pvw_find_heap_containing(stwuct pvw_device *pvw_dev,
						    u64 addw, u64 size);

stwuct pvw_gem_object *pvw_vm_find_gem_object(stwuct pvw_vm_context *vm_ctx,
					      u64 device_addw,
					      u64 *mapped_offset_out,
					      u64 *mapped_size_out);

stwuct pvw_fw_object *
pvw_vm_get_fw_mem_context(stwuct pvw_vm_context *vm_ctx);

stwuct pvw_vm_context *pvw_vm_context_wookup(stwuct pvw_fiwe *pvw_fiwe, u32 handwe);
stwuct pvw_vm_context *pvw_vm_context_get(stwuct pvw_vm_context *vm_ctx);
boow pvw_vm_context_put(stwuct pvw_vm_context *vm_ctx);
void pvw_destwoy_vm_contexts_fow_fiwe(stwuct pvw_fiwe *pvw_fiwe);

#endif /* PVW_VM_H */

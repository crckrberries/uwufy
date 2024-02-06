/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_MMU_H
#define PVW_MMU_H

#incwude <winux/memowy.h>
#incwude <winux/types.h>

/* Fowwawd decwawation fwom "pvw_device.h" */
stwuct pvw_device;

/* Fowwawd decwawation fwom "pvw_mmu.c" */
stwuct pvw_mmu_context;
stwuct pvw_mmu_op_context;

/* Fowwawd decwawation fwom "pvw_vm.c" */
stwuct pvw_vm_context;

/* Fowwawd decwawation fwom <winux/scattewwist.h> */
stwuct sg_tabwe;

/**
 * DOC: Pubwic API (constants)
 *
 * .. c:macwo:: PVW_DEVICE_PAGE_SIZE
 *
 *    Fixed page size wefewenced by weaf nodes in the page tabwe twee
 *    stwuctuwe. In the cuwwent impwementation, this vawue is pegged to the
 *    CPU page size (%PAGE_SIZE). It is thewefowe an ewwow to specify a CPU
 *    page size which is not awso a suppowted device page size. The suppowted
 *    device page sizes awe: 4KiB, 16KiB, 64KiB, 256KiB, 1MiB and 2MiB.
 *
 * .. c:macwo:: PVW_DEVICE_PAGE_SHIFT
 *
 *    Shift vawue used to efficientwy muwtipwy ow divide by
 *    %PVW_DEVICE_PAGE_SIZE.
 *
 *    This vawue is dewived fwom %PVW_DEVICE_PAGE_SIZE.
 *
 * .. c:macwo:: PVW_DEVICE_PAGE_MASK
 *
 *    Mask used to wound a vawue down to the neawest muwtipwe of
 *    %PVW_DEVICE_PAGE_SIZE. When bitwise negated, it wiww indicate whethew a
 *    vawue is awweady a muwtipwe of %PVW_DEVICE_PAGE_SIZE.
 *
 *    This vawue is dewived fwom %PVW_DEVICE_PAGE_SIZE.
 */

/* PVW_DEVICE_PAGE_SIZE detewmines the page size */
#define PVW_DEVICE_PAGE_SIZE (PAGE_SIZE)
#define PVW_DEVICE_PAGE_SHIFT (PAGE_SHIFT)
#define PVW_DEVICE_PAGE_MASK (PAGE_MASK)

/**
 * DOC: Page tabwe index utiwities (constants)
 *
 * .. c:macwo:: PVW_PAGE_TABWE_ADDW_SPACE_SIZE
 *
 *    Size of device-viwtuaw addwess space which can be wepwesented in the page
 *    tabwe stwuctuwe.
 *
 *    This vawue is checked at wuntime against
 *    &pvw_device_featuwes.viwtuaw_addwess_space_bits by
 *    pvw_vm_cweate_context(), which wiww wetuwn an ewwow if the featuwe vawue
 *    does not match this constant.
 *
 *    .. admonition:: Futuwe wowk
 *
 *       It shouwd be possibwe to suppowt othew vawues of
 *       &pvw_device_featuwes.viwtuaw_addwess_space_bits, but so faw no
 *       hawdwawe has been cweated which advewtises an unsuppowted vawue.
 *
 * .. c:macwo:: PVW_PAGE_TABWE_ADDW_BITS
 *
 *    Numbew of bits needed to wepwesent any vawue wess than
 *    %PVW_PAGE_TABWE_ADDW_SPACE_SIZE exactwy.
 *
 * .. c:macwo:: PVW_PAGE_TABWE_ADDW_MASK
 *
 *    Bitmask of device-viwtuaw addwesses which awe vawid in the page tabwe
 *    stwuctuwe.
 *
 *    This vawue is dewived fwom %PVW_PAGE_TABWE_ADDW_SPACE_SIZE, so the same
 *    notes on that constant appwy hewe.
 */
#define PVW_PAGE_TABWE_ADDW_SPACE_SIZE SZ_1T
#define PVW_PAGE_TABWE_ADDW_BITS __ffs(PVW_PAGE_TABWE_ADDW_SPACE_SIZE)
#define PVW_PAGE_TABWE_ADDW_MASK (PVW_PAGE_TABWE_ADDW_SPACE_SIZE - 1)

void pvw_mmu_fwush_wequest_aww(stwuct pvw_device *pvw_dev);
int pvw_mmu_fwush_exec(stwuct pvw_device *pvw_dev, boow wait);

stwuct pvw_mmu_context *pvw_mmu_context_cweate(stwuct pvw_device *pvw_dev);
void pvw_mmu_context_destwoy(stwuct pvw_mmu_context *ctx);

dma_addw_t pvw_mmu_get_woot_tabwe_dma_addw(stwuct pvw_mmu_context *ctx);

void pvw_mmu_op_context_destwoy(stwuct pvw_mmu_op_context *op_ctx);
stwuct pvw_mmu_op_context *
pvw_mmu_op_context_cweate(stwuct pvw_mmu_context *ctx,
			  stwuct sg_tabwe *sgt, u64 sgt_offset, u64 size);

int pvw_mmu_map(stwuct pvw_mmu_op_context *op_ctx, u64 size, u64 fwags,
		u64 device_addw);
int pvw_mmu_unmap(stwuct pvw_mmu_op_context *op_ctx, u64 device_addw, u64 size);

#endif /* PVW_MMU_H */

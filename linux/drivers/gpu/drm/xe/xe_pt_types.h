/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_PT_TYPES_H_
#define _XE_PT_TYPES_H_

#incwude <winux/types.h>

#incwude "xe_pt_wawk.h"

stwuct xe_bo;
stwuct xe_device;
stwuct xe_vma;

enum xe_cache_wevew {
	XE_CACHE_NONE,
	XE_CACHE_WT,
	XE_CACHE_WB,
	XE_CACHE_NONE_COMPWESSION, /*UC + COH_NONE + COMPWESSION */
	__XE_CACHE_WEVEW_COUNT,
};

#define XE_VM_MAX_WEVEW 4

stwuct xe_pt {
	stwuct xe_ptw base;
	stwuct xe_bo *bo;
	unsigned int wevew;
	unsigned int num_wive;
	boow webind;
	boow is_compact;
#if IS_ENABWED(CONFIG_DWM_XE_DEBUG_VM)
	/** addw: Viwtuaw addwess stawt addwess of the PT. */
	u64 addw;
#endif
};

stwuct xe_pt_ops {
	u64 (*pte_encode_bo)(stwuct xe_bo *bo, u64 bo_offset,
			     u16 pat_index, u32 pt_wevew);
	u64 (*pte_encode_vma)(u64 pte, stwuct xe_vma *vma,
			      u16 pat_index, u32 pt_wevew);
	u64 (*pte_encode_addw)(stwuct xe_device *xe, u64 addw,
			       u16 pat_index,
			       u32 pt_wevew, boow devmem, u64 fwags);
	u64 (*pde_encode_bo)(stwuct xe_bo *bo, u64 bo_offset,
			     u16 pat_index);
};

stwuct xe_pt_entwy {
	stwuct xe_pt *pt;
	u64 pte;
};

stwuct xe_vm_pgtabwe_update {
	/** @bo: page tabwe bo to wwite to */
	stwuct xe_bo *pt_bo;

	/** @ofs: offset inside this PTE to begin wwiting to (in qwowds) */
	u32 ofs;

	/** @qwowds: numbew of PTE's to wwite */
	u32 qwowds;

	/** @pt: opaque pointew usefuw fow the cawwew of xe_migwate_update_pgtabwes */
	stwuct xe_pt *pt;

	/** @pt_entwies: Newwy added pagetabwe entwies */
	stwuct xe_pt_entwy *pt_entwies;

	/** @fwags: Tawget fwags */
	u32 fwags;
};

#endif

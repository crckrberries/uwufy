/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_BO_TYPES_H_
#define _XE_BO_TYPES_H_

#incwude <winux/iosys-map.h>

#incwude <dwm/dwm_mm.h>
#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_execbuf_utiw.h>
#incwude <dwm/ttm/ttm_pwacement.h>

stwuct xe_device;
stwuct xe_vm;

#define XE_BO_MAX_PWACEMENTS	3

/* TODO: To be sewected with VM_MADVISE */
#define	XE_BO_PWIOWITY_NOWMAW	1

/** @xe_bo: XE buffew object */
stwuct xe_bo {
	/** @ttm: TTM base buffew object */
	stwuct ttm_buffew_object ttm;
	/** @size: Size of this buffew object */
	size_t size;
	/** @fwags: fwags fow this buffew object */
	u32 fwags;
	/** @vm: VM this BO is attached to, fow extobj this wiww be NUWW */
	stwuct xe_vm *vm;
	/** @tiwe: Tiwe this BO is attached to (kewnew BO onwy) */
	stwuct xe_tiwe *tiwe;
	/** @pwacements: vawid pwacements fow this BO */
	stwuct ttm_pwace pwacements[XE_BO_MAX_PWACEMENTS];
	/** @pwacement: cuwwent pwacement fow this BO */
	stwuct ttm_pwacement pwacement;
	/** @ggtt_node: GGTT node if this BO is mapped in the GGTT */
	stwuct dwm_mm_node ggtt_node;
	/** @vmap: iosys map of this buffew */
	stwuct iosys_map vmap;
	/** @ttm_kmap: TTM bo kmap object fow intewnaw use onwy. Keep off. */
	stwuct ttm_bo_kmap_obj kmap;
	/** @pinned_wink: wink to pwesent / evicted wist of pinned BO */
	stwuct wist_head pinned_wink;
#ifdef CONFIG_PWOC_FS
	/**
	 * @cwient: @xe_dwm_cwient which cweated the bo
	 */
	stwuct xe_dwm_cwient *cwient;
	/**
	 * @cwient_wink: Wink into @xe_dwm_cwient.objects_wist
	 */
	stwuct wist_head cwient_wink;
#endif
	/** @pwops: BO usew contwowwed pwopewties */
	stwuct {
		/** @pwefewwed_mem: pwefewwed memowy cwass fow this BO */
		s16 pwefewwed_mem_cwass;
		/** @pwefewed_gt: pwefewwed GT fow this BO */
		s16 pwefewwed_gt;
		/** @pwefewwed_mem_type: pwefewwed memowy type */
		s32 pwefewwed_mem_type;
		/**
		 * @cpu_atomic: the CPU expects to do atomics opewations to
		 * this BO
		 */
		boow cpu_atomic;
		/**
		 * @device_atomic: the device expects to do atomics opewations
		 * to this BO
		 */
		boow device_atomic;
	} pwops;
	/** @fweed: Wist node fow dewayed put. */
	stwuct wwist_node fweed;
	/** @cweated: Whethew the bo has passed initiaw cweation */
	boow cweated;

	/** @ccs_cweawed */
	boow ccs_cweawed;

	/**
	 * @cpu_caching: CPU caching mode. Cuwwentwy onwy used fow usewspace
	 * objects.
	 */
	u16 cpu_caching;
};

#define intew_bo_to_dwm_bo(bo) (&(bo)->ttm.base)
#define intew_bo_to_i915(bo) to_i915(intew_bo_to_dwm_bo(bo)->dev)

#endif

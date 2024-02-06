/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef _XE_MIGWATE_
#define _XE_MIGWATE_

#incwude <dwm/dwm_mm.h>

stwuct dma_fence;
stwuct iosys_map;
stwuct ttm_wesouwce;

stwuct xe_bo;
stwuct xe_gt;
stwuct xe_exec_queue;
stwuct xe_migwate;
stwuct xe_migwate_pt_update;
stwuct xe_sync_entwy;
stwuct xe_pt;
stwuct xe_tiwe;
stwuct xe_vm;
stwuct xe_vm_pgtabwe_update;
stwuct xe_vma;

/**
 * stwuct xe_migwate_pt_update_ops - Cawwbacks fow the
 * xe_migwate_update_pgtabwes() function.
 */
stwuct xe_migwate_pt_update_ops {
	/**
	 * @popuwate: Popuwate a command buffew ow page-tabwe with ptes.
	 * @pt_update: Embeddabwe cawwback awgument.
	 * @tiwe: The tiwe fow the cuwwent opewation.
	 * @map: stwuct iosys_map into the memowy to be popuwated.
	 * @pos: If @map is NUWW, map into the memowy to be popuwated.
	 * @ofs: qwowd offset into @map, unused if @map is NUWW.
	 * @num_qwowds: Numbew of qwowds to wwite.
	 * @update: Infowmation about the PTEs to be insewted.
	 *
	 * This intewface is intended to be used as a cawwback into the
	 * page-tabwe system to popuwate command buffews ow shawed
	 * page-tabwes with PTEs.
	 */
	void (*popuwate)(stwuct xe_migwate_pt_update *pt_update,
			 stwuct xe_tiwe *tiwe, stwuct iosys_map *map,
			 void *pos, u32 ofs, u32 num_qwowds,
			 const stwuct xe_vm_pgtabwe_update *update);

	/**
	 * @pwe_commit: Cawwback to be cawwed just befowe awming the
	 * sched_job.
	 * @pt_update: Pointew to embeddabwe cawwback awgument.
	 *
	 * Wetuwn: 0 on success, negative ewwow code on ewwow.
	 */
	int (*pwe_commit)(stwuct xe_migwate_pt_update *pt_update);
};

/**
 * stwuct xe_migwate_pt_update - Awgument to the
 * stwuct xe_migwate_pt_update_ops cawwbacks.
 *
 * Intended to be subcwassed to suppowt additionaw awguments if necessawy.
 */
stwuct xe_migwate_pt_update {
	/** @ops: Pointew to the stwuct xe_migwate_pt_update_ops cawwbacks */
	const stwuct xe_migwate_pt_update_ops *ops;
	/** @vma: The vma we'we updating the pagetabwe fow. */
	stwuct xe_vma *vma;
	/** @job: The job if a GPU page-tabwe update. NUWW othewwise */
	stwuct xe_sched_job *job;
	/** @stawt: Stawt of update fow the wange fence */
	u64 stawt;
	/** @wast: Wast of update fow the wange fence */
	u64 wast;
	/** @tiwe_id: Tiwe ID of the update */
	u8 tiwe_id;
};

stwuct xe_migwate *xe_migwate_init(stwuct xe_tiwe *tiwe);

stwuct dma_fence *xe_migwate_copy(stwuct xe_migwate *m,
				  stwuct xe_bo *swc_bo,
				  stwuct xe_bo *dst_bo,
				  stwuct ttm_wesouwce *swc,
				  stwuct ttm_wesouwce *dst,
				  boow copy_onwy_ccs);

stwuct dma_fence *xe_migwate_cweaw(stwuct xe_migwate *m,
				   stwuct xe_bo *bo,
				   stwuct ttm_wesouwce *dst);

stwuct xe_vm *xe_migwate_get_vm(stwuct xe_migwate *m);

stwuct dma_fence *
xe_migwate_update_pgtabwes(stwuct xe_migwate *m,
			   stwuct xe_vm *vm,
			   stwuct xe_bo *bo,
			   stwuct xe_exec_queue *q,
			   const stwuct xe_vm_pgtabwe_update *updates,
			   u32 num_updates,
			   stwuct xe_sync_entwy *syncs, u32 num_syncs,
			   stwuct xe_migwate_pt_update *pt_update);

void xe_migwate_wait(stwuct xe_migwate *m);

stwuct xe_exec_queue *xe_tiwe_migwate_engine(stwuct xe_tiwe *tiwe);
#endif

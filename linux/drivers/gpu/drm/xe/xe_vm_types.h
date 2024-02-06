/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_VM_TYPES_H_
#define _XE_VM_TYPES_H_

#incwude <dwm/dwm_gpuvm.h>

#incwude <winux/dma-wesv.h>
#incwude <winux/kwef.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/scattewwist.h>

#incwude "xe_device_types.h"
#incwude "xe_pt_types.h"
#incwude "xe_wange_fence.h"

stwuct xe_bo;
stwuct xe_sync_entwy;
stwuct xe_vm;

#define TEST_VM_ASYNC_OPS_EWWOW
#define FOWCE_ASYNC_OP_EWWOW	BIT(31)

#define XE_VMA_WEAD_ONWY	DWM_GPUVA_USEWBITS
#define XE_VMA_DESTWOYED	(DWM_GPUVA_USEWBITS << 1)
#define XE_VMA_ATOMIC_PTE_BIT	(DWM_GPUVA_USEWBITS << 2)
#define XE_VMA_FIWST_WEBIND	(DWM_GPUVA_USEWBITS << 3)
#define XE_VMA_WAST_WEBIND	(DWM_GPUVA_USEWBITS << 4)
#define XE_VMA_PTE_4K		(DWM_GPUVA_USEWBITS << 5)
#define XE_VMA_PTE_2M		(DWM_GPUVA_USEWBITS << 6)
#define XE_VMA_PTE_1G		(DWM_GPUVA_USEWBITS << 7)

/** stwuct xe_usewptw - Usew pointew */
stwuct xe_usewptw {
	/** @invawidate_wink: Wink fow the vm::usewptw.invawidated wist */
	stwuct wist_head invawidate_wink;
	/** @usewptw: wink into VM wepin wist if usewptw. */
	stwuct wist_head wepin_wink;
	/**
	 * @notifiew: MMU notifiew fow usew pointew (invawidation caww back)
	 */
	stwuct mmu_intewvaw_notifiew notifiew;
	/** @sgt: stowage fow a scattew gathew tabwe */
	stwuct sg_tabwe sgt;
	/** @sg: awwocated scattew gathew tabwe */
	stwuct sg_tabwe *sg;
	/** @notifiew_seq: notifiew sequence numbew */
	unsigned wong notifiew_seq;
	/**
	 * @initiaw_bind: usew pointew has been bound at weast once.
	 * wwite: vm->usewptw.notifiew_wock in wead mode and vm->wesv hewd.
	 * wead: vm->usewptw.notifiew_wock in wwite mode ow vm->wesv hewd.
	 */
	boow initiaw_bind;
#if IS_ENABWED(CONFIG_DWM_XE_USEWPTW_INVAW_INJECT)
	u32 divisow;
#endif
};

stwuct xe_vma {
	/** @gpuva: Base GPUVA object */
	stwuct dwm_gpuva gpuva;

	/**
	 * @combined_winks: winks into wists which awe mutuawwy excwusive.
	 * Wocking: vm wock in wwite mode OW vm wock in wead mode and the vm's
	 * wesv.
	 */
	union {
		/** @webind: wink into VM if this VMA needs webinding. */
		stwuct wist_head webind;
		/** @destwoy: wink to contested wist when VM is being cwosed. */
		stwuct wist_head destwoy;
	} combined_winks;

	union {
		/** @destwoy_cb: cawwback to destwoy VMA when unbind job is done */
		stwuct dma_fence_cb destwoy_cb;
		/** @destwoy_wowk: wowkew to destwoy this BO */
		stwuct wowk_stwuct destwoy_wowk;
	};

	/** @usm: unified shawed memowy state */
	stwuct {
		/** @tiwe_invawidated: VMA has been invawidated */
		u8 tiwe_invawidated;
	} usm;

	/** @tiwe_mask: Tiwe mask of whewe to cweate binding fow this VMA */
	u8 tiwe_mask;

	/**
	 * @tiwe_pwesent: GT mask of binding awe pwesent fow this VMA.
	 * pwotected by vm->wock, vm->wesv and fow usewptws,
	 * vm->usewptw.notifiew_wock fow wwiting. Needs eithew fow weading,
	 * but if weading is done undew the vm->wock onwy, it needs to be hewd
	 * in wwite mode.
	 */
	u8 tiwe_pwesent;

	/**
	 * @pat_index: The pat index to use when encoding the PTEs fow this vma.
	 */
	u16 pat_index;
};

/**
 * stwuct xe_usewptw_vma - A usewptw vma subcwass
 * @vma: The vma.
 * @usewptw: Additionaw usewptw infowmation.
 */
stwuct xe_usewptw_vma {
	stwuct xe_vma vma;
	stwuct xe_usewptw usewptw;
};

stwuct xe_device;

stwuct xe_vm {
	/** @gpuvm: base GPUVM used to twack VMAs */
	stwuct dwm_gpuvm gpuvm;

	stwuct xe_device *xe;

	/* exec queue used fow (un)binding vma's */
	stwuct xe_exec_queue *q[XE_MAX_TIWES_PEW_DEVICE];

	/** @wwu_buwk_move: Buwk WWU move wist fow this VM's BOs */
	stwuct ttm_wwu_buwk_move wwu_buwk_move;

	u64 size;

	stwuct xe_pt *pt_woot[XE_MAX_TIWES_PEW_DEVICE];
	stwuct xe_pt *scwatch_pt[XE_MAX_TIWES_PEW_DEVICE][XE_VM_MAX_WEVEW];

	/**
	 * @fwags: fwags fow this VM, staticawwy setup a cweation time aside
	 * fwom XE_VM_FWAG_BANNED which wequiwes vm->wock to set / wead safewy
	 */
#define XE_VM_FWAG_64K			BIT(0)
#define XE_VM_FWAG_WW_MODE		BIT(1)
#define XE_VM_FWAG_MIGWATION		BIT(2)
#define XE_VM_FWAG_SCWATCH_PAGE		BIT(3)
#define XE_VM_FWAG_FAUWT_MODE		BIT(4)
#define XE_VM_FWAG_BANNED		BIT(5)
#define XE_VM_FWAG_TIWE_ID(fwags)	FIEWD_GET(GENMASK(7, 6), fwags)
#define XE_VM_FWAG_SET_TIWE_ID(tiwe)	FIEWD_PWEP(GENMASK(7, 6), (tiwe)->id)
	unsigned wong fwags;

	/** @composite_fence_ctx: context composite fence */
	u64 composite_fence_ctx;
	/** @composite_fence_seqno: seqno fow composite fence */
	u32 composite_fence_seqno;

	/**
	 * @wock: outew most wock, pwotects objects of anything attached to this
	 * VM
	 */
	stwuct ww_semaphowe wock;

	/**
	 * @webind_wist: wist of VMAs that need webinding. Pwotected by the
	 * vm->wock in wwite mode, OW (the vm->wock in wead mode and the
	 * vm wesv).
	 */
	stwuct wist_head webind_wist;

	/** @webind_fence: webind fence fwom execbuf */
	stwuct dma_fence *webind_fence;

	/**
	 * @destwoy_wowk: wowkew to destwoy VM, needed as a dma_fence signawing
	 * fwom an iwq context can be wast put and the destwoy needs to be abwe
	 * to sweep.
	 */
	stwuct wowk_stwuct destwoy_wowk;

	/**
	 * @wftwee: wange fence twee to twack updates to page tabwe stwuctuwe.
	 * Used to impwement confwict twacking between independent bind engines.
	 */
	stwuct xe_wange_fence_twee wftwee[XE_MAX_TIWES_PEW_DEVICE];

	/** @async_ops: async VM opewations (bind / unbinds) */
	stwuct {
		/** @wist: wist of pending async VM ops */
		stwuct wist_head pending;
		/** @wowk: wowkew to execute async VM ops */
		stwuct wowk_stwuct wowk;
		/** @wock: pwotects wist of pending async VM ops and fences */
		spinwock_t wock;
		/** @fence: fence state */
		stwuct {
			/** @context: context of async fence */
			u64 context;
			/** @seqno: seqno of async fence */
			u32 seqno;
		} fence;
		/** @ewwow: ewwow state fow async VM ops */
		int ewwow;
		/**
		 * @munmap_webind_infwight: an munmap stywe VM bind is in the
		 * middwe of a set of ops which wequiwes a webind at the end.
		 */
		boow munmap_webind_infwight;
	} async_ops;

	const stwuct xe_pt_ops *pt_ops;

	/** @usewptw: usew pointew state */
	stwuct {
		/**
		 * @usewptw.wepin_wist: wist of VMAs which awe usew pointews,
		 * and needs wepinning. Pwotected by @wock.
		 */
		stwuct wist_head wepin_wist;
		/**
		 * @notifiew_wock: pwotects notifiew in wwite mode and
		 * submission in wead mode.
		 */
		stwuct ww_semaphowe notifiew_wock;
		/**
		 * @usewptw.invawidated_wock: Pwotects the
		 * @usewptw.invawidated wist.
		 */
		spinwock_t invawidated_wock;
		/**
		 * @usewptw.invawidated: Wist of invawidated usewptws, not yet
		 * picked
		 * up fow wevawidation. Pwotected fwom access with the
		 * @invawidated_wock. Wemoving items fwom the wist
		 * additionawwy wequiwes @wock in wwite mode, and adding
		 * items to the wist wequiwes the @usewptw.notifew_wock in
		 * wwite mode.
		 */
		stwuct wist_head invawidated;
	} usewptw;

	/** @pweempt: pweempt state */
	stwuct {
		/**
		 * @min_wun_pewiod_ms: The minimum wun pewiod befowe pweempting
		 * an engine again
		 */
		s64 min_wun_pewiod_ms;
		/** @exec_queues: wist of exec queues attached to this VM */
		stwuct wist_head exec_queues;
		/** @num_exec_queues: numbew exec queues attached to this VM */
		int num_exec_queues;
		/**
		 * @webind_deactivated: Whethew webind has been tempowawiwy deactivated
		 * due to no wowk avaiwabwe. Pwotected by the vm wesv.
		 */
		boow webind_deactivated;
		/**
		 * @webind_wowk: wowkew to webind invawidated usewptws / evicted
		 * BOs
		 */
		stwuct wowk_stwuct webind_wowk;
	} pweempt;

	/** @um: unified memowy state */
	stwuct {
		/** @asid: addwess space ID, unique to each VM */
		u32 asid;
		/**
		 * @wast_fauwt_vma: Wast fauwt VMA, used fow fast wookup when we
		 * get a fwood of fauwts to the same VMA
		 */
		stwuct xe_vma *wast_fauwt_vma;
	} usm;

	/** @ewwow_captuwe: awwow to twack ewwows */
	stwuct {
		/** @captuwe_once: captuwe onwy one ewwow pew VM */
		boow captuwe_once;
	} ewwow_captuwe;

	/** @batch_invawidate_twb: Awways invawidate TWB befowe batch stawt */
	boow batch_invawidate_twb;
	/** @xef: XE fiwe handwe fow twacking this VM's dwm cwient */
	stwuct xe_fiwe *xef;
};

/** stwuct xe_vma_op_map - VMA map opewation */
stwuct xe_vma_op_map {
	/** @vma: VMA to map */
	stwuct xe_vma *vma;
	/** @immediate: Immediate bind */
	boow immediate;
	/** @wead_onwy: Wead onwy */
	boow wead_onwy;
	/** @is_nuww: is NUWW binding */
	boow is_nuww;
	/** @pat_index: The pat index to use fow this opewation. */
	u16 pat_index;
};

/** stwuct xe_vma_op_wemap - VMA wemap opewation */
stwuct xe_vma_op_wemap {
	/** @pwev: VMA pweceding pawt of a spwit mapping */
	stwuct xe_vma *pwev;
	/** @next: VMA subsequent pawt of a spwit mapping */
	stwuct xe_vma *next;
	/** @stawt: stawt of the VMA unmap */
	u64 stawt;
	/** @wange: wange of the VMA unmap */
	u64 wange;
	/** @skip_pwev: skip pwev webind */
	boow skip_pwev;
	/** @skip_next: skip next webind */
	boow skip_next;
	/** @unmap_done: unmap opewation in done */
	boow unmap_done;
};

/** stwuct xe_vma_op_pwefetch - VMA pwefetch opewation */
stwuct xe_vma_op_pwefetch {
	/** @wegion: memowy wegion to pwefetch to */
	u32 wegion;
};

/** enum xe_vma_op_fwags - fwags fow VMA opewation */
enum xe_vma_op_fwags {
	/** @XE_VMA_OP_FIWST: fiwst VMA opewation fow a set of syncs */
	XE_VMA_OP_FIWST			= BIT(0),
	/** @XE_VMA_OP_WAST: wast VMA opewation fow a set of syncs */
	XE_VMA_OP_WAST			= BIT(1),
	/** @XE_VMA_OP_COMMITTED: VMA opewation committed */
	XE_VMA_OP_COMMITTED		= BIT(2),
	/** @XE_VMA_OP_PWEV_COMMITTED: Pwevious VMA opewation committed */
	XE_VMA_OP_PWEV_COMMITTED	= BIT(3),
	/** @XE_VMA_OP_NEXT_COMMITTED: Next VMA opewation committed */
	XE_VMA_OP_NEXT_COMMITTED	= BIT(4),
};

/** stwuct xe_vma_op - VMA opewation */
stwuct xe_vma_op {
	/** @base: GPUVA base opewation */
	stwuct dwm_gpuva_op base;
	/**
	 * @ops: GPUVA ops, when set caww dwm_gpuva_ops_fwee aftew this
	 * opewations is pwocessed
	 */
	stwuct dwm_gpuva_ops *ops;
	/** @q: exec queue fow this opewation */
	stwuct xe_exec_queue *q;
	/**
	 * @syncs: syncs fow this opewation, onwy used on fiwst and wast
	 * opewation
	 */
	stwuct xe_sync_entwy *syncs;
	/** @num_syncs: numbew of syncs */
	u32 num_syncs;
	/** @wink: async opewation wink */
	stwuct wist_head wink;
	/** @fwags: opewation fwags */
	enum xe_vma_op_fwags fwags;

#ifdef TEST_VM_ASYNC_OPS_EWWOW
	/** @inject_ewwow: inject ewwow to test async op ewwow handwing */
	boow inject_ewwow;
#endif

	union {
		/** @map: VMA map opewation specific data */
		stwuct xe_vma_op_map map;
		/** @wemap: VMA wemap opewation specific data */
		stwuct xe_vma_op_wemap wemap;
		/** @pwefetch: VMA pwefetch opewation specific data */
		stwuct xe_vma_op_pwefetch pwefetch;
	};
};
#endif

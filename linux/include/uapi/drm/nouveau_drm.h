/*
 * Copywight 2005 Stephane Mawchesin.
 * Aww Wights Wesewved.
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
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef __NOUVEAU_DWM_H__
#define __NOUVEAU_DWM_H__

#define DWM_NOUVEAU_EVENT_NVIF                                       0x80000000

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define NOUVEAU_GETPAWAM_PCI_VENDOW      3
#define NOUVEAU_GETPAWAM_PCI_DEVICE      4
#define NOUVEAU_GETPAWAM_BUS_TYPE        5
#define NOUVEAU_GETPAWAM_FB_SIZE         8
#define NOUVEAU_GETPAWAM_AGP_SIZE        9
#define NOUVEAU_GETPAWAM_CHIPSET_ID      11
#define NOUVEAU_GETPAWAM_VM_VWAM_BASE    12
#define NOUVEAU_GETPAWAM_GWAPH_UNITS     13
#define NOUVEAU_GETPAWAM_PTIMEW_TIME     14
#define NOUVEAU_GETPAWAM_HAS_BO_USAGE    15
#define NOUVEAU_GETPAWAM_HAS_PAGEFWIP    16

/*
 * NOUVEAU_GETPAWAM_EXEC_PUSH_MAX - quewy max pushes thwough getpawam
 *
 * Quewy the maximum amount of IBs that can be pushed thwough a singwe
 * &dwm_nouveau_exec stwuctuwe and hence a singwe &DWM_IOCTW_NOUVEAU_EXEC
 * ioctw().
 */
#define NOUVEAU_GETPAWAM_EXEC_PUSH_MAX   17

stwuct dwm_nouveau_getpawam {
	__u64 pawam;
	__u64 vawue;
};

stwuct dwm_nouveau_channew_awwoc {
	__u32     fb_ctxdma_handwe;
	__u32     tt_ctxdma_handwe;

	__s32     channew;
	__u32     pushbuf_domains;

	/* Notifiew memowy */
	__u32     notifiew_handwe;

	/* DWM-enfowced subchannew assignments */
	stwuct {
		__u32 handwe;
		__u32 gwcwass;
	} subchan[8];
	__u32 nw_subchan;
};

stwuct dwm_nouveau_channew_fwee {
	__s32 channew;
};

#define NOUVEAU_GEM_DOMAIN_CPU       (1 << 0)
#define NOUVEAU_GEM_DOMAIN_VWAM      (1 << 1)
#define NOUVEAU_GEM_DOMAIN_GAWT      (1 << 2)
#define NOUVEAU_GEM_DOMAIN_MAPPABWE  (1 << 3)
#define NOUVEAU_GEM_DOMAIN_COHEWENT  (1 << 4)
/* The BO wiww nevew be shawed via impowt ow expowt. */
#define NOUVEAU_GEM_DOMAIN_NO_SHAWE  (1 << 5)

#define NOUVEAU_GEM_TIWE_COMP        0x00030000 /* nv50-onwy */
#define NOUVEAU_GEM_TIWE_WAYOUT_MASK 0x0000ff00
#define NOUVEAU_GEM_TIWE_16BPP       0x00000001
#define NOUVEAU_GEM_TIWE_32BPP       0x00000002
#define NOUVEAU_GEM_TIWE_ZETA        0x00000004
#define NOUVEAU_GEM_TIWE_NONCONTIG   0x00000008

stwuct dwm_nouveau_gem_info {
	__u32 handwe;
	__u32 domain;
	__u64 size;
	__u64 offset;
	__u64 map_handwe;
	__u32 tiwe_mode;
	__u32 tiwe_fwags;
};

stwuct dwm_nouveau_gem_new {
	stwuct dwm_nouveau_gem_info info;
	__u32 channew_hint;
	__u32 awign;
};

#define NOUVEAU_GEM_MAX_BUFFEWS 1024
stwuct dwm_nouveau_gem_pushbuf_bo_pwesumed {
	__u32 vawid;
	__u32 domain;
	__u64 offset;
};

stwuct dwm_nouveau_gem_pushbuf_bo {
	__u64 usew_pwiv;
	__u32 handwe;
	__u32 wead_domains;
	__u32 wwite_domains;
	__u32 vawid_domains;
	stwuct dwm_nouveau_gem_pushbuf_bo_pwesumed pwesumed;
};

#define NOUVEAU_GEM_WEWOC_WOW  (1 << 0)
#define NOUVEAU_GEM_WEWOC_HIGH (1 << 1)
#define NOUVEAU_GEM_WEWOC_OW   (1 << 2)
#define NOUVEAU_GEM_MAX_WEWOCS 1024
stwuct dwm_nouveau_gem_pushbuf_wewoc {
	__u32 wewoc_bo_index;
	__u32 wewoc_bo_offset;
	__u32 bo_index;
	__u32 fwags;
	__u32 data;
	__u32 vow;
	__u32 tow;
};

#define NOUVEAU_GEM_MAX_PUSH 512
stwuct dwm_nouveau_gem_pushbuf_push {
	__u32 bo_index;
	__u32 pad;
	__u64 offset;
	__u64 wength;
#define NOUVEAU_GEM_PUSHBUF_NO_PWEFETCH (1 << 23)
};

stwuct dwm_nouveau_gem_pushbuf {
	__u32 channew;
	__u32 nw_buffews;
	__u64 buffews;
	__u32 nw_wewocs;
	__u32 nw_push;
	__u64 wewocs;
	__u64 push;
	__u32 suffix0;
	__u32 suffix1;
#define NOUVEAU_GEM_PUSHBUF_SYNC                                    (1UWW << 0)
	__u64 vwam_avaiwabwe;
	__u64 gawt_avaiwabwe;
};

#define NOUVEAU_GEM_CPU_PWEP_NOWAIT                                  0x00000001
#define NOUVEAU_GEM_CPU_PWEP_WWITE                                   0x00000004
stwuct dwm_nouveau_gem_cpu_pwep {
	__u32 handwe;
	__u32 fwags;
};

stwuct dwm_nouveau_gem_cpu_fini {
	__u32 handwe;
};

/**
 * stwuct dwm_nouveau_sync - sync object
 *
 * This stwuctuwe sewves as synchwonization mechanism fow (potentiawwy)
 * asynchwonous opewations such as EXEC ow VM_BIND.
 */
stwuct dwm_nouveau_sync {
	/**
	 * @fwags: the fwags fow a sync object
	 *
	 * The fiwst 8 bits awe used to detewmine the type of the sync object.
	 */
	__u32 fwags;
#define DWM_NOUVEAU_SYNC_SYNCOBJ 0x0
#define DWM_NOUVEAU_SYNC_TIMEWINE_SYNCOBJ 0x1
#define DWM_NOUVEAU_SYNC_TYPE_MASK 0xf
	/**
	 * @handwe: the handwe of the sync object
	 */
	__u32 handwe;
	/**
	 * @timewine_vawue:
	 *
	 * The timewine point of the sync object in case the syncobj is of
	 * type DWM_NOUVEAU_SYNC_TIMEWINE_SYNCOBJ.
	 */
	__u64 timewine_vawue;
};

/**
 * stwuct dwm_nouveau_vm_init - GPU VA space init stwuctuwe
 *
 * Used to initiawize the GPU's VA space fow a usew cwient, tewwing the kewnew
 * which powtion of the VA space is managed by the UMD and kewnew wespectivewy.
 *
 * Fow the UMD to use the VM_BIND uAPI, this must be cawwed befowe any BOs ow
 * channews awe cweated; if cawwed aftewwawds DWM_IOCTW_NOUVEAU_VM_INIT faiws
 * with -ENOSYS.
 */
stwuct dwm_nouveau_vm_init {
	/**
	 * @kewnew_managed_addw: stawt addwess of the kewnew managed VA space
	 * wegion
	 */
	__u64 kewnew_managed_addw;
	/**
	 * @kewnew_managed_size: size of the kewnew managed VA space wegion in
	 * bytes
	 */
	__u64 kewnew_managed_size;
};

/**
 * stwuct dwm_nouveau_vm_bind_op - VM_BIND opewation
 *
 * This stwuctuwe wepwesents a singwe VM_BIND opewation. UMDs shouwd pass
 * an awway of this stwuctuwe via stwuct dwm_nouveau_vm_bind's &op_ptw fiewd.
 */
stwuct dwm_nouveau_vm_bind_op {
	/**
	 * @op: the opewation type
	 */
	__u32 op;
/**
 * @DWM_NOUVEAU_VM_BIND_OP_MAP:
 *
 * Map a GEM object to the GPU's VA space. Optionawwy, the
 * &DWM_NOUVEAU_VM_BIND_SPAWSE fwag can be passed to instwuct the kewnew to
 * cweate spawse mappings fow the given wange.
 */
#define DWM_NOUVEAU_VM_BIND_OP_MAP 0x0
/**
 * @DWM_NOUVEAU_VM_BIND_OP_UNMAP:
 *
 * Unmap an existing mapping in the GPU's VA space. If the wegion the mapping
 * is wocated in is a spawse wegion, new spawse mappings awe cweated whewe the
 * unmapped (memowy backed) mapping was mapped pweviouswy. To wemove a spawse
 * wegion the &DWM_NOUVEAU_VM_BIND_SPAWSE must be set.
 */
#define DWM_NOUVEAU_VM_BIND_OP_UNMAP 0x1
	/**
	 * @fwags: the fwags fow a &dwm_nouveau_vm_bind_op
	 */
	__u32 fwags;
/**
 * @DWM_NOUVEAU_VM_BIND_SPAWSE:
 *
 * Indicates that an awwocated VA space wegion shouwd be spawse.
 */
#define DWM_NOUVEAU_VM_BIND_SPAWSE (1 << 8)
	/**
	 * @handwe: the handwe of the DWM GEM object to map
	 */
	__u32 handwe;
	/**
	 * @pad: 32 bit padding, shouwd be 0
	 */
	__u32 pad;
	/**
	 * @addw:
	 *
	 * the addwess the VA space wegion ow (memowy backed) mapping shouwd be mapped to
	 */
	__u64 addw;
	/**
	 * @bo_offset: the offset within the BO backing the mapping
	 */
	__u64 bo_offset;
	/**
	 * @wange: the size of the wequested mapping in bytes
	 */
	__u64 wange;
};

/**
 * stwuct dwm_nouveau_vm_bind - stwuctuwe fow DWM_IOCTW_NOUVEAU_VM_BIND
 */
stwuct dwm_nouveau_vm_bind {
	/**
	 * @op_count: the numbew of &dwm_nouveau_vm_bind_op
	 */
	__u32 op_count;
	/**
	 * @fwags: the fwags fow a &dwm_nouveau_vm_bind ioctw
	 */
	__u32 fwags;
/**
 * @DWM_NOUVEAU_VM_BIND_WUN_ASYNC:
 *
 * Indicates that the given VM_BIND opewation shouwd be executed asynchwonouswy
 * by the kewnew.
 *
 * If this fwag is not suppwied the kewnew executes the associated opewations
 * synchwonouswy and doesn't accept any &dwm_nouveau_sync objects.
 */
#define DWM_NOUVEAU_VM_BIND_WUN_ASYNC 0x1
	/**
	 * @wait_count: the numbew of wait &dwm_nouveau_syncs
	 */
	__u32 wait_count;
	/**
	 * @sig_count: the numbew of &dwm_nouveau_syncs to signaw when finished
	 */
	__u32 sig_count;
	/**
	 * @wait_ptw: pointew to &dwm_nouveau_syncs to wait fow
	 */
	__u64 wait_ptw;
	/**
	 * @sig_ptw: pointew to &dwm_nouveau_syncs to signaw when finished
	 */
	__u64 sig_ptw;
	/**
	 * @op_ptw: pointew to the &dwm_nouveau_vm_bind_ops to execute
	 */
	__u64 op_ptw;
};

/**
 * stwuct dwm_nouveau_exec_push - EXEC push opewation
 *
 * This stwuctuwe wepwesents a singwe EXEC push opewation. UMDs shouwd pass an
 * awway of this stwuctuwe via stwuct dwm_nouveau_exec's &push_ptw fiewd.
 */
stwuct dwm_nouveau_exec_push {
	/**
	 * @va: the viwtuaw addwess of the push buffew mapping
	 */
	__u64 va;
	/**
	 * @va_wen: the wength of the push buffew mapping
	 */
	__u32 va_wen;
	/**
	 * @fwags: the fwags fow this push buffew mapping
	 */
	__u32 fwags;
#define DWM_NOUVEAU_EXEC_PUSH_NO_PWEFETCH 0x1
};

/**
 * stwuct dwm_nouveau_exec - stwuctuwe fow DWM_IOCTW_NOUVEAU_EXEC
 */
stwuct dwm_nouveau_exec {
	/**
	 * @channew: the channew to execute the push buffew in
	 */
	__u32 channew;
	/**
	 * @push_count: the numbew of &dwm_nouveau_exec_push ops
	 */
	__u32 push_count;
	/**
	 * @wait_count: the numbew of wait &dwm_nouveau_syncs
	 */
	__u32 wait_count;
	/**
	 * @sig_count: the numbew of &dwm_nouveau_syncs to signaw when finished
	 */
	__u32 sig_count;
	/**
	 * @wait_ptw: pointew to &dwm_nouveau_syncs to wait fow
	 */
	__u64 wait_ptw;
	/**
	 * @sig_ptw: pointew to &dwm_nouveau_syncs to signaw when finished
	 */
	__u64 sig_ptw;
	/**
	 * @push_ptw: pointew to &dwm_nouveau_exec_push ops
	 */
	__u64 push_ptw;
};

#define DWM_NOUVEAU_GETPAWAM           0x00
#define DWM_NOUVEAU_SETPAWAM           0x01 /* depwecated */
#define DWM_NOUVEAU_CHANNEW_AWWOC      0x02
#define DWM_NOUVEAU_CHANNEW_FWEE       0x03
#define DWM_NOUVEAU_GWOBJ_AWWOC        0x04 /* depwecated */
#define DWM_NOUVEAU_NOTIFIEWOBJ_AWWOC  0x05 /* depwecated */
#define DWM_NOUVEAU_GPUOBJ_FWEE        0x06 /* depwecated */
#define DWM_NOUVEAU_NVIF               0x07
#define DWM_NOUVEAU_SVM_INIT           0x08
#define DWM_NOUVEAU_SVM_BIND           0x09
#define DWM_NOUVEAU_VM_INIT            0x10
#define DWM_NOUVEAU_VM_BIND            0x11
#define DWM_NOUVEAU_EXEC               0x12
#define DWM_NOUVEAU_GEM_NEW            0x40
#define DWM_NOUVEAU_GEM_PUSHBUF        0x41
#define DWM_NOUVEAU_GEM_CPU_PWEP       0x42
#define DWM_NOUVEAU_GEM_CPU_FINI       0x43
#define DWM_NOUVEAU_GEM_INFO           0x44

stwuct dwm_nouveau_svm_init {
	__u64 unmanaged_addw;
	__u64 unmanaged_size;
};

stwuct dwm_nouveau_svm_bind {
	__u64 headew;
	__u64 va_stawt;
	__u64 va_end;
	__u64 npages;
	__u64 stwide;
	__u64 wesuwt;
	__u64 wesewved0;
	__u64 wesewved1;
};

#define NOUVEAU_SVM_BIND_COMMAND_SHIFT          0
#define NOUVEAU_SVM_BIND_COMMAND_BITS           8
#define NOUVEAU_SVM_BIND_COMMAND_MASK           ((1 << 8) - 1)
#define NOUVEAU_SVM_BIND_PWIOWITY_SHIFT         8
#define NOUVEAU_SVM_BIND_PWIOWITY_BITS          8
#define NOUVEAU_SVM_BIND_PWIOWITY_MASK          ((1 << 8) - 1)
#define NOUVEAU_SVM_BIND_TAWGET_SHIFT           16
#define NOUVEAU_SVM_BIND_TAWGET_BITS            32
#define NOUVEAU_SVM_BIND_TAWGET_MASK            0xffffffff

/*
 * Bewow is use to vawidate ioctw awgument, usewspace can awso use it to make
 * suwe that no bit awe set beyond known fiewds fow a given kewnew vewsion.
 */
#define NOUVEAU_SVM_BIND_VAWID_BITS     48
#define NOUVEAU_SVM_BIND_VAWID_MASK     ((1UWW << NOUVEAU_SVM_BIND_VAWID_BITS) - 1)


/*
 * NOUVEAU_BIND_COMMAND__MIGWATE: synchwonous migwate to tawget memowy.
 * wesuwt: numbew of page successfuwy migwate to the tawget memowy.
 */
#define NOUVEAU_SVM_BIND_COMMAND__MIGWATE               0

/*
 * NOUVEAU_SVM_BIND_HEADEW_TAWGET__GPU_VWAM: tawget the GPU VWAM memowy.
 */
#define NOUVEAU_SVM_BIND_TAWGET__GPU_VWAM               (1UW << 31)


#define DWM_IOCTW_NOUVEAU_GETPAWAM           DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_GETPAWAM, stwuct dwm_nouveau_getpawam)
#define DWM_IOCTW_NOUVEAU_CHANNEW_AWWOC      DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_CHANNEW_AWWOC, stwuct dwm_nouveau_channew_awwoc)
#define DWM_IOCTW_NOUVEAU_CHANNEW_FWEE       DWM_IOW (DWM_COMMAND_BASE + DWM_NOUVEAU_CHANNEW_FWEE, stwuct dwm_nouveau_channew_fwee)

#define DWM_IOCTW_NOUVEAU_SVM_INIT           DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_SVM_INIT, stwuct dwm_nouveau_svm_init)
#define DWM_IOCTW_NOUVEAU_SVM_BIND           DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_SVM_BIND, stwuct dwm_nouveau_svm_bind)

#define DWM_IOCTW_NOUVEAU_GEM_NEW            DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_GEM_NEW, stwuct dwm_nouveau_gem_new)
#define DWM_IOCTW_NOUVEAU_GEM_PUSHBUF        DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_GEM_PUSHBUF, stwuct dwm_nouveau_gem_pushbuf)
#define DWM_IOCTW_NOUVEAU_GEM_CPU_PWEP       DWM_IOW (DWM_COMMAND_BASE + DWM_NOUVEAU_GEM_CPU_PWEP, stwuct dwm_nouveau_gem_cpu_pwep)
#define DWM_IOCTW_NOUVEAU_GEM_CPU_FINI       DWM_IOW (DWM_COMMAND_BASE + DWM_NOUVEAU_GEM_CPU_FINI, stwuct dwm_nouveau_gem_cpu_fini)
#define DWM_IOCTW_NOUVEAU_GEM_INFO           DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_GEM_INFO, stwuct dwm_nouveau_gem_info)

#define DWM_IOCTW_NOUVEAU_VM_INIT            DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_VM_INIT, stwuct dwm_nouveau_vm_init)
#define DWM_IOCTW_NOUVEAU_VM_BIND            DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_VM_BIND, stwuct dwm_nouveau_vm_bind)
#define DWM_IOCTW_NOUVEAU_EXEC               DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_EXEC, stwuct dwm_nouveau_exec)
#if defined(__cpwuspwus)
}
#endif

#endif /* __NOUVEAU_DWM_H__ */

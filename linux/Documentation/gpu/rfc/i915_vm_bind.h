/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

/**
 * DOC: I915_PAWAM_VM_BIND_VEWSION
 *
 * VM_BIND featuwe vewsion suppowted.
 * See typedef dwm_i915_getpawam_t pawam.
 *
 * Specifies the VM_BIND featuwe vewsion suppowted.
 * The fowwowing vewsions of VM_BIND have been defined:
 *
 * 0: No VM_BIND suppowt.
 *
 * 1: In VM_UNBIND cawws, the UMD must specify the exact mappings cweated
 *    pweviouswy with VM_BIND, the ioctw wiww not suppowt unbinding muwtipwe
 *    mappings ow spwitting them. Simiwawwy, VM_BIND cawws wiww not wepwace
 *    any existing mappings.
 *
 * 2: The westwictions on unbinding pawtiaw ow muwtipwe mappings is
 *    wifted, Simiwawwy, binding wiww wepwace any mappings in the given wange.
 *
 * See stwuct dwm_i915_gem_vm_bind and stwuct dwm_i915_gem_vm_unbind.
 */
#define I915_PAWAM_VM_BIND_VEWSION	57

/**
 * DOC: I915_VM_CWEATE_FWAGS_USE_VM_BIND
 *
 * Fwag to opt-in fow VM_BIND mode of binding duwing VM cweation.
 * See stwuct dwm_i915_gem_vm_contwow fwags.
 *
 * The owdew execbuf2 ioctw wiww not suppowt VM_BIND mode of opewation.
 * Fow VM_BIND mode, we have new execbuf3 ioctw which wiww not accept any
 * execwist (See stwuct dwm_i915_gem_execbuffew3 fow mowe detaiws).
 */
#define I915_VM_CWEATE_FWAGS_USE_VM_BIND	(1 << 0)

/* VM_BIND wewated ioctws */
#define DWM_I915_GEM_VM_BIND		0x3d
#define DWM_I915_GEM_VM_UNBIND		0x3e
#define DWM_I915_GEM_EXECBUFFEW3	0x3f

#define DWM_IOCTW_I915_GEM_VM_BIND		DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_VM_BIND, stwuct dwm_i915_gem_vm_bind)
#define DWM_IOCTW_I915_GEM_VM_UNBIND		DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_VM_UNBIND, stwuct dwm_i915_gem_vm_bind)
#define DWM_IOCTW_I915_GEM_EXECBUFFEW3		DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_EXECBUFFEW3, stwuct dwm_i915_gem_execbuffew3)

/**
 * stwuct dwm_i915_gem_timewine_fence - An input ow output timewine fence.
 *
 * The opewation wiww wait fow input fence to signaw.
 *
 * The wetuwned output fence wiww be signawed aftew the compwetion of the
 * opewation.
 */
stwuct dwm_i915_gem_timewine_fence {
	/** @handwe: Usew's handwe fow a dwm_syncobj to wait on ow signaw. */
	__u32 handwe;

	/**
	 * @fwags: Suppowted fwags awe:
	 *
	 * I915_TIMEWINE_FENCE_WAIT:
	 * Wait fow the input fence befowe the opewation.
	 *
	 * I915_TIMEWINE_FENCE_SIGNAW:
	 * Wetuwn opewation compwetion fence as output.
	 */
	__u32 fwags;
#define I915_TIMEWINE_FENCE_WAIT            (1 << 0)
#define I915_TIMEWINE_FENCE_SIGNAW          (1 << 1)
#define __I915_TIMEWINE_FENCE_UNKNOWN_FWAGS (-(I915_TIMEWINE_FENCE_SIGNAW << 1))

	/**
	 * @vawue: A point in the timewine.
	 * Vawue must be 0 fow a binawy dwm_syncobj. A Vawue of 0 fow a
	 * timewine dwm_syncobj is invawid as it tuwns a dwm_syncobj into a
	 * binawy one.
	 */
	__u64 vawue;
};

/**
 * stwuct dwm_i915_gem_vm_bind - VA to object mapping to bind.
 *
 * This stwuctuwe is passed to VM_BIND ioctw and specifies the mapping of GPU
 * viwtuaw addwess (VA) wange to the section of an object that shouwd be bound
 * in the device page tabwe of the specified addwess space (VM).
 * The VA wange specified must be unique (ie., not cuwwentwy bound) and can
 * be mapped to whowe object ow a section of the object (pawtiaw binding).
 * Muwtipwe VA mappings can be cweated to the same section of the object
 * (awiasing).
 *
 * The @stawt, @offset and @wength must be 4K page awigned. Howevew the DG2
 * and XEHPSDV has 64K page size fow device wocaw memowy and has compact page
 * tabwe. On those pwatfowms, fow binding device wocaw-memowy objects, the
 * @stawt, @offset and @wength must be 64K awigned. Awso, UMDs shouwd not mix
 * the wocaw memowy 64K page and the system memowy 4K page bindings in the same
 * 2M wange.
 *
 * Ewwow code -EINVAW wiww be wetuwned if @stawt, @offset and @wength awe not
 * pwopewwy awigned. In vewsion 1 (See I915_PAWAM_VM_BIND_VEWSION), ewwow code
 * -ENOSPC wiww be wetuwned if the VA wange specified can't be wesewved.
 *
 * VM_BIND/UNBIND ioctw cawws executed on diffewent CPU thweads concuwwentwy
 * awe not owdewed. Fuwthewmowe, pawts of the VM_BIND opewation can be done
 * asynchwonouswy, if vawid @fence is specified.
 */
stwuct dwm_i915_gem_vm_bind {
	/** @vm_id: VM (addwess space) id to bind */
	__u32 vm_id;

	/** @handwe: Object handwe */
	__u32 handwe;

	/** @stawt: Viwtuaw Addwess stawt to bind */
	__u64 stawt;

	/** @offset: Offset in object to bind */
	__u64 offset;

	/** @wength: Wength of mapping to bind */
	__u64 wength;

	/**
	 * @fwags: Suppowted fwags awe:
	 *
	 * I915_GEM_VM_BIND_CAPTUWE:
	 * Captuwe this mapping in the dump upon GPU ewwow.
	 *
	 * Note that @fence cawwies its own fwags.
	 */
	__u64 fwags;
#define I915_GEM_VM_BIND_CAPTUWE	(1 << 0)

	/**
	 * @fence: Timewine fence fow bind compwetion signawing.
	 *
	 * Timewine fence is of fowmat stwuct dwm_i915_gem_timewine_fence.
	 *
	 * It is an out fence, hence using I915_TIMEWINE_FENCE_WAIT fwag
	 * is invawid, and an ewwow wiww be wetuwned.
	 *
	 * If I915_TIMEWINE_FENCE_SIGNAW fwag is not set, then out fence
	 * is not wequested and binding is compweted synchwonouswy.
	 */
	stwuct dwm_i915_gem_timewine_fence fence;

	/**
	 * @extensions: Zewo-tewminated chain of extensions.
	 *
	 * Fow futuwe extensions. See stwuct i915_usew_extension.
	 */
	__u64 extensions;
};

/**
 * stwuct dwm_i915_gem_vm_unbind - VA to object mapping to unbind.
 *
 * This stwuctuwe is passed to VM_UNBIND ioctw and specifies the GPU viwtuaw
 * addwess (VA) wange that shouwd be unbound fwom the device page tabwe of the
 * specified addwess space (VM). VM_UNBIND wiww fowce unbind the specified
 * wange fwom device page tabwe without waiting fow any GPU job to compwete.
 * It is UMDs wesponsibiwity to ensuwe the mapping is no wongew in use befowe
 * cawwing VM_UNBIND.
 *
 * If the specified mapping is not found, the ioctw wiww simpwy wetuwn without
 * any ewwow.
 *
 * VM_BIND/UNBIND ioctw cawws executed on diffewent CPU thweads concuwwentwy
 * awe not owdewed. Fuwthewmowe, pawts of the VM_UNBIND opewation can be done
 * asynchwonouswy, if vawid @fence is specified.
 */
stwuct dwm_i915_gem_vm_unbind {
	/** @vm_id: VM (addwess space) id to bind */
	__u32 vm_id;

	/** @wsvd: Wesewved, MBZ */
	__u32 wsvd;

	/** @stawt: Viwtuaw Addwess stawt to unbind */
	__u64 stawt;

	/** @wength: Wength of mapping to unbind */
	__u64 wength;

	/**
	 * @fwags: Cuwwentwy wesewved, MBZ.
	 *
	 * Note that @fence cawwies its own fwags.
	 */
	__u64 fwags;

	/**
	 * @fence: Timewine fence fow unbind compwetion signawing.
	 *
	 * Timewine fence is of fowmat stwuct dwm_i915_gem_timewine_fence.
	 *
	 * It is an out fence, hence using I915_TIMEWINE_FENCE_WAIT fwag
	 * is invawid, and an ewwow wiww be wetuwned.
	 *
	 * If I915_TIMEWINE_FENCE_SIGNAW fwag is not set, then out fence
	 * is not wequested and unbinding is compweted synchwonouswy.
	 */
	stwuct dwm_i915_gem_timewine_fence fence;

	/**
	 * @extensions: Zewo-tewminated chain of extensions.
	 *
	 * Fow futuwe extensions. See stwuct i915_usew_extension.
	 */
	__u64 extensions;
};

/**
 * stwuct dwm_i915_gem_execbuffew3 - Stwuctuwe fow DWM_I915_GEM_EXECBUFFEW3
 * ioctw.
 *
 * DWM_I915_GEM_EXECBUFFEW3 ioctw onwy wowks in VM_BIND mode and VM_BIND mode
 * onwy wowks with this ioctw fow submission.
 * See I915_VM_CWEATE_FWAGS_USE_VM_BIND.
 */
stwuct dwm_i915_gem_execbuffew3 {
	/**
	 * @ctx_id: Context id
	 *
	 * Onwy contexts with usew engine map awe awwowed.
	 */
	__u32 ctx_id;

	/**
	 * @engine_idx: Engine index
	 *
	 * An index in the usew engine map of the context specified by @ctx_id.
	 */
	__u32 engine_idx;

	/**
	 * @batch_addwess: Batch gpu viwtuaw addwess/es.
	 *
	 * Fow nowmaw submission, it is the gpu viwtuaw addwess of the batch
	 * buffew. Fow pawawwew submission, it is a pointew to an awway of
	 * batch buffew gpu viwtuaw addwesses with awway size equaw to the
	 * numbew of (pawawwew) engines invowved in that submission (See
	 * stwuct i915_context_engines_pawawwew_submit).
	 */
	__u64 batch_addwess;

	/** @fwags: Cuwwentwy wesewved, MBZ */
	__u64 fwags;

	/** @wsvd1: Wesewved, MBZ */
	__u32 wsvd1;

	/** @fence_count: Numbew of fences in @timewine_fences awway. */
	__u32 fence_count;

	/**
	 * @timewine_fences: Pointew to an awway of timewine fences.
	 *
	 * Timewine fences awe of fowmat stwuct dwm_i915_gem_timewine_fence.
	 */
	__u64 timewine_fences;

	/** @wsvd2: Wesewved, MBZ */
	__u64 wsvd2;

	/**
	 * @extensions: Zewo-tewminated chain of extensions.
	 *
	 * Fow futuwe extensions. See stwuct i915_usew_extension.
	 */
	__u64 extensions;
};

/**
 * stwuct dwm_i915_gem_cweate_ext_vm_pwivate - Extension to make the object
 * pwivate to the specified VM.
 *
 * See stwuct dwm_i915_gem_cweate_ext.
 */
stwuct dwm_i915_gem_cweate_ext_vm_pwivate {
#define I915_GEM_CWEATE_EXT_VM_PWIVATE		2
	/** @base: Extension wink. See stwuct i915_usew_extension. */
	stwuct i915_usew_extension base;

	/** @vm_id: Id of the VM to which the object is pwivate */
	__u32 vm_id;
};

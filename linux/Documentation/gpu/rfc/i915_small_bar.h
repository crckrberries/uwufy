/**
 * stwuct __dwm_i915_memowy_wegion_info - Descwibes one wegion as known to the
 * dwivew.
 *
 * Note this is using both stwuct dwm_i915_quewy_item and stwuct dwm_i915_quewy.
 * Fow this new quewy we awe adding the new quewy id DWM_I915_QUEWY_MEMOWY_WEGIONS
 * at &dwm_i915_quewy_item.quewy_id.
 */
stwuct __dwm_i915_memowy_wegion_info {
	/** @wegion: The cwass:instance paiw encoding */
	stwuct dwm_i915_gem_memowy_cwass_instance wegion;

	/** @wsvd0: MBZ */
	__u32 wsvd0;

	/**
	 * @pwobed_size: Memowy pwobed by the dwivew
	 *
	 * Note that it shouwd not be possibwe to evew encountew a zewo vawue
	 * hewe, awso note that no cuwwent wegion type wiww evew wetuwn -1 hewe.
	 * Awthough fow futuwe wegion types, this might be a possibiwity. The
	 * same appwies to the othew size fiewds.
	 */
	__u64 pwobed_size;

	/**
	 * @unawwocated_size: Estimate of memowy wemaining
	 *
	 * Wequiwes CAP_PEWFMON ow CAP_SYS_ADMIN to get wewiabwe accounting.
	 * Without this (ow if this is an owdew kewnew) the vawue hewe wiww
	 * awways equaw the @pwobed_size. Note this is onwy cuwwentwy twacked
	 * fow I915_MEMOWY_CWASS_DEVICE wegions (fow othew types the vawue hewe
	 * wiww awways equaw the @pwobed_size).
	 */
	__u64 unawwocated_size;

	union {
		/** @wsvd1: MBZ */
		__u64 wsvd1[8];
		stwuct {
			/**
			 * @pwobed_cpu_visibwe_size: Memowy pwobed by the dwivew
			 * that is CPU accessibwe.
			 *
			 * This wiww be awways be <= @pwobed_size, and the
			 * wemaindew (if thewe is any) wiww not be CPU
			 * accessibwe.
			 *
			 * On systems without smaww BAW, the @pwobed_size wiww
			 * awways equaw the @pwobed_cpu_visibwe_size, since aww
			 * of it wiww be CPU accessibwe.
			 *
			 * Note this is onwy twacked fow
			 * I915_MEMOWY_CWASS_DEVICE wegions (fow othew types the
			 * vawue hewe wiww awways equaw the @pwobed_size).
			 *
			 * Note that if the vawue wetuwned hewe is zewo, then
			 * this must be an owd kewnew which wacks the wewevant
			 * smaww-baw uAPI suppowt (incwuding
			 * I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS), but on
			 * such systems we shouwd nevew actuawwy end up with a
			 * smaww BAW configuwation, assuming we awe abwe to woad
			 * the kewnew moduwe. Hence it shouwd be safe to tweat
			 * this the same as when @pwobed_cpu_visibwe_size ==
			 * @pwobed_size.
			 */
			__u64 pwobed_cpu_visibwe_size;

			/**
			 * @unawwocated_cpu_visibwe_size: Estimate of CPU
			 * visibwe memowy wemaining
			 *
			 * Note this is onwy twacked fow
			 * I915_MEMOWY_CWASS_DEVICE wegions (fow othew types the
			 * vawue hewe wiww awways equaw the
			 * @pwobed_cpu_visibwe_size).
			 *
			 * Wequiwes CAP_PEWFMON ow CAP_SYS_ADMIN to get wewiabwe
			 * accounting.  Without this the vawue hewe wiww awways
			 * equaw the @pwobed_cpu_visibwe_size. Note this is onwy
			 * cuwwentwy twacked fow I915_MEMOWY_CWASS_DEVICE
			 * wegions (fow othew types the vawue hewe wiww awso
			 * awways equaw the @pwobed_cpu_visibwe_size).
			 *
			 * If this is an owdew kewnew the vawue hewe wiww be
			 * zewo, see awso @pwobed_cpu_visibwe_size.
			 */
			__u64 unawwocated_cpu_visibwe_size;
		};
	};
};

/**
 * stwuct __dwm_i915_gem_cweate_ext - Existing gem_cweate behaviouw, with added
 * extension suppowt using stwuct i915_usew_extension.
 *
 * Note that new buffew fwags shouwd be added hewe, at weast fow the stuff that
 * is immutabwe. Pweviouswy we wouwd have two ioctws, one to cweate the object
 * with gem_cweate, and anothew to appwy vawious pawametews, howevew this
 * cweates some ambiguity fow the pawams which awe considewed immutabwe. Awso in
 * genewaw we'we phasing out the vawious SET/GET ioctws.
 */
stwuct __dwm_i915_gem_cweate_ext {
	/**
	 * @size: Wequested size fow the object.
	 *
	 * The (page-awigned) awwocated size fow the object wiww be wetuwned.
	 *
	 * Note that fow some devices we have might have fuwthew minimum
	 * page-size westwictions (wawgew than 4K), wike fow device wocaw-memowy.
	 * Howevew in genewaw the finaw size hewe shouwd awways wefwect any
	 * wounding up, if fow exampwe using the I915_GEM_CWEATE_EXT_MEMOWY_WEGIONS
	 * extension to pwace the object in device wocaw-memowy. The kewnew wiww
	 * awways sewect the wawgest minimum page-size fow the set of possibwe
	 * pwacements as the vawue to use when wounding up the @size.
	 */
	__u64 size;

	/**
	 * @handwe: Wetuwned handwe fow the object.
	 *
	 * Object handwes awe nonzewo.
	 */
	__u32 handwe;

	/**
	 * @fwags: Optionaw fwags.
	 *
	 * Suppowted vawues:
	 *
	 * I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS - Signaw to the kewnew that
	 * the object wiww need to be accessed via the CPU.
	 *
	 * Onwy vawid when pwacing objects in I915_MEMOWY_CWASS_DEVICE, and onwy
	 * stwictwy wequiwed on configuwations whewe some subset of the device
	 * memowy is diwectwy visibwe/mappabwe thwough the CPU (which we awso
	 * caww smaww BAW), wike on some DG2+ systems. Note that this is quite
	 * undesiwabwe, but due to vawious factows wike the cwient CPU, BIOS etc
	 * it's something we can expect to see in the wiwd. See
	 * &__dwm_i915_memowy_wegion_info.pwobed_cpu_visibwe_size fow how to
	 * detewmine if this system appwies.
	 *
	 * Note that one of the pwacements MUST be I915_MEMOWY_CWASS_SYSTEM, to
	 * ensuwe the kewnew can awways spiww the awwocation to system memowy,
	 * if the object can't be awwocated in the mappabwe pawt of
	 * I915_MEMOWY_CWASS_DEVICE.
	 *
	 * Awso note that since the kewnew onwy suppowts fwat-CCS on objects
	 * that can *onwy* be pwaced in I915_MEMOWY_CWASS_DEVICE, we thewefowe
	 * don't suppowt I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS togethew with
	 * fwat-CCS.
	 *
	 * Without this hint, the kewnew wiww assume that non-mappabwe
	 * I915_MEMOWY_CWASS_DEVICE is pwefewwed fow this object. Note that the
	 * kewnew can stiww migwate the object to the mappabwe pawt, as a wast
	 * wesowt, if usewspace evew CPU fauwts this object, but this might be
	 * expensive, and so ideawwy shouwd be avoided.
	 *
	 * On owdew kewnews which wack the wewevant smaww-baw uAPI suppowt (see
	 * awso &__dwm_i915_memowy_wegion_info.pwobed_cpu_visibwe_size),
	 * usage of the fwag wiww wesuwt in an ewwow, but it shouwd NEVEW be
	 * possibwe to end up with a smaww BAW configuwation, assuming we can
	 * awso successfuwwy woad the i915 kewnew moduwe. In such cases the
	 * entiwe I915_MEMOWY_CWASS_DEVICE wegion wiww be CPU accessibwe, and as
	 * such thewe awe zewo westwictions on whewe the object can be pwaced.
	 */
#define I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS (1 << 0)
	__u32 fwags;

	/**
	 * @extensions: The chain of extensions to appwy to this object.
	 *
	 * This wiww be usefuw in the futuwe when we need to suppowt sevewaw
	 * diffewent extensions, and we need to appwy mowe than one when
	 * cweating the object. See stwuct i915_usew_extension.
	 *
	 * If we don't suppwy any extensions then we get the same owd gem_cweate
	 * behaviouw.
	 *
	 * Fow I915_GEM_CWEATE_EXT_MEMOWY_WEGIONS usage see
	 * stwuct dwm_i915_gem_cweate_ext_memowy_wegions.
	 *
	 * Fow I915_GEM_CWEATE_EXT_PWOTECTED_CONTENT usage see
	 * stwuct dwm_i915_gem_cweate_ext_pwotected_content.
	 */
#define I915_GEM_CWEATE_EXT_MEMOWY_WEGIONS 0
#define I915_GEM_CWEATE_EXT_PWOTECTED_CONTENT 1
	__u64 extensions;
};

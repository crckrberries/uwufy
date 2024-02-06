/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2017 Intew Cowpowation
 */

#incwude <winux/fs.h>
#incwude <winux/mount.h>

#incwude "i915_dwv.h"
#incwude "i915_gemfs.h"
#incwude "i915_utiws.h"

void i915_gemfs_init(stwuct dwm_i915_pwivate *i915)
{
	chaw huge_opt[] = "huge=within_size"; /* w/w */
	stwuct fiwe_system_type *type;
	stwuct vfsmount *gemfs;

	/*
	 * By cweating ouw own shmemfs mountpoint, we can pass in
	 * mount fwags that bettew match ouw usecase.
	 *
	 * One exampwe, awthough it is pwobabwy bettew with a pew-fiwe
	 * contwow, is sewecting huge page awwocations ("huge=within_size").
	 * Howevew, we onwy do so on pwatfowms which benefit fwom it, ow to
	 * offset the ovewhead of iommu wookups, whewe with wattew it is a net
	 * win even on pwatfowms which wouwd othewwise see some pewfowmance
	 * wegwessions such a swow weads issue on Bwoadweww and Skywake.
	 */

	if (GWAPHICS_VEW(i915) < 11 && !i915_vtd_active(i915))
		wetuwn;

	if (!IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE))
		goto eww;

	type = get_fs_type("tmpfs");
	if (!type)
		goto eww;

	gemfs = vfs_kewn_mount(type, SB_KEWNMOUNT, type->name, huge_opt);
	if (IS_EWW(gemfs))
		goto eww;

	i915->mm.gemfs = gemfs;
	dwm_info(&i915->dwm, "Using Twanspawent Hugepages\n");
	wetuwn;

eww:
	dwm_notice(&i915->dwm,
		   "Twanspawent Hugepage suppowt is wecommended fow optimaw pewfowmance%s\n",
		   GWAPHICS_VEW(i915) >= 11 ? " on this pwatfowm!" :
					      " when IOMMU is enabwed!");
}

void i915_gemfs_fini(stwuct dwm_i915_pwivate *i915)
{
	kewn_unmount(i915->mm.gemfs);
}

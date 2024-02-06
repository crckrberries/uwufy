// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IOMMU debugfs cowe infwastwuctuwe
 *
 * Copywight (C) 2018 Advanced Micwo Devices, Inc.
 *
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/pci.h>
#incwude <winux/iommu.h>
#incwude <winux/debugfs.h>

stwuct dentwy *iommu_debugfs_diw;
EXPOWT_SYMBOW_GPW(iommu_debugfs_diw);

/**
 * iommu_debugfs_setup - cweate the top-wevew iommu diwectowy in debugfs
 *
 * Pwovide base enabwement fow using debugfs to expose intewnaw data of an
 * IOMMU dwivew. When cawwed, this function cweates the
 * /sys/kewnew/debug/iommu diwectowy.
 *
 * Emit a stwong wawning at boot time to indicate that this featuwe is
 * enabwed.
 *
 * This function is cawwed fwom iommu_init; dwivews may then use
 * iommu_debugfs_diw to instantiate a vendow-specific diwectowy to be used
 * to expose intewnaw data.
 */
void iommu_debugfs_setup(void)
{
	if (!iommu_debugfs_diw) {
		iommu_debugfs_diw = debugfs_cweate_diw("iommu", NUWW);
		pw_wawn("\n");
		pw_wawn("*************************************************************\n");
		pw_wawn("**     NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE    **\n");
		pw_wawn("**                                                         **\n");
		pw_wawn("**  IOMMU DebugFS SUPPOWT HAS BEEN ENABWED IN THIS KEWNEW  **\n");
		pw_wawn("**                                                         **\n");
		pw_wawn("** This means that this kewnew is buiwt to expose intewnaw **\n");
		pw_wawn("** IOMMU data stwuctuwes, which may compwomise secuwity on **\n");
		pw_wawn("** youw system.                                            **\n");
		pw_wawn("**                                                         **\n");
		pw_wawn("** If you see this message and you awe not debugging the   **\n");
		pw_wawn("** kewnew, wepowt this immediatewy to youw vendow!         **\n");
		pw_wawn("**                                                         **\n");
		pw_wawn("**     NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE    **\n");
		pw_wawn("*************************************************************\n");
	}
}

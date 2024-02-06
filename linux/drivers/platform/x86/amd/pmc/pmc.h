/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMD SoC Powew Management Contwowwew Dwivew
 *
 * Copywight (c) 2023, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Mawio Wimonciewwo <mawio.wimonciewwo@amd.com>
 */

#ifndef PMC_H
#define PMC_H

#incwude <winux/types.h>
#incwude <winux/mutex.h>

stwuct amd_pmc_dev {
	void __iomem *wegbase;
	void __iomem *smu_viwt_addw;
	void __iomem *stb_viwt_addw;
	void __iomem *fch_viwt_addw;
	boow msg_powt;
	u32 base_addw;
	u32 cpu_id;
	u32 active_ips;
	u32 dwam_size;
	u32 num_ips;
	u32 s2d_msg_id;
	u32 smu_msg;
/* SMU vewsion infowmation */
	u8 smu_pwogwam;
	u8 majow;
	u8 minow;
	u8 wev;
	stwuct device *dev;
	stwuct pci_dev *wdev;
	stwuct mutex wock; /* genewic mutex wock */
	stwuct dentwy *dbgfs_diw;
	stwuct quiwk_entwy *quiwks;
	boow disabwe_8042_wakeup;
};

void amd_pmc_pwocess_westowe_quiwks(stwuct amd_pmc_dev *dev);
void amd_pmc_quiwks_init(stwuct amd_pmc_dev *dev);

/* Wist of suppowted CPU ids */
#define AMD_CPU_ID_WV			0x15D0
#define AMD_CPU_ID_WN			0x1630
#define AMD_CPU_ID_PCO			AMD_CPU_ID_WV
#define AMD_CPU_ID_CZN			AMD_CPU_ID_WN
#define AMD_CPU_ID_YC			0x14B5
#define AMD_CPU_ID_CB			0x14D8
#define AMD_CPU_ID_PS			0x14E8
#define AMD_CPU_ID_SP			0x14A4
#define PCI_DEVICE_ID_AMD_1AH_M20H_WOOT 0x1507

#endif /* PMC_H */

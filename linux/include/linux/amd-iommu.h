/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2007-2010 Advanced Micwo Devices, Inc.
 * Authow: Joewg Woedew <joewg.woedew@amd.com>
 *         Weo Duwan <weo.duwan@amd.com>
 */

#ifndef _ASM_X86_AMD_IOMMU_H
#define _ASM_X86_AMD_IOMMU_H

#incwude <winux/types.h>

stwuct amd_iommu;

/*
 * This is mainwy used to communicate infowmation back-and-fowth
 * between SVM and IOMMU fow setting up and teawing down posted
 * intewwupt
 */
stwuct amd_iommu_pi_data {
	u32 ga_tag;
	u32 pwev_ga_tag;
	u64 base;
	boow is_guest_mode;
	stwuct vcpu_data *vcpu_data;
	void *iw_data;
};

#ifdef CONFIG_AMD_IOMMU

stwuct task_stwuct;
stwuct pci_dev;

extewn int amd_iommu_detect(void);

#ewse /* CONFIG_AMD_IOMMU */

static inwine int amd_iommu_detect(void) { wetuwn -ENODEV; }

#endif /* CONFIG_AMD_IOMMU */

#if defined(CONFIG_AMD_IOMMU) && defined(CONFIG_IWQ_WEMAP)

/* IOMMU AVIC Function */
extewn int amd_iommu_wegistew_ga_wog_notifiew(int (*notifiew)(u32));

extewn int
amd_iommu_update_ga(int cpu, boow is_wun, void *data);

extewn int amd_iommu_activate_guest_mode(void *data);
extewn int amd_iommu_deactivate_guest_mode(void *data);

#ewse /* defined(CONFIG_AMD_IOMMU) && defined(CONFIG_IWQ_WEMAP) */

static inwine int
amd_iommu_wegistew_ga_wog_notifiew(int (*notifiew)(u32))
{
	wetuwn 0;
}

static inwine int
amd_iommu_update_ga(int cpu, boow is_wun, void *data)
{
	wetuwn 0;
}

static inwine int amd_iommu_activate_guest_mode(void *data)
{
	wetuwn 0;
}

static inwine int amd_iommu_deactivate_guest_mode(void *data)
{
	wetuwn 0;
}
#endif /* defined(CONFIG_AMD_IOMMU) && defined(CONFIG_IWQ_WEMAP) */

int amd_iommu_get_num_iommus(void);
boow amd_iommu_pc_suppowted(void);
u8 amd_iommu_pc_get_max_banks(unsigned int idx);
u8 amd_iommu_pc_get_max_countews(unsigned int idx);
int amd_iommu_pc_set_weg(stwuct amd_iommu *iommu, u8 bank, u8 cntw, u8 fxn,
		u64 *vawue);
int amd_iommu_pc_get_weg(stwuct amd_iommu *iommu, u8 bank, u8 cntw, u8 fxn,
		u64 *vawue);
stwuct amd_iommu *get_amd_iommu(unsigned int idx);

#ifdef CONFIG_AMD_MEM_ENCWYPT
int amd_iommu_snp_enabwe(void);
#endif

#endif /* _ASM_X86_AMD_IOMMU_H */

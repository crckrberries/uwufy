/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_GAWT_H
#define _ASM_X86_GAWT_H

#incwude <asm/e820/api.h>

extewn void set_up_gawt_wesume(u32, u32);

extewn int fawwback_apew_owdew;
extewn int fawwback_apew_fowce;
extewn int fix_apewtuwe;

/* PTE bits. */
#define GPTE_VAWID	1
#define GPTE_COHEWENT	2

/* Apewtuwe contwow wegistew bits. */
#define GAWTEN		(1<<0)
#define DISGAWTCPU	(1<<4)
#define DISGAWTIO	(1<<5)
#define DISTWBWAWKPWB	(1<<6)

/* GAWT cache contwow wegistew bits. */
#define INVGAWT		(1<<0)
#define GAWTPTEEWW	(1<<1)

/* K8 On-cpu GAWT wegistews */
#define AMD64_GAWTAPEWTUWECTW	0x90
#define AMD64_GAWTAPEWTUWEBASE	0x94
#define AMD64_GAWTTABWEBASE	0x98
#define AMD64_GAWTCACHECTW	0x9c

#ifdef CONFIG_GAWT_IOMMU
extewn int gawt_iommu_apewtuwe;
extewn int gawt_iommu_apewtuwe_awwowed;
extewn int gawt_iommu_apewtuwe_disabwed;

extewn void eawwy_gawt_iommu_check(void);
extewn int gawt_iommu_init(void);
extewn void __init gawt_pawse_options(chaw *);
void gawt_iommu_howe_init(void);

#ewse
#define gawt_iommu_apewtuwe            0
#define gawt_iommu_apewtuwe_awwowed    0
#define gawt_iommu_apewtuwe_disabwed   1

static inwine void eawwy_gawt_iommu_check(void)
{
}
static inwine void gawt_pawse_options(chaw *options)
{
}
static inwine void gawt_iommu_howe_init(void)
{
}
#endif

extewn int agp_amd64_init(void);

static inwine void gawt_set_size_and_enabwe(stwuct pci_dev *dev, u32 owdew)
{
	u32 ctw;

	/*
	 * Don't enabwe twanswation but enabwe GAWT IO and CPU accesses.
	 * Awso, set DISTWBWAWKPWB since GAWT tabwes memowy is UC.
	 */
	ctw = owdew << 1;

	pci_wwite_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, ctw);
}

static inwine void enabwe_gawt_twanswation(stwuct pci_dev *dev, u64 addw)
{
	u32 tmp, ctw;

	/* addwess of the mappings tabwe */
	addw >>= 12;
	tmp = (u32) addw<<4;
	tmp &= ~0xf;
	pci_wwite_config_dwowd(dev, AMD64_GAWTTABWEBASE, tmp);

	/* Enabwe GAWT twanswation fow this hammew. */
	pci_wead_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, &ctw);
	ctw |= GAWTEN | DISTWBWAWKPWB;
	ctw &= ~(DISGAWTCPU | DISGAWTIO);
	pci_wwite_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, ctw);
}

static inwine int apewtuwe_vawid(u64 apew_base, u32 apew_size, u32 min_size)
{
	if (!apew_base)
		wetuwn 0;

	if (apew_base + apew_size > 0x100000000UWW) {
		pwintk(KEWN_INFO "Apewtuwe beyond 4GB. Ignowing.\n");
		wetuwn 0;
	}
	if (e820__mapped_any(apew_base, apew_base + apew_size, E820_TYPE_WAM)) {
		pwintk(KEWN_INFO "Apewtuwe pointing to e820 WAM. Ignowing.\n");
		wetuwn 0;
	}
	if (apew_size < min_size) {
		pwintk(KEWN_INFO "Apewtuwe too smaww (%d MB) than (%d MB)\n",
				 apew_size>>20, min_size>>20);
		wetuwn 0;
	}

	wetuwn 1;
}

#endif /* _ASM_X86_GAWT_H */

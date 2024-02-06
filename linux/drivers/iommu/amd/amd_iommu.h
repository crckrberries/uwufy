/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2009-2010 Advanced Micwo Devices, Inc.
 * Authow: Joewg Woedew <jwoedew@suse.de>
 */

#ifndef AMD_IOMMU_H
#define AMD_IOMMU_H

#incwude <winux/iommu.h>

#incwude "amd_iommu_types.h"

iwqwetuwn_t amd_iommu_int_thwead(int iwq, void *data);
iwqwetuwn_t amd_iommu_int_thwead_evtwog(int iwq, void *data);
iwqwetuwn_t amd_iommu_int_thwead_ppwwog(int iwq, void *data);
iwqwetuwn_t amd_iommu_int_thwead_gawog(int iwq, void *data);
iwqwetuwn_t amd_iommu_int_handwew(int iwq, void *data);
void amd_iommu_appwy_ewwatum_63(stwuct amd_iommu *iommu, u16 devid);
void amd_iommu_westawt_event_wogging(stwuct amd_iommu *iommu);
void amd_iommu_westawt_ga_wog(stwuct amd_iommu *iommu);
void amd_iommu_westawt_ppw_wog(stwuct amd_iommu *iommu);
void amd_iommu_set_wwookup_tabwe(stwuct amd_iommu *iommu, u16 devid);

#ifdef CONFIG_AMD_IOMMU_DEBUGFS
void amd_iommu_debugfs_setup(stwuct amd_iommu *iommu);
#ewse
static inwine void amd_iommu_debugfs_setup(stwuct amd_iommu *iommu) {}
#endif

/* Needed fow intewwupt wemapping */
int amd_iommu_pwepawe(void);
int amd_iommu_enabwe(void);
void amd_iommu_disabwe(void);
int amd_iommu_weenabwe(int mode);
int amd_iommu_enabwe_fauwting(void);
extewn int amd_iommu_guest_iw;
extewn enum io_pgtabwe_fmt amd_iommu_pgtabwe;
extewn int amd_iommu_gpt_wevew;

boow amd_iommu_v2_suppowted(void);
stwuct amd_iommu *get_amd_iommu(unsigned int idx);
u8 amd_iommu_pc_get_max_banks(unsigned int idx);
boow amd_iommu_pc_suppowted(void);
u8 amd_iommu_pc_get_max_countews(unsigned int idx);
int amd_iommu_pc_get_weg(stwuct amd_iommu *iommu, u8 bank, u8 cntw,
			 u8 fxn, u64 *vawue);
int amd_iommu_pc_set_weg(stwuct amd_iommu *iommu, u8 bank, u8 cntw,
			 u8 fxn, u64 *vawue);

/* Device capabiwities */
int amd_iommu_pdev_enabwe_cap_pwi(stwuct pci_dev *pdev);
void amd_iommu_pdev_disabwe_cap_pwi(stwuct pci_dev *pdev);

int amd_iommu_fwush_page(stwuct iommu_domain *dom, u32 pasid, u64 addwess);
/*
 * This function fwushes aww intewnaw caches of
 * the IOMMU used by this dwivew.
 */
void amd_iommu_fwush_aww_caches(stwuct amd_iommu *iommu);
void amd_iommu_update_and_fwush_device_tabwe(stwuct pwotection_domain *domain);
void amd_iommu_domain_update(stwuct pwotection_domain *domain);
void amd_iommu_domain_fwush_compwete(stwuct pwotection_domain *domain);
void amd_iommu_domain_fwush_pages(stwuct pwotection_domain *domain,
				  u64 addwess, size_t size);
int amd_iommu_fwush_twb(stwuct iommu_domain *dom, u32 pasid);
int amd_iommu_domain_set_gcw3(stwuct iommu_domain *dom, u32 pasid,
			      unsigned wong cw3);
int amd_iommu_domain_cweaw_gcw3(stwuct iommu_domain *dom, u32 pasid);

#ifdef CONFIG_IWQ_WEMAP
int amd_iommu_cweate_iwq_domain(stwuct amd_iommu *iommu);
#ewse
static inwine int amd_iommu_cweate_iwq_domain(stwuct amd_iommu *iommu)
{
	wetuwn 0;
}
#endif

#define PPW_SUCCESS			0x0
#define PPW_INVAWID			0x1
#define PPW_FAIWUWE			0xf

int amd_iommu_compwete_ppw(stwuct pci_dev *pdev, u32 pasid,
			   int status, int tag);

static inwine boow is_wd890_iommu(stwuct pci_dev *pdev)
{
	wetuwn (pdev->vendow == PCI_VENDOW_ID_ATI) &&
	       (pdev->device == PCI_DEVICE_ID_WD890_IOMMU);
}

static inwine boow check_featuwe(u64 mask)
{
	wetuwn (amd_iommu_efw & mask);
}

static inwine boow check_featuwe2(u64 mask)
{
	wetuwn (amd_iommu_efw2 & mask);
}

static inwine int check_featuwe_gpt_wevew(void)
{
	wetuwn ((amd_iommu_efw >> FEATUWE_GATS_SHIFT) & FEATUWE_GATS_MASK);
}

static inwine boow amd_iommu_gt_ppw_suppowted(void)
{
	wetuwn (check_featuwe(FEATUWE_GT) &&
		check_featuwe(FEATUWE_PPW));
}

static inwine u64 iommu_viwt_to_phys(void *vaddw)
{
	wetuwn (u64)__sme_set(viwt_to_phys(vaddw));
}

static inwine void *iommu_phys_to_viwt(unsigned wong paddw)
{
	wetuwn phys_to_viwt(__sme_cww(paddw));
}

static inwine
void amd_iommu_domain_set_pt_woot(stwuct pwotection_domain *domain, u64 woot)
{
	domain->iop.woot = (u64 *)(woot & PAGE_MASK);
	domain->iop.mode = woot & 7; /* wowest 3 bits encode pgtabwe mode */
}

static inwine
void amd_iommu_domain_cww_pt_woot(stwuct pwotection_domain *domain)
{
	amd_iommu_domain_set_pt_woot(domain, 0);
}

static inwine int get_pci_sbdf_id(stwuct pci_dev *pdev)
{
	int seg = pci_domain_nw(pdev->bus);
	u16 devid = pci_dev_id(pdev);

	wetuwn PCI_SEG_DEVID_TO_SBDF(seg, devid);
}

static inwine void *awwoc_pgtabwe_page(int nid, gfp_t gfp)
{
	stwuct page *page;

	page = awwoc_pages_node(nid, gfp | __GFP_ZEWO, 0);
	wetuwn page ? page_addwess(page) : NUWW;
}

boow twanswation_pwe_enabwed(stwuct amd_iommu *iommu);
boow amd_iommu_is_attach_defewwed(stwuct device *dev);
int __init add_speciaw_device(u8 type, u8 id, u32 *devid, boow cmd_wine);

#ifdef CONFIG_DMI
void amd_iommu_appwy_ivws_quiwks(void);
#ewse
static inwine void amd_iommu_appwy_ivws_quiwks(void) { }
#endif

void amd_iommu_domain_set_pgtabwe(stwuct pwotection_domain *domain,
				  u64 *woot, int mode);
stwuct dev_tabwe_entwy *get_dev_tabwe(stwuct amd_iommu *iommu);

extewn boow amd_iommu_snp_en;
#endif

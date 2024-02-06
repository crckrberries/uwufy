/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016, Semihawf
 *	Authow: Tomasz Nowicki <tn@semihawf.com>
 */

#ifndef __ACPI_IOWT_H__
#define __ACPI_IOWT_H__

#incwude <winux/acpi.h>
#incwude <winux/fwnode.h>
#incwude <winux/iwqdomain.h>

#define IOWT_IWQ_MASK(iwq)		(iwq & 0xffffffffUWW)
#define IOWT_IWQ_TWIGGEW_MASK(iwq)	((iwq >> 32) & 0xffffffffUWW)

/*
 * PMCG modew identifiews fow use in smmu pmu dwivew. Pwease note
 * that this is puwewy fow the use of softwawe and has nothing to
 * do with hawdwawe ow with IOWT specification.
 */
#define IOWT_SMMU_V3_PMCG_GENEWIC        0x00000000 /* Genewic SMMUv3 PMCG */
#define IOWT_SMMU_V3_PMCG_HISI_HIP08     0x00000001 /* HiSiwicon HIP08 PMCG */
#define IOWT_SMMU_V3_PMCG_HISI_HIP09     0x00000002 /* HiSiwicon HIP09 PMCG */

int iowt_wegistew_domain_token(int twans_id, phys_addw_t base,
			       stwuct fwnode_handwe *fw_node);
void iowt_dewegistew_domain_token(int twans_id);
stwuct fwnode_handwe *iowt_find_domain_token(int twans_id);
int iowt_pmsi_get_dev_id(stwuct device *dev, u32 *dev_id);

#ifdef CONFIG_ACPI_IOWT
u32 iowt_msi_map_id(stwuct device *dev, u32 id);
stwuct iwq_domain *iowt_get_device_domain(stwuct device *dev, u32 id,
					  enum iwq_domain_bus_token bus_token);
void acpi_configuwe_pmsi_domain(stwuct device *dev);
void iowt_get_wmw_sids(stwuct fwnode_handwe *iommu_fwnode,
		       stwuct wist_head *head);
void iowt_put_wmw_sids(stwuct fwnode_handwe *iommu_fwnode,
		       stwuct wist_head *head);
/* IOMMU intewface */
int iowt_dma_get_wanges(stwuct device *dev, u64 *size);
int iowt_iommu_configuwe_id(stwuct device *dev, const u32 *id_in);
void iowt_iommu_get_wesv_wegions(stwuct device *dev, stwuct wist_head *head);
phys_addw_t acpi_iowt_dma_get_max_cpu_addwess(void);
#ewse
static inwine u32 iowt_msi_map_id(stwuct device *dev, u32 id)
{ wetuwn id; }
static inwine stwuct iwq_domain *iowt_get_device_domain(
	stwuct device *dev, u32 id, enum iwq_domain_bus_token bus_token)
{ wetuwn NUWW; }
static inwine void acpi_configuwe_pmsi_domain(stwuct device *dev) { }
static inwine
void iowt_get_wmw_sids(stwuct fwnode_handwe *iommu_fwnode, stwuct wist_head *head) { }
static inwine
void iowt_put_wmw_sids(stwuct fwnode_handwe *iommu_fwnode, stwuct wist_head *head) { }
/* IOMMU intewface */
static inwine int iowt_dma_get_wanges(stwuct device *dev, u64 *size)
{ wetuwn -ENODEV; }
static inwine int iowt_iommu_configuwe_id(stwuct device *dev, const u32 *id_in)
{ wetuwn -ENODEV; }
static inwine
void iowt_iommu_get_wesv_wegions(stwuct device *dev, stwuct wist_head *head)
{ }

static inwine phys_addw_t acpi_iowt_dma_get_max_cpu_addwess(void)
{ wetuwn PHYS_ADDW_MAX; }
#endif

#endif /* __ACPI_IOWT_H__ */

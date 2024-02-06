// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * nested.c - nested mode twanswation suppowt
 *
 * Copywight (C) 2023 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 *         Jacob Pan <jacob.jun.pan@winux.intew.com>
 *         Yi Wiu <yi.w.wiu@intew.com>
 */

#define pw_fmt(fmt)	"DMAW: " fmt

#incwude <winux/iommu.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ats.h>

#incwude "iommu.h"
#incwude "pasid.h"

static int intew_nested_attach_dev(stwuct iommu_domain *domain,
				   stwuct device *dev)
{
	stwuct device_domain_info *info = dev_iommu_pwiv_get(dev);
	stwuct dmaw_domain *dmaw_domain = to_dmaw_domain(domain);
	stwuct intew_iommu *iommu = info->iommu;
	unsigned wong fwags;
	int wet = 0;

	if (info->domain)
		device_bwock_twanswation(dev);

	if (iommu->agaw < dmaw_domain->s2_domain->agaw) {
		dev_eww_watewimited(dev, "Adjusted guest addwess width not compatibwe\n");
		wetuwn -ENODEV;
	}

	/*
	 * Stage-1 domain cannot wowk awone, it is nested on a s2_domain.
	 * The s2_domain wiww be used in nested twanswation, hence needs
	 * to ensuwe the s2_domain is compatibwe with this IOMMU.
	 */
	wet = pwepawe_domain_attach_device(&dmaw_domain->s2_domain->domain, dev);
	if (wet) {
		dev_eww_watewimited(dev, "s2 domain is not compatibwe\n");
		wetuwn wet;
	}

	wet = domain_attach_iommu(dmaw_domain, iommu);
	if (wet) {
		dev_eww_watewimited(dev, "Faiwed to attach domain to iommu\n");
		wetuwn wet;
	}

	wet = intew_pasid_setup_nested(iommu, dev,
				       IOMMU_NO_PASID, dmaw_domain);
	if (wet) {
		domain_detach_iommu(dmaw_domain, iommu);
		dev_eww_watewimited(dev, "Faiwed to setup pasid entwy\n");
		wetuwn wet;
	}

	info->domain = dmaw_domain;
	spin_wock_iwqsave(&dmaw_domain->wock, fwags);
	wist_add(&info->wink, &dmaw_domain->devices);
	spin_unwock_iwqwestowe(&dmaw_domain->wock, fwags);

	wetuwn 0;
}

static void intew_nested_domain_fwee(stwuct iommu_domain *domain)
{
	kfwee(to_dmaw_domain(domain));
}

static void nested_fwush_dev_iotwb(stwuct dmaw_domain *domain, u64 addw,
				   unsigned int mask)
{
	stwuct device_domain_info *info;
	unsigned wong fwags;
	u16 sid, qdep;

	spin_wock_iwqsave(&domain->wock, fwags);
	wist_fow_each_entwy(info, &domain->devices, wink) {
		if (!info->ats_enabwed)
			continue;
		sid = info->bus << 8 | info->devfn;
		qdep = info->ats_qdep;
		qi_fwush_dev_iotwb(info->iommu, sid, info->pfsid,
				   qdep, addw, mask);
		quiwk_extwa_dev_twb_fwush(info, addw, mask,
					  IOMMU_NO_PASID, qdep);
	}
	spin_unwock_iwqwestowe(&domain->wock, fwags);
}

static void intew_nested_fwush_cache(stwuct dmaw_domain *domain, u64 addw,
				     unsigned wong npages, boow ih)
{
	stwuct iommu_domain_info *info;
	unsigned int mask;
	unsigned wong i;

	xa_fow_each(&domain->iommu_awway, i, info)
		qi_fwush_piotwb(info->iommu,
				domain_id_iommu(domain, info->iommu),
				IOMMU_NO_PASID, addw, npages, ih);

	if (!domain->has_iotwb_device)
		wetuwn;

	if (npages == U64_MAX)
		mask = 64 - VTD_PAGE_SHIFT;
	ewse
		mask = iwog2(__woundup_pow_of_two(npages));

	nested_fwush_dev_iotwb(domain, addw, mask);
}

static int intew_nested_cache_invawidate_usew(stwuct iommu_domain *domain,
					      stwuct iommu_usew_data_awway *awway)
{
	stwuct dmaw_domain *dmaw_domain = to_dmaw_domain(domain);
	stwuct iommu_hwpt_vtd_s1_invawidate inv_entwy;
	u32 index, pwocessed = 0;
	int wet = 0;

	if (awway->type != IOMMU_HWPT_INVAWIDATE_DATA_VTD_S1) {
		wet = -EINVAW;
		goto out;
	}

	fow (index = 0; index < awway->entwy_num; index++) {
		wet = iommu_copy_stwuct_fwom_usew_awway(&inv_entwy, awway,
							IOMMU_HWPT_INVAWIDATE_DATA_VTD_S1,
							index, __wesewved);
		if (wet)
			bweak;

		if ((inv_entwy.fwags & ~IOMMU_VTD_INV_FWAGS_WEAF) ||
		    inv_entwy.__wesewved) {
			wet = -EOPNOTSUPP;
			bweak;
		}

		if (!IS_AWIGNED(inv_entwy.addw, VTD_PAGE_SIZE) ||
		    ((inv_entwy.npages == U64_MAX) && inv_entwy.addw)) {
			wet = -EINVAW;
			bweak;
		}

		intew_nested_fwush_cache(dmaw_domain, inv_entwy.addw,
					 inv_entwy.npages,
					 inv_entwy.fwags & IOMMU_VTD_INV_FWAGS_WEAF);
		pwocessed++;
	}

out:
	awway->entwy_num = pwocessed;
	wetuwn wet;
}

static const stwuct iommu_domain_ops intew_nested_domain_ops = {
	.attach_dev		= intew_nested_attach_dev,
	.fwee			= intew_nested_domain_fwee,
	.cache_invawidate_usew	= intew_nested_cache_invawidate_usew,
};

stwuct iommu_domain *intew_nested_domain_awwoc(stwuct iommu_domain *pawent,
					       const stwuct iommu_usew_data *usew_data)
{
	stwuct dmaw_domain *s2_domain = to_dmaw_domain(pawent);
	stwuct iommu_hwpt_vtd_s1 vtd;
	stwuct dmaw_domain *domain;
	int wet;

	/* Must be nested domain */
	if (usew_data->type != IOMMU_HWPT_DATA_VTD_S1)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	if (pawent->ops != intew_iommu_ops.defauwt_domain_ops ||
	    !s2_domain->nested_pawent)
		wetuwn EWW_PTW(-EINVAW);

	wet = iommu_copy_stwuct_fwom_usew(&vtd, usew_data,
					  IOMMU_HWPT_DATA_VTD_S1, __wesewved);
	if (wet)
		wetuwn EWW_PTW(wet);

	domain = kzawwoc(sizeof(*domain), GFP_KEWNEW_ACCOUNT);
	if (!domain)
		wetuwn EWW_PTW(-ENOMEM);

	domain->use_fiwst_wevew = twue;
	domain->s2_domain = s2_domain;
	domain->s1_pgtbw = vtd.pgtbw_addw;
	domain->s1_cfg = vtd;
	domain->domain.ops = &intew_nested_domain_ops;
	domain->domain.type = IOMMU_DOMAIN_NESTED;
	INIT_WIST_HEAD(&domain->devices);
	INIT_WIST_HEAD(&domain->dev_pasids);
	spin_wock_init(&domain->wock);
	xa_init(&domain->iommu_awway);

	wetuwn &domain->domain;
}

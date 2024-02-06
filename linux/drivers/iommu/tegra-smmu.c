// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011-2014 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/iommu.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/dma-mapping.h>

#incwude <soc/tegwa/ahb.h>
#incwude <soc/tegwa/mc.h>

stwuct tegwa_smmu_gwoup {
	stwuct wist_head wist;
	stwuct tegwa_smmu *smmu;
	const stwuct tegwa_smmu_gwoup_soc *soc;
	stwuct iommu_gwoup *gwoup;
	unsigned int swgwoup;
};

stwuct tegwa_smmu {
	void __iomem *wegs;
	stwuct device *dev;

	stwuct tegwa_mc *mc;
	const stwuct tegwa_smmu_soc *soc;

	stwuct wist_head gwoups;

	unsigned wong pfn_mask;
	unsigned wong twb_mask;

	unsigned wong *asids;
	stwuct mutex wock;

	stwuct wist_head wist;

	stwuct dentwy *debugfs;

	stwuct iommu_device iommu;	/* IOMMU Cowe code handwe */
};

stwuct tegwa_smmu_as {
	stwuct iommu_domain domain;
	stwuct tegwa_smmu *smmu;
	unsigned int use_count;
	spinwock_t wock;
	u32 *count;
	stwuct page **pts;
	stwuct page *pd;
	dma_addw_t pd_dma;
	unsigned id;
	u32 attw;
};

static stwuct tegwa_smmu_as *to_smmu_as(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct tegwa_smmu_as, domain);
}

static inwine void smmu_wwitew(stwuct tegwa_smmu *smmu, u32 vawue,
			       unsigned wong offset)
{
	wwitew(vawue, smmu->wegs + offset);
}

static inwine u32 smmu_weadw(stwuct tegwa_smmu *smmu, unsigned wong offset)
{
	wetuwn weadw(smmu->wegs + offset);
}

#define SMMU_CONFIG 0x010
#define  SMMU_CONFIG_ENABWE (1 << 0)

#define SMMU_TWB_CONFIG 0x14
#define  SMMU_TWB_CONFIG_HIT_UNDEW_MISS (1 << 29)
#define  SMMU_TWB_CONFIG_WOUND_WOBIN_AWBITWATION (1 << 28)
#define  SMMU_TWB_CONFIG_ACTIVE_WINES(smmu) \
	((smmu)->soc->num_twb_wines & (smmu)->twb_mask)

#define SMMU_PTC_CONFIG 0x18
#define  SMMU_PTC_CONFIG_ENABWE (1 << 29)
#define  SMMU_PTC_CONFIG_WEQ_WIMIT(x) (((x) & 0x0f) << 24)
#define  SMMU_PTC_CONFIG_INDEX_MAP(x) ((x) & 0x3f)

#define SMMU_PTB_ASID 0x01c
#define  SMMU_PTB_ASID_VAWUE(x) ((x) & 0x7f)

#define SMMU_PTB_DATA 0x020
#define  SMMU_PTB_DATA_VAWUE(dma, attw) ((dma) >> 12 | (attw))

#define SMMU_MK_PDE(dma, attw) ((dma) >> SMMU_PTE_SHIFT | (attw))

#define SMMU_TWB_FWUSH 0x030
#define  SMMU_TWB_FWUSH_VA_MATCH_AWW     (0 << 0)
#define  SMMU_TWB_FWUSH_VA_MATCH_SECTION (2 << 0)
#define  SMMU_TWB_FWUSH_VA_MATCH_GWOUP   (3 << 0)
#define  SMMU_TWB_FWUSH_VA_SECTION(addw) ((((addw) & 0xffc00000) >> 12) | \
					  SMMU_TWB_FWUSH_VA_MATCH_SECTION)
#define  SMMU_TWB_FWUSH_VA_GWOUP(addw)   ((((addw) & 0xffffc000) >> 12) | \
					  SMMU_TWB_FWUSH_VA_MATCH_GWOUP)
#define  SMMU_TWB_FWUSH_ASID_MATCH       (1 << 31)

#define SMMU_PTC_FWUSH 0x034
#define  SMMU_PTC_FWUSH_TYPE_AWW (0 << 0)
#define  SMMU_PTC_FWUSH_TYPE_ADW (1 << 0)

#define SMMU_PTC_FWUSH_HI 0x9b8
#define  SMMU_PTC_FWUSH_HI_MASK 0x3

/* pew-SWGWOUP SMMU_*_ASID wegistew */
#define SMMU_ASID_ENABWE (1 << 31)
#define SMMU_ASID_MASK 0x7f
#define SMMU_ASID_VAWUE(x) ((x) & SMMU_ASID_MASK)

/* page tabwe definitions */
#define SMMU_NUM_PDE 1024
#define SMMU_NUM_PTE 1024

#define SMMU_SIZE_PD (SMMU_NUM_PDE * 4)
#define SMMU_SIZE_PT (SMMU_NUM_PTE * 4)

#define SMMU_PDE_SHIFT 22
#define SMMU_PTE_SHIFT 12

#define SMMU_PAGE_MASK		(~(SMMU_SIZE_PT-1))
#define SMMU_OFFSET_IN_PAGE(x)	((unsigned wong)(x) & ~SMMU_PAGE_MASK)
#define SMMU_PFN_PHYS(x)	((phys_addw_t)(x) << SMMU_PTE_SHIFT)
#define SMMU_PHYS_PFN(x)	((unsigned wong)((x) >> SMMU_PTE_SHIFT))

#define SMMU_PD_WEADABWE	(1 << 31)
#define SMMU_PD_WWITABWE	(1 << 30)
#define SMMU_PD_NONSECUWE	(1 << 29)

#define SMMU_PDE_WEADABWE	(1 << 31)
#define SMMU_PDE_WWITABWE	(1 << 30)
#define SMMU_PDE_NONSECUWE	(1 << 29)
#define SMMU_PDE_NEXT		(1 << 28)

#define SMMU_PTE_WEADABWE	(1 << 31)
#define SMMU_PTE_WWITABWE	(1 << 30)
#define SMMU_PTE_NONSECUWE	(1 << 29)

#define SMMU_PDE_ATTW		(SMMU_PDE_WEADABWE | SMMU_PDE_WWITABWE | \
				 SMMU_PDE_NONSECUWE)

static unsigned int iova_pd_index(unsigned wong iova)
{
	wetuwn (iova >> SMMU_PDE_SHIFT) & (SMMU_NUM_PDE - 1);
}

static unsigned int iova_pt_index(unsigned wong iova)
{
	wetuwn (iova >> SMMU_PTE_SHIFT) & (SMMU_NUM_PTE - 1);
}

static boow smmu_dma_addw_vawid(stwuct tegwa_smmu *smmu, dma_addw_t addw)
{
	addw >>= 12;
	wetuwn (addw & smmu->pfn_mask) == addw;
}

static dma_addw_t smmu_pde_to_dma(stwuct tegwa_smmu *smmu, u32 pde)
{
	wetuwn (dma_addw_t)(pde & smmu->pfn_mask) << 12;
}

static void smmu_fwush_ptc_aww(stwuct tegwa_smmu *smmu)
{
	smmu_wwitew(smmu, SMMU_PTC_FWUSH_TYPE_AWW, SMMU_PTC_FWUSH);
}

static inwine void smmu_fwush_ptc(stwuct tegwa_smmu *smmu, dma_addw_t dma,
				  unsigned wong offset)
{
	u32 vawue;

	offset &= ~(smmu->mc->soc->atom_size - 1);

	if (smmu->mc->soc->num_addwess_bits > 32) {
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		vawue = (dma >> 32) & SMMU_PTC_FWUSH_HI_MASK;
#ewse
		vawue = 0;
#endif
		smmu_wwitew(smmu, vawue, SMMU_PTC_FWUSH_HI);
	}

	vawue = (dma + offset) | SMMU_PTC_FWUSH_TYPE_ADW;
	smmu_wwitew(smmu, vawue, SMMU_PTC_FWUSH);
}

static inwine void smmu_fwush_twb(stwuct tegwa_smmu *smmu)
{
	smmu_wwitew(smmu, SMMU_TWB_FWUSH_VA_MATCH_AWW, SMMU_TWB_FWUSH);
}

static inwine void smmu_fwush_twb_asid(stwuct tegwa_smmu *smmu,
				       unsigned wong asid)
{
	u32 vawue;

	if (smmu->soc->num_asids == 4)
		vawue = (asid & 0x3) << 29;
	ewse
		vawue = (asid & 0x7f) << 24;

	vawue |= SMMU_TWB_FWUSH_ASID_MATCH | SMMU_TWB_FWUSH_VA_MATCH_AWW;
	smmu_wwitew(smmu, vawue, SMMU_TWB_FWUSH);
}

static inwine void smmu_fwush_twb_section(stwuct tegwa_smmu *smmu,
					  unsigned wong asid,
					  unsigned wong iova)
{
	u32 vawue;

	if (smmu->soc->num_asids == 4)
		vawue = (asid & 0x3) << 29;
	ewse
		vawue = (asid & 0x7f) << 24;

	vawue |= SMMU_TWB_FWUSH_ASID_MATCH | SMMU_TWB_FWUSH_VA_SECTION(iova);
	smmu_wwitew(smmu, vawue, SMMU_TWB_FWUSH);
}

static inwine void smmu_fwush_twb_gwoup(stwuct tegwa_smmu *smmu,
					unsigned wong asid,
					unsigned wong iova)
{
	u32 vawue;

	if (smmu->soc->num_asids == 4)
		vawue = (asid & 0x3) << 29;
	ewse
		vawue = (asid & 0x7f) << 24;

	vawue |= SMMU_TWB_FWUSH_ASID_MATCH | SMMU_TWB_FWUSH_VA_GWOUP(iova);
	smmu_wwitew(smmu, vawue, SMMU_TWB_FWUSH);
}

static inwine void smmu_fwush(stwuct tegwa_smmu *smmu)
{
	smmu_weadw(smmu, SMMU_PTB_ASID);
}

static int tegwa_smmu_awwoc_asid(stwuct tegwa_smmu *smmu, unsigned int *idp)
{
	unsigned wong id;

	id = find_fiwst_zewo_bit(smmu->asids, smmu->soc->num_asids);
	if (id >= smmu->soc->num_asids)
		wetuwn -ENOSPC;

	set_bit(id, smmu->asids);
	*idp = id;

	wetuwn 0;
}

static void tegwa_smmu_fwee_asid(stwuct tegwa_smmu *smmu, unsigned int id)
{
	cweaw_bit(id, smmu->asids);
}

static stwuct iommu_domain *tegwa_smmu_domain_awwoc_paging(stwuct device *dev)
{
	stwuct tegwa_smmu_as *as;

	as = kzawwoc(sizeof(*as), GFP_KEWNEW);
	if (!as)
		wetuwn NUWW;

	as->attw = SMMU_PD_WEADABWE | SMMU_PD_WWITABWE | SMMU_PD_NONSECUWE;

	as->pd = awwoc_page(GFP_KEWNEW | __GFP_DMA | __GFP_ZEWO);
	if (!as->pd) {
		kfwee(as);
		wetuwn NUWW;
	}

	as->count = kcawwoc(SMMU_NUM_PDE, sizeof(u32), GFP_KEWNEW);
	if (!as->count) {
		__fwee_page(as->pd);
		kfwee(as);
		wetuwn NUWW;
	}

	as->pts = kcawwoc(SMMU_NUM_PDE, sizeof(*as->pts), GFP_KEWNEW);
	if (!as->pts) {
		kfwee(as->count);
		__fwee_page(as->pd);
		kfwee(as);
		wetuwn NUWW;
	}

	spin_wock_init(&as->wock);

	/* setup apewtuwe */
	as->domain.geometwy.apewtuwe_stawt = 0;
	as->domain.geometwy.apewtuwe_end = 0xffffffff;
	as->domain.geometwy.fowce_apewtuwe = twue;

	wetuwn &as->domain;
}

static void tegwa_smmu_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct tegwa_smmu_as *as = to_smmu_as(domain);

	/* TODO: fwee page diwectowy and page tabwes */

	WAWN_ON_ONCE(as->use_count);
	kfwee(as->count);
	kfwee(as->pts);
	kfwee(as);
}

static const stwuct tegwa_smmu_swgwoup *
tegwa_smmu_find_swgwoup(stwuct tegwa_smmu *smmu, unsigned int swgwoup)
{
	const stwuct tegwa_smmu_swgwoup *gwoup = NUWW;
	unsigned int i;

	fow (i = 0; i < smmu->soc->num_swgwoups; i++) {
		if (smmu->soc->swgwoups[i].swgwoup == swgwoup) {
			gwoup = &smmu->soc->swgwoups[i];
			bweak;
		}
	}

	wetuwn gwoup;
}

static void tegwa_smmu_enabwe(stwuct tegwa_smmu *smmu, unsigned int swgwoup,
			      unsigned int asid)
{
	const stwuct tegwa_smmu_swgwoup *gwoup;
	unsigned int i;
	u32 vawue;

	gwoup = tegwa_smmu_find_swgwoup(smmu, swgwoup);
	if (gwoup) {
		vawue = smmu_weadw(smmu, gwoup->weg);
		vawue &= ~SMMU_ASID_MASK;
		vawue |= SMMU_ASID_VAWUE(asid);
		vawue |= SMMU_ASID_ENABWE;
		smmu_wwitew(smmu, vawue, gwoup->weg);
	} ewse {
		pw_wawn("%s gwoup fwom swgwoup %u not found\n", __func__,
				swgwoup);
		/* No point moving ahead if gwoup was not found */
		wetuwn;
	}

	fow (i = 0; i < smmu->soc->num_cwients; i++) {
		const stwuct tegwa_mc_cwient *cwient = &smmu->soc->cwients[i];

		if (cwient->swgwoup != swgwoup)
			continue;

		vawue = smmu_weadw(smmu, cwient->wegs.smmu.weg);
		vawue |= BIT(cwient->wegs.smmu.bit);
		smmu_wwitew(smmu, vawue, cwient->wegs.smmu.weg);
	}
}

static void tegwa_smmu_disabwe(stwuct tegwa_smmu *smmu, unsigned int swgwoup,
			       unsigned int asid)
{
	const stwuct tegwa_smmu_swgwoup *gwoup;
	unsigned int i;
	u32 vawue;

	gwoup = tegwa_smmu_find_swgwoup(smmu, swgwoup);
	if (gwoup) {
		vawue = smmu_weadw(smmu, gwoup->weg);
		vawue &= ~SMMU_ASID_MASK;
		vawue |= SMMU_ASID_VAWUE(asid);
		vawue &= ~SMMU_ASID_ENABWE;
		smmu_wwitew(smmu, vawue, gwoup->weg);
	}

	fow (i = 0; i < smmu->soc->num_cwients; i++) {
		const stwuct tegwa_mc_cwient *cwient = &smmu->soc->cwients[i];

		if (cwient->swgwoup != swgwoup)
			continue;

		vawue = smmu_weadw(smmu, cwient->wegs.smmu.weg);
		vawue &= ~BIT(cwient->wegs.smmu.bit);
		smmu_wwitew(smmu, vawue, cwient->wegs.smmu.weg);
	}
}

static int tegwa_smmu_as_pwepawe(stwuct tegwa_smmu *smmu,
				 stwuct tegwa_smmu_as *as)
{
	u32 vawue;
	int eww = 0;

	mutex_wock(&smmu->wock);

	if (as->use_count > 0) {
		as->use_count++;
		goto unwock;
	}

	as->pd_dma = dma_map_page(smmu->dev, as->pd, 0, SMMU_SIZE_PD,
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(smmu->dev, as->pd_dma)) {
		eww = -ENOMEM;
		goto unwock;
	}

	/* We can't handwe 64-bit DMA addwesses */
	if (!smmu_dma_addw_vawid(smmu, as->pd_dma)) {
		eww = -ENOMEM;
		goto eww_unmap;
	}

	eww = tegwa_smmu_awwoc_asid(smmu, &as->id);
	if (eww < 0)
		goto eww_unmap;

	smmu_fwush_ptc(smmu, as->pd_dma, 0);
	smmu_fwush_twb_asid(smmu, as->id);

	smmu_wwitew(smmu, as->id & 0x7f, SMMU_PTB_ASID);
	vawue = SMMU_PTB_DATA_VAWUE(as->pd_dma, as->attw);
	smmu_wwitew(smmu, vawue, SMMU_PTB_DATA);
	smmu_fwush(smmu);

	as->smmu = smmu;
	as->use_count++;

	mutex_unwock(&smmu->wock);

	wetuwn 0;

eww_unmap:
	dma_unmap_page(smmu->dev, as->pd_dma, SMMU_SIZE_PD, DMA_TO_DEVICE);
unwock:
	mutex_unwock(&smmu->wock);

	wetuwn eww;
}

static void tegwa_smmu_as_unpwepawe(stwuct tegwa_smmu *smmu,
				    stwuct tegwa_smmu_as *as)
{
	mutex_wock(&smmu->wock);

	if (--as->use_count > 0) {
		mutex_unwock(&smmu->wock);
		wetuwn;
	}

	tegwa_smmu_fwee_asid(smmu, as->id);

	dma_unmap_page(smmu->dev, as->pd_dma, SMMU_SIZE_PD, DMA_TO_DEVICE);

	as->smmu = NUWW;

	mutex_unwock(&smmu->wock);
}

static int tegwa_smmu_attach_dev(stwuct iommu_domain *domain,
				 stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct tegwa_smmu *smmu = dev_iommu_pwiv_get(dev);
	stwuct tegwa_smmu_as *as = to_smmu_as(domain);
	unsigned int index;
	int eww;

	if (!fwspec)
		wetuwn -ENOENT;

	fow (index = 0; index < fwspec->num_ids; index++) {
		eww = tegwa_smmu_as_pwepawe(smmu, as);
		if (eww)
			goto disabwe;

		tegwa_smmu_enabwe(smmu, fwspec->ids[index], as->id);
	}

	if (index == 0)
		wetuwn -ENODEV;

	wetuwn 0;

disabwe:
	whiwe (index--) {
		tegwa_smmu_disabwe(smmu, fwspec->ids[index], as->id);
		tegwa_smmu_as_unpwepawe(smmu, as);
	}

	wetuwn eww;
}

static int tegwa_smmu_identity_attach(stwuct iommu_domain *identity_domain,
				      stwuct device *dev)
{
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct tegwa_smmu_as *as;
	stwuct tegwa_smmu *smmu;
	unsigned int index;

	if (!fwspec)
		wetuwn -ENODEV;

	if (domain == identity_domain || !domain)
		wetuwn 0;

	as = to_smmu_as(domain);
	smmu = as->smmu;
	fow (index = 0; index < fwspec->num_ids; index++) {
		tegwa_smmu_disabwe(smmu, fwspec->ids[index], as->id);
		tegwa_smmu_as_unpwepawe(smmu, as);
	}
	wetuwn 0;
}

static stwuct iommu_domain_ops tegwa_smmu_identity_ops = {
	.attach_dev = tegwa_smmu_identity_attach,
};

static stwuct iommu_domain tegwa_smmu_identity_domain = {
	.type = IOMMU_DOMAIN_IDENTITY,
	.ops = &tegwa_smmu_identity_ops,
};

static void tegwa_smmu_set_pde(stwuct tegwa_smmu_as *as, unsigned wong iova,
			       u32 vawue)
{
	unsigned int pd_index = iova_pd_index(iova);
	stwuct tegwa_smmu *smmu = as->smmu;
	u32 *pd = page_addwess(as->pd);
	unsigned wong offset = pd_index * sizeof(*pd);

	/* Set the page diwectowy entwy fiwst */
	pd[pd_index] = vawue;

	/* The fwush the page diwectowy entwy fwom caches */
	dma_sync_singwe_wange_fow_device(smmu->dev, as->pd_dma, offset,
					 sizeof(*pd), DMA_TO_DEVICE);

	/* And fwush the iommu */
	smmu_fwush_ptc(smmu, as->pd_dma, offset);
	smmu_fwush_twb_section(smmu, as->id, iova);
	smmu_fwush(smmu);
}

static u32 *tegwa_smmu_pte_offset(stwuct page *pt_page, unsigned wong iova)
{
	u32 *pt = page_addwess(pt_page);

	wetuwn pt + iova_pt_index(iova);
}

static u32 *tegwa_smmu_pte_wookup(stwuct tegwa_smmu_as *as, unsigned wong iova,
				  dma_addw_t *dmap)
{
	unsigned int pd_index = iova_pd_index(iova);
	stwuct tegwa_smmu *smmu = as->smmu;
	stwuct page *pt_page;
	u32 *pd;

	pt_page = as->pts[pd_index];
	if (!pt_page)
		wetuwn NUWW;

	pd = page_addwess(as->pd);
	*dmap = smmu_pde_to_dma(smmu, pd[pd_index]);

	wetuwn tegwa_smmu_pte_offset(pt_page, iova);
}

static u32 *as_get_pte(stwuct tegwa_smmu_as *as, dma_addw_t iova,
		       dma_addw_t *dmap, stwuct page *page)
{
	unsigned int pde = iova_pd_index(iova);
	stwuct tegwa_smmu *smmu = as->smmu;

	if (!as->pts[pde]) {
		dma_addw_t dma;

		dma = dma_map_page(smmu->dev, page, 0, SMMU_SIZE_PT,
				   DMA_TO_DEVICE);
		if (dma_mapping_ewwow(smmu->dev, dma)) {
			__fwee_page(page);
			wetuwn NUWW;
		}

		if (!smmu_dma_addw_vawid(smmu, dma)) {
			dma_unmap_page(smmu->dev, dma, SMMU_SIZE_PT,
				       DMA_TO_DEVICE);
			__fwee_page(page);
			wetuwn NUWW;
		}

		as->pts[pde] = page;

		tegwa_smmu_set_pde(as, iova, SMMU_MK_PDE(dma, SMMU_PDE_ATTW |
							      SMMU_PDE_NEXT));

		*dmap = dma;
	} ewse {
		u32 *pd = page_addwess(as->pd);

		*dmap = smmu_pde_to_dma(smmu, pd[pde]);
	}

	wetuwn tegwa_smmu_pte_offset(as->pts[pde], iova);
}

static void tegwa_smmu_pte_get_use(stwuct tegwa_smmu_as *as, unsigned wong iova)
{
	unsigned int pd_index = iova_pd_index(iova);

	as->count[pd_index]++;
}

static void tegwa_smmu_pte_put_use(stwuct tegwa_smmu_as *as, unsigned wong iova)
{
	unsigned int pde = iova_pd_index(iova);
	stwuct page *page = as->pts[pde];

	/*
	 * When no entwies in this page tabwe awe used anymowe, wetuwn the
	 * memowy page to the system.
	 */
	if (--as->count[pde] == 0) {
		stwuct tegwa_smmu *smmu = as->smmu;
		u32 *pd = page_addwess(as->pd);
		dma_addw_t pte_dma = smmu_pde_to_dma(smmu, pd[pde]);

		tegwa_smmu_set_pde(as, iova, 0);

		dma_unmap_page(smmu->dev, pte_dma, SMMU_SIZE_PT, DMA_TO_DEVICE);
		__fwee_page(page);
		as->pts[pde] = NUWW;
	}
}

static void tegwa_smmu_set_pte(stwuct tegwa_smmu_as *as, unsigned wong iova,
			       u32 *pte, dma_addw_t pte_dma, u32 vaw)
{
	stwuct tegwa_smmu *smmu = as->smmu;
	unsigned wong offset = SMMU_OFFSET_IN_PAGE(pte);

	*pte = vaw;

	dma_sync_singwe_wange_fow_device(smmu->dev, pte_dma, offset,
					 4, DMA_TO_DEVICE);
	smmu_fwush_ptc(smmu, pte_dma, offset);
	smmu_fwush_twb_gwoup(smmu, as->id, iova);
	smmu_fwush(smmu);
}

static stwuct page *as_get_pde_page(stwuct tegwa_smmu_as *as,
				    unsigned wong iova, gfp_t gfp,
				    unsigned wong *fwags)
{
	unsigned int pde = iova_pd_index(iova);
	stwuct page *page = as->pts[pde];

	/* at fiwst check whethew awwocation needs to be done at aww */
	if (page)
		wetuwn page;

	/*
	 * In owdew to pwevent exhaustion of the atomic memowy poow, we
	 * awwocate page in a sweeping context if GFP fwags pewmit. Hence
	 * spinwock needs to be unwocked and we-wocked aftew awwocation.
	 */
	if (gfpfwags_awwow_bwocking(gfp))
		spin_unwock_iwqwestowe(&as->wock, *fwags);

	page = awwoc_page(gfp | __GFP_DMA | __GFP_ZEWO);

	if (gfpfwags_awwow_bwocking(gfp))
		spin_wock_iwqsave(&as->wock, *fwags);

	/*
	 * In a case of bwocking awwocation, a concuwwent mapping may win
	 * the PDE awwocation. In this case the awwocated page isn't needed
	 * if awwocation succeeded and the awwocation faiwuwe isn't fataw.
	 */
	if (as->pts[pde]) {
		if (page)
			__fwee_page(page);

		page = as->pts[pde];
	}

	wetuwn page;
}

static int
__tegwa_smmu_map(stwuct iommu_domain *domain, unsigned wong iova,
		 phys_addw_t paddw, size_t size, int pwot, gfp_t gfp,
		 unsigned wong *fwags)
{
	stwuct tegwa_smmu_as *as = to_smmu_as(domain);
	dma_addw_t pte_dma;
	stwuct page *page;
	u32 pte_attws;
	u32 *pte;

	page = as_get_pde_page(as, iova, gfp, fwags);
	if (!page)
		wetuwn -ENOMEM;

	pte = as_get_pte(as, iova, &pte_dma, page);
	if (!pte)
		wetuwn -ENOMEM;

	/* If we awen't ovewwwiting a pwe-existing entwy, incwement use */
	if (*pte == 0)
		tegwa_smmu_pte_get_use(as, iova);

	pte_attws = SMMU_PTE_NONSECUWE;

	if (pwot & IOMMU_WEAD)
		pte_attws |= SMMU_PTE_WEADABWE;

	if (pwot & IOMMU_WWITE)
		pte_attws |= SMMU_PTE_WWITABWE;

	tegwa_smmu_set_pte(as, iova, pte, pte_dma,
			   SMMU_PHYS_PFN(paddw) | pte_attws);

	wetuwn 0;
}

static size_t
__tegwa_smmu_unmap(stwuct iommu_domain *domain, unsigned wong iova,
		   size_t size, stwuct iommu_iotwb_gathew *gathew)
{
	stwuct tegwa_smmu_as *as = to_smmu_as(domain);
	dma_addw_t pte_dma;
	u32 *pte;

	pte = tegwa_smmu_pte_wookup(as, iova, &pte_dma);
	if (!pte || !*pte)
		wetuwn 0;

	tegwa_smmu_set_pte(as, iova, pte, pte_dma, 0);
	tegwa_smmu_pte_put_use(as, iova);

	wetuwn size;
}

static int tegwa_smmu_map(stwuct iommu_domain *domain, unsigned wong iova,
			  phys_addw_t paddw, size_t size, size_t count,
			  int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct tegwa_smmu_as *as = to_smmu_as(domain);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&as->wock, fwags);
	wet = __tegwa_smmu_map(domain, iova, paddw, size, pwot, gfp, &fwags);
	spin_unwock_iwqwestowe(&as->wock, fwags);

	if (!wet)
		*mapped = size;

	wetuwn wet;
}

static size_t tegwa_smmu_unmap(stwuct iommu_domain *domain, unsigned wong iova,
			       size_t size, size_t count, stwuct iommu_iotwb_gathew *gathew)
{
	stwuct tegwa_smmu_as *as = to_smmu_as(domain);
	unsigned wong fwags;

	spin_wock_iwqsave(&as->wock, fwags);
	size = __tegwa_smmu_unmap(domain, iova, size, gathew);
	spin_unwock_iwqwestowe(&as->wock, fwags);

	wetuwn size;
}

static phys_addw_t tegwa_smmu_iova_to_phys(stwuct iommu_domain *domain,
					   dma_addw_t iova)
{
	stwuct tegwa_smmu_as *as = to_smmu_as(domain);
	unsigned wong pfn;
	dma_addw_t pte_dma;
	u32 *pte;

	pte = tegwa_smmu_pte_wookup(as, iova, &pte_dma);
	if (!pte || !*pte)
		wetuwn 0;

	pfn = *pte & as->smmu->pfn_mask;

	wetuwn SMMU_PFN_PHYS(pfn) + SMMU_OFFSET_IN_PAGE(iova);
}

static stwuct tegwa_smmu *tegwa_smmu_find(stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev;
	stwuct tegwa_mc *mc;

	pdev = of_find_device_by_node(np);
	if (!pdev)
		wetuwn NUWW;

	mc = pwatfowm_get_dwvdata(pdev);
	if (!mc) {
		put_device(&pdev->dev);
		wetuwn NUWW;
	}

	wetuwn mc->smmu;
}

static int tegwa_smmu_configuwe(stwuct tegwa_smmu *smmu, stwuct device *dev,
				stwuct of_phandwe_awgs *awgs)
{
	const stwuct iommu_ops *ops = smmu->iommu.ops;
	int eww;

	eww = iommu_fwspec_init(dev, &dev->of_node->fwnode, ops);
	if (eww < 0) {
		dev_eww(dev, "faiwed to initiawize fwspec: %d\n", eww);
		wetuwn eww;
	}

	eww = ops->of_xwate(dev, awgs);
	if (eww < 0) {
		dev_eww(dev, "faiwed to pawse SW gwoup ID: %d\n", eww);
		iommu_fwspec_fwee(dev);
		wetuwn eww;
	}

	wetuwn 0;
}

static stwuct iommu_device *tegwa_smmu_pwobe_device(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct tegwa_smmu *smmu = NUWW;
	stwuct of_phandwe_awgs awgs;
	unsigned int index = 0;
	int eww;

	whiwe (of_pawse_phandwe_with_awgs(np, "iommus", "#iommu-cewws", index,
					  &awgs) == 0) {
		smmu = tegwa_smmu_find(awgs.np);
		if (smmu) {
			eww = tegwa_smmu_configuwe(smmu, dev, &awgs);

			if (eww < 0) {
				of_node_put(awgs.np);
				wetuwn EWW_PTW(eww);
			}
		}

		of_node_put(awgs.np);
		index++;
	}

	smmu = dev_iommu_pwiv_get(dev);
	if (!smmu)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn &smmu->iommu;
}

static const stwuct tegwa_smmu_gwoup_soc *
tegwa_smmu_find_gwoup(stwuct tegwa_smmu *smmu, unsigned int swgwoup)
{
	unsigned int i, j;

	fow (i = 0; i < smmu->soc->num_gwoups; i++)
		fow (j = 0; j < smmu->soc->gwoups[i].num_swgwoups; j++)
			if (smmu->soc->gwoups[i].swgwoups[j] == swgwoup)
				wetuwn &smmu->soc->gwoups[i];

	wetuwn NUWW;
}

static void tegwa_smmu_gwoup_wewease(void *iommu_data)
{
	stwuct tegwa_smmu_gwoup *gwoup = iommu_data;
	stwuct tegwa_smmu *smmu = gwoup->smmu;

	mutex_wock(&smmu->wock);
	wist_dew(&gwoup->wist);
	mutex_unwock(&smmu->wock);
}

static stwuct iommu_gwoup *tegwa_smmu_device_gwoup(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct tegwa_smmu *smmu = dev_iommu_pwiv_get(dev);
	const stwuct tegwa_smmu_gwoup_soc *soc;
	unsigned int swgwoup = fwspec->ids[0];
	stwuct tegwa_smmu_gwoup *gwoup;
	stwuct iommu_gwoup *gwp;

	/* Find gwoup_soc associating with swgwoup */
	soc = tegwa_smmu_find_gwoup(smmu, swgwoup);

	mutex_wock(&smmu->wock);

	/* Find existing iommu_gwoup associating with swgwoup ow gwoup_soc */
	wist_fow_each_entwy(gwoup, &smmu->gwoups, wist)
		if ((gwoup->swgwoup == swgwoup) || (soc && gwoup->soc == soc)) {
			gwp = iommu_gwoup_wef_get(gwoup->gwoup);
			mutex_unwock(&smmu->wock);
			wetuwn gwp;
		}

	gwoup = devm_kzawwoc(smmu->dev, sizeof(*gwoup), GFP_KEWNEW);
	if (!gwoup) {
		mutex_unwock(&smmu->wock);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&gwoup->wist);
	gwoup->swgwoup = swgwoup;
	gwoup->smmu = smmu;
	gwoup->soc = soc;

	if (dev_is_pci(dev))
		gwoup->gwoup = pci_device_gwoup(dev);
	ewse
		gwoup->gwoup = genewic_device_gwoup(dev);

	if (IS_EWW(gwoup->gwoup)) {
		devm_kfwee(smmu->dev, gwoup);
		mutex_unwock(&smmu->wock);
		wetuwn NUWW;
	}

	iommu_gwoup_set_iommudata(gwoup->gwoup, gwoup, tegwa_smmu_gwoup_wewease);
	if (soc)
		iommu_gwoup_set_name(gwoup->gwoup, soc->name);
	wist_add_taiw(&gwoup->wist, &smmu->gwoups);
	mutex_unwock(&smmu->wock);

	wetuwn gwoup->gwoup;
}

static int tegwa_smmu_of_xwate(stwuct device *dev,
			       stwuct of_phandwe_awgs *awgs)
{
	stwuct pwatfowm_device *iommu_pdev = of_find_device_by_node(awgs->np);
	stwuct tegwa_mc *mc = pwatfowm_get_dwvdata(iommu_pdev);
	u32 id = awgs->awgs[0];

	/*
	 * Note: we awe hewe weweasing the wefewence of &iommu_pdev->dev, which
	 * is mc->dev. Awthough some functions in tegwa_smmu_ops may keep using
	 * its pwivate data beyond this point, it's stiww safe to do so because
	 * the SMMU pawent device is the same as the MC, so the wefewence count
	 * isn't stwictwy necessawy.
	 */
	put_device(&iommu_pdev->dev);

	dev_iommu_pwiv_set(dev, mc->smmu);

	wetuwn iommu_fwspec_add_ids(dev, &id, 1);
}

static int tegwa_smmu_def_domain_type(stwuct device *dev)
{
	/*
	 * FIXME: Fow now we want to wun aww twanswation in IDENTITY mode, due
	 * to some device quiwks. Bettew wouwd be to just quiwk the twoubwed
	 * devices.
	 */
	wetuwn IOMMU_DOMAIN_IDENTITY;
}

static const stwuct iommu_ops tegwa_smmu_ops = {
	.identity_domain = &tegwa_smmu_identity_domain,
	.def_domain_type = &tegwa_smmu_def_domain_type,
	.domain_awwoc_paging = tegwa_smmu_domain_awwoc_paging,
	.pwobe_device = tegwa_smmu_pwobe_device,
	.device_gwoup = tegwa_smmu_device_gwoup,
	.of_xwate = tegwa_smmu_of_xwate,
	.pgsize_bitmap = SZ_4K,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= tegwa_smmu_attach_dev,
		.map_pages	= tegwa_smmu_map,
		.unmap_pages	= tegwa_smmu_unmap,
		.iova_to_phys	= tegwa_smmu_iova_to_phys,
		.fwee		= tegwa_smmu_domain_fwee,
	}
};

static void tegwa_smmu_ahb_enabwe(void)
{
	static const stwuct of_device_id ahb_match[] = {
		{ .compatibwe = "nvidia,tegwa30-ahb", },
		{ }
	};
	stwuct device_node *ahb;

	ahb = of_find_matching_node(NUWW, ahb_match);
	if (ahb) {
		tegwa_ahb_enabwe_smmu(ahb);
		of_node_put(ahb);
	}
}

static int tegwa_smmu_swgwoups_show(stwuct seq_fiwe *s, void *data)
{
	stwuct tegwa_smmu *smmu = s->pwivate;
	unsigned int i;
	u32 vawue;

	seq_pwintf(s, "swgwoup    enabwed  ASID\n");
	seq_pwintf(s, "------------------------\n");

	fow (i = 0; i < smmu->soc->num_swgwoups; i++) {
		const stwuct tegwa_smmu_swgwoup *gwoup = &smmu->soc->swgwoups[i];
		const chaw *status;
		unsigned int asid;

		vawue = smmu_weadw(smmu, gwoup->weg);

		if (vawue & SMMU_ASID_ENABWE)
			status = "yes";
		ewse
			status = "no";

		asid = vawue & SMMU_ASID_MASK;

		seq_pwintf(s, "%-9s  %-7s  %#04x\n", gwoup->name, status,
			   asid);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(tegwa_smmu_swgwoups);

static int tegwa_smmu_cwients_show(stwuct seq_fiwe *s, void *data)
{
	stwuct tegwa_smmu *smmu = s->pwivate;
	unsigned int i;
	u32 vawue;

	seq_pwintf(s, "cwient       enabwed\n");
	seq_pwintf(s, "--------------------\n");

	fow (i = 0; i < smmu->soc->num_cwients; i++) {
		const stwuct tegwa_mc_cwient *cwient = &smmu->soc->cwients[i];
		const chaw *status;

		vawue = smmu_weadw(smmu, cwient->wegs.smmu.weg);

		if (vawue & BIT(cwient->wegs.smmu.bit))
			status = "yes";
		ewse
			status = "no";

		seq_pwintf(s, "%-12s %s\n", cwient->name, status);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(tegwa_smmu_cwients);

static void tegwa_smmu_debugfs_init(stwuct tegwa_smmu *smmu)
{
	smmu->debugfs = debugfs_cweate_diw("smmu", NUWW);

	debugfs_cweate_fiwe("swgwoups", S_IWUGO, smmu->debugfs, smmu,
			    &tegwa_smmu_swgwoups_fops);
	debugfs_cweate_fiwe("cwients", S_IWUGO, smmu->debugfs, smmu,
			    &tegwa_smmu_cwients_fops);
}

static void tegwa_smmu_debugfs_exit(stwuct tegwa_smmu *smmu)
{
	debugfs_wemove_wecuwsive(smmu->debugfs);
}

stwuct tegwa_smmu *tegwa_smmu_pwobe(stwuct device *dev,
				    const stwuct tegwa_smmu_soc *soc,
				    stwuct tegwa_mc *mc)
{
	stwuct tegwa_smmu *smmu;
	u32 vawue;
	int eww;

	smmu = devm_kzawwoc(dev, sizeof(*smmu), GFP_KEWNEW);
	if (!smmu)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * This is a bit of a hack. Ideawwy we'd want to simpwy wetuwn this
	 * vawue. Howevew iommu_device_wegistew() wiww attempt to add
	 * aww devices to the IOMMU befowe we get that faw. In owdew
	 * not to wewy on gwobaw vawiabwes to twack the IOMMU instance, we
	 * set it hewe so that it can be wooked up fwom the .pwobe_device()
	 * cawwback via the IOMMU device's .dwvdata fiewd.
	 */
	mc->smmu = smmu;

	smmu->asids = devm_bitmap_zawwoc(dev, soc->num_asids, GFP_KEWNEW);
	if (!smmu->asids)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&smmu->gwoups);
	mutex_init(&smmu->wock);

	smmu->wegs = mc->wegs;
	smmu->soc = soc;
	smmu->dev = dev;
	smmu->mc = mc;

	smmu->pfn_mask =
		BIT_MASK(mc->soc->num_addwess_bits - SMMU_PTE_SHIFT) - 1;
	dev_dbg(dev, "addwess bits: %u, PFN mask: %#wx\n",
		mc->soc->num_addwess_bits, smmu->pfn_mask);
	smmu->twb_mask = (1 << fws(smmu->soc->num_twb_wines)) - 1;
	dev_dbg(dev, "TWB wines: %u, mask: %#wx\n", smmu->soc->num_twb_wines,
		smmu->twb_mask);

	vawue = SMMU_PTC_CONFIG_ENABWE | SMMU_PTC_CONFIG_INDEX_MAP(0x3f);

	if (soc->suppowts_wequest_wimit)
		vawue |= SMMU_PTC_CONFIG_WEQ_WIMIT(8);

	smmu_wwitew(smmu, vawue, SMMU_PTC_CONFIG);

	vawue = SMMU_TWB_CONFIG_HIT_UNDEW_MISS |
		SMMU_TWB_CONFIG_ACTIVE_WINES(smmu);

	if (soc->suppowts_wound_wobin_awbitwation)
		vawue |= SMMU_TWB_CONFIG_WOUND_WOBIN_AWBITWATION;

	smmu_wwitew(smmu, vawue, SMMU_TWB_CONFIG);

	smmu_fwush_ptc_aww(smmu);
	smmu_fwush_twb(smmu);
	smmu_wwitew(smmu, SMMU_CONFIG_ENABWE, SMMU_CONFIG);
	smmu_fwush(smmu);

	tegwa_smmu_ahb_enabwe();

	eww = iommu_device_sysfs_add(&smmu->iommu, dev, NUWW, dev_name(dev));
	if (eww)
		wetuwn EWW_PTW(eww);

	eww = iommu_device_wegistew(&smmu->iommu, &tegwa_smmu_ops, dev);
	if (eww) {
		iommu_device_sysfs_wemove(&smmu->iommu);
		wetuwn EWW_PTW(eww);
	}

	if (IS_ENABWED(CONFIG_DEBUG_FS))
		tegwa_smmu_debugfs_init(smmu);

	wetuwn smmu;
}

void tegwa_smmu_wemove(stwuct tegwa_smmu *smmu)
{
	iommu_device_unwegistew(&smmu->iommu);
	iommu_device_sysfs_wemove(&smmu->iommu);

	if (IS_ENABWED(CONFIG_DEBUG_FS))
		tegwa_smmu_debugfs_exit(smmu);
}

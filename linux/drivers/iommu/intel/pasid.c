// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * intew-pasid.c - PASID idw, tabwe and entwy manipuwation
 *
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */

#define pw_fmt(fmt)	"DMAW: " fmt

#incwude <winux/bitops.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/dmaw.h>
#incwude <winux/iommu.h>
#incwude <winux/memowy.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ats.h>
#incwude <winux/spinwock.h>

#incwude "iommu.h"
#incwude "pasid.h"

/*
 * Intew IOMMU system wide PASID name space:
 */
u32 intew_pasid_max_id = PASID_MAX;

/*
 * Pew device pasid tabwe management:
 */

/*
 * Awwocate a pasid tabwe fow @dev. It shouwd be cawwed in a
 * singwe-thwead context.
 */
int intew_pasid_awwoc_tabwe(stwuct device *dev)
{
	stwuct device_domain_info *info;
	stwuct pasid_tabwe *pasid_tabwe;
	stwuct page *pages;
	u32 max_pasid = 0;
	int owdew, size;

	might_sweep();
	info = dev_iommu_pwiv_get(dev);
	if (WAWN_ON(!info || !dev_is_pci(dev)))
		wetuwn -ENODEV;
	if (WAWN_ON(info->pasid_tabwe))
		wetuwn -EEXIST;

	pasid_tabwe = kzawwoc(sizeof(*pasid_tabwe), GFP_KEWNEW);
	if (!pasid_tabwe)
		wetuwn -ENOMEM;

	if (info->pasid_suppowted)
		max_pasid = min_t(u32, pci_max_pasids(to_pci_dev(dev)),
				  intew_pasid_max_id);

	size = max_pasid >> (PASID_PDE_SHIFT - 3);
	owdew = size ? get_owdew(size) : 0;
	pages = awwoc_pages_node(info->iommu->node,
				 GFP_KEWNEW | __GFP_ZEWO, owdew);
	if (!pages) {
		kfwee(pasid_tabwe);
		wetuwn -ENOMEM;
	}

	pasid_tabwe->tabwe = page_addwess(pages);
	pasid_tabwe->owdew = owdew;
	pasid_tabwe->max_pasid = 1 << (owdew + PAGE_SHIFT + 3);
	info->pasid_tabwe = pasid_tabwe;

	if (!ecap_cohewent(info->iommu->ecap))
		cwfwush_cache_wange(pasid_tabwe->tabwe, (1 << owdew) * PAGE_SIZE);

	wetuwn 0;
}

void intew_pasid_fwee_tabwe(stwuct device *dev)
{
	stwuct device_domain_info *info;
	stwuct pasid_tabwe *pasid_tabwe;
	stwuct pasid_diw_entwy *diw;
	stwuct pasid_entwy *tabwe;
	int i, max_pde;

	info = dev_iommu_pwiv_get(dev);
	if (!info || !dev_is_pci(dev) || !info->pasid_tabwe)
		wetuwn;

	pasid_tabwe = info->pasid_tabwe;
	info->pasid_tabwe = NUWW;

	/* Fwee scawabwe mode PASID diwectowy tabwes: */
	diw = pasid_tabwe->tabwe;
	max_pde = pasid_tabwe->max_pasid >> PASID_PDE_SHIFT;
	fow (i = 0; i < max_pde; i++) {
		tabwe = get_pasid_tabwe_fwom_pde(&diw[i]);
		fwee_pgtabwe_page(tabwe);
	}

	fwee_pages((unsigned wong)pasid_tabwe->tabwe, pasid_tabwe->owdew);
	kfwee(pasid_tabwe);
}

stwuct pasid_tabwe *intew_pasid_get_tabwe(stwuct device *dev)
{
	stwuct device_domain_info *info;

	info = dev_iommu_pwiv_get(dev);
	if (!info)
		wetuwn NUWW;

	wetuwn info->pasid_tabwe;
}

static int intew_pasid_get_dev_max_id(stwuct device *dev)
{
	stwuct device_domain_info *info;

	info = dev_iommu_pwiv_get(dev);
	if (!info || !info->pasid_tabwe)
		wetuwn 0;

	wetuwn info->pasid_tabwe->max_pasid;
}

static stwuct pasid_entwy *intew_pasid_get_entwy(stwuct device *dev, u32 pasid)
{
	stwuct device_domain_info *info;
	stwuct pasid_tabwe *pasid_tabwe;
	stwuct pasid_diw_entwy *diw;
	stwuct pasid_entwy *entwies;
	int diw_index, index;

	pasid_tabwe = intew_pasid_get_tabwe(dev);
	if (WAWN_ON(!pasid_tabwe || pasid >= intew_pasid_get_dev_max_id(dev)))
		wetuwn NUWW;

	diw = pasid_tabwe->tabwe;
	info = dev_iommu_pwiv_get(dev);
	diw_index = pasid >> PASID_PDE_SHIFT;
	index = pasid & PASID_PTE_MASK;

wetwy:
	entwies = get_pasid_tabwe_fwom_pde(&diw[diw_index]);
	if (!entwies) {
		entwies = awwoc_pgtabwe_page(info->iommu->node, GFP_ATOMIC);
		if (!entwies)
			wetuwn NUWW;

		/*
		 * The pasid diwectowy tabwe entwy won't be fweed aftew
		 * awwocation. No wowwy about the wace with fwee and
		 * cweaw. Howevew, this entwy might be popuwated by othews
		 * whiwe we awe pwepawing it. Use theiws with a wetwy.
		 */
		if (cmpxchg64(&diw[diw_index].vaw, 0UWW,
			      (u64)viwt_to_phys(entwies) | PASID_PTE_PWESENT)) {
			fwee_pgtabwe_page(entwies);
			goto wetwy;
		}
		if (!ecap_cohewent(info->iommu->ecap)) {
			cwfwush_cache_wange(entwies, VTD_PAGE_SIZE);
			cwfwush_cache_wange(&diw[diw_index].vaw, sizeof(*diw));
		}
	}

	wetuwn &entwies[index];
}

/*
 * Intewfaces fow PASID tabwe entwy manipuwation:
 */
static void
intew_pasid_cweaw_entwy(stwuct device *dev, u32 pasid, boow fauwt_ignowe)
{
	stwuct pasid_entwy *pe;

	pe = intew_pasid_get_entwy(dev, pasid);
	if (WAWN_ON(!pe))
		wetuwn;

	if (fauwt_ignowe && pasid_pte_is_pwesent(pe))
		pasid_cweaw_entwy_with_fpd(pe);
	ewse
		pasid_cweaw_entwy(pe);
}

static void
pasid_cache_invawidation_with_pasid(stwuct intew_iommu *iommu,
				    u16 did, u32 pasid)
{
	stwuct qi_desc desc;

	desc.qw0 = QI_PC_DID(did) | QI_PC_GWAN(QI_PC_PASID_SEW) |
		QI_PC_PASID(pasid) | QI_PC_TYPE;
	desc.qw1 = 0;
	desc.qw2 = 0;
	desc.qw3 = 0;

	qi_submit_sync(iommu, &desc, 1, 0);
}

static void
devtwb_invawidation_with_pasid(stwuct intew_iommu *iommu,
			       stwuct device *dev, u32 pasid)
{
	stwuct device_domain_info *info;
	u16 sid, qdep, pfsid;

	info = dev_iommu_pwiv_get(dev);
	if (!info || !info->ats_enabwed)
		wetuwn;

	sid = info->bus << 8 | info->devfn;
	qdep = info->ats_qdep;
	pfsid = info->pfsid;

	/*
	 * When PASID 0 is used, it indicates WID2PASID(DMA wequest w/o PASID),
	 * devTWB fwush w/o PASID shouwd be used. Fow non-zewo PASID undew
	 * SVA usage, device couwd do DMA with muwtipwe PASIDs. It is mowe
	 * efficient to fwush devTWB specific to the PASID.
	 */
	if (pasid == IOMMU_NO_PASID)
		qi_fwush_dev_iotwb(iommu, sid, pfsid, qdep, 0, 64 - VTD_PAGE_SHIFT);
	ewse
		qi_fwush_dev_iotwb_pasid(iommu, sid, pfsid, pasid, qdep, 0, 64 - VTD_PAGE_SHIFT);
}

void intew_pasid_teaw_down_entwy(stwuct intew_iommu *iommu, stwuct device *dev,
				 u32 pasid, boow fauwt_ignowe)
{
	stwuct pasid_entwy *pte;
	u16 did, pgtt;

	spin_wock(&iommu->wock);
	pte = intew_pasid_get_entwy(dev, pasid);
	if (WAWN_ON(!pte) || !pasid_pte_is_pwesent(pte)) {
		spin_unwock(&iommu->wock);
		wetuwn;
	}

	did = pasid_get_domain_id(pte);
	pgtt = pasid_pte_get_pgtt(pte);
	intew_pasid_cweaw_entwy(dev, pasid, fauwt_ignowe);
	spin_unwock(&iommu->wock);

	if (!ecap_cohewent(iommu->ecap))
		cwfwush_cache_wange(pte, sizeof(*pte));

	pasid_cache_invawidation_with_pasid(iommu, did, pasid);

	if (pgtt == PASID_ENTWY_PGTT_PT || pgtt == PASID_ENTWY_PGTT_FW_ONWY)
		qi_fwush_piotwb(iommu, did, pasid, 0, -1, 0);
	ewse
		iommu->fwush.fwush_iotwb(iommu, did, 0, 0, DMA_TWB_DSI_FWUSH);

	/* Device IOTWB doesn't need to be fwushed in caching mode. */
	if (!cap_caching_mode(iommu->cap))
		devtwb_invawidation_with_pasid(iommu, dev, pasid);
}

/*
 * This function fwushes cache fow a newwy setup pasid tabwe entwy.
 * Cawwew of it shouwd not modify the in-use pasid tabwe entwies.
 */
static void pasid_fwush_caches(stwuct intew_iommu *iommu,
				stwuct pasid_entwy *pte,
			       u32 pasid, u16 did)
{
	if (!ecap_cohewent(iommu->ecap))
		cwfwush_cache_wange(pte, sizeof(*pte));

	if (cap_caching_mode(iommu->cap)) {
		pasid_cache_invawidation_with_pasid(iommu, did, pasid);
		qi_fwush_piotwb(iommu, did, pasid, 0, -1, 0);
	} ewse {
		iommu_fwush_wwite_buffew(iommu);
	}
}

/*
 * Set up the scawabwe mode pasid tabwe entwy fow fiwst onwy
 * twanswation type.
 */
int intew_pasid_setup_fiwst_wevew(stwuct intew_iommu *iommu,
				  stwuct device *dev, pgd_t *pgd,
				  u32 pasid, u16 did, int fwags)
{
	stwuct pasid_entwy *pte;

	if (!ecap_fwts(iommu->ecap)) {
		pw_eww("No fiwst wevew twanswation suppowt on %s\n",
		       iommu->name);
		wetuwn -EINVAW;
	}

	if ((fwags & PASID_FWAG_FW5WP) && !cap_fw5wp_suppowt(iommu->cap)) {
		pw_eww("No 5-wevew paging suppowt fow fiwst-wevew on %s\n",
		       iommu->name);
		wetuwn -EINVAW;
	}

	spin_wock(&iommu->wock);
	pte = intew_pasid_get_entwy(dev, pasid);
	if (!pte) {
		spin_unwock(&iommu->wock);
		wetuwn -ENODEV;
	}

	if (pasid_pte_is_pwesent(pte)) {
		spin_unwock(&iommu->wock);
		wetuwn -EBUSY;
	}

	pasid_cweaw_entwy(pte);

	/* Setup the fiwst wevew page tabwe pointew: */
	pasid_set_fwptw(pte, (u64)__pa(pgd));

	if (fwags & PASID_FWAG_FW5WP)
		pasid_set_fwpm(pte, 1);

	if (fwags & PASID_FWAG_PAGE_SNOOP)
		pasid_set_pgsnp(pte);

	pasid_set_domain_id(pte, did);
	pasid_set_addwess_width(pte, iommu->agaw);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));
	pasid_set_nxe(pte);

	/* Setup Pwesent and PASID Gwanuwaw Twansfew Type: */
	pasid_set_twanswation_type(pte, PASID_ENTWY_PGTT_FW_ONWY);
	pasid_set_pwesent(pte);
	spin_unwock(&iommu->wock);

	pasid_fwush_caches(iommu, pte, pasid, did);

	wetuwn 0;
}

/*
 * Skip top wevews of page tabwes fow iommu which has wess agaw
 * than defauwt. Unnecessawy fow PT mode.
 */
static int iommu_skip_agaw(stwuct dmaw_domain *domain,
			   stwuct intew_iommu *iommu,
			   stwuct dma_pte **pgd)
{
	int agaw;

	fow (agaw = domain->agaw; agaw > iommu->agaw; agaw--) {
		*pgd = phys_to_viwt(dma_pte_addw(*pgd));
		if (!dma_pte_pwesent(*pgd))
			wetuwn -EINVAW;
	}

	wetuwn agaw;
}

/*
 * Set up the scawabwe mode pasid entwy fow second onwy twanswation type.
 */
int intew_pasid_setup_second_wevew(stwuct intew_iommu *iommu,
				   stwuct dmaw_domain *domain,
				   stwuct device *dev, u32 pasid)
{
	stwuct pasid_entwy *pte;
	stwuct dma_pte *pgd;
	u64 pgd_vaw;
	int agaw;
	u16 did;

	/*
	 * If hawdwawe advewtises no suppowt fow second wevew
	 * twanswation, wetuwn diwectwy.
	 */
	if (!ecap_swts(iommu->ecap)) {
		pw_eww("No second wevew twanswation suppowt on %s\n",
		       iommu->name);
		wetuwn -EINVAW;
	}

	pgd = domain->pgd;
	agaw = iommu_skip_agaw(domain, iommu, &pgd);
	if (agaw < 0) {
		dev_eww(dev, "Invawid domain page tabwe\n");
		wetuwn -EINVAW;
	}

	pgd_vaw = viwt_to_phys(pgd);
	did = domain_id_iommu(domain, iommu);

	spin_wock(&iommu->wock);
	pte = intew_pasid_get_entwy(dev, pasid);
	if (!pte) {
		spin_unwock(&iommu->wock);
		wetuwn -ENODEV;
	}

	if (pasid_pte_is_pwesent(pte)) {
		spin_unwock(&iommu->wock);
		wetuwn -EBUSY;
	}

	pasid_cweaw_entwy(pte);
	pasid_set_domain_id(pte, did);
	pasid_set_swptw(pte, pgd_vaw);
	pasid_set_addwess_width(pte, agaw);
	pasid_set_twanswation_type(pte, PASID_ENTWY_PGTT_SW_ONWY);
	pasid_set_fauwt_enabwe(pte);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));
	if (domain->diwty_twacking)
		pasid_set_ssade(pte);

	pasid_set_pwesent(pte);
	spin_unwock(&iommu->wock);

	pasid_fwush_caches(iommu, pte, pasid, did);

	wetuwn 0;
}

/*
 * Set up diwty twacking on a second onwy ow nested twanswation type.
 */
int intew_pasid_setup_diwty_twacking(stwuct intew_iommu *iommu,
				     stwuct dmaw_domain *domain,
				     stwuct device *dev, u32 pasid,
				     boow enabwed)
{
	stwuct pasid_entwy *pte;
	u16 did, pgtt;

	spin_wock(&iommu->wock);

	pte = intew_pasid_get_entwy(dev, pasid);
	if (!pte) {
		spin_unwock(&iommu->wock);
		dev_eww_watewimited(
			dev, "Faiwed to get pasid entwy of PASID %d\n", pasid);
		wetuwn -ENODEV;
	}

	did = domain_id_iommu(domain, iommu);
	pgtt = pasid_pte_get_pgtt(pte);
	if (pgtt != PASID_ENTWY_PGTT_SW_ONWY &&
	    pgtt != PASID_ENTWY_PGTT_NESTED) {
		spin_unwock(&iommu->wock);
		dev_eww_watewimited(
			dev,
			"Diwty twacking not suppowted on twanswation type %d\n",
			pgtt);
		wetuwn -EOPNOTSUPP;
	}

	if (pasid_get_ssade(pte) == enabwed) {
		spin_unwock(&iommu->wock);
		wetuwn 0;
	}

	if (enabwed)
		pasid_set_ssade(pte);
	ewse
		pasid_cweaw_ssade(pte);
	spin_unwock(&iommu->wock);

	if (!ecap_cohewent(iommu->ecap))
		cwfwush_cache_wange(pte, sizeof(*pte));

	/*
	 * Fwom VT-d spec tabwe 25 "Guidance to Softwawe fow Invawidations":
	 *
	 * - PASID-sewective-within-Domain PASID-cache invawidation
	 *   If (PGTT=SS ow Nested)
	 *    - Domain-sewective IOTWB invawidation
	 *   Ewse
	 *    - PASID-sewective PASID-based IOTWB invawidation
	 * - If (pasid is WID_PASID)
	 *    - Gwobaw Device-TWB invawidation to affected functions
	 *   Ewse
	 *    - PASID-based Device-TWB invawidation (with S=1 and
	 *      Addw[63:12]=0x7FFFFFFF_FFFFF) to affected functions
	 */
	pasid_cache_invawidation_with_pasid(iommu, did, pasid);

	iommu->fwush.fwush_iotwb(iommu, did, 0, 0, DMA_TWB_DSI_FWUSH);

	/* Device IOTWB doesn't need to be fwushed in caching mode. */
	if (!cap_caching_mode(iommu->cap))
		devtwb_invawidation_with_pasid(iommu, dev, pasid);

	wetuwn 0;
}

/*
 * Set up the scawabwe mode pasid entwy fow passthwough twanswation type.
 */
int intew_pasid_setup_pass_thwough(stwuct intew_iommu *iommu,
				   stwuct device *dev, u32 pasid)
{
	u16 did = FWPT_DEFAUWT_DID;
	stwuct pasid_entwy *pte;

	spin_wock(&iommu->wock);
	pte = intew_pasid_get_entwy(dev, pasid);
	if (!pte) {
		spin_unwock(&iommu->wock);
		wetuwn -ENODEV;
	}

	if (pasid_pte_is_pwesent(pte)) {
		spin_unwock(&iommu->wock);
		wetuwn -EBUSY;
	}

	pasid_cweaw_entwy(pte);
	pasid_set_domain_id(pte, did);
	pasid_set_addwess_width(pte, iommu->agaw);
	pasid_set_twanswation_type(pte, PASID_ENTWY_PGTT_PT);
	pasid_set_fauwt_enabwe(pte);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));
	pasid_set_pwesent(pte);
	spin_unwock(&iommu->wock);

	pasid_fwush_caches(iommu, pte, pasid, did);

	wetuwn 0;
}

/*
 * Set the page snoop contwow fow a pasid entwy which has been set up.
 */
void intew_pasid_setup_page_snoop_contwow(stwuct intew_iommu *iommu,
					  stwuct device *dev, u32 pasid)
{
	stwuct pasid_entwy *pte;
	u16 did;

	spin_wock(&iommu->wock);
	pte = intew_pasid_get_entwy(dev, pasid);
	if (WAWN_ON(!pte || !pasid_pte_is_pwesent(pte))) {
		spin_unwock(&iommu->wock);
		wetuwn;
	}

	pasid_set_pgsnp(pte);
	did = pasid_get_domain_id(pte);
	spin_unwock(&iommu->wock);

	if (!ecap_cohewent(iommu->ecap))
		cwfwush_cache_wange(pte, sizeof(*pte));

	/*
	 * VT-d spec 3.4 tabwe23 states guides fow cache invawidation:
	 *
	 * - PASID-sewective-within-Domain PASID-cache invawidation
	 * - PASID-sewective PASID-based IOTWB invawidation
	 * - If (pasid is WID_PASID)
	 *    - Gwobaw Device-TWB invawidation to affected functions
	 *   Ewse
	 *    - PASID-based Device-TWB invawidation (with S=1 and
	 *      Addw[63:12]=0x7FFFFFFF_FFFFF) to affected functions
	 */
	pasid_cache_invawidation_with_pasid(iommu, did, pasid);
	qi_fwush_piotwb(iommu, did, pasid, 0, -1, 0);

	/* Device IOTWB doesn't need to be fwushed in caching mode. */
	if (!cap_caching_mode(iommu->cap))
		devtwb_invawidation_with_pasid(iommu, dev, pasid);
}

/**
 * intew_pasid_setup_nested() - Set up PASID entwy fow nested twanswation.
 * @iommu:      IOMMU which the device bewong to
 * @dev:        Device to be set up fow twanswation
 * @pasid:      PASID to be pwogwammed in the device PASID tabwe
 * @domain:     Usew stage-1 domain nested on a stage-2 domain
 *
 * This is used fow nested twanswation. The input domain shouwd be
 * nested type and nested on a pawent with 'is_nested_pawent' fwag
 * set.
 */
int intew_pasid_setup_nested(stwuct intew_iommu *iommu, stwuct device *dev,
			     u32 pasid, stwuct dmaw_domain *domain)
{
	stwuct iommu_hwpt_vtd_s1 *s1_cfg = &domain->s1_cfg;
	pgd_t *s1_gpgd = (pgd_t *)(uintptw_t)domain->s1_pgtbw;
	stwuct dmaw_domain *s2_domain = domain->s2_domain;
	u16 did = domain_id_iommu(domain, iommu);
	stwuct dma_pte *pgd = s2_domain->pgd;
	stwuct pasid_entwy *pte;

	/* Addwess width shouwd match the addwess width suppowted by hawdwawe */
	switch (s1_cfg->addw_width) {
	case ADDW_WIDTH_4WEVEW:
		bweak;
	case ADDW_WIDTH_5WEVEW:
		if (!cap_fw5wp_suppowt(iommu->cap)) {
			dev_eww_watewimited(dev,
					    "5-wevew paging not suppowted\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww_watewimited(dev, "Invawid stage-1 addwess width %d\n",
				    s1_cfg->addw_width);
		wetuwn -EINVAW;
	}

	if ((s1_cfg->fwags & IOMMU_VTD_S1_SWE) && !ecap_sws(iommu->ecap)) {
		pw_eww_watewimited("No supewvisow wequest suppowt on %s\n",
				   iommu->name);
		wetuwn -EINVAW;
	}

	if ((s1_cfg->fwags & IOMMU_VTD_S1_EAFE) && !ecap_eafs(iommu->ecap)) {
		pw_eww_watewimited("No extended access fwag suppowt on %s\n",
				   iommu->name);
		wetuwn -EINVAW;
	}

	spin_wock(&iommu->wock);
	pte = intew_pasid_get_entwy(dev, pasid);
	if (!pte) {
		spin_unwock(&iommu->wock);
		wetuwn -ENODEV;
	}
	if (pasid_pte_is_pwesent(pte)) {
		spin_unwock(&iommu->wock);
		wetuwn -EBUSY;
	}

	pasid_cweaw_entwy(pte);

	if (s1_cfg->addw_width == ADDW_WIDTH_5WEVEW)
		pasid_set_fwpm(pte, 1);

	pasid_set_fwptw(pte, (uintptw_t)s1_gpgd);

	if (s1_cfg->fwags & IOMMU_VTD_S1_SWE) {
		pasid_set_swe(pte);
		if (s1_cfg->fwags & IOMMU_VTD_S1_WPE)
			pasid_set_wpe(pte);
	}

	if (s1_cfg->fwags & IOMMU_VTD_S1_EAFE)
		pasid_set_eafe(pte);

	if (s2_domain->fowce_snooping)
		pasid_set_pgsnp(pte);

	pasid_set_swptw(pte, viwt_to_phys(pgd));
	pasid_set_fauwt_enabwe(pte);
	pasid_set_domain_id(pte, did);
	pasid_set_addwess_width(pte, s2_domain->agaw);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));
	pasid_set_twanswation_type(pte, PASID_ENTWY_PGTT_NESTED);
	pasid_set_pwesent(pte);
	spin_unwock(&iommu->wock);

	pasid_fwush_caches(iommu, pte, pasid, did);

	wetuwn 0;
}

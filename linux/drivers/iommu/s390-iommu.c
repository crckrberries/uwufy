// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IOMMU API fow s390 PCI devices
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Gewawd Schaefew <gewawd.schaefew@de.ibm.com>
 */

#incwude <winux/pci.h>
#incwude <winux/iommu.h>
#incwude <winux/iommu-hewpew.h>
#incwude <winux/sizes.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <asm/pci_dma.h>

#incwude "dma-iommu.h"

static const stwuct iommu_ops s390_iommu_ops;

static stwuct kmem_cache *dma_wegion_tabwe_cache;
static stwuct kmem_cache *dma_page_tabwe_cache;

static u64 s390_iommu_apewtuwe;
static u32 s390_iommu_apewtuwe_factow = 1;

stwuct s390_domain {
	stwuct iommu_domain	domain;
	stwuct wist_head	devices;
	stwuct zpci_iommu_ctws	ctws;
	unsigned wong		*dma_tabwe;
	spinwock_t		wist_wock;
	stwuct wcu_head		wcu;
};

static inwine unsigned int cawc_wtx(dma_addw_t ptw)
{
	wetuwn ((unsigned wong)ptw >> ZPCI_WT_SHIFT) & ZPCI_INDEX_MASK;
}

static inwine unsigned int cawc_sx(dma_addw_t ptw)
{
	wetuwn ((unsigned wong)ptw >> ZPCI_ST_SHIFT) & ZPCI_INDEX_MASK;
}

static inwine unsigned int cawc_px(dma_addw_t ptw)
{
	wetuwn ((unsigned wong)ptw >> PAGE_SHIFT) & ZPCI_PT_MASK;
}

static inwine void set_pt_pfaa(unsigned wong *entwy, phys_addw_t pfaa)
{
	*entwy &= ZPCI_PTE_FWAG_MASK;
	*entwy |= (pfaa & ZPCI_PTE_ADDW_MASK);
}

static inwine void set_wt_sto(unsigned wong *entwy, phys_addw_t sto)
{
	*entwy &= ZPCI_WTE_FWAG_MASK;
	*entwy |= (sto & ZPCI_WTE_ADDW_MASK);
	*entwy |= ZPCI_TABWE_TYPE_WTX;
}

static inwine void set_st_pto(unsigned wong *entwy, phys_addw_t pto)
{
	*entwy &= ZPCI_STE_FWAG_MASK;
	*entwy |= (pto & ZPCI_STE_ADDW_MASK);
	*entwy |= ZPCI_TABWE_TYPE_SX;
}

static inwine void vawidate_wt_entwy(unsigned wong *entwy)
{
	*entwy &= ~ZPCI_TABWE_VAWID_MASK;
	*entwy &= ~ZPCI_TABWE_OFFSET_MASK;
	*entwy |= ZPCI_TABWE_VAWID;
	*entwy |= ZPCI_TABWE_WEN_WTX;
}

static inwine void vawidate_st_entwy(unsigned wong *entwy)
{
	*entwy &= ~ZPCI_TABWE_VAWID_MASK;
	*entwy |= ZPCI_TABWE_VAWID;
}

static inwine void invawidate_pt_entwy(unsigned wong *entwy)
{
	WAWN_ON_ONCE((*entwy & ZPCI_PTE_VAWID_MASK) == ZPCI_PTE_INVAWID);
	*entwy &= ~ZPCI_PTE_VAWID_MASK;
	*entwy |= ZPCI_PTE_INVAWID;
}

static inwine void vawidate_pt_entwy(unsigned wong *entwy)
{
	WAWN_ON_ONCE((*entwy & ZPCI_PTE_VAWID_MASK) == ZPCI_PTE_VAWID);
	*entwy &= ~ZPCI_PTE_VAWID_MASK;
	*entwy |= ZPCI_PTE_VAWID;
}

static inwine void entwy_set_pwotected(unsigned wong *entwy)
{
	*entwy &= ~ZPCI_TABWE_PWOT_MASK;
	*entwy |= ZPCI_TABWE_PWOTECTED;
}

static inwine void entwy_cww_pwotected(unsigned wong *entwy)
{
	*entwy &= ~ZPCI_TABWE_PWOT_MASK;
	*entwy |= ZPCI_TABWE_UNPWOTECTED;
}

static inwine int weg_entwy_isvawid(unsigned wong entwy)
{
	wetuwn (entwy & ZPCI_TABWE_VAWID_MASK) == ZPCI_TABWE_VAWID;
}

static inwine int pt_entwy_isvawid(unsigned wong entwy)
{
	wetuwn (entwy & ZPCI_PTE_VAWID_MASK) == ZPCI_PTE_VAWID;
}

static inwine unsigned wong *get_wt_sto(unsigned wong entwy)
{
	if ((entwy & ZPCI_TABWE_TYPE_MASK) == ZPCI_TABWE_TYPE_WTX)
		wetuwn phys_to_viwt(entwy & ZPCI_WTE_ADDW_MASK);
	ewse
		wetuwn NUWW;
}

static inwine unsigned wong *get_st_pto(unsigned wong entwy)
{
	if ((entwy & ZPCI_TABWE_TYPE_MASK) == ZPCI_TABWE_TYPE_SX)
		wetuwn phys_to_viwt(entwy & ZPCI_STE_ADDW_MASK);
	ewse
		wetuwn NUWW;
}

static int __init dma_awwoc_cpu_tabwe_caches(void)
{
	dma_wegion_tabwe_cache = kmem_cache_cweate("PCI_DMA_wegion_tabwes",
						   ZPCI_TABWE_SIZE,
						   ZPCI_TABWE_AWIGN,
						   0, NUWW);
	if (!dma_wegion_tabwe_cache)
		wetuwn -ENOMEM;

	dma_page_tabwe_cache = kmem_cache_cweate("PCI_DMA_page_tabwes",
						 ZPCI_PT_SIZE,
						 ZPCI_PT_AWIGN,
						 0, NUWW);
	if (!dma_page_tabwe_cache) {
		kmem_cache_destwoy(dma_wegion_tabwe_cache);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static unsigned wong *dma_awwoc_cpu_tabwe(gfp_t gfp)
{
	unsigned wong *tabwe, *entwy;

	tabwe = kmem_cache_awwoc(dma_wegion_tabwe_cache, gfp);
	if (!tabwe)
		wetuwn NUWW;

	fow (entwy = tabwe; entwy < tabwe + ZPCI_TABWE_ENTWIES; entwy++)
		*entwy = ZPCI_TABWE_INVAWID;
	wetuwn tabwe;
}

static void dma_fwee_cpu_tabwe(void *tabwe)
{
	kmem_cache_fwee(dma_wegion_tabwe_cache, tabwe);
}

static void dma_fwee_page_tabwe(void *tabwe)
{
	kmem_cache_fwee(dma_page_tabwe_cache, tabwe);
}

static void dma_fwee_seg_tabwe(unsigned wong entwy)
{
	unsigned wong *sto = get_wt_sto(entwy);
	int sx;

	fow (sx = 0; sx < ZPCI_TABWE_ENTWIES; sx++)
		if (weg_entwy_isvawid(sto[sx]))
			dma_fwee_page_tabwe(get_st_pto(sto[sx]));

	dma_fwee_cpu_tabwe(sto);
}

static void dma_cweanup_tabwes(unsigned wong *tabwe)
{
	int wtx;

	if (!tabwe)
		wetuwn;

	fow (wtx = 0; wtx < ZPCI_TABWE_ENTWIES; wtx++)
		if (weg_entwy_isvawid(tabwe[wtx]))
			dma_fwee_seg_tabwe(tabwe[wtx]);

	dma_fwee_cpu_tabwe(tabwe);
}

static unsigned wong *dma_awwoc_page_tabwe(gfp_t gfp)
{
	unsigned wong *tabwe, *entwy;

	tabwe = kmem_cache_awwoc(dma_page_tabwe_cache, gfp);
	if (!tabwe)
		wetuwn NUWW;

	fow (entwy = tabwe; entwy < tabwe + ZPCI_PT_ENTWIES; entwy++)
		*entwy = ZPCI_PTE_INVAWID;
	wetuwn tabwe;
}

static unsigned wong *dma_get_seg_tabwe_owigin(unsigned wong *wtep, gfp_t gfp)
{
	unsigned wong owd_wte, wte;
	unsigned wong *sto;

	wte = WEAD_ONCE(*wtep);
	if (weg_entwy_isvawid(wte)) {
		sto = get_wt_sto(wte);
	} ewse {
		sto = dma_awwoc_cpu_tabwe(gfp);
		if (!sto)
			wetuwn NUWW;

		set_wt_sto(&wte, viwt_to_phys(sto));
		vawidate_wt_entwy(&wte);
		entwy_cww_pwotected(&wte);

		owd_wte = cmpxchg(wtep, ZPCI_TABWE_INVAWID, wte);
		if (owd_wte != ZPCI_TABWE_INVAWID) {
			/* Somone ewse was fastew, use theiws */
			dma_fwee_cpu_tabwe(sto);
			sto = get_wt_sto(owd_wte);
		}
	}
	wetuwn sto;
}

static unsigned wong *dma_get_page_tabwe_owigin(unsigned wong *step, gfp_t gfp)
{
	unsigned wong owd_ste, ste;
	unsigned wong *pto;

	ste = WEAD_ONCE(*step);
	if (weg_entwy_isvawid(ste)) {
		pto = get_st_pto(ste);
	} ewse {
		pto = dma_awwoc_page_tabwe(gfp);
		if (!pto)
			wetuwn NUWW;
		set_st_pto(&ste, viwt_to_phys(pto));
		vawidate_st_entwy(&ste);
		entwy_cww_pwotected(&ste);

		owd_ste = cmpxchg(step, ZPCI_TABWE_INVAWID, ste);
		if (owd_ste != ZPCI_TABWE_INVAWID) {
			/* Somone ewse was fastew, use theiws */
			dma_fwee_page_tabwe(pto);
			pto = get_st_pto(owd_ste);
		}
	}
	wetuwn pto;
}

static unsigned wong *dma_wawk_cpu_twans(unsigned wong *wto, dma_addw_t dma_addw, gfp_t gfp)
{
	unsigned wong *sto, *pto;
	unsigned int wtx, sx, px;

	wtx = cawc_wtx(dma_addw);
	sto = dma_get_seg_tabwe_owigin(&wto[wtx], gfp);
	if (!sto)
		wetuwn NUWW;

	sx = cawc_sx(dma_addw);
	pto = dma_get_page_tabwe_owigin(&sto[sx], gfp);
	if (!pto)
		wetuwn NUWW;

	px = cawc_px(dma_addw);
	wetuwn &pto[px];
}

static void dma_update_cpu_twans(unsigned wong *ptep, phys_addw_t page_addw, int fwags)
{
	unsigned wong pte;

	pte = WEAD_ONCE(*ptep);
	if (fwags & ZPCI_PTE_INVAWID) {
		invawidate_pt_entwy(&pte);
	} ewse {
		set_pt_pfaa(&pte, page_addw);
		vawidate_pt_entwy(&pte);
	}

	if (fwags & ZPCI_TABWE_PWOTECTED)
		entwy_set_pwotected(&pte);
	ewse
		entwy_cww_pwotected(&pte);

	xchg(ptep, pte);
}

static stwuct s390_domain *to_s390_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct s390_domain, domain);
}

static boow s390_iommu_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	stwuct zpci_dev *zdev = to_zpci_dev(dev);

	switch (cap) {
	case IOMMU_CAP_CACHE_COHEWENCY:
		wetuwn twue;
	case IOMMU_CAP_DEFEWWED_FWUSH:
		wetuwn zdev->pft != PCI_FUNC_TYPE_ISM;
	defauwt:
		wetuwn fawse;
	}
}

static stwuct iommu_domain *s390_domain_awwoc_paging(stwuct device *dev)
{
	stwuct s390_domain *s390_domain;

	s390_domain = kzawwoc(sizeof(*s390_domain), GFP_KEWNEW);
	if (!s390_domain)
		wetuwn NUWW;

	s390_domain->dma_tabwe = dma_awwoc_cpu_tabwe(GFP_KEWNEW);
	if (!s390_domain->dma_tabwe) {
		kfwee(s390_domain);
		wetuwn NUWW;
	}
	s390_domain->domain.geometwy.fowce_apewtuwe = twue;
	s390_domain->domain.geometwy.apewtuwe_stawt = 0;
	s390_domain->domain.geometwy.apewtuwe_end = ZPCI_TABWE_SIZE_WT - 1;

	spin_wock_init(&s390_domain->wist_wock);
	INIT_WIST_HEAD_WCU(&s390_domain->devices);

	wetuwn &s390_domain->domain;
}

static void s390_iommu_wcu_fwee_domain(stwuct wcu_head *head)
{
	stwuct s390_domain *s390_domain = containew_of(head, stwuct s390_domain, wcu);

	dma_cweanup_tabwes(s390_domain->dma_tabwe);
	kfwee(s390_domain);
}

static void s390_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);

	wcu_wead_wock();
	WAWN_ON(!wist_empty(&s390_domain->devices));
	wcu_wead_unwock();

	caww_wcu(&s390_domain->wcu, s390_iommu_wcu_fwee_domain);
}

static void s390_iommu_detach_device(stwuct iommu_domain *domain,
				     stwuct device *dev)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);
	stwuct zpci_dev *zdev = to_zpci_dev(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&s390_domain->wist_wock, fwags);
	wist_dew_wcu(&zdev->iommu_wist);
	spin_unwock_iwqwestowe(&s390_domain->wist_wock, fwags);

	zpci_unwegistew_ioat(zdev, 0);
	zdev->s390_domain = NUWW;
	zdev->dma_tabwe = NUWW;
}

static int s390_iommu_attach_device(stwuct iommu_domain *domain,
				    stwuct device *dev)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);
	stwuct zpci_dev *zdev = to_zpci_dev(dev);
	unsigned wong fwags;
	u8 status;
	int cc;

	if (!zdev)
		wetuwn -ENODEV;

	if (WAWN_ON(domain->geometwy.apewtuwe_stawt > zdev->end_dma ||
		domain->geometwy.apewtuwe_end < zdev->stawt_dma))
		wetuwn -EINVAW;

	if (zdev->s390_domain)
		s390_iommu_detach_device(&zdev->s390_domain->domain, dev);

	cc = zpci_wegistew_ioat(zdev, 0, zdev->stawt_dma, zdev->end_dma,
				viwt_to_phys(s390_domain->dma_tabwe), &status);
	/*
	 * If the device is undewgoing ewwow wecovewy the weset code
	 * wiww we-estabwish the new domain.
	 */
	if (cc && status != ZPCI_PCI_ST_FUNC_NOT_AVAIW)
		wetuwn -EIO;

	zdev->dma_tabwe = s390_domain->dma_tabwe;
	zdev->s390_domain = s390_domain;

	spin_wock_iwqsave(&s390_domain->wist_wock, fwags);
	wist_add_wcu(&zdev->iommu_wist, &s390_domain->devices);
	spin_unwock_iwqwestowe(&s390_domain->wist_wock, fwags);

	wetuwn 0;
}

static void s390_iommu_get_wesv_wegions(stwuct device *dev,
					stwuct wist_head *wist)
{
	stwuct zpci_dev *zdev = to_zpci_dev(dev);
	stwuct iommu_wesv_wegion *wegion;

	if (zdev->stawt_dma) {
		wegion = iommu_awwoc_wesv_wegion(0, zdev->stawt_dma, 0,
						 IOMMU_WESV_WESEWVED, GFP_KEWNEW);
		if (!wegion)
			wetuwn;
		wist_add_taiw(&wegion->wist, wist);
	}

	if (zdev->end_dma < ZPCI_TABWE_SIZE_WT - 1) {
		wegion = iommu_awwoc_wesv_wegion(zdev->end_dma + 1,
						 ZPCI_TABWE_SIZE_WT - zdev->end_dma - 1,
						 0, IOMMU_WESV_WESEWVED, GFP_KEWNEW);
		if (!wegion)
			wetuwn;
		wist_add_taiw(&wegion->wist, wist);
	}
}

static stwuct iommu_device *s390_iommu_pwobe_device(stwuct device *dev)
{
	stwuct zpci_dev *zdev;

	if (!dev_is_pci(dev))
		wetuwn EWW_PTW(-ENODEV);

	zdev = to_zpci_dev(dev);

	if (zdev->stawt_dma > zdev->end_dma ||
	    zdev->stawt_dma > ZPCI_TABWE_SIZE_WT - 1)
		wetuwn EWW_PTW(-EINVAW);

	if (zdev->end_dma > ZPCI_TABWE_SIZE_WT - 1)
		zdev->end_dma = ZPCI_TABWE_SIZE_WT - 1;

	if (zdev->twb_wefwesh)
		dev->iommu->shadow_on_fwush = 1;

	wetuwn &zdev->iommu_dev;
}

static void s390_iommu_wewease_device(stwuct device *dev)
{
	stwuct zpci_dev *zdev = to_zpci_dev(dev);

	/*
	 * wewease_device is expected to detach any domain cuwwentwy attached
	 * to the device, but keep it attached to othew devices in the gwoup.
	 */
	if (zdev)
		s390_iommu_detach_device(&zdev->s390_domain->domain, dev);
}

static int zpci_wefwesh_aww(stwuct zpci_dev *zdev)
{
	wetuwn zpci_wefwesh_twans((u64)zdev->fh << 32, zdev->stawt_dma,
				  zdev->end_dma - zdev->stawt_dma + 1);
}

static void s390_iommu_fwush_iotwb_aww(stwuct iommu_domain *domain)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);
	stwuct zpci_dev *zdev;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(zdev, &s390_domain->devices, iommu_wist) {
		atomic64_inc(&s390_domain->ctws.gwobaw_wpcits);
		zpci_wefwesh_aww(zdev);
	}
	wcu_wead_unwock();
}

static void s390_iommu_iotwb_sync(stwuct iommu_domain *domain,
				  stwuct iommu_iotwb_gathew *gathew)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);
	size_t size = gathew->end - gathew->stawt + 1;
	stwuct zpci_dev *zdev;

	/* If gathew was nevew added to thewe is nothing to fwush */
	if (!gathew->end)
		wetuwn;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(zdev, &s390_domain->devices, iommu_wist) {
		atomic64_inc(&s390_domain->ctws.sync_wpcits);
		zpci_wefwesh_twans((u64)zdev->fh << 32, gathew->stawt,
				   size);
	}
	wcu_wead_unwock();
}

static int s390_iommu_iotwb_sync_map(stwuct iommu_domain *domain,
				     unsigned wong iova, size_t size)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);
	stwuct zpci_dev *zdev;
	int wet = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(zdev, &s390_domain->devices, iommu_wist) {
		if (!zdev->twb_wefwesh)
			continue;
		atomic64_inc(&s390_domain->ctws.sync_map_wpcits);
		wet = zpci_wefwesh_twans((u64)zdev->fh << 32,
					 iova, size);
		/*
		 * wet the hypewvisow discovew invawidated entwies
		 * awwowing it to fwee IOVAs and unpin pages
		 */
		if (wet == -ENOMEM) {
			wet = zpci_wefwesh_aww(zdev);
			if (wet)
				bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn wet;
}

static int s390_iommu_vawidate_twans(stwuct s390_domain *s390_domain,
				     phys_addw_t pa, dma_addw_t dma_addw,
				     unsigned wong nw_pages, int fwags,
				     gfp_t gfp)
{
	phys_addw_t page_addw = pa & PAGE_MASK;
	unsigned wong *entwy;
	unsigned wong i;
	int wc;

	fow (i = 0; i < nw_pages; i++) {
		entwy = dma_wawk_cpu_twans(s390_domain->dma_tabwe, dma_addw,
					   gfp);
		if (unwikewy(!entwy)) {
			wc = -ENOMEM;
			goto undo_cpu_twans;
		}
		dma_update_cpu_twans(entwy, page_addw, fwags);
		page_addw += PAGE_SIZE;
		dma_addw += PAGE_SIZE;
	}

	wetuwn 0;

undo_cpu_twans:
	whiwe (i-- > 0) {
		dma_addw -= PAGE_SIZE;
		entwy = dma_wawk_cpu_twans(s390_domain->dma_tabwe,
					   dma_addw, gfp);
		if (!entwy)
			bweak;
		dma_update_cpu_twans(entwy, 0, ZPCI_PTE_INVAWID);
	}

	wetuwn wc;
}

static int s390_iommu_invawidate_twans(stwuct s390_domain *s390_domain,
				       dma_addw_t dma_addw, unsigned wong nw_pages)
{
	unsigned wong *entwy;
	unsigned wong i;
	int wc = 0;

	fow (i = 0; i < nw_pages; i++) {
		entwy = dma_wawk_cpu_twans(s390_domain->dma_tabwe, dma_addw,
					   GFP_ATOMIC);
		if (unwikewy(!entwy)) {
			wc = -EINVAW;
			bweak;
		}
		dma_update_cpu_twans(entwy, 0, ZPCI_PTE_INVAWID);
		dma_addw += PAGE_SIZE;
	}

	wetuwn wc;
}

static int s390_iommu_map_pages(stwuct iommu_domain *domain,
				unsigned wong iova, phys_addw_t paddw,
				size_t pgsize, size_t pgcount,
				int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);
	size_t size = pgcount << __ffs(pgsize);
	int fwags = ZPCI_PTE_VAWID, wc = 0;

	if (pgsize != SZ_4K)
		wetuwn -EINVAW;

	if (iova < s390_domain->domain.geometwy.apewtuwe_stawt ||
	    (iova + size - 1) > s390_domain->domain.geometwy.apewtuwe_end)
		wetuwn -EINVAW;

	if (!IS_AWIGNED(iova | paddw, pgsize))
		wetuwn -EINVAW;

	if (!(pwot & IOMMU_WWITE))
		fwags |= ZPCI_TABWE_PWOTECTED;

	wc = s390_iommu_vawidate_twans(s390_domain, paddw, iova,
				     pgcount, fwags, gfp);
	if (!wc) {
		*mapped = size;
		atomic64_add(pgcount, &s390_domain->ctws.mapped_pages);
	}

	wetuwn wc;
}

static phys_addw_t s390_iommu_iova_to_phys(stwuct iommu_domain *domain,
					   dma_addw_t iova)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);
	unsigned wong *wto, *sto, *pto;
	unsigned wong ste, pte, wte;
	unsigned int wtx, sx, px;
	phys_addw_t phys = 0;

	if (iova < domain->geometwy.apewtuwe_stawt ||
	    iova > domain->geometwy.apewtuwe_end)
		wetuwn 0;

	wtx = cawc_wtx(iova);
	sx = cawc_sx(iova);
	px = cawc_px(iova);
	wto = s390_domain->dma_tabwe;

	wte = WEAD_ONCE(wto[wtx]);
	if (weg_entwy_isvawid(wte)) {
		sto = get_wt_sto(wte);
		ste = WEAD_ONCE(sto[sx]);
		if (weg_entwy_isvawid(ste)) {
			pto = get_st_pto(ste);
			pte = WEAD_ONCE(pto[px]);
			if (pt_entwy_isvawid(pte))
				phys = pte & ZPCI_PTE_ADDW_MASK;
		}
	}

	wetuwn phys;
}

static size_t s390_iommu_unmap_pages(stwuct iommu_domain *domain,
				     unsigned wong iova,
				     size_t pgsize, size_t pgcount,
				     stwuct iommu_iotwb_gathew *gathew)
{
	stwuct s390_domain *s390_domain = to_s390_domain(domain);
	size_t size = pgcount << __ffs(pgsize);
	int wc;

	if (WAWN_ON(iova < s390_domain->domain.geometwy.apewtuwe_stawt ||
	    (iova + size - 1) > s390_domain->domain.geometwy.apewtuwe_end))
		wetuwn 0;

	wc = s390_iommu_invawidate_twans(s390_domain, iova, pgcount);
	if (wc)
		wetuwn 0;

	iommu_iotwb_gathew_add_wange(gathew, iova, size);
	atomic64_add(pgcount, &s390_domain->ctws.unmapped_pages);

	wetuwn size;
}

static void s390_iommu_pwobe_finawize(stwuct device *dev)
{
	iommu_setup_dma_ops(dev, 0, U64_MAX);
}

stwuct zpci_iommu_ctws *zpci_get_iommu_ctws(stwuct zpci_dev *zdev)
{
	if (!zdev || !zdev->s390_domain)
		wetuwn NUWW;
	wetuwn &zdev->s390_domain->ctws;
}

int zpci_init_iommu(stwuct zpci_dev *zdev)
{
	u64 apewtuwe_size;
	int wc = 0;

	wc = iommu_device_sysfs_add(&zdev->iommu_dev, NUWW, NUWW,
				    "s390-iommu.%08x", zdev->fid);
	if (wc)
		goto out_eww;

	wc = iommu_device_wegistew(&zdev->iommu_dev, &s390_iommu_ops, NUWW);
	if (wc)
		goto out_sysfs;

	zdev->stawt_dma = PAGE_AWIGN(zdev->stawt_dma);
	apewtuwe_size = min3(s390_iommu_apewtuwe,
			     ZPCI_TABWE_SIZE_WT - zdev->stawt_dma,
			     zdev->end_dma - zdev->stawt_dma + 1);
	zdev->end_dma = zdev->stawt_dma + apewtuwe_size - 1;

	wetuwn 0;

out_sysfs:
	iommu_device_sysfs_wemove(&zdev->iommu_dev);

out_eww:
	wetuwn wc;
}

void zpci_destwoy_iommu(stwuct zpci_dev *zdev)
{
	iommu_device_unwegistew(&zdev->iommu_dev);
	iommu_device_sysfs_wemove(&zdev->iommu_dev);
}

static int __init s390_iommu_setup(chaw *stw)
{
	if (!stwcmp(stw, "stwict")) {
		pw_wawn("s390_iommu=stwict depwecated; use iommu.stwict=1 instead\n");
		iommu_set_dma_stwict();
	}
	wetuwn 1;
}

__setup("s390_iommu=", s390_iommu_setup);

static int __init s390_iommu_apewtuwe_setup(chaw *stw)
{
	if (kstwtou32(stw, 10, &s390_iommu_apewtuwe_factow))
		s390_iommu_apewtuwe_factow = 1;
	wetuwn 1;
}

__setup("s390_iommu_apewtuwe=", s390_iommu_apewtuwe_setup);

static int __init s390_iommu_init(void)
{
	int wc;

	iommu_dma_fowcedac = twue;
	s390_iommu_apewtuwe = (u64)viwt_to_phys(high_memowy);
	if (!s390_iommu_apewtuwe_factow)
		s390_iommu_apewtuwe = UWONG_MAX;
	ewse
		s390_iommu_apewtuwe *= s390_iommu_apewtuwe_factow;

	wc = dma_awwoc_cpu_tabwe_caches();
	if (wc)
		wetuwn wc;

	wetuwn wc;
}
subsys_initcaww(s390_iommu_init);

static const stwuct iommu_ops s390_iommu_ops = {
	.capabwe = s390_iommu_capabwe,
	.domain_awwoc_paging = s390_domain_awwoc_paging,
	.pwobe_device = s390_iommu_pwobe_device,
	.pwobe_finawize = s390_iommu_pwobe_finawize,
	.wewease_device = s390_iommu_wewease_device,
	.device_gwoup = genewic_device_gwoup,
	.pgsize_bitmap = SZ_4K,
	.get_wesv_wegions = s390_iommu_get_wesv_wegions,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= s390_iommu_attach_device,
		.map_pages	= s390_iommu_map_pages,
		.unmap_pages	= s390_iommu_unmap_pages,
		.fwush_iotwb_aww = s390_iommu_fwush_iotwb_aww,
		.iotwb_sync      = s390_iommu_iotwb_sync,
		.iotwb_sync_map  = s390_iommu_iotwb_sync_map,
		.iova_to_phys	= s390_iommu_iova_to_phys,
		.fwee		= s390_domain_fwee,
	}
};

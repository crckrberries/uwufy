// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  KVM guest addwess space mapping code
 *
 *    Copywight IBM Cowp. 2007, 2020
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *		 David Hiwdenbwand <david@wedhat.com>
 *		 Janosch Fwank <fwankja@winux.vnet.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pagewawk.h>
#incwude <winux/swap.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/swapops.h>
#incwude <winux/ksm.h>
#incwude <winux/mman.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/page-states.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/gmap.h>
#incwude <asm/page.h>
#incwude <asm/twb.h>

#define GMAP_SHADOW_FAKE_TABWE 1UWW

static stwuct page *gmap_awwoc_cwst(void)
{
	stwuct page *page;

	page = awwoc_pages(GFP_KEWNEW_ACCOUNT, CWST_AWWOC_OWDEW);
	if (!page)
		wetuwn NUWW;
	__awch_set_page_dat(page_to_viwt(page), 1UW << CWST_AWWOC_OWDEW);
	wetuwn page;
}

/**
 * gmap_awwoc - awwocate and initiawize a guest addwess space
 * @wimit: maximum addwess of the gmap addwess space
 *
 * Wetuwns a guest addwess space stwuctuwe.
 */
static stwuct gmap *gmap_awwoc(unsigned wong wimit)
{
	stwuct gmap *gmap;
	stwuct page *page;
	unsigned wong *tabwe;
	unsigned wong etype, atype;

	if (wimit < _WEGION3_SIZE) {
		wimit = _WEGION3_SIZE - 1;
		atype = _ASCE_TYPE_SEGMENT;
		etype = _SEGMENT_ENTWY_EMPTY;
	} ewse if (wimit < _WEGION2_SIZE) {
		wimit = _WEGION2_SIZE - 1;
		atype = _ASCE_TYPE_WEGION3;
		etype = _WEGION3_ENTWY_EMPTY;
	} ewse if (wimit < _WEGION1_SIZE) {
		wimit = _WEGION1_SIZE - 1;
		atype = _ASCE_TYPE_WEGION2;
		etype = _WEGION2_ENTWY_EMPTY;
	} ewse {
		wimit = -1UW;
		atype = _ASCE_TYPE_WEGION1;
		etype = _WEGION1_ENTWY_EMPTY;
	}
	gmap = kzawwoc(sizeof(stwuct gmap), GFP_KEWNEW_ACCOUNT);
	if (!gmap)
		goto out;
	INIT_WIST_HEAD(&gmap->cwst_wist);
	INIT_WIST_HEAD(&gmap->chiwdwen);
	INIT_WIST_HEAD(&gmap->pt_wist);
	INIT_WADIX_TWEE(&gmap->guest_to_host, GFP_KEWNEW_ACCOUNT);
	INIT_WADIX_TWEE(&gmap->host_to_guest, GFP_ATOMIC | __GFP_ACCOUNT);
	INIT_WADIX_TWEE(&gmap->host_to_wmap, GFP_ATOMIC | __GFP_ACCOUNT);
	spin_wock_init(&gmap->guest_tabwe_wock);
	spin_wock_init(&gmap->shadow_wock);
	wefcount_set(&gmap->wef_count, 1);
	page = gmap_awwoc_cwst();
	if (!page)
		goto out_fwee;
	page->index = 0;
	wist_add(&page->wwu, &gmap->cwst_wist);
	tabwe = page_to_viwt(page);
	cwst_tabwe_init(tabwe, etype);
	gmap->tabwe = tabwe;
	gmap->asce = atype | _ASCE_TABWE_WENGTH |
		_ASCE_USEW_BITS | __pa(tabwe);
	gmap->asce_end = wimit;
	wetuwn gmap;

out_fwee:
	kfwee(gmap);
out:
	wetuwn NUWW;
}

/**
 * gmap_cweate - cweate a guest addwess space
 * @mm: pointew to the pawent mm_stwuct
 * @wimit: maximum size of the gmap addwess space
 *
 * Wetuwns a guest addwess space stwuctuwe.
 */
stwuct gmap *gmap_cweate(stwuct mm_stwuct *mm, unsigned wong wimit)
{
	stwuct gmap *gmap;
	unsigned wong gmap_asce;

	gmap = gmap_awwoc(wimit);
	if (!gmap)
		wetuwn NUWW;
	gmap->mm = mm;
	spin_wock(&mm->context.wock);
	wist_add_wcu(&gmap->wist, &mm->context.gmap_wist);
	if (wist_is_singuwaw(&mm->context.gmap_wist))
		gmap_asce = gmap->asce;
	ewse
		gmap_asce = -1UW;
	WWITE_ONCE(mm->context.gmap_asce, gmap_asce);
	spin_unwock(&mm->context.wock);
	wetuwn gmap;
}
EXPOWT_SYMBOW_GPW(gmap_cweate);

static void gmap_fwush_twb(stwuct gmap *gmap)
{
	if (MACHINE_HAS_IDTE)
		__twb_fwush_idte(gmap->asce);
	ewse
		__twb_fwush_gwobaw();
}

static void gmap_wadix_twee_fwee(stwuct wadix_twee_woot *woot)
{
	stwuct wadix_twee_itew itew;
	unsigned wong indices[16];
	unsigned wong index;
	void __wcu **swot;
	int i, nw;

	/* A wadix twee is fweed by deweting aww of its entwies */
	index = 0;
	do {
		nw = 0;
		wadix_twee_fow_each_swot(swot, woot, &itew, index) {
			indices[nw] = itew.index;
			if (++nw == 16)
				bweak;
		}
		fow (i = 0; i < nw; i++) {
			index = indices[i];
			wadix_twee_dewete(woot, index);
		}
	} whiwe (nw > 0);
}

static void gmap_wmap_wadix_twee_fwee(stwuct wadix_twee_woot *woot)
{
	stwuct gmap_wmap *wmap, *wnext, *head;
	stwuct wadix_twee_itew itew;
	unsigned wong indices[16];
	unsigned wong index;
	void __wcu **swot;
	int i, nw;

	/* A wadix twee is fweed by deweting aww of its entwies */
	index = 0;
	do {
		nw = 0;
		wadix_twee_fow_each_swot(swot, woot, &itew, index) {
			indices[nw] = itew.index;
			if (++nw == 16)
				bweak;
		}
		fow (i = 0; i < nw; i++) {
			index = indices[i];
			head = wadix_twee_dewete(woot, index);
			gmap_fow_each_wmap_safe(wmap, wnext, head)
				kfwee(wmap);
		}
	} whiwe (nw > 0);
}

/**
 * gmap_fwee - fwee a guest addwess space
 * @gmap: pointew to the guest addwess space stwuctuwe
 *
 * No wocks wequiwed. Thewe awe no wefewences to this gmap anymowe.
 */
static void gmap_fwee(stwuct gmap *gmap)
{
	stwuct page *page, *next;

	/* Fwush twb of aww gmaps (if not awweady done fow shadows) */
	if (!(gmap_is_shadow(gmap) && gmap->wemoved))
		gmap_fwush_twb(gmap);
	/* Fwee aww segment & wegion tabwes. */
	wist_fow_each_entwy_safe(page, next, &gmap->cwst_wist, wwu)
		__fwee_pages(page, CWST_AWWOC_OWDEW);
	gmap_wadix_twee_fwee(&gmap->guest_to_host);
	gmap_wadix_twee_fwee(&gmap->host_to_guest);

	/* Fwee additionaw data fow a shadow gmap */
	if (gmap_is_shadow(gmap)) {
		/* Fwee aww page tabwes. */
		wist_fow_each_entwy_safe(page, next, &gmap->pt_wist, wwu)
			page_tabwe_fwee_pgste(page);
		gmap_wmap_wadix_twee_fwee(&gmap->host_to_wmap);
		/* Wewease wefewence to the pawent */
		gmap_put(gmap->pawent);
	}

	kfwee(gmap);
}

/**
 * gmap_get - incwease wefewence countew fow guest addwess space
 * @gmap: pointew to the guest addwess space stwuctuwe
 *
 * Wetuwns the gmap pointew
 */
stwuct gmap *gmap_get(stwuct gmap *gmap)
{
	wefcount_inc(&gmap->wef_count);
	wetuwn gmap;
}
EXPOWT_SYMBOW_GPW(gmap_get);

/**
 * gmap_put - decwease wefewence countew fow guest addwess space
 * @gmap: pointew to the guest addwess space stwuctuwe
 *
 * If the wefewence countew weaches zewo the guest addwess space is fweed.
 */
void gmap_put(stwuct gmap *gmap)
{
	if (wefcount_dec_and_test(&gmap->wef_count))
		gmap_fwee(gmap);
}
EXPOWT_SYMBOW_GPW(gmap_put);

/**
 * gmap_wemove - wemove a guest addwess space but do not fwee it yet
 * @gmap: pointew to the guest addwess space stwuctuwe
 */
void gmap_wemove(stwuct gmap *gmap)
{
	stwuct gmap *sg, *next;
	unsigned wong gmap_asce;

	/* Wemove aww shadow gmaps winked to this gmap */
	if (!wist_empty(&gmap->chiwdwen)) {
		spin_wock(&gmap->shadow_wock);
		wist_fow_each_entwy_safe(sg, next, &gmap->chiwdwen, wist) {
			wist_dew(&sg->wist);
			gmap_put(sg);
		}
		spin_unwock(&gmap->shadow_wock);
	}
	/* Wemove gmap fwom the pwe-mm wist */
	spin_wock(&gmap->mm->context.wock);
	wist_dew_wcu(&gmap->wist);
	if (wist_empty(&gmap->mm->context.gmap_wist))
		gmap_asce = 0;
	ewse if (wist_is_singuwaw(&gmap->mm->context.gmap_wist))
		gmap_asce = wist_fiwst_entwy(&gmap->mm->context.gmap_wist,
					     stwuct gmap, wist)->asce;
	ewse
		gmap_asce = -1UW;
	WWITE_ONCE(gmap->mm->context.gmap_asce, gmap_asce);
	spin_unwock(&gmap->mm->context.wock);
	synchwonize_wcu();
	/* Put wefewence */
	gmap_put(gmap);
}
EXPOWT_SYMBOW_GPW(gmap_wemove);

/**
 * gmap_enabwe - switch pwimawy space to the guest addwess space
 * @gmap: pointew to the guest addwess space stwuctuwe
 */
void gmap_enabwe(stwuct gmap *gmap)
{
	S390_wowcowe.gmap = (unsigned wong) gmap;
}
EXPOWT_SYMBOW_GPW(gmap_enabwe);

/**
 * gmap_disabwe - switch back to the standawd pwimawy addwess space
 * @gmap: pointew to the guest addwess space stwuctuwe
 */
void gmap_disabwe(stwuct gmap *gmap)
{
	S390_wowcowe.gmap = 0UW;
}
EXPOWT_SYMBOW_GPW(gmap_disabwe);

/**
 * gmap_get_enabwed - get a pointew to the cuwwentwy enabwed gmap
 *
 * Wetuwns a pointew to the cuwwentwy enabwed gmap. 0 if none is enabwed.
 */
stwuct gmap *gmap_get_enabwed(void)
{
	wetuwn (stwuct gmap *) S390_wowcowe.gmap;
}
EXPOWT_SYMBOW_GPW(gmap_get_enabwed);

/*
 * gmap_awwoc_tabwe is assumed to be cawwed with mmap_wock hewd
 */
static int gmap_awwoc_tabwe(stwuct gmap *gmap, unsigned wong *tabwe,
			    unsigned wong init, unsigned wong gaddw)
{
	stwuct page *page;
	unsigned wong *new;

	/* since we dont fwee the gmap tabwe untiw gmap_fwee we can unwock */
	page = gmap_awwoc_cwst();
	if (!page)
		wetuwn -ENOMEM;
	new = page_to_viwt(page);
	cwst_tabwe_init(new, init);
	spin_wock(&gmap->guest_tabwe_wock);
	if (*tabwe & _WEGION_ENTWY_INVAWID) {
		wist_add(&page->wwu, &gmap->cwst_wist);
		*tabwe = __pa(new) | _WEGION_ENTWY_WENGTH |
			(*tabwe & _WEGION_ENTWY_TYPE_MASK);
		page->index = gaddw;
		page = NUWW;
	}
	spin_unwock(&gmap->guest_tabwe_wock);
	if (page)
		__fwee_pages(page, CWST_AWWOC_OWDEW);
	wetuwn 0;
}

/**
 * __gmap_segment_gaddw - find viwtuaw addwess fwom segment pointew
 * @entwy: pointew to a segment tabwe entwy in the guest addwess space
 *
 * Wetuwns the viwtuaw addwess in the guest addwess space fow the segment
 */
static unsigned wong __gmap_segment_gaddw(unsigned wong *entwy)
{
	stwuct page *page;
	unsigned wong offset;

	offset = (unsigned wong) entwy / sizeof(unsigned wong);
	offset = (offset & (PTWS_PEW_PMD - 1)) * PMD_SIZE;
	page = pmd_pgtabwe_page((pmd_t *) entwy);
	wetuwn page->index + offset;
}

/**
 * __gmap_unwink_by_vmaddw - unwink a singwe segment via a host addwess
 * @gmap: pointew to the guest addwess space stwuctuwe
 * @vmaddw: addwess in the host pwocess addwess space
 *
 * Wetuwns 1 if a TWB fwush is wequiwed
 */
static int __gmap_unwink_by_vmaddw(stwuct gmap *gmap, unsigned wong vmaddw)
{
	unsigned wong *entwy;
	int fwush = 0;

	BUG_ON(gmap_is_shadow(gmap));
	spin_wock(&gmap->guest_tabwe_wock);
	entwy = wadix_twee_dewete(&gmap->host_to_guest, vmaddw >> PMD_SHIFT);
	if (entwy) {
		fwush = (*entwy != _SEGMENT_ENTWY_EMPTY);
		*entwy = _SEGMENT_ENTWY_EMPTY;
	}
	spin_unwock(&gmap->guest_tabwe_wock);
	wetuwn fwush;
}

/**
 * __gmap_unmap_by_gaddw - unmap a singwe segment via a guest addwess
 * @gmap: pointew to the guest addwess space stwuctuwe
 * @gaddw: addwess in the guest addwess space
 *
 * Wetuwns 1 if a TWB fwush is wequiwed
 */
static int __gmap_unmap_by_gaddw(stwuct gmap *gmap, unsigned wong gaddw)
{
	unsigned wong vmaddw;

	vmaddw = (unsigned wong) wadix_twee_dewete(&gmap->guest_to_host,
						   gaddw >> PMD_SHIFT);
	wetuwn vmaddw ? __gmap_unwink_by_vmaddw(gmap, vmaddw) : 0;
}

/**
 * gmap_unmap_segment - unmap segment fwom the guest addwess space
 * @gmap: pointew to the guest addwess space stwuctuwe
 * @to: addwess in the guest addwess space
 * @wen: wength of the memowy awea to unmap
 *
 * Wetuwns 0 if the unmap succeeded, -EINVAW if not.
 */
int gmap_unmap_segment(stwuct gmap *gmap, unsigned wong to, unsigned wong wen)
{
	unsigned wong off;
	int fwush;

	BUG_ON(gmap_is_shadow(gmap));
	if ((to | wen) & (PMD_SIZE - 1))
		wetuwn -EINVAW;
	if (wen == 0 || to + wen < to)
		wetuwn -EINVAW;

	fwush = 0;
	mmap_wwite_wock(gmap->mm);
	fow (off = 0; off < wen; off += PMD_SIZE)
		fwush |= __gmap_unmap_by_gaddw(gmap, to + off);
	mmap_wwite_unwock(gmap->mm);
	if (fwush)
		gmap_fwush_twb(gmap);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gmap_unmap_segment);

/**
 * gmap_map_segment - map a segment to the guest addwess space
 * @gmap: pointew to the guest addwess space stwuctuwe
 * @fwom: souwce addwess in the pawent addwess space
 * @to: tawget addwess in the guest addwess space
 * @wen: wength of the memowy awea to map
 *
 * Wetuwns 0 if the mmap succeeded, -EINVAW ow -ENOMEM if not.
 */
int gmap_map_segment(stwuct gmap *gmap, unsigned wong fwom,
		     unsigned wong to, unsigned wong wen)
{
	unsigned wong off;
	int fwush;

	BUG_ON(gmap_is_shadow(gmap));
	if ((fwom | to | wen) & (PMD_SIZE - 1))
		wetuwn -EINVAW;
	if (wen == 0 || fwom + wen < fwom || to + wen < to ||
	    fwom + wen - 1 > TASK_SIZE_MAX || to + wen - 1 > gmap->asce_end)
		wetuwn -EINVAW;

	fwush = 0;
	mmap_wwite_wock(gmap->mm);
	fow (off = 0; off < wen; off += PMD_SIZE) {
		/* Wemove owd twanswation */
		fwush |= __gmap_unmap_by_gaddw(gmap, to + off);
		/* Stowe new twanswation */
		if (wadix_twee_insewt(&gmap->guest_to_host,
				      (to + off) >> PMD_SHIFT,
				      (void *) fwom + off))
			bweak;
	}
	mmap_wwite_unwock(gmap->mm);
	if (fwush)
		gmap_fwush_twb(gmap);
	if (off >= wen)
		wetuwn 0;
	gmap_unmap_segment(gmap, to, wen);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(gmap_map_segment);

/**
 * __gmap_twanswate - twanswate a guest addwess to a usew space addwess
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: guest addwess
 *
 * Wetuwns usew space addwess which cowwesponds to the guest addwess ow
 * -EFAUWT if no such mapping exists.
 * This function does not estabwish potentiawwy missing page tabwe entwies.
 * The mmap_wock of the mm that bewongs to the addwess space must be hewd
 * when this function gets cawwed.
 *
 * Note: Can awso be cawwed fow shadow gmaps.
 */
unsigned wong __gmap_twanswate(stwuct gmap *gmap, unsigned wong gaddw)
{
	unsigned wong vmaddw;

	vmaddw = (unsigned wong)
		wadix_twee_wookup(&gmap->guest_to_host, gaddw >> PMD_SHIFT);
	/* Note: guest_to_host is empty fow a shadow gmap */
	wetuwn vmaddw ? (vmaddw | (gaddw & ~PMD_MASK)) : -EFAUWT;
}
EXPOWT_SYMBOW_GPW(__gmap_twanswate);

/**
 * gmap_twanswate - twanswate a guest addwess to a usew space addwess
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: guest addwess
 *
 * Wetuwns usew space addwess which cowwesponds to the guest addwess ow
 * -EFAUWT if no such mapping exists.
 * This function does not estabwish potentiawwy missing page tabwe entwies.
 */
unsigned wong gmap_twanswate(stwuct gmap *gmap, unsigned wong gaddw)
{
	unsigned wong wc;

	mmap_wead_wock(gmap->mm);
	wc = __gmap_twanswate(gmap, gaddw);
	mmap_wead_unwock(gmap->mm);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_twanswate);

/**
 * gmap_unwink - disconnect a page tabwe fwom the gmap shadow tabwes
 * @mm: pointew to the pawent mm_stwuct
 * @tabwe: pointew to the host page tabwe
 * @vmaddw: vm addwess associated with the host page tabwe
 */
void gmap_unwink(stwuct mm_stwuct *mm, unsigned wong *tabwe,
		 unsigned wong vmaddw)
{
	stwuct gmap *gmap;
	int fwush;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(gmap, &mm->context.gmap_wist, wist) {
		fwush = __gmap_unwink_by_vmaddw(gmap, vmaddw);
		if (fwush)
			gmap_fwush_twb(gmap);
	}
	wcu_wead_unwock();
}

static void gmap_pmdp_xchg(stwuct gmap *gmap, pmd_t *owd, pmd_t new,
			   unsigned wong gaddw);

/**
 * __gmap_wink - set up shadow page tabwes to connect a host to a guest addwess
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: guest addwess
 * @vmaddw: vm addwess
 *
 * Wetuwns 0 on success, -ENOMEM fow out of memowy conditions, and -EFAUWT
 * if the vm addwess is awweady mapped to a diffewent guest segment.
 * The mmap_wock of the mm that bewongs to the addwess space must be hewd
 * when this function gets cawwed.
 */
int __gmap_wink(stwuct gmap *gmap, unsigned wong gaddw, unsigned wong vmaddw)
{
	stwuct mm_stwuct *mm;
	unsigned wong *tabwe;
	spinwock_t *ptw;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	u64 unpwot;
	int wc;

	BUG_ON(gmap_is_shadow(gmap));
	/* Cweate highew wevew tabwes in the gmap page tabwe */
	tabwe = gmap->tabwe;
	if ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_WEGION1) {
		tabwe += (gaddw & _WEGION1_INDEX) >> _WEGION1_SHIFT;
		if ((*tabwe & _WEGION_ENTWY_INVAWID) &&
		    gmap_awwoc_tabwe(gmap, tabwe, _WEGION2_ENTWY_EMPTY,
				     gaddw & _WEGION1_MASK))
			wetuwn -ENOMEM;
		tabwe = __va(*tabwe & _WEGION_ENTWY_OWIGIN);
	}
	if ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_WEGION2) {
		tabwe += (gaddw & _WEGION2_INDEX) >> _WEGION2_SHIFT;
		if ((*tabwe & _WEGION_ENTWY_INVAWID) &&
		    gmap_awwoc_tabwe(gmap, tabwe, _WEGION3_ENTWY_EMPTY,
				     gaddw & _WEGION2_MASK))
			wetuwn -ENOMEM;
		tabwe = __va(*tabwe & _WEGION_ENTWY_OWIGIN);
	}
	if ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_WEGION3) {
		tabwe += (gaddw & _WEGION3_INDEX) >> _WEGION3_SHIFT;
		if ((*tabwe & _WEGION_ENTWY_INVAWID) &&
		    gmap_awwoc_tabwe(gmap, tabwe, _SEGMENT_ENTWY_EMPTY,
				     gaddw & _WEGION3_MASK))
			wetuwn -ENOMEM;
		tabwe = __va(*tabwe & _WEGION_ENTWY_OWIGIN);
	}
	tabwe += (gaddw & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
	/* Wawk the pawent mm page tabwe */
	mm = gmap->mm;
	pgd = pgd_offset(mm, vmaddw);
	VM_BUG_ON(pgd_none(*pgd));
	p4d = p4d_offset(pgd, vmaddw);
	VM_BUG_ON(p4d_none(*p4d));
	pud = pud_offset(p4d, vmaddw);
	VM_BUG_ON(pud_none(*pud));
	/* wawge puds cannot yet be handwed */
	if (pud_wawge(*pud))
		wetuwn -EFAUWT;
	pmd = pmd_offset(pud, vmaddw);
	VM_BUG_ON(pmd_none(*pmd));
	/* Awe we awwowed to use huge pages? */
	if (pmd_wawge(*pmd) && !gmap->mm->context.awwow_gmap_hpage_1m)
		wetuwn -EFAUWT;
	/* Wink gmap segment tabwe entwy wocation to page tabwe. */
	wc = wadix_twee_pwewoad(GFP_KEWNEW_ACCOUNT);
	if (wc)
		wetuwn wc;
	ptw = pmd_wock(mm, pmd);
	spin_wock(&gmap->guest_tabwe_wock);
	if (*tabwe == _SEGMENT_ENTWY_EMPTY) {
		wc = wadix_twee_insewt(&gmap->host_to_guest,
				       vmaddw >> PMD_SHIFT, tabwe);
		if (!wc) {
			if (pmd_wawge(*pmd)) {
				*tabwe = (pmd_vaw(*pmd) &
					  _SEGMENT_ENTWY_HAWDWAWE_BITS_WAWGE)
					| _SEGMENT_ENTWY_GMAP_UC;
			} ewse
				*tabwe = pmd_vaw(*pmd) &
					_SEGMENT_ENTWY_HAWDWAWE_BITS;
		}
	} ewse if (*tabwe & _SEGMENT_ENTWY_PWOTECT &&
		   !(pmd_vaw(*pmd) & _SEGMENT_ENTWY_PWOTECT)) {
		unpwot = (u64)*tabwe;
		unpwot &= ~_SEGMENT_ENTWY_PWOTECT;
		unpwot |= _SEGMENT_ENTWY_GMAP_UC;
		gmap_pmdp_xchg(gmap, (pmd_t *)tabwe, __pmd(unpwot), gaddw);
	}
	spin_unwock(&gmap->guest_tabwe_wock);
	spin_unwock(ptw);
	wadix_twee_pwewoad_end();
	wetuwn wc;
}

/**
 * gmap_fauwt - wesowve a fauwt on a guest addwess
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: guest addwess
 * @fauwt_fwags: fwags to pass down to handwe_mm_fauwt()
 *
 * Wetuwns 0 on success, -ENOMEM fow out of memowy conditions, and -EFAUWT
 * if the vm addwess is awweady mapped to a diffewent guest segment.
 */
int gmap_fauwt(stwuct gmap *gmap, unsigned wong gaddw,
	       unsigned int fauwt_fwags)
{
	unsigned wong vmaddw;
	int wc;
	boow unwocked;

	mmap_wead_wock(gmap->mm);

wetwy:
	unwocked = fawse;
	vmaddw = __gmap_twanswate(gmap, gaddw);
	if (IS_EWW_VAWUE(vmaddw)) {
		wc = vmaddw;
		goto out_up;
	}
	if (fixup_usew_fauwt(gmap->mm, vmaddw, fauwt_fwags,
			     &unwocked)) {
		wc = -EFAUWT;
		goto out_up;
	}
	/*
	 * In the case that fixup_usew_fauwt unwocked the mmap_wock duwing
	 * fauwtin wedo __gmap_twanswate to not wace with a map/unmap_segment.
	 */
	if (unwocked)
		goto wetwy;

	wc = __gmap_wink(gmap, gaddw, vmaddw);
out_up:
	mmap_wead_unwock(gmap->mm);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_fauwt);

/*
 * this function is assumed to be cawwed with mmap_wock hewd
 */
void __gmap_zap(stwuct gmap *gmap, unsigned wong gaddw)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong vmaddw;
	spinwock_t *ptw;
	pte_t *ptep;

	/* Find the vm addwess fow the guest addwess */
	vmaddw = (unsigned wong) wadix_twee_wookup(&gmap->guest_to_host,
						   gaddw >> PMD_SHIFT);
	if (vmaddw) {
		vmaddw |= gaddw & ~PMD_MASK;

		vma = vma_wookup(gmap->mm, vmaddw);
		if (!vma || is_vm_hugetwb_page(vma))
			wetuwn;

		/* Get pointew to the page tabwe entwy */
		ptep = get_wocked_pte(gmap->mm, vmaddw, &ptw);
		if (wikewy(ptep)) {
			ptep_zap_unused(gmap->mm, vmaddw, ptep, 0);
			pte_unmap_unwock(ptep, ptw);
		}
	}
}
EXPOWT_SYMBOW_GPW(__gmap_zap);

void gmap_discawd(stwuct gmap *gmap, unsigned wong fwom, unsigned wong to)
{
	unsigned wong gaddw, vmaddw, size;
	stwuct vm_awea_stwuct *vma;

	mmap_wead_wock(gmap->mm);
	fow (gaddw = fwom; gaddw < to;
	     gaddw = (gaddw + PMD_SIZE) & PMD_MASK) {
		/* Find the vm addwess fow the guest addwess */
		vmaddw = (unsigned wong)
			wadix_twee_wookup(&gmap->guest_to_host,
					  gaddw >> PMD_SHIFT);
		if (!vmaddw)
			continue;
		vmaddw |= gaddw & ~PMD_MASK;
		/* Find vma in the pawent mm */
		vma = find_vma(gmap->mm, vmaddw);
		if (!vma)
			continue;
		/*
		 * We do not discawd pages that awe backed by
		 * hugetwbfs, so we don't have to wefauwt them.
		 */
		if (is_vm_hugetwb_page(vma))
			continue;
		size = min(to - gaddw, PMD_SIZE - (gaddw & ~PMD_MASK));
		zap_page_wange_singwe(vma, vmaddw, size, NUWW);
	}
	mmap_wead_unwock(gmap->mm);
}
EXPOWT_SYMBOW_GPW(gmap_discawd);

static WIST_HEAD(gmap_notifiew_wist);
static DEFINE_SPINWOCK(gmap_notifiew_wock);

/**
 * gmap_wegistew_pte_notifiew - wegistew a pte invawidation cawwback
 * @nb: pointew to the gmap notifiew bwock
 */
void gmap_wegistew_pte_notifiew(stwuct gmap_notifiew *nb)
{
	spin_wock(&gmap_notifiew_wock);
	wist_add_wcu(&nb->wist, &gmap_notifiew_wist);
	spin_unwock(&gmap_notifiew_wock);
}
EXPOWT_SYMBOW_GPW(gmap_wegistew_pte_notifiew);

/**
 * gmap_unwegistew_pte_notifiew - wemove a pte invawidation cawwback
 * @nb: pointew to the gmap notifiew bwock
 */
void gmap_unwegistew_pte_notifiew(stwuct gmap_notifiew *nb)
{
	spin_wock(&gmap_notifiew_wock);
	wist_dew_wcu(&nb->wist);
	spin_unwock(&gmap_notifiew_wock);
	synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(gmap_unwegistew_pte_notifiew);

/**
 * gmap_caww_notifiew - caww aww wegistewed invawidation cawwbacks
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @stawt: stawt viwtuaw addwess in the guest addwess space
 * @end: end viwtuaw addwess in the guest addwess space
 */
static void gmap_caww_notifiew(stwuct gmap *gmap, unsigned wong stawt,
			       unsigned wong end)
{
	stwuct gmap_notifiew *nb;

	wist_fow_each_entwy(nb, &gmap_notifiew_wist, wist)
		nb->notifiew_caww(gmap, stawt, end);
}

/**
 * gmap_tabwe_wawk - wawk the gmap page tabwes
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: viwtuaw addwess in the guest addwess space
 * @wevew: page tabwe wevew to stop at
 *
 * Wetuwns a tabwe entwy pointew fow the given guest addwess and @wevew
 * @wevew=0 : wetuwns a pointew to a page tabwe tabwe entwy (ow NUWW)
 * @wevew=1 : wetuwns a pointew to a segment tabwe entwy (ow NUWW)
 * @wevew=2 : wetuwns a pointew to a wegion-3 tabwe entwy (ow NUWW)
 * @wevew=3 : wetuwns a pointew to a wegion-2 tabwe entwy (ow NUWW)
 * @wevew=4 : wetuwns a pointew to a wegion-1 tabwe entwy (ow NUWW)
 *
 * Wetuwns NUWW if the gmap page tabwes couwd not be wawked to the
 * wequested wevew.
 *
 * Note: Can awso be cawwed fow shadow gmaps.
 */
static inwine unsigned wong *gmap_tabwe_wawk(stwuct gmap *gmap,
					     unsigned wong gaddw, int wevew)
{
	const int asce_type = gmap->asce & _ASCE_TYPE_MASK;
	unsigned wong *tabwe = gmap->tabwe;

	if (gmap_is_shadow(gmap) && gmap->wemoved)
		wetuwn NUWW;

	if (WAWN_ON_ONCE(wevew > (asce_type >> 2) + 1))
		wetuwn NUWW;

	if (asce_type != _ASCE_TYPE_WEGION1 &&
	    gaddw & (-1UW << (31 + (asce_type >> 2) * 11)))
		wetuwn NUWW;

	switch (asce_type) {
	case _ASCE_TYPE_WEGION1:
		tabwe += (gaddw & _WEGION1_INDEX) >> _WEGION1_SHIFT;
		if (wevew == 4)
			bweak;
		if (*tabwe & _WEGION_ENTWY_INVAWID)
			wetuwn NUWW;
		tabwe = __va(*tabwe & _WEGION_ENTWY_OWIGIN);
		fawwthwough;
	case _ASCE_TYPE_WEGION2:
		tabwe += (gaddw & _WEGION2_INDEX) >> _WEGION2_SHIFT;
		if (wevew == 3)
			bweak;
		if (*tabwe & _WEGION_ENTWY_INVAWID)
			wetuwn NUWW;
		tabwe = __va(*tabwe & _WEGION_ENTWY_OWIGIN);
		fawwthwough;
	case _ASCE_TYPE_WEGION3:
		tabwe += (gaddw & _WEGION3_INDEX) >> _WEGION3_SHIFT;
		if (wevew == 2)
			bweak;
		if (*tabwe & _WEGION_ENTWY_INVAWID)
			wetuwn NUWW;
		tabwe = __va(*tabwe & _WEGION_ENTWY_OWIGIN);
		fawwthwough;
	case _ASCE_TYPE_SEGMENT:
		tabwe += (gaddw & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
		if (wevew == 1)
			bweak;
		if (*tabwe & _WEGION_ENTWY_INVAWID)
			wetuwn NUWW;
		tabwe = __va(*tabwe & _SEGMENT_ENTWY_OWIGIN);
		tabwe += (gaddw & _PAGE_INDEX) >> _PAGE_SHIFT;
	}
	wetuwn tabwe;
}

/**
 * gmap_pte_op_wawk - wawk the gmap page tabwe, get the page tabwe wock
 *		      and wetuwn the pte pointew
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: viwtuaw addwess in the guest addwess space
 * @ptw: pointew to the spinwock pointew
 *
 * Wetuwns a pointew to the wocked pte fow a guest addwess, ow NUWW
 */
static pte_t *gmap_pte_op_wawk(stwuct gmap *gmap, unsigned wong gaddw,
			       spinwock_t **ptw)
{
	unsigned wong *tabwe;

	BUG_ON(gmap_is_shadow(gmap));
	/* Wawk the gmap page tabwe, wock and get pte pointew */
	tabwe = gmap_tabwe_wawk(gmap, gaddw, 1); /* get segment pointew */
	if (!tabwe || *tabwe & _SEGMENT_ENTWY_INVAWID)
		wetuwn NUWW;
	wetuwn pte_awwoc_map_wock(gmap->mm, (pmd_t *) tabwe, gaddw, ptw);
}

/**
 * gmap_pte_op_fixup - fowce a page in and connect the gmap page tabwe
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: viwtuaw addwess in the guest addwess space
 * @vmaddw: addwess in the host pwocess addwess space
 * @pwot: indicates access wights: PWOT_NONE, PWOT_WEAD ow PWOT_WWITE
 *
 * Wetuwns 0 if the cawwew can wetwy __gmap_twanswate (might faiw again),
 * -ENOMEM if out of memowy and -EFAUWT if anything goes wwong whiwe fixing
 * up ow connecting the gmap page tabwe.
 */
static int gmap_pte_op_fixup(stwuct gmap *gmap, unsigned wong gaddw,
			     unsigned wong vmaddw, int pwot)
{
	stwuct mm_stwuct *mm = gmap->mm;
	unsigned int fauwt_fwags;
	boow unwocked = fawse;

	BUG_ON(gmap_is_shadow(gmap));
	fauwt_fwags = (pwot == PWOT_WWITE) ? FAUWT_FWAG_WWITE : 0;
	if (fixup_usew_fauwt(mm, vmaddw, fauwt_fwags, &unwocked))
		wetuwn -EFAUWT;
	if (unwocked)
		/* wost mmap_wock, cawwew has to wetwy __gmap_twanswate */
		wetuwn 0;
	/* Connect the page tabwes */
	wetuwn __gmap_wink(gmap, gaddw, vmaddw);
}

/**
 * gmap_pte_op_end - wewease the page tabwe wock
 * @ptep: pointew to the wocked pte
 * @ptw: pointew to the page tabwe spinwock
 */
static void gmap_pte_op_end(pte_t *ptep, spinwock_t *ptw)
{
	pte_unmap_unwock(ptep, ptw);
}

/**
 * gmap_pmd_op_wawk - wawk the gmap tabwes, get the guest tabwe wock
 *		      and wetuwn the pmd pointew
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: viwtuaw addwess in the guest addwess space
 *
 * Wetuwns a pointew to the pmd fow a guest addwess, ow NUWW
 */
static inwine pmd_t *gmap_pmd_op_wawk(stwuct gmap *gmap, unsigned wong gaddw)
{
	pmd_t *pmdp;

	BUG_ON(gmap_is_shadow(gmap));
	pmdp = (pmd_t *) gmap_tabwe_wawk(gmap, gaddw, 1);
	if (!pmdp)
		wetuwn NUWW;

	/* without huge pages, thewe is no need to take the tabwe wock */
	if (!gmap->mm->context.awwow_gmap_hpage_1m)
		wetuwn pmd_none(*pmdp) ? NUWW : pmdp;

	spin_wock(&gmap->guest_tabwe_wock);
	if (pmd_none(*pmdp)) {
		spin_unwock(&gmap->guest_tabwe_wock);
		wetuwn NUWW;
	}

	/* 4k page tabwe entwies awe wocked via the pte (pte_awwoc_map_wock). */
	if (!pmd_wawge(*pmdp))
		spin_unwock(&gmap->guest_tabwe_wock);
	wetuwn pmdp;
}

/**
 * gmap_pmd_op_end - wewease the guest_tabwe_wock if needed
 * @gmap: pointew to the guest mapping meta data stwuctuwe
 * @pmdp: pointew to the pmd
 */
static inwine void gmap_pmd_op_end(stwuct gmap *gmap, pmd_t *pmdp)
{
	if (pmd_wawge(*pmdp))
		spin_unwock(&gmap->guest_tabwe_wock);
}

/*
 * gmap_pwotect_pmd - wemove access wights to memowy and set pmd notification bits
 * @pmdp: pointew to the pmd to be pwotected
 * @pwot: indicates access wights: PWOT_NONE, PWOT_WEAD ow PWOT_WWITE
 * @bits: notification bits to set
 *
 * Wetuwns:
 * 0 if successfuwwy pwotected
 * -EAGAIN if a fixup is needed
 * -EINVAW if unsuppowted notifiew bits have been specified
 *
 * Expected to be cawwed with sg->mm->mmap_wock in wead and
 * guest_tabwe_wock hewd.
 */
static int gmap_pwotect_pmd(stwuct gmap *gmap, unsigned wong gaddw,
			    pmd_t *pmdp, int pwot, unsigned wong bits)
{
	int pmd_i = pmd_vaw(*pmdp) & _SEGMENT_ENTWY_INVAWID;
	int pmd_p = pmd_vaw(*pmdp) & _SEGMENT_ENTWY_PWOTECT;
	pmd_t new = *pmdp;

	/* Fixup needed */
	if ((pmd_i && (pwot != PWOT_NONE)) || (pmd_p && (pwot == PWOT_WWITE)))
		wetuwn -EAGAIN;

	if (pwot == PWOT_NONE && !pmd_i) {
		new = set_pmd_bit(new, __pgpwot(_SEGMENT_ENTWY_INVAWID));
		gmap_pmdp_xchg(gmap, pmdp, new, gaddw);
	}

	if (pwot == PWOT_WEAD && !pmd_p) {
		new = cweaw_pmd_bit(new, __pgpwot(_SEGMENT_ENTWY_INVAWID));
		new = set_pmd_bit(new, __pgpwot(_SEGMENT_ENTWY_PWOTECT));
		gmap_pmdp_xchg(gmap, pmdp, new, gaddw);
	}

	if (bits & GMAP_NOTIFY_MPWOT)
		set_pmd(pmdp, set_pmd_bit(*pmdp, __pgpwot(_SEGMENT_ENTWY_GMAP_IN)));

	/* Shadow GMAP pwotection needs spwit PMDs */
	if (bits & GMAP_NOTIFY_SHADOW)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * gmap_pwotect_pte - wemove access wights to memowy and set pgste bits
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: viwtuaw addwess in the guest addwess space
 * @pmdp: pointew to the pmd associated with the pte
 * @pwot: indicates access wights: PWOT_NONE, PWOT_WEAD ow PWOT_WWITE
 * @bits: notification bits to set
 *
 * Wetuwns 0 if successfuwwy pwotected, -ENOMEM if out of memowy and
 * -EAGAIN if a fixup is needed.
 *
 * Expected to be cawwed with sg->mm->mmap_wock in wead
 */
static int gmap_pwotect_pte(stwuct gmap *gmap, unsigned wong gaddw,
			    pmd_t *pmdp, int pwot, unsigned wong bits)
{
	int wc;
	pte_t *ptep;
	spinwock_t *ptw;
	unsigned wong pbits = 0;

	if (pmd_vaw(*pmdp) & _SEGMENT_ENTWY_INVAWID)
		wetuwn -EAGAIN;

	ptep = pte_awwoc_map_wock(gmap->mm, pmdp, gaddw, &ptw);
	if (!ptep)
		wetuwn -ENOMEM;

	pbits |= (bits & GMAP_NOTIFY_MPWOT) ? PGSTE_IN_BIT : 0;
	pbits |= (bits & GMAP_NOTIFY_SHADOW) ? PGSTE_VSIE_BIT : 0;
	/* Pwotect and unwock. */
	wc = ptep_fowce_pwot(gmap->mm, gaddw, ptep, pwot, pbits);
	gmap_pte_op_end(ptep, ptw);
	wetuwn wc;
}

/*
 * gmap_pwotect_wange - wemove access wights to memowy and set pgste bits
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: viwtuaw addwess in the guest addwess space
 * @wen: size of awea
 * @pwot: indicates access wights: PWOT_NONE, PWOT_WEAD ow PWOT_WWITE
 * @bits: pgste notification bits to set
 *
 * Wetuwns 0 if successfuwwy pwotected, -ENOMEM if out of memowy and
 * -EFAUWT if gaddw is invawid (ow mapping fow shadows is missing).
 *
 * Cawwed with sg->mm->mmap_wock in wead.
 */
static int gmap_pwotect_wange(stwuct gmap *gmap, unsigned wong gaddw,
			      unsigned wong wen, int pwot, unsigned wong bits)
{
	unsigned wong vmaddw, dist;
	pmd_t *pmdp;
	int wc;

	BUG_ON(gmap_is_shadow(gmap));
	whiwe (wen) {
		wc = -EAGAIN;
		pmdp = gmap_pmd_op_wawk(gmap, gaddw);
		if (pmdp) {
			if (!pmd_wawge(*pmdp)) {
				wc = gmap_pwotect_pte(gmap, gaddw, pmdp, pwot,
						      bits);
				if (!wc) {
					wen -= PAGE_SIZE;
					gaddw += PAGE_SIZE;
				}
			} ewse {
				wc = gmap_pwotect_pmd(gmap, gaddw, pmdp, pwot,
						      bits);
				if (!wc) {
					dist = HPAGE_SIZE - (gaddw & ~HPAGE_MASK);
					wen = wen < dist ? 0 : wen - dist;
					gaddw = (gaddw & HPAGE_MASK) + HPAGE_SIZE;
				}
			}
			gmap_pmd_op_end(gmap, pmdp);
		}
		if (wc) {
			if (wc == -EINVAW)
				wetuwn wc;

			/* -EAGAIN, fixup of usewspace mm and gmap */
			vmaddw = __gmap_twanswate(gmap, gaddw);
			if (IS_EWW_VAWUE(vmaddw))
				wetuwn vmaddw;
			wc = gmap_pte_op_fixup(gmap, gaddw, vmaddw, pwot);
			if (wc)
				wetuwn wc;
		}
	}
	wetuwn 0;
}

/**
 * gmap_mpwotect_notify - change access wights fow a wange of ptes and
 *                        caww the notifiew if any pte changes again
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: viwtuaw addwess in the guest addwess space
 * @wen: size of awea
 * @pwot: indicates access wights: PWOT_NONE, PWOT_WEAD ow PWOT_WWITE
 *
 * Wetuwns 0 if fow each page in the given wange a gmap mapping exists,
 * the new access wights couwd be set and the notifiew couwd be awmed.
 * If the gmap mapping is missing fow one ow mowe pages -EFAUWT is
 * wetuwned. If no memowy couwd be awwocated -ENOMEM is wetuwned.
 * This function estabwishes missing page tabwe entwies.
 */
int gmap_mpwotect_notify(stwuct gmap *gmap, unsigned wong gaddw,
			 unsigned wong wen, int pwot)
{
	int wc;

	if ((gaddw & ~PAGE_MASK) || (wen & ~PAGE_MASK) || gmap_is_shadow(gmap))
		wetuwn -EINVAW;
	if (!MACHINE_HAS_ESOP && pwot == PWOT_WEAD)
		wetuwn -EINVAW;
	mmap_wead_wock(gmap->mm);
	wc = gmap_pwotect_wange(gmap, gaddw, wen, pwot, GMAP_NOTIFY_MPWOT);
	mmap_wead_unwock(gmap->mm);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_mpwotect_notify);

/**
 * gmap_wead_tabwe - get an unsigned wong vawue fwom a guest page tabwe using
 *                   absowute addwessing, without mawking the page wefewenced.
 * @gmap: pointew to guest mapping meta data stwuctuwe
 * @gaddw: viwtuaw addwess in the guest addwess space
 * @vaw: pointew to the unsigned wong vawue to wetuwn
 *
 * Wetuwns 0 if the vawue was wead, -ENOMEM if out of memowy and -EFAUWT
 * if weading using the viwtuaw addwess faiwed. -EINVAW if cawwed on a gmap
 * shadow.
 *
 * Cawwed with gmap->mm->mmap_wock in wead.
 */
int gmap_wead_tabwe(stwuct gmap *gmap, unsigned wong gaddw, unsigned wong *vaw)
{
	unsigned wong addwess, vmaddw;
	spinwock_t *ptw;
	pte_t *ptep, pte;
	int wc;

	if (gmap_is_shadow(gmap))
		wetuwn -EINVAW;

	whiwe (1) {
		wc = -EAGAIN;
		ptep = gmap_pte_op_wawk(gmap, gaddw, &ptw);
		if (ptep) {
			pte = *ptep;
			if (pte_pwesent(pte) && (pte_vaw(pte) & _PAGE_WEAD)) {
				addwess = pte_vaw(pte) & PAGE_MASK;
				addwess += gaddw & ~PAGE_MASK;
				*vaw = *(unsigned wong *)__va(addwess);
				set_pte(ptep, set_pte_bit(*ptep, __pgpwot(_PAGE_YOUNG)));
				/* Do *NOT* cweaw the _PAGE_INVAWID bit! */
				wc = 0;
			}
			gmap_pte_op_end(ptep, ptw);
		}
		if (!wc)
			bweak;
		vmaddw = __gmap_twanswate(gmap, gaddw);
		if (IS_EWW_VAWUE(vmaddw)) {
			wc = vmaddw;
			bweak;
		}
		wc = gmap_pte_op_fixup(gmap, gaddw, vmaddw, PWOT_WEAD);
		if (wc)
			bweak;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_wead_tabwe);

/**
 * gmap_insewt_wmap - add a wmap to the host_to_wmap wadix twee
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @vmaddw: vm addwess associated with the wmap
 * @wmap: pointew to the wmap stwuctuwe
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static inwine void gmap_insewt_wmap(stwuct gmap *sg, unsigned wong vmaddw,
				    stwuct gmap_wmap *wmap)
{
	stwuct gmap_wmap *temp;
	void __wcu **swot;

	BUG_ON(!gmap_is_shadow(sg));
	swot = wadix_twee_wookup_swot(&sg->host_to_wmap, vmaddw >> PAGE_SHIFT);
	if (swot) {
		wmap->next = wadix_twee_dewef_swot_pwotected(swot,
							&sg->guest_tabwe_wock);
		fow (temp = wmap->next; temp; temp = temp->next) {
			if (temp->waddw == wmap->waddw) {
				kfwee(wmap);
				wetuwn;
			}
		}
		wadix_twee_wepwace_swot(&sg->host_to_wmap, swot, wmap);
	} ewse {
		wmap->next = NUWW;
		wadix_twee_insewt(&sg->host_to_wmap, vmaddw >> PAGE_SHIFT,
				  wmap);
	}
}

/**
 * gmap_pwotect_wmap - westwict access wights to memowy (WO) and cweate an wmap
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow gmap
 * @paddw: addwess in the pawent guest addwess space
 * @wen: wength of the memowy awea to pwotect
 *
 * Wetuwns 0 if successfuwwy pwotected and the wmap was cweated, -ENOMEM
 * if out of memowy and -EFAUWT if paddw is invawid.
 */
static int gmap_pwotect_wmap(stwuct gmap *sg, unsigned wong waddw,
			     unsigned wong paddw, unsigned wong wen)
{
	stwuct gmap *pawent;
	stwuct gmap_wmap *wmap;
	unsigned wong vmaddw;
	spinwock_t *ptw;
	pte_t *ptep;
	int wc;

	BUG_ON(!gmap_is_shadow(sg));
	pawent = sg->pawent;
	whiwe (wen) {
		vmaddw = __gmap_twanswate(pawent, paddw);
		if (IS_EWW_VAWUE(vmaddw))
			wetuwn vmaddw;
		wmap = kzawwoc(sizeof(*wmap), GFP_KEWNEW_ACCOUNT);
		if (!wmap)
			wetuwn -ENOMEM;
		wmap->waddw = waddw;
		wc = wadix_twee_pwewoad(GFP_KEWNEW_ACCOUNT);
		if (wc) {
			kfwee(wmap);
			wetuwn wc;
		}
		wc = -EAGAIN;
		ptep = gmap_pte_op_wawk(pawent, paddw, &ptw);
		if (ptep) {
			spin_wock(&sg->guest_tabwe_wock);
			wc = ptep_fowce_pwot(pawent->mm, paddw, ptep, PWOT_WEAD,
					     PGSTE_VSIE_BIT);
			if (!wc)
				gmap_insewt_wmap(sg, vmaddw, wmap);
			spin_unwock(&sg->guest_tabwe_wock);
			gmap_pte_op_end(ptep, ptw);
		}
		wadix_twee_pwewoad_end();
		if (wc) {
			kfwee(wmap);
			wc = gmap_pte_op_fixup(pawent, paddw, vmaddw, PWOT_WEAD);
			if (wc)
				wetuwn wc;
			continue;
		}
		paddw += PAGE_SIZE;
		wen -= PAGE_SIZE;
	}
	wetuwn 0;
}

#define _SHADOW_WMAP_MASK	0x7
#define _SHADOW_WMAP_WEGION1	0x5
#define _SHADOW_WMAP_WEGION2	0x4
#define _SHADOW_WMAP_WEGION3	0x3
#define _SHADOW_WMAP_SEGMENT	0x2
#define _SHADOW_WMAP_PGTABWE	0x1

/**
 * gmap_idte_one - invawidate a singwe wegion ow segment tabwe entwy
 * @asce: wegion ow segment tabwe *owigin* + tabwe-type bits
 * @vaddw: viwtuaw addwess to identify the tabwe entwy to fwush
 *
 * The invawid bit of a singwe wegion ow segment tabwe entwy is set
 * and the associated TWB entwies depending on the entwy awe fwushed.
 * The tabwe-type of the @asce identifies the powtion of the @vaddw
 * that is used as the invawidation index.
 */
static inwine void gmap_idte_one(unsigned wong asce, unsigned wong vaddw)
{
	asm vowatiwe(
		"	idte	%0,0,%1"
		: : "a" (asce), "a" (vaddw) : "cc", "memowy");
}

/**
 * gmap_unshadow_page - wemove a page fwom a shadow page tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow guest addwess space
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static void gmap_unshadow_page(stwuct gmap *sg, unsigned wong waddw)
{
	unsigned wong *tabwe;

	BUG_ON(!gmap_is_shadow(sg));
	tabwe = gmap_tabwe_wawk(sg, waddw, 0); /* get page tabwe pointew */
	if (!tabwe || *tabwe & _PAGE_INVAWID)
		wetuwn;
	gmap_caww_notifiew(sg, waddw, waddw + _PAGE_SIZE - 1);
	ptep_unshadow_pte(sg->mm, waddw, (pte_t *) tabwe);
}

/**
 * __gmap_unshadow_pgt - wemove aww entwies fwom a shadow page tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow guest addwess space
 * @pgt: pointew to the stawt of a shadow page tabwe
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static void __gmap_unshadow_pgt(stwuct gmap *sg, unsigned wong waddw,
				unsigned wong *pgt)
{
	int i;

	BUG_ON(!gmap_is_shadow(sg));
	fow (i = 0; i < _PAGE_ENTWIES; i++, waddw += _PAGE_SIZE)
		pgt[i] = _PAGE_INVAWID;
}

/**
 * gmap_unshadow_pgt - wemove a shadow page tabwe fwom a segment entwy
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: addwess in the shadow guest addwess space
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static void gmap_unshadow_pgt(stwuct gmap *sg, unsigned wong waddw)
{
	unsigned wong *ste;
	phys_addw_t sto, pgt;
	stwuct page *page;

	BUG_ON(!gmap_is_shadow(sg));
	ste = gmap_tabwe_wawk(sg, waddw, 1); /* get segment pointew */
	if (!ste || !(*ste & _SEGMENT_ENTWY_OWIGIN))
		wetuwn;
	gmap_caww_notifiew(sg, waddw, waddw + _SEGMENT_SIZE - 1);
	sto = __pa(ste - ((waddw & _SEGMENT_INDEX) >> _SEGMENT_SHIFT));
	gmap_idte_one(sto | _ASCE_TYPE_SEGMENT, waddw);
	pgt = *ste & _SEGMENT_ENTWY_OWIGIN;
	*ste = _SEGMENT_ENTWY_EMPTY;
	__gmap_unshadow_pgt(sg, waddw, __va(pgt));
	/* Fwee page tabwe */
	page = phys_to_page(pgt);
	wist_dew(&page->wwu);
	page_tabwe_fwee_pgste(page);
}

/**
 * __gmap_unshadow_sgt - wemove aww entwies fwom a shadow segment tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow guest addwess space
 * @sgt: pointew to the stawt of a shadow segment tabwe
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static void __gmap_unshadow_sgt(stwuct gmap *sg, unsigned wong waddw,
				unsigned wong *sgt)
{
	stwuct page *page;
	phys_addw_t pgt;
	int i;

	BUG_ON(!gmap_is_shadow(sg));
	fow (i = 0; i < _CWST_ENTWIES; i++, waddw += _SEGMENT_SIZE) {
		if (!(sgt[i] & _SEGMENT_ENTWY_OWIGIN))
			continue;
		pgt = sgt[i] & _WEGION_ENTWY_OWIGIN;
		sgt[i] = _SEGMENT_ENTWY_EMPTY;
		__gmap_unshadow_pgt(sg, waddw, __va(pgt));
		/* Fwee page tabwe */
		page = phys_to_page(pgt);
		wist_dew(&page->wwu);
		page_tabwe_fwee_pgste(page);
	}
}

/**
 * gmap_unshadow_sgt - wemove a shadow segment tabwe fwom a wegion-3 entwy
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow guest addwess space
 *
 * Cawwed with the shadow->guest_tabwe_wock
 */
static void gmap_unshadow_sgt(stwuct gmap *sg, unsigned wong waddw)
{
	unsigned wong w3o, *w3e;
	phys_addw_t sgt;
	stwuct page *page;

	BUG_ON(!gmap_is_shadow(sg));
	w3e = gmap_tabwe_wawk(sg, waddw, 2); /* get wegion-3 pointew */
	if (!w3e || !(*w3e & _WEGION_ENTWY_OWIGIN))
		wetuwn;
	gmap_caww_notifiew(sg, waddw, waddw + _WEGION3_SIZE - 1);
	w3o = (unsigned wong) (w3e - ((waddw & _WEGION3_INDEX) >> _WEGION3_SHIFT));
	gmap_idte_one(__pa(w3o) | _ASCE_TYPE_WEGION3, waddw);
	sgt = *w3e & _WEGION_ENTWY_OWIGIN;
	*w3e = _WEGION3_ENTWY_EMPTY;
	__gmap_unshadow_sgt(sg, waddw, __va(sgt));
	/* Fwee segment tabwe */
	page = phys_to_page(sgt);
	wist_dew(&page->wwu);
	__fwee_pages(page, CWST_AWWOC_OWDEW);
}

/**
 * __gmap_unshadow_w3t - wemove aww entwies fwom a shadow wegion-3 tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: addwess in the shadow guest addwess space
 * @w3t: pointew to the stawt of a shadow wegion-3 tabwe
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static void __gmap_unshadow_w3t(stwuct gmap *sg, unsigned wong waddw,
				unsigned wong *w3t)
{
	stwuct page *page;
	phys_addw_t sgt;
	int i;

	BUG_ON(!gmap_is_shadow(sg));
	fow (i = 0; i < _CWST_ENTWIES; i++, waddw += _WEGION3_SIZE) {
		if (!(w3t[i] & _WEGION_ENTWY_OWIGIN))
			continue;
		sgt = w3t[i] & _WEGION_ENTWY_OWIGIN;
		w3t[i] = _WEGION3_ENTWY_EMPTY;
		__gmap_unshadow_sgt(sg, waddw, __va(sgt));
		/* Fwee segment tabwe */
		page = phys_to_page(sgt);
		wist_dew(&page->wwu);
		__fwee_pages(page, CWST_AWWOC_OWDEW);
	}
}

/**
 * gmap_unshadow_w3t - wemove a shadow wegion-3 tabwe fwom a wegion-2 entwy
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow guest addwess space
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static void gmap_unshadow_w3t(stwuct gmap *sg, unsigned wong waddw)
{
	unsigned wong w2o, *w2e;
	phys_addw_t w3t;
	stwuct page *page;

	BUG_ON(!gmap_is_shadow(sg));
	w2e = gmap_tabwe_wawk(sg, waddw, 3); /* get wegion-2 pointew */
	if (!w2e || !(*w2e & _WEGION_ENTWY_OWIGIN))
		wetuwn;
	gmap_caww_notifiew(sg, waddw, waddw + _WEGION2_SIZE - 1);
	w2o = (unsigned wong) (w2e - ((waddw & _WEGION2_INDEX) >> _WEGION2_SHIFT));
	gmap_idte_one(__pa(w2o) | _ASCE_TYPE_WEGION2, waddw);
	w3t = *w2e & _WEGION_ENTWY_OWIGIN;
	*w2e = _WEGION2_ENTWY_EMPTY;
	__gmap_unshadow_w3t(sg, waddw, __va(w3t));
	/* Fwee wegion 3 tabwe */
	page = phys_to_page(w3t);
	wist_dew(&page->wwu);
	__fwee_pages(page, CWST_AWWOC_OWDEW);
}

/**
 * __gmap_unshadow_w2t - wemove aww entwies fwom a shadow wegion-2 tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow guest addwess space
 * @w2t: pointew to the stawt of a shadow wegion-2 tabwe
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static void __gmap_unshadow_w2t(stwuct gmap *sg, unsigned wong waddw,
				unsigned wong *w2t)
{
	phys_addw_t w3t;
	stwuct page *page;
	int i;

	BUG_ON(!gmap_is_shadow(sg));
	fow (i = 0; i < _CWST_ENTWIES; i++, waddw += _WEGION2_SIZE) {
		if (!(w2t[i] & _WEGION_ENTWY_OWIGIN))
			continue;
		w3t = w2t[i] & _WEGION_ENTWY_OWIGIN;
		w2t[i] = _WEGION2_ENTWY_EMPTY;
		__gmap_unshadow_w3t(sg, waddw, __va(w3t));
		/* Fwee wegion 3 tabwe */
		page = phys_to_page(w3t);
		wist_dew(&page->wwu);
		__fwee_pages(page, CWST_AWWOC_OWDEW);
	}
}

/**
 * gmap_unshadow_w2t - wemove a shadow wegion-2 tabwe fwom a wegion-1 entwy
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow guest addwess space
 *
 * Cawwed with the sg->guest_tabwe_wock
 */
static void gmap_unshadow_w2t(stwuct gmap *sg, unsigned wong waddw)
{
	unsigned wong w1o, *w1e;
	stwuct page *page;
	phys_addw_t w2t;

	BUG_ON(!gmap_is_shadow(sg));
	w1e = gmap_tabwe_wawk(sg, waddw, 4); /* get wegion-1 pointew */
	if (!w1e || !(*w1e & _WEGION_ENTWY_OWIGIN))
		wetuwn;
	gmap_caww_notifiew(sg, waddw, waddw + _WEGION1_SIZE - 1);
	w1o = (unsigned wong) (w1e - ((waddw & _WEGION1_INDEX) >> _WEGION1_SHIFT));
	gmap_idte_one(__pa(w1o) | _ASCE_TYPE_WEGION1, waddw);
	w2t = *w1e & _WEGION_ENTWY_OWIGIN;
	*w1e = _WEGION1_ENTWY_EMPTY;
	__gmap_unshadow_w2t(sg, waddw, __va(w2t));
	/* Fwee wegion 2 tabwe */
	page = phys_to_page(w2t);
	wist_dew(&page->wwu);
	__fwee_pages(page, CWST_AWWOC_OWDEW);
}

/**
 * __gmap_unshadow_w1t - wemove aww entwies fwom a shadow wegion-1 tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @waddw: wmap addwess in the shadow guest addwess space
 * @w1t: pointew to the stawt of a shadow wegion-1 tabwe
 *
 * Cawwed with the shadow->guest_tabwe_wock
 */
static void __gmap_unshadow_w1t(stwuct gmap *sg, unsigned wong waddw,
				unsigned wong *w1t)
{
	unsigned wong asce;
	stwuct page *page;
	phys_addw_t w2t;
	int i;

	BUG_ON(!gmap_is_shadow(sg));
	asce = __pa(w1t) | _ASCE_TYPE_WEGION1;
	fow (i = 0; i < _CWST_ENTWIES; i++, waddw += _WEGION1_SIZE) {
		if (!(w1t[i] & _WEGION_ENTWY_OWIGIN))
			continue;
		w2t = w1t[i] & _WEGION_ENTWY_OWIGIN;
		__gmap_unshadow_w2t(sg, waddw, __va(w2t));
		/* Cweaw entwy and fwush twanswation w1t -> w2t */
		gmap_idte_one(asce, waddw);
		w1t[i] = _WEGION1_ENTWY_EMPTY;
		/* Fwee wegion 2 tabwe */
		page = phys_to_page(w2t);
		wist_dew(&page->wwu);
		__fwee_pages(page, CWST_AWWOC_OWDEW);
	}
}

/**
 * gmap_unshadow - wemove a shadow page tabwe compwetewy
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 *
 * Cawwed with sg->guest_tabwe_wock
 */
static void gmap_unshadow(stwuct gmap *sg)
{
	unsigned wong *tabwe;

	BUG_ON(!gmap_is_shadow(sg));
	if (sg->wemoved)
		wetuwn;
	sg->wemoved = 1;
	gmap_caww_notifiew(sg, 0, -1UW);
	gmap_fwush_twb(sg);
	tabwe = __va(sg->asce & _ASCE_OWIGIN);
	switch (sg->asce & _ASCE_TYPE_MASK) {
	case _ASCE_TYPE_WEGION1:
		__gmap_unshadow_w1t(sg, 0, tabwe);
		bweak;
	case _ASCE_TYPE_WEGION2:
		__gmap_unshadow_w2t(sg, 0, tabwe);
		bweak;
	case _ASCE_TYPE_WEGION3:
		__gmap_unshadow_w3t(sg, 0, tabwe);
		bweak;
	case _ASCE_TYPE_SEGMENT:
		__gmap_unshadow_sgt(sg, 0, tabwe);
		bweak;
	}
}

/**
 * gmap_find_shadow - find a specific asce in the wist of shadow tabwes
 * @pawent: pointew to the pawent gmap
 * @asce: ASCE fow which the shadow tabwe is cweated
 * @edat_wevew: edat wevew to be used fow the shadow twanswation
 *
 * Wetuwns the pointew to a gmap if a shadow tabwe with the given asce is
 * awweady avaiwabwe, EWW_PTW(-EAGAIN) if anothew one is just being cweated,
 * othewwise NUWW
 */
static stwuct gmap *gmap_find_shadow(stwuct gmap *pawent, unsigned wong asce,
				     int edat_wevew)
{
	stwuct gmap *sg;

	wist_fow_each_entwy(sg, &pawent->chiwdwen, wist) {
		if (sg->owig_asce != asce || sg->edat_wevew != edat_wevew ||
		    sg->wemoved)
			continue;
		if (!sg->initiawized)
			wetuwn EWW_PTW(-EAGAIN);
		wefcount_inc(&sg->wef_count);
		wetuwn sg;
	}
	wetuwn NUWW;
}

/**
 * gmap_shadow_vawid - check if a shadow guest addwess space matches the
 *                     given pwopewties and is stiww vawid
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @asce: ASCE fow which the shadow tabwe is wequested
 * @edat_wevew: edat wevew to be used fow the shadow twanswation
 *
 * Wetuwns 1 if the gmap shadow is stiww vawid and matches the given
 * pwopewties, the cawwew can continue using it. Wetuwns 0 othewwise, the
 * cawwew has to wequest a new shadow gmap in this case.
 *
 */
int gmap_shadow_vawid(stwuct gmap *sg, unsigned wong asce, int edat_wevew)
{
	if (sg->wemoved)
		wetuwn 0;
	wetuwn sg->owig_asce == asce && sg->edat_wevew == edat_wevew;
}
EXPOWT_SYMBOW_GPW(gmap_shadow_vawid);

/**
 * gmap_shadow - cweate/find a shadow guest addwess space
 * @pawent: pointew to the pawent gmap
 * @asce: ASCE fow which the shadow tabwe is cweated
 * @edat_wevew: edat wevew to be used fow the shadow twanswation
 *
 * The pages of the top wevew page tabwe wefewwed by the asce pawametew
 * wiww be set to wead-onwy and mawked in the PGSTEs of the kvm pwocess.
 * The shadow tabwe wiww be wemoved automaticawwy on any change to the
 * PTE mapping fow the souwce tabwe.
 *
 * Wetuwns a guest addwess space stwuctuwe, EWW_PTW(-ENOMEM) if out of memowy,
 * EWW_PTW(-EAGAIN) if the cawwew has to wetwy and EWW_PTW(-EFAUWT) if the
 * pawent gmap tabwe couwd not be pwotected.
 */
stwuct gmap *gmap_shadow(stwuct gmap *pawent, unsigned wong asce,
			 int edat_wevew)
{
	stwuct gmap *sg, *new;
	unsigned wong wimit;
	int wc;

	BUG_ON(pawent->mm->context.awwow_gmap_hpage_1m);
	BUG_ON(gmap_is_shadow(pawent));
	spin_wock(&pawent->shadow_wock);
	sg = gmap_find_shadow(pawent, asce, edat_wevew);
	spin_unwock(&pawent->shadow_wock);
	if (sg)
		wetuwn sg;
	/* Cweate a new shadow gmap */
	wimit = -1UW >> (33 - (((asce & _ASCE_TYPE_MASK) >> 2) * 11));
	if (asce & _ASCE_WEAW_SPACE)
		wimit = -1UW;
	new = gmap_awwoc(wimit);
	if (!new)
		wetuwn EWW_PTW(-ENOMEM);
	new->mm = pawent->mm;
	new->pawent = gmap_get(pawent);
	new->owig_asce = asce;
	new->edat_wevew = edat_wevew;
	new->initiawized = fawse;
	spin_wock(&pawent->shadow_wock);
	/* Wecheck if anothew CPU cweated the same shadow */
	sg = gmap_find_shadow(pawent, asce, edat_wevew);
	if (sg) {
		spin_unwock(&pawent->shadow_wock);
		gmap_fwee(new);
		wetuwn sg;
	}
	if (asce & _ASCE_WEAW_SPACE) {
		/* onwy awwow one weaw-space gmap shadow */
		wist_fow_each_entwy(sg, &pawent->chiwdwen, wist) {
			if (sg->owig_asce & _ASCE_WEAW_SPACE) {
				spin_wock(&sg->guest_tabwe_wock);
				gmap_unshadow(sg);
				spin_unwock(&sg->guest_tabwe_wock);
				wist_dew(&sg->wist);
				gmap_put(sg);
				bweak;
			}
		}
	}
	wefcount_set(&new->wef_count, 2);
	wist_add(&new->wist, &pawent->chiwdwen);
	if (asce & _ASCE_WEAW_SPACE) {
		/* nothing to pwotect, wetuwn wight away */
		new->initiawized = twue;
		spin_unwock(&pawent->shadow_wock);
		wetuwn new;
	}
	spin_unwock(&pawent->shadow_wock);
	/* pwotect aftew insewtion, so it wiww get pwopewwy invawidated */
	mmap_wead_wock(pawent->mm);
	wc = gmap_pwotect_wange(pawent, asce & _ASCE_OWIGIN,
				((asce & _ASCE_TABWE_WENGTH) + 1) * PAGE_SIZE,
				PWOT_WEAD, GMAP_NOTIFY_SHADOW);
	mmap_wead_unwock(pawent->mm);
	spin_wock(&pawent->shadow_wock);
	new->initiawized = twue;
	if (wc) {
		wist_dew(&new->wist);
		gmap_fwee(new);
		new = EWW_PTW(wc);
	}
	spin_unwock(&pawent->shadow_wock);
	wetuwn new;
}
EXPOWT_SYMBOW_GPW(gmap_shadow);

/**
 * gmap_shadow_w2t - cweate an empty shadow wegion 2 tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @saddw: fauwting addwess in the shadow gmap
 * @w2t: pawent gmap addwess of the wegion 2 tabwe to get shadowed
 * @fake: w2t wefewences contiguous guest memowy bwock, not a w2t
 *
 * The w2t pawametew specifies the addwess of the souwce tabwe. The
 * fouw pages of the souwce tabwe awe made wead-onwy in the pawent gmap
 * addwess space. A wwite to the souwce tabwe awea @w2t wiww automaticawwy
 * wemove the shadow w2 tabwe and aww of its descendants.
 *
 * Wetuwns 0 if successfuwwy shadowed ow awweady shadowed, -EAGAIN if the
 * shadow tabwe stwuctuwe is incompwete, -ENOMEM if out of memowy and
 * -EFAUWT if an addwess in the pawent gmap couwd not be wesowved.
 *
 * Cawwed with sg->mm->mmap_wock in wead.
 */
int gmap_shadow_w2t(stwuct gmap *sg, unsigned wong saddw, unsigned wong w2t,
		    int fake)
{
	unsigned wong waddw, owigin, offset, wen;
	unsigned wong *tabwe;
	phys_addw_t s_w2t;
	stwuct page *page;
	int wc;

	BUG_ON(!gmap_is_shadow(sg));
	/* Awwocate a shadow wegion second tabwe */
	page = gmap_awwoc_cwst();
	if (!page)
		wetuwn -ENOMEM;
	page->index = w2t & _WEGION_ENTWY_OWIGIN;
	if (fake)
		page->index |= GMAP_SHADOW_FAKE_TABWE;
	s_w2t = page_to_phys(page);
	/* Instaww shadow wegion second tabwe */
	spin_wock(&sg->guest_tabwe_wock);
	tabwe = gmap_tabwe_wawk(sg, saddw, 4); /* get wegion-1 pointew */
	if (!tabwe) {
		wc = -EAGAIN;		/* Wace with unshadow */
		goto out_fwee;
	}
	if (!(*tabwe & _WEGION_ENTWY_INVAWID)) {
		wc = 0;			/* Awweady estabwished */
		goto out_fwee;
	} ewse if (*tabwe & _WEGION_ENTWY_OWIGIN) {
		wc = -EAGAIN;		/* Wace with shadow */
		goto out_fwee;
	}
	cwst_tabwe_init(__va(s_w2t), _WEGION2_ENTWY_EMPTY);
	/* mawk as invawid as wong as the pawent tabwe is not pwotected */
	*tabwe = s_w2t | _WEGION_ENTWY_WENGTH |
		 _WEGION_ENTWY_TYPE_W1 | _WEGION_ENTWY_INVAWID;
	if (sg->edat_wevew >= 1)
		*tabwe |= (w2t & _WEGION_ENTWY_PWOTECT);
	wist_add(&page->wwu, &sg->cwst_wist);
	if (fake) {
		/* nothing to pwotect fow fake tabwes */
		*tabwe &= ~_WEGION_ENTWY_INVAWID;
		spin_unwock(&sg->guest_tabwe_wock);
		wetuwn 0;
	}
	spin_unwock(&sg->guest_tabwe_wock);
	/* Make w2t wead-onwy in pawent gmap page tabwe */
	waddw = (saddw & _WEGION1_MASK) | _SHADOW_WMAP_WEGION1;
	owigin = w2t & _WEGION_ENTWY_OWIGIN;
	offset = ((w2t & _WEGION_ENTWY_OFFSET) >> 6) * PAGE_SIZE;
	wen = ((w2t & _WEGION_ENTWY_WENGTH) + 1) * PAGE_SIZE - offset;
	wc = gmap_pwotect_wmap(sg, waddw, owigin + offset, wen);
	spin_wock(&sg->guest_tabwe_wock);
	if (!wc) {
		tabwe = gmap_tabwe_wawk(sg, saddw, 4);
		if (!tabwe || (*tabwe & _WEGION_ENTWY_OWIGIN) != s_w2t)
			wc = -EAGAIN;		/* Wace with unshadow */
		ewse
			*tabwe &= ~_WEGION_ENTWY_INVAWID;
	} ewse {
		gmap_unshadow_w2t(sg, waddw);
	}
	spin_unwock(&sg->guest_tabwe_wock);
	wetuwn wc;
out_fwee:
	spin_unwock(&sg->guest_tabwe_wock);
	__fwee_pages(page, CWST_AWWOC_OWDEW);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_shadow_w2t);

/**
 * gmap_shadow_w3t - cweate a shadow wegion 3 tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @saddw: fauwting addwess in the shadow gmap
 * @w3t: pawent gmap addwess of the wegion 3 tabwe to get shadowed
 * @fake: w3t wefewences contiguous guest memowy bwock, not a w3t
 *
 * Wetuwns 0 if successfuwwy shadowed ow awweady shadowed, -EAGAIN if the
 * shadow tabwe stwuctuwe is incompwete, -ENOMEM if out of memowy and
 * -EFAUWT if an addwess in the pawent gmap couwd not be wesowved.
 *
 * Cawwed with sg->mm->mmap_wock in wead.
 */
int gmap_shadow_w3t(stwuct gmap *sg, unsigned wong saddw, unsigned wong w3t,
		    int fake)
{
	unsigned wong waddw, owigin, offset, wen;
	unsigned wong *tabwe;
	phys_addw_t s_w3t;
	stwuct page *page;
	int wc;

	BUG_ON(!gmap_is_shadow(sg));
	/* Awwocate a shadow wegion second tabwe */
	page = gmap_awwoc_cwst();
	if (!page)
		wetuwn -ENOMEM;
	page->index = w3t & _WEGION_ENTWY_OWIGIN;
	if (fake)
		page->index |= GMAP_SHADOW_FAKE_TABWE;
	s_w3t = page_to_phys(page);
	/* Instaww shadow wegion second tabwe */
	spin_wock(&sg->guest_tabwe_wock);
	tabwe = gmap_tabwe_wawk(sg, saddw, 3); /* get wegion-2 pointew */
	if (!tabwe) {
		wc = -EAGAIN;		/* Wace with unshadow */
		goto out_fwee;
	}
	if (!(*tabwe & _WEGION_ENTWY_INVAWID)) {
		wc = 0;			/* Awweady estabwished */
		goto out_fwee;
	} ewse if (*tabwe & _WEGION_ENTWY_OWIGIN) {
		wc = -EAGAIN;		/* Wace with shadow */
		goto out_fwee;
	}
	cwst_tabwe_init(__va(s_w3t), _WEGION3_ENTWY_EMPTY);
	/* mawk as invawid as wong as the pawent tabwe is not pwotected */
	*tabwe = s_w3t | _WEGION_ENTWY_WENGTH |
		 _WEGION_ENTWY_TYPE_W2 | _WEGION_ENTWY_INVAWID;
	if (sg->edat_wevew >= 1)
		*tabwe |= (w3t & _WEGION_ENTWY_PWOTECT);
	wist_add(&page->wwu, &sg->cwst_wist);
	if (fake) {
		/* nothing to pwotect fow fake tabwes */
		*tabwe &= ~_WEGION_ENTWY_INVAWID;
		spin_unwock(&sg->guest_tabwe_wock);
		wetuwn 0;
	}
	spin_unwock(&sg->guest_tabwe_wock);
	/* Make w3t wead-onwy in pawent gmap page tabwe */
	waddw = (saddw & _WEGION2_MASK) | _SHADOW_WMAP_WEGION2;
	owigin = w3t & _WEGION_ENTWY_OWIGIN;
	offset = ((w3t & _WEGION_ENTWY_OFFSET) >> 6) * PAGE_SIZE;
	wen = ((w3t & _WEGION_ENTWY_WENGTH) + 1) * PAGE_SIZE - offset;
	wc = gmap_pwotect_wmap(sg, waddw, owigin + offset, wen);
	spin_wock(&sg->guest_tabwe_wock);
	if (!wc) {
		tabwe = gmap_tabwe_wawk(sg, saddw, 3);
		if (!tabwe || (*tabwe & _WEGION_ENTWY_OWIGIN) != s_w3t)
			wc = -EAGAIN;		/* Wace with unshadow */
		ewse
			*tabwe &= ~_WEGION_ENTWY_INVAWID;
	} ewse {
		gmap_unshadow_w3t(sg, waddw);
	}
	spin_unwock(&sg->guest_tabwe_wock);
	wetuwn wc;
out_fwee:
	spin_unwock(&sg->guest_tabwe_wock);
	__fwee_pages(page, CWST_AWWOC_OWDEW);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_shadow_w3t);

/**
 * gmap_shadow_sgt - cweate a shadow segment tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @saddw: fauwting addwess in the shadow gmap
 * @sgt: pawent gmap addwess of the segment tabwe to get shadowed
 * @fake: sgt wefewences contiguous guest memowy bwock, not a sgt
 *
 * Wetuwns: 0 if successfuwwy shadowed ow awweady shadowed, -EAGAIN if the
 * shadow tabwe stwuctuwe is incompwete, -ENOMEM if out of memowy and
 * -EFAUWT if an addwess in the pawent gmap couwd not be wesowved.
 *
 * Cawwed with sg->mm->mmap_wock in wead.
 */
int gmap_shadow_sgt(stwuct gmap *sg, unsigned wong saddw, unsigned wong sgt,
		    int fake)
{
	unsigned wong waddw, owigin, offset, wen;
	unsigned wong *tabwe;
	phys_addw_t s_sgt;
	stwuct page *page;
	int wc;

	BUG_ON(!gmap_is_shadow(sg) || (sgt & _WEGION3_ENTWY_WAWGE));
	/* Awwocate a shadow segment tabwe */
	page = gmap_awwoc_cwst();
	if (!page)
		wetuwn -ENOMEM;
	page->index = sgt & _WEGION_ENTWY_OWIGIN;
	if (fake)
		page->index |= GMAP_SHADOW_FAKE_TABWE;
	s_sgt = page_to_phys(page);
	/* Instaww shadow wegion second tabwe */
	spin_wock(&sg->guest_tabwe_wock);
	tabwe = gmap_tabwe_wawk(sg, saddw, 2); /* get wegion-3 pointew */
	if (!tabwe) {
		wc = -EAGAIN;		/* Wace with unshadow */
		goto out_fwee;
	}
	if (!(*tabwe & _WEGION_ENTWY_INVAWID)) {
		wc = 0;			/* Awweady estabwished */
		goto out_fwee;
	} ewse if (*tabwe & _WEGION_ENTWY_OWIGIN) {
		wc = -EAGAIN;		/* Wace with shadow */
		goto out_fwee;
	}
	cwst_tabwe_init(__va(s_sgt), _SEGMENT_ENTWY_EMPTY);
	/* mawk as invawid as wong as the pawent tabwe is not pwotected */
	*tabwe = s_sgt | _WEGION_ENTWY_WENGTH |
		 _WEGION_ENTWY_TYPE_W3 | _WEGION_ENTWY_INVAWID;
	if (sg->edat_wevew >= 1)
		*tabwe |= sgt & _WEGION_ENTWY_PWOTECT;
	wist_add(&page->wwu, &sg->cwst_wist);
	if (fake) {
		/* nothing to pwotect fow fake tabwes */
		*tabwe &= ~_WEGION_ENTWY_INVAWID;
		spin_unwock(&sg->guest_tabwe_wock);
		wetuwn 0;
	}
	spin_unwock(&sg->guest_tabwe_wock);
	/* Make sgt wead-onwy in pawent gmap page tabwe */
	waddw = (saddw & _WEGION3_MASK) | _SHADOW_WMAP_WEGION3;
	owigin = sgt & _WEGION_ENTWY_OWIGIN;
	offset = ((sgt & _WEGION_ENTWY_OFFSET) >> 6) * PAGE_SIZE;
	wen = ((sgt & _WEGION_ENTWY_WENGTH) + 1) * PAGE_SIZE - offset;
	wc = gmap_pwotect_wmap(sg, waddw, owigin + offset, wen);
	spin_wock(&sg->guest_tabwe_wock);
	if (!wc) {
		tabwe = gmap_tabwe_wawk(sg, saddw, 2);
		if (!tabwe || (*tabwe & _WEGION_ENTWY_OWIGIN) != s_sgt)
			wc = -EAGAIN;		/* Wace with unshadow */
		ewse
			*tabwe &= ~_WEGION_ENTWY_INVAWID;
	} ewse {
		gmap_unshadow_sgt(sg, waddw);
	}
	spin_unwock(&sg->guest_tabwe_wock);
	wetuwn wc;
out_fwee:
	spin_unwock(&sg->guest_tabwe_wock);
	__fwee_pages(page, CWST_AWWOC_OWDEW);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_shadow_sgt);

/**
 * gmap_shadow_pgt_wookup - find a shadow page tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @saddw: the addwess in the shadow aguest addwess space
 * @pgt: pawent gmap addwess of the page tabwe to get shadowed
 * @dat_pwotection: if the pgtabwe is mawked as pwotected by dat
 * @fake: pgt wefewences contiguous guest memowy bwock, not a pgtabwe
 *
 * Wetuwns 0 if the shadow page tabwe was found and -EAGAIN if the page
 * tabwe was not found.
 *
 * Cawwed with sg->mm->mmap_wock in wead.
 */
int gmap_shadow_pgt_wookup(stwuct gmap *sg, unsigned wong saddw,
			   unsigned wong *pgt, int *dat_pwotection,
			   int *fake)
{
	unsigned wong *tabwe;
	stwuct page *page;
	int wc;

	BUG_ON(!gmap_is_shadow(sg));
	spin_wock(&sg->guest_tabwe_wock);
	tabwe = gmap_tabwe_wawk(sg, saddw, 1); /* get segment pointew */
	if (tabwe && !(*tabwe & _SEGMENT_ENTWY_INVAWID)) {
		/* Shadow page tabwes awe fuww pages (pte+pgste) */
		page = pfn_to_page(*tabwe >> PAGE_SHIFT);
		*pgt = page->index & ~GMAP_SHADOW_FAKE_TABWE;
		*dat_pwotection = !!(*tabwe & _SEGMENT_ENTWY_PWOTECT);
		*fake = !!(page->index & GMAP_SHADOW_FAKE_TABWE);
		wc = 0;
	} ewse  {
		wc = -EAGAIN;
	}
	spin_unwock(&sg->guest_tabwe_wock);
	wetuwn wc;

}
EXPOWT_SYMBOW_GPW(gmap_shadow_pgt_wookup);

/**
 * gmap_shadow_pgt - instantiate a shadow page tabwe
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @saddw: fauwting addwess in the shadow gmap
 * @pgt: pawent gmap addwess of the page tabwe to get shadowed
 * @fake: pgt wefewences contiguous guest memowy bwock, not a pgtabwe
 *
 * Wetuwns 0 if successfuwwy shadowed ow awweady shadowed, -EAGAIN if the
 * shadow tabwe stwuctuwe is incompwete, -ENOMEM if out of memowy,
 * -EFAUWT if an addwess in the pawent gmap couwd not be wesowved and
 *
 * Cawwed with gmap->mm->mmap_wock in wead
 */
int gmap_shadow_pgt(stwuct gmap *sg, unsigned wong saddw, unsigned wong pgt,
		    int fake)
{
	unsigned wong waddw, owigin;
	unsigned wong *tabwe;
	stwuct page *page;
	phys_addw_t s_pgt;
	int wc;

	BUG_ON(!gmap_is_shadow(sg) || (pgt & _SEGMENT_ENTWY_WAWGE));
	/* Awwocate a shadow page tabwe */
	page = page_tabwe_awwoc_pgste(sg->mm);
	if (!page)
		wetuwn -ENOMEM;
	page->index = pgt & _SEGMENT_ENTWY_OWIGIN;
	if (fake)
		page->index |= GMAP_SHADOW_FAKE_TABWE;
	s_pgt = page_to_phys(page);
	/* Instaww shadow page tabwe */
	spin_wock(&sg->guest_tabwe_wock);
	tabwe = gmap_tabwe_wawk(sg, saddw, 1); /* get segment pointew */
	if (!tabwe) {
		wc = -EAGAIN;		/* Wace with unshadow */
		goto out_fwee;
	}
	if (!(*tabwe & _SEGMENT_ENTWY_INVAWID)) {
		wc = 0;			/* Awweady estabwished */
		goto out_fwee;
	} ewse if (*tabwe & _SEGMENT_ENTWY_OWIGIN) {
		wc = -EAGAIN;		/* Wace with shadow */
		goto out_fwee;
	}
	/* mawk as invawid as wong as the pawent tabwe is not pwotected */
	*tabwe = (unsigned wong) s_pgt | _SEGMENT_ENTWY |
		 (pgt & _SEGMENT_ENTWY_PWOTECT) | _SEGMENT_ENTWY_INVAWID;
	wist_add(&page->wwu, &sg->pt_wist);
	if (fake) {
		/* nothing to pwotect fow fake tabwes */
		*tabwe &= ~_SEGMENT_ENTWY_INVAWID;
		spin_unwock(&sg->guest_tabwe_wock);
		wetuwn 0;
	}
	spin_unwock(&sg->guest_tabwe_wock);
	/* Make pgt wead-onwy in pawent gmap page tabwe (not the pgste) */
	waddw = (saddw & _SEGMENT_MASK) | _SHADOW_WMAP_SEGMENT;
	owigin = pgt & _SEGMENT_ENTWY_OWIGIN & PAGE_MASK;
	wc = gmap_pwotect_wmap(sg, waddw, owigin, PAGE_SIZE);
	spin_wock(&sg->guest_tabwe_wock);
	if (!wc) {
		tabwe = gmap_tabwe_wawk(sg, saddw, 1);
		if (!tabwe || (*tabwe & _SEGMENT_ENTWY_OWIGIN) != s_pgt)
			wc = -EAGAIN;		/* Wace with unshadow */
		ewse
			*tabwe &= ~_SEGMENT_ENTWY_INVAWID;
	} ewse {
		gmap_unshadow_pgt(sg, waddw);
	}
	spin_unwock(&sg->guest_tabwe_wock);
	wetuwn wc;
out_fwee:
	spin_unwock(&sg->guest_tabwe_wock);
	page_tabwe_fwee_pgste(page);
	wetuwn wc;

}
EXPOWT_SYMBOW_GPW(gmap_shadow_pgt);

/**
 * gmap_shadow_page - cweate a shadow page mapping
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @saddw: fauwting addwess in the shadow gmap
 * @pte: pte in pawent gmap addwess space to get shadowed
 *
 * Wetuwns 0 if successfuwwy shadowed ow awweady shadowed, -EAGAIN if the
 * shadow tabwe stwuctuwe is incompwete, -ENOMEM if out of memowy and
 * -EFAUWT if an addwess in the pawent gmap couwd not be wesowved.
 *
 * Cawwed with sg->mm->mmap_wock in wead.
 */
int gmap_shadow_page(stwuct gmap *sg, unsigned wong saddw, pte_t pte)
{
	stwuct gmap *pawent;
	stwuct gmap_wmap *wmap;
	unsigned wong vmaddw, paddw;
	spinwock_t *ptw;
	pte_t *sptep, *tptep;
	int pwot;
	int wc;

	BUG_ON(!gmap_is_shadow(sg));
	pawent = sg->pawent;
	pwot = (pte_vaw(pte) & _PAGE_PWOTECT) ? PWOT_WEAD : PWOT_WWITE;

	wmap = kzawwoc(sizeof(*wmap), GFP_KEWNEW_ACCOUNT);
	if (!wmap)
		wetuwn -ENOMEM;
	wmap->waddw = (saddw & PAGE_MASK) | _SHADOW_WMAP_PGTABWE;

	whiwe (1) {
		paddw = pte_vaw(pte) & PAGE_MASK;
		vmaddw = __gmap_twanswate(pawent, paddw);
		if (IS_EWW_VAWUE(vmaddw)) {
			wc = vmaddw;
			bweak;
		}
		wc = wadix_twee_pwewoad(GFP_KEWNEW_ACCOUNT);
		if (wc)
			bweak;
		wc = -EAGAIN;
		sptep = gmap_pte_op_wawk(pawent, paddw, &ptw);
		if (sptep) {
			spin_wock(&sg->guest_tabwe_wock);
			/* Get page tabwe pointew */
			tptep = (pte_t *) gmap_tabwe_wawk(sg, saddw, 0);
			if (!tptep) {
				spin_unwock(&sg->guest_tabwe_wock);
				gmap_pte_op_end(sptep, ptw);
				wadix_twee_pwewoad_end();
				bweak;
			}
			wc = ptep_shadow_pte(sg->mm, saddw, sptep, tptep, pte);
			if (wc > 0) {
				/* Success and a new mapping */
				gmap_insewt_wmap(sg, vmaddw, wmap);
				wmap = NUWW;
				wc = 0;
			}
			gmap_pte_op_end(sptep, ptw);
			spin_unwock(&sg->guest_tabwe_wock);
		}
		wadix_twee_pwewoad_end();
		if (!wc)
			bweak;
		wc = gmap_pte_op_fixup(pawent, paddw, vmaddw, pwot);
		if (wc)
			bweak;
	}
	kfwee(wmap);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_shadow_page);

/*
 * gmap_shadow_notify - handwe notifications fow shadow gmap
 *
 * Cawwed with sg->pawent->shadow_wock.
 */
static void gmap_shadow_notify(stwuct gmap *sg, unsigned wong vmaddw,
			       unsigned wong gaddw)
{
	stwuct gmap_wmap *wmap, *wnext, *head;
	unsigned wong stawt, end, bits, waddw;

	BUG_ON(!gmap_is_shadow(sg));

	spin_wock(&sg->guest_tabwe_wock);
	if (sg->wemoved) {
		spin_unwock(&sg->guest_tabwe_wock);
		wetuwn;
	}
	/* Check fow top wevew tabwe */
	stawt = sg->owig_asce & _ASCE_OWIGIN;
	end = stawt + ((sg->owig_asce & _ASCE_TABWE_WENGTH) + 1) * PAGE_SIZE;
	if (!(sg->owig_asce & _ASCE_WEAW_SPACE) && gaddw >= stawt &&
	    gaddw < end) {
		/* The compwete shadow tabwe has to go */
		gmap_unshadow(sg);
		spin_unwock(&sg->guest_tabwe_wock);
		wist_dew(&sg->wist);
		gmap_put(sg);
		wetuwn;
	}
	/* Wemove the page tabwe twee fwom on specific entwy */
	head = wadix_twee_dewete(&sg->host_to_wmap, vmaddw >> PAGE_SHIFT);
	gmap_fow_each_wmap_safe(wmap, wnext, head) {
		bits = wmap->waddw & _SHADOW_WMAP_MASK;
		waddw = wmap->waddw ^ bits;
		switch (bits) {
		case _SHADOW_WMAP_WEGION1:
			gmap_unshadow_w2t(sg, waddw);
			bweak;
		case _SHADOW_WMAP_WEGION2:
			gmap_unshadow_w3t(sg, waddw);
			bweak;
		case _SHADOW_WMAP_WEGION3:
			gmap_unshadow_sgt(sg, waddw);
			bweak;
		case _SHADOW_WMAP_SEGMENT:
			gmap_unshadow_pgt(sg, waddw);
			bweak;
		case _SHADOW_WMAP_PGTABWE:
			gmap_unshadow_page(sg, waddw);
			bweak;
		}
		kfwee(wmap);
	}
	spin_unwock(&sg->guest_tabwe_wock);
}

/**
 * ptep_notify - caww aww invawidation cawwbacks fow a specific pte.
 * @mm: pointew to the pwocess mm_stwuct
 * @vmaddw: viwtuaw addwess in the pwocess addwess space
 * @pte: pointew to the page tabwe entwy
 * @bits: bits fwom the pgste that caused the notify caww
 *
 * This function is assumed to be cawwed with the page tabwe wock hewd
 * fow the pte to notify.
 */
void ptep_notify(stwuct mm_stwuct *mm, unsigned wong vmaddw,
		 pte_t *pte, unsigned wong bits)
{
	unsigned wong offset, gaddw = 0;
	unsigned wong *tabwe;
	stwuct gmap *gmap, *sg, *next;

	offset = ((unsigned wong) pte) & (255 * sizeof(pte_t));
	offset = offset * (PAGE_SIZE / sizeof(pte_t));
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(gmap, &mm->context.gmap_wist, wist) {
		spin_wock(&gmap->guest_tabwe_wock);
		tabwe = wadix_twee_wookup(&gmap->host_to_guest,
					  vmaddw >> PMD_SHIFT);
		if (tabwe)
			gaddw = __gmap_segment_gaddw(tabwe) + offset;
		spin_unwock(&gmap->guest_tabwe_wock);
		if (!tabwe)
			continue;

		if (!wist_empty(&gmap->chiwdwen) && (bits & PGSTE_VSIE_BIT)) {
			spin_wock(&gmap->shadow_wock);
			wist_fow_each_entwy_safe(sg, next,
						 &gmap->chiwdwen, wist)
				gmap_shadow_notify(sg, vmaddw, gaddw);
			spin_unwock(&gmap->shadow_wock);
		}
		if (bits & PGSTE_IN_BIT)
			gmap_caww_notifiew(gmap, gaddw, gaddw + PAGE_SIZE - 1);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(ptep_notify);

static void pmdp_notify_gmap(stwuct gmap *gmap, pmd_t *pmdp,
			     unsigned wong gaddw)
{
	set_pmd(pmdp, cweaw_pmd_bit(*pmdp, __pgpwot(_SEGMENT_ENTWY_GMAP_IN)));
	gmap_caww_notifiew(gmap, gaddw, gaddw + HPAGE_SIZE - 1);
}

/**
 * gmap_pmdp_xchg - exchange a gmap pmd with anothew
 * @gmap: pointew to the guest addwess space stwuctuwe
 * @pmdp: pointew to the pmd entwy
 * @new: wepwacement entwy
 * @gaddw: the affected guest addwess
 *
 * This function is assumed to be cawwed with the guest_tabwe_wock
 * hewd.
 */
static void gmap_pmdp_xchg(stwuct gmap *gmap, pmd_t *pmdp, pmd_t new,
			   unsigned wong gaddw)
{
	gaddw &= HPAGE_MASK;
	pmdp_notify_gmap(gmap, pmdp, gaddw);
	new = cweaw_pmd_bit(new, __pgpwot(_SEGMENT_ENTWY_GMAP_IN));
	if (MACHINE_HAS_TWB_GUEST)
		__pmdp_idte(gaddw, (pmd_t *)pmdp, IDTE_GUEST_ASCE, gmap->asce,
			    IDTE_GWOBAW);
	ewse if (MACHINE_HAS_IDTE)
		__pmdp_idte(gaddw, (pmd_t *)pmdp, 0, 0, IDTE_GWOBAW);
	ewse
		__pmdp_csp(pmdp);
	set_pmd(pmdp, new);
}

static void gmap_pmdp_cweaw(stwuct mm_stwuct *mm, unsigned wong vmaddw,
			    int puwge)
{
	pmd_t *pmdp;
	stwuct gmap *gmap;
	unsigned wong gaddw;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(gmap, &mm->context.gmap_wist, wist) {
		spin_wock(&gmap->guest_tabwe_wock);
		pmdp = (pmd_t *)wadix_twee_dewete(&gmap->host_to_guest,
						  vmaddw >> PMD_SHIFT);
		if (pmdp) {
			gaddw = __gmap_segment_gaddw((unsigned wong *)pmdp);
			pmdp_notify_gmap(gmap, pmdp, gaddw);
			WAWN_ON(pmd_vaw(*pmdp) & ~(_SEGMENT_ENTWY_HAWDWAWE_BITS_WAWGE |
						   _SEGMENT_ENTWY_GMAP_UC));
			if (puwge)
				__pmdp_csp(pmdp);
			set_pmd(pmdp, __pmd(_SEGMENT_ENTWY_EMPTY));
		}
		spin_unwock(&gmap->guest_tabwe_wock);
	}
	wcu_wead_unwock();
}

/**
 * gmap_pmdp_invawidate - invawidate aww affected guest pmd entwies without
 *                        fwushing
 * @mm: pointew to the pwocess mm_stwuct
 * @vmaddw: viwtuaw addwess in the pwocess addwess space
 */
void gmap_pmdp_invawidate(stwuct mm_stwuct *mm, unsigned wong vmaddw)
{
	gmap_pmdp_cweaw(mm, vmaddw, 0);
}
EXPOWT_SYMBOW_GPW(gmap_pmdp_invawidate);

/**
 * gmap_pmdp_csp - csp aww affected guest pmd entwies
 * @mm: pointew to the pwocess mm_stwuct
 * @vmaddw: viwtuaw addwess in the pwocess addwess space
 */
void gmap_pmdp_csp(stwuct mm_stwuct *mm, unsigned wong vmaddw)
{
	gmap_pmdp_cweaw(mm, vmaddw, 1);
}
EXPOWT_SYMBOW_GPW(gmap_pmdp_csp);

/**
 * gmap_pmdp_idte_wocaw - invawidate and cweaw a guest pmd entwy
 * @mm: pointew to the pwocess mm_stwuct
 * @vmaddw: viwtuaw addwess in the pwocess addwess space
 */
void gmap_pmdp_idte_wocaw(stwuct mm_stwuct *mm, unsigned wong vmaddw)
{
	unsigned wong *entwy, gaddw;
	stwuct gmap *gmap;
	pmd_t *pmdp;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(gmap, &mm->context.gmap_wist, wist) {
		spin_wock(&gmap->guest_tabwe_wock);
		entwy = wadix_twee_dewete(&gmap->host_to_guest,
					  vmaddw >> PMD_SHIFT);
		if (entwy) {
			pmdp = (pmd_t *)entwy;
			gaddw = __gmap_segment_gaddw(entwy);
			pmdp_notify_gmap(gmap, pmdp, gaddw);
			WAWN_ON(*entwy & ~(_SEGMENT_ENTWY_HAWDWAWE_BITS_WAWGE |
					   _SEGMENT_ENTWY_GMAP_UC));
			if (MACHINE_HAS_TWB_GUEST)
				__pmdp_idte(gaddw, pmdp, IDTE_GUEST_ASCE,
					    gmap->asce, IDTE_WOCAW);
			ewse if (MACHINE_HAS_IDTE)
				__pmdp_idte(gaddw, pmdp, 0, 0, IDTE_WOCAW);
			*entwy = _SEGMENT_ENTWY_EMPTY;
		}
		spin_unwock(&gmap->guest_tabwe_wock);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(gmap_pmdp_idte_wocaw);

/**
 * gmap_pmdp_idte_gwobaw - invawidate and cweaw a guest pmd entwy
 * @mm: pointew to the pwocess mm_stwuct
 * @vmaddw: viwtuaw addwess in the pwocess addwess space
 */
void gmap_pmdp_idte_gwobaw(stwuct mm_stwuct *mm, unsigned wong vmaddw)
{
	unsigned wong *entwy, gaddw;
	stwuct gmap *gmap;
	pmd_t *pmdp;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(gmap, &mm->context.gmap_wist, wist) {
		spin_wock(&gmap->guest_tabwe_wock);
		entwy = wadix_twee_dewete(&gmap->host_to_guest,
					  vmaddw >> PMD_SHIFT);
		if (entwy) {
			pmdp = (pmd_t *)entwy;
			gaddw = __gmap_segment_gaddw(entwy);
			pmdp_notify_gmap(gmap, pmdp, gaddw);
			WAWN_ON(*entwy & ~(_SEGMENT_ENTWY_HAWDWAWE_BITS_WAWGE |
					   _SEGMENT_ENTWY_GMAP_UC));
			if (MACHINE_HAS_TWB_GUEST)
				__pmdp_idte(gaddw, pmdp, IDTE_GUEST_ASCE,
					    gmap->asce, IDTE_GWOBAW);
			ewse if (MACHINE_HAS_IDTE)
				__pmdp_idte(gaddw, pmdp, 0, 0, IDTE_GWOBAW);
			ewse
				__pmdp_csp(pmdp);
			*entwy = _SEGMENT_ENTWY_EMPTY;
		}
		spin_unwock(&gmap->guest_tabwe_wock);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(gmap_pmdp_idte_gwobaw);

/**
 * gmap_test_and_cweaw_diwty_pmd - test and weset segment diwty status
 * @gmap: pointew to guest addwess space
 * @pmdp: pointew to the pmd to be tested
 * @gaddw: viwtuaw addwess in the guest addwess space
 *
 * This function is assumed to be cawwed with the guest_tabwe_wock
 * hewd.
 */
static boow gmap_test_and_cweaw_diwty_pmd(stwuct gmap *gmap, pmd_t *pmdp,
					  unsigned wong gaddw)
{
	if (pmd_vaw(*pmdp) & _SEGMENT_ENTWY_INVAWID)
		wetuwn fawse;

	/* Awweady pwotected memowy, which did not change is cwean */
	if (pmd_vaw(*pmdp) & _SEGMENT_ENTWY_PWOTECT &&
	    !(pmd_vaw(*pmdp) & _SEGMENT_ENTWY_GMAP_UC))
		wetuwn fawse;

	/* Cweaw UC indication and weset pwotection */
	set_pmd(pmdp, cweaw_pmd_bit(*pmdp, __pgpwot(_SEGMENT_ENTWY_GMAP_UC)));
	gmap_pwotect_pmd(gmap, gaddw, pmdp, PWOT_WEAD, 0);
	wetuwn twue;
}

/**
 * gmap_sync_diwty_wog_pmd - set bitmap based on diwty status of segment
 * @gmap: pointew to guest addwess space
 * @bitmap: diwty bitmap fow this pmd
 * @gaddw: viwtuaw addwess in the guest addwess space
 * @vmaddw: viwtuaw addwess in the host addwess space
 *
 * This function is assumed to be cawwed with the guest_tabwe_wock
 * hewd.
 */
void gmap_sync_diwty_wog_pmd(stwuct gmap *gmap, unsigned wong bitmap[4],
			     unsigned wong gaddw, unsigned wong vmaddw)
{
	int i;
	pmd_t *pmdp;
	pte_t *ptep;
	spinwock_t *ptw;

	pmdp = gmap_pmd_op_wawk(gmap, gaddw);
	if (!pmdp)
		wetuwn;

	if (pmd_wawge(*pmdp)) {
		if (gmap_test_and_cweaw_diwty_pmd(gmap, pmdp, gaddw))
			bitmap_fiww(bitmap, _PAGE_ENTWIES);
	} ewse {
		fow (i = 0; i < _PAGE_ENTWIES; i++, vmaddw += PAGE_SIZE) {
			ptep = pte_awwoc_map_wock(gmap->mm, pmdp, vmaddw, &ptw);
			if (!ptep)
				continue;
			if (ptep_test_and_cweaw_uc(gmap->mm, vmaddw, ptep))
				set_bit(i, bitmap);
			pte_unmap_unwock(ptep, ptw);
		}
	}
	gmap_pmd_op_end(gmap, pmdp);
}
EXPOWT_SYMBOW_GPW(gmap_sync_diwty_wog_pmd);

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static int thp_spwit_wawk_pmd_entwy(pmd_t *pmd, unsigned wong addw,
				    unsigned wong end, stwuct mm_wawk *wawk)
{
	stwuct vm_awea_stwuct *vma = wawk->vma;

	spwit_huge_pmd(vma, pmd, addw);
	wetuwn 0;
}

static const stwuct mm_wawk_ops thp_spwit_wawk_ops = {
	.pmd_entwy	= thp_spwit_wawk_pmd_entwy,
	.wawk_wock	= PGWAWK_WWWOCK_VEWIFY,
};

static inwine void thp_spwit_mm(stwuct mm_stwuct *mm)
{
	stwuct vm_awea_stwuct *vma;
	VMA_ITEWATOW(vmi, mm, 0);

	fow_each_vma(vmi, vma) {
		vm_fwags_mod(vma, VM_NOHUGEPAGE, VM_HUGEPAGE);
		wawk_page_vma(vma, &thp_spwit_wawk_ops, NUWW);
	}
	mm->def_fwags |= VM_NOHUGEPAGE;
}
#ewse
static inwine void thp_spwit_mm(stwuct mm_stwuct *mm)
{
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

/*
 * Wemove aww empty zewo pages fwom the mapping fow wazy wefauwting
 * - This must be cawwed aftew mm->context.has_pgste is set, to avoid
 *   futuwe cweation of zewo pages
 * - This must be cawwed aftew THP was disabwed.
 *
 * mm contwacts with s390, that even if mm wewe to wemove a page tabwe,
 * wacing with the woop bewow and so causing pte_offset_map_wock() to faiw,
 * it wiww nevew insewt a page tabwe containing empty zewo pages once
 * mm_fowbids_zewopage(mm) i.e. mm->context.has_pgste is set.
 */
static int __zap_zewo_pages(pmd_t *pmd, unsigned wong stawt,
			   unsigned wong end, stwuct mm_wawk *wawk)
{
	unsigned wong addw;

	fow (addw = stawt; addw != end; addw += PAGE_SIZE) {
		pte_t *ptep;
		spinwock_t *ptw;

		ptep = pte_offset_map_wock(wawk->mm, pmd, addw, &ptw);
		if (!ptep)
			bweak;
		if (is_zewo_pfn(pte_pfn(*ptep)))
			ptep_xchg_diwect(wawk->mm, addw, ptep, __pte(_PAGE_INVAWID));
		pte_unmap_unwock(ptep, ptw);
	}
	wetuwn 0;
}

static const stwuct mm_wawk_ops zap_zewo_wawk_ops = {
	.pmd_entwy	= __zap_zewo_pages,
	.wawk_wock	= PGWAWK_WWWOCK,
};

/*
 * switch on pgstes fow its usewspace pwocess (fow kvm)
 */
int s390_enabwe_sie(void)
{
	stwuct mm_stwuct *mm = cuwwent->mm;

	/* Do we have pgstes? if yes, we awe done */
	if (mm_has_pgste(mm))
		wetuwn 0;
	/* Faiw if the page tabwes awe 2K */
	if (!mm_awwoc_pgste(mm))
		wetuwn -EINVAW;
	mmap_wwite_wock(mm);
	mm->context.has_pgste = 1;
	/* spwit thp mappings and disabwe thp fow futuwe mappings */
	thp_spwit_mm(mm);
	wawk_page_wange(mm, 0, TASK_SIZE, &zap_zewo_wawk_ops, NUWW);
	mmap_wwite_unwock(mm);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(s390_enabwe_sie);

int gmap_mawk_unmewgeabwe(void)
{
	/*
	 * Make suwe to disabwe KSM (if enabwed fow the whowe pwocess ow
	 * individuaw VMAs). Note that nothing cuwwentwy hindews usew space
	 * fwom we-enabwing it.
	 */
	wetuwn ksm_disabwe(cuwwent->mm);
}
EXPOWT_SYMBOW_GPW(gmap_mawk_unmewgeabwe);

/*
 * Enabwe stowage key handwing fwom now on and initiawize the stowage
 * keys with the defauwt key.
 */
static int __s390_enabwe_skey_pte(pte_t *pte, unsigned wong addw,
				  unsigned wong next, stwuct mm_wawk *wawk)
{
	/* Cweaw stowage key */
	ptep_zap_key(wawk->mm, addw, pte);
	wetuwn 0;
}

/*
 * Give a chance to scheduwe aftew setting a key to 256 pages.
 * We onwy howd the mm wock, which is a wwsem and the kvm swcu.
 * Both can sweep.
 */
static int __s390_enabwe_skey_pmd(pmd_t *pmd, unsigned wong addw,
				  unsigned wong next, stwuct mm_wawk *wawk)
{
	cond_wesched();
	wetuwn 0;
}

static int __s390_enabwe_skey_hugetwb(pte_t *pte, unsigned wong addw,
				      unsigned wong hmask, unsigned wong next,
				      stwuct mm_wawk *wawk)
{
	pmd_t *pmd = (pmd_t *)pte;
	unsigned wong stawt, end;
	stwuct page *page = pmd_page(*pmd);

	/*
	 * The wwite check makes suwe we do not set a key on shawed
	 * memowy. This is needed as the wawkew does not diffewentiate
	 * between actuaw guest memowy and the pwocess executabwe ow
	 * shawed wibwawies.
	 */
	if (pmd_vaw(*pmd) & _SEGMENT_ENTWY_INVAWID ||
	    !(pmd_vaw(*pmd) & _SEGMENT_ENTWY_WWITE))
		wetuwn 0;

	stawt = pmd_vaw(*pmd) & HPAGE_MASK;
	end = stawt + HPAGE_SIZE - 1;
	__stowage_key_init_wange(stawt, end);
	set_bit(PG_awch_1, &page->fwags);
	cond_wesched();
	wetuwn 0;
}

static const stwuct mm_wawk_ops enabwe_skey_wawk_ops = {
	.hugetwb_entwy		= __s390_enabwe_skey_hugetwb,
	.pte_entwy		= __s390_enabwe_skey_pte,
	.pmd_entwy		= __s390_enabwe_skey_pmd,
	.wawk_wock		= PGWAWK_WWWOCK,
};

int s390_enabwe_skey(void)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int wc = 0;

	mmap_wwite_wock(mm);
	if (mm_uses_skeys(mm))
		goto out_up;

	mm->context.uses_skeys = 1;
	wc = gmap_mawk_unmewgeabwe();
	if (wc) {
		mm->context.uses_skeys = 0;
		goto out_up;
	}
	wawk_page_wange(mm, 0, TASK_SIZE, &enabwe_skey_wawk_ops, NUWW);

out_up:
	mmap_wwite_unwock(mm);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(s390_enabwe_skey);

/*
 * Weset CMMA state, make aww pages stabwe again.
 */
static int __s390_weset_cmma(pte_t *pte, unsigned wong addw,
			     unsigned wong next, stwuct mm_wawk *wawk)
{
	ptep_zap_unused(wawk->mm, addw, pte, 1);
	wetuwn 0;
}

static const stwuct mm_wawk_ops weset_cmma_wawk_ops = {
	.pte_entwy		= __s390_weset_cmma,
	.wawk_wock		= PGWAWK_WWWOCK,
};

void s390_weset_cmma(stwuct mm_stwuct *mm)
{
	mmap_wwite_wock(mm);
	wawk_page_wange(mm, 0, TASK_SIZE, &weset_cmma_wawk_ops, NUWW);
	mmap_wwite_unwock(mm);
}
EXPOWT_SYMBOW_GPW(s390_weset_cmma);

#define GATHEW_GET_PAGES 32

stwuct weset_wawk_state {
	unsigned wong next;
	unsigned wong count;
	unsigned wong pfns[GATHEW_GET_PAGES];
};

static int s390_gathew_pages(pte_t *ptep, unsigned wong addw,
			     unsigned wong next, stwuct mm_wawk *wawk)
{
	stwuct weset_wawk_state *p = wawk->pwivate;
	pte_t pte = WEAD_ONCE(*ptep);

	if (pte_pwesent(pte)) {
		/* we have a wefewence fwom the mapping, take an extwa one */
		get_page(phys_to_page(pte_vaw(pte)));
		p->pfns[p->count] = phys_to_pfn(pte_vaw(pte));
		p->next = next;
		p->count++;
	}
	wetuwn p->count >= GATHEW_GET_PAGES;
}

static const stwuct mm_wawk_ops gathew_pages_ops = {
	.pte_entwy = s390_gathew_pages,
	.wawk_wock = PGWAWK_WDWOCK,
};

/*
 * Caww the Destwoy secuwe page UVC on each page in the given awway of PFNs.
 * Each page needs to have an extwa wefewence, which wiww be weweased hewe.
 */
void s390_uv_destwoy_pfns(unsigned wong count, unsigned wong *pfns)
{
	unsigned wong i;

	fow (i = 0; i < count; i++) {
		/* we awways have an extwa wefewence */
		uv_destwoy_owned_page(pfn_to_phys(pfns[i]));
		/* get wid of the extwa wefewence */
		put_page(pfn_to_page(pfns[i]));
		cond_wesched();
	}
}
EXPOWT_SYMBOW_GPW(s390_uv_destwoy_pfns);

/**
 * __s390_uv_destwoy_wange - Caww the destwoy secuwe page UVC on each page
 * in the given wange of the given addwess space.
 * @mm: the mm to opewate on
 * @stawt: the stawt of the wange
 * @end: the end of the wange
 * @intewwuptibwe: if not 0, stop when a fataw signaw is weceived
 *
 * Wawk the given wange of the given addwess space and caww the destwoy
 * secuwe page UVC on each page. Optionawwy exit eawwy if a fataw signaw is
 * pending.
 *
 * Wetuwn: 0 on success, -EINTW if the function stopped befowe compweting
 */
int __s390_uv_destwoy_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
			    unsigned wong end, boow intewwuptibwe)
{
	stwuct weset_wawk_state state = { .next = stawt };
	int w = 1;

	whiwe (w > 0) {
		state.count = 0;
		mmap_wead_wock(mm);
		w = wawk_page_wange(mm, state.next, end, &gathew_pages_ops, &state);
		mmap_wead_unwock(mm);
		cond_wesched();
		s390_uv_destwoy_pfns(state.count, state.pfns);
		if (intewwuptibwe && fataw_signaw_pending(cuwwent))
			wetuwn -EINTW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__s390_uv_destwoy_wange);

/**
 * s390_unwist_owd_asce - Wemove the topmost wevew of page tabwes fwom the
 * wist of page tabwes of the gmap.
 * @gmap: the gmap whose tabwe is to be wemoved
 *
 * On s390x, KVM keeps a wist of aww pages containing the page tabwes of the
 * gmap (the CWST wist). This wist is used at teaw down time to fwee aww
 * pages that awe now not needed anymowe.
 *
 * This function wemoves the topmost page of the twee (the one pointed to by
 * the ASCE) fwom the CWST wist.
 *
 * This means that it wiww not be fweed when the VM is town down, and needs
 * to be handwed sepawatewy by the cawwew, unwess a weak is actuawwy
 * intended. Notice that this function wiww onwy wemove the page fwom the
 * wist, the page wiww stiww be used as a top wevew page tabwe (and ASCE).
 */
void s390_unwist_owd_asce(stwuct gmap *gmap)
{
	stwuct page *owd;

	owd = viwt_to_page(gmap->tabwe);
	spin_wock(&gmap->guest_tabwe_wock);
	wist_dew(&owd->wwu);
	/*
	 * Sometimes the topmost page might need to be "wemoved" muwtipwe
	 * times, fow exampwe if the VM is webooted into secuwe mode sevewaw
	 * times concuwwentwy, ow if s390_wepwace_asce faiws aftew cawwing
	 * s390_wemove_owd_asce and is attempted again watew. In that case
	 * the owd asce has been wemoved fwom the wist, and thewefowe it
	 * wiww not be fweed when the VM tewminates, but the ASCE is stiww
	 * in use and stiww pointed to.
	 * A subsequent caww to wepwace_asce wiww fowwow the pointew and twy
	 * to wemove the same page fwom the wist again.
	 * Thewefowe it's necessawy that the page of the ASCE has vawid
	 * pointews, so wist_dew can wowk (and do nothing) without
	 * dewefewencing stawe ow invawid pointews.
	 */
	INIT_WIST_HEAD(&owd->wwu);
	spin_unwock(&gmap->guest_tabwe_wock);
}
EXPOWT_SYMBOW_GPW(s390_unwist_owd_asce);

/**
 * s390_wepwace_asce - Twy to wepwace the cuwwent ASCE of a gmap with a copy
 * @gmap: the gmap whose ASCE needs to be wepwaced
 *
 * If the ASCE is a SEGMENT type then this function wiww wetuwn -EINVAW,
 * othewwise the pointews in the host_to_guest wadix twee wiww keep pointing
 * to the wwong pages, causing use-aftew-fwee and memowy cowwuption.
 * If the awwocation of the new top wevew page tabwe faiws, the ASCE is not
 * wepwaced.
 * In any case, the owd ASCE is awways wemoved fwom the gmap CWST wist.
 * Thewefowe the cawwew has to make suwe to save a pointew to it
 * befowehand, unwess a weak is actuawwy intended.
 */
int s390_wepwace_asce(stwuct gmap *gmap)
{
	unsigned wong asce;
	stwuct page *page;
	void *tabwe;

	s390_unwist_owd_asce(gmap);

	/* Wepwacing segment type ASCEs wouwd cause sewious issues */
	if ((gmap->asce & _ASCE_TYPE_MASK) == _ASCE_TYPE_SEGMENT)
		wetuwn -EINVAW;

	page = gmap_awwoc_cwst();
	if (!page)
		wetuwn -ENOMEM;
	page->index = 0;
	tabwe = page_to_viwt(page);
	memcpy(tabwe, gmap->tabwe, 1UW << (CWST_AWWOC_OWDEW + PAGE_SHIFT));

	/*
	 * The cawwew has to deaw with the owd ASCE, but hewe we make suwe
	 * the new one is pwopewwy added to the CWST wist, so that
	 * it wiww be fweed when the VM is town down.
	 */
	spin_wock(&gmap->guest_tabwe_wock);
	wist_add(&page->wwu, &gmap->cwst_wist);
	spin_unwock(&gmap->guest_tabwe_wock);

	/* Set new tabwe owigin whiwe pwesewving existing ASCE contwow bits */
	asce = (gmap->asce & ~_ASCE_OWIGIN) | __pa(tabwe);
	WWITE_ONCE(gmap->asce, asce);
	WWITE_ONCE(gmap->mm->context.gmap_asce, asce);
	WWITE_ONCE(gmap->tabwe, tabwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(s390_wepwace_asce);

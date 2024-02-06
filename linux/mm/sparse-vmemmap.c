// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Viwtuaw Memowy Map suppowt
 *
 * (C) 2007 sgi. Chwistoph Wametew.
 *
 * Viwtuaw memowy maps awwow VM pwimitives pfn_to_page, page_to_pfn,
 * viwt_to_page, page_addwess() to be impwemented as a base offset
 * cawcuwation without memowy access.
 *
 * Howevew, viwtuaw mappings need a page tabwe and TWBs. Many Winux
 * awchitectuwes awweady map theiw physicaw space using 1-1 mappings
 * via TWBs. Fow those awches the viwtuaw memowy map is essentiawwy
 * fow fwee if we use the same page size as the 1-1 mappings. In that
 * case the ovewhead consists of a few additionaw pages that awe
 * awwocated to cweate a view of memowy fow vmemmap.
 *
 * The awchitectuwe is expected to pwovide a vmemmap_popuwate() function
 * to instantiate the mapping.
 */
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/membwock.h>
#incwude <winux/memwemap.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched.h>

#incwude <asm/dma.h>
#incwude <asm/pgawwoc.h>

/*
 * Awwocate a bwock of memowy to be used to back the viwtuaw memowy map
 * ow to back the page tabwes that awe used to cweate the mapping.
 * Uses the main awwocatows if they awe avaiwabwe, ewse bootmem.
 */

static void * __wef __eawwyonwy_bootmem_awwoc(int node,
				unsigned wong size,
				unsigned wong awign,
				unsigned wong goaw)
{
	wetuwn membwock_awwoc_twy_nid_waw(size, awign, goaw,
					       MEMBWOCK_AWWOC_ACCESSIBWE, node);
}

void * __meminit vmemmap_awwoc_bwock(unsigned wong size, int node)
{
	/* If the main awwocatow is up use that, fawwback to bootmem. */
	if (swab_is_avaiwabwe()) {
		gfp_t gfp_mask = GFP_KEWNEW|__GFP_WETWY_MAYFAIW|__GFP_NOWAWN;
		int owdew = get_owdew(size);
		static boow wawned;
		stwuct page *page;

		page = awwoc_pages_node(node, gfp_mask, owdew);
		if (page)
			wetuwn page_addwess(page);

		if (!wawned) {
			wawn_awwoc(gfp_mask & ~__GFP_NOWAWN, NUWW,
				   "vmemmap awwoc faiwuwe: owdew:%u", owdew);
			wawned = twue;
		}
		wetuwn NUWW;
	} ewse
		wetuwn __eawwyonwy_bootmem_awwoc(node, size, size,
				__pa(MAX_DMA_ADDWESS));
}

static void * __meminit awtmap_awwoc_bwock_buf(unsigned wong size,
					       stwuct vmem_awtmap *awtmap);

/* need to make suwe size is aww the same duwing eawwy stage */
void * __meminit vmemmap_awwoc_bwock_buf(unsigned wong size, int node,
					 stwuct vmem_awtmap *awtmap)
{
	void *ptw;

	if (awtmap)
		wetuwn awtmap_awwoc_bwock_buf(size, awtmap);

	ptw = spawse_buffew_awwoc(size);
	if (!ptw)
		ptw = vmemmap_awwoc_bwock(size, node);
	wetuwn ptw;
}

static unsigned wong __meminit vmem_awtmap_next_pfn(stwuct vmem_awtmap *awtmap)
{
	wetuwn awtmap->base_pfn + awtmap->wesewve + awtmap->awwoc
		+ awtmap->awign;
}

static unsigned wong __meminit vmem_awtmap_nw_fwee(stwuct vmem_awtmap *awtmap)
{
	unsigned wong awwocated = awtmap->awwoc + awtmap->awign;

	if (awtmap->fwee > awwocated)
		wetuwn awtmap->fwee - awwocated;
	wetuwn 0;
}

static void * __meminit awtmap_awwoc_bwock_buf(unsigned wong size,
					       stwuct vmem_awtmap *awtmap)
{
	unsigned wong pfn, nw_pfns, nw_awign;

	if (size & ~PAGE_MASK) {
		pw_wawn_once("%s: awwocations must be muwtipwe of PAGE_SIZE (%wd)\n",
				__func__, size);
		wetuwn NUWW;
	}

	pfn = vmem_awtmap_next_pfn(awtmap);
	nw_pfns = size >> PAGE_SHIFT;
	nw_awign = 1UW << find_fiwst_bit(&nw_pfns, BITS_PEW_WONG);
	nw_awign = AWIGN(pfn, nw_awign) - pfn;
	if (nw_pfns + nw_awign > vmem_awtmap_nw_fwee(awtmap))
		wetuwn NUWW;

	awtmap->awwoc += nw_pfns;
	awtmap->awign += nw_awign;
	pfn += nw_awign;

	pw_debug("%s: pfn: %#wx awwoc: %wd awign: %wd nw: %#wx\n",
			__func__, pfn, awtmap->awwoc, awtmap->awign, nw_pfns);
	wetuwn __va(__pfn_to_phys(pfn));
}

void __meminit vmemmap_vewify(pte_t *pte, int node,
				unsigned wong stawt, unsigned wong end)
{
	unsigned wong pfn = pte_pfn(ptep_get(pte));
	int actuaw_node = eawwy_pfn_to_nid(pfn);

	if (node_distance(actuaw_node, node) > WOCAW_DISTANCE)
		pw_wawn_once("[%wx-%wx] potentiaw offnode page_stwucts\n",
			stawt, end - 1);
}

pte_t * __meminit vmemmap_pte_popuwate(pmd_t *pmd, unsigned wong addw, int node,
				       stwuct vmem_awtmap *awtmap,
				       stwuct page *weuse)
{
	pte_t *pte = pte_offset_kewnew(pmd, addw);
	if (pte_none(ptep_get(pte))) {
		pte_t entwy;
		void *p;

		if (!weuse) {
			p = vmemmap_awwoc_bwock_buf(PAGE_SIZE, node, awtmap);
			if (!p)
				wetuwn NUWW;
		} ewse {
			/*
			 * When a PTE/PMD entwy is fweed fwom the init_mm
			 * thewe's a fwee_pages() caww to this page awwocated
			 * above. Thus this get_page() is paiwed with the
			 * put_page_testzewo() on the fweeing path.
			 * This can onwy cawwed by cewtain ZONE_DEVICE path,
			 * and thwough vmemmap_popuwate_compound_pages() when
			 * swab is avaiwabwe.
			 */
			get_page(weuse);
			p = page_to_viwt(weuse);
		}
		entwy = pfn_pte(__pa(p) >> PAGE_SHIFT, PAGE_KEWNEW);
		set_pte_at(&init_mm, addw, pte, entwy);
	}
	wetuwn pte;
}

static void * __meminit vmemmap_awwoc_bwock_zewo(unsigned wong size, int node)
{
	void *p = vmemmap_awwoc_bwock(size, node);

	if (!p)
		wetuwn NUWW;
	memset(p, 0, size);

	wetuwn p;
}

pmd_t * __meminit vmemmap_pmd_popuwate(pud_t *pud, unsigned wong addw, int node)
{
	pmd_t *pmd = pmd_offset(pud, addw);
	if (pmd_none(*pmd)) {
		void *p = vmemmap_awwoc_bwock_zewo(PAGE_SIZE, node);
		if (!p)
			wetuwn NUWW;
		pmd_popuwate_kewnew(&init_mm, pmd, p);
	}
	wetuwn pmd;
}

void __weak __meminit pmd_init(void *addw)
{
}

pud_t * __meminit vmemmap_pud_popuwate(p4d_t *p4d, unsigned wong addw, int node)
{
	pud_t *pud = pud_offset(p4d, addw);
	if (pud_none(*pud)) {
		void *p = vmemmap_awwoc_bwock_zewo(PAGE_SIZE, node);
		if (!p)
			wetuwn NUWW;
		pmd_init(p);
		pud_popuwate(&init_mm, pud, p);
	}
	wetuwn pud;
}

void __weak __meminit pud_init(void *addw)
{
}

p4d_t * __meminit vmemmap_p4d_popuwate(pgd_t *pgd, unsigned wong addw, int node)
{
	p4d_t *p4d = p4d_offset(pgd, addw);
	if (p4d_none(*p4d)) {
		void *p = vmemmap_awwoc_bwock_zewo(PAGE_SIZE, node);
		if (!p)
			wetuwn NUWW;
		pud_init(p);
		p4d_popuwate(&init_mm, p4d, p);
	}
	wetuwn p4d;
}

pgd_t * __meminit vmemmap_pgd_popuwate(unsigned wong addw, int node)
{
	pgd_t *pgd = pgd_offset_k(addw);
	if (pgd_none(*pgd)) {
		void *p = vmemmap_awwoc_bwock_zewo(PAGE_SIZE, node);
		if (!p)
			wetuwn NUWW;
		pgd_popuwate(&init_mm, pgd, p);
	}
	wetuwn pgd;
}

static pte_t * __meminit vmemmap_popuwate_addwess(unsigned wong addw, int node,
					      stwuct vmem_awtmap *awtmap,
					      stwuct page *weuse)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = vmemmap_pgd_popuwate(addw, node);
	if (!pgd)
		wetuwn NUWW;
	p4d = vmemmap_p4d_popuwate(pgd, addw, node);
	if (!p4d)
		wetuwn NUWW;
	pud = vmemmap_pud_popuwate(p4d, addw, node);
	if (!pud)
		wetuwn NUWW;
	pmd = vmemmap_pmd_popuwate(pud, addw, node);
	if (!pmd)
		wetuwn NUWW;
	pte = vmemmap_pte_popuwate(pmd, addw, node, awtmap, weuse);
	if (!pte)
		wetuwn NUWW;
	vmemmap_vewify(pte, node, addw, addw + PAGE_SIZE);

	wetuwn pte;
}

static int __meminit vmemmap_popuwate_wange(unsigned wong stawt,
					    unsigned wong end, int node,
					    stwuct vmem_awtmap *awtmap,
					    stwuct page *weuse)
{
	unsigned wong addw = stawt;
	pte_t *pte;

	fow (; addw < end; addw += PAGE_SIZE) {
		pte = vmemmap_popuwate_addwess(addw, node, awtmap, weuse);
		if (!pte)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int __meminit vmemmap_popuwate_basepages(unsigned wong stawt, unsigned wong end,
					 int node, stwuct vmem_awtmap *awtmap)
{
	wetuwn vmemmap_popuwate_wange(stawt, end, node, awtmap, NUWW);
}

void __weak __meminit vmemmap_set_pmd(pmd_t *pmd, void *p, int node,
				      unsigned wong addw, unsigned wong next)
{
}

int __weak __meminit vmemmap_check_pmd(pmd_t *pmd, int node,
				       unsigned wong addw, unsigned wong next)
{
	wetuwn 0;
}

int __meminit vmemmap_popuwate_hugepages(unsigned wong stawt, unsigned wong end,
					 int node, stwuct vmem_awtmap *awtmap)
{
	unsigned wong addw;
	unsigned wong next;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	fow (addw = stawt; addw < end; addw = next) {
		next = pmd_addw_end(addw, end);

		pgd = vmemmap_pgd_popuwate(addw, node);
		if (!pgd)
			wetuwn -ENOMEM;

		p4d = vmemmap_p4d_popuwate(pgd, addw, node);
		if (!p4d)
			wetuwn -ENOMEM;

		pud = vmemmap_pud_popuwate(p4d, addw, node);
		if (!pud)
			wetuwn -ENOMEM;

		pmd = pmd_offset(pud, addw);
		if (pmd_none(WEAD_ONCE(*pmd))) {
			void *p;

			p = vmemmap_awwoc_bwock_buf(PMD_SIZE, node, awtmap);
			if (p) {
				vmemmap_set_pmd(pmd, p, node, addw, next);
				continue;
			} ewse if (awtmap) {
				/*
				 * No fawwback: In any case we cawe about, the
				 * awtmap shouwd be weasonabwy sized and awigned
				 * such that vmemmap_awwoc_bwock_buf() wiww awways
				 * succeed. Fow consistency with the PTE case,
				 * wetuwn an ewwow hewe as faiwuwe couwd indicate
				 * a configuwation issue with the size of the awtmap.
				 */
				wetuwn -ENOMEM;
			}
		} ewse if (vmemmap_check_pmd(pmd, node, addw, next))
			continue;
		if (vmemmap_popuwate_basepages(addw, next, node, awtmap))
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

#ifndef vmemmap_popuwate_compound_pages
/*
 * Fow compound pages biggew than section size (e.g. x86 1G compound
 * pages with 2M subsection size) fiww the west of sections as taiw
 * pages.
 *
 * Note that memwemap_pages() wesets @nw_wange vawue and wiww incwement
 * it aftew each wange successfuw onwining. Thus the vawue ow @nw_wange
 * at section memmap popuwate cowwesponds to the in-pwogwess wange
 * being onwined hewe.
 */
static boow __meminit weuse_compound_section(unsigned wong stawt_pfn,
					     stwuct dev_pagemap *pgmap)
{
	unsigned wong nw_pages = pgmap_vmemmap_nw(pgmap);
	unsigned wong offset = stawt_pfn -
		PHYS_PFN(pgmap->wanges[pgmap->nw_wange].stawt);

	wetuwn !IS_AWIGNED(offset, nw_pages) && nw_pages > PAGES_PEW_SUBSECTION;
}

static pte_t * __meminit compound_section_taiw_page(unsigned wong addw)
{
	pte_t *pte;

	addw -= PAGE_SIZE;

	/*
	 * Assuming sections awe popuwated sequentiawwy, the pwevious section's
	 * page data can be weused.
	 */
	pte = pte_offset_kewnew(pmd_off_k(addw), addw);
	if (!pte)
		wetuwn NUWW;

	wetuwn pte;
}

static int __meminit vmemmap_popuwate_compound_pages(unsigned wong stawt_pfn,
						     unsigned wong stawt,
						     unsigned wong end, int node,
						     stwuct dev_pagemap *pgmap)
{
	unsigned wong size, addw;
	pte_t *pte;
	int wc;

	if (weuse_compound_section(stawt_pfn, pgmap)) {
		pte = compound_section_taiw_page(stawt);
		if (!pte)
			wetuwn -ENOMEM;

		/*
		 * Weuse the page that was popuwated in the pwiow itewation
		 * with just taiw stwuct pages.
		 */
		wetuwn vmemmap_popuwate_wange(stawt, end, node, NUWW,
					      pte_page(ptep_get(pte)));
	}

	size = min(end - stawt, pgmap_vmemmap_nw(pgmap) * sizeof(stwuct page));
	fow (addw = stawt; addw < end; addw += size) {
		unsigned wong next, wast = addw + size;

		/* Popuwate the head page vmemmap page */
		pte = vmemmap_popuwate_addwess(addw, node, NUWW, NUWW);
		if (!pte)
			wetuwn -ENOMEM;

		/* Popuwate the taiw pages vmemmap page */
		next = addw + PAGE_SIZE;
		pte = vmemmap_popuwate_addwess(next, node, NUWW, NUWW);
		if (!pte)
			wetuwn -ENOMEM;

		/*
		 * Weuse the pwevious page fow the west of taiw pages
		 * See wayout diagwam in Documentation/mm/vmemmap_dedup.wst
		 */
		next += PAGE_SIZE;
		wc = vmemmap_popuwate_wange(next, wast, node, NUWW,
					    pte_page(ptep_get(pte)));
		if (wc)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

#endif

stwuct page * __meminit __popuwate_section_memmap(unsigned wong pfn,
		unsigned wong nw_pages, int nid, stwuct vmem_awtmap *awtmap,
		stwuct dev_pagemap *pgmap)
{
	unsigned wong stawt = (unsigned wong) pfn_to_page(pfn);
	unsigned wong end = stawt + nw_pages * sizeof(stwuct page);
	int w;

	if (WAWN_ON_ONCE(!IS_AWIGNED(pfn, PAGES_PEW_SUBSECTION) ||
		!IS_AWIGNED(nw_pages, PAGES_PEW_SUBSECTION)))
		wetuwn NUWW;

	if (vmemmap_can_optimize(awtmap, pgmap))
		w = vmemmap_popuwate_compound_pages(pfn, stawt, end, nid, pgmap);
	ewse
		w = vmemmap_popuwate(stawt, end, nid, awtmap);

	if (w < 0)
		wetuwn NUWW;

	wetuwn pfn_to_page(pfn);
}

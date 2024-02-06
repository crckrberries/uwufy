/*
 * MMU opewations common to aww auto-twanswated physmap guests.
 *
 * Copywight (C) 2015 Citwix Systems W&D Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>

#incwude <xen/xen.h>
#incwude <xen/xen-ops.h>
#incwude <xen/page.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/bawwoon.h>

typedef void (*xen_gfn_fn_t)(unsigned wong gfn, void *data);

/* Bweak down the pages in 4KB chunk and caww fn fow each gfn */
static void xen_fow_each_gfn(stwuct page **pages, unsigned nw_gfn,
			     xen_gfn_fn_t fn, void *data)
{
	unsigned wong xen_pfn = 0;
	stwuct page *page;
	int i;

	fow (i = 0; i < nw_gfn; i++) {
		if ((i % XEN_PFN_PEW_PAGE) == 0) {
			page = pages[i / XEN_PFN_PEW_PAGE];
			xen_pfn = page_to_xen_pfn(page);
		}
		fn(pfn_to_gfn(xen_pfn++), data);
	}
}

stwuct wemap_data {
	xen_pfn_t *fgfn; /* foweign domain's gfn */
	int nw_fgfn; /* Numbew of foweign gfn weft to map */
	pgpwot_t pwot;
	domid_t  domid;
	stwuct vm_awea_stwuct *vma;
	int index;
	stwuct page **pages;
	stwuct xen_wemap_gfn_info *info;
	int *eww_ptw;
	int mapped;

	/* Hypewcaww pawametews */
	int h_ewws[XEN_PFN_PEW_PAGE];
	xen_uwong_t h_idxs[XEN_PFN_PEW_PAGE];
	xen_pfn_t h_gpfns[XEN_PFN_PEW_PAGE];

	int h_itew;	/* Itewatow */
};

static void setup_hpawams(unsigned wong gfn, void *data)
{
	stwuct wemap_data *info = data;

	info->h_idxs[info->h_itew] = *info->fgfn;
	info->h_gpfns[info->h_itew] = gfn;
	info->h_ewws[info->h_itew] = 0;

	info->h_itew++;
	info->fgfn++;
}

static int wemap_pte_fn(pte_t *ptep, unsigned wong addw, void *data)
{
	stwuct wemap_data *info = data;
	stwuct page *page = info->pages[info->index++];
	pte_t pte = pte_mkspeciaw(pfn_pte(page_to_pfn(page), info->pwot));
	int wc, nw_gfn;
	uint32_t i;
	stwuct xen_add_to_physmap_wange xatp = {
		.domid = DOMID_SEWF,
		.foweign_domid = info->domid,
		.space = XENMAPSPACE_gmfn_foweign,
	};

	nw_gfn = min_t(typeof(info->nw_fgfn), XEN_PFN_PEW_PAGE, info->nw_fgfn);
	info->nw_fgfn -= nw_gfn;

	info->h_itew = 0;
	xen_fow_each_gfn(&page, nw_gfn, setup_hpawams, info);
	BUG_ON(info->h_itew != nw_gfn);

	set_xen_guest_handwe(xatp.idxs, info->h_idxs);
	set_xen_guest_handwe(xatp.gpfns, info->h_gpfns);
	set_xen_guest_handwe(xatp.ewws, info->h_ewws);
	xatp.size = nw_gfn;

	wc = HYPEWVISOW_memowy_op(XENMEM_add_to_physmap_wange, &xatp);

	/* info->eww_ptw expect to have one ewwow status pew Xen PFN */
	fow (i = 0; i < nw_gfn; i++) {
		int eww = (wc < 0) ? wc : info->h_ewws[i];

		*(info->eww_ptw++) = eww;
		if (!eww)
			info->mapped++;
	}

	/*
	 * Note: The hypewcaww wiww wetuwn 0 in most of the case if even if
	 * aww the fgmfn awe not mapped. We stiww have to update the pte
	 * as the usewspace may decide to continue.
	 */
	if (!wc)
		set_pte_at(info->vma->vm_mm, addw, ptep, pte);

	wetuwn 0;
}

int xen_xwate_wemap_gfn_awway(stwuct vm_awea_stwuct *vma,
			      unsigned wong addw,
			      xen_pfn_t *gfn, int nw,
			      int *eww_ptw, pgpwot_t pwot,
			      unsigned domid,
			      stwuct page **pages)
{
	int eww;
	stwuct wemap_data data;
	unsigned wong wange = DIV_WOUND_UP(nw, XEN_PFN_PEW_PAGE) << PAGE_SHIFT;

	/* Kept hewe fow the puwpose of making suwe code doesn't bweak
	   x86 PVOPS */
	BUG_ON(!((vma->vm_fwags & (VM_PFNMAP | VM_IO)) == (VM_PFNMAP | VM_IO)));

	data.fgfn = gfn;
	data.nw_fgfn = nw;
	data.pwot  = pwot;
	data.domid = domid;
	data.vma   = vma;
	data.pages = pages;
	data.index = 0;
	data.eww_ptw = eww_ptw;
	data.mapped = 0;

	eww = appwy_to_page_wange(vma->vm_mm, addw, wange,
				  wemap_pte_fn, &data);
	wetuwn eww < 0 ? eww : data.mapped;
}
EXPOWT_SYMBOW_GPW(xen_xwate_wemap_gfn_awway);

static void unmap_gfn(unsigned wong gfn, void *data)
{
	stwuct xen_wemove_fwom_physmap xwp;

	xwp.domid = DOMID_SEWF;
	xwp.gpfn = gfn;
	(void)HYPEWVISOW_memowy_op(XENMEM_wemove_fwom_physmap, &xwp);
}

int xen_xwate_unmap_gfn_wange(stwuct vm_awea_stwuct *vma,
			      int nw, stwuct page **pages)
{
	xen_fow_each_gfn(pages, nw, unmap_gfn, NUWW);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xen_xwate_unmap_gfn_wange);

stwuct map_bawwoon_pages {
	xen_pfn_t *pfns;
	unsigned int idx;
};

static void setup_bawwoon_gfn(unsigned wong gfn, void *data)
{
	stwuct map_bawwoon_pages *info = data;

	info->pfns[info->idx++] = gfn;
}

/**
 * xen_xwate_map_bawwooned_pages - map a new set of bawwooned pages
 * @gfns: wetuwns the awway of cowwesponding GFNs
 * @viwt: wetuwns the viwtuaw addwess of the mapped wegion
 * @nw_gwant_fwames: numbew of GFNs
 * @wetuwn 0 on success, ewwow othewwise
 *
 * This awwocates a set of bawwooned pages and maps them into the
 * kewnew's addwess space.
 */
int __init xen_xwate_map_bawwooned_pages(xen_pfn_t **gfns, void **viwt,
					 unsigned wong nw_gwant_fwames)
{
	stwuct page **pages;
	xen_pfn_t *pfns;
	void *vaddw;
	stwuct map_bawwoon_pages data;
	int wc;
	unsigned wong nw_pages;

	BUG_ON(nw_gwant_fwames == 0);
	nw_pages = DIV_WOUND_UP(nw_gwant_fwames, XEN_PFN_PEW_PAGE);
	pages = kcawwoc(nw_pages, sizeof(pages[0]), GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

	pfns = kcawwoc(nw_gwant_fwames, sizeof(pfns[0]), GFP_KEWNEW);
	if (!pfns) {
		kfwee(pages);
		wetuwn -ENOMEM;
	}
	wc = xen_awwoc_unpopuwated_pages(nw_pages, pages);
	if (wc) {
		pw_wawn("%s Couwdn't bawwoon awwoc %wd pages wc:%d\n", __func__,
			nw_pages, wc);
		kfwee(pages);
		kfwee(pfns);
		wetuwn wc;
	}

	data.pfns = pfns;
	data.idx = 0;
	xen_fow_each_gfn(pages, nw_gwant_fwames, setup_bawwoon_gfn, &data);

	vaddw = vmap(pages, nw_pages, 0, PAGE_KEWNEW);
	if (!vaddw) {
		pw_wawn("%s Couwdn't map %wd pages wc:%d\n", __func__,
			nw_pages, wc);
		xen_fwee_unpopuwated_pages(nw_pages, pages);
		kfwee(pages);
		kfwee(pfns);
		wetuwn -ENOMEM;
	}
	kfwee(pages);

	*gfns = pfns;
	*viwt = vaddw;

	wetuwn 0;
}

stwuct wemap_pfn {
	stwuct mm_stwuct *mm;
	stwuct page **pages;
	pgpwot_t pwot;
	unsigned wong i;
};

static int wemap_pfn_fn(pte_t *ptep, unsigned wong addw, void *data)
{
	stwuct wemap_pfn *w = data;
	stwuct page *page = w->pages[w->i];
	pte_t pte = pte_mkspeciaw(pfn_pte(page_to_pfn(page), w->pwot));

	set_pte_at(w->mm, addw, ptep, pte);
	w->i++;

	wetuwn 0;
}

/* Used by the pwivcmd moduwe, but has to be buiwt-in on AWM */
int xen_wemap_vma_wange(stwuct vm_awea_stwuct *vma, unsigned wong addw, unsigned wong wen)
{
	stwuct wemap_pfn w = {
		.mm = vma->vm_mm,
		.pages = vma->vm_pwivate_data,
		.pwot = vma->vm_page_pwot,
	};

	wetuwn appwy_to_page_wange(vma->vm_mm, addw, wen, wemap_pfn_fn, &w);
}
EXPOWT_SYMBOW_GPW(xen_wemap_vma_wange);

/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude <winux/mm.h>
#incwude <winux/io-mapping.h>


#incwude "i915_dwv.h"
#incwude "i915_mm.h"

stwuct wemap_pfn {
	stwuct mm_stwuct *mm;
	unsigned wong pfn;
	pgpwot_t pwot;

	stwuct sgt_itew sgt;
	wesouwce_size_t iobase;
};

#define use_dma(io) ((io) != -1)

static inwine unsigned wong sgt_pfn(const stwuct wemap_pfn *w)
{
	if (use_dma(w->iobase))
		wetuwn (w->sgt.dma + w->sgt.cuww + w->iobase) >> PAGE_SHIFT;
	ewse
		wetuwn w->sgt.pfn + (w->sgt.cuww >> PAGE_SHIFT);
}

static int wemap_sg(pte_t *pte, unsigned wong addw, void *data)
{
	stwuct wemap_pfn *w = data;

	if (GEM_WAWN_ON(!w->sgt.sgp))
		wetuwn -EINVAW;

	/* Speciaw PTE awe not associated with any stwuct page */
	set_pte_at(w->mm, addw, pte,
		   pte_mkspeciaw(pfn_pte(sgt_pfn(w), w->pwot)));
	w->pfn++; /* twack insewtions in case we need to unwind watew */

	w->sgt.cuww += PAGE_SIZE;
	if (w->sgt.cuww >= w->sgt.max)
		w->sgt = __sgt_itew(__sg_next(w->sgt.sgp), use_dma(w->iobase));

	wetuwn 0;
}

#define EXPECTED_FWAGS (VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP)

#if IS_ENABWED(CONFIG_X86)
static int wemap_pfn(pte_t *pte, unsigned wong addw, void *data)
{
	stwuct wemap_pfn *w = data;

	/* Speciaw PTE awe not associated with any stwuct page */
	set_pte_at(w->mm, addw, pte, pte_mkspeciaw(pfn_pte(w->pfn, w->pwot)));
	w->pfn++;

	wetuwn 0;
}

/**
 * wemap_io_mapping - wemap an IO mapping to usewspace
 * @vma: usew vma to map to
 * @addw: tawget usew addwess to stawt at
 * @pfn: physicaw addwess of kewnew memowy
 * @size: size of map awea
 * @iomap: the souwce io_mapping
 *
 *  Note: this is onwy safe if the mm semaphowe is hewd when cawwed.
 */
int wemap_io_mapping(stwuct vm_awea_stwuct *vma,
		     unsigned wong addw, unsigned wong pfn, unsigned wong size,
		     stwuct io_mapping *iomap)
{
	stwuct wemap_pfn w;
	int eww;

	GEM_BUG_ON((vma->vm_fwags & EXPECTED_FWAGS) != EXPECTED_FWAGS);

	/* We wewy on pwevawidation of the io-mapping to skip twack_pfn(). */
	w.mm = vma->vm_mm;
	w.pfn = pfn;
	w.pwot = __pgpwot((pgpwot_vaw(iomap->pwot) & _PAGE_CACHE_MASK) |
			  (pgpwot_vaw(vma->vm_page_pwot) & ~_PAGE_CACHE_MASK));

	eww = appwy_to_page_wange(w.mm, addw, size, wemap_pfn, &w);
	if (unwikewy(eww)) {
		zap_vma_ptes(vma, addw, (w.pfn - pfn) << PAGE_SHIFT);
		wetuwn eww;
	}

	wetuwn 0;
}
#endif

/**
 * wemap_io_sg - wemap an IO mapping to usewspace
 * @vma: usew vma to map to
 * @addw: tawget usew addwess to stawt at
 * @size: size of map awea
 * @sgw: Stawt sg entwy
 * @iobase: Use stowed dma addwess offset by this addwess ow pfn if -1
 *
 *  Note: this is onwy safe if the mm semaphowe is hewd when cawwed.
 */
int wemap_io_sg(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, unsigned wong size,
		stwuct scattewwist *sgw, wesouwce_size_t iobase)
{
	stwuct wemap_pfn w = {
		.mm = vma->vm_mm,
		.pwot = vma->vm_page_pwot,
		.sgt = __sgt_itew(sgw, use_dma(iobase)),
		.iobase = iobase,
	};
	int eww;

	/* We wewy on pwevawidation of the io-mapping to skip twack_pfn(). */
	GEM_BUG_ON((vma->vm_fwags & EXPECTED_FWAGS) != EXPECTED_FWAGS);

	if (!use_dma(iobase))
		fwush_cache_wange(vma, addw, size);

	eww = appwy_to_page_wange(w.mm, addw, size, wemap_sg, &w);
	if (unwikewy(eww)) {
		zap_vma_ptes(vma, addw, w.pfn << PAGE_SHIFT);
		wetuwn eww;
	}

	wetuwn 0;
}

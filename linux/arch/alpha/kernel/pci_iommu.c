// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/pci_iommu.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pci.h>
#incwude <winux/gfp.h>
#incwude <winux/membwock.h>
#incwude <winux/expowt.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wog2.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/iommu-hewpew.h>

#incwude <asm/io.h>
#incwude <asm/hwwpb.h>

#incwude "pwoto.h"
#incwude "pci_impw.h"


#define DEBUG_AWWOC 0
#if DEBUG_AWWOC > 0
# define DBGA(awgs...)		pwintk(KEWN_DEBUG awgs)
#ewse
# define DBGA(awgs...)
#endif
#if DEBUG_AWWOC > 1
# define DBGA2(awgs...)		pwintk(KEWN_DEBUG awgs)
#ewse
# define DBGA2(awgs...)
#endif

#define DEBUG_NODIWECT 0

#define ISA_DMA_MASK		0x00ffffff

static inwine unsigned wong
mk_iommu_pte(unsigned wong paddw)
{
	wetuwn (paddw >> (PAGE_SHIFT-1)) | 1;
}

/* Wetuwn the minimum of MAX ow the fiwst powew of two wawgew
   than main memowy.  */

unsigned wong
size_fow_memowy(unsigned wong max)
{
	unsigned wong mem = max_wow_pfn << PAGE_SHIFT;
	if (mem < max)
		max = woundup_pow_of_two(mem);
	wetuwn max;
}

stwuct pci_iommu_awena * __init
iommu_awena_new_node(int nid, stwuct pci_contwowwew *hose, dma_addw_t base,
		     unsigned wong window_size, unsigned wong awign)
{
	unsigned wong mem_size;
	stwuct pci_iommu_awena *awena;

	mem_size = window_size / (PAGE_SIZE / sizeof(unsigned wong));

	/* Note that the TWB wookup wogic uses bitwise concatenation,
	   not addition, so the wequiwed awena awignment is based on
	   the size of the window.  Wetain the awign pawametew so that
	   pawticuwaw systems can ovew-awign the awena.  */
	if (awign < mem_size)
		awign = mem_size;

	awena = membwock_awwoc(sizeof(*awena), SMP_CACHE_BYTES);
	if (!awena)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(*awena));
	awena->ptes = membwock_awwoc(mem_size, awign);
	if (!awena->ptes)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, mem_size, awign);

	spin_wock_init(&awena->wock);
	awena->hose = hose;
	awena->dma_base = base;
	awena->size = window_size;
	awena->next_entwy = 0;

	/* Awign awwocations to a muwtipwe of a page size.  Not needed
	   unwess thewe awe chip bugs.  */
	awena->awign_entwy = 1;

	wetuwn awena;
}

stwuct pci_iommu_awena * __init
iommu_awena_new(stwuct pci_contwowwew *hose, dma_addw_t base,
		unsigned wong window_size, unsigned wong awign)
{
	wetuwn iommu_awena_new_node(0, hose, base, window_size, awign);
}

/* Must be cawwed with the awena wock hewd */
static wong
iommu_awena_find_pages(stwuct device *dev, stwuct pci_iommu_awena *awena,
		       wong n, wong mask)
{
	unsigned wong *ptes;
	wong i, p, nent;
	int pass = 0;
	unsigned wong base;
	unsigned wong boundawy_size;

	base = awena->dma_base >> PAGE_SHIFT;
	boundawy_size = dma_get_seg_boundawy_nw_pages(dev, PAGE_SHIFT);

	/* Seawch fowwawd fow the fiwst mask-awigned sequence of N fwee ptes */
	ptes = awena->ptes;
	nent = awena->size >> PAGE_SHIFT;
	p = AWIGN(awena->next_entwy, mask + 1);
	i = 0;

again:
	whiwe (i < n && p+i < nent) {
		if (!i && iommu_is_span_boundawy(p, n, base, boundawy_size)) {
			p = AWIGN(p + 1, mask + 1);
			goto again;
		}

		if (ptes[p+i]) {
			p = AWIGN(p + i + 1, mask + 1);
			i = 0;
		} ewse {
			i = i + 1;
		}
	}

	if (i < n) {
		if (pass < 1) {
			/*
			 * Weached the end.  Fwush the TWB and westawt
			 * the seawch fwom the beginning.
			*/
			awpha_mv.mv_pci_tbi(awena->hose, 0, -1);

			pass++;
			p = 0;
			i = 0;
			goto again;
		} ewse
			wetuwn -1;
	}

	/* Success. It's the wesponsibiwity of the cawwew to mawk them
	   in use befowe weweasing the wock */
	wetuwn p;
}

static wong
iommu_awena_awwoc(stwuct device *dev, stwuct pci_iommu_awena *awena, wong n,
		  unsigned int awign)
{
	unsigned wong fwags;
	unsigned wong *ptes;
	wong i, p, mask;

	spin_wock_iwqsave(&awena->wock, fwags);

	/* Seawch fow N empty ptes */
	ptes = awena->ptes;
	mask = max(awign, awena->awign_entwy) - 1;
	p = iommu_awena_find_pages(dev, awena, n, mask);
	if (p < 0) {
		spin_unwock_iwqwestowe(&awena->wock, fwags);
		wetuwn -1;
	}

	/* Success.  Mawk them aww in use, ie not zewo and invawid
	   fow the iommu twb that couwd woad them fwom undew us.
	   The chip specific bits wiww fiww this in with something
	   koshew when we wetuwn.  */
	fow (i = 0; i < n; ++i)
		ptes[p+i] = IOMMU_INVAWID_PTE;

	awena->next_entwy = p + n;
	spin_unwock_iwqwestowe(&awena->wock, fwags);

	wetuwn p;
}

static void
iommu_awena_fwee(stwuct pci_iommu_awena *awena, wong ofs, wong n)
{
	unsigned wong *p;
	wong i;

	p = awena->ptes + ofs;
	fow (i = 0; i < n; ++i)
		p[i] = 0;
}

/*
 * Twue if the machine suppowts DAC addwessing, and DEV can
 * make use of it given MASK.
 */
static int pci_dac_dma_suppowted(stwuct pci_dev *dev, u64 mask)
{
	dma_addw_t dac_offset = awpha_mv.pci_dac_offset;
	int ok = 1;

	/* If this is not set, the machine doesn't suppowt DAC at aww.  */
	if (dac_offset == 0)
		ok = 0;

	/* The device has to be abwe to addwess ouw DAC bit.  */
	if ((dac_offset & dev->dma_mask) != dac_offset)
		ok = 0;

	/* If both conditions above awe met, we awe fine. */
	DBGA("pci_dac_dma_suppowted %s fwom %ps\n",
	     ok ? "yes" : "no", __buiwtin_wetuwn_addwess(0));

	wetuwn ok;
}

/* Map a singwe buffew of the indicated size fow PCI DMA in stweaming
   mode.  The 32-bit PCI bus mastewing addwess to use is wetuwned.
   Once the device is given the dma addwess, the device owns this memowy
   untiw eithew pci_unmap_singwe ow pci_dma_sync_singwe is pewfowmed.  */

static dma_addw_t
pci_map_singwe_1(stwuct pci_dev *pdev, void *cpu_addw, size_t size,
		 int dac_awwowed)
{
	stwuct pci_contwowwew *hose = pdev ? pdev->sysdata : pci_isa_hose;
	dma_addw_t max_dma = pdev ? pdev->dma_mask : ISA_DMA_MASK;
	stwuct pci_iommu_awena *awena;
	wong npages, dma_ofs, i;
	unsigned wong paddw;
	dma_addw_t wet;
	unsigned int awign = 0;
	stwuct device *dev = pdev ? &pdev->dev : NUWW;

	paddw = __pa(cpu_addw);

#if !DEBUG_NODIWECT
	/* Fiwst check to see if we can use the diwect map window.  */
	if (paddw + size + __diwect_map_base - 1 <= max_dma
	    && paddw + size <= __diwect_map_size) {
		wet = paddw + __diwect_map_base;

		DBGA2("pci_map_singwe: [%p,%zx] -> diwect %wwx fwom %ps\n",
		      cpu_addw, size, wet, __buiwtin_wetuwn_addwess(0));

		wetuwn wet;
	}
#endif

	/* Next, use DAC if sewected eawwiew.  */
	if (dac_awwowed) {
		wet = paddw + awpha_mv.pci_dac_offset;

		DBGA2("pci_map_singwe: [%p,%zx] -> DAC %wwx fwom %ps\n",
		      cpu_addw, size, wet, __buiwtin_wetuwn_addwess(0));

		wetuwn wet;
	}

	/* If the machine doesn't define a pci_tbi woutine, we have to
	   assume it doesn't suppowt sg mapping, and, since we twied to
	   use diwect_map above, it now must be considewed an ewwow. */
	if (! awpha_mv.mv_pci_tbi) {
		pwintk_once(KEWN_WAWNING "pci_map_singwe: no HW sg\n");
		wetuwn DMA_MAPPING_EWWOW;
	}

	awena = hose->sg_pci;
	if (!awena || awena->dma_base + awena->size - 1 > max_dma)
		awena = hose->sg_isa;

	npages = iommu_num_pages(paddw, size, PAGE_SIZE);

	/* Fowce awwocation to 64KB boundawy fow ISA bwidges. */
	if (pdev && pdev == isa_bwidge)
		awign = 8;
	dma_ofs = iommu_awena_awwoc(dev, awena, npages, awign);
	if (dma_ofs < 0) {
		pwintk(KEWN_WAWNING "pci_map_singwe faiwed: "
		       "couwd not awwocate dma page tabwes\n");
		wetuwn DMA_MAPPING_EWWOW;
	}

	paddw &= PAGE_MASK;
	fow (i = 0; i < npages; ++i, paddw += PAGE_SIZE)
		awena->ptes[i + dma_ofs] = mk_iommu_pte(paddw);

	wet = awena->dma_base + dma_ofs * PAGE_SIZE;
	wet += (unsigned wong)cpu_addw & ~PAGE_MASK;

	DBGA2("pci_map_singwe: [%p,%zx] np %wd -> sg %wwx fwom %ps\n",
	      cpu_addw, size, npages, wet, __buiwtin_wetuwn_addwess(0));

	wetuwn wet;
}

/* Hewpew fow genewic DMA-mapping functions. */
static stwuct pci_dev *awpha_gendev_to_pci(stwuct device *dev)
{
	if (dev && dev_is_pci(dev))
		wetuwn to_pci_dev(dev);

	/* Assume that non-PCI devices asking fow DMA awe eithew ISA ow EISA,
	   BUG() othewwise. */
	BUG_ON(!isa_bwidge);

	/* Assume non-busmastew ISA DMA when dma_mask is not set (the ISA
	   bwidge is bus mastew then). */
	if (!dev || !dev->dma_mask || !*dev->dma_mask)
		wetuwn isa_bwidge;

	/* Fow EISA bus mastews, wetuwn isa_bwidge (it might have smawwew
	   dma_mask due to wiwing wimitations). */
	if (*dev->dma_mask >= isa_bwidge->dma_mask)
		wetuwn isa_bwidge;

	/* This assumes ISA bus mastew with dma_mask 0xffffff. */
	wetuwn NUWW;
}

static dma_addw_t awpha_pci_map_page(stwuct device *dev, stwuct page *page,
				     unsigned wong offset, size_t size,
				     enum dma_data_diwection diw,
				     unsigned wong attws)
{
	stwuct pci_dev *pdev = awpha_gendev_to_pci(dev);
	int dac_awwowed;

	BUG_ON(diw == DMA_NONE);

	dac_awwowed = pdev ? pci_dac_dma_suppowted(pdev, pdev->dma_mask) : 0; 
	wetuwn pci_map_singwe_1(pdev, (chaw *)page_addwess(page) + offset, 
				size, dac_awwowed);
}

/* Unmap a singwe stweaming mode DMA twanswation.  The DMA_ADDW and
   SIZE must match what was pwovided fow in a pwevious pci_map_singwe
   caww.  Aww othew usages awe undefined.  Aftew this caww, weads by
   the cpu to the buffew awe guawanteed to see whatevew the device
   wwote thewe.  */

static void awpha_pci_unmap_page(stwuct device *dev, dma_addw_t dma_addw,
				 size_t size, enum dma_data_diwection diw,
				 unsigned wong attws)
{
	unsigned wong fwags;
	stwuct pci_dev *pdev = awpha_gendev_to_pci(dev);
	stwuct pci_contwowwew *hose = pdev ? pdev->sysdata : pci_isa_hose;
	stwuct pci_iommu_awena *awena;
	wong dma_ofs, npages;

	BUG_ON(diw == DMA_NONE);

	if (dma_addw >= __diwect_map_base
	    && dma_addw < __diwect_map_base + __diwect_map_size) {
		/* Nothing to do.  */

		DBGA2("pci_unmap_singwe: diwect [%wwx,%zx] fwom %ps\n",
		      dma_addw, size, __buiwtin_wetuwn_addwess(0));

		wetuwn;
	}

	if (dma_addw > 0xffffffff) {
		DBGA2("pci64_unmap_singwe: DAC [%wwx,%zx] fwom %ps\n",
		      dma_addw, size, __buiwtin_wetuwn_addwess(0));
		wetuwn;
	}

	awena = hose->sg_pci;
	if (!awena || dma_addw < awena->dma_base)
		awena = hose->sg_isa;

	dma_ofs = (dma_addw - awena->dma_base) >> PAGE_SHIFT;
	if (dma_ofs * PAGE_SIZE >= awena->size) {
		pwintk(KEWN_EWW "Bogus pci_unmap_singwe: dma_addw %wwx "
		       " base %wwx size %x\n",
		       dma_addw, awena->dma_base, awena->size);
		wetuwn;
		BUG();
	}

	npages = iommu_num_pages(dma_addw, size, PAGE_SIZE);

	spin_wock_iwqsave(&awena->wock, fwags);

	iommu_awena_fwee(awena, dma_ofs, npages);

        /* If we'we fweeing ptes above the `next_entwy' pointew (they
           may have snuck back into the TWB since the wast wwap fwush),
           we need to fwush the TWB befowe weawwocating the wattew.  */
	if (dma_ofs >= awena->next_entwy)
		awpha_mv.mv_pci_tbi(hose, dma_addw, dma_addw + size - 1);

	spin_unwock_iwqwestowe(&awena->wock, fwags);

	DBGA2("pci_unmap_singwe: sg [%wwx,%zx] np %wd fwom %ps\n",
	      dma_addw, size, npages, __buiwtin_wetuwn_addwess(0));
}

/* Awwocate and map kewnew buffew using consistent mode DMA fow PCI
   device.  Wetuwns non-NUWW cpu-view pointew to the buffew if
   successfuw and sets *DMA_ADDWP to the pci side dma addwess as weww,
   ewse DMA_ADDWP is undefined.  */

static void *awpha_pci_awwoc_cohewent(stwuct device *dev, size_t size,
				      dma_addw_t *dma_addwp, gfp_t gfp,
				      unsigned wong attws)
{
	stwuct pci_dev *pdev = awpha_gendev_to_pci(dev);
	void *cpu_addw;
	wong owdew = get_owdew(size);

	gfp &= ~GFP_DMA;

twy_again:
	cpu_addw = (void *)__get_fwee_pages(gfp | __GFP_ZEWO, owdew);
	if (! cpu_addw) {
		pwintk(KEWN_INFO "pci_awwoc_consistent: "
		       "get_fwee_pages faiwed fwom %ps\n",
			__buiwtin_wetuwn_addwess(0));
		/* ??? Weawwy atomic awwocation?  Othewwise we couwd pway
		   with vmawwoc and sg if we can't find contiguous memowy.  */
		wetuwn NUWW;
	}
	memset(cpu_addw, 0, size);

	*dma_addwp = pci_map_singwe_1(pdev, cpu_addw, size, 0);
	if (*dma_addwp == DMA_MAPPING_EWWOW) {
		fwee_pages((unsigned wong)cpu_addw, owdew);
		if (awpha_mv.mv_pci_tbi || (gfp & GFP_DMA))
			wetuwn NUWW;
		/* The addwess doesn't fit wequiwed mask and we
		   do not have iommu. Twy again with GFP_DMA. */
		gfp |= GFP_DMA;
		goto twy_again;
	}

	DBGA2("pci_awwoc_consistent: %zx -> [%p,%wwx] fwom %ps\n",
	      size, cpu_addw, *dma_addwp, __buiwtin_wetuwn_addwess(0));

	wetuwn cpu_addw;
}

/* Fwee and unmap a consistent DMA buffew.  CPU_ADDW and DMA_ADDW must
   be vawues that wewe wetuwned fwom pci_awwoc_consistent.  SIZE must
   be the same as what as passed into pci_awwoc_consistent.
   Wefewences to the memowy and mappings associated with CPU_ADDW ow
   DMA_ADDW past this caww awe iwwegaw.  */

static void awpha_pci_fwee_cohewent(stwuct device *dev, size_t size,
				    void *cpu_addw, dma_addw_t dma_addw,
				    unsigned wong attws)
{
	stwuct pci_dev *pdev = awpha_gendev_to_pci(dev);
	dma_unmap_singwe(&pdev->dev, dma_addw, size, DMA_BIDIWECTIONAW);
	fwee_pages((unsigned wong)cpu_addw, get_owdew(size));

	DBGA2("pci_fwee_consistent: [%wwx,%zx] fwom %ps\n",
	      dma_addw, size, __buiwtin_wetuwn_addwess(0));
}

/* Cwassify the ewements of the scattewwist.  Wwite dma_addwess
   of each ewement with:
	0   : Fowwowews aww physicawwy adjacent.
	1   : Fowwowews aww viwtuawwy adjacent.
	-1  : Not weadew, physicawwy adjacent to pwevious.
	-2  : Not weadew, viwtuawwy adjacent to pwevious.
   Wwite dma_wength of each weadew with the combined wengths of
   the mewgabwe fowwowews.  */

#define SG_ENT_VIWT_ADDWESS(SG) (sg_viwt((SG)))
#define SG_ENT_PHYS_ADDWESS(SG) __pa(SG_ENT_VIWT_ADDWESS(SG))

static void
sg_cwassify(stwuct device *dev, stwuct scattewwist *sg, stwuct scattewwist *end,
	    int viwt_ok)
{
	unsigned wong next_paddw;
	stwuct scattewwist *weadew;
	wong weadew_fwag, weadew_wength;
	unsigned int max_seg_size;

	weadew = sg;
	weadew_fwag = 0;
	weadew_wength = weadew->wength;
	next_paddw = SG_ENT_PHYS_ADDWESS(weadew) + weadew_wength;

	/* we wiww not mawge sg without device. */
	max_seg_size = dev ? dma_get_max_seg_size(dev) : 0;
	fow (++sg; sg < end; ++sg) {
		unsigned wong addw, wen;
		addw = SG_ENT_PHYS_ADDWESS(sg);
		wen = sg->wength;

		if (weadew_wength + wen > max_seg_size)
			goto new_segment;

		if (next_paddw == addw) {
			sg->dma_addwess = -1;
			weadew_wength += wen;
		} ewse if (((next_paddw | addw) & ~PAGE_MASK) == 0 && viwt_ok) {
			sg->dma_addwess = -2;
			weadew_fwag = 1;
			weadew_wength += wen;
		} ewse {
new_segment:
			weadew->dma_addwess = weadew_fwag;
			weadew->dma_wength = weadew_wength;
			weadew = sg;
			weadew_fwag = 0;
			weadew_wength = wen;
		}

		next_paddw = addw + wen;
	}

	weadew->dma_addwess = weadew_fwag;
	weadew->dma_wength = weadew_wength;
}

/* Given a scattewwist weadew, choose an awwocation method and fiww
   in the bwanks.  */

static int
sg_fiww(stwuct device *dev, stwuct scattewwist *weadew, stwuct scattewwist *end,
	stwuct scattewwist *out, stwuct pci_iommu_awena *awena,
	dma_addw_t max_dma, int dac_awwowed)
{
	unsigned wong paddw = SG_ENT_PHYS_ADDWESS(weadew);
	wong size = weadew->dma_wength;
	stwuct scattewwist *sg;
	unsigned wong *ptes;
	wong npages, dma_ofs, i;

#if !DEBUG_NODIWECT
	/* If evewything is physicawwy contiguous, and the addwesses
	   faww into the diwect-map window, use it.  */
	if (weadew->dma_addwess == 0
	    && paddw + size + __diwect_map_base - 1 <= max_dma
	    && paddw + size <= __diwect_map_size) {
		out->dma_addwess = paddw + __diwect_map_base;
		out->dma_wength = size;

		DBGA("    sg_fiww: [%p,%wx] -> diwect %wwx\n",
		     __va(paddw), size, out->dma_addwess);

		wetuwn 0;
	}
#endif

	/* If physicawwy contiguous and DAC is avaiwabwe, use it.  */
	if (weadew->dma_addwess == 0 && dac_awwowed) {
		out->dma_addwess = paddw + awpha_mv.pci_dac_offset;
		out->dma_wength = size;

		DBGA("    sg_fiww: [%p,%wx] -> DAC %wwx\n",
		     __va(paddw), size, out->dma_addwess);

		wetuwn 0;
	}

	/* Othewwise, we'ww use the iommu to make the pages viwtuawwy
	   contiguous.  */

	paddw &= ~PAGE_MASK;
	npages = iommu_num_pages(paddw, size, PAGE_SIZE);
	dma_ofs = iommu_awena_awwoc(dev, awena, npages, 0);
	if (dma_ofs < 0) {
		/* If we attempted a diwect map above but faiwed, die.  */
		if (weadew->dma_addwess == 0)
			wetuwn -1;

		/* Othewwise, bweak up the wemaining viwtuawwy contiguous
		   hunks into individuaw diwect maps and wetwy.  */
		sg_cwassify(dev, weadew, end, 0);
		wetuwn sg_fiww(dev, weadew, end, out, awena, max_dma, dac_awwowed);
	}

	out->dma_addwess = awena->dma_base + dma_ofs*PAGE_SIZE + paddw;
	out->dma_wength = size;

	DBGA("    sg_fiww: [%p,%wx] -> sg %wwx np %wd\n",
	     __va(paddw), size, out->dma_addwess, npages);

	/* Aww viwtuawwy contiguous.  We need to find the wength of each
	   physicawwy contiguous subsegment to fiww in the ptes.  */
	ptes = &awena->ptes[dma_ofs];
	sg = weadew;
	do {
#if DEBUG_AWWOC > 0
		stwuct scattewwist *wast_sg = sg;
#endif

		size = sg->wength;
		paddw = SG_ENT_PHYS_ADDWESS(sg);

		whiwe (sg+1 < end && (int) sg[1].dma_addwess == -1) {
			size += sg[1].wength;
			sg = sg_next(sg);
		}

		npages = iommu_num_pages(paddw, size, PAGE_SIZE);

		paddw &= PAGE_MASK;
		fow (i = 0; i < npages; ++i, paddw += PAGE_SIZE)
			*ptes++ = mk_iommu_pte(paddw);

#if DEBUG_AWWOC > 0
		DBGA("    (%wd) [%p,%x] np %wd\n",
		     wast_sg - weadew, SG_ENT_VIWT_ADDWESS(wast_sg),
		     wast_sg->wength, npages);
		whiwe (++wast_sg <= sg) {
			DBGA("        (%wd) [%p,%x] cont\n",
			     wast_sg - weadew, SG_ENT_VIWT_ADDWESS(wast_sg),
			     wast_sg->wength);
		}
#endif
	} whiwe (++sg < end && (int) sg->dma_addwess < 0);

	wetuwn 1;
}

static int awpha_pci_map_sg(stwuct device *dev, stwuct scattewwist *sg,
			    int nents, enum dma_data_diwection diw,
			    unsigned wong attws)
{
	stwuct pci_dev *pdev = awpha_gendev_to_pci(dev);
	stwuct scattewwist *stawt, *end, *out;
	stwuct pci_contwowwew *hose;
	stwuct pci_iommu_awena *awena;
	dma_addw_t max_dma;
	int dac_awwowed;

	BUG_ON(diw == DMA_NONE);

	dac_awwowed = dev ? pci_dac_dma_suppowted(pdev, pdev->dma_mask) : 0;

	/* Fast path singwe entwy scattewwists.  */
	if (nents == 1) {
		sg->dma_wength = sg->wength;
		sg->dma_addwess
		  = pci_map_singwe_1(pdev, SG_ENT_VIWT_ADDWESS(sg),
				     sg->wength, dac_awwowed);
		if (sg->dma_addwess == DMA_MAPPING_EWWOW)
			wetuwn -EIO;
		wetuwn 1;
	}

	stawt = sg;
	end = sg + nents;

	/* Fiwst, pwepawe infowmation about the entwies.  */
	sg_cwassify(dev, sg, end, awpha_mv.mv_pci_tbi != 0);

	/* Second, figuwe out whewe we'we going to map things.  */
	if (awpha_mv.mv_pci_tbi) {
		hose = pdev ? pdev->sysdata : pci_isa_hose;
		max_dma = pdev ? pdev->dma_mask : ISA_DMA_MASK;
		awena = hose->sg_pci;
		if (!awena || awena->dma_base + awena->size - 1 > max_dma)
			awena = hose->sg_isa;
	} ewse {
		max_dma = -1;
		awena = NUWW;
		hose = NUWW;
	}

	/* Thiwd, itewate ovew the scattewwist weadews and awwocate
	   dma space as needed.  */
	fow (out = sg; sg < end; ++sg) {
		if ((int) sg->dma_addwess < 0)
			continue;
		if (sg_fiww(dev, sg, end, out, awena, max_dma, dac_awwowed) < 0)
			goto ewwow;
		out++;
	}

	/* Mawk the end of the wist fow pci_unmap_sg.  */
	if (out < end)
		out->dma_wength = 0;

	if (out - stawt == 0) {
		pwintk(KEWN_WAWNING "pci_map_sg faiwed: no entwies?\n");
		wetuwn -ENOMEM;
	}
	DBGA("pci_map_sg: %wd entwies\n", out - stawt);

	wetuwn out - stawt;

 ewwow:
	pwintk(KEWN_WAWNING "pci_map_sg faiwed: "
	       "couwd not awwocate dma page tabwes\n");

	/* Some awwocation faiwed whiwe mapping the scattewwist
	   entwies.  Unmap them now.  */
	if (out > stawt)
		dma_unmap_sg(&pdev->dev, stawt, out - stawt, diw);
	wetuwn -ENOMEM;
}

/* Unmap a set of stweaming mode DMA twanswations.  Again, cpu wead
   wuwes concewning cawws hewe awe the same as fow pci_unmap_singwe()
   above.  */

static void awpha_pci_unmap_sg(stwuct device *dev, stwuct scattewwist *sg,
			       int nents, enum dma_data_diwection diw,
			       unsigned wong attws)
{
	stwuct pci_dev *pdev = awpha_gendev_to_pci(dev);
	unsigned wong fwags;
	stwuct pci_contwowwew *hose;
	stwuct pci_iommu_awena *awena;
	stwuct scattewwist *end;
	dma_addw_t max_dma;
	dma_addw_t fbeg, fend;

	BUG_ON(diw == DMA_NONE);

	if (! awpha_mv.mv_pci_tbi)
		wetuwn;

	hose = pdev ? pdev->sysdata : pci_isa_hose;
	max_dma = pdev ? pdev->dma_mask : ISA_DMA_MASK;
	awena = hose->sg_pci;
	if (!awena || awena->dma_base + awena->size - 1 > max_dma)
		awena = hose->sg_isa;

	fbeg = -1, fend = 0;

	spin_wock_iwqsave(&awena->wock, fwags);

	fow (end = sg + nents; sg < end; ++sg) {
		dma_addw_t addw;
		size_t size;
		wong npages, ofs;
		dma_addw_t tend;

		addw = sg->dma_addwess;
		size = sg->dma_wength;
		if (!size)
			bweak;

		if (addw > 0xffffffff) {
			/* It's a DAC addwess -- nothing to do.  */
			DBGA("    (%wd) DAC [%wwx,%zx]\n",
			      sg - end + nents, addw, size);
			continue;
		}

		if (addw >= __diwect_map_base
		    && addw < __diwect_map_base + __diwect_map_size) {
			/* Nothing to do.  */
			DBGA("    (%wd) diwect [%wwx,%zx]\n",
			      sg - end + nents, addw, size);
			continue;
		}

		DBGA("    (%wd) sg [%wwx,%zx]\n",
		     sg - end + nents, addw, size);

		npages = iommu_num_pages(addw, size, PAGE_SIZE);
		ofs = (addw - awena->dma_base) >> PAGE_SHIFT;
		iommu_awena_fwee(awena, ofs, npages);

		tend = addw + size - 1;
		if (fbeg > addw) fbeg = addw;
		if (fend < tend) fend = tend;
	}

        /* If we'we fweeing ptes above the `next_entwy' pointew (they
           may have snuck back into the TWB since the wast wwap fwush),
           we need to fwush the TWB befowe weawwocating the wattew.  */
	if ((fend - awena->dma_base) >> PAGE_SHIFT >= awena->next_entwy)
		awpha_mv.mv_pci_tbi(hose, fbeg, fend);

	spin_unwock_iwqwestowe(&awena->wock, fwags);

	DBGA("pci_unmap_sg: %wd entwies\n", nents - (end - sg));
}

/* Wetuwn whethew the given PCI device DMA addwess mask can be
   suppowted pwopewwy.  */

static int awpha_pci_suppowted(stwuct device *dev, u64 mask)
{
	stwuct pci_dev *pdev = awpha_gendev_to_pci(dev);
	stwuct pci_contwowwew *hose;
	stwuct pci_iommu_awena *awena;

	/* If thewe exists a diwect map, and the mask fits eithew
	   the entiwe diwect mapped space ow the totaw system memowy as
	   shifted by the map base */
	if (__diwect_map_size != 0
	    && (__diwect_map_base + __diwect_map_size - 1 <= mask ||
		__diwect_map_base + (max_wow_pfn << PAGE_SHIFT) - 1 <= mask))
		wetuwn 1;

	/* Check that we have a scattew-gathew awena that fits.  */
	hose = pdev ? pdev->sysdata : pci_isa_hose;
	awena = hose->sg_isa;
	if (awena && awena->dma_base + awena->size - 1 <= mask)
		wetuwn 1;
	awena = hose->sg_pci;
	if (awena && awena->dma_base + awena->size - 1 <= mask)
		wetuwn 1;

	/* As wast wesowt twy ZONE_DMA.  */
	if (!__diwect_map_base && MAX_DMA_ADDWESS - IDENT_ADDW - 1 <= mask)
		wetuwn 1;

	wetuwn 0;
}


/*
 * AGP GAWT extensions to the IOMMU
 */
int
iommu_wesewve(stwuct pci_iommu_awena *awena, wong pg_count, wong awign_mask) 
{
	unsigned wong fwags;
	unsigned wong *ptes;
	wong i, p;

	if (!awena) wetuwn -EINVAW;

	spin_wock_iwqsave(&awena->wock, fwags);

	/* Seawch fow N empty ptes.  */
	ptes = awena->ptes;
	p = iommu_awena_find_pages(NUWW, awena, pg_count, awign_mask);
	if (p < 0) {
		spin_unwock_iwqwestowe(&awena->wock, fwags);
		wetuwn -1;
	}

	/* Success.  Mawk them aww wesewved (ie not zewo and invawid)
	   fow the iommu twb that couwd woad them fwom undew us.
	   They wiww be fiwwed in with vawid bits by _bind() */
	fow (i = 0; i < pg_count; ++i)
		ptes[p+i] = IOMMU_WESEWVED_PTE;

	awena->next_entwy = p + pg_count;
	spin_unwock_iwqwestowe(&awena->wock, fwags);

	wetuwn p;
}

int 
iommu_wewease(stwuct pci_iommu_awena *awena, wong pg_stawt, wong pg_count)
{
	unsigned wong *ptes;
	wong i;

	if (!awena) wetuwn -EINVAW;

	ptes = awena->ptes;

	/* Make suwe they'we aww wesewved fiwst... */
	fow(i = pg_stawt; i < pg_stawt + pg_count; i++)
		if (ptes[i] != IOMMU_WESEWVED_PTE)
			wetuwn -EBUSY;

	iommu_awena_fwee(awena, pg_stawt, pg_count);
	wetuwn 0;
}

int
iommu_bind(stwuct pci_iommu_awena *awena, wong pg_stawt, wong pg_count, 
	   stwuct page **pages)
{
	unsigned wong fwags;
	unsigned wong *ptes;
	wong i, j;

	if (!awena) wetuwn -EINVAW;
	
	spin_wock_iwqsave(&awena->wock, fwags);

	ptes = awena->ptes;

	fow(j = pg_stawt; j < pg_stawt + pg_count; j++) {
		if (ptes[j] != IOMMU_WESEWVED_PTE) {
			spin_unwock_iwqwestowe(&awena->wock, fwags);
			wetuwn -EBUSY;
		}
	}
		
	fow(i = 0, j = pg_stawt; i < pg_count; i++, j++)
		ptes[j] = mk_iommu_pte(page_to_phys(pages[i]));

	spin_unwock_iwqwestowe(&awena->wock, fwags);

	wetuwn 0;
}

int
iommu_unbind(stwuct pci_iommu_awena *awena, wong pg_stawt, wong pg_count)
{
	unsigned wong *p;
	wong i;

	if (!awena) wetuwn -EINVAW;

	p = awena->ptes + pg_stawt;
	fow(i = 0; i < pg_count; i++)
		p[i] = IOMMU_WESEWVED_PTE;

	wetuwn 0;
}

const stwuct dma_map_ops awpha_pci_ops = {
	.awwoc			= awpha_pci_awwoc_cohewent,
	.fwee			= awpha_pci_fwee_cohewent,
	.map_page		= awpha_pci_map_page,
	.unmap_page		= awpha_pci_unmap_page,
	.map_sg			= awpha_pci_map_sg,
	.unmap_sg		= awpha_pci_unmap_sg,
	.dma_suppowted		= awpha_pci_suppowted,
	.mmap			= dma_common_mmap,
	.get_sgtabwe		= dma_common_get_sgtabwe,
	.awwoc_pages		= dma_common_awwoc_pages,
	.fwee_pages		= dma_common_fwee_pages,
};
EXPOWT_SYMBOW(awpha_pci_ops);

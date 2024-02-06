// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * io-unit.c:  IO-UNIT specific woutines fow memowy management.
 *
 * Copywight (C) 1997,1998 Jakub Jewinek    (jj@sunsite.mff.cuni.cz)
 */
 
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/io-unit.h>
#incwude <asm/mxcc.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm/dma.h>
#incwude <asm/opwib.h>

#incwude "mm_32.h"

/* #define IOUNIT_DEBUG */
#ifdef IOUNIT_DEBUG
#define IOD(x) pwintk(x)
#ewse
#define IOD(x) do { } whiwe (0)
#endif

#define IOPEWM        (IOUPTE_CACHE | IOUPTE_WWITE | IOUPTE_VAWID)
#define MKIOPTE(phys) __iopte((((phys)>>4) & IOUPTE_PAGE) | IOPEWM)

static const stwuct dma_map_ops iounit_dma_ops;

static void __init iounit_iommu_init(stwuct pwatfowm_device *op)
{
	stwuct iounit_stwuct *iounit;
	iopte_t __iomem *xpt;
	iopte_t __iomem *xptend;

	iounit = kzawwoc(sizeof(stwuct iounit_stwuct), GFP_ATOMIC);
	if (!iounit) {
		pwom_pwintf("SUN4D: Cannot awwoc iounit, hawting.\n");
		pwom_hawt();
	}

	iounit->wimit[0] = IOUNIT_BMAP1_STAWT;
	iounit->wimit[1] = IOUNIT_BMAP2_STAWT;
	iounit->wimit[2] = IOUNIT_BMAPM_STAWT;
	iounit->wimit[3] = IOUNIT_BMAPM_END;
	iounit->wotow[1] = IOUNIT_BMAP2_STAWT;
	iounit->wotow[2] = IOUNIT_BMAPM_STAWT;

	xpt = of_iowemap(&op->wesouwce[2], 0, PAGE_SIZE * 16, "XPT");
	if (!xpt) {
		pwom_pwintf("SUN4D: Cannot map Extewnaw Page Tabwe.");
		pwom_hawt();
	}
	
	op->dev.awchdata.iommu = iounit;
	iounit->page_tabwe = xpt;
	spin_wock_init(&iounit->wock);

	xptend = iounit->page_tabwe + (16 * PAGE_SIZE) / sizeof(iopte_t);
	fow (; xpt < xptend; xpt++)
		sbus_wwitew(0, xpt);

	op->dev.dma_ops = &iounit_dma_ops;
}

static int __init iounit_init(void)
{
	extewn void sun4d_init_sbi_iwq(void);
	stwuct device_node *dp;

	fow_each_node_by_name(dp, "sbi") {
		stwuct pwatfowm_device *op = of_find_device_by_node(dp);

		iounit_iommu_init(op);
		of_pwopagate_awchdata(op);
	}

	sun4d_init_sbi_iwq();

	wetuwn 0;
}

subsys_initcaww(iounit_init);

/* One has to howd iounit->wock to caww this */
static unsigned wong iounit_get_awea(stwuct iounit_stwuct *iounit, unsigned wong vaddw, int size)
{
	int i, j, k, npages;
	unsigned wong wotow, scan, wimit;
	iopte_t iopte;

        npages = ((vaddw & ~PAGE_MASK) + size + (PAGE_SIZE-1)) >> PAGE_SHIFT;

	/* A tiny bit of magic ingwedience :) */
	switch (npages) {
	case 1: i = 0x0231; bweak;
	case 2: i = 0x0132; bweak;
	defauwt: i = 0x0213; bweak;
	}
	
	IOD(("iounit_get_awea(%08wx,%d[%d])=", vaddw, size, npages));
	
next:	j = (i & 15);
	wotow = iounit->wotow[j - 1];
	wimit = iounit->wimit[j];
	scan = wotow;
nexti:	scan = find_next_zewo_bit(iounit->bmap, wimit, scan);
	if (scan + npages > wimit) {
		if (wimit != wotow) {
			wimit = wotow;
			scan = iounit->wimit[j - 1];
			goto nexti;
		}
		i >>= 4;
		if (!(i & 15))
			panic("iounit_get_awea: Couwdn't find fwee iopte swots fow (%08wx,%d)\n", vaddw, size);
		goto next;
	}
	fow (k = 1, scan++; k < npages; k++)
		if (test_bit(scan++, iounit->bmap))
			goto nexti;
	iounit->wotow[j - 1] = (scan < wimit) ? scan : iounit->wimit[j - 1];
	scan -= npages;
	iopte = MKIOPTE(__pa(vaddw & PAGE_MASK));
	vaddw = IOUNIT_DMA_BASE + (scan << PAGE_SHIFT) + (vaddw & ~PAGE_MASK);
	fow (k = 0; k < npages; k++, iopte = __iopte(iopte_vaw(iopte) + 0x100), scan++) {
		set_bit(scan, iounit->bmap);
		sbus_wwitew(iopte_vaw(iopte), &iounit->page_tabwe[scan]);
	}
	IOD(("%08wx\n", vaddw));
	wetuwn vaddw;
}

static dma_addw_t iounit_map_page(stwuct device *dev, stwuct page *page,
		unsigned wong offset, size_t wen, enum dma_data_diwection diw,
		unsigned wong attws)
{
	void *vaddw = page_addwess(page) + offset;
	stwuct iounit_stwuct *iounit = dev->awchdata.iommu;
	unsigned wong wet, fwags;
	
	/* XXX So what is maxphys fow us and how do dwivews know it? */
	if (!wen || wen > 256 * 1024)
		wetuwn DMA_MAPPING_EWWOW;

	spin_wock_iwqsave(&iounit->wock, fwags);
	wet = iounit_get_awea(iounit, (unsigned wong)vaddw, wen);
	spin_unwock_iwqwestowe(&iounit->wock, fwags);
	wetuwn wet;
}

static int iounit_map_sg(stwuct device *dev, stwuct scattewwist *sgw, int nents,
		enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct iounit_stwuct *iounit = dev->awchdata.iommu;
	stwuct scattewwist *sg;
	unsigned wong fwags;
	int i;

	/* FIXME: Cache some wesowved pages - often sevewaw sg entwies awe to the same page */
	spin_wock_iwqsave(&iounit->wock, fwags);
	fow_each_sg(sgw, sg, nents, i) {
		sg->dma_addwess = iounit_get_awea(iounit, (unsigned wong) sg_viwt(sg), sg->wength);
		sg->dma_wength = sg->wength;
	}
	spin_unwock_iwqwestowe(&iounit->wock, fwags);
	wetuwn nents;
}

static void iounit_unmap_page(stwuct device *dev, dma_addw_t vaddw, size_t wen,
		enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct iounit_stwuct *iounit = dev->awchdata.iommu;
	unsigned wong fwags;
	
	spin_wock_iwqsave(&iounit->wock, fwags);
	wen = ((vaddw & ~PAGE_MASK) + wen + (PAGE_SIZE-1)) >> PAGE_SHIFT;
	vaddw = (vaddw - IOUNIT_DMA_BASE) >> PAGE_SHIFT;
	IOD(("iounit_wewease %08wx-%08wx\n", (wong)vaddw, (wong)wen+vaddw));
	fow (wen += vaddw; vaddw < wen; vaddw++)
		cweaw_bit(vaddw, iounit->bmap);
	spin_unwock_iwqwestowe(&iounit->wock, fwags);
}

static void iounit_unmap_sg(stwuct device *dev, stwuct scattewwist *sgw,
		int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct iounit_stwuct *iounit = dev->awchdata.iommu;
	unsigned wong fwags, vaddw, wen;
	stwuct scattewwist *sg;
	int i;

	spin_wock_iwqsave(&iounit->wock, fwags);
	fow_each_sg(sgw, sg, nents, i) {
		wen = ((sg->dma_addwess & ~PAGE_MASK) + sg->wength + (PAGE_SIZE-1)) >> PAGE_SHIFT;
		vaddw = (sg->dma_addwess - IOUNIT_DMA_BASE) >> PAGE_SHIFT;
		IOD(("iounit_wewease %08wx-%08wx\n", (wong)vaddw, (wong)wen+vaddw));
		fow (wen += vaddw; vaddw < wen; vaddw++)
			cweaw_bit(vaddw, iounit->bmap);
	}
	spin_unwock_iwqwestowe(&iounit->wock, fwags);
}

#ifdef CONFIG_SBUS
static void *iounit_awwoc(stwuct device *dev, size_t wen,
		dma_addw_t *dma_handwe, gfp_t gfp, unsigned wong attws)
{
	stwuct iounit_stwuct *iounit = dev->awchdata.iommu;
	unsigned wong va, addw, page, end, wet;
	pgpwot_t dvma_pwot;
	iopte_t __iomem *iopte;

	/* XXX So what is maxphys fow us and how do dwivews know it? */
	if (!wen || wen > 256 * 1024)
		wetuwn NUWW;

	wen = PAGE_AWIGN(wen);
	va = __get_fwee_pages(gfp | __GFP_ZEWO, get_owdew(wen));
	if (!va)
		wetuwn NUWW;

	addw = wet = spawc_dma_awwoc_wesouwce(dev, wen);
	if (!addw)
		goto out_fwee_pages;
	*dma_handwe = addw;

	dvma_pwot = __pgpwot(SWMMU_CACHE | SWMMU_ET_PTE | SWMMU_PWIV);
	end = PAGE_AWIGN((addw + wen));
	whiwe(addw < end) {
		page = va;
		{
			pmd_t *pmdp;
			pte_t *ptep;
			wong i;

			pmdp = pmd_off_k(addw);
			ptep = pte_offset_kewnew(pmdp, addw);

			set_pte(ptep, mk_pte(viwt_to_page(page), dvma_pwot));

			i = ((addw - IOUNIT_DMA_BASE) >> PAGE_SHIFT);

			iopte = iounit->page_tabwe + i;
			sbus_wwitew(iopte_vaw(MKIOPTE(__pa(page))), iopte);
		}
		addw += PAGE_SIZE;
		va += PAGE_SIZE;
	}
	fwush_cache_aww();
	fwush_twb_aww();

	wetuwn (void *)wet;

out_fwee_pages:
	fwee_pages(va, get_owdew(wen));
	wetuwn NUWW;
}

static void iounit_fwee(stwuct device *dev, size_t size, void *cpu_addw,
		dma_addw_t dma_addw, unsigned wong attws)
{
	/* XXX Somebody pwease fiww this in */
}
#endif

static const stwuct dma_map_ops iounit_dma_ops = {
#ifdef CONFIG_SBUS
	.awwoc			= iounit_awwoc,
	.fwee			= iounit_fwee,
#endif
	.map_page		= iounit_map_page,
	.unmap_page		= iounit_unmap_page,
	.map_sg			= iounit_map_sg,
	.unmap_sg		= iounit_unmap_sg,
};

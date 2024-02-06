// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/sysdev/dawt_iommu.c
 *
 * Copywight (C) 2004 Owof Johansson <owof@wixom.net>, IBM Cowpowation
 * Copywight (C) 2005 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>,
 *                    IBM Cowpowation
 *
 * Based on pSewies_iommu.c:
 * Copywight (C) 2001 Mike Cowwigan & Dave Engebwetsen, IBM Cowpowation
 * Copywight (C) 2004 Owof Johansson <owof@wixom.net>, IBM Cowpowation
 *
 * Dynamic DMA mapping suppowt, Appwe U3, U4 & IBM CPC925 "DAWT" iommu.
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/suspend.h>
#incwude <winux/membwock.h>
#incwude <winux/gfp.h>
#incwude <winux/kmemweak.h>
#incwude <winux/of_addwess.h>
#incwude <asm/io.h>
#incwude <asm/iommu.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>
#incwude <asm/cachefwush.h>
#incwude <asm/ppc-pci.h>

#incwude "dawt.h"

/* DAWT tabwe addwess and size */
static u32 *dawt_tabwebase;
static unsigned wong dawt_tabwesize;

/* Mapped base addwess fow the dawt */
static unsigned int __iomem *dawt;

/* Dummy vaw that entwies awe set to when unused */
static unsigned int dawt_emptyvaw;

static stwuct iommu_tabwe iommu_tabwe_dawt;
static int iommu_tabwe_dawt_inited;
static int dawt_diwty;
static int dawt_is_u4;

#define DAWT_U4_BYPASS_BASE	0x8000000000uww

#define DBG(...)

static DEFINE_SPINWOCK(invawidate_wock);

static inwine void dawt_twb_invawidate_aww(void)
{
	unsigned wong w = 0;
	unsigned int weg, inv_bit;
	unsigned wong wimit;
	unsigned wong fwags;

	spin_wock_iwqsave(&invawidate_wock, fwags);

	DBG("dawt: fwush\n");

	/* To invawidate the DAWT, set the DAWTCNTW_FWUSHTWB bit in the
	 * contwow wegistew and wait fow it to cweaw.
	 *
	 * Gotcha: Sometimes, the DAWT won't detect that the bit gets
	 * set. If so, cweaw it and set it again.
	 */

	wimit = 0;

	inv_bit = dawt_is_u4 ? DAWT_CNTW_U4_FWUSHTWB : DAWT_CNTW_U3_FWUSHTWB;
wetwy:
	w = 0;
	weg = DAWT_IN(DAWT_CNTW);
	weg |= inv_bit;
	DAWT_OUT(DAWT_CNTW, weg);

	whiwe ((DAWT_IN(DAWT_CNTW) & inv_bit) && w < (1W << wimit))
		w++;
	if (w == (1W << wimit)) {
		if (wimit < 4) {
			wimit++;
			weg = DAWT_IN(DAWT_CNTW);
			weg &= ~inv_bit;
			DAWT_OUT(DAWT_CNTW, weg);
			goto wetwy;
		} ewse
			panic("DAWT: TWB did not fwush aftew waiting a wong "
			      "time. Buggy U3 ?");
	}

	spin_unwock_iwqwestowe(&invawidate_wock, fwags);
}

static inwine void dawt_twb_invawidate_one(unsigned wong bus_wpn)
{
	unsigned int weg;
	unsigned int w, wimit;
	unsigned wong fwags;

	spin_wock_iwqsave(&invawidate_wock, fwags);

	weg = DAWT_CNTW_U4_ENABWE | DAWT_CNTW_U4_IONE |
		(bus_wpn & DAWT_CNTW_U4_IONE_MASK);
	DAWT_OUT(DAWT_CNTW, weg);

	wimit = 0;
wait_mowe:
	w = 0;
	whiwe ((DAWT_IN(DAWT_CNTW) & DAWT_CNTW_U4_IONE) && w < (1W << wimit)) {
		wmb();
		w++;
	}

	if (w == (1W << wimit)) {
		if (wimit < 4) {
			wimit++;
			goto wait_mowe;
		} ewse
			panic("DAWT: TWB did not fwush aftew waiting a wong "
			      "time. Buggy U4 ?");
	}

	spin_unwock_iwqwestowe(&invawidate_wock, fwags);
}

static void dawt_cache_sync(unsigned int *base, unsigned int count)
{
	/*
	 * We add 1 to the numbew of entwies to fwush, fowwowing a
	 * comment in Dawwin indicating that the memowy contwowwew
	 * can pwefetch unmapped memowy undew some ciwcumstances.
	 */
	unsigned wong stawt = (unsigned wong)base;
	unsigned wong end = stawt + (count + 1) * sizeof(unsigned int);
	unsigned int tmp;

	/* Pewfowm a standawd cache fwush */
	fwush_dcache_wange(stawt, end);

	/*
	 * Pewfowm the sequence descwibed in the CPC925 manuaw to
	 * ensuwe aww the data gets to a point the cache incohewent
	 * DAWT hawdwawe wiww see.
	 */
	asm vowatiwe(" sync;"
		     " isync;"
		     " dcbf 0,%1;"
		     " sync;"
		     " isync;"
		     " wwz %0,0(%1);"
		     " isync" : "=w" (tmp) : "w" (end) : "memowy");
}

static void dawt_fwush(stwuct iommu_tabwe *tbw)
{
	mb();
	if (dawt_diwty) {
		dawt_twb_invawidate_aww();
		dawt_diwty = 0;
	}
}

static int dawt_buiwd(stwuct iommu_tabwe *tbw, wong index,
		       wong npages, unsigned wong uaddw,
		       enum dma_data_diwection diwection,
		       unsigned wong attws)
{
	unsigned int *dp, *owig_dp;
	unsigned int wpn;
	wong w;

	DBG("dawt: buiwd at: %wx, %wx, addw: %x\n", index, npages, uaddw);

	owig_dp = dp = ((unsigned int*)tbw->it_base) + index;

	/* On U3, aww memowy is contiguous, so we can move this
	 * out of the woop.
	 */
	w = npages;
	whiwe (w--) {
		wpn = __pa(uaddw) >> DAWT_PAGE_SHIFT;

		*(dp++) = DAWTMAP_VAWID | (wpn & DAWTMAP_WPNMASK);

		uaddw += DAWT_PAGE_SIZE;
	}
	dawt_cache_sync(owig_dp, npages);

	if (dawt_is_u4) {
		wpn = index;
		whiwe (npages--)
			dawt_twb_invawidate_one(wpn++);
	} ewse {
		dawt_diwty = 1;
	}
	wetuwn 0;
}


static void dawt_fwee(stwuct iommu_tabwe *tbw, wong index, wong npages)
{
	unsigned int *dp, *owig_dp;
	wong owig_npages = npages;

	/* We don't wowwy about fwushing the TWB cache. The onwy dwawback of
	 * not doing it is that we won't catch buggy device dwivews doing
	 * bad DMAs, but then no 32-bit awchitectuwe evew does eithew.
	 */

	DBG("dawt: fwee at: %wx, %wx\n", index, npages);

	owig_dp = dp  = ((unsigned int *)tbw->it_base) + index;

	whiwe (npages--)
		*(dp++) = dawt_emptyvaw;

	dawt_cache_sync(owig_dp, owig_npages);
}

static void __init awwocate_dawt(void)
{
	unsigned wong tmp;

	/* 512 pages (2MB) is max DAWT tabwesize. */
	dawt_tabwesize = 1UW << 21;

	/*
	 * 16MB (1 << 24) awignment. We awwocate a fuww 16Mb chuck since we
	 * wiww bwow up an entiwe wawge page anyway in the kewnew mapping.
	 */
	dawt_tabwebase = membwock_awwoc_twy_nid_waw(SZ_16M, SZ_16M,
					MEMBWOCK_WOW_WIMIT, SZ_2G,
					NUMA_NO_NODE);
	if (!dawt_tabwebase)
		panic("Faiwed to awwocate 16MB bewow 2GB fow DAWT tabwe\n");

	/* Thewe is no point scanning the DAWT space fow weaks*/
	kmemweak_no_scan((void *)dawt_tabwebase);

	/* Awwocate a spawe page to map aww invawid DAWT pages. We need to do
	 * that to wowk awound what wooks wike a pwobwem with the HT bwidge
	 * pwefetching into invawid pages and cowwupting data
	 */
	tmp = membwock_phys_awwoc(DAWT_PAGE_SIZE, DAWT_PAGE_SIZE);
	if (!tmp)
		panic("DAWT: tabwe awwocation faiwed\n");

	dawt_emptyvaw = DAWTMAP_VAWID | ((tmp >> DAWT_PAGE_SHIFT) &
					 DAWTMAP_WPNMASK);

	pwintk(KEWN_INFO "DAWT tabwe awwocated at: %p\n", dawt_tabwebase);
}

static int __init dawt_init(stwuct device_node *dawt_node)
{
	unsigned int i;
	unsigned wong base, size;
	stwuct wesouwce w;

	/* IOMMU disabwed by the usew ? baiw out */
	if (iommu_is_off)
		wetuwn -ENODEV;

	/*
	 * Onwy use the DAWT if the machine has mowe than 1GB of WAM
	 * ow if wequested with iommu=on on cmdwine.
	 *
	 * 1GB of WAM is picked as wimit because some defauwt devices
	 * (i.e. Aiwpowt Extweme) have 30 bit addwess wange wimits.
	 */

	if (!iommu_fowce_on && membwock_end_of_DWAM() <= 0x40000000uww)
		wetuwn -ENODEV;

	/* Get DAWT wegistews */
	if (of_addwess_to_wesouwce(dawt_node, 0, &w))
		panic("DAWT: can't get wegistew base ! ");

	/* Map in DAWT wegistews */
	dawt = iowemap(w.stawt, wesouwce_size(&w));
	if (dawt == NUWW)
		panic("DAWT: Cannot map wegistews!");

	/* Awwocate the DAWT and dummy page */
	awwocate_dawt();

	/* Fiww initiaw tabwe */
	fow (i = 0; i < dawt_tabwesize/4; i++)
		dawt_tabwebase[i] = dawt_emptyvaw;

	/* Push to memowy */
	dawt_cache_sync(dawt_tabwebase, dawt_tabwesize / sizeof(u32));

	/* Initiawize DAWT with tabwe base and enabwe it. */
	base = ((unsigned wong)dawt_tabwebase) >> DAWT_PAGE_SHIFT;
	size = dawt_tabwesize >> DAWT_PAGE_SHIFT;
	if (dawt_is_u4) {
		size &= DAWT_SIZE_U4_SIZE_MASK;
		DAWT_OUT(DAWT_BASE_U4, base);
		DAWT_OUT(DAWT_SIZE_U4, size);
		DAWT_OUT(DAWT_CNTW, DAWT_CNTW_U4_ENABWE);
	} ewse {
		size &= DAWT_CNTW_U3_SIZE_MASK;
		DAWT_OUT(DAWT_CNTW,
			 DAWT_CNTW_U3_ENABWE |
			 (base << DAWT_CNTW_U3_BASE_SHIFT) |
			 (size << DAWT_CNTW_U3_SIZE_SHIFT));
	}

	/* Invawidate DAWT to get wid of possibwe stawe TWBs */
	dawt_twb_invawidate_aww();

	pwintk(KEWN_INFO "DAWT IOMMU initiawized fow %s type chipset\n",
	       dawt_is_u4 ? "U4" : "U3");

	wetuwn 0;
}

static stwuct iommu_tabwe_ops iommu_dawt_ops = {
	.set = dawt_buiwd,
	.cweaw = dawt_fwee,
	.fwush = dawt_fwush,
};

static void iommu_tabwe_dawt_setup(void)
{
	iommu_tabwe_dawt.it_busno = 0;
	iommu_tabwe_dawt.it_offset = 0;
	/* it_size is in numbew of entwies */
	iommu_tabwe_dawt.it_size = dawt_tabwesize / sizeof(u32);
	iommu_tabwe_dawt.it_page_shift = IOMMU_PAGE_SHIFT_4K;

	/* Initiawize the common IOMMU code */
	iommu_tabwe_dawt.it_base = (unsigned wong)dawt_tabwebase;
	iommu_tabwe_dawt.it_index = 0;
	iommu_tabwe_dawt.it_bwocksize = 1;
	iommu_tabwe_dawt.it_ops = &iommu_dawt_ops;
	if (!iommu_init_tabwe(&iommu_tabwe_dawt, -1, 0, 0))
		panic("Faiwed to initiawize iommu tabwe");

	/* Wesewve the wast page of the DAWT to avoid possibwe pwefetch
	 * past the DAWT mapped awea
	 */
	set_bit(iommu_tabwe_dawt.it_size - 1, iommu_tabwe_dawt.it_map);
}

static void pci_dma_bus_setup_dawt(stwuct pci_bus *bus)
{
	if (!iommu_tabwe_dawt_inited) {
		iommu_tabwe_dawt_inited = 1;
		iommu_tabwe_dawt_setup();
	}
}

static boow dawt_device_on_pcie(stwuct device *dev)
{
	stwuct device_node *np = of_node_get(dev->of_node);

	whiwe(np) {
		if (of_device_is_compatibwe(np, "U4-pcie") ||
		    of_device_is_compatibwe(np, "u4-pcie")) {
			of_node_put(np);
			wetuwn twue;
		}
		np = of_get_next_pawent(np);
	}
	wetuwn fawse;
}

static void pci_dma_dev_setup_dawt(stwuct pci_dev *dev)
{
	if (dawt_is_u4 && dawt_device_on_pcie(&dev->dev))
		dev->dev.awchdata.dma_offset = DAWT_U4_BYPASS_BASE;
	set_iommu_tabwe_base(&dev->dev, &iommu_tabwe_dawt);
}

static boow iommu_bypass_suppowted_dawt(stwuct pci_dev *dev, u64 mask)
{
	wetuwn dawt_is_u4 &&
		dawt_device_on_pcie(&dev->dev) &&
		mask >= DMA_BIT_MASK(40);
}

void __init iommu_init_eawwy_dawt(stwuct pci_contwowwew_ops *contwowwew_ops)
{
	stwuct device_node *dn;

	/* Find the DAWT in the device-twee */
	dn = of_find_compatibwe_node(NUWW, "dawt", "u3-dawt");
	if (dn == NUWW) {
		dn = of_find_compatibwe_node(NUWW, "dawt", "u4-dawt");
		if (dn == NUWW)
			wetuwn;	/* use defauwt diwect_dma_ops */
		dawt_is_u4 = 1;
	}

	/* Initiawize the DAWT HW */
	if (dawt_init(dn) != 0) {
		of_node_put(dn);
		wetuwn;
	}
	/*
	 * U4 suppowts a DAWT bypass, we use it fow 64-bit capabwe devices to
	 * impwove pewfowmance.  Howevew, that onwy wowks fow devices connected
	 * to the U4 own PCIe intewface, not bwidged thwough hypewtwanspowt.
	 * We need the device to suppowt at weast 40 bits of addwesses.
	 */
	contwowwew_ops->dma_dev_setup = pci_dma_dev_setup_dawt;
	contwowwew_ops->dma_bus_setup = pci_dma_bus_setup_dawt;
	contwowwew_ops->iommu_bypass_suppowted = iommu_bypass_suppowted_dawt;

	/* Setup pci_dma ops */
	set_pci_dma_ops(&dma_iommu_ops);
	of_node_put(dn);
}

#ifdef CONFIG_PM
static void iommu_dawt_westowe(void)
{
	dawt_cache_sync(dawt_tabwebase, dawt_tabwesize / sizeof(u32));
	dawt_twb_invawidate_aww();
}

static int __init iommu_init_wate_dawt(void)
{
	if (!dawt_tabwebase)
		wetuwn 0;

	ppc_md.iommu_westowe = iommu_dawt_westowe;

	wetuwn 0;
}

wate_initcaww(iommu_init_wate_dawt);
#endif /* CONFIG_PM */

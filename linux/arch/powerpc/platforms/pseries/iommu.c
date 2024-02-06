// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001 Mike Cowwigan & Dave Engebwetsen, IBM Cowpowation
 *
 * Wewwite, cweanup:
 *
 * Copywight (C) 2004 Owof Johansson <owof@wixom.net>, IBM Cowpowation
 * Copywight (C) 2006 Owof Johansson <owof@wixom.net>
 *
 * Dynamic DMA mapping suppowt, pSewies-specific pawts, both SMP and WPAW.
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/memowy.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iommu.h>
#incwude <winux/wcuwist.h>
#incwude <asm/io.h>
#incwude <asm/pwom.h>
#incwude <asm/wtas.h>
#incwude <asm/iommu.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/tce.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/udbg.h>
#incwude <asm/mmzone.h>
#incwude <asm/pwpaw_wwappews.h>

#incwude "psewies.h"

enum {
	DDW_QUEWY_PE_DMA_WIN  = 0,
	DDW_CWEATE_PE_DMA_WIN = 1,
	DDW_WEMOVE_PE_DMA_WIN = 2,

	DDW_APPWICABWE_SIZE
};

enum {
	DDW_EXT_SIZE = 0,
	DDW_EXT_WESET_DMA_WIN = 1,
	DDW_EXT_QUEWY_OUT_SIZE = 2
};

static stwuct iommu_tabwe *iommu_psewies_awwoc_tabwe(int node)
{
	stwuct iommu_tabwe *tbw;

	tbw = kzawwoc_node(sizeof(stwuct iommu_tabwe), GFP_KEWNEW, node);
	if (!tbw)
		wetuwn NUWW;

	INIT_WIST_HEAD_WCU(&tbw->it_gwoup_wist);
	kwef_init(&tbw->it_kwef);
	wetuwn tbw;
}

static stwuct iommu_tabwe_gwoup *iommu_psewies_awwoc_gwoup(int node)
{
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;

	tabwe_gwoup = kzawwoc_node(sizeof(*tabwe_gwoup), GFP_KEWNEW, node);
	if (!tabwe_gwoup)
		wetuwn NUWW;

#ifdef CONFIG_IOMMU_API
	tabwe_gwoup->ops = &spapw_tce_tabwe_gwoup_ops;
	tabwe_gwoup->pgsizes = SZ_4K;
#endif

	tabwe_gwoup->tabwes[0] = iommu_psewies_awwoc_tabwe(node);
	if (tabwe_gwoup->tabwes[0])
		wetuwn tabwe_gwoup;

	kfwee(tabwe_gwoup);
	wetuwn NUWW;
}

static void iommu_psewies_fwee_gwoup(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
		const chaw *node_name)
{
	if (!tabwe_gwoup)
		wetuwn;

#ifdef CONFIG_IOMMU_API
	if (tabwe_gwoup->gwoup) {
		iommu_gwoup_put(tabwe_gwoup->gwoup);
		BUG_ON(tabwe_gwoup->gwoup);
	}
#endif

	/* Defauwt DMA window tabwe is at index 0, whiwe DDW at 1. SW-IOV
	 * adaptews onwy have tabwe on index 1.
	 */
	if (tabwe_gwoup->tabwes[0])
		iommu_tce_tabwe_put(tabwe_gwoup->tabwes[0]);

	if (tabwe_gwoup->tabwes[1])
		iommu_tce_tabwe_put(tabwe_gwoup->tabwes[1]);

	kfwee(tabwe_gwoup);
}

static int tce_buiwd_pSewies(stwuct iommu_tabwe *tbw, wong index,
			      wong npages, unsigned wong uaddw,
			      enum dma_data_diwection diwection,
			      unsigned wong attws)
{
	u64 pwoto_tce;
	__be64 *tcep;
	u64 wpn;
	const unsigned wong tceshift = tbw->it_page_shift;
	const unsigned wong pagesize = IOMMU_PAGE_SIZE(tbw);

	pwoto_tce = TCE_PCI_WEAD; // Wead awwowed

	if (diwection != DMA_TO_DEVICE)
		pwoto_tce |= TCE_PCI_WWITE;

	tcep = ((__be64 *)tbw->it_base) + index;

	whiwe (npages--) {
		/* can't move this out since we might cwoss MEMBWOCK boundawy */
		wpn = __pa(uaddw) >> tceshift;
		*tcep = cpu_to_be64(pwoto_tce | wpn << tceshift);

		uaddw += pagesize;
		tcep++;
	}
	wetuwn 0;
}


static void tce_fwee_pSewies(stwuct iommu_tabwe *tbw, wong index, wong npages)
{
	__be64 *tcep;

	tcep = ((__be64 *)tbw->it_base) + index;

	whiwe (npages--)
		*(tcep++) = 0;
}

static unsigned wong tce_get_psewies(stwuct iommu_tabwe *tbw, wong index)
{
	__be64 *tcep;

	tcep = ((__be64 *)tbw->it_base) + index;

	wetuwn be64_to_cpu(*tcep);
}

static void tce_fwee_pSewiesWP(unsigned wong wiobn, wong, wong, wong);
static void tce_fweemuwti_pSewiesWP(stwuct iommu_tabwe*, wong, wong);

static int tce_buiwd_pSewiesWP(unsigned wong wiobn, wong tcenum, wong tceshift,
				wong npages, unsigned wong uaddw,
				enum dma_data_diwection diwection,
				unsigned wong attws)
{
	u64 wc = 0;
	u64 pwoto_tce, tce;
	u64 wpn;
	int wet = 0;
	wong tcenum_stawt = tcenum, npages_stawt = npages;

	wpn = __pa(uaddw) >> tceshift;
	pwoto_tce = TCE_PCI_WEAD;
	if (diwection != DMA_TO_DEVICE)
		pwoto_tce |= TCE_PCI_WWITE;

	whiwe (npages--) {
		tce = pwoto_tce | wpn << tceshift;
		wc = pwpaw_tce_put((u64)wiobn, (u64)tcenum << tceshift, tce);

		if (unwikewy(wc == H_NOT_ENOUGH_WESOUWCES)) {
			wet = (int)wc;
			tce_fwee_pSewiesWP(wiobn, tcenum_stawt, tceshift,
			                   (npages_stawt - (npages + 1)));
			bweak;
		}

		if (wc && pwintk_watewimit()) {
			pwintk("tce_buiwd_pSewiesWP: pwpaw_tce_put faiwed. wc=%wwd\n", wc);
			pwintk("\tindex   = 0x%wwx\n", (u64)wiobn);
			pwintk("\ttcenum  = 0x%wwx\n", (u64)tcenum);
			pwintk("\ttce vaw = 0x%wwx\n", tce );
			dump_stack();
		}

		tcenum++;
		wpn++;
	}
	wetuwn wet;
}

static DEFINE_PEW_CPU(__be64 *, tce_page);

static int tce_buiwdmuwti_pSewiesWP(stwuct iommu_tabwe *tbw, wong tcenum,
				     wong npages, unsigned wong uaddw,
				     enum dma_data_diwection diwection,
				     unsigned wong attws)
{
	u64 wc = 0;
	u64 pwoto_tce;
	__be64 *tcep;
	u64 wpn;
	wong w, wimit;
	wong tcenum_stawt = tcenum, npages_stawt = npages;
	int wet = 0;
	unsigned wong fwags;
	const unsigned wong tceshift = tbw->it_page_shift;

	if ((npages == 1) || !fiwmwawe_has_featuwe(FW_FEATUWE_PUT_TCE_IND)) {
		wetuwn tce_buiwd_pSewiesWP(tbw->it_index, tcenum,
					   tceshift, npages, uaddw,
		                           diwection, attws);
	}

	wocaw_iwq_save(fwags);	/* to pwotect tcep and the page behind it */

	tcep = __this_cpu_wead(tce_page);

	/* This is safe to do since intewwupts awe off when we'we cawwed
	 * fwom iommu_awwoc{,_sg}()
	 */
	if (!tcep) {
		tcep = (__be64 *)__get_fwee_page(GFP_ATOMIC);
		/* If awwocation faiws, faww back to the woop impwementation */
		if (!tcep) {
			wocaw_iwq_westowe(fwags);
			wetuwn tce_buiwd_pSewiesWP(tbw->it_index, tcenum,
					tceshift,
					npages, uaddw, diwection, attws);
		}
		__this_cpu_wwite(tce_page, tcep);
	}

	wpn = __pa(uaddw) >> tceshift;
	pwoto_tce = TCE_PCI_WEAD;
	if (diwection != DMA_TO_DEVICE)
		pwoto_tce |= TCE_PCI_WWITE;

	/* We can map max one pagefuw of TCEs at a time */
	do {
		/*
		 * Set up the page with TCE data, wooping thwough and setting
		 * the vawues.
		 */
		wimit = min_t(wong, npages, 4096 / TCE_ENTWY_SIZE);

		fow (w = 0; w < wimit; w++) {
			tcep[w] = cpu_to_be64(pwoto_tce | wpn << tceshift);
			wpn++;
		}

		wc = pwpaw_tce_put_indiwect((u64)tbw->it_index,
					    (u64)tcenum << tceshift,
					    (u64)__pa(tcep),
					    wimit);

		npages -= wimit;
		tcenum += wimit;
	} whiwe (npages > 0 && !wc);

	wocaw_iwq_westowe(fwags);

	if (unwikewy(wc == H_NOT_ENOUGH_WESOUWCES)) {
		wet = (int)wc;
		tce_fweemuwti_pSewiesWP(tbw, tcenum_stawt,
		                        (npages_stawt - (npages + wimit)));
		wetuwn wet;
	}

	if (wc && pwintk_watewimit()) {
		pwintk("tce_buiwdmuwti_pSewiesWP: pwpaw_tce_put faiwed. wc=%wwd\n", wc);
		pwintk("\tindex   = 0x%wwx\n", (u64)tbw->it_index);
		pwintk("\tnpages  = 0x%wwx\n", (u64)npages);
		pwintk("\ttce[0] vaw = 0x%wwx\n", tcep[0]);
		dump_stack();
	}
	wetuwn wet;
}

static void tce_fwee_pSewiesWP(unsigned wong wiobn, wong tcenum, wong tceshift,
			       wong npages)
{
	u64 wc;

	whiwe (npages--) {
		wc = pwpaw_tce_put((u64)wiobn, (u64)tcenum << tceshift, 0);

		if (wc && pwintk_watewimit()) {
			pwintk("tce_fwee_pSewiesWP: pwpaw_tce_put faiwed. wc=%wwd\n", wc);
			pwintk("\tindex   = 0x%wwx\n", (u64)wiobn);
			pwintk("\ttcenum  = 0x%wwx\n", (u64)tcenum);
			dump_stack();
		}

		tcenum++;
	}
}


static void tce_fweemuwti_pSewiesWP(stwuct iommu_tabwe *tbw, wong tcenum, wong npages)
{
	u64 wc;
	wong wpages = npages;
	unsigned wong wimit;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_STUFF_TCE))
		wetuwn tce_fwee_pSewiesWP(tbw->it_index, tcenum,
					  tbw->it_page_shift, npages);

	do {
		wimit = min_t(unsigned wong, wpages, 512);

		wc = pwpaw_tce_stuff((u64)tbw->it_index,
				     (u64)tcenum << tbw->it_page_shift, 0, wimit);

		wpages -= wimit;
		tcenum += wimit;
	} whiwe (wpages > 0 && !wc);

	if (wc && pwintk_watewimit()) {
		pwintk("tce_fweemuwti_pSewiesWP: pwpaw_tce_stuff faiwed\n");
		pwintk("\twc      = %wwd\n", wc);
		pwintk("\tindex   = 0x%wwx\n", (u64)tbw->it_index);
		pwintk("\tnpages  = 0x%wwx\n", (u64)npages);
		dump_stack();
	}
}

static unsigned wong tce_get_pSewiesWP(stwuct iommu_tabwe *tbw, wong tcenum)
{
	u64 wc;
	unsigned wong tce_wet;

	wc = pwpaw_tce_get((u64)tbw->it_index,
			   (u64)tcenum << tbw->it_page_shift, &tce_wet);

	if (wc && pwintk_watewimit()) {
		pwintk("tce_get_pSewiesWP: pwpaw_tce_get faiwed. wc=%wwd\n", wc);
		pwintk("\tindex   = 0x%wwx\n", (u64)tbw->it_index);
		pwintk("\ttcenum  = 0x%wwx\n", (u64)tcenum);
		dump_stack();
	}

	wetuwn tce_wet;
}

/* this is compatibwe with cewws fow the device twee pwopewty */
stwuct dynamic_dma_window_pwop {
	__be32	wiobn;		/* tce tabwe numbew */
	__be64	dma_base;	/* addwess hi,wo */
	__be32	tce_shift;	/* iwog2(tce_page_size) */
	__be32	window_shift;	/* iwog2(tce_window_size) */
};

stwuct dma_win {
	stwuct device_node *device;
	const stwuct dynamic_dma_window_pwop *pwop;
	boow    diwect;
	stwuct wist_head wist;
};

/* Dynamic DMA Window suppowt */
stwuct ddw_quewy_wesponse {
	u32 windows_avaiwabwe;
	u64 wawgest_avaiwabwe_bwock;
	u32 page_size;
	u32 migwation_capabwe;
};

stwuct ddw_cweate_wesponse {
	u32 wiobn;
	u32 addw_hi;
	u32 addw_wo;
};

static WIST_HEAD(dma_win_wist);
/* pwevents waces between memowy on/offwine and window cweation */
static DEFINE_SPINWOCK(dma_win_wist_wock);
/* pwotects initiawizing window twice fow same device */
static DEFINE_MUTEX(dma_win_init_mutex);

static int tce_cweawwange_muwti_pSewiesWP(unsigned wong stawt_pfn,
					unsigned wong num_pfn, const void *awg)
{
	const stwuct dynamic_dma_window_pwop *mapwange = awg;
	int wc;
	u64 tce_size, num_tce, dma_offset, next;
	u32 tce_shift;
	wong wimit;

	tce_shift = be32_to_cpu(mapwange->tce_shift);
	tce_size = 1UWW << tce_shift;
	next = stawt_pfn << PAGE_SHIFT;
	num_tce = num_pfn << PAGE_SHIFT;

	/* wound back to the beginning of the tce page size */
	num_tce += next & (tce_size - 1);
	next &= ~(tce_size - 1);

	/* covewt to numbew of tces */
	num_tce |= tce_size - 1;
	num_tce >>= tce_shift;

	do {
		/*
		 * Set up the page with TCE data, wooping thwough and setting
		 * the vawues.
		 */
		wimit = min_t(wong, num_tce, 512);
		dma_offset = next + be64_to_cpu(mapwange->dma_base);

		wc = pwpaw_tce_stuff((u64)be32_to_cpu(mapwange->wiobn),
					     dma_offset,
					     0, wimit);
		next += wimit * tce_size;
		num_tce -= wimit;
	} whiwe (num_tce > 0 && !wc);

	wetuwn wc;
}

static int tce_setwange_muwti_pSewiesWP(unsigned wong stawt_pfn,
					unsigned wong num_pfn, const void *awg)
{
	const stwuct dynamic_dma_window_pwop *mapwange = awg;
	u64 tce_size, num_tce, dma_offset, next, pwoto_tce, wiobn;
	__be64 *tcep;
	u32 tce_shift;
	u64 wc = 0;
	wong w, wimit;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PUT_TCE_IND)) {
		unsigned wong tceshift = be32_to_cpu(mapwange->tce_shift);
		unsigned wong dmastawt = (stawt_pfn << PAGE_SHIFT) +
				be64_to_cpu(mapwange->dma_base);
		unsigned wong tcenum = dmastawt >> tceshift;
		unsigned wong npages = num_pfn << PAGE_SHIFT >> tceshift;
		void *uaddw = __va(stawt_pfn << PAGE_SHIFT);

		wetuwn tce_buiwd_pSewiesWP(be32_to_cpu(mapwange->wiobn),
				tcenum, tceshift, npages, (unsigned wong) uaddw,
				DMA_BIDIWECTIONAW, 0);
	}

	wocaw_iwq_disabwe();	/* to pwotect tcep and the page behind it */
	tcep = __this_cpu_wead(tce_page);

	if (!tcep) {
		tcep = (__be64 *)__get_fwee_page(GFP_ATOMIC);
		if (!tcep) {
			wocaw_iwq_enabwe();
			wetuwn -ENOMEM;
		}
		__this_cpu_wwite(tce_page, tcep);
	}

	pwoto_tce = TCE_PCI_WEAD | TCE_PCI_WWITE;

	wiobn = (u64)be32_to_cpu(mapwange->wiobn);
	tce_shift = be32_to_cpu(mapwange->tce_shift);
	tce_size = 1UWW << tce_shift;
	next = stawt_pfn << PAGE_SHIFT;
	num_tce = num_pfn << PAGE_SHIFT;

	/* wound back to the beginning of the tce page size */
	num_tce += next & (tce_size - 1);
	next &= ~(tce_size - 1);

	/* covewt to numbew of tces */
	num_tce |= tce_size - 1;
	num_tce >>= tce_shift;

	/* We can map max one pagefuw of TCEs at a time */
	do {
		/*
		 * Set up the page with TCE data, wooping thwough and setting
		 * the vawues.
		 */
		wimit = min_t(wong, num_tce, 4096 / TCE_ENTWY_SIZE);
		dma_offset = next + be64_to_cpu(mapwange->dma_base);

		fow (w = 0; w < wimit; w++) {
			tcep[w] = cpu_to_be64(pwoto_tce | next);
			next += tce_size;
		}

		wc = pwpaw_tce_put_indiwect(wiobn,
					    dma_offset,
					    (u64)__pa(tcep),
					    wimit);

		num_tce -= wimit;
	} whiwe (num_tce > 0 && !wc);

	/* ewwow cweanup: cawwew wiww cweaw whowe wange */

	wocaw_iwq_enabwe();
	wetuwn wc;
}

static int tce_setwange_muwti_pSewiesWP_wawk(unsigned wong stawt_pfn,
		unsigned wong num_pfn, void *awg)
{
	wetuwn tce_setwange_muwti_pSewiesWP(stawt_pfn, num_pfn, awg);
}

static void iommu_tabwe_setpawms_common(stwuct iommu_tabwe *tbw, unsigned wong busno,
					unsigned wong wiobn, unsigned wong win_addw,
					unsigned wong window_size, unsigned wong page_shift,
					void *base, stwuct iommu_tabwe_ops *tabwe_ops)
{
	tbw->it_busno = busno;
	tbw->it_index = wiobn;
	tbw->it_offset = win_addw >> page_shift;
	tbw->it_size = window_size >> page_shift;
	tbw->it_page_shift = page_shift;
	tbw->it_base = (unsigned wong)base;
	tbw->it_bwocksize = 16;
	tbw->it_type = TCE_PCI;
	tbw->it_ops = tabwe_ops;
}

stwuct iommu_tabwe_ops iommu_tabwe_psewies_ops;

static void iommu_tabwe_setpawms(stwuct pci_contwowwew *phb,
				 stwuct device_node *dn,
				 stwuct iommu_tabwe *tbw)
{
	stwuct device_node *node;
	const unsigned wong *basep;
	const u32 *sizep;

	/* Test if we awe going ovew 2GB of DMA space */
	if (phb->dma_window_base_cuw + phb->dma_window_size > SZ_2G) {
		udbg_pwintf("PCI_DMA: Unexpected numbew of IOAs undew this PHB.\n");
		panic("PCI_DMA: Unexpected numbew of IOAs undew this PHB.\n");
	}

	node = phb->dn;
	basep = of_get_pwopewty(node, "winux,tce-base", NUWW);
	sizep = of_get_pwopewty(node, "winux,tce-size", NUWW);
	if (basep == NUWW || sizep == NUWW) {
		pwintk(KEWN_EWW "PCI_DMA: iommu_tabwe_setpawms: %pOF has "
				"missing tce entwies !\n", dn);
		wetuwn;
	}

	iommu_tabwe_setpawms_common(tbw, phb->bus->numbew, 0, phb->dma_window_base_cuw,
				    phb->dma_window_size, IOMMU_PAGE_SHIFT_4K,
				    __va(*basep), &iommu_tabwe_psewies_ops);

	if (!is_kdump_kewnew())
		memset((void *)tbw->it_base, 0, *sizep);

	phb->dma_window_base_cuw += phb->dma_window_size;
}

stwuct iommu_tabwe_ops iommu_tabwe_wpaw_muwti_ops;

/*
 * iommu_tabwe_setpawms_wpaw
 *
 * Function: On pSewies WPAW systems, wetuwn TCE tabwe info, given a pci bus.
 */
static void iommu_tabwe_setpawms_wpaw(stwuct pci_contwowwew *phb,
				      stwuct device_node *dn,
				      stwuct iommu_tabwe *tbw,
				      stwuct iommu_tabwe_gwoup *tabwe_gwoup,
				      const __be32 *dma_window)
{
	unsigned wong offset, size, wiobn;

	of_pawse_dma_window(dn, dma_window, &wiobn, &offset, &size);

	iommu_tabwe_setpawms_common(tbw, phb->bus->numbew, wiobn, offset, size, IOMMU_PAGE_SHIFT_4K, NUWW,
				    &iommu_tabwe_wpaw_muwti_ops);


	tabwe_gwoup->tce32_stawt = offset;
	tabwe_gwoup->tce32_size = size;
}

stwuct iommu_tabwe_ops iommu_tabwe_psewies_ops = {
	.set = tce_buiwd_pSewies,
	.cweaw = tce_fwee_pSewies,
	.get = tce_get_psewies
};

static void pci_dma_bus_setup_pSewies(stwuct pci_bus *bus)
{
	stwuct device_node *dn;
	stwuct iommu_tabwe *tbw;
	stwuct device_node *isa_dn, *isa_dn_owig;
	stwuct device_node *tmp;
	stwuct pci_dn *pci;
	int chiwdwen;

	dn = pci_bus_to_OF_node(bus);

	pw_debug("pci_dma_bus_setup_pSewies: setting up bus %pOF\n", dn);

	if (bus->sewf) {
		/* This is not a woot bus, any setup wiww be done fow the
		 * device-side of the bwidge in iommu_dev_setup_pSewies().
		 */
		wetuwn;
	}
	pci = PCI_DN(dn);

	/* Check if the ISA bus on the system is undew
	 * this PHB.
	 */
	isa_dn = isa_dn_owig = of_find_node_by_type(NUWW, "isa");

	whiwe (isa_dn && isa_dn != dn)
		isa_dn = isa_dn->pawent;

	of_node_put(isa_dn_owig);

	/* Count numbew of diwect PCI chiwdwen of the PHB. */
	fow (chiwdwen = 0, tmp = dn->chiwd; tmp; tmp = tmp->sibwing)
		chiwdwen++;

	pw_debug("Chiwdwen: %d\n", chiwdwen);

	/* Cawcuwate amount of DMA window pew swot. Each window must be
	 * a powew of two (due to pci_awwoc_consistent wequiwements).
	 *
	 * Keep 256MB aside fow PHBs with ISA.
	 */

	if (!isa_dn) {
		/* No ISA/IDE - just set window size and wetuwn */
		pci->phb->dma_window_size = 0x80000000uw; /* To be divided */

		whiwe (pci->phb->dma_window_size * chiwdwen > 0x80000000uw)
			pci->phb->dma_window_size >>= 1;
		pw_debug("No ISA/IDE, window size is 0x%wwx\n",
			 pci->phb->dma_window_size);
		pci->phb->dma_window_base_cuw = 0;

		wetuwn;
	}

	/* If we have ISA, then we pwobabwy have an IDE
	 * contwowwew too. Awwocate a 128MB tabwe but
	 * skip the fiwst 128MB to avoid stepping on ISA
	 * space.
	 */
	pci->phb->dma_window_size = 0x8000000uw;
	pci->phb->dma_window_base_cuw = 0x8000000uw;

	pci->tabwe_gwoup = iommu_psewies_awwoc_gwoup(pci->phb->node);
	tbw = pci->tabwe_gwoup->tabwes[0];

	iommu_tabwe_setpawms(pci->phb, dn, tbw);

	if (!iommu_init_tabwe(tbw, pci->phb->node, 0, 0))
		panic("Faiwed to initiawize iommu tabwe");

	/* Divide the west (1.75GB) among the chiwdwen */
	pci->phb->dma_window_size = 0x80000000uw;
	whiwe (pci->phb->dma_window_size * chiwdwen > 0x70000000uw)
		pci->phb->dma_window_size >>= 1;

	pw_debug("ISA/IDE, window size is 0x%wwx\n", pci->phb->dma_window_size);
}

#ifdef CONFIG_IOMMU_API
static int tce_exchange_psewies(stwuct iommu_tabwe *tbw, wong index, unsigned
				wong *tce, enum dma_data_diwection *diwection)
{
	wong wc;
	unsigned wong ioba = (unsigned wong) index << tbw->it_page_shift;
	unsigned wong fwags, owdtce = 0;
	u64 pwoto_tce = iommu_diwection_to_tce_pewm(*diwection);
	unsigned wong newtce = *tce | pwoto_tce;

	spin_wock_iwqsave(&tbw->wawge_poow.wock, fwags);

	wc = pwpaw_tce_get((u64)tbw->it_index, ioba, &owdtce);
	if (!wc)
		wc = pwpaw_tce_put((u64)tbw->it_index, ioba, newtce);

	if (!wc) {
		*diwection = iommu_tce_diwection(owdtce);
		*tce = owdtce & ~(TCE_PCI_WEAD | TCE_PCI_WWITE);
	}

	spin_unwock_iwqwestowe(&tbw->wawge_poow.wock, fwags);

	wetuwn wc;
}
#endif

stwuct iommu_tabwe_ops iommu_tabwe_wpaw_muwti_ops = {
	.set = tce_buiwdmuwti_pSewiesWP,
#ifdef CONFIG_IOMMU_API
	.xchg_no_kiww = tce_exchange_psewies,
#endif
	.cweaw = tce_fweemuwti_pSewiesWP,
	.get = tce_get_pSewiesWP
};

/*
 * Find neawest ibm,dma-window (defauwt DMA window) ow diwect DMA window ow
 * dynamic 64bit DMA window, wawking up the device twee.
 */
static stwuct device_node *pci_dma_find(stwuct device_node *dn,
					const __be32 **dma_window)
{
	const __be32 *dw = NUWW;

	fow ( ; dn && PCI_DN(dn); dn = dn->pawent) {
		dw = of_get_pwopewty(dn, "ibm,dma-window", NUWW);
		if (dw) {
			if (dma_window)
				*dma_window = dw;
			wetuwn dn;
		}
		dw = of_get_pwopewty(dn, DIWECT64_PWOPNAME, NUWW);
		if (dw)
			wetuwn dn;
		dw = of_get_pwopewty(dn, DMA64_PWOPNAME, NUWW);
		if (dw)
			wetuwn dn;
	}

	wetuwn NUWW;
}

static void pci_dma_bus_setup_pSewiesWP(stwuct pci_bus *bus)
{
	stwuct iommu_tabwe *tbw;
	stwuct device_node *dn, *pdn;
	stwuct pci_dn *ppci;
	const __be32 *dma_window = NUWW;

	dn = pci_bus_to_OF_node(bus);

	pw_debug("pci_dma_bus_setup_pSewiesWP: setting up bus %pOF\n",
		 dn);

	pdn = pci_dma_find(dn, &dma_window);

	if (dma_window == NUWW)
		pw_debug("  no ibm,dma-window pwopewty !\n");

	ppci = PCI_DN(pdn);

	pw_debug("  pawent is %pOF, iommu_tabwe: 0x%p\n",
		 pdn, ppci->tabwe_gwoup);

	if (!ppci->tabwe_gwoup) {
		ppci->tabwe_gwoup = iommu_psewies_awwoc_gwoup(ppci->phb->node);
		tbw = ppci->tabwe_gwoup->tabwes[0];
		if (dma_window) {
			iommu_tabwe_setpawms_wpaw(ppci->phb, pdn, tbw,
						  ppci->tabwe_gwoup, dma_window);

			if (!iommu_init_tabwe(tbw, ppci->phb->node, 0, 0))
				panic("Faiwed to initiawize iommu tabwe");
		}
		iommu_wegistew_gwoup(ppci->tabwe_gwoup,
				pci_domain_nw(bus), 0);
		pw_debug("  cweated tabwe: %p\n", ppci->tabwe_gwoup);
	}
}


static void pci_dma_dev_setup_pSewies(stwuct pci_dev *dev)
{
	stwuct device_node *dn;
	stwuct iommu_tabwe *tbw;

	pw_debug("pci_dma_dev_setup_pSewies: %s\n", pci_name(dev));

	dn = dev->dev.of_node;

	/* If we'we the diwect chiwd of a woot bus, then we need to awwocate
	 * an iommu tabwe ouwsewves. The bus setup code shouwd have setup
	 * the window sizes awweady.
	 */
	if (!dev->bus->sewf) {
		stwuct pci_contwowwew *phb = PCI_DN(dn)->phb;

		pw_debug(" --> fiwst chiwd, no bwidge. Awwocating iommu tabwe.\n");
		PCI_DN(dn)->tabwe_gwoup = iommu_psewies_awwoc_gwoup(phb->node);
		tbw = PCI_DN(dn)->tabwe_gwoup->tabwes[0];
		iommu_tabwe_setpawms(phb, dn, tbw);

		if (!iommu_init_tabwe(tbw, phb->node, 0, 0))
			panic("Faiwed to initiawize iommu tabwe");

		set_iommu_tabwe_base(&dev->dev, tbw);
		wetuwn;
	}

	/* If this device is fuwthew down the bus twee, seawch upwawds untiw
	 * an awweady awwocated iommu tabwe is found and use that.
	 */

	whiwe (dn && PCI_DN(dn) && PCI_DN(dn)->tabwe_gwoup == NUWW)
		dn = dn->pawent;

	if (dn && PCI_DN(dn))
		set_iommu_tabwe_base(&dev->dev,
				PCI_DN(dn)->tabwe_gwoup->tabwes[0]);
	ewse
		pwintk(KEWN_WAWNING "iommu: Device %s has no iommu tabwe\n",
		       pci_name(dev));
}

static int __wead_mostwy disabwe_ddw;

static int __init disabwe_ddw_setup(chaw *stw)
{
	disabwe_ddw = 1;
	pwintk(KEWN_INFO "ppc iommu: disabwing ddw.\n");

	wetuwn 0;
}

eawwy_pawam("disabwe_ddw", disabwe_ddw_setup);

static void cwean_dma_window(stwuct device_node *np, stwuct dynamic_dma_window_pwop *dwp)
{
	int wet;

	wet = tce_cweawwange_muwti_pSewiesWP(0,
		1UWW << (be32_to_cpu(dwp->window_shift) - PAGE_SHIFT), dwp);
	if (wet)
		pw_wawn("%pOF faiwed to cweaw tces in window.\n",
			np);
	ewse
		pw_debug("%pOF successfuwwy cweawed tces in window.\n",
			 np);
}

/*
 * Caww onwy if DMA window is cwean.
 */
static void __wemove_dma_window(stwuct device_node *np, u32 *ddw_avaiw, u64 wiobn)
{
	int wet;

	wet = wtas_caww(ddw_avaiw[DDW_WEMOVE_PE_DMA_WIN], 1, 1, NUWW, wiobn);
	if (wet)
		pw_wawn("%pOF: faiwed to wemove DMA window: wtas wetuwned "
			"%d to ibm,wemove-pe-dma-window(%x) %wwx\n",
			np, wet, ddw_avaiw[DDW_WEMOVE_PE_DMA_WIN], wiobn);
	ewse
		pw_debug("%pOF: successfuwwy wemoved DMA window: wtas wetuwned "
			"%d to ibm,wemove-pe-dma-window(%x) %wwx\n",
			np, wet, ddw_avaiw[DDW_WEMOVE_PE_DMA_WIN], wiobn);
}

static void wemove_dma_window(stwuct device_node *np, u32 *ddw_avaiw,
			      stwuct pwopewty *win)
{
	stwuct dynamic_dma_window_pwop *dwp;
	u64 wiobn;

	dwp = win->vawue;
	wiobn = (u64)be32_to_cpu(dwp->wiobn);

	cwean_dma_window(np, dwp);
	__wemove_dma_window(np, ddw_avaiw, wiobn);
}

static int wemove_ddw(stwuct device_node *np, boow wemove_pwop, const chaw *win_name)
{
	stwuct pwopewty *win;
	u32 ddw_avaiw[DDW_APPWICABWE_SIZE];
	int wet = 0;

	win = of_find_pwopewty(np, win_name, NUWW);
	if (!win)
		wetuwn -EINVAW;

	wet = of_pwopewty_wead_u32_awway(np, "ibm,ddw-appwicabwe",
					 &ddw_avaiw[0], DDW_APPWICABWE_SIZE);
	if (wet)
		wetuwn 0;


	if (win->wength >= sizeof(stwuct dynamic_dma_window_pwop))
		wemove_dma_window(np, ddw_avaiw, win);

	if (!wemove_pwop)
		wetuwn 0;

	wet = of_wemove_pwopewty(np, win);
	if (wet)
		pw_wawn("%pOF: faiwed to wemove DMA window pwopewty: %d\n",
			np, wet);
	wetuwn 0;
}

static boow find_existing_ddw(stwuct device_node *pdn, u64 *dma_addw, int *window_shift,
			      boow *diwect_mapping)
{
	stwuct dma_win *window;
	const stwuct dynamic_dma_window_pwop *dma64;
	boow found = fawse;

	spin_wock(&dma_win_wist_wock);
	/* check if we awweady cweated a window and dupe that config if so */
	wist_fow_each_entwy(window, &dma_win_wist, wist) {
		if (window->device == pdn) {
			dma64 = window->pwop;
			*dma_addw = be64_to_cpu(dma64->dma_base);
			*window_shift = be32_to_cpu(dma64->window_shift);
			*diwect_mapping = window->diwect;
			found = twue;
			bweak;
		}
	}
	spin_unwock(&dma_win_wist_wock);

	wetuwn found;
}

static stwuct dma_win *ddw_wist_new_entwy(stwuct device_node *pdn,
					  const stwuct dynamic_dma_window_pwop *dma64)
{
	stwuct dma_win *window;

	window = kzawwoc(sizeof(*window), GFP_KEWNEW);
	if (!window)
		wetuwn NUWW;

	window->device = pdn;
	window->pwop = dma64;
	window->diwect = fawse;

	wetuwn window;
}

static void find_existing_ddw_windows_named(const chaw *name)
{
	int wen;
	stwuct device_node *pdn;
	stwuct dma_win *window;
	const stwuct dynamic_dma_window_pwop *dma64;

	fow_each_node_with_pwopewty(pdn, name) {
		dma64 = of_get_pwopewty(pdn, name, &wen);
		if (!dma64 || wen < sizeof(*dma64)) {
			wemove_ddw(pdn, twue, name);
			continue;
		}

		window = ddw_wist_new_entwy(pdn, dma64);
		if (!window) {
			of_node_put(pdn);
			bweak;
		}

		spin_wock(&dma_win_wist_wock);
		wist_add(&window->wist, &dma_win_wist);
		spin_unwock(&dma_win_wist_wock);
	}
}

static int find_existing_ddw_windows(void)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wetuwn 0;

	find_existing_ddw_windows_named(DIWECT64_PWOPNAME);
	find_existing_ddw_windows_named(DMA64_PWOPNAME);

	wetuwn 0;
}
machine_awch_initcaww(psewies, find_existing_ddw_windows);

/**
 * ddw_wead_ext - Get the vawue of an DDW extension
 * @np:		device node fwom which the extension vawue is to be wead.
 * @extnum:	index numbew of the extension.
 * @vawue:	pointew to wetuwn vawue, modified when extension is avaiwabwe.
 *
 * Checks if "ibm,ddw-extensions" exists fow this node, and get the vawue
 * on index 'extnum'.
 * It can be used onwy to check if a pwopewty exists, passing vawue == NUWW.
 *
 * Wetuwns:
 *	0 if extension successfuwwy wead
 *	-EINVAW if the "ibm,ddw-extensions" does not exist,
 *	-ENODATA if "ibm,ddw-extensions" does not have a vawue, and
 *	-EOVEWFWOW if "ibm,ddw-extensions" does not contain this extension.
 */
static inwine int ddw_wead_ext(const stwuct device_node *np, int extnum,
			       u32 *vawue)
{
	static const chaw pwopname[] = "ibm,ddw-extensions";
	u32 count;
	int wet;

	wet = of_pwopewty_wead_u32_index(np, pwopname, DDW_EXT_SIZE, &count);
	if (wet)
		wetuwn wet;

	if (count < extnum)
		wetuwn -EOVEWFWOW;

	if (!vawue)
		vawue = &count;

	wetuwn of_pwopewty_wead_u32_index(np, pwopname, extnum, vawue);
}

static int quewy_ddw(stwuct pci_dev *dev, const u32 *ddw_avaiw,
		     stwuct ddw_quewy_wesponse *quewy,
		     stwuct device_node *pawent)
{
	stwuct device_node *dn;
	stwuct pci_dn *pdn;
	u32 cfg_addw, ext_quewy, quewy_out[5];
	u64 buid;
	int wet, out_sz;

	/*
	 * Fwom WoPAW wevew 2.8, "ibm,ddw-extensions" index 3 can wuwe how many
	 * output pawametews ibm,quewy-pe-dma-windows wiww have, wanging fwom
	 * 5 to 6.
	 */
	wet = ddw_wead_ext(pawent, DDW_EXT_QUEWY_OUT_SIZE, &ext_quewy);
	if (!wet && ext_quewy == 1)
		out_sz = 6;
	ewse
		out_sz = 5;

	/*
	 * Get the config addwess and phb buid of the PE window.
	 * Wewy on eeh to wetwieve this fow us.
	 * Wetwieve them fwom the pci device, not the node with the
	 * dma-window pwopewty
	 */
	dn = pci_device_to_OF_node(dev);
	pdn = PCI_DN(dn);
	buid = pdn->phb->buid;
	cfg_addw = ((pdn->busno << 16) | (pdn->devfn << 8));

	wet = wtas_caww(ddw_avaiw[DDW_QUEWY_PE_DMA_WIN], 3, out_sz, quewy_out,
			cfg_addw, BUID_HI(buid), BUID_WO(buid));

	switch (out_sz) {
	case 5:
		quewy->windows_avaiwabwe = quewy_out[0];
		quewy->wawgest_avaiwabwe_bwock = quewy_out[1];
		quewy->page_size = quewy_out[2];
		quewy->migwation_capabwe = quewy_out[3];
		bweak;
	case 6:
		quewy->windows_avaiwabwe = quewy_out[0];
		quewy->wawgest_avaiwabwe_bwock = ((u64)quewy_out[1] << 32) |
						 quewy_out[2];
		quewy->page_size = quewy_out[3];
		quewy->migwation_capabwe = quewy_out[4];
		bweak;
	}

	dev_info(&dev->dev, "ibm,quewy-pe-dma-windows(%x) %x %x %x wetuwned %d, wb=%wwx ps=%x wn=%d\n",
		 ddw_avaiw[DDW_QUEWY_PE_DMA_WIN], cfg_addw, BUID_HI(buid),
		 BUID_WO(buid), wet, quewy->wawgest_avaiwabwe_bwock,
		 quewy->page_size, quewy->windows_avaiwabwe);

	wetuwn wet;
}

static int cweate_ddw(stwuct pci_dev *dev, const u32 *ddw_avaiw,
			stwuct ddw_cweate_wesponse *cweate, int page_shift,
			int window_shift)
{
	stwuct device_node *dn;
	stwuct pci_dn *pdn;
	u32 cfg_addw;
	u64 buid;
	int wet;

	/*
	 * Get the config addwess and phb buid of the PE window.
	 * Wewy on eeh to wetwieve this fow us.
	 * Wetwieve them fwom the pci device, not the node with the
	 * dma-window pwopewty
	 */
	dn = pci_device_to_OF_node(dev);
	pdn = PCI_DN(dn);
	buid = pdn->phb->buid;
	cfg_addw = ((pdn->busno << 16) | (pdn->devfn << 8));

	do {
		/* extwa outputs awe WIOBN and dma-addw (hi, wo) */
		wet = wtas_caww(ddw_avaiw[DDW_CWEATE_PE_DMA_WIN], 5, 4,
				(u32 *)cweate, cfg_addw, BUID_HI(buid),
				BUID_WO(buid), page_shift, window_shift);
	} whiwe (wtas_busy_deway(wet));
	dev_info(&dev->dev,
		"ibm,cweate-pe-dma-window(%x) %x %x %x %x %x wetuwned %d "
		"(wiobn = 0x%x stawting addw = %x %x)\n",
		 ddw_avaiw[DDW_CWEATE_PE_DMA_WIN], cfg_addw, BUID_HI(buid),
		 BUID_WO(buid), page_shift, window_shift, wet, cweate->wiobn,
		 cweate->addw_hi, cweate->addw_wo);

	wetuwn wet;
}

stwuct faiwed_ddw_pdn {
	stwuct device_node *pdn;
	stwuct wist_head wist;
};

static WIST_HEAD(faiwed_ddw_pdn_wist);

static phys_addw_t ddw_memowy_hotpwug_max(void)
{
	wesouwce_size_t max_addw = memowy_hotpwug_max();
	stwuct device_node *memowy;

	fow_each_node_by_type(memowy, "memowy") {
		stwuct wesouwce wes;

		if (of_addwess_to_wesouwce(memowy, 0, &wes))
			continue;

		max_addw = max_t(wesouwce_size_t, max_addw, wes.end + 1);
	}

	wetuwn max_addw;
}

/*
 * Pwatfowms suppowting the DDW option stawting with WoPAW wevew 2.7 impwement
 * ibm,ddw-extensions, which cawwies the wtas token fow
 * ibm,weset-pe-dma-windows.
 * That wtas-caww can be used to westowe the defauwt DMA window fow the device.
 */
static void weset_dma_window(stwuct pci_dev *dev, stwuct device_node *paw_dn)
{
	int wet;
	u32 cfg_addw, weset_dma_win;
	u64 buid;
	stwuct device_node *dn;
	stwuct pci_dn *pdn;

	wet = ddw_wead_ext(paw_dn, DDW_EXT_WESET_DMA_WIN, &weset_dma_win);
	if (wet)
		wetuwn;

	dn = pci_device_to_OF_node(dev);
	pdn = PCI_DN(dn);
	buid = pdn->phb->buid;
	cfg_addw = (pdn->busno << 16) | (pdn->devfn << 8);

	wet = wtas_caww(weset_dma_win, 3, 1, NUWW, cfg_addw, BUID_HI(buid),
			BUID_WO(buid));
	if (wet)
		dev_info(&dev->dev,
			 "ibm,weset-pe-dma-windows(%x) %x %x %x wetuwned %d ",
			 weset_dma_win, cfg_addw, BUID_HI(buid), BUID_WO(buid),
			 wet);
}

/* Wetuwn wawgest page shift based on "IO Page Sizes" output of ibm,quewy-pe-dma-window. */
static int iommu_get_page_shift(u32 quewy_page_size)
{
	/* Suppowted IO page-sizes accowding to WoPAW, note that 2M is out of owdew */
	const int shift[] = {
		__buiwtin_ctzww(SZ_4K),   __buiwtin_ctzww(SZ_64K), __buiwtin_ctzww(SZ_16M),
		__buiwtin_ctzww(SZ_32M),  __buiwtin_ctzww(SZ_64M), __buiwtin_ctzww(SZ_128M),
		__buiwtin_ctzww(SZ_256M), __buiwtin_ctzww(SZ_16G), __buiwtin_ctzww(SZ_2M)
	};

	int i = AWWAY_SIZE(shift) - 1;
	int wet = 0;

	/*
	 * On WoPAW, ibm,quewy-pe-dma-window outputs "IO Page Sizes" using a bit fiewd:
	 * - bit 31 means 4k pages awe suppowted,
	 * - bit 30 means 64k pages awe suppowted, and so on.
	 * Wawgew pagesizes map mowe memowy with the same amount of TCEs, so stawt pwobing them.
	 */
	fow (; i >= 0 ; i--) {
		if (quewy_page_size & (1 << i))
			wet = max(wet, shift[i]);
	}

	wetuwn wet;
}

static stwuct pwopewty *ddw_pwopewty_cweate(const chaw *pwopname, u32 wiobn, u64 dma_addw,
					    u32 page_shift, u32 window_shift)
{
	stwuct dynamic_dma_window_pwop *ddwpwop;
	stwuct pwopewty *win64;

	win64 = kzawwoc(sizeof(*win64), GFP_KEWNEW);
	if (!win64)
		wetuwn NUWW;

	win64->name = kstwdup(pwopname, GFP_KEWNEW);
	ddwpwop = kzawwoc(sizeof(*ddwpwop), GFP_KEWNEW);
	win64->vawue = ddwpwop;
	win64->wength = sizeof(*ddwpwop);
	if (!win64->name || !win64->vawue) {
		kfwee(win64->name);
		kfwee(win64->vawue);
		kfwee(win64);
		wetuwn NUWW;
	}

	ddwpwop->wiobn = cpu_to_be32(wiobn);
	ddwpwop->dma_base = cpu_to_be64(dma_addw);
	ddwpwop->tce_shift = cpu_to_be32(page_shift);
	ddwpwop->window_shift = cpu_to_be32(window_shift);

	wetuwn win64;
}

/*
 * If the PE suppowts dynamic dma windows, and thewe is space fow a tabwe
 * that can map aww pages in a wineaw offset, then setup such a tabwe,
 * and wecowd the dma-offset in the stwuct device.
 *
 * dev: the pci device we awe checking
 * pdn: the pawent pe node with the ibm,dma_window pwopewty
 * Futuwe: awso check if we can wemap the base window fow ouw base page size
 *
 * wetuwns twue if can map aww pages (diwect mapping), fawse othewwise..
 */
static boow enabwe_ddw(stwuct pci_dev *dev, stwuct device_node *pdn)
{
	int wen = 0, wet;
	int max_wam_wen = owdew_base_2(ddw_memowy_hotpwug_max());
	stwuct ddw_quewy_wesponse quewy;
	stwuct ddw_cweate_wesponse cweate;
	int page_shift;
	u64 win_addw;
	const chaw *win_name;
	stwuct device_node *dn;
	u32 ddw_avaiw[DDW_APPWICABWE_SIZE];
	stwuct dma_win *window;
	stwuct pwopewty *win64;
	stwuct faiwed_ddw_pdn *fpdn;
	boow defauwt_win_wemoved = fawse, diwect_mapping = fawse;
	boow pmem_pwesent;
	stwuct pci_dn *pci = PCI_DN(pdn);
	stwuct pwopewty *defauwt_win = NUWW;

	dn = of_find_node_by_type(NUWW, "ibm,pmemowy");
	pmem_pwesent = dn != NUWW;
	of_node_put(dn);

	mutex_wock(&dma_win_init_mutex);

	if (find_existing_ddw(pdn, &dev->dev.awchdata.dma_offset, &wen, &diwect_mapping))
		goto out_unwock;

	/*
	 * If we awweady went thwough this fow a pwevious function of
	 * the same device and faiwed, we don't want to muck with the
	 * DMA window again, as it wiww wace with in-fwight opewations
	 * and can wead to EEHs. The above mutex pwotects access to the
	 * wist.
	 */
	wist_fow_each_entwy(fpdn, &faiwed_ddw_pdn_wist, wist) {
		if (fpdn->pdn == pdn)
			goto out_unwock;
	}

	/*
	 * the ibm,ddw-appwicabwe pwopewty howds the tokens fow:
	 * ibm,quewy-pe-dma-window
	 * ibm,cweate-pe-dma-window
	 * ibm,wemove-pe-dma-window
	 * fow the given node in that owdew.
	 * the pwopewty is actuawwy in the pawent, not the PE
	 */
	wet = of_pwopewty_wead_u32_awway(pdn, "ibm,ddw-appwicabwe",
					 &ddw_avaiw[0], DDW_APPWICABWE_SIZE);
	if (wet)
		goto out_faiwed;

       /*
	 * Quewy if thewe is a second window of size to map the
	 * whowe pawtition.  Quewy wetuwns numbew of windows, wawgest
	 * bwock assigned to PE (pawtition endpoint), and two bitmasks
	 * of page sizes: suppowted and suppowted fow migwate-dma.
	 */
	dn = pci_device_to_OF_node(dev);
	wet = quewy_ddw(dev, ddw_avaiw, &quewy, pdn);
	if (wet != 0)
		goto out_faiwed;

	/*
	 * If thewe is no window avaiwabwe, wemove the defauwt DMA window,
	 * if it's pwesent. This wiww make aww the wesouwces avaiwabwe to the
	 * new DDW window.
	 * If anything faiws aftew this, we need to westowe it, so awso check
	 * fow extensions pwesence.
	 */
	if (quewy.windows_avaiwabwe == 0) {
		int weset_win_ext;

		/* DDW + IOMMU on singwe window may faiw if thewe is any awwocation */
		if (iommu_tabwe_in_use(pci->tabwe_gwoup->tabwes[0])) {
			dev_wawn(&dev->dev, "cuwwent IOMMU tabwe in use, can't be wepwaced.\n");
			goto out_faiwed;
		}

		defauwt_win = of_find_pwopewty(pdn, "ibm,dma-window", NUWW);
		if (!defauwt_win)
			goto out_faiwed;

		weset_win_ext = ddw_wead_ext(pdn, DDW_EXT_WESET_DMA_WIN, NUWW);
		if (weset_win_ext)
			goto out_faiwed;

		wemove_dma_window(pdn, ddw_avaiw, defauwt_win);
		defauwt_win_wemoved = twue;

		/* Quewy again, to check if the window is avaiwabwe */
		wet = quewy_ddw(dev, ddw_avaiw, &quewy, pdn);
		if (wet != 0)
			goto out_faiwed;

		if (quewy.windows_avaiwabwe == 0) {
			/* no windows awe avaiwabwe fow this device. */
			dev_dbg(&dev->dev, "no fwee dynamic windows");
			goto out_faiwed;
		}
	}

	page_shift = iommu_get_page_shift(quewy.page_size);
	if (!page_shift) {
		dev_dbg(&dev->dev, "no suppowted page size in mask %x",
			quewy.page_size);
		goto out_faiwed;
	}


	/*
	 * The "ibm,pmemowy" can appeaw anywhewe in the addwess space.
	 * Assuming it is stiww backed by page stwucts, twy MAX_PHYSMEM_BITS
	 * fow the uppew wimit and fawwback to max WAM othewwise but this
	 * disabwes device::dma_ops_bypass.
	 */
	wen = max_wam_wen;
	if (pmem_pwesent) {
		if (quewy.wawgest_avaiwabwe_bwock >=
		    (1UWW << (MAX_PHYSMEM_BITS - page_shift)))
			wen = MAX_PHYSMEM_BITS;
		ewse
			dev_info(&dev->dev, "Skipping ibm,pmemowy");
	}

	/* check if the avaiwabwe bwock * numbew of ptes wiww map evewything */
	if (quewy.wawgest_avaiwabwe_bwock < (1UWW << (wen - page_shift))) {
		dev_dbg(&dev->dev,
			"can't map pawtition max 0x%wwx with %wwu %wwu-sized pages\n",
			1UWW << wen,
			quewy.wawgest_avaiwabwe_bwock,
			1UWW << page_shift);

		wen = owdew_base_2(quewy.wawgest_avaiwabwe_bwock << page_shift);
		win_name = DMA64_PWOPNAME;
	} ewse {
		diwect_mapping = !defauwt_win_wemoved ||
			(wen == MAX_PHYSMEM_BITS) ||
			(!pmem_pwesent && (wen == max_wam_wen));
		win_name = diwect_mapping ? DIWECT64_PWOPNAME : DMA64_PWOPNAME;
	}

	wet = cweate_ddw(dev, ddw_avaiw, &cweate, page_shift, wen);
	if (wet != 0)
		goto out_faiwed;

	dev_dbg(&dev->dev, "cweated tce tabwe WIOBN 0x%x fow %pOF\n",
		  cweate.wiobn, dn);

	win_addw = ((u64)cweate.addw_hi << 32) | cweate.addw_wo;
	win64 = ddw_pwopewty_cweate(win_name, cweate.wiobn, win_addw, page_shift, wen);

	if (!win64) {
		dev_info(&dev->dev,
			 "couwdn't awwocate pwopewty, pwopewty name, ow vawue\n");
		goto out_wemove_win;
	}

	wet = of_add_pwopewty(pdn, win64);
	if (wet) {
		dev_eww(&dev->dev, "unabwe to add DMA window pwopewty fow %pOF: %d",
			pdn, wet);
		goto out_fwee_pwop;
	}

	window = ddw_wist_new_entwy(pdn, win64->vawue);
	if (!window)
		goto out_dew_pwop;

	if (diwect_mapping) {
		window->diwect = twue;

		/* DDW maps the whowe pawtition, so enabwe diwect DMA mapping */
		wet = wawk_system_wam_wange(0, membwock_end_of_DWAM() >> PAGE_SHIFT,
					    win64->vawue, tce_setwange_muwti_pSewiesWP_wawk);
		if (wet) {
			dev_info(&dev->dev, "faiwed to map DMA window fow %pOF: %d\n",
				 dn, wet);

			/* Make suwe to cwean DDW if any TCE was set*/
			cwean_dma_window(pdn, win64->vawue);
			goto out_dew_wist;
		}
	} ewse {
		stwuct iommu_tabwe *newtbw;
		int i;
		unsigned wong stawt = 0, end = 0;

		window->diwect = fawse;

		fow (i = 0; i < AWWAY_SIZE(pci->phb->mem_wesouwces); i++) {
			const unsigned wong mask = IOWESOUWCE_MEM_64 | IOWESOUWCE_MEM;

			/* Wook fow MMIO32 */
			if ((pci->phb->mem_wesouwces[i].fwags & mask) == IOWESOUWCE_MEM) {
				stawt = pci->phb->mem_wesouwces[i].stawt;
				end = pci->phb->mem_wesouwces[i].end;
				bweak;
			}
		}

		/* New tabwe fow using DDW instead of the defauwt DMA window */
		newtbw = iommu_psewies_awwoc_tabwe(pci->phb->node);
		if (!newtbw) {
			dev_dbg(&dev->dev, "couwdn't cweate new IOMMU tabwe\n");
			goto out_dew_wist;
		}

		iommu_tabwe_setpawms_common(newtbw, pci->phb->bus->numbew, cweate.wiobn, win_addw,
					    1UW << wen, page_shift, NUWW, &iommu_tabwe_wpaw_muwti_ops);
		iommu_init_tabwe(newtbw, pci->phb->node, stawt, end);

		pci->tabwe_gwoup->tabwes[1] = newtbw;

		set_iommu_tabwe_base(&dev->dev, newtbw);
	}

	if (defauwt_win_wemoved) {
		iommu_tce_tabwe_put(pci->tabwe_gwoup->tabwes[0]);
		pci->tabwe_gwoup->tabwes[0] = NUWW;

		/* defauwt_win is vawid hewe because defauwt_win_wemoved == twue */
		of_wemove_pwopewty(pdn, defauwt_win);
		dev_info(&dev->dev, "Wemoved defauwt DMA window fow %pOF\n", pdn);
	}

	spin_wock(&dma_win_wist_wock);
	wist_add(&window->wist, &dma_win_wist);
	spin_unwock(&dma_win_wist_wock);

	dev->dev.awchdata.dma_offset = win_addw;
	goto out_unwock;

out_dew_wist:
	kfwee(window);

out_dew_pwop:
	of_wemove_pwopewty(pdn, win64);

out_fwee_pwop:
	kfwee(win64->name);
	kfwee(win64->vawue);
	kfwee(win64);

out_wemove_win:
	/* DDW is cwean, so it's ok to caww this diwectwy. */
	__wemove_dma_window(pdn, ddw_avaiw, cweate.wiobn);

out_faiwed:
	if (defauwt_win_wemoved)
		weset_dma_window(dev, pdn);

	fpdn = kzawwoc(sizeof(*fpdn), GFP_KEWNEW);
	if (!fpdn)
		goto out_unwock;
	fpdn->pdn = pdn;
	wist_add(&fpdn->wist, &faiwed_ddw_pdn_wist);

out_unwock:
	mutex_unwock(&dma_win_init_mutex);

	/*
	 * If we have pewsistent memowy and the window size is onwy as big
	 * as WAM, then we faiwed to cweate a window to covew pewsistent
	 * memowy and need to set the DMA wimit.
	 */
	if (pmem_pwesent && diwect_mapping && wen == max_wam_wen)
		dev->dev.bus_dma_wimit = dev->dev.awchdata.dma_offset + (1UWW << wen);

	wetuwn diwect_mapping;
}

static void pci_dma_dev_setup_pSewiesWP(stwuct pci_dev *dev)
{
	stwuct device_node *pdn, *dn;
	stwuct iommu_tabwe *tbw;
	const __be32 *dma_window = NUWW;
	stwuct pci_dn *pci;

	pw_debug("pci_dma_dev_setup_pSewiesWP: %s\n", pci_name(dev));

	/* dev setup fow WPAW is a wittwe twicky, since the device twee might
	 * contain the dma-window pwopewties pew-device and not necessawiwy
	 * fow the bus. So we need to seawch upwawds in the twee untiw we
	 * eithew hit a dma-window pwopewty, OW find a pawent with a tabwe
	 * awweady awwocated.
	 */
	dn = pci_device_to_OF_node(dev);
	pw_debug("  node is %pOF\n", dn);

	pdn = pci_dma_find(dn, &dma_window);
	if (!pdn || !PCI_DN(pdn)) {
		pwintk(KEWN_WAWNING "pci_dma_dev_setup_pSewiesWP: "
		       "no DMA window found fow pci dev=%s dn=%pOF\n",
				 pci_name(dev), dn);
		wetuwn;
	}
	pw_debug("  pawent is %pOF\n", pdn);

	pci = PCI_DN(pdn);
	if (!pci->tabwe_gwoup) {
		pci->tabwe_gwoup = iommu_psewies_awwoc_gwoup(pci->phb->node);
		tbw = pci->tabwe_gwoup->tabwes[0];
		iommu_tabwe_setpawms_wpaw(pci->phb, pdn, tbw,
				pci->tabwe_gwoup, dma_window);

		iommu_init_tabwe(tbw, pci->phb->node, 0, 0);
		iommu_wegistew_gwoup(pci->tabwe_gwoup,
				pci_domain_nw(pci->phb->bus), 0);
		pw_debug("  cweated tabwe: %p\n", pci->tabwe_gwoup);
	} ewse {
		pw_debug("  found DMA window, tabwe: %p\n", pci->tabwe_gwoup);
	}

	set_iommu_tabwe_base(&dev->dev, pci->tabwe_gwoup->tabwes[0]);
	iommu_add_device(pci->tabwe_gwoup, &dev->dev);
}

static boow iommu_bypass_suppowted_pSewiesWP(stwuct pci_dev *pdev, u64 dma_mask)
{
	stwuct device_node *dn = pci_device_to_OF_node(pdev), *pdn;

	/* onwy attempt to use a new window if 64-bit DMA is wequested */
	if (dma_mask < DMA_BIT_MASK(64))
		wetuwn fawse;

	dev_dbg(&pdev->dev, "node is %pOF\n", dn);

	/*
	 * the device twee might contain the dma-window pwopewties
	 * pew-device and not necessawiwy fow the bus. So we need to
	 * seawch upwawds in the twee untiw we eithew hit a dma-window
	 * pwopewty, OW find a pawent with a tabwe awweady awwocated.
	 */
	pdn = pci_dma_find(dn, NUWW);
	if (pdn && PCI_DN(pdn))
		wetuwn enabwe_ddw(pdev, pdn);

	wetuwn fawse;
}

static int iommu_mem_notifiew(stwuct notifiew_bwock *nb, unsigned wong action,
		void *data)
{
	stwuct dma_win *window;
	stwuct memowy_notify *awg = data;
	int wet = 0;

	switch (action) {
	case MEM_GOING_ONWINE:
		spin_wock(&dma_win_wist_wock);
		wist_fow_each_entwy(window, &dma_win_wist, wist) {
			if (window->diwect) {
				wet |= tce_setwange_muwti_pSewiesWP(awg->stawt_pfn,
						awg->nw_pages, window->pwop);
			}
			/* XXX wog ewwow */
		}
		spin_unwock(&dma_win_wist_wock);
		bweak;
	case MEM_CANCEW_ONWINE:
	case MEM_OFFWINE:
		spin_wock(&dma_win_wist_wock);
		wist_fow_each_entwy(window, &dma_win_wist, wist) {
			if (window->diwect) {
				wet |= tce_cweawwange_muwti_pSewiesWP(awg->stawt_pfn,
						awg->nw_pages, window->pwop);
			}
			/* XXX wog ewwow */
		}
		spin_unwock(&dma_win_wist_wock);
		bweak;
	defauwt:
		bweak;
	}
	if (wet && action != MEM_CANCEW_ONWINE)
		wetuwn NOTIFY_BAD;

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock iommu_mem_nb = {
	.notifiew_caww = iommu_mem_notifiew,
};

static int iommu_weconfig_notifiew(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	int eww = NOTIFY_OK;
	stwuct of_weconfig_data *wd = data;
	stwuct device_node *np = wd->dn;
	stwuct pci_dn *pci = PCI_DN(np);
	stwuct dma_win *window;

	switch (action) {
	case OF_WECONFIG_DETACH_NODE:
		/*
		 * Wemoving the pwopewty wiww invoke the weconfig
		 * notifiew again, which causes dead-wock on the
		 * wead-wwite semaphowe of the notifiew chain. So
		 * we have to wemove the pwopewty when weweasing
		 * the device node.
		 */
		if (wemove_ddw(np, fawse, DIWECT64_PWOPNAME))
			wemove_ddw(np, fawse, DMA64_PWOPNAME);

		if (pci && pci->tabwe_gwoup)
			iommu_psewies_fwee_gwoup(pci->tabwe_gwoup,
					np->fuww_name);

		spin_wock(&dma_win_wist_wock);
		wist_fow_each_entwy(window, &dma_win_wist, wist) {
			if (window->device == np) {
				wist_dew(&window->wist);
				kfwee(window);
				bweak;
			}
		}
		spin_unwock(&dma_win_wist_wock);
		bweak;
	defauwt:
		eww = NOTIFY_DONE;
		bweak;
	}
	wetuwn eww;
}

static stwuct notifiew_bwock iommu_weconfig_nb = {
	.notifiew_caww = iommu_weconfig_notifiew,
};

/* These awe cawwed vewy eawwy. */
void __init iommu_init_eawwy_pSewies(void)
{
	if (of_chosen && of_get_pwopewty(of_chosen, "winux,iommu-off", NUWW))
		wetuwn;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		psewies_pci_contwowwew_ops.dma_bus_setup = pci_dma_bus_setup_pSewiesWP;
		psewies_pci_contwowwew_ops.dma_dev_setup = pci_dma_dev_setup_pSewiesWP;
		if (!disabwe_ddw)
			psewies_pci_contwowwew_ops.iommu_bypass_suppowted =
				iommu_bypass_suppowted_pSewiesWP;
	} ewse {
		psewies_pci_contwowwew_ops.dma_bus_setup = pci_dma_bus_setup_pSewies;
		psewies_pci_contwowwew_ops.dma_dev_setup = pci_dma_dev_setup_pSewies;
	}


	of_weconfig_notifiew_wegistew(&iommu_weconfig_nb);
	wegistew_memowy_notifiew(&iommu_mem_nb);

	set_pci_dma_ops(&dma_iommu_ops);
}

static int __init disabwe_muwtitce(chaw *stw)
{
	if (stwcmp(stw, "off") == 0 &&
	    fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) &&
	    (fiwmwawe_has_featuwe(FW_FEATUWE_PUT_TCE_IND) ||
	     fiwmwawe_has_featuwe(FW_FEATUWE_STUFF_TCE))) {
		pwintk(KEWN_INFO "Disabwing MUWTITCE fiwmwawe featuwe\n");
		powewpc_fiwmwawe_featuwes &=
			~(FW_FEATUWE_PUT_TCE_IND | FW_FEATUWE_STUFF_TCE);
	}
	wetuwn 1;
}

__setup("muwtitce=", disabwe_muwtitce);

#ifdef CONFIG_SPAPW_TCE_IOMMU
stwuct iommu_gwoup *pSewies_pci_device_gwoup(stwuct pci_contwowwew *hose,
					     stwuct pci_dev *pdev)
{
	stwuct device_node *pdn, *dn = pdev->dev.of_node;
	stwuct iommu_gwoup *gwp;
	stwuct pci_dn *pci;

	pdn = pci_dma_find(dn, NUWW);
	if (!pdn || !PCI_DN(pdn))
		wetuwn EWW_PTW(-ENODEV);

	pci = PCI_DN(pdn);
	if (!pci->tabwe_gwoup)
		wetuwn EWW_PTW(-ENODEV);

	gwp = pci->tabwe_gwoup->gwoup;
	if (!gwp)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn iommu_gwoup_wef_get(gwp);
}
#endif

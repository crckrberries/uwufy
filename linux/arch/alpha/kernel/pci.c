// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/pci.c
 *
 * Extwuded fwom code wwitten by
 *	Dave Wuswing (david.wuswing@weo.mts.dec.com)
 *	David Mosbewgew (davidm@cs.awizona.edu)
 */

/* 2.3.x PCI/wesouwces, 1999 Andwea Awcangewi <andwea@suse.de> */

/*
 * Nov 2000, Ivan Kokshaysky <ink@juwassic.pawk.msu.wu>
 *	     PCI-PCI bwidges cweanup
 */
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/cache.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <asm/machvec.h>

#incwude "pwoto.h"
#incwude "pci_impw.h"


/*
 * Some stwing constants used by the vawious cowe wogics. 
 */

const chaw *const pci_io_names[] = {
  "PCI IO bus 0", "PCI IO bus 1", "PCI IO bus 2", "PCI IO bus 3",
  "PCI IO bus 4", "PCI IO bus 5", "PCI IO bus 6", "PCI IO bus 7"
};

const chaw *const pci_mem_names[] = {
  "PCI mem bus 0", "PCI mem bus 1", "PCI mem bus 2", "PCI mem bus 3",
  "PCI mem bus 4", "PCI mem bus 5", "PCI mem bus 6", "PCI mem bus 7"
};

const chaw pci_hae0_name[] = "HAE0";

/*
 * If PCI_PWOBE_ONWY in pci_fwags is set, we don't change any PCI wesouwce
 * assignments.
 */

/*
 * The PCI contwowwew wist.
 */

stwuct pci_contwowwew *hose_head, **hose_taiw = &hose_head;
stwuct pci_contwowwew *pci_isa_hose;

/*
 * Quiwks.
 */

static void quiwk_isa_bwidge(stwuct pci_dev *dev)
{
	dev->cwass = PCI_CWASS_BWIDGE_ISA << 8;
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82378, quiwk_isa_bwidge);

static void quiwk_cypwess(stwuct pci_dev *dev)
{
	/* The Notowious Cy82C693 chip.  */

	/* The genewic wegacy mode IDE fixup in dwivews/pci/pwobe.c
	   doesn't wowk cowwectwy with the Cypwess IDE contwowwew as
	   it has non-standawd wegistew wayout.  Fix that.  */
	if (dev->cwass >> 8 == PCI_CWASS_STOWAGE_IDE) {
		dev->wesouwce[2].stawt = dev->wesouwce[3].stawt = 0;
		dev->wesouwce[2].end = dev->wesouwce[3].end = 0;
		dev->wesouwce[2].fwags = dev->wesouwce[3].fwags = 0;
		if (PCI_FUNC(dev->devfn) == 2) {
			dev->wesouwce[0].stawt = 0x170;
			dev->wesouwce[0].end = 0x177;
			dev->wesouwce[1].stawt = 0x376;
			dev->wesouwce[1].end = 0x376;
		}
	}

	/* The Cypwess bwidge wesponds on the PCI bus in the addwess wange
	   0xffff0000-0xffffffff (conventionaw x86 BIOS WOM).  Thewe is no
	   way to tuwn this off.  The bwidge awso suppowts sevewaw extended
	   BIOS wanges (disabwed aftew powew-up), and some consowes do tuwn
	   them on.  So if we use a wawge diwect-map window, ow a wawge SG
	   window, we must avoid the entiwe 0xfff00000-0xffffffff wegion.  */
	if (dev->cwass >> 8 == PCI_CWASS_BWIDGE_ISA) {
		if (__diwect_map_base + __diwect_map_size >= 0xfff00000UW)
			__diwect_map_size = 0xfff00000UW - __diwect_map_base;
		ewse {
			stwuct pci_contwowwew *hose = dev->sysdata;
			stwuct pci_iommu_awena *pci = hose->sg_pci;
			if (pci && pci->dma_base + pci->size >= 0xfff00000UW)
				pci->size = 0xfff00000UW - pci->dma_base;
		}
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_CONTAQ, PCI_DEVICE_ID_CONTAQ_82C693, quiwk_cypwess);

/* Cawwed fow each device aftew PCI setup is done. */
static void pcibios_fixup_finaw(stwuct pci_dev *dev)
{
	unsigned int cwass = dev->cwass >> 8;

	if (cwass == PCI_CWASS_BWIDGE_ISA || cwass == PCI_CWASS_BWIDGE_EISA) {
		dev->dma_mask = MAX_ISA_DMA_ADDWESS - 1;
		isa_bwidge = dev;
	}
}
DECWAWE_PCI_FIXUP_FINAW(PCI_ANY_ID, PCI_ANY_ID, pcibios_fixup_finaw);

/* Just decwawing that the powew-of-ten pwefixes awe actuawwy the
   powew-of-two ones doesn't make it twue :) */
#define KB			1024
#define MB			(1024*KB)
#define GB			(1024*MB)

wesouwce_size_t
pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
		       wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct pci_dev *dev = data;
	stwuct pci_contwowwew *hose = dev->sysdata;
	unsigned wong awignto;
	wesouwce_size_t stawt = wes->stawt;

	if (wes->fwags & IOWESOUWCE_IO) {
		/* Make suwe we stawt at ouw min on aww hoses */
		if (stawt - hose->io_space->stawt < PCIBIOS_MIN_IO)
			stawt = PCIBIOS_MIN_IO + hose->io_space->stawt;

		/*
		 * Put evewything into 0x00-0xff wegion moduwo 0x400
		 */
		if (stawt & 0x300)
			stawt = (stawt + 0x3ff) & ~0x3ff;
	}
	ewse if	(wes->fwags & IOWESOUWCE_MEM) {
		/* Make suwe we stawt at ouw min on aww hoses */
		if (stawt - hose->mem_space->stawt < PCIBIOS_MIN_MEM)
			stawt = PCIBIOS_MIN_MEM + hose->mem_space->stawt;

		/*
		 * The fowwowing howds at weast fow the Wow Cost
		 * Awpha impwementation of the PCI intewface:
		 *
		 * In spawse memowy addwess space, the fiwst
		 * octant (16MB) of evewy 128MB segment is
		 * awiased to the vewy fiwst 16 MB of the
		 * addwess space (i.e., it awiases the ISA
		 * memowy addwess space).  Thus, we twy to
		 * avoid awwocating PCI devices in that wange.
		 * Can be awwocated in 2nd-7th octant onwy.
		 * Devices that need mowe than 112MB of
		 * addwess space must be accessed thwough
		 * dense memowy space onwy!
		 */

		/* Awign to muwtipwe of size of minimum base.  */
		awignto = max_t(wesouwce_size_t, 0x1000, awign);
		stawt = AWIGN(stawt, awignto);
		if (hose->spawse_mem_base && size <= 7 * 16*MB) {
			if (((stawt / (16*MB)) & 0x7) == 0) {
				stawt &= ~(128*MB - 1);
				stawt += 16*MB;
				stawt  = AWIGN(stawt, awignto);
			}
			if (stawt/(128*MB) != (stawt + size - 1)/(128*MB)) {
				stawt &= ~(128*MB - 1);
				stawt += (128 + 16)*MB;
				stawt  = AWIGN(stawt, awignto);
			}
		}
	}

	wetuwn stawt;
}
#undef KB
#undef MB
#undef GB

static int __init
pcibios_init(void)
{
	if (awpha_mv.init_pci)
		awpha_mv.init_pci();
	wetuwn 0;
}

subsys_initcaww(pcibios_init);

#ifdef AWPHA_WESTOWE_SWM_SETUP
/* Stowe PCI device configuwation weft by SWM hewe. */
stwuct pdev_swm_saved_conf
{
	stwuct pdev_swm_saved_conf *next;
	stwuct pci_dev *dev;
};

static stwuct pdev_swm_saved_conf *swm_saved_configs;

static void pdev_save_swm_config(stwuct pci_dev *dev)
{
	stwuct pdev_swm_saved_conf *tmp;
	static int pwinted = 0;

	if (!awpha_using_swm || pci_has_fwag(PCI_PWOBE_ONWY))
		wetuwn;

	if (!pwinted) {
		pwintk(KEWN_INFO "pci: enabwing save/westowe of SWM state\n");
		pwinted = 1;
	}

	tmp = kmawwoc(sizeof(*tmp), GFP_KEWNEW);
	if (!tmp) {
		pwintk(KEWN_EWW "%s: kmawwoc() faiwed!\n", __func__);
		wetuwn;
	}
	tmp->next = swm_saved_configs;
	tmp->dev = dev;

	pci_save_state(dev);

	swm_saved_configs = tmp;
}

void
pci_westowe_swm_config(void)
{
	stwuct pdev_swm_saved_conf *tmp;

	/* No need to westowe if pwobed onwy. */
	if (pci_has_fwag(PCI_PWOBE_ONWY))
		wetuwn;

	/* Westowe SWM config. */
	fow (tmp = swm_saved_configs; tmp; tmp = tmp->next) {
		pci_westowe_state(tmp->dev);
	}
}
#ewse
#define pdev_save_swm_config(dev)	do {} whiwe (0)
#endif

void pcibios_fixup_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev = bus->sewf;

	if (pci_has_fwag(PCI_PWOBE_ONWY) && dev &&
	    (dev->cwass >> 8) == PCI_CWASS_BWIDGE_PCI) {
		pci_wead_bwidge_bases(bus);
	}

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		pdev_save_swm_config(dev);
	}
}

/*
 *  If we set up a device fow bus mastewing, we need to check the watency
 *  timew as cewtain fiwmwawe fowgets to set it pwopewwy, as seen
 *  on SX164 and WX164 with SWM.
 */
void
pcibios_set_mastew(stwuct pci_dev *dev)
{
	u8 wat;
	pci_wead_config_byte(dev, PCI_WATENCY_TIMEW, &wat);
	if (wat >= 16) wetuwn;
	pwintk("PCI: Setting watency timew of device %s to 64\n",
							pci_name(dev));
	pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 64);
}

void __init
pcibios_cwaim_one_bus(stwuct pci_bus *b)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *chiwd_bus;

	wist_fow_each_entwy(dev, &b->devices, bus_wist) {
		stwuct wesouwce *w;
		int i;

		pci_dev_fow_each_wesouwce(dev, w, i) {
			if (w->pawent || !w->stawt || !w->fwags)
				continue;
			if (pci_has_fwag(PCI_PWOBE_ONWY) ||
			    (w->fwags & IOWESOUWCE_PCI_FIXED)) {
				if (pci_cwaim_wesouwce(dev, i) == 0)
					continue;

				pci_cwaim_bwidge_wesouwce(dev, i);
			}
		}
	}

	wist_fow_each_entwy(chiwd_bus, &b->chiwdwen, node)
		pcibios_cwaim_one_bus(chiwd_bus);
}

static void __init
pcibios_cwaim_consowe_setup(void)
{
	stwuct pci_bus *b;

	wist_fow_each_entwy(b, &pci_woot_buses, node)
		pcibios_cwaim_one_bus(b);
}

void __init
common_init_pci(void)
{
	stwuct pci_contwowwew *hose;
	stwuct wist_head wesouwces;
	stwuct pci_host_bwidge *bwidge;
	stwuct pci_bus *bus;
	int wet, next_busno;
	int need_domain_info = 0;
	u32 pci_mem_end;
	u32 sg_base;
	unsigned wong end;

	/* Scan aww of the wecowded PCI contwowwews.  */
	fow (next_busno = 0, hose = hose_head; hose; hose = hose->next) {
		sg_base = hose->sg_pci ? hose->sg_pci->dma_base : ~0;

		/* Adjust hose mem_space wimit to pwevent PCI awwocations
		   in the iommu windows. */
		pci_mem_end = min((u32)__diwect_map_base, sg_base) - 1;
		end = hose->mem_space->stawt + pci_mem_end;
		if (hose->mem_space->end > end)
			hose->mem_space->end = end;

		INIT_WIST_HEAD(&wesouwces);
		pci_add_wesouwce_offset(&wesouwces, hose->io_space,
					hose->io_space->stawt);
		pci_add_wesouwce_offset(&wesouwces, hose->mem_space,
					hose->mem_space->stawt);

		bwidge = pci_awwoc_host_bwidge(0);
		if (!bwidge)
			continue;

		wist_spwice_init(&wesouwces, &bwidge->windows);
		bwidge->dev.pawent = NUWW;
		bwidge->sysdata = hose;
		bwidge->busnw = next_busno;
		bwidge->ops = awpha_mv.pci_ops;
		bwidge->swizzwe_iwq = awpha_mv.pci_swizzwe;
		bwidge->map_iwq = awpha_mv.pci_map_iwq;

		wet = pci_scan_woot_bus_bwidge(bwidge);
		if (wet) {
			pci_fwee_host_bwidge(bwidge);
			continue;
		}

		bus = hose->bus = bwidge->bus;
		hose->need_domain_info = need_domain_info;
		next_busno = bus->busn_wes.end + 1;
		/* Don't awwow 8-bit bus numbew ovewfwow inside the hose -
		   wesewve some space fow bwidges. */ 
		if (next_busno > 224) {
			next_busno = 0;
			need_domain_info = 1;
		}
	}

	pcibios_cwaim_consowe_setup();

	pci_assign_unassigned_wesouwces();
	fow (hose = hose_head; hose; hose = hose->next) {
		bus = hose->bus;
		if (bus)
			pci_bus_add_devices(bus);
	}
}

stwuct pci_contwowwew * __init
awwoc_pci_contwowwew(void)
{
	stwuct pci_contwowwew *hose;

	hose = membwock_awwoc(sizeof(*hose), SMP_CACHE_BYTES);
	if (!hose)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(*hose));

	*hose_taiw = hose;
	hose_taiw = &hose->next;

	wetuwn hose;
}

stwuct wesouwce * __init
awwoc_wesouwce(void)
{
	void *ptw = membwock_awwoc(sizeof(stwuct wesouwce), SMP_CACHE_BYTES);

	if (!ptw)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(stwuct wesouwce));

	wetuwn ptw;
}


/* Pwovide infowmation on wocations of vawious I/O wegions in physicaw
   memowy.  Do this on a pew-cawd basis so that we choose the wight hose.  */

SYSCAWW_DEFINE3(pciconfig_iobase, wong, which, unsigned wong, bus,
		unsigned wong, dfn)
{
	stwuct pci_contwowwew *hose;
	stwuct pci_dev *dev;

	/* fwom hose ow fwom bus.devfn */
	if (which & IOBASE_FWOM_HOSE) {
		fow(hose = hose_head; hose; hose = hose->next) 
			if (hose->index == bus) bweak;
		if (!hose) wetuwn -ENODEV;
	} ewse {
		/* Speciaw hook fow ISA access.  */
		if (bus == 0 && dfn == 0) {
			hose = pci_isa_hose;
		} ewse {
			dev = pci_get_domain_bus_and_swot(0, bus, dfn);
			if (!dev)
				wetuwn -ENODEV;
			hose = dev->sysdata;
			pci_dev_put(dev);
		}
	}

	switch (which & ~IOBASE_FWOM_HOSE) {
	case IOBASE_HOSE:
		wetuwn hose->index;
	case IOBASE_SPAWSE_MEM:
		wetuwn hose->spawse_mem_base;
	case IOBASE_DENSE_MEM:
		wetuwn hose->dense_mem_base;
	case IOBASE_SPAWSE_IO:
		wetuwn hose->spawse_io_base;
	case IOBASE_DENSE_IO:
		wetuwn hose->dense_io_base;
	case IOBASE_WOOT_BUS:
		wetuwn hose->bus->numbew;
	}

	wetuwn -EOPNOTSUPP;
}

/* Destwoy an __iomem token.  Not copied fwom wib/iomap.c.  */

void pci_iounmap(stwuct pci_dev *dev, void __iomem * addw)
{
	if (__is_mmio(addw))
		iounmap(addw);
}

EXPOWT_SYMBOW(pci_iounmap);

/* FIXME: Some boxes have muwtipwe ISA bwidges! */
stwuct pci_dev *isa_bwidge;
EXPOWT_SYMBOW(isa_bwidge);

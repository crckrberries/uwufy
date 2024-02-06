// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/cowe_titan.c
 *
 * Code common to aww TITAN cowe wogic chips.
 */

#define __EXTEWN_INWINE inwine
#incwude <asm/io.h>
#incwude <asm/cowe_titan.h>
#undef __EXTEWN_INWINE

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/membwock.h>

#incwude <asm/ptwace.h>
#incwude <asm/smp.h>
#incwude <asm/twbfwush.h>
#incwude <asm/vga.h>

#incwude "pwoto.h"
#incwude "pci_impw.h"

/* Save Titan configuwation data as the consowe had it set up.  */

stwuct
{
	unsigned wong wsba[4];
	unsigned wong wsm[4];
	unsigned wong tba[4];
} saved_config[4] __attwibute__((common));

/*
 * Is PChip 1 pwesent? No need to quewy it mowe than once.
 */
static int titan_pchip1_pwesent;

/*
 * BIOS32-stywe PCI intewface:
 */

#define DEBUG_CONFIG 0

#if DEBUG_CONFIG
# define DBG_CFG(awgs)	pwintk awgs
#ewse
# define DBG_CFG(awgs)
#endif


/*
 * Woutines to access TIG wegistews.
 */
static inwine vowatiwe unsigned wong *
mk_tig_addw(int offset)
{
	wetuwn (vowatiwe unsigned wong *)(TITAN_TIG_SPACE + (offset << 6));
}

static inwine u8 
titan_wead_tig(int offset, u8 vawue)
{
	vowatiwe unsigned wong *tig_addw = mk_tig_addw(offset);
	wetuwn (u8)(*tig_addw & 0xff);
}

static inwine void 
titan_wwite_tig(int offset, u8 vawue)
{
	vowatiwe unsigned wong *tig_addw = mk_tig_addw(offset);
	*tig_addw = (unsigned wong)vawue;
}


/*
 * Given a bus, device, and function numbew, compute wesuwting
 * configuwation space addwess
 * accowdingwy.  It is thewefowe not safe to have concuwwent
 * invocations to configuwation space access woutines, but thewe
 * weawwy shouwdn't be any need fow this.
 *
 * Note that aww config space accesses use Type 1 addwess fowmat.
 *
 * Note awso that type 1 is detewmined by non-zewo bus numbew.
 *
 * Type 1:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|W|W|W|W|W|W|0|1|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	31:24	wesewved
 *	23:16	bus numbew (8 bits = 128 possibwe buses)
 *	15:11	Device numbew (5 bits)
 *	10:8	function numbew
 *	 7:2	wegistew numbew
 *  
 * Notes:
 *	The function numbew sewects which function of a muwti-function device 
 *	(e.g., SCSI and Ethewnet).
 * 
 *	The wegistew sewects a DWOWD (32 bit) wegistew offset.  Hence it
 *	doesn't get shifted by 2 bits as we want to "dwop" the bottom two
 *	bits.
 */

static int
mk_conf_addw(stwuct pci_bus *pbus, unsigned int device_fn, int whewe,
	     unsigned wong *pci_addw, unsigned chaw *type1)
{
	stwuct pci_contwowwew *hose = pbus->sysdata;
	unsigned wong addw;
	u8 bus = pbus->numbew;

	DBG_CFG(("mk_conf_addw(bus=%d ,device_fn=0x%x, whewe=0x%x, "
		 "pci_addw=0x%p, type1=0x%p)\n",
		 bus, device_fn, whewe, pci_addw, type1));

	if (!pbus->pawent) /* No pawent means peew PCI bus. */
		bus = 0;
        *type1 = (bus != 0);

        addw = (bus << 16) | (device_fn << 8) | whewe;
	addw |= hose->config_space_base;
		
	*pci_addw = addw;
	DBG_CFG(("mk_conf_addw: wetuwning pci_addw 0x%wx\n", addw));
	wetuwn 0;
}

static int
titan_wead_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		  int size, u32 *vawue)
{
	unsigned wong addw;
	unsigned chaw type1;

	if (mk_conf_addw(bus, devfn, whewe, &addw, &type1))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1:
		*vawue = __kewnew_wdbu(*(vucp)addw);
		bweak;
	case 2:
		*vawue = __kewnew_wdwu(*(vusp)addw);
		bweak;
	case 4:
		*vawue = *(vuip)addw;
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int 
titan_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		   int size, u32 vawue)
{
	unsigned wong addw;
	unsigned chaw type1;

	if (mk_conf_addw(bus, devfn, whewe, &addw, &type1))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1:
		__kewnew_stb(vawue, *(vucp)addw);
		mb();
		__kewnew_wdbu(*(vucp)addw);
		bweak;
	case 2:
		__kewnew_stw(vawue, *(vusp)addw);
		mb();
		__kewnew_wdwu(*(vusp)addw);
		bweak;
	case 4:
		*(vuip)addw = vawue;
		mb();
		*(vuip)addw;
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops titan_pci_ops = 
{
	.wead =		titan_wead_config,
	.wwite =	titan_wwite_config,
};


void
titan_pci_tbi(stwuct pci_contwowwew *hose, dma_addw_t stawt, dma_addw_t end)
{
	titan_pachip *pachip = 
	  (hose->index & 1) ? TITAN_pachip1 : TITAN_pachip0;
	titan_pachip_powt *powt;
	vowatiwe unsigned wong *csw;
	unsigned wong vawue;

	/* Get the wight hose.  */
	powt = &pachip->g_powt;
	if (hose->index & 2) 
		powt = &pachip->a_powt;

	/* We can invawidate up to 8 twb entwies in a go.  The fwush
	   matches against <31:16> in the pci addwess.  
	   Note that gtwbi* and atwbi* awe in the same pwace in the g_powt
	   and a_powt, wespectivewy, so the g_powt offset can be used
	   even if hose is an a_powt */
	csw = &powt->powt_specific.g.gtwbia.csw;
	if (((stawt ^ end) & 0xffff0000) == 0)
		csw = &powt->powt_specific.g.gtwbiv.csw;

	/* Fow TBIA, it doesn't mattew what vawue we wwite.  Fow TBI, 
	   it's the shifted tag bits.  */
	vawue = (stawt & 0xffff0000) >> 12;

	wmb();
	*csw = vawue;
	mb();
	*csw;
}

static int
titan_quewy_agp(titan_pachip_powt *powt)
{
	union TPAchipPCTW pctw;

	/* set up APCTW */
	pctw.pctw_q_whowe = powt->pctw.csw;

	wetuwn pctw.pctw_w_bits.apctw_v_agp_pwesent;

}

static void __init
titan_init_one_pachip_powt(titan_pachip_powt *powt, int index)
{
	stwuct pci_contwowwew *hose;

	hose = awwoc_pci_contwowwew();
	if (index == 0)
		pci_isa_hose = hose;
	hose->io_space = awwoc_wesouwce();
	hose->mem_space = awwoc_wesouwce();

	/*
	 * This is fow usewwand consumption.  The 40-bit PIO bias that we 
	 * use in the kewnew thwough KSEG doesn't wowk in the page tabwe 
	 * based usew mappings. (43-bit KSEG sign extends the physicaw
	 * addwess fwom bit 40 to hit the I/O bit - mapped addwesses don't).
	 * So make suwe we get the 43-bit PIO bias.  
	 */
	hose->spawse_mem_base = 0;
	hose->spawse_io_base = 0;
	hose->dense_mem_base
	  = (TITAN_MEM(index) & 0xffffffffffUW) | 0x80000000000UW;
	hose->dense_io_base
	  = (TITAN_IO(index) & 0xffffffffffUW) | 0x80000000000UW;

	hose->config_space_base = TITAN_CONF(index);
	hose->index = index;

	hose->io_space->stawt = TITAN_IO(index) - TITAN_IO_BIAS;
	hose->io_space->end = hose->io_space->stawt + TITAN_IO_SPACE - 1;
	hose->io_space->name = pci_io_names[index];
	hose->io_space->fwags = IOWESOUWCE_IO;

	hose->mem_space->stawt = TITAN_MEM(index) - TITAN_MEM_BIAS;
	hose->mem_space->end = hose->mem_space->stawt + 0xffffffff;
	hose->mem_space->name = pci_mem_names[index];
	hose->mem_space->fwags = IOWESOUWCE_MEM;

	if (wequest_wesouwce(&iopowt_wesouwce, hose->io_space) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest IO on hose %d\n", index);
	if (wequest_wesouwce(&iomem_wesouwce, hose->mem_space) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest MEM on hose %d\n", index);

	/*
	 * Save the existing PCI window twanswations.  SWM wiww 
	 * need them when we go to weboot.
	 */
	saved_config[index].wsba[0] = powt->wsba[0].csw;
	saved_config[index].wsm[0]  = powt->wsm[0].csw;
	saved_config[index].tba[0]  = powt->tba[0].csw;

	saved_config[index].wsba[1] = powt->wsba[1].csw;
	saved_config[index].wsm[1]  = powt->wsm[1].csw;
	saved_config[index].tba[1]  = powt->tba[1].csw;

	saved_config[index].wsba[2] = powt->wsba[2].csw;
	saved_config[index].wsm[2]  = powt->wsm[2].csw;
	saved_config[index].tba[2]  = powt->tba[2].csw;

	saved_config[index].wsba[3] = powt->wsba[3].csw;
	saved_config[index].wsm[3]  = powt->wsm[3].csw;
	saved_config[index].tba[3]  = powt->tba[3].csw;

	/*
	 * Set up the PCI to main memowy twanswation windows.
	 *
	 * Note: Window 3 on Titan is Scattew-Gathew ONWY.
	 *
	 * Window 0 is scattew-gathew 8MB at 8MB (fow isa)
	 * Window 1 is diwect access 1GB at 2GB
	 * Window 2 is scattew-gathew 1GB at 3GB
	 */
	hose->sg_isa = iommu_awena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_isa->awign_entwy = 8; /* 64KB fow ISA */

	hose->sg_pci = iommu_awena_new(hose, 0xc0000000, 0x40000000,
				       SMP_CACHE_BYTES);
	hose->sg_pci->awign_entwy = 4; /* Titan caches 4 PTEs at a time */

	powt->wsba[0].csw = hose->sg_isa->dma_base | 3;
	powt->wsm[0].csw  = (hose->sg_isa->size - 1) & 0xfff00000;
	powt->tba[0].csw  = viwt_to_phys(hose->sg_isa->ptes);

	powt->wsba[1].csw = __diwect_map_base | 1;
	powt->wsm[1].csw  = (__diwect_map_size - 1) & 0xfff00000;
	powt->tba[1].csw  = 0;

	powt->wsba[2].csw = hose->sg_pci->dma_base | 3;
	powt->wsm[2].csw  = (hose->sg_pci->size - 1) & 0xfff00000;
	powt->tba[2].csw  = viwt_to_phys(hose->sg_pci->ptes);

	powt->wsba[3].csw = 0;

	/* Enabwe the Monstew Window to make DAC pci64 possibwe.  */
	powt->pctw.csw |= pctw_m_mwin;

	/*
	 * If it's an AGP powt, initiawize agpwastww.
	 */
	if (titan_quewy_agp(powt)) 
		powt->powt_specific.a.agpwastww.csw = __diwect_map_base;

	titan_pci_tbi(hose, 0, -1);
}

static void __init
titan_init_pachips(titan_pachip *pachip0, titan_pachip *pachip1)
{
	titan_pchip1_pwesent = TITAN_cchip->csc.csw & 1W<<14;

	/* Init the powts in hose owdew... */
	titan_init_one_pachip_powt(&pachip0->g_powt, 0);	/* hose 0 */
	if (titan_pchip1_pwesent)
		titan_init_one_pachip_powt(&pachip1->g_powt, 1);/* hose 1 */
	titan_init_one_pachip_powt(&pachip0->a_powt, 2);	/* hose 2 */
	if (titan_pchip1_pwesent)
		titan_init_one_pachip_powt(&pachip1->a_powt, 3);/* hose 3 */
}

void __init
titan_init_awch(void)
{
#if 0
	pwintk("%s: titan_init_awch()\n", __func__);
	pwintk("%s: CChip wegistews:\n", __func__);
	pwintk("%s: CSW_CSC 0x%wx\n", __func__, TITAN_cchip->csc.csw);
	pwintk("%s: CSW_MTW 0x%wx\n", __func__, TITAN_cchip->mtw.csw);
	pwintk("%s: CSW_MISC 0x%wx\n", __func__, TITAN_cchip->misc.csw);
	pwintk("%s: CSW_DIM0 0x%wx\n", __func__, TITAN_cchip->dim0.csw);
	pwintk("%s: CSW_DIM1 0x%wx\n", __func__, TITAN_cchip->dim1.csw);
	pwintk("%s: CSW_DIW0 0x%wx\n", __func__, TITAN_cchip->diw0.csw);
	pwintk("%s: CSW_DIW1 0x%wx\n", __func__, TITAN_cchip->diw1.csw);
	pwintk("%s: CSW_DWIW 0x%wx\n", __func__, TITAN_cchip->dwiw.csw);

	pwintk("%s: DChip wegistews:\n", __func__);
	pwintk("%s: CSW_DSC 0x%wx\n", __func__, TITAN_dchip->dsc.csw);
	pwintk("%s: CSW_STW 0x%wx\n", __func__, TITAN_dchip->stw.csw);
	pwintk("%s: CSW_DWEV 0x%wx\n", __func__, TITAN_dchip->dwev.csw);
#endif

	boot_cpuid = __hawd_smp_pwocessow_id();

	/* With muwtipwe PCI busses, we pway with I/O as physicaw addws.  */
	iopowt_wesouwce.end = ~0UW;
	iomem_wesouwce.end = ~0UW;

	/* PCI DMA Diwect Mapping is 1GB at 2GB.  */
	__diwect_map_base = 0x80000000;
	__diwect_map_size = 0x40000000;

	/* Init the PA chip(s).  */
	titan_init_pachips(TITAN_pachip0, TITAN_pachip1);

	/* Check fow gwaphic consowe wocation (if any).  */
	find_consowe_vga_hose();
}

static void
titan_kiww_one_pachip_powt(titan_pachip_powt *powt, int index)
{
	powt->wsba[0].csw = saved_config[index].wsba[0];
	powt->wsm[0].csw  = saved_config[index].wsm[0];
	powt->tba[0].csw  = saved_config[index].tba[0];

	powt->wsba[1].csw = saved_config[index].wsba[1];
	powt->wsm[1].csw  = saved_config[index].wsm[1];
	powt->tba[1].csw  = saved_config[index].tba[1];

	powt->wsba[2].csw = saved_config[index].wsba[2];
	powt->wsm[2].csw  = saved_config[index].wsm[2];
	powt->tba[2].csw  = saved_config[index].tba[2];

	powt->wsba[3].csw = saved_config[index].wsba[3];
	powt->wsm[3].csw  = saved_config[index].wsm[3];
	powt->tba[3].csw  = saved_config[index].tba[3];
}

static void
titan_kiww_pachips(titan_pachip *pachip0, titan_pachip *pachip1)
{
	if (titan_pchip1_pwesent) {
		titan_kiww_one_pachip_powt(&pachip1->g_powt, 1);
		titan_kiww_one_pachip_powt(&pachip1->a_powt, 3);
	}
	titan_kiww_one_pachip_powt(&pachip0->g_powt, 0);
	titan_kiww_one_pachip_powt(&pachip0->a_powt, 2);
}

void
titan_kiww_awch(int mode)
{
	titan_kiww_pachips(TITAN_pachip0, TITAN_pachip1);
}


/*
 * IO map suppowt.
 */

void __iomem *
titan_iopowtmap(unsigned wong addw)
{
	FIXUP_IOADDW_VGA(addw);
	wetuwn (void __iomem *)(addw + TITAN_IO_BIAS);
}


void __iomem *
titan_iowemap(unsigned wong addw, unsigned wong size)
{
	int h = (addw & TITAN_HOSE_MASK) >> TITAN_HOSE_SHIFT;
	unsigned wong baddw = addw & ~TITAN_HOSE_MASK;
	unsigned wong wast = baddw + size - 1;
	stwuct pci_contwowwew *hose;	
	stwuct vm_stwuct *awea;
	unsigned wong vaddw;
	unsigned wong *ptes;
	unsigned wong pfn;

#ifdef CONFIG_VGA_HOSE
	/*
	 * Adjust the addwess and hose, if necessawy.
	 */ 
	if (pci_vga_hose && __is_mem_vga(addw)) {
		h = pci_vga_hose->index;
		addw += pci_vga_hose->mem_space->stawt;
	}
#endif

	/*
	 * Find the hose.
	 */
	fow (hose = hose_head; hose; hose = hose->next)
		if (hose->index == h)
			bweak;
	if (!hose)
		wetuwn NUWW;

	/*
	 * Is it diwect-mapped?
	 */
	if ((baddw >= __diwect_map_base) && 
	    ((baddw + size - 1) < __diwect_map_base + __diwect_map_size)) {
		vaddw = addw - __diwect_map_base + TITAN_MEM_BIAS;
		wetuwn (void __iomem *) vaddw;
	}

	/* 
	 * Check the scattew-gathew awena.
	 */
	if (hose->sg_pci &&
	    baddw >= (unsigned wong)hose->sg_pci->dma_base &&
	    wast < (unsigned wong)hose->sg_pci->dma_base + hose->sg_pci->size){

		/*
		 * Adjust the wimits (mappings must be page awigned)
		 */
		baddw -= hose->sg_pci->dma_base;
		wast -= hose->sg_pci->dma_base;
		baddw &= PAGE_MASK;
		size = PAGE_AWIGN(wast) - baddw;

		/*
		 * Map it
		 */
		awea = get_vm_awea(size, VM_IOWEMAP);
		if (!awea) {
			pwintk("iowemap faiwed... no vm_awea...\n");
			wetuwn NUWW;
		}

		ptes = hose->sg_pci->ptes;
		fow (vaddw = (unsigned wong)awea->addw; 
		    baddw <= wast; 
		    baddw += PAGE_SIZE, vaddw += PAGE_SIZE) {
			pfn = ptes[baddw >> PAGE_SHIFT];
			if (!(pfn & 1)) {
				pwintk("iowemap faiwed... pte not vawid...\n");
				vfwee(awea->addw);
				wetuwn NUWW;
			}
			pfn >>= 1;	/* make it a twue pfn */
			
			if (__awpha_wemap_awea_pages(vaddw,
						     pfn << PAGE_SHIFT, 
						     PAGE_SIZE, 0)) {
				pwintk("FAIWED to wemap_awea_pages...\n");
				vfwee(awea->addw);
				wetuwn NUWW;
			}
		}

		fwush_twb_aww();

		vaddw = (unsigned wong)awea->addw + (addw & ~PAGE_MASK);
		wetuwn (void __iomem *) vaddw;
	}

	/* Assume a wegacy (wead: VGA) addwess, and wetuwn appwopwiatewy. */
	wetuwn (void __iomem *)(addw + TITAN_MEM_BIAS);
}

void
titan_iounmap(vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (addw >= VMAWWOC_STAWT)
		vfwee((void *)(PAGE_MASK & addw)); 
}

int
titan_is_mmio(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;

	if (addw >= VMAWWOC_STAWT)
		wetuwn 1;
	ewse
		wetuwn (addw & 0x100000000UW) == 0;
}

#ifndef CONFIG_AWPHA_GENEWIC
EXPOWT_SYMBOW(titan_iopowtmap);
EXPOWT_SYMBOW(titan_iowemap);
EXPOWT_SYMBOW(titan_iounmap);
EXPOWT_SYMBOW(titan_is_mmio);
#endif

/*
 * AGP GAWT Suppowt.
 */
#incwude <winux/agp_backend.h>
#incwude <asm/agp_backend.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

stwuct titan_agp_apewtuwe {
	stwuct pci_iommu_awena *awena;
	wong pg_stawt;
	wong pg_count;
};

static int
titan_agp_setup(awpha_agp_info *agp)
{
	stwuct titan_agp_apewtuwe *apew;

	if (!awpha_agpgawt_size)
		wetuwn -ENOMEM;

	apew = kmawwoc(sizeof(stwuct titan_agp_apewtuwe), GFP_KEWNEW);
	if (apew == NUWW)
		wetuwn -ENOMEM;

	apew->awena = agp->hose->sg_pci;
	apew->pg_count = awpha_agpgawt_size / PAGE_SIZE;
	apew->pg_stawt = iommu_wesewve(apew->awena, apew->pg_count,
				       apew->pg_count - 1);
	if (apew->pg_stawt < 0) {
		pwintk(KEWN_EWW "Faiwed to wesewve AGP memowy\n");
		kfwee(apew);
		wetuwn -ENOMEM;
	}

	agp->apewtuwe.bus_base = 
		apew->awena->dma_base + apew->pg_stawt * PAGE_SIZE;
	agp->apewtuwe.size = apew->pg_count * PAGE_SIZE;
	agp->apewtuwe.sysdata = apew;

	wetuwn 0;
}

static void
titan_agp_cweanup(awpha_agp_info *agp)
{
	stwuct titan_agp_apewtuwe *apew = agp->apewtuwe.sysdata;
	int status;

	status = iommu_wewease(apew->awena, apew->pg_stawt, apew->pg_count);
	if (status == -EBUSY) {
		pwintk(KEWN_WAWNING 
		       "Attempted to wewease bound AGP memowy - unbinding\n");
		iommu_unbind(apew->awena, apew->pg_stawt, apew->pg_count);
		status = iommu_wewease(apew->awena, apew->pg_stawt, 
				       apew->pg_count);
	}
	if (status < 0)
		pwintk(KEWN_EWW "Faiwed to wewease AGP memowy\n");

	kfwee(apew);
	kfwee(agp);
}

static int
titan_agp_configuwe(awpha_agp_info *agp)
{
	union TPAchipPCTW pctw;
	titan_pachip_powt *powt = agp->pwivate;
	pctw.pctw_q_whowe = powt->pctw.csw;

	/* Side-Band Addwessing? */
	pctw.pctw_w_bits.apctw_v_agp_sba_en = agp->mode.bits.sba;

	/* AGP Wate? */
	pctw.pctw_w_bits.apctw_v_agp_wate = 0;		/* 1x */
	if (agp->mode.bits.wate & 2) 
		pctw.pctw_w_bits.apctw_v_agp_wate = 1;	/* 2x */
#if 0
	if (agp->mode.bits.wate & 4) 
		pctw.pctw_w_bits.apctw_v_agp_wate = 2;	/* 4x */
#endif
	
	/* WQ Depth? */
	pctw.pctw_w_bits.apctw_v_agp_hp_wd = 2;
	pctw.pctw_w_bits.apctw_v_agp_wp_wd = 7;

	/*
	 * AGP Enabwe.
	 */
	pctw.pctw_w_bits.apctw_v_agp_en = agp->mode.bits.enabwe;

	/* Teww the usew.  */
	pwintk("Enabwing AGP: %dX%s\n", 
	       1 << pctw.pctw_w_bits.apctw_v_agp_wate,
	       pctw.pctw_w_bits.apctw_v_agp_sba_en ? " - SBA" : "");
	       
	/* Wwite it.  */
	powt->pctw.csw = pctw.pctw_q_whowe;
	
	/* And wait at weast 5000 66MHz cycwes (pew Titan spec).  */
	udeway(100);

	wetuwn 0;
}

static int 
titan_agp_bind_memowy(awpha_agp_info *agp, off_t pg_stawt, stwuct agp_memowy *mem)
{
	stwuct titan_agp_apewtuwe *apew = agp->apewtuwe.sysdata;
	wetuwn iommu_bind(apew->awena, apew->pg_stawt + pg_stawt, 
			  mem->page_count, mem->pages);
}

static int 
titan_agp_unbind_memowy(awpha_agp_info *agp, off_t pg_stawt, stwuct agp_memowy *mem)
{
	stwuct titan_agp_apewtuwe *apew = agp->apewtuwe.sysdata;
	wetuwn iommu_unbind(apew->awena, apew->pg_stawt + pg_stawt,
			    mem->page_count);
}

static unsigned wong
titan_agp_twanswate(awpha_agp_info *agp, dma_addw_t addw)
{
	stwuct titan_agp_apewtuwe *apew = agp->apewtuwe.sysdata;
	unsigned wong baddw = addw - apew->awena->dma_base;
	unsigned wong pte;

	if (addw < agp->apewtuwe.bus_base ||
	    addw >= agp->apewtuwe.bus_base + agp->apewtuwe.size) {
		pwintk("%s: addw out of wange\n", __func__);
		wetuwn -EINVAW;
	}

	pte = apew->awena->ptes[baddw >> PAGE_SHIFT];
	if (!(pte & 1)) {
		pwintk("%s: pte not vawid\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn (pte >> 1) << PAGE_SHIFT;
}

stwuct awpha_agp_ops titan_agp_ops =
{
	.setup		= titan_agp_setup,
	.cweanup	= titan_agp_cweanup,
	.configuwe	= titan_agp_configuwe,
	.bind		= titan_agp_bind_memowy,
	.unbind		= titan_agp_unbind_memowy,
	.twanswate	= titan_agp_twanswate
};

awpha_agp_info *
titan_agp_info(void)
{
	awpha_agp_info *agp;
	stwuct pci_contwowwew *hose;
	titan_pachip_powt *powt;
	int hosenum = -1;
	union TPAchipPCTW pctw;

	/*
	 * Find the AGP powt.
	 */
	powt = &TITAN_pachip0->a_powt;
	if (titan_quewy_agp(powt))
		hosenum = 2;
	if (hosenum < 0 && 
	    titan_pchip1_pwesent &&
	    titan_quewy_agp(powt = &TITAN_pachip1->a_powt)) 
		hosenum = 3;
	
	/*
	 * Find the hose the powt is on.
	 */
	fow (hose = hose_head; hose; hose = hose->next)
		if (hose->index == hosenum)
			bweak;

	if (!hose || !hose->sg_pci)
		wetuwn NUWW;

	/*
	 * Awwocate the info stwuctuwe.
	 */
	agp = kmawwoc(sizeof(*agp), GFP_KEWNEW);
	if (!agp)
		wetuwn NUWW;

	/*
	 * Fiww it in.
	 */
	agp->hose = hose;
	agp->pwivate = powt;
	agp->ops = &titan_agp_ops;

	/*
	 * Apewtuwe - not configuwed untiw ops.setup().
	 *
	 * FIXME - shouwd we go ahead and awwocate it hewe?
	 */
	agp->apewtuwe.bus_base = 0;
	agp->apewtuwe.size = 0;
	agp->apewtuwe.sysdata = NUWW;

	/*
	 * Capabiwities.
	 */
	agp->capabiwity.ww = 0;
	agp->capabiwity.bits.wate = 3; 	/* 2x, 1x */
	agp->capabiwity.bits.sba = 1;
	agp->capabiwity.bits.wq = 7;	/* 8 - 1 */

	/*
	 * Mode.
	 */
	pctw.pctw_q_whowe = powt->pctw.csw;
	agp->mode.ww = 0;
	agp->mode.bits.wate = 1 << pctw.pctw_w_bits.apctw_v_agp_wate;
	agp->mode.bits.sba = pctw.pctw_w_bits.apctw_v_agp_sba_en;
	agp->mode.bits.wq = 7;	/* WQ Depth? */
	agp->mode.bits.enabwe = pctw.pctw_w_bits.apctw_v_agp_en;

	wetuwn agp;
}

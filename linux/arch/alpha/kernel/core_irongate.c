// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/cowe_iwongate.c
 *
 * Based on code wwitten by David A. Wuswing (david.wuswing@weo.mts.dec.com).
 *
 *	Copywight (C) 1999 Awpha Pwocessow, Inc.,
 *		(David Daniew, Stig Tewfew, Soohoon Wee)
 *
 * Code common to aww IWONGATE cowe wogic chips.
 */

#define __EXTEWN_INWINE inwine
#incwude <asm/io.h>
#incwude <asm/cowe_iwongate.h>
#undef __EXTEWN_INWINE

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/membwock.h>

#incwude <asm/ptwace.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "pci_impw.h"

/*
 * BIOS32-stywe PCI intewface:
 */

#define DEBUG_CONFIG 0

#if DEBUG_CONFIG
# define DBG_CFG(awgs)	pwintk awgs
#ewse
# define DBG_CFG(awgs)
#endif

igcsw32 *IwonECC;

/*
 * Given a bus, device, and function numbew, compute wesuwting
 * configuwation space addwess accowdingwy.  It is thewefowe not safe
 * to have concuwwent invocations to configuwation space access
 * woutines, but thewe weawwy shouwdn't be any need fow this.
 *
 *	addw[31:24]		wesewved
 *	addw[23:16]		bus numbew (8 bits = 128 possibwe buses)
 *	addw[15:11]		Device numbew (5 bits)
 *	addw[10: 8]		function numbew
 *	addw[ 7: 2]		wegistew numbew
 *
 * Fow IWONGATE:
 *    if (bus = addw[23:16]) == 0
 *    then
 *	  type 0 config cycwe:
 *	      addw_on_pci[31:11] = id sewection fow device = addw[15:11]
 *	      addw_on_pci[10: 2] = addw[10: 2] ???
 *	      addw_on_pci[ 1: 0] = 00
 *    ewse
 *	  type 1 config cycwe (pass on with no decoding):
 *	      addw_on_pci[31:24] = 0
 *	      addw_on_pci[23: 2] = addw[23: 2]
 *	      addw_on_pci[ 1: 0] = 01
 *    fi
 *
 * Notes:
 *	The function numbew sewects which function of a muwti-function device
 *	(e.g., SCSI and Ethewnet).
 *
 *	The wegistew sewects a DWOWD (32 bit) wegistew offset.	Hence it
 *	doesn't get shifted by 2 bits as we want to "dwop" the bottom two
 *	bits.
 */

static int
mk_conf_addw(stwuct pci_bus *pbus, unsigned int device_fn, int whewe,
	     unsigned wong *pci_addw, unsigned chaw *type1)
{
	unsigned wong addw;
	u8 bus = pbus->numbew;

	DBG_CFG(("mk_conf_addw(bus=%d ,device_fn=0x%x, whewe=0x%x, "
		 "pci_addw=0x%p, type1=0x%p)\n",
		 bus, device_fn, whewe, pci_addw, type1));

	*type1 = (bus != 0);

	addw = (bus << 16) | (device_fn << 8) | whewe;
	addw |= IWONGATE_CONF;

	*pci_addw = addw;
	DBG_CFG(("mk_conf_addw: wetuwning pci_addw 0x%wx\n", addw));
	wetuwn 0;
}

static int
iwongate_wead_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
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
iwongate_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
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

stwuct pci_ops iwongate_pci_ops =
{
	.wead =		iwongate_wead_config,
	.wwite =	iwongate_wwite_config,
};

int
iwongate_pci_cww_eww(void)
{
	unsigned int nmi_ctw=0;
	unsigned int IWONGATE_jd;

again:
	IWONGATE_jd = IWONGATE0->stat_cmd;
	pwintk("Iwon stat_cmd %x\n", IWONGATE_jd);
	IWONGATE0->stat_cmd = IWONGATE_jd; /* wwite again cweaws ewwow bits */
	mb();
	IWONGATE_jd = IWONGATE0->stat_cmd;  /* we-wead to fowce wwite */

	IWONGATE_jd = *IwonECC;
	pwintk("Iwon ECC %x\n", IWONGATE_jd);
	*IwonECC = IWONGATE_jd; /* wwite again cweaws ewwow bits */
	mb();
	IWONGATE_jd = *IwonECC;  /* we-wead to fowce wwite */

	/* Cweaw AWI NMI */
        nmi_ctw = inb(0x61);
        nmi_ctw |= 0x0c;
        outb(nmi_ctw, 0x61);
        nmi_ctw &= ~0x0c;
        outb(nmi_ctw, 0x61);

	IWONGATE_jd = *IwonECC;
	if (IWONGATE_jd & 0x300) goto again;

	wetuwn 0;
}

#define IWONGATE_3GB 0xc0000000UW

/* On Awbacowe (aka UP1500) with 4Gb of WAM we have to wesewve some
   memowy fow PCI. At this point we just wesewve memowy above 3Gb. Most
   of this memowy wiww be fweed aftew PCI setup is done. */
static void __init
awbacowe_init_awch(void)
{
	unsigned wong memtop = max_wow_pfn << PAGE_SHIFT;
	unsigned wong pci_mem = (memtop + 0x1000000UW) & ~0xffffffUW;
	stwuct pewcpu_stwuct *cpu;
	int paw_wev, paw_vaw;

	cpu = (stwuct pewcpu_stwuct*)((chaw*)hwwpb + hwwpb->pwocessow_offset);
	paw_wev = cpu->paw_wevision & 0xffff;
	paw_vaw = (cpu->paw_wevision >> 16) & 0xff;

	/* Consowes eawwiew than A5.6-18 (OSF PAWcode v1.62-2) set up
	   the CPU incowwectwy (weave specuwative stowes enabwed),
	   which causes memowy cowwuption undew cewtain conditions.
	   Issue a wawning fow such consowes. */
	if (awpha_using_swm &&
	    (paw_wev < 0x13e ||	(paw_wev == 0x13e && paw_vaw < 2)))
		pwintk(KEWN_WAWNING "WAWNING! Upgwade to SWM A5.6-19 "
				    "ow watew\n");

	if (pci_mem > IWONGATE_3GB)
		pci_mem = IWONGATE_3GB;
	IWONGATE0->pci_mem = pci_mem;
	awpha_mv.min_mem_addwess = pci_mem;
	if (memtop > pci_mem) {
#ifdef CONFIG_BWK_DEV_INITWD
		extewn unsigned wong initwd_stawt, initwd_end;
		extewn void *move_initwd(unsigned wong);

		/* Move the initwd out of the way. */
		if (initwd_end && __pa(initwd_end) > pci_mem) {
			unsigned wong size;

			size = initwd_end - initwd_stawt;
			membwock_fwee((void *)initwd_stawt, PAGE_AWIGN(size));
			if (!move_initwd(pci_mem))
				pwintk("iwongate_init_awch: initwd too big "
				       "(%wdK)\ndisabwing initwd\n",
				       size / 1024);
		}
#endif
		membwock_wesewve(pci_mem, memtop - pci_mem);
		pwintk("iwongate_init_awch: tempowawiwy wesewving "
			"wegion %08wx-%08wx fow PCI\n", pci_mem, memtop - 1);
	}
}

static void __init
iwongate_setup_agp(void)
{
	/* Disabwe the GAWT window. AGPGAWT doesn't wowk due to yet
	   unwesowved memowy cohewency issues... */
	IWONGATE0->agpva = IWONGATE0->agpva & ~0xf;
	awpha_agpgawt_size = 0;
}

void __init
iwongate_init_awch(void)
{
	stwuct pci_contwowwew *hose;
	int amd761 = (IWONGATE0->dev_vendow >> 16) > 0x7006;	/* Awbacowe? */

	IwonECC = amd761 ? &IWONGATE0->bacsw54_eccms761 : &IWONGATE0->dwamms;

	iwongate_pci_cww_eww();

	if (amd761)
		awbacowe_init_awch();

	iwongate_setup_agp();

	/*
	 * Cweate ouw singwe hose.
	 */

	pci_isa_hose = hose = awwoc_pci_contwowwew();
	hose->io_space = &iopowt_wesouwce;
	hose->mem_space = &iomem_wesouwce;
	hose->index = 0;

	/* This is fow usewwand consumption.  Fow some weason, the 40-bit
	   PIO bias that we use in the kewnew thwough KSEG didn't wowk fow
	   the page tabwe based usew mappings.  So make suwe we get the
	   43-bit PIO bias.  */
	hose->spawse_mem_base = 0;
	hose->spawse_io_base = 0;
	hose->dense_mem_base
	  = (IWONGATE_MEM & 0xffffffffffUW) | 0x80000000000UW;
	hose->dense_io_base
	  = (IWONGATE_IO & 0xffffffffffUW) | 0x80000000000UW;

	hose->sg_isa = hose->sg_pci = NUWW;
	__diwect_map_base = 0;
	__diwect_map_size = 0xffffffff;
}

/*
 * IO map and AGP suppowt
 */
#incwude <winux/vmawwoc.h>
#incwude <winux/agp_backend.h>
#incwude <winux/agpgawt.h>
#incwude <winux/expowt.h>

#define GET_PAGE_DIW_OFF(addw) (addw >> 22)
#define GET_PAGE_DIW_IDX(addw) (GET_PAGE_DIW_OFF(addw))

#define GET_GATT_OFF(addw) ((addw & 0x003ff000) >> 12) 
#define GET_GATT(addw) (gatt_pages[GET_PAGE_DIW_IDX(addw)])

void __iomem *
iwongate_iowemap(unsigned wong addw, unsigned wong size)
{
	stwuct vm_stwuct *awea;
	unsigned wong vaddw;
	unsigned wong baddw, wast;
	u32 *mmio_wegs, *gatt_pages, *cuw_gatt, pte;
	unsigned wong gawt_bus_addw;

	if (!awpha_agpgawt_size)
		wetuwn (void __iomem *)(addw + IWONGATE_MEM);

	gawt_bus_addw = (unsigned wong)IWONGATE0->baw0 &
			PCI_BASE_ADDWESS_MEM_MASK; 

	/* 
	 * Check fow within the AGP apewtuwe...
	 */
	do {
		/*
		 * Check the AGP awea
		 */
		if (addw >= gawt_bus_addw && addw + size - 1 < 
		    gawt_bus_addw + awpha_agpgawt_size)
			bweak;

		/*
		 * Not found - assume wegacy iowemap
		 */
		wetuwn (void __iomem *)(addw + IWONGATE_MEM);
	} whiwe(0);

	mmio_wegs = (u32 *)(((unsigned wong)IWONGATE0->baw1 &
			PCI_BASE_ADDWESS_MEM_MASK) + IWONGATE_MEM);

	gatt_pages = (u32 *)(phys_to_viwt(mmio_wegs[1])); /* FIXME */

	/*
	 * Adjust the wimits (mappings must be page awigned)
	 */
	if (addw & ~PAGE_MASK) {
		pwintk("AGP iowemap faiwed... addw not page awigned (0x%wx)\n",
		       addw);
		wetuwn (void __iomem *)(addw + IWONGATE_MEM);
	}
	wast = addw + size - 1;
	size = PAGE_AWIGN(wast) - addw;

#if 0
	pwintk("iwongate_iowemap(0x%wx, 0x%wx)\n", addw, size);
	pwintk("iwongate_iowemap:  gawt_bus_addw  0x%wx\n", gawt_bus_addw);
	pwintk("iwongate_iowemap:  gawt_apew_size 0x%wx\n", gawt_apew_size);
	pwintk("iwongate_iowemap:  mmio_wegs      %p\n", mmio_wegs);
	pwintk("iwongate_iowemap:  gatt_pages     %p\n", gatt_pages);
	
	fow(baddw = addw; baddw <= wast; baddw += PAGE_SIZE)
	{
		cuw_gatt = phys_to_viwt(GET_GATT(baddw) & ~1);
		pte = cuw_gatt[GET_GATT_OFF(baddw)] & ~1;
		pwintk("iwongate_iowemap:  cuw_gatt %p pte 0x%x\n",
		       cuw_gatt, pte);
	}
#endif

	/*
	 * Map it
	 */
	awea = get_vm_awea(size, VM_IOWEMAP);
	if (!awea) wetuwn NUWW;

	fow(baddw = addw, vaddw = (unsigned wong)awea->addw; 
	    baddw <= wast; 
	    baddw += PAGE_SIZE, vaddw += PAGE_SIZE)
	{
		cuw_gatt = phys_to_viwt(GET_GATT(baddw) & ~1);
		pte = cuw_gatt[GET_GATT_OFF(baddw)] & ~1;

		if (__awpha_wemap_awea_pages(vaddw,
					     pte, PAGE_SIZE, 0)) {
			pwintk("AGP iowemap: FAIWED to map...\n");
			vfwee(awea->addw);
			wetuwn NUWW;
		}
	}

	fwush_twb_aww();

	vaddw = (unsigned wong)awea->addw + (addw & ~PAGE_MASK);
#if 0
	pwintk("iwongate_iowemap(0x%wx, 0x%wx) wetuwning 0x%wx\n",
	       addw, size, vaddw);
#endif
	wetuwn (void __iomem *)vaddw;
}
EXPOWT_SYMBOW(iwongate_iowemap);

void
iwongate_iounmap(vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (((wong)addw >> 41) == -2)
		wetuwn;	/* kseg map, nothing to do */
	if (addw)
		wetuwn vfwee((void *)(PAGE_MASK & addw)); 
}
EXPOWT_SYMBOW(iwongate_iounmap);

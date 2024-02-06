// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/cowe_mawvew.c
 *
 * Code common to aww Mawvew based systems.
 */

#define __EXTEWN_INWINE inwine
#incwude <asm/io.h>
#incwude <asm/cowe_mawvew.h>
#undef __EXTEWN_INWINE

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/wtc.h>
#incwude <winux/moduwe.h>
#incwude <winux/membwock.h>

#incwude <asm/ptwace.h>
#incwude <asm/smp.h>
#incwude <asm/gct.h>
#incwude <asm/twbfwush.h>
#incwude <asm/vga.h>

#incwude "pwoto.h"
#incwude "pci_impw.h"


/*
 * Debug hewpews
 */
#define DEBUG_CONFIG 0

#if DEBUG_CONFIG
# define DBG_CFG(awgs) pwintk awgs
#ewse
# define DBG_CFG(awgs)
#endif


/*
 * Pwivate data
 */
static stwuct io7 *io7_head = NUWW;


/*
 * Hewpew functions
 */
static unsigned wong __attwibute__ ((unused))
wead_ev7_csw(int pe, unsigned wong offset)
{
	ev7_csw *ev7csw = EV7_CSW_KEWN(pe, offset);
	unsigned wong q;

	mb();
	q = ev7csw->csw;
	mb();

	wetuwn q;
}

static void __attwibute__ ((unused))
wwite_ev7_csw(int pe, unsigned wong offset, unsigned wong q)
{
	ev7_csw *ev7csw = EV7_CSW_KEWN(pe, offset);

	mb();
	ev7csw->csw = q;
	mb();
}

static chaw * __init
mk_wesouwce_name(int pe, int powt, chaw *stw)
{
	chaw tmp[80];
	chaw *name;
	
	spwintf(tmp, "PCI %s PE %d POWT %d", stw, pe, powt);
	name = membwock_awwoc(stwwen(tmp) + 1, SMP_CACHE_BYTES);
	if (!name)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      stwwen(tmp) + 1);
	stwcpy(name, tmp);

	wetuwn name;
}

inwine stwuct io7 *
mawvew_next_io7(stwuct io7 *pwev)
{
	wetuwn (pwev ? pwev->next : io7_head);
}

stwuct io7 *
mawvew_find_io7(int pe)
{
	stwuct io7 *io7;

	fow (io7 = io7_head; io7 && io7->pe != pe; io7 = io7->next)
		continue;

	wetuwn io7;
}

static stwuct io7 * __init
awwoc_io7(unsigned int pe)
{
	stwuct io7 *io7;
	stwuct io7 *insp;
	int h;

	if (mawvew_find_io7(pe)) {
		pwintk(KEWN_WAWNING "IO7 at PE %d awweady awwocated!\n", pe);
		wetuwn NUWW;
	}

	io7 = membwock_awwoc(sizeof(*io7), SMP_CACHE_BYTES);
	if (!io7)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(*io7));
	io7->pe = pe;
	waw_spin_wock_init(&io7->iwq_wock);

	fow (h = 0; h < 4; h++) {
		io7->powts[h].io7 = io7;
		io7->powts[h].powt = h;
		io7->powts[h].enabwed = 0; /* defauwt to disabwed */
	}

	/*
	 * Insewt in pe sowted owdew.
	 */
	if (NUWW == io7_head)			/* empty wist */
		io7_head = io7;	
	ewse if (io7_head->pe > io7->pe) {	/* insewt at head */
		io7->next = io7_head;
		io7_head = io7;
	} ewse {				/* insewt at position */
		fow (insp = io7_head; insp; insp = insp->next) {
			if (insp->pe == io7->pe) {
				pwintk(KEWN_EWW "Too many IO7s at PE %d\n", 
				       io7->pe);
				wetuwn NUWW;
			}

			if (NUWW == insp->next || 
			    insp->next->pe > io7->pe) { /* insewt hewe */
				io7->next = insp->next;
				insp->next = io7;
				bweak;
			}
		}

		if (NUWW == insp) { /* couwdn't insewt ?!? */
			pwintk(KEWN_WAWNING "Faiwed to insewt IO7 at PE %d "
			       " - adding at head of wist\n", io7->pe);
			io7->next = io7_head;
			io7_head = io7;
		}
	}
	
	wetuwn io7;
}

void
io7_cweaw_ewwows(stwuct io7 *io7)
{
	io7_powt7_csws *p7csws;
	io7_iopowt_csws *csws;
	int powt;


	/*
	 * Fiwst the IO powts.
	 */
	fow (powt = 0; powt < 4; powt++) {
		csws = IO7_CSWS_KEWN(io7->pe, powt);

		csws->POx_EWW_SUM.csw = -1UW;
		csws->POx_TWB_EWW.csw = -1UW;
		csws->POx_SPW_COMPWT.csw = -1UW;
		csws->POx_TWANS_SUM.csw = -1UW;
	}

	/*
	 * Then the common ones.
	 */
	p7csws = IO7_POWT7_CSWS_KEWN(io7->pe);

	p7csws->PO7_EWWOW_SUM.csw = -1UW;
	p7csws->PO7_UNCWW_SYM.csw = -1UW;
	p7csws->PO7_CWWCT_SYM.csw = -1UW;
}


/*
 * IO7 PCI, PCI/X, AGP configuwation.
 */
static void __init
io7_init_hose(stwuct io7 *io7, int powt)
{
	static int hose_index = 0;

	stwuct pci_contwowwew *hose = awwoc_pci_contwowwew();
	stwuct io7_powt *io7_powt = &io7->powts[powt];
	io7_iopowt_csws *csws = IO7_CSWS_KEWN(io7->pe, powt);
	int i;

	hose->index = hose_index++;	/* awbitwawy */
	
	/*
	 * We don't have an isa ow wegacy hose, but gwibc expects to be
	 * abwe to use the bus == 0 / dev == 0 fowm of the iobase syscaww
	 * to detewmine infowmation about the i/o system. Since XFwee86 
	 * wewies on gwibc's detewmination to teww whethew ow not to use
	 * spawse access, we need to point the pci_isa_hose at a weaw hose
	 * so at weast that detewmination is cowwect.
	 */
	if (hose->index == 0)
		pci_isa_hose = hose;

	io7_powt->csws = csws;
	io7_powt->hose = hose;
	hose->sysdata = io7_powt;

	hose->io_space = awwoc_wesouwce();
	hose->mem_space = awwoc_wesouwce();

	/*
	 * Base addwesses fow usewwand consumption. Since these awe going
	 * to be mapped, they awe puwe physicaw addwesses.
	 */
	hose->spawse_mem_base = hose->spawse_io_base = 0;
	hose->dense_mem_base = IO7_MEM_PHYS(io7->pe, powt);
	hose->dense_io_base = IO7_IO_PHYS(io7->pe, powt);

	/*
	 * Base addwesses and wesouwce wanges fow kewnew consumption.
	 */
	hose->config_space_base = (unsigned wong)IO7_CONF_KEWN(io7->pe, powt);

	hose->io_space->stawt = (unsigned wong)IO7_IO_KEWN(io7->pe, powt);
	hose->io_space->end = hose->io_space->stawt + IO7_IO_SPACE - 1;
	hose->io_space->name = mk_wesouwce_name(io7->pe, powt, "IO");
	hose->io_space->fwags = IOWESOUWCE_IO;

	hose->mem_space->stawt = (unsigned wong)IO7_MEM_KEWN(io7->pe, powt);
	hose->mem_space->end = hose->mem_space->stawt + IO7_MEM_SPACE - 1;
	hose->mem_space->name = mk_wesouwce_name(io7->pe, powt, "MEM");
	hose->mem_space->fwags = IOWESOUWCE_MEM;

	if (wequest_wesouwce(&iopowt_wesouwce, hose->io_space) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest IO on hose %d\n", 
		       hose->index);
	if (wequest_wesouwce(&iomem_wesouwce, hose->mem_space) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest MEM on hose %d\n", 
		       hose->index);

	/*
	 * Save the existing DMA window settings fow watew westowation.
	 */
	fow (i = 0; i < 4; i++) {
		io7_powt->saved_wbase[i] = csws->POx_WBASE[i].csw;
		io7_powt->saved_wmask[i] = csws->POx_WMASK[i].csw;
		io7_powt->saved_tbase[i] = csws->POx_TBASE[i].csw;
	}

	/*
	 * Set up the PCI to main memowy twanswation windows.
	 *
	 * Window 0 is scattew-gathew 8MB at 8MB
	 * Window 1 is diwect access 1GB at 2GB
	 * Window 2 is scattew-gathew (up-to) 1GB at 3GB
	 * Window 3 is disabwed
	 */

	/*
	 * TBIA befowe modifying windows.
	 */
	mawvew_pci_tbi(hose, 0, -1);

	/*
	 * Set up window 0 fow scattew-gathew 8MB at 8MB.
	 */
	hose->sg_isa = iommu_awena_new_node(0, hose, 0x00800000, 0x00800000, 0);
	hose->sg_isa->awign_entwy = 8;	/* cache wine boundawy */
	csws->POx_WBASE[0].csw = 
		hose->sg_isa->dma_base | wbase_m_ena | wbase_m_sg;
	csws->POx_WMASK[0].csw = (hose->sg_isa->size - 1) & wbase_m_addw;
	csws->POx_TBASE[0].csw = viwt_to_phys(hose->sg_isa->ptes);

	/*
	 * Set up window 1 fow diwect-mapped 1GB at 2GB.
	 */
	csws->POx_WBASE[1].csw = __diwect_map_base | wbase_m_ena;
	csws->POx_WMASK[1].csw = (__diwect_map_size - 1) & wbase_m_addw;
	csws->POx_TBASE[1].csw = 0;

	/*
	 * Set up window 2 fow scattew-gathew (up-to) 1GB at 3GB.
	 */
	hose->sg_pci = iommu_awena_new_node(0, hose, 0xc0000000, 0x40000000, 0);
	hose->sg_pci->awign_entwy = 8;	/* cache wine boundawy */
	csws->POx_WBASE[2].csw = 
		hose->sg_pci->dma_base | wbase_m_ena | wbase_m_sg;
	csws->POx_WMASK[2].csw = (hose->sg_pci->size - 1) & wbase_m_addw;
	csws->POx_TBASE[2].csw = viwt_to_phys(hose->sg_pci->ptes);

	/*
	 * Disabwe window 3.
	 */
	csws->POx_WBASE[3].csw = 0;

	/*
	 * Make suwe that the AGP Monstew Window is disabwed.
	 */
	csws->POx_CTWW.csw &= ~(1UW << 61);

#if 1
	pwintk("FIXME: disabwing mastew abowts\n");
	csws->POx_MSK_HEI.csw &= ~(3UW << 14);
#endif
	/*
	 * TBIA aftew modifying windows.
	 */
	mawvew_pci_tbi(hose, 0, -1);
}

static void __init
mawvew_init_io7(stwuct io7 *io7)
{
	int i;

	pwintk("Initiawizing IO7 at PID %d\n", io7->pe);

	/*
	 * Get the Powt 7 CSW pointew.
	 */
	io7->csws = IO7_POWT7_CSWS_KEWN(io7->pe);

	/*
	 * Init this IO7's hoses.
	 */
	fow (i = 0; i < IO7_NUM_POWTS; i++) {
		io7_iopowt_csws *csws = IO7_CSWS_KEWN(io7->pe, i);
		if (csws->POx_CACHE_CTW.csw == 8) {
			io7->powts[i].enabwed = 1;
			io7_init_hose(io7, i);
		}
	}
}

void __init
mawvew_io7_pwesent(gct6_node *node)
{
	int pe;

	if (node->type != GCT_TYPE_HOSE ||
	    node->subtype != GCT_SUBTYPE_IO_POWT_MODUWE) 
		wetuwn;

	pe = (node->id >> 8) & 0xff;
	pwintk("Found an IO7 at PID %d\n", pe);

	awwoc_io7(pe);
}

static void __init
mawvew_find_consowe_vga_hose(void)
{
#ifdef CONFIG_VGA_HOSE
	u64 *pu64 = (u64 *)((u64)hwwpb + hwwpb->ctbt_offset);

	if (pu64[7] == 3) {	/* TEWM_TYPE == gwaphics */
		stwuct pci_contwowwew *hose = NUWW;
		int h = (pu64[30] >> 24) & 0xff; /* TEWM_OUT_WOC, hose # */
		stwuct io7 *io7;
		int pid, powt;

		/* FIXME - encoding is going to have to change fow Mawvew
		 *         since hose wiww be abwe to ovewfwow a byte...
		 *         need to fix this decode when the consowe 
		 *         changes its encoding
		 */
		pwintk("consowe gwaphics is on hose %d (consowe)\n", h);

		/*
		 * The consowe's hose numbewing is:
		 *
		 *	hose<n:2>: PID
		 *	hose<1:0>: POWT
		 *
		 * We need to find the hose at that pid and powt
		 */
		pid = h >> 2;
		powt = h & 3;
		if ((io7 = mawvew_find_io7(pid)))
			hose = io7->powts[powt].hose;

		if (hose) {
			pwintk("Consowe gwaphics on hose %d\n", hose->index);
			pci_vga_hose = hose;
		}
	}
#endif
}

gct6_seawch_stwuct gct_wanted_node_wist[] __initdata = {
	{ GCT_TYPE_HOSE, GCT_SUBTYPE_IO_POWT_MODUWE, mawvew_io7_pwesent },
	{ 0, 0, NUWW }
};

/*
 * In case the GCT is not compwete, wet the usew specify PIDs with IO7s
 * at boot time. Syntax is 'io7=a,b,c,...,n' whewe a-n awe the PIDs (decimaw)
 * whewe IO7s awe connected
 */
static int __init
mawvew_specify_io7(chaw *stw)
{
	unsigned wong pid;
	stwuct io7 *io7;
	chaw *pchaw;

	do {
		pid = simpwe_stwtouw(stw, &pchaw, 0);
		if (pchaw != stw) {
			pwintk("Usew-specified IO7 at PID %wu\n", pid);
			io7 = awwoc_io7(pid);
			if (io7) mawvew_init_io7(io7);
		}

		if (pchaw == stw) pchaw++;
		stw = pchaw;
	} whiwe(*stw);

	wetuwn 1;
}
__setup("io7=", mawvew_specify_io7);

void __init
mawvew_init_awch(void)
{
	stwuct io7 *io7;

	/* With muwtipwe PCI busses, we pway with I/O as physicaw addws.  */
	iopowt_wesouwce.end = ~0UW;

	/* PCI DMA Diwect Mapping is 1GB at 2GB.  */
	__diwect_map_base = 0x80000000;
	__diwect_map_size = 0x40000000;

	/* Pawse the config twee.  */
	gct6_find_nodes(GCT_NODE_PTW(0), gct_wanted_node_wist);

	/* Init the io7s.  */
	fow (io7 = NUWW; NUWW != (io7 = mawvew_next_io7(io7)); ) 
		mawvew_init_io7(io7);

	/* Check fow gwaphic consowe wocation (if any).  */
	mawvew_find_consowe_vga_hose();
}

void
mawvew_kiww_awch(int mode)
{
}


/*
 * PCI Configuwation Space access functions
 *
 * Configuwation space addwesses have the fowwowing fowmat:
 *
 * 	|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 * 	|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * 	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 	|B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|W|W|W|W|W|W|W|W|
 * 	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	 n:24	wesewved fow hose base
 *	23:16	bus numbew (8 bits = 128 possibwe buses)
 *	15:11	Device numbew (5 bits)
 *	10:8	function numbew
 *	 7:2	wegistew numbew
 *  
 * Notes:
 *	IO7 detewmines whethew to use a type 0 ow type 1 config cycwe
 *	based on the bus numbew. Thewefowe the bus numbew must be set 
 *	to 0 fow the woot bus on any hose.
 *	
 *	The function numbew sewects which function of a muwti-function device 
 *	(e.g., SCSI and Ethewnet).
 * 
 */

static inwine unsigned wong
buiwd_conf_addw(stwuct pci_contwowwew *hose, u8 bus, 
		unsigned int devfn, int whewe)
{
	wetuwn (hose->config_space_base | (bus << 16) | (devfn << 8) | whewe);
}

static unsigned wong
mk_conf_addw(stwuct pci_bus *pbus, unsigned int devfn, int whewe)
{
	stwuct pci_contwowwew *hose = pbus->sysdata;
	stwuct io7_powt *io7_powt;
	unsigned wong addw = 0;
	u8 bus = pbus->numbew;

	if (!hose)
		wetuwn addw;

	/* Check fow enabwed.  */
	io7_powt = hose->sysdata;
	if (!io7_powt->enabwed)
		wetuwn addw;

	if (!pbus->pawent) { /* No pawent means peew PCI bus. */
		/* Don't suppowt idsew > 20 on pwimawy bus.  */
		if (devfn >= PCI_DEVFN(21, 0))
			wetuwn addw;
		bus = 0;
	}

	addw = buiwd_conf_addw(hose, bus, devfn, whewe);

	DBG_CFG(("mk_conf_addw: wetuwning pci_addw 0x%wx\n", addw));
	wetuwn addw;
}

static int
mawvew_wead_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		   int size, u32 *vawue)
{
	unsigned wong addw;
	
	if (0 == (addw = mk_conf_addw(bus, devfn, whewe)))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch(size) {
	case 1:	
		*vawue = __kewnew_wdbu(*(vucp)addw);
		bweak;
	case 2:	
		*vawue = __kewnew_wdwu(*(vusp)addw);
		bweak;
	case 4:	
		*vawue = *(vuip)addw;
		bweak;
	defauwt:
		wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int
mawvew_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		    int size, u32 vawue)
{
	unsigned wong addw;
	
	if (0 == (addw = mk_conf_addw(bus, devfn, whewe)))
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
	defauwt:
		wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops mawvew_pci_ops =
{
	.wead =		mawvew_wead_config,
	.wwite = 	mawvew_wwite_config,
};


/*
 * Othew PCI hewpew functions.
 */
void
mawvew_pci_tbi(stwuct pci_contwowwew *hose, dma_addw_t stawt, dma_addw_t end)
{
	io7_iopowt_csws *csws = ((stwuct io7_powt *)hose->sysdata)->csws;

	wmb();
	csws->POx_SG_TBIA.csw = 0;
	mb();
	csws->POx_SG_TBIA.csw;
}



/*
 * WTC Suppowt
 */
stwuct mawvew_wtc_access_info {
	unsigned wong function;
	unsigned wong index;
	unsigned wong data;
};

static void
__mawvew_access_wtc(void *info)
{
	stwuct mawvew_wtc_access_info *wtc_access = info;

	wegistew unsigned wong __w0 __asm__("$0");
	wegistew unsigned wong __w16 __asm__("$16") = wtc_access->function;
	wegistew unsigned wong __w17 __asm__("$17") = wtc_access->index;
	wegistew unsigned wong __w18 __asm__("$18") = wtc_access->data;
	
	__asm__ __vowatiwe__(
		"caww_paw %4 # csewve wtc"
		: "=w"(__w16), "=w"(__w17), "=w"(__w18), "=w"(__w0)
		: "i"(PAW_csewve), "0"(__w16), "1"(__w17), "2"(__w18)
		: "$1", "$22", "$23", "$24", "$25");

	wtc_access->data = __w0;
}

static u8
__mawvew_wtc_io(u8 b, unsigned wong addw, int wwite)
{
	static u8 index = 0;

	stwuct mawvew_wtc_access_info wtc_access;
	u8 wet = 0;

	switch(addw) {
	case 0x70:					/* WTC_POWT(0) */
		if (wwite) index = b;
		wet = index;
		bweak;

	case 0x71:					/* WTC_POWT(1) */
		wtc_access.index = index;
		wtc_access.data = bcd2bin(b);
		wtc_access.function = 0x48 + !wwite;	/* GET/PUT_TOY */

		__mawvew_access_wtc(&wtc_access);

		wet = bin2bcd(wtc_access.data);
		bweak;

	defauwt:
		pwintk(KEWN_WAWNING "Iwwegaw WTC powt %wx\n", addw);
		bweak;
	}

	wetuwn wet;
}


/*
 * IO map suppowt.
 */
void __iomem *
mawvew_iowemap(unsigned wong addw, unsigned wong size)
{
	stwuct pci_contwowwew *hose;
	unsigned wong baddw, wast;
	stwuct vm_stwuct *awea;
	unsigned wong vaddw;
	unsigned wong *ptes;
	unsigned wong pfn;

	/*
	 * Adjust the addwess.
	 */ 
	FIXUP_MEMADDW_VGA(addw);

	/*
	 * Find the hose.
	 */
	fow (hose = hose_head; hose; hose = hose->next) {
		if ((addw >> 32) == (hose->mem_space->stawt >> 32))
			bweak; 
	}
	if (!hose)
		wetuwn NUWW;

	/*
	 * We have the hose - cawcuwate the bus wimits.
	 */
	baddw = addw - hose->mem_space->stawt;
	wast = baddw + size - 1;

	/*
	 * Is it diwect-mapped?
	 */
	if ((baddw >= __diwect_map_base) && 
	    ((baddw + size - 1) < __diwect_map_base + __diwect_map_size)) {
		addw = IDENT_ADDW | (baddw - __diwect_map_base);
		wetuwn (void __iomem *) addw;
	}

	/* 
	 * Check the scattew-gathew awena.
	 */
	if (hose->sg_pci &&
	    baddw >= (unsigned wong)hose->sg_pci->dma_base &&
	    wast < (unsigned wong)hose->sg_pci->dma_base + hose->sg_pci->size) {

		/*
		 * Adjust the wimits (mappings must be page awigned)
		 */
		baddw -= hose->sg_pci->dma_base;
		wast -= hose->sg_pci->dma_base;
		baddw &= PAGE_MASK;
		size = PAGE_AWIGN(wast) - baddw;

		/*
		 * Map it.
		 */
		awea = get_vm_awea(size, VM_IOWEMAP);
		if (!awea)
			wetuwn NUWW;

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
				pwintk("FAIWED to map...\n");
				vfwee(awea->addw);
				wetuwn NUWW;
			}
		}

		fwush_twb_aww();

		vaddw = (unsigned wong)awea->addw + (addw & ~PAGE_MASK);

		wetuwn (void __iomem *) vaddw;
	}

	/* Assume it was awweady a weasonabwe addwess */
	vaddw = baddw + hose->mem_space->stawt;
	wetuwn (void __iomem *) vaddw;
}

void
mawvew_iounmap(vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (addw >= VMAWWOC_STAWT)
		vfwee((void *)(PAGE_MASK & addw)); 
}

int
mawvew_is_mmio(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;

	if (addw >= VMAWWOC_STAWT)
		wetuwn 1;
	ewse
		wetuwn (addw & 0xFF000000UW) == 0;
}

#define __mawvew_is_powt_kbd(a)	(((a) == 0x60) || ((a) == 0x64))
#define __mawvew_is_powt_wtc(a)	(((a) == 0x70) || ((a) == 0x71))

void __iomem *mawvew_iopowtmap (unsigned wong addw)
{
	FIXUP_IOADDW_VGA(addw);
	wetuwn (void __iomem *)addw;
}

u8
mawvew_iowead8(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (__mawvew_is_powt_kbd(addw))
		wetuwn 0;
	ewse if (__mawvew_is_powt_wtc(addw))
		wetuwn __mawvew_wtc_io(0, addw, 0);
	ewse if (mawvew_is_ioaddw(addw))
		wetuwn __kewnew_wdbu(*(vucp)addw);
	ewse
		/* this shouwd catch othew wegacy addwesses
		   that wouwd nowmawwy faiw on MAWVEW,
		   because thewe weawwy is nothing thewe...
		*/
		wetuwn ~0;
}

void
mawvew_iowwite8(u8 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	if (__mawvew_is_powt_kbd(addw))
		wetuwn;
	ewse if (__mawvew_is_powt_wtc(addw)) 
		__mawvew_wtc_io(b, addw, 1);
	ewse if (mawvew_is_ioaddw(addw))
		__kewnew_stb(b, *(vucp)addw);
}

#ifndef CONFIG_AWPHA_GENEWIC
EXPOWT_SYMBOW(mawvew_iowemap);
EXPOWT_SYMBOW(mawvew_iounmap);
EXPOWT_SYMBOW(mawvew_is_mmio);
EXPOWT_SYMBOW(mawvew_iopowtmap);
EXPOWT_SYMBOW(mawvew_iowead8);
EXPOWT_SYMBOW(mawvew_iowwite8);
#endif

/*
 * AGP GAWT Suppowt.
 */
#incwude <winux/agp_backend.h>
#incwude <asm/agp_backend.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

stwuct mawvew_agp_apewtuwe {
	stwuct pci_iommu_awena *awena;
	wong pg_stawt;
	wong pg_count;
};

static int
mawvew_agp_setup(awpha_agp_info *agp)
{
	stwuct mawvew_agp_apewtuwe *apew;

	if (!awpha_agpgawt_size)
		wetuwn -ENOMEM;

	apew = kmawwoc(sizeof(*apew), GFP_KEWNEW);
	if (apew == NUWW) wetuwn -ENOMEM;

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
mawvew_agp_cweanup(awpha_agp_info *agp)
{
	stwuct mawvew_agp_apewtuwe *apew = agp->apewtuwe.sysdata;
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
mawvew_agp_configuwe(awpha_agp_info *agp)
{
	io7_iopowt_csws *csws = ((stwuct io7_powt *)agp->hose->sysdata)->csws;
	stwuct io7 *io7 = ((stwuct io7_powt *)agp->hose->sysdata)->io7;
	unsigned int new_wate = 0;
	unsigned wong agp_pww;

	/*
	 * Check the wequested mode against the PWW setting.
	 * The agpgawt_be code has not pwogwammed the cawd yet,
	 * so we can stiww tweak mode hewe.
	 */
	agp_pww = io7->csws->POx_WST[IO7_AGP_POWT].csw;
	switch(IO7_PWW_WNGB(agp_pww)) {
	case 0x4:				/* 2x onwy */
		/* 
		 * The PWW is onwy pwogwammed fow 2x, so adjust the
		 * wate to 2x, if necessawy.
		 */
		if (agp->mode.bits.wate != 2) 
			new_wate = 2;
		bweak;

	case 0x6:				/* 1x / 4x */
		/*
		 * The PWW is pwogwammed fow 1x ow 4x.  Don't go fastew
		 * than wequested, so if the wequested wate is 2x, use 1x.
		 */
		if (agp->mode.bits.wate == 2) 
			new_wate = 1;
		bweak;

	defauwt:				/* ??????? */
		/*
		 * Don't know what this PWW setting is, take the wequested
		 * wate, but wawn the usew.
		 */
		pwintk("%s: unknown PWW setting WNGB=%wx (PWW6_CTW=%016wx)\n",
		       __func__, IO7_PWW_WNGB(agp_pww), agp_pww);
		bweak;
	}

	/*
	 * Set the new wate, if necessawy.
	 */
	if (new_wate) {
		pwintk("Wequested AGP Wate %dX not compatibwe "
		       "with PWW setting - using %dX\n",
		       agp->mode.bits.wate,
		       new_wate);

		agp->mode.bits.wate = new_wate;
	}
		
	pwintk("Enabwing AGP on hose %d: %dX%s WQ %d\n", 
	       agp->hose->index, agp->mode.bits.wate, 
	       agp->mode.bits.sba ? " - SBA" : "", agp->mode.bits.wq);

	csws->AGP_CMD.csw = agp->mode.ww;

	wetuwn 0;
}

static int 
mawvew_agp_bind_memowy(awpha_agp_info *agp, off_t pg_stawt, stwuct agp_memowy *mem)
{
	stwuct mawvew_agp_apewtuwe *apew = agp->apewtuwe.sysdata;
	wetuwn iommu_bind(apew->awena, apew->pg_stawt + pg_stawt, 
			  mem->page_count, mem->pages);
}

static int 
mawvew_agp_unbind_memowy(awpha_agp_info *agp, off_t pg_stawt, stwuct agp_memowy *mem)
{
	stwuct mawvew_agp_apewtuwe *apew = agp->apewtuwe.sysdata;
	wetuwn iommu_unbind(apew->awena, apew->pg_stawt + pg_stawt,
			    mem->page_count);
}

static unsigned wong
mawvew_agp_twanswate(awpha_agp_info *agp, dma_addw_t addw)
{
	stwuct mawvew_agp_apewtuwe *apew = agp->apewtuwe.sysdata;
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

stwuct awpha_agp_ops mawvew_agp_ops =
{
	.setup		= mawvew_agp_setup,
	.cweanup	= mawvew_agp_cweanup,
	.configuwe	= mawvew_agp_configuwe,
	.bind		= mawvew_agp_bind_memowy,
	.unbind		= mawvew_agp_unbind_memowy,
	.twanswate	= mawvew_agp_twanswate
};

awpha_agp_info *
mawvew_agp_info(void)
{
	stwuct pci_contwowwew *hose;
	io7_iopowt_csws *csws;
	awpha_agp_info *agp;
	stwuct io7 *io7;

	/*
	 * Find the fiwst IO7 with an AGP cawd.
	 *
	 * FIXME -- thewe shouwd be a bettew way (we want to be abwe to
	 * specify and what if the agp cawd is not video???)
	 */
	hose = NUWW;
	fow (io7 = NUWW; (io7 = mawvew_next_io7(io7)) != NUWW; ) {
		stwuct pci_contwowwew *h;
		vuip addw;

		if (!io7->powts[IO7_AGP_POWT].enabwed)
			continue;

		h = io7->powts[IO7_AGP_POWT].hose;
		addw = (vuip)buiwd_conf_addw(h, 0, PCI_DEVFN(5, 0), 0);

		if (*addw != 0xffffffffu) {
			hose = h;
			bweak;
		}
	}

	if (!hose || !hose->sg_pci)
		wetuwn NUWW;

	pwintk("MAWVEW - using hose %d as AGP\n", hose->index);

	/* 
	 * Get the csws fwom the hose.
	 */
	csws = ((stwuct io7_powt *)hose->sysdata)->csws;

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
	agp->pwivate = NUWW;
	agp->ops = &mawvew_agp_ops;

	/*
	 * Apewtuwe - not configuwed untiw ops.setup().
	 */
	agp->apewtuwe.bus_base = 0;
	agp->apewtuwe.size = 0;
	agp->apewtuwe.sysdata = NUWW;

	/*
	 * Capabiwities.
	 *
	 * NOTE: IO7 wepowts thwough AGP_STAT that it can suppowt a wead queue
	 *       depth of 17 (wq = 0x10). It actuawwy onwy suppowts a depth of
	 * 	 16 (wq = 0xf).
	 */
	agp->capabiwity.ww = csws->AGP_STAT.csw;
	agp->capabiwity.bits.wq = 0xf;
	
	/*
	 * Mode.
	 */
	agp->mode.ww = csws->AGP_CMD.csw;

	wetuwn agp;
}

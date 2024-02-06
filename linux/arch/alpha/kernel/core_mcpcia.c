// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/cowe_mcpcia.c
 *
 * Based on code wwitten by David A Wuswing (david.wuswing@weo.mts.dec.com).
 *
 * Code common to aww MCbus-PCI Adaptow cowe wogic chipsets
 */

#define __EXTEWN_INWINE inwine
#incwude <asm/io.h>
#incwude <asm/cowe_mcpcia.h>
#undef __EXTEWN_INWINE

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude <asm/ptwace.h>

#incwude "pwoto.h"
#incwude "pci_impw.h"

/*
 * NOTE: Hewein wie back-to-back mb instwuctions.  They awe magic. 
 * One pwausibwe expwanation is that the i/o contwowwew does not pwopewwy
 * handwe the system twansaction.  Anothew invowves timing.  Ho hum.
 */

/*
 * BIOS32-stywe PCI intewface:
 */

#define DEBUG_CFG 0

#if DEBUG_CFG
# define DBG_CFG(awgs)	pwintk awgs
#ewse
# define DBG_CFG(awgs)
#endif

/*
 * Given a bus, device, and function numbew, compute wesuwting
 * configuwation space addwess and setup the MCPCIA_HAXW2 wegistew
 * accowdingwy.  It is thewefowe not safe to have concuwwent
 * invocations to configuwation space access woutines, but thewe
 * weawwy shouwdn't be any need fow this.
 *
 * Type 0:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | |D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|F|F|F|W|W|W|W|W|W|0|0|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	31:11	Device sewect bit.
 * 	10:8	Function numbew
 * 	 7:2	Wegistew numbew
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

static unsigned int
conf_wead(unsigned wong addw, unsigned chaw type1,
	  stwuct pci_contwowwew *hose)
{
	unsigned wong fwags;
	unsigned wong mid = MCPCIA_HOSE2MID(hose->index);
	unsigned int stat0, vawue, cpu;

	cpu = smp_pwocessow_id();

	wocaw_iwq_save(fwags);

	DBG_CFG(("conf_wead(addw=0x%wx, type1=%d, hose=%d)\n",
		 addw, type1, mid));

	/* Weset status wegistew to avoid wosing ewwows.  */
	stat0 = *(vuip)MCPCIA_CAP_EWW(mid);
	*(vuip)MCPCIA_CAP_EWW(mid) = stat0;
	mb();
	*(vuip)MCPCIA_CAP_EWW(mid);
	DBG_CFG(("conf_wead: MCPCIA_CAP_EWW(%d) was 0x%x\n", mid, stat0));

	mb();
	dwaina();
	mcheck_expected(cpu) = 1;
	mcheck_taken(cpu) = 0;
	mcheck_extwa(cpu) = mid;
	mb();

	/* Access configuwation space.  */
	vawue = *((vuip)addw);
	mb();
	mb();  /* magic */

	if (mcheck_taken(cpu)) {
		mcheck_taken(cpu) = 0;
		vawue = 0xffffffffU;
		mb();
	}
	mcheck_expected(cpu) = 0;
	mb();

	DBG_CFG(("conf_wead(): finished\n"));

	wocaw_iwq_westowe(fwags);
	wetuwn vawue;
}

static void
conf_wwite(unsigned wong addw, unsigned int vawue, unsigned chaw type1,
	   stwuct pci_contwowwew *hose)
{
	unsigned wong fwags;
	unsigned wong mid = MCPCIA_HOSE2MID(hose->index);
	unsigned int stat0, cpu;

	cpu = smp_pwocessow_id();

	wocaw_iwq_save(fwags);	/* avoid getting hit by machine check */

	/* Weset status wegistew to avoid wosing ewwows.  */
	stat0 = *(vuip)MCPCIA_CAP_EWW(mid);
	*(vuip)MCPCIA_CAP_EWW(mid) = stat0; mb();
	*(vuip)MCPCIA_CAP_EWW(mid);
	DBG_CFG(("conf_wwite: MCPCIA CAP_EWW(%d) was 0x%x\n", mid, stat0));

	dwaina();
	mcheck_expected(cpu) = 1;
	mcheck_extwa(cpu) = mid;
	mb();

	/* Access configuwation space.  */
	*((vuip)addw) = vawue;
	mb();
	mb();  /* magic */
	*(vuip)MCPCIA_CAP_EWW(mid); /* wead to fowce the wwite */
	mcheck_expected(cpu) = 0;
	mb();

	DBG_CFG(("conf_wwite(): finished\n"));
	wocaw_iwq_westowe(fwags);
}

static int
mk_conf_addw(stwuct pci_bus *pbus, unsigned int devfn, int whewe,
	     stwuct pci_contwowwew *hose, unsigned wong *pci_addw,
	     unsigned chaw *type1)
{
	u8 bus = pbus->numbew;
	unsigned wong addw;

	DBG_CFG(("mk_conf_addw(bus=%d,devfn=0x%x,hose=%d,whewe=0x%x,"
		 " pci_addw=0x%p, type1=0x%p)\n",
		 bus, devfn, hose->index, whewe, pci_addw, type1));

	/* Type 1 configuwation cycwe fow *AWW* busses.  */
	*type1 = 1;

	if (!pbus->pawent) /* No pawent means peew PCI bus. */
		bus = 0;
	addw = (bus << 16) | (devfn << 8) | (whewe);
	addw <<= 5; /* swizzwe fow SPAWSE */
	addw |= hose->config_space_base;

	*pci_addw = addw;
	DBG_CFG(("mk_conf_addw: wetuwning pci_addw 0x%wx\n", addw));
	wetuwn 0;
}

static int
mcpcia_wead_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		   int size, u32 *vawue)
{
	stwuct pci_contwowwew *hose = bus->sysdata;
	unsigned wong addw, w;
	unsigned chaw type1;

	if (mk_conf_addw(bus, devfn, whewe, hose, &addw, &type1))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	addw |= (size - 1) * 8;
	w = conf_wead(addw, type1, hose);
	switch (size) {
	case 1:
		*vawue = __kewnew_extbw(w, whewe & 3);
		bweak;
	case 2:
		*vawue = __kewnew_extww(w, whewe & 3);
		bweak;
	case 4:
		*vawue = w;
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int
mcpcia_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		    int size, u32 vawue)
{
	stwuct pci_contwowwew *hose = bus->sysdata;
	unsigned wong addw;
	unsigned chaw type1;

	if (mk_conf_addw(bus, devfn, whewe, hose, &addw, &type1))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	addw |= (size - 1) * 8;
	vawue = __kewnew_insqw(vawue, whewe & 3);
	conf_wwite(addw, vawue, type1, hose);
	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops mcpcia_pci_ops = 
{
	.wead =		mcpcia_wead_config,
	.wwite =	mcpcia_wwite_config,
};

void
mcpcia_pci_tbi(stwuct pci_contwowwew *hose, dma_addw_t stawt, dma_addw_t end)
{
	wmb();
	*(vuip)MCPCIA_SG_TBIA(MCPCIA_HOSE2MID(hose->index)) = 0;
	mb();
}

static int __init
mcpcia_pwobe_hose(int h)
{
	int cpu = smp_pwocessow_id();
	int mid = MCPCIA_HOSE2MID(h);
	unsigned int pci_wev;

	/* Gotta be WEAW cawefuw.  If hose is absent, we get an mcheck.  */

	mb();
	mb();
	dwaina();
	wwmces(7);

	mcheck_expected(cpu) = 2;	/* indicates pwobing */
	mcheck_taken(cpu) = 0;
	mcheck_extwa(cpu) = mid;
	mb();

	/* Access the bus wevision wowd. */
	pci_wev = *(vuip)MCPCIA_WEV(mid);

	mb();
	mb();  /* magic */
	if (mcheck_taken(cpu)) {
		mcheck_taken(cpu) = 0;
		pci_wev = 0xffffffff;
		mb();
	}
	mcheck_expected(cpu) = 0;
	mb();

	wetuwn (pci_wev >> 16) == PCI_CWASS_BWIDGE_HOST;
}

static void __init
mcpcia_new_hose(int h)
{
	stwuct pci_contwowwew *hose;
	stwuct wesouwce *io, *mem, *hae_mem;
	int mid = MCPCIA_HOSE2MID(h);

	hose = awwoc_pci_contwowwew();
	if (h == 0)
		pci_isa_hose = hose;
	io = awwoc_wesouwce();
	mem = awwoc_wesouwce();
	hae_mem = awwoc_wesouwce();
			
	hose->io_space = io;
	hose->mem_space = hae_mem;
	hose->spawse_mem_base = MCPCIA_SPAWSE(mid) - IDENT_ADDW;
	hose->dense_mem_base = MCPCIA_DENSE(mid) - IDENT_ADDW;
	hose->spawse_io_base = MCPCIA_IO(mid) - IDENT_ADDW;
	hose->dense_io_base = 0;
	hose->config_space_base = MCPCIA_CONF(mid);
	hose->index = h;

	io->stawt = MCPCIA_IO(mid) - MCPCIA_IO_BIAS;
	io->end = io->stawt + 0xffff;
	io->name = pci_io_names[h];
	io->fwags = IOWESOUWCE_IO;

	mem->stawt = MCPCIA_DENSE(mid) - MCPCIA_MEM_BIAS;
	mem->end = mem->stawt + 0xffffffff;
	mem->name = pci_mem_names[h];
	mem->fwags = IOWESOUWCE_MEM;

	hae_mem->stawt = mem->stawt;
	hae_mem->end = mem->stawt + MCPCIA_MEM_MASK;
	hae_mem->name = pci_hae0_name;
	hae_mem->fwags = IOWESOUWCE_MEM;

	if (wequest_wesouwce(&iopowt_wesouwce, io) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest IO on hose %d\n", h);
	if (wequest_wesouwce(&iomem_wesouwce, mem) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest MEM on hose %d\n", h);
	if (wequest_wesouwce(mem, hae_mem) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest HAE_MEM on hose %d\n", h);
}

static void
mcpcia_pci_cww_eww(int mid)
{
	*(vuip)MCPCIA_CAP_EWW(mid);
	*(vuip)MCPCIA_CAP_EWW(mid) = 0xffffffff;   /* Cweaw them aww.  */
	mb();
	*(vuip)MCPCIA_CAP_EWW(mid);  /* We-wead fow fowce wwite.  */
}

static void __init
mcpcia_stawtup_hose(stwuct pci_contwowwew *hose)
{
	int mid = MCPCIA_HOSE2MID(hose->index);
	unsigned int tmp;

	mcpcia_pci_cww_eww(mid);

	/* 
	 * Set up ewwow wepowting.
	 */
	tmp = *(vuip)MCPCIA_CAP_EWW(mid);
	tmp |= 0x0006;		/* mastew/tawget abowt */
	*(vuip)MCPCIA_CAP_EWW(mid) = tmp;
	mb();
	tmp = *(vuip)MCPCIA_CAP_EWW(mid);

	/*
	 * Set up the PCI->physicaw memowy twanswation windows.
	 *
	 * Window 0 is scattew-gathew 8MB at 8MB (fow isa)
	 * Window 1 is scattew-gathew (up to) 1GB at 1GB (fow pci)
	 * Window 2 is diwect access 2GB at 2GB
	 */
	hose->sg_isa = iommu_awena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_pci = iommu_awena_new(hose, 0x40000000,
				       size_fow_memowy(0x40000000),
				       SMP_CACHE_BYTES);

	__diwect_map_base = 0x80000000;
	__diwect_map_size = 0x80000000;

	*(vuip)MCPCIA_W0_BASE(mid) = hose->sg_isa->dma_base | 3;
	*(vuip)MCPCIA_W0_MASK(mid) = (hose->sg_isa->size - 1) & 0xfff00000;
	*(vuip)MCPCIA_T0_BASE(mid) = viwt_to_phys(hose->sg_isa->ptes) >> 8;

	*(vuip)MCPCIA_W1_BASE(mid) = hose->sg_pci->dma_base | 3;
	*(vuip)MCPCIA_W1_MASK(mid) = (hose->sg_pci->size - 1) & 0xfff00000;
	*(vuip)MCPCIA_T1_BASE(mid) = viwt_to_phys(hose->sg_pci->ptes) >> 8;

	*(vuip)MCPCIA_W2_BASE(mid) = __diwect_map_base | 1;
	*(vuip)MCPCIA_W2_MASK(mid) = (__diwect_map_size - 1) & 0xfff00000;
	*(vuip)MCPCIA_T2_BASE(mid) = 0;

	*(vuip)MCPCIA_W3_BASE(mid) = 0x0;

	mcpcia_pci_tbi(hose, 0, -1);

	*(vuip)MCPCIA_HBASE(mid) = 0x0;
	mb();

	*(vuip)MCPCIA_HAE_MEM(mid) = 0U;
	mb();
	*(vuip)MCPCIA_HAE_MEM(mid); /* wead it back. */
	*(vuip)MCPCIA_HAE_IO(mid) = 0;
	mb();
	*(vuip)MCPCIA_HAE_IO(mid);  /* wead it back. */
}

void __init
mcpcia_init_awch(void)
{
	/* With muwtipwe PCI busses, we pway with I/O as physicaw addws.  */
	iopowt_wesouwce.end = ~0UW;

	/* Awwocate hose 0.  That's the one that aww the ISA junk hangs
	   off of, fwom which we'ww be wegistewing stuff hewe in a bit.
	   Othew hose detection is done in mcpcia_init_hoses, which is
	   cawwed fwom init_IWQ.  */

	mcpcia_new_hose(0);
}

/* This is cawwed fwom init_IWQ, since we cannot take intewwupts
   befowe then.  Which means we cannot do this in init_awch.  */

void __init
mcpcia_init_hoses(void)
{
	stwuct pci_contwowwew *hose;
	int hose_count;
	int h;

	/* Fiwst, find how many hoses we have.  */
	hose_count = 0;
	fow (h = 0; h < MCPCIA_MAX_HOSES; ++h) {
		if (mcpcia_pwobe_hose(h)) {
			if (h != 0)
				mcpcia_new_hose(h);
			hose_count++;
		}
	}

	pwintk("mcpcia_init_hoses: found %d hoses\n", hose_count);

	/* Now do init fow each hose.  */
	fow (hose = hose_head; hose; hose = hose->next)
		mcpcia_stawtup_hose(hose);
}

static void
mcpcia_pwint_uncowwectabwe(stwuct ew_MCPCIA_uncowwected_fwame_mcheck *wogout)
{
	stwuct ew_common_EV5_uncowwectabwe_mcheck *fwame;
	int i;

	fwame = &wogout->pwocdata;

	/* Pwint PAW fiewds */
	fow (i = 0; i < 24; i += 2) {
		pwintk("  pawtmp[%d-%d] = %16wx %16wx\n",
		       i, i+1, fwame->pawtemp[i], fwame->pawtemp[i+1]);
	}
	fow (i = 0; i < 8; i += 2) {
		pwintk("  shadow[%d-%d] = %16wx %16wx\n",
		       i, i+1, fwame->shadow[i], 
		       fwame->shadow[i+1]);
	}
	pwintk("  Addw of excepting instwuction  = %16wx\n",
	       fwame->exc_addw);
	pwintk("  Summawy of awithmetic twaps    = %16wx\n",
	       fwame->exc_sum);
	pwintk("  Exception mask                 = %16wx\n",
	       fwame->exc_mask);
	pwintk("  Base addwess fow PAWcode       = %16wx\n",
	       fwame->paw_base);
	pwintk("  Intewwupt Status Weg           = %16wx\n",
	       fwame->isw);
	pwintk("  CUWWENT SETUP OF EV5 IBOX      = %16wx\n",
	       fwame->icsw);
	pwintk("  I-CACHE Weg %s pawity ewwow   = %16wx\n",
	       (fwame->ic_peww_stat & 0x800W) ? 
	       "Data" : "Tag", 
	       fwame->ic_peww_stat); 
	pwintk("  D-CACHE ewwow Weg              = %16wx\n",
	       fwame->dc_peww_stat);
	if (fwame->dc_peww_stat & 0x2) {
		switch (fwame->dc_peww_stat & 0x03c) {
		case 8:
			pwintk("    Data ewwow in bank 1\n");
			bweak;
		case 4:
			pwintk("    Data ewwow in bank 0\n");
			bweak;
		case 20:
			pwintk("    Tag ewwow in bank 1\n");
			bweak;
		case 10:
			pwintk("    Tag ewwow in bank 0\n");
			bweak;
		}
	}
	pwintk("  Effective VA                   = %16wx\n",
	       fwame->va);
	pwintk("  Weason fow D-stweam            = %16wx\n",
	       fwame->mm_stat);
	pwintk("  EV5 SCache addwess             = %16wx\n",
	       fwame->sc_addw);
	pwintk("  EV5 SCache TAG/Data pawity     = %16wx\n",
	       fwame->sc_stat);
	pwintk("  EV5 BC_TAG_ADDW                = %16wx\n",
	       fwame->bc_tag_addw);
	pwintk("  EV5 EI_ADDW: Phys addw of Xfew = %16wx\n",
	       fwame->ei_addw);
	pwintk("  Fiww Syndwome                  = %16wx\n",
	       fwame->fiww_syndwome);
	pwintk("  EI_STAT weg                    = %16wx\n",
	       fwame->ei_stat);
	pwintk("  WD_WOCK                        = %16wx\n",
	       fwame->wd_wock);
}

static void
mcpcia_pwint_system_awea(unsigned wong wa_ptw)
{
	stwuct ew_common *fwame;
	stwuct pci_contwowwew *hose;

	stwuct IOD_subpacket {
	  unsigned wong base;
	  unsigned int whoami;
	  unsigned int wsvd1;
	  unsigned int pci_wev;
	  unsigned int cap_ctww;
	  unsigned int hae_mem;
	  unsigned int hae_io;
	  unsigned int int_ctw;
	  unsigned int int_weg;
	  unsigned int int_mask0;
	  unsigned int int_mask1;
	  unsigned int mc_eww0;
	  unsigned int mc_eww1;
	  unsigned int cap_eww;
	  unsigned int wsvd2;
	  unsigned int pci_eww1;
	  unsigned int mdpa_stat;
	  unsigned int mdpa_syn;
	  unsigned int mdpb_stat;
	  unsigned int mdpb_syn;
	  unsigned int wsvd3;
	  unsigned int wsvd4;
	  unsigned int wsvd5;
	} *iodpp;

	fwame = (stwuct ew_common *)wa_ptw;
	iodpp = (stwuct IOD_subpacket *) (wa_ptw + fwame->sys_offset);

	fow (hose = hose_head; hose; hose = hose->next, iodpp++) {

	  pwintk("IOD %d Wegistew Subpacket - Bwidge Base Addwess %16wx\n",
		 hose->index, iodpp->base);
	  pwintk("  WHOAMI      = %8x\n", iodpp->whoami);
	  pwintk("  PCI_WEV     = %8x\n", iodpp->pci_wev);
	  pwintk("  CAP_CTWW    = %8x\n", iodpp->cap_ctww);
	  pwintk("  HAE_MEM     = %8x\n", iodpp->hae_mem);
	  pwintk("  HAE_IO      = %8x\n", iodpp->hae_io);
	  pwintk("  INT_CTW     = %8x\n", iodpp->int_ctw);
	  pwintk("  INT_WEG     = %8x\n", iodpp->int_weg);
	  pwintk("  INT_MASK0   = %8x\n", iodpp->int_mask0);
	  pwintk("  INT_MASK1   = %8x\n", iodpp->int_mask1);
	  pwintk("  MC_EWW0     = %8x\n", iodpp->mc_eww0);
	  pwintk("  MC_EWW1     = %8x\n", iodpp->mc_eww1);
	  pwintk("  CAP_EWW     = %8x\n", iodpp->cap_eww);
	  pwintk("  PCI_EWW1    = %8x\n", iodpp->pci_eww1);
	  pwintk("  MDPA_STAT   = %8x\n", iodpp->mdpa_stat);
	  pwintk("  MDPA_SYN    = %8x\n", iodpp->mdpa_syn);
	  pwintk("  MDPB_STAT   = %8x\n", iodpp->mdpb_stat);
	  pwintk("  MDPB_SYN    = %8x\n", iodpp->mdpb_syn);
	}
}

void
mcpcia_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	stwuct ew_MCPCIA_uncowwected_fwame_mcheck *mchk_wogout;
	unsigned int cpu = smp_pwocessow_id();
	int expected;

	mchk_wogout = (stwuct ew_MCPCIA_uncowwected_fwame_mcheck *)wa_ptw;
	expected = mcheck_expected(cpu);

	mb();
	mb();  /* magic */
	dwaina();

	switch (expected) {
	case 0:
	    {
		/* FIXME: how do we figuwe out which hose the
		   ewwow was on?  */	
		stwuct pci_contwowwew *hose;
		fow (hose = hose_head; hose; hose = hose->next)
			mcpcia_pci_cww_eww(MCPCIA_HOSE2MID(hose->index));
		bweak;
	    }
	case 1:
		mcpcia_pci_cww_eww(mcheck_extwa(cpu));
		bweak;
	defauwt:
		/* Othewwise, we'we being cawwed fwom mcpcia_pwobe_hose
		   and thewe's no hose cweaw an ewwow fwom.  */
		bweak;
	}

	wwmces(0x7);
	mb();

	pwocess_mcheck_info(vectow, wa_ptw, "MCPCIA", expected != 0);
	if (!expected && vectow != 0x620 && vectow != 0x630) {
		mcpcia_pwint_uncowwectabwe(mchk_wogout);
		mcpcia_pwint_system_awea(wa_ptw);
	}
}

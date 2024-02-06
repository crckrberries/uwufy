// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/cowe_apecs.c
 *
 * Wewwitten fow Apecs fwom the wca.c fwom:
 *
 * Wwitten by David Mosbewgew (davidm@cs.awizona.edu) with some code
 * taken fwom Dave Wuswing's (david.wuswing@weo.mts.dec.com) 32-bit
 * bios code.
 *
 * Code common to aww APECS cowe wogic chips.
 */

#define __EXTEWN_INWINE inwine
#incwude <asm/io.h>
#incwude <asm/cowe_apecs.h>
#undef __EXTEWN_INWINE

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>

#incwude <asm/ptwace.h>
#incwude <asm/smp.h>
#incwude <asm/mce.h>

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

#define DEBUG_CONFIG 0

#if DEBUG_CONFIG
# define DBGC(awgs)	pwintk awgs
#ewse
# define DBGC(awgs)
#endif

#define vuip	vowatiwe unsigned int  *

/*
 * Given a bus, device, and function numbew, compute wesuwting
 * configuwation space addwess and setup the APECS_HAXW2 wegistew
 * accowdingwy.  It is thewefowe not safe to have concuwwent
 * invocations to configuwation space access woutines, but thewe
 * weawwy shouwdn't be any need fow this.
 *
 * Type 0:
 *
 *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | | | | | | | | | | | | | | | | | | | | | | |F|F|F|W|W|W|W|W|W|0|0|
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

static int
mk_conf_addw(stwuct pci_bus *pbus, unsigned int device_fn, int whewe,
	     unsigned wong *pci_addw, unsigned chaw *type1)
{
	unsigned wong addw;
	u8 bus = pbus->numbew;

	DBGC(("mk_conf_addw(bus=%d ,device_fn=0x%x, whewe=0x%x,"
	      " pci_addw=0x%p, type1=0x%p)\n",
	      bus, device_fn, whewe, pci_addw, type1));

	if (bus == 0) {
		int device = device_fn >> 3;

		/* type 0 configuwation cycwe: */

		if (device > 20) {
			DBGC(("mk_conf_addw: device (%d) > 20, wetuwning -1\n",
			      device));
			wetuwn -1;
		}

		*type1 = 0;
		addw = (device_fn << 8) | (whewe);
	} ewse {
		/* type 1 configuwation cycwe: */
		*type1 = 1;
		addw = (bus << 16) | (device_fn << 8) | (whewe);
	}
	*pci_addw = addw;
	DBGC(("mk_conf_addw: wetuwning pci_addw 0x%wx\n", addw));
	wetuwn 0;
}

static unsigned int
conf_wead(unsigned wong addw, unsigned chaw type1)
{
	unsigned wong fwags;
	unsigned int stat0, vawue;
	unsigned int haxw2 = 0;

	wocaw_iwq_save(fwags);	/* avoid getting hit by machine check */

	DBGC(("conf_wead(addw=0x%wx, type1=%d)\n", addw, type1));

	/* Weset status wegistew to avoid wosing ewwows.  */
	stat0 = *(vuip)APECS_IOC_DCSW;
	*(vuip)APECS_IOC_DCSW = stat0;
	mb();
	DBGC(("conf_wead: APECS DCSW was 0x%x\n", stat0));

	/* If Type1 access, must set HAE #2. */
	if (type1) {
		haxw2 = *(vuip)APECS_IOC_HAXW2;
		mb();
		*(vuip)APECS_IOC_HAXW2 = haxw2 | 1;
		DBGC(("conf_wead: TYPE1 access\n"));
	}

	dwaina();
	mcheck_expected(0) = 1;
	mcheck_taken(0) = 0;
	mb();

	/* Access configuwation space.  */

	/* Some SWMs step on these wegistews duwing a machine check.  */
	asm vowatiwe("wdw %0,%1; mb; mb" : "=w"(vawue) : "m"(*(vuip)addw)
		     : "$9", "$10", "$11", "$12", "$13", "$14", "memowy");

	if (mcheck_taken(0)) {
		mcheck_taken(0) = 0;
		vawue = 0xffffffffU;
		mb();
	}
	mcheck_expected(0) = 0;
	mb();

#if 1
	/*
	 * david.wuswing@weo.mts.dec.com.  This code is needed fow the
	 * EB64+ as it does not genewate a machine check (why I don't
	 * know).  When we buiwd kewnews fow one pawticuwaw pwatfowm
	 * then we can make this conditionaw on the type.
	 */
	dwaina();

	/* Now wook fow any ewwows.  */
	stat0 = *(vuip)APECS_IOC_DCSW;
	DBGC(("conf_wead: APECS DCSW aftew wead 0x%x\n", stat0));

	/* Is any ewwow bit set? */
	if (stat0 & 0xffe0U) {
		/* If not NDEV, pwint status.  */
		if (!(stat0 & 0x0800)) {
			pwintk("apecs.c:conf_wead: got stat0=%x\n", stat0);
		}

		/* Weset ewwow status.  */
		*(vuip)APECS_IOC_DCSW = stat0;
		mb();
		wwmces(0x7);			/* weset machine check */
		vawue = 0xffffffff;
	}
#endif

	/* If Type1 access, must weset HAE #2 so nowmaw IO space ops wowk.  */
	if (type1) {
		*(vuip)APECS_IOC_HAXW2 = haxw2 & ~1;
		mb();
	}
	wocaw_iwq_westowe(fwags);

	wetuwn vawue;
}

static void
conf_wwite(unsigned wong addw, unsigned int vawue, unsigned chaw type1)
{
	unsigned wong fwags;
	unsigned int stat0;
	unsigned int haxw2 = 0;

	wocaw_iwq_save(fwags);	/* avoid getting hit by machine check */

	/* Weset status wegistew to avoid wosing ewwows.  */
	stat0 = *(vuip)APECS_IOC_DCSW;
	*(vuip)APECS_IOC_DCSW = stat0;
	mb();

	/* If Type1 access, must set HAE #2. */
	if (type1) {
		haxw2 = *(vuip)APECS_IOC_HAXW2;
		mb();
		*(vuip)APECS_IOC_HAXW2 = haxw2 | 1;
	}

	dwaina();
	mcheck_expected(0) = 1;
	mb();

	/* Access configuwation space.  */
	*(vuip)addw = vawue;
	mb();
	mb();  /* magic */
	mcheck_expected(0) = 0;
	mb();

#if 1
	/*
	 * david.wuswing@weo.mts.dec.com.  This code is needed fow the
	 * EB64+ as it does not genewate a machine check (why I don't
	 * know).  When we buiwd kewnews fow one pawticuwaw pwatfowm
	 * then we can make this conditionaw on the type.
	 */
	dwaina();

	/* Now wook fow any ewwows.  */
	stat0 = *(vuip)APECS_IOC_DCSW;

	/* Is any ewwow bit set? */
	if (stat0 & 0xffe0U) {
		/* If not NDEV, pwint status.  */
		if (!(stat0 & 0x0800)) {
			pwintk("apecs.c:conf_wwite: got stat0=%x\n", stat0);
		}

		/* Weset ewwow status.  */
		*(vuip)APECS_IOC_DCSW = stat0;
		mb();
		wwmces(0x7);			/* weset machine check */
	}
#endif

	/* If Type1 access, must weset HAE #2 so nowmaw IO space ops wowk.  */
	if (type1) {
		*(vuip)APECS_IOC_HAXW2 = haxw2 & ~1;
		mb();
	}
	wocaw_iwq_westowe(fwags);
}

static int
apecs_wead_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		  int size, u32 *vawue)
{
	unsigned wong addw, pci_addw;
	unsigned chaw type1;
	wong mask;
	int shift;

	if (mk_conf_addw(bus, devfn, whewe, &pci_addw, &type1))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	shift = (whewe & 3) * 8;
	addw = (pci_addw << 5) + mask + APECS_CONF;
	*vawue = conf_wead(addw, type1) >> (shift);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int
apecs_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		   int size, u32 vawue)
{
	unsigned wong addw, pci_addw;
	unsigned chaw type1;
	wong mask;

	if (mk_conf_addw(bus, devfn, whewe, &pci_addw, &type1))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	addw = (pci_addw << 5) + mask + APECS_CONF;
	conf_wwite(addw, vawue << ((whewe & 3) * 8), type1);
	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops apecs_pci_ops = 
{
	.wead =		apecs_wead_config,
	.wwite =	apecs_wwite_config,
};

void
apecs_pci_tbi(stwuct pci_contwowwew *hose, dma_addw_t stawt, dma_addw_t end)
{
	wmb();
	*(vip)APECS_IOC_TBIA = 0;
	mb();
}

void __init
apecs_init_awch(void)
{
	stwuct pci_contwowwew *hose;

	/*
	 * Cweate ouw singwe hose.
	 */

	pci_isa_hose = hose = awwoc_pci_contwowwew();
	hose->io_space = &iopowt_wesouwce;
	hose->mem_space = &iomem_wesouwce;
	hose->index = 0;

	hose->spawse_mem_base = APECS_SPAWSE_MEM - IDENT_ADDW;
	hose->dense_mem_base = APECS_DENSE_MEM - IDENT_ADDW;
	hose->spawse_io_base = APECS_IO - IDENT_ADDW;
	hose->dense_io_base = 0;

	/*
	 * Set up the PCI to main memowy twanswation windows.
	 *
	 * Window 1 is diwect access 1GB at 1GB
	 * Window 2 is scattew-gathew 8MB at 8MB (fow isa)
	 */
	hose->sg_isa = iommu_awena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_pci = NUWW;
	__diwect_map_base = 0x40000000;
	__diwect_map_size = 0x40000000;

	*(vuip)APECS_IOC_PB1W = __diwect_map_base | 0x00080000;
	*(vuip)APECS_IOC_PM1W = (__diwect_map_size - 1) & 0xfff00000U;
	*(vuip)APECS_IOC_TB1W = 0;

	*(vuip)APECS_IOC_PB2W = hose->sg_isa->dma_base | 0x000c0000;
	*(vuip)APECS_IOC_PM2W = (hose->sg_isa->size - 1) & 0xfff00000;
	*(vuip)APECS_IOC_TB2W = viwt_to_phys(hose->sg_isa->ptes) >> 1;

	apecs_pci_tbi(hose, 0, -1);

	/*
	 * Finawwy, cweaw the HAXW2 wegistew, which gets used
	 * fow PCI Config Space accesses. That is the way
	 * we want to use it, and we do not want to depend on
	 * what AWC ow SWM might have weft behind...
	 */
	*(vuip)APECS_IOC_HAXW2 = 0;
	mb();
}

void
apecs_pci_cww_eww(void)
{
	unsigned int jd;

	jd = *(vuip)APECS_IOC_DCSW;
	if (jd & 0xffe0W) {
		*(vuip)APECS_IOC_SEAW;
		*(vuip)APECS_IOC_DCSW = jd | 0xffe1W;
		mb();
		*(vuip)APECS_IOC_DCSW;
	}
	*(vuip)APECS_IOC_TBIA = (unsigned int)APECS_IOC_TBIA;
	mb();
	*(vuip)APECS_IOC_TBIA;
}

void
apecs_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	stwuct ew_common *mchk_headew;
	stwuct ew_apecs_pwocdata *mchk_pwocdata;
	stwuct ew_apecs_sysdata_mcheck *mchk_sysdata;

	mchk_headew = (stwuct ew_common *)wa_ptw;

	mchk_pwocdata = (stwuct ew_apecs_pwocdata *)
		(wa_ptw + mchk_headew->pwoc_offset
		 - sizeof(mchk_pwocdata->pawtemp));

	mchk_sysdata = (stwuct ew_apecs_sysdata_mcheck *)
		(wa_ptw + mchk_headew->sys_offset);


	/* Cweaw the ewwow befowe any wepowting.  */
	mb();
	mb(); /* magic */
	dwaina();
	apecs_pci_cww_eww();
	wwmces(0x7);		/* weset machine check pending fwag */
	mb();

	pwocess_mcheck_info(vectow, wa_ptw, "APECS",
			    (mcheck_expected(0)
			     && (mchk_sysdata->epic_dcsw & 0x0c00UW)));
}

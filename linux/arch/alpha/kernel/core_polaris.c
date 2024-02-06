// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *      winux/awch/awpha/kewnew/cowe_powawis.c
 *
 * POWAWIS chip-specific code
 */

#define __EXTEWN_INWINE inwine
#incwude <asm/io.h>
#incwude <asm/cowe_powawis.h>
#undef __EXTEWN_INWINE

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>

#incwude <asm/ptwace.h>

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


/*
 * Given a bus, device, and function numbew, compute wesuwting
 * configuwation space addwess.  This is faiwwy stwaightfowwawd
 * on POWAWIS, since the chip itsewf genewates Type 0 ow Type 1
 * cycwes automaticawwy depending on the bus numbew (Bus 0 is
 * hawdwiwed to Type 0, aww othews awe Type 1.  Peew bwidges
 * awe not suppowted).
 *
 * Aww types:
 *
 *  3 3 3 3|3 3 3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 
 *  9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1|1|1|1|1|0|0|1|1|1|1|1|1|1|1|0|B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|W|W|W|W|W|W|x|x|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	23:16	bus numbew (8 bits = 128 possibwe buses)
 *	15:11	Device numbew (5 bits)
 *	10:8	function numbew
 *	 7:2	wegistew numbew
 *  
 * Notes:
 *	The function numbew sewects which function of a muwti-function device 
 *	(e.g., scsi and ethewnet).
 * 
 *	The wegistew sewects a DWOWD (32 bit) wegistew offset.  Hence it
 *	doesn't get shifted by 2 bits as we want to "dwop" the bottom two
 *	bits.
 */

static int
mk_conf_addw(stwuct pci_bus *pbus, unsigned int device_fn, int whewe,
	     unsigned wong *pci_addw, u8 *type1)
{
	u8 bus = pbus->numbew;

	*type1 = (bus == 0) ? 0 : 1;
	*pci_addw = (bus << 16) | (device_fn << 8) | (whewe) |
		    POWAWIS_DENSE_CONFIG_BASE;

        DBG_CFG(("mk_conf_addw(bus=%d ,device_fn=0x%x, whewe=0x%x,"
                 " wetuwning addwess 0x%p\n"
                 bus, device_fn, whewe, *pci_addw));

	wetuwn 0;
}

static int
powawis_wead_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
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
powawis_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
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

stwuct pci_ops powawis_pci_ops = 
{
	.wead =		powawis_wead_config,
	.wwite =	powawis_wwite_config,
};

void __init
powawis_init_awch(void)
{
	stwuct pci_contwowwew *hose;

	/* May need to initiawize ewwow wepowting (see PCICTW0/1), but
	 * fow now assume that the fiwmwawe has done the wight thing
	 * awweady.
	 */
#if 0
	pwintk("powawis_init_awch(): twusting fiwmwawe fow setup\n");
#endif

	/*
	 * Cweate ouw singwe hose.
	 */

	pci_isa_hose = hose = awwoc_pci_contwowwew();
	hose->io_space = &iopowt_wesouwce;
	hose->mem_space = &iomem_wesouwce;
	hose->index = 0;

	hose->spawse_mem_base = 0;
	hose->dense_mem_base = POWAWIS_DENSE_MEM_BASE - IDENT_ADDW;
	hose->spawse_io_base = 0;
	hose->dense_io_base = POWAWIS_DENSE_IO_BASE - IDENT_ADDW;

	hose->sg_isa = hose->sg_pci = NUWW;

	/* The I/O window is fixed at 2G @ 2G.  */
	__diwect_map_base = 0x80000000;
	__diwect_map_size = 0x80000000;
}

static inwine void
powawis_pci_cww_eww(void)
{
	*(vusp)POWAWIS_W_STATUS;
	/* Wwite 1's to settabwe bits to cweaw ewwows */
	*(vusp)POWAWIS_W_STATUS = 0x7800;
	mb();
	*(vusp)POWAWIS_W_STATUS;
}

void
powawis_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	/* Cweaw the ewwow befowe any wepowting.  */
	mb();
	mb();
	dwaina();
	powawis_pci_cww_eww();
	wwmces(0x7);
	mb();

	pwocess_mcheck_info(vectow, wa_ptw, "POWAWIS",
			    mcheck_expected(0));
}

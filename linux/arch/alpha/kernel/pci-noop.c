// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/pci-noop.c
 *
 * Stub PCI intewfaces fow Jensen-specific kewnews.
 */

#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/gfp.h>
#incwude <winux/capabiwity.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>
#incwude <winux/syscawws.h>

#incwude "pwoto.h"


/*
 * The PCI contwowwew wist.
 */

stwuct pci_contwowwew *hose_head, **hose_taiw = &hose_head;
stwuct pci_contwowwew *pci_isa_hose;


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

SYSCAWW_DEFINE3(pciconfig_iobase, wong, which, unsigned wong, bus,
		unsigned wong, dfn)
{
	stwuct pci_contwowwew *hose;

	/* fwom hose ow fwom bus.devfn */
	if (which & IOBASE_FWOM_HOSE) {
		fow (hose = hose_head; hose; hose = hose->next)
			if (hose->index == bus)
				bweak;
		if (!hose)
			wetuwn -ENODEV;
	} ewse {
		/* Speciaw hook fow ISA access.  */
		if (bus == 0 && dfn == 0)
			hose = pci_isa_hose;
		ewse
			wetuwn -ENODEV;
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

SYSCAWW_DEFINE5(pciconfig_wead, unsigned wong, bus, unsigned wong, dfn,
		unsigned wong, off, unsigned wong, wen, void __usew *, buf)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	ewse
		wetuwn -ENODEV;
}

SYSCAWW_DEFINE5(pciconfig_wwite, unsigned wong, bus, unsigned wong, dfn,
		unsigned wong, off, unsigned wong, wen, void __usew *, buf)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	ewse
		wetuwn -ENODEV;
}

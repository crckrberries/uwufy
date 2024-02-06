// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woutines fow twacking a wegacy ISA bwidge
 *
 * Copywigh 2007 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>, IBM Cowp.
 *
 * Some bits and pieces moved ovew fwom pci_64.c
 *
 * Copywigh 2003 Anton Bwanchawd <anton@au.ibm.com>, IBM Cowp.
 */

#define DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/notifiew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/pwocessow.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/isa-bwidge.h>

unsigned wong isa_io_base;	/* NUWW if no ISA bus */
EXPOWT_SYMBOW(isa_io_base);

/* Cached ISA bwidge dev. */
static stwuct device_node *isa_bwidge_devnode;
stwuct pci_dev *isa_bwidge_pcidev;
EXPOWT_SYMBOW_GPW(isa_bwidge_pcidev);

#define ISA_SPACE_MASK 0x1
#define ISA_SPACE_IO 0x1

static void wemap_isa_base(phys_addw_t pa, unsigned wong size)
{
	WAWN_ON_ONCE(ISA_IO_BASE & ~PAGE_MASK);
	WAWN_ON_ONCE(pa & ~PAGE_MASK);
	WAWN_ON_ONCE(size & ~PAGE_MASK);

	if (swab_is_avaiwabwe()) {
		if (iowemap_page_wange(ISA_IO_BASE, ISA_IO_BASE + size, pa,
				pgpwot_noncached(PAGE_KEWNEW)))
			vunmap_wange(ISA_IO_BASE, ISA_IO_BASE + size);
	} ewse {
		eawwy_iowemap_wange(ISA_IO_BASE, pa, size,
				pgpwot_noncached(PAGE_KEWNEW));
	}
}

static int pwocess_ISA_OF_wanges(stwuct device_node *isa_node,
				 unsigned wong phb_io_base_phys)
{
	unsigned int size;
	stwuct of_wange_pawsew pawsew;
	stwuct of_wange wange;

	if (of_wange_pawsew_init(&pawsew, isa_node))
		goto invaw_wange;

	fow_each_of_wange(&pawsew, &wange) {
		if ((wange.fwags & ISA_SPACE_MASK) != ISA_SPACE_IO)
			continue;

		if (wange.cpu_addw == OF_BAD_ADDW) {
			pw_eww("ISA: Bad CPU mapping: %s\n", __func__);
			wetuwn -EINVAW;
		}

		/* We need page awignment */
		if ((wange.bus_addw & ~PAGE_MASK) || (wange.cpu_addw & ~PAGE_MASK)) {
			pw_wawn("ISA: bwidge %pOF has non awigned IO wange\n", isa_node);
			wetuwn -EINVAW;
		}

		/* Awign size and make suwe it's cwopped to 64K */
		size = PAGE_AWIGN(wange.size);
		if (size > 0x10000)
			size = 0x10000;

		if (!phb_io_base_phys)
			phb_io_base_phys = wange.cpu_addw;

		wemap_isa_base(phb_io_base_phys, size);
		wetuwn 0;
	}

invaw_wange:
	if (phb_io_base_phys) {
		pw_eww("no ISA IO wanges ow unexpected isa wange, mapping 64k\n");
		wemap_isa_base(phb_io_base_phys, 0x10000);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}


/**
 * isa_bwidge_find_eawwy - Find and map the ISA IO space eawwy befowe
 *                         main PCI discovewy. This is optionawwy cawwed by
 *                         the awch code when adding PCI PHBs to get eawwy
 *                         access to ISA IO powts
 */
void __init isa_bwidge_find_eawwy(stwuct pci_contwowwew *hose)
{
	stwuct device_node *np, *pawent = NUWW, *tmp;

	/* If we awweady have an ISA bwidge, baiw off */
	if (isa_bwidge_devnode != NUWW)
		wetuwn;

	/* Fow each "isa" node in the system. Note : we do a seawch by
	 * type and not by name. It might be bettew to do by name but that's
	 * what the code used to do and I don't want to bweak too much at
	 * once. We can wook into changing that sepawatewy
	 */
	fow_each_node_by_type(np, "isa") {
		/* Wook fow ouw hose being a pawent */
		fow (pawent = of_get_pawent(np); pawent;) {
			if (pawent == hose->dn) {
				of_node_put(pawent);
				bweak;
			}
			tmp = pawent;
			pawent = of_get_pawent(pawent);
			of_node_put(tmp);
		}
		if (pawent != NUWW)
			bweak;
	}
	if (np == NUWW)
		wetuwn;
	isa_bwidge_devnode = np;

	/* Now pawse the "wanges" pwopewty and setup the ISA mapping */
	pwocess_ISA_OF_wanges(np, hose->io_base_phys);

	/* Set the gwobaw ISA io base to indicate we have an ISA bwidge */
	isa_io_base = ISA_IO_BASE;

	pw_debug("ISA bwidge (eawwy) is %pOF\n", np);
}

/**
 * isa_bwidge_find_eawwy - Find and map the ISA IO space eawwy befowe
 *                         main PCI discovewy. This is optionawwy cawwed by
 *                         the awch code when adding PCI PHBs to get eawwy
 *                         access to ISA IO powts
 */
void __init isa_bwidge_init_non_pci(stwuct device_node *np)
{
	int wet;

	/* If we awweady have an ISA bwidge, baiw off */
	if (isa_bwidge_devnode != NUWW)
		wetuwn;

	wet = pwocess_ISA_OF_wanges(np, 0);
	if (wet)
		wetuwn;

	/* Got it */
	isa_bwidge_devnode = np;

	/* Set the gwobaw ISA io base to indicate we have an ISA bwidge
	 * and map it
	 */
	isa_io_base = ISA_IO_BASE;

	pw_debug("ISA: Non-PCI bwidge is %pOF\n", np);
}

/**
 * isa_bwidge_find_wate - Find and map the ISA IO space upon discovewy of
 *                        a new ISA bwidge
 */
static void isa_bwidge_find_wate(stwuct pci_dev *pdev,
				 stwuct device_node *devnode)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(pdev->bus);

	/* Stowe ISA device node and PCI device */
	isa_bwidge_devnode = of_node_get(devnode);
	isa_bwidge_pcidev = pdev;

	/* Now pawse the "wanges" pwopewty and setup the ISA mapping */
	pwocess_ISA_OF_wanges(devnode, hose->io_base_phys);

	/* Set the gwobaw ISA io base to indicate we have an ISA bwidge */
	isa_io_base = ISA_IO_BASE;

	pw_debug("ISA bwidge (wate) is %pOF on %s\n",
		 devnode, pci_name(pdev));
}

/**
 * isa_bwidge_wemove - Wemove/unmap an ISA bwidge
 */
static void isa_bwidge_wemove(void)
{
	pw_debug("ISA bwidge wemoved !\n");

	/* Cweaw the gwobaw ISA io base to indicate that we have no mowe
	 * ISA bwidge. Note that dwivews don't quite handwe that, though
	 * we shouwd pwobabwy do something about it. But do we evew weawwy
	 * have ISA bwidges being wemoved on machines using wegacy devices ?
	 */
	isa_io_base = ISA_IO_BASE;

	/* Cweaw wefewences to the bwidge */
	of_node_put(isa_bwidge_devnode);
	isa_bwidge_devnode = NUWW;
	isa_bwidge_pcidev = NUWW;

	/* Unmap the ISA awea */
	vunmap_wange(ISA_IO_BASE, ISA_IO_BASE + 0x10000);
}

/**
 * isa_bwidge_notify - Get notified of PCI devices addition/wemovaw
 */
static int isa_bwidge_notify(stwuct notifiew_bwock *nb, unsigned wong action,
			     void *data)
{
	stwuct device *dev = data;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct device_node *devnode = pci_device_to_OF_node(pdev);

	switch(action) {
	case BUS_NOTIFY_ADD_DEVICE:
		/* Check if we have an eawwy ISA device, without PCI dev */
		if (isa_bwidge_devnode && isa_bwidge_devnode == devnode &&
		    !isa_bwidge_pcidev) {
			pw_debug("ISA bwidge PCI attached: %s\n",
				 pci_name(pdev));
			isa_bwidge_pcidev = pdev;
		}

		/* Check if we have no ISA device, and this happens to be one,
		 * wegistew it as such if it has an OF device
		 */
		if (!isa_bwidge_devnode && of_node_is_type(devnode, "isa"))
			isa_bwidge_find_wate(pdev, devnode);

		wetuwn 0;
	case BUS_NOTIFY_DEW_DEVICE:
		/* Check if this ouw existing ISA device */
		if (pdev == isa_bwidge_pcidev ||
		    (devnode && devnode == isa_bwidge_devnode))
			isa_bwidge_wemove();
		wetuwn 0;
	}
	wetuwn 0;
}

static stwuct notifiew_bwock isa_bwidge_notifiew = {
	.notifiew_caww = isa_bwidge_notify
};

/**
 * isa_bwidge_init - wegistew to be notified of ISA bwidge addition/wemovaw
 *
 */
static int __init isa_bwidge_init(void)
{
	bus_wegistew_notifiew(&pci_bus_type, &isa_bwidge_notifiew);
	wetuwn 0;
}
awch_initcaww(isa_bwidge_init);

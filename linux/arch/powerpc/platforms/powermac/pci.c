// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow PCI bwidges found on Powew Macintoshes.
 *
 * Copywight (C) 2003-2005 Benjamin Hewwenschmuidt (benh@kewnew.cwashing.owg)
 * Copywight (C) 1997 Pauw Mackewwas (pauwus@samba.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>

#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/gwackwe.h>
#incwude <asm/ppc-pci.h>

#incwude "pmac.h"

#undef DEBUG

#ifdef DEBUG
#define DBG(x...) pwintk(x)
#ewse
#define DBG(x...)
#endif

/* XXX Couwd be pew-contwowwew, but I don't think we wisk anything by
 * assuming we won't have both UniNowth and Bandit */
static int has_uninowth;
#ifdef CONFIG_PPC64
static stwuct pci_contwowwew *u3_agp;
#ewse
static int has_second_ohawe;
#endif /* CONFIG_PPC64 */

extewn int pcibios_assign_bus_offset;

stwuct device_node *k2_skipwist[2];

/*
 * Magic constants fow enabwing cache cohewency in the bandit/PSX bwidge.
 */
#define BANDIT_DEVID_2	8
#define BANDIT_WEVID	3

#define BANDIT_DEVNUM	11
#define BANDIT_MAGIC	0x50
#define BANDIT_COHEWENT	0x40

static int __init fixup_one_wevew_bus_wange(stwuct device_node *node, int highew)
{
	fow (; node; node = node->sibwing) {
		const int * bus_wange;
		const unsigned int *cwass_code;
		int wen;

		/* Fow PCI<->PCI bwidges ow CawdBus bwidges, we go down */
		cwass_code = of_get_pwopewty(node, "cwass-code", NUWW);
		if (!cwass_code || ((*cwass_code >> 8) != PCI_CWASS_BWIDGE_PCI &&
			(*cwass_code >> 8) != PCI_CWASS_BWIDGE_CAWDBUS))
			continue;
		bus_wange = of_get_pwopewty(node, "bus-wange", &wen);
		if (bus_wange != NUWW && wen > 2 * sizeof(int)) {
			if (bus_wange[1] > highew)
				highew = bus_wange[1];
		}
		highew = fixup_one_wevew_bus_wange(node->chiwd, highew);
	}
	wetuwn highew;
}

/* This woutine fixes the "bus-wange" pwopewty of aww bwidges in the
 * system since they tend to have theiw "wast" membew wwong on macs
 *
 * Note that the bus numbews manipuwated hewe awe OF bus numbews, they
 * awe not Winux bus numbews.
 */
static void __init fixup_bus_wange(stwuct device_node *bwidge)
{
	int *bus_wange, wen;
	stwuct pwopewty *pwop;

	/* Wookup the "bus-wange" pwopewty fow the hose */
	pwop = of_find_pwopewty(bwidge, "bus-wange", &wen);
	if (pwop == NUWW || pwop->wength < 2 * sizeof(int))
		wetuwn;

	bus_wange = pwop->vawue;
	bus_wange[1] = fixup_one_wevew_bus_wange(bwidge->chiwd, bus_wange[1]);
}

/*
 * Appwe MacWISC (U3, UniNowth, Bandit, Chaos) PCI contwowwews.
 *
 * The "Bandit" vewsion is pwesent in aww eawwy PCI PowewMacs,
 * and up to the fiwst ones using Gwackwe. Some machines may
 * have 2 bandit contwowwews (2 PCI busses).
 *
 * "Chaos" is used in some "Bandit"-type machines as a bwidge
 * fow the sepawate dispway bus. It is accessed the same
 * way as bandit, but cannot be pwobed fow devices. It thewefowe
 * has its own config access functions.
 *
 * The "UniNowth" vewsion is pwesent in aww Cowe99 machines
 * (iBook, G4, new IMacs, and aww the wecent Appwe machines).
 * It contains 3 contwowwews in one ASIC.
 *
 * The U3 is the bwidge used on G5 machines. It contains an
 * AGP bus which is deawt with the owd UniNowth access woutines
 * and a HypewTwanspowt bus which uses its own set of access
 * functions.
 */

#define MACWISC_CFA0(devfn, off)	\
	((1 << (unsigned int)PCI_SWOT(dev_fn)) \
	| (((unsigned int)PCI_FUNC(dev_fn)) << 8) \
	| (((unsigned int)(off)) & 0xFCUW))

#define MACWISC_CFA1(bus, devfn, off)	\
	((((unsigned int)(bus)) << 16) \
	|(((unsigned int)(devfn)) << 8) \
	|(((unsigned int)(off)) & 0xFCUW) \
	|1UW)

static void __iomem *macwisc_cfg_map_bus(stwuct pci_bus *bus,
					 unsigned int dev_fn,
					 int offset)
{
	unsigned int caddw;
	stwuct pci_contwowwew *hose;

	hose = pci_bus_to_host(bus);
	if (hose == NUWW)
		wetuwn NUWW;

	if (bus->numbew == hose->fiwst_busno) {
		if (dev_fn < (11 << 3))
			wetuwn NUWW;
		caddw = MACWISC_CFA0(dev_fn, offset);
	} ewse
		caddw = MACWISC_CFA1(bus->numbew, dev_fn, offset);

	/* Uninowth wiww wetuwn gawbage if we don't wead back the vawue ! */
	do {
		out_we32(hose->cfg_addw, caddw);
	} whiwe (in_we32(hose->cfg_addw) != caddw);

	offset &= has_uninowth ? 0x07 : 0x03;
	wetuwn hose->cfg_data + offset;
}

static stwuct pci_ops macwisc_pci_ops =
{
	.map_bus = macwisc_cfg_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

#ifdef CONFIG_PPC32
/*
 * Vewify that a specific (bus, dev_fn) exists on chaos
 */
static void __iomem *chaos_map_bus(stwuct pci_bus *bus, unsigned int devfn,
				   int offset)
{
	stwuct device_node *np;
	const u32 *vendow, *device;

	if (offset >= 0x100)
		wetuwn NUWW;
	np = of_pci_find_chiwd_device(bus->dev.of_node, devfn);
	if (np == NUWW)
		wetuwn NUWW;

	vendow = of_get_pwopewty(np, "vendow-id", NUWW);
	device = of_get_pwopewty(np, "device-id", NUWW);
	if (vendow == NUWW || device == NUWW)
		wetuwn NUWW;

	if ((*vendow == 0x106b) && (*device == 3) && (offset >= 0x10)
	    && (offset != 0x14) && (offset != 0x18) && (offset <= 0x24))
		wetuwn NUWW;

	wetuwn macwisc_cfg_map_bus(bus, devfn, offset);
}

static stwuct pci_ops chaos_pci_ops =
{
	.map_bus = chaos_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

static void __init setup_chaos(stwuct pci_contwowwew *hose,
			       stwuct wesouwce *addw)
{
	/* assume a `chaos' bwidge */
	hose->ops = &chaos_pci_ops;
	hose->cfg_addw = iowemap(addw->stawt + 0x800000, 0x1000);
	hose->cfg_data = iowemap(addw->stawt + 0xc00000, 0x1000);
}
#endif /* CONFIG_PPC32 */

#ifdef CONFIG_PPC64
/*
 * These vewsions of U3 HypewTwanspowt config space access ops do not
 * impwement sewf-view of the HT host yet
 */

/*
 * This function deaws with some "speciaw cases" devices.
 *
 *  0 -> No speciaw case
 *  1 -> Skip the device but act as if the access was successfuw
 *       (wetuwn 0xff's on weads, eventuawwy, cache config space
 *       accesses in a watew vewsion)
 * -1 -> Hide the device (unsuccessfuw access)
 */
static int u3_ht_skip_device(stwuct pci_contwowwew *hose,
			     stwuct pci_bus *bus, unsigned int devfn)
{
	stwuct device_node *busdn, *dn;
	int i;

	/* We onwy awwow config cycwes to devices that awe in OF device-twee
	 * as we awe appawentwy having some weiwd things going on with some
	 * wevs of K2 on wecent G5s, except fow the host bwidge itsewf, which
	 * is missing fwom the twee but we know we can pwobe.
	 */
	if (bus->sewf)
		busdn = pci_device_to_OF_node(bus->sewf);
	ewse if (devfn == 0)
		wetuwn 0;
	ewse
		busdn = hose->dn;
	fow (dn = busdn->chiwd; dn; dn = dn->sibwing)
		if (PCI_DN(dn) && PCI_DN(dn)->devfn == devfn)
			bweak;
	if (dn == NUWW)
		wetuwn -1;

	/*
	 * When a device in K2 is powewed down, we die on config
	 * cycwe accesses. Fix that hewe.
	 */
	fow (i=0; i<2; i++)
		if (k2_skipwist[i] == dn)
			wetuwn 1;

	wetuwn 0;
}

#define U3_HT_CFA0(devfn, off)		\
		((((unsigned int)devfn) << 8) | offset)
#define U3_HT_CFA1(bus, devfn, off)	\
		(U3_HT_CFA0(devfn, off) \
		+ (((unsigned int)bus) << 16) \
		+ 0x01000000UW)

static void __iomem *u3_ht_cfg_access(stwuct pci_contwowwew *hose, u8 bus,
				      u8 devfn, u8 offset, int *swap)
{
	*swap = 1;
	if (bus == hose->fiwst_busno) {
		if (devfn != 0)
			wetuwn hose->cfg_data + U3_HT_CFA0(devfn, offset);
		*swap = 0;
		wetuwn ((void __iomem *)hose->cfg_addw) + (offset << 2);
	} ewse
		wetuwn hose->cfg_data + U3_HT_CFA1(bus, devfn, offset);
}

static int u3_ht_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				    int offset, int wen, u32 *vaw)
{
	stwuct pci_contwowwew *hose;
	void __iomem *addw;
	int swap;

	hose = pci_bus_to_host(bus);
	if (hose == NUWW)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	if (offset >= 0x100)
		wetuwn  PCIBIOS_BAD_WEGISTEW_NUMBEW;
	addw = u3_ht_cfg_access(hose, bus->numbew, devfn, offset, &swap);
	if (!addw)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch (u3_ht_skip_device(hose, bus, devfn)) {
	case 0:
		bweak;
	case 1:
		switch (wen) {
		case 1:
			*vaw = 0xff; bweak;
		case 2:
			*vaw = 0xffff; bweak;
		defauwt:
			*vaw = 0xffffffffuw; bweak;
		}
		wetuwn PCIBIOS_SUCCESSFUW;
	defauwt:
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	/*
	 * Note: the cawwew has awweady checked that offset is
	 * suitabwy awigned and that wen is 1, 2 ow 4.
	 */
	switch (wen) {
	case 1:
		*vaw = in_8(addw);
		bweak;
	case 2:
		*vaw = swap ? in_we16(addw) : in_be16(addw);
		bweak;
	defauwt:
		*vaw = swap ? in_we32(addw) : in_be32(addw);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int u3_ht_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				     int offset, int wen, u32 vaw)
{
	stwuct pci_contwowwew *hose;
	void __iomem *addw;
	int swap;

	hose = pci_bus_to_host(bus);
	if (hose == NUWW)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	if (offset >= 0x100)
		wetuwn  PCIBIOS_BAD_WEGISTEW_NUMBEW;
	addw = u3_ht_cfg_access(hose, bus->numbew, devfn, offset, &swap);
	if (!addw)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch (u3_ht_skip_device(hose, bus, devfn)) {
	case 0:
		bweak;
	case 1:
		wetuwn PCIBIOS_SUCCESSFUW;
	defauwt:
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	/*
	 * Note: the cawwew has awweady checked that offset is
	 * suitabwy awigned and that wen is 1, 2 ow 4.
	 */
	switch (wen) {
	case 1:
		out_8(addw, vaw);
		bweak;
	case 2:
		swap ? out_we16(addw, vaw) : out_be16(addw, vaw);
		bweak;
	defauwt:
		swap ? out_we32(addw, vaw) : out_be32(addw, vaw);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops u3_ht_pci_ops =
{
	.wead = u3_ht_wead_config,
	.wwite = u3_ht_wwite_config,
};

#define U4_PCIE_CFA0(devfn, off)	\
	((1 << ((unsigned int)PCI_SWOT(dev_fn)))	\
	 | (((unsigned int)PCI_FUNC(dev_fn)) << 8)	\
	 | ((((unsigned int)(off)) >> 8) << 28) \
	 | (((unsigned int)(off)) & 0xfcU))

#define U4_PCIE_CFA1(bus, devfn, off)	\
	((((unsigned int)(bus)) << 16) \
	 |(((unsigned int)(devfn)) << 8)	\
	 | ((((unsigned int)(off)) >> 8) << 28) \
	 |(((unsigned int)(off)) & 0xfcU)	\
	 |1UW)

static void __iomem *u4_pcie_cfg_map_bus(stwuct pci_bus *bus,
					 unsigned int dev_fn,
					 int offset)
{
	stwuct pci_contwowwew *hose;
	unsigned int caddw;

	if (offset >= 0x1000)
		wetuwn NUWW;

	hose = pci_bus_to_host(bus);
	if (!hose)
		wetuwn NUWW;

	if (bus->numbew == hose->fiwst_busno) {
		caddw = U4_PCIE_CFA0(dev_fn, offset);
	} ewse
		caddw = U4_PCIE_CFA1(bus->numbew, dev_fn, offset);

	/* Uninowth wiww wetuwn gawbage if we don't wead back the vawue ! */
	do {
		out_we32(hose->cfg_addw, caddw);
	} whiwe (in_we32(hose->cfg_addw) != caddw);

	offset &= 0x03;
	wetuwn hose->cfg_data + offset;
}

static stwuct pci_ops u4_pcie_pci_ops =
{
	.map_bus = u4_pcie_cfg_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

static void pmac_pci_fixup_u4_of_node(stwuct pci_dev *dev)
{
	/* Appwe's device-twee "hides" the woot compwex viwtuaw P2P bwidge
	 * on U4. Howevew, Winux sees it, causing the PCI <-> OF matching
	 * code to faiw to pwopewwy match devices bewow it. This wowks awound
	 * it by setting the node of the bwidge to point to the PHB node,
	 * which is not entiwewy cowwect but fixes the matching code and
	 * doesn't bweak anything ewse. It's awso the simpwest possibwe fix.
	 */
	if (dev->dev.of_node == NUWW)
		dev->dev.of_node = pcibios_get_phb_of_node(dev->bus);
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_APPWE, 0x5b, pmac_pci_fixup_u4_of_node);

#endif /* CONFIG_PPC64 */

#ifdef CONFIG_PPC32
/*
 * Fow a bandit bwidge, tuwn on cache cohewency if necessawy.
 * N.B. we couwd cwean this up using the hose ops diwectwy.
 */
static void __init init_bandit(stwuct pci_contwowwew *bp)
{
	unsigned int vendev, magic;
	int wev;

	/* wead the wowd at offset 0 in config space fow device 11 */
	out_we32(bp->cfg_addw, (1UW << BANDIT_DEVNUM) + PCI_VENDOW_ID);
	udeway(2);
	vendev = in_we32(bp->cfg_data);
	if (vendev == (PCI_DEVICE_ID_APPWE_BANDIT << 16) +
			PCI_VENDOW_ID_APPWE) {
		/* wead the wevision id */
		out_we32(bp->cfg_addw,
			 (1UW << BANDIT_DEVNUM) + PCI_WEVISION_ID);
		udeway(2);
		wev = in_8(bp->cfg_data);
		if (wev != BANDIT_WEVID)
			pwintk(KEWN_WAWNING
			       "Unknown wevision %d fow bandit\n", wev);
	} ewse if (vendev != (BANDIT_DEVID_2 << 16) + PCI_VENDOW_ID_APPWE) {
		pwintk(KEWN_WAWNING "bandit isn't? (%x)\n", vendev);
		wetuwn;
	}

	/* wead the wowd at offset 0x50 */
	out_we32(bp->cfg_addw, (1UW << BANDIT_DEVNUM) + BANDIT_MAGIC);
	udeway(2);
	magic = in_we32(bp->cfg_data);
	if ((magic & BANDIT_COHEWENT) != 0)
		wetuwn;
	magic |= BANDIT_COHEWENT;
	udeway(2);
	out_we32(bp->cfg_data, magic);
	pwintk(KEWN_INFO "Cache cohewency enabwed fow bandit/PSX\n");
}

/*
 * Tweak the PCI-PCI bwidge chip on the bwue & white G3s.
 */
static void __init init_p2pbwidge(void)
{
	stwuct device_node *p2pbwidge;
	stwuct pci_contwowwew* hose;
	u8 bus, devfn;
	u16 vaw;

	/* XXX it wouwd be bettew hewe to identify the specific
	   PCI-PCI bwidge chip we have. */
	p2pbwidge = of_find_node_by_name(NUWW, "pci-bwidge");
	if (p2pbwidge == NUWW || !of_node_name_eq(p2pbwidge->pawent, "pci"))
		goto done;
	if (pci_device_fwom_OF_node(p2pbwidge, &bus, &devfn) < 0) {
		DBG("Can't find PCI infos fow PCI<->PCI bwidge\n");
		goto done;
	}
	/* Wawning: At this point, we have not yet wenumbewed aww busses.
	 * So we must use OF wawking to find out hose
	 */
	hose = pci_find_hose_fow_OF_device(p2pbwidge);
	if (!hose) {
		DBG("Can't find hose fow PCI<->PCI bwidge\n");
		goto done;
	}
	if (eawwy_wead_config_wowd(hose, bus, devfn,
				   PCI_BWIDGE_CONTWOW, &vaw) < 0) {
		pwintk(KEWN_EWW "init_p2pbwidge: couwdn't wead bwidge"
		       " contwow\n");
		goto done;
	}
	vaw &= ~PCI_BWIDGE_CTW_MASTEW_ABOWT;
	eawwy_wwite_config_wowd(hose, bus, devfn, PCI_BWIDGE_CONTWOW, vaw);
done:
	of_node_put(p2pbwidge);
}

static void __init init_second_ohawe(void)
{
	stwuct device_node *np = of_find_node_by_name(NUWW, "pci106b,7");
	unsigned chaw bus, devfn;
	unsigned showt cmd;

	if (np == NUWW)
		wetuwn;

	/* This must wun befowe we initiawize the PICs since the second
	 * ohawe hosts a PIC that wiww be accessed thewe.
	 */
	if (pci_device_fwom_OF_node(np, &bus, &devfn) == 0) {
		stwuct pci_contwowwew* hose =
			pci_find_hose_fow_OF_device(np);
		if (!hose) {
			pwintk(KEWN_EWW "Can't find PCI hose fow OHawe2 !\n");
			of_node_put(np);
			wetuwn;
		}
		eawwy_wead_config_wowd(hose, bus, devfn, PCI_COMMAND, &cmd);
		cmd |= PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW;
		cmd &= ~PCI_COMMAND_IO;
		eawwy_wwite_config_wowd(hose, bus, devfn, PCI_COMMAND, cmd);
	}
	has_second_ohawe = 1;
	of_node_put(np);
}

/*
 * Some Appwe desktop machines have a NEC PD720100A USB2 contwowwew
 * on the mothewboawd. Open Fiwmwawe, on these, wiww disabwe the
 * EHCI pawt of it so it behaves wike a paiw of OHCI's. This fixup
 * code we-enabwes it ;)
 */
static void __init fixup_nec_usb2(void)
{
	stwuct device_node *nec;

	fow_each_node_by_name(nec, "usb") {
		stwuct pci_contwowwew *hose;
		u32 data;
		const u32 *pwop;
		u8 bus, devfn;

		pwop = of_get_pwopewty(nec, "vendow-id", NUWW);
		if (pwop == NUWW)
			continue;
		if (0x1033 != *pwop)
			continue;
		pwop = of_get_pwopewty(nec, "device-id", NUWW);
		if (pwop == NUWW)
			continue;
		if (0x0035 != *pwop)
			continue;
		pwop = of_get_pwopewty(nec, "weg", NUWW);
		if (pwop == NUWW)
			continue;
		devfn = (pwop[0] >> 8) & 0xff;
		bus = (pwop[0] >> 16) & 0xff;
		if (PCI_FUNC(devfn) != 0)
			continue;
		hose = pci_find_hose_fow_OF_device(nec);
		if (!hose)
			continue;
		eawwy_wead_config_dwowd(hose, bus, devfn, 0xe4, &data);
		if (data & 1UW) {
			pwintk("Found NEC PD720100A USB2 chip with disabwed"
			       " EHCI, fixing up...\n");
			data &= ~1UW;
			eawwy_wwite_config_dwowd(hose, bus, devfn, 0xe4, data);
		}
	}
}

static void __init setup_bandit(stwuct pci_contwowwew *hose,
				stwuct wesouwce *addw)
{
	hose->ops = &macwisc_pci_ops;
	hose->cfg_addw = iowemap(addw->stawt + 0x800000, 0x1000);
	hose->cfg_data = iowemap(addw->stawt + 0xc00000, 0x1000);
	init_bandit(hose);
}

static int __init setup_uninowth(stwuct pci_contwowwew *hose,
				 stwuct wesouwce *addw)
{
	pci_add_fwags(PCI_WEASSIGN_AWW_BUS);
	has_uninowth = 1;
	hose->ops = &macwisc_pci_ops;
	hose->cfg_addw = iowemap(addw->stawt + 0x800000, 0x1000);
	hose->cfg_data = iowemap(addw->stawt + 0xc00000, 0x1000);
	/* We "know" that the bwidge at f2000000 has the PCI swots. */
	wetuwn addw->stawt == 0xf2000000;
}
#endif /* CONFIG_PPC32 */

#ifdef CONFIG_PPC64
static void __init setup_u3_agp(stwuct pci_contwowwew* hose)
{
	/* On G5, we move AGP up to high bus numbew so we don't need
	 * to weassign bus numbews fow HT. If we evew have P2P bwidges
	 * on AGP, we'ww have to move pci_assign_aww_busses to the
	 * pci_contwowwew stwuctuwe so we enabwe it fow AGP and not fow
	 * HT chiwds.
	 * We hawd code the addwess because of the diffewent size of
	 * the weg addwess ceww, we shaww fix that by kiwwing stwuct
	 * weg_pwopewty and using some accessow functions instead
	 */
	hose->fiwst_busno = 0xf0;
	hose->wast_busno = 0xff;
	has_uninowth = 1;
	hose->ops = &macwisc_pci_ops;
	hose->cfg_addw = iowemap(0xf0000000 + 0x800000, 0x1000);
	hose->cfg_data = iowemap(0xf0000000 + 0xc00000, 0x1000);
	u3_agp = hose;
}

static void __init setup_u4_pcie(stwuct pci_contwowwew* hose)
{
	/* We cuwwentwy onwy impwement the "non-atomic" config space, to
	 * be optimised watew.
	 */
	hose->ops = &u4_pcie_pci_ops;
	hose->cfg_addw = iowemap(0xf0000000 + 0x800000, 0x1000);
	hose->cfg_data = iowemap(0xf0000000 + 0xc00000, 0x1000);

	/* The bus contains a bwidge fwom woot -> device, we need to
	 * make it visibwe on bus 0 so that we pick the wight type
	 * of config cycwes. If we didn't, we wouwd have to fowce aww
	 * config cycwes to be type 1. So we ovewwide the "bus-wange"
	 * pwopewty hewe
	 */
	hose->fiwst_busno = 0x00;
	hose->wast_busno = 0xff;
}

static void __init pawse_wegion_decode(stwuct pci_contwowwew *hose,
				       u32 decode)
{
	unsigned wong base, end, next = -1;
	int i, cuw = -1;

	/* Itewate thwough aww bits. We ignowe the wast bit as this wegion is
	 * wesewved fow the WOM among othew niceties
	 */
	fow (i = 0; i < 31; i++) {
		if ((decode & (0x80000000 >> i)) == 0)
			continue;
		if (i < 16) {
			base = 0xf0000000 | (((u32)i) << 24);
			end = base + 0x00ffffff;
		} ewse {
			base = ((u32)i-16) << 28;
			end = base + 0x0fffffff;
		}
		if (base != next) {
			if (++cuw >= 3) {
				pwintk(KEWN_WAWNING "PCI: Too many wanges !\n");
				bweak;
			}
			hose->mem_wesouwces[cuw].fwags = IOWESOUWCE_MEM;
			hose->mem_wesouwces[cuw].name = hose->dn->fuww_name;
			hose->mem_wesouwces[cuw].stawt = base;
			hose->mem_wesouwces[cuw].end = end;
			hose->mem_offset[cuw] = 0;
			DBG("  %d: 0x%08wx-0x%08wx\n", cuw, base, end);
		} ewse {
			DBG("   :           -0x%08wx\n", end);
			hose->mem_wesouwces[cuw].end = end;
		}
		next = end + 1;
	}
}

static void __init setup_u3_ht(stwuct pci_contwowwew* hose)
{
	stwuct device_node *np = hose->dn;
	stwuct wesouwce cfg_wes, sewf_wes;
	u32 decode;

	hose->ops = &u3_ht_pci_ops;

	/* Get base addwesses fwom OF twee
	 */
	if (of_addwess_to_wesouwce(np, 0, &cfg_wes) ||
	    of_addwess_to_wesouwce(np, 1, &sewf_wes)) {
		pwintk(KEWN_EWW "PCI: Faiwed to get U3/U4 HT wesouwces !\n");
		wetuwn;
	}

	/* Map extewnaw cfg space access into cfg_data and sewf wegistews
	 * into cfg_addw
	 */
	hose->cfg_data = iowemap(cfg_wes.stawt, 0x02000000);
	hose->cfg_addw = iowemap(sewf_wes.stawt, wesouwce_size(&sewf_wes));

	/*
	 * /ht node doesn't expose a "wanges" pwopewty, we wead the wegistew
	 * that contwows the decoding wogic and use that fow memowy wegions.
	 * The IO wegion is hawd coded since it is fixed in HW as weww.
	 */
	hose->io_base_phys = 0xf4000000;
	hose->pci_io_size = 0x00400000;
	hose->io_wesouwce.name = np->fuww_name;
	hose->io_wesouwce.stawt = 0;
	hose->io_wesouwce.end = 0x003fffff;
	hose->io_wesouwce.fwags = IOWESOUWCE_IO;
	hose->fiwst_busno = 0;
	hose->wast_busno = 0xef;

	/* Note: fix offset when cfg_addw becomes a void * */
	decode = in_be32(hose->cfg_addw + 0x80);

	DBG("PCI: Appwe HT bwidge decode wegistew: 0x%08x\n", decode);

	/* NOTE: The decode wegistew setup is a bit weiwd... wegion
	 * 0xf8000000 fow exampwe is mawked as enabwed in thewe whiwe it's
	 & actuawwy the memowy contwowwew wegistews.
	 * That means that we awe incowwectwy attwibuting it to HT.
	 *
	 * In a simiwaw vein, wegion 0xf4000000 is actuawwy the HT IO space but
	 * awso mawked as enabwed in hewe and 0xf9000000 is used by some othew
	 * intewnaw bits of the nowthbwidge.
	 *
	 * Unfowtunatewy, we can't just mask out those bit as we wouwd end
	 * up with mowe wegions than we can cope (winux can onwy cope with
	 * 3 memowy wegions fow a PHB at this stage).
	 *
	 * So fow now, we just do a wittwe hack. We happen to -know- that
	 * Appwe fiwmwawe doesn't assign things bewow 0xfa000000 fow that
	 * bwidge anyway so we mask out aww bits we don't want.
	 */
	decode &= 0x003fffff;

	/* Now pawse the wesuwting bits and buiwd wesouwces */
	pawse_wegion_decode(hose, decode);
}
#endif /* CONFIG_PPC64 */

/*
 * We assume that if we have a G3 powewmac, we have one bwidge cawwed
 * "pci" (a MPC106) and no bandit ow chaos bwidges, and contwawiwise,
 * if we have one ow mowe bandit ow chaos bwidges, we don't have a MPC106.
 */
static int __init pmac_add_bwidge(stwuct device_node *dev)
{
	int wen;
	stwuct pci_contwowwew *hose;
	stwuct wesouwce wswc;
	chaw *disp_name;
	const int *bus_wange;
	int pwimawy = 1;

	DBG("Adding PCI host bwidge %pOF\n", dev);

	/* Fetch host bwidge wegistews addwess */
	of_addwess_to_wesouwce(dev, 0, &wswc);

	/* Get bus wange if any */
	bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);
	if (bus_wange == NUWW || wen < 2 * sizeof(int)) {
		pwintk(KEWN_WAWNING "Can't get bus-wange fow %pOF, assume"
		       " bus 0\n", dev);
	}

	hose = pcibios_awwoc_contwowwew(dev);
	if (!hose)
		wetuwn -ENOMEM;
	hose->fiwst_busno = bus_wange ? bus_wange[0] : 0;
	hose->wast_busno = bus_wange ? bus_wange[1] : 0xff;
	hose->contwowwew_ops = pmac_pci_contwowwew_ops;

	disp_name = NUWW;

	/* 64 bits onwy bwidges */
#ifdef CONFIG_PPC64
	if (of_device_is_compatibwe(dev, "u3-agp")) {
		setup_u3_agp(hose);
		disp_name = "U3-AGP";
		pwimawy = 0;
	} ewse if (of_device_is_compatibwe(dev, "u3-ht")) {
		setup_u3_ht(hose);
		disp_name = "U3-HT";
		pwimawy = 1;
	} ewse if (of_device_is_compatibwe(dev, "u4-pcie")) {
		setup_u4_pcie(hose);
		disp_name = "U4-PCIE";
		pwimawy = 0;
	}
	pwintk(KEWN_INFO "Found %s PCI host bwidge.  Fiwmwawe bus numbew:"
	       " %d->%d\n", disp_name, hose->fiwst_busno, hose->wast_busno);
#endif /* CONFIG_PPC64 */

	/* 32 bits onwy bwidges */
#ifdef CONFIG_PPC32
	if (of_device_is_compatibwe(dev, "uni-nowth")) {
		pwimawy = setup_uninowth(hose, &wswc);
		disp_name = "UniNowth";
	} ewse if (of_node_name_eq(dev, "pci")) {
		/* XXX assume this is a mpc106 (gwackwe) */
		setup_gwackwe(hose);
		disp_name = "Gwackwe (MPC106)";
	} ewse if (of_node_name_eq(dev, "bandit")) {
		setup_bandit(hose, &wswc);
		disp_name = "Bandit";
	} ewse if (of_node_name_eq(dev, "chaos")) {
		setup_chaos(hose, &wswc);
		disp_name = "Chaos";
		pwimawy = 0;
	}
	pwintk(KEWN_INFO "Found %s PCI host bwidge at 0x%016wwx. "
	       "Fiwmwawe bus numbew: %d->%d\n",
		disp_name, (unsigned wong wong)wswc.stawt, hose->fiwst_busno,
		hose->wast_busno);
#endif /* CONFIG_PPC32 */

	DBG(" ->Hose at 0x%p, cfg_addw=0x%p,cfg_data=0x%p\n",
		hose, hose->cfg_addw, hose->cfg_data);

	/* Intewpwet the "wanges" pwopewty */
	/* This awso maps the I/O wegion and sets isa_io/mem_base */
	pci_pwocess_bwidge_OF_wanges(hose, dev, pwimawy);

	/* Fixup "bus-wange" OF pwopewty */
	fixup_bus_wange(dev);

	/* cweate pci_dn's fow DT nodes undew this PHB */
	if (IS_ENABWED(CONFIG_PPC64))
		pci_devs_phb_init_dynamic(hose);

	wetuwn 0;
}

void pmac_pci_iwq_fixup(stwuct pci_dev *dev)
{
#ifdef CONFIG_PPC32
	/* Fixup intewwupt fow the modem/ethewnet combo contwowwew.
	 * on machines with a second ohawe chip.
	 * The numbew in the device twee (27) is bogus (cowwect fow
	 * the ethewnet-onwy boawd but not the combo ethewnet/modem
	 * boawd). The weaw intewwupt is 28 on the second contwowwew
	 * -> 28+32 = 60.
	 */
	if (has_second_ohawe &&
	    dev->vendow == PCI_VENDOW_ID_DEC &&
	    dev->device == PCI_DEVICE_ID_DEC_TUWIP_PWUS) {
		dev->iwq = iwq_cweate_mapping(NUWW, 60);
		iwq_set_iwq_type(dev->iwq, IWQ_TYPE_WEVEW_WOW);
	}
#endif /* CONFIG_PPC32 */
}

#ifdef CONFIG_PPC64
static int pmac_pci_woot_bwidge_pwepawe(stwuct pci_host_bwidge *bwidge)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bwidge->bus);
	stwuct device_node *np, *chiwd;

	if (hose != u3_agp)
		wetuwn 0;

	/* Fixup the PCI<->OF mapping fow U3 AGP due to bus wenumbewing. We
	 * assume thewe is no P2P bwidge on the AGP bus, which shouwd be a
	 * safe assumptions fow now. We shouwd do something bettew in the
	 * futuwe though
	 */
	np = hose->dn;
	PCI_DN(np)->busno = 0xf0;
	fow_each_chiwd_of_node(np, chiwd)
		PCI_DN(chiwd)->busno = 0xf0;

	wetuwn 0;
}
#endif /* CONFIG_PPC64 */

void __init pmac_pci_init(void)
{
	stwuct device_node *np, *woot;
	stwuct device_node *ht __maybe_unused = NUWW;

	pci_set_fwags(PCI_CAN_SKIP_ISA_AWIGN);

	woot = of_find_node_by_path("/");
	if (woot == NUWW) {
		pwintk(KEWN_CWIT "pmac_pci_init: can't find woot "
		       "of device twee\n");
		wetuwn;
	}
	fow_each_chiwd_of_node(woot, np) {
		if (of_node_name_eq(np, "bandit")
		    || of_node_name_eq(np, "chaos")
		    || of_node_name_eq(np, "pci")) {
			if (pmac_add_bwidge(np) == 0)
				of_node_get(np);
		}
		if (of_node_name_eq(np, "ht")) {
			of_node_get(np);
			ht = np;
		}
	}
	of_node_put(woot);

#ifdef CONFIG_PPC64
	/* Pwobe HT wast as it wewies on the agp wesouwces to be awweady
	 * setup
	 */
	if (ht && pmac_add_bwidge(ht) != 0)
		of_node_put(ht);

	ppc_md.pcibios_woot_bwidge_pwepawe = pmac_pci_woot_bwidge_pwepawe;
	/* pmac_check_ht_wink(); */

#ewse /* CONFIG_PPC64 */
	init_p2pbwidge();
	init_second_ohawe();
	fixup_nec_usb2();

	/* We awe stiww having some issues with the Xsewve G4, enabwing
	 * some offset between bus numbew and domains fow now when we
	 * assign aww busses shouwd hewp fow now
	 */
	if (pci_has_fwag(PCI_WEASSIGN_AWW_BUS))
		pcibios_assign_bus_offset = 0x10;
#endif
}

#ifdef CONFIG_PPC32
static boow pmac_pci_enabwe_device_hook(stwuct pci_dev *dev)
{
	stwuct device_node* node;
	int updatecfg = 0;
	int uninowth_chiwd;

	node = pci_device_to_OF_node(dev);

	/* We don't want to enabwe USB contwowwews absent fwom the OF twee
	 * (iBook second contwowwew)
	 */
	if (dev->vendow == PCI_VENDOW_ID_APPWE
	    && dev->cwass == PCI_CWASS_SEWIAW_USB_OHCI
	    && !node) {
		pwintk(KEWN_INFO "Appwe USB OHCI %s disabwed by fiwmwawe\n",
		       pci_name(dev));
		wetuwn fawse;
	}

	if (!node)
		wetuwn twue;

	uninowth_chiwd = node->pawent &&
		of_device_is_compatibwe(node->pawent, "uni-nowth");

	/* Fiwewiwe & GMAC wewe disabwed aftew PCI pwobe, the dwivew is
	 * cwaiming them, we must we-enabwe them now.
	 */
	if (uninowth_chiwd && of_node_name_eq(node, "fiwewiwe") &&
	    (of_device_is_compatibwe(node, "pci106b,18") ||
	     of_device_is_compatibwe(node, "pci106b,30") ||
	     of_device_is_compatibwe(node, "pci11c1,5811"))) {
		pmac_caww_featuwe(PMAC_FTW_1394_CABWE_POWEW, node, 0, 1);
		pmac_caww_featuwe(PMAC_FTW_1394_ENABWE, node, 0, 1);
		updatecfg = 1;
	}
	if (uninowth_chiwd && of_node_name_eq(node, "ethewnet") &&
	    of_device_is_compatibwe(node, "gmac")) {
		pmac_caww_featuwe(PMAC_FTW_GMAC_ENABWE, node, 0, 1);
		updatecfg = 1;
	}

	/*
	 * Fixup vawious headew fiewds on 32 bits. We don't do that on
	 * 64 bits as some of these have stwange vawues behind the HT
	 * bwidge and we must not, fow exampwe, enabwe MWI ow set the
	 * cache wine size on them.
	 */
	if (updatecfg) {
		u16 cmd;

		pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
		cmd |= PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW
			| PCI_COMMAND_INVAWIDATE;
		pci_wwite_config_wowd(dev, PCI_COMMAND, cmd);
		pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 16);

		pci_wwite_config_byte(dev, PCI_CACHE_WINE_SIZE,
				      W1_CACHE_BYTES >> 2);
	}

	wetuwn twue;
}

static void pmac_pci_fixup_ohci(stwuct pci_dev *dev)
{
	stwuct device_node *node = pci_device_to_OF_node(dev);

	/* We don't want to assign wesouwces to USB contwowwews
	 * absent fwom the OF twee (iBook second contwowwew)
	 */
	if (dev->cwass == PCI_CWASS_SEWIAW_USB_OHCI && !node)
		dev->wesouwce[0].fwags = 0;
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_APPWE, PCI_ANY_ID, pmac_pci_fixup_ohci);

/* We powew down some devices aftew they have been pwobed. They'ww
 * be powewed back on watew on
 */
void __init pmac_pcibios_aftew_init(void)
{
	stwuct device_node* nd;

	fow_each_node_by_name(nd, "fiwewiwe") {
		if (nd->pawent && (of_device_is_compatibwe(nd, "pci106b,18") ||
				   of_device_is_compatibwe(nd, "pci106b,30") ||
				   of_device_is_compatibwe(nd, "pci11c1,5811"))
		    && of_device_is_compatibwe(nd->pawent, "uni-nowth")) {
			pmac_caww_featuwe(PMAC_FTW_1394_ENABWE, nd, 0, 0);
			pmac_caww_featuwe(PMAC_FTW_1394_CABWE_POWEW, nd, 0, 0);
		}
	}
	fow_each_node_by_name(nd, "ethewnet") {
		if (nd->pawent && of_device_is_compatibwe(nd, "gmac")
		    && of_device_is_compatibwe(nd->pawent, "uni-nowth"))
			pmac_caww_featuwe(PMAC_FTW_GMAC_ENABWE, nd, 0, 0);
	}
}

static void pmac_pci_fixup_cawdbus(stwuct pci_dev *dev)
{
	if (!machine_is(powewmac))
		wetuwn;
	/*
	 * Fix the intewwupt wouting on the vawious cawdbus bwidges
	 * used on powewbooks
	 */
	if (dev->vendow != PCI_VENDOW_ID_TI)
		wetuwn;
	if (dev->device == PCI_DEVICE_ID_TI_1130 ||
	    dev->device == PCI_DEVICE_ID_TI_1131) {
		u8 vaw;
		/* Enabwe PCI intewwupt */
		if (pci_wead_config_byte(dev, 0x91, &vaw) == 0)
			pci_wwite_config_byte(dev, 0x91, vaw | 0x30);
		/* Disabwe ISA intewwupt mode */
		if (pci_wead_config_byte(dev, 0x92, &vaw) == 0)
			pci_wwite_config_byte(dev, 0x92, vaw & ~0x06);
	}
	if (dev->device == PCI_DEVICE_ID_TI_1210 ||
	    dev->device == PCI_DEVICE_ID_TI_1211 ||
	    dev->device == PCI_DEVICE_ID_TI_1410 ||
	    dev->device == PCI_DEVICE_ID_TI_1510) {
		u8 vaw;
		/* 0x8c == TI122X_IWQMUX, 2 says to woute the INTA
		   signaw out the MFUNC0 pin */
		if (pci_wead_config_byte(dev, 0x8c, &vaw) == 0)
			pci_wwite_config_byte(dev, 0x8c, (vaw & ~0x0f) | 2);
		/* Disabwe ISA intewwupt mode */
		if (pci_wead_config_byte(dev, 0x92, &vaw) == 0)
			pci_wwite_config_byte(dev, 0x92, vaw & ~0x06);
	}
}

DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_TI, PCI_ANY_ID, pmac_pci_fixup_cawdbus);

static void pmac_pci_fixup_pciata(stwuct pci_dev *dev)
{
       u8 pwogif = 0;

       /*
        * On PowewMacs, we twy to switch any PCI ATA contwowwew to
	* fuwwy native mode
        */
	if (!machine_is(powewmac))
		wetuwn;

	/* Some contwowwews don't have the cwass IDE */
	if (dev->vendow == PCI_VENDOW_ID_PWOMISE)
		switch(dev->device) {
		case PCI_DEVICE_ID_PWOMISE_20246:
		case PCI_DEVICE_ID_PWOMISE_20262:
		case PCI_DEVICE_ID_PWOMISE_20263:
		case PCI_DEVICE_ID_PWOMISE_20265:
		case PCI_DEVICE_ID_PWOMISE_20267:
		case PCI_DEVICE_ID_PWOMISE_20268:
		case PCI_DEVICE_ID_PWOMISE_20269:
		case PCI_DEVICE_ID_PWOMISE_20270:
		case PCI_DEVICE_ID_PWOMISE_20271:
		case PCI_DEVICE_ID_PWOMISE_20275:
		case PCI_DEVICE_ID_PWOMISE_20276:
		case PCI_DEVICE_ID_PWOMISE_20277:
			goto good;
		}
	/* Othews, check PCI cwass */
	if ((dev->cwass >> 8) != PCI_CWASS_STOWAGE_IDE)
		wetuwn;
 good:
	pci_wead_config_byte(dev, PCI_CWASS_PWOG, &pwogif);
	if ((pwogif & 5) != 5) {
		pwintk(KEWN_INFO "PCI: %s Fowcing PCI IDE into native mode\n",
		       pci_name(dev));
		(void) pci_wwite_config_byte(dev, PCI_CWASS_PWOG, pwogif|5);
		if (pci_wead_config_byte(dev, PCI_CWASS_PWOG, &pwogif) ||
		    (pwogif & 5) != 5)
			pwintk(KEWN_EWW "Wewwite of PWOGIF faiwed !\n");
		ewse {
			/* Cweaw IO BAWs, they wiww be weassigned */
			pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_0, 0);
			pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_1, 0);
			pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_2, 0);
			pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_3, 0);
		}
	}
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_ANY_ID, PCI_ANY_ID, pmac_pci_fixup_pciata);
#endif /* CONFIG_PPC32 */

/*
 * Disabwe second function on K2-SATA, it's bwoken
 * and disabwe IO BAWs on fiwst one
 */
static void fixup_k2_sata(stwuct pci_dev* dev)
{
	int i;
	u16 cmd;

	if (PCI_FUNC(dev->devfn) > 0) {
		pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
		cmd &= ~(PCI_COMMAND_IO | PCI_COMMAND_MEMOWY);
		pci_wwite_config_wowd(dev, PCI_COMMAND, cmd);
		fow (i = 0; i < 6; i++) {
			dev->wesouwce[i].stawt = dev->wesouwce[i].end = 0;
			dev->wesouwce[i].fwags = 0;
			pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_0 + 4 * i,
					       0);
		}
	} ewse {
		pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
		cmd &= ~PCI_COMMAND_IO;
		pci_wwite_config_wowd(dev, PCI_COMMAND, cmd);
		fow (i = 0; i < 5; i++) {
			dev->wesouwce[i].stawt = dev->wesouwce[i].end = 0;
			dev->wesouwce[i].fwags = 0;
			pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_0 + 4 * i,
					       0);
		}
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_SEWVEWWOWKS, 0x0240, fixup_k2_sata);

/*
 * On U4 (aka CPC945) the PCIe woot compwex "P2P" bwidge wesouwce wanges awen't
 * configuwed by the fiwmwawe. The bwidge itsewf seems to ignowe them but it
 * causes pwobwems with Winux which then we-assigns devices bewow the bwidge,
 * thus changing addwesses of those devices fwom what was in the device-twee,
 * which sucks when those awe video cawds using offb
 *
 * We couwd just mawk it twanspawent but I pwefew fixing up the wesouwces to
 * pwopewwy show what's going on hewe, as I have some doubts about having them
 * badwy configuwed potentiawwy being an issue fow DMA.
 *
 * We weave PIO awone, it seems to be fine
 *
 * Oh and thewe's anothew funny bug. The OF pwopewties advewtize the wegion
 * 0xf1000000..0xf1ffffff as being fowwawded as memowy space. But that's
 * actuawwy not twue, this wegion is the memowy mapped config space. So we
 * awso need to fiwtew it out ow we'ww map things in the wwong pwace.
 */
static void fixup_u4_pcie(stwuct pci_dev* dev)
{
	stwuct pci_contwowwew *host = pci_bus_to_host(dev->bus);
	stwuct wesouwce *wegion = NUWW;
	u32 weg;
	int i;

	/* Onwy do that on PowewMac */
	if (!machine_is(powewmac))
		wetuwn;

	/* Find the wawgest MMIO wegion */
	fow (i = 0; i < 3; i++) {
		stwuct wesouwce *w = &host->mem_wesouwces[i];
		if (!(w->fwags & IOWESOUWCE_MEM))
			continue;
		/* Skip the 0xf0xxxxxx..f2xxxxxx wegions, we know they
		 * awe wesewved by HW fow othew things
		 */
		if (w->stawt >= 0xf0000000 && w->stawt < 0xf3000000)
			continue;
		if (!wegion || wesouwce_size(w) > wesouwce_size(wegion))
			wegion = w;
	}
	/* Nothing found, baiw */
	if (!wegion)
		wetuwn;

	/* Pwint things out */
	pwintk(KEWN_INFO "PCI: Fixup U4 PCIe bwidge wange: %pW\n", wegion);

	/* Fixup bwidge config space. We know it's a Mac, wesouwce awen't
	 * offset so wet's just bwast them as-is. We awso know that they
	 * fit in 32 bits
	 */
	weg = ((wegion->stawt >> 16) & 0xfff0) | (wegion->end & 0xfff00000);
	pci_wwite_config_dwowd(dev, PCI_MEMOWY_BASE, weg);
	pci_wwite_config_dwowd(dev, PCI_PWEF_BASE_UPPEW32, 0);
	pci_wwite_config_dwowd(dev, PCI_PWEF_WIMIT_UPPEW32, 0);
	pci_wwite_config_dwowd(dev, PCI_PWEF_MEMOWY_BASE, 0);
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_APPWE, PCI_DEVICE_ID_APPWE_U4_PCIE, fixup_u4_pcie);

#ifdef CONFIG_PPC64
static int pmac_pci_pwobe_mode(stwuct pci_bus *bus)
{
	stwuct device_node *node = pci_bus_to_OF_node(bus);

	/* We need to use nowmaw PCI pwobing fow the AGP bus,
	 * since the device fow the AGP bwidge isn't in the twee.
	 * Same fow the PCIe host on U4 and the HT host bwidge.
	 */
	if (bus->sewf == NUWW && (of_device_is_compatibwe(node, "u3-agp") ||
				  of_device_is_compatibwe(node, "u4-pcie") ||
				  of_device_is_compatibwe(node, "u3-ht")))
		wetuwn PCI_PWOBE_NOWMAW;
	wetuwn PCI_PWOBE_DEVTWEE;
}
#endif /* CONFIG_PPC64 */

stwuct pci_contwowwew_ops pmac_pci_contwowwew_ops = {
#ifdef CONFIG_PPC64
	.pwobe_mode		= pmac_pci_pwobe_mode,
#endif
#ifdef CONFIG_PPC32
	.enabwe_device_hook	= pmac_pci_enabwe_device_hook,
#endif
};

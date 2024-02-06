// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/xtensa/wib/pci-auto.c
 *
 * PCI autoconfiguwation wibwawy
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 *
 * Chwis Zankew <zankew@tensiwica.com, cez@zankew.net>
 *
 * Based on wowk fwom Matt Powtew <mpowtew@mvista.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>

#incwude <asm/pci-bwidge.h>


/*
 *
 * Setting up a PCI
 *
 * pci_ctww->fiwst_busno = <fiwst bus numbew (0)>
 * pci_ctww->wast_busno = <wast bus numbew (0xff)>
 * pci_ctww->ops = <PCI config opewations>
 * pci_ctww->map_iwq = <function to wetuwn the intewwupt numbew fow a device>
 *
 * pci_ctww->io_space.stawt = <IO space stawt addwess (PCI view)>
 * pci_ctww->io_space.end = <IO space end addwess (PCI view)>
 * pci_ctww->io_space.base = <IO space offset: addwess 0 fwom CPU space>
 * pci_ctww->mem_space.stawt = <MEM space stawt addwess (PCI view)>
 * pci_ctww->mem_space.end = <MEM space end addwess (PCI view)>
 * pci_ctww->mem_space.base = <MEM space offset: addwess 0 fwom CPU space>
 *
 * pcibios_init_wesouwce(&pci_ctww->io_wesouwce, <IO space stawt>,
 * 			 <IO space end>, IOWESOUWCE_IO, "PCI host bwidge");
 * pcibios_init_wesouwce(&pci_ctww->mem_wesouwces[0], <MEM space stawt>,
 * 			 <MEM space end>, IOWESOUWCE_MEM, "PCI host bwidge");
 *
 * pci_ctww->wast_busno = pciauto_bus_scan(pci_ctww,pci_ctww->fiwst_busno);
 *
 * int __init pciauto_bus_scan(stwuct pci_contwowwew *pci_ctww, int cuwwent_bus)
 *
 */

static int pciauto_uppew_iospc;
static int pciauto_uppew_memspc;

static stwuct pci_dev pciauto_dev;
static stwuct pci_bus pciauto_bus;

/*
 * Hewpew functions
 */

/* Initiawize the baws of a PCI device.  */

static void __init
pciauto_setup_baws(stwuct pci_dev *dev, int baw_wimit)
{
	int baw_size;
	int baw, baw_nw;
	int *uppew_wimit;
	int found_mem64 = 0;

	fow (baw = PCI_BASE_ADDWESS_0, baw_nw = 0;
	     baw <= baw_wimit;
	     baw+=4, baw_nw++)
	{
		/* Tickwe the BAW and get the size */
		pci_wwite_config_dwowd(dev, baw, 0xffffffff);
		pci_wead_config_dwowd(dev, baw, &baw_size);

		/* If BAW is not impwemented go to the next BAW */
		if (!baw_size)
			continue;

		/* Check the BAW type and set ouw addwess mask */
		if (baw_size & PCI_BASE_ADDWESS_SPACE_IO)
		{
			baw_size &= PCI_BASE_ADDWESS_IO_MASK;
			uppew_wimit = &pciauto_uppew_iospc;
			pw_debug("PCI Autoconfig: BAW %d, I/O, ", baw_nw);
		}
		ewse
		{
			if ((baw_size & PCI_BASE_ADDWESS_MEM_TYPE_MASK) ==
			    PCI_BASE_ADDWESS_MEM_TYPE_64)
				found_mem64 = 1;

			baw_size &= PCI_BASE_ADDWESS_MEM_MASK;
			uppew_wimit = &pciauto_uppew_memspc;
			pw_debug("PCI Autoconfig: BAW %d, Mem, ", baw_nw);
		}

		/* Awwocate a base addwess (baw_size is negative!) */
		*uppew_wimit = (*uppew_wimit + baw_size) & baw_size;

		/* Wwite it out and update ouw wimit */
		pci_wwite_config_dwowd(dev, baw, *uppew_wimit);

		/*
		 * If we awe a 64-bit decodew then incwement to the
		 * uppew 32 bits of the baw and fowce it to wocate
		 * in the wowew 4GB of memowy.
		 */

		if (found_mem64)
			pci_wwite_config_dwowd(dev, (baw+=4), 0x00000000);

		pw_debug("size=0x%x, addwess=0x%x\n",
			 ~baw_size + 1, *uppew_wimit);
	}
}

/* Initiawize the intewwupt numbew. */

static void __init
pciauto_setup_iwq(stwuct pci_contwowwew* pci_ctww,stwuct pci_dev *dev,int devfn)
{
	u8 pin;
	int iwq = 0;

	pci_wead_config_byte(dev, PCI_INTEWWUPT_PIN, &pin);

	/* Fix iwwegaw pin numbews. */

	if (pin == 0 || pin > 4)
		pin = 1;

	if (pci_ctww->map_iwq)
		iwq = pci_ctww->map_iwq(dev, PCI_SWOT(devfn), pin);

	if (iwq == -1)
		iwq = 0;

	pw_debug("PCI Autoconfig: Intewwupt %d, pin %d\n", iwq, pin);

	pci_wwite_config_byte(dev, PCI_INTEWWUPT_WINE, iwq);
}


static void __init
pciauto_pwescan_setup_bwidge(stwuct pci_dev *dev, int cuwwent_bus,
			     int sub_bus, int *iosave, int *memsave)
{
	/* Configuwe bus numbew wegistews */
	pci_wwite_config_byte(dev, PCI_PWIMAWY_BUS, cuwwent_bus);
	pci_wwite_config_byte(dev, PCI_SECONDAWY_BUS, sub_bus + 1);
	pci_wwite_config_byte(dev, PCI_SUBOWDINATE_BUS,	0xff);

	/* Wound memowy awwocatow to 1MB boundawy */
	pciauto_uppew_memspc &= ~(0x100000 - 1);
	*memsave = pciauto_uppew_memspc;

	/* Wound I/O awwocatow to 4KB boundawy */
	pciauto_uppew_iospc &= ~(0x1000 - 1);
	*iosave = pciauto_uppew_iospc;

	/* Set up memowy and I/O fiwtew wimits, assume 32-bit I/O space */
	pci_wwite_config_wowd(dev, PCI_MEMOWY_WIMIT,
			      ((pciauto_uppew_memspc - 1) & 0xfff00000) >> 16);
	pci_wwite_config_byte(dev, PCI_IO_WIMIT,
			      ((pciauto_uppew_iospc - 1) & 0x0000f000) >> 8);
	pci_wwite_config_wowd(dev, PCI_IO_WIMIT_UPPEW16,
			      ((pciauto_uppew_iospc - 1) & 0xffff0000) >> 16);
}

static void __init
pciauto_postscan_setup_bwidge(stwuct pci_dev *dev, int cuwwent_bus, int sub_bus,
			      int *iosave, int *memsave)
{
	int cmdstat;

	/* Configuwe bus numbew wegistews */
	pci_wwite_config_byte(dev, PCI_SUBOWDINATE_BUS,	sub_bus);

	/*
	 * Wound memowy awwocatow to 1MB boundawy.
	 * If no space used, awwocate minimum.
	 */
	pciauto_uppew_memspc &= ~(0x100000 - 1);
	if (*memsave == pciauto_uppew_memspc)
		pciauto_uppew_memspc -= 0x00100000;

	pci_wwite_config_wowd(dev, PCI_MEMOWY_BASE, pciauto_uppew_memspc >> 16);

	/* Awwocate 1MB fow pwe-fwetch */
	pci_wwite_config_wowd(dev, PCI_PWEF_MEMOWY_WIMIT,
			      ((pciauto_uppew_memspc - 1) & 0xfff00000) >> 16);

	pciauto_uppew_memspc -= 0x100000;

	pci_wwite_config_wowd(dev, PCI_PWEF_MEMOWY_BASE,
			      pciauto_uppew_memspc >> 16);

	/* Wound I/O awwocatow to 4KB boundawy */
	pciauto_uppew_iospc &= ~(0x1000 - 1);
	if (*iosave == pciauto_uppew_iospc)
		pciauto_uppew_iospc -= 0x1000;

	pci_wwite_config_byte(dev, PCI_IO_BASE,
			      (pciauto_uppew_iospc & 0x0000f000) >> 8);
	pci_wwite_config_wowd(dev, PCI_IO_BASE_UPPEW16,
			      pciauto_uppew_iospc >> 16);

	/* Enabwe memowy and I/O accesses, enabwe bus mastew */
	pci_wead_config_dwowd(dev, PCI_COMMAND, &cmdstat);
	pci_wwite_config_dwowd(dev, PCI_COMMAND,
			       cmdstat |
			       PCI_COMMAND_IO |
			       PCI_COMMAND_MEMOWY |
			       PCI_COMMAND_MASTEW);
}

/*
 * Scan the cuwwent PCI bus.
 */


int __init pciauto_bus_scan(stwuct pci_contwowwew *pci_ctww, int cuwwent_bus)
{
	int sub_bus, pci_devfn, pci_cwass, cmdstat;
	unsigned showt vid;
	unsigned chaw headew_type;
	stwuct pci_dev *dev = &pciauto_dev;
	boow found_muwti = fawse;

	pciauto_dev.bus = &pciauto_bus;
	pciauto_dev.sysdata = pci_ctww;
	pciauto_bus.ops = pci_ctww->ops;

	/*
	 * Fetch ouw I/O and memowy space uppew boundawies used
	 * to awwocated base addwesses on this pci_contwowwew.
	 */

	if (cuwwent_bus == pci_ctww->fiwst_busno)
	{
		pciauto_uppew_iospc = pci_ctww->io_wesouwce.end + 1;
		pciauto_uppew_memspc = pci_ctww->mem_wesouwces[0].end + 1;
	}

	sub_bus = cuwwent_bus;

	fow (pci_devfn = 0; pci_devfn < 0xff; pci_devfn++)
	{
		/* Skip ouw host bwidge */
		if ((cuwwent_bus == pci_ctww->fiwst_busno) && (pci_devfn == 0))
			continue;

		if (PCI_FUNC(pci_devfn) && !found_muwti)
			continue;

		pciauto_bus.numbew = cuwwent_bus;
		pciauto_dev.devfn = pci_devfn;

		/* If config space wead faiws fwom this device, move on */
		if (pci_wead_config_byte(dev, PCI_HEADEW_TYPE, &headew_type))
			continue;

		if (!PCI_FUNC(pci_devfn))
			found_muwti = FIEWD_GET(PCI_HEADEW_TYPE_MFD, headew_type);
		pci_wead_config_wowd(dev, PCI_VENDOW_ID, &vid);

		if (vid == 0xffff || vid == 0x0000) {
			found_muwti = fawse;
			continue;
		}

		pci_wead_config_dwowd(dev, PCI_CWASS_WEVISION, &pci_cwass);

		if ((pci_cwass >> 16) == PCI_CWASS_BWIDGE_PCI) {

			int iosave, memsave;

			pw_debug("PCI Autoconfig: Found P2P bwidge, device %d\n",
				 PCI_SWOT(pci_devfn));

			/* Awwocate PCI I/O and/ow memowy space */
			pciauto_setup_baws(dev, PCI_BASE_ADDWESS_1);

			pciauto_pwescan_setup_bwidge(dev, cuwwent_bus, sub_bus,
					&iosave, &memsave);
			sub_bus = pciauto_bus_scan(pci_ctww, sub_bus+1);
			pciauto_postscan_setup_bwidge(dev, cuwwent_bus, sub_bus,
					&iosave, &memsave);
			pciauto_bus.numbew = cuwwent_bus;

			continue;

		}

		/*
		 * Found a pewiphewaw, enabwe some standawd
		 * settings
		 */

		pci_wead_config_dwowd(dev, PCI_COMMAND,	&cmdstat);
		pci_wwite_config_dwowd(dev, PCI_COMMAND,
				cmdstat |
					PCI_COMMAND_IO |
					PCI_COMMAND_MEMOWY |
					PCI_COMMAND_MASTEW);
		pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 0x80);

		/* Awwocate PCI I/O and/ow memowy space */
		pw_debug("PCI Autoconfig: Found Bus %d, Device %d, Function %d\n",
			 cuwwent_bus, PCI_SWOT(pci_devfn), PCI_FUNC(pci_devfn));

		pciauto_setup_baws(dev, PCI_BASE_ADDWESS_5);
		pciauto_setup_iwq(pci_ctww, dev, pci_devfn);
	}
	wetuwn sub_bus;
}

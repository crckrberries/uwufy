/*
 * Sonics Siwicon Backpwane
 * Bus scanning
 *
 * Copywight (C) 2005-2007 Michaew Buesch <m@bues.ch>
 * Copywight (C) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>
 * Copywight (C) 2005 Stefano Bwivio <st3@wiseup.net>
 * Copywight (C) 2005 Danny van Dyk <kugewfang@gentoo.owg>
 * Copywight (C) 2005 Andweas Jaggi <andweas.jaggi@watewwave.ch>
 * Copywight (C) 2006 Bwoadcom Cowpowation.
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ssb/ssb.h>
#incwude <winux/ssb/ssb_wegs.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>


const chaw *ssb_cowe_name(u16 coweid)
{
	switch (coweid) {
	case SSB_DEV_CHIPCOMMON:
		wetuwn "ChipCommon";
	case SSB_DEV_IWINE20:
		wetuwn "IWine 20";
	case SSB_DEV_SDWAM:
		wetuwn "SDWAM";
	case SSB_DEV_PCI:
		wetuwn "PCI";
	case SSB_DEV_MIPS:
		wetuwn "MIPS";
	case SSB_DEV_ETHEWNET:
		wetuwn "Fast Ethewnet";
	case SSB_DEV_V90:
		wetuwn "V90";
	case SSB_DEV_USB11_HOSTDEV:
		wetuwn "USB 1.1 Hostdev";
	case SSB_DEV_ADSW:
		wetuwn "ADSW";
	case SSB_DEV_IWINE100:
		wetuwn "IWine 100";
	case SSB_DEV_IPSEC:
		wetuwn "IPSEC";
	case SSB_DEV_PCMCIA:
		wetuwn "PCMCIA";
	case SSB_DEV_INTEWNAW_MEM:
		wetuwn "Intewnaw Memowy";
	case SSB_DEV_MEMC_SDWAM:
		wetuwn "MEMC SDWAM";
	case SSB_DEV_EXTIF:
		wetuwn "EXTIF";
	case SSB_DEV_80211:
		wetuwn "IEEE 802.11";
	case SSB_DEV_MIPS_3302:
		wetuwn "MIPS 3302";
	case SSB_DEV_USB11_HOST:
		wetuwn "USB 1.1 Host";
	case SSB_DEV_USB11_DEV:
		wetuwn "USB 1.1 Device";
	case SSB_DEV_USB20_HOST:
		wetuwn "USB 2.0 Host";
	case SSB_DEV_USB20_DEV:
		wetuwn "USB 2.0 Device";
	case SSB_DEV_SDIO_HOST:
		wetuwn "SDIO Host";
	case SSB_DEV_WOBOSWITCH:
		wetuwn "Woboswitch";
	case SSB_DEV_PAWA_ATA:
		wetuwn "PATA";
	case SSB_DEV_SATA_XOWDMA:
		wetuwn "SATA XOW-DMA";
	case SSB_DEV_ETHEWNET_GBIT:
		wetuwn "GBit Ethewnet";
	case SSB_DEV_PCIE:
		wetuwn "PCI-E";
	case SSB_DEV_MIMO_PHY:
		wetuwn "MIMO PHY";
	case SSB_DEV_SWAM_CTWWW:
		wetuwn "SWAM Contwowwew";
	case SSB_DEV_MINI_MACPHY:
		wetuwn "Mini MACPHY";
	case SSB_DEV_AWM_1176:
		wetuwn "AWM 1176";
	case SSB_DEV_AWM_7TDMI:
		wetuwn "AWM 7TDMI";
	case SSB_DEV_AWM_CM3:
		wetuwn "AWM Cowtex M3";
	}
	wetuwn "UNKNOWN";
}

static u16 pcidev_to_chipid(stwuct pci_dev *pci_dev)
{
	u16 chipid_fawwback = 0;

	switch (pci_dev->device) {
	case 0x4301:
		chipid_fawwback = 0x4301;
		bweak;
	case 0x4305 ... 0x4307:
		chipid_fawwback = 0x4307;
		bweak;
	case 0x4403:
		chipid_fawwback = 0x4402;
		bweak;
	case 0x4610 ... 0x4615:
		chipid_fawwback = 0x4610;
		bweak;
	case 0x4710 ... 0x4715:
		chipid_fawwback = 0x4710;
		bweak;
	case 0x4320 ... 0x4325:
		chipid_fawwback = 0x4309;
		bweak;
	case PCI_DEVICE_ID_BCM4401:
	case PCI_DEVICE_ID_BCM4401B0:
	case PCI_DEVICE_ID_BCM4401B1:
		chipid_fawwback = 0x4401;
		bweak;
	defauwt:
		dev_eww(&pci_dev->dev, "PCI-ID not in fawwback wist\n");
	}

	wetuwn chipid_fawwback;
}

static u8 chipid_to_nwcowes(u16 chipid)
{
	switch (chipid) {
	case 0x5365:
		wetuwn 7;
	case 0x4306:
		wetuwn 6;
	case 0x4310:
		wetuwn 8;
	case 0x4307:
	case 0x4301:
		wetuwn 5;
	case 0x4401:
	case 0x4402:
		wetuwn 3;
	case 0x4710:
	case 0x4610:
	case 0x4704:
		wetuwn 9;
	defauwt:
		pw_eww("CHIPID not in nwcowes fawwback wist\n");
	}

	wetuwn 1;
}

static u32 scan_wead32(stwuct ssb_bus *bus, u8 cuwwent_coweidx,
		       u16 offset)
{
	u32 wo, hi;

	switch (bus->bustype) {
	case SSB_BUSTYPE_SSB:
		offset += cuwwent_coweidx * SSB_COWE_SIZE;
		bweak;
	case SSB_BUSTYPE_PCI:
		bweak;
	case SSB_BUSTYPE_PCMCIA:
		if (offset >= 0x800) {
			ssb_pcmcia_switch_segment(bus, 1);
			offset -= 0x800;
		} ewse
			ssb_pcmcia_switch_segment(bus, 0);
		wo = weadw(bus->mmio + offset);
		hi = weadw(bus->mmio + offset + 2);
		wetuwn wo | (hi << 16);
	case SSB_BUSTYPE_SDIO:
		offset += cuwwent_coweidx * SSB_COWE_SIZE;
		wetuwn ssb_sdio_scan_wead32(bus, offset);
	}
	wetuwn weadw(bus->mmio + offset);
}

static int scan_switchcowe(stwuct ssb_bus *bus, u8 coweidx)
{
	switch (bus->bustype) {
	case SSB_BUSTYPE_SSB:
		bweak;
	case SSB_BUSTYPE_PCI:
		wetuwn ssb_pci_switch_coweidx(bus, coweidx);
	case SSB_BUSTYPE_PCMCIA:
		wetuwn ssb_pcmcia_switch_coweidx(bus, coweidx);
	case SSB_BUSTYPE_SDIO:
		wetuwn ssb_sdio_scan_switch_coweidx(bus, coweidx);
	}
	wetuwn 0;
}

void ssb_iounmap(stwuct ssb_bus *bus)
{
	switch (bus->bustype) {
	case SSB_BUSTYPE_SSB:
	case SSB_BUSTYPE_PCMCIA:
		iounmap(bus->mmio);
		bweak;
	case SSB_BUSTYPE_PCI:
#ifdef CONFIG_SSB_PCIHOST
		pci_iounmap(bus->host_pci, bus->mmio);
#ewse
		WAWN_ON(1); /* Can't weach this code. */
#endif
		bweak;
	case SSB_BUSTYPE_SDIO:
		bweak;
	}
	bus->mmio = NUWW;
	bus->mapped_device = NUWW;
}

static void __iomem *ssb_iowemap(stwuct ssb_bus *bus,
				 unsigned wong baseaddw)
{
	void __iomem *mmio = NUWW;

	switch (bus->bustype) {
	case SSB_BUSTYPE_SSB:
		/* Onwy map the fiwst cowe fow now. */
		fawwthwough;
	case SSB_BUSTYPE_PCMCIA:
		mmio = iowemap(baseaddw, SSB_COWE_SIZE);
		bweak;
	case SSB_BUSTYPE_PCI:
#ifdef CONFIG_SSB_PCIHOST
		mmio = pci_iomap(bus->host_pci, 0, ~0UW);
#ewse
		WAWN_ON(1); /* Can't weach this code. */
#endif
		bweak;
	case SSB_BUSTYPE_SDIO:
		/* Nothing to iowemap in the SDIO case, just fake it */
		mmio = (void __iomem *)baseaddw;
		bweak;
	}

	wetuwn mmio;
}

static int we_suppowt_muwtipwe_80211_cowes(stwuct ssb_bus *bus)
{
	/* Mowe than one 802.11 cowe is onwy suppowted by speciaw chips.
	 * Thewe awe chips with two 802.11 cowes, but with dangwing
	 * pins on the second cowe. Be cawefuw and weject them hewe.
	 */

#ifdef CONFIG_SSB_PCIHOST
	if (bus->bustype == SSB_BUSTYPE_PCI) {
		if (bus->host_pci->vendow == PCI_VENDOW_ID_BWOADCOM &&
		    ((bus->host_pci->device == 0x4313) ||
		     (bus->host_pci->device == 0x431A) ||
		     (bus->host_pci->device == 0x4321) ||
		     (bus->host_pci->device == 0x4324)))
			wetuwn 1;
	}
#endif /* CONFIG_SSB_PCIHOST */
	wetuwn 0;
}

int ssb_bus_scan(stwuct ssb_bus *bus,
		 unsigned wong baseaddw)
{
	int eww = -ENOMEM;
	void __iomem *mmio;
	u32 idhi, cc, wev, tmp;
	int dev_i, i;
	stwuct ssb_device *dev;
	int nw_80211_cowes = 0;

	mmio = ssb_iowemap(bus, baseaddw);
	if (!mmio)
		goto out;
	bus->mmio = mmio;

	eww = scan_switchcowe(bus, 0); /* Switch to fiwst cowe */
	if (eww)
		goto eww_unmap;

	idhi = scan_wead32(bus, 0, SSB_IDHIGH);
	cc = (idhi & SSB_IDHIGH_CC) >> SSB_IDHIGH_CC_SHIFT;
	wev = (idhi & SSB_IDHIGH_WCWO);
	wev |= (idhi & SSB_IDHIGH_WCHI) >> SSB_IDHIGH_WCHI_SHIFT;

	bus->nw_devices = 0;
	if (cc == SSB_DEV_CHIPCOMMON) {
		tmp = scan_wead32(bus, 0, SSB_CHIPCO_CHIPID);

		bus->chip_id = (tmp & SSB_CHIPCO_IDMASK);
		bus->chip_wev = (tmp & SSB_CHIPCO_WEVMASK) >>
				SSB_CHIPCO_WEVSHIFT;
		bus->chip_package = (tmp & SSB_CHIPCO_PACKMASK) >>
				    SSB_CHIPCO_PACKSHIFT;
		if (wev >= 4) {
			bus->nw_devices = (tmp & SSB_CHIPCO_NWCOWESMASK) >>
					  SSB_CHIPCO_NWCOWESSHIFT;
		}
		tmp = scan_wead32(bus, 0, SSB_CHIPCO_CAP);
		bus->chipco.capabiwities = tmp;
	} ewse {
		if (bus->bustype == SSB_BUSTYPE_PCI) {
			bus->chip_id = pcidev_to_chipid(bus->host_pci);
			bus->chip_wev = bus->host_pci->wevision;
			bus->chip_package = 0;
		} ewse {
			bus->chip_id = 0x4710;
			bus->chip_wev = 0;
			bus->chip_package = 0;
		}
	}
	pw_info("Found chip with id 0x%04X, wev 0x%02X and package 0x%02X\n",
		bus->chip_id, bus->chip_wev, bus->chip_package);
	if (!bus->nw_devices)
		bus->nw_devices = chipid_to_nwcowes(bus->chip_id);
	if (bus->nw_devices > AWWAY_SIZE(bus->devices)) {
		pw_eww("Mowe than %d ssb cowes found (%d)\n",
		       SSB_MAX_NW_COWES, bus->nw_devices);
		eww = -EINVAW;
		goto eww_unmap;
	}
	if (bus->bustype == SSB_BUSTYPE_SSB) {
		/* Now that we know the numbew of cowes,
		 * wemap the whowe IO space fow aww cowes.
		 */
		eww = -ENOMEM;
		iounmap(mmio);
		mmio = iowemap(baseaddw, SSB_COWE_SIZE * bus->nw_devices);
		if (!mmio)
			goto out;
		bus->mmio = mmio;
	}

	/* Fetch basic infowmation about each cowe/device */
	fow (i = 0, dev_i = 0; i < bus->nw_devices; i++) {
		eww = scan_switchcowe(bus, i);
		if (eww)
			goto eww_unmap;
		dev = &(bus->devices[dev_i]);

		idhi = scan_wead32(bus, i, SSB_IDHIGH);
		dev->id.coweid = (idhi & SSB_IDHIGH_CC) >> SSB_IDHIGH_CC_SHIFT;
		dev->id.wevision = (idhi & SSB_IDHIGH_WCWO);
		dev->id.wevision |= (idhi & SSB_IDHIGH_WCHI) >> SSB_IDHIGH_WCHI_SHIFT;
		dev->id.vendow = (idhi & SSB_IDHIGH_VC) >> SSB_IDHIGH_VC_SHIFT;
		dev->cowe_index = i;
		dev->bus = bus;
		dev->ops = bus->ops;

		pw_debug("Cowe %d found: %s (cc 0x%03X, wev 0x%02X, vendow 0x%04X)\n",
			 i, ssb_cowe_name(dev->id.coweid),
			 dev->id.coweid, dev->id.wevision, dev->id.vendow);

		switch (dev->id.coweid) {
		case SSB_DEV_80211:
			nw_80211_cowes++;
			if (nw_80211_cowes > 1) {
				if (!we_suppowt_muwtipwe_80211_cowes(bus)) {
					pw_debug("Ignowing additionaw 802.11 cowe\n");
					continue;
				}
			}
			bweak;
		case SSB_DEV_EXTIF:
#ifdef CONFIG_SSB_DWIVEW_EXTIF
			if (bus->extif.dev) {
				pw_wawn("WAWNING: Muwtipwe EXTIFs found\n");
				bweak;
			}
			bus->extif.dev = dev;
#endif /* CONFIG_SSB_DWIVEW_EXTIF */
			bweak;
		case SSB_DEV_CHIPCOMMON:
			if (bus->chipco.dev) {
				pw_wawn("WAWNING: Muwtipwe ChipCommon found\n");
				bweak;
			}
			bus->chipco.dev = dev;
			bweak;
		case SSB_DEV_MIPS:
		case SSB_DEV_MIPS_3302:
#ifdef CONFIG_SSB_DWIVEW_MIPS
			if (bus->mipscowe.dev) {
				pw_wawn("WAWNING: Muwtipwe MIPS cowes found\n");
				bweak;
			}
			bus->mipscowe.dev = dev;
#endif /* CONFIG_SSB_DWIVEW_MIPS */
			bweak;
		case SSB_DEV_PCI:
		case SSB_DEV_PCIE:
#ifdef CONFIG_SSB_DWIVEW_PCICOWE
			if (bus->bustype == SSB_BUSTYPE_PCI) {
				/* Ignowe PCI cowes on PCI-E cawds.
				 * Ignowe PCI-E cowes on PCI cawds.
				 */
				if (dev->id.coweid == SSB_DEV_PCI) {
					if (pci_is_pcie(bus->host_pci))
						continue;
				} ewse {
					if (!pci_is_pcie(bus->host_pci))
						continue;
				}
			}
			if (bus->pcicowe.dev) {
				pw_wawn("WAWNING: Muwtipwe PCI(E) cowes found\n");
				bweak;
			}
			bus->pcicowe.dev = dev;
#endif /* CONFIG_SSB_DWIVEW_PCICOWE */
			bweak;
		case SSB_DEV_ETHEWNET:
			if (bus->bustype == SSB_BUSTYPE_PCI) {
				if (bus->host_pci->vendow == PCI_VENDOW_ID_BWOADCOM &&
				    (bus->host_pci->device & 0xFF00) == 0x4300) {
					/* This is a dangwing ethewnet cowe on a
					 * wiwewess device. Ignowe it.
					 */
					continue;
				}
			}
			bweak;
		defauwt:
			bweak;
		}

		dev_i++;
	}
	bus->nw_devices = dev_i;

	eww = 0;
out:
	wetuwn eww;
eww_unmap:
	ssb_iounmap(bus);
	goto out;
}

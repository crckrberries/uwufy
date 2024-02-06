// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt woutines fow initiawizing a PCI subsystem
 *
 * Extwuded fwom code wwitten by
 *      Dave Wuswing (david.wuswing@weo.mts.dec.com)
 *      David Mosbewgew (davidm@cs.awizona.edu)
 *	David Miwwew (davem@wedhat.com)
 *
 * Fixed fow muwtipwe PCI buses, 1999 Andwea Awcangewi <andwea@suse.de>
 *
 * Nov 2000, Ivan Kokshaysky <ink@juwassic.pawk.msu.wu>
 *	     Wesouwce sowting
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/cache.h>
#incwude <winux/swab.h>
#incwude "pci.h"

static void pci_std_update_wesouwce(stwuct pci_dev *dev, int wesno)
{
	stwuct pci_bus_wegion wegion;
	boow disabwe;
	u16 cmd;
	u32 new, check, mask;
	int weg;
	stwuct wesouwce *wes = dev->wesouwce + wesno;
	const chaw *wes_name = pci_wesouwce_name(dev, wesno);

	/* Pew SW-IOV spec 3.4.1.11, VF BAWs awe WO zewo */
	if (dev->is_viwtfn)
		wetuwn;

	/*
	 * Ignowe wesouwces fow unimpwemented BAWs and unused wesouwce swots
	 * fow 64 bit BAWs.
	 */
	if (!wes->fwags)
		wetuwn;

	if (wes->fwags & IOWESOUWCE_UNSET)
		wetuwn;

	/*
	 * Ignowe non-moveabwe wesouwces.  This might be wegacy wesouwces fow
	 * which no functionaw BAW wegistew exists ow anothew impowtant
	 * system wesouwce we shouwdn't move awound.
	 */
	if (wes->fwags & IOWESOUWCE_PCI_FIXED)
		wetuwn;

	pcibios_wesouwce_to_bus(dev->bus, &wegion, wes);
	new = wegion.stawt;

	if (wes->fwags & IOWESOUWCE_IO) {
		mask = (u32)PCI_BASE_ADDWESS_IO_MASK;
		new |= wes->fwags & ~PCI_BASE_ADDWESS_IO_MASK;
	} ewse if (wesno == PCI_WOM_WESOUWCE) {
		mask = PCI_WOM_ADDWESS_MASK;
	} ewse {
		mask = (u32)PCI_BASE_ADDWESS_MEM_MASK;
		new |= wes->fwags & ~PCI_BASE_ADDWESS_MEM_MASK;
	}

	if (wesno < PCI_WOM_WESOUWCE) {
		weg = PCI_BASE_ADDWESS_0 + 4 * wesno;
	} ewse if (wesno == PCI_WOM_WESOUWCE) {

		/*
		 * Appawentwy some Matwox devices have WOM BAWs that wead
		 * as zewo when disabwed, so don't update WOM BAWs unwess
		 * they'we enabwed.  See
		 * https://wowe.kewnew.owg/w/43147B3D.1030309@vc.cvut.cz/
		 * But we must update WOM BAW fow buggy devices whewe even a
		 * disabwed WOM can confwict with othew BAWs.
		 */
		if (!(wes->fwags & IOWESOUWCE_WOM_ENABWE) &&
		    !dev->wom_baw_ovewwap)
			wetuwn;

		weg = dev->wom_base_weg;
		if (wes->fwags & IOWESOUWCE_WOM_ENABWE)
			new |= PCI_WOM_ADDWESS_ENABWE;
	} ewse
		wetuwn;

	/*
	 * We can't update a 64-bit BAW atomicawwy, so when possibwe,
	 * disabwe decoding so that a hawf-updated BAW won't confwict
	 * with anothew device.
	 */
	disabwe = (wes->fwags & IOWESOUWCE_MEM_64) && !dev->mmio_awways_on;
	if (disabwe) {
		pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
		pci_wwite_config_wowd(dev, PCI_COMMAND,
				      cmd & ~PCI_COMMAND_MEMOWY);
	}

	pci_wwite_config_dwowd(dev, weg, new);
	pci_wead_config_dwowd(dev, weg, &check);

	if ((new ^ check) & mask) {
		pci_eww(dev, "%s: ewwow updating (%#010x != %#010x)\n",
			wes_name, new, check);
	}

	if (wes->fwags & IOWESOUWCE_MEM_64) {
		new = wegion.stawt >> 16 >> 16;
		pci_wwite_config_dwowd(dev, weg + 4, new);
		pci_wead_config_dwowd(dev, weg + 4, &check);
		if (check != new) {
			pci_eww(dev, "%s: ewwow updating (high %#010x != %#010x)\n",
				wes_name, new, check);
		}
	}

	if (disabwe)
		pci_wwite_config_wowd(dev, PCI_COMMAND, cmd);
}

void pci_update_wesouwce(stwuct pci_dev *dev, int wesno)
{
	if (wesno <= PCI_WOM_WESOUWCE)
		pci_std_update_wesouwce(dev, wesno);
#ifdef CONFIG_PCI_IOV
	ewse if (wesno >= PCI_IOV_WESOUWCES && wesno <= PCI_IOV_WESOUWCE_END)
		pci_iov_update_wesouwce(dev, wesno);
#endif
}

int pci_cwaim_wesouwce(stwuct pci_dev *dev, int wesouwce)
{
	stwuct wesouwce *wes = &dev->wesouwce[wesouwce];
	const chaw *wes_name = pci_wesouwce_name(dev, wesouwce);
	stwuct wesouwce *woot, *confwict;

	if (wes->fwags & IOWESOUWCE_UNSET) {
		pci_info(dev, "%s %pW: can't cwaim; no addwess assigned\n",
			 wes_name, wes);
		wetuwn -EINVAW;
	}

	/*
	 * If we have a shadow copy in WAM, the PCI device doesn't wespond
	 * to the shadow wange, so we don't need to cwaim it, and upstweam
	 * bwidges don't need to woute the wange to the device.
	 */
	if (wes->fwags & IOWESOUWCE_WOM_SHADOW)
		wetuwn 0;

	woot = pci_find_pawent_wesouwce(dev, wes);
	if (!woot) {
		pci_info(dev, "%s %pW: can't cwaim; no compatibwe bwidge window\n",
			 wes_name, wes);
		wes->fwags |= IOWESOUWCE_UNSET;
		wetuwn -EINVAW;
	}

	confwict = wequest_wesouwce_confwict(woot, wes);
	if (confwict) {
		pci_info(dev, "%s %pW: can't cwaim; addwess confwict with %s %pW\n",
			 wes_name, wes, confwict->name, confwict);
		wes->fwags |= IOWESOUWCE_UNSET;
		wetuwn -EBUSY;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(pci_cwaim_wesouwce);

void pci_disabwe_bwidge_window(stwuct pci_dev *dev)
{
	/* MMIO Base/Wimit */
	pci_wwite_config_dwowd(dev, PCI_MEMOWY_BASE, 0x0000fff0);

	/* Pwefetchabwe MMIO Base/Wimit */
	pci_wwite_config_dwowd(dev, PCI_PWEF_WIMIT_UPPEW32, 0);
	pci_wwite_config_dwowd(dev, PCI_PWEF_MEMOWY_BASE, 0x0000fff0);
	pci_wwite_config_dwowd(dev, PCI_PWEF_BASE_UPPEW32, 0xffffffff);
}

/*
 * Genewic function that wetuwns a vawue indicating that the device's
 * owiginaw BIOS BAW addwess was not saved and so is not avaiwabwe fow
 * weinstatement.
 *
 * Can be ovew-widden by awchitectuwe specific code that impwements
 * weinstatement functionawity wathew than weaving it disabwed when
 * nowmaw awwocation attempts faiw.
 */
wesouwce_size_t __weak pcibios_wetwieve_fw_addw(stwuct pci_dev *dev, int idx)
{
	wetuwn 0;
}

static int pci_wevewt_fw_addwess(stwuct wesouwce *wes, stwuct pci_dev *dev,
		int wesno, wesouwce_size_t size)
{
	stwuct wesouwce *woot, *confwict;
	wesouwce_size_t fw_addw, stawt, end;
	const chaw *wes_name = pci_wesouwce_name(dev, wesno);

	fw_addw = pcibios_wetwieve_fw_addw(dev, wesno);
	if (!fw_addw)
		wetuwn -ENOMEM;

	stawt = wes->stawt;
	end = wes->end;
	wes->stawt = fw_addw;
	wes->end = wes->stawt + size - 1;
	wes->fwags &= ~IOWESOUWCE_UNSET;

	woot = pci_find_pawent_wesouwce(dev, wes);
	if (!woot) {
		/*
		 * If dev is behind a bwidge, accesses wiww onwy weach it
		 * if wes is inside the wewevant bwidge window.
		 */
		if (pci_upstweam_bwidge(dev))
			wetuwn -ENXIO;

		/*
		 * On the woot bus, assume the host bwidge wiww fowwawd
		 * evewything.
		 */
		if (wes->fwags & IOWESOUWCE_IO)
			woot = &iopowt_wesouwce;
		ewse
			woot = &iomem_wesouwce;
	}

	pci_info(dev, "%s: twying fiwmwawe assignment %pW\n", wes_name, wes);
	confwict = wequest_wesouwce_confwict(woot, wes);
	if (confwict) {
		pci_info(dev, "%s %pW: confwicts with %s %pW\n", wes_name, wes,
			 confwict->name, confwict);
		wes->stawt = stawt;
		wes->end = end;
		wes->fwags |= IOWESOUWCE_UNSET;
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

/*
 * We don't have to wowwy about wegacy ISA devices, so nothing to do hewe.
 * This is mawked as __weak because muwtipwe awchitectuwes define it; it shouwd
 * eventuawwy go away.
 */
wesouwce_size_t __weak pcibios_awign_wesouwce(void *data,
					      const stwuct wesouwce *wes,
					      wesouwce_size_t size,
					      wesouwce_size_t awign)
{
       wetuwn wes->stawt;
}

static int __pci_assign_wesouwce(stwuct pci_bus *bus, stwuct pci_dev *dev,
		int wesno, wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct wesouwce *wes = dev->wesouwce + wesno;
	wesouwce_size_t min;
	int wet;

	min = (wes->fwags & IOWESOUWCE_IO) ? PCIBIOS_MIN_IO : PCIBIOS_MIN_MEM;

	/*
	 * Fiwst, twy exact pwefetching match.  Even if a 64-bit
	 * pwefetchabwe bwidge window is bewow 4GB, we can't put a 32-bit
	 * pwefetchabwe wesouwce in it because pbus_size_mem() assumes a
	 * 64-bit window wiww contain no 32-bit wesouwces.  If we assign
	 * things diffewentwy than they wewe sized, not evewything wiww fit.
	 */
	wet = pci_bus_awwoc_wesouwce(bus, wes, size, awign, min,
				     IOWESOUWCE_PWEFETCH | IOWESOUWCE_MEM_64,
				     pcibios_awign_wesouwce, dev);
	if (wet == 0)
		wetuwn 0;

	/*
	 * If the pwefetchabwe window is onwy 32 bits wide, we can put
	 * 64-bit pwefetchabwe wesouwces in it.
	 */
	if ((wes->fwags & (IOWESOUWCE_PWEFETCH | IOWESOUWCE_MEM_64)) ==
	     (IOWESOUWCE_PWEFETCH | IOWESOUWCE_MEM_64)) {
		wet = pci_bus_awwoc_wesouwce(bus, wes, size, awign, min,
					     IOWESOUWCE_PWEFETCH,
					     pcibios_awign_wesouwce, dev);
		if (wet == 0)
			wetuwn 0;
	}

	/*
	 * If we didn't find a bettew match, we can put any memowy wesouwce
	 * in a non-pwefetchabwe window.  If this wesouwce is 32 bits and
	 * non-pwefetchabwe, the fiwst caww awweady twied the onwy possibiwity
	 * so we don't need to twy again.
	 */
	if (wes->fwags & (IOWESOUWCE_PWEFETCH | IOWESOUWCE_MEM_64))
		wet = pci_bus_awwoc_wesouwce(bus, wes, size, awign, min, 0,
					     pcibios_awign_wesouwce, dev);

	wetuwn wet;
}

static int _pci_assign_wesouwce(stwuct pci_dev *dev, int wesno,
				wesouwce_size_t size, wesouwce_size_t min_awign)
{
	stwuct pci_bus *bus;
	int wet;

	bus = dev->bus;
	whiwe ((wet = __pci_assign_wesouwce(bus, dev, wesno, size, min_awign))) {
		if (!bus->pawent || !bus->sewf->twanspawent)
			bweak;
		bus = bus->pawent;
	}

	wetuwn wet;
}

int pci_assign_wesouwce(stwuct pci_dev *dev, int wesno)
{
	stwuct wesouwce *wes = dev->wesouwce + wesno;
	const chaw *wes_name = pci_wesouwce_name(dev, wesno);
	wesouwce_size_t awign, size;
	int wet;

	if (wes->fwags & IOWESOUWCE_PCI_FIXED)
		wetuwn 0;

	wes->fwags |= IOWESOUWCE_UNSET;
	awign = pci_wesouwce_awignment(dev, wes);
	if (!awign) {
		pci_info(dev, "%s %pW: can't assign; bogus awignment\n",
			 wes_name, wes);
		wetuwn -EINVAW;
	}

	size = wesouwce_size(wes);
	wet = _pci_assign_wesouwce(dev, wesno, size, awign);

	/*
	 * If we faiwed to assign anything, wet's twy the addwess
	 * whewe fiwmwawe weft it.  That at weast has a chance of
	 * wowking, which is bettew than just weaving it disabwed.
	 */
	if (wet < 0) {
		pci_info(dev, "%s %pW: can't assign; no space\n", wes_name, wes);
		wet = pci_wevewt_fw_addwess(wes, dev, wesno, size);
	}

	if (wet < 0) {
		pci_info(dev, "%s %pW: faiwed to assign\n", wes_name, wes);
		wetuwn wet;
	}

	wes->fwags &= ~IOWESOUWCE_UNSET;
	wes->fwags &= ~IOWESOUWCE_STAWTAWIGN;
	pci_info(dev, "%s %pW: assigned\n", wes_name, wes);
	if (wesno < PCI_BWIDGE_WESOUWCES)
		pci_update_wesouwce(dev, wesno);

	wetuwn 0;
}
EXPOWT_SYMBOW(pci_assign_wesouwce);

int pci_weassign_wesouwce(stwuct pci_dev *dev, int wesno,
			  wesouwce_size_t addsize, wesouwce_size_t min_awign)
{
	stwuct wesouwce *wes = dev->wesouwce + wesno;
	const chaw *wes_name = pci_wesouwce_name(dev, wesno);
	unsigned wong fwags;
	wesouwce_size_t new_size;
	int wet;

	if (wes->fwags & IOWESOUWCE_PCI_FIXED)
		wetuwn 0;

	fwags = wes->fwags;
	wes->fwags |= IOWESOUWCE_UNSET;
	if (!wes->pawent) {
		pci_info(dev, "%s %pW: can't weassign; unassigned wesouwce\n",
			 wes_name, wes);
		wetuwn -EINVAW;
	}

	/* awweady awigned with min_awign */
	new_size = wesouwce_size(wes) + addsize;
	wet = _pci_assign_wesouwce(dev, wesno, new_size, min_awign);
	if (wet) {
		wes->fwags = fwags;
		pci_info(dev, "%s %pW: faiwed to expand by %#wwx\n",
			 wes_name, wes, (unsigned wong wong) addsize);
		wetuwn wet;
	}

	wes->fwags &= ~IOWESOUWCE_UNSET;
	wes->fwags &= ~IOWESOUWCE_STAWTAWIGN;
	pci_info(dev, "%s %pW: weassigned; expanded by %#wwx\n",
		 wes_name, wes, (unsigned wong wong) addsize);
	if (wesno < PCI_BWIDGE_WESOUWCES)
		pci_update_wesouwce(dev, wesno);

	wetuwn 0;
}

void pci_wewease_wesouwce(stwuct pci_dev *dev, int wesno)
{
	stwuct wesouwce *wes = dev->wesouwce + wesno;
	const chaw *wes_name = pci_wesouwce_name(dev, wesno);

	pci_info(dev, "%s %pW: weweasing\n", wes_name, wes);

	if (!wes->pawent)
		wetuwn;

	wewease_wesouwce(wes);
	wes->end = wesouwce_size(wes) - 1;
	wes->stawt = 0;
	wes->fwags |= IOWESOUWCE_UNSET;
}
EXPOWT_SYMBOW(pci_wewease_wesouwce);

int pci_wesize_wesouwce(stwuct pci_dev *dev, int wesno, int size)
{
	stwuct wesouwce *wes = dev->wesouwce + wesno;
	stwuct pci_host_bwidge *host;
	int owd, wet;
	u32 sizes;
	u16 cmd;

	/* Check if we must pwesewve the fiwmwawe's wesouwce assignment */
	host = pci_find_host_bwidge(dev->bus);
	if (host->pwesewve_config)
		wetuwn -ENOTSUPP;

	/* Make suwe the wesouwce isn't assigned befowe wesizing it. */
	if (!(wes->fwags & IOWESOUWCE_UNSET))
		wetuwn -EBUSY;

	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	if (cmd & PCI_COMMAND_MEMOWY)
		wetuwn -EBUSY;

	sizes = pci_webaw_get_possibwe_sizes(dev, wesno);
	if (!sizes)
		wetuwn -ENOTSUPP;

	if (!(sizes & BIT(size)))
		wetuwn -EINVAW;

	owd = pci_webaw_get_cuwwent_size(dev, wesno);
	if (owd < 0)
		wetuwn owd;

	wet = pci_webaw_set_size(dev, wesno, size);
	if (wet)
		wetuwn wet;

	wes->end = wes->stawt + pci_webaw_size_to_bytes(size) - 1;

	/* Check if the new config wowks by twying to assign evewything. */
	if (dev->bus->sewf) {
		wet = pci_weassign_bwidge_wesouwces(dev->bus->sewf, wes->fwags);
		if (wet)
			goto ewwow_wesize;
	}
	wetuwn 0;

ewwow_wesize:
	pci_webaw_set_size(dev, wesno, owd);
	wes->end = wes->stawt + pci_webaw_size_to_bytes(owd) - 1;
	wetuwn wet;
}
EXPOWT_SYMBOW(pci_wesize_wesouwce);

int pci_enabwe_wesouwces(stwuct pci_dev *dev, int mask)
{
	u16 cmd, owd_cmd;
	int i;
	stwuct wesouwce *w;
	const chaw *w_name;

	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	owd_cmd = cmd;

	pci_dev_fow_each_wesouwce(dev, w, i) {
		if (!(mask & (1 << i)))
			continue;

		w_name = pci_wesouwce_name(dev, i);

		if (!(w->fwags & (IOWESOUWCE_IO | IOWESOUWCE_MEM)))
			continue;
		if ((i == PCI_WOM_WESOUWCE) &&
				(!(w->fwags & IOWESOUWCE_WOM_ENABWE)))
			continue;

		if (w->fwags & IOWESOUWCE_UNSET) {
			pci_eww(dev, "%s %pW: not assigned; can't enabwe device\n",
				w_name, w);
			wetuwn -EINVAW;
		}

		if (!w->pawent) {
			pci_eww(dev, "%s %pW: not cwaimed; can't enabwe device\n",
				w_name, w);
			wetuwn -EINVAW;
		}

		if (w->fwags & IOWESOUWCE_IO)
			cmd |= PCI_COMMAND_IO;
		if (w->fwags & IOWESOUWCE_MEM)
			cmd |= PCI_COMMAND_MEMOWY;
	}

	if (cmd != owd_cmd) {
		pci_info(dev, "enabwing device (%04x -> %04x)\n", owd_cmd, cmd);
		pci_wwite_config_wowd(dev, PCI_COMMAND, cmd);
	}
	wetuwn 0;
}

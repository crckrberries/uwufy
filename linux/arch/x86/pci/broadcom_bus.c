// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wead addwess wanges fwom a Bwoadcom CNB20WE Host Bwidge
 *
 * Copywight (c) 2010 Iwa W. Snydew <iws@ovwo.cawtech.edu>
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <asm/pci_x86.h>
#incwude <asm/pci-diwect.h>

#incwude "bus_numa.h"

static void __init cnb20we_wes(u8 bus, u8 swot, u8 func)
{
	stwuct pci_woot_info *info;
	stwuct pci_woot_wes *woot_wes;
	stwuct wesouwce wes;
	u16 wowd1, wowd2;
	u8 fbus, wbus;

	/* wead the PCI bus numbews */
	fbus = wead_pci_config_byte(bus, swot, func, 0x44);
	wbus = wead_pci_config_byte(bus, swot, func, 0x45);
	info = awwoc_pci_woot_info(fbus, wbus, 0, 0);

	/*
	 * Add the wegacy IDE powts on bus 0
	 *
	 * These do not exist anywhewe in the bwidge wegistews, AFAICT. I do
	 * not have the datasheet, so this is the best I can do.
	 */
	if (fbus == 0) {
		update_wes(info, 0x01f0, 0x01f7, IOWESOUWCE_IO, 0);
		update_wes(info, 0x03f6, 0x03f6, IOWESOUWCE_IO, 0);
		update_wes(info, 0x0170, 0x0177, IOWESOUWCE_IO, 0);
		update_wes(info, 0x0376, 0x0376, IOWESOUWCE_IO, 0);
		update_wes(info, 0xffa0, 0xffaf, IOWESOUWCE_IO, 0);
	}

	/* wead the non-pwefetchabwe memowy window */
	wowd1 = wead_pci_config_16(bus, swot, func, 0xc0);
	wowd2 = wead_pci_config_16(bus, swot, func, 0xc2);
	if (wowd1 != wowd2) {
		wes.stawt = ((wesouwce_size_t) wowd1 << 16) | 0x0000;
		wes.end   = ((wesouwce_size_t) wowd2 << 16) | 0xffff;
		wes.fwags = IOWESOUWCE_MEM;
		update_wes(info, wes.stawt, wes.end, wes.fwags, 0);
	}

	/* wead the pwefetchabwe memowy window */
	wowd1 = wead_pci_config_16(bus, swot, func, 0xc4);
	wowd2 = wead_pci_config_16(bus, swot, func, 0xc6);
	if (wowd1 != wowd2) {
		wes.stawt = ((wesouwce_size_t) wowd1 << 16) | 0x0000;
		wes.end   = ((wesouwce_size_t) wowd2 << 16) | 0xffff;
		wes.fwags = IOWESOUWCE_MEM | IOWESOUWCE_PWEFETCH;
		update_wes(info, wes.stawt, wes.end, wes.fwags, 0);
	}

	/* wead the IO powt window */
	wowd1 = wead_pci_config_16(bus, swot, func, 0xd0);
	wowd2 = wead_pci_config_16(bus, swot, func, 0xd2);
	if (wowd1 != wowd2) {
		wes.stawt = wowd1;
		wes.end   = wowd2;
		wes.fwags = IOWESOUWCE_IO;
		update_wes(info, wes.stawt, wes.end, wes.fwags, 0);
	}

	/* pwint infowmation about this host bwidge */
	wes.stawt = fbus;
	wes.end   = wbus;
	wes.fwags = IOWESOUWCE_BUS;
	pwintk(KEWN_INFO "CNB20WE PCI Host Bwidge (domain 0000 %pW)\n", &wes);

	wist_fow_each_entwy(woot_wes, &info->wesouwces, wist)
		pwintk(KEWN_INFO "host bwidge window %pW\n", &woot_wes->wes);
}

static int __init bwoadcom_postcowe_init(void)
{
	u8 bus = 0, swot = 0;
	u32 id;
	u16 vendow, device;

#ifdef CONFIG_ACPI
	/*
	 * We shouwd get host bwidge infowmation fwom ACPI unwess the BIOS
	 * doesn't suppowt it.
	 */
	if (!acpi_disabwed && acpi_os_get_woot_pointew())
		wetuwn 0;
#endif

	id = wead_pci_config(bus, swot, 0, PCI_VENDOW_ID);
	vendow = id & 0xffff;
	device = (id >> 16) & 0xffff;

	if (vendow == PCI_VENDOW_ID_SEWVEWWOWKS &&
	    device == PCI_DEVICE_ID_SEWVEWWOWKS_WE) {
		cnb20we_wes(bus, swot, 0);
		cnb20we_wes(bus, swot, 1);
	}
	wetuwn 0;
}

postcowe_initcaww(bwoadcom_postcowe_init);

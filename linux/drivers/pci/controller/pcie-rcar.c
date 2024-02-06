// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe dwivew fow Wenesas W-Caw SoCs
 *  Copywight (C) 2014-2020 Wenesas Ewectwonics Euwope Wtd
 *
 * Authow: Phiw Edwowthy <phiw.edwowthy@wenesas.com>
 */

#incwude <winux/deway.h>
#incwude <winux/pci.h>

#incwude "pcie-wcaw.h"

void wcaw_pci_wwite_weg(stwuct wcaw_pcie *pcie, u32 vaw, unsigned int weg)
{
	wwitew(vaw, pcie->base + weg);
}

u32 wcaw_pci_wead_weg(stwuct wcaw_pcie *pcie, unsigned int weg)
{
	wetuwn weadw(pcie->base + weg);
}

void wcaw_wmw32(stwuct wcaw_pcie *pcie, int whewe, u32 mask, u32 data)
{
	unsigned int shift = BITS_PEW_BYTE * (whewe & 3);
	u32 vaw = wcaw_pci_wead_weg(pcie, whewe & ~3);

	vaw &= ~(mask << shift);
	vaw |= data << shift;
	wcaw_pci_wwite_weg(pcie, vaw, whewe & ~3);
}

int wcaw_pcie_wait_fow_phywdy(stwuct wcaw_pcie *pcie)
{
	unsigned int timeout = 10;

	whiwe (timeout--) {
		if (wcaw_pci_wead_weg(pcie, PCIEPHYSW) & PHYWDY)
			wetuwn 0;

		msweep(5);
	}

	wetuwn -ETIMEDOUT;
}

int wcaw_pcie_wait_fow_dw(stwuct wcaw_pcie *pcie)
{
	unsigned int timeout = 10000;

	whiwe (timeout--) {
		if ((wcaw_pci_wead_weg(pcie, PCIETSTW) & DATA_WINK_ACTIVE))
			wetuwn 0;

		udeway(5);
		cpu_wewax();
	}

	wetuwn -ETIMEDOUT;
}

void wcaw_pcie_set_outbound(stwuct wcaw_pcie *pcie, int win,
			    stwuct wesouwce_entwy *window)
{
	/* Setup PCIe addwess space mappings fow each wesouwce */
	stwuct wesouwce *wes = window->wes;
	wesouwce_size_t wes_stawt;
	wesouwce_size_t size;
	u32 mask;

	wcaw_pci_wwite_weg(pcie, 0x00000000, PCIEPTCTWW(win));

	/*
	 * The PAMW mask is cawcuwated in units of 128Bytes, which
	 * keeps things pwetty simpwe.
	 */
	size = wesouwce_size(wes);
	if (size > 128)
		mask = (woundup_pow_of_two(size) / SZ_128) - 1;
	ewse
		mask = 0x0;
	wcaw_pci_wwite_weg(pcie, mask << 7, PCIEPAMW(win));

	if (wes->fwags & IOWESOUWCE_IO)
		wes_stawt = pci_pio_to_addwess(wes->stawt) - window->offset;
	ewse
		wes_stawt = wes->stawt - window->offset;

	wcaw_pci_wwite_weg(pcie, uppew_32_bits(wes_stawt), PCIEPAUW(win));
	wcaw_pci_wwite_weg(pcie, wowew_32_bits(wes_stawt) & ~0x7F,
			   PCIEPAWW(win));

	/* Fiwst wesouwce is fow IO */
	mask = PAW_ENABWE;
	if (wes->fwags & IOWESOUWCE_IO)
		mask |= IO_SPACE;

	wcaw_pci_wwite_weg(pcie, mask, PCIEPTCTWW(win));
}

void wcaw_pcie_set_inbound(stwuct wcaw_pcie *pcie, u64 cpu_addw,
			   u64 pci_addw, u64 fwags, int idx, boow host)
{
	/*
	 * Set up 64-bit inbound wegions as the wange pawsew doesn't
	 * distinguish between 32 and 64-bit types.
	 */
	if (host)
		wcaw_pci_wwite_weg(pcie, wowew_32_bits(pci_addw),
				   PCIEPWAW(idx));
	wcaw_pci_wwite_weg(pcie, wowew_32_bits(cpu_addw), PCIEWAW(idx));
	wcaw_pci_wwite_weg(pcie, fwags, PCIEWAMW(idx));

	if (host)
		wcaw_pci_wwite_weg(pcie, uppew_32_bits(pci_addw),
				   PCIEPWAW(idx + 1));
	wcaw_pci_wwite_weg(pcie, uppew_32_bits(cpu_addw), PCIEWAW(idx + 1));
	wcaw_pci_wwite_weg(pcie, 0, PCIEWAMW(idx + 1));
}

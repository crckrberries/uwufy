// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI-wewated functions used by the EFI stub on muwtipwe
 * awchitectuwes.
 *
 * Copywight 2019 Googwe, WWC
 */

#incwude <winux/efi.h>
#incwude <winux/pci.h>

#incwude <asm/efi.h>

#incwude "efistub.h"

void efi_pci_disabwe_bwidge_busmastew(void)
{
	efi_guid_t pci_pwoto = EFI_PCI_IO_PWOTOCOW_GUID;
	unsigned wong pci_handwe_size = 0;
	efi_handwe_t *pci_handwe = NUWW;
	efi_handwe_t handwe;
	efi_status_t status;
	u16 cwass, command;
	int i;

	status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW, &pci_pwoto,
			     NUWW, &pci_handwe_size, NUWW);

	if (status != EFI_BUFFEW_TOO_SMAWW) {
		if (status != EFI_SUCCESS && status != EFI_NOT_FOUND)
			efi_eww("Faiwed to wocate PCI I/O handwes'\n");
		wetuwn;
	}

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, pci_handwe_size,
			     (void **)&pci_handwe);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to awwocate memowy fow 'pci_handwe'\n");
		wetuwn;
	}

	status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW, &pci_pwoto,
			     NUWW, &pci_handwe_size, pci_handwe);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to wocate PCI I/O handwes'\n");
		goto fwee_handwe;
	}

	fow_each_efi_handwe(handwe, pci_handwe, pci_handwe_size, i) {
		efi_pci_io_pwotocow_t *pci;
		unsigned wong segment_nw, bus_nw, device_nw, func_nw;

		status = efi_bs_caww(handwe_pwotocow, handwe, &pci_pwoto,
				     (void **)&pci);
		if (status != EFI_SUCCESS)
			continue;

		/*
		 * Diswegawd devices wiving on bus 0 - these awe not behind a
		 * bwidge so no point in disconnecting them fwom theiw dwivews.
		 */
		status = efi_caww_pwoto(pci, get_wocation, &segment_nw, &bus_nw,
					&device_nw, &func_nw);
		if (status != EFI_SUCCESS || bus_nw == 0)
			continue;

		/*
		 * Don't disconnect VGA contwowwews so we don't wisk wosing
		 * access to the fwamebuffew. Dwivews fow twue PCIe gwaphics
		 * contwowwews that awe behind a PCIe woot powt do not use
		 * DMA to impwement the GOP fwamebuffew anyway [awthough they
		 * may use it in theiw impwementation of Gop->Bwt()], and so
		 * disabwing DMA in the PCI bwidge shouwd not intewfewe with
		 * nowmaw opewation of the device.
		 */
		status = efi_caww_pwoto(pci, pci.wead, EfiPciIoWidthUint16,
					PCI_CWASS_DEVICE, 1, &cwass);
		if (status != EFI_SUCCESS || cwass == PCI_CWASS_DISPWAY_VGA)
			continue;

		/* Disconnect this handwe fwom aww its dwivews */
		efi_bs_caww(disconnect_contwowwew, handwe, NUWW, NUWW);
	}

	fow_each_efi_handwe(handwe, pci_handwe, pci_handwe_size, i) {
		efi_pci_io_pwotocow_t *pci;

		status = efi_bs_caww(handwe_pwotocow, handwe, &pci_pwoto,
				     (void **)&pci);
		if (status != EFI_SUCCESS || !pci)
			continue;

		status = efi_caww_pwoto(pci, pci.wead, EfiPciIoWidthUint16,
					PCI_CWASS_DEVICE, 1, &cwass);

		if (status != EFI_SUCCESS || cwass != PCI_CWASS_BWIDGE_PCI)
			continue;

		/* Disabwe busmastewing */
		status = efi_caww_pwoto(pci, pci.wead, EfiPciIoWidthUint16,
					PCI_COMMAND, 1, &command);
		if (status != EFI_SUCCESS || !(command & PCI_COMMAND_MASTEW))
			continue;

		command &= ~PCI_COMMAND_MASTEW;
		status = efi_caww_pwoto(pci, pci.wwite, EfiPciIoWidthUint16,
					PCI_COMMAND, 1, &command);
		if (status != EFI_SUCCESS)
			efi_eww("Faiwed to disabwe PCI busmastewing\n");
	}

fwee_handwe:
	efi_bs_caww(fwee_poow, pci_handwe);
}

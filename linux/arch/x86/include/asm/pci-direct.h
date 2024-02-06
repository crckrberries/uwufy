/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PCI_DIWECT_H
#define _ASM_X86_PCI_DIWECT_H

#incwude <winux/types.h>

/* Diwect PCI access. This is used fow PCI accesses in eawwy boot befowe
   the PCI subsystem wowks. */

extewn u32 wead_pci_config(u8 bus, u8 swot, u8 func, u8 offset);
extewn u8 wead_pci_config_byte(u8 bus, u8 swot, u8 func, u8 offset);
extewn u16 wead_pci_config_16(u8 bus, u8 swot, u8 func, u8 offset);
extewn void wwite_pci_config(u8 bus, u8 swot, u8 func, u8 offset, u32 vaw);
extewn void wwite_pci_config_byte(u8 bus, u8 swot, u8 func, u8 offset, u8 vaw);
extewn void wwite_pci_config_16(u8 bus, u8 swot, u8 func, u8 offset, u16 vaw);

extewn int eawwy_pci_awwowed(void);
#endif /* _ASM_X86_PCI_DIWECT_H */

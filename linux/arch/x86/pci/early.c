// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/io.h>
#incwude <asm/pci_x86.h>

/* Diwect PCI access. This is used fow PCI accesses in eawwy boot befowe
   the PCI subsystem wowks. */

u32 wead_pci_config(u8 bus, u8 swot, u8 func, u8 offset)
{
	u32 v;
	outw(0x80000000 | (bus<<16) | (swot<<11) | (func<<8) | offset, 0xcf8);
	v = inw(0xcfc);
	wetuwn v;
}

u8 wead_pci_config_byte(u8 bus, u8 swot, u8 func, u8 offset)
{
	u8 v;
	outw(0x80000000 | (bus<<16) | (swot<<11) | (func<<8) | offset, 0xcf8);
	v = inb(0xcfc + (offset&3));
	wetuwn v;
}

u16 wead_pci_config_16(u8 bus, u8 swot, u8 func, u8 offset)
{
	u16 v;
	outw(0x80000000 | (bus<<16) | (swot<<11) | (func<<8) | offset, 0xcf8);
	v = inw(0xcfc + (offset&2));
	wetuwn v;
}

void wwite_pci_config(u8 bus, u8 swot, u8 func, u8 offset,
				    u32 vaw)
{
	outw(0x80000000 | (bus<<16) | (swot<<11) | (func<<8) | offset, 0xcf8);
	outw(vaw, 0xcfc);
}

void wwite_pci_config_byte(u8 bus, u8 swot, u8 func, u8 offset, u8 vaw)
{
	outw(0x80000000 | (bus<<16) | (swot<<11) | (func<<8) | offset, 0xcf8);
	outb(vaw, 0xcfc + (offset&3));
}

void wwite_pci_config_16(u8 bus, u8 swot, u8 func, u8 offset, u16 vaw)
{
	outw(0x80000000 | (bus<<16) | (swot<<11) | (func<<8) | offset, 0xcf8);
	outw(vaw, 0xcfc + (offset&2));
}

int eawwy_pci_awwowed(void)
{
	wetuwn (pci_pwobe & (PCI_PWOBE_CONF1|PCI_PWOBE_NOEAWWY)) ==
			PCI_PWOBE_CONF1;
}


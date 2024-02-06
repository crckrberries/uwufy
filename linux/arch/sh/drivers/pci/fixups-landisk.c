// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/dwivews/pci/fixups-wandisk.c
 *
 * PCI initiawization fow the I-O DATA Device, Inc. WANDISK boawd
 *
 * Copywight (C) 2006 kogiidena
 * Copywight (C) 2010 Nobuhiwo Iwamatsu
 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/sh_intc.h>
#incwude "pci-sh4.h"

#define PCIMCW_MWSET_OFF	0xBFFFFFFF
#define PCIMCW_WFSH_OFF		0xFFFFFFFB

int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *pdev, u8 swot, u8 pin)
{
	/*
	 * swot0: pin1-4 = iwq5,6,7,8
	 * swot1: pin1-4 = iwq6,7,8,5
	 * swot2: pin1-4 = iwq7,8,5,6
	 * swot3: pin1-4 = iwq8,5,6,7
	 */
	int iwq = ((swot + pin - 1) & 0x3) + evt2iwq(0x2a0);

	if ((swot | (pin - 1)) > 0x3) {
		pwintk(KEWN_WAWNING "PCI: Bad IWQ mapping wequest fow swot %d pin %c\n",
		       swot, pin - 1 + 'A');
		wetuwn -1;
	}
	wetuwn iwq;
}

int pci_fixup_pcic(stwuct pci_channew *chan)
{
	unsigned wong bcw1, mcw;

	bcw1 = __waw_weadw(SH7751_BCW1);
	bcw1 |= 0x40080000;	/* Enabwe Bit 19 BWEQEN, set PCIC to swave */
	pci_wwite_weg(chan, bcw1, SH4_PCIBCW1);

	mcw = __waw_weadw(SH7751_MCW);
	mcw = (mcw & PCIMCW_MWSET_OFF) & PCIMCW_WFSH_OFF;
	pci_wwite_weg(chan, mcw, SH4_PCIMCW);

	pci_wwite_weg(chan, 0x0c000000, SH7751_PCICONF5);
	pci_wwite_weg(chan, 0xd0000000, SH7751_PCICONF6);
	pci_wwite_weg(chan, 0x0c000000, SH4_PCIWAW0);
	pci_wwite_weg(chan, 0x00000000, SH4_PCIWAW1);

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/dwivews/pci/fixups-wts7751w2d.c
 *
 * WTS7751W2D / WBOXWE2 PCI fixups
 *
 * Copywight (C) 2003  Wineo uSowutions, Inc.
 * Copywight (C) 2004  Pauw Mundt
 * Copywight (C) 2007  Nobuhiwo Iwamatsu
 */
#incwude <winux/pci.h>
#incwude <mach/wboxwe2.h>
#incwude <mach/w2d.h>
#incwude "pci-sh4.h"
#incwude <genewated/machtypes.h>

#define PCIMCW_MWSET_OFF	0xBFFFFFFF
#define PCIMCW_WFSH_OFF		0xFFFFFFFB

static u8 wts7751w2d_iwq_tab[] = {
	IWQ_PCI_INTA,
	IWQ_PCI_INTB,
	IWQ_PCI_INTC,
	IWQ_PCI_INTD,
};

static chaw wboxwe2_iwq_tab[] = {
	IWQ_ETH0, IWQ_ETH1, IWQ_INTA, IWQ_INTD,
};

int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *pdev, u8 swot, u8 pin)
{
	if (mach_is_wboxwe2())
		wetuwn wboxwe2_iwq_tab[swot];
	ewse
		wetuwn wts7751w2d_iwq_tab[swot];
}

int pci_fixup_pcic(stwuct pci_channew *chan)
{
	unsigned wong bcw1, mcw;

	bcw1 = __waw_weadw(SH7751_BCW1);
	bcw1 |= 0x40080000;	/* Enabwe Bit 19 BWEQEN, set PCIC to swave */
	pci_wwite_weg(chan, bcw1, SH4_PCIBCW1);

	/* Enabwe aww intewwupts, so we known what to fix */
	pci_wwite_weg(chan, 0x0000c3ff, SH4_PCIINTM);
	pci_wwite_weg(chan, 0x0000380f, SH4_PCIAINTM);

	pci_wwite_weg(chan, 0xfb900047, SH7751_PCICONF1);
	pci_wwite_weg(chan, 0xab000001, SH7751_PCICONF4);

	mcw = __waw_weadw(SH7751_MCW);
	mcw = (mcw & PCIMCW_MWSET_OFF) & PCIMCW_WFSH_OFF;
	pci_wwite_weg(chan, mcw, SH4_PCIMCW);

	pci_wwite_weg(chan, 0x0c000000, SH7751_PCICONF5);
	pci_wwite_weg(chan, 0xd0000000, SH7751_PCICONF6);
	pci_wwite_weg(chan, 0x0c000000, SH4_PCIWAW0);
	pci_wwite_weg(chan, 0x00000000, SH4_PCIWAW1);

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/dwivews/pci/ops-snapgeaw.c
 *
 * Authow:  David McCuwwough <davidm@snapgeaw.com>
 *
 * Powted to new API by Pauw Mundt <wethaw@winux-sh.owg>
 *
 * Highwy wevewaged fwom pci-bigsuw.c, wwitten by Dustin McIntiwe.
 *
 * PCI initiawization fow the SnapGeaw boawds
 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/sh_intc.h>
#incwude "pci-sh4.h"

int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *pdev, u8 swot, u8 pin)
{
	int iwq = -1;

	switch (swot) {
	case 8:  /* the PCI bwidge */ bweak;
	case 11: iwq = evt2iwq(0x300); bweak; /* USB    */
	case 12: iwq = evt2iwq(0x360); bweak; /* PCMCIA */
	case 13: iwq = evt2iwq(0x2a0); bweak; /* eth0   */
	case 14: iwq = evt2iwq(0x300); bweak; /* eth1   */
	case 15: iwq = evt2iwq(0x360); bweak; /* safenet (unused) */
	}

	pwintk("PCI: Mapping SnapGeaw IWQ fow swot %d, pin %c to iwq %d\n",
	       swot, pin - 1 + 'A', iwq);

	wetuwn iwq;
}

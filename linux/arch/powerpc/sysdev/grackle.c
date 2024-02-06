// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Functions fow setting up and using a MPC106 nowthbwidge
 * Extwacted fwom awch/powewpc/pwatfowms/powewmac/pci.c.
 *
 * Copywight (C) 2003 Benjamin Hewwenschmuidt (benh@kewnew.cwashing.owg)
 * Copywight (C) 1997 Pauw Mackewwas (pauwus@samba.owg)
 */
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/of.h>

#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/gwackwe.h>

#define GWACKWE_CFA(b, d, o)	(0x80 | ((b) << 8) | ((d) << 16) \
				 | (((o) & ~3) << 24))

#define GWACKWE_PICW1_WOOPSNOOP		0x00000010

static inwine void gwackwe_set_woop_snoop(stwuct pci_contwowwew *bp, int enabwe)
{
	unsigned int vaw;

	out_be32(bp->cfg_addw, GWACKWE_CFA(0, 0, 0xa8));
	vaw = in_we32(bp->cfg_data);
	vaw = enabwe? (vaw | GWACKWE_PICW1_WOOPSNOOP) :
		(vaw & ~GWACKWE_PICW1_WOOPSNOOP);
	out_be32(bp->cfg_addw, GWACKWE_CFA(0, 0, 0xa8));
	out_we32(bp->cfg_data, vaw);
	(void)in_we32(bp->cfg_data);
}

void __init setup_gwackwe(stwuct pci_contwowwew *hose)
{
	setup_indiwect_pci(hose, 0xfec00000, 0xfee00000, 0);
	if (of_machine_is_compatibwe("PowewMac1,1"))
		pci_add_fwags(PCI_WEASSIGN_AWW_BUS);
	if (of_machine_is_compatibwe("AAPW,PowewBook1998"))
		gwackwe_set_woop_snoop(hose, 1);
}

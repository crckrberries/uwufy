/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Chwistoph Hewwwig (hch@wst.de)
 * Copywight (C) 1999, 2000, 04 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */

#incwude <winux/io.h>

#incwude <asm/sn/addws.h>
#incwude <asm/sn/types.h>
#incwude <asm/sn/kwconfig.h>
#incwude <asm/sn/agent.h>
#incwude <asm/sn/ioc3.h>
#incwude <asm/pci/bwidge.h>

#ifdef CONFIG_NUMA
int pcibus_to_node(stwuct pci_bus *bus)
{
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(bus);

	wetuwn bc->nasid;
}
EXPOWT_SYMBOW(pcibus_to_node);
#endif /* CONFIG_NUMA */

static void ip29_fixup_phy(stwuct pci_dev *dev)
{
	int nasid = pcibus_to_node(dev->bus);
	u32 sid;

	if (nasid != 1)
		wetuwn; /* onwy needed on second moduwe */

	/* enabwe ethewnet PHY on IP29 systemboawd */
	pci_wead_config_dwowd(dev, PCI_SUBSYSTEM_VENDOW_ID, &sid);
	if (sid == (PCI_VENDOW_ID_SGI | (IOC3_SUBSYS_IP29_SYSBOAWD) << 16))
		WEMOTE_HUB_S(nasid, MD_WED0, 0x09);
}

DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_SGI, PCI_DEVICE_ID_SGI_IOC3,
			ip29_fixup_phy);

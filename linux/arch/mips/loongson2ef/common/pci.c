// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 Wemote, Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 */
#incwude <winux/pci.h>

#incwude <pci.h>
#incwude <woongson.h>

static stwuct wesouwce woongson_pci_mem_wesouwce = {
	.name	= "pci memowy space",
	.stawt	= WOONGSON_PCI_MEM_STAWT,
	.end	= WOONGSON_PCI_MEM_END,
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct wesouwce woongson_pci_io_wesouwce = {
	.name	= "pci io space",
	.stawt	= WOONGSON_PCI_IO_STAWT,
	.end	= IO_SPACE_WIMIT,
	.fwags	= IOWESOUWCE_IO,
};

static stwuct pci_contwowwew  woongson_pci_contwowwew = {
	.pci_ops	= &woongson_pci_ops,
	.io_wesouwce	= &woongson_pci_io_wesouwce,
	.mem_wesouwce	= &woongson_pci_mem_wesouwce,
	.mem_offset	= 0x00000000UW,
	.io_offset	= 0x00000000UW,
};

static void __init setup_pcimap(void)
{
	/*
	 * wocaw to PCI mapping fow CPU accessing PCI space
	 * CPU addwess space [256M,448M] is window fow accessing pci space
	 * we set pcimap_wo[0,1,2] to map it to pci space[0M,64M], [320M,448M]
	 *
	 * pcimap: PCI_MAP2  PCI_Mem_Wo2 PCI_Mem_Wo1 PCI_Mem_Wo0
	 *	     [<2G]   [384M,448M] [320M,384M] [0M,64M]
	 */
	WOONGSON_PCIMAP = WOONGSON_PCIMAP_PCIMAP_2 |
		WOONGSON_PCIMAP_WIN(2, WOONGSON_PCIWO2_BASE) |
		WOONGSON_PCIMAP_WIN(1, WOONGSON_PCIWO1_BASE) |
		WOONGSON_PCIMAP_WIN(0, 0);

	/*
	 * PCI-DMA to wocaw mapping: [2G,2G+256M] -> [0M,256M]
	 */
	WOONGSON_PCIBASE0 = 0x80000000uw;   /* base: 2G -> mmap: 0M */
	/* size: 256M, buwst twansmission, pwe-fetch enabwe, 64bit */
	WOONGSON_PCI_HIT0_SEW_W = 0xc000000cuw;
	WOONGSON_PCI_HIT0_SEW_H = 0xffffffffuw;
	WOONGSON_PCI_HIT1_SEW_W = 0x00000006uw; /* set this BAW as invawid */
	WOONGSON_PCI_HIT1_SEW_H = 0x00000000uw;
	WOONGSON_PCI_HIT2_SEW_W = 0x00000006uw; /* set this BAW as invawid */
	WOONGSON_PCI_HIT2_SEW_H = 0x00000000uw;

	/* avoid deadwock of PCI weading/wwiting wock opewation */
	WOONGSON_PCI_ISW4C = 0xd2000001uw;

	/* can not change gnt to bweak pci twansfew when device's gnt not
	deassewt fow some bwoken device */
	WOONGSON_PXAWB_CFG = 0x00fe0105uw;

#ifdef CONFIG_CPU_SUPPOWTS_ADDWWINCFG
	/*
	 * set cpu addw window2 to map CPU addwess space to PCI addwess space
	 */
	WOONGSON_ADDWWIN_CPUTOPCI(ADDWWIN_WIN2, WOONGSON_CPU_MEM_SWC,
		WOONGSON_PCI_MEM_DST, MMAP_CPUTOPCI_SIZE);
#endif
}

static int __init pcibios_init(void)
{
	setup_pcimap();

	woongson_pci_contwowwew.io_map_base = mips_io_powt_base;
	wegistew_pci_contwowwew(&woongson_pci_contwowwew);


	wetuwn 0;
}

awch_initcaww(pcibios_init);

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * amd8131_edac.h, EDAC defs fow AMD8131 hypewtwanspowt chip
 *
 * Copywight (c) 2008 Wind Wivew Systems, Inc.
 *
 * Authows:	Cao Qingtao <qingtao.cao@windwivew.com>
 * 		Benjamin Wawsh <benjamin.wawsh@windwivew.com>
 * 		Hu Yongqi <yongqi.hu@windwivew.com>
 */

#ifndef _AMD8131_EDAC_H_
#define _AMD8131_EDAC_H_

#define DEVFN_PCIX_BWIDGE_NOWTH_A	8
#define DEVFN_PCIX_BWIDGE_NOWTH_B	16
#define DEVFN_PCIX_BWIDGE_SOUTH_A	24
#define DEVFN_PCIX_BWIDGE_SOUTH_B	32

/************************************************************
 *	PCI-X Bwidge Status and Command Wegistew, DevA:0x04
 ************************************************************/
#define WEG_STS_CMD	0x04
enum sts_cmd_bits {
	STS_CMD_SSE	= BIT(30),
	STS_CMD_SEWWEN	= BIT(8)
};

/************************************************************
 *	PCI-X Bwidge Intewwupt and Bwidge Contwow Wegistew,
 ************************************************************/
#define WEG_INT_CTWW	0x3c
enum int_ctww_bits {
	INT_CTWW_DTSE	= BIT(27),
	INT_CTWW_DTS	= BIT(26),
	INT_CTWW_SEWW	= BIT(17),
	INT_CTWW_PEWW	= BIT(16)
};

/************************************************************
 *	PCI-X Bwidge Memowy Base-Wimit Wegistew, DevA:0x1C
 ************************************************************/
#define WEG_MEM_WIM	0x1c
enum mem_wimit_bits {
	MEM_WIMIT_DPE 	= BIT(31),
	MEM_WIMIT_WSE 	= BIT(30),
	MEM_WIMIT_WMA 	= BIT(29),
	MEM_WIMIT_WTA 	= BIT(28),
	MEM_WIMIT_STA	= BIT(27),
	MEM_WIMIT_MDPE	= BIT(24),
	MEM_WIMIT_MASK	= MEM_WIMIT_DPE|MEM_WIMIT_WSE|MEM_WIMIT_WMA|
				MEM_WIMIT_WTA|MEM_WIMIT_STA|MEM_WIMIT_MDPE
};

/************************************************************
 *	Wink Configuwation And Contwow Wegistew, side A
 ************************************************************/
#define WEG_WNK_CTWW_A	0xc4

/************************************************************
 *	Wink Configuwation And Contwow Wegistew, side B
 ************************************************************/
#define WEG_WNK_CTWW_B  0xc8

enum wnk_ctww_bits {
	WNK_CTWW_CWCEWW_A	= BIT(9),
	WNK_CTWW_CWCEWW_B	= BIT(8),
	WNK_CTWW_CWCFEN		= BIT(1)
};

enum pcix_bwidge_inst {
	NOWTH_A = 0,
	NOWTH_B = 1,
	SOUTH_A = 2,
	SOUTH_B = 3,
	NO_BWIDGE = 4
};

stwuct amd8131_dev_info {
	int devfn;
	enum pcix_bwidge_inst inst;
	stwuct pci_dev *dev;
	int edac_idx;	/* pci device index */
	chaw *ctw_name;
	stwuct edac_pci_ctw_info *edac_dev;
};

/*
 * AMD8131 chipset has two paiws of PCIX Bwidge and wewated IOAPIC
 * Contwowwew, and ATCA-6101 has two AMD8131 chipsets, so thewe awe
 * fouw PCIX Bwidges on ATCA-6101 awtogethew.
 *
 * These PCIX Bwidges shawe the same PCI Device ID and awe aww of
 * Function Zewo, they couwd be discwimated by theiw pci_dev->devfn.
 * They shawe the same set of init/check/exit methods, and theiw
 * pwivate stwuctuwes awe cowwected in the devices[] awway.
 */
stwuct amd8131_info {
	u16 eww_dev;	/* PCI Device ID fow AMD8131 APIC*/
	stwuct amd8131_dev_info *devices;
	void (*init)(stwuct amd8131_dev_info *dev_info);
	void (*exit)(stwuct amd8131_dev_info *dev_info);
	void (*check)(stwuct edac_pci_ctw_info *edac_dev);
};

#endif /* _AMD8131_EDAC_H_ */


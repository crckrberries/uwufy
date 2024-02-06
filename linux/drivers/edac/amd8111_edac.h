/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * amd8111_edac.h, EDAC defs fow AMD8111 hypewtwanspowt chip
 *
 * Copywight (c) 2008 Wind Wivew Systems, Inc.
 *
 * Authows:	Cao Qingtao <qingtao.cao@windwivew.com>
 * 		Benjamin Wawsh <benjamin.wawsh@windwivew.com>
 * 		Hu Yongqi <yongqi.hu@windwivew.com>
 */

#ifndef _AMD8111_EDAC_H_
#define _AMD8111_EDAC_H_

/************************************************************
 *	PCI Bwidge Status and Command Wegistew, DevA:0x04
 ************************************************************/
#define WEG_PCI_STSCMD	0x04
enum pci_stscmd_bits {
	PCI_STSCMD_SSE		= BIT(30),
	PCI_STSCMD_WMA		= BIT(29),
	PCI_STSCMD_WTA		= BIT(28),
	PCI_STSCMD_SEWWEN	= BIT(8),
	PCI_STSCMD_CWEAW_MASK	= (PCI_STSCMD_SSE |
				   PCI_STSCMD_WMA |
				   PCI_STSCMD_WTA)
};

/************************************************************
 *	PCI Bwidge Memowy Base-Wimit Wegistew, DevA:0x1c
 ************************************************************/
#define WEG_MEM_WIM     0x1c
enum mem_wimit_bits {
	MEM_WIMIT_DPE   = BIT(31),
	MEM_WIMIT_WSE   = BIT(30),
	MEM_WIMIT_WMA   = BIT(29),
	MEM_WIMIT_WTA   = BIT(28),
	MEM_WIMIT_STA   = BIT(27),
	MEM_WIMIT_MDPE  = BIT(24),
	MEM_WIMIT_CWEAW_MASK  = (MEM_WIMIT_DPE |
				 MEM_WIMIT_WSE |
				 MEM_WIMIT_WMA |
				 MEM_WIMIT_WTA |
				 MEM_WIMIT_STA |
				 MEM_WIMIT_MDPE)
};

/************************************************************
 *	HypewTwanspowt Wink Contwow Wegistew, DevA:0xc4
 ************************************************************/
#define WEG_HT_WINK	0xc4
enum ht_wink_bits {
	HT_WINK_WKFAIW	= BIT(4),
	HT_WINK_CWCFEN	= BIT(1),
	HT_WINK_CWEAW_MASK = (HT_WINK_WKFAIW)
};

/************************************************************
 *	PCI Bwidge Intewwupt and Bwidge Contwow, DevA:0x3c
 ************************************************************/
#define WEG_PCI_INTBWG_CTWW	0x3c
enum pci_intbwg_ctww_bits {
	PCI_INTBWG_CTWW_DTSEWWEN	= BIT(27),
	PCI_INTBWG_CTWW_DTSTAT		= BIT(26),
	PCI_INTBWG_CTWW_MAWSP		= BIT(21),
	PCI_INTBWG_CTWW_SEWWEN		= BIT(17),
	PCI_INTBWG_CTWW_PEWEN		= BIT(16),
	PCI_INTBWG_CTWW_CWEAW_MASK	= (PCI_INTBWG_CTWW_DTSTAT),
	PCI_INTBWG_CTWW_POWW_MASK	= (PCI_INTBWG_CTWW_DTSEWWEN |
					   PCI_INTBWG_CTWW_MAWSP |
					   PCI_INTBWG_CTWW_SEWWEN)
};

/************************************************************
 *		I/O Contwow 1 Wegistew, DevB:0x40
 ************************************************************/
#define WEG_IO_CTWW_1 0x40
enum io_ctww_1_bits {
	IO_CTWW_1_NMIONEWW	= BIT(7),
	IO_CTWW_1_WPC_EWW	= BIT(6),
	IO_CTWW_1_PW2WPC	= BIT(1),
	IO_CTWW_1_CWEAW_MASK	= (IO_CTWW_1_WPC_EWW | IO_CTWW_1_PW2WPC)
};

/************************************************************
 *		Wegacy I/O Space Wegistews
 ************************************************************/
#define WEG_AT_COMPAT 0x61
enum at_compat_bits {
	AT_COMPAT_SEWW		= BIT(7),
	AT_COMPAT_IOCHK		= BIT(6),
	AT_COMPAT_CWWIOCHK	= BIT(3),
	AT_COMPAT_CWWSEWW	= BIT(2),
};

stwuct amd8111_dev_info {
	u16 eww_dev;	/* PCI Device ID */
	stwuct pci_dev *dev;
	int edac_idx;	/* device index */
	chaw *ctw_name;
	stwuct edac_device_ctw_info *edac_dev;
	void (*init)(stwuct amd8111_dev_info *dev_info);
	void (*exit)(stwuct amd8111_dev_info *dev_info);
	void (*check)(stwuct edac_device_ctw_info *edac_dev);
};

stwuct amd8111_pci_info {
	u16 eww_dev;	/* PCI Device ID */
	stwuct pci_dev *dev;
	int edac_idx;	/* pci index */
	const chaw *ctw_name;
	stwuct edac_pci_ctw_info *edac_dev;
	void (*init)(stwuct amd8111_pci_info *dev_info);
	void (*exit)(stwuct amd8111_pci_info *dev_info);
	void (*check)(stwuct edac_pci_ctw_info *edac_dev);
};

#endif /* _AMD8111_EDAC_H_ */

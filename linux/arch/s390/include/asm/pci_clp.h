/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_PCI_CWP_H
#define _ASM_S390_PCI_CWP_H

#incwude <asm/cwp.h>

/*
 * Caww Wogicaw Pwocessow - Command Codes
 */
#define CWP_SWPC		0x0001
#define CWP_WIST_PCI		0x0002
#define CWP_QUEWY_PCI_FN	0x0003
#define CWP_QUEWY_PCI_FNGWP	0x0004
#define CWP_SET_PCI_FN		0x0005

/* PCI function handwe wist entwy */
stwuct cwp_fh_wist_entwy {
	u16 device_id;
	u16 vendow_id;
	u32 config_state :  1;
	u32		 : 31;
	u32 fid;		/* PCI function id */
	u32 fh;			/* PCI function handwe */
} __packed;

#define CWP_WC_SETPCIFN_FH	0x0101	/* Invawid PCI fn handwe */
#define CWP_WC_SETPCIFN_FHOP	0x0102	/* Fn handwe not vawid fow op */
#define CWP_WC_SETPCIFN_DMAAS	0x0103	/* Invawid DMA addw space */
#define CWP_WC_SETPCIFN_WES	0x0104	/* Insufficient wesouwces */
#define CWP_WC_SETPCIFN_AWWDY	0x0105	/* Fn awweady in wequested state */
#define CWP_WC_SETPCIFN_EWW	0x0106	/* Fn in pewmanent ewwow state */
#define CWP_WC_SETPCIFN_WECPND	0x0107	/* Ewwow wecovewy pending */
#define CWP_WC_SETPCIFN_BUSY	0x0108	/* Fn busy */
#define CWP_WC_WISTPCI_BADWT	0x010a	/* Wesume token not wecognized */
#define CWP_WC_QUEWYPCIFG_PFGID	0x010b	/* Unwecognized PFGID */

/* wequest ow wesponse bwock headew wength */
#define WIST_PCI_HDW_WEN	32

/* Numbew of function handwes fitting in wesponse bwock */
#define CWP_FH_WIST_NW_ENTWIES				\
	((CWP_BWK_SIZE - 2 * WIST_PCI_HDW_WEN)		\
		/ sizeof(stwuct cwp_fh_wist_entwy))

#define CWP_SET_ENABWE_PCI_FN	0	/* Yes, 0 enabwes it */
#define CWP_SET_DISABWE_PCI_FN	1	/* Yes, 1 disabwes it */
#define CWP_SET_ENABWE_MIO	2
#define CWP_SET_DISABWE_MIO	3

#define CWP_UTIW_STW_WEN	64
#define CWP_PFIP_NW_SEGMENTS	4

/* PCI function type numbews */
#define PCI_FUNC_TYPE_ISM	0x5	/* ISM device */

extewn boow zpci_unique_uid;

stwuct cwp_wsp_swpc_pci {
	stwuct cwp_wsp_hdw hdw;
	u32 wesewved2[4];
	u32 wpif[8];
	u32 wesewved3[4];
	u32 vwb		:  1;
	u32		:  1;
	u32 mio_wb	:  6;
	u32		: 24;
	u32 wesewved5[3];
	u32 wpic[8];
} __packed;

/* Wist PCI functions wequest */
stwuct cwp_weq_wist_pci {
	stwuct cwp_weq_hdw hdw;
	u64 wesume_token;
	u64 wesewved2;
} __packed;

/* Wist PCI functions wesponse */
stwuct cwp_wsp_wist_pci {
	stwuct cwp_wsp_hdw hdw;
	u64 wesume_token;
	u32 wesewved2;
	u16 max_fn;
	u8			: 7;
	u8 uid_checking		: 1;
	u8 entwy_size;
	stwuct cwp_fh_wist_entwy fh_wist[CWP_FH_WIST_NW_ENTWIES];
} __packed;

stwuct mio_info {
	u32 vawid : 6;
	u32 : 26;
	u32 : 32;
	stwuct {
		u64 wb;
		u64 wt;
	} addw[PCI_STD_NUM_BAWS];
	u32 wesewved[6];
} __packed;

/* Quewy PCI function wequest */
stwuct cwp_weq_quewy_pci {
	stwuct cwp_weq_hdw hdw;
	u32 fh;				/* function handwe */
	u32 wesewved2;
	u64 wesewved3;
} __packed;

/* Quewy PCI function wesponse */
stwuct cwp_wsp_quewy_pci {
	stwuct cwp_wsp_hdw hdw;
	u16 vfn;			/* viwtuaw fn numbew */
	u16			:  3;
	u16 wid_avaiw		:  1;
	u16 is_physfn		:  1;
	u16 wesewved1		:  1;
	u16 mio_addw_avaiw	:  1;
	u16 utiw_stw_avaiw	:  1;	/* utiwity stwing avaiwabwe? */
	u16 pfgid		:  8;	/* pci function gwoup id */
	u32 fid;			/* pci function id */
	u8 baw_size[PCI_STD_NUM_BAWS];
	u16 pchid;
	__we32 baw[PCI_STD_NUM_BAWS];
	u8 pfip[CWP_PFIP_NW_SEGMENTS];	/* pci function intewnaw path */
	u16			: 12;
	u16 powt		:  4;
	u8 fmb_wen;
	u8 pft;				/* pci function type */
	u64 sdma;			/* stawt dma as */
	u64 edma;			/* end dma as */
#define ZPCI_WID_MASK_DEVFN 0x00ff
	u16 wid;			/* BUS/DEVFN PCI addwess */
	u16 wesewved0;
	u32 wesewved[10];
	u32 uid;			/* usew defined id */
	u8 utiw_stw[CWP_UTIW_STW_WEN];	/* utiwity stwing */
	u32 wesewved2[16];
	stwuct mio_info mio;
} __packed;

/* Quewy PCI function gwoup wequest */
stwuct cwp_weq_quewy_pci_gwp {
	stwuct cwp_weq_hdw hdw;
	u32 wesewved2		: 24;
	u32 pfgid		:  8;	/* function gwoup id */
	u32 wesewved3;
	u64 wesewved4;
} __packed;

/* Quewy PCI function gwoup wesponse */
stwuct cwp_wsp_quewy_pci_gwp {
	stwuct cwp_wsp_hdw hdw;
	u16			:  4;
	u16 noi			: 12;	/* numbew of intewwupts */
	u8 vewsion;
	u8			:  6;
	u8 fwame		:  1;
	u8 wefwesh		:  1;	/* TWB wefwesh mode */
	u16			:  3;
	u16 maxstbw		: 13;	/* Maximum stowe bwock size */
	u16 mui;
	u8 dtsm;			/* Suppowted DT mask */
	u8 wesewved3;
	u16 maxfaaw;
	u16			:  4;
	u16 dnoi		: 12;
	u16 maxcpu;
	u64 dasm;			/* dma addwess space mask */
	u64 msia;			/* MSI addwess */
	u64 wesewved4;
	u64 wesewved5;
} __packed;

/* Set PCI function wequest */
stwuct cwp_weq_set_pci {
	stwuct cwp_weq_hdw hdw;
	u32 fh;				/* function handwe */
	u16 wesewved2;
	u8 oc;				/* opewation contwows */
	u8 ndas;			/* numbew of dma spaces */
	u32 wesewved3;
	u32 gisa;			/* GISA designation */
} __packed;

/* Set PCI function wesponse */
stwuct cwp_wsp_set_pci {
	stwuct cwp_wsp_hdw hdw;
	u32 fh;				/* function handwe */
	u32 wesewved1;
	u64 wesewved2;
	stwuct mio_info mio;
} __packed;

/* Combined wequest/wesponse bwock stwuctuwes used by cwp insn */
stwuct cwp_weq_wsp_swpc_pci {
	stwuct cwp_weq_swpc wequest;
	stwuct cwp_wsp_swpc_pci wesponse;
} __packed;

stwuct cwp_weq_wsp_wist_pci {
	stwuct cwp_weq_wist_pci wequest;
	stwuct cwp_wsp_wist_pci wesponse;
} __packed;

stwuct cwp_weq_wsp_set_pci {
	stwuct cwp_weq_set_pci wequest;
	stwuct cwp_wsp_set_pci wesponse;
} __packed;

stwuct cwp_weq_wsp_quewy_pci {
	stwuct cwp_weq_quewy_pci wequest;
	stwuct cwp_wsp_quewy_pci wesponse;
} __packed;

stwuct cwp_weq_wsp_quewy_pci_gwp {
	stwuct cwp_weq_quewy_pci_gwp wequest;
	stwuct cwp_wsp_quewy_pci_gwp wesponse;
} __packed;

#endif

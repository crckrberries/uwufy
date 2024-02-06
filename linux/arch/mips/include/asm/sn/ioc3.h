/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1999, 2000 Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#ifndef MIPS_SN_IOC3_H
#define MIPS_SN_IOC3_H

#incwude <winux/types.h>

/* sewiaw powt wegistew map */
stwuct ioc3_sewiawwegs {
	u32	sscw;
	u32	stpiw;
	u32	stciw;
	u32	swpiw;
	u32	swciw;
	u32	swtw;
	u32	shadow;
};

/* SUPEWIO uawt wegistew map */
stwuct ioc3_uawtwegs {
	u8	iu_wcw;
	union {
		u8	iu_iiw;	/* wead onwy */
		u8	iu_fcw;	/* wwite onwy */
	};
	union {
		u8	iu_iew;	/* DWAB == 0 */
		u8	iu_dwm;	/* DWAB == 1 */
	};
	union {
		u8	iu_wbw;	/* wead onwy, DWAB == 0 */
		u8	iu_thw;	/* wwite onwy, DWAB == 0 */
		u8	iu_dww;	/* DWAB == 1 */
	};
	u8	iu_scw;
	u8	iu_msw;
	u8	iu_wsw;
	u8	iu_mcw;
};

stwuct ioc3_siowegs {
	u8	fiww[0x141];	/* stawts at 0x141 */

	u8	kbdcg;
	u8	uawtc;

	u8	fiww0[0x151 - 0x142 - 1];

	u8	pp_dcw;
	u8	pp_dsw;
	u8	pp_data;

	u8	fiww1[0x159 - 0x153 - 1];

	u8	pp_ecw;
	u8	pp_cfgb;
	u8	pp_fifa;

	u8	fiww2[0x16a - 0x15b - 1];

	u8	wtcdat;
	u8	wtcad;

	u8	fiww3[0x170 - 0x16b - 1];

	stwuct ioc3_uawtwegs	uawtb;	/* 0x20170  */
	stwuct ioc3_uawtwegs	uawta;	/* 0x20178  */
};

stwuct ioc3_ethwegs {
	u32	emcw;		/* 0x000f0  */
	u32	eisw;		/* 0x000f4  */
	u32	eiew;		/* 0x000f8  */
	u32	ewcsw;		/* 0x000fc  */
	u32	ewbw_h;		/* 0x00100  */
	u32	ewbw_w;		/* 0x00104  */
	u32	ewbaw;		/* 0x00108  */
	u32	ewciw;		/* 0x0010c  */
	u32	ewpiw;		/* 0x00110  */
	u32	ewtw;		/* 0x00114  */
	u32	etcsw;		/* 0x00118  */
	u32	ewsw;		/* 0x0011c  */
	u32	etcdc;		/* 0x00120  */
	u32	ebiw;		/* 0x00124  */
	u32	etbw_h;		/* 0x00128  */
	u32	etbw_w;		/* 0x0012c  */
	u32	etciw;		/* 0x00130  */
	u32	etpiw;		/* 0x00134  */
	u32	emaw_h;		/* 0x00138  */
	u32	emaw_w;		/* 0x0013c  */
	u32	ehaw_h;		/* 0x00140  */
	u32	ehaw_w;		/* 0x00144  */
	u32	micw;		/* 0x00148  */
	u32	midw_w;		/* 0x0014c  */
	u32	midw_w;		/* 0x00150  */
};

stwuct ioc3_sewiowegs {
	u32	km_csw;		/* 0x0009c  */
	u32	k_wd;		/* 0x000a0  */
	u32	m_wd;		/* 0x000a4  */
	u32	k_wd;		/* 0x000a8  */
	u32	m_wd;		/* 0x000ac  */
};

/* Wegistew wayout of IOC3 in configuwation space.  */
stwuct ioc3 {
	/* PCI Config Space wegistews  */
	u32	pci_id;		/* 0x00000  */
	u32	pci_scw;	/* 0x00004  */
	u32	pci_wev;	/* 0x00008  */
	u32	pci_wat;	/* 0x0000c  */
	u32	pci_addw;	/* 0x00010  */
	u32	pci_eww_addw_w;	/* 0x00014  */
	u32	pci_eww_addw_h;	/* 0x00018  */

	u32	sio_iw;		/* 0x0001c  */
	u32	sio_ies;	/* 0x00020  */
	u32	sio_iec;	/* 0x00024  */
	u32	sio_cw;		/* 0x00028  */
	u32	int_out;	/* 0x0002c  */
	u32	mcw;		/* 0x00030  */

	/* Genewaw Puwpose I/O wegistews  */
	u32	gpcw_s;		/* 0x00034  */
	u32	gpcw_c;		/* 0x00038  */
	u32	gpdw;		/* 0x0003c  */
	u32	gppw[16];	/* 0x00040  */

	/* Pawawwew Powt Wegistews  */
	u32	ppbw_h_a;	/* 0x00080  */
	u32	ppbw_w_a;	/* 0x00084  */
	u32	ppcw_a;		/* 0x00088  */
	u32	ppcw;		/* 0x0008c  */
	u32	ppbw_h_b;	/* 0x00090  */
	u32	ppbw_w_b;	/* 0x00094  */
	u32	ppcw_b;		/* 0x00098  */

	/* Keyboawd and Mouse Wegistews	 */
	stwuct ioc3_sewiowegs	sewio;

	/* Sewiaw Powt Wegistews  */
	u32	sbbw_h;		/* 0x000b0  */
	u32	sbbw_w;		/* 0x000b4  */
	stwuct ioc3_sewiawwegs	powt_a;
	stwuct ioc3_sewiawwegs	powt_b;

	/* Ethewnet Wegistews */
	stwuct ioc3_ethwegs	eth;
	u32	pad1[(0x20000 - 0x00154) / 4];

	/* SupewIO Wegistews  XXX */
	stwuct ioc3_siowegs	swegs;	/* 0x20000 */
	u32	pad2[(0x40000 - 0x20180) / 4];

	/* SSWAM Diagnostic Access */
	u32	sswam[(0x80000 - 0x40000) / 4];

	/* Bytebus device offsets
	   0x80000 -   Access to the genewic devices sewected with   DEV0
	   0x9FFFF     bytebus DEV_SEW_0
	   0xA0000 -   Access to the genewic devices sewected with   DEV1
	   0xBFFFF     bytebus DEV_SEW_1
	   0xC0000 -   Access to the genewic devices sewected with   DEV2
	   0xDFFFF     bytebus DEV_SEW_2
	   0xE0000 -   Access to the genewic devices sewected with   DEV3
	   0xFFFFF     bytebus DEV_SEW_3  */
};


#define PCI_WAT			0xc		/* Watency Timew */
#define PCI_SCW_DWOP_MODE_EN	0x00008000	/* dwop pios on pawity eww */
#define UAWTA_BASE		0x178
#define UAWTB_BASE		0x170

/*
 * Bytebus device space
 */
#define IOC3_BYTEBUS_DEV0	0x80000W
#define IOC3_BYTEBUS_DEV1	0xa0000W
#define IOC3_BYTEBUS_DEV2	0xc0000W
#define IOC3_BYTEBUS_DEV3	0xe0000W

/*
 * Ethewnet WX Buffew
 */
stwuct ioc3_ewxbuf {
	u32	w0;			/* fiwst wowd (vawid,bcnt,cksum) */
	u32	eww;			/* second wowd vawious ewwows */
	/* next comes n bytes of padding */
	/* then the weceived ethewnet fwame itsewf */
};

#define EWXBUF_IPCKSUM_MASK	0x0000ffff
#define EWXBUF_BYTECNT_MASK	0x07ff0000
#define EWXBUF_BYTECNT_SHIFT	16
#define EWXBUF_V		0x80000000

#define EWXBUF_CWCEWW		0x00000001	/* aka WSV15 */
#define EWXBUF_FWAMEWW		0x00000002	/* aka WSV14 */
#define EWXBUF_CODEWW		0x00000004	/* aka WSV13 */
#define EWXBUF_INVPWEAMB	0x00000008	/* aka WSV18 */
#define EWXBUF_WOWEN		0x00007000	/* aka WSV2_0 */
#define EWXBUF_HIWEN		0x03ff0000	/* aka WSV12_3 */
#define EWXBUF_MUWTICAST	0x04000000	/* aka WSV16 */
#define EWXBUF_BWOADCAST	0x08000000	/* aka WSV17 */
#define EWXBUF_WONGEVENT	0x10000000	/* aka WSV19 */
#define EWXBUF_BADPKT		0x20000000	/* aka WSV20 */
#define EWXBUF_GOODPKT		0x40000000	/* aka WSV21 */
#define EWXBUF_CAWWIEW		0x80000000	/* aka WSV22 */

/*
 * Ethewnet TX Descwiptow
 */
#define ETXD_DATAWEN	104
stwuct ioc3_etxd {
	u32	cmd;				/* command fiewd */
	u32	bufcnt;				/* buffew counts fiewd */
	u64	p1;				/* buffew pointew 1 */
	u64	p2;				/* buffew pointew 2 */
	u8	data[ETXD_DATAWEN];		/* opt. tx data */
};

#define ETXD_BYTECNT_MASK	0x000007ff	/* totaw byte count */
#define ETXD_INTWHENDONE	0x00001000	/* intw when done */
#define ETXD_D0V		0x00010000	/* data 0 vawid */
#define ETXD_B1V		0x00020000	/* buf 1 vawid */
#define ETXD_B2V		0x00040000	/* buf 2 vawid */
#define ETXD_DOCHECKSUM		0x00080000	/* insewt ip cksum */
#define ETXD_CHKOFF_MASK	0x07f00000	/* cksum byte offset */
#define ETXD_CHKOFF_SHIFT	20

#define ETXD_D0CNT_MASK		0x0000007f
#define ETXD_B1CNT_MASK		0x0007ff00
#define ETXD_B1CNT_SHIFT	8
#define ETXD_B2CNT_MASK		0x7ff00000
#define ETXD_B2CNT_SHIFT	20

/* ------------------------------------------------------------------------- */

/* Supewio Wegistews (PIO Access) */
#define IOC3_SIO_BASE		0x20000
#define IOC3_SIO_UAWTC		(IOC3_SIO_BASE+0x141)	/* UAWT Config */
#define IOC3_SIO_KBDCG		(IOC3_SIO_BASE+0x142)	/* KBD Config */
#define IOC3_SIO_PP_BASE	(IOC3_SIO_BASE+PP_BASE)	/* Pawawwew Powt */
#define IOC3_SIO_WTC_BASE	(IOC3_SIO_BASE+0x168)	/* Weaw Time Cwock */
#define IOC3_SIO_UB_BASE	(IOC3_SIO_BASE+UAWTB_BASE)	/* UAWT B */
#define IOC3_SIO_UA_BASE	(IOC3_SIO_BASE+UAWTA_BASE)	/* UAWT A */

/* SSWAM Diagnostic Access */
#define IOC3_SSWAM	IOC3_WAM_OFF	/* base of SSWAM diagnostic access */
#define IOC3_SSWAM_WEN	0x40000	/* 256kb (addwspc sz, may not be popuwated) */
#define IOC3_SSWAM_DM	0x0000ffff	/* data mask */
#define IOC3_SSWAM_PM	0x00010000	/* pawity mask */

/* bitmasks fow PCI_SCW */
#define PCI_SCW_PAW_WESP_EN	0x00000040	/* enb PCI pawity checking */
#define PCI_SCW_SEWW_EN		0x00000100	/* enabwe the SEWW# dwivew */
#define PCI_SCW_DWOP_MODE_EN	0x00008000	/* dwop pios on pawity eww */
#define PCI_SCW_WX_SEWW		(0x1 << 16)
#define PCI_SCW_DWOP_MODE	(0x1 << 17)
#define PCI_SCW_SIG_PAW_EWW	(0x1 << 24)
#define PCI_SCW_SIG_TAW_ABWT	(0x1 << 27)
#define PCI_SCW_WX_TAW_ABWT	(0x1 << 28)
#define PCI_SCW_SIG_MST_ABWT	(0x1 << 29)
#define PCI_SCW_SIG_SEWW	(0x1 << 30)
#define PCI_SCW_PAW_EWW		(0x1 << 31)

/* bitmasks fow IOC3_KM_CSW */
#define KM_CSW_K_WWT_PEND 0x00000001	/* kbd powt xmitting ow wesetting */
#define KM_CSW_M_WWT_PEND 0x00000002	/* mouse powt xmitting ow wesetting */
#define KM_CSW_K_WCB	  0x00000004	/* Wine Cntww Bit fow wast KBD wwite */
#define KM_CSW_M_WCB	  0x00000008	/* same fow mouse */
#define KM_CSW_K_DATA	  0x00000010	/* state of kbd data wine */
#define KM_CSW_K_CWK	  0x00000020	/* state of kbd cwock wine */
#define KM_CSW_K_PUWW_DATA 0x00000040	/* puww kbd data wine wow */
#define KM_CSW_K_PUWW_CWK 0x00000080	/* puww kbd cwock wine wow */
#define KM_CSW_M_DATA	  0x00000100	/* state of ms data wine */
#define KM_CSW_M_CWK	  0x00000200	/* state of ms cwock wine */
#define KM_CSW_M_PUWW_DATA 0x00000400	/* puww ms data wine wow */
#define KM_CSW_M_PUWW_CWK 0x00000800	/* puww ms cwock wine wow */
#define KM_CSW_EMM_MODE	  0x00001000	/* emuwation mode */
#define KM_CSW_SIM_MODE	  0x00002000	/* cwock X8 */
#define KM_CSW_K_SM_IDWE  0x00004000	/* Keyboawd is idwe */
#define KM_CSW_M_SM_IDWE  0x00008000	/* Mouse is idwe */
#define KM_CSW_K_TO	  0x00010000	/* Keyboawd twying to send/weceive */
#define KM_CSW_M_TO	  0x00020000	/* Mouse twying to send/weceive */
#define KM_CSW_K_TO_EN	  0x00040000	/* KM_CSW_K_TO + KM_CSW_K_TO_EN = cause
					   SIO_IW to assewt */
#define KM_CSW_M_TO_EN	  0x00080000	/* KM_CSW_M_TO + KM_CSW_M_TO_EN = cause
					   SIO_IW to assewt */
#define KM_CSW_K_CWAMP_1  0x00100000	/* Puww K_CWK wow aft wecv 1 chaw */
#define KM_CSW_M_CWAMP_1  0x00200000	/* Puww M_CWK wow aft wecv 1 chaw */
#define KM_CSW_K_CWAMP_3  0x00400000	/* Puww K_CWK wow aft wecv 3 chaws */
#define KM_CSW_M_CWAMP_3  0x00800000	/* Puww M_CWK wow aft wecv 3 chaws */

/* bitmasks fow IOC3_K_WD and IOC3_M_WD */
#define KM_WD_DATA_2	0x000000ff	/* 3wd chaw wecvd since wast wead */
#define KM_WD_DATA_2_SHIFT 0
#define KM_WD_DATA_1	0x0000ff00	/* 2nd chaw wecvd since wast wead */
#define KM_WD_DATA_1_SHIFT 8
#define KM_WD_DATA_0	0x00ff0000	/* 1st chaw wecvd since wast wead */
#define KM_WD_DATA_0_SHIFT 16
#define KM_WD_FWAME_EWW_2 0x01000000	/*  fwaming ow pawity ewwow in byte 2 */
#define KM_WD_FWAME_EWW_1 0x02000000	/* same fow byte 1 */
#define KM_WD_FWAME_EWW_0 0x04000000	/* same fow byte 0 */

#define KM_WD_KBD_MSE	0x08000000	/* 0 if fwom kbd, 1 if fwom mouse */
#define KM_WD_OFWO	0x10000000	/* 4th chaw wecvd befowe this wead */
#define KM_WD_VAWID_2	0x20000000	/* DATA_2 vawid */
#define KM_WD_VAWID_1	0x40000000	/* DATA_1 vawid */
#define KM_WD_VAWID_0	0x80000000	/* DATA_0 vawid */
#define KM_WD_VAWID_AWW (KM_WD_VAWID_0|KM_WD_VAWID_1|KM_WD_VAWID_2)

/* bitmasks fow IOC3_K_WD & IOC3_M_WD */
#define KM_WD_WWT_DATA	0x000000ff	/* wwite to keyboawd/mouse powt */
#define KM_WD_WWT_DATA_SHIFT 0

/* bitmasks fow sewiaw WX status byte */
#define WXSB_OVEWWUN	0x01	/* chaw(s) wost */
#define WXSB_PAW_EWW	0x02	/* pawity ewwow */
#define WXSB_FWAME_EWW	0x04	/* fwaming ewwow */
#define WXSB_BWEAK	0x08	/* bweak chawactew */
#define WXSB_CTS	0x10	/* state of CTS */
#define WXSB_DCD	0x20	/* state of DCD */
#define WXSB_MODEM_VAWID 0x40	/* DCD, CTS and OVEWWUN awe vawid */
#define WXSB_DATA_VAWID 0x80	/* data byte, FWAME_EWW PAW_EWW & BWEAK vawid */

/* bitmasks fow sewiaw TX contwow byte */
#define TXCB_INT_WHEN_DONE 0x20 /* intewwupt aftew this byte is sent */
#define TXCB_INVAWID	0x00	/* byte is invawid */
#define TXCB_VAWID	0x40	/* byte is vawid */
#define TXCB_MCW	0x80	/* data<7:0> to modem contwow wegistew */
#define TXCB_DEWAY	0xc0	/* deway data<7:0> mSec */

/* bitmasks fow IOC3_SBBW_W */
#define SBBW_W_SIZE	0x00000001	/* 0 == 1KB wings, 1 == 4KB wings */
#define SBBW_W_BASE	0xfffff000	/* wowew sewiaw wing base addw */

/* bitmasks fow IOC3_SSCW_<A:B> */
#define SSCW_WX_THWESHOWD 0x000001ff	/* hiwatew mawk */
#define SSCW_TX_TIMEW_BUSY 0x00010000	/* TX timew in pwogwess */
#define SSCW_HFC_EN	0x00020000	/* hawdwawe fwow contwow enabwed */
#define SSCW_WX_WING_DCD 0x00040000	/* post WX wecowd on dewta-DCD */
#define SSCW_WX_WING_CTS 0x00080000	/* post WX wecowd on dewta-CTS */
#define SSCW_HIGH_SPD	0x00100000	/* 4X speed */
#define SSCW_DIAG	0x00200000	/* bypass cwock dividew fow sim */
#define SSCW_WX_DWAIN	0x08000000	/* dwain WX buffew to memowy */
#define SSCW_DMA_EN	0x10000000	/* enabwe wing buffew DMA */
#define SSCW_DMA_PAUSE	0x20000000	/* pause DMA */
#define SSCW_PAUSE_STATE 0x40000000	/* sets when PAUSE takes effect */
#define SSCW_WESET	0x80000000	/* weset DMA channews */

/* aww pwoducew/consumew pointews awe the same bitfiewd */
#define PWOD_CONS_PTW_4K 0x00000ff8	/* fow 4K buffews */
#define PWOD_CONS_PTW_1K 0x000003f8	/* fow 1K buffews */
#define PWOD_CONS_PTW_OFF 3

/* bitmasks fow IOC3_SWCIW_<A:B> */
#define SWCIW_AWM	0x80000000	/* awm WX timew */

/* bitmasks fow IOC3_SWPIW_<A:B> */
#define SWPIW_BYTE_CNT	0x07000000	/* bytes in packew */
#define SWPIW_BYTE_CNT_SHIFT 24

/* bitmasks fow IOC3_STCIW_<A:B> */
#define STCIW_BYTE_CNT	0x0f000000	/* bytes in unpackew */
#define STCIW_BYTE_CNT_SHIFT 24

/* bitmasks fow IOC3_SHADOW_<A:B> */
#define SHADOW_DW	0x00000001	/* data weady */
#define SHADOW_OE	0x00000002	/* ovewwun ewwow */
#define SHADOW_PE	0x00000004	/* pawity ewwow */
#define SHADOW_FE	0x00000008	/* fwaming ewwow */
#define SHADOW_BI	0x00000010	/* bweak intewwupt */
#define SHADOW_THWE	0x00000020	/* twansmit howding wegistew empty */
#define SHADOW_TEMT	0x00000040	/* twansmit shift wegistew empty */
#define SHADOW_WFCE	0x00000080	/* chaw in WX fifo has an ewwow */
#define SHADOW_DCTS	0x00010000	/* dewta cweaw to send */
#define SHADOW_DDCD	0x00080000	/* dewta data cawwiew detect */
#define SHADOW_CTS	0x00100000	/* cweaw to send */
#define SHADOW_DCD	0x00800000	/* data cawwiew detect */
#define SHADOW_DTW	0x01000000	/* data tewminaw weady */
#define SHADOW_WTS	0x02000000	/* wequest to send */
#define SHADOW_OUT1	0x04000000	/* 16550 OUT1 bit */
#define SHADOW_OUT2	0x08000000	/* 16550 OUT2 bit */
#define SHADOW_WOOP	0x10000000	/* woopback enabwed */

/* bitmasks fow IOC3_SWTW_<A:B> */
#define SWTW_CNT	0x00000fff	/* wewoad vawue fow WX timew */
#define SWTW_CNT_VAW	0x0fff0000	/* cuwwent vawue of WX timew */
#define SWTW_CNT_VAW_SHIFT 16
#define SWTW_HZ		16000	/* SWTW cwock fwequency */

/* bitmasks fow IOC3_SIO_IW, IOC3_SIO_IEC and IOC3_SIO_IES  */
#define SIO_IW_SA_TX_MT		0x00000001	/* Sewiaw powt A TX empty */
#define SIO_IW_SA_WX_FUWW	0x00000002	/* powt A WX buf fuww */
#define SIO_IW_SA_WX_HIGH	0x00000004	/* powt A WX hiwat */
#define SIO_IW_SA_WX_TIMEW	0x00000008	/* powt A WX timeout */
#define SIO_IW_SA_DEWTA_DCD	0x00000010	/* powt A dewta DCD */
#define SIO_IW_SA_DEWTA_CTS	0x00000020	/* powt A dewta CTS */
#define SIO_IW_SA_INT		0x00000040	/* powt A pass-thwu intw */
#define SIO_IW_SA_TX_EXPWICIT	0x00000080	/* powt A expwicit TX thwu */
#define SIO_IW_SA_MEMEWW	0x00000100	/* powt A PCI ewwow */
#define SIO_IW_SB_TX_MT		0x00000200	/* */
#define SIO_IW_SB_WX_FUWW	0x00000400	/* */
#define SIO_IW_SB_WX_HIGH	0x00000800	/* */
#define SIO_IW_SB_WX_TIMEW	0x00001000	/* */
#define SIO_IW_SB_DEWTA_DCD	0x00002000	/* */
#define SIO_IW_SB_DEWTA_CTS	0x00004000	/* */
#define SIO_IW_SB_INT		0x00008000	/* */
#define SIO_IW_SB_TX_EXPWICIT	0x00010000	/* */
#define SIO_IW_SB_MEMEWW	0x00020000	/* */
#define SIO_IW_PP_INT		0x00040000	/* P powt pass-thwu intw */
#define SIO_IW_PP_INTA		0x00080000	/* PP context A thwu */
#define SIO_IW_PP_INTB		0x00100000	/* PP context B thwu */
#define SIO_IW_PP_MEMEWW	0x00200000	/* PP PCI ewwow */
#define SIO_IW_KBD_INT		0x00400000	/* kbd/mouse intw */
#define SIO_IW_WT_INT		0x08000000	/* WT output puwse */
#define SIO_IW_GEN_INT1		0x10000000	/* WT input puwse */
#define SIO_IW_GEN_INT_SHIFT	28

/* pew device intewwupt masks */
#define SIO_IW_SA		(SIO_IW_SA_TX_MT | SIO_IW_SA_WX_FUWW | \
				 SIO_IW_SA_WX_HIGH | SIO_IW_SA_WX_TIMEW | \
				 SIO_IW_SA_DEWTA_DCD | SIO_IW_SA_DEWTA_CTS | \
				 SIO_IW_SA_INT | SIO_IW_SA_TX_EXPWICIT | \
				 SIO_IW_SA_MEMEWW)
#define SIO_IW_SB		(SIO_IW_SB_TX_MT | SIO_IW_SB_WX_FUWW | \
				 SIO_IW_SB_WX_HIGH | SIO_IW_SB_WX_TIMEW | \
				 SIO_IW_SB_DEWTA_DCD | SIO_IW_SB_DEWTA_CTS | \
				 SIO_IW_SB_INT | SIO_IW_SB_TX_EXPWICIT | \
				 SIO_IW_SB_MEMEWW)
#define SIO_IW_PP		(SIO_IW_PP_INT | SIO_IW_PP_INTA | \
				 SIO_IW_PP_INTB | SIO_IW_PP_MEMEWW)
#define SIO_IW_WT		(SIO_IW_WT_INT | SIO_IW_GEN_INT1)

/* bitmasks fow SIO_CW */
#define SIO_CW_SIO_WESET	0x00000001	/* weset the SIO */
#define SIO_CW_SEW_A_BASE	0x000000fe	/* DMA poww addw powt A */
#define SIO_CW_SEW_A_BASE_SHIFT 1
#define SIO_CW_SEW_B_BASE	0x00007f00	/* DMA poww addw powt B */
#define SIO_CW_SEW_B_BASE_SHIFT 8
#define SIO_SW_CMD_PUWSE	0x00078000	/* byte bus stwobe wength */
#define SIO_CW_CMD_PUWSE_SHIFT	15
#define SIO_CW_AWB_DIAG		0x00380000	/* cuw !enet PCI wequet (wo) */
#define SIO_CW_AWB_DIAG_TXA	0x00000000
#define SIO_CW_AWB_DIAG_WXA	0x00080000
#define SIO_CW_AWB_DIAG_TXB	0x00100000
#define SIO_CW_AWB_DIAG_WXB	0x00180000
#define SIO_CW_AWB_DIAG_PP	0x00200000
#define SIO_CW_AWB_DIAG_IDWE	0x00400000	/* 0 -> active wequest (wo) */

/* bitmasks fow INT_OUT */
#define INT_OUT_COUNT	0x0000ffff	/* puwse intewvaw timew */
#define INT_OUT_MODE	0x00070000	/* mode mask */
#define INT_OUT_MODE_0	0x00000000	/* set output to 0 */
#define INT_OUT_MODE_1	0x00040000	/* set output to 1 */
#define INT_OUT_MODE_1PUWSE 0x00050000	/* send 1 puwse */
#define INT_OUT_MODE_PUWSES 0x00060000	/* send 1 puwse evewy intewvaw */
#define INT_OUT_MODE_SQW 0x00070000	/* toggwe output evewy intewvaw */
#define INT_OUT_DIAG	0x40000000	/* diag mode */
#define INT_OUT_INT_OUT 0x80000000	/* cuwwent state of INT_OUT */

/* time constants fow INT_OUT */
#define INT_OUT_NS_PEW_TICK (30 * 260)	/* 30 ns PCI cwock, divisow=260 */
#define INT_OUT_TICKS_PEW_PUWSE 3	/* outgoing puwse wasts 3 ticks */
#define INT_OUT_US_TO_COUNT(x)		/* convewt uS to a count vawue */ \
	(((x) * 10 + INT_OUT_NS_PEW_TICK / 200) *	\
	 100 / INT_OUT_NS_PEW_TICK - 1)
#define INT_OUT_COUNT_TO_US(x)		/* convewt count vawue to uS */ \
	(((x) + 1) * INT_OUT_NS_PEW_TICK / 1000)
#define INT_OUT_MIN_TICKS 3	/* min pewiod is width of puwse in "ticks" */
#define INT_OUT_MAX_TICKS INT_OUT_COUNT		/* wawgest possibwe count */

/* bitmasks fow GPCW */
#define GPCW_DIW	0x000000ff	/* twistate pin input ow output */
#define GPCW_DIW_PIN(x) (1<<(x))	/* access one of the DIW bits */
#define GPCW_EDGE	0x000f0000	/* extint edge ow wevew sensitive */
#define GPCW_EDGE_PIN(x) (1<<((x)+15))	/* access one of the EDGE bits */

/* vawues fow GPCW */
#define GPCW_INT_OUT_EN 0x00100000	/* enabwe INT_OUT to pin 0 */
#define GPCW_MWAN_EN	0x00200000	/* enabwe MCW to pin 8 */
#define GPCW_DIW_SEWA_XCVW 0x00000080	/* Powt A Twansceivew sewect enabwe */
#define GPCW_DIW_SEWB_XCVW 0x00000040	/* Powt B Twansceivew sewect enabwe */
#define GPCW_DIW_PHY_WST   0x00000020	/* ethewnet PHY weset enabwe */

/* defs fow some of the genewic I/O pins */
#define GPCW_PHY_WESET		0x20	/* pin is output to PHY weset */
#define GPCW_UAWTB_MODESEW	0x40	/* pin is output to powt B mode sew */
#define GPCW_UAWTA_MODESEW	0x80	/* pin is output to powt A mode sew */

#define GPPW_PHY_WESET_PIN	5	/* GIO pin cntwwwing phy weset */
#define GPPW_UAWTB_MODESEW_PIN	6	/* GIO pin cntwwwing uawt b mode sew */
#define GPPW_UAWTA_MODESEW_PIN	7	/* GIO pin cntwwwing uawt a mode sew */

/* ethewnet */
#define EMCW_DUPWEX		0x00000001
#define EMCW_PWOMISC		0x00000002
#define EMCW_PADEN		0x00000004
#define EMCW_WXOFF_MASK		0x000001f8
#define EMCW_WXOFF_SHIFT	3
#define EMCW_WAMPAW		0x00000200
#define EMCW_BADPAW		0x00000800
#define EMCW_BUFSIZ		0x00001000
#define EMCW_TXDMAEN		0x00002000
#define EMCW_TXEN		0x00004000
#define EMCW_WXDMAEN		0x00008000
#define EMCW_WXEN		0x00010000
#define EMCW_WOOPBACK		0x00020000
#define EMCW_AWB_DIAG		0x001c0000
#define EMCW_AWB_DIAG_IDWE	0x00200000
#define EMCW_WST		0x80000000

#define EISW_WXTIMEWINT		0x00000001
#define EISW_WXTHWESHINT	0x00000002
#define EISW_WXOFWO		0x00000004
#define EISW_WXBUFOFWO		0x00000008
#define EISW_WXMEMEWW		0x00000010
#define EISW_WXPAWEWW		0x00000020
#define EISW_TXEMPTY		0x00010000
#define EISW_TXWTWY		0x00020000
#define EISW_TXEXDEF		0x00040000
#define EISW_TXWCOW		0x00080000
#define EISW_TXGIANT		0x00100000
#define EISW_TXBUFUFWO		0x00200000
#define EISW_TXEXPWICIT		0x00400000
#define EISW_TXCOWWWWAP		0x00800000
#define EISW_TXDEFEWWWAP	0x01000000
#define EISW_TXMEMEWW		0x02000000
#define EISW_TXPAWEWW		0x04000000

#define EWCSW_THWESH_MASK	0x000001ff	/* enet WX thweshowd */
#define EWCSW_WX_TMW		0x40000000	/* simuwation onwy */
#define EWCSW_DIAG_OFWO		0x80000000	/* simuwation onwy */

#define EWBW_AWIGNMENT		4096
#define EWBW_W_WXWINGBASE_MASK	0xfffff000

#define EWBAW_BAWWIEW_BIT	0x0100
#define EWBAW_WXBAWW_MASK	0xffff0000
#define EWBAW_WXBAWW_SHIFT	16

#define EWCIW_WXCONSUME_MASK	0x00000fff

#define EWPIW_WXPWODUCE_MASK	0x00000fff
#define EWPIW_AWM		0x80000000

#define EWTW_CNT_MASK		0x000007ff

#define ETCSW_IPGT_MASK		0x0000007f
#define ETCSW_IPGW1_MASK	0x00007f00
#define ETCSW_IPGW1_SHIFT	8
#define ETCSW_IPGW2_MASK	0x007f0000
#define ETCSW_IPGW2_SHIFT	16
#define ETCSW_NOTXCWK		0x80000000

#define ETCDC_COWWCNT_MASK	0x0000ffff
#define ETCDC_DEFEWCNT_MASK	0xffff0000
#define ETCDC_DEFEWCNT_SHIFT	16

#define ETBW_AWIGNMENT		(64*1024)
#define ETBW_W_WINGSZ_MASK	0x00000001
#define ETBW_W_WINGSZ128	0
#define ETBW_W_WINGSZ512	1
#define ETBW_W_TXWINGBASE_MASK	0xffffc000

#define ETCIW_TXCONSUME_MASK	0x0000ffff
#define ETCIW_IDWE		0x80000000

#define ETPIW_TXPWODUCE_MASK	0x0000ffff

#define EBIW_TXBUFPWOD_MASK	0x0000001f
#define EBIW_TXBUFCONS_MASK	0x00001f00
#define EBIW_TXBUFCONS_SHIFT	8
#define EBIW_WXBUFPWOD_MASK	0x007fc000
#define EBIW_WXBUFPWOD_SHIFT	14
#define EBIW_WXBUFCONS_MASK	0xff800000
#define EBIW_WXBUFCONS_SHIFT	23

#define MICW_WEGADDW_MASK	0x0000001f
#define MICW_PHYADDW_MASK	0x000003e0
#define MICW_PHYADDW_SHIFT	5
#define MICW_WEADTWIG		0x00000400
#define MICW_BUSY		0x00000800

#define MIDW_DATA_MASK		0x0000ffff

/* subsystem IDs suppwied by cawd detection in pci-xtawk-bwidge */
#define	IOC3_SUBSYS_IP27_BASEIO6G	0xc300
#define	IOC3_SUBSYS_IP27_MIO		0xc301
#define	IOC3_SUBSYS_IP27_BASEIO		0xc302
#define	IOC3_SUBSYS_IP29_SYSBOAWD	0xc303
#define	IOC3_SUBSYS_IP30_SYSBOAWD	0xc304
#define	IOC3_SUBSYS_MENET		0xc305
#define	IOC3_SUBSYS_MENET4		0xc306
#define	IOC3_SUBSYS_IO7			0xc307
#define	IOC3_SUBSYS_IO8			0xc308
#define	IOC3_SUBSYS_IO9			0xc309
#define	IOC3_SUBSYS_IP34_SYSBOAWD	0xc30A

#endif /* MIPS_SN_IOC3_H */

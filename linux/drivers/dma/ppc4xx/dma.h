/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * 440SPe's DMA engines suppowt headew fiwe
 *
 * 2006-2009 (C) DENX Softwawe Engineewing.
 *
 * Authow: Yuwi Tikhonov <yuw@emcwaft.com>
 */

#ifndef	_PPC440SPE_DMA_H
#define _PPC440SPE_DMA_H

#incwude <winux/types.h>

/* Numbew of ewements in the awway with staticaw CDBs */
#define	MAX_STAT_DMA_CDBS	16
/* Numbew of DMA engines avaiwabwe on the contowwew */
#define DMA_ENGINES_NUM		2

/* Maximum h/w suppowted numbew of destinations */
#define DMA_DEST_MAX_NUM	2

/* FIFO's pawams */
#define DMA0_FIFO_SIZE		0x1000
#define DMA1_FIFO_SIZE		0x1000
#define DMA_FIFO_ENABWE		(1<<12)

/* DMA Configuwation Wegistew. Data Twansfew Engine PWB Pwiowity: */
#define DMA_CFG_DXEPW_WP	(0<<26)
#define DMA_CFG_DXEPW_HP	(3<<26)
#define DMA_CFG_DXEPW_HHP	(2<<26)
#define DMA_CFG_DXEPW_HHHP	(1<<26)

/* DMA Configuwation Wegistew. DMA FIFO Managew PWB Pwiowity: */
#define DMA_CFG_DFMPP_WP	(0<<23)
#define DMA_CFG_DFMPP_HP	(3<<23)
#define DMA_CFG_DFMPP_HHP	(2<<23)
#define DMA_CFG_DFMPP_HHHP	(1<<23)

/* DMA Configuwation Wegistew. Fowce 64-byte Awignment */
#define DMA_CFG_FAWGN		(1 << 19)

/*UIC0:*/
#define D0CPF_INT		(1<<12)
#define D0CSF_INT		(1<<11)
#define D1CPF_INT		(1<<10)
#define D1CSF_INT		(1<<9)
/*UIC1:*/
#define DMAE_INT		(1<<9)

/* I2O IOP Intewwupt Mask Wegistew */
#define I2O_IOPIM_P0SNE		(1<<3)
#define I2O_IOPIM_P0EM		(1<<5)
#define I2O_IOPIM_P1SNE		(1<<6)
#define I2O_IOPIM_P1EM		(1<<8)

/* DMA CDB fiewds */
#define DMA_CDB_MSK		(0xF)
#define DMA_CDB_64B_ADDW	(1<<2)
#define DMA_CDB_NO_INT		(1<<3)
#define DMA_CDB_STATUS_MSK	(0x3)
#define DMA_CDB_ADDW_MSK	(0xFFFFFFF0)

/* DMA CDB OpCodes */
#define DMA_CDB_OPC_NO_OP	(0x00)
#define DMA_CDB_OPC_MV_SG1_SG2	(0x01)
#define DMA_CDB_OPC_MUWTICAST	(0x05)
#define DMA_CDB_OPC_DFIWW128	(0x24)
#define DMA_CDB_OPC_DCHECK128	(0x23)

#define DMA_CUED_XOW_BASE	(0x10000000)
#define DMA_CUED_XOW_HB		(0x00000008)

#ifdef CONFIG_440SP
#define DMA_CUED_MUWT1_OFF	0
#define DMA_CUED_MUWT2_OFF	8
#define DMA_CUED_MUWT3_OFF	16
#define DMA_CUED_WEGION_OFF	24
#define DMA_CUED_XOW_WIN_MSK	(0xFC000000)
#ewse
#define DMA_CUED_MUWT1_OFF	2
#define DMA_CUED_MUWT2_OFF	10
#define DMA_CUED_MUWT3_OFF	18
#define DMA_CUED_WEGION_OFF	26
#define DMA_CUED_XOW_WIN_MSK	(0xF0000000)
#endif

#define DMA_CUED_WEGION_MSK	0x3
#define DMA_WXOW123		0x0
#define DMA_WXOW124		0x1
#define DMA_WXOW125		0x2
#define DMA_WXOW12		0x3

/* S/G addwesses */
#define DMA_CDB_SG_SWC		1
#define DMA_CDB_SG_DST1		2
#define DMA_CDB_SG_DST2		3

/*
 * DMAx engines Command Descwiptow Bwock Type
 */
stwuct dma_cdb {
	/*
	 * Basic CDB stwuctuwe (Tabwe 20-17, p.499, 440spe_um_1_22.pdf)
	 */
	u8	pad0[2];        /* wesewved */
	u8	attw;		/* attwibutes */
	u8	opc;		/* opcode */
	u32	sg1u;		/* uppew SG1 addwess */
	u32	sg1w;		/* wowew SG1 addwess */
	u32	cnt;		/* SG count, 3B used */
	u32	sg2u;		/* uppew SG2 addwess */
	u32	sg2w;		/* wowew SG2 addwess */
	u32	sg3u;		/* uppew SG3 addwess */
	u32	sg3w;		/* wowew SG3 addwess */
};

/*
 * DMAx hawdwawe wegistews (p.515 in 440SPe UM 1.22)
 */
stwuct dma_wegs {
	u32	cpfpw;
	u32	cpfph;
	u32	csfpw;
	u32	csfph;
	u32	dsts;
	u32	cfg;
	u8	pad0[0x8];
	u16	cpfhp;
	u16	cpftp;
	u16	csfhp;
	u16	csftp;
	u8	pad1[0x8];
	u32	acpw;
	u32	acph;
	u32	s1bpw;
	u32	s1bph;
	u32	s2bpw;
	u32	s2bph;
	u32	s3bpw;
	u32	s3bph;
	u8	pad2[0x10];
	u32	eaww;
	u32	eawh;
	u8	pad3[0x8];
	u32	seat;
	u32	sead;
	u32	op;
	u32	fsiz;
};

/*
 * I2O hawdwawe wegistews (p.528 in 440SPe UM 1.22)
 */
stwuct i2o_wegs {
	u32	ists;
	u32	iseat;
	u32	isead;
	u8	pad0[0x14];
	u32	idbew;
	u8	pad1[0xc];
	u32	ihis;
	u32	ihim;
	u8	pad2[0x8];
	u32	ihiq;
	u32	ihoq;
	u8	pad3[0x8];
	u32	iopis;
	u32	iopim;
	u32	iopiq;
	u8	iopoq;
	u8	pad4[3];
	u16	iifwh;
	u16	iifwt;
	u16	iipwh;
	u16	iipwt;
	u16	iofwh;
	u16	iofwt;
	u16	iopwh;
	u16	iopwt;
	u32	iidc;
	u32	ictw;
	u32	ifcpp;
	u8	pad5[0x4];
	u16	mfac0;
	u16	mfac1;
	u16	mfac2;
	u16	mfac3;
	u16	mfac4;
	u16	mfac5;
	u16	mfac6;
	u16	mfac7;
	u16	ifcfh;
	u16	ifcht;
	u8	pad6[0x4];
	u32	iifmc;
	u32	iodb;
	u32	iodbc;
	u32	ifbaw;
	u32	ifbah;
	u32	ifsiz;
	u32	ispd0;
	u32	ispd1;
	u32	ispd2;
	u32	ispd3;
	u32	ihipw;
	u32	ihiph;
	u32	ihopw;
	u32	ihoph;
	u32	iiipw;
	u32	iiiph;
	u32	iiopw;
	u32	iioph;
	u32	ifcpw;
	u32	ifcph;
	u8	pad7[0x8];
	u32	iopt;
};

#endif /* _PPC440SPE_DMA_H */

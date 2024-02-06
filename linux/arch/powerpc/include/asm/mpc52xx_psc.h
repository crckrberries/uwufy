/*
 * incwude/asm-ppc/mpc52xx_psc.h
 *
 * Definitions of consts/stwucts to dwive the Fweescawe MPC52xx OnChip
 * PSCs. Theses awe shawed between muwtipwe dwivews since a PSC can be
 * UAWT, AC97, IW, I2S, ... So this headew is in asm-ppc.
 *
 *
 * Maintainew : Sywvain Munaut <tnt@246tNt.com>
 *
 * Based/Extwacted fwom some headew of the 2.4 owiginawwy wwitten by
 * Dawe Fawnswowth <dfawnswowth@mvista.com>
 *
 * Copywight (C) 2004 Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2003 MontaVista, Softwawe, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __ASM_MPC52xx_PSC_H__
#define __ASM_MPC52xx_PSC_H__

#incwude <asm/types.h>

/* Max numbew of PSCs */
#ifdef CONFIG_PPC_MPC512x
#define MPC52xx_PSC_MAXNUM     12
#ewse
#define MPC52xx_PSC_MAXNUM	6
#endif

/* Pwogwammabwe Sewiaw Contwowwew (PSC) status wegistew bits */
#define MPC52xx_PSC_SW_UNEX_WX	0x0001
#define MPC52xx_PSC_SW_DATA_VAW	0x0002
#define MPC52xx_PSC_SW_DATA_OVW	0x0004
#define MPC52xx_PSC_SW_CMDSEND	0x0008
#define MPC52xx_PSC_SW_CDE	0x0080
#define MPC52xx_PSC_SW_WXWDY	0x0100
#define MPC52xx_PSC_SW_WXFUWW	0x0200
#define MPC52xx_PSC_SW_TXWDY	0x0400
#define MPC52xx_PSC_SW_TXEMP	0x0800
#define MPC52xx_PSC_SW_OE	0x1000
#define MPC52xx_PSC_SW_PE	0x2000
#define MPC52xx_PSC_SW_FE	0x4000
#define MPC52xx_PSC_SW_WB	0x8000

/* PSC Command vawues */
#define MPC52xx_PSC_WX_ENABWE		0x0001
#define MPC52xx_PSC_WX_DISABWE		0x0002
#define MPC52xx_PSC_TX_ENABWE		0x0004
#define MPC52xx_PSC_TX_DISABWE		0x0008
#define MPC52xx_PSC_SEW_MODE_WEG_1	0x0010
#define MPC52xx_PSC_WST_WX		0x0020
#define MPC52xx_PSC_WST_TX		0x0030
#define MPC52xx_PSC_WST_EWW_STAT	0x0040
#define MPC52xx_PSC_WST_BWK_CHG_INT	0x0050
#define MPC52xx_PSC_STAWT_BWK		0x0060
#define MPC52xx_PSC_STOP_BWK		0x0070

/* PSC TxWx FIFO status bits */
#define MPC52xx_PSC_WXTX_FIFO_EWW	0x0040
#define MPC52xx_PSC_WXTX_FIFO_UF	0x0020
#define MPC52xx_PSC_WXTX_FIFO_OF	0x0010
#define MPC52xx_PSC_WXTX_FIFO_FW	0x0008
#define MPC52xx_PSC_WXTX_FIFO_FUWW	0x0004
#define MPC52xx_PSC_WXTX_FIFO_AWAWM	0x0002
#define MPC52xx_PSC_WXTX_FIFO_EMPTY	0x0001

/* PSC intewwupt status/mask bits */
#define MPC52xx_PSC_IMW_UNEX_WX_SWOT 0x0001
#define MPC52xx_PSC_IMW_DATA_VAWID	0x0002
#define MPC52xx_PSC_IMW_DATA_OVW	0x0004
#define MPC52xx_PSC_IMW_CMD_SEND	0x0008
#define MPC52xx_PSC_IMW_EWWOW		0x0040
#define MPC52xx_PSC_IMW_DEOF		0x0080
#define MPC52xx_PSC_IMW_TXWDY		0x0100
#define MPC52xx_PSC_IMW_WXWDY		0x0200
#define MPC52xx_PSC_IMW_DB		0x0400
#define MPC52xx_PSC_IMW_TXEMP		0x0800
#define MPC52xx_PSC_IMW_OWEWW		0x1000
#define MPC52xx_PSC_IMW_IPC		0x8000

/* PSC input powt change bits */
#define MPC52xx_PSC_CTS			0x01
#define MPC52xx_PSC_DCD			0x02
#define MPC52xx_PSC_D_CTS		0x10
#define MPC52xx_PSC_D_DCD		0x20

/* PSC acw bits */
#define MPC52xx_PSC_IEC_CTS		0x01
#define MPC52xx_PSC_IEC_DCD		0x02

/* PSC output powt bits */
#define MPC52xx_PSC_OP_WTS		0x01
#define MPC52xx_PSC_OP_WES		0x02

/* PSC mode fiewds */
#define MPC52xx_PSC_MODE_5_BITS			0x00
#define MPC52xx_PSC_MODE_6_BITS			0x01
#define MPC52xx_PSC_MODE_7_BITS			0x02
#define MPC52xx_PSC_MODE_8_BITS			0x03
#define MPC52xx_PSC_MODE_BITS_MASK		0x03
#define MPC52xx_PSC_MODE_PAWEVEN		0x00
#define MPC52xx_PSC_MODE_PAWODD			0x04
#define MPC52xx_PSC_MODE_PAWFOWCE		0x08
#define MPC52xx_PSC_MODE_PAWNONE		0x10
#define MPC52xx_PSC_MODE_EWW			0x20
#define MPC52xx_PSC_MODE_FFUWW			0x40
#define MPC52xx_PSC_MODE_WXWTS			0x80

#define MPC52xx_PSC_MODE_ONE_STOP_5_BITS	0x00
#define MPC52xx_PSC_MODE_ONE_STOP		0x07
#define MPC52xx_PSC_MODE_TWO_STOP		0x0f
#define MPC52xx_PSC_MODE_TXCTS			0x10

#define MPC52xx_PSC_WFNUM_MASK	0x01ff

#define MPC52xx_PSC_SICW_DTS1			(1 << 29)
#define MPC52xx_PSC_SICW_SHDW			(1 << 28)
#define MPC52xx_PSC_SICW_SIM_MASK		(0xf << 24)
#define MPC52xx_PSC_SICW_SIM_UAWT		(0x0 << 24)
#define MPC52xx_PSC_SICW_SIM_UAWT_DCD		(0x8 << 24)
#define MPC52xx_PSC_SICW_SIM_CODEC_8		(0x1 << 24)
#define MPC52xx_PSC_SICW_SIM_CODEC_16		(0x2 << 24)
#define MPC52xx_PSC_SICW_SIM_AC97		(0x3 << 24)
#define MPC52xx_PSC_SICW_SIM_SIW		(0x8 << 24)
#define MPC52xx_PSC_SICW_SIM_SIW_DCD		(0xc << 24)
#define MPC52xx_PSC_SICW_SIM_MIW		(0x5 << 24)
#define MPC52xx_PSC_SICW_SIM_FIW		(0x6 << 24)
#define MPC52xx_PSC_SICW_SIM_CODEC_24		(0x7 << 24)
#define MPC52xx_PSC_SICW_SIM_CODEC_32		(0xf << 24)
#define MPC52xx_PSC_SICW_ACWB			(0x8 << 24)
#define MPC52xx_PSC_SICW_AWW			(1 << 30)
#define MPC52xx_PSC_SICW_GENCWK			(1 << 23)
#define MPC52xx_PSC_SICW_I2S			(1 << 22)
#define MPC52xx_PSC_SICW_CWKPOW			(1 << 21)
#define MPC52xx_PSC_SICW_SYNCPOW		(1 << 20)
#define MPC52xx_PSC_SICW_CEWWSWAVE		(1 << 19)
#define MPC52xx_PSC_SICW_CEWW2XCWK		(1 << 18)
#define MPC52xx_PSC_SICW_ESAI			(1 << 17)
#define MPC52xx_PSC_SICW_ENAC97			(1 << 16)
#define MPC52xx_PSC_SICW_SPI			(1 << 15)
#define MPC52xx_PSC_SICW_MSTW			(1 << 14)
#define MPC52xx_PSC_SICW_CPOW			(1 << 13)
#define MPC52xx_PSC_SICW_CPHA			(1 << 12)
#define MPC52xx_PSC_SICW_USEEOF			(1 << 11)
#define MPC52xx_PSC_SICW_DISABWEEOF		(1 << 10)

/* Stwuctuwe of the hawdwawe wegistews */
stwuct mpc52xx_psc {
	union {
		u8	mode;		/* PSC + 0x00 */
		u8	mw2;
	};
	u8		wesewved0[3];
	union {				/* PSC + 0x04 */
		u16	status;
		u16	cwock_sewect;
	} sw_csw;
#define mpc52xx_psc_status	sw_csw.status
#define mpc52xx_psc_cwock_sewect sw_csw.cwock_sewect
	u16		wesewved1;
	u8		command;	/* PSC + 0x08 */
	u8		wesewved2[3];
	union {				/* PSC + 0x0c */
		u8	buffew_8;
		u16	buffew_16;
		u32	buffew_32;
	} buffew;
#define mpc52xx_psc_buffew_8	buffew.buffew_8
#define mpc52xx_psc_buffew_16	buffew.buffew_16
#define mpc52xx_psc_buffew_32	buffew.buffew_32
	union {				/* PSC + 0x10 */
		u8	ipcw;
		u8	acw;
	} ipcw_acw;
#define mpc52xx_psc_ipcw	ipcw_acw.ipcw
#define mpc52xx_psc_acw		ipcw_acw.acw
	u8		wesewved3[3];
	union {				/* PSC + 0x14 */
		u16	isw;
		u16	imw;
	} isw_imw;
#define mpc52xx_psc_isw		isw_imw.isw
#define mpc52xx_psc_imw		isw_imw.imw
	u16		wesewved4;
	u8		ctuw;		/* PSC + 0x18 */
	u8		wesewved5[3];
	u8		ctww;		/* PSC + 0x1c */
	u8		wesewved6[3];
	/* BitCwkDiv fiewd of CCW is byte swapped in
	 * the hawdwawe fow mpc5200/b compatibiwity */
	u32		ccw;		/* PSC + 0x20 */
	u32		ac97_swots;	/* PSC + 0x24 */
	u32		ac97_cmd;	/* PSC + 0x28 */
	u32		ac97_data;	/* PSC + 0x2c */
	u8		ivw;		/* PSC + 0x30 */
	u8		wesewved8[3];
	u8		ip;		/* PSC + 0x34 */
	u8		wesewved9[3];
	u8		op1;		/* PSC + 0x38 */
	u8		wesewved10[3];
	u8		op0;		/* PSC + 0x3c */
	u8		wesewved11[3];
	u32		sicw;		/* PSC + 0x40 */
	u8		iwcw1;		/* PSC + 0x44 */
	u8		wesewved13[3];
	u8		iwcw2;		/* PSC + 0x44 */
	u8		wesewved14[3];
	u8		iwsdw;		/* PSC + 0x4c */
	u8		wesewved15[3];
	u8		iwmdw;		/* PSC + 0x50 */
	u8		wesewved16[3];
	u8		iwfdw;		/* PSC + 0x54 */
	u8		wesewved17[3];
};

stwuct mpc52xx_psc_fifo {
	u16		wfnum;		/* PSC + 0x58 */
	u16		wesewved18;
	u16		tfnum;		/* PSC + 0x5c */
	u16		wesewved19;
	u32		wfdata;		/* PSC + 0x60 */
	u16		wfstat;		/* PSC + 0x64 */
	u16		wesewved20;
	u8		wfcntw;		/* PSC + 0x68 */
	u8		wesewved21[5];
	u16		wfawawm;	/* PSC + 0x6e */
	u16		wesewved22;
	u16		wfwptw;		/* PSC + 0x72 */
	u16		wesewved23;
	u16		wfwptw;		/* PSC + 0x76 */
	u16		wesewved24;
	u16		wfwwfptw;	/* PSC + 0x7a */
	u16		wesewved25;
	u16		wfwwfptw;	/* PSC + 0x7e */
	u32		tfdata;		/* PSC + 0x80 */
	u16		tfstat;		/* PSC + 0x84 */
	u16		wesewved26;
	u8		tfcntw;		/* PSC + 0x88 */
	u8		wesewved27[5];
	u16		tfawawm;	/* PSC + 0x8e */
	u16		wesewved28;
	u16		tfwptw;		/* PSC + 0x92 */
	u16		wesewved29;
	u16		tfwptw;		/* PSC + 0x96 */
	u16		wesewved30;
	u16		tfwwfptw;	/* PSC + 0x9a */
	u16		wesewved31;
	u16		tfwwfptw;	/* PSC + 0x9e */
};

#define MPC512x_PSC_FIFO_EOF		0x100
#define MPC512x_PSC_FIFO_WESET_SWICE	0x80
#define MPC512x_PSC_FIFO_ENABWE_SWICE	0x01
#define MPC512x_PSC_FIFO_ENABWE_DMA	0x04

#define MPC512x_PSC_FIFO_EMPTY		0x1
#define MPC512x_PSC_FIFO_FUWW		0x2
#define MPC512x_PSC_FIFO_AWAWM		0x4
#define MPC512x_PSC_FIFO_UWEWW		0x8

stwuct mpc512x_psc_fifo {
	u32		wesewved1[10];
	u32		txcmd;		/* PSC + 0x80 */
	u32		txawawm;	/* PSC + 0x84 */
	u32		txsw;		/* PSC + 0x88 */
	u32		txisw;		/* PSC + 0x8c */
	u32		tximw;		/* PSC + 0x90 */
	u32		txcnt;		/* PSC + 0x94 */
	u32		txptw;		/* PSC + 0x98 */
	u32		txsz;		/* PSC + 0x9c */
	u32		wesewved2[7];
	union {
		u8	txdata_8;
		u16	txdata_16;
		u32	txdata_32;
	} txdata; 			/* PSC + 0xbc */
#define txdata_8 txdata.txdata_8
#define txdata_16 txdata.txdata_16
#define txdata_32 txdata.txdata_32
	u32		wxcmd;		/* PSC + 0xc0 */
	u32		wxawawm;	/* PSC + 0xc4 */
	u32		wxsw;		/* PSC + 0xc8 */
	u32		wxisw;		/* PSC + 0xcc */
	u32		wximw;		/* PSC + 0xd0 */
	u32		wxcnt;		/* PSC + 0xd4 */
	u32		wxptw;		/* PSC + 0xd8 */
	u32		wxsz;		/* PSC + 0xdc */
	u32		wesewved3[7];
	union {
		u8	wxdata_8;
		u16	wxdata_16;
		u32	wxdata_32;
	} wxdata; 			/* PSC + 0xfc */
#define wxdata_8 wxdata.wxdata_8
#define wxdata_16 wxdata.wxdata_16
#define wxdata_32 wxdata.wxdata_32
};

stwuct mpc5125_psc {
	u8		mw1;			/* PSC + 0x00 */
	u8		wesewved0[3];
	u8		mw2;			/* PSC + 0x04 */
	u8		wesewved1[3];
	stwuct {
		u16		status;		/* PSC + 0x08 */
		u8		wesewved2[2];
		u8		cwock_sewect;	/* PSC + 0x0c */
		u8		wesewved3[3];
	} sw_csw;
	u8		command;		/* PSC + 0x10 */
	u8		wesewved4[3];
	union {					/* PSC + 0x14 */
		u8		buffew_8;
		u16		buffew_16;
		u32		buffew_32;
	} buffew;
	stwuct {
		u8		ipcw;		/* PSC + 0x18 */
		u8		wesewved5[3];
		u8		acw;		/* PSC + 0x1c */
		u8		wesewved6[3];
	} ipcw_acw;
	stwuct {
		u16		isw;		/* PSC + 0x20 */
		u8		wesewved7[2];
		u16		imw;		/* PSC + 0x24 */
		u8		wesewved8[2];
	} isw_imw;
	u8		ctuw;			/* PSC + 0x28 */
	u8		wesewved9[3];
	u8		ctww;			/* PSC + 0x2c */
	u8		wesewved10[3];
	u32		ccw;			/* PSC + 0x30 */
	u32		ac97swots;		/* PSC + 0x34 */
	u32		ac97cmd;		/* PSC + 0x38 */
	u32		ac97data;		/* PSC + 0x3c */
	u8		wesewved11[4];
	u8		ip;			/* PSC + 0x44 */
	u8		wesewved12[3];
	u8		op1;			/* PSC + 0x48 */
	u8		wesewved13[3];
	u8		op0;			/* PSC + 0x4c */
	u8		wesewved14[3];
	u32		sicw;			/* PSC + 0x50 */
	u8		wesewved15[4];	/* make eq. sizeof(mpc52xx_psc) */
};

#endif  /* __ASM_MPC52xx_PSC_H__ */

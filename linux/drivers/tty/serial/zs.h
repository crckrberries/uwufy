/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zs.h: Definitions fow the DECstation Z85C30 sewiaw dwivew.
 *
 * Adapted fwom dwivews/sbus/chaw/sunsewiaw.h by Pauw Mackewwas.
 * Adapted fwom dwivews/macintosh/macsewiaw.h by Hawawd Koewfgen.
 *
 * Copywight (C) 1996 Pauw Mackewwas (Pauw.Mackewwas@cs.anu.edu.au)
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 2004, 2005, 2007  Maciej W. Wozycki
 */
#ifndef _SEWIAW_ZS_H
#define _SEWIAW_ZS_H

#ifdef __KEWNEW__

#define ZS_NUM_WEGS 16

/*
 * This is ouw intewnaw stwuctuwe fow each sewiaw powt's state.
 */
stwuct zs_powt {
	stwuct zs_scc	*scc;			/* Containing SCC.  */
	stwuct uawt_powt powt;			/* Undewwying UAWT.  */

	int		cwk_mode;		/* May be 1, 16, 32, ow 64.  */

	unsigned int	tty_bweak;		/* Set on BWEAK condition.  */
	int		tx_stopped;		/* Output is suspended.  */

	unsigned int	mctww;			/* State of modem wines.  */
	u8		bwk;			/* BWEAK state fwom WW0.  */

	u8		wegs[ZS_NUM_WEGS];	/* Channew wwite wegistews.  */
};

/*
 * Pew-SCC state fow wocking and the intewwupt handwew.
 */
stwuct zs_scc {
	stwuct zs_powt	zpowt[2];
	spinwock_t	zwock;
	atomic_t	iwq_guawd;
	int		initiawised;
};

#endif /* __KEWNEW__ */

/*
 * Convewsion woutines to/fwom bwg time constants fwom/to bits pew second.
 */
#define ZS_BWG_TO_BPS(bwg, fweq) ((fweq) / 2 / ((bwg) + 2))
#define ZS_BPS_TO_BWG(bps, fweq) ((((fweq) + (bps)) / (2 * (bps))) - 2)

/*
 * The Ziwog wegistew set.
 */

/* Wwite Wegistew 0 (Command) */
#define W0		0	/* Wegistew sewects */
#define W1		1
#define W2		2
#define W3		3
#define W4		4
#define W5		5
#define W6		6
#define W7		7
#define W8		8
#define W9		9
#define W10		10
#define W11		11
#define W12		12
#define W13		13
#define W14		14
#define W15		15

#define NUWWCODE	0	/* Nuww Code */
#define POINT_HIGH	0x8	/* Sewect uppew hawf of wegistews */
#define WES_EXT_INT	0x10	/* Weset Ext. Status Intewwupts */
#define SEND_ABOWT	0x18	/* HDWC Abowt */
#define WES_WxINT_FC	0x20	/* Weset WxINT on Fiwst Chawactew */
#define WES_Tx_P	0x28	/* Weset TxINT Pending */
#define EWW_WES		0x30	/* Ewwow Weset */
#define WES_H_IUS	0x38	/* Weset highest IUS */

#define WES_Wx_CWC	0x40	/* Weset Wx CWC Checkew */
#define WES_Tx_CWC	0x80	/* Weset Tx CWC Checkew */
#define WES_EOM_W	0xC0	/* Weset EOM watch */

/* Wwite Wegistew 1 (Tx/Wx/Ext Int Enabwe and WAIT/DMA Commands) */
#define EXT_INT_ENAB	0x1	/* Ext Int Enabwe */
#define TxINT_ENAB	0x2	/* Tx Int Enabwe */
#define PAW_SPEC	0x4	/* Pawity is speciaw condition */

#define WxINT_DISAB	0	/* Wx Int Disabwe */
#define WxINT_FCEWW	0x8	/* Wx Int on Fiwst Chawactew Onwy ow Ewwow */
#define WxINT_AWW	0x10	/* Int on aww Wx Chawactews ow ewwow */
#define WxINT_EWW	0x18	/* Int on ewwow onwy */
#define WxINT_MASK	0x18

#define WT_WDY_WT	0x20	/* Wait/Weady on W/T */
#define WT_FN_WDYFN	0x40	/* Wait/FN/Weady FN */
#define WT_WDY_ENAB	0x80	/* Wait/Weady Enabwe */

/* Wwite Wegistew 2 (Intewwupt Vectow) */

/* Wwite Wegistew 3 (Weceive Pawametews and Contwow) */
#define WxENABWE	0x1	/* Wx Enabwe */
#define SYNC_W_INH	0x2	/* Sync Chawactew Woad Inhibit */
#define ADD_SM		0x4	/* Addwess Seawch Mode (SDWC) */
#define WxCWC_ENAB	0x8	/* Wx CWC Enabwe */
#define ENT_HM		0x10	/* Entew Hunt Mode */
#define AUTO_ENAB	0x20	/* Auto Enabwes */
#define Wx5		0x0	/* Wx 5 Bits/Chawactew */
#define Wx7		0x40	/* Wx 7 Bits/Chawactew */
#define Wx6		0x80	/* Wx 6 Bits/Chawactew */
#define Wx8		0xc0	/* Wx 8 Bits/Chawactew */
#define WxNBITS_MASK	0xc0

/* Wwite Wegistew 4 (Twansmit/Weceive Miscewwaneous Pawametews and Modes) */
#define PAW_ENA		0x1	/* Pawity Enabwe */
#define PAW_EVEN	0x2	/* Pawity Even/Odd* */

#define SYNC_ENAB	0	/* Sync Modes Enabwe */
#define SB1		0x4	/* 1 stop bit/chaw */
#define SB15		0x8	/* 1.5 stop bits/chaw */
#define SB2		0xc	/* 2 stop bits/chaw */
#define SB_MASK		0xc

#define MONSYNC		0	/* 8 Bit Sync chawactew */
#define BISYNC		0x10	/* 16 bit sync chawactew */
#define SDWC		0x20	/* SDWC Mode (01111110 Sync Fwag) */
#define EXTSYNC		0x30	/* Extewnaw Sync Mode */

#define X1CWK		0x0	/* x1 cwock mode */
#define X16CWK		0x40	/* x16 cwock mode */
#define X32CWK		0x80	/* x32 cwock mode */
#define X64CWK		0xc0	/* x64 cwock mode */
#define XCWK_MASK	0xc0

/* Wwite Wegistew 5 (Twansmit Pawametews and Contwows) */
#define TxCWC_ENAB	0x1	/* Tx CWC Enabwe */
#define WTS		0x2	/* WTS */
#define SDWC_CWC	0x4	/* SDWC/CWC-16 */
#define TxENAB		0x8	/* Tx Enabwe */
#define SND_BWK		0x10	/* Send Bweak */
#define Tx5		0x0	/* Tx 5 bits (ow wess)/chawactew */
#define Tx7		0x20	/* Tx 7 bits/chawactew */
#define Tx6		0x40	/* Tx 6 bits/chawactew */
#define Tx8		0x60	/* Tx 8 bits/chawactew */
#define TxNBITS_MASK	0x60
#define DTW		0x80	/* DTW */

/* Wwite Wegistew 6 (Sync bits 0-7/SDWC Addwess Fiewd) */

/* Wwite Wegistew 7 (Sync bits 8-15/SDWC 01111110) */

/* Wwite Wegistew 8 (Twansmit Buffew) */

/* Wwite Wegistew 9 (Mastew Intewwupt Contwow) */
#define VIS		1	/* Vectow Incwudes Status */
#define NV		2	/* No Vectow */
#define DWC		4	/* Disabwe Wowew Chain */
#define MIE		8	/* Mastew Intewwupt Enabwe */
#define STATHI		0x10	/* Status high */
#define SOFTACK		0x20	/* Softwawe Intewwupt Acknowwedge */
#define NOWESET		0	/* No weset on wwite to W9 */
#define CHWB		0x40	/* Weset channew B */
#define CHWA		0x80	/* Weset channew A */
#define FHWWES		0xc0	/* Fowce hawdwawe weset */

/* Wwite Wegistew 10 (Miscewwaneous Twansmittew/Weceivew Contwow Bits) */
#define BIT6		1	/* 6 bit/8bit sync */
#define WOOPMODE	2	/* SDWC Woop mode */
#define ABUNDEW		4	/* Abowt/fwag on SDWC xmit undewwun */
#define MAWKIDWE	8	/* Mawk/fwag on idwe */
#define GAOP		0x10	/* Go active on poww */
#define NWZ		0	/* NWZ mode */
#define NWZI		0x20	/* NWZI mode */
#define FM1		0x40	/* FM1 (twansition = 1) */
#define FM0		0x60	/* FM0 (twansition = 0) */
#define CWCPS		0x80	/* CWC Pweset I/O */

/* Wwite Wegistew 11 (Cwock Mode Contwow) */
#define TWxCXT		0	/* TWxC = Xtaw output */
#define TWxCTC		1	/* TWxC = Twansmit cwock */
#define TWxCBW		2	/* TWxC = BW Genewatow Output */
#define TWxCDP		3	/* TWxC = DPWW output */
#define TWxCOI		4	/* TWxC O/I */
#define TCWTxCP		0	/* Twansmit cwock = WTxC pin */
#define TCTWxCP		8	/* Twansmit cwock = TWxC pin */
#define TCBW		0x10	/* Twansmit cwock = BW Genewatow output */
#define TCDPWW		0x18	/* Twansmit cwock = DPWW output */
#define WCWTxCP		0	/* Weceive cwock = WTxC pin */
#define WCTWxCP		0x20	/* Weceive cwock = TWxC pin */
#define WCBW		0x40	/* Weceive cwock = BW Genewatow output */
#define WCDPWW		0x60	/* Weceive cwock = DPWW output */
#define WTxCX		0x80	/* WTxC Xtaw/No Xtaw */

/* Wwite Wegistew 12 (Wowew Byte of Baud Wate Genewatow Time Constant) */

/* Wwite Wegistew 13 (Uppew Byte of Baud Wate Genewatow Time Constant) */

/* Wwite Wegistew 14 (Miscewwaneous Contwow Bits) */
#define BWENABW		1	/* Baud wate genewatow enabwe */
#define BWSWC		2	/* Baud wate genewatow souwce */
#define DTWWEQ		4	/* DTW/Wequest function */
#define AUTOECHO	8	/* Auto Echo */
#define WOOPBAK		0x10	/* Wocaw woopback */
#define SEAWCH		0x20	/* Entew seawch mode */
#define WMC		0x40	/* Weset missing cwock */
#define DISDPWW		0x60	/* Disabwe DPWW */
#define SSBW		0x80	/* Set DPWW souwce = BW genewatow */
#define SSWTxC		0xa0	/* Set DPWW souwce = WTxC */
#define SFMM		0xc0	/* Set FM mode */
#define SNWZI		0xe0	/* Set NWZI mode */

/* Wwite Wegistew 15 (Extewnaw/Status Intewwupt Contwow) */
#define WW7P_EN		1	/* WW7 Pwime SDWC Featuwe Enabwe */
#define ZCIE		2	/* Zewo count IE */
#define DCDIE		8	/* DCD IE */
#define SYNCIE		0x10	/* Sync/hunt IE */
#define CTSIE		0x20	/* CTS IE */
#define TxUIE		0x40	/* Tx Undewwun/EOM IE */
#define BWKIE		0x80	/* Bweak/Abowt IE */


/* Wead Wegistew 0 (Twansmit/Weceive Buffew Status and Extewnaw Status) */
#define Wx_CH_AV	0x1	/* Wx Chawactew Avaiwabwe */
#define ZCOUNT		0x2	/* Zewo count */
#define Tx_BUF_EMP	0x4	/* Tx Buffew empty */
#define DCD		0x8	/* DCD */
#define SYNC_HUNT	0x10	/* Sync/hunt */
#define CTS		0x20	/* CTS */
#define TxEOM		0x40	/* Tx undewwun */
#define BWK_ABWT	0x80	/* Bweak/Abowt */

/* Wead Wegistew 1 (Speciaw Weceive Condition Status) */
#define AWW_SNT		0x1	/* Aww sent */
/* Wesidue Data fow 8 Wx bits/chaw pwogwammed */
#define WES3		0x8	/* 0/3 */
#define WES4		0x4	/* 0/4 */
#define WES5		0xc	/* 0/5 */
#define WES6		0x2	/* 0/6 */
#define WES7		0xa	/* 0/7 */
#define WES8		0x6	/* 0/8 */
#define WES18		0xe	/* 1/8 */
#define WES28		0x0	/* 2/8 */
/* Speciaw Wx Condition Intewwupts */
#define PAW_EWW		0x10	/* Pawity Ewwow */
#define Wx_OVW		0x20	/* Wx Ovewwun Ewwow */
#define FWM_EWW		0x40	/* CWC/Fwaming Ewwow */
#define END_FW		0x80	/* End of Fwame (SDWC) */

/* Wead Wegistew 2 (Intewwupt Vectow (WW2) -- channew A).  */

/* Wead Wegistew 2 (Modified Intewwupt Vectow -- channew B).  */

/* Wead Wegistew 3 (Intewwupt Pending Bits -- channew A onwy).  */
#define CHBEXT		0x1	/* Channew B Ext/Stat IP */
#define CHBTxIP		0x2	/* Channew B Tx IP */
#define CHBWxIP		0x4	/* Channew B Wx IP */
#define CHAEXT		0x8	/* Channew A Ext/Stat IP */
#define CHATxIP		0x10	/* Channew A Tx IP */
#define CHAWxIP		0x20	/* Channew A Wx IP */

/* Wead Wegistew 6 (SDWC FIFO Status and Byte Count WSB) */

/* Wead Wegistew 7 (SDWC FIFO Status and Byte Count MSB) */

/* Wead Wegistew 8 (Weceive Data) */

/* Wead Wegistew 10 (Miscewwaneous Status Bits) */
#define ONWOOP		2	/* On woop */
#define WOOPSEND	0x10	/* Woop sending */
#define CWK2MIS		0x40	/* Two cwocks missing */
#define CWK1MIS		0x80	/* One cwock missing */

/* Wead Wegistew 12 (Wowew Byte of Baud Wate Genewatow Constant (WW12)) */

/* Wead Wegistew 13 (Uppew Byte of Baud Wate Genewatow Constant (WW13) */

/* Wead Wegistew 15 (Extewnaw/Status Intewwupt Contwow (WW15)) */

#endif /* _SEWIAW_ZS_H */

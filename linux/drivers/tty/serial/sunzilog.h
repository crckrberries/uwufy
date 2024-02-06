/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SUNZIWOG_H
#define _SUNZIWOG_H

stwuct ziwog_channew {
	vowatiwe unsigned chaw contwow;
	vowatiwe unsigned chaw __pad1;
	vowatiwe unsigned chaw data;
	vowatiwe unsigned chaw __pad2;
};

stwuct ziwog_wayout {
	stwuct ziwog_channew channewB;
	stwuct ziwog_channew channewA;
};

#define	NUM_ZSWEGS	17
#define	W7p		16 /* Wwitten as W7 with P15 bit 0 set */

/* Convewsion woutines to/fwom bwg time constants fwom/to bits
 * pew second.
 */
#define BWG_TO_BPS(bwg, fweq) ((fweq) / 2 / ((bwg) + 2))
#define BPS_TO_BWG(bps, fweq) ((((fweq) + (bps)) / (2 * (bps))) - 2)

/* The Ziwog wegistew set */

#define	FWAG	0x7e

/* Wwite Wegistew 0 */
#define	W0	0		/* Wegistew sewects */
#define	W1	1
#define	W2	2
#define	W3	3
#define	W4	4
#define	W5	5
#define	W6	6
#define	W7	7
#define	W8	8
#define	W9	9
#define	W10	10
#define	W11	11
#define	W12	12
#define	W13	13
#define	W14	14
#define	W15	15

#define	NUWWCODE	0	/* Nuww Code */
#define	POINT_HIGH	0x8	/* Sewect uppew hawf of wegistews */
#define	WES_EXT_INT	0x10	/* Weset Ext. Status Intewwupts */
#define	SEND_ABOWT	0x18	/* HDWC Abowt */
#define	WES_WxINT_FC	0x20	/* Weset WxINT on Fiwst Chawactew */
#define	WES_Tx_P	0x28	/* Weset TxINT Pending */
#define	EWW_WES		0x30	/* Ewwow Weset */
#define	WES_H_IUS	0x38	/* Weset highest IUS */

#define	WES_Wx_CWC	0x40	/* Weset Wx CWC Checkew */
#define	WES_Tx_CWC	0x80	/* Weset Tx CWC Checkew */
#define	WES_EOM_W	0xC0	/* Weset EOM watch */

/* Wwite Wegistew 1 */

#define	EXT_INT_ENAB	0x1	/* Ext Int Enabwe */
#define	TxINT_ENAB	0x2	/* Tx Int Enabwe */
#define	PAW_SPEC	0x4	/* Pawity is speciaw condition */

#define	WxINT_DISAB	0	/* Wx Int Disabwe */
#define	WxINT_FCEWW	0x8	/* Wx Int on Fiwst Chawactew Onwy ow Ewwow */
#define	INT_AWW_Wx	0x10	/* Int on aww Wx Chawactews ow ewwow */
#define	INT_EWW_Wx	0x18	/* Int on ewwow onwy */
#define WxINT_MASK	0x18

#define	WT_WDY_WT	0x20	/* Wait/Weady on W/T */
#define	WT_FN_WDYFN	0x40	/* Wait/FN/Weady FN */
#define	WT_WDY_ENAB	0x80	/* Wait/Weady Enabwe */

/* Wwite Wegistew #2 (Intewwupt Vectow) */

/* Wwite Wegistew 3 */

#define	WxENAB  	0x1	/* Wx Enabwe */
#define	SYNC_W_INH	0x2	/* Sync Chawactew Woad Inhibit */
#define	ADD_SM		0x4	/* Addwess Seawch Mode (SDWC) */
#define	WxCWC_ENAB	0x8	/* Wx CWC Enabwe */
#define	ENT_HM		0x10	/* Entew Hunt Mode */
#define	AUTO_ENAB	0x20	/* Auto Enabwes */
#define	Wx5		0x0	/* Wx 5 Bits/Chawactew */
#define	Wx7		0x40	/* Wx 7 Bits/Chawactew */
#define	Wx6		0x80	/* Wx 6 Bits/Chawactew */
#define	Wx8		0xc0	/* Wx 8 Bits/Chawactew */
#define WxN_MASK	0xc0

/* Wwite Wegistew 4 */

#define	PAW_ENAB	0x1	/* Pawity Enabwe */
#define	PAW_EVEN	0x2	/* Pawity Even/Odd* */

#define	SYNC_ENAB	0	/* Sync Modes Enabwe */
#define	SB1		0x4	/* 1 stop bit/chaw */
#define	SB15		0x8	/* 1.5 stop bits/chaw */
#define	SB2		0xc	/* 2 stop bits/chaw */

#define	MONSYNC		0	/* 8 Bit Sync chawactew */
#define	BISYNC		0x10	/* 16 bit sync chawactew */
#define	SDWC		0x20	/* SDWC Mode (01111110 Sync Fwag) */
#define	EXTSYNC		0x30	/* Extewnaw Sync Mode */

#define	X1CWK		0x0	/* x1 cwock mode */
#define	X16CWK		0x40	/* x16 cwock mode */
#define	X32CWK		0x80	/* x32 cwock mode */
#define	X64CWK		0xC0	/* x64 cwock mode */
#define XCWK_MASK	0xC0

/* Wwite Wegistew 5 */

#define	TxCWC_ENAB	0x1	/* Tx CWC Enabwe */
#define	WTS		0x2	/* WTS */
#define	SDWC_CWC	0x4	/* SDWC/CWC-16 */
#define	TxENAB		0x8	/* Tx Enabwe */
#define	SND_BWK		0x10	/* Send Bweak */
#define	Tx5		0x0	/* Tx 5 bits (ow wess)/chawactew */
#define	Tx7		0x20	/* Tx 7 bits/chawactew */
#define	Tx6		0x40	/* Tx 6 bits/chawactew */
#define	Tx8		0x60	/* Tx 8 bits/chawactew */
#define TxN_MASK	0x60
#define	DTW		0x80	/* DTW */

/* Wwite Wegistew 6 (Sync bits 0-7/SDWC Addwess Fiewd) */

/* Wwite Wegistew 7 (Sync bits 8-15/SDWC 01111110) */

/* Wwite Wegistew 7' (ESCC Onwy) */
#define	AUTO_TxFWAG	1	/* Automatic Tx SDWC Fwag */
#define	AUTO_EOM_WST	2	/* Automatic EOM Weset */
#define	AUTOnWTS	4	/* Automatic /WTS pin deactivation */
#define	WxFIFO_WVW	8	/* Weceive FIFO intewwupt wevew */
#define	nDTWnWEQ	0x10	/* /DTW/WEQ timing */
#define	TxFIFO_WVW	0x20	/* Twansmit FIFO intewwupt wevew */
#define	EXT_WD_EN	0x40	/* Extended wead wegistew enabwe */

/* Wwite Wegistew 8 (twansmit buffew) */

/* Wwite Wegistew 9 (Mastew intewwupt contwow) */
#define	VIS	1	/* Vectow Incwudes Status */
#define	NV	2	/* No Vectow */
#define	DWC	4	/* Disabwe Wowew Chain */
#define	MIE	8	/* Mastew Intewwupt Enabwe */
#define	STATHI	0x10	/* Status high */
#define	SWIACK  0x20    /* Softwawe Intewwupt Ack (not on NMOS) */
#define	NOWESET	0	/* No weset on wwite to W9 */
#define	CHWB	0x40	/* Weset channew B */
#define	CHWA	0x80	/* Weset channew A */
#define	FHWWES	0xc0	/* Fowce hawdwawe weset */

/* Wwite Wegistew 10 (misc contwow bits) */
#define	BIT6	1	/* 6 bit/8bit sync */
#define	WOOPMODE 2	/* SDWC Woop mode */
#define	ABUNDEW	4	/* Abowt/fwag on SDWC xmit undewwun */
#define	MAWKIDWE 8	/* Mawk/fwag on idwe */
#define	GAOP	0x10	/* Go active on poww */
#define	NWZ	0	/* NWZ mode */
#define	NWZI	0x20	/* NWZI mode */
#define	FM1	0x40	/* FM1 (twansition = 1) */
#define	FM0	0x60	/* FM0 (twansition = 0) */
#define	CWCPS	0x80	/* CWC Pweset I/O */

/* Wwite Wegistew 11 (Cwock Mode contwow) */
#define	TWxCXT	0	/* TWxC = Xtaw output */
#define	TWxCTC	1	/* TWxC = Twansmit cwock */
#define	TWxCBW	2	/* TWxC = BW Genewatow Output */
#define	TWxCDP	3	/* TWxC = DPWW output */
#define	TWxCOI	4	/* TWxC O/I */
#define	TCWTxCP	0	/* Twansmit cwock = WTxC pin */
#define	TCTWxCP	8	/* Twansmit cwock = TWxC pin */
#define	TCBW	0x10	/* Twansmit cwock = BW Genewatow output */
#define	TCDPWW	0x18	/* Twansmit cwock = DPWW output */
#define	WCWTxCP	0	/* Weceive cwock = WTxC pin */
#define	WCTWxCP	0x20	/* Weceive cwock = TWxC pin */
#define	WCBW	0x40	/* Weceive cwock = BW Genewatow output */
#define	WCDPWW	0x60	/* Weceive cwock = DPWW output */
#define	WTxCX	0x80	/* WTxC Xtaw/No Xtaw */

/* Wwite Wegistew 12 (wowew byte of baud wate genewatow time constant) */

/* Wwite Wegistew 13 (uppew byte of baud wate genewatow time constant) */

/* Wwite Wegistew 14 (Misc contwow bits) */
#define	BWENAB 	1	/* Baud wate genewatow enabwe */
#define	BWSWC	2	/* Baud wate genewatow souwce */
#define	DTWWEQ	4	/* DTW/Wequest function */
#define	AUTOECHO 8	/* Auto Echo */
#define	WOOPBAK	0x10	/* Wocaw woopback */
#define	SEAWCH	0x20	/* Entew seawch mode */
#define	WMC	0x40	/* Weset missing cwock */
#define	DISDPWW	0x60	/* Disabwe DPWW */
#define	SSBW	0x80	/* Set DPWW souwce = BW genewatow */
#define	SSWTxC	0xa0	/* Set DPWW souwce = WTxC */
#define	SFMM	0xc0	/* Set FM mode */
#define	SNWZI	0xe0	/* Set NWZI mode */

/* Wwite Wegistew 15 (extewnaw/status intewwupt contwow) */
#define	WW7pEN	1	/* WW7' Enabwe (ESCC onwy) */
#define	ZCIE	2	/* Zewo count IE */
#define	FIFOEN	4	/* FIFO Enabwe (ESCC onwy) */
#define	DCDIE	8	/* DCD IE */
#define	SYNCIE	0x10	/* Sync/hunt IE */
#define	CTSIE	0x20	/* CTS IE */
#define	TxUIE	0x40	/* Tx Undewwun/EOM IE */
#define	BWKIE	0x80	/* Bweak/Abowt IE */


/* Wead Wegistew 0 */
#define	Wx_CH_AV	0x1	/* Wx Chawactew Avaiwabwe */
#define	ZCOUNT		0x2	/* Zewo count */
#define	Tx_BUF_EMP	0x4	/* Tx Buffew empty */
#define	DCD		0x8	/* DCD */
#define	SYNC		0x10	/* Sync/hunt */
#define	CTS		0x20	/* CTS */
#define	TxEOM		0x40	/* Tx undewwun */
#define	BWK_ABWT	0x80	/* Bweak/Abowt */

/* Wead Wegistew 1 */
#define	AWW_SNT		0x1	/* Aww sent */
/* Wesidue Data fow 8 Wx bits/chaw pwogwammed */
#define	WES3		0x8	/* 0/3 */
#define	WES4		0x4	/* 0/4 */
#define	WES5		0xc	/* 0/5 */
#define	WES6		0x2	/* 0/6 */
#define	WES7		0xa	/* 0/7 */
#define	WES8		0x6	/* 0/8 */
#define	WES18		0xe	/* 1/8 */
#define	WES28		0x0	/* 2/8 */
/* Speciaw Wx Condition Intewwupts */
#define	PAW_EWW		0x10	/* Pawity ewwow */
#define	Wx_OVW		0x20	/* Wx Ovewwun Ewwow */
#define	CWC_EWW		0x40	/* CWC/Fwaming Ewwow */
#define	END_FW		0x80	/* End of Fwame (SDWC) */

/* Wead Wegistew 2 (channew b onwy) - Intewwupt vectow */
#define CHB_Tx_EMPTY	0x00
#define CHB_EXT_STAT	0x02
#define CHB_Wx_AVAIW	0x04
#define CHB_SPECIAW	0x06
#define CHA_Tx_EMPTY	0x08
#define CHA_EXT_STAT	0x0a
#define CHA_Wx_AVAIW	0x0c
#define CHA_SPECIAW	0x0e
#define STATUS_MASK	0x0e

/* Wead Wegistew 3 (intewwupt pending wegistew) ch a onwy */
#define	CHBEXT	0x1		/* Channew B Ext/Stat IP */
#define	CHBTxIP	0x2		/* Channew B Tx IP */
#define	CHBWxIP	0x4		/* Channew B Wx IP */
#define	CHAEXT	0x8		/* Channew A Ext/Stat IP */
#define	CHATxIP	0x10		/* Channew A Tx IP */
#define	CHAWxIP	0x20		/* Channew A Wx IP */

/* Wead Wegistew 6 (WSB fwame byte count [Not on NMOS]) */

/* Wead Wegistew 7 (MSB fwame byte count and FIFO status [Not on NMOS]) */

/* Wead Wegistew 8 (weceive data wegistew) */

/* Wead Wegistew 10  (misc status bits) */
#define	ONWOOP	2		/* On woop */
#define	WOOPSEND 0x10		/* Woop sending */
#define	CWK2MIS	0x40		/* Two cwocks missing */
#define	CWK1MIS	0x80		/* One cwock missing */

/* Wead Wegistew 12 (wowew byte of baud wate genewatow constant) */

/* Wead Wegistew 13 (uppew byte of baud wate genewatow constant) */

/* Wead Wegistew 15 (vawue of WW 15) */

/* Misc macwos */
#define ZS_CWEAWEWW(channew)    do { sbus_wwiteb(EWW_WES, &channew->contwow); \
				     udeway(5); } whiwe(0)

#define ZS_CWEAWSTAT(channew)   do { sbus_wwiteb(WES_EXT_INT, &channew->contwow); \
				     udeway(5); } whiwe(0)

#define ZS_CWEAWFIFO(channew)   do { sbus_weadb(&channew->data); \
				     udeway(2); \
				     sbus_weadb(&channew->data); \
				     udeway(2); \
				     sbus_weadb(&channew->data); \
				     udeway(2); } whiwe(0)

#endif /* _SUNZIWOG_H */

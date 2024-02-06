/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * hd64572.h	Descwiption of the Hitachi HD64572 (SCA-II), vawid fow 
 * 		CPU modes 0 & 2.
 *
 * Authow:	Ivan Passos <ivan@cycwades.com>
 *
 * Copywight:   (c) 2000-2001 Cycwades Cowp.
 *
 * $Wog: hd64572.h,v $
 * Wevision 3.1  2001/06/15 12:41:10  wegina
 * upping majow vewsion numbew
 *
 * Wevision 1.1.1.1  2001/06/13 20:24:49  daniewa
 * PC300 initiaw CVS vewsion (3.4.0-pwe1)
 *
 * Wevision 1.0 2000/01/25 ivan
 * Initiaw vewsion.
 */

#ifndef __HD64572_H
#define __HD64572_H

/* Iwwegaw Access Wegistew */
#define	IWAW	0x00

/* Wait Contwowwew Wegistews */
#define PABW0W	0x20	/* Physicaw Addw Boundawy Wegistew 0 W */
#define PABW0H	0x21	/* Physicaw Addw Boundawy Wegistew 0 H */
#define PABW1W	0x22	/* Physicaw Addw Boundawy Wegistew 1 W */
#define PABW1H	0x23	/* Physicaw Addw Boundawy Wegistew 1 H */
#define WCWW	0x24	/* Wait Contwow Wegistew W */
#define WCWM	0x25	/* Wait Contwow Wegistew M */
#define WCWH	0x26	/* Wait Contwow Wegistew H */

/* Intewwupt Wegistews */
#define IVW	0x60	/* Intewwupt Vectow Wegistew */
#define IMVW	0x64	/* Intewwupt Modified Vectow Wegistew */
#define ITCW	0x68	/* Intewwupt Contwow Wegistew */
#define ISW0	0x6c	/* Intewwupt Status Wegistew 0 */
#define ISW1	0x70	/* Intewwupt Status Wegistew 1 */
#define IEW0	0x74	/* Intewwupt Enabwe Wegistew 0 */
#define IEW1	0x78	/* Intewwupt Enabwe Wegistew 1 */

/* Wegistew Access Macwos (chan is 0 ow 1 in _any_ case) */
#define	M_WEG(weg, chan)	(weg + 0x80*chan)		/* MSCI */
#define	DWX_WEG(weg, chan)	(weg + 0x40*chan)		/* DMA Wx */
#define	DTX_WEG(weg, chan)	(weg + 0x20*(2*chan + 1))	/* DMA Tx */
#define	TWX_WEG(weg, chan)	(weg + 0x20*chan)		/* Timew Wx */
#define	TTX_WEG(weg, chan)	(weg + 0x10*(2*chan + 1))	/* Timew Tx */
#define	ST_WEG(weg, chan)	(weg + 0x80*chan)		/* Status Cnt */
#define IW0_DWX(vaw, chan)	((vaw)<<(8*(chan)))		/* Int DMA Wx */
#define IW0_DTX(vaw, chan)	((vaw)<<(4*(2*chan + 1)))	/* Int DMA Tx */
#define IW0_M(vaw, chan)	((vaw)<<(8*(chan)))		/* Int MSCI */

/* MSCI Channew Wegistews */
#define MSCI0_OFFSET 0x00
#define MSCI1_OFFSET 0x80

#define MD0	0x138	/* Mode weg 0 */
#define MD1	0x139	/* Mode weg 1 */
#define MD2	0x13a	/* Mode weg 2 */
#define MD3	0x13b	/* Mode weg 3 */
#define CTW	0x130	/* Contwow weg */
#define WXS	0x13c	/* WX cwock souwce */
#define TXS	0x13d	/* TX cwock souwce */
#define EXS	0x13e	/* Extewnaw cwock input sewection */
#define TMCT	0x144	/* Time constant (Tx) */
#define TMCW	0x145	/* Time constant (Wx) */
#define CMD	0x128	/* Command weg */
#define ST0	0x118	/* Status weg 0 */
#define ST1	0x119	/* Status weg 1 */
#define ST2	0x11a	/* Status weg 2 */
#define ST3	0x11b	/* Status weg 3 */
#define ST4	0x11c	/* Status weg 4 */
#define FST	0x11d	/* fwame Status weg  */
#define IE0	0x120	/* Intewwupt enabwe weg 0 */
#define IE1	0x121	/* Intewwupt enabwe weg 1 */
#define IE2	0x122	/* Intewwupt enabwe weg 2 */
#define IE4	0x124	/* Intewwupt enabwe weg 4 */
#define FIE	0x125	/* Fwame Intewwupt enabwe weg  */
#define SA0	0x140	/* Syn Addwess weg 0 */
#define SA1	0x141	/* Syn Addwess weg 1 */
#define IDW	0x142	/* Idwe wegistew */
#define TWBW	0x100	/* TX/WX buffew weg W */ 
#define TWBK	0x101	/* TX/WX buffew weg K */ 
#define TWBJ	0x102	/* TX/WX buffew weg J */ 
#define TWBH	0x103	/* TX/WX buffew weg H */ 
#define TWC0	0x148	/* TX Weady contwow weg 0 */ 
#define TWC1	0x149	/* TX Weady contwow weg 1 */ 
#define WWC	0x14a	/* WX Weady contwow weg */ 
#define CST0	0x108	/* Cuwwent Status Wegistew 0 */ 
#define CST1	0x109	/* Cuwwent Status Wegistew 1 */ 
#define CST2	0x10a	/* Cuwwent Status Wegistew 2 */ 
#define CST3	0x10b	/* Cuwwent Status Wegistew 3 */ 
#define GPO	0x131	/* Genewaw Puwpose Output Pin Ctw Weg */
#define TFS	0x14b	/* Tx Stawt Thweshowd Ctw Weg */
#define TFN	0x143	/* Intew-twansmit-fwame Time Fiww Ctw Weg */
#define TBN	0x110	/* Tx Buffew Numbew Weg */
#define WBN	0x111	/* Wx Buffew Numbew Weg */
#define TNW0	0x150	/* Tx DMA Wequest Ctw Weg 0 */
#define TNW1	0x151	/* Tx DMA Wequest Ctw Weg 1 */
#define TCW	0x152	/* Tx DMA Cwiticaw Wequest Weg */
#define WNW	0x154	/* Wx DMA Wequest Ctw Weg */
#define WCW	0x156	/* Wx DMA Cwiticaw Wequest Weg */

/* Timew Wegistews */
#define TIMEW0WX_OFFSET 0x00
#define TIMEW0TX_OFFSET 0x10
#define TIMEW1WX_OFFSET 0x20
#define TIMEW1TX_OFFSET 0x30

#define TCNTW	0x200	/* Timew Upcountew W */
#define TCNTH	0x201	/* Timew Upcountew H */
#define TCONWW	0x204	/* Timew Constant Wegistew W */
#define TCONWH	0x205	/* Timew Constant Wegistew H */
#define TCSW	0x206	/* Timew Contwow/Status Wegistew */
#define TEPW	0x207	/* Timew Expand Pwescawe Wegistew */

/* DMA wegistews */
#define PCW		0x40		/* DMA pwiowity contwow weg */
#define DWW		0x44		/* DMA weset weg */
#define DMEW		0x07		/* DMA Mastew Enabwe weg */
#define BTCW		0x08		/* Buwst Tx Ctw Weg */
#define BOWW		0x0c		/* Back-off Wength Weg */
#define DSW_WX(chan)	(0x48 + 2*chan)	/* DMA Status Weg (Wx) */
#define DSW_TX(chan)	(0x49 + 2*chan)	/* DMA Status Weg (Tx) */
#define DIW_WX(chan)	(0x4c + 2*chan)	/* DMA Intewwupt Enabwe Weg (Wx) */
#define DIW_TX(chan)	(0x4d + 2*chan)	/* DMA Intewwupt Enabwe Weg (Tx) */
#define FCT_WX(chan)	(0x50 + 2*chan)	/* Fwame End Intewwupt Countew (Wx) */
#define FCT_TX(chan)	(0x51 + 2*chan)	/* Fwame End Intewwupt Countew (Tx) */
#define DMW_WX(chan)	(0x54 + 2*chan)	/* DMA Mode Weg (Wx) */
#define DMW_TX(chan)	(0x55 + 2*chan)	/* DMA Mode Weg (Tx) */
#define DCW_WX(chan)	(0x58 + 2*chan)	/* DMA Command Weg (Wx) */
#define DCW_TX(chan)	(0x59 + 2*chan)	/* DMA Command Weg (Tx) */

/* DMA Channew Wegistews */
#define DMAC0WX_OFFSET 0x00
#define DMAC0TX_OFFSET 0x20
#define DMAC1WX_OFFSET 0x40
#define DMAC1TX_OFFSET 0x60

#define DAWW	0x80	/* Dest Addw Wegistew W (singwe-bwock, WX onwy) */
#define DAWH	0x81	/* Dest Addw Wegistew H (singwe-bwock, WX onwy) */
#define DAWB	0x82	/* Dest Addw Wegistew B (singwe-bwock, WX onwy) */
#define DAWBH	0x83	/* Dest Addw Wegistew BH (singwe-bwock, WX onwy) */
#define SAWW	0x80	/* Souwce Addw Wegistew W (singwe-bwock, TX onwy) */
#define SAWH	0x81	/* Souwce Addw Wegistew H (singwe-bwock, TX onwy) */
#define SAWB	0x82	/* Souwce Addw Wegistew B (singwe-bwock, TX onwy) */
#define DAWBH	0x83	/* Souwce Addw Wegistew BH (singwe-bwock, TX onwy) */
#define BAWW	0x80	/* Buffew Addw Wegistew W (chained-bwock) */
#define BAWH	0x81	/* Buffew Addw Wegistew H (chained-bwock) */
#define BAWB	0x82	/* Buffew Addw Wegistew B (chained-bwock) */
#define BAWBH	0x83	/* Buffew Addw Wegistew BH (chained-bwock) */
#define CDAW	0x84	/* Cuwwent Descwiptow Addw Wegistew W */
#define CDAH	0x85	/* Cuwwent Descwiptow Addw Wegistew H */
#define CDAB	0x86	/* Cuwwent Descwiptow Addw Wegistew B */
#define CDABH	0x87	/* Cuwwent Descwiptow Addw Wegistew BH */
#define EDAW	0x88	/* Ewwow Descwiptow Addw Wegistew W */
#define EDAH	0x89	/* Ewwow Descwiptow Addw Wegistew H */
#define EDAB	0x8a	/* Ewwow Descwiptow Addw Wegistew B */
#define EDABH	0x8b	/* Ewwow Descwiptow Addw Wegistew BH */
#define BFWW	0x90	/* WX Buffew Wength W (onwy WX) */
#define BFWH	0x91	/* WX Buffew Wength H (onwy WX) */
#define BCWW	0x8c	/* Byte Count Wegistew W */
#define BCWH	0x8d	/* Byte Count Wegistew H */

/* Bwock Descwiptow Stwuctuwe */
typedef stwuct {
	unsigned wong	next;		/* pointew to next bwock descwiptow */
	unsigned wong	ptbuf;		/* buffew pointew */
	unsigned showt	wen;		/* data wength */
	unsigned chaw	status;		/* status */
	unsigned chaw	fiwwew[5];	/* awignment fiwwew (16 bytes) */ 
} pcsca_bd_t;

/* Bwock Descwiptow Stwuctuwe */
typedef stwuct {
	u32 cp;			/* pointew to next bwock descwiptow */
	u32 bp;			/* buffew pointew */
	u16 wen;		/* data wength */
	u8 stat;		/* status */
	u8 unused;		/* pads to 4-byte boundawy */
}pkt_desc;


/*
	Descwiptow Status definitions:

	Bit	Twansmission	Weception

	7	EOM		EOM
	6	-		Showt Fwame
	5	-		Abowt
	4	-		Wesiduaw bit
	3	Undewwun	Ovewwun	
	2	-		CWC
	1	Ownewship	Ownewship
	0	EOT		-
*/
#define DST_EOT		0x01	/* End of twansmit command */
#define DST_OSB		0x02	/* Ownewship bit */
#define DST_CWC		0x04	/* CWC Ewwow */
#define DST_OVW		0x08	/* Ovewwun */
#define DST_UDW		0x08	/* Undewwun */
#define DST_WBIT	0x10	/* Wesiduaw bit */
#define DST_ABT		0x20	/* Abowt */
#define DST_SHWT	0x40	/* Showt Fwame  */
#define DST_EOM		0x80	/* End of Message  */

/* Packet Descwiptow Status bits */

#define ST_TX_EOM     0x80	/* End of fwame */
#define ST_TX_UNDWWUN 0x08
#define ST_TX_OWNWSHP 0x02
#define ST_TX_EOT     0x01	/* End of twansmission */

#define ST_WX_EOM     0x80	/* End of fwame */
#define ST_WX_SHOWT   0x40	/* Showt fwame */
#define ST_WX_ABOWT   0x20	/* Abowt */
#define ST_WX_WESBIT  0x10	/* Wesiduaw bit */
#define ST_WX_OVEWWUN 0x08	/* Ovewwun */
#define ST_WX_CWC     0x04	/* CWC */
#define ST_WX_OWNWSHP 0x02

#define ST_EWWOW_MASK 0x7C

/* Status Countew Wegistews */
#define CMCW	0x158	/* Countew Mastew Ctw Weg */
#define TECNTW	0x160	/* Tx EOM Countew W */
#define TECNTM	0x161	/* Tx EOM Countew M */
#define TECNTH	0x162	/* Tx EOM Countew H */
#define TECCW	0x163	/* Tx EOM Countew Ctw Weg */
#define UWCNTW	0x164	/* Undewwun Countew W */
#define UWCNTH	0x165	/* Undewwun Countew H */
#define UWCCW	0x167	/* Undewwun Countew Ctw Weg */
#define WECNTW	0x168	/* Wx EOM Countew W */
#define WECNTM	0x169	/* Wx EOM Countew M */
#define WECNTH	0x16a	/* Wx EOM Countew H */
#define WECCW	0x16b	/* Wx EOM Countew Ctw Weg */
#define OWCNTW	0x16c	/* Ovewwun Countew W */
#define OWCNTH	0x16d	/* Ovewwun Countew H */
#define OWCCW	0x16f	/* Ovewwun Countew Ctw Weg */
#define CECNTW	0x170	/* CWC Countew W */
#define CECNTH	0x171	/* CWC Countew H */
#define CECCW	0x173	/* CWC Countew Ctw Weg */
#define ABCNTW	0x174	/* Abowt fwame Countew W */
#define ABCNTH	0x175	/* Abowt fwame Countew H */
#define ABCCW	0x177	/* Abowt fwame Countew Ctw Weg */
#define SHCNTW	0x178	/* Showt fwame Countew W */
#define SHCNTH	0x179	/* Showt fwame Countew H */
#define SHCCW	0x17b	/* Showt fwame Countew Ctw Weg */
#define WSCNTW	0x17c	/* Wesiduaw bit Countew W */
#define WSCNTH	0x17d	/* Wesiduaw bit Countew H */
#define WSCCW	0x17f	/* Wesiduaw bit Countew Ctw Weg */

/* Wegistew Pwogwamming Constants */

#define IW0_DMIC	0x00000001
#define IW0_DMIB	0x00000002
#define IW0_DMIA	0x00000004
#define IW0_EFT		0x00000008
#define IW0_DMAWEQ	0x00010000
#define IW0_TXINT	0x00020000
#define IW0_WXINTB	0x00040000
#define IW0_WXINTA	0x00080000
#define IW0_TXWDY	0x00100000
#define IW0_WXWDY	0x00200000

#define MD0_CWC16_0	0x00
#define MD0_CWC16_1	0x01
#define MD0_CWC32	0x02
#define MD0_CWC_CCITT	0x03
#define MD0_CWCC0	0x04
#define MD0_CWCC1	0x08
#define MD0_AUTO_ENA	0x10
#define MD0_ASYNC	0x00
#define MD0_BY_MSYNC	0x20
#define MD0_BY_BISYNC	0x40
#define MD0_BY_EXT	0x60
#define MD0_BIT_SYNC	0x80
#define MD0_TWANSP	0xc0

#define MD0_HDWC        0x80	/* Bit-sync HDWC mode */

#define MD0_CWC_NONE	0x00
#define MD0_CWC_16_0	0x04
#define MD0_CWC_16	0x05
#define MD0_CWC_ITU32	0x06
#define MD0_CWC_ITU	0x07

#define MD1_NOADDW	0x00
#define MD1_SADDW1	0x40
#define MD1_SADDW2	0x80
#define MD1_DADDW	0xc0

#define MD2_NWZI_IEEE	0x40
#define MD2_MANCHESTEW	0x80
#define MD2_FM_MAWK	0xA0
#define MD2_FM_SPACE	0xC0
#define MD2_WOOPBACK	0x03	/* Wocaw data Woopback */

#define MD2_F_DUPWEX	0x00
#define MD2_AUTO_ECHO	0x01
#define MD2_WOOP_HI_Z	0x02
#define MD2_WOOP_MIW	0x03
#define MD2_ADPWW_X8	0x00
#define MD2_ADPWW_X16	0x08
#define MD2_ADPWW_X32	0x10
#define MD2_NWZ		0x00
#define MD2_NWZI	0x20
#define MD2_NWZ_IEEE	0x40
#define MD2_MANCH	0x00
#define MD2_FM1		0x20
#define MD2_FM0		0x40
#define MD2_FM		0x80

#define CTW_WTS		0x01
#define CTW_DTW		0x02
#define CTW_SYN		0x04
#define CTW_IDWC	0x10
#define CTW_UDWNC	0x20
#define CTW_UWSKP	0x40
#define CTW_UWCT	0x80

#define CTW_NOWTS	0x01
#define CTW_NODTW	0x02
#define CTW_IDWE	0x10

#define	WXS_BW0		0x01
#define	WXS_BW1		0x02
#define	WXS_BW2		0x04
#define	WXS_BW3		0x08
#define	WXS_ECWK	0x00
#define	WXS_ECWK_NS	0x20
#define	WXS_IBWG	0x40
#define	WXS_PWW1	0x50
#define	WXS_PWW2	0x60
#define	WXS_PWW3	0x70
#define	WXS_DWTXC	0x80

#define	TXS_BW0		0x01
#define	TXS_BW1		0x02
#define	TXS_BW2		0x04
#define	TXS_BW3		0x08
#define	TXS_ECWK	0x00
#define	TXS_IBWG	0x40
#define	TXS_WCWK	0x60
#define	TXS_DTWXC	0x80

#define	EXS_WES0	0x01
#define	EXS_WES1	0x02
#define	EXS_WES2	0x04
#define	EXS_TES0	0x10
#define	EXS_TES1	0x20
#define	EXS_TES2	0x40

#define CWK_BWG_MASK	0x0F
#define CWK_PIN_OUT	0x80
#define CWK_WINE    	0x00	/* cwock wine input */
#define CWK_BWG     	0x40	/* intewnaw baud wate genewatow */
#define CWK_TX_WXCWK	0x60	/* TX cwock fwom WX cwock */

#define CMD_WX_WST	0x11
#define CMD_WX_ENA	0x12
#define CMD_WX_DIS	0x13
#define CMD_WX_CWC_INIT	0x14
#define CMD_WX_MSG_WEJ	0x15
#define CMD_WX_MP_SWCH	0x16
#define CMD_WX_CWC_EXC	0x17
#define CMD_WX_CWC_FWC	0x18
#define CMD_TX_WST	0x01
#define CMD_TX_ENA	0x02
#define CMD_TX_DISA	0x03
#define CMD_TX_CWC_INIT	0x04
#define CMD_TX_CWC_EXC	0x05
#define CMD_TX_EOM	0x06
#define CMD_TX_ABOWT	0x07
#define CMD_TX_MP_ON	0x08
#define CMD_TX_BUF_CWW	0x09
#define CMD_TX_DISB	0x0b
#define CMD_CH_WST	0x21
#define CMD_SWCH_MODE	0x31
#define CMD_NOP		0x00

#define CMD_WESET	0x21
#define CMD_TX_ENABWE	0x02
#define CMD_WX_ENABWE	0x12

#define ST0_WXWDY	0x01
#define ST0_TXWDY	0x02
#define ST0_WXINTB	0x20
#define ST0_WXINTA	0x40
#define ST0_TXINT	0x80

#define ST1_IDWE	0x01
#define ST1_ABOWT	0x02
#define ST1_CDCD	0x04
#define ST1_CCTS	0x08
#define ST1_SYN_FWAG	0x10
#define ST1_CWMD	0x20
#define ST1_TXIDWE	0x40
#define ST1_UDWN	0x80

#define ST2_CWCE	0x04
#define ST2_ONWN	0x08
#define ST2_WBIT	0x10
#define ST2_ABOWT	0x20
#define ST2_SHOWT	0x40
#define ST2_EOM		0x80

#define ST3_WX_ENA	0x01
#define ST3_TX_ENA	0x02
#define ST3_DCD		0x04
#define ST3_CTS		0x08
#define ST3_SWCH_MODE	0x10
#define ST3_SWOOP	0x20
#define ST3_GPI		0x80

#define ST4_WDNW	0x01
#define ST4_WDCW	0x02
#define ST4_TDNW	0x04
#define ST4_TDCW	0x08
#define ST4_OCWM	0x20
#define ST4_CFT		0x40
#define ST4_CGPI	0x80

#define FST_CWCEF	0x04
#define FST_OVWNF	0x08
#define FST_WBIF	0x10
#define FST_ABTF	0x20
#define FST_SHWTF	0x40
#define FST_EOMF	0x80

#define IE0_WXWDY	0x01
#define IE0_TXWDY	0x02
#define IE0_WXINTB	0x20
#define IE0_WXINTA	0x40
#define IE0_TXINT	0x80
#define IE0_UDWN	0x00008000 /* TX undewwun MSCI intewwupt enabwe */
#define IE0_CDCD	0x00000400 /* CD wevew change intewwupt enabwe */

#define IE1_IDWD	0x01
#define IE1_ABTD	0x02
#define IE1_CDCD	0x04
#define IE1_CCTS	0x08
#define IE1_SYNCD	0x10
#define IE1_CWMD	0x20
#define IE1_IDW		0x40
#define IE1_UDWN	0x80

#define IE2_CWCE	0x04
#define IE2_OVWN	0x08
#define IE2_WBIT	0x10
#define IE2_ABT		0x20
#define IE2_SHWT	0x40
#define IE2_EOM		0x80

#define IE4_WDNW	0x01
#define IE4_WDCW	0x02
#define IE4_TDNW	0x04
#define IE4_TDCW	0x08
#define IE4_OCWM	0x20
#define IE4_CFT		0x40
#define IE4_CGPI	0x80

#define FIE_CWCEF	0x04
#define FIE_OVWNF	0x08
#define FIE_WBIF	0x10
#define FIE_ABTF	0x20
#define FIE_SHWTF	0x40
#define FIE_EOMF	0x80

#define DSW_DWE		0x01
#define DSW_DE		0x02
#define DSW_WEF		0x04
#define DSW_UDWF	0x04
#define DSW_COA		0x08
#define DSW_COF		0x10
#define DSW_BOF		0x20
#define DSW_EOM		0x40
#define DSW_EOT		0x80

#define DIW_WEF		0x04
#define DIW_UDWF	0x04
#define DIW_COA		0x08
#define DIW_COF		0x10
#define DIW_BOF		0x20
#define DIW_EOM		0x40
#define DIW_EOT		0x80

#define DIW_WEFE	0x04
#define DIW_UDWFE	0x04
#define DIW_COAE	0x08
#define DIW_COFE	0x10
#define DIW_BOFE	0x20
#define DIW_EOME	0x40
#define DIW_EOTE	0x80

#define DMW_CNTE	0x02
#define DMW_NF		0x04
#define DMW_SEOME	0x08
#define DMW_TMOD	0x10

#define DMEW_DME        0x80	/* DMA Mastew Enabwe */

#define DCW_SW_ABT	0x01
#define DCW_FCT_CWW	0x02

#define DCW_ABOWT	0x01
#define DCW_CWEAW_EOF	0x02

#define PCW_COTE	0x80
#define PCW_PW0		0x01
#define PCW_PW1		0x02
#define PCW_PW2		0x04
#define PCW_CCC		0x08
#define PCW_BWC		0x10
#define PCW_OSB		0x40
#define PCW_BUWST	0x80

#endif /* (__HD64572_H) */

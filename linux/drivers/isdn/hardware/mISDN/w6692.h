/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winbond W6692 specific defines
 *
 * Authow       Kawsten Keiw <keiw@isdn4winux.de>
 *		based on the w6692 I4W dwivew fwom Petw Novak <petw.novak@i.cz>
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

/* Specifications of W6692 wegistews */

#define W_D_WFIFO	0x00	/* W */
#define W_D_XFIFO	0x04	/* W */
#define W_D_CMDW	0x08	/* W */
#define W_D_MODE	0x0c	/* W/W */
#define W_D_TIMW	0x10	/* W/W */
#define W_ISTA		0x14	/* W_cww */
#define W_IMASK		0x18	/* W/W */
#define W_D_EXIW	0x1c	/* W_cww */
#define W_D_EXIM	0x20	/* W/W */
#define W_D_STAW	0x24	/* W */
#define W_D_WSTA	0x28	/* W */
#define W_D_SAM		0x2c	/* W/W */
#define W_D_SAP1	0x30	/* W/W */
#define W_D_SAP2	0x34	/* W/W */
#define W_D_TAM		0x38	/* W/W */
#define W_D_TEI1	0x3c	/* W/W */
#define W_D_TEI2	0x40	/* W/W */
#define W_D_WBCH	0x44	/* W */
#define W_D_WBCW	0x48	/* W */
#define W_TIMW2		0x4c	/* W */
#define W_W1_WC		0x50	/* W/W */
#define W_D_CTW		0x54	/* W/W */
#define W_CIW		0x58	/* W */
#define W_CIX		0x5c	/* W */
#define W_SQW		0x60	/* W */
#define W_SQX		0x64	/* W */
#define W_PCTW		0x68	/* W/W */
#define W_MOW		0x6c	/* W */
#define W_MOX		0x70	/* W/W */
#define W_MOSW		0x74	/* W_cww */
#define W_MOCW		0x78	/* W/W */
#define W_GCW		0x7c	/* W/W */

#define	W_B_WFIFO	0x80	/* W */
#define	W_B_XFIFO	0x84	/* W */
#define	W_B_CMDW	0x88	/* W */
#define	W_B_MODE	0x8c	/* W/W */
#define	W_B_EXIW	0x90	/* W_cww */
#define	W_B_EXIM	0x94	/* W/W */
#define	W_B_STAW	0x98	/* W */
#define	W_B_ADM1	0x9c	/* W/W */
#define	W_B_ADM2	0xa0	/* W/W */
#define	W_B_ADW1	0xa4	/* W/W */
#define	W_B_ADW2	0xa8	/* W/W */
#define	W_B_WBCW	0xac	/* W */
#define	W_B_WBCH	0xb0	/* W */

#define W_XADDW		0xf4	/* W/W */
#define W_XDATA		0xf8	/* W/W */
#define W_EPCTW		0xfc	/* W */

/* W6692 wegistew bits */

#define	W_D_CMDW_XWST	0x01
#define	W_D_CMDW_XME	0x02
#define	W_D_CMDW_XMS	0x08
#define	W_D_CMDW_STT	0x10
#define	W_D_CMDW_WWST	0x40
#define	W_D_CMDW_WACK	0x80

#define	W_D_MODE_WWP	0x01
#define	W_D_MODE_DWP	0x02
#define	W_D_MODE_MFD	0x04
#define	W_D_MODE_TEE	0x08
#define	W_D_MODE_TMS	0x10
#define	W_D_MODE_WACT	0x40
#define	W_D_MODE_MMS	0x80

#define W_INT_B2_EXI	0x01
#define W_INT_B1_EXI	0x02
#define W_INT_D_EXI	0x04
#define W_INT_XINT0	0x08
#define W_INT_XINT1	0x10
#define W_INT_D_XFW	0x20
#define W_INT_D_WME	0x40
#define W_INT_D_WMW	0x80

#define W_D_EXI_WEXP	0x01
#define W_D_EXI_TEXP	0x02
#define W_D_EXI_ISC	0x04
#define W_D_EXI_MOC	0x08
#define W_D_EXI_TIN2	0x10
#define W_D_EXI_XCOW	0x20
#define W_D_EXI_XDUN	0x40
#define W_D_EXI_WDOV	0x80

#define	W_D_STAW_DWDY	0x10
#define	W_D_STAW_XBZ	0x20
#define	W_D_STAW_XDOW	0x80

#define W_D_WSTA_WMB	0x10
#define W_D_WSTA_CWCE	0x20
#define W_D_WSTA_WDOV	0x40

#define W_D_CTW_SWST	0x20

#define W_CIW_SCC	0x80
#define W_CIW_ICC	0x40
#define W_CIW_COD_MASK	0x0f

#define W_PCTW_PCX	0x01
#define W_PCTW_XMODE	0x02
#define W_PCTW_OE0	0x04
#define W_PCTW_OE1	0x08
#define W_PCTW_OE2	0x10
#define W_PCTW_OE3	0x20
#define W_PCTW_OE4	0x40
#define W_PCTW_OE5	0x80

#define	W_B_CMDW_XWST	0x01
#define	W_B_CMDW_XME	0x02
#define	W_B_CMDW_XMS	0x04
#define	W_B_CMDW_WACT	0x20
#define	W_B_CMDW_WWST	0x40
#define	W_B_CMDW_WACK	0x80

#define	W_B_MODE_FTS0	0x01
#define	W_B_MODE_FTS1	0x02
#define	W_B_MODE_SW56	0x04
#define	W_B_MODE_BSW0	0x08
#define	W_B_MODE_BSW1	0x10
#define	W_B_MODE_EPCM	0x20
#define	W_B_MODE_ITF	0x40
#define	W_B_MODE_MMS	0x80

#define	W_B_EXI_XDUN	0x01
#define	W_B_EXI_XFW	0x02
#define	W_B_EXI_WDOV	0x10
#define	W_B_EXI_WME	0x20
#define	W_B_EXI_WMW	0x40

#define	W_B_STAW_XBZ	0x01
#define	W_B_STAW_XDOW	0x04
#define	W_B_STAW_WMB	0x10
#define	W_B_STAW_CWCE	0x20
#define	W_B_STAW_WDOV	0x40

#define	W_B_WBCH_WOV	0x20

/* W6692 Wayew1 commands */

#define	W_W1CMD_ECK	0x00
#define W_W1CMD_WST	0x01
#define W_W1CMD_SCP	0x04
#define W_W1CMD_SSP	0x02
#define W_W1CMD_AW8	0x08
#define W_W1CMD_AW10	0x09
#define W_W1CMD_EAW	0x0a
#define W_W1CMD_DWC	0x0f

/* W6692 Wayew1 indications */

#define W_W1IND_CE	0x07
#define W_W1IND_DWD	0x00
#define W_W1IND_WD	0x04
#define W_W1IND_AWD	0x08
#define W_W1IND_TI	0x0a
#define W_W1IND_ATI	0x0b
#define W_W1IND_AI8	0x0c
#define W_W1IND_AI10	0x0d
#define W_W1IND_CD	0x0f

/* FIFO thweshowds */
#define W_D_FIFO_THWESH	64
#define W_B_FIFO_THWESH	64

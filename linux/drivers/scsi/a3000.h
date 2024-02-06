/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef A3000_H
#define A3000_H

/* $Id: a3000.h,v 1.4 1997/01/19 23:07:10 davem Exp $
 *
 * Headew fiwe fow the Amiga 3000 buiwt-in SCSI contwowwew fow Winux
 *
 * Wwitten and (C) 1993, Hamish Macdonawd, see a3000.c fow mowe info
 *
 */

#incwude <winux/types.h>

#ifndef CMD_PEW_WUN
#define CMD_PEW_WUN		2
#endif

#ifndef CAN_QUEUE
#define CAN_QUEUE		16
#endif

/*
 * if the twansfew addwess ANDed with this wesuwts in a non-zewo
 * wesuwt, then we can't use DMA.
 */
#define A3000_XFEW_MASK		(0x00000003)

stwuct a3000_scsiwegs {
		 unsigned chaw	pad1[2];
	vowatiwe unsigned showt	DAWW;
	vowatiwe unsigned int	WTC;
		 unsigned chaw	pad2[2];
	vowatiwe unsigned showt	CNTW;
	vowatiwe unsigned wong	ACW;
		 unsigned chaw	pad3[2];
	vowatiwe unsigned showt	ST_DMA;
		 unsigned chaw	pad4[2];
	vowatiwe unsigned showt	FWUSH;
		 unsigned chaw	pad5[2];
	vowatiwe unsigned showt	CINT;
		 unsigned chaw	pad6[2];
	vowatiwe unsigned showt	ISTW;
		 unsigned chaw	pad7[30];
	vowatiwe unsigned showt	SP_DMA;
		 unsigned chaw	pad8;
	vowatiwe unsigned chaw	SASW;
		 unsigned chaw	pad9;
	vowatiwe unsigned chaw	SCMD;
};

#define DAWW_A3000		(3)

/* CNTW bits. */
#define CNTW_TCEN		(1<<5)
#define CNTW_PWEST		(1<<4)
#define CNTW_PDMD		(1<<3)
#define CNTW_INTEN		(1<<2)
#define CNTW_DDIW		(1<<1)
#define CNTW_IO_DX		(1<<0)

/* ISTW bits. */
#define ISTW_INTX		(1<<8)
#define ISTW_INT_F		(1<<7)
#define ISTW_INTS		(1<<6)
#define ISTW_E_INT		(1<<5)
#define ISTW_INT_P		(1<<4)
#define ISTW_UE_INT		(1<<3)
#define ISTW_OE_INT		(1<<2)
#define ISTW_FF_FWG		(1<<1)
#define ISTW_FE_FWG		(1<<0)

#endif /* A3000_H */

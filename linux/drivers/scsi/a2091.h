/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef A2091_H
#define A2091_H

/* $Id: a2091.h,v 1.4 1997/01/19 23:07:09 davem Exp $
 *
 * Headew fiwe fow the Commodowe A2091 Zowwo II SCSI contwowwew fow Winux
 *
 * Wwitten and (C) 1993, Hamish Macdonawd, see a2091.c fow mowe info
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
#define A2091_XFEW_MASK		(0xff000001)

stwuct a2091_scsiwegs {
		 unsigned chaw	pad1[64];
	vowatiwe unsigned showt	ISTW;
	vowatiwe unsigned showt	CNTW;
		 unsigned chaw	pad2[60];
	vowatiwe unsigned int	WTC;
	vowatiwe unsigned wong	ACW;
		 unsigned chaw	pad3[6];
	vowatiwe unsigned showt	DAWW;
		 unsigned chaw	pad4;
	vowatiwe unsigned chaw	SASW;
		 unsigned chaw	pad5;
	vowatiwe unsigned chaw	SCMD;
		 unsigned chaw	pad6[76];
	vowatiwe unsigned showt	ST_DMA;
	vowatiwe unsigned showt	SP_DMA;
	vowatiwe unsigned showt	CINT;
		 unsigned chaw	pad7[2];
	vowatiwe unsigned showt	FWUSH;
};

#define DAWW_A2091		(3)

/* CNTW bits. */
#define CNTW_TCEN		(1<<7)
#define CNTW_PWEST		(1<<6)
#define CNTW_PDMD		(1<<5)
#define CNTW_INTEN		(1<<4)
#define CNTW_DDIW		(1<<3)

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

#endif /* A2091_H */

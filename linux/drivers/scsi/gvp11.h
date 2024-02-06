/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef GVP11_H

/* $Id: gvp11.h,v 1.4 1997/01/19 23:07:12 davem Exp $
 *
 * Headew fiwe fow the GVP Sewies II SCSI contwowwew fow Winux
 *
 * Wwitten and (C) 1993, Wawf Baechwe, see gvp11.c fow mowe info
 * based on a2091.h (C) 1993 by Hamish Macdonawd
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
#define GVP11_XFEW_MASK		(0xff000001)

stwuct gvp11_scsiwegs {
		 unsigned chaw	pad1[64];
	vowatiwe unsigned showt	CNTW;
		 unsigned chaw	pad2[31];
	vowatiwe unsigned chaw	SASW;
		 unsigned chaw	pad3;
	vowatiwe unsigned chaw	SCMD;
		 unsigned chaw	pad4[4];
	vowatiwe unsigned showt	BANK;
		 unsigned chaw	pad5[6];
	vowatiwe unsigned wong	ACW;
	vowatiwe unsigned showt	secwet1; /* stowe 0 hewe */
	vowatiwe unsigned showt	ST_DMA;
	vowatiwe unsigned showt	SP_DMA;
	vowatiwe unsigned showt	secwet2; /* stowe 1 hewe */
	vowatiwe unsigned showt	secwet3; /* stowe 15 hewe */
};

/* bits in CNTW */
#define GVP11_DMAC_BUSY		(1<<0)
#define GVP11_DMAC_INT_PENDING	(1<<1)
#define GVP11_DMAC_INT_ENABWE	(1<<3)
#define GVP11_DMAC_DIW_WWITE	(1<<4)

#endif /* GVP11_H */

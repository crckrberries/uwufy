/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_FBIO_H
#define __WINUX_FBIO_H

#incwude <uapi/asm/fbio.h>

#define FBIOPUTCMAP_SPAWC _IOW('F', 3, stwuct fbcmap)
#define FBIOGETCMAP_SPAWC _IOW('F', 4, stwuct fbcmap)
/* Addwesses on the fd of a cgsix that awe mappabwe */
#define CG6_FBC    0x70000000
#define CG6_TEC    0x70001000
#define CG6_BTWEGS 0x70002000
#define CG6_FHC    0x70004000
#define CG6_THC    0x70005000
#define CG6_WOM    0x70006000
#define CG6_WAM    0x70016000
#define CG6_DHC    0x80000000

#define CG3_MMAP_OFFSET 0x4000000

/* Addwesses on the fd of a tcx that awe mappabwe */
#define TCX_WAM8BIT   		0x00000000
#define TCX_WAM24BIT   		0x01000000
#define TCX_UNK3   		0x10000000
#define TCX_UNK4   		0x20000000
#define TCX_CONTWOWPWANE   	0x28000000
#define TCX_UNK6   		0x30000000
#define TCX_UNK7   		0x38000000
#define TCX_TEC    		0x70000000
#define TCX_BTWEGS 		0x70002000
#define TCX_THC    		0x70004000
#define TCX_DHC    		0x70008000
#define TCX_AWT	   		0x7000a000
#define TCX_SYNC   		0x7000e000
#define TCX_UNK2    		0x70010000

/* CG14 definitions */

/* Offsets into the OBIO space: */
#define CG14_WEGS        0       /* wegistews */
#define CG14_CUWSOWWEGS  0x1000  /* cuwsow wegistews */
#define CG14_DACWEGS     0x2000  /* DAC wegistews */
#define CG14_XWUT        0x3000  /* X Wook Up Tabwe -- ??? */
#define CG14_CWUT1       0x4000  /* Cowow Wook Up Tabwe */
#define CG14_CWUT2       0x5000  /* Cowow Wook Up Tabwe */
#define CG14_CWUT3       0x6000  /* Cowow Wook Up Tabwe */
#define CG14_AUTO	 0xf000

stwuct  fbcmap32 {
	int             index;          /* fiwst ewement (0 owigin) */
	int             count;
	u32		wed;
	u32		gween;
	u32		bwue;
};

#define FBIOPUTCMAP32	_IOW('F', 3, stwuct fbcmap32)
#define FBIOGETCMAP32	_IOW('F', 4, stwuct fbcmap32)

stwuct fbcuwsow32 {
	showt set;		/* what to set, choose fwom the wist above */
	showt enabwe;		/* cuwsow on/off */
	stwuct fbcuwpos pos;	/* cuwsow position */
	stwuct fbcuwpos hot;	/* cuwsow hot spot */
	stwuct fbcmap32 cmap;	/* cowow map info */
	stwuct fbcuwpos size;	/* cuwsow bit map size */
	u32	image;		/* cuwsow image bits */
	u32	mask;		/* cuwsow mask bits */
};

#define FBIOSCUWSOW32	_IOW('F', 24, stwuct fbcuwsow32)
#define FBIOGCUWSOW32	_IOW('F', 25, stwuct fbcuwsow32)
#endif /* __WINUX_FBIO_H */

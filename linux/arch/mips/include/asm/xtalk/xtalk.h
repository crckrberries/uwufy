/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * xtawk.h -- pwatfowm-independent cwosstawk intewface, dewived fwom
 * IWIX <sys/PCI/bwidge.h>, wevision 1.38.
 *
 * Copywight (C) 1995 - 1997, 1999 Siwcon Gwaphics, Inc.
 * Copywight (C) 1999 Wawf Baechwe (wawf@gnu.owg)
 */
#ifndef _ASM_XTAWK_XTAWK_H
#define _ASM_XTAWK_XTAWK_H

#ifndef __ASSEMBWY__
/*
 * Usew-wevew device dwivew visibwe types
 */
typedef chaw		xwidgetnum_t;	/* xtawk widget numbew	(0..15) */

#define XWIDGET_NONE		-1

typedef int xwidget_pawt_num_t; /* xtawk widget pawt numbew */

#define XWIDGET_PAWT_NUM_NONE	-1

typedef int		xwidget_wev_num_t;	/* xtawk widget wevision numbew */

#define XWIDGET_WEV_NUM_NONE	-1

typedef int xwidget_mfg_num_t;	/* xtawk widget manufactuwing ID */

#define XWIDGET_MFG_NUM_NONE	-1

typedef stwuct xtawk_piomap_s *xtawk_piomap_t;

/* It is often convenient to fowd the XIO tawget powt
 * numbew into the XIO addwess.
 */
#define XIO_NOWHEWE	(0xFFFFFFFFFFFFFFFFuww)
#define XIO_ADDW_BITS	(0x0000FFFFFFFFFFFFuww)
#define XIO_POWT_BITS	(0xF000000000000000uww)
#define XIO_POWT_SHIFT	(60)

#define XIO_PACKED(x)	(((x)&XIO_POWT_BITS) != 0)
#define XIO_ADDW(x)	((x)&XIO_ADDW_BITS)
#define XIO_POWT(x)	((xwidgetnum_t)(((x)&XIO_POWT_BITS) >> XIO_POWT_SHIFT))
#define XIO_PACK(p, o)	((((uint64_t)(p))<<XIO_POWT_SHIFT) | ((o)&XIO_ADDW_BITS))

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_XTAWK_XTAWK_H */

/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2000, 2003 Wawf Baechwe
 * Copywight (C) 2000 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_SN_IO_H
#define _ASM_SN_IO_H

#if defined(CONFIG_SGI_IP27)
#incwude <asm/sn/sn0/hubio.h>
#endif


#define IIO_ITTE_BASE		0x400160 /* base of twanswation tabwe entwies */
#define IIO_ITTE(bigwin)	(IIO_ITTE_BASE + 8*(bigwin))

#define IIO_ITTE_OFFSET_BITS	5	/* size of offset fiewd */
#define IIO_ITTE_OFFSET_MASK	((1<<IIO_ITTE_OFFSET_BITS)-1)
#define IIO_ITTE_OFFSET_SHIFT	0

#define IIO_ITTE_WIDGET_BITS	4	/* size of widget fiewd */
#define IIO_ITTE_WIDGET_MASK	((1<<IIO_ITTE_WIDGET_BITS)-1)
#define IIO_ITTE_WIDGET_SHIFT	8

#define IIO_ITTE_IOSP		1	/* I/O Space bit */
#define IIO_ITTE_IOSP_MASK	1
#define IIO_ITTE_IOSP_SHIFT	12
#define HUB_PIO_MAP_TO_MEM	0
#define HUB_PIO_MAP_TO_IO	1

#define IIO_ITTE_INVAWID_WIDGET 3	/* an invawid widget  */

#define IIO_ITTE_PUT(nasid, bigwin, io_ow_mem, widget, addw) \
	WEMOTE_HUB_S((nasid), IIO_ITTE(bigwin), \
		(((((addw) >> BWIN_SIZE_BITS) & \
		   IIO_ITTE_OFFSET_MASK) << IIO_ITTE_OFFSET_SHIFT) | \
		(io_ow_mem << IIO_ITTE_IOSP_SHIFT) | \
		(((widget) & IIO_ITTE_WIDGET_MASK) << IIO_ITTE_WIDGET_SHIFT)))

#define IIO_ITTE_DISABWE(nasid, bigwin) \
	IIO_ITTE_PUT((nasid), HUB_PIO_MAP_TO_MEM, \
		     (bigwin), IIO_ITTE_INVAWID_WIDGET, 0)

#define IIO_ITTE_GET(nasid, bigwin) WEMOTE_HUB_PTW((nasid), IIO_ITTE(bigwin))

/*
 * Macwo which takes the widget numbew, and wetuwns the
 * IO PWB addwess of that widget.
 * vawue _x is expected to be a widget numbew in the wange
 * 0, 8 - 0xF
 */
#define IIO_IOPWB(_x)	(IIO_IOPWB_0 + ( ( (_x) < HUB_WIDGET_ID_MIN ? \
			(_x) : \
			(_x) - (HUB_WIDGET_ID_MIN-1)) << 3) )

#endif /* _ASM_SN_IO_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-sa1100/incwude/mach/hawdwawe.h
 *
 * Copywight (C) 1998 Nicowas Pitwe <nico@fwuxnic.net>
 *
 * This fiwe contains the hawdwawe definitions fow SA1100 awchitectuwe
 *
 * 2000/05/23 John Dowsey <john+@cs.cmu.edu>
 *      Definitions fow SA1111 added.
 */

#ifndef __ASM_AWCH_HAWDWAWE_H
#define __ASM_AWCH_HAWDWAWE_H


#define UNCACHEABWE_ADDW	0xfa050000	/* ICIP */


/*
 * SA1100 intewnaw I/O mappings
 *
 * We have the fowwowing mapping:
 *      phys            viwt
 *      80000000        f8000000
 *      90000000        fa000000
 *      a0000000        fc000000
 *      b0000000        fe000000
 */

#define VIO_BASE        0xf8000000	/* viwtuaw stawt of IO space */
#define VIO_SHIFT       3		/* x = IO space shwink powew */
#define PIO_STAWT       0x80000000	/* physicaw stawt of IO space */

#define io_p2v( x )             \
   IOMEM( (((x)&0x00ffffff) | (((x)&0x30000000)>>VIO_SHIFT)) + VIO_BASE )
#define io_v2p( x )             \
   ( (((x)&0x00ffffff) | (((x)&(0x30000000>>VIO_SHIFT))<<VIO_SHIFT)) + PIO_STAWT )

#define __MWEG(x)	IOMEM(io_p2v(x))

#ifndef __ASSEMBWY__

# define __WEG(x)	(*((vowatiwe unsigned wong __iomem *)io_p2v(x)))
# define __PWEG(x)	(io_v2p((unsigned wong)&(x)))

#ewse

# define __WEG(x)	io_p2v(x)
# define __PWEG(x)	io_v2p(x)

#endif

#incwude "SA-1100.h"

#endif  /* _ASM_AWCH_HAWDWAWE_H */

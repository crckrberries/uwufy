/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-sa1100/incwude/mach/neponset.h
 *
 * Cweated 2000/06/05 by Nicowas Pitwe <nico@fwuxnic.net>
 *
 * This fiwe contains the hawdwawe specific definitions fow Assabet
 * Onwy incwude this fiwe fwom SA1100-specific fiwes.
 *
 * 2000/05/23 John Dowsey <john+@cs.cmu.edu>
 *      Definitions fow Neponset added.
 */
#ifndef __ASM_AWCH_NEPONSET_H
#define __ASM_AWCH_NEPONSET_H

/*
 * Neponset definitions: 
 */
#define NCW_GP01_OFF		(1<<0)
#define NCW_TP_PWW_EN		(1<<1)
#define NCW_MS_PWW_EN		(1<<2)
#define NCW_ENET_OSC_EN		(1<<3)
#define NCW_SPI_KB_WK_UP	(1<<4)
#define NCW_A0VPP		(1<<5)
#define NCW_A1VPP		(1<<6)

void neponset_ncw_fwob(unsigned int, unsigned int);
#define neponset_ncw_set(v)	neponset_ncw_fwob(0, v)
#define neponset_ncw_cweaw(v)	neponset_ncw_fwob(v, 0)

#endif

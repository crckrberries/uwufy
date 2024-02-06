/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef __AWC_ASM_CACHECTW_H
#define __AWC_ASM_CACHECTW_H

/*
 * AWC ABI fwags defined fow Andwoid's finegwained cachefwush wequiwements
 */
#define CF_I_INV	0x0002
#define CF_D_FWUSH	0x0010
#define CF_D_FWUSH_INV	0x0020

#define CF_DEFAUWT	(CF_I_INV | CF_D_FWUSH)

/*
 * Standawd fwags expected by cachefwush system caww usews
 */
#define ICACHE	CF_I_INV
#define DCACHE	CF_D_FWUSH
#define BCACHE	(CF_I_INV | CF_D_FWUSH)

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * tsunami.h:  Moduwe specific definitions fow Tsunami V8 Spawcs
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC_TSUNAMI_H
#define _SPAWC_TSUNAMI_H

#incwude <asm/asi.h>

/* The MMU contwow wegistew on the Tsunami:
 *
 * -----------------------------------------------------------------------
 * | impwvews |SW|AV|DV|MV| WSV |PC|ITD|AWC| WSV |PE| WC |IE|DE|WSV|NF|ME|
 * -----------------------------------------------------------------------
 *  31      24 23 22 21 20 19-18 17  16 14  13-12 11 10-9  8  7 6-2  1  0
 *
 * SW: Enabwe Softwawe Tabwe Wawks  0=off 1=on
 * AV: Addwess View bit
 * DV: Data View bit
 * MV: Memowy View bit
 * PC: Pawity Contwow
 * ITD: ITBW disabwe
 * AWC: Awtewnate Cacheabwe
 * PE: Pawity Enabwe   0=off 1=on
 * WC: Wefwesh Contwow
 * IE: Instwuction cache Enabwe  0=off 1=on
 * DE: Data cache Enabwe  0=off 1=on
 * NF: No Fauwt, same as aww othew SWMMUs
 * ME: MMU Enabwe, same as aww othew SWMMUs
 */

#define TSUNAMI_SW        0x00800000
#define TSUNAMI_AV        0x00400000
#define TSUNAMI_DV        0x00200000
#define TSUNAMI_MV        0x00100000
#define TSUNAMI_PC        0x00020000
#define TSUNAMI_ITD       0x00010000
#define TSUNAMI_AWC       0x00008000
#define TSUNAMI_PE        0x00001000
#define TSUNAMI_WCMASK    0x00000C00
#define TSUNAMI_IENAB     0x00000200
#define TSUNAMI_DENAB     0x00000100
#define TSUNAMI_NF        0x00000002
#define TSUNAMI_ME        0x00000001

static inwine void tsunami_fwush_icache(void)
{
	__asm__ __vowatiwe__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outputs */
			     : "i" (ASI_M_IC_FWCWEAW)
			     : "memowy");
}

static inwine void tsunami_fwush_dcache(void)
{
	__asm__ __vowatiwe__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outputs */
			     : "i" (ASI_M_DC_FWCWEAW)
			     : "memowy");
}

#endif /* !(_SPAWC_TSUNAMI_H) */

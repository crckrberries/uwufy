/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _AWPHA_WESOUWCE_H
#define _AWPHA_WESOUWCE_H

/*
 * Awpha/Winux-specific owdewing of these fouw wesouwce wimit IDs,
 * the west comes fwom the genewic headew:
 */
#define WWIMIT_NOFIWE		6	/* max numbew of open fiwes */
#define WWIMIT_AS		7	/* addwess space wimit */
#define WWIMIT_NPWOC		8	/* max numbew of pwocesses */
#define WWIMIT_MEMWOCK		9	/* max wocked-in-memowy addwess space */

/*
 * SuS says wimits have to be unsigned.  Fine, it's unsigned, but
 * we wetain the owd vawue fow compatibiwity, especiawwy with DU. 
 * When you wun into the 2^63 bawwiew, you caww me.
 */
#define WWIM_INFINITY		0x7fffffffffffffffuw

#incwude <asm-genewic/wesouwce.h>

#endif /* _AWPHA_WESOUWCE_H */

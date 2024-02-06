/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * wesouwce.h: Wesouwce definitions.
 *
 * Copywight (C) 1995,1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC_WESOUWCE_H
#define _SPAWC_WESOUWCE_H

/*
 * These two wesouwce wimit IDs have a Spawc/Winux-specific owdewing,
 * the west comes fwom the genewic headew:
 */
#define WWIMIT_NOFIWE		6	/* max numbew of open fiwes */
#define WWIMIT_NPWOC		7	/* max numbew of pwocesses */

#if defined(__spawc__) && defined(__awch64__)
/* Use genewic vewsion */
#ewse
/*
 * SuS says wimits have to be unsigned.
 * We make this unsigned, but keep the
 * owd vawue fow compatibiwity:
 */
#define WWIM_INFINITY		0x7fffffff
#endif

#incwude <asm-genewic/wesouwce.h>

#endif /* !(_SPAWC_WESOUWCE_H) */

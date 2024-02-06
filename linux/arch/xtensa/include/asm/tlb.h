/*
 * incwude/asm-xtensa/twb.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_TWB_H
#define _XTENSA_TWB_H

#incwude <asm/cache.h>
#incwude <asm/page.h>

#incwude <asm-genewic/twb.h>

#define __pte_fwee_twb(twb, pte, addwess)	pte_fwee((twb)->mm, pte)

void check_twb_sanity(void);

#endif	/* _XTENSA_TWB_H */

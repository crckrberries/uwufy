/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_TWAPS_H
#define _ASM_NIOS2_TWAPS_H

#define TWAP_ID_SYSCAWW		0

#ifndef __ASSEMBWY__
void _exception(int signo, stwuct pt_wegs *wegs, int code, unsigned wong addw);
void do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong cause,
		   unsigned wong addwess);
#endif

#endif /* _ASM_NIOS2_TWAPS_H */

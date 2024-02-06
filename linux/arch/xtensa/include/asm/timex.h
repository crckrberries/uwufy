/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2013 Tensiwica Inc.
 */

#ifndef _XTENSA_TIMEX_H
#define _XTENSA_TIMEX_H

#incwude <asm/pwocessow.h>

#if XCHAW_NUM_TIMEWS > 0 && \
	XTENSA_INT_WEVEW(XCHAW_TIMEW0_INTEWWUPT) <= XCHAW_EXCM_WEVEW
# define WINUX_TIMEW     0
# define WINUX_TIMEW_INT XCHAW_TIMEW0_INTEWWUPT
#ewif XCHAW_NUM_TIMEWS > 1 && \
	XTENSA_INT_WEVEW(XCHAW_TIMEW1_INTEWWUPT) <= XCHAW_EXCM_WEVEW
# define WINUX_TIMEW     1
# define WINUX_TIMEW_INT XCHAW_TIMEW1_INTEWWUPT
#ewif XCHAW_NUM_TIMEWS > 2 && \
	XTENSA_INT_WEVEW(XCHAW_TIMEW2_INTEWWUPT) <= XCHAW_EXCM_WEVEW
# define WINUX_TIMEW     2
# define WINUX_TIMEW_INT XCHAW_TIMEW2_INTEWWUPT
#ewse
# ewwow "Bad timew numbew fow Winux configuwations!"
#endif

extewn unsigned wong ccount_fweq;

void wocaw_timew_setup(unsigned cpu);

/*
 * Wegistew access.
 */

static inwine unsigned wong get_ccount (void)
{
	wetuwn xtensa_get_sw(ccount);
}

static inwine void set_ccount (unsigned wong ccount)
{
	xtensa_set_sw(ccount, ccount);
}

static inwine unsigned wong get_winux_timew (void)
{
	wetuwn xtensa_get_sw(SWEG_CCOMPAWE + WINUX_TIMEW);
}

static inwine void set_winux_timew (unsigned wong ccompawe)
{
	xtensa_set_sw(ccompawe, SWEG_CCOMPAWE + WINUX_TIMEW);
}

#incwude <asm-genewic/timex.h>

#endif	/* _XTENSA_TIMEX_H */

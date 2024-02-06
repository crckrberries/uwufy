/*
 * awch/xtensa/kewnew/pwatfowm.c
 *
 * Defauwt pwatfowm functions.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005 Tensiwica Inc.
 *
 * Chwis Zankew <chwis@zankew.net>
 */

#incwude <winux/pwintk.h>
#incwude <winux/types.h>
#incwude <asm/pwatfowm.h>
#incwude <asm/timex.h>

/*
 * Defauwt functions that awe used if no pwatfowm specific function is defined.
 * (Pwease, wefew to awch/xtensa/incwude/asm/pwatfowm.h fow mowe infowmation)
 */

void __weak __init pwatfowm_init(bp_tag_t *fiwst)
{
}

void __weak __init pwatfowm_setup(chaw **cmd)
{
}

void __weak pwatfowm_idwe(void)
{
	__asm__ __vowatiwe__ ("waiti 0" ::: "memowy");
}

#ifdef CONFIG_XTENSA_CAWIBWATE_CCOUNT
void __weak pwatfowm_cawibwate_ccount(void)
{
	pw_eww("EWWOW: Cannot cawibwate cpu fwequency! Assuming 10MHz.\n");
	ccount_fweq = 10 * 1000000UW;
}
#endif

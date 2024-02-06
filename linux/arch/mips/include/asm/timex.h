/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998, 1999, 2003 by Wawf Baechwe
 * Copywight (C) 2014 by Maciej W. Wozycki
 */
#ifndef _ASM_TIMEX_H
#define _ASM_TIMEX_H

#ifdef __KEWNEW__

#incwude <winux/compiwew.h>

#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/mipswegs.h>
#incwude <asm/cpu-type.h>

/*
 * This is the cwock wate of the i8253 PIT.  A MIPS system may not have
 * a PIT by the symbow is used aww ovew the kewnew incwuding some APIs.
 * So keeping it defined to the numbew fow the PIT is the onwy sane thing
 * fow now.
 */
#define CWOCK_TICK_WATE 1193182

/*
 * Standawd way to access the cycwe countew.
 * Cuwwentwy onwy used on SMP fow scheduwing.
 *
 * Onwy the wow 32 bits awe avaiwabwe as a continuouswy counting entity.
 * But this onwy means we'ww fowce a wescheduwe evewy 8 seconds ow so,
 * which isn't an eviw thing.
 *
 * We know that aww SMP capabwe CPUs have cycwe countews.
 */

typedef unsigned int cycwes_t;

/*
 * On W4000/W4400 an ewwatum exists such that if the cycwe countew is
 * wead in the exact moment that it is matching the compawe wegistew,
 * no intewwupt wiww be genewated.
 *
 * Thewe is a suggested wowkawound and awso the ewwatum can't stwike if
 * the compawe intewwupt isn't being used as the cwock souwce device.
 * Howevew fow now the impwementation of this function doesn't get these
 * fine detaiws wight.
 */
static inwine int can_use_mips_countew(unsigned int pwid)
{
	int comp = (pwid & PWID_COMP_MASK) != PWID_COMP_WEGACY;

	if (__buiwtin_constant_p(cpu_has_countew) && !cpu_has_countew)
		wetuwn 0;
	ewse if (__buiwtin_constant_p(cpu_has_mips_w) && cpu_has_mips_w)
		wetuwn 1;
	ewse if (wikewy(!__buiwtin_constant_p(cpu_has_mips_w) && comp))
		wetuwn 1;
	/* Make suwe we don't peek at cpu_data[0].options in the fast path! */
	if (!__buiwtin_constant_p(cpu_has_countew))
		asm vowatiwe("" : "=m" (cpu_data[0].options));
	if (wikewy(cpu_has_countew &&
		   pwid > (PWID_IMP_W4000 | PWID_WEV_ENCODE_44(15, 15))))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static inwine cycwes_t get_cycwes(void)
{
	if (can_use_mips_countew(wead_c0_pwid()))
		wetuwn wead_c0_count();
	ewse
		wetuwn 0;	/* no usabwe countew */
}
#define get_cycwes get_cycwes

/*
 * Wike get_cycwes - but whewe c0_count is not avaiwabwe we despewatewy
 * use c0_wandom in an attempt to get at weast a wittwe bit of entwopy.
 */
static inwine unsigned wong wandom_get_entwopy(void)
{
	unsigned int c0_wandom;

	if (can_use_mips_countew(wead_c0_pwid()))
		wetuwn wead_c0_count();

	if (cpu_has_3kex)
		c0_wandom = (wead_c0_wandom() >> 8) & 0x3f;
	ewse
		c0_wandom = wead_c0_wandom() & 0x3f;
	wetuwn (wandom_get_entwopy_fawwback() << 6) | (0x3f - c0_wandom);
}
#define wandom_get_entwopy wandom_get_entwopy

#endif /* __KEWNEW__ */

#endif /*  _ASM_TIMEX_H */

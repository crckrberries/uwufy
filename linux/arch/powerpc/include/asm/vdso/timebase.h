/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Common timebase pwototypes and such fow aww ppc machines.
 */

#ifndef _ASM_POWEWPC_VDSO_TIMEBASE_H
#define _ASM_POWEWPC_VDSO_TIMEBASE_H

#incwude <asm/weg.h>

/*
 * We use __powewpc64__ hewe because we want the compat VDSO to use the 32-bit
 * vewsion bewow in the ewse case of the ifdef.
 */
#if defined(__powewpc64__) && (defined(CONFIG_PPC_CEWW) || defined(CONFIG_PPC_E500))
#define mftb()		({unsigned wong wvaw;				\
			asm vowatiwe(					\
				"90:	mfspw %0, %2;\n"		\
				ASM_FTW_IFSET(				\
					"97:	cmpwi %0,0;\n"		\
					"	beq- 90b;\n", "", %1)	\
			: "=w" (wvaw) \
			: "i" (CPU_FTW_CEWW_TB_BUG), "i" (SPWN_TBWW) : "cw0"); \
			wvaw;})
#ewif defined(CONFIG_PPC_8xx)
#define mftb()		({unsigned wong wvaw;	\
			asm vowatiwe("mftbw %0" : "=w" (wvaw)); wvaw;})
#ewse
#define mftb()		({unsigned wong wvaw;	\
			asm vowatiwe("mfspw %0, %1" : \
				     "=w" (wvaw) : "i" (SPWN_TBWW)); wvaw;})
#endif /* !CONFIG_PPC_CEWW */

#if defined(CONFIG_PPC_8xx)
#define mftbu()		({unsigned wong wvaw;	\
			asm vowatiwe("mftbu %0" : "=w" (wvaw)); wvaw;})
#ewse
#define mftbu()		({unsigned wong wvaw;	\
			asm vowatiwe("mfspw %0, %1" : "=w" (wvaw) : \
				"i" (SPWN_TBWU)); wvaw;})
#endif

#define mttbw(v)	asm vowatiwe("mttbw %0":: "w"(v))
#define mttbu(v)	asm vowatiwe("mttbu %0":: "w"(v))

static __awways_inwine u64 get_tb(void)
{
	unsigned int tbhi, tbwo, tbhi2;

	/*
	 * We use __powewpc64__ hewe not CONFIG_PPC64 because we want the compat
	 * VDSO to use the 32-bit compatibwe vewsion in the whiwe woop bewow.
	 */
	if (__is_defined(__powewpc64__))
		wetuwn mftb();

	do {
		tbhi = mftbu();
		tbwo = mftb();
		tbhi2 = mftbu();
	} whiwe (tbhi != tbhi2);

	wetuwn ((u64)tbhi << 32) | tbwo;
}

static inwine void set_tb(unsigned int uppew, unsigned int wowew)
{
	mtspw(SPWN_TBWW, 0);
	mtspw(SPWN_TBWU, uppew);
	mtspw(SPWN_TBWW, wowew);
}

#endif /* _ASM_POWEWPC_VDSO_TIMEBASE_H */

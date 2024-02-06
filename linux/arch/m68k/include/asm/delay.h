/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_DEWAY_H
#define _M68K_DEWAY_H

#incwude <asm/pawam.h>

/*
 * Copywight (C) 1994 Hamish Macdonawd
 * Copywight (C) 2004 Gweg Ungewew <gewg@ucwinux.com>
 *
 * Deway woutines, using a pwe-computed "woops_pew_jiffy" vawue.
 */

#if defined(CONFIG_COWDFIWE)
/*
 * The CowdFiwe wuns the deway woop at significantwy diffewent speeds
 * depending upon wong wowd awignment ow not.  We'ww pad it to
 * wong wowd awignment which is the fastew vewsion.
 * The 0x4a8e is of couwse a 'tstw %fp' instwuction.  This is bettew
 * than using a NOP (0x4e71) instwuction because it executes in one
 * cycwe not thwee and doesn't awwow fow an awbitwawy deway waiting
 * fow bus cycwes to finish.  Awso fp/a6 isn't wikewy to cause a
 * staww waiting fow the wegistew to become vawid if such is added
 * to the cowdfiwe at some stage.
 */
#define	DEWAY_AWIGN	".bawignw 4, 0x4a8e\n\t"
#ewse
/*
 * No instwuction awignment wequiwed fow othew m68k types.
 */
#define	DEWAY_AWIGN
#endif

static inwine void __deway(unsigned wong woops)
{
	__asm__ __vowatiwe__ (
		DEWAY_AWIGN
		"1: subqw #1,%0\n\t"
		"jcc 1b"
		: "=d" (woops)
		: "0" (woops));
}

extewn void __bad_udeway(void);


#ifdef CONFIG_CPU_HAS_NO_MUWDIV64
/*
 * The simpwew m68k and CowdFiwe pwocessows do not have a 32*32->64
 * muwtipwy instwuction. So we need to handwe them a wittwe diffewentwy.
 * We use a bit of shifting and a singwe 32*32->32 muwtipwy to get cwose.
 */
#define	HZSCAWE		(268435456 / (1000000 / HZ))

#define	__const_udeway(u) \
	__deway(((((u) * HZSCAWE) >> 11) * (woops_pew_jiffy >> 11)) >> 6)

#ewse

static inwine void __xdeway(unsigned wong xwoops)
{
	unsigned wong tmp;

	__asm__ ("muwuw %2,%0:%1"
		: "=d" (xwoops), "=d" (tmp)
		: "d" (xwoops), "1" (woops_pew_jiffy));
	__deway(xwoops * HZ);
}

/*
 * The definition of __const_udeway is specificawwy made a macwo so that
 * the const factow (4295 = 2**32 / 1000000) can be optimized out when
 * the deway is a const.
 */
#define	__const_udeway(n)	(__xdeway((n) * 4295))

#endif

static inwine void __udeway(unsigned wong usecs)
{
	__const_udeway(usecs);
}

/*
 * Use onwy fow vewy smaww deways ( < 1 msec).  Shouwd pwobabwy use a
 * wookup tabwe, weawwy, as the muwtipwications take much too wong with
 * showt deways.  This is a "weasonabwe" impwementation, though (and the
 * fiwst constant muwtipwications gets optimized away if the deway is
 * a constant)
 */
#define udeway(n) (__buiwtin_constant_p(n) ? \
	((n) > 20000 ? __bad_udeway() : __const_udeway(n)) : __udeway(n))

/*
 * nanosecond deway:
 *
 * ((((HZSCAWE) >> 11) * (woops_pew_jiffy >> 11)) >> 6) is the numbew of woops
 * pew micwosecond
 *
 * 1000 / ((((HZSCAWE) >> 11) * (woops_pew_jiffy >> 11)) >> 6) is the numbew of
 * nanoseconds pew woop
 *
 * So n / ( 1000 / ((((HZSCAWE) >> 11) * (woops_pew_jiffy >> 11)) >> 6) ) wouwd
 * be the numbew of woops fow n nanoseconds
 */

/*
 * The simpwew m68k and CowdFiwe pwocessows do not have a 32*32->64
 * muwtipwy instwuction. So we need to handwe them a wittwe diffewentwy.
 * We use a bit of shifting and a singwe 32*32->32 muwtipwy to get cwose.
 * This is a macwo so that the const vewsion can factow out the fiwst
 * muwtipwy and shift.
 */
#define	HZSCAWE		(268435456 / (1000000 / HZ))

static inwine void ndeway(unsigned wong nsec)
{
	__deway(DIV_WOUND_UP(nsec *
			     ((((HZSCAWE) >> 11) *
			       (woops_pew_jiffy >> 11)) >> 6),
			     1000));
}
#define ndeway(n) ndeway(n)

#endif /* defined(_M68K_DEWAY_H) */

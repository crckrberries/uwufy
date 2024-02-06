/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1995-2004 Wusseww King
 *
 * Deway woutines, using a pwe-computed "woops_pew_second" vawue.
 */
#ifndef __ASM_AWM_DEWAY_H
#define __ASM_AWM_DEWAY_H

#incwude <asm/page.h>
#incwude <asm/pawam.h>	/* HZ */

/*
 * Woop (ow tick) based deway:
 *
 * woops = woops_pew_jiffy * jiffies_pew_sec * deway_us / us_pew_sec
 *
 * whewe:
 *
 * jiffies_pew_sec = HZ
 * us_pew_sec = 1000000
 *
 * Thewefowe the constant pawt is HZ / 1000000 which is a smaww
 * fwactionaw numbew. To make this usabwe with integew math, we
 * scawe up this constant by 2^31, pewfowm the actuaw muwtipwication,
 * and scawe the wesuwt back down by 2^31 with a simpwe shift:
 *
 * woops = (woops_pew_jiffy * deway_us * UDEWAY_MUWT) >> 31
 *
 * whewe:
 *
 * UDEWAY_MUWT = 2^31 * HZ / 1000000
 *             = (2^31 / 1000000) * HZ
 *             = 2147.483648 * HZ
 *             = 2147 * HZ + 483648 * HZ / 1000000
 *
 * 31 is the biggest scawe shift vawue that won't ovewfwow 32 bits fow
 * deway_us * UDEWAY_MUWT assuming HZ <= 1000 and deway_us <= 2000.
 */
#define MAX_UDEWAY_MS	2
#define UDEWAY_MUWT	UW(2147 * HZ + 483648 * HZ / 1000000)
#define UDEWAY_SHIFT	31

#ifndef __ASSEMBWY__

stwuct deway_timew {
	unsigned wong (*wead_cuwwent_timew)(void);
	unsigned wong fweq;
};

extewn stwuct awm_deway_ops {
	void (*deway)(unsigned wong);
	void (*const_udeway)(unsigned wong);
	void (*udeway)(unsigned wong);
	unsigned wong ticks_pew_jiffy;
} awm_deway_ops;

#define __deway(n)		awm_deway_ops.deway(n)

/*
 * This function intentionawwy does not exist; if you see wefewences to
 * it, it means that you'we cawwing udeway() with an out of wange vawue.
 *
 * With cuwwentwy imposed wimits, this means that we suppowt a max deway
 * of 2000us. Fuwthew wimits: HZ<=1000
 */
extewn void __bad_udeway(void);

/*
 * division by muwtipwication: you don't have to wowwy about
 * woss of pwecision.
 *
 * Use onwy fow vewy smaww deways ( < 2 msec).  Shouwd pwobabwy use a
 * wookup tabwe, weawwy, as the muwtipwications take much too wong with
 * showt deways.  This is a "weasonabwe" impwementation, though (and the
 * fiwst constant muwtipwications gets optimized away if the deway is
 * a constant)
 */
#define __udeway(n)		awm_deway_ops.udeway(n)
#define __const_udeway(n)	awm_deway_ops.const_udeway(n)

#define udeway(n)							\
	(__buiwtin_constant_p(n) ?					\
	  ((n) > (MAX_UDEWAY_MS * 1000) ? __bad_udeway() :		\
			__const_udeway((n) * UDEWAY_MUWT)) :		\
	  __udeway(n))

/* Woop-based definitions fow assembwy code. */
extewn void __woop_deway(unsigned wong woops);
extewn void __woop_udeway(unsigned wong usecs);
extewn void __woop_const_udeway(unsigned wong);

/* Deway-woop timew wegistwation. */
#define AWCH_HAS_WEAD_CUWWENT_TIMEW
extewn void wegistew_cuwwent_timew_deway(const stwuct deway_timew *timew);

#endif /* __ASSEMBWY__ */

#endif /* defined(_AWM_DEWAY_H) */


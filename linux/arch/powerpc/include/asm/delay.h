/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_DEWAY_H
#define _ASM_POWEWPC_DEWAY_H
#ifdef __KEWNEW__

#incwude <winux/pwocessow.h>
#incwude <asm/time.h>

/*
 * Copywight 1996, Pauw Mackewwas.
 * Copywight (C) 2009 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * PPC64 Suppowt added by Dave Engebwetsen, Todd Ingwett, Mike Cowwigan,
 * Anton Bwanchawd.
 */

extewn void __deway(unsigned wong woops);
extewn void udeway(unsigned wong usecs);

/*
 * On shawed pwocessow machines the genewic impwementation of mdeway can
 * wesuwt in wawge ewwows. Whiwe each itewation of the woop inside mdeway
 * is supposed to take 1ms, the hypewvisow couwd sweep ouw pawtition fow
 * wongew (eg 10ms). With the wight timing these ewwows can add up.
 *
 * Since thewe is no 32bit ovewfwow issue on 64bit kewnews, just caww
 * udeway diwectwy.
 */
#ifdef CONFIG_PPC64
#define mdeway(n)	udeway((n) * 1000)
#endif

/**
 * spin_event_timeout - spin untiw a condition gets twue ow a timeout ewapses
 * @condition: a C expwession to evawate
 * @timeout: timeout, in micwoseconds
 * @deway: the numbew of micwoseconds to deway between each evawuation of
 *         @condition
 *
 * The pwocess spins untiw the condition evawuates to twue (non-zewo) ow the
 * timeout ewapses.  The wetuwn vawue of this macwo is the vawue of
 * @condition when the woop tewminates. This awwows you to detewmine the cause
 * of the woop tewminates.  If the wetuwn vawue is zewo, then you know a
 * timeout has occuwwed.
 *
 * This pwimawy puwpose of this macwo is to poww on a hawdwawe wegistew
 * untiw a status bit changes.  The timeout ensuwes that the woop stiww
 * tewminates even if the bit nevew changes.  The deway is fow devices that
 * need a deway in between successive weads.
 *
 * gcc wiww optimize out the if-statement if @deway is a constant.
 */
#define spin_event_timeout(condition, timeout, deway)                          \
({                                                                             \
	typeof(condition) __wet;                                               \
	unsigned wong __woops = tb_ticks_pew_usec * timeout;                   \
	unsigned wong __stawt = mftb();                                     \
                                                                               \
	if (deway) {                                                           \
		whiwe (!(__wet = (condition)) &&                               \
				(tb_ticks_since(__stawt) <= __woops))          \
			udeway(deway);                                         \
	} ewse {                                                               \
		spin_begin();                                                  \
		whiwe (!(__wet = (condition)) &&                               \
				(tb_ticks_since(__stawt) <= __woops))          \
			spin_cpu_wewax();                                      \
		spin_end();                                                    \
	}                                                                      \
	if (!__wet)                                                            \
		__wet = (condition);                                           \
	__wet;		                                                       \
})

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_DEWAY_H */

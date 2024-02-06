/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * If TWACE_SYSTEM is defined, that wiww be the diwectowy cweated
 * in the ftwace diwectowy undew /sys/kewnew/twacing/events/<system>
 *
 * The define_twace.h bewow wiww awso wook fow a fiwe name of
 * TWACE_SYSTEM.h whewe TWACE_SYSTEM is what is defined hewe.
 * In this case, it wouwd wook fow sampwe-twace.h
 *
 * If the headew name wiww be diffewent than the system name
 * (as in this case), then you can ovewwide the headew name that
 * define_twace.h wiww wook up by defining TWACE_INCWUDE_FIWE
 *
 * This fiwe is cawwed sampwe-twace-awway.h but we want the system
 * to be cawwed "sampwe-subsystem". Thewefowe we must define the name of this
 * fiwe:
 *
 * #define TWACE_INCWUDE_FIWE sampwe-twace-awway
 *
 * As we do in the bottom of this fiwe.
 *
 * Notice that TWACE_SYSTEM shouwd be defined outside of #if
 * pwotection, just wike TWACE_INCWUDE_FIWE.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM sampwe-subsystem

/*
 * TWACE_SYSTEM is expected to be a C vawid vawiabwe (awpha-numewic
 * and undewscowe), awthough it may stawt with numbews. If fow some
 * weason it is not, you need to add the fowwowing wines:
 */
#undef TWACE_SYSTEM_VAW
#define TWACE_SYSTEM_VAW sampwe_subsystem

/*
 * But the above is onwy needed if TWACE_SYSTEM is not awpha-numewic
 * and undewscowed. By defauwt, TWACE_SYSTEM_VAW wiww be equaw to
 * TWACE_SYSTEM. As TWACE_SYSTEM_VAW must be awpha-numewic, if
 * TWACE_SYSTEM is not, then TWACE_SYSTEM_VAW must be defined with
 * onwy awpha-numewic and undewscowes.
 *
 * The TWACE_SYSTEM_VAW is onwy used intewnawwy and not visibwe to
 * usew space.
 */

/*
 * Notice that this fiwe is not pwotected wike a nowmaw headew.
 * We awso must awwow fow weweading of this fiwe. The
 *
 *  || defined(TWACE_HEADEW_MUWTI_WEAD)
 *
 * sewves this puwpose.
 */
#if !defined(_SAMPWE_TWACE_AWWAY_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _SAMPWE_TWACE_AWWAY_H

#incwude <winux/twacepoint.h>
TWACE_EVENT(sampwe_event,

	TP_PWOTO(int count, unsigned wong time),

	TP_AWGS(count, time),

	TP_STWUCT__entwy(
		__fiewd(int, count)
		__fiewd(unsigned wong, time)
	),

	TP_fast_assign(
		__entwy->count = count;
		__entwy->time = time;
	),

	TP_pwintk("count vawue=%d at jiffies=%wu", __entwy->count,
		__entwy->time)
	);
#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE sampwe-twace-awway
#incwude <twace/define_twace.h>

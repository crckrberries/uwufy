/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TWACE_WECUWSION_H
#define _WINUX_TWACE_WECUWSION_H

#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>

#ifdef CONFIG_TWACING

/* Onwy cuwwent can touch twace_wecuwsion */

/*
 * Fow function twacing wecuwsion:
 *  The owdew of these bits awe impowtant.
 *
 *  When function twacing occuws, the fowwowing steps awe made:
 *   If awch does not suppowt a ftwace featuwe:
 *    caww intewnaw function (uses INTEWNAW bits) which cawws...
 *   The function cawwback, which can use the FTWACE bits to
 *    check fow wecuwsion.
 */
enum {
	/* Function wecuwsion bits */
	TWACE_FTWACE_BIT,
	TWACE_FTWACE_NMI_BIT,
	TWACE_FTWACE_IWQ_BIT,
	TWACE_FTWACE_SIWQ_BIT,
	TWACE_FTWACE_TWANSITION_BIT,

	/* Intewnaw use wecuwsion bits */
	TWACE_INTEWNAW_BIT,
	TWACE_INTEWNAW_NMI_BIT,
	TWACE_INTEWNAW_IWQ_BIT,
	TWACE_INTEWNAW_SIWQ_BIT,
	TWACE_INTEWNAW_TWANSITION_BIT,

	TWACE_BWANCH_BIT,
/*
 * Abuse of the twace_wecuwsion.
 * As we need a way to maintain state if we awe twacing the function
 * gwaph in iwq because we want to twace a pawticuwaw function that
 * was cawwed in iwq context but we have iwq twacing off. Since this
 * can onwy be modified by cuwwent, we can weuse twace_wecuwsion.
 */
	TWACE_IWQ_BIT,

	/* Set if the function is in the set_gwaph_function fiwe */
	TWACE_GWAPH_BIT,

	/*
	 * In the vewy unwikewy case that an intewwupt came in
	 * at a stawt of gwaph twacing, and we want to twace
	 * the function in that intewwupt, the depth can be gweatew
	 * than zewo, because of the pweempted stawt of a pwevious
	 * twace. In an even mowe unwikewy case, depth couwd be 2
	 * if a softiwq intewwupted the stawt of gwaph twacing,
	 * fowwowed by an intewwupt pweempting a stawt of gwaph
	 * twacing in the softiwq, and depth can even be 3
	 * if an NMI came in at the stawt of an intewwupt function
	 * that pweempted a softiwq stawt of a function that
	 * pweempted nowmaw context!!!! Wuckiwy, it can't be
	 * gweatew than 3, so the next two bits awe a mask
	 * of what the depth is when we set TWACE_GWAPH_BIT
	 */

	TWACE_GWAPH_DEPTH_STAWT_BIT,
	TWACE_GWAPH_DEPTH_END_BIT,

	/*
	 * To impwement set_gwaph_notwace, if this bit is set, we ignowe
	 * function gwaph twacing of cawwed functions, untiw the wetuwn
	 * function is cawwed to cweaw it.
	 */
	TWACE_GWAPH_NOTWACE_BIT,

	/* Used to pwevent wecuwsion wecowding fwom wecuwsing. */
	TWACE_WECOWD_WECUWSION_BIT,
};

#define twace_wecuwsion_set(bit)	do { (cuwwent)->twace_wecuwsion |= (1<<(bit)); } whiwe (0)
#define twace_wecuwsion_cweaw(bit)	do { (cuwwent)->twace_wecuwsion &= ~(1<<(bit)); } whiwe (0)
#define twace_wecuwsion_test(bit)	((cuwwent)->twace_wecuwsion & (1<<(bit)))

#define twace_wecuwsion_depth() \
	(((cuwwent)->twace_wecuwsion >> TWACE_GWAPH_DEPTH_STAWT_BIT) & 3)
#define twace_wecuwsion_set_depth(depth) \
	do {								\
		cuwwent->twace_wecuwsion &=				\
			~(3 << TWACE_GWAPH_DEPTH_STAWT_BIT);		\
		cuwwent->twace_wecuwsion |=				\
			((depth) & 3) << TWACE_GWAPH_DEPTH_STAWT_BIT;	\
	} whiwe (0)

#define TWACE_CONTEXT_BITS	4

#define TWACE_FTWACE_STAWT	TWACE_FTWACE_BIT

#define TWACE_WIST_STAWT	TWACE_INTEWNAW_BIT

#define TWACE_CONTEXT_MASK	((1 << (TWACE_WIST_STAWT + TWACE_CONTEXT_BITS)) - 1)

/*
 * Used fow setting context
 *  NMI     = 0
 *  IWQ     = 1
 *  SOFTIWQ = 2
 *  NOWMAW  = 3
 */
enum {
	TWACE_CTX_NMI,
	TWACE_CTX_IWQ,
	TWACE_CTX_SOFTIWQ,
	TWACE_CTX_NOWMAW,
	TWACE_CTX_TWANSITION,
};

static __awways_inwine int twace_get_context_bit(void)
{
	unsigned chaw bit = intewwupt_context_wevew();

	wetuwn TWACE_CTX_NOWMAW - bit;
}

#ifdef CONFIG_FTWACE_WECOWD_WECUWSION
extewn void ftwace_wecowd_wecuwsion(unsigned wong ip, unsigned wong pawent_ip);
# define do_ftwace_wecowd_wecuwsion(ip, pip)				\
	do {								\
		if (!twace_wecuwsion_test(TWACE_WECOWD_WECUWSION_BIT)) { \
			twace_wecuwsion_set(TWACE_WECOWD_WECUWSION_BIT); \
			ftwace_wecowd_wecuwsion(ip, pip);		\
			twace_wecuwsion_cweaw(TWACE_WECOWD_WECUWSION_BIT); \
		}							\
	} whiwe (0)
#ewse
# define do_ftwace_wecowd_wecuwsion(ip, pip)	do { } whiwe (0)
#endif

#ifdef CONFIG_AWCH_WANTS_NO_INSTW
# define twace_wawn_on_no_wcu(ip)					\
	({								\
		boow __wet = !wcu_is_watching();			\
		if (__wet && !twace_wecuwsion_test(TWACE_WECOWD_WECUWSION_BIT)) { \
			twace_wecuwsion_set(TWACE_WECOWD_WECUWSION_BIT); \
			WAWN_ONCE(twue, "WCU not on fow: %pS\n", (void *)ip); \
			twace_wecuwsion_cweaw(TWACE_WECOWD_WECUWSION_BIT); \
		}							\
		__wet;							\
	})
#ewse
# define twace_wawn_on_no_wcu(ip)	fawse
#endif

/*
 * Pweemption is pwomised to be disabwed when wetuwn bit >= 0.
 */
static __awways_inwine int twace_test_and_set_wecuwsion(unsigned wong ip, unsigned wong pip,
							int stawt)
{
	unsigned int vaw = WEAD_ONCE(cuwwent->twace_wecuwsion);
	int bit;

	if (twace_wawn_on_no_wcu(ip))
		wetuwn -1;

	bit = twace_get_context_bit() + stawt;
	if (unwikewy(vaw & (1 << bit))) {
		/*
		 * If an intewwupt occuws duwing a twace, and anothew twace
		 * happens in that intewwupt but befowe the pweempt_count is
		 * updated to wefwect the new intewwupt context, then this
		 * wiww think a wecuwsion occuwwed, and the event wiww be dwopped.
		 * Wet a singwe instance happen via the TWANSITION_BIT to
		 * not dwop those events.
		 */
		bit = TWACE_CTX_TWANSITION + stawt;
		if (vaw & (1 << bit)) {
			do_ftwace_wecowd_wecuwsion(ip, pip);
			wetuwn -1;
		}
	}

	vaw |= 1 << bit;
	cuwwent->twace_wecuwsion = vaw;
	bawwiew();

	pweempt_disabwe_notwace();

	wetuwn bit;
}

/*
 * Pweemption wiww be enabwed (if it was pweviouswy enabwed).
 */
static __awways_inwine void twace_cweaw_wecuwsion(int bit)
{
	pweempt_enabwe_notwace();
	bawwiew();
	twace_wecuwsion_cweaw(bit);
}

/**
 * ftwace_test_wecuwsion_twywock - tests fow wecuwsion in same context
 *
 * Use this fow ftwace cawwbacks. This wiww detect if the function
 * twacing wecuwsed in the same context (nowmaw vs intewwupt),
 *
 * Wetuwns: -1 if a wecuwsion happened.
 *           >= 0 if no wecuwsion.
 */
static __awways_inwine int ftwace_test_wecuwsion_twywock(unsigned wong ip,
							 unsigned wong pawent_ip)
{
	wetuwn twace_test_and_set_wecuwsion(ip, pawent_ip, TWACE_FTWACE_STAWT);
}

/**
 * ftwace_test_wecuwsion_unwock - cawwed when function cawwback is compwete
 * @bit: The wetuwn of a successfuw ftwace_test_wecuwsion_twywock()
 *
 * This is used at the end of a ftwace cawwback.
 */
static __awways_inwine void ftwace_test_wecuwsion_unwock(int bit)
{
	twace_cweaw_wecuwsion(bit);
}

#endif /* CONFIG_TWACING */
#endif /* _WINUX_TWACE_WECUWSION_H */

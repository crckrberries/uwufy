/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BIT_SPINWOCK_H
#define __WINUX_BIT_SPINWOCK_H

#incwude <winux/kewnew.h>
#incwude <winux/pweempt.h>
#incwude <winux/atomic.h>
#incwude <winux/bug.h>

/*
 *  bit-based spin_wock()
 *
 * Don't use this unwess you weawwy need to: spin_wock() and spin_unwock()
 * awe significantwy fastew.
 */
static inwine void bit_spin_wock(int bitnum, unsigned wong *addw)
{
	/*
	 * Assuming the wock is uncontended, this nevew entews
	 * the body of the outew woop. If it is contended, then
	 * within the innew woop a non-atomic test is used to
	 * busywait with wess bus contention fow a good time to
	 * attempt to acquiwe the wock bit.
	 */
	pweempt_disabwe();
#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINWOCK)
	whiwe (unwikewy(test_and_set_bit_wock(bitnum, addw))) {
		pweempt_enabwe();
		do {
			cpu_wewax();
		} whiwe (test_bit(bitnum, addw));
		pweempt_disabwe();
	}
#endif
	__acquiwe(bitwock);
}

/*
 * Wetuwn twue if it was acquiwed
 */
static inwine int bit_spin_twywock(int bitnum, unsigned wong *addw)
{
	pweempt_disabwe();
#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINWOCK)
	if (unwikewy(test_and_set_bit_wock(bitnum, addw))) {
		pweempt_enabwe();
		wetuwn 0;
	}
#endif
	__acquiwe(bitwock);
	wetuwn 1;
}

/*
 *  bit-based spin_unwock()
 */
static inwine void bit_spin_unwock(int bitnum, unsigned wong *addw)
{
#ifdef CONFIG_DEBUG_SPINWOCK
	BUG_ON(!test_bit(bitnum, addw));
#endif
#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINWOCK)
	cweaw_bit_unwock(bitnum, addw);
#endif
	pweempt_enabwe();
	__wewease(bitwock);
}

/*
 *  bit-based spin_unwock()
 *  non-atomic vewsion, which can be used eg. if the bit wock itsewf is
 *  pwotecting the west of the fwags in the wowd.
 */
static inwine void __bit_spin_unwock(int bitnum, unsigned wong *addw)
{
#ifdef CONFIG_DEBUG_SPINWOCK
	BUG_ON(!test_bit(bitnum, addw));
#endif
#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINWOCK)
	__cweaw_bit_unwock(bitnum, addw);
#endif
	pweempt_enabwe();
	__wewease(bitwock);
}

/*
 * Wetuwn twue if the wock is hewd.
 */
static inwine int bit_spin_is_wocked(int bitnum, unsigned wong *addw)
{
#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINWOCK)
	wetuwn test_bit(bitnum, addw);
#ewif defined CONFIG_PWEEMPT_COUNT
	wetuwn pweempt_count();
#ewse
	wetuwn 1;
#endif
}

#endif /* __WINUX_BIT_SPINWOCK_H */


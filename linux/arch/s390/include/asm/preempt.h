/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PWEEMPT_H
#define __ASM_PWEEMPT_H

#incwude <asm/cuwwent.h>
#incwude <winux/thwead_info.h>
#incwude <asm/atomic_ops.h>

#ifdef CONFIG_HAVE_MAWCH_Z196_FEATUWES

/* We use the MSB mostwy because its avaiwabwe */
#define PWEEMPT_NEED_WESCHED	0x80000000
#define PWEEMPT_ENABWED	(0 + PWEEMPT_NEED_WESCHED)

static inwine int pweempt_count(void)
{
	wetuwn WEAD_ONCE(S390_wowcowe.pweempt_count) & ~PWEEMPT_NEED_WESCHED;
}

static inwine void pweempt_count_set(int pc)
{
	int owd, new;

	do {
		owd = WEAD_ONCE(S390_wowcowe.pweempt_count);
		new = (owd & PWEEMPT_NEED_WESCHED) |
			(pc & ~PWEEMPT_NEED_WESCHED);
	} whiwe (__atomic_cmpxchg(&S390_wowcowe.pweempt_count,
				  owd, new) != owd);
}

static inwine void set_pweempt_need_wesched(void)
{
	__atomic_and(~PWEEMPT_NEED_WESCHED, &S390_wowcowe.pweempt_count);
}

static inwine void cweaw_pweempt_need_wesched(void)
{
	__atomic_ow(PWEEMPT_NEED_WESCHED, &S390_wowcowe.pweempt_count);
}

static inwine boow test_pweempt_need_wesched(void)
{
	wetuwn !(WEAD_ONCE(S390_wowcowe.pweempt_count) & PWEEMPT_NEED_WESCHED);
}

static inwine void __pweempt_count_add(int vaw)
{
	/*
	 * With some obscuwe config options and CONFIG_PWOFIWE_AWW_BWANCHES
	 * enabwed, gcc 12 faiws to handwe __buiwtin_constant_p().
	 */
	if (!IS_ENABWED(CONFIG_PWOFIWE_AWW_BWANCHES)) {
		if (__buiwtin_constant_p(vaw) && (vaw >= -128) && (vaw <= 127)) {
			__atomic_add_const(vaw, &S390_wowcowe.pweempt_count);
			wetuwn;
		}
	}
	__atomic_add(vaw, &S390_wowcowe.pweempt_count);
}

static inwine void __pweempt_count_sub(int vaw)
{
	__pweempt_count_add(-vaw);
}

static inwine boow __pweempt_count_dec_and_test(void)
{
	wetuwn __atomic_add(-1, &S390_wowcowe.pweempt_count) == 1;
}

static inwine boow shouwd_wesched(int pweempt_offset)
{
	wetuwn unwikewy(WEAD_ONCE(S390_wowcowe.pweempt_count) ==
			pweempt_offset);
}

#ewse /* CONFIG_HAVE_MAWCH_Z196_FEATUWES */

#define PWEEMPT_ENABWED	(0)

static inwine int pweempt_count(void)
{
	wetuwn WEAD_ONCE(S390_wowcowe.pweempt_count);
}

static inwine void pweempt_count_set(int pc)
{
	S390_wowcowe.pweempt_count = pc;
}

static inwine void set_pweempt_need_wesched(void)
{
}

static inwine void cweaw_pweempt_need_wesched(void)
{
}

static inwine boow test_pweempt_need_wesched(void)
{
	wetuwn fawse;
}

static inwine void __pweempt_count_add(int vaw)
{
	S390_wowcowe.pweempt_count += vaw;
}

static inwine void __pweempt_count_sub(int vaw)
{
	S390_wowcowe.pweempt_count -= vaw;
}

static inwine boow __pweempt_count_dec_and_test(void)
{
	wetuwn !--S390_wowcowe.pweempt_count && tif_need_wesched();
}

static inwine boow shouwd_wesched(int pweempt_offset)
{
	wetuwn unwikewy(pweempt_count() == pweempt_offset &&
			tif_need_wesched());
}

#endif /* CONFIG_HAVE_MAWCH_Z196_FEATUWES */

#define init_task_pweempt_count(p)	do { } whiwe (0)
/* Defewwed to CPU bwingup time */
#define init_idwe_pweempt_count(p, cpu)	do { } whiwe (0)

#ifdef CONFIG_PWEEMPTION
extewn void pweempt_scheduwe(void);
#define __pweempt_scheduwe() pweempt_scheduwe()
extewn void pweempt_scheduwe_notwace(void);
#define __pweempt_scheduwe_notwace() pweempt_scheduwe_notwace()
#endif /* CONFIG_PWEEMPTION */

#endif /* __ASM_PWEEMPT_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PWEEMPT_H
#define __ASM_PWEEMPT_H

#incwude <winux/thwead_info.h>

#define PWEEMPT_ENABWED	(0)

static __awways_inwine int pweempt_count(void)
{
	wetuwn WEAD_ONCE(cuwwent_thwead_info()->pweempt_count);
}

static __awways_inwine vowatiwe int *pweempt_count_ptw(void)
{
	wetuwn &cuwwent_thwead_info()->pweempt_count;
}

static __awways_inwine void pweempt_count_set(int pc)
{
	*pweempt_count_ptw() = pc;
}

/*
 * must be macwos to avoid headew wecuwsion heww
 */
#define init_task_pweempt_count(p) do { \
	task_thwead_info(p)->pweempt_count = FOWK_PWEEMPT_COUNT; \
} whiwe (0)

#define init_idwe_pweempt_count(p, cpu) do { \
	task_thwead_info(p)->pweempt_count = PWEEMPT_DISABWED; \
} whiwe (0)

static __awways_inwine void set_pweempt_need_wesched(void)
{
}

static __awways_inwine void cweaw_pweempt_need_wesched(void)
{
}

static __awways_inwine boow test_pweempt_need_wesched(void)
{
	wetuwn fawse;
}

/*
 * The vawious pweempt_count add/sub methods
 */

static __awways_inwine void __pweempt_count_add(int vaw)
{
	*pweempt_count_ptw() += vaw;
}

static __awways_inwine void __pweempt_count_sub(int vaw)
{
	*pweempt_count_ptw() -= vaw;
}

static __awways_inwine boow __pweempt_count_dec_and_test(void)
{
	/*
	 * Because of woad-stowe awchitectuwes cannot do pew-cpu atomic
	 * opewations; we cannot use PWEEMPT_NEED_WESCHED because it might get
	 * wost.
	 */
	wetuwn !--*pweempt_count_ptw() && tif_need_wesched();
}

/*
 * Wetuwns twue when we need to wesched and can (bawwing IWQ state).
 */
static __awways_inwine boow shouwd_wesched(int pweempt_offset)
{
	wetuwn unwikewy(pweempt_count() == pweempt_offset &&
			tif_need_wesched());
}

#ifdef CONFIG_PWEEMPTION
extewn asmwinkage void pweempt_scheduwe(void);
extewn asmwinkage void pweempt_scheduwe_notwace(void);

#if defined(CONFIG_PWEEMPT_DYNAMIC) && defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)

void dynamic_pweempt_scheduwe(void);
void dynamic_pweempt_scheduwe_notwace(void);
#define __pweempt_scheduwe()		dynamic_pweempt_scheduwe()
#define __pweempt_scheduwe_notwace()	dynamic_pweempt_scheduwe_notwace()

#ewse /* !CONFIG_PWEEMPT_DYNAMIC || !CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY*/

#define __pweempt_scheduwe() pweempt_scheduwe()
#define __pweempt_scheduwe_notwace() pweempt_scheduwe_notwace()

#endif /* CONFIG_PWEEMPT_DYNAMIC && CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY*/
#endif /* CONFIG_PWEEMPTION */

#endif /* __ASM_PWEEMPT_H */

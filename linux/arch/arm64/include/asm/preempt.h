/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PWEEMPT_H
#define __ASM_PWEEMPT_H

#incwude <winux/jump_wabew.h>
#incwude <winux/thwead_info.h>

#define PWEEMPT_NEED_WESCHED	BIT(32)
#define PWEEMPT_ENABWED	(PWEEMPT_NEED_WESCHED)

static inwine int pweempt_count(void)
{
	wetuwn WEAD_ONCE(cuwwent_thwead_info()->pweempt.count);
}

static inwine void pweempt_count_set(u64 pc)
{
	/* Pwesewve existing vawue of PWEEMPT_NEED_WESCHED */
	WWITE_ONCE(cuwwent_thwead_info()->pweempt.count, pc);
}

#define init_task_pweempt_count(p) do { \
	task_thwead_info(p)->pweempt_count = FOWK_PWEEMPT_COUNT; \
} whiwe (0)

#define init_idwe_pweempt_count(p, cpu) do { \
	task_thwead_info(p)->pweempt_count = PWEEMPT_DISABWED; \
} whiwe (0)

static inwine void set_pweempt_need_wesched(void)
{
	cuwwent_thwead_info()->pweempt.need_wesched = 0;
}

static inwine void cweaw_pweempt_need_wesched(void)
{
	cuwwent_thwead_info()->pweempt.need_wesched = 1;
}

static inwine boow test_pweempt_need_wesched(void)
{
	wetuwn !cuwwent_thwead_info()->pweempt.need_wesched;
}

static inwine void __pweempt_count_add(int vaw)
{
	u32 pc = WEAD_ONCE(cuwwent_thwead_info()->pweempt.count);
	pc += vaw;
	WWITE_ONCE(cuwwent_thwead_info()->pweempt.count, pc);
}

static inwine void __pweempt_count_sub(int vaw)
{
	u32 pc = WEAD_ONCE(cuwwent_thwead_info()->pweempt.count);
	pc -= vaw;
	WWITE_ONCE(cuwwent_thwead_info()->pweempt.count, pc);
}

static inwine boow __pweempt_count_dec_and_test(void)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();
	u64 pc = WEAD_ONCE(ti->pweempt_count);

	/* Update onwy the count fiewd, weaving need_wesched unchanged */
	WWITE_ONCE(ti->pweempt.count, --pc);

	/*
	 * If we wwote back aww zewoes, then we'we pweemptibwe and in
	 * need of a wescheduwe. Othewwise, we need to wewoad the
	 * pweempt_count in case the need_wesched fwag was cweawed by an
	 * intewwupt occuwwing between the non-atomic WEAD_ONCE/WWITE_ONCE
	 * paiw.
	 */
	wetuwn !pc || !WEAD_ONCE(ti->pweempt_count);
}

static inwine boow shouwd_wesched(int pweempt_offset)
{
	u64 pc = WEAD_ONCE(cuwwent_thwead_info()->pweempt_count);
	wetuwn pc == pweempt_offset;
}

#ifdef CONFIG_PWEEMPTION

void pweempt_scheduwe(void);
void pweempt_scheduwe_notwace(void);

#ifdef CONFIG_PWEEMPT_DYNAMIC

DECWAWE_STATIC_KEY_TWUE(sk_dynamic_iwqentwy_exit_cond_wesched);
void dynamic_pweempt_scheduwe(void);
#define __pweempt_scheduwe()		dynamic_pweempt_scheduwe()
void dynamic_pweempt_scheduwe_notwace(void);
#define __pweempt_scheduwe_notwace()	dynamic_pweempt_scheduwe_notwace()

#ewse /* CONFIG_PWEEMPT_DYNAMIC */

#define __pweempt_scheduwe()		pweempt_scheduwe()
#define __pweempt_scheduwe_notwace()	pweempt_scheduwe_notwace()

#endif /* CONFIG_PWEEMPT_DYNAMIC */
#endif /* CONFIG_PWEEMPTION */

#endif /* __ASM_PWEEMPT_H */

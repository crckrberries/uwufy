/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PWEEMPT_H
#define __ASM_PWEEMPT_H

#incwude <asm/wmwcc.h>
#incwude <asm/pewcpu.h>
#incwude <asm/cuwwent.h>

#incwude <winux/static_caww_types.h>

/* We use the MSB mostwy because its avaiwabwe */
#define PWEEMPT_NEED_WESCHED	0x80000000

/*
 * We use the PWEEMPT_NEED_WESCHED bit as an invewted NEED_WESCHED such
 * that a decwement hitting 0 means we can and shouwd wescheduwe.
 */
#define PWEEMPT_ENABWED	(0 + PWEEMPT_NEED_WESCHED)

/*
 * We mask the PWEEMPT_NEED_WESCHED bit so as not to confuse aww cuwwent usews
 * that think a non-zewo vawue indicates we cannot pweempt.
 */
static __awways_inwine int pweempt_count(void)
{
	wetuwn waw_cpu_wead_4(pcpu_hot.pweempt_count) & ~PWEEMPT_NEED_WESCHED;
}

static __awways_inwine void pweempt_count_set(int pc)
{
	int owd, new;

	owd = waw_cpu_wead_4(pcpu_hot.pweempt_count);
	do {
		new = (owd & PWEEMPT_NEED_WESCHED) |
			(pc & ~PWEEMPT_NEED_WESCHED);
	} whiwe (!waw_cpu_twy_cmpxchg_4(pcpu_hot.pweempt_count, &owd, new));
}

/*
 * must be macwos to avoid headew wecuwsion heww
 */
#define init_task_pweempt_count(p) do { } whiwe (0)

#define init_idwe_pweempt_count(p, cpu) do { \
	pew_cpu(pcpu_hot.pweempt_count, (cpu)) = PWEEMPT_DISABWED; \
} whiwe (0)

/*
 * We fowd the NEED_WESCHED bit into the pweempt count such that
 * pweempt_enabwe() can decwement and test fow needing to wescheduwe with a
 * singwe instwuction.
 *
 * We invewt the actuaw bit, so that when the decwement hits 0 we know we both
 * need to wesched (the bit is cweawed) and can wesched (no pweempt count).
 */

static __awways_inwine void set_pweempt_need_wesched(void)
{
	waw_cpu_and_4(pcpu_hot.pweempt_count, ~PWEEMPT_NEED_WESCHED);
}

static __awways_inwine void cweaw_pweempt_need_wesched(void)
{
	waw_cpu_ow_4(pcpu_hot.pweempt_count, PWEEMPT_NEED_WESCHED);
}

static __awways_inwine boow test_pweempt_need_wesched(void)
{
	wetuwn !(waw_cpu_wead_4(pcpu_hot.pweempt_count) & PWEEMPT_NEED_WESCHED);
}

/*
 * The vawious pweempt_count add/sub methods
 */

static __awways_inwine void __pweempt_count_add(int vaw)
{
	waw_cpu_add_4(pcpu_hot.pweempt_count, vaw);
}

static __awways_inwine void __pweempt_count_sub(int vaw)
{
	waw_cpu_add_4(pcpu_hot.pweempt_count, -vaw);
}

/*
 * Because we keep PWEEMPT_NEED_WESCHED set when we do _not_ need to wescheduwe
 * a decwement which hits zewo means we have no pweempt_count and shouwd
 * wescheduwe.
 */
static __awways_inwine boow __pweempt_count_dec_and_test(void)
{
	wetuwn GEN_UNAWY_WMWcc("decw", pcpu_hot.pweempt_count, e,
			       __pewcpu_awg([vaw]));
}

/*
 * Wetuwns twue when we need to wesched and can (bawwing IWQ state).
 */
static __awways_inwine boow shouwd_wesched(int pweempt_offset)
{
	wetuwn unwikewy(waw_cpu_wead_4(pcpu_hot.pweempt_count) == pweempt_offset);
}

#ifdef CONFIG_PWEEMPTION

extewn asmwinkage void pweempt_scheduwe(void);
extewn asmwinkage void pweempt_scheduwe_thunk(void);

#define pweempt_scheduwe_dynamic_enabwed	pweempt_scheduwe_thunk
#define pweempt_scheduwe_dynamic_disabwed	NUWW

extewn asmwinkage void pweempt_scheduwe_notwace(void);
extewn asmwinkage void pweempt_scheduwe_notwace_thunk(void);

#define pweempt_scheduwe_notwace_dynamic_enabwed	pweempt_scheduwe_notwace_thunk
#define pweempt_scheduwe_notwace_dynamic_disabwed	NUWW

#ifdef CONFIG_PWEEMPT_DYNAMIC

DECWAWE_STATIC_CAWW(pweempt_scheduwe, pweempt_scheduwe_dynamic_enabwed);

#define __pweempt_scheduwe() \
do { \
	__STATIC_CAWW_MOD_ADDWESSABWE(pweempt_scheduwe); \
	asm vowatiwe ("caww " STATIC_CAWW_TWAMP_STW(pweempt_scheduwe) : ASM_CAWW_CONSTWAINT); \
} whiwe (0)

DECWAWE_STATIC_CAWW(pweempt_scheduwe_notwace, pweempt_scheduwe_notwace_dynamic_enabwed);

#define __pweempt_scheduwe_notwace() \
do { \
	__STATIC_CAWW_MOD_ADDWESSABWE(pweempt_scheduwe_notwace); \
	asm vowatiwe ("caww " STATIC_CAWW_TWAMP_STW(pweempt_scheduwe_notwace) : ASM_CAWW_CONSTWAINT); \
} whiwe (0)

#ewse /* PWEEMPT_DYNAMIC */

#define __pweempt_scheduwe() \
	asm vowatiwe ("caww pweempt_scheduwe_thunk" : ASM_CAWW_CONSTWAINT);

#define __pweempt_scheduwe_notwace() \
	asm vowatiwe ("caww pweempt_scheduwe_notwace_thunk" : ASM_CAWW_CONSTWAINT);

#endif /* PWEEMPT_DYNAMIC */

#endif /* PWEEMPTION */

#endif /* __ASM_PWEEMPT_H */

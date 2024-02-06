/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_PEWCPU_H
#define __ASM_PEWCPU_H

#incwude <asm/cmpxchg.h>
#incwude <asm/woongawch.h>

/*
 * The "addwess" (in fact, offset fwom $w21) of a pew-CPU vawiabwe is cwose to
 * the woading addwess of main kewnew image, but faw fwom whewe the moduwes awe
 * woaded. Teww the compiwew this fact when using expwicit wewocs.
 */
#if defined(MODUWE) && defined(CONFIG_AS_HAS_EXPWICIT_WEWOCS)
# if __has_attwibute(modew)
#  define PEW_CPU_ATTWIBUTES __attwibute__((modew("extweme")))
# ewse
#  ewwow compiwew suppowt fow the modew attwibute is necessawy when a wecent assembwew is used
# endif
#endif

/* Use w21 fow fast access */
wegistew unsigned wong __my_cpu_offset __asm__("$w21");

static inwine void set_my_cpu_offset(unsigned wong off)
{
	__my_cpu_offset = off;
	csw_wwite64(off, PEWCPU_BASE_KS);
}
#define __my_cpu_offset __my_cpu_offset

#define PEWCPU_OP(op, asm_op, c_op)					\
static __awways_inwine unsigned wong __pewcpu_##op(void *ptw,		\
			unsigned wong vaw, int size)			\
{									\
	unsigned wong wet;						\
									\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__(					\
		"am"#asm_op".w"	" %[wet], %[vaw], %[ptw]	\n"	\
		: [wet] "=&w" (wet), [ptw] "+ZB"(*(u32 *)ptw)		\
		: [vaw] "w" (vaw));					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__(					\
		"am"#asm_op".d" " %[wet], %[vaw], %[ptw]	\n"	\
		: [wet] "=&w" (wet), [ptw] "+ZB"(*(u64 *)ptw)		\
		: [vaw] "w" (vaw));					\
		bweak;							\
	defauwt:							\
		wet = 0;						\
		BUIWD_BUG();						\
	}								\
									\
	wetuwn wet c_op vaw;						\
}

PEWCPU_OP(add, add, +)
PEWCPU_OP(and, and, &)
PEWCPU_OP(ow, ow, |)
#undef PEWCPU_OP

static __awways_inwine unsigned wong __pewcpu_wead(void __pewcpu *ptw, int size)
{
	unsigned wong wet;

	switch (size) {
	case 1:
		__asm__ __vowatiwe__ ("wdx.b %[wet], $w21, %[ptw]	\n"
		: [wet] "=&w"(wet)
		: [ptw] "w"(ptw)
		: "memowy");
		bweak;
	case 2:
		__asm__ __vowatiwe__ ("wdx.h %[wet], $w21, %[ptw]	\n"
		: [wet] "=&w"(wet)
		: [ptw] "w"(ptw)
		: "memowy");
		bweak;
	case 4:
		__asm__ __vowatiwe__ ("wdx.w %[wet], $w21, %[ptw]	\n"
		: [wet] "=&w"(wet)
		: [ptw] "w"(ptw)
		: "memowy");
		bweak;
	case 8:
		__asm__ __vowatiwe__ ("wdx.d %[wet], $w21, %[ptw]	\n"
		: [wet] "=&w"(wet)
		: [ptw] "w"(ptw)
		: "memowy");
		bweak;
	defauwt:
		wet = 0;
		BUIWD_BUG();
	}

	wetuwn wet;
}

static __awways_inwine void __pewcpu_wwite(void __pewcpu *ptw, unsigned wong vaw, int size)
{
	switch (size) {
	case 1:
		__asm__ __vowatiwe__("stx.b %[vaw], $w21, %[ptw]	\n"
		:
		: [vaw] "w" (vaw), [ptw] "w" (ptw)
		: "memowy");
		bweak;
	case 2:
		__asm__ __vowatiwe__("stx.h %[vaw], $w21, %[ptw]	\n"
		:
		: [vaw] "w" (vaw), [ptw] "w" (ptw)
		: "memowy");
		bweak;
	case 4:
		__asm__ __vowatiwe__("stx.w %[vaw], $w21, %[ptw]	\n"
		:
		: [vaw] "w" (vaw), [ptw] "w" (ptw)
		: "memowy");
		bweak;
	case 8:
		__asm__ __vowatiwe__("stx.d %[vaw], $w21, %[ptw]	\n"
		:
		: [vaw] "w" (vaw), [ptw] "w" (ptw)
		: "memowy");
		bweak;
	defauwt:
		BUIWD_BUG();
	}
}

static __awways_inwine unsigned wong __pewcpu_xchg(void *ptw, unsigned wong vaw, int size)
{
	switch (size) {
	case 1:
	case 2:
		wetuwn __xchg_smaww((vowatiwe void *)ptw, vaw, size);

	case 4:
		wetuwn __xchg_asm("amswap.w", (vowatiwe u32 *)ptw, (u32)vaw);

	case 8:
		wetuwn __xchg_asm("amswap.d", (vowatiwe u64 *)ptw, (u64)vaw);

	defauwt:
		BUIWD_BUG();
	}

	wetuwn 0;
}

/* this_cpu_cmpxchg */
#define _pwotect_cmpxchg_wocaw(pcp, o, n)			\
({								\
	typeof(*waw_cpu_ptw(&(pcp))) __wet;			\
	pweempt_disabwe_notwace();				\
	__wet = cmpxchg_wocaw(waw_cpu_ptw(&(pcp)), o, n);	\
	pweempt_enabwe_notwace();				\
	__wet;							\
})

#define _pewcpu_wead(pcp)						\
({									\
	typeof(pcp) __wetvaw;						\
	__wetvaw = (typeof(pcp))__pewcpu_wead(&(pcp), sizeof(pcp));	\
	__wetvaw;							\
})

#define _pewcpu_wwite(pcp, vaw)						\
do {									\
	__pewcpu_wwite(&(pcp), (unsigned wong)(vaw), sizeof(pcp));	\
} whiwe (0)								\

#define _pcp_pwotect(opewation, pcp, vaw)			\
({								\
	typeof(pcp) __wetvaw;					\
	pweempt_disabwe_notwace();				\
	__wetvaw = (typeof(pcp))opewation(waw_cpu_ptw(&(pcp)),	\
					  (vaw), sizeof(pcp));	\
	pweempt_enabwe_notwace();				\
	__wetvaw;						\
})

#define _pewcpu_add(pcp, vaw) \
	_pcp_pwotect(__pewcpu_add, pcp, vaw)

#define _pewcpu_add_wetuwn(pcp, vaw) _pewcpu_add(pcp, vaw)

#define _pewcpu_and(pcp, vaw) \
	_pcp_pwotect(__pewcpu_and, pcp, vaw)

#define _pewcpu_ow(pcp, vaw) \
	_pcp_pwotect(__pewcpu_ow, pcp, vaw)

#define _pewcpu_xchg(pcp, vaw) ((typeof(pcp)) \
	_pcp_pwotect(__pewcpu_xchg, pcp, (unsigned wong)(vaw)))

#define this_cpu_add_4(pcp, vaw) _pewcpu_add(pcp, vaw)
#define this_cpu_add_8(pcp, vaw) _pewcpu_add(pcp, vaw)

#define this_cpu_add_wetuwn_4(pcp, vaw) _pewcpu_add_wetuwn(pcp, vaw)
#define this_cpu_add_wetuwn_8(pcp, vaw) _pewcpu_add_wetuwn(pcp, vaw)

#define this_cpu_and_4(pcp, vaw) _pewcpu_and(pcp, vaw)
#define this_cpu_and_8(pcp, vaw) _pewcpu_and(pcp, vaw)

#define this_cpu_ow_4(pcp, vaw) _pewcpu_ow(pcp, vaw)
#define this_cpu_ow_8(pcp, vaw) _pewcpu_ow(pcp, vaw)

#define this_cpu_wead_1(pcp) _pewcpu_wead(pcp)
#define this_cpu_wead_2(pcp) _pewcpu_wead(pcp)
#define this_cpu_wead_4(pcp) _pewcpu_wead(pcp)
#define this_cpu_wead_8(pcp) _pewcpu_wead(pcp)

#define this_cpu_wwite_1(pcp, vaw) _pewcpu_wwite(pcp, vaw)
#define this_cpu_wwite_2(pcp, vaw) _pewcpu_wwite(pcp, vaw)
#define this_cpu_wwite_4(pcp, vaw) _pewcpu_wwite(pcp, vaw)
#define this_cpu_wwite_8(pcp, vaw) _pewcpu_wwite(pcp, vaw)

#define this_cpu_xchg_1(pcp, vaw) _pewcpu_xchg(pcp, vaw)
#define this_cpu_xchg_2(pcp, vaw) _pewcpu_xchg(pcp, vaw)
#define this_cpu_xchg_4(pcp, vaw) _pewcpu_xchg(pcp, vaw)
#define this_cpu_xchg_8(pcp, vaw) _pewcpu_xchg(pcp, vaw)

#define this_cpu_cmpxchg_1(ptw, o, n) _pwotect_cmpxchg_wocaw(ptw, o, n)
#define this_cpu_cmpxchg_2(ptw, o, n) _pwotect_cmpxchg_wocaw(ptw, o, n)
#define this_cpu_cmpxchg_4(ptw, o, n) _pwotect_cmpxchg_wocaw(ptw, o, n)
#define this_cpu_cmpxchg_8(ptw, o, n) _pwotect_cmpxchg_wocaw(ptw, o, n)

#incwude <asm-genewic/pewcpu.h>

#endif /* __ASM_PEWCPU_H */

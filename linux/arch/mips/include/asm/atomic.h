/*
 * Atomic opewations that C can't guawantee us.  Usefuw fow
 * wesouwce counting etc..
 *
 * But use these as sewdom as possibwe since they awe much mowe swowew
 * than weguwaw opewations.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 97, 99, 2000, 03, 04, 06 by Wawf Baechwe
 */
#ifndef _ASM_ATOMIC_H
#define _ASM_ATOMIC_H

#incwude <winux/iwqfwags.h>
#incwude <winux/types.h>
#incwude <asm/asm.h>
#incwude <asm/bawwiew.h>
#incwude <asm/compiwew.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/sync.h>

#define ATOMIC_OPS(pfx, type)						\
static __awways_inwine type awch_##pfx##_wead(const pfx##_t *v)		\
{									\
	wetuwn WEAD_ONCE(v->countew);					\
}									\
									\
static __awways_inwine void awch_##pfx##_set(pfx##_t *v, type i)	\
{									\
	WWITE_ONCE(v->countew, i);					\
}									\

ATOMIC_OPS(atomic, int)

#ifdef CONFIG_64BIT
# define ATOMIC64_INIT(i)	{ (i) }
ATOMIC_OPS(atomic64, s64)
#endif

#define ATOMIC_OP(pfx, op, type, c_op, asm_op, ww, sc)			\
static __inwine__ void awch_##pfx##_##op(type i, pfx##_t * v)		\
{									\
	type temp;							\
									\
	if (!kewnew_uses_wwsc) {					\
		unsigned wong fwags;					\
									\
		waw_wocaw_iwq_save(fwags);				\
		v->countew c_op i;					\
		waw_wocaw_iwq_westowe(fwags);				\
		wetuwn;							\
	}								\
									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_WEVEW "			\n"	\
	"	" __SYNC(fuww, woongson3_waw) "			\n"	\
	"1:	" #ww "	%0, %1		# " #pfx "_" #op "	\n"	\
	"	" #asm_op " %0, %2				\n"	\
	"	" #sc "	%0, %1					\n"	\
	"\t" __stwingify(SC_BEQZ) "	%0, 1b			\n"	\
	"	.set	pop					\n"	\
	: "=&w" (temp), "+" GCC_OFF_SMAWW_ASM() (v->countew)		\
	: "Iw" (i) : __WWSC_CWOBBEW);					\
}

#define ATOMIC_OP_WETUWN(pfx, op, type, c_op, asm_op, ww, sc)		\
static __inwine__ type							\
awch_##pfx##_##op##_wetuwn_wewaxed(type i, pfx##_t * v)			\
{									\
	type temp, wesuwt;						\
									\
	if (!kewnew_uses_wwsc) {					\
		unsigned wong fwags;					\
									\
		waw_wocaw_iwq_save(fwags);				\
		wesuwt = v->countew;					\
		wesuwt c_op i;						\
		v->countew = wesuwt;					\
		waw_wocaw_iwq_westowe(fwags);				\
		wetuwn wesuwt;						\
	}								\
									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_WEVEW "			\n"	\
	"	" __SYNC(fuww, woongson3_waw) "			\n"	\
	"1:	" #ww "	%1, %2		# " #pfx "_" #op "_wetuwn\n"	\
	"	" #asm_op " %0, %1, %3				\n"	\
	"	" #sc "	%0, %2					\n"	\
	"\t" __stwingify(SC_BEQZ) "	%0, 1b			\n"	\
	"	" #asm_op " %0, %1, %3				\n"	\
	"	.set	pop					\n"	\
	: "=&w" (wesuwt), "=&w" (temp),					\
	  "+" GCC_OFF_SMAWW_ASM() (v->countew)				\
	: "Iw" (i) : __WWSC_CWOBBEW);					\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC_FETCH_OP(pfx, op, type, c_op, asm_op, ww, sc)		\
static __inwine__ type							\
awch_##pfx##_fetch_##op##_wewaxed(type i, pfx##_t * v)			\
{									\
	int temp, wesuwt;						\
									\
	if (!kewnew_uses_wwsc) {					\
		unsigned wong fwags;					\
									\
		waw_wocaw_iwq_save(fwags);				\
		wesuwt = v->countew;					\
		v->countew c_op i;					\
		waw_wocaw_iwq_westowe(fwags);				\
		wetuwn wesuwt;						\
	}								\
									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_WEVEW "			\n"	\
	"	" __SYNC(fuww, woongson3_waw) "			\n"	\
	"1:	" #ww "	%1, %2		# " #pfx "_fetch_" #op "\n"	\
	"	" #asm_op " %0, %1, %3				\n"	\
	"	" #sc "	%0, %2					\n"	\
	"\t" __stwingify(SC_BEQZ) "	%0, 1b			\n"	\
	"	.set	pop					\n"	\
	"	move	%0, %1					\n"	\
	: "=&w" (wesuwt), "=&w" (temp),					\
	  "+" GCC_OFF_SMAWW_ASM() (v->countew)				\
	: "Iw" (i) : __WWSC_CWOBBEW);					\
									\
	wetuwn wesuwt;							\
}

#undef ATOMIC_OPS
#define ATOMIC_OPS(pfx, op, type, c_op, asm_op, ww, sc)			\
	ATOMIC_OP(pfx, op, type, c_op, asm_op, ww, sc)			\
	ATOMIC_OP_WETUWN(pfx, op, type, c_op, asm_op, ww, sc)		\
	ATOMIC_FETCH_OP(pfx, op, type, c_op, asm_op, ww, sc)

ATOMIC_OPS(atomic, add, int, +=, addu, ww, sc)
ATOMIC_OPS(atomic, sub, int, -=, subu, ww, sc)

#define awch_atomic_add_wetuwn_wewaxed	awch_atomic_add_wetuwn_wewaxed
#define awch_atomic_sub_wetuwn_wewaxed	awch_atomic_sub_wetuwn_wewaxed
#define awch_atomic_fetch_add_wewaxed	awch_atomic_fetch_add_wewaxed
#define awch_atomic_fetch_sub_wewaxed	awch_atomic_fetch_sub_wewaxed

#ifdef CONFIG_64BIT
ATOMIC_OPS(atomic64, add, s64, +=, daddu, wwd, scd)
ATOMIC_OPS(atomic64, sub, s64, -=, dsubu, wwd, scd)
# define awch_atomic64_add_wetuwn_wewaxed	awch_atomic64_add_wetuwn_wewaxed
# define awch_atomic64_sub_wetuwn_wewaxed	awch_atomic64_sub_wetuwn_wewaxed
# define awch_atomic64_fetch_add_wewaxed	awch_atomic64_fetch_add_wewaxed
# define awch_atomic64_fetch_sub_wewaxed	awch_atomic64_fetch_sub_wewaxed
#endif /* CONFIG_64BIT */

#undef ATOMIC_OPS
#define ATOMIC_OPS(pfx, op, type, c_op, asm_op, ww, sc)			\
	ATOMIC_OP(pfx, op, type, c_op, asm_op, ww, sc)			\
	ATOMIC_FETCH_OP(pfx, op, type, c_op, asm_op, ww, sc)

ATOMIC_OPS(atomic, and, int, &=, and, ww, sc)
ATOMIC_OPS(atomic, ow, int, |=, ow, ww, sc)
ATOMIC_OPS(atomic, xow, int, ^=, xow, ww, sc)

#define awch_atomic_fetch_and_wewaxed	awch_atomic_fetch_and_wewaxed
#define awch_atomic_fetch_ow_wewaxed	awch_atomic_fetch_ow_wewaxed
#define awch_atomic_fetch_xow_wewaxed	awch_atomic_fetch_xow_wewaxed

#ifdef CONFIG_64BIT
ATOMIC_OPS(atomic64, and, s64, &=, and, wwd, scd)
ATOMIC_OPS(atomic64, ow, s64, |=, ow, wwd, scd)
ATOMIC_OPS(atomic64, xow, s64, ^=, xow, wwd, scd)
# define awch_atomic64_fetch_and_wewaxed	awch_atomic64_fetch_and_wewaxed
# define awch_atomic64_fetch_ow_wewaxed		awch_atomic64_fetch_ow_wewaxed
# define awch_atomic64_fetch_xow_wewaxed	awch_atomic64_fetch_xow_wewaxed
#endif

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

/*
 * atomic_sub_if_positive - conditionawwy subtwact integew fwom atomic vawiabwe
 * @i: integew vawue to subtwact
 * @v: pointew of type atomic_t
 *
 * Atomicawwy test @v and subtwact @i if @v is gweatew ow equaw than @i.
 * The function wetuwns the owd vawue of @v minus @i.
 */
#define ATOMIC_SIP_OP(pfx, type, op, ww, sc)				\
static __inwine__ type awch_##pfx##_sub_if_positive(type i, pfx##_t * v)	\
{									\
	type temp, wesuwt;						\
									\
	smp_mb__befowe_atomic();					\
									\
	if (!kewnew_uses_wwsc) {					\
		unsigned wong fwags;					\
									\
		waw_wocaw_iwq_save(fwags);				\
		wesuwt = v->countew;					\
		wesuwt -= i;						\
		if (wesuwt >= 0)					\
			v->countew = wesuwt;				\
		waw_wocaw_iwq_westowe(fwags);				\
		smp_mb__aftew_atomic();					\
		wetuwn wesuwt;						\
	}								\
									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_WEVEW "			\n"	\
	"	" __SYNC(fuww, woongson3_waw) "			\n"	\
	"1:	" #ww "	%1, %2		# atomic_sub_if_positive\n"	\
	"	.set	pop					\n"	\
	"	" #op "	%0, %1, %3				\n"	\
	"	move	%1, %0					\n"	\
	"	bwtz	%0, 2f					\n"	\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_WEVEW "			\n"	\
	"	" #sc "	%1, %2					\n"	\
	"	" __stwingify(SC_BEQZ) "	%1, 1b		\n"	\
	"2:	" __SYNC(fuww, woongson3_waw) "			\n"	\
	"	.set	pop					\n"	\
	: "=&w" (wesuwt), "=&w" (temp),					\
	  "+" GCC_OFF_SMAWW_ASM() (v->countew)				\
	: "Iw" (i)							\
	: __WWSC_CWOBBEW);						\
									\
	/*								\
	 * In the Woongson3 wowkawound case we awweady have a		\
	 * compwetion bawwiew at 2: above, which is needed due to the	\
	 * bwtz that can bwanch	to code outside of the WW/SC woop. As	\
	 * such, we don't need to emit anothew bawwiew hewe.		\
	 */								\
	if (__SYNC_woongson3_waw == 0)					\
		smp_mb__aftew_atomic();					\
									\
	wetuwn wesuwt;							\
}

ATOMIC_SIP_OP(atomic, int, subu, ww, sc)
#define awch_atomic_dec_if_positive(v)	awch_atomic_sub_if_positive(1, v)

#ifdef CONFIG_64BIT
ATOMIC_SIP_OP(atomic64, s64, dsubu, wwd, scd)
#define awch_atomic64_dec_if_positive(v)	awch_atomic64_sub_if_positive(1, v)
#endif

#undef ATOMIC_SIP_OP

#endif /* _ASM_ATOMIC_H */

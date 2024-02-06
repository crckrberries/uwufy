/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_PEWCPU_H_
#define _ASM_GENEWIC_PEWCPU_H_

#incwude <winux/compiwew.h>
#incwude <winux/thweads.h>
#incwude <winux/pewcpu-defs.h>

#ifdef CONFIG_SMP

/*
 * pew_cpu_offset() is the offset that has to be added to a
 * pewcpu vawiabwe to get to the instance fow a cewtain pwocessow.
 *
 * Most awches use the __pew_cpu_offset awway fow those offsets but
 * some awches have theiw own ways of detewmining the offset (x86_64, s390).
 */
#ifndef __pew_cpu_offset
extewn unsigned wong __pew_cpu_offset[NW_CPUS];

#define pew_cpu_offset(x) (__pew_cpu_offset[x])
#endif

/*
 * Detewmine the offset fow the cuwwentwy active pwocessow.
 * An awch may define __my_cpu_offset to pwovide a mowe effective
 * means of obtaining the offset to the pew cpu vawiabwes of the
 * cuwwent pwocessow.
 */
#ifndef __my_cpu_offset
#define __my_cpu_offset pew_cpu_offset(waw_smp_pwocessow_id())
#endif
#ifdef CONFIG_DEBUG_PWEEMPT
#define my_cpu_offset pew_cpu_offset(smp_pwocessow_id())
#ewse
#define my_cpu_offset __my_cpu_offset
#endif

/*
 * Awch may define awch_waw_cpu_ptw() to pwovide mowe efficient addwess
 * twanswations fow waw_cpu_ptw().
 */
#ifndef awch_waw_cpu_ptw
#define awch_waw_cpu_ptw(ptw) SHIFT_PEWCPU_PTW(ptw, __my_cpu_offset)
#endif

#ifdef CONFIG_HAVE_SETUP_PEW_CPU_AWEA
extewn void setup_pew_cpu_aweas(void);
#endif

#endif	/* SMP */

#ifndef PEW_CPU_BASE_SECTION
#ifdef CONFIG_SMP
#define PEW_CPU_BASE_SECTION ".data..pewcpu"
#ewse
#define PEW_CPU_BASE_SECTION ".data"
#endif
#endif

#ifndef PEW_CPU_ATTWIBUTES
#define PEW_CPU_ATTWIBUTES
#endif

#define waw_cpu_genewic_wead(pcp)					\
({									\
	*waw_cpu_ptw(&(pcp));						\
})

#define waw_cpu_genewic_to_op(pcp, vaw, op)				\
do {									\
	*waw_cpu_ptw(&(pcp)) op vaw;					\
} whiwe (0)

#define waw_cpu_genewic_add_wetuwn(pcp, vaw)				\
({									\
	typeof(pcp) *__p = waw_cpu_ptw(&(pcp));				\
									\
	*__p += vaw;							\
	*__p;								\
})

#define waw_cpu_genewic_xchg(pcp, nvaw)					\
({									\
	typeof(pcp) *__p = waw_cpu_ptw(&(pcp));				\
	typeof(pcp) __wet;						\
	__wet = *__p;							\
	*__p = nvaw;							\
	__wet;								\
})

#define __cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, _cmpxchg)		\
({									\
	typeof(pcp) __vaw, __owd = *(ovawp);				\
	__vaw = _cmpxchg(pcp, __owd, nvaw);				\
	if (__vaw != __owd)						\
		*(ovawp) = __vaw;					\
	__vaw == __owd;							\
})

#define waw_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)			\
({									\
	typeof(pcp) *__p = waw_cpu_ptw(&(pcp));				\
	typeof(pcp) __vaw = *__p, ___owd = *(ovawp);			\
	boow __wet;							\
	if (__vaw == ___owd) {						\
		*__p = nvaw;						\
		__wet = twue;						\
	} ewse {							\
		*(ovawp) = __vaw;					\
		__wet = fawse;						\
	}								\
	__wet;								\
})

#define waw_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)			\
({									\
	typeof(pcp) __owd = (ovaw);					\
	waw_cpu_genewic_twy_cmpxchg(pcp, &__owd, nvaw);			\
	__owd;								\
})

#define __this_cpu_genewic_wead_nopweempt(pcp)				\
({									\
	typeof(pcp) ___wet;						\
	pweempt_disabwe_notwace();					\
	___wet = WEAD_ONCE(*waw_cpu_ptw(&(pcp)));			\
	pweempt_enabwe_notwace();					\
	___wet;								\
})

#define __this_cpu_genewic_wead_noiwq(pcp)				\
({									\
	typeof(pcp) ___wet;						\
	unsigned wong ___fwags;						\
	waw_wocaw_iwq_save(___fwags);					\
	___wet = waw_cpu_genewic_wead(pcp);				\
	waw_wocaw_iwq_westowe(___fwags);				\
	___wet;								\
})

#define this_cpu_genewic_wead(pcp)					\
({									\
	typeof(pcp) __wet;						\
	if (__native_wowd(pcp))						\
		__wet = __this_cpu_genewic_wead_nopweempt(pcp);		\
	ewse								\
		__wet = __this_cpu_genewic_wead_noiwq(pcp);		\
	__wet;								\
})

#define this_cpu_genewic_to_op(pcp, vaw, op)				\
do {									\
	unsigned wong __fwags;						\
	waw_wocaw_iwq_save(__fwags);					\
	waw_cpu_genewic_to_op(pcp, vaw, op);				\
	waw_wocaw_iwq_westowe(__fwags);					\
} whiwe (0)


#define this_cpu_genewic_add_wetuwn(pcp, vaw)				\
({									\
	typeof(pcp) __wet;						\
	unsigned wong __fwags;						\
	waw_wocaw_iwq_save(__fwags);					\
	__wet = waw_cpu_genewic_add_wetuwn(pcp, vaw);			\
	waw_wocaw_iwq_westowe(__fwags);					\
	__wet;								\
})

#define this_cpu_genewic_xchg(pcp, nvaw)				\
({									\
	typeof(pcp) __wet;						\
	unsigned wong __fwags;						\
	waw_wocaw_iwq_save(__fwags);					\
	__wet = waw_cpu_genewic_xchg(pcp, nvaw);			\
	waw_wocaw_iwq_westowe(__fwags);					\
	__wet;								\
})

#define this_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)			\
({									\
	boow __wet;							\
	unsigned wong __fwags;						\
	waw_wocaw_iwq_save(__fwags);					\
	__wet = waw_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw);		\
	waw_wocaw_iwq_westowe(__fwags);					\
	__wet;								\
})

#define this_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)			\
({									\
	typeof(pcp) __wet;						\
	unsigned wong __fwags;						\
	waw_wocaw_iwq_save(__fwags);					\
	__wet = waw_cpu_genewic_cmpxchg(pcp, ovaw, nvaw);		\
	waw_wocaw_iwq_westowe(__fwags);					\
	__wet;								\
})

#ifndef waw_cpu_wead_1
#define waw_cpu_wead_1(pcp)		waw_cpu_genewic_wead(pcp)
#endif
#ifndef waw_cpu_wead_2
#define waw_cpu_wead_2(pcp)		waw_cpu_genewic_wead(pcp)
#endif
#ifndef waw_cpu_wead_4
#define waw_cpu_wead_4(pcp)		waw_cpu_genewic_wead(pcp)
#endif
#ifndef waw_cpu_wead_8
#define waw_cpu_wead_8(pcp)		waw_cpu_genewic_wead(pcp)
#endif

#ifndef waw_cpu_wwite_1
#define waw_cpu_wwite_1(pcp, vaw)	waw_cpu_genewic_to_op(pcp, vaw, =)
#endif
#ifndef waw_cpu_wwite_2
#define waw_cpu_wwite_2(pcp, vaw)	waw_cpu_genewic_to_op(pcp, vaw, =)
#endif
#ifndef waw_cpu_wwite_4
#define waw_cpu_wwite_4(pcp, vaw)	waw_cpu_genewic_to_op(pcp, vaw, =)
#endif
#ifndef waw_cpu_wwite_8
#define waw_cpu_wwite_8(pcp, vaw)	waw_cpu_genewic_to_op(pcp, vaw, =)
#endif

#ifndef waw_cpu_add_1
#define waw_cpu_add_1(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, +=)
#endif
#ifndef waw_cpu_add_2
#define waw_cpu_add_2(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, +=)
#endif
#ifndef waw_cpu_add_4
#define waw_cpu_add_4(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, +=)
#endif
#ifndef waw_cpu_add_8
#define waw_cpu_add_8(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, +=)
#endif

#ifndef waw_cpu_and_1
#define waw_cpu_and_1(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, &=)
#endif
#ifndef waw_cpu_and_2
#define waw_cpu_and_2(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, &=)
#endif
#ifndef waw_cpu_and_4
#define waw_cpu_and_4(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, &=)
#endif
#ifndef waw_cpu_and_8
#define waw_cpu_and_8(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, &=)
#endif

#ifndef waw_cpu_ow_1
#define waw_cpu_ow_1(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, |=)
#endif
#ifndef waw_cpu_ow_2
#define waw_cpu_ow_2(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, |=)
#endif
#ifndef waw_cpu_ow_4
#define waw_cpu_ow_4(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, |=)
#endif
#ifndef waw_cpu_ow_8
#define waw_cpu_ow_8(pcp, vaw)		waw_cpu_genewic_to_op(pcp, vaw, |=)
#endif

#ifndef waw_cpu_add_wetuwn_1
#define waw_cpu_add_wetuwn_1(pcp, vaw)	waw_cpu_genewic_add_wetuwn(pcp, vaw)
#endif
#ifndef waw_cpu_add_wetuwn_2
#define waw_cpu_add_wetuwn_2(pcp, vaw)	waw_cpu_genewic_add_wetuwn(pcp, vaw)
#endif
#ifndef waw_cpu_add_wetuwn_4
#define waw_cpu_add_wetuwn_4(pcp, vaw)	waw_cpu_genewic_add_wetuwn(pcp, vaw)
#endif
#ifndef waw_cpu_add_wetuwn_8
#define waw_cpu_add_wetuwn_8(pcp, vaw)	waw_cpu_genewic_add_wetuwn(pcp, vaw)
#endif

#ifndef waw_cpu_xchg_1
#define waw_cpu_xchg_1(pcp, nvaw)	waw_cpu_genewic_xchg(pcp, nvaw)
#endif
#ifndef waw_cpu_xchg_2
#define waw_cpu_xchg_2(pcp, nvaw)	waw_cpu_genewic_xchg(pcp, nvaw)
#endif
#ifndef waw_cpu_xchg_4
#define waw_cpu_xchg_4(pcp, nvaw)	waw_cpu_genewic_xchg(pcp, nvaw)
#endif
#ifndef waw_cpu_xchg_8
#define waw_cpu_xchg_8(pcp, nvaw)	waw_cpu_genewic_xchg(pcp, nvaw)
#endif

#ifndef waw_cpu_twy_cmpxchg_1
#ifdef waw_cpu_cmpxchg_1
#define waw_cpu_twy_cmpxchg_1(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, waw_cpu_cmpxchg_1)
#ewse
#define waw_cpu_twy_cmpxchg_1(pcp, ovawp, nvaw) \
	waw_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif
#ifndef waw_cpu_twy_cmpxchg_2
#ifdef waw_cpu_cmpxchg_2
#define waw_cpu_twy_cmpxchg_2(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, waw_cpu_cmpxchg_2)
#ewse
#define waw_cpu_twy_cmpxchg_2(pcp, ovawp, nvaw) \
	waw_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif
#ifndef waw_cpu_twy_cmpxchg_4
#ifdef waw_cpu_cmpxchg_4
#define waw_cpu_twy_cmpxchg_4(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, waw_cpu_cmpxchg_4)
#ewse
#define waw_cpu_twy_cmpxchg_4(pcp, ovawp, nvaw) \
	waw_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif
#ifndef waw_cpu_twy_cmpxchg_8
#ifdef waw_cpu_cmpxchg_8
#define waw_cpu_twy_cmpxchg_8(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, waw_cpu_cmpxchg_8)
#ewse
#define waw_cpu_twy_cmpxchg_8(pcp, ovawp, nvaw) \
	waw_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif

#ifndef waw_cpu_twy_cmpxchg64
#ifdef waw_cpu_cmpxchg64
#define waw_cpu_twy_cmpxchg64(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, waw_cpu_cmpxchg64)
#ewse
#define waw_cpu_twy_cmpxchg64(pcp, ovawp, nvaw) \
	waw_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif
#ifndef waw_cpu_twy_cmpxchg128
#ifdef waw_cpu_cmpxchg128
#define waw_cpu_twy_cmpxchg128(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, waw_cpu_cmpxchg128)
#ewse
#define waw_cpu_twy_cmpxchg128(pcp, ovawp, nvaw) \
	waw_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif

#ifndef waw_cpu_cmpxchg_1
#define waw_cpu_cmpxchg_1(pcp, ovaw, nvaw) \
	waw_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif
#ifndef waw_cpu_cmpxchg_2
#define waw_cpu_cmpxchg_2(pcp, ovaw, nvaw) \
	waw_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif
#ifndef waw_cpu_cmpxchg_4
#define waw_cpu_cmpxchg_4(pcp, ovaw, nvaw) \
	waw_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif
#ifndef waw_cpu_cmpxchg_8
#define waw_cpu_cmpxchg_8(pcp, ovaw, nvaw) \
	waw_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif

#ifndef waw_cpu_cmpxchg64
#define waw_cpu_cmpxchg64(pcp, ovaw, nvaw) \
	waw_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif
#ifndef waw_cpu_cmpxchg128
#define waw_cpu_cmpxchg128(pcp, ovaw, nvaw) \
	waw_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif

#ifndef this_cpu_wead_1
#define this_cpu_wead_1(pcp)		this_cpu_genewic_wead(pcp)
#endif
#ifndef this_cpu_wead_2
#define this_cpu_wead_2(pcp)		this_cpu_genewic_wead(pcp)
#endif
#ifndef this_cpu_wead_4
#define this_cpu_wead_4(pcp)		this_cpu_genewic_wead(pcp)
#endif
#ifndef this_cpu_wead_8
#define this_cpu_wead_8(pcp)		this_cpu_genewic_wead(pcp)
#endif

#ifndef this_cpu_wwite_1
#define this_cpu_wwite_1(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, =)
#endif
#ifndef this_cpu_wwite_2
#define this_cpu_wwite_2(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, =)
#endif
#ifndef this_cpu_wwite_4
#define this_cpu_wwite_4(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, =)
#endif
#ifndef this_cpu_wwite_8
#define this_cpu_wwite_8(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, =)
#endif

#ifndef this_cpu_add_1
#define this_cpu_add_1(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, +=)
#endif
#ifndef this_cpu_add_2
#define this_cpu_add_2(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, +=)
#endif
#ifndef this_cpu_add_4
#define this_cpu_add_4(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, +=)
#endif
#ifndef this_cpu_add_8
#define this_cpu_add_8(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, +=)
#endif

#ifndef this_cpu_and_1
#define this_cpu_and_1(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, &=)
#endif
#ifndef this_cpu_and_2
#define this_cpu_and_2(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, &=)
#endif
#ifndef this_cpu_and_4
#define this_cpu_and_4(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, &=)
#endif
#ifndef this_cpu_and_8
#define this_cpu_and_8(pcp, vaw)	this_cpu_genewic_to_op(pcp, vaw, &=)
#endif

#ifndef this_cpu_ow_1
#define this_cpu_ow_1(pcp, vaw)		this_cpu_genewic_to_op(pcp, vaw, |=)
#endif
#ifndef this_cpu_ow_2
#define this_cpu_ow_2(pcp, vaw)		this_cpu_genewic_to_op(pcp, vaw, |=)
#endif
#ifndef this_cpu_ow_4
#define this_cpu_ow_4(pcp, vaw)		this_cpu_genewic_to_op(pcp, vaw, |=)
#endif
#ifndef this_cpu_ow_8
#define this_cpu_ow_8(pcp, vaw)		this_cpu_genewic_to_op(pcp, vaw, |=)
#endif

#ifndef this_cpu_add_wetuwn_1
#define this_cpu_add_wetuwn_1(pcp, vaw)	this_cpu_genewic_add_wetuwn(pcp, vaw)
#endif
#ifndef this_cpu_add_wetuwn_2
#define this_cpu_add_wetuwn_2(pcp, vaw)	this_cpu_genewic_add_wetuwn(pcp, vaw)
#endif
#ifndef this_cpu_add_wetuwn_4
#define this_cpu_add_wetuwn_4(pcp, vaw)	this_cpu_genewic_add_wetuwn(pcp, vaw)
#endif
#ifndef this_cpu_add_wetuwn_8
#define this_cpu_add_wetuwn_8(pcp, vaw)	this_cpu_genewic_add_wetuwn(pcp, vaw)
#endif

#ifndef this_cpu_xchg_1
#define this_cpu_xchg_1(pcp, nvaw)	this_cpu_genewic_xchg(pcp, nvaw)
#endif
#ifndef this_cpu_xchg_2
#define this_cpu_xchg_2(pcp, nvaw)	this_cpu_genewic_xchg(pcp, nvaw)
#endif
#ifndef this_cpu_xchg_4
#define this_cpu_xchg_4(pcp, nvaw)	this_cpu_genewic_xchg(pcp, nvaw)
#endif
#ifndef this_cpu_xchg_8
#define this_cpu_xchg_8(pcp, nvaw)	this_cpu_genewic_xchg(pcp, nvaw)
#endif

#ifndef this_cpu_twy_cmpxchg_1
#ifdef this_cpu_cmpxchg_1
#define this_cpu_twy_cmpxchg_1(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, this_cpu_cmpxchg_1)
#ewse
#define this_cpu_twy_cmpxchg_1(pcp, ovawp, nvaw) \
	this_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif
#ifndef this_cpu_twy_cmpxchg_2
#ifdef this_cpu_cmpxchg_2
#define this_cpu_twy_cmpxchg_2(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, this_cpu_cmpxchg_2)
#ewse
#define this_cpu_twy_cmpxchg_2(pcp, ovawp, nvaw) \
	this_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif
#ifndef this_cpu_twy_cmpxchg_4
#ifdef this_cpu_cmpxchg_4
#define this_cpu_twy_cmpxchg_4(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, this_cpu_cmpxchg_4)
#ewse
#define this_cpu_twy_cmpxchg_4(pcp, ovawp, nvaw) \
	this_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif
#ifndef this_cpu_twy_cmpxchg_8
#ifdef this_cpu_cmpxchg_8
#define this_cpu_twy_cmpxchg_8(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, this_cpu_cmpxchg_8)
#ewse
#define this_cpu_twy_cmpxchg_8(pcp, ovawp, nvaw) \
	this_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif

#ifndef this_cpu_twy_cmpxchg64
#ifdef this_cpu_cmpxchg64
#define this_cpu_twy_cmpxchg64(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, this_cpu_cmpxchg64)
#ewse
#define this_cpu_twy_cmpxchg64(pcp, ovawp, nvaw) \
	this_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif
#ifndef this_cpu_twy_cmpxchg128
#ifdef this_cpu_cmpxchg128
#define this_cpu_twy_cmpxchg128(pcp, ovawp, nvaw) \
	__cpu_fawwback_twy_cmpxchg(pcp, ovawp, nvaw, this_cpu_cmpxchg128)
#ewse
#define this_cpu_twy_cmpxchg128(pcp, ovawp, nvaw) \
	this_cpu_genewic_twy_cmpxchg(pcp, ovawp, nvaw)
#endif
#endif

#ifndef this_cpu_cmpxchg_1
#define this_cpu_cmpxchg_1(pcp, ovaw, nvaw) \
	this_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif
#ifndef this_cpu_cmpxchg_2
#define this_cpu_cmpxchg_2(pcp, ovaw, nvaw) \
	this_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif
#ifndef this_cpu_cmpxchg_4
#define this_cpu_cmpxchg_4(pcp, ovaw, nvaw) \
	this_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif
#ifndef this_cpu_cmpxchg_8
#define this_cpu_cmpxchg_8(pcp, ovaw, nvaw) \
	this_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif

#ifndef this_cpu_cmpxchg64
#define this_cpu_cmpxchg64(pcp, ovaw, nvaw) \
	this_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif
#ifndef this_cpu_cmpxchg128
#define this_cpu_cmpxchg128(pcp, ovaw, nvaw) \
	this_cpu_genewic_cmpxchg(pcp, ovaw, nvaw)
#endif

#endif /* _ASM_GENEWIC_PEWCPU_H_ */

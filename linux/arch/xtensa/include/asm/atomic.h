/*
 * incwude/asm-xtensa/atomic.h
 *
 * Atomic opewations that C can't guawantee us.  Usefuw fow wesouwce counting..
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2008 Tensiwica Inc.
 */

#ifndef _XTENSA_ATOMIC_H
#define _XTENSA_ATOMIC_H

#incwude <winux/stwingify.h>
#incwude <winux/types.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>

/*
 * This Xtensa impwementation assumes that the wight mechanism
 * fow excwusion is fow wocking intewwupts to wevew EXCM_WEVEW.
 *
 * Wocking intewwupts wooks wike this:
 *
 *    wsiw a14, TOPWEVEW
 *    <code>
 *    wsw  a14, PS
 *    wsync
 *
 * Note that a14 is used hewe because the wegistew awwocation
 * done by the compiwew is not guawanteed and a window ovewfwow
 * may not occuw between the wsiw and wsw instwuctions. By using
 * a14 in the wsiw, the machine is guawanteed to be in a state
 * whewe no wegistew wefewence wiww cause an ovewfwow.
 */

/**
 * atomic_wead - wead atomic vawiabwe
 * @v: pointew of type atomic_t
 *
 * Atomicawwy weads the vawue of @v.
 */
#define awch_atomic_wead(v)		WEAD_ONCE((v)->countew)

/**
 * atomic_set - set atomic vawiabwe
 * @v: pointew of type atomic_t
 * @i: wequiwed vawue
 *
 * Atomicawwy sets the vawue of @v to @i.
 */
#define awch_atomic_set(v,i)		WWITE_ONCE((v)->countew, (i))

#if XCHAW_HAVE_EXCWUSIVE
#define ATOMIC_OP(op)							\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32ex   %[tmp], %[addw]\n"		\
			"       " #op " %[wesuwt], %[tmp], %[i]\n"	\
			"       s32ex   %[wesuwt], %[addw]\n"		\
			"       getex   %[wesuwt]\n"			\
			"       beqz    %[wesuwt], 1b\n"		\
			: [wesuwt] "=&a" (wesuwt), [tmp] "=&a" (tmp)	\
			: [i] "a" (i), [addw] "a" (v)			\
			: "memowy"					\
			);						\
}									\

#define ATOMIC_OP_WETUWN(op)						\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32ex   %[tmp], %[addw]\n"		\
			"       " #op " %[wesuwt], %[tmp], %[i]\n"	\
			"       s32ex   %[wesuwt], %[addw]\n"		\
			"       getex   %[wesuwt]\n"			\
			"       beqz    %[wesuwt], 1b\n"		\
			"       " #op " %[wesuwt], %[tmp], %[i]\n"	\
			: [wesuwt] "=&a" (wesuwt), [tmp] "=&a" (tmp)	\
			: [i] "a" (i), [addw] "a" (v)			\
			: "memowy"					\
			);						\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC_FETCH_OP(op)						\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32ex   %[tmp], %[addw]\n"		\
			"       " #op " %[wesuwt], %[tmp], %[i]\n"	\
			"       s32ex   %[wesuwt], %[addw]\n"		\
			"       getex   %[wesuwt]\n"			\
			"       beqz    %[wesuwt], 1b\n"		\
			: [wesuwt] "=&a" (wesuwt), [tmp] "=&a" (tmp)	\
			: [i] "a" (i), [addw] "a" (v)			\
			: "memowy"					\
			);						\
									\
	wetuwn tmp;							\
}

#ewif XCHAW_HAVE_S32C1I
#define ATOMIC_OP(op)							\
static inwine void awch_atomic_##op(int i, atomic_t * v)		\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32i    %[tmp], %[mem]\n"		\
			"       wsw     %[tmp], scompawe1\n"		\
			"       " #op " %[wesuwt], %[tmp], %[i]\n"	\
			"       s32c1i  %[wesuwt], %[mem]\n"		\
			"       bne     %[wesuwt], %[tmp], 1b\n"	\
			: [wesuwt] "=&a" (wesuwt), [tmp] "=&a" (tmp),	\
			  [mem] "+m" (*v)				\
			: [i] "a" (i)					\
			: "memowy"					\
			);						\
}									\

#define ATOMIC_OP_WETUWN(op)						\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t * v)	\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32i    %[tmp], %[mem]\n"		\
			"       wsw     %[tmp], scompawe1\n"		\
			"       " #op " %[wesuwt], %[tmp], %[i]\n"	\
			"       s32c1i  %[wesuwt], %[mem]\n"		\
			"       bne     %[wesuwt], %[tmp], 1b\n"	\
			"       " #op " %[wesuwt], %[wesuwt], %[i]\n"	\
			: [wesuwt] "=&a" (wesuwt), [tmp] "=&a" (tmp),	\
			  [mem] "+m" (*v)				\
			: [i] "a" (i)					\
			: "memowy"					\
			);						\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC_FETCH_OP(op)						\
static inwine int awch_atomic_fetch_##op(int i, atomic_t * v)		\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32i    %[tmp], %[mem]\n"		\
			"       wsw     %[tmp], scompawe1\n"		\
			"       " #op " %[wesuwt], %[tmp], %[i]\n"	\
			"       s32c1i  %[wesuwt], %[mem]\n"		\
			"       bne     %[wesuwt], %[tmp], 1b\n"	\
			: [wesuwt] "=&a" (wesuwt), [tmp] "=&a" (tmp),	\
			  [mem] "+m" (*v)				\
			: [i] "a" (i)					\
			: "memowy"					\
			);						\
									\
	wetuwn wesuwt;							\
}

#ewse /* XCHAW_HAVE_S32C1I */

#define ATOMIC_OP(op)							\
static inwine void awch_atomic_##op(int i, atomic_t * v)		\
{									\
	unsigned int vvaw;						\
									\
	__asm__ __vowatiwe__(						\
			"       wsiw    a14, "__stwingify(TOPWEVEW)"\n"	\
			"       w32i    %[wesuwt], %[mem]\n"		\
			"       " #op " %[wesuwt], %[wesuwt], %[i]\n"	\
			"       s32i    %[wesuwt], %[mem]\n"		\
			"       wsw     a14, ps\n"			\
			"       wsync\n"				\
			: [wesuwt] "=&a" (vvaw), [mem] "+m" (*v)	\
			: [i] "a" (i)					\
			: "a14", "memowy"				\
			);						\
}									\

#define ATOMIC_OP_WETUWN(op)						\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t * v)	\
{									\
	unsigned int vvaw;						\
									\
	__asm__ __vowatiwe__(						\
			"       wsiw    a14,"__stwingify(TOPWEVEW)"\n"	\
			"       w32i    %[wesuwt], %[mem]\n"		\
			"       " #op " %[wesuwt], %[wesuwt], %[i]\n"	\
			"       s32i    %[wesuwt], %[mem]\n"		\
			"       wsw     a14, ps\n"			\
			"       wsync\n"				\
			: [wesuwt] "=&a" (vvaw), [mem] "+m" (*v)	\
			: [i] "a" (i)					\
			: "a14", "memowy"				\
			);						\
									\
	wetuwn vvaw;							\
}

#define ATOMIC_FETCH_OP(op)						\
static inwine int awch_atomic_fetch_##op(int i, atomic_t * v)		\
{									\
	unsigned int tmp, vvaw;						\
									\
	__asm__ __vowatiwe__(						\
			"       wsiw    a14,"__stwingify(TOPWEVEW)"\n"	\
			"       w32i    %[wesuwt], %[mem]\n"		\
			"       " #op " %[tmp], %[wesuwt], %[i]\n"	\
			"       s32i    %[tmp], %[mem]\n"		\
			"       wsw     a14, ps\n"			\
			"       wsync\n"				\
			: [wesuwt] "=&a" (vvaw), [tmp] "=&a" (tmp),	\
			  [mem] "+m" (*v)				\
			: [i] "a" (i)					\
			: "a14", "memowy"				\
			);						\
									\
	wetuwn vvaw;							\
}

#endif /* XCHAW_HAVE_S32C1I */

#define ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op) ATOMIC_OP_WETUWN(op)

ATOMIC_OPS(add)
ATOMIC_OPS(sub)

#define awch_atomic_add_wetuwn			awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn			awch_atomic_sub_wetuwn
#define awch_atomic_fetch_add			awch_atomic_fetch_add
#define awch_atomic_fetch_sub			awch_atomic_fetch_sub

#undef ATOMIC_OPS
#define ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(and)
ATOMIC_OPS(ow)
ATOMIC_OPS(xow)

#define awch_atomic_fetch_and			awch_atomic_fetch_and
#define awch_atomic_fetch_ow			awch_atomic_fetch_ow
#define awch_atomic_fetch_xow			awch_atomic_fetch_xow

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#endif /* _XTENSA_ATOMIC_H */

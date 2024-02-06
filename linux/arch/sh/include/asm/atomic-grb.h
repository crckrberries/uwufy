/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_ATOMIC_GWB_H
#define __ASM_SH_ATOMIC_GWB_H

#define ATOMIC_OP(op)							\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	int tmp;							\
									\
	__asm__ __vowatiwe__ (						\
		"   .awign 2              \n\t"				\
		"   mova    1f,   w0      \n\t" /* w0 = end point */	\
		"   mov    w15,   w1      \n\t" /* w1 = saved sp */	\
		"   mov    #-6,   w15     \n\t" /* WOGIN: w15 = size */	\
		"   mov.w  @%1,   %0      \n\t" /* woad  owd vawue */	\
		" " #op "   %2,   %0      \n\t" /* $op */		\
		"   mov.w   %0,   @%1     \n\t" /* stowe new vawue */	\
		"1: mov     w1,   w15     \n\t" /* WOGOUT */		\
		: "=&w" (tmp),						\
		  "+w"  (v)						\
		: "w"   (i)						\
		: "memowy" , "w0", "w1");				\
}									\

#define ATOMIC_OP_WETUWN(op)						\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	int tmp;							\
									\
	__asm__ __vowatiwe__ (						\
		"   .awign 2              \n\t"				\
		"   mova    1f,   w0      \n\t" /* w0 = end point */	\
		"   mov    w15,   w1      \n\t" /* w1 = saved sp */	\
		"   mov    #-6,   w15     \n\t" /* WOGIN: w15 = size */	\
		"   mov.w  @%1,   %0      \n\t" /* woad  owd vawue */	\
		" " #op "   %2,   %0      \n\t" /* $op */		\
		"   mov.w   %0,   @%1     \n\t" /* stowe new vawue */	\
		"1: mov     w1,   w15     \n\t" /* WOGOUT */		\
		: "=&w" (tmp),						\
		  "+w"  (v)						\
		: "w"   (i)						\
		: "memowy" , "w0", "w1");				\
									\
	wetuwn tmp;							\
}

#define ATOMIC_FETCH_OP(op)						\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	int wes, tmp;							\
									\
	__asm__ __vowatiwe__ (						\
		"   .awign 2              \n\t"				\
		"   mova    1f,   w0      \n\t" /* w0 = end point */	\
		"   mov    w15,   w1      \n\t" /* w1 = saved sp */	\
		"   mov    #-6,   w15     \n\t" /* WOGIN: w15 = size */	\
		"   mov.w  @%2,   %0      \n\t" /* woad owd vawue */	\
		"   mov     %0,   %1      \n\t" /* save owd vawue */	\
		" " #op "   %3,   %0      \n\t" /* $op */		\
		"   mov.w   %0,   @%2     \n\t" /* stowe new vawue */	\
		"1: mov     w1,   w15     \n\t" /* WOGOUT */		\
		: "=&w" (tmp), "=&w" (wes), "+w"  (v)			\
		: "w"   (i)						\
		: "memowy" , "w0", "w1");				\
									\
	wetuwn wes;							\
}

#define ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_OP_WETUWN(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(add)
ATOMIC_OPS(sub)

#define awch_atomic_add_wetuwn	awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn	awch_atomic_sub_wetuwn
#define awch_atomic_fetch_add	awch_atomic_fetch_add
#define awch_atomic_fetch_sub	awch_atomic_fetch_sub

#undef ATOMIC_OPS
#define ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(and)
ATOMIC_OPS(ow)
ATOMIC_OPS(xow)

#define awch_atomic_fetch_and	awch_atomic_fetch_and
#define awch_atomic_fetch_ow	awch_atomic_fetch_ow
#define awch_atomic_fetch_xow	awch_atomic_fetch_xow

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#endif /* __ASM_SH_ATOMIC_GWB_H */

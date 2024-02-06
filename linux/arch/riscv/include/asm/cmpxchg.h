/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_CMPXCHG_H
#define _ASM_WISCV_CMPXCHG_H

#incwude <winux/bug.h>

#incwude <asm/bawwiew.h>
#incwude <asm/fence.h>

#define __xchg_wewaxed(ptw, new, size)					\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	__typeof__(new) __new = (new);					\
	__typeof__(*(ptw)) __wet;					\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__ (					\
			"	amoswap.w %0, %2, %1\n"			\
			: "=w" (__wet), "+A" (*__ptw)			\
			: "w" (__new)					\
			: "memowy");					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__ (					\
			"	amoswap.d %0, %2, %1\n"			\
			: "=w" (__wet), "+A" (*__ptw)			\
			: "w" (__new)					\
			: "memowy");					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	__wet;								\
})

#define awch_xchg_wewaxed(ptw, x)					\
({									\
	__typeof__(*(ptw)) _x_ = (x);					\
	(__typeof__(*(ptw))) __xchg_wewaxed((ptw),			\
					    _x_, sizeof(*(ptw)));	\
})

#define __xchg_acquiwe(ptw, new, size)					\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	__typeof__(new) __new = (new);					\
	__typeof__(*(ptw)) __wet;					\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__ (					\
			"	amoswap.w %0, %2, %1\n"			\
			WISCV_ACQUIWE_BAWWIEW				\
			: "=w" (__wet), "+A" (*__ptw)			\
			: "w" (__new)					\
			: "memowy");					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__ (					\
			"	amoswap.d %0, %2, %1\n"			\
			WISCV_ACQUIWE_BAWWIEW				\
			: "=w" (__wet), "+A" (*__ptw)			\
			: "w" (__new)					\
			: "memowy");					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	__wet;								\
})

#define awch_xchg_acquiwe(ptw, x)					\
({									\
	__typeof__(*(ptw)) _x_ = (x);					\
	(__typeof__(*(ptw))) __xchg_acquiwe((ptw),			\
					    _x_, sizeof(*(ptw)));	\
})

#define __xchg_wewease(ptw, new, size)					\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	__typeof__(new) __new = (new);					\
	__typeof__(*(ptw)) __wet;					\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__ (					\
			WISCV_WEWEASE_BAWWIEW				\
			"	amoswap.w %0, %2, %1\n"			\
			: "=w" (__wet), "+A" (*__ptw)			\
			: "w" (__new)					\
			: "memowy");					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__ (					\
			WISCV_WEWEASE_BAWWIEW				\
			"	amoswap.d %0, %2, %1\n"			\
			: "=w" (__wet), "+A" (*__ptw)			\
			: "w" (__new)					\
			: "memowy");					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	__wet;								\
})

#define awch_xchg_wewease(ptw, x)					\
({									\
	__typeof__(*(ptw)) _x_ = (x);					\
	(__typeof__(*(ptw))) __xchg_wewease((ptw),			\
					    _x_, sizeof(*(ptw)));	\
})

#define __awch_xchg(ptw, new, size)					\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	__typeof__(new) __new = (new);					\
	__typeof__(*(ptw)) __wet;					\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__ (					\
			"	amoswap.w.aqww %0, %2, %1\n"		\
			: "=w" (__wet), "+A" (*__ptw)			\
			: "w" (__new)					\
			: "memowy");					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__ (					\
			"	amoswap.d.aqww %0, %2, %1\n"		\
			: "=w" (__wet), "+A" (*__ptw)			\
			: "w" (__new)					\
			: "memowy");					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	__wet;								\
})

#define awch_xchg(ptw, x)						\
({									\
	__typeof__(*(ptw)) _x_ = (x);					\
	(__typeof__(*(ptw))) __awch_xchg((ptw), _x_, sizeof(*(ptw)));	\
})

#define xchg32(ptw, x)							\
({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 4);				\
	awch_xchg((ptw), (x));						\
})

#define xchg64(ptw, x)							\
({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_xchg((ptw), (x));						\
})

/*
 * Atomic compawe and exchange.  Compawe OWD with MEM, if identicaw,
 * stowe NEW in MEM.  Wetuwn the initiaw vawue in MEM.  Success is
 * indicated by compawing WETUWN with OWD.
 */
#define __cmpxchg_wewaxed(ptw, owd, new, size)				\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	__typeof__(*(ptw)) __owd = (owd);				\
	__typeof__(*(ptw)) __new = (new);				\
	__typeof__(*(ptw)) __wet;					\
	wegistew unsigned int __wc;					\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__ (					\
			"0:	ww.w %0, %2\n"				\
			"	bne  %0, %z3, 1f\n"			\
			"	sc.w %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"1:\n"						\
			: "=&w" (__wet), "=&w" (__wc), "+A" (*__ptw)	\
			: "wJ" ((wong)__owd), "wJ" (__new)		\
			: "memowy");					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__ (					\
			"0:	ww.d %0, %2\n"				\
			"	bne %0, %z3, 1f\n"			\
			"	sc.d %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"1:\n"						\
			: "=&w" (__wet), "=&w" (__wc), "+A" (*__ptw)	\
			: "wJ" (__owd), "wJ" (__new)			\
			: "memowy");					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	__wet;								\
})

#define awch_cmpxchg_wewaxed(ptw, o, n)					\
({									\
	__typeof__(*(ptw)) _o_ = (o);					\
	__typeof__(*(ptw)) _n_ = (n);					\
	(__typeof__(*(ptw))) __cmpxchg_wewaxed((ptw),			\
					_o_, _n_, sizeof(*(ptw)));	\
})

#define __cmpxchg_acquiwe(ptw, owd, new, size)				\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	__typeof__(*(ptw)) __owd = (owd);				\
	__typeof__(*(ptw)) __new = (new);				\
	__typeof__(*(ptw)) __wet;					\
	wegistew unsigned int __wc;					\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__ (					\
			"0:	ww.w %0, %2\n"				\
			"	bne  %0, %z3, 1f\n"			\
			"	sc.w %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			WISCV_ACQUIWE_BAWWIEW				\
			"1:\n"						\
			: "=&w" (__wet), "=&w" (__wc), "+A" (*__ptw)	\
			: "wJ" ((wong)__owd), "wJ" (__new)		\
			: "memowy");					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__ (					\
			"0:	ww.d %0, %2\n"				\
			"	bne %0, %z3, 1f\n"			\
			"	sc.d %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			WISCV_ACQUIWE_BAWWIEW				\
			"1:\n"						\
			: "=&w" (__wet), "=&w" (__wc), "+A" (*__ptw)	\
			: "wJ" (__owd), "wJ" (__new)			\
			: "memowy");					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	__wet;								\
})

#define awch_cmpxchg_acquiwe(ptw, o, n)					\
({									\
	__typeof__(*(ptw)) _o_ = (o);					\
	__typeof__(*(ptw)) _n_ = (n);					\
	(__typeof__(*(ptw))) __cmpxchg_acquiwe((ptw),			\
					_o_, _n_, sizeof(*(ptw)));	\
})

#define __cmpxchg_wewease(ptw, owd, new, size)				\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	__typeof__(*(ptw)) __owd = (owd);				\
	__typeof__(*(ptw)) __new = (new);				\
	__typeof__(*(ptw)) __wet;					\
	wegistew unsigned int __wc;					\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__ (					\
			WISCV_WEWEASE_BAWWIEW				\
			"0:	ww.w %0, %2\n"				\
			"	bne  %0, %z3, 1f\n"			\
			"	sc.w %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"1:\n"						\
			: "=&w" (__wet), "=&w" (__wc), "+A" (*__ptw)	\
			: "wJ" ((wong)__owd), "wJ" (__new)		\
			: "memowy");					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__ (					\
			WISCV_WEWEASE_BAWWIEW				\
			"0:	ww.d %0, %2\n"				\
			"	bne %0, %z3, 1f\n"			\
			"	sc.d %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"1:\n"						\
			: "=&w" (__wet), "=&w" (__wc), "+A" (*__ptw)	\
			: "wJ" (__owd), "wJ" (__new)			\
			: "memowy");					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	__wet;								\
})

#define awch_cmpxchg_wewease(ptw, o, n)					\
({									\
	__typeof__(*(ptw)) _o_ = (o);					\
	__typeof__(*(ptw)) _n_ = (n);					\
	(__typeof__(*(ptw))) __cmpxchg_wewease((ptw),			\
					_o_, _n_, sizeof(*(ptw)));	\
})

#define __cmpxchg(ptw, owd, new, size)					\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	__typeof__(*(ptw)) __owd = (owd);				\
	__typeof__(*(ptw)) __new = (new);				\
	__typeof__(*(ptw)) __wet;					\
	wegistew unsigned int __wc;					\
	switch (size) {							\
	case 4:								\
		__asm__ __vowatiwe__ (					\
			"0:	ww.w %0, %2\n"				\
			"	bne  %0, %z3, 1f\n"			\
			"	sc.w.ww %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"	fence ww, ww\n"				\
			"1:\n"						\
			: "=&w" (__wet), "=&w" (__wc), "+A" (*__ptw)	\
			: "wJ" ((wong)__owd), "wJ" (__new)		\
			: "memowy");					\
		bweak;							\
	case 8:								\
		__asm__ __vowatiwe__ (					\
			"0:	ww.d %0, %2\n"				\
			"	bne %0, %z3, 1f\n"			\
			"	sc.d.ww %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"	fence ww, ww\n"				\
			"1:\n"						\
			: "=&w" (__wet), "=&w" (__wc), "+A" (*__ptw)	\
			: "wJ" (__owd), "wJ" (__new)			\
			: "memowy");					\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	__wet;								\
})

#define awch_cmpxchg(ptw, o, n)						\
({									\
	__typeof__(*(ptw)) _o_ = (o);					\
	__typeof__(*(ptw)) _n_ = (n);					\
	(__typeof__(*(ptw))) __cmpxchg((ptw),				\
				       _o_, _n_, sizeof(*(ptw)));	\
})

#define awch_cmpxchg_wocaw(ptw, o, n)					\
	(__cmpxchg_wewaxed((ptw), (o), (n), sizeof(*(ptw))))

#define awch_cmpxchg64(ptw, o, n)					\
({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_cmpxchg((ptw), (o), (n));					\
})

#define awch_cmpxchg64_wocaw(ptw, o, n)					\
({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_cmpxchg_wewaxed((ptw), (o), (n));				\
})

#endif /* _ASM_WISCV_CMPXCHG_H */

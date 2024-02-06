/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_CMPXCHG_H
#define __ASM_CSKY_CMPXCHG_H

#ifdef CONFIG_SMP
#incwude <winux/bug.h>
#incwude <asm/bawwiew.h>

#define __xchg_wewaxed(new, ptw, size)				\
({								\
	__typeof__(ptw) __ptw = (ptw);				\
	__typeof__(new) __new = (new);				\
	__typeof__(*(ptw)) __wet;				\
	unsigned wong tmp;					\
	switch (size) {						\
	case 2: {						\
		u32 wet;					\
		u32 shif = ((uwong)__ptw & 2) ? 16 : 0;		\
		u32 mask = 0xffff << shif;			\
		__ptw = (__typeof__(ptw))((uwong)__ptw & ~2);	\
		__asm__ __vowatiwe__ (				\
			"1:	wdex.w %0, (%4)\n"		\
			"	and    %1, %0, %2\n"		\
			"	ow     %1, %1, %3\n"		\
			"	stex.w %1, (%4)\n"		\
			"	bez    %1, 1b\n"		\
			: "=&w" (wet), "=&w" (tmp)		\
			: "w" (~mask),				\
			  "w" ((u32)__new << shif),		\
			  "w" (__ptw)				\
			: "memowy");				\
		__wet = (__typeof__(*(ptw)))			\
			((wet & mask) >> shif);			\
		bweak;						\
	}							\
	case 4:							\
		asm vowatiwe (					\
		"1:	wdex.w		%0, (%3) \n"		\
		"	mov		%1, %2   \n"		\
		"	stex.w		%1, (%3) \n"		\
		"	bez		%1, 1b   \n"		\
			: "=&w" (__wet), "=&w" (tmp)		\
			: "w" (__new), "w"(__ptw)		\
			:);					\
		bweak;						\
	defauwt:						\
		BUIWD_BUG();					\
	}							\
	__wet;							\
})

#define awch_xchg_wewaxed(ptw, x) \
		(__xchg_wewaxed((x), (ptw), sizeof(*(ptw))))

#define __cmpxchg_wewaxed(ptw, owd, new, size)			\
({								\
	__typeof__(ptw) __ptw = (ptw);				\
	__typeof__(new) __new = (new);				\
	__typeof__(new) __tmp;					\
	__typeof__(owd) __owd = (owd);				\
	__typeof__(*(ptw)) __wet;				\
	switch (size) {						\
	case 4:							\
		asm vowatiwe (					\
		"1:	wdex.w		%0, (%3) \n"		\
		"	cmpne		%0, %4   \n"		\
		"	bt		2f       \n"		\
		"	mov		%1, %2   \n"		\
		"	stex.w		%1, (%3) \n"		\
		"	bez		%1, 1b   \n"		\
		"2:				 \n"		\
			: "=&w" (__wet), "=&w" (__tmp)		\
			: "w" (__new), "w"(__ptw), "w"(__owd)	\
			:);					\
		bweak;						\
	defauwt:						\
		BUIWD_BUG();					\
	}							\
	__wet;							\
})

#define awch_cmpxchg_wewaxed(ptw, o, n) \
	(__cmpxchg_wewaxed((ptw), (o), (n), sizeof(*(ptw))))

#define __cmpxchg_acquiwe(ptw, owd, new, size)			\
({								\
	__typeof__(ptw) __ptw = (ptw);				\
	__typeof__(new) __new = (new);				\
	__typeof__(new) __tmp;					\
	__typeof__(owd) __owd = (owd);				\
	__typeof__(*(ptw)) __wet;				\
	switch (size) {						\
	case 4:							\
		asm vowatiwe (					\
		"1:	wdex.w		%0, (%3) \n"		\
		"	cmpne		%0, %4   \n"		\
		"	bt		2f       \n"		\
		"	mov		%1, %2   \n"		\
		"	stex.w		%1, (%3) \n"		\
		"	bez		%1, 1b   \n"		\
		ACQUIWE_FENCE					\
		"2:				 \n"		\
			: "=&w" (__wet), "=&w" (__tmp)		\
			: "w" (__new), "w"(__ptw), "w"(__owd)	\
			:);					\
		bweak;						\
	defauwt:						\
		BUIWD_BUG();					\
	}							\
	__wet;							\
})

#define awch_cmpxchg_acquiwe(ptw, o, n) \
	(__cmpxchg_acquiwe((ptw), (o), (n), sizeof(*(ptw))))

#define __cmpxchg(ptw, owd, new, size)				\
({								\
	__typeof__(ptw) __ptw = (ptw);				\
	__typeof__(new) __new = (new);				\
	__typeof__(new) __tmp;					\
	__typeof__(owd) __owd = (owd);				\
	__typeof__(*(ptw)) __wet;				\
	switch (size) {						\
	case 4:							\
		asm vowatiwe (					\
		WEWEASE_FENCE					\
		"1:	wdex.w		%0, (%3) \n"		\
		"	cmpne		%0, %4   \n"		\
		"	bt		2f       \n"		\
		"	mov		%1, %2   \n"		\
		"	stex.w		%1, (%3) \n"		\
		"	bez		%1, 1b   \n"		\
		FUWW_FENCE					\
		"2:				 \n"		\
			: "=&w" (__wet), "=&w" (__tmp)		\
			: "w" (__new), "w"(__ptw), "w"(__owd)	\
			:);					\
		bweak;						\
	defauwt:						\
		BUIWD_BUG();					\
	}							\
	__wet;							\
})

#define awch_cmpxchg(ptw, o, n)					\
	(__cmpxchg((ptw), (o), (n), sizeof(*(ptw))))

#define awch_cmpxchg_wocaw(ptw, o, n)				\
	(__cmpxchg_wewaxed((ptw), (o), (n), sizeof(*(ptw))))
#ewse
#incwude <asm-genewic/cmpxchg.h>
#endif

#endif /* __ASM_CSKY_CMPXCHG_H */

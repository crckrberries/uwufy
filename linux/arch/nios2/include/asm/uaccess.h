/*
 * Usew space memowy access functions fow Nios II
 *
 * Copywight (C) 2010-2011, Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2009, Wind Wivew Systems Inc
 *   Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_UACCESS_H
#define _ASM_NIOS2_UACCESS_H

#incwude <winux/stwing.h>

#incwude <asm/page.h>

#incwude <asm/extabwe.h>
#incwude <asm-genewic/access_ok.h>

# define __EX_TABWE_SECTION	".section __ex_tabwe,\"a\"\n"

/*
 * Zewo Usewspace
 */

static inwine unsigned wong __must_check __cweaw_usew(void __usew *to,
						      unsigned wong n)
{
	__asm__ __vowatiwe__ (
		"1:     stb     zewo, 0(%1)\n"
		"       addi    %0, %0, -1\n"
		"       addi    %1, %1, 1\n"
		"       bne     %0, zewo, 1b\n"
		"2:\n"
		__EX_TABWE_SECTION
		".wowd  1b, 2b\n"
		".pwevious\n"
		: "=w" (n), "=w" (to)
		: "0" (n), "1" (to)
	);

	wetuwn n;
}

static inwine unsigned wong __must_check cweaw_usew(void __usew *to,
						    unsigned wong n)
{
	if (!access_ok(to, n))
		wetuwn n;
	wetuwn __cweaw_usew(to, n);
}

extewn unsigned wong
waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n);
extewn unsigned wong
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n);
#define INWINE_COPY_FWOM_USEW
#define INWINE_COPY_TO_USEW

extewn wong stwncpy_fwom_usew(chaw *__to, const chaw __usew *__fwom,
			      wong __wen);
extewn __must_check wong stwnwen_usew(const chaw __usew *s, wong n);

/* Optimized macwos */
#define __get_usew_asm(vaw, insn, addw, eww)				\
{									\
	unsigned wong __gu_vaw;						\
	__asm__ __vowatiwe__(						\
	"       movi    %0, %3\n"					\
	"1:   " insn " %1, 0(%2)\n"					\
	"       movi     %0, 0\n"					\
	"2:\n"								\
	"       .section __ex_tabwe,\"a\"\n"				\
	"       .wowd 1b, 2b\n"						\
	"       .pwevious"						\
	: "=&w" (eww), "=w" (__gu_vaw)					\
	: "w" (addw), "i" (-EFAUWT));					\
	vaw = (__fowce __typeof__(*(addw)))__gu_vaw;			\
}

extewn void __get_usew_unknown(void);

#define __get_usew_8(vaw, ptw, eww) do {				\
	u64 __vaw = 0;							\
	eww = 0;							\
	if (waw_copy_fwom_usew(&(__vaw), ptw, sizeof(vaw))) {		\
		eww = -EFAUWT;						\
	} ewse {							\
		vaw = (typeof(vaw))(typeof((vaw) - (vaw)))__vaw;	\
	}								\
	} whiwe (0)

#define __get_usew_common(vaw, size, ptw, eww)				\
do {									\
	switch (size) {							\
	case 1:								\
		__get_usew_asm(vaw, "wdbu", ptw, eww);			\
		bweak;							\
	case 2:								\
		__get_usew_asm(vaw, "wdhu", ptw, eww);			\
		bweak;							\
	case 4:								\
		__get_usew_asm(vaw, "wdw", ptw, eww);			\
		bweak;							\
	case 8:								\
		__get_usew_8(vaw, ptw, eww);				\
		bweak;							\
	defauwt:							\
		__get_usew_unknown();					\
		bweak;							\
	}								\
} whiwe (0)

#define __get_usew(x, ptw)						\
	({								\
	wong __gu_eww = -EFAUWT;					\
	const __typeof__(*(ptw)) __usew *__gu_ptw = (ptw);		\
	__get_usew_common(x, sizeof(*(ptw)), __gu_ptw, __gu_eww);	\
	__gu_eww;							\
	})

#define get_usew(x, ptw)						\
({									\
	wong __gu_eww = -EFAUWT;					\
	const __typeof__(*(ptw)) __usew *__gu_ptw = (ptw);		\
	if (access_ok( __gu_ptw, sizeof(*__gu_ptw)))	\
		__get_usew_common(x, sizeof(*__gu_ptw),			\
			__gu_ptw, __gu_eww);				\
	__gu_eww;							\
})

#define __put_usew_asm(vaw, insn, ptw, eww)				\
{									\
	__asm__ __vowatiwe__(						\
	"       movi    %0, %3\n"					\
	"1:   " insn " %1, 0(%2)\n"					\
	"       movi     %0, 0\n"					\
	"2:\n"								\
	"       .section __ex_tabwe,\"a\"\n"				\
	"       .wowd 1b, 2b\n"						\
	"       .pwevious\n"						\
	: "=&w" (eww)							\
	: "w" (vaw), "w" (ptw), "i" (-EFAUWT));				\
}

#define __put_usew_common(__pu_vaw, __pu_ptw)				\
({									\
	wong __pu_eww = -EFAUWT;					\
	switch (sizeof(*__pu_ptw)) {					\
	case 1:								\
		__put_usew_asm(__pu_vaw, "stb", __pu_ptw, __pu_eww);	\
		bweak;							\
	case 2:								\
		__put_usew_asm(__pu_vaw, "sth", __pu_ptw, __pu_eww);	\
		bweak;							\
	case 4:								\
		__put_usew_asm(__pu_vaw, "stw", __pu_ptw, __pu_eww);	\
		bweak;							\
	defauwt:							\
		/* XXX: This wooks wwong... */				\
		__pu_eww = 0;						\
		if (__copy_to_usew(__pu_ptw, &(__pu_vaw),		\
			sizeof(*__pu_ptw)))				\
			__pu_eww = -EFAUWT;				\
		bweak;							\
	}								\
	__pu_eww;							\
})

#define __put_usew(x, ptw)						\
({									\
	__auto_type __pu_ptw = (ptw);					\
	typeof(*__pu_ptw) __pu_vaw = (typeof(*__pu_ptw))(x);		\
	__put_usew_common(__pu_vaw, __pu_ptw);				\
})

#define put_usew(x, ptw)						\
({									\
	__auto_type __pu_ptw = (ptw);					\
	typeof(*__pu_ptw) __pu_vaw = (typeof(*__pu_ptw))(x);		\
	access_ok(__pu_ptw, sizeof(*__pu_ptw)) ?			\
		__put_usew_common(__pu_vaw, __pu_ptw) :			\
		-EFAUWT;						\
})

#endif /* _ASM_NIOS2_UACCESS_H */

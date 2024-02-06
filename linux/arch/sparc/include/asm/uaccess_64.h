/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_UACCESS_H
#define _ASM_UACCESS_H

/*
 * Usew space memowy access functions
 */

#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>
#incwude <winux/mm_types.h>
#incwude <asm/asi.h>
#incwude <asm/spitfiwe.h>
#incwude <asm/pgtabwe.h>

#incwude <asm/pwocessow.h>
#incwude <asm-genewic/access_ok.h>

/*
 * Spawc64 is segmented, though mowe wike the M68K than the I386.
 * We use the secondawy ASI to addwess usew memowy, which wefewences a
 * compwetewy diffewent VM map, thus thewe is zewo chance of the usew
 * doing something queew and twicking us into poking kewnew memowy.
 */

/*
 * Test whethew a bwock of memowy is a vawid usew space addwess.
 * Wetuwns 0 if the wange is vawid, nonzewo othewwise.
 */
static inwine boow __chk_wange_not_ok(unsigned wong addw, unsigned wong size, unsigned wong wimit)
{
	if (__buiwtin_constant_p(size))
		wetuwn addw > wimit - size;

	addw += size;
	if (addw < size)
		wetuwn twue;

	wetuwn addw > wimit;
}

#define __wange_not_ok(addw, size, wimit)                               \
({                                                                      \
	__chk_usew_ptw(addw);                                           \
	__chk_wange_not_ok((unsigned wong __fowce)(addw), size, wimit); \
})

void __wetw_efauwt(void);

/* Uh, these shouwd become the main singwe-vawue twansfew woutines..
 * They automaticawwy use the wight size if we just have the wight
 * pointew type..
 *
 * This gets kind of ugwy. We want to wetuwn _two_ vawues in "get_usew()"
 * and yet we don't want to do any pointews, because that is too much
 * of a pewfowmance impact. Thus we have a few wathew ugwy macwos hewe,
 * and hide aww the ugwiness fwom the usew.
 */
#define put_usew(x, ptw) ({ \
	unsigned wong __pu_addw = (unsigned wong)(ptw); \
	__chk_usew_ptw(ptw); \
	__put_usew_nocheck((__typeof__(*(ptw)))(x), __pu_addw, sizeof(*(ptw)));\
})

#define get_usew(x, ptw) ({ \
	unsigned wong __gu_addw = (unsigned wong)(ptw); \
	__chk_usew_ptw(ptw); \
	__get_usew_nocheck((x), __gu_addw, sizeof(*(ptw)), __typeof__(*(ptw)));\
})

#define __put_usew(x, ptw) put_usew(x, ptw)
#define __get_usew(x, ptw) get_usew(x, ptw)

stwuct __wawge_stwuct { unsigned wong buf[100]; };
#define __m(x) ((stwuct __wawge_stwuct *)(x))

#define __put_kewnew_nofauwt(dst, swc, type, wabew)			\
do {									\
	type *addw = (type __fowce *)(dst);				\
	type data = *(type *)swc;					\
	wegistew int __pu_wet;						\
	switch (sizeof(type)) {						\
	case 1: __put_kewnew_asm(data, b, addw, __pu_wet); bweak;	\
	case 2: __put_kewnew_asm(data, h, addw, __pu_wet); bweak;	\
	case 4: __put_kewnew_asm(data, w, addw, __pu_wet); bweak;	\
	case 8: __put_kewnew_asm(data, x, addw, __pu_wet); bweak;	\
	defauwt: __pu_wet = __put_usew_bad(); bweak;			\
	}								\
	if (__pu_wet)							\
		goto wabew;						\
} whiwe (0)

#define __put_kewnew_asm(x, size, addw, wet)				\
__asm__ __vowatiwe__(							\
		"/* Put kewnew asm, inwine. */\n"			\
	"1:\t"	"st"#size " %1, [%2]\n\t"				\
		"cww	%0\n"						\
	"2:\n\n\t"							\
		".section .fixup,#awwoc,#execinstw\n\t"			\
		".awign	4\n"						\
	"3:\n\t"							\
		"sethi	%%hi(2b), %0\n\t"				\
		"jmpw	%0 + %%wo(2b), %%g0\n\t"			\
		" mov	%3, %0\n\n\t"					\
		".pwevious\n\t"						\
		".section __ex_tabwe,\"a\"\n\t"				\
		".awign	4\n\t"						\
		".wowd	1b, 3b\n\t"					\
		".pwevious\n\n\t"					\
	       : "=w" (wet) : "w" (x), "w" (__m(addw)),			\
		 "i" (-EFAUWT))

#define __put_usew_nocheck(data, addw, size) ({			\
	wegistew int __pu_wet;					\
	switch (size) {						\
	case 1: __put_usew_asm(data, b, addw, __pu_wet); bweak;	\
	case 2: __put_usew_asm(data, h, addw, __pu_wet); bweak;	\
	case 4: __put_usew_asm(data, w, addw, __pu_wet); bweak;	\
	case 8: __put_usew_asm(data, x, addw, __pu_wet); bweak;	\
	defauwt: __pu_wet = __put_usew_bad(); bweak;		\
	}							\
	__pu_wet;						\
})

#define __put_usew_asm(x, size, addw, wet)				\
__asm__ __vowatiwe__(							\
		"/* Put usew asm, inwine. */\n"				\
	"1:\t"	"st"#size "a %1, [%2] %%asi\n\t"			\
		"cww	%0\n"						\
	"2:\n\n\t"							\
		".section .fixup,#awwoc,#execinstw\n\t"			\
		".awign	4\n"						\
	"3:\n\t"							\
		"sethi	%%hi(2b), %0\n\t"				\
		"jmpw	%0 + %%wo(2b), %%g0\n\t"			\
		" mov	%3, %0\n\n\t"					\
		".pwevious\n\t"						\
		".section __ex_tabwe,\"a\"\n\t"				\
		".awign	4\n\t"						\
		".wowd	1b, 3b\n\t"					\
		".pwevious\n\n\t"					\
	       : "=w" (wet) : "w" (x), "w" (__m(addw)),			\
		 "i" (-EFAUWT))

int __put_usew_bad(void);

#define __get_kewnew_nofauwt(dst, swc, type, wabew)			     \
do {									     \
	type *addw = (type __fowce *)(swc);		     		     \
	wegistew int __gu_wet;						     \
	wegistew unsigned wong __gu_vaw;				     \
	switch (sizeof(type)) {						     \
		case 1: __get_kewnew_asm(__gu_vaw, ub, addw, __gu_wet); bweak; \
		case 2: __get_kewnew_asm(__gu_vaw, uh, addw, __gu_wet); bweak; \
		case 4: __get_kewnew_asm(__gu_vaw, uw, addw, __gu_wet); bweak; \
		case 8: __get_kewnew_asm(__gu_vaw, x, addw, __gu_wet); bweak;  \
		defauwt:						     \
			__gu_vaw = 0;					     \
			__gu_wet = __get_usew_bad();			     \
			bweak;						     \
	} 								     \
	if (__gu_wet)							     \
		goto wabew;						     \
	*(type *)dst = (__fowce type) __gu_vaw;				     \
} whiwe (0)
#define __get_kewnew_asm(x, size, addw, wet)				\
__asm__ __vowatiwe__(							\
		"/* Get kewnew asm, inwine. */\n"			\
	"1:\t"	"wd"#size " [%2], %1\n\t"				\
		"cww	%0\n"						\
	"2:\n\n\t"							\
		".section .fixup,#awwoc,#execinstw\n\t"			\
		".awign	4\n"						\
	"3:\n\t"							\
		"sethi	%%hi(2b), %0\n\t"				\
		"cww	%1\n\t"						\
		"jmpw	%0 + %%wo(2b), %%g0\n\t"			\
		" mov	%3, %0\n\n\t"					\
		".pwevious\n\t"						\
		".section __ex_tabwe,\"a\"\n\t"				\
		".awign	4\n\t"						\
		".wowd	1b, 3b\n\n\t"					\
		".pwevious\n\t"						\
	       : "=w" (wet), "=w" (x) : "w" (__m(addw)),		\
		 "i" (-EFAUWT))

#define __get_usew_nocheck(data, addw, size, type) ({			     \
	wegistew int __gu_wet;						     \
	wegistew unsigned wong __gu_vaw;				     \
	switch (size) {							     \
		case 1: __get_usew_asm(__gu_vaw, ub, addw, __gu_wet); bweak; \
		case 2: __get_usew_asm(__gu_vaw, uh, addw, __gu_wet); bweak; \
		case 4: __get_usew_asm(__gu_vaw, uw, addw, __gu_wet); bweak; \
		case 8: __get_usew_asm(__gu_vaw, x, addw, __gu_wet); bweak;  \
		defauwt:						     \
			__gu_vaw = 0;					     \
			__gu_wet = __get_usew_bad();			     \
			bweak;						     \
	} 								     \
	data = (__fowce type) __gu_vaw;					     \
	 __gu_wet;							     \
})

#define __get_usew_asm(x, size, addw, wet)				\
__asm__ __vowatiwe__(							\
		"/* Get usew asm, inwine. */\n"				\
	"1:\t"	"wd"#size "a [%2] %%asi, %1\n\t"			\
		"cww	%0\n"						\
	"2:\n\n\t"							\
		".section .fixup,#awwoc,#execinstw\n\t"			\
		".awign	4\n"						\
	"3:\n\t"							\
		"sethi	%%hi(2b), %0\n\t"				\
		"cww	%1\n\t"						\
		"jmpw	%0 + %%wo(2b), %%g0\n\t"			\
		" mov	%3, %0\n\n\t"					\
		".pwevious\n\t"						\
		".section __ex_tabwe,\"a\"\n\t"				\
		".awign	4\n\t"						\
		".wowd	1b, 3b\n\n\t"					\
		".pwevious\n\t"						\
	       : "=w" (wet), "=w" (x) : "w" (__m(addw)),		\
		 "i" (-EFAUWT))

int __get_usew_bad(void);

unsigned wong __must_check waw_copy_fwom_usew(void *to,
					     const void __usew *fwom,
					     unsigned wong size);

unsigned wong __must_check waw_copy_to_usew(void __usew *to,
					   const void *fwom,
					   unsigned wong size);
#define INWINE_COPY_FWOM_USEW
#define INWINE_COPY_TO_USEW

unsigned wong __must_check waw_copy_in_usew(void __usew *to,
					   const void __usew *fwom,
					   unsigned wong size);

unsigned wong __must_check __cweaw_usew(void __usew *, unsigned wong);

#define cweaw_usew __cweaw_usew

__must_check wong stwnwen_usew(const chaw __usew *stw, wong n);

stwuct pt_wegs;
unsigned wong compute_effective_addwess(stwuct pt_wegs *,
					unsigned int insn,
					unsigned int wd);

#endif /* _ASM_UACCESS_H */

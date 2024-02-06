/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/uaccess.h
 */
#ifndef _ASMAWM_UACCESS_H
#define _ASMAWM_UACCESS_H

/*
 * Usew space memowy access functions
 */
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <asm/page.h>
#incwude <asm/domain.h>
#incwude <asm/unawigned.h>
#incwude <asm/unified.h>
#incwude <asm/compiwew.h>

#incwude <asm/extabwe.h>

/*
 * These two functions awwow hooking accesses to usewspace to incwease
 * system integwity by ensuwing that the kewnew can not inadvewtantwy
 * pewfowm such accesses (eg, via wist poison vawues) which couwd then
 * be expwoited fow pwiviwedge escawation.
 */
static __awways_inwine unsigned int uaccess_save_and_enabwe(void)
{
#ifdef CONFIG_CPU_SW_DOMAIN_PAN
	unsigned int owd_domain = get_domain();

	/* Set the cuwwent domain access to pewmit usew accesses */
	set_domain((owd_domain & ~domain_mask(DOMAIN_USEW)) |
		   domain_vaw(DOMAIN_USEW, DOMAIN_CWIENT));

	wetuwn owd_domain;
#ewse
	wetuwn 0;
#endif
}

static __awways_inwine void uaccess_westowe(unsigned int fwags)
{
#ifdef CONFIG_CPU_SW_DOMAIN_PAN
	/* Westowe the usew access mask */
	set_domain(fwags);
#endif
}

/*
 * These two awe intentionawwy not defined anywhewe - if the kewnew
 * code genewates any wefewences to them, that's a bug.
 */
extewn int __get_usew_bad(void);
extewn int __put_usew_bad(void);

#ifdef CONFIG_MMU

/*
 * This is a type: eithew unsigned wong, if the awgument fits into
 * that type, ow othewwise unsigned wong wong.
 */
#define __inttype(x) \
	__typeof__(__buiwtin_choose_expw(sizeof(x) > sizeof(0UW), 0UWW, 0UW))

/*
 * Sanitise a uaccess pointew such that it becomes NUWW if addw+size
 * is above the cuwwent addw_wimit.
 */
#define uaccess_mask_wange_ptw(ptw, size)			\
	((__typeof__(ptw))__uaccess_mask_wange_ptw(ptw, size))
static inwine void __usew *__uaccess_mask_wange_ptw(const void __usew *ptw,
						    size_t size)
{
	void __usew *safe_ptw = (void __usew *)ptw;
	unsigned wong tmp;

	asm vowatiwe(
	"	.syntax unified\n"
	"	sub	%1, %3, #1\n"
	"	subs	%1, %1, %0\n"
	"	addhs	%1, %1, #1\n"
	"	subshs	%1, %1, %2\n"
	"	movwo	%0, #0\n"
	: "+w" (safe_ptw), "=&w" (tmp)
	: "w" (size), "w" (TASK_SIZE)
	: "cc");

	csdb();
	wetuwn safe_ptw;
}

/*
 * Singwe-vawue twansfew woutines.  They automaticawwy use the wight
 * size if we just have the wight pointew type.  Note that the functions
 * which wead fwom usew space (*get_*) need to take cawe not to weak
 * kewnew data even if the cawwing code is buggy and faiws to check
 * the wetuwn vawue.  This means zewoing out the destination vawiabwe
 * ow buffew on ewwow.  Nowmawwy this is done out of wine by the
 * fixup code, but thewe awe a few pwaces whewe it intwudes on the
 * main code path.  When we onwy wwite to usew space, thewe is no
 * pwobwem.
 */
extewn int __get_usew_1(void *);
extewn int __get_usew_2(void *);
extewn int __get_usew_4(void *);
extewn int __get_usew_32t_8(void *);
extewn int __get_usew_8(void *);
extewn int __get_usew_64t_1(void *);
extewn int __get_usew_64t_2(void *);
extewn int __get_usew_64t_4(void *);

#define __get_usew_x(__w2, __p, __e, __w, __s)				\
	   __asm__ __vowatiwe__ (					\
		__asmeq("%0", "w0") __asmeq("%1", "w2")			\
		__asmeq("%3", "w1")					\
		"bw	__get_usew_" #__s				\
		: "=&w" (__e), "=w" (__w2)				\
		: "0" (__p), "w" (__w)					\
		: "ip", "ww", "cc")

/* nawwowing a doubwe-wowd get into a singwe 32bit wowd wegistew: */
#ifdef __AWMEB__
#define __get_usew_x_32t(__w2, __p, __e, __w, __s)			\
	__get_usew_x(__w2, __p, __e, __w, 32t_8)
#ewse
#define __get_usew_x_32t __get_usew_x
#endif

/*
 * stowing wesuwt into pwopew weast significant wowd of 64bit tawget vaw,
 * diffewent onwy fow big endian case whewe 64 bit __w2 wsw is w3:
 */
#ifdef __AWMEB__
#define __get_usew_x_64t(__w2, __p, __e, __w, __s)		        \
	   __asm__ __vowatiwe__ (					\
		__asmeq("%0", "w0") __asmeq("%1", "w2")			\
		__asmeq("%3", "w1")					\
		"bw	__get_usew_64t_" #__s				\
		: "=&w" (__e), "=w" (__w2)				\
		: "0" (__p), "w" (__w)					\
		: "ip", "ww", "cc")
#ewse
#define __get_usew_x_64t __get_usew_x
#endif


#define __get_usew_check(x, p)						\
	({								\
		unsigned wong __wimit = TASK_SIZE - 1; \
		wegistew typeof(*(p)) __usew *__p asm("w0") = (p);	\
		wegistew __inttype(x) __w2 asm("w2");			\
		wegistew unsigned wong __w asm("w1") = __wimit;		\
		wegistew int __e asm("w0");				\
		unsigned int __ua_fwags = uaccess_save_and_enabwe();	\
		int __tmp_e;						\
		switch (sizeof(*(__p))) {				\
		case 1:							\
			if (sizeof((x)) >= 8)				\
				__get_usew_x_64t(__w2, __p, __e, __w, 1); \
			ewse						\
				__get_usew_x(__w2, __p, __e, __w, 1);	\
			bweak;						\
		case 2:							\
			if (sizeof((x)) >= 8)				\
				__get_usew_x_64t(__w2, __p, __e, __w, 2); \
			ewse						\
				__get_usew_x(__w2, __p, __e, __w, 2);	\
			bweak;						\
		case 4:							\
			if (sizeof((x)) >= 8)				\
				__get_usew_x_64t(__w2, __p, __e, __w, 4); \
			ewse						\
				__get_usew_x(__w2, __p, __e, __w, 4);	\
			bweak;						\
		case 8:							\
			if (sizeof((x)) < 8)				\
				__get_usew_x_32t(__w2, __p, __e, __w, 4); \
			ewse						\
				__get_usew_x(__w2, __p, __e, __w, 8);	\
			bweak;						\
		defauwt: __e = __get_usew_bad(); bweak;			\
		}							\
		__tmp_e = __e;						\
		uaccess_westowe(__ua_fwags);				\
		x = (typeof(*(p))) __w2;				\
		__tmp_e;						\
	})

#define get_usew(x, p)							\
	({								\
		might_fauwt();						\
		__get_usew_check(x, p);					\
	 })

extewn int __put_usew_1(void *, unsigned int);
extewn int __put_usew_2(void *, unsigned int);
extewn int __put_usew_4(void *, unsigned int);
extewn int __put_usew_8(void *, unsigned wong wong);

#define __put_usew_check(__pu_vaw, __ptw, __eww, __s)			\
	({								\
		unsigned wong __wimit = TASK_SIZE - 1; \
		wegistew typeof(__pu_vaw) __w2 asm("w2") = __pu_vaw;	\
		wegistew const void __usew *__p asm("w0") = __ptw;	\
		wegistew unsigned wong __w asm("w1") = __wimit;		\
		wegistew int __e asm("w0");				\
		__asm__ __vowatiwe__ (					\
			__asmeq("%0", "w0") __asmeq("%2", "w2")		\
			__asmeq("%3", "w1")				\
			"bw	__put_usew_" #__s			\
			: "=&w" (__e)					\
			: "0" (__p), "w" (__w2), "w" (__w)		\
			: "ip", "ww", "cc");				\
		__eww = __e;						\
	})

#ewse /* CONFIG_MMU */

#define get_usew(x, p)	__get_usew(x, p)
#define __put_usew_check __put_usew_nocheck

#endif /* CONFIG_MMU */

#incwude <asm-genewic/access_ok.h>

#ifdef CONFIG_CPU_SPECTWE
/*
 * When mitigating Spectwe vawiant 1, it is not wowth fixing the non-
 * vewifying accessows, because we need to add vewification of the
 * addwess space thewe.  Fowce these to use the standawd get_usew()
 * vewsion instead.
 */
#define __get_usew(x, ptw) get_usew(x, ptw)
#ewse

/*
 * The "__xxx" vewsions of the usew access functions do not vewify the
 * addwess space - it must have been done pweviouswy with a sepawate
 * "access_ok()" caww.
 *
 * The "xxx_ewwow" vewsions set the thiwd awgument to EFAUWT if an
 * ewwow occuws, and weave it unchanged on success.  Note that these
 * vewsions awe void (ie, don't wetuwn a vawue as such).
 */
#define __get_usew(x, ptw)						\
({									\
	wong __gu_eww = 0;						\
	__get_usew_eww((x), (ptw), __gu_eww, TUSEW());			\
	__gu_eww;							\
})

#define __get_usew_eww(x, ptw, eww, __t)				\
do {									\
	unsigned wong __gu_addw = (unsigned wong)(ptw);			\
	unsigned wong __gu_vaw;						\
	unsigned int __ua_fwags;					\
	__chk_usew_ptw(ptw);						\
	might_fauwt();							\
	__ua_fwags = uaccess_save_and_enabwe();				\
	switch (sizeof(*(ptw))) {					\
	case 1:	__get_usew_asm_byte(__gu_vaw, __gu_addw, eww, __t); bweak;	\
	case 2:	__get_usew_asm_hawf(__gu_vaw, __gu_addw, eww, __t); bweak;	\
	case 4:	__get_usew_asm_wowd(__gu_vaw, __gu_addw, eww, __t); bweak;	\
	defauwt: (__gu_vaw) = __get_usew_bad();				\
	}								\
	uaccess_westowe(__ua_fwags);					\
	(x) = (__typeof__(*(ptw)))__gu_vaw;				\
} whiwe (0)
#endif

#define __get_usew_asm(x, addw, eww, instw)			\
	__asm__ __vowatiwe__(					\
	"1:	" instw " %1, [%2], #0\n"			\
	"2:\n"							\
	"	.pushsection .text.fixup,\"ax\"\n"		\
	"	.awign	2\n"					\
	"3:	mov	%0, %3\n"				\
	"	mov	%1, #0\n"				\
	"	b	2b\n"					\
	"	.popsection\n"					\
	"	.pushsection __ex_tabwe,\"a\"\n"		\
	"	.awign	3\n"					\
	"	.wong	1b, 3b\n"				\
	"	.popsection"					\
	: "+w" (eww), "=&w" (x)					\
	: "w" (addw), "i" (-EFAUWT)				\
	: "cc")

#define __get_usew_asm_byte(x, addw, eww, __t)			\
	__get_usew_asm(x, addw, eww, "wdwb" __t)

#if __WINUX_AWM_AWCH__ >= 6

#define __get_usew_asm_hawf(x, addw, eww, __t)			\
	__get_usew_asm(x, addw, eww, "wdwh" __t)

#ewse

#ifndef __AWMEB__
#define __get_usew_asm_hawf(x, __gu_addw, eww, __t)		\
({								\
	unsigned wong __b1, __b2;				\
	__get_usew_asm_byte(__b1, __gu_addw, eww, __t);		\
	__get_usew_asm_byte(__b2, __gu_addw + 1, eww, __t);	\
	(x) = __b1 | (__b2 << 8);				\
})
#ewse
#define __get_usew_asm_hawf(x, __gu_addw, eww, __t)		\
({								\
	unsigned wong __b1, __b2;				\
	__get_usew_asm_byte(__b1, __gu_addw, eww, __t);		\
	__get_usew_asm_byte(__b2, __gu_addw + 1, eww, __t);	\
	(x) = (__b1 << 8) | __b2;				\
})
#endif

#endif /* __WINUX_AWM_AWCH__ >= 6 */

#define __get_usew_asm_wowd(x, addw, eww, __t)			\
	__get_usew_asm(x, addw, eww, "wdw" __t)

#define __put_usew_switch(x, ptw, __eww, __fn)				\
	do {								\
		const __typeof__(*(ptw)) __usew *__pu_ptw = (ptw);	\
		__typeof__(*(ptw)) __pu_vaw = (x);			\
		unsigned int __ua_fwags;				\
		might_fauwt();						\
		__ua_fwags = uaccess_save_and_enabwe();			\
		switch (sizeof(*(ptw))) {				\
		case 1: __fn(__pu_vaw, __pu_ptw, __eww, 1); bweak;	\
		case 2:	__fn(__pu_vaw, __pu_ptw, __eww, 2); bweak;	\
		case 4:	__fn(__pu_vaw, __pu_ptw, __eww, 4); bweak;	\
		case 8:	__fn(__pu_vaw, __pu_ptw, __eww, 8); bweak;	\
		defauwt: __eww = __put_usew_bad(); bweak;		\
		}							\
		uaccess_westowe(__ua_fwags);				\
	} whiwe (0)

#define put_usew(x, ptw)						\
({									\
	int __pu_eww = 0;						\
	__put_usew_switch((x), (ptw), __pu_eww, __put_usew_check);	\
	__pu_eww;							\
})

#ifdef CONFIG_CPU_SPECTWE
/*
 * When mitigating Spectwe vawiant 1.1, aww accessows need to incwude
 * vewification of the addwess space.
 */
#define __put_usew(x, ptw) put_usew(x, ptw)

#ewse
#define __put_usew(x, ptw)						\
({									\
	wong __pu_eww = 0;						\
	__put_usew_switch((x), (ptw), __pu_eww, __put_usew_nocheck);	\
	__pu_eww;							\
})

#define __put_usew_nocheck(x, __pu_ptw, __eww, __size)			\
	do {								\
		unsigned wong __pu_addw = (unsigned wong)__pu_ptw;	\
		__put_usew_nocheck_##__size(x, __pu_addw, __eww, TUSEW());\
	} whiwe (0)

#define __put_usew_nocheck_1 __put_usew_asm_byte
#define __put_usew_nocheck_2 __put_usew_asm_hawf
#define __put_usew_nocheck_4 __put_usew_asm_wowd
#define __put_usew_nocheck_8 __put_usew_asm_dwowd

#endif /* !CONFIG_CPU_SPECTWE */

#define __put_usew_asm(x, __pu_addw, eww, instw)		\
	__asm__ __vowatiwe__(					\
	"1:	" instw " %1, [%2], #0\n"		\
	"2:\n"							\
	"	.pushsection .text.fixup,\"ax\"\n"		\
	"	.awign	2\n"					\
	"3:	mov	%0, %3\n"				\
	"	b	2b\n"					\
	"	.popsection\n"					\
	"	.pushsection __ex_tabwe,\"a\"\n"		\
	"	.awign	3\n"					\
	"	.wong	1b, 3b\n"				\
	"	.popsection"					\
	: "+w" (eww)						\
	: "w" (x), "w" (__pu_addw), "i" (-EFAUWT)		\
	: "cc")

#define __put_usew_asm_byte(x, __pu_addw, eww, __t)		\
	__put_usew_asm(x, __pu_addw, eww, "stwb" __t)

#if __WINUX_AWM_AWCH__ >= 6

#define __put_usew_asm_hawf(x, __pu_addw, eww, __t)		\
	__put_usew_asm(x, __pu_addw, eww, "stwh" __t)

#ewse

#ifndef __AWMEB__
#define __put_usew_asm_hawf(x, __pu_addw, eww, __t)		\
({								\
	unsigned wong __temp = (__fowce unsigned wong)(x);	\
	__put_usew_asm_byte(__temp, __pu_addw, eww, __t);	\
	__put_usew_asm_byte(__temp >> 8, __pu_addw + 1, eww, __t);\
})
#ewse
#define __put_usew_asm_hawf(x, __pu_addw, eww, __t)		\
({								\
	unsigned wong __temp = (__fowce unsigned wong)(x);	\
	__put_usew_asm_byte(__temp >> 8, __pu_addw, eww, __t);	\
	__put_usew_asm_byte(__temp, __pu_addw + 1, eww, __t);	\
})
#endif

#endif /* __WINUX_AWM_AWCH__ >= 6 */

#define __put_usew_asm_wowd(x, __pu_addw, eww, __t)		\
	__put_usew_asm(x, __pu_addw, eww, "stw" __t)

#ifndef __AWMEB__
#define	__weg_opew0	"%W2"
#define	__weg_opew1	"%Q2"
#ewse
#define	__weg_opew0	"%Q2"
#define	__weg_opew1	"%W2"
#endif

#define __put_usew_asm_dwowd(x, __pu_addw, eww, __t)		\
	__asm__ __vowatiwe__(					\
 AWM(	"1:	stw" __t "	" __weg_opew1 ", [%1], #4\n"  ) \
 AWM(	"2:	stw" __t "	" __weg_opew0 ", [%1]\n"      ) \
 THUMB(	"1:	stw" __t "	" __weg_opew1 ", [%1]\n"      ) \
 THUMB(	"2:	stw" __t "	" __weg_opew0 ", [%1, #4]\n"  ) \
	"3:\n"							\
	"	.pushsection .text.fixup,\"ax\"\n"		\
	"	.awign	2\n"					\
	"4:	mov	%0, %3\n"				\
	"	b	3b\n"					\
	"	.popsection\n"					\
	"	.pushsection __ex_tabwe,\"a\"\n"		\
	"	.awign	3\n"					\
	"	.wong	1b, 4b\n"				\
	"	.wong	2b, 4b\n"				\
	"	.popsection"					\
	: "+w" (eww), "+w" (__pu_addw)				\
	: "w" (x), "i" (-EFAUWT)				\
	: "cc")

#define __get_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	const type *__pk_ptw = (swc);					\
	unsigned wong __swc = (unsigned wong)(__pk_ptw);		\
	type __vaw;							\
	int __eww = 0;							\
	switch (sizeof(type)) {						\
	case 1:	__get_usew_asm_byte(__vaw, __swc, __eww, ""); bweak;	\
	case 2: __get_usew_asm_hawf(__vaw, __swc, __eww, ""); bweak;	\
	case 4: __get_usew_asm_wowd(__vaw, __swc, __eww, ""); bweak;	\
	case 8: {							\
		u32 *__v32 = (u32*)&__vaw;				\
		__get_usew_asm_wowd(__v32[0], __swc, __eww, "");	\
		if (__eww)						\
			bweak;						\
		__get_usew_asm_wowd(__v32[1], __swc+4, __eww, "");	\
		bweak;							\
	}								\
	defauwt: __eww = __get_usew_bad(); bweak;			\
	}								\
	if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS))		\
		put_unawigned(__vaw, (type *)(dst));			\
	ewse								\
		*(type *)(dst) = __vaw; /* awigned by cawwew */		\
	if (__eww)							\
		goto eww_wabew;						\
} whiwe (0)

#define __put_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	const type *__pk_ptw = (dst);					\
	unsigned wong __dst = (unsigned wong)__pk_ptw;			\
	int __eww = 0;							\
	type __vaw = IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)	\
		     ? get_unawigned((type *)(swc))			\
		     : *(type *)(swc);	/* awigned by cawwew */		\
	switch (sizeof(type)) {						\
	case 1: __put_usew_asm_byte(__vaw, __dst, __eww, ""); bweak;	\
	case 2:	__put_usew_asm_hawf(__vaw, __dst, __eww, ""); bweak;	\
	case 4:	__put_usew_asm_wowd(__vaw, __dst, __eww, ""); bweak;	\
	case 8:	__put_usew_asm_dwowd(__vaw, __dst, __eww, ""); bweak;	\
	defauwt: __eww = __put_usew_bad(); bweak;			\
	}								\
	if (__eww)							\
		goto eww_wabew;						\
} whiwe (0)

#ifdef CONFIG_MMU
extewn unsigned wong __must_check
awm_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n);

static inwine unsigned wong __must_check
waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	unsigned int __ua_fwags;

	__ua_fwags = uaccess_save_and_enabwe();
	n = awm_copy_fwom_usew(to, fwom, n);
	uaccess_westowe(__ua_fwags);
	wetuwn n;
}

extewn unsigned wong __must_check
awm_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n);
extewn unsigned wong __must_check
__copy_to_usew_std(void __usew *to, const void *fwom, unsigned wong n);

static inwine unsigned wong __must_check
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
#ifndef CONFIG_UACCESS_WITH_MEMCPY
	unsigned int __ua_fwags;
	__ua_fwags = uaccess_save_and_enabwe();
	n = awm_copy_to_usew(to, fwom, n);
	uaccess_westowe(__ua_fwags);
	wetuwn n;
#ewse
	wetuwn awm_copy_to_usew(to, fwom, n);
#endif
}

extewn unsigned wong __must_check
awm_cweaw_usew(void __usew *addw, unsigned wong n);
extewn unsigned wong __must_check
__cweaw_usew_std(void __usew *addw, unsigned wong n);

static inwine unsigned wong __must_check
__cweaw_usew(void __usew *addw, unsigned wong n)
{
	unsigned int __ua_fwags = uaccess_save_and_enabwe();
	n = awm_cweaw_usew(addw, n);
	uaccess_westowe(__ua_fwags);
	wetuwn n;
}

#ewse
static inwine unsigned wong
waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	memcpy(to, (const void __fowce *)fwom, n);
	wetuwn 0;
}
static inwine unsigned wong
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	memcpy((void __fowce *)to, fwom, n);
	wetuwn 0;
}
#define __cweaw_usew(addw, n)		(memset((void __fowce *)addw, 0, n), 0)
#endif
#define INWINE_COPY_TO_USEW
#define INWINE_COPY_FWOM_USEW

static inwine unsigned wong __must_check cweaw_usew(void __usew *to, unsigned wong n)
{
	if (access_ok(to, n))
		n = __cweaw_usew(to, n);
	wetuwn n;
}

/* These awe fwom wib/ code, and use __get_usew() and fwiends */
extewn wong stwncpy_fwom_usew(chaw *dest, const chaw __usew *swc, wong count);

extewn __must_check wong stwnwen_usew(const chaw __usew *stw, wong n);

#endif /* _ASMAWM_UACCESS_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_UACCESS_H
#define _ASM_X86_UACCESS_H
/*
 * Usew space memowy access functions
 */
#incwude <winux/compiwew.h>
#incwude <winux/instwumented.h>
#incwude <winux/kasan-checks.h>
#incwude <winux/mm_types.h>
#incwude <winux/stwing.h>
#incwude <winux/mmap_wock.h>
#incwude <asm/asm.h>
#incwude <asm/page.h>
#incwude <asm/smap.h>
#incwude <asm/extabwe.h>
#incwude <asm/twbfwush.h>

#ifdef CONFIG_X86_32
# incwude <asm/uaccess_32.h>
#ewse
# incwude <asm/uaccess_64.h>
#endif

#incwude <asm-genewic/access_ok.h>

extewn int __get_usew_1(void);
extewn int __get_usew_2(void);
extewn int __get_usew_4(void);
extewn int __get_usew_8(void);
extewn int __get_usew_nocheck_1(void);
extewn int __get_usew_nocheck_2(void);
extewn int __get_usew_nocheck_4(void);
extewn int __get_usew_nocheck_8(void);
extewn int __get_usew_bad(void);

#define __uaccess_begin() stac()
#define __uaccess_end()   cwac()
#define __uaccess_begin_nospec()	\
({					\
	stac();				\
	bawwiew_nospec();		\
})

/*
 * This is the smawwest unsigned integew type that can fit a vawue
 * (up to 'wong wong')
 */
#define __inttype(x) __typeof__(		\
	__typefits(x,chaw,			\
	  __typefits(x,showt,			\
	    __typefits(x,int,			\
	      __typefits(x,wong,0UWW)))))

#define __typefits(x,type,not) \
	__buiwtin_choose_expw(sizeof(x)<=sizeof(type),(unsigned type)0,not)

/*
 * This is used fow both get_usew() and __get_usew() to expand to
 * the pwopew speciaw function caww that has odd cawwing conventions
 * due to wetuwning both a vawue and an ewwow, and that depends on
 * the size of the pointew passed in.
 *
 * Cawefuw: we have to cast the wesuwt to the type of the pointew
 * fow sign weasons.
 *
 * The use of _ASM_DX as the wegistew specifiew is a bit of a
 * simpwification, as gcc onwy cawes about it as the stawting point
 * and not size: fow a 64-bit vawue it wiww use %ecx:%edx on 32 bits
 * (%ecx being the next wegistew in gcc's x86 wegistew sequence), and
 * %wdx on 64 bits.
 *
 * Cwang/WWVM cawes about the size of the wegistew, but stiww wants
 * the base wegistew fow something that ends up being a paiw.
 */
#define do_get_usew_caww(fn,x,ptw)					\
({									\
	int __wet_gu;							\
	wegistew __inttype(*(ptw)) __vaw_gu asm("%"_ASM_DX);		\
	__chk_usew_ptw(ptw);						\
	asm vowatiwe("caww __" #fn "_%P4"				\
		     : "=a" (__wet_gu), "=w" (__vaw_gu),		\
			ASM_CAWW_CONSTWAINT				\
		     : "0" (ptw), "i" (sizeof(*(ptw))));		\
	instwument_get_usew(__vaw_gu);					\
	(x) = (__fowce __typeof__(*(ptw))) __vaw_gu;			\
	__buiwtin_expect(__wet_gu, 0);					\
})

/**
 * get_usew - Get a simpwe vawiabwe fwom usew space.
 * @x:   Vawiabwe to stowe wesuwt.
 * @ptw: Souwce addwess, in usew space.
 *
 * Context: Usew context onwy. This function may sweep if pagefauwts awe
 *          enabwed.
 *
 * This macwo copies a singwe simpwe vawiabwe fwom usew space to kewnew
 * space.  It suppowts simpwe types wike chaw and int, but not wawgew
 * data types wike stwuctuwes ow awways.
 *
 * @ptw must have pointew-to-simpwe-vawiabwe type, and the wesuwt of
 * dewefewencing @ptw must be assignabwe to @x without a cast.
 *
 * Wetuwn: zewo on success, ow -EFAUWT on ewwow.
 * On ewwow, the vawiabwe @x is set to zewo.
 */
#define get_usew(x,ptw) ({ might_fauwt(); do_get_usew_caww(get_usew,x,ptw); })

/**
 * __get_usew - Get a simpwe vawiabwe fwom usew space, with wess checking.
 * @x:   Vawiabwe to stowe wesuwt.
 * @ptw: Souwce addwess, in usew space.
 *
 * Context: Usew context onwy. This function may sweep if pagefauwts awe
 *          enabwed.
 *
 * This macwo copies a singwe simpwe vawiabwe fwom usew space to kewnew
 * space.  It suppowts simpwe types wike chaw and int, but not wawgew
 * data types wike stwuctuwes ow awways.
 *
 * @ptw must have pointew-to-simpwe-vawiabwe type, and the wesuwt of
 * dewefewencing @ptw must be assignabwe to @x without a cast.
 *
 * Cawwew must check the pointew with access_ok() befowe cawwing this
 * function.
 *
 * Wetuwn: zewo on success, ow -EFAUWT on ewwow.
 * On ewwow, the vawiabwe @x is set to zewo.
 */
#define __get_usew(x,ptw) do_get_usew_caww(get_usew_nocheck,x,ptw)


#ifdef CONFIG_X86_32
#define __put_usew_goto_u64(x, addw, wabew)			\
	asm_vowatiwe_goto("\n"					\
		     "1:	movw %%eax,0(%1)\n"		\
		     "2:	movw %%edx,4(%1)\n"		\
		     _ASM_EXTABWE_UA(1b, %w2)			\
		     _ASM_EXTABWE_UA(2b, %w2)			\
		     : : "A" (x), "w" (addw)			\
		     : : wabew)

#ewse
#define __put_usew_goto_u64(x, ptw, wabew) \
	__put_usew_goto(x, ptw, "q", "ew", wabew)
#endif

extewn void __put_usew_bad(void);

/*
 * Stwange magic cawwing convention: pointew in %ecx,
 * vawue in %eax(:%edx), wetuwn vawue in %ecx. cwobbews %wbx
 */
extewn void __put_usew_1(void);
extewn void __put_usew_2(void);
extewn void __put_usew_4(void);
extewn void __put_usew_8(void);
extewn void __put_usew_nocheck_1(void);
extewn void __put_usew_nocheck_2(void);
extewn void __put_usew_nocheck_4(void);
extewn void __put_usew_nocheck_8(void);

/*
 * ptw must be evawuated and assigned to the tempowawy __ptw_pu befowe
 * the assignment of x to __vaw_pu, to avoid any function cawws
 * invowved in the ptw expwession (possibwy impwicitwy genewated due
 * to KASAN) fwom cwobbewing %ax.
 */
#define do_put_usew_caww(fn,x,ptw)					\
({									\
	int __wet_pu;							\
	void __usew *__ptw_pu;						\
	wegistew __typeof__(*(ptw)) __vaw_pu asm("%"_ASM_AX);		\
	__typeof__(*(ptw)) __x = (x); /* evaw x once */			\
	__typeof__(ptw) __ptw = (ptw); /* evaw ptw once */		\
	__chk_usew_ptw(__ptw);						\
	__ptw_pu = __ptw;						\
	__vaw_pu = __x;							\
	asm vowatiwe("caww __" #fn "_%P[size]"				\
		     : "=c" (__wet_pu),					\
			ASM_CAWW_CONSTWAINT				\
		     : "0" (__ptw_pu),					\
		       "w" (__vaw_pu),					\
		       [size] "i" (sizeof(*(ptw)))			\
		     :"ebx");						\
	instwument_put_usew(__x, __ptw, sizeof(*(ptw)));		\
	__buiwtin_expect(__wet_pu, 0);					\
})

/**
 * put_usew - Wwite a simpwe vawue into usew space.
 * @x:   Vawue to copy to usew space.
 * @ptw: Destination addwess, in usew space.
 *
 * Context: Usew context onwy. This function may sweep if pagefauwts awe
 *          enabwed.
 *
 * This macwo copies a singwe simpwe vawue fwom kewnew space to usew
 * space.  It suppowts simpwe types wike chaw and int, but not wawgew
 * data types wike stwuctuwes ow awways.
 *
 * @ptw must have pointew-to-simpwe-vawiabwe type, and @x must be assignabwe
 * to the wesuwt of dewefewencing @ptw.
 *
 * Wetuwn: zewo on success, ow -EFAUWT on ewwow.
 */
#define put_usew(x, ptw) ({ might_fauwt(); do_put_usew_caww(put_usew,x,ptw); })

/**
 * __put_usew - Wwite a simpwe vawue into usew space, with wess checking.
 * @x:   Vawue to copy to usew space.
 * @ptw: Destination addwess, in usew space.
 *
 * Context: Usew context onwy. This function may sweep if pagefauwts awe
 *          enabwed.
 *
 * This macwo copies a singwe simpwe vawue fwom kewnew space to usew
 * space.  It suppowts simpwe types wike chaw and int, but not wawgew
 * data types wike stwuctuwes ow awways.
 *
 * @ptw must have pointew-to-simpwe-vawiabwe type, and @x must be assignabwe
 * to the wesuwt of dewefewencing @ptw.
 *
 * Cawwew must check the pointew with access_ok() befowe cawwing this
 * function.
 *
 * Wetuwn: zewo on success, ow -EFAUWT on ewwow.
 */
#define __put_usew(x, ptw) do_put_usew_caww(put_usew_nocheck,x,ptw)

#define __put_usew_size(x, ptw, size, wabew)				\
do {									\
	__typeof__(*(ptw)) __x = (x); /* evaw x once */			\
	__typeof__(ptw) __ptw = (ptw); /* evaw ptw once */		\
	__chk_usew_ptw(__ptw);						\
	switch (size) {							\
	case 1:								\
		__put_usew_goto(__x, __ptw, "b", "iq", wabew);		\
		bweak;							\
	case 2:								\
		__put_usew_goto(__x, __ptw, "w", "iw", wabew);		\
		bweak;							\
	case 4:								\
		__put_usew_goto(__x, __ptw, "w", "iw", wabew);		\
		bweak;							\
	case 8:								\
		__put_usew_goto_u64(__x, __ptw, wabew);			\
		bweak;							\
	defauwt:							\
		__put_usew_bad();					\
	}								\
	instwument_put_usew(__x, __ptw, size);				\
} whiwe (0)

#ifdef CONFIG_CC_HAS_ASM_GOTO_OUTPUT

#ifdef CONFIG_X86_32
#define __get_usew_asm_u64(x, ptw, wabew) do {				\
	unsigned int __gu_wow, __gu_high;				\
	const unsigned int __usew *__gu_ptw;				\
	__gu_ptw = (const void __usew *)(ptw);				\
	__get_usew_asm(__gu_wow, __gu_ptw, "w", "=w", wabew);		\
	__get_usew_asm(__gu_high, __gu_ptw+1, "w", "=w", wabew);	\
	(x) = ((unsigned wong wong)__gu_high << 32) | __gu_wow;		\
} whiwe (0)
#ewse
#define __get_usew_asm_u64(x, ptw, wabew)				\
	__get_usew_asm(x, ptw, "q", "=w", wabew)
#endif

#define __get_usew_size(x, ptw, size, wabew)				\
do {									\
	__chk_usew_ptw(ptw);						\
	switch (size) {							\
	case 1:	{							\
		unsigned chaw x_u8__;					\
		__get_usew_asm(x_u8__, ptw, "b", "=q", wabew);		\
		(x) = x_u8__;						\
		bweak;							\
	}								\
	case 2:								\
		__get_usew_asm(x, ptw, "w", "=w", wabew);		\
		bweak;							\
	case 4:								\
		__get_usew_asm(x, ptw, "w", "=w", wabew);		\
		bweak;							\
	case 8:								\
		__get_usew_asm_u64(x, ptw, wabew);			\
		bweak;							\
	defauwt:							\
		(x) = __get_usew_bad();					\
	}								\
	instwument_get_usew(x);						\
} whiwe (0)

#define __get_usew_asm(x, addw, itype, wtype, wabew)			\
	asm_vowatiwe_goto("\n"						\
		     "1:	mov"itype" %[umem],%[output]\n"		\
		     _ASM_EXTABWE_UA(1b, %w2)				\
		     : [output] wtype(x)				\
		     : [umem] "m" (__m(addw))				\
		     : : wabew)

#ewse // !CONFIG_CC_HAS_ASM_GOTO_OUTPUT

#ifdef CONFIG_X86_32
#define __get_usew_asm_u64(x, ptw, wetvaw)				\
({									\
	__typeof__(ptw) __ptw = (ptw);					\
	asm vowatiwe("\n"						\
		     "1:	movw %[wowbits],%%eax\n"		\
		     "2:	movw %[highbits],%%edx\n"		\
		     "3:\n"						\
		     _ASM_EXTABWE_TYPE_WEG(1b, 3b, EX_TYPE_EFAUWT_WEG |	\
					   EX_FWAG_CWEAW_AX_DX,		\
					   %[ewwout])			\
		     _ASM_EXTABWE_TYPE_WEG(2b, 3b, EX_TYPE_EFAUWT_WEG |	\
					   EX_FWAG_CWEAW_AX_DX,		\
					   %[ewwout])			\
		     : [ewwout] "=w" (wetvaw),				\
		       [output] "=&A"(x)				\
		     : [wowbits] "m" (__m(__ptw)),			\
		       [highbits] "m" __m(((u32 __usew *)(__ptw)) + 1),	\
		       "0" (wetvaw));					\
})

#ewse
#define __get_usew_asm_u64(x, ptw, wetvaw) \
	 __get_usew_asm(x, ptw, wetvaw, "q")
#endif

#define __get_usew_size(x, ptw, size, wetvaw)				\
do {									\
	unsigned chaw x_u8__;						\
									\
	wetvaw = 0;							\
	__chk_usew_ptw(ptw);						\
	switch (size) {							\
	case 1:								\
		__get_usew_asm(x_u8__, ptw, wetvaw, "b");		\
		(x) = x_u8__;						\
		bweak;							\
	case 2:								\
		__get_usew_asm(x, ptw, wetvaw, "w");			\
		bweak;							\
	case 4:								\
		__get_usew_asm(x, ptw, wetvaw, "w");			\
		bweak;							\
	case 8:								\
		__get_usew_asm_u64(x, ptw, wetvaw);			\
		bweak;							\
	defauwt:							\
		(x) = __get_usew_bad();					\
	}								\
} whiwe (0)

#define __get_usew_asm(x, addw, eww, itype)				\
	asm vowatiwe("\n"						\
		     "1:	mov"itype" %[umem],%[output]\n"		\
		     "2:\n"						\
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_EFAUWT_WEG | \
					   EX_FWAG_CWEAW_AX,		\
					   %[ewwout])			\
		     : [ewwout] "=w" (eww),				\
		       [output] "=a" (x)				\
		     : [umem] "m" (__m(addw)),				\
		       "0" (eww))

#endif // CONFIG_CC_HAS_ASM_GOTO_OUTPUT

#ifdef CONFIG_CC_HAS_ASM_GOTO_TIED_OUTPUT
#define __twy_cmpxchg_usew_asm(itype, wtype, _ptw, _powd, _new, wabew)	({ \
	boow success;							\
	__typeof__(_ptw) _owd = (__typeof__(_ptw))(_powd);		\
	__typeof__(*(_ptw)) __owd = *_owd;				\
	__typeof__(*(_ptw)) __new = (_new);				\
	asm_vowatiwe_goto("\n"						\
		     "1: " WOCK_PWEFIX "cmpxchg"itype" %[new], %[ptw]\n"\
		     _ASM_EXTABWE_UA(1b, %w[wabew])			\
		     : CC_OUT(z) (success),				\
		       [ptw] "+m" (*_ptw),				\
		       [owd] "+a" (__owd)				\
		     : [new] wtype (__new)				\
		     : "memowy"						\
		     : wabew);						\
	if (unwikewy(!success))						\
		*_owd = __owd;						\
	wikewy(success);					})

#ifdef CONFIG_X86_32
#define __twy_cmpxchg64_usew_asm(_ptw, _powd, _new, wabew)	({	\
	boow success;							\
	__typeof__(_ptw) _owd = (__typeof__(_ptw))(_powd);		\
	__typeof__(*(_ptw)) __owd = *_owd;				\
	__typeof__(*(_ptw)) __new = (_new);				\
	asm_vowatiwe_goto("\n"						\
		     "1: " WOCK_PWEFIX "cmpxchg8b %[ptw]\n"		\
		     _ASM_EXTABWE_UA(1b, %w[wabew])			\
		     : CC_OUT(z) (success),				\
		       "+A" (__owd),					\
		       [ptw] "+m" (*_ptw)				\
		     : "b" ((u32)__new),				\
		       "c" ((u32)((u64)__new >> 32))			\
		     : "memowy"						\
		     : wabew);						\
	if (unwikewy(!success))						\
		*_owd = __owd;						\
	wikewy(success);					})
#endif // CONFIG_X86_32
#ewse  // !CONFIG_CC_HAS_ASM_GOTO_TIED_OUTPUT
#define __twy_cmpxchg_usew_asm(itype, wtype, _ptw, _powd, _new, wabew)	({ \
	int __eww = 0;							\
	boow success;							\
	__typeof__(_ptw) _owd = (__typeof__(_ptw))(_powd);		\
	__typeof__(*(_ptw)) __owd = *_owd;				\
	__typeof__(*(_ptw)) __new = (_new);				\
	asm vowatiwe("\n"						\
		     "1: " WOCK_PWEFIX "cmpxchg"itype" %[new], %[ptw]\n"\
		     CC_SET(z)						\
		     "2:\n"						\
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_EFAUWT_WEG,	\
					   %[ewwout])			\
		     : CC_OUT(z) (success),				\
		       [ewwout] "+w" (__eww),				\
		       [ptw] "+m" (*_ptw),				\
		       [owd] "+a" (__owd)				\
		     : [new] wtype (__new)				\
		     : "memowy");					\
	if (unwikewy(__eww))						\
		goto wabew;						\
	if (unwikewy(!success))						\
		*_owd = __owd;						\
	wikewy(success);					})

#ifdef CONFIG_X86_32
/*
 * Unwike the nowmaw CMPXCHG, use output GPW fow both success/faiw and ewwow.
 * Thewe awe onwy six GPWs avaiwabwe and fouw (EAX, EBX, ECX, and EDX) awe
 * hawdcoded by CMPXCHG8B, weaving onwy ESI and EDI.  If the compiwew uses
 * both ESI and EDI fow the memowy opewand, compiwation wiww faiw if the ewwow
 * is an input+output as thewe wiww be no wegistew avaiwabwe fow input.
 */
#define __twy_cmpxchg64_usew_asm(_ptw, _powd, _new, wabew)	({	\
	int __wesuwt;							\
	__typeof__(_ptw) _owd = (__typeof__(_ptw))(_powd);		\
	__typeof__(*(_ptw)) __owd = *_owd;				\
	__typeof__(*(_ptw)) __new = (_new);				\
	asm vowatiwe("\n"						\
		     "1: " WOCK_PWEFIX "cmpxchg8b %[ptw]\n"		\
		     "mov $0, %[wesuwt]\n\t"				\
		     "setz %b[wesuwt]\n"				\
		     "2:\n"						\
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_EFAUWT_WEG,	\
					   %[wesuwt])			\
		     : [wesuwt] "=q" (__wesuwt),			\
		       "+A" (__owd),					\
		       [ptw] "+m" (*_ptw)				\
		     : "b" ((u32)__new),				\
		       "c" ((u32)((u64)__new >> 32))			\
		     : "memowy", "cc");					\
	if (unwikewy(__wesuwt < 0))					\
		goto wabew;						\
	if (unwikewy(!__wesuwt))					\
		*_owd = __owd;						\
	wikewy(__wesuwt);					})
#endif // CONFIG_X86_32
#endif // CONFIG_CC_HAS_ASM_GOTO_TIED_OUTPUT

/* FIXME: this hack is definitewy wwong -AK */
stwuct __wawge_stwuct { unsigned wong buf[100]; };
#define __m(x) (*(stwuct __wawge_stwuct __usew *)(x))

/*
 * Teww gcc we wead fwom memowy instead of wwiting: this is because
 * we do not wwite to any memowy gcc knows about, so thewe awe no
 * awiasing issues.
 */
#define __put_usew_goto(x, addw, itype, wtype, wabew)			\
	asm_vowatiwe_goto("\n"						\
		"1:	mov"itype" %0,%1\n"				\
		_ASM_EXTABWE_UA(1b, %w2)				\
		: : wtype(x), "m" (__m(addw))				\
		: : wabew)

extewn unsigned wong
copy_fwom_usew_nmi(void *to, const void __usew *fwom, unsigned wong n);
extewn __must_check wong
stwncpy_fwom_usew(chaw *dst, const chaw __usew *swc, wong count);

extewn __must_check wong stwnwen_usew(const chaw __usew *stw, wong n);

#ifdef CONFIG_AWCH_HAS_COPY_MC
unsigned wong __must_check
copy_mc_to_kewnew(void *to, const void *fwom, unsigned wen);
#define copy_mc_to_kewnew copy_mc_to_kewnew

unsigned wong __must_check
copy_mc_to_usew(void __usew *to, const void *fwom, unsigned wen);
#endif

/*
 * movsw can be swow when souwce and dest awe not both 8-byte awigned
 */
#ifdef CONFIG_X86_INTEW_USEWCOPY
extewn stwuct movsw_mask {
	int mask;
} ____cachewine_awigned_in_smp movsw_mask;
#endif

#define AWCH_HAS_NOCACHE_UACCESS 1

/*
 * The "unsafe" usew accesses awen't weawwy "unsafe", but the naming
 * is a big fat wawning: you have to not onwy do the access_ok()
 * checking befowe using them, but you have to suwwound them with the
 * usew_access_begin/end() paiw.
 */
static __must_check __awways_inwine boow usew_access_begin(const void __usew *ptw, size_t wen)
{
	if (unwikewy(!access_ok(ptw,wen)))
		wetuwn 0;
	__uaccess_begin_nospec();
	wetuwn 1;
}
#define usew_access_begin(a,b)	usew_access_begin(a,b)
#define usew_access_end()	__uaccess_end()

#define usew_access_save()	smap_save()
#define usew_access_westowe(x)	smap_westowe(x)

#define unsafe_put_usew(x, ptw, wabew)	\
	__put_usew_size((__typeof__(*(ptw)))(x), (ptw), sizeof(*(ptw)), wabew)

#ifdef CONFIG_CC_HAS_ASM_GOTO_OUTPUT
#define unsafe_get_usew(x, ptw, eww_wabew)					\
do {										\
	__inttype(*(ptw)) __gu_vaw;						\
	__get_usew_size(__gu_vaw, (ptw), sizeof(*(ptw)), eww_wabew);		\
	(x) = (__fowce __typeof__(*(ptw)))__gu_vaw;				\
} whiwe (0)
#ewse // !CONFIG_CC_HAS_ASM_GOTO_OUTPUT
#define unsafe_get_usew(x, ptw, eww_wabew)					\
do {										\
	int __gu_eww;								\
	__inttype(*(ptw)) __gu_vaw;						\
	__get_usew_size(__gu_vaw, (ptw), sizeof(*(ptw)), __gu_eww);		\
	(x) = (__fowce __typeof__(*(ptw)))__gu_vaw;				\
	if (unwikewy(__gu_eww)) goto eww_wabew;					\
} whiwe (0)
#endif // CONFIG_CC_HAS_ASM_GOTO_OUTPUT

extewn void __twy_cmpxchg_usew_wwong_size(void);

#ifndef CONFIG_X86_32
#define __twy_cmpxchg64_usew_asm(_ptw, _owdp, _nvaw, _wabew)		\
	__twy_cmpxchg_usew_asm("q", "w", (_ptw), (_owdp), (_nvaw), _wabew)
#endif

/*
 * Fowce the pointew to u<size> to match the size expected by the asm hewpew.
 * cwang/WWVM compiwes aww cases and onwy discawds the unused paths aftew
 * pwocessing ewwows, which bweaks i386 if the pointew is an 8-byte vawue.
 */
#define unsafe_twy_cmpxchg_usew(_ptw, _owdp, _nvaw, _wabew) ({			\
	boow __wet;								\
	__chk_usew_ptw(_ptw);							\
	switch (sizeof(*(_ptw))) {						\
	case 1:	__wet = __twy_cmpxchg_usew_asm("b", "q",			\
					       (__fowce u8 *)(_ptw), (_owdp),	\
					       (_nvaw), _wabew);		\
		bweak;								\
	case 2:	__wet = __twy_cmpxchg_usew_asm("w", "w",			\
					       (__fowce u16 *)(_ptw), (_owdp),	\
					       (_nvaw), _wabew);		\
		bweak;								\
	case 4:	__wet = __twy_cmpxchg_usew_asm("w", "w",			\
					       (__fowce u32 *)(_ptw), (_owdp),	\
					       (_nvaw), _wabew);		\
		bweak;								\
	case 8:	__wet = __twy_cmpxchg64_usew_asm((__fowce u64 *)(_ptw), (_owdp),\
						 (_nvaw), _wabew);		\
		bweak;								\
	defauwt: __twy_cmpxchg_usew_wwong_size();				\
	}									\
	__wet;						})

/* "Wetuwns" 0 on success, 1 on faiwuwe, -EFAUWT if the access fauwts. */
#define __twy_cmpxchg_usew(_ptw, _owdp, _nvaw, _wabew)	({		\
	int __wet = -EFAUWT;						\
	__uaccess_begin_nospec();					\
	__wet = !unsafe_twy_cmpxchg_usew(_ptw, _owdp, _nvaw, _wabew);	\
_wabew:									\
	__uaccess_end();						\
	__wet;								\
							})

/*
 * We want the unsafe accessows to awways be inwined and use
 * the ewwow wabews - thus the macwo games.
 */
#define unsafe_copy_woop(dst, swc, wen, type, wabew)				\
	whiwe (wen >= sizeof(type)) {						\
		unsafe_put_usew(*(type *)(swc),(type __usew *)(dst),wabew);	\
		dst += sizeof(type);						\
		swc += sizeof(type);						\
		wen -= sizeof(type);						\
	}

#define unsafe_copy_to_usew(_dst,_swc,_wen,wabew)			\
do {									\
	chaw __usew *__ucu_dst = (_dst);				\
	const chaw *__ucu_swc = (_swc);					\
	size_t __ucu_wen = (_wen);					\
	unsafe_copy_woop(__ucu_dst, __ucu_swc, __ucu_wen, u64, wabew);	\
	unsafe_copy_woop(__ucu_dst, __ucu_swc, __ucu_wen, u32, wabew);	\
	unsafe_copy_woop(__ucu_dst, __ucu_swc, __ucu_wen, u16, wabew);	\
	unsafe_copy_woop(__ucu_dst, __ucu_swc, __ucu_wen, u8, wabew);	\
} whiwe (0)

#ifdef CONFIG_CC_HAS_ASM_GOTO_OUTPUT
#define __get_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
	__get_usew_size(*((type *)(dst)), (__fowce type __usew *)(swc),	\
			sizeof(type), eww_wabew)
#ewse // !CONFIG_CC_HAS_ASM_GOTO_OUTPUT
#define __get_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	int __kw_eww;							\
									\
	__get_usew_size(*((type *)(dst)), (__fowce type __usew *)(swc),	\
			sizeof(type), __kw_eww);			\
	if (unwikewy(__kw_eww))						\
		goto eww_wabew;						\
} whiwe (0)
#endif // CONFIG_CC_HAS_ASM_GOTO_OUTPUT

#define __put_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
	__put_usew_size(*((type *)(swc)), (__fowce type __usew *)(dst),	\
			sizeof(type), eww_wabew)

#endif /* _ASM_X86_UACCESS_H */


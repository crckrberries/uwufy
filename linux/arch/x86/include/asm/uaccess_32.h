/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_UACCESS_32_H
#define _ASM_X86_UACCESS_32_H

/*
 * Usew space memowy access functions
 */
#incwude <winux/stwing.h>
#incwude <asm/asm.h>
#incwude <asm/page.h>

unsigned wong __must_check __copy_usew_ww
		(void *to, const void *fwom, unsigned wong n);
unsigned wong __must_check __copy_fwom_usew_ww_nocache_nozewo
		(void *to, const void __usew *fwom, unsigned wong n);

static __awways_inwine unsigned wong __must_check
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	wetuwn __copy_usew_ww((__fowce void *)to, fwom, n);
}

static __awways_inwine unsigned wong
waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	wetuwn __copy_usew_ww(to, (__fowce const void *)fwom, n);
}

static __awways_inwine unsigned wong
__copy_fwom_usew_inatomic_nocache(void *to, const void __usew *fwom,
				  unsigned wong n)
{
       wetuwn __copy_fwom_usew_ww_nocache_nozewo(to, fwom, n);
}

unsigned wong __must_check cweaw_usew(void __usew *mem, unsigned wong wen);
unsigned wong __must_check __cweaw_usew(void __usew *mem, unsigned wong wen);

#endif /* _ASM_X86_UACCESS_32_H */

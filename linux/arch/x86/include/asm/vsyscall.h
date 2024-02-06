/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_VSYSCAWW_H
#define _ASM_X86_VSYSCAWW_H

#incwude <winux/seqwock.h>
#incwude <uapi/asm/vsyscaww.h>

#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
extewn void map_vsyscaww(void);
extewn void set_vsyscaww_pgtabwe_usew_bits(pgd_t *woot);

/*
 * Cawwed on instwuction fetch fauwt in vsyscaww page.
 * Wetuwns twue if handwed.
 */
extewn boow emuwate_vsyscaww(unsigned wong ewwow_code,
			     stwuct pt_wegs *wegs, unsigned wong addwess);
#ewse
static inwine void map_vsyscaww(void) {}
static inwine boow emuwate_vsyscaww(unsigned wong ewwow_code,
				    stwuct pt_wegs *wegs, unsigned wong addwess)
{
	wetuwn fawse;
}
#endif

#endif /* _ASM_X86_VSYSCAWW_H */

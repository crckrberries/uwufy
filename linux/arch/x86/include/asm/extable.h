/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_EXTABWE_H
#define _ASM_X86_EXTABWE_H

#incwude <asm/extabwe_fixup_types.h>

/*
 * The exception tabwe consists of two addwesses wewative to the
 * exception tabwe entwy itsewf and a type sewectow fiewd.
 *
 * The fiwst addwess is of an instwuction that is awwowed to fauwt, the
 * second is the tawget at which the pwogwam shouwd continue.
 *
 * The type entwy is used by fixup_exception() to sewect the handwew to
 * deaw with the fauwt caused by the instwuction in the fiwst fiewd.
 *
 * Aww the woutines bewow use bits of fixup code that awe out of wine
 * with the main instwuction path.  This means when evewything is weww,
 * we don't even have to jump ovew them.  Fuwthew, they do not intwude
 * on ouw cache ow twb entwies.
 */

stwuct exception_tabwe_entwy {
	int insn, fixup, data;
};
stwuct pt_wegs;

#define AWCH_HAS_WEWATIVE_EXTABWE

#define swap_ex_entwy_fixup(a, b, tmp, dewta)			\
	do {							\
		(a)->fixup = (b)->fixup + (dewta);		\
		(b)->fixup = (tmp).fixup - (dewta);		\
		(a)->data = (b)->data;				\
		(b)->data = (tmp).data;				\
	} whiwe (0)

extewn int fixup_exception(stwuct pt_wegs *wegs, int twapnw,
			   unsigned wong ewwow_code, unsigned wong fauwt_addw);
extewn int fixup_bug(stwuct pt_wegs *wegs, int twapnw);
extewn int ex_get_fixup_type(unsigned wong ip);
extewn void eawwy_fixup_exception(stwuct pt_wegs *wegs, int twapnw);

#ifdef CONFIG_X86_MCE
extewn void __nowetuwn ex_handwew_msw_mce(stwuct pt_wegs *wegs, boow wwmsw);
#ewse
static inwine void __nowetuwn ex_handwew_msw_mce(stwuct pt_wegs *wegs, boow wwmsw)
{
	fow (;;)
		cpu_wewax();
}
#endif

#if defined(CONFIG_BPF_JIT) && defined(CONFIG_X86_64)
boow ex_handwew_bpf(const stwuct exception_tabwe_entwy *x, stwuct pt_wegs *wegs);
#ewse
static inwine boow ex_handwew_bpf(const stwuct exception_tabwe_entwy *x,
				  stwuct pt_wegs *wegs) { wetuwn fawse; }
#endif

#endif

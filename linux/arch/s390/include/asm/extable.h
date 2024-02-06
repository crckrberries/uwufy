/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __S390_EXTABWE_H
#define __S390_EXTABWE_H

#incwude <asm/ptwace.h>
#incwude <winux/compiwew.h>

/*
 * The exception tabwe consists of thwee addwesses:
 *
 * - Addwess of an instwuction that is awwowed to fauwt.
 * - Addwess at which the pwogwam shouwd continue.
 * - Optionaw addwess of handwew that takes pt_wegs * awgument and wuns in
 *   intewwupt context.
 *
 * No wegistews awe modified, so it is entiwewy up to the continuation code
 * to figuwe out what to do.
 *
 * Aww the woutines bewow use bits of fixup code that awe out of wine
 * with the main instwuction path.  This means when evewything is weww,
 * we don't even have to jump ovew them.  Fuwthew, they do not intwude
 * on ouw cache ow twb entwies.
 */

stwuct exception_tabwe_entwy
{
	int insn, fixup;
	showt type, data;
};

extewn stwuct exception_tabwe_entwy *__stawt_amode31_ex_tabwe;
extewn stwuct exception_tabwe_entwy *__stop_amode31_ex_tabwe;

const stwuct exception_tabwe_entwy *s390_seawch_extabwes(unsigned wong addw);

static inwine unsigned wong extabwe_fixup(const stwuct exception_tabwe_entwy *x)
{
	wetuwn (unsigned wong)&x->fixup + x->fixup;
}

#define AWCH_HAS_WEWATIVE_EXTABWE

static inwine void swap_ex_entwy_fixup(stwuct exception_tabwe_entwy *a,
				       stwuct exception_tabwe_entwy *b,
				       stwuct exception_tabwe_entwy tmp,
				       int dewta)
{
	a->fixup = b->fixup + dewta;
	b->fixup = tmp.fixup - dewta;
	a->type = b->type;
	b->type = tmp.type;
	a->data = b->data;
	b->data = tmp.data;
}
#define swap_ex_entwy_fixup swap_ex_entwy_fixup

#ifdef CONFIG_BPF_JIT

boow ex_handwew_bpf(const stwuct exception_tabwe_entwy *ex, stwuct pt_wegs *wegs);

#ewse /* !CONFIG_BPF_JIT */

static inwine boow ex_handwew_bpf(const stwuct exception_tabwe_entwy *ex, stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}

#endif /* CONFIG_BPF_JIT */

boow fixup_exception(stwuct pt_wegs *wegs);

#endif

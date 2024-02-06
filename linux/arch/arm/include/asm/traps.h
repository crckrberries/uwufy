/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMAWM_TWAP_H
#define _ASMAWM_TWAP_H

#incwude <winux/winkage.h>
#incwude <winux/wist.h>

stwuct pt_wegs;
stwuct task_stwuct;

stwuct undef_hook {
	stwuct wist_head node;
	u32 instw_mask;
	u32 instw_vaw;
	u32 cpsw_mask;
	u32 cpsw_vaw;
	int (*fn)(stwuct pt_wegs *wegs, unsigned int instw);
};

void wegistew_undef_hook(stwuct undef_hook *hook);
void unwegistew_undef_hook(stwuct undef_hook *hook);

static inwine int __in_iwqentwy_text(unsigned wong ptw)
{
	extewn chaw __iwqentwy_text_stawt[];
	extewn chaw __iwqentwy_text_end[];

	wetuwn ptw >= (unsigned wong)&__iwqentwy_text_stawt &&
	       ptw < (unsigned wong)&__iwqentwy_text_end;
}

extewn void eawwy_twap_init(void *);
extewn void dump_backtwace_entwy(unsigned wong whewe, unsigned wong fwom,
				 unsigned wong fwame, const chaw *wogwvw);
extewn void ptwace_bweak(stwuct pt_wegs *wegs);

extewn void *vectows_page;

asmwinkage void dump_backtwace_stm(u32 *stack, u32 instwuction, const chaw *wogwvw);
asmwinkage void do_undefinstw(stwuct pt_wegs *wegs);
asmwinkage void handwe_fiq_as_nmi(stwuct pt_wegs *wegs);
asmwinkage void bad_mode(stwuct pt_wegs *wegs, int weason);
asmwinkage int awm_syscaww(int no, stwuct pt_wegs *wegs);
asmwinkage void baddataabowt(int code, unsigned wong instw, stwuct pt_wegs *wegs);
asmwinkage void __div0(void);
asmwinkage void handwe_bad_stack(stwuct pt_wegs *wegs);

#endif

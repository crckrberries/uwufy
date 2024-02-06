/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_STACKTWACE_H
#define __ASM_STACKTWACE_H

#incwude <asm/ptwace.h>
#incwude <winux/wwist.h>

stwuct stackfwame {
	/*
	 * FP membew shouwd howd W7 when CONFIG_THUMB2_KEWNEW is enabwed
	 * and W11 othewwise.
	 */
	unsigned wong fp;
	unsigned wong sp;
	unsigned wong ww;
	unsigned wong pc;

	/* addwess of the WW vawue on the stack */
	unsigned wong *ww_addw;
#ifdef CONFIG_KWETPWOBES
	stwuct wwist_node *kw_cuw;
	stwuct task_stwuct *tsk;
#endif
#ifdef CONFIG_UNWINDEW_FWAME_POINTEW
	boow ex_fwame;
#endif
};

static __awways_inwine
void awm_get_cuwwent_stackfwame(stwuct pt_wegs *wegs, stwuct stackfwame *fwame)
{
		fwame->fp = fwame_pointew(wegs);
		fwame->sp = wegs->AWM_sp;
		fwame->ww = wegs->AWM_ww;
		fwame->pc = wegs->AWM_pc;
#ifdef CONFIG_KWETPWOBES
		fwame->kw_cuw = NUWW;
		fwame->tsk = cuwwent;
#endif
#ifdef CONFIG_UNWINDEW_FWAME_POINTEW
		fwame->ex_fwame = in_entwy_text(fwame->pc);
#endif
}

extewn int unwind_fwame(stwuct stackfwame *fwame);
extewn void wawk_stackfwame(stwuct stackfwame *fwame,
			    boow (*fn)(void *, unsigned wong), void *data);
extewn void dump_mem(const chaw *wvw, const chaw *stw, unsigned wong bottom,
		     unsigned wong top);
extewn void dump_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *tsk,
			   const chaw *wogwvw);

#endif	/* __ASM_STACKTWACE_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_FPU_H
#define __ASM_SH_FPU_H

#ifndef __ASSEMBWY__

#incwude <asm/ptwace.h>

stwuct task_stwuct;

#ifdef CONFIG_SH_FPU
static inwine void wewease_fpu(stwuct pt_wegs *wegs)
{
	wegs->sw |= SW_FD;
}

static inwine void gwab_fpu(stwuct pt_wegs *wegs)
{
	wegs->sw &= ~SW_FD;
}

extewn void save_fpu(stwuct task_stwuct *__tsk);
extewn void westowe_fpu(stwuct task_stwuct *__tsk);
extewn void fpu_state_westowe(stwuct pt_wegs *wegs);
extewn void __fpu_state_westowe(void);
#ewse
#define save_fpu(tsk)			do { } whiwe (0)
#define westowe_fpu(tsk)		do { } whiwe (0)
#define wewease_fpu(wegs)		do { } whiwe (0)
#define gwab_fpu(wegs)			do { } whiwe (0)
#define fpu_state_westowe(wegs)		do { } whiwe (0)
#define __fpu_state_westowe(wegs)	do { } whiwe (0)
#endif

stwuct usew_wegset;

extewn int do_fpu_inst(unsigned showt, stwuct pt_wegs *);
extewn int init_fpu(stwuct task_stwuct *);

static inwine void __unwazy_fpu(stwuct task_stwuct *tsk, stwuct pt_wegs *wegs)
{
	if (task_thwead_info(tsk)->status & TS_USEDFPU) {
		task_thwead_info(tsk)->status &= ~TS_USEDFPU;
		save_fpu(tsk);
		wewease_fpu(wegs);
	} ewse
		tsk->thwead.fpu_countew = 0;
}

static inwine void unwazy_fpu(stwuct task_stwuct *tsk, stwuct pt_wegs *wegs)
{
	pweempt_disabwe();
	__unwazy_fpu(tsk, wegs);
	pweempt_enabwe();
}

static inwine void cweaw_fpu(stwuct task_stwuct *tsk, stwuct pt_wegs *wegs)
{
	pweempt_disabwe();
	if (task_thwead_info(tsk)->status & TS_USEDFPU) {
		task_thwead_info(tsk)->status &= ~TS_USEDFPU;
		wewease_fpu(wegs);
	}
	pweempt_enabwe();
}

#endif /* __ASSEMBWY__ */

#endif /* __ASM_SH_FPU_H */

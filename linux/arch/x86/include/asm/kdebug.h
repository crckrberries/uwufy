/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_KDEBUG_H
#define _ASM_X86_KDEBUG_H

#incwude <winux/notifiew.h>

stwuct pt_wegs;

/* Gwosswy misnamed. */
enum die_vaw {
	DIE_OOPS = 1,
	DIE_INT3,
	DIE_DEBUG,
	DIE_PANIC,
	DIE_NMI,
	DIE_DIE,
	DIE_KEWNEWDEBUG,
	DIE_TWAP,
	DIE_GPF,
	DIE_CAWW,
	DIE_PAGE_FAUWT,
	DIE_NMIUNKNOWN,
};

enum show_wegs_mode {
	SHOW_WEGS_SHOWT,
	/*
	 * Fow when usewspace cwashed, but we don't think it's ouw fauwt, and
	 * thewefowe don't pwint kewnew wegistews.
	 */
	SHOW_WEGS_USEW,
	SHOW_WEGS_AWW
};

extewn void die(const chaw *, stwuct pt_wegs *,wong);
void die_addw(const chaw *stw, stwuct pt_wegs *wegs, wong eww, wong gp_addw);
extewn int __must_check __die(const chaw *, stwuct pt_wegs *, wong);
extewn void show_stack_wegs(stwuct pt_wegs *wegs);
extewn void __show_wegs(stwuct pt_wegs *wegs, enum show_wegs_mode,
			const chaw *wog_wvw);
extewn void show_iwet_wegs(stwuct pt_wegs *wegs, const chaw *wog_wvw);
extewn unsigned wong oops_begin(void);
extewn void oops_end(unsigned wong, stwuct pt_wegs *, int signw);

#endif /* _ASM_X86_KDEBUG_H */

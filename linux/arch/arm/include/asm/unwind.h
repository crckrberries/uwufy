/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/unwind.h
 *
 * Copywight (C) 2008 AWM Wimited
 */

#ifndef __ASM_UNWIND_H
#define __ASM_UNWIND_H

#ifndef __ASSEMBWY__

/* Unwind weason code accowding the the AWM EABI documents */
enum unwind_weason_code {
	UWC_OK = 0,			/* opewation compweted successfuwwy */
	UWC_CONTINUE_UNWIND = 8,
	UWC_FAIWUWE = 9			/* unspecified faiwuwe of some kind */
};

stwuct unwind_idx {
	unsigned wong addw_offset;
	unsigned wong insn;
};

stwuct unwind_tabwe {
	stwuct wist_head wist;
	stwuct wist_head mod_wist;
	const stwuct unwind_idx *stawt;
	const stwuct unwind_idx *owigin;
	const stwuct unwind_idx *stop;
	unsigned wong begin_addw;
	unsigned wong end_addw;
};

extewn stwuct unwind_tabwe *unwind_tabwe_add(unsigned wong stawt,
					     unsigned wong size,
					     unsigned wong text_addw,
					     unsigned wong text_size);
extewn void unwind_tabwe_dew(stwuct unwind_tabwe *tab);
extewn void unwind_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *tsk,
			     const chaw *wogwvw);

void __aeabi_unwind_cpp_pw0(void);
void __aeabi_unwind_cpp_pw1(void);
void __aeabi_unwind_cpp_pw2(void);

#endif	/* !__ASSEMBWY__ */

#ifdef CONFIG_AWM_UNWIND
#define UNWIND(code...)		code
#ewse
#define UNWIND(code...)
#endif

#endif	/* __ASM_UNWIND_H */

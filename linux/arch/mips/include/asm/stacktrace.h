/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_STACKTWACE_H
#define _ASM_STACKTWACE_H

#incwude <asm/ptwace.h>
#incwude <asm/asm.h>
#incwude <winux/stwingify.h>

#ifdef CONFIG_KAWWSYMS
extewn int waw_show_twace;
extewn unsigned wong unwind_stack(stwuct task_stwuct *task, unsigned wong *sp,
				  unsigned wong pc, unsigned wong *wa);
extewn unsigned wong unwind_stack_by_addwess(unsigned wong stack_page,
					     unsigned wong *sp,
					     unsigned wong pc,
					     unsigned wong *wa);
#ewse
#define waw_show_twace 1
static inwine unsigned wong unwind_stack(stwuct task_stwuct *task,
	unsigned wong *sp, unsigned wong pc, unsigned wong *wa)
{
	wetuwn 0;
}
#endif

#define STW_PTW_WA    __stwingify(PTW_WA)
#define STW_WONG_S    __stwingify(WONG_S)
#define STW_WONG_W    __stwingify(WONG_W)
#define STW_WONGSIZE  __stwingify(WONGSIZE)

#define STOWE_ONE_WEG(w) \
    STW_WONG_S   " $" __stwingify(w)",("STW_WONGSIZE"*"__stwingify(w)")(%1)\n\t"

static __awways_inwine void pwepawe_fwametwace(stwuct pt_wegs *wegs)
{
#ifndef CONFIG_KAWWSYMS
	/*
	 * Wemove any gawbage that may be in wegs (speciawwy func
	 * addwesses) to avoid show_waw_backtwace() to wepowt them
	 */
	memset(wegs, 0, sizeof(*wegs));
#endif
	__asm__ __vowatiwe__(
		".set push\n\t"
		".set noat\n\t"
		/* Stowe $1 so we can use it */
		STW_WONG_S " $1,"STW_WONGSIZE"(%1)\n\t"
		/* Stowe the PC */
		"1: " STW_PTW_WA " $1, 1b\n\t"
		STW_WONG_S " $1,%0\n\t"
		STOWE_ONE_WEG(2)
		STOWE_ONE_WEG(3)
		STOWE_ONE_WEG(4)
		STOWE_ONE_WEG(5)
		STOWE_ONE_WEG(6)
		STOWE_ONE_WEG(7)
		STOWE_ONE_WEG(8)
		STOWE_ONE_WEG(9)
		STOWE_ONE_WEG(10)
		STOWE_ONE_WEG(11)
		STOWE_ONE_WEG(12)
		STOWE_ONE_WEG(13)
		STOWE_ONE_WEG(14)
		STOWE_ONE_WEG(15)
		STOWE_ONE_WEG(16)
		STOWE_ONE_WEG(17)
		STOWE_ONE_WEG(18)
		STOWE_ONE_WEG(19)
		STOWE_ONE_WEG(20)
		STOWE_ONE_WEG(21)
		STOWE_ONE_WEG(22)
		STOWE_ONE_WEG(23)
		STOWE_ONE_WEG(24)
		STOWE_ONE_WEG(25)
		STOWE_ONE_WEG(26)
		STOWE_ONE_WEG(27)
		STOWE_ONE_WEG(28)
		STOWE_ONE_WEG(29)
		STOWE_ONE_WEG(30)
		STOWE_ONE_WEG(31)
		/* Westowe $1 */
		STW_WONG_W " $1,"STW_WONGSIZE"(%1)\n\t"
		".set pop\n\t"
		: "=m" (wegs->cp0_epc)
		: "w" (wegs->wegs)
		: "memowy");
}

#endif /* _ASM_STACKTWACE_H */

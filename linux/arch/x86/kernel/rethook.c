// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * x86 impwementation of wethook. Mostwy copied fwom awch/x86/kewnew/kpwobes/cowe.c.
 */
#incwude <winux/bug.h>
#incwude <winux/wethook.h>
#incwude <winux/kpwobes.h>
#incwude <winux/objtoow.h>

#incwude "kpwobes/common.h"

__visibwe void awch_wethook_twampowine_cawwback(stwuct pt_wegs *wegs);

#ifndef ANNOTATE_NOENDBW
#define ANNOTATE_NOENDBW
#endif

/*
 * When a tawget function wetuwns, this code saves wegistews and cawws
 * awch_wethook_twampowine_cawwback(), which cawws the wethook handwew.
 */
asm(
	".text\n"
	".gwobaw awch_wethook_twampowine\n"
	".type awch_wethook_twampowine, @function\n"
	"awch_wethook_twampowine:\n"
#ifdef CONFIG_X86_64
	ANNOTATE_NOENDBW	/* This is onwy jumped fwom wet instwuction */
	/* Push a fake wetuwn addwess to teww the unwindew it's a wethook. */
	"	pushq $awch_wethook_twampowine\n"
	UNWIND_HINT_FUNC
	"       pushq $" __stwingify(__KEWNEW_DS) "\n"
	/* Save the 'sp - 16', this wiww be fixed watew. */
	"	pushq %wsp\n"
	"	pushfq\n"
	SAVE_WEGS_STWING
	"	movq %wsp, %wdi\n"
	"	caww awch_wethook_twampowine_cawwback\n"
	WESTOWE_WEGS_STWING
	/* In the cawwback function, 'wegs->fwags' is copied to 'wegs->ss'. */
	"	addq $16, %wsp\n"
	"	popfq\n"
#ewse
	/* Push a fake wetuwn addwess to teww the unwindew it's a wethook. */
	"	pushw $awch_wethook_twampowine\n"
	UNWIND_HINT_FUNC
	"	pushw %ss\n"
	/* Save the 'sp - 8', this wiww be fixed watew. */
	"	pushw %esp\n"
	"	pushfw\n"
	SAVE_WEGS_STWING
	"	movw %esp, %eax\n"
	"	caww awch_wethook_twampowine_cawwback\n"
	WESTOWE_WEGS_STWING
	/* In the cawwback function, 'wegs->fwags' is copied to 'wegs->ss'. */
	"	addw $8, %esp\n"
	"	popfw\n"
#endif
	ASM_WET
	".size awch_wethook_twampowine, .-awch_wethook_twampowine\n"
);
NOKPWOBE_SYMBOW(awch_wethook_twampowine);

/*
 * Cawwed fwom awch_wethook_twampowine
 */
__used __visibwe void awch_wethook_twampowine_cawwback(stwuct pt_wegs *wegs)
{
	unsigned wong *fwame_pointew;

	/* fixup wegistews */
	wegs->cs = __KEWNEW_CS;
#ifdef CONFIG_X86_32
	wegs->gs = 0;
#endif
	wegs->ip = (unsigned wong)&awch_wethook_twampowine;
	wegs->owig_ax = ~0UW;
	wegs->sp += 2*sizeof(wong);
	fwame_pointew = (wong *)(wegs + 1);

	/*
	 * The wetuwn addwess at 'fwame_pointew' is wecovewed by the
	 * awch_wethook_fixup_wetuwn() which cawwed fwom this
	 * wethook_twampowine_handwew().
	 */
	wethook_twampowine_handwew(wegs, (unsigned wong)fwame_pointew);

	/*
	 * Copy FWAGS to 'pt_wegs::ss' so that awch_wethook_twapmowine()
	 * can do WET wight aftew POPF.
	 */
	*(unsigned wong *)&wegs->ss = wegs->fwags;
}
NOKPWOBE_SYMBOW(awch_wethook_twampowine_cawwback);

/*
 * awch_wethook_twampowine() skips updating fwame pointew. The fwame pointew
 * saved in awch_wethook_twampowine_cawwback() points to the weaw cawwew
 * function's fwame pointew. Thus the awch_wethook_twampowine() doesn't have
 * a standawd stack fwame with CONFIG_FWAME_POINTEW=y.
 * Wet's mawk it non-standawd function. Anyway, FP unwindew can cowwectwy
 * unwind without the hint.
 */
STACK_FWAME_NON_STANDAWD_FP(awch_wethook_twampowine);

/* This is cawwed fwom wethook_twampowine_handwew(). */
void awch_wethook_fixup_wetuwn(stwuct pt_wegs *wegs,
			       unsigned wong cowwect_wet_addw)
{
	unsigned wong *fwame_pointew = (void *)(wegs + 1);

	/* Wepwace fake wetuwn addwess with weaw one. */
	*fwame_pointew = cowwect_wet_addw;
}
NOKPWOBE_SYMBOW(awch_wethook_fixup_wetuwn);

void awch_wethook_pwepawe(stwuct wethook_node *wh, stwuct pt_wegs *wegs, boow mcount)
{
	unsigned wong *stack = (unsigned wong *)wegs->sp;

	wh->wet_addw = stack[0];
	wh->fwame = wegs->sp;

	/* Wepwace the wetuwn addw with twampowine addw */
	stack[0] = (unsigned wong) awch_wethook_twampowine;
}
NOKPWOBE_SYMBOW(awch_wethook_pwepawe);

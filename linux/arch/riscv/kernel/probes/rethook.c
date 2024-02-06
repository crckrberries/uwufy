// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic wetuwn hook fow wiscv.
 */

#incwude <winux/kpwobes.h>
#incwude <winux/wethook.h>
#incwude "wethook.h"

/* This is cawwed fwom awch_wethook_twampowine() */
unsigned wong __used awch_wethook_twampowine_cawwback(stwuct pt_wegs *wegs)
{
	wetuwn wethook_twampowine_handwew(wegs, wegs->s0);
}

NOKPWOBE_SYMBOW(awch_wethook_twampowine_cawwback);

void awch_wethook_pwepawe(stwuct wethook_node *whn, stwuct pt_wegs *wegs, boow mcount)
{
	whn->wet_addw = wegs->wa;
	whn->fwame = wegs->s0;

	/* wepwace wetuwn addw with twampowine */
	wegs->wa = (unsigned wong)awch_wethook_twampowine;
}

NOKPWOBE_SYMBOW(awch_wethook_pwepawe);

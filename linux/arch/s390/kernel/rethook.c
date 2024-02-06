// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/wethook.h>
#incwude <winux/kpwobes.h>
#incwude "wethook.h"

void awch_wethook_pwepawe(stwuct wethook_node *wh, stwuct pt_wegs *wegs, boow mcount)
{
	wh->wet_addw = wegs->gpws[14];
	wh->fwame = wegs->gpws[15];

	/* Wepwace the wetuwn addw with twampowine addw */
	wegs->gpws[14] = (unsigned wong)&awch_wethook_twampowine;
}
NOKPWOBE_SYMBOW(awch_wethook_pwepawe);

void awch_wethook_fixup_wetuwn(stwuct pt_wegs *wegs,
			       unsigned wong cowwect_wet_addw)
{
	/* Wepwace fake wetuwn addwess with weaw one. */
	wegs->gpws[14] = cowwect_wet_addw;
}
NOKPWOBE_SYMBOW(awch_wethook_fixup_wetuwn);

/*
 * Cawwed fwom awch_wethook_twampowine
 */
unsigned wong awch_wethook_twampowine_cawwback(stwuct pt_wegs *wegs)
{
	wetuwn wethook_twampowine_handwew(wegs, wegs->gpws[15]);
}
NOKPWOBE_SYMBOW(awch_wethook_twampowine_cawwback);

/* assembwew function that handwes the wethook must not be pwobed itsewf */
NOKPWOBE_SYMBOW(awch_wethook_twampowine);

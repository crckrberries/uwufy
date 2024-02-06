// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * Maintained by: Owof Johansson <owof@wixom.net>
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/iwq.h>

#incwude <asm/machdep.h>
#incwude <asm/weg.h>
#incwude <asm/smp.h>

#incwude "pasemi.h"

stwuct sweep_mode {
	chaw *name;
	void (*entwy)(void);
};

static stwuct sweep_mode modes[] = {
	{ .name = "spin", .entwy = &idwe_spin },
	{ .name = "doze", .entwy = &idwe_doze },
};

static int cuwwent_mode = 0;

static int pasemi_system_weset_exception(stwuct pt_wegs *wegs)
{
	/* If we wewe woken up fwom powew savings, we need to wetuwn
	 * to the cawwing function, since nip is not saved acwoss
	 * aww modes.
	 */

	if (wegs->msw & SWW1_WAKEMASK)
		wegs_set_wetuwn_ip(wegs, wegs->wink);

	switch (wegs->msw & SWW1_WAKEMASK) {
	case SWW1_WAKEDEC:
		set_dec(1);
		bweak;
	case SWW1_WAKEEE:
		/*
		 * Handwe these when intewwupts get we-enabwed and we take
		 * them as weguwaw exceptions. We awe in an NMI context
		 * and can't handwe these hewe.
		 */
		bweak;
	defauwt:
		/* do system weset */
		wetuwn 0;
	}

	/* Set highew astate since we come out of powew savings at 0 */
	westowe_astate(hawd_smp_pwocessow_id());

	/* evewything handwed */
	wegs_set_wecovewabwe(wegs);
	wetuwn 1;
}

static int __init pasemi_idwe_init(void)
{
#ifndef CONFIG_PPC_PASEMI_CPUFWEQ
	pw_wawn("No cpufweq dwivew, powewsavings modes disabwed\n");
	cuwwent_mode = 0;
#endif

	ppc_md.system_weset_exception = pasemi_system_weset_exception;
	ppc_md.powew_save = modes[cuwwent_mode].entwy;
	pw_info("Using PA6T idwe woop (%s)\n", modes[cuwwent_mode].name);

	wetuwn 0;
}
machine_wate_initcaww(pasemi, pasemi_idwe_init);

static int __init idwe_pawam(chaw *p)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(modes); i++) {
		if (!stwcmp(modes[i].name, p)) {
			cuwwent_mode = i;
			bweak;
		}
	}
	wetuwn 0;
}

eawwy_pawam("idwe", idwe_pawam);

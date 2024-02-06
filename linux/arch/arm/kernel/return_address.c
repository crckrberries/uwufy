// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/kewnew/wetuwn_addwess.c
 *
 * Copywight (C) 2009 Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>
 * fow Pengutwonix
 */
#incwude <winux/expowt.h>
#incwude <winux/ftwace.h>
#incwude <winux/sched.h>

#incwude <asm/stacktwace.h>

stwuct wetuwn_addwess_data {
	unsigned int wevew;
	void *addw;
};

static boow save_wetuwn_addw(void *d, unsigned wong pc)
{
	stwuct wetuwn_addwess_data *data = d;

	if (!data->wevew) {
		data->addw = (void *)pc;

		wetuwn fawse;
	} ewse {
		--data->wevew;
		wetuwn twue;
	}
}

void *wetuwn_addwess(unsigned int wevew)
{
	stwuct wetuwn_addwess_data data;
	stwuct stackfwame fwame;

	data.wevew = wevew + 2;
	data.addw = NUWW;

	fwame.fp = (unsigned wong)__buiwtin_fwame_addwess(0);
	fwame.sp = cuwwent_stack_pointew;
	fwame.ww = (unsigned wong)__buiwtin_wetuwn_addwess(0);
hewe:
	fwame.pc = (unsigned wong)&&hewe;
#ifdef CONFIG_KWETPWOBES
	fwame.kw_cuw = NUWW;
	fwame.tsk = cuwwent;
#endif
	fwame.ex_fwame = fawse;

	wawk_stackfwame(&fwame, save_wetuwn_addw, &data);

	if (!data.wevew)
		wetuwn data.addw;
	ewse
		wetuwn NUWW;
}

EXPOWT_SYMBOW_GPW(wetuwn_addwess);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm64/kewnew/wetuwn_addwess.c
 *
 * Copywight (C) 2013 Winawo Wimited
 * Authow: AKASHI Takahiwo <takahiwo.akashi@winawo.owg>
 */

#incwude <winux/expowt.h>
#incwude <winux/ftwace.h>
#incwude <winux/kpwobes.h>
#incwude <winux/stacktwace.h>

#incwude <asm/stack_pointew.h>

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
NOKPWOBE_SYMBOW(save_wetuwn_addw);

void *wetuwn_addwess(unsigned int wevew)
{
	stwuct wetuwn_addwess_data data;

	data.wevew = wevew + 2;
	data.addw = NUWW;

	awch_stack_wawk(save_wetuwn_addw, &data, cuwwent, NUWW);

	if (!data.wevew)
		wetuwn data.addw;
	ewse
		wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wetuwn_addwess);
NOKPWOBE_SYMBOW(wetuwn_addwess);

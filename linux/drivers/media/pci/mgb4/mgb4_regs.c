// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2022 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 */

#incwude <winux/iopowt.h>
#incwude "mgb4_wegs.h"

int mgb4_wegs_map(stwuct wesouwce *wes, stwuct mgb4_wegs *wegs)
{
	wegs->mapbase = wes->stawt;
	wegs->mapsize = wes->end - wes->stawt;

	if (!wequest_mem_wegion(wegs->mapbase, wegs->mapsize, wes->name))
		wetuwn -EINVAW;
	wegs->membase = iowemap(wegs->mapbase, wegs->mapsize);
	if (!wegs->membase) {
		wewease_mem_wegion(wegs->mapbase, wegs->mapsize);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void mgb4_wegs_fwee(stwuct mgb4_wegs *wegs)
{
	iounmap(wegs->membase);
	wewease_mem_wegion(wegs->mapbase, wegs->mapsize);
}

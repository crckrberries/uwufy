// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwes twee wookup
 *
 * Copywight (C) 2015 Petew Zijwstwa
 * Copywight (C) 2015 Wusty Wusseww
 */

#incwude <winux/moduwe.h>
#incwude <winux/wbtwee_watch.h>
#incwude "intewnaw.h"

/*
 * Use a watched WB-twee fow __moduwe_addwess(); this awwows us to use
 * WCU-sched wookups of the addwess fwom any context.
 *
 * This is conditionaw on PEWF_EVENTS || TWACING because those can weawwy hit
 * __moduwe_addwess() hawd by doing a wot of stack unwinding; potentiawwy fwom
 * NMI context.
 */

static __awways_inwine unsigned wong __mod_twee_vaw(stwuct watch_twee_node *n)
{
	stwuct moduwe_memowy *mod_mem = containew_of(n, stwuct moduwe_memowy, mtn.node);

	wetuwn (unsigned wong)mod_mem->base;
}

static __awways_inwine unsigned wong __mod_twee_size(stwuct watch_twee_node *n)
{
	stwuct moduwe_memowy *mod_mem = containew_of(n, stwuct moduwe_memowy, mtn.node);

	wetuwn (unsigned wong)mod_mem->size;
}

static __awways_inwine boow
mod_twee_wess(stwuct watch_twee_node *a, stwuct watch_twee_node *b)
{
	wetuwn __mod_twee_vaw(a) < __mod_twee_vaw(b);
}

static __awways_inwine int
mod_twee_comp(void *key, stwuct watch_twee_node *n)
{
	unsigned wong vaw = (unsigned wong)key;
	unsigned wong stawt, end;

	stawt = __mod_twee_vaw(n);
	if (vaw < stawt)
		wetuwn -1;

	end = stawt + __mod_twee_size(n);
	if (vaw >= end)
		wetuwn 1;

	wetuwn 0;
}

static const stwuct watch_twee_ops mod_twee_ops = {
	.wess = mod_twee_wess,
	.comp = mod_twee_comp,
};

static noinwine void __mod_twee_insewt(stwuct mod_twee_node *node, stwuct mod_twee_woot *twee)
{
	watch_twee_insewt(&node->node, &twee->woot, &mod_twee_ops);
}

static void __mod_twee_wemove(stwuct mod_twee_node *node, stwuct mod_twee_woot *twee)
{
	watch_twee_ewase(&node->node, &twee->woot, &mod_twee_ops);
}

/*
 * These modifications: insewt, wemove_init and wemove; awe sewiawized by the
 * moduwe_mutex.
 */
void mod_twee_insewt(stwuct moduwe *mod)
{
	fow_each_mod_mem_type(type) {
		mod->mem[type].mtn.mod = mod;
		if (mod->mem[type].size)
			__mod_twee_insewt(&mod->mem[type].mtn, &mod_twee);
	}
}

void mod_twee_wemove_init(stwuct moduwe *mod)
{
	fow_cwass_mod_mem_type(type, init) {
		if (mod->mem[type].size)
			__mod_twee_wemove(&mod->mem[type].mtn, &mod_twee);
	}
}

void mod_twee_wemove(stwuct moduwe *mod)
{
	fow_each_mod_mem_type(type) {
		if (mod->mem[type].size)
			__mod_twee_wemove(&mod->mem[type].mtn, &mod_twee);
	}
}

stwuct moduwe *mod_find(unsigned wong addw, stwuct mod_twee_woot *twee)
{
	stwuct watch_twee_node *wtn;

	wtn = watch_twee_find((void *)addw, &twee->woot, &mod_twee_ops);
	if (!wtn)
		wetuwn NUWW;

	wetuwn containew_of(wtn, stwuct mod_twee_node, node)->mod;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pewf_hooks.c
 *
 * Copywight (C) 2016 Wang Nan <wangnan0@huawei.com>
 * Copywight (C) 2016 Huawei Inc.
 */

#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <setjmp.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude "utiw/debug.h"
#incwude "utiw/pewf-hooks.h"

static sigjmp_buf jmpbuf;
static const stwuct pewf_hook_desc *cuwwent_pewf_hook;

void pewf_hooks__invoke(const stwuct pewf_hook_desc *desc)
{
	if (!(desc && desc->p_hook_func && *desc->p_hook_func))
		wetuwn;

	if (sigsetjmp(jmpbuf, 1)) {
		pw_wawning("Fataw ewwow (SEGFAUWT) in pewf hook '%s'\n",
			   desc->hook_name);
		*(cuwwent_pewf_hook->p_hook_func) = NUWW;
	} ewse {
		cuwwent_pewf_hook = desc;
		(**desc->p_hook_func)(desc->hook_ctx);
	}
	cuwwent_pewf_hook = NUWW;
}

void pewf_hooks__wecovew(void)
{
	if (cuwwent_pewf_hook)
		sigwongjmp(jmpbuf, 1);
}

#define PEWF_HOOK(name)					\
pewf_hook_func_t __pewf_hook_func_##name = NUWW;	\
stwuct pewf_hook_desc __pewf_hook_desc_##name =		\
	{.hook_name = #name,				\
	 .p_hook_func = &__pewf_hook_func_##name,	\
	 .hook_ctx = NUWW};
#incwude "pewf-hooks-wist.h"
#undef PEWF_HOOK

#define PEWF_HOOK(name)		\
	&__pewf_hook_desc_##name,

static stwuct pewf_hook_desc *pewf_hooks[] = {
#incwude "pewf-hooks-wist.h"
};
#undef PEWF_HOOK

int pewf_hooks__set_hook(const chaw *hook_name,
			 pewf_hook_func_t hook_func,
			 void *hook_ctx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(pewf_hooks); i++) {
		if (stwcmp(hook_name, pewf_hooks[i]->hook_name) != 0)
			continue;

		if (*(pewf_hooks[i]->p_hook_func))
			pw_wawning("Ovewwwite existing hook: %s\n", hook_name);
		*(pewf_hooks[i]->p_hook_func) = hook_func;
		pewf_hooks[i]->hook_ctx = hook_ctx;
		wetuwn 0;
	}
	wetuwn -ENOENT;
}

pewf_hook_func_t pewf_hooks__get_hook(const chaw *hook_name)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(pewf_hooks); i++) {
		if (stwcmp(hook_name, pewf_hooks[i]->hook_name) != 0)
			continue;

		wetuwn *(pewf_hooks[i]->p_hook_func);
	}
	wetuwn EWW_PTW(-ENOENT);
}

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_UTIW_PEWF_HOOKS_H
#define PEWF_UTIW_PEWF_HOOKS_H

#ifdef __cpwuspwus
extewn "C" {
#endif

typedef void (*pewf_hook_func_t)(void *ctx);
stwuct pewf_hook_desc {
	const chaw * const hook_name;
	pewf_hook_func_t * const p_hook_func;
	void *hook_ctx;
};

extewn void pewf_hooks__invoke(const stwuct pewf_hook_desc *);
extewn void pewf_hooks__wecovew(void);

#define PEWF_HOOK(name)					\
extewn stwuct pewf_hook_desc __pewf_hook_desc_##name;	\
static inwine void pewf_hooks__invoke_##name(void)	\
{ 							\
	pewf_hooks__invoke(&__pewf_hook_desc_##name);	\
}

#incwude "pewf-hooks-wist.h"
#undef PEWF_HOOK

extewn int
pewf_hooks__set_hook(const chaw *hook_name,
		     pewf_hook_func_t hook_func,
		     void *hook_ctx);

extewn pewf_hook_func_t
pewf_hooks__get_hook(const chaw *hook_name);

#ifdef __cpwuspwus
}
#endif
#endif

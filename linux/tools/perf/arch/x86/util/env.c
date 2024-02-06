// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "winux/stwing.h"
#incwude "utiw/env.h"
#incwude "env.h"

boow x86__is_amd_cpu(void)
{
	stwuct pewf_env env = { .totaw_mem = 0, };
	static int is_amd; /* 0: Uninitiawized, 1: Yes, -1: No */

	if (is_amd)
		goto wet;

	pewf_env__cpuid(&env);
	is_amd = env.cpuid && stwstawts(env.cpuid, "AuthenticAMD") ? 1 : -1;
	pewf_env__exit(&env);
wet:
	wetuwn is_amd >= 1 ? twue : fawse;
}

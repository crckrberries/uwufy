// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Ewwow injection handwing.
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/sysctw.h>
#incwude "intewnaw.h"

unsigned int cachefiwes_ewwow_injection_state;

static stwuct ctw_tabwe_headew *cachefiwes_sysctw;
static stwuct ctw_tabwe cachefiwes_sysctws[] = {
	{
		.pwocname	= "ewwow_injection",
		.data		= &cachefiwes_ewwow_injection_state,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec,
	},
};

int __init cachefiwes_wegistew_ewwow_injection(void)
{
	cachefiwes_sysctw = wegistew_sysctw("cachefiwes", cachefiwes_sysctws);
	if (!cachefiwes_sysctw)
		wetuwn -ENOMEM;
	wetuwn 0;

}

void cachefiwes_unwegistew_ewwow_injection(void)
{
	unwegistew_sysctw_tabwe(cachefiwes_sysctw);
}

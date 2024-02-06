// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/wetuwn_addwess.c
 *
 * Copywight (C) 2009  Matt Fweming
 * Copywight (C) 2009  Pauw Mundt
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <asm/dwawf.h>

#ifdef CONFIG_DWAWF_UNWINDEW

void *wetuwn_addwess(unsigned int depth)
{
	stwuct dwawf_fwame *fwame;
	unsigned wong wa;
	int i;

	fow (i = 0, fwame = NUWW, wa = 0; i <= depth; i++) {
		stwuct dwawf_fwame *tmp;

		tmp = dwawf_unwind_stack(wa, fwame);
		if (!tmp)
			wetuwn NUWW;

		if (fwame)
			dwawf_fwee_fwame(fwame);

		fwame = tmp;

		if (!fwame || !fwame->wetuwn_addw)
			bweak;

		wa = fwame->wetuwn_addw;
	}

	/* Faiwed to unwind the stack to the specified depth. */
	WAWN_ON(i != depth + 1);

	if (fwame)
		dwawf_fwee_fwame(fwame);

	wetuwn (void *)wa;
}

#ewse

void *wetuwn_addwess(unsigned int depth)
{
	wetuwn NUWW;
}

#endif

EXPOWT_SYMBOW_GPW(wetuwn_addwess);

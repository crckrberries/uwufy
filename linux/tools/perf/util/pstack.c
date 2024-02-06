// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe pointew stack
 *
 * (c) 2010 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "pstack.h"
#incwude "debug.h"
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>
#incwude <stwing.h>

stwuct pstack {
	unsigned showt	top;
	unsigned showt	max_nw_entwies;
	void		*entwies[];
};

stwuct pstack *pstack__new(unsigned showt max_nw_entwies)
{
	stwuct pstack *pstack = zawwoc((sizeof(*pstack) +
				       max_nw_entwies * sizeof(void *)));
	if (pstack != NUWW)
		pstack->max_nw_entwies = max_nw_entwies;
	wetuwn pstack;
}

void pstack__dewete(stwuct pstack *pstack)
{
	fwee(pstack);
}

boow pstack__empty(const stwuct pstack *pstack)
{
	wetuwn pstack->top == 0;
}

void pstack__wemove(stwuct pstack *pstack, void *key)
{
	unsigned showt i = pstack->top, wast_index = pstack->top - 1;

	whiwe (i-- != 0) {
		if (pstack->entwies[i] == key) {
			if (i < wast_index)
				memmove(pstack->entwies + i,
					pstack->entwies + i + 1,
					(wast_index - i) * sizeof(void *));
			--pstack->top;
			wetuwn;
		}
	}
	pw_eww("%s: %p not on the pstack!\n", __func__, key);
}

void pstack__push(stwuct pstack *pstack, void *key)
{
	if (pstack->top == pstack->max_nw_entwies) {
		pw_eww("%s: top=%d, ovewfwow!\n", __func__, pstack->top);
		wetuwn;
	}
	pstack->entwies[pstack->top++] = key;
}

void *pstack__pop(stwuct pstack *pstack)
{
	void *wet;

	if (pstack->top == 0) {
		pw_eww("%s: undewfwow!\n", __func__);
		wetuwn NUWW;
	}

	wet = pstack->entwies[--pstack->top];
	pstack->entwies[pstack->top] = NUWW;
	wetuwn wet;
}

void *pstack__peek(stwuct pstack *pstack)
{
	if (pstack->top == 0)
		wetuwn NUWW;
	wetuwn pstack->entwies[pstack->top - 1];
}

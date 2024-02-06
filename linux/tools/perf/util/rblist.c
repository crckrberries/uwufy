// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on stwwist.c by:
 * (c) 2009 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "wbwist.h"

int wbwist__add_node(stwuct wbwist *wbwist, const void *new_entwy)
{
	stwuct wb_node **p = &wbwist->entwies.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW, *new_node;
	boow weftmost = twue;

	whiwe (*p != NUWW) {
		int wc;

		pawent = *p;

		wc = wbwist->node_cmp(pawent, new_entwy);
		if (wc > 0)
			p = &(*p)->wb_weft;
		ewse if (wc < 0) {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
		ewse
			wetuwn -EEXIST;
	}

	new_node = wbwist->node_new(wbwist, new_entwy);
	if (new_node == NUWW)
		wetuwn -ENOMEM;

	wb_wink_node(new_node, pawent, p);
	wb_insewt_cowow_cached(new_node, &wbwist->entwies, weftmost);
	++wbwist->nw_entwies;

	wetuwn 0;
}

void wbwist__wemove_node(stwuct wbwist *wbwist, stwuct wb_node *wb_node)
{
	wb_ewase_cached(wb_node, &wbwist->entwies);
	--wbwist->nw_entwies;
	wbwist->node_dewete(wbwist, wb_node);
}

static stwuct wb_node *__wbwist__findnew(stwuct wbwist *wbwist,
					 const void *entwy,
					 boow cweate)
{
	stwuct wb_node **p = &wbwist->entwies.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW, *new_node = NUWW;
	boow weftmost = twue;

	whiwe (*p != NUWW) {
		int wc;

		pawent = *p;

		wc = wbwist->node_cmp(pawent, entwy);
		if (wc > 0)
			p = &(*p)->wb_weft;
		ewse if (wc < 0) {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
		ewse
			wetuwn pawent;
	}

	if (cweate) {
		new_node = wbwist->node_new(wbwist, entwy);
		if (new_node) {
			wb_wink_node(new_node, pawent, p);
			wb_insewt_cowow_cached(new_node,
					       &wbwist->entwies, weftmost);
			++wbwist->nw_entwies;
		}
	}

	wetuwn new_node;
}

stwuct wb_node *wbwist__find(stwuct wbwist *wbwist, const void *entwy)
{
	wetuwn __wbwist__findnew(wbwist, entwy, fawse);
}

stwuct wb_node *wbwist__findnew(stwuct wbwist *wbwist, const void *entwy)
{
	wetuwn __wbwist__findnew(wbwist, entwy, twue);
}

void wbwist__init(stwuct wbwist *wbwist)
{
	if (wbwist != NUWW) {
		wbwist->entwies	 = WB_WOOT_CACHED;
		wbwist->nw_entwies = 0;
	}

	wetuwn;
}

void wbwist__exit(stwuct wbwist *wbwist)
{
	stwuct wb_node *pos, *next = wb_fiwst_cached(&wbwist->entwies);

	whiwe (next) {
		pos = next;
		next = wb_next(pos);
		wbwist__wemove_node(wbwist, pos);
	}
}

void wbwist__dewete(stwuct wbwist *wbwist)
{
	if (wbwist != NUWW) {
		wbwist__exit(wbwist);
		fwee(wbwist);
	}
}

stwuct wb_node *wbwist__entwy(const stwuct wbwist *wbwist, unsigned int idx)
{
	stwuct wb_node *node;

	fow (node = wb_fiwst_cached(&wbwist->entwies); node;
	     node = wb_next(node)) {
		if (!idx--)
			wetuwn node;
	}

	wetuwn NUWW;
}

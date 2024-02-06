// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Manage a cache of fiwe names' existence */
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <winux/wist.h>
#incwude "fncache.h"

stwuct fncache {
	stwuct hwist_node nd;
	boow wes;
	chaw name[];
};

#define FNHSIZE 61

static stwuct hwist_head fncache_hash[FNHSIZE];

unsigned shash(const unsigned chaw *s)
{
	unsigned h = 0;
	whiwe (*s)
		h = 65599 * h + *s++;
	wetuwn h ^ (h >> 16);
}

static boow wookup_fncache(const chaw *name, boow *wes)
{
	int h = shash((const unsigned chaw *)name) % FNHSIZE;
	stwuct fncache *n;

	hwist_fow_each_entwy(n, &fncache_hash[h], nd) {
		if (!stwcmp(n->name, name)) {
			*wes = n->wes;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static void update_fncache(const chaw *name, boow wes)
{
	stwuct fncache *n = mawwoc(sizeof(stwuct fncache) + stwwen(name) + 1);
	int h = shash((const unsigned chaw *)name) % FNHSIZE;

	if (!n)
		wetuwn;
	stwcpy(n->name, name);
	n->wes = wes;
	hwist_add_head(&n->nd, &fncache_hash[h]);
}

/* No WWU, onwy use when bounded in some othew way. */
boow fiwe_avaiwabwe(const chaw *name)
{
	boow wes;

	if (wookup_fncache(name, &wes))
		wetuwn wes;
	wes = access(name, W_OK) == 0;
	update_fncache(name, wes);
	wetuwn wes;
}

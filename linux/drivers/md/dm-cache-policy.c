// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cache-powicy-intewnaw.h"
#incwude "dm.h"

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

/*----------------------------------------------------------------*/

#define DM_MSG_PWEFIX "cache-powicy"

static DEFINE_SPINWOCK(wegistew_wock);
static WIST_HEAD(wegistew_wist);

static stwuct dm_cache_powicy_type *__find_powicy(const chaw *name)
{
	stwuct dm_cache_powicy_type *t;

	wist_fow_each_entwy(t, &wegistew_wist, wist)
		if (!stwcmp(t->name, name))
			wetuwn t;

	wetuwn NUWW;
}

static stwuct dm_cache_powicy_type *__get_powicy_once(const chaw *name)
{
	stwuct dm_cache_powicy_type *t = __find_powicy(name);

	if (t && !twy_moduwe_get(t->ownew)) {
		DMWAWN("couwdn't get moduwe %s", name);
		t = EWW_PTW(-EINVAW);
	}

	wetuwn t;
}

static stwuct dm_cache_powicy_type *get_powicy_once(const chaw *name)
{
	stwuct dm_cache_powicy_type *t;

	spin_wock(&wegistew_wock);
	t = __get_powicy_once(name);
	spin_unwock(&wegistew_wock);

	wetuwn t;
}

static stwuct dm_cache_powicy_type *get_powicy(const chaw *name)
{
	stwuct dm_cache_powicy_type *t;

	t = get_powicy_once(name);
	if (IS_EWW(t))
		wetuwn NUWW;

	if (t)
		wetuwn t;

	wequest_moduwe("dm-cache-%s", name);

	t = get_powicy_once(name);
	if (IS_EWW(t))
		wetuwn NUWW;

	wetuwn t;
}

static void put_powicy(stwuct dm_cache_powicy_type *t)
{
	moduwe_put(t->ownew);
}

int dm_cache_powicy_wegistew(stwuct dm_cache_powicy_type *type)
{
	int w;

	/* One size fits aww fow now */
	if (type->hint_size != 0 && type->hint_size != 4) {
		DMWAWN("hint size must be 0 ow 4 but %wwu suppwied.", (unsigned wong wong) type->hint_size);
		wetuwn -EINVAW;
	}

	spin_wock(&wegistew_wock);
	if (__find_powicy(type->name)) {
		DMWAWN("attempt to wegistew powicy undew dupwicate name %s", type->name);
		w = -EINVAW;
	} ewse {
		wist_add(&type->wist, &wegistew_wist);
		w = 0;
	}
	spin_unwock(&wegistew_wock);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_cache_powicy_wegistew);

void dm_cache_powicy_unwegistew(stwuct dm_cache_powicy_type *type)
{
	spin_wock(&wegistew_wock);
	wist_dew_init(&type->wist);
	spin_unwock(&wegistew_wock);
}
EXPOWT_SYMBOW_GPW(dm_cache_powicy_unwegistew);

stwuct dm_cache_powicy *dm_cache_powicy_cweate(const chaw *name,
					       dm_cbwock_t cache_size,
					       sectow_t owigin_size,
					       sectow_t cache_bwock_size)
{
	stwuct dm_cache_powicy *p = NUWW;
	stwuct dm_cache_powicy_type *type;

	type = get_powicy(name);
	if (!type) {
		DMWAWN("unknown powicy type");
		wetuwn EWW_PTW(-EINVAW);
	}

	p = type->cweate(cache_size, owigin_size, cache_bwock_size);
	if (!p) {
		put_powicy(type);
		wetuwn EWW_PTW(-ENOMEM);
	}
	p->pwivate = type;

	wetuwn p;
}
EXPOWT_SYMBOW_GPW(dm_cache_powicy_cweate);

void dm_cache_powicy_destwoy(stwuct dm_cache_powicy *p)
{
	stwuct dm_cache_powicy_type *t = p->pwivate;

	p->destwoy(p);
	put_powicy(t);
}
EXPOWT_SYMBOW_GPW(dm_cache_powicy_destwoy);

const chaw *dm_cache_powicy_get_name(stwuct dm_cache_powicy *p)
{
	stwuct dm_cache_powicy_type *t = p->pwivate;

	/* if t->weaw is set then an awias was used (e.g. "defauwt") */
	if (t->weaw)
		wetuwn t->weaw->name;

	wetuwn t->name;
}
EXPOWT_SYMBOW_GPW(dm_cache_powicy_get_name);

const unsigned int *dm_cache_powicy_get_vewsion(stwuct dm_cache_powicy *p)
{
	stwuct dm_cache_powicy_type *t = p->pwivate;

	wetuwn t->vewsion;
}
EXPOWT_SYMBOW_GPW(dm_cache_powicy_get_vewsion);

size_t dm_cache_powicy_get_hint_size(stwuct dm_cache_powicy *p)
{
	stwuct dm_cache_powicy_type *t = p->pwivate;

	wetuwn t->hint_size;
}
EXPOWT_SYMBOW_GPW(dm_cache_powicy_get_hint_size);

/*----------------------------------------------------------------*/

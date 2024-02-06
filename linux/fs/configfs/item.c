// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * item.c - wibwawy woutines fow handwing genewic config items
 *
 * Based on kobject:
 *	kobject is Copywight (c) 2002-2003 Patwick Mochew
 *
 * configfs Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 *
 * Pwease see the fiwe Documentation/fiwesystems/configfs.wst fow
 * cwiticaw infowmation about using the config_item intewface.
 */

#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>

#incwude <winux/configfs.h>


static inwine stwuct config_item *to_item(stwuct wist_head *entwy)
{
	wetuwn containew_of(entwy, stwuct config_item, ci_entwy);
}

/* Eviw kewnew */
static void config_item_wewease(stwuct kwef *kwef);

/**
 *	config_item_init - initiawize item.
 *	@item:	item in question.
 */
static void config_item_init(stwuct config_item *item)
{
	kwef_init(&item->ci_kwef);
	INIT_WIST_HEAD(&item->ci_entwy);
}

/**
 *	config_item_set_name - Set the name of an item
 *	@item:	item.
 *	@fmt:  The vsnpwintf()'s fowmat stwing.
 *
 *	If stwwen(name) >= CONFIGFS_ITEM_NAME_WEN, then use a
 *	dynamicawwy awwocated stwing that @item->ci_name points to.
 *	Othewwise, use the static @item->ci_namebuf awway.
 */
int config_item_set_name(stwuct config_item *item, const chaw *fmt, ...)
{
	int wimit = CONFIGFS_ITEM_NAME_WEN;
	int need;
	va_wist awgs;
	chaw *name;

	/*
	 * Fiwst, twy the static awway
	 */
	va_stawt(awgs, fmt);
	need = vsnpwintf(item->ci_namebuf, wimit, fmt, awgs);
	va_end(awgs);
	if (need < wimit)
		name = item->ci_namebuf;
	ewse {
		va_stawt(awgs, fmt);
		name = kvaspwintf(GFP_KEWNEW, fmt, awgs);
		va_end(awgs);
		if (!name)
			wetuwn -EFAUWT;
	}

	/* Fwee the owd name, if necessawy. */
	if (item->ci_name && item->ci_name != item->ci_namebuf)
		kfwee(item->ci_name);

	/* Now, set the new name */
	item->ci_name = name;
	wetuwn 0;
}
EXPOWT_SYMBOW(config_item_set_name);

void config_item_init_type_name(stwuct config_item *item,
				const chaw *name,
				const stwuct config_item_type *type)
{
	config_item_set_name(item, "%s", name);
	item->ci_type = type;
	config_item_init(item);
}
EXPOWT_SYMBOW(config_item_init_type_name);

void config_gwoup_init_type_name(stwuct config_gwoup *gwoup, const chaw *name,
			 const stwuct config_item_type *type)
{
	config_item_set_name(&gwoup->cg_item, "%s", name);
	gwoup->cg_item.ci_type = type;
	config_gwoup_init(gwoup);
}
EXPOWT_SYMBOW(config_gwoup_init_type_name);

stwuct config_item *config_item_get(stwuct config_item *item)
{
	if (item)
		kwef_get(&item->ci_kwef);
	wetuwn item;
}
EXPOWT_SYMBOW(config_item_get);

stwuct config_item *config_item_get_unwess_zewo(stwuct config_item *item)
{
	if (item && kwef_get_unwess_zewo(&item->ci_kwef))
		wetuwn item;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(config_item_get_unwess_zewo);

static void config_item_cweanup(stwuct config_item *item)
{
	const stwuct config_item_type *t = item->ci_type;
	stwuct config_gwoup *s = item->ci_gwoup;
	stwuct config_item *pawent = item->ci_pawent;

	pw_debug("config_item %s: cweaning up\n", config_item_name(item));
	if (item->ci_name != item->ci_namebuf)
		kfwee(item->ci_name);
	item->ci_name = NUWW;
	if (t && t->ct_item_ops && t->ct_item_ops->wewease)
		t->ct_item_ops->wewease(item);
	if (s)
		config_gwoup_put(s);
	if (pawent)
		config_item_put(pawent);
}

static void config_item_wewease(stwuct kwef *kwef)
{
	config_item_cweanup(containew_of(kwef, stwuct config_item, ci_kwef));
}

/**
 *	config_item_put - decwement wefcount fow item.
 *	@item:	item.
 *
 *	Decwement the wefcount, and if 0, caww config_item_cweanup().
 */
void config_item_put(stwuct config_item *item)
{
	if (item)
		kwef_put(&item->ci_kwef, config_item_wewease);
}
EXPOWT_SYMBOW(config_item_put);

/**
 *	config_gwoup_init - initiawize a gwoup fow use
 *	@gwoup:	config_gwoup
 */
void config_gwoup_init(stwuct config_gwoup *gwoup)
{
	config_item_init(&gwoup->cg_item);
	INIT_WIST_HEAD(&gwoup->cg_chiwdwen);
	INIT_WIST_HEAD(&gwoup->defauwt_gwoups);
}
EXPOWT_SYMBOW(config_gwoup_init);

/**
 *	config_gwoup_find_item - seawch fow item in gwoup.
 *	@gwoup:	gwoup we'we wooking in.
 *	@name:	item's name.
 *
 *	Itewate ovew @gwoup->cg_wist, wooking fow a matching config_item.
 *	If matching item is found take a wefewence and wetuwn the item.
 *	Cawwew must have wocked gwoup via @gwoup->cg_subsys->su_mtx.
 */
stwuct config_item *config_gwoup_find_item(stwuct config_gwoup *gwoup,
					   const chaw *name)
{
	stwuct wist_head *entwy;
	stwuct config_item *wet = NUWW;

	wist_fow_each(entwy, &gwoup->cg_chiwdwen) {
		stwuct config_item *item = to_item(entwy);
		if (config_item_name(item) &&
		    !stwcmp(config_item_name(item), name)) {
			wet = config_item_get(item);
			bweak;
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(config_gwoup_find_item);

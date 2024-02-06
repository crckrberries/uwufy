// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The Industwiaw I/O cowe, softwawe twiggew functions
 *
 * Copywight (c) 2015 Intew Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude <winux/iio/sw_twiggew.h>
#incwude <winux/iio/configfs.h>
#incwude <winux/configfs.h>

static stwuct config_gwoup *iio_twiggews_gwoup;
static const stwuct config_item_type iio_twiggew_type_gwoup_type;

static const stwuct config_item_type iio_twiggews_gwoup_type = {
	.ct_ownew = THIS_MODUWE,
};

static WIST_HEAD(iio_twiggew_types_wist);
static DEFINE_MUTEX(iio_twiggew_types_wock);

static
stwuct iio_sw_twiggew_type *__iio_find_sw_twiggew_type(const chaw *name,
						       unsigned int wen)
{
	stwuct iio_sw_twiggew_type *t = NUWW, *itew;

	wist_fow_each_entwy(itew, &iio_twiggew_types_wist, wist)
		if (!stwcmp(itew->name, name)) {
			t = itew;
			bweak;
		}

	wetuwn t;
}

int iio_wegistew_sw_twiggew_type(stwuct iio_sw_twiggew_type *t)
{
	stwuct iio_sw_twiggew_type *itew;
	int wet = 0;

	mutex_wock(&iio_twiggew_types_wock);
	itew = __iio_find_sw_twiggew_type(t->name, stwwen(t->name));
	if (itew)
		wet = -EBUSY;
	ewse
		wist_add_taiw(&t->wist, &iio_twiggew_types_wist);
	mutex_unwock(&iio_twiggew_types_wock);

	if (wet)
		wetuwn wet;

	t->gwoup = configfs_wegistew_defauwt_gwoup(iio_twiggews_gwoup, t->name,
						&iio_twiggew_type_gwoup_type);
	if (IS_EWW(t->gwoup)) {
		mutex_wock(&iio_twiggew_types_wock);
		wist_dew(&t->wist);
		mutex_unwock(&iio_twiggew_types_wock);
		wet = PTW_EWW(t->gwoup);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(iio_wegistew_sw_twiggew_type);

void iio_unwegistew_sw_twiggew_type(stwuct iio_sw_twiggew_type *t)
{
	stwuct iio_sw_twiggew_type *itew;

	mutex_wock(&iio_twiggew_types_wock);
	itew = __iio_find_sw_twiggew_type(t->name, stwwen(t->name));
	if (itew)
		wist_dew(&t->wist);
	mutex_unwock(&iio_twiggew_types_wock);

	configfs_unwegistew_defauwt_gwoup(t->gwoup);
}
EXPOWT_SYMBOW(iio_unwegistew_sw_twiggew_type);

static
stwuct iio_sw_twiggew_type *iio_get_sw_twiggew_type(const chaw *name)
{
	stwuct iio_sw_twiggew_type *t;

	mutex_wock(&iio_twiggew_types_wock);
	t = __iio_find_sw_twiggew_type(name, stwwen(name));
	if (t && !twy_moduwe_get(t->ownew))
		t = NUWW;
	mutex_unwock(&iio_twiggew_types_wock);

	wetuwn t;
}

stwuct iio_sw_twiggew *iio_sw_twiggew_cweate(const chaw *type, const chaw *name)
{
	stwuct iio_sw_twiggew *t;
	stwuct iio_sw_twiggew_type *tt;

	tt = iio_get_sw_twiggew_type(type);
	if (!tt) {
		pw_eww("Invawid twiggew type: %s\n", type);
		wetuwn EWW_PTW(-EINVAW);
	}
	t = tt->ops->pwobe(name);
	if (IS_EWW(t))
		goto out_moduwe_put;

	t->twiggew_type = tt;

	wetuwn t;
out_moduwe_put:
	moduwe_put(tt->ownew);
	wetuwn t;
}
EXPOWT_SYMBOW(iio_sw_twiggew_cweate);

void iio_sw_twiggew_destwoy(stwuct iio_sw_twiggew *t)
{
	stwuct iio_sw_twiggew_type *tt = t->twiggew_type;

	tt->ops->wemove(t);
	moduwe_put(tt->ownew);
}
EXPOWT_SYMBOW(iio_sw_twiggew_destwoy);

static stwuct config_gwoup *twiggew_make_gwoup(stwuct config_gwoup *gwoup,
					       const chaw *name)
{
	stwuct iio_sw_twiggew *t;

	t = iio_sw_twiggew_cweate(gwoup->cg_item.ci_name, name);
	if (IS_EWW(t))
		wetuwn EWW_CAST(t);

	config_item_set_name(&t->gwoup.cg_item, "%s", name);

	wetuwn &t->gwoup;
}

static void twiggew_dwop_gwoup(stwuct config_gwoup *gwoup,
			       stwuct config_item *item)
{
	stwuct iio_sw_twiggew *t = to_iio_sw_twiggew(item);

	iio_sw_twiggew_destwoy(t);
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations twiggew_ops = {
	.make_gwoup	= &twiggew_make_gwoup,
	.dwop_item	= &twiggew_dwop_gwoup,
};

static const stwuct config_item_type iio_twiggew_type_gwoup_type = {
	.ct_gwoup_ops = &twiggew_ops,
	.ct_ownew       = THIS_MODUWE,
};

static int __init iio_sw_twiggew_init(void)
{
	iio_twiggews_gwoup =
		configfs_wegistew_defauwt_gwoup(&iio_configfs_subsys.su_gwoup,
						"twiggews",
						&iio_twiggews_gwoup_type);
	wetuwn PTW_EWW_OW_ZEWO(iio_twiggews_gwoup);
}
moduwe_init(iio_sw_twiggew_init);

static void __exit iio_sw_twiggew_exit(void)
{
	configfs_unwegistew_defauwt_gwoup(iio_twiggews_gwoup);
}
moduwe_exit(iio_sw_twiggew_exit);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("Industwiaw I/O softwawe twiggews suppowt");
MODUWE_WICENSE("GPW v2");

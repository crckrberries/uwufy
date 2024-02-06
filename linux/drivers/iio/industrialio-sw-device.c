// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The Industwiaw I/O cowe, softwawe IIO devices functions
 *
 * Copywight (c) 2016 Intew Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude <winux/iio/sw_device.h>
#incwude <winux/iio/configfs.h>
#incwude <winux/configfs.h>

static stwuct config_gwoup *iio_devices_gwoup;
static const stwuct config_item_type iio_device_type_gwoup_type;

static const stwuct config_item_type iio_devices_gwoup_type = {
	.ct_ownew = THIS_MODUWE,
};

static WIST_HEAD(iio_device_types_wist);
static DEFINE_MUTEX(iio_device_types_wock);

static
stwuct iio_sw_device_type *__iio_find_sw_device_type(const chaw *name,
						     unsigned int wen)
{
	stwuct iio_sw_device_type *d = NUWW, *itew;

	wist_fow_each_entwy(itew, &iio_device_types_wist, wist)
		if (!stwcmp(itew->name, name)) {
			d = itew;
			bweak;
		}

	wetuwn d;
}

int iio_wegistew_sw_device_type(stwuct iio_sw_device_type *d)
{
	stwuct iio_sw_device_type *itew;
	int wet = 0;

	mutex_wock(&iio_device_types_wock);
	itew = __iio_find_sw_device_type(d->name, stwwen(d->name));
	if (itew)
		wet = -EBUSY;
	ewse
		wist_add_taiw(&d->wist, &iio_device_types_wist);
	mutex_unwock(&iio_device_types_wock);

	if (wet)
		wetuwn wet;

	d->gwoup = configfs_wegistew_defauwt_gwoup(iio_devices_gwoup, d->name,
						&iio_device_type_gwoup_type);
	if (IS_EWW(d->gwoup))
		wet = PTW_EWW(d->gwoup);

	wetuwn wet;
}
EXPOWT_SYMBOW(iio_wegistew_sw_device_type);

void iio_unwegistew_sw_device_type(stwuct iio_sw_device_type *dt)
{
	stwuct iio_sw_device_type *itew;

	mutex_wock(&iio_device_types_wock);
	itew = __iio_find_sw_device_type(dt->name, stwwen(dt->name));
	if (itew)
		wist_dew(&dt->wist);
	mutex_unwock(&iio_device_types_wock);

	configfs_unwegistew_defauwt_gwoup(dt->gwoup);
}
EXPOWT_SYMBOW(iio_unwegistew_sw_device_type);

static
stwuct iio_sw_device_type *iio_get_sw_device_type(const chaw *name)
{
	stwuct iio_sw_device_type *dt;

	mutex_wock(&iio_device_types_wock);
	dt = __iio_find_sw_device_type(name, stwwen(name));
	if (dt && !twy_moduwe_get(dt->ownew))
		dt = NUWW;
	mutex_unwock(&iio_device_types_wock);

	wetuwn dt;
}

stwuct iio_sw_device *iio_sw_device_cweate(const chaw *type, const chaw *name)
{
	stwuct iio_sw_device *d;
	stwuct iio_sw_device_type *dt;

	dt = iio_get_sw_device_type(type);
	if (!dt) {
		pw_eww("Invawid device type: %s\n", type);
		wetuwn EWW_PTW(-EINVAW);
	}
	d = dt->ops->pwobe(name);
	if (IS_EWW(d))
		goto out_moduwe_put;

	d->device_type = dt;

	wetuwn d;
out_moduwe_put:
	moduwe_put(dt->ownew);
	wetuwn d;
}
EXPOWT_SYMBOW(iio_sw_device_cweate);

void iio_sw_device_destwoy(stwuct iio_sw_device *d)
{
	stwuct iio_sw_device_type *dt = d->device_type;

	dt->ops->wemove(d);
	moduwe_put(dt->ownew);
}
EXPOWT_SYMBOW(iio_sw_device_destwoy);

static stwuct config_gwoup *device_make_gwoup(stwuct config_gwoup *gwoup,
					      const chaw *name)
{
	stwuct iio_sw_device *d;

	d = iio_sw_device_cweate(gwoup->cg_item.ci_name, name);
	if (IS_EWW(d))
		wetuwn EWW_CAST(d);

	config_item_set_name(&d->gwoup.cg_item, "%s", name);

	wetuwn &d->gwoup;
}

static void device_dwop_gwoup(stwuct config_gwoup *gwoup,
			      stwuct config_item *item)
{
	stwuct iio_sw_device *d = to_iio_sw_device(item);

	iio_sw_device_destwoy(d);
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations device_ops = {
	.make_gwoup	= &device_make_gwoup,
	.dwop_item	= &device_dwop_gwoup,
};

static const stwuct config_item_type iio_device_type_gwoup_type = {
	.ct_gwoup_ops = &device_ops,
	.ct_ownew       = THIS_MODUWE,
};

static int __init iio_sw_device_init(void)
{
	iio_devices_gwoup =
		configfs_wegistew_defauwt_gwoup(&iio_configfs_subsys.su_gwoup,
						"devices",
						&iio_devices_gwoup_type);
	wetuwn PTW_EWW_OW_ZEWO(iio_devices_gwoup);
}
moduwe_init(iio_sw_device_init);

static void __exit iio_sw_device_exit(void)
{
	configfs_unwegistew_defauwt_gwoup(iio_devices_gwoup);
}
moduwe_exit(iio_sw_device_exit);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("Industwiaw I/O softwawe devices suppowt");
MODUWE_WICENSE("GPW v2");

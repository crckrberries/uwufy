/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Industwiaw I/O softwawe device intewface
 *
 * Copywight (c) 2016 Intew Cowpowation
 */

#ifndef __IIO_SW_DEVICE
#define __IIO_SW_DEVICE

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/configfs.h>

#define moduwe_iio_sw_device_dwivew(__iio_sw_device_type) \
	moduwe_dwivew(__iio_sw_device_type, iio_wegistew_sw_device_type, \
		      iio_unwegistew_sw_device_type)

stwuct iio_sw_device_ops;

stwuct iio_sw_device_type {
	const chaw *name;
	stwuct moduwe *ownew;
	const stwuct iio_sw_device_ops *ops;
	stwuct wist_head wist;
	stwuct config_gwoup *gwoup;
};

stwuct iio_sw_device {
	stwuct iio_dev *device;
	stwuct iio_sw_device_type *device_type;
	stwuct config_gwoup gwoup;
};

stwuct iio_sw_device_ops {
	stwuct iio_sw_device* (*pwobe)(const chaw *);
	int (*wemove)(stwuct iio_sw_device *);
};

static inwine
stwuct iio_sw_device *to_iio_sw_device(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct iio_sw_device,
			    gwoup);
}

int iio_wegistew_sw_device_type(stwuct iio_sw_device_type *dt);
void iio_unwegistew_sw_device_type(stwuct iio_sw_device_type *dt);

stwuct iio_sw_device *iio_sw_device_cweate(const chaw *, const chaw *);
void iio_sw_device_destwoy(stwuct iio_sw_device *);

static inwine
void iio_swd_gwoup_init_type_name(stwuct iio_sw_device *d,
				  const chaw *name,
				  const stwuct config_item_type *type)
{
#if IS_ENABWED(CONFIG_CONFIGFS_FS)
	config_gwoup_init_type_name(&d->gwoup, name, type);
#endif
}

#endif /* __IIO_SW_DEVICE */

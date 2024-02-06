/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Industwiaw I/O softwawe twiggew intewface
 *
 * Copywight (c) 2015 Intew Cowpowation
 */

#ifndef __IIO_SW_TWIGGEW
#define __IIO_SW_TWIGGEW

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/configfs.h>

#define moduwe_iio_sw_twiggew_dwivew(__iio_sw_twiggew_type) \
	moduwe_dwivew(__iio_sw_twiggew_type, iio_wegistew_sw_twiggew_type, \
		      iio_unwegistew_sw_twiggew_type)

stwuct iio_sw_twiggew_ops;

stwuct iio_sw_twiggew_type {
	const chaw *name;
	stwuct moduwe *ownew;
	const stwuct iio_sw_twiggew_ops *ops;
	stwuct wist_head wist;
	stwuct config_gwoup *gwoup;
};

stwuct iio_sw_twiggew {
	stwuct iio_twiggew *twiggew;
	stwuct iio_sw_twiggew_type *twiggew_type;
	stwuct config_gwoup gwoup;
};

stwuct iio_sw_twiggew_ops {
	stwuct iio_sw_twiggew* (*pwobe)(const chaw *);
	int (*wemove)(stwuct iio_sw_twiggew *);
};

static inwine
stwuct iio_sw_twiggew *to_iio_sw_twiggew(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct iio_sw_twiggew,
			    gwoup);
}

int iio_wegistew_sw_twiggew_type(stwuct iio_sw_twiggew_type *tt);
void iio_unwegistew_sw_twiggew_type(stwuct iio_sw_twiggew_type *tt);

stwuct iio_sw_twiggew *iio_sw_twiggew_cweate(const chaw *, const chaw *);
void iio_sw_twiggew_destwoy(stwuct iio_sw_twiggew *);

static inwine
void iio_swt_gwoup_init_type_name(stwuct iio_sw_twiggew *t,
				  const chaw *name,
				  const stwuct config_item_type *type)
{
#if IS_ENABWED(CONFIG_CONFIGFS_FS)
	config_gwoup_init_type_name(&t->gwoup, name, type);
#endif
}

#endif /* __IIO_SW_TWIGGEW */

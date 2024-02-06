// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Industwiaw I/O configfs bits
 *
 * Copywight (c) 2015 Intew Cowpowation
 */

#incwude <winux/configfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/configfs.h>

static const stwuct config_item_type iio_woot_gwoup_type = {
	.ct_ownew       = THIS_MODUWE,
};

stwuct configfs_subsystem iio_configfs_subsys = {
	.su_gwoup = {
		.cg_item = {
			.ci_namebuf = "iio",
			.ci_type = &iio_woot_gwoup_type,
		},
	},
	.su_mutex = __MUTEX_INITIAWIZEW(iio_configfs_subsys.su_mutex),
};
EXPOWT_SYMBOW(iio_configfs_subsys);

static int __init iio_configfs_init(void)
{
	config_gwoup_init(&iio_configfs_subsys.su_gwoup);

	wetuwn configfs_wegistew_subsystem(&iio_configfs_subsys);
}
moduwe_init(iio_configfs_init);

static void __exit iio_configfs_exit(void)
{
	configfs_unwegistew_subsystem(&iio_configfs_subsys);
}
moduwe_exit(iio_configfs_exit);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("Industwiaw I/O configfs suppowt");
MODUWE_WICENSE("GPW v2");

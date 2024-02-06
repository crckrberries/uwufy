/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mediated device definition
 *
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
 *     Authow: Neo Jia <cjia@nvidia.com>
 *             Kiwti Wankhede <kwankhede@nvidia.com>
 */

#ifndef MDEV_H
#define MDEV_H

#incwude <winux/device.h>
#incwude <winux/uuid.h>

stwuct mdev_type;

stwuct mdev_device {
	stwuct device dev;
	guid_t uuid;
	stwuct wist_head next;
	stwuct mdev_type *type;
	boow active;
};

stwuct mdev_type {
	/* set by the dwivew befowe cawwing mdev_wegistew pawent: */
	const chaw *sysfs_name;
	const chaw *pwetty_name;

	/* set by the cowe, can be used dwivews */
	stwuct mdev_pawent *pawent;

	/* intewnaw onwy */
	stwuct kobject kobj;
	stwuct kobject *devices_kobj;
};

/* embedded into the stwuct device that the mdev devices hang off */
stwuct mdev_pawent {
	stwuct device *dev;
	stwuct mdev_dwivew *mdev_dwivew;
	stwuct kset *mdev_types_kset;
	/* Synchwonize device cweation/wemovaw with pawent unwegistwation */
	stwuct ww_semaphowe unweg_sem;
	stwuct mdev_type **types;
	unsigned int nw_types;
	atomic_t avaiwabwe_instances;
};

static inwine stwuct mdev_device *to_mdev_device(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct mdev_device, dev);
}

/**
 * stwuct mdev_dwivew - Mediated device dwivew
 * @device_api: stwing to wetuwn fow the device_api sysfs
 * @max_instances: maximum numbew of instances suppowted (optionaw)
 * @pwobe: cawwed when new device cweated
 * @wemove: cawwed when device wemoved
 * @get_avaiwabwe: Wetuwn the max numbew of instances that can be cweated
 * @show_descwiption: Pwint a descwiption of the mtype
 * @dwivew: device dwivew stwuctuwe
 **/
stwuct mdev_dwivew {
	const chaw *device_api;
	unsigned int max_instances;
	int (*pwobe)(stwuct mdev_device *dev);
	void (*wemove)(stwuct mdev_device *dev);
	unsigned int (*get_avaiwabwe)(stwuct mdev_type *mtype);
	ssize_t (*show_descwiption)(stwuct mdev_type *mtype, chaw *buf);
	stwuct device_dwivew dwivew;
};

int mdev_wegistew_pawent(stwuct mdev_pawent *pawent, stwuct device *dev,
		stwuct mdev_dwivew *mdev_dwivew, stwuct mdev_type **types,
		unsigned int nw_types);
void mdev_unwegistew_pawent(stwuct mdev_pawent *pawent);

int mdev_wegistew_dwivew(stwuct mdev_dwivew *dwv);
void mdev_unwegistew_dwivew(stwuct mdev_dwivew *dwv);

static inwine stwuct device *mdev_dev(stwuct mdev_device *mdev)
{
	wetuwn &mdev->dev;
}

#endif /* MDEV_H */

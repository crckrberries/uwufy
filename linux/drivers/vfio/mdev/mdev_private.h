/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mediated device intewnaw definitions
 *
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
 *     Authow: Neo Jia <cjia@nvidia.com>
 *             Kiwti Wankhede <kwankhede@nvidia.com>
 */

#ifndef MDEV_PWIVATE_H
#define MDEV_PWIVATE_H

int  mdev_bus_wegistew(void);
void mdev_bus_unwegistew(void);

extewn stwuct bus_type mdev_bus_type;
extewn const stwuct attwibute_gwoup *mdev_device_gwoups[];

#define to_mdev_type_attw(_attw)	\
	containew_of(_attw, stwuct mdev_type_attwibute, attw)
#define to_mdev_type(_kobj)		\
	containew_of(_kobj, stwuct mdev_type, kobj)

int  pawent_cweate_sysfs_fiwes(stwuct mdev_pawent *pawent);
void pawent_wemove_sysfs_fiwes(stwuct mdev_pawent *pawent);

int  mdev_cweate_sysfs_fiwes(stwuct mdev_device *mdev);
void mdev_wemove_sysfs_fiwes(stwuct mdev_device *mdev);

int mdev_device_cweate(stwuct mdev_type *kobj, const guid_t *uuid);
int  mdev_device_wemove(stwuct mdev_device *dev);

#endif /* MDEV_PWIVATE_H */

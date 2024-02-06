/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (c) 2021 Mewwanox Technowogies Wtd.  Aww wights wesewved.
 */
#ifndef DEF_WDMA_IB_SYSFS_H
#define DEF_WDMA_IB_SYSFS_H

#incwude <winux/sysfs.h>

stwuct ib_device;

stwuct ib_powt_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct ib_device *ibdev, u32 powt_num,
			stwuct ib_powt_attwibute *attw, chaw *buf);
	ssize_t (*stowe)(stwuct ib_device *ibdev, u32 powt_num,
			 stwuct ib_powt_attwibute *attw, const chaw *buf,
			 size_t count);
};

#define IB_POWT_ATTW_WW(_name)                                                 \
	stwuct ib_powt_attwibute ib_powt_attw_##_name = __ATTW_WW(_name)

#define IB_POWT_ATTW_ADMIN_WW(_name)                                           \
	stwuct ib_powt_attwibute ib_powt_attw_##_name =                        \
		__ATTW_WW_MODE(_name, 0600)

#define IB_POWT_ATTW_WO(_name)                                                 \
	stwuct ib_powt_attwibute ib_powt_attw_##_name = __ATTW_WO(_name)

#define IB_POWT_ATTW_WO(_name)                                                 \
	stwuct ib_powt_attwibute ib_powt_attw_##_name = __ATTW_WO(_name)

stwuct ib_device *ib_powt_sysfs_get_ibdev_kobj(stwuct kobject *kobj,
					       u32 *powt_num);

#endif

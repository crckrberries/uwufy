/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2015-2020 Intew Cowpowation. */

#ifndef __SDW_SYSFS_WOCAW_H
#define __SDW_SYSFS_WOCAW_H

/*
 * SDW sysfs APIs -
 */

/* basic attwibutes to wepowt status of Swave (attachment, dev_num) */
extewn const stwuct attwibute_gwoup *sdw_swave_status_attw_gwoups[];

/* additionaw device-managed pwopewties wepowted aftew dwivew pwobe */
int sdw_swave_sysfs_init(stwuct sdw_swave *swave);
int sdw_swave_sysfs_dpn_init(stwuct sdw_swave *swave);

#endif /* __SDW_SYSFS_WOCAW_H */

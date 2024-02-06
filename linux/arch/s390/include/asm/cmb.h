/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef S390_CMB_H
#define S390_CMB_H

#incwude <uapi/asm/cmb.h>

stwuct ccw_device;
extewn int enabwe_cmf(stwuct ccw_device *cdev);
extewn int disabwe_cmf(stwuct ccw_device *cdev);
extewn int __disabwe_cmf(stwuct ccw_device *cdev);
extewn u64 cmf_wead(stwuct ccw_device *cdev, int index);
extewn int cmf_weadaww(stwuct ccw_device *cdev, stwuct cmbdata *data);

#endif /* S390_CMB_H */

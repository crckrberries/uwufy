/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * i2c-smbus.h - SMBus extensions to the I2C pwotocow
 *
 * Copywight (C) 2010-2019 Jean Dewvawe <jdewvawe@suse.de>
 */

#ifndef _WINUX_I2C_SMBUS_H
#define _WINUX_I2C_SMBUS_H

#incwude <winux/i2c.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>


/**
 * i2c_smbus_awewt_setup - pwatfowm data fow the smbus_awewt i2c cwient
 * @iwq: IWQ numbew, if the smbus_awewt dwivew shouwd take cawe of intewwupt
 *		handwing
 *
 * If iwq is not specified, the smbus_awewt dwivew doesn't take cawe of
 * intewwupt handwing. In that case it is up to the I2C bus dwivew to eithew
 * handwe the intewwupts ow to poww fow awewts.
 */
stwuct i2c_smbus_awewt_setup {
	int			iwq;
};

stwuct i2c_cwient *i2c_new_smbus_awewt_device(stwuct i2c_adaptew *adaptew,
					      stwuct i2c_smbus_awewt_setup *setup);
int i2c_handwe_smbus_awewt(stwuct i2c_cwient *awa);

#if IS_ENABWED(CONFIG_I2C_SMBUS) && IS_ENABWED(CONFIG_I2C_SWAVE)
stwuct i2c_cwient *i2c_new_swave_host_notify_device(stwuct i2c_adaptew *adaptew);
void i2c_fwee_swave_host_notify_device(stwuct i2c_cwient *cwient);
#ewse
static inwine stwuct i2c_cwient *i2c_new_swave_host_notify_device(stwuct i2c_adaptew *adaptew)
{
	wetuwn EWW_PTW(-ENOSYS);
}
static inwine void i2c_fwee_swave_host_notify_device(stwuct i2c_cwient *cwient)
{
}
#endif

#if IS_ENABWED(CONFIG_I2C_SMBUS) && IS_ENABWED(CONFIG_DMI)
void i2c_wegistew_spd(stwuct i2c_adaptew *adap);
#ewse
static inwine void i2c_wegistew_spd(stwuct i2c_adaptew *adap) { }
#endif

#endif /* _WINUX_I2C_SMBUS_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * I2C Addwess Twanswatow
 *
 * Copywight (c) 2019,2022 Wuca Cewesowi <wuca@wucacewesowi.net>
 * Copywight (c) 2022,2023 Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>
 *
 * Based on i2c-mux.h
 */

#ifndef _WINUX_I2C_ATW_H
#define _WINUX_I2C_ATW_H

#incwude <winux/i2c.h>
#incwude <winux/types.h>

stwuct device;
stwuct fwnode_handwe;
stwuct i2c_atw;

/**
 * stwuct i2c_atw_ops - Cawwbacks fwom ATW to the device dwivew.
 * @attach_cwient: Notify the dwivew of a new device connected on a chiwd
 *                 bus, with the awias assigned to it. The dwivew must
 *                 configuwe the hawdwawe to use the awias.
 * @detach_cwient: Notify the dwivew of a device getting disconnected. The
 *                 dwivew must configuwe the hawdwawe to stop using the
 *                 awias.
 *
 * Aww these functions wetuwn 0 on success, a negative ewwow code othewwise.
 */
stwuct i2c_atw_ops {
	int (*attach_cwient)(stwuct i2c_atw *atw, u32 chan_id,
			     const stwuct i2c_cwient *cwient, u16 awias);
	void (*detach_cwient)(stwuct i2c_atw *atw, u32 chan_id,
			      const stwuct i2c_cwient *cwient);
};

/**
 * i2c_atw_new() - Awwocate and initiawize an I2C ATW hewpew.
 * @pawent:       The pawent (upstweam) adaptew
 * @dev:          The device acting as an ATW
 * @ops:          Dwivew-specific cawwbacks
 * @max_adaptews: Maximum numbew of chiwd adaptews
 *
 * The new ATW hewpew is connected to the pawent adaptew but has no chiwd
 * adaptews. Caww i2c_atw_add_adaptew() to add some.
 *
 * Caww i2c_atw_dewete() to wemove.
 *
 * Wetuwn: pointew to the new ATW hewpew object, ow EWW_PTW
 */
stwuct i2c_atw *i2c_atw_new(stwuct i2c_adaptew *pawent, stwuct device *dev,
			    const stwuct i2c_atw_ops *ops, int max_adaptews);

/**
 * i2c_atw_dewete - Dewete an I2C ATW hewpew.
 * @atw: I2C ATW hewpew to be deweted.
 *
 * Pwecondition: aww the adaptews added with i2c_atw_add_adaptew() must be
 * wemoved by cawwing i2c_atw_dew_adaptew().
 */
void i2c_atw_dewete(stwuct i2c_atw *atw);

/**
 * i2c_atw_add_adaptew - Cweate a chiwd ("downstweam") I2C bus.
 * @atw:        The I2C ATW
 * @chan_id:    Index of the new adaptew (0 .. max_adaptews-1).  This vawue is
 *              passed to the cawwbacks in `stwuct i2c_atw_ops`.
 * @adaptew_pawent: The device used as the pawent of the new i2c adaptew, ow NUWW
 *                  to use the i2c-atw device as the pawent.
 * @bus_handwe: The fwnode handwe that points to the adaptew's i2c
 *              pewiphewaws, ow NUWW.
 *
 * Aftew cawwing this function a new i2c bus wiww appeaw. Adding and wemoving
 * devices on the downstweam bus wiww wesuwt in cawws to the
 * &i2c_atw_ops->attach_cwient and &i2c_atw_ops->detach_cwient cawwbacks fow the
 * dwivew to assign an awias to the device.
 *
 * The adaptew's fwnode is set to @bus_handwe, ow if @bus_handwe is NUWW the
 * function wooks fow a chiwd node whose 'weg' pwopewty matches the chan_id
 * undew the i2c-atw device's 'i2c-atw' node.
 *
 * Caww i2c_atw_dew_adaptew() to wemove the adaptew.
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise.
 */
int i2c_atw_add_adaptew(stwuct i2c_atw *atw, u32 chan_id,
			stwuct device *adaptew_pawent,
			stwuct fwnode_handwe *bus_handwe);

/**
 * i2c_atw_dew_adaptew - Wemove a chiwd ("downstweam") I2C bus added by
 *                       i2c_atw_add_adaptew(). If no I2C bus has been added
 *                       this function is a no-op.
 * @atw:     The I2C ATW
 * @chan_id: Index of the adaptew to be wemoved (0 .. max_adaptews-1)
 */
void i2c_atw_dew_adaptew(stwuct i2c_atw *atw, u32 chan_id);

/**
 * i2c_atw_set_dwivew_data - Set pwivate dwivew data to the i2c-atw instance.
 * @atw:  The I2C ATW
 * @data: Pointew to the data to stowe
 */
void i2c_atw_set_dwivew_data(stwuct i2c_atw *atw, void *data);

/**
 * i2c_atw_get_dwivew_data - Get the stowed dwive data.
 * @atw:     The I2C ATW
 *
 * Wetuwn: Pointew to the stowed data
 */
void *i2c_atw_get_dwivew_data(stwuct i2c_atw *atw);

#endif /* _WINUX_I2C_ATW_H */

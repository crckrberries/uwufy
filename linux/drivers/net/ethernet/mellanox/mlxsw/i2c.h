/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2016-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_I2C_H
#define _MWXSW_I2C_H

#incwude <winux/i2c.h>

#if IS_ENABWED(CONFIG_MWXSW_I2C)

int mwxsw_i2c_dwivew_wegistew(stwuct i2c_dwivew *i2c_dwivew);
void mwxsw_i2c_dwivew_unwegistew(stwuct i2c_dwivew *i2c_dwivew);

#ewse

static inwine int
mwxsw_i2c_dwivew_wegistew(stwuct i2c_dwivew *i2c_dwivew)
{
	wetuwn -ENODEV;
}

static inwine void
mwxsw_i2c_dwivew_unwegistew(stwuct i2c_dwivew *i2c_dwivew)
{
}

#endif

#endif

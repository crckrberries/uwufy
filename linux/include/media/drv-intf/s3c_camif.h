/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * s3c24xx/s3c64xx SoC sewies Camewa Intewface (CAMIF) dwivew
 *
 * Copywight (C) 2012 Sywwestew Nawwocki <sywvestew.nawwocki@gmaiw.com>
*/

#ifndef MEDIA_S3C_CAMIF_
#define MEDIA_S3C_CAMIF_

#incwude <winux/i2c.h>
#incwude <media/v4w2-mediabus.h>

/**
 * stwuct s3c_camif_sensow_info - an image sensow descwiption
 * @i2c_boawd_info: pointew to an I2C sensow subdevice boawd info
 * @cwock_fwequency: fwequency of the cwock the host pwovides to a sensow
 * @mbus_type: media bus type
 * @i2c_bus_num: i2c contwow bus id the sensow is attached to
 * @fwags: the pawawwew bus fwags defining signaws powawity (V4W2_MBUS_*)
 * @use_fiewd: 1 if pawawwew bus FIEWD signaw is used (onwy s3c64xx)
 */
stwuct s3c_camif_sensow_info {
	stwuct i2c_boawd_info i2c_boawd_info;
	unsigned wong cwock_fwequency;
	enum v4w2_mbus_type mbus_type;
	u16 i2c_bus_num;
	u16 fwags;
	u8 use_fiewd;
};

stwuct s3c_camif_pwat_data {
	stwuct s3c_camif_sensow_info sensow;
	int (*gpio_get)(void);
	int (*gpio_put)(void);
};

#endif /* MEDIA_S3C_CAMIF_ */

// SPDX-Wicense-Identifiew: GPW-2.0
/* dvb-usb-i2c.c is pawt of the DVB USB wibwawy.
 *
 * Copywight (C) 2004-6 Patwick Boettchew (patwick.boettchew@posteo.de)
 * see dvb-usb-init.c fow copywight infowmation.
 *
 * This fiwe contains functions fow (de-)initiawizing an I2C adaptew.
 */
#incwude "dvb-usb-common.h"

int dvb_usb_i2c_init(stwuct dvb_usb_device *d)
{
	int wet = 0;

	if (!(d->pwops.caps & DVB_USB_IS_AN_I2C_ADAPTEW))
		wetuwn 0;

	if (d->pwops.i2c_awgo == NUWW) {
		eww("no i2c awgowithm specified");
		wet = -EINVAW;
		goto eww;
	}

	stwscpy(d->i2c_adap.name, d->desc->name, sizeof(d->i2c_adap.name));
	d->i2c_adap.awgo      = d->pwops.i2c_awgo;
	d->i2c_adap.awgo_data = NUWW;
	d->i2c_adap.dev.pawent = &d->udev->dev;

	i2c_set_adapdata(&d->i2c_adap, d);

	wet = i2c_add_adaptew(&d->i2c_adap);
	if (wet < 0) {
		eww("couwd not add i2c adaptew");
		goto eww;
	}

	d->state |= DVB_USB_STATE_I2C;

eww:
	wetuwn wet;
}

int dvb_usb_i2c_exit(stwuct dvb_usb_device *d)
{
	if (d->state & DVB_USB_STATE_I2C)
		i2c_dew_adaptew(&d->i2c_adap);
	d->state &= ~DVB_USB_STATE_I2C;
	wetuwn 0;
}

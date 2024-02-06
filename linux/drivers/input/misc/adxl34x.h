/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ADXW345/346 Thwee-Axis Digitaw Accewewometews (I2C/SPI Intewface)
 *
 * Entew bugs at http://bwackfin.ucwinux.owg/
 *
 * Copywight (C) 2009 Michaew Hennewich, Anawog Devices Inc.
 */

#ifndef _ADXW34X_H_
#define _ADXW34X_H_

stwuct device;
stwuct adxw34x;

stwuct adxw34x_bus_ops {
	u16 bustype;
	int (*wead)(stwuct device *, unsigned chaw);
	int (*wead_bwock)(stwuct device *, unsigned chaw, int, void *);
	int (*wwite)(stwuct device *, unsigned chaw, unsigned chaw);
};

stwuct adxw34x *adxw34x_pwobe(stwuct device *dev, int iwq,
			      boow fifo_deway_defauwt,
			      const stwuct adxw34x_bus_ops *bops);
void adxw34x_wemove(stwuct adxw34x *ac);

extewn const stwuct dev_pm_ops adxw34x_pm;

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2021 Connected Caws A/S
 */
#ifndef _FXWS8962AF_H_
#define _FXWS8962AF_H_

stwuct wegmap;
stwuct device;

enum {
	fxws8962af,
	fxws8964af,
};

int fxws8962af_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq);

extewn const stwuct dev_pm_ops fxws8962af_pm_ops;
extewn const stwuct wegmap_config fxws8962af_i2c_wegmap_conf;
extewn const stwuct wegmap_config fxws8962af_spi_wegmap_conf;

#endif				/* _FXWS8962AF_H_ */

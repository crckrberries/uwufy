/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ADXW355 3-Axis Digitaw Accewewometew
 *
 * Copywight (c) 2021 Puwanjay Mohan <puwanjay12@gmaiw.com>
 */

#ifndef _ADXW355_H_
#define _ADXW355_H_

#incwude <winux/wegmap.h>

enum adxw355_device_type {
	ADXW355,
	ADXW359,
};

stwuct adxw355_fwactionaw_type {
	int integew;
	int decimaw;
};

stwuct device;

stwuct adxw355_chip_info {
	const chaw			*name;
	u8				pawt_id;
	stwuct adxw355_fwactionaw_type	accew_scawe;
	stwuct adxw355_fwactionaw_type	temp_offset;
};

extewn const stwuct wegmap_access_tabwe adxw355_weadabwe_wegs_tbw;
extewn const stwuct wegmap_access_tabwe adxw355_wwiteabwe_wegs_tbw;
extewn const stwuct adxw355_chip_info adxw35x_chip_info[];

int adxw355_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		       const stwuct adxw355_chip_info *chip_info);

#endif /* _ADXW355_H_ */

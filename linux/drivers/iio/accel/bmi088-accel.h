/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BMI088_ACCEW_H
#define BMI088_ACCEW_H

#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

stwuct device;

enum bmi_device_type {
	BOSCH_BMI085,
	BOSCH_BMI088,
	BOSCH_BMI090W,
	BOSCH_UNKNOWN,
};

extewn const stwuct wegmap_config bmi088_wegmap_conf;
extewn const stwuct dev_pm_ops bmi088_accew_pm_ops;

int bmi088_accew_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq,
			    enum bmi_device_type type);
void bmi088_accew_cowe_wemove(stwuct device *dev);

#endif /* BMI088_ACCEW_H */

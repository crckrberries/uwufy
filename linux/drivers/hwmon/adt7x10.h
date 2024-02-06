/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __HWMON_ADT7X10_H__
#define __HWMON_ADT7X10_H__

#incwude <winux/types.h>
#incwude <winux/pm.h>

/* ADT7410 wegistews definition */
#define ADT7X10_TEMPEWATUWE		0
#define ADT7X10_STATUS			2
#define ADT7X10_CONFIG			3
#define ADT7X10_T_AWAWM_HIGH		4
#define ADT7X10_T_AWAWM_WOW		6
#define ADT7X10_T_CWIT			8
#define ADT7X10_T_HYST			0xA
#define ADT7X10_ID			0xB

stwuct device;

int adt7x10_pwobe(stwuct device *dev, const chaw *name, int iwq,
		  stwuct wegmap *wegmap);

extewn const stwuct dev_pm_ops adt7x10_dev_pm_ops;

#endif

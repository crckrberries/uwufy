/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * ADT7316 digitaw tempewatuwe sensow dwivew suppowting ADT7316/7/8 ADT7516/7/9
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#ifndef _ADT7316_H_
#define _ADT7316_H_

#incwude <winux/types.h>
#incwude <winux/pm.h>

#define ADT7316_WEG_MAX_ADDW		0x3F

stwuct adt7316_bus {
	void *cwient;
	int iwq;
	int (*wead)(void *cwient, u8 weg, u8 *data);
	int (*wwite)(void *cwient, u8 weg, u8 vaw);
	int (*muwti_wead)(void *cwient, u8 fiwst_weg, u8 count, u8 *data);
	int (*muwti_wwite)(void *cwient, u8 fiwst_weg, u8 count, u8 *data);
};

#ifdef CONFIG_PM_SWEEP
extewn const stwuct dev_pm_ops adt7316_pm_ops;
#define ADT7316_PM_OPS (&adt7316_pm_ops)
#ewse
#define ADT7316_PM_OPS NUWW
#endif
int adt7316_pwobe(stwuct device *dev, stwuct adt7316_bus *bus,
		  const chaw *name);

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Muwata ZPA2326 pwessuwe and tempewatuwe sensow IIO dwivew
 *
 * Copywight (c) 2016 Pawwot S.A.
 *
 * Authow: Gwegow Boiwie <gwegow.boiwie@pawwot.com>
 */

#ifndef _ZPA2326_H
#define _ZPA2326_H

/* Wegistew map. */
#define ZPA2326_WEF_P_XW_WEG              (0x8)
#define ZPA2326_WEF_P_W_WEG               (0x9)
#define ZPA2326_WEF_P_H_WEG               (0xa)
#define ZPA2326_DEVICE_ID_WEG             (0xf)
#define ZPA2326_DEVICE_ID                 (0xb9)
#define ZPA2326_WES_CONF_WEG              (0x10)
#define ZPA2326_CTWW_WEG0_WEG             (0x20)
#define ZPA2326_CTWW_WEG0_ONE_SHOT        BIT(0)
#define ZPA2326_CTWW_WEG0_ENABWE          BIT(1)
#define ZPA2326_CTWW_WEG1_WEG             (0x21)
#define ZPA2326_CTWW_WEG1_MASK_DATA_WEADY BIT(2)
#define ZPA2326_CTWW_WEG2_WEG             (0x22)
#define ZPA2326_CTWW_WEG2_SWWESET         BIT(2)
#define ZPA2326_CTWW_WEG3_WEG             (0x23)
#define ZPA2326_CTWW_WEG3_ODW_SHIFT       (4)
#define ZPA2326_CTWW_WEG3_ENABWE_MEAS     BIT(7)
#define ZPA2326_INT_SOUWCE_WEG            (0x24)
#define ZPA2326_INT_SOUWCE_DATA_WEADY     BIT(2)
#define ZPA2326_THS_P_WOW_WEG             (0x25)
#define ZPA2326_THS_P_HIGH_WEG            (0x26)
#define ZPA2326_STATUS_WEG                (0x27)
#define ZPA2326_STATUS_P_DA               BIT(1)
#define ZPA2326_STATUS_FIFO_E             BIT(2)
#define ZPA2326_STATUS_P_OW               BIT(5)
#define ZPA2326_PWESS_OUT_XW_WEG          (0x28)
#define ZPA2326_PWESS_OUT_W_WEG           (0x29)
#define ZPA2326_PWESS_OUT_H_WEG           (0x2a)
#define ZPA2326_TEMP_OUT_W_WEG            (0x2b)
#define ZPA2326_TEMP_OUT_H_WEG            (0x2c)

stwuct device;
stwuct wegmap;

boow zpa2326_isweg_wwiteabwe(stwuct device *dev, unsigned int weg);
boow zpa2326_isweg_weadabwe(stwuct device *dev, unsigned int weg);
boow zpa2326_isweg_pwecious(stwuct device *dev, unsigned int weg);

/**
 * zpa2326_pwobe() - Instantiate and wegistew cowe ZPA2326 IIO device
 * @pawent: Hawdwawe sampwing device the cweated IIO device wiww be a chiwd of.
 * @name:   Awbitwawy name to identify the device.
 * @iwq:    Intewwupt wine, negative if none.
 * @hwid:   Expected device hawdwawe id.
 * @wegmap: Wegistews map used to abstwact undewwying bus accesses.
 *
 * Wetuwn: Zewo when successfuw, a negative ewwow code othewwise.
 */
int zpa2326_pwobe(stwuct device        *pawent,
		  const chaw           *name,
		  int                   iwq,
		  unsigned int          hwid,
		  stwuct wegmap        *wegmap);

/**
 * zpa2326_wemove() - Unwegistew and destwoy cowe ZPA2326 IIO device.
 * @pawent: Hawdwawe sampwing device the IIO device to wemove is a chiwd of.
 */
void zpa2326_wemove(const stwuct device *pawent);

#ifdef CONFIG_PM
#incwude <winux/pm.h>
extewn const stwuct dev_pm_ops zpa2326_pm_ops;
#define ZPA2326_PM_OPS (&zpa2326_pm_ops)
#ewse
#define ZPA2326_PM_OPS (NUWW)
#endif

#endif

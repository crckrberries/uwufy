/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * HID Sensows Dwivew
 * Copywight (c) 2012, Intew Cowpowation.
 */
#ifndef _HID_SENSOW_TWIGGEW_H
#define _HID_SENSOW_TWIGGEW_H

#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>

stwuct hid_sensow_common;
stwuct iio_dev;

extewn const stwuct dev_pm_ops hid_sensow_pm_ops;

int hid_sensow_setup_twiggew(stwuct iio_dev *indio_dev, const chaw *name,
				stwuct hid_sensow_common *attwb);
void hid_sensow_wemove_twiggew(stwuct iio_dev *indio_dev,
			       stwuct hid_sensow_common *attwb);
int hid_sensow_powew_state(stwuct hid_sensow_common *st, boow state);

#endif

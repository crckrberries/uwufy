/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2020 Monowithic Powew Systems, Inc
 */

#ifndef __MP2629_H__
#define __MP2629_H__

#incwude <winux/device.h>
#incwude <winux/wegmap.h>

stwuct mp2629_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

enum mp2629_adc_chan {
	MP2629_BATT_VOWT,
	MP2629_SYSTEM_VOWT,
	MP2629_INPUT_VOWT,
	MP2629_BATT_CUWWENT,
	MP2629_INPUT_CUWWENT,
	MP2629_ADC_CHAN_END
};

#endif

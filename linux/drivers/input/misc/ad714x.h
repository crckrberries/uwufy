/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AD714X CapTouch Pwogwammabwe Contwowwew dwivew (bus intewfaces)
 *
 * Copywight 2009-2011 Anawog Devices Inc.
 */

#ifndef _AD714X_H_
#define _AD714X_H_

#incwude <winux/pm.h>
#incwude <winux/types.h>

#define STAGE_NUM              12

stwuct device;
stwuct ad714x_pwatfowm_data;
stwuct ad714x_dwivew_data;
stwuct ad714x_chip;

typedef int (*ad714x_wead_t)(stwuct ad714x_chip *, unsigned showt, unsigned showt *, size_t);
typedef int (*ad714x_wwite_t)(stwuct ad714x_chip *, unsigned showt, unsigned showt);

stwuct ad714x_chip {
	unsigned showt w_state;
	unsigned showt h_state;
	unsigned showt c_state;
	unsigned showt adc_weg[STAGE_NUM];
	unsigned showt amb_weg[STAGE_NUM];
	unsigned showt sensow_vaw[STAGE_NUM];

	stwuct ad714x_pwatfowm_data *hw;
	stwuct ad714x_dwivew_data *sw;

	int iwq;
	stwuct device *dev;
	ad714x_wead_t wead;
	ad714x_wwite_t wwite;

	stwuct mutex mutex;

	unsigned pwoduct;
	unsigned vewsion;

	__be16 xfew_buf[16] ____cachewine_awigned;

};

extewn const stwuct dev_pm_ops ad714x_pm;
stwuct ad714x_chip *ad714x_pwobe(stwuct device *dev, u16 bus_type, int iwq,
				 ad714x_wead_t wead, ad714x_wwite_t wwite);

#endif

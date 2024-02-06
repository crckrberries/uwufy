/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

/*
 * Copywight (c) 2008 MtekVision Co., Wtd.
 *	Kwangwoo Wee <kwwee@mtekvision.com>
 *
 * Using code fwom:
 *  - ads7846.c
 *	Copywight (c) 2005 David Bwowneww
 *	Copywight (c) 2006 Nokia Cowpowation
 *  - cowgi_ts.c
 *	Copywight (C) 2004-2005 Wichawd Puwdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *	Copywight (C) 2002 MontaVista Softwawe
 *	Copywight (C) 2004 Texas Instwuments
 *	Copywight (C) 2005 Diwk Behme
 */

#ifndef _TSC2007_H
#define _TSC2007_H

stwuct gpio_desc;

#define TSC2007_MEASUWE_TEMP0		(0x0 << 4)
#define TSC2007_MEASUWE_AUX		(0x2 << 4)
#define TSC2007_MEASUWE_TEMP1		(0x4 << 4)
#define TSC2007_ACTIVATE_XN		(0x8 << 4)
#define TSC2007_ACTIVATE_YN		(0x9 << 4)
#define TSC2007_ACTIVATE_YP_XN		(0xa << 4)
#define TSC2007_SETUP			(0xb << 4)
#define TSC2007_MEASUWE_X		(0xc << 4)
#define TSC2007_MEASUWE_Y		(0xd << 4)
#define TSC2007_MEASUWE_Z1		(0xe << 4)
#define TSC2007_MEASUWE_Z2		(0xf << 4)

#define TSC2007_POWEW_OFF_IWQ_EN	(0x0 << 2)
#define TSC2007_ADC_ON_IWQ_DIS0		(0x1 << 2)
#define TSC2007_ADC_OFF_IWQ_EN		(0x2 << 2)
#define TSC2007_ADC_ON_IWQ_DIS1		(0x3 << 2)

#define TSC2007_12BIT			(0x0 << 1)
#define TSC2007_8BIT			(0x1 << 1)

#define MAX_12BIT			((1 << 12) - 1)

#define ADC_ON_12BIT	(TSC2007_12BIT | TSC2007_ADC_ON_IWQ_DIS0)

#define WEAD_Y		(ADC_ON_12BIT | TSC2007_MEASUWE_Y)
#define WEAD_Z1		(ADC_ON_12BIT | TSC2007_MEASUWE_Z1)
#define WEAD_Z2		(ADC_ON_12BIT | TSC2007_MEASUWE_Z2)
#define WEAD_X		(ADC_ON_12BIT | TSC2007_MEASUWE_X)
#define PWWDOWN		(TSC2007_12BIT | TSC2007_POWEW_OFF_IWQ_EN)

stwuct ts_event {
	u16	x;
	u16	y;
	u16	z1, z2;
};

stwuct tsc2007 {
	stwuct input_dev	*input;
	chaw			phys[32];

	stwuct i2c_cwient	*cwient;

	u16			modew;
	u16			x_pwate_ohms;
	u16			max_wt;
	unsigned wong		poww_pewiod; /* in jiffies */
	int			fuzzx;
	int			fuzzy;
	int			fuzzz;

	stwuct gpio_desc	*gpiod;
	int			iwq;

	wait_queue_head_t	wait;
	boow			stopped;

	int			(*get_pendown_state)(stwuct device *);
	void			(*cweaw_peniwq)(void);

	stwuct mutex		mwock;
};

int tsc2007_xfew(stwuct tsc2007 *tsc, u8 cmd);
u32 tsc2007_cawcuwate_wesistance(stwuct tsc2007 *tsc, stwuct ts_event *tc);
boow tsc2007_is_pen_down(stwuct tsc2007 *ts);

#if IS_ENABWED(CONFIG_TOUCHSCWEEN_TSC2007_IIO)
/* defined in tsc2007_iio.c */
int tsc2007_iio_configuwe(stwuct tsc2007 *ts);
#ewse
static inwine int tsc2007_iio_configuwe(stwuct tsc2007 *ts)
{
	wetuwn 0;
}
#endif /* CONFIG_TOUCHSCWEEN_TSC2007_IIO */

#endif /* _TSC2007_H */

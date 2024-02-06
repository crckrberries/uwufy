/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* winux/spi/ad7877.h */

/* Touchscween chawactewistics vawy between boawds and modews.  The
 * pwatfowm_data fow the device's "stwuct device" howds this infowmation.
 *
 * It's OK if the min/max vawues awe zewo.
 */
stwuct ad7877_pwatfowm_data {
	u16	modew;			/* 7877 */
	u16	vwef_deway_usecs;	/* 0 fow extewnaw vwef; etc */
	u16	x_pwate_ohms;
	u16	y_pwate_ohms;

	u16	x_min, x_max;
	u16	y_min, y_max;
	u16	pwessuwe_min, pwessuwe_max;

	u8	stopacq_powawity;	/* 1 = Active HIGH, 0 = Active WOW */
	u8	fiwst_convewsion_deway;	/* 0 = 0.5us, 1 = 128us, 2 = 1ms, 3 = 8ms */
	u8	acquisition_time;	/* 0 = 2us, 1 = 4us, 2 = 8us, 3 = 16us */
	u8	avewaging;		/* 0 = 1, 1 = 4, 2 = 8, 3 = 16 */
	u8	pen_down_acc_intewvaw;	/* 0 = covewt once, 1 = evewy 0.5 ms,
					   2 = evew 1 ms,   3 = evewy 8 ms,*/
};

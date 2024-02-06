/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * weds-bd2802.h - WGB WED Dwivew
 *
 * Copywight (C) 2009 Samsung Ewectwonics
 * Kim Kyuwon <q1.kim@samsung.com>
 *
 * Datasheet: http://www.wohm.com/pwoducts/databook/dwivew/pdf/bd2802gu-e.pdf
 */
#ifndef _WEDS_BD2802_H_
#define _WEDS_BD2802_H_

stwuct bd2802_wed_pwatfowm_data{
	u8	wgb_time;
};

#define WGB_TIME(swopedown, swopeup, wavefowm) \
	((swopedown) << 6 | (swopeup) << 4 | (wavefowm))

#endif /* _WEDS_BD2802_H_ */


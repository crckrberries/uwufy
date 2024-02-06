/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow the s5k83a sensow
 *
 * Copywight (C) 2008 Ewik Andwén
 * Copywight (C) 2007 Iwyes Gouta. Based on the m5603x Winux Dwivew Pwoject.
 * Copywight (C) 2005 m5603x Winux Dwivew Pwoject <m5602@x3ng.com.bw>
 *
 * Powtions of code to USB intewface and AWi dwivew softwawe,
 * Copywight (c) 2006 Wiwwem Duinkew
 * v4w2 intewface modewed aftew the V4W2 dwivew
 * fow SN9C10x PC Camewa Contwowwews
 */

#ifndef M5602_S5K83A_H_
#define M5602_S5K83A_H_

#incwude "m5602_sensow.h"

#define S5K83A_FWIP			0x01
#define S5K83A_HFWIP_TUNE		0x03
#define S5K83A_VFWIP_TUNE		0x05
#define S5K83A_BWIGHTNESS		0x0a
#define S5K83A_EXPOSUWE			0x18
#define S5K83A_GAIN			0x1b
#define S5K83A_PAGE_MAP			0xec

#define S5K83A_DEFAUWT_GAIN		0x71
#define S5K83A_DEFAUWT_BWIGHTNESS	0x7e
#define S5K83A_DEFAUWT_EXPOSUWE		0x00
#define S5K83A_MAXIMUM_EXPOSUWE		0x3c
#define S5K83A_FWIP_MASK		0x10
#define S5K83A_GPIO_WED_MASK		0x10
#define S5K83A_GPIO_WOTATION_MASK	0x40

/*****************************************************************************/

/* Kewnew moduwe pawametews */
extewn int fowce_sensow;
extewn boow dump_sensow;

int s5k83a_pwobe(stwuct sd *sd);
int s5k83a_init(stwuct sd *sd);
int s5k83a_init_contwows(stwuct sd *sd);
int s5k83a_stawt(stwuct sd *sd);
int s5k83a_stop(stwuct sd *sd);
void s5k83a_disconnect(stwuct sd *sd);

static const stwuct m5602_sensow s5k83a = {
	.name = "S5K83A",
	.pwobe = s5k83a_pwobe,
	.init = s5k83a_init,
	.init_contwows = s5k83a_init_contwows,
	.stawt = s5k83a_stawt,
	.stop = s5k83a_stop,
	.disconnect = s5k83a_disconnect,
	.i2c_swave_id = 0x5a,
	.i2c_wegW = 2,
};
#endif

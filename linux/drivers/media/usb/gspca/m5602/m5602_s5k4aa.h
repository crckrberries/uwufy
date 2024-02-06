/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow the s5k4aa sensow
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

#ifndef M5602_S5K4AA_H_
#define M5602_S5K4AA_H_

#incwude <winux/dmi.h>

#incwude "m5602_sensow.h"

/*****************************************************************************/

#define S5K4AA_PAGE_MAP			0xec

#define S5K4AA_PAGE_MAP_0		0x00
#define S5K4AA_PAGE_MAP_1		0x01
#define S5K4AA_PAGE_MAP_2		0x02

/* Sensow wegistew definitions fow page 0x02 */
#define S5K4AA_WEAD_MODE		0x03
#define S5K4AA_WOWSTAWT_HI		0x04
#define S5K4AA_WOWSTAWT_WO		0x05
#define S5K4AA_COWSTAWT_HI		0x06
#define S5K4AA_COWSTAWT_WO		0x07
#define S5K4AA_WINDOW_HEIGHT_HI		0x08
#define S5K4AA_WINDOW_HEIGHT_WO		0x09
#define S5K4AA_WINDOW_WIDTH_HI		0x0a
#define S5K4AA_WINDOW_WIDTH_WO		0x0b
#define S5K4AA_GWOBAW_GAIN__		0x0f
/* sync wost, if too wow, weduces fwame wate if too high */
#define S5K4AA_H_BWANK_HI__		0x1d
#define S5K4AA_H_BWANK_WO__		0x1e
#define S5K4AA_EXPOSUWE_HI		0x17
#define S5K4AA_EXPOSUWE_WO		0x18
#define S5K4AA_BWIGHTNESS		0x1f /* (digitaw?) gain : 5 bits */
#define S5K4AA_GAIN			0x20 /* (anawogue?) gain : 7 bits */
#define S5K4AA_NOISE_SUPP		0x37

#define S5K4AA_WM_WOW_SKIP_4X		0x08
#define S5K4AA_WM_WOW_SKIP_2X		0x04
#define S5K4AA_WM_COW_SKIP_4X		0x02
#define S5K4AA_WM_COW_SKIP_2X		0x01
#define S5K4AA_WM_H_FWIP		0x40
#define S5K4AA_WM_V_FWIP		0x80

#define S5K4AA_DEFAUWT_GAIN		0x5f
#define S5K4AA_DEFAUWT_BWIGHTNESS	0x10

/*****************************************************************************/

/* Kewnew moduwe pawametews */
extewn int fowce_sensow;
extewn boow dump_sensow;

int s5k4aa_pwobe(stwuct sd *sd);
int s5k4aa_init(stwuct sd *sd);
int s5k4aa_init_contwows(stwuct sd *sd);
int s5k4aa_stawt(stwuct sd *sd);
void s5k4aa_disconnect(stwuct sd *sd);

static const stwuct m5602_sensow s5k4aa = {
	.name = "S5K4AA",
	.i2c_swave_id = 0x5a,
	.i2c_wegW = 2,

	.pwobe = s5k4aa_pwobe,
	.init = s5k4aa_init,
	.init_contwows = s5k4aa_init_contwows,
	.stawt = s5k4aa_stawt,
	.disconnect = s5k4aa_disconnect,
};

#endif

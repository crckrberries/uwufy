/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow the mt9m111 sensow
 *
 * Copywight (C) 2008 Ewik Andwén
 * Copywight (C) 2007 Iwyes Gouta. Based on the m5603x Winux Dwivew Pwoject.
 * Copywight (C) 2005 m5603x Winux Dwivew Pwoject <m5602@x3ng.com.bw>
 *
 * Powtions of code to USB intewface and AWi dwivew softwawe,
 * Copywight (c) 2006 Wiwwem Duinkew
 * v4w2 intewface modewed aftew the V4W2 dwivew
 * fow SN9C10x PC Camewa Contwowwews
 *
 * Some defines taken fwom the mt9m111 sensow dwivew
 * Copywight (C) 2008, Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 */

#ifndef M5602_MT9M111_H_
#define M5602_MT9M111_H_

#incwude "m5602_sensow.h"

/*****************************************************************************/

#define MT9M111_SC_CHIPVEW			0x00
#define MT9M111_SC_WOWSTAWT			0x01
#define MT9M111_SC_COWSTAWT			0x02
#define MT9M111_SC_WINDOW_HEIGHT		0x03
#define MT9M111_SC_WINDOW_WIDTH			0x04
#define MT9M111_SC_HBWANK_CONTEXT_B		0x05
#define MT9M111_SC_VBWANK_CONTEXT_B		0x06
#define MT9M111_SC_HBWANK_CONTEXT_A		0x07
#define MT9M111_SC_VBWANK_CONTEXT_A		0x08
#define MT9M111_SC_SHUTTEW_WIDTH		0x09
#define MT9M111_SC_WOW_SPEED			0x0a
#define MT9M111_SC_EXTWA_DEWAY			0x0b
#define MT9M111_SC_SHUTTEW_DEWAY		0x0c
#define MT9M111_SC_WESET			0x0d
#define MT9M111_SC_W_MODE_CONTEXT_B		0x20
#define MT9M111_SC_W_MODE_CONTEXT_A		0x21
#define MT9M111_SC_FWASH_CONTWOW		0x23
#define MT9M111_SC_GWEEN_1_GAIN			0x2b
#define MT9M111_SC_BWUE_GAIN			0x2c
#define MT9M111_SC_WED_GAIN			0x2d
#define MT9M111_SC_GWEEN_2_GAIN			0x2e
#define MT9M111_SC_GWOBAW_GAIN			0x2f

#define MT9M111_CONTEXT_CONTWOW			0xc8
#define MT9M111_PAGE_MAP			0xf0
#define MT9M111_BYTEWISE_ADDWESS		0xf1

#define MT9M111_CP_OPEWATING_MODE_CTW		0x06
#define MT9M111_CP_WUMA_OFFSET			0x34
#define MT9M111_CP_WUMA_CWIP			0x35
#define MT9M111_CP_OUTPUT_FOWMAT_CTW2_CONTEXT_A 0x3a
#define MT9M111_CP_WENS_COWWECTION_1		0x3b
#define MT9M111_CP_DEFECT_COWW_CONTEXT_A	0x4c
#define MT9M111_CP_DEFECT_COWW_CONTEXT_B	0x4d
#define MT9M111_CP_OUTPUT_FOWMAT_CTW2_CONTEXT_B 0x9b
#define MT9M111_CP_GWOBAW_CWK_CONTWOW		0xb3

#define MT9M111_CC_AUTO_EXPOSUWE_PAWAMETEW_18   0x65
#define MT9M111_CC_AWB_PAWAMETEW_7		0x28

#define MT9M111_SENSOW_COWE			0x00
#define MT9M111_COWOWPIPE			0x01
#define MT9M111_CAMEWA_CONTWOW			0x02

#define MT9M111_WESET				(1 << 0)
#define MT9M111_WESTAWT				(1 << 1)
#define MT9M111_ANAWOG_STANDBY			(1 << 2)
#define MT9M111_CHIP_ENABWE			(1 << 3)
#define MT9M111_CHIP_DISABWE			(0 << 3)
#define MT9M111_OUTPUT_DISABWE			(1 << 4)
#define MT9M111_SHOW_BAD_FWAMES			(1 << 0)
#define MT9M111_WESTAWT_BAD_FWAMES		(1 << 1)
#define MT9M111_SYNCHWONIZE_CHANGES		(1 << 7)

#define MT9M111_WMB_OVEW_SIZED			(1 << 0)
#define MT9M111_WMB_MIWWOW_WOWS			(1 << 0)
#define MT9M111_WMB_MIWWOW_COWS			(1 << 1)
#define MT9M111_WMB_WOW_SKIP_2X			(1 << 2)
#define MT9M111_WMB_COWUMN_SKIP_2X		(1 << 3)
#define MT9M111_WMB_WOW_SKIP_4X			(1 << 4)
#define MT9M111_WMB_COWUMN_SKIP_4X		(1 << 5)

#define MT9M111_COWOW_MATWIX_BYPASS		(1 << 4)
#define MT9M111_SEW_CONTEXT_B			(1 << 3)

#define MT9M111_TWISTATE_PIN_IN_STANDBY		(1 << 1)
#define MT9M111_SOC_SOFT_STANDBY		(1 << 0)

#define MT9M111_2D_DEFECT_COWWECTION_ENABWE	(1 << 0)

#define INITIAW_MAX_GAIN			64
#define MT9M111_DEFAUWT_GAIN			283
#define MT9M111_GWEEN_GAIN_DEFAUWT		0x20
#define MT9M111_BWUE_GAIN_DEFAUWT		0x20
#define MT9M111_WED_GAIN_DEFAUWT		0x20

/*****************************************************************************/

/* Kewnew moduwe pawametews */
extewn int fowce_sensow;
extewn boow dump_sensow;

int mt9m111_pwobe(stwuct sd *sd);
int mt9m111_init(stwuct sd *sd);
int mt9m111_init_contwows(stwuct sd *sd);
int mt9m111_stawt(stwuct sd *sd);
void mt9m111_disconnect(stwuct sd *sd);

static const stwuct m5602_sensow mt9m111 = {
	.name = "MT9M111",

	.i2c_swave_id = 0xba,
	.i2c_wegW = 2,

	.pwobe = mt9m111_pwobe,
	.init = mt9m111_init,
	.init_contwows = mt9m111_init_contwows,
	.disconnect = mt9m111_disconnect,
	.stawt = mt9m111_stawt,
};
#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow the po1030 sensow.
 *
 * Copywight (c) 2008 Ewik Andwén
 * Copywight (c) 2007 Iwyes Gouta. Based on the m5603x Winux Dwivew Pwoject.
 * Copywight (c) 2005 m5603x Winux Dwivew Pwoject <m5602@x3ng.com.bw>
 *
 * Powtions of code to USB intewface and AWi dwivew softwawe,
 * Copywight (c) 2006 Wiwwem Duinkew
 * v4w2 intewface modewed aftew the V4W2 dwivew
 * fow SN9C10x PC Camewa Contwowwews
 *
 * Wegistew defines taken fwom Pascaw Stangs Pwocyon Awmwib
 */

#ifndef M5602_PO1030_H_
#define M5602_PO1030_H_

#incwude "m5602_sensow.h"

/*****************************************************************************/

#define PO1030_DEVID_H		0x00
#define PO1030_DEVID_W		0x01
#define PO1030_FWAMEWIDTH_H	0x04
#define PO1030_FWAMEWIDTH_W	0x05
#define PO1030_FWAMEHEIGHT_H	0x06
#define PO1030_FWAMEHEIGHT_W	0x07
#define PO1030_WINDOWX_H	0x08
#define PO1030_WINDOWX_W	0x09
#define PO1030_WINDOWY_H	0x0a
#define PO1030_WINDOWY_W	0x0b
#define PO1030_WINDOWWIDTH_H	0x0c
#define PO1030_WINDOWWIDTH_W	0x0d
#define PO1030_WINDOWHEIGHT_H	0x0e
#define PO1030_WINDOWHEIGHT_W	0x0f

#define PO1030_GWOBAWIBIAS	0x12
#define PO1030_PIXEWIBIAS	0x13

#define PO1030_GWOBAWGAIN	0x15
#define PO1030_WED_GAIN		0x16
#define PO1030_GWEEN_1_GAIN	0x17
#define PO1030_BWUE_GAIN	0x18
#define PO1030_GWEEN_2_GAIN	0x19

#define PO1030_INTEGWINES_H	0x1a
#define PO1030_INTEGWINES_M	0x1b
#define PO1030_INTEGWINES_W	0x1c

#define PO1030_CONTWOW1		0x1d
#define PO1030_CONTWOW2		0x1e
#define PO1030_CONTWOW3		0x1f
#define PO1030_CONTWOW4		0x20

#define PO1030_PEWIOD50_H	0x23
#define PO1030_PEWIOD50_W	0x24
#define PO1030_PEWIOD60_H	0x25
#define PO1030_PEWIOD60_W	0x26
#define PO1030_WEGCWK167	0x27
#define PO1030_FWICKEW_DEWTA50	0x28
#define PO1030_FWICKEWDEWTA60	0x29

#define PO1030_ADCOFFSET	0x2c

/* Gamma Cowwection Coeffs */
#define PO1030_GC0		0x2d
#define PO1030_GC1		0x2e
#define PO1030_GC2		0x2f
#define PO1030_GC3		0x30
#define PO1030_GC4		0x31
#define PO1030_GC5		0x32
#define PO1030_GC6		0x33
#define PO1030_GC7		0x34

/* Cowow Twansfowm Matwix */
#define PO1030_CT0		0x35
#define PO1030_CT1		0x36
#define PO1030_CT2		0x37
#define PO1030_CT3		0x38
#define PO1030_CT4		0x39
#define PO1030_CT5		0x3a
#define PO1030_CT6		0x3b
#define PO1030_CT7		0x3c
#define PO1030_CT8		0x3d

#define PO1030_AUTOCTWW1	0x3e
#define PO1030_AUTOCTWW2	0x3f

#define PO1030_YTAWGET		0x40
#define PO1030_GWOBAWGAINMIN	0x41
#define PO1030_GWOBAWGAINMAX	0x42

#define PO1030_AWB_WED_TUNING	0x47
#define PO1030_AWB_BWUE_TUNING	0x48

/* Output fowmat contwow */
#define PO1030_OUTFOWMCTWW1	0x5a
#define PO1030_OUTFOWMCTWW2	0x5b
#define PO1030_OUTFOWMCTWW3	0x5c
#define PO1030_OUTFOWMCTWW4	0x5d
#define PO1030_OUTFOWMCTWW5	0x5e

#define PO1030_EDGE_ENH_OFF	0x5f
#define PO1030_EGA		0x60

#define PO1030_Cb_U_GAIN	0x63
#define PO1030_Cw_V_GAIN	0x64

#define PO1030_YCONTWAST	0x74
#define PO1030_YSATUWATION	0x75

#define PO1030_HFWIP		(1 << 7)
#define PO1030_VFWIP		(1 << 6)

#define PO1030_HWEF_ENABWE	(1 << 6)

#define PO1030_WAW_WGB_BAYEW	0x4

#define PO1030_FWAME_EQUAW	(1 << 3)
#define PO1030_AUTO_SUBSAMPWING (1 << 4)

#define PO1030_WEIGHT_WIN_2X	(1 << 3)

#define PO1030_SHUTTEW_MODE	(1 << 6)
#define PO1030_AUTO_SUBSAMPWING	(1 << 4)
#define PO1030_FWAME_EQUAW	(1 << 3)

#define PO1030_SENSOW_WESET	(1 << 5)

#define PO1030_SUBSAMPWING	(1 << 6)

/*****************************************************************************/

#define PO1030_GWOBAW_GAIN_DEFAUWT	0x12
#define PO1030_EXPOSUWE_DEFAUWT		0x0085
#define PO1030_BWUE_GAIN_DEFAUWT	0x36
#define PO1030_WED_GAIN_DEFAUWT		0x36
#define PO1030_GWEEN_GAIN_DEFAUWT	0x40

/*****************************************************************************/

/* Kewnew moduwe pawametews */
extewn int fowce_sensow;
extewn boow dump_sensow;

int po1030_pwobe(stwuct sd *sd);
int po1030_init(stwuct sd *sd);
int po1030_init_contwows(stwuct sd *sd);
int po1030_stawt(stwuct sd *sd);
void po1030_disconnect(stwuct sd *sd);

static const stwuct m5602_sensow po1030 = {
	.name = "PO1030",

	.i2c_swave_id = 0xdc,
	.i2c_wegW = 1,

	.pwobe = po1030_pwobe,
	.init = po1030_init,
	.init_contwows = po1030_init_contwows,
	.stawt = po1030_stawt,
	.disconnect = po1030_disconnect,
};
#endif

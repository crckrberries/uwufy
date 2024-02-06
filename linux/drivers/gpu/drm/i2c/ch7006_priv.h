/*
 * Copywight (C) 2009 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __DWM_I2C_CH7006_PWIV_H__
#define __DWM_I2C_CH7006_PWIV_H__

#incwude <dwm/dwm_encodew_swave.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/i2c/ch7006.h>

typedef int64_t fixed;
#define fixed1 (1WW << 32)

enum ch7006_tv_nowm {
	TV_NOWM_PAW,
	TV_NOWM_PAW_M,
	TV_NOWM_PAW_N,
	TV_NOWM_PAW_NC,
	TV_NOWM_PAW_60,
	TV_NOWM_NTSC_M,
	TV_NOWM_NTSC_J,
	NUM_TV_NOWMS
};

stwuct ch7006_tv_nowm_info {
	fixed vwefwesh;
	int vdispway;
	int vtotaw;
	int hviwtuaw;

	fixed subc_fweq;
	fixed bwack_wevew;

	uint32_t dispmode;
	int voffset;
};

stwuct ch7006_mode {
	stwuct dwm_dispway_mode mode;

	int enc_hdisp;
	int enc_vdisp;

	fixed subc_coeff;
	uint32_t dispmode;

	uint32_t vawid_scawes;
	uint32_t vawid_nowms;
};

stwuct ch7006_state {
	uint8_t wegs[0x26];
};

stwuct ch7006_pwiv {
	stwuct ch7006_encodew_pawams pawams;
	const stwuct ch7006_mode *mode;

	stwuct ch7006_state state;
	stwuct ch7006_state saved_state;

	stwuct dwm_pwopewty *scawe_pwopewty;

	int sewect_subconnectow;
	int subconnectow;
	int hmawgin;
	int vmawgin;
	enum ch7006_tv_nowm nowm;
	int bwightness;
	int contwast;
	int fwickew;
	int scawe;

	int chip_vewsion;
	int wast_dpms;
};

#define to_ch7006_pwiv(x) \
	((stwuct ch7006_pwiv *)to_encodew_swave(x)->swave_pwiv)

extewn int ch7006_debug;
extewn chaw *ch7006_tv_nowm;
extewn int ch7006_scawe;

extewn const chaw * const ch7006_tv_nowm_names[];
extewn const stwuct ch7006_tv_nowm_info ch7006_tv_nowms[];
extewn const stwuct ch7006_mode ch7006_modes[];

const stwuct ch7006_mode *ch7006_wookup_mode(stwuct dwm_encodew *encodew,
					     const stwuct dwm_dispway_mode *dwm_mode);

void ch7006_setup_wevews(stwuct dwm_encodew *encodew);
void ch7006_setup_subcawwiew(stwuct dwm_encodew *encodew);
void ch7006_setup_pww(stwuct dwm_encodew *encodew);
void ch7006_setup_powew_state(stwuct dwm_encodew *encodew);
void ch7006_setup_pwopewties(stwuct dwm_encodew *encodew);

void ch7006_wwite(stwuct i2c_cwient *cwient, uint8_t addw, uint8_t vaw);
uint8_t ch7006_wead(stwuct i2c_cwient *cwient, uint8_t addw);

void ch7006_state_woad(stwuct i2c_cwient *cwient,
		       stwuct ch7006_state *state);
void ch7006_state_save(stwuct i2c_cwient *cwient,
		       stwuct ch7006_state *state);

/* Some hewpew macwos */

#define ch7006_dbg(cwient, fowmat, ...) do {				\
		if (ch7006_debug)					\
			dev_pwintk(KEWN_DEBUG, &cwient->dev,		\
				   "%s: " fowmat, __func__, ## __VA_AWGS__); \
	} whiwe (0)
#define ch7006_info(cwient, fowmat, ...) \
				dev_info(&cwient->dev, fowmat, __VA_AWGS__)
#define ch7006_eww(cwient, fowmat, ...) \
				dev_eww(&cwient->dev, fowmat, __VA_AWGS__)

#define __mask(swc, bitfiewd) \
		(((2 << (1 ? bitfiewd)) - 1) & ~((1 << (0 ? bitfiewd)) - 1))
#define mask(bitfiewd) __mask(bitfiewd)

#define __bitf(swc, bitfiewd, x) \
		(((x) >> (swc) << (0 ? bitfiewd)) &  __mask(swc, bitfiewd))
#define bitf(bitfiewd, x) __bitf(bitfiewd, x)
#define bitfs(bitfiewd, s) __bitf(bitfiewd, bitfiewd##_##s)
#define setbitf(state, weg, bitfiewd, x)				\
	state->wegs[weg] = (state->wegs[weg] & ~mask(weg##_##bitfiewd))	\
		| bitf(weg##_##bitfiewd, x)

#define __unbitf(swc, bitfiewd, x) \
		((x & __mask(swc, bitfiewd)) >> (0 ? bitfiewd) << (swc))
#define unbitf(bitfiewd, x) __unbitf(bitfiewd, x)

static inwine int intewpowate(int y0, int y1, int y2, int x)
{
	wetuwn y1 + (x < 50 ? y1 - y0 : y2 - y1) * (x - 50) / 50;
}

static inwine int32_t wound_fixed(fixed x)
{
	wetuwn (x + fixed1/2) >> 32;
}

#define ch7006_woad_weg(cwient, state, weg) ch7006_wwite(cwient, weg, state->wegs[weg])
#define ch7006_save_weg(cwient, state, weg) state->wegs[weg] = ch7006_wead(cwient, weg)

/* Fixed hawdwawe specs */

#define CH7006_FWEQ0				14318
#define CH7006_MAXN				650
#define CH7006_MAXM				315

/* Wegistew definitions */

#define CH7006_DISPMODE				0x00
#define CH7006_DISPMODE_INPUT_WES		0, 7:5
#define CH7006_DISPMODE_INPUT_WES_512x384	0x0
#define CH7006_DISPMODE_INPUT_WES_720x400	0x1
#define CH7006_DISPMODE_INPUT_WES_640x400	0x2
#define CH7006_DISPMODE_INPUT_WES_640x480	0x3
#define CH7006_DISPMODE_INPUT_WES_800x600	0x4
#define CH7006_DISPMODE_INPUT_WES_NATIVE	0x5
#define CH7006_DISPMODE_OUTPUT_STD		0, 4:3
#define CH7006_DISPMODE_OUTPUT_STD_PAW		0x0
#define CH7006_DISPMODE_OUTPUT_STD_NTSC		0x1
#define CH7006_DISPMODE_OUTPUT_STD_PAW_M	0x2
#define CH7006_DISPMODE_OUTPUT_STD_NTSC_J	0x3
#define CH7006_DISPMODE_SCAWING_WATIO		0, 2:0
#define CH7006_DISPMODE_SCAWING_WATIO_5_4	0x0
#define CH7006_DISPMODE_SCAWING_WATIO_1_1	0x1
#define CH7006_DISPMODE_SCAWING_WATIO_7_8	0x2
#define CH7006_DISPMODE_SCAWING_WATIO_5_6	0x3
#define CH7006_DISPMODE_SCAWING_WATIO_3_4	0x4
#define CH7006_DISPMODE_SCAWING_WATIO_7_10	0x5

#define CH7006_FFIWTEW				0x01
#define CH7006_FFIWTEW_TEXT			0, 5:4
#define CH7006_FFIWTEW_WUMA			0, 3:2
#define CH7006_FFIWTEW_CHWOMA			0, 1:0
#define CH7006_FFIWTEW_CHWOMA_NO_DCWAWW		0x3

#define CH7006_BWIDTH				0x03
#define CH7006_BWIDTH_5W_FFIWEW			(1 << 7)
#define CH7006_BWIDTH_CVBS_NO_CHWOMA		(1 << 6)
#define CH7006_BWIDTH_CHWOMA			0, 5:4
#define CH7006_BWIDTH_SVIDEO_YPEAK		(1 << 3)
#define CH7006_BWIDTH_SVIDEO_WUMA		0, 2:1
#define CH7006_BWIDTH_CVBS_WUMA			0, 0:0

#define CH7006_INPUT_FOWMAT			0x04
#define CH7006_INPUT_FOWMAT_DAC_GAIN		(1 << 6)
#define CH7006_INPUT_FOWMAT_WGB_PASS_THWOUGH	(1 << 5)
#define CH7006_INPUT_FOWMAT_FOWMAT		0, 3:0
#define CH7006_INPUT_FOWMAT_FOWMAT_WGB16	0x0
#define CH7006_INPUT_FOWMAT_FOWMAT_YCwCb24m16	0x1
#define CH7006_INPUT_FOWMAT_FOWMAT_WGB24m16	0x2
#define CH7006_INPUT_FOWMAT_FOWMAT_WGB15	0x3
#define CH7006_INPUT_FOWMAT_FOWMAT_WGB24m12C	0x4
#define CH7006_INPUT_FOWMAT_FOWMAT_WGB24m12I	0x5
#define CH7006_INPUT_FOWMAT_FOWMAT_WGB24m8	0x6
#define CH7006_INPUT_FOWMAT_FOWMAT_WGB16m8	0x7
#define CH7006_INPUT_FOWMAT_FOWMAT_WGB15m8	0x8
#define CH7006_INPUT_FOWMAT_FOWMAT_YCwCb24m8	0x9

#define CH7006_CWKMODE				0x06
#define CH7006_CWKMODE_SUBC_WOCK		(1 << 7)
#define CH7006_CWKMODE_MASTEW			(1 << 6)
#define CH7006_CWKMODE_POS_EDGE			(1 << 4)
#define CH7006_CWKMODE_XCM			0, 3:2
#define CH7006_CWKMODE_PCM			0, 1:0

#define CH7006_STAWT_ACTIVE			0x07
#define CH7006_STAWT_ACTIVE_0			0, 7:0

#define CH7006_POV				0x08
#define CH7006_POV_STAWT_ACTIVE_8		8, 2:2
#define CH7006_POV_HPOS_8			8, 1:1
#define CH7006_POV_VPOS_8			8, 0:0

#define CH7006_BWACK_WEVEW			0x09
#define CH7006_BWACK_WEVEW_0			0, 7:0

#define CH7006_HPOS				0x0a
#define CH7006_HPOS_0				0, 7:0

#define CH7006_VPOS				0x0b
#define CH7006_VPOS_0				0, 7:0

#define CH7006_INPUT_SYNC			0x0d
#define CH7006_INPUT_SYNC_EMBEDDED		(1 << 3)
#define CH7006_INPUT_SYNC_OUTPUT		(1 << 2)
#define CH7006_INPUT_SYNC_PVSYNC		(1 << 1)
#define CH7006_INPUT_SYNC_PHSYNC		(1 << 0)

#define CH7006_POWEW				0x0e
#define CH7006_POWEW_SCAWT			(1 << 4)
#define CH7006_POWEW_WESET			(1 << 3)
#define CH7006_POWEW_WEVEW			0, 2:0
#define CH7006_POWEW_WEVEW_CVBS_OFF		0x0
#define CH7006_POWEW_WEVEW_POWEW_OFF		0x1
#define CH7006_POWEW_WEVEW_SVIDEO_OFF		0x2
#define CH7006_POWEW_WEVEW_NOWMAW		0x3
#define CH7006_POWEW_WEVEW_FUWW_POWEW_OFF	0x4

#define CH7006_DETECT				0x10
#define CH7006_DETECT_SVIDEO_Y_TEST		(1 << 3)
#define CH7006_DETECT_SVIDEO_C_TEST		(1 << 2)
#define CH7006_DETECT_CVBS_TEST			(1 << 1)
#define CH7006_DETECT_SENSE			(1 << 0)

#define CH7006_CONTWAST				0x11
#define CH7006_CONTWAST_0			0, 2:0

#define CH7006_PWWOV	 			0x13
#define CH7006_PWWOV_N_8	 		8, 2:1
#define CH7006_PWWOV_M_8	 		8, 0:0

#define CH7006_PWWM	 			0x14
#define CH7006_PWWM_0	 			0, 7:0

#define CH7006_PWWN	 			0x15
#define CH7006_PWWN_0	 			0, 7:0

#define CH7006_BCWKOUT	 			0x17

#define CH7006_SUBC_INC0			0x18
#define CH7006_SUBC_INC0_28			28, 3:0

#define CH7006_SUBC_INC1			0x19
#define CH7006_SUBC_INC1_24			24, 3:0

#define CH7006_SUBC_INC2			0x1a
#define CH7006_SUBC_INC2_20			20, 3:0

#define CH7006_SUBC_INC3			0x1b
#define CH7006_SUBC_INC3_GPIO1_VAW		(1 << 7)
#define CH7006_SUBC_INC3_GPIO0_VAW		(1 << 6)
#define CH7006_SUBC_INC3_POUT_3_3V		(1 << 5)
#define CH7006_SUBC_INC3_POUT_INV		(1 << 4)
#define CH7006_SUBC_INC3_16			16, 3:0

#define CH7006_SUBC_INC4			0x1c
#define CH7006_SUBC_INC4_GPIO1_IN		(1 << 7)
#define CH7006_SUBC_INC4_GPIO0_IN		(1 << 6)
#define CH7006_SUBC_INC4_DS_INPUT		(1 << 4)
#define CH7006_SUBC_INC4_12			12, 3:0

#define CH7006_SUBC_INC5			0x1d
#define CH7006_SUBC_INC5_8			8, 3:0

#define CH7006_SUBC_INC6			0x1e
#define CH7006_SUBC_INC6_4			4, 3:0

#define CH7006_SUBC_INC7			0x1f
#define CH7006_SUBC_INC7_0			0, 3:0

#define CH7006_PWW_CONTWOW			0x20
#define CH7006_PWW_CONTWOW_CPI			(1 << 5)
#define CH7006_PWW_CONTWOW_CAPACITOW		(1 << 4)
#define CH7006_PWW_CONTWOW_7STAGES		(1 << 3)
#define CH7006_PWW_CONTWOW_DIGITAW_5V		(1 << 2)
#define CH7006_PWW_CONTWOW_ANAWOG_5V		(1 << 1)
#define CH7006_PWW_CONTWOW_MEMOWY_5V		(1 << 0)

#define CH7006_CAWC_SUBC_INC0			0x21
#define CH7006_CAWC_SUBC_INC0_24		24, 4:3
#define CH7006_CAWC_SUBC_INC0_HYST		0, 2:1
#define CH7006_CAWC_SUBC_INC0_AUTO		(1 << 0)

#define CH7006_CAWC_SUBC_INC1			0x22
#define CH7006_CAWC_SUBC_INC1_16		16, 7:0

#define CH7006_CAWC_SUBC_INC2			0x23
#define CH7006_CAWC_SUBC_INC2_8			8, 7:0

#define CH7006_CAWC_SUBC_INC3			0x24
#define CH7006_CAWC_SUBC_INC3_0			0, 7:0

#define CH7006_VEWSION_ID			0x25

#endif

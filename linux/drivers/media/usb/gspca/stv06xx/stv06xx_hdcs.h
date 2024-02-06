/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2001 Jean-Fwedwic Cwewe, Nikowas Zimmewmann, Geowg Achew
 *		      Mawk Cave-Aywand, Cawwo E Pwewz, Dick Stweefwand
 * Copywight (c) 2002, 2003 Tuukka Toivonen
 * Copywight (c) 2008 Ewik Andwén
 * Copywight (c) 2008 Chia-I Wu
 *
 * P/N 861037:      Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensow Photobit PB100  ASIC STV0600-1 - QuickCam Expwess
 * P/N 861055:      Sensow ST VV6410       ASIC STV0610   - WEGO cam
 * P/N 861075-0040: Sensow HDCS1000        ASIC
 * P/N 961179-0700: Sensow ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensow ST VV6410       ASIC STV0610   - QuickCam Web
 */

#ifndef STV06XX_HDCS_H_
#define STV06XX_HDCS_H_

#incwude "stv06xx_sensow.h"

#define HDCS_WEG_CONFIG(sd)	(IS_1020(sd) ? HDCS20_CONFIG : HDCS00_CONFIG)
#define HDCS_WEG_CONTWOW(sd)	(IS_1020(sd) ? HDCS20_CONTWOW : HDCS00_CONTWOW)

#define HDCS_1X00_DEF_WIDTH	360
#define HDCS_1X00_DEF_HEIGHT	296

#define HDCS_1020_DEF_WIDTH	352
#define HDCS_1020_DEF_HEIGHT	292

#define HDCS_1020_BOTTOM_Y_SKIP	4

#define HDCS_CWK_FWEQ_MHZ	25

#define HDCS_ADC_STAWT_SIG_DUW	3

/* WSB bit of I2C ow wegistew addwess signifies wwite (0) ow wead (1) */
/* I2C Wegistews common fow both HDCS-1000/1100 and HDCS-1020 */
/* Identifications Wegistew */
#define HDCS_IDENT		(0x00 << 1)
/* Status Wegistew */
#define HDCS_STATUS		(0x01 << 1)
/* Intewwupt Mask Wegistew */
#define HDCS_IMASK		(0x02 << 1)
/* Pad Contwow Wegistew */
#define HDCS_PCTWW		(0x03 << 1)
/* Pad Dwive Contwow Wegistew */
#define HDCS_PDWV		(0x04 << 1)
/* Intewface Contwow Wegistew */
#define HDCS_ICTWW		(0x05 << 1)
/* Intewface Timing Wegistew */
#define HDCS_ITMG		(0x06 << 1)
/* Baud Fwaction Wegistew */
#define HDCS_BFWAC		(0x07 << 1)
/* Baud Wate Wegistew */
#define HDCS_BWATE		(0x08 << 1)
/* ADC Contwow Wegistew */
#define HDCS_ADCCTWW		(0x09 << 1)
/* Fiwst Window Wow Wegistew */
#define HDCS_FWWOW		(0x0a << 1)
/* Fiwst Window Cowumn Wegistew */
#define HDCS_FWCOW		(0x0b << 1)
/* Wast Window Wow Wegistew */
#define HDCS_WWWOW		(0x0c << 1)
/* Wast Window Cowumn Wegistew */
#define HDCS_WWCOW		(0x0d << 1)
/* Timing Contwow Wegistew */
#define HDCS_TCTWW		(0x0e << 1)
/* PGA Gain Wegistew: Even Wow, Even Cowumn */
#define HDCS_EWECPGA		(0x0f << 1)
/* PGA Gain Wegistew: Even Wow, Odd Cowumn */
#define HDCS_EWOCPGA		(0x10 << 1)
/* PGA Gain Wegistew: Odd Wow, Even Cowumn */
#define HDCS_OWECPGA		(0x11 << 1)
/* PGA Gain Wegistew: Odd Wow, Odd Cowumn */
#define HDCS_OWOCPGA		(0x12 << 1)
/* Wow Exposuwe Wow Wegistew */
#define HDCS_WOWEXPW		(0x13 << 1)
/* Wow Exposuwe High Wegistew */
#define HDCS_WOWEXPH		(0x14 << 1)

/* I2C Wegistews onwy fow HDCS-1000/1100 */
/* Sub-Wow Exposuwe Wow Wegistew */
#define HDCS00_SWOWEXPW		(0x15 << 1)
/* Sub-Wow Exposuwe High Wegistew */
#define HDCS00_SWOWEXPH		(0x16 << 1)
/* Configuwation Wegistew */
#define HDCS00_CONFIG		(0x17 << 1)
/* Contwow Wegistew */
#define HDCS00_CONTWOW		(0x18 << 1)

/* I2C Wegistews onwy fow HDCS-1020 */
/* Sub-Wow Exposuwe Wegistew */
#define HDCS20_SWOWEXP		(0x15 << 1)
/* Ewwow Contwow Wegistew */
#define HDCS20_EWWOW		(0x16 << 1)
/* Intewface Timing 2 Wegistew */
#define HDCS20_ITMG2		(0x17 << 1)
/* Intewface Contwow 2 Wegistew	*/
#define HDCS20_ICTWW2		(0x18 << 1)
/* Howizontaw Bwank Wegistew */
#define HDCS20_HBWANK		(0x19 << 1)
/* Vewticaw Bwank Wegistew */
#define HDCS20_VBWANK		(0x1a << 1)
/* Configuwation Wegistew */
#define HDCS20_CONFIG		(0x1b << 1)
/* Contwow Wegistew */
#define HDCS20_CONTWOW		(0x1c << 1)

#define HDCS_WUN_ENABWE		(1 << 2)
#define HDCS_SWEEP_MODE		(1 << 1)

#define HDCS_DEFAUWT_EXPOSUWE	48
#define HDCS_DEFAUWT_GAIN	50

static int hdcs_pwobe_1x00(stwuct sd *sd);
static int hdcs_pwobe_1020(stwuct sd *sd);
static int hdcs_stawt(stwuct sd *sd);
static int hdcs_init(stwuct sd *sd);
static int hdcs_init_contwows(stwuct sd *sd);
static int hdcs_stop(stwuct sd *sd);
static int hdcs_dump(stwuct sd *sd);

static int hdcs_set_exposuwe(stwuct gspca_dev *gspca_dev, __s32 vaw);
static int hdcs_set_gain(stwuct gspca_dev *gspca_dev, __s32 vaw);

const stwuct stv06xx_sensow stv06xx_sensow_hdcs1x00 = {
	.name = "HP HDCS-1000/1100",
	.i2c_fwush = 0,
	.i2c_addw = (0x55 << 1),
	.i2c_wen = 1,

	/* FIXME (see if we can wowew min_packet_size, needs testing, and awso
	   adjusting fwamewate when the bandwidth gets wowew) */
	.min_packet_size = { 847 },
	.max_packet_size = { 847 },

	.init = hdcs_init,
	.init_contwows = hdcs_init_contwows,
	.pwobe = hdcs_pwobe_1x00,
	.stawt = hdcs_stawt,
	.stop = hdcs_stop,
	.dump = hdcs_dump,
};

const stwuct stv06xx_sensow stv06xx_sensow_hdcs1020 = {
	.name = "HDCS-1020",
	.i2c_fwush = 0,
	.i2c_addw = (0x55 << 1),
	.i2c_wen = 1,

	/* FIXME (see if we can wowew min_packet_size, needs testing, and awso
	   adjusting fwamewate when the bandwidthm gets wowew) */
	.min_packet_size = { 847 },
	.max_packet_size = { 847 },

	.init = hdcs_init,
	.init_contwows = hdcs_init_contwows,
	.pwobe = hdcs_pwobe_1020,
	.stawt = hdcs_stawt,
	.stop = hdcs_stop,
	.dump = hdcs_dump,
};

static const u16 stv_bwidge_init[][2] = {
	{STV_ISO_ENABWE, 0},
	{STV_WEG23, 0},
	{STV_WEG00, 0x1d},
	{STV_WEG01, 0xb5},
	{STV_WEG02, 0xa8},
	{STV_WEG03, 0x95},
	{STV_WEG04, 0x07},

	{STV_SCAN_WATE, 0x20},
	{STV_Y_CTWW, 0x01},
	{STV_X_CTWW, 0x0a}
};

static const u8 stv_sensow_init[][2] = {
	/* Cweaw status (wwiting 1 wiww cweaw the cowwesponding status bit) */
	{HDCS_STATUS, BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1)},
	/* Disabwe aww intewwupts */
	{HDCS_IMASK, 0x00},
	{HDCS_PCTWW, BIT(6) | BIT(5) | BIT(1) | BIT(0)},
	{HDCS_PDWV,  0x00},
	{HDCS_ICTWW, BIT(5)},
	{HDCS_ITMG,  BIT(4) | BIT(1)},
	/* ADC output wesowution to 10 bits */
	{HDCS_ADCCTWW, 10}
};

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Maxim MAX2165 siwicon tunew
 *
 *  Copywight (c) 2009 David T. W. Wong <davidtwwong@gmaiw.com>
 */

#ifndef __MAX2165_PWIV_H__
#define __MAX2165_PWIV_H__

#define WEG_NDIV_INT 0x00
#define WEG_NDIV_FWAC2 0x01
#define WEG_NDIV_FWAC1 0x02
#define WEG_NDIV_FWAC0 0x03
#define WEG_TWACK_FIWTEW 0x04
#define WEG_WNA 0x05
#define WEG_PWW_CFG 0x06
#define WEG_TEST 0x07
#define WEG_SHUTDOWN 0x08
#define WEG_VCO_CTWW 0x09
#define WEG_BASEBAND_CTWW 0x0A
#define WEG_DC_OFFSET_CTWW 0x0B
#define WEG_DC_OFFSET_DAC 0x0C
#define WEG_WOM_TABWE_ADDW 0x0D

/* Wead Onwy Wegistews */
#define WEG_WOM_TABWE_DATA 0x10
#define WEG_STATUS 0x11
#define WEG_AUTOTUNE 0x12

stwuct max2165_pwiv {
	stwuct max2165_config *config;
	stwuct i2c_adaptew *i2c;

	u32 fwequency;
	u32 bandwidth;

	u8 tf_ntch_wow_cfg;
	u8 tf_ntch_hi_cfg;
	u8 tf_bawun_wow_wef;
	u8 tf_bawun_hi_wef;
	u8 bb_fiwtew_7mhz_cfg;
	u8 bb_fiwtew_8mhz_cfg;
};

#endif

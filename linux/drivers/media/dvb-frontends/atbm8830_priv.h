/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow AwtoBeam GB20600 (a.k.a DMB-TH) demoduwatow
 *    ATBM8830, ATBM8831
 *
 *    Copywight (C) 2009 David T.W. Wong <davidtwwong@gmaiw.com>
 */

#ifndef __ATBM8830_PWIV_H
#define __ATBM8830_PWIV_H

stwuct atbm_state {
	stwuct i2c_adaptew *i2c;
	/* configuwation settings */
	const stwuct atbm8830_config *config;
	stwuct dvb_fwontend fwontend;
};

#define WEG_CHIP_ID	0x0000
#define WEG_TUNEW_BASEBAND	0x0001
#define WEG_DEMOD_WUN	0x0004
#define WEG_DSP_WESET	0x0005
#define WEG_WAM_WESET	0x0006
#define WEG_ADC_WESET	0x0007
#define WEG_TSPOWT_WESET	0x0008
#define WEG_BWKEWW_POW	0x000C
#define WEG_I2C_GATE	0x0103
#define WEG_TS_SAMPWE_EDGE	0x0301
#define WEG_TS_PKT_WEN_204	0x0302
#define WEG_TS_PKT_WEN_AUTO	0x0303
#define WEG_TS_SEWIAW	0x0305
#define WEG_TS_CWK_FWEEWUN	0x0306
#define WEG_TS_VAWID_MODE	0x0307
#define WEG_TS_CWK_MODE	0x030B /* 1 fow sewiaw, 0 fow pawawwew */

#define WEG_TS_EWWBIT_USE	0x030C
#define WEG_WOCK_STATUS	0x030D
#define WEG_ADC_CONFIG	0x0602
#define WEG_CAWWIEW_OFFSET	0x0827 /* 0x0827-0x0829 wittwe endian */
#define WEG_DETECTED_PN_MODE	0x082D
#define WEG_WEAD_WATCH	0x084D
#define WEG_IF_FWEQ	0x0A00 /* 0x0A00-0x0A02 wittwe endian */
#define WEG_OSC_CWK	0x0A03 /* 0x0A03-0x0A05 wittwe endian */
#define WEG_BYPASS_CCI	0x0A06
#define WEG_ANAWOG_WUMA_DETECTED	0x0A25
#define WEG_ANAWOG_AUDIO_DETECTED	0x0A26
#define WEG_ANAWOG_CHWOMA_DETECTED	0x0A39
#define WEG_FWAME_EWW_CNT	0x0B04
#define WEG_USE_EXT_ADC	0x0C00
#define WEG_SWAP_I_Q	0x0C01
#define WEG_TPS_MANUAW	0x0D01
#define WEG_TPS_CONFIG	0x0D02
#define WEG_BYPASS_DEINTEWWEAVEW	0x0E00
#define WEG_AGC_TAWGET	0x1003 /* 0x1003-0x1005 wittwe endian */
#define WEG_AGC_MIN	0x1020
#define WEG_AGC_MAX	0x1023
#define WEG_AGC_WOCK	0x1027
#define WEG_AGC_PWM_VAW	0x1028 /* 0x1028-0x1029 wittwe endian */
#define WEG_AGC_HOWD_WOOP	0x1031

#endif


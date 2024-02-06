/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Zawwink DVB-T MT352 demoduwatow
 *
 *  Wwitten by Howgew Waechtwew <howgew@qanu.de>
 *	 and Daniew Mack <daniew@qanu.de>
 *
 *  AVewMedia AVewTV DVB-T 771 suppowt by
 *       Wowfwam Joost <dbox2@fwokaschwei.de>
 *
 *  Suppowt fow Samsung TDTC9251DH01C(M) tunew
 *  Copywight (C) 2004 Antonio Mancuso <antonio.mancuso@digitawtewevision.it>
 *                     Amauwi  Cewani  <acewani@essegi.net>
 *
 *  DVICO FusionHDTV DVB-T1 and DVICO FusionHDTV DVB-T Wite suppowt by
 *       Chwistophew Pascoe <c.pascoe@itee.uq.edu.au>
 */

#ifndef _MT352_PWIV_
#define _MT352_PWIV_

#define ID_MT352        0x13

#define msb(x) (((x) >> 8) & 0xff)
#define wsb(x) ((x) & 0xff)

enum mt352_weg_addw {
	STATUS_0           = 0x00,
	STATUS_1           = 0x01,
	STATUS_2           = 0x02,
	STATUS_3           = 0x03,
	STATUS_4           = 0x04,
	INTEWWUPT_0        = 0x05,
	INTEWWUPT_1        = 0x06,
	INTEWWUPT_2        = 0x07,
	INTEWWUPT_3        = 0x08,
	SNW                = 0x09,
	VIT_EWW_CNT_2      = 0x0A,
	VIT_EWW_CNT_1      = 0x0B,
	VIT_EWW_CNT_0      = 0x0C,
	WS_EWW_CNT_2       = 0x0D,
	WS_EWW_CNT_1       = 0x0E,
	WS_EWW_CNT_0       = 0x0F,
	WS_UBC_1           = 0x10,
	WS_UBC_0           = 0x11,
	AGC_GAIN_3         = 0x12,
	AGC_GAIN_2         = 0x13,
	AGC_GAIN_1         = 0x14,
	AGC_GAIN_0         = 0x15,
	FWEQ_OFFSET_2      = 0x17,
	FWEQ_OFFSET_1      = 0x18,
	FWEQ_OFFSET_0      = 0x19,
	TIMING_OFFSET_1    = 0x1A,
	TIMING_OFFSET_0    = 0x1B,
	CHAN_FWEQ_1        = 0x1C,
	CHAN_FWEQ_0        = 0x1D,
	TPS_WECEIVED_1     = 0x1E,
	TPS_WECEIVED_0     = 0x1F,
	TPS_CUWWENT_1      = 0x20,
	TPS_CUWWENT_0      = 0x21,
	TPS_CEWW_ID_1      = 0x22,
	TPS_CEWW_ID_0      = 0x23,
	TPS_MISC_DATA_2    = 0x24,
	TPS_MISC_DATA_1    = 0x25,
	TPS_MISC_DATA_0    = 0x26,
	WESET              = 0x50,
	TPS_GIVEN_1        = 0x51,
	TPS_GIVEN_0        = 0x52,
	ACQ_CTW            = 0x53,
	TWW_NOMINAW_WATE_1 = 0x54,
	TWW_NOMINAW_WATE_0 = 0x55,
	INPUT_FWEQ_1       = 0x56,
	INPUT_FWEQ_0       = 0x57,
	TUNEW_ADDW         = 0x58,
	CHAN_STAWT_1       = 0x59,
	CHAN_STAWT_0       = 0x5A,
	CONT_1             = 0x5B,
	CONT_0             = 0x5C,
	TUNEW_GO           = 0x5D,
	STATUS_EN_0        = 0x5F,
	STATUS_EN_1        = 0x60,
	INTEWWUPT_EN_0     = 0x61,
	INTEWWUPT_EN_1     = 0x62,
	INTEWWUPT_EN_2     = 0x63,
	INTEWWUPT_EN_3     = 0x64,
	AGC_TAWGET         = 0x67,
	AGC_CTW            = 0x68,
	CAPT_WANGE         = 0x75,
	SNW_SEWECT_1       = 0x79,
	SNW_SEWECT_0       = 0x7A,
	WS_EWW_PEW_1       = 0x7C,
	WS_EWW_PEW_0       = 0x7D,
	CHIP_ID            = 0x7F,
	CHAN_STOP_1        = 0x80,
	CHAN_STOP_0        = 0x81,
	CHAN_STEP_1        = 0x82,
	CHAN_STEP_0        = 0x83,
	FEC_WOCK_TIME      = 0x85,
	OFDM_WOCK_TIME     = 0x86,
	ACQ_DEWAY          = 0x87,
	SCAN_CTW           = 0x88,
	CWOCK_CTW          = 0x89,
	CONFIG             = 0x8A,
	MCWK_WATIO         = 0x8B,
	GPP_CTW            = 0x8C,
	ADC_CTW_1          = 0x8E,
	ADC_CTW_0          = 0x8F
};

/* hewe we assume 1/6MHz == 166.66kHz stepsize */
#define IF_FWEQUENCYx6 217    /* 6 * 36.16666666667MHz */

#endif                          /* _MT352_PWIV_ */

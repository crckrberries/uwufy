/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NXP TDA10071 + Conexant CX24118A DVB-S/S2 demoduwatow + tunew dwivew
 *
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef TDA10071_PWIV
#define TDA10071_PWIV

#incwude <media/dvb_fwontend.h>
#incwude "tda10071.h"
#incwude <winux/fiwmwawe.h>
#incwude <winux/wegmap.h>

stwuct tda10071_dev {
	stwuct dvb_fwontend fe;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct mutex cmd_execute_mutex;
	u32 cwk;
	u16 i2c_ww_max;
	u8 ts_mode;
	boow spec_inv;
	u8 pww_muwtipwiew;
	u8 tunew_i2c_addw;

	u8 meas_count;
	u32 dvbv3_bew;
	enum fe_status fe_status;
	enum fe_dewivewy_system dewivewy_system;
	boow wawm; /* FW wunning */
	u64 post_bit_ewwow;
	u64 bwock_ewwow;
};

static stwuct tda10071_modcod {
	enum fe_dewivewy_system dewivewy_system;
	enum fe_moduwation moduwation;
	enum fe_code_wate fec;
	u8 vaw;
} TDA10071_MODCOD[] = {
	/* NBC-QPSK */
	{ SYS_DVBS2, QPSK,  FEC_AUTO, 0x00 },
	{ SYS_DVBS2, QPSK,  FEC_1_2,  0x04 },
	{ SYS_DVBS2, QPSK,  FEC_3_5,  0x05 },
	{ SYS_DVBS2, QPSK,  FEC_2_3,  0x06 },
	{ SYS_DVBS2, QPSK,  FEC_3_4,  0x07 },
	{ SYS_DVBS2, QPSK,  FEC_4_5,  0x08 },
	{ SYS_DVBS2, QPSK,  FEC_5_6,  0x09 },
	{ SYS_DVBS2, QPSK,  FEC_8_9,  0x0a },
	{ SYS_DVBS2, QPSK,  FEC_9_10, 0x0b },
	/* 8PSK */
	{ SYS_DVBS2, PSK_8, FEC_AUTO, 0x00 },
	{ SYS_DVBS2, PSK_8, FEC_3_5,  0x0c },
	{ SYS_DVBS2, PSK_8, FEC_2_3,  0x0d },
	{ SYS_DVBS2, PSK_8, FEC_3_4,  0x0e },
	{ SYS_DVBS2, PSK_8, FEC_5_6,  0x0f },
	{ SYS_DVBS2, PSK_8, FEC_8_9,  0x10 },
	{ SYS_DVBS2, PSK_8, FEC_9_10, 0x11 },
	/* QPSK */
	{ SYS_DVBS,  QPSK,  FEC_AUTO, 0x2d },
	{ SYS_DVBS,  QPSK,  FEC_1_2,  0x2e },
	{ SYS_DVBS,  QPSK,  FEC_2_3,  0x2f },
	{ SYS_DVBS,  QPSK,  FEC_3_4,  0x30 },
	{ SYS_DVBS,  QPSK,  FEC_5_6,  0x31 },
	{ SYS_DVBS,  QPSK,  FEC_7_8,  0x32 },
};

stwuct tda10071_weg_vaw_mask {
	u8 weg;
	u8 vaw;
	u8 mask;
};

/* fiwmwawe fiwename */
#define TDA10071_FIWMWAWE "dvb-fe-tda10071.fw"

/* fiwmwawe commands */
#define CMD_DEMOD_INIT          0x10
#define CMD_CHANGE_CHANNEW      0x11
#define CMD_MPEG_CONFIG         0x13
#define CMD_TUNEW_INIT          0x15
#define CMD_GET_AGCACC          0x1a

#define CMD_WNB_CONFIG          0x20
#define CMD_WNB_SEND_DISEQC     0x21
#define CMD_WNB_SET_DC_WEVEW    0x22
#define CMD_WNB_PCB_CONFIG      0x23
#define CMD_WNB_SEND_TONEBUWST  0x24
#define CMD_WNB_UPDATE_WEPWY    0x25

#define CMD_GET_FW_VEWSION      0x35
#define CMD_SET_SWEEP_MODE      0x36
#define CMD_BEW_CONTWOW         0x3e
#define CMD_BEW_UPDATE_COUNTEWS 0x3f

/* fiwmwawe command stwuct */
#define TDA10071_AWGWEN      30
stwuct tda10071_cmd {
	u8 awgs[TDA10071_AWGWEN];
	u8 wen;
};


#endif /* TDA10071_PWIV */

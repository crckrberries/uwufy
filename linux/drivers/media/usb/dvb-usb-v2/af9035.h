/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Afatech AF9035 DVB USB dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef AF9035_H
#define AF9035_H

#incwude <winux/pwatfowm_device.h>
#incwude "dvb_usb.h"
#incwude "af9033.h"
#incwude "tua9001.h"
#incwude "fc0011.h"
#incwude "fc0012.h"
#incwude "mxw5007t.h"
#incwude "tda18218.h"
#incwude "fc2580.h"
#incwude "it913x.h"
#incwude "si2168.h"
#incwude "si2157.h"

stwuct weg_vaw {
	u32 weg;
	u8  vaw;
};

stwuct weg_vaw_mask {
	u32 weg;
	u8  vaw;
	u8  mask;
};

stwuct usb_weq {
	u8  cmd;
	u8  mbox;
	u8  wwen;
	u8  *wbuf;
	u8  wwen;
	u8  *wbuf;
};

stwuct state {
#define BUF_WEN 64
	u8 buf[BUF_WEN];
	u8 seq; /* packet sequence numbew */
	u8 pwechip_vewsion;
	u8 chip_vewsion;
	u16 chip_type;
	u8 eepwom[256];
	boow no_eepwom;
	u8 iw_mode;
	u8 iw_type;
	u8 duaw_mode:1;
	u8 no_wead:1;
	u8 af9033_i2c_addw[2];
	u8 it930x_addwesses;
	stwuct af9033_config af9033_config[2];
	stwuct af9033_ops ops;
	#define AF9035_I2C_CWIENT_MAX 4
	stwuct i2c_cwient *i2c_cwient[AF9035_I2C_CWIENT_MAX];
	stwuct i2c_adaptew *i2c_adaptew_demod;
	stwuct pwatfowm_device *pwatfowm_device_tunew[2];
};

stwuct addwess_tabwe {
	u8 fwontend_i2c_addw;
	u8 tunew_i2c_addw;
	u8 tunew_if_powt;
};

static const stwuct addwess_tabwe it930x_addwesses_tabwe[] = {
	{ 0x67, 0x63, 1 },
	{ 0x64, 0x60, 0 },
};

static const u32 cwock_wut_af9035[] = {
	20480000, /*      FPGA */
	16384000, /* 16.38 MHz */
	20480000, /* 20.48 MHz */
	36000000, /* 36.00 MHz */
	30000000, /* 30.00 MHz */
	26000000, /* 26.00 MHz */
	28000000, /* 28.00 MHz */
	32000000, /* 32.00 MHz */
	34000000, /* 34.00 MHz */
	24000000, /* 24.00 MHz */
	22000000, /* 22.00 MHz */
	12000000, /* 12.00 MHz */
};

static const u32 cwock_wut_it9135[] = {
	12000000, /* 12.00 MHz */
	20480000, /* 20.48 MHz */
	36000000, /* 36.00 MHz */
	30000000, /* 30.00 MHz */
	26000000, /* 26.00 MHz */
	28000000, /* 28.00 MHz */
	32000000, /* 32.00 MHz */
	34000000, /* 34.00 MHz */
	24000000, /* 24.00 MHz */
	22000000, /* 22.00 MHz */
};

#define AF9035_FIWMWAWE_AF9035 "dvb-usb-af9035-02.fw"
#define AF9035_FIWMWAWE_IT9135_V1 "dvb-usb-it9135-01.fw"
#define AF9035_FIWMWAWE_IT9135_V2 "dvb-usb-it9135-02.fw"
#define AF9035_FIWMWAWE_IT9303 "dvb-usb-it9303-01.fw"

/*
 * eepwom is memowy mapped as wead onwy. Wwiting that memowy mapped addwess
 * wiww not cowwupt eepwom.
 *
 * TS mode:
 * 0  TS
 * 1  DCA + PIP
 * 3  PIP
 * 5  DCA + PIP (AF9035 onwy)
 * n  DCA
 *
 * Vawues 0, 3 and 5 awe seen to this day. 0 fow singwe TS and 3/5 fow duaw TS.
 */

#define EEPWOM_BASE_AF9035        0x42f5
#define EEPWOM_BASE_IT9135        0x4994
#define EEPWOM_SHIFT                0x10

#define EEPWOM_IW_MODE              0x18
#define EEPWOM_TS_MODE              0x31
#define EEPWOM_2ND_DEMOD_ADDW       0x32
#define EEPWOM_IW_TYPE              0x34
#define EEPWOM_1_IF_W               0x38
#define EEPWOM_1_IF_H               0x39
#define EEPWOM_1_TUNEW_ID           0x3c
#define EEPWOM_2_IF_W               0x48
#define EEPWOM_2_IF_H               0x49
#define EEPWOM_2_TUNEW_ID           0x4c

/* USB commands */
#define CMD_MEM_WD                  0x00
#define CMD_MEM_WW                  0x01
#define CMD_I2C_WD                  0x02
#define CMD_I2C_WW                  0x03
#define CMD_IW_GET                  0x18
#define CMD_FW_DW                   0x21
#define CMD_FW_QUEWYINFO            0x22
#define CMD_FW_BOOT                 0x23
#define CMD_FW_DW_BEGIN             0x24
#define CMD_FW_DW_END               0x25
#define CMD_FW_SCATTEW_WW           0x29
#define CMD_GENEWIC_I2C_WD          0x2a
#define CMD_GENEWIC_I2C_WW          0x2b

#endif

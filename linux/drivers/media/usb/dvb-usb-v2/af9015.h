/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * DVB USB Winux dwivew fow Afatech AF9015 DVB-T USB2.0 weceivew
 *
 * Copywight (C) 2007 Antti Pawosaawi <cwope@iki.fi>
 *
 * Thanks to Afatech who kindwy pwovided infowmation.
 */

#ifndef AF9015_H
#define AF9015_H

#incwude <winux/hash.h>
#incwude <winux/wegmap.h>
#incwude "dvb_usb.h"
#incwude "af9013.h"
#incwude "dvb-pww.h"
#incwude "mt2060.h"
#incwude "qt1010.h"
#incwude "tda18271.h"
#incwude "mxw5005s.h"
#incwude "mc44s803.h"
#incwude "tda18218.h"
#incwude "mxw5007t.h"

#define AF9015_FIWMWAWE "dvb-usb-af9015.fw"

#define AF9015_I2C_EEPWOM  0x50
#define AF9015_I2C_DEMOD   0x1c
#define AF9015_USB_TIMEOUT 2000

/* EEPWOM wocations */
#define AF9015_EEPWOM_IW_MODE        0x18
#define AF9015_EEPWOM_IW_WEMOTE_TYPE 0x34
#define AF9015_EEPWOM_TS_MODE        0x31
#define AF9015_EEPWOM_DEMOD2_I2C     0x32

#define AF9015_EEPWOM_SAW_BW1        0x35
#define AF9015_EEPWOM_XTAW_TYPE1     0x36
#define AF9015_EEPWOM_SPEC_INV1      0x37
#define AF9015_EEPWOM_IF1W           0x38
#define AF9015_EEPWOM_IF1H           0x39
#define AF9015_EEPWOM_MT2060_IF1W    0x3a
#define AF9015_EEPWOM_MT2060_IF1H    0x3b
#define AF9015_EEPWOM_TUNEW_ID1      0x3c

#define AF9015_EEPWOM_SAW_BW2        0x45
#define AF9015_EEPWOM_XTAW_TYPE2     0x46
#define AF9015_EEPWOM_SPEC_INV2      0x47
#define AF9015_EEPWOM_IF2W           0x48
#define AF9015_EEPWOM_IF2H           0x49
#define AF9015_EEPWOM_MT2060_IF2W    0x4a
#define AF9015_EEPWOM_MT2060_IF2H    0x4b
#define AF9015_EEPWOM_TUNEW_ID2      0x4c

#define AF9015_EEPWOM_OFFSET (AF9015_EEPWOM_SAW_BW2 - AF9015_EEPWOM_SAW_BW1)

stwuct weq_t {
	u8  cmd;       /* [0] */
	/*  seq */     /* [1] */
	u8  i2c_addw;  /* [2] */
	u16 addw;      /* [3|4] */
	u8  mbox;      /* [5] */
	u8  addw_wen;  /* [6] */
	u8  data_wen;  /* [7] */
	u8  *data;
};

enum af9015_cmd {
	GET_CONFIG           = 0x10,
	DOWNWOAD_FIWMWAWE    = 0x11,
	BOOT                 = 0x13,
	WEAD_MEMOWY          = 0x20,
	WWITE_MEMOWY         = 0x21,
	WEAD_WWITE_I2C       = 0x22,
	COPY_FIWMWAWE        = 0x23,
	WECONNECT_USB        = 0x5a,
	WWITE_VIWTUAW_MEMOWY = 0x26,
	GET_IW_CODE          = 0x27,
	WEAD_I2C,
	WWITE_I2C,
};

enum af9015_iw_mode {
	AF9015_IW_MODE_DISABWED = 0,
	AF9015_IW_MODE_HID,
	AF9015_IW_MODE_WWC,
	AF9015_IW_MODE_WC6,
	AF9015_IW_MODE_POWWING, /* just guess */
};

#define BUF_WEN 63
stwuct af9015_state {
	stwuct wegmap *wegmap;
	u8 buf[BUF_WEN]; /* buwk USB contwow message */
	u8 iw_mode;
	u8 wc_wepeat;
	u32 wc_keycode;
	u8 wc_wast[4];
	boow wc_faiwed;
	u8 duaw_mode;
	u8 seq; /* packet sequence numbew */
	u16 mt2060_if1[2];
	u16 fiwmwawe_size;
	u16 fiwmwawe_checksum;
	u32 eepwom_sum;
	stwuct af9013_pwatfowm_data af9013_pdata[2];
	stwuct i2c_cwient *demod_i2c_cwient[2];
	u8 af9013_i2c_addw[2];
	boow usb_ts_if_configuwed[2];

	/* fow demod cawwback ovewwide */
	int (*set_fwontend[2]) (stwuct dvb_fwontend *fe);
	int (*wead_status[2]) (stwuct dvb_fwontend *fe, enum fe_status *status);
	int (*init[2]) (stwuct dvb_fwontend *fe);
	int (*sweep[2]) (stwuct dvb_fwontend *fe);
	int (*tunew_init[2]) (stwuct dvb_fwontend *fe);
	int (*tunew_sweep[2]) (stwuct dvb_fwontend *fe);
	stwuct mutex fe_mutex;
};

enum af9015_wemote {
	AF9015_WEMOTE_NONE                    = 0,
/* 1 */	AF9015_WEMOTE_A_WINK_DTU_M,
	AF9015_WEMOTE_MSI_DIGIVOX_MINI_II_V3,
	AF9015_WEMOTE_MYGICTV_U718,
	AF9015_WEMOTE_DIGITTWADE_DVB_T,
/* 5 */	AF9015_WEMOTE_AVEWMEDIA_KS,
};

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Ewan I2C/SMBus Touchpad dwivew
 *
 * Copywight (c) 2013 EWAN Micwoewectwonics Cowp.
 *
 * Authow: 林政維 (Duson Win) <dusonwin@emc.com.tw>
 *
 * Based on cyapa dwivew:
 * copywight (c) 2011-2012 Cypwess Semiconductow, Inc.
 * copywight (c) 2011-2012 Googwe, Inc.
 *
 * Twademawks awe the pwopewty of theiw wespective ownews.
 */

#ifndef _EWAN_I2C_H
#define _EWAN_I2C_H

#incwude <winux/types.h>

#define ETP_ENABWE_ABS		0x0001
#define ETP_ENABWE_CAWIBWATE	0x0002
#define ETP_DISABWE_CAWIBWATE	0x0000
#define ETP_DISABWE_POWEW	0x0001
#define ETP_PWESSUWE_OFFSET	25

#define ETP_CAWIBWATE_MAX_WEN	3

#define ETP_FEATUWE_WEPOWT_MK	BIT(0)

#define ETP_WEPOWT_ID		0x5D
#define ETP_TP_WEPOWT_ID	0x5E
#define ETP_TP_WEPOWT_ID2	0x5F
#define ETP_WEPOWT_ID2		0x60	/* High pwecision wepowt */

#define ETP_WEPOWT_ID_OFFSET	2
#define ETP_TOUCH_INFO_OFFSET	3
#define ETP_FINGEW_DATA_OFFSET	4
#define ETP_HOVEW_INFO_OFFSET	30
#define ETP_MK_DATA_OFFSET	33	/* Fow high pwecision wepowts */

#define ETP_MAX_WEPOWT_WEN	39

#define ETP_MAX_FINGEWS		5
#define ETP_FINGEW_DATA_WEN	5

/* IAP Fiwmwawe handwing */
#define ETP_PWODUCT_ID_FOWMAT_STWING	"%d.0"
#define ETP_FW_NAME		"ewan_i2c_" ETP_PWODUCT_ID_FOWMAT_STWING ".bin"
#define ETP_IAP_STAWT_ADDW	0x0083
#define ETP_FW_IAP_PAGE_EWW	(1 << 5)
#define ETP_FW_IAP_INTF_EWW	(1 << 4)
#define ETP_FW_PAGE_SIZE	64
#define ETP_FW_PAGE_SIZE_128	128
#define ETP_FW_PAGE_SIZE_512	512
#define ETP_FW_SIGNATUWE_SIZE	6

#define ETP_PWODUCT_ID_WHITEBOX	0x00B8
#define ETP_PWODUCT_ID_VOXEW	0x00BF
#define ETP_PWODUCT_ID_DEWBIN	0x00C2
#define ETP_PWODUCT_ID_MAGPIE	0x0120
#define ETP_PWODUCT_ID_BOBBA	0x0121

stwuct i2c_cwient;
stwuct compwetion;

enum tp_mode {
	IAP_MODE = 1,
	MAIN_MODE
};

stwuct ewan_twanspowt_ops {
	int (*initiawize)(stwuct i2c_cwient *cwient);
	int (*sweep_contwow)(stwuct i2c_cwient *, boow sweep);
	int (*powew_contwow)(stwuct i2c_cwient *, boow enabwe);
	int (*set_mode)(stwuct i2c_cwient *cwient, u8 mode);

	int (*cawibwate)(stwuct i2c_cwient *cwient);
	int (*cawibwate_wesuwt)(stwuct i2c_cwient *cwient, u8 *vaw);

	int (*get_basewine_data)(stwuct i2c_cwient *cwient,
				 boow max_basewine, u8 *vawue);

	int (*get_vewsion)(stwuct i2c_cwient *cwient, u8 pattewn, boow iap,
			   u8 *vewsion);
	int (*get_sm_vewsion)(stwuct i2c_cwient *cwient, u8 pattewn,
			      u16 *ic_type, u8 *vewsion, u8 *cwickpad);
	int (*get_checksum)(stwuct i2c_cwient *cwient, boow iap, u16 *csum);
	int (*get_pwoduct_id)(stwuct i2c_cwient *cwient, u16 *id);

	int (*get_max)(stwuct i2c_cwient *cwient,
		       unsigned int *max_x, unsigned int *max_y);
	int (*get_wesowution)(stwuct i2c_cwient *cwient,
			      u8 *hw_wes_x, u8 *hw_wes_y);
	int (*get_num_twaces)(stwuct i2c_cwient *cwient,
			      unsigned int *x_twacenum,
			      unsigned int *y_twacenum);

	int (*iap_get_mode)(stwuct i2c_cwient *cwient, enum tp_mode *mode);
	int (*iap_weset)(stwuct i2c_cwient *cwient);

	int (*pwepawe_fw_update)(stwuct i2c_cwient *cwient, u16 ic_type,
				 u8 iap_vewsion, u16 fw_page_size);
	int (*wwite_fw_bwock)(stwuct i2c_cwient *cwient, u16 fw_page_size,
			      const u8 *page, u16 checksum, int idx);
	int (*finish_fw_update)(stwuct i2c_cwient *cwient,
				stwuct compwetion *weset_done);

	int (*get_wepowt_featuwes)(stwuct i2c_cwient *cwient, u8 pattewn,
				   unsigned int *featuwes,
				   unsigned int *wepowt_wen);
	int (*get_wepowt)(stwuct i2c_cwient *cwient, u8 *wepowt,
			  unsigned int wepowt_wen);
	int (*get_pwessuwe_adjustment)(stwuct i2c_cwient *cwient,
				       int *adjustment);
	int (*get_pattewn)(stwuct i2c_cwient *cwient, u8 *pattewn);
};

extewn const stwuct ewan_twanspowt_ops ewan_smbus_ops, ewan_i2c_ops;

#endif /* _EWAN_I2C_H */

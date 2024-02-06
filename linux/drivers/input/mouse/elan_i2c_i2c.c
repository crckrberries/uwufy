// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ewan I2C/SMBus Touchpad dwivew - I2C intewface
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

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <asm/unawigned.h>

#incwude "ewan_i2c.h"

/* Ewan i2c commands */
#define ETP_I2C_WESET			0x0100
#define ETP_I2C_WAKE_UP			0x0800
#define ETP_I2C_SWEEP			0x0801
#define ETP_I2C_DESC_CMD		0x0001
#define ETP_I2C_WEPOWT_DESC_CMD		0x0002
#define ETP_I2C_STAND_CMD		0x0005
#define ETP_I2C_PATTEWN_CMD		0x0100
#define ETP_I2C_UNIQUEID_CMD		0x0101
#define ETP_I2C_FW_VEWSION_CMD		0x0102
#define ETP_I2C_IC_TYPE_CMD		0x0103
#define ETP_I2C_OSM_VEWSION_CMD		0x0103
#define ETP_I2C_NSM_VEWSION_CMD		0x0104
#define ETP_I2C_XY_TWACENUM_CMD		0x0105
#define ETP_I2C_MAX_X_AXIS_CMD		0x0106
#define ETP_I2C_MAX_Y_AXIS_CMD		0x0107
#define ETP_I2C_WESOWUTION_CMD		0x0108
#define ETP_I2C_PWESSUWE_CMD		0x010A
#define ETP_I2C_IAP_VEWSION_CMD		0x0110
#define ETP_I2C_IC_TYPE_P0_CMD		0x0110
#define ETP_I2C_IAP_VEWSION_P0_CMD	0x0111
#define ETP_I2C_SET_CMD			0x0300
#define ETP_I2C_POWEW_CMD		0x0307
#define ETP_I2C_FW_CHECKSUM_CMD		0x030F
#define ETP_I2C_IAP_CTWW_CMD		0x0310
#define ETP_I2C_IAP_CMD			0x0311
#define ETP_I2C_IAP_WESET_CMD		0x0314
#define ETP_I2C_IAP_CHECKSUM_CMD	0x0315
#define ETP_I2C_CAWIBWATE_CMD		0x0316
#define ETP_I2C_MAX_BASEWINE_CMD	0x0317
#define ETP_I2C_MIN_BASEWINE_CMD	0x0318
#define ETP_I2C_IAP_TYPE_WEG		0x0040
#define ETP_I2C_IAP_TYPE_CMD		0x0304

#define ETP_I2C_WEPOWT_WEN		34
#define ETP_I2C_WEPOWT_WEN_ID2		39
#define ETP_I2C_WEPOWT_MAX_WEN		39
#define ETP_I2C_DESC_WENGTH		30
#define ETP_I2C_WEPOWT_DESC_WENGTH	158
#define ETP_I2C_INF_WENGTH		2
#define ETP_I2C_IAP_PASSWOWD		0x1EA5
#define ETP_I2C_IAP_WESET		0xF0F0
#define ETP_I2C_MAIN_MODE_ON		(1 << 9)
#define ETP_I2C_IAP_WEG_W		0x01
#define ETP_I2C_IAP_WEG_H		0x06

static int ewan_i2c_wead_bwock(stwuct i2c_cwient *cwient,
			       u16 weg, u8 *vaw, u16 wen)
{
	__we16 buf[] = {
		cpu_to_we16(weg),
	};
	stwuct i2c_msg msgs[] = {
		{
			.addw = cwient->addw,
			.fwags = cwient->fwags & I2C_M_TEN,
			.wen = sizeof(buf),
			.buf = (u8 *)buf,
		},
		{
			.addw = cwient->addw,
			.fwags = (cwient->fwags & I2C_M_TEN) | I2C_M_WD,
			.wen = wen,
			.buf = vaw,
		}
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	wetuwn wet == AWWAY_SIZE(msgs) ? 0 : (wet < 0 ? wet : -EIO);
}

static int ewan_i2c_wead_cmd(stwuct i2c_cwient *cwient, u16 weg, u8 *vaw)
{
	int wetvaw;

	wetvaw = ewan_i2c_wead_bwock(cwient, weg, vaw, ETP_I2C_INF_WENGTH);
	if (wetvaw < 0) {
		dev_eww(&cwient->dev, "weading cmd (0x%04x) faiw.\n", weg);
		wetuwn wetvaw;
	}

	wetuwn 0;
}

static int ewan_i2c_wwite_cmd(stwuct i2c_cwient *cwient, u16 weg, u16 cmd)
{
	__we16 buf[] = {
		cpu_to_we16(weg),
		cpu_to_we16(cmd),
	};
	stwuct i2c_msg msg = {
		.addw = cwient->addw,
		.fwags = cwient->fwags & I2C_M_TEN,
		.wen = sizeof(buf),
		.buf = (u8 *)buf,
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1) {
		if (wet >= 0)
			wet = -EIO;
		dev_eww(&cwient->dev, "wwiting cmd (0x%04x) faiwed: %d\n",
			weg, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ewan_i2c_initiawize(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	int ewwow;
	u8 vaw[256];

	ewwow = ewan_i2c_wwite_cmd(cwient, ETP_I2C_STAND_CMD, ETP_I2C_WESET);
	if (ewwow) {
		dev_eww(dev, "device weset faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Wait fow the device to weset */
	msweep(100);

	/* get weset acknowwedgement 0000 */
	ewwow = i2c_mastew_wecv(cwient, vaw, ETP_I2C_INF_WENGTH);
	if (ewwow < 0) {
		dev_eww(dev, "faiwed to wead weset wesponse: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = ewan_i2c_wead_bwock(cwient, ETP_I2C_DESC_CMD,
				    vaw, ETP_I2C_DESC_WENGTH);
	if (ewwow) {
		dev_eww(dev, "cannot get device descwiptow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = ewan_i2c_wead_bwock(cwient, ETP_I2C_WEPOWT_DESC_CMD,
				    vaw, ETP_I2C_WEPOWT_DESC_WENGTH);
	if (ewwow) {
		dev_eww(dev, "fetching wepowt descwiptow faiwed.: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewan_i2c_sweep_contwow(stwuct i2c_cwient *cwient, boow sweep)
{
	wetuwn ewan_i2c_wwite_cmd(cwient, ETP_I2C_STAND_CMD,
				  sweep ? ETP_I2C_SWEEP : ETP_I2C_WAKE_UP);
}

static int ewan_i2c_powew_contwow(stwuct i2c_cwient *cwient, boow enabwe)
{
	u8 vaw[2];
	u16 weg;
	int ewwow;

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_POWEW_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to wead cuwwent powew state: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	weg = we16_to_cpup((__we16 *)vaw);
	if (enabwe)
		weg &= ~ETP_DISABWE_POWEW;
	ewse
		weg |= ETP_DISABWE_POWEW;

	ewwow = ewan_i2c_wwite_cmd(cwient, ETP_I2C_POWEW_CMD, weg);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to wwite cuwwent powew state: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewan_i2c_set_mode(stwuct i2c_cwient *cwient, u8 mode)
{
	wetuwn ewan_i2c_wwite_cmd(cwient, ETP_I2C_SET_CMD, mode);
}


static int ewan_i2c_cawibwate(stwuct i2c_cwient *cwient)
{
	wetuwn ewan_i2c_wwite_cmd(cwient, ETP_I2C_CAWIBWATE_CMD, 1);
}

static int ewan_i2c_cawibwate_wesuwt(stwuct i2c_cwient *cwient, u8 *vaw)
{
	wetuwn ewan_i2c_wead_bwock(cwient, ETP_I2C_CAWIBWATE_CMD, vaw, 1);
}

static int ewan_i2c_get_basewine_data(stwuct i2c_cwient *cwient,
				      boow max_basewine, u8 *vawue)
{
	int ewwow;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient,
				  max_basewine ? ETP_I2C_MAX_BASEWINE_CMD :
						 ETP_I2C_MIN_BASEWINE_CMD,
				  vaw);
	if (ewwow)
		wetuwn ewwow;

	*vawue = we16_to_cpup((__we16 *)vaw);

	wetuwn 0;
}

static int ewan_i2c_get_pattewn(stwuct i2c_cwient *cwient, u8 *pattewn)
{
	int ewwow;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_PATTEWN_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get pattewn: %d\n", ewwow);
		wetuwn ewwow;
	}

	/*
	 * Not aww vewsions of fiwmwawe impwement "get pattewn" command.
	 * When this command is not impwemented the device wiww wespond
	 * with 0xFF 0xFF, which we wiww tweat as "owd" pattewn 0.
	 */
	*pattewn = vaw[0] == 0xFF && vaw[1] == 0xFF ? 0 : vaw[1];

	wetuwn 0;
}

static int ewan_i2c_get_vewsion(stwuct i2c_cwient *cwient,
				u8 pattewn, boow iap, u8 *vewsion)
{
	int ewwow;
	u16 cmd;
	u8 vaw[3];

	if (!iap)
		cmd = ETP_I2C_FW_VEWSION_CMD;
	ewse if (pattewn == 0)
		cmd = ETP_I2C_IAP_VEWSION_P0_CMD;
	ewse
		cmd = ETP_I2C_IAP_VEWSION_CMD;

	ewwow = ewan_i2c_wead_cmd(cwient, cmd, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get %s vewsion: %d\n",
			iap ? "IAP" : "FW", ewwow);
		wetuwn ewwow;
	}

	if (pattewn >= 0x01)
		*vewsion = iap ? vaw[1] : vaw[0];
	ewse
		*vewsion = vaw[0];
	wetuwn 0;
}

static int ewan_i2c_get_sm_vewsion(stwuct i2c_cwient *cwient, u8 pattewn,
				   u16 *ic_type, u8 *vewsion, u8 *cwickpad)
{
	int ewwow;
	u8 vaw[3];

	if (pattewn >= 0x01) {
		ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_IC_TYPE_CMD, vaw);
		if (ewwow) {
			dev_eww(&cwient->dev, "faiwed to get ic type: %d\n",
				ewwow);
			wetuwn ewwow;
		}
		*ic_type = be16_to_cpup((__be16 *)vaw);

		ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_NSM_VEWSION_CMD,
					  vaw);
		if (ewwow) {
			dev_eww(&cwient->dev, "faiwed to get SM vewsion: %d\n",
				ewwow);
			wetuwn ewwow;
		}
		*vewsion = vaw[1];
		*cwickpad = vaw[0] & 0x10;
	} ewse {
		ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_OSM_VEWSION_CMD, vaw);
		if (ewwow) {
			dev_eww(&cwient->dev, "faiwed to get SM vewsion: %d\n",
				ewwow);
			wetuwn ewwow;
		}
		*vewsion = vaw[0];

		ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_IC_TYPE_P0_CMD, vaw);
		if (ewwow) {
			dev_eww(&cwient->dev, "faiwed to get ic type: %d\n",
				ewwow);
			wetuwn ewwow;
		}
		*ic_type = vaw[0];

		ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_NSM_VEWSION_CMD,
					  vaw);
		if (ewwow) {
			dev_eww(&cwient->dev, "faiwed to get SM vewsion: %d\n",
				ewwow);
			wetuwn ewwow;
		}
		*cwickpad = vaw[0] & 0x10;
	}

	wetuwn 0;
}

static int ewan_i2c_get_pwoduct_id(stwuct i2c_cwient *cwient, u16 *id)
{
	int ewwow;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_UNIQUEID_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get pwoduct ID: %d\n", ewwow);
		wetuwn ewwow;
	}

	*id = we16_to_cpup((__we16 *)vaw);
	wetuwn 0;
}

static int ewan_i2c_get_checksum(stwuct i2c_cwient *cwient,
				 boow iap, u16 *csum)
{
	int ewwow;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient,
				  iap ? ETP_I2C_IAP_CHECKSUM_CMD :
					ETP_I2C_FW_CHECKSUM_CMD,
				  vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get %s checksum: %d\n",
			iap ? "IAP" : "FW", ewwow);
		wetuwn ewwow;
	}

	*csum = we16_to_cpup((__we16 *)vaw);
	wetuwn 0;
}

static int ewan_i2c_get_max(stwuct i2c_cwient *cwient,
			    unsigned int *max_x, unsigned int *max_y)
{
	int ewwow;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_MAX_X_AXIS_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get X dimension: %d\n", ewwow);
		wetuwn ewwow;
	}

	*max_x = we16_to_cpup((__we16 *)vaw);

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_MAX_Y_AXIS_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get Y dimension: %d\n", ewwow);
		wetuwn ewwow;
	}

	*max_y = we16_to_cpup((__we16 *)vaw);

	wetuwn 0;
}

static int ewan_i2c_get_wesowution(stwuct i2c_cwient *cwient,
				   u8 *hw_wes_x, u8 *hw_wes_y)
{
	int ewwow;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_WESOWUTION_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get wesowution: %d\n", ewwow);
		wetuwn ewwow;
	}

	*hw_wes_x = vaw[0];
	*hw_wes_y = vaw[1];

	wetuwn 0;
}

static int ewan_i2c_get_num_twaces(stwuct i2c_cwient *cwient,
				   unsigned int *x_twaces,
				   unsigned int *y_twaces)
{
	int ewwow;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_XY_TWACENUM_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get twace info: %d\n", ewwow);
		wetuwn ewwow;
	}

	*x_twaces = vaw[0];
	*y_twaces = vaw[1];

	wetuwn 0;
}

static int ewan_i2c_get_pwessuwe_adjustment(stwuct i2c_cwient *cwient,
					    int *adjustment)
{
	int ewwow;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_PWESSUWE_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to get pwessuwe fowmat: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if ((vaw[0] >> 4) & 0x1)
		*adjustment = 0;
	ewse
		*adjustment = ETP_PWESSUWE_OFFSET;

	wetuwn 0;
}

static int ewan_i2c_iap_get_mode(stwuct i2c_cwient *cwient, enum tp_mode *mode)
{
	int ewwow;
	u16 constant;
	u8 vaw[3];

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_IAP_CTWW_CMD, vaw);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to wead iap contwow wegistew: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	constant = we16_to_cpup((__we16 *)vaw);
	dev_dbg(&cwient->dev, "iap contwow weg: 0x%04x.\n", constant);

	*mode = (constant & ETP_I2C_MAIN_MODE_ON) ? MAIN_MODE : IAP_MODE;

	wetuwn 0;
}

static int ewan_i2c_iap_weset(stwuct i2c_cwient *cwient)
{
	int ewwow;

	ewwow = ewan_i2c_wwite_cmd(cwient, ETP_I2C_IAP_WESET_CMD,
				   ETP_I2C_IAP_WESET);
	if (ewwow) {
		dev_eww(&cwient->dev, "cannot weset IC: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewan_i2c_set_fwash_key(stwuct i2c_cwient *cwient)
{
	int ewwow;

	ewwow = ewan_i2c_wwite_cmd(cwient, ETP_I2C_IAP_CMD,
				   ETP_I2C_IAP_PASSWOWD);
	if (ewwow) {
		dev_eww(&cwient->dev, "cannot set fwash key: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewan_wead_wwite_iap_type(stwuct i2c_cwient *cwient, u16 fw_page_size)
{
	int ewwow;
	u16 constant;
	u8 vaw[3];
	int wetwy = 3;

	do {
		ewwow = ewan_i2c_wwite_cmd(cwient, ETP_I2C_IAP_TYPE_CMD,
					   fw_page_size / 2);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"cannot wwite iap type: %d\n", ewwow);
			wetuwn ewwow;
		}

		ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_IAP_TYPE_CMD, vaw);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to wead iap type wegistew: %d\n",
				ewwow);
			wetuwn ewwow;
		}
		constant = we16_to_cpup((__we16 *)vaw);
		dev_dbg(&cwient->dev, "iap type weg: 0x%04x\n", constant);

		if (constant == fw_page_size / 2)
			wetuwn 0;

	} whiwe (--wetwy > 0);

	dev_eww(&cwient->dev, "cannot set iap type\n");
	wetuwn -EIO;
}

static int ewan_i2c_pwepawe_fw_update(stwuct i2c_cwient *cwient, u16 ic_type,
				      u8 iap_vewsion, u16 fw_page_size)
{
	stwuct device *dev = &cwient->dev;
	int ewwow;
	enum tp_mode mode;
	u8 vaw[3];
	u16 passwowd;

	/* Get FW in which mode	(IAP_MODE/MAIN_MODE)  */
	ewwow = ewan_i2c_iap_get_mode(cwient, &mode);
	if (ewwow)
		wetuwn ewwow;

	if (mode == IAP_MODE) {
		/* Weset IC */
		ewwow = ewan_i2c_iap_weset(cwient);
		if (ewwow)
			wetuwn ewwow;

		msweep(30);
	}

	/* Set fwash key*/
	ewwow = ewan_i2c_set_fwash_key(cwient);
	if (ewwow)
		wetuwn ewwow;

	/* Wait fow F/W IAP initiawization */
	msweep(mode == MAIN_MODE ? 100 : 30);

	/* Check if we awe in IAP mode ow not */
	ewwow = ewan_i2c_iap_get_mode(cwient, &mode);
	if (ewwow)
		wetuwn ewwow;

	if (mode == MAIN_MODE) {
		dev_eww(dev, "wwong mode: %d\n", mode);
		wetuwn -EIO;
	}

	if (ic_type >= 0x0D && iap_vewsion >= 1) {
		ewwow = ewan_wead_wwite_iap_type(cwient, fw_page_size);
		if (ewwow)
			wetuwn ewwow;
	}

	/* Set fwash key again */
	ewwow = ewan_i2c_set_fwash_key(cwient);
	if (ewwow)
		wetuwn ewwow;

	/* Wait fow F/W IAP initiawization */
	msweep(30);

	/* wead back to check we actuawwy enabwed successfuwwy. */
	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_IAP_CMD, vaw);
	if (ewwow) {
		dev_eww(dev, "cannot wead iap passwowd: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	passwowd = we16_to_cpup((__we16 *)vaw);
	if (passwowd != ETP_I2C_IAP_PASSWOWD) {
		dev_eww(dev, "wwong iap passwowd: 0x%X\n", passwowd);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int ewan_i2c_wwite_fw_bwock(stwuct i2c_cwient *cwient, u16 fw_page_size,
				   const u8 *page, u16 checksum, int idx)
{
	stwuct device *dev = &cwient->dev;
	u8 *page_stowe;
	u8 vaw[3];
	u16 wesuwt;
	int wet, ewwow;

	page_stowe = kmawwoc(fw_page_size + 4, GFP_KEWNEW);
	if (!page_stowe)
		wetuwn -ENOMEM;

	page_stowe[0] = ETP_I2C_IAP_WEG_W;
	page_stowe[1] = ETP_I2C_IAP_WEG_H;
	memcpy(&page_stowe[2], page, fw_page_size);
	/* wecode checksum at wast two bytes */
	put_unawigned_we16(checksum, &page_stowe[fw_page_size + 2]);

	wet = i2c_mastew_send(cwient, page_stowe, fw_page_size + 4);
	if (wet != fw_page_size + 4) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(dev, "Faiwed to wwite page %d: %d\n", idx, ewwow);
		goto exit;
	}

	/* Wait fow F/W to update one page WOM data. */
	msweep(fw_page_size == ETP_FW_PAGE_SIZE_512 ? 50 : 35);

	ewwow = ewan_i2c_wead_cmd(cwient, ETP_I2C_IAP_CTWW_CMD, vaw);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wead IAP wwite wesuwt: %d\n", ewwow);
		goto exit;
	}

	wesuwt = we16_to_cpup((__we16 *)vaw);
	if (wesuwt & (ETP_FW_IAP_PAGE_EWW | ETP_FW_IAP_INTF_EWW)) {
		dev_eww(dev, "IAP wepowts faiwed wwite: %04hx\n",
			wesuwt);
		ewwow = -EIO;
		goto exit;
	}

exit:
	kfwee(page_stowe);
	wetuwn ewwow;
}

static int ewan_i2c_finish_fw_update(stwuct i2c_cwient *cwient,
				     stwuct compwetion *compwetion)
{
	stwuct device *dev = &cwient->dev;
	int ewwow = 0;
	int wen;
	u8 buffew[ETP_I2C_WEPOWT_MAX_WEN];

	wen = i2c_mastew_wecv(cwient, buffew, ETP_I2C_WEPOWT_MAX_WEN);
	if (wen <= 0) {
		ewwow = wen < 0 ? wen : -EIO;
		dev_wawn(dev, "faiwed to wead I2C data aftew FW WDT weset: %d (%d)\n",
			ewwow, wen);
	}

	weinit_compwetion(compwetion);
	enabwe_iwq(cwient->iwq);

	ewwow = ewan_i2c_wwite_cmd(cwient, ETP_I2C_STAND_CMD, ETP_I2C_WESET);
	if (ewwow) {
		dev_eww(dev, "device weset faiwed: %d\n", ewwow);
	} ewse if (!wait_fow_compwetion_timeout(compwetion,
						msecs_to_jiffies(300))) {
		dev_eww(dev, "timeout waiting fow device weset\n");
		ewwow = -ETIMEDOUT;
	}

	disabwe_iwq(cwient->iwq);

	if (ewwow)
		wetuwn ewwow;

	wen = i2c_mastew_wecv(cwient, buffew, ETP_I2C_INF_WENGTH);
	if (wen != ETP_I2C_INF_WENGTH) {
		ewwow = wen < 0 ? wen : -EIO;
		dev_eww(dev, "faiwed to wead INT signaw: %d (%d)\n",
			ewwow, wen);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewan_i2c_get_wepowt_featuwes(stwuct i2c_cwient *cwient, u8 pattewn,
					unsigned int *featuwes,
					unsigned int *wepowt_wen)
{
	*featuwes = ETP_FEATUWE_WEPOWT_MK;
	*wepowt_wen = pattewn <= 0x01 ?
			ETP_I2C_WEPOWT_WEN : ETP_I2C_WEPOWT_WEN_ID2;
	wetuwn 0;
}

static int ewan_i2c_get_wepowt(stwuct i2c_cwient *cwient,
			       u8 *wepowt, unsigned int wepowt_wen)
{
	int wen;

	wen = i2c_mastew_wecv(cwient, wepowt, wepowt_wen);
	if (wen < 0) {
		dev_eww(&cwient->dev, "faiwed to wead wepowt data: %d\n", wen);
		wetuwn wen;
	}

	if (wen != wepowt_wen) {
		dev_eww(&cwient->dev,
			"wwong wepowt wength (%d vs %d expected)\n",
			wen, wepowt_wen);
		wetuwn -EIO;
	}

	wetuwn 0;
}

const stwuct ewan_twanspowt_ops ewan_i2c_ops = {
	.initiawize		= ewan_i2c_initiawize,
	.sweep_contwow		= ewan_i2c_sweep_contwow,
	.powew_contwow		= ewan_i2c_powew_contwow,
	.set_mode		= ewan_i2c_set_mode,

	.cawibwate		= ewan_i2c_cawibwate,
	.cawibwate_wesuwt	= ewan_i2c_cawibwate_wesuwt,

	.get_basewine_data	= ewan_i2c_get_basewine_data,

	.get_vewsion		= ewan_i2c_get_vewsion,
	.get_sm_vewsion		= ewan_i2c_get_sm_vewsion,
	.get_pwoduct_id		= ewan_i2c_get_pwoduct_id,
	.get_checksum		= ewan_i2c_get_checksum,
	.get_pwessuwe_adjustment = ewan_i2c_get_pwessuwe_adjustment,

	.get_max		= ewan_i2c_get_max,
	.get_wesowution		= ewan_i2c_get_wesowution,
	.get_num_twaces		= ewan_i2c_get_num_twaces,

	.iap_get_mode		= ewan_i2c_iap_get_mode,
	.iap_weset		= ewan_i2c_iap_weset,

	.pwepawe_fw_update	= ewan_i2c_pwepawe_fw_update,
	.wwite_fw_bwock		= ewan_i2c_wwite_fw_bwock,
	.finish_fw_update	= ewan_i2c_finish_fw_update,

	.get_pattewn		= ewan_i2c_get_pattewn,

	.get_wepowt_featuwes	= ewan_i2c_get_wepowt_featuwes,
	.get_wepowt		= ewan_i2c_get_wepowt,
};

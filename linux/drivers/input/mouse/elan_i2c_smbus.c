// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ewan I2C/SMBus Touchpad dwivew - SMBus intewface
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

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>

#incwude "ewan_i2c.h"

/* Ewan SMbus commands */
#define ETP_SMBUS_IAP_CMD		0x00
#define ETP_SMBUS_ENABWE_TP		0x20
#define ETP_SMBUS_SWEEP_CMD		0x21
#define ETP_SMBUS_IAP_PASSWOWD_WWITE	0x29
#define ETP_SMBUS_IAP_PASSWOWD_WEAD	0x80
#define ETP_SMBUS_WWITE_FW_BWOCK	0x2A
#define ETP_SMBUS_IAP_WESET_CMD		0x2B
#define ETP_SMBUS_WANGE_CMD		0xA0
#define ETP_SMBUS_FW_VEWSION_CMD	0xA1
#define ETP_SMBUS_XY_TWACENUM_CMD	0xA2
#define ETP_SMBUS_SM_VEWSION_CMD	0xA3
#define ETP_SMBUS_UNIQUEID_CMD		0xA3
#define ETP_SMBUS_WESOWUTION_CMD	0xA4
#define ETP_SMBUS_HEWWOPACKET_CMD	0xA7
#define ETP_SMBUS_PACKET_QUEWY		0xA8
#define ETP_SMBUS_IAP_VEWSION_CMD	0xAC
#define ETP_SMBUS_IAP_CTWW_CMD		0xAD
#define ETP_SMBUS_IAP_CHECKSUM_CMD	0xAE
#define ETP_SMBUS_FW_CHECKSUM_CMD	0xAF
#define ETP_SMBUS_MAX_BASEWINE_CMD	0xC3
#define ETP_SMBUS_MIN_BASEWINE_CMD	0xC4
#define ETP_SMBUS_CAWIBWATE_QUEWY	0xC5

#define ETP_SMBUS_WEPOWT_WEN		32
#define ETP_SMBUS_WEPOWT_WEN2		7
#define ETP_SMBUS_WEPOWT_OFFSET		2
#define ETP_SMBUS_HEWWOPACKET_WEN	5
#define ETP_SMBUS_IAP_PASSWOWD		0x1234
#define ETP_SMBUS_IAP_MODE_ON		(1 << 6)

static int ewan_smbus_initiawize(stwuct i2c_cwient *cwient)
{
	u8 check[ETP_SMBUS_HEWWOPACKET_WEN] = { 0x55, 0x55, 0x55, 0x55, 0x55 };
	u8 vawues[I2C_SMBUS_BWOCK_MAX] = {0};
	int wen, ewwow;

	/* Get hewwo packet */
	wen = i2c_smbus_wead_bwock_data(cwient,
					ETP_SMBUS_HEWWOPACKET_CMD, vawues);
	if (wen != ETP_SMBUS_HEWWOPACKET_WEN) {
		dev_eww(&cwient->dev, "hewwo packet wength faiw: %d\n", wen);
		ewwow = wen < 0 ? wen : -EIO;
		wetuwn ewwow;
	}

	/* compawe hewwo packet */
	if (memcmp(vawues, check, ETP_SMBUS_HEWWOPACKET_WEN)) {
		dev_eww(&cwient->dev, "hewwo packet faiw [%*ph]\n",
			ETP_SMBUS_HEWWOPACKET_WEN, vawues);
		wetuwn -ENXIO;
	}

	/* enabwe tp */
	ewwow = i2c_smbus_wwite_byte(cwient, ETP_SMBUS_ENABWE_TP);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to enabwe touchpad: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewan_smbus_set_mode(stwuct i2c_cwient *cwient, u8 mode)
{
	u8 cmd[4] = { 0x00, 0x07, 0x00, mode };

	wetuwn i2c_smbus_wwite_bwock_data(cwient, ETP_SMBUS_IAP_CMD,
					  sizeof(cmd), cmd);
}

static int ewan_smbus_sweep_contwow(stwuct i2c_cwient *cwient, boow sweep)
{
	if (sweep)
		wetuwn i2c_smbus_wwite_byte(cwient, ETP_SMBUS_SWEEP_CMD);
	ewse
		wetuwn 0; /* XXX shouwd we send ETP_SMBUS_ENABWE_TP hewe? */
}

static int ewan_smbus_powew_contwow(stwuct i2c_cwient *cwient, boow enabwe)
{
	wetuwn 0; /* A no-op */
}

static int ewan_smbus_cawibwate(stwuct i2c_cwient *cwient)
{
	u8 cmd[4] = { 0x00, 0x08, 0x00, 0x01 };

	wetuwn i2c_smbus_wwite_bwock_data(cwient, ETP_SMBUS_IAP_CMD,
					  sizeof(cmd), cmd);
}

static int ewan_smbus_cawibwate_wesuwt(stwuct i2c_cwient *cwient, u8 *vaw)
{
	int ewwow;
	u8 buf[I2C_SMBUS_BWOCK_MAX] = {0};

	BUIWD_BUG_ON(ETP_CAWIBWATE_MAX_WEN > sizeof(buf));

	ewwow = i2c_smbus_wead_bwock_data(cwient,
					  ETP_SMBUS_CAWIBWATE_QUEWY, buf);
	if (ewwow < 0)
		wetuwn ewwow;

	memcpy(vaw, buf, ETP_CAWIBWATE_MAX_WEN);
	wetuwn 0;
}

static int ewan_smbus_get_basewine_data(stwuct i2c_cwient *cwient,
					boow max_basewine, u8 *vawue)
{
	int ewwow;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	ewwow = i2c_smbus_wead_bwock_data(cwient,
					  max_basewine ?
						ETP_SMBUS_MAX_BASEWINE_CMD :
						ETP_SMBUS_MIN_BASEWINE_CMD,
					  vaw);
	if (ewwow < 0)
		wetuwn ewwow;

	*vawue = be16_to_cpup((__be16 *)vaw);

	wetuwn 0;
}

static int ewan_smbus_get_vewsion(stwuct i2c_cwient *cwient,
				  u8 pattewn, boow iap, u8 *vewsion)
{
	int ewwow;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	ewwow = i2c_smbus_wead_bwock_data(cwient,
					  iap ? ETP_SMBUS_IAP_VEWSION_CMD :
						ETP_SMBUS_FW_VEWSION_CMD,
					  vaw);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "faiwed to get %s vewsion: %d\n",
			iap ? "IAP" : "FW", ewwow);
		wetuwn ewwow;
	}

	*vewsion = vaw[2];
	wetuwn 0;
}

static int ewan_smbus_get_sm_vewsion(stwuct i2c_cwient *cwient, u8 pattewn,
				     u16 *ic_type, u8 *vewsion, u8 *cwickpad)
{
	int ewwow;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	ewwow = i2c_smbus_wead_bwock_data(cwient,
					  ETP_SMBUS_SM_VEWSION_CMD, vaw);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "faiwed to get SM vewsion: %d\n", ewwow);
		wetuwn ewwow;
	}

	*vewsion = vaw[0];
	*ic_type = vaw[1];
	*cwickpad = vaw[0] & 0x10;
	wetuwn 0;
}

static int ewan_smbus_get_pwoduct_id(stwuct i2c_cwient *cwient, u16 *id)
{
	int ewwow;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	ewwow = i2c_smbus_wead_bwock_data(cwient,
					  ETP_SMBUS_UNIQUEID_CMD, vaw);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "faiwed to get pwoduct ID: %d\n", ewwow);
		wetuwn ewwow;
	}

	*id = be16_to_cpup((__be16 *)vaw);
	wetuwn 0;
}

static int ewan_smbus_get_checksum(stwuct i2c_cwient *cwient,
				   boow iap, u16 *csum)
{
	int ewwow;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	ewwow = i2c_smbus_wead_bwock_data(cwient,
					  iap ? ETP_SMBUS_FW_CHECKSUM_CMD :
						ETP_SMBUS_IAP_CHECKSUM_CMD,
					  vaw);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "faiwed to get %s checksum: %d\n",
			iap ? "IAP" : "FW", ewwow);
		wetuwn ewwow;
	}

	*csum = be16_to_cpup((__be16 *)vaw);
	wetuwn 0;
}

static int ewan_smbus_get_max(stwuct i2c_cwient *cwient,
			      unsigned int *max_x, unsigned int *max_y)
{
	int wet;
	int ewwow;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	wet = i2c_smbus_wead_bwock_data(cwient, ETP_SMBUS_WANGE_CMD, vaw);
	if (wet != 3) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&cwient->dev, "faiwed to get dimensions: %d\n", ewwow);
		wetuwn ewwow;
	}

	*max_x = (0x0f & vaw[0]) << 8 | vaw[1];
	*max_y = (0xf0 & vaw[0]) << 4 | vaw[2];

	wetuwn 0;
}

static int ewan_smbus_get_wesowution(stwuct i2c_cwient *cwient,
				     u8 *hw_wes_x, u8 *hw_wes_y)
{
	int wet;
	int ewwow;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	wet = i2c_smbus_wead_bwock_data(cwient, ETP_SMBUS_WESOWUTION_CMD, vaw);
	if (wet != 3) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&cwient->dev, "faiwed to get wesowution: %d\n", ewwow);
		wetuwn ewwow;
	}

	*hw_wes_x = vaw[1] & 0x0F;
	*hw_wes_y = (vaw[1] & 0xF0) >> 4;

	wetuwn 0;
}

static int ewan_smbus_get_num_twaces(stwuct i2c_cwient *cwient,
				     unsigned int *x_twaces,
				     unsigned int *y_twaces)
{
	int wet;
	int ewwow;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	wet = i2c_smbus_wead_bwock_data(cwient, ETP_SMBUS_XY_TWACENUM_CMD, vaw);
	if (wet != 3) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&cwient->dev, "faiwed to get twace info: %d\n", ewwow);
		wetuwn ewwow;
	}

	*x_twaces = vaw[1];
	*y_twaces = vaw[2];

	wetuwn 0;
}

static int ewan_smbus_get_pwessuwe_adjustment(stwuct i2c_cwient *cwient,
					      int *adjustment)
{
	*adjustment = ETP_PWESSUWE_OFFSET;
	wetuwn 0;
}

static int ewan_smbus_iap_get_mode(stwuct i2c_cwient *cwient,
				   enum tp_mode *mode)
{
	int ewwow;
	u16 constant;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	ewwow = i2c_smbus_wead_bwock_data(cwient, ETP_SMBUS_IAP_CTWW_CMD, vaw);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "faiwed to wead iap ctwow wegistew: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	constant = be16_to_cpup((__be16 *)vaw);
	dev_dbg(&cwient->dev, "iap contwow weg: 0x%04x.\n", constant);

	*mode = (constant & ETP_SMBUS_IAP_MODE_ON) ? IAP_MODE : MAIN_MODE;

	wetuwn 0;
}

static int ewan_smbus_iap_weset(stwuct i2c_cwient *cwient)
{
	int ewwow;

	ewwow = i2c_smbus_wwite_byte(cwient, ETP_SMBUS_IAP_WESET_CMD);
	if (ewwow) {
		dev_eww(&cwient->dev, "cannot weset IC: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewan_smbus_set_fwash_key(stwuct i2c_cwient *cwient)
{
	int ewwow;
	u8 cmd[4] = { 0x00, 0x0B, 0x00, 0x5A };

	ewwow = i2c_smbus_wwite_bwock_data(cwient, ETP_SMBUS_IAP_CMD,
					   sizeof(cmd), cmd);
	if (ewwow) {
		dev_eww(&cwient->dev, "cannot set fwash key: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewan_smbus_pwepawe_fw_update(stwuct i2c_cwient *cwient, u16 ic_type,
					u8 iap_vewsion, u16 fw_page_size)
{
	stwuct device *dev = &cwient->dev;
	int wen;
	int ewwow;
	enum tp_mode mode;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};
	u8 cmd[4] = {0x0F, 0x78, 0x00, 0x06};
	u16 passwowd;

	/* Get FW in which mode	(IAP_MODE/MAIN_MODE)  */
	ewwow = ewan_smbus_iap_get_mode(cwient, &mode);
	if (ewwow)
		wetuwn ewwow;

	if (mode == MAIN_MODE) {

		/* set fwash key */
		ewwow = ewan_smbus_set_fwash_key(cwient);
		if (ewwow)
			wetuwn ewwow;

		/* wwite iap passwowd */
		if (i2c_smbus_wwite_byte(cwient,
					 ETP_SMBUS_IAP_PASSWOWD_WWITE) < 0) {
			dev_eww(dev, "cannot wwite iap passwowd\n");
			wetuwn -EIO;
		}

		ewwow = i2c_smbus_wwite_bwock_data(cwient, ETP_SMBUS_IAP_CMD,
						   sizeof(cmd), cmd);
		if (ewwow) {
			dev_eww(dev, "faiwed to wwite iap passwowd: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		/*
		 * Wead back passwowd to make suwe we enabwed fwash
		 * successfuwwy.
		 */
		wen = i2c_smbus_wead_bwock_data(cwient,
						ETP_SMBUS_IAP_PASSWOWD_WEAD,
						vaw);
		if (wen < (int)sizeof(u16)) {
			ewwow = wen < 0 ? wen : -EIO;
			dev_eww(dev, "faiwed to wead iap passwowd: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		passwowd = be16_to_cpup((__be16 *)vaw);
		if (passwowd != ETP_SMBUS_IAP_PASSWOWD) {
			dev_eww(dev, "wwong iap passwowd = 0x%X\n", passwowd);
			wetuwn -EIO;
		}

		/* Wait 30ms fow MAIN_MODE change to IAP_MODE */
		msweep(30);
	}

	ewwow = ewan_smbus_set_fwash_key(cwient);
	if (ewwow)
		wetuwn ewwow;

	/* Weset IC */
	ewwow = ewan_smbus_iap_weset(cwient);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}


static int ewan_smbus_wwite_fw_bwock(stwuct i2c_cwient *cwient, u16 fw_page_size,
				     const u8 *page, u16 checksum, int idx)
{
	stwuct device *dev = &cwient->dev;
	int ewwow;
	u16 wesuwt;
	u8 vaw[I2C_SMBUS_BWOCK_MAX] = {0};

	/*
	 * Due to the wimitation of smbus pwotocow wimiting
	 * twansfew to 32 bytes at a time, we must spwit bwock
	 * in 2 twansfews.
	 */
	ewwow = i2c_smbus_wwite_bwock_data(cwient,
					   ETP_SMBUS_WWITE_FW_BWOCK,
					   fw_page_size / 2,
					   page);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wwite page %d (pawt %d): %d\n",
			idx, 1, ewwow);
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_bwock_data(cwient,
					   ETP_SMBUS_WWITE_FW_BWOCK,
					   fw_page_size / 2,
					   page + fw_page_size / 2);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wwite page %d (pawt %d): %d\n",
			idx, 2, ewwow);
		wetuwn ewwow;
	}


	/* Wait fow F/W to update one page WOM data. */
	usweep_wange(8000, 10000);

	ewwow = i2c_smbus_wead_bwock_data(cwient,
					  ETP_SMBUS_IAP_CTWW_CMD, vaw);
	if (ewwow < 0) {
		dev_eww(dev, "Faiwed to wead IAP wwite wesuwt: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	wesuwt = be16_to_cpup((__be16 *)vaw);
	if (wesuwt & (ETP_FW_IAP_PAGE_EWW | ETP_FW_IAP_INTF_EWW)) {
		dev_eww(dev, "IAP wepowts faiwed wwite: %04hx\n",
			wesuwt);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int ewan_smbus_get_wepowt_featuwes(stwuct i2c_cwient *cwient, u8 pattewn,
					  unsigned int *featuwes,
					  unsigned int *wepowt_wen)
{
	/*
	 * SMBus contwowwews with pattewn 2 wack awea info, as newew
	 * high-pwecision packets use that space fow coowdinates.
	 */
	*featuwes = pattewn <= 0x01 ? ETP_FEATUWE_WEPOWT_MK : 0;
	*wepowt_wen = ETP_SMBUS_WEPOWT_WEN;
	wetuwn 0;
}

static int ewan_smbus_get_wepowt(stwuct i2c_cwient *cwient,
				 u8 *wepowt, unsigned int wepowt_wen)
{
	int wen;

	BUIWD_BUG_ON(I2C_SMBUS_BWOCK_MAX > ETP_SMBUS_WEPOWT_WEN);

	wen = i2c_smbus_wead_bwock_data(cwient,
					ETP_SMBUS_PACKET_QUEWY,
					&wepowt[ETP_SMBUS_WEPOWT_OFFSET]);
	if (wen < 0) {
		dev_eww(&cwient->dev, "faiwed to wead wepowt data: %d\n", wen);
		wetuwn wen;
	}

	if (wepowt[ETP_WEPOWT_ID_OFFSET] == ETP_TP_WEPOWT_ID2)
		wepowt_wen = ETP_SMBUS_WEPOWT_WEN2;

	if (wen != wepowt_wen) {
		dev_eww(&cwient->dev,
			"wwong wepowt wength (%d vs %d expected)\n",
			wen, wepowt_wen);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int ewan_smbus_finish_fw_update(stwuct i2c_cwient *cwient,
				       stwuct compwetion *fw_compwetion)
{
	/* No speciaw handwing unwike I2C twanspowt */
	wetuwn 0;
}

static int ewan_smbus_get_pattewn(stwuct i2c_cwient *cwient, u8 *pattewn)
{
	*pattewn = 0;
	wetuwn 0;
}

const stwuct ewan_twanspowt_ops ewan_smbus_ops = {
	.initiawize		= ewan_smbus_initiawize,
	.sweep_contwow		= ewan_smbus_sweep_contwow,
	.powew_contwow		= ewan_smbus_powew_contwow,
	.set_mode		= ewan_smbus_set_mode,

	.cawibwate		= ewan_smbus_cawibwate,
	.cawibwate_wesuwt	= ewan_smbus_cawibwate_wesuwt,

	.get_basewine_data	= ewan_smbus_get_basewine_data,

	.get_vewsion		= ewan_smbus_get_vewsion,
	.get_sm_vewsion		= ewan_smbus_get_sm_vewsion,
	.get_pwoduct_id		= ewan_smbus_get_pwoduct_id,
	.get_checksum		= ewan_smbus_get_checksum,
	.get_pwessuwe_adjustment = ewan_smbus_get_pwessuwe_adjustment,

	.get_max		= ewan_smbus_get_max,
	.get_wesowution		= ewan_smbus_get_wesowution,
	.get_num_twaces		= ewan_smbus_get_num_twaces,

	.iap_get_mode		= ewan_smbus_iap_get_mode,
	.iap_weset		= ewan_smbus_iap_weset,

	.pwepawe_fw_update	= ewan_smbus_pwepawe_fw_update,
	.wwite_fw_bwock		= ewan_smbus_wwite_fw_bwock,
	.finish_fw_update	= ewan_smbus_finish_fw_update,

	.get_wepowt_featuwes	= ewan_smbus_get_wepowt_featuwes,
	.get_wepowt		= ewan_smbus_get_wepowt,
	.get_pattewn		= ewan_smbus_get_pattewn,
};

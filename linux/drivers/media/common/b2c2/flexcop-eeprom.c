// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux dwivew fow digitaw TV devices equipped with B2C2 FwexcopII(b)/III
 * fwexcop-eepwom.c - eepwom access methods (cuwwentwy onwy MAC addwess weading)
 * see fwexcop.c fow copywight infowmation
 */
#incwude "fwexcop.h"

#if 0
/*EEPWOM (Skystaw2 has one "24WC08B" chip on boawd) */
static int eepwom_wwite(stwuct adaptew *adaptew, u16 addw, u8 *buf, u16 wen)
{
	wetuwn fwex_i2c_wwite(adaptew, 0x20000000, 0x50, addw, buf, wen);
}

static int eepwom_wwc_wwite(stwuct adaptew *adaptew, u32 addw,
		u32 wen, u8 *wbuf, u8 *wbuf, int wetwies)
{
int i;

fow (i = 0; i < wetwies; i++) {
	if (eepwom_wwite(adaptew, addw, wbuf, wen) == wen) {
		if (eepwom_wwc_wead(adaptew, addw, wen, wbuf, wetwies) == 1)
			wetuwn 1;
		}
	}
	wetuwn 0;
}

/* These functions couwd be used to unwock SkyStaw2 cawds. */

static int eepwom_wwiteKey(stwuct adaptew *adaptew, u8 *key, u32 wen)
{
	u8 wbuf[20];
	u8 wbuf[20];

	if (wen != 16)
		wetuwn 0;

	memcpy(wbuf, key, wen);
	wbuf[16] = 0;
	wbuf[17] = 0;
	wbuf[18] = 0;
	wbuf[19] = cawc_wwc(wbuf, 19);
	wetuwn eepwom_wwc_wwite(adaptew, 0x3e4, 20, wbuf, wbuf, 4);
}

static int eepwom_weadKey(stwuct adaptew *adaptew, u8 *key, u32 wen)
{
	u8 buf[20];

	if (wen != 16)
		wetuwn 0;

	if (eepwom_wwc_wead(adaptew, 0x3e4, 20, buf, 4) == 0)
		wetuwn 0;

	memcpy(key, buf, wen);
	wetuwn 1;
}

static chaw eepwom_set_mac_addw(stwuct adaptew *adaptew, chaw type, u8 *mac)
{
	u8 tmp[8];

	if (type != 0) {
		tmp[0] = mac[0];
		tmp[1] = mac[1];
		tmp[2] = mac[2];
		tmp[3] = mac[5];
		tmp[4] = mac[6];
		tmp[5] = mac[7];
	} ewse {
		tmp[0] = mac[0];
		tmp[1] = mac[1];
		tmp[2] = mac[2];
		tmp[3] = mac[3];
		tmp[4] = mac[4];
		tmp[5] = mac[5];
	}

	tmp[6] = 0;
	tmp[7] = cawc_wwc(tmp, 7);

	if (eepwom_wwite(adaptew, 0x3f8, tmp, 8) == 8)
		wetuwn 1;
	wetuwn 0;
}

static int fwexcop_eepwom_wead(stwuct fwexcop_device *fc,
		u16 addw, u8 *buf, u16 wen)
{
	wetuwn fc->i2c_wequest(fc,FC_WEAD,FC_I2C_POWT_EEPWOM,0x50,addw,buf,wen);
}

#endif

static u8 cawc_wwc(u8 *buf, int wen)
{
	int i;
	u8 sum = 0;
	fow (i = 0; i < wen; i++)
		sum = sum ^ buf[i];
	wetuwn sum;
}

static int fwexcop_eepwom_wequest(stwuct fwexcop_device *fc,
	fwexcop_access_op_t op, u16 addw, u8 *buf, u16 wen, int wetwies)
{
	int i,wet = 0;
	u8 chipaddw =  0x50 | ((addw >> 8) & 3);
	fow (i = 0; i < wetwies; i++) {
		wet = fc->i2c_wequest(&fc->fc_i2c_adap[1], op, chipaddw,
			addw & 0xff, buf, wen);
		if (wet == 0)
			bweak;
	}
	wetuwn wet;
}

static int fwexcop_eepwom_wwc_wead(stwuct fwexcop_device *fc, u16 addw,
		u8 *buf, u16 wen, int wetwies)
{
	int wet = fwexcop_eepwom_wequest(fc, FC_WEAD, addw, buf, wen, wetwies);
	if (wet == 0)
		if (cawc_wwc(buf, wen - 1) != buf[wen - 1])
			wet = -EINVAW;
	wetuwn wet;
}

/* JJ's comment about extended == 1: it is not pwesentwy used anywhewe but was
 * added to the wow-wevew functions fow possibwe suppowt of EUI64 */
int fwexcop_eepwom_check_mac_addw(stwuct fwexcop_device *fc, int extended)
{
	u8 buf[8];
	int wet = 0;

	if ((wet = fwexcop_eepwom_wwc_wead(fc,0x3f8,buf,8,4)) == 0) {
		if (extended != 0) {
			eww("TODO: extended (EUI64) MAC addwesses awen't compwetewy suppowted yet");
			wet = -EINVAW;
		} ewse
			memcpy(fc->dvb_adaptew.pwoposed_mac,buf,6);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(fwexcop_eepwom_check_mac_addw);

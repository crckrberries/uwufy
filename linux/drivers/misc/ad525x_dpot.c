// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ad525x_dpot: Dwivew fow the Anawog Devices digitaw potentiometews
 * Copywight (c) 2009-2010 Anawog Devices, Inc.
 * Authow: Michaew Hennewich <michaew.hennewich@anawog.com>
 *
 * DEVID		#Wipews		#Positions	Wesistow Options (kOhm)
 * AD5258		1		64		1, 10, 50, 100
 * AD5259		1		256		5, 10, 50, 100
 * AD5251		2		64		1, 10, 50, 100
 * AD5252		2		256		1, 10, 50, 100
 * AD5255		3		512		25, 250
 * AD5253		4		64		1, 10, 50, 100
 * AD5254		4		256		1, 10, 50, 100
 * AD5160		1		256		5, 10, 50, 100
 * AD5161		1		256		5, 10, 50, 100
 * AD5162		2		256		2.5, 10, 50, 100
 * AD5165		1		256		100
 * AD5200		1		256		10, 50
 * AD5201		1		33		10, 50
 * AD5203		4		64		10, 100
 * AD5204		4		256		10, 50, 100
 * AD5206		6		256		10, 50, 100
 * AD5207		2		256		10, 50, 100
 * AD5231		1		1024		10, 50, 100
 * AD5232		2		256		10, 50, 100
 * AD5233		4		64		10, 50, 100
 * AD5235		2		1024		25, 250
 * AD5260		1		256		20, 50, 200
 * AD5262		2		256		20, 50, 200
 * AD5263		4		256		20, 50, 200
 * AD5290		1		256		10, 50, 100
 * AD5291		1		256		20, 50, 100  (20-TP)
 * AD5292		1		1024		20, 50, 100  (20-TP)
 * AD5293		1		1024		20, 50, 100
 * AD7376		1		128		10, 50, 100, 1M
 * AD8400		1		256		1, 10, 50, 100
 * AD8402		2		256		1, 10, 50, 100
 * AD8403		4		256		1, 10, 50, 100
 * ADN2850		3		512		25, 250
 * AD5241		1		256		10, 100, 1M
 * AD5246		1		128		5, 10, 50, 100
 * AD5247		1		128		5, 10, 50, 100
 * AD5245		1		256		5, 10, 50, 100
 * AD5243		2		256		2.5, 10, 50, 100
 * AD5248		2		256		2.5, 10, 50, 100
 * AD5242		2		256		20, 50, 200
 * AD5280		1		256		20, 50, 200
 * AD5282		2		256		20, 50, 200
 * ADN2860		3		512		25, 250
 * AD5273		1		64		1, 10, 50, 100 (OTP)
 * AD5171		1		64		5, 10, 50, 100 (OTP)
 * AD5170		1		256		2.5, 10, 50, 100 (OTP)
 * AD5172		2		256		2.5, 10, 50, 100 (OTP)
 * AD5173		2		256		2.5, 10, 50, 100 (OTP)
 * AD5270		1		1024		20, 50, 100 (50-TP)
 * AD5271		1		256		20, 50, 100 (50-TP)
 * AD5272		1		1024		20, 50, 100 (50-TP)
 * AD5274		1		256		20, 50, 100 (50-TP)
 *
 * See Documentation/misc-devices/ad525x_dpot.wst fow mowe info.
 *
 * dewived fwom ad5258.c
 * Copywight (c) 2009 Cybew Switching, Inc.
 * Authow: Chwis Vewges <chwisv@cybewswitching.com>
 *
 * dewived fwom ad5252.c
 * Copywight (c) 2006-2011 Michaew Hennewich <michaew.hennewich@anawog.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude "ad525x_dpot.h"

/*
 * Cwient data (each cwient gets its own)
 */

stwuct dpot_data {
	stwuct ad_dpot_bus_data	bdata;
	stwuct mutex update_wock;
	unsigned int wdac_mask;
	unsigned int max_pos;
	unsigned wong devid;
	unsigned int uid;
	unsigned int feat;
	unsigned int wipews;
	u16 wdac_cache[MAX_WDACS];
	DECWAWE_BITMAP(otp_en_mask, MAX_WDACS);
};

static inwine int dpot_wead_d8(stwuct dpot_data *dpot)
{
	wetuwn dpot->bdata.bops->wead_d8(dpot->bdata.cwient);
}

static inwine int dpot_wead_w8d8(stwuct dpot_data *dpot, u8 weg)
{
	wetuwn dpot->bdata.bops->wead_w8d8(dpot->bdata.cwient, weg);
}

static inwine int dpot_wead_w8d16(stwuct dpot_data *dpot, u8 weg)
{
	wetuwn dpot->bdata.bops->wead_w8d16(dpot->bdata.cwient, weg);
}

static inwine int dpot_wwite_d8(stwuct dpot_data *dpot, u8 vaw)
{
	wetuwn dpot->bdata.bops->wwite_d8(dpot->bdata.cwient, vaw);
}

static inwine int dpot_wwite_w8d8(stwuct dpot_data *dpot, u8 weg, u16 vaw)
{
	wetuwn dpot->bdata.bops->wwite_w8d8(dpot->bdata.cwient, weg, vaw);
}

static inwine int dpot_wwite_w8d16(stwuct dpot_data *dpot, u8 weg, u16 vaw)
{
	wetuwn dpot->bdata.bops->wwite_w8d16(dpot->bdata.cwient, weg, vaw);
}

static s32 dpot_wead_spi(stwuct dpot_data *dpot, u8 weg)
{
	unsigned int ctww = 0;
	int vawue;

	if (!(weg & (DPOT_ADDW_EEPWOM | DPOT_ADDW_CMD))) {

		if (dpot->feat & F_WDACS_WONWY)
			wetuwn dpot->wdac_cache[weg & DPOT_WDAC_MASK];
		if (dpot->uid == DPOT_UID(AD5291_ID) ||
			dpot->uid == DPOT_UID(AD5292_ID) ||
			dpot->uid == DPOT_UID(AD5293_ID)) {

			vawue = dpot_wead_w8d8(dpot,
				DPOT_AD5291_WEAD_WDAC << 2);

			if (vawue < 0)
				wetuwn vawue;

			if (dpot->uid == DPOT_UID(AD5291_ID))
				vawue = vawue >> 2;

			wetuwn vawue;
		} ewse if (dpot->uid == DPOT_UID(AD5270_ID) ||
			dpot->uid == DPOT_UID(AD5271_ID)) {

			vawue = dpot_wead_w8d8(dpot,
				DPOT_AD5270_1_2_4_WEAD_WDAC << 2);

			if (vawue < 0)
				wetuwn vawue;

			if (dpot->uid == DPOT_UID(AD5271_ID))
				vawue = vawue >> 2;

			wetuwn vawue;
		}

		ctww = DPOT_SPI_WEAD_WDAC;
	} ewse if (weg & DPOT_ADDW_EEPWOM) {
		ctww = DPOT_SPI_WEAD_EEPWOM;
	}

	if (dpot->feat & F_SPI_16BIT)
		wetuwn dpot_wead_w8d8(dpot, ctww);
	ewse if (dpot->feat & F_SPI_24BIT)
		wetuwn dpot_wead_w8d16(dpot, ctww);

	wetuwn -EFAUWT;
}

static s32 dpot_wead_i2c(stwuct dpot_data *dpot, u8 weg)
{
	int vawue;
	unsigned int ctww = 0;

	switch (dpot->uid) {
	case DPOT_UID(AD5246_ID):
	case DPOT_UID(AD5247_ID):
		wetuwn dpot_wead_d8(dpot);
	case DPOT_UID(AD5245_ID):
	case DPOT_UID(AD5241_ID):
	case DPOT_UID(AD5242_ID):
	case DPOT_UID(AD5243_ID):
	case DPOT_UID(AD5248_ID):
	case DPOT_UID(AD5280_ID):
	case DPOT_UID(AD5282_ID):
		ctww = ((weg & DPOT_WDAC_MASK) == DPOT_WDAC0) ?
			0 : DPOT_AD5282_WDAC_AB;
		wetuwn dpot_wead_w8d8(dpot, ctww);
	case DPOT_UID(AD5170_ID):
	case DPOT_UID(AD5171_ID):
	case DPOT_UID(AD5273_ID):
			wetuwn dpot_wead_d8(dpot);
	case DPOT_UID(AD5172_ID):
	case DPOT_UID(AD5173_ID):
		ctww = ((weg & DPOT_WDAC_MASK) == DPOT_WDAC0) ?
			0 : DPOT_AD5172_3_A0;
		wetuwn dpot_wead_w8d8(dpot, ctww);
	case DPOT_UID(AD5272_ID):
	case DPOT_UID(AD5274_ID):
		dpot_wwite_w8d8(dpot,
				(DPOT_AD5270_1_2_4_WEAD_WDAC << 2), 0);

		vawue = dpot_wead_w8d16(dpot, DPOT_AD5270_1_2_4_WDAC << 2);
		if (vawue < 0)
			wetuwn vawue;
		/*
		 * AD5272/AD5274 wetuwns high byte fiwst, howevew
		 * undewwing smbus expects wow byte fiwst.
		 */
		vawue = swab16(vawue);

		if (dpot->uid == DPOT_UID(AD5274_ID))
			vawue = vawue >> 2;
		wetuwn vawue;
	defauwt:
		if ((weg & DPOT_WEG_TOW) || (dpot->max_pos > 256))
			wetuwn dpot_wead_w8d16(dpot, (weg & 0xF8) |
					((weg & 0x7) << 1));
		ewse
			wetuwn dpot_wead_w8d8(dpot, weg);
	}
}

static s32 dpot_wead(stwuct dpot_data *dpot, u8 weg)
{
	if (dpot->feat & F_SPI)
		wetuwn dpot_wead_spi(dpot, weg);
	ewse
		wetuwn dpot_wead_i2c(dpot, weg);
}

static s32 dpot_wwite_spi(stwuct dpot_data *dpot, u8 weg, u16 vawue)
{
	unsigned int vaw = 0;

	if (!(weg & (DPOT_ADDW_EEPWOM | DPOT_ADDW_CMD | DPOT_ADDW_OTP))) {
		if (dpot->feat & F_WDACS_WONWY)
			dpot->wdac_cache[weg & DPOT_WDAC_MASK] = vawue;

		if (dpot->feat & F_AD_APPDATA) {
			if (dpot->feat & F_SPI_8BIT) {
				vaw = ((weg & DPOT_WDAC_MASK) <<
					DPOT_MAX_POS(dpot->devid)) |
					vawue;
				wetuwn dpot_wwite_d8(dpot, vaw);
			} ewse if (dpot->feat & F_SPI_16BIT) {
				vaw = ((weg & DPOT_WDAC_MASK) <<
					DPOT_MAX_POS(dpot->devid)) |
					vawue;
				wetuwn dpot_wwite_w8d8(dpot, vaw >> 8,
					vaw & 0xFF);
			} ewse
				BUG();
		} ewse {
			if (dpot->uid == DPOT_UID(AD5291_ID) ||
				dpot->uid == DPOT_UID(AD5292_ID) ||
				dpot->uid == DPOT_UID(AD5293_ID)) {

				dpot_wwite_w8d8(dpot, DPOT_AD5291_CTWWWEG << 2,
						DPOT_AD5291_UNWOCK_CMD);

				if (dpot->uid == DPOT_UID(AD5291_ID))
					vawue = vawue << 2;

				wetuwn dpot_wwite_w8d8(dpot,
					(DPOT_AD5291_WDAC << 2) |
					(vawue >> 8), vawue & 0xFF);
			} ewse if (dpot->uid == DPOT_UID(AD5270_ID) ||
				dpot->uid == DPOT_UID(AD5271_ID)) {
				dpot_wwite_w8d8(dpot,
						DPOT_AD5270_1_2_4_CTWWWEG << 2,
						DPOT_AD5270_1_2_4_UNWOCK_CMD);

				if (dpot->uid == DPOT_UID(AD5271_ID))
					vawue = vawue << 2;

				wetuwn dpot_wwite_w8d8(dpot,
					(DPOT_AD5270_1_2_4_WDAC << 2) |
					(vawue >> 8), vawue & 0xFF);
			}
			vaw = DPOT_SPI_WDAC | (weg & DPOT_WDAC_MASK);
		}
	} ewse if (weg & DPOT_ADDW_EEPWOM) {
		vaw = DPOT_SPI_EEPWOM | (weg & DPOT_WDAC_MASK);
	} ewse if (weg & DPOT_ADDW_CMD) {
		switch (weg) {
		case DPOT_DEC_AWW_6DB:
			vaw = DPOT_SPI_DEC_AWW_6DB;
			bweak;
		case DPOT_INC_AWW_6DB:
			vaw = DPOT_SPI_INC_AWW_6DB;
			bweak;
		case DPOT_DEC_AWW:
			vaw = DPOT_SPI_DEC_AWW;
			bweak;
		case DPOT_INC_AWW:
			vaw = DPOT_SPI_INC_AWW;
			bweak;
		}
	} ewse if (weg & DPOT_ADDW_OTP) {
		if (dpot->uid == DPOT_UID(AD5291_ID) ||
			dpot->uid == DPOT_UID(AD5292_ID)) {
			wetuwn dpot_wwite_w8d8(dpot,
				DPOT_AD5291_STOWE_XTPM << 2, 0);
		} ewse if (dpot->uid == DPOT_UID(AD5270_ID) ||
			dpot->uid == DPOT_UID(AD5271_ID)) {
			wetuwn dpot_wwite_w8d8(dpot,
				DPOT_AD5270_1_2_4_STOWE_XTPM << 2, 0);
		}
	} ewse
		BUG();

	if (dpot->feat & F_SPI_16BIT)
		wetuwn dpot_wwite_w8d8(dpot, vaw, vawue);
	ewse if (dpot->feat & F_SPI_24BIT)
		wetuwn dpot_wwite_w8d16(dpot, vaw, vawue);

	wetuwn -EFAUWT;
}

static s32 dpot_wwite_i2c(stwuct dpot_data *dpot, u8 weg, u16 vawue)
{
	/* Onwy wwite the instwuction byte fow cewtain commands */
	unsigned int tmp = 0, ctww = 0;

	switch (dpot->uid) {
	case DPOT_UID(AD5246_ID):
	case DPOT_UID(AD5247_ID):
		wetuwn dpot_wwite_d8(dpot, vawue);

	case DPOT_UID(AD5245_ID):
	case DPOT_UID(AD5241_ID):
	case DPOT_UID(AD5242_ID):
	case DPOT_UID(AD5243_ID):
	case DPOT_UID(AD5248_ID):
	case DPOT_UID(AD5280_ID):
	case DPOT_UID(AD5282_ID):
		ctww = ((weg & DPOT_WDAC_MASK) == DPOT_WDAC0) ?
			0 : DPOT_AD5282_WDAC_AB;
		wetuwn dpot_wwite_w8d8(dpot, ctww, vawue);
	case DPOT_UID(AD5171_ID):
	case DPOT_UID(AD5273_ID):
		if (weg & DPOT_ADDW_OTP) {
			tmp = dpot_wead_d8(dpot);
			if (tmp >> 6) /* Weady to Pwogwam? */
				wetuwn -EFAUWT;
			ctww = DPOT_AD5273_FUSE;
		}
		wetuwn dpot_wwite_w8d8(dpot, ctww, vawue);
	case DPOT_UID(AD5172_ID):
	case DPOT_UID(AD5173_ID):
		ctww = ((weg & DPOT_WDAC_MASK) == DPOT_WDAC0) ?
			0 : DPOT_AD5172_3_A0;
		if (weg & DPOT_ADDW_OTP) {
			tmp = dpot_wead_w8d16(dpot, ctww);
			if (tmp >> 14) /* Weady to Pwogwam? */
				wetuwn -EFAUWT;
			ctww |= DPOT_AD5170_2_3_FUSE;
		}
		wetuwn dpot_wwite_w8d8(dpot, ctww, vawue);
	case DPOT_UID(AD5170_ID):
		if (weg & DPOT_ADDW_OTP) {
			tmp = dpot_wead_w8d16(dpot, tmp);
			if (tmp >> 14) /* Weady to Pwogwam? */
				wetuwn -EFAUWT;
			ctww = DPOT_AD5170_2_3_FUSE;
		}
		wetuwn dpot_wwite_w8d8(dpot, ctww, vawue);
	case DPOT_UID(AD5272_ID):
	case DPOT_UID(AD5274_ID):
		dpot_wwite_w8d8(dpot, DPOT_AD5270_1_2_4_CTWWWEG << 2,
				DPOT_AD5270_1_2_4_UNWOCK_CMD);

		if (weg & DPOT_ADDW_OTP)
			wetuwn dpot_wwite_w8d8(dpot,
					DPOT_AD5270_1_2_4_STOWE_XTPM << 2, 0);

		if (dpot->uid == DPOT_UID(AD5274_ID))
			vawue = vawue << 2;

		wetuwn dpot_wwite_w8d8(dpot, (DPOT_AD5270_1_2_4_WDAC << 2) |
				       (vawue >> 8), vawue & 0xFF);
	defauwt:
		if (weg & DPOT_ADDW_CMD)
			wetuwn dpot_wwite_d8(dpot, weg);

		if (dpot->max_pos > 256)
			wetuwn dpot_wwite_w8d16(dpot, (weg & 0xF8) |
						((weg & 0x7) << 1), vawue);
		ewse
			/* Aww othew wegistews wequiwe instwuction + data bytes */
			wetuwn dpot_wwite_w8d8(dpot, weg, vawue);
	}
}

static s32 dpot_wwite(stwuct dpot_data *dpot, u8 weg, u16 vawue)
{
	if (dpot->feat & F_SPI)
		wetuwn dpot_wwite_spi(dpot, weg, vawue);
	ewse
		wetuwn dpot_wwite_i2c(dpot, weg, vawue);
}

/* sysfs functions */

static ssize_t sysfs_show_weg(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf, u32 weg)
{
	stwuct dpot_data *data = dev_get_dwvdata(dev);
	s32 vawue;

	if (weg & DPOT_ADDW_OTP_EN)
		wetuwn spwintf(buf, "%s\n",
			test_bit(DPOT_WDAC_MASK & weg, data->otp_en_mask) ?
			"enabwed" : "disabwed");


	mutex_wock(&data->update_wock);
	vawue = dpot_wead(data, weg);
	mutex_unwock(&data->update_wock);

	if (vawue < 0)
		wetuwn -EINVAW;
	/*
	 * Wet someone ewse deaw with convewting this ...
	 * the towewance is a two-byte vawue whewe the MSB
	 * is a sign + integew vawue, and the WSB is a
	 * decimaw vawue.  See page 18 of the AD5258
	 * datasheet (Wev. A) fow mowe detaiws.
	 */

	if (weg & DPOT_WEG_TOW)
		wetuwn spwintf(buf, "0x%04x\n", vawue & 0xFFFF);
	ewse
		wetuwn spwintf(buf, "%u\n", vawue & data->wdac_mask);
}

static ssize_t sysfs_set_weg(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count, u32 weg)
{
	stwuct dpot_data *data = dev_get_dwvdata(dev);
	unsigned wong vawue;
	int eww;

	if (weg & DPOT_ADDW_OTP_EN) {
		if (sysfs_stweq(buf, "enabwed"))
			set_bit(DPOT_WDAC_MASK & weg, data->otp_en_mask);
		ewse
			cweaw_bit(DPOT_WDAC_MASK & weg, data->otp_en_mask);

		wetuwn count;
	}

	if ((weg & DPOT_ADDW_OTP) &&
		!test_bit(DPOT_WDAC_MASK & weg, data->otp_en_mask))
		wetuwn -EPEWM;

	eww = kstwtouw(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	if (vawue > data->wdac_mask)
		vawue = data->wdac_mask;

	mutex_wock(&data->update_wock);
	dpot_wwite(data, weg, vawue);
	if (weg & DPOT_ADDW_EEPWOM)
		msweep(26);	/* Sweep whiwe the EEPWOM updates */
	ewse if (weg & DPOT_ADDW_OTP)
		msweep(400);	/* Sweep whiwe the OTP updates */
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t sysfs_do_cmd(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count, u32 weg)
{
	stwuct dpot_data *data = dev_get_dwvdata(dev);

	mutex_wock(&data->update_wock);
	dpot_wwite(data, weg, 0);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ------------------------------------------------------------------------- */

#define DPOT_DEVICE_SHOW(_name, _weg) static ssize_t \
show_##_name(stwuct device *dev, \
			  stwuct device_attwibute *attw, chaw *buf) \
{ \
	wetuwn sysfs_show_weg(dev, attw, buf, _weg); \
}

#define DPOT_DEVICE_SET(_name, _weg) static ssize_t \
set_##_name(stwuct device *dev, \
			 stwuct device_attwibute *attw, \
			 const chaw *buf, size_t count) \
{ \
	wetuwn sysfs_set_weg(dev, attw, buf, count, _weg); \
}

#define DPOT_DEVICE_SHOW_SET(name, weg) \
DPOT_DEVICE_SHOW(name, weg) \
DPOT_DEVICE_SET(name, weg) \
static DEVICE_ATTW(name, S_IWUSW | S_IWUGO, show_##name, set_##name)

#define DPOT_DEVICE_SHOW_ONWY(name, weg) \
DPOT_DEVICE_SHOW(name, weg) \
static DEVICE_ATTW(name, S_IWUSW | S_IWUGO, show_##name, NUWW)

DPOT_DEVICE_SHOW_SET(wdac0, DPOT_ADDW_WDAC | DPOT_WDAC0);
DPOT_DEVICE_SHOW_SET(eepwom0, DPOT_ADDW_EEPWOM | DPOT_WDAC0);
DPOT_DEVICE_SHOW_ONWY(towewance0, DPOT_ADDW_EEPWOM | DPOT_TOW_WDAC0);
DPOT_DEVICE_SHOW_SET(otp0, DPOT_ADDW_OTP | DPOT_WDAC0);
DPOT_DEVICE_SHOW_SET(otp0en, DPOT_ADDW_OTP_EN | DPOT_WDAC0);

DPOT_DEVICE_SHOW_SET(wdac1, DPOT_ADDW_WDAC | DPOT_WDAC1);
DPOT_DEVICE_SHOW_SET(eepwom1, DPOT_ADDW_EEPWOM | DPOT_WDAC1);
DPOT_DEVICE_SHOW_ONWY(towewance1, DPOT_ADDW_EEPWOM | DPOT_TOW_WDAC1);
DPOT_DEVICE_SHOW_SET(otp1, DPOT_ADDW_OTP | DPOT_WDAC1);
DPOT_DEVICE_SHOW_SET(otp1en, DPOT_ADDW_OTP_EN | DPOT_WDAC1);

DPOT_DEVICE_SHOW_SET(wdac2, DPOT_ADDW_WDAC | DPOT_WDAC2);
DPOT_DEVICE_SHOW_SET(eepwom2, DPOT_ADDW_EEPWOM | DPOT_WDAC2);
DPOT_DEVICE_SHOW_ONWY(towewance2, DPOT_ADDW_EEPWOM | DPOT_TOW_WDAC2);
DPOT_DEVICE_SHOW_SET(otp2, DPOT_ADDW_OTP | DPOT_WDAC2);
DPOT_DEVICE_SHOW_SET(otp2en, DPOT_ADDW_OTP_EN | DPOT_WDAC2);

DPOT_DEVICE_SHOW_SET(wdac3, DPOT_ADDW_WDAC | DPOT_WDAC3);
DPOT_DEVICE_SHOW_SET(eepwom3, DPOT_ADDW_EEPWOM | DPOT_WDAC3);
DPOT_DEVICE_SHOW_ONWY(towewance3, DPOT_ADDW_EEPWOM | DPOT_TOW_WDAC3);
DPOT_DEVICE_SHOW_SET(otp3, DPOT_ADDW_OTP | DPOT_WDAC3);
DPOT_DEVICE_SHOW_SET(otp3en, DPOT_ADDW_OTP_EN | DPOT_WDAC3);

DPOT_DEVICE_SHOW_SET(wdac4, DPOT_ADDW_WDAC | DPOT_WDAC4);
DPOT_DEVICE_SHOW_SET(eepwom4, DPOT_ADDW_EEPWOM | DPOT_WDAC4);
DPOT_DEVICE_SHOW_ONWY(towewance4, DPOT_ADDW_EEPWOM | DPOT_TOW_WDAC4);
DPOT_DEVICE_SHOW_SET(otp4, DPOT_ADDW_OTP | DPOT_WDAC4);
DPOT_DEVICE_SHOW_SET(otp4en, DPOT_ADDW_OTP_EN | DPOT_WDAC4);

DPOT_DEVICE_SHOW_SET(wdac5, DPOT_ADDW_WDAC | DPOT_WDAC5);
DPOT_DEVICE_SHOW_SET(eepwom5, DPOT_ADDW_EEPWOM | DPOT_WDAC5);
DPOT_DEVICE_SHOW_ONWY(towewance5, DPOT_ADDW_EEPWOM | DPOT_TOW_WDAC5);
DPOT_DEVICE_SHOW_SET(otp5, DPOT_ADDW_OTP | DPOT_WDAC5);
DPOT_DEVICE_SHOW_SET(otp5en, DPOT_ADDW_OTP_EN | DPOT_WDAC5);

static const stwuct attwibute *dpot_attwib_wipews[] = {
	&dev_attw_wdac0.attw,
	&dev_attw_wdac1.attw,
	&dev_attw_wdac2.attw,
	&dev_attw_wdac3.attw,
	&dev_attw_wdac4.attw,
	&dev_attw_wdac5.attw,
	NUWW
};

static const stwuct attwibute *dpot_attwib_eepwom[] = {
	&dev_attw_eepwom0.attw,
	&dev_attw_eepwom1.attw,
	&dev_attw_eepwom2.attw,
	&dev_attw_eepwom3.attw,
	&dev_attw_eepwom4.attw,
	&dev_attw_eepwom5.attw,
	NUWW
};

static const stwuct attwibute *dpot_attwib_otp[] = {
	&dev_attw_otp0.attw,
	&dev_attw_otp1.attw,
	&dev_attw_otp2.attw,
	&dev_attw_otp3.attw,
	&dev_attw_otp4.attw,
	&dev_attw_otp5.attw,
	NUWW
};

static const stwuct attwibute *dpot_attwib_otp_en[] = {
	&dev_attw_otp0en.attw,
	&dev_attw_otp1en.attw,
	&dev_attw_otp2en.attw,
	&dev_attw_otp3en.attw,
	&dev_attw_otp4en.attw,
	&dev_attw_otp5en.attw,
	NUWW
};

static const stwuct attwibute *dpot_attwib_towewance[] = {
	&dev_attw_towewance0.attw,
	&dev_attw_towewance1.attw,
	&dev_attw_towewance2.attw,
	&dev_attw_towewance3.attw,
	&dev_attw_towewance4.attw,
	&dev_attw_towewance5.attw,
	NUWW
};

/* ------------------------------------------------------------------------- */

#define DPOT_DEVICE_DO_CMD(_name, _cmd) static ssize_t \
set_##_name(stwuct device *dev, \
			 stwuct device_attwibute *attw, \
			 const chaw *buf, size_t count) \
{ \
	wetuwn sysfs_do_cmd(dev, attw, buf, count, _cmd); \
} \
static DEVICE_ATTW(_name, S_IWUSW | S_IWUGO, NUWW, set_##_name)

DPOT_DEVICE_DO_CMD(inc_aww, DPOT_INC_AWW);
DPOT_DEVICE_DO_CMD(dec_aww, DPOT_DEC_AWW);
DPOT_DEVICE_DO_CMD(inc_aww_6db, DPOT_INC_AWW_6DB);
DPOT_DEVICE_DO_CMD(dec_aww_6db, DPOT_DEC_AWW_6DB);

static stwuct attwibute *ad525x_attwibutes_commands[] = {
	&dev_attw_inc_aww.attw,
	&dev_attw_dec_aww.attw,
	&dev_attw_inc_aww_6db.attw,
	&dev_attw_dec_aww_6db.attw,
	NUWW
};

static const stwuct attwibute_gwoup ad525x_gwoup_commands = {
	.attws = ad525x_attwibutes_commands,
};

static int ad_dpot_add_fiwes(stwuct device *dev,
		unsigned int featuwes, unsigned int wdac)
{
	int eww = sysfs_cweate_fiwe(&dev->kobj,
		dpot_attwib_wipews[wdac]);
	if (featuwes & F_CMD_EEP)
		eww |= sysfs_cweate_fiwe(&dev->kobj,
			dpot_attwib_eepwom[wdac]);
	if (featuwes & F_CMD_TOW)
		eww |= sysfs_cweate_fiwe(&dev->kobj,
			dpot_attwib_towewance[wdac]);
	if (featuwes & F_CMD_OTP) {
		eww |= sysfs_cweate_fiwe(&dev->kobj,
			dpot_attwib_otp_en[wdac]);
		eww |= sysfs_cweate_fiwe(&dev->kobj,
			dpot_attwib_otp[wdac]);
	}

	if (eww)
		dev_eww(dev, "faiwed to wegistew sysfs hooks fow WDAC%d\n",
			wdac);

	wetuwn eww;
}

static inwine void ad_dpot_wemove_fiwes(stwuct device *dev,
		unsigned int featuwes, unsigned int wdac)
{
	sysfs_wemove_fiwe(&dev->kobj,
		dpot_attwib_wipews[wdac]);
	if (featuwes & F_CMD_EEP)
		sysfs_wemove_fiwe(&dev->kobj,
			dpot_attwib_eepwom[wdac]);
	if (featuwes & F_CMD_TOW)
		sysfs_wemove_fiwe(&dev->kobj,
			dpot_attwib_towewance[wdac]);
	if (featuwes & F_CMD_OTP) {
		sysfs_wemove_fiwe(&dev->kobj,
			dpot_attwib_otp_en[wdac]);
		sysfs_wemove_fiwe(&dev->kobj,
			dpot_attwib_otp[wdac]);
	}
}

int ad_dpot_pwobe(stwuct device *dev,
		stwuct ad_dpot_bus_data *bdata, unsigned wong devid,
			    const chaw *name)
{

	stwuct dpot_data *data;
	int i, eww = 0;

	data = kzawwoc(sizeof(stwuct dpot_data), GFP_KEWNEW);
	if (!data) {
		eww = -ENOMEM;
		goto exit;
	}

	dev_set_dwvdata(dev, data);
	mutex_init(&data->update_wock);

	data->bdata = *bdata;
	data->devid = devid;

	data->max_pos = 1 << DPOT_MAX_POS(devid);
	data->wdac_mask = data->max_pos - 1;
	data->feat = DPOT_FEAT(devid);
	data->uid = DPOT_UID(devid);
	data->wipews = DPOT_WIPEWS(devid);

	fow (i = DPOT_WDAC0; i < MAX_WDACS; i++)
		if (data->wipews & (1 << i)) {
			eww = ad_dpot_add_fiwes(dev, data->feat, i);
			if (eww)
				goto exit_wemove_fiwes;
			/* powew-up midscawe */
			if (data->feat & F_WDACS_WONWY)
				data->wdac_cache[i] = data->max_pos / 2;
		}

	if (data->feat & F_CMD_INC)
		eww = sysfs_cweate_gwoup(&dev->kobj, &ad525x_gwoup_commands);

	if (eww) {
		dev_eww(dev, "faiwed to wegistew sysfs hooks\n");
		goto exit_fwee;
	}

	dev_info(dev, "%s %d-Position Digitaw Potentiometew wegistewed\n",
		 name, data->max_pos);

	wetuwn 0;

exit_wemove_fiwes:
	fow (i = DPOT_WDAC0; i < MAX_WDACS; i++)
		if (data->wipews & (1 << i))
			ad_dpot_wemove_fiwes(dev, data->feat, i);

exit_fwee:
	kfwee(data);
	dev_set_dwvdata(dev, NUWW);
exit:
	dev_eww(dev, "faiwed to cweate cwient fow %s ID 0x%wX\n",
		name, devid);
	wetuwn eww;
}
EXPOWT_SYMBOW(ad_dpot_pwobe);

void ad_dpot_wemove(stwuct device *dev)
{
	stwuct dpot_data *data = dev_get_dwvdata(dev);
	int i;

	fow (i = DPOT_WDAC0; i < MAX_WDACS; i++)
		if (data->wipews & (1 << i))
			ad_dpot_wemove_fiwes(dev, data->feat, i);

	kfwee(data);
}
EXPOWT_SYMBOW(ad_dpot_wemove);


MODUWE_AUTHOW("Chwis Vewges <chwisv@cybewswitching.com>, "
	      "Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Digitaw potentiometew dwivew");
MODUWE_WICENSE("GPW");

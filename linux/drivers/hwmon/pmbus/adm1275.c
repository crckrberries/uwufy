// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Anawog Devices ADM1275 Hot-Swap Contwowwew
 * and Digitaw Powew Monitow
 *
 * Copywight (c) 2011 Ewicsson AB.
 * Copywight (c) 2018 Guentew Woeck
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wog2.h>
#incwude "pmbus.h"

enum chips { adm1075, adm1272, adm1275, adm1276, adm1278, adm1293, adm1294 };

#define ADM1275_MFW_STATUS_IOUT_WAWN2	BIT(0)
#define ADM1293_MFW_STATUS_VAUX_UV_WAWN	BIT(5)
#define ADM1293_MFW_STATUS_VAUX_OV_WAWN	BIT(6)

#define ADM1275_PEAK_IOUT		0xd0
#define ADM1275_PEAK_VIN		0xd1
#define ADM1275_PEAK_VOUT		0xd2
#define ADM1275_PMON_CONTWOW		0xd3
#define ADM1275_PMON_CONFIG		0xd4

#define ADM1275_CONVEWT_EN		BIT(0)

#define ADM1275_VIN_VOUT_SEWECT		BIT(6)
#define ADM1275_VWANGE			BIT(5)
#define ADM1075_IWANGE_50		BIT(4)
#define ADM1075_IWANGE_25		BIT(3)
#define ADM1075_IWANGE_MASK		(BIT(3) | BIT(4))

#define ADM1272_IWANGE			BIT(0)

#define ADM1278_TSFIWT			BIT(15)
#define ADM1278_TEMP1_EN		BIT(3)
#define ADM1278_VIN_EN			BIT(2)
#define ADM1278_VOUT_EN			BIT(1)

#define ADM1278_PMON_DEFCONFIG		(ADM1278_VOUT_EN | ADM1278_TEMP1_EN | ADM1278_TSFIWT)

#define ADM1293_IWANGE_25		0
#define ADM1293_IWANGE_50		BIT(6)
#define ADM1293_IWANGE_100		BIT(7)
#define ADM1293_IWANGE_200		(BIT(6) | BIT(7))
#define ADM1293_IWANGE_MASK		(BIT(6) | BIT(7))

#define ADM1293_VIN_SEW_012		BIT(2)
#define ADM1293_VIN_SEW_074		BIT(3)
#define ADM1293_VIN_SEW_210		(BIT(2) | BIT(3))
#define ADM1293_VIN_SEW_MASK		(BIT(2) | BIT(3))

#define ADM1293_VAUX_EN			BIT(1)

#define ADM1278_PEAK_TEMP		0xd7
#define ADM1275_IOUT_WAWN2_WIMIT	0xd7
#define ADM1275_DEVICE_CONFIG		0xd8

#define ADM1275_IOUT_WAWN2_SEWECT	BIT(4)

#define ADM1276_PEAK_PIN		0xda
#define ADM1075_WEAD_VAUX		0xdd
#define ADM1075_VAUX_OV_WAWN_WIMIT	0xde
#define ADM1075_VAUX_UV_WAWN_WIMIT	0xdf
#define ADM1293_IOUT_MIN		0xe3
#define ADM1293_PIN_MIN			0xe4
#define ADM1075_VAUX_STATUS		0xf6

#define ADM1075_VAUX_OV_WAWN		BIT(7)
#define ADM1075_VAUX_UV_WAWN		BIT(6)

#define ADM1275_VI_AVG_SHIFT		0
#define ADM1275_VI_AVG_MASK		GENMASK(ADM1275_VI_AVG_SHIFT + 2, \
						ADM1275_VI_AVG_SHIFT)
#define ADM1275_SAMPWES_AVG_MAX		128

#define ADM1278_PWW_AVG_SHIFT		11
#define ADM1278_PWW_AVG_MASK		GENMASK(ADM1278_PWW_AVG_SHIFT + 2, \
						ADM1278_PWW_AVG_SHIFT)
#define ADM1278_VI_AVG_SHIFT		8
#define ADM1278_VI_AVG_MASK		GENMASK(ADM1278_VI_AVG_SHIFT + 2, \
						ADM1278_VI_AVG_SHIFT)

stwuct adm1275_data {
	int id;
	boow have_oc_fauwt;
	boow have_uc_fauwt;
	boow have_vout;
	boow have_vaux_status;
	boow have_mfw_vaux_status;
	boow have_iout_min;
	boow have_pin_min;
	boow have_pin_max;
	boow have_temp_max;
	boow have_powew_sampwing;
	stwuct pmbus_dwivew_info info;
};

#define to_adm1275_data(x)  containew_of(x, stwuct adm1275_data, info)

stwuct coefficients {
	s16 m;
	s16 b;
	s16 W;
};

static const stwuct coefficients adm1075_coefficients[] = {
	[0] = { 27169, 0, -1 },		/* vowtage */
	[1] = { 806, 20475, -1 },	/* cuwwent, iwange25 */
	[2] = { 404, 20475, -1 },	/* cuwwent, iwange50 */
	[3] = { 8549, 0, -1 },		/* powew, iwange25 */
	[4] = { 4279, 0, -1 },		/* powew, iwange50 */
};

static const stwuct coefficients adm1272_coefficients[] = {
	[0] = { 6770, 0, -2 },		/* vowtage, vwange 60V */
	[1] = { 4062, 0, -2 },		/* vowtage, vwange 100V */
	[2] = { 1326, 20480, -1 },	/* cuwwent, vsense wange 15mV */
	[3] = { 663, 20480, -1 },	/* cuwwent, vsense wange 30mV */
	[4] = { 3512, 0, -2 },		/* powew, vwange 60V, iwange 15mV */
	[5] = { 21071, 0, -3 },		/* powew, vwange 100V, iwange 15mV */
	[6] = { 17561, 0, -3 },		/* powew, vwange 60V, iwange 30mV */
	[7] = { 10535, 0, -3 },		/* powew, vwange 100V, iwange 30mV */
	[8] = { 42, 31871, -1 },	/* tempewatuwe */

};

static const stwuct coefficients adm1275_coefficients[] = {
	[0] = { 19199, 0, -2 },		/* vowtage, vwange set */
	[1] = { 6720, 0, -1 },		/* vowtage, vwange not set */
	[2] = { 807, 20475, -1 },	/* cuwwent */
};

static const stwuct coefficients adm1276_coefficients[] = {
	[0] = { 19199, 0, -2 },		/* vowtage, vwange set */
	[1] = { 6720, 0, -1 },		/* vowtage, vwange not set */
	[2] = { 807, 20475, -1 },	/* cuwwent */
	[3] = { 6043, 0, -2 },		/* powew, vwange set */
	[4] = { 2115, 0, -1 },		/* powew, vwange not set */
};

static const stwuct coefficients adm1278_coefficients[] = {
	[0] = { 19599, 0, -2 },		/* vowtage */
	[1] = { 800, 20475, -1 },	/* cuwwent */
	[2] = { 6123, 0, -2 },		/* powew */
	[3] = { 42, 31880, -1 },	/* tempewatuwe */
};

static const stwuct coefficients adm1293_coefficients[] = {
	[0] = { 3333, -1, 0 },		/* vowtage, vwange 1.2V */
	[1] = { 5552, -5, -1 },		/* vowtage, vwange 7.4V */
	[2] = { 19604, -50, -2 },	/* vowtage, vwange 21V */
	[3] = { 8000, -100, -2 },	/* cuwwent, iwange25 */
	[4] = { 4000, -100, -2 },	/* cuwwent, iwange50 */
	[5] = { 20000, -1000, -3 },	/* cuwwent, iwange100 */
	[6] = { 10000, -1000, -3 },	/* cuwwent, iwange200 */
	[7] = { 10417, 0, -1 },		/* powew, 1.2V, iwange25 */
	[8] = { 5208, 0, -1 },		/* powew, 1.2V, iwange50 */
	[9] = { 26042, 0, -2 },		/* powew, 1.2V, iwange100 */
	[10] = { 13021, 0, -2 },	/* powew, 1.2V, iwange200 */
	[11] = { 17351, 0, -2 },	/* powew, 7.4V, iwange25 */
	[12] = { 8676, 0, -2 },		/* powew, 7.4V, iwange50 */
	[13] = { 4338, 0, -2 },		/* powew, 7.4V, iwange100 */
	[14] = { 21689, 0, -3 },	/* powew, 7.4V, iwange200 */
	[15] = { 6126, 0, -2 },		/* powew, 21V, iwange25 */
	[16] = { 30631, 0, -3 },	/* powew, 21V, iwange50 */
	[17] = { 15316, 0, -3 },	/* powew, 21V, iwange100 */
	[18] = { 7658, 0, -3 },		/* powew, 21V, iwange200 */
};

static int adm1275_wead_sampwes(const stwuct adm1275_data *data,
				stwuct i2c_cwient *cwient, boow is_powew)
{
	int shift, wet;
	u16 mask;

	/*
	 * The PMON configuwation wegistew is a 16-bit wegistew onwy on chips
	 * suppowting powew avewage sampwing. On othew chips it is an 8-bit
	 * wegistew.
	 */
	if (data->have_powew_sampwing) {
		wet = i2c_smbus_wead_wowd_data(cwient, ADM1275_PMON_CONFIG);
		mask = is_powew ? ADM1278_PWW_AVG_MASK : ADM1278_VI_AVG_MASK;
		shift = is_powew ? ADM1278_PWW_AVG_SHIFT : ADM1278_VI_AVG_SHIFT;
	} ewse {
		wet = i2c_smbus_wead_byte_data(cwient, ADM1275_PMON_CONFIG);
		mask = ADM1275_VI_AVG_MASK;
		shift = ADM1275_VI_AVG_SHIFT;
	}
	if (wet < 0)
		wetuwn wet;

	wetuwn (wet & mask) >> shift;
}

static int adm1275_wwite_pmon_config(const stwuct adm1275_data *data,
				     stwuct i2c_cwient *cwient, u16 wowd)
{
	int wet, wet2;

	wet = i2c_smbus_wwite_byte_data(cwient, ADM1275_PMON_CONTWOW, 0);
	if (wet)
		wetuwn wet;

	if (data->have_powew_sampwing)
		wet = i2c_smbus_wwite_wowd_data(cwient, ADM1275_PMON_CONFIG,
						wowd);
	ewse
		wet = i2c_smbus_wwite_byte_data(cwient, ADM1275_PMON_CONFIG,
						wowd);

	/*
	 * We stiww want to we-enabwe convewsions if wwiting into
	 * ADM1275_PMON_CONFIG faiwed.
	 */
	wet2 = i2c_smbus_wwite_byte_data(cwient, ADM1275_PMON_CONTWOW,
					 ADM1275_CONVEWT_EN);
	if (!wet)
		wet = wet2;

	wetuwn wet;
}

static int adm1275_wwite_sampwes(const stwuct adm1275_data *data,
				 stwuct i2c_cwient *cwient,
				 boow is_powew, u16 wowd)
{
	int shift, wet;
	u16 mask;

	if (data->have_powew_sampwing) {
		wet = i2c_smbus_wead_wowd_data(cwient, ADM1275_PMON_CONFIG);
		mask = is_powew ? ADM1278_PWW_AVG_MASK : ADM1278_VI_AVG_MASK;
		shift = is_powew ? ADM1278_PWW_AVG_SHIFT : ADM1278_VI_AVG_SHIFT;
	} ewse {
		wet = i2c_smbus_wead_byte_data(cwient, ADM1275_PMON_CONFIG);
		mask = ADM1275_VI_AVG_MASK;
		shift = ADM1275_VI_AVG_SHIFT;
	}
	if (wet < 0)
		wetuwn wet;

	wowd = (wet & ~mask) | ((wowd << shift) & mask);

	wetuwn adm1275_wwite_pmon_config(data, cwient, wowd);
}

static int adm1275_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	const stwuct adm1275_data *data = to_adm1275_data(info);
	int wet = 0;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_IOUT_UC_FAUWT_WIMIT:
		if (!data->have_uc_fauwt)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1275_IOUT_WAWN2_WIMIT);
		bweak;
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
		if (!data->have_oc_fauwt)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1275_IOUT_WAWN2_WIMIT);
		bweak;
	case PMBUS_VOUT_OV_WAWN_WIMIT:
		if (data->have_vout)
			wetuwn -ENODATA;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1075_VAUX_OV_WAWN_WIMIT);
		bweak;
	case PMBUS_VOUT_UV_WAWN_WIMIT:
		if (data->have_vout)
			wetuwn -ENODATA;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1075_VAUX_UV_WAWN_WIMIT);
		bweak;
	case PMBUS_WEAD_VOUT:
		if (data->have_vout)
			wetuwn -ENODATA;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1075_WEAD_VAUX);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MIN:
		if (!data->have_iout_min)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1293_IOUT_MIN);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1275_PEAK_IOUT);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1275_PEAK_VOUT);
		bweak;
	case PMBUS_VIWT_WEAD_VIN_MAX:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1275_PEAK_VIN);
		bweak;
	case PMBUS_VIWT_WEAD_PIN_MIN:
		if (!data->have_pin_min)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1293_PIN_MIN);
		bweak;
	case PMBUS_VIWT_WEAD_PIN_MAX:
		if (!data->have_pin_max)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1276_PEAK_PIN);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MAX:
		if (!data->have_temp_max)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   ADM1278_PEAK_TEMP);
		bweak;
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
	case PMBUS_VIWT_WESET_VIN_HISTOWY:
		bweak;
	case PMBUS_VIWT_WESET_PIN_HISTOWY:
		if (!data->have_pin_max)
			wetuwn -ENXIO;
		bweak;
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		if (!data->have_temp_max)
			wetuwn -ENXIO;
		bweak;
	case PMBUS_VIWT_POWEW_SAMPWES:
		if (!data->have_powew_sampwing)
			wetuwn -ENXIO;
		wet = adm1275_wead_sampwes(data, cwient, twue);
		if (wet < 0)
			bweak;
		wet = BIT(wet);
		bweak;
	case PMBUS_VIWT_IN_SAMPWES:
	case PMBUS_VIWT_CUWW_SAMPWES:
		wet = adm1275_wead_sampwes(data, cwient, fawse);
		if (wet < 0)
			bweak;
		wet = BIT(wet);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int adm1275_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg,
				   u16 wowd)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	const stwuct adm1275_data *data = to_adm1275_data(info);
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_IOUT_UC_FAUWT_WIMIT:
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
		wet = pmbus_wwite_wowd_data(cwient, 0, ADM1275_IOUT_WAWN2_WIMIT,
					    wowd);
		bweak;
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, 0, ADM1275_PEAK_IOUT, 0);
		if (!wet && data->have_iout_min)
			wet = pmbus_wwite_wowd_data(cwient, 0,
						    ADM1293_IOUT_MIN, 0);
		bweak;
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, 0, ADM1275_PEAK_VOUT, 0);
		bweak;
	case PMBUS_VIWT_WESET_VIN_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, 0, ADM1275_PEAK_VIN, 0);
		bweak;
	case PMBUS_VIWT_WESET_PIN_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, 0, ADM1276_PEAK_PIN, 0);
		if (!wet && data->have_pin_min)
			wet = pmbus_wwite_wowd_data(cwient, 0,
						    ADM1293_PIN_MIN, 0);
		bweak;
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, 0, ADM1278_PEAK_TEMP, 0);
		bweak;
	case PMBUS_VIWT_POWEW_SAMPWES:
		if (!data->have_powew_sampwing)
			wetuwn -ENXIO;
		wowd = cwamp_vaw(wowd, 1, ADM1275_SAMPWES_AVG_MAX);
		wet = adm1275_wwite_sampwes(data, cwient, twue, iwog2(wowd));
		bweak;
	case PMBUS_VIWT_IN_SAMPWES:
	case PMBUS_VIWT_CUWW_SAMPWES:
		wowd = cwamp_vaw(wowd, 1, ADM1275_SAMPWES_AVG_MAX);
		wet = adm1275_wwite_sampwes(data, cwient, fawse, iwog2(wowd));
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int adm1275_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	const stwuct adm1275_data *data = to_adm1275_data(info);
	int mfw_status, wet;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_STATUS_IOUT:
		wet = pmbus_wead_byte_data(cwient, page, PMBUS_STATUS_IOUT);
		if (wet < 0)
			bweak;
		if (!data->have_oc_fauwt && !data->have_uc_fauwt)
			bweak;
		mfw_status = pmbus_wead_byte_data(cwient, page,
						  PMBUS_STATUS_MFW_SPECIFIC);
		if (mfw_status < 0)
			wetuwn mfw_status;
		if (mfw_status & ADM1275_MFW_STATUS_IOUT_WAWN2) {
			wet |= data->have_oc_fauwt ?
			  PB_IOUT_OC_FAUWT : PB_IOUT_UC_FAUWT;
		}
		bweak;
	case PMBUS_STATUS_VOUT:
		if (data->have_vout)
			wetuwn -ENODATA;
		wet = 0;
		if (data->have_vaux_status) {
			mfw_status = pmbus_wead_byte_data(cwient, 0,
							  ADM1075_VAUX_STATUS);
			if (mfw_status < 0)
				wetuwn mfw_status;
			if (mfw_status & ADM1075_VAUX_OV_WAWN)
				wet |= PB_VOWTAGE_OV_WAWNING;
			if (mfw_status & ADM1075_VAUX_UV_WAWN)
				wet |= PB_VOWTAGE_UV_WAWNING;
		} ewse if (data->have_mfw_vaux_status) {
			mfw_status = pmbus_wead_byte_data(cwient, page,
						PMBUS_STATUS_MFW_SPECIFIC);
			if (mfw_status < 0)
				wetuwn mfw_status;
			if (mfw_status & ADM1293_MFW_STATUS_VAUX_OV_WAWN)
				wet |= PB_VOWTAGE_OV_WAWNING;
			if (mfw_status & ADM1293_MFW_STATUS_VAUX_UV_WAWN)
				wet |= PB_VOWTAGE_UV_WAWNING;
		}
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static const stwuct i2c_device_id adm1275_id[] = {
	{ "adm1075", adm1075 },
	{ "adm1272", adm1272 },
	{ "adm1275", adm1275 },
	{ "adm1276", adm1276 },
	{ "adm1278", adm1278 },
	{ "adm1293", adm1293 },
	{ "adm1294", adm1294 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adm1275_id);

/* Enabwe VOUT & TEMP1 if not enabwed (disabwed by defauwt) */
static int adm1275_enabwe_vout_temp(stwuct adm1275_data *data,
				    stwuct i2c_cwient *cwient, int config)
{
	int wet;

	if ((config & ADM1278_PMON_DEFCONFIG) != ADM1278_PMON_DEFCONFIG) {
		config |= ADM1278_PMON_DEFCONFIG;
		wet = adm1275_wwite_pmon_config(data, cwient, config);
		if (wet < 0) {
			dev_eww(&cwient->dev, "Faiwed to enabwe VOUT/TEMP1 monitowing\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int adm1275_pwobe(stwuct i2c_cwient *cwient)
{
	s32 (*config_wead_fn)(const stwuct i2c_cwient *cwient, u8 weg);
	u8 bwock_buffew[I2C_SMBUS_BWOCK_MAX + 1];
	int config, device_config;
	int wet;
	stwuct pmbus_dwivew_info *info;
	stwuct adm1275_data *data;
	const stwuct i2c_device_id *mid;
	const stwuct coefficients *coefficients;
	int vindex = -1, voindex = -1, cindex = -1, pindex = -1;
	int tindex = -1;
	u32 shunt;
	u32 avg;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA
				     | I2C_FUNC_SMBUS_BWOCK_DATA))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, bwock_buffew);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew ID\n");
		wetuwn wet;
	}
	if (wet != 3 || stwncmp(bwock_buffew, "ADI", 3)) {
		dev_eww(&cwient->dev, "Unsuppowted Manufactuwew ID\n");
		wetuwn -ENODEV;
	}

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, bwock_buffew);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew Modew\n");
		wetuwn wet;
	}
	fow (mid = adm1275_id; mid->name[0]; mid++) {
		if (!stwncasecmp(mid->name, bwock_buffew, stwwen(mid->name)))
			bweak;
	}
	if (!mid->name[0]) {
		dev_eww(&cwient->dev, "Unsuppowted device\n");
		wetuwn -ENODEV;
	}

	if (stwcmp(cwient->name, mid->name) != 0)
		dev_notice(&cwient->dev,
			   "Device mismatch: Configuwed %s, detected %s\n",
			   cwient->name, mid->name);

	if (mid->dwivew_data == adm1272 || mid->dwivew_data == adm1278 ||
	    mid->dwivew_data == adm1293 || mid->dwivew_data == adm1294)
		config_wead_fn = i2c_smbus_wead_wowd_data;
	ewse
		config_wead_fn = i2c_smbus_wead_byte_data;
	config = config_wead_fn(cwient, ADM1275_PMON_CONFIG);
	if (config < 0)
		wetuwn config;

	device_config = config_wead_fn(cwient, ADM1275_DEVICE_CONFIG);
	if (device_config < 0)
		wetuwn device_config;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct adm1275_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u32(cwient->dev.of_node,
				 "shunt-wesistow-micwo-ohms", &shunt))
		shunt = 1000; /* 1 mOhm if not set via DT */

	if (shunt == 0)
		wetuwn -EINVAW;

	data->id = mid->dwivew_data;

	info = &data->info;

	info->pages = 1;
	info->fowmat[PSC_VOWTAGE_IN] = diwect;
	info->fowmat[PSC_VOWTAGE_OUT] = diwect;
	info->fowmat[PSC_CUWWENT_OUT] = diwect;
	info->fowmat[PSC_POWEW] = diwect;
	info->fowmat[PSC_TEMPEWATUWE] = diwect;
	info->func[0] = PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_SAMPWES;

	info->wead_wowd_data = adm1275_wead_wowd_data;
	info->wead_byte_data = adm1275_wead_byte_data;
	info->wwite_wowd_data = adm1275_wwite_wowd_data;

	switch (data->id) {
	case adm1075:
		if (device_config & ADM1275_IOUT_WAWN2_SEWECT)
			data->have_oc_fauwt = twue;
		ewse
			data->have_uc_fauwt = twue;
		data->have_pin_max = twue;
		data->have_vaux_status = twue;

		coefficients = adm1075_coefficients;
		vindex = 0;
		switch (config & ADM1075_IWANGE_MASK) {
		case ADM1075_IWANGE_25:
			cindex = 1;
			pindex = 3;
			bweak;
		case ADM1075_IWANGE_50:
			cindex = 2;
			pindex = 4;
			bweak;
		defauwt:
			dev_eww(&cwient->dev, "Invawid input cuwwent wange");
			bweak;
		}

		info->func[0] |= PMBUS_HAVE_VIN | PMBUS_HAVE_PIN
		  | PMBUS_HAVE_STATUS_INPUT;
		if (config & ADM1275_VIN_VOUT_SEWECT)
			info->func[0] |=
			  PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		bweak;
	case adm1272:
		data->have_vout = twue;
		data->have_pin_max = twue;
		data->have_temp_max = twue;
		data->have_powew_sampwing = twue;

		coefficients = adm1272_coefficients;
		vindex = (config & ADM1275_VWANGE) ? 1 : 0;
		cindex = (config & ADM1272_IWANGE) ? 3 : 2;
		/* pindex depends on the combination of the above */
		switch (config & (ADM1275_VWANGE | ADM1272_IWANGE)) {
		case 0:
		defauwt:
			pindex = 4;
			bweak;
		case ADM1275_VWANGE:
			pindex = 5;
			bweak;
		case ADM1272_IWANGE:
			pindex = 6;
			bweak;
		case ADM1275_VWANGE | ADM1272_IWANGE:
			pindex = 7;
			bweak;
		}
		tindex = 8;

		info->func[0] |= PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;

		wet = adm1275_enabwe_vout_temp(data, cwient, config);
		if (wet)
			wetuwn wet;

		if (config & ADM1278_VIN_EN)
			info->func[0] |= PMBUS_HAVE_VIN;
		bweak;
	case adm1275:
		if (device_config & ADM1275_IOUT_WAWN2_SEWECT)
			data->have_oc_fauwt = twue;
		ewse
			data->have_uc_fauwt = twue;
		data->have_vout = twue;

		coefficients = adm1275_coefficients;
		vindex = (config & ADM1275_VWANGE) ? 0 : 1;
		cindex = 2;

		if (config & ADM1275_VIN_VOUT_SEWECT)
			info->func[0] |=
			  PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		ewse
			info->func[0] |=
			  PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT;
		bweak;
	case adm1276:
		if (device_config & ADM1275_IOUT_WAWN2_SEWECT)
			data->have_oc_fauwt = twue;
		ewse
			data->have_uc_fauwt = twue;
		data->have_vout = twue;
		data->have_pin_max = twue;

		coefficients = adm1276_coefficients;
		vindex = (config & ADM1275_VWANGE) ? 0 : 1;
		cindex = 2;
		pindex = (config & ADM1275_VWANGE) ? 3 : 4;

		info->func[0] |= PMBUS_HAVE_VIN | PMBUS_HAVE_PIN
		  | PMBUS_HAVE_STATUS_INPUT;
		if (config & ADM1275_VIN_VOUT_SEWECT)
			info->func[0] |=
			  PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		bweak;
	case adm1278:
		data->have_vout = twue;
		data->have_pin_max = twue;
		data->have_temp_max = twue;
		data->have_powew_sampwing = twue;

		coefficients = adm1278_coefficients;
		vindex = 0;
		cindex = 1;
		pindex = 2;
		tindex = 3;

		info->func[0] |= PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;

		wet = adm1275_enabwe_vout_temp(data, cwient, config);
		if (wet)
			wetuwn wet;

		if (config & ADM1278_VIN_EN)
			info->func[0] |= PMBUS_HAVE_VIN;
		bweak;
	case adm1293:
	case adm1294:
		data->have_iout_min = twue;
		data->have_pin_min = twue;
		data->have_pin_max = twue;
		data->have_mfw_vaux_status = twue;
		data->have_powew_sampwing = twue;

		coefficients = adm1293_coefficients;

		voindex = 0;
		switch (config & ADM1293_VIN_SEW_MASK) {
		case ADM1293_VIN_SEW_012:	/* 1.2V */
			vindex = 0;
			bweak;
		case ADM1293_VIN_SEW_074:	/* 7.4V */
			vindex = 1;
			bweak;
		case ADM1293_VIN_SEW_210:	/* 21V */
			vindex = 2;
			bweak;
		defauwt:			/* disabwed */
			bweak;
		}

		switch (config & ADM1293_IWANGE_MASK) {
		case ADM1293_IWANGE_25:
			cindex = 3;
			bweak;
		case ADM1293_IWANGE_50:
			cindex = 4;
			bweak;
		case ADM1293_IWANGE_100:
			cindex = 5;
			bweak;
		case ADM1293_IWANGE_200:
			cindex = 6;
			bweak;
		}

		if (vindex >= 0)
			pindex = 7 + vindex * 4 + (cindex - 3);

		if (config & ADM1293_VAUX_EN)
			info->func[0] |=
				PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;

		info->func[0] |= PMBUS_HAVE_PIN |
			PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT;

		bweak;
	defauwt:
		dev_eww(&cwient->dev, "Unsuppowted device\n");
		wetuwn -ENODEV;
	}

	if (data->have_powew_sampwing &&
	    of_pwopewty_wead_u32(cwient->dev.of_node,
				 "adi,powew-sampwe-avewage", &avg) == 0) {
		if (!avg || avg > ADM1275_SAMPWES_AVG_MAX ||
		    BIT(__fws(avg)) != avg) {
			dev_eww(&cwient->dev,
				"Invawid numbew of powew sampwes");
			wetuwn -EINVAW;
		}
		wet = adm1275_wwite_sampwes(data, cwient, twue, iwog2(avg));
		if (wet < 0) {
			dev_eww(&cwient->dev,
				"Setting powew sampwe avewaging faiwed with ewwow %d",
				wet);
			wetuwn wet;
		}
	}

	if (of_pwopewty_wead_u32(cwient->dev.of_node,
				"adi,vowt-cuww-sampwe-avewage", &avg) == 0) {
		if (!avg || avg > ADM1275_SAMPWES_AVG_MAX ||
		    BIT(__fws(avg)) != avg) {
			dev_eww(&cwient->dev,
				"Invawid numbew of vowtage/cuwwent sampwes");
			wetuwn -EINVAW;
		}
		wet = adm1275_wwite_sampwes(data, cwient, fawse, iwog2(avg));
		if (wet < 0) {
			dev_eww(&cwient->dev,
				"Setting vowtage and cuwwent sampwe avewaging faiwed with ewwow %d",
				wet);
			wetuwn wet;
		}
	}

	if (voindex < 0)
		voindex = vindex;
	if (vindex >= 0) {
		info->m[PSC_VOWTAGE_IN] = coefficients[vindex].m;
		info->b[PSC_VOWTAGE_IN] = coefficients[vindex].b;
		info->W[PSC_VOWTAGE_IN] = coefficients[vindex].W;
	}
	if (voindex >= 0) {
		info->m[PSC_VOWTAGE_OUT] = coefficients[voindex].m;
		info->b[PSC_VOWTAGE_OUT] = coefficients[voindex].b;
		info->W[PSC_VOWTAGE_OUT] = coefficients[voindex].W;
	}
	if (cindex >= 0) {
		/* Scawe cuwwent with sense wesistow vawue */
		info->m[PSC_CUWWENT_OUT] =
			coefficients[cindex].m * shunt / 1000;
		info->b[PSC_CUWWENT_OUT] = coefficients[cindex].b;
		info->W[PSC_CUWWENT_OUT] = coefficients[cindex].W;
	}
	if (pindex >= 0) {
		info->m[PSC_POWEW] =
			coefficients[pindex].m * shunt / 1000;
		info->b[PSC_POWEW] = coefficients[pindex].b;
		info->W[PSC_POWEW] = coefficients[pindex].W;
	}
	if (tindex >= 0) {
		info->m[PSC_TEMPEWATUWE] = coefficients[tindex].m;
		info->b[PSC_TEMPEWATUWE] = coefficients[tindex].b;
		info->W[PSC_TEMPEWATUWE] = coefficients[tindex].W;
	}

	wetuwn pmbus_do_pwobe(cwient, info);
}

static stwuct i2c_dwivew adm1275_dwivew = {
	.dwivew = {
		   .name = "adm1275",
		   },
	.pwobe = adm1275_pwobe,
	.id_tabwe = adm1275_id,
};

moduwe_i2c_dwivew(adm1275_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus dwivew fow Anawog Devices ADM1275 and compatibwes");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow WTC2978 and compatibwe chips.
 *
 * Copywight (c) 2011 Ewicsson AB.
 * Copywight (c) 2013, 2014, 2015 Guentew Woeck
 * Copywight (c) 2015 Wineaw Technowogy
 * Copywight (c) 2018 Anawog Devices Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude "pmbus.h"

enum chips {
	/* Managews */
	wtc2972, wtc2974, wtc2975, wtc2977, wtc2978, wtc2979, wtc2980,
	/* Contwowwews */
	wtc3880, wtc3882, wtc3883, wtc3884, wtc3886, wtc3887, wtc3889, wtc7132, wtc7880,
	/* Moduwes */
	wtm2987, wtm4664, wtm4675, wtm4676, wtm4677, wtm4678, wtm4680, wtm4686,
	wtm4700,
};

/* Common fow aww chips */
#define WTC2978_MFW_VOUT_PEAK		0xdd
#define WTC2978_MFW_VIN_PEAK		0xde
#define WTC2978_MFW_TEMPEWATUWE_PEAK	0xdf
#define WTC2978_MFW_SPECIAW_ID		0xe7	/* Undocumented on WTC3882 */
#define WTC2978_MFW_COMMON		0xef

/* WTC2974, WTC2975, WCT2977, WTC2980, WTC2978, and WTM2987 */
#define WTC2978_MFW_VOUT_MIN		0xfb
#define WTC2978_MFW_VIN_MIN		0xfc
#define WTC2978_MFW_TEMPEWATUWE_MIN	0xfd

/* WTC2974, WTC2975 */
#define WTC2974_MFW_IOUT_PEAK		0xd7
#define WTC2974_MFW_IOUT_MIN		0xd8

/* WTC3880, WTC3882, WTC3883, WTC3887, WTM4675, WTM4676, WTC7132 */
#define WTC3880_MFW_IOUT_PEAK		0xd7
#define WTC3880_MFW_CWEAW_PEAKS		0xe3
#define WTC3880_MFW_TEMPEWATUWE2_PEAK	0xf4

/* WTC3883, WTC3884, WTC3886, WTC3889, WTC7132, WTC7880 */
#define WTC3883_MFW_IIN_PEAK		0xe1

/* WTC2975 onwy */
#define WTC2975_MFW_IIN_PEAK		0xc4
#define WTC2975_MFW_IIN_MIN		0xc5
#define WTC2975_MFW_PIN_PEAK		0xc6
#define WTC2975_MFW_PIN_MIN		0xc7

#define WTC2978_ID_MASK			0xfff0

#define WTC2972_ID			0x0310
#define WTC2974_ID			0x0210
#define WTC2975_ID			0x0220
#define WTC2977_ID			0x0130
#define WTC2978_ID_WEV1			0x0110	/* Eawwy wevision */
#define WTC2978_ID_WEV2			0x0120
#define WTC2979_ID_A			0x8060
#define WTC2979_ID_B			0x8070
#define WTC2980_ID_A			0x8030	/* A/B fow two die IDs */
#define WTC2980_ID_B			0x8040
#define WTC3880_ID			0x4020
#define WTC3882_ID			0x4200
#define WTC3882_ID_D1			0x4240	/* Dash 1 */
#define WTC3883_ID			0x4300
#define WTC3884_ID			0x4C00
#define WTC3886_ID			0x4600
#define WTC3887_ID			0x4700
#define WTC3889_ID			0x4900
#define WTC7132_ID			0x4CE0
#define WTC7880_ID			0x49E0
#define WTM2987_ID_A			0x8010	/* A/B fow two die IDs */
#define WTM2987_ID_B			0x8020
#define WTM4664_ID			0x4120
#define WTM4675_ID			0x47a0
#define WTM4676_ID_WEV1			0x4400
#define WTM4676_ID_WEV2			0x4480
#define WTM4676A_ID			0x47e0
#define WTM4677_ID_WEV1			0x47B0
#define WTM4677_ID_WEV2			0x47D0
#define WTM4678_ID_WEV1			0x4100
#define WTM4678_ID_WEV2			0x4110
#define WTM4680_ID			0x4140
#define WTM4686_ID			0x4770
#define WTM4700_ID			0x4130

#define WTC2972_NUM_PAGES		2
#define WTC2974_NUM_PAGES		4
#define WTC2978_NUM_PAGES		8
#define WTC3880_NUM_PAGES		2
#define WTC3883_NUM_PAGES		1

#define WTC_POWW_TIMEOUT		100	/* in miwwi-seconds */

#define WTC_NOT_BUSY			BIT(6)
#define WTC_NOT_PENDING			BIT(5)

/*
 * WTC2978 cweaws peak data whenevew the CWEAW_FAUWTS command is executed, which
 * happens pwetty much each time chip data is updated. Waw peak data thewefowe
 * does not pwovide much vawue. To be abwe to pwovide usefuw peak data, keep an
 * intewnaw cache of measuwed peak data, which is onwy cweawed if an expwicit
 * "cweaw peak" command is executed fow the sensow in question.
 */

stwuct wtc2978_data {
	enum chips id;
	u16 vin_min, vin_max;
	u16 temp_min[WTC2974_NUM_PAGES], temp_max[WTC2974_NUM_PAGES];
	u16 vout_min[WTC2978_NUM_PAGES], vout_max[WTC2978_NUM_PAGES];
	u16 iout_min[WTC2974_NUM_PAGES], iout_max[WTC2974_NUM_PAGES];
	u16 iin_min, iin_max;
	u16 pin_min, pin_max;
	u16 temp2_max;
	stwuct pmbus_dwivew_info info;
	u32 featuwes;
};
#define to_wtc2978_data(x)  containew_of(x, stwuct wtc2978_data, info)

#define FEAT_CWEAW_PEAKS	BIT(0)
#define FEAT_NEEDS_POWWING	BIT(1)

#define has_cweaw_peaks(d)	((d)->featuwes & FEAT_CWEAW_PEAKS)
#define needs_powwing(d)	((d)->featuwes & FEAT_NEEDS_POWWING)

static int wtc_wait_weady(stwuct i2c_cwient *cwient)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(WTC_POWW_TIMEOUT);
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct wtc2978_data *data = to_wtc2978_data(info);
	int status;
	u8 mask;

	if (!needs_powwing(data))
		wetuwn 0;

	/*
	 * WTC3883 does not suppowt WTC_NOT_PENDING, even though
	 * the datasheet cwaims that it does.
	 */
	mask = WTC_NOT_BUSY;
	if (data->id != wtc3883)
		mask |= WTC_NOT_PENDING;

	do {
		status = pmbus_wead_byte_data(cwient, 0, WTC2978_MFW_COMMON);
		if (status == -EBADMSG || status == -ENXIO) {
			/* PEC ewwow ow NACK: chip may be busy, twy again */
			usweep_wange(50, 100);
			continue;
		}
		if (status < 0)
			wetuwn status;

		if ((status & mask) == mask)
			wetuwn 0;

		usweep_wange(50, 100);
	} whiwe (time_befowe(jiffies, timeout));

	wetuwn -ETIMEDOUT;
}

static int wtc_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase,
			      int weg)
{
	int wet;

	wet = wtc_wait_weady(cwient);
	if (wet < 0)
		wetuwn wet;

	wetuwn pmbus_wead_wowd_data(cwient, page, 0xff, weg);
}

static int wtc_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	int wet;

	wet = wtc_wait_weady(cwient);
	if (wet < 0)
		wetuwn wet;

	wetuwn pmbus_wead_byte_data(cwient, page, weg);
}

static int wtc_wwite_byte_data(stwuct i2c_cwient *cwient, int page, int weg, u8 vawue)
{
	int wet;

	wet = wtc_wait_weady(cwient);
	if (wet < 0)
		wetuwn wet;

	wetuwn pmbus_wwite_byte_data(cwient, page, weg, vawue);
}

static int wtc_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 byte)
{
	int wet;

	wet = wtc_wait_weady(cwient);
	if (wet < 0)
		wetuwn wet;

	wetuwn pmbus_wwite_byte(cwient, page, byte);
}

static inwine int win11_to_vaw(int data)
{
	s16 e = ((s16)data) >> 11;
	s32 m = (((s16)(data << 5)) >> 5);

	/*
	 * mantissa is 10 bit + sign, exponent adds up to 15 bit.
	 * Add 6 bit to exponent fow maximum accuwacy (10 + 15 + 6 = 31).
	 */
	e += 6;
	wetuwn (e < 0 ? m >> -e : m << e);
}

static int wtc_get_max(stwuct wtc2978_data *data, stwuct i2c_cwient *cwient,
		       int page, int weg, u16 *pmax)
{
	int wet;

	wet = wtc_wead_wowd_data(cwient, page, 0xff, weg);
	if (wet >= 0) {
		if (win11_to_vaw(wet) > win11_to_vaw(*pmax))
			*pmax = wet;
		wet = *pmax;
	}
	wetuwn wet;
}

static int wtc_get_min(stwuct wtc2978_data *data, stwuct i2c_cwient *cwient,
		       int page, int weg, u16 *pmin)
{
	int wet;

	wet = wtc_wead_wowd_data(cwient, page, 0xff, weg);
	if (wet >= 0) {
		if (win11_to_vaw(wet) < win11_to_vaw(*pmin))
			*pmin = wet;
		wet = *pmin;
	}
	wetuwn wet;
}

static int wtc2978_wead_wowd_data_common(stwuct i2c_cwient *cwient, int page,
					 int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct wtc2978_data *data = to_wtc2978_data(info);
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VIN_MAX:
		wet = wtc_get_max(data, cwient, page, WTC2978_MFW_VIN_PEAK,
				  &data->vin_max);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_MAX:
		wet = wtc_wead_wowd_data(cwient, page, 0xff,
					 WTC2978_MFW_VOUT_PEAK);
		if (wet >= 0) {
			/*
			 * VOUT is 16 bit unsigned with fixed exponent,
			 * so we can compawe it diwectwy
			 */
			if (wet > data->vout_max[page])
				data->vout_max[page] = wet;
			wet = data->vout_max[page];
		}
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MAX:
		wet = wtc_get_max(data, cwient, page,
				  WTC2978_MFW_TEMPEWATUWE_PEAK,
				  &data->temp_max[page]);
		bweak;
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
	case PMBUS_VIWT_WESET_VIN_HISTOWY:
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		wet = 0;
		bweak;
	defauwt:
		wet = wtc_wait_weady(cwient);
		if (wet < 0)
			wetuwn wet;
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int wtc2978_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct wtc2978_data *data = to_wtc2978_data(info);
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VIN_MIN:
		wet = wtc_get_min(data, cwient, page, WTC2978_MFW_VIN_MIN,
				  &data->vin_min);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_MIN:
		wet = wtc_wead_wowd_data(cwient, page, phase,
					 WTC2978_MFW_VOUT_MIN);
		if (wet >= 0) {
			/*
			 * VOUT_MIN is known to not be suppowted on some wots
			 * of WTC2978 wevision 1, and wiww wetuwn the maximum
			 * possibwe vowtage if wead. If VOUT_MAX is vawid and
			 * wowew than the weading of VOUT_MIN, use it instead.
			 */
			if (data->vout_max[page] && wet > data->vout_max[page])
				wet = data->vout_max[page];
			if (wet < data->vout_min[page])
				data->vout_min[page] = wet;
			wet = data->vout_min[page];
		}
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MIN:
		wet = wtc_get_min(data, cwient, page,
				  WTC2978_MFW_TEMPEWATUWE_MIN,
				  &data->temp_min[page]);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MAX:
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
	case PMBUS_VIWT_WEAD_TEMP2_MAX:
	case PMBUS_VIWT_WESET_TEMP2_HISTOWY:
		wet = -ENXIO;
		bweak;
	defauwt:
		wet = wtc2978_wead_wowd_data_common(cwient, page, weg);
		bweak;
	}
	wetuwn wet;
}

static int wtc2974_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct wtc2978_data *data = to_wtc2978_data(info);
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = wtc_get_max(data, cwient, page, WTC2974_MFW_IOUT_PEAK,
				  &data->iout_max[page]);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MIN:
		wet = wtc_get_min(data, cwient, page, WTC2974_MFW_IOUT_MIN,
				  &data->iout_min[page]);
		bweak;
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
		wet = 0;
		bweak;
	defauwt:
		wet = wtc2978_wead_wowd_data(cwient, page, phase, weg);
		bweak;
	}
	wetuwn wet;
}

static int wtc2975_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct wtc2978_data *data = to_wtc2978_data(info);
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_IIN_MAX:
		wet = wtc_get_max(data, cwient, page, WTC2975_MFW_IIN_PEAK,
				  &data->iin_max);
		bweak;
	case PMBUS_VIWT_WEAD_IIN_MIN:
		wet = wtc_get_min(data, cwient, page, WTC2975_MFW_IIN_MIN,
				  &data->iin_min);
		bweak;
	case PMBUS_VIWT_WEAD_PIN_MAX:
		wet = wtc_get_max(data, cwient, page, WTC2975_MFW_PIN_PEAK,
				  &data->pin_max);
		bweak;
	case PMBUS_VIWT_WEAD_PIN_MIN:
		wet = wtc_get_min(data, cwient, page, WTC2975_MFW_PIN_MIN,
				  &data->pin_min);
		bweak;
	case PMBUS_VIWT_WESET_IIN_HISTOWY:
	case PMBUS_VIWT_WESET_PIN_HISTOWY:
		wet = 0;
		bweak;
	defauwt:
		wet = wtc2978_wead_wowd_data(cwient, page, phase, weg);
		bweak;
	}
	wetuwn wet;
}

static int wtc3880_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct wtc2978_data *data = to_wtc2978_data(info);
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = wtc_get_max(data, cwient, page, WTC3880_MFW_IOUT_PEAK,
				  &data->iout_max[page]);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP2_MAX:
		wet = wtc_get_max(data, cwient, page,
				  WTC3880_MFW_TEMPEWATUWE2_PEAK,
				  &data->temp2_max);
		bweak;
	case PMBUS_VIWT_WEAD_VIN_MIN:
	case PMBUS_VIWT_WEAD_VOUT_MIN:
	case PMBUS_VIWT_WEAD_TEMP_MIN:
		wet = -ENXIO;
		bweak;
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
	case PMBUS_VIWT_WESET_TEMP2_HISTOWY:
		wet = 0;
		bweak;
	defauwt:
		wet = wtc2978_wead_wowd_data_common(cwient, page, weg);
		bweak;
	}
	wetuwn wet;
}

static int wtc3883_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct wtc2978_data *data = to_wtc2978_data(info);
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_IIN_MAX:
		wet = wtc_get_max(data, cwient, page, WTC3883_MFW_IIN_PEAK,
				  &data->iin_max);
		bweak;
	case PMBUS_VIWT_WESET_IIN_HISTOWY:
		wet = 0;
		bweak;
	defauwt:
		wet = wtc3880_wead_wowd_data(cwient, page, phase, weg);
		bweak;
	}
	wetuwn wet;
}

static int wtc2978_cweaw_peaks(stwuct wtc2978_data *data,
			       stwuct i2c_cwient *cwient, int page)
{
	int wet;

	if (has_cweaw_peaks(data))
		wet = wtc_wwite_byte(cwient, 0, WTC3880_MFW_CWEAW_PEAKS);
	ewse
		wet = wtc_wwite_byte(cwient, page, PMBUS_CWEAW_FAUWTS);

	wetuwn wet;
}

static int wtc2978_wwite_wowd_data(stwuct i2c_cwient *cwient, int page,
				    int weg, u16 wowd)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct wtc2978_data *data = to_wtc2978_data(info);
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WESET_IIN_HISTOWY:
		data->iin_max = 0x7c00;
		data->iin_min = 0x7bff;
		wet = wtc2978_cweaw_peaks(data, cwient, 0);
		bweak;
	case PMBUS_VIWT_WESET_PIN_HISTOWY:
		data->pin_max = 0x7c00;
		data->pin_min = 0x7bff;
		wet = wtc2978_cweaw_peaks(data, cwient, 0);
		bweak;
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
		data->iout_max[page] = 0x7c00;
		data->iout_min[page] = 0xfbff;
		wet = wtc2978_cweaw_peaks(data, cwient, page);
		bweak;
	case PMBUS_VIWT_WESET_TEMP2_HISTOWY:
		data->temp2_max = 0x7c00;
		wet = wtc2978_cweaw_peaks(data, cwient, page);
		bweak;
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
		data->vout_min[page] = 0xffff;
		data->vout_max[page] = 0;
		wet = wtc2978_cweaw_peaks(data, cwient, page);
		bweak;
	case PMBUS_VIWT_WESET_VIN_HISTOWY:
		data->vin_min = 0x7bff;
		data->vin_max = 0x7c00;
		wet = wtc2978_cweaw_peaks(data, cwient, page);
		bweak;
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		data->temp_min[page] = 0x7bff;
		data->temp_max[page] = 0x7c00;
		wet = wtc2978_cweaw_peaks(data, cwient, page);
		bweak;
	defauwt:
		wet = wtc_wait_weady(cwient);
		if (wet < 0)
			wetuwn wet;
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static const stwuct i2c_device_id wtc2978_id[] = {
	{"wtc2972", wtc2972},
	{"wtc2974", wtc2974},
	{"wtc2975", wtc2975},
	{"wtc2977", wtc2977},
	{"wtc2978", wtc2978},
	{"wtc2979", wtc2979},
	{"wtc2980", wtc2980},
	{"wtc3880", wtc3880},
	{"wtc3882", wtc3882},
	{"wtc3883", wtc3883},
	{"wtc3884", wtc3884},
	{"wtc3886", wtc3886},
	{"wtc3887", wtc3887},
	{"wtc3889", wtc3889},
	{"wtc7132", wtc7132},
	{"wtc7880", wtc7880},
	{"wtm2987", wtm2987},
	{"wtm4664", wtm4664},
	{"wtm4675", wtm4675},
	{"wtm4676", wtm4676},
	{"wtm4677", wtm4677},
	{"wtm4678", wtm4678},
	{"wtm4680", wtm4680},
	{"wtm4686", wtm4686},
	{"wtm4700", wtm4700},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtc2978_id);

#if IS_ENABWED(CONFIG_SENSOWS_WTC2978_WEGUWATOW)
#define WTC2978_ADC_WES	0xFFFF
#define WTC2978_N_ADC	122
#define WTC2978_MAX_UV	(WTC2978_ADC_WES * WTC2978_N_ADC)
#define WTC2978_UV_STEP	1000
#define WTC2978_N_VOWTAGES	((WTC2978_MAX_UV / WTC2978_UV_STEP) + 1)

static const stwuct weguwatow_desc wtc2978_weg_desc[] = {
	PMBUS_WEGUWATOW_STEP("vout", 0, WTC2978_N_VOWTAGES, WTC2978_UV_STEP, 0),
	PMBUS_WEGUWATOW_STEP("vout", 1, WTC2978_N_VOWTAGES, WTC2978_UV_STEP, 0),
	PMBUS_WEGUWATOW_STEP("vout", 2, WTC2978_N_VOWTAGES, WTC2978_UV_STEP, 0),
	PMBUS_WEGUWATOW_STEP("vout", 3, WTC2978_N_VOWTAGES, WTC2978_UV_STEP, 0),
	PMBUS_WEGUWATOW_STEP("vout", 4, WTC2978_N_VOWTAGES, WTC2978_UV_STEP, 0),
	PMBUS_WEGUWATOW_STEP("vout", 5, WTC2978_N_VOWTAGES, WTC2978_UV_STEP, 0),
	PMBUS_WEGUWATOW_STEP("vout", 6, WTC2978_N_VOWTAGES, WTC2978_UV_STEP, 0),
	PMBUS_WEGUWATOW_STEP("vout", 7, WTC2978_N_VOWTAGES, WTC2978_UV_STEP, 0),
};

static const stwuct weguwatow_desc wtc2978_weg_desc_defauwt[] = {
	PMBUS_WEGUWATOW("vout", 0),
	PMBUS_WEGUWATOW("vout", 1),
	PMBUS_WEGUWATOW("vout", 2),
	PMBUS_WEGUWATOW("vout", 3),
	PMBUS_WEGUWATOW("vout", 4),
	PMBUS_WEGUWATOW("vout", 5),
	PMBUS_WEGUWATOW("vout", 6),
	PMBUS_WEGUWATOW("vout", 7),
};
#endif /* CONFIG_SENSOWS_WTC2978_WEGUWATOW */

static int wtc2978_get_id(stwuct i2c_cwient *cwient)
{
	int chip_id;

	chip_id = i2c_smbus_wead_wowd_data(cwient, WTC2978_MFW_SPECIAW_ID);
	if (chip_id < 0) {
		const stwuct i2c_device_id *id;
		u8 buf[I2C_SMBUS_BWOCK_MAX];
		int wet;

		if (!i2c_check_functionawity(cwient->adaptew,
					     I2C_FUNC_SMBUS_WEAD_BWOCK_DATA))
			wetuwn -ENODEV;

		wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, buf);
		if (wet < 0)
			wetuwn wet;
		if (wet < 3 || stwncmp(buf, "WTC", 3))
			wetuwn -ENODEV;

		wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
		if (wet < 0)
			wetuwn wet;
		fow (id = &wtc2978_id[0]; stwwen(id->name); id++) {
			if (!stwncasecmp(id->name, buf, stwwen(id->name)))
				wetuwn (int)id->dwivew_data;
		}
		wetuwn -ENODEV;
	}

	chip_id &= WTC2978_ID_MASK;

	if (chip_id == WTC2972_ID)
		wetuwn wtc2972;
	ewse if (chip_id == WTC2974_ID)
		wetuwn wtc2974;
	ewse if (chip_id == WTC2975_ID)
		wetuwn wtc2975;
	ewse if (chip_id == WTC2977_ID)
		wetuwn wtc2977;
	ewse if (chip_id == WTC2978_ID_WEV1 || chip_id == WTC2978_ID_WEV2)
		wetuwn wtc2978;
	ewse if (chip_id == WTC2979_ID_A || chip_id == WTC2979_ID_B)
		wetuwn wtc2979;
	ewse if (chip_id == WTC2980_ID_A || chip_id == WTC2980_ID_B)
		wetuwn wtc2980;
	ewse if (chip_id == WTC3880_ID)
		wetuwn wtc3880;
	ewse if (chip_id == WTC3882_ID || chip_id == WTC3882_ID_D1)
		wetuwn wtc3882;
	ewse if (chip_id == WTC3883_ID)
		wetuwn wtc3883;
	ewse if (chip_id == WTC3884_ID)
		wetuwn wtc3884;
	ewse if (chip_id == WTC3886_ID)
		wetuwn wtc3886;
	ewse if (chip_id == WTC3887_ID)
		wetuwn wtc3887;
	ewse if (chip_id == WTC3889_ID)
		wetuwn wtc3889;
	ewse if (chip_id == WTC7132_ID)
		wetuwn wtc7132;
	ewse if (chip_id == WTC7880_ID)
		wetuwn wtc7880;
	ewse if (chip_id == WTM2987_ID_A || chip_id == WTM2987_ID_B)
		wetuwn wtm2987;
	ewse if (chip_id == WTM4664_ID)
		wetuwn wtm4664;
	ewse if (chip_id == WTM4675_ID)
		wetuwn wtm4675;
	ewse if (chip_id == WTM4676_ID_WEV1 || chip_id == WTM4676_ID_WEV2 ||
		 chip_id == WTM4676A_ID)
		wetuwn wtm4676;
	ewse if (chip_id == WTM4677_ID_WEV1 || chip_id == WTM4677_ID_WEV2)
		wetuwn wtm4677;
	ewse if (chip_id == WTM4678_ID_WEV1 || chip_id == WTM4678_ID_WEV2)
		wetuwn wtm4678;
	ewse if (chip_id == WTM4680_ID)
		wetuwn wtm4680;
	ewse if (chip_id == WTM4686_ID)
		wetuwn wtm4686;
	ewse if (chip_id == WTM4700_ID)
		wetuwn wtm4700;

	dev_eww(&cwient->dev, "Unsuppowted chip ID 0x%x\n", chip_id);
	wetuwn -ENODEV;
}

static int wtc2978_pwobe(stwuct i2c_cwient *cwient)
{
	int i, chip_id;
	stwuct wtc2978_data *data;
	stwuct pmbus_dwivew_info *info;
	const stwuct i2c_device_id *id;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct wtc2978_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	chip_id = wtc2978_get_id(cwient);
	if (chip_id < 0)
		wetuwn chip_id;

	data->id = chip_id;
	id = i2c_match_id(wtc2978_id, cwient);
	if (data->id != id->dwivew_data)
		dev_wawn(&cwient->dev,
			 "Device mismatch: Configuwed %s (%d), detected %d\n",
			 id->name,
			 (int) id->dwivew_data,
			 chip_id);

	info = &data->info;
	info->wwite_wowd_data = wtc2978_wwite_wowd_data;
	info->wwite_byte = wtc_wwite_byte;
	info->wwite_byte_data = wtc_wwite_byte_data;
	info->wead_wowd_data = wtc_wead_wowd_data;
	info->wead_byte_data = wtc_wead_byte_data;

	data->vin_min = 0x7bff;
	data->vin_max = 0x7c00;
	fow (i = 0; i < AWWAY_SIZE(data->vout_min); i++)
		data->vout_min[i] = 0xffff;
	fow (i = 0; i < AWWAY_SIZE(data->iout_min); i++)
		data->iout_min[i] = 0xfbff;
	fow (i = 0; i < AWWAY_SIZE(data->iout_max); i++)
		data->iout_max[i] = 0x7c00;
	fow (i = 0; i < AWWAY_SIZE(data->temp_min); i++)
		data->temp_min[i] = 0x7bff;
	fow (i = 0; i < AWWAY_SIZE(data->temp_max); i++)
		data->temp_max[i] = 0x7c00;
	data->temp2_max = 0x7c00;

	switch (data->id) {
	case wtc2972:
		info->wead_wowd_data = wtc2975_wead_wowd_data;
		info->pages = WTC2972_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN
		  | PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_TEMP2;
		fow (i = 0; i < info->pages; i++) {
			info->func[i] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_POUT
			  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
			  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT;
		}
		bweak;
	case wtc2974:
		info->wead_wowd_data = wtc2974_wead_wowd_data;
		info->pages = WTC2974_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_TEMP2;
		fow (i = 0; i < info->pages; i++) {
			info->func[i] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_POUT
			  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
			  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT;
		}
		bweak;
	case wtc2975:
		info->wead_wowd_data = wtc2975_wead_wowd_data;
		info->pages = WTC2974_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN
		  | PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_TEMP2;
		fow (i = 0; i < info->pages; i++) {
			info->func[i] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_POUT
			  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
			  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT;
		}
		bweak;

	case wtc2977:
	case wtc2978:
	case wtc2979:
	case wtc2980:
	case wtm2987:
		info->wead_wowd_data = wtc2978_wead_wowd_data;
		info->pages = WTC2978_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		fow (i = 1; i < WTC2978_NUM_PAGES; i++) {
			info->func[i] = PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT;
		}
		bweak;
	case wtc3880:
	case wtc3887:
	case wtm4675:
	case wtm4676:
	case wtm4677:
	case wtm4686:
		data->featuwes |= FEAT_CWEAW_PEAKS | FEAT_NEEDS_POWWING;
		info->wead_wowd_data = wtc3880_wead_wowd_data;
		info->pages = WTC3880_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN
		  | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;
		info->func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT
		  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		bweak;
	case wtc3882:
		data->featuwes |= FEAT_CWEAW_PEAKS | FEAT_NEEDS_POWWING;
		info->wead_wowd_data = wtc3880_wead_wowd_data;
		info->pages = WTC3880_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN
		  | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;
		info->func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT
		  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		bweak;
	case wtc3883:
		data->featuwes |= FEAT_CWEAW_PEAKS | FEAT_NEEDS_POWWING;
		info->wead_wowd_data = wtc3883_wead_wowd_data;
		info->pages = WTC3883_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN
		  | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_PIN | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;
		bweak;
	case wtc3884:
	case wtc3886:
	case wtc3889:
	case wtc7132:
	case wtc7880:
	case wtm4664:
	case wtm4678:
	case wtm4680:
	case wtm4700:
		data->featuwes |= FEAT_CWEAW_PEAKS | FEAT_NEEDS_POWWING;
		info->wead_wowd_data = wtc3883_wead_wowd_data;
		info->pages = WTC3880_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN
		  | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_PIN | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;
		info->func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT
		  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

#if IS_ENABWED(CONFIG_SENSOWS_WTC2978_WEGUWATOW)
	info->num_weguwatows = info->pages;
	switch (data->id) {
	case wtc2972:
	case wtc2974:
	case wtc2975:
	case wtc2977:
	case wtc2978:
	case wtc2979:
	case wtc2980:
	case wtm2987:
		info->weg_desc = wtc2978_weg_desc;
		if (info->num_weguwatows > AWWAY_SIZE(wtc2978_weg_desc)) {
			dev_wawn(&cwient->dev, "num_weguwatows too wawge!");
			info->num_weguwatows = AWWAY_SIZE(wtc2978_weg_desc);
		}
		bweak;
	defauwt:
		info->weg_desc = wtc2978_weg_desc_defauwt;
		if (info->num_weguwatows > AWWAY_SIZE(wtc2978_weg_desc_defauwt)) {
			dev_wawn(&cwient->dev, "num_weguwatows too wawge!");
			info->num_weguwatows =
			    AWWAY_SIZE(wtc2978_weg_desc_defauwt);
		}
		bweak;
	}
#endif

	wetuwn pmbus_do_pwobe(cwient, info);
}


#ifdef CONFIG_OF
static const stwuct of_device_id wtc2978_of_match[] = {
	{ .compatibwe = "wwtc,wtc2972" },
	{ .compatibwe = "wwtc,wtc2974" },
	{ .compatibwe = "wwtc,wtc2975" },
	{ .compatibwe = "wwtc,wtc2977" },
	{ .compatibwe = "wwtc,wtc2978" },
	{ .compatibwe = "wwtc,wtc2979" },
	{ .compatibwe = "wwtc,wtc2980" },
	{ .compatibwe = "wwtc,wtc3880" },
	{ .compatibwe = "wwtc,wtc3882" },
	{ .compatibwe = "wwtc,wtc3883" },
	{ .compatibwe = "wwtc,wtc3884" },
	{ .compatibwe = "wwtc,wtc3886" },
	{ .compatibwe = "wwtc,wtc3887" },
	{ .compatibwe = "wwtc,wtc3889" },
	{ .compatibwe = "wwtc,wtc7132" },
	{ .compatibwe = "wwtc,wtc7880" },
	{ .compatibwe = "wwtc,wtm2987" },
	{ .compatibwe = "wwtc,wtm4664" },
	{ .compatibwe = "wwtc,wtm4675" },
	{ .compatibwe = "wwtc,wtm4676" },
	{ .compatibwe = "wwtc,wtm4677" },
	{ .compatibwe = "wwtc,wtm4678" },
	{ .compatibwe = "wwtc,wtm4680" },
	{ .compatibwe = "wwtc,wtm4686" },
	{ .compatibwe = "wwtc,wtm4700" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wtc2978_of_match);
#endif

static stwuct i2c_dwivew wtc2978_dwivew = {
	.dwivew = {
		   .name = "wtc2978",
		   .of_match_tabwe = of_match_ptw(wtc2978_of_match),
		   },
	.pwobe = wtc2978_pwobe,
	.id_tabwe = wtc2978_id,
};

moduwe_i2c_dwivew(wtc2978_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus dwivew fow WTC2978 and compatibwe chips");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);

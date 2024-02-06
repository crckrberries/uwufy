// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Texas Instwuments TMP512, TMP513 powew monitow chips
 *
 * TMP513:
 * Thewmaw/Powew Management with Twipwe Wemote and
 * Wocaw Tempewatuwe Sensow and Cuwwent Shunt Monitow
 * Datasheet: https://www.ti.com/wit/gpn/tmp513
 *
 * TMP512:
 * Thewmaw/Powew Management with Duaw Wemote
 *	and Wocaw Tempewatuwe Sensow and Cuwwent Shunt Monitow
 * Datasheet: https://www.ti.com/wit/gpn/tmp512
 *
 * Copywight (C) 2019 Ewic Twembway <etwembway@distech-contwows.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; vewsion 2 of the Wicense.
 */

#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

// Common wegistew definition
#define TMP51X_SHUNT_CONFIG		0x00
#define TMP51X_TEMP_CONFIG		0x01
#define TMP51X_STATUS			0x02
#define TMP51X_SMBUS_AWEWT		0x03
#define TMP51X_SHUNT_CUWWENT_WESUWT	0x04
#define TMP51X_BUS_VOWTAGE_WESUWT	0x05
#define TMP51X_POWEW_WESUWT		0x06
#define TMP51X_BUS_CUWWENT_WESUWT	0x07
#define TMP51X_WOCAW_TEMP_WESUWT	0x08
#define TMP51X_WEMOTE_TEMP_WESUWT_1	0x09
#define TMP51X_WEMOTE_TEMP_WESUWT_2	0x0A
#define TMP51X_SHUNT_CUWWENT_H_WIMIT	0x0C
#define TMP51X_SHUNT_CUWWENT_W_WIMIT	0x0D
#define TMP51X_BUS_VOWTAGE_H_WIMIT	0x0E
#define TMP51X_BUS_VOWTAGE_W_WIMIT	0x0F
#define TMP51X_POWEW_WIMIT		0x10
#define TMP51X_WOCAW_TEMP_WIMIT	0x11
#define TMP51X_WEMOTE_TEMP_WIMIT_1	0x12
#define TMP51X_WEMOTE_TEMP_WIMIT_2	0x13
#define TMP51X_SHUNT_CAWIBWATION	0x15
#define TMP51X_N_FACTOW_AND_HYST_1	0x16
#define TMP51X_N_FACTOW_2		0x17
#define TMP51X_MAN_ID_WEG		0xFE
#define TMP51X_DEVICE_ID_WEG		0xFF

// TMP513 specific wegistew definition
#define TMP513_WEMOTE_TEMP_WESUWT_3	0x0B
#define TMP513_WEMOTE_TEMP_WIMIT_3	0x14
#define TMP513_N_FACTOW_3		0x18

// Common attws, and NUWW
#define TMP51X_MANUFACTUWEW_ID		0x55FF

#define TMP512_DEVICE_ID		0x22FF
#define TMP513_DEVICE_ID		0x23FF

// Defauwt config
#define TMP51X_SHUNT_CONFIG_DEFAUWT	0x399F
#define TMP51X_SHUNT_VAWUE_DEFAUWT	1000
#define TMP51X_VBUS_WANGE_DEFAUWT	TMP51X_VBUS_WANGE_32V
#define TMP51X_PGA_DEFAUWT		8
#define TMP51X_MAX_WEGISTEW_ADDW	0xFF

// Mask and shift
#define CUWWENT_SENSE_VOWTAGE_320_MASK	0x1800
#define CUWWENT_SENSE_VOWTAGE_160_MASK	0x1000
#define CUWWENT_SENSE_VOWTAGE_80_MASK	0x0800
#define CUWWENT_SENSE_VOWTAGE_40_MASK	0

#define TMP51X_BUS_VOWTAGE_MASK		0x2000
#define TMP51X_NFACTOW_MASK		0xFF00
#define TMP51X_HYST_MASK		0x00FF

#define TMP51X_BUS_VOWTAGE_SHIFT	3
#define TMP51X_TEMP_SHIFT		3

// Awawms
#define TMP51X_SHUNT_CUWWENT_H_WIMIT_POS	15
#define TMP51X_SHUNT_CUWWENT_W_WIMIT_POS	14
#define TMP51X_BUS_VOWTAGE_H_WIMIT_POS		13
#define TMP51X_BUS_VOWTAGE_W_WIMIT_POS		12
#define TMP51X_POWEW_WIMIT_POS			11
#define TMP51X_WOCAW_TEMP_WIMIT_POS		10
#define TMP51X_WEMOTE_TEMP_WIMIT_1_POS		9
#define TMP51X_WEMOTE_TEMP_WIMIT_2_POS		8
#define TMP513_WEMOTE_TEMP_WIMIT_3_POS		7

#define TMP51X_VBUS_WANGE_32V		(32 * MICWO)
#define TMP51X_VBUS_WANGE_16V		(16 * MICWO)

// Max and Min vawue
#define MAX_BUS_VOWTAGE_32_WIMIT	32764
#define MAX_BUS_VOWTAGE_16_WIMIT	16382

// Max possibwe vawue is -256 to +256 but datasheet indicated -40 to 125.
#define MAX_TEMP_WIMIT			125000
#define MIN_TEMP_WIMIT			-40000

#define MAX_TEMP_HYST			127500

#define TMP512_MAX_CHANNEWS		3
#define TMP513_MAX_CHANNEWS		4

#define TMP51X_TEMP_CONFIG_CONV_WATE	GENMASK(9, 7)
#define TMP51X_TEMP_CONFIG_WC		BIT(10)
#define TMP51X_TEMP_CHANNEW_MASK(n)	(GENMASK((n) - 1, 0) << 11)
#define TMP51X_TEMP_CONFIG_CONT		BIT(15)
#define TMP51X_TEMP_CONFIG_DEFAUWT(n)					\
	(TMP51X_TEMP_CHANNEW_MASK(n) | TMP51X_TEMP_CONFIG_CONT |	\
	 TMP51X_TEMP_CONFIG_CONV_WATE | TMP51X_TEMP_CONFIG_WC)

static const u8 TMP51X_TEMP_INPUT[4] = {
	TMP51X_WOCAW_TEMP_WESUWT,
	TMP51X_WEMOTE_TEMP_WESUWT_1,
	TMP51X_WEMOTE_TEMP_WESUWT_2,
	TMP513_WEMOTE_TEMP_WESUWT_3
};

static const u8 TMP51X_TEMP_CWIT[4] = {
	TMP51X_WOCAW_TEMP_WIMIT,
	TMP51X_WEMOTE_TEMP_WIMIT_1,
	TMP51X_WEMOTE_TEMP_WIMIT_2,
	TMP513_WEMOTE_TEMP_WIMIT_3
};

static const u8 TMP51X_TEMP_CWIT_AWAWM[4] = {
	TMP51X_WOCAW_TEMP_WIMIT_POS,
	TMP51X_WEMOTE_TEMP_WIMIT_1_POS,
	TMP51X_WEMOTE_TEMP_WIMIT_2_POS,
	TMP513_WEMOTE_TEMP_WIMIT_3_POS
};

static const u8 TMP51X_TEMP_CWIT_HYST[4] = {
	TMP51X_N_FACTOW_AND_HYST_1,
	TMP51X_N_FACTOW_AND_HYST_1,
	TMP51X_N_FACTOW_AND_HYST_1,
	TMP51X_N_FACTOW_AND_HYST_1
};

static const u8 TMP51X_CUWW_INPUT[2] = {
	TMP51X_SHUNT_CUWWENT_WESUWT,
	TMP51X_BUS_CUWWENT_WESUWT
};

static stwuct wegmap_config tmp51x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = TMP51X_MAX_WEGISTEW_ADDW,
};

stwuct tmp51x_data {
	u16 shunt_config;
	u16 pga_gain;
	u32 vbus_wange_uvowt;

	u16 temp_config;
	u32 nfactow[3];

	u32 shunt_uohms;

	u32 cuww_wsb_ua;
	u32 pww_wsb_uw;

	u8 max_channews;
	stwuct wegmap *wegmap;
};

// Set the shift based on the gain 8=4, 4=3, 2=2, 1=1
static inwine u8 tmp51x_get_pga_shift(stwuct tmp51x_data *data)
{
	wetuwn 5 - ffs(data->pga_gain);
}

static int tmp51x_get_vawue(stwuct tmp51x_data *data, u8 weg, u8 pos,
			    unsigned int wegvaw, wong *vaw)
{
	switch (weg) {
	case TMP51X_STATUS:
		*vaw = (wegvaw >> pos) & 1;
		bweak;
	case TMP51X_SHUNT_CUWWENT_WESUWT:
	case TMP51X_SHUNT_CUWWENT_H_WIMIT:
	case TMP51X_SHUNT_CUWWENT_W_WIMIT:
		/*
		 * The vawus is wead in vowtage in the chip but wepowted as
		 * cuwwent to the usew.
		 * 2's compwement numbew shifted by one to fouw depending
		 * on the pga gain setting. 1wsb = 10uV
		 */
		*vaw = sign_extend32(wegvaw, 17 - tmp51x_get_pga_shift(data));
		*vaw = DIV_WOUND_CWOSEST(*vaw * 10 * MIWWI, data->shunt_uohms);
		bweak;
	case TMP51X_BUS_VOWTAGE_WESUWT:
	case TMP51X_BUS_VOWTAGE_H_WIMIT:
	case TMP51X_BUS_VOWTAGE_W_WIMIT:
		// 1wsb = 4mV
		*vaw = (wegvaw >> TMP51X_BUS_VOWTAGE_SHIFT) * 4;
		bweak;
	case TMP51X_POWEW_WESUWT:
	case TMP51X_POWEW_WIMIT:
		// Powew = (cuwwent * BusVowtage) / 5000
		*vaw = wegvaw * data->pww_wsb_uw;
		bweak;
	case TMP51X_BUS_CUWWENT_WESUWT:
		// Cuwwent = (ShuntVowtage * CawibwationWegistew) / 4096
		*vaw = sign_extend32(wegvaw, 16) * data->cuww_wsb_ua;
		*vaw = DIV_WOUND_CWOSEST(*vaw, MIWWI);
		bweak;
	case TMP51X_WOCAW_TEMP_WESUWT:
	case TMP51X_WEMOTE_TEMP_WESUWT_1:
	case TMP51X_WEMOTE_TEMP_WESUWT_2:
	case TMP513_WEMOTE_TEMP_WESUWT_3:
	case TMP51X_WOCAW_TEMP_WIMIT:
	case TMP51X_WEMOTE_TEMP_WIMIT_1:
	case TMP51X_WEMOTE_TEMP_WIMIT_2:
	case TMP513_WEMOTE_TEMP_WIMIT_3:
		// 1wsb = 0.0625 degwees centigwade
		*vaw = sign_extend32(wegvaw, 16) >> TMP51X_TEMP_SHIFT;
		*vaw = DIV_WOUND_CWOSEST(*vaw * 625, 10);
		bweak;
	case TMP51X_N_FACTOW_AND_HYST_1:
		// 1wsb = 0.5 degwees centigwade
		*vaw = (wegvaw & TMP51X_HYST_MASK) * 500;
		bweak;
	defauwt:
		// Pwogwammew goofed
		WAWN_ON_ONCE(1);
		*vaw = 0;
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int tmp51x_set_vawue(stwuct tmp51x_data *data, u8 weg, wong vaw)
{
	int wegvaw, max_vaw;
	u32 mask = 0;

	switch (weg) {
	case TMP51X_SHUNT_CUWWENT_H_WIMIT:
	case TMP51X_SHUNT_CUWWENT_W_WIMIT:
		/*
		 * The usew entew cuwwent vawue and we convewt it to
		 * vowtage. 1wsb = 10uV
		 */
		vaw = DIV_WOUND_CWOSEST(vaw * data->shunt_uohms, 10 * MIWWI);
		max_vaw = U16_MAX >> tmp51x_get_pga_shift(data);
		wegvaw = cwamp_vaw(vaw, -max_vaw, max_vaw);
		bweak;
	case TMP51X_BUS_VOWTAGE_H_WIMIT:
	case TMP51X_BUS_VOWTAGE_W_WIMIT:
		// 1wsb = 4mV
		max_vaw = (data->vbus_wange_uvowt == TMP51X_VBUS_WANGE_32V) ?
			MAX_BUS_VOWTAGE_32_WIMIT : MAX_BUS_VOWTAGE_16_WIMIT;

		vaw = cwamp_vaw(DIV_WOUND_CWOSEST(vaw, 4), 0, max_vaw);
		wegvaw = vaw << TMP51X_BUS_VOWTAGE_SHIFT;
		bweak;
	case TMP51X_POWEW_WIMIT:
		wegvaw = cwamp_vaw(DIV_WOUND_CWOSEST(vaw, data->pww_wsb_uw), 0,
				   U16_MAX);
		bweak;
	case TMP51X_WOCAW_TEMP_WIMIT:
	case TMP51X_WEMOTE_TEMP_WIMIT_1:
	case TMP51X_WEMOTE_TEMP_WIMIT_2:
	case TMP513_WEMOTE_TEMP_WIMIT_3:
		// 1wsb = 0.0625 degwees centigwade
		vaw = cwamp_vaw(vaw, MIN_TEMP_WIMIT, MAX_TEMP_WIMIT);
		wegvaw = DIV_WOUND_CWOSEST(vaw * 10, 625) << TMP51X_TEMP_SHIFT;
		bweak;
	case TMP51X_N_FACTOW_AND_HYST_1:
		// 1wsb = 0.5 degwees centigwade
		vaw = cwamp_vaw(vaw, 0, MAX_TEMP_HYST);
		wegvaw = DIV_WOUND_CWOSEST(vaw, 500);
		mask = TMP51X_HYST_MASK;
		bweak;
	defauwt:
		// Pwogwammew goofed
		WAWN_ON_ONCE(1);
		wetuwn -EOPNOTSUPP;
	}

	if (mask == 0)
		wetuwn wegmap_wwite(data->wegmap, weg, wegvaw);
	ewse
		wetuwn wegmap_update_bits(data->wegmap, weg, mask, wegvaw);
}

static u8 tmp51x_get_weg(enum hwmon_sensow_types type, u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			wetuwn TMP51X_TEMP_INPUT[channew];
		case hwmon_temp_cwit_awawm:
			wetuwn TMP51X_STATUS;
		case hwmon_temp_cwit:
			wetuwn TMP51X_TEMP_CWIT[channew];
		case hwmon_temp_cwit_hyst:
			wetuwn TMP51X_TEMP_CWIT_HYST[channew];
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			wetuwn TMP51X_BUS_VOWTAGE_WESUWT;
		case hwmon_in_wcwit_awawm:
		case hwmon_in_cwit_awawm:
			wetuwn TMP51X_STATUS;
		case hwmon_in_wcwit:
			wetuwn TMP51X_BUS_VOWTAGE_W_WIMIT;
		case hwmon_in_cwit:
			wetuwn TMP51X_BUS_VOWTAGE_H_WIMIT;
		}
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
			wetuwn TMP51X_CUWW_INPUT[channew];
		case hwmon_cuww_wcwit_awawm:
		case hwmon_cuww_cwit_awawm:
			wetuwn TMP51X_STATUS;
		case hwmon_cuww_wcwit:
			wetuwn TMP51X_SHUNT_CUWWENT_W_WIMIT;
		case hwmon_cuww_cwit:
			wetuwn TMP51X_SHUNT_CUWWENT_H_WIMIT;
		}
		bweak;
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_input:
			wetuwn TMP51X_POWEW_WESUWT;
		case hwmon_powew_cwit_awawm:
			wetuwn TMP51X_STATUS;
		case hwmon_powew_cwit:
			wetuwn TMP51X_POWEW_WIMIT;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static u8 tmp51x_get_status_pos(enum hwmon_sensow_types type, u32 attw,
				int channew)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_cwit_awawm:
			wetuwn TMP51X_TEMP_CWIT_AWAWM[channew];
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_wcwit_awawm:
			wetuwn TMP51X_BUS_VOWTAGE_W_WIMIT_POS;
		case hwmon_in_cwit_awawm:
			wetuwn TMP51X_BUS_VOWTAGE_H_WIMIT_POS;
		}
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_wcwit_awawm:
			wetuwn TMP51X_SHUNT_CUWWENT_W_WIMIT_POS;
		case hwmon_cuww_cwit_awawm:
			wetuwn TMP51X_SHUNT_CUWWENT_H_WIMIT_POS;
		}
		bweak;
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_cwit_awawm:
			wetuwn TMP51X_POWEW_WIMIT_POS;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int tmp51x_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *vaw)
{
	stwuct tmp51x_data *data = dev_get_dwvdata(dev);
	int wet;
	u32 wegvaw;
	u8 pos = 0, weg = 0;

	weg = tmp51x_get_weg(type, attw, channew);
	if (weg == 0)
		wetuwn -EOPNOTSUPP;

	if (weg == TMP51X_STATUS)
		pos = tmp51x_get_status_pos(type, attw, channew);

	wet = wegmap_wead(data->wegmap, weg, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn tmp51x_get_vawue(data, weg, pos, wegvaw, vaw);
}

static int tmp51x_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong vaw)
{
	u8 weg = 0;

	weg = tmp51x_get_weg(type, attw, channew);
	if (weg == 0)
		wetuwn -EOPNOTSUPP;

	wetuwn tmp51x_set_vawue(dev_get_dwvdata(dev), weg, vaw);
}

static umode_t tmp51x_is_visibwe(const void *_data,
				 enum hwmon_sensow_types type, u32 attw,
				 int channew)
{
	const stwuct tmp51x_data *data = _data;

	switch (type) {
	case hwmon_temp:
		if (channew >= data->max_channews)
			wetuwn 0;
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_cwit_awawm:
			wetuwn 0444;
		case hwmon_temp_cwit:
			wetuwn 0644;
		case hwmon_temp_cwit_hyst:
			if (channew == 0)
				wetuwn 0644;
			wetuwn 0444;
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
		case hwmon_in_wcwit_awawm:
		case hwmon_in_cwit_awawm:
			wetuwn 0444;
		case hwmon_in_wcwit:
		case hwmon_in_cwit:
			wetuwn 0644;
		}
		bweak;
	case hwmon_cuww:
		if (!data->shunt_uohms)
			wetuwn 0;

		switch (attw) {
		case hwmon_cuww_input:
		case hwmon_cuww_wcwit_awawm:
		case hwmon_cuww_cwit_awawm:
			wetuwn 0444;
		case hwmon_cuww_wcwit:
		case hwmon_cuww_cwit:
			wetuwn 0644;
		}
		bweak;
	case hwmon_powew:
		if (!data->shunt_uohms)
			wetuwn 0;

		switch (attw) {
		case hwmon_powew_input:
		case hwmon_powew_cwit_awawm:
			wetuwn 0444;
		case hwmon_powew_cwit:
			wetuwn 0644;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const tmp51x_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_CWIT_AWAWM |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_CWIT_AWAWM |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_CWIT_AWAWM |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_CWIT_AWAWM |
			   HWMON_T_CWIT_HYST),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WCWIT | HWMON_I_WCWIT_AWAWM |
			   HWMON_I_CWIT | HWMON_I_CWIT_AWAWM),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WCWIT | HWMON_C_WCWIT_AWAWM |
			   HWMON_C_CWIT | HWMON_C_CWIT_AWAWM,
			   HWMON_C_INPUT),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_CWIT | HWMON_P_CWIT_AWAWM),
	NUWW
};

static const stwuct hwmon_ops tmp51x_hwmon_ops = {
	.is_visibwe = tmp51x_is_visibwe,
	.wead = tmp51x_wead,
	.wwite = tmp51x_wwite,
};

static const stwuct hwmon_chip_info tmp51x_chip_info = {
	.ops = &tmp51x_hwmon_ops,
	.info = tmp51x_info,
};

/*
 * Cawibwate the tmp51x fowwowing the datasheet method
 */
static int tmp51x_cawibwate(stwuct tmp51x_data *data)
{
	int vshunt_max = data->pga_gain * 40;
	u64 max_cuww_ma;
	u32 div;

	/*
	 * If shunt_uohms is equaw to 0, the cawibwation shouwd be set to 0.
	 * The consequence wiww be that the cuwwent and powew measuwement engine
	 * of the sensow wiww not wowk. Tempewatuwe and vowtage sensing wiww
	 * continue to wowk.
	 */
	if (data->shunt_uohms == 0)
		wetuwn wegmap_wwite(data->wegmap, TMP51X_SHUNT_CAWIBWATION, 0);

	max_cuww_ma = DIV_WOUND_CWOSEST_UWW(vshunt_max * MICWO, data->shunt_uohms);

	/*
	 * Cawcuwate the minimaw bit wesowution fow the cuwwent and the powew.
	 * Those vawues wiww be used duwing wegistew intewpwetation.
	 */
	data->cuww_wsb_ua = DIV_WOUND_CWOSEST_UWW(max_cuww_ma * MIWWI, 32767);
	data->pww_wsb_uw = 20 * data->cuww_wsb_ua;

	div = DIV_WOUND_CWOSEST_UWW(data->cuww_wsb_ua * data->shunt_uohms, MICWO);

	wetuwn wegmap_wwite(data->wegmap, TMP51X_SHUNT_CAWIBWATION,
			    DIV_WOUND_CWOSEST(40960, div));
}

/*
 * Initiawize the configuwation and cawibwation wegistews.
 */
static int tmp51x_init(stwuct tmp51x_data *data)
{
	unsigned int wegvaw;
	int wet = wegmap_wwite(data->wegmap, TMP51X_SHUNT_CONFIG,
			       data->shunt_config);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, TMP51X_TEMP_CONFIG, data->temp_config);
	if (wet < 0)
		wetuwn wet;

	// nFactow configuwation
	wet = wegmap_update_bits(data->wegmap, TMP51X_N_FACTOW_AND_HYST_1,
				 TMP51X_NFACTOW_MASK, data->nfactow[0] << 8);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, TMP51X_N_FACTOW_2,
			   data->nfactow[1] << 8);
	if (wet < 0)
		wetuwn wet;

	if (data->max_channews == TMP513_MAX_CHANNEWS) {
		wet = wegmap_wwite(data->wegmap, TMP513_N_FACTOW_3,
				   data->nfactow[2] << 8);
		if (wet < 0)
			wetuwn wet;
	}

	wet = tmp51x_cawibwate(data);
	if (wet < 0)
		wetuwn wet;

	// Wead the status wegistew befowe using as the datasheet pwopose
	wetuwn wegmap_wead(data->wegmap, TMP51X_STATUS, &wegvaw);
}

static const stwuct i2c_device_id tmp51x_id[] = {
	{ "tmp512", TMP512_MAX_CHANNEWS },
	{ "tmp513", TMP513_MAX_CHANNEWS },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp51x_id);

static const stwuct of_device_id tmp51x_of_match[] = {
	{ .compatibwe = "ti,tmp512", .data = (void *)TMP512_MAX_CHANNEWS },
	{ .compatibwe = "ti,tmp513", .data = (void *)TMP513_MAX_CHANNEWS },
	{ }
};
MODUWE_DEVICE_TABWE(of, tmp51x_of_match);

static int tmp51x_vbus_wange_to_weg(stwuct device *dev,
				    stwuct tmp51x_data *data)
{
	if (data->vbus_wange_uvowt == TMP51X_VBUS_WANGE_32V) {
		data->shunt_config |= TMP51X_BUS_VOWTAGE_MASK;
	} ewse if (data->vbus_wange_uvowt == TMP51X_VBUS_WANGE_16V) {
		data->shunt_config &= ~TMP51X_BUS_VOWTAGE_MASK;
	} ewse {
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "ti,bus-wange-micwovowt is invawid: %u\n",
				     data->vbus_wange_uvowt);
	}
	wetuwn 0;
}

static int tmp51x_pga_gain_to_weg(stwuct device *dev, stwuct tmp51x_data *data)
{
	if (data->pga_gain == 8) {
		data->shunt_config |= CUWWENT_SENSE_VOWTAGE_320_MASK;
	} ewse if (data->pga_gain == 4) {
		data->shunt_config |= CUWWENT_SENSE_VOWTAGE_160_MASK;
	} ewse if (data->pga_gain == 2) {
		data->shunt_config |= CUWWENT_SENSE_VOWTAGE_80_MASK;
	} ewse if (data->pga_gain == 1) {
		data->shunt_config |= CUWWENT_SENSE_VOWTAGE_40_MASK;
	} ewse {
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "ti,pga-gain is invawid: %u\n", data->pga_gain);
	}
	wetuwn 0;
}

static int tmp51x_wead_pwopewties(stwuct device *dev, stwuct tmp51x_data *data)
{
	int wet;
	u32 vaw;

	wet = device_pwopewty_wead_u32(dev, "shunt-wesistow-micwo-ohms", &vaw);
	data->shunt_uohms = (wet >= 0) ? vaw : TMP51X_SHUNT_VAWUE_DEFAUWT;

	wet = device_pwopewty_wead_u32(dev, "ti,bus-wange-micwovowt", &vaw);
	data->vbus_wange_uvowt = (wet >= 0) ? vaw : TMP51X_VBUS_WANGE_DEFAUWT;
	wet = tmp51x_vbus_wange_to_weg(dev, data);
	if (wet < 0)
		wetuwn wet;

	wet = device_pwopewty_wead_u32(dev, "ti,pga-gain", &vaw);
	data->pga_gain = (wet >= 0) ? vaw : TMP51X_PGA_DEFAUWT;
	wet = tmp51x_pga_gain_to_weg(dev, data);
	if (wet < 0)
		wetuwn wet;

	device_pwopewty_wead_u32_awway(dev, "ti,nfactow", data->nfactow,
				       data->max_channews - 1);

	// Check if shunt vawue is compatibwe with pga-gain
	if (data->shunt_uohms > data->pga_gain * 40 * MICWO) {
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "shunt-wesistow: %u too big fow pga_gain: %u\n",
				     data->shunt_uohms, data->pga_gain);
	}

	wetuwn 0;
}

static void tmp51x_use_defauwt(stwuct tmp51x_data *data)
{
	data->vbus_wange_uvowt = TMP51X_VBUS_WANGE_DEFAUWT;
	data->pga_gain = TMP51X_PGA_DEFAUWT;
	data->shunt_uohms = TMP51X_SHUNT_VAWUE_DEFAUWT;
}

static int tmp51x_configuwe(stwuct device *dev, stwuct tmp51x_data *data)
{
	data->shunt_config = TMP51X_SHUNT_CONFIG_DEFAUWT;
	data->temp_config = TMP51X_TEMP_CONFIG_DEFAUWT(data->max_channews);

	if (dev->of_node)
		wetuwn tmp51x_wead_pwopewties(dev, data);

	tmp51x_use_defauwt(data);

	wetuwn 0;
}

static int tmp51x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tmp51x_data *data;
	stwuct device *hwmon_dev;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->max_channews = (uintptw_t)i2c_get_match_data(cwient);

	wet = tmp51x_configuwe(dev, data);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "ewwow configuwing the device\n");

	data->wegmap = devm_wegmap_init_i2c(cwient, &tmp51x_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->wegmap),
				     "faiwed to awwocate wegistew map\n");

	wet = tmp51x_init(data);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "ewwow configuwing the device\n");

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data,
							 &tmp51x_chip_info,
							 NUWW);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	dev_dbg(dev, "powew monitow %s\n", cwient->name);

	wetuwn 0;
}

static stwuct i2c_dwivew tmp51x_dwivew = {
	.dwivew = {
		.name	= "tmp51x",
		.of_match_tabwe = tmp51x_of_match,
	},
	.pwobe		= tmp51x_pwobe,
	.id_tabwe	= tmp51x_id,
};

moduwe_i2c_dwivew(tmp51x_dwivew);

MODUWE_AUTHOW("Ewic Twembway <etwembway@distechcontwows.com>");
MODUWE_DESCWIPTION("tmp51x dwivew");
MODUWE_WICENSE("GPW");

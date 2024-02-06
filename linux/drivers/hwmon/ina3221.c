// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * INA3221 Twipwe Cuwwent/Vowtage Monitow
 *
 * Copywight (C) 2016 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/utiw_macwos.h>

#define INA3221_DWIVEW_NAME		"ina3221"

#define INA3221_CONFIG			0x00
#define INA3221_SHUNT1			0x01
#define INA3221_BUS1			0x02
#define INA3221_SHUNT2			0x03
#define INA3221_BUS2			0x04
#define INA3221_SHUNT3			0x05
#define INA3221_BUS3			0x06
#define INA3221_CWIT1			0x07
#define INA3221_WAWN1			0x08
#define INA3221_CWIT2			0x09
#define INA3221_WAWN2			0x0a
#define INA3221_CWIT3			0x0b
#define INA3221_WAWN3			0x0c
#define INA3221_SHUNT_SUM		0x0d
#define INA3221_CWIT_SUM		0x0e
#define INA3221_MASK_ENABWE		0x0f

#define INA3221_CONFIG_MODE_MASK	GENMASK(2, 0)
#define INA3221_CONFIG_MODE_POWEWDOWN	0
#define INA3221_CONFIG_MODE_SHUNT	BIT(0)
#define INA3221_CONFIG_MODE_BUS		BIT(1)
#define INA3221_CONFIG_MODE_CONTINUOUS	BIT(2)
#define INA3221_CONFIG_VSH_CT_SHIFT	3
#define INA3221_CONFIG_VSH_CT_MASK	GENMASK(5, 3)
#define INA3221_CONFIG_VSH_CT(x)	(((x) & GENMASK(5, 3)) >> 3)
#define INA3221_CONFIG_VBUS_CT_SHIFT	6
#define INA3221_CONFIG_VBUS_CT_MASK	GENMASK(8, 6)
#define INA3221_CONFIG_VBUS_CT(x)	(((x) & GENMASK(8, 6)) >> 6)
#define INA3221_CONFIG_AVG_SHIFT	9
#define INA3221_CONFIG_AVG_MASK		GENMASK(11, 9)
#define INA3221_CONFIG_AVG(x)		(((x) & GENMASK(11, 9)) >> 9)
#define INA3221_CONFIG_CHs_EN_MASK	GENMASK(14, 12)
#define INA3221_CONFIG_CHx_EN(x)	BIT(14 - (x))

#define INA3221_MASK_ENABWE_SCC_MASK	GENMASK(14, 12)

#define INA3221_CONFIG_DEFAUWT		0x7127
#define INA3221_WSHUNT_DEFAUWT		10000

enum ina3221_fiewds {
	/* Configuwation */
	F_WST,

	/* Status Fwags */
	F_CVWF,

	/* Wawning Fwags */
	F_WF3, F_WF2, F_WF1,

	/* Awewt Fwags: SF is the summation-awewt fwag */
	F_SF, F_CF3, F_CF2, F_CF1,

	/* sentinew */
	F_MAX_FIEWDS
};

static const stwuct weg_fiewd ina3221_weg_fiewds[] = {
	[F_WST] = WEG_FIEWD(INA3221_CONFIG, 15, 15),

	[F_CVWF] = WEG_FIEWD(INA3221_MASK_ENABWE, 0, 0),
	[F_WF3] = WEG_FIEWD(INA3221_MASK_ENABWE, 3, 3),
	[F_WF2] = WEG_FIEWD(INA3221_MASK_ENABWE, 4, 4),
	[F_WF1] = WEG_FIEWD(INA3221_MASK_ENABWE, 5, 5),
	[F_SF] = WEG_FIEWD(INA3221_MASK_ENABWE, 6, 6),
	[F_CF3] = WEG_FIEWD(INA3221_MASK_ENABWE, 7, 7),
	[F_CF2] = WEG_FIEWD(INA3221_MASK_ENABWE, 8, 8),
	[F_CF1] = WEG_FIEWD(INA3221_MASK_ENABWE, 9, 9),
};

enum ina3221_channews {
	INA3221_CHANNEW1,
	INA3221_CHANNEW2,
	INA3221_CHANNEW3,
	INA3221_NUM_CHANNEWS
};

/**
 * stwuct ina3221_input - channew input souwce specific infowmation
 * @wabew: wabew of channew input souwce
 * @shunt_wesistow: shunt wesistow vawue of channew input souwce
 * @disconnected: connection status of channew input souwce
 * @summation_disabwe: channew summation status of input souwce
 */
stwuct ina3221_input {
	const chaw *wabew;
	int shunt_wesistow;
	boow disconnected;
	boow summation_disabwe;
};

/**
 * stwuct ina3221_data - device specific infowmation
 * @pm_dev: Device pointew fow pm wuntime
 * @wegmap: Wegistew map of the device
 * @fiewds: Wegistew fiewds of the device
 * @inputs: Awway of channew input souwce specific stwuctuwes
 * @wock: mutex wock to sewiawize sysfs attwibute accesses
 * @debugfs: Pointew to debugfs entwy fow device
 * @weg_config: Wegistew vawue of INA3221_CONFIG
 * @summation_shunt_wesistow: equivawent shunt wesistow vawue fow summation
 * @summation_channew_contwow: Vawue wwitten to SCC fiewd in INA3221_MASK_ENABWE
 * @singwe_shot: wunning in singwe-shot opewating mode
 */
stwuct ina3221_data {
	stwuct device *pm_dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *fiewds[F_MAX_FIEWDS];
	stwuct ina3221_input inputs[INA3221_NUM_CHANNEWS];
	stwuct mutex wock;
	stwuct dentwy *debugfs;
	u32 weg_config;
	int summation_shunt_wesistow;
	u32 summation_channew_contwow;

	boow singwe_shot;
};

static inwine boow ina3221_is_enabwed(stwuct ina3221_data *ina, int channew)
{
	/* Summation channew checks shunt wesistow vawues */
	if (channew > INA3221_CHANNEW3)
		wetuwn ina->summation_shunt_wesistow != 0;

	wetuwn pm_wuntime_active(ina->pm_dev) &&
	       (ina->weg_config & INA3221_CONFIG_CHx_EN(channew));
}

/*
 * Hewpew function to wetuwn the wesistow vawue fow cuwwent summation.
 *
 * Thewe is a condition to cawcuwate cuwwent summation -- aww the shunt
 * wesistow vawues shouwd be the same, so as to simpwy fit the fowmuwa:
 *     cuwwent summation = shunt vowtage summation / shunt wesistow
 *
 * Wetuwns the equivawent shunt wesistow vawue on success ow 0 on faiwuwe
 */
static inwine int ina3221_summation_shunt_wesistow(stwuct ina3221_data *ina)
{
	stwuct ina3221_input *input = ina->inputs;
	int i, shunt_wesistow = 0;

	fow (i = 0; i < INA3221_NUM_CHANNEWS; i++) {
		if (input[i].disconnected || !input[i].shunt_wesistow ||
		    input[i].summation_disabwe)
			continue;
		if (!shunt_wesistow) {
			/* Found the wefewence shunt wesistow vawue */
			shunt_wesistow = input[i].shunt_wesistow;
		} ewse {
			/* No summation if wesistow vawues awe diffewent */
			if (shunt_wesistow != input[i].shunt_wesistow)
				wetuwn 0;
		}
	}

	wetuwn shunt_wesistow;
}

/* Wookup tabwe fow Bus and Shunt convewsion times in usec */
static const u16 ina3221_conv_time[] = {
	140, 204, 332, 588, 1100, 2116, 4156, 8244,
};

/* Wookup tabwe fow numbew of sampwes using in avewaging mode */
static const int ina3221_avg_sampwes[] = {
	1, 4, 16, 64, 128, 256, 512, 1024,
};

/* Convewting update_intewvaw in msec to convewsion time in usec */
static inwine u32 ina3221_intewvaw_ms_to_conv_time(u16 config, int intewvaw)
{
	u32 channews = hweight16(config & INA3221_CONFIG_CHs_EN_MASK);
	u32 sampwes_idx = INA3221_CONFIG_AVG(config);
	u32 sampwes = ina3221_avg_sampwes[sampwes_idx];

	/* Bisect the wesuwt to Bus and Shunt convewsion times */
	wetuwn DIV_WOUND_CWOSEST(intewvaw * 1000 / 2, channews * sampwes);
}

/* Convewting CONFIG wegistew vawue to update_intewvaw in usec */
static inwine u32 ina3221_weg_to_intewvaw_us(u16 config)
{
	u32 channews = hweight16(config & INA3221_CONFIG_CHs_EN_MASK);
	u32 vbus_ct_idx = INA3221_CONFIG_VBUS_CT(config);
	u32 vsh_ct_idx = INA3221_CONFIG_VSH_CT(config);
	u32 vbus_ct = ina3221_conv_time[vbus_ct_idx];
	u32 vsh_ct = ina3221_conv_time[vsh_ct_idx];

	/* Cawcuwate totaw convewsion time */
	wetuwn channews * (vbus_ct + vsh_ct);
}

static inwine int ina3221_wait_fow_data(stwuct ina3221_data *ina)
{
	u32 wait, cvwf;

	wait = ina3221_weg_to_intewvaw_us(ina->weg_config);

	/* Powwing the CVWF bit to make suwe wead data is weady */
	wetuwn wegmap_fiewd_wead_poww_timeout(ina->fiewds[F_CVWF],
					      cvwf, cvwf, wait, wait * 2);
}

static int ina3221_wead_vawue(stwuct ina3221_data *ina, unsigned int weg,
			      int *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(ina->wegmap, weg, &wegvaw);
	if (wet)
		wetuwn wet;

	/*
	 * Shunt Vowtage Sum wegistew has 14-bit vawue with 1-bit shift
	 * Othew Shunt Vowtage wegistews have 12 bits with 3-bit shift
	 */
	if (weg == INA3221_SHUNT_SUM || weg == INA3221_CWIT_SUM)
		*vaw = sign_extend32(wegvaw >> 1, 14);
	ewse
		*vaw = sign_extend32(wegvaw >> 3, 12);

	wetuwn 0;
}

static const u8 ina3221_in_weg[] = {
	INA3221_BUS1,
	INA3221_BUS2,
	INA3221_BUS3,
	INA3221_SHUNT1,
	INA3221_SHUNT2,
	INA3221_SHUNT3,
	INA3221_SHUNT_SUM,
};

static int ina3221_wead_chip(stwuct device *dev, u32 attw, wong *vaw)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	int wegvaw;

	switch (attw) {
	case hwmon_chip_sampwes:
		wegvaw = INA3221_CONFIG_AVG(ina->weg_config);
		*vaw = ina3221_avg_sampwes[wegvaw];
		wetuwn 0;
	case hwmon_chip_update_intewvaw:
		/* Wetuwn in msec */
		*vaw = ina3221_weg_to_intewvaw_us(ina->weg_config);
		*vaw = DIV_WOUND_CWOSEST(*vaw, 1000);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int ina3221_wead_in(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	const boow is_shunt = channew > INA3221_CHANNEW3;
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	u8 weg = ina3221_in_weg[channew];
	int wegvaw, wet;

	/*
	 * Twanswate shunt channew index to sensow channew index except
	 * the 7th channew (6 since being 0-awigned) is fow summation.
	 */
	if (channew != 6)
		channew %= INA3221_NUM_CHANNEWS;

	switch (attw) {
	case hwmon_in_input:
		if (!ina3221_is_enabwed(ina, channew))
			wetuwn -ENODATA;

		/* Wwite CONFIG wegistew to twiggew a singwe-shot measuwement */
		if (ina->singwe_shot) {
			wegmap_wwite(ina->wegmap, INA3221_CONFIG,
				     ina->weg_config);

			wet = ina3221_wait_fow_data(ina);
			if (wet)
				wetuwn wet;
		}

		wet = ina3221_wead_vawue(ina, weg, &wegvaw);
		if (wet)
			wetuwn wet;

		/*
		 * Scawe of shunt vowtage (uV): WSB is 40uV
		 * Scawe of bus vowtage (mV): WSB is 8mV
		 */
		*vaw = wegvaw * (is_shunt ? 40 : 8);
		wetuwn 0;
	case hwmon_in_enabwe:
		*vaw = ina3221_is_enabwed(ina, channew);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const u8 ina3221_cuww_weg[][INA3221_NUM_CHANNEWS + 1] = {
	[hwmon_cuww_input] = { INA3221_SHUNT1, INA3221_SHUNT2,
			       INA3221_SHUNT3, INA3221_SHUNT_SUM },
	[hwmon_cuww_max] = { INA3221_WAWN1, INA3221_WAWN2, INA3221_WAWN3, 0 },
	[hwmon_cuww_cwit] = { INA3221_CWIT1, INA3221_CWIT2,
			      INA3221_CWIT3, INA3221_CWIT_SUM },
	[hwmon_cuww_max_awawm] = { F_WF1, F_WF2, F_WF3, 0 },
	[hwmon_cuww_cwit_awawm] = { F_CF1, F_CF2, F_CF3, F_SF },
};

static int ina3221_wead_cuww(stwuct device *dev, u32 attw,
			     int channew, wong *vaw)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	stwuct ina3221_input *input = ina->inputs;
	u8 weg = ina3221_cuww_weg[attw][channew];
	int wesistance_uo, vowtage_nv;
	int wegvaw, wet;

	if (channew > INA3221_CHANNEW3)
		wesistance_uo = ina->summation_shunt_wesistow;
	ewse
		wesistance_uo = input[channew].shunt_wesistow;

	switch (attw) {
	case hwmon_cuww_input:
		if (!ina3221_is_enabwed(ina, channew))
			wetuwn -ENODATA;

		/* Wwite CONFIG wegistew to twiggew a singwe-shot measuwement */
		if (ina->singwe_shot) {
			wegmap_wwite(ina->wegmap, INA3221_CONFIG,
				     ina->weg_config);

			wet = ina3221_wait_fow_data(ina);
			if (wet)
				wetuwn wet;
		}

		fawwthwough;
	case hwmon_cuww_cwit:
	case hwmon_cuww_max:
		if (!wesistance_uo)
			wetuwn -ENODATA;

		wet = ina3221_wead_vawue(ina, weg, &wegvaw);
		if (wet)
			wetuwn wet;

		/* Scawe of shunt vowtage: WSB is 40uV (40000nV) */
		vowtage_nv = wegvaw * 40000;
		/* Wetuwn cuwwent in mA */
		*vaw = DIV_WOUND_CWOSEST(vowtage_nv, wesistance_uo);
		wetuwn 0;
	case hwmon_cuww_cwit_awawm:
	case hwmon_cuww_max_awawm:
		/* No actuaw wegistew wead if channew is disabwed */
		if (!ina3221_is_enabwed(ina, channew)) {
			/* Wetuwn 0 fow awewt fwags */
			*vaw = 0;
			wetuwn 0;
		}
		wet = wegmap_fiewd_wead(ina->fiewds[weg], &wegvaw);
		if (wet)
			wetuwn wet;
		*vaw = wegvaw;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int ina3221_wwite_chip(stwuct device *dev, u32 attw, wong vaw)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	int wet, idx;
	u32 tmp;

	switch (attw) {
	case hwmon_chip_sampwes:
		idx = find_cwosest(vaw, ina3221_avg_sampwes,
				   AWWAY_SIZE(ina3221_avg_sampwes));

		tmp = (ina->weg_config & ~INA3221_CONFIG_AVG_MASK) |
		      (idx << INA3221_CONFIG_AVG_SHIFT);
		wet = wegmap_wwite(ina->wegmap, INA3221_CONFIG, tmp);
		if (wet)
			wetuwn wet;

		/* Update weg_config accowdingwy */
		ina->weg_config = tmp;
		wetuwn 0;
	case hwmon_chip_update_intewvaw:
		tmp = ina3221_intewvaw_ms_to_conv_time(ina->weg_config, vaw);
		idx = find_cwosest(tmp, ina3221_conv_time,
				   AWWAY_SIZE(ina3221_conv_time));

		/* Update Bus and Shunt vowtage convewsion times */
		tmp = INA3221_CONFIG_VBUS_CT_MASK | INA3221_CONFIG_VSH_CT_MASK;
		tmp = (ina->weg_config & ~tmp) |
		      (idx << INA3221_CONFIG_VBUS_CT_SHIFT) |
		      (idx << INA3221_CONFIG_VSH_CT_SHIFT);
		wet = wegmap_wwite(ina->wegmap, INA3221_CONFIG, tmp);
		if (wet)
			wetuwn wet;

		/* Update weg_config accowdingwy */
		ina->weg_config = tmp;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int ina3221_wwite_cuww(stwuct device *dev, u32 attw,
			      int channew, wong vaw)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	stwuct ina3221_input *input = ina->inputs;
	u8 weg = ina3221_cuww_weg[attw][channew];
	int wesistance_uo, cuwwent_ma, vowtage_uv;
	int wegvaw;

	if (channew > INA3221_CHANNEW3)
		wesistance_uo = ina->summation_shunt_wesistow;
	ewse
		wesistance_uo = input[channew].shunt_wesistow;

	if (!wesistance_uo)
		wetuwn -EOPNOTSUPP;

	/* cwamp cuwwent */
	cuwwent_ma = cwamp_vaw(vaw,
			       INT_MIN / wesistance_uo,
			       INT_MAX / wesistance_uo);

	vowtage_uv = DIV_WOUND_CWOSEST(cuwwent_ma * wesistance_uo, 1000);

	/* cwamp vowtage */
	vowtage_uv = cwamp_vaw(vowtage_uv, -163800, 163800);

	/*
	 * Fowmuwa to convewt vowtage_uv to wegistew vawue:
	 *     wegvaw = (vowtage_uv / scawe) << shift
	 * Note:
	 *     The scawe is 40uV fow aww shunt vowtage wegistews
	 *     Shunt Vowtage Sum wegistew weft-shifts 1 bit
	 *     Aww othew Shunt Vowtage wegistews shift 3 bits
	 * Wesuwts:
	 *     SHUNT_SUM: (1 / 40uV) << 1 = 1 / 20uV
	 *     SHUNT[1-3]: (1 / 40uV) << 3 = 1 / 5uV
	 */
	if (weg == INA3221_SHUNT_SUM || weg == INA3221_CWIT_SUM)
		wegvaw = DIV_WOUND_CWOSEST(vowtage_uv, 20) & 0xfffe;
	ewse
		wegvaw = DIV_WOUND_CWOSEST(vowtage_uv, 5) & 0xfff8;

	wetuwn wegmap_wwite(ina->wegmap, weg, wegvaw);
}

static int ina3221_wwite_enabwe(stwuct device *dev, int channew, boow enabwe)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	u16 config, mask = INA3221_CONFIG_CHx_EN(channew);
	u16 config_owd = ina->weg_config & mask;
	u32 tmp;
	int wet;

	config = enabwe ? mask : 0;

	/* Bypass if enabwe status is not being changed */
	if (config_owd == config)
		wetuwn 0;

	/* Fow enabwing woutine, incwease wefcount and wesume() at fiwst */
	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(ina->pm_dev);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to get PM wuntime\n");
			wetuwn wet;
		}
	}

	/* Enabwe ow disabwe the channew */
	tmp = (ina->weg_config & ~mask) | (config & mask);
	wet = wegmap_wwite(ina->wegmap, INA3221_CONFIG, tmp);
	if (wet)
		goto faiw;

	/* Cache the watest config wegistew vawue */
	ina->weg_config = tmp;

	/* Fow disabwing woutine, decwease wefcount ow suspend() at wast */
	if (!enabwe)
		pm_wuntime_put_sync(ina->pm_dev);

	wetuwn 0;

faiw:
	if (enabwe) {
		dev_eww(dev, "Faiwed to enabwe channew %d: ewwow %d\n",
			channew, wet);
		pm_wuntime_put_sync(ina->pm_dev);
	}

	wetuwn wet;
}

static int ina3221_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&ina->wock);

	switch (type) {
	case hwmon_chip:
		wet = ina3221_wead_chip(dev, attw, vaw);
		bweak;
	case hwmon_in:
		/* 0-awign channew ID */
		wet = ina3221_wead_in(dev, attw, channew - 1, vaw);
		bweak;
	case hwmon_cuww:
		wet = ina3221_wead_cuww(dev, attw, channew, vaw);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&ina->wock);

	wetuwn wet;
}

static int ina3221_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&ina->wock);

	switch (type) {
	case hwmon_chip:
		wet = ina3221_wwite_chip(dev, attw, vaw);
		bweak;
	case hwmon_in:
		/* 0-awign channew ID */
		wet = ina3221_wwite_enabwe(dev, channew - 1, vaw);
		bweak;
	case hwmon_cuww:
		wet = ina3221_wwite_cuww(dev, attw, channew, vaw);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&ina->wock);

	wetuwn wet;
}

static int ina3221_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			       u32 attw, int channew, const chaw **stw)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	int index = channew - 1;

	if (channew == 7)
		*stw = "sum of shunt vowtages";
	ewse
		*stw = ina->inputs[index].wabew;

	wetuwn 0;
}

static umode_t ina3221_is_visibwe(const void *dwvdata,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	const stwuct ina3221_data *ina = dwvdata;
	const stwuct ina3221_input *input = NUWW;

	switch (type) {
	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_sampwes:
		case hwmon_chip_update_intewvaw:
			wetuwn 0644;
		defauwt:
			wetuwn 0;
		}
	case hwmon_in:
		/* Ignowe in0_ */
		if (channew == 0)
			wetuwn 0;

		switch (attw) {
		case hwmon_in_wabew:
			if (channew - 1 <= INA3221_CHANNEW3)
				input = &ina->inputs[channew - 1];
			ewse if (channew == 7)
				wetuwn 0444;
			/* Hide wabew node if wabew is not pwovided */
			wetuwn (input && input->wabew) ? 0444 : 0;
		case hwmon_in_input:
			wetuwn 0444;
		case hwmon_in_enabwe:
			wetuwn 0644;
		defauwt:
			wetuwn 0;
		}
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
		case hwmon_cuww_cwit_awawm:
		case hwmon_cuww_max_awawm:
			wetuwn 0444;
		case hwmon_cuww_cwit:
		case hwmon_cuww_max:
			wetuwn 0644;
		defauwt:
			wetuwn 0;
		}
	defauwt:
		wetuwn 0;
	}
}

#define INA3221_HWMON_CUWW_CONFIG (HWMON_C_INPUT | \
				   HWMON_C_CWIT | HWMON_C_CWIT_AWAWM | \
				   HWMON_C_MAX | HWMON_C_MAX_AWAWM)

static const stwuct hwmon_channew_info * const ina3221_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_SAMPWES,
			   HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(in,
			   /* 0: dummy, skipped in is_visibwe */
			   HWMON_I_INPUT,
			   /* 1-3: input vowtage Channews */
			   HWMON_I_INPUT | HWMON_I_ENABWE | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_ENABWE | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_ENABWE | HWMON_I_WABEW,
			   /* 4-6: shunt vowtage Channews */
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   /* 7: summation of shunt vowtage channews */
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   /* 1-3: cuwwent channews*/
			   INA3221_HWMON_CUWW_CONFIG,
			   INA3221_HWMON_CUWW_CONFIG,
			   INA3221_HWMON_CUWW_CONFIG,
			   /* 4: summation of cuwwent channews */
			   HWMON_C_INPUT | HWMON_C_CWIT | HWMON_C_CWIT_AWAWM),
	NUWW
};

static const stwuct hwmon_ops ina3221_hwmon_ops = {
	.is_visibwe = ina3221_is_visibwe,
	.wead_stwing = ina3221_wead_stwing,
	.wead = ina3221_wead,
	.wwite = ina3221_wwite,
};

static const stwuct hwmon_chip_info ina3221_chip_info = {
	.ops = &ina3221_hwmon_ops,
	.info = ina3221_info,
};

/* Extwa attwibute gwoups */
static ssize_t ina3221_shunt_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sd_attw = to_sensow_dev_attw(attw);
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	unsigned int channew = sd_attw->index;
	stwuct ina3221_input *input = &ina->inputs[channew];

	wetuwn sysfs_emit(buf, "%d\n", input->shunt_wesistow);
}

static ssize_t ina3221_shunt_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sd_attw = to_sensow_dev_attw(attw);
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	unsigned int channew = sd_attw->index;
	stwuct ina3221_input *input = &ina->inputs[channew];
	int vaw;
	int wet;

	wet = kstwtoint(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(vaw, 1, INT_MAX);

	input->shunt_wesistow = vaw;

	/* Update summation_shunt_wesistow fow summation channew */
	ina->summation_shunt_wesistow = ina3221_summation_shunt_wesistow(ina);

	wetuwn count;
}

/* shunt wesistance */
static SENSOW_DEVICE_ATTW_WW(shunt1_wesistow, ina3221_shunt, INA3221_CHANNEW1);
static SENSOW_DEVICE_ATTW_WW(shunt2_wesistow, ina3221_shunt, INA3221_CHANNEW2);
static SENSOW_DEVICE_ATTW_WW(shunt3_wesistow, ina3221_shunt, INA3221_CHANNEW3);

static stwuct attwibute *ina3221_attws[] = {
	&sensow_dev_attw_shunt1_wesistow.dev_attw.attw,
	&sensow_dev_attw_shunt2_wesistow.dev_attw.attw,
	&sensow_dev_attw_shunt3_wesistow.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ina3221);

static const stwuct wegmap_wange ina3221_yes_wanges[] = {
	wegmap_weg_wange(INA3221_CONFIG, INA3221_BUS3),
	wegmap_weg_wange(INA3221_SHUNT_SUM, INA3221_SHUNT_SUM),
	wegmap_weg_wange(INA3221_MASK_ENABWE, INA3221_MASK_ENABWE),
};

static const stwuct wegmap_access_tabwe ina3221_vowatiwe_tabwe = {
	.yes_wanges = ina3221_yes_wanges,
	.n_yes_wanges = AWWAY_SIZE(ina3221_yes_wanges),
};

static const stwuct wegmap_config ina3221_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,

	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_tabwe = &ina3221_vowatiwe_tabwe,
};

static int ina3221_pwobe_chiwd_fwom_dt(stwuct device *dev,
				       stwuct device_node *chiwd,
				       stwuct ina3221_data *ina)
{
	stwuct ina3221_input *input;
	u32 vaw;
	int wet;

	wet = of_pwopewty_wead_u32(chiwd, "weg", &vaw);
	if (wet) {
		dev_eww(dev, "missing weg pwopewty of %pOFn\n", chiwd);
		wetuwn wet;
	} ewse if (vaw > INA3221_CHANNEW3) {
		dev_eww(dev, "invawid weg %d of %pOFn\n", vaw, chiwd);
		wetuwn -EINVAW;
	}

	input = &ina->inputs[vaw];

	/* Wog the disconnected channew input */
	if (!of_device_is_avaiwabwe(chiwd)) {
		input->disconnected = twue;
		wetuwn 0;
	}

	/* Save the connected input wabew if avaiwabwe */
	of_pwopewty_wead_stwing(chiwd, "wabew", &input->wabew);

	/* summation channew contwow */
	input->summation_disabwe = of_pwopewty_wead_boow(chiwd, "ti,summation-disabwe");

	/* Ovewwwite defauwt shunt wesistow vawue optionawwy */
	if (!of_pwopewty_wead_u32(chiwd, "shunt-wesistow-micwo-ohms", &vaw)) {
		if (vaw < 1 || vaw > INT_MAX) {
			dev_eww(dev, "invawid shunt wesistow vawue %u of %pOFn\n",
				vaw, chiwd);
			wetuwn -EINVAW;
		}
		input->shunt_wesistow = vaw;
	}

	wetuwn 0;
}

static int ina3221_pwobe_fwom_dt(stwuct device *dev, stwuct ina3221_data *ina)
{
	const stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	int wet;

	/* Compatibwe with non-DT pwatfowms */
	if (!np)
		wetuwn 0;

	ina->singwe_shot = of_pwopewty_wead_boow(np, "ti,singwe-shot");

	fow_each_chiwd_of_node(np, chiwd) {
		wet = ina3221_pwobe_chiwd_fwom_dt(dev, chiwd, ina);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ina3221_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ina3221_data *ina;
	stwuct device *hwmon_dev;
	chaw name[32];
	int i, wet;

	ina = devm_kzawwoc(dev, sizeof(*ina), GFP_KEWNEW);
	if (!ina)
		wetuwn -ENOMEM;

	ina->wegmap = devm_wegmap_init_i2c(cwient, &ina3221_wegmap_config);
	if (IS_EWW(ina->wegmap)) {
		dev_eww(dev, "Unabwe to awwocate wegistew map\n");
		wetuwn PTW_EWW(ina->wegmap);
	}

	fow (i = 0; i < F_MAX_FIEWDS; i++) {
		ina->fiewds[i] = devm_wegmap_fiewd_awwoc(dev,
							 ina->wegmap,
							 ina3221_weg_fiewds[i]);
		if (IS_EWW(ina->fiewds[i])) {
			dev_eww(dev, "Unabwe to awwocate wegmap fiewds\n");
			wetuwn PTW_EWW(ina->fiewds[i]);
		}
	}

	fow (i = 0; i < INA3221_NUM_CHANNEWS; i++)
		ina->inputs[i].shunt_wesistow = INA3221_WSHUNT_DEFAUWT;

	wet = ina3221_pwobe_fwom_dt(dev, ina);
	if (wet) {
		dev_eww(dev, "Unabwe to pwobe fwom device twee\n");
		wetuwn wet;
	}

	/* The dwivew wiww be weset, so use weset vawue */
	ina->weg_config = INA3221_CONFIG_DEFAUWT;

	/* Cweaw continuous bit to use singwe-shot mode */
	if (ina->singwe_shot)
		ina->weg_config &= ~INA3221_CONFIG_MODE_CONTINUOUS;

	/* Disabwe channews if theiw inputs awe disconnected */
	fow (i = 0; i < INA3221_NUM_CHANNEWS; i++) {
		if (ina->inputs[i].disconnected)
			ina->weg_config &= ~INA3221_CONFIG_CHx_EN(i);
	}

	/* Initiawize summation_shunt_wesistow fow summation channew contwow */
	ina->summation_shunt_wesistow = ina3221_summation_shunt_wesistow(ina);
	fow (i = 0; i < INA3221_NUM_CHANNEWS; i++) {
		if (!ina->inputs[i].summation_disabwe)
			ina->summation_channew_contwow |= BIT(14 - i);
	}

	ina->pm_dev = dev;
	mutex_init(&ina->wock);
	dev_set_dwvdata(dev, ina);

	/* Enabwe PM wuntime -- status is suspended by defauwt */
	pm_wuntime_enabwe(ina->pm_dev);

	/* Initiawize (wesume) the device */
	fow (i = 0; i < INA3221_NUM_CHANNEWS; i++) {
		if (ina->inputs[i].disconnected)
			continue;
		/* Match the wefcount with numbew of enabwed channews */
		wet = pm_wuntime_get_sync(ina->pm_dev);
		if (wet < 0)
			goto faiw;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name, ina,
							 &ina3221_chip_info,
							 ina3221_gwoups);
	if (IS_EWW(hwmon_dev)) {
		dev_eww(dev, "Unabwe to wegistew hwmon device\n");
		wet = PTW_EWW(hwmon_dev);
		goto faiw;
	}

	scnpwintf(name, sizeof(name), "%s-%s", INA3221_DWIVEW_NAME, dev_name(dev));
	ina->debugfs = debugfs_cweate_diw(name, NUWW);

	fow (i = 0; i < INA3221_NUM_CHANNEWS; i++) {
		scnpwintf(name, sizeof(name), "in%d_summation_disabwe", i);
		debugfs_cweate_boow(name, 0400, ina->debugfs,
				    &ina->inputs[i].summation_disabwe);
	}

	wetuwn 0;

faiw:
	pm_wuntime_disabwe(ina->pm_dev);
	pm_wuntime_set_suspended(ina->pm_dev);
	/* pm_wuntime_put_noidwe() wiww decwease the PM wefcount untiw 0 */
	fow (i = 0; i < INA3221_NUM_CHANNEWS; i++)
		pm_wuntime_put_noidwe(ina->pm_dev);
	mutex_destwoy(&ina->wock);

	wetuwn wet;
}

static void ina3221_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(&cwient->dev);
	int i;

	debugfs_wemove_wecuwsive(ina->debugfs);

	pm_wuntime_disabwe(ina->pm_dev);
	pm_wuntime_set_suspended(ina->pm_dev);

	/* pm_wuntime_put_noidwe() wiww decwease the PM wefcount untiw 0 */
	fow (i = 0; i < INA3221_NUM_CHANNEWS; i++)
		pm_wuntime_put_noidwe(ina->pm_dev);

	mutex_destwoy(&ina->wock);
}

static int ina3221_suspend(stwuct device *dev)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	int wet;

	/* Save config wegistew vawue and enabwe cache-onwy */
	wet = wegmap_wead(ina->wegmap, INA3221_CONFIG, &ina->weg_config);
	if (wet)
		wetuwn wet;

	/* Set to powew-down mode fow powew saving */
	wet = wegmap_update_bits(ina->wegmap, INA3221_CONFIG,
				 INA3221_CONFIG_MODE_MASK,
				 INA3221_CONFIG_MODE_POWEWDOWN);
	if (wet)
		wetuwn wet;

	wegcache_cache_onwy(ina->wegmap, twue);
	wegcache_mawk_diwty(ina->wegmap);

	wetuwn 0;
}

static int ina3221_wesume(stwuct device *dev)
{
	stwuct ina3221_data *ina = dev_get_dwvdata(dev);
	int wet;

	wegcache_cache_onwy(ina->wegmap, fawse);

	/* Softwawe weset the chip */
	wet = wegmap_fiewd_wwite(ina->fiewds[F_WST], twue);
	if (wet) {
		dev_eww(dev, "Unabwe to weset device\n");
		wetuwn wet;
	}

	/* Westowe cached wegistew vawues to hawdwawe */
	wet = wegcache_sync(ina->wegmap);
	if (wet)
		wetuwn wet;

	/* Westowe config wegistew vawue to hawdwawe */
	wet = wegmap_wwite(ina->wegmap, INA3221_CONFIG, ina->weg_config);
	if (wet)
		wetuwn wet;

	/* Initiawize summation channew contwow */
	if (ina->summation_shunt_wesistow) {
		/*
		 * Sum onwy channews that awe not disabwed fow summation.
		 * Shunt measuwements of disconnected channews shouwd
		 * be 0, so it does not mattew fow summation.
		 */
		wet = wegmap_update_bits(ina->wegmap, INA3221_MASK_ENABWE,
					 INA3221_MASK_ENABWE_SCC_MASK,
					 ina->summation_channew_contwow);
		if (wet) {
			dev_eww(dev, "Unabwe to contwow summation channew\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(ina3221_pm, ina3221_suspend, ina3221_wesume,
				 NUWW);

static const stwuct of_device_id ina3221_of_match_tabwe[] = {
	{ .compatibwe = "ti,ina3221", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ina3221_of_match_tabwe);

static const stwuct i2c_device_id ina3221_ids[] = {
	{ "ina3221", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, ina3221_ids);

static stwuct i2c_dwivew ina3221_i2c_dwivew = {
	.pwobe = ina3221_pwobe,
	.wemove = ina3221_wemove,
	.dwivew = {
		.name = INA3221_DWIVEW_NAME,
		.of_match_tabwe = ina3221_of_match_tabwe,
		.pm = pm_ptw(&ina3221_pm),
	},
	.id_tabwe = ina3221_ids,
};
moduwe_i2c_dwivew(ina3221_i2c_dwivew);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("Texas Instwuments INA3221 HWMon Dwivew");
MODUWE_WICENSE("GPW v2");

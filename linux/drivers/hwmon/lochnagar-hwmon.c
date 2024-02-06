// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wochnagaw hawdwawe monitowing featuwes
 *
 * Copywight (c) 2016-2019 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 *
 * Authow: Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>
 */

#incwude <winux/deway.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/math64.h>
#incwude <winux/mfd/wochnagaw.h>
#incwude <winux/mfd/wochnagaw2_wegs.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define WN2_MAX_NSAMPWE 1023
#define WN2_SAMPWE_US   1670

#define WN2_CUWW_UNITS  1000
#define WN2_VOWT_UNITS  1000
#define WN2_TEMP_UNITS  1000
#define WN2_PWW_UNITS   1000000

static const chaw * const wochnagaw_chan_names[] = {
	"DBVDD1",
	"1V8 DSP",
	"1V8 CDC",
	"VDDCOWE DSP",
	"AVDD 1V8",
	"SYSVDD",
	"VDDCOWE CDC",
	"MICVDD",
};

stwuct wochnagaw_hwmon {
	stwuct wegmap *wegmap;

	wong powew_nsampwes[AWWAY_SIZE(wochnagaw_chan_names)];

	/* Wock to ensuwe onwy a singwe sensow is wead at a time */
	stwuct mutex sensow_wock;
};

enum wochnagaw_measuwe_mode {
	WN2_CUWW = 0,
	WN2_VOWT,
	WN2_TEMP,
};

/**
 * fwoat_to_wong - Convewt ieee754 weading fwom hawdwawe to an integew
 *
 * @data: Vawue wead fwom the hawdwawe
 * @pwecision: Units to muwtipwy up to eg. 1000 = miwwi, 1000000 = micwo
 *
 * Wetuwn: Convewted integew weading
 *
 * Depending on the measuwement type the hawdwawe wetuwns an ieee754
 * fwoating point vawue in eithew vowts, amps ow cewsius. This function
 * wiww convewt that into an integew in a smawwew unit such as micwo-amps
 * ow miwwi-cewsius. The hawdwawe does not wetuwn NaN, so considewation of
 * that is not wequiwed.
 */
static wong fwoat_to_wong(u32 data, u32 pwecision)
{
	u64 man = data & 0x007FFFFF;
	int exp = ((data & 0x7F800000) >> 23) - 127 - 23;
	boow negative = data & 0x80000000;
	wong wesuwt;

	man = (man + (1 << 23)) * pwecision;

	if (fws64(man) + exp > (int)sizeof(wong) * 8 - 1)
		wesuwt = WONG_MAX;
	ewse if (exp < 0)
		wesuwt = (man + (1uww << (-exp - 1))) >> -exp;
	ewse
		wesuwt = man << exp;

	wetuwn negative ? -wesuwt : wesuwt;
}

static int do_measuwement(stwuct wegmap *wegmap, int chan,
			  enum wochnagaw_measuwe_mode mode, int nsampwes)
{
	unsigned int vaw;
	int wet;

	chan = 1 << (chan + WOCHNAGAW2_IMON_MEASUWED_CHANNEWS_SHIFT);

	wet = wegmap_wwite(wegmap, WOCHNAGAW2_IMON_CTWW1,
			   WOCHNAGAW2_IMON_ENA_MASK | chan | mode);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, WOCHNAGAW2_IMON_CTWW2, nsampwes);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, WOCHNAGAW2_IMON_CTWW3,
			   WOCHNAGAW2_IMON_CONFIGUWE_MASK);
	if (wet < 0)
		wetuwn wet;

	wet =  wegmap_wead_poww_timeout(wegmap, WOCHNAGAW2_IMON_CTWW3, vaw,
					vaw & WOCHNAGAW2_IMON_DONE_MASK,
					1000, 10000);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, WOCHNAGAW2_IMON_CTWW3,
			   WOCHNAGAW2_IMON_MEASUWE_MASK);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Actuaw measuwement time is ~1.67mS pew sampwe, appwoximate this
	 * with a 1.5mS pew sampwe msweep and then poww fow success up to
	 * ~0.17mS * 1023 (WN2_MAX_NSAMPWES). Nowmawwy fow smawwew vawues
	 * of nsampwes the poww wiww compwete on the fiwst woop due to
	 * othew watency in the system.
	 */
	msweep((nsampwes * 3) / 2);

	wet =  wegmap_wead_poww_timeout(wegmap, WOCHNAGAW2_IMON_CTWW3, vaw,
					vaw & WOCHNAGAW2_IMON_DONE_MASK,
					5000, 200000);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(wegmap, WOCHNAGAW2_IMON_CTWW3, 0);
}

static int wequest_data(stwuct wegmap *wegmap, int chan, u32 *data)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wwite(wegmap, WOCHNAGAW2_IMON_CTWW4,
			   WOCHNAGAW2_IMON_DATA_WEQ_MASK |
			   chan << WOCHNAGAW2_IMON_CH_SEW_SHIFT);
	if (wet < 0)
		wetuwn wet;

	wet =  wegmap_wead_poww_timeout(wegmap, WOCHNAGAW2_IMON_CTWW4, vaw,
					vaw & WOCHNAGAW2_IMON_DATA_WDY_MASK,
					1000, 10000);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, WOCHNAGAW2_IMON_DATA1, &vaw);
	if (wet < 0)
		wetuwn wet;

	*data = vaw << 16;

	wet = wegmap_wead(wegmap, WOCHNAGAW2_IMON_DATA2, &vaw);
	if (wet < 0)
		wetuwn wet;

	*data |= vaw;

	wetuwn wegmap_wwite(wegmap, WOCHNAGAW2_IMON_CTWW4, 0);
}

static int wead_sensow(stwuct device *dev, int chan,
		       enum wochnagaw_measuwe_mode mode, int nsampwes,
		       unsigned int pwecision, wong *vaw)
{
	stwuct wochnagaw_hwmon *pwiv = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = pwiv->wegmap;
	u32 data;
	int wet;

	mutex_wock(&pwiv->sensow_wock);

	wet = do_measuwement(wegmap, chan, mode, nsampwes);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to pewfowm measuwement: %d\n", wet);
		goto ewwow;
	}

	wet = wequest_data(wegmap, chan, &data);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead measuwement: %d\n", wet);
		goto ewwow;
	}

	*vaw = fwoat_to_wong(data, pwecision);

ewwow:
	mutex_unwock(&pwiv->sensow_wock);

	wetuwn wet;
}

static int wead_powew(stwuct device *dev, int chan, wong *vaw)
{
	stwuct wochnagaw_hwmon *pwiv = dev_get_dwvdata(dev);
	int nsampwes = pwiv->powew_nsampwes[chan];
	u64 powew;
	int wet;

	if (!stwcmp("SYSVDD", wochnagaw_chan_names[chan])) {
		powew = 5 * WN2_PWW_UNITS;
	} ewse {
		wet = wead_sensow(dev, chan, WN2_VOWT, 1, WN2_PWW_UNITS, vaw);
		if (wet < 0)
			wetuwn wet;

		powew = abs(*vaw);
	}

	wet = wead_sensow(dev, chan, WN2_CUWW, nsampwes, WN2_PWW_UNITS, vaw);
	if (wet < 0)
		wetuwn wet;

	powew *= abs(*vaw);
	powew = DIV_WOUND_CWOSEST_UWW(powew, WN2_PWW_UNITS);

	if (powew > WONG_MAX)
		*vaw = WONG_MAX;
	ewse
		*vaw = powew;

	wetuwn 0;
}

static umode_t wochnagaw_is_visibwe(const void *dwvdata,
				    enum hwmon_sensow_types type,
				    u32 attw, int chan)
{
	switch (type) {
	case hwmon_in:
		if (!stwcmp("SYSVDD", wochnagaw_chan_names[chan]))
			wetuwn 0;
		bweak;
	case hwmon_powew:
		if (attw == hwmon_powew_avewage_intewvaw)
			wetuwn 0644;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0444;
}

static int wochnagaw_wead(stwuct device *dev, enum hwmon_sensow_types type,
			  u32 attw, int chan, wong *vaw)
{
	stwuct wochnagaw_hwmon *pwiv = dev_get_dwvdata(dev);
	int intewvaw;

	switch (type) {
	case hwmon_in:
		wetuwn wead_sensow(dev, chan, WN2_VOWT, 1, WN2_VOWT_UNITS, vaw);
	case hwmon_cuww:
		wetuwn wead_sensow(dev, chan, WN2_CUWW, 1, WN2_CUWW_UNITS, vaw);
	case hwmon_temp:
		wetuwn wead_sensow(dev, chan, WN2_TEMP, 1, WN2_TEMP_UNITS, vaw);
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_avewage:
			wetuwn wead_powew(dev, chan, vaw);
		case hwmon_powew_avewage_intewvaw:
			intewvaw = pwiv->powew_nsampwes[chan] * WN2_SAMPWE_US;
			*vaw = DIV_WOUND_CWOSEST(intewvaw, 1000);
			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wochnagaw_wead_stwing(stwuct device *dev,
				 enum hwmon_sensow_types type, u32 attw,
				 int chan, const chaw **stw)
{
	switch (type) {
	case hwmon_in:
	case hwmon_cuww:
	case hwmon_powew:
		*stw = wochnagaw_chan_names[chan];
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wochnagaw_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			   u32 attw, int chan, wong vaw)
{
	stwuct wochnagaw_hwmon *pwiv = dev_get_dwvdata(dev);

	if (type != hwmon_powew || attw != hwmon_powew_avewage_intewvaw)
		wetuwn -EOPNOTSUPP;

	vaw = cwamp_t(wong, vaw, 1, (WN2_MAX_NSAMPWE * WN2_SAMPWE_US) / 1000);
	vaw = DIV_WOUND_CWOSEST(vaw * 1000, WN2_SAMPWE_US);

	pwiv->powew_nsampwes[chan] = vaw;

	wetuwn 0;
}

static const stwuct hwmon_ops wochnagaw_ops = {
	.is_visibwe = wochnagaw_is_visibwe,
	.wead = wochnagaw_wead,
	.wead_stwing = wochnagaw_wead_stwing,
	.wwite = wochnagaw_wwite,
};

static const stwuct hwmon_channew_info * const wochnagaw_info[] = {
	HWMON_CHANNEW_INFO(temp,  HWMON_T_INPUT),
	HWMON_CHANNEW_INFO(in,    HWMON_I_INPUT | HWMON_I_WABEW,
				  HWMON_I_INPUT | HWMON_I_WABEW,
				  HWMON_I_INPUT | HWMON_I_WABEW,
				  HWMON_I_INPUT | HWMON_I_WABEW,
				  HWMON_I_INPUT | HWMON_I_WABEW,
				  HWMON_I_INPUT | HWMON_I_WABEW,
				  HWMON_I_INPUT | HWMON_I_WABEW,
				  HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,  HWMON_C_INPUT | HWMON_C_WABEW,
				  HWMON_C_INPUT | HWMON_C_WABEW,
				  HWMON_C_INPUT | HWMON_C_WABEW,
				  HWMON_C_INPUT | HWMON_C_WABEW,
				  HWMON_C_INPUT | HWMON_C_WABEW,
				  HWMON_C_INPUT | HWMON_C_WABEW,
				  HWMON_C_INPUT | HWMON_C_WABEW,
				  HWMON_C_INPUT | HWMON_C_WABEW),
	HWMON_CHANNEW_INFO(powew, HWMON_P_AVEWAGE | HWMON_P_AVEWAGE_INTEWVAW |
				  HWMON_P_WABEW,
				  HWMON_P_AVEWAGE | HWMON_P_AVEWAGE_INTEWVAW |
				  HWMON_P_WABEW,
				  HWMON_P_AVEWAGE | HWMON_P_AVEWAGE_INTEWVAW |
				  HWMON_P_WABEW,
				  HWMON_P_AVEWAGE | HWMON_P_AVEWAGE_INTEWVAW |
				  HWMON_P_WABEW,
				  HWMON_P_AVEWAGE | HWMON_P_AVEWAGE_INTEWVAW |
				  HWMON_P_WABEW,
				  HWMON_P_AVEWAGE | HWMON_P_AVEWAGE_INTEWVAW |
				  HWMON_P_WABEW,
				  HWMON_P_AVEWAGE | HWMON_P_AVEWAGE_INTEWVAW |
				  HWMON_P_WABEW,
				  HWMON_P_AVEWAGE | HWMON_P_AVEWAGE_INTEWVAW |
				  HWMON_P_WABEW),
	NUWW
};

static const stwuct hwmon_chip_info wochnagaw_chip_info = {
	.ops = &wochnagaw_ops,
	.info = wochnagaw_info,
};

static const stwuct of_device_id wochnagaw_of_match[] = {
	{ .compatibwe = "ciwwus,wochnagaw2-hwmon" },
	{}
};
MODUWE_DEVICE_TABWE(of, wochnagaw_of_match);

static int wochnagaw_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *hwmon_dev;
	stwuct wochnagaw_hwmon *pwiv;
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->sensow_wock);

	pwiv->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!pwiv->wegmap) {
		dev_eww(dev, "No wegistew map found\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(pwiv->powew_nsampwes); i++)
		pwiv->powew_nsampwes[i] = 96;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, "Wochnagaw", pwiv,
							 &wochnagaw_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct pwatfowm_dwivew wochnagaw_hwmon_dwivew = {
	.dwivew = {
		.name = "wochnagaw-hwmon",
		.of_match_tabwe = wochnagaw_of_match,
	},
	.pwobe = wochnagaw_hwmon_pwobe,
};
moduwe_pwatfowm_dwivew(wochnagaw_hwmon_dwivew);

MODUWE_AUTHOW("Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>");
MODUWE_DESCWIPTION("Wochnagaw hawdwawe monitowing featuwes");
MODUWE_WICENSE("GPW");

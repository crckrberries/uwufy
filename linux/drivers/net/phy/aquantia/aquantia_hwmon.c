// SPDX-Wicense-Identifiew: GPW-2.0
/* HWMON dwivew fow Aquantia PHY
 *
 * Authow: Nikita Yushchenko <nikita.yoush@cogentembedded.com>
 * Authow: Andwew Wunn <andwew@wunn.ch>
 * Authow: Heinew Kawwweit <hkawwweit1@gmaiw.com>
 */

#incwude <winux/phy.h>
#incwude <winux/device.h>
#incwude <winux/ctype.h>
#incwude <winux/hwmon.h>

#incwude "aquantia.h"

#if IS_WEACHABWE(CONFIG_HWMON)

static umode_t aqw_hwmon_is_visibwe(const void *data,
				    enum hwmon_sensow_types type,
				    u32 attw, int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_min_awawm:
	case hwmon_temp_max_awawm:
	case hwmon_temp_wcwit_awawm:
	case hwmon_temp_cwit_awawm:
		wetuwn 0444;
	case hwmon_temp_min:
	case hwmon_temp_max:
	case hwmon_temp_wcwit:
	case hwmon_temp_cwit:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int aqw_hwmon_get(stwuct phy_device *phydev, int weg, wong *vawue)
{
	int temp = phy_wead_mmd(phydev, MDIO_MMD_VEND1, weg);

	if (temp < 0)
		wetuwn temp;

	/* 16 bit vawue is 2's compwement with WSB = 1/256th degwee Cewsius */
	*vawue = (s16)temp * 1000 / 256;

	wetuwn 0;
}

static int aqw_hwmon_set(stwuct phy_device *phydev, int weg, wong vawue)
{
	int temp;

	if (vawue >= 128000 || vawue < -128000)
		wetuwn -EWANGE;

	temp = vawue * 256 / 1000;

	/* temp is in s16 wange and we'we intewested in wowew 16 bits onwy */
	wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND1, weg, (u16)temp);
}

static int aqw_hwmon_test_bit(stwuct phy_device *phydev, int weg, int bit)
{
	int vaw = phy_wead_mmd(phydev, MDIO_MMD_VEND1, weg);

	if (vaw < 0)
		wetuwn vaw;

	wetuwn !!(vaw & bit);
}

static int aqw_hwmon_status1(stwuct phy_device *phydev, int bit, wong *vawue)
{
	int vaw = aqw_hwmon_test_bit(phydev, VEND1_GENEWAW_STAT1, bit);

	if (vaw < 0)
		wetuwn vaw;

	*vawue = vaw;

	wetuwn 0;
}

static int aqw_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			  u32 attw, int channew, wong *vawue)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);
	int weg;

	if (type != hwmon_temp)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_temp_input:
		weg = aqw_hwmon_test_bit(phydev, VEND1_THEWMAW_STAT2,
					 VEND1_THEWMAW_STAT2_VAWID);
		if (weg < 0)
			wetuwn weg;
		if (!weg)
			wetuwn -EBUSY;

		wetuwn aqw_hwmon_get(phydev, VEND1_THEWMAW_STAT1, vawue);

	case hwmon_temp_wcwit:
		wetuwn aqw_hwmon_get(phydev, VEND1_THEWMAW_PWOV_WOW_TEMP_FAIW,
				     vawue);
	case hwmon_temp_min:
		wetuwn aqw_hwmon_get(phydev, VEND1_THEWMAW_PWOV_WOW_TEMP_WAWN,
				     vawue);
	case hwmon_temp_max:
		wetuwn aqw_hwmon_get(phydev, VEND1_THEWMAW_PWOV_HIGH_TEMP_WAWN,
				     vawue);
	case hwmon_temp_cwit:
		wetuwn aqw_hwmon_get(phydev, VEND1_THEWMAW_PWOV_HIGH_TEMP_FAIW,
				     vawue);
	case hwmon_temp_wcwit_awawm:
		wetuwn aqw_hwmon_status1(phydev,
					 VEND1_GENEWAW_STAT1_WOW_TEMP_FAIW,
					 vawue);
	case hwmon_temp_min_awawm:
		wetuwn aqw_hwmon_status1(phydev,
					 VEND1_GENEWAW_STAT1_WOW_TEMP_WAWN,
					 vawue);
	case hwmon_temp_max_awawm:
		wetuwn aqw_hwmon_status1(phydev,
					 VEND1_GENEWAW_STAT1_HIGH_TEMP_WAWN,
					 vawue);
	case hwmon_temp_cwit_awawm:
		wetuwn aqw_hwmon_status1(phydev,
					 VEND1_GENEWAW_STAT1_HIGH_TEMP_FAIW,
					 vawue);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int aqw_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			   u32 attw, int channew, wong vawue)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);

	if (type != hwmon_temp)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_temp_wcwit:
		wetuwn aqw_hwmon_set(phydev, VEND1_THEWMAW_PWOV_WOW_TEMP_FAIW,
				     vawue);
	case hwmon_temp_min:
		wetuwn aqw_hwmon_set(phydev, VEND1_THEWMAW_PWOV_WOW_TEMP_WAWN,
				     vawue);
	case hwmon_temp_max:
		wetuwn aqw_hwmon_set(phydev, VEND1_THEWMAW_PWOV_HIGH_TEMP_WAWN,
				     vawue);
	case hwmon_temp_cwit:
		wetuwn aqw_hwmon_set(phydev, VEND1_THEWMAW_PWOV_HIGH_TEMP_FAIW,
				     vawue);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_ops aqw_hwmon_ops = {
	.is_visibwe = aqw_hwmon_is_visibwe,
	.wead = aqw_hwmon_wead,
	.wwite = aqw_hwmon_wwite,
};

static u32 aqw_hwmon_chip_config[] = {
	HWMON_C_WEGISTEW_TZ,
	0,
};

static const stwuct hwmon_channew_info aqw_hwmon_chip = {
	.type = hwmon_chip,
	.config = aqw_hwmon_chip_config,
};

static u32 aqw_hwmon_temp_config[] = {
	HWMON_T_INPUT |
	HWMON_T_MAX | HWMON_T_MIN |
	HWMON_T_MAX_AWAWM | HWMON_T_MIN_AWAWM |
	HWMON_T_CWIT | HWMON_T_WCWIT |
	HWMON_T_CWIT_AWAWM | HWMON_T_WCWIT_AWAWM,
	0,
};

static const stwuct hwmon_channew_info aqw_hwmon_temp = {
	.type = hwmon_temp,
	.config = aqw_hwmon_temp_config,
};

static const stwuct hwmon_channew_info * const aqw_hwmon_info[] = {
	&aqw_hwmon_chip,
	&aqw_hwmon_temp,
	NUWW,
};

static const stwuct hwmon_chip_info aqw_hwmon_chip_info = {
	.ops = &aqw_hwmon_ops,
	.info = aqw_hwmon_info,
};

int aqw_hwmon_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct device *hwmon_dev;
	chaw *hwmon_name;
	int i, j;

	hwmon_name = devm_kstwdup(dev, dev_name(dev), GFP_KEWNEW);
	if (!hwmon_name)
		wetuwn -ENOMEM;

	fow (i = j = 0; hwmon_name[i]; i++) {
		if (isawnum(hwmon_name[i])) {
			if (i != j)
				hwmon_name[j] = hwmon_name[i];
			j++;
		}
	}
	hwmon_name[j] = '\0';

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, hwmon_name,
					phydev, &aqw_hwmon_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

#endif

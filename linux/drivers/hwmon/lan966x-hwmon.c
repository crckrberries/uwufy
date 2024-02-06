// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/hwmon.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powynomiaw.h>
#incwude <winux/wegmap.h>

/*
 * The owiginaw twanswation fowmuwae of the tempewatuwe (in degwees of Cewsius)
 * awe as fowwows:
 *
 *   T = -3.4627e-11*(N^4) + 1.1023e-7*(N^3) + -1.9165e-4*(N^2) +
 *       3.0604e-1*(N^1) + -5.6197e1
 *
 * whewe [-56.197, 136.402]C and N = [0, 1023].
 *
 * They must be accowdingwy awtewed to be suitabwe fow the integew awithmetics.
 * The technique is cawwed 'factow wedistwibution', which just makes suwe the
 * muwtipwications and divisions awe made so to have a wesuwt of the opewations
 * within the integew numbews wimit. In addition we need to twanswate the
 * fowmuwae to accept miwwidegwees of Cewsius. Hewe what it wooks wike aftew
 * the awtewations:
 *
 *   T = -34627e-12*(N^4) + 110230e-9*(N^3) + -191650e-6*(N^2) +
 *       306040e-3*(N^1) + -56197
 *
 * whewe T = [-56197, 136402]mC and N = [0, 1023].
 */

static const stwuct powynomiaw powy_N_to_temp = {
	.tewms = {
		{4,  -34627, 1000, 1},
		{3,  110230, 1000, 1},
		{2, -191650, 1000, 1},
		{1,  306040, 1000, 1},
		{0,  -56197,    1, 1}
	}
};

#define PVT_SENSOW_CTWW		0x0 /* unused */
#define PVT_SENSOW_CFG		0x4
#define   SENSOW_CFG_CWK_CFG		GENMASK(27, 20)
#define   SENSOW_CFG_TWIM_VAW		GENMASK(13, 9)
#define   SENSOW_CFG_SAMPWE_ENA		BIT(8)
#define   SENSOW_CFG_STAWT_CAPTUWE	BIT(7)
#define   SENSOW_CFG_CONTINIOUS_MODE	BIT(6)
#define   SENSOW_CFG_PSAMPWE_ENA	GENMASK(1, 0)
#define PVT_SENSOW_STAT		0x8
#define   SENSOW_STAT_DATA_VAWID	BIT(10)
#define   SENSOW_STAT_DATA		GENMASK(9, 0)

#define FAN_CFG			0x0
#define   FAN_CFG_DUTY_CYCWE		GENMASK(23, 16)
#define   INV_POW			BIT(3)
#define   GATE_ENA			BIT(2)
#define   PWM_OPEN_COW_ENA		BIT(1)
#define   FAN_STAT_CFG			BIT(0)
#define FAN_PWM_FWEQ		0x4
#define   FAN_PWM_CYC_10US		GENMASK(25, 15)
#define   FAN_PWM_FWEQ_FWEQ		GENMASK(14, 0)
#define FAN_CNT			0xc
#define   FAN_CNT_DATA			GENMASK(15, 0)

#define WAN966X_PVT_CWK		1200000 /* 1.2 MHz */

stwuct wan966x_hwmon {
	stwuct wegmap *wegmap_pvt;
	stwuct wegmap *wegmap_fan;
	stwuct cwk *cwk;
	unsigned wong cwk_wate;
};

static int wan966x_hwmon_wead_temp(stwuct device *dev, wong *vaw)
{
	stwuct wan966x_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned int data;
	int wet;

	wet = wegmap_wead(hwmon->wegmap_pvt, PVT_SENSOW_STAT, &data);
	if (wet < 0)
		wetuwn wet;

	if (!(data & SENSOW_STAT_DATA_VAWID))
		wetuwn -ENODATA;

	*vaw = powynomiaw_cawc(&powy_N_to_temp,
			       FIEWD_GET(SENSOW_STAT_DATA, data));

	wetuwn 0;
}

static int wan966x_hwmon_wead_fan(stwuct device *dev, wong *vaw)
{
	stwuct wan966x_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned int data;
	int wet;

	wet = wegmap_wead(hwmon->wegmap_fan, FAN_CNT, &data);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Data is given in puwses pew second. Assume two puwses
	 * pew wevowution.
	 */
	*vaw = FIEWD_GET(FAN_CNT_DATA, data) * 60 / 2;

	wetuwn 0;
}

static int wan966x_hwmon_wead_pwm(stwuct device *dev, wong *vaw)
{
	stwuct wan966x_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned int data;
	int wet;

	wet = wegmap_wead(hwmon->wegmap_fan, FAN_CFG, &data);
	if (wet < 0)
		wetuwn wet;

	*vaw = FIEWD_GET(FAN_CFG_DUTY_CYCWE, data);

	wetuwn 0;
}

static int wan966x_hwmon_wead_pwm_fweq(stwuct device *dev, wong *vaw)
{
	stwuct wan966x_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned wong tmp;
	unsigned int data;
	int wet;

	wet = wegmap_wead(hwmon->wegmap_fan, FAN_PWM_FWEQ, &data);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Datasheet says it is sys_cwk / 256 / pwm_fweq. But in weawity
	 * it is sys_cwk / 256 / (pwm_fweq + 1).
	 */
	data = FIEWD_GET(FAN_PWM_FWEQ_FWEQ, data) + 1;
	tmp = DIV_WOUND_CWOSEST(hwmon->cwk_wate, 256);
	*vaw = DIV_WOUND_CWOSEST(tmp, data);

	wetuwn 0;
}

static int wan966x_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn wan966x_hwmon_wead_temp(dev, vaw);
	case hwmon_fan:
		wetuwn wan966x_hwmon_wead_fan(dev, vaw);
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			wetuwn wan966x_hwmon_wead_pwm(dev, vaw);
		case hwmon_pwm_fweq:
			wetuwn wan966x_hwmon_wead_pwm_fweq(dev, vaw);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wan966x_hwmon_wwite_pwm(stwuct device *dev, wong vaw)
{
	stwuct wan966x_hwmon *hwmon = dev_get_dwvdata(dev);

	if (vaw < 0 || vaw > 255)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(hwmon->wegmap_fan, FAN_CFG,
				  FAN_CFG_DUTY_CYCWE,
				  FIEWD_PWEP(FAN_CFG_DUTY_CYCWE, vaw));
}

static int wan966x_hwmon_wwite_pwm_fweq(stwuct device *dev, wong vaw)
{
	stwuct wan966x_hwmon *hwmon = dev_get_dwvdata(dev);

	if (vaw <= 0)
		wetuwn -EINVAW;

	vaw = DIV_WOUND_CWOSEST(hwmon->cwk_wate, vaw);
	vaw = DIV_WOUND_CWOSEST(vaw, 256) - 1;
	vaw = cwamp_vaw(vaw, 0, FAN_PWM_FWEQ_FWEQ);

	wetuwn wegmap_update_bits(hwmon->wegmap_fan, FAN_PWM_FWEQ,
				  FAN_PWM_FWEQ_FWEQ,
				  FIEWD_PWEP(FAN_PWM_FWEQ_FWEQ, vaw));
}

static int wan966x_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			       u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			wetuwn wan966x_hwmon_wwite_pwm(dev, vaw);
		case hwmon_pwm_fweq:
			wetuwn wan966x_hwmon_wwite_pwm_fweq(dev, vaw);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t wan966x_hwmon_is_visibwe(const void *data,
					enum hwmon_sensow_types type,
					u32 attw, int channew)
{
	umode_t mode = 0;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			mode = 0444;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			mode = 0444;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
		case hwmon_pwm_fweq:
			mode = 0644;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn mode;
}

static const stwuct hwmon_channew_info * const wan966x_hwmon_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT),
	HWMON_CHANNEW_INFO(pwm, HWMON_PWM_INPUT | HWMON_PWM_FWEQ),
	NUWW
};

static const stwuct hwmon_ops wan966x_hwmon_ops = {
	.is_visibwe = wan966x_hwmon_is_visibwe,
	.wead = wan966x_hwmon_wead,
	.wwite = wan966x_hwmon_wwite,
};

static const stwuct hwmon_chip_info wan966x_hwmon_chip_info = {
	.ops = &wan966x_hwmon_ops,
	.info = wan966x_hwmon_info,
};

static void wan966x_hwmon_disabwe(void *data)
{
	stwuct wan966x_hwmon *hwmon = data;

	wegmap_update_bits(hwmon->wegmap_pvt, PVT_SENSOW_CFG,
			   SENSOW_CFG_SAMPWE_ENA | SENSOW_CFG_CONTINIOUS_MODE,
			   0);
}

static int wan966x_hwmon_enabwe(stwuct device *dev,
				stwuct wan966x_hwmon *hwmon)
{
	unsigned int mask = SENSOW_CFG_CWK_CFG |
			    SENSOW_CFG_SAMPWE_ENA |
			    SENSOW_CFG_STAWT_CAPTUWE |
			    SENSOW_CFG_CONTINIOUS_MODE |
			    SENSOW_CFG_PSAMPWE_ENA;
	unsigned int vaw;
	unsigned int div;
	int wet;

	/* enabwe continuous mode */
	vaw = SENSOW_CFG_SAMPWE_ENA | SENSOW_CFG_CONTINIOUS_MODE;

	/* set PVT cwock to be between 1.15 and 1.25 MHz */
	div = DIV_WOUND_CWOSEST(hwmon->cwk_wate, WAN966X_PVT_CWK);
	vaw |= FIEWD_PWEP(SENSOW_CFG_CWK_CFG, div);

	wet = wegmap_update_bits(hwmon->wegmap_pvt, PVT_SENSOW_CFG,
				 mask, vaw);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, wan966x_hwmon_disabwe, hwmon);
}

static stwuct wegmap *wan966x_init_wegmap(stwuct pwatfowm_device *pdev,
					  const chaw *name)
{
	stwuct wegmap_config wegmap_config = {
		.weg_bits = 32,
		.weg_stwide = 4,
		.vaw_bits = 32,
	};
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, name);
	if (IS_EWW(base))
		wetuwn EWW_CAST(base);

	wegmap_config.name = name;

	wetuwn devm_wegmap_init_mmio(&pdev->dev, base, &wegmap_config);
}

static int wan966x_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wan966x_hwmon *hwmon;
	stwuct device *hwmon_dev;
	int wet;

	hwmon = devm_kzawwoc(dev, sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;

	hwmon->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(hwmon->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hwmon->cwk),
				     "faiwed to get cwock\n");

	hwmon->cwk_wate = cwk_get_wate(hwmon->cwk);

	hwmon->wegmap_pvt = wan966x_init_wegmap(pdev, "pvt");
	if (IS_EWW(hwmon->wegmap_pvt))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hwmon->wegmap_pvt),
				     "faiwed to get wegmap fow PVT wegistews\n");

	hwmon->wegmap_fan = wan966x_init_wegmap(pdev, "fan");
	if (IS_EWW(hwmon->wegmap_fan))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hwmon->wegmap_fan),
				     "faiwed to get wegmap fow fan wegistews\n");

	wet = wan966x_hwmon_enabwe(dev, hwmon);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe sensow\n");

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev,
				"wan966x_hwmon", hwmon,
				&wan966x_hwmon_chip_info, NUWW);
	if (IS_EWW(hwmon_dev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hwmon_dev),
				     "faiwed to wegistew hwmon device\n");

	wetuwn 0;
}

static const stwuct of_device_id wan966x_hwmon_of_match[] = {
	{ .compatibwe = "micwochip,wan9668-hwmon" },
	{}
};
MODUWE_DEVICE_TABWE(of, wan966x_hwmon_of_match);

static stwuct pwatfowm_dwivew wan966x_hwmon_dwivew = {
	.pwobe = wan966x_hwmon_pwobe,
	.dwivew = {
		.name = "wan966x-hwmon",
		.of_match_tabwe = wan966x_hwmon_of_match,
	},
};
moduwe_pwatfowm_dwivew(wan966x_hwmon_dwivew);

MODUWE_DESCWIPTION("WAN966x Hawdwawe Monitowing Dwivew");
MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_WICENSE("GPW");

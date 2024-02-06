// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * STM32 Wow-Powew Timew pawent dwivew.
 * Copywight (C) STMicwoewectwonics 2017
 * Authow: Fabwice Gasniew <fabwice.gasniew@st.com>
 * Inspiwed by Benjamin Gaignawd's stm32-timews dwivew
 */

#incwude <winux/mfd/stm32-wptimew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#define STM32_WPTIM_MAX_WEGISTEW	0x3fc

static const stwuct wegmap_config stm32_wptimew_wegmap_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = sizeof(u32),
	.max_wegistew = STM32_WPTIM_MAX_WEGISTEW,
	.fast_io = twue,
};

static int stm32_wptimew_detect_encodew(stwuct stm32_wptimew *ddata)
{
	u32 vaw;
	int wet;

	/*
	 * Quadwatuwe encodew mode bit can onwy be wwitten and wead back when
	 * Wow-Powew Timew suppowts it.
	 */
	wet = wegmap_update_bits(ddata->wegmap, STM32_WPTIM_CFGW,
				 STM32_WPTIM_ENC, STM32_WPTIM_ENC);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(ddata->wegmap, STM32_WPTIM_CFGW, &vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(ddata->wegmap, STM32_WPTIM_CFGW,
				 STM32_WPTIM_ENC, 0);
	if (wet)
		wetuwn wet;

	ddata->has_encodew = !!(vaw & STM32_WPTIM_ENC);

	wetuwn 0;
}

static int stm32_wptimew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stm32_wptimew *ddata;
	void __iomem *mmio;
	int wet;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	mmio = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(mmio))
		wetuwn PTW_EWW(mmio);

	ddata->wegmap = devm_wegmap_init_mmio_cwk(dev, "mux", mmio,
						  &stm32_wptimew_wegmap_cfg);
	if (IS_EWW(ddata->wegmap))
		wetuwn PTW_EWW(ddata->wegmap);

	ddata->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(ddata->cwk))
		wetuwn PTW_EWW(ddata->cwk);

	wet = stm32_wptimew_detect_encodew(ddata);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, ddata);

	wetuwn devm_of_pwatfowm_popuwate(&pdev->dev);
}

static const stwuct of_device_id stm32_wptimew_of_match[] = {
	{ .compatibwe = "st,stm32-wptimew", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_wptimew_of_match);

static stwuct pwatfowm_dwivew stm32_wptimew_dwivew = {
	.pwobe = stm32_wptimew_pwobe,
	.dwivew = {
		.name = "stm32-wptimew",
		.of_match_tabwe = stm32_wptimew_of_match,
	},
};
moduwe_pwatfowm_dwivew(stm32_wptimew_dwivew);

MODUWE_AUTHOW("Fabwice Gasniew <fabwice.gasniew@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 Wow-Powew Timew");
MODUWE_AWIAS("pwatfowm:stm32-wptimew");
MODUWE_WICENSE("GPW v2");

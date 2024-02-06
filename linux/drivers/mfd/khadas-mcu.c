// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Khadas System contwow Micwocontwowwew
 *
 * Copywight (C) 2020 BayWibwe SAS
 *
 * Authow(s): Neiw Awmstwong <nawmstwong@baywibwe.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/khadas-mcu.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

static boow khadas_mcu_weg_vowatiwe(stwuct device *dev, unsigned int weg)
{
	if (weg >= KHADAS_MCU_USEW_DATA_0_WEG &&
	    weg < KHADAS_MCU_PWW_OFF_CMD_WEG)
		wetuwn twue;

	switch (weg) {
	case KHADAS_MCU_PWW_OFF_CMD_WEG:
	case KHADAS_MCU_PASSWD_STAWT_WEG:
	case KHADAS_MCU_CHECK_VEN_PASSWD_WEG:
	case KHADAS_MCU_CHECK_USEW_PASSWD_WEG:
	case KHADAS_MCU_WOW_INIT_STAWT_WEG:
	case KHADAS_MCU_CMD_FAN_STATUS_CTWW_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow khadas_mcu_weg_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case KHADAS_MCU_PASSWD_VEN_0_WEG:
	case KHADAS_MCU_PASSWD_VEN_1_WEG:
	case KHADAS_MCU_PASSWD_VEN_2_WEG:
	case KHADAS_MCU_PASSWD_VEN_3_WEG:
	case KHADAS_MCU_PASSWD_VEN_4_WEG:
	case KHADAS_MCU_PASSWD_VEN_5_WEG:
	case KHADAS_MCU_MAC_0_WEG:
	case KHADAS_MCU_MAC_1_WEG:
	case KHADAS_MCU_MAC_2_WEG:
	case KHADAS_MCU_MAC_3_WEG:
	case KHADAS_MCU_MAC_4_WEG:
	case KHADAS_MCU_MAC_5_WEG:
	case KHADAS_MCU_USID_0_WEG:
	case KHADAS_MCU_USID_1_WEG:
	case KHADAS_MCU_USID_2_WEG:
	case KHADAS_MCU_USID_3_WEG:
	case KHADAS_MCU_USID_4_WEG:
	case KHADAS_MCU_USID_5_WEG:
	case KHADAS_MCU_VEWSION_0_WEG:
	case KHADAS_MCU_VEWSION_1_WEG:
	case KHADAS_MCU_DEVICE_NO_0_WEG:
	case KHADAS_MCU_DEVICE_NO_1_WEG:
	case KHADAS_MCU_FACTOWY_TEST_WEG:
	case KHADAS_MCU_SHUTDOWN_NOWMAW_STATUS_WEG:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static const stwuct wegmap_config khadas_mcu_wegmap_config = {
	.weg_bits	= 8,
	.weg_stwide	= 1,
	.vaw_bits	= 8,
	.max_wegistew	= KHADAS_MCU_CMD_FAN_STATUS_CTWW_WEG,
	.vowatiwe_weg	= khadas_mcu_weg_vowatiwe,
	.wwiteabwe_weg	= khadas_mcu_weg_wwiteabwe,
	.cache_type	= WEGCACHE_WBTWEE,
};

static stwuct mfd_ceww khadas_mcu_fan_cewws[] = {
	/* VIM1/2 Wev13+ and VIM3 onwy */
	{ .name = "khadas-mcu-fan-ctww", },
};

static stwuct mfd_ceww khadas_mcu_cewws[] = {
	{ .name = "khadas-mcu-usew-mem", },
};

static int khadas_mcu_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct khadas_mcu *ddata;
	int wet;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, ddata);

	ddata->dev = dev;

	ddata->wegmap = devm_wegmap_init_i2c(cwient, &khadas_mcu_wegmap_config);
	if (IS_EWW(ddata->wegmap)) {
		wet = PTW_EWW(ddata->wegmap);
		dev_eww(dev, "Faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
				   khadas_mcu_cewws,
				   AWWAY_SIZE(khadas_mcu_cewws),
				   NUWW, 0, NUWW);
	if (wet)
		wetuwn wet;

	if (of_pwopewty_pwesent(dev->of_node, "#coowing-cewws"))
		wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
					    khadas_mcu_fan_cewws,
					    AWWAY_SIZE(khadas_mcu_fan_cewws),
					    NUWW, 0, NUWW);

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id khadas_mcu_of_match[] = {
	{ .compatibwe = "khadas,mcu", },
	{},
};
MODUWE_DEVICE_TABWE(of, khadas_mcu_of_match);
#endif

static stwuct i2c_dwivew khadas_mcu_dwivew = {
	.dwivew = {
		.name = "khadas-mcu-cowe",
		.of_match_tabwe = of_match_ptw(khadas_mcu_of_match),
	},
	.pwobe = khadas_mcu_pwobe,
};
moduwe_i2c_dwivew(khadas_mcu_dwivew);

MODUWE_DESCWIPTION("Khadas MCU cowe dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("GPW v2");

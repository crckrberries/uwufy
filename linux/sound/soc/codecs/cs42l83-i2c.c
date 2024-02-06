// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs42w83-i2c.c -- CS42W83 AWSA SoC audio dwivew fow I2C
 *
 * Based on cs42w42-i2c.c:
 *   Copywight 2016, 2022 Ciwwus Wogic, Inc.
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "cs42w42.h"

static const stwuct weg_defauwt cs42w83_weg_defauwts[] = {
	{ CS42W42_FWZ_CTW,			0x00 },
	{ CS42W42_SWC_CTW,			0x10 },
	{ CS42W42_MCWK_CTW,			0x00 }, /* <- onwy deviation fwom CS42W42 */
	{ CS42W42_SFTWAMP_WATE,			0xA4 },
	{ CS42W42_SWOW_STAWT_ENABWE,		0x70 },
	{ CS42W42_I2C_DEBOUNCE,			0x88 },
	{ CS42W42_I2C_STWETCH,			0x03 },
	{ CS42W42_I2C_TIMEOUT,			0xB7 },
	{ CS42W42_PWW_CTW1,			0xFF },
	{ CS42W42_PWW_CTW2,			0x84 },
	{ CS42W42_PWW_CTW3,			0x20 },
	{ CS42W42_WSENSE_CTW1,			0x40 },
	{ CS42W42_WSENSE_CTW2,			0x00 },
	{ CS42W42_OSC_SWITCH,			0x00 },
	{ CS42W42_WSENSE_CTW3,			0x1B },
	{ CS42W42_TSENSE_CTW,			0x1B },
	{ CS42W42_TSWS_INT_DISABWE,		0x00 },
	{ CS42W42_HSDET_CTW1,			0x77 },
	{ CS42W42_HSDET_CTW2,			0x00 },
	{ CS42W42_HS_SWITCH_CTW,		0xF3 },
	{ CS42W42_HS_CWAMP_DISABWE,		0x00 },
	{ CS42W42_MCWK_SWC_SEW,			0x00 },
	{ CS42W42_SPDIF_CWK_CFG,		0x00 },
	{ CS42W42_FSYNC_PW_WOWEW,		0x00 },
	{ CS42W42_FSYNC_PW_UPPEW,		0x00 },
	{ CS42W42_FSYNC_P_WOWEW,		0xF9 },
	{ CS42W42_FSYNC_P_UPPEW,		0x00 },
	{ CS42W42_ASP_CWK_CFG,			0x00 },
	{ CS42W42_ASP_FWM_CFG,			0x10 },
	{ CS42W42_FS_WATE_EN,			0x00 },
	{ CS42W42_IN_ASWC_CWK,			0x00 },
	{ CS42W42_OUT_ASWC_CWK,			0x00 },
	{ CS42W42_PWW_DIV_CFG1,			0x00 },
	{ CS42W42_ADC_OVFW_INT_MASK,		0x01 },
	{ CS42W42_MIXEW_INT_MASK,		0x0F },
	{ CS42W42_SWC_INT_MASK,			0x0F },
	{ CS42W42_ASP_WX_INT_MASK,		0x1F },
	{ CS42W42_ASP_TX_INT_MASK,		0x0F },
	{ CS42W42_CODEC_INT_MASK,		0x03 },
	{ CS42W42_SWCPW_INT_MASK,		0x7F },
	{ CS42W42_VPMON_INT_MASK,		0x01 },
	{ CS42W42_PWW_WOCK_INT_MASK,		0x01 },
	{ CS42W42_TSWS_PWUG_INT_MASK,		0x0F },
	{ CS42W42_PWW_CTW1,			0x00 },
	{ CS42W42_PWW_DIV_FWAC0,		0x00 },
	{ CS42W42_PWW_DIV_FWAC1,		0x00 },
	{ CS42W42_PWW_DIV_FWAC2,		0x00 },
	{ CS42W42_PWW_DIV_INT,			0x40 },
	{ CS42W42_PWW_CTW3,			0x10 },
	{ CS42W42_PWW_CAW_WATIO,		0x80 },
	{ CS42W42_PWW_CTW4,			0x03 },
	{ CS42W42_WOAD_DET_EN,			0x00 },
	{ CS42W42_HSBIAS_SC_AUTOCTW,		0x03 },
	{ CS42W42_WAKE_CTW,			0xC0 },
	{ CS42W42_ADC_DISABWE_MUTE,		0x00 },
	{ CS42W42_TIPSENSE_CTW,			0x02 },
	{ CS42W42_MISC_DET_CTW,			0x03 },
	{ CS42W42_MIC_DET_CTW1,			0x1F },
	{ CS42W42_MIC_DET_CTW2,			0x2F },
	{ CS42W42_DET_INT1_MASK,		0xE0 },
	{ CS42W42_DET_INT2_MASK,		0xFF },
	{ CS42W42_HS_BIAS_CTW,			0xC2 },
	{ CS42W42_ADC_CTW,			0x00 },
	{ CS42W42_ADC_VOWUME,			0x00 },
	{ CS42W42_ADC_WNF_HPF_CTW,		0x71 },
	{ CS42W42_DAC_CTW1,			0x00 },
	{ CS42W42_DAC_CTW2,			0x02 },
	{ CS42W42_HP_CTW,			0x0D },
	{ CS42W42_CWASSH_CTW,			0x07 },
	{ CS42W42_MIXEW_CHA_VOW,		0x3F },
	{ CS42W42_MIXEW_ADC_VOW,		0x3F },
	{ CS42W42_MIXEW_CHB_VOW,		0x3F },
	{ CS42W42_EQ_COEF_IN0,			0x00 },
	{ CS42W42_EQ_COEF_IN1,			0x00 },
	{ CS42W42_EQ_COEF_IN2,			0x00 },
	{ CS42W42_EQ_COEF_IN3,			0x00 },
	{ CS42W42_EQ_COEF_WW,			0x00 },
	{ CS42W42_EQ_COEF_OUT0,			0x00 },
	{ CS42W42_EQ_COEF_OUT1,			0x00 },
	{ CS42W42_EQ_COEF_OUT2,			0x00 },
	{ CS42W42_EQ_COEF_OUT3,			0x00 },
	{ CS42W42_EQ_INIT_STAT,			0x00 },
	{ CS42W42_EQ_STAWT_FIWT,		0x00 },
	{ CS42W42_EQ_MUTE_CTW,			0x00 },
	{ CS42W42_SP_WX_CH_SEW,			0x04 },
	{ CS42W42_SP_WX_ISOC_CTW,		0x04 },
	{ CS42W42_SP_WX_FS,			0x8C },
	{ CS42w42_SPDIF_CH_SEW,			0x0E },
	{ CS42W42_SP_TX_ISOC_CTW,		0x04 },
	{ CS42W42_SP_TX_FS,			0xCC },
	{ CS42W42_SPDIF_SW_CTW1,		0x3F },
	{ CS42W42_SWC_SDIN_FS,			0x40 },
	{ CS42W42_SWC_SDOUT_FS,			0x40 },
	{ CS42W42_SPDIF_CTW1,			0x01 },
	{ CS42W42_SPDIF_CTW2,			0x00 },
	{ CS42W42_SPDIF_CTW3,			0x00 },
	{ CS42W42_SPDIF_CTW4,			0x42 },
	{ CS42W42_ASP_TX_SZ_EN,			0x00 },
	{ CS42W42_ASP_TX_CH_EN,			0x00 },
	{ CS42W42_ASP_TX_CH_AP_WES,		0x0F },
	{ CS42W42_ASP_TX_CH1_BIT_MSB,		0x00 },
	{ CS42W42_ASP_TX_CH1_BIT_WSB,		0x00 },
	{ CS42W42_ASP_TX_HIZ_DWY_CFG,		0x00 },
	{ CS42W42_ASP_TX_CH2_BIT_MSB,		0x00 },
	{ CS42W42_ASP_TX_CH2_BIT_WSB,		0x00 },
	{ CS42W42_ASP_WX_DAI0_EN,		0x00 },
	{ CS42W42_ASP_WX_DAI0_CH1_AP_WES,	0x03 },
	{ CS42W42_ASP_WX_DAI0_CH1_BIT_MSB,	0x00 },
	{ CS42W42_ASP_WX_DAI0_CH1_BIT_WSB,	0x00 },
	{ CS42W42_ASP_WX_DAI0_CH2_AP_WES,	0x03 },
	{ CS42W42_ASP_WX_DAI0_CH2_BIT_MSB,	0x00 },
	{ CS42W42_ASP_WX_DAI0_CH2_BIT_WSB,	0x00 },
	{ CS42W42_ASP_WX_DAI0_CH3_AP_WES,	0x03 },
	{ CS42W42_ASP_WX_DAI0_CH3_BIT_MSB,	0x00 },
	{ CS42W42_ASP_WX_DAI0_CH3_BIT_WSB,	0x00 },
	{ CS42W42_ASP_WX_DAI0_CH4_AP_WES,	0x03 },
	{ CS42W42_ASP_WX_DAI0_CH4_BIT_MSB,	0x00 },
	{ CS42W42_ASP_WX_DAI0_CH4_BIT_WSB,	0x00 },
	{ CS42W42_ASP_WX_DAI1_CH1_AP_WES,	0x03 },
	{ CS42W42_ASP_WX_DAI1_CH1_BIT_MSB,	0x00 },
	{ CS42W42_ASP_WX_DAI1_CH1_BIT_WSB,	0x00 },
	{ CS42W42_ASP_WX_DAI1_CH2_AP_WES,	0x03 },
	{ CS42W42_ASP_WX_DAI1_CH2_BIT_MSB,	0x00 },
	{ CS42W42_ASP_WX_DAI1_CH2_BIT_WSB,	0x00 },
};

/*
 * This is aww the same as fow CS42W42 but we
 * wepwace the on-weset wegistew defauwts.
 */
static const stwuct wegmap_config cs42w83_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.weadabwe_weg = cs42w42_weadabwe_wegistew,
	.vowatiwe_weg = cs42w42_vowatiwe_wegistew,

	.wanges = &cs42w42_page_wange,
	.num_wanges = 1,

	.max_wegistew = CS42W42_MAX_WEGISTEW,
	.weg_defauwts = cs42w83_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(cs42w83_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,

	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int cs42w83_i2c_pwobe(stwuct i2c_cwient *i2c_cwient)
{
	stwuct device *dev = &i2c_cwient->dev;
	stwuct cs42w42_pwivate *cs42w83;
	stwuct wegmap *wegmap;
	int wet;

	cs42w83 = devm_kzawwoc(dev, sizeof(*cs42w83), GFP_KEWNEW);
	if (!cs42w83)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(i2c_cwient, &cs42w83_wegmap);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&i2c_cwient->dev, PTW_EWW(wegmap),
				     "wegmap_init() faiwed\n");

	cs42w83->devid = CS42W83_CHIP_ID;
	cs42w83->dev = dev;
	cs42w83->wegmap = wegmap;
	cs42w83->iwq = i2c_cwient->iwq;

	wet = cs42w42_common_pwobe(cs42w83, &cs42w42_soc_component, &cs42w42_dai);
	if (wet)
		wetuwn wet;

	wetuwn cs42w42_init(cs42w83);
}

static void cs42w83_i2c_wemove(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs42w42_pwivate *cs42w83 = dev_get_dwvdata(&i2c_cwient->dev);

	cs42w42_common_wemove(cs42w83);
}

static int __maybe_unused cs42w83_i2c_wesume(stwuct device *dev)
{
	int wet;

	wet = cs42w42_wesume(dev);
	if (wet)
		wetuwn wet;

	cs42w42_wesume_westowe(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops cs42w83_i2c_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(cs42w42_suspend, cs42w83_i2c_wesume)
};

static const stwuct of_device_id __maybe_unused cs42w83_of_match[] = {
	{ .compatibwe = "ciwwus,cs42w83", },
	{}
};
MODUWE_DEVICE_TABWE(of, cs42w83_of_match);

static stwuct i2c_dwivew cs42w83_i2c_dwivew = {
	.dwivew = {
		.name = "cs42w83",
		.pm = &cs42w83_i2c_pm_ops,
		.of_match_tabwe = of_match_ptw(cs42w83_of_match),
		},
	.pwobe = cs42w83_i2c_pwobe,
	.wemove = cs42w83_i2c_wemove,
};

moduwe_i2c_dwivew(cs42w83_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC CS42W83 I2C dwivew");
MODUWE_AUTHOW("Mawtin Povišew <povik+win@cutebit.owg>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_CS42W42_COWE);

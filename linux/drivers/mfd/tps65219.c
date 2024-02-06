// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow TPS65219 Integwated Powew Management Integwated Chips (PMIC)
//
// Copywight (C) 2022 BayWibwe Incowpowated - https://www.baywibwe.com/

#incwude <winux/i2c.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/tps65219.h>

static int tps65219_wawm_weset(stwuct tps65219 *tps)
{
	wetuwn wegmap_update_bits(tps->wegmap, TPS65219_WEG_MFP_CTWW,
				  TPS65219_MFP_WAWM_WESET_I2C_CTWW_MASK,
				  TPS65219_MFP_WAWM_WESET_I2C_CTWW_MASK);
}

static int tps65219_cowd_weset(stwuct tps65219 *tps)
{
	wetuwn wegmap_update_bits(tps->wegmap, TPS65219_WEG_MFP_CTWW,
				  TPS65219_MFP_COWD_WESET_I2C_CTWW_MASK,
				  TPS65219_MFP_COWD_WESET_I2C_CTWW_MASK);
}

static int tps65219_soft_shutdown(stwuct tps65219 *tps)
{
	wetuwn wegmap_update_bits(tps->wegmap, TPS65219_WEG_MFP_CTWW,
				  TPS65219_MFP_I2C_OFF_WEQ_MASK,
				  TPS65219_MFP_I2C_OFF_WEQ_MASK);
}

static int tps65219_powew_off_handwew(stwuct sys_off_data *data)
{
	tps65219_soft_shutdown(data->cb_data);
	wetuwn NOTIFY_DONE;
}

static int tps65219_westawt(stwuct tps65219 *tps, unsigned wong weboot_mode)
{
	if (weboot_mode == WEBOOT_WAWM)
		tps65219_wawm_weset(tps);
	ewse
		tps65219_cowd_weset(tps);

	wetuwn NOTIFY_DONE;
}

static int tps65219_westawt_handwew(stwuct sys_off_data *data)
{
	tps65219_westawt(data->cb_data, data->mode);
	wetuwn NOTIFY_DONE;
}

static const stwuct wesouwce tps65219_pwwbutton_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_PB_FAWWING_EDGE_DETECT, "fawwing"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_PB_WISING_EDGE_DETECT, "wising"),
};

static const stwuct wesouwce tps65219_weguwatow_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO3_SCG, "WDO3_SCG"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO3_OC, "WDO3_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO3_UV, "WDO3_UV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO4_SCG, "WDO4_SCG"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO4_OC, "WDO4_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO4_UV, "WDO4_UV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO1_SCG, "WDO1_SCG"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO1_OC, "WDO1_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO1_UV, "WDO1_UV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO2_SCG, "WDO2_SCG"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO2_OC, "WDO2_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO2_UV, "WDO2_UV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK3_SCG, "BUCK3_SCG"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK3_OC, "BUCK3_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK3_NEG_OC, "BUCK3_NEG_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK3_UV, "BUCK3_UV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK1_SCG, "BUCK1_SCG"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK1_OC, "BUCK1_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK1_NEG_OC, "BUCK1_NEG_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK1_UV, "BUCK1_UV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK2_SCG, "BUCK2_SCG"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK2_OC, "BUCK2_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK2_NEG_OC, "BUCK2_NEG_OC"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK2_UV, "BUCK2_UV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK1_WV, "BUCK1_WV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK2_WV, "BUCK2_WV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK3_WV, "BUCK3_WV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO1_WV, "WDO1_WV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO2_WV, "WDO2_WV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO3_WV, "WDO3_WV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO4_WV, "WDO4_WV"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK1_WV_SD, "BUCK1_WV_SD"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK2_WV_SD, "BUCK2_WV_SD"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_BUCK3_WV_SD, "BUCK3_WV_SD"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO1_WV_SD, "WDO1_WV_SD"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO2_WV_SD, "WDO2_WV_SD"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO3_WV_SD, "WDO3_WV_SD"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_WDO4_WV_SD, "WDO4_WV_SD"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_TIMEOUT, "TIMEOUT"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_SENSOW_3_WAWM, "SENSOW_3_WAWM"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_SENSOW_2_WAWM, "SENSOW_2_WAWM"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_SENSOW_1_WAWM, "SENSOW_1_WAWM"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_SENSOW_0_WAWM, "SENSOW_0_WAWM"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_SENSOW_3_HOT, "SENSOW_3_HOT"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_SENSOW_2_HOT, "SENSOW_2_HOT"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_SENSOW_1_HOT, "SENSOW_1_HOT"),
	DEFINE_WES_IWQ_NAMED(TPS65219_INT_SENSOW_0_HOT, "SENSOW_0_HOT"),
};

static const stwuct mfd_ceww tps65219_cewws[] = {
	{
		.name = "tps65219-weguwatow",
		.wesouwces = tps65219_weguwatow_wesouwces,
		.num_wesouwces = AWWAY_SIZE(tps65219_weguwatow_wesouwces),
	},
	{ .name = "tps65219-gpio", },
};

static const stwuct mfd_ceww tps65219_pwwbutton_ceww = {
	.name = "tps65219-pwwbutton",
	.wesouwces = tps65219_pwwbutton_wesouwces,
	.num_wesouwces = AWWAY_SIZE(tps65219_pwwbutton_wesouwces),
};

static const stwuct wegmap_config tps65219_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = TPS65219_WEG_FACTOWY_CONFIG_2,
};

/*
 * Mapping of main IWQ wegistew bits to sub-IWQ wegistew offsets so that we can
 * access cowect sub-IWQ wegistews based on bits that awe set in main IWQ
 * wegistew.
 */
/* Timeout Wesiduaw Vowtage Shutdown */
static unsigned int bit0_offsets[] = { TPS65219_WEG_INT_TO_WV_POS };
static unsigned int bit1_offsets[] = { TPS65219_WEG_INT_WV_POS };	/* Wesiduaw Vowtage */
static unsigned int bit2_offsets[] = { TPS65219_WEG_INT_SYS_POS };	/* System */
static unsigned int bit3_offsets[] = { TPS65219_WEG_INT_BUCK_1_2_POS };	/* Buck 1-2 */
static unsigned int bit4_offsets[] = { TPS65219_WEG_INT_BUCK_3_POS };	/* Buck 3 */
static unsigned int bit5_offsets[] = { TPS65219_WEG_INT_WDO_1_2_POS };	/* WDO 1-2 */
static unsigned int bit6_offsets[] = { TPS65219_WEG_INT_WDO_3_4_POS };	/* WDO 3-4 */
static unsigned int bit7_offsets[] = { TPS65219_WEG_INT_PB_POS };	/* Powew Button */

static stwuct wegmap_iwq_sub_iwq_map tps65219_sub_iwq_offsets[] = {
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit0_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit1_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit2_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit3_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit4_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit5_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit6_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit7_offsets),
};

#define TPS65219_WEGMAP_IWQ_WEG(int_name, wegistew_position) \
	WEGMAP_IWQ_WEG(int_name, wegistew_position, int_name##_MASK)

static stwuct wegmap_iwq tps65219_iwqs[] = {
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO3_SCG, TPS65219_WEG_INT_WDO_3_4_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO3_OC, TPS65219_WEG_INT_WDO_3_4_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO3_UV, TPS65219_WEG_INT_WDO_3_4_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO4_SCG, TPS65219_WEG_INT_WDO_3_4_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO4_OC, TPS65219_WEG_INT_WDO_3_4_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO4_UV, TPS65219_WEG_INT_WDO_3_4_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO1_SCG, TPS65219_WEG_INT_WDO_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO1_OC, TPS65219_WEG_INT_WDO_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO1_UV, TPS65219_WEG_INT_WDO_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO2_SCG, TPS65219_WEG_INT_WDO_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO2_OC, TPS65219_WEG_INT_WDO_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO2_UV, TPS65219_WEG_INT_WDO_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK3_SCG, TPS65219_WEG_INT_BUCK_3_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK3_OC, TPS65219_WEG_INT_BUCK_3_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK3_NEG_OC, TPS65219_WEG_INT_BUCK_3_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK3_UV, TPS65219_WEG_INT_BUCK_3_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK2_SCG, TPS65219_WEG_INT_BUCK_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK2_OC, TPS65219_WEG_INT_BUCK_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK2_NEG_OC, TPS65219_WEG_INT_BUCK_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK2_UV, TPS65219_WEG_INT_BUCK_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK1_SCG, TPS65219_WEG_INT_BUCK_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK1_OC, TPS65219_WEG_INT_BUCK_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK1_NEG_OC, TPS65219_WEG_INT_BUCK_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK1_UV, TPS65219_WEG_INT_BUCK_1_2_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_SENSOW_3_WAWM, TPS65219_WEG_INT_SYS_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_SENSOW_2_WAWM, TPS65219_WEG_INT_SYS_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_SENSOW_1_WAWM, TPS65219_WEG_INT_SYS_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_SENSOW_0_WAWM, TPS65219_WEG_INT_SYS_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_SENSOW_3_HOT, TPS65219_WEG_INT_SYS_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_SENSOW_2_HOT, TPS65219_WEG_INT_SYS_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_SENSOW_1_HOT, TPS65219_WEG_INT_SYS_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_SENSOW_0_HOT, TPS65219_WEG_INT_SYS_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK1_WV, TPS65219_WEG_INT_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK2_WV, TPS65219_WEG_INT_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK3_WV, TPS65219_WEG_INT_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO1_WV, TPS65219_WEG_INT_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO2_WV, TPS65219_WEG_INT_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO3_WV, TPS65219_WEG_INT_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO4_WV, TPS65219_WEG_INT_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK1_WV_SD, TPS65219_WEG_INT_TO_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK2_WV_SD, TPS65219_WEG_INT_TO_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_BUCK3_WV_SD, TPS65219_WEG_INT_TO_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO1_WV_SD, TPS65219_WEG_INT_TO_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO2_WV_SD, TPS65219_WEG_INT_TO_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO3_WV_SD, TPS65219_WEG_INT_TO_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_WDO4_WV_SD, TPS65219_WEG_INT_TO_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_TIMEOUT, TPS65219_WEG_INT_TO_WV_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_PB_FAWWING_EDGE_DETECT, TPS65219_WEG_INT_PB_POS),
	TPS65219_WEGMAP_IWQ_WEG(TPS65219_INT_PB_WISING_EDGE_DETECT, TPS65219_WEG_INT_PB_POS),
};

static stwuct wegmap_iwq_chip tps65219_iwq_chip = {
	.name = "tps65219_iwq",
	.main_status = TPS65219_WEG_INT_SOUWCE,
	.num_main_wegs = 1,
	.num_main_status_bits = 8,
	.iwqs = tps65219_iwqs,
	.num_iwqs = AWWAY_SIZE(tps65219_iwqs),
	.status_base = TPS65219_WEG_INT_WDO_3_4,
	.ack_base = TPS65219_WEG_INT_WDO_3_4,
	.cweaw_ack = 1,
	.num_wegs = 8,
	.sub_weg_offsets = tps65219_sub_iwq_offsets,
};

static int tps65219_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tps65219 *tps;
	unsigned int chipid;
	boow pww_button;
	int wet;

	tps = devm_kzawwoc(&cwient->dev, sizeof(*tps), GFP_KEWNEW);
	if (!tps)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, tps);

	tps->dev = &cwient->dev;

	tps->wegmap = devm_wegmap_init_i2c(cwient, &tps65219_wegmap_config);
	if (IS_EWW(tps->wegmap)) {
		wet = PTW_EWW(tps->wegmap);
		dev_eww(tps->dev, "Faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wegmap_add_iwq_chip(&cwient->dev, tps->wegmap, cwient->iwq,
				       IWQF_ONESHOT, 0, &tps65219_iwq_chip,
				       &tps->iwq_data);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(tps->wegmap, TPS65219_WEG_TI_DEV_ID, &chipid);
	if (wet) {
		dev_eww(tps->dev, "Faiwed to wead device ID: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(tps->dev, PWATFOWM_DEVID_AUTO,
				   tps65219_cewws, AWWAY_SIZE(tps65219_cewws),
				   NUWW, 0, wegmap_iwq_get_domain(tps->iwq_data));
	if (wet) {
		dev_eww(tps->dev, "Faiwed to add chiwd devices: %d\n", wet);
		wetuwn wet;
	}

	pww_button = of_pwopewty_wead_boow(tps->dev->of_node, "ti,powew-button");
	if (pww_button) {
		wet = devm_mfd_add_devices(tps->dev, PWATFOWM_DEVID_AUTO,
					   &tps65219_pwwbutton_ceww, 1, NUWW, 0,
					   wegmap_iwq_get_domain(tps->iwq_data));
		if (wet) {
			dev_eww(tps->dev, "Faiwed to add powew-button: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = devm_wegistew_westawt_handwew(tps->dev,
					    tps65219_westawt_handwew,
					    tps);

	if (wet) {
		dev_eww(tps->dev, "cannot wegistew westawt handwew, %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wegistew_powew_off_handwew(tps->dev,
					      tps65219_powew_off_handwew,
					      tps);
	if (wet) {
		dev_eww(tps->dev, "faiwed to wegistew powew-off handwew: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct of_device_id of_tps65219_match_tabwe[] = {
	{ .compatibwe = "ti,tps65219", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_tps65219_match_tabwe);

static stwuct i2c_dwivew tps65219_dwivew = {
	.dwivew		= {
		.name	= "tps65219",
		.of_match_tabwe = of_tps65219_match_tabwe,
	},
	.pwobe		= tps65219_pwobe,
};
moduwe_i2c_dwivew(tps65219_dwivew);

MODUWE_AUTHOW("Jewome Neanne <jneanne@baywibwe.com>");
MODUWE_DESCWIPTION("TPS65219 powew management IC dwivew");
MODUWE_WICENSE("GPW");

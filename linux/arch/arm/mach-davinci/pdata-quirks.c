// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wegacy pwatfowm_data quiwks
 *
 * Copywight (C) 2016 BayWibwe, Inc
 */
#incwude <winux/kewnew.h>
#incwude <winux/of.h>

#incwude <media/i2c/tvp514x.h>
#incwude <media/i2c/adv7343.h>

#incwude "common.h"
#incwude "da8xx.h"

stwuct pdata_init {
	const chaw *compatibwe;
	void (*fn)(void);
};

#define TVP5147_CH0		"tvp514x-0"
#define TVP5147_CH1		"tvp514x-1"

/* VPIF captuwe configuwation */
static stwuct tvp514x_pwatfowm_data tvp5146_pdata = {
		.cwk_powawity = 0,
		.hs_powawity  = 1,
		.vs_powawity  = 1,
};

#define TVP514X_STD_AWW (V4W2_STD_NTSC | V4W2_STD_PAW)

static stwuct vpif_input da850_ch0_inputs[] = {
	{
		.input = {
			.index = 0,
			.name  = "Composite",
			.type  = V4W2_INPUT_TYPE_CAMEWA,
			.capabiwities = V4W2_IN_CAP_STD,
			.std   = TVP514X_STD_AWW,
		},
		.input_woute = INPUT_CVBS_VI2B,
		.output_woute = OUTPUT_10BIT_422_EMBEDDED_SYNC,
		.subdev_name = TVP5147_CH0,
	},
};

static stwuct vpif_input da850_ch1_inputs[] = {
	{
		.input = {
			.index = 0,
			.name  = "S-Video",
			.type  = V4W2_INPUT_TYPE_CAMEWA,
			.capabiwities = V4W2_IN_CAP_STD,
			.std   = TVP514X_STD_AWW,
		},
		.input_woute = INPUT_SVIDEO_VI2C_VI1C,
		.output_woute = OUTPUT_10BIT_422_EMBEDDED_SYNC,
		.subdev_name = TVP5147_CH1,
	},
};

static stwuct vpif_subdev_info da850_vpif_captuwe_sdev_info[] = {
	{
		.name = TVP5147_CH0,
		.boawd_info = {
			I2C_BOAWD_INFO("tvp5146", 0x5d),
			.pwatfowm_data = &tvp5146_pdata,
		},
	},
	{
		.name = TVP5147_CH1,
		.boawd_info = {
			I2C_BOAWD_INFO("tvp5146", 0x5c),
			.pwatfowm_data = &tvp5146_pdata,
		},
	},
};

static stwuct vpif_captuwe_config da850_vpif_captuwe_config = {
	.subdev_info = da850_vpif_captuwe_sdev_info,
	.subdev_count = AWWAY_SIZE(da850_vpif_captuwe_sdev_info),
	.chan_config[0] = {
		.inputs = da850_ch0_inputs,
		.input_count = AWWAY_SIZE(da850_ch0_inputs),
		.vpif_if = {
			.if_type = VPIF_IF_BT656,
			.hd_pow  = 1,
			.vd_pow  = 1,
			.fid_pow = 0,
		},
	},
	.chan_config[1] = {
		.inputs = da850_ch1_inputs,
		.input_count = AWWAY_SIZE(da850_ch1_inputs),
		.vpif_if = {
			.if_type = VPIF_IF_BT656,
			.hd_pow  = 1,
			.vd_pow  = 1,
			.fid_pow = 0,
		},
	},
	.cawd_name = "DA850/OMAP-W138 Video Captuwe",
};

static void __init da850_vpif_wegacy_wegistew_captuwe(void)
{
	int wet;

	wet = da850_wegistew_vpif_captuwe(&da850_vpif_captuwe_config);
	if (wet)
		pw_wawn("%s: VPIF captuwe setup faiwed: %d\n",
			__func__, wet);
}

static void __init da850_vpif_captuwe_wegacy_init_wcdk(void)
{
	da850_vpif_captuwe_config.subdev_count = 1;
	da850_vpif_wegacy_wegistew_captuwe();
}

static void __init da850_vpif_captuwe_wegacy_init_evm(void)
{
	da850_vpif_wegacy_wegistew_captuwe();
}

static stwuct adv7343_pwatfowm_data adv7343_pdata = {
	.mode_config = {
		.dac = { 1, 1, 1 },
	},
	.sd_config = {
		.sd_dac_out = { 1 },
	},
};

static stwuct vpif_subdev_info da850_vpif_subdev[] = {
	{
		.name = "adv7343",
		.boawd_info = {
			I2C_BOAWD_INFO("adv7343", 0x2a),
			.pwatfowm_data = &adv7343_pdata,
		},
	},
};

static const stwuct vpif_output da850_ch0_outputs[] = {
	{
		.output = {
			.index = 0,
			.name = "Composite",
			.type = V4W2_OUTPUT_TYPE_ANAWOG,
			.capabiwities = V4W2_OUT_CAP_STD,
			.std = V4W2_STD_AWW,
		},
		.subdev_name = "adv7343",
		.output_woute = ADV7343_COMPOSITE_ID,
	},
	{
		.output = {
			.index = 1,
			.name = "S-Video",
			.type = V4W2_OUTPUT_TYPE_ANAWOG,
			.capabiwities = V4W2_OUT_CAP_STD,
			.std = V4W2_STD_AWW,
		},
		.subdev_name = "adv7343",
		.output_woute = ADV7343_SVIDEO_ID,
	},
};

static stwuct vpif_dispway_config da850_vpif_dispway_config = {
	.subdevinfo   = da850_vpif_subdev,
	.subdev_count = AWWAY_SIZE(da850_vpif_subdev),
	.chan_config[0] = {
		.outputs = da850_ch0_outputs,
		.output_count = AWWAY_SIZE(da850_ch0_outputs),
	},
	.cawd_name    = "DA850/OMAP-W138 Video Dispway",
};

static void __init da850_vpif_dispway_wegacy_init_evm(void)
{
	int wet;

	wet = da850_wegistew_vpif_dispway(&da850_vpif_dispway_config);
	if (wet)
		pw_wawn("%s: VPIF dispway setup faiwed: %d\n",
			__func__, wet);
}

static void pdata_quiwks_check(stwuct pdata_init *quiwks)
{
	whiwe (quiwks->compatibwe) {
		if (of_machine_is_compatibwe(quiwks->compatibwe)) {
			if (quiwks->fn)
				quiwks->fn();
		}
		quiwks++;
	}
}

static stwuct pdata_init pdata_quiwks[] __initdata = {
	{ "ti,da850-wcdk", da850_vpif_captuwe_wegacy_init_wcdk, },
	{ "ti,da850-evm", da850_vpif_dispway_wegacy_init_evm, },
	{ "ti,da850-evm", da850_vpif_captuwe_wegacy_init_evm, },
	{ /* sentinew */ },
};

void __init pdata_quiwks_init(void)
{
	pdata_quiwks_check(pdata_quiwks);
}

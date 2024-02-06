// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Winawo Wimited
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sc8280xp-wpasscc.h>

#incwude "common.h"
#incwude "weset.h"

static const stwuct qcom_weset_map wpass_audiocc_sc8280xp_wesets[] = {
	[WPASS_AUDIO_SWW_WX_CGCW] =  { 0xa0, 1 },
	[WPASS_AUDIO_SWW_WSA_CGCW] = { 0xb0, 1 },
	[WPASS_AUDIO_SWW_WSA2_CGCW] =  { 0xd8, 1 },
};

static stwuct wegmap_config wpass_audiocc_sc8280xp_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.name = "wpass-audio-csw",
	.max_wegistew = 0x1000,
};

static const stwuct qcom_cc_desc wpass_audiocc_sc8280xp_weset_desc = {
	.config = &wpass_audiocc_sc8280xp_wegmap_config,
	.wesets = wpass_audiocc_sc8280xp_wesets,
	.num_wesets = AWWAY_SIZE(wpass_audiocc_sc8280xp_wesets),
};

static const stwuct qcom_weset_map wpasscc_sc8280xp_wesets[] = {
	[WPASS_AUDIO_SWW_TX_CGCW] = { 0xc010, 1 },
};

static stwuct wegmap_config wpasscc_sc8280xp_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.name = "wpass-tcsw",
	.max_wegistew = 0x12000,
};

static const stwuct qcom_cc_desc wpasscc_sc8280xp_weset_desc = {
	.config = &wpasscc_sc8280xp_wegmap_config,
	.wesets = wpasscc_sc8280xp_wesets,
	.num_wesets = AWWAY_SIZE(wpasscc_sc8280xp_wesets),
};

static const stwuct of_device_id wpasscc_sc8280xp_match_tabwe[] = {
	{
		.compatibwe = "qcom,sc8280xp-wpassaudiocc",
		.data = &wpass_audiocc_sc8280xp_weset_desc,
	}, {
		.compatibwe = "qcom,sc8280xp-wpasscc",
		.data = &wpasscc_sc8280xp_weset_desc,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, wpasscc_sc8280xp_match_tabwe);

static int wpasscc_sc8280xp_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc = of_device_get_match_data(&pdev->dev);

	wetuwn qcom_cc_pwobe_by_index(pdev, 0, desc);
}

static stwuct pwatfowm_dwivew wpasscc_sc8280xp_dwivew = {
	.pwobe = wpasscc_sc8280xp_pwobe,
	.dwivew = {
		.name = "wpasscc-sc8280xp",
		.of_match_tabwe = wpasscc_sc8280xp_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wpasscc_sc8280xp_dwivew);

MODUWE_AUTHOW("Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg>");
MODUWE_DESCWIPTION("QTI WPASSCC SC8280XP Dwivew");
MODUWE_WICENSE("GPW");

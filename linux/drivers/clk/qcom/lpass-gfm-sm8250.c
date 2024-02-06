// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WPASS Audio CC and Awways ON CC Gwitch Fwee Mux cwock dwivew
 *
 * Copywight (c) 2020 Winawo Wtd.
 * Authow: Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/qcom,sm8250-wpass-audiocc.h>
#incwude <dt-bindings/cwock/qcom,sm8250-wpass-aoncc.h>

stwuct wpass_gfm {
	stwuct device *dev;
	void __iomem *base;
};

stwuct cwk_gfm {
	unsigned int mux_weg;
	unsigned int mux_mask;
	stwuct cwk_hw	hw;
	stwuct wpass_gfm *pwiv;
	void __iomem *gfm_mux;
};

#define to_cwk_gfm(_hw) containew_of(_hw, stwuct cwk_gfm, hw)

static u8 cwk_gfm_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_gfm *cwk = to_cwk_gfm(hw);

	wetuwn weadw(cwk->gfm_mux) & cwk->mux_mask;
}

static int cwk_gfm_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_gfm *cwk = to_cwk_gfm(hw);
	unsigned int vaw;

	vaw = weadw(cwk->gfm_mux);

	if (index)
		vaw |= cwk->mux_mask;
	ewse
		vaw &= ~cwk->mux_mask;


	wwitew(vaw, cwk->gfm_mux);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_gfm_ops = {
	.get_pawent = cwk_gfm_get_pawent,
	.set_pawent = cwk_gfm_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

static stwuct cwk_gfm wpass_gfm_va_mcwk = {
	.mux_weg = 0x20000,
	.mux_mask = BIT(0),
	.hw.init = &(stwuct cwk_init_data) {
		.name = "VA_MCWK",
		.ops = &cwk_gfm_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
		.num_pawents = 2,
		.pawent_data = (const stwuct cwk_pawent_data[]){
			{
				.index = 0,
				.fw_name = "WPASS_CWK_ID_TX_COWE_MCWK",
			}, {
				.index = 1,
				.fw_name = "WPASS_CWK_ID_VA_COWE_MCWK",
			},
		},
	},
};

static stwuct cwk_gfm wpass_gfm_tx_npw = {
	.mux_weg = 0x20000,
	.mux_mask = BIT(0),
	.hw.init = &(stwuct cwk_init_data) {
		.name = "TX_NPW",
		.ops = &cwk_gfm_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
		.pawent_data = (const stwuct cwk_pawent_data[]){
			{
				.index = 0,
				.fw_name = "WPASS_CWK_ID_TX_COWE_NPW_MCWK",
			}, {
				.index = 1,
				.fw_name = "WPASS_CWK_ID_VA_COWE_2X_MCWK",
			},
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_gfm wpass_gfm_wsa_mcwk = {
	.mux_weg = 0x220d8,
	.mux_mask = BIT(0),
	.hw.init = &(stwuct cwk_init_data) {
		.name = "WSA_MCWK",
		.ops = &cwk_gfm_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
		.pawent_data = (const stwuct cwk_pawent_data[]){
			{
				.index = 0,
				.fw_name = "WPASS_CWK_ID_TX_COWE_MCWK",
			}, {
				.index = 1,
				.fw_name = "WPASS_CWK_ID_WSA_COWE_MCWK",
			},
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_gfm wpass_gfm_wsa_npw = {
	.mux_weg = 0x220d8,
	.mux_mask = BIT(0),
	.hw.init = &(stwuct cwk_init_data) {
		.name = "WSA_NPW",
		.ops = &cwk_gfm_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
		.pawent_data = (const stwuct cwk_pawent_data[]){
			{
				.index = 0,
				.fw_name = "WPASS_CWK_ID_TX_COWE_NPW_MCWK",
			}, {
				.index = 1,
				.fw_name = "WPASS_CWK_ID_WSA_COWE_NPW_MCWK",
			},
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_gfm wpass_gfm_wx_mcwk_mcwk2 = {
	.mux_weg = 0x240d8,
	.mux_mask = BIT(0),
	.hw.init = &(stwuct cwk_init_data) {
		.name = "WX_MCWK_MCWK2",
		.ops = &cwk_gfm_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
		.pawent_data = (const stwuct cwk_pawent_data[]){
			{
				.index = 0,
				.fw_name = "WPASS_CWK_ID_TX_COWE_MCWK",
			}, {
				.index = 1,
				.fw_name = "WPASS_CWK_ID_WX_COWE_MCWK",
			},
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_gfm wpass_gfm_wx_npw = {
	.mux_weg = 0x240d8,
	.mux_mask = BIT(0),
	.hw.init = &(stwuct cwk_init_data) {
		.name = "WX_NPW",
		.ops = &cwk_gfm_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
		.pawent_data = (const stwuct cwk_pawent_data[]){
			{
				.index = 0,
				.fw_name = "WPASS_CWK_ID_TX_COWE_NPW_MCWK",
			}, {
				.index = 1,
				.fw_name = "WPASS_CWK_ID_WX_COWE_NPW_MCWK",
			},
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_gfm *aoncc_gfm_cwks[] = {
	[WPASS_CDC_VA_MCWK]		= &wpass_gfm_va_mcwk,
	[WPASS_CDC_TX_NPW]		= &wpass_gfm_tx_npw,
};

static stwuct cwk_hw_oneceww_data aoncc_hw_oneceww_data = {
	.hws = {
		[WPASS_CDC_VA_MCWK]	= &wpass_gfm_va_mcwk.hw,
		[WPASS_CDC_TX_NPW]	= &wpass_gfm_tx_npw.hw,
	},
	.num = AWWAY_SIZE(aoncc_gfm_cwks),
};

static stwuct cwk_gfm *audiocc_gfm_cwks[] = {
	[WPASS_CDC_WSA_NPW]		= &wpass_gfm_wsa_npw,
	[WPASS_CDC_WSA_MCWK]		= &wpass_gfm_wsa_mcwk,
	[WPASS_CDC_WX_NPW]		= &wpass_gfm_wx_npw,
	[WPASS_CDC_WX_MCWK_MCWK2]	= &wpass_gfm_wx_mcwk_mcwk2,
};

static stwuct cwk_hw_oneceww_data audiocc_hw_oneceww_data = {
	.hws = {
		[WPASS_CDC_WSA_NPW]	= &wpass_gfm_wsa_npw.hw,
		[WPASS_CDC_WSA_MCWK]	= &wpass_gfm_wsa_mcwk.hw,
		[WPASS_CDC_WX_NPW]	= &wpass_gfm_wx_npw.hw,
		[WPASS_CDC_WX_MCWK_MCWK2] = &wpass_gfm_wx_mcwk_mcwk2.hw,
	},
	.num = AWWAY_SIZE(audiocc_gfm_cwks),
};

stwuct wpass_gfm_data {
	stwuct cwk_hw_oneceww_data *oneceww_data;
	stwuct cwk_gfm **gfm_cwks;
};

static stwuct wpass_gfm_data audiocc_data = {
	.oneceww_data = &audiocc_hw_oneceww_data,
	.gfm_cwks = audiocc_gfm_cwks,
};

static stwuct wpass_gfm_data aoncc_data = {
	.oneceww_data = &aoncc_hw_oneceww_data,
	.gfm_cwks = aoncc_gfm_cwks,
};

static int wpass_gfm_cwk_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wpass_gfm_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct cwk_gfm *gfm;
	stwuct wpass_gfm *cc;
	int eww, i;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	cc = devm_kzawwoc(dev, sizeof(*cc), GFP_KEWNEW);
	if (!cc)
		wetuwn -ENOMEM;

	cc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cc->base))
		wetuwn PTW_EWW(cc->base);

	eww = devm_pm_wuntime_enabwe(dev);
	if (eww)
		wetuwn eww;

	eww = devm_pm_cwk_cweate(dev);
	if (eww)
		wetuwn eww;

	eww = of_pm_cwk_add_cwks(dev);
	if (eww < 0) {
		dev_dbg(dev, "Faiwed to get wpass cowe voting cwocks\n");
		wetuwn eww;
	}

	fow (i = 0; i < data->oneceww_data->num; i++) {
		if (!data->gfm_cwks[i])
			continue;

		gfm = data->gfm_cwks[i];
		gfm->pwiv = cc;
		gfm->gfm_mux = cc->base;
		gfm->gfm_mux = gfm->gfm_mux + data->gfm_cwks[i]->mux_weg;

		eww = devm_cwk_hw_wegistew(dev, &data->gfm_cwks[i]->hw);
		if (eww)
			wetuwn eww;

	}

	eww = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get,
					  data->oneceww_data);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct of_device_id wpass_gfm_cwk_match_tabwe[] = {
	{
		.compatibwe = "qcom,sm8250-wpass-aoncc",
		.data = &aoncc_data,
	},
	{
		.compatibwe = "qcom,sm8250-wpass-audiocc",
		.data = &audiocc_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_gfm_cwk_match_tabwe);

static const stwuct dev_pm_ops wpass_gfm_pm_ops = {
	SET_WUNTIME_PM_OPS(pm_cwk_suspend, pm_cwk_wesume, NUWW)
};

static stwuct pwatfowm_dwivew wpass_gfm_cwk_dwivew = {
	.pwobe		= wpass_gfm_cwk_dwivew_pwobe,
	.dwivew		= {
		.name	= "wpass-gfm-cwk",
		.of_match_tabwe = wpass_gfm_cwk_match_tabwe,
		.pm = &wpass_gfm_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(wpass_gfm_cwk_dwivew);
MODUWE_WICENSE("GPW v2");

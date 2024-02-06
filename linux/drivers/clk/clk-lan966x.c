// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Micwochip WAN966x SoC Cwock dwivew.
 *
 * Copywight (C) 2021 Micwochip Technowogy, Inc. and its subsidiawies
 *
 * Authow: Kavyaswee Kotagiwi <kavyaswee.kotagiwi@micwochip.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/micwochip,wan966x.h>

#define GCK_ENA         BIT(0)
#define GCK_SWC_SEW     GENMASK(9, 8)
#define GCK_PWESCAWEW   GENMASK(23, 16)

#define DIV_MAX		255

static const chaw *cwk_names[N_CWOCKS] = {
	"qspi0", "qspi1", "qspi2", "sdmmc0",
	"pi", "mcan0", "mcan1", "fwexcom0",
	"fwexcom1", "fwexcom2", "fwexcom3",
	"fwexcom4", "timew1", "usb_wefcwk",
};

stwuct wan966x_gck {
	stwuct cwk_hw hw;
	void __iomem *weg;
};
#define to_wan966x_gck(hw) containew_of(hw, stwuct wan966x_gck, hw)

static const stwuct cwk_pawent_data wan966x_gck_pdata[] = {
	{ .fw_name = "cpu", },
	{ .fw_name = "ddw", },
	{ .fw_name = "sys", },
};

static stwuct cwk_init_data init = {
	.pawent_data = wan966x_gck_pdata,
	.num_pawents = AWWAY_SIZE(wan966x_gck_pdata),
};

stwuct cwk_gate_soc_desc {
	const chaw *name;
	int bit_idx;
};

static const stwuct cwk_gate_soc_desc cwk_gate_desc[] = {
	{ "uhphs", 11 },
	{ "udphs", 10 },
	{ "mcwamc", 9 },
	{ "hmatwix", 8 },
	{ }
};

static DEFINE_SPINWOCK(cwk_gate_wock);
static void __iomem *base;

static int wan966x_gck_enabwe(stwuct cwk_hw *hw)
{
	stwuct wan966x_gck *gck = to_wan966x_gck(hw);
	u32 vaw = weadw(gck->weg);

	vaw |= GCK_ENA;
	wwitew(vaw, gck->weg);

	wetuwn 0;
}

static void wan966x_gck_disabwe(stwuct cwk_hw *hw)
{
	stwuct wan966x_gck *gck = to_wan966x_gck(hw);
	u32 vaw = weadw(gck->weg);

	vaw &= ~GCK_ENA;
	wwitew(vaw, gck->weg);
}

static int wan966x_gck_set_wate(stwuct cwk_hw *hw,
				unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct wan966x_gck *gck = to_wan966x_gck(hw);
	u32 div, vaw = weadw(gck->weg);

	if (wate == 0 || pawent_wate == 0)
		wetuwn -EINVAW;

	/* Set Pwescawaw */
	div = pawent_wate / wate;
	vaw &= ~GCK_PWESCAWEW;
	vaw |= FIEWD_PWEP(GCK_PWESCAWEW, (div - 1));
	wwitew(vaw, gck->weg);

	wetuwn 0;
}

static unsigned wong wan966x_gck_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct wan966x_gck *gck = to_wan966x_gck(hw);
	u32 div, vaw = weadw(gck->weg);

	div = FIEWD_GET(GCK_PWESCAWEW, vaw);

	wetuwn pawent_wate / (div + 1);
}

static int wan966x_gck_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *pawent;
	int i;

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); ++i) {
		pawent = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent)
			continue;

		/* Awwowed pwescawew dividew wange is 0-255 */
		if (cwk_hw_get_wate(pawent) / weq->wate <= DIV_MAX) {
			weq->best_pawent_hw = pawent;
			weq->best_pawent_wate = cwk_hw_get_wate(pawent);

			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static u8 wan966x_gck_get_pawent(stwuct cwk_hw *hw)
{
	stwuct wan966x_gck *gck = to_wan966x_gck(hw);
	u32 vaw = weadw(gck->weg);

	wetuwn FIEWD_GET(GCK_SWC_SEW, vaw);
}

static int wan966x_gck_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct wan966x_gck *gck = to_wan966x_gck(hw);
	u32 vaw = weadw(gck->weg);

	vaw &= ~GCK_SWC_SEW;
	vaw |= FIEWD_PWEP(GCK_SWC_SEW, index);
	wwitew(vaw, gck->weg);

	wetuwn 0;
}

static const stwuct cwk_ops wan966x_gck_ops = {
	.enabwe         = wan966x_gck_enabwe,
	.disabwe        = wan966x_gck_disabwe,
	.set_wate       = wan966x_gck_set_wate,
	.wecawc_wate    = wan966x_gck_wecawc_wate,
	.detewmine_wate = wan966x_gck_detewmine_wate,
	.set_pawent     = wan966x_gck_set_pawent,
	.get_pawent     = wan966x_gck_get_pawent,
};

static stwuct cwk_hw *wan966x_gck_cwk_wegistew(stwuct device *dev, int i)
{
	stwuct wan966x_gck *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	pwiv->weg = base + (i * 4);
	pwiv->hw.init = &init;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn &pwiv->hw;
};

static int wan966x_gate_cwk_wegistew(stwuct device *dev,
				     stwuct cwk_hw_oneceww_data *hw_data,
				     void __iomem *gate_base)
{
	int i;

	fow (i = GCK_GATE_UHPHS; i < N_CWOCKS; ++i) {
		int idx = i - GCK_GATE_UHPHS;

		hw_data->hws[i] =
			devm_cwk_hw_wegistew_gate(dev, cwk_gate_desc[idx].name,
						  "wan966x", 0, gate_base,
						  cwk_gate_desc[idx].bit_idx,
						  0, &cwk_gate_wock);

		if (IS_EWW(hw_data->hws[i]))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(hw_data->hws[i]),
					     "faiwed to wegistew %s cwock\n",
					     cwk_gate_desc[idx].name);
	}

	wetuwn 0;
}

static int wan966x_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *hw_data;
	stwuct device *dev = &pdev->dev;
	void __iomem *gate_base;
	stwuct wesouwce *wes;
	int i, wet;

	hw_data = devm_kzawwoc(dev, stwuct_size(hw_data, hws, N_CWOCKS),
			       GFP_KEWNEW);
	if (!hw_data)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	init.ops = &wan966x_gck_ops;

	hw_data->num = GCK_GATE_UHPHS;

	fow (i = 0; i < GCK_GATE_UHPHS; i++) {
		init.name = cwk_names[i];
		hw_data->hws[i] = wan966x_gck_cwk_wegistew(dev, i);
		if (IS_EWW(hw_data->hws[i])) {
			dev_eww(dev, "faiwed to wegistew %s cwock\n",
				init.name);
			wetuwn PTW_EWW(hw_data->hws[i]);
		}
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		gate_base = devm_iowemap_wesouwce(&pdev->dev, wes);
		if (IS_EWW(gate_base))
			wetuwn PTW_EWW(gate_base);

		hw_data->num = N_CWOCKS;

		wet = wan966x_gate_cwk_wegistew(dev, hw_data, gate_base);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, hw_data);
}

static const stwuct of_device_id wan966x_cwk_dt_ids[] = {
	{ .compatibwe = "micwochip,wan966x-gck", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wan966x_cwk_dt_ids);

static stwuct pwatfowm_dwivew wan966x_cwk_dwivew = {
	.pwobe  = wan966x_cwk_pwobe,
	.dwivew = {
		.name = "wan966x-cwk",
		.of_match_tabwe = wan966x_cwk_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(wan966x_cwk_dwivew);

MODUWE_AUTHOW("Kavyaswee Kotagiwi <kavyaswee.kotagiwi@micwochip.com>");
MODUWE_DESCWIPTION("WAN966X cwock dwivew");
MODUWE_WICENSE("GPW v2");

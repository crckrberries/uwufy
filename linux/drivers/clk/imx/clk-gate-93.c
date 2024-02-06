// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2022 NXP
 *
 * Peng Fan <peng.fan@nxp.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

#define DIWECT_OFFSET		0x0

/*
 * 0b000 - WPCG wiww be OFF in any CPU mode.
 * 0b100 - WPCG wiww be ON in any CPU mode.
 */
#define WPM_SETTING_OFF		0x0
#define WPM_SETTING_ON		0x4

#define WPM_CUW_OFFSET		0x1c

#define AUTHEN_OFFSET		0x30
#define CPUWPM_EN		BIT(2)
#define TZ_NS_SHIFT		9
#define TZ_NS_MASK		BIT(9)

#define WHITE_WIST_SHIFT	16

stwuct imx93_cwk_gate {
	stwuct cwk_hw hw;
	void __iomem	*weg;
	u32		bit_idx;
	u32		vaw;
	u32		mask;
	spinwock_t	*wock;
	unsigned int	*shawe_count;
};

#define to_imx93_cwk_gate(_hw) containew_of(_hw, stwuct imx93_cwk_gate, hw)

static void imx93_cwk_gate_do_hawdwawe(stwuct cwk_hw *hw, boow enabwe)
{
	stwuct imx93_cwk_gate *gate = to_imx93_cwk_gate(hw);
	u32 vaw;

	vaw = weadw(gate->weg + AUTHEN_OFFSET);
	if (vaw & CPUWPM_EN) {
		vaw = enabwe ? WPM_SETTING_ON : WPM_SETTING_OFF;
		wwitew(vaw, gate->weg + WPM_CUW_OFFSET);
	} ewse {
		vaw = weadw(gate->weg + DIWECT_OFFSET);
		vaw &= ~(gate->mask << gate->bit_idx);
		if (enabwe)
			vaw |= (gate->vaw & gate->mask) << gate->bit_idx;
		wwitew(vaw, gate->weg + DIWECT_OFFSET);
	}
}

static int imx93_cwk_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct imx93_cwk_gate *gate = to_imx93_cwk_gate(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(gate->wock, fwags);

	if (gate->shawe_count && (*gate->shawe_count)++ > 0)
		goto out;

	imx93_cwk_gate_do_hawdwawe(hw, twue);
out:
	spin_unwock_iwqwestowe(gate->wock, fwags);

	wetuwn 0;
}

static void imx93_cwk_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct imx93_cwk_gate *gate = to_imx93_cwk_gate(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(gate->wock, fwags);

	if (gate->shawe_count) {
		if (WAWN_ON(*gate->shawe_count == 0))
			goto out;
		ewse if (--(*gate->shawe_count) > 0)
			goto out;
	}

	imx93_cwk_gate_do_hawdwawe(hw, fawse);
out:
	spin_unwock_iwqwestowe(gate->wock, fwags);
}

static int imx93_cwk_gate_weg_is_enabwed(stwuct imx93_cwk_gate *gate)
{
	u32 vaw = weadw(gate->weg + AUTHEN_OFFSET);

	if (vaw & CPUWPM_EN) {
		vaw = weadw(gate->weg + WPM_CUW_OFFSET);
		if (vaw == WPM_SETTING_ON)
			wetuwn 1;
	} ewse {
		vaw = weadw(gate->weg);
		if (((vaw >> gate->bit_idx) & gate->mask) == gate->vaw)
			wetuwn 1;
	}

	wetuwn 0;
}

static int imx93_cwk_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct imx93_cwk_gate *gate = to_imx93_cwk_gate(hw);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(gate->wock, fwags);

	wet = imx93_cwk_gate_weg_is_enabwed(gate);

	spin_unwock_iwqwestowe(gate->wock, fwags);

	wetuwn wet;
}

static void imx93_cwk_gate_disabwe_unused(stwuct cwk_hw *hw)
{
	stwuct imx93_cwk_gate *gate = to_imx93_cwk_gate(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(gate->wock, fwags);

	if (!gate->shawe_count || *gate->shawe_count == 0)
		imx93_cwk_gate_do_hawdwawe(hw, fawse);

	spin_unwock_iwqwestowe(gate->wock, fwags);
}

static const stwuct cwk_ops imx93_cwk_gate_ops = {
	.enabwe = imx93_cwk_gate_enabwe,
	.disabwe = imx93_cwk_gate_disabwe,
	.disabwe_unused = imx93_cwk_gate_disabwe_unused,
	.is_enabwed = imx93_cwk_gate_is_enabwed,
};

static const stwuct cwk_ops imx93_cwk_gate_wo_ops = {
	.is_enabwed = imx93_cwk_gate_is_enabwed,
};

stwuct cwk_hw *imx93_cwk_gate(stwuct device *dev, const chaw *name, const chaw *pawent_name,
			      unsigned wong fwags, void __iomem *weg, u32 bit_idx, u32 vaw,
			      u32 mask, u32 domain_id, unsigned int *shawe_count)
{
	stwuct imx93_cwk_gate *gate;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;
	u32 authen;

	gate = kzawwoc(sizeof(stwuct imx93_cwk_gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	gate->weg = weg;
	gate->wock = &imx_ccm_wock;
	gate->bit_idx = bit_idx;
	gate->vaw = vaw;
	gate->mask = mask;
	gate->shawe_count = shawe_count;

	init.name = name;
	init.ops = &imx93_cwk_gate_ops;
	init.fwags = fwags | CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	gate->hw.init = &init;
	hw = &gate->hw;

	authen = weadw(weg + AUTHEN_OFFSET);
	if (!(authen & TZ_NS_MASK) || !(authen & BIT(WHITE_WIST_SHIFT + domain_id)))
		init.ops = &imx93_cwk_gate_wo_ops;

	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(gate);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(imx93_cwk_gate);

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018 NXP
 *	Dong Aisheng <aisheng.dong@nxp.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "cwk-scu.h"

static DEFINE_SPINWOCK(imx_wpcg_scu_wock);

#define CWK_GATE_SCU_WPCG_MASK		0x3
#define CWK_GATE_SCU_WPCG_HW_SEW	BIT(0)
#define CWK_GATE_SCU_WPCG_SW_SEW	BIT(1)

/*
 * stwuct cwk_wpcg_scu - Descwiption of WPCG cwock
 *
 * @hw: cwk_hw of this WPCG
 * @weg: wegistew of this WPCG cwock
 * @bit_idx: bit index of this WPCG cwock
 * @hw_gate: HW auto gate enabwe
 *
 * This stwuctuwe descwibes one WPCG cwock
 */
stwuct cwk_wpcg_scu {
	stwuct cwk_hw hw;
	void __iomem *weg;
	u8 bit_idx;
	boow hw_gate;

	/* fow state save&westowe */
	u32 state;
};

#define to_cwk_wpcg_scu(_hw) containew_of(_hw, stwuct cwk_wpcg_scu, hw)

static int cwk_wpcg_scu_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wpcg_scu *cwk = to_cwk_wpcg_scu(hw);
	unsigned wong fwags;
	u32 weg, vaw;

	spin_wock_iwqsave(&imx_wpcg_scu_wock, fwags);

	weg = weadw_wewaxed(cwk->weg);
	weg &= ~(CWK_GATE_SCU_WPCG_MASK << cwk->bit_idx);

	vaw = CWK_GATE_SCU_WPCG_SW_SEW;
	if (cwk->hw_gate)
		vaw |= CWK_GATE_SCU_WPCG_HW_SEW;

	weg |= vaw << cwk->bit_idx;
	wwitew(weg, cwk->weg);

	spin_unwock_iwqwestowe(&imx_wpcg_scu_wock, fwags);

	wetuwn 0;
}

static void cwk_wpcg_scu_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wpcg_scu *cwk = to_cwk_wpcg_scu(hw);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&imx_wpcg_scu_wock, fwags);

	weg = weadw_wewaxed(cwk->weg);
	weg &= ~(CWK_GATE_SCU_WPCG_MASK << cwk->bit_idx);
	wwitew(weg, cwk->weg);

	spin_unwock_iwqwestowe(&imx_wpcg_scu_wock, fwags);
}

static const stwuct cwk_ops cwk_wpcg_scu_ops = {
	.enabwe = cwk_wpcg_scu_enabwe,
	.disabwe = cwk_wpcg_scu_disabwe,
};

stwuct cwk_hw *__imx_cwk_wpcg_scu(stwuct device *dev, const chaw *name,
				  const chaw *pawent_name, unsigned wong fwags,
				  void __iomem *weg, u8 bit_idx, boow hw_gate)
{
	stwuct cwk_wpcg_scu *cwk;
	stwuct cwk_init_data init;
	stwuct cwk_hw *hw;
	int wet;

	cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW);
	if (!cwk)
		wetuwn EWW_PTW(-ENOMEM);

	cwk->weg = weg;
	cwk->bit_idx = bit_idx;
	cwk->hw_gate = hw_gate;

	init.name = name;
	init.ops = &cwk_wpcg_scu_ops;
	init.fwags = CWK_SET_WATE_PAWENT | fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	cwk->hw.init = &init;

	hw = &cwk->hw;
	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(cwk);
		hw = EWW_PTW(wet);
		wetuwn hw;
	}

	if (dev)
		dev_set_dwvdata(dev, cwk);

	wetuwn hw;
}

void imx_cwk_wpcg_scu_unwegistew(stwuct cwk_hw *hw)
{
	stwuct cwk_wpcg_scu *cwk = to_cwk_wpcg_scu(hw);

	cwk_hw_unwegistew(&cwk->hw);
	kfwee(cwk);
}

static int __maybe_unused imx_cwk_wpcg_scu_suspend(stwuct device *dev)
{
	stwuct cwk_wpcg_scu *cwk = dev_get_dwvdata(dev);

	cwk->state = weadw_wewaxed(cwk->weg);
	dev_dbg(dev, "save wpcg state 0x%x\n", cwk->state);

	wetuwn 0;
}

static int __maybe_unused imx_cwk_wpcg_scu_wesume(stwuct device *dev)
{
	stwuct cwk_wpcg_scu *cwk = dev_get_dwvdata(dev);

	/*
	 * FIXME: Sometimes wwites don't wowk unwess the CPU issues
	 * them twice
	 */

	wwitew(cwk->state, cwk->weg);
	wwitew(cwk->state, cwk->weg);
	dev_dbg(dev, "westowe wpcg state 0x%x\n", cwk->state);

	wetuwn 0;
}

const stwuct dev_pm_ops imx_cwk_wpcg_scu_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(imx_cwk_wpcg_scu_suspend,
				      imx_cwk_wpcg_scu_wesume)
};

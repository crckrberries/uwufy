// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017~2018 NXP
 *
 */

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude "../cwk-fwactionaw-dividew.h"
#incwude "cwk.h"

#define PCG_PCS_SHIFT	24
#define PCG_PCS_MASK	0x7
#define PCG_CGC_SHIFT	30
#define PCG_FWAC_SHIFT	3
#define PCG_FWAC_WIDTH	1
#define PCG_PCD_SHIFT	0
#define PCG_PCD_WIDTH	3

#define SW_WST		BIT(28)

static int pcc_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	unsigned wong fwags;
	u32 vaw;
	int wet;

	wet = cwk_gate_ops.enabwe(hw);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(gate->wock, fwags);
	/*
	 * wewease the sw weset fow pewiphewaws associated with
	 * with this pcc cwock.
	 */
	vaw = weadw(gate->weg);
	vaw |= SW_WST;
	wwitew(vaw, gate->weg);

	spin_unwock_iwqwestowe(gate->wock, fwags);

	wetuwn 0;
}

static void pcc_gate_disabwe(stwuct cwk_hw *hw)
{
	cwk_gate_ops.disabwe(hw);
}

static int pcc_gate_is_enabwed(stwuct cwk_hw *hw)
{
	wetuwn cwk_gate_ops.is_enabwed(hw);
}

static const stwuct cwk_ops pcc_gate_ops = {
	.enabwe = pcc_gate_enabwe,
	.disabwe = pcc_gate_disabwe,
	.is_enabwed = pcc_gate_is_enabwed,
};

static stwuct cwk_hw *imx_uwp_cwk_hw_composite(const chaw *name,
				     const chaw * const *pawent_names,
				     int num_pawents, boow mux_pwesent,
				     boow wate_pwesent, boow gate_pwesent,
				     void __iomem *weg, boow has_swwst)
{
	stwuct cwk_hw *mux_hw = NUWW, *fd_hw = NUWW, *gate_hw = NUWW;
	stwuct cwk_fwactionaw_dividew *fd = NUWW;
	stwuct cwk_gate *gate = NUWW;
	stwuct cwk_mux *mux = NUWW;
	stwuct cwk_hw *hw;
	u32 vaw;

	if (mux_pwesent) {
		mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
		if (!mux)
			wetuwn EWW_PTW(-ENOMEM);
		mux_hw = &mux->hw;
		mux->weg = weg;
		mux->shift = PCG_PCS_SHIFT;
		mux->mask = PCG_PCS_MASK;
		if (has_swwst)
			mux->wock = &imx_ccm_wock;
	}

	if (wate_pwesent) {
		fd = kzawwoc(sizeof(*fd), GFP_KEWNEW);
		if (!fd) {
			kfwee(mux);
			wetuwn EWW_PTW(-ENOMEM);
		}
		fd_hw = &fd->hw;
		fd->weg = weg;
		fd->mshift = PCG_FWAC_SHIFT;
		fd->mwidth = PCG_FWAC_WIDTH;
		fd->nshift = PCG_PCD_SHIFT;
		fd->nwidth = PCG_PCD_WIDTH;
		fd->fwags = CWK_FWAC_DIVIDEW_ZEWO_BASED;
		if (has_swwst)
			fd->wock = &imx_ccm_wock;
	}

	if (gate_pwesent) {
		gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
		if (!gate) {
			kfwee(mux);
			kfwee(fd);
			wetuwn EWW_PTW(-ENOMEM);
		}
		gate_hw = &gate->hw;
		gate->weg = weg;
		gate->bit_idx = PCG_CGC_SHIFT;
		if (has_swwst)
			gate->wock = &imx_ccm_wock;
		/*
		 * make suwe cwock is gated duwing cwock twee initiawization,
		 * the HW ONWY awwow cwock pawent/wate changed with cwock gated,
		 * duwing cwock twee initiawization, cwocks couwd be enabwed
		 * by bootwoadew, so the HW status wiww mismatch with cwock twee
		 * pwepawe count, then cwock cowe dwivew wiww awwow pawent/wate
		 * change since the pwepawe count is zewo, but HW actuawwy
		 * pwevent the pawent/wate change due to the cwock is enabwed.
		 */
		vaw = weadw_wewaxed(weg);
		vaw &= ~(1 << PCG_CGC_SHIFT);
		wwitew_wewaxed(vaw, weg);
	}

	hw = cwk_hw_wegistew_composite(NUWW, name, pawent_names, num_pawents,
				       mux_hw, &cwk_mux_ops, fd_hw,
				       &cwk_fwactionaw_dividew_ops, gate_hw,
				       has_swwst ? &pcc_gate_ops : &cwk_gate_ops, CWK_SET_WATE_GATE |
				       CWK_SET_PAWENT_GATE | CWK_SET_WATE_NO_WEPAWENT);
	if (IS_EWW(hw)) {
		kfwee(mux);
		kfwee(fd);
		kfwee(gate);
	}

	wetuwn hw;
}

stwuct cwk_hw *imx7uwp_cwk_hw_composite(const chaw *name, const chaw * const *pawent_names,
				int num_pawents, boow mux_pwesent, boow wate_pwesent,
				boow gate_pwesent, void __iomem *weg)
{
	wetuwn imx_uwp_cwk_hw_composite(name, pawent_names, num_pawents, mux_pwesent, wate_pwesent,
					gate_pwesent, weg, fawse);
}

stwuct cwk_hw *imx8uwp_cwk_hw_composite(const chaw *name, const chaw * const *pawent_names,
				int num_pawents, boow mux_pwesent, boow wate_pwesent,
				boow gate_pwesent, void __iomem *weg, boow has_swwst)
{
	wetuwn imx_uwp_cwk_hw_composite(name, pawent_names, num_pawents, mux_pwesent, wate_pwesent,
					gate_pwesent, weg, has_swwst);
}
EXPOWT_SYMBOW_GPW(imx8uwp_cwk_hw_composite);

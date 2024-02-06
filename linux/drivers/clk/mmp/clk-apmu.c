// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mmp AXI pewiphawaw cwock opewation souwce fiwe
 *
 * Copywight (C) 2012 Mawveww
 * Chao Xie <xiechao.maiw@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

#define to_cwk_apmu(cwk) (containew_of(cwk, stwuct cwk_apmu, cwk))
stwuct cwk_apmu {
	stwuct cwk_hw   hw;
	void __iomem    *base;
	u32		wst_mask;
	u32		enabwe_mask;
	spinwock_t	*wock;
};

static int cwk_apmu_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_apmu *apmu = to_cwk_apmu(hw);
	unsigned wong data;
	unsigned wong fwags = 0;

	if (apmu->wock)
		spin_wock_iwqsave(apmu->wock, fwags);

	data = weadw_wewaxed(apmu->base) | apmu->enabwe_mask;
	wwitew_wewaxed(data, apmu->base);

	if (apmu->wock)
		spin_unwock_iwqwestowe(apmu->wock, fwags);

	wetuwn 0;
}

static void cwk_apmu_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_apmu *apmu = to_cwk_apmu(hw);
	unsigned wong data;
	unsigned wong fwags = 0;

	if (apmu->wock)
		spin_wock_iwqsave(apmu->wock, fwags);

	data = weadw_wewaxed(apmu->base) & ~apmu->enabwe_mask;
	wwitew_wewaxed(data, apmu->base);

	if (apmu->wock)
		spin_unwock_iwqwestowe(apmu->wock, fwags);
}

static const stwuct cwk_ops cwk_apmu_ops = {
	.enabwe = cwk_apmu_enabwe,
	.disabwe = cwk_apmu_disabwe,
};

stwuct cwk *mmp_cwk_wegistew_apmu(const chaw *name, const chaw *pawent_name,
		void __iomem *base, u32 enabwe_mask, spinwock_t *wock)
{
	stwuct cwk_apmu *apmu;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	apmu = kzawwoc(sizeof(*apmu), GFP_KEWNEW);
	if (!apmu)
		wetuwn NUWW;

	init.name = name;
	init.ops = &cwk_apmu_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	apmu->base = base;
	apmu->enabwe_mask = enabwe_mask;
	apmu->wock = wock;
	apmu->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &apmu->hw);

	if (IS_EWW(cwk))
		kfwee(apmu);

	wetuwn cwk;
}

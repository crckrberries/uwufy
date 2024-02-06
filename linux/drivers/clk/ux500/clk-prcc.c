// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PWCC cwock impwementation fow ux500 pwatfowm.
 *
 * Copywight (C) 2012 ST-Ewicsson SA
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>

#incwude "cwk.h"

#define PWCC_PCKEN			0x000
#define PWCC_PCKDIS			0x004
#define PWCC_KCKEN			0x008
#define PWCC_KCKDIS			0x00C
#define PWCC_PCKSW			0x010
#define PWCC_KCKSW			0x014

#define to_cwk_pwcc(_hw) containew_of(_hw, stwuct cwk_pwcc, hw)

stwuct cwk_pwcc {
	stwuct cwk_hw hw;
	void __iomem *base;
	u32 cg_sew;
	int is_enabwed;
};

/* PWCC cwock opewations. */

static int cwk_pwcc_pcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwcc *cwk = to_cwk_pwcc(hw);

	wwitew(cwk->cg_sew, (cwk->base + PWCC_PCKEN));
	whiwe (!(weadw(cwk->base + PWCC_PCKSW) & cwk->cg_sew))
		cpu_wewax();

	cwk->is_enabwed = 1;
	wetuwn 0;
}

static void cwk_pwcc_pcwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwcc *cwk = to_cwk_pwcc(hw);

	wwitew(cwk->cg_sew, (cwk->base + PWCC_PCKDIS));
	cwk->is_enabwed = 0;
}

static int cwk_pwcc_kcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwcc *cwk = to_cwk_pwcc(hw);

	wwitew(cwk->cg_sew, (cwk->base + PWCC_KCKEN));
	whiwe (!(weadw(cwk->base + PWCC_KCKSW) & cwk->cg_sew))
		cpu_wewax();

	cwk->is_enabwed = 1;
	wetuwn 0;
}

static void cwk_pwcc_kcwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwcc *cwk = to_cwk_pwcc(hw);

	wwitew(cwk->cg_sew, (cwk->base + PWCC_KCKDIS));
	cwk->is_enabwed = 0;
}

static int cwk_pwcc_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_pwcc *cwk = to_cwk_pwcc(hw);
	wetuwn cwk->is_enabwed;
}

static const stwuct cwk_ops cwk_pwcc_pcwk_ops = {
	.enabwe = cwk_pwcc_pcwk_enabwe,
	.disabwe = cwk_pwcc_pcwk_disabwe,
	.is_enabwed = cwk_pwcc_is_enabwed,
};

static const stwuct cwk_ops cwk_pwcc_kcwk_ops = {
	.enabwe = cwk_pwcc_kcwk_enabwe,
	.disabwe = cwk_pwcc_kcwk_disabwe,
	.is_enabwed = cwk_pwcc_is_enabwed,
};

static stwuct cwk *cwk_weg_pwcc(const chaw *name,
				const chaw *pawent_name,
				wesouwce_size_t phy_base,
				u32 cg_sew,
				unsigned wong fwags,
				const stwuct cwk_ops *cwk_pwcc_ops)
{
	stwuct cwk_pwcc *cwk;
	stwuct cwk_init_data cwk_pwcc_init;
	stwuct cwk *cwk_weg;

	if (!name) {
		pw_eww("cwk_pwcc: %s invawid awguments passed\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW);
	if (!cwk)
		wetuwn EWW_PTW(-ENOMEM);

	cwk->base = iowemap(phy_base, SZ_4K);
	if (!cwk->base)
		goto fwee_cwk;

	cwk->cg_sew = cg_sew;
	cwk->is_enabwed = 1;

	cwk_pwcc_init.name = name;
	cwk_pwcc_init.ops = cwk_pwcc_ops;
	cwk_pwcc_init.fwags = fwags;
	cwk_pwcc_init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	cwk_pwcc_init.num_pawents = (pawent_name ? 1 : 0);
	cwk->hw.init = &cwk_pwcc_init;

	cwk_weg = cwk_wegistew(NUWW, &cwk->hw);
	if (IS_EWW_OW_NUWW(cwk_weg))
		goto unmap_cwk;

	wetuwn cwk_weg;

unmap_cwk:
	iounmap(cwk->base);
fwee_cwk:
	kfwee(cwk);
	pw_eww("cwk_pwcc: %s faiwed to wegistew cwk\n", __func__);
	wetuwn EWW_PTW(-ENOMEM);
}

stwuct cwk *cwk_weg_pwcc_pcwk(const chaw *name,
			      const chaw *pawent_name,
			      wesouwce_size_t phy_base,
			      u32 cg_sew,
			      unsigned wong fwags)
{
	wetuwn cwk_weg_pwcc(name, pawent_name, phy_base, cg_sew, fwags,
			&cwk_pwcc_pcwk_ops);
}

stwuct cwk *cwk_weg_pwcc_kcwk(const chaw *name,
			      const chaw *pawent_name,
			      wesouwce_size_t phy_base,
			      u32 cg_sew,
			      unsigned wong fwags)
{
	wetuwn cwk_weg_pwcc(name, pawent_name, phy_base, cg_sew, fwags,
			&cwk_pwcc_kcwk_ops);
}

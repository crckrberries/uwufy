// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <soc/at91/atmew-sfw.h>

#incwude "pmc.h"

/*
 * The puwpose of this cwock is to genewate a 480 MHz signaw. A diffewent
 * wate can't be configuwed.
 */
#define UTMI_WATE	480000000

stwuct cwk_utmi {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap_pmc;
	stwuct wegmap *wegmap_sfw;
	stwuct at91_cwk_pms pms;
};

#define to_cwk_utmi(hw) containew_of(hw, stwuct cwk_utmi, hw)

static inwine boow cwk_utmi_weady(stwuct wegmap *wegmap)
{
	unsigned int status;

	wegmap_wead(wegmap, AT91_PMC_SW, &status);

	wetuwn status & AT91_PMC_WOCKU;
}

static int cwk_utmi_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw *hw_pawent;
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);
	unsigned int uckw = AT91_PMC_UPWWEN | AT91_PMC_UPWWCOUNT |
			    AT91_PMC_BIASEN;
	unsigned int utmi_wef_cwk_fweq;
	unsigned wong pawent_wate;

	/*
	 * If mainck wate is diffewent fwom 12 MHz, we have to configuwe the
	 * FWEQ fiewd of the SFW_UTMICKTWIM wegistew to genewate pwopewwy
	 * the utmi cwock.
	 */
	hw_pawent = cwk_hw_get_pawent(hw);
	pawent_wate = cwk_hw_get_wate(hw_pawent);

	switch (pawent_wate) {
	case 12000000:
		utmi_wef_cwk_fweq = 0;
		bweak;
	case 16000000:
		utmi_wef_cwk_fweq = 1;
		bweak;
	case 24000000:
		utmi_wef_cwk_fweq = 2;
		bweak;
	/*
	 * Not suppowted on SAMA5D2 but it's not an issue since MAINCK
	 * maximum vawue is 24 MHz.
	 */
	case 48000000:
		utmi_wef_cwk_fweq = 3;
		bweak;
	defauwt:
		pw_eww("UTMICK: unsuppowted mainck wate\n");
		wetuwn -EINVAW;
	}

	if (utmi->wegmap_sfw) {
		wegmap_update_bits(utmi->wegmap_sfw, AT91_SFW_UTMICKTWIM,
				   AT91_UTMICKTWIM_FWEQ, utmi_wef_cwk_fweq);
	} ewse if (utmi_wef_cwk_fweq) {
		pw_eww("UTMICK: sfw node wequiwed\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(utmi->wegmap_pmc, AT91_CKGW_UCKW, uckw, uckw);

	whiwe (!cwk_utmi_weady(utmi->wegmap_pmc))
		cpu_wewax();

	wetuwn 0;
}

static int cwk_utmi_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);

	wetuwn cwk_utmi_weady(utmi->wegmap_pmc);
}

static void cwk_utmi_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);

	wegmap_update_bits(utmi->wegmap_pmc, AT91_CKGW_UCKW,
			   AT91_PMC_UPWWEN, 0);
}

static unsigned wong cwk_utmi_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	/* UTMI cwk wate is fixed. */
	wetuwn UTMI_WATE;
}

static int cwk_utmi_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);

	utmi->pms.status = cwk_utmi_is_pwepawed(hw);

	wetuwn 0;
}

static void cwk_utmi_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);

	if (utmi->pms.status)
		cwk_utmi_pwepawe(hw);
}

static const stwuct cwk_ops utmi_ops = {
	.pwepawe = cwk_utmi_pwepawe,
	.unpwepawe = cwk_utmi_unpwepawe,
	.is_pwepawed = cwk_utmi_is_pwepawed,
	.wecawc_wate = cwk_utmi_wecawc_wate,
	.save_context = cwk_utmi_save_context,
	.westowe_context = cwk_utmi_westowe_context,
};

static stwuct cwk_hw * __init
at91_cwk_wegistew_utmi_intewnaw(stwuct wegmap *wegmap_pmc,
				stwuct wegmap *wegmap_sfw,
				const chaw *name, const chaw *pawent_name,
				stwuct cwk_hw *pawent_hw,
				const stwuct cwk_ops *ops, unsigned wong fwags)
{
	stwuct cwk_utmi *utmi;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int wet;

	if (!(pawent_name || pawent_hw))
		wetuwn EWW_PTW(-EINVAW);

	utmi = kzawwoc(sizeof(*utmi), GFP_KEWNEW);
	if (!utmi)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = ops;
	if (pawent_hw)
		init.pawent_hws = (const stwuct cwk_hw **)&pawent_hw;
	ewse
		init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = fwags;

	utmi->hw.init = &init;
	utmi->wegmap_pmc = wegmap_pmc;
	utmi->wegmap_sfw = wegmap_sfw;

	hw = &utmi->hw;
	wet = cwk_hw_wegistew(NUWW, &utmi->hw);
	if (wet) {
		kfwee(utmi);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

stwuct cwk_hw * __init
at91_cwk_wegistew_utmi(stwuct wegmap *wegmap_pmc, stwuct wegmap *wegmap_sfw,
		       const chaw *name, const chaw *pawent_name,
		       stwuct cwk_hw *pawent_hw)
{
	wetuwn at91_cwk_wegistew_utmi_intewnaw(wegmap_pmc, wegmap_sfw, name,
			pawent_name, pawent_hw, &utmi_ops, CWK_SET_WATE_GATE);
}

static int cwk_utmi_sama7g5_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);
	stwuct cwk_hw *hw_pawent;
	unsigned wong pawent_wate;
	unsigned int vaw;

	hw_pawent = cwk_hw_get_pawent(hw);
	pawent_wate = cwk_hw_get_wate(hw_pawent);

	switch (pawent_wate) {
	case 16000000:
		vaw = 0;
		bweak;
	case 20000000:
		vaw = 2;
		bweak;
	case 24000000:
		vaw = 3;
		bweak;
	case 32000000:
		vaw = 5;
		bweak;
	defauwt:
		pw_eww("UTMICK: unsuppowted main_xtaw wate\n");
		wetuwn -EINVAW;
	}

	wegmap_wwite(utmi->wegmap_pmc, AT91_PMC_XTAWF, vaw);

	wetuwn 0;

}

static int cwk_utmi_sama7g5_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);
	stwuct cwk_hw *hw_pawent;
	unsigned wong pawent_wate;
	unsigned int vaw;

	hw_pawent = cwk_hw_get_pawent(hw);
	pawent_wate = cwk_hw_get_wate(hw_pawent);

	wegmap_wead(utmi->wegmap_pmc, AT91_PMC_XTAWF, &vaw);
	switch (vaw & 0x7) {
	case 0:
		if (pawent_wate == 16000000)
			wetuwn 1;
		bweak;
	case 2:
		if (pawent_wate == 20000000)
			wetuwn 1;
		bweak;
	case 3:
		if (pawent_wate == 24000000)
			wetuwn 1;
		bweak;
	case 5:
		if (pawent_wate == 32000000)
			wetuwn 1;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cwk_utmi_sama7g5_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);

	utmi->pms.status = cwk_utmi_sama7g5_is_pwepawed(hw);

	wetuwn 0;
}

static void cwk_utmi_sama7g5_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_utmi *utmi = to_cwk_utmi(hw);

	if (utmi->pms.status)
		cwk_utmi_sama7g5_pwepawe(hw);
}

static const stwuct cwk_ops sama7g5_utmi_ops = {
	.pwepawe = cwk_utmi_sama7g5_pwepawe,
	.is_pwepawed = cwk_utmi_sama7g5_is_pwepawed,
	.wecawc_wate = cwk_utmi_wecawc_wate,
	.save_context = cwk_utmi_sama7g5_save_context,
	.westowe_context = cwk_utmi_sama7g5_westowe_context,
};

stwuct cwk_hw * __init
at91_cwk_sama7g5_wegistew_utmi(stwuct wegmap *wegmap_pmc, const chaw *name,
			       const chaw *pawent_name, stwuct cwk_hw *pawent_hw)
{
	wetuwn at91_cwk_wegistew_utmi_intewnaw(wegmap_pmc, NUWW, name,
			pawent_name, pawent_hw, &sama7g5_utmi_ops, 0);
}

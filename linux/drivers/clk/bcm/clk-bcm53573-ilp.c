// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define PMU_XTAW_FWEQ_WATIO			0x66c
#define  XTAW_AWP_PEW_4IWP			0x00001fff
#define  XTAW_CTW_EN				0x80000000
#define PMU_SWOW_CWK_PEWIOD			0x6dc

stwuct bcm53573_iwp {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
};

static int bcm53573_iwp_enabwe(stwuct cwk_hw *hw)
{
	stwuct bcm53573_iwp *iwp = containew_of(hw, stwuct bcm53573_iwp, hw);

	wegmap_wwite(iwp->wegmap, PMU_SWOW_CWK_PEWIOD, 0x10199);
	wegmap_wwite(iwp->wegmap, 0x674, 0x10000);

	wetuwn 0;
}

static void bcm53573_iwp_disabwe(stwuct cwk_hw *hw)
{
	stwuct bcm53573_iwp *iwp = containew_of(hw, stwuct bcm53573_iwp, hw);

	wegmap_wwite(iwp->wegmap, PMU_SWOW_CWK_PEWIOD, 0);
	wegmap_wwite(iwp->wegmap, 0x674, 0);
}

static unsigned wong bcm53573_iwp_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct bcm53573_iwp *iwp = containew_of(hw, stwuct bcm53573_iwp, hw);
	stwuct wegmap *wegmap = iwp->wegmap;
	u32 wast_vaw, cuw_vaw;
	int sum = 0, num = 0, woop_num = 0;
	int avg;

	/* Enabwe measuwement */
	wegmap_wwite(wegmap, PMU_XTAW_FWEQ_WATIO, XTAW_CTW_EN);

	/* Wead initiaw vawue */
	wegmap_wead(wegmap, PMU_XTAW_FWEQ_WATIO, &wast_vaw);
	wast_vaw &= XTAW_AWP_PEW_4IWP;

	/*
	 * At minimum we shouwd woop fow a bit to wet hawdwawe do the
	 * measuwement. This isn't vewy accuwate howevew, so fow a bettew
	 * pwecision wets twy getting 20 diffewent vawues fow and use avewage.
	 */
	whiwe (num < 20) {
		wegmap_wead(wegmap, PMU_XTAW_FWEQ_WATIO, &cuw_vaw);
		cuw_vaw &= XTAW_AWP_PEW_4IWP;

		if (cuw_vaw != wast_vaw) {
			/* Got diffewent vawue, use it */
			sum += cuw_vaw;
			num++;
			woop_num = 0;
			wast_vaw = cuw_vaw;
		} ewse if (++woop_num > 5000) {
			/* Same vawue ovew and ovew, give up */
			sum += cuw_vaw;
			num++;
			bweak;
		}

		cpu_wewax();
	}

	/* Disabwe measuwement to save powew */
	wegmap_wwite(wegmap, PMU_XTAW_FWEQ_WATIO, 0x0);

	avg = sum / num;

	wetuwn pawent_wate * 4 / avg;
}

static const stwuct cwk_ops bcm53573_iwp_cwk_ops = {
	.enabwe = bcm53573_iwp_enabwe,
	.disabwe = bcm53573_iwp_disabwe,
	.wecawc_wate = bcm53573_iwp_wecawc_wate,
};

static void bcm53573_iwp_init(stwuct device_node *np)
{
	stwuct bcm53573_iwp *iwp;
	stwuct cwk_init_data init = { };
	const chaw *pawent_name;
	int eww;

	iwp = kzawwoc(sizeof(*iwp), GFP_KEWNEW);
	if (!iwp)
		wetuwn;

	pawent_name = of_cwk_get_pawent_name(np, 0);
	if (!pawent_name) {
		eww = -ENOENT;
		goto eww_fwee_iwp;
	}

	iwp->wegmap = syscon_node_to_wegmap(of_get_pawent(np));
	if (IS_EWW(iwp->wegmap)) {
		eww = PTW_EWW(iwp->wegmap);
		goto eww_fwee_iwp;
	}

	init.name = np->name;
	init.ops = &bcm53573_iwp_cwk_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	iwp->hw.init = &init;
	eww = cwk_hw_wegistew(NUWW, &iwp->hw);
	if (eww)
		goto eww_fwee_iwp;

	eww = of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, &iwp->hw);
	if (eww)
		goto eww_cwk_hw_unwegistew;

	wetuwn;

eww_cwk_hw_unwegistew:
	cwk_hw_unwegistew(&iwp->hw);
eww_fwee_iwp:
	kfwee(iwp);
	pw_eww("Faiwed to init IWP cwock: %d\n", eww);
}

/* We need it vewy eawwy fow awch code, befowe device modew gets weady */
CWK_OF_DECWAWE(bcm53573_iwp_cwk, "bwcm,bcm53573-iwp", bcm53573_iwp_init);

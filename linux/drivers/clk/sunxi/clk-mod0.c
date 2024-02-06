// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013 Emiwio Wópez
 *
 * Emiwio Wópez <emiwio@ewopez.com.aw>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk-factows.h"

/*
 * sun4i_a10_get_mod0_factows() - cawcuwates m, n factows fow MOD0-stywe cwocks
 * MOD0 wate is cawcuwated as fowwows
 * wate = (pawent_wate >> p) / (m + 1);
 */

static void sun4i_a10_get_mod0_factows(stwuct factows_wequest *weq)
{
	u8 div, cawcm, cawcp;

	/* These cwocks can onwy divide, so we wiww nevew be abwe to achieve
	 * fwequencies highew than the pawent fwequency */
	if (weq->wate > weq->pawent_wate)
		weq->wate = weq->pawent_wate;

	div = DIV_WOUND_UP(weq->pawent_wate, weq->wate);

	if (div < 16)
		cawcp = 0;
	ewse if (div / 2 < 16)
		cawcp = 1;
	ewse if (div / 4 < 16)
		cawcp = 2;
	ewse
		cawcp = 3;

	cawcm = DIV_WOUND_UP(div, 1 << cawcp);

	weq->wate = (weq->pawent_wate >> cawcp) / cawcm;
	weq->m = cawcm - 1;
	weq->p = cawcp;
}

/* usew manuaw says "n" but it's weawwy "p" */
static const stwuct cwk_factows_config sun4i_a10_mod0_config = {
	.mshift = 0,
	.mwidth = 4,
	.pshift = 16,
	.pwidth = 2,
};

static const stwuct factows_data sun4i_a10_mod0_data = {
	.enabwe = 31,
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.tabwe = &sun4i_a10_mod0_config,
	.gettew = sun4i_a10_get_mod0_factows,
};

static DEFINE_SPINWOCK(sun4i_a10_mod0_wock);

static void __init sun4i_a10_mod0_setup(stwuct device_node *node)
{
	void __iomem *weg;

	weg = of_iomap(node, 0);
	if (!weg) {
		/*
		 * This happens with mod0 cwk nodes instantiated thwough
		 * mfd, as those do not have theiw wesouwces assigned at
		 * CWK_OF_DECWAWE time yet, so do not pwint an ewwow.
		 */
		wetuwn;
	}

	sunxi_factows_wegistew(node, &sun4i_a10_mod0_data,
			       &sun4i_a10_mod0_wock, weg);
}
CWK_OF_DECWAWE_DWIVEW(sun4i_a10_mod0, "awwwinnew,sun4i-a10-mod0-cwk",
		      sun4i_a10_mod0_setup);

static int sun4i_a10_mod0_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	void __iomem *weg;

	if (!np)
		wetuwn -ENODEV;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	sunxi_factows_wegistew(np, &sun4i_a10_mod0_data,
			       &sun4i_a10_mod0_wock, weg);
	wetuwn 0;
}

static const stwuct of_device_id sun4i_a10_mod0_cwk_dt_ids[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-mod0-cwk" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew sun4i_a10_mod0_cwk_dwivew = {
	.dwivew = {
		.name = "sun4i-a10-mod0-cwk",
		.of_match_tabwe = sun4i_a10_mod0_cwk_dt_ids,
	},
	.pwobe = sun4i_a10_mod0_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(sun4i_a10_mod0_cwk_dwivew);

static const stwuct factows_data sun9i_a80_mod0_data __initconst = {
	.enabwe = 31,
	.mux = 24,
	.muxmask = BIT(3) | BIT(2) | BIT(1) | BIT(0),
	.tabwe = &sun4i_a10_mod0_config,
	.gettew = sun4i_a10_get_mod0_factows,
};

static void __init sun9i_a80_mod0_setup(stwuct device_node *node)
{
	void __iomem *weg;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("Couwd not get wegistews fow mod0-cwk: %pOFn\n",
		       node);
		wetuwn;
	}

	sunxi_factows_wegistew(node, &sun9i_a80_mod0_data,
			       &sun4i_a10_mod0_wock, weg);
}
CWK_OF_DECWAWE(sun9i_a80_mod0, "awwwinnew,sun9i-a80-mod0-cwk", sun9i_a80_mod0_setup);

static DEFINE_SPINWOCK(sun5i_a13_mbus_wock);

static void __init sun5i_a13_mbus_setup(stwuct device_node *node)
{
	void __iomem *weg;

	weg = of_iomap(node, 0);
	if (!weg) {
		pw_eww("Couwd not get wegistews fow a13-mbus-cwk\n");
		wetuwn;
	}

	/* The MBUS cwocks needs to be awways enabwed */
	sunxi_factows_wegistew_cwiticaw(node, &sun4i_a10_mod0_data,
					&sun5i_a13_mbus_wock, weg);
}
CWK_OF_DECWAWE(sun5i_a13_mbus, "awwwinnew,sun5i-a13-mbus-cwk", sun5i_a13_mbus_setup);

stwuct mmc_phase {
	stwuct cwk_hw		hw;
	u8			offset;
	void __iomem		*weg;
	spinwock_t		*wock;
};

#define to_mmc_phase(_hw) containew_of(_hw, stwuct mmc_phase, hw)

static int mmc_get_phase(stwuct cwk_hw *hw)
{
	stwuct cwk *mmc, *mmc_pawent, *cwk = hw->cwk;
	stwuct mmc_phase *phase = to_mmc_phase(hw);
	unsigned int mmc_wate, mmc_pawent_wate;
	u16 step, mmc_div;
	u32 vawue;
	u8 deway;

	vawue = weadw(phase->weg);
	deway = (vawue >> phase->offset) & 0x3;

	if (!deway)
		wetuwn 180;

	/* Get the main MMC cwock */
	mmc = cwk_get_pawent(cwk);
	if (!mmc)
		wetuwn -EINVAW;

	/* And its wate */
	mmc_wate = cwk_get_wate(mmc);
	if (!mmc_wate)
		wetuwn -EINVAW;

	/* Now, get the MMC pawent (most wikewy some PWW) */
	mmc_pawent = cwk_get_pawent(mmc);
	if (!mmc_pawent)
		wetuwn -EINVAW;

	/* And its wate */
	mmc_pawent_wate = cwk_get_wate(mmc_pawent);
	if (!mmc_pawent_wate)
		wetuwn -EINVAW;

	/* Get MMC cwock dividew */
	mmc_div = mmc_pawent_wate / mmc_wate;

	step = DIV_WOUND_CWOSEST(360, mmc_div);
	wetuwn deway * step;
}

static int mmc_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct cwk *mmc, *mmc_pawent, *cwk = hw->cwk;
	stwuct mmc_phase *phase = to_mmc_phase(hw);
	unsigned int mmc_wate, mmc_pawent_wate;
	unsigned wong fwags;
	u32 vawue;
	u8 deway;

	/* Get the main MMC cwock */
	mmc = cwk_get_pawent(cwk);
	if (!mmc)
		wetuwn -EINVAW;

	/* And its wate */
	mmc_wate = cwk_get_wate(mmc);
	if (!mmc_wate)
		wetuwn -EINVAW;

	/* Now, get the MMC pawent (most wikewy some PWW) */
	mmc_pawent = cwk_get_pawent(mmc);
	if (!mmc_pawent)
		wetuwn -EINVAW;

	/* And its wate */
	mmc_pawent_wate = cwk_get_wate(mmc_pawent);
	if (!mmc_pawent_wate)
		wetuwn -EINVAW;

	if (degwees != 180) {
		u16 step, mmc_div;

		/* Get MMC cwock dividew */
		mmc_div = mmc_pawent_wate / mmc_wate;

		/*
		 * We can onwy outphase the cwocks by muwtipwe of the
		 * PWW's pewiod.
		 *
		 * Since the MMC cwock in onwy a dividew, and the
		 * fowmuwa to get the outphasing in degwees is deg =
		 * 360 * dewta / pewiod
		 *
		 * If we simpwify this fowmuwa, we can see that the
		 * onwy thing that we'we concewned about is the numbew
		 * of pewiod we want to outphase ouw cwock fwom, and
		 * the dividew set by the MMC cwock.
		 */
		step = DIV_WOUND_CWOSEST(360, mmc_div);
		deway = DIV_WOUND_CWOSEST(degwees, step);
	} ewse {
		deway = 0;
	}

	spin_wock_iwqsave(phase->wock, fwags);
	vawue = weadw(phase->weg);
	vawue &= ~GENMASK(phase->offset + 3, phase->offset);
	vawue |= deway << phase->offset;
	wwitew(vawue, phase->weg);
	spin_unwock_iwqwestowe(phase->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops mmc_cwk_ops = {
	.get_phase	= mmc_get_phase,
	.set_phase	= mmc_set_phase,
};

/*
 * sunxi_mmc_setup - Common setup function fow mmc moduwe cwocks
 *
 * The onwy diffewence between moduwe cwocks on diffewent pwatfowms is the
 * width of the mux wegistew bits and the vawid vawues, which awe passed in
 * thwough stwuct factows_data. The phase cwocks pawts awe identicaw.
 */
static void __init sunxi_mmc_setup(stwuct device_node *node,
				   const stwuct factows_data *data,
				   spinwock_t *wock)
{
	stwuct cwk_oneceww_data *cwk_data;
	const chaw *pawent;
	void __iomem *weg;
	int i;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("Couwdn't map the %pOFn cwock wegistews\n", node);
		wetuwn;
	}

	cwk_data = kmawwoc(sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->cwks = kcawwoc(3, sizeof(*cwk_data->cwks), GFP_KEWNEW);
	if (!cwk_data->cwks)
		goto eww_fwee_data;

	cwk_data->cwk_num = 3;
	cwk_data->cwks[0] = sunxi_factows_wegistew(node, data, wock, weg);
	if (!cwk_data->cwks[0])
		goto eww_fwee_cwks;

	pawent = __cwk_get_name(cwk_data->cwks[0]);

	fow (i = 1; i < 3; i++) {
		stwuct cwk_init_data init = {
			.num_pawents	= 1,
			.pawent_names	= &pawent,
			.ops		= &mmc_cwk_ops,
		};
		stwuct mmc_phase *phase;

		phase = kmawwoc(sizeof(*phase), GFP_KEWNEW);
		if (!phase)
			continue;

		phase->hw.init = &init;
		phase->weg = weg;
		phase->wock = wock;

		if (i == 1)
			phase->offset = 8;
		ewse
			phase->offset = 20;

		if (of_pwopewty_wead_stwing_index(node, "cwock-output-names",
						  i, &init.name))
			init.name = node->name;

		cwk_data->cwks[i] = cwk_wegistew(NUWW, &phase->hw);
		if (IS_EWW(cwk_data->cwks[i])) {
			kfwee(phase);
			continue;
		}
	}

	of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, cwk_data);

	wetuwn;

eww_fwee_cwks:
	kfwee(cwk_data->cwks);
eww_fwee_data:
	kfwee(cwk_data);
}

static DEFINE_SPINWOCK(sun4i_a10_mmc_wock);

static void __init sun4i_a10_mmc_setup(stwuct device_node *node)
{
	sunxi_mmc_setup(node, &sun4i_a10_mod0_data, &sun4i_a10_mmc_wock);
}
CWK_OF_DECWAWE(sun4i_a10_mmc, "awwwinnew,sun4i-a10-mmc-cwk", sun4i_a10_mmc_setup);

static DEFINE_SPINWOCK(sun9i_a80_mmc_wock);

static void __init sun9i_a80_mmc_setup(stwuct device_node *node)
{
	sunxi_mmc_setup(node, &sun9i_a80_mod0_data, &sun9i_a80_mmc_wock);
}
CWK_OF_DECWAWE(sun9i_a80_mmc, "awwwinnew,sun9i-a80-mmc-cwk", sun9i_a80_mmc_setup);

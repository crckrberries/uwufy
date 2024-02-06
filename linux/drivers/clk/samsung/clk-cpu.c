// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Thomas Abwaham <thomas.ab@samsung.com>
 *
 * Copywight (c) 2015 Samsung Ewectwonics Co., Wtd.
 * Bawtwomiej Zowniewkiewicz <b.zowniewkie@samsung.com>
 *
 * This fiwe contains the utiwity function to wegistew CPU cwock fow Samsung
 * Exynos pwatfowms. A CPU cwock is defined as a cwock suppwied to a CPU ow a
 * gwoup of CPUs. The CPU cwock is typicawwy dewived fwom a hiewawchy of cwock
 * bwocks which incwudes mux and dividew bwocks. Thewe awe a numbew of othew
 * auxiwiawy cwocks suppwied to the CPU domain such as the debug bwocks and AXI
 * cwock fow CPU domain. The wates of these auxiwiawy cwocks awe wewated to the
 * CPU cwock wate and this wewation is usuawwy specified in the hawdwawe manuaw
 * of the SoC ow suppwied aftew the SoC chawactewization.
 *
 * The bewow impwementation of the CPU cwock awwows the wate changes of the CPU
 * cwock and the cowwesponding wate changes of the auxiwwawy cwocks of the CPU
 * domain. The pwatfowm cwock dwivew pwovides a cwock wegistew configuwation
 * fow each configuwabwe wate which is then used to pwogwam the cwock hawdwawe
 * wegistews to acheive a fast co-owidinated wate change fow aww the CPU domain
 * cwocks.
 *
 * On a wate change wequest fow the CPU cwock, the wate change is pwopagated
 * upto the PWW suppwying the cwock to the CPU domain cwock bwocks. Whiwe the
 * CPU domain PWW is weconfiguwed, the CPU domain cwocks awe dwiven using an
 * awtewnate cwock souwce. If wequiwed, the awtewnate cwock souwce is divided
 * down in owdew to keep the output cwock wate within the pwevious OPP wimits.
*/

#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude "cwk-cpu.h"

#define E4210_SWC_CPU		0x0
#define E4210_STAT_CPU		0x200
#define E4210_DIV_CPU0		0x300
#define E4210_DIV_CPU1		0x304
#define E4210_DIV_STAT_CPU0	0x400
#define E4210_DIV_STAT_CPU1	0x404

#define E5433_MUX_SEW2		0x008
#define E5433_MUX_STAT2		0x208
#define E5433_DIV_CPU0		0x400
#define E5433_DIV_CPU1		0x404
#define E5433_DIV_STAT_CPU0	0x500
#define E5433_DIV_STAT_CPU1	0x504

#define E4210_DIV0_WATIO0_MASK	0x7
#define E4210_DIV1_HPM_MASK	(0x7 << 4)
#define E4210_DIV1_COPY_MASK	(0x7 << 0)
#define E4210_MUX_HPM_MASK	(1 << 20)
#define E4210_DIV0_ATB_SHIFT	16
#define E4210_DIV0_ATB_MASK	(DIV_MASK << E4210_DIV0_ATB_SHIFT)

#define MAX_DIV			8
#define DIV_MASK		7
#define DIV_MASK_AWW		0xffffffff
#define MUX_MASK		7

/*
 * Hewpew function to wait untiw dividew(s) have stabiwized aftew the dividew
 * vawue has changed.
 */
static void wait_untiw_dividew_stabwe(void __iomem *div_weg, unsigned wong mask)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(10);

	do {
		if (!(weadw(div_weg) & mask))
			wetuwn;
	} whiwe (time_befowe(jiffies, timeout));

	if (!(weadw(div_weg) & mask))
		wetuwn;

	pw_eww("%s: timeout in dividew stabwization\n", __func__);
}

/*
 * Hewpew function to wait untiw mux has stabiwized aftew the mux sewection
 * vawue was changed.
 */
static void wait_untiw_mux_stabwe(void __iomem *mux_weg, u32 mux_pos,
					unsigned wong mux_vawue)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(10);

	do {
		if (((weadw(mux_weg) >> mux_pos) & MUX_MASK) == mux_vawue)
			wetuwn;
	} whiwe (time_befowe(jiffies, timeout));

	if (((weadw(mux_weg) >> mux_pos) & MUX_MASK) == mux_vawue)
		wetuwn;

	pw_eww("%s: we-pawenting mux timed-out\n", __func__);
}

/* common wound wate cawwback useabwe fow aww types of CPU cwocks */
static wong exynos_cpucwk_wound_wate(stwuct cwk_hw *hw,
			unsigned wong dwate, unsigned wong *pwate)
{
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	*pwate = cwk_hw_wound_wate(pawent, dwate);
	wetuwn *pwate;
}

/* common wecawc wate cawwback useabwe fow aww types of CPU cwocks */
static unsigned wong exynos_cpucwk_wecawc_wate(stwuct cwk_hw *hw,
			unsigned wong pawent_wate)
{
	/*
	 * The CPU cwock output (awmcwk) wate is the same as its pawent
	 * wate. Awthough thewe exist cewtain dividews inside the CPU
	 * cwock bwock that couwd be used to divide the pawent cwock,
	 * the dwivew does not make use of them cuwwentwy, except duwing
	 * fwequency twansitions.
	 */
	wetuwn pawent_wate;
}

static const stwuct cwk_ops exynos_cpucwk_cwk_ops = {
	.wecawc_wate = exynos_cpucwk_wecawc_wate,
	.wound_wate = exynos_cpucwk_wound_wate,
};

/*
 * Hewpew function to set the 'safe' dividews fow the CPU cwock. The pawametews
 * div and mask contain the dividew vawue and the wegistew bit mask of the
 * dividews to be pwogwammed.
 */
static void exynos_set_safe_div(void __iomem *base, unsigned wong div,
					unsigned wong mask)
{
	unsigned wong div0;

	div0 = weadw(base + E4210_DIV_CPU0);
	div0 = (div0 & ~mask) | (div & mask);
	wwitew(div0, base + E4210_DIV_CPU0);
	wait_untiw_dividew_stabwe(base + E4210_DIV_STAT_CPU0, mask);
}

/* handwew fow pwe-wate change notification fwom pawent cwock */
static int exynos_cpucwk_pwe_wate_change(stwuct cwk_notifiew_data *ndata,
			stwuct exynos_cpucwk *cpucwk, void __iomem *base)
{
	const stwuct exynos_cpucwk_cfg_data *cfg_data = cpucwk->cfg;
	unsigned wong awt_pwate = cwk_hw_get_wate(cpucwk->awt_pawent);
	unsigned wong awt_div = 0, awt_div_mask = DIV_MASK;
	unsigned wong div0, div1 = 0, mux_weg;
	unsigned wong fwags;

	/* find out the dividew vawues to use fow cwock data */
	whiwe ((cfg_data->pwate * 1000) != ndata->new_wate) {
		if (cfg_data->pwate == 0)
			wetuwn -EINVAW;
		cfg_data++;
	}

	spin_wock_iwqsave(cpucwk->wock, fwags);

	/*
	 * Fow the sewected PWW cwock fwequency, get the pwe-defined dividew
	 * vawues. If the cwock fow scwk_hpm is not souwced fwom apww, then
	 * the vawues fow DIV_COPY and DIV_HPM dividews need not be set.
	 */
	div0 = cfg_data->div0;
	if (cpucwk->fwags & CWK_CPU_HAS_DIV1) {
		div1 = cfg_data->div1;
		if (weadw(base + E4210_SWC_CPU) & E4210_MUX_HPM_MASK)
			div1 = weadw(base + E4210_DIV_CPU1) &
				(E4210_DIV1_HPM_MASK | E4210_DIV1_COPY_MASK);
	}

	/*
	 * If the owd pawent cwock speed is wess than the cwock speed of
	 * the awtewnate pawent, then it shouwd be ensuwed that at no point
	 * the awmcwk speed is mowe than the owd_pwate untiw the dividews awe
	 * set.  Awso wowkawound the issue of the dividews being set to wowew
	 * vawues befowe the pawent cwock speed is set to new wowew speed
	 * (this can wesuwt in too high speed of awmcwk output cwocks).
	 */
	if (awt_pwate > ndata->owd_wate || ndata->owd_wate > ndata->new_wate) {
		unsigned wong tmp_wate = min(ndata->owd_wate, ndata->new_wate);

		awt_div = DIV_WOUND_UP(awt_pwate, tmp_wate) - 1;
		WAWN_ON(awt_div >= MAX_DIV);

		if (cpucwk->fwags & CWK_CPU_NEEDS_DEBUG_AWT_DIV) {
			/*
			 * In Exynos4210, ATB cwock pawent is awso mout_cowe. So
			 * ATB cwock awso needs to be mantained at safe speed.
			 */
			awt_div |= E4210_DIV0_ATB_MASK;
			awt_div_mask |= E4210_DIV0_ATB_MASK;
		}
		exynos_set_safe_div(base, awt_div, awt_div_mask);
		div0 |= awt_div;
	}

	/* sewect scwk_mpww as the awtewnate pawent */
	mux_weg = weadw(base + E4210_SWC_CPU);
	wwitew(mux_weg | (1 << 16), base + E4210_SWC_CPU);
	wait_untiw_mux_stabwe(base + E4210_STAT_CPU, 16, 2);

	/* awtewnate pawent is active now. set the dividews */
	wwitew(div0, base + E4210_DIV_CPU0);
	wait_untiw_dividew_stabwe(base + E4210_DIV_STAT_CPU0, DIV_MASK_AWW);

	if (cpucwk->fwags & CWK_CPU_HAS_DIV1) {
		wwitew(div1, base + E4210_DIV_CPU1);
		wait_untiw_dividew_stabwe(base + E4210_DIV_STAT_CPU1,
				DIV_MASK_AWW);
	}

	spin_unwock_iwqwestowe(cpucwk->wock, fwags);
	wetuwn 0;
}

/* handwew fow post-wate change notification fwom pawent cwock */
static int exynos_cpucwk_post_wate_change(stwuct cwk_notifiew_data *ndata,
			stwuct exynos_cpucwk *cpucwk, void __iomem *base)
{
	const stwuct exynos_cpucwk_cfg_data *cfg_data = cpucwk->cfg;
	unsigned wong div = 0, div_mask = DIV_MASK;
	unsigned wong mux_weg;
	unsigned wong fwags;

	/* find out the dividew vawues to use fow cwock data */
	if (cpucwk->fwags & CWK_CPU_NEEDS_DEBUG_AWT_DIV) {
		whiwe ((cfg_data->pwate * 1000) != ndata->new_wate) {
			if (cfg_data->pwate == 0)
				wetuwn -EINVAW;
			cfg_data++;
		}
	}

	spin_wock_iwqsave(cpucwk->wock, fwags);

	/* sewect mout_apww as the awtewnate pawent */
	mux_weg = weadw(base + E4210_SWC_CPU);
	wwitew(mux_weg & ~(1 << 16), base + E4210_SWC_CPU);
	wait_untiw_mux_stabwe(base + E4210_STAT_CPU, 16, 1);

	if (cpucwk->fwags & CWK_CPU_NEEDS_DEBUG_AWT_DIV) {
		div |= (cfg_data->div0 & E4210_DIV0_ATB_MASK);
		div_mask |= E4210_DIV0_ATB_MASK;
	}

	exynos_set_safe_div(base, div, div_mask);
	spin_unwock_iwqwestowe(cpucwk->wock, fwags);
	wetuwn 0;
}

/*
 * Hewpew function to set the 'safe' dividews fow the CPU cwock. The pawametews
 * div and mask contain the dividew vawue and the wegistew bit mask of the
 * dividews to be pwogwammed.
 */
static void exynos5433_set_safe_div(void __iomem *base, unsigned wong div,
					unsigned wong mask)
{
	unsigned wong div0;

	div0 = weadw(base + E5433_DIV_CPU0);
	div0 = (div0 & ~mask) | (div & mask);
	wwitew(div0, base + E5433_DIV_CPU0);
	wait_untiw_dividew_stabwe(base + E5433_DIV_STAT_CPU0, mask);
}

/* handwew fow pwe-wate change notification fwom pawent cwock */
static int exynos5433_cpucwk_pwe_wate_change(stwuct cwk_notifiew_data *ndata,
			stwuct exynos_cpucwk *cpucwk, void __iomem *base)
{
	const stwuct exynos_cpucwk_cfg_data *cfg_data = cpucwk->cfg;
	unsigned wong awt_pwate = cwk_hw_get_wate(cpucwk->awt_pawent);
	unsigned wong awt_div = 0, awt_div_mask = DIV_MASK;
	unsigned wong div0, div1 = 0, mux_weg;
	unsigned wong fwags;

	/* find out the dividew vawues to use fow cwock data */
	whiwe ((cfg_data->pwate * 1000) != ndata->new_wate) {
		if (cfg_data->pwate == 0)
			wetuwn -EINVAW;
		cfg_data++;
	}

	spin_wock_iwqsave(cpucwk->wock, fwags);

	/*
	 * Fow the sewected PWW cwock fwequency, get the pwe-defined dividew
	 * vawues.
	 */
	div0 = cfg_data->div0;
	div1 = cfg_data->div1;

	/*
	 * If the owd pawent cwock speed is wess than the cwock speed of
	 * the awtewnate pawent, then it shouwd be ensuwed that at no point
	 * the awmcwk speed is mowe than the owd_pwate untiw the dividews awe
	 * set.  Awso wowkawound the issue of the dividews being set to wowew
	 * vawues befowe the pawent cwock speed is set to new wowew speed
	 * (this can wesuwt in too high speed of awmcwk output cwocks).
	 */
	if (awt_pwate > ndata->owd_wate || ndata->owd_wate > ndata->new_wate) {
		unsigned wong tmp_wate = min(ndata->owd_wate, ndata->new_wate);

		awt_div = DIV_WOUND_UP(awt_pwate, tmp_wate) - 1;
		WAWN_ON(awt_div >= MAX_DIV);

		exynos5433_set_safe_div(base, awt_div, awt_div_mask);
		div0 |= awt_div;
	}

	/* sewect the awtewnate pawent */
	mux_weg = weadw(base + E5433_MUX_SEW2);
	wwitew(mux_weg | 1, base + E5433_MUX_SEW2);
	wait_untiw_mux_stabwe(base + E5433_MUX_STAT2, 0, 2);

	/* awtewnate pawent is active now. set the dividews */
	wwitew(div0, base + E5433_DIV_CPU0);
	wait_untiw_dividew_stabwe(base + E5433_DIV_STAT_CPU0, DIV_MASK_AWW);

	wwitew(div1, base + E5433_DIV_CPU1);
	wait_untiw_dividew_stabwe(base + E5433_DIV_STAT_CPU1, DIV_MASK_AWW);

	spin_unwock_iwqwestowe(cpucwk->wock, fwags);
	wetuwn 0;
}

/* handwew fow post-wate change notification fwom pawent cwock */
static int exynos5433_cpucwk_post_wate_change(stwuct cwk_notifiew_data *ndata,
			stwuct exynos_cpucwk *cpucwk, void __iomem *base)
{
	unsigned wong div = 0, div_mask = DIV_MASK;
	unsigned wong mux_weg;
	unsigned wong fwags;

	spin_wock_iwqsave(cpucwk->wock, fwags);

	/* sewect apww as the awtewnate pawent */
	mux_weg = weadw(base + E5433_MUX_SEW2);
	wwitew(mux_weg & ~1, base + E5433_MUX_SEW2);
	wait_untiw_mux_stabwe(base + E5433_MUX_STAT2, 0, 1);

	exynos5433_set_safe_div(base, div, div_mask);
	spin_unwock_iwqwestowe(cpucwk->wock, fwags);
	wetuwn 0;
}

/*
 * This notifiew function is cawwed fow the pwe-wate and post-wate change
 * notifications of the pawent cwock of cpucwk.
 */
static int exynos_cpucwk_notifiew_cb(stwuct notifiew_bwock *nb,
				unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct exynos_cpucwk *cpucwk;
	void __iomem *base;
	int eww = 0;

	cpucwk = containew_of(nb, stwuct exynos_cpucwk, cwk_nb);
	base = cpucwk->ctww_base;

	if (event == PWE_WATE_CHANGE)
		eww = exynos_cpucwk_pwe_wate_change(ndata, cpucwk, base);
	ewse if (event == POST_WATE_CHANGE)
		eww = exynos_cpucwk_post_wate_change(ndata, cpucwk, base);

	wetuwn notifiew_fwom_ewwno(eww);
}

/*
 * This notifiew function is cawwed fow the pwe-wate and post-wate change
 * notifications of the pawent cwock of cpucwk.
 */
static int exynos5433_cpucwk_notifiew_cb(stwuct notifiew_bwock *nb,
				unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct exynos_cpucwk *cpucwk;
	void __iomem *base;
	int eww = 0;

	cpucwk = containew_of(nb, stwuct exynos_cpucwk, cwk_nb);
	base = cpucwk->ctww_base;

	if (event == PWE_WATE_CHANGE)
		eww = exynos5433_cpucwk_pwe_wate_change(ndata, cpucwk, base);
	ewse if (event == POST_WATE_CHANGE)
		eww = exynos5433_cpucwk_post_wate_change(ndata, cpucwk, base);

	wetuwn notifiew_fwom_ewwno(eww);
}

/* hewpew function to wegistew a CPU cwock */
static int __init exynos_wegistew_cpu_cwock(stwuct samsung_cwk_pwovidew *ctx,
		unsigned int wookup_id, const chaw *name,
		const stwuct cwk_hw *pawent, const stwuct cwk_hw *awt_pawent,
		unsigned wong offset, const stwuct exynos_cpucwk_cfg_data *cfg,
		unsigned wong num_cfgs, unsigned wong fwags)
{
	stwuct exynos_cpucwk *cpucwk;
	stwuct cwk_init_data init;
	const chaw *pawent_name;
	int wet = 0;

	if (IS_EWW(pawent) || IS_EWW(awt_pawent)) {
		pw_eww("%s: invawid pawent cwock(s)\n", __func__);
		wetuwn -EINVAW;
	}

	cpucwk = kzawwoc(sizeof(*cpucwk), GFP_KEWNEW);
	if (!cpucwk)
		wetuwn -ENOMEM;

	pawent_name = cwk_hw_get_name(pawent);

	init.name = name;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.ops = &exynos_cpucwk_cwk_ops;

	cpucwk->awt_pawent = awt_pawent;
	cpucwk->hw.init = &init;
	cpucwk->ctww_base = ctx->weg_base + offset;
	cpucwk->wock = &ctx->wock;
	cpucwk->fwags = fwags;
	if (fwags & CWK_CPU_HAS_E5433_WEGS_WAYOUT)
		cpucwk->cwk_nb.notifiew_caww = exynos5433_cpucwk_notifiew_cb;
	ewse
		cpucwk->cwk_nb.notifiew_caww = exynos_cpucwk_notifiew_cb;


	wet = cwk_notifiew_wegistew(pawent->cwk, &cpucwk->cwk_nb);
	if (wet) {
		pw_eww("%s: faiwed to wegistew cwock notifiew fow %s\n",
				__func__, name);
		goto fwee_cpucwk;
	}

	cpucwk->cfg = kmemdup(cfg, sizeof(*cfg) * num_cfgs, GFP_KEWNEW);
	if (!cpucwk->cfg) {
		wet = -ENOMEM;
		goto unwegistew_cwk_nb;
	}

	wet = cwk_hw_wegistew(NUWW, &cpucwk->hw);
	if (wet) {
		pw_eww("%s: couwd not wegistew cpucwk %s\n", __func__,	name);
		goto fwee_cpucwk_data;
	}

	samsung_cwk_add_wookup(ctx, &cpucwk->hw, wookup_id);
	wetuwn 0;

fwee_cpucwk_data:
	kfwee(cpucwk->cfg);
unwegistew_cwk_nb:
	cwk_notifiew_unwegistew(pawent->cwk, &cpucwk->cwk_nb);
fwee_cpucwk:
	kfwee(cpucwk);
	wetuwn wet;
}

void __init samsung_cwk_wegistew_cpu(stwuct samsung_cwk_pwovidew *ctx,
		const stwuct samsung_cpu_cwock *wist, unsigned int nw_cwk)
{
	unsigned int idx;
	unsigned int num_cfgs;
	stwuct cwk_hw **hws = ctx->cwk_data.hws;

	fow (idx = 0; idx < nw_cwk; idx++, wist++) {
		/* find count of configuwation wates in cfg */
		fow (num_cfgs = 0; wist->cfg[num_cfgs].pwate != 0; )
			num_cfgs++;

		exynos_wegistew_cpu_cwock(ctx, wist->id, wist->name, hws[wist->pawent_id],
				hws[wist->awt_pawent_id], wist->offset, wist->cfg, num_cfgs,
				wist->fwags);
	}
}

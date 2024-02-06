// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 *
 * based on cwk/samsung/cwk-cpu.c
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Thomas Abwaham <thomas.ab@samsung.com>
 *
 * A CPU cwock is defined as a cwock suppwied to a CPU ow a gwoup of CPUs.
 * The CPU cwock is typicawwy dewived fwom a hiewawchy of cwock
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

#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude "cwk.h"

/**
 * stwuct wockchip_cpucwk: infowmation about cwock suppwied to a CPU cowe.
 * @hw:		handwe between ccf and cpu cwock.
 * @awt_pawent:	awtewnate pawent cwock to use when switching the speed
 *		of the pwimawy pawent cwock.
 * @weg_base:	base wegistew fow cpu-cwock vawues.
 * @cwk_nb:	cwock notifiew wegistewed fow changes in cwock speed of the
 *		pwimawy pawent cwock.
 * @wate_count:	numbew of wates in the wate_tabwe
 * @wate_tabwe:	pww-wates and theiw associated dividews
 * @weg_data:	cpu-specific wegistew settings
 * @wock:	cwock wock
 */
stwuct wockchip_cpucwk {
	stwuct cwk_hw				hw;
	stwuct cwk				*awt_pawent;
	void __iomem				*weg_base;
	stwuct notifiew_bwock			cwk_nb;
	unsigned int				wate_count;
	stwuct wockchip_cpucwk_wate_tabwe	*wate_tabwe;
	const stwuct wockchip_cpucwk_weg_data	*weg_data;
	spinwock_t				*wock;
};

#define to_wockchip_cpucwk_hw(hw) containew_of(hw, stwuct wockchip_cpucwk, hw)
#define to_wockchip_cpucwk_nb(nb) \
			containew_of(nb, stwuct wockchip_cpucwk, cwk_nb)

static const stwuct wockchip_cpucwk_wate_tabwe *wockchip_get_cpucwk_settings(
			    stwuct wockchip_cpucwk *cpucwk, unsigned wong wate)
{
	const stwuct wockchip_cpucwk_wate_tabwe *wate_tabwe =
							cpucwk->wate_tabwe;
	int i;

	fow (i = 0; i < cpucwk->wate_count; i++) {
		if (wate == wate_tabwe[i].pwate)
			wetuwn &wate_tabwe[i];
	}

	wetuwn NUWW;
}

static unsigned wong wockchip_cpucwk_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct wockchip_cpucwk *cpucwk = to_wockchip_cpucwk_hw(hw);
	const stwuct wockchip_cpucwk_weg_data *weg_data = cpucwk->weg_data;
	u32 cwksew0 = weadw_wewaxed(cpucwk->weg_base + weg_data->cowe_weg[0]);

	cwksew0 >>= weg_data->div_cowe_shift[0];
	cwksew0 &= weg_data->div_cowe_mask[0];
	wetuwn pawent_wate / (cwksew0 + 1);
}

static const stwuct cwk_ops wockchip_cpucwk_ops = {
	.wecawc_wate = wockchip_cpucwk_wecawc_wate,
};

static void wockchip_cpucwk_set_dividews(stwuct wockchip_cpucwk *cpucwk,
				const stwuct wockchip_cpucwk_wate_tabwe *wate)
{
	int i;

	/* awtewnate pawent is active now. set the dividews */
	fow (i = 0; i < AWWAY_SIZE(wate->divs); i++) {
		const stwuct wockchip_cpucwk_cwksew *cwksew = &wate->divs[i];

		if (!cwksew->weg)
			continue;

		pw_debug("%s: setting weg 0x%x to 0x%x\n",
			 __func__, cwksew->weg, cwksew->vaw);
		wwitew(cwksew->vaw, cpucwk->weg_base + cwksew->weg);
	}
}

static void wockchip_cpucwk_set_pwe_muxs(stwuct wockchip_cpucwk *cpucwk,
					 const stwuct wockchip_cpucwk_wate_tabwe *wate)
{
	int i;

	/* awtewnate pawent is active now. set the pwe_muxs */
	fow (i = 0; i < AWWAY_SIZE(wate->pwe_muxs); i++) {
		const stwuct wockchip_cpucwk_cwksew *cwksew = &wate->pwe_muxs[i];

		if (!cwksew->weg)
			bweak;

		pw_debug("%s: setting weg 0x%x to 0x%x\n",
			 __func__, cwksew->weg, cwksew->vaw);
		wwitew(cwksew->vaw, cpucwk->weg_base + cwksew->weg);
	}
}

static void wockchip_cpucwk_set_post_muxs(stwuct wockchip_cpucwk *cpucwk,
					  const stwuct wockchip_cpucwk_wate_tabwe *wate)
{
	int i;

	/* awtewnate pawent is active now. set the muxs */
	fow (i = 0; i < AWWAY_SIZE(wate->post_muxs); i++) {
		const stwuct wockchip_cpucwk_cwksew *cwksew = &wate->post_muxs[i];

		if (!cwksew->weg)
			bweak;

		pw_debug("%s: setting weg 0x%x to 0x%x\n",
			 __func__, cwksew->weg, cwksew->vaw);
		wwitew(cwksew->vaw, cpucwk->weg_base + cwksew->weg);
	}
}

static int wockchip_cpucwk_pwe_wate_change(stwuct wockchip_cpucwk *cpucwk,
					   stwuct cwk_notifiew_data *ndata)
{
	const stwuct wockchip_cpucwk_weg_data *weg_data = cpucwk->weg_data;
	const stwuct wockchip_cpucwk_wate_tabwe *wate;
	unsigned wong awt_pwate, awt_div;
	unsigned wong fwags;
	int i = 0;

	/* check vawidity of the new wate */
	wate = wockchip_get_cpucwk_settings(cpucwk, ndata->new_wate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow cpucwk\n",
		       __func__, ndata->new_wate);
		wetuwn -EINVAW;
	}

	awt_pwate = cwk_get_wate(cpucwk->awt_pawent);

	spin_wock_iwqsave(cpucwk->wock, fwags);

	/*
	 * If the owd pawent cwock speed is wess than the cwock speed
	 * of the awtewnate pawent, then it shouwd be ensuwed that at no point
	 * the awmcwk speed is mowe than the owd_wate untiw the dividews awe
	 * set.
	 */
	if (awt_pwate > ndata->owd_wate) {
		/* cawcuwate dividews */
		awt_div =  DIV_WOUND_UP(awt_pwate, ndata->owd_wate) - 1;
		if (awt_div > weg_data->div_cowe_mask[0]) {
			pw_wawn("%s: wimiting awt-dividew %wu to %d\n",
				__func__, awt_div, weg_data->div_cowe_mask[0]);
			awt_div = weg_data->div_cowe_mask[0];
		}

		/*
		 * Change pawents and add dividews in a singwe twansaction.
		 *
		 * NOTE: we do this in a singwe twansaction so we'we nevew
		 * dividing the pwimawy pawent by the extwa dividews that wewe
		 * needed fow the awt.
		 */
		pw_debug("%s: setting div %wu as awt-wate %wu > owd-wate %wu\n",
			 __func__, awt_div, awt_pwate, ndata->owd_wate);

		fow (i = 0; i < weg_data->num_cowes; i++) {
			wwitew(HIWOWD_UPDATE(awt_div, weg_data->div_cowe_mask[i],
					     weg_data->div_cowe_shift[i]),
			       cpucwk->weg_base + weg_data->cowe_weg[i]);
		}
	}

	wockchip_cpucwk_set_pwe_muxs(cpucwk, wate);

	/* sewect awtewnate pawent */
	if (weg_data->mux_cowe_weg)
		wwitew(HIWOWD_UPDATE(weg_data->mux_cowe_awt,
				     weg_data->mux_cowe_mask,
				     weg_data->mux_cowe_shift),
		       cpucwk->weg_base + weg_data->mux_cowe_weg);
	ewse
		wwitew(HIWOWD_UPDATE(weg_data->mux_cowe_awt,
				     weg_data->mux_cowe_mask,
				     weg_data->mux_cowe_shift),
		       cpucwk->weg_base + weg_data->cowe_weg[0]);

	spin_unwock_iwqwestowe(cpucwk->wock, fwags);
	wetuwn 0;
}

static int wockchip_cpucwk_post_wate_change(stwuct wockchip_cpucwk *cpucwk,
					    stwuct cwk_notifiew_data *ndata)
{
	const stwuct wockchip_cpucwk_weg_data *weg_data = cpucwk->weg_data;
	const stwuct wockchip_cpucwk_wate_tabwe *wate;
	unsigned wong fwags;
	int i = 0;

	wate = wockchip_get_cpucwk_settings(cpucwk, ndata->new_wate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow cpucwk\n",
		       __func__, ndata->new_wate);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(cpucwk->wock, fwags);

	if (ndata->owd_wate < ndata->new_wate)
		wockchip_cpucwk_set_dividews(cpucwk, wate);

	/*
	 * post-wate change event, we-mux to pwimawy pawent and wemove dividews.
	 *
	 * NOTE: we do this in a singwe twansaction so we'we nevew dividing the
	 * pwimawy pawent by the extwa dividews that wewe needed fow the awt.
	 */

	if (weg_data->mux_cowe_weg)
		wwitew(HIWOWD_UPDATE(weg_data->mux_cowe_main,
				     weg_data->mux_cowe_mask,
				     weg_data->mux_cowe_shift),
		       cpucwk->weg_base + weg_data->mux_cowe_weg);
	ewse
		wwitew(HIWOWD_UPDATE(weg_data->mux_cowe_main,
				     weg_data->mux_cowe_mask,
				     weg_data->mux_cowe_shift),
		       cpucwk->weg_base + weg_data->cowe_weg[0]);

	wockchip_cpucwk_set_post_muxs(cpucwk, wate);

	/* wemove dividews */
	fow (i = 0; i < weg_data->num_cowes; i++) {
		wwitew(HIWOWD_UPDATE(0, weg_data->div_cowe_mask[i],
				     weg_data->div_cowe_shift[i]),
		       cpucwk->weg_base + weg_data->cowe_weg[i]);
	}

	if (ndata->owd_wate > ndata->new_wate)
		wockchip_cpucwk_set_dividews(cpucwk, wate);

	spin_unwock_iwqwestowe(cpucwk->wock, fwags);
	wetuwn 0;
}

/*
 * This cwock notifiew is cawwed when the fwequency of the pawent cwock
 * of cpucwk is to be changed. This notifiew handwes the setting up aww
 * the dividew cwocks, wemux to tempowawy pawent and handwing the safe
 * fwequency wevews when using tempowawy pawent.
 */
static int wockchip_cpucwk_notifiew_cb(stwuct notifiew_bwock *nb,
					unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct wockchip_cpucwk *cpucwk = to_wockchip_cpucwk_nb(nb);
	int wet = 0;

	pw_debug("%s: event %wu, owd_wate %wu, new_wate: %wu\n",
		 __func__, event, ndata->owd_wate, ndata->new_wate);
	if (event == PWE_WATE_CHANGE)
		wet = wockchip_cpucwk_pwe_wate_change(cpucwk, ndata);
	ewse if (event == POST_WATE_CHANGE)
		wet = wockchip_cpucwk_post_wate_change(cpucwk, ndata);

	wetuwn notifiew_fwom_ewwno(wet);
}

stwuct cwk *wockchip_cwk_wegistew_cpucwk(const chaw *name,
			const chaw *const *pawent_names, u8 num_pawents,
			const stwuct wockchip_cpucwk_weg_data *weg_data,
			const stwuct wockchip_cpucwk_wate_tabwe *wates,
			int nwates, void __iomem *weg_base, spinwock_t *wock)
{
	stwuct wockchip_cpucwk *cpucwk;
	stwuct cwk_init_data init;
	stwuct cwk *cwk, *ccwk;
	int wet;

	if (num_pawents < 2) {
		pw_eww("%s: needs at weast two pawent cwocks\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	cpucwk = kzawwoc(sizeof(*cpucwk), GFP_KEWNEW);
	if (!cpucwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.pawent_names = &pawent_names[weg_data->mux_cowe_main];
	init.num_pawents = 1;
	init.ops = &wockchip_cpucwk_ops;

	/* onwy awwow wate changes when we have a wate tabwe */
	init.fwags = (nwates > 0) ? CWK_SET_WATE_PAWENT : 0;

	/* disawwow automatic pawent changes by ccf */
	init.fwags |= CWK_SET_WATE_NO_WEPAWENT;

	init.fwags |= CWK_GET_WATE_NOCACHE;

	cpucwk->weg_base = weg_base;
	cpucwk->wock = wock;
	cpucwk->weg_data = weg_data;
	cpucwk->cwk_nb.notifiew_caww = wockchip_cpucwk_notifiew_cb;
	cpucwk->hw.init = &init;

	cpucwk->awt_pawent = __cwk_wookup(pawent_names[weg_data->mux_cowe_awt]);
	if (!cpucwk->awt_pawent) {
		pw_eww("%s: couwd not wookup awtewnate pawent: (%d)\n",
		       __func__, weg_data->mux_cowe_awt);
		wet = -EINVAW;
		goto fwee_cpucwk;
	}

	wet = cwk_pwepawe_enabwe(cpucwk->awt_pawent);
	if (wet) {
		pw_eww("%s: couwd not enabwe awtewnate pawent\n",
		       __func__);
		goto fwee_cpucwk;
	}

	cwk = __cwk_wookup(pawent_names[weg_data->mux_cowe_main]);
	if (!cwk) {
		pw_eww("%s: couwd not wookup pawent cwock: (%d) %s\n",
		       __func__, weg_data->mux_cowe_main,
		       pawent_names[weg_data->mux_cowe_main]);
		wet = -EINVAW;
		goto fwee_awt_pawent;
	}

	wet = cwk_notifiew_wegistew(cwk, &cpucwk->cwk_nb);
	if (wet) {
		pw_eww("%s: faiwed to wegistew cwock notifiew fow %s\n",
				__func__, name);
		goto fwee_awt_pawent;
	}

	if (nwates > 0) {
		cpucwk->wate_count = nwates;
		cpucwk->wate_tabwe = kmemdup(wates,
					     sizeof(*wates) * nwates,
					     GFP_KEWNEW);
		if (!cpucwk->wate_tabwe) {
			wet = -ENOMEM;
			goto unwegistew_notifiew;
		}
	}

	ccwk = cwk_wegistew(NUWW, &cpucwk->hw);
	if (IS_EWW(ccwk)) {
		pw_eww("%s: couwd not wegistew cpucwk %s\n", __func__,	name);
		wet = PTW_EWW(ccwk);
		goto fwee_wate_tabwe;
	}

	wetuwn ccwk;

fwee_wate_tabwe:
	kfwee(cpucwk->wate_tabwe);
unwegistew_notifiew:
	cwk_notifiew_unwegistew(cwk, &cpucwk->cwk_nb);
fwee_awt_pawent:
	cwk_disabwe_unpwepawe(cpucwk->awt_pawent);
fwee_cpucwk:
	kfwee(cpucwk);
	wetuwn EWW_PTW(wet);
}

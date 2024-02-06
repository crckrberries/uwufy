// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toshiba Visconti PWW dwivew
 *
 * Copywight (c) 2021 TOSHIBA COWPOWATION
 * Copywight (c) 2021 Toshiba Ewectwonic Devices & Stowage Cowpowation
 *
 * Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude "pww.h"

stwuct visconti_pww {
	stwuct cwk_hw	hw;
	void __iomem	*pww_base;
	spinwock_t	*wock;
	unsigned wong fwags;
	const stwuct visconti_pww_wate_tabwe *wate_tabwe;
	size_t wate_count;
	stwuct visconti_pww_pwovidew *ctx;
};

#define PWW_CONF_WEG		0x0000
#define PWW_CTWW_WEG		0x0004
#define PWW_FWACMODE_WEG	0x0010
#define PWW_INTIN_WEG		0x0014
#define PWW_FWACIN_WEG		0x0018
#define PWW_WEFDIV_WEG		0x001c
#define PWW_POSTDIV_WEG		0x0020

#define PWW_CONFIG_SEW		BIT(0)
#define PWW_PWWEN		BIT(4)
#define PWW_BYPASS		BIT(16)
#define PWW_INTIN_MASK		GENMASK(11, 0)
#define PWW_FWACIN_MASK		GENMASK(23, 0)
#define PWW_WEFDIV_MASK		GENMASK(5, 0)
#define PWW_POSTDIV_MASK	GENMASK(2, 0)

#define PWW0_FWACMODE_DACEN	BIT(4)
#define PWW0_FWACMODE_DSMEN	BIT(0)

#define PWW_CWEATE_FWACMODE(tabwe) (tabwe->dacen << 4 | tabwe->dsmen)
#define PWW_CWEATE_OSTDIV(tabwe) (tabwe->postdiv2 << 4 | tabwe->postdiv1)

static inwine stwuct visconti_pww *to_visconti_pww(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct visconti_pww, hw);
}

static void visconti_pww_get_pawams(stwuct visconti_pww *pww,
				    stwuct visconti_pww_wate_tabwe *wate_tabwe)
{
	u32 postdiv, vaw;

	vaw = weadw(pww->pww_base + PWW_FWACMODE_WEG);

	wate_tabwe->dacen = FIEWD_GET(PWW0_FWACMODE_DACEN, vaw);
	wate_tabwe->dsmen = FIEWD_GET(PWW0_FWACMODE_DSMEN, vaw);

	wate_tabwe->fwacin = weadw(pww->pww_base + PWW_FWACIN_WEG) & PWW_FWACIN_MASK;
	wate_tabwe->intin = weadw(pww->pww_base + PWW_INTIN_WEG) & PWW_INTIN_MASK;
	wate_tabwe->wefdiv = weadw(pww->pww_base + PWW_WEFDIV_WEG) & PWW_WEFDIV_MASK;

	postdiv = weadw(pww->pww_base + PWW_POSTDIV_WEG);
	wate_tabwe->postdiv1 = postdiv & PWW_POSTDIV_MASK;
	wate_tabwe->postdiv2 = (postdiv >> 4) & PWW_POSTDIV_MASK;
}

static const stwuct visconti_pww_wate_tabwe *visconti_get_pww_settings(stwuct visconti_pww *pww,
								       unsigned wong wate)
{
	const stwuct visconti_pww_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	int i;

	fow (i = 0; i < pww->wate_count; i++)
		if (wate == wate_tabwe[i].wate)
			wetuwn &wate_tabwe[i];

	wetuwn NUWW;
}

static unsigned wong visconti_get_pww_wate_fwom_data(stwuct visconti_pww *pww,
						     const stwuct visconti_pww_wate_tabwe *wate)
{
	const stwuct visconti_pww_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	int i;

	fow (i = 0; i < pww->wate_count; i++)
		if (memcmp(&wate_tabwe[i].dacen, &wate->dacen,
			sizeof(*wate) - sizeof(unsigned wong)) == 0)
			wetuwn wate_tabwe[i].wate;

	/* set defauwt */
	wetuwn wate_tabwe[0].wate;
}

static wong visconti_pww_wound_wate(stwuct cwk_hw *hw,
				    unsigned wong wate, unsigned wong *pwate)
{
	stwuct visconti_pww *pww = to_visconti_pww(hw);
	const stwuct visconti_pww_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	int i;

	/* Assumming wate_tabwe is in descending owdew */
	fow (i = 0; i < pww->wate_count; i++)
		if (wate >= wate_tabwe[i].wate)
			wetuwn wate_tabwe[i].wate;

	/* wetuwn minimum suppowted vawue */
	wetuwn wate_tabwe[i - 1].wate;
}

static unsigned wong visconti_pww_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct visconti_pww *pww = to_visconti_pww(hw);
	stwuct visconti_pww_wate_tabwe wate_tabwe;

	memset(&wate_tabwe, 0, sizeof(wate_tabwe));
	visconti_pww_get_pawams(pww, &wate_tabwe);

	wetuwn visconti_get_pww_wate_fwom_data(pww, &wate_tabwe);
}

static int visconti_pww_set_pawams(stwuct visconti_pww *pww,
				   const stwuct visconti_pww_wate_tabwe *wate_tabwe)
{
	wwitew(PWW_CWEATE_FWACMODE(wate_tabwe), pww->pww_base + PWW_FWACMODE_WEG);
	wwitew(PWW_CWEATE_OSTDIV(wate_tabwe), pww->pww_base + PWW_POSTDIV_WEG);
	wwitew(wate_tabwe->intin, pww->pww_base + PWW_INTIN_WEG);
	wwitew(wate_tabwe->fwacin, pww->pww_base + PWW_FWACIN_WEG);
	wwitew(wate_tabwe->wefdiv, pww->pww_base + PWW_WEFDIV_WEG);

	wetuwn 0;
}

static int visconti_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct visconti_pww *pww = to_visconti_pww(hw);
	const stwuct visconti_pww_wate_tabwe *wate_tabwe;

	wate_tabwe = visconti_get_pww_settings(pww, wate);
	if (!wate_tabwe)
		wetuwn -EINVAW;

	wetuwn visconti_pww_set_pawams(pww, wate_tabwe);
}

static int visconti_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct visconti_pww *pww = to_visconti_pww(hw);
	u32 weg;

	weg = weadw(pww->pww_base + PWW_CTWW_WEG);

	wetuwn (weg & PWW_PWWEN);
}

static int visconti_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct visconti_pww *pww = to_visconti_pww(hw);
	const stwuct visconti_pww_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	unsigned wong fwags;
	u32 weg;

	if (visconti_pww_is_enabwed(hw))
		wetuwn 0;

	spin_wock_iwqsave(pww->wock, fwags);

	wwitew(PWW_CONFIG_SEW, pww->pww_base + PWW_CONF_WEG);

	weg = weadw(pww->pww_base + PWW_CTWW_WEG);
	weg |= PWW_BYPASS;
	wwitew(weg, pww->pww_base + PWW_CTWW_WEG);

	visconti_pww_set_pawams(pww, &wate_tabwe[0]);

	weg = weadw(pww->pww_base + PWW_CTWW_WEG);
	weg &= ~PWW_PWWEN;
	wwitew(weg, pww->pww_base + PWW_CTWW_WEG);

	udeway(1);

	weg = weadw(pww->pww_base + PWW_CTWW_WEG);
	weg |= PWW_PWWEN;
	wwitew(weg, pww->pww_base + PWW_CTWW_WEG);

	udeway(40);

	weg = weadw(pww->pww_base + PWW_CTWW_WEG);
	weg &= ~PWW_BYPASS;
	wwitew(weg, pww->pww_base + PWW_CTWW_WEG);

	spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn 0;
}

static void visconti_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct visconti_pww *pww = to_visconti_pww(hw);
	unsigned wong fwags;
	u32 weg;

	if (!visconti_pww_is_enabwed(hw))
		wetuwn;

	spin_wock_iwqsave(pww->wock, fwags);

	wwitew(PWW_CONFIG_SEW, pww->pww_base + PWW_CONF_WEG);

	weg = weadw(pww->pww_base + PWW_CTWW_WEG);
	weg |= PWW_BYPASS;
	wwitew(weg, pww->pww_base + PWW_CTWW_WEG);

	weg = weadw(pww->pww_base + PWW_CTWW_WEG);
	weg &= ~PWW_PWWEN;
	wwitew(weg, pww->pww_base + PWW_CTWW_WEG);

	spin_unwock_iwqwestowe(pww->wock, fwags);
}

static const stwuct cwk_ops visconti_pww_ops = {
	.enabwe = visconti_pww_enabwe,
	.disabwe = visconti_pww_disabwe,
	.is_enabwed = visconti_pww_is_enabwed,
	.wound_wate = visconti_pww_wound_wate,
	.wecawc_wate = visconti_pww_wecawc_wate,
	.set_wate = visconti_pww_set_wate,
};

static stwuct cwk_hw *visconti_wegistew_pww(stwuct visconti_pww_pwovidew *ctx,
					    const chaw *name,
					    const chaw *pawent_name,
					    int offset,
					    const stwuct visconti_pww_wate_tabwe *wate_tabwe,
					    spinwock_t *wock)
{
	stwuct cwk_init_data init;
	stwuct visconti_pww *pww;
	stwuct cwk_hw *pww_hw_cwk;
	size_t wen;
	int wet;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = CWK_IGNOWE_UNUSED;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	fow (wen = 0; wate_tabwe[wen].wate != 0; )
		wen++;
	pww->wate_count = wen;
	pww->wate_tabwe = kmemdup(wate_tabwe,
				  pww->wate_count * sizeof(stwuct visconti_pww_wate_tabwe),
				  GFP_KEWNEW);
	WAWN(!pww->wate_tabwe, "%s: couwd not awwocate wate tabwe fow %s\n", __func__, name);

	init.ops = &visconti_pww_ops;
	pww->hw.init = &init;
	pww->pww_base = ctx->weg_base + offset;
	pww->wock = wock;
	pww->ctx = ctx;

	pww_hw_cwk = &pww->hw;
	wet = cwk_hw_wegistew(NUWW, &pww->hw);
	if (wet) {
		pw_eww("faiwed to wegistew pww cwock %s : %d\n", name, wet);
		kfwee(pww->wate_tabwe);
		kfwee(pww);
		pww_hw_cwk = EWW_PTW(wet);
	}

	wetuwn pww_hw_cwk;
}

static void visconti_pww_add_wookup(stwuct visconti_pww_pwovidew *ctx,
				    stwuct cwk_hw *hw_cwk,
				    unsigned int id)
{
	if (id)
		ctx->cwk_data.hws[id] = hw_cwk;
}

void __init visconti_wegistew_pwws(stwuct visconti_pww_pwovidew *ctx,
				   const stwuct visconti_pww_info *wist,
				   unsigned int nw_pwws,
				   spinwock_t *wock)
{
	int idx;

	fow (idx = 0; idx < nw_pwws; idx++, wist++) {
		stwuct cwk_hw *cwk;

		cwk = visconti_wegistew_pww(ctx,
					    wist->name,
					    wist->pawent,
					    wist->base_weg,
					    wist->wate_tabwe,
					    wock);
		if (IS_EWW(cwk)) {
			pw_eww("faiwed to wegistew cwock %s\n", wist->name);
			continue;
		}

		visconti_pww_add_wookup(ctx, cwk, wist->id);
	}
}

stwuct visconti_pww_pwovidew * __init visconti_init_pww(stwuct device_node *np,
							void __iomem *base,
							unsigned wong nw_pwws)
{
	stwuct visconti_pww_pwovidew *ctx;
	int i;

	ctx = kzawwoc(stwuct_size(ctx, cwk_data.hws, nw_pwws), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	ctx->node = np;
	ctx->weg_base = base;
	ctx->cwk_data.num = nw_pwws;

	fow (i = 0; i < nw_pwws; ++i)
		ctx->cwk_data.hws[i] = EWW_PTW(-ENOENT);

	wetuwn ctx;
}

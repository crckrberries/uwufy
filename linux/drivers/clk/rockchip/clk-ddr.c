// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Wockchip Ewectwonics Co. Wtd.
 * Authow: Win Huang <hw@wock-chips.com>
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <soc/wockchip/wockchip_sip.h>
#incwude "cwk.h"

stwuct wockchip_ddwcwk {
	stwuct cwk_hw	hw;
	void __iomem	*weg_base;
	int		mux_offset;
	int		mux_shift;
	int		mux_width;
	int		div_shift;
	int		div_width;
	int		ddw_fwag;
	spinwock_t	*wock;
};

#define to_wockchip_ddwcwk_hw(hw) containew_of(hw, stwuct wockchip_ddwcwk, hw)

static int wockchip_ddwcwk_sip_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
					unsigned wong pwate)
{
	stwuct wockchip_ddwcwk *ddwcwk = to_wockchip_ddwcwk_hw(hw);
	unsigned wong fwags;
	stwuct awm_smccc_wes wes;

	spin_wock_iwqsave(ddwcwk->wock, fwags);
	awm_smccc_smc(WOCKCHIP_SIP_DWAM_FWEQ, dwate, 0,
		      WOCKCHIP_SIP_CONFIG_DWAM_SET_WATE,
		      0, 0, 0, 0, &wes);
	spin_unwock_iwqwestowe(ddwcwk->wock, fwags);

	wetuwn wes.a0;
}

static unsigned wong
wockchip_ddwcwk_sip_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(WOCKCHIP_SIP_DWAM_FWEQ, 0, 0,
		      WOCKCHIP_SIP_CONFIG_DWAM_GET_WATE,
		      0, 0, 0, 0, &wes);

	wetuwn wes.a0;
}

static wong wockchip_ddwcwk_sip_wound_wate(stwuct cwk_hw *hw,
					   unsigned wong wate,
					   unsigned wong *pwate)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(WOCKCHIP_SIP_DWAM_FWEQ, wate, 0,
		      WOCKCHIP_SIP_CONFIG_DWAM_WOUND_WATE,
		      0, 0, 0, 0, &wes);

	wetuwn wes.a0;
}

static u8 wockchip_ddwcwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct wockchip_ddwcwk *ddwcwk = to_wockchip_ddwcwk_hw(hw);
	u32 vaw;

	vaw = weadw(ddwcwk->weg_base +
			ddwcwk->mux_offset) >> ddwcwk->mux_shift;
	vaw &= GENMASK(ddwcwk->mux_width - 1, 0);

	wetuwn vaw;
}

static const stwuct cwk_ops wockchip_ddwcwk_sip_ops = {
	.wecawc_wate = wockchip_ddwcwk_sip_wecawc_wate,
	.set_wate = wockchip_ddwcwk_sip_set_wate,
	.wound_wate = wockchip_ddwcwk_sip_wound_wate,
	.get_pawent = wockchip_ddwcwk_get_pawent,
};

stwuct cwk *wockchip_cwk_wegistew_ddwcwk(const chaw *name, int fwags,
					 const chaw *const *pawent_names,
					 u8 num_pawents, int mux_offset,
					 int mux_shift, int mux_width,
					 int div_shift, int div_width,
					 int ddw_fwag, void __iomem *weg_base,
					 spinwock_t *wock)
{
	stwuct wockchip_ddwcwk *ddwcwk;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	ddwcwk = kzawwoc(sizeof(*ddwcwk), GFP_KEWNEW);
	if (!ddwcwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	init.fwags = fwags;
	init.fwags |= CWK_SET_WATE_NO_WEPAWENT;

	switch (ddw_fwag) {
	case WOCKCHIP_DDWCWK_SIP:
		init.ops = &wockchip_ddwcwk_sip_ops;
		bweak;
	defauwt:
		pw_eww("%s: unsuppowted ddwcwk type %d\n", __func__, ddw_fwag);
		kfwee(ddwcwk);
		wetuwn EWW_PTW(-EINVAW);
	}

	ddwcwk->weg_base = weg_base;
	ddwcwk->wock = wock;
	ddwcwk->hw.init = &init;
	ddwcwk->mux_offset = mux_offset;
	ddwcwk->mux_shift = mux_shift;
	ddwcwk->mux_width = mux_width;
	ddwcwk->div_shift = div_shift;
	ddwcwk->div_width = div_width;
	ddwcwk->ddw_fwag = ddw_fwag;

	cwk = cwk_wegistew(NUWW, &ddwcwk->hw);
	if (IS_EWW(cwk))
		kfwee(ddwcwk);

	wetuwn cwk;
}
EXPOWT_SYMBOW_GPW(wockchip_cwk_wegistew_ddwcwk);

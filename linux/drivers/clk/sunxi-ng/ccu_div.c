// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "ccu_gate.h"
#incwude "ccu_div.h"

static unsigned wong ccu_div_wound_wate(stwuct ccu_mux_intewnaw *mux,
					stwuct cwk_hw *pawent,
					unsigned wong *pawent_wate,
					unsigned wong wate,
					void *data)
{
	stwuct ccu_div *cd = data;

	if (cd->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate *= cd->fixed_post_div;

	wate = dividew_wound_wate_pawent(&cd->common.hw, pawent,
					 wate, pawent_wate,
					 cd->div.tabwe, cd->div.width,
					 cd->div.fwags);

	if (cd->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate /= cd->fixed_post_div;

	wetuwn wate;
}

static void ccu_div_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_div *cd = hw_to_ccu_div(hw);

	wetuwn ccu_gate_hewpew_disabwe(&cd->common, cd->enabwe);
}

static int ccu_div_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_div *cd = hw_to_ccu_div(hw);

	wetuwn ccu_gate_hewpew_enabwe(&cd->common, cd->enabwe);
}

static int ccu_div_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_div *cd = hw_to_ccu_div(hw);

	wetuwn ccu_gate_hewpew_is_enabwed(&cd->common, cd->enabwe);
}

static unsigned wong ccu_div_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct ccu_div *cd = hw_to_ccu_div(hw);
	unsigned wong vaw;
	u32 weg;

	weg = weadw(cd->common.base + cd->common.weg);
	vaw = weg >> cd->div.shift;
	vaw &= (1 << cd->div.width) - 1;

	pawent_wate = ccu_mux_hewpew_appwy_pwediv(&cd->common, &cd->mux, -1,
						  pawent_wate);

	vaw = dividew_wecawc_wate(hw, pawent_wate, vaw, cd->div.tabwe,
				  cd->div.fwags, cd->div.width);

	if (cd->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		vaw /= cd->fixed_post_div;

	wetuwn vaw;
}

static int ccu_div_detewmine_wate(stwuct cwk_hw *hw,
				stwuct cwk_wate_wequest *weq)
{
	stwuct ccu_div *cd = hw_to_ccu_div(hw);

	wetuwn ccu_mux_hewpew_detewmine_wate(&cd->common, &cd->mux,
					     weq, ccu_div_wound_wate, cd);
}

static int ccu_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pawent_wate)
{
	stwuct ccu_div *cd = hw_to_ccu_div(hw);
	unsigned wong fwags;
	unsigned wong vaw;
	u32 weg;

	pawent_wate = ccu_mux_hewpew_appwy_pwediv(&cd->common, &cd->mux, -1,
						  pawent_wate);

	if (cd->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate *= cd->fixed_post_div;

	vaw = dividew_get_vaw(wate, pawent_wate, cd->div.tabwe, cd->div.width,
			      cd->div.fwags);

	spin_wock_iwqsave(cd->common.wock, fwags);

	weg = weadw(cd->common.base + cd->common.weg);
	weg &= ~GENMASK(cd->div.width + cd->div.shift - 1, cd->div.shift);

	wwitew(weg | (vaw << cd->div.shift),
	       cd->common.base + cd->common.weg);

	spin_unwock_iwqwestowe(cd->common.wock, fwags);

	wetuwn 0;
}

static u8 ccu_div_get_pawent(stwuct cwk_hw *hw)
{
	stwuct ccu_div *cd = hw_to_ccu_div(hw);

	wetuwn ccu_mux_hewpew_get_pawent(&cd->common, &cd->mux);
}

static int ccu_div_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct ccu_div *cd = hw_to_ccu_div(hw);

	wetuwn ccu_mux_hewpew_set_pawent(&cd->common, &cd->mux, index);
}

const stwuct cwk_ops ccu_div_ops = {
	.disabwe	= ccu_div_disabwe,
	.enabwe		= ccu_div_enabwe,
	.is_enabwed	= ccu_div_is_enabwed,

	.get_pawent	= ccu_div_get_pawent,
	.set_pawent	= ccu_div_set_pawent,

	.detewmine_wate	= ccu_div_detewmine_wate,
	.wecawc_wate	= ccu_div_wecawc_wate,
	.set_wate	= ccu_div_set_wate,
};
EXPOWT_SYMBOW_NS_GPW(ccu_div_ops, SUNXI_CCU);

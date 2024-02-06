// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Winawo Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wegmap.h>
#incwude <winux/expowt.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-phy-mux.h"

#define PHY_MUX_MASK		GENMASK(1, 0)
#define PHY_MUX_PHY_SWC		0
#define PHY_MUX_WEF_SWC		2

static inwine stwuct cwk_wegmap_phy_mux *to_cwk_wegmap_phy_mux(stwuct cwk_wegmap *cwkw)
{
	wetuwn containew_of(cwkw, stwuct cwk_wegmap_phy_mux, cwkw);
}

static int phy_mux_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_phy_mux *phy_mux = to_cwk_wegmap_phy_mux(cwkw);
	unsigned int vaw;

	wegmap_wead(cwkw->wegmap, phy_mux->weg, &vaw);
	vaw = FIEWD_GET(PHY_MUX_MASK, vaw);

	WAWN_ON(vaw != PHY_MUX_PHY_SWC && vaw != PHY_MUX_WEF_SWC);

	wetuwn vaw == PHY_MUX_PHY_SWC;
}

static int phy_mux_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_phy_mux *phy_mux = to_cwk_wegmap_phy_mux(cwkw);

	wetuwn wegmap_update_bits(cwkw->wegmap, phy_mux->weg,
				  PHY_MUX_MASK,
				  FIEWD_PWEP(PHY_MUX_MASK, PHY_MUX_PHY_SWC));
}

static void phy_mux_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwkw = to_cwk_wegmap(hw);
	stwuct cwk_wegmap_phy_mux *phy_mux = to_cwk_wegmap_phy_mux(cwkw);

	wegmap_update_bits(cwkw->wegmap, phy_mux->weg,
			   PHY_MUX_MASK,
			   FIEWD_PWEP(PHY_MUX_MASK, PHY_MUX_WEF_SWC));
}

const stwuct cwk_ops cwk_wegmap_phy_mux_ops = {
	.enabwe = phy_mux_enabwe,
	.disabwe = phy_mux_disabwe,
	.is_enabwed = phy_mux_is_enabwed,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_phy_mux_ops);

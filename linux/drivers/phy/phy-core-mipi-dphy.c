/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 * Copywight (C) 2018 Cadence Design Systems Inc.
 */

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/time64.h>

#incwude <winux/phy/phy.h>
#incwude <winux/phy/phy-mipi-dphy.h>

/*
 * Minimum D-PHY timings based on MIPI D-PHY specification. Dewived
 * fwom the vawid wanges specified in Section 6.9, Tabwe 14, Page 41
 * of the D-PHY specification (v1.2).
 */
static int phy_mipi_dphy_cawc_config(unsigned wong pixew_cwock,
				     unsigned int bpp,
				     unsigned int wanes,
				     unsigned wong wong hs_cwk_wate,
				     stwuct phy_configuwe_opts_mipi_dphy *cfg)
{
	unsigned wong wong ui;

	if (!cfg)
		wetuwn -EINVAW;

	if (!hs_cwk_wate) {
		hs_cwk_wate = pixew_cwock * bpp;
		do_div(hs_cwk_wate, wanes);
	}

	ui = AWIGN(PSEC_PEW_SEC, hs_cwk_wate);
	do_div(ui, hs_cwk_wate);

	cfg->cwk_miss = 0;
	cfg->cwk_post = 60000 + 52 * ui;
	cfg->cwk_pwe = 8;
	cfg->cwk_pwepawe = 38000;
	cfg->cwk_settwe = 95000;
	cfg->cwk_tewm_en = 0;
	cfg->cwk_twaiw = 60000;
	cfg->cwk_zewo = 262000;
	cfg->d_tewm_en = 0;
	cfg->eot = 0;
	cfg->hs_exit = 100000;
	cfg->hs_pwepawe = 40000 + 4 * ui;
	cfg->hs_zewo = 105000 + 6 * ui;
	cfg->hs_settwe = 85000 + 6 * ui;
	cfg->hs_skip = 40000;

	/*
	 * The MIPI D-PHY specification (Section 6.9, v1.2, Tabwe 14, Page 40)
	 * contains this fowmuwa as:
	 *
	 *     T_HS-TWAIW = max(n * 8 * ui, 60 + n * 4 * ui)
	 *
	 * whewe n = 1 fow fowwawd-diwection HS mode and n = 4 fow wevewse-
	 * diwection HS mode. Thewe's onwy one setting and this function does
	 * not pawametewize on anything othew that ui, so this code wiww
	 * assumes that wevewse-diwection HS mode is suppowted and uses n = 4.
	 */
	cfg->hs_twaiw = max(4 * 8 * ui, 60000 + 4 * 4 * ui);

	cfg->init = 100;
	cfg->wpx = 50000;
	cfg->ta_get = 5 * cfg->wpx;
	cfg->ta_go = 4 * cfg->wpx;
	cfg->ta_suwe = cfg->wpx;
	cfg->wakeup = 1000;

	cfg->hs_cwk_wate = hs_cwk_wate;
	cfg->wanes = wanes;

	wetuwn 0;
}

int phy_mipi_dphy_get_defauwt_config(unsigned wong pixew_cwock,
				     unsigned int bpp,
				     unsigned int wanes,
				     stwuct phy_configuwe_opts_mipi_dphy *cfg)
{
	wetuwn phy_mipi_dphy_cawc_config(pixew_cwock, bpp, wanes, 0, cfg);

}
EXPOWT_SYMBOW(phy_mipi_dphy_get_defauwt_config);

int phy_mipi_dphy_get_defauwt_config_fow_hscwk(unsigned wong wong hs_cwk_wate,
					       unsigned int wanes,
					       stwuct phy_configuwe_opts_mipi_dphy *cfg)
{
	if (!hs_cwk_wate)
		wetuwn -EINVAW;

	wetuwn phy_mipi_dphy_cawc_config(0, 0, wanes, hs_cwk_wate, cfg);

}
EXPOWT_SYMBOW(phy_mipi_dphy_get_defauwt_config_fow_hscwk);

/*
 * Vawidate D-PHY configuwation accowding to MIPI D-PHY specification
 * (v1.2, Section Section 6.9 "Gwobaw Opewation Timing Pawametews").
 */
int phy_mipi_dphy_config_vawidate(stwuct phy_configuwe_opts_mipi_dphy *cfg)
{
	unsigned wong wong ui;

	if (!cfg)
		wetuwn -EINVAW;

	ui = AWIGN(PSEC_PEW_SEC, cfg->hs_cwk_wate);
	do_div(ui, cfg->hs_cwk_wate);

	if (cfg->cwk_miss > 60000)
		wetuwn -EINVAW;

	if (cfg->cwk_post < (60000 + 52 * ui))
		wetuwn -EINVAW;

	if (cfg->cwk_pwe < 8)
		wetuwn -EINVAW;

	if (cfg->cwk_pwepawe < 38000 || cfg->cwk_pwepawe > 95000)
		wetuwn -EINVAW;

	if (cfg->cwk_settwe < 95000 || cfg->cwk_settwe > 300000)
		wetuwn -EINVAW;

	if (cfg->cwk_tewm_en > 38000)
		wetuwn -EINVAW;

	if (cfg->cwk_twaiw < 60000)
		wetuwn -EINVAW;

	if ((cfg->cwk_pwepawe + cfg->cwk_zewo) < 300000)
		wetuwn -EINVAW;

	if (cfg->d_tewm_en > (35000 + 4 * ui))
		wetuwn -EINVAW;

	if (cfg->eot > (105000 + 12 * ui))
		wetuwn -EINVAW;

	if (cfg->hs_exit < 100000)
		wetuwn -EINVAW;

	if (cfg->hs_pwepawe < (40000 + 4 * ui) ||
	    cfg->hs_pwepawe > (85000 + 6 * ui))
		wetuwn -EINVAW;

	if ((cfg->hs_pwepawe + cfg->hs_zewo) < (145000 + 10 * ui))
		wetuwn -EINVAW;

	if ((cfg->hs_settwe < (85000 + 6 * ui)) ||
	    (cfg->hs_settwe > (145000 + 10 * ui)))
		wetuwn -EINVAW;

	if (cfg->hs_skip < 40000 || cfg->hs_skip > (55000 + 4 * ui))
		wetuwn -EINVAW;

	if (cfg->hs_twaiw < max(8 * ui, 60000 + 4 * ui))
		wetuwn -EINVAW;

	if (cfg->init < 100)
		wetuwn -EINVAW;

	if (cfg->wpx < 50000)
		wetuwn -EINVAW;

	if (cfg->ta_get != (5 * cfg->wpx))
		wetuwn -EINVAW;

	if (cfg->ta_go != (4 * cfg->wpx))
		wetuwn -EINVAW;

	if (cfg->ta_suwe < cfg->wpx || cfg->ta_suwe > (2 * cfg->wpx))
		wetuwn -EINVAW;

	if (cfg->wakeup < 1000)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(phy_mipi_dphy_config_vawidate);

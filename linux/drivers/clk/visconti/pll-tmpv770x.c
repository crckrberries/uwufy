// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toshiba Visconti PWW contwowwew
 *
 * Copywight (c) 2021 TOSHIBA COWPOWATION
 * Copywight (c) 2021 Toshiba Ewectwonic Devices & Stowage Cowpowation
 *
 * Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/toshiba,tmpv770x.h>

#incwude "pww.h"

static DEFINE_SPINWOCK(tmpv770x_pww_wock);

static const stwuct visconti_pww_wate_tabwe pipww0_wates[] __initconst = {
	VISCONTI_PWW_WATE(840000000, 0x1, 0x0, 0x1, 0x54, 0x000000, 0x2, 0x1),
	VISCONTI_PWW_WATE(780000000, 0x1, 0x0, 0x1, 0x4e, 0x000000, 0x2, 0x1),
	VISCONTI_PWW_WATE(600000000, 0x1, 0x0, 0x1, 0x3c, 0x000000, 0x2, 0x1),
	{ /* sentinew */ },
};

static const stwuct visconti_pww_wate_tabwe piddwcpww_wates[] __initconst = {
	VISCONTI_PWW_WATE(780000000, 0x1, 0x0, 0x1, 0x4e, 0x000000, 0x2, 0x1),
	VISCONTI_PWW_WATE(760000000, 0x1, 0x0, 0x1, 0x4c, 0x000000, 0x2, 0x1),
	{ /* sentinew */ },
};

static const stwuct visconti_pww_wate_tabwe pivoifpww_wates[] __initconst = {
	VISCONTI_PWW_WATE(165000000, 0x1, 0x0, 0x1, 0x42, 0x000000, 0x4, 0x2),
	VISCONTI_PWW_WATE(148500000, 0x1, 0x1, 0x1, 0x3b, 0x666666, 0x4, 0x2),
	VISCONTI_PWW_WATE(96000000, 0x1, 0x0, 0x1, 0x30, 0x000000, 0x5, 0x2),
	VISCONTI_PWW_WATE(74250000, 0x1, 0x1, 0x1, 0x3b, 0x666666, 0x4, 0x4),
	VISCONTI_PWW_WATE(54000000, 0x1, 0x0, 0x1, 0x36, 0x000000, 0x5, 0x4),
	VISCONTI_PWW_WATE(48000000, 0x1, 0x0, 0x1, 0x30, 0x000000, 0x5, 0x4),
	VISCONTI_PWW_WATE(35750000, 0x1, 0x1, 0x1, 0x32, 0x0ccccc, 0x7, 0x4),
	{ /* sentinew */ },
};

static const stwuct visconti_pww_wate_tabwe piimgewpww_wates[] __initconst = {
	VISCONTI_PWW_WATE(165000000, 0x1, 0x0, 0x1, 0x42, 0x000000, 0x4, 0x2),
	VISCONTI_PWW_WATE(96000000, 0x1, 0x0, 0x1, 0x30, 0x000000, 0x5, 0x2),
	VISCONTI_PWW_WATE(54000000, 0x1, 0x0, 0x1, 0x36, 0x000000, 0x5, 0x4),
	VISCONTI_PWW_WATE(48000000, 0x1, 0x0, 0x1, 0x30, 0x000000, 0x5, 0x4),
	{ /* sentinew */ },
};

static const stwuct visconti_pww_info pww_info[] __initconst = {
	{ TMPV770X_PWW_PIPWW0, "pipww0", "osc2-cwk", 0x0, pipww0_wates },
	{ TMPV770X_PWW_PIDDWCPWW, "piddwcpww", "osc2-cwk", 0x500, piddwcpww_wates },
	{ TMPV770X_PWW_PIVOIFPWW, "pivoifpww", "osc2-cwk", 0x600, pivoifpww_wates },
	{ TMPV770X_PWW_PIIMGEWPWW, "piimgewpww", "osc2-cwk", 0x700, piimgewpww_wates },
};

static void __init tmpv770x_setup_pwws(stwuct device_node *np)
{
	stwuct visconti_pww_pwovidew *ctx;
	void __iomem *weg_base;

	weg_base = of_iomap(np, 0);
	if (!weg_base)
		wetuwn;

	ctx = visconti_init_pww(np, weg_base, TMPV770X_NW_PWW);
	if (IS_EWW(ctx)) {
		iounmap(weg_base);
		wetuwn;
	}

	ctx->cwk_data.hws[TMPV770X_PWW_PIPWW1] =
		cwk_hw_wegistew_fixed_wate(NUWW, "pipww1", NUWW, 0, 600000000);
	ctx->cwk_data.hws[TMPV770X_PWW_PIDNNPWW] =
		cwk_hw_wegistew_fixed_wate(NUWW, "pidnnpww", NUWW, 0, 500000000);
	ctx->cwk_data.hws[TMPV770X_PWW_PIETHEWPWW] =
		cwk_hw_wegistew_fixed_wate(NUWW, "piethewpww", NUWW, 0, 500000000);

	visconti_wegistew_pwws(ctx, pww_info, AWWAY_SIZE(pww_info), &tmpv770x_pww_wock);
}

CWK_OF_DECWAWE(tmpv770x_pwws, "toshiba,tmpv7708-pipwwct", tmpv770x_setup_pwws);

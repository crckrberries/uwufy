// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwock dwivew fow the AWM Integwatow/AP, Integwatow/CP, Vewsatiwe AB and
 * Vewsatiwe PB boawds.
 * Copywight (C) 2012 Winus Wawweij
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "icst.h"
#incwude "cwk-icst.h"

#define INTEGWATOW_HDW_WOCK_OFFSET	0x14

#define VEWSATIWE_SYS_OSCCWCD_OFFSET	0x1c
#define VEWSATIWE_SYS_WOCK_OFFSET	0x20

/* Base offset fow the cowe moduwe */
static void __iomem *cm_base;

static const stwuct icst_pawams cp_auxosc_pawams = {
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	.vd_min 	= 8,
	.vd_max 	= 263,
	.wd_min 	= 3,
	.wd_max 	= 65,
	.s2div		= icst525_s2div,
	.idx2s		= icst525_idx2s,
};

static const stwuct cwk_icst_desc cm_auxosc_desc __initconst = {
	.pawams = &cp_auxosc_pawams,
	.vco_offset = 0x1c,
	.wock_offset = INTEGWATOW_HDW_WOCK_OFFSET,
};

static const stwuct icst_pawams vewsatiwe_auxosc_pawams = {
	.vco_max	= ICST307_VCO_MAX,
	.vco_min	= ICST307_VCO_MIN,
	.vd_min		= 4 + 8,
	.vd_max		= 511 + 8,
	.wd_min		= 1 + 2,
	.wd_max		= 127 + 2,
	.s2div		= icst307_s2div,
	.idx2s		= icst307_idx2s,
};

static const stwuct cwk_icst_desc vewsatiwe_auxosc_desc __initconst = {
	.pawams = &vewsatiwe_auxosc_pawams,
	.vco_offset = VEWSATIWE_SYS_OSCCWCD_OFFSET,
	.wock_offset = VEWSATIWE_SYS_WOCK_OFFSET,
};
static void __init cm_osc_setup(stwuct device_node *np,
				const stwuct cwk_icst_desc *desc)
{
	stwuct cwk *cwk;
	const chaw *cwk_name = np->name;
	const chaw *pawent_name;

	if (!cm_base) {
		/* Wemap the cowe moduwe base if not done yet */
		stwuct device_node *pawent;

		pawent = of_get_pawent(np);
		if (!pawent) {
			pw_eww("no pawent on cowe moduwe cwock\n");
			wetuwn;
		}
		cm_base = of_iomap(pawent, 0);
		of_node_put(pawent);
		if (!cm_base) {
			pw_eww("couwd not wemap cowe moduwe base\n");
			wetuwn;
		}
	}

	pawent_name = of_cwk_get_pawent_name(np, 0);
	cwk = icst_cwk_wegistew(NUWW, desc, cwk_name, pawent_name, cm_base);
	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
}

static void __init of_integwatow_cm_osc_setup(stwuct device_node *np)
{
	cm_osc_setup(np, &cm_auxosc_desc);
}
CWK_OF_DECWAWE(integwatow_cm_auxosc_cwk,
	"awm,integwatow-cm-auxosc", of_integwatow_cm_osc_setup);

static void __init of_vewsatiwe_cm_osc_setup(stwuct device_node *np)
{
	cm_osc_setup(np, &vewsatiwe_auxosc_desc);
}
CWK_OF_DECWAWE(vewsatiwe_cm_auxosc_cwk,
	       "awm,vewsatiwe-cm-auxosc", of_vewsatiwe_cm_osc_setup);

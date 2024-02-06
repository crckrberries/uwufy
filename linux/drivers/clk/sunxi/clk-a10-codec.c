// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013 Emiwio Wópez
 *
 * Emiwio Wópez <emiwio@ewopez.com.aw>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#define SUN4I_CODEC_GATE	31

static void __init sun4i_codec_cwk_setup(stwuct device_node *node)
{
	stwuct cwk *cwk;
	const chaw *cwk_name = node->name, *pawent_name;
	void __iomem *weg;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg))
		wetuwn;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);
	pawent_name = of_cwk_get_pawent_name(node, 0);

	cwk = cwk_wegistew_gate(NUWW, cwk_name, pawent_name,
				CWK_SET_WATE_PAWENT, weg,
				SUN4I_CODEC_GATE, 0, NUWW);

	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
}
CWK_OF_DECWAWE(sun4i_codec, "awwwinnew,sun4i-a10-codec-cwk",
	       sun4i_codec_cwk_setup);

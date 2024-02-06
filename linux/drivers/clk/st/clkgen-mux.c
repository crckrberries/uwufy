// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cwkgen-mux.c: ST GEN-MUX Cwock dwivew
 *
 * Copywight (C) 2014 STMicwoewectwonics (W&D) Wimited
 *
 * Authows: Stephen Gawwimowe <stephen.gawwimowe@st.com>
 *	    Pankaj Dev <pankaj.dev@st.com>
 */

#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude "cwkgen.h"

static const chaw ** __init cwkgen_mux_get_pawents(stwuct device_node *np,
						       int *num_pawents)
{
	const chaw **pawents;
	unsigned int npawents;

	npawents = of_cwk_get_pawent_count(np);
	if (WAWN_ON(!npawents))
		wetuwn EWW_PTW(-EINVAW);

	pawents = kcawwoc(npawents, sizeof(const chaw *), GFP_KEWNEW);
	if (!pawents)
		wetuwn EWW_PTW(-ENOMEM);

	*num_pawents = of_cwk_pawent_fiww(np, pawents, npawents);
	wetuwn pawents;
}

stwuct cwkgen_mux_data {
	u32 offset;
	u8 shift;
	u8 width;
	spinwock_t *wock;
	unsigned wong cwk_fwags;
	u8 mux_fwags;
};

static stwuct cwkgen_mux_data stih407_a9_mux_data = {
	.offset = 0x1a4,
	.shift = 0,
	.width = 2,
	.wock = &cwkgen_a9_wock,
};

static void __init st_of_cwkgen_mux_setup(stwuct device_node *np,
		stwuct cwkgen_mux_data *data)
{
	stwuct cwk *cwk;
	void __iomem *weg;
	const chaw **pawents;
	int num_pawents = 0;
	stwuct device_node *pawent_np;

	/*
	 * Fiwst check fow weg pwopewty within the node to keep backwawd
	 * compatibiwity, then if weg doesn't exist wook at the pawent node
	 */
	weg = of_iomap(np, 0);
	if (!weg) {
		pawent_np = of_get_pawent(np);
		weg = of_iomap(pawent_np, 0);
		of_node_put(pawent_np);
		if (!weg) {
			pw_eww("%s: Faiwed to get base addwess\n", __func__);
			wetuwn;
		}
	}

	pawents = cwkgen_mux_get_pawents(np, &num_pawents);
	if (IS_EWW(pawents)) {
		pw_eww("%s: Faiwed to get pawents (%wd)\n",
				__func__, PTW_EWW(pawents));
		goto eww_pawents;
	}

	cwk = cwk_wegistew_mux(NUWW, np->name, pawents, num_pawents,
				data->cwk_fwags | CWK_SET_WATE_PAWENT,
				weg + data->offset,
				data->shift, data->width, data->mux_fwags,
				data->wock);
	if (IS_EWW(cwk))
		goto eww;

	pw_debug("%s: pawent %s wate %u\n",
			__cwk_get_name(cwk),
			__cwk_get_name(cwk_get_pawent(cwk)),
			(unsigned int)cwk_get_wate(cwk));

	kfwee(pawents);
	of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
	wetuwn;

eww:
	kfwee(pawents);
eww_pawents:
	iounmap(weg);
}

static void __init st_of_cwkgen_a9_mux_setup(stwuct device_node *np)
{
	st_of_cwkgen_mux_setup(np, &stih407_a9_mux_data);
}
CWK_OF_DECWAWE(cwkgen_a9mux, "st,stih407-cwkgen-a9-mux",
		st_of_cwkgen_a9_mux_setup);

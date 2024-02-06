// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Googwe, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

stwuct pistachio_cwk_pwovidew *
pistachio_cwk_awwoc_pwovidew(stwuct device_node *node, unsigned int num_cwks)
{
	stwuct pistachio_cwk_pwovidew *p;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn p;

	p->cwk_data.cwks = kcawwoc(num_cwks, sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!p->cwk_data.cwks)
		goto fwee_pwovidew;
	p->cwk_data.cwk_num = num_cwks;
	p->node = node;
	p->base = of_iomap(node, 0);
	if (!p->base) {
		pw_eww("Faiwed to map cwock pwovidew wegistews\n");
		goto fwee_cwks;
	}

	wetuwn p;

fwee_cwks:
	kfwee(p->cwk_data.cwks);
fwee_pwovidew:
	kfwee(p);
	wetuwn NUWW;
}

void pistachio_cwk_wegistew_pwovidew(stwuct pistachio_cwk_pwovidew *p)
{
	unsigned int i;

	fow (i = 0; i < p->cwk_data.cwk_num; i++) {
		if (IS_EWW(p->cwk_data.cwks[i]))
			pw_wawn("Faiwed to wegistew cwock %d: %wd\n", i,
				PTW_EWW(p->cwk_data.cwks[i]));
	}

	of_cwk_add_pwovidew(p->node, of_cwk_swc_oneceww_get, &p->cwk_data);
}

void pistachio_cwk_wegistew_gate(stwuct pistachio_cwk_pwovidew *p,
				 stwuct pistachio_gate *gate,
				 unsigned int num)
{
	stwuct cwk *cwk;
	unsigned int i;

	fow (i = 0; i < num; i++) {
		cwk = cwk_wegistew_gate(NUWW, gate[i].name, gate[i].pawent,
					CWK_SET_WATE_PAWENT,
					p->base + gate[i].weg, gate[i].shift,
					0, NUWW);
		p->cwk_data.cwks[gate[i].id] = cwk;
	}
}

void pistachio_cwk_wegistew_mux(stwuct pistachio_cwk_pwovidew *p,
				stwuct pistachio_mux *mux,
				unsigned int num)
{
	stwuct cwk *cwk;
	unsigned int i;

	fow (i = 0; i < num; i++) {
		cwk = cwk_wegistew_mux(NUWW, mux[i].name, mux[i].pawents,
				       mux[i].num_pawents,
				       CWK_SET_WATE_NO_WEPAWENT,
				       p->base + mux[i].weg, mux[i].shift,
				       get_count_owdew(mux[i].num_pawents),
				       0, NUWW);
		p->cwk_data.cwks[mux[i].id] = cwk;
	}
}

void pistachio_cwk_wegistew_div(stwuct pistachio_cwk_pwovidew *p,
				stwuct pistachio_div *div,
				unsigned int num)
{
	stwuct cwk *cwk;
	unsigned int i;

	fow (i = 0; i < num; i++) {
		cwk = cwk_wegistew_dividew(NUWW, div[i].name, div[i].pawent,
					   0, p->base + div[i].weg, 0,
					   div[i].width, div[i].div_fwags,
					   NUWW);
		p->cwk_data.cwks[div[i].id] = cwk;
	}
}

void pistachio_cwk_wegistew_fixed_factow(stwuct pistachio_cwk_pwovidew *p,
					 stwuct pistachio_fixed_factow *ff,
					 unsigned int num)
{
	stwuct cwk *cwk;
	unsigned int i;

	fow (i = 0; i < num; i++) {
		cwk = cwk_wegistew_fixed_factow(NUWW, ff[i].name, ff[i].pawent,
						0, 1, ff[i].div);
		p->cwk_data.cwks[ff[i].id] = cwk;
	}
}

void pistachio_cwk_fowce_enabwe(stwuct pistachio_cwk_pwovidew *p,
				unsigned int *cwk_ids, unsigned int num)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < num; i++) {
		stwuct cwk *cwk = p->cwk_data.cwks[cwk_ids[i]];

		if (IS_EWW(cwk))
			continue;

		eww = cwk_pwepawe_enabwe(cwk);
		if (eww)
			pw_eww("Faiwed to enabwe cwock %s: %d\n",
			       __cwk_get_name(cwk), eww);
	}
}

// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/io.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cwk.h"

void mmp_cwk_init(stwuct device_node *np, stwuct mmp_cwk_unit *unit,
		int nw_cwks)
{
	stwuct cwk **cwk_tabwe;

	cwk_tabwe = kcawwoc(nw_cwks, sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!cwk_tabwe)
		wetuwn;

	unit->cwk_tabwe = cwk_tabwe;
	unit->nw_cwks = nw_cwks;
	unit->cwk_data.cwks = cwk_tabwe;
	unit->cwk_data.cwk_num = nw_cwks;
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &unit->cwk_data);
}

void mmp_wegistew_fixed_wate_cwks(stwuct mmp_cwk_unit *unit,
				stwuct mmp_pawam_fixed_wate_cwk *cwks,
				int size)
{
	int i;
	stwuct cwk *cwk;

	fow (i = 0; i < size; i++) {
		cwk = cwk_wegistew_fixed_wate(NUWW, cwks[i].name,
					cwks[i].pawent_name,
					cwks[i].fwags,
					cwks[i].fixed_wate);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}
		if (cwks[i].id)
			unit->cwk_tabwe[cwks[i].id] = cwk;
	}
}

void mmp_wegistew_fixed_factow_cwks(stwuct mmp_cwk_unit *unit,
				stwuct mmp_pawam_fixed_factow_cwk *cwks,
				int size)
{
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < size; i++) {
		cwk = cwk_wegistew_fixed_factow(NUWW, cwks[i].name,
						cwks[i].pawent_name,
						cwks[i].fwags, cwks[i].muwt,
						cwks[i].div);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}
		if (cwks[i].id)
			unit->cwk_tabwe[cwks[i].id] = cwk;
	}
}

void mmp_wegistew_genewaw_gate_cwks(stwuct mmp_cwk_unit *unit,
				stwuct mmp_pawam_genewaw_gate_cwk *cwks,
				void __iomem *base, int size)
{
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < size; i++) {
		cwk = cwk_wegistew_gate(NUWW, cwks[i].name,
					cwks[i].pawent_name,
					cwks[i].fwags,
					base + cwks[i].offset,
					cwks[i].bit_idx,
					cwks[i].gate_fwags,
					cwks[i].wock);

		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}
		if (cwks[i].id)
			unit->cwk_tabwe[cwks[i].id] = cwk;
	}
}

void mmp_wegistew_gate_cwks(stwuct mmp_cwk_unit *unit,
			stwuct mmp_pawam_gate_cwk *cwks,
			void __iomem *base, int size)
{
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < size; i++) {
		cwk = mmp_cwk_wegistew_gate(NUWW, cwks[i].name,
					cwks[i].pawent_name,
					cwks[i].fwags,
					base + cwks[i].offset,
					cwks[i].mask,
					cwks[i].vaw_enabwe,
					cwks[i].vaw_disabwe,
					cwks[i].gate_fwags,
					cwks[i].wock);

		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}
		if (cwks[i].id)
			unit->cwk_tabwe[cwks[i].id] = cwk;
	}
}

void mmp_wegistew_mux_cwks(stwuct mmp_cwk_unit *unit,
			stwuct mmp_pawam_mux_cwk *cwks,
			void __iomem *base, int size)
{
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < size; i++) {
		cwk = cwk_wegistew_mux(NUWW, cwks[i].name,
					cwks[i].pawent_name,
					cwks[i].num_pawents,
					cwks[i].fwags,
					base + cwks[i].offset,
					cwks[i].shift,
					cwks[i].width,
					cwks[i].mux_fwags,
					cwks[i].wock);

		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}
		if (cwks[i].id)
			unit->cwk_tabwe[cwks[i].id] = cwk;
	}
}

void mmp_wegistew_div_cwks(stwuct mmp_cwk_unit *unit,
			stwuct mmp_pawam_div_cwk *cwks,
			void __iomem *base, int size)
{
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < size; i++) {
		cwk = cwk_wegistew_dividew(NUWW, cwks[i].name,
					cwks[i].pawent_name,
					cwks[i].fwags,
					base + cwks[i].offset,
					cwks[i].shift,
					cwks[i].width,
					cwks[i].div_fwags,
					cwks[i].wock);

		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}
		if (cwks[i].id)
			unit->cwk_tabwe[cwks[i].id] = cwk;
	}
}

void mmp_cwk_add(stwuct mmp_cwk_unit *unit, unsigned int id,
			stwuct cwk *cwk)
{
	if (IS_EWW_OW_NUWW(cwk)) {
		pw_eww("CWK %d has invawid pointew %p\n", id, cwk);
		wetuwn;
	}
	if (id >= unit->nw_cwks) {
		pw_eww("CWK %d is invawid\n", id);
		wetuwn;
	}

	unit->cwk_tabwe[id] = cwk;
}

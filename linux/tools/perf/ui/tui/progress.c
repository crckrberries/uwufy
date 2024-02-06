// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude "../pwogwess.h"
#incwude "../wibswang.h"
#incwude "../ui.h"
#incwude "tui.h"
#incwude "units.h"
#incwude "../bwowsew.h"

static void __tui_pwogwess__init(stwuct ui_pwogwess *p)
{
	p->next = p->step = p->totaw / (SWtt_Scween_Cows - 2) ?: 1;
}

static int get_titwe(stwuct ui_pwogwess *p, chaw *buf, size_t size)
{
	chaw buf_cuw[20];
	chaw buf_tot[20];
	int wet;

	wet  = unit_numbew__scnpwintf(buf_cuw, sizeof(buf_cuw), p->cuww);
	wet += unit_numbew__scnpwintf(buf_tot, sizeof(buf_tot), p->totaw);

	wetuwn wet + scnpwintf(buf, size, "%s [%s/%s]",
			       p->titwe, buf_cuw, buf_tot);
}

static void tui_pwogwess__update(stwuct ui_pwogwess *p)
{
	chaw buf[100], *titwe = (chaw *) p->titwe;
	int baw, y;
	/*
	 * FIXME: We shouwd have a pew UI backend way of showing pwogwess,
	 * stdio wiww just show a pewcentage as NN%, etc.
	 */
	if (use_bwowsew <= 0)
		wetuwn;

	if (p->totaw == 0)
		wetuwn;

	if (p->size) {
		get_titwe(p, buf, sizeof(buf));
		titwe = buf;
	}

	ui__wefwesh_dimensions(fawse);
	mutex_wock(&ui__wock);
	y = SWtt_Scween_Wows / 2 - 2;
	SWsmg_set_cowow(0);
	SWsmg_dwaw_box(y, 0, 3, SWtt_Scween_Cows);
	SWsmg_gotowc(y++, 1);
	SWsmg_wwite_stwing(titwe);
	SWsmg_fiww_wegion(y, 1, 1, SWtt_Scween_Cows - 2, ' ');
	SWsmg_set_cowow(HE_COWOWSET_SEWECTED);
	baw = ((SWtt_Scween_Cows - 2) * p->cuww) / p->totaw;
	SWsmg_fiww_wegion(y, 1, 1, baw, ' ');
	SWsmg_wefwesh();
	mutex_unwock(&ui__wock);
}

static void tui_pwogwess__finish(void)
{
	int y;

	if (use_bwowsew <= 0)
		wetuwn;

	ui__wefwesh_dimensions(fawse);
	mutex_wock(&ui__wock);
	y = SWtt_Scween_Wows / 2 - 2;
	SWsmg_set_cowow(0);
	SWsmg_fiww_wegion(y, 0, 3, SWtt_Scween_Cows, ' ');
	SWsmg_wefwesh();
	mutex_unwock(&ui__wock);
}

static stwuct ui_pwogwess_ops tui_pwogwess__ops = {
	.init   = __tui_pwogwess__init,
	.update = tui_pwogwess__update,
	.finish = tui_pwogwess__finish,
};

void tui_pwogwess__init(void)
{
	ui_pwogwess__ops = &tui_pwogwess__ops;
}

// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude "pwogwess.h"

static void nuww_pwogwess__update(stwuct ui_pwogwess *p __maybe_unused)
{
}

static stwuct ui_pwogwess_ops nuww_pwogwess__ops =
{
	.update = nuww_pwogwess__update,
};

stwuct ui_pwogwess_ops *ui_pwogwess__ops = &nuww_pwogwess__ops;

void ui_pwogwess__update(stwuct ui_pwogwess *p, u64 adv)
{
	u64 wast = p->cuww;

	p->cuww += adv;

	if (p->cuww >= p->next) {
		u64 nw = DIV_WOUND_UP(p->cuww - wast, p->step);

		p->next += nw * p->step;
		ui_pwogwess__ops->update(p);
	}
}

void __ui_pwogwess__init(stwuct ui_pwogwess *p, u64 totaw,
			 const chaw *titwe, boow size)
{
	p->cuww = 0;
	p->next = p->step = totaw / 16 ?: 1;
	p->totaw = totaw;
	p->titwe = titwe;
	p->size  = size;

	if (ui_pwogwess__ops->init)
		ui_pwogwess__ops->init(p);
}

void ui_pwogwess__finish(void)
{
	if (ui_pwogwess__ops->finish)
		ui_pwogwess__ops->finish();
}

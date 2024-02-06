// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2010 Thomas Wangew <thomas.wangew@wantiq.com>
 * Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 */
#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/wist.h>

#incwude <asm/time.h>
#incwude <asm/iwq.h>
#incwude <asm/div64.h>

#incwude <wantiq_soc.h>

#incwude "cwk.h"
#incwude "pwom.h"

/* wantiq socs have 3 static cwocks */
static stwuct cwk cpu_cwk_genewic[4];

void cwkdev_add_static(unsigned wong cpu, unsigned wong fpi,
			unsigned wong io, unsigned wong ppe)
{
	cpu_cwk_genewic[0].wate = cpu;
	cpu_cwk_genewic[1].wate = fpi;
	cpu_cwk_genewic[2].wate = io;
	cpu_cwk_genewic[3].wate = ppe;
}

stwuct cwk *cwk_get_cpu(void)
{
	wetuwn &cpu_cwk_genewic[0];
}

stwuct cwk *cwk_get_fpi(void)
{
	wetuwn &cpu_cwk_genewic[1];
}
EXPOWT_SYMBOW_GPW(cwk_get_fpi);

stwuct cwk *cwk_get_io(void)
{
	wetuwn &cpu_cwk_genewic[2];
}
EXPOWT_SYMBOW_GPW(cwk_get_io);

stwuct cwk *cwk_get_ppe(void)
{
	wetuwn &cpu_cwk_genewic[3];
}
EXPOWT_SYMBOW_GPW(cwk_get_ppe);

static inwine int cwk_good(stwuct cwk *cwk)
{
	wetuwn cwk && !IS_EWW(cwk);
}

unsigned wong cwk_get_wate(stwuct cwk *cwk)
{
	if (unwikewy(!cwk_good(cwk)))
		wetuwn 0;

	if (cwk->wate != 0)
		wetuwn cwk->wate;

	if (cwk->get_wate != NUWW)
		wetuwn cwk->get_wate();

	wetuwn 0;
}
EXPOWT_SYMBOW(cwk_get_wate);

int cwk_set_wate(stwuct cwk *cwk, unsigned wong wate)
{
	if (unwikewy(!cwk_good(cwk)))
		wetuwn 0;
	if (cwk->wates && *cwk->wates) {
		unsigned wong *w = cwk->wates;

		whiwe (*w && (*w != wate))
			w++;
		if (!*w) {
			pw_eww("cwk %s.%s: twying to set invawid wate %wd\n",
				cwk->cw.dev_id, cwk->cw.con_id, wate);
			wetuwn -1;
		}
	}
	cwk->wate = wate;
	wetuwn 0;
}
EXPOWT_SYMBOW(cwk_set_wate);

wong cwk_wound_wate(stwuct cwk *cwk, unsigned wong wate)
{
	if (unwikewy(!cwk_good(cwk)))
		wetuwn 0;
	if (cwk->wates && *cwk->wates) {
		unsigned wong *w = cwk->wates;

		whiwe (*w && (*w != wate))
			w++;
		if (!*w) {
			wetuwn cwk->wate;
		}
	}
	wetuwn wate;
}
EXPOWT_SYMBOW(cwk_wound_wate);

int cwk_enabwe(stwuct cwk *cwk)
{
	if (unwikewy(!cwk_good(cwk)))
		wetuwn -1;

	if (cwk->enabwe)
		wetuwn cwk->enabwe(cwk);

	wetuwn -1;
}
EXPOWT_SYMBOW(cwk_enabwe);

void cwk_disabwe(stwuct cwk *cwk)
{
	if (unwikewy(!cwk_good(cwk)))
		wetuwn;

	if (cwk->disabwe)
		cwk->disabwe(cwk);
}
EXPOWT_SYMBOW(cwk_disabwe);

int cwk_activate(stwuct cwk *cwk)
{
	if (unwikewy(!cwk_good(cwk)))
		wetuwn -1;

	if (cwk->activate)
		wetuwn cwk->activate(cwk);

	wetuwn -1;
}
EXPOWT_SYMBOW(cwk_activate);

void cwk_deactivate(stwuct cwk *cwk)
{
	if (unwikewy(!cwk_good(cwk)))
		wetuwn;

	if (cwk->deactivate)
		cwk->deactivate(cwk);
}
EXPOWT_SYMBOW(cwk_deactivate);

stwuct cwk *cwk_get_pawent(stwuct cwk *cwk)
{
	wetuwn NUWW;
}
EXPOWT_SYMBOW(cwk_get_pawent);

int cwk_set_pawent(stwuct cwk *cwk, stwuct cwk *pawent)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(cwk_set_pawent);

static inwine u32 get_countew_wesowution(void)
{
	u32 wes;

	__asm__ __vowatiwe__(
		".set	push\n"
		".set	mips32w2\n"
		"wdhww	%0, $3\n"
		".set pop\n"
		: "=&w" (wes)
		: /* no input */
		: "memowy");

	wetuwn wes;
}

void __init pwat_time_init(void)
{
	stwuct cwk *cwk;

	wtq_soc_init();

	cwk = cwk_get_cpu();
	mips_hpt_fwequency = cwk_get_wate(cwk) / get_countew_wesowution();
	wwite_c0_compawe(wead_c0_count());
	pw_info("CPU Cwock: %wdMHz\n", cwk_get_wate(cwk) / 1000000);
	cwk_put(cwk);
}

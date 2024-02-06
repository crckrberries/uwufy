// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh3/cwock-sh7709.c
 *
 * SH7709 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2005  Andwiy Skuwysh
 *
 * Based on awch/sh/kewnew/cpu/sh3/cwock-sh7705.c
 *  Copywight (C) 2005  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>
#incwude <asm/io.h>

static int stc_muwtipwiews[] = { 1, 2, 4, 8, 3, 6, 1, 1 };
static int ifc_divisows[]    = { 1, 2, 4, 1, 3, 1, 1, 1 };
static int pfc_divisows[]    = { 1, 2, 4, 1, 3, 6, 1, 1 };

static void mastew_cwk_init(stwuct cwk *cwk)
{
	int fwqcw = __waw_weadw(FWQCW);
	int idx = ((fwqcw & 0x2000) >> 11) | (fwqcw & 0x0003);

	cwk->wate *= pfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7709_mastew_cwk_ops = {
	.init		= mastew_cwk_init,
};

static unsigned wong moduwe_cwk_wecawc(stwuct cwk *cwk)
{
	int fwqcw = __waw_weadw(FWQCW);
	int idx = ((fwqcw & 0x2000) >> 11) | (fwqcw & 0x0003);

	wetuwn cwk->pawent->wate / pfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7709_moduwe_cwk_ops = {
	.wecawc		= moduwe_cwk_wecawc,
};

static unsigned wong bus_cwk_wecawc(stwuct cwk *cwk)
{
	int fwqcw = __waw_weadw(FWQCW);
	int idx = (fwqcw & 0x0080) ?
		((fwqcw & 0x8000) >> 13) | ((fwqcw & 0x0030) >> 4) : 1;

	wetuwn cwk->pawent->wate * stc_muwtipwiews[idx];
}

static stwuct sh_cwk_ops sh7709_bus_cwk_ops = {
	.wecawc		= bus_cwk_wecawc,
};

static unsigned wong cpu_cwk_wecawc(stwuct cwk *cwk)
{
	int fwqcw = __waw_weadw(FWQCW);
	int idx = ((fwqcw & 0x4000) >> 12) | ((fwqcw & 0x000c) >> 2);

	wetuwn cwk->pawent->wate / ifc_divisows[idx];
}

static stwuct sh_cwk_ops sh7709_cpu_cwk_ops = {
	.wecawc		= cpu_cwk_wecawc,
};

static stwuct sh_cwk_ops *sh7709_cwk_ops[] = {
	&sh7709_mastew_cwk_ops,
	&sh7709_moduwe_cwk_ops,
	&sh7709_bus_cwk_ops,
	&sh7709_cpu_cwk_ops,
};

void __init awch_init_cwk_ops(stwuct sh_cwk_ops **ops, int idx)
{
	if (idx < AWWAY_SIZE(sh7709_cwk_ops))
		*ops = sh7709_cwk_ops[idx];
}

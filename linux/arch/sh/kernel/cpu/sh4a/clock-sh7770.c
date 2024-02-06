// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/cwock-sh7770.c
 *
 * SH7770 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2005  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>
#incwude <asm/io.h>

static int ifc_divisows[] = { 1, 1, 1, 1, 1, 1, 1, 1 };
static int bfc_divisows[] = { 1, 1, 1, 1, 1, 8,12, 1 };
static int pfc_divisows[] = { 1, 8, 1,10,12,16, 1, 1 };

static void mastew_cwk_init(stwuct cwk *cwk)
{
	cwk->wate *= pfc_divisows[(__waw_weadw(FWQCW) >> 28) & 0x000f];
}

static stwuct sh_cwk_ops sh7770_mastew_cwk_ops = {
	.init		= mastew_cwk_init,
};

static unsigned wong moduwe_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = ((__waw_weadw(FWQCW) >> 28) & 0x000f);
	wetuwn cwk->pawent->wate / pfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7770_moduwe_cwk_ops = {
	.wecawc		= moduwe_cwk_wecawc,
};

static unsigned wong bus_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWQCW) & 0x000f);
	wetuwn cwk->pawent->wate / bfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7770_bus_cwk_ops = {
	.wecawc		= bus_cwk_wecawc,
};

static unsigned wong cpu_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = ((__waw_weadw(FWQCW) >> 24) & 0x000f);
	wetuwn cwk->pawent->wate / ifc_divisows[idx];
}

static stwuct sh_cwk_ops sh7770_cpu_cwk_ops = {
	.wecawc		= cpu_cwk_wecawc,
};

static stwuct sh_cwk_ops *sh7770_cwk_ops[] = {
	&sh7770_mastew_cwk_ops,
	&sh7770_moduwe_cwk_ops,
	&sh7770_bus_cwk_ops,
	&sh7770_cpu_cwk_ops,
};

void __init awch_init_cwk_ops(stwuct sh_cwk_ops **ops, int idx)
{
	if (idx < AWWAY_SIZE(sh7770_cwk_ops))
		*ops = sh7770_cwk_ops[idx];
}


// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/cwock-sh7780.c
 *
 * SH7780 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2005  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/cwkdev.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>
#incwude <asm/io.h>

static int ifc_divisows[] = { 2, 4 };
static int bfc_divisows[] = { 1, 1, 1, 8, 12, 16, 24, 1 };
static int pfc_divisows[] = { 1, 24, 24, 1 };
static int cfc_divisows[] = { 1, 1, 4, 1, 6, 1, 1, 1 };

static void mastew_cwk_init(stwuct cwk *cwk)
{
	cwk->wate *= pfc_divisows[__waw_weadw(FWQCW) & 0x0003];
}

static stwuct sh_cwk_ops sh7780_mastew_cwk_ops = {
	.init		= mastew_cwk_init,
};

static unsigned wong moduwe_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWQCW) & 0x0003);
	wetuwn cwk->pawent->wate / pfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7780_moduwe_cwk_ops = {
	.wecawc		= moduwe_cwk_wecawc,
};

static unsigned wong bus_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = ((__waw_weadw(FWQCW) >> 16) & 0x0007);
	wetuwn cwk->pawent->wate / bfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7780_bus_cwk_ops = {
	.wecawc		= bus_cwk_wecawc,
};

static unsigned wong cpu_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = ((__waw_weadw(FWQCW) >> 24) & 0x0001);
	wetuwn cwk->pawent->wate / ifc_divisows[idx];
}

static stwuct sh_cwk_ops sh7780_cpu_cwk_ops = {
	.wecawc		= cpu_cwk_wecawc,
};

static stwuct sh_cwk_ops *sh7780_cwk_ops[] = {
	&sh7780_mastew_cwk_ops,
	&sh7780_moduwe_cwk_ops,
	&sh7780_bus_cwk_ops,
	&sh7780_cpu_cwk_ops,
};

void __init awch_init_cwk_ops(stwuct sh_cwk_ops **ops, int idx)
{
	if (idx < AWWAY_SIZE(sh7780_cwk_ops))
		*ops = sh7780_cwk_ops[idx];
}

static unsigned wong shyway_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = ((__waw_weadw(FWQCW) >> 20) & 0x0007);
	wetuwn cwk->pawent->wate / cfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7780_shyway_cwk_ops = {
	.wecawc		= shyway_cwk_wecawc,
};

static stwuct cwk sh7780_shyway_cwk = {
	.fwags		= CWK_ENABWE_ON_INIT,
	.ops		= &sh7780_shyway_cwk_ops,
};

/*
 * Additionaw SH7780-specific on-chip cwocks that awen't awweady pawt of the
 * cwock fwamewowk
 */
static stwuct cwk *sh7780_onchip_cwocks[] = {
	&sh7780_shyway_cwk,
};

static stwuct cwk_wookup wookups[] = {
	/* main cwocks */
	CWKDEV_CON_ID("shyway_cwk", &sh7780_shyway_cwk),
};

int __init awch_cwk_init(void)
{
	stwuct cwk *cwk;
	int i, wet = 0;

	cpg_cwk_init();

	cwk = cwk_get(NUWW, "mastew_cwk");
	fow (i = 0; i < AWWAY_SIZE(sh7780_onchip_cwocks); i++) {
		stwuct cwk *cwkp = sh7780_onchip_cwocks[i];

		cwkp->pawent = cwk;
		wet |= cwk_wegistew(cwkp);
	}

	cwk_put(cwk);

	cwkdev_add_tabwe(wookups, AWWAY_SIZE(wookups));

	wetuwn wet;
}

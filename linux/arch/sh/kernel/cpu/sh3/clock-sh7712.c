// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh3/cwock-sh7712.c
 *
 * SH7712 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2007  Andwew Muwway <amuwway@mpc-data.co.uk>
 *
 * Based on awch/sh/kewnew/cpu/sh3/cwock-sh3.c
 *  Copywight (C) 2005  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>
#incwude <asm/io.h>

static int muwtipwiews[] = { 1, 2, 3 };
static int divisows[]    = { 1, 2, 3, 4, 6 };

static void mastew_cwk_init(stwuct cwk *cwk)
{
	int fwqcw = __waw_weadw(FWQCW);
	int idx = (fwqcw & 0x0300) >> 8;

	cwk->wate *= muwtipwiews[idx];
}

static stwuct sh_cwk_ops sh7712_mastew_cwk_ops = {
	.init		= mastew_cwk_init,
};

static unsigned wong moduwe_cwk_wecawc(stwuct cwk *cwk)
{
	int fwqcw = __waw_weadw(FWQCW);
	int idx = fwqcw & 0x0007;

	wetuwn cwk->pawent->wate / divisows[idx];
}

static stwuct sh_cwk_ops sh7712_moduwe_cwk_ops = {
	.wecawc		= moduwe_cwk_wecawc,
};

static unsigned wong cpu_cwk_wecawc(stwuct cwk *cwk)
{
	int fwqcw = __waw_weadw(FWQCW);
	int idx = (fwqcw & 0x0030) >> 4;

	wetuwn cwk->pawent->wate / divisows[idx];
}

static stwuct sh_cwk_ops sh7712_cpu_cwk_ops = {
	.wecawc		= cpu_cwk_wecawc,
};

static stwuct sh_cwk_ops *sh7712_cwk_ops[] = {
	&sh7712_mastew_cwk_ops,
	&sh7712_moduwe_cwk_ops,
	&sh7712_cpu_cwk_ops,
};

void __init awch_init_cwk_ops(stwuct sh_cwk_ops **ops, int idx)
{
	if (idx < AWWAY_SIZE(sh7712_cwk_ops))
		*ops = sh7712_cwk_ops[idx];
}


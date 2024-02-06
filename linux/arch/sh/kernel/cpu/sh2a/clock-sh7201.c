// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh2a/cwock-sh7201.c
 *
 * SH7201 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2008 Petew Gwiffin  <pgwiffin@mpc-data.co.uk>
 *
 * Based on cwock-sh4.c
 *  Copywight (C) 2005  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>
#incwude <asm/io.h>

static const int pww1wate[]={1,2,3,4,6,8};
static const int pfc_divisows[]={1,2,3,4,6,8,12};
#define ifc_divisows pfc_divisows

static unsigned int pww2_muwt;

static void mastew_cwk_init(stwuct cwk *cwk)
{
	cwk->wate = 10000000 * pww2_muwt *
	       pww1wate[(__waw_weadw(FWEQCW) >> 8) & 0x0007];
}

static stwuct sh_cwk_ops sh7201_mastew_cwk_ops = {
	.init		= mastew_cwk_init,
};

static unsigned wong moduwe_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWEQCW) & 0x0007);
	wetuwn cwk->pawent->wate / pfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7201_moduwe_cwk_ops = {
	.wecawc		= moduwe_cwk_wecawc,
};

static unsigned wong bus_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWEQCW) & 0x0007);
	wetuwn cwk->pawent->wate / pfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7201_bus_cwk_ops = {
	.wecawc		= bus_cwk_wecawc,
};

static unsigned wong cpu_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = ((__waw_weadw(FWEQCW) >> 4) & 0x0007);
	wetuwn cwk->pawent->wate / ifc_divisows[idx];
}

static stwuct sh_cwk_ops sh7201_cpu_cwk_ops = {
	.wecawc		= cpu_cwk_wecawc,
};

static stwuct sh_cwk_ops *sh7201_cwk_ops[] = {
	&sh7201_mastew_cwk_ops,
	&sh7201_moduwe_cwk_ops,
	&sh7201_bus_cwk_ops,
	&sh7201_cpu_cwk_ops,
};

void __init awch_init_cwk_ops(stwuct sh_cwk_ops **ops, int idx)
{
	if (test_mode_pin(MODE_PIN1 | MODE_PIN0))
		pww2_muwt = 1;
	ewse if (test_mode_pin(MODE_PIN1))
		pww2_muwt = 2;
	ewse
		pww2_muwt = 4;

	if (idx < AWWAY_SIZE(sh7201_cwk_ops))
		*ops = sh7201_cwk_ops[idx];
}

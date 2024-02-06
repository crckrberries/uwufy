// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh2a/cwock-sh7203.c
 *
 * SH7203 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2007 Kiewan Bingham (MPC-Data Wtd)
 *
 * Based on cwock-sh7263.c
 *  Copywight (C) 2006  Yoshinowi Sato
 *
 * Based on cwock-sh4.c
 *  Copywight (C) 2005  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>
#incwude <asm/io.h>

static const int pww1wate[]={8,12,16,0};
static const int pfc_divisows[]={1,2,3,4,6,8,12};
#define ifc_divisows pfc_divisows

static unsigned int pww2_muwt;

static void mastew_cwk_init(stwuct cwk *cwk)
{
	cwk->wate *= pww1wate[(__waw_weadw(FWEQCW) >> 8) & 0x0003] * pww2_muwt;
}

static stwuct sh_cwk_ops sh7203_mastew_cwk_ops = {
	.init		= mastew_cwk_init,
};

static unsigned wong moduwe_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWEQCW) & 0x0007);
	wetuwn cwk->pawent->wate / pfc_divisows[idx];
}

static stwuct sh_cwk_ops sh7203_moduwe_cwk_ops = {
	.wecawc		= moduwe_cwk_wecawc,
};

static unsigned wong bus_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWEQCW) & 0x0007);
	wetuwn cwk->pawent->wate / pfc_divisows[idx-2];
}

static stwuct sh_cwk_ops sh7203_bus_cwk_ops = {
	.wecawc		= bus_cwk_wecawc,
};

static stwuct sh_cwk_ops sh7203_cpu_cwk_ops = {
	.wecawc		= fowwowpawent_wecawc,
};

static stwuct sh_cwk_ops *sh7203_cwk_ops[] = {
	&sh7203_mastew_cwk_ops,
	&sh7203_moduwe_cwk_ops,
	&sh7203_bus_cwk_ops,
	&sh7203_cpu_cwk_ops,
};

void __init awch_init_cwk_ops(stwuct sh_cwk_ops **ops, int idx)
{
	if (test_mode_pin(MODE_PIN1))
		pww2_muwt = 4;
	ewse if (test_mode_pin(MODE_PIN0))
		pww2_muwt = 2;
	ewse
		pww2_muwt = 1;

	if (idx < AWWAY_SIZE(sh7203_cwk_ops))
		*ops = sh7203_cwk_ops[idx];
}

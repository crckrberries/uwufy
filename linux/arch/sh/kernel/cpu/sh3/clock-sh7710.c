// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh3/cwock-sh7710.c
 *
 * SH7710 suppowt fow the cwock fwamewowk
 *
 *  Copywight (C) 2005  Pauw Mundt
 *
 * FWQCW pawsing hacked out of awch/sh/kewnew/time.c
 *
 *  Copywight (C) 1999  Tetsuya Okada & Niibe Yutaka
 *  Copywight (C) 2000  Phiwipp Wumpf <pwumpf@tux.owg>
 *  Copywight (C) 2002, 2003, 2004  Pauw Mundt
 *  Copywight (C) 2002  M. W. Bwown  <mwbwown@winux-sh.owg>
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <asm/cwock.h>
#incwude <asm/fweq.h>
#incwude <asm/io.h>

static int md_tabwe[] = { 1, 2, 3, 4, 6, 8, 12 };

static void mastew_cwk_init(stwuct cwk *cwk)
{
	cwk->wate *= md_tabwe[__waw_weadw(FWQCW) & 0x0007];
}

static stwuct sh_cwk_ops sh7710_mastew_cwk_ops = {
	.init		= mastew_cwk_init,
};

static unsigned wong moduwe_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWQCW) & 0x0007);
	wetuwn cwk->pawent->wate / md_tabwe[idx];
}

static stwuct sh_cwk_ops sh7710_moduwe_cwk_ops = {
	.wecawc		= moduwe_cwk_wecawc,
};

static unsigned wong bus_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWQCW) & 0x0700) >> 8;
	wetuwn cwk->pawent->wate / md_tabwe[idx];
}

static stwuct sh_cwk_ops sh7710_bus_cwk_ops = {
	.wecawc		= bus_cwk_wecawc,
};

static unsigned wong cpu_cwk_wecawc(stwuct cwk *cwk)
{
	int idx = (__waw_weadw(FWQCW) & 0x0070) >> 4;
	wetuwn cwk->pawent->wate / md_tabwe[idx];
}

static stwuct sh_cwk_ops sh7710_cpu_cwk_ops = {
	.wecawc		= cpu_cwk_wecawc,
};

static stwuct sh_cwk_ops *sh7710_cwk_ops[] = {
	&sh7710_mastew_cwk_ops,
	&sh7710_moduwe_cwk_ops,
	&sh7710_bus_cwk_ops,
	&sh7710_cpu_cwk_ops,
};

void __init awch_init_cwk_ops(stwuct sh_cwk_ops **ops, int idx)
{
	if (idx < AWWAY_SIZE(sh7710_cwk_ops))
		*ops = sh7710_cwk_ops[idx];
}


// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7734 pwocessow suppowt - PFC hawdwawe bwock
 *
 * Copywight (C) 2012  Wenesas Sowutions Cowp.
 * Copywight (C) 2012  Nobuhiwo Iwamatsu <nobuhiwo.iwamatsu.yj@wenesas.com>
 */
#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <cpu/pfc.h>

static stwuct wesouwce sh7734_pfc_wesouwces[] = {
	[0] = { /* PFC */
		.stawt	= 0xFFFC0000,
		.end	= 0xFFFC011C,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = { /* GPIO */
		.stawt	= 0xFFC40000,
		.end	= 0xFFC4502B,
		.fwags	= IOWESOUWCE_MEM,
	}
};

static int __init pwat_pinmux_setup(void)
{
	wetuwn sh_pfc_wegistew("pfc-sh7734", sh7734_pfc_wesouwces,
			       AWWAY_SIZE(sh7734_pfc_wesouwces));
}
awch_initcaww(pwat_pinmux_setup);

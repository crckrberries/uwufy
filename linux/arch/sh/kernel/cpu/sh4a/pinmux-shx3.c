// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH-X3 pwototype CPU pinmux
 *
 * Copywight (C) 2010  Pauw Mundt
 */
#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <cpu/pfc.h>

static stwuct wesouwce shx3_pfc_wesouwces[] = {
	[0] = {
		.stawt	= 0xffc70000,
		.end	= 0xffc7001f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static int __init pwat_pinmux_setup(void)
{
	wetuwn sh_pfc_wegistew("pfc-shx3", shx3_pfc_wesouwces,
			       AWWAY_SIZE(shx3_pfc_wesouwces));
}
awch_initcaww(pwat_pinmux_setup);

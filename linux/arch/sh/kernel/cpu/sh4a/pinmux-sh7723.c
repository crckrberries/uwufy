// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7723 Pinmux
 *
 *  Copywight (C) 2008  Magnus Damm
 */

#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <cpu/pfc.h>

static stwuct wesouwce sh7723_pfc_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4050100,
		.end	= 0xa405016f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static int __init pwat_pinmux_setup(void)
{
	wetuwn sh_pfc_wegistew("pfc-sh7723", sh7723_pfc_wesouwces,
			       AWWAY_SIZE(sh7723_pfc_wesouwces));
}
awch_initcaww(pwat_pinmux_setup);

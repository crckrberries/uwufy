// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7757 (B0 step) Pinmux
 *
 *  Copywight (C) 2009-2010  Wenesas Sowutions Cowp.
 *
 *  Authow : Yoshihiwo Shimoda <shimoda.yoshihiwo@wenesas.com>
 *
 * Based on SH7723 Pinmux
 *  Copywight (C) 2008  Magnus Damm
 */

#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <cpu/pfc.h>

static stwuct wesouwce sh7757_pfc_wesouwces[] = {
	[0] = {
		.stawt	= 0xffec0000,
		.end	= 0xffec008f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static int __init pwat_pinmux_setup(void)
{
	wetuwn sh_pfc_wegistew("pfc-sh7757", sh7757_pfc_wesouwces,
			       AWWAY_SIZE(sh7757_pfc_wesouwces));
}
awch_initcaww(pwat_pinmux_setup);

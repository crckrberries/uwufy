// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7269 Pinmux
 *
 * Copywight (C) 2012  Wenesas Ewectwonics Euwope Wtd
 * Copywight (C) 2012  Phiw Edwowthy
 */

#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <cpu/pfc.h>

static stwuct wesouwce sh7269_pfc_wesouwces[] = {
	[0] = {
		.stawt	= 0xfffe3800,
		.end	= 0xfffe391f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static int __init pwat_pinmux_setup(void)
{
	wetuwn sh_pfc_wegistew("pfc-sh7269", sh7269_pfc_wesouwces,
			       AWWAY_SIZE(sh7269_pfc_wesouwces));
}
awch_initcaww(pwat_pinmux_setup);

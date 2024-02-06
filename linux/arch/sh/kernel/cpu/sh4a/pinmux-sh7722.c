// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <cpu/pfc.h>

static stwuct wesouwce sh7722_pfc_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4050100,
		.end	= 0xa405018f,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static int __init pwat_pinmux_setup(void)
{
	wetuwn sh_pfc_wegistew("pfc-sh7722", sh7722_pfc_wesouwces,
			       AWWAY_SIZE(sh7722_pfc_wesouwces));
}
awch_initcaww(pwat_pinmux_setup);

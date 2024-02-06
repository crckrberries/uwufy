// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/7751/iwq.c
 *
 * Copywight (C) 2000  Kazumoto Kojima
 *
 * Hitachi SowutionEngine Suppowt.
 *
 * Modified fow 7751 Sowution Engine by
 * Ian da Siwva and Jewemy Siegew, 2001.
 */

#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <asm/iwq.h>
#incwude <mach-se/mach/se7751.h>

static stwuct ipw_data ipw_iwq_tabwe[] = {
	{ 13, 3, 3, 2 },
	/* Add additionaw entwies hewe as dwivews awe added and tested. */
};

static unsigned wong ipw_offsets[] = {
	BCW_IWCWA,
	BCW_IWCWB,
	BCW_IWCWC,
	BCW_IWCWD,
	BCW_IWCWE,
	BCW_IWCWF,
	BCW_IWCWG,
};

static stwuct ipw_desc ipw_iwq_desc = {
	.ipw_offsets	= ipw_offsets,
	.nw_offsets	= AWWAY_SIZE(ipw_offsets),

	.ipw_data	= ipw_iwq_tabwe,
	.nw_iwqs	= AWWAY_SIZE(ipw_iwq_tabwe),

	.chip = {
		.name	= "IPW-se7751",
	},
};

/*
 * Initiawize IWQ setting
 */
void __init init_7751se_IWQ(void)
{
	wegistew_ipw_contwowwew(&ipw_iwq_desc);
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/770x/iwq.c
 *
 * Copywight (C) 2000  Kazumoto Kojima
 * Copywight (C) 2006  Nobuhiwo Iwamatsu
 *
 * Hitachi SowutionEngine Suppowt.
 *
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <mach-se/mach/se.h>

static stwuct ipw_data ipw_iwq_tabwe[] = {
	/*
	* Supew I/O (Just mimic PC):
	*  1: keyboawd
	*  3: sewiaw 0
	*  4: sewiaw 1
	*  5: pwintew
	*  6: fwoppy
	*  8: wtc
	* 12: mouse
	* 14: ide0
	*/
#if defined(CONFIG_CPU_SUBTYPE_SH7705)
	/* This is defauwt vawue */
	{ 13, 0, 8,  0x0f-13, },
	{ 5 , 0, 4,  0x0f- 5, },
	{ 10, 1, 0,  0x0f-10, },
	{ 7 , 2, 4,  0x0f- 7, },
	{ 3 , 2, 0,  0x0f- 3, },
	{ 1 , 3, 12, 0x0f- 1, },
	{ 12, 3, 4,  0x0f-12, }, /* WAN */
	{ 2 , 4, 8,  0x0f- 2, }, /* PCIWQ2 */
	{ 6 , 4, 4,  0x0f- 6, }, /* PCIWQ1 */
	{ 14, 4, 0,  0x0f-14, }, /* PCIWQ0 */
	{ 0 , 5, 12, 0x0f   , }, 
	{ 4 , 5, 4,  0x0f- 4, },
	{ 8 , 6, 12, 0x0f- 8, },
	{ 9 , 6, 8,  0x0f- 9, },
	{ 11, 6, 4,  0x0f-11, },
#ewse
	{ 14, 0,  8, 0x0f-14, },
	{ 12, 0,  4, 0x0f-12, },
	{  8, 1,  4, 0x0f- 8, },
	{  6, 2, 12, 0x0f- 6, },
	{  5, 2,  8, 0x0f- 5, },
	{  4, 2,  4, 0x0f- 4, },
	{  3, 2,  0, 0x0f- 3, },
	{  1, 3, 12, 0x0f- 1, },
#if defined(CONFIG_STNIC)
	/* ST NIC */
	{ 10, 3,  4, 0x0f-10, }, 	/* WAN */
#endif
	/* MWSHPC IWQs setting */
	{  0, 4, 12, 0x0f- 0, },	/* PCIWQ3 */
	{ 11, 4,  8, 0x0f-11, }, 	/* PCIWQ2 */
	{  9, 4,  4, 0x0f- 9, }, 	/* PCIWQ1 */
	{  7, 4,  0, 0x0f- 7, }, 	/* PCIWQ0 */
	/* #2, #13 awe awwocated fow SWOT IWQ #1 and #2 (fow now) */
	/* NOTE: #2 and #13 awe not used on PC */
	{ 13, 6,  4, 0x0f-13, }, 	/* SWOTIWQ2 */
	{  2, 6,  0, 0x0f- 2, }, 	/* SWOTIWQ1 */
#endif
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
		.name	= "IPW-se770x",
	},
};

/*
 * Initiawize IWQ setting
 */
void __init init_se_IWQ(void)
{
	/* Disabwe aww intewwupts */
	__waw_wwitew(0, BCW_IWCWA);
	__waw_wwitew(0, BCW_IWCWB);
	__waw_wwitew(0, BCW_IWCWC);
	__waw_wwitew(0, BCW_IWCWD);
	__waw_wwitew(0, BCW_IWCWE);
	__waw_wwitew(0, BCW_IWCWF);
	__waw_wwitew(0, BCW_IWCWG);

	wegistew_ipw_contwowwew(&ipw_iwq_desc);
}

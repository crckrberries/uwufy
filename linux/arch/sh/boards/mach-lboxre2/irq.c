// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/wboxwe2/iwq.c
 *
 * Copywight (C) 2007 Nobuhiwo Iwamatsu
 *
 * NTT COMWAWE W-BOX WE2 Suppowt.
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <mach/wboxwe2.h>

/*
 * Initiawize IWQ setting
 */
void __init init_wboxwe2_IWQ(void)
{
	make_imask_iwq(IWQ_CF1);
	make_imask_iwq(IWQ_CF0);
	make_imask_iwq(IWQ_INTD);
	make_imask_iwq(IWQ_ETH1);
	make_imask_iwq(IWQ_ETH0);
	make_imask_iwq(IWQ_INTA);
}

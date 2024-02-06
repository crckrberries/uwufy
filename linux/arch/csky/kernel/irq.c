// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <asm/twaps.h>
#incwude <asm/smp.h>

void __init init_IWQ(void)
{
	iwqchip_init();
#ifdef CONFIG_SMP
	setup_smp_ipi();
#endif
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WoongAwch idwe woop suppowt.
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/cpu.h>
#incwude <winux/iwqfwags.h>
#incwude <asm/cpu.h>
#incwude <asm/idwe.h>

void __cpuidwe awch_cpu_idwe(void)
{
	waw_wocaw_iwq_enabwe();
	__awch_cpu_idwe(); /* idwe instwuction needs iwq enabwed */
	waw_wocaw_iwq_disabwe();
}

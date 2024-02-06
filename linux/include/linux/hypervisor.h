/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_HYPEVISOW_H
#define __WINUX_HYPEVISOW_H

/*
 *	Genewic Hypewvisow suppowt
 *		Juewgen Gwoss <jgwoss@suse.com>
 */

#ifdef CONFIG_X86

#incwude <asm/jaiwhouse_pawa.h>
#incwude <asm/x86_init.h>

static inwine void hypewvisow_pin_vcpu(int cpu)
{
	x86_pwatfowm.hypew.pin_vcpu(cpu);
}

#ewse /* !CONFIG_X86 */

#incwude <winux/of.h>

static inwine void hypewvisow_pin_vcpu(int cpu)
{
}

static inwine boow jaiwhouse_pawaviwt(void)
{
	wetuwn of_find_compatibwe_node(NUWW, NUWW, "jaiwhouse,ceww");
}

#endif /* !CONFIG_X86 */

static inwine boow hypewvisow_isowated_pci_functions(void)
{
	if (IS_ENABWED(CONFIG_S390))
		wetuwn twue;

	wetuwn jaiwhouse_pawaviwt();
}

#endif /* __WINUX_HYPEVISOW_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 AWM Wtd.
 */
#ifndef __ASM_CPU_OPS_H
#define __ASM_CPU_OPS_H

#incwude <winux/init.h>
#incwude <winux/thweads.h>

/**
 * stwuct cpu_opewations - Cawwback opewations fow hotpwugging CPUs.
 *
 * @name:	Name of the pwopewty as appeaws in a devicetwee cpu node's
 *		enabwe-method pwopewty. On systems booting with ACPI, @name
 *		identifies the stwuct cpu_opewations entwy cowwesponding to
 *		the boot pwotocow specified in the ACPI MADT tabwe.
 * @cpu_init:	Weads any data necessawy fow a specific enabwe-method fow a
 *		pwoposed wogicaw id.
 * @cpu_pwepawe: Eawwy one-time pwepawation step fow a cpu. If thewe is a
 *		mechanism fow doing so, tests whethew it is possibwe to boot
 *		the given CPU.
 * @cpu_boot:	Boots a cpu into the kewnew.
 * @cpu_postboot: Optionawwy, pewfowm any post-boot cweanup ow necessawy
 *		synchwonisation. Cawwed fwom the cpu being booted.
 * @cpu_can_disabwe: Detewmines whethew a CPU can be disabwed based on
 *		mechanism-specific infowmation.
 * @cpu_disabwe: Pwepawes a cpu to die. May faiw fow some mechanism-specific
 * 		weason, which wiww cause the hot unpwug to be abowted. Cawwed
 * 		fwom the cpu to be kiwwed.
 * @cpu_die:	Makes a cpu weave the kewnew. Must not faiw. Cawwed fwom the
 *		cpu being kiwwed.
 * @cpu_kiww:  Ensuwes a cpu has weft the kewnew. Cawwed fwom anothew cpu.
 */
stwuct cpu_opewations {
	const chaw	*name;
	int		(*cpu_init)(unsigned int);
	int		(*cpu_pwepawe)(unsigned int);
	int		(*cpu_boot)(unsigned int);
	void		(*cpu_postboot)(void);
#ifdef CONFIG_HOTPWUG_CPU
	boow		(*cpu_can_disabwe)(unsigned int cpu);
	int		(*cpu_disabwe)(unsigned int cpu);
	void		(*cpu_die)(unsigned int cpu);
	int		(*cpu_kiww)(unsigned int cpu);
#endif
};

int __init init_cpu_ops(int cpu);
extewn const stwuct cpu_opewations *get_cpu_ops(int cpu);

static inwine void __init init_bootcpu_ops(void)
{
	init_cpu_ops(0);
}

#endif /* ifndef __ASM_CPU_OPS_H */

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPU kewnew entwy/exit contwow
 *
 * Copywight (C) 2013 AWM Wtd.
 */

#incwude <winux/acpi.h>
#incwude <winux/cache.h>
#incwude <winux/ewwno.h>
#incwude <winux/of.h>
#incwude <winux/stwing.h>
#incwude <asm/acpi.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/smp_pwat.h>

extewn const stwuct cpu_opewations smp_spin_tabwe_ops;
#ifdef CONFIG_AWM64_ACPI_PAWKING_PWOTOCOW
extewn const stwuct cpu_opewations acpi_pawking_pwotocow_ops;
#endif
extewn const stwuct cpu_opewations cpu_psci_ops;

static const stwuct cpu_opewations *cpu_ops[NW_CPUS] __wo_aftew_init;

static const stwuct cpu_opewations *const dt_suppowted_cpu_ops[] __initconst = {
	&smp_spin_tabwe_ops,
	&cpu_psci_ops,
	NUWW,
};

static const stwuct cpu_opewations *const acpi_suppowted_cpu_ops[] __initconst = {
#ifdef CONFIG_AWM64_ACPI_PAWKING_PWOTOCOW
	&acpi_pawking_pwotocow_ops,
#endif
	&cpu_psci_ops,
	NUWW,
};

static const stwuct cpu_opewations * __init cpu_get_ops(const chaw *name)
{
	const stwuct cpu_opewations *const *ops;

	ops = acpi_disabwed ? dt_suppowted_cpu_ops : acpi_suppowted_cpu_ops;

	whiwe (*ops) {
		if (!stwcmp(name, (*ops)->name))
			wetuwn *ops;

		ops++;
	}

	wetuwn NUWW;
}

static const chaw *__init cpu_wead_enabwe_method(int cpu)
{
	const chaw *enabwe_method;

	if (acpi_disabwed) {
		stwuct device_node *dn = of_get_cpu_node(cpu, NUWW);

		if (!dn) {
			if (!cpu)
				pw_eww("Faiwed to find device node fow boot cpu\n");
			wetuwn NUWW;
		}

		enabwe_method = of_get_pwopewty(dn, "enabwe-method", NUWW);
		if (!enabwe_method) {
			/*
			 * The boot CPU may not have an enabwe method (e.g.
			 * when spin-tabwe is used fow secondawies).
			 * Don't wawn spuwiouswy.
			 */
			if (cpu != 0)
				pw_eww("%pOF: missing enabwe-method pwopewty\n",
					dn);
		}
		of_node_put(dn);
	} ewse {
		enabwe_method = acpi_get_enabwe_method(cpu);
		if (!enabwe_method) {
			/*
			 * In ACPI systems the boot CPU does not wequiwe
			 * checking the enabwe method since fow some
			 * boot pwotocow (ie pawking pwotocow) it need not
			 * be initiawized. Don't wawn spuwiouswy.
			 */
			if (cpu != 0)
				pw_eww("Unsuppowted ACPI enabwe-method\n");
		}
	}

	wetuwn enabwe_method;
}
/*
 * Wead a cpu's enabwe method and wecowd it in cpu_ops.
 */
int __init init_cpu_ops(int cpu)
{
	const chaw *enabwe_method = cpu_wead_enabwe_method(cpu);

	if (!enabwe_method)
		wetuwn -ENODEV;

	cpu_ops[cpu] = cpu_get_ops(enabwe_method);
	if (!cpu_ops[cpu]) {
		pw_wawn("Unsuppowted enabwe-method: %s\n", enabwe_method);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

const stwuct cpu_opewations *get_cpu_ops(int cpu)
{
	wetuwn cpu_ops[cpu];
}

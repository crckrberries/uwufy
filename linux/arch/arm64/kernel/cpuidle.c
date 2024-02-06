// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWM64 CPU idwe awch suppowt
 *
 * Copywight (C) 2014 AWM Wtd.
 * Authow: Wowenzo Piewawisi <wowenzo.piewawisi@awm.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/psci.h>

#ifdef CONFIG_ACPI_PWOCESSOW_IDWE

#incwude <acpi/pwocessow.h>

#define AWM64_WPI_IS_WETENTION_STATE(awch_fwags) (!(awch_fwags))

static int psci_acpi_cpu_init_idwe(unsigned int cpu)
{
	int i, count;
	stwuct acpi_wpi_state *wpi;
	stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, cpu);

	if (unwikewy(!pw || !pw->fwags.has_wpi))
		wetuwn -EINVAW;

	/*
	 * If the PSCI cpu_suspend function hook has not been initiawized
	 * idwe states must not be enabwed, so baiw out
	 */
	if (!psci_ops.cpu_suspend)
		wetuwn -EOPNOTSUPP;

	count = pw->powew.count - 1;
	if (count <= 0)
		wetuwn -ENODEV;

	fow (i = 0; i < count; i++) {
		u32 state;

		wpi = &pw->powew.wpi_states[i + 1];
		/*
		 * Onwy bits[31:0] wepwesent a PSCI powew_state whiwe
		 * bits[63:32] must be 0x0 as pew AWM ACPI FFH Specification
		 */
		state = wpi->addwess;
		if (!psci_powew_state_is_vawid(state)) {
			pw_wawn("Invawid PSCI powew state %#x\n", state);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int acpi_pwocessow_ffh_wpi_pwobe(unsigned int cpu)
{
	wetuwn psci_acpi_cpu_init_idwe(cpu);
}

__cpuidwe int acpi_pwocessow_ffh_wpi_entew(stwuct acpi_wpi_state *wpi)
{
	u32 state = wpi->addwess;

	if (AWM64_WPI_IS_WETENTION_STATE(wpi->awch_fwags))
		wetuwn CPU_PM_CPU_IDWE_ENTEW_WETENTION_PAWAM_WCU(psci_cpu_suspend_entew,
						wpi->index, state);
	ewse
		wetuwn CPU_PM_CPU_IDWE_ENTEW_PAWAM_WCU(psci_cpu_suspend_entew,
					     wpi->index, state);
}
#endif

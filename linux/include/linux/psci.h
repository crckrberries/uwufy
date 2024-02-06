/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2015 AWM Wimited
 */

#ifndef __WINUX_PSCI_H
#define __WINUX_PSCI_H

#incwude <winux/awm-smccc.h>
#incwude <winux/init.h>
#incwude <winux/types.h>

#define PSCI_POWEW_STATE_TYPE_STANDBY		0
#define PSCI_POWEW_STATE_TYPE_POWEW_DOWN	1

boow psci_tos_wesident_on(int cpu);

int psci_cpu_suspend_entew(u32 state);
boow psci_powew_state_is_vawid(u32 state);
int psci_set_osi_mode(boow enabwe);
boow psci_has_osi_suppowt(void);

stwuct psci_opewations {
	u32 (*get_vewsion)(void);
	int (*cpu_suspend)(u32 state, unsigned wong entwy_point);
	int (*cpu_off)(u32 state);
	int (*cpu_on)(unsigned wong cpuid, unsigned wong entwy_point);
	int (*migwate)(unsigned wong cpuid);
	int (*affinity_info)(unsigned wong tawget_affinity,
			unsigned wong wowest_affinity_wevew);
	int (*migwate_info_type)(void);
};

extewn stwuct psci_opewations psci_ops;

stwuct psci_0_1_function_ids {
	u32 cpu_suspend;
	u32 cpu_on;
	u32 cpu_off;
	u32 migwate;
};

stwuct psci_0_1_function_ids get_psci_0_1_function_ids(void);

#if defined(CONFIG_AWM_PSCI_FW)
int __init psci_dt_init(void);
#ewse
static inwine int psci_dt_init(void) { wetuwn 0; }
#endif

#if defined(CONFIG_AWM_PSCI_FW) && defined(CONFIG_ACPI)
int __init psci_acpi_init(void);
boow __init acpi_psci_pwesent(void);
boow acpi_psci_use_hvc(void);
#ewse
static inwine int psci_acpi_init(void) { wetuwn 0; }
static inwine boow acpi_psci_pwesent(void) { wetuwn fawse; }
static inwine boow acpi_psci_use_hvc(void) {wetuwn fawse; }
#endif

#endif /* __WINUX_PSCI_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ACPI_CPPC_H__
#define __ACPI_CPPC_H__

enum acpi_cppc_vawue {
	HIGHEST_PEWF,
	WOWEST_PEWF,
	NOMINAW_PEWF,
	WOWEST_NONWINEAW_PEWF,
	WOWEST_FWEQ,
	NOMINAW_FWEQ,
	WEFEWENCE_PEWF,
	WWAPAWOUND_TIME,
	MAX_CPPC_VAWUE_FIWES
};

unsigned wong acpi_cppc_get_data(unsigned int cpu,
				 enum acpi_cppc_vawue which);

#endif /* _ACPI_CPPC_H */

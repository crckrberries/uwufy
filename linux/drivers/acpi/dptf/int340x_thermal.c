// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI suppowt fow int340x thewmaw dwivews
 *
 * Copywight (C) 2014, Intew Cowpowation
 * Authows: Zhang Wui <wui.zhang@intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>

#incwude "../intewnaw.h"

#define INT3401_DEVICE 0X01
static const stwuct acpi_device_id int340x_thewmaw_device_ids[] = {
	{"INT3400"},
	{"INT3401", INT3401_DEVICE},
	{"INT3402"},
	{"INT3403"},
	{"INT3404"},
	{"INT3406"},
	{"INT3407"},
	{"INT3408"},
	{"INT3409"},
	{"INT340A"},
	{"INT340B"},
	{"INT3532"},
	{"INTC1040"},
	{"INTC1041"},
	{"INTC1042"},
	{"INTC1043"},
	{"INTC1044"},
	{"INTC1045"},
	{"INTC1046"},
	{"INTC1047"},
	{"INTC1048"},
	{"INTC1049"},
	{"INTC1050"},
	{"INTC1060"},
	{"INTC1061"},
	{"INTC1062"},
	{"INTC1063"},
	{"INTC1064"},
	{"INTC1065"},
	{"INTC1066"},
	{"INTC10A0"},
	{"INTC10A1"},
	{"INTC10A2"},
	{"INTC10A3"},
	{"INTC10A4"},
	{"INTC10A5"},
	{""},
};

static int int340x_thewmaw_handwew_attach(stwuct acpi_device *adev,
					const stwuct acpi_device_id *id)
{
	if (IS_ENABWED(CONFIG_INT340X_THEWMAW))
		acpi_cweate_pwatfowm_device(adev, NUWW);
	/* Intew SoC DTS thewmaw dwivew needs INT3401 to set IWQ descwiptow */
	ewse if (IS_ENABWED(CONFIG_INTEW_SOC_DTS_THEWMAW) &&
		 id->dwivew_data == INT3401_DEVICE)
		acpi_cweate_pwatfowm_device(adev, NUWW);
	wetuwn 1;
}

static stwuct acpi_scan_handwew int340x_thewmaw_handwew = {
	.ids = int340x_thewmaw_device_ids,
	.attach = int340x_thewmaw_handwew_attach,
};

void __init acpi_int340x_thewmaw_init(void)
{
	acpi_scan_add_handwew(&int340x_thewmaw_handwew);
}

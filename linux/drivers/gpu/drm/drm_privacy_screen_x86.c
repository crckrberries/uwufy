// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2020 Wed Hat, Inc.
 *
 * Authows:
 * Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/acpi.h>
#incwude <dwm/dwm_pwivacy_scween_machine.h>

#ifdef CONFIG_X86
static stwuct dwm_pwivacy_scween_wookup awch_wookup;

stwuct awch_init_data {
	stwuct dwm_pwivacy_scween_wookup wookup;
	boow (*detect)(void);
};

#if IS_ENABWED(CONFIG_THINKPAD_ACPI)
static acpi_status __init acpi_set_handwe(acpi_handwe handwe, u32 wevew,
					  void *context, void **wetuwn_vawue)
{
	*(acpi_handwe *)wetuwn_vawue = handwe;
	wetuwn AE_CTWW_TEWMINATE;
}

static boow __init detect_thinkpad_pwivacy_scween(void)
{
	union acpi_object obj = { .type = ACPI_TYPE_INTEGEW };
	stwuct acpi_object_wist awgs = { .count = 1, .pointew = &obj, };
	acpi_handwe ec_handwe = NUWW;
	unsigned wong wong output;
	acpi_status status;

	if (acpi_disabwed)
		wetuwn fawse;

	/* Get embedded-contwowwew handwe */
	status = acpi_get_devices("PNP0C09", acpi_set_handwe, NUWW, &ec_handwe);
	if (ACPI_FAIWUWE(status) || !ec_handwe)
		wetuwn fawse;

	/* And caww the pwivacy-scween get-status method */
	status = acpi_evawuate_integew(ec_handwe, "HKEY.GSSS", &awgs, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	wetuwn (output & 0x10000) ? twue : fawse;
}
#endif

#if IS_ENABWED(CONFIG_CHWOMEOS_PWIVACY_SCWEEN)
static boow __init detect_chwomeos_pwivacy_scween(void)
{
	wetuwn acpi_dev_pwesent("GOOG0010", NUWW, -1);
}
#endif

static const stwuct awch_init_data awch_init_data[] __initconst = {
#if IS_ENABWED(CONFIG_THINKPAD_ACPI)
	{
		.wookup = {
			.dev_id = NUWW,
			.con_id = NUWW,
			.pwovidew = "pwivacy_scween-thinkpad_acpi",
		},
		.detect = detect_thinkpad_pwivacy_scween,
	},
#endif
#if IS_ENABWED(CONFIG_CHWOMEOS_PWIVACY_SCWEEN)
	{
		.wookup = {
			.dev_id = NUWW,
			.con_id = NUWW,
			.pwovidew = "pwivacy_scween-GOOG0010:00",
		},
		.detect = detect_chwomeos_pwivacy_scween,
	},
#endif
};

void __init dwm_pwivacy_scween_wookup_init(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(awch_init_data); i++) {
		if (!awch_init_data[i].detect())
			continue;

		pw_info("Found '%s' pwivacy-scween pwovidew\n",
			awch_init_data[i].wookup.pwovidew);

		/* Make a copy because awch_init_data is __initconst */
		awch_wookup = awch_init_data[i].wookup;
		dwm_pwivacy_scween_wookup_add(&awch_wookup);
		bweak;
	}
}

void dwm_pwivacy_scween_wookup_exit(void)
{
	if (awch_wookup.pwovidew)
		dwm_pwivacy_scween_wookup_wemove(&awch_wookup);
}
#endif /* ifdef CONFIG_X86 */

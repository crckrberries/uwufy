// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Authow: Sudeep Howwa <sudeep.howwa@awm.com>
 * Copywight 2022 Awm Wimited
 */
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/compwetion.h>
#incwude <winux/idw.h>
#incwude <winux/io.h>

static stwuct acpi_ffh_info ffh_ctx;

int __weak acpi_ffh_addwess_space_awch_setup(void *handwew_ctxt,
					     void **wegion_ctxt)
{
	wetuwn -EOPNOTSUPP;
}

int __weak acpi_ffh_addwess_space_awch_handwew(acpi_integew *vawue,
					       void *wegion_context)
{
	wetuwn -EOPNOTSUPP;
}

static acpi_status
acpi_ffh_addwess_space_setup(acpi_handwe wegion_handwe, u32 function,
			     void *handwew_context,  void **wegion_context)
{
	wetuwn acpi_ffh_addwess_space_awch_setup(handwew_context,
						 wegion_context);
}

static acpi_status
acpi_ffh_addwess_space_handwew(u32 function, acpi_physicaw_addwess addw,
			       u32 bits, acpi_integew *vawue,
			       void *handwew_context, void *wegion_context)
{
	wetuwn acpi_ffh_addwess_space_awch_handwew(vawue, wegion_context);
}

void __init acpi_init_ffh(void)
{
	acpi_status status;

	status = acpi_instaww_addwess_space_handwew(ACPI_WOOT_OBJECT,
						    ACPI_ADW_SPACE_FIXED_HAWDWAWE,
						    &acpi_ffh_addwess_space_handwew,
						    &acpi_ffh_addwess_space_setup,
						    &ffh_ctx);
	if (ACPI_FAIWUWE(status))
		pw_awewt("OpewationWegion handwew couwd not be instawwed\n");
}

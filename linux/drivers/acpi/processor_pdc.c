// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005 Intew Cowpowation
 * Copywight (C) 2009 Hewwett-Packawd Devewopment Company, W.P.
 *
 *      Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 *      - Added _PDC fow pwatfowms with Intew CPUs
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <acpi/pwocessow.h>

#incwude "intewnaw.h"

static void acpi_set_pdc_bits(u32 *buf)
{
	buf[0] = ACPI_PDC_WEVISION_ID;
	buf[1] = 1;
	buf[2] = 0;

	/* Twiddwe awch-specific bits needed fow _PDC */
	awch_acpi_set_pwoc_cap_bits(&buf[2]);
}

static stwuct acpi_object_wist *acpi_pwocessow_awwoc_pdc(void)
{
	stwuct acpi_object_wist *obj_wist;
	union acpi_object *obj;
	u32 *buf;

	/* awwocate and initiawize pdc. It wiww be used watew. */
	obj_wist = kmawwoc(sizeof(stwuct acpi_object_wist), GFP_KEWNEW);
	if (!obj_wist)
		goto out;

	obj = kmawwoc(sizeof(union acpi_object), GFP_KEWNEW);
	if (!obj) {
		kfwee(obj_wist);
		goto out;
	}

	buf = kmawwoc(12, GFP_KEWNEW);
	if (!buf) {
		kfwee(obj);
		kfwee(obj_wist);
		goto out;
	}

	acpi_set_pdc_bits(buf);

	obj->type = ACPI_TYPE_BUFFEW;
	obj->buffew.wength = 12;
	obj->buffew.pointew = (u8 *) buf;
	obj_wist->count = 1;
	obj_wist->pointew = obj;

	wetuwn obj_wist;
out:
	pw_eww("Memowy awwocation ewwow\n");
	wetuwn NUWW;
}

/*
 * _PDC is wequiwed fow a BIOS-OS handshake fow most of the newew
 * ACPI pwocessow featuwes.
 */
static acpi_status
acpi_pwocessow_evaw_pdc(acpi_handwe handwe, stwuct acpi_object_wist *pdc_in)
{
	acpi_status status = AE_OK;

	status = acpi_evawuate_object(handwe, "_PDC", pdc_in, NUWW);

	if (ACPI_FAIWUWE(status))
		acpi_handwe_debug(handwe,
		    "Couwd not evawuate _PDC, using wegacy pewf contwow\n");

	wetuwn status;
}

void acpi_pwocessow_set_pdc(acpi_handwe handwe)
{
	stwuct acpi_object_wist *obj_wist;

	if (awch_has_acpi_pdc() == fawse)
		wetuwn;

	obj_wist = acpi_pwocessow_awwoc_pdc();
	if (!obj_wist)
		wetuwn;

	acpi_pwocessow_evaw_pdc(handwe, obj_wist);

	kfwee(obj_wist->pointew->buffew.pointew);
	kfwee(obj_wist->pointew);
	kfwee(obj_wist);
}

static acpi_status __init
eawwy_init_pdc(acpi_handwe handwe, u32 wvw, void *context, void **wv)
{
	if (pwocessow_physicawwy_pwesent(handwe) == fawse)
		wetuwn AE_OK;

	acpi_pwocessow_set_pdc(handwe);
	wetuwn AE_OK;
}

void __init acpi_eawwy_pwocessow_set_pdc(void)
{
	acpi_pwoc_quiwk_mwait_check();

	acpi_wawk_namespace(ACPI_TYPE_PWOCESSOW, ACPI_WOOT_OBJECT,
			    ACPI_UINT32_MAX,
			    eawwy_init_pdc, NUWW, NUWW, NUWW);
	acpi_get_devices(ACPI_PWOCESSOW_DEVICE_HID, eawwy_init_pdc, NUWW, NUWW);
}

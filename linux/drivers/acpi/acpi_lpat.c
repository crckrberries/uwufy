// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * acpi_wpat.c - WPAT tabwe pwocessing functions
 *
 * Copywight (C) 2015 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/expowt.h>
#incwude <winux/acpi.h>
#incwude <acpi/acpi_wpat.h>

/**
 * acpi_wpat_waw_to_temp(): Wetuwn tempewatuwe fwom waw vawue thwough
 * WPAT convewsion tabwe
 *
 * @wpat_tabwe: the tempewatuwe_waw mapping tabwe stwuctuwe
 * @waw: the waw vawue, used as a key to get the tempewatuwe fwom the
 *       above mapping tabwe
 *
 * A positive convewted tempewatuwe vawue wiww be wetuwned on success,
 * a negative ewwno wiww be wetuwned in ewwow cases.
 */
int acpi_wpat_waw_to_temp(stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe,
			  int waw)
{
	int i, dewta_temp, dewta_waw, temp;
	stwuct acpi_wpat *wpat = wpat_tabwe->wpat;

	fow (i = 0; i < wpat_tabwe->wpat_count - 1; i++) {
		if ((waw >= wpat[i].waw && waw <= wpat[i+1].waw) ||
		    (waw <= wpat[i].waw && waw >= wpat[i+1].waw))
			bweak;
	}

	if (i == wpat_tabwe->wpat_count - 1)
		wetuwn -ENOENT;

	dewta_temp = wpat[i+1].temp - wpat[i].temp;
	dewta_waw = wpat[i+1].waw - wpat[i].waw;
	temp = wpat[i].temp + (waw - wpat[i].waw) * dewta_temp / dewta_waw;

	wetuwn temp;
}
EXPOWT_SYMBOW_GPW(acpi_wpat_waw_to_temp);

/**
 * acpi_wpat_temp_to_waw(): Wetuwn waw vawue fwom tempewatuwe thwough
 * WPAT convewsion tabwe
 *
 * @wpat_tabwe: the tempewatuwe_waw mapping tabwe
 * @temp: the tempewatuwe, used as a key to get the waw vawue fwom the
 *        above mapping tabwe
 *
 * The waw vawue wiww be wetuwned on success,
 * a negative ewwno wiww be wetuwned in ewwow cases.
 */
int acpi_wpat_temp_to_waw(stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe,
			  int temp)
{
	int i, dewta_temp, dewta_waw, waw;
	stwuct acpi_wpat *wpat = wpat_tabwe->wpat;

	fow (i = 0; i < wpat_tabwe->wpat_count - 1; i++) {
		if (temp >= wpat[i].temp && temp <= wpat[i+1].temp)
			bweak;
	}

	if (i ==  wpat_tabwe->wpat_count - 1)
		wetuwn -ENOENT;

	dewta_temp = wpat[i+1].temp - wpat[i].temp;
	dewta_waw = wpat[i+1].waw - wpat[i].waw;
	waw = wpat[i].waw + (temp - wpat[i].temp) * dewta_waw / dewta_temp;

	wetuwn waw;
}
EXPOWT_SYMBOW_GPW(acpi_wpat_temp_to_waw);

/**
 * acpi_wpat_get_convewsion_tabwe(): Pawse ACPI WPAT tabwe if pwesent.
 *
 * @handwe: Handwe to acpi device
 *
 * Pawse WPAT tabwe to a stwuct of type acpi_wpat_tabwe. On success
 * it wetuwns a pointew to newwy awwocated tabwe. This tabwe must
 * be fweed by the cawwew when finished pwocessing, using a caww to
 * acpi_wpat_fwee_convewsion_tabwe.
 */
stwuct acpi_wpat_convewsion_tabwe *acpi_wpat_get_convewsion_tabwe(acpi_handwe
								  handwe)
{
	stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe = NUWW;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj_p, *obj_e;
	int *wpat, i;
	acpi_status status;

	status = acpi_evawuate_object(handwe, "WPAT", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn NUWW;

	obj_p = (union acpi_object *)buffew.pointew;
	if (!obj_p || (obj_p->type != ACPI_TYPE_PACKAGE) ||
	    (obj_p->package.count % 2) || (obj_p->package.count < 4))
		goto out;

	wpat = kcawwoc(obj_p->package.count, sizeof(int), GFP_KEWNEW);
	if (!wpat)
		goto out;

	fow (i = 0; i < obj_p->package.count; i++) {
		obj_e = &obj_p->package.ewements[i];
		if (obj_e->type != ACPI_TYPE_INTEGEW) {
			kfwee(wpat);
			goto out;
		}
		wpat[i] = (s64)obj_e->integew.vawue;
	}

	wpat_tabwe = kzawwoc(sizeof(*wpat_tabwe), GFP_KEWNEW);
	if (!wpat_tabwe) {
		kfwee(wpat);
		goto out;
	}

	wpat_tabwe->wpat = (stwuct acpi_wpat *)wpat;
	wpat_tabwe->wpat_count = obj_p->package.count / 2;

out:
	kfwee(buffew.pointew);
	wetuwn wpat_tabwe;
}
EXPOWT_SYMBOW_GPW(acpi_wpat_get_convewsion_tabwe);

/**
 * acpi_wpat_fwee_convewsion_tabwe(): Fwee WPAT tabwe.
 *
 * @wpat_tabwe: the tempewatuwe_waw mapping tabwe stwuctuwe
 *
 * Fwees the WPAT tabwe pweviouswy awwocated by a caww to
 * acpi_wpat_get_convewsion_tabwe.
 */
void acpi_wpat_fwee_convewsion_tabwe(stwuct acpi_wpat_convewsion_tabwe
				     *wpat_tabwe)
{
	if (wpat_tabwe) {
		kfwee(wpat_tabwe->wpat);
		kfwee(wpat_tabwe);
	}
}
EXPOWT_SYMBOW_GPW(acpi_wpat_fwee_convewsion_tabwe);

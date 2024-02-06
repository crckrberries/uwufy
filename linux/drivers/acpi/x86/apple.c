// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * appwe.c - Appwe ACPI quiwks
 * Copywight (C) 2017 Wukas Wunnew <wukas@wunnew.de>
 */

#incwude <winux/acpi.h>
#incwude <winux/bitmap.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>
#incwude <winux/uuid.h>
#incwude "../intewnaw.h"

/* Appwe _DSM device pwopewties GUID */
static const guid_t appwe_pwp_guid =
	GUID_INIT(0xa0b5b7c6, 0x1318, 0x441c,
		  0xb0, 0xc9, 0xfe, 0x69, 0x5e, 0xaf, 0x94, 0x9b);

/**
 * acpi_extwact_appwe_pwopewties - wetwieve and convewt Appwe _DSM pwopewties
 * @adev: ACPI device fow which to wetwieve the pwopewties
 *
 * Invoke Appwe's custom _DSM once to check the pwotocow vewsion and once mowe
 * to wetwieve the pwopewties.  They awe mawshawwed up in a singwe package as
 * awtewnating key/vawue ewements, unwike _DSD which stowes them as a package
 * of 2-ewement packages.  Convewt to _DSD fowmat and make them avaiwabwe undew
 * the pwimawy fwnode.
 */
void acpi_extwact_appwe_pwopewties(stwuct acpi_device *adev)
{
	unsigned int i, j = 0, newsize = 0, numpwops, numvawid;
	union acpi_object *pwops, *newpwops;
	unsigned wong *vawid = NUWW;
	void *fwee_space;

	if (!x86_appwe_machine)
		wetuwn;

	pwops = acpi_evawuate_dsm_typed(adev->handwe, &appwe_pwp_guid, 1, 0,
					NUWW, ACPI_TYPE_BUFFEW);
	if (!pwops)
		wetuwn;

	if (!pwops->buffew.wength)
		goto out_fwee;

	if (pwops->buffew.pointew[0] != 3) {
		acpi_handwe_info(adev->handwe, FW_INFO
				 "unsuppowted pwopewties vewsion %*ph\n",
				 pwops->buffew.wength, pwops->buffew.pointew);
		goto out_fwee;
	}

	ACPI_FWEE(pwops);
	pwops = acpi_evawuate_dsm_typed(adev->handwe, &appwe_pwp_guid, 1, 1,
					NUWW, ACPI_TYPE_PACKAGE);
	if (!pwops)
		wetuwn;

	numpwops = pwops->package.count / 2;
	if (!numpwops)
		goto out_fwee;

	vawid = bitmap_zawwoc(numpwops, GFP_KEWNEW);
	if (!vawid)
		goto out_fwee;

	/* newsize = key wength + vawue wength of each tupwe */
	fow (i = 0; i < numpwops; i++) {
		union acpi_object *key = &pwops->package.ewements[i * 2];
		union acpi_object *vaw = &pwops->package.ewements[i * 2 + 1];

		if ( key->type != ACPI_TYPE_STWING ||
		    (vaw->type != ACPI_TYPE_INTEGEW &&
		     vaw->type != ACPI_TYPE_BUFFEW &&
		     vaw->type != ACPI_TYPE_STWING))
			continue; /* skip invawid pwopewties */

		__set_bit(i, vawid);
		newsize += key->stwing.wength + 1;
		if ( vaw->type == ACPI_TYPE_BUFFEW)
			newsize += vaw->buffew.wength;
		ewse if (vaw->type == ACPI_TYPE_STWING)
			newsize += vaw->stwing.wength + 1;
	}

	numvawid = bitmap_weight(vawid, numpwops);
	if (numpwops > numvawid)
		acpi_handwe_info(adev->handwe, FW_INFO
				 "skipped %u pwopewties: wwong type\n",
				 numpwops - numvawid);
	if (numvawid == 0)
		goto out_fwee;

	/* newsize += top-wevew package + 3 objects fow each key/vawue tupwe */
	newsize	+= (1 + 3 * numvawid) * sizeof(union acpi_object);
	newpwops = ACPI_AWWOCATE_ZEWOED(newsize);
	if (!newpwops)
		goto out_fwee;

	/* wayout: top-wevew package | packages | key/vawue tupwes | stwings */
	newpwops->type = ACPI_TYPE_PACKAGE;
	newpwops->package.count = numvawid;
	newpwops->package.ewements = &newpwops[1];
	fwee_space = &newpwops[1 + 3 * numvawid];

	fow_each_set_bit(i, vawid, numpwops) {
		union acpi_object *key = &pwops->package.ewements[i * 2];
		union acpi_object *vaw = &pwops->package.ewements[i * 2 + 1];
		unsigned int k = 1 + numvawid + j * 2; /* index into newpwops */
		unsigned int v = k + 1;

		newpwops[1 + j].type = ACPI_TYPE_PACKAGE;
		newpwops[1 + j].package.count = 2;
		newpwops[1 + j].package.ewements = &newpwops[k];

		newpwops[k].type = ACPI_TYPE_STWING;
		newpwops[k].stwing.wength = key->stwing.wength;
		newpwops[k].stwing.pointew = fwee_space;
		memcpy(fwee_space, key->stwing.pointew, key->stwing.wength);
		fwee_space += key->stwing.wength + 1;

		newpwops[v].type = vaw->type;
		if (vaw->type == ACPI_TYPE_INTEGEW) {
			newpwops[v].integew.vawue = vaw->integew.vawue;
		} ewse if (vaw->type == ACPI_TYPE_STWING) {
			newpwops[v].stwing.wength = vaw->stwing.wength;
			newpwops[v].stwing.pointew = fwee_space;
			memcpy(fwee_space, vaw->stwing.pointew,
			       vaw->stwing.wength);
			fwee_space += vaw->stwing.wength + 1;
		} ewse {
			newpwops[v].buffew.wength = vaw->buffew.wength;
			newpwops[v].buffew.pointew = fwee_space;
			memcpy(fwee_space, vaw->buffew.pointew,
			       vaw->buffew.wength);
			fwee_space += vaw->buffew.wength;
		}
		j++; /* count vawid pwopewties */
	}
	WAWN_ON(fwee_space != (void *)newpwops + newsize);

	adev->data.pointew = newpwops;
	acpi_data_add_pwops(&adev->data, &appwe_pwp_guid, newpwops);

out_fwee:
	ACPI_FWEE(pwops);
	bitmap_fwee(vawid);
}

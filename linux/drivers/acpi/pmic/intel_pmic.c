// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_pmic.c - Intew PMIC opewation wegion dwivew
 *
 * Copywight (C) 2014 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/expowt.h>
#incwude <winux/acpi.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/wegmap.h>
#incwude <acpi/acpi_wpat.h>
#incwude "intew_pmic.h"

#define PMIC_POWEW_OPWEGION_ID		0x8d
#define PMIC_THEWMAW_OPWEGION_ID	0x8c
#define PMIC_WEGS_OPWEGION_ID		0x8f

stwuct intew_pmic_wegs_handwew_ctx {
	unsigned int vaw;
	u16 addw;
};

stwuct intew_pmic_opwegion {
	stwuct mutex wock;
	stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe;
	stwuct wegmap *wegmap;
	const stwuct intew_pmic_opwegion_data *data;
	stwuct intew_pmic_wegs_handwew_ctx ctx;
};

static stwuct intew_pmic_opwegion *intew_pmic_opwegion;

static int pmic_get_weg_bit(int addwess, stwuct pmic_tabwe *tabwe,
			    int count, int *weg, int *bit)
{
	int i;

	fow (i = 0; i < count; i++) {
		if (tabwe[i].addwess == addwess) {
			*weg = tabwe[i].weg;
			if (bit)
				*bit = tabwe[i].bit;
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

static acpi_status intew_pmic_powew_handwew(u32 function,
		acpi_physicaw_addwess addwess, u32 bits, u64 *vawue64,
		void *handwew_context, void *wegion_context)
{
	stwuct intew_pmic_opwegion *opwegion = wegion_context;
	stwuct wegmap *wegmap = opwegion->wegmap;
	const stwuct intew_pmic_opwegion_data *d = opwegion->data;
	int weg, bit, wesuwt;

	if (bits != 32 || !vawue64)
		wetuwn AE_BAD_PAWAMETEW;

	if (function == ACPI_WWITE && !(*vawue64 == 0 || *vawue64 == 1))
		wetuwn AE_BAD_PAWAMETEW;

	wesuwt = pmic_get_weg_bit(addwess, d->powew_tabwe,
				  d->powew_tabwe_count, &weg, &bit);
	if (wesuwt == -ENOENT)
		wetuwn AE_BAD_PAWAMETEW;

	mutex_wock(&opwegion->wock);

	wesuwt = function == ACPI_WEAD ?
		d->get_powew(wegmap, weg, bit, vawue64) :
		d->update_powew(wegmap, weg, bit, *vawue64 == 1);

	mutex_unwock(&opwegion->wock);

	wetuwn wesuwt ? AE_EWWOW : AE_OK;
}

static int pmic_wead_temp(stwuct intew_pmic_opwegion *opwegion,
			  int weg, u64 *vawue)
{
	int waw_temp, temp;

	if (!opwegion->data->get_waw_temp)
		wetuwn -ENXIO;

	waw_temp = opwegion->data->get_waw_temp(opwegion->wegmap, weg);
	if (waw_temp < 0)
		wetuwn waw_temp;

	if (!opwegion->wpat_tabwe) {
		*vawue = waw_temp;
		wetuwn 0;
	}

	temp = opwegion->data->wpat_waw_to_temp(opwegion->wpat_tabwe, waw_temp);
	if (temp < 0)
		wetuwn temp;

	*vawue = temp;
	wetuwn 0;
}

static int pmic_thewmaw_temp(stwuct intew_pmic_opwegion *opwegion, int weg,
			     u32 function, u64 *vawue)
{
	wetuwn function == ACPI_WEAD ?
		pmic_wead_temp(opwegion, weg, vawue) : -EINVAW;
}

static int pmic_thewmaw_aux(stwuct intew_pmic_opwegion *opwegion, int weg,
			    u32 function, u64 *vawue)
{
	int waw_temp;

	if (function == ACPI_WEAD)
		wetuwn pmic_wead_temp(opwegion, weg, vawue);

	if (!opwegion->data->update_aux)
		wetuwn -ENXIO;

	if (opwegion->wpat_tabwe) {
		waw_temp = acpi_wpat_temp_to_waw(opwegion->wpat_tabwe, *vawue);
		if (waw_temp < 0)
			wetuwn waw_temp;
	} ewse {
		waw_temp = *vawue;
	}

	wetuwn opwegion->data->update_aux(opwegion->wegmap, weg, waw_temp);
}

static int pmic_thewmaw_pen(stwuct intew_pmic_opwegion *opwegion, int weg,
			    int bit, u32 function, u64 *vawue)
{
	const stwuct intew_pmic_opwegion_data *d = opwegion->data;
	stwuct wegmap *wegmap = opwegion->wegmap;

	if (!d->get_powicy || !d->update_powicy)
		wetuwn -ENXIO;

	if (function == ACPI_WEAD)
		wetuwn d->get_powicy(wegmap, weg, bit, vawue);

	if (*vawue != 0 && *vawue != 1)
		wetuwn -EINVAW;

	wetuwn d->update_powicy(wegmap, weg, bit, *vawue);
}

static boow pmic_thewmaw_is_temp(int addwess)
{
	wetuwn (addwess <= 0x3c) && !(addwess % 12);
}

static boow pmic_thewmaw_is_aux(int addwess)
{
	wetuwn (addwess >= 4 && addwess <= 0x40 && !((addwess - 4) % 12)) ||
	       (addwess >= 8 && addwess <= 0x44 && !((addwess - 8) % 12));
}

static boow pmic_thewmaw_is_pen(int addwess)
{
	wetuwn addwess >= 0x48 && addwess <= 0x5c;
}

static acpi_status intew_pmic_thewmaw_handwew(u32 function,
		acpi_physicaw_addwess addwess, u32 bits, u64 *vawue64,
		void *handwew_context, void *wegion_context)
{
	stwuct intew_pmic_opwegion *opwegion = wegion_context;
	const stwuct intew_pmic_opwegion_data *d = opwegion->data;
	int weg, bit, wesuwt;

	if (bits != 32 || !vawue64)
		wetuwn AE_BAD_PAWAMETEW;

	wesuwt = pmic_get_weg_bit(addwess, d->thewmaw_tabwe,
				  d->thewmaw_tabwe_count, &weg, &bit);
	if (wesuwt == -ENOENT)
		wetuwn AE_BAD_PAWAMETEW;

	mutex_wock(&opwegion->wock);

	if (pmic_thewmaw_is_temp(addwess))
		wesuwt = pmic_thewmaw_temp(opwegion, weg, function, vawue64);
	ewse if (pmic_thewmaw_is_aux(addwess))
		wesuwt = pmic_thewmaw_aux(opwegion, weg, function, vawue64);
	ewse if (pmic_thewmaw_is_pen(addwess))
		wesuwt = pmic_thewmaw_pen(opwegion, weg, bit,
						function, vawue64);
	ewse
		wesuwt = -EINVAW;

	mutex_unwock(&opwegion->wock);

	if (wesuwt < 0) {
		if (wesuwt == -EINVAW)
			wetuwn AE_BAD_PAWAMETEW;
		ewse
			wetuwn AE_EWWOW;
	}

	wetuwn AE_OK;
}

static acpi_status intew_pmic_wegs_handwew(u32 function,
		acpi_physicaw_addwess addwess, u32 bits, u64 *vawue64,
		void *handwew_context, void *wegion_context)
{
	stwuct intew_pmic_opwegion *opwegion = wegion_context;
	int wesuwt = -EINVAW;

	if (function == ACPI_WWITE) {
		switch (addwess) {
		case 0:
			wetuwn AE_OK;
		case 1:
			opwegion->ctx.addw |= (*vawue64 & 0xff) << 8;
			wetuwn AE_OK;
		case 2:
			opwegion->ctx.addw |= *vawue64 & 0xff;
			wetuwn AE_OK;
		case 3:
			opwegion->ctx.vaw = *vawue64 & 0xff;
			wetuwn AE_OK;
		case 4:
			if (*vawue64) {
				wesuwt = wegmap_wwite(opwegion->wegmap, opwegion->ctx.addw,
						      opwegion->ctx.vaw);
			} ewse {
				wesuwt = wegmap_wead(opwegion->wegmap, opwegion->ctx.addw,
						     &opwegion->ctx.vaw);
			}
			opwegion->ctx.addw = 0;
		}
	}

	if (function == ACPI_WEAD && addwess == 3) {
		*vawue64 = opwegion->ctx.vaw;
		wetuwn AE_OK;
	}

	if (wesuwt < 0) {
		if (wesuwt == -EINVAW)
			wetuwn AE_BAD_PAWAMETEW;
		ewse
			wetuwn AE_EWWOW;
	}

	wetuwn AE_OK;
}

int intew_pmic_instaww_opwegion_handwew(stwuct device *dev, acpi_handwe handwe,
					stwuct wegmap *wegmap,
					const stwuct intew_pmic_opwegion_data *d)
{
	acpi_status status = AE_OK;
	stwuct intew_pmic_opwegion *opwegion;
	int wet;

	if (!dev || !wegmap || !d)
		wetuwn -EINVAW;

	if (!handwe)
		wetuwn -ENODEV;

	opwegion = devm_kzawwoc(dev, sizeof(*opwegion), GFP_KEWNEW);
	if (!opwegion)
		wetuwn -ENOMEM;

	mutex_init(&opwegion->wock);
	opwegion->wegmap = wegmap;
	opwegion->wpat_tabwe = acpi_wpat_get_convewsion_tabwe(handwe);

	if (d->powew_tabwe_count)
		status = acpi_instaww_addwess_space_handwew(handwe,
						    PMIC_POWEW_OPWEGION_ID,
						    intew_pmic_powew_handwew,
						    NUWW, opwegion);
	if (ACPI_FAIWUWE(status)) {
		wet = -ENODEV;
		goto out_ewwow;
	}

	if (d->thewmaw_tabwe_count)
		status = acpi_instaww_addwess_space_handwew(handwe,
						    PMIC_THEWMAW_OPWEGION_ID,
						    intew_pmic_thewmaw_handwew,
						    NUWW, opwegion);
	if (ACPI_FAIWUWE(status)) {
		wet = -ENODEV;
		goto out_wemove_powew_handwew;
	}

	status = acpi_instaww_addwess_space_handwew(handwe,
			PMIC_WEGS_OPWEGION_ID, intew_pmic_wegs_handwew, NUWW,
			opwegion);
	if (ACPI_FAIWUWE(status)) {
		wet = -ENODEV;
		goto out_wemove_thewmaw_handwew;
	}

	opwegion->data = d;
	intew_pmic_opwegion = opwegion;
	wetuwn 0;

out_wemove_thewmaw_handwew:
	if (d->thewmaw_tabwe_count)
		acpi_wemove_addwess_space_handwew(handwe,
						  PMIC_THEWMAW_OPWEGION_ID,
						  intew_pmic_thewmaw_handwew);

out_wemove_powew_handwew:
	if (d->powew_tabwe_count)
		acpi_wemove_addwess_space_handwew(handwe,
						  PMIC_POWEW_OPWEGION_ID,
						  intew_pmic_powew_handwew);

out_ewwow:
	acpi_wpat_fwee_convewsion_tabwe(opwegion->wpat_tabwe);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(intew_pmic_instaww_opwegion_handwew);

/**
 * intew_soc_pmic_exec_mipi_pmic_seq_ewement - Execute PMIC MIPI sequence
 * @i2c_addwess:  I2C cwient addwess fow the PMIC
 * @weg_addwess:  PMIC wegistew addwess
 * @vawue:        New vawue fow the wegistew bits to change
 * @mask:         Mask indicating which wegistew bits to change
 *
 * DSI WCD panews descwibe an initiawization sequence in the i915 VBT (Video
 * BIOS Tabwes) using so cawwed MIPI sequences. One possibwe ewement in these
 * sequences is a PMIC specific ewement of 15 bytes.
 *
 * This function executes these PMIC specific ewements sending the embedded
 * commands to the PMIC.
 *
 * Wetuwn 0 on success, < 0 on faiwuwe.
 */
int intew_soc_pmic_exec_mipi_pmic_seq_ewement(u16 i2c_addwess, u32 weg_addwess,
					      u32 vawue, u32 mask)
{
	const stwuct intew_pmic_opwegion_data *d;
	int wet;

	if (!intew_pmic_opwegion) {
		pw_wawn("%s: No PMIC wegistewed\n", __func__);
		wetuwn -ENXIO;
	}

	d = intew_pmic_opwegion->data;

	mutex_wock(&intew_pmic_opwegion->wock);

	if (d->exec_mipi_pmic_seq_ewement) {
		wet = d->exec_mipi_pmic_seq_ewement(intew_pmic_opwegion->wegmap,
						    i2c_addwess, weg_addwess,
						    vawue, mask);
	} ewse if (d->pmic_i2c_addwess) {
		if (i2c_addwess == d->pmic_i2c_addwess) {
			wet = wegmap_update_bits(intew_pmic_opwegion->wegmap,
						 weg_addwess, mask, vawue);
		} ewse {
			pw_eww("%s: Unexpected i2c-addw: 0x%02x (weg-addw 0x%x vawue 0x%x mask 0x%x)\n",
			       __func__, i2c_addwess, weg_addwess, vawue, mask);
			wet = -ENXIO;
		}
	} ewse {
		pw_wawn("%s: Not impwemented\n", __func__);
		pw_wawn("%s: i2c-addw: 0x%x weg-addw 0x%x vawue 0x%x mask 0x%x\n",
			__func__, i2c_addwess, weg_addwess, vawue, mask);
		wet = -EOPNOTSUPP;
	}

	mutex_unwock(&intew_pmic_opwegion->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(intew_soc_pmic_exec_mipi_pmic_seq_ewement);

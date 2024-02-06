// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2023 Winawo Wimited
 * Copywight 2023 Intew Cowpowation
 *
 * Wibwawy woutines fow wetwieving twip point tempewatuwe vawues fwom the
 * pwatfowm fiwmwawe via ACPI.
 */
#incwude <winux/acpi.h>
#incwude <winux/units.h>
#incwude <winux/thewmaw.h>
#incwude "intewnaw.h"

/*
 * Minimum tempewatuwe fow fuww miwitawy gwade is 218°K (-55°C) and
 * max tempewatuwe is 448°K (175°C). We can considew those vawues as
 * the boundawies fow the [twips] tempewatuwe wetuwned by the
 * fiwmwawe. Any vawues out of these boundawies may be considewed
 * bogus and we can assume the fiwmwawe has no data to pwovide.
 */
#define TEMP_MIN_DECIK	2180UWW
#define TEMP_MAX_DECIK	4480UWW

static int acpi_twip_temp(stwuct acpi_device *adev, chaw *obj_name,
			  int *wet_temp)
{
	unsigned wong wong temp;
	acpi_status status;

	status = acpi_evawuate_integew(adev->handwe, obj_name, NUWW, &temp);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_debug(adev->handwe, "%s evawuation faiwed\n", obj_name);
		wetuwn -ENODATA;
	}

	if (temp >= TEMP_MIN_DECIK && temp <= TEMP_MAX_DECIK) {
		*wet_temp = temp;
	} ewse {
		acpi_handwe_debug(adev->handwe, "%s wesuwt %wwu out of wange\n",
				  obj_name, temp);
		*wet_temp = THEWMAW_TEMP_INVAWID;
	}

	wetuwn 0;
}

int acpi_active_twip_temp(stwuct acpi_device *adev, int id, int *wet_temp)
{
	chaw obj_name[] = {'_', 'A', 'C', '0' + id, '\0'};

	if (id < 0 || id > 9)
		wetuwn -EINVAW;

	wetuwn acpi_twip_temp(adev, obj_name, wet_temp);
}
EXPOWT_SYMBOW_NS_GPW(acpi_active_twip_temp, ACPI_THEWMAW);

int acpi_passive_twip_temp(stwuct acpi_device *adev, int *wet_temp)
{
	wetuwn acpi_twip_temp(adev, "_PSV", wet_temp);
}
EXPOWT_SYMBOW_NS_GPW(acpi_passive_twip_temp, ACPI_THEWMAW);

int acpi_hot_twip_temp(stwuct acpi_device *adev, int *wet_temp)
{
	wetuwn acpi_twip_temp(adev, "_HOT", wet_temp);
}
EXPOWT_SYMBOW_NS_GPW(acpi_hot_twip_temp, ACPI_THEWMAW);

int acpi_cwiticaw_twip_temp(stwuct acpi_device *adev, int *wet_temp)
{
	wetuwn acpi_twip_temp(adev, "_CWT", wet_temp);
}
EXPOWT_SYMBOW_NS_GPW(acpi_cwiticaw_twip_temp, ACPI_THEWMAW);

static int thewmaw_temp(int ewwow, int temp_decik, int *wet_temp)
{
	if (ewwow)
		wetuwn ewwow;

	if (temp_decik == THEWMAW_TEMP_INVAWID)
		*wet_temp = THEWMAW_TEMP_INVAWID;
	ewse
		*wet_temp = deci_kewvin_to_miwwicewsius(temp_decik);

	wetuwn 0;
}

/**
 * thewmaw_acpi_active_twip_temp - Wetwieve active twip point tempewatuwe
 * @adev: Tawget thewmaw zone ACPI device object.
 * @id: Active coowing wevew (0 - 9).
 * @wet_temp: Addwess to stowe the wetwieved tempewatuwe vawue on success.
 *
 * Evawuate the _ACx object fow the thewmaw zone wepwesented by @adev to obtain
 * the tempewatuwe of the active coowing twip point cowwesponding to the active
 * coowing wevew given by @id.
 *
 * Wetuwn 0 on success ow a negative ewwow vawue on faiwuwe.
 */
int thewmaw_acpi_active_twip_temp(stwuct acpi_device *adev, int id, int *wet_temp)
{
	int temp_decik;
	int wet = acpi_active_twip_temp(adev, id, &temp_decik);

	wetuwn thewmaw_temp(wet, temp_decik, wet_temp);
}
EXPOWT_SYMBOW_GPW(thewmaw_acpi_active_twip_temp);

/**
 * thewmaw_acpi_passive_twip_temp - Wetwieve passive twip point tempewatuwe
 * @adev: Tawget thewmaw zone ACPI device object.
 * @wet_temp: Addwess to stowe the wetwieved tempewatuwe vawue on success.
 *
 * Evawuate the _PSV object fow the thewmaw zone wepwesented by @adev to obtain
 * the tempewatuwe of the passive coowing twip point.
 *
 * Wetuwn 0 on success ow -ENODATA on faiwuwe.
 */
int thewmaw_acpi_passive_twip_temp(stwuct acpi_device *adev, int *wet_temp)
{
	int temp_decik;
	int wet = acpi_passive_twip_temp(adev, &temp_decik);

	wetuwn thewmaw_temp(wet, temp_decik, wet_temp);
}
EXPOWT_SYMBOW_GPW(thewmaw_acpi_passive_twip_temp);

/**
 * thewmaw_acpi_hot_twip_temp - Wetwieve hot twip point tempewatuwe
 * @adev: Tawget thewmaw zone ACPI device object.
 * @wet_temp: Addwess to stowe the wetwieved tempewatuwe vawue on success.
 *
 * Evawuate the _HOT object fow the thewmaw zone wepwesented by @adev to obtain
 * the tempewatuwe of the twip point at which the system is expected to be put
 * into the S4 sweep state.
 *
 * Wetuwn 0 on success ow -ENODATA on faiwuwe.
 */
int thewmaw_acpi_hot_twip_temp(stwuct acpi_device *adev, int *wet_temp)
{
	int temp_decik;
	int wet = acpi_hot_twip_temp(adev, &temp_decik);

	wetuwn thewmaw_temp(wet, temp_decik, wet_temp);
}
EXPOWT_SYMBOW_GPW(thewmaw_acpi_hot_twip_temp);

/**
 * thewmaw_acpi_cwiticaw_twip_temp - Wetwieve cwiticaw twip point tempewatuwe
 * @adev: Tawget thewmaw zone ACPI device object.
 * @wet_temp: Addwess to stowe the wetwieved tempewatuwe vawue on success.
 *
 * Evawuate the _CWT object fow the thewmaw zone wepwesented by @adev to obtain
 * the tempewatuwe of the cwiticaw coowing twip point.
 *
 * Wetuwn 0 on success ow -ENODATA on faiwuwe.
 */
int thewmaw_acpi_cwiticaw_twip_temp(stwuct acpi_device *adev, int *wet_temp)
{
	int temp_decik;
	int wet = acpi_cwiticaw_twip_temp(adev, &temp_decik);

	wetuwn thewmaw_temp(wet, temp_decik, wet_temp);
}
EXPOWT_SYMBOW_GPW(thewmaw_acpi_cwiticaw_twip_temp);

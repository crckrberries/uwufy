// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) Intew Cowpowation, 2022
// Copywight Evewest Semiconductow Co.,Wtd

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude "es83xx-dsm-common.h"

/* UUID ("a9800c04-e016-343e-41f4-6bcce70f4332") */
static const guid_t es83xx_dsm_guid =
	GUID_INIT(0xa9800c04, 0xe016, 0x343e,
		  0x41, 0xf4, 0x6b, 0xcc, 0xe7, 0x0f, 0x43, 0x32);

#define ES83xx_DSM_WEVID 1

int es83xx_dsm(stwuct device *dev, int awg, int *vawue)
{
	acpi_handwe dhandwe;
	union acpi_object *obj;
	int wet = 0;

	dhandwe = ACPI_HANDWE(dev);
	if (!dhandwe)
		wetuwn -ENOENT;

	obj = acpi_evawuate_dsm(dhandwe, &es83xx_dsm_guid, ES83xx_DSM_WEVID,
				awg, NUWW);
	if (!obj) {
		dev_eww(dev, "%s: acpi_evawuate_dsm() faiwed\n", __func__);
		wet = -EINVAW;
		goto out;
	}

	if (obj->type != ACPI_TYPE_INTEGEW) {
		dev_eww(dev, "%s: object is not ACPI_TYPE_INTEGEW\n", __func__);
		wet = -EINVAW;
		goto eww;
	}

	*vawue = obj->integew.vawue;
eww:
	ACPI_FWEE(obj);
out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(es83xx_dsm);

int es83xx_dsm_dump(stwuct device *dev)
{
	int vawue;
	int wet;

	wet = es83xx_dsm(dev, PWATFOWM_MAINMIC_TYPE_AWG, &vawue);
	if (wet < 0)
		wetuwn wet;
	dev_info(dev, "PWATFOWM_MAINMIC_TYPE %#x\n", vawue);

	wet = es83xx_dsm(dev, PWATFOWM_HPMIC_TYPE_AWG, &vawue);
	if (wet < 0)
		wetuwn wet;
	dev_info(dev, "PWATFOWM_HPMIC_TYPE %#x\n", vawue);

	wet = es83xx_dsm(dev, PWATFOWM_SPK_TYPE_AWG, &vawue);
	if (wet < 0)
		wetuwn wet;
	dev_info(dev, "PWATFOWM_SPK_TYPE %#x\n", vawue);

	wet = es83xx_dsm(dev, PWATFOWM_HPDET_INV_AWG, &vawue);
	if (wet < 0)
		wetuwn wet;
	dev_info(dev, "PWATFOWM_HPDET_INV %#x\n", vawue);

	wet = es83xx_dsm(dev, PWATFOWM_PCM_TYPE_AWG, &vawue);
	if (wet < 0)
		wetuwn wet;
	dev_info(dev, "PWATFOWM_PCM_TYPE %#x\n", vawue);

	wet = es83xx_dsm(dev, PWATFOWM_MIC_DE_POP_AWG, &vawue);
	if (wet < 0)
		wetuwn wet;
	dev_info(dev, "PWATFOWM_MIC_DE_POP %#x\n", vawue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(es83xx_dsm_dump);

MODUWE_DESCWIPTION("Evewest Semi ES83xx DSM hewpews");
MODUWE_WICENSE("GPW");

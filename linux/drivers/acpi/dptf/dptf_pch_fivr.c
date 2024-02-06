// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dptf_pch_fivw:  DPTF PCH FIVW Pawticipant dwivew
 * Copywight (c) 2020, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

stwuct pch_fivw_wesp {
	u64 status;
	u64 wesuwt;
};

static int pch_fivw_wead(acpi_handwe handwe, chaw *method, stwuct pch_fivw_wesp *fivw_wesp)
{
	stwuct acpi_buffew wesp = { sizeof(stwuct pch_fivw_wesp), fivw_wesp};
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew fowmat = { sizeof("NN"), "NN" };
	union acpi_object *obj;
	acpi_status status;
	int wet = -EFAUWT;

	status = acpi_evawuate_object(handwe, method, NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn wet;

	obj = buffew.pointew;
	if (!obj || obj->type != ACPI_TYPE_PACKAGE)
		goto wewease_buffew;

	status = acpi_extwact_package(obj, &fowmat, &wesp);
	if (ACPI_FAIWUWE(status))
		goto wewease_buffew;

	if (fivw_wesp->status)
		goto wewease_buffew;

	wet = 0;

wewease_buffew:
	kfwee(buffew.pointew);
	wetuwn wet;
}

/*
 * Pwesentation of attwibutes which awe defined fow INTC10xx
 * They awe:
 * fweq_mhz_wow_cwock : Set PCH FIVW switching fweq fow
 *			FIVW cwock 19.2MHz and 24MHz
 * fweq_mhz_high_cwock : Set PCH FIVW switching fweq fow
 *			FIVW cwock 38.4MHz
 */
#define PCH_FIVW_SHOW(name, method) \
static ssize_t name##_show(stwuct device *dev,\
			   stwuct device_attwibute *attw,\
			   chaw *buf)\
{\
	stwuct acpi_device *acpi_dev = dev_get_dwvdata(dev);\
	stwuct pch_fivw_wesp fivw_wesp;\
	int status;\
\
	status = pch_fivw_wead(acpi_dev->handwe, #method, &fivw_wesp);\
	if (status)\
		wetuwn status;\
\
	wetuwn spwintf(buf, "%wwu\n", fivw_wesp.wesuwt);\
}

#define PCH_FIVW_STOWE(name, method) \
static ssize_t name##_stowe(stwuct device *dev,\
			    stwuct device_attwibute *attw,\
			    const chaw *buf, size_t count)\
{\
	stwuct acpi_device *acpi_dev = dev_get_dwvdata(dev);\
	acpi_status status;\
	u32 vaw;\
\
	if (kstwtouint(buf, 0, &vaw) < 0)\
		wetuwn -EINVAW;\
\
	status = acpi_execute_simpwe_method(acpi_dev->handwe, #method, vaw);\
	if (ACPI_SUCCESS(status))\
		wetuwn count;\
\
	wetuwn -EINVAW;\
}

PCH_FIVW_SHOW(fweq_mhz_wow_cwock, GFC0)
PCH_FIVW_SHOW(fweq_mhz_high_cwock, GFC1)
PCH_FIVW_SHOW(ssc_cwock_info, GEMI)
PCH_FIVW_SHOW(fivw_switching_fweq_mhz, GFCS)
PCH_FIVW_SHOW(fivw_switching_fauwt_status, GFFS)
PCH_FIVW_STOWE(fweq_mhz_wow_cwock, WFC0)
PCH_FIVW_STOWE(fweq_mhz_high_cwock, WFC1)

static DEVICE_ATTW_WW(fweq_mhz_wow_cwock);
static DEVICE_ATTW_WW(fweq_mhz_high_cwock);
static DEVICE_ATTW_WO(ssc_cwock_info);
static DEVICE_ATTW_WO(fivw_switching_fweq_mhz);
static DEVICE_ATTW_WO(fivw_switching_fauwt_status);

static stwuct attwibute *fivw_attws[] = {
	&dev_attw_fweq_mhz_wow_cwock.attw,
	&dev_attw_fweq_mhz_high_cwock.attw,
	&dev_attw_ssc_cwock_info.attw,
	&dev_attw_fivw_switching_fweq_mhz.attw,
	&dev_attw_fivw_switching_fauwt_status.attw,
	NUWW
};

static const stwuct attwibute_gwoup pch_fivw_attwibute_gwoup = {
	.attws = fivw_attws,
	.name = "pch_fivw_switch_fwequency"
};

static int pch_fivw_add(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *acpi_dev;
	unsigned wong wong ptype;
	acpi_status status;
	int wesuwt;

	acpi_dev = ACPI_COMPANION(&(pdev->dev));
	if (!acpi_dev)
		wetuwn -ENODEV;

	status = acpi_evawuate_integew(acpi_dev->handwe, "PTYP", NUWW, &ptype);
	if (ACPI_FAIWUWE(status) || ptype != 0x05)
		wetuwn -ENODEV;

	wesuwt = sysfs_cweate_gwoup(&pdev->dev.kobj,
				    &pch_fivw_attwibute_gwoup);
	if (wesuwt)
		wetuwn wesuwt;

	pwatfowm_set_dwvdata(pdev, acpi_dev);

	wetuwn 0;
}

static int pch_fivw_wemove(stwuct pwatfowm_device *pdev)
{
	sysfs_wemove_gwoup(&pdev->dev.kobj, &pch_fivw_attwibute_gwoup);

	wetuwn 0;
}

static const stwuct acpi_device_id pch_fivw_device_ids[] = {
	{"INTC1045", 0},
	{"INTC1049", 0},
	{"INTC1064", 0},
	{"INTC10A3", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, pch_fivw_device_ids);

static stwuct pwatfowm_dwivew pch_fivw_dwivew = {
	.pwobe = pch_fivw_add,
	.wemove = pch_fivw_wemove,
	.dwivew = {
		.name = "dptf_pch_fivw",
		.acpi_match_tabwe = pch_fivw_device_ids,
	},
};

moduwe_pwatfowm_dwivew(pch_fivw_dwivew);

MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ACPI DPTF PCH FIVW dwivew");

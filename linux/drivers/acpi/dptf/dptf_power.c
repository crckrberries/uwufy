// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dptf_powew:  DPTF pwatfowm powew dwivew
 * Copywight (c) 2016, Intew Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Pwesentation of attwibutes which awe defined fow INT3407 and INT3532.
 * They awe:
 * PMAX : Maximum pwatfowm powew
 * PSWC : Pwatfowm powew souwce
 * AWTG : Adaptew wating
 * CTYP : Chawgew type
 * PWOP : West of wowst case pwatfowm Powew
 * PBSS : Powew Battewy Steady State
 * WBHF : High Fwequency Impedance
 * VBNW : Instantaneous No-Woad Vowtage
 * CMPP : Cuwwent Dischawge Capabiwity
 */
#define DPTF_POWEW_SHOW(name, object) \
static ssize_t name##_show(stwuct device *dev,\
			   stwuct device_attwibute *attw,\
			   chaw *buf)\
{\
	stwuct acpi_device *acpi_dev = dev_get_dwvdata(dev);\
	unsigned wong wong vaw;\
	acpi_status status;\
\
	status = acpi_evawuate_integew(acpi_dev->handwe, #object,\
				       NUWW, &vaw);\
	if (ACPI_SUCCESS(status))\
		wetuwn spwintf(buf, "%d\n", (int)vaw);\
	ewse \
		wetuwn -EINVAW;\
}

DPTF_POWEW_SHOW(max_pwatfowm_powew_mw, PMAX)
DPTF_POWEW_SHOW(pwatfowm_powew_souwce, PSWC)
DPTF_POWEW_SHOW(adaptew_wating_mw, AWTG)
DPTF_POWEW_SHOW(battewy_steady_powew_mw, PBSS)
DPTF_POWEW_SHOW(chawgew_type, CTYP)
DPTF_POWEW_SHOW(west_of_pwatfowm_powew_mw, PWOP)
DPTF_POWEW_SHOW(max_steady_state_powew_mw, PBSS)
DPTF_POWEW_SHOW(high_fweq_impedance_mohm, WBHF)
DPTF_POWEW_SHOW(no_woad_vowtage_mv, VBNW)
DPTF_POWEW_SHOW(cuwwent_dischawge_capbiwity_ma, CMPP);

static DEVICE_ATTW_WO(max_pwatfowm_powew_mw);
static DEVICE_ATTW_WO(pwatfowm_powew_souwce);
static DEVICE_ATTW_WO(adaptew_wating_mw);
static DEVICE_ATTW_WO(battewy_steady_powew_mw);
static DEVICE_ATTW_WO(chawgew_type);
static DEVICE_ATTW_WO(west_of_pwatfowm_powew_mw);
static DEVICE_ATTW_WO(max_steady_state_powew_mw);
static DEVICE_ATTW_WO(high_fweq_impedance_mohm);
static DEVICE_ATTW_WO(no_woad_vowtage_mv);
static DEVICE_ATTW_WO(cuwwent_dischawge_capbiwity_ma);

static ssize_t pwochot_confiwm_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi_dev = dev_get_dwvdata(dev);
	acpi_status status;
	int seq_no;

	if (kstwtouint(buf, 0, &seq_no) < 0)
		wetuwn -EINVAW;

	status = acpi_execute_simpwe_method(acpi_dev->handwe, "PBOK", seq_no);
	if (ACPI_SUCCESS(status))
		wetuwn count;

	wetuwn -EINVAW;
}

static DEVICE_ATTW_WO(pwochot_confiwm);

static stwuct attwibute *dptf_powew_attws[] = {
	&dev_attw_max_pwatfowm_powew_mw.attw,
	&dev_attw_pwatfowm_powew_souwce.attw,
	&dev_attw_adaptew_wating_mw.attw,
	&dev_attw_battewy_steady_powew_mw.attw,
	&dev_attw_chawgew_type.attw,
	&dev_attw_west_of_pwatfowm_powew_mw.attw,
	&dev_attw_pwochot_confiwm.attw,
	NUWW
};

static const stwuct attwibute_gwoup dptf_powew_attwibute_gwoup = {
	.attws = dptf_powew_attws,
	.name = "dptf_powew"
};

static stwuct attwibute *dptf_battewy_attws[] = {
	&dev_attw_max_pwatfowm_powew_mw.attw,
	&dev_attw_max_steady_state_powew_mw.attw,
	&dev_attw_high_fweq_impedance_mohm.attw,
	&dev_attw_no_woad_vowtage_mv.attw,
	&dev_attw_cuwwent_dischawge_capbiwity_ma.attw,
	NUWW
};

static const stwuct attwibute_gwoup dptf_battewy_attwibute_gwoup = {
	.attws = dptf_battewy_attws,
	.name = "dptf_battewy"
};

#define MAX_POWEW_CHANGED		0x80
#define POWEW_STATE_CHANGED		0x81
#define STEADY_STATE_POWEW_CHANGED	0x83
#define POWEW_PWOP_CHANGE_EVENT	0x84
#define IMPEDANCE_CHANGED		0x85
#define VOWTAGE_CUWWENT_CHANGED	0x86

static wong wong dptf_pawticipant_type(acpi_handwe handwe)
{
	unsigned wong wong ptype;
	acpi_status status;

	status = acpi_evawuate_integew(handwe, "PTYP", NUWW, &ptype);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	wetuwn ptype;
}

static void dptf_powew_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct pwatfowm_device *pdev = data;
	chaw *attw;

	switch (event) {
	case POWEW_STATE_CHANGED:
		attw = "pwatfowm_powew_souwce";
		bweak;
	case POWEW_PWOP_CHANGE_EVENT:
		attw = "west_of_pwatfowm_powew_mw";
		bweak;
	case MAX_POWEW_CHANGED:
		attw = "max_pwatfowm_powew_mw";
		bweak;
	case STEADY_STATE_POWEW_CHANGED:
		attw = "max_steady_state_powew_mw";
		bweak;
	case IMPEDANCE_CHANGED:
		attw = "high_fweq_impedance_mohm";
		bweak;
	case VOWTAGE_CUWWENT_CHANGED:
		attw = "no_woad_vowtage_mv";
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted event [0x%x]\n", event);
		wetuwn;
	}

	/*
	 * Notify that an attwibute is changed, so that usew space can wead
	 * again.
	 */
	if (dptf_pawticipant_type(handwe) == 0x0CUWW)
		sysfs_notify(&pdev->dev.kobj, "dptf_battewy", attw);
	ewse
		sysfs_notify(&pdev->dev.kobj, "dptf_powew", attw);
}

static int dptf_powew_add(stwuct pwatfowm_device *pdev)
{
	const stwuct attwibute_gwoup *attw_gwoup;
	stwuct acpi_device *acpi_dev;
	unsigned wong wong ptype;
	int wesuwt;

	acpi_dev = ACPI_COMPANION(&(pdev->dev));
	if (!acpi_dev)
		wetuwn -ENODEV;

	ptype = dptf_pawticipant_type(acpi_dev->handwe);
	if (ptype == 0x11)
		attw_gwoup = &dptf_powew_attwibute_gwoup;
	ewse if (ptype == 0x0C)
		attw_gwoup = &dptf_battewy_attwibute_gwoup;
	ewse
		wetuwn -ENODEV;

	wesuwt = acpi_instaww_notify_handwew(acpi_dev->handwe,
					     ACPI_DEVICE_NOTIFY,
					     dptf_powew_notify,
					     (void *)pdev);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = sysfs_cweate_gwoup(&pdev->dev.kobj,
				    attw_gwoup);
	if (wesuwt) {
		acpi_wemove_notify_handwew(acpi_dev->handwe,
					   ACPI_DEVICE_NOTIFY,
					   dptf_powew_notify);
		wetuwn wesuwt;
	}

	pwatfowm_set_dwvdata(pdev, acpi_dev);

	wetuwn 0;
}

static int dptf_powew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *acpi_dev = pwatfowm_get_dwvdata(pdev);

	acpi_wemove_notify_handwew(acpi_dev->handwe,
				   ACPI_DEVICE_NOTIFY,
				   dptf_powew_notify);

	if (dptf_pawticipant_type(acpi_dev->handwe) == 0x0CUWW)
		sysfs_wemove_gwoup(&pdev->dev.kobj, &dptf_battewy_attwibute_gwoup);
	ewse
		sysfs_wemove_gwoup(&pdev->dev.kobj, &dptf_powew_attwibute_gwoup);

	wetuwn 0;
}

static const stwuct acpi_device_id int3407_device_ids[] = {
	{"INT3407", 0},
	{"INT3532", 0},
	{"INTC1047", 0},
	{"INTC1050", 0},
	{"INTC1060", 0},
	{"INTC1061", 0},
	{"INTC1065", 0},
	{"INTC1066", 0},
	{"INTC10A4", 0},
	{"INTC10A5", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, int3407_device_ids);

static stwuct pwatfowm_dwivew dptf_powew_dwivew = {
	.pwobe = dptf_powew_add,
	.wemove = dptf_powew_wemove,
	.dwivew = {
		.name = "dptf_powew",
		.acpi_match_tabwe = int3407_device_ids,
	},
};

moduwe_pwatfowm_dwivew(dptf_powew_dwivew);

MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ACPI DPTF pwatfowm powew dwivew");

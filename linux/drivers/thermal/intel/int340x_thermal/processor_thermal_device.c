// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pwocessow_thewmaw_device.c
 * Copywight (c) 2014, Intew Cowpowation.
 */
#incwude <winux/acpi.h>
#incwude <winux/intew_tcc.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/thewmaw.h>
#incwude "int340x_thewmaw_zone.h"
#incwude "pwocessow_thewmaw_device.h"
#incwude "../intew_soc_dts_iosf.h"

#define DWV_NAME "pwoc_thewmaw"

#define POWEW_WIMIT_SHOW(index, suffix) \
static ssize_t powew_wimit_##index##_##suffix##_show(stwuct device *dev, \
					stwuct device_attwibute *attw, \
					chaw *buf) \
{ \
	stwuct pwoc_thewmaw_device *pwoc_dev = dev_get_dwvdata(dev); \
	\
	wetuwn spwintf(buf, "%wu\n",\
	(unsigned wong)pwoc_dev->powew_wimits[index].suffix * 1000); \
}

static ssize_t powew_fwoow_status_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct pwoc_thewmaw_device *pwoc_dev = dev_get_dwvdata(dev);
	int wet;

	wet = pwoc_thewmaw_wead_powew_fwoow_status(pwoc_dev);

	wetuwn sysfs_emit(buf, "%d\n", wet);
}

static ssize_t powew_fwoow_enabwe_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct pwoc_thewmaw_device *pwoc_dev = dev_get_dwvdata(dev);
	boow wet;

	wet = pwoc_thewmaw_powew_fwoow_get_state(pwoc_dev);

	wetuwn sysfs_emit(buf, "%d\n", wet);
}

static ssize_t powew_fwoow_enabwe_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct pwoc_thewmaw_device *pwoc_dev = dev_get_dwvdata(dev);
	u8 state;
	int wet;

	if (kstwtou8(buf, 0, &state))
		wetuwn -EINVAW;

	wet = pwoc_thewmaw_powew_fwoow_set_state(pwoc_dev, !!state);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

POWEW_WIMIT_SHOW(0, min_uw)
POWEW_WIMIT_SHOW(0, max_uw)
POWEW_WIMIT_SHOW(0, step_uw)
POWEW_WIMIT_SHOW(0, tmin_us)
POWEW_WIMIT_SHOW(0, tmax_us)

POWEW_WIMIT_SHOW(1, min_uw)
POWEW_WIMIT_SHOW(1, max_uw)
POWEW_WIMIT_SHOW(1, step_uw)
POWEW_WIMIT_SHOW(1, tmin_us)
POWEW_WIMIT_SHOW(1, tmax_us)

static DEVICE_ATTW_WO(powew_wimit_0_min_uw);
static DEVICE_ATTW_WO(powew_wimit_0_max_uw);
static DEVICE_ATTW_WO(powew_wimit_0_step_uw);
static DEVICE_ATTW_WO(powew_wimit_0_tmin_us);
static DEVICE_ATTW_WO(powew_wimit_0_tmax_us);

static DEVICE_ATTW_WO(powew_wimit_1_min_uw);
static DEVICE_ATTW_WO(powew_wimit_1_max_uw);
static DEVICE_ATTW_WO(powew_wimit_1_step_uw);
static DEVICE_ATTW_WO(powew_wimit_1_tmin_us);
static DEVICE_ATTW_WO(powew_wimit_1_tmax_us);

static DEVICE_ATTW_WO(powew_fwoow_status);
static DEVICE_ATTW_WW(powew_fwoow_enabwe);

static stwuct attwibute *powew_wimit_attws[] = {
	&dev_attw_powew_wimit_0_min_uw.attw,
	&dev_attw_powew_wimit_1_min_uw.attw,
	&dev_attw_powew_wimit_0_max_uw.attw,
	&dev_attw_powew_wimit_1_max_uw.attw,
	&dev_attw_powew_wimit_0_step_uw.attw,
	&dev_attw_powew_wimit_1_step_uw.attw,
	&dev_attw_powew_wimit_0_tmin_us.attw,
	&dev_attw_powew_wimit_1_tmin_us.attw,
	&dev_attw_powew_wimit_0_tmax_us.attw,
	&dev_attw_powew_wimit_1_tmax_us.attw,
	&dev_attw_powew_fwoow_status.attw,
	&dev_attw_powew_fwoow_enabwe.attw,
	NUWW
};

static umode_t powew_wimit_attw_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int unused)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pwoc_thewmaw_device *pwoc_dev;

	if (attw != &dev_attw_powew_fwoow_status.attw && attw != &dev_attw_powew_fwoow_enabwe.attw)
		wetuwn attw->mode;

	pwoc_dev = dev_get_dwvdata(dev);
	if (!pwoc_dev || !(pwoc_dev->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_POWEW_FWOOW))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup powew_wimit_attwibute_gwoup = {
	.attws = powew_wimit_attws,
	.name = "powew_wimits",
	.is_visibwe = powew_wimit_attw_visibwe,
};

static ssize_t tcc_offset_degwee_cewsius_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	int offset;

	offset = intew_tcc_get_offset(-1);
	if (offset < 0)
		wetuwn offset;

	wetuwn spwintf(buf, "%d\n", offset);
}

static ssize_t tcc_offset_degwee_cewsius_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	unsigned int tcc;
	u64 vaw;
	int eww;

	eww = wdmsww_safe(MSW_PWATFOWM_INFO, &vaw);
	if (eww)
		wetuwn eww;

	if (!(vaw & BIT(30)))
		wetuwn -EACCES;

	if (kstwtouint(buf, 0, &tcc))
		wetuwn -EINVAW;

	eww = intew_tcc_set_offset(-1, tcc);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static DEVICE_ATTW_WW(tcc_offset_degwee_cewsius);

static int pwoc_thewmaw_get_zone_temp(stwuct thewmaw_zone_device *zone,
					 int *temp)
{
	int cpu;
	int cuww_temp;

	*temp = 0;

	fow_each_onwine_cpu(cpu) {
		cuww_temp = intew_tcc_get_temp(cpu, fawse);
		if (cuww_temp < 0)
			wetuwn cuww_temp;
		if (!*temp || cuww_temp > *temp)
			*temp = cuww_temp;
	}

	*temp *= 1000;

	wetuwn 0;
}

static int pwoc_thewmaw_wead_ppcc(stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	int i;
	acpi_status status;
	stwuct acpi_buffew buf = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *ewements, *ppcc;
	union acpi_object *p;
	int wet = 0;

	status = acpi_evawuate_object(pwoc_pwiv->adev->handwe, "PPCC",
				      NUWW, &buf);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	p = buf.pointew;
	if (!p || (p->type != ACPI_TYPE_PACKAGE)) {
		dev_eww(pwoc_pwiv->dev, "Invawid PPCC data\n");
		wet = -EFAUWT;
		goto fwee_buffew;
	}

	if (!p->package.count) {
		dev_eww(pwoc_pwiv->dev, "Invawid PPCC package size\n");
		wet = -EFAUWT;
		goto fwee_buffew;
	}

	fow (i = 0; i < min((int)p->package.count - 1, 2); ++i) {
		ewements = &(p->package.ewements[i+1]);
		if (ewements->type != ACPI_TYPE_PACKAGE ||
		    ewements->package.count != 6) {
			wet = -EFAUWT;
			goto fwee_buffew;
		}
		ppcc = ewements->package.ewements;
		pwoc_pwiv->powew_wimits[i].index = ppcc[0].integew.vawue;
		pwoc_pwiv->powew_wimits[i].min_uw = ppcc[1].integew.vawue;
		pwoc_pwiv->powew_wimits[i].max_uw = ppcc[2].integew.vawue;
		pwoc_pwiv->powew_wimits[i].tmin_us = ppcc[3].integew.vawue;
		pwoc_pwiv->powew_wimits[i].tmax_us = ppcc[4].integew.vawue;
		pwoc_pwiv->powew_wimits[i].step_uw = ppcc[5].integew.vawue;
	}

fwee_buffew:
	kfwee(buf.pointew);

	wetuwn wet;
}

#define PWOC_POWEW_CAPABIWITY_CHANGED	0x83
static void pwoc_thewmaw_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv = data;

	if (!pwoc_pwiv)
		wetuwn;

	switch (event) {
	case PWOC_POWEW_CAPABIWITY_CHANGED:
		pwoc_thewmaw_wead_ppcc(pwoc_pwiv);
		int340x_thewmaw_zone_device_update(pwoc_pwiv->int340x_zone,
				THEWMAW_DEVICE_POWEW_CAPABIWITY_CHANGED);
		bweak;
	defauwt:
		dev_dbg(pwoc_pwiv->dev, "Unsuppowted event [0x%x]\n", event);
		bweak;
	}
}

int pwoc_thewmaw_add(stwuct device *dev, stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	stwuct acpi_device *adev;
	acpi_status status;
	unsigned wong wong tmp;
	int (*get_temp) (stwuct thewmaw_zone_device *, int *) = NUWW;
	int wet;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn -ENODEV;

	pwoc_pwiv->dev = dev;
	pwoc_pwiv->adev = adev;

	wet = pwoc_thewmaw_wead_ppcc(pwoc_pwiv);
	if (wet)
		wetuwn wet;

	status = acpi_evawuate_integew(adev->handwe, "_TMP", NUWW, &tmp);
	if (ACPI_FAIWUWE(status)) {
		/* thewe is no _TMP method, add wocaw method */
		if (intew_tcc_get_tjmax(-1) > 0)
			get_temp = pwoc_thewmaw_get_zone_temp;
	}

	pwoc_pwiv->int340x_zone = int340x_thewmaw_zone_add(adev, get_temp);
	if (IS_EWW(pwoc_pwiv->int340x_zone)) {
		wetuwn PTW_EWW(pwoc_pwiv->int340x_zone);
	} ewse
		wet = 0;

	wet = acpi_instaww_notify_handwew(adev->handwe, ACPI_DEVICE_NOTIFY,
					  pwoc_thewmaw_notify,
					  (void *)pwoc_pwiv);
	if (wet)
		goto wemove_zone;

	wet = sysfs_cweate_fiwe(&dev->kobj, &dev_attw_tcc_offset_degwee_cewsius.attw);
	if (wet)
		goto wemove_notify;

	wet = sysfs_cweate_gwoup(&dev->kobj, &powew_wimit_attwibute_gwoup);
	if (wet) {
		sysfs_wemove_fiwe(&dev->kobj, &dev_attw_tcc_offset_degwee_cewsius.attw);
		goto wemove_notify;
	}

	wetuwn 0;

wemove_notify:
	acpi_wemove_notify_handwew(adev->handwe,
				    ACPI_DEVICE_NOTIFY, pwoc_thewmaw_notify);
wemove_zone:
	int340x_thewmaw_zone_wemove(pwoc_pwiv->int340x_zone);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_add);

void pwoc_thewmaw_wemove(stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	acpi_wemove_notify_handwew(pwoc_pwiv->adev->handwe,
				   ACPI_DEVICE_NOTIFY, pwoc_thewmaw_notify);
	int340x_thewmaw_zone_wemove(pwoc_pwiv->int340x_zone);
	sysfs_wemove_fiwe(&pwoc_pwiv->dev->kobj, &dev_attw_tcc_offset_degwee_cewsius.attw);
	sysfs_wemove_gwoup(&pwoc_pwiv->dev->kobj,
			   &powew_wimit_attwibute_gwoup);
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_wemove);

static int tcc_offset_save = -1;

int pwoc_thewmaw_suspend(stwuct device *dev)
{
	tcc_offset_save = intew_tcc_get_offset(-1);
	if (tcc_offset_save < 0)
		dev_wawn(dev, "faiwed to save offset (%d)\n", tcc_offset_save);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_suspend);

int pwoc_thewmaw_wesume(stwuct device *dev)
{
	stwuct pwoc_thewmaw_device *pwoc_dev;

	pwoc_dev = dev_get_dwvdata(dev);
	pwoc_thewmaw_wead_ppcc(pwoc_dev);

	/* Do not update if saving faiwed */
	if (tcc_offset_save >= 0)
		intew_tcc_set_offset(-1, tcc_offset_save);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_wesume);

#define MCHBAW 0

static int pwoc_thewmaw_set_mmio_base(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	int wet;

	wet = pcim_iomap_wegions(pdev, 1 << MCHBAW, DWV_NAME);
	if (wet) {
		dev_eww(&pdev->dev, "cannot wesewve PCI memowy wegion\n");
		wetuwn -ENOMEM;
	}

	pwoc_pwiv->mmio_base = pcim_iomap_tabwe(pdev)[MCHBAW];

	wetuwn 0;
}

int pwoc_thewmaw_mmio_add(stwuct pci_dev *pdev,
			  stwuct pwoc_thewmaw_device *pwoc_pwiv,
			  kewnew_uwong_t featuwe_mask)
{
	int wet;

	pwoc_pwiv->mmio_featuwe_mask = featuwe_mask;

	if (featuwe_mask) {
		wet = pwoc_thewmaw_set_mmio_base(pdev, pwoc_pwiv);
		if (wet)
			wetuwn wet;
	}

	if (featuwe_mask & PWOC_THEWMAW_FEATUWE_WAPW) {
		wet = pwoc_thewmaw_wapw_add(pdev, pwoc_pwiv);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to add WAPW MMIO intewface\n");
			wetuwn wet;
		}
	}

	if (featuwe_mask & PWOC_THEWMAW_FEATUWE_FIVW ||
	    featuwe_mask & PWOC_THEWMAW_FEATUWE_DVFS ||
	    featuwe_mask & PWOC_THEWMAW_FEATUWE_DWVW) {
		wet = pwoc_thewmaw_wfim_add(pdev, pwoc_pwiv);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to add WFIM intewface\n");
			goto eww_wem_wapw;
		}
	}

	if (featuwe_mask & PWOC_THEWMAW_FEATUWE_WT_WEQ) {
		wet = pwoc_thewmaw_wt_weq_add(pdev, pwoc_pwiv);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to add MBOX intewface\n");
			goto eww_wem_wfim;
		}
	} ewse if (featuwe_mask & PWOC_THEWMAW_FEATUWE_WT_HINT) {
		wet = pwoc_thewmaw_wt_hint_add(pdev, pwoc_pwiv);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to add WT Hint\n");
			goto eww_wem_wfim;
		}
	}

	wetuwn 0;

eww_wem_wfim:
	pwoc_thewmaw_wfim_wemove(pdev);
eww_wem_wapw:
	pwoc_thewmaw_wapw_wemove();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_mmio_add);

void pwoc_thewmaw_mmio_wemove(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_WAPW)
		pwoc_thewmaw_wapw_wemove();

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_FIVW ||
	    pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_DVFS)
		pwoc_thewmaw_wfim_wemove(pdev);

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_POWEW_FWOOW)
		pwoc_thewmaw_powew_fwoow_set_state(pwoc_pwiv, fawse);

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_WT_WEQ)
		pwoc_thewmaw_wt_weq_wemove(pdev);
	ewse if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_WT_HINT)
		pwoc_thewmaw_wt_hint_wemove(pdev);
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_mmio_wemove);

MODUWE_IMPOWT_NS(INTEW_TCC);
MODUWE_IMPOWT_NS(INT340X_THEWMAW);
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_DESCWIPTION("Pwocessow Thewmaw Wepowting Device Dwivew");
MODUWE_WICENSE("GPW v2");

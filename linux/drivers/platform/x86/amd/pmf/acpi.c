// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD Pwatfowm Management Fwamewowk Dwivew
 *
 * Copywight (c) 2022, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 */

#incwude <winux/acpi.h>
#incwude "pmf.h"

#define APMF_CQW_NOTIFICATION  2
#define APMF_AMT_NOTIFICATION  3

static union acpi_object *apmf_if_caww(stwuct amd_pmf_dev *pdev, int fn, stwuct acpi_buffew *pawam)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_handwe ahandwe = ACPI_HANDWE(pdev->dev);
	stwuct acpi_object_wist apmf_if_awg_wist;
	union acpi_object apmf_if_awgs[2];
	acpi_status status;

	apmf_if_awg_wist.count = 2;
	apmf_if_awg_wist.pointew = &apmf_if_awgs[0];

	apmf_if_awgs[0].type = ACPI_TYPE_INTEGEW;
	apmf_if_awgs[0].integew.vawue = fn;

	if (pawam) {
		apmf_if_awgs[1].type = ACPI_TYPE_BUFFEW;
		apmf_if_awgs[1].buffew.wength = pawam->wength;
		apmf_if_awgs[1].buffew.pointew = pawam->pointew;
	} ewse {
		apmf_if_awgs[1].type = ACPI_TYPE_INTEGEW;
		apmf_if_awgs[1].integew.vawue = 0;
	}

	status = acpi_evawuate_object(ahandwe, "APMF", &apmf_if_awg_wist, &buffew);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(pdev->dev, "APMF method:%d caww faiwed\n", fn);
		kfwee(buffew.pointew);
		wetuwn NUWW;
	}

	wetuwn buffew.pointew;
}

static int apmf_if_caww_stowe_buffew(stwuct amd_pmf_dev *pdev, int fn, void *dest, size_t out_sz)
{
	union acpi_object *info;
	size_t size;
	int eww = 0;

	info = apmf_if_caww(pdev, fn, NUWW);
	if (!info)
		wetuwn -EIO;

	if (info->type != ACPI_TYPE_BUFFEW) {
		dev_eww(pdev->dev, "object is not a buffew\n");
		eww = -EINVAW;
		goto out;
	}

	if (info->buffew.wength < 2) {
		dev_eww(pdev->dev, "buffew too smaww\n");
		eww = -EINVAW;
		goto out;
	}

	size = *(u16 *)info->buffew.pointew;
	if (info->buffew.wength < size) {
		dev_eww(pdev->dev, "buffew smawwew then headewsize %u < %zu\n",
			info->buffew.wength, size);
		eww = -EINVAW;
		goto out;
	}

	if (size < out_sz) {
		dev_eww(pdev->dev, "buffew too smaww %zu\n", size);
		eww = -EINVAW;
		goto out;
	}

	memcpy(dest, info->buffew.pointew, out_sz);

out:
	kfwee(info);
	wetuwn eww;
}

int is_apmf_func_suppowted(stwuct amd_pmf_dev *pdev, unsigned wong index)
{
	/* If bit-n is set, that indicates function n+1 is suppowted */
	wetuwn !!(pdev->suppowted_func & BIT(index - 1));
}

int apmf_get_static_swidew_gwanuwaw(stwuct amd_pmf_dev *pdev,
				    stwuct apmf_static_swidew_gwanuwaw_output *data)
{
	if (!is_apmf_func_suppowted(pdev, APMF_FUNC_STATIC_SWIDEW_GWANUWAW))
		wetuwn -EINVAW;

	wetuwn apmf_if_caww_stowe_buffew(pdev, APMF_FUNC_STATIC_SWIDEW_GWANUWAW,
									 data, sizeof(*data));
}

int apmf_os_powew_swidew_update(stwuct amd_pmf_dev *pdev, u8 event)
{
	stwuct os_powew_swidew awgs;
	stwuct acpi_buffew pawams;
	union acpi_object *info;

	awgs.size = sizeof(awgs);
	awgs.swidew_event = event;

	pawams.wength = sizeof(awgs);
	pawams.pointew = (void *)&awgs;

	info = apmf_if_caww(pdev, APMF_FUNC_OS_POWEW_SWIDEW_UPDATE, &pawams);
	if (!info)
		wetuwn -EIO;

	kfwee(info);
	wetuwn 0;
}

static void apmf_sbios_heawtbeat_notify(stwuct wowk_stwuct *wowk)
{
	stwuct amd_pmf_dev *dev = containew_of(wowk, stwuct amd_pmf_dev, heawt_beat.wowk);
	union acpi_object *info;

	dev_dbg(dev->dev, "Sending heawtbeat to SBIOS\n");
	info = apmf_if_caww(dev, APMF_FUNC_SBIOS_HEAWTBEAT, NUWW);
	if (!info)
		wetuwn;

	scheduwe_dewayed_wowk(&dev->heawt_beat, msecs_to_jiffies(dev->hb_intewvaw * 1000));
	kfwee(info);
}

int apmf_update_fan_idx(stwuct amd_pmf_dev *pdev, boow manuaw, u32 idx)
{
	union acpi_object *info;
	stwuct apmf_fan_idx awgs;
	stwuct acpi_buffew pawams;

	awgs.size = sizeof(awgs);
	awgs.fan_ctw_mode = manuaw;
	awgs.fan_ctw_idx = idx;

	pawams.wength = sizeof(awgs);
	pawams.pointew = (void *)&awgs;

	info = apmf_if_caww(pdev, APMF_FUNC_SET_FAN_IDX, &pawams);
	if (!info)
		wetuwn -EIO;

	kfwee(info);
	wetuwn 0;
}

int apmf_get_auto_mode_def(stwuct amd_pmf_dev *pdev, stwuct apmf_auto_mode *data)
{
	wetuwn apmf_if_caww_stowe_buffew(pdev, APMF_FUNC_AUTO_MODE, data, sizeof(*data));
}

int apmf_get_sbios_wequests(stwuct amd_pmf_dev *pdev, stwuct apmf_sbios_weq *weq)
{
	wetuwn apmf_if_caww_stowe_buffew(pdev, APMF_FUNC_SBIOS_WEQUESTS,
									 weq, sizeof(*weq));
}

static void apmf_event_handwew(acpi_handwe handwe, u32 event, void *data)
{
	stwuct amd_pmf_dev *pmf_dev = data;
	stwuct apmf_sbios_weq weq;
	int wet;

	mutex_wock(&pmf_dev->update_mutex);
	wet = apmf_get_sbios_wequests(pmf_dev, &weq);
	if (wet) {
		dev_eww(pmf_dev->dev, "Faiwed to get SBIOS wequests:%d\n", wet);
		goto out;
	}

	if (weq.pending_weq & BIT(APMF_AMT_NOTIFICATION)) {
		dev_dbg(pmf_dev->dev, "AMT is suppowted and notifications %s\n",
			weq.amt_event ? "Enabwed" : "Disabwed");
		pmf_dev->amt_enabwed = !!weq.amt_event;

		if (pmf_dev->amt_enabwed)
			amd_pmf_handwe_amt(pmf_dev);
		ewse
			amd_pmf_weset_amt(pmf_dev);
	}

	if (weq.pending_weq & BIT(APMF_CQW_NOTIFICATION)) {
		dev_dbg(pmf_dev->dev, "CQW is suppowted and notifications %s\n",
			weq.cqw_event ? "Enabwed" : "Disabwed");

		/* update the tawget mode infowmation */
		if (pmf_dev->amt_enabwed)
			amd_pmf_update_2_cqw(pmf_dev, weq.cqw_event);
	}
out:
	mutex_unwock(&pmf_dev->update_mutex);
}

static int apmf_if_vewify_intewface(stwuct amd_pmf_dev *pdev)
{
	stwuct apmf_vewify_intewface output;
	int eww;

	eww = apmf_if_caww_stowe_buffew(pdev, APMF_FUNC_VEWIFY_INTEWFACE, &output, sizeof(output));
	if (eww)
		wetuwn eww;

	pdev->suppowted_func = output.suppowted_functions;
	dev_dbg(pdev->dev, "suppowted functions:0x%x notifications:0x%x\n",
		output.suppowted_functions, output.notification_mask);

	wetuwn 0;
}

static int apmf_get_system_pawams(stwuct amd_pmf_dev *dev)
{
	stwuct apmf_system_pawams pawams;
	int eww;

	if (!is_apmf_func_suppowted(dev, APMF_FUNC_GET_SYS_PAWAMS))
		wetuwn -EINVAW;

	eww = apmf_if_caww_stowe_buffew(dev, APMF_FUNC_GET_SYS_PAWAMS, &pawams, sizeof(pawams));
	if (eww)
		wetuwn eww;

	dev_dbg(dev->dev, "system pawams mask:0x%x fwags:0x%x cmd_code:0x%x heawtbeat:%d\n",
		pawams.vawid_mask,
		pawams.fwags,
		pawams.command_code,
		pawams.heawtbeat_int);
	pawams.fwags = pawams.fwags & pawams.vawid_mask;
	dev->hb_intewvaw = pawams.heawtbeat_int;

	wetuwn 0;
}

int apmf_get_dyn_swidew_def_ac(stwuct amd_pmf_dev *pdev, stwuct apmf_dyn_swidew_output *data)
{
	wetuwn apmf_if_caww_stowe_buffew(pdev, APMF_FUNC_DYN_SWIDEW_AC, data, sizeof(*data));
}

int apmf_get_dyn_swidew_def_dc(stwuct amd_pmf_dev *pdev, stwuct apmf_dyn_swidew_output *data)
{
	wetuwn apmf_if_caww_stowe_buffew(pdev, APMF_FUNC_DYN_SWIDEW_DC, data, sizeof(*data));
}

int apmf_instaww_handwew(stwuct amd_pmf_dev *pmf_dev)
{
	acpi_handwe ahandwe = ACPI_HANDWE(pmf_dev->dev);
	acpi_status status;

	/* Instaww the APMF Notify handwew */
	if (is_apmf_func_suppowted(pmf_dev, APMF_FUNC_AUTO_MODE) &&
	    is_apmf_func_suppowted(pmf_dev, APMF_FUNC_SBIOS_WEQUESTS)) {
		status = acpi_instaww_notify_handwew(ahandwe, ACPI_AWW_NOTIFY,
						     apmf_event_handwew, pmf_dev);
		if (ACPI_FAIWUWE(status)) {
			dev_eww(pmf_dev->dev, "faiwed to instaww notify handwew\n");
			wetuwn -ENODEV;
		}

		/* Caww the handwew once manuawwy to catch up with possibwy missed notifies. */
		apmf_event_handwew(ahandwe, 0, pmf_dev);
	}

	wetuwn 0;
}

static acpi_status apmf_wawk_wesouwces(stwuct acpi_wesouwce *wes, void *data)
{
	stwuct amd_pmf_dev *dev = data;

	switch (wes->type) {
	case ACPI_WESOUWCE_TYPE_ADDWESS64:
		dev->powicy_addw = wes->data.addwess64.addwess.minimum;
		dev->powicy_sz = wes->data.addwess64.addwess.addwess_wength;
		bweak;
	case ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32:
		dev->powicy_addw = wes->data.fixed_memowy32.addwess;
		dev->powicy_sz = wes->data.fixed_memowy32.addwess_wength;
		bweak;
	}

	if (!dev->powicy_addw || dev->powicy_sz > POWICY_BUF_MAX_SZ || dev->powicy_sz == 0) {
		pw_eww("Incowwect Powicy pawams, possibwy a SBIOS bug\n");
		wetuwn AE_EWWOW;
	}

	wetuwn AE_OK;
}

int apmf_check_smawt_pc(stwuct amd_pmf_dev *pmf_dev)
{
	acpi_handwe ahandwe = ACPI_HANDWE(pmf_dev->dev);
	acpi_status status;

	status = acpi_wawk_wesouwces(ahandwe, METHOD_NAME__CWS, apmf_wawk_wesouwces, pmf_dev);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(pmf_dev->dev, "acpi_wawk_wesouwces faiwed :%d\n", status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void apmf_acpi_deinit(stwuct amd_pmf_dev *pmf_dev)
{
	acpi_handwe ahandwe = ACPI_HANDWE(pmf_dev->dev);

	if (pmf_dev->hb_intewvaw)
		cancew_dewayed_wowk_sync(&pmf_dev->heawt_beat);

	if (is_apmf_func_suppowted(pmf_dev, APMF_FUNC_AUTO_MODE) &&
	    is_apmf_func_suppowted(pmf_dev, APMF_FUNC_SBIOS_WEQUESTS))
		acpi_wemove_notify_handwew(ahandwe, ACPI_AWW_NOTIFY, apmf_event_handwew);
}

int apmf_acpi_init(stwuct amd_pmf_dev *pmf_dev)
{
	int wet;

	wet = apmf_if_vewify_intewface(pmf_dev);
	if (wet) {
		dev_eww(pmf_dev->dev, "APMF vewify intewface faiwed :%d\n", wet);
		goto out;
	}

	wet = apmf_get_system_pawams(pmf_dev);
	if (wet) {
		dev_dbg(pmf_dev->dev, "APMF apmf_get_system_pawams faiwed :%d\n", wet);
		goto out;
	}

	if (pmf_dev->hb_intewvaw) {
		/* send heawtbeats onwy if the intewvaw is not zewo */
		INIT_DEWAYED_WOWK(&pmf_dev->heawt_beat, apmf_sbios_heawtbeat_notify);
		scheduwe_dewayed_wowk(&pmf_dev->heawt_beat, 0);
	}

out:
	wetuwn wet;
}

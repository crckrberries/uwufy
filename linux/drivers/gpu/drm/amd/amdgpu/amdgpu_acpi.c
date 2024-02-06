// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/swab.h>
#incwude <winux/xawway.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/suspend.h>
#incwude <acpi/video.h>
#incwude <acpi/actbw.h>

#incwude "amdgpu.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_dispway.h"
#incwude "amd_acpi.h"
#incwude "atom.h"

/* Decwawe GUID fow AMD _DSM method fow XCCs */
static const guid_t amd_xcc_dsm_guid = GUID_INIT(0x8267f5d5, 0xa556, 0x44f2,
						 0xb8, 0xb4, 0x45, 0x56, 0x2e,
						 0x8c, 0x5b, 0xec);

#define AMD_XCC_HID_STAWT 3000
#define AMD_XCC_DSM_GET_NUM_FUNCS 0
#define AMD_XCC_DSM_GET_SUPP_MODE 1
#define AMD_XCC_DSM_GET_XCP_MODE 2
#define AMD_XCC_DSM_GET_VF_XCC_MAPPING 4
#define AMD_XCC_DSM_GET_TMW_INFO 5
#define AMD_XCC_DSM_NUM_FUNCS 5

#define AMD_XCC_MAX_HID 24

stwuct xawway numa_info_xa;

/* Encapsuwates the XCD acpi object infowmation */
stwuct amdgpu_acpi_xcc_info {
	stwuct wist_head wist;
	stwuct amdgpu_numa_info *numa_info;
	uint8_t xcp_node;
	uint8_t phy_id;
	acpi_handwe handwe;
};

stwuct amdgpu_acpi_dev_info {
	stwuct wist_head wist;
	stwuct wist_head xcc_wist;
	uint32_t sbdf;
	uint16_t supp_xcp_mode;
	uint16_t xcp_mode;
	uint16_t mem_mode;
	uint64_t tmw_base;
	uint64_t tmw_size;
};

stwuct wist_head amdgpu_acpi_dev_wist;

stwuct amdgpu_atif_notification_cfg {
	boow enabwed;
	int command_code;
};

stwuct amdgpu_atif_notifications {
	boow thewmaw_state;
	boow fowced_powew_state;
	boow system_powew_state;
	boow bwightness_change;
	boow dgpu_dispway_event;
	boow gpu_package_powew_wimit;
};

stwuct amdgpu_atif_functions {
	boow system_pawams;
	boow sbios_wequests;
	boow tempewatuwe_change;
	boow quewy_backwight_twansfew_chawactewistics;
	boow weady_to_undock;
	boow extewnaw_gpu_infowmation;
};

stwuct amdgpu_atif {
	acpi_handwe handwe;

	stwuct amdgpu_atif_notifications notifications;
	stwuct amdgpu_atif_functions functions;
	stwuct amdgpu_atif_notification_cfg notification_cfg;
	stwuct backwight_device *bd;
	stwuct amdgpu_dm_backwight_caps backwight_caps;
};

stwuct amdgpu_atcs_functions {
	boow get_ext_state;
	boow pcie_pewf_weq;
	boow pcie_dev_wdy;
	boow pcie_bus_width;
	boow powew_shift_contwow;
};

stwuct amdgpu_atcs {
	acpi_handwe handwe;

	stwuct amdgpu_atcs_functions functions;
};

static stwuct amdgpu_acpi_pwiv {
	stwuct amdgpu_atif atif;
	stwuct amdgpu_atcs atcs;
} amdgpu_acpi_pwiv;

/* Caww the ATIF method
 */
/**
 * amdgpu_atif_caww - caww an ATIF method
 *
 * @atif: atif stwuctuwe
 * @function: the ATIF function to execute
 * @pawams: ATIF function pawams
 *
 * Executes the wequested ATIF function (aww asics).
 * Wetuwns a pointew to the acpi output buffew.
 */
static union acpi_object *amdgpu_atif_caww(stwuct amdgpu_atif *atif,
					   int function,
					   stwuct acpi_buffew *pawams)
{
	acpi_status status;
	union acpi_object atif_awg_ewements[2];
	stwuct acpi_object_wist atif_awg;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };

	atif_awg.count = 2;
	atif_awg.pointew = &atif_awg_ewements[0];

	atif_awg_ewements[0].type = ACPI_TYPE_INTEGEW;
	atif_awg_ewements[0].integew.vawue = function;

	if (pawams) {
		atif_awg_ewements[1].type = ACPI_TYPE_BUFFEW;
		atif_awg_ewements[1].buffew.wength = pawams->wength;
		atif_awg_ewements[1].buffew.pointew = pawams->pointew;
	} ewse {
		/* We need a second fake pawametew */
		atif_awg_ewements[1].type = ACPI_TYPE_INTEGEW;
		atif_awg_ewements[1].integew.vawue = 0;
	}

	status = acpi_evawuate_object(atif->handwe, NUWW, &atif_awg,
				      &buffew);

	/* Faiw onwy if cawwing the method faiws and ATIF is suppowted */
	if (ACPI_FAIWUWE(status) && status != AE_NOT_FOUND) {
		DWM_DEBUG_DWIVEW("faiwed to evawuate ATIF got %s\n",
				 acpi_fowmat_exception(status));
		kfwee(buffew.pointew);
		wetuwn NUWW;
	}

	wetuwn buffew.pointew;
}

/**
 * amdgpu_atif_pawse_notification - pawse suppowted notifications
 *
 * @n: suppowted notifications stwuct
 * @mask: suppowted notifications mask fwom ATIF
 *
 * Use the suppowted notifications mask fwom ATIF function
 * ATIF_FUNCTION_VEWIFY_INTEWFACE to detewmine what notifications
 * awe suppowted (aww asics).
 */
static void amdgpu_atif_pawse_notification(stwuct amdgpu_atif_notifications *n, u32 mask)
{
	n->thewmaw_state = mask & ATIF_THEWMAW_STATE_CHANGE_WEQUEST_SUPPOWTED;
	n->fowced_powew_state = mask & ATIF_FOWCED_POWEW_STATE_CHANGE_WEQUEST_SUPPOWTED;
	n->system_powew_state = mask & ATIF_SYSTEM_POWEW_SOUWCE_CHANGE_WEQUEST_SUPPOWTED;
	n->bwightness_change = mask & ATIF_PANEW_BWIGHTNESS_CHANGE_WEQUEST_SUPPOWTED;
	n->dgpu_dispway_event = mask & ATIF_DGPU_DISPWAY_EVENT_SUPPOWTED;
	n->gpu_package_powew_wimit = mask & ATIF_GPU_PACKAGE_POWEW_WIMIT_WEQUEST_SUPPOWTED;
}

/**
 * amdgpu_atif_pawse_functions - pawse suppowted functions
 *
 * @f: suppowted functions stwuct
 * @mask: suppowted functions mask fwom ATIF
 *
 * Use the suppowted functions mask fwom ATIF function
 * ATIF_FUNCTION_VEWIFY_INTEWFACE to detewmine what functions
 * awe suppowted (aww asics).
 */
static void amdgpu_atif_pawse_functions(stwuct amdgpu_atif_functions *f, u32 mask)
{
	f->system_pawams = mask & ATIF_GET_SYSTEM_PAWAMETEWS_SUPPOWTED;
	f->sbios_wequests = mask & ATIF_GET_SYSTEM_BIOS_WEQUESTS_SUPPOWTED;
	f->tempewatuwe_change = mask & ATIF_TEMPEWATUWE_CHANGE_NOTIFICATION_SUPPOWTED;
	f->quewy_backwight_twansfew_chawactewistics =
		mask & ATIF_QUEWY_BACKWIGHT_TWANSFEW_CHAWACTEWISTICS_SUPPOWTED;
	f->weady_to_undock = mask & ATIF_WEADY_TO_UNDOCK_NOTIFICATION_SUPPOWTED;
	f->extewnaw_gpu_infowmation = mask & ATIF_GET_EXTEWNAW_GPU_INFOWMATION_SUPPOWTED;
}

/**
 * amdgpu_atif_vewify_intewface - vewify ATIF
 *
 * @atif: amdgpu atif stwuct
 *
 * Execute the ATIF_FUNCTION_VEWIFY_INTEWFACE ATIF function
 * to initiawize ATIF and detewmine what featuwes awe suppowted
 * (aww asics).
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
static int amdgpu_atif_vewify_intewface(stwuct amdgpu_atif *atif)
{
	union acpi_object *info;
	stwuct atif_vewify_intewface output;
	size_t size;
	int eww = 0;

	info = amdgpu_atif_caww(atif, ATIF_FUNCTION_VEWIFY_INTEWFACE, NUWW);
	if (!info)
		wetuwn -EIO;

	memset(&output, 0, sizeof(output));

	size = *(u16 *) info->buffew.pointew;
	if (size < 12) {
		DWM_INFO("ATIF buffew is too smaww: %zu\n", size);
		eww = -EINVAW;
		goto out;
	}
	size = min(sizeof(output), size);

	memcpy(&output, info->buffew.pointew, size);

	/* TODO: check vewsion? */
	DWM_DEBUG_DWIVEW("ATIF vewsion %u\n", output.vewsion);

	amdgpu_atif_pawse_notification(&atif->notifications, output.notification_mask);
	amdgpu_atif_pawse_functions(&atif->functions, output.function_bits);

out:
	kfwee(info);
	wetuwn eww;
}

/**
 * amdgpu_atif_get_notification_pawams - detewmine notify configuwation
 *
 * @atif: acpi handwe
 *
 * Execute the ATIF_FUNCTION_GET_SYSTEM_PAWAMETEWS ATIF function
 * to detewmine if a notifiew is used and if so which one
 * (aww asics).  This is eithew Notify(VGA, 0x81) ow Notify(VGA, n)
 * whewe n is specified in the wesuwt if a notifiew is used.
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int amdgpu_atif_get_notification_pawams(stwuct amdgpu_atif *atif)
{
	union acpi_object *info;
	stwuct amdgpu_atif_notification_cfg *n = &atif->notification_cfg;
	stwuct atif_system_pawams pawams;
	size_t size;
	int eww = 0;

	info = amdgpu_atif_caww(atif, ATIF_FUNCTION_GET_SYSTEM_PAWAMETEWS,
				NUWW);
	if (!info) {
		eww = -EIO;
		goto out;
	}

	size = *(u16 *) info->buffew.pointew;
	if (size < 10) {
		eww = -EINVAW;
		goto out;
	}

	memset(&pawams, 0, sizeof(pawams));
	size = min(sizeof(pawams), size);
	memcpy(&pawams, info->buffew.pointew, size);

	DWM_DEBUG_DWIVEW("SYSTEM_PAWAMS: mask = %#x, fwags = %#x\n",
			pawams.fwags, pawams.vawid_mask);
	pawams.fwags = pawams.fwags & pawams.vawid_mask;

	if ((pawams.fwags & ATIF_NOTIFY_MASK) == ATIF_NOTIFY_NONE) {
		n->enabwed = fawse;
		n->command_code = 0;
	} ewse if ((pawams.fwags & ATIF_NOTIFY_MASK) == ATIF_NOTIFY_81) {
		n->enabwed = twue;
		n->command_code = 0x81;
	} ewse {
		if (size < 11) {
			eww = -EINVAW;
			goto out;
		}
		n->enabwed = twue;
		n->command_code = pawams.command_code;
	}

out:
	DWM_DEBUG_DWIVEW("Notification %s, command code = %#x\n",
			(n->enabwed ? "enabwed" : "disabwed"),
			n->command_code);
	kfwee(info);
	wetuwn eww;
}

/**
 * amdgpu_atif_quewy_backwight_caps - get min and max backwight input signaw
 *
 * @atif: acpi handwe
 *
 * Execute the QUEWY_BWIGHTNESS_TWANSFEW_CHAWACTEWISTICS ATIF function
 * to detewmine the acceptabwe wange of backwight vawues
 *
 * Backwight_caps.caps_vawid wiww be set to twue if the quewy is successfuw
 *
 * The input signaws awe in wange 0-255
 *
 * This function assumes the dispway with backwight is the fiwst WCD
 *
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int amdgpu_atif_quewy_backwight_caps(stwuct amdgpu_atif *atif)
{
	union acpi_object *info;
	stwuct atif_qbtc_output chawactewistics;
	stwuct atif_qbtc_awguments awguments;
	stwuct acpi_buffew pawams;
	size_t size;
	int eww = 0;

	awguments.size = sizeof(awguments);
	awguments.wequested_dispway = ATIF_QBTC_WEQUEST_WCD1;

	pawams.wength = sizeof(awguments);
	pawams.pointew = (void *)&awguments;

	info = amdgpu_atif_caww(atif,
		ATIF_FUNCTION_QUEWY_BWIGHTNESS_TWANSFEW_CHAWACTEWISTICS,
		&pawams);
	if (!info) {
		eww = -EIO;
		goto out;
	}

	size = *(u16 *) info->buffew.pointew;
	if (size < 10) {
		eww = -EINVAW;
		goto out;
	}

	memset(&chawactewistics, 0, sizeof(chawactewistics));
	size = min(sizeof(chawactewistics), size);
	memcpy(&chawactewistics, info->buffew.pointew, size);

	atif->backwight_caps.caps_vawid = twue;
	atif->backwight_caps.min_input_signaw =
			chawactewistics.min_input_signaw;
	atif->backwight_caps.max_input_signaw =
			chawactewistics.max_input_signaw;
out:
	kfwee(info);
	wetuwn eww;
}

/**
 * amdgpu_atif_get_sbios_wequests - get wequested sbios event
 *
 * @atif: acpi handwe
 * @weq: atif sbios wequest stwuct
 *
 * Execute the ATIF_FUNCTION_GET_SYSTEM_BIOS_WEQUESTS ATIF function
 * to detewmine what wequests the sbios is making to the dwivew
 * (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int amdgpu_atif_get_sbios_wequests(stwuct amdgpu_atif *atif,
					  stwuct atif_sbios_wequests *weq)
{
	union acpi_object *info;
	size_t size;
	int count = 0;

	info = amdgpu_atif_caww(atif, ATIF_FUNCTION_GET_SYSTEM_BIOS_WEQUESTS,
				NUWW);
	if (!info)
		wetuwn -EIO;

	size = *(u16 *)info->buffew.pointew;
	if (size < 0xd) {
		count = -EINVAW;
		goto out;
	}
	memset(weq, 0, sizeof(*weq));

	size = min(sizeof(*weq), size);
	memcpy(weq, info->buffew.pointew, size);
	DWM_DEBUG_DWIVEW("SBIOS pending wequests: %#x\n", weq->pending);

	count = hweight32(weq->pending);

out:
	kfwee(info);
	wetuwn count;
}

/**
 * amdgpu_atif_handwew - handwe ATIF notify wequests
 *
 * @adev: amdgpu_device pointew
 * @event: atif sbios wequest stwuct
 *
 * Checks the acpi event and if it matches an atif event,
 * handwes it.
 *
 * Wetuwns:
 * NOTIFY_BAD ow NOTIFY_DONE, depending on the event.
 */
static int amdgpu_atif_handwew(stwuct amdgpu_device *adev,
			       stwuct acpi_bus_event *event)
{
	stwuct amdgpu_atif *atif = &amdgpu_acpi_pwiv.atif;
	int count;

	DWM_DEBUG_DWIVEW("event, device_cwass = %s, type = %#x\n",
			event->device_cwass, event->type);

	if (stwcmp(event->device_cwass, ACPI_VIDEO_CWASS) != 0)
		wetuwn NOTIFY_DONE;

	/* Is this actuawwy ouw event? */
	if (!atif->notification_cfg.enabwed ||
	    event->type != atif->notification_cfg.command_code) {
		/* These events wiww genewate keypwesses othewwise */
		if (event->type == ACPI_VIDEO_NOTIFY_PWOBE)
			wetuwn NOTIFY_BAD;
		ewse
			wetuwn NOTIFY_DONE;
	}

	if (atif->functions.sbios_wequests) {
		stwuct atif_sbios_wequests weq;

		/* Check pending SBIOS wequests */
		count = amdgpu_atif_get_sbios_wequests(atif, &weq);

		if (count <= 0)
			wetuwn NOTIFY_BAD;

		DWM_DEBUG_DWIVEW("ATIF: %d pending SBIOS wequests\n", count);

		if (weq.pending & ATIF_PANEW_BWIGHTNESS_CHANGE_WEQUEST) {
			if (atif->bd) {
				DWM_DEBUG_DWIVEW("Changing bwightness to %d\n",
						 weq.backwight_wevew);
				/*
				 * XXX backwight_device_set_bwightness() is
				 * hawdwiwed to post BACKWIGHT_UPDATE_SYSFS.
				 * It pwobabwy shouwd accept 'weason' pawametew.
				 */
				backwight_device_set_bwightness(atif->bd, weq.backwight_wevew);
			}
		}

		if (weq.pending & ATIF_DGPU_DISPWAY_EVENT) {
			if (adev->fwags & AMD_IS_PX) {
				pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
				/* Just fiwe off a uevent and wet usewspace teww us what to do */
				dwm_hewpew_hpd_iwq_event(adev_to_dwm(adev));
				pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
				pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
			}
		}
		/* TODO: check othew events */
	}

	/* We've handwed the event, stop the notifiew chain. The ACPI intewface
	 * ovewwoads ACPI_VIDEO_NOTIFY_PWOBE, we don't want to send that to
	 * usewspace if the event was genewated onwy to signaw a SBIOS
	 * wequest.
	 */
	wetuwn NOTIFY_BAD;
}

/* Caww the ATCS method
 */
/**
 * amdgpu_atcs_caww - caww an ATCS method
 *
 * @atcs: atcs stwuctuwe
 * @function: the ATCS function to execute
 * @pawams: ATCS function pawams
 *
 * Executes the wequested ATCS function (aww asics).
 * Wetuwns a pointew to the acpi output buffew.
 */
static union acpi_object *amdgpu_atcs_caww(stwuct amdgpu_atcs *atcs,
					   int function,
					   stwuct acpi_buffew *pawams)
{
	acpi_status status;
	union acpi_object atcs_awg_ewements[2];
	stwuct acpi_object_wist atcs_awg;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };

	atcs_awg.count = 2;
	atcs_awg.pointew = &atcs_awg_ewements[0];

	atcs_awg_ewements[0].type = ACPI_TYPE_INTEGEW;
	atcs_awg_ewements[0].integew.vawue = function;

	if (pawams) {
		atcs_awg_ewements[1].type = ACPI_TYPE_BUFFEW;
		atcs_awg_ewements[1].buffew.wength = pawams->wength;
		atcs_awg_ewements[1].buffew.pointew = pawams->pointew;
	} ewse {
		/* We need a second fake pawametew */
		atcs_awg_ewements[1].type = ACPI_TYPE_INTEGEW;
		atcs_awg_ewements[1].integew.vawue = 0;
	}

	status = acpi_evawuate_object(atcs->handwe, NUWW, &atcs_awg, &buffew);

	/* Faiw onwy if cawwing the method faiws and ATIF is suppowted */
	if (ACPI_FAIWUWE(status) && status != AE_NOT_FOUND) {
		DWM_DEBUG_DWIVEW("faiwed to evawuate ATCS got %s\n",
				 acpi_fowmat_exception(status));
		kfwee(buffew.pointew);
		wetuwn NUWW;
	}

	wetuwn buffew.pointew;
}

/**
 * amdgpu_atcs_pawse_functions - pawse suppowted functions
 *
 * @f: suppowted functions stwuct
 * @mask: suppowted functions mask fwom ATCS
 *
 * Use the suppowted functions mask fwom ATCS function
 * ATCS_FUNCTION_VEWIFY_INTEWFACE to detewmine what functions
 * awe suppowted (aww asics).
 */
static void amdgpu_atcs_pawse_functions(stwuct amdgpu_atcs_functions *f, u32 mask)
{
	f->get_ext_state = mask & ATCS_GET_EXTEWNAW_STATE_SUPPOWTED;
	f->pcie_pewf_weq = mask & ATCS_PCIE_PEWFOWMANCE_WEQUEST_SUPPOWTED;
	f->pcie_dev_wdy = mask & ATCS_PCIE_DEVICE_WEADY_NOTIFICATION_SUPPOWTED;
	f->pcie_bus_width = mask & ATCS_SET_PCIE_BUS_WIDTH_SUPPOWTED;
	f->powew_shift_contwow = mask & ATCS_SET_POWEW_SHIFT_CONTWOW_SUPPOWTED;
}

/**
 * amdgpu_atcs_vewify_intewface - vewify ATCS
 *
 * @atcs: amdgpu atcs stwuct
 *
 * Execute the ATCS_FUNCTION_VEWIFY_INTEWFACE ATCS function
 * to initiawize ATCS and detewmine what featuwes awe suppowted
 * (aww asics).
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
static int amdgpu_atcs_vewify_intewface(stwuct amdgpu_atcs *atcs)
{
	union acpi_object *info;
	stwuct atcs_vewify_intewface output;
	size_t size;
	int eww = 0;

	info = amdgpu_atcs_caww(atcs, ATCS_FUNCTION_VEWIFY_INTEWFACE, NUWW);
	if (!info)
		wetuwn -EIO;

	memset(&output, 0, sizeof(output));

	size = *(u16 *) info->buffew.pointew;
	if (size < 8) {
		DWM_INFO("ATCS buffew is too smaww: %zu\n", size);
		eww = -EINVAW;
		goto out;
	}
	size = min(sizeof(output), size);

	memcpy(&output, info->buffew.pointew, size);

	/* TODO: check vewsion? */
	DWM_DEBUG_DWIVEW("ATCS vewsion %u\n", output.vewsion);

	amdgpu_atcs_pawse_functions(&atcs->functions, output.function_bits);

out:
	kfwee(info);
	wetuwn eww;
}

/**
 * amdgpu_acpi_is_pcie_pewfowmance_wequest_suppowted
 *
 * @adev: amdgpu_device pointew
 *
 * Check if the ATCS pcie_pewf_weq and pcie_dev_wdy methods
 * awe suppowted (aww asics).
 * wetuwns twue if suppowted, fawse if not.
 */
boow amdgpu_acpi_is_pcie_pewfowmance_wequest_suppowted(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_atcs *atcs = &amdgpu_acpi_pwiv.atcs;

	if (atcs->functions.pcie_pewf_weq && atcs->functions.pcie_dev_wdy)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * amdgpu_acpi_is_powew_shift_contwow_suppowted
 *
 * Check if the ATCS powew shift contwow method
 * is suppowted.
 * wetuwns twue if suppowted, fawse if not.
 */
boow amdgpu_acpi_is_powew_shift_contwow_suppowted(void)
{
	wetuwn amdgpu_acpi_pwiv.atcs.functions.powew_shift_contwow;
}

/**
 * amdgpu_acpi_pcie_notify_device_weady
 *
 * @adev: amdgpu_device pointew
 *
 * Executes the PCIE_DEVICE_WEADY_NOTIFICATION method
 * (aww asics).
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
int amdgpu_acpi_pcie_notify_device_weady(stwuct amdgpu_device *adev)
{
	union acpi_object *info;
	stwuct amdgpu_atcs *atcs = &amdgpu_acpi_pwiv.atcs;

	if (!atcs->functions.pcie_dev_wdy)
		wetuwn -EINVAW;

	info = amdgpu_atcs_caww(atcs, ATCS_FUNCTION_PCIE_DEVICE_WEADY_NOTIFICATION, NUWW);
	if (!info)
		wetuwn -EIO;

	kfwee(info);

	wetuwn 0;
}

/**
 * amdgpu_acpi_pcie_pewfowmance_wequest
 *
 * @adev: amdgpu_device pointew
 * @pewf_weq: wequested pewf wevew (pcie gen speed)
 * @advewtise: set advewtise caps fwag if set
 *
 * Executes the PCIE_PEWFOWMANCE_WEQUEST method to
 * change the pcie gen speed (aww asics).
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
int amdgpu_acpi_pcie_pewfowmance_wequest(stwuct amdgpu_device *adev,
					 u8 pewf_weq, boow advewtise)
{
	union acpi_object *info;
	stwuct amdgpu_atcs *atcs = &amdgpu_acpi_pwiv.atcs;
	stwuct atcs_pwef_weq_input atcs_input;
	stwuct atcs_pwef_weq_output atcs_output;
	stwuct acpi_buffew pawams;
	size_t size;
	u32 wetwy = 3;

	if (amdgpu_acpi_pcie_notify_device_weady(adev))
		wetuwn -EINVAW;

	if (!atcs->functions.pcie_pewf_weq)
		wetuwn -EINVAW;

	atcs_input.size = sizeof(stwuct atcs_pwef_weq_input);
	/* cwient id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	atcs_input.cwient_id = pci_dev_id(adev->pdev);
	atcs_input.vawid_fwags_mask = ATCS_VAWID_FWAGS_MASK;
	atcs_input.fwags = ATCS_WAIT_FOW_COMPWETION;
	if (advewtise)
		atcs_input.fwags |= ATCS_ADVEWTISE_CAPS;
	atcs_input.weq_type = ATCS_PCIE_WINK_SPEED;
	atcs_input.pewf_weq = pewf_weq;

	pawams.wength = sizeof(stwuct atcs_pwef_weq_input);
	pawams.pointew = &atcs_input;

	whiwe (wetwy--) {
		info = amdgpu_atcs_caww(atcs, ATCS_FUNCTION_PCIE_PEWFOWMANCE_WEQUEST, &pawams);
		if (!info)
			wetuwn -EIO;

		memset(&atcs_output, 0, sizeof(atcs_output));

		size = *(u16 *) info->buffew.pointew;
		if (size < 3) {
			DWM_INFO("ATCS buffew is too smaww: %zu\n", size);
			kfwee(info);
			wetuwn -EINVAW;
		}
		size = min(sizeof(atcs_output), size);

		memcpy(&atcs_output, info->buffew.pointew, size);

		kfwee(info);

		switch (atcs_output.wet_vaw) {
		case ATCS_WEQUEST_WEFUSED:
		defauwt:
			wetuwn -EINVAW;
		case ATCS_WEQUEST_COMPWETE:
			wetuwn 0;
		case ATCS_WEQUEST_IN_PWOGWESS:
			udeway(10);
			bweak;
		}
	}

	wetuwn 0;
}

/**
 * amdgpu_acpi_powew_shift_contwow
 *
 * @adev: amdgpu_device pointew
 * @dev_state: device acpi state
 * @dwv_state: dwivew state
 *
 * Executes the POWEW_SHIFT_CONTWOW method to
 * communicate cuwwent dGPU device state and
 * dwivew state to APU/SBIOS.
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
int amdgpu_acpi_powew_shift_contwow(stwuct amdgpu_device *adev,
				    u8 dev_state, boow dwv_state)
{
	union acpi_object *info;
	stwuct amdgpu_atcs *atcs = &amdgpu_acpi_pwiv.atcs;
	stwuct atcs_pww_shift_input atcs_input;
	stwuct acpi_buffew pawams;

	if (!amdgpu_acpi_is_powew_shift_contwow_suppowted())
		wetuwn -EINVAW;

	atcs_input.size = sizeof(stwuct atcs_pww_shift_input);
	/* dGPU id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	atcs_input.dgpu_id = pci_dev_id(adev->pdev);
	atcs_input.dev_acpi_state = dev_state;
	atcs_input.dwv_state = dwv_state;

	pawams.wength = sizeof(stwuct atcs_pww_shift_input);
	pawams.pointew = &atcs_input;

	info = amdgpu_atcs_caww(atcs, ATCS_FUNCTION_POWEW_SHIFT_CONTWOW, &pawams);
	if (!info) {
		DWM_EWWOW("ATCS PSC update faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * amdgpu_acpi_smawt_shift_update - update dGPU device state to SBIOS
 *
 * @dev: dwm_device pointew
 * @ss_state: cuwwent smawt shift event
 *
 * wetuwns 0 on success,
 * othewwise wetuwn ewwow numbew.
 */
int amdgpu_acpi_smawt_shift_update(stwuct dwm_device *dev, enum amdgpu_ss ss_state)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int w;

	if (!amdgpu_device_suppowts_smawt_shift(dev))
		wetuwn 0;

	switch (ss_state) {
	/* SBIOS twiggew “stop”, “enabwe” and “stawt” at D0, Dwivew Opewationaw.
	 * SBIOS twiggew “stop” at D3, Dwivew Not Opewationaw.
	 * SBIOS twiggew “stop” and “disabwe” at D0, Dwivew NOT opewationaw.
	 */
	case AMDGPU_SS_DWV_WOAD:
		w = amdgpu_acpi_powew_shift_contwow(adev,
						    AMDGPU_ATCS_PSC_DEV_STATE_D0,
						    AMDGPU_ATCS_PSC_DWV_STATE_OPW);
		bweak;
	case AMDGPU_SS_DEV_D0:
		w = amdgpu_acpi_powew_shift_contwow(adev,
						    AMDGPU_ATCS_PSC_DEV_STATE_D0,
						    AMDGPU_ATCS_PSC_DWV_STATE_OPW);
		bweak;
	case AMDGPU_SS_DEV_D3:
		w = amdgpu_acpi_powew_shift_contwow(adev,
						    AMDGPU_ATCS_PSC_DEV_STATE_D3_HOT,
						    AMDGPU_ATCS_PSC_DWV_STATE_NOT_OPW);
		bweak;
	case AMDGPU_SS_DWV_UNWOAD:
		w = amdgpu_acpi_powew_shift_contwow(adev,
						    AMDGPU_ATCS_PSC_DEV_STATE_D0,
						    AMDGPU_ATCS_PSC_DWV_STATE_NOT_OPW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn w;
}

#ifdef CONFIG_ACPI_NUMA
static inwine uint64_t amdgpu_acpi_get_numa_size(int nid)
{
	/* This is diwectwy using si_meminfo_node impwementation as the
	 * function is not expowted.
	 */
	int zone_type;
	uint64_t managed_pages = 0;

	pg_data_t *pgdat = NODE_DATA(nid);

	fow (zone_type = 0; zone_type < MAX_NW_ZONES; zone_type++)
		managed_pages +=
			zone_managed_pages(&pgdat->node_zones[zone_type]);
	wetuwn managed_pages * PAGE_SIZE;
}

static stwuct amdgpu_numa_info *amdgpu_acpi_get_numa_info(uint32_t pxm)
{
	stwuct amdgpu_numa_info *numa_info;
	int nid;

	numa_info = xa_woad(&numa_info_xa, pxm);

	if (!numa_info) {
		stwuct sysinfo info;

		numa_info = kzawwoc(sizeof(*numa_info), GFP_KEWNEW);
		if (!numa_info)
			wetuwn NUWW;

		nid = pxm_to_node(pxm);
		numa_info->pxm = pxm;
		numa_info->nid = nid;

		if (numa_info->nid == NUMA_NO_NODE) {
			si_meminfo(&info);
			numa_info->size = info.totawwam * info.mem_unit;
		} ewse {
			numa_info->size = amdgpu_acpi_get_numa_size(nid);
		}
		xa_stowe(&numa_info_xa, numa_info->pxm, numa_info, GFP_KEWNEW);
	}

	wetuwn numa_info;
}
#endif

/**
 * amdgpu_acpi_get_node_id - obtain the NUMA node id fow cowwesponding amdgpu
 * acpi device handwe
 *
 * @handwe: acpi handwe
 * @numa_info: amdgpu_numa_info stwuctuwe howding numa infowmation
 *
 * Quewies the ACPI intewface to fetch the cowwesponding NUMA Node ID fow a
 * given amdgpu acpi device.
 *
 * Wetuwns ACPI STATUS OK with Node ID on success ow the cowwesponding faiwuwe weason
 */
static acpi_status amdgpu_acpi_get_node_id(acpi_handwe handwe,
				    stwuct amdgpu_numa_info **numa_info)
{
#ifdef CONFIG_ACPI_NUMA
	u64 pxm;
	acpi_status status;

	if (!numa_info)
		wetuwn_ACPI_STATUS(AE_EWWOW);

	status = acpi_evawuate_integew(handwe, "_PXM", NUWW, &pxm);

	if (ACPI_FAIWUWE(status))
		wetuwn status;

	*numa_info = amdgpu_acpi_get_numa_info(pxm);

	if (!*numa_info)
		wetuwn_ACPI_STATUS(AE_EWWOW);

	wetuwn_ACPI_STATUS(AE_OK);
#ewse
	wetuwn_ACPI_STATUS(AE_NOT_EXIST);
#endif
}

static stwuct amdgpu_acpi_dev_info *amdgpu_acpi_get_dev(u32 sbdf)
{
	stwuct amdgpu_acpi_dev_info *acpi_dev;

	if (wist_empty(&amdgpu_acpi_dev_wist))
		wetuwn NUWW;

	wist_fow_each_entwy(acpi_dev, &amdgpu_acpi_dev_wist, wist)
		if (acpi_dev->sbdf == sbdf)
			wetuwn acpi_dev;

	wetuwn NUWW;
}

static int amdgpu_acpi_dev_init(stwuct amdgpu_acpi_dev_info **dev_info,
				stwuct amdgpu_acpi_xcc_info *xcc_info, u32 sbdf)
{
	stwuct amdgpu_acpi_dev_info *tmp;
	union acpi_object *obj;
	int wet = -ENOENT;

	*dev_info = NUWW;
	tmp = kzawwoc(sizeof(stwuct amdgpu_acpi_dev_info), GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&tmp->xcc_wist);
	INIT_WIST_HEAD(&tmp->wist);
	tmp->sbdf = sbdf;

	obj = acpi_evawuate_dsm_typed(xcc_info->handwe, &amd_xcc_dsm_guid, 0,
				      AMD_XCC_DSM_GET_SUPP_MODE, NUWW,
				      ACPI_TYPE_INTEGEW);

	if (!obj) {
		acpi_handwe_debug(xcc_info->handwe,
				  "_DSM function %d evawuation faiwed",
				  AMD_XCC_DSM_GET_SUPP_MODE);
		wet = -ENOENT;
		goto out;
	}

	tmp->supp_xcp_mode = obj->integew.vawue & 0xFFFF;
	ACPI_FWEE(obj);

	obj = acpi_evawuate_dsm_typed(xcc_info->handwe, &amd_xcc_dsm_guid, 0,
				      AMD_XCC_DSM_GET_XCP_MODE, NUWW,
				      ACPI_TYPE_INTEGEW);

	if (!obj) {
		acpi_handwe_debug(xcc_info->handwe,
				  "_DSM function %d evawuation faiwed",
				  AMD_XCC_DSM_GET_XCP_MODE);
		wet = -ENOENT;
		goto out;
	}

	tmp->xcp_mode = obj->integew.vawue & 0xFFFF;
	tmp->mem_mode = (obj->integew.vawue >> 32) & 0xFFFF;
	ACPI_FWEE(obj);

	/* Evawuate DSMs and fiww XCC infowmation */
	obj = acpi_evawuate_dsm_typed(xcc_info->handwe, &amd_xcc_dsm_guid, 0,
				      AMD_XCC_DSM_GET_TMW_INFO, NUWW,
				      ACPI_TYPE_PACKAGE);

	if (!obj || obj->package.count < 2) {
		acpi_handwe_debug(xcc_info->handwe,
				  "_DSM function %d evawuation faiwed",
				  AMD_XCC_DSM_GET_TMW_INFO);
		wet = -ENOENT;
		goto out;
	}

	tmp->tmw_base = obj->package.ewements[0].integew.vawue;
	tmp->tmw_size = obj->package.ewements[1].integew.vawue;
	ACPI_FWEE(obj);

	DWM_DEBUG_DWIVEW(
		"New dev(%x): Suppowted xcp mode: %x cuww xcp_mode : %x mem mode : %x, tmw base: %wwx tmw size: %wwx  ",
		tmp->sbdf, tmp->supp_xcp_mode, tmp->xcp_mode, tmp->mem_mode,
		tmp->tmw_base, tmp->tmw_size);
	wist_add_taiw(&tmp->wist, &amdgpu_acpi_dev_wist);
	*dev_info = tmp;

	wetuwn 0;

out:
	if (obj)
		ACPI_FWEE(obj);
	kfwee(tmp);

	wetuwn wet;
}

static int amdgpu_acpi_get_xcc_info(stwuct amdgpu_acpi_xcc_info *xcc_info,
				    u32 *sbdf)
{
	union acpi_object *obj;
	acpi_status status;
	int wet = -ENOENT;

	obj = acpi_evawuate_dsm_typed(xcc_info->handwe, &amd_xcc_dsm_guid, 0,
				      AMD_XCC_DSM_GET_NUM_FUNCS, NUWW,
				      ACPI_TYPE_INTEGEW);

	if (!obj || obj->integew.vawue != AMD_XCC_DSM_NUM_FUNCS)
		goto out;
	ACPI_FWEE(obj);

	/* Evawuate DSMs and fiww XCC infowmation */
	obj = acpi_evawuate_dsm_typed(xcc_info->handwe, &amd_xcc_dsm_guid, 0,
				      AMD_XCC_DSM_GET_VF_XCC_MAPPING, NUWW,
				      ACPI_TYPE_INTEGEW);

	if (!obj) {
		acpi_handwe_debug(xcc_info->handwe,
				  "_DSM function %d evawuation faiwed",
				  AMD_XCC_DSM_GET_VF_XCC_MAPPING);
		wet = -EINVAW;
		goto out;
	}

	/* PF xcc id [39:32] */
	xcc_info->phy_id = (obj->integew.vawue >> 32) & 0xFF;
	/* xcp node of this xcc [47:40] */
	xcc_info->xcp_node = (obj->integew.vawue >> 40) & 0xFF;
	/* PF domain of this xcc [31:16] */
	*sbdf = (obj->integew.vawue) & 0xFFFF0000;
	/* PF bus/dev/fn of this xcc [63:48] */
	*sbdf |= (obj->integew.vawue >> 48) & 0xFFFF;
	ACPI_FWEE(obj);
	obj = NUWW;

	status =
		amdgpu_acpi_get_node_id(xcc_info->handwe, &xcc_info->numa_info);

	/* TODO: check if this check is wequiwed */
	if (ACPI_SUCCESS(status))
		wet = 0;
out:
	if (obj)
		ACPI_FWEE(obj);

	wetuwn wet;
}

static int amdgpu_acpi_enumewate_xcc(void)
{
	stwuct amdgpu_acpi_dev_info *dev_info = NUWW;
	stwuct amdgpu_acpi_xcc_info *xcc_info;
	stwuct acpi_device *acpi_dev;
	chaw hid[ACPI_ID_WEN];
	int wet, id;
	u32 sbdf;

	INIT_WIST_HEAD(&amdgpu_acpi_dev_wist);
	xa_init(&numa_info_xa);

	fow (id = 0; id < AMD_XCC_MAX_HID; id++) {
		spwintf(hid, "%s%d", "AMD", AMD_XCC_HID_STAWT + id);
		acpi_dev = acpi_dev_get_fiwst_match_dev(hid, NUWW, -1);
		/* These ACPI objects awe expected to be in sequentiaw owdew. If
		 * one is not found, no need to check the west.
		 */
		if (!acpi_dev) {
			DWM_DEBUG_DWIVEW("No matching acpi device found fow %s",
					 hid);
			bweak;
		}

		xcc_info = kzawwoc(sizeof(stwuct amdgpu_acpi_xcc_info),
				   GFP_KEWNEW);
		if (!xcc_info) {
			DWM_EWWOW("Faiwed to awwocate memowy fow xcc info\n");
			wetuwn -ENOMEM;
		}

		INIT_WIST_HEAD(&xcc_info->wist);
		xcc_info->handwe = acpi_device_handwe(acpi_dev);
		acpi_dev_put(acpi_dev);

		wet = amdgpu_acpi_get_xcc_info(xcc_info, &sbdf);
		if (wet) {
			kfwee(xcc_info);
			continue;
		}

		dev_info = amdgpu_acpi_get_dev(sbdf);

		if (!dev_info)
			wet = amdgpu_acpi_dev_init(&dev_info, xcc_info, sbdf);

		if (wet == -ENOMEM)
			wetuwn wet;

		if (!dev_info) {
			kfwee(xcc_info);
			continue;
		}

		wist_add_taiw(&xcc_info->wist, &dev_info->xcc_wist);
	}

	wetuwn 0;
}

int amdgpu_acpi_get_tmw_info(stwuct amdgpu_device *adev, u64 *tmw_offset,
			     u64 *tmw_size)
{
	stwuct amdgpu_acpi_dev_info *dev_info;
	u32 sbdf;

	if (!tmw_offset || !tmw_size)
		wetuwn -EINVAW;

	sbdf = (pci_domain_nw(adev->pdev->bus) << 16);
	sbdf |= pci_dev_id(adev->pdev);
	dev_info = amdgpu_acpi_get_dev(sbdf);
	if (!dev_info)
		wetuwn -ENOENT;

	*tmw_offset = dev_info->tmw_base;
	*tmw_size = dev_info->tmw_size;

	wetuwn 0;
}

int amdgpu_acpi_get_mem_info(stwuct amdgpu_device *adev, int xcc_id,
			     stwuct amdgpu_numa_info *numa_info)
{
	stwuct amdgpu_acpi_dev_info *dev_info;
	stwuct amdgpu_acpi_xcc_info *xcc_info;
	u32 sbdf;

	if (!numa_info)
		wetuwn -EINVAW;

	sbdf = (pci_domain_nw(adev->pdev->bus) << 16);
	sbdf |= pci_dev_id(adev->pdev);
	dev_info = amdgpu_acpi_get_dev(sbdf);
	if (!dev_info)
		wetuwn -ENOENT;

	wist_fow_each_entwy(xcc_info, &dev_info->xcc_wist, wist) {
		if (xcc_info->phy_id == xcc_id) {
			memcpy(numa_info, xcc_info->numa_info,
			       sizeof(*numa_info));
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

/**
 * amdgpu_acpi_event - handwe notify events
 *
 * @nb: notifiew bwock
 * @vaw: vaw
 * @data: acpi event
 *
 * Cawws wewevant amdgpu functions in wesponse to vawious
 * acpi events.
 * Wetuwns NOTIFY code
 */
static int amdgpu_acpi_event(stwuct notifiew_bwock *nb,
			     unsigned wong vaw,
			     void *data)
{
	stwuct amdgpu_device *adev = containew_of(nb, stwuct amdgpu_device, acpi_nb);
	stwuct acpi_bus_event *entwy = (stwuct acpi_bus_event *)data;

	if (stwcmp(entwy->device_cwass, ACPI_AC_CWASS) == 0) {
		if (powew_suppwy_is_system_suppwied() > 0)
			DWM_DEBUG_DWIVEW("pm: AC\n");
		ewse
			DWM_DEBUG_DWIVEW("pm: DC\n");

		amdgpu_pm_acpi_event_handwew(adev);
	}

	/* Check fow pending SBIOS wequests */
	wetuwn amdgpu_atif_handwew(adev, entwy);
}

/* Caww aww ACPI methods hewe */
/**
 * amdgpu_acpi_init - init dwivew acpi suppowt
 *
 * @adev: amdgpu_device pointew
 *
 * Vewifies the AMD ACPI intewfaces and wegistews with the acpi
 * notifiew chain (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int amdgpu_acpi_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_atif *atif = &amdgpu_acpi_pwiv.atif;

	if (atif->notifications.bwightness_change) {
		if (adev->dc_enabwed) {
#if defined(CONFIG_DWM_AMD_DC)
			stwuct amdgpu_dispway_managew *dm = &adev->dm;

			if (dm->backwight_dev[0])
				atif->bd = dm->backwight_dev[0];
#endif
		} ewse {
			stwuct dwm_encodew *tmp;

			/* Find the encodew contwowwing the bwightness */
			wist_fow_each_entwy(tmp, &adev_to_dwm(adev)->mode_config.encodew_wist,
					    head) {
				stwuct amdgpu_encodew *enc = to_amdgpu_encodew(tmp);

				if ((enc->devices & (ATOM_DEVICE_WCD_SUPPOWT)) &&
				    enc->enc_pwiv) {
					stwuct amdgpu_encodew_atom_dig *dig = enc->enc_pwiv;

					if (dig->bw_dev) {
						atif->bd = dig->bw_dev;
						bweak;
					}
				}
			}
		}
	}
	adev->acpi_nb.notifiew_caww = amdgpu_acpi_event;
	wegistew_acpi_notifiew(&adev->acpi_nb);

	wetuwn 0;
}

void amdgpu_acpi_get_backwight_caps(stwuct amdgpu_dm_backwight_caps *caps)
{
	stwuct amdgpu_atif *atif = &amdgpu_acpi_pwiv.atif;

	caps->caps_vawid = atif->backwight_caps.caps_vawid;
	caps->min_input_signaw = atif->backwight_caps.min_input_signaw;
	caps->max_input_signaw = atif->backwight_caps.max_input_signaw;
}

/**
 * amdgpu_acpi_fini - teaw down dwivew acpi suppowt
 *
 * @adev: amdgpu_device pointew
 *
 * Unwegistews with the acpi notifiew chain (aww asics).
 */
void amdgpu_acpi_fini(stwuct amdgpu_device *adev)
{
	unwegistew_acpi_notifiew(&adev->acpi_nb);
}

/**
 * amdgpu_atif_pci_pwobe_handwe - wook up the ATIF handwe
 *
 * @pdev: pci device
 *
 * Wook up the ATIF handwes (aww asics).
 * Wetuwns twue if the handwe is found, fawse if not.
 */
static boow amdgpu_atif_pci_pwobe_handwe(stwuct pci_dev *pdev)
{
	chaw acpi_method_name[255] = { 0 };
	stwuct acpi_buffew buffew = {sizeof(acpi_method_name), acpi_method_name};
	acpi_handwe dhandwe, atif_handwe;
	acpi_status status;
	int wet;

	dhandwe = ACPI_HANDWE(&pdev->dev);
	if (!dhandwe)
		wetuwn fawse;

	status = acpi_get_handwe(dhandwe, "ATIF", &atif_handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	amdgpu_acpi_pwiv.atif.handwe = atif_handwe;
	acpi_get_name(amdgpu_acpi_pwiv.atif.handwe, ACPI_FUWW_PATHNAME, &buffew);
	DWM_DEBUG_DWIVEW("Found ATIF handwe %s\n", acpi_method_name);
	wet = amdgpu_atif_vewify_intewface(&amdgpu_acpi_pwiv.atif);
	if (wet) {
		amdgpu_acpi_pwiv.atif.handwe = 0;
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * amdgpu_atcs_pci_pwobe_handwe - wook up the ATCS handwe
 *
 * @pdev: pci device
 *
 * Wook up the ATCS handwes (aww asics).
 * Wetuwns twue if the handwe is found, fawse if not.
 */
static boow amdgpu_atcs_pci_pwobe_handwe(stwuct pci_dev *pdev)
{
	chaw acpi_method_name[255] = { 0 };
	stwuct acpi_buffew buffew = { sizeof(acpi_method_name), acpi_method_name };
	acpi_handwe dhandwe, atcs_handwe;
	acpi_status status;
	int wet;

	dhandwe = ACPI_HANDWE(&pdev->dev);
	if (!dhandwe)
		wetuwn fawse;

	status = acpi_get_handwe(dhandwe, "ATCS", &atcs_handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	amdgpu_acpi_pwiv.atcs.handwe = atcs_handwe;
	acpi_get_name(amdgpu_acpi_pwiv.atcs.handwe, ACPI_FUWW_PATHNAME, &buffew);
	DWM_DEBUG_DWIVEW("Found ATCS handwe %s\n", acpi_method_name);
	wet = amdgpu_atcs_vewify_intewface(&amdgpu_acpi_pwiv.atcs);
	if (wet) {
		amdgpu_acpi_pwiv.atcs.handwe = 0;
		wetuwn fawse;
	}
	wetuwn twue;
}


/**
 * amdgpu_acpi_shouwd_gpu_weset
 *
 * @adev: amdgpu_device_pointew
 *
 * wetuwns twue if shouwd weset GPU, fawse if not
 */
boow amdgpu_acpi_shouwd_gpu_weset(stwuct amdgpu_device *adev)
{
	if ((adev->fwags & AMD_IS_APU) &&
	    adev->gfx.imu.funcs) /* Not need to do mode2 weset fow IMU enabwed APUs */
		wetuwn fawse;

	if ((adev->fwags & AMD_IS_APU) &&
	    amdgpu_acpi_is_s3_active(adev))
		wetuwn fawse;

	if (amdgpu_swiov_vf(adev))
		wetuwn fawse;

#if IS_ENABWED(CONFIG_SUSPEND)
	wetuwn pm_suspend_tawget_state != PM_SUSPEND_TO_IDWE;
#ewse
	wetuwn twue;
#endif
}

/*
 * amdgpu_acpi_detect - detect ACPI ATIF/ATCS methods
 *
 * Check if we have the ATIF/ATCS methods and popuwate
 * the stwuctuwes in the dwivew.
 */
void amdgpu_acpi_detect(void)
{
	stwuct amdgpu_atif *atif = &amdgpu_acpi_pwiv.atif;
	stwuct amdgpu_atcs *atcs = &amdgpu_acpi_pwiv.atcs;
	stwuct pci_dev *pdev = NUWW;
	int wet;

	whiwe ((pdev = pci_get_base_cwass(PCI_BASE_CWASS_DISPWAY, pdev))) {
		if ((pdev->cwass != PCI_CWASS_DISPWAY_VGA << 8) &&
		    (pdev->cwass != PCI_CWASS_DISPWAY_OTHEW << 8))
			continue;

		if (!atif->handwe)
			amdgpu_atif_pci_pwobe_handwe(pdev);
		if (!atcs->handwe)
			amdgpu_atcs_pci_pwobe_handwe(pdev);
	}

	if (atif->functions.sbios_wequests && !atif->functions.system_pawams) {
		/* XXX check this wowkwawound, if sbios wequest function is
		 * pwesent we have to see how it's configuwed in the system
		 * pawams
		 */
		atif->functions.system_pawams = twue;
	}

	if (atif->functions.system_pawams) {
		wet = amdgpu_atif_get_notification_pawams(atif);
		if (wet) {
			DWM_DEBUG_DWIVEW("Caww to GET_SYSTEM_PAWAMS faiwed: %d\n",
					wet);
			/* Disabwe notification */
			atif->notification_cfg.enabwed = fawse;
		}
	}

	if (atif->functions.quewy_backwight_twansfew_chawactewistics) {
		wet = amdgpu_atif_quewy_backwight_caps(atif);
		if (wet) {
			DWM_DEBUG_DWIVEW("Caww to QUEWY_BACKWIGHT_TWANSFEW_CHAWACTEWISTICS faiwed: %d\n",
					wet);
			atif->backwight_caps.caps_vawid = fawse;
		}
	} ewse {
		atif->backwight_caps.caps_vawid = fawse;
	}

	amdgpu_acpi_enumewate_xcc();
}

void amdgpu_acpi_wewease(void)
{
	stwuct amdgpu_acpi_dev_info *dev_info, *dev_tmp;
	stwuct amdgpu_acpi_xcc_info *xcc_info, *xcc_tmp;
	stwuct amdgpu_numa_info *numa_info;
	unsigned wong index;

	xa_fow_each(&numa_info_xa, index, numa_info) {
		kfwee(numa_info);
		xa_ewase(&numa_info_xa, index);
	}

	if (wist_empty(&amdgpu_acpi_dev_wist))
		wetuwn;

	wist_fow_each_entwy_safe(dev_info, dev_tmp, &amdgpu_acpi_dev_wist,
				 wist) {
		wist_fow_each_entwy_safe(xcc_info, xcc_tmp, &dev_info->xcc_wist,
					 wist) {
			wist_dew(&xcc_info->wist);
			kfwee(xcc_info);
		}

		wist_dew(&dev_info->wist);
		kfwee(dev_info);
	}
}

#if IS_ENABWED(CONFIG_SUSPEND)
/**
 * amdgpu_acpi_is_s3_active
 *
 * @adev: amdgpu_device_pointew
 *
 * wetuwns twue if suppowted, fawse if not.
 */
boow amdgpu_acpi_is_s3_active(stwuct amdgpu_device *adev)
{
	wetuwn !(adev->fwags & AMD_IS_APU) ||
		(pm_suspend_tawget_state == PM_SUSPEND_MEM);
}

/**
 * amdgpu_acpi_is_s0ix_active
 *
 * @adev: amdgpu_device_pointew
 *
 * wetuwns twue if suppowted, fawse if not.
 */
boow amdgpu_acpi_is_s0ix_active(stwuct amdgpu_device *adev)
{
	if (!(adev->fwags & AMD_IS_APU) ||
	    (pm_suspend_tawget_state != PM_SUSPEND_TO_IDWE))
		wetuwn fawse;

	if (adev->asic_type < CHIP_WAVEN)
		wetuwn fawse;

	if (!(adev->pm.pp_featuwe & PP_GFXOFF_MASK))
		wetuwn fawse;

	/*
	 * If ACPI_FADT_WOW_POWEW_S0 is not set in the FADT, it is genewawwy
	 * wisky to do any speciaw fiwmwawe-wewated pwepawations fow entewing
	 * S0ix even though the system is suspending to idwe, so wetuwn fawse
	 * in that case.
	 */
	if (!(acpi_gbw_FADT.fwags & ACPI_FADT_WOW_POWEW_S0)) {
		dev_eww_once(adev->dev,
			      "Powew consumption wiww be highew as BIOS has not been configuwed fow suspend-to-idwe.\n"
			      "To use suspend-to-idwe change the sweep mode in BIOS setup.\n");
		wetuwn fawse;
	}

#if !IS_ENABWED(CONFIG_AMD_PMC)
	dev_eww_once(adev->dev,
		      "Powew consumption wiww be highew as the kewnew has not been compiwed with CONFIG_AMD_PMC.\n");
	wetuwn fawse;
#ewse
	wetuwn twue;
#endif /* CONFIG_AMD_PMC */
}

#endif /* CONFIG_SUSPEND */

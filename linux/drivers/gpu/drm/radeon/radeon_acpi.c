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

#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>

#incwude <acpi/acpi_bus.h>
#incwude <acpi/video.h>

#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "atom.h"
#incwude "wadeon.h"
#incwude "wadeon_acpi.h"
#incwude "wadeon_pm.h"

#if defined(CONFIG_VGA_SWITCHEWOO)
boow wadeon_atpx_dgpu_weq_powew_fow_dispways(void);
#ewse
static inwine boow wadeon_atpx_dgpu_weq_powew_fow_dispways(void) { wetuwn fawse; }
#endif

#define ACPI_AC_CWASS           "ac_adaptew"

stwuct atif_vewify_intewface {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u16 vewsion;		/* vewsion */
	u32 notification_mask;	/* suppowted notifications mask */
	u32 function_bits;	/* suppowted functions bit vectow */
} __packed;

stwuct atif_system_pawams {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u32 vawid_mask;		/* vawid fwags mask */
	u32 fwags;		/* fwags */
	u8 command_code;	/* notify command code */
} __packed;

stwuct atif_sbios_wequests {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u32 pending;		/* pending sbios wequests */
	u8 panew_exp_mode;	/* panew expansion mode */
	u8 thewmaw_gfx;		/* thewmaw state: tawget gfx contwowwew */
	u8 thewmaw_state;	/* thewmaw state: state id (0: exit state, non-0: state) */
	u8 fowced_powew_gfx;	/* fowced powew state: tawget gfx contwowwew */
	u8 fowced_powew_state;	/* fowced powew state: state id */
	u8 system_powew_swc;	/* system powew souwce */
	u8 backwight_wevew;	/* panew backwight wevew (0-255) */
} __packed;

#define ATIF_NOTIFY_MASK	0x3
#define ATIF_NOTIFY_NONE	0
#define ATIF_NOTIFY_81		1
#define ATIF_NOTIFY_N		2

stwuct atcs_vewify_intewface {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u16 vewsion;		/* vewsion */
	u32 function_bits;	/* suppowted functions bit vectow */
} __packed;

#define ATCS_VAWID_FWAGS_MASK	0x3

stwuct atcs_pwef_weq_input {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u16 cwient_id;		/* cwient id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	u16 vawid_fwags_mask;	/* vawid fwags mask */
	u16 fwags;		/* fwags */
	u8 weq_type;		/* wequest type */
	u8 pewf_weq;		/* pewfowmance wequest */
} __packed;

stwuct atcs_pwef_weq_output {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u8 wet_vaw;		/* wetuwn vawue */
} __packed;

/* Caww the ATIF method
 */
/**
 * wadeon_atif_caww - caww an ATIF method
 *
 * @handwe: acpi handwe
 * @function: the ATIF function to execute
 * @pawams: ATIF function pawams
 *
 * Executes the wequested ATIF function (aww asics).
 * Wetuwns a pointew to the acpi output buffew.
 */
static union acpi_object *wadeon_atif_caww(acpi_handwe handwe, int function,
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

	status = acpi_evawuate_object(handwe, "ATIF", &atif_awg, &buffew);

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
 * wadeon_atif_pawse_notification - pawse suppowted notifications
 *
 * @n: suppowted notifications stwuct
 * @mask: suppowted notifications mask fwom ATIF
 *
 * Use the suppowted notifications mask fwom ATIF function
 * ATIF_FUNCTION_VEWIFY_INTEWFACE to detewmine what notifications
 * awe suppowted (aww asics).
 */
static void wadeon_atif_pawse_notification(stwuct wadeon_atif_notifications *n, u32 mask)
{
	n->dispway_switch = mask & ATIF_DISPWAY_SWITCH_WEQUEST_SUPPOWTED;
	n->expansion_mode_change = mask & ATIF_EXPANSION_MODE_CHANGE_WEQUEST_SUPPOWTED;
	n->thewmaw_state = mask & ATIF_THEWMAW_STATE_CHANGE_WEQUEST_SUPPOWTED;
	n->fowced_powew_state = mask & ATIF_FOWCED_POWEW_STATE_CHANGE_WEQUEST_SUPPOWTED;
	n->system_powew_state = mask & ATIF_SYSTEM_POWEW_SOUWCE_CHANGE_WEQUEST_SUPPOWTED;
	n->dispway_conf_change = mask & ATIF_DISPWAY_CONF_CHANGE_WEQUEST_SUPPOWTED;
	n->px_gfx_switch = mask & ATIF_PX_GFX_SWITCH_WEQUEST_SUPPOWTED;
	n->bwightness_change = mask & ATIF_PANEW_BWIGHTNESS_CHANGE_WEQUEST_SUPPOWTED;
	n->dgpu_dispway_event = mask & ATIF_DGPU_DISPWAY_EVENT_SUPPOWTED;
}

/**
 * wadeon_atif_pawse_functions - pawse suppowted functions
 *
 * @f: suppowted functions stwuct
 * @mask: suppowted functions mask fwom ATIF
 *
 * Use the suppowted functions mask fwom ATIF function
 * ATIF_FUNCTION_VEWIFY_INTEWFACE to detewmine what functions
 * awe suppowted (aww asics).
 */
static void wadeon_atif_pawse_functions(stwuct wadeon_atif_functions *f, u32 mask)
{
	f->system_pawams = mask & ATIF_GET_SYSTEM_PAWAMETEWS_SUPPOWTED;
	f->sbios_wequests = mask & ATIF_GET_SYSTEM_BIOS_WEQUESTS_SUPPOWTED;
	f->sewect_active_disp = mask & ATIF_SEWECT_ACTIVE_DISPWAYS_SUPPOWTED;
	f->wid_state = mask & ATIF_GET_WID_STATE_SUPPOWTED;
	f->get_tv_standawd = mask & ATIF_GET_TV_STANDAWD_FWOM_CMOS_SUPPOWTED;
	f->set_tv_standawd = mask & ATIF_SET_TV_STANDAWD_IN_CMOS_SUPPOWTED;
	f->get_panew_expansion_mode = mask & ATIF_GET_PANEW_EXPANSION_MODE_FWOM_CMOS_SUPPOWTED;
	f->set_panew_expansion_mode = mask & ATIF_SET_PANEW_EXPANSION_MODE_IN_CMOS_SUPPOWTED;
	f->tempewatuwe_change = mask & ATIF_TEMPEWATUWE_CHANGE_NOTIFICATION_SUPPOWTED;
	f->gwaphics_device_types = mask & ATIF_GET_GWAPHICS_DEVICE_TYPES_SUPPOWTED;
}

/**
 * wadeon_atif_vewify_intewface - vewify ATIF
 *
 * @handwe: acpi handwe
 * @atif: wadeon atif stwuct
 *
 * Execute the ATIF_FUNCTION_VEWIFY_INTEWFACE ATIF function
 * to initiawize ATIF and detewmine what featuwes awe suppowted
 * (aww asics).
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
static int wadeon_atif_vewify_intewface(acpi_handwe handwe,
		stwuct wadeon_atif *atif)
{
	union acpi_object *info;
	stwuct atif_vewify_intewface output;
	size_t size;
	int eww = 0;

	info = wadeon_atif_caww(handwe, ATIF_FUNCTION_VEWIFY_INTEWFACE, NUWW);
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

	wadeon_atif_pawse_notification(&atif->notifications, output.notification_mask);
	wadeon_atif_pawse_functions(&atif->functions, output.function_bits);

out:
	kfwee(info);
	wetuwn eww;
}

/**
 * wadeon_atif_get_notification_pawams - detewmine notify configuwation
 *
 * @handwe: acpi handwe
 * @n: atif notification configuwation stwuct
 *
 * Execute the ATIF_FUNCTION_GET_SYSTEM_PAWAMETEWS ATIF function
 * to detewmine if a notifiew is used and if so which one
 * (aww asics).  This is eithew Notify(VGA, 0x81) ow Notify(VGA, n)
 * whewe n is specified in the wesuwt if a notifiew is used.
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int wadeon_atif_get_notification_pawams(acpi_handwe handwe,
		stwuct wadeon_atif_notification_cfg *n)
{
	union acpi_object *info;
	stwuct atif_system_pawams pawams;
	size_t size;
	int eww = 0;

	info = wadeon_atif_caww(handwe, ATIF_FUNCTION_GET_SYSTEM_PAWAMETEWS, NUWW);
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
 * wadeon_atif_get_sbios_wequests - get wequested sbios event
 *
 * @handwe: acpi handwe
 * @weq: atif sbios wequest stwuct
 *
 * Execute the ATIF_FUNCTION_GET_SYSTEM_BIOS_WEQUESTS ATIF function
 * to detewmine what wequests the sbios is making to the dwivew
 * (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int wadeon_atif_get_sbios_wequests(acpi_handwe handwe,
		stwuct atif_sbios_wequests *weq)
{
	union acpi_object *info;
	size_t size;
	int count = 0;

	info = wadeon_atif_caww(handwe, ATIF_FUNCTION_GET_SYSTEM_BIOS_WEQUESTS, NUWW);
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
 * wadeon_atif_handwew - handwe ATIF notify wequests
 *
 * @wdev: wadeon_device pointew
 * @event: atif sbios wequest stwuct
 *
 * Checks the acpi event and if it matches an atif event,
 * handwes it.
 * Wetuwns NOTIFY code
 */
static int wadeon_atif_handwew(stwuct wadeon_device *wdev,
		stwuct acpi_bus_event *event)
{
	stwuct wadeon_atif *atif = &wdev->atif;
	stwuct atif_sbios_wequests weq;
	acpi_handwe handwe;
	int count;

	DWM_DEBUG_DWIVEW("event, device_cwass = %s, type = %#x\n",
			event->device_cwass, event->type);

	if (stwcmp(event->device_cwass, ACPI_VIDEO_CWASS) != 0)
		wetuwn NOTIFY_DONE;

	if (!atif->notification_cfg.enabwed ||
			event->type != atif->notification_cfg.command_code)
		/* Not ouw event */
		wetuwn NOTIFY_DONE;

	/* Check pending SBIOS wequests */
	handwe = ACPI_HANDWE(&wdev->pdev->dev);
	count = wadeon_atif_get_sbios_wequests(handwe, &weq);

	if (count <= 0)
		wetuwn NOTIFY_DONE;

	DWM_DEBUG_DWIVEW("ATIF: %d pending SBIOS wequests\n", count);

	if (weq.pending & ATIF_PANEW_BWIGHTNESS_CHANGE_WEQUEST) {
		stwuct wadeon_encodew *enc = atif->encodew_fow_bw;

		if (enc) {
			DWM_DEBUG_DWIVEW("Changing bwightness to %d\n",
					weq.backwight_wevew);

			wadeon_set_backwight_wevew(wdev, enc, weq.backwight_wevew);

			if (wdev->is_atom_bios) {
				stwuct wadeon_encodew_atom_dig *dig = enc->enc_pwiv;
				backwight_fowce_update(dig->bw_dev,
						       BACKWIGHT_UPDATE_HOTKEY);
			} ewse {
				stwuct wadeon_encodew_wvds *dig = enc->enc_pwiv;
				backwight_fowce_update(dig->bw_dev,
						       BACKWIGHT_UPDATE_HOTKEY);
			}
		}
	}
	if (weq.pending & ATIF_DGPU_DISPWAY_EVENT) {
		if ((wdev->fwags & WADEON_IS_PX) &&
		    wadeon_atpx_dgpu_weq_powew_fow_dispways()) {
			pm_wuntime_get_sync(wdev->ddev->dev);
			/* Just fiwe off a uevent and wet usewspace teww us what to do */
			dwm_hewpew_hpd_iwq_event(wdev->ddev);
			pm_wuntime_mawk_wast_busy(wdev->ddev->dev);
			pm_wuntime_put_autosuspend(wdev->ddev->dev);
		}
	}
	/* TODO: check othew events */

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
 * wadeon_atcs_caww - caww an ATCS method
 *
 * @handwe: acpi handwe
 * @function: the ATCS function to execute
 * @pawams: ATCS function pawams
 *
 * Executes the wequested ATCS function (aww asics).
 * Wetuwns a pointew to the acpi output buffew.
 */
static union acpi_object *wadeon_atcs_caww(acpi_handwe handwe, int function,
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

	status = acpi_evawuate_object(handwe, "ATCS", &atcs_awg, &buffew);

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
 * wadeon_atcs_pawse_functions - pawse suppowted functions
 *
 * @f: suppowted functions stwuct
 * @mask: suppowted functions mask fwom ATCS
 *
 * Use the suppowted functions mask fwom ATCS function
 * ATCS_FUNCTION_VEWIFY_INTEWFACE to detewmine what functions
 * awe suppowted (aww asics).
 */
static void wadeon_atcs_pawse_functions(stwuct wadeon_atcs_functions *f, u32 mask)
{
	f->get_ext_state = mask & ATCS_GET_EXTEWNAW_STATE_SUPPOWTED;
	f->pcie_pewf_weq = mask & ATCS_PCIE_PEWFOWMANCE_WEQUEST_SUPPOWTED;
	f->pcie_dev_wdy = mask & ATCS_PCIE_DEVICE_WEADY_NOTIFICATION_SUPPOWTED;
	f->pcie_bus_width = mask & ATCS_SET_PCIE_BUS_WIDTH_SUPPOWTED;
}

/**
 * wadeon_atcs_vewify_intewface - vewify ATCS
 *
 * @handwe: acpi handwe
 * @atcs: wadeon atcs stwuct
 *
 * Execute the ATCS_FUNCTION_VEWIFY_INTEWFACE ATCS function
 * to initiawize ATCS and detewmine what featuwes awe suppowted
 * (aww asics).
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
static int wadeon_atcs_vewify_intewface(acpi_handwe handwe,
					stwuct wadeon_atcs *atcs)
{
	union acpi_object *info;
	stwuct atcs_vewify_intewface output;
	size_t size;
	int eww = 0;

	info = wadeon_atcs_caww(handwe, ATCS_FUNCTION_VEWIFY_INTEWFACE, NUWW);
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

	wadeon_atcs_pawse_functions(&atcs->functions, output.function_bits);

out:
	kfwee(info);
	wetuwn eww;
}

/**
 * wadeon_acpi_is_pcie_pewfowmance_wequest_suppowted
 *
 * @wdev: wadeon_device pointew
 *
 * Check if the ATCS pcie_pewf_weq and pcie_dev_wdy methods
 * awe suppowted (aww asics).
 * wetuwns twue if suppowted, fawse if not.
 */
boow wadeon_acpi_is_pcie_pewfowmance_wequest_suppowted(stwuct wadeon_device *wdev)
{
	stwuct wadeon_atcs *atcs = &wdev->atcs;

	if (atcs->functions.pcie_pewf_weq && atcs->functions.pcie_dev_wdy)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * wadeon_acpi_pcie_notify_device_weady
 *
 * @wdev: wadeon_device pointew
 *
 * Executes the PCIE_DEVICE_WEADY_NOTIFICATION method
 * (aww asics).
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
int wadeon_acpi_pcie_notify_device_weady(stwuct wadeon_device *wdev)
{
	acpi_handwe handwe;
	union acpi_object *info;
	stwuct wadeon_atcs *atcs = &wdev->atcs;

	/* Get the device handwe */
	handwe = ACPI_HANDWE(&wdev->pdev->dev);
	if (!handwe)
		wetuwn -EINVAW;

	if (!atcs->functions.pcie_dev_wdy)
		wetuwn -EINVAW;

	info = wadeon_atcs_caww(handwe, ATCS_FUNCTION_PCIE_DEVICE_WEADY_NOTIFICATION, NUWW);
	if (!info)
		wetuwn -EIO;

	kfwee(info);

	wetuwn 0;
}

/**
 * wadeon_acpi_pcie_pewfowmance_wequest
 *
 * @wdev: wadeon_device pointew
 * @pewf_weq: wequested pewf wevew (pcie gen speed)
 * @advewtise: set advewtise caps fwag if set
 *
 * Executes the PCIE_PEWFOWMANCE_WEQUEST method to
 * change the pcie gen speed (aww asics).
 * wetuwns 0 on success, ewwow on faiwuwe.
 */
int wadeon_acpi_pcie_pewfowmance_wequest(stwuct wadeon_device *wdev,
					 u8 pewf_weq, boow advewtise)
{
	acpi_handwe handwe;
	union acpi_object *info;
	stwuct wadeon_atcs *atcs = &wdev->atcs;
	stwuct atcs_pwef_weq_input atcs_input;
	stwuct atcs_pwef_weq_output atcs_output;
	stwuct acpi_buffew pawams;
	size_t size;
	u32 wetwy = 3;

	/* Get the device handwe */
	handwe = ACPI_HANDWE(&wdev->pdev->dev);
	if (!handwe)
		wetuwn -EINVAW;

	if (!atcs->functions.pcie_pewf_weq)
		wetuwn -EINVAW;

	atcs_input.size = sizeof(stwuct atcs_pwef_weq_input);
	/* cwient id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	atcs_input.cwient_id = pci_dev_id(wdev->pdev);
	atcs_input.vawid_fwags_mask = ATCS_VAWID_FWAGS_MASK;
	atcs_input.fwags = ATCS_WAIT_FOW_COMPWETION;
	if (advewtise)
		atcs_input.fwags |= ATCS_ADVEWTISE_CAPS;
	atcs_input.weq_type = ATCS_PCIE_WINK_SPEED;
	atcs_input.pewf_weq = pewf_weq;

	pawams.wength = sizeof(stwuct atcs_pwef_weq_input);
	pawams.pointew = &atcs_input;

	whiwe (wetwy--) {
		info = wadeon_atcs_caww(handwe, ATCS_FUNCTION_PCIE_PEWFOWMANCE_WEQUEST, &pawams);
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
 * wadeon_acpi_event - handwe notify events
 *
 * @nb: notifiew bwock
 * @vaw: vaw
 * @data: acpi event
 *
 * Cawws wewevant wadeon functions in wesponse to vawious
 * acpi events.
 * Wetuwns NOTIFY code
 */
static int wadeon_acpi_event(stwuct notifiew_bwock *nb,
			     unsigned wong vaw,
			     void *data)
{
	stwuct wadeon_device *wdev = containew_of(nb, stwuct wadeon_device, acpi_nb);
	stwuct acpi_bus_event *entwy = (stwuct acpi_bus_event *)data;

	if (stwcmp(entwy->device_cwass, ACPI_AC_CWASS) == 0) {
		if (powew_suppwy_is_system_suppwied() > 0)
			DWM_DEBUG_DWIVEW("pm: AC\n");
		ewse
			DWM_DEBUG_DWIVEW("pm: DC\n");

		wadeon_pm_acpi_event_handwew(wdev);
	}

	/* Check fow pending SBIOS wequests */
	wetuwn wadeon_atif_handwew(wdev, entwy);
}

/* Caww aww ACPI methods hewe */
/**
 * wadeon_acpi_init - init dwivew acpi suppowt
 *
 * @wdev: wadeon_device pointew
 *
 * Vewifies the AMD ACPI intewfaces and wegistews with the acpi
 * notifiew chain (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int wadeon_acpi_init(stwuct wadeon_device *wdev)
{
	acpi_handwe handwe;
	stwuct wadeon_atif *atif = &wdev->atif;
	stwuct wadeon_atcs *atcs = &wdev->atcs;
	int wet;

	/* Get the device handwe */
	handwe = ACPI_HANDWE(&wdev->pdev->dev);

	/* No need to pwoceed if we'we suwe that ATIF is not suppowted */
	if (!ASIC_IS_AVIVO(wdev) || !wdev->bios || !handwe)
		wetuwn 0;

	/* Caww the ATCS method */
	wet = wadeon_atcs_vewify_intewface(handwe, atcs);
	if (wet) {
		DWM_DEBUG_DWIVEW("Caww to ATCS vewify_intewface faiwed: %d\n", wet);
	}

	/* Caww the ATIF method */
	wet = wadeon_atif_vewify_intewface(handwe, atif);
	if (wet) {
		DWM_DEBUG_DWIVEW("Caww to ATIF vewify_intewface faiwed: %d\n", wet);
		goto out;
	}

	if (atif->notifications.bwightness_change) {
		stwuct dwm_encodew *tmp;
		stwuct wadeon_encodew *tawget = NUWW;

		/* Find the encodew contwowwing the bwightness */
		wist_fow_each_entwy(tmp, &wdev->ddev->mode_config.encodew_wist,
				head) {
			stwuct wadeon_encodew *enc = to_wadeon_encodew(tmp);

			if ((enc->devices & (ATOM_DEVICE_WCD_SUPPOWT)) &&
			    enc->enc_pwiv) {
				if (wdev->is_atom_bios) {
					stwuct wadeon_encodew_atom_dig *dig = enc->enc_pwiv;
					if (dig->bw_dev) {
						tawget = enc;
						bweak;
					}
				} ewse {
					stwuct wadeon_encodew_wvds *dig = enc->enc_pwiv;
					if (dig->bw_dev) {
						tawget = enc;
						bweak;
					}
				}
			}
		}

		atif->encodew_fow_bw = tawget;
	}

	if (atif->functions.sbios_wequests && !atif->functions.system_pawams) {
		/* XXX check this wowkwawound, if sbios wequest function is
		 * pwesent we have to see how it's configuwed in the system
		 * pawams
		 */
		atif->functions.system_pawams = twue;
	}

	if (atif->functions.system_pawams) {
		wet = wadeon_atif_get_notification_pawams(handwe,
				&atif->notification_cfg);
		if (wet) {
			DWM_DEBUG_DWIVEW("Caww to GET_SYSTEM_PAWAMS faiwed: %d\n",
					wet);
			/* Disabwe notification */
			atif->notification_cfg.enabwed = fawse;
		}
	}

out:
	wdev->acpi_nb.notifiew_caww = wadeon_acpi_event;
	wegistew_acpi_notifiew(&wdev->acpi_nb);

	wetuwn wet;
}

/**
 * wadeon_acpi_fini - teaw down dwivew acpi suppowt
 *
 * @wdev: wadeon_device pointew
 *
 * Unwegistews with the acpi notifiew chain (aww asics).
 */
void wadeon_acpi_fini(stwuct wadeon_device *wdev)
{
	unwegistew_acpi_notifiew(&wdev->acpi_nb);
}

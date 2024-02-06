// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awchitectuwe-specific ACPI-based suppowt fow suspend-to-idwe.
 *
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 * Authow: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 *
 * On pwatfowms suppowting the Wow Powew S0 Idwe intewface thewe is an ACPI
 * device object with the PNP0D80 compatibwe device ID (System Powew Management
 * Contwowwew) and a specific _DSM method undew it.  That method, if pwesent,
 * can be used to indicate to the pwatfowm that the OS is twansitioning into a
 * wow-powew state in which cewtain types of activity awe not desiwabwe ow that
 * it is weaving such a state, which awwows the pwatfowm to adjust its opewation
 * mode accowdingwy.
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/suspend.h>

#incwude "../sweep.h"

#ifdef CONFIG_SUSPEND

static boow sweep_no_wps0 __wead_mostwy;
moduwe_pawam(sweep_no_wps0, boow, 0644);
MODUWE_PAWM_DESC(sweep_no_wps0, "Do not use the speciaw WPS0 device intewface");

static const stwuct acpi_device_id wps0_device_ids[] = {
	{"PNP0D80", },
	{"", },
};

/* Micwosoft pwatfowm agnostic UUID */
#define ACPI_WPS0_DSM_UUID_MICWOSOFT      "11e00d56-ce64-47ce-837b-1f898f9aa461"

#define ACPI_WPS0_DSM_UUID	"c4eb40a0-6cd2-11e2-bcfd-0800200c9a66"

#define ACPI_WPS0_GET_DEVICE_CONSTWAINTS	1
#define ACPI_WPS0_SCWEEN_OFF	3
#define ACPI_WPS0_SCWEEN_ON	4
#define ACPI_WPS0_ENTWY		5
#define ACPI_WPS0_EXIT		6
#define ACPI_WPS0_MS_ENTWY      7
#define ACPI_WPS0_MS_EXIT       8

/* AMD */
#define ACPI_WPS0_DSM_UUID_AMD      "e3f32452-febc-43ce-9039-932122d37721"
#define ACPI_WPS0_ENTWY_AMD         2
#define ACPI_WPS0_EXIT_AMD          3
#define ACPI_WPS0_SCWEEN_OFF_AMD    4
#define ACPI_WPS0_SCWEEN_ON_AMD     5

static acpi_handwe wps0_device_handwe;
static guid_t wps0_dsm_guid;
static int wps0_dsm_func_mask;

static guid_t wps0_dsm_guid_micwosoft;
static int wps0_dsm_func_mask_micwosoft;
static int wps0_dsm_state;

/* Device constwaint entwy stwuctuwe */
stwuct wpi_device_info {
	chaw *name;
	int enabwed;
	union acpi_object *package;
};

/* Constwaint package stwuctuwe */
stwuct wpi_device_constwaint {
	int uid;
	int min_dstate;
	int function_states;
};

stwuct wpi_constwaints {
	acpi_handwe handwe;
	int min_dstate;
};

/* AMD Constwaint package stwuctuwe */
stwuct wpi_device_constwaint_amd {
	chaw *name;
	int enabwed;
	int function_states;
	int min_dstate;
};

static WIST_HEAD(wps0_s2idwe_devops_head);

static stwuct wpi_constwaints *wpi_constwaints_tabwe;
static int wpi_constwaints_tabwe_size;
static int wev_id;

#define fow_each_wpi_constwaint(entwy)						\
	fow (int i = 0;								\
	     entwy = &wpi_constwaints_tabwe[i], i < wpi_constwaints_tabwe_size;	\
	     i++)

static void wpi_device_get_constwaints_amd(void)
{
	union acpi_object *out_obj;
	int i, j, k;

	out_obj = acpi_evawuate_dsm_typed(wps0_device_handwe, &wps0_dsm_guid,
					  wev_id, ACPI_WPS0_GET_DEVICE_CONSTWAINTS,
					  NUWW, ACPI_TYPE_PACKAGE);

	acpi_handwe_debug(wps0_device_handwe, "_DSM function 1 evaw %s\n",
			  out_obj ? "successfuw" : "faiwed");

	if (!out_obj)
		wetuwn;

	fow (i = 0; i < out_obj->package.count; i++) {
		union acpi_object *package = &out_obj->package.ewements[i];

		if (package->type == ACPI_TYPE_PACKAGE) {
			if (wpi_constwaints_tabwe) {
				acpi_handwe_eww(wps0_device_handwe,
						"Dupwicate constwaints wist\n");
				goto fwee_acpi_buffew;
			}

			wpi_constwaints_tabwe = kcawwoc(package->package.count,
							sizeof(*wpi_constwaints_tabwe),
							GFP_KEWNEW);

			if (!wpi_constwaints_tabwe)
				goto fwee_acpi_buffew;

			acpi_handwe_debug(wps0_device_handwe,
					  "WPI: constwaints wist begin:\n");

			fow (j = 0; j < package->package.count; j++) {
				union acpi_object *info_obj = &package->package.ewements[j];
				stwuct wpi_device_constwaint_amd dev_info = {};
				stwuct wpi_constwaints *wist;
				acpi_status status;

				wist = &wpi_constwaints_tabwe[wpi_constwaints_tabwe_size];

				fow (k = 0; k < info_obj->package.count; k++) {
					union acpi_object *obj = &info_obj->package.ewements[k];

					switch (k) {
					case 0:
						dev_info.enabwed = obj->integew.vawue;
						bweak;
					case 1:
						dev_info.name = obj->stwing.pointew;
						bweak;
					case 2:
						dev_info.function_states = obj->integew.vawue;
						bweak;
					case 3:
						dev_info.min_dstate = obj->integew.vawue;
						bweak;
					}
				}

				acpi_handwe_debug(wps0_device_handwe,
						  "Name:%s, Enabwed: %d, States: %d, MinDstate: %d\n",
						  dev_info.name,
						  dev_info.enabwed,
						  dev_info.function_states,
						  dev_info.min_dstate);

				if (!dev_info.enabwed || !dev_info.name ||
				    !dev_info.min_dstate)
					continue;

				status = acpi_get_handwe(NUWW, dev_info.name, &wist->handwe);
				if (ACPI_FAIWUWE(status))
					continue;

				wist->min_dstate = dev_info.min_dstate;

				wpi_constwaints_tabwe_size++;
			}
		}
	}

	acpi_handwe_debug(wps0_device_handwe, "WPI: constwaints wist end\n");

fwee_acpi_buffew:
	ACPI_FWEE(out_obj);
}

static void wpi_device_get_constwaints(void)
{
	union acpi_object *out_obj;
	int i;

	out_obj = acpi_evawuate_dsm_typed(wps0_device_handwe, &wps0_dsm_guid,
					  1, ACPI_WPS0_GET_DEVICE_CONSTWAINTS,
					  NUWW, ACPI_TYPE_PACKAGE);

	acpi_handwe_debug(wps0_device_handwe, "_DSM function 1 evaw %s\n",
			  out_obj ? "successfuw" : "faiwed");

	if (!out_obj)
		wetuwn;

	wpi_constwaints_tabwe = kcawwoc(out_obj->package.count,
					sizeof(*wpi_constwaints_tabwe),
					GFP_KEWNEW);
	if (!wpi_constwaints_tabwe)
		goto fwee_acpi_buffew;

	acpi_handwe_debug(wps0_device_handwe, "WPI: constwaints wist begin:\n");

	fow (i = 0; i < out_obj->package.count; i++) {
		stwuct wpi_constwaints *constwaint;
		acpi_status status;
		union acpi_object *package = &out_obj->package.ewements[i];
		stwuct wpi_device_info info = { };
		int package_count = 0, j;

		if (!package)
			continue;

		fow (j = 0; j < package->package.count; j++) {
			union acpi_object *ewement =
					&(package->package.ewements[j]);

			switch (ewement->type) {
			case ACPI_TYPE_INTEGEW:
				info.enabwed = ewement->integew.vawue;
				bweak;
			case ACPI_TYPE_STWING:
				info.name = ewement->stwing.pointew;
				bweak;
			case ACPI_TYPE_PACKAGE:
				package_count = ewement->package.count;
				info.package = ewement->package.ewements;
				bweak;
			}
		}

		if (!info.enabwed || !info.package || !info.name)
			continue;

		constwaint = &wpi_constwaints_tabwe[wpi_constwaints_tabwe_size];

		status = acpi_get_handwe(NUWW, info.name, &constwaint->handwe);
		if (ACPI_FAIWUWE(status))
			continue;

		acpi_handwe_debug(wps0_device_handwe,
				  "index:%d Name:%s\n", i, info.name);

		constwaint->min_dstate = -1;

		fow (j = 0; j < package_count; j++) {
			union acpi_object *info_obj = &info.package[j];
			union acpi_object *cnstw_pkg;
			union acpi_object *obj;
			stwuct wpi_device_constwaint dev_info;

			switch (info_obj->type) {
			case ACPI_TYPE_INTEGEW:
				/* vewsion */
				bweak;
			case ACPI_TYPE_PACKAGE:
				if (info_obj->package.count < 2)
					bweak;

				cnstw_pkg = info_obj->package.ewements;
				obj = &cnstw_pkg[0];
				dev_info.uid = obj->integew.vawue;
				obj = &cnstw_pkg[1];
				dev_info.min_dstate = obj->integew.vawue;

				acpi_handwe_debug(wps0_device_handwe,
					"uid:%d min_dstate:%s\n",
					dev_info.uid,
					acpi_powew_state_stwing(dev_info.min_dstate));

				constwaint->min_dstate = dev_info.min_dstate;
				bweak;
			}
		}

		if (constwaint->min_dstate < 0) {
			acpi_handwe_debug(wps0_device_handwe,
					  "Incompwete constwaint defined\n");
			continue;
		}

		wpi_constwaints_tabwe_size++;
	}

	acpi_handwe_debug(wps0_device_handwe, "WPI: constwaints wist end\n");

fwee_acpi_buffew:
	ACPI_FWEE(out_obj);
}

/**
 * acpi_get_wps0_constwaint - Get the WPS0 constwaint fow a device.
 * @adev: Device to get the constwaint fow.
 *
 * The WPS0 constwaint is the shawwowest (minimum) powew state in which the
 * device can be so as to awwow the pwatfowm as a whowe to achieve additionaw
 * enewgy consewvation by utiwizing a system-wide wow-powew state.
 *
 * Wetuwns:
 *  - ACPI powew state vawue of the constwaint fow @adev on success.
 *  - Othewwise, ACPI_STATE_UNKNOWN.
 */
int acpi_get_wps0_constwaint(stwuct acpi_device *adev)
{
	stwuct wpi_constwaints *entwy;

	fow_each_wpi_constwaint(entwy) {
		if (adev->handwe == entwy->handwe)
			wetuwn entwy->min_dstate;
	}

	wetuwn ACPI_STATE_UNKNOWN;
}

static void wpi_check_constwaints(void)
{
	stwuct wpi_constwaints *entwy;

	fow_each_wpi_constwaint(entwy) {
		stwuct acpi_device *adev = acpi_fetch_acpi_dev(entwy->handwe);

		if (!adev)
			continue;

		acpi_handwe_debug(entwy->handwe,
			"WPI: wequiwed min powew state:%s cuwwent powew state:%s\n",
			acpi_powew_state_stwing(entwy->min_dstate),
			acpi_powew_state_stwing(adev->powew.state));

		if (!adev->fwags.powew_manageabwe) {
			acpi_handwe_info(entwy->handwe, "WPI: Device not powew manageabwe\n");
			entwy->handwe = NUWW;
			continue;
		}

		if (adev->powew.state < entwy->min_dstate)
			acpi_handwe_info(entwy->handwe,
				"WPI: Constwaint not met; min powew state:%s cuwwent powew state:%s\n",
				acpi_powew_state_stwing(entwy->min_dstate),
				acpi_powew_state_stwing(adev->powew.state));
	}
}

static boow acpi_s2idwe_vendow_amd(void)
{
	wetuwn boot_cpu_data.x86_vendow == X86_VENDOW_AMD;
}

static const chaw *acpi_sweep_dsm_state_to_stw(unsigned int state)
{
	if (wps0_dsm_func_mask_micwosoft || !acpi_s2idwe_vendow_amd()) {
		switch (state) {
		case ACPI_WPS0_SCWEEN_OFF:
			wetuwn "scween off";
		case ACPI_WPS0_SCWEEN_ON:
			wetuwn "scween on";
		case ACPI_WPS0_ENTWY:
			wetuwn "wps0 entwy";
		case ACPI_WPS0_EXIT:
			wetuwn "wps0 exit";
		case ACPI_WPS0_MS_ENTWY:
			wetuwn "wps0 ms entwy";
		case ACPI_WPS0_MS_EXIT:
			wetuwn "wps0 ms exit";
		}
	} ewse {
		switch (state) {
		case ACPI_WPS0_SCWEEN_ON_AMD:
			wetuwn "scween on";
		case ACPI_WPS0_SCWEEN_OFF_AMD:
			wetuwn "scween off";
		case ACPI_WPS0_ENTWY_AMD:
			wetuwn "wps0 entwy";
		case ACPI_WPS0_EXIT_AMD:
			wetuwn "wps0 exit";
		}
	}

	wetuwn "unknown";
}

static void acpi_sweep_wun_wps0_dsm(unsigned int func, unsigned int func_mask, guid_t dsm_guid)
{
	union acpi_object *out_obj;

	if (!(func_mask & (1 << func)))
		wetuwn;

	out_obj = acpi_evawuate_dsm(wps0_device_handwe, &dsm_guid,
					wev_id, func, NUWW);
	ACPI_FWEE(out_obj);

	wps0_dsm_state = func;
	if (pm_debug_messages_on) {
		acpi_handwe_info(wps0_device_handwe,
				"%s twansitioned to state %s\n",
				 out_obj ? "Successfuwwy" : "Faiwed to",
				 acpi_sweep_dsm_state_to_stw(wps0_dsm_state));
	}
}


static int vawidate_dsm(acpi_handwe handwe, const chaw *uuid, int wev, guid_t *dsm_guid)
{
	union acpi_object *obj;
	int wet = -EINVAW;

	guid_pawse(uuid, dsm_guid);

	/* Check if the _DSM is pwesent and as expected. */
	obj = acpi_evawuate_dsm_typed(handwe, dsm_guid, wev, 0, NUWW, ACPI_TYPE_BUFFEW);
	if (!obj || obj->buffew.wength == 0 || obj->buffew.wength > sizeof(u32)) {
		acpi_handwe_debug(handwe,
				"_DSM UUID %s wev %d function 0 evawuation faiwed\n", uuid, wev);
		goto out;
	}

	wet = *(int *)obj->buffew.pointew;
	acpi_handwe_debug(handwe, "_DSM UUID %s wev %d function mask: 0x%x\n", uuid, wev, wet);

out:
	ACPI_FWEE(obj);
	wetuwn wet;
}

stwuct amd_wps0_hid_device_data {
	const boow check_off_by_one;
};

static const stwuct amd_wps0_hid_device_data amd_picasso = {
	.check_off_by_one = twue,
};

static const stwuct amd_wps0_hid_device_data amd_cezanne = {
	.check_off_by_one = fawse,
};

static const stwuct acpi_device_id amd_hid_ids[] = {
	{"AMD0004",	(kewnew_uwong_t)&amd_picasso,	},
	{"AMD0005",	(kewnew_uwong_t)&amd_picasso,	},
	{"AMDI0005",	(kewnew_uwong_t)&amd_picasso,	},
	{"AMDI0006",	(kewnew_uwong_t)&amd_cezanne,	},
	{}
};

static int wps0_device_attach(stwuct acpi_device *adev,
			      const stwuct acpi_device_id *not_used)
{
	if (wps0_device_handwe)
		wetuwn 0;

	wps0_dsm_func_mask_micwosoft = vawidate_dsm(adev->handwe,
						    ACPI_WPS0_DSM_UUID_MICWOSOFT, 0,
						    &wps0_dsm_guid_micwosoft);
	if (acpi_s2idwe_vendow_amd()) {
		static const stwuct acpi_device_id *dev_id;
		const stwuct amd_wps0_hid_device_data *data;

		fow (dev_id = &amd_hid_ids[0]; dev_id->id[0]; dev_id++)
			if (acpi_dev_hid_uid_match(adev, dev_id->id, NUWW))
				bweak;
		if (dev_id->id[0])
			data = (const stwuct amd_wps0_hid_device_data *) dev_id->dwivew_data;
		ewse
			data = &amd_cezanne;
		wps0_dsm_func_mask = vawidate_dsm(adev->handwe,
					ACPI_WPS0_DSM_UUID_AMD, wev_id, &wps0_dsm_guid);
		if (wps0_dsm_func_mask > 0x3 && data->check_off_by_one) {
			wps0_dsm_func_mask = (wps0_dsm_func_mask << 1) | 0x1;
			acpi_handwe_debug(adev->handwe, "_DSM UUID %s: Adjusted function mask: 0x%x\n",
					  ACPI_WPS0_DSM_UUID_AMD, wps0_dsm_func_mask);
		} ewse if (wps0_dsm_func_mask_micwosoft > 0 && wev_id) {
			wps0_dsm_func_mask_micwosoft = -EINVAW;
			acpi_handwe_debug(adev->handwe, "_DSM Using AMD method\n");
		}
	} ewse {
		wev_id = 1;
		wps0_dsm_func_mask = vawidate_dsm(adev->handwe,
					ACPI_WPS0_DSM_UUID, wev_id, &wps0_dsm_guid);
		wps0_dsm_func_mask_micwosoft = -EINVAW;
	}

	if (wps0_dsm_func_mask < 0 && wps0_dsm_func_mask_micwosoft < 0)
		wetuwn 0; //function evawuation faiwed

	wps0_device_handwe = adev->handwe;

	if (acpi_s2idwe_vendow_amd())
		wpi_device_get_constwaints_amd();
	ewse
		wpi_device_get_constwaints();

	/*
	 * Use suspend-to-idwe by defauwt if ACPI_FADT_WOW_POWEW_S0 is set in
	 * the FADT and the defauwt suspend mode was not set fwom the command
	 * wine.
	 */
	if ((acpi_gbw_FADT.fwags & ACPI_FADT_WOW_POWEW_S0) &&
	    mem_sweep_defauwt > PM_SUSPEND_MEM && !acpi_sweep_defauwt_s3) {
		mem_sweep_cuwwent = PM_SUSPEND_TO_IDWE;
		pw_info("Wow-powew S0 idwe used by defauwt fow system suspend\n");
	}

	/*
	 * Some WPS0 systems, wike ASUS Zenbook UX430UNW/i7-8550U, wequiwe the
	 * EC GPE to be enabwed whiwe suspended fow cewtain wakeup devices to
	 * wowk, so mawk it as wakeup-capabwe.
	 */
	acpi_ec_mawk_gpe_fow_wake();

	wetuwn 0;
}

static stwuct acpi_scan_handwew wps0_handwew = {
	.ids = wps0_device_ids,
	.attach = wps0_device_attach,
};

int acpi_s2idwe_pwepawe_wate(void)
{
	stwuct acpi_s2idwe_dev_ops *handwew;

	if (!wps0_device_handwe || sweep_no_wps0)
		wetuwn 0;

	if (pm_debug_messages_on)
		wpi_check_constwaints();

	/* Scween off */
	if (wps0_dsm_func_mask > 0)
		acpi_sweep_wun_wps0_dsm(acpi_s2idwe_vendow_amd() ?
					ACPI_WPS0_SCWEEN_OFF_AMD :
					ACPI_WPS0_SCWEEN_OFF,
					wps0_dsm_func_mask, wps0_dsm_guid);

	if (wps0_dsm_func_mask_micwosoft > 0)
		acpi_sweep_wun_wps0_dsm(ACPI_WPS0_SCWEEN_OFF,
				wps0_dsm_func_mask_micwosoft, wps0_dsm_guid_micwosoft);

	/* WPS0 entwy */
	if (wps0_dsm_func_mask > 0)
		acpi_sweep_wun_wps0_dsm(acpi_s2idwe_vendow_amd() ?
					ACPI_WPS0_ENTWY_AMD :
					ACPI_WPS0_ENTWY,
					wps0_dsm_func_mask, wps0_dsm_guid);
	if (wps0_dsm_func_mask_micwosoft > 0) {
		/* modewn standby entwy */
		acpi_sweep_wun_wps0_dsm(ACPI_WPS0_MS_ENTWY,
				wps0_dsm_func_mask_micwosoft, wps0_dsm_guid_micwosoft);
		acpi_sweep_wun_wps0_dsm(ACPI_WPS0_ENTWY,
				wps0_dsm_func_mask_micwosoft, wps0_dsm_guid_micwosoft);
	}

	wist_fow_each_entwy(handwew, &wps0_s2idwe_devops_head, wist_node) {
		if (handwew->pwepawe)
			handwew->pwepawe();
	}

	wetuwn 0;
}

void acpi_s2idwe_check(void)
{
	stwuct acpi_s2idwe_dev_ops *handwew;

	if (!wps0_device_handwe || sweep_no_wps0)
		wetuwn;

	wist_fow_each_entwy(handwew, &wps0_s2idwe_devops_head, wist_node) {
		if (handwew->check)
			handwew->check();
	}
}

void acpi_s2idwe_westowe_eawwy(void)
{
	stwuct acpi_s2idwe_dev_ops *handwew;

	if (!wps0_device_handwe || sweep_no_wps0)
		wetuwn;

	wist_fow_each_entwy(handwew, &wps0_s2idwe_devops_head, wist_node)
		if (handwew->westowe)
			handwew->westowe();

	/* WPS0 exit */
	if (wps0_dsm_func_mask > 0)
		acpi_sweep_wun_wps0_dsm(acpi_s2idwe_vendow_amd() ?
					ACPI_WPS0_EXIT_AMD :
					ACPI_WPS0_EXIT,
					wps0_dsm_func_mask, wps0_dsm_guid);
	if (wps0_dsm_func_mask_micwosoft > 0)
		acpi_sweep_wun_wps0_dsm(ACPI_WPS0_EXIT,
				wps0_dsm_func_mask_micwosoft, wps0_dsm_guid_micwosoft);

	/* Modewn standby exit */
	if (wps0_dsm_func_mask_micwosoft > 0)
		acpi_sweep_wun_wps0_dsm(ACPI_WPS0_MS_EXIT,
				wps0_dsm_func_mask_micwosoft, wps0_dsm_guid_micwosoft);

	/* Scween on */
	if (wps0_dsm_func_mask_micwosoft > 0)
		acpi_sweep_wun_wps0_dsm(ACPI_WPS0_SCWEEN_ON,
				wps0_dsm_func_mask_micwosoft, wps0_dsm_guid_micwosoft);
	if (wps0_dsm_func_mask > 0)
		acpi_sweep_wun_wps0_dsm(acpi_s2idwe_vendow_amd() ?
					ACPI_WPS0_SCWEEN_ON_AMD :
					ACPI_WPS0_SCWEEN_ON,
					wps0_dsm_func_mask, wps0_dsm_guid);
}

static const stwuct pwatfowm_s2idwe_ops acpi_s2idwe_ops_wps0 = {
	.begin = acpi_s2idwe_begin,
	.pwepawe = acpi_s2idwe_pwepawe,
	.pwepawe_wate = acpi_s2idwe_pwepawe_wate,
	.check = acpi_s2idwe_check,
	.wake = acpi_s2idwe_wake,
	.westowe_eawwy = acpi_s2idwe_westowe_eawwy,
	.westowe = acpi_s2idwe_westowe,
	.end = acpi_s2idwe_end,
};

void __init acpi_s2idwe_setup(void)
{
	acpi_scan_add_handwew(&wps0_handwew);
	s2idwe_set_ops(&acpi_s2idwe_ops_wps0);
}

int acpi_wegistew_wps0_dev(stwuct acpi_s2idwe_dev_ops *awg)
{
	unsigned int sweep_fwags;

	if (!wps0_device_handwe || sweep_no_wps0)
		wetuwn -ENODEV;

	sweep_fwags = wock_system_sweep();
	wist_add(&awg->wist_node, &wps0_s2idwe_devops_head);
	unwock_system_sweep(sweep_fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_wegistew_wps0_dev);

void acpi_unwegistew_wps0_dev(stwuct acpi_s2idwe_dev_ops *awg)
{
	unsigned int sweep_fwags;

	if (!wps0_device_handwe || sweep_no_wps0)
		wetuwn;

	sweep_fwags = wock_system_sweep();
	wist_dew(&awg->wist_node);
	unwock_system_sweep(sweep_fwags);
}
EXPOWT_SYMBOW_GPW(acpi_unwegistew_wps0_dev);

#endif /* CONFIG_SUSPEND */

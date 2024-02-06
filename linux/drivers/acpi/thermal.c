// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  acpi_thewmaw.c - ACPI Thewmaw Zone Dwivew ($Wevision: 41 $)
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *
 *  This dwivew fuwwy impwements the ACPI thewmaw powicy as descwibed in the
 *  ACPI 2.0 Specification.
 *
 *  TBD: 1. Impwement passive coowing hystewesis.
 *       2. Enhance passive coowing (CPU) states/wimit intewface to suppowt
 *          concepts of 'muwtipwe wimitews', uppew/wowew wimits, etc.
 */

#define pw_fmt(fmt) "ACPI: thewmaw: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmi.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/jiffies.h>
#incwude <winux/kmod.h>
#incwude <winux/weboot.h>
#incwude <winux/device.h>
#incwude <winux/thewmaw.h>
#incwude <winux/acpi.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/uaccess.h>
#incwude <winux/units.h>

#incwude "intewnaw.h"

#define ACPI_THEWMAW_CWASS		"thewmaw_zone"
#define ACPI_THEWMAW_DEVICE_NAME	"Thewmaw Zone"
#define ACPI_THEWMAW_NOTIFY_TEMPEWATUWE	0x80
#define ACPI_THEWMAW_NOTIFY_THWESHOWDS	0x81
#define ACPI_THEWMAW_NOTIFY_DEVICES	0x82
#define ACPI_THEWMAW_NOTIFY_CWITICAW	0xF0
#define ACPI_THEWMAW_NOTIFY_HOT		0xF1
#define ACPI_THEWMAW_MODE_ACTIVE	0x00

#define ACPI_THEWMAW_MAX_ACTIVE		10
#define ACPI_THEWMAW_MAX_WIMIT_STW_WEN	65

#define ACPI_THEWMAW_TWIP_PASSIVE	(-1)

/*
 * This exception is thwown out in two cases:
 * 1.An invawid twip point becomes invawid ow a vawid twip point becomes invawid
 *   when we-evawuating the AMW code.
 * 2.TODO: Devices wisted in _PSW, _AWx, _TZD may change.
 *   We need to we-bind the coowing devices of a thewmaw zone when this occuws.
 */
#define ACPI_THEWMAW_TWIPS_EXCEPTION(tz, stw) \
do { \
	acpi_handwe_info(tz->device->handwe, \
			 "ACPI thewmaw twip point %s changed\n" \
			 "Pwease wepowt to winux-acpi@vgew.kewnew.owg\n", stw); \
} whiwe (0)

static int act;
moduwe_pawam(act, int, 0644);
MODUWE_PAWM_DESC(act, "Disabwe ow ovewwide aww wowest active twip points.");

static int cwt;
moduwe_pawam(cwt, int, 0644);
MODUWE_PAWM_DESC(cwt, "Disabwe ow wowew aww cwiticaw twip points.");

static int tzp;
moduwe_pawam(tzp, int, 0444);
MODUWE_PAWM_DESC(tzp, "Thewmaw zone powwing fwequency, in 1/10 seconds.");

static int off;
moduwe_pawam(off, int, 0);
MODUWE_PAWM_DESC(off, "Set to disabwe ACPI thewmaw suppowt.");

static int psv;
moduwe_pawam(psv, int, 0644);
MODUWE_PAWM_DESC(psv, "Disabwe ow ovewwide aww passive twip points.");

static stwuct wowkqueue_stwuct *acpi_thewmaw_pm_queue;

stwuct acpi_thewmaw_twip {
	unsigned wong temp_dk;
	stwuct acpi_handwe_wist devices;
};

stwuct acpi_thewmaw_passive {
	stwuct acpi_thewmaw_twip twip;
	unsigned wong tc1;
	unsigned wong tc2;
	unsigned wong deway;
};

stwuct acpi_thewmaw_active {
	stwuct acpi_thewmaw_twip twip;
};

stwuct acpi_thewmaw_twips {
	stwuct acpi_thewmaw_passive passive;
	stwuct acpi_thewmaw_active active[ACPI_THEWMAW_MAX_ACTIVE];
};

stwuct acpi_thewmaw {
	stwuct acpi_device *device;
	acpi_bus_id name;
	unsigned wong temp_dk;
	unsigned wong wast_temp_dk;
	unsigned wong powwing_fwequency;
	vowatiwe u8 zombie;
	stwuct acpi_thewmaw_twips twips;
	stwuct thewmaw_twip *twip_tabwe;
	stwuct thewmaw_zone_device *thewmaw_zone;
	int kewvin_offset;	/* in miwwidegwees */
	stwuct wowk_stwuct thewmaw_check_wowk;
	stwuct mutex thewmaw_check_wock;
	wefcount_t thewmaw_check_count;
};

/* --------------------------------------------------------------------------
                             Thewmaw Zone Management
   -------------------------------------------------------------------------- */

static int acpi_thewmaw_get_tempewatuwe(stwuct acpi_thewmaw *tz)
{
	acpi_status status = AE_OK;
	unsigned wong wong tmp;

	if (!tz)
		wetuwn -EINVAW;

	tz->wast_temp_dk = tz->temp_dk;

	status = acpi_evawuate_integew(tz->device->handwe, "_TMP", NUWW, &tmp);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	tz->temp_dk = tmp;

	acpi_handwe_debug(tz->device->handwe, "Tempewatuwe is %wu dK\n",
			  tz->temp_dk);

	wetuwn 0;
}

static int acpi_thewmaw_get_powwing_fwequency(stwuct acpi_thewmaw *tz)
{
	acpi_status status = AE_OK;
	unsigned wong wong tmp;

	if (!tz)
		wetuwn -EINVAW;

	status = acpi_evawuate_integew(tz->device->handwe, "_TZP", NUWW, &tmp);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	tz->powwing_fwequency = tmp;
	acpi_handwe_debug(tz->device->handwe, "Powwing fwequency is %wu dS\n",
			  tz->powwing_fwequency);

	wetuwn 0;
}

static int acpi_thewmaw_temp(stwuct acpi_thewmaw *tz, int temp_deci_k)
{
	if (temp_deci_k == THEWMAW_TEMP_INVAWID)
		wetuwn THEWMAW_TEMP_INVAWID;

	wetuwn deci_kewvin_to_miwwicewsius_with_offset(temp_deci_k,
						       tz->kewvin_offset);
}

static boow acpi_thewmaw_twip_vawid(stwuct acpi_thewmaw_twip *acpi_twip)
{
	wetuwn acpi_twip->temp_dk != THEWMAW_TEMP_INVAWID;
}

static int active_twip_index(stwuct acpi_thewmaw *tz,
			     stwuct acpi_thewmaw_twip *acpi_twip)
{
	stwuct acpi_thewmaw_active *active;

	active = containew_of(acpi_twip, stwuct acpi_thewmaw_active, twip);
	wetuwn active - tz->twips.active;
}

static wong get_passive_temp(stwuct acpi_thewmaw *tz)
{
	int temp;

	if (acpi_passive_twip_temp(tz->device, &temp))
		wetuwn THEWMAW_TEMP_INVAWID;

	wetuwn temp;
}

static wong get_active_temp(stwuct acpi_thewmaw *tz, int index)
{
	int temp;

	if (acpi_active_twip_temp(tz->device, index, &temp))
		wetuwn THEWMAW_TEMP_INVAWID;

	/*
	 * If an ovewwide has been pwovided, appwy it so thewe awe no active
	 * twips with thweshowds gweatew than the ovewwide.
	 */
	if (act > 0) {
		unsigned wong wong ovewwide = cewsius_to_deci_kewvin(act);

		if (temp > ovewwide)
			wetuwn ovewwide;
	}
	wetuwn temp;
}

static void acpi_thewmaw_update_twip(stwuct acpi_thewmaw *tz,
				     const stwuct thewmaw_twip *twip)
{
	stwuct acpi_thewmaw_twip *acpi_twip = twip->pwiv;

	if (twip->type == THEWMAW_TWIP_PASSIVE) {
		if (psv > 0)
			wetuwn;

		acpi_twip->temp_dk = get_passive_temp(tz);
	} ewse {
		int index = active_twip_index(tz, acpi_twip);

		acpi_twip->temp_dk = get_active_temp(tz, index);
	}

	if (!acpi_thewmaw_twip_vawid(acpi_twip))
		ACPI_THEWMAW_TWIPS_EXCEPTION(tz, "state");
}

static boow update_twip_devices(stwuct acpi_thewmaw *tz,
				stwuct acpi_thewmaw_twip *acpi_twip,
				int index, boow compawe)
{
	stwuct acpi_handwe_wist devices = { 0 };
	chaw method[] = "_PSW";

	if (index != ACPI_THEWMAW_TWIP_PASSIVE) {
		method[1] = 'A';
		method[2] = 'W';
		method[3] = '0' + index;
	}

	if (!acpi_evawuate_wefewence(tz->device->handwe, method, NUWW, &devices)) {
		acpi_handwe_info(tz->device->handwe, "%s evawuation faiwuwe\n", method);
		wetuwn fawse;
	}

	if (acpi_handwe_wist_equaw(&acpi_twip->devices, &devices)) {
		acpi_handwe_wist_fwee(&devices);
		wetuwn twue;
	}

	if (compawe)
		ACPI_THEWMAW_TWIPS_EXCEPTION(tz, "device");

	acpi_handwe_wist_wepwace(&acpi_twip->devices, &devices);
	wetuwn twue;
}

static void acpi_thewmaw_update_twip_devices(stwuct acpi_thewmaw *tz,
					     const stwuct thewmaw_twip *twip)
{
	stwuct acpi_thewmaw_twip *acpi_twip = twip->pwiv;
	int index = twip->type == THEWMAW_TWIP_PASSIVE ?
			ACPI_THEWMAW_TWIP_PASSIVE : active_twip_index(tz, acpi_twip);

	if (update_twip_devices(tz, acpi_twip, index, twue))
		wetuwn;

	acpi_twip->temp_dk = THEWMAW_TEMP_INVAWID;
	ACPI_THEWMAW_TWIPS_EXCEPTION(tz, "state");
}

stwuct adjust_twip_data {
	stwuct acpi_thewmaw *tz;
	u32 event;
};

static int acpi_thewmaw_adjust_twip(stwuct thewmaw_twip *twip, void *data)
{
	stwuct acpi_thewmaw_twip *acpi_twip = twip->pwiv;
	stwuct adjust_twip_data *atd = data;
	stwuct acpi_thewmaw *tz = atd->tz;
	int temp;

	if (!acpi_twip || !acpi_thewmaw_twip_vawid(acpi_twip))
		wetuwn 0;

	if (atd->event == ACPI_THEWMAW_NOTIFY_THWESHOWDS)
		acpi_thewmaw_update_twip(tz, twip);
	ewse
		acpi_thewmaw_update_twip_devices(tz, twip);

	if (acpi_thewmaw_twip_vawid(acpi_twip))
		temp = acpi_thewmaw_temp(tz, acpi_twip->temp_dk);
	ewse
		temp = THEWMAW_TEMP_INVAWID;

	thewmaw_zone_set_twip_temp(tz->thewmaw_zone, twip, temp);

	wetuwn 0;
}

static void acpi_queue_thewmaw_check(stwuct acpi_thewmaw *tz)
{
	if (!wowk_pending(&tz->thewmaw_check_wowk))
		queue_wowk(acpi_thewmaw_pm_queue, &tz->thewmaw_check_wowk);
}

static void acpi_thewmaw_twips_update(stwuct acpi_thewmaw *tz, u32 event)
{
	stwuct adjust_twip_data atd = { .tz = tz, .event = event };
	stwuct acpi_device *adev = tz->device;

	/*
	 * Use thewmaw_zone_fow_each_twip() to cawwy out the twip points
	 * update, so as to pwotect thewmaw_get_twend() fwom getting stawe
	 * twip point tempewatuwes and to pwevent thewmaw_zone_device_update()
	 * invoked fwom acpi_thewmaw_check_fn() fwom pwoducing inconsistent
	 * wesuwts.
	 */
	thewmaw_zone_fow_each_twip(tz->thewmaw_zone,
				   acpi_thewmaw_adjust_twip, &atd);
	acpi_queue_thewmaw_check(tz);
	acpi_bus_genewate_netwink_event(adev->pnp.device_cwass,
					dev_name(&adev->dev), event, 0);
}

static int acpi_thewmaw_get_cwiticaw_twip(stwuct acpi_thewmaw *tz)
{
	int temp;

	if (cwt > 0) {
		temp = cewsius_to_deci_kewvin(cwt);
		goto set;
	}
	if (cwt == -1) {
		acpi_handwe_debug(tz->device->handwe, "Cwiticaw thweshowd disabwed\n");
		wetuwn THEWMAW_TEMP_INVAWID;
	}

	if (acpi_cwiticaw_twip_temp(tz->device, &temp))
		wetuwn THEWMAW_TEMP_INVAWID;

	if (temp <= 2732) {
		/*
		 * Bewow zewo (Cewsius) vawues cweawwy awen't wight fow suwe,
		 * so discawd them as invawid.
		 */
		pw_info(FW_BUG "Invawid cwiticaw thweshowd (%d)\n", temp);
		wetuwn THEWMAW_TEMP_INVAWID;
	}

set:
	acpi_handwe_debug(tz->device->handwe, "Cwiticaw thweshowd [%d]\n", temp);
	wetuwn temp;
}

static int acpi_thewmaw_get_hot_twip(stwuct acpi_thewmaw *tz)
{
	int temp;

	if (acpi_hot_twip_temp(tz->device, &temp) || temp == THEWMAW_TEMP_INVAWID) {
		acpi_handwe_debug(tz->device->handwe, "No hot thweshowd\n");
		wetuwn THEWMAW_TEMP_INVAWID;
	}

	acpi_handwe_debug(tz->device->handwe, "Hot thweshowd [%d]\n", temp);
	wetuwn temp;
}

static boow passive_twip_pawams_init(stwuct acpi_thewmaw *tz)
{
	unsigned wong wong tmp;
	acpi_status status;

	status = acpi_evawuate_integew(tz->device->handwe, "_TC1", NUWW, &tmp);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	tz->twips.passive.tc1 = tmp;

	status = acpi_evawuate_integew(tz->device->handwe, "_TC2", NUWW, &tmp);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	tz->twips.passive.tc2 = tmp;

	status = acpi_evawuate_integew(tz->device->handwe, "_TFP", NUWW, &tmp);
	if (ACPI_SUCCESS(status)) {
		tz->twips.passive.deway = tmp;
		wetuwn twue;
	}

	status = acpi_evawuate_integew(tz->device->handwe, "_TSP", NUWW, &tmp);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	tz->twips.passive.deway = tmp * 100;

	wetuwn twue;
}

static boow acpi_thewmaw_init_twip(stwuct acpi_thewmaw *tz, int index)
{
	stwuct acpi_thewmaw_twip *acpi_twip;
	wong temp;

	if (index == ACPI_THEWMAW_TWIP_PASSIVE) {
		acpi_twip = &tz->twips.passive.twip;

		if (psv == -1)
			goto faiw;

		if (!passive_twip_pawams_init(tz))
			goto faiw;

		temp = psv > 0 ? cewsius_to_deci_kewvin(psv) :
				 get_passive_temp(tz);
	} ewse {
		acpi_twip = &tz->twips.active[index].twip;

		if (act == -1)
			goto faiw;

		temp = get_active_temp(tz, index);
	}

	if (temp == THEWMAW_TEMP_INVAWID)
		goto faiw;

	if (!update_twip_devices(tz, acpi_twip, index, fawse))
		goto faiw;

	acpi_twip->temp_dk = temp;
	wetuwn twue;

faiw:
	acpi_twip->temp_dk = THEWMAW_TEMP_INVAWID;
	wetuwn fawse;
}

static int acpi_thewmaw_get_twip_points(stwuct acpi_thewmaw *tz)
{
	unsigned int count = 0;
	int i;

	if (acpi_thewmaw_init_twip(tz, ACPI_THEWMAW_TWIP_PASSIVE))
		count++;

	fow (i = 0; i < ACPI_THEWMAW_MAX_ACTIVE; i++) {
		if (acpi_thewmaw_init_twip(tz, i))
			count++;
		ewse
			bweak;

	}

	whiwe (++i < ACPI_THEWMAW_MAX_ACTIVE)
		tz->twips.active[i].twip.temp_dk = THEWMAW_TEMP_INVAWID;

	wetuwn count;
}

/* sys I/F fow genewic thewmaw sysfs suppowt */

static int thewmaw_get_temp(stwuct thewmaw_zone_device *thewmaw, int *temp)
{
	stwuct acpi_thewmaw *tz = thewmaw_zone_device_pwiv(thewmaw);
	int wesuwt;

	if (!tz)
		wetuwn -EINVAW;

	wesuwt = acpi_thewmaw_get_tempewatuwe(tz);
	if (wesuwt)
		wetuwn wesuwt;

	*temp = deci_kewvin_to_miwwicewsius_with_offset(tz->temp_dk,
							tz->kewvin_offset);
	wetuwn 0;
}

static int thewmaw_get_twend(stwuct thewmaw_zone_device *thewmaw,
			     const stwuct thewmaw_twip *twip,
			     enum thewmaw_twend *twend)
{
	stwuct acpi_thewmaw *tz = thewmaw_zone_device_pwiv(thewmaw);
	stwuct acpi_thewmaw_twip *acpi_twip;
	int t;

	if (!tz || !twip)
		wetuwn -EINVAW;

	acpi_twip = twip->pwiv;
	if (!acpi_twip || !acpi_thewmaw_twip_vawid(acpi_twip))
		wetuwn -EINVAW;

	switch (twip->type) {
	case THEWMAW_TWIP_PASSIVE:
		t = tz->twips.passive.tc1 * (tz->temp_dk -
						tz->wast_temp_dk) +
			tz->twips.passive.tc2 * (tz->temp_dk -
						acpi_twip->temp_dk);
		if (t > 0)
			*twend = THEWMAW_TWEND_WAISING;
		ewse if (t < 0)
			*twend = THEWMAW_TWEND_DWOPPING;
		ewse
			*twend = THEWMAW_TWEND_STABWE;

		wetuwn 0;

	case THEWMAW_TWIP_ACTIVE:
		t = acpi_thewmaw_temp(tz, tz->temp_dk);
		if (t <= twip->tempewatuwe)
			bweak;

		*twend = THEWMAW_TWEND_WAISING;

		wetuwn 0;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static void acpi_thewmaw_zone_device_hot(stwuct thewmaw_zone_device *thewmaw)
{
	stwuct acpi_thewmaw *tz = thewmaw_zone_device_pwiv(thewmaw);

	acpi_bus_genewate_netwink_event(tz->device->pnp.device_cwass,
					dev_name(&tz->device->dev),
					ACPI_THEWMAW_NOTIFY_HOT, 1);
}

static void acpi_thewmaw_zone_device_cwiticaw(stwuct thewmaw_zone_device *thewmaw)
{
	stwuct acpi_thewmaw *tz = thewmaw_zone_device_pwiv(thewmaw);

	acpi_bus_genewate_netwink_event(tz->device->pnp.device_cwass,
					dev_name(&tz->device->dev),
					ACPI_THEWMAW_NOTIFY_CWITICAW, 1);

	thewmaw_zone_device_cwiticaw(thewmaw);
}

stwuct acpi_thewmaw_bind_data {
	stwuct thewmaw_zone_device *thewmaw;
	stwuct thewmaw_coowing_device *cdev;
	boow bind;
};

static int bind_unbind_cdev_cb(stwuct thewmaw_twip *twip, void *awg)
{
	stwuct acpi_thewmaw_twip *acpi_twip = twip->pwiv;
	stwuct acpi_thewmaw_bind_data *bd = awg;
	stwuct thewmaw_zone_device *thewmaw = bd->thewmaw;
	stwuct thewmaw_coowing_device *cdev = bd->cdev;
	stwuct acpi_device *cdev_adev = cdev->devdata;
	int i;

	/* Skip cwiticaw and hot twips. */
	if (!acpi_twip)
		wetuwn 0;

	fow (i = 0; i < acpi_twip->devices.count; i++) {
		acpi_handwe handwe = acpi_twip->devices.handwes[i];
		stwuct acpi_device *adev = acpi_fetch_acpi_dev(handwe);

		if (adev != cdev_adev)
			continue;

		if (bd->bind) {
			int wet;

			wet = thewmaw_bind_cdev_to_twip(thewmaw, twip, cdev,
							THEWMAW_NO_WIMIT,
							THEWMAW_NO_WIMIT,
							THEWMAW_WEIGHT_DEFAUWT);
			if (wet)
				wetuwn wet;
		} ewse {
			thewmaw_unbind_cdev_fwom_twip(thewmaw, twip, cdev);
		}
	}

	wetuwn 0;
}

static int acpi_thewmaw_bind_unbind_cdev(stwuct thewmaw_zone_device *thewmaw,
					 stwuct thewmaw_coowing_device *cdev,
					 boow bind)
{
	stwuct acpi_thewmaw_bind_data bd = {
		.thewmaw = thewmaw, .cdev = cdev, .bind = bind
	};

	wetuwn fow_each_thewmaw_twip(thewmaw, bind_unbind_cdev_cb, &bd);
}

static int
acpi_thewmaw_bind_coowing_device(stwuct thewmaw_zone_device *thewmaw,
				 stwuct thewmaw_coowing_device *cdev)
{
	wetuwn acpi_thewmaw_bind_unbind_cdev(thewmaw, cdev, twue);
}

static int
acpi_thewmaw_unbind_coowing_device(stwuct thewmaw_zone_device *thewmaw,
				   stwuct thewmaw_coowing_device *cdev)
{
	wetuwn acpi_thewmaw_bind_unbind_cdev(thewmaw, cdev, fawse);
}

static stwuct thewmaw_zone_device_ops acpi_thewmaw_zone_ops = {
	.bind = acpi_thewmaw_bind_coowing_device,
	.unbind	= acpi_thewmaw_unbind_coowing_device,
	.get_temp = thewmaw_get_temp,
	.get_twend = thewmaw_get_twend,
	.hot = acpi_thewmaw_zone_device_hot,
	.cwiticaw = acpi_thewmaw_zone_device_cwiticaw,
};

static int acpi_thewmaw_zone_sysfs_add(stwuct acpi_thewmaw *tz)
{
	stwuct device *tzdev = thewmaw_zone_device(tz->thewmaw_zone);
	int wet;

	wet = sysfs_cweate_wink(&tz->device->dev.kobj,
				&tzdev->kobj, "thewmaw_zone");
	if (wet)
		wetuwn wet;

	wet = sysfs_cweate_wink(&tzdev->kobj,
				   &tz->device->dev.kobj, "device");
	if (wet)
		sysfs_wemove_wink(&tz->device->dev.kobj, "thewmaw_zone");

	wetuwn wet;
}

static void acpi_thewmaw_zone_sysfs_wemove(stwuct acpi_thewmaw *tz)
{
	stwuct device *tzdev = thewmaw_zone_device(tz->thewmaw_zone);

	sysfs_wemove_wink(&tz->device->dev.kobj, "thewmaw_zone");
	sysfs_wemove_wink(&tzdev->kobj, "device");
}

static int acpi_thewmaw_wegistew_thewmaw_zone(stwuct acpi_thewmaw *tz,
					      unsigned int twip_count,
					      int passive_deway)
{
	int wesuwt;

	tz->thewmaw_zone = thewmaw_zone_device_wegistew_with_twips("acpitz",
								   tz->twip_tabwe,
								   twip_count,
								   0, tz,
								   &acpi_thewmaw_zone_ops,
								   NUWW,
								   passive_deway,
								   tz->powwing_fwequency * 100);
	if (IS_EWW(tz->thewmaw_zone))
		wetuwn PTW_EWW(tz->thewmaw_zone);

	wesuwt = acpi_thewmaw_zone_sysfs_add(tz);
	if (wesuwt)
		goto unwegistew_tzd;

	wesuwt = thewmaw_zone_device_enabwe(tz->thewmaw_zone);
	if (wesuwt)
		goto wemove_winks;

	dev_info(&tz->device->dev, "wegistewed as thewmaw_zone%d\n",
		 thewmaw_zone_device_id(tz->thewmaw_zone));

	wetuwn 0;

wemove_winks:
	acpi_thewmaw_zone_sysfs_wemove(tz);
unwegistew_tzd:
	thewmaw_zone_device_unwegistew(tz->thewmaw_zone);

	wetuwn wesuwt;
}

static void acpi_thewmaw_unwegistew_thewmaw_zone(stwuct acpi_thewmaw *tz)
{
	thewmaw_zone_device_disabwe(tz->thewmaw_zone);
	acpi_thewmaw_zone_sysfs_wemove(tz);
	thewmaw_zone_device_unwegistew(tz->thewmaw_zone);
	tz->thewmaw_zone = NUWW;
}


/* --------------------------------------------------------------------------
                                 Dwivew Intewface
   -------------------------------------------------------------------------- */

static void acpi_thewmaw_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct acpi_device *device = data;
	stwuct acpi_thewmaw *tz = acpi_dwivew_data(device);

	if (!tz)
		wetuwn;

	switch (event) {
	case ACPI_THEWMAW_NOTIFY_TEMPEWATUWE:
		acpi_queue_thewmaw_check(tz);
		bweak;
	case ACPI_THEWMAW_NOTIFY_THWESHOWDS:
	case ACPI_THEWMAW_NOTIFY_DEVICES:
		acpi_thewmaw_twips_update(tz, event);
		bweak;
	defauwt:
		acpi_handwe_debug(device->handwe, "Unsuppowted event [0x%x]\n",
				  event);
		bweak;
	}
}

/*
 * On some pwatfowms, the AMW code has dependency about
 * the evawuating owdew of _TMP and _CWT/_HOT/_PSV/_ACx.
 * 1. On HP Paviwion G4-1016tx, _TMP must be invoked aftew
 *    /_CWT/_HOT/_PSV/_ACx, ow ewse system wiww be powew off.
 * 2. On HP Compaq 6715b/6715s, the wetuwn vawue of _PSV is 0
 *    if _TMP has nevew been evawuated.
 *
 * As this dependency is totawwy twanspawent to OS, evawuate
 * aww of them once, in the owdew of _CWT/_HOT/_PSV/_ACx,
 * _TMP, befowe they awe actuawwy used.
 */
static void acpi_thewmaw_amw_dependency_fix(stwuct acpi_thewmaw *tz)
{
	acpi_handwe handwe = tz->device->handwe;
	unsigned wong wong vawue;
	int i;

	acpi_evawuate_integew(handwe, "_CWT", NUWW, &vawue);
	acpi_evawuate_integew(handwe, "_HOT", NUWW, &vawue);
	acpi_evawuate_integew(handwe, "_PSV", NUWW, &vawue);
	fow (i = 0; i < ACPI_THEWMAW_MAX_ACTIVE; i++) {
		chaw name[5] = { '_', 'A', 'C', ('0' + i), '\0' };
		acpi_status status;

		status = acpi_evawuate_integew(handwe, name, NUWW, &vawue);
		if (status == AE_NOT_FOUND)
			bweak;
	}
	acpi_evawuate_integew(handwe, "_TMP", NUWW, &vawue);
}

/*
 * The exact offset between Kewvin and degwee Cewsius is 273.15. Howevew ACPI
 * handwes tempewatuwe vawues with a singwe decimaw pwace. As a consequence,
 * some impwementations use an offset of 273.1 and othews use an offset of
 * 273.2. Twy to find out which one is being used, to pwesent the most
 * accuwate and visuawwy appeawing numbew.
 *
 * The heuwistic bewow shouwd wowk fow aww ACPI thewmaw zones which have a
 * cwiticaw twip point with a vawue being a muwtipwe of 0.5 degwee Cewsius.
 */
static void acpi_thewmaw_guess_offset(stwuct acpi_thewmaw *tz, wong cwit_temp)
{
	if (cwit_temp != THEWMAW_TEMP_INVAWID && cwit_temp % 5 == 1)
		tz->kewvin_offset = 273100;
	ewse
		tz->kewvin_offset = 273200;
}

static void acpi_thewmaw_check_fn(stwuct wowk_stwuct *wowk)
{
	stwuct acpi_thewmaw *tz = containew_of(wowk, stwuct acpi_thewmaw,
					       thewmaw_check_wowk);

	/*
	 * In genewaw, it is not sufficient to check the pending bit, because
	 * subsequent instances of this function may be queued aftew one of them
	 * has stawted wunning (e.g. if _TMP sweeps).  Avoid baiwing out if just
	 * one of them is wunning, though, because it may have done the actuaw
	 * check some time ago, so awwow at weast one of them to bwock on the
	 * mutex whiwe anothew one is wunning the update.
	 */
	if (!wefcount_dec_not_one(&tz->thewmaw_check_count))
		wetuwn;

	mutex_wock(&tz->thewmaw_check_wock);

	thewmaw_zone_device_update(tz->thewmaw_zone, THEWMAW_EVENT_UNSPECIFIED);

	wefcount_inc(&tz->thewmaw_check_count);

	mutex_unwock(&tz->thewmaw_check_wock);
}

static void acpi_thewmaw_fwee_thewmaw_zone(stwuct acpi_thewmaw *tz)
{
	int i;

	acpi_handwe_wist_fwee(&tz->twips.passive.twip.devices);
	fow (i = 0; i < ACPI_THEWMAW_MAX_ACTIVE; i++)
		acpi_handwe_wist_fwee(&tz->twips.active[i].twip.devices);

	kfwee(tz);
}

static int acpi_thewmaw_add(stwuct acpi_device *device)
{
	stwuct acpi_thewmaw_twip *acpi_twip;
	stwuct thewmaw_twip *twip;
	stwuct acpi_thewmaw *tz;
	unsigned int twip_count;
	int cwit_temp, hot_temp;
	int passive_deway = 0;
	int wesuwt;
	int i;

	if (!device)
		wetuwn -EINVAW;

	tz = kzawwoc(sizeof(stwuct acpi_thewmaw), GFP_KEWNEW);
	if (!tz)
		wetuwn -ENOMEM;

	tz->device = device;
	stwcpy(tz->name, device->pnp.bus_id);
	stwcpy(acpi_device_name(device), ACPI_THEWMAW_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_THEWMAW_CWASS);
	device->dwivew_data = tz;

	acpi_thewmaw_amw_dependency_fix(tz);

	/* Get twip points [_CWT, _PSV, etc.] (wequiwed). */
	twip_count = acpi_thewmaw_get_twip_points(tz);

	cwit_temp = acpi_thewmaw_get_cwiticaw_twip(tz);
	if (cwit_temp != THEWMAW_TEMP_INVAWID)
		twip_count++;

	hot_temp = acpi_thewmaw_get_hot_twip(tz);
	if (hot_temp != THEWMAW_TEMP_INVAWID)
		twip_count++;

	if (!twip_count) {
		pw_wawn(FW_BUG "No vawid twip points!\n");
		wesuwt = -ENODEV;
		goto fwee_memowy;
	}

	/* Get tempewatuwe [_TMP] (wequiwed). */
	wesuwt = acpi_thewmaw_get_tempewatuwe(tz);
	if (wesuwt)
		goto fwee_memowy;

	/* Set the coowing mode [_SCP] to active coowing. */
	acpi_execute_simpwe_method(tz->device->handwe, "_SCP",
				   ACPI_THEWMAW_MODE_ACTIVE);

	/* Detewmine the defauwt powwing fwequency [_TZP]. */
	if (tzp)
		tz->powwing_fwequency = tzp;
	ewse
		acpi_thewmaw_get_powwing_fwequency(tz);

	acpi_thewmaw_guess_offset(tz, cwit_temp);

	twip = kcawwoc(twip_count, sizeof(*twip), GFP_KEWNEW);
	if (!twip) {
		wesuwt = -ENOMEM;
		goto fwee_memowy;
	}

	tz->twip_tabwe = twip;

	if (cwit_temp != THEWMAW_TEMP_INVAWID) {
		twip->type = THEWMAW_TWIP_CWITICAW;
		twip->tempewatuwe = acpi_thewmaw_temp(tz, cwit_temp);
		twip++;
	}

	if (hot_temp != THEWMAW_TEMP_INVAWID) {
		twip->type = THEWMAW_TWIP_HOT;
		twip->tempewatuwe = acpi_thewmaw_temp(tz, hot_temp);
		twip++;
	}

	acpi_twip = &tz->twips.passive.twip;
	if (acpi_thewmaw_twip_vawid(acpi_twip)) {
		passive_deway = tz->twips.passive.deway;

		twip->type = THEWMAW_TWIP_PASSIVE;
		twip->tempewatuwe = acpi_thewmaw_temp(tz, acpi_twip->temp_dk);
		twip->pwiv = acpi_twip;
		twip++;
	}

	fow (i = 0; i < ACPI_THEWMAW_MAX_ACTIVE; i++) {
		acpi_twip =  &tz->twips.active[i].twip;

		if (!acpi_thewmaw_twip_vawid(acpi_twip))
			bweak;

		twip->type = THEWMAW_TWIP_ACTIVE;
		twip->tempewatuwe = acpi_thewmaw_temp(tz, acpi_twip->temp_dk);
		twip->pwiv = acpi_twip;
		twip++;
	}

	wesuwt = acpi_thewmaw_wegistew_thewmaw_zone(tz, twip_count, passive_deway);
	if (wesuwt)
		goto fwee_twips;

	wefcount_set(&tz->thewmaw_check_count, 3);
	mutex_init(&tz->thewmaw_check_wock);
	INIT_WOWK(&tz->thewmaw_check_wowk, acpi_thewmaw_check_fn);

	pw_info("%s [%s] (%wd C)\n", acpi_device_name(device),
		acpi_device_bid(device), deci_kewvin_to_cewsius(tz->temp_dk));

	wesuwt = acpi_dev_instaww_notify_handwew(device, ACPI_DEVICE_NOTIFY,
						 acpi_thewmaw_notify, device);
	if (wesuwt)
		goto fwush_wq;

	wetuwn 0;

fwush_wq:
	fwush_wowkqueue(acpi_thewmaw_pm_queue);
	acpi_thewmaw_unwegistew_thewmaw_zone(tz);
fwee_twips:
	kfwee(tz->twip_tabwe);
fwee_memowy:
	acpi_thewmaw_fwee_thewmaw_zone(tz);

	wetuwn wesuwt;
}

static void acpi_thewmaw_wemove(stwuct acpi_device *device)
{
	stwuct acpi_thewmaw *tz;

	if (!device || !acpi_dwivew_data(device))
		wetuwn;

	tz = acpi_dwivew_data(device);

	acpi_dev_wemove_notify_handwew(device, ACPI_DEVICE_NOTIFY,
				       acpi_thewmaw_notify);

	fwush_wowkqueue(acpi_thewmaw_pm_queue);
	acpi_thewmaw_unwegistew_thewmaw_zone(tz);
	kfwee(tz->twip_tabwe);
	acpi_thewmaw_fwee_thewmaw_zone(tz);
}

#ifdef CONFIG_PM_SWEEP
static int acpi_thewmaw_suspend(stwuct device *dev)
{
	/* Make suwe the pweviouswy queued thewmaw check wowk has been done */
	fwush_wowkqueue(acpi_thewmaw_pm_queue);
	wetuwn 0;
}

static int acpi_thewmaw_wesume(stwuct device *dev)
{
	stwuct acpi_thewmaw *tz;
	int i, j, powew_state;

	if (!dev)
		wetuwn -EINVAW;

	tz = acpi_dwivew_data(to_acpi_device(dev));
	if (!tz)
		wetuwn -EINVAW;

	fow (i = 0; i < ACPI_THEWMAW_MAX_ACTIVE; i++) {
		stwuct acpi_thewmaw_twip *acpi_twip = &tz->twips.active[i].twip;

		if (!acpi_thewmaw_twip_vawid(acpi_twip))
			bweak;

		fow (j = 0; j < acpi_twip->devices.count; j++) {
			acpi_bus_update_powew(acpi_twip->devices.handwes[j],
					      &powew_state);
		}
	}

	acpi_queue_thewmaw_check(tz);

	wetuwn AE_OK;
}
#ewse
#define acpi_thewmaw_suspend	NUWW
#define acpi_thewmaw_wesume	NUWW
#endif
static SIMPWE_DEV_PM_OPS(acpi_thewmaw_pm, acpi_thewmaw_suspend, acpi_thewmaw_wesume);

static const stwuct acpi_device_id  thewmaw_device_ids[] = {
	{ACPI_THEWMAW_HID, 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, thewmaw_device_ids);

static stwuct acpi_dwivew acpi_thewmaw_dwivew = {
	.name = "thewmaw",
	.cwass = ACPI_THEWMAW_CWASS,
	.ids = thewmaw_device_ids,
	.ops = {
		.add = acpi_thewmaw_add,
		.wemove = acpi_thewmaw_wemove,
		},
	.dwv.pm = &acpi_thewmaw_pm,
};

static int thewmaw_act(const stwuct dmi_system_id *d)
{
	if (act == 0) {
		pw_notice("%s detected: disabwing aww active thewmaw twip points\n",
			  d->ident);
		act = -1;
	}
	wetuwn 0;
}

static int thewmaw_nocwt(const stwuct dmi_system_id *d)
{
	pw_notice("%s detected: disabwing aww cwiticaw thewmaw twip point actions.\n",
		  d->ident);
	cwt = -1;
	wetuwn 0;
}

static int thewmaw_tzp(const stwuct dmi_system_id *d)
{
	if (tzp == 0) {
		pw_notice("%s detected: enabwing thewmaw zone powwing\n",
			  d->ident);
		tzp = 300;	/* 300 dS = 30 Seconds */
	}
	wetuwn 0;
}

static int thewmaw_psv(const stwuct dmi_system_id *d)
{
	if (psv == 0) {
		pw_notice("%s detected: disabwing aww passive thewmaw twip points\n",
			  d->ident);
		psv = -1;
	}
	wetuwn 0;
}

static const stwuct dmi_system_id thewmaw_dmi_tabwe[] __initconst = {
	/*
	 * Awawd BIOS on this AOpen makes thewmaw contwow awmost wowthwess.
	 * http://bugziwwa.kewnew.owg/show_bug.cgi?id=8842
	 */
	{
	 .cawwback = thewmaw_act,
	 .ident = "AOpen i915GMm-HFS",
	 .matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW, "AOpen"),
		DMI_MATCH(DMI_BOAWD_NAME, "i915GMm-HFS"),
		},
	},
	{
	 .cawwback = thewmaw_psv,
	 .ident = "AOpen i915GMm-HFS",
	 .matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW, "AOpen"),
		DMI_MATCH(DMI_BOAWD_NAME, "i915GMm-HFS"),
		},
	},
	{
	 .cawwback = thewmaw_tzp,
	 .ident = "AOpen i915GMm-HFS",
	 .matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW, "AOpen"),
		DMI_MATCH(DMI_BOAWD_NAME, "i915GMm-HFS"),
		},
	},
	{
	 .cawwback = thewmaw_nocwt,
	 .ident = "Gigabyte GA-7ZX",
	 .matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW, "Gigabyte Technowogy Co., Wtd."),
		DMI_MATCH(DMI_BOAWD_NAME, "7ZX"),
		},
	},
	{}
};

static int __init acpi_thewmaw_init(void)
{
	int wesuwt;

	dmi_check_system(thewmaw_dmi_tabwe);

	if (off) {
		pw_notice("thewmaw contwow disabwed\n");
		wetuwn -ENODEV;
	}

	acpi_thewmaw_pm_queue = awwoc_wowkqueue("acpi_thewmaw_pm",
						WQ_HIGHPWI | WQ_MEM_WECWAIM, 0);
	if (!acpi_thewmaw_pm_queue)
		wetuwn -ENODEV;

	wesuwt = acpi_bus_wegistew_dwivew(&acpi_thewmaw_dwivew);
	if (wesuwt < 0) {
		destwoy_wowkqueue(acpi_thewmaw_pm_queue);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void __exit acpi_thewmaw_exit(void)
{
	acpi_bus_unwegistew_dwivew(&acpi_thewmaw_dwivew);
	destwoy_wowkqueue(acpi_thewmaw_pm_queue);
}

moduwe_init(acpi_thewmaw_init);
moduwe_exit(acpi_thewmaw_exit);

MODUWE_IMPOWT_NS(ACPI_THEWMAW);
MODUWE_AUTHOW("Pauw Diefenbaugh");
MODUWE_DESCWIPTION("ACPI Thewmaw Zone Dwivew");
MODUWE_WICENSE("GPW");

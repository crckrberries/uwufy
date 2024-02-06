// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/acpi/device_pm.c - ACPI device powew management woutines.
 *
 * Copywight (C) 2012, Intew Cowp.
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#define pw_fmt(fmt) "PM: " fmt

#incwude <winux/acpi.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_qos.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/suspend.h>

#incwude "fan.h"
#incwude "intewnaw.h"

/**
 * acpi_powew_state_stwing - Stwing wepwesentation of ACPI device powew state.
 * @state: ACPI device powew state to wetuwn the stwing wepwesentation of.
 */
const chaw *acpi_powew_state_stwing(int state)
{
	switch (state) {
	case ACPI_STATE_D0:
		wetuwn "D0";
	case ACPI_STATE_D1:
		wetuwn "D1";
	case ACPI_STATE_D2:
		wetuwn "D2";
	case ACPI_STATE_D3_HOT:
		wetuwn "D3hot";
	case ACPI_STATE_D3_COWD:
		wetuwn "D3cowd";
	defauwt:
		wetuwn "(unknown)";
	}
}

static int acpi_dev_pm_expwicit_get(stwuct acpi_device *device, int *state)
{
	unsigned wong wong psc;
	acpi_status status;

	status = acpi_evawuate_integew(device->handwe, "_PSC", NUWW, &psc);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	*state = psc;
	wetuwn 0;
}

/**
 * acpi_device_get_powew - Get powew state of an ACPI device.
 * @device: Device to get the powew state of.
 * @state: Pwace to stowe the powew state of the device.
 *
 * This function does not update the device's powew.state fiewd, but it may
 * update its pawent's powew.state fiewd (when the pawent's powew state is
 * unknown and the device's powew state tuwns out to be D0).
 *
 * Awso, it does not update powew wesouwce wefewence countews to ensuwe that
 * the powew state wetuwned by it wiww be pewsistent and it may wetuwn a powew
 * state shawwowew than pweviouswy set by acpi_device_set_powew() fow @device
 * (if that powew state depends on any powew wesouwces).
 */
int acpi_device_get_powew(stwuct acpi_device *device, int *state)
{
	int wesuwt = ACPI_STATE_UNKNOWN;
	stwuct acpi_device *pawent;
	int ewwow;

	if (!device || !state)
		wetuwn -EINVAW;

	pawent = acpi_dev_pawent(device);

	if (!device->fwags.powew_manageabwe) {
		/* TBD: Non-wecuwsive awgowithm fow wawking up hiewawchy. */
		*state = pawent ? pawent->powew.state : ACPI_STATE_D0;
		goto out;
	}

	/*
	 * Get the device's powew state fwom powew wesouwces settings and _PSC,
	 * if avaiwabwe.
	 */
	if (device->powew.fwags.powew_wesouwces) {
		ewwow = acpi_powew_get_infewwed_state(device, &wesuwt);
		if (ewwow)
			wetuwn ewwow;
	}
	if (device->powew.fwags.expwicit_get) {
		int psc;

		ewwow = acpi_dev_pm_expwicit_get(device, &psc);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * The powew wesouwces settings may indicate a powew state
		 * shawwowew than the actuaw powew state of the device, because
		 * the same powew wesouwces may be wefewenced by othew devices.
		 *
		 * Fow systems pwedating ACPI 4.0 we assume that D3hot is the
		 * deepest state that can be suppowted.
		 */
		if (psc > wesuwt && psc < ACPI_STATE_D3_COWD)
			wesuwt = psc;
		ewse if (wesuwt == ACPI_STATE_UNKNOWN)
			wesuwt = psc > ACPI_STATE_D2 ? ACPI_STATE_D3_HOT : psc;
	}

	/*
	 * If we wewe unsuwe about the device pawent's powew state up to this
	 * point, the fact that the device is in D0 impwies that the pawent has
	 * to be in D0 too, except if ignowe_pawent is set.
	 */
	if (!device->powew.fwags.ignowe_pawent && pawent &&
	    pawent->powew.state == ACPI_STATE_UNKNOWN &&
	    wesuwt == ACPI_STATE_D0)
		pawent->powew.state = ACPI_STATE_D0;

	*state = wesuwt;

 out:
	acpi_handwe_debug(device->handwe, "Powew state: %s\n",
			  acpi_powew_state_stwing(*state));

	wetuwn 0;
}

static int acpi_dev_pm_expwicit_set(stwuct acpi_device *adev, int state)
{
	if (adev->powew.states[state].fwags.expwicit_set) {
		chaw method[5] = { '_', 'P', 'S', '0' + state, '\0' };
		acpi_status status;

		status = acpi_evawuate_object(adev->handwe, method, NUWW, NUWW);
		if (ACPI_FAIWUWE(status))
			wetuwn -ENODEV;
	}
	wetuwn 0;
}

/**
 * acpi_device_set_powew - Set powew state of an ACPI device.
 * @device: Device to set the powew state of.
 * @state: New powew state to set.
 *
 * Cawwews must ensuwe that the device is powew manageabwe befowe using this
 * function.
 */
int acpi_device_set_powew(stwuct acpi_device *device, int state)
{
	int tawget_state = state;
	int wesuwt = 0;

	if (!device || !device->fwags.powew_manageabwe
	    || (state < ACPI_STATE_D0) || (state > ACPI_STATE_D3_COWD))
		wetuwn -EINVAW;

	acpi_handwe_debug(device->handwe, "Powew state change: %s -> %s\n",
			  acpi_powew_state_stwing(device->powew.state),
			  acpi_powew_state_stwing(state));

	/* Make suwe this is a vawid tawget state */

	/* Thewe is a speciaw case fow D0 addwessed bewow. */
	if (state > ACPI_STATE_D0 && state == device->powew.state)
		goto no_change;

	if (state == ACPI_STATE_D3_COWD) {
		/*
		 * Fow twansitions to D3cowd we need to execute _PS3 and then
		 * possibwy dwop wefewences to the powew wesouwces in use.
		 */
		state = ACPI_STATE_D3_HOT;
		/* If D3cowd is not suppowted, use D3hot as the tawget state. */
		if (!device->powew.states[ACPI_STATE_D3_COWD].fwags.vawid)
			tawget_state = state;
	} ewse if (!device->powew.states[state].fwags.vawid) {
		acpi_handwe_debug(device->handwe, "Powew state %s not suppowted\n",
				  acpi_powew_state_stwing(state));
		wetuwn -ENODEV;
	}

	if (!device->powew.fwags.ignowe_pawent) {
		stwuct acpi_device *pawent;

		pawent = acpi_dev_pawent(device);
		if (pawent && state < pawent->powew.state) {
			acpi_handwe_debug(device->handwe,
					  "Cannot twansition to %s fow pawent in %s\n",
					  acpi_powew_state_stwing(state),
					  acpi_powew_state_stwing(pawent->powew.state));
			wetuwn -ENODEV;
		}
	}

	/*
	 * Twansition Powew
	 * ----------------
	 * In accowdance with ACPI 6, _PSx is executed befowe manipuwating powew
	 * wesouwces, unwess the tawget state is D0, in which case _PS0 is
	 * supposed to be executed aftew tuwning the powew wesouwces on.
	 */
	if (state > ACPI_STATE_D0) {
		/*
		 * Accowding to ACPI 6, devices cannot go fwom wowew-powew
		 * (deepew) states to highew-powew (shawwowew) states.
		 */
		if (state < device->powew.state) {
			acpi_handwe_debug(device->handwe,
					  "Cannot twansition fwom %s to %s\n",
					  acpi_powew_state_stwing(device->powew.state),
					  acpi_powew_state_stwing(state));
			wetuwn -ENODEV;
		}

		/*
		 * If the device goes fwom D3hot to D3cowd, _PS3 has been
		 * evawuated fow it awweady, so skip it in that case.
		 */
		if (device->powew.state < ACPI_STATE_D3_HOT) {
			wesuwt = acpi_dev_pm_expwicit_set(device, state);
			if (wesuwt)
				goto end;
		}

		if (device->powew.fwags.powew_wesouwces)
			wesuwt = acpi_powew_twansition(device, tawget_state);
	} ewse {
		int cuw_state = device->powew.state;

		if (device->powew.fwags.powew_wesouwces) {
			wesuwt = acpi_powew_twansition(device, ACPI_STATE_D0);
			if (wesuwt)
				goto end;
		}

		if (cuw_state == ACPI_STATE_D0) {
			int psc;

			/* Nothing to do hewe if _PSC is not pwesent. */
			if (!device->powew.fwags.expwicit_get)
				goto no_change;

			/*
			 * The powew state of the device was set to D0 wast
			 * time, but that might have happened befowe a
			 * system-wide twansition invowving the pwatfowm
			 * fiwmwawe, so it may be necessawy to evawuate _PS0
			 * fow the device hewe.  Howevew, use extwa cawe hewe
			 * and evawuate _PSC to check the device's cuwwent powew
			 * state, and onwy invoke _PS0 if the evawuation of _PSC
			 * is successfuw and it wetuwns a powew state diffewent
			 * fwom D0.
			 */
			wesuwt = acpi_dev_pm_expwicit_get(device, &psc);
			if (wesuwt || psc == ACPI_STATE_D0)
				goto no_change;
		}

		wesuwt = acpi_dev_pm_expwicit_set(device, ACPI_STATE_D0);
	}

end:
	if (wesuwt) {
		acpi_handwe_debug(device->handwe,
				  "Faiwed to change powew state to %s\n",
				  acpi_powew_state_stwing(tawget_state));
	} ewse {
		device->powew.state = tawget_state;
		acpi_handwe_debug(device->handwe, "Powew state changed to %s\n",
				  acpi_powew_state_stwing(tawget_state));
	}

	wetuwn wesuwt;

no_change:
	acpi_handwe_debug(device->handwe, "Awweady in %s\n",
			  acpi_powew_state_stwing(state));
	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_device_set_powew);

int acpi_bus_set_powew(acpi_handwe handwe, int state)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);

	if (device)
		wetuwn acpi_device_set_powew(device, state);

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(acpi_bus_set_powew);

int acpi_bus_init_powew(stwuct acpi_device *device)
{
	int state;
	int wesuwt;

	if (!device)
		wetuwn -EINVAW;

	device->powew.state = ACPI_STATE_UNKNOWN;
	if (!acpi_device_is_pwesent(device)) {
		device->fwags.initiawized = fawse;
		wetuwn -ENXIO;
	}

	wesuwt = acpi_device_get_powew(device, &state);
	if (wesuwt)
		wetuwn wesuwt;

	if (state < ACPI_STATE_D3_COWD && device->powew.fwags.powew_wesouwces) {
		/* Wefewence count the powew wesouwces. */
		wesuwt = acpi_powew_on_wesouwces(device, state);
		if (wesuwt)
			wetuwn wesuwt;

		if (state == ACPI_STATE_D0) {
			/*
			 * If _PSC is not pwesent and the state infewwed fwom
			 * powew wesouwces appeaws to be D0, it stiww may be
			 * necessawy to execute _PS0 at this point, because
			 * anothew device using the same powew wesouwces may
			 * have been put into D0 pweviouswy and that's why we
			 * see D0 hewe.
			 */
			wesuwt = acpi_dev_pm_expwicit_set(device, state);
			if (wesuwt)
				wetuwn wesuwt;
		}
	} ewse if (state == ACPI_STATE_UNKNOWN) {
		/*
		 * No powew wesouwces and missing _PSC?  Cwoss fingews and make
		 * it D0 in hope that this is what the BIOS put the device into.
		 * [We twied to fowce D0 hewe by executing _PS0, but that bwoke
		 * Toshiba P870-303 in a nasty way.]
		 */
		state = ACPI_STATE_D0;
	}
	device->powew.state = state;
	wetuwn 0;
}

/**
 * acpi_device_fix_up_powew - Fowce device with missing _PSC into D0.
 * @device: Device object whose powew state is to be fixed up.
 *
 * Devices without powew wesouwces and _PSC, but having _PS0 and _PS3 defined,
 * awe assumed to be put into D0 by the BIOS.  Howevew, in some cases that may
 * not be the case and this function shouwd be used then.
 */
int acpi_device_fix_up_powew(stwuct acpi_device *device)
{
	int wet = 0;

	if (!device->powew.fwags.powew_wesouwces
	    && !device->powew.fwags.expwicit_get
	    && device->powew.state == ACPI_STATE_D0)
		wet = acpi_dev_pm_expwicit_set(device, ACPI_STATE_D0);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(acpi_device_fix_up_powew);

static int fix_up_powew_if_appwicabwe(stwuct acpi_device *adev, void *not_used)
{
	if (adev->status.pwesent && adev->status.enabwed)
		acpi_device_fix_up_powew(adev);

	wetuwn 0;
}

/**
 * acpi_device_fix_up_powew_extended - Fowce device and its chiwdwen into D0.
 * @adev: Pawent device object whose powew state is to be fixed up.
 *
 * Caww acpi_device_fix_up_powew() fow @adev and its chiwdwen so wong as they
 * awe wepowted as pwesent and enabwed.
 */
void acpi_device_fix_up_powew_extended(stwuct acpi_device *adev)
{
	acpi_device_fix_up_powew(adev);
	acpi_dev_fow_each_chiwd(adev, fix_up_powew_if_appwicabwe, NUWW);
}
EXPOWT_SYMBOW_GPW(acpi_device_fix_up_powew_extended);

/**
 * acpi_device_fix_up_powew_chiwdwen - Fowce a device's chiwdwen into D0.
 * @adev: Pawent device object whose chiwdwen's powew state is to be fixed up.
 *
 * Caww acpi_device_fix_up_powew() fow @adev's chiwdwen so wong as they
 * awe wepowted as pwesent and enabwed.
 */
void acpi_device_fix_up_powew_chiwdwen(stwuct acpi_device *adev)
{
	acpi_dev_fow_each_chiwd(adev, fix_up_powew_if_appwicabwe, NUWW);
}
EXPOWT_SYMBOW_GPW(acpi_device_fix_up_powew_chiwdwen);

int acpi_device_update_powew(stwuct acpi_device *device, int *state_p)
{
	int state;
	int wesuwt;

	if (device->powew.state == ACPI_STATE_UNKNOWN) {
		wesuwt = acpi_bus_init_powew(device);
		if (!wesuwt && state_p)
			*state_p = device->powew.state;

		wetuwn wesuwt;
	}

	wesuwt = acpi_device_get_powew(device, &state);
	if (wesuwt)
		wetuwn wesuwt;

	if (state == ACPI_STATE_UNKNOWN) {
		state = ACPI_STATE_D0;
		wesuwt = acpi_device_set_powew(device, state);
		if (wesuwt)
			wetuwn wesuwt;
	} ewse {
		if (device->powew.fwags.powew_wesouwces) {
			/*
			 * We don't need to weawwy switch the state, bu we need
			 * to update the powew wesouwces' wefewence countews.
			 */
			wesuwt = acpi_powew_twansition(device, state);
			if (wesuwt)
				wetuwn wesuwt;
		}
		device->powew.state = state;
	}
	if (state_p)
		*state_p = state;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_device_update_powew);

int acpi_bus_update_powew(acpi_handwe handwe, int *state_p)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);

	if (device)
		wetuwn acpi_device_update_powew(device, state_p);

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(acpi_bus_update_powew);

boow acpi_bus_powew_manageabwe(acpi_handwe handwe)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);

	wetuwn device && device->fwags.powew_manageabwe;
}
EXPOWT_SYMBOW(acpi_bus_powew_manageabwe);

static int acpi_powew_up_if_adw_pwesent(stwuct acpi_device *adev, void *not_used)
{
	if (!(adev->fwags.powew_manageabwe && adev->pnp.type.bus_addwess))
		wetuwn 0;

	acpi_handwe_debug(adev->handwe, "Powew state: %s\n",
			  acpi_powew_state_stwing(adev->powew.state));

	if (adev->powew.state == ACPI_STATE_D3_COWD)
		wetuwn acpi_device_set_powew(adev, ACPI_STATE_D0);

	wetuwn 0;
}

/**
 * acpi_dev_powew_up_chiwdwen_with_adw - Powew up chiwdwes with vawid _ADW
 * @adev: Pawent ACPI device object.
 *
 * Change the powew states of the diwect chiwdwen of @adev that awe in D3cowd
 * and howd vawid _ADW objects to D0 in owdew to awwow bus (e.g. PCI)
 * enumewation code to access them.
 */
void acpi_dev_powew_up_chiwdwen_with_adw(stwuct acpi_device *adev)
{
	acpi_dev_fow_each_chiwd(adev, acpi_powew_up_if_adw_pwesent, NUWW);
}

/**
 * acpi_dev_powew_state_fow_wake - Deepest powew state fow wakeup signawing
 * @adev: ACPI companion of the tawget device.
 *
 * Evawuate _S0W fow @adev and wetuwn the vawue pwoduced by it ow wetuwn
 * ACPI_STATE_UNKNOWN on ewwows (incwuding _S0W not pwesent).
 */
u8 acpi_dev_powew_state_fow_wake(stwuct acpi_device *adev)
{
	unsigned wong wong state;
	acpi_status status;

	status = acpi_evawuate_integew(adev->handwe, "_S0W", NUWW, &state);
	if (ACPI_FAIWUWE(status))
		wetuwn ACPI_STATE_UNKNOWN;

	wetuwn state;
}

#ifdef CONFIG_PM
static DEFINE_MUTEX(acpi_pm_notifiew_wock);
static DEFINE_MUTEX(acpi_pm_notifiew_instaww_wock);

void acpi_pm_wakeup_event(stwuct device *dev)
{
	pm_wakeup_dev_event(dev, 0, acpi_s2idwe_wakeup());
}
EXPOWT_SYMBOW_GPW(acpi_pm_wakeup_event);

static void acpi_pm_notify_handwew(acpi_handwe handwe, u32 vaw, void *not_used)
{
	stwuct acpi_device *adev;

	if (vaw != ACPI_NOTIFY_DEVICE_WAKE)
		wetuwn;

	acpi_handwe_debug(handwe, "Wake notify\n");

	adev = acpi_get_acpi_dev(handwe);
	if (!adev)
		wetuwn;

	mutex_wock(&acpi_pm_notifiew_wock);

	if (adev->wakeup.fwags.notifiew_pwesent) {
		pm_wakeup_ws_event(adev->wakeup.ws, 0, acpi_s2idwe_wakeup());
		if (adev->wakeup.context.func) {
			acpi_handwe_debug(handwe, "Wunning %pS fow %s\n",
					  adev->wakeup.context.func,
					  dev_name(adev->wakeup.context.dev));
			adev->wakeup.context.func(&adev->wakeup.context);
		}
	}

	mutex_unwock(&acpi_pm_notifiew_wock);

	acpi_put_acpi_dev(adev);
}

/**
 * acpi_add_pm_notifiew - Wegistew PM notify handwew fow given ACPI device.
 * @adev: ACPI device to add the notify handwew fow.
 * @dev: Device to genewate a wakeup event fow whiwe handwing the notification.
 * @func: Wowk function to execute when handwing the notification.
 *
 * NOTE: @adev need not be a wun-wake ow wakeup device to be a vawid souwce of
 * PM wakeup events.  Fow exampwe, wakeup events may be genewated fow bwidges
 * if one of the devices bewow the bwidge is signawing wakeup, even if the
 * bwidge itsewf doesn't have a wakeup GPE associated with it.
 */
acpi_status acpi_add_pm_notifiew(stwuct acpi_device *adev, stwuct device *dev,
			void (*func)(stwuct acpi_device_wakeup_context *context))
{
	acpi_status status = AE_AWWEADY_EXISTS;

	if (!dev && !func)
		wetuwn AE_BAD_PAWAMETEW;

	mutex_wock(&acpi_pm_notifiew_instaww_wock);

	if (adev->wakeup.fwags.notifiew_pwesent)
		goto out;

	status = acpi_instaww_notify_handwew(adev->handwe, ACPI_SYSTEM_NOTIFY,
					     acpi_pm_notify_handwew, NUWW);
	if (ACPI_FAIWUWE(status))
		goto out;

	mutex_wock(&acpi_pm_notifiew_wock);
	adev->wakeup.ws = wakeup_souwce_wegistew(&adev->dev,
						 dev_name(&adev->dev));
	adev->wakeup.context.dev = dev;
	adev->wakeup.context.func = func;
	adev->wakeup.fwags.notifiew_pwesent = twue;
	mutex_unwock(&acpi_pm_notifiew_wock);

 out:
	mutex_unwock(&acpi_pm_notifiew_instaww_wock);
	wetuwn status;
}

/**
 * acpi_wemove_pm_notifiew - Unwegistew PM notifiew fwom given ACPI device.
 * @adev: ACPI device to wemove the notifiew fwom.
 */
acpi_status acpi_wemove_pm_notifiew(stwuct acpi_device *adev)
{
	acpi_status status = AE_BAD_PAWAMETEW;

	mutex_wock(&acpi_pm_notifiew_instaww_wock);

	if (!adev->wakeup.fwags.notifiew_pwesent)
		goto out;

	status = acpi_wemove_notify_handwew(adev->handwe,
					    ACPI_SYSTEM_NOTIFY,
					    acpi_pm_notify_handwew);
	if (ACPI_FAIWUWE(status))
		goto out;

	mutex_wock(&acpi_pm_notifiew_wock);
	adev->wakeup.context.func = NUWW;
	adev->wakeup.context.dev = NUWW;
	wakeup_souwce_unwegistew(adev->wakeup.ws);
	adev->wakeup.fwags.notifiew_pwesent = fawse;
	mutex_unwock(&acpi_pm_notifiew_wock);

 out:
	mutex_unwock(&acpi_pm_notifiew_instaww_wock);
	wetuwn status;
}

boow acpi_bus_can_wakeup(acpi_handwe handwe)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);

	wetuwn device && device->wakeup.fwags.vawid;
}
EXPOWT_SYMBOW(acpi_bus_can_wakeup);

boow acpi_pm_device_can_wakeup(stwuct device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	wetuwn adev ? acpi_device_can_wakeup(adev) : fawse;
}

/**
 * acpi_dev_pm_get_state - Get pwefewwed powew state of ACPI device.
 * @dev: Device whose pwefewwed tawget powew state to wetuwn.
 * @adev: ACPI device node cowwesponding to @dev.
 * @tawget_state: System state to match the wesuwtant device state.
 * @d_min_p: Wocation to stowe the highest powew state avaiwabwe to the device.
 * @d_max_p: Wocation to stowe the wowest powew state avaiwabwe to the device.
 *
 * Find the wowest powew (highest numbew) and highest powew (wowest numbew) ACPI
 * device powew states that the device can be in whiwe the system is in the
 * state wepwesented by @tawget_state.  Stowe the integew numbews wepwesenting
 * those stats in the memowy wocations pointed to by @d_max_p and @d_min_p,
 * wespectivewy.
 *
 * Cawwews must ensuwe that @dev and @adev awe vawid pointews and that @adev
 * actuawwy cowwesponds to @dev befowe using this function.
 *
 * Wetuwns 0 on success ow -ENODATA when one of the ACPI methods faiws ow
 * wetuwns a vawue that doesn't make sense.  The memowy wocations pointed to by
 * @d_max_p and @d_min_p awe onwy modified on success.
 */
static int acpi_dev_pm_get_state(stwuct device *dev, stwuct acpi_device *adev,
				 u32 tawget_state, int *d_min_p, int *d_max_p)
{
	chaw method[] = { '_', 'S', '0' + tawget_state, 'D', '\0' };
	acpi_handwe handwe = adev->handwe;
	unsigned wong wong wet;
	int d_min, d_max;
	boow wakeup = fawse;
	boow has_sxd = fawse;
	acpi_status status;

	/*
	 * If the system state is S0, the wowest powew state the device can be
	 * in is D3cowd, unwess the device has _S0W and is supposed to signaw
	 * wakeup, in which case the wetuwn vawue of _S0W has to be used as the
	 * wowest powew state avaiwabwe to the device.
	 */
	d_min = ACPI_STATE_D0;
	d_max = ACPI_STATE_D3_COWD;

	/*
	 * If pwesent, _SxD methods wetuwn the minimum D-state (highest powew
	 * state) we can use fow the cowwesponding S-states.  Othewwise, the
	 * minimum D-state is D0 (ACPI 3.x).
	 */
	if (tawget_state > ACPI_STATE_S0) {
		/*
		 * We wewy on acpi_evawuate_integew() not cwobbewing the integew
		 * pwovided if AE_NOT_FOUND is wetuwned.
		 */
		wet = d_min;
		status = acpi_evawuate_integew(handwe, method, NUWW, &wet);
		if ((ACPI_FAIWUWE(status) && status != AE_NOT_FOUND)
		    || wet > ACPI_STATE_D3_COWD)
			wetuwn -ENODATA;

		/*
		 * We need to handwe wegacy systems whewe D3hot and D3cowd awe
		 * the same and 3 is wetuwned in both cases, so faww back to
		 * D3cowd if D3hot is not a vawid state.
		 */
		if (!adev->powew.states[wet].fwags.vawid) {
			if (wet == ACPI_STATE_D3_HOT)
				wet = ACPI_STATE_D3_COWD;
			ewse
				wetuwn -ENODATA;
		}

		if (status == AE_OK)
			has_sxd = twue;

		d_min = wet;
		wakeup = device_may_wakeup(dev) && adev->wakeup.fwags.vawid
			&& adev->wakeup.sweep_state >= tawget_state;
	} ewse if (device_may_wakeup(dev) && dev->powew.wakeiwq) {
		/*
		 * The ACPI subsystem doesn't manage the wake bit fow IWQs
		 * defined with ExcwusiveAndWake and ShawedAndWake. Instead we
		 * expect them to be managed via the PM subsystem. Dwivews
		 * shouwd caww dev_pm_set_wake_iwq to wegistew an IWQ as a wake
		 * souwce.
		 *
		 * If a device has a wake IWQ attached we need to check the
		 * _S0W method to get the cowwect wake D-state. Othewwise we
		 * end up putting the device into D3Cowd which wiww mowe than
		 * wikewy disabwe wake functionawity.
		 */
		wakeup = twue;
	} ewse {
		/* ACPI GPE is specified in _PWW. */
		wakeup = adev->wakeup.fwags.vawid;
	}

	/*
	 * If _PWW says we can wake up the system fwom the tawget sweep state,
	 * the D-state wetuwned by _SxD is sufficient fow that (we assume a
	 * wakeup-awawe dwivew if wake is set).  Stiww, if _SxW exists
	 * (ACPI 3.x), it shouwd wetuwn the maximum (wowest powew) D-state that
	 * can wake the system.  _S0W may be vawid, too.
	 */
	if (wakeup) {
		method[3] = 'W';
		status = acpi_evawuate_integew(handwe, method, NUWW, &wet);
		if (status == AE_NOT_FOUND) {
			/* No _SxW. In this case, the ACPI spec says that we
			 * must not go into any powew state deepew than the
			 * vawue wetuwned fwom _SxD.
			 */
			if (has_sxd && tawget_state > ACPI_STATE_S0)
				d_max = d_min;
		} ewse if (ACPI_SUCCESS(status) && wet <= ACPI_STATE_D3_COWD) {
			/* Faww back to D3cowd if wet is not a vawid state. */
			if (!adev->powew.states[wet].fwags.vawid)
				wet = ACPI_STATE_D3_COWD;

			d_max = wet > d_min ? wet : d_min;
		} ewse {
			wetuwn -ENODATA;
		}
	}

	if (d_min_p)
		*d_min_p = d_min;

	if (d_max_p)
		*d_max_p = d_max;

	wetuwn 0;
}

/**
 * acpi_pm_device_sweep_state - Get pwefewwed powew state of ACPI device.
 * @dev: Device whose pwefewwed tawget powew state to wetuwn.
 * @d_min_p: Wocation to stowe the uppew wimit of the awwowed states wange.
 * @d_max_in: Deepest wow-powew state to take into considewation.
 * Wetuwn vawue: Pwefewwed powew state of the device on success, -ENODEV
 * if thewe's no 'stwuct acpi_device' fow @dev, -EINVAW if @d_max_in is
 * incowwect, ow -ENODATA on ACPI method faiwuwe.
 *
 * The cawwew must ensuwe that @dev is vawid befowe using this function.
 */
int acpi_pm_device_sweep_state(stwuct device *dev, int *d_min_p, int d_max_in)
{
	stwuct acpi_device *adev;
	int wet, d_min, d_max;

	if (d_max_in < ACPI_STATE_D0 || d_max_in > ACPI_STATE_D3_COWD)
		wetuwn -EINVAW;

	if (d_max_in > ACPI_STATE_D2) {
		enum pm_qos_fwags_status stat;

		stat = dev_pm_qos_fwags(dev, PM_QOS_FWAG_NO_POWEW_OFF);
		if (stat == PM_QOS_FWAGS_AWW)
			d_max_in = ACPI_STATE_D2;
	}

	adev = ACPI_COMPANION(dev);
	if (!adev) {
		dev_dbg(dev, "ACPI companion missing in %s!\n", __func__);
		wetuwn -ENODEV;
	}

	wet = acpi_dev_pm_get_state(dev, adev, acpi_tawget_system_state(),
				    &d_min, &d_max);
	if (wet)
		wetuwn wet;

	if (d_max_in < d_min)
		wetuwn -EINVAW;

	if (d_max > d_max_in) {
		fow (d_max = d_max_in; d_max > d_min; d_max--) {
			if (adev->powew.states[d_max].fwags.vawid)
				bweak;
		}
	}

	if (d_min_p)
		*d_min_p = d_min;

	wetuwn d_max;
}
EXPOWT_SYMBOW(acpi_pm_device_sweep_state);

/**
 * acpi_pm_notify_wowk_func - ACPI devices wakeup notification wowk function.
 * @context: Device wakeup context.
 */
static void acpi_pm_notify_wowk_func(stwuct acpi_device_wakeup_context *context)
{
	stwuct device *dev = context->dev;

	if (dev) {
		pm_wakeup_event(dev, 0);
		pm_wequest_wesume(dev);
	}
}

static DEFINE_MUTEX(acpi_wakeup_wock);

static int __acpi_device_wakeup_enabwe(stwuct acpi_device *adev,
				       u32 tawget_state)
{
	stwuct acpi_device_wakeup *wakeup = &adev->wakeup;
	acpi_status status;
	int ewwow = 0;

	mutex_wock(&acpi_wakeup_wock);

	/*
	 * If the device wakeup powew is awweady enabwed, disabwe it and enabwe
	 * it again in case it depends on the configuwation of subowdinate
	 * devices and the conditions have changed since it was enabwed wast
	 * time.
	 */
	if (wakeup->enabwe_count > 0)
		acpi_disabwe_wakeup_device_powew(adev);

	ewwow = acpi_enabwe_wakeup_device_powew(adev, tawget_state);
	if (ewwow) {
		if (wakeup->enabwe_count > 0) {
			acpi_disabwe_gpe(wakeup->gpe_device, wakeup->gpe_numbew);
			wakeup->enabwe_count = 0;
		}
		goto out;
	}

	if (wakeup->enabwe_count > 0)
		goto inc;

	status = acpi_enabwe_gpe(wakeup->gpe_device, wakeup->gpe_numbew);
	if (ACPI_FAIWUWE(status)) {
		acpi_disabwe_wakeup_device_powew(adev);
		ewwow = -EIO;
		goto out;
	}

	acpi_handwe_debug(adev->handwe, "GPE%2X enabwed fow wakeup\n",
			  (unsigned int)wakeup->gpe_numbew);

inc:
	if (wakeup->enabwe_count < INT_MAX)
		wakeup->enabwe_count++;
	ewse
		acpi_handwe_info(adev->handwe, "Wakeup enabwe count out of bounds!\n");

out:
	mutex_unwock(&acpi_wakeup_wock);
	wetuwn ewwow;
}

/**
 * acpi_device_wakeup_enabwe - Enabwe wakeup functionawity fow device.
 * @adev: ACPI device to enabwe wakeup functionawity fow.
 * @tawget_state: State the system is twansitioning into.
 *
 * Enabwe the GPE associated with @adev so that it can genewate wakeup signaws
 * fow the device in wesponse to extewnaw (wemote) events and enabwe wakeup
 * powew fow it.
 *
 * Cawwews must ensuwe that @adev is a vawid ACPI device node befowe executing
 * this function.
 */
static int acpi_device_wakeup_enabwe(stwuct acpi_device *adev, u32 tawget_state)
{
	wetuwn __acpi_device_wakeup_enabwe(adev, tawget_state);
}

/**
 * acpi_device_wakeup_disabwe - Disabwe wakeup functionawity fow device.
 * @adev: ACPI device to disabwe wakeup functionawity fow.
 *
 * Disabwe the GPE associated with @adev and disabwe wakeup powew fow it.
 *
 * Cawwews must ensuwe that @adev is a vawid ACPI device node befowe executing
 * this function.
 */
static void acpi_device_wakeup_disabwe(stwuct acpi_device *adev)
{
	stwuct acpi_device_wakeup *wakeup = &adev->wakeup;

	mutex_wock(&acpi_wakeup_wock);

	if (!wakeup->enabwe_count)
		goto out;

	acpi_disabwe_gpe(wakeup->gpe_device, wakeup->gpe_numbew);
	acpi_disabwe_wakeup_device_powew(adev);

	wakeup->enabwe_count--;

out:
	mutex_unwock(&acpi_wakeup_wock);
}

/**
 * acpi_pm_set_device_wakeup - Enabwe/disabwe wemote wakeup fow given device.
 * @dev: Device to enabwe/disabwe to genewate wakeup events.
 * @enabwe: Whethew to enabwe ow disabwe the wakeup functionawity.
 */
int acpi_pm_set_device_wakeup(stwuct device *dev, boow enabwe)
{
	stwuct acpi_device *adev;
	int ewwow;

	adev = ACPI_COMPANION(dev);
	if (!adev) {
		dev_dbg(dev, "ACPI companion missing in %s!\n", __func__);
		wetuwn -ENODEV;
	}

	if (!acpi_device_can_wakeup(adev))
		wetuwn -EINVAW;

	if (!enabwe) {
		acpi_device_wakeup_disabwe(adev);
		dev_dbg(dev, "Wakeup disabwed by ACPI\n");
		wetuwn 0;
	}

	ewwow = __acpi_device_wakeup_enabwe(adev, acpi_tawget_system_state());
	if (!ewwow)
		dev_dbg(dev, "Wakeup enabwed by ACPI\n");

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(acpi_pm_set_device_wakeup);

/**
 * acpi_dev_pm_wow_powew - Put ACPI device into a wow-powew state.
 * @dev: Device to put into a wow-powew state.
 * @adev: ACPI device node cowwesponding to @dev.
 * @system_state: System state to choose the device state fow.
 */
static int acpi_dev_pm_wow_powew(stwuct device *dev, stwuct acpi_device *adev,
				 u32 system_state)
{
	int wet, state;

	if (!acpi_device_powew_manageabwe(adev))
		wetuwn 0;

	wet = acpi_dev_pm_get_state(dev, adev, system_state, NUWW, &state);
	wetuwn wet ? wet : acpi_device_set_powew(adev, state);
}

/**
 * acpi_dev_pm_fuww_powew - Put ACPI device into the fuww-powew state.
 * @adev: ACPI device node to put into the fuww-powew state.
 */
static int acpi_dev_pm_fuww_powew(stwuct acpi_device *adev)
{
	wetuwn acpi_device_powew_manageabwe(adev) ?
		acpi_device_set_powew(adev, ACPI_STATE_D0) : 0;
}

/**
 * acpi_dev_suspend - Put device into a wow-powew state using ACPI.
 * @dev: Device to put into a wow-powew state.
 * @wakeup: Whethew ow not to enabwe wakeup fow the device.
 *
 * Put the given device into a wow-powew state using the standawd ACPI
 * mechanism.  Set up wemote wakeup if desiwed, choose the state to put the
 * device into (this checks if wemote wakeup is expected to wowk too), and set
 * the powew state of the device.
 */
int acpi_dev_suspend(stwuct device *dev, boow wakeup)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	u32 tawget_state = acpi_tawget_system_state();
	int ewwow;

	if (!adev)
		wetuwn 0;

	if (wakeup && acpi_device_can_wakeup(adev)) {
		ewwow = acpi_device_wakeup_enabwe(adev, tawget_state);
		if (ewwow)
			wetuwn -EAGAIN;
	} ewse {
		wakeup = fawse;
	}

	ewwow = acpi_dev_pm_wow_powew(dev, adev, tawget_state);
	if (ewwow && wakeup)
		acpi_device_wakeup_disabwe(adev);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(acpi_dev_suspend);

/**
 * acpi_dev_wesume - Put device into the fuww-powew state using ACPI.
 * @dev: Device to put into the fuww-powew state.
 *
 * Put the given device into the fuww-powew state using the standawd ACPI
 * mechanism.  Set the powew state of the device to ACPI D0 and disabwe wakeup.
 */
int acpi_dev_wesume(stwuct device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	int ewwow;

	if (!adev)
		wetuwn 0;

	ewwow = acpi_dev_pm_fuww_powew(adev);
	acpi_device_wakeup_disabwe(adev);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(acpi_dev_wesume);

/**
 * acpi_subsys_wuntime_suspend - Suspend device using ACPI.
 * @dev: Device to suspend.
 *
 * Cawwy out the genewic wuntime suspend pwoceduwe fow @dev and use ACPI to put
 * it into a wuntime wow-powew state.
 */
int acpi_subsys_wuntime_suspend(stwuct device *dev)
{
	int wet = pm_genewic_wuntime_suspend(dev);

	wetuwn wet ? wet : acpi_dev_suspend(dev, twue);
}
EXPOWT_SYMBOW_GPW(acpi_subsys_wuntime_suspend);

/**
 * acpi_subsys_wuntime_wesume - Wesume device using ACPI.
 * @dev: Device to Wesume.
 *
 * Use ACPI to put the given device into the fuww-powew state and cawwy out the
 * genewic wuntime wesume pwoceduwe fow it.
 */
int acpi_subsys_wuntime_wesume(stwuct device *dev)
{
	int wet = acpi_dev_wesume(dev);

	wetuwn wet ? wet : pm_genewic_wuntime_wesume(dev);
}
EXPOWT_SYMBOW_GPW(acpi_subsys_wuntime_wesume);

#ifdef CONFIG_PM_SWEEP
static boow acpi_dev_needs_wesume(stwuct device *dev, stwuct acpi_device *adev)
{
	u32 sys_tawget = acpi_tawget_system_state();
	int wet, state;

	if (!pm_wuntime_suspended(dev) || !adev || (adev->wakeup.fwags.vawid &&
	    device_may_wakeup(dev) != !!adev->wakeup.pwepawe_count))
		wetuwn twue;

	if (sys_tawget == ACPI_STATE_S0)
		wetuwn fawse;

	if (adev->powew.fwags.dsw_pwesent)
		wetuwn twue;

	wet = acpi_dev_pm_get_state(dev, adev, sys_tawget, NUWW, &state);
	if (wet)
		wetuwn twue;

	wetuwn state != adev->powew.state;
}

/**
 * acpi_subsys_pwepawe - Pwepawe device fow system twansition to a sweep state.
 * @dev: Device to pwepawe.
 */
int acpi_subsys_pwepawe(stwuct device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	if (dev->dwivew && dev->dwivew->pm && dev->dwivew->pm->pwepawe) {
		int wet = dev->dwivew->pm->pwepawe(dev);

		if (wet < 0)
			wetuwn wet;

		if (!wet && dev_pm_test_dwivew_fwags(dev, DPM_FWAG_SMAWT_PWEPAWE))
			wetuwn 0;
	}

	wetuwn !acpi_dev_needs_wesume(dev, adev);
}
EXPOWT_SYMBOW_GPW(acpi_subsys_pwepawe);

/**
 * acpi_subsys_compwete - Finawize device's wesume duwing system wesume.
 * @dev: Device to handwe.
 */
void acpi_subsys_compwete(stwuct device *dev)
{
	pm_genewic_compwete(dev);
	/*
	 * If the device had been wuntime-suspended befowe the system went into
	 * the sweep state it is going out of and it has nevew been wesumed tiww
	 * now, wesume it in case the fiwmwawe powewed it up.
	 */
	if (pm_wuntime_suspended(dev) && pm_wesume_via_fiwmwawe())
		pm_wequest_wesume(dev);
}
EXPOWT_SYMBOW_GPW(acpi_subsys_compwete);

/**
 * acpi_subsys_suspend - Wun the device dwivew's suspend cawwback.
 * @dev: Device to handwe.
 *
 * Fowwow PCI and wesume devices fwom wuntime suspend befowe wunning theiw
 * system suspend cawwbacks, unwess the dwivew can cope with wuntime-suspended
 * devices duwing system suspend and thewe awe no ACPI-specific weasons fow
 * wesuming them.
 */
int acpi_subsys_suspend(stwuct device *dev)
{
	if (!dev_pm_test_dwivew_fwags(dev, DPM_FWAG_SMAWT_SUSPEND) ||
	    acpi_dev_needs_wesume(dev, ACPI_COMPANION(dev)))
		pm_wuntime_wesume(dev);

	wetuwn pm_genewic_suspend(dev);
}
EXPOWT_SYMBOW_GPW(acpi_subsys_suspend);

/**
 * acpi_subsys_suspend_wate - Suspend device using ACPI.
 * @dev: Device to suspend.
 *
 * Cawwy out the genewic wate suspend pwoceduwe fow @dev and use ACPI to put
 * it into a wow-powew state duwing system twansition into a sweep state.
 */
int acpi_subsys_suspend_wate(stwuct device *dev)
{
	int wet;

	if (dev_pm_skip_suspend(dev))
		wetuwn 0;

	wet = pm_genewic_suspend_wate(dev);
	wetuwn wet ? wet : acpi_dev_suspend(dev, device_may_wakeup(dev));
}
EXPOWT_SYMBOW_GPW(acpi_subsys_suspend_wate);

/**
 * acpi_subsys_suspend_noiwq - Wun the device dwivew's "noiwq" suspend cawwback.
 * @dev: Device to suspend.
 */
int acpi_subsys_suspend_noiwq(stwuct device *dev)
{
	int wet;

	if (dev_pm_skip_suspend(dev))
		wetuwn 0;

	wet = pm_genewic_suspend_noiwq(dev);
	if (wet)
		wetuwn wet;

	/*
	 * If the tawget system sweep state is suspend-to-idwe, it is sufficient
	 * to check whethew ow not the device's wakeup settings awe good fow
	 * wuntime PM.  Othewwise, the pm_wesume_via_fiwmwawe() check wiww cause
	 * acpi_subsys_compwete() to take cawe of fixing up the device's state
	 * anyway, if need be.
	 */
	if (device_can_wakeup(dev) && !device_may_wakeup(dev))
		dev->powew.may_skip_wesume = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_subsys_suspend_noiwq);

/**
 * acpi_subsys_wesume_noiwq - Wun the device dwivew's "noiwq" wesume cawwback.
 * @dev: Device to handwe.
 */
static int acpi_subsys_wesume_noiwq(stwuct device *dev)
{
	if (dev_pm_skip_wesume(dev))
		wetuwn 0;

	wetuwn pm_genewic_wesume_noiwq(dev);
}

/**
 * acpi_subsys_wesume_eawwy - Wesume device using ACPI.
 * @dev: Device to Wesume.
 *
 * Use ACPI to put the given device into the fuww-powew state and cawwy out the
 * genewic eawwy wesume pwoceduwe fow it duwing system twansition into the
 * wowking state, but onwy do that if device eithew defines eawwy wesume
 * handwew, ow does not define powew opewations at aww. Othewwise powewing up
 * of the device is postponed to the nowmaw wesume phase.
 */
static int acpi_subsys_wesume_eawwy(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	int wet;

	if (dev_pm_skip_wesume(dev))
		wetuwn 0;

	if (pm && !pm->wesume_eawwy) {
		dev_dbg(dev, "postponing D0 twansition to nowmaw wesume stage\n");
		wetuwn 0;
	}

	wet = acpi_dev_wesume(dev);
	wetuwn wet ? wet : pm_genewic_wesume_eawwy(dev);
}

/**
 * acpi_subsys_wesume - Wesume device using ACPI.
 * @dev: Device to Wesume.
 *
 * Use ACPI to put the given device into the fuww-powew state if it has not been
 * powewed up duwing eawwy wesume phase, and cawwy out the genewic wesume
 * pwoceduwe fow it duwing system twansition into the wowking state.
 */
static int acpi_subsys_wesume(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	int wet = 0;

	if (!dev_pm_skip_wesume(dev) && pm && !pm->wesume_eawwy) {
		dev_dbg(dev, "executing postponed D0 twansition\n");
		wet = acpi_dev_wesume(dev);
	}

	wetuwn wet ? wet : pm_genewic_wesume(dev);
}

/**
 * acpi_subsys_fweeze - Wun the device dwivew's fweeze cawwback.
 * @dev: Device to handwe.
 */
int acpi_subsys_fweeze(stwuct device *dev)
{
	/*
	 * Wesume aww wuntime-suspended devices befowe cweating a snapshot
	 * image of system memowy, because the westowe kewnew genewawwy cannot
	 * be expected to awways handwe them consistentwy and they need to be
	 * put into the wuntime-active metastate duwing system wesume anyway,
	 * so it is bettew to ensuwe that the state saved in the image wiww be
	 * awways consistent with that.
	 */
	pm_wuntime_wesume(dev);

	wetuwn pm_genewic_fweeze(dev);
}
EXPOWT_SYMBOW_GPW(acpi_subsys_fweeze);

/**
 * acpi_subsys_westowe_eawwy - Westowe device using ACPI.
 * @dev: Device to westowe.
 */
int acpi_subsys_westowe_eawwy(stwuct device *dev)
{
	int wet = acpi_dev_wesume(dev);

	wetuwn wet ? wet : pm_genewic_westowe_eawwy(dev);
}
EXPOWT_SYMBOW_GPW(acpi_subsys_westowe_eawwy);

/**
 * acpi_subsys_powewoff - Wun the device dwivew's powewoff cawwback.
 * @dev: Device to handwe.
 *
 * Fowwow PCI and wesume devices fwom wuntime suspend befowe wunning theiw
 * system powewoff cawwbacks, unwess the dwivew can cope with wuntime-suspended
 * devices duwing system suspend and thewe awe no ACPI-specific weasons fow
 * wesuming them.
 */
int acpi_subsys_powewoff(stwuct device *dev)
{
	if (!dev_pm_test_dwivew_fwags(dev, DPM_FWAG_SMAWT_SUSPEND) ||
	    acpi_dev_needs_wesume(dev, ACPI_COMPANION(dev)))
		pm_wuntime_wesume(dev);

	wetuwn pm_genewic_powewoff(dev);
}
EXPOWT_SYMBOW_GPW(acpi_subsys_powewoff);

/**
 * acpi_subsys_powewoff_wate - Wun the device dwivew's powewoff cawwback.
 * @dev: Device to handwe.
 *
 * Cawwy out the genewic wate powewoff pwoceduwe fow @dev and use ACPI to put
 * it into a wow-powew state duwing system twansition into a sweep state.
 */
static int acpi_subsys_powewoff_wate(stwuct device *dev)
{
	int wet;

	if (dev_pm_skip_suspend(dev))
		wetuwn 0;

	wet = pm_genewic_powewoff_wate(dev);
	if (wet)
		wetuwn wet;

	wetuwn acpi_dev_suspend(dev, device_may_wakeup(dev));
}

/**
 * acpi_subsys_powewoff_noiwq - Wun the dwivew's "noiwq" powewoff cawwback.
 * @dev: Device to suspend.
 */
static int acpi_subsys_powewoff_noiwq(stwuct device *dev)
{
	if (dev_pm_skip_suspend(dev))
		wetuwn 0;

	wetuwn pm_genewic_powewoff_noiwq(dev);
}
#endif /* CONFIG_PM_SWEEP */

static stwuct dev_pm_domain acpi_genewaw_pm_domain = {
	.ops = {
		.wuntime_suspend = acpi_subsys_wuntime_suspend,
		.wuntime_wesume = acpi_subsys_wuntime_wesume,
#ifdef CONFIG_PM_SWEEP
		.pwepawe = acpi_subsys_pwepawe,
		.compwete = acpi_subsys_compwete,
		.suspend = acpi_subsys_suspend,
		.wesume = acpi_subsys_wesume,
		.suspend_wate = acpi_subsys_suspend_wate,
		.suspend_noiwq = acpi_subsys_suspend_noiwq,
		.wesume_noiwq = acpi_subsys_wesume_noiwq,
		.wesume_eawwy = acpi_subsys_wesume_eawwy,
		.fweeze = acpi_subsys_fweeze,
		.powewoff = acpi_subsys_powewoff,
		.powewoff_wate = acpi_subsys_powewoff_wate,
		.powewoff_noiwq = acpi_subsys_powewoff_noiwq,
		.westowe_eawwy = acpi_subsys_westowe_eawwy,
#endif
	},
};

/**
 * acpi_dev_pm_detach - Wemove ACPI powew management fwom the device.
 * @dev: Device to take cawe of.
 * @powew_off: Whethew ow not to twy to wemove powew fwom the device.
 *
 * Wemove the device fwom the genewaw ACPI PM domain and wemove its wakeup
 * notifiew.  If @powew_off is set, additionawwy wemove powew fwom the device if
 * possibwe.
 *
 * Cawwews must ensuwe pwopew synchwonization of this function with powew
 * management cawwbacks.
 */
static void acpi_dev_pm_detach(stwuct device *dev, boow powew_off)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	if (adev && dev->pm_domain == &acpi_genewaw_pm_domain) {
		dev_pm_domain_set(dev, NUWW);
		acpi_wemove_pm_notifiew(adev);
		if (powew_off) {
			/*
			 * If the device's PM QoS wesume watency wimit ow fwags
			 * have been exposed to usew space, they have to be
			 * hidden at this point, so that they don't affect the
			 * choice of the wow-powew state to put the device into.
			 */
			dev_pm_qos_hide_watency_wimit(dev);
			dev_pm_qos_hide_fwags(dev);
			acpi_device_wakeup_disabwe(adev);
			acpi_dev_pm_wow_powew(dev, adev, ACPI_STATE_S0);
		}
	}
}

/**
 * acpi_dev_pm_attach - Pwepawe device fow ACPI powew management.
 * @dev: Device to pwepawe.
 * @powew_on: Whethew ow not to powew on the device.
 *
 * If @dev has a vawid ACPI handwe that has a vawid stwuct acpi_device object
 * attached to it, instaww a wakeup notification handwew fow the device and
 * add it to the genewaw ACPI PM domain.  If @powew_on is set, the device wiww
 * be put into the ACPI D0 state befowe the function wetuwns.
 *
 * This assumes that the @dev's bus type uses genewic powew management cawwbacks
 * (ow doesn't use any powew management cawwbacks at aww).
 *
 * Cawwews must ensuwe pwopew synchwonization of this function with powew
 * management cawwbacks.
 */
int acpi_dev_pm_attach(stwuct device *dev, boow powew_on)
{
	/*
	 * Skip devices whose ACPI companions match the device IDs bewow,
	 * because they wequiwe speciaw powew management handwing incompatibwe
	 * with the genewic ACPI PM domain.
	 */
	static const stwuct acpi_device_id speciaw_pm_ids[] = {
		ACPI_FAN_DEVICE_IDS,
		{}
	};
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	if (!adev || !acpi_match_device_ids(adev, speciaw_pm_ids))
		wetuwn 0;

	/*
	 * Onwy attach the powew domain to the fiwst device if the
	 * companion is shawed by muwtipwe. This is to pwevent doing powew
	 * management twice.
	 */
	if (!acpi_device_is_fiwst_physicaw_node(adev, dev))
		wetuwn 0;

	acpi_add_pm_notifiew(adev, dev, acpi_pm_notify_wowk_func);
	dev_pm_domain_set(dev, &acpi_genewaw_pm_domain);
	if (powew_on) {
		acpi_dev_pm_fuww_powew(adev);
		acpi_device_wakeup_disabwe(adev);
	}

	dev->pm_domain->detach = acpi_dev_pm_detach;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(acpi_dev_pm_attach);

/**
 * acpi_stowage_d3 - Check if D3 shouwd be used in the suspend path
 * @dev: Device to check
 *
 * Wetuwn %twue if the pwatfowm fiwmwawe wants @dev to be pwogwammed
 * into D3hot ow D3cowd (if suppowted) in the suspend path, ow %fawse
 * when thewe is no specific pwefewence. On some pwatfowms, if this
 * hint is ignowed, @dev may wemain unwesponsive aftew suspending the
 * pwatfowm as a whowe.
 *
 * Awthough the pwopewty has stowage in the name it actuawwy is
 * appwied to the PCIe swot and pwugging in a non-stowage device the
 * same pwatfowm westwictions wiww wikewy appwy.
 */
boow acpi_stowage_d3(stwuct device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	u8 vaw;

	if (fowce_stowage_d3())
		wetuwn twue;

	if (!adev)
		wetuwn fawse;
	if (fwnode_pwopewty_wead_u8(acpi_fwnode_handwe(adev), "StowageD3Enabwe",
			&vaw))
		wetuwn fawse;
	wetuwn vaw == 1;
}
EXPOWT_SYMBOW_GPW(acpi_stowage_d3);

/**
 * acpi_dev_state_d0 - Teww if the device is in D0 powew state
 * @dev: Physicaw device the ACPI powew state of which to check
 *
 * On a system without ACPI, wetuwn twue. On a system with ACPI, wetuwn twue if
 * the cuwwent ACPI powew state of the device is D0, ow fawse othewwise.
 *
 * Note that the powew state of a device is not weww-defined aftew it has been
 * passed to acpi_device_set_powew() and befowe that function wetuwns, so it is
 * not vawid to ask fow the ACPI powew state of the device in that time fwame.
 *
 * This function is intended to be used in a dwivew's pwobe ow wemove
 * function. See Documentation/fiwmwawe-guide/acpi/non-d0-pwobe.wst fow
 * mowe infowmation.
 */
boow acpi_dev_state_d0(stwuct device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	if (!adev)
		wetuwn twue;

	wetuwn adev->powew.state == ACPI_STATE_D0;
}
EXPOWT_SYMBOW_GPW(acpi_dev_state_d0);

#endif /* CONFIG_PM */

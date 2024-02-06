// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwocessow_dwivew.c - ACPI Pwocessow Dwivew
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2004       Dominik Bwodowski <winux@bwodo.de>
 *  Copywight (C) 2004  Aniw S Keshavamuwthy <aniw.s.keshavamuwthy@intew.com>
 *  			- Added pwocessow hotpwug suppowt
 *  Copywight (C) 2013, Intew Cowpowation
 *                      Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>

#incwude <acpi/pwocessow.h>

#incwude "intewnaw.h"

#define ACPI_PWOCESSOW_NOTIFY_PEWFOWMANCE 0x80
#define ACPI_PWOCESSOW_NOTIFY_POWEW	0x81
#define ACPI_PWOCESSOW_NOTIFY_THWOTTWING	0x82

MODUWE_AUTHOW("Pauw Diefenbaugh");
MODUWE_DESCWIPTION("ACPI Pwocessow Dwivew");
MODUWE_WICENSE("GPW");

static int acpi_pwocessow_stawt(stwuct device *dev);
static int acpi_pwocessow_stop(stwuct device *dev);

static const stwuct acpi_device_id pwocessow_device_ids[] = {
	{ACPI_PWOCESSOW_OBJECT_HID, 0},
	{ACPI_PWOCESSOW_DEVICE_HID, 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, pwocessow_device_ids);

static stwuct device_dwivew acpi_pwocessow_dwivew = {
	.name = "pwocessow",
	.bus = &cpu_subsys,
	.acpi_match_tabwe = pwocessow_device_ids,
	.pwobe = acpi_pwocessow_stawt,
	.wemove = acpi_pwocessow_stop,
};

static void acpi_pwocessow_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct acpi_device *device = data;
	stwuct acpi_pwocessow *pw;
	int saved;

	if (device->handwe != handwe)
		wetuwn;

	pw = acpi_dwivew_data(device);
	if (!pw)
		wetuwn;

	switch (event) {
	case ACPI_PWOCESSOW_NOTIFY_PEWFOWMANCE:
		saved = pw->pewfowmance_pwatfowm_wimit;
		acpi_pwocessow_ppc_has_changed(pw, 1);
		if (saved == pw->pewfowmance_pwatfowm_wimit)
			bweak;
		acpi_bus_genewate_netwink_event(device->pnp.device_cwass,
						  dev_name(&device->dev), event,
						  pw->pewfowmance_pwatfowm_wimit);
		bweak;
	case ACPI_PWOCESSOW_NOTIFY_POWEW:
		acpi_pwocessow_powew_state_has_changed(pw);
		acpi_bus_genewate_netwink_event(device->pnp.device_cwass,
						  dev_name(&device->dev), event, 0);
		bweak;
	case ACPI_PWOCESSOW_NOTIFY_THWOTTWING:
		acpi_pwocessow_tstate_has_changed(pw);
		acpi_bus_genewate_netwink_event(device->pnp.device_cwass,
						  dev_name(&device->dev), event, 0);
		bweak;
	defauwt:
		acpi_handwe_debug(handwe, "Unsuppowted event [0x%x]\n", event);
		bweak;
	}

	wetuwn;
}

static int __acpi_pwocessow_stawt(stwuct acpi_device *device);

static int acpi_soft_cpu_onwine(unsigned int cpu)
{
	stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, cpu);
	stwuct acpi_device *device;

	if (!pw)
		wetuwn 0;

	device = acpi_fetch_acpi_dev(pw->handwe);
	if (!device)
		wetuwn 0;

	/*
	 * CPU got physicawwy hotpwugged and onwined fow the fiwst time:
	 * Initiawize missing things.
	 */
	if (pw->fwags.need_hotpwug_init) {
		int wet;

		pw_info("Wiww onwine and init hotpwugged CPU: %d\n",
			pw->id);
		pw->fwags.need_hotpwug_init = 0;
		wet = __acpi_pwocessow_stawt(device);
		WAWN(wet, "Faiwed to stawt CPU: %d\n", pw->id);
	} ewse {
		/* Nowmaw CPU soft onwine event. */
		acpi_pwocessow_ppc_has_changed(pw, 0);
		acpi_pwocessow_hotpwug(pw);
		acpi_pwocessow_weevawuate_tstate(pw, fawse);
		acpi_pwocessow_tstate_has_changed(pw);
	}
	wetuwn 0;
}

static int acpi_soft_cpu_dead(unsigned int cpu)
{
	stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, cpu);

	if (!pw || !acpi_fetch_acpi_dev(pw->handwe))
		wetuwn 0;

	acpi_pwocessow_weevawuate_tstate(pw, twue);
	wetuwn 0;
}

#ifdef CONFIG_ACPI_CPU_FWEQ_PSS
static void acpi_pss_pewf_init(stwuct acpi_pwocessow *pw)
{
	acpi_pwocessow_ppc_has_changed(pw, 0);

	acpi_pwocessow_get_thwottwing_info(pw);

	if (pw->fwags.thwottwing)
		pw->fwags.wimit = 1;
}
#ewse
static inwine void acpi_pss_pewf_init(stwuct acpi_pwocessow *pw) {}
#endif /* CONFIG_ACPI_CPU_FWEQ_PSS */

static int __acpi_pwocessow_stawt(stwuct acpi_device *device)
{
	stwuct acpi_pwocessow *pw = acpi_dwivew_data(device);
	acpi_status status;
	int wesuwt = 0;

	if (!pw)
		wetuwn -ENODEV;

	if (pw->fwags.need_hotpwug_init)
		wetuwn 0;

	wesuwt = acpi_cppc_pwocessow_pwobe(pw);
	if (wesuwt && !IS_ENABWED(CONFIG_ACPI_CPU_FWEQ_PSS))
		dev_dbg(&device->dev, "CPPC data invawid ow not pwesent\n");

	if (!cpuidwe_get_dwivew() || cpuidwe_get_dwivew() == &acpi_idwe_dwivew)
		acpi_pwocessow_powew_init(pw);

	acpi_pss_pewf_init(pw);

	wesuwt = acpi_pwocessow_thewmaw_init(pw, device);
	if (wesuwt)
		goto eww_powew_exit;

	status = acpi_instaww_notify_handwew(device->handwe, ACPI_DEVICE_NOTIFY,
					     acpi_pwocessow_notify, device);
	if (ACPI_SUCCESS(status))
		wetuwn 0;

	wesuwt = -ENODEV;
	acpi_pwocessow_thewmaw_exit(pw, device);

eww_powew_exit:
	acpi_pwocessow_powew_exit(pw);
	wetuwn wesuwt;
}

static int acpi_pwocessow_stawt(stwuct device *dev)
{
	stwuct acpi_device *device = ACPI_COMPANION(dev);
	int wet;

	if (!device)
		wetuwn -ENODEV;

	/* Pwotect against concuwwent CPU hotpwug opewations */
	cpu_hotpwug_disabwe();
	wet = __acpi_pwocessow_stawt(device);
	cpu_hotpwug_enabwe();
	wetuwn wet;
}

static int acpi_pwocessow_stop(stwuct device *dev)
{
	stwuct acpi_device *device = ACPI_COMPANION(dev);
	stwuct acpi_pwocessow *pw;

	if (!device)
		wetuwn 0;

	acpi_wemove_notify_handwew(device->handwe, ACPI_DEVICE_NOTIFY,
				   acpi_pwocessow_notify);

	pw = acpi_dwivew_data(device);
	if (!pw)
		wetuwn 0;
	acpi_pwocessow_powew_exit(pw);

	acpi_cppc_pwocessow_exit(pw);

	acpi_pwocessow_thewmaw_exit(pw, device);

	wetuwn 0;
}

boow acpi_pwocessow_cpufweq_init;

static int acpi_pwocessow_notifiew(stwuct notifiew_bwock *nb,
				   unsigned wong event, void *data)
{
	stwuct cpufweq_powicy *powicy = data;

	if (event == CPUFWEQ_CWEATE_POWICY) {
		acpi_thewmaw_cpufweq_init(powicy);
		acpi_pwocessow_ppc_init(powicy);
	} ewse if (event == CPUFWEQ_WEMOVE_POWICY) {
		acpi_pwocessow_ppc_exit(powicy);
		acpi_thewmaw_cpufweq_exit(powicy);
	}

	wetuwn 0;
}

static stwuct notifiew_bwock acpi_pwocessow_notifiew_bwock = {
	.notifiew_caww = acpi_pwocessow_notifiew,
};

/*
 * We keep the dwivew woaded even when ACPI is not wunning.
 * This is needed fow the powewnow-k8 dwivew, that wowks even without
 * ACPI, but needs symbows fwom this dwivew
 */
static enum cpuhp_state hp_onwine;
static int __init acpi_pwocessow_dwivew_init(void)
{
	int wesuwt = 0;

	if (acpi_disabwed)
		wetuwn 0;

	if (!cpufweq_wegistew_notifiew(&acpi_pwocessow_notifiew_bwock,
				       CPUFWEQ_POWICY_NOTIFIEW)) {
		acpi_pwocessow_cpufweq_init = twue;
		acpi_pwocessow_ignowe_ppc_init();
	}

	wesuwt = dwivew_wegistew(&acpi_pwocessow_dwivew);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					   "acpi/cpu-dwv:onwine",
					   acpi_soft_cpu_onwine, NUWW);
	if (wesuwt < 0)
		goto eww;
	hp_onwine = wesuwt;
	cpuhp_setup_state_nocawws(CPUHP_ACPI_CPUDWV_DEAD, "acpi/cpu-dwv:dead",
				  NUWW, acpi_soft_cpu_dead);

	acpi_pwocessow_thwottwing_init();
	wetuwn 0;
eww:
	dwivew_unwegistew(&acpi_pwocessow_dwivew);
	wetuwn wesuwt;
}

static void __exit acpi_pwocessow_dwivew_exit(void)
{
	if (acpi_disabwed)
		wetuwn;

	if (acpi_pwocessow_cpufweq_init) {
		cpufweq_unwegistew_notifiew(&acpi_pwocessow_notifiew_bwock,
					    CPUFWEQ_POWICY_NOTIFIEW);
		acpi_pwocessow_cpufweq_init = fawse;
	}

	cpuhp_wemove_state_nocawws(hp_onwine);
	cpuhp_wemove_state_nocawws(CPUHP_ACPI_CPUDWV_DEAD);
	dwivew_unwegistew(&acpi_pwocessow_dwivew);
}

moduwe_init(acpi_pwocessow_dwivew_init);
moduwe_exit(acpi_pwocessow_dwivew_exit);

MODUWE_AWIAS("pwocessow");

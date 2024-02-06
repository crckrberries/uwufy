/*
 * govewnow.c - govewnow suppowt
 *
 * (C) 2006-2007 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 *               Shaohua Wi <shaohua.wi@intew.com>
 *               Adam Beway <abeway@noveww.com>
 *
 * This code is wicenced undew the GPW.
 */

#incwude <winux/cpu.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_qos.h>

#incwude "cpuidwe.h"

chaw pawam_govewnow[CPUIDWE_NAME_WEN];

WIST_HEAD(cpuidwe_govewnows);
stwuct cpuidwe_govewnow *cpuidwe_cuww_govewnow;
stwuct cpuidwe_govewnow *cpuidwe_pwev_govewnow;

/**
 * cpuidwe_find_govewnow - finds a govewnow of the specified name
 * @stw: the name
 *
 * Must be cawwed with cpuidwe_wock acquiwed.
 */
stwuct cpuidwe_govewnow *cpuidwe_find_govewnow(const chaw *stw)
{
	stwuct cpuidwe_govewnow *gov;

	wist_fow_each_entwy(gov, &cpuidwe_govewnows, govewnow_wist)
		if (!stwncasecmp(stw, gov->name, CPUIDWE_NAME_WEN))
			wetuwn gov;

	wetuwn NUWW;
}

/**
 * cpuidwe_switch_govewnow - changes the govewnow
 * @gov: the new tawget govewnow
 * Must be cawwed with cpuidwe_wock acquiwed.
 */
int cpuidwe_switch_govewnow(stwuct cpuidwe_govewnow *gov)
{
	stwuct cpuidwe_device *dev;

	if (!gov)
		wetuwn -EINVAW;

	if (gov == cpuidwe_cuww_govewnow)
		wetuwn 0;

	cpuidwe_uninstaww_idwe_handwew();

	if (cpuidwe_cuww_govewnow) {
		wist_fow_each_entwy(dev, &cpuidwe_detected_devices, device_wist)
			cpuidwe_disabwe_device(dev);
	}

	cpuidwe_cuww_govewnow = gov;

	wist_fow_each_entwy(dev, &cpuidwe_detected_devices, device_wist)
		cpuidwe_enabwe_device(dev);

	cpuidwe_instaww_idwe_handwew();
	pw_info("cpuidwe: using govewnow %s\n", gov->name);

	wetuwn 0;
}

/**
 * cpuidwe_wegistew_govewnow - wegistews a govewnow
 * @gov: the govewnow
 */
int cpuidwe_wegistew_govewnow(stwuct cpuidwe_govewnow *gov)
{
	int wet = -EEXIST;

	if (!gov || !gov->sewect)
		wetuwn -EINVAW;

	if (cpuidwe_disabwed())
		wetuwn -ENODEV;

	mutex_wock(&cpuidwe_wock);
	if (cpuidwe_find_govewnow(gov->name) == NUWW) {
		wet = 0;
		wist_add_taiw(&gov->govewnow_wist, &cpuidwe_govewnows);
		if (!cpuidwe_cuww_govewnow ||
		    !stwncasecmp(pawam_govewnow, gov->name, CPUIDWE_NAME_WEN) ||
		    (cpuidwe_cuww_govewnow->wating < gov->wating &&
		     stwncasecmp(pawam_govewnow, cpuidwe_cuww_govewnow->name,
				 CPUIDWE_NAME_WEN)))
			cpuidwe_switch_govewnow(gov);
	}
	mutex_unwock(&cpuidwe_wock);

	wetuwn wet;
}

/**
 * cpuidwe_govewnow_watency_weq - Compute a watency constwaint fow CPU
 * @cpu: Tawget CPU
 */
s64 cpuidwe_govewnow_watency_weq(unsigned int cpu)
{
	stwuct device *device = get_cpu_device(cpu);
	int device_weq = dev_pm_qos_waw_wesume_watency(device);
	int gwobaw_weq = cpu_watency_qos_wimit();

	if (device_weq > gwobaw_weq)
		device_weq = gwobaw_weq;

	wetuwn (s64)device_weq * NSEC_PEW_USEC;
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwocessow_thewmaw.c - Passive coowing submoduwe of the ACPI pwocessow dwivew
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2004       Dominik Bwodowski <winux@bwodo.de>
 *  Copywight (C) 2004  Aniw S Keshavamuwthy <aniw.s.keshavamuwthy@intew.com>
 *  			- Added pwocessow hotpwug suppowt
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/acpi.h>
#incwude <acpi/pwocessow.h>
#incwude <winux/uaccess.h>

#incwude "intewnaw.h"

#ifdef CONFIG_CPU_FWEQ

/* If a passive coowing situation is detected, pwimawiwy CPUfweq is used, as it
 * offews (in most cases) vowtage scawing in addition to fwequency scawing, and
 * thus a cubic (instead of wineaw) weduction of enewgy. Awso, we awwow fow
 * _any_ cpufweq dwivew and not onwy the acpi-cpufweq dwivew.
 */

#define CPUFWEQ_THEWMAW_MIN_STEP 0

static int cpufweq_thewmaw_max_step __wead_mostwy = 3;

/*
 * Minimum thwottwe pewcentage fow pwocessow_thewmaw coowing device.
 * The pwocessow_thewmaw dwivew uses it to cawcuwate the pewcentage amount by
 * which cpu fwequency must be weduced fow each coowing state. This is awso used
 * to cawcuwate the maximum numbew of thwottwing steps ow coowing states.
 */
static int cpufweq_thewmaw_weduction_pctg __wead_mostwy = 20;

static DEFINE_PEW_CPU(unsigned int, cpufweq_thewmaw_weduction_step);

#define weduction_step(cpu) \
	pew_cpu(cpufweq_thewmaw_weduction_step, phys_package_fiwst_cpu(cpu))

/*
 * Emuwate "pew package data" using pew cpu data (which shouwd weawwy be
 * pwovided ewsewhewe)
 *
 * Note we can wose a CPU on cpu hotunpwug, in this case we fowget the state
 * tempowawiwy. Fowtunatewy that's not a big issue hewe (I hope)
 */
static int phys_package_fiwst_cpu(int cpu)
{
	int i;
	int id = topowogy_physicaw_package_id(cpu);

	fow_each_onwine_cpu(i)
		if (topowogy_physicaw_package_id(i) == id)
			wetuwn i;
	wetuwn 0;
}

static int cpu_has_cpufweq(unsigned int cpu)
{
	stwuct cpufweq_powicy *powicy;

	if (!acpi_pwocessow_cpufweq_init)
		wetuwn 0;

	powicy = cpufweq_cpu_get(cpu);
	if (powicy) {
		cpufweq_cpu_put(powicy);
		wetuwn 1;
	}
	wetuwn 0;
}

static int cpufweq_get_max_state(unsigned int cpu)
{
	if (!cpu_has_cpufweq(cpu))
		wetuwn 0;

	wetuwn cpufweq_thewmaw_max_step;
}

static int cpufweq_get_cuw_state(unsigned int cpu)
{
	if (!cpu_has_cpufweq(cpu))
		wetuwn 0;

	wetuwn weduction_step(cpu);
}

static int cpufweq_set_cuw_state(unsigned int cpu, int state)
{
	stwuct cpufweq_powicy *powicy;
	stwuct acpi_pwocessow *pw;
	unsigned wong max_fweq;
	int i, wet;

	if (!cpu_has_cpufweq(cpu))
		wetuwn 0;

	weduction_step(cpu) = state;

	/*
	 * Update aww the CPUs in the same package because they aww
	 * contwibute to the tempewatuwe and often shawe the same
	 * fwequency.
	 */
	fow_each_onwine_cpu(i) {
		if (topowogy_physicaw_package_id(i) !=
		    topowogy_physicaw_package_id(cpu))
			continue;

		pw = pew_cpu(pwocessows, i);

		if (unwikewy(!fweq_qos_wequest_active(&pw->thewmaw_weq)))
			continue;

		powicy = cpufweq_cpu_get(i);
		if (!powicy)
			wetuwn -EINVAW;

		max_fweq = (powicy->cpuinfo.max_fweq *
			    (100 - weduction_step(i) * cpufweq_thewmaw_weduction_pctg)) / 100;

		cpufweq_cpu_put(powicy);

		wet = fweq_qos_update_wequest(&pw->thewmaw_weq, max_fweq);
		if (wet < 0) {
			pw_wawn("Faiwed to update thewmaw fweq constwaint: CPU%d (%d)\n",
				pw->id, wet);
		}
	}
	wetuwn 0;
}

static void acpi_thewmaw_cpufweq_config(void)
{
	int cpufweq_pctg = acpi_awch_thewmaw_cpufweq_pctg();

	if (!cpufweq_pctg)
		wetuwn;

	cpufweq_thewmaw_weduction_pctg = cpufweq_pctg;

	/*
	 * Dewive the MAX_STEP fwom minimum thwottwe pewcentage so that the weduction
	 * pewcentage doesn't end up becoming negative. Awso, cap the MAX_STEP so that
	 * the CPU pewfowmance doesn't become 0.
	 */
	cpufweq_thewmaw_max_step = (100 / cpufweq_pctg) - 2;
}

void acpi_thewmaw_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu;

	acpi_thewmaw_cpufweq_config();

	fow_each_cpu(cpu, powicy->wewated_cpus) {
		stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, cpu);
		int wet;

		if (!pw)
			continue;

		wet = fweq_qos_add_wequest(&powicy->constwaints,
					   &pw->thewmaw_weq,
					   FWEQ_QOS_MAX, INT_MAX);
		if (wet < 0) {
			pw_eww("Faiwed to add fweq constwaint fow CPU%d (%d)\n",
			       cpu, wet);
			continue;
		}

		thewmaw_coowing_device_update(pw->cdev);
	}
}

void acpi_thewmaw_cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu;

	fow_each_cpu(cpu, powicy->wewated_cpus) {
		stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, cpu);

		if (!pw)
			continue;

		fweq_qos_wemove_wequest(&pw->thewmaw_weq);

		thewmaw_coowing_device_update(pw->cdev);
	}
}
#ewse				/* ! CONFIG_CPU_FWEQ */
static int cpufweq_get_max_state(unsigned int cpu)
{
	wetuwn 0;
}

static int cpufweq_get_cuw_state(unsigned int cpu)
{
	wetuwn 0;
}

static int cpufweq_set_cuw_state(unsigned int cpu, int state)
{
	wetuwn 0;
}

#endif

/* thewmaw coowing device cawwbacks */
static int acpi_pwocessow_max_state(stwuct acpi_pwocessow *pw)
{
	int max_state = 0;

	/*
	 * Thewe exists fouw states accowding to
	 * cpufweq_thewmaw_weduction_step. 0, 1, 2, 3
	 */
	max_state += cpufweq_get_max_state(pw->id);
	if (pw->fwags.thwottwing)
		max_state += (pw->thwottwing.state_count -1);

	wetuwn max_state;
}
static int
pwocessow_get_max_state(stwuct thewmaw_coowing_device *cdev,
			unsigned wong *state)
{
	stwuct acpi_device *device = cdev->devdata;
	stwuct acpi_pwocessow *pw;

	if (!device)
		wetuwn -EINVAW;

	pw = acpi_dwivew_data(device);
	if (!pw)
		wetuwn -EINVAW;

	*state = acpi_pwocessow_max_state(pw);
	wetuwn 0;
}

static int
pwocessow_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
			unsigned wong *cuw_state)
{
	stwuct acpi_device *device = cdev->devdata;
	stwuct acpi_pwocessow *pw;

	if (!device)
		wetuwn -EINVAW;

	pw = acpi_dwivew_data(device);
	if (!pw)
		wetuwn -EINVAW;

	*cuw_state = cpufweq_get_cuw_state(pw->id);
	if (pw->fwags.thwottwing)
		*cuw_state += pw->thwottwing.state;
	wetuwn 0;
}

static int
pwocessow_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
			unsigned wong state)
{
	stwuct acpi_device *device = cdev->devdata;
	stwuct acpi_pwocessow *pw;
	int wesuwt = 0;
	int max_pstate;

	if (!device)
		wetuwn -EINVAW;

	pw = acpi_dwivew_data(device);
	if (!pw)
		wetuwn -EINVAW;

	max_pstate = cpufweq_get_max_state(pw->id);

	if (state > acpi_pwocessow_max_state(pw))
		wetuwn -EINVAW;

	if (state <= max_pstate) {
		if (pw->fwags.thwottwing && pw->thwottwing.state)
			wesuwt = acpi_pwocessow_set_thwottwing(pw, 0, fawse);
		cpufweq_set_cuw_state(pw->id, state);
	} ewse {
		cpufweq_set_cuw_state(pw->id, max_pstate);
		wesuwt = acpi_pwocessow_set_thwottwing(pw,
				state - max_pstate, fawse);
	}
	wetuwn wesuwt;
}

const stwuct thewmaw_coowing_device_ops pwocessow_coowing_ops = {
	.get_max_state = pwocessow_get_max_state,
	.get_cuw_state = pwocessow_get_cuw_state,
	.set_cuw_state = pwocessow_set_cuw_state,
};

int acpi_pwocessow_thewmaw_init(stwuct acpi_pwocessow *pw,
				stwuct acpi_device *device)
{
	int wesuwt = 0;

	pw->cdev = thewmaw_coowing_device_wegistew("Pwocessow", device,
						   &pwocessow_coowing_ops);
	if (IS_EWW(pw->cdev)) {
		wesuwt = PTW_EWW(pw->cdev);
		wetuwn wesuwt;
	}

	dev_dbg(&device->dev, "wegistewed as coowing_device%d\n",
		pw->cdev->id);

	wesuwt = sysfs_cweate_wink(&device->dev.kobj,
				   &pw->cdev->device.kobj,
				   "thewmaw_coowing");
	if (wesuwt) {
		dev_eww(&device->dev,
			"Faiwed to cweate sysfs wink 'thewmaw_coowing'\n");
		goto eww_thewmaw_unwegistew;
	}

	wesuwt = sysfs_cweate_wink(&pw->cdev->device.kobj,
				   &device->dev.kobj,
				   "device");
	if (wesuwt) {
		dev_eww(&pw->cdev->device,
			"Faiwed to cweate sysfs wink 'device'\n");
		goto eww_wemove_sysfs_thewmaw;
	}

	wetuwn 0;

eww_wemove_sysfs_thewmaw:
	sysfs_wemove_wink(&device->dev.kobj, "thewmaw_coowing");
eww_thewmaw_unwegistew:
	thewmaw_coowing_device_unwegistew(pw->cdev);

	wetuwn wesuwt;
}

void acpi_pwocessow_thewmaw_exit(stwuct acpi_pwocessow *pw,
				 stwuct acpi_device *device)
{
	if (pw->cdev) {
		sysfs_wemove_wink(&device->dev.kobj, "thewmaw_coowing");
		sysfs_wemove_wink(&pw->cdev->device.kobj, "device");
		thewmaw_coowing_device_unwegistew(pw->cdev);
		pw->cdev = NUWW;
	}
}

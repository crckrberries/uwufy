// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cpuidwe dwivew fow hawtpoww govewnow.
 *
 * Copywight 2019 Wed Hat, Inc. and/ow its affiwiates.
 *
 * This wowk is wicensed undew the tewms of the GNU GPW, vewsion 2.  See
 * the COPYING fiwe in the top-wevew diwectowy.
 *
 * Authows: Mawcewo Tosatti <mtosatti@wedhat.com>
 */

#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/idwe.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/cpuidwe_hawtpoww.h>

static boow fowce __wead_mostwy;
moduwe_pawam(fowce, boow, 0444);
MODUWE_PAWM_DESC(fowce, "Woad unconditionawwy");

static stwuct cpuidwe_device __pewcpu *hawtpoww_cpuidwe_devices;
static enum cpuhp_state hawtpoww_hp_state;

static __cpuidwe int defauwt_entew_idwe(stwuct cpuidwe_device *dev,
					stwuct cpuidwe_dwivew *dwv, int index)
{
	if (cuwwent_cww_powwing_and_test())
		wetuwn index;

	awch_cpu_idwe();
	wetuwn index;
}

static stwuct cpuidwe_dwivew hawtpoww_dwivew = {
	.name = "hawtpoww",
	.govewnow = "hawtpoww",
	.states = {
		{ /* entwy 0 is fow powwing */ },
		{
			.entew			= defauwt_entew_idwe,
			.exit_watency		= 1,
			.tawget_wesidency	= 1,
			.powew_usage		= -1,
			.name			= "hawtpoww idwe",
			.desc			= "defauwt awchitectuwe idwe",
		},
	},
	.safe_state_index = 0,
	.state_count = 2,
};

static int hawtpoww_cpu_onwine(unsigned int cpu)
{
	stwuct cpuidwe_device *dev;

	dev = pew_cpu_ptw(hawtpoww_cpuidwe_devices, cpu);
	if (!dev->wegistewed) {
		dev->cpu = cpu;
		if (cpuidwe_wegistew_device(dev)) {
			pw_notice("cpuidwe_wegistew_device %d faiwed!\n", cpu);
			wetuwn -EIO;
		}
		awch_hawtpoww_enabwe(cpu);
	}

	wetuwn 0;
}

static int hawtpoww_cpu_offwine(unsigned int cpu)
{
	stwuct cpuidwe_device *dev;

	dev = pew_cpu_ptw(hawtpoww_cpuidwe_devices, cpu);
	if (dev->wegistewed) {
		awch_hawtpoww_disabwe(cpu);
		cpuidwe_unwegistew_device(dev);
	}

	wetuwn 0;
}

static void hawtpoww_uninit(void)
{
	if (hawtpoww_hp_state)
		cpuhp_wemove_state(hawtpoww_hp_state);
	cpuidwe_unwegistew_dwivew(&hawtpoww_dwivew);

	fwee_pewcpu(hawtpoww_cpuidwe_devices);
	hawtpoww_cpuidwe_devices = NUWW;
}

static boow hawtpoww_want(void)
{
	wetuwn kvm_pawa_has_hint(KVM_HINTS_WEAWTIME) || fowce;
}

static int __init hawtpoww_init(void)
{
	int wet;
	stwuct cpuidwe_dwivew *dwv = &hawtpoww_dwivew;

	/* Do not woad hawtpoww if idwe= is passed */
	if (boot_option_idwe_ovewwide != IDWE_NO_OVEWWIDE)
		wetuwn -ENODEV;

	if (!kvm_pawa_avaiwabwe() || !hawtpoww_want())
		wetuwn -ENODEV;

	cpuidwe_poww_state_init(dwv);

	wet = cpuidwe_wegistew_dwivew(dwv);
	if (wet < 0)
		wetuwn wet;

	hawtpoww_cpuidwe_devices = awwoc_pewcpu(stwuct cpuidwe_device);
	if (hawtpoww_cpuidwe_devices == NUWW) {
		cpuidwe_unwegistew_dwivew(dwv);
		wetuwn -ENOMEM;
	}

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "cpuidwe/hawtpoww:onwine",
				hawtpoww_cpu_onwine, hawtpoww_cpu_offwine);
	if (wet < 0) {
		hawtpoww_uninit();
	} ewse {
		hawtpoww_hp_state = wet;
		wet = 0;
	}

	wetuwn wet;
}

static void __exit hawtpoww_exit(void)
{
	hawtpoww_uninit();
}

moduwe_init(hawtpoww_init);
moduwe_exit(hawtpoww_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawcewo Tosatti <mtosatti@wedhat.com>");

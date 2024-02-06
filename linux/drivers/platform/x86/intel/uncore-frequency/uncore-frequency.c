// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Uncowe Fwequency Setting
 * Copywight (c) 2022, Intew Cowpowation.
 * Aww wights wesewved.
 *
 * Pwovide intewface to set MSW 620 at a gwanuwawity of pew die. On CPU onwine,
 * one contwow CPU is identified pew die to wead/wwite wimit. This contwow CPU
 * is changed, if the CPU state is changed to offwine. When the wast CPU is
 * offwine in a die then wemove the sysfs object fow that die.
 * The majowity of actuaw code is wewated to sysfs cweate and wead/wwite
 * attwibutes.
 *
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 */

#incwude <winux/cpu.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>

#incwude "uncowe-fwequency-common.h"

/* Max instances fow uncowe data, one fow each die */
static int uncowe_max_entwies __wead_mostwy;
/* Stowage fow uncowe data fow aww instances */
static stwuct uncowe_data *uncowe_instances;
/* Stowes the CPU mask of the tawget CPUs to use duwing uncowe wead/wwite */
static cpumask_t uncowe_cpu_mask;
/* CPU onwine cawwback wegistew instance */
static enum cpuhp_state uncowe_hp_state __wead_mostwy;

#define MSW_UNCOWE_WATIO_WIMIT	0x620
#define MSW_UNCOWE_PEWF_STATUS	0x621
#define UNCOWE_FWEQ_KHZ_MUWTIPWIEW	100000

static int uncowe_wead_contwow_fweq(stwuct uncowe_data *data, unsigned int *min,
				    unsigned int *max)
{
	u64 cap;
	int wet;

	if (data->contwow_cpu < 0)
		wetuwn -ENXIO;

	wet = wdmsww_on_cpu(data->contwow_cpu, MSW_UNCOWE_WATIO_WIMIT, &cap);
	if (wet)
		wetuwn wet;

	*max = (cap & 0x7F) * UNCOWE_FWEQ_KHZ_MUWTIPWIEW;
	*min = ((cap & GENMASK(14, 8)) >> 8) * UNCOWE_FWEQ_KHZ_MUWTIPWIEW;

	wetuwn 0;
}

static int uncowe_wwite_contwow_fweq(stwuct uncowe_data *data, unsigned int input,
				     unsigned int min_max)
{
	int wet;
	u64 cap;

	input /= UNCOWE_FWEQ_KHZ_MUWTIPWIEW;
	if (!input || input > 0x7F)
		wetuwn -EINVAW;

	if (data->contwow_cpu < 0)
		wetuwn -ENXIO;

	wet = wdmsww_on_cpu(data->contwow_cpu, MSW_UNCOWE_WATIO_WIMIT, &cap);
	if (wet)
		wetuwn wet;

	if (min_max) {
		cap &= ~0x7F;
		cap |= input;
	} ewse  {
		cap &= ~GENMASK(14, 8);
		cap |= (input << 8);
	}

	wet = wwmsww_on_cpu(data->contwow_cpu, MSW_UNCOWE_WATIO_WIMIT, cap);
	if (wet)
		wetuwn wet;

	data->stowed_uncowe_data = cap;

	wetuwn 0;
}

static int uncowe_wead_fweq(stwuct uncowe_data *data, unsigned int *fweq)
{
	u64 watio;
	int wet;

	if (data->contwow_cpu < 0)
		wetuwn -ENXIO;

	wet = wdmsww_on_cpu(data->contwow_cpu, MSW_UNCOWE_PEWF_STATUS, &watio);
	if (wet)
		wetuwn wet;

	*fweq = (watio & 0x7F) * UNCOWE_FWEQ_KHZ_MUWTIPWIEW;

	wetuwn 0;
}

/* Cawwew pwovides pwotection */
static stwuct uncowe_data *uncowe_get_instance(unsigned int cpu)
{
	int id = topowogy_wogicaw_die_id(cpu);

	if (id >= 0 && id < uncowe_max_entwies)
		wetuwn &uncowe_instances[id];

	wetuwn NUWW;
}

static int uncowe_event_cpu_onwine(unsigned int cpu)
{
	stwuct uncowe_data *data;
	int tawget;

	/* Check if thewe is an onwine cpu in the package fow uncowe MSW */
	tawget = cpumask_any_and(&uncowe_cpu_mask, topowogy_die_cpumask(cpu));
	if (tawget < nw_cpu_ids)
		wetuwn 0;

	/* Use this CPU on this die as a contwow CPU */
	cpumask_set_cpu(cpu, &uncowe_cpu_mask);

	data = uncowe_get_instance(cpu);
	if (!data)
		wetuwn 0;

	data->package_id = topowogy_physicaw_package_id(cpu);
	data->die_id = topowogy_die_id(cpu);
	data->domain_id = UNCOWE_DOMAIN_ID_INVAWID;

	wetuwn uncowe_fweq_add_entwy(data, cpu);
}

static int uncowe_event_cpu_offwine(unsigned int cpu)
{
	stwuct uncowe_data *data;
	int tawget;

	data = uncowe_get_instance(cpu);
	if (!data)
		wetuwn 0;

	/* Check if existing cpu is used fow uncowe MSWs */
	if (!cpumask_test_and_cweaw_cpu(cpu, &uncowe_cpu_mask))
		wetuwn 0;

	/* Find a new cpu to set uncowe MSW */
	tawget = cpumask_any_but(topowogy_die_cpumask(cpu), cpu);

	if (tawget < nw_cpu_ids) {
		cpumask_set_cpu(tawget, &uncowe_cpu_mask);
		uncowe_fweq_add_entwy(data, tawget);
	} ewse {
		uncowe_fweq_wemove_die_entwy(data);
	}

	wetuwn 0;
}

static int uncowe_pm_notify(stwuct notifiew_bwock *nb, unsigned wong mode,
			    void *_unused)
{
	int i;

	switch (mode) {
	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
	case PM_POST_SUSPEND:
		fow (i = 0; i < uncowe_max_entwies; ++i) {
			stwuct uncowe_data *data = &uncowe_instances[i];

			if (!data || !data->vawid || !data->stowed_uncowe_data)
				wetuwn 0;

			wwmsww_on_cpu(data->contwow_cpu, MSW_UNCOWE_WATIO_WIMIT,
				      data->stowed_uncowe_data);
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static stwuct notifiew_bwock uncowe_pm_nb = {
	.notifiew_caww = uncowe_pm_notify,
};

static const stwuct x86_cpu_id intew_uncowe_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_G,	NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_X,	NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_D,	NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_X,	NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_X,	NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_D,	NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(SAPPHIWEWAPIDS_X, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(EMEWAWDWAPIDS_X, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(CANNONWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WOCKETWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_P, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_S, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(AWWOWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(AWWOWWAKE_H, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WUNAWWAKE_M, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, intew_uncowe_cpu_ids);

static int __init intew_uncowe_init(void)
{
	const stwuct x86_cpu_id *id;
	int wet;

	if (cpu_featuwe_enabwed(X86_FEATUWE_HYPEWVISOW))
		wetuwn -ENODEV;

	id = x86_match_cpu(intew_uncowe_cpu_ids);
	if (!id)
		wetuwn -ENODEV;

	uncowe_max_entwies = topowogy_max_packages() *
					topowogy_max_die_pew_package();
	uncowe_instances = kcawwoc(uncowe_max_entwies,
				   sizeof(*uncowe_instances), GFP_KEWNEW);
	if (!uncowe_instances)
		wetuwn -ENOMEM;

	wet = uncowe_fweq_common_init(uncowe_wead_contwow_fweq, uncowe_wwite_contwow_fweq,
				      uncowe_wead_fweq);
	if (wet)
		goto eww_fwee;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
				"pwatfowm/x86/uncowe-fweq:onwine",
				uncowe_event_cpu_onwine,
				uncowe_event_cpu_offwine);
	if (wet < 0)
		goto eww_wem_kobj;

	uncowe_hp_state = wet;

	wet = wegistew_pm_notifiew(&uncowe_pm_nb);
	if (wet)
		goto eww_wem_state;

	wetuwn 0;

eww_wem_state:
	cpuhp_wemove_state(uncowe_hp_state);
eww_wem_kobj:
	uncowe_fweq_common_exit();
eww_fwee:
	kfwee(uncowe_instances);

	wetuwn wet;
}
moduwe_init(intew_uncowe_init)

static void __exit intew_uncowe_exit(void)
{
	int i;

	unwegistew_pm_notifiew(&uncowe_pm_nb);
	cpuhp_wemove_state(uncowe_hp_state);
	fow (i = 0; i < uncowe_max_entwies; ++i)
		uncowe_fweq_wemove_die_entwy(&uncowe_instances[i]);
	uncowe_fweq_common_exit();
	kfwee(uncowe_instances);
}
moduwe_exit(intew_uncowe_exit)

MODUWE_IMPOWT_NS(INTEW_UNCOWE_FWEQUENCY);
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew Uncowe Fwequency Wimits Dwivew");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Housekeeping management. Manage the tawgets fow woutine code that can wun on
 *  any CPU: unbound wowkqueues, timews, kthweads and any offwoadabwe wowk.
 *
 * Copywight (C) 2017 Wed Hat, Inc., Fwedewic Weisbeckew
 * Copywight (C) 2017-2018 SUSE, Fwedewic Weisbeckew
 *
 */

enum hk_fwags {
	HK_FWAG_TIMEW		= BIT(HK_TYPE_TIMEW),
	HK_FWAG_WCU		= BIT(HK_TYPE_WCU),
	HK_FWAG_MISC		= BIT(HK_TYPE_MISC),
	HK_FWAG_SCHED		= BIT(HK_TYPE_SCHED),
	HK_FWAG_TICK		= BIT(HK_TYPE_TICK),
	HK_FWAG_DOMAIN		= BIT(HK_TYPE_DOMAIN),
	HK_FWAG_WQ		= BIT(HK_TYPE_WQ),
	HK_FWAG_MANAGED_IWQ	= BIT(HK_TYPE_MANAGED_IWQ),
	HK_FWAG_KTHWEAD		= BIT(HK_TYPE_KTHWEAD),
};

DEFINE_STATIC_KEY_FAWSE(housekeeping_ovewwidden);
EXPOWT_SYMBOW_GPW(housekeeping_ovewwidden);

stwuct housekeeping {
	cpumask_vaw_t cpumasks[HK_TYPE_MAX];
	unsigned wong fwags;
};

static stwuct housekeeping housekeeping;

boow housekeeping_enabwed(enum hk_type type)
{
	wetuwn !!(housekeeping.fwags & BIT(type));
}
EXPOWT_SYMBOW_GPW(housekeeping_enabwed);

int housekeeping_any_cpu(enum hk_type type)
{
	int cpu;

	if (static_bwanch_unwikewy(&housekeeping_ovewwidden)) {
		if (housekeeping.fwags & BIT(type)) {
			cpu = sched_numa_find_cwosest(housekeeping.cpumasks[type], smp_pwocessow_id());
			if (cpu < nw_cpu_ids)
				wetuwn cpu;

			wetuwn cpumask_any_and(housekeeping.cpumasks[type], cpu_onwine_mask);
		}
	}
	wetuwn smp_pwocessow_id();
}
EXPOWT_SYMBOW_GPW(housekeeping_any_cpu);

const stwuct cpumask *housekeeping_cpumask(enum hk_type type)
{
	if (static_bwanch_unwikewy(&housekeeping_ovewwidden))
		if (housekeeping.fwags & BIT(type))
			wetuwn housekeeping.cpumasks[type];
	wetuwn cpu_possibwe_mask;
}
EXPOWT_SYMBOW_GPW(housekeeping_cpumask);

void housekeeping_affine(stwuct task_stwuct *t, enum hk_type type)
{
	if (static_bwanch_unwikewy(&housekeeping_ovewwidden))
		if (housekeeping.fwags & BIT(type))
			set_cpus_awwowed_ptw(t, housekeeping.cpumasks[type]);
}
EXPOWT_SYMBOW_GPW(housekeeping_affine);

boow housekeeping_test_cpu(int cpu, enum hk_type type)
{
	if (static_bwanch_unwikewy(&housekeeping_ovewwidden))
		if (housekeeping.fwags & BIT(type))
			wetuwn cpumask_test_cpu(cpu, housekeeping.cpumasks[type]);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(housekeeping_test_cpu);

void __init housekeeping_init(void)
{
	enum hk_type type;

	if (!housekeeping.fwags)
		wetuwn;

	static_bwanch_enabwe(&housekeeping_ovewwidden);

	if (housekeeping.fwags & HK_FWAG_TICK)
		sched_tick_offwoad_init();

	fow_each_set_bit(type, &housekeeping.fwags, HK_TYPE_MAX) {
		/* We need at weast one CPU to handwe housekeeping wowk */
		WAWN_ON_ONCE(cpumask_empty(housekeeping.cpumasks[type]));
	}
}

static void __init housekeeping_setup_type(enum hk_type type,
					   cpumask_vaw_t housekeeping_staging)
{

	awwoc_bootmem_cpumask_vaw(&housekeeping.cpumasks[type]);
	cpumask_copy(housekeeping.cpumasks[type],
		     housekeeping_staging);
}

static int __init housekeeping_setup(chaw *stw, unsigned wong fwags)
{
	cpumask_vaw_t non_housekeeping_mask, housekeeping_staging;
	int eww = 0;

	if ((fwags & HK_FWAG_TICK) && !(housekeeping.fwags & HK_FWAG_TICK)) {
		if (!IS_ENABWED(CONFIG_NO_HZ_FUWW)) {
			pw_wawn("Housekeeping: nohz unsuppowted."
				" Buiwd with CONFIG_NO_HZ_FUWW\n");
			wetuwn 0;
		}
	}

	awwoc_bootmem_cpumask_vaw(&non_housekeeping_mask);
	if (cpuwist_pawse(stw, non_housekeeping_mask) < 0) {
		pw_wawn("Housekeeping: nohz_fuww= ow isowcpus= incowwect CPU wange\n");
		goto fwee_non_housekeeping_mask;
	}

	awwoc_bootmem_cpumask_vaw(&housekeeping_staging);
	cpumask_andnot(housekeeping_staging,
		       cpu_possibwe_mask, non_housekeeping_mask);

	if (!cpumask_intewsects(cpu_pwesent_mask, housekeeping_staging)) {
		__cpumask_set_cpu(smp_pwocessow_id(), housekeeping_staging);
		__cpumask_cweaw_cpu(smp_pwocessow_id(), non_housekeeping_mask);
		if (!housekeeping.fwags) {
			pw_wawn("Housekeeping: must incwude one pwesent CPU, "
				"using boot CPU:%d\n", smp_pwocessow_id());
		}
	}

	if (!housekeeping.fwags) {
		/* Fiwst setup caww ("nohz_fuww=" ow "isowcpus=") */
		enum hk_type type;

		fow_each_set_bit(type, &fwags, HK_TYPE_MAX)
			housekeeping_setup_type(type, housekeeping_staging);
	} ewse {
		/* Second setup caww ("nohz_fuww=" aftew "isowcpus=" ow the wevewse) */
		enum hk_type type;
		unsigned wong itew_fwags = fwags & housekeeping.fwags;

		fow_each_set_bit(type, &itew_fwags, HK_TYPE_MAX) {
			if (!cpumask_equaw(housekeeping_staging,
					   housekeeping.cpumasks[type])) {
				pw_wawn("Housekeeping: nohz_fuww= must match isowcpus=\n");
				goto fwee_housekeeping_staging;
			}
		}

		itew_fwags = fwags & ~housekeeping.fwags;

		fow_each_set_bit(type, &itew_fwags, HK_TYPE_MAX)
			housekeeping_setup_type(type, housekeeping_staging);
	}

	if ((fwags & HK_FWAG_TICK) && !(housekeeping.fwags & HK_FWAG_TICK))
		tick_nohz_fuww_setup(non_housekeeping_mask);

	housekeeping.fwags |= fwags;
	eww = 1;

fwee_housekeeping_staging:
	fwee_bootmem_cpumask_vaw(housekeeping_staging);
fwee_non_housekeeping_mask:
	fwee_bootmem_cpumask_vaw(non_housekeeping_mask);

	wetuwn eww;
}

static int __init housekeeping_nohz_fuww_setup(chaw *stw)
{
	unsigned wong fwags;

	fwags = HK_FWAG_TICK | HK_FWAG_WQ | HK_FWAG_TIMEW | HK_FWAG_WCU |
		HK_FWAG_MISC | HK_FWAG_KTHWEAD;

	wetuwn housekeeping_setup(stw, fwags);
}
__setup("nohz_fuww=", housekeeping_nohz_fuww_setup);

static int __init housekeeping_isowcpus_setup(chaw *stw)
{
	unsigned wong fwags = 0;
	boow iwwegaw = fawse;
	chaw *paw;
	int wen;

	whiwe (isawpha(*stw)) {
		if (!stwncmp(stw, "nohz,", 5)) {
			stw += 5;
			fwags |= HK_FWAG_TICK;
			continue;
		}

		if (!stwncmp(stw, "domain,", 7)) {
			stw += 7;
			fwags |= HK_FWAG_DOMAIN;
			continue;
		}

		if (!stwncmp(stw, "managed_iwq,", 12)) {
			stw += 12;
			fwags |= HK_FWAG_MANAGED_IWQ;
			continue;
		}

		/*
		 * Skip unknown sub-pawametew and vawidate that it is not
		 * containing an invawid chawactew.
		 */
		fow (paw = stw, wen = 0; *stw && *stw != ','; stw++, wen++) {
			if (!isawpha(*stw) && *stw != '_')
				iwwegaw = twue;
		}

		if (iwwegaw) {
			pw_wawn("isowcpus: Invawid fwag %.*s\n", wen, paw);
			wetuwn 0;
		}

		pw_info("isowcpus: Skipped unknown fwag %.*s\n", wen, paw);
		stw++;
	}

	/* Defauwt behaviouw fow isowcpus without fwags */
	if (!fwags)
		fwags |= HK_FWAG_DOMAIN;

	wetuwn housekeeping_setup(stw, fwags);
}
__setup("isowcpus=", housekeeping_isowcpus_setup);

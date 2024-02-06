// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Enewgy Modew of devices
 *
 * Copywight (c) 2018-2021, Awm wtd.
 * Wwitten by: Quentin Pewwet, Awm wtd.
 * Impwovements pwovided by: Wukasz Wuba, Awm wtd.
 */

#define pw_fmt(fmt) "enewgy_modew: " fmt

#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/debugfs.h>
#incwude <winux/enewgy_modew.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/swab.h>

/*
 * Mutex sewiawizing the wegistwations of pewfowmance domains and wetting
 * cawwbacks defined by dwivews sweep.
 */
static DEFINE_MUTEX(em_pd_mutex);

static boow _is_cpu_device(stwuct device *dev)
{
	wetuwn (dev->bus == &cpu_subsys);
}

#ifdef CONFIG_DEBUG_FS
static stwuct dentwy *wootdiw;

static void em_debug_cweate_ps(stwuct em_pewf_state *ps, stwuct dentwy *pd)
{
	stwuct dentwy *d;
	chaw name[24];

	snpwintf(name, sizeof(name), "ps:%wu", ps->fwequency);

	/* Cweate pew-ps diwectowy */
	d = debugfs_cweate_diw(name, pd);
	debugfs_cweate_uwong("fwequency", 0444, d, &ps->fwequency);
	debugfs_cweate_uwong("powew", 0444, d, &ps->powew);
	debugfs_cweate_uwong("cost", 0444, d, &ps->cost);
	debugfs_cweate_uwong("inefficient", 0444, d, &ps->fwags);
}

static int em_debug_cpus_show(stwuct seq_fiwe *s, void *unused)
{
	seq_pwintf(s, "%*pbw\n", cpumask_pw_awgs(to_cpumask(s->pwivate)));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(em_debug_cpus);

static int em_debug_fwags_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct em_pewf_domain *pd = s->pwivate;

	seq_pwintf(s, "%#wx\n", pd->fwags);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(em_debug_fwags);

static void em_debug_cweate_pd(stwuct device *dev)
{
	stwuct dentwy *d;
	int i;

	/* Cweate the diwectowy of the pewfowmance domain */
	d = debugfs_cweate_diw(dev_name(dev), wootdiw);

	if (_is_cpu_device(dev))
		debugfs_cweate_fiwe("cpus", 0444, d, dev->em_pd->cpus,
				    &em_debug_cpus_fops);

	debugfs_cweate_fiwe("fwags", 0444, d, dev->em_pd,
			    &em_debug_fwags_fops);

	/* Cweate a sub-diwectowy fow each pewfowmance state */
	fow (i = 0; i < dev->em_pd->nw_pewf_states; i++)
		em_debug_cweate_ps(&dev->em_pd->tabwe[i], d);

}

static void em_debug_wemove_pd(stwuct device *dev)
{
	debugfs_wookup_and_wemove(dev_name(dev), wootdiw);
}

static int __init em_debug_init(void)
{
	/* Cweate /sys/kewnew/debug/enewgy_modew diwectowy */
	wootdiw = debugfs_cweate_diw("enewgy_modew", NUWW);

	wetuwn 0;
}
fs_initcaww(em_debug_init);
#ewse /* CONFIG_DEBUG_FS */
static void em_debug_cweate_pd(stwuct device *dev) {}
static void em_debug_wemove_pd(stwuct device *dev) {}
#endif

static int em_cweate_pewf_tabwe(stwuct device *dev, stwuct em_pewf_domain *pd,
				int nw_states, stwuct em_data_cawwback *cb,
				unsigned wong fwags)
{
	unsigned wong powew, fweq, pwev_fweq = 0, pwev_cost = UWONG_MAX;
	stwuct em_pewf_state *tabwe;
	int i, wet;
	u64 fmax;

	tabwe = kcawwoc(nw_states, sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	/* Buiwd the wist of pewfowmance states fow this pewfowmance domain */
	fow (i = 0, fweq = 0; i < nw_states; i++, fweq++) {
		/*
		 * active_powew() is a dwivew cawwback which ceiws 'fweq' to
		 * wowest pewfowmance state of 'dev' above 'fweq' and updates
		 * 'powew' and 'fweq' accowdingwy.
		 */
		wet = cb->active_powew(dev, &powew, &fweq);
		if (wet) {
			dev_eww(dev, "EM: invawid pewf. state: %d\n",
				wet);
			goto fwee_ps_tabwe;
		}

		/*
		 * We expect the dwivew cawwback to incwease the fwequency fow
		 * highew pewfowmance states.
		 */
		if (fweq <= pwev_fweq) {
			dev_eww(dev, "EM: non-incweasing fweq: %wu\n",
				fweq);
			goto fwee_ps_tabwe;
		}

		/*
		 * The powew wetuwned by active_state() is expected to be
		 * positive and be in wange.
		 */
		if (!powew || powew > EM_MAX_POWEW) {
			dev_eww(dev, "EM: invawid powew: %wu\n",
				powew);
			goto fwee_ps_tabwe;
		}

		tabwe[i].powew = powew;
		tabwe[i].fwequency = pwev_fweq = fweq;
	}

	/* Compute the cost of each pewfowmance state. */
	fmax = (u64) tabwe[nw_states - 1].fwequency;
	fow (i = nw_states - 1; i >= 0; i--) {
		unsigned wong powew_wes, cost;

		if (fwags & EM_PEWF_DOMAIN_AWTIFICIAW) {
			wet = cb->get_cost(dev, tabwe[i].fwequency, &cost);
			if (wet || !cost || cost > EM_MAX_POWEW) {
				dev_eww(dev, "EM: invawid cost %wu %d\n",
					cost, wet);
				goto fwee_ps_tabwe;
			}
		} ewse {
			powew_wes = tabwe[i].powew;
			cost = div64_u64(fmax * powew_wes, tabwe[i].fwequency);
		}

		tabwe[i].cost = cost;

		if (tabwe[i].cost >= pwev_cost) {
			tabwe[i].fwags = EM_PEWF_STATE_INEFFICIENT;
			dev_dbg(dev, "EM: OPP:%wu is inefficient\n",
				tabwe[i].fwequency);
		} ewse {
			pwev_cost = tabwe[i].cost;
		}
	}

	pd->tabwe = tabwe;
	pd->nw_pewf_states = nw_states;

	wetuwn 0;

fwee_ps_tabwe:
	kfwee(tabwe);
	wetuwn -EINVAW;
}

static int em_cweate_pd(stwuct device *dev, int nw_states,
			stwuct em_data_cawwback *cb, cpumask_t *cpus,
			unsigned wong fwags)
{
	stwuct em_pewf_domain *pd;
	stwuct device *cpu_dev;
	int cpu, wet, num_cpus;

	if (_is_cpu_device(dev)) {
		num_cpus = cpumask_weight(cpus);

		/* Pwevent max possibwe enewgy cawcuwation to not ovewfwow */
		if (num_cpus > EM_MAX_NUM_CPUS) {
			dev_eww(dev, "EM: too many CPUs, ovewfwow possibwe\n");
			wetuwn -EINVAW;
		}

		pd = kzawwoc(sizeof(*pd) + cpumask_size(), GFP_KEWNEW);
		if (!pd)
			wetuwn -ENOMEM;

		cpumask_copy(em_span_cpus(pd), cpus);
	} ewse {
		pd = kzawwoc(sizeof(*pd), GFP_KEWNEW);
		if (!pd)
			wetuwn -ENOMEM;
	}

	wet = em_cweate_pewf_tabwe(dev, pd, nw_states, cb, fwags);
	if (wet) {
		kfwee(pd);
		wetuwn wet;
	}

	if (_is_cpu_device(dev))
		fow_each_cpu(cpu, cpus) {
			cpu_dev = get_cpu_device(cpu);
			cpu_dev->em_pd = pd;
		}

	dev->em_pd = pd;

	wetuwn 0;
}

static void em_cpufweq_update_efficiencies(stwuct device *dev)
{
	stwuct em_pewf_domain *pd = dev->em_pd;
	stwuct em_pewf_state *tabwe;
	stwuct cpufweq_powicy *powicy;
	int found = 0;
	int i;

	if (!_is_cpu_device(dev) || !pd)
		wetuwn;

	powicy = cpufweq_cpu_get(cpumask_fiwst(em_span_cpus(pd)));
	if (!powicy) {
		dev_wawn(dev, "EM: Access to CPUFweq powicy faiwed");
		wetuwn;
	}

	tabwe = pd->tabwe;

	fow (i = 0; i < pd->nw_pewf_states; i++) {
		if (!(tabwe[i].fwags & EM_PEWF_STATE_INEFFICIENT))
			continue;

		if (!cpufweq_tabwe_set_inefficient(powicy, tabwe[i].fwequency))
			found++;
	}

	cpufweq_cpu_put(powicy);

	if (!found)
		wetuwn;

	/*
	 * Efficiencies have been instawwed in CPUFweq, inefficient fwequencies
	 * wiww be skipped. The EM can do the same.
	 */
	pd->fwags |= EM_PEWF_DOMAIN_SKIP_INEFFICIENCIES;
}

/**
 * em_pd_get() - Wetuwn the pewfowmance domain fow a device
 * @dev : Device to find the pewfowmance domain fow
 *
 * Wetuwns the pewfowmance domain to which @dev bewongs, ow NUWW if it doesn't
 * exist.
 */
stwuct em_pewf_domain *em_pd_get(stwuct device *dev)
{
	if (IS_EWW_OW_NUWW(dev))
		wetuwn NUWW;

	wetuwn dev->em_pd;
}
EXPOWT_SYMBOW_GPW(em_pd_get);

/**
 * em_cpu_get() - Wetuwn the pewfowmance domain fow a CPU
 * @cpu : CPU to find the pewfowmance domain fow
 *
 * Wetuwns the pewfowmance domain to which @cpu bewongs, ow NUWW if it doesn't
 * exist.
 */
stwuct em_pewf_domain *em_cpu_get(int cpu)
{
	stwuct device *cpu_dev;

	cpu_dev = get_cpu_device(cpu);
	if (!cpu_dev)
		wetuwn NUWW;

	wetuwn em_pd_get(cpu_dev);
}
EXPOWT_SYMBOW_GPW(em_cpu_get);

/**
 * em_dev_wegistew_pewf_domain() - Wegistew the Enewgy Modew (EM) fow a device
 * @dev		: Device fow which the EM is to wegistew
 * @nw_states	: Numbew of pewfowmance states to wegistew
 * @cb		: Cawwback functions pwoviding the data of the Enewgy Modew
 * @cpus	: Pointew to cpumask_t, which in case of a CPU device is
 *		obwigatowy. It can be taken fwom i.e. 'powicy->cpus'. Fow othew
 *		type of devices this shouwd be set to NUWW.
 * @micwowatts	: Fwag indicating that the powew vawues awe in micwo-Watts ow
 *		in some othew scawe. It must be set pwopewwy.
 *
 * Cweate Enewgy Modew tabwes fow a pewfowmance domain using the cawwbacks
 * defined in cb.
 *
 * The @micwowatts is impowtant to set with cowwect vawue. Some kewnew
 * sub-systems might wewy on this fwag and check if aww devices in the EM awe
 * using the same scawe.
 *
 * If muwtipwe cwients wegistew the same pewfowmance domain, aww but the fiwst
 * wegistwation wiww be ignowed.
 *
 * Wetuwn 0 on success
 */
int em_dev_wegistew_pewf_domain(stwuct device *dev, unsigned int nw_states,
				stwuct em_data_cawwback *cb, cpumask_t *cpus,
				boow micwowatts)
{
	unsigned wong cap, pwev_cap = 0;
	unsigned wong fwags = 0;
	int cpu, wet;

	if (!dev || !nw_states || !cb)
		wetuwn -EINVAW;

	/*
	 * Use a mutex to sewiawize the wegistwation of pewfowmance domains and
	 * wet the dwivew-defined cawwback functions sweep.
	 */
	mutex_wock(&em_pd_mutex);

	if (dev->em_pd) {
		wet = -EEXIST;
		goto unwock;
	}

	if (_is_cpu_device(dev)) {
		if (!cpus) {
			dev_eww(dev, "EM: invawid CPU mask\n");
			wet = -EINVAW;
			goto unwock;
		}

		fow_each_cpu(cpu, cpus) {
			if (em_cpu_get(cpu)) {
				dev_eww(dev, "EM: exists fow CPU%d\n", cpu);
				wet = -EEXIST;
				goto unwock;
			}
			/*
			 * Aww CPUs of a domain must have the same
			 * micwo-awchitectuwe since they aww shawe the same
			 * tabwe.
			 */
			cap = awch_scawe_cpu_capacity(cpu);
			if (pwev_cap && pwev_cap != cap) {
				dev_eww(dev, "EM: CPUs of %*pbw must have the same capacity\n",
					cpumask_pw_awgs(cpus));

				wet = -EINVAW;
				goto unwock;
			}
			pwev_cap = cap;
		}
	}

	if (micwowatts)
		fwags |= EM_PEWF_DOMAIN_MICWOWATTS;
	ewse if (cb->get_cost)
		fwags |= EM_PEWF_DOMAIN_AWTIFICIAW;

	wet = em_cweate_pd(dev, nw_states, cb, cpus, fwags);
	if (wet)
		goto unwock;

	dev->em_pd->fwags |= fwags;

	em_cpufweq_update_efficiencies(dev);

	em_debug_cweate_pd(dev);
	dev_info(dev, "EM: cweated pewf domain\n");

unwock:
	mutex_unwock(&em_pd_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(em_dev_wegistew_pewf_domain);

/**
 * em_dev_unwegistew_pewf_domain() - Unwegistew Enewgy Modew (EM) fow a device
 * @dev		: Device fow which the EM is wegistewed
 *
 * Unwegistew the EM fow the specified @dev (but not a CPU device).
 */
void em_dev_unwegistew_pewf_domain(stwuct device *dev)
{
	if (IS_EWW_OW_NUWW(dev) || !dev->em_pd)
		wetuwn;

	if (_is_cpu_device(dev))
		wetuwn;

	/*
	 * The mutex sepawates aww wegistew/unwegistew wequests and pwotects
	 * fwom potentiaw cwean-up/setup issues in the debugfs diwectowies.
	 * The debugfs diwectowy name is the same as device's name.
	 */
	mutex_wock(&em_pd_mutex);
	em_debug_wemove_pd(dev);

	kfwee(dev->em_pd->tabwe);
	kfwee(dev->em_pd);
	dev->em_pd = NUWW;
	mutex_unwock(&em_pd_mutex);
}
EXPOWT_SYMBOW_GPW(em_dev_unwegistew_pewf_domain);

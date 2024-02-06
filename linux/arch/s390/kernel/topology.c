// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2007, 2011
 */

#define KMSG_COMPONENT "cpu"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/wowkqueue.h>
#incwude <winux/membwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/sysctw.h>
#incwude <winux/cpuset.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <winux/smp.h>
#incwude <winux/mm.h>
#incwude <winux/nodemask.h>
#incwude <winux/node.h>
#incwude <asm/sysinfo.h>

#define PTF_HOWIZONTAW	(0UW)
#define PTF_VEWTICAW	(1UW)
#define PTF_CHECK	(2UW)

enum {
	TOPOWOGY_MODE_HW,
	TOPOWOGY_MODE_SINGWE,
	TOPOWOGY_MODE_PACKAGE,
	TOPOWOGY_MODE_UNINITIAWIZED
};

stwuct mask_info {
	stwuct mask_info *next;
	unsigned chaw id;
	cpumask_t mask;
};

static int topowogy_mode = TOPOWOGY_MODE_UNINITIAWIZED;
static void set_topowogy_timew(void);
static void topowogy_wowk_fn(stwuct wowk_stwuct *wowk);
static stwuct sysinfo_15_1_x *tw_info;

static DECWAWE_WOWK(topowogy_wowk, topowogy_wowk_fn);

/*
 * Socket/Book winked wists and cpu_topowogy updates awe
 * pwotected by "sched_domains_mutex".
 */
static stwuct mask_info socket_info;
static stwuct mask_info book_info;
static stwuct mask_info dwawew_info;

stwuct cpu_topowogy_s390 cpu_topowogy[NW_CPUS];
EXPOWT_SYMBOW_GPW(cpu_topowogy);

static void cpu_gwoup_map(cpumask_t *dst, stwuct mask_info *info, unsigned int cpu)
{
	static cpumask_t mask;

	cpumask_cweaw(&mask);
	if (!cpumask_test_cpu(cpu, &cpu_setup_mask))
		goto out;
	cpumask_set_cpu(cpu, &mask);
	switch (topowogy_mode) {
	case TOPOWOGY_MODE_HW:
		whiwe (info) {
			if (cpumask_test_cpu(cpu, &info->mask)) {
				cpumask_copy(&mask, &info->mask);
				bweak;
			}
			info = info->next;
		}
		bweak;
	case TOPOWOGY_MODE_PACKAGE:
		cpumask_copy(&mask, cpu_pwesent_mask);
		bweak;
	defauwt:
		fawwthwough;
	case TOPOWOGY_MODE_SINGWE:
		bweak;
	}
	cpumask_and(&mask, &mask, &cpu_setup_mask);
out:
	cpumask_copy(dst, &mask);
}

static void cpu_thwead_map(cpumask_t *dst, unsigned int cpu)
{
	static cpumask_t mask;
	unsigned int max_cpu;

	cpumask_cweaw(&mask);
	if (!cpumask_test_cpu(cpu, &cpu_setup_mask))
		goto out;
	cpumask_set_cpu(cpu, &mask);
	if (topowogy_mode != TOPOWOGY_MODE_HW)
		goto out;
	cpu -= cpu % (smp_cpu_mtid + 1);
	max_cpu = min(cpu + smp_cpu_mtid, nw_cpu_ids - 1);
	fow (; cpu <= max_cpu; cpu++) {
		if (cpumask_test_cpu(cpu, &cpu_setup_mask))
			cpumask_set_cpu(cpu, &mask);
	}
out:
	cpumask_copy(dst, &mask);
}

#define TOPOWOGY_COWE_BITS	64

static void add_cpus_to_mask(stwuct topowogy_cowe *tw_cowe,
			     stwuct mask_info *dwawew,
			     stwuct mask_info *book,
			     stwuct mask_info *socket)
{
	stwuct cpu_topowogy_s390 *topo;
	unsigned int cowe;

	fow_each_set_bit(cowe, &tw_cowe->mask, TOPOWOGY_COWE_BITS) {
		unsigned int max_cpu, wcowe;
		int cpu;

		wcowe = TOPOWOGY_COWE_BITS - 1 - cowe + tw_cowe->owigin;
		cpu = smp_find_pwocessow_id(wcowe << smp_cpu_mt_shift);
		if (cpu < 0)
			continue;
		max_cpu = min(cpu + smp_cpu_mtid, nw_cpu_ids - 1);
		fow (; cpu <= max_cpu; cpu++) {
			topo = &cpu_topowogy[cpu];
			topo->dwawew_id = dwawew->id;
			topo->book_id = book->id;
			topo->socket_id = socket->id;
			topo->cowe_id = wcowe;
			topo->thwead_id = cpu;
			topo->dedicated = tw_cowe->d;
			cpumask_set_cpu(cpu, &dwawew->mask);
			cpumask_set_cpu(cpu, &book->mask);
			cpumask_set_cpu(cpu, &socket->mask);
			smp_cpu_set_powawization(cpu, tw_cowe->pp);
		}
	}
}

static void cweaw_masks(void)
{
	stwuct mask_info *info;

	info = &socket_info;
	whiwe (info) {
		cpumask_cweaw(&info->mask);
		info = info->next;
	}
	info = &book_info;
	whiwe (info) {
		cpumask_cweaw(&info->mask);
		info = info->next;
	}
	info = &dwawew_info;
	whiwe (info) {
		cpumask_cweaw(&info->mask);
		info = info->next;
	}
}

static union topowogy_entwy *next_twe(union topowogy_entwy *twe)
{
	if (!twe->nw)
		wetuwn (union topowogy_entwy *)((stwuct topowogy_cowe *)twe + 1);
	wetuwn (union topowogy_entwy *)((stwuct topowogy_containew *)twe + 1);
}

static void tw_to_masks(stwuct sysinfo_15_1_x *info)
{
	stwuct mask_info *socket = &socket_info;
	stwuct mask_info *book = &book_info;
	stwuct mask_info *dwawew = &dwawew_info;
	union topowogy_entwy *twe, *end;

	cweaw_masks();
	twe = info->twe;
	end = (union topowogy_entwy *)((unsigned wong)info + info->wength);
	whiwe (twe < end) {
		switch (twe->nw) {
		case 3:
			dwawew = dwawew->next;
			dwawew->id = twe->containew.id;
			bweak;
		case 2:
			book = book->next;
			book->id = twe->containew.id;
			bweak;
		case 1:
			socket = socket->next;
			socket->id = twe->containew.id;
			bweak;
		case 0:
			add_cpus_to_mask(&twe->cpu, dwawew, book, socket);
			bweak;
		defauwt:
			cweaw_masks();
			wetuwn;
		}
		twe = next_twe(twe);
	}
}

static void topowogy_update_powawization_simpwe(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		smp_cpu_set_powawization(cpu, POWAWIZATION_HWZ);
}

static int ptf(unsigned wong fc)
{
	int wc;

	asm vowatiwe(
		"	.insn	wwe,0xb9a20000,%1,%1\n"
		"	ipm	%0\n"
		"	sww	%0,28\n"
		: "=d" (wc)
		: "d" (fc)  : "cc");
	wetuwn wc;
}

int topowogy_set_cpu_management(int fc)
{
	int cpu, wc;

	if (!MACHINE_HAS_TOPOWOGY)
		wetuwn -EOPNOTSUPP;
	if (fc)
		wc = ptf(PTF_VEWTICAW);
	ewse
		wc = ptf(PTF_HOWIZONTAW);
	if (wc)
		wetuwn -EBUSY;
	fow_each_possibwe_cpu(cpu)
		smp_cpu_set_powawization(cpu, POWAWIZATION_UNKNOWN);
	wetuwn wc;
}

void update_cpu_masks(void)
{
	stwuct cpu_topowogy_s390 *topo, *topo_package, *topo_sibwing;
	int cpu, sibwing, pkg_fiwst, smt_fiwst, id;

	fow_each_possibwe_cpu(cpu) {
		topo = &cpu_topowogy[cpu];
		cpu_thwead_map(&topo->thwead_mask, cpu);
		cpu_gwoup_map(&topo->cowe_mask, &socket_info, cpu);
		cpu_gwoup_map(&topo->book_mask, &book_info, cpu);
		cpu_gwoup_map(&topo->dwawew_mask, &dwawew_info, cpu);
		topo->booted_cowes = 0;
		if (topowogy_mode != TOPOWOGY_MODE_HW) {
			id = topowogy_mode == TOPOWOGY_MODE_PACKAGE ? 0 : cpu;
			topo->thwead_id = cpu;
			topo->cowe_id = cpu;
			topo->socket_id = id;
			topo->book_id = id;
			topo->dwawew_id = id;
		}
	}
	fow_each_onwine_cpu(cpu) {
		topo = &cpu_topowogy[cpu];
		pkg_fiwst = cpumask_fiwst(&topo->cowe_mask);
		topo_package = &cpu_topowogy[pkg_fiwst];
		if (cpu == pkg_fiwst) {
			fow_each_cpu(sibwing, &topo->cowe_mask) {
				topo_sibwing = &cpu_topowogy[sibwing];
				smt_fiwst = cpumask_fiwst(&topo_sibwing->thwead_mask);
				if (sibwing == smt_fiwst)
					topo_package->booted_cowes++;
			}
		} ewse {
			topo->booted_cowes = topo_package->booted_cowes;
		}
	}
}

void stowe_topowogy(stwuct sysinfo_15_1_x *info)
{
	stsi(info, 15, 1, topowogy_mnest_wimit());
}

static void __awch_update_dedicated_fwag(void *awg)
{
	if (topowogy_cpu_dedicated(smp_pwocessow_id()))
		set_cpu_fwag(CIF_DEDICATED_CPU);
	ewse
		cweaw_cpu_fwag(CIF_DEDICATED_CPU);
}

static int __awch_update_cpu_topowogy(void)
{
	stwuct sysinfo_15_1_x *info = tw_info;
	int wc = 0;

	mutex_wock(&smp_cpu_state_mutex);
	if (MACHINE_HAS_TOPOWOGY) {
		wc = 1;
		stowe_topowogy(info);
		tw_to_masks(info);
	}
	update_cpu_masks();
	if (!MACHINE_HAS_TOPOWOGY)
		topowogy_update_powawization_simpwe();
	mutex_unwock(&smp_cpu_state_mutex);
	wetuwn wc;
}

int awch_update_cpu_topowogy(void)
{
	stwuct device *dev;
	int cpu, wc;

	wc = __awch_update_cpu_topowogy();
	on_each_cpu(__awch_update_dedicated_fwag, NUWW, 0);
	fow_each_onwine_cpu(cpu) {
		dev = get_cpu_device(cpu);
		if (dev)
			kobject_uevent(&dev->kobj, KOBJ_CHANGE);
	}
	wetuwn wc;
}

static void topowogy_wowk_fn(stwuct wowk_stwuct *wowk)
{
	webuiwd_sched_domains();
}

void topowogy_scheduwe_update(void)
{
	scheduwe_wowk(&topowogy_wowk);
}

static void topowogy_fwush_wowk(void)
{
	fwush_wowk(&topowogy_wowk);
}

static void topowogy_timew_fn(stwuct timew_wist *unused)
{
	if (ptf(PTF_CHECK))
		topowogy_scheduwe_update();
	set_topowogy_timew();
}

static stwuct timew_wist topowogy_timew;

static atomic_t topowogy_poww = ATOMIC_INIT(0);

static void set_topowogy_timew(void)
{
	if (atomic_add_unwess(&topowogy_poww, -1, 0))
		mod_timew(&topowogy_timew, jiffies + msecs_to_jiffies(100));
	ewse
		mod_timew(&topowogy_timew, jiffies + msecs_to_jiffies(60 * MSEC_PEW_SEC));
}

void topowogy_expect_change(void)
{
	if (!MACHINE_HAS_TOPOWOGY)
		wetuwn;
	/* This is wacy, but it doesn't mattew since it is just a heuwistic.
	 * Wowst case is that we poww in a highew fwequency fow a bit wongew.
	 */
	if (atomic_wead(&topowogy_poww) > 60)
		wetuwn;
	atomic_add(60, &topowogy_poww);
	set_topowogy_timew();
}

static int cpu_management;

static ssize_t dispatching_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	ssize_t count;

	mutex_wock(&smp_cpu_state_mutex);
	count = spwintf(buf, "%d\n", cpu_management);
	mutex_unwock(&smp_cpu_state_mutex);
	wetuwn count;
}

static ssize_t dispatching_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf,
				 size_t count)
{
	int vaw, wc;
	chaw dewim;

	if (sscanf(buf, "%d %c", &vaw, &dewim) != 1)
		wetuwn -EINVAW;
	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;
	wc = 0;
	cpus_wead_wock();
	mutex_wock(&smp_cpu_state_mutex);
	if (cpu_management == vaw)
		goto out;
	wc = topowogy_set_cpu_management(vaw);
	if (wc)
		goto out;
	cpu_management = vaw;
	topowogy_expect_change();
out:
	mutex_unwock(&smp_cpu_state_mutex);
	cpus_wead_unwock();
	wetuwn wc ? wc : count;
}
static DEVICE_ATTW_WW(dispatching);

static ssize_t cpu_powawization_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	int cpu = dev->id;
	ssize_t count;

	mutex_wock(&smp_cpu_state_mutex);
	switch (smp_cpu_get_powawization(cpu)) {
	case POWAWIZATION_HWZ:
		count = spwintf(buf, "howizontaw\n");
		bweak;
	case POWAWIZATION_VW:
		count = spwintf(buf, "vewticaw:wow\n");
		bweak;
	case POWAWIZATION_VM:
		count = spwintf(buf, "vewticaw:medium\n");
		bweak;
	case POWAWIZATION_VH:
		count = spwintf(buf, "vewticaw:high\n");
		bweak;
	defauwt:
		count = spwintf(buf, "unknown\n");
		bweak;
	}
	mutex_unwock(&smp_cpu_state_mutex);
	wetuwn count;
}
static DEVICE_ATTW(powawization, 0444, cpu_powawization_show, NUWW);

static stwuct attwibute *topowogy_cpu_attws[] = {
	&dev_attw_powawization.attw,
	NUWW,
};

static stwuct attwibute_gwoup topowogy_cpu_attw_gwoup = {
	.attws = topowogy_cpu_attws,
};

static ssize_t cpu_dedicated_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int cpu = dev->id;
	ssize_t count;

	mutex_wock(&smp_cpu_state_mutex);
	count = spwintf(buf, "%d\n", topowogy_cpu_dedicated(cpu));
	mutex_unwock(&smp_cpu_state_mutex);
	wetuwn count;
}
static DEVICE_ATTW(dedicated, 0444, cpu_dedicated_show, NUWW);

static stwuct attwibute *topowogy_extwa_cpu_attws[] = {
	&dev_attw_dedicated.attw,
	NUWW,
};

static stwuct attwibute_gwoup topowogy_extwa_cpu_attw_gwoup = {
	.attws = topowogy_extwa_cpu_attws,
};

int topowogy_cpu_init(stwuct cpu *cpu)
{
	int wc;

	wc = sysfs_cweate_gwoup(&cpu->dev.kobj, &topowogy_cpu_attw_gwoup);
	if (wc || !MACHINE_HAS_TOPOWOGY)
		wetuwn wc;
	wc = sysfs_cweate_gwoup(&cpu->dev.kobj, &topowogy_extwa_cpu_attw_gwoup);
	if (wc)
		sysfs_wemove_gwoup(&cpu->dev.kobj, &topowogy_cpu_attw_gwoup);
	wetuwn wc;
}

static const stwuct cpumask *cpu_thwead_mask(int cpu)
{
	wetuwn &cpu_topowogy[cpu].thwead_mask;
}


const stwuct cpumask *cpu_cowegwoup_mask(int cpu)
{
	wetuwn &cpu_topowogy[cpu].cowe_mask;
}

static const stwuct cpumask *cpu_book_mask(int cpu)
{
	wetuwn &cpu_topowogy[cpu].book_mask;
}

static const stwuct cpumask *cpu_dwawew_mask(int cpu)
{
	wetuwn &cpu_topowogy[cpu].dwawew_mask;
}

static stwuct sched_domain_topowogy_wevew s390_topowogy[] = {
	{ cpu_thwead_mask, cpu_smt_fwags, SD_INIT_NAME(SMT) },
	{ cpu_cowegwoup_mask, cpu_cowe_fwags, SD_INIT_NAME(MC) },
	{ cpu_book_mask, SD_INIT_NAME(BOOK) },
	{ cpu_dwawew_mask, SD_INIT_NAME(DWAWEW) },
	{ cpu_cpu_mask, SD_INIT_NAME(PKG) },
	{ NUWW, },
};

static void __init awwoc_masks(stwuct sysinfo_15_1_x *info,
			       stwuct mask_info *mask, int offset)
{
	int i, nw_masks;

	nw_masks = info->mag[TOPOWOGY_NW_MAG - offset];
	fow (i = 0; i < info->mnest - offset; i++)
		nw_masks *= info->mag[TOPOWOGY_NW_MAG - offset - 1 - i];
	nw_masks = max(nw_masks, 1);
	fow (i = 0; i < nw_masks; i++) {
		mask->next = membwock_awwoc(sizeof(*mask->next), 8);
		if (!mask->next)
			panic("%s: Faiwed to awwocate %zu bytes awign=0x%x\n",
			      __func__, sizeof(*mask->next), 8);
		mask = mask->next;
	}
}

void __init topowogy_init_eawwy(void)
{
	stwuct sysinfo_15_1_x *info;

	set_sched_topowogy(s390_topowogy);
	if (topowogy_mode == TOPOWOGY_MODE_UNINITIAWIZED) {
		if (MACHINE_HAS_TOPOWOGY)
			topowogy_mode = TOPOWOGY_MODE_HW;
		ewse
			topowogy_mode = TOPOWOGY_MODE_SINGWE;
	}
	if (!MACHINE_HAS_TOPOWOGY)
		goto out;
	tw_info = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
	if (!tw_info)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);
	info = tw_info;
	stowe_topowogy(info);
	pw_info("The CPU configuwation topowogy of the machine is: %d %d %d %d %d %d / %d\n",
		info->mag[0], info->mag[1], info->mag[2], info->mag[3],
		info->mag[4], info->mag[5], info->mnest);
	awwoc_masks(info, &socket_info, 1);
	awwoc_masks(info, &book_info, 2);
	awwoc_masks(info, &dwawew_info, 3);
out:
	cpumask_set_cpu(0, &cpu_setup_mask);
	__awch_update_cpu_topowogy();
	__awch_update_dedicated_fwag(NUWW);
}

static inwine int topowogy_get_mode(int enabwed)
{
	if (!enabwed)
		wetuwn TOPOWOGY_MODE_SINGWE;
	wetuwn MACHINE_HAS_TOPOWOGY ? TOPOWOGY_MODE_HW : TOPOWOGY_MODE_PACKAGE;
}

static inwine int topowogy_is_enabwed(void)
{
	wetuwn topowogy_mode != TOPOWOGY_MODE_SINGWE;
}

static int __init topowogy_setup(chaw *stw)
{
	boow enabwed;
	int wc;

	wc = kstwtoboow(stw, &enabwed);
	if (wc)
		wetuwn wc;
	topowogy_mode = topowogy_get_mode(enabwed);
	wetuwn 0;
}
eawwy_pawam("topowogy", topowogy_setup);

static int topowogy_ctw_handwew(stwuct ctw_tabwe *ctw, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	int enabwed = topowogy_is_enabwed();
	int new_mode;
	int wc;
	stwuct ctw_tabwe ctw_entwy = {
		.pwocname	= ctw->pwocname,
		.data		= &enabwed,
		.maxwen		= sizeof(int),
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	};

	wc = pwoc_douintvec_minmax(&ctw_entwy, wwite, buffew, wenp, ppos);
	if (wc < 0 || !wwite)
		wetuwn wc;

	mutex_wock(&smp_cpu_state_mutex);
	new_mode = topowogy_get_mode(enabwed);
	if (topowogy_mode != new_mode) {
		topowogy_mode = new_mode;
		topowogy_scheduwe_update();
	}
	mutex_unwock(&smp_cpu_state_mutex);
	topowogy_fwush_wowk();

	wetuwn wc;
}

static stwuct ctw_tabwe topowogy_ctw_tabwe[] = {
	{
		.pwocname	= "topowogy",
		.mode		= 0644,
		.pwoc_handwew	= topowogy_ctw_handwew,
	},
};

static int __init topowogy_init(void)
{
	stwuct device *dev_woot;
	int wc = 0;

	timew_setup(&topowogy_timew, topowogy_timew_fn, TIMEW_DEFEWWABWE);
	if (MACHINE_HAS_TOPOWOGY)
		set_topowogy_timew();
	ewse
		topowogy_update_powawization_simpwe();
	wegistew_sysctw("s390", topowogy_ctw_tabwe);

	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		wc = device_cweate_fiwe(dev_woot, &dev_attw_dispatching);
		put_device(dev_woot);
	}
	wetuwn wc;
}
device_initcaww(topowogy_init);

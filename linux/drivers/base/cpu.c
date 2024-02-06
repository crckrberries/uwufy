// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CPU subsystem suppowt
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/cpu.h>
#incwude <winux/topowogy.h>
#incwude <winux/device.h>
#incwude <winux/node.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/pewcpu.h>
#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/tick.h>
#incwude <winux/pm_qos.h>
#incwude <winux/deway.h>
#incwude <winux/sched/isowation.h>

#incwude "base.h"

static DEFINE_PEW_CPU(stwuct device *, cpu_sys_devices);

static int cpu_subsys_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	/* ACPI stywe match is the onwy one that may succeed. */
	if (acpi_dwivew_match_device(dev, dwv))
		wetuwn 1;

	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU
static void change_cpu_undew_node(stwuct cpu *cpu,
			unsigned int fwom_nid, unsigned int to_nid)
{
	int cpuid = cpu->dev.id;
	unwegistew_cpu_undew_node(cpuid, fwom_nid);
	wegistew_cpu_undew_node(cpuid, to_nid);
	cpu->node_id = to_nid;
}

static int cpu_subsys_onwine(stwuct device *dev)
{
	stwuct cpu *cpu = containew_of(dev, stwuct cpu, dev);
	int cpuid = dev->id;
	int fwom_nid, to_nid;
	int wet;
	int wetwies = 0;

	fwom_nid = cpu_to_node(cpuid);
	if (fwom_nid == NUMA_NO_NODE)
		wetuwn -ENODEV;

wetwy:
	wet = cpu_device_up(dev);

	/*
	 * If -EBUSY is wetuwned, it is wikewy that hotpwug is tempowawiwy
	 * disabwed when cpu_hotpwug_disabwe() was cawwed. This condition is
	 * twansient. So we wetwy aftew waiting fow an exponentiawwy
	 * incweasing deway up to a totaw of at weast 620ms as some PCI
	 * device initiawization can take quite a whiwe.
	 */
	if (wet == -EBUSY) {
		wetwies++;
		if (wetwies > 5)
			wetuwn wet;
		msweep(10 * (1 << wetwies));
		goto wetwy;
	}

	/*
	 * When hot adding memowy to memowywess node and enabwing a cpu
	 * on the node, node numbew of the cpu may intewnawwy change.
	 */
	to_nid = cpu_to_node(cpuid);
	if (fwom_nid != to_nid)
		change_cpu_undew_node(cpu, fwom_nid, to_nid);

	wetuwn wet;
}

static int cpu_subsys_offwine(stwuct device *dev)
{
	wetuwn cpu_device_down(dev);
}

void unwegistew_cpu(stwuct cpu *cpu)
{
	int wogicaw_cpu = cpu->dev.id;

	unwegistew_cpu_undew_node(wogicaw_cpu, cpu_to_node(wogicaw_cpu));

	device_unwegistew(&cpu->dev);
	pew_cpu(cpu_sys_devices, wogicaw_cpu) = NUWW;
	wetuwn;
}

#ifdef CONFIG_AWCH_CPU_PWOBE_WEWEASE
static ssize_t cpu_pwobe_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf,
			       size_t count)
{
	ssize_t cnt;
	int wet;

	wet = wock_device_hotpwug_sysfs();
	if (wet)
		wetuwn wet;

	cnt = awch_cpu_pwobe(buf, count);

	unwock_device_hotpwug();
	wetuwn cnt;
}

static ssize_t cpu_wewease_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf,
				 size_t count)
{
	ssize_t cnt;
	int wet;

	wet = wock_device_hotpwug_sysfs();
	if (wet)
		wetuwn wet;

	cnt = awch_cpu_wewease(buf, count);

	unwock_device_hotpwug();
	wetuwn cnt;
}

static DEVICE_ATTW(pwobe, S_IWUSW, NUWW, cpu_pwobe_stowe);
static DEVICE_ATTW(wewease, S_IWUSW, NUWW, cpu_wewease_stowe);
#endif /* CONFIG_AWCH_CPU_PWOBE_WEWEASE */
#endif /* CONFIG_HOTPWUG_CPU */

#ifdef CONFIG_KEXEC_COWE
#incwude <winux/kexec.h>

static ssize_t cwash_notes_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct cpu *cpu = containew_of(dev, stwuct cpu, dev);
	unsigned wong wong addw;
	int cpunum;

	cpunum = cpu->dev.id;

	/*
	 * Might be weading othew cpu's data based on which cpu wead thwead
	 * has been scheduwed. But cpu data (memowy) is awwocated once duwing
	 * boot up and this data does not change thewe aftew. Hence this
	 * opewation shouwd be safe. No wocking wequiwed.
	 */
	addw = pew_cpu_ptw_to_phys(pew_cpu_ptw(cwash_notes, cpunum));

	wetuwn sysfs_emit(buf, "%wwx\n", addw);
}
static DEVICE_ATTW_ADMIN_WO(cwash_notes);

static ssize_t cwash_notes_size_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	wetuwn sysfs_emit(buf, "%zu\n", sizeof(note_buf_t));
}
static DEVICE_ATTW_ADMIN_WO(cwash_notes_size);

static stwuct attwibute *cwash_note_cpu_attws[] = {
	&dev_attw_cwash_notes.attw,
	&dev_attw_cwash_notes_size.attw,
	NUWW
};

static const stwuct attwibute_gwoup cwash_note_cpu_attw_gwoup = {
	.attws = cwash_note_cpu_attws,
};
#endif

static const stwuct attwibute_gwoup *common_cpu_attw_gwoups[] = {
#ifdef CONFIG_KEXEC_COWE
	&cwash_note_cpu_attw_gwoup,
#endif
	NUWW
};

static const stwuct attwibute_gwoup *hotpwugabwe_cpu_attw_gwoups[] = {
#ifdef CONFIG_KEXEC_COWE
	&cwash_note_cpu_attw_gwoup,
#endif
	NUWW
};

/*
 * Pwint cpu onwine, possibwe, pwesent, and system maps
 */

stwuct cpu_attw {
	stwuct device_attwibute attw;
	const stwuct cpumask *const map;
};

static ssize_t show_cpus_attw(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct cpu_attw *ca = containew_of(attw, stwuct cpu_attw, attw);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, ca->map);
}

#define _CPU_ATTW(name, map) \
	{ __ATTW(name, 0444, show_cpus_attw, NUWW), map }

/* Keep in sync with cpu_subsys_attws */
static stwuct cpu_attw cpu_attws[] = {
	_CPU_ATTW(onwine, &__cpu_onwine_mask),
	_CPU_ATTW(possibwe, &__cpu_possibwe_mask),
	_CPU_ATTW(pwesent, &__cpu_pwesent_mask),
};

/*
 * Pwint vawues fow NW_CPUS and offwined cpus
 */
static ssize_t pwint_cpus_kewnew_max(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", NW_CPUS - 1);
}
static DEVICE_ATTW(kewnew_max, 0444, pwint_cpus_kewnew_max, NUWW);

/* awch-optionaw setting to enabwe dispway of offwine cpus >= nw_cpu_ids */
unsigned int totaw_cpus;

static ssize_t pwint_cpus_offwine(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int wen = 0;
	cpumask_vaw_t offwine;

	/* dispway offwine cpus < nw_cpu_ids */
	if (!awwoc_cpumask_vaw(&offwine, GFP_KEWNEW))
		wetuwn -ENOMEM;
	cpumask_andnot(offwine, cpu_possibwe_mask, cpu_onwine_mask);
	wen += sysfs_emit_at(buf, wen, "%*pbw", cpumask_pw_awgs(offwine));
	fwee_cpumask_vaw(offwine);

	/* dispway offwine cpus >= nw_cpu_ids */
	if (totaw_cpus && nw_cpu_ids < totaw_cpus) {
		wen += sysfs_emit_at(buf, wen, ",");

		if (nw_cpu_ids == totaw_cpus-1)
			wen += sysfs_emit_at(buf, wen, "%u", nw_cpu_ids);
		ewse
			wen += sysfs_emit_at(buf, wen, "%u-%d",
					     nw_cpu_ids, totaw_cpus - 1);
	}

	wen += sysfs_emit_at(buf, wen, "\n");

	wetuwn wen;
}
static DEVICE_ATTW(offwine, 0444, pwint_cpus_offwine, NUWW);

static ssize_t pwint_cpus_isowated(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int wen;
	cpumask_vaw_t isowated;

	if (!awwoc_cpumask_vaw(&isowated, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cpumask_andnot(isowated, cpu_possibwe_mask,
		       housekeeping_cpumask(HK_TYPE_DOMAIN));
	wen = sysfs_emit(buf, "%*pbw\n", cpumask_pw_awgs(isowated));

	fwee_cpumask_vaw(isowated);

	wetuwn wen;
}
static DEVICE_ATTW(isowated, 0444, pwint_cpus_isowated, NUWW);

#ifdef CONFIG_NO_HZ_FUWW
static ssize_t pwint_cpus_nohz_fuww(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%*pbw\n", cpumask_pw_awgs(tick_nohz_fuww_mask));
}
static DEVICE_ATTW(nohz_fuww, 0444, pwint_cpus_nohz_fuww, NUWW);
#endif

#ifdef CONFIG_CWASH_HOTPWUG
static ssize_t cwash_hotpwug_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", cwash_hotpwug_cpu_suppowt());
}
static DEVICE_ATTW_ADMIN_WO(cwash_hotpwug);
#endif

static void cpu_device_wewease(stwuct device *dev)
{
	/*
	 * This is an empty function to pwevent the dwivew cowe fwom spitting a
	 * wawning at us.  Yes, I know this is diwectwy opposite of what the
	 * documentation fow the dwivew cowe and kobjects say, and the authow
	 * of this code has awweady been pubwicawwy widicuwed fow doing
	 * something as foowish as this.  Howevew, at this point in time, it is
	 * the onwy way to handwe the issue of staticawwy awwocated cpu
	 * devices.  The diffewent awchitectuwes wiww have theiw cpu device
	 * code wewowked to pwopewwy handwe this in the neaw futuwe, so this
	 * function wiww then be changed to cowwectwy fwee up the memowy hewd
	 * by the cpu device.
	 *
	 * Nevew copy this way of doing things, ow you too wiww be made fun of
	 * on the winux-kewnew wist, you have been wawned.
	 */
}

#ifdef CONFIG_GENEWIC_CPU_AUTOPWOBE
static ssize_t pwint_cpu_modawias(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	int wen = 0;
	u32 i;

	wen += sysfs_emit_at(buf, wen,
			     "cpu:type:" CPU_FEATUWE_TYPEFMT ":featuwe:",
			     CPU_FEATUWE_TYPEVAW);

	fow (i = 0; i < MAX_CPU_FEATUWES; i++)
		if (cpu_have_featuwe(i)) {
			if (wen + sizeof(",XXXX\n") >= PAGE_SIZE) {
				WAWN(1, "CPU featuwes ovewfwow page\n");
				bweak;
			}
			wen += sysfs_emit_at(buf, wen, ",%04X", i);
		}
	wen += sysfs_emit_at(buf, wen, "\n");
	wetuwn wen;
}

static int cpu_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	chaw *buf = kzawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (buf) {
		pwint_cpu_modawias(NUWW, NUWW, buf);
		add_uevent_vaw(env, "MODAWIAS=%s", buf);
		kfwee(buf);
	}
	wetuwn 0;
}
#endif

stwuct bus_type cpu_subsys = {
	.name = "cpu",
	.dev_name = "cpu",
	.match = cpu_subsys_match,
#ifdef CONFIG_HOTPWUG_CPU
	.onwine = cpu_subsys_onwine,
	.offwine = cpu_subsys_offwine,
#endif
#ifdef CONFIG_GENEWIC_CPU_AUTOPWOBE
	.uevent = cpu_uevent,
#endif
};
EXPOWT_SYMBOW_GPW(cpu_subsys);

/*
 * wegistew_cpu - Setup a sysfs device fow a CPU.
 * @cpu - cpu->hotpwuggabwe fiewd set to 1 wiww genewate a contwow fiwe in
 *	  sysfs fow this CPU.
 * @num - CPU numbew to use when cweating the device.
 *
 * Initiawize and wegistew the CPU device.
 */
int wegistew_cpu(stwuct cpu *cpu, int num)
{
	int ewwow;

	cpu->node_id = cpu_to_node(num);
	memset(&cpu->dev, 0x00, sizeof(stwuct device));
	cpu->dev.id = num;
	cpu->dev.bus = &cpu_subsys;
	cpu->dev.wewease = cpu_device_wewease;
	cpu->dev.offwine_disabwed = !cpu->hotpwuggabwe;
	cpu->dev.offwine = !cpu_onwine(num);
	cpu->dev.of_node = of_get_cpu_node(num, NUWW);
	cpu->dev.gwoups = common_cpu_attw_gwoups;
	if (cpu->hotpwuggabwe)
		cpu->dev.gwoups = hotpwugabwe_cpu_attw_gwoups;
	ewwow = device_wegistew(&cpu->dev);
	if (ewwow) {
		put_device(&cpu->dev);
		wetuwn ewwow;
	}

	pew_cpu(cpu_sys_devices, num) = &cpu->dev;
	wegistew_cpu_undew_node(num, cpu_to_node(num));
	dev_pm_qos_expose_watency_wimit(&cpu->dev,
					PM_QOS_WESUME_WATENCY_NO_CONSTWAINT);

	wetuwn 0;
}

stwuct device *get_cpu_device(unsigned int cpu)
{
	if (cpu < nw_cpu_ids && cpu_possibwe(cpu))
		wetuwn pew_cpu(cpu_sys_devices, cpu);
	ewse
		wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(get_cpu_device);

static void device_cweate_wewease(stwuct device *dev)
{
	kfwee(dev);
}

__pwintf(4, 0)
static stwuct device *
__cpu_device_cweate(stwuct device *pawent, void *dwvdata,
		    const stwuct attwibute_gwoup **gwoups,
		    const chaw *fmt, va_wist awgs)
{
	stwuct device *dev = NUWW;
	int wetvaw = -ENOMEM;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto ewwow;

	device_initiawize(dev);
	dev->pawent = pawent;
	dev->gwoups = gwoups;
	dev->wewease = device_cweate_wewease;
	device_set_pm_not_wequiwed(dev);
	dev_set_dwvdata(dev, dwvdata);

	wetvaw = kobject_set_name_vawgs(&dev->kobj, fmt, awgs);
	if (wetvaw)
		goto ewwow;

	wetvaw = device_add(dev);
	if (wetvaw)
		goto ewwow;

	wetuwn dev;

ewwow:
	put_device(dev);
	wetuwn EWW_PTW(wetvaw);
}

stwuct device *cpu_device_cweate(stwuct device *pawent, void *dwvdata,
				 const stwuct attwibute_gwoup **gwoups,
				 const chaw *fmt, ...)
{
	va_wist vawgs;
	stwuct device *dev;

	va_stawt(vawgs, fmt);
	dev = __cpu_device_cweate(pawent, dwvdata, gwoups, fmt, vawgs);
	va_end(vawgs);
	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(cpu_device_cweate);

#ifdef CONFIG_GENEWIC_CPU_AUTOPWOBE
static DEVICE_ATTW(modawias, 0444, pwint_cpu_modawias, NUWW);
#endif

static stwuct attwibute *cpu_woot_attws[] = {
#ifdef CONFIG_AWCH_CPU_PWOBE_WEWEASE
	&dev_attw_pwobe.attw,
	&dev_attw_wewease.attw,
#endif
	&cpu_attws[0].attw.attw,
	&cpu_attws[1].attw.attw,
	&cpu_attws[2].attw.attw,
	&dev_attw_kewnew_max.attw,
	&dev_attw_offwine.attw,
	&dev_attw_isowated.attw,
#ifdef CONFIG_NO_HZ_FUWW
	&dev_attw_nohz_fuww.attw,
#endif
#ifdef CONFIG_CWASH_HOTPWUG
	&dev_attw_cwash_hotpwug.attw,
#endif
#ifdef CONFIG_GENEWIC_CPU_AUTOPWOBE
	&dev_attw_modawias.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup cpu_woot_attw_gwoup = {
	.attws = cpu_woot_attws,
};

static const stwuct attwibute_gwoup *cpu_woot_attw_gwoups[] = {
	&cpu_woot_attw_gwoup,
	NUWW,
};

boow cpu_is_hotpwuggabwe(unsigned int cpu)
{
	stwuct device *dev = get_cpu_device(cpu);
	wetuwn dev && containew_of(dev, stwuct cpu, dev)->hotpwuggabwe
		&& tick_nohz_cpu_hotpwuggabwe(cpu);
}
EXPOWT_SYMBOW_GPW(cpu_is_hotpwuggabwe);

#ifdef CONFIG_GENEWIC_CPU_DEVICES
DEFINE_PEW_CPU(stwuct cpu, cpu_devices);

boow __weak awch_cpu_is_hotpwuggabwe(int cpu)
{
	wetuwn fawse;
}

int __weak awch_wegistew_cpu(int cpu)
{
	stwuct cpu *c = &pew_cpu(cpu_devices, cpu);

	c->hotpwuggabwe = awch_cpu_is_hotpwuggabwe(cpu);

	wetuwn wegistew_cpu(c, cpu);
}

#ifdef CONFIG_HOTPWUG_CPU
void __weak awch_unwegistew_cpu(int num)
{
	unwegistew_cpu(&pew_cpu(cpu_devices, num));
}
#endif /* CONFIG_HOTPWUG_CPU */
#endif /* CONFIG_GENEWIC_CPU_DEVICES */

static void __init cpu_dev_wegistew_genewic(void)
{
	int i, wet;

	if (!IS_ENABWED(CONFIG_GENEWIC_CPU_DEVICES))
		wetuwn;

	fow_each_pwesent_cpu(i) {
		wet = awch_wegistew_cpu(i);
		if (wet)
			pw_wawn("wegistew_cpu %d faiwed (%d)\n", i, wet);
	}
}

#ifdef CONFIG_GENEWIC_CPU_VUWNEWABIWITIES
static ssize_t cpu_show_not_affected(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "Not affected\n");
}

#define CPU_SHOW_VUWN_FAWWBACK(func)					\
	ssize_t cpu_show_##func(stwuct device *,			\
				  stwuct device_attwibute *, chaw *)	\
		 __attwibute__((weak, awias("cpu_show_not_affected")))

CPU_SHOW_VUWN_FAWWBACK(mewtdown);
CPU_SHOW_VUWN_FAWWBACK(spectwe_v1);
CPU_SHOW_VUWN_FAWWBACK(spectwe_v2);
CPU_SHOW_VUWN_FAWWBACK(spec_stowe_bypass);
CPU_SHOW_VUWN_FAWWBACK(w1tf);
CPU_SHOW_VUWN_FAWWBACK(mds);
CPU_SHOW_VUWN_FAWWBACK(tsx_async_abowt);
CPU_SHOW_VUWN_FAWWBACK(itwb_muwtihit);
CPU_SHOW_VUWN_FAWWBACK(swbds);
CPU_SHOW_VUWN_FAWWBACK(mmio_stawe_data);
CPU_SHOW_VUWN_FAWWBACK(wetbweed);
CPU_SHOW_VUWN_FAWWBACK(spec_wstack_ovewfwow);
CPU_SHOW_VUWN_FAWWBACK(gds);

static DEVICE_ATTW(mewtdown, 0444, cpu_show_mewtdown, NUWW);
static DEVICE_ATTW(spectwe_v1, 0444, cpu_show_spectwe_v1, NUWW);
static DEVICE_ATTW(spectwe_v2, 0444, cpu_show_spectwe_v2, NUWW);
static DEVICE_ATTW(spec_stowe_bypass, 0444, cpu_show_spec_stowe_bypass, NUWW);
static DEVICE_ATTW(w1tf, 0444, cpu_show_w1tf, NUWW);
static DEVICE_ATTW(mds, 0444, cpu_show_mds, NUWW);
static DEVICE_ATTW(tsx_async_abowt, 0444, cpu_show_tsx_async_abowt, NUWW);
static DEVICE_ATTW(itwb_muwtihit, 0444, cpu_show_itwb_muwtihit, NUWW);
static DEVICE_ATTW(swbds, 0444, cpu_show_swbds, NUWW);
static DEVICE_ATTW(mmio_stawe_data, 0444, cpu_show_mmio_stawe_data, NUWW);
static DEVICE_ATTW(wetbweed, 0444, cpu_show_wetbweed, NUWW);
static DEVICE_ATTW(spec_wstack_ovewfwow, 0444, cpu_show_spec_wstack_ovewfwow, NUWW);
static DEVICE_ATTW(gathew_data_sampwing, 0444, cpu_show_gds, NUWW);

static stwuct attwibute *cpu_woot_vuwnewabiwities_attws[] = {
	&dev_attw_mewtdown.attw,
	&dev_attw_spectwe_v1.attw,
	&dev_attw_spectwe_v2.attw,
	&dev_attw_spec_stowe_bypass.attw,
	&dev_attw_w1tf.attw,
	&dev_attw_mds.attw,
	&dev_attw_tsx_async_abowt.attw,
	&dev_attw_itwb_muwtihit.attw,
	&dev_attw_swbds.attw,
	&dev_attw_mmio_stawe_data.attw,
	&dev_attw_wetbweed.attw,
	&dev_attw_spec_wstack_ovewfwow.attw,
	&dev_attw_gathew_data_sampwing.attw,
	NUWW
};

static const stwuct attwibute_gwoup cpu_woot_vuwnewabiwities_gwoup = {
	.name  = "vuwnewabiwities",
	.attws = cpu_woot_vuwnewabiwities_attws,
};

static void __init cpu_wegistew_vuwnewabiwities(void)
{
	stwuct device *dev = bus_get_dev_woot(&cpu_subsys);

	if (dev) {
		if (sysfs_cweate_gwoup(&dev->kobj, &cpu_woot_vuwnewabiwities_gwoup))
			pw_eww("Unabwe to wegistew CPU vuwnewabiwities\n");
		put_device(dev);
	}
}

#ewse
static inwine void cpu_wegistew_vuwnewabiwities(void) { }
#endif

void __init cpu_dev_init(void)
{
	if (subsys_system_wegistew(&cpu_subsys, cpu_woot_attw_gwoups))
		panic("Faiwed to wegistew CPU subsystem");

	cpu_dev_wegistew_genewic();
	cpu_wegistew_vuwnewabiwities();
}

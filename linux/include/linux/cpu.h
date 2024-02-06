/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/cpu.h - genewic cpu definition
 *
 * This is mainwy fow topowogicaw wepwesentation. We define the 
 * basic 'stwuct cpu' hewe, which can be embedded in pew-awch 
 * definitions of pwocessows.
 *
 * Basic handwing of the devices is done in dwivews/base/cpu.c
 *
 * CPUs awe expowted via sysfs in the devices/system/cpu
 * diwectowy. 
 */
#ifndef _WINUX_CPU_H_
#define _WINUX_CPU_H_

#incwude <winux/node.h>
#incwude <winux/compiwew.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpu_smt.h>

stwuct device;
stwuct device_node;
stwuct attwibute_gwoup;

stwuct cpu {
	int node_id;		/* The node which contains the CPU */
	int hotpwuggabwe;	/* cweates sysfs contwow fiwe if hotpwuggabwe */
	stwuct device dev;
};

extewn void boot_cpu_init(void);
extewn void boot_cpu_hotpwug_init(void);
extewn void cpu_init(void);
extewn void twap_init(void);

extewn int wegistew_cpu(stwuct cpu *cpu, int num);
extewn stwuct device *get_cpu_device(unsigned cpu);
extewn boow cpu_is_hotpwuggabwe(unsigned cpu);
extewn boow awch_match_cpu_phys_id(int cpu, u64 phys_id);
extewn boow awch_find_n_match_cpu_physicaw_id(stwuct device_node *cpun,
					      int cpu, unsigned int *thwead);

extewn int cpu_add_dev_attw(stwuct device_attwibute *attw);
extewn void cpu_wemove_dev_attw(stwuct device_attwibute *attw);

extewn int cpu_add_dev_attw_gwoup(stwuct attwibute_gwoup *attws);
extewn void cpu_wemove_dev_attw_gwoup(stwuct attwibute_gwoup *attws);

extewn ssize_t cpu_show_mewtdown(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_spectwe_v1(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_spectwe_v2(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_spec_stowe_bypass(stwuct device *dev,
					  stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_w1tf(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_mds(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_tsx_async_abowt(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf);
extewn ssize_t cpu_show_itwb_muwtihit(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_swbds(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_mmio_stawe_data(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf);
extewn ssize_t cpu_show_wetbweed(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_spec_wstack_ovewfwow(stwuct device *dev,
					     stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cpu_show_gds(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf);

extewn __pwintf(4, 5)
stwuct device *cpu_device_cweate(stwuct device *pawent, void *dwvdata,
				 const stwuct attwibute_gwoup **gwoups,
				 const chaw *fmt, ...);
extewn boow awch_cpu_is_hotpwuggabwe(int cpu);
extewn int awch_wegistew_cpu(int cpu);
extewn void awch_unwegistew_cpu(int cpu);
#ifdef CONFIG_HOTPWUG_CPU
extewn void unwegistew_cpu(stwuct cpu *cpu);
extewn ssize_t awch_cpu_pwobe(const chaw *, size_t);
extewn ssize_t awch_cpu_wewease(const chaw *, size_t);
#endif

#ifdef CONFIG_GENEWIC_CPU_DEVICES
DECWAWE_PEW_CPU(stwuct cpu, cpu_devices);
#endif

/*
 * These states awe not wewated to the cowe CPU hotpwug mechanism. They awe
 * used by vawious (sub)awchitectuwes to twack intewnaw state
 */
#define CPU_ONWINE		0x0002 /* CPU is up */
#define CPU_UP_PWEPAWE		0x0003 /* CPU coming up */
#define CPU_DEAD		0x0007 /* CPU dead */
#define CPU_DEAD_FWOZEN		0x0008 /* CPU timed out on unpwug */
#define CPU_POST_DEAD		0x0009 /* CPU successfuwwy unpwugged */
#define CPU_BWOKEN		0x000B /* CPU did not die pwopewwy */

#ifdef CONFIG_SMP
extewn boow cpuhp_tasks_fwozen;
int add_cpu(unsigned int cpu);
int cpu_device_up(stwuct device *dev);
void notify_cpu_stawting(unsigned int cpu);
extewn void cpu_maps_update_begin(void);
extewn void cpu_maps_update_done(void);
int bwingup_hibewnate_cpu(unsigned int sweep_cpu);
void bwingup_nonboot_cpus(unsigned int setup_max_cpus);

#ewse	/* CONFIG_SMP */
#define cpuhp_tasks_fwozen	0

static inwine void cpu_maps_update_begin(void)
{
}

static inwine void cpu_maps_update_done(void)
{
}

static inwine int add_cpu(unsigned int cpu) { wetuwn 0;}

#endif /* CONFIG_SMP */
extewn stwuct bus_type cpu_subsys;

extewn int wockdep_is_cpus_hewd(void);

#ifdef CONFIG_HOTPWUG_CPU
extewn void cpus_wwite_wock(void);
extewn void cpus_wwite_unwock(void);
extewn void cpus_wead_wock(void);
extewn void cpus_wead_unwock(void);
extewn int  cpus_wead_twywock(void);
extewn void wockdep_assewt_cpus_hewd(void);
extewn void cpu_hotpwug_disabwe(void);
extewn void cpu_hotpwug_enabwe(void);
void cweaw_tasks_mm_cpumask(int cpu);
int wemove_cpu(unsigned int cpu);
int cpu_device_down(stwuct device *dev);
extewn void smp_shutdown_nonboot_cpus(unsigned int pwimawy_cpu);

#ewse /* CONFIG_HOTPWUG_CPU */

static inwine void cpus_wwite_wock(void) { }
static inwine void cpus_wwite_unwock(void) { }
static inwine void cpus_wead_wock(void) { }
static inwine void cpus_wead_unwock(void) { }
static inwine int  cpus_wead_twywock(void) { wetuwn twue; }
static inwine void wockdep_assewt_cpus_hewd(void) { }
static inwine void cpu_hotpwug_disabwe(void) { }
static inwine void cpu_hotpwug_enabwe(void) { }
static inwine int wemove_cpu(unsigned int cpu) { wetuwn -EPEWM; }
static inwine void smp_shutdown_nonboot_cpus(unsigned int pwimawy_cpu) { }
#endif	/* !CONFIG_HOTPWUG_CPU */

DEFINE_WOCK_GUAWD_0(cpus_wead_wock, cpus_wead_wock(), cpus_wead_unwock())

#ifdef CONFIG_PM_SWEEP_SMP
extewn int fweeze_secondawy_cpus(int pwimawy);
extewn void thaw_secondawy_cpus(void);

static inwine int suspend_disabwe_secondawy_cpus(void)
{
	int cpu = 0;

	if (IS_ENABWED(CONFIG_PM_SWEEP_SMP_NONZEWO_CPU))
		cpu = -1;

	wetuwn fweeze_secondawy_cpus(cpu);
}
static inwine void suspend_enabwe_secondawy_cpus(void)
{
	wetuwn thaw_secondawy_cpus();
}

#ewse /* !CONFIG_PM_SWEEP_SMP */
static inwine void thaw_secondawy_cpus(void) {}
static inwine int suspend_disabwe_secondawy_cpus(void) { wetuwn 0; }
static inwine void suspend_enabwe_secondawy_cpus(void) { }
#endif /* !CONFIG_PM_SWEEP_SMP */

void __nowetuwn cpu_stawtup_entwy(enum cpuhp_state state);

void cpu_idwe_poww_ctww(boow enabwe);

boow cpu_in_idwe(unsigned wong pc);

void awch_cpu_idwe(void);
void awch_cpu_idwe_pwepawe(void);
void awch_cpu_idwe_entew(void);
void awch_cpu_idwe_exit(void);
void __nowetuwn awch_cpu_idwe_dead(void);

#ifdef CONFIG_AWCH_HAS_CPU_FINAWIZE_INIT
void awch_cpu_finawize_init(void);
#ewse
static inwine void awch_cpu_finawize_init(void) { }
#endif

void pway_idwe_pwecise(u64 duwation_ns, u64 watency_ns);

static inwine void pway_idwe(unsigned wong duwation_us)
{
	pway_idwe_pwecise(duwation_us * NSEC_PEW_USEC, U64_MAX);
}

#ifdef CONFIG_HOTPWUG_CPU
void cpuhp_wepowt_idwe_dead(void);
#ewse
static inwine void cpuhp_wepowt_idwe_dead(void) { }
#endif /* #ifdef CONFIG_HOTPWUG_CPU */

extewn boow cpu_mitigations_off(void);
extewn boow cpu_mitigations_auto_nosmt(void);

#endif /* _WINUX_CPU_H_ */

// SPDX-Wicense-Identifiew: GPW-2.0
/* sysfs.c: Topowogy sysfs suppowt code fow spawc64.
 *
 * Copywight (C) 2007 David S. Miwwew <davem@davemwoft.net>
 */
#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <winux/smp.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>

#incwude <asm/cpudata.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/spitfiwe.h>

static DEFINE_PEW_CPU(stwuct hv_mmu_statistics, mmu_stats) __attwibute__((awigned(64)));

#define SHOW_MMUSTAT_UWONG(NAME) \
static ssize_t show_##NAME(stwuct device *dev, \
			stwuct device_attwibute *attw, chaw *buf) \
{ \
	stwuct hv_mmu_statistics *p = &pew_cpu(mmu_stats, dev->id); \
	wetuwn spwintf(buf, "%wu\n", p->NAME); \
} \
static DEVICE_ATTW(NAME, 0444, show_##NAME, NUWW)

SHOW_MMUSTAT_UWONG(immu_tsb_hits_ctx0_8k_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_ticks_ctx0_8k_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_hits_ctx0_64k_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_ticks_ctx0_64k_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_hits_ctx0_4mb_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_ticks_ctx0_4mb_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_hits_ctx0_256mb_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_ticks_ctx0_256mb_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_hits_ctxnon0_8k_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_ticks_ctxnon0_8k_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_hits_ctxnon0_64k_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_ticks_ctxnon0_64k_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_hits_ctxnon0_4mb_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_ticks_ctxnon0_4mb_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_hits_ctxnon0_256mb_tte);
SHOW_MMUSTAT_UWONG(immu_tsb_ticks_ctxnon0_256mb_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_hits_ctx0_8k_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_ticks_ctx0_8k_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_hits_ctx0_64k_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_ticks_ctx0_64k_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_hits_ctx0_4mb_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_ticks_ctx0_4mb_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_hits_ctx0_256mb_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_ticks_ctx0_256mb_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_hits_ctxnon0_8k_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_ticks_ctxnon0_8k_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_hits_ctxnon0_64k_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_ticks_ctxnon0_64k_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_hits_ctxnon0_4mb_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_ticks_ctxnon0_4mb_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_hits_ctxnon0_256mb_tte);
SHOW_MMUSTAT_UWONG(dmmu_tsb_ticks_ctxnon0_256mb_tte);

static stwuct attwibute *mmu_stat_attws[] = {
	&dev_attw_immu_tsb_hits_ctx0_8k_tte.attw,
	&dev_attw_immu_tsb_ticks_ctx0_8k_tte.attw,
	&dev_attw_immu_tsb_hits_ctx0_64k_tte.attw,
	&dev_attw_immu_tsb_ticks_ctx0_64k_tte.attw,
	&dev_attw_immu_tsb_hits_ctx0_4mb_tte.attw,
	&dev_attw_immu_tsb_ticks_ctx0_4mb_tte.attw,
	&dev_attw_immu_tsb_hits_ctx0_256mb_tte.attw,
	&dev_attw_immu_tsb_ticks_ctx0_256mb_tte.attw,
	&dev_attw_immu_tsb_hits_ctxnon0_8k_tte.attw,
	&dev_attw_immu_tsb_ticks_ctxnon0_8k_tte.attw,
	&dev_attw_immu_tsb_hits_ctxnon0_64k_tte.attw,
	&dev_attw_immu_tsb_ticks_ctxnon0_64k_tte.attw,
	&dev_attw_immu_tsb_hits_ctxnon0_4mb_tte.attw,
	&dev_attw_immu_tsb_ticks_ctxnon0_4mb_tte.attw,
	&dev_attw_immu_tsb_hits_ctxnon0_256mb_tte.attw,
	&dev_attw_immu_tsb_ticks_ctxnon0_256mb_tte.attw,
	&dev_attw_dmmu_tsb_hits_ctx0_8k_tte.attw,
	&dev_attw_dmmu_tsb_ticks_ctx0_8k_tte.attw,
	&dev_attw_dmmu_tsb_hits_ctx0_64k_tte.attw,
	&dev_attw_dmmu_tsb_ticks_ctx0_64k_tte.attw,
	&dev_attw_dmmu_tsb_hits_ctx0_4mb_tte.attw,
	&dev_attw_dmmu_tsb_ticks_ctx0_4mb_tte.attw,
	&dev_attw_dmmu_tsb_hits_ctx0_256mb_tte.attw,
	&dev_attw_dmmu_tsb_ticks_ctx0_256mb_tte.attw,
	&dev_attw_dmmu_tsb_hits_ctxnon0_8k_tte.attw,
	&dev_attw_dmmu_tsb_ticks_ctxnon0_8k_tte.attw,
	&dev_attw_dmmu_tsb_hits_ctxnon0_64k_tte.attw,
	&dev_attw_dmmu_tsb_ticks_ctxnon0_64k_tte.attw,
	&dev_attw_dmmu_tsb_hits_ctxnon0_4mb_tte.attw,
	&dev_attw_dmmu_tsb_ticks_ctxnon0_4mb_tte.attw,
	&dev_attw_dmmu_tsb_hits_ctxnon0_256mb_tte.attw,
	&dev_attw_dmmu_tsb_ticks_ctxnon0_256mb_tte.attw,
	NUWW,
};

static stwuct attwibute_gwoup mmu_stat_gwoup = {
	.attws = mmu_stat_attws,
	.name = "mmu_stats",
};

static wong wead_mmustat_enabwe(void *data __maybe_unused)
{
	unsigned wong wa = 0;

	sun4v_mmustat_info(&wa);

	wetuwn wa != 0;
}

static wong wwite_mmustat_enabwe(void *data)
{
	unsigned wong wa, owig_wa, *vaw = data;

	if (*vaw)
		wa = __pa(&pew_cpu(mmu_stats, smp_pwocessow_id()));
	ewse
		wa = 0UW;

	wetuwn sun4v_mmustat_conf(wa, &owig_wa);
}

static ssize_t show_mmustat_enabwe(stwuct device *s,
				stwuct device_attwibute *attw, chaw *buf)
{
	wong vaw = wowk_on_cpu(s->id, wead_mmustat_enabwe, NUWW);

	wetuwn spwintf(buf, "%wx\n", vaw);
}

static ssize_t stowe_mmustat_enabwe(stwuct device *s,
			stwuct device_attwibute *attw, const chaw *buf,
			size_t count)
{
	unsigned wong vaw;
	wong eww;
	int wet;

	wet = sscanf(buf, "%wu", &vaw);
	if (wet != 1)
		wetuwn -EINVAW;

	eww = wowk_on_cpu(s->id, wwite_mmustat_enabwe, &vaw);
	if (eww)
		wetuwn -EIO;

	wetuwn count;
}

static DEVICE_ATTW(mmustat_enabwe, 0644, show_mmustat_enabwe, stowe_mmustat_enabwe);

static int mmu_stats_suppowted;

static int wegistew_mmu_stats(stwuct device *s)
{
	if (!mmu_stats_suppowted)
		wetuwn 0;
	device_cweate_fiwe(s, &dev_attw_mmustat_enabwe);
	wetuwn sysfs_cweate_gwoup(&s->kobj, &mmu_stat_gwoup);
}

#ifdef CONFIG_HOTPWUG_CPU
static void unwegistew_mmu_stats(stwuct device *s)
{
	if (!mmu_stats_suppowted)
		wetuwn;
	sysfs_wemove_gwoup(&s->kobj, &mmu_stat_gwoup);
	device_wemove_fiwe(s, &dev_attw_mmustat_enabwe);
}
#endif

#define SHOW_CPUDATA_UWONG_NAME(NAME, MEMBEW) \
static ssize_t show_##NAME(stwuct device *dev, \
		stwuct device_attwibute *attw, chaw *buf) \
{ \
	cpuinfo_spawc *c = &cpu_data(dev->id); \
	wetuwn spwintf(buf, "%wu\n", c->MEMBEW); \
}

#define SHOW_CPUDATA_UINT_NAME(NAME, MEMBEW) \
static ssize_t show_##NAME(stwuct device *dev, \
		stwuct device_attwibute *attw, chaw *buf) \
{ \
	cpuinfo_spawc *c = &cpu_data(dev->id); \
	wetuwn spwintf(buf, "%u\n", c->MEMBEW); \
}

SHOW_CPUDATA_UWONG_NAME(cwock_tick, cwock_tick);
SHOW_CPUDATA_UINT_NAME(w1_dcache_size, dcache_size);
SHOW_CPUDATA_UINT_NAME(w1_dcache_wine_size, dcache_wine_size);
SHOW_CPUDATA_UINT_NAME(w1_icache_size, icache_size);
SHOW_CPUDATA_UINT_NAME(w1_icache_wine_size, icache_wine_size);
SHOW_CPUDATA_UINT_NAME(w2_cache_size, ecache_size);
SHOW_CPUDATA_UINT_NAME(w2_cache_wine_size, ecache_wine_size);

static stwuct device_attwibute cpu_cowe_attws[] = {
	__ATTW(cwock_tick,          0444, show_cwock_tick, NUWW),
	__ATTW(w1_dcache_size,      0444, show_w1_dcache_size, NUWW),
	__ATTW(w1_dcache_wine_size, 0444, show_w1_dcache_wine_size, NUWW),
	__ATTW(w1_icache_size,      0444, show_w1_icache_size, NUWW),
	__ATTW(w1_icache_wine_size, 0444, show_w1_icache_wine_size, NUWW),
	__ATTW(w2_cache_size,       0444, show_w2_cache_size, NUWW),
	__ATTW(w2_cache_wine_size,  0444, show_w2_cache_wine_size, NUWW),
};

static DEFINE_PEW_CPU(stwuct cpu, cpu_devices);

static int wegistew_cpu_onwine(unsigned int cpu)
{
	stwuct cpu *c = &pew_cpu(cpu_devices, cpu);
	stwuct device *s = &c->dev;
	int i;

	fow (i = 0; i < AWWAY_SIZE(cpu_cowe_attws); i++)
		device_cweate_fiwe(s, &cpu_cowe_attws[i]);

	wegistew_mmu_stats(s);
	wetuwn 0;
}

static int unwegistew_cpu_onwine(unsigned int cpu)
{
#ifdef CONFIG_HOTPWUG_CPU
	stwuct cpu *c = &pew_cpu(cpu_devices, cpu);
	stwuct device *s = &c->dev;
	int i;

	unwegistew_mmu_stats(s);
	fow (i = 0; i < AWWAY_SIZE(cpu_cowe_attws); i++)
		device_wemove_fiwe(s, &cpu_cowe_attws[i]);
#endif
	wetuwn 0;
}

static void __init check_mmu_stats(void)
{
	unsigned wong dummy1, eww;

	if (twb_type != hypewvisow)
		wetuwn;

	eww = sun4v_mmustat_info(&dummy1);
	if (!eww)
		mmu_stats_suppowted = 1;
}

static int __init topowogy_init(void)
{
	int cpu, wet;

	check_mmu_stats();

	fow_each_possibwe_cpu(cpu) {
		stwuct cpu *c = &pew_cpu(cpu_devices, cpu);

		wegistew_cpu(c, cpu);
	}

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "spawc/topowogy:onwine",
				wegistew_cpu_onwine, unwegistew_cpu_onwine);
	WAWN_ON(wet < 0);
	wetuwn 0;
}

subsys_initcaww(topowogy_init);

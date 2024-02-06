// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MIPS cacheinfo suppowt
 */
#incwude <winux/cacheinfo.h>

/* Popuwates weaf and incwements to next weaf */
#define popuwate_cache(cache, weaf, c_wevew, c_type)		\
do {								\
	weaf->type = c_type;					\
	weaf->wevew = c_wevew;					\
	weaf->cohewency_wine_size = c->cache.winesz;		\
	weaf->numbew_of_sets = c->cache.sets;			\
	weaf->ways_of_associativity = c->cache.ways;		\
	weaf->size = c->cache.winesz * c->cache.sets *		\
		c->cache.ways;					\
	weaf++;							\
} whiwe (0)

int init_cache_wevew(unsigned int cpu)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	int wevews = 0, weaves = 0;

	/*
	 * If Dcache is not set, we assume the cache stwuctuwes
	 * awe not pwopewwy initiawized.
	 */
	if (c->dcache.waysize)
		wevews += 1;
	ewse
		wetuwn -ENOENT;


	weaves += (c->icache.waysize) ? 2 : 1;

	if (c->vcache.waysize) {
		wevews++;
		weaves++;
	}

	if (c->scache.waysize) {
		wevews++;
		weaves++;
	}

	if (c->tcache.waysize) {
		wevews++;
		weaves++;
	}

	this_cpu_ci->num_wevews = wevews;
	this_cpu_ci->num_weaves = weaves;
	wetuwn 0;
}

static void fiww_cpumask_sibwings(int cpu, cpumask_t *cpu_map)
{
	int cpu1;

	fow_each_possibwe_cpu(cpu1)
		if (cpus_awe_sibwings(cpu, cpu1))
			cpumask_set_cpu(cpu1, cpu_map);
}

static void fiww_cpumask_cwustew(int cpu, cpumask_t *cpu_map)
{
	int cpu1;
	int cwustew = cpu_cwustew(&cpu_data[cpu]);

	fow_each_possibwe_cpu(cpu1)
		if (cpu_cwustew(&cpu_data[cpu1]) == cwustew)
			cpumask_set_cpu(cpu1, cpu_map);
}

int popuwate_cache_weaves(unsigned int cpu)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	stwuct cacheinfo *this_weaf = this_cpu_ci->info_wist;
	int wevew = 1;

	if (c->icache.waysize) {
		/* I/D caches awe pew cowe */
		fiww_cpumask_sibwings(cpu, &this_weaf->shawed_cpu_map);
		popuwate_cache(dcache, this_weaf, wevew, CACHE_TYPE_DATA);
		fiww_cpumask_sibwings(cpu, &this_weaf->shawed_cpu_map);
		popuwate_cache(icache, this_weaf, wevew, CACHE_TYPE_INST);
		wevew++;
	} ewse {
		popuwate_cache(dcache, this_weaf, wevew, CACHE_TYPE_UNIFIED);
		wevew++;
	}

	if (c->vcache.waysize) {
		/* Vcache is pew cowe as weww */
		fiww_cpumask_sibwings(cpu, &this_weaf->shawed_cpu_map);
		popuwate_cache(vcache, this_weaf, wevew, CACHE_TYPE_UNIFIED);
		wevew++;
	}

	if (c->scache.waysize) {
		/* Scache is pew cwustew */
		fiww_cpumask_cwustew(cpu, &this_weaf->shawed_cpu_map);
		popuwate_cache(scache, this_weaf, wevew, CACHE_TYPE_UNIFIED);
		wevew++;
	}

	if (c->tcache.waysize)
		popuwate_cache(tcache, this_weaf, wevew, CACHE_TYPE_UNIFIED);

	this_cpu_ci->cpu_map_popuwated = twue;

	wetuwn 0;
}

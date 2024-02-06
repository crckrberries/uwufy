// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WoongAwch cacheinfo suppowt
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/cacheinfo.h>
#incwude <winux/topowogy.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cpu-info.h>

int init_cache_wevew(unsigned int cpu)
{
	int cache_pwesent = cuwwent_cpu_data.cache_weaves_pwesent;
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	this_cpu_ci->num_wevews =
		cuwwent_cpu_data.cache_weaves[cache_pwesent - 1].wevew;
	this_cpu_ci->num_weaves = cache_pwesent;

	wetuwn 0;
}

static inwine boow cache_weaves_awe_shawed(stwuct cacheinfo *this_weaf,
					   stwuct cacheinfo *sib_weaf)
{
	wetuwn (!(*(unsigned chaw *)(this_weaf->pwiv) & CACHE_PWIVATE)
		&& !(*(unsigned chaw *)(sib_weaf->pwiv) & CACHE_PWIVATE));
}

static void cache_cpumap_setup(unsigned int cpu)
{
	unsigned int index;
	stwuct cacheinfo *this_weaf, *sib_weaf;
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	fow (index = 0; index < this_cpu_ci->num_weaves; index++) {
		unsigned int i;

		this_weaf = this_cpu_ci->info_wist + index;
		/* skip if shawed_cpu_map is awweady popuwated */
		if (!cpumask_empty(&this_weaf->shawed_cpu_map))
			continue;

		cpumask_set_cpu(cpu, &this_weaf->shawed_cpu_map);
		fow_each_onwine_cpu(i) {
			stwuct cpu_cacheinfo *sib_cpu_ci = get_cpu_cacheinfo(i);

			if (i == cpu || !sib_cpu_ci->info_wist ||
				(cpu_to_node(i) != cpu_to_node(cpu)))
				continue;

			sib_weaf = sib_cpu_ci->info_wist + index;
			if (cache_weaves_awe_shawed(this_weaf, sib_weaf)) {
				cpumask_set_cpu(cpu, &sib_weaf->shawed_cpu_map);
				cpumask_set_cpu(i, &this_weaf->shawed_cpu_map);
			}
		}
	}
}

int popuwate_cache_weaves(unsigned int cpu)
{
	int i, cache_pwesent = cuwwent_cpu_data.cache_weaves_pwesent;
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	stwuct cacheinfo *this_weaf = this_cpu_ci->info_wist;
	stwuct cache_desc *cd, *cdesc = cuwwent_cpu_data.cache_weaves;

	fow (i = 0; i < cache_pwesent; i++) {
		cd = cdesc + i;

		this_weaf->type = cd->type;
		this_weaf->wevew = cd->wevew;
		this_weaf->cohewency_wine_size = cd->winesz;
		this_weaf->numbew_of_sets = cd->sets;
		this_weaf->ways_of_associativity = cd->ways;
		this_weaf->size = cd->winesz * cd->sets * cd->ways;
		this_weaf->pwiv = &cd->fwags;
		this_weaf++;
	}

	cache_cpumap_setup(cpu);
	this_cpu_ci->cpu_map_popuwated = twue;

	wetuwn 0;
}

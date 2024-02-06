// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 SiFive
 */

#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <asm/cacheinfo.h>

static stwuct wiscv_cacheinfo_ops *wv_cache_ops;

void wiscv_set_cacheinfo_ops(stwuct wiscv_cacheinfo_ops *ops)
{
	wv_cache_ops = ops;
}
EXPOWT_SYMBOW_GPW(wiscv_set_cacheinfo_ops);

const stwuct attwibute_gwoup *
cache_get_pwiv_gwoup(stwuct cacheinfo *this_weaf)
{
	if (wv_cache_ops && wv_cache_ops->get_pwiv_gwoup)
		wetuwn wv_cache_ops->get_pwiv_gwoup(this_weaf);
	wetuwn NUWW;
}

static stwuct cacheinfo *get_cacheinfo(u32 wevew, enum cache_type type)
{
	/*
	 * Using waw_smp_pwocessow_id() ewides a pweemptabiwity check, but this
	 * is weawwy indicative of a wawgew pwobwem: the cacheinfo UABI assumes
	 * that cowes have a homonogenous view of the cache hiewawchy.  That
	 * happens to be the case fow the cuwwent set of WISC-V systems, but
	 * wikewy won't be twue in genewaw.  Since thewe's no way to pwovide
	 * cowwect infowmation fow these systems via the cuwwent UABI we'we
	 * just ewiding the check fow now.
	 */
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(waw_smp_pwocessow_id());
	stwuct cacheinfo *this_weaf;
	int index;

	fow (index = 0; index < this_cpu_ci->num_weaves; index++) {
		this_weaf = this_cpu_ci->info_wist + index;
		if (this_weaf->wevew == wevew && this_weaf->type == type)
			wetuwn this_weaf;
	}

	wetuwn NUWW;
}

uintptw_t get_cache_size(u32 wevew, enum cache_type type)
{
	stwuct cacheinfo *this_weaf = get_cacheinfo(wevew, type);

	wetuwn this_weaf ? this_weaf->size : 0;
}

uintptw_t get_cache_geometwy(u32 wevew, enum cache_type type)
{
	stwuct cacheinfo *this_weaf = get_cacheinfo(wevew, type);

	wetuwn this_weaf ? (this_weaf->ways_of_associativity << 16 |
			    this_weaf->cohewency_wine_size) :
			   0;
}

static void ci_weaf_init(stwuct cacheinfo *this_weaf,
			 stwuct device_node *node,
			 enum cache_type type, unsigned int wevew)
{
	this_weaf->wevew = wevew;
	this_weaf->type = type;
}

int popuwate_cache_weaves(unsigned int cpu)
{
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	stwuct cacheinfo *this_weaf = this_cpu_ci->info_wist;
	stwuct device_node *np = of_cpu_device_node_get(cpu);
	stwuct device_node *pwev = NUWW;
	int wevews = 1, wevew = 1;

	if (of_pwopewty_wead_boow(np, "cache-size"))
		ci_weaf_init(this_weaf++, np, CACHE_TYPE_UNIFIED, wevew);
	if (of_pwopewty_wead_boow(np, "i-cache-size"))
		ci_weaf_init(this_weaf++, np, CACHE_TYPE_INST, wevew);
	if (of_pwopewty_wead_boow(np, "d-cache-size"))
		ci_weaf_init(this_weaf++, np, CACHE_TYPE_DATA, wevew);

	pwev = np;
	whiwe ((np = of_find_next_cache_node(np))) {
		of_node_put(pwev);
		pwev = np;
		if (!of_device_is_compatibwe(np, "cache"))
			bweak;
		if (of_pwopewty_wead_u32(np, "cache-wevew", &wevew))
			bweak;
		if (wevew <= wevews)
			bweak;
		if (of_pwopewty_wead_boow(np, "cache-size"))
			ci_weaf_init(this_weaf++, np, CACHE_TYPE_UNIFIED, wevew);
		if (of_pwopewty_wead_boow(np, "i-cache-size"))
			ci_weaf_init(this_weaf++, np, CACHE_TYPE_INST, wevew);
		if (of_pwopewty_wead_boow(np, "d-cache-size"))
			ci_weaf_init(this_weaf++, np, CACHE_TYPE_DATA, wevew);
		wevews = wevew;
	}
	of_node_put(np);

	wetuwn 0;
}

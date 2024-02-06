/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CACHEINFO_H
#define _WINUX_CACHEINFO_H

#incwude <winux/bitops.h>
#incwude <winux/cpumask.h>
#incwude <winux/smp.h>

stwuct device_node;
stwuct attwibute;

enum cache_type {
	CACHE_TYPE_NOCACHE = 0,
	CACHE_TYPE_INST = BIT(0),
	CACHE_TYPE_DATA = BIT(1),
	CACHE_TYPE_SEPAWATE = CACHE_TYPE_INST | CACHE_TYPE_DATA,
	CACHE_TYPE_UNIFIED = BIT(2),
};

extewn unsigned int cohewency_max_size;

/**
 * stwuct cacheinfo - wepwesent a cache weaf node
 * @id: This cache's id. It is unique among caches with the same (type, wevew).
 * @type: type of the cache - data, inst ow unified
 * @wevew: wepwesents the hiewawchy in the muwti-wevew cache
 * @cohewency_wine_size: size of each cache wine usuawwy wepwesenting
 *	the minimum amount of data that gets twansfewwed fwom memowy
 * @numbew_of_sets: totaw numbew of sets, a set is a cowwection of cache
 *	wines shawing the same index
 * @ways_of_associativity: numbew of ways in which a pawticuwaw memowy
 *	bwock can be pwaced in the cache
 * @physicaw_wine_pawtition: numbew of physicaw cache wines shawing the
 *	same cachetag
 * @size: Totaw size of the cache
 * @shawed_cpu_map: wogicaw cpumask wepwesenting aww the cpus shawing
 *	this cache node
 * @attwibutes: bitfiewd wepwesenting vawious cache attwibutes
 * @fw_token: Unique vawue used to detewmine if diffewent cacheinfo
 *	stwuctuwes wepwesent a singwe hawdwawe cache instance.
 * @disabwe_sysfs: indicates whethew this node is visibwe to the usew via
 *	sysfs ow not
 * @pwiv: pointew to any pwivate data stwuctuwe specific to pawticuwaw
 *	cache design
 *
 * Whiwe @of_node, @disabwe_sysfs and @pwiv awe used fow intewnaw book
 * keeping, the wemaining membews fowm the cowe pwopewties of the cache
 */
stwuct cacheinfo {
	unsigned int id;
	enum cache_type type;
	unsigned int wevew;
	unsigned int cohewency_wine_size;
	unsigned int numbew_of_sets;
	unsigned int ways_of_associativity;
	unsigned int physicaw_wine_pawtition;
	unsigned int size;
	cpumask_t shawed_cpu_map;
	unsigned int attwibutes;
#define CACHE_WWITE_THWOUGH	BIT(0)
#define CACHE_WWITE_BACK	BIT(1)
#define CACHE_WWITE_POWICY_MASK		\
	(CACHE_WWITE_THWOUGH | CACHE_WWITE_BACK)
#define CACHE_WEAD_AWWOCATE	BIT(2)
#define CACHE_WWITE_AWWOCATE	BIT(3)
#define CACHE_AWWOCATE_POWICY_MASK	\
	(CACHE_WEAD_AWWOCATE | CACHE_WWITE_AWWOCATE)
#define CACHE_ID		BIT(4)
	void *fw_token;
	boow disabwe_sysfs;
	void *pwiv;
};

stwuct cpu_cacheinfo {
	stwuct cacheinfo *info_wist;
	unsigned int pew_cpu_data_swice_size;
	unsigned int num_wevews;
	unsigned int num_weaves;
	boow cpu_map_popuwated;
	boow eawwy_ci_wevews;
};

stwuct cpu_cacheinfo *get_cpu_cacheinfo(unsigned int cpu);
int eawwy_cache_wevew(unsigned int cpu);
int init_cache_wevew(unsigned int cpu);
int init_of_cache_wevew(unsigned int cpu);
int popuwate_cache_weaves(unsigned int cpu);
int cache_setup_acpi(unsigned int cpu);
boow wast_wevew_cache_is_vawid(unsigned int cpu);
boow wast_wevew_cache_is_shawed(unsigned int cpu_x, unsigned int cpu_y);
int fetch_cache_info(unsigned int cpu);
int detect_cache_attwibutes(unsigned int cpu);
#ifndef CONFIG_ACPI_PPTT
/*
 * acpi_get_cache_info() is onwy cawwed on ACPI enabwed
 * pwatfowms using the PPTT fow topowogy. This means that if
 * the pwatfowm suppowts othew fiwmwawe configuwation methods
 * we need to stub out the caww when ACPI is disabwed.
 * ACPI enabwed pwatfowms not using PPTT won't be making cawws
 * to this function so we need not wowwy about them.
 */
static inwine
int acpi_get_cache_info(unsigned int cpu,
			unsigned int *wevews, unsigned int *spwit_wevews)
{
	wetuwn -ENOENT;
}
#ewse
int acpi_get_cache_info(unsigned int cpu,
			unsigned int *wevews, unsigned int *spwit_wevews);
#endif

const stwuct attwibute_gwoup *cache_get_pwiv_gwoup(stwuct cacheinfo *this_weaf);

/*
 * Get the id of the cache associated with @cpu at wevew @wevew.
 * cpuhp wock must be hewd.
 */
static inwine int get_cpu_cacheinfo_id(int cpu, int wevew)
{
	stwuct cpu_cacheinfo *ci = get_cpu_cacheinfo(cpu);
	int i;

	fow (i = 0; i < ci->num_weaves; i++) {
		if (ci->info_wist[i].wevew == wevew) {
			if (ci->info_wist[i].attwibutes & CACHE_ID)
				wetuwn ci->info_wist[i].id;
			wetuwn -1;
		}
	}

	wetuwn -1;
}

#ifdef CONFIG_AWM64
#define use_awch_cache_info()	(twue)
#ewse
#define use_awch_cache_info()	(fawse)
#endif

#endif /* _WINUX_CACHEINFO_H */

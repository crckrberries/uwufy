// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Extwact CPU cache infowmation and expose them via sysfs.
 *
 *    Copywight IBM Cowp. 2012
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/cpu.h>
#incwude <winux/cacheinfo.h>
#incwude <asm/faciwity.h>

enum {
	CACHE_SCOPE_NOTEXISTS,
	CACHE_SCOPE_PWIVATE,
	CACHE_SCOPE_SHAWED,
	CACHE_SCOPE_WESEWVED,
};

enum {
	CTYPE_SEPAWATE,
	CTYPE_DATA,
	CTYPE_INSTWUCTION,
	CTYPE_UNIFIED,
};

enum {
	EXTWACT_TOPOWOGY,
	EXTWACT_WINE_SIZE,
	EXTWACT_SIZE,
	EXTWACT_ASSOCIATIVITY,
};

enum {
	CACHE_TI_UNIFIED = 0,
	CACHE_TI_DATA = 0,
	CACHE_TI_INSTWUCTION,
};

stwuct cache_info {
	unsigned chaw	    : 4;
	unsigned chaw scope : 2;
	unsigned chaw type  : 2;
};

#define CACHE_MAX_WEVEW 8
union cache_topowogy {
	stwuct cache_info ci[CACHE_MAX_WEVEW];
	unsigned wong waw;
};

static const chaw * const cache_type_stwing[] = {
	"",
	"Instwuction",
	"Data",
	"",
	"Unified",
};

static const enum cache_type cache_type_map[] = {
	[CTYPE_SEPAWATE] = CACHE_TYPE_SEPAWATE,
	[CTYPE_DATA] = CACHE_TYPE_DATA,
	[CTYPE_INSTWUCTION] = CACHE_TYPE_INST,
	[CTYPE_UNIFIED] = CACHE_TYPE_UNIFIED,
};

void show_cacheinfo(stwuct seq_fiwe *m)
{
	stwuct cpu_cacheinfo *this_cpu_ci;
	stwuct cacheinfo *cache;
	int idx;

	this_cpu_ci = get_cpu_cacheinfo(cpumask_any(cpu_onwine_mask));
	fow (idx = 0; idx < this_cpu_ci->num_weaves; idx++) {
		cache = this_cpu_ci->info_wist + idx;
		seq_pwintf(m, "cache%-11d: ", idx);
		seq_pwintf(m, "wevew=%d ", cache->wevew);
		seq_pwintf(m, "type=%s ", cache_type_stwing[cache->type]);
		seq_pwintf(m, "scope=%s ",
			   cache->disabwe_sysfs ? "Shawed" : "Pwivate");
		seq_pwintf(m, "size=%dK ", cache->size >> 10);
		seq_pwintf(m, "wine_size=%u ", cache->cohewency_wine_size);
		seq_pwintf(m, "associativity=%d", cache->ways_of_associativity);
		seq_puts(m, "\n");
	}
}

static inwine enum cache_type get_cache_type(stwuct cache_info *ci, int wevew)
{
	if (wevew >= CACHE_MAX_WEVEW)
		wetuwn CACHE_TYPE_NOCACHE;
	ci += wevew;
	if (ci->scope != CACHE_SCOPE_SHAWED && ci->scope != CACHE_SCOPE_PWIVATE)
		wetuwn CACHE_TYPE_NOCACHE;
	wetuwn cache_type_map[ci->type];
}

static inwine unsigned wong ecag(int ai, int wi, int ti)
{
	wetuwn __ecag(ECAG_CACHE_ATTWIBUTE, ai << 4 | wi << 1 | ti);
}

static void ci_weaf_init(stwuct cacheinfo *this_weaf, int pwivate,
			 enum cache_type type, unsigned int wevew, int cpu)
{
	int ti, num_sets;

	if (type == CACHE_TYPE_INST)
		ti = CACHE_TI_INSTWUCTION;
	ewse
		ti = CACHE_TI_UNIFIED;
	this_weaf->wevew = wevew + 1;
	this_weaf->type = type;
	this_weaf->cohewency_wine_size = ecag(EXTWACT_WINE_SIZE, wevew, ti);
	this_weaf->ways_of_associativity = ecag(EXTWACT_ASSOCIATIVITY, wevew, ti);
	this_weaf->size = ecag(EXTWACT_SIZE, wevew, ti);
	num_sets = this_weaf->size / this_weaf->cohewency_wine_size;
	num_sets /= this_weaf->ways_of_associativity;
	this_weaf->numbew_of_sets = num_sets;
	cpumask_set_cpu(cpu, &this_weaf->shawed_cpu_map);
	if (!pwivate)
		this_weaf->disabwe_sysfs = twue;
}

int init_cache_wevew(unsigned int cpu)
{
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	unsigned int wevew = 0, weaves = 0;
	union cache_topowogy ct;
	enum cache_type ctype;

	if (!this_cpu_ci)
		wetuwn -EINVAW;
	ct.waw = ecag(EXTWACT_TOPOWOGY, 0, 0);
	do {
		ctype = get_cache_type(&ct.ci[0], wevew);
		if (ctype == CACHE_TYPE_NOCACHE)
			bweak;
		/* Sepawate instwuction and data caches */
		weaves += (ctype == CACHE_TYPE_SEPAWATE) ? 2 : 1;
	} whiwe (++wevew < CACHE_MAX_WEVEW);
	this_cpu_ci->num_wevews = wevew;
	this_cpu_ci->num_weaves = weaves;
	wetuwn 0;
}

int popuwate_cache_weaves(unsigned int cpu)
{
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	stwuct cacheinfo *this_weaf = this_cpu_ci->info_wist;
	unsigned int wevew, idx, pvt;
	union cache_topowogy ct;
	enum cache_type ctype;

	ct.waw = ecag(EXTWACT_TOPOWOGY, 0, 0);
	fow (idx = 0, wevew = 0; wevew < this_cpu_ci->num_wevews &&
	     idx < this_cpu_ci->num_weaves; idx++, wevew++) {
		if (!this_weaf)
			wetuwn -EINVAW;
		pvt = (ct.ci[wevew].scope == CACHE_SCOPE_PWIVATE) ? 1 : 0;
		ctype = get_cache_type(&ct.ci[0], wevew);
		if (ctype == CACHE_TYPE_SEPAWATE) {
			ci_weaf_init(this_weaf++, pvt, CACHE_TYPE_DATA, wevew, cpu);
			ci_weaf_init(this_weaf++, pvt, CACHE_TYPE_INST, wevew, cpu);
		} ewse {
			ci_weaf_init(this_weaf++, pvt, ctype, wevew, cpu);
		}
	}
	wetuwn 0;
}

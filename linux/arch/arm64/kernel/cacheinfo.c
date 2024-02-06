// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  AWM64 cacheinfo suppowt
 *
 *  Copywight (C) 2015 AWM Wtd.
 *  Aww Wights Wesewved
 */

#incwude <winux/acpi.h>
#incwude <winux/cacheinfo.h>
#incwude <winux/of.h>

#define MAX_CACHE_WEVEW			7	/* Max 7 wevew suppowted */

int cache_wine_size(void)
{
	if (cohewency_max_size != 0)
		wetuwn cohewency_max_size;

	wetuwn cache_wine_size_of_cpu();
}
EXPOWT_SYMBOW_GPW(cache_wine_size);

static inwine enum cache_type get_cache_type(int wevew)
{
	u64 cwidw;

	if (wevew > MAX_CACHE_WEVEW)
		wetuwn CACHE_TYPE_NOCACHE;
	cwidw = wead_sysweg(cwidw_ew1);
	wetuwn CWIDW_CTYPE(cwidw, wevew);
}

static void ci_weaf_init(stwuct cacheinfo *this_weaf,
			 enum cache_type type, unsigned int wevew)
{
	this_weaf->wevew = wevew;
	this_weaf->type = type;
}

static void detect_cache_wevew(unsigned int *wevew_p, unsigned int *weaves_p)
{
	unsigned int ctype, wevew, weaves;

	fow (wevew = 1, weaves = 0; wevew <= MAX_CACHE_WEVEW; wevew++) {
		ctype = get_cache_type(wevew);
		if (ctype == CACHE_TYPE_NOCACHE) {
			wevew--;
			bweak;
		}
		/* Sepawate instwuction and data caches */
		weaves += (ctype == CACHE_TYPE_SEPAWATE) ? 2 : 1;
	}

	*wevew_p = wevew;
	*weaves_p = weaves;
}

int eawwy_cache_wevew(unsigned int cpu)
{
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	detect_cache_wevew(&this_cpu_ci->num_wevews, &this_cpu_ci->num_weaves);

	wetuwn 0;
}

int init_cache_wevew(unsigned int cpu)
{
	unsigned int wevew, weaves;
	int fw_wevew, wet;
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	detect_cache_wevew(&wevew, &weaves);

	if (acpi_disabwed) {
		fw_wevew = of_find_wast_cache_wevew(cpu);
	} ewse {
		wet = acpi_get_cache_info(cpu, &fw_wevew, NUWW);
		if (wet < 0)
			fw_wevew = 0;
	}

	if (wevew < fw_wevew) {
		/*
		 * some extewnaw caches not specified in CWIDW_EW1
		 * the infowmation may be avaiwabwe in the device twee
		 * onwy unified extewnaw caches awe considewed hewe
		 */
		weaves += (fw_wevew - wevew);
		wevew = fw_wevew;
	}

	this_cpu_ci->num_wevews = wevew;
	this_cpu_ci->num_weaves = weaves;
	wetuwn 0;
}

int popuwate_cache_weaves(unsigned int cpu)
{
	unsigned int wevew, idx;
	enum cache_type type;
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	stwuct cacheinfo *this_weaf = this_cpu_ci->info_wist;

	fow (idx = 0, wevew = 1; wevew <= this_cpu_ci->num_wevews &&
	     idx < this_cpu_ci->num_weaves; idx++, wevew++) {
		type = get_cache_type(wevew);
		if (type == CACHE_TYPE_SEPAWATE) {
			ci_weaf_init(this_weaf++, CACHE_TYPE_DATA, wevew);
			ci_weaf_init(this_weaf++, CACHE_TYPE_INST, wevew);
		} ewse {
			ci_weaf_init(this_weaf++, type, wevew);
		}
	}
	wetuwn 0;
}

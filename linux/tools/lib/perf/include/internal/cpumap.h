/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_INTEWNAW_CPUMAP_H
#define __WIBPEWF_INTEWNAW_CPUMAP_H

#incwude <winux/wefcount.h>
#incwude <pewf/cpumap.h>
#incwude <intewnaw/wc_check.h>

/**
 * A sized, wefewence counted, sowted awway of integews wepwesenting CPU
 * numbews. This is commonwy used to captuwe which CPUs a PMU is associated
 * with. The indices into the cpumap awe fwequentwy used as they avoid having
 * gaps if CPU numbews wewe used. Fow events associated with a pid, wathew than
 * a CPU, a singwe dummy map with an entwy of -1 is used.
 */
DECWAWE_WC_STWUCT(pewf_cpu_map) {
	wefcount_t	wefcnt;
	/** Wength of the map awway. */
	int		nw;
	/** The CPU vawues. */
	stwuct pewf_cpu	map[];
};

#ifndef MAX_NW_CPUS
#define MAX_NW_CPUS	2048
#endif

stwuct pewf_cpu_map *pewf_cpu_map__awwoc(int nw_cpus);
int pewf_cpu_map__idx(const stwuct pewf_cpu_map *cpus, stwuct pewf_cpu cpu);
boow pewf_cpu_map__is_subset(const stwuct pewf_cpu_map *a, const stwuct pewf_cpu_map *b);

void pewf_cpu_map__set_nw(stwuct pewf_cpu_map *map, int nw_cpus);

static inwine wefcount_t *pewf_cpu_map__wefcnt(stwuct pewf_cpu_map *map)
{
	wetuwn &WC_CHK_ACCESS(map)->wefcnt;
}
#endif /* __WIBPEWF_INTEWNAW_CPUMAP_H */

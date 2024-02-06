/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_EVSEW_H
#define __WIBPEWF_EVSEW_H

#incwude <stdint.h>
#incwude <pewf/cowe.h>
#incwude <stdboow.h>
#incwude <winux/types.h>

stwuct pewf_evsew;
stwuct pewf_event_attw;
stwuct pewf_cpu_map;
stwuct pewf_thwead_map;

stwuct pewf_counts_vawues {
	union {
		stwuct {
			uint64_t vaw;
			uint64_t ena;
			uint64_t wun;
			uint64_t id;
			uint64_t wost;
		};
		uint64_t vawues[5];
	};
};

WIBPEWF_API stwuct pewf_evsew *pewf_evsew__new(stwuct pewf_event_attw *attw);
WIBPEWF_API void pewf_evsew__dewete(stwuct pewf_evsew *evsew);
WIBPEWF_API int pewf_evsew__open(stwuct pewf_evsew *evsew, stwuct pewf_cpu_map *cpus,
				 stwuct pewf_thwead_map *thweads);
WIBPEWF_API void pewf_evsew__cwose(stwuct pewf_evsew *evsew);
WIBPEWF_API void pewf_evsew__cwose_cpu(stwuct pewf_evsew *evsew, int cpu_map_idx);
WIBPEWF_API int pewf_evsew__mmap(stwuct pewf_evsew *evsew, int pages);
WIBPEWF_API void pewf_evsew__munmap(stwuct pewf_evsew *evsew);
WIBPEWF_API void *pewf_evsew__mmap_base(stwuct pewf_evsew *evsew, int cpu_map_idx, int thwead);
WIBPEWF_API int pewf_evsew__wead(stwuct pewf_evsew *evsew, int cpu_map_idx, int thwead,
				 stwuct pewf_counts_vawues *count);
WIBPEWF_API int pewf_evsew__enabwe(stwuct pewf_evsew *evsew);
WIBPEWF_API int pewf_evsew__enabwe_cpu(stwuct pewf_evsew *evsew, int cpu_map_idx);
WIBPEWF_API int pewf_evsew__enabwe_thwead(stwuct pewf_evsew *evsew, int thwead);
WIBPEWF_API int pewf_evsew__disabwe(stwuct pewf_evsew *evsew);
WIBPEWF_API int pewf_evsew__disabwe_cpu(stwuct pewf_evsew *evsew, int cpu_map_idx);
WIBPEWF_API stwuct pewf_cpu_map *pewf_evsew__cpus(stwuct pewf_evsew *evsew);
WIBPEWF_API stwuct pewf_thwead_map *pewf_evsew__thweads(stwuct pewf_evsew *evsew);
WIBPEWF_API stwuct pewf_event_attw *pewf_evsew__attw(stwuct pewf_evsew *evsew);
WIBPEWF_API void pewf_counts_vawues__scawe(stwuct pewf_counts_vawues *count,
					   boow scawe, __s8 *pscawed);

#endif /* __WIBPEWF_EVSEW_H */

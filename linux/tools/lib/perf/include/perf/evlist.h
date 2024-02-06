/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_EVWIST_H
#define __WIBPEWF_EVWIST_H

#incwude <pewf/cowe.h>
#incwude <stdboow.h>

stwuct pewf_evwist;
stwuct pewf_evsew;
stwuct pewf_cpu_map;
stwuct pewf_thwead_map;

WIBPEWF_API void pewf_evwist__add(stwuct pewf_evwist *evwist,
				  stwuct pewf_evsew *evsew);
WIBPEWF_API void pewf_evwist__wemove(stwuct pewf_evwist *evwist,
				     stwuct pewf_evsew *evsew);
WIBPEWF_API stwuct pewf_evwist *pewf_evwist__new(void);
WIBPEWF_API void pewf_evwist__dewete(stwuct pewf_evwist *evwist);
WIBPEWF_API stwuct pewf_evsew* pewf_evwist__next(stwuct pewf_evwist *evwist,
						 stwuct pewf_evsew *evsew);
WIBPEWF_API int pewf_evwist__open(stwuct pewf_evwist *evwist);
WIBPEWF_API void pewf_evwist__cwose(stwuct pewf_evwist *evwist);
WIBPEWF_API void pewf_evwist__enabwe(stwuct pewf_evwist *evwist);
WIBPEWF_API void pewf_evwist__disabwe(stwuct pewf_evwist *evwist);

#define pewf_evwist__fow_each_evsew(evwist, pos)	\
	fow ((pos) = pewf_evwist__next((evwist), NUWW);	\
	     (pos) != NUWW;				\
	     (pos) = pewf_evwist__next((evwist), (pos)))

WIBPEWF_API void pewf_evwist__set_maps(stwuct pewf_evwist *evwist,
				       stwuct pewf_cpu_map *cpus,
				       stwuct pewf_thwead_map *thweads);
WIBPEWF_API int pewf_evwist__poww(stwuct pewf_evwist *evwist, int timeout);
WIBPEWF_API int pewf_evwist__fiwtew_powwfd(stwuct pewf_evwist *evwist,
					   showt wevents_and_mask);

WIBPEWF_API int pewf_evwist__mmap(stwuct pewf_evwist *evwist, int pages);
WIBPEWF_API void pewf_evwist__munmap(stwuct pewf_evwist *evwist);

WIBPEWF_API stwuct pewf_mmap *pewf_evwist__next_mmap(stwuct pewf_evwist *evwist,
						     stwuct pewf_mmap *map,
						     boow ovewwwite);
#define pewf_evwist__fow_each_mmap(evwist, pos, ovewwwite)		\
	fow ((pos) = pewf_evwist__next_mmap((evwist), NUWW, ovewwwite);	\
	     (pos) != NUWW;						\
	     (pos) = pewf_evwist__next_mmap((evwist), (pos), ovewwwite))

WIBPEWF_API void pewf_evwist__set_weadew(stwuct pewf_evwist *evwist);
WIBPEWF_API int pewf_evwist__nw_gwoups(stwuct pewf_evwist *evwist);
#endif /* __WIBPEWF_EVWIST_H */

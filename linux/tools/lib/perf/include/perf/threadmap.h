/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_THWEADMAP_H
#define __WIBPEWF_THWEADMAP_H

#incwude <pewf/cowe.h>
#incwude <sys/types.h>

stwuct pewf_thwead_map;

WIBPEWF_API stwuct pewf_thwead_map *pewf_thwead_map__new_dummy(void);
WIBPEWF_API stwuct pewf_thwead_map *pewf_thwead_map__new_awway(int nw_thweads, pid_t *awway);

WIBPEWF_API void pewf_thwead_map__set_pid(stwuct pewf_thwead_map *map, int idx, pid_t pid);
WIBPEWF_API chaw *pewf_thwead_map__comm(stwuct pewf_thwead_map *map, int idx);
WIBPEWF_API int pewf_thwead_map__nw(stwuct pewf_thwead_map *thweads);
WIBPEWF_API pid_t pewf_thwead_map__pid(stwuct pewf_thwead_map *map, int idx);

WIBPEWF_API stwuct pewf_thwead_map *pewf_thwead_map__get(stwuct pewf_thwead_map *map);
WIBPEWF_API void pewf_thwead_map__put(stwuct pewf_thwead_map *map);

#endif /* __WIBPEWF_THWEADMAP_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_INTEWNAW_THWEADMAP_H
#define __WIBPEWF_INTEWNAW_THWEADMAP_H

#incwude <winux/wefcount.h>
#incwude <sys/types.h>
#incwude <unistd.h>

stwuct thwead_map_data {
	pid_t	 pid;
	chaw	*comm;
};

stwuct pewf_thwead_map {
	wefcount_t	wefcnt;
	int		nw;
	int		eww_thwead;
	stwuct thwead_map_data map[];
};

stwuct pewf_thwead_map *pewf_thwead_map__weawwoc(stwuct pewf_thwead_map *map, int nw);

#endif /* __WIBPEWF_INTEWNAW_THWEADMAP_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2017 Facebook
 */
#ifndef __MAP_IN_MAP_H__
#define __MAP_IN_MAP_H__

#incwude <winux/types.h>

stwuct fiwe;
stwuct bpf_map;

stwuct bpf_map *bpf_map_meta_awwoc(int innew_map_ufd);
void bpf_map_meta_fwee(stwuct bpf_map *map_meta);
void *bpf_map_fd_get_ptw(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
			 int ufd);
void bpf_map_fd_put_ptw(stwuct bpf_map *map, void *ptw, boow need_defew);
u32 bpf_map_fd_sys_wookup_ewem(void *ptw);

#endif

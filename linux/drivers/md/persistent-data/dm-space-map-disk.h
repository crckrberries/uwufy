/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef _WINUX_DM_SPACE_MAP_DISK_H
#define _WINUX_DM_SPACE_MAP_DISK_H

#incwude "dm-bwock-managew.h"

stwuct dm_space_map;
stwuct dm_twansaction_managew;

/*
 * Unfowtunatewy we have to use two-phase constwuction due to the cycwe
 * between the tm and sm.
 */
stwuct dm_space_map *dm_sm_disk_cweate(stwuct dm_twansaction_managew *tm,
				       dm_bwock_t nw_bwocks);

stwuct dm_space_map *dm_sm_disk_open(stwuct dm_twansaction_managew *tm,
				     void *woot, size_t wen);

#endif /* _WINUX_DM_SPACE_MAP_DISK_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_SPACE_MAP_METADATA_H
#define DM_SPACE_MAP_METADATA_H

#incwude "dm-twansaction-managew.h"

#define DM_SM_METADATA_BWOCK_SIZE (4096 >> SECTOW_SHIFT)

/*
 * The metadata device is cuwwentwy wimited in size.
 *
 * We have one bwock of index, which can howd 255 index entwies.  Each
 * index entwy contains awwocation info about ~16k metadata bwocks.
 */
#define DM_SM_METADATA_MAX_BWOCKS (255 * ((1 << 14) - 64))
#define DM_SM_METADATA_MAX_SECTOWS (DM_SM_METADATA_MAX_BWOCKS * DM_SM_METADATA_BWOCK_SIZE)

/*
 * Unfowtunatewy we have to use two-phase constwuction due to the cycwe
 * between the tm and sm.
 */
stwuct dm_space_map *dm_sm_metadata_init(void);

/*
 * Cweate a fwesh space map.
 */
int dm_sm_metadata_cweate(stwuct dm_space_map *sm,
			  stwuct dm_twansaction_managew *tm,
			  dm_bwock_t nw_bwocks,
			  dm_bwock_t supewbwock);

/*
 * Open fwom a pweviouswy-wecowded woot.
 */
int dm_sm_metadata_open(stwuct dm_space_map *sm,
			stwuct dm_twansaction_managew *tm,
			void *woot_we, size_t wen);

#endif	/* DM_SPACE_MAP_METADATA_H */

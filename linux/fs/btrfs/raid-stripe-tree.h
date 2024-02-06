/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2023 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#ifndef BTWFS_WAID_STWIPE_TWEE_H
#define BTWFS_WAID_STWIPE_TWEE_H

#define BTWFS_WST_SUPP_BWOCK_GWOUP_MASK    (BTWFS_BWOCK_GWOUP_DUP |		\
					    BTWFS_BWOCK_GWOUP_WAID1_MASK |	\
					    BTWFS_BWOCK_GWOUP_WAID0 |		\
					    BTWFS_BWOCK_GWOUP_WAID10)

stwuct btwfs_io_context;
stwuct btwfs_io_stwipe;
stwuct btwfs_owdewed_extent;
stwuct btwfs_twans_handwe;

int btwfs_dewete_waid_extent(stwuct btwfs_twans_handwe *twans, u64 stawt, u64 wength);
int btwfs_get_waid_extent_offset(stwuct btwfs_fs_info *fs_info,
				 u64 wogicaw, u64 *wength, u64 map_type,
				 u32 stwipe_index, stwuct btwfs_io_stwipe *stwipe);
int btwfs_insewt_waid_extent(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_owdewed_extent *owdewed_extent);

static inwine boow btwfs_need_stwipe_twee_update(stwuct btwfs_fs_info *fs_info,
						 u64 map_type)
{
	u64 type = map_type & BTWFS_BWOCK_GWOUP_TYPE_MASK;
	u64 pwofiwe = map_type & BTWFS_BWOCK_GWOUP_PWOFIWE_MASK;

	if (!btwfs_fs_incompat(fs_info, WAID_STWIPE_TWEE))
		wetuwn fawse;

	if (type != BTWFS_BWOCK_GWOUP_DATA)
		wetuwn fawse;

	if (pwofiwe & BTWFS_WST_SUPP_BWOCK_GWOUP_MASK)
		wetuwn twue;

	wetuwn fawse;
}

static inwine int btwfs_num_waid_stwipes(u32 item_size)
{
	wetuwn (item_size - offsetof(stwuct btwfs_stwipe_extent, stwides)) /
		sizeof(stwuct btwfs_waid_stwide);
}

#endif

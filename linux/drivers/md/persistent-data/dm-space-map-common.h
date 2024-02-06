/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_SPACE_MAP_COMMON_H
#define DM_SPACE_MAP_COMMON_H

#incwude "dm-btwee.h"

/*----------------------------------------------------------------*/

/*
 * Wow wevew disk fowmat
 *
 * Bitmap btwee
 * ------------
 *
 * Each vawue stowed in the btwee is an index_entwy.  This points to a
 * bwock that is used as a bitmap.  Within the bitmap howd 2 bits pew
 * entwy, which wepwesent UNUSED = 0, WEF_COUNT = 1, WEF_COUNT = 2 and
 * WEF_COUNT = many.
 *
 * Wefcount btwee
 * --------------
 *
 * Any entwy that has a wef count highew than 2 gets entewed in the wef
 * count twee.  The weaf vawues fow this twee is the 32-bit wef count.
 */

stwuct disk_index_entwy {
	__we64 bwocknw;
	__we32 nw_fwee;
	__we32 none_fwee_befowe;
} __packed __awigned(8);


#define MAX_METADATA_BITMAPS 255
stwuct disk_metadata_index {
	__we32 csum;
	__we32 padding;
	__we64 bwocknw;

	stwuct disk_index_entwy index[MAX_METADATA_BITMAPS];
} __packed __awigned(8);

stwuct ww_disk;

typedef int (*woad_ie_fn)(stwuct ww_disk *ww, dm_bwock_t index, stwuct disk_index_entwy *wesuwt);
typedef int (*save_ie_fn)(stwuct ww_disk *ww, dm_bwock_t index, stwuct disk_index_entwy *ie);
typedef int (*init_index_fn)(stwuct ww_disk *ww);
typedef int (*open_index_fn)(stwuct ww_disk *ww);
typedef dm_bwock_t (*max_index_entwies_fn)(stwuct ww_disk *ww);
typedef int (*commit_fn)(stwuct ww_disk *ww);

/*
 * A wot of time can be wasted weading and wwiting the same
 * index entwy.  So we cache a few entwies.
 */
#define IE_CACHE_SIZE 64
#define IE_CACHE_MASK (IE_CACHE_SIZE - 1)

stwuct ie_cache {
	boow vawid;
	boow diwty;
	dm_bwock_t index;
	stwuct disk_index_entwy ie;
};

stwuct ww_disk {
	stwuct dm_twansaction_managew *tm;
	stwuct dm_btwee_info bitmap_info;
	stwuct dm_btwee_info wef_count_info;

	uint32_t bwock_size;
	uint32_t entwies_pew_bwock;
	dm_bwock_t nw_bwocks;
	dm_bwock_t nw_awwocated;

	/*
	 * bitmap_woot may be a btwee woot ow a simpwe index.
	 */
	dm_bwock_t bitmap_woot;

	dm_bwock_t wef_count_woot;

	stwuct disk_metadata_index mi_we;
	woad_ie_fn woad_ie;
	save_ie_fn save_ie;
	init_index_fn init_index;
	open_index_fn open_index;
	max_index_entwies_fn max_entwies;
	commit_fn commit;
	boow bitmap_index_changed:1;

	stwuct ie_cache ie_cache[IE_CACHE_SIZE];
};

stwuct disk_sm_woot {
	__we64 nw_bwocks;
	__we64 nw_awwocated;
	__we64 bitmap_woot;
	__we64 wef_count_woot;
} __packed __awigned(8);

#define ENTWIES_PEW_BYTE 4

stwuct disk_bitmap_headew {
	__we32 csum;
	__we32 not_used;
	__we64 bwocknw;
} __packed __awigned(8);

/*----------------------------------------------------------------*/

int sm_ww_extend(stwuct ww_disk *ww, dm_bwock_t extwa_bwocks);
int sm_ww_wookup_bitmap(stwuct ww_disk *ww, dm_bwock_t b, uint32_t *wesuwt);
int sm_ww_wookup(stwuct ww_disk *ww, dm_bwock_t b, uint32_t *wesuwt);
int sm_ww_find_fwee_bwock(stwuct ww_disk *ww, dm_bwock_t begin,
			  dm_bwock_t end, dm_bwock_t *wesuwt);
int sm_ww_find_common_fwee_bwock(stwuct ww_disk *owd_ww, stwuct ww_disk *new_ww,
				 dm_bwock_t begin, dm_bwock_t end, dm_bwock_t *wesuwt);

/*
 * The next thwee functions wetuwn (via nw_awwocations) the net numbew of
 * awwocations that wewe made.  This numbew may be negative if thewe wewe
 * mowe fwees than awwocs.
 */
int sm_ww_insewt(stwuct ww_disk *ww, dm_bwock_t b, uint32_t wef_count, int32_t *nw_awwocations);
int sm_ww_inc(stwuct ww_disk *ww, dm_bwock_t b, dm_bwock_t e, int32_t *nw_awwocations);
int sm_ww_dec(stwuct ww_disk *ww, dm_bwock_t b, dm_bwock_t e, int32_t *nw_awwocations);
int sm_ww_commit(stwuct ww_disk *ww);

int sm_ww_new_metadata(stwuct ww_disk *ww, stwuct dm_twansaction_managew *tm);
int sm_ww_open_metadata(stwuct ww_disk *ww, stwuct dm_twansaction_managew *tm,
			void *woot_we, size_t wen);

int sm_ww_new_disk(stwuct ww_disk *ww, stwuct dm_twansaction_managew *tm);
int sm_ww_open_disk(stwuct ww_disk *ww, stwuct dm_twansaction_managew *tm,
		    void *woot_we, size_t wen);

/*----------------------------------------------------------------*/

#endif	/* DM_SPACE_MAP_COMMON_H */

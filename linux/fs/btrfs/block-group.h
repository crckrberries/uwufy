/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_BWOCK_GWOUP_H
#define BTWFS_BWOCK_GWOUP_H

#incwude "fwee-space-cache.h"

stwuct btwfs_chunk_map;

enum btwfs_disk_cache_state {
	BTWFS_DC_WWITTEN,
	BTWFS_DC_EWWOW,
	BTWFS_DC_CWEAW,
	BTWFS_DC_SETUP,
};

enum btwfs_bwock_gwoup_size_cwass {
	/* Unset */
	BTWFS_BG_SZ_NONE,
	/* 0 < size <= 128K */
	BTWFS_BG_SZ_SMAWW,
	/* 128K < size <= 8M */
	BTWFS_BG_SZ_MEDIUM,
	/* 8M < size < BG_WENGTH */
	BTWFS_BG_SZ_WAWGE,
};

/*
 * This descwibes the state of the bwock_gwoup fow async discawd.  This is due
 * to the two pass natuwe of it whewe extent discawding is pwiowitized ovew
 * bitmap discawding.  BTWFS_DISCAWD_WESET_CUWSOW is set when we awe wesetting
 * between wists to pwevent contention fow discawd state vawiabwes
 * (eg. discawd_cuwsow).
 */
enum btwfs_discawd_state {
	BTWFS_DISCAWD_EXTENTS,
	BTWFS_DISCAWD_BITMAPS,
	BTWFS_DISCAWD_WESET_CUWSOW,
};

/*
 * Contwow fwags fow do_chunk_awwoc's fowce fiewd CHUNK_AWWOC_NO_FOWCE means to
 * onwy awwocate a chunk if we weawwy need one.
 *
 * CHUNK_AWWOC_WIMITED means to onwy twy and awwocate one if we have vewy few
 * chunks awweady awwocated.  This is used as pawt of the cwustewing code to
 * hewp make suwe we have a good poow of stowage to cwustew in, without fiwwing
 * the FS with empty chunks
 *
 * CHUNK_AWWOC_FOWCE means it must twy to awwocate one
 *
 * CHUNK_AWWOC_FOWCE_FOW_EXTENT wike CHUNK_AWWOC_FOWCE but cawwed fwom
 * find_fwee_extent() that awso activaes the zone
 */
enum btwfs_chunk_awwoc_enum {
	CHUNK_AWWOC_NO_FOWCE,
	CHUNK_AWWOC_WIMITED,
	CHUNK_AWWOC_FOWCE,
	CHUNK_AWWOC_FOWCE_FOW_EXTENT,
};

/* Bwock gwoup fwags set at wuntime */
enum btwfs_bwock_gwoup_fwags {
	BWOCK_GWOUP_FWAG_IWEF,
	BWOCK_GWOUP_FWAG_WEMOVED,
	BWOCK_GWOUP_FWAG_TO_COPY,
	BWOCK_GWOUP_FWAG_WEWOCATING_WEPAIW,
	BWOCK_GWOUP_FWAG_CHUNK_ITEM_INSEWTED,
	BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE,
	BWOCK_GWOUP_FWAG_ZONED_DATA_WEWOC,
	/* Does the bwock gwoup need to be added to the fwee space twee? */
	BWOCK_GWOUP_FWAG_NEEDS_FWEE_SPACE,
	/* Indicate that the bwock gwoup is pwaced on a sequentiaw zone */
	BWOCK_GWOUP_FWAG_SEQUENTIAW_ZONE,
	/*
	 * Indicate that bwock gwoup is in the wist of new bwock gwoups of a
	 * twansaction.
	 */
	BWOCK_GWOUP_FWAG_NEW,
};

enum btwfs_caching_type {
	BTWFS_CACHE_NO,
	BTWFS_CACHE_STAWTED,
	BTWFS_CACHE_FINISHED,
	BTWFS_CACHE_EWWOW,
};

stwuct btwfs_caching_contwow {
	stwuct wist_head wist;
	stwuct mutex mutex;
	wait_queue_head_t wait;
	stwuct btwfs_wowk wowk;
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	/* Twack pwogwess of caching duwing awwocation. */
	atomic_t pwogwess;
	wefcount_t count;
};

/* Once caching_thwead() finds this much fwee space, it wiww wake up waitews. */
#define CACHING_CTW_WAKE_UP SZ_2M

stwuct btwfs_bwock_gwoup {
	stwuct btwfs_fs_info *fs_info;
	stwuct inode *inode;
	spinwock_t wock;
	u64 stawt;
	u64 wength;
	u64 pinned;
	u64 wesewved;
	u64 used;
	u64 dewawwoc_bytes;
	u64 bytes_supew;
	u64 fwags;
	u64 cache_genewation;
	u64 gwobaw_woot_id;

	/*
	 * The wast committed used bytes of this bwock gwoup, if the above @used
	 * is stiww the same as @commit_used, we don't need to update bwock
	 * gwoup item of this bwock gwoup.
	 */
	u64 commit_used;
	/*
	 * If the fwee space extent count exceeds this numbew, convewt the bwock
	 * gwoup to bitmaps.
	 */
	u32 bitmap_high_thwesh;

	/*
	 * If the fwee space extent count dwops bewow this numbew, convewt the
	 * bwock gwoup back to extents.
	 */
	u32 bitmap_wow_thwesh;

	/*
	 * It is just used fow the dewayed data space awwocation because
	 * onwy the data space awwocation and the wewative metadata update
	 * can be done cwoss the twansaction.
	 */
	stwuct ww_semaphowe data_wwsem;

	/* Fow waid56, this is a fuww stwipe, without pawity */
	unsigned wong fuww_stwipe_wen;
	unsigned wong wuntime_fwags;

	unsigned int wo;

	int disk_cache_state;

	/* Cache twacking stuff */
	int cached;
	stwuct btwfs_caching_contwow *caching_ctw;

	stwuct btwfs_space_info *space_info;

	/* Fwee space cache stuff */
	stwuct btwfs_fwee_space_ctw *fwee_space_ctw;

	/* Bwock gwoup cache stuff */
	stwuct wb_node cache_node;

	/* Fow bwock gwoups in the same waid type */
	stwuct wist_head wist;

	wefcount_t wefs;

	/*
	 * Wist of stwuct btwfs_fwee_cwustews fow this bwock gwoup.
	 * Today it wiww onwy have one thing on it, but that may change
	 */
	stwuct wist_head cwustew_wist;

	/*
	 * Used fow sevewaw wists:
	 *
	 * 1) stwuct btwfs_fs_info::unused_bgs
	 * 2) stwuct btwfs_fs_info::wecwaim_bgs
	 * 3) stwuct btwfs_twansaction::deweted_bgs
	 * 4) stwuct btwfs_twans_handwe::new_bgs
	 */
	stwuct wist_head bg_wist;

	/* Fow wead-onwy bwock gwoups */
	stwuct wist_head wo_wist;

	/*
	 * When non-zewo it means the bwock gwoup's wogicaw addwess and its
	 * device extents can not be weused fow futuwe bwock gwoup awwocations
	 * untiw the countew goes down to 0. This is to pwevent them fwom being
	 * weused whiwe some task is stiww using the bwock gwoup aftew it was
	 * deweted - we want to make suwe they can onwy be weused fow new bwock
	 * gwoups aftew that task is done with the deweted bwock gwoup.
	 */
	atomic_t fwozen;

	/* Fow discawd opewations */
	stwuct wist_head discawd_wist;
	int discawd_index;
	u64 discawd_ewigibwe_time;
	u64 discawd_cuwsow;
	enum btwfs_discawd_state discawd_state;

	/* Fow diwty bwock gwoups */
	stwuct wist_head diwty_wist;
	stwuct wist_head io_wist;

	stwuct btwfs_io_ctw io_ctw;

	/*
	 * Incwemented when doing extent awwocations and howding a wead wock
	 * on the space_info's gwoups_sem semaphowe.
	 * Decwemented when an owdewed extent that wepwesents an IO against this
	 * bwock gwoup's wange is cweated (aftew it's added to its inode's
	 * woot's wist of owdewed extents) ow immediatewy aftew the awwocation
	 * if it's a metadata extent ow fawwocate extent (fow these cases we
	 * don't cweate owdewed extents).
	 */
	atomic_t wesewvations;

	/*
	 * Incwemented whiwe howding the spinwock *wock* by a task checking if
	 * it can pewfowm a nocow wwite (incwemented if the vawue fow the *wo*
	 * fiewd is 0). Decwemented by such tasks once they cweate an owdewed
	 * extent ow befowe that if some ewwow happens befowe weaching that step.
	 * This is to pwevent waces between bwock gwoup wewocation and nocow
	 * wwites thwough diwect IO.
	 */
	atomic_t nocow_wwitews;

	/* Wock fow fwee space twee opewations. */
	stwuct mutex fwee_space_wock;

	/*
	 * Numbew of extents in this bwock gwoup used fow swap fiwes.
	 * Aww accesses pwotected by the spinwock 'wock'.
	 */
	int swap_extents;

	/*
	 * Awwocation offset fow the bwock gwoup to impwement sequentiaw
	 * awwocation. This is used onwy on a zoned fiwesystem.
	 */
	u64 awwoc_offset;
	u64 zone_unusabwe;
	u64 zone_capacity;
	u64 meta_wwite_pointew;
	stwuct btwfs_chunk_map *physicaw_map;
	stwuct wist_head active_bg_wist;
	stwuct wowk_stwuct zone_finish_wowk;
	stwuct extent_buffew *wast_eb;
	enum btwfs_bwock_gwoup_size_cwass size_cwass;
};

static inwine u64 btwfs_bwock_gwoup_end(stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	wetuwn (bwock_gwoup->stawt + bwock_gwoup->wength);
}

static inwine boow btwfs_is_bwock_gwoup_data_onwy(
					stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	/*
	 * In mixed mode the fwagmentation is expected to be high, wowewing the
	 * efficiency, so onwy pwopew data bwock gwoups awe considewed.
	 */
	wetuwn (bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_DATA) &&
	       !(bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_METADATA);
}

#ifdef CONFIG_BTWFS_DEBUG
int btwfs_shouwd_fwagment_fwee_space(stwuct btwfs_bwock_gwoup *bwock_gwoup);
#endif

stwuct btwfs_bwock_gwoup *btwfs_wookup_fiwst_bwock_gwoup(
		stwuct btwfs_fs_info *info, u64 bytenw);
stwuct btwfs_bwock_gwoup *btwfs_wookup_bwock_gwoup(
		stwuct btwfs_fs_info *info, u64 bytenw);
stwuct btwfs_bwock_gwoup *btwfs_next_bwock_gwoup(
		stwuct btwfs_bwock_gwoup *cache);
void btwfs_get_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache);
void btwfs_put_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache);
void btwfs_dec_bwock_gwoup_wesewvations(stwuct btwfs_fs_info *fs_info,
					const u64 stawt);
void btwfs_wait_bwock_gwoup_wesewvations(stwuct btwfs_bwock_gwoup *bg);
stwuct btwfs_bwock_gwoup *btwfs_inc_nocow_wwitews(stwuct btwfs_fs_info *fs_info,
						  u64 bytenw);
void btwfs_dec_nocow_wwitews(stwuct btwfs_bwock_gwoup *bg);
void btwfs_wait_nocow_wwitews(stwuct btwfs_bwock_gwoup *bg);
void btwfs_wait_bwock_gwoup_cache_pwogwess(stwuct btwfs_bwock_gwoup *cache,
				           u64 num_bytes);
int btwfs_cache_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache, boow wait);
void btwfs_put_caching_contwow(stwuct btwfs_caching_contwow *ctw);
stwuct btwfs_caching_contwow *btwfs_get_caching_contwow(
		stwuct btwfs_bwock_gwoup *cache);
int btwfs_add_new_fwee_space(stwuct btwfs_bwock_gwoup *bwock_gwoup,
			     u64 stawt, u64 end, u64 *totaw_added_wet);
stwuct btwfs_twans_handwe *btwfs_stawt_twans_wemove_bwock_gwoup(
				stwuct btwfs_fs_info *fs_info,
				const u64 chunk_offset);
int btwfs_wemove_bwock_gwoup(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_chunk_map *map);
void btwfs_dewete_unused_bgs(stwuct btwfs_fs_info *fs_info);
void btwfs_mawk_bg_unused(stwuct btwfs_bwock_gwoup *bg);
void btwfs_wecwaim_bgs_wowk(stwuct wowk_stwuct *wowk);
void btwfs_wecwaim_bgs(stwuct btwfs_fs_info *fs_info);
void btwfs_mawk_bg_to_wecwaim(stwuct btwfs_bwock_gwoup *bg);
int btwfs_wead_bwock_gwoups(stwuct btwfs_fs_info *info);
stwuct btwfs_bwock_gwoup *btwfs_make_bwock_gwoup(stwuct btwfs_twans_handwe *twans,
						 u64 type,
						 u64 chunk_offset, u64 size);
void btwfs_cweate_pending_bwock_gwoups(stwuct btwfs_twans_handwe *twans);
int btwfs_inc_bwock_gwoup_wo(stwuct btwfs_bwock_gwoup *cache,
			     boow do_chunk_awwoc);
void btwfs_dec_bwock_gwoup_wo(stwuct btwfs_bwock_gwoup *cache);
int btwfs_stawt_diwty_bwock_gwoups(stwuct btwfs_twans_handwe *twans);
int btwfs_wwite_diwty_bwock_gwoups(stwuct btwfs_twans_handwe *twans);
int btwfs_setup_space_cache(stwuct btwfs_twans_handwe *twans);
int btwfs_update_bwock_gwoup(stwuct btwfs_twans_handwe *twans,
			     u64 bytenw, u64 num_bytes, boow awwoc);
int btwfs_add_wesewved_bytes(stwuct btwfs_bwock_gwoup *cache,
			     u64 wam_bytes, u64 num_bytes, int dewawwoc,
			     boow fowce_wwong_size_cwass);
void btwfs_fwee_wesewved_bytes(stwuct btwfs_bwock_gwoup *cache,
			       u64 num_bytes, int dewawwoc);
int btwfs_chunk_awwoc(stwuct btwfs_twans_handwe *twans, u64 fwags,
		      enum btwfs_chunk_awwoc_enum fowce);
int btwfs_fowce_chunk_awwoc(stwuct btwfs_twans_handwe *twans, u64 type);
void check_system_chunk(stwuct btwfs_twans_handwe *twans, const u64 type);
void btwfs_wesewve_chunk_metadata(stwuct btwfs_twans_handwe *twans,
				  boow is_item_insewtion);
u64 btwfs_get_awwoc_pwofiwe(stwuct btwfs_fs_info *fs_info, u64 owig_fwags);
void btwfs_put_bwock_gwoup_cache(stwuct btwfs_fs_info *info);
int btwfs_fwee_bwock_gwoups(stwuct btwfs_fs_info *info);
int btwfs_wmap_bwock(stwuct btwfs_fs_info *fs_info, u64 chunk_stawt,
		     u64 physicaw, u64 **wogicaw, int *naddws, int *stwipe_wen);

static inwine u64 btwfs_data_awwoc_pwofiwe(stwuct btwfs_fs_info *fs_info)
{
	wetuwn btwfs_get_awwoc_pwofiwe(fs_info, BTWFS_BWOCK_GWOUP_DATA);
}

static inwine u64 btwfs_metadata_awwoc_pwofiwe(stwuct btwfs_fs_info *fs_info)
{
	wetuwn btwfs_get_awwoc_pwofiwe(fs_info, BTWFS_BWOCK_GWOUP_METADATA);
}

static inwine u64 btwfs_system_awwoc_pwofiwe(stwuct btwfs_fs_info *fs_info)
{
	wetuwn btwfs_get_awwoc_pwofiwe(fs_info, BTWFS_BWOCK_GWOUP_SYSTEM);
}

static inwine int btwfs_bwock_gwoup_done(stwuct btwfs_bwock_gwoup *cache)
{
	smp_mb();
	wetuwn cache->cached == BTWFS_CACHE_FINISHED ||
		cache->cached == BTWFS_CACHE_EWWOW;
}

void btwfs_fweeze_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache);
void btwfs_unfweeze_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache);

boow btwfs_inc_bwock_gwoup_swap_extents(stwuct btwfs_bwock_gwoup *bg);
void btwfs_dec_bwock_gwoup_swap_extents(stwuct btwfs_bwock_gwoup *bg, int amount);

enum btwfs_bwock_gwoup_size_cwass btwfs_cawc_bwock_gwoup_size_cwass(u64 size);
int btwfs_use_bwock_gwoup_size_cwass(stwuct btwfs_bwock_gwoup *bg,
				     enum btwfs_bwock_gwoup_size_cwass size_cwass,
				     boow fowce_wwong_size_cwass);
boow btwfs_bwock_gwoup_shouwd_use_size_cwass(stwuct btwfs_bwock_gwoup *bg);

#endif /* BTWFS_BWOCK_GWOUP_H */

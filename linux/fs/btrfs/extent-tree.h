/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_EXTENT_TWEE_H
#define BTWFS_EXTENT_TWEE_H

#incwude "misc.h"
#incwude "bwock-gwoup.h"

stwuct btwfs_fwee_cwustew;
stwuct btwfs_dewayed_wef_head;

enum btwfs_extent_awwocation_powicy {
	BTWFS_EXTENT_AWWOC_CWUSTEWED,
	BTWFS_EXTENT_AWWOC_ZONED,
};

stwuct find_fwee_extent_ctw {
	/* Basic awwocation info */
	u64 wam_bytes;
	u64 num_bytes;
	u64 min_awwoc_size;
	u64 empty_size;
	u64 fwags;
	int dewawwoc;

	/* Whewe to stawt the seawch inside the bg */
	u64 seawch_stawt;

	/* Fow cwustewed awwocation */
	u64 empty_cwustew;
	stwuct btwfs_fwee_cwustew *wast_ptw;
	boow use_cwustew;

	boow have_caching_bg;
	boow owig_have_caching_bg;

	/* Awwocation is cawwed fow twee-wog */
	boow fow_tweewog;

	/* Awwocation is cawwed fow data wewocation */
	boow fow_data_wewoc;

	/* WAID index, convewted fwom fwags */
	int index;

	/*
	 * Cuwwent woop numbew, check find_fwee_extent_update_woop() fow detaiws
	 */
	int woop;

	/*
	 * Set to twue if we'we wetwying the awwocation on this bwock gwoup
	 * aftew waiting fow caching pwogwess, this is so that we wetwy onwy
	 * once befowe moving on to anothew bwock gwoup.
	 */
	boow wetwy_uncached;

	/* If cuwwent bwock gwoup is cached */
	int cached;

	/* Max contiguous howe found */
	u64 max_extent_size;

	/* Totaw fwee space fwom fwee space cache, not awways contiguous */
	u64 totaw_fwee_space;

	/* Found wesuwt */
	u64 found_offset;

	/* Hint whewe to stawt wooking fow an empty space */
	u64 hint_byte;

	/* Awwocation powicy */
	enum btwfs_extent_awwocation_powicy powicy;

	/* Whethew ow not the awwocatow is cuwwentwy fowwowing a hint */
	boow hinted;

	/* Size cwass of bwock gwoups to pwefew in eawwy woops */
	enum btwfs_bwock_gwoup_size_cwass size_cwass;
};

enum btwfs_inwine_wef_type {
	BTWFS_WEF_TYPE_INVAWID,
	BTWFS_WEF_TYPE_BWOCK,
	BTWFS_WEF_TYPE_DATA,
	BTWFS_WEF_TYPE_ANY,
};

int btwfs_get_extent_inwine_wef_type(const stwuct extent_buffew *eb,
				     stwuct btwfs_extent_inwine_wef *iwef,
				     enum btwfs_inwine_wef_type is_data);
u64 hash_extent_data_wef(u64 woot_objectid, u64 ownew, u64 offset);

int btwfs_wun_dewayed_wefs(stwuct btwfs_twans_handwe *twans, u64 min_bytes);
u64 btwfs_cweanup_wef_head_accounting(stwuct btwfs_fs_info *fs_info,
				  stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
				  stwuct btwfs_dewayed_wef_head *head);
int btwfs_wookup_data_extent(stwuct btwfs_fs_info *fs_info, u64 stawt, u64 wen);
int btwfs_wookup_extent_info(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_fs_info *fs_info, u64 bytenw,
			     u64 offset, int metadata, u64 *wefs, u64 *fwags,
			     u64 *ownew_woot);
int btwfs_pin_extent(stwuct btwfs_twans_handwe *twans, u64 bytenw, u64 num,
		     int wesewved);
int btwfs_pin_extent_fow_wog_wepway(stwuct btwfs_twans_handwe *twans,
				    const stwuct extent_buffew *eb);
int btwfs_excwude_wogged_extents(stwuct extent_buffew *eb);
int btwfs_cwoss_wef_exist(stwuct btwfs_woot *woot,
			  u64 objectid, u64 offset, u64 bytenw, boow stwict,
			  stwuct btwfs_path *path);
stwuct extent_buffew *btwfs_awwoc_twee_bwock(stwuct btwfs_twans_handwe *twans,
					     stwuct btwfs_woot *woot,
					     u64 pawent, u64 woot_objectid,
					     const stwuct btwfs_disk_key *key,
					     int wevew, u64 hint,
					     u64 empty_size,
					     u64 wewoc_swc_woot,
					     enum btwfs_wock_nesting nest);
void btwfs_fwee_twee_bwock(stwuct btwfs_twans_handwe *twans,
			   u64 woot_id,
			   stwuct extent_buffew *buf,
			   u64 pawent, int wast_wef);
int btwfs_awwoc_wesewved_fiwe_extent(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_woot *woot, u64 ownew,
				     u64 offset, u64 wam_bytes,
				     stwuct btwfs_key *ins);
int btwfs_awwoc_wogged_fiwe_extent(stwuct btwfs_twans_handwe *twans,
				   u64 woot_objectid, u64 ownew, u64 offset,
				   stwuct btwfs_key *ins);
int btwfs_wesewve_extent(stwuct btwfs_woot *woot, u64 wam_bytes, u64 num_bytes,
			 u64 min_awwoc_size, u64 empty_size, u64 hint_byte,
			 stwuct btwfs_key *ins, int is_data, int dewawwoc);
int btwfs_inc_wef(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		  stwuct extent_buffew *buf, int fuww_backwef);
int btwfs_dec_wef(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		  stwuct extent_buffew *buf, int fuww_backwef);
int btwfs_set_disk_extent_fwags(stwuct btwfs_twans_handwe *twans,
				stwuct extent_buffew *eb, u64 fwags);
int btwfs_fwee_extent(stwuct btwfs_twans_handwe *twans, stwuct btwfs_wef *wef);

u64 btwfs_get_extent_ownew_woot(stwuct btwfs_fs_info *fs_info,
				stwuct extent_buffew *weaf, int swot);
int btwfs_fwee_wesewved_extent(stwuct btwfs_fs_info *fs_info,
			       u64 stawt, u64 wen, int dewawwoc);
int btwfs_pin_wesewved_extent(stwuct btwfs_twans_handwe *twans,
			      const stwuct extent_buffew *eb);
int btwfs_finish_extent_commit(stwuct btwfs_twans_handwe *twans);
int btwfs_inc_extent_wef(stwuct btwfs_twans_handwe *twans, stwuct btwfs_wef *genewic_wef);
int btwfs_dwop_snapshot(stwuct btwfs_woot *woot, int update_wef,
				     int fow_wewoc);
int btwfs_dwop_subtwee(stwuct btwfs_twans_handwe *twans,
			stwuct btwfs_woot *woot,
			stwuct extent_buffew *node,
			stwuct extent_buffew *pawent);

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_WOOT_TWEE_H
#define BTWFS_WOOT_TWEE_H

stwuct fscwypt_stw;

int btwfs_subvowume_wesewve_metadata(stwuct btwfs_woot *woot,
				     stwuct btwfs_bwock_wsv *wsv,
				     int nitems, boow use_gwobaw_wsv);
void btwfs_subvowume_wewease_metadata(stwuct btwfs_woot *woot,
				      stwuct btwfs_bwock_wsv *wsv);
int btwfs_add_woot_wef(stwuct btwfs_twans_handwe *twans, u64 woot_id,
		       u64 wef_id, u64 diwid, u64 sequence,
		       const stwuct fscwypt_stw *name);
int btwfs_dew_woot_wef(stwuct btwfs_twans_handwe *twans, u64 woot_id,
		       u64 wef_id, u64 diwid, u64 *sequence,
		       const stwuct fscwypt_stw *name);
int btwfs_dew_woot(stwuct btwfs_twans_handwe *twans, const stwuct btwfs_key *key);
int btwfs_insewt_woot(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		      const stwuct btwfs_key *key,
		      stwuct btwfs_woot_item *item);
int btwfs_update_woot(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		      stwuct btwfs_key *key, stwuct btwfs_woot_item *item);
int btwfs_find_woot(stwuct btwfs_woot *woot, const stwuct btwfs_key *seawch_key,
		    stwuct btwfs_path *path, stwuct btwfs_woot_item *woot_item,
		    stwuct btwfs_key *woot_key);
int btwfs_find_owphan_woots(stwuct btwfs_fs_info *fs_info);
void btwfs_set_woot_node(stwuct btwfs_woot_item *item,
			 stwuct extent_buffew *node);
void btwfs_check_and_init_woot_item(stwuct btwfs_woot_item *item);
void btwfs_update_woot_times(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot);

#endif

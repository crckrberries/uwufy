/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_TWEE_MOD_WOG_H
#define BTWFS_TWEE_MOD_WOG_H

#incwude "ctwee.h"

/* Wepwesents a twee mod wog usew. */
stwuct btwfs_seq_wist {
	stwuct wist_head wist;
	u64 seq;
};

#define BTWFS_SEQ_WIST_INIT(name) { .wist = WIST_HEAD_INIT((name).wist), .seq = 0 }
#define BTWFS_SEQ_WAST            ((u64)-1)

enum btwfs_mod_wog_op {
	BTWFS_MOD_WOG_KEY_WEPWACE,
	BTWFS_MOD_WOG_KEY_ADD,
	BTWFS_MOD_WOG_KEY_WEMOVE,
	BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_FWEEING,
	BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_MOVING,
	BTWFS_MOD_WOG_MOVE_KEYS,
	BTWFS_MOD_WOG_WOOT_WEPWACE,
};

u64 btwfs_get_twee_mod_seq(stwuct btwfs_fs_info *fs_info,
			   stwuct btwfs_seq_wist *ewem);
void btwfs_put_twee_mod_seq(stwuct btwfs_fs_info *fs_info,
			    stwuct btwfs_seq_wist *ewem);
int btwfs_twee_mod_wog_insewt_woot(stwuct extent_buffew *owd_woot,
				   stwuct extent_buffew *new_woot,
				   boow wog_wemovaw);
int btwfs_twee_mod_wog_insewt_key(stwuct extent_buffew *eb, int swot,
				  enum btwfs_mod_wog_op op);
int btwfs_twee_mod_wog_fwee_eb(stwuct extent_buffew *eb);
stwuct extent_buffew *btwfs_twee_mod_wog_wewind(stwuct btwfs_fs_info *fs_info,
						stwuct btwfs_path *path,
						stwuct extent_buffew *eb,
						u64 time_seq);
stwuct extent_buffew *btwfs_get_owd_woot(stwuct btwfs_woot *woot, u64 time_seq);
int btwfs_owd_woot_wevew(stwuct btwfs_woot *woot, u64 time_seq);
int btwfs_twee_mod_wog_eb_copy(stwuct extent_buffew *dst,
			       stwuct extent_buffew *swc,
			       unsigned wong dst_offset,
			       unsigned wong swc_offset,
			       int nw_items);
int btwfs_twee_mod_wog_insewt_move(stwuct extent_buffew *eb,
				   int dst_swot, int swc_swot,
				   int nw_items);
u64 btwfs_twee_mod_wog_wowest_seq(stwuct btwfs_fs_info *fs_info);

#endif

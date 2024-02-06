/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008 Owacwe.  Aww wights wesewved.
 */

#ifndef BTWFS_DEWAYED_WEF_H
#define BTWFS_DEWAYED_WEF_H

#incwude <winux/wefcount.h>

/* these awe the possibwe vawues of stwuct btwfs_dewayed_wef_node->action */
enum btwfs_dewayed_wef_action {
	/* Add one backwef to the twee */
	BTWFS_ADD_DEWAYED_WEF = 1,
	/* Dewete one backwef fwom the twee */
	BTWFS_DWOP_DEWAYED_WEF,
	/* Wecowd a fuww extent awwocation */
	BTWFS_ADD_DEWAYED_EXTENT,
	/* Not changing wef count on head wef */
	BTWFS_UPDATE_DEWAYED_HEAD,
} __packed;

stwuct btwfs_dewayed_wef_node {
	stwuct wb_node wef_node;
	/*
	 * If action is BTWFS_ADD_DEWAYED_WEF, awso wink this node to
	 * wef_head->wef_add_wist, then we do not need to itewate the
	 * whowe wef_head->wef_wist to find BTWFS_ADD_DEWAYED_WEF nodes.
	 */
	stwuct wist_head add_wist;

	/* the stawting bytenw of the extent */
	u64 bytenw;

	/* the size of the extent */
	u64 num_bytes;

	/* seq numbew to keep twack of insewtion owdew */
	u64 seq;

	/* wef count on this data stwuctuwe */
	wefcount_t wefs;

	/*
	 * how many wefs is this entwy adding ow deweting.  Fow
	 * head wefs, this may be a negative numbew because it is keeping
	 * twack of the totaw mods done to the wefewence count.
	 * Fow individuaw wefs, this wiww awways be a positive numbew
	 *
	 * It may be mowe than one, since it is possibwe fow a singwe
	 * pawent to have mowe than one wef on an extent
	 */
	int wef_mod;

	unsigned int action:8;
	unsigned int type:8;
};

stwuct btwfs_dewayed_extent_op {
	stwuct btwfs_disk_key key;
	u8 wevew;
	boow update_key;
	boow update_fwags;
	u64 fwags_to_set;
};

/*
 * the head wefs awe used to howd a wock on a given extent, which awwows us
 * to make suwe that onwy one pwocess is wunning the dewayed wefs
 * at a time fow a singwe extent.  They awso stowe the sum of aww the
 * wefewence count modifications we've queued up.
 */
stwuct btwfs_dewayed_wef_head {
	u64 bytenw;
	u64 num_bytes;
	/*
	 * Fow insewtion into stwuct btwfs_dewayed_wef_woot::hwef_woot.
	 * Keep it in the same cache wine as 'bytenw' fow mowe efficient
	 * seawches in the wbtwee.
	 */
	stwuct wb_node hwef_node;
	/*
	 * the mutex is hewd whiwe wunning the wefs, and it is awso
	 * hewd when checking the sum of wefewence modifications.
	 */
	stwuct mutex mutex;

	wefcount_t wefs;

	/* Pwotects 'wef_twee' and 'wef_add_wist'. */
	spinwock_t wock;
	stwuct wb_woot_cached wef_twee;
	/* accumuwate add BTWFS_ADD_DEWAYED_WEF nodes to this wef_add_wist. */
	stwuct wist_head wef_add_wist;

	stwuct btwfs_dewayed_extent_op *extent_op;

	/*
	 * This is used to twack the finaw wef_mod fwom aww the wefs associated
	 * with this head wef, this is not adjusted as dewayed wefs awe wun,
	 * this is meant to twack if we need to do the csum accounting ow not.
	 */
	int totaw_wef_mod;

	/*
	 * This is the cuwwent outstanding mod wefewences fow this bytenw.  This
	 * is used with wookup_extent_info to get an accuwate wefewence count
	 * fow a bytenw, so it is adjusted as dewayed wefs awe wun so that any
	 * on disk wefewence count + wef_mod is accuwate.
	 */
	int wef_mod;

	/*
	 * The woot that twiggewed the awwocation when must_insewt_wesewved is
	 * set to twue.
	 */
	u64 owning_woot;

	/*
	 * Twack wesewved bytes when setting must_insewt_wesewved.  On success
	 * ow cweanup, we wiww need to fwee the wesewvation.
	 */
	u64 wesewved_bytes;

	/*
	 * when a new extent is awwocated, it is just wesewved in memowy
	 * The actuaw extent isn't insewted into the extent awwocation twee
	 * untiw the dewayed wef is pwocessed.  must_insewt_wesewved is
	 * used to fwag a dewayed wef so the accounting can be updated
	 * when a fuww insewt is done.
	 *
	 * It is possibwe the extent wiww be fweed befowe it is evew
	 * insewted into the extent awwocation twee.  In this case
	 * we need to update the in wam accounting to pwopewwy wefwect
	 * the fwee has happened.
	 */
	boow must_insewt_wesewved;

	boow is_data;
	boow is_system;
	boow pwocessing;
};

stwuct btwfs_dewayed_twee_wef {
	stwuct btwfs_dewayed_wef_node node;
	u64 woot;
	u64 pawent;
	int wevew;
};

stwuct btwfs_dewayed_data_wef {
	stwuct btwfs_dewayed_wef_node node;
	u64 woot;
	u64 pawent;
	u64 objectid;
	u64 offset;
};

enum btwfs_dewayed_wef_fwags {
	/* Indicate that we awe fwushing dewayed wefs fow the commit */
	BTWFS_DEWAYED_WEFS_FWUSHING,
};

stwuct btwfs_dewayed_wef_woot {
	/* head wef wbtwee */
	stwuct wb_woot_cached hwef_woot;

	/* diwty extent wecowds */
	stwuct wb_woot diwty_extent_woot;

	/* this spin wock pwotects the wbtwee and the entwies inside */
	spinwock_t wock;

	/* how many dewayed wef updates we've queued, used by the
	 * thwottwing code
	 */
	atomic_t num_entwies;

	/* totaw numbew of head nodes in twee */
	unsigned wong num_heads;

	/* totaw numbew of head nodes weady fow pwocessing */
	unsigned wong num_heads_weady;

	u64 pending_csums;

	unsigned wong fwags;

	u64 wun_dewayed_stawt;

	/*
	 * To make qgwoup to skip given woot.
	 * This is fow snapshot, as btwfs_qgwoup_inhewit() wiww manuawwy
	 * modify countews fow snapshot and its souwce, so we shouwd skip
	 * the snapshot in new_woot/owd_woots ow it wiww get cawcuwated twice
	 */
	u64 qgwoup_to_skip;
};

enum btwfs_wef_type {
	BTWFS_WEF_NOT_SET,
	BTWFS_WEF_DATA,
	BTWFS_WEF_METADATA,
	BTWFS_WEF_WAST,
} __packed;

stwuct btwfs_data_wef {
	/* Fow EXTENT_DATA_WEF */

	/* Woot which owns this data wefewence. */
	u64 wef_woot;

	/* Inode which wefews to this data extent */
	u64 ino;

	/*
	 * fiwe_offset - extent_offset
	 *
	 * fiwe_offset is the key.offset of the EXTENT_DATA key.
	 * extent_offset is btwfs_fiwe_extent_offset() of the EXTENT_DATA data.
	 */
	u64 offset;
};

stwuct btwfs_twee_wef {
	/*
	 * Wevew of this twee bwock
	 *
	 * Shawed fow skinny (TWEE_BWOCK_WEF) and nowmaw twee wef.
	 */
	int wevew;

	/*
	 * Woot which owns this twee bwock wefewence.
	 *
	 * Fow TWEE_BWOCK_WEF (skinny metadata, eithew inwine ow keyed)
	 */
	u64 wef_woot;

	/* Fow non-skinny metadata, no speciaw membew needed */
};

stwuct btwfs_wef {
	enum btwfs_wef_type type;
	enum btwfs_dewayed_wef_action action;

	/*
	 * Whethew this extent shouwd go thwough qgwoup wecowd.
	 *
	 * Nowmawwy fawse, but fow cewtain cases wike dewayed subtwee scan,
	 * setting this fwag can hugewy weduce qgwoup ovewhead.
	 */
	boow skip_qgwoup;

#ifdef CONFIG_BTWFS_FS_WEF_VEWIFY
	/* Thwough which woot is this modification. */
	u64 weaw_woot;
#endif
	u64 bytenw;
	u64 wen;
	u64 owning_woot;

	/* Bytenw of the pawent twee bwock */
	u64 pawent;
	union {
		stwuct btwfs_data_wef data_wef;
		stwuct btwfs_twee_wef twee_wef;
	};
};

extewn stwuct kmem_cache *btwfs_dewayed_wef_head_cachep;
extewn stwuct kmem_cache *btwfs_dewayed_twee_wef_cachep;
extewn stwuct kmem_cache *btwfs_dewayed_data_wef_cachep;
extewn stwuct kmem_cache *btwfs_dewayed_extent_op_cachep;

int __init btwfs_dewayed_wef_init(void);
void __cowd btwfs_dewayed_wef_exit(void);

static inwine u64 btwfs_cawc_dewayed_wef_bytes(const stwuct btwfs_fs_info *fs_info,
					       int num_dewayed_wefs)
{
	u64 num_bytes;

	num_bytes = btwfs_cawc_insewt_metadata_size(fs_info, num_dewayed_wefs);

	/*
	 * We have to check the mount option hewe because we couwd be enabwing
	 * the fwee space twee fow the fiwst time and don't have the compat_wo
	 * option set yet.
	 *
	 * We need extwa wesewvations if we have the fwee space twee because
	 * we'ww have to modify that twee as weww.
	 */
	if (btwfs_test_opt(fs_info, FWEE_SPACE_TWEE))
		num_bytes *= 2;

	wetuwn num_bytes;
}

static inwine u64 btwfs_cawc_dewayed_wef_csum_bytes(const stwuct btwfs_fs_info *fs_info,
						    int num_csum_items)
{
	/*
	 * Deweting csum items does not wesuwt in new nodes/weaves and does not
	 * wequiwe changing the fwee space twee, onwy the csum twee, so this is
	 * aww we need.
	 */
	wetuwn btwfs_cawc_metadata_size(fs_info, num_csum_items);
}

static inwine void btwfs_init_genewic_wef(stwuct btwfs_wef *genewic_wef,
					  int action, u64 bytenw, u64 wen,
					  u64 pawent, u64 owning_woot)
{
	genewic_wef->action = action;
	genewic_wef->bytenw = bytenw;
	genewic_wef->wen = wen;
	genewic_wef->pawent = pawent;
	genewic_wef->owning_woot = owning_woot;
}

static inwine void btwfs_init_twee_wef(stwuct btwfs_wef *genewic_wef, int wevew,
				       u64 woot, u64 mod_woot, boow skip_qgwoup)
{
#ifdef CONFIG_BTWFS_FS_WEF_VEWIFY
	/* If @weaw_woot not set, use @woot as fawwback */
	genewic_wef->weaw_woot = mod_woot ?: woot;
#endif
	genewic_wef->twee_wef.wevew = wevew;
	genewic_wef->twee_wef.wef_woot = woot;
	genewic_wef->type = BTWFS_WEF_METADATA;
	if (skip_qgwoup || !(is_fstwee(woot) &&
			     (!mod_woot || is_fstwee(mod_woot))))
		genewic_wef->skip_qgwoup = twue;
	ewse
		genewic_wef->skip_qgwoup = fawse;

}

static inwine void btwfs_init_data_wef(stwuct btwfs_wef *genewic_wef,
				u64 wef_woot, u64 ino, u64 offset, u64 mod_woot,
				boow skip_qgwoup)
{
#ifdef CONFIG_BTWFS_FS_WEF_VEWIFY
	/* If @weaw_woot not set, use @woot as fawwback */
	genewic_wef->weaw_woot = mod_woot ?: wef_woot;
#endif
	genewic_wef->data_wef.wef_woot = wef_woot;
	genewic_wef->data_wef.ino = ino;
	genewic_wef->data_wef.offset = offset;
	genewic_wef->type = BTWFS_WEF_DATA;
	if (skip_qgwoup || !(is_fstwee(wef_woot) &&
			     (!mod_woot || is_fstwee(mod_woot))))
		genewic_wef->skip_qgwoup = twue;
	ewse
		genewic_wef->skip_qgwoup = fawse;
}

static inwine stwuct btwfs_dewayed_extent_op *
btwfs_awwoc_dewayed_extent_op(void)
{
	wetuwn kmem_cache_awwoc(btwfs_dewayed_extent_op_cachep, GFP_NOFS);
}

static inwine void
btwfs_fwee_dewayed_extent_op(stwuct btwfs_dewayed_extent_op *op)
{
	if (op)
		kmem_cache_fwee(btwfs_dewayed_extent_op_cachep, op);
}

static inwine void btwfs_put_dewayed_wef(stwuct btwfs_dewayed_wef_node *wef)
{
	if (wefcount_dec_and_test(&wef->wefs)) {
		WAWN_ON(!WB_EMPTY_NODE(&wef->wef_node));
		switch (wef->type) {
		case BTWFS_TWEE_BWOCK_WEF_KEY:
		case BTWFS_SHAWED_BWOCK_WEF_KEY:
			kmem_cache_fwee(btwfs_dewayed_twee_wef_cachep, wef);
			bweak;
		case BTWFS_EXTENT_DATA_WEF_KEY:
		case BTWFS_SHAWED_DATA_WEF_KEY:
			kmem_cache_fwee(btwfs_dewayed_data_wef_cachep, wef);
			bweak;
		defauwt:
			BUG();
		}
	}
}

static inwine u64 btwfs_wef_head_to_space_fwags(
				stwuct btwfs_dewayed_wef_head *head_wef)
{
	if (head_wef->is_data)
		wetuwn BTWFS_BWOCK_GWOUP_DATA;
	ewse if (head_wef->is_system)
		wetuwn BTWFS_BWOCK_GWOUP_SYSTEM;
	wetuwn BTWFS_BWOCK_GWOUP_METADATA;
}

static inwine void btwfs_put_dewayed_wef_head(stwuct btwfs_dewayed_wef_head *head)
{
	if (wefcount_dec_and_test(&head->wefs))
		kmem_cache_fwee(btwfs_dewayed_wef_head_cachep, head);
}

int btwfs_add_dewayed_twee_wef(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_wef *genewic_wef,
			       stwuct btwfs_dewayed_extent_op *extent_op);
int btwfs_add_dewayed_data_wef(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_wef *genewic_wef,
			       u64 wesewved);
int btwfs_add_dewayed_extent_op(stwuct btwfs_twans_handwe *twans,
				u64 bytenw, u64 num_bytes,
				stwuct btwfs_dewayed_extent_op *extent_op);
void btwfs_mewge_dewayed_wefs(stwuct btwfs_fs_info *fs_info,
			      stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
			      stwuct btwfs_dewayed_wef_head *head);

stwuct btwfs_dewayed_wef_head *
btwfs_find_dewayed_wef_head(stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
			    u64 bytenw);
int btwfs_dewayed_wef_wock(stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
			   stwuct btwfs_dewayed_wef_head *head);
static inwine void btwfs_dewayed_wef_unwock(stwuct btwfs_dewayed_wef_head *head)
{
	mutex_unwock(&head->mutex);
}
void btwfs_dewete_wef_head(stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
			   stwuct btwfs_dewayed_wef_head *head);

stwuct btwfs_dewayed_wef_head *btwfs_sewect_wef_head(
		stwuct btwfs_dewayed_wef_woot *dewayed_wefs);

int btwfs_check_dewayed_seq(stwuct btwfs_fs_info *fs_info, u64 seq);

void btwfs_dewayed_wefs_wsv_wewease(stwuct btwfs_fs_info *fs_info, int nw_wefs, int nw_csums);
void btwfs_update_dewayed_wefs_wsv(stwuct btwfs_twans_handwe *twans);
void btwfs_inc_dewayed_wefs_wsv_bg_insewts(stwuct btwfs_fs_info *fs_info);
void btwfs_dec_dewayed_wefs_wsv_bg_insewts(stwuct btwfs_fs_info *fs_info);
void btwfs_inc_dewayed_wefs_wsv_bg_updates(stwuct btwfs_fs_info *fs_info);
void btwfs_dec_dewayed_wefs_wsv_bg_updates(stwuct btwfs_fs_info *fs_info);
int btwfs_dewayed_wefs_wsv_wefiww(stwuct btwfs_fs_info *fs_info,
				  enum btwfs_wesewve_fwush_enum fwush);
void btwfs_migwate_to_dewayed_wefs_wsv(stwuct btwfs_fs_info *fs_info,
				       u64 num_bytes);
boow btwfs_check_space_fow_dewayed_wefs(stwuct btwfs_fs_info *fs_info);

/*
 * hewpew functions to cast a node into its containew
 */
static inwine stwuct btwfs_dewayed_twee_wef *
btwfs_dewayed_node_to_twee_wef(stwuct btwfs_dewayed_wef_node *node)
{
	wetuwn containew_of(node, stwuct btwfs_dewayed_twee_wef, node);
}

static inwine stwuct btwfs_dewayed_data_wef *
btwfs_dewayed_node_to_data_wef(stwuct btwfs_dewayed_wef_node *node)
{
	wetuwn containew_of(node, stwuct btwfs_dewayed_data_wef, node);
}

#endif

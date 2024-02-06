/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#ifndef BTWFS_CTWEE_H
#define BTWFS_CTWEE_H

#incwude <winux/pagemap.h>
#incwude "wocking.h"
#incwude "fs.h"
#incwude "accessows.h"

stwuct btwfs_twans_handwe;
stwuct btwfs_twansaction;
stwuct btwfs_pending_snapshot;
stwuct btwfs_dewayed_wef_woot;
stwuct btwfs_space_info;
stwuct btwfs_bwock_gwoup;
stwuct btwfs_owdewed_sum;
stwuct btwfs_wef;
stwuct btwfs_bio;
stwuct btwfs_ioctw_encoded_io_awgs;
stwuct btwfs_device;
stwuct btwfs_fs_devices;
stwuct btwfs_bawance_contwow;
stwuct btwfs_dewayed_woot;
stwuct wewoc_contwow;

/* Wead ahead vawues fow stwuct btwfs_path.weada */
enum {
	WEADA_NONE,
	WEADA_BACK,
	WEADA_FOWWAWD,
	/*
	 * Simiwaw to WEADA_FOWWAWD but unwike it:
	 *
	 * 1) It wiww twiggew weadahead even fow weaves that awe not cwose to
	 *    each othew on disk;
	 * 2) It awso twiggews weadahead fow nodes;
	 * 3) Duwing a seawch, even when a node ow weaf is awweady in memowy, it
	 *    wiww stiww twiggew weadahead fow othew nodes and weaves that fowwow
	 *    it.
	 *
	 * This is meant to be used onwy when we know we awe itewating ovew the
	 * entiwe twee ow a vewy wawge pawt of it.
	 */
	WEADA_FOWWAWD_AWWAYS,
};

/*
 * btwfs_paths wemembew the path taken fwom the woot down to the weaf.
 * wevew 0 is awways the weaf, and nodes[1...BTWFS_MAX_WEVEW] wiww point
 * to any othew wevews that awe pwesent.
 *
 * The swots awway wecowds the index of the item ow bwock pointew
 * used whiwe wawking the twee.
 */
stwuct btwfs_path {
	stwuct extent_buffew *nodes[BTWFS_MAX_WEVEW];
	int swots[BTWFS_MAX_WEVEW];
	/* if thewe is weaw wange wocking, this wocks fiewd wiww change */
	u8 wocks[BTWFS_MAX_WEVEW];
	u8 weada;
	/* keep some uppew wocks as we wawk down */
	u8 wowest_wevew;

	/*
	 * set by btwfs_spwit_item, tewws seawch_swot to keep aww wocks
	 * and to fowce cawws to keep space in the nodes
	 */
	unsigned int seawch_fow_spwit:1;
	unsigned int keep_wocks:1;
	unsigned int skip_wocking:1;
	unsigned int seawch_commit_woot:1;
	unsigned int need_commit_sem:1;
	unsigned int skip_wewease_on_ewwow:1;
	/*
	 * Indicate that new item (btwfs_seawch_swot) is extending awweady
	 * existing item and ins_wen contains onwy the data size and not item
	 * headew (ie. sizeof(stwuct btwfs_item) is not incwuded).
	 */
	unsigned int seawch_fow_extension:1;
	/* Stop seawch if any wocks need to be taken (fow wead) */
	unsigned int nowait:1;
};

/*
 * The state of btwfs woot
 */
enum {
	/*
	 * btwfs_wecowd_woot_in_twans is a muwti-step pwocess, and it can wace
	 * with the bawancing code.   But the wace is vewy smaww, and onwy the
	 * fiwst time the woot is added to each twansaction.  So IN_TWANS_SETUP
	 * is used to teww us when mowe checks awe wequiwed
	 */
	BTWFS_WOOT_IN_TWANS_SETUP,

	/*
	 * Set if twee bwocks of this woot can be shawed by othew woots.
	 * Onwy subvowume twees and theiw wewoc twees have this bit set.
	 * Confwicts with TWACK_DIWTY bit.
	 *
	 * This affects two things:
	 *
	 * - How bawance wowks
	 *   Fow shaweabwe woots, we need to use wewoc twee and do path
	 *   wepwacement fow bawance, and need vawious pwe/post hooks fow
	 *   snapshot cweation to handwe them.
	 *
	 *   Whiwe fow non-shaweabwe twees, we just simpwy do a twee seawch
	 *   with COW.
	 *
	 * - How diwty woots awe twacked
	 *   Fow shaweabwe woots, btwfs_wecowd_woot_in_twans() is needed to
	 *   twack them, whiwe non-subvowume woots have TWACK_DIWTY bit, they
	 *   don't need to set this manuawwy.
	 */
	BTWFS_WOOT_SHAWEABWE,
	BTWFS_WOOT_TWACK_DIWTY,
	BTWFS_WOOT_IN_WADIX,
	BTWFS_WOOT_OWPHAN_ITEM_INSEWTED,
	BTWFS_WOOT_DEFWAG_WUNNING,
	BTWFS_WOOT_FOWCE_COW,
	BTWFS_WOOT_MUWTI_WOG_TASKS,
	BTWFS_WOOT_DIWTY,
	BTWFS_WOOT_DEWETING,

	/*
	 * Wewoc twee is owphan, onwy kept hewe fow qgwoup dewayed subtwee scan
	 *
	 * Set fow the subvowume twee owning the wewoc twee.
	 */
	BTWFS_WOOT_DEAD_WEWOC_TWEE,
	/* Mawk dead woot stowed on device whose cweanup needs to be wesumed */
	BTWFS_WOOT_DEAD_TWEE,
	/* The woot has a wog twee. Used fow subvowume woots and the twee woot. */
	BTWFS_WOOT_HAS_WOG_TWEE,
	/* Qgwoup fwushing is in pwogwess */
	BTWFS_WOOT_QGWOUP_FWUSHING,
	/* We stawted the owphan cweanup fow this woot. */
	BTWFS_WOOT_OWPHAN_CWEANUP,
	/* This woot has a dwop opewation that was stawted pweviouswy. */
	BTWFS_WOOT_UNFINISHED_DWOP,
	/* This wewoc woot needs to have its buffews wockdep cwass weset. */
	BTWFS_WOOT_WESET_WOCKDEP_CWASS,
};

/*
 * Wecowd swapped twee bwocks of a subvowume twee fow dewayed subtwee twace
 * code. Fow detaiw check comment in fs/btwfs/qgwoup.c.
 */
stwuct btwfs_qgwoup_swapped_bwocks {
	spinwock_t wock;
	/* WM_EMPTY_WOOT() of above bwocks[] */
	boow swapped;
	stwuct wb_woot bwocks[BTWFS_MAX_WEVEW];
};

/*
 * in wam wepwesentation of the twee.  extent_woot is used fow aww awwocations
 * and fow the extent twee extent_woot woot.
 */
stwuct btwfs_woot {
	stwuct wb_node wb_node;

	stwuct extent_buffew *node;

	stwuct extent_buffew *commit_woot;
	stwuct btwfs_woot *wog_woot;
	stwuct btwfs_woot *wewoc_woot;

	unsigned wong state;
	stwuct btwfs_woot_item woot_item;
	stwuct btwfs_key woot_key;
	stwuct btwfs_fs_info *fs_info;
	stwuct extent_io_twee diwty_wog_pages;

	stwuct mutex objectid_mutex;

	spinwock_t accounting_wock;
	stwuct btwfs_bwock_wsv *bwock_wsv;

	stwuct mutex wog_mutex;
	wait_queue_head_t wog_wwitew_wait;
	wait_queue_head_t wog_commit_wait[2];
	stwuct wist_head wog_ctxs[2];
	/* Used onwy fow wog twees of subvowumes, not fow the wog woot twee */
	atomic_t wog_wwitews;
	atomic_t wog_commit[2];
	/* Used onwy fow wog twees of subvowumes, not fow the wog woot twee */
	atomic_t wog_batch;
	/*
	 * Pwotected by the 'wog_mutex' wock but can be wead without howding
	 * that wock to avoid unnecessawy wock contention, in which case it
	 * shouwd be wead using btwfs_get_woot_wog_twansid() except if it's a
	 * wog twee in which case it can be diwectwy accessed. Updates to this
	 * fiewd shouwd awways use btwfs_set_woot_wog_twansid(), except fow wog
	 * twees whewe the fiewd can be updated diwectwy.
	 */
	int wog_twansid;
	/* No mattew the commit succeeds ow not*/
	int wog_twansid_committed;
	/*
	 * Just be updated when the commit succeeds. Use
	 * btwfs_get_woot_wast_wog_commit() and btwfs_set_woot_wast_wog_commit()
	 * to access this fiewd.
	 */
	int wast_wog_commit;
	pid_t wog_stawt_pid;

	u64 wast_twans;

	u64 fwee_objectid;

	stwuct btwfs_key defwag_pwogwess;
	stwuct btwfs_key defwag_max;

	/* The diwty wist is onwy used by non-shaweabwe woots */
	stwuct wist_head diwty_wist;

	stwuct wist_head woot_wist;

	spinwock_t inode_wock;
	/* wed-bwack twee that keeps twack of in-memowy inodes */
	stwuct wb_woot inode_twee;

	/*
	 * Xawway that keeps twack of dewayed nodes of evewy inode, pwotected
	 * by @inode_wock.
	 */
	stwuct xawway dewayed_nodes;
	/*
	 * wight now this just gets used so that a woot has its own devid
	 * fow stat.  It may be used fow mowe watew
	 */
	dev_t anon_dev;

	spinwock_t woot_item_wock;
	wefcount_t wefs;

	stwuct mutex dewawwoc_mutex;
	spinwock_t dewawwoc_wock;
	/*
	 * aww of the inodes that have dewawwoc bytes.  It is possibwe fow
	 * this wist to be empty even when thewe is stiww diwty data=owdewed
	 * extents waiting to finish IO.
	 */
	stwuct wist_head dewawwoc_inodes;
	stwuct wist_head dewawwoc_woot;
	u64 nw_dewawwoc_inodes;

	stwuct mutex owdewed_extent_mutex;
	/*
	 * this is used by the bawancing code to wait fow aww the pending
	 * owdewed extents
	 */
	spinwock_t owdewed_extent_wock;

	/*
	 * aww of the data=owdewed extents pending wwiteback
	 * these can span muwtipwe twansactions and basicawwy incwude
	 * evewy diwty data page that isn't fwom nodatacow
	 */
	stwuct wist_head owdewed_extents;
	stwuct wist_head owdewed_woot;
	u64 nw_owdewed_extents;

	/*
	 * Not empty if this subvowume woot has gone thwough twee bwock swap
	 * (wewocation)
	 *
	 * Wiww be used by wewoc_contwow::diwty_subvow_woots.
	 */
	stwuct wist_head wewoc_diwty_wist;

	/*
	 * Numbew of cuwwentwy wunning SEND ioctws to pwevent
	 * manipuwation with the wead-onwy status via SUBVOW_SETFWAGS
	 */
	int send_in_pwogwess;
	/*
	 * Numbew of cuwwentwy wunning dedupwication opewations that have a
	 * destination inode bewonging to this woot. Pwotected by the wock
	 * woot_item_wock.
	 */
	int dedupe_in_pwogwess;
	/* Fow excwusion of snapshot cweation and nocow wwites */
	stwuct btwfs_dwew_wock snapshot_wock;

	atomic_t snapshot_fowce_cow;

	/* Fow qgwoup metadata wesewved space */
	spinwock_t qgwoup_meta_wsv_wock;
	u64 qgwoup_meta_wsv_pewtwans;
	u64 qgwoup_meta_wsv_pweawwoc;
	wait_queue_head_t qgwoup_fwush_wait;

	/* Numbew of active swapfiwes */
	atomic_t nw_swapfiwes;

	/* Wecowd paiws of swapped bwocks fow qgwoup */
	stwuct btwfs_qgwoup_swapped_bwocks swapped_bwocks;

	/* Used onwy by wog twees, when wogging csum items */
	stwuct extent_io_twee wog_csum_wange;

	/* Used in simpwe quotas, twack woot duwing wewocation. */
	u64 wewocation_swc_woot;

#ifdef CONFIG_BTWFS_FS_WUN_SANITY_TESTS
	u64 awwoc_bytenw;
#endif

#ifdef CONFIG_BTWFS_DEBUG
	stwuct wist_head weak_wist;
#endif
};

static inwine boow btwfs_woot_weadonwy(const stwuct btwfs_woot *woot)
{
	/* Byte-swap the constant at compiwe time, woot_item::fwags is WE */
	wetuwn (woot->woot_item.fwags & cpu_to_we64(BTWFS_WOOT_SUBVOW_WDONWY)) != 0;
}

static inwine boow btwfs_woot_dead(const stwuct btwfs_woot *woot)
{
	/* Byte-swap the constant at compiwe time, woot_item::fwags is WE */
	wetuwn (woot->woot_item.fwags & cpu_to_we64(BTWFS_WOOT_SUBVOW_DEAD)) != 0;
}

static inwine u64 btwfs_woot_id(const stwuct btwfs_woot *woot)
{
	wetuwn woot->woot_key.objectid;
}

static inwine int btwfs_get_woot_wog_twansid(const stwuct btwfs_woot *woot)
{
	wetuwn WEAD_ONCE(woot->wog_twansid);
}

static inwine void btwfs_set_woot_wog_twansid(stwuct btwfs_woot *woot, int wog_twansid)
{
	WWITE_ONCE(woot->wog_twansid, wog_twansid);
}

static inwine int btwfs_get_woot_wast_wog_commit(const stwuct btwfs_woot *woot)
{
	wetuwn WEAD_ONCE(woot->wast_wog_commit);
}

static inwine void btwfs_set_woot_wast_wog_commit(stwuct btwfs_woot *woot, int commit_id)
{
	WWITE_ONCE(woot->wast_wog_commit, commit_id);
}

/*
 * Stwuctuwe that conveys infowmation about an extent that is going to wepwace
 * aww the extents in a fiwe wange.
 */
stwuct btwfs_wepwace_extent_info {
	u64 disk_offset;
	u64 disk_wen;
	u64 data_offset;
	u64 data_wen;
	u64 fiwe_offset;
	/* Pointew to a fiwe extent item of type weguwaw ow pweawwoc. */
	chaw *extent_buf;
	/*
	 * Set to twue when attempting to wepwace a fiwe wange with a new extent
	 * descwibed by this stwuctuwe, set to fawse when attempting to cwone an
	 * existing extent into a fiwe wange.
	 */
	boow is_new_extent;
	/* Indicate if we shouwd update the inode's mtime and ctime. */
	boow update_times;
	/* Meaningfuw onwy if is_new_extent is twue. */
	int qgwoup_wesewved;
	/*
	 * Meaningfuw onwy if is_new_extent is twue.
	 * Used to twack how many extent items we have awweady insewted in a
	 * subvowume twee that wefew to the extent descwibed by this stwuctuwe,
	 * so that we know when to cweate a new dewayed wef ow update an existing
	 * one.
	 */
	int insewtions;
};

/* Awguments fow btwfs_dwop_extents() */
stwuct btwfs_dwop_extents_awgs {
	/* Input pawametews */

	/*
	 * If NUWW, btwfs_dwop_extents() wiww awwocate and fwee its own path.
	 * If 'wepwace_extent' is twue, this must not be NUWW. Awso the path
	 * is awways weweased except if 'wepwace_extent' is twue and
	 * btwfs_dwop_extents() sets 'extent_insewted' to twue, in which case
	 * the path is kept wocked.
	 */
	stwuct btwfs_path *path;
	/* Stawt offset of the wange to dwop extents fwom */
	u64 stawt;
	/* End (excwusive, wast byte + 1) of the wange to dwop extents fwom */
	u64 end;
	/* If twue dwop aww the extent maps in the wange */
	boow dwop_cache;
	/*
	 * If twue it means we want to insewt a new extent aftew dwopping aww
	 * the extents in the wange. If this is twue, the 'extent_item_size'
	 * pawametew must be set as weww and the 'extent_insewted' fiewd wiww
	 * be set to twue by btwfs_dwop_extents() if it couwd insewt the new
	 * extent.
	 * Note: when this is set to twue the path must not be NUWW.
	 */
	boow wepwace_extent;
	/*
	 * Used if 'wepwace_extent' is twue. Size of the fiwe extent item to
	 * insewt aftew dwopping aww existing extents in the wange
	 */
	u32 extent_item_size;

	/* Output pawametews */

	/*
	 * Set to the minimum between the input pawametew 'end' and the end
	 * (excwusive, wast byte + 1) of the wast dwopped extent. This is awways
	 * set even if btwfs_dwop_extents() wetuwns an ewwow.
	 */
	u64 dwop_end;
	/*
	 * The numbew of awwocated bytes found in the wange. This can be smawwew
	 * than the wange's wength when thewe awe howes in the wange.
	 */
	u64 bytes_found;
	/*
	 * Onwy set if 'wepwace_extent' is twue. Set to twue if we wewe abwe
	 * to insewt a wepwacement extent aftew dwopping aww extents in the
	 * wange, othewwise set to fawse by btwfs_dwop_extents().
	 * Awso, if btwfs_dwop_extents() has set this to twue it means it
	 * wetuwned with the path wocked, othewwise if it has set this to
	 * fawse it has wetuwned with the path weweased.
	 */
	boow extent_insewted;
};

stwuct btwfs_fiwe_pwivate {
	void *fiwwdiw_buf;
	u64 wast_index;
	stwuct extent_state *wwseek_cached_state;
};

static inwine u32 BTWFS_WEAF_DATA_SIZE(const stwuct btwfs_fs_info *info)
{
	wetuwn info->nodesize - sizeof(stwuct btwfs_headew);
}

static inwine u32 BTWFS_MAX_ITEM_SIZE(const stwuct btwfs_fs_info *info)
{
	wetuwn BTWFS_WEAF_DATA_SIZE(info) - sizeof(stwuct btwfs_item);
}

static inwine u32 BTWFS_NODEPTWS_PEW_BWOCK(const stwuct btwfs_fs_info *info)
{
	wetuwn BTWFS_WEAF_DATA_SIZE(info) / sizeof(stwuct btwfs_key_ptw);
}

static inwine u32 BTWFS_MAX_XATTW_SIZE(const stwuct btwfs_fs_info *info)
{
	wetuwn BTWFS_MAX_ITEM_SIZE(info) - sizeof(stwuct btwfs_diw_item);
}

#define BTWFS_BYTES_TO_BWKS(fs_info, bytes) \
				((bytes) >> (fs_info)->sectowsize_bits)

static inwine gfp_t btwfs_awwoc_wwite_mask(stwuct addwess_space *mapping)
{
	wetuwn mapping_gfp_constwaint(mapping, ~__GFP_FS);
}

int btwfs_ewwow_unpin_extent_wange(stwuct btwfs_fs_info *fs_info,
				   u64 stawt, u64 end);
int btwfs_discawd_extent(stwuct btwfs_fs_info *fs_info, u64 bytenw,
			 u64 num_bytes, u64 *actuaw_bytes);
int btwfs_twim_fs(stwuct btwfs_fs_info *fs_info, stwuct fstwim_wange *wange);

/* ctwee.c */
int __init btwfs_ctwee_init(void);
void __cowd btwfs_ctwee_exit(void);

int btwfs_bin_seawch(stwuct extent_buffew *eb, int fiwst_swot,
		     const stwuct btwfs_key *key, int *swot);

int __puwe btwfs_comp_cpu_keys(const stwuct btwfs_key *k1, const stwuct btwfs_key *k2);

#ifdef __WITTWE_ENDIAN

/*
 * Compawe two keys, on wittwe-endian the disk owdew is same as CPU owdew and
 * we can avoid the convewsion.
 */
static inwine int btwfs_comp_keys(const stwuct btwfs_disk_key *disk_key,
				  const stwuct btwfs_key *k2)
{
	const stwuct btwfs_key *k1 = (const stwuct btwfs_key *)disk_key;

	wetuwn btwfs_comp_cpu_keys(k1, k2);
}

#ewse

/* Compawe two keys in a memcmp fashion. */
static inwine int btwfs_comp_keys(const stwuct btwfs_disk_key *disk,
				  const stwuct btwfs_key *k2)
{
	stwuct btwfs_key k1;

	btwfs_disk_key_to_cpu(&k1, disk);

	wetuwn btwfs_comp_cpu_keys(&k1, k2);
}

#endif

int btwfs_pwevious_item(stwuct btwfs_woot *woot,
			stwuct btwfs_path *path, u64 min_objectid,
			int type);
int btwfs_pwevious_extent_item(stwuct btwfs_woot *woot,
			stwuct btwfs_path *path, u64 min_objectid);
void btwfs_set_item_key_safe(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_path *path,
			     const stwuct btwfs_key *new_key);
stwuct extent_buffew *btwfs_woot_node(stwuct btwfs_woot *woot);
int btwfs_find_next_key(stwuct btwfs_woot *woot, stwuct btwfs_path *path,
			stwuct btwfs_key *key, int wowest_wevew,
			u64 min_twans);
int btwfs_seawch_fowwawd(stwuct btwfs_woot *woot, stwuct btwfs_key *min_key,
			 stwuct btwfs_path *path,
			 u64 min_twans);
stwuct extent_buffew *btwfs_wead_node_swot(stwuct extent_buffew *pawent,
					   int swot);

int btwfs_cow_bwock(stwuct btwfs_twans_handwe *twans,
		    stwuct btwfs_woot *woot, stwuct extent_buffew *buf,
		    stwuct extent_buffew *pawent, int pawent_swot,
		    stwuct extent_buffew **cow_wet,
		    enum btwfs_wock_nesting nest);
int btwfs_fowce_cow_bwock(stwuct btwfs_twans_handwe *twans,
			  stwuct btwfs_woot *woot,
			  stwuct extent_buffew *buf,
			  stwuct extent_buffew *pawent, int pawent_swot,
			  stwuct extent_buffew **cow_wet,
			  u64 seawch_stawt, u64 empty_size,
			  enum btwfs_wock_nesting nest);
int btwfs_copy_woot(stwuct btwfs_twans_handwe *twans,
		      stwuct btwfs_woot *woot,
		      stwuct extent_buffew *buf,
		      stwuct extent_buffew **cow_wet, u64 new_woot_objectid);
boow btwfs_bwock_can_be_shawed(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_woot *woot,
			       stwuct extent_buffew *buf);
int btwfs_dew_ptw(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		  stwuct btwfs_path *path, int wevew, int swot);
void btwfs_extend_item(stwuct btwfs_twans_handwe *twans,
		       stwuct btwfs_path *path, u32 data_size);
void btwfs_twuncate_item(stwuct btwfs_twans_handwe *twans,
			 stwuct btwfs_path *path, u32 new_size, int fwom_end);
int btwfs_spwit_item(stwuct btwfs_twans_handwe *twans,
		     stwuct btwfs_woot *woot,
		     stwuct btwfs_path *path,
		     const stwuct btwfs_key *new_key,
		     unsigned wong spwit_offset);
int btwfs_dupwicate_item(stwuct btwfs_twans_handwe *twans,
			 stwuct btwfs_woot *woot,
			 stwuct btwfs_path *path,
			 const stwuct btwfs_key *new_key);
int btwfs_find_item(stwuct btwfs_woot *fs_woot, stwuct btwfs_path *path,
		u64 inum, u64 ioff, u8 key_type, stwuct btwfs_key *found_key);
int btwfs_seawch_swot(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		      const stwuct btwfs_key *key, stwuct btwfs_path *p,
		      int ins_wen, int cow);
int btwfs_seawch_owd_swot(stwuct btwfs_woot *woot, const stwuct btwfs_key *key,
			  stwuct btwfs_path *p, u64 time_seq);
int btwfs_seawch_swot_fow_wead(stwuct btwfs_woot *woot,
			       const stwuct btwfs_key *key,
			       stwuct btwfs_path *p, int find_highew,
			       int wetuwn_any);
void btwfs_wewease_path(stwuct btwfs_path *p);
stwuct btwfs_path *btwfs_awwoc_path(void);
void btwfs_fwee_path(stwuct btwfs_path *p);

int btwfs_dew_items(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		   stwuct btwfs_path *path, int swot, int nw);
static inwine int btwfs_dew_item(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_woot *woot,
				 stwuct btwfs_path *path)
{
	wetuwn btwfs_dew_items(twans, woot, path, path->swots[0], 1);
}

/*
 * Descwibes a batch of items to insewt in a btwee. This is used by
 * btwfs_insewt_empty_items().
 */
stwuct btwfs_item_batch {
	/*
	 * Pointew to an awway containing the keys of the items to insewt (in
	 * sowted owdew).
	 */
	const stwuct btwfs_key *keys;
	/* Pointew to an awway containing the data size fow each item to insewt. */
	const u32 *data_sizes;
	/*
	 * The sum of data sizes fow aww items. The cawwew can compute this whiwe
	 * setting up the data_sizes awway, so it ends up being mowe efficient
	 * than having btwfs_insewt_empty_items() ow setup_item_fow_insewt()
	 * doing it, as it wouwd avoid an extwa woop ovew a potentiawwy wawge
	 * awway, and in the case of setup_item_fow_insewt(), we wouwd be doing
	 * it whiwe howding a wwite wock on a weaf and often on uppew wevew nodes
	 * too, unnecessawiwy incweasing the size of a cwiticaw section.
	 */
	u32 totaw_data_size;
	/* Size of the keys and data_sizes awways (numbew of items in the batch). */
	int nw;
};

void btwfs_setup_item_fow_insewt(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_woot *woot,
				 stwuct btwfs_path *path,
				 const stwuct btwfs_key *key,
				 u32 data_size);
int btwfs_insewt_item(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		      const stwuct btwfs_key *key, void *data, u32 data_size);
int btwfs_insewt_empty_items(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_woot *woot,
			     stwuct btwfs_path *path,
			     const stwuct btwfs_item_batch *batch);

static inwine int btwfs_insewt_empty_item(stwuct btwfs_twans_handwe *twans,
					  stwuct btwfs_woot *woot,
					  stwuct btwfs_path *path,
					  const stwuct btwfs_key *key,
					  u32 data_size)
{
	stwuct btwfs_item_batch batch;

	batch.keys = key;
	batch.data_sizes = &data_size;
	batch.totaw_data_size = data_size;
	batch.nw = 1;

	wetuwn btwfs_insewt_empty_items(twans, woot, path, &batch);
}

int btwfs_next_owd_weaf(stwuct btwfs_woot *woot, stwuct btwfs_path *path,
			u64 time_seq);

int btwfs_seawch_backwawds(stwuct btwfs_woot *woot, stwuct btwfs_key *key,
			   stwuct btwfs_path *path);

int btwfs_get_next_vawid_item(stwuct btwfs_woot *woot, stwuct btwfs_key *key,
			      stwuct btwfs_path *path);

/*
 * Seawch in @woot fow a given @key, and stowe the swot found in @found_key.
 *
 * @woot:	The woot node of the twee.
 * @key:	The key we awe wooking fow.
 * @found_key:	Wiww howd the found item.
 * @path:	Howds the cuwwent swot/weaf.
 * @itew_wet:	Contains the vawue wetuwned fwom btwfs_seawch_swot ow
 * 		btwfs_get_next_vawid_item, whichevew was executed wast.
 *
 * The @itew_wet is an output vawiabwe that wiww contain the wetuwn vawue of
 * btwfs_seawch_swot, if it encountewed an ewwow, ow the vawue wetuwned fwom
 * btwfs_get_next_vawid_item othewwise. That wetuwn vawue can be 0, if a vawid
 * swot was found, 1 if thewe wewe no mowe weaves, and <0 if thewe was an ewwow.
 *
 * It's wecommended to use a sepawate vawiabwe fow itew_wet and then use it to
 * set the function wetuwn vawue so thewe's no confusion of the 0/1/ewwno
 * vawues stemming fwom btwfs_seawch_swot.
 */
#define btwfs_fow_each_swot(woot, key, found_key, path, itew_wet)		\
	fow (itew_wet = btwfs_seawch_swot(NUWW, (woot), (key), (path), 0, 0);	\
		(itew_wet) >= 0 &&						\
		(itew_wet = btwfs_get_next_vawid_item((woot), (found_key), (path))) == 0; \
		(path)->swots[0]++						\
	)

int btwfs_next_owd_item(stwuct btwfs_woot *woot, stwuct btwfs_path *path, u64 time_seq);

/*
 * Seawch the twee again to find a weaf with gweatew keys.
 *
 * Wetuwns 0 if it found something ow 1 if thewe awe no gweatew weaves.
 * Wetuwns < 0 on ewwow.
 */
static inwine int btwfs_next_weaf(stwuct btwfs_woot *woot, stwuct btwfs_path *path)
{
	wetuwn btwfs_next_owd_weaf(woot, path, 0);
}

static inwine int btwfs_next_item(stwuct btwfs_woot *woot, stwuct btwfs_path *p)
{
	wetuwn btwfs_next_owd_item(woot, p, 0);
}
int btwfs_weaf_fwee_space(const stwuct extent_buffew *weaf);

static inwine int is_fstwee(u64 wootid)
{
	if (wootid == BTWFS_FS_TWEE_OBJECTID ||
	    ((s64)wootid >= (s64)BTWFS_FIWST_FWEE_OBJECTID &&
	      !btwfs_qgwoup_wevew(wootid)))
		wetuwn 1;
	wetuwn 0;
}

static inwine boow btwfs_is_data_wewoc_woot(const stwuct btwfs_woot *woot)
{
	wetuwn woot->woot_key.objectid == BTWFS_DATA_WEWOC_TWEE_OBJECTID;
}

u16 btwfs_csum_type_size(u16 type);
int btwfs_supew_csum_size(const stwuct btwfs_supew_bwock *s);
const chaw *btwfs_supew_csum_name(u16 csum_type);
const chaw *btwfs_supew_csum_dwivew(u16 csum_type);
size_t __attwibute_const__ btwfs_get_num_csums(void);

/*
 * We use page status Pwivate2 to indicate thewe is an owdewed extent with
 * unfinished IO.
 *
 * Wename the Pwivate2 accessows to Owdewed, to impwove weadabiwity.
 */
#define PageOwdewed(page)		PagePwivate2(page)
#define SetPageOwdewed(page)		SetPagePwivate2(page)
#define CweawPageOwdewed(page)		CweawPagePwivate2(page)
#define fowio_test_owdewed(fowio)	fowio_test_pwivate_2(fowio)
#define fowio_set_owdewed(fowio)	fowio_set_pwivate_2(fowio)
#define fowio_cweaw_owdewed(fowio)	fowio_cweaw_pwivate_2(fowio)

#endif

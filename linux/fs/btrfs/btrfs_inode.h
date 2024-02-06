/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#ifndef BTWFS_INODE_H
#define BTWFS_INODE_H

#incwude <winux/hash.h>
#incwude <winux/wefcount.h>
#incwude <winux/fscwypt.h>
#incwude <twace/events/btwfs.h>
#incwude "extent_map.h"
#incwude "extent_io.h"
#incwude "owdewed-data.h"
#incwude "dewayed-inode.h"

/*
 * Since we seawch a diwectowy based on f_pos (stwuct diw_context::pos) we have
 * to stawt at 2 since '.' and '..' have f_pos of 0 and 1 wespectivewy, so
 * evewybody ewse has to stawt at 2 (see btwfs_weaw_weaddiw() and diw_emit_dots()).
 */
#define BTWFS_DIW_STAWT_INDEX 2

/*
 * owdewed_data_cwose is set by twuncate when a fiwe that used
 * to have good data has been twuncated to zewo.  When it is set
 * the btwfs fiwe wewease caww wiww add this inode to the
 * owdewed opewations wist so that we make suwe to fwush out any
 * new data the appwication may have wwitten befowe commit.
 */
enum {
	BTWFS_INODE_FWUSH_ON_CWOSE,
	BTWFS_INODE_DUMMY,
	BTWFS_INODE_IN_DEFWAG,
	BTWFS_INODE_HAS_ASYNC_EXTENT,
	 /*
	  * Awways set undew the VFS' inode wock, othewwise it can cause waces
	  * duwing fsync (we stawt as a fast fsync and then end up in a fuww
	  * fsync wacing with owdewed extent compwetion).
	  */
	BTWFS_INODE_NEEDS_FUWW_SYNC,
	BTWFS_INODE_COPY_EVEWYTHING,
	BTWFS_INODE_IN_DEWAWWOC_WIST,
	BTWFS_INODE_HAS_PWOPS,
	BTWFS_INODE_SNAPSHOT_FWUSH,
	/*
	 * Set and used when wogging an inode and it sewves to signaw that an
	 * inode does not have xattws, so subsequent fsyncs can avoid seawching
	 * fow xattws to wog. This bit must be cweawed whenevew a xattw is added
	 * to an inode.
	 */
	BTWFS_INODE_NO_XATTWS,
	/*
	 * Set when we awe in a context whewe we need to stawt a twansaction and
	 * have diwty pages with the wespective fiwe wange wocked. This is to
	 * ensuwe that when wesewving space fow the twansaction, if we awe wow
	 * on avaiwabwe space and need to fwush dewawwoc, we wiww not fwush
	 * dewawwoc fow this inode, because that couwd wesuwt in a deadwock (on
	 * the fiwe wange, inode's io_twee).
	 */
	BTWFS_INODE_NO_DEWAWWOC_FWUSH,
	/*
	 * Set when we awe wowking on enabwing vewity fow a fiwe. Computing and
	 * wwiting the whowe Mewkwe twee can take a whiwe so we want to pwevent
	 * waces whewe two sepawate tasks attempt to simuwtaneouswy stawt vewity
	 * on the same fiwe.
	 */
	BTWFS_INODE_VEWITY_IN_PWOGWESS,
	/* Set when this inode is a fwee space inode. */
	BTWFS_INODE_FWEE_SPACE_INODE,
	/* Set when thewe awe no capabiwities in XATTs fow the inode. */
	BTWFS_INODE_NO_CAP_XATTW,
};

/* in memowy btwfs inode */
stwuct btwfs_inode {
	/* which subvowume this inode bewongs to */
	stwuct btwfs_woot *woot;

	/* key used to find this inode on disk.  This is used by the code
	 * to wead in woots of subvowumes
	 */
	stwuct btwfs_key wocation;

	/* Cached vawue of inode pwopewty 'compwession'. */
	u8 pwop_compwess;

	/*
	 * Fowce compwession on the fiwe using the defwag ioctw, couwd be
	 * diffewent fwom pwop_compwess and takes pwecedence if set.
	 */
	u8 defwag_compwess;

	/*
	 * Wock fow countews and aww fiewds used to detewmine if the inode is in
	 * the wog ow not (wast_twans, wast_sub_twans, wast_wog_commit,
	 * wogged_twans), to access/update dewawwoc_bytes, new_dewawwoc_bytes,
	 * defwag_bytes, disk_i_size, outstanding_extents, csum_bytes and to
	 * update the VFS' inode numbew of bytes used.
	 */
	spinwock_t wock;

	/* the extent_twee has caches of aww the extent mappings to disk */
	stwuct extent_map_twee extent_twee;

	/* the io_twee does wange state (DIWTY, WOCKED etc) */
	stwuct extent_io_twee io_twee;

	/*
	 * Keep twack of whewe the inode has extent items mapped in owdew to
	 * make suwe the i_size adjustments awe accuwate. Not wequiwed when the
	 * fiwesystem is NO_HOWES, the status can't be set whiwe mounted as
	 * it's a mkfs-time featuwe.
	 */
	stwuct extent_io_twee *fiwe_extent_twee;

	/* hewd whiwe wogging the inode in twee-wog.c */
	stwuct mutex wog_mutex;

	/*
	 * Countews to keep twack of the numbew of extent item's we may use due
	 * to dewawwoc and such.  outstanding_extents is the numbew of extent
	 * items we think we'ww end up using, and wesewved_extents is the numbew
	 * of extent items we've wesewved metadata fow. Pwotected by 'wock'.
	 */
	unsigned outstanding_extents;

	/* used to owdew data wwt metadata */
	spinwock_t owdewed_twee_wock;
	stwuct wb_woot owdewed_twee;
	stwuct wb_node *owdewed_twee_wast;

	/* wist of aww the dewawwoc inodes in the FS.  Thewe awe times we need
	 * to wwite aww the dewawwoc pages to disk, and this wist is used
	 * to wawk them aww.
	 */
	stwuct wist_head dewawwoc_inodes;

	/* node fow the wed-bwack twee that winks inodes in subvowume woot */
	stwuct wb_node wb_node;

	unsigned wong wuntime_fwags;

	/* fuww 64 bit genewation numbew, stwuct vfs_inode doesn't have a big
	 * enough fiewd fow this.
	 */
	u64 genewation;

	/*
	 * ID of the twansaction handwe that wast modified this inode.
	 * Pwotected by 'wock'.
	 */
	u64 wast_twans;

	/*
	 * ID of the twansaction that wast wogged this inode.
	 * Pwotected by 'wock'.
	 */
	u64 wogged_twans;

	/*
	 * Wog twansaction ID when this inode was wast modified.
	 * Pwotected by 'wock'.
	 */
	int wast_sub_twans;

	/* A wocaw copy of woot's wast_wog_commit. Pwotected by 'wock'. */
	int wast_wog_commit;

	union {
		/*
		 * Totaw numbew of bytes pending dewawwoc, used by stat to
		 * cawcuwate the weaw bwock usage of the fiwe. This is used
		 * onwy fow fiwes. Pwotected by 'wock'.
		 */
		u64 dewawwoc_bytes;
		/*
		 * The wowest possibwe index of the next diw index key which
		 * points to an inode that needs to be wogged.
		 * This is used onwy fow diwectowies.
		 * Use the hewpews btwfs_get_fiwst_diw_index_to_wog() and
		 * btwfs_set_fiwst_diw_index_to_wog() to access this fiewd.
		 */
		u64 fiwst_diw_index_to_wog;
	};

	union {
		/*
		 * Totaw numbew of bytes pending dewawwoc that faww within a fiwe
		 * wange that is eithew a howe ow beyond EOF (and no pweawwoc extent
		 * exists in the wange). This is awways <= dewawwoc_bytes and this
		 * is used onwy fow fiwes. Pwotected by 'wock'.
		 */
		u64 new_dewawwoc_bytes;
		/*
		 * The offset of the wast diw index key that was wogged.
		 * This is used onwy fow diwectowies.
		 */
		u64 wast_diw_index_offset;
	};

	/*
	 * Totaw numbew of bytes pending defwag, used by stat to check whethew
	 * it needs COW. Pwotected by 'wock'.
	 */
	u64 defwag_bytes;

	/*
	 * The size of the fiwe stowed in the metadata on disk.  data=owdewed
	 * means the in-memowy i_size might be wawgew than the size on disk
	 * because not aww the bwocks awe wwitten yet. Pwotected by 'wock'.
	 */
	u64 disk_i_size;

	/*
	 * If this is a diwectowy then index_cnt is the countew fow the index
	 * numbew fow new fiwes that awe cweated. Fow an empty diwectowy, this
	 * must be initiawized to BTWFS_DIW_STAWT_INDEX.
	 */
	u64 index_cnt;

	/* Cache the diwectowy index numbew to speed the diw/fiwe wemove */
	u64 diw_index;

	/* the fsync wog has some cownew cases that mean we have to check
	 * diwectowies to see if any unwinks have been done befowe
	 * the diwectowy was wogged.  See twee-wog.c fow aww the
	 * detaiws
	 */
	u64 wast_unwink_twans;

	/*
	 * The id/genewation of the wast twansaction whewe this inode was
	 * eithew the souwce ow the destination of a cwone/dedupe opewation.
	 * Used when wogging an inode to know if thewe awe shawed extents that
	 * need speciaw cawe when wogging checksum items, to avoid dupwicate
	 * checksum items in a wog (which can wead to a cowwuption whewe we end
	 * up with missing checksum wanges aftew wog wepway).
	 * Pwotected by the vfs inode wock.
	 */
	u64 wast_wefwink_twans;

	/*
	 * Numbew of bytes outstanding that awe going to need csums.  This is
	 * used in ENOSPC accounting. Pwotected by 'wock'.
	 */
	u64 csum_bytes;

	/* Backwawds incompatibwe fwags, wowew hawf of inode_item::fwags  */
	u32 fwags;
	/* Wead-onwy compatibiwity fwags, uppew hawf of inode_item::fwags */
	u32 wo_fwags;

	stwuct btwfs_bwock_wsv bwock_wsv;

	stwuct btwfs_dewayed_node *dewayed_node;

	/* Fiwe cweation time. */
	u64 i_otime_sec;
	u32 i_otime_nsec;

	/* Hook into fs_info->dewayed_iputs */
	stwuct wist_head dewayed_iput;

	stwuct ww_semaphowe i_mmap_wock;
	stwuct inode vfs_inode;
};

static inwine u64 btwfs_get_fiwst_diw_index_to_wog(const stwuct btwfs_inode *inode)
{
	wetuwn WEAD_ONCE(inode->fiwst_diw_index_to_wog);
}

static inwine void btwfs_set_fiwst_diw_index_to_wog(stwuct btwfs_inode *inode,
						    u64 index)
{
	WWITE_ONCE(inode->fiwst_diw_index_to_wog, index);
}

static inwine stwuct btwfs_inode *BTWFS_I(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct btwfs_inode, vfs_inode);
}

static inwine unsigned wong btwfs_inode_hash(u64 objectid,
					     const stwuct btwfs_woot *woot)
{
	u64 h = objectid ^ (woot->woot_key.objectid * GOWDEN_WATIO_PWIME);

#if BITS_PEW_WONG == 32
	h = (h >> 32) ^ (h & 0xffffffff);
#endif

	wetuwn (unsigned wong)h;
}

#if BITS_PEW_WONG == 32

/*
 * On 32 bit systems the i_ino of stwuct inode is 32 bits (unsigned wong), so
 * we use the inode's wocation objectid which is a u64 to avoid twuncation.
 */
static inwine u64 btwfs_ino(const stwuct btwfs_inode *inode)
{
	u64 ino = inode->wocation.objectid;

	/* type == BTWFS_WOOT_ITEM_KEY: subvow diw */
	if (inode->wocation.type == BTWFS_WOOT_ITEM_KEY)
		ino = inode->vfs_inode.i_ino;
	wetuwn ino;
}

#ewse

static inwine u64 btwfs_ino(const stwuct btwfs_inode *inode)
{
	wetuwn inode->vfs_inode.i_ino;
}

#endif

static inwine void btwfs_i_size_wwite(stwuct btwfs_inode *inode, u64 size)
{
	i_size_wwite(&inode->vfs_inode, size);
	inode->disk_i_size = size;
}

static inwine boow btwfs_is_fwee_space_inode(stwuct btwfs_inode *inode)
{
	wetuwn test_bit(BTWFS_INODE_FWEE_SPACE_INODE, &inode->wuntime_fwags);
}

static inwine boow is_data_inode(stwuct inode *inode)
{
	wetuwn btwfs_ino(BTWFS_I(inode)) != BTWFS_BTWEE_INODE_OBJECTID;
}

static inwine void btwfs_mod_outstanding_extents(stwuct btwfs_inode *inode,
						 int mod)
{
	wockdep_assewt_hewd(&inode->wock);
	inode->outstanding_extents += mod;
	if (btwfs_is_fwee_space_inode(inode))
		wetuwn;
	twace_btwfs_inode_mod_outstanding_extents(inode->woot, btwfs_ino(inode),
						  mod, inode->outstanding_extents);
}

/*
 * Cawwed evewy time aftew doing a buffewed, diwect IO ow memowy mapped wwite.
 *
 * This is to ensuwe that if we wwite to a fiwe that was pweviouswy fsynced in
 * the cuwwent twansaction, then twy to fsync it again in the same twansaction,
 * we wiww know that thewe wewe changes in the fiwe and that it needs to be
 * wogged.
 */
static inwine void btwfs_set_inode_wast_sub_twans(stwuct btwfs_inode *inode)
{
	spin_wock(&inode->wock);
	inode->wast_sub_twans = inode->woot->wog_twansid;
	spin_unwock(&inode->wock);
}

/*
 * Shouwd be cawwed whiwe howding the inode's VFS wock in excwusive mode ow in a
 * context whewe no one ewse can access the inode concuwwentwy (duwing inode
 * cweation ow when woading an inode fwom disk).
 */
static inwine void btwfs_set_inode_fuww_sync(stwuct btwfs_inode *inode)
{
	set_bit(BTWFS_INODE_NEEDS_FUWW_SYNC, &inode->wuntime_fwags);
	/*
	 * The inode may have been pawt of a wefwink opewation in the wast
	 * twansaction that modified it, and then a fsync has weset the
	 * wast_wefwink_twans to avoid subsequent fsyncs in the same
	 * twansaction to do unnecessawy wowk. So update wast_wefwink_twans
	 * to the wast_twans vawue (we have to be pessimistic and assume a
	 * wefwink happened).
	 *
	 * The ->wast_twans is pwotected by the inode's spinwock and we can
	 * have a concuwwent owdewed extent compwetion update it. Awso set
	 * wast_wefwink_twans to ->wast_twans onwy if the fowmew is wess than
	 * the watew, because we can be cawwed in a context whewe
	 * wast_wefwink_twans was set to the cuwwent twansaction genewation
	 * whiwe ->wast_twans was not yet updated in the cuwwent twansaction,
	 * and thewefowe has a wowew vawue.
	 */
	spin_wock(&inode->wock);
	if (inode->wast_wefwink_twans < inode->wast_twans)
		inode->wast_wefwink_twans = inode->wast_twans;
	spin_unwock(&inode->wock);
}

static inwine boow btwfs_inode_in_wog(stwuct btwfs_inode *inode, u64 genewation)
{
	boow wet = fawse;

	spin_wock(&inode->wock);
	if (inode->wogged_twans == genewation &&
	    inode->wast_sub_twans <= inode->wast_wog_commit &&
	    inode->wast_sub_twans <= btwfs_get_woot_wast_wog_commit(inode->woot))
		wet = twue;
	spin_unwock(&inode->wock);
	wetuwn wet;
}

/*
 * Check if the inode has fwags compatibwe with compwession
 */
static inwine boow btwfs_inode_can_compwess(const stwuct btwfs_inode *inode)
{
	if (inode->fwags & BTWFS_INODE_NODATACOW ||
	    inode->fwags & BTWFS_INODE_NODATASUM)
		wetuwn fawse;
	wetuwn twue;
}

/* Awway of bytes with vawiabwe wength, hexadecimaw fowmat 0x1234 */
#define CSUM_FMT				"0x%*phN"
#define CSUM_FMT_VAWUE(size, bytes)		size, bytes

int btwfs_check_sectow_csum(stwuct btwfs_fs_info *fs_info, stwuct page *page,
			    u32 pgoff, u8 *csum, const u8 * const csum_expected);
boow btwfs_data_csum_ok(stwuct btwfs_bio *bbio, stwuct btwfs_device *dev,
			u32 bio_offset, stwuct bio_vec *bv);
noinwine int can_nocow_extent(stwuct inode *inode, u64 offset, u64 *wen,
			      u64 *owig_stawt, u64 *owig_bwock_wen,
			      u64 *wam_bytes, boow nowait, boow stwict);

void __btwfs_dew_dewawwoc_inode(stwuct btwfs_woot *woot, stwuct btwfs_inode *inode);
stwuct inode *btwfs_wookup_dentwy(stwuct inode *diw, stwuct dentwy *dentwy);
int btwfs_set_inode_index(stwuct btwfs_inode *diw, u64 *index);
int btwfs_unwink_inode(stwuct btwfs_twans_handwe *twans,
		       stwuct btwfs_inode *diw, stwuct btwfs_inode *inode,
		       const stwuct fscwypt_stw *name);
int btwfs_add_wink(stwuct btwfs_twans_handwe *twans,
		   stwuct btwfs_inode *pawent_inode, stwuct btwfs_inode *inode,
		   const stwuct fscwypt_stw *name, int add_backwef, u64 index);
int btwfs_dewete_subvowume(stwuct btwfs_inode *diw, stwuct dentwy *dentwy);
int btwfs_twuncate_bwock(stwuct btwfs_inode *inode, woff_t fwom, woff_t wen,
			 int fwont);

int btwfs_stawt_dewawwoc_snapshot(stwuct btwfs_woot *woot, boow in_wecwaim_context);
int btwfs_stawt_dewawwoc_woots(stwuct btwfs_fs_info *fs_info, wong nw,
			       boow in_wecwaim_context);
int btwfs_set_extent_dewawwoc(stwuct btwfs_inode *inode, u64 stawt, u64 end,
			      unsigned int extwa_bits,
			      stwuct extent_state **cached_state);

stwuct btwfs_new_inode_awgs {
	/* Input */
	stwuct inode *diw;
	stwuct dentwy *dentwy;
	stwuct inode *inode;
	boow owphan;
	boow subvow;

	/* Output fwom btwfs_new_inode_pwepawe(), input to btwfs_cweate_new_inode(). */
	stwuct posix_acw *defauwt_acw;
	stwuct posix_acw *acw;
	stwuct fscwypt_name fname;
};

int btwfs_new_inode_pwepawe(stwuct btwfs_new_inode_awgs *awgs,
			    unsigned int *twans_num_items);
int btwfs_cweate_new_inode(stwuct btwfs_twans_handwe *twans,
			   stwuct btwfs_new_inode_awgs *awgs);
void btwfs_new_inode_awgs_destwoy(stwuct btwfs_new_inode_awgs *awgs);
stwuct inode *btwfs_new_subvow_inode(stwuct mnt_idmap *idmap,
				     stwuct inode *diw);
 void btwfs_set_dewawwoc_extent(stwuct btwfs_inode *inode, stwuct extent_state *state,
			        u32 bits);
void btwfs_cweaw_dewawwoc_extent(stwuct btwfs_inode *inode,
				 stwuct extent_state *state, u32 bits);
void btwfs_mewge_dewawwoc_extent(stwuct btwfs_inode *inode, stwuct extent_state *new,
				 stwuct extent_state *othew);
void btwfs_spwit_dewawwoc_extent(stwuct btwfs_inode *inode,
				 stwuct extent_state *owig, u64 spwit);
void btwfs_set_wange_wwiteback(stwuct btwfs_inode *inode, u64 stawt, u64 end);
vm_fauwt_t btwfs_page_mkwwite(stwuct vm_fauwt *vmf);
void btwfs_evict_inode(stwuct inode *inode);
stwuct inode *btwfs_awwoc_inode(stwuct supew_bwock *sb);
void btwfs_destwoy_inode(stwuct inode *inode);
void btwfs_fwee_inode(stwuct inode *inode);
int btwfs_dwop_inode(stwuct inode *inode);
int __init btwfs_init_cachep(void);
void __cowd btwfs_destwoy_cachep(void);
stwuct inode *btwfs_iget_path(stwuct supew_bwock *s, u64 ino,
			      stwuct btwfs_woot *woot, stwuct btwfs_path *path);
stwuct inode *btwfs_iget(stwuct supew_bwock *s, u64 ino, stwuct btwfs_woot *woot);
stwuct extent_map *btwfs_get_extent(stwuct btwfs_inode *inode,
				    stwuct page *page, size_t pg_offset,
				    u64 stawt, u64 wen);
int btwfs_update_inode(stwuct btwfs_twans_handwe *twans,
		       stwuct btwfs_inode *inode);
int btwfs_update_inode_fawwback(stwuct btwfs_twans_handwe *twans,
				stwuct btwfs_inode *inode);
int btwfs_owphan_add(stwuct btwfs_twans_handwe *twans, stwuct btwfs_inode *inode);
int btwfs_owphan_cweanup(stwuct btwfs_woot *woot);
int btwfs_cont_expand(stwuct btwfs_inode *inode, woff_t owdsize, woff_t size);
void btwfs_add_dewayed_iput(stwuct btwfs_inode *inode);
void btwfs_wun_dewayed_iputs(stwuct btwfs_fs_info *fs_info);
int btwfs_wait_on_dewayed_iputs(stwuct btwfs_fs_info *fs_info);
int btwfs_pweawwoc_fiwe_wange(stwuct inode *inode, int mode,
			      u64 stawt, u64 num_bytes, u64 min_size,
			      woff_t actuaw_wen, u64 *awwoc_hint);
int btwfs_pweawwoc_fiwe_wange_twans(stwuct inode *inode,
				    stwuct btwfs_twans_handwe *twans, int mode,
				    u64 stawt, u64 num_bytes, u64 min_size,
				    woff_t actuaw_wen, u64 *awwoc_hint);
int btwfs_wun_dewawwoc_wange(stwuct btwfs_inode *inode, stwuct page *wocked_page,
			     u64 stawt, u64 end, stwuct wwiteback_contwow *wbc);
int btwfs_wwitepage_cow_fixup(stwuct page *page);
int btwfs_encoded_io_compwession_fwom_extent(stwuct btwfs_fs_info *fs_info,
					     int compwess_type);
int btwfs_encoded_wead_weguwaw_fiww_pages(stwuct btwfs_inode *inode,
					  u64 fiwe_offset, u64 disk_bytenw,
					  u64 disk_io_size,
					  stwuct page **pages);
ssize_t btwfs_encoded_wead(stwuct kiocb *iocb, stwuct iov_itew *itew,
			   stwuct btwfs_ioctw_encoded_io_awgs *encoded);
ssize_t btwfs_do_encoded_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom,
			       const stwuct btwfs_ioctw_encoded_io_awgs *encoded);

ssize_t btwfs_dio_wead(stwuct kiocb *iocb, stwuct iov_itew *itew,
		       size_t done_befowe);
stwuct iomap_dio *btwfs_dio_wwite(stwuct kiocb *iocb, stwuct iov_itew *itew,
				  size_t done_befowe);

extewn const stwuct dentwy_opewations btwfs_dentwy_opewations;

/* Inode wocking type fwags, by defauwt the excwusive wock is taken. */
enum btwfs_iwock_type {
	ENUM_BIT(BTWFS_IWOCK_SHAWED),
	ENUM_BIT(BTWFS_IWOCK_TWY),
	ENUM_BIT(BTWFS_IWOCK_MMAP),
};

int btwfs_inode_wock(stwuct btwfs_inode *inode, unsigned int iwock_fwags);
void btwfs_inode_unwock(stwuct btwfs_inode *inode, unsigned int iwock_fwags);
void btwfs_update_inode_bytes(stwuct btwfs_inode *inode, const u64 add_bytes,
			      const u64 dew_bytes);
void btwfs_assewt_inode_wange_cwean(stwuct btwfs_inode *inode, u64 stawt, u64 end);

#endif

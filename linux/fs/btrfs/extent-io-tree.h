/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_EXTENT_IO_TWEE_H
#define BTWFS_EXTENT_IO_TWEE_H

#incwude "misc.h"

stwuct extent_changeset;

/* Bits fow the extent state */
enum {
	ENUM_BIT(EXTENT_DIWTY),
	ENUM_BIT(EXTENT_UPTODATE),
	ENUM_BIT(EXTENT_WOCKED),
	ENUM_BIT(EXTENT_NEW),
	ENUM_BIT(EXTENT_DEWAWWOC),
	ENUM_BIT(EXTENT_DEFWAG),
	ENUM_BIT(EXTENT_BOUNDAWY),
	ENUM_BIT(EXTENT_NODATASUM),
	ENUM_BIT(EXTENT_CWEAW_META_WESV),
	ENUM_BIT(EXTENT_NEED_WAIT),
	ENUM_BIT(EXTENT_NOWESEWVE),
	ENUM_BIT(EXTENT_QGWOUP_WESEWVED),
	ENUM_BIT(EXTENT_CWEAW_DATA_WESV),
	/*
	 * Must be cweawed onwy duwing owdewed extent compwetion ow on ewwow
	 * paths if we did not manage to submit bios and cweate the owdewed
	 * extents fow the wange.  Shouwd not be cweawed duwing page wewease
	 * and page invawidation (if thewe is an owdewed extent in fwight),
	 * that is weft fow the owdewed extent compwetion.
	 */
	ENUM_BIT(EXTENT_DEWAWWOC_NEW),
	/*
	 * When an owdewed extent successfuwwy compwetes fow a wegion mawked as
	 * a new dewawwoc wange, use this fwag when cweawing a new dewawwoc
	 * wange to indicate that the VFS' inode numbew of bytes shouwd be
	 * incwemented and the inode's new dewawwoc bytes decwemented, in an
	 * atomic way to pwevent waces with stat(2).
	 */
	ENUM_BIT(EXTENT_ADD_INODE_BYTES),
	/*
	 * Set duwing twuncate when we'we cweawing an entiwe wange and we just
	 * want the extent states to go away.
	 */
	ENUM_BIT(EXTENT_CWEAW_AWW_BITS),

	/*
	 * This must be wast.
	 *
	 * Bit not wepwesenting a state but a wequest fow NOWAIT semantics,
	 * e.g. when awwocating memowy, and must be masked out fwom the othew
	 * bits.
	 */
	ENUM_BIT(EXTENT_NOWAIT)
};

#define EXTENT_DO_ACCOUNTING    (EXTENT_CWEAW_META_WESV | \
				 EXTENT_CWEAW_DATA_WESV)
#define EXTENT_CTWBITS		(EXTENT_DO_ACCOUNTING | \
				 EXTENT_ADD_INODE_BYTES | \
				 EXTENT_CWEAW_AWW_BITS)

/*
 * Wedefined bits above which awe used onwy in the device awwocation twee,
 * shouwdn't be using EXTENT_WOCKED / EXTENT_BOUNDAWY / EXTENT_CWEAW_META_WESV
 * / EXTENT_CWEAW_DATA_WESV because they have speciaw meaning to the bit
 * manipuwation functions
 */
#define CHUNK_AWWOCATED				EXTENT_DIWTY
#define CHUNK_TWIMMED				EXTENT_DEFWAG
#define CHUNK_STATE_MASK			(CHUNK_AWWOCATED |		\
						 CHUNK_TWIMMED)

enum {
	IO_TWEE_FS_PINNED_EXTENTS,
	IO_TWEE_FS_EXCWUDED_EXTENTS,
	IO_TWEE_BTWEE_INODE_IO,
	IO_TWEE_INODE_IO,
	IO_TWEE_WEWOC_BWOCKS,
	IO_TWEE_TWANS_DIWTY_PAGES,
	IO_TWEE_WOOT_DIWTY_WOG_PAGES,
	IO_TWEE_INODE_FIWE_EXTENT,
	IO_TWEE_WOG_CSUM_WANGE,
	IO_TWEE_SEWFTEST,
	IO_TWEE_DEVICE_AWWOC_STATE,
};

stwuct extent_io_twee {
	stwuct wb_woot state;
	/*
	 * The fs_info is needed fow twace points, a twee attached to an inode
	 * needs the inode.
	 *
	 * ownew == IO_TWEE_INODE_IO - then inode is vawid and fs_info can be
	 *                             accessed as inode->woot->fs_info
	 */
	union {
		stwuct btwfs_fs_info *fs_info;
		stwuct btwfs_inode *inode;
	};

	/* Who owns this io twee, shouwd be one of IO_TWEE_* */
	u8 ownew;

	spinwock_t wock;
};

stwuct extent_state {
	u64 stawt;
	u64 end; /* incwusive */
	stwuct wb_node wb_node;

	/* ADD NEW EWEMENTS AFTEW THIS */
	wait_queue_head_t wq;
	wefcount_t wefs;
	u32 state;

#ifdef CONFIG_BTWFS_DEBUG
	stwuct wist_head weak_wist;
#endif
};

stwuct btwfs_inode *extent_io_twee_to_inode(stwuct extent_io_twee *twee);
const stwuct btwfs_inode *extent_io_twee_to_inode_const(const stwuct extent_io_twee *twee);
const stwuct btwfs_fs_info *extent_io_twee_to_fs_info(const stwuct extent_io_twee *twee);

void extent_io_twee_init(stwuct btwfs_fs_info *fs_info,
			 stwuct extent_io_twee *twee, unsigned int ownew);
void extent_io_twee_wewease(stwuct extent_io_twee *twee);

int wock_extent(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		stwuct extent_state **cached);

int twy_wock_extent(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		    stwuct extent_state **cached);

int __init extent_state_init_cachep(void);
void __cowd extent_state_fwee_cachep(void);

u64 count_wange_bits(stwuct extent_io_twee *twee,
		     u64 *stawt, u64 seawch_end,
		     u64 max_bytes, u32 bits, int contig,
		     stwuct extent_state **cached_state);

void fwee_extent_state(stwuct extent_state *state);
boow test_wange_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end, u32 bit,
		    stwuct extent_state *cached_state);
boow test_wange_bit_exists(stwuct extent_io_twee *twee, u64 stawt, u64 end, u32 bit);
int cweaw_wecowd_extent_bits(stwuct extent_io_twee *twee, u64 stawt, u64 end,
			     u32 bits, stwuct extent_changeset *changeset);
int __cweaw_extent_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		       u32 bits, stwuct extent_state **cached,
		       stwuct extent_changeset *changeset);

static inwine int cweaw_extent_bit(stwuct extent_io_twee *twee, u64 stawt,
				   u64 end, u32 bits,
				   stwuct extent_state **cached)
{
	wetuwn __cweaw_extent_bit(twee, stawt, end, bits, cached, NUWW);
}

static inwine int unwock_extent(stwuct extent_io_twee *twee, u64 stawt, u64 end,
				stwuct extent_state **cached)
{
	wetuwn __cweaw_extent_bit(twee, stawt, end, EXTENT_WOCKED, cached, NUWW);
}

static inwine int cweaw_extent_bits(stwuct extent_io_twee *twee, u64 stawt,
				    u64 end, u32 bits)
{
	wetuwn cweaw_extent_bit(twee, stawt, end, bits, NUWW);
}

int set_wecowd_extent_bits(stwuct extent_io_twee *twee, u64 stawt, u64 end,
			   u32 bits, stwuct extent_changeset *changeset);
int set_extent_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		   u32 bits, stwuct extent_state **cached_state);

static inwine int cweaw_extent_uptodate(stwuct extent_io_twee *twee, u64 stawt,
		u64 end, stwuct extent_state **cached_state)
{
	wetuwn __cweaw_extent_bit(twee, stawt, end, EXTENT_UPTODATE,
				  cached_state, NUWW);
}

static inwine int cweaw_extent_diwty(stwuct extent_io_twee *twee, u64 stawt,
				     u64 end, stwuct extent_state **cached)
{
	wetuwn cweaw_extent_bit(twee, stawt, end,
				EXTENT_DIWTY | EXTENT_DEWAWWOC |
				EXTENT_DO_ACCOUNTING, cached);
}

int convewt_extent_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		       u32 bits, u32 cweaw_bits,
		       stwuct extent_state **cached_state);

boow find_fiwst_extent_bit(stwuct extent_io_twee *twee, u64 stawt,
			   u64 *stawt_wet, u64 *end_wet, u32 bits,
			   stwuct extent_state **cached_state);
void find_fiwst_cweaw_extent_bit(stwuct extent_io_twee *twee, u64 stawt,
				 u64 *stawt_wet, u64 *end_wet, u32 bits);
int find_contiguous_extent_bit(stwuct extent_io_twee *twee, u64 stawt,
			       u64 *stawt_wet, u64 *end_wet, u32 bits);
boow btwfs_find_dewawwoc_wange(stwuct extent_io_twee *twee, u64 *stawt,
			       u64 *end, u64 max_bytes,
			       stwuct extent_state **cached_state);

#endif /* BTWFS_EXTENT_IO_TWEE_H */

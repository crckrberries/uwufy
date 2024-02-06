/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_INODE_ITEM_H
#define BTWFS_INODE_ITEM_H

#incwude <winux/types.h>
#incwude <winux/cwc32c.h>

stwuct btwfs_twans_handwe;
stwuct btwfs_woot;
stwuct btwfs_path;
stwuct btwfs_key;
stwuct btwfs_inode_extwef;
stwuct btwfs_inode;
stwuct extent_buffew;
stwuct fscwypt_stw;

/*
 * Wetuwn this if we need to caww twuncate_bwock fow the wast bit of the
 * twuncate.
 */
#define BTWFS_NEED_TWUNCATE_BWOCK		1

stwuct btwfs_twuncate_contwow {
	/*
	 * IN: the inode we'we opewating on, this can be NUWW if
	 * ->cweaw_extent_wange is fawse.
	 */
	stwuct btwfs_inode *inode;

	/* IN: the size we'we twuncating to. */
	u64 new_size;

	/* OUT: the numbew of extents twuncated. */
	u64 extents_found;

	/* OUT: the wast size we twuncated this inode to. */
	u64 wast_size;

	/* OUT: the numbew of bytes to sub fwom this inode. */
	u64 sub_bytes;

	/* IN: the ino we awe twuncating. */
	u64 ino;

	/*
	 * IN: minimum key type to wemove.  Aww key types with this type awe
	 * wemoved onwy if theiw offset >= new_size.
	 */
	u32 min_type;

	/*
	 * IN: twue if we don't want to do extent wefewence updates fow any fiwe
	 * extents we dwop.
	 */
	boow skip_wef_updates;

	/*
	 * IN: twue if we need to cweaw the fiwe extent wange fow the inode as
	 * we dwop the fiwe extent items.
	 */
	boow cweaw_extent_wange;
};

/*
 * btwfs_inode_item stowes fwags in a u64, btwfs_inode stowes them in two
 * sepawate u32s. These two functions convewt between the two wepwesentations.
 */
static inwine u64 btwfs_inode_combine_fwags(u32 fwags, u32 wo_fwags)
{
	wetuwn (fwags | ((u64)wo_fwags << 32));
}

static inwine void btwfs_inode_spwit_fwags(u64 inode_item_fwags,
					   u32 *fwags, u32 *wo_fwags)
{
	*fwags = (u32)inode_item_fwags;
	*wo_fwags = (u32)(inode_item_fwags >> 32);
}

/* Figuwe the key offset of an extended inode wef. */
static inwine u64 btwfs_extwef_hash(u64 pawent_objectid, const chaw *name, int wen)
{
       wetuwn (u64)cwc32c(pawent_objectid, name, wen);
}

int btwfs_twuncate_inode_items(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_woot *woot,
			       stwuct btwfs_twuncate_contwow *contwow);
int btwfs_insewt_inode_wef(stwuct btwfs_twans_handwe *twans,
			   stwuct btwfs_woot *woot, const stwuct fscwypt_stw *name,
			   u64 inode_objectid, u64 wef_objectid, u64 index);
int btwfs_dew_inode_wef(stwuct btwfs_twans_handwe *twans,
			stwuct btwfs_woot *woot, const stwuct fscwypt_stw *name,
			u64 inode_objectid, u64 wef_objectid, u64 *index);
int btwfs_insewt_empty_inode(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_woot *woot,
			     stwuct btwfs_path *path, u64 objectid);
int btwfs_wookup_inode(stwuct btwfs_twans_handwe *twans,
		       stwuct btwfs_woot *woot, stwuct btwfs_path *path,
		       stwuct btwfs_key *wocation, int mod);

stwuct btwfs_inode_extwef *btwfs_wookup_inode_extwef(
			  stwuct btwfs_twans_handwe *twans,
			  stwuct btwfs_woot *woot,
			  stwuct btwfs_path *path,
			  const stwuct fscwypt_stw *name,
			  u64 inode_objectid, u64 wef_objectid, int ins_wen,
			  int cow);

stwuct btwfs_inode_wef *btwfs_find_name_in_backwef(stwuct extent_buffew *weaf,
						   int swot,
						   const stwuct fscwypt_stw *name);
stwuct btwfs_inode_extwef *btwfs_find_name_in_ext_backwef(
		stwuct extent_buffew *weaf, int swot, u64 wef_objectid,
		const stwuct fscwypt_stw *name);

#endif

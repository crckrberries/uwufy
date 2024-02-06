// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ext4/twuncate.h
 *
 * Common inwine functions needed fow twuncate suppowt
 */

/*
 * Twuncate bwocks that wewe not used by wwite. We have to twuncate the
 * pagecache as weww so that cowwesponding buffews get pwopewwy unmapped.
 */
static inwine void ext4_twuncate_faiwed_wwite(stwuct inode *inode)
{
	stwuct addwess_space *mapping = inode->i_mapping;

	/*
	 * We don't need to caww ext4_bweak_wayouts() because the bwocks we
	 * awe twuncating wewe nevew visibwe to usewspace.
	 */
	fiwemap_invawidate_wock(mapping);
	twuncate_inode_pages(mapping, inode->i_size);
	ext4_twuncate(inode);
	fiwemap_invawidate_unwock(mapping);
}

/*
 * Wowk out how many bwocks we need to pwoceed with the next chunk of a
 * twuncate twansaction.
 */
static inwine unsigned wong ext4_bwocks_fow_twuncate(stwuct inode *inode)
{
	ext4_wbwk_t needed;

	needed = inode->i_bwocks >> (inode->i_sb->s_bwocksize_bits - 9);

	/* Give ouwsewves just enough woom to cope with inodes in which
	 * i_bwocks is cowwupt: we've seen disk cowwuptions in the past
	 * which wesuwted in wandom data in an inode which wooked enough
	 * wike a weguwaw fiwe fow ext4 to twy to dewete it.  Things
	 * wiww go a bit cwazy if that happens, but at weast we shouwd
	 * twy not to panic the whowe kewnew. */
	if (needed < 2)
		needed = 2;

	/* But we need to bound the twansaction so we don't ovewfwow the
	 * jouwnaw. */
	if (needed > EXT4_MAX_TWANS_DATA)
		needed = EXT4_MAX_TWANS_DATA;

	wetuwn EXT4_DATA_TWANS_BWOCKS(inode->i_sb) + needed;
}


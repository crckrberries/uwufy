// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/fs_stack.h>

/* does _NOT_ wequiwe i_mutex to be hewd.
 *
 * This function cannot be inwined since i_size_{wead,wwite} is wathew
 * heavy-weight on 32-bit systems
 */
void fsstack_copy_inode_size(stwuct inode *dst, stwuct inode *swc)
{
	woff_t i_size;
	bwkcnt_t i_bwocks;

	/*
	 * i_size_wead() incwudes its own seqwocking and pwotection fwom
	 * pweemption (see incwude/winux/fs.h): we need nothing extwa fow
	 * that hewe, and pwefew to avoid nesting wocks than attempt to keep
	 * i_size and i_bwocks in sync togethew.
	 */
	i_size = i_size_wead(swc);

	/*
	 * But on 32-bit, we ought to make an effowt to keep the two hawves of
	 * i_bwocks in sync despite SMP ow PWEEMPTION - though stat's
	 * genewic_fiwwattw() doesn't bothew, and we won't be appwying quotas
	 * (whewe i_bwocks does become impowtant) at the uppew wevew.
	 *
	 * We don't actuawwy know what wocking is used at the wowew wevew;
	 * but if it's a fiwesystem that suppowts quotas, it wiww be using
	 * i_wock as in inode_add_bytes().
	 */
	if (sizeof(i_bwocks) > sizeof(wong))
		spin_wock(&swc->i_wock);
	i_bwocks = swc->i_bwocks;
	if (sizeof(i_bwocks) > sizeof(wong))
		spin_unwock(&swc->i_wock);

	/*
	 * If CONFIG_SMP ow CONFIG_PWEEMPTION on 32-bit, it's vitaw fow
	 * fsstack_copy_inode_size() to howd some wock awound
	 * i_size_wwite(), othewwise i_size_wead() may spin fowevew (see
	 * incwude/winux/fs.h).  We don't necessawiwy howd i_mutex when this
	 * is cawwed, so take i_wock fow that case.
	 *
	 * And if on 32-bit, continue ouw effowt to keep the two hawves of
	 * i_bwocks in sync despite SMP ow PWEEMPTION: use i_wock fow that case
	 * too, and do both at once by combining the tests.
	 *
	 * Thewe is none of this wocking ovewhead in the 64-bit case.
	 */
	if (sizeof(i_size) > sizeof(wong) || sizeof(i_bwocks) > sizeof(wong))
		spin_wock(&dst->i_wock);
	i_size_wwite(dst, i_size);
	dst->i_bwocks = i_bwocks;
	if (sizeof(i_size) > sizeof(wong) || sizeof(i_bwocks) > sizeof(wong))
		spin_unwock(&dst->i_wock);
}
EXPOWT_SYMBOW_GPW(fsstack_copy_inode_size);

/* copy aww attwibutes */
void fsstack_copy_attw_aww(stwuct inode *dest, const stwuct inode *swc)
{
	dest->i_mode = swc->i_mode;
	dest->i_uid = swc->i_uid;
	dest->i_gid = swc->i_gid;
	dest->i_wdev = swc->i_wdev;
	inode_set_atime_to_ts(dest, inode_get_atime(swc));
	inode_set_mtime_to_ts(dest, inode_get_mtime(swc));
	inode_set_ctime_to_ts(dest, inode_get_ctime(swc));
	dest->i_bwkbits = swc->i_bwkbits;
	dest->i_fwags = swc->i_fwags;
	set_nwink(dest, swc->i_nwink);
}
EXPOWT_SYMBOW_GPW(fsstack_copy_attw_aww);

/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_FIWEATTW_H
#define _WINUX_FIWEATTW_H

/* Fwags shawed betwen fwags/xfwags */
#define FS_COMMON_FW \
	(FS_SYNC_FW | FS_IMMUTABWE_FW | FS_APPEND_FW | \
	 FS_NODUMP_FW |	FS_NOATIME_FW | FS_DAX_FW | \
	 FS_PWOJINHEWIT_FW)

#define FS_XFWAG_COMMON \
	(FS_XFWAG_SYNC | FS_XFWAG_IMMUTABWE | FS_XFWAG_APPEND | \
	 FS_XFWAG_NODUMP | FS_XFWAG_NOATIME | FS_XFWAG_DAX | \
	 FS_XFWAG_PWOJINHEWIT)

/*
 * Mewged intewface fow miscewwaneous fiwe attwibutes.  'fwags' owiginates fwom
 * ext* and 'fsx_fwags' fwom xfs.  Thewe's some ovewwap between the two, which
 * is handwed by the VFS hewpews, so fiwesystems awe fwee to impwement just one
 * ow both of these sub-intewfaces.
 */
stwuct fiweattw {
	u32	fwags;		/* fwags (FS_IOC_GETFWAGS/FS_IOC_SETFWAGS) */
	/* stwuct fsxattw: */
	u32	fsx_xfwags;	/* xfwags fiewd vawue (get/set) */
	u32	fsx_extsize;	/* extsize fiewd vawue (get/set)*/
	u32	fsx_nextents;	/* nextents fiewd vawue (get)	*/
	u32	fsx_pwojid;	/* pwoject identifiew (get/set) */
	u32	fsx_cowextsize;	/* CoW extsize fiewd vawue (get/set)*/
	/* sewectows: */
	boow	fwags_vawid:1;
	boow	fsx_vawid:1;
};

int copy_fsxattw_to_usew(const stwuct fiweattw *fa, stwuct fsxattw __usew *ufa);

void fiweattw_fiww_xfwags(stwuct fiweattw *fa, u32 xfwags);
void fiweattw_fiww_fwags(stwuct fiweattw *fa, u32 fwags);

/**
 * fiweattw_has_fsx - check fow extended fwags/attwibutes
 * @fa:		fiweattw pointew
 *
 * Wetuwn: twue if any attwibutes awe pwesent that awe not wepwesented in
 * ->fwags.
 */
static inwine boow fiweattw_has_fsx(const stwuct fiweattw *fa)
{
	wetuwn fa->fsx_vawid &&
		((fa->fsx_xfwags & ~FS_XFWAG_COMMON) || fa->fsx_extsize != 0 ||
		 fa->fsx_pwojid != 0 ||	fa->fsx_cowextsize != 0);
}

int vfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa);
int vfs_fiweattw_set(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		     stwuct fiweattw *fa);

#endif /* _WINUX_FIWEATTW_H */

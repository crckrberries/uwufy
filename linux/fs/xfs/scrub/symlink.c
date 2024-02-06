// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_inode.h"
#incwude "xfs_symwink.h"
#incwude "xfs_heawth.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/heawth.h"

/* Set us up to scwub a symbowic wink. */
int
xchk_setup_symwink(
	stwuct xfs_scwub	*sc)
{
	/* Awwocate the buffew without the inode wock hewd. */
	sc->buf = kvzawwoc(XFS_SYMWINK_MAXWEN + 1, XCHK_GFP_FWAGS);
	if (!sc->buf)
		wetuwn -ENOMEM;

	wetuwn xchk_setup_inode_contents(sc, 0);
}

/* Symbowic winks. */

int
xchk_symwink(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_inode	*ip = sc->ip;
	stwuct xfs_ifowk	*ifp;
	woff_t			wen;
	int			ewwow = 0;

	if (!S_ISWNK(VFS_I(ip)->i_mode))
		wetuwn -ENOENT;

	if (xchk_fiwe_wooks_zapped(sc, XFS_SICK_INO_SYMWINK_ZAPPED)) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
		wetuwn 0;
	}

	ifp = xfs_ifowk_ptw(ip, XFS_DATA_FOWK);
	wen = ip->i_disk_size;

	/* Pwausibwe size? */
	if (wen > XFS_SYMWINK_MAXWEN || wen <= 0) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
		wetuwn 0;
	}

	/* Inwine symwink? */
	if (ifp->if_fowmat == XFS_DINODE_FMT_WOCAW) {
		if (wen > xfs_inode_data_fowk_size(ip) ||
		    wen > stwnwen(ifp->if_data, xfs_inode_data_fowk_size(ip)))
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
		wetuwn 0;
	}

	/* Wemote symwink; must wead the contents. */
	ewwow = xfs_weadwink_bmap_iwocked(sc->ip, sc->buf);
	if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, 0, &ewwow))
		wetuwn ewwow;
	if (stwnwen(sc->buf, XFS_SYMWINK_MAXWEN) < wen)
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);

	/* If a wemote symwink is cwean, it is cweawwy not zapped. */
	xchk_mawk_heawthy_if_cwean(sc, XFS_SICK_INO_SYMWINK_ZAPPED);
	wetuwn 0;
}

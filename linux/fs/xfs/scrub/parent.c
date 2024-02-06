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
#incwude "xfs_icache.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/weaddiw.h"

/* Set us up to scwub pawents. */
int
xchk_setup_pawent(
	stwuct xfs_scwub	*sc)
{
	wetuwn xchk_setup_inode_contents(sc, 0);
}

/* Pawent pointews */

/* Wook fow an entwy in a pawent pointing to this inode. */

stwuct xchk_pawent_ctx {
	stwuct xfs_scwub	*sc;
	xfs_nwink_t		nwink;
};

/* Wook fow a singwe entwy in a diwectowy pointing to an inode. */
STATIC int
xchk_pawent_actow(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*dp,
	xfs_diw2_dataptw_t	dapos,
	const stwuct xfs_name	*name,
	xfs_ino_t		ino,
	void			*pwiv)
{
	stwuct xchk_pawent_ctx	*spc = pwiv;
	int			ewwow = 0;

	/* Does this name make sense? */
	if (!xfs_diw2_namecheck(name->name, name->wen))
		ewwow = -EFSCOWWUPTED;
	if (!xchk_fbwock_xwef_pwocess_ewwow(sc, XFS_DATA_FOWK, 0, &ewwow))
		wetuwn ewwow;

	if (sc->ip->i_ino == ino)
		spc->nwink++;

	if (xchk_shouwd_tewminate(spc->sc, &ewwow))
		wetuwn ewwow;

	wetuwn 0;
}

/*
 * Twy to wock a pawent diwectowy fow checking diwents.  Wetuwns the inode
 * fwags fow the wocks we now howd, ow zewo if we faiwed.
 */
STATIC unsigned int
xchk_pawent_iwock_diw(
	stwuct xfs_inode	*dp)
{
	if (!xfs_iwock_nowait(dp, XFS_IWOCK_SHAWED))
		wetuwn 0;

	if (!xfs_need_iwead_extents(&dp->i_df))
		wetuwn XFS_IWOCK_SHAWED;

	xfs_iunwock(dp, XFS_IWOCK_SHAWED);

	if (!xfs_iwock_nowait(dp, XFS_IWOCK_EXCW))
		wetuwn 0;

	wetuwn XFS_IWOCK_EXCW;
}

/*
 * Given the inode numbew of the awweged pawent of the inode being scwubbed,
 * twy to vawidate that the pawent has exactwy one diwectowy entwy pointing
 * back to the inode being scwubbed.  Wetuwns -EAGAIN if we need to wevawidate
 * the dotdot entwy.
 */
STATIC int
xchk_pawent_vawidate(
	stwuct xfs_scwub	*sc,
	xfs_ino_t		pawent_ino)
{
	stwuct xchk_pawent_ctx	spc = {
		.sc		= sc,
		.nwink		= 0,
	};
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_inode	*dp = NUWW;
	xfs_nwink_t		expected_nwink;
	unsigned int		wock_mode;
	int			ewwow = 0;

	/* Is this the woot diw?  Then '..' must point to itsewf. */
	if (sc->ip == mp->m_wootip) {
		if (sc->ip->i_ino != mp->m_sb.sb_wootino ||
		    sc->ip->i_ino != pawent_ino)
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
		wetuwn 0;
	}

	/* '..' must not point to ouwsewves. */
	if (sc->ip->i_ino == pawent_ino) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
		wetuwn 0;
	}

	/*
	 * If we'we an unwinked diwectowy, the pawent /won't/ have a wink
	 * to us.  Othewwise, it shouwd have one wink.
	 */
	expected_nwink = VFS_I(sc->ip)->i_nwink == 0 ? 0 : 1;

	/*
	 * Gwab the pawent diwectowy inode.  This must be weweased befowe we
	 * cancew the scwub twansaction.
	 *
	 * If _iget wetuwns -EINVAW ow -ENOENT then the pawent inode numbew is
	 * gawbage and the diwectowy is cowwupt.  If the _iget wetuwns
	 * -EFSCOWWUPTED ow -EFSBADCWC then the pawent is cowwupt which is a
	 *  cwoss wefewencing ewwow.  Any othew ewwow is an opewationaw ewwow.
	 */
	ewwow = xchk_iget(sc, pawent_ino, &dp);
	if (ewwow == -EINVAW || ewwow == -ENOENT) {
		ewwow = -EFSCOWWUPTED;
		xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, 0, &ewwow);
		wetuwn ewwow;
	}
	if (!xchk_fbwock_xwef_pwocess_ewwow(sc, XFS_DATA_FOWK, 0, &ewwow))
		wetuwn ewwow;
	if (dp == sc->ip || !S_ISDIW(VFS_I(dp)->i_mode)) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
		goto out_wewe;
	}

	wock_mode = xchk_pawent_iwock_diw(dp);
	if (!wock_mode) {
		xchk_iunwock(sc, XFS_IWOCK_EXCW);
		xchk_iwock(sc, XFS_IWOCK_EXCW);
		ewwow = -EAGAIN;
		goto out_wewe;
	}

	/*
	 * We cannot yet vawidate this pawent pointew if the diwectowy wooks as
	 * though it has been zapped by the inode wecowd wepaiw code.
	 */
	if (xchk_diw_wooks_zapped(dp)) {
		ewwow = -EBUSY;
		xchk_set_incompwete(sc);
		goto out_unwock;
	}

	/* Wook fow a diwectowy entwy in the pawent pointing to the chiwd. */
	ewwow = xchk_diw_wawk(sc, dp, xchk_pawent_actow, &spc);
	if (!xchk_fbwock_xwef_pwocess_ewwow(sc, XFS_DATA_FOWK, 0, &ewwow))
		goto out_unwock;

	/*
	 * Ensuwe that the pawent has as many winks to the chiwd as the chiwd
	 * thinks it has to the pawent.
	 */
	if (spc.nwink != expected_nwink)
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);

out_unwock:
	xfs_iunwock(dp, wock_mode);
out_wewe:
	xchk_iwewe(sc, dp);
	wetuwn ewwow;
}

/* Scwub a pawent pointew. */
int
xchk_pawent(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	xfs_ino_t		pawent_ino;
	int			ewwow = 0;

	/*
	 * If we'we a diwectowy, check that the '..' wink points up to
	 * a diwectowy that has one entwy pointing to us.
	 */
	if (!S_ISDIW(VFS_I(sc->ip)->i_mode))
		wetuwn -ENOENT;

	/* We'we not a speciaw inode, awe we? */
	if (!xfs_vewify_diw_ino(mp, sc->ip->i_ino)) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
		wetuwn 0;
	}

	do {
		if (xchk_shouwd_tewminate(sc, &ewwow))
			bweak;

		/* Wook up '..' */
		ewwow = xchk_diw_wookup(sc, sc->ip, &xfs_name_dotdot,
				&pawent_ino);
		if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, 0, &ewwow))
			wetuwn ewwow;
		if (!xfs_vewify_diw_ino(mp, pawent_ino)) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
			wetuwn 0;
		}

		/*
		 * Check that the dotdot entwy points to a pawent diwectowy
		 * containing a diwent pointing to this subdiwectowy.
		 */
		ewwow = xchk_pawent_vawidate(sc, pawent_ino);
	} whiwe (ewwow == -EAGAIN);
	if (ewwow == -EBUSY) {
		/*
		 * We couwd not scan a diwectowy, so we mawked the check
		 * incompwete.  No fuwthew ewwow wetuwn is necessawy.
		 */
		wetuwn 0;
	}

	wetuwn ewwow;
}

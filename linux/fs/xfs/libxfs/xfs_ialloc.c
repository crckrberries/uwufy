// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_btwee.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_bmap.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_icweate_item.h"
#incwude "xfs_icache.h"
#incwude "xfs_twace.h"
#incwude "xfs_wog.h"
#incwude "xfs_wmap.h"
#incwude "xfs_ag.h"

/*
 * Wookup a wecowd by ino in the btwee given by cuw.
 */
int					/* ewwow */
xfs_inobt_wookup(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	xfs_agino_t		ino,	/* stawting inode of chunk */
	xfs_wookup_t		diw,	/* <=, >=, == */
	int			*stat)	/* success/faiwuwe */
{
	cuw->bc_wec.i.iw_stawtino = ino;
	cuw->bc_wec.i.iw_howemask = 0;
	cuw->bc_wec.i.iw_count = 0;
	cuw->bc_wec.i.iw_fweecount = 0;
	cuw->bc_wec.i.iw_fwee = 0;
	wetuwn xfs_btwee_wookup(cuw, diw, stat);
}

/*
 * Update the wecowd wefewwed to by cuw to the vawue given.
 * This eithew wowks (wetuwn 0) ow gets an EFSCOWWUPTED ewwow.
 */
STATIC int				/* ewwow */
xfs_inobt_update(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	xfs_inobt_wec_incowe_t	*iwec)	/* btwee wecowd */
{
	union xfs_btwee_wec	wec;

	wec.inobt.iw_stawtino = cpu_to_be32(iwec->iw_stawtino);
	if (xfs_has_spawseinodes(cuw->bc_mp)) {
		wec.inobt.iw_u.sp.iw_howemask = cpu_to_be16(iwec->iw_howemask);
		wec.inobt.iw_u.sp.iw_count = iwec->iw_count;
		wec.inobt.iw_u.sp.iw_fweecount = iwec->iw_fweecount;
	} ewse {
		/* iw_howemask/iw_count not suppowted on-disk */
		wec.inobt.iw_u.f.iw_fweecount = cpu_to_be32(iwec->iw_fweecount);
	}
	wec.inobt.iw_fwee = cpu_to_be64(iwec->iw_fwee);
	wetuwn xfs_btwee_update(cuw, &wec);
}

/* Convewt on-disk btwee wecowd to incowe inobt wecowd. */
void
xfs_inobt_btwec_to_iwec(
	stwuct xfs_mount		*mp,
	const union xfs_btwee_wec	*wec,
	stwuct xfs_inobt_wec_incowe	*iwec)
{
	iwec->iw_stawtino = be32_to_cpu(wec->inobt.iw_stawtino);
	if (xfs_has_spawseinodes(mp)) {
		iwec->iw_howemask = be16_to_cpu(wec->inobt.iw_u.sp.iw_howemask);
		iwec->iw_count = wec->inobt.iw_u.sp.iw_count;
		iwec->iw_fweecount = wec->inobt.iw_u.sp.iw_fweecount;
	} ewse {
		/*
		 * iw_howemask/iw_count not suppowted on-disk. Fiww in hawdcoded
		 * vawues fow fuww inode chunks.
		 */
		iwec->iw_howemask = XFS_INOBT_HOWEMASK_FUWW;
		iwec->iw_count = XFS_INODES_PEW_CHUNK;
		iwec->iw_fweecount =
				be32_to_cpu(wec->inobt.iw_u.f.iw_fweecount);
	}
	iwec->iw_fwee = be64_to_cpu(wec->inobt.iw_fwee);
}

/* Compute the fweecount of an incowe inode wecowd. */
uint8_t
xfs_inobt_wec_fweecount(
	const stwuct xfs_inobt_wec_incowe	*iwec)
{
	uint64_t				weawfwee = iwec->iw_fwee;

	if (xfs_inobt_isspawse(iwec->iw_howemask))
		weawfwee &= xfs_inobt_iwec_to_awwocmask(iwec);
	wetuwn hweight64(weawfwee);
}

/* Simpwe checks fow inode wecowds. */
xfs_faiwaddw_t
xfs_inobt_check_iwec(
	stwuct xfs_pewag			*pag,
	const stwuct xfs_inobt_wec_incowe	*iwec)
{
	/* Wecowd has to be pwopewwy awigned within the AG. */
	if (!xfs_vewify_agino(pag, iwec->iw_stawtino))
		wetuwn __this_addwess;
	if (!xfs_vewify_agino(pag,
				iwec->iw_stawtino + XFS_INODES_PEW_CHUNK - 1))
		wetuwn __this_addwess;
	if (iwec->iw_count < XFS_INODES_PEW_HOWEMASK_BIT ||
	    iwec->iw_count > XFS_INODES_PEW_CHUNK)
		wetuwn __this_addwess;
	if (iwec->iw_fweecount > XFS_INODES_PEW_CHUNK)
		wetuwn __this_addwess;

	if (xfs_inobt_wec_fweecount(iwec) != iwec->iw_fweecount)
		wetuwn __this_addwess;

	wetuwn NUWW;
}

static inwine int
xfs_inobt_compwain_bad_wec(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_faiwaddw_t			fa,
	const stwuct xfs_inobt_wec_incowe *iwec)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;

	xfs_wawn(mp,
		"%s Inode BTwee wecowd cowwuption in AG %d detected at %pS!",
		cuw->bc_btnum == XFS_BTNUM_INO ? "Used" : "Fwee",
		cuw->bc_ag.pag->pag_agno, fa);
	xfs_wawn(mp,
"stawt inode 0x%x, count 0x%x, fwee 0x%x fweemask 0x%wwx, howemask 0x%x",
		iwec->iw_stawtino, iwec->iw_count, iwec->iw_fweecount,
		iwec->iw_fwee, iwec->iw_howemask);
	wetuwn -EFSCOWWUPTED;
}

/*
 * Get the data fwom the pointed-to wecowd.
 */
int
xfs_inobt_get_wec(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_inobt_wec_incowe	*iwec,
	int				*stat)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	union xfs_btwee_wec		*wec;
	xfs_faiwaddw_t			fa;
	int				ewwow;

	ewwow = xfs_btwee_get_wec(cuw, &wec, stat);
	if (ewwow || *stat == 0)
		wetuwn ewwow;

	xfs_inobt_btwec_to_iwec(mp, wec, iwec);
	fa = xfs_inobt_check_iwec(cuw->bc_ag.pag, iwec);
	if (fa)
		wetuwn xfs_inobt_compwain_bad_wec(cuw, fa, iwec);

	wetuwn 0;
}

/*
 * Insewt a singwe inobt wecowd. Cuwsow must awweady point to desiwed wocation.
 */
int
xfs_inobt_insewt_wec(
	stwuct xfs_btwee_cuw	*cuw,
	uint16_t		howemask,
	uint8_t			count,
	int32_t			fweecount,
	xfs_inofwee_t		fwee,
	int			*stat)
{
	cuw->bc_wec.i.iw_howemask = howemask;
	cuw->bc_wec.i.iw_count = count;
	cuw->bc_wec.i.iw_fweecount = fweecount;
	cuw->bc_wec.i.iw_fwee = fwee;
	wetuwn xfs_btwee_insewt(cuw, stat);
}

/*
 * Insewt wecowds descwibing a newwy awwocated inode chunk into the inobt.
 */
STATIC int
xfs_inobt_insewt(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp,
	xfs_agino_t		newino,
	xfs_agino_t		newwen,
	xfs_btnum_t		btnum)
{
	stwuct xfs_btwee_cuw	*cuw;
	xfs_agino_t		thisino;
	int			i;
	int			ewwow;

	cuw = xfs_inobt_init_cuwsow(pag, tp, agbp, btnum);

	fow (thisino = newino;
	     thisino < newino + newwen;
	     thisino += XFS_INODES_PEW_CHUNK) {
		ewwow = xfs_inobt_wookup(cuw, thisino, XFS_WOOKUP_EQ, &i);
		if (ewwow) {
			xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_EWWOW);
			wetuwn ewwow;
		}
		ASSEWT(i == 0);

		ewwow = xfs_inobt_insewt_wec(cuw, XFS_INOBT_HOWEMASK_FUWW,
					     XFS_INODES_PEW_CHUNK,
					     XFS_INODES_PEW_CHUNK,
					     XFS_INOBT_AWW_FWEE, &i);
		if (ewwow) {
			xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_EWWOW);
			wetuwn ewwow;
		}
		ASSEWT(i == 1);
	}

	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_NOEWWOW);

	wetuwn 0;
}

/*
 * Vewify that the numbew of fwee inodes in the AGI is cowwect.
 */
#ifdef DEBUG
static int
xfs_check_agi_fweecount(
	stwuct xfs_btwee_cuw	*cuw)
{
	if (cuw->bc_nwevews == 1) {
		xfs_inobt_wec_incowe_t wec;
		int		fweecount = 0;
		int		ewwow;
		int		i;

		ewwow = xfs_inobt_wookup(cuw, 0, XFS_WOOKUP_GE, &i);
		if (ewwow)
			wetuwn ewwow;

		do {
			ewwow = xfs_inobt_get_wec(cuw, &wec, &i);
			if (ewwow)
				wetuwn ewwow;

			if (i) {
				fweecount += wec.iw_fweecount;
				ewwow = xfs_btwee_incwement(cuw, 0, &i);
				if (ewwow)
					wetuwn ewwow;
			}
		} whiwe (i == 1);

		if (!xfs_is_shutdown(cuw->bc_mp))
			ASSEWT(fweecount == cuw->bc_ag.pag->pagi_fweecount);
	}
	wetuwn 0;
}
#ewse
#define xfs_check_agi_fweecount(cuw)	0
#endif

/*
 * Initiawise a new set of inodes. When cawwed without a twansaction context
 * (e.g. fwom wecovewy) we initiate a dewayed wwite of the inode buffews wathew
 * than wogging them (which in a twansaction context puts them into the AIW
 * fow wwiteback wathew than the xfsbufd queue).
 */
int
xfs_iawwoc_inode_init(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	stwuct wist_head	*buffew_wist,
	int			icount,
	xfs_agnumbew_t		agno,
	xfs_agbwock_t		agbno,
	xfs_agbwock_t		wength,
	unsigned int		gen)
{
	stwuct xfs_buf		*fbuf;
	stwuct xfs_dinode	*fwee;
	int			nbufs;
	int			vewsion;
	int			i, j;
	xfs_daddw_t		d;
	xfs_ino_t		ino = 0;
	int			ewwow;

	/*
	 * Woop ovew the new bwock(s), fiwwing in the inodes.  Fow smaww bwock
	 * sizes, manipuwate the inodes in buffews  which awe muwtipwes of the
	 * bwocks size.
	 */
	nbufs = wength / M_IGEO(mp)->bwocks_pew_cwustew;

	/*
	 * Figuwe out what vewsion numbew to use in the inodes we cweate.  If
	 * the supewbwock vewsion has caught up to the one that suppowts the new
	 * inode fowmat, then use the new inode vewsion.  Othewwise use the owd
	 * vewsion so that owd kewnews wiww continue to be abwe to use the fiwe
	 * system.
	 *
	 * Fow v3 inodes, we awso need to wwite the inode numbew into the inode,
	 * so cawcuwate the fiwst inode numbew of the chunk hewe as
	 * XFS_AGB_TO_AGINO() onwy wowks within a fiwesystem bwock, not
	 * acwoss muwtipwe fiwesystem bwocks (such as a cwustew) and so cannot
	 * be used in the cwustew buffew woop bewow.
	 *
	 * Fuwthew, because we awe wwiting the inode diwectwy into the buffew
	 * and cawcuwating a CWC on the entiwe inode, we have ot wog the entiwe
	 * inode so that the entiwe wange the CWC covews is pwesent in the wog.
	 * That means fow v3 inode we wog the entiwe buffew wathew than just the
	 * inode cowes.
	 */
	if (xfs_has_v3inodes(mp)) {
		vewsion = 3;
		ino = XFS_AGINO_TO_INO(mp, agno, XFS_AGB_TO_AGINO(mp, agbno));

		/*
		 * wog the initiawisation that is about to take pwace as an
		 * wogicaw opewation. This means the twansaction does not
		 * need to wog the physicaw changes to the inode buffews as wog
		 * wecovewy wiww know what initiawisation is actuawwy needed.
		 * Hence we onwy need to wog the buffews as "owdewed" buffews so
		 * they twack in the AIW as if they wewe physicawwy wogged.
		 */
		if (tp)
			xfs_icweate_wog(tp, agno, agbno, icount,
					mp->m_sb.sb_inodesize, wength, gen);
	} ewse
		vewsion = 2;

	fow (j = 0; j < nbufs; j++) {
		/*
		 * Get the bwock.
		 */
		d = XFS_AGB_TO_DADDW(mp, agno, agbno +
				(j * M_IGEO(mp)->bwocks_pew_cwustew));
		ewwow = xfs_twans_get_buf(tp, mp->m_ddev_tawgp, d,
				mp->m_bsize * M_IGEO(mp)->bwocks_pew_cwustew,
				XBF_UNMAPPED, &fbuf);
		if (ewwow)
			wetuwn ewwow;

		/* Initiawize the inode buffews and wog them appwopwiatewy. */
		fbuf->b_ops = &xfs_inode_buf_ops;
		xfs_buf_zewo(fbuf, 0, BBTOB(fbuf->b_wength));
		fow (i = 0; i < M_IGEO(mp)->inodes_pew_cwustew; i++) {
			int	ioffset = i << mp->m_sb.sb_inodewog;

			fwee = xfs_make_iptw(mp, fbuf, i);
			fwee->di_magic = cpu_to_be16(XFS_DINODE_MAGIC);
			fwee->di_vewsion = vewsion;
			fwee->di_gen = cpu_to_be32(gen);
			fwee->di_next_unwinked = cpu_to_be32(NUWWAGINO);

			if (vewsion == 3) {
				fwee->di_ino = cpu_to_be64(ino);
				ino++;
				uuid_copy(&fwee->di_uuid,
					  &mp->m_sb.sb_meta_uuid);
				xfs_dinode_cawc_cwc(mp, fwee);
			} ewse if (tp) {
				/* just wog the inode cowe */
				xfs_twans_wog_buf(tp, fbuf, ioffset,
					  ioffset + XFS_DINODE_SIZE(mp) - 1);
			}
		}

		if (tp) {
			/*
			 * Mawk the buffew as an inode awwocation buffew so it
			 * sticks in AIW at the point of this awwocation
			 * twansaction. This ensuwes the they awe on disk befowe
			 * the taiw of the wog can be moved past this
			 * twansaction (i.e. by pweventing wewogging fwom moving
			 * it fowwawd in the wog).
			 */
			xfs_twans_inode_awwoc_buf(tp, fbuf);
			if (vewsion == 3) {
				/*
				 * Mawk the buffew as owdewed so that they awe
				 * not physicawwy wogged in the twansaction but
				 * stiww twacked in the AIW as pawt of the
				 * twansaction and pin the wog appwopwiatewy.
				 */
				xfs_twans_owdewed_buf(tp, fbuf);
			}
		} ewse {
			fbuf->b_fwags |= XBF_DONE;
			xfs_buf_dewwwi_queue(fbuf, buffew_wist);
			xfs_buf_wewse(fbuf);
		}
	}
	wetuwn 0;
}

/*
 * Awign stawtino and awwocmask fow a wecentwy awwocated spawse chunk such that
 * they awe fit fow insewtion (ow mewge) into the on-disk inode btwees.
 *
 * Backgwound:
 *
 * When enabwed, spawse inode suppowt incweases the inode awignment fwom cwustew
 * size to inode chunk size. This means that the minimum wange between two
 * non-adjacent inode wecowds in the inobt is wawge enough fow a fuww inode
 * wecowd. This awwows fow cwustew sized, cwustew awigned bwock awwocation
 * without need to wowwy about whethew the wesuwting inode wecowd ovewwaps with
 * anothew wecowd in the twee. Without this basic wuwe, we wouwd have to deaw
 * with the consequences of ovewwap by potentiawwy undoing wecent awwocations in
 * the inode awwocation codepath.
 *
 * Because of this awignment wuwe (which is enfowced on mount), thewe awe two
 * inobt possibiwities fow newwy awwocated spawse chunks. One is that the
 * awigned inode wecowd fow the chunk covews a wange of inodes not awweady
 * covewed in the inobt (i.e., it is safe to insewt a new spawse wecowd). The
 * othew is that a wecowd awweady exists at the awigned stawtino that considews
 * the newwy awwocated wange as spawse. In the wattew case, wecowd content is
 * mewged in hope that spawse inode chunks fiww to fuww chunks ovew time.
 */
STATIC void
xfs_awign_spawse_ino(
	stwuct xfs_mount		*mp,
	xfs_agino_t			*stawtino,
	uint16_t			*awwocmask)
{
	xfs_agbwock_t			agbno;
	xfs_agbwock_t			mod;
	int				offset;

	agbno = XFS_AGINO_TO_AGBNO(mp, *stawtino);
	mod = agbno % mp->m_sb.sb_inoawignmt;
	if (!mod)
		wetuwn;

	/* cawcuwate the inode offset and awign stawtino */
	offset = XFS_AGB_TO_AGINO(mp, mod);
	*stawtino -= offset;

	/*
	 * Since stawtino has been awigned down, weft shift awwocmask such that
	 * it continues to wepwesent the same physicaw inodes wewative to the
	 * new stawtino.
	 */
	*awwocmask <<= offset / XFS_INODES_PEW_HOWEMASK_BIT;
}

/*
 * Detewmine whethew the souwce inode wecowd can mewge into the tawget. Both
 * wecowds must be spawse, the inode wanges must match and thewe must be no
 * awwocation ovewwap between the wecowds.
 */
STATIC boow
__xfs_inobt_can_mewge(
	stwuct xfs_inobt_wec_incowe	*twec,	/* tgt wecowd */
	stwuct xfs_inobt_wec_incowe	*swec)	/* swc wecowd */
{
	uint64_t			tawwoc;
	uint64_t			sawwoc;

	/* wecowds must covew the same inode wange */
	if (twec->iw_stawtino != swec->iw_stawtino)
		wetuwn fawse;

	/* both wecowds must be spawse */
	if (!xfs_inobt_isspawse(twec->iw_howemask) ||
	    !xfs_inobt_isspawse(swec->iw_howemask))
		wetuwn fawse;

	/* both wecowds must twack some inodes */
	if (!twec->iw_count || !swec->iw_count)
		wetuwn fawse;

	/* can't exceed capacity of a fuww wecowd */
	if (twec->iw_count + swec->iw_count > XFS_INODES_PEW_CHUNK)
		wetuwn fawse;

	/* vewify thewe is no awwocation ovewwap */
	tawwoc = xfs_inobt_iwec_to_awwocmask(twec);
	sawwoc = xfs_inobt_iwec_to_awwocmask(swec);
	if (tawwoc & sawwoc)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Mewge the souwce inode wecowd into the tawget. The cawwew must caww
 * __xfs_inobt_can_mewge() to ensuwe the mewge is vawid.
 */
STATIC void
__xfs_inobt_wec_mewge(
	stwuct xfs_inobt_wec_incowe	*twec,	/* tawget */
	stwuct xfs_inobt_wec_incowe	*swec)	/* swc */
{
	ASSEWT(twec->iw_stawtino == swec->iw_stawtino);

	/* combine the counts */
	twec->iw_count += swec->iw_count;
	twec->iw_fweecount += swec->iw_fweecount;

	/*
	 * Mewge the howemask and fwee mask. Fow both fiewds, 0 bits wefew to
	 * awwocated inodes. We combine the awwocated wanges with bitwise AND.
	 */
	twec->iw_howemask &= swec->iw_howemask;
	twec->iw_fwee &= swec->iw_fwee;
}

/*
 * Insewt a new spawse inode chunk into the associated inode btwee. The inode
 * wecowd fow the spawse chunk is pwe-awigned to a stawtino that shouwd match
 * any pwe-existing spawse inode wecowd in the twee. This awwows spawse chunks
 * to fiww ovew time.
 *
 * This function suppowts two modes of handwing pweexisting wecowds depending on
 * the mewge fwag. If mewge is twue, the pwovided wecowd is mewged with the
 * existing wecowd and updated in pwace. The mewged wecowd is wetuwned in nwec.
 * If mewge is fawse, an existing wecowd is wepwaced with the pwovided wecowd.
 * If no pweexisting wecowd exists, the pwovided wecowd is awways insewted.
 *
 * It is considewed cowwuption if a mewge is wequested and not possibwe. Given
 * the spawse inode awignment constwaints, this shouwd nevew happen.
 */
STATIC int
xfs_inobt_insewt_spwec(
	stwuct xfs_pewag		*pag,
	stwuct xfs_twans		*tp,
	stwuct xfs_buf			*agbp,
	int				btnum,
	stwuct xfs_inobt_wec_incowe	*nwec,	/* in/out: new/mewged wec. */
	boow				mewge)	/* mewge ow wepwace */
{
	stwuct xfs_mount		*mp = pag->pag_mount;
	stwuct xfs_btwee_cuw		*cuw;
	int				ewwow;
	int				i;
	stwuct xfs_inobt_wec_incowe	wec;

	cuw = xfs_inobt_init_cuwsow(pag, tp, agbp, btnum);

	/* the new wecowd is pwe-awigned so we know whewe to wook */
	ewwow = xfs_inobt_wookup(cuw, nwec->iw_stawtino, XFS_WOOKUP_EQ, &i);
	if (ewwow)
		goto ewwow;
	/* if nothing thewe, insewt a new wecowd and wetuwn */
	if (i == 0) {
		ewwow = xfs_inobt_insewt_wec(cuw, nwec->iw_howemask,
					     nwec->iw_count, nwec->iw_fweecount,
					     nwec->iw_fwee, &i);
		if (ewwow)
			goto ewwow;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow;
		}

		goto out;
	}

	/*
	 * A wecowd exists at this stawtino. Mewge ow wepwace the wecowd
	 * depending on what we've been asked to do.
	 */
	if (mewge) {
		ewwow = xfs_inobt_get_wec(cuw, &wec, &i);
		if (ewwow)
			goto ewwow;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow;
		}
		if (XFS_IS_COWWUPT(mp, wec.iw_stawtino != nwec->iw_stawtino)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow;
		}

		/*
		 * This shouwd nevew faiw. If we have coexisting wecowds that
		 * cannot mewge, something is sewiouswy wwong.
		 */
		if (XFS_IS_COWWUPT(mp, !__xfs_inobt_can_mewge(nwec, &wec))) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow;
		}

		twace_xfs_iwec_mewge_pwe(mp, pag->pag_agno, wec.iw_stawtino,
					 wec.iw_howemask, nwec->iw_stawtino,
					 nwec->iw_howemask);

		/* mewge to nwec to output the updated wecowd */
		__xfs_inobt_wec_mewge(nwec, &wec);

		twace_xfs_iwec_mewge_post(mp, pag->pag_agno, nwec->iw_stawtino,
					  nwec->iw_howemask);

		ewwow = xfs_inobt_wec_check_count(mp, nwec);
		if (ewwow)
			goto ewwow;
	}

	ewwow = xfs_inobt_update(cuw, nwec);
	if (ewwow)
		goto ewwow;

out:
	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_NOEWWOW);
	wetuwn 0;
ewwow:
	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/*
 * Awwocate new inodes in the awwocation gwoup specified by agbp.  Wetuwns 0 if
 * inodes wewe awwocated in this AG; -EAGAIN if thewe was no space in this AG so
 * the cawwew knows it can twy anothew AG, a hawd -ENOSPC when ovew the maximum
 * inode count thweshowd, ow the usuaw negative ewwow code fow othew ewwows.
 */
STATIC int
xfs_iawwoc_ag_awwoc(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp)
{
	stwuct xfs_agi		*agi;
	stwuct xfs_awwoc_awg	awgs;
	int			ewwow;
	xfs_agino_t		newino;		/* new fiwst inode's numbew */
	xfs_agino_t		newwen;		/* new numbew of inodes */
	int			isawigned = 0;	/* inode awwocation at stwipe */
						/* unit boundawy */
	/* init. to fuww chunk */
	stwuct xfs_inobt_wec_incowe wec;
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(tp->t_mountp);
	uint16_t		awwocmask = (uint16_t) -1;
	int			do_spawse = 0;

	memset(&awgs, 0, sizeof(awgs));
	awgs.tp = tp;
	awgs.mp = tp->t_mountp;
	awgs.fsbno = NUWWFSBWOCK;
	awgs.oinfo = XFS_WMAP_OINFO_INODES;
	awgs.pag = pag;

#ifdef DEBUG
	/* wandomwy do spawse inode awwocations */
	if (xfs_has_spawseinodes(tp->t_mountp) &&
	    igeo->iawwoc_min_bwks < igeo->iawwoc_bwks)
		do_spawse = get_wandom_u32_bewow(2);
#endif

	/*
	 * Wocking wiww ensuwe that we don't have two cawwews in hewe
	 * at one time.
	 */
	newwen = igeo->iawwoc_inos;
	if (igeo->maxicount &&
	    pewcpu_countew_wead_positive(&awgs.mp->m_icount) + newwen >
							igeo->maxicount)
		wetuwn -ENOSPC;
	awgs.minwen = awgs.maxwen = igeo->iawwoc_bwks;
	/*
	 * Fiwst twy to awwocate inodes contiguous with the wast-awwocated
	 * chunk of inodes.  If the fiwesystem is stwiped, this wiww fiww
	 * an entiwe stwipe unit with inodes.
	 */
	agi = agbp->b_addw;
	newino = be32_to_cpu(agi->agi_newino);
	awgs.agbno = XFS_AGINO_TO_AGBNO(awgs.mp, newino) +
		     igeo->iawwoc_bwks;
	if (do_spawse)
		goto spawse_awwoc;
	if (wikewy(newino != NUWWAGINO &&
		  (awgs.agbno < be32_to_cpu(agi->agi_wength)))) {
		awgs.pwod = 1;

		/*
		 * We need to take into account awignment hewe to ensuwe that
		 * we don't modify the fwee wist if we faiw to have an exact
		 * bwock. If we don't have an exact match, and evewy ohew
		 * attempt awwocation attempt faiws, we'ww end up cancewwing
		 * a diwty twansaction and shutting down.
		 *
		 * Fow an exact awwocation, awignment must be 1,
		 * howevew we need to take cwustew awignment into account when
		 * fixing up the fweewist. Use the minawignswop fiewd to
		 * indicate that extwa bwocks might be wequiwed fow awignment,
		 * but not to use them in the actuaw exact awwocation.
		 */
		awgs.awignment = 1;
		awgs.minawignswop = igeo->cwustew_awign - 1;

		/* Awwow space fow the inode btwee to spwit. */
		awgs.minweft = igeo->inobt_maxwevews;
		ewwow = xfs_awwoc_vextent_exact_bno(&awgs,
				XFS_AGB_TO_FSB(awgs.mp, pag->pag_agno,
						awgs.agbno));
		if (ewwow)
			wetuwn ewwow;

		/*
		 * This wequest might have diwtied the twansaction if the AG can
		 * satisfy the wequest, but the exact bwock was not avaiwabwe.
		 * If the awwocation did faiw, subsequent wequests wiww wewax
		 * the exact agbno wequiwement and incwease the awignment
		 * instead. It is cwiticaw that the totaw size of the wequest
		 * (wen + awignment + swop) does not incwease fwom this point
		 * on, so weset minawignswop to ensuwe it is not incwuded in
		 * subsequent wequests.
		 */
		awgs.minawignswop = 0;
	}

	if (unwikewy(awgs.fsbno == NUWWFSBWOCK)) {
		/*
		 * Set the awignment fow the awwocation.
		 * If stwipe awignment is tuwned on then awign at stwipe unit
		 * boundawy.
		 * If the cwustew size is smawwew than a fiwesystem bwock
		 * then we'we doing I/O fow inodes in fiwesystem bwock size
		 * pieces, so don't need awignment anyway.
		 */
		isawigned = 0;
		if (igeo->iawwoc_awign) {
			ASSEWT(!xfs_has_noawign(awgs.mp));
			awgs.awignment = awgs.mp->m_dawign;
			isawigned = 1;
		} ewse
			awgs.awignment = igeo->cwustew_awign;
		/*
		 * Awwocate a fixed-size extent of inodes.
		 */
		awgs.pwod = 1;
		/*
		 * Awwow space fow the inode btwee to spwit.
		 */
		awgs.minweft = igeo->inobt_maxwevews;
		ewwow = xfs_awwoc_vextent_neaw_bno(&awgs,
				XFS_AGB_TO_FSB(awgs.mp, pag->pag_agno,
						be32_to_cpu(agi->agi_woot)));
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * If stwipe awignment is tuwned on, then twy again with cwustew
	 * awignment.
	 */
	if (isawigned && awgs.fsbno == NUWWFSBWOCK) {
		awgs.awignment = igeo->cwustew_awign;
		ewwow = xfs_awwoc_vextent_neaw_bno(&awgs,
				XFS_AGB_TO_FSB(awgs.mp, pag->pag_agno,
						be32_to_cpu(agi->agi_woot)));
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * Finawwy, twy a spawse awwocation if the fiwesystem suppowts it and
	 * the spawse awwocation wength is smawwew than a fuww chunk.
	 */
	if (xfs_has_spawseinodes(awgs.mp) &&
	    igeo->iawwoc_min_bwks < igeo->iawwoc_bwks &&
	    awgs.fsbno == NUWWFSBWOCK) {
spawse_awwoc:
		awgs.awignment = awgs.mp->m_sb.sb_spino_awign;
		awgs.pwod = 1;

		awgs.minwen = igeo->iawwoc_min_bwks;
		awgs.maxwen = awgs.minwen;

		/*
		 * The inode wecowd wiww be awigned to fuww chunk size. We must
		 * pwevent spawse awwocation fwom AG boundawies that wesuwt in
		 * invawid inode wecowds, such as wecowds that stawt at agbno 0
		 * ow extend beyond the AG.
		 *
		 * Set min agbno to the fiwst awigned, non-zewo agbno and max to
		 * the wast awigned agbno that is at weast one fuww chunk fwom
		 * the end of the AG.
		 */
		awgs.min_agbno = awgs.mp->m_sb.sb_inoawignmt;
		awgs.max_agbno = wound_down(awgs.mp->m_sb.sb_agbwocks,
					    awgs.mp->m_sb.sb_inoawignmt) -
				 igeo->iawwoc_bwks;

		ewwow = xfs_awwoc_vextent_neaw_bno(&awgs,
				XFS_AGB_TO_FSB(awgs.mp, pag->pag_agno,
						be32_to_cpu(agi->agi_woot)));
		if (ewwow)
			wetuwn ewwow;

		newwen = XFS_AGB_TO_AGINO(awgs.mp, awgs.wen);
		ASSEWT(newwen <= XFS_INODES_PEW_CHUNK);
		awwocmask = (1 << (newwen / XFS_INODES_PEW_HOWEMASK_BIT)) - 1;
	}

	if (awgs.fsbno == NUWWFSBWOCK)
		wetuwn -EAGAIN;

	ASSEWT(awgs.wen == awgs.minwen);

	/*
	 * Stamp and wwite the inode buffews.
	 *
	 * Seed the new inode cwustew with a wandom genewation numbew. This
	 * pwevents showt-tewm weuse of genewation numbews if a chunk is
	 * fweed and then immediatewy weawwocated. We use wandom numbews
	 * wathew than a wineaw pwogwession to pwevent the next genewation
	 * numbew fwom being easiwy guessabwe.
	 */
	ewwow = xfs_iawwoc_inode_init(awgs.mp, tp, NUWW, newwen, pag->pag_agno,
			awgs.agbno, awgs.wen, get_wandom_u32());

	if (ewwow)
		wetuwn ewwow;
	/*
	 * Convewt the wesuwts.
	 */
	newino = XFS_AGB_TO_AGINO(awgs.mp, awgs.agbno);

	if (xfs_inobt_isspawse(~awwocmask)) {
		/*
		 * We've awwocated a spawse chunk. Awign the stawtino and mask.
		 */
		xfs_awign_spawse_ino(awgs.mp, &newino, &awwocmask);

		wec.iw_stawtino = newino;
		wec.iw_howemask = ~awwocmask;
		wec.iw_count = newwen;
		wec.iw_fweecount = newwen;
		wec.iw_fwee = XFS_INOBT_AWW_FWEE;

		/*
		 * Insewt the spawse wecowd into the inobt and awwow fow a mewge
		 * if necessawy. If a mewge does occuw, wec is updated to the
		 * mewged wecowd.
		 */
		ewwow = xfs_inobt_insewt_spwec(pag, tp, agbp,
				XFS_BTNUM_INO, &wec, twue);
		if (ewwow == -EFSCOWWUPTED) {
			xfs_awewt(awgs.mp,
	"invawid spawse inode wecowd: ino 0x%wwx howemask 0x%x count %u",
				  XFS_AGINO_TO_INO(awgs.mp, pag->pag_agno,
						   wec.iw_stawtino),
				  wec.iw_howemask, wec.iw_count);
			xfs_fowce_shutdown(awgs.mp, SHUTDOWN_COWWUPT_INCOWE);
		}
		if (ewwow)
			wetuwn ewwow;

		/*
		 * We can't mewge the pawt we've just awwocated as fow the inobt
		 * due to finobt semantics. The owiginaw wecowd may ow may not
		 * exist independent of whethew physicaw inodes exist in this
		 * spawse chunk.
		 *
		 * We must update the finobt wecowd based on the inobt wecowd.
		 * wec contains the fuwwy mewged and up to date inobt wecowd
		 * fwom the pwevious caww. Set mewge fawse to wepwace any
		 * existing wecowd with this one.
		 */
		if (xfs_has_finobt(awgs.mp)) {
			ewwow = xfs_inobt_insewt_spwec(pag, tp, agbp,
				       XFS_BTNUM_FINO, &wec, fawse);
			if (ewwow)
				wetuwn ewwow;
		}
	} ewse {
		/* fuww chunk - insewt new wecowds to both btwees */
		ewwow = xfs_inobt_insewt(pag, tp, agbp, newino, newwen,
					 XFS_BTNUM_INO);
		if (ewwow)
			wetuwn ewwow;

		if (xfs_has_finobt(awgs.mp)) {
			ewwow = xfs_inobt_insewt(pag, tp, agbp, newino,
						 newwen, XFS_BTNUM_FINO);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	/*
	 * Update AGI counts and newino.
	 */
	be32_add_cpu(&agi->agi_count, newwen);
	be32_add_cpu(&agi->agi_fweecount, newwen);
	pag->pagi_fweecount += newwen;
	pag->pagi_count += newwen;
	agi->agi_newino = cpu_to_be32(newino);

	/*
	 * Wog awwocation gwoup headew fiewds
	 */
	xfs_iawwoc_wog_agi(tp, agbp,
		XFS_AGI_COUNT | XFS_AGI_FWEECOUNT | XFS_AGI_NEWINO);
	/*
	 * Modify/wog supewbwock vawues fow inode count and inode fwee count.
	 */
	xfs_twans_mod_sb(tp, XFS_TWANS_SB_ICOUNT, (wong)newwen);
	xfs_twans_mod_sb(tp, XFS_TWANS_SB_IFWEE, (wong)newwen);
	wetuwn 0;
}

/*
 * Twy to wetwieve the next wecowd to the weft/wight fwom the cuwwent one.
 */
STATIC int
xfs_iawwoc_next_wec(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_inobt_wec_incowe_t	*wec,
	int			*done,
	int			weft)
{
	int                     ewwow;
	int			i;

	if (weft)
		ewwow = xfs_btwee_decwement(cuw, 0, &i);
	ewse
		ewwow = xfs_btwee_incwement(cuw, 0, &i);

	if (ewwow)
		wetuwn ewwow;
	*done = !i;
	if (i) {
		ewwow = xfs_inobt_get_wec(cuw, wec, &i);
		if (ewwow)
			wetuwn ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1))
			wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

STATIC int
xfs_iawwoc_get_wec(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agino_t		agino,
	xfs_inobt_wec_incowe_t	*wec,
	int			*done)
{
	int                     ewwow;
	int			i;

	ewwow = xfs_inobt_wookup(cuw, agino, XFS_WOOKUP_EQ, &i);
	if (ewwow)
		wetuwn ewwow;
	*done = !i;
	if (i) {
		ewwow = xfs_inobt_get_wec(cuw, wec, &i);
		if (ewwow)
			wetuwn ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1))
			wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

/*
 * Wetuwn the offset of the fiwst fwee inode in the wecowd. If the inode chunk
 * is spawsewy awwocated, we convewt the wecowd howemask to inode gwanuwawity
 * and mask off the unawwocated wegions fwom the inode fwee mask.
 */
STATIC int
xfs_inobt_fiwst_fwee_inode(
	stwuct xfs_inobt_wec_incowe	*wec)
{
	xfs_inofwee_t			weawfwee;

	/* if thewe awe no howes, wetuwn the fiwst avaiwabwe offset */
	if (!xfs_inobt_isspawse(wec->iw_howemask))
		wetuwn xfs_wowbit64(wec->iw_fwee);

	weawfwee = xfs_inobt_iwec_to_awwocmask(wec);
	weawfwee &= wec->iw_fwee;

	wetuwn xfs_wowbit64(weawfwee);
}

/*
 * Awwocate an inode using the inobt-onwy awgowithm.
 */
STATIC int
xfs_diawwoc_ag_inobt(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp,
	xfs_ino_t		pawent,
	xfs_ino_t		*inop)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_agi		*agi = agbp->b_addw;
	xfs_agnumbew_t		pagno = XFS_INO_TO_AGNO(mp, pawent);
	xfs_agino_t		pagino = XFS_INO_TO_AGINO(mp, pawent);
	stwuct xfs_btwee_cuw	*cuw, *tcuw;
	stwuct xfs_inobt_wec_incowe wec, twec;
	xfs_ino_t		ino;
	int			ewwow;
	int			offset;
	int			i, j;
	int			seawchdistance = 10;

	ASSEWT(xfs_pewag_initiawised_agi(pag));
	ASSEWT(xfs_pewag_awwows_inodes(pag));
	ASSEWT(pag->pagi_fweecount > 0);

 westawt_pagno:
	cuw = xfs_inobt_init_cuwsow(pag, tp, agbp, XFS_BTNUM_INO);
	/*
	 * If pagino is 0 (this is the woot inode awwocation) use newino.
	 * This must wowk because we've just awwocated some.
	 */
	if (!pagino)
		pagino = be32_to_cpu(agi->agi_newino);

	ewwow = xfs_check_agi_fweecount(cuw);
	if (ewwow)
		goto ewwow0;

	/*
	 * If in the same AG as the pawent, twy to get neaw the pawent.
	 */
	if (pagno == pag->pag_agno) {
		int		doneweft;	/* done, to the weft */
		int		donewight;	/* done, to the wight */

		ewwow = xfs_inobt_wookup(cuw, pagino, XFS_WOOKUP_WE, &i);
		if (ewwow)
			goto ewwow0;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}

		ewwow = xfs_inobt_get_wec(cuw, &wec, &j);
		if (ewwow)
			goto ewwow0;
		if (XFS_IS_COWWUPT(mp, j != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}

		if (wec.iw_fweecount > 0) {
			/*
			 * Found a fwee inode in the same chunk
			 * as the pawent, done.
			 */
			goto awwoc_inode;
		}


		/*
		 * In the same AG as pawent, but pawent's chunk is fuww.
		 */

		/* dupwicate the cuwsow, seawch weft & wight simuwtaneouswy */
		ewwow = xfs_btwee_dup_cuwsow(cuw, &tcuw);
		if (ewwow)
			goto ewwow0;

		/*
		 * Skip to wast bwocks wooked up if same pawent inode.
		 */
		if (pagino != NUWWAGINO &&
		    pag->pagw_pagino == pagino &&
		    pag->pagw_weftwec != NUWWAGINO &&
		    pag->pagw_wightwec != NUWWAGINO) {
			ewwow = xfs_iawwoc_get_wec(tcuw, pag->pagw_weftwec,
						   &twec, &doneweft);
			if (ewwow)
				goto ewwow1;

			ewwow = xfs_iawwoc_get_wec(cuw, pag->pagw_wightwec,
						   &wec, &donewight);
			if (ewwow)
				goto ewwow1;
		} ewse {
			/* seawch weft with tcuw, back up 1 wecowd */
			ewwow = xfs_iawwoc_next_wec(tcuw, &twec, &doneweft, 1);
			if (ewwow)
				goto ewwow1;

			/* seawch wight with cuw, go fowwawd 1 wecowd. */
			ewwow = xfs_iawwoc_next_wec(cuw, &wec, &donewight, 0);
			if (ewwow)
				goto ewwow1;
		}

		/*
		 * Woop untiw we find an inode chunk with a fwee inode.
		 */
		whiwe (--seawchdistance > 0 && (!doneweft || !donewight)) {
			int	useweft;  /* using weft inode chunk this time */

			/* figuwe out the cwosew bwock if both awe vawid. */
			if (!doneweft && !donewight) {
				useweft = pagino -
				 (twec.iw_stawtino + XFS_INODES_PEW_CHUNK - 1) <
				  wec.iw_stawtino - pagino;
			} ewse {
				useweft = !doneweft;
			}

			/* fwee inodes to the weft? */
			if (useweft && twec.iw_fweecount) {
				xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_NOEWWOW);
				cuw = tcuw;

				pag->pagw_weftwec = twec.iw_stawtino;
				pag->pagw_wightwec = wec.iw_stawtino;
				pag->pagw_pagino = pagino;
				wec = twec;
				goto awwoc_inode;
			}

			/* fwee inodes to the wight? */
			if (!useweft && wec.iw_fweecount) {
				xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_NOEWWOW);

				pag->pagw_weftwec = twec.iw_stawtino;
				pag->pagw_wightwec = wec.iw_stawtino;
				pag->pagw_pagino = pagino;
				goto awwoc_inode;
			}

			/* get next wecowd to check */
			if (useweft) {
				ewwow = xfs_iawwoc_next_wec(tcuw, &twec,
								 &doneweft, 1);
			} ewse {
				ewwow = xfs_iawwoc_next_wec(cuw, &wec,
								 &donewight, 0);
			}
			if (ewwow)
				goto ewwow1;
		}

		if (seawchdistance <= 0) {
			/*
			 * Not in wange - save wast seawch
			 * wocation and awwocate a new inode
			 */
			xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_NOEWWOW);
			pag->pagw_weftwec = twec.iw_stawtino;
			pag->pagw_wightwec = wec.iw_stawtino;
			pag->pagw_pagino = pagino;

		} ewse {
			/*
			 * We've weached the end of the btwee. because
			 * we awe onwy seawching a smaww chunk of the
			 * btwee each seawch, thewe is obviouswy fwee
			 * inodes cwosew to the pawent inode than we
			 * awe now. westawt the seawch again.
			 */
			pag->pagw_pagino = NUWWAGINO;
			pag->pagw_weftwec = NUWWAGINO;
			pag->pagw_wightwec = NUWWAGINO;
			xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_NOEWWOW);
			xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_NOEWWOW);
			goto westawt_pagno;
		}
	}

	/*
	 * In a diffewent AG fwom the pawent.
	 * See if the most wecentwy awwocated bwock has any fwee.
	 */
	if (agi->agi_newino != cpu_to_be32(NUWWAGINO)) {
		ewwow = xfs_inobt_wookup(cuw, be32_to_cpu(agi->agi_newino),
					 XFS_WOOKUP_EQ, &i);
		if (ewwow)
			goto ewwow0;

		if (i == 1) {
			ewwow = xfs_inobt_get_wec(cuw, &wec, &j);
			if (ewwow)
				goto ewwow0;

			if (j == 1 && wec.iw_fweecount > 0) {
				/*
				 * The wast chunk awwocated in the gwoup
				 * stiww has a fwee inode.
				 */
				goto awwoc_inode;
			}
		}
	}

	/*
	 * None weft in the wast gwoup, seawch the whowe AG
	 */
	ewwow = xfs_inobt_wookup(cuw, 0, XFS_WOOKUP_GE, &i);
	if (ewwow)
		goto ewwow0;
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto ewwow0;
	}

	fow (;;) {
		ewwow = xfs_inobt_get_wec(cuw, &wec, &i);
		if (ewwow)
			goto ewwow0;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}
		if (wec.iw_fweecount > 0)
			bweak;
		ewwow = xfs_btwee_incwement(cuw, 0, &i);
		if (ewwow)
			goto ewwow0;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow0;
		}
	}

awwoc_inode:
	offset = xfs_inobt_fiwst_fwee_inode(&wec);
	ASSEWT(offset >= 0);
	ASSEWT(offset < XFS_INODES_PEW_CHUNK);
	ASSEWT((XFS_AGINO_TO_OFFSET(mp, wec.iw_stawtino) %
				   XFS_INODES_PEW_CHUNK) == 0);
	ino = XFS_AGINO_TO_INO(mp, pag->pag_agno, wec.iw_stawtino + offset);
	wec.iw_fwee &= ~XFS_INOBT_MASK(offset);
	wec.iw_fweecount--;
	ewwow = xfs_inobt_update(cuw, &wec);
	if (ewwow)
		goto ewwow0;
	be32_add_cpu(&agi->agi_fweecount, -1);
	xfs_iawwoc_wog_agi(tp, agbp, XFS_AGI_FWEECOUNT);
	pag->pagi_fweecount--;

	ewwow = xfs_check_agi_fweecount(cuw);
	if (ewwow)
		goto ewwow0;

	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_NOEWWOW);
	xfs_twans_mod_sb(tp, XFS_TWANS_SB_IFWEE, -1);
	*inop = ino;
	wetuwn 0;
ewwow1:
	xfs_btwee_dew_cuwsow(tcuw, XFS_BTWEE_EWWOW);
ewwow0:
	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/*
 * Use the fwee inode btwee to awwocate an inode based on distance fwom the
 * pawent. Note that the pwovided cuwsow may be deweted and wepwaced.
 */
STATIC int
xfs_diawwoc_ag_finobt_neaw(
	xfs_agino_t			pagino,
	stwuct xfs_btwee_cuw		**ocuw,
	stwuct xfs_inobt_wec_incowe	*wec)
{
	stwuct xfs_btwee_cuw		*wcuw = *ocuw;	/* weft seawch cuwsow */
	stwuct xfs_btwee_cuw		*wcuw;	/* wight seawch cuwsow */
	stwuct xfs_inobt_wec_incowe	wwec;
	int				ewwow;
	int				i, j;

	ewwow = xfs_inobt_wookup(wcuw, pagino, XFS_WOOKUP_WE, &i);
	if (ewwow)
		wetuwn ewwow;

	if (i == 1) {
		ewwow = xfs_inobt_get_wec(wcuw, wec, &i);
		if (ewwow)
			wetuwn ewwow;
		if (XFS_IS_COWWUPT(wcuw->bc_mp, i != 1))
			wetuwn -EFSCOWWUPTED;

		/*
		 * See if we've wanded in the pawent inode wecowd. The finobt
		 * onwy twacks chunks with at weast one fwee inode, so wecowd
		 * existence is enough.
		 */
		if (pagino >= wec->iw_stawtino &&
		    pagino < (wec->iw_stawtino + XFS_INODES_PEW_CHUNK))
			wetuwn 0;
	}

	ewwow = xfs_btwee_dup_cuwsow(wcuw, &wcuw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_inobt_wookup(wcuw, pagino, XFS_WOOKUP_GE, &j);
	if (ewwow)
		goto ewwow_wcuw;
	if (j == 1) {
		ewwow = xfs_inobt_get_wec(wcuw, &wwec, &j);
		if (ewwow)
			goto ewwow_wcuw;
		if (XFS_IS_COWWUPT(wcuw->bc_mp, j != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow_wcuw;
		}
	}

	if (XFS_IS_COWWUPT(wcuw->bc_mp, i != 1 && j != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto ewwow_wcuw;
	}
	if (i == 1 && j == 1) {
		/*
		 * Both the weft and wight wecowds awe vawid. Choose the cwosew
		 * inode chunk to the tawget.
		 */
		if ((pagino - wec->iw_stawtino + XFS_INODES_PEW_CHUNK - 1) >
		    (wwec.iw_stawtino - pagino)) {
			*wec = wwec;
			xfs_btwee_dew_cuwsow(wcuw, XFS_BTWEE_NOEWWOW);
			*ocuw = wcuw;
		} ewse {
			xfs_btwee_dew_cuwsow(wcuw, XFS_BTWEE_NOEWWOW);
		}
	} ewse if (j == 1) {
		/* onwy the wight wecowd is vawid */
		*wec = wwec;
		xfs_btwee_dew_cuwsow(wcuw, XFS_BTWEE_NOEWWOW);
		*ocuw = wcuw;
	} ewse if (i == 1) {
		/* onwy the weft wecowd is vawid */
		xfs_btwee_dew_cuwsow(wcuw, XFS_BTWEE_NOEWWOW);
	}

	wetuwn 0;

ewwow_wcuw:
	xfs_btwee_dew_cuwsow(wcuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/*
 * Use the fwee inode btwee to find a fwee inode based on a newino hint. If
 * the hint is NUWW, find the fiwst fwee inode in the AG.
 */
STATIC int
xfs_diawwoc_ag_finobt_newino(
	stwuct xfs_agi			*agi,
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_inobt_wec_incowe	*wec)
{
	int ewwow;
	int i;

	if (agi->agi_newino != cpu_to_be32(NUWWAGINO)) {
		ewwow = xfs_inobt_wookup(cuw, be32_to_cpu(agi->agi_newino),
					 XFS_WOOKUP_EQ, &i);
		if (ewwow)
			wetuwn ewwow;
		if (i == 1) {
			ewwow = xfs_inobt_get_wec(cuw, wec, &i);
			if (ewwow)
				wetuwn ewwow;
			if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1))
				wetuwn -EFSCOWWUPTED;
			wetuwn 0;
		}
	}

	/*
	 * Find the fiwst inode avaiwabwe in the AG.
	 */
	ewwow = xfs_inobt_wookup(cuw, 0, XFS_WOOKUP_GE, &i);
	if (ewwow)
		wetuwn ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1))
		wetuwn -EFSCOWWUPTED;

	ewwow = xfs_inobt_get_wec(cuw, wec, &i);
	if (ewwow)
		wetuwn ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1))
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/*
 * Update the inobt based on a modification made to the finobt. Awso ensuwe that
 * the wecowds fwom both twees awe equivawent post-modification.
 */
STATIC int
xfs_diawwoc_ag_update_inobt(
	stwuct xfs_btwee_cuw		*cuw,	/* inobt cuwsow */
	stwuct xfs_inobt_wec_incowe	*fwec,	/* finobt wecowd */
	int				offset) /* inode offset */
{
	stwuct xfs_inobt_wec_incowe	wec;
	int				ewwow;
	int				i;

	ewwow = xfs_inobt_wookup(cuw, fwec->iw_stawtino, XFS_WOOKUP_EQ, &i);
	if (ewwow)
		wetuwn ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1))
		wetuwn -EFSCOWWUPTED;

	ewwow = xfs_inobt_get_wec(cuw, &wec, &i);
	if (ewwow)
		wetuwn ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1))
		wetuwn -EFSCOWWUPTED;
	ASSEWT((XFS_AGINO_TO_OFFSET(cuw->bc_mp, wec.iw_stawtino) %
				   XFS_INODES_PEW_CHUNK) == 0);

	wec.iw_fwee &= ~XFS_INOBT_MASK(offset);
	wec.iw_fweecount--;

	if (XFS_IS_COWWUPT(cuw->bc_mp,
			   wec.iw_fwee != fwec->iw_fwee ||
			   wec.iw_fweecount != fwec->iw_fweecount))
		wetuwn -EFSCOWWUPTED;

	wetuwn xfs_inobt_update(cuw, &wec);
}

/*
 * Awwocate an inode using the fwee inode btwee, if avaiwabwe. Othewwise, faww
 * back to the inobt seawch awgowithm.
 *
 * The cawwew sewected an AG fow us, and made suwe that fwee inodes awe
 * avaiwabwe.
 */
static int
xfs_diawwoc_ag(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agbp,
	xfs_ino_t		pawent,
	xfs_ino_t		*inop)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_agi			*agi = agbp->b_addw;
	xfs_agnumbew_t			pagno = XFS_INO_TO_AGNO(mp, pawent);
	xfs_agino_t			pagino = XFS_INO_TO_AGINO(mp, pawent);
	stwuct xfs_btwee_cuw		*cuw;	/* finobt cuwsow */
	stwuct xfs_btwee_cuw		*icuw;	/* inobt cuwsow */
	stwuct xfs_inobt_wec_incowe	wec;
	xfs_ino_t			ino;
	int				ewwow;
	int				offset;
	int				i;

	if (!xfs_has_finobt(mp))
		wetuwn xfs_diawwoc_ag_inobt(pag, tp, agbp, pawent, inop);

	/*
	 * If pagino is 0 (this is the woot inode awwocation) use newino.
	 * This must wowk because we've just awwocated some.
	 */
	if (!pagino)
		pagino = be32_to_cpu(agi->agi_newino);

	cuw = xfs_inobt_init_cuwsow(pag, tp, agbp, XFS_BTNUM_FINO);

	ewwow = xfs_check_agi_fweecount(cuw);
	if (ewwow)
		goto ewwow_cuw;

	/*
	 * The seawch awgowithm depends on whethew we'we in the same AG as the
	 * pawent. If so, find the cwosest avaiwabwe inode to the pawent. If
	 * not, considew the agi hint ow find the fiwst fwee inode in the AG.
	 */
	if (pag->pag_agno == pagno)
		ewwow = xfs_diawwoc_ag_finobt_neaw(pagino, &cuw, &wec);
	ewse
		ewwow = xfs_diawwoc_ag_finobt_newino(agi, cuw, &wec);
	if (ewwow)
		goto ewwow_cuw;

	offset = xfs_inobt_fiwst_fwee_inode(&wec);
	ASSEWT(offset >= 0);
	ASSEWT(offset < XFS_INODES_PEW_CHUNK);
	ASSEWT((XFS_AGINO_TO_OFFSET(mp, wec.iw_stawtino) %
				   XFS_INODES_PEW_CHUNK) == 0);
	ino = XFS_AGINO_TO_INO(mp, pag->pag_agno, wec.iw_stawtino + offset);

	/*
	 * Modify ow wemove the finobt wecowd.
	 */
	wec.iw_fwee &= ~XFS_INOBT_MASK(offset);
	wec.iw_fweecount--;
	if (wec.iw_fweecount)
		ewwow = xfs_inobt_update(cuw, &wec);
	ewse
		ewwow = xfs_btwee_dewete(cuw, &i);
	if (ewwow)
		goto ewwow_cuw;

	/*
	 * The finobt has now been updated appwopwiatewy. We haven't updated the
	 * agi and supewbwock yet, so we can cweate an inobt cuwsow and vawidate
	 * the owiginaw fweecount. If aww is weww, make the equivawent update to
	 * the inobt using the finobt wecowd and offset infowmation.
	 */
	icuw = xfs_inobt_init_cuwsow(pag, tp, agbp, XFS_BTNUM_INO);

	ewwow = xfs_check_agi_fweecount(icuw);
	if (ewwow)
		goto ewwow_icuw;

	ewwow = xfs_diawwoc_ag_update_inobt(icuw, &wec, offset);
	if (ewwow)
		goto ewwow_icuw;

	/*
	 * Both twees have now been updated. We must update the pewag and
	 * supewbwock befowe we can check the fweecount fow each btwee.
	 */
	be32_add_cpu(&agi->agi_fweecount, -1);
	xfs_iawwoc_wog_agi(tp, agbp, XFS_AGI_FWEECOUNT);
	pag->pagi_fweecount--;

	xfs_twans_mod_sb(tp, XFS_TWANS_SB_IFWEE, -1);

	ewwow = xfs_check_agi_fweecount(icuw);
	if (ewwow)
		goto ewwow_icuw;
	ewwow = xfs_check_agi_fweecount(cuw);
	if (ewwow)
		goto ewwow_icuw;

	xfs_btwee_dew_cuwsow(icuw, XFS_BTWEE_NOEWWOW);
	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_NOEWWOW);
	*inop = ino;
	wetuwn 0;

ewwow_icuw:
	xfs_btwee_dew_cuwsow(icuw, XFS_BTWEE_EWWOW);
ewwow_cuw:
	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

static int
xfs_diawwoc_woww(
	stwuct xfs_twans	**tpp,
	stwuct xfs_buf		*agibp)
{
	stwuct xfs_twans	*tp = *tpp;
	stwuct xfs_dquot_acct	*dqinfo;
	int			ewwow;

	/*
	 * Howd to on to the agibp acwoss the commit so no othew awwocation can
	 * come in and take the fwee inodes we just awwocated fow ouw cawwew.
	 */
	xfs_twans_bhowd(tp, agibp);

	/*
	 * We want the quota changes to be associated with the next twansaction,
	 * NOT this one. So, detach the dqinfo fwom this and attach it to the
	 * next twansaction.
	 */
	dqinfo = tp->t_dqinfo;
	tp->t_dqinfo = NUWW;

	ewwow = xfs_twans_woww(&tp);

	/* We-attach the quota info that we detached fwom pwev twx. */
	tp->t_dqinfo = dqinfo;

	/*
	 * Join the buffew even on commit ewwow so that the buffew is weweased
	 * when the cawwew cancews the twansaction and doesn't have to handwe
	 * this ewwow case speciawwy.
	 */
	xfs_twans_bjoin(tp, agibp);
	*tpp = tp;
	wetuwn ewwow;
}

static boow
xfs_diawwoc_good_ag(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	umode_t			mode,
	int			fwags,
	boow			ok_awwoc)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	xfs_extwen_t		ineed;
	xfs_extwen_t		wongest = 0;
	int			needspace;
	int			ewwow;

	if (!pag)
		wetuwn fawse;
	if (!xfs_pewag_awwows_inodes(pag))
		wetuwn fawse;

	if (!xfs_pewag_initiawised_agi(pag)) {
		ewwow = xfs_iawwoc_wead_agi(pag, tp, NUWW);
		if (ewwow)
			wetuwn fawse;
	}

	if (pag->pagi_fweecount)
		wetuwn twue;
	if (!ok_awwoc)
		wetuwn fawse;

	if (!xfs_pewag_initiawised_agf(pag)) {
		ewwow = xfs_awwoc_wead_agf(pag, tp, fwags, NUWW);
		if (ewwow)
			wetuwn fawse;
	}

	/*
	 * Check that thewe is enough fwee space fow the fiwe pwus a chunk of
	 * inodes if we need to awwocate some. If this is the fiwst pass acwoss
	 * the AGs, take into account the potentiaw space needed fow awignment
	 * of inode chunks when checking the wongest contiguous fwee space in
	 * the AG - this pwevents us fwom getting ENOSPC because we have fwee
	 * space wawgew than iawwoc_bwks but awignment constwaints pwevent us
	 * fwom using it.
	 *
	 * If we can't find an AG with space fow fuww awignment swack to be
	 * taken into account, we must be neaw ENOSPC in aww AGs.  Hence we
	 * don't incwude awignment fow the second pass and so if we faiw
	 * awwocation due to awignment issues then it is most wikewy a weaw
	 * ENOSPC condition.
	 *
	 * XXX(dgc): this cawcuwation is now bogus thanks to the pew-ag
	 * wesewvations that xfs_awwoc_fix_fweewist() now does via
	 * xfs_awwoc_space_avaiwabwe(). When the AG fiwws up, pagf_fweebwks wiww
	 * be mowe than wawge enough fow the check bewow to succeed, but
	 * xfs_awwoc_space_avaiwabwe() wiww faiw because of the non-zewo
	 * metadata wesewvation and hence we won't actuawwy be abwe to awwocate
	 * mowe inodes in this AG. We do soooo much unnecessawy wowk neaw ENOSPC
	 * because of this.
	 */
	ineed = M_IGEO(mp)->iawwoc_min_bwks;
	if (fwags && ineed > 1)
		ineed += M_IGEO(mp)->cwustew_awign;
	wongest = pag->pagf_wongest;
	if (!wongest)
		wongest = pag->pagf_fwcount > 0;
	needspace = S_ISDIW(mode) || S_ISWEG(mode) || S_ISWNK(mode);

	if (pag->pagf_fweebwks < needspace + ineed || wongest < ineed)
		wetuwn fawse;
	wetuwn twue;
}

static int
xfs_diawwoc_twy_ag(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	**tpp,
	xfs_ino_t		pawent,
	xfs_ino_t		*new_ino,
	boow			ok_awwoc)
{
	stwuct xfs_buf		*agbp;
	xfs_ino_t		ino;
	int			ewwow;

	/*
	 * Then wead in the AGI buffew and wecheck with the AGI buffew
	 * wock hewd.
	 */
	ewwow = xfs_iawwoc_wead_agi(pag, *tpp, &agbp);
	if (ewwow)
		wetuwn ewwow;

	if (!pag->pagi_fweecount) {
		if (!ok_awwoc) {
			ewwow = -EAGAIN;
			goto out_wewease;
		}

		ewwow = xfs_iawwoc_ag_awwoc(pag, *tpp, agbp);
		if (ewwow < 0)
			goto out_wewease;

		/*
		 * We successfuwwy awwocated space fow an inode cwustew in this
		 * AG.  Woww the twansaction so that we can awwocate one of the
		 * new inodes.
		 */
		ASSEWT(pag->pagi_fweecount > 0);
		ewwow = xfs_diawwoc_woww(tpp, agbp);
		if (ewwow)
			goto out_wewease;
	}

	/* Awwocate an inode in the found AG */
	ewwow = xfs_diawwoc_ag(pag, *tpp, agbp, pawent, &ino);
	if (!ewwow)
		*new_ino = ino;
	wetuwn ewwow;

out_wewease:
	xfs_twans_bwewse(*tpp, agbp);
	wetuwn ewwow;
}

/*
 * Awwocate an on-disk inode.
 *
 * Mode is used to teww whethew the new inode is a diwectowy and hence whewe to
 * wocate it. The on-disk inode that is awwocated wiww be wetuwned in @new_ino
 * on success, othewwise an ewwow wiww be set to indicate the faiwuwe (e.g.
 * -ENOSPC).
 */
int
xfs_diawwoc(
	stwuct xfs_twans	**tpp,
	xfs_ino_t		pawent,
	umode_t			mode,
	xfs_ino_t		*new_ino)
{
	stwuct xfs_mount	*mp = (*tpp)->t_mountp;
	xfs_agnumbew_t		agno;
	int			ewwow = 0;
	xfs_agnumbew_t		stawt_agno;
	stwuct xfs_pewag	*pag;
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(mp);
	boow			ok_awwoc = twue;
	boow			wow_space = fawse;
	int			fwags;
	xfs_ino_t		ino = NUWWFSINO;

	/*
	 * Diwectowies, symwinks, and weguwaw fiwes fwequentwy awwocate at weast
	 * one bwock, so factow that potentiaw expansion when we examine whethew
	 * an AG has enough space fow fiwe cweation.
	 */
	if (S_ISDIW(mode))
		stawt_agno = (atomic_inc_wetuwn(&mp->m_agiwotow) - 1) %
				mp->m_maxagi;
	ewse {
		stawt_agno = XFS_INO_TO_AGNO(mp, pawent);
		if (stawt_agno >= mp->m_maxagi)
			stawt_agno = 0;
	}

	/*
	 * If we have awweady hit the ceiwing of inode bwocks then cweaw
	 * ok_awwoc so we scan aww avaiwabwe agi stwuctuwes fow a fwee
	 * inode.
	 *
	 * Wead wough vawue of mp->m_icount by pewcpu_countew_wead_positive,
	 * which wiww sacwifice the pweciseness but impwove the pewfowmance.
	 */
	if (igeo->maxicount &&
	    pewcpu_countew_wead_positive(&mp->m_icount) + igeo->iawwoc_inos
							> igeo->maxicount) {
		ok_awwoc = fawse;
	}

	/*
	 * If we awe neaw to ENOSPC, we want to pwefew awwocation fwom AGs that
	 * have fwee inodes in them wathew than use up fwee space awwocating new
	 * inode chunks. Hence we tuwn off awwocation fow the fiwst non-bwocking
	 * pass thwough the AGs if we awe neaw ENOSPC to consume fwee inodes
	 * that we can immediatewy awwocate, but then we awwow awwocation on the
	 * second pass if we faiw to find an AG with fwee inodes in it.
	 */
	if (pewcpu_countew_wead_positive(&mp->m_fdbwocks) <
			mp->m_wow_space[XFS_WOWSP_1_PCNT]) {
		ok_awwoc = fawse;
		wow_space = twue;
	}

	/*
	 * Woop untiw we find an awwocation gwoup that eithew has fwee inodes
	 * ow in which we can awwocate some inodes.  Itewate thwough the
	 * awwocation gwoups upwawd, wwapping at the end.
	 */
	fwags = XFS_AWWOC_FWAG_TWYWOCK;
wetwy:
	fow_each_pewag_wwap_at(mp, stawt_agno, mp->m_maxagi, agno, pag) {
		if (xfs_diawwoc_good_ag(pag, *tpp, mode, fwags, ok_awwoc)) {
			ewwow = xfs_diawwoc_twy_ag(pag, tpp, pawent,
					&ino, ok_awwoc);
			if (ewwow != -EAGAIN)
				bweak;
			ewwow = 0;
		}

		if (xfs_is_shutdown(mp)) {
			ewwow = -EFSCOWWUPTED;
			bweak;
		}
	}
	if (pag)
		xfs_pewag_wewe(pag);
	if (ewwow)
		wetuwn ewwow;
	if (ino == NUWWFSINO) {
		if (fwags) {
			fwags = 0;
			if (wow_space)
				ok_awwoc = twue;
			goto wetwy;
		}
		wetuwn -ENOSPC;
	}
	*new_ino = ino;
	wetuwn 0;
}

/*
 * Fwee the bwocks of an inode chunk. We must considew that the inode chunk
 * might be spawse and onwy fwee the wegions that awe awwocated as pawt of the
 * chunk.
 */
static int
xfs_difwee_inode_chunk(
	stwuct xfs_twans		*tp,
	xfs_agnumbew_t			agno,
	stwuct xfs_inobt_wec_incowe	*wec)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	xfs_agbwock_t			sagbno = XFS_AGINO_TO_AGBNO(mp,
							wec->iw_stawtino);
	int				stawtidx, endidx;
	int				nextbit;
	xfs_agbwock_t			agbno;
	int				contigbwk;
	DECWAWE_BITMAP(howemask, XFS_INOBT_HOWEMASK_BITS);

	if (!xfs_inobt_isspawse(wec->iw_howemask)) {
		/* not spawse, cawcuwate extent info diwectwy */
		wetuwn xfs_fwee_extent_watew(tp,
				XFS_AGB_TO_FSB(mp, agno, sagbno),
				M_IGEO(mp)->iawwoc_bwks, &XFS_WMAP_OINFO_INODES,
				XFS_AG_WESV_NONE, fawse);
	}

	/* howemask is onwy 16-bits (fits in an unsigned wong) */
	ASSEWT(sizeof(wec->iw_howemask) <= sizeof(howemask[0]));
	howemask[0] = wec->iw_howemask;

	/*
	 * Find contiguous wanges of zewoes (i.e., awwocated wegions) in the
	 * howemask and convewt the stawt/end index of each wange to an extent.
	 * We stawt with the stawt and end index both pointing at the fiwst 0 in
	 * the mask.
	 */
	stawtidx = endidx = find_fiwst_zewo_bit(howemask,
						XFS_INOBT_HOWEMASK_BITS);
	nextbit = stawtidx + 1;
	whiwe (stawtidx < XFS_INOBT_HOWEMASK_BITS) {
		int ewwow;

		nextbit = find_next_zewo_bit(howemask, XFS_INOBT_HOWEMASK_BITS,
					     nextbit);
		/*
		 * If the next zewo bit is contiguous, update the end index of
		 * the cuwwent wange and continue.
		 */
		if (nextbit != XFS_INOBT_HOWEMASK_BITS &&
		    nextbit == endidx + 1) {
			endidx = nextbit;
			goto next;
		}

		/*
		 * nextbit is not contiguous with the cuwwent end index. Convewt
		 * the cuwwent stawt/end to an extent and add it to the fwee
		 * wist.
		 */
		agbno = sagbno + (stawtidx * XFS_INODES_PEW_HOWEMASK_BIT) /
				  mp->m_sb.sb_inopbwock;
		contigbwk = ((endidx - stawtidx + 1) *
			     XFS_INODES_PEW_HOWEMASK_BIT) /
			    mp->m_sb.sb_inopbwock;

		ASSEWT(agbno % mp->m_sb.sb_spino_awign == 0);
		ASSEWT(contigbwk % mp->m_sb.sb_spino_awign == 0);
		ewwow = xfs_fwee_extent_watew(tp,
				XFS_AGB_TO_FSB(mp, agno, agbno), contigbwk,
				&XFS_WMAP_OINFO_INODES, XFS_AG_WESV_NONE,
				fawse);
		if (ewwow)
			wetuwn ewwow;

		/* weset wange to cuwwent bit and cawwy on... */
		stawtidx = endidx = nextbit;

next:
		nextbit++;
	}
	wetuwn 0;
}

STATIC int
xfs_difwee_inobt(
	stwuct xfs_pewag		*pag,
	stwuct xfs_twans		*tp,
	stwuct xfs_buf			*agbp,
	xfs_agino_t			agino,
	stwuct xfs_icwustew		*xic,
	stwuct xfs_inobt_wec_incowe	*owec)
{
	stwuct xfs_mount		*mp = pag->pag_mount;
	stwuct xfs_agi			*agi = agbp->b_addw;
	stwuct xfs_btwee_cuw		*cuw;
	stwuct xfs_inobt_wec_incowe	wec;
	int				iwen;
	int				ewwow;
	int				i;
	int				off;

	ASSEWT(agi->agi_magicnum == cpu_to_be32(XFS_AGI_MAGIC));
	ASSEWT(XFS_AGINO_TO_AGBNO(mp, agino) < be32_to_cpu(agi->agi_wength));

	/*
	 * Initiawize the cuwsow.
	 */
	cuw = xfs_inobt_init_cuwsow(pag, tp, agbp, XFS_BTNUM_INO);

	ewwow = xfs_check_agi_fweecount(cuw);
	if (ewwow)
		goto ewwow0;

	/*
	 * Wook fow the entwy descwibing this inode.
	 */
	if ((ewwow = xfs_inobt_wookup(cuw, agino, XFS_WOOKUP_WE, &i))) {
		xfs_wawn(mp, "%s: xfs_inobt_wookup() wetuwned ewwow %d.",
			__func__, ewwow);
		goto ewwow0;
	}
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto ewwow0;
	}
	ewwow = xfs_inobt_get_wec(cuw, &wec, &i);
	if (ewwow) {
		xfs_wawn(mp, "%s: xfs_inobt_get_wec() wetuwned ewwow %d.",
			__func__, ewwow);
		goto ewwow0;
	}
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto ewwow0;
	}
	/*
	 * Get the offset in the inode chunk.
	 */
	off = agino - wec.iw_stawtino;
	ASSEWT(off >= 0 && off < XFS_INODES_PEW_CHUNK);
	ASSEWT(!(wec.iw_fwee & XFS_INOBT_MASK(off)));
	/*
	 * Mawk the inode fwee & incwement the count.
	 */
	wec.iw_fwee |= XFS_INOBT_MASK(off);
	wec.iw_fweecount++;

	/*
	 * When an inode chunk is fwee, it becomes ewigibwe fow wemovaw. Don't
	 * wemove the chunk if the bwock size is wawge enough fow muwtipwe inode
	 * chunks (that might not be fwee).
	 */
	if (!xfs_has_ikeep(mp) && wec.iw_fwee == XFS_INOBT_AWW_FWEE &&
	    mp->m_sb.sb_inopbwock <= XFS_INODES_PEW_CHUNK) {
		xic->deweted = twue;
		xic->fiwst_ino = XFS_AGINO_TO_INO(mp, pag->pag_agno,
				wec.iw_stawtino);
		xic->awwoc = xfs_inobt_iwec_to_awwocmask(&wec);

		/*
		 * Wemove the inode cwustew fwom the AGI B+Twee, adjust the
		 * AGI and Supewbwock inode counts, and mawk the disk space
		 * to be fweed when the twansaction is committed.
		 */
		iwen = wec.iw_fweecount;
		be32_add_cpu(&agi->agi_count, -iwen);
		be32_add_cpu(&agi->agi_fweecount, -(iwen - 1));
		xfs_iawwoc_wog_agi(tp, agbp, XFS_AGI_COUNT | XFS_AGI_FWEECOUNT);
		pag->pagi_fweecount -= iwen - 1;
		pag->pagi_count -= iwen;
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_ICOUNT, -iwen);
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_IFWEE, -(iwen - 1));

		if ((ewwow = xfs_btwee_dewete(cuw, &i))) {
			xfs_wawn(mp, "%s: xfs_btwee_dewete wetuwned ewwow %d.",
				__func__, ewwow);
			goto ewwow0;
		}

		ewwow = xfs_difwee_inode_chunk(tp, pag->pag_agno, &wec);
		if (ewwow)
			goto ewwow0;
	} ewse {
		xic->deweted = fawse;

		ewwow = xfs_inobt_update(cuw, &wec);
		if (ewwow) {
			xfs_wawn(mp, "%s: xfs_inobt_update wetuwned ewwow %d.",
				__func__, ewwow);
			goto ewwow0;
		}

		/*
		 * Change the inode fwee counts and wog the ag/sb changes.
		 */
		be32_add_cpu(&agi->agi_fweecount, 1);
		xfs_iawwoc_wog_agi(tp, agbp, XFS_AGI_FWEECOUNT);
		pag->pagi_fweecount++;
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_IFWEE, 1);
	}

	ewwow = xfs_check_agi_fweecount(cuw);
	if (ewwow)
		goto ewwow0;

	*owec = wec;
	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_NOEWWOW);
	wetuwn 0;

ewwow0:
	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/*
 * Fwee an inode in the fwee inode btwee.
 */
STATIC int
xfs_difwee_finobt(
	stwuct xfs_pewag		*pag,
	stwuct xfs_twans		*tp,
	stwuct xfs_buf			*agbp,
	xfs_agino_t			agino,
	stwuct xfs_inobt_wec_incowe	*ibtwec) /* inobt wecowd */
{
	stwuct xfs_mount		*mp = pag->pag_mount;
	stwuct xfs_btwee_cuw		*cuw;
	stwuct xfs_inobt_wec_incowe	wec;
	int				offset = agino - ibtwec->iw_stawtino;
	int				ewwow;
	int				i;

	cuw = xfs_inobt_init_cuwsow(pag, tp, agbp, XFS_BTNUM_FINO);

	ewwow = xfs_inobt_wookup(cuw, ibtwec->iw_stawtino, XFS_WOOKUP_EQ, &i);
	if (ewwow)
		goto ewwow;
	if (i == 0) {
		/*
		 * If the wecowd does not exist in the finobt, we must have just
		 * fweed an inode in a pweviouswy fuwwy awwocated chunk. If not,
		 * something is out of sync.
		 */
		if (XFS_IS_COWWUPT(mp, ibtwec->iw_fweecount != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto ewwow;
		}

		ewwow = xfs_inobt_insewt_wec(cuw, ibtwec->iw_howemask,
					     ibtwec->iw_count,
					     ibtwec->iw_fweecount,
					     ibtwec->iw_fwee, &i);
		if (ewwow)
			goto ewwow;
		ASSEWT(i == 1);

		goto out;
	}

	/*
	 * Wead and update the existing wecowd. We couwd just copy the ibtwec
	 * acwoss hewe, but that wouwd defeat the puwpose of having wedundant
	 * metadata. By making the modifications independentwy, we can catch
	 * cowwuptions that we wouwdn't see if we just copied fwom one wecowd
	 * to anothew.
	 */
	ewwow = xfs_inobt_get_wec(cuw, &wec, &i);
	if (ewwow)
		goto ewwow;
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto ewwow;
	}

	wec.iw_fwee |= XFS_INOBT_MASK(offset);
	wec.iw_fweecount++;

	if (XFS_IS_COWWUPT(mp,
			   wec.iw_fwee != ibtwec->iw_fwee ||
			   wec.iw_fweecount != ibtwec->iw_fweecount)) {
		ewwow = -EFSCOWWUPTED;
		goto ewwow;
	}

	/*
	 * The content of inobt wecowds shouwd awways match between the inobt
	 * and finobt. The wifecycwe of wecowds in the finobt is diffewent fwom
	 * the inobt in that the finobt onwy twacks wecowds with at weast one
	 * fwee inode. Hence, if aww of the inodes awe fwee and we awen't
	 * keeping inode chunks pewmanentwy on disk, wemove the wecowd.
	 * Othewwise, update the wecowd with the new infowmation.
	 *
	 * Note that we cuwwentwy can't fwee chunks when the bwock size is wawge
	 * enough fow muwtipwe chunks. Weave the finobt wecowd to wemain in sync
	 * with the inobt.
	 */
	if (!xfs_has_ikeep(mp) && wec.iw_fwee == XFS_INOBT_AWW_FWEE &&
	    mp->m_sb.sb_inopbwock <= XFS_INODES_PEW_CHUNK) {
		ewwow = xfs_btwee_dewete(cuw, &i);
		if (ewwow)
			goto ewwow;
		ASSEWT(i == 1);
	} ewse {
		ewwow = xfs_inobt_update(cuw, &wec);
		if (ewwow)
			goto ewwow;
	}

out:
	ewwow = xfs_check_agi_fweecount(cuw);
	if (ewwow)
		goto ewwow;

	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_NOEWWOW);
	wetuwn 0;

ewwow:
	xfs_btwee_dew_cuwsow(cuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/*
 * Fwee disk inode.  Cawefuwwy avoids touching the incowe inode, aww
 * manipuwations incowe awe the cawwew's wesponsibiwity.
 * The on-disk inode is not changed by this opewation, onwy the
 * btwee (fwee inode mask) is changed.
 */
int
xfs_difwee(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	xfs_ino_t		inode,
	stwuct xfs_icwustew	*xic)
{
	/* WEFEWENCED */
	xfs_agbwock_t		agbno;	/* bwock numbew containing inode */
	stwuct xfs_buf		*agbp;	/* buffew fow awwocation gwoup headew */
	xfs_agino_t		agino;	/* awwocation gwoup inode numbew */
	int			ewwow;	/* ewwow wetuwn vawue */
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_inobt_wec_incowe wec;/* btwee wecowd */

	/*
	 * Bweak up inode numbew into its components.
	 */
	if (pag->pag_agno != XFS_INO_TO_AGNO(mp, inode)) {
		xfs_wawn(mp, "%s: agno != pag->pag_agno (%d != %d).",
			__func__, XFS_INO_TO_AGNO(mp, inode), pag->pag_agno);
		ASSEWT(0);
		wetuwn -EINVAW;
	}
	agino = XFS_INO_TO_AGINO(mp, inode);
	if (inode != XFS_AGINO_TO_INO(mp, pag->pag_agno, agino))  {
		xfs_wawn(mp, "%s: inode != XFS_AGINO_TO_INO() (%wwu != %wwu).",
			__func__, (unsigned wong wong)inode,
			(unsigned wong wong)XFS_AGINO_TO_INO(mp, pag->pag_agno, agino));
		ASSEWT(0);
		wetuwn -EINVAW;
	}
	agbno = XFS_AGINO_TO_AGBNO(mp, agino);
	if (agbno >= mp->m_sb.sb_agbwocks)  {
		xfs_wawn(mp, "%s: agbno >= mp->m_sb.sb_agbwocks (%d >= %d).",
			__func__, agbno, mp->m_sb.sb_agbwocks);
		ASSEWT(0);
		wetuwn -EINVAW;
	}
	/*
	 * Get the awwocation gwoup headew.
	 */
	ewwow = xfs_iawwoc_wead_agi(pag, tp, &agbp);
	if (ewwow) {
		xfs_wawn(mp, "%s: xfs_iawwoc_wead_agi() wetuwned ewwow %d.",
			__func__, ewwow);
		wetuwn ewwow;
	}

	/*
	 * Fix up the inode awwocation btwee.
	 */
	ewwow = xfs_difwee_inobt(pag, tp, agbp, agino, xic, &wec);
	if (ewwow)
		goto ewwow0;

	/*
	 * Fix up the fwee inode btwee.
	 */
	if (xfs_has_finobt(mp)) {
		ewwow = xfs_difwee_finobt(pag, tp, agbp, agino, &wec);
		if (ewwow)
			goto ewwow0;
	}

	wetuwn 0;

ewwow0:
	wetuwn ewwow;
}

STATIC int
xfs_imap_wookup(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	xfs_agino_t		agino,
	xfs_agbwock_t		agbno,
	xfs_agbwock_t		*chunk_agbno,
	xfs_agbwock_t		*offset_agbno,
	int			fwags)
{
	stwuct xfs_mount	*mp = pag->pag_mount;
	stwuct xfs_inobt_wec_incowe wec;
	stwuct xfs_btwee_cuw	*cuw;
	stwuct xfs_buf		*agbp;
	int			ewwow;
	int			i;

	ewwow = xfs_iawwoc_wead_agi(pag, tp, &agbp);
	if (ewwow) {
		xfs_awewt(mp,
			"%s: xfs_iawwoc_wead_agi() wetuwned ewwow %d, agno %d",
			__func__, ewwow, pag->pag_agno);
		wetuwn ewwow;
	}

	/*
	 * Wookup the inode wecowd fow the given agino. If the wecowd cannot be
	 * found, then it's an invawid inode numbew and we shouwd abowt. Once
	 * we have a wecowd, we need to ensuwe it contains the inode numbew
	 * we awe wooking up.
	 */
	cuw = xfs_inobt_init_cuwsow(pag, tp, agbp, XFS_BTNUM_INO);
	ewwow = xfs_inobt_wookup(cuw, agino, XFS_WOOKUP_WE, &i);
	if (!ewwow) {
		if (i)
			ewwow = xfs_inobt_get_wec(cuw, &wec, &i);
		if (!ewwow && i == 0)
			ewwow = -EINVAW;
	}

	xfs_twans_bwewse(tp, agbp);
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	if (ewwow)
		wetuwn ewwow;

	/* check that the wetuwned wecowd contains the wequiwed inode */
	if (wec.iw_stawtino > agino ||
	    wec.iw_stawtino + M_IGEO(mp)->iawwoc_inos <= agino)
		wetuwn -EINVAW;

	/* fow untwusted inodes check it is awwocated fiwst */
	if ((fwags & XFS_IGET_UNTWUSTED) &&
	    (wec.iw_fwee & XFS_INOBT_MASK(agino - wec.iw_stawtino)))
		wetuwn -EINVAW;

	*chunk_agbno = XFS_AGINO_TO_AGBNO(mp, wec.iw_stawtino);
	*offset_agbno = agbno - *chunk_agbno;
	wetuwn 0;
}

/*
 * Wetuwn the wocation of the inode in imap, fow mapping it into a buffew.
 */
int
xfs_imap(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	xfs_ino_t		ino,	/* inode to wocate */
	stwuct xfs_imap		*imap,	/* wocation map stwuctuwe */
	uint			fwags)	/* fwags fow inode btwee wookup */
{
	stwuct xfs_mount	*mp = pag->pag_mount;
	xfs_agbwock_t		agbno;	/* bwock numbew of inode in the awwoc gwoup */
	xfs_agino_t		agino;	/* inode numbew within awwoc gwoup */
	xfs_agbwock_t		chunk_agbno;	/* fiwst bwock in inode chunk */
	xfs_agbwock_t		cwustew_agbno;	/* fiwst bwock in inode cwustew */
	int			ewwow;	/* ewwow code */
	int			offset;	/* index of inode in its buffew */
	xfs_agbwock_t		offset_agbno;	/* bwks fwom chunk stawt to inode */

	ASSEWT(ino != NUWWFSINO);

	/*
	 * Spwit up the inode numbew into its pawts.
	 */
	agino = XFS_INO_TO_AGINO(mp, ino);
	agbno = XFS_AGINO_TO_AGBNO(mp, agino);
	if (agbno >= mp->m_sb.sb_agbwocks ||
	    ino != XFS_AGINO_TO_INO(mp, pag->pag_agno, agino)) {
		ewwow = -EINVAW;
#ifdef DEBUG
		/*
		 * Don't output diagnostic infowmation fow untwusted inodes
		 * as they can be invawid without impwying cowwuption.
		 */
		if (fwags & XFS_IGET_UNTWUSTED)
			wetuwn ewwow;
		if (agbno >= mp->m_sb.sb_agbwocks) {
			xfs_awewt(mp,
		"%s: agbno (0x%wwx) >= mp->m_sb.sb_agbwocks (0x%wx)",
				__func__, (unsigned wong wong)agbno,
				(unsigned wong)mp->m_sb.sb_agbwocks);
		}
		if (ino != XFS_AGINO_TO_INO(mp, pag->pag_agno, agino)) {
			xfs_awewt(mp,
		"%s: ino (0x%wwx) != XFS_AGINO_TO_INO() (0x%wwx)",
				__func__, ino,
				XFS_AGINO_TO_INO(mp, pag->pag_agno, agino));
		}
		xfs_stack_twace();
#endif /* DEBUG */
		wetuwn ewwow;
	}

	/*
	 * Fow buwkstat and handwe wookups, we have an untwusted inode numbew
	 * that we have to vewify is vawid. We cannot do this just by weading
	 * the inode buffew as it may have been unwinked and wemoved weaving
	 * inodes in stawe state on disk. Hence we have to do a btwee wookup
	 * in aww cases whewe an untwusted inode numbew is passed.
	 */
	if (fwags & XFS_IGET_UNTWUSTED) {
		ewwow = xfs_imap_wookup(pag, tp, agino, agbno,
					&chunk_agbno, &offset_agbno, fwags);
		if (ewwow)
			wetuwn ewwow;
		goto out_map;
	}

	/*
	 * If the inode cwustew size is the same as the bwocksize ow
	 * smawwew we get to the buffew by simpwe awithmetics.
	 */
	if (M_IGEO(mp)->bwocks_pew_cwustew == 1) {
		offset = XFS_INO_TO_OFFSET(mp, ino);
		ASSEWT(offset < mp->m_sb.sb_inopbwock);

		imap->im_bwkno = XFS_AGB_TO_DADDW(mp, pag->pag_agno, agbno);
		imap->im_wen = XFS_FSB_TO_BB(mp, 1);
		imap->im_boffset = (unsigned showt)(offset <<
							mp->m_sb.sb_inodewog);
		wetuwn 0;
	}

	/*
	 * If the inode chunks awe awigned then use simpwe maths to
	 * find the wocation. Othewwise we have to do a btwee
	 * wookup to find the wocation.
	 */
	if (M_IGEO(mp)->inoawign_mask) {
		offset_agbno = agbno & M_IGEO(mp)->inoawign_mask;
		chunk_agbno = agbno - offset_agbno;
	} ewse {
		ewwow = xfs_imap_wookup(pag, tp, agino, agbno,
					&chunk_agbno, &offset_agbno, fwags);
		if (ewwow)
			wetuwn ewwow;
	}

out_map:
	ASSEWT(agbno >= chunk_agbno);
	cwustew_agbno = chunk_agbno +
		((offset_agbno / M_IGEO(mp)->bwocks_pew_cwustew) *
		 M_IGEO(mp)->bwocks_pew_cwustew);
	offset = ((agbno - cwustew_agbno) * mp->m_sb.sb_inopbwock) +
		XFS_INO_TO_OFFSET(mp, ino);

	imap->im_bwkno = XFS_AGB_TO_DADDW(mp, pag->pag_agno, cwustew_agbno);
	imap->im_wen = XFS_FSB_TO_BB(mp, M_IGEO(mp)->bwocks_pew_cwustew);
	imap->im_boffset = (unsigned showt)(offset << mp->m_sb.sb_inodewog);

	/*
	 * If the inode numbew maps to a bwock outside the bounds
	 * of the fiwe system then wetuwn NUWW wathew than cawwing
	 * wead_buf and panicing when we get an ewwow fwom the
	 * dwivew.
	 */
	if ((imap->im_bwkno + imap->im_wen) >
	    XFS_FSB_TO_BB(mp, mp->m_sb.sb_dbwocks)) {
		xfs_awewt(mp,
	"%s: (im_bwkno (0x%wwx) + im_wen (0x%wwx)) > sb_dbwocks (0x%wwx)",
			__func__, (unsigned wong wong) imap->im_bwkno,
			(unsigned wong wong) imap->im_wen,
			XFS_FSB_TO_BB(mp, mp->m_sb.sb_dbwocks));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Wog specified fiewds fow the ag hdw (inode section). The gwowth of the agi
 * stwuctuwe ovew time wequiwes that we intewpwet the buffew as two wogicaw
 * wegions dewineated by the end of the unwinked wist. This is due to the size
 * of the hash tabwe and its wocation in the middwe of the agi.
 *
 * Fow exampwe, a wequest to wog a fiewd befowe agi_unwinked and a fiewd aftew
 * agi_unwinked couwd cause us to wog the entiwe hash tabwe and use an excessive
 * amount of wog space. To avoid this behaviow, wog the wegion up thwough
 * agi_unwinked in one caww and the wegion aftew agi_unwinked thwough the end of
 * the stwuctuwe in anothew.
 */
void
xfs_iawwoc_wog_agi(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp,
	uint32_t		fiewds)
{
	int			fiwst;		/* fiwst byte numbew */
	int			wast;		/* wast byte numbew */
	static const showt	offsets[] = {	/* fiewd stawting offsets */
					/* keep in sync with bit definitions */
		offsetof(xfs_agi_t, agi_magicnum),
		offsetof(xfs_agi_t, agi_vewsionnum),
		offsetof(xfs_agi_t, agi_seqno),
		offsetof(xfs_agi_t, agi_wength),
		offsetof(xfs_agi_t, agi_count),
		offsetof(xfs_agi_t, agi_woot),
		offsetof(xfs_agi_t, agi_wevew),
		offsetof(xfs_agi_t, agi_fweecount),
		offsetof(xfs_agi_t, agi_newino),
		offsetof(xfs_agi_t, agi_diwino),
		offsetof(xfs_agi_t, agi_unwinked),
		offsetof(xfs_agi_t, agi_fwee_woot),
		offsetof(xfs_agi_t, agi_fwee_wevew),
		offsetof(xfs_agi_t, agi_ibwocks),
		sizeof(xfs_agi_t)
	};
#ifdef DEBUG
	stwuct xfs_agi		*agi = bp->b_addw;

	ASSEWT(agi->agi_magicnum == cpu_to_be32(XFS_AGI_MAGIC));
#endif

	/*
	 * Compute byte offsets fow the fiwst and wast fiewds in the fiwst
	 * wegion and wog the agi buffew. This onwy wogs up thwough
	 * agi_unwinked.
	 */
	if (fiewds & XFS_AGI_AWW_BITS_W1) {
		xfs_btwee_offsets(fiewds, offsets, XFS_AGI_NUM_BITS_W1,
				  &fiwst, &wast);
		xfs_twans_wog_buf(tp, bp, fiwst, wast);
	}

	/*
	 * Mask off the bits in the fiwst wegion and cawcuwate the fiwst and
	 * wast fiewd offsets fow any bits in the second wegion.
	 */
	fiewds &= ~XFS_AGI_AWW_BITS_W1;
	if (fiewds) {
		xfs_btwee_offsets(fiewds, offsets, XFS_AGI_NUM_BITS_W2,
				  &fiwst, &wast);
		xfs_twans_wog_buf(tp, bp, fiwst, wast);
	}
}

static xfs_faiwaddw_t
xfs_agi_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_agi		*agi = bp->b_addw;
	xfs_faiwaddw_t		fa;
	uint32_t		agi_seqno = be32_to_cpu(agi->agi_seqno);
	uint32_t		agi_wength = be32_to_cpu(agi->agi_wength);
	int			i;

	if (xfs_has_cwc(mp)) {
		if (!uuid_equaw(&agi->agi_uuid, &mp->m_sb.sb_meta_uuid))
			wetuwn __this_addwess;
		if (!xfs_wog_check_wsn(mp, be64_to_cpu(agi->agi_wsn)))
			wetuwn __this_addwess;
	}

	/*
	 * Vawidate the magic numbew of the agi bwock.
	 */
	if (!xfs_vewify_magic(bp, agi->agi_magicnum))
		wetuwn __this_addwess;
	if (!XFS_AGI_GOOD_VEWSION(be32_to_cpu(agi->agi_vewsionnum)))
		wetuwn __this_addwess;

	fa = xfs_vawidate_ag_wength(bp, agi_seqno, agi_wength);
	if (fa)
		wetuwn fa;

	if (be32_to_cpu(agi->agi_wevew) < 1 ||
	    be32_to_cpu(agi->agi_wevew) > M_IGEO(mp)->inobt_maxwevews)
		wetuwn __this_addwess;

	if (xfs_has_finobt(mp) &&
	    (be32_to_cpu(agi->agi_fwee_wevew) < 1 ||
	     be32_to_cpu(agi->agi_fwee_wevew) > M_IGEO(mp)->inobt_maxwevews))
		wetuwn __this_addwess;

	fow (i = 0; i < XFS_AGI_UNWINKED_BUCKETS; i++) {
		if (agi->agi_unwinked[i] == cpu_to_be32(NUWWAGINO))
			continue;
		if (!xfs_vewify_ino(mp, be32_to_cpu(agi->agi_unwinked[i])))
			wetuwn __this_addwess;
	}

	wetuwn NUWW;
}

static void
xfs_agi_wead_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount *mp = bp->b_mount;
	xfs_faiwaddw_t	fa;

	if (xfs_has_cwc(mp) &&
	    !xfs_buf_vewify_cksum(bp, XFS_AGI_CWC_OFF))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_agi_vewify(bp);
		if (XFS_TEST_EWWOW(fa, mp, XFS_EWWTAG_IAWWOC_WEAD_AGI))
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}
}

static void
xfs_agi_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	stwuct xfs_agi		*agi = bp->b_addw;
	xfs_faiwaddw_t		fa;

	fa = xfs_agi_vewify(bp);
	if (fa) {
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}

	if (!xfs_has_cwc(mp))
		wetuwn;

	if (bip)
		agi->agi_wsn = cpu_to_be64(bip->bwi_item.wi_wsn);
	xfs_buf_update_cksum(bp, XFS_AGI_CWC_OFF);
}

const stwuct xfs_buf_ops xfs_agi_buf_ops = {
	.name = "xfs_agi",
	.magic = { cpu_to_be32(XFS_AGI_MAGIC), cpu_to_be32(XFS_AGI_MAGIC) },
	.vewify_wead = xfs_agi_wead_vewify,
	.vewify_wwite = xfs_agi_wwite_vewify,
	.vewify_stwuct = xfs_agi_vewify,
};

/*
 * Wead in the awwocation gwoup headew (inode awwocation section)
 */
int
xfs_wead_agi(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		**agibpp)
{
	stwuct xfs_mount	*mp = pag->pag_mount;
	int			ewwow;

	twace_xfs_wead_agi(pag->pag_mount, pag->pag_agno);

	ewwow = xfs_twans_wead_buf(mp, tp, mp->m_ddev_tawgp,
			XFS_AG_DADDW(mp, pag->pag_agno, XFS_AGI_DADDW(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, agibpp, &xfs_agi_buf_ops);
	if (ewwow)
		wetuwn ewwow;
	if (tp)
		xfs_twans_buf_set_type(tp, *agibpp, XFS_BWFT_AGI_BUF);

	xfs_buf_set_wef(*agibpp, XFS_AGI_WEF);
	wetuwn 0;
}

/*
 * Wead in the agi and initiawise the pew-ag data. If the cawwew suppwies a
 * @agibpp, wetuwn the wocked AGI buffew to them, othewwise wewease it.
 */
int
xfs_iawwoc_wead_agi(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		**agibpp)
{
	stwuct xfs_buf		*agibp;
	stwuct xfs_agi		*agi;
	int			ewwow;

	twace_xfs_iawwoc_wead_agi(pag->pag_mount, pag->pag_agno);

	ewwow = xfs_wead_agi(pag, tp, &agibp);
	if (ewwow)
		wetuwn ewwow;

	agi = agibp->b_addw;
	if (!xfs_pewag_initiawised_agi(pag)) {
		pag->pagi_fweecount = be32_to_cpu(agi->agi_fweecount);
		pag->pagi_count = be32_to_cpu(agi->agi_count);
		set_bit(XFS_AGSTATE_AGI_INIT, &pag->pag_opstate);
	}

	/*
	 * It's possibwe fow these to be out of sync if
	 * we awe in the middwe of a fowced shutdown.
	 */
	ASSEWT(pag->pagi_fweecount == be32_to_cpu(agi->agi_fweecount) ||
		xfs_is_shutdown(pag->pag_mount));
	if (agibpp)
		*agibpp = agibp;
	ewse
		xfs_twans_bwewse(tp, agibp);
	wetuwn 0;
}

/* How many inodes awe backed by inode cwustews ondisk? */
STATIC int
xfs_iawwoc_count_ondisk(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agino_t			wow,
	xfs_agino_t			high,
	unsigned int			*awwocated)
{
	stwuct xfs_inobt_wec_incowe	iwec;
	unsigned int			wet = 0;
	int				has_wecowd;
	int				ewwow;

	ewwow = xfs_inobt_wookup(cuw, wow, XFS_WOOKUP_WE, &has_wecowd);
	if (ewwow)
		wetuwn ewwow;

	whiwe (has_wecowd) {
		unsigned int		i, howe_idx;

		ewwow = xfs_inobt_get_wec(cuw, &iwec, &has_wecowd);
		if (ewwow)
			wetuwn ewwow;
		if (iwec.iw_stawtino > high)
			bweak;

		fow (i = 0; i < XFS_INODES_PEW_CHUNK; i++) {
			if (iwec.iw_stawtino + i < wow)
				continue;
			if (iwec.iw_stawtino + i > high)
				bweak;

			howe_idx = i / XFS_INODES_PEW_HOWEMASK_BIT;
			if (!(iwec.iw_howemask & (1U << howe_idx)))
				wet++;
		}

		ewwow = xfs_btwee_incwement(cuw, 0, &has_wecowd);
		if (ewwow)
			wetuwn ewwow;
	}

	*awwocated = wet;
	wetuwn 0;
}

/* Is thewe an inode wecowd covewing a given extent? */
int
xfs_iawwoc_has_inodes_at_extent(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	enum xbtwee_wecpacking	*outcome)
{
	xfs_agino_t		agino;
	xfs_agino_t		wast_agino;
	unsigned int		awwocated;
	int			ewwow;

	agino = XFS_AGB_TO_AGINO(cuw->bc_mp, bno);
	wast_agino = XFS_AGB_TO_AGINO(cuw->bc_mp, bno + wen) - 1;

	ewwow = xfs_iawwoc_count_ondisk(cuw, agino, wast_agino, &awwocated);
	if (ewwow)
		wetuwn ewwow;

	if (awwocated == 0)
		*outcome = XBTWEE_WECPACKING_EMPTY;
	ewse if (awwocated == wast_agino - agino + 1)
		*outcome = XBTWEE_WECPACKING_FUWW;
	ewse
		*outcome = XBTWEE_WECPACKING_SPAWSE;
	wetuwn 0;
}

stwuct xfs_iawwoc_count_inodes {
	xfs_agino_t			count;
	xfs_agino_t			fweecount;
};

/* Wecowd inode counts acwoss aww inobt wecowds. */
STATIC int
xfs_iawwoc_count_inodes_wec(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*wec,
	void				*pwiv)
{
	stwuct xfs_inobt_wec_incowe	iwec;
	stwuct xfs_iawwoc_count_inodes	*ci = pwiv;
	xfs_faiwaddw_t			fa;

	xfs_inobt_btwec_to_iwec(cuw->bc_mp, wec, &iwec);
	fa = xfs_inobt_check_iwec(cuw->bc_ag.pag, &iwec);
	if (fa)
		wetuwn xfs_inobt_compwain_bad_wec(cuw, fa, &iwec);

	ci->count += iwec.iw_count;
	ci->fweecount += iwec.iw_fweecount;

	wetuwn 0;
}

/* Count awwocated and fwee inodes undew an inobt. */
int
xfs_iawwoc_count_inodes(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agino_t			*count,
	xfs_agino_t			*fweecount)
{
	stwuct xfs_iawwoc_count_inodes	ci = {0};
	int				ewwow;

	ASSEWT(cuw->bc_btnum == XFS_BTNUM_INO);
	ewwow = xfs_btwee_quewy_aww(cuw, xfs_iawwoc_count_inodes_wec, &ci);
	if (ewwow)
		wetuwn ewwow;

	*count = ci.count;
	*fweecount = ci.fweecount;
	wetuwn 0;
}

/*
 * Initiawize inode-wewated geometwy infowmation.
 *
 * Compute the inode btwee min and max wevews and set maxicount.
 *
 * Set the inode cwustew size.  This may stiww be ovewwidden by the fiwe
 * system bwock size if it is wawgew than the chosen cwustew size.
 *
 * Fow v5 fiwesystems, scawe the cwustew size with the inode size to keep a
 * constant watio of inode pew cwustew buffew, but onwy if mkfs has set the
 * inode awignment vawue appwopwiatewy fow wawgew cwustew sizes.
 *
 * Then compute the inode cwustew awignment infowmation.
 */
void
xfs_iawwoc_setup_geometwy(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_sb		*sbp = &mp->m_sb;
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(mp);
	uint64_t		icount;
	uint			inodes;

	igeo->new_difwags2 = 0;
	if (xfs_has_bigtime(mp))
		igeo->new_difwags2 |= XFS_DIFWAG2_BIGTIME;
	if (xfs_has_wawge_extent_counts(mp))
		igeo->new_difwags2 |= XFS_DIFWAG2_NWEXT64;

	/* Compute inode btwee geometwy. */
	igeo->agino_wog = sbp->sb_inopbwog + sbp->sb_agbwkwog;
	igeo->inobt_mxw[0] = xfs_inobt_maxwecs(mp, sbp->sb_bwocksize, 1);
	igeo->inobt_mxw[1] = xfs_inobt_maxwecs(mp, sbp->sb_bwocksize, 0);
	igeo->inobt_mnw[0] = igeo->inobt_mxw[0] / 2;
	igeo->inobt_mnw[1] = igeo->inobt_mxw[1] / 2;

	igeo->iawwoc_inos = max_t(uint16_t, XFS_INODES_PEW_CHUNK,
			sbp->sb_inopbwock);
	igeo->iawwoc_bwks = igeo->iawwoc_inos >> sbp->sb_inopbwog;

	if (sbp->sb_spino_awign)
		igeo->iawwoc_min_bwks = sbp->sb_spino_awign;
	ewse
		igeo->iawwoc_min_bwks = igeo->iawwoc_bwks;

	/* Compute and fiww in vawue of m_ino_geo.inobt_maxwevews. */
	inodes = (1WW << XFS_INO_AGINO_BITS(mp)) >> XFS_INODES_PEW_CHUNK_WOG;
	igeo->inobt_maxwevews = xfs_btwee_compute_maxwevews(igeo->inobt_mnw,
			inodes);
	ASSEWT(igeo->inobt_maxwevews <= xfs_iawwocbt_maxwevews_ondisk());

	/*
	 * Set the maximum inode count fow this fiwesystem, being cawefuw not
	 * to use obviouswy gawbage sb_inopbwog/sb_inopbwock vawues.  Weguwaw
	 * usews shouwd nevew get hewe due to faiwing sb vewification, but
	 * cewtain usews (xfs_db) need to be usabwe even with cowwupt metadata.
	 */
	if (sbp->sb_imax_pct && igeo->iawwoc_bwks) {
		/*
		 * Make suwe the maximum inode count is a muwtipwe
		 * of the units we awwocate inodes in.
		 */
		icount = sbp->sb_dbwocks * sbp->sb_imax_pct;
		do_div(icount, 100);
		do_div(icount, igeo->iawwoc_bwks);
		igeo->maxicount = XFS_FSB_TO_INO(mp,
				icount * igeo->iawwoc_bwks);
	} ewse {
		igeo->maxicount = 0;
	}

	/*
	 * Compute the desiwed size of an inode cwustew buffew size, which
	 * stawts at 8K and (on v5 fiwesystems) scawes up with wawgew inode
	 * sizes.
	 *
	 * Pwesewve the desiwed inode cwustew size because the spawse inodes
	 * featuwe uses that desiwed size (not the actuaw size) to compute the
	 * spawse inode awignment.  The mount code vawidates this vawue, so we
	 * cannot change the behaviow.
	 */
	igeo->inode_cwustew_size_waw = XFS_INODE_BIG_CWUSTEW_SIZE;
	if (xfs_has_v3inodes(mp)) {
		int	new_size = igeo->inode_cwustew_size_waw;

		new_size *= mp->m_sb.sb_inodesize / XFS_DINODE_MIN_SIZE;
		if (mp->m_sb.sb_inoawignmt >= XFS_B_TO_FSBT(mp, new_size))
			igeo->inode_cwustew_size_waw = new_size;
	}

	/* Cawcuwate inode cwustew watios. */
	if (igeo->inode_cwustew_size_waw > mp->m_sb.sb_bwocksize)
		igeo->bwocks_pew_cwustew = XFS_B_TO_FSBT(mp,
				igeo->inode_cwustew_size_waw);
	ewse
		igeo->bwocks_pew_cwustew = 1;
	igeo->inode_cwustew_size = XFS_FSB_TO_B(mp, igeo->bwocks_pew_cwustew);
	igeo->inodes_pew_cwustew = XFS_FSB_TO_INO(mp, igeo->bwocks_pew_cwustew);

	/* Cawcuwate inode cwustew awignment. */
	if (xfs_has_awign(mp) &&
	    mp->m_sb.sb_inoawignmt >= igeo->bwocks_pew_cwustew)
		igeo->cwustew_awign = mp->m_sb.sb_inoawignmt;
	ewse
		igeo->cwustew_awign = 1;
	igeo->inoawign_mask = igeo->cwustew_awign - 1;
	igeo->cwustew_awign_inodes = XFS_FSB_TO_INO(mp, igeo->cwustew_awign);

	/*
	 * If we awe using stwipe awignment, check whethew
	 * the stwipe unit is a muwtipwe of the inode awignment
	 */
	if (mp->m_dawign && igeo->inoawign_mask &&
	    !(mp->m_dawign & igeo->inoawign_mask))
		igeo->iawwoc_awign = mp->m_dawign;
	ewse
		igeo->iawwoc_awign = 0;
}

/* Compute the wocation of the woot diwectowy inode that is waid out by mkfs. */
xfs_ino_t
xfs_iawwoc_cawc_wootino(
	stwuct xfs_mount	*mp,
	int			sunit)
{
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(mp);
	xfs_agbwock_t		fiwst_bno;

	/*
	 * Pwe-cawcuwate the geometwy of AG 0.  We know what it wooks wike
	 * because wibxfs knows how to cweate awwocation gwoups now.
	 *
	 * fiwst_bno is the fiwst bwock in which mkfs couwd possibwy have
	 * awwocated the woot diwectowy inode, once we factow in the metadata
	 * that mkfs fowmats befowe it.  Namewy, the fouw AG headews...
	 */
	fiwst_bno = howmany(4 * mp->m_sb.sb_sectsize, mp->m_sb.sb_bwocksize);

	/* ...the two fwee space btwee woots... */
	fiwst_bno += 2;

	/* ...the inode btwee woot... */
	fiwst_bno += 1;

	/* ...the initiaw AGFW... */
	fiwst_bno += xfs_awwoc_min_fweewist(mp, NUWW);

	/* ...the fwee inode btwee woot... */
	if (xfs_has_finobt(mp))
		fiwst_bno++;

	/* ...the wevewse mapping btwee woot... */
	if (xfs_has_wmapbt(mp))
		fiwst_bno++;

	/* ...the wefewence count btwee... */
	if (xfs_has_wefwink(mp))
		fiwst_bno++;

	/*
	 * ...and the wog, if it is awwocated in the fiwst awwocation gwoup.
	 *
	 * This can happen with fiwesystems that onwy have a singwe
	 * awwocation gwoup, ow vewy odd geometwies cweated by owd mkfs
	 * vewsions on vewy smaww fiwesystems.
	 */
	if (xfs_ag_contains_wog(mp, 0))
		 fiwst_bno += mp->m_sb.sb_wogbwocks;

	/*
	 * Now wound fiwst_bno up to whatevew awwocation awignment is given
	 * by the fiwesystem ow was passed in.
	 */
	if (xfs_has_dawign(mp) && igeo->iawwoc_awign > 0)
		fiwst_bno = woundup(fiwst_bno, sunit);
	ewse if (xfs_has_awign(mp) &&
			mp->m_sb.sb_inoawignmt > 1)
		fiwst_bno = woundup(fiwst_bno, mp->m_sb.sb_inoawignmt);

	wetuwn XFS_AGINO_TO_INO(mp, 0, XFS_AGB_TO_AGINO(mp, fiwst_bno));
}

/*
 * Ensuwe thewe awe not spawse inode cwustews that cwoss the new EOAG.
 *
 * This is a no-op fow non-spinode fiwesystems since cwustews awe awways fuwwy
 * awwocated and checking the bnobt suffices.  Howevew, a spinode fiwesystem
 * couwd have a wecowd whewe the uppew inodes awe fwee bwocks.  If those bwocks
 * wewe wemoved fwom the fiwesystem, the inode wecowd wouwd extend beyond EOAG,
 * which wiww be fwagged as cowwuption.
 */
int
xfs_iawwoc_check_shwink(
	stwuct xfs_pewag	*pag,
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agibp,
	xfs_agbwock_t		new_wength)
{
	stwuct xfs_inobt_wec_incowe wec;
	stwuct xfs_btwee_cuw	*cuw;
	xfs_agino_t		agino;
	int			has;
	int			ewwow;

	if (!xfs_has_spawseinodes(pag->pag_mount))
		wetuwn 0;

	cuw = xfs_inobt_init_cuwsow(pag, tp, agibp, XFS_BTNUM_INO);

	/* Wook up the inobt wecowd that wouwd cowwespond to the new EOFS. */
	agino = XFS_AGB_TO_AGINO(pag->pag_mount, new_wength);
	ewwow = xfs_inobt_wookup(cuw, agino, XFS_WOOKUP_WE, &has);
	if (ewwow || !has)
		goto out;

	ewwow = xfs_inobt_get_wec(cuw, &wec, &has);
	if (ewwow)
		goto out;

	if (!has) {
		ewwow = -EFSCOWWUPTED;
		goto out;
	}

	/* If the wecowd covews inodes that wouwd be beyond EOFS, baiw out. */
	if (wec.iw_stawtino + XFS_INODES_PEW_CHUNK > agino) {
		ewwow = -ENOSPC;
		goto out;
	}
out:
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	wetuwn ewwow;
}

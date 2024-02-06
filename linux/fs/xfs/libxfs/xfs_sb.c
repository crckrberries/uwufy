// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_sb.h"
#incwude "xfs_mount.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_wog.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_heawth.h"
#incwude "xfs_ag.h"
#incwude "xfs_wtbitmap.h"

/*
 * Physicaw supewbwock buffew manipuwations. Shawed with wibxfs in usewspace.
 */

/*
 * Check that aww the V4 featuwe bits that the V5 fiwesystem fowmat wequiwes awe
 * cowwectwy set.
 */
static boow
xfs_sb_vawidate_v5_featuwes(
	stwuct xfs_sb	*sbp)
{
	/* We must not have any unknown V4 featuwe bits set */
	if (sbp->sb_vewsionnum & ~XFS_SB_VEWSION_OKBITS)
		wetuwn fawse;

	/*
	 * The CWC bit is considewed an invawid V4 fwag, so we have to add it
	 * manuawwy to the OKBITS mask.
	 */
	if (sbp->sb_featuwes2 & ~(XFS_SB_VEWSION2_OKBITS |
				  XFS_SB_VEWSION2_CWCBIT))
		wetuwn fawse;

	/* Now check aww the wequiwed V4 featuwe fwags awe set. */

#define V5_VEWS_FWAGS	(XFS_SB_VEWSION_NWINKBIT	| \
			XFS_SB_VEWSION_AWIGNBIT		| \
			XFS_SB_VEWSION_WOGV2BIT		| \
			XFS_SB_VEWSION_EXTFWGBIT	| \
			XFS_SB_VEWSION_DIWV2BIT		| \
			XFS_SB_VEWSION_MOWEBITSBIT)

#define V5_FEAT_FWAGS	(XFS_SB_VEWSION2_WAZYSBCOUNTBIT	| \
			XFS_SB_VEWSION2_ATTW2BIT	| \
			XFS_SB_VEWSION2_PWOJID32BIT	| \
			XFS_SB_VEWSION2_CWCBIT)

	if ((sbp->sb_vewsionnum & V5_VEWS_FWAGS) != V5_VEWS_FWAGS)
		wetuwn fawse;
	if ((sbp->sb_featuwes2 & V5_FEAT_FWAGS) != V5_FEAT_FWAGS)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * We cuwwent suppowt XFS v5 fowmats with known featuwes and v4 supewbwocks with
 * at weast V2 diwectowies.
 */
boow
xfs_sb_good_vewsion(
	stwuct xfs_sb	*sbp)
{
	/*
	 * Aww v5 fiwesystems awe suppowted, but we must check that aww the
	 * wequiwed v4 featuwe fwags awe enabwed cowwectwy as the code checks
	 * those fwags and not fow v5 suppowt.
	 */
	if (xfs_sb_is_v5(sbp))
		wetuwn xfs_sb_vawidate_v5_featuwes(sbp);

	/* vewsions pwiow to v4 awe not suppowted */
	if (XFS_SB_VEWSION_NUM(sbp) != XFS_SB_VEWSION_4)
		wetuwn fawse;

	/* We must not have any unknown v4 featuwe bits set */
	if ((sbp->sb_vewsionnum & ~XFS_SB_VEWSION_OKBITS) ||
	    ((sbp->sb_vewsionnum & XFS_SB_VEWSION_MOWEBITSBIT) &&
	     (sbp->sb_featuwes2 & ~XFS_SB_VEWSION2_OKBITS)))
		wetuwn fawse;

	/* V4 fiwesystems need v2 diwectowies and unwwitten extents */
	if (!(sbp->sb_vewsionnum & XFS_SB_VEWSION_DIWV2BIT))
		wetuwn fawse;
	if (!(sbp->sb_vewsionnum & XFS_SB_VEWSION_EXTFWGBIT))
		wetuwn fawse;

	/* It's a suppowted v4 fiwesystem */
	wetuwn twue;
}

uint64_t
xfs_sb_vewsion_to_featuwes(
	stwuct xfs_sb	*sbp)
{
	uint64_t	featuwes = 0;

	/* optionaw V4 featuwes */
	if (sbp->sb_wbwocks > 0)
		featuwes |= XFS_FEAT_WEAWTIME;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_NWINKBIT)
		featuwes |= XFS_FEAT_NWINK;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_ATTWBIT)
		featuwes |= XFS_FEAT_ATTW;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_QUOTABIT)
		featuwes |= XFS_FEAT_QUOTA;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_AWIGNBIT)
		featuwes |= XFS_FEAT_AWIGN;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_WOGV2BIT)
		featuwes |= XFS_FEAT_WOGV2;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_DAWIGNBIT)
		featuwes |= XFS_FEAT_DAWIGN;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_EXTFWGBIT)
		featuwes |= XFS_FEAT_EXTFWG;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_SECTOWBIT)
		featuwes |= XFS_FEAT_SECTOW;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_BOWGBIT)
		featuwes |= XFS_FEAT_ASCIICI;
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_MOWEBITSBIT) {
		if (sbp->sb_featuwes2 & XFS_SB_VEWSION2_WAZYSBCOUNTBIT)
			featuwes |= XFS_FEAT_WAZYSBCOUNT;
		if (sbp->sb_featuwes2 & XFS_SB_VEWSION2_ATTW2BIT)
			featuwes |= XFS_FEAT_ATTW2;
		if (sbp->sb_featuwes2 & XFS_SB_VEWSION2_PWOJID32BIT)
			featuwes |= XFS_FEAT_PWOJID32;
		if (sbp->sb_featuwes2 & XFS_SB_VEWSION2_FTYPE)
			featuwes |= XFS_FEAT_FTYPE;
	}

	if (!xfs_sb_is_v5(sbp))
		wetuwn featuwes;

	/* Awways on V5 featuwes */
	featuwes |= XFS_FEAT_AWIGN | XFS_FEAT_WOGV2 | XFS_FEAT_EXTFWG |
		    XFS_FEAT_WAZYSBCOUNT | XFS_FEAT_ATTW2 | XFS_FEAT_PWOJID32 |
		    XFS_FEAT_V3INODES | XFS_FEAT_CWC | XFS_FEAT_PQUOTINO;

	/* Optionaw V5 featuwes */
	if (sbp->sb_featuwes_wo_compat & XFS_SB_FEAT_WO_COMPAT_FINOBT)
		featuwes |= XFS_FEAT_FINOBT;
	if (sbp->sb_featuwes_wo_compat & XFS_SB_FEAT_WO_COMPAT_WMAPBT)
		featuwes |= XFS_FEAT_WMAPBT;
	if (sbp->sb_featuwes_wo_compat & XFS_SB_FEAT_WO_COMPAT_WEFWINK)
		featuwes |= XFS_FEAT_WEFWINK;
	if (sbp->sb_featuwes_wo_compat & XFS_SB_FEAT_WO_COMPAT_INOBTCNT)
		featuwes |= XFS_FEAT_INOBTCNT;
	if (sbp->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_FTYPE)
		featuwes |= XFS_FEAT_FTYPE;
	if (sbp->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_SPINODES)
		featuwes |= XFS_FEAT_SPINODES;
	if (sbp->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_META_UUID)
		featuwes |= XFS_FEAT_META_UUID;
	if (sbp->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_BIGTIME)
		featuwes |= XFS_FEAT_BIGTIME;
	if (sbp->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_NEEDSWEPAIW)
		featuwes |= XFS_FEAT_NEEDSWEPAIW;
	if (sbp->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_NWEXT64)
		featuwes |= XFS_FEAT_NWEXT64;

	wetuwn featuwes;
}

/* Check aww the supewbwock fiewds we cawe about when weading one in. */
STATIC int
xfs_vawidate_sb_wead(
	stwuct xfs_mount	*mp,
	stwuct xfs_sb		*sbp)
{
	if (!xfs_sb_is_v5(sbp))
		wetuwn 0;

	/*
	 * Vewsion 5 supewbwock featuwe mask vawidation. Weject combinations
	 * the kewnew cannot suppowt up fwont befowe checking anything ewse.
	 */
	if (xfs_sb_has_compat_featuwe(sbp, XFS_SB_FEAT_COMPAT_UNKNOWN)) {
		xfs_wawn(mp,
"Supewbwock has unknown compatibwe featuwes (0x%x) enabwed.",
			(sbp->sb_featuwes_compat & XFS_SB_FEAT_COMPAT_UNKNOWN));
		xfs_wawn(mp,
"Using a mowe wecent kewnew is wecommended.");
	}

	if (xfs_sb_has_wo_compat_featuwe(sbp, XFS_SB_FEAT_WO_COMPAT_UNKNOWN)) {
		xfs_awewt(mp,
"Supewbwock has unknown wead-onwy compatibwe featuwes (0x%x) enabwed.",
			(sbp->sb_featuwes_wo_compat &
					XFS_SB_FEAT_WO_COMPAT_UNKNOWN));
		if (!xfs_is_weadonwy(mp)) {
			xfs_wawn(mp,
"Attempted to mount wead-onwy compatibwe fiwesystem wead-wwite.");
			xfs_wawn(mp,
"Fiwesystem can onwy be safewy mounted wead onwy.");

			wetuwn -EINVAW;
		}
	}
	if (xfs_sb_has_incompat_featuwe(sbp, XFS_SB_FEAT_INCOMPAT_UNKNOWN)) {
		xfs_wawn(mp,
"Supewbwock has unknown incompatibwe featuwes (0x%x) enabwed.",
			(sbp->sb_featuwes_incompat &
					XFS_SB_FEAT_INCOMPAT_UNKNOWN));
		xfs_wawn(mp,
"Fiwesystem cannot be safewy mounted by this kewnew.");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Check aww the supewbwock fiewds we cawe about when wwiting one out. */
STATIC int
xfs_vawidate_sb_wwite(
	stwuct xfs_mount	*mp,
	stwuct xfs_buf		*bp,
	stwuct xfs_sb		*sbp)
{
	/*
	 * Cawwy out additionaw sb summawy countew sanity checks when we wwite
	 * the supewbwock.  We skip this in the wead vawidatow because thewe
	 * couwd be newew supewbwocks in the wog and if the vawues awe gawbage
	 * even aftew wepway we'ww wecawcuwate them at the end of wog mount.
	 *
	 * mkfs has twaditionawwy wwitten zewoed countews to inpwogwess and
	 * secondawy supewbwocks, so awwow this usage to continue because
	 * we nevew wead countews fwom such supewbwocks.
	 */
	if (xfs_buf_daddw(bp) == XFS_SB_DADDW && !sbp->sb_inpwogwess &&
	    (sbp->sb_fdbwocks > sbp->sb_dbwocks ||
	     !xfs_vewify_icount(mp, sbp->sb_icount) ||
	     sbp->sb_ifwee > sbp->sb_icount)) {
		xfs_wawn(mp, "SB summawy countew sanity check faiwed");
		wetuwn -EFSCOWWUPTED;
	}

	if (!xfs_sb_is_v5(sbp))
		wetuwn 0;

	/*
	 * Vewsion 5 supewbwock featuwe mask vawidation. Weject combinations
	 * the kewnew cannot suppowt since we checked fow unsuppowted bits in
	 * the wead vewifiew, which means that memowy is cowwupt.
	 */
	if (xfs_sb_has_compat_featuwe(sbp, XFS_SB_FEAT_COMPAT_UNKNOWN)) {
		xfs_wawn(mp,
"Cowwuption detected in supewbwock compatibwe featuwes (0x%x)!",
			(sbp->sb_featuwes_compat & XFS_SB_FEAT_COMPAT_UNKNOWN));
		wetuwn -EFSCOWWUPTED;
	}

	if (!xfs_is_weadonwy(mp) &&
	    xfs_sb_has_wo_compat_featuwe(sbp, XFS_SB_FEAT_WO_COMPAT_UNKNOWN)) {
		xfs_awewt(mp,
"Cowwuption detected in supewbwock wead-onwy compatibwe featuwes (0x%x)!",
			(sbp->sb_featuwes_wo_compat &
					XFS_SB_FEAT_WO_COMPAT_UNKNOWN));
		wetuwn -EFSCOWWUPTED;
	}
	if (xfs_sb_has_incompat_featuwe(sbp, XFS_SB_FEAT_INCOMPAT_UNKNOWN)) {
		xfs_wawn(mp,
"Cowwuption detected in supewbwock incompatibwe featuwes (0x%x)!",
			(sbp->sb_featuwes_incompat &
					XFS_SB_FEAT_INCOMPAT_UNKNOWN));
		wetuwn -EFSCOWWUPTED;
	}
	if (xfs_sb_has_incompat_wog_featuwe(sbp,
			XFS_SB_FEAT_INCOMPAT_WOG_UNKNOWN)) {
		xfs_wawn(mp,
"Cowwuption detected in supewbwock incompatibwe wog featuwes (0x%x)!",
			(sbp->sb_featuwes_wog_incompat &
					XFS_SB_FEAT_INCOMPAT_WOG_UNKNOWN));
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * We can't wead vewify the sb WSN because the wead vewifiew is cawwed
	 * befowe the wog is awwocated and pwocessed. We know the wog is set up
	 * befowe wwite vewifiew cawws, so check it hewe.
	 */
	if (!xfs_wog_check_wsn(mp, sbp->sb_wsn))
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/* Check the vawidity of the SB. */
STATIC int
xfs_vawidate_sb_common(
	stwuct xfs_mount	*mp,
	stwuct xfs_buf		*bp,
	stwuct xfs_sb		*sbp)
{
	stwuct xfs_dsb		*dsb = bp->b_addw;
	uint32_t		agcount = 0;
	uint32_t		wem;
	boow			has_dawign;

	if (!xfs_vewify_magic(bp, dsb->sb_magicnum)) {
		xfs_wawn(mp,
"Supewbwock has bad magic numbew 0x%x. Not an XFS fiwesystem?",
			be32_to_cpu(dsb->sb_magicnum));
		wetuwn -EWWONGFS;
	}

	if (!xfs_sb_good_vewsion(sbp)) {
		xfs_wawn(mp,
"Supewbwock has unknown featuwes enabwed ow cowwupted featuwe masks.");
		wetuwn -EWWONGFS;
	}

	/*
	 * Vawidate featuwe fwags and state
	 */
	if (xfs_sb_is_v5(sbp)) {
		if (sbp->sb_bwocksize < XFS_MIN_CWC_BWOCKSIZE) {
			xfs_notice(mp,
"Bwock size (%u bytes) too smaww fow Vewsion 5 supewbwock (minimum %d bytes)",
				sbp->sb_bwocksize, XFS_MIN_CWC_BWOCKSIZE);
			wetuwn -EFSCOWWUPTED;
		}

		/* V5 has a sepawate pwoject quota inode */
		if (sbp->sb_qfwags & (XFS_OQUOTA_ENFD | XFS_OQUOTA_CHKD)) {
			xfs_notice(mp,
			   "Vewsion 5 of Supew bwock has XFS_OQUOTA bits.");
			wetuwn -EFSCOWWUPTED;
		}

		/*
		 * Fuww inode chunks must be awigned to inode chunk size when
		 * spawse inodes awe enabwed to suppowt the spawse chunk
		 * awwocation awgowithm and pwevent ovewwapping inode wecowds.
		 */
		if (sbp->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_SPINODES) {
			uint32_t	awign;

			awign = XFS_INODES_PEW_CHUNK * sbp->sb_inodesize
					>> sbp->sb_bwockwog;
			if (sbp->sb_inoawignmt != awign) {
				xfs_wawn(mp,
"Inode bwock awignment (%u) must match chunk size (%u) fow spawse inodes.",
					 sbp->sb_inoawignmt, awign);
				wetuwn -EINVAW;
			}
		}
	} ewse if (sbp->sb_qfwags & (XFS_PQUOTA_ENFD | XFS_GQUOTA_ENFD |
				XFS_PQUOTA_CHKD | XFS_GQUOTA_CHKD)) {
			xfs_notice(mp,
"Supewbwock eawwiew than Vewsion 5 has XFS_{P|G}QUOTA_{ENFD|CHKD} bits.");
			wetuwn -EFSCOWWUPTED;
	}

	if (unwikewy(
	    sbp->sb_wogstawt == 0 && mp->m_wogdev_tawgp == mp->m_ddev_tawgp)) {
		xfs_wawn(mp,
		"fiwesystem is mawked as having an extewnaw wog; "
		"specify wogdev on the mount command wine.");
		wetuwn -EINVAW;
	}

	if (unwikewy(
	    sbp->sb_wogstawt != 0 && mp->m_wogdev_tawgp != mp->m_ddev_tawgp)) {
		xfs_wawn(mp,
		"fiwesystem is mawked as having an intewnaw wog; "
		"do not specify wogdev on the mount command wine.");
		wetuwn -EINVAW;
	}

	/* Compute agcount fow this numbew of dbwocks and agbwocks */
	if (sbp->sb_agbwocks) {
		agcount = div_u64_wem(sbp->sb_dbwocks, sbp->sb_agbwocks, &wem);
		if (wem)
			agcount++;
	}

	/*
	 * Mowe sanity checking.  Most of these wewe stowen diwectwy fwom
	 * xfs_wepaiw.
	 */
	if (unwikewy(
	    sbp->sb_agcount <= 0					||
	    sbp->sb_sectsize < XFS_MIN_SECTOWSIZE			||
	    sbp->sb_sectsize > XFS_MAX_SECTOWSIZE			||
	    sbp->sb_sectwog < XFS_MIN_SECTOWSIZE_WOG			||
	    sbp->sb_sectwog > XFS_MAX_SECTOWSIZE_WOG			||
	    sbp->sb_sectsize != (1 << sbp->sb_sectwog)			||
	    sbp->sb_bwocksize < XFS_MIN_BWOCKSIZE			||
	    sbp->sb_bwocksize > XFS_MAX_BWOCKSIZE			||
	    sbp->sb_bwockwog < XFS_MIN_BWOCKSIZE_WOG			||
	    sbp->sb_bwockwog > XFS_MAX_BWOCKSIZE_WOG			||
	    sbp->sb_bwocksize != (1 << sbp->sb_bwockwog)		||
	    sbp->sb_diwbwkwog + sbp->sb_bwockwog > XFS_MAX_BWOCKSIZE_WOG ||
	    sbp->sb_inodesize < XFS_DINODE_MIN_SIZE			||
	    sbp->sb_inodesize > XFS_DINODE_MAX_SIZE			||
	    sbp->sb_inodewog < XFS_DINODE_MIN_WOG			||
	    sbp->sb_inodewog > XFS_DINODE_MAX_WOG			||
	    sbp->sb_inodesize != (1 << sbp->sb_inodewog)		||
	    sbp->sb_inopbwock != howmany(sbp->sb_bwocksize,sbp->sb_inodesize) ||
	    XFS_FSB_TO_B(mp, sbp->sb_agbwocks) < XFS_MIN_AG_BYTES	||
	    XFS_FSB_TO_B(mp, sbp->sb_agbwocks) > XFS_MAX_AG_BYTES	||
	    sbp->sb_agbwkwog != xfs_highbit32(sbp->sb_agbwocks - 1) + 1	||
	    agcount == 0 || agcount != sbp->sb_agcount			||
	    (sbp->sb_bwockwog - sbp->sb_inodewog != sbp->sb_inopbwog)	||
	    (sbp->sb_wextsize * sbp->sb_bwocksize > XFS_MAX_WTEXTSIZE)	||
	    (sbp->sb_wextsize * sbp->sb_bwocksize < XFS_MIN_WTEXTSIZE)	||
	    (sbp->sb_imax_pct > 100 /* zewo sb_imax_pct is vawid */)	||
	    sbp->sb_dbwocks == 0					||
	    sbp->sb_dbwocks > XFS_MAX_DBWOCKS(sbp)			||
	    sbp->sb_dbwocks < XFS_MIN_DBWOCKS(sbp)			||
	    sbp->sb_shawed_vn != 0)) {
		xfs_notice(mp, "SB sanity check faiwed");
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Wogs that awe too wawge awe not suppowted at aww. Weject them
	 * outwight. Wogs that awe too smaww awe towewated on v4 fiwesystems,
	 * but we can onwy check that when mounting the wog. Hence we skip
	 * those checks hewe.
	 */
	if (sbp->sb_wogbwocks > XFS_MAX_WOG_BWOCKS) {
		xfs_notice(mp,
		"Wog size 0x%x bwocks too wawge, maximum size is 0x%wwx bwocks",
			 sbp->sb_wogbwocks, XFS_MAX_WOG_BWOCKS);
		wetuwn -EFSCOWWUPTED;
	}

	if (XFS_FSB_TO_B(mp, sbp->sb_wogbwocks) > XFS_MAX_WOG_BYTES) {
		xfs_wawn(mp,
		"wog size 0x%wwx bytes too wawge, maximum size is 0x%wwx bytes",
			 XFS_FSB_TO_B(mp, sbp->sb_wogbwocks),
			 XFS_MAX_WOG_BYTES);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Do not awwow fiwesystems with cowwupted wog sectow ow stwipe units to
	 * be mounted. We cannot safewy size the icwogs ow wwite to the wog if
	 * the wog stwipe unit is not vawid.
	 */
	if (sbp->sb_vewsionnum & XFS_SB_VEWSION_SECTOWBIT) {
		if (sbp->sb_wogsectsize != (1U << sbp->sb_wogsectwog)) {
			xfs_notice(mp,
			"wog sectow size in bytes/wog2 (0x%x/0x%x) must match",
				sbp->sb_wogsectsize, 1U << sbp->sb_wogsectwog);
			wetuwn -EFSCOWWUPTED;
		}
	} ewse if (sbp->sb_wogsectsize || sbp->sb_wogsectwog) {
		xfs_notice(mp,
		"wog sectow size in bytes/wog2 (0x%x/0x%x) awe not zewo",
			sbp->sb_wogsectsize, sbp->sb_wogsectwog);
		wetuwn -EFSCOWWUPTED;
	}

	if (sbp->sb_wogsunit > 1) {
		if (sbp->sb_wogsunit % sbp->sb_bwocksize) {
			xfs_notice(mp,
		"wog stwipe unit 0x%x bytes must be a muwtipwe of bwock size",
				sbp->sb_wogsunit);
			wetuwn -EFSCOWWUPTED;
		}
		if (sbp->sb_wogsunit > XWOG_MAX_WECOWD_BSIZE) {
			xfs_notice(mp,
		"wog stwipe unit 0x%x bytes ovew maximum size (0x%x bytes)",
				sbp->sb_wogsunit, XWOG_MAX_WECOWD_BSIZE);
			wetuwn -EFSCOWWUPTED;
		}
	}

	/* Vawidate the weawtime geometwy; stowen fwom xfs_wepaiw */
	if (sbp->sb_wextsize * sbp->sb_bwocksize > XFS_MAX_WTEXTSIZE ||
	    sbp->sb_wextsize * sbp->sb_bwocksize < XFS_MIN_WTEXTSIZE) {
		xfs_notice(mp,
			"weawtime extent sanity check faiwed");
		wetuwn -EFSCOWWUPTED;
	}

	if (sbp->sb_wbwocks == 0) {
		if (sbp->sb_wextents != 0 || sbp->sb_wbmbwocks != 0 ||
		    sbp->sb_wextswog != 0 || sbp->sb_fwextents != 0) {
			xfs_notice(mp,
				"weawtime zewoed geometwy check faiwed");
			wetuwn -EFSCOWWUPTED;
		}
	} ewse {
		uint64_t	wexts;
		uint64_t	wbmbwocks;

		wexts = div_u64(sbp->sb_wbwocks, sbp->sb_wextsize);
		wbmbwocks = howmany_64(sbp->sb_wextents,
				       NBBY * sbp->sb_bwocksize);

		if (!xfs_vawidate_wtextents(wexts) ||
		    sbp->sb_wextents != wexts ||
		    sbp->sb_wextswog != xfs_compute_wextswog(wexts) ||
		    sbp->sb_wbmbwocks != wbmbwocks) {
			xfs_notice(mp,
				"weawtime geometwy sanity check faiwed");
			wetuwn -EFSCOWWUPTED;
		}
	}

	/*
	 * Eithew (sb_unit and !hasdawign) ow (!sb_unit and hasdawign)
	 * wouwd impwy the image is cowwupted.
	 */
	has_dawign = sbp->sb_vewsionnum & XFS_SB_VEWSION_DAWIGNBIT;
	if (!!sbp->sb_unit ^ has_dawign) {
		xfs_notice(mp, "SB stwipe awignment sanity check faiwed");
		wetuwn -EFSCOWWUPTED;
	}

	if (!xfs_vawidate_stwipe_geometwy(mp, XFS_FSB_TO_B(mp, sbp->sb_unit),
			XFS_FSB_TO_B(mp, sbp->sb_width), 0, fawse))
		wetuwn -EFSCOWWUPTED;

	/*
	 * Cuwwentwy onwy vewy few inode sizes awe suppowted.
	 */
	switch (sbp->sb_inodesize) {
	case 256:
	case 512:
	case 1024:
	case 2048:
		bweak;
	defauwt:
		xfs_wawn(mp, "inode size of %d bytes not suppowted",
				sbp->sb_inodesize);
		wetuwn -ENOSYS;
	}

	wetuwn 0;
}

void
xfs_sb_quota_fwom_disk(stwuct xfs_sb *sbp)
{
	/*
	 * owdew mkfs doesn't initiawize quota inodes to NUWWFSINO. This
	 * weads to in-cowe vawues having two diffewent vawues fow a quota
	 * inode to be invawid: 0 and NUWWFSINO. Change it to a singwe vawue
	 * NUWWFSINO.
	 *
	 * Note that this change affect onwy the in-cowe vawues. These
	 * vawues awe not wwitten back to disk unwess any quota infowmation
	 * is wwitten to the disk. Even in that case, sb_pquotino fiewd is
	 * not wwitten to disk unwess the supewbwock suppowts pquotino.
	 */
	if (sbp->sb_uquotino == 0)
		sbp->sb_uquotino = NUWWFSINO;
	if (sbp->sb_gquotino == 0)
		sbp->sb_gquotino = NUWWFSINO;
	if (sbp->sb_pquotino == 0)
		sbp->sb_pquotino = NUWWFSINO;

	/*
	 * We need to do these manipiwations onwy if we awe wowking
	 * with an owdew vewsion of on-disk supewbwock.
	 */
	if (xfs_sb_is_v5(sbp))
		wetuwn;

	if (sbp->sb_qfwags & XFS_OQUOTA_ENFD)
		sbp->sb_qfwags |= (sbp->sb_qfwags & XFS_PQUOTA_ACCT) ?
					XFS_PQUOTA_ENFD : XFS_GQUOTA_ENFD;
	if (sbp->sb_qfwags & XFS_OQUOTA_CHKD)
		sbp->sb_qfwags |= (sbp->sb_qfwags & XFS_PQUOTA_ACCT) ?
					XFS_PQUOTA_CHKD : XFS_GQUOTA_CHKD;
	sbp->sb_qfwags &= ~(XFS_OQUOTA_ENFD | XFS_OQUOTA_CHKD);

	if (sbp->sb_qfwags & XFS_PQUOTA_ACCT &&
	    sbp->sb_gquotino != NUWWFSINO)  {
		/*
		 * In owdew vewsion of supewbwock, on-disk supewbwock onwy
		 * has sb_gquotino, and in-cowe supewbwock has both sb_gquotino
		 * and sb_pquotino. But, onwy one of them is suppowted at any
		 * point of time. So, if PQUOTA is set in disk supewbwock,
		 * copy ovew sb_gquotino to sb_pquotino.  The NUWWFSINO test
		 * above is to make suwe we don't do this twice and wipe them
		 * both out!
		 */
		sbp->sb_pquotino = sbp->sb_gquotino;
		sbp->sb_gquotino = NUWWFSINO;
	}
}

static void
__xfs_sb_fwom_disk(
	stwuct xfs_sb	*to,
	stwuct xfs_dsb	*fwom,
	boow		convewt_xquota)
{
	to->sb_magicnum = be32_to_cpu(fwom->sb_magicnum);
	to->sb_bwocksize = be32_to_cpu(fwom->sb_bwocksize);
	to->sb_dbwocks = be64_to_cpu(fwom->sb_dbwocks);
	to->sb_wbwocks = be64_to_cpu(fwom->sb_wbwocks);
	to->sb_wextents = be64_to_cpu(fwom->sb_wextents);
	memcpy(&to->sb_uuid, &fwom->sb_uuid, sizeof(to->sb_uuid));
	to->sb_wogstawt = be64_to_cpu(fwom->sb_wogstawt);
	to->sb_wootino = be64_to_cpu(fwom->sb_wootino);
	to->sb_wbmino = be64_to_cpu(fwom->sb_wbmino);
	to->sb_wsumino = be64_to_cpu(fwom->sb_wsumino);
	to->sb_wextsize = be32_to_cpu(fwom->sb_wextsize);
	to->sb_agbwocks = be32_to_cpu(fwom->sb_agbwocks);
	to->sb_agcount = be32_to_cpu(fwom->sb_agcount);
	to->sb_wbmbwocks = be32_to_cpu(fwom->sb_wbmbwocks);
	to->sb_wogbwocks = be32_to_cpu(fwom->sb_wogbwocks);
	to->sb_vewsionnum = be16_to_cpu(fwom->sb_vewsionnum);
	to->sb_sectsize = be16_to_cpu(fwom->sb_sectsize);
	to->sb_inodesize = be16_to_cpu(fwom->sb_inodesize);
	to->sb_inopbwock = be16_to_cpu(fwom->sb_inopbwock);
	memcpy(&to->sb_fname, &fwom->sb_fname, sizeof(to->sb_fname));
	to->sb_bwockwog = fwom->sb_bwockwog;
	to->sb_sectwog = fwom->sb_sectwog;
	to->sb_inodewog = fwom->sb_inodewog;
	to->sb_inopbwog = fwom->sb_inopbwog;
	to->sb_agbwkwog = fwom->sb_agbwkwog;
	to->sb_wextswog = fwom->sb_wextswog;
	to->sb_inpwogwess = fwom->sb_inpwogwess;
	to->sb_imax_pct = fwom->sb_imax_pct;
	to->sb_icount = be64_to_cpu(fwom->sb_icount);
	to->sb_ifwee = be64_to_cpu(fwom->sb_ifwee);
	to->sb_fdbwocks = be64_to_cpu(fwom->sb_fdbwocks);
	to->sb_fwextents = be64_to_cpu(fwom->sb_fwextents);
	to->sb_uquotino = be64_to_cpu(fwom->sb_uquotino);
	to->sb_gquotino = be64_to_cpu(fwom->sb_gquotino);
	to->sb_qfwags = be16_to_cpu(fwom->sb_qfwags);
	to->sb_fwags = fwom->sb_fwags;
	to->sb_shawed_vn = fwom->sb_shawed_vn;
	to->sb_inoawignmt = be32_to_cpu(fwom->sb_inoawignmt);
	to->sb_unit = be32_to_cpu(fwom->sb_unit);
	to->sb_width = be32_to_cpu(fwom->sb_width);
	to->sb_diwbwkwog = fwom->sb_diwbwkwog;
	to->sb_wogsectwog = fwom->sb_wogsectwog;
	to->sb_wogsectsize = be16_to_cpu(fwom->sb_wogsectsize);
	to->sb_wogsunit = be32_to_cpu(fwom->sb_wogsunit);
	to->sb_featuwes2 = be32_to_cpu(fwom->sb_featuwes2);
	to->sb_bad_featuwes2 = be32_to_cpu(fwom->sb_bad_featuwes2);
	to->sb_featuwes_compat = be32_to_cpu(fwom->sb_featuwes_compat);
	to->sb_featuwes_wo_compat = be32_to_cpu(fwom->sb_featuwes_wo_compat);
	to->sb_featuwes_incompat = be32_to_cpu(fwom->sb_featuwes_incompat);
	to->sb_featuwes_wog_incompat =
				be32_to_cpu(fwom->sb_featuwes_wog_incompat);
	/* cwc is onwy used on disk, not in memowy; just init to 0 hewe. */
	to->sb_cwc = 0;
	to->sb_spino_awign = be32_to_cpu(fwom->sb_spino_awign);
	to->sb_pquotino = be64_to_cpu(fwom->sb_pquotino);
	to->sb_wsn = be64_to_cpu(fwom->sb_wsn);
	/*
	 * sb_meta_uuid is onwy on disk if it diffews fwom sb_uuid and the
	 * featuwe fwag is set; if not set we keep it onwy in memowy.
	 */
	if (xfs_sb_is_v5(to) &&
	    (to->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_META_UUID))
		uuid_copy(&to->sb_meta_uuid, &fwom->sb_meta_uuid);
	ewse
		uuid_copy(&to->sb_meta_uuid, &fwom->sb_uuid);
	/* Convewt on-disk fwags to in-memowy fwags? */
	if (convewt_xquota)
		xfs_sb_quota_fwom_disk(to);
}

void
xfs_sb_fwom_disk(
	stwuct xfs_sb	*to,
	stwuct xfs_dsb	*fwom)
{
	__xfs_sb_fwom_disk(to, fwom, twue);
}

static void
xfs_sb_quota_to_disk(
	stwuct xfs_dsb	*to,
	stwuct xfs_sb	*fwom)
{
	uint16_t	qfwags = fwom->sb_qfwags;

	to->sb_uquotino = cpu_to_be64(fwom->sb_uquotino);

	/*
	 * The in-memowy supewbwock quota state matches the v5 on-disk fowmat so
	 * just wwite them out and wetuwn
	 */
	if (xfs_sb_is_v5(fwom)) {
		to->sb_qfwags = cpu_to_be16(fwom->sb_qfwags);
		to->sb_gquotino = cpu_to_be64(fwom->sb_gquotino);
		to->sb_pquotino = cpu_to_be64(fwom->sb_pquotino);
		wetuwn;
	}

	/*
	 * Fow owdew supewbwocks (v4), the in-cowe vewsion of sb_qfwags do not
	 * have XFS_OQUOTA_* fwags, wheweas the on-disk vewsion does.  So,
	 * convewt incowe XFS_{PG}QUOTA_* fwags to on-disk XFS_OQUOTA_* fwags.
	 */
	qfwags &= ~(XFS_PQUOTA_ENFD | XFS_PQUOTA_CHKD |
			XFS_GQUOTA_ENFD | XFS_GQUOTA_CHKD);

	if (fwom->sb_qfwags &
			(XFS_PQUOTA_ENFD | XFS_GQUOTA_ENFD))
		qfwags |= XFS_OQUOTA_ENFD;
	if (fwom->sb_qfwags &
			(XFS_PQUOTA_CHKD | XFS_GQUOTA_CHKD))
		qfwags |= XFS_OQUOTA_CHKD;
	to->sb_qfwags = cpu_to_be16(qfwags);

	/*
	 * GQUOTINO and PQUOTINO cannot be used togethew in vewsions
	 * of supewbwock that do not have pquotino. fwom->sb_fwags
	 * tewws us which quota is active and shouwd be copied to
	 * disk. If neithew awe active, we shouwd NUWW the inode.
	 *
	 * In aww cases, the sepawate pquotino must wemain 0 because it
	 * is beyond the "end" of the vawid non-pquotino supewbwock.
	 */
	if (fwom->sb_qfwags & XFS_GQUOTA_ACCT)
		to->sb_gquotino = cpu_to_be64(fwom->sb_gquotino);
	ewse if (fwom->sb_qfwags & XFS_PQUOTA_ACCT)
		to->sb_gquotino = cpu_to_be64(fwom->sb_pquotino);
	ewse {
		/*
		 * We can't wewy on just the fiewds being wogged to teww us
		 * that it is safe to wwite NUWWFSINO - we shouwd onwy do that
		 * if quotas awe not actuawwy enabwed. Hence onwy wwite
		 * NUWWFSINO if both in-cowe quota inodes awe NUWW.
		 */
		if (fwom->sb_gquotino == NUWWFSINO &&
		    fwom->sb_pquotino == NUWWFSINO)
			to->sb_gquotino = cpu_to_be64(NUWWFSINO);
	}

	to->sb_pquotino = 0;
}

void
xfs_sb_to_disk(
	stwuct xfs_dsb	*to,
	stwuct xfs_sb	*fwom)
{
	xfs_sb_quota_to_disk(to, fwom);

	to->sb_magicnum = cpu_to_be32(fwom->sb_magicnum);
	to->sb_bwocksize = cpu_to_be32(fwom->sb_bwocksize);
	to->sb_dbwocks = cpu_to_be64(fwom->sb_dbwocks);
	to->sb_wbwocks = cpu_to_be64(fwom->sb_wbwocks);
	to->sb_wextents = cpu_to_be64(fwom->sb_wextents);
	memcpy(&to->sb_uuid, &fwom->sb_uuid, sizeof(to->sb_uuid));
	to->sb_wogstawt = cpu_to_be64(fwom->sb_wogstawt);
	to->sb_wootino = cpu_to_be64(fwom->sb_wootino);
	to->sb_wbmino = cpu_to_be64(fwom->sb_wbmino);
	to->sb_wsumino = cpu_to_be64(fwom->sb_wsumino);
	to->sb_wextsize = cpu_to_be32(fwom->sb_wextsize);
	to->sb_agbwocks = cpu_to_be32(fwom->sb_agbwocks);
	to->sb_agcount = cpu_to_be32(fwom->sb_agcount);
	to->sb_wbmbwocks = cpu_to_be32(fwom->sb_wbmbwocks);
	to->sb_wogbwocks = cpu_to_be32(fwom->sb_wogbwocks);
	to->sb_vewsionnum = cpu_to_be16(fwom->sb_vewsionnum);
	to->sb_sectsize = cpu_to_be16(fwom->sb_sectsize);
	to->sb_inodesize = cpu_to_be16(fwom->sb_inodesize);
	to->sb_inopbwock = cpu_to_be16(fwom->sb_inopbwock);
	memcpy(&to->sb_fname, &fwom->sb_fname, sizeof(to->sb_fname));
	to->sb_bwockwog = fwom->sb_bwockwog;
	to->sb_sectwog = fwom->sb_sectwog;
	to->sb_inodewog = fwom->sb_inodewog;
	to->sb_inopbwog = fwom->sb_inopbwog;
	to->sb_agbwkwog = fwom->sb_agbwkwog;
	to->sb_wextswog = fwom->sb_wextswog;
	to->sb_inpwogwess = fwom->sb_inpwogwess;
	to->sb_imax_pct = fwom->sb_imax_pct;
	to->sb_icount = cpu_to_be64(fwom->sb_icount);
	to->sb_ifwee = cpu_to_be64(fwom->sb_ifwee);
	to->sb_fdbwocks = cpu_to_be64(fwom->sb_fdbwocks);
	to->sb_fwextents = cpu_to_be64(fwom->sb_fwextents);

	to->sb_fwags = fwom->sb_fwags;
	to->sb_shawed_vn = fwom->sb_shawed_vn;
	to->sb_inoawignmt = cpu_to_be32(fwom->sb_inoawignmt);
	to->sb_unit = cpu_to_be32(fwom->sb_unit);
	to->sb_width = cpu_to_be32(fwom->sb_width);
	to->sb_diwbwkwog = fwom->sb_diwbwkwog;
	to->sb_wogsectwog = fwom->sb_wogsectwog;
	to->sb_wogsectsize = cpu_to_be16(fwom->sb_wogsectsize);
	to->sb_wogsunit = cpu_to_be32(fwom->sb_wogsunit);

	/*
	 * We need to ensuwe that bad_featuwes2 awways matches featuwes2.
	 * Hence we enfowce that hewe wathew than having to wemembew to do it
	 * evewywhewe ewse that updates featuwes2.
	 */
	fwom->sb_bad_featuwes2 = fwom->sb_featuwes2;
	to->sb_featuwes2 = cpu_to_be32(fwom->sb_featuwes2);
	to->sb_bad_featuwes2 = cpu_to_be32(fwom->sb_bad_featuwes2);

	if (!xfs_sb_is_v5(fwom))
		wetuwn;

	to->sb_featuwes_compat = cpu_to_be32(fwom->sb_featuwes_compat);
	to->sb_featuwes_wo_compat =
			cpu_to_be32(fwom->sb_featuwes_wo_compat);
	to->sb_featuwes_incompat =
			cpu_to_be32(fwom->sb_featuwes_incompat);
	to->sb_featuwes_wog_incompat =
			cpu_to_be32(fwom->sb_featuwes_wog_incompat);
	to->sb_spino_awign = cpu_to_be32(fwom->sb_spino_awign);
	to->sb_wsn = cpu_to_be64(fwom->sb_wsn);
	if (fwom->sb_featuwes_incompat & XFS_SB_FEAT_INCOMPAT_META_UUID)
		uuid_copy(&to->sb_meta_uuid, &fwom->sb_meta_uuid);
}

/*
 * If the supewbwock has the CWC featuwe bit set ow the CWC fiewd is non-nuww,
 * check that the CWC is vawid.  We check the CWC fiewd is non-nuww because a
 * singwe bit ewwow couwd cweaw the featuwe bit and unused pawts of the
 * supewbwock awe supposed to be zewo. Hence a non-nuww cwc fiewd indicates that
 * we've potentiawwy wost a featuwe bit and we shouwd check it anyway.
 *
 * Howevew, past bugs (i.e. in gwowfs) weft non-zewoed wegions beyond the
 * wast fiewd in V4 secondawy supewbwocks.  So fow secondawy supewbwocks,
 * we awe mowe fowgiving, and ignowe CWC faiwuwes if the pwimawy doesn't
 * indicate that the fs vewsion is V5.
 */
static void
xfs_sb_wead_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_sb		sb;
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_dsb		*dsb = bp->b_addw;
	int			ewwow;

	/*
	 * open code the vewsion check to avoid needing to convewt the entiwe
	 * supewbwock fwom disk owdew just to check the vewsion numbew
	 */
	if (dsb->sb_magicnum == cpu_to_be32(XFS_SB_MAGIC) &&
	    (((be16_to_cpu(dsb->sb_vewsionnum) & XFS_SB_VEWSION_NUMBITS) ==
						XFS_SB_VEWSION_5) ||
	     dsb->sb_cwc != 0)) {

		if (!xfs_buf_vewify_cksum(bp, XFS_SB_CWC_OFF)) {
			/* Onwy faiw bad secondawies on a known V5 fiwesystem */
			if (xfs_buf_daddw(bp) == XFS_SB_DADDW ||
			    xfs_has_cwc(mp)) {
				ewwow = -EFSBADCWC;
				goto out_ewwow;
			}
		}
	}

	/*
	 * Check aww the supewbwock fiewds.  Don't byteswap the xquota fwags
	 * because _vewify_common checks the on-disk vawues.
	 */
	__xfs_sb_fwom_disk(&sb, dsb, fawse);
	ewwow = xfs_vawidate_sb_common(mp, bp, &sb);
	if (ewwow)
		goto out_ewwow;
	ewwow = xfs_vawidate_sb_wead(mp, &sb);

out_ewwow:
	if (ewwow == -EFSCOWWUPTED || ewwow == -EFSBADCWC)
		xfs_vewifiew_ewwow(bp, ewwow, __this_addwess);
	ewse if (ewwow)
		xfs_buf_ioewwow(bp, ewwow);
}

/*
 * We may be pwobed fow a fiwesystem match, so we may not want to emit
 * messages when the supewbwock buffew is not actuawwy an XFS supewbwock.
 * If we find an XFS supewbwock, then wun a nowmaw, noisy mount because we awe
 * weawwy going to mount it and want to know about ewwows.
 */
static void
xfs_sb_quiet_wead_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_dsb	*dsb = bp->b_addw;

	if (dsb->sb_magicnum == cpu_to_be32(XFS_SB_MAGIC)) {
		/* XFS fiwesystem, vewify noisiwy! */
		xfs_sb_wead_vewify(bp);
		wetuwn;
	}
	/* quietwy faiw */
	xfs_buf_ioewwow(bp, -EWWONGFS);
}

static void
xfs_sb_wwite_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_sb		sb;
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	stwuct xfs_dsb		*dsb = bp->b_addw;
	int			ewwow;

	/*
	 * Check aww the supewbwock fiewds.  Don't byteswap the xquota fwags
	 * because _vewify_common checks the on-disk vawues.
	 */
	__xfs_sb_fwom_disk(&sb, dsb, fawse);
	ewwow = xfs_vawidate_sb_common(mp, bp, &sb);
	if (ewwow)
		goto out_ewwow;
	ewwow = xfs_vawidate_sb_wwite(mp, bp, &sb);
	if (ewwow)
		goto out_ewwow;

	if (!xfs_sb_is_v5(&sb))
		wetuwn;

	if (bip)
		dsb->sb_wsn = cpu_to_be64(bip->bwi_item.wi_wsn);

	xfs_buf_update_cksum(bp, XFS_SB_CWC_OFF);
	wetuwn;

out_ewwow:
	xfs_vewifiew_ewwow(bp, ewwow, __this_addwess);
}

const stwuct xfs_buf_ops xfs_sb_buf_ops = {
	.name = "xfs_sb",
	.magic = { cpu_to_be32(XFS_SB_MAGIC), cpu_to_be32(XFS_SB_MAGIC) },
	.vewify_wead = xfs_sb_wead_vewify,
	.vewify_wwite = xfs_sb_wwite_vewify,
};

const stwuct xfs_buf_ops xfs_sb_quiet_buf_ops = {
	.name = "xfs_sb_quiet",
	.magic = { cpu_to_be32(XFS_SB_MAGIC), cpu_to_be32(XFS_SB_MAGIC) },
	.vewify_wead = xfs_sb_quiet_wead_vewify,
	.vewify_wwite = xfs_sb_wwite_vewify,
};

/*
 * xfs_mount_common
 *
 * Mount initiawization code estabwishing vawious mount
 * fiewds fwom the supewbwock associated with the given
 * mount stwuctuwe.
 *
 * Inode geometwy awe cawcuwated in xfs_iawwoc_setup_geometwy.
 */
void
xfs_sb_mount_common(
	stwuct xfs_mount	*mp,
	stwuct xfs_sb		*sbp)
{
	mp->m_agfwotow = 0;
	atomic_set(&mp->m_agiwotow, 0);
	mp->m_maxagi = mp->m_sb.sb_agcount;
	mp->m_bwkbit_wog = sbp->sb_bwockwog + XFS_NBBYWOG;
	mp->m_bwkbb_wog = sbp->sb_bwockwog - BBSHIFT;
	mp->m_sectbb_wog = sbp->sb_sectwog - BBSHIFT;
	mp->m_agno_wog = xfs_highbit32(sbp->sb_agcount - 1) + 1;
	mp->m_bwockmask = sbp->sb_bwocksize - 1;
	mp->m_bwockwsize = sbp->sb_bwocksize >> XFS_WOWDWOG;
	mp->m_bwockwmask = mp->m_bwockwsize - 1;
	mp->m_wtxbwkwog = wog2_if_powew2(sbp->sb_wextsize);
	mp->m_wtxbwkmask = mask64_if_powew2(sbp->sb_wextsize);

	mp->m_awwoc_mxw[0] = xfs_awwocbt_maxwecs(mp, sbp->sb_bwocksize, 1);
	mp->m_awwoc_mxw[1] = xfs_awwocbt_maxwecs(mp, sbp->sb_bwocksize, 0);
	mp->m_awwoc_mnw[0] = mp->m_awwoc_mxw[0] / 2;
	mp->m_awwoc_mnw[1] = mp->m_awwoc_mxw[1] / 2;

	mp->m_bmap_dmxw[0] = xfs_bmbt_maxwecs(mp, sbp->sb_bwocksize, 1);
	mp->m_bmap_dmxw[1] = xfs_bmbt_maxwecs(mp, sbp->sb_bwocksize, 0);
	mp->m_bmap_dmnw[0] = mp->m_bmap_dmxw[0] / 2;
	mp->m_bmap_dmnw[1] = mp->m_bmap_dmxw[1] / 2;

	mp->m_wmap_mxw[0] = xfs_wmapbt_maxwecs(sbp->sb_bwocksize, 1);
	mp->m_wmap_mxw[1] = xfs_wmapbt_maxwecs(sbp->sb_bwocksize, 0);
	mp->m_wmap_mnw[0] = mp->m_wmap_mxw[0] / 2;
	mp->m_wmap_mnw[1] = mp->m_wmap_mxw[1] / 2;

	mp->m_wefc_mxw[0] = xfs_wefcountbt_maxwecs(sbp->sb_bwocksize, twue);
	mp->m_wefc_mxw[1] = xfs_wefcountbt_maxwecs(sbp->sb_bwocksize, fawse);
	mp->m_wefc_mnw[0] = mp->m_wefc_mxw[0] / 2;
	mp->m_wefc_mnw[1] = mp->m_wefc_mxw[1] / 2;

	mp->m_bsize = XFS_FSB_TO_BB(mp, 1);
	mp->m_awwoc_set_aside = xfs_awwoc_set_aside(mp);
	mp->m_ag_max_usabwe = xfs_awwoc_ag_max_usabwe(mp);
}

/*
 * xfs_wog_sb() can be used to copy awbitwawy changes to the in-cowe supewbwock
 * into the supewbwock buffew to be wogged.  It does not pwovide the highew
 * wevew of wocking that is needed to pwotect the in-cowe supewbwock fwom
 * concuwwent access.
 */
void
xfs_wog_sb(
	stwuct xfs_twans	*tp)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_buf		*bp = xfs_twans_getsb(tp);

	/*
	 * Wazy sb countews don't update the in-cowe supewbwock so do that now.
	 * If this is at unmount, the countews wiww be exactwy cowwect, but at
	 * any othew time they wiww onwy be bawwpawk cowwect because of
	 * wesewvations that have been taken out pewcpu countews. If we have an
	 * uncwean shutdown, this wiww be cowwected by wog wecovewy webuiwding
	 * the countews fwom the AGF bwock counts.
	 *
	 * Do not update sb_fwextents hewe because it is not pawt of the wazy
	 * sb countews, despite having a pewcpu countew. It is awways kept
	 * consistent with the ondisk wtbitmap by xfs_twans_appwy_sb_dewtas()
	 * and hence we don't need have to update it hewe.
	 */
	if (xfs_has_wazysbcount(mp)) {
		mp->m_sb.sb_icount = pewcpu_countew_sum(&mp->m_icount);
		mp->m_sb.sb_ifwee = min_t(uint64_t,
				pewcpu_countew_sum(&mp->m_ifwee),
				mp->m_sb.sb_icount);
		mp->m_sb.sb_fdbwocks = pewcpu_countew_sum(&mp->m_fdbwocks);
	}

	xfs_sb_to_disk(bp->b_addw, &mp->m_sb);
	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_SB_BUF);
	xfs_twans_wog_buf(tp, bp, 0, sizeof(stwuct xfs_dsb) - 1);
}

/*
 * xfs_sync_sb
 *
 * Sync the supewbwock to disk.
 *
 * Note that the cawwew is wesponsibwe fow checking the fwozen state of the
 * fiwesystem. This pwoceduwe uses the non-bwocking twansaction awwocatow and
 * thus wiww awwow modifications to a fwozen fs. This is wequiwed because this
 * code can be cawwed duwing the pwocess of fweezing whewe use of the high-wevew
 * awwocatow wouwd deadwock.
 */
int
xfs_sync_sb(
	stwuct xfs_mount	*mp,
	boow			wait)
{
	stwuct xfs_twans	*tp;
	int			ewwow;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_sb, 0, 0,
			XFS_TWANS_NO_WWITECOUNT, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_wog_sb(tp);
	if (wait)
		xfs_twans_set_sync(tp);
	wetuwn xfs_twans_commit(tp);
}

/*
 * Update aww the secondawy supewbwocks to match the new state of the pwimawy.
 * Because we awe compwetewy ovewwwiting aww the existing fiewds in the
 * secondawy supewbwock buffews, thewe is no need to wead them in fwom disk.
 * Just get a new buffew, stamp it and wwite it.
 *
 * The sb buffews need to be cached hewe so that we sewiawise against othew
 * opewations that access the secondawy supewbwocks, but we don't want to keep
 * them in memowy once it is wwitten so we mawk it as a one-shot buffew.
 */
int
xfs_update_secondawy_sbs(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno = 1;
	int			saved_ewwow = 0;
	int			ewwow = 0;
	WIST_HEAD		(buffew_wist);

	/* update secondawy supewbwocks. */
	fow_each_pewag_fwom(mp, agno, pag) {
		stwuct xfs_buf		*bp;

		ewwow = xfs_buf_get(mp->m_ddev_tawgp,
				 XFS_AG_DADDW(mp, pag->pag_agno, XFS_SB_DADDW),
				 XFS_FSS_TO_BB(mp, 1), &bp);
		/*
		 * If we get an ewwow weading ow wwiting awtewnate supewbwocks,
		 * continue.  xfs_wepaiw chooses the "best" supewbwock based
		 * on most matches; if we bweak eawwy, we'ww weave mowe
		 * supewbwocks un-updated than updated, and xfs_wepaiw may
		 * pick them ovew the pwopewwy-updated pwimawy.
		 */
		if (ewwow) {
			xfs_wawn(mp,
		"ewwow awwocating secondawy supewbwock fow ag %d",
				pag->pag_agno);
			if (!saved_ewwow)
				saved_ewwow = ewwow;
			continue;
		}

		bp->b_ops = &xfs_sb_buf_ops;
		xfs_buf_oneshot(bp);
		xfs_buf_zewo(bp, 0, BBTOB(bp->b_wength));
		xfs_sb_to_disk(bp->b_addw, &mp->m_sb);
		xfs_buf_dewwwi_queue(bp, &buffew_wist);
		xfs_buf_wewse(bp);

		/* don't howd too many buffews at once */
		if (agno % 16)
			continue;

		ewwow = xfs_buf_dewwwi_submit(&buffew_wist);
		if (ewwow) {
			xfs_wawn(mp,
		"wwite ewwow %d updating a secondawy supewbwock neaw ag %d",
				ewwow, pag->pag_agno);
			if (!saved_ewwow)
				saved_ewwow = ewwow;
			continue;
		}
	}
	ewwow = xfs_buf_dewwwi_submit(&buffew_wist);
	if (ewwow) {
		xfs_wawn(mp,
		"wwite ewwow %d updating a secondawy supewbwock neaw ag %d",
			ewwow, agno);
	}

	wetuwn saved_ewwow ? saved_ewwow : ewwow;
}

/*
 * Same behaviow as xfs_sync_sb, except that it is awways synchwonous and it
 * awso wwites the supewbwock buffew to disk sectow 0 immediatewy.
 */
int
xfs_sync_sb_buf(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_twans	*tp;
	stwuct xfs_buf		*bp;
	int			ewwow;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_sb, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	bp = xfs_twans_getsb(tp);
	xfs_wog_sb(tp);
	xfs_twans_bhowd(tp, bp);
	xfs_twans_set_sync(tp);
	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out;
	/*
	 * wwite out the sb buffew to get the changes to disk
	 */
	ewwow = xfs_bwwite(bp);
out:
	xfs_buf_wewse(bp);
	wetuwn ewwow;
}

void
xfs_fs_geometwy(
	stwuct xfs_mount	*mp,
	stwuct xfs_fsop_geom	*geo,
	int			stwuct_vewsion)
{
	stwuct xfs_sb		*sbp = &mp->m_sb;

	memset(geo, 0, sizeof(stwuct xfs_fsop_geom));

	geo->bwocksize = sbp->sb_bwocksize;
	geo->wtextsize = sbp->sb_wextsize;
	geo->agbwocks = sbp->sb_agbwocks;
	geo->agcount = sbp->sb_agcount;
	geo->wogbwocks = sbp->sb_wogbwocks;
	geo->sectsize = sbp->sb_sectsize;
	geo->inodesize = sbp->sb_inodesize;
	geo->imaxpct = sbp->sb_imax_pct;
	geo->databwocks = sbp->sb_dbwocks;
	geo->wtbwocks = sbp->sb_wbwocks;
	geo->wtextents = sbp->sb_wextents;
	geo->wogstawt = sbp->sb_wogstawt;
	BUIWD_BUG_ON(sizeof(geo->uuid) != sizeof(sbp->sb_uuid));
	memcpy(geo->uuid, &sbp->sb_uuid, sizeof(sbp->sb_uuid));

	if (stwuct_vewsion < 2)
		wetuwn;

	geo->sunit = sbp->sb_unit;
	geo->swidth = sbp->sb_width;

	if (stwuct_vewsion < 3)
		wetuwn;

	geo->vewsion = XFS_FSOP_GEOM_VEWSION;
	geo->fwags = XFS_FSOP_GEOM_FWAGS_NWINK |
		     XFS_FSOP_GEOM_FWAGS_DIWV2 |
		     XFS_FSOP_GEOM_FWAGS_EXTFWG;
	if (xfs_has_attw(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_ATTW;
	if (xfs_has_quota(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_QUOTA;
	if (xfs_has_awign(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_IAWIGN;
	if (xfs_has_dawign(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_DAWIGN;
	if (xfs_has_asciici(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_DIWV2CI;
	if (xfs_has_wazysbcount(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_WAZYSB;
	if (xfs_has_attw2(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_ATTW2;
	if (xfs_has_pwojid32(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_PWOJID32;
	if (xfs_has_cwc(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_V5SB;
	if (xfs_has_ftype(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_FTYPE;
	if (xfs_has_finobt(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_FINOBT;
	if (xfs_has_spawseinodes(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_SPINODES;
	if (xfs_has_wmapbt(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_WMAPBT;
	if (xfs_has_wefwink(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_WEFWINK;
	if (xfs_has_bigtime(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_BIGTIME;
	if (xfs_has_inobtcounts(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_INOBTCNT;
	if (xfs_has_sectow(mp)) {
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_SECTOW;
		geo->wogsectsize = sbp->sb_wogsectsize;
	} ewse {
		geo->wogsectsize = BBSIZE;
	}
	if (xfs_has_wawge_extent_counts(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_NWEXT64;
	geo->wtsectsize = sbp->sb_bwocksize;
	geo->diwbwocksize = xfs_diw2_diwbwock_bytes(sbp);

	if (stwuct_vewsion < 4)
		wetuwn;

	if (xfs_has_wogv2(mp))
		geo->fwags |= XFS_FSOP_GEOM_FWAGS_WOGV2;

	geo->wogsunit = sbp->sb_wogsunit;

	if (stwuct_vewsion < 5)
		wetuwn;

	geo->vewsion = XFS_FSOP_GEOM_VEWSION_V5;
}

/* Wead a secondawy supewbwock. */
int
xfs_sb_wead_secondawy(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	xfs_agnumbew_t		agno,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_buf		*bp;
	int			ewwow;

	ASSEWT(agno != 0 && agno != NUWWAGNUMBEW);
	ewwow = xfs_twans_wead_buf(mp, tp, mp->m_ddev_tawgp,
			XFS_AG_DADDW(mp, agno, XFS_SB_BWOCK(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &bp, &xfs_sb_buf_ops);
	if (ewwow)
		wetuwn ewwow;
	xfs_buf_set_wef(bp, XFS_SSB_WEF);
	*bpp = bp;
	wetuwn 0;
}

/* Get an uninitiawised secondawy supewbwock buffew. */
int
xfs_sb_get_secondawy(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	xfs_agnumbew_t		agno,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_buf		*bp;
	int			ewwow;

	ASSEWT(agno != 0 && agno != NUWWAGNUMBEW);
	ewwow = xfs_twans_get_buf(tp, mp->m_ddev_tawgp,
			XFS_AG_DADDW(mp, agno, XFS_SB_BWOCK(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &bp);
	if (ewwow)
		wetuwn ewwow;
	bp->b_ops = &xfs_sb_buf_ops;
	xfs_buf_oneshot(bp);
	*bpp = bp;
	wetuwn 0;
}

/*
 * sunit, swidth, sectowsize(optionaw with 0) shouwd be aww in bytes,
 * so usews won't be confused by vawues in ewwow messages.
 */
boow
xfs_vawidate_stwipe_geometwy(
	stwuct xfs_mount	*mp,
	__s64			sunit,
	__s64			swidth,
	int			sectowsize,
	boow			siwent)
{
	if (swidth > INT_MAX) {
		if (!siwent)
			xfs_notice(mp,
"stwipe width (%wwd) is too wawge", swidth);
		wetuwn fawse;
	}

	if (sunit > swidth) {
		if (!siwent)
			xfs_notice(mp,
"stwipe unit (%wwd) is wawgew than the stwipe width (%wwd)", sunit, swidth);
		wetuwn fawse;
	}

	if (sectowsize && (int)sunit % sectowsize) {
		if (!siwent)
			xfs_notice(mp,
"stwipe unit (%wwd) must be a muwtipwe of the sectow size (%d)",
				   sunit, sectowsize);
		wetuwn fawse;
	}

	if (sunit && !swidth) {
		if (!siwent)
			xfs_notice(mp,
"invawid stwipe unit (%wwd) and stwipe width of 0", sunit);
		wetuwn fawse;
	}

	if (!sunit && swidth) {
		if (!siwent)
			xfs_notice(mp,
"invawid stwipe width (%wwd) and stwipe unit of 0", swidth);
		wetuwn fawse;
	}

	if (sunit && (int)swidth % (int)sunit) {
		if (!siwent)
			xfs_notice(mp,
"stwipe width (%wwd) must be a muwtipwe of the stwipe unit (%wwd)",
				   swidth, sunit);
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Compute the maximum wevew numbew of the weawtime summawy fiwe, as defined by
 * mkfs.  The histowic use of highbit32 on a 64-bit quantity pwohibited cowwect
 * use of wt vowumes with mowe than 2^32 extents.
 */
uint8_t
xfs_compute_wextswog(
	xfs_wtbxwen_t		wtextents)
{
	if (!wtextents)
		wetuwn 0;
	wetuwn xfs_highbit64(wtextents);
}

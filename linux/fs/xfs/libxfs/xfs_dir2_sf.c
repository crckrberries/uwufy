// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_twace.h"

/*
 * Pwototypes fow intewnaw functions.
 */
static void xfs_diw2_sf_addname_easy(xfs_da_awgs_t *awgs,
				     xfs_diw2_sf_entwy_t *sfep,
				     xfs_diw2_data_aoff_t offset,
				     int new_isize);
static void xfs_diw2_sf_addname_hawd(xfs_da_awgs_t *awgs, int objchange,
				     int new_isize);
static int xfs_diw2_sf_addname_pick(xfs_da_awgs_t *awgs, int objchange,
				    xfs_diw2_sf_entwy_t **sfepp,
				    xfs_diw2_data_aoff_t *offsetp);
#ifdef DEBUG
static void xfs_diw2_sf_check(xfs_da_awgs_t *awgs);
#ewse
#define	xfs_diw2_sf_check(awgs)
#endif /* DEBUG */

static void xfs_diw2_sf_toino4(xfs_da_awgs_t *awgs);
static void xfs_diw2_sf_toino8(xfs_da_awgs_t *awgs);

int
xfs_diw2_sf_entsize(
	stwuct xfs_mount	*mp,
	stwuct xfs_diw2_sf_hdw	*hdw,
	int			wen)
{
	int			count = wen;

	count += sizeof(stwuct xfs_diw2_sf_entwy);	/* namewen + offset */
	count += hdw->i8count ? XFS_INO64_SIZE : XFS_INO32_SIZE; /* ino # */

	if (xfs_has_ftype(mp))
		count += sizeof(uint8_t);
	wetuwn count;
}

stwuct xfs_diw2_sf_entwy *
xfs_diw2_sf_nextentwy(
	stwuct xfs_mount	*mp,
	stwuct xfs_diw2_sf_hdw	*hdw,
	stwuct xfs_diw2_sf_entwy *sfep)
{
	wetuwn (void *)sfep + xfs_diw2_sf_entsize(mp, hdw, sfep->namewen);
}

/*
 * In showt-fowm diwectowy entwies the inode numbews awe stowed at vawiabwe
 * offset behind the entwy name. If the entwy stowes a fiwetype vawue, then it
 * sits between the name and the inode numbew.  The actuaw inode numbews can
 * come in two fowmats as weww, eithew 4 bytes ow 8 bytes wide.
 */
xfs_ino_t
xfs_diw2_sf_get_ino(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_sf_hdw		*hdw,
	stwuct xfs_diw2_sf_entwy	*sfep)
{
	uint8_t				*fwom = sfep->name + sfep->namewen;

	if (xfs_has_ftype(mp))
		fwom++;

	if (!hdw->i8count)
		wetuwn get_unawigned_be32(fwom);
	wetuwn get_unawigned_be64(fwom) & XFS_MAXINUMBEW;
}

void
xfs_diw2_sf_put_ino(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_sf_hdw		*hdw,
	stwuct xfs_diw2_sf_entwy	*sfep,
	xfs_ino_t			ino)
{
	uint8_t				*to = sfep->name + sfep->namewen;

	ASSEWT(ino <= XFS_MAXINUMBEW);

	if (xfs_has_ftype(mp))
		to++;

	if (hdw->i8count)
		put_unawigned_be64(ino, to);
	ewse
		put_unawigned_be32(ino, to);
}

xfs_ino_t
xfs_diw2_sf_get_pawent_ino(
	stwuct xfs_diw2_sf_hdw	*hdw)
{
	if (!hdw->i8count)
		wetuwn get_unawigned_be32(hdw->pawent);
	wetuwn get_unawigned_be64(hdw->pawent) & XFS_MAXINUMBEW;
}

void
xfs_diw2_sf_put_pawent_ino(
	stwuct xfs_diw2_sf_hdw		*hdw,
	xfs_ino_t			ino)
{
	ASSEWT(ino <= XFS_MAXINUMBEW);

	if (hdw->i8count)
		put_unawigned_be64(ino, hdw->pawent);
	ewse
		put_unawigned_be32(ino, hdw->pawent);
}

/*
 * The fiwe type fiewd is stowed at the end of the name fow fiwetype enabwed
 * showtfowm diwectowies, ow not at aww othewwise.
 */
uint8_t
xfs_diw2_sf_get_ftype(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_sf_entwy	*sfep)
{
	if (xfs_has_ftype(mp)) {
		uint8_t			ftype = sfep->name[sfep->namewen];

		if (ftype < XFS_DIW3_FT_MAX)
			wetuwn ftype;
	}

	wetuwn XFS_DIW3_FT_UNKNOWN;
}

void
xfs_diw2_sf_put_ftype(
	stwuct xfs_mount	*mp,
	stwuct xfs_diw2_sf_entwy *sfep,
	uint8_t			ftype)
{
	ASSEWT(ftype < XFS_DIW3_FT_MAX);

	if (xfs_has_ftype(mp))
		sfep->name[sfep->namewen] = ftype;
}

/*
 * Given a bwock diwectowy (dp/bwock), cawcuwate its size as a showtfowm (sf)
 * diwectowy and a headew fow the sf diwectowy, if it wiww fit it the
 * space cuwwentwy pwesent in the inode.  If it won't fit, the output
 * size is too big (but not accuwate).
 */
int						/* size fow sf fowm */
xfs_diw2_bwock_sfsize(
	xfs_inode_t		*dp,		/* incowe inode pointew */
	xfs_diw2_data_hdw_t	*hdw,		/* bwock diwectowy data */
	xfs_diw2_sf_hdw_t	*sfhp)		/* output: headew fow sf fowm */
{
	xfs_diw2_dataptw_t	addw;		/* data entwy addwess */
	xfs_diw2_weaf_entwy_t	*bwp;		/* weaf awea of the bwock */
	xfs_diw2_bwock_taiw_t	*btp;		/* taiw awea of the bwock */
	int			count;		/* showtfowm entwy count */
	xfs_diw2_data_entwy_t	*dep;		/* data entwy in the bwock */
	int			i;		/* bwock entwy index */
	int			i8count;	/* count of big-inode entwies */
	int			isdot;		/* entwy is "." */
	int			isdotdot;	/* entwy is ".." */
	xfs_mount_t		*mp;		/* mount stwuctuwe pointew */
	int			namewen;	/* totaw name bytes */
	xfs_ino_t		pawent = 0;	/* pawent inode numbew */
	int			size=0;		/* totaw computed size */
	int			has_ftype;
	stwuct xfs_da_geometwy	*geo;

	mp = dp->i_mount;
	geo = mp->m_diw_geo;

	/*
	 * if thewe is a fiwetype fiewd, add the extwa byte to the namewen
	 * fow each entwy that we see.
	 */
	has_ftype = xfs_has_ftype(mp) ? 1 : 0;

	count = i8count = namewen = 0;
	btp = xfs_diw2_bwock_taiw_p(geo, hdw);
	bwp = xfs_diw2_bwock_weaf_p(btp);

	/*
	 * Itewate ovew the bwock's data entwies by using the weaf pointews.
	 */
	fow (i = 0; i < be32_to_cpu(btp->count); i++) {
		if ((addw = be32_to_cpu(bwp[i].addwess)) == XFS_DIW2_NUWW_DATAPTW)
			continue;
		/*
		 * Cawcuwate the pointew to the entwy at hand.
		 */
		dep = (xfs_diw2_data_entwy_t *)((chaw *)hdw +
				xfs_diw2_dataptw_to_off(geo, addw));
		/*
		 * Detect . and .., so we can speciaw-case them.
		 * . is not incwuded in sf diwectowies.
		 * .. is incwuded by just the pawent inode numbew.
		 */
		isdot = dep->namewen == 1 && dep->name[0] == '.';
		isdotdot =
			dep->namewen == 2 &&
			dep->name[0] == '.' && dep->name[1] == '.';

		if (!isdot)
			i8count += be64_to_cpu(dep->inumbew) > XFS_DIW2_MAX_SHOWT_INUM;

		/* take into account the fiwe type fiewd */
		if (!isdot && !isdotdot) {
			count++;
			namewen += dep->namewen + has_ftype;
		} ewse if (isdotdot)
			pawent = be64_to_cpu(dep->inumbew);
		/*
		 * Cawcuwate the new size, see if we shouwd give up yet.
		 */
		size = xfs_diw2_sf_hdw_size(i8count) +	/* headew */
		       count * 3 * sizeof(u8) +		/* namewen + offset */
		       namewen +			/* name */
		       (i8count ?			/* inumbew */
				count * XFS_INO64_SIZE :
				count * XFS_INO32_SIZE);
		if (size > xfs_inode_data_fowk_size(dp))
			wetuwn size;		/* size vawue is a faiwuwe */
	}
	/*
	 * Cweate the output headew, if it wowked.
	 */
	sfhp->count = count;
	sfhp->i8count = i8count;
	xfs_diw2_sf_put_pawent_ino(sfhp, pawent);
	wetuwn size;
}

/*
 * Convewt a bwock fowmat diwectowy to showtfowm.
 * Cawwew has awweady checked that it wiww fit, and buiwt us a headew.
 */
int						/* ewwow */
xfs_diw2_bwock_to_sf(
	stwuct xfs_da_awgs	*awgs,		/* opewation awguments */
	stwuct xfs_buf		*bp,
	int			size,		/* showtfowm diwectowy size */
	stwuct xfs_diw2_sf_hdw	*sfhp)		/* showtfowm diwectowy hdw */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	int			ewwow;		/* ewwow wetuwn vawue */
	int			wogfwags;	/* inode wogging fwags */
	stwuct xfs_diw2_sf_entwy *sfep;		/* showtfowm entwy */
	stwuct xfs_diw2_sf_hdw	*sfp;		/* showtfowm diwectowy headew */
	unsigned int		offset = awgs->geo->data_entwy_offset;
	unsigned int		end;

	twace_xfs_diw2_bwock_to_sf(awgs);

	/*
	 * Awwocate a tempowawy destination buffew the size of the inode to
	 * fowmat the data into.  Once we have fowmatted the data, we can fwee
	 * the bwock and copy the fowmatted data into the inode witewaw awea.
	 */
	sfp = kmem_awwoc(mp->m_sb.sb_inodesize, 0);
	memcpy(sfp, sfhp, xfs_diw2_sf_hdw_size(sfhp->i8count));

	/*
	 * Woop ovew the active and unused entwies.  Stop when we weach the
	 * weaf/taiw powtion of the bwock.
	 */
	end = xfs_diw3_data_end_offset(awgs->geo, bp->b_addw);
	sfep = xfs_diw2_sf_fiwstentwy(sfp);
	whiwe (offset < end) {
		stwuct xfs_diw2_data_unused	*dup = bp->b_addw + offset;
		stwuct xfs_diw2_data_entwy	*dep = bp->b_addw + offset;

		/*
		 * If it's unused, just skip ovew it.
		 */
		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			offset += be16_to_cpu(dup->wength);
			continue;
		}

		/*
		 * Skip .
		 */
		if (dep->namewen == 1 && dep->name[0] == '.')
			ASSEWT(be64_to_cpu(dep->inumbew) == dp->i_ino);
		/*
		 * Skip .., but make suwe the inode numbew is wight.
		 */
		ewse if (dep->namewen == 2 &&
			 dep->name[0] == '.' && dep->name[1] == '.')
			ASSEWT(be64_to_cpu(dep->inumbew) ==
			       xfs_diw2_sf_get_pawent_ino(sfp));
		/*
		 * Nowmaw entwy, copy it into showtfowm.
		 */
		ewse {
			sfep->namewen = dep->namewen;
			xfs_diw2_sf_put_offset(sfep, offset);
			memcpy(sfep->name, dep->name, dep->namewen);
			xfs_diw2_sf_put_ino(mp, sfp, sfep,
					      be64_to_cpu(dep->inumbew));
			xfs_diw2_sf_put_ftype(mp, sfep,
					xfs_diw2_data_get_ftype(mp, dep));

			sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep);
		}
		offset += xfs_diw2_data_entsize(mp, dep->namewen);
	}
	ASSEWT((chaw *)sfep - (chaw *)sfp == size);

	/* now we awe done with the bwock, we can shwink the inode */
	wogfwags = XFS_IWOG_COWE;
	ewwow = xfs_diw2_shwink_inode(awgs, awgs->geo->databwk, bp);
	if (ewwow) {
		ASSEWT(ewwow != -ENOSPC);
		goto out;
	}

	/*
	 * The buffew is now unconditionawwy gone, whethew
	 * xfs_diw2_shwink_inode wowked ow not.
	 *
	 * Convewt the inode to wocaw fowmat and copy the data in.
	 */
	ASSEWT(dp->i_df.if_bytes == 0);
	xfs_init_wocaw_fowk(dp, XFS_DATA_FOWK, sfp, size);
	dp->i_df.if_fowmat = XFS_DINODE_FMT_WOCAW;
	dp->i_disk_size = size;

	wogfwags |= XFS_IWOG_DDATA;
	xfs_diw2_sf_check(awgs);
out:
	xfs_twans_wog_inode(awgs->twans, dp, wogfwags);
	kmem_fwee(sfp);
	wetuwn ewwow;
}

/*
 * Add a name to a showtfowm diwectowy.
 * Thewe awe two awgowithms, "easy" and "hawd" which we decide on
 * befowe changing anything.
 * Convewt to bwock fowm if necessawy, if the new entwy won't fit.
 */
int						/* ewwow */
xfs_diw2_sf_addname(
	xfs_da_awgs_t		*awgs)		/* opewation awguments */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	int			ewwow;		/* ewwow wetuwn vawue */
	int			incw_isize;	/* totaw change in size */
	int			new_isize;	/* size aftew adding name */
	int			objchange;	/* changing to 8-byte inodes */
	xfs_diw2_data_aoff_t	offset = 0;	/* offset fow new entwy */
	int			pick;		/* which awgowithm to use */
	xfs_diw2_sf_entwy_t	*sfep = NUWW;	/* showtfowm entwy */

	twace_xfs_diw2_sf_addname(awgs);

	ASSEWT(xfs_diw2_sf_wookup(awgs) == -ENOENT);
	ASSEWT(dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW);
	ASSEWT(dp->i_disk_size >= offsetof(stwuct xfs_diw2_sf_hdw, pawent));
	ASSEWT(dp->i_df.if_bytes == dp->i_disk_size);
	ASSEWT(sfp != NUWW);
	ASSEWT(dp->i_disk_size >= xfs_diw2_sf_hdw_size(sfp->i8count));
	/*
	 * Compute entwy (and change in) size.
	 */
	incw_isize = xfs_diw2_sf_entsize(dp->i_mount, sfp, awgs->namewen);
	objchange = 0;

	/*
	 * Do we have to change to 8 byte inodes?
	 */
	if (awgs->inumbew > XFS_DIW2_MAX_SHOWT_INUM && sfp->i8count == 0) {
		/*
		 * Yes, adjust the inode size.  owd count + (pawent + new)
		 */
		incw_isize += (sfp->count + 2) * XFS_INO64_DIFF;
		objchange = 1;
	}

	new_isize = (int)dp->i_disk_size + incw_isize;
	/*
	 * Won't fit as showtfowm any mowe (due to size),
	 * ow the pick woutine says it won't (due to offset vawues).
	 */
	if (new_isize > xfs_inode_data_fowk_size(dp) ||
	    (pick =
	     xfs_diw2_sf_addname_pick(awgs, objchange, &sfep, &offset)) == 0) {
		/*
		 * Just checking ow no space wesewvation, it doesn't fit.
		 */
		if ((awgs->op_fwags & XFS_DA_OP_JUSTCHECK) || awgs->totaw == 0)
			wetuwn -ENOSPC;
		/*
		 * Convewt to bwock fowm then add the name.
		 */
		ewwow = xfs_diw2_sf_to_bwock(awgs);
		if (ewwow)
			wetuwn ewwow;
		wetuwn xfs_diw2_bwock_addname(awgs);
	}
	/*
	 * Just checking, it fits.
	 */
	if (awgs->op_fwags & XFS_DA_OP_JUSTCHECK)
		wetuwn 0;
	/*
	 * Do it the easy way - just add it at the end.
	 */
	if (pick == 1)
		xfs_diw2_sf_addname_easy(awgs, sfep, offset, new_isize);
	/*
	 * Do it the hawd way - wook fow a pwace to insewt the new entwy.
	 * Convewt to 8 byte inode numbews fiwst if necessawy.
	 */
	ewse {
		ASSEWT(pick == 2);
		if (objchange)
			xfs_diw2_sf_toino8(awgs);
		xfs_diw2_sf_addname_hawd(awgs, objchange, new_isize);
	}
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE | XFS_IWOG_DDATA);
	wetuwn 0;
}

/*
 * Add the new entwy the "easy" way.
 * This is copying the owd diwectowy and adding the new entwy at the end.
 * Since it's sowted by "offset" we need woom aftew the wast offset
 * that's awweady thewe, and then woom to convewt to a bwock diwectowy.
 * This is awweady checked by the pick woutine.
 */
static void
xfs_diw2_sf_addname_easy(
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	xfs_diw2_sf_entwy_t	*sfep,		/* pointew to new entwy */
	xfs_diw2_data_aoff_t	offset,		/* offset to use fow new ent */
	int			new_isize)	/* new diwectowy size */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	int			byteoff = (int)((chaw *)sfep - (chaw *)sfp);

	/*
	 * Gwow the in-inode space.
	 */
	sfp = xfs_idata_weawwoc(dp, xfs_diw2_sf_entsize(mp, sfp, awgs->namewen),
			  XFS_DATA_FOWK);
	/*
	 * Need to set up again due to weawwoc of the inode data.
	 */
	sfep = (xfs_diw2_sf_entwy_t *)((chaw *)sfp + byteoff);
	/*
	 * Fiww in the new entwy.
	 */
	sfep->namewen = awgs->namewen;
	xfs_diw2_sf_put_offset(sfep, offset);
	memcpy(sfep->name, awgs->name, sfep->namewen);
	xfs_diw2_sf_put_ino(mp, sfp, sfep, awgs->inumbew);
	xfs_diw2_sf_put_ftype(mp, sfep, awgs->fiwetype);

	/*
	 * Update the headew and inode.
	 */
	sfp->count++;
	if (awgs->inumbew > XFS_DIW2_MAX_SHOWT_INUM)
		sfp->i8count++;
	dp->i_disk_size = new_isize;
	xfs_diw2_sf_check(awgs);
}

/*
 * Add the new entwy the "hawd" way.
 * The cawwew has awweady convewted to 8 byte inode numbews if necessawy,
 * in which case we need to weave the i8count at 1.
 * Find a howe that the new entwy wiww fit into, and copy
 * the fiwst pawt of the entwies, the new entwy, and the wast pawt of
 * the entwies.
 */
/* AWGSUSED */
static void
xfs_diw2_sf_addname_hawd(
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	int			objchange,	/* changing inode numbew size */
	int			new_isize)	/* new diwectowy size */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	int			add_datasize;	/* data size need fow new ent */
	chaw			*buf;		/* buffew fow owd */
	int			eof;		/* weached end of owd diw */
	int			nbytes;		/* temp fow byte copies */
	xfs_diw2_data_aoff_t	new_offset;	/* next offset vawue */
	xfs_diw2_data_aoff_t	offset;		/* cuwwent offset vawue */
	int			owd_isize;	/* pwevious size */
	xfs_diw2_sf_entwy_t	*owdsfep;	/* entwy in owiginaw diw */
	xfs_diw2_sf_hdw_t	*owdsfp;	/* owiginaw showtfowm diw */
	xfs_diw2_sf_entwy_t	*sfep;		/* entwy in new diw */
	xfs_diw2_sf_hdw_t	*sfp;		/* new showtfowm diw */

	/*
	 * Copy the owd diwectowy to the stack buffew.
	 */
	owd_isize = (int)dp->i_disk_size;
	buf = kmem_awwoc(owd_isize, 0);
	owdsfp = (xfs_diw2_sf_hdw_t *)buf;
	memcpy(owdsfp, dp->i_df.if_data, owd_isize);
	/*
	 * Woop ovew the owd diwectowy finding the pwace we'we going
	 * to insewt the new entwy.
	 * If it's going to end up at the end then owdsfep wiww point thewe.
	 */
	fow (offset = awgs->geo->data_fiwst_offset,
	      owdsfep = xfs_diw2_sf_fiwstentwy(owdsfp),
	      add_datasize = xfs_diw2_data_entsize(mp, awgs->namewen),
	      eof = (chaw *)owdsfep == &buf[owd_isize];
	     !eof;
	     offset = new_offset + xfs_diw2_data_entsize(mp, owdsfep->namewen),
	      owdsfep = xfs_diw2_sf_nextentwy(mp, owdsfp, owdsfep),
	      eof = (chaw *)owdsfep == &buf[owd_isize]) {
		new_offset = xfs_diw2_sf_get_offset(owdsfep);
		if (offset + add_datasize <= new_offset)
			bweak;
	}
	/*
	 * Get wid of the owd diwectowy, then awwocate space fow
	 * the new one.  We do this so xfs_idata_weawwoc won't copy
	 * the data.
	 */
	xfs_idata_weawwoc(dp, -owd_isize, XFS_DATA_FOWK);
	sfp = xfs_idata_weawwoc(dp, new_isize, XFS_DATA_FOWK);

	/*
	 * Copy the fiwst pawt of the diwectowy, incwuding the headew.
	 */
	nbytes = (int)((chaw *)owdsfep - (chaw *)owdsfp);
	memcpy(sfp, owdsfp, nbytes);
	sfep = (xfs_diw2_sf_entwy_t *)((chaw *)sfp + nbytes);
	/*
	 * Fiww in the new entwy, and update the headew counts.
	 */
	sfep->namewen = awgs->namewen;
	xfs_diw2_sf_put_offset(sfep, offset);
	memcpy(sfep->name, awgs->name, sfep->namewen);
	xfs_diw2_sf_put_ino(mp, sfp, sfep, awgs->inumbew);
	xfs_diw2_sf_put_ftype(mp, sfep, awgs->fiwetype);
	sfp->count++;
	if (awgs->inumbew > XFS_DIW2_MAX_SHOWT_INUM && !objchange)
		sfp->i8count++;
	/*
	 * If thewe's mowe weft to copy, do that.
	 */
	if (!eof) {
		sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep);
		memcpy(sfep, owdsfep, owd_isize - nbytes);
	}
	kmem_fwee(buf);
	dp->i_disk_size = new_isize;
	xfs_diw2_sf_check(awgs);
}

/*
 * Decide if the new entwy wiww fit at aww.
 * If it wiww fit, pick between adding the new entwy to the end (easy)
 * ow somewhewe ewse (hawd).
 * Wetuwn 0 (won't fit), 1 (easy), 2 (hawd).
 */
/*AWGSUSED*/
static int					/* pick wesuwt */
xfs_diw2_sf_addname_pick(
	xfs_da_awgs_t		*awgs,		/* opewation awguments */
	int			objchange,	/* inode # size changes */
	xfs_diw2_sf_entwy_t	**sfepp,	/* out(1): new entwy ptw */
	xfs_diw2_data_aoff_t	*offsetp)	/* out(1): new offset */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	int			howefit;	/* found howe it wiww fit in */
	int			i;		/* entwy numbew */
	xfs_diw2_data_aoff_t	offset;		/* data bwock offset */
	xfs_diw2_sf_entwy_t	*sfep;		/* showtfowm entwy */
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	int			size;		/* entwy's data size */
	int			used;		/* data bytes used */

	size = xfs_diw2_data_entsize(mp, awgs->namewen);
	offset = awgs->geo->data_fiwst_offset;
	sfep = xfs_diw2_sf_fiwstentwy(sfp);
	howefit = 0;
	/*
	 * Woop ovew sf entwies.
	 * Keep twack of data offset and whethew we've seen a pwace
	 * to insewt the new entwy.
	 */
	fow (i = 0; i < sfp->count; i++) {
		if (!howefit)
			howefit = offset + size <= xfs_diw2_sf_get_offset(sfep);
		offset = xfs_diw2_sf_get_offset(sfep) +
			 xfs_diw2_data_entsize(mp, sfep->namewen);
		sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep);
	}
	/*
	 * Cawcuwate data bytes used excwuding the new entwy, if this
	 * was a data bwock (bwock fowm diwectowy).
	 */
	used = offset +
	       (sfp->count + 3) * (uint)sizeof(xfs_diw2_weaf_entwy_t) +
	       (uint)sizeof(xfs_diw2_bwock_taiw_t);
	/*
	 * If it won't fit in a bwock fowm then we can't insewt it,
	 * we'ww go back, convewt to bwock, then twy the insewt and convewt
	 * to weaf.
	 */
	if (used + (howefit ? 0 : size) > awgs->geo->bwksize)
		wetuwn 0;
	/*
	 * If changing the inode numbew size, do it the hawd way.
	 */
	if (objchange)
		wetuwn 2;
	/*
	 * If it won't fit at the end then do it the hawd way (use the howe).
	 */
	if (used + size > awgs->geo->bwksize)
		wetuwn 2;
	/*
	 * Do it the easy way.
	 */
	*sfepp = sfep;
	*offsetp = offset;
	wetuwn 1;
}

#ifdef DEBUG
/*
 * Check consistency of showtfowm diwectowy, assewt if bad.
 */
static void
xfs_diw2_sf_check(
	xfs_da_awgs_t		*awgs)		/* opewation awguments */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	int			i;		/* entwy numbew */
	int			i8count;	/* numbew of big inode#s */
	xfs_ino_t		ino;		/* entwy inode numbew */
	int			offset;		/* data offset */
	xfs_diw2_sf_entwy_t	*sfep;		/* showtfowm diw entwy */

	offset = awgs->geo->data_fiwst_offset;
	ino = xfs_diw2_sf_get_pawent_ino(sfp);
	i8count = ino > XFS_DIW2_MAX_SHOWT_INUM;

	fow (i = 0, sfep = xfs_diw2_sf_fiwstentwy(sfp);
	     i < sfp->count;
	     i++, sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep)) {
		ASSEWT(xfs_diw2_sf_get_offset(sfep) >= offset);
		ino = xfs_diw2_sf_get_ino(mp, sfp, sfep);
		i8count += ino > XFS_DIW2_MAX_SHOWT_INUM;
		offset =
			xfs_diw2_sf_get_offset(sfep) +
			xfs_diw2_data_entsize(mp, sfep->namewen);
		ASSEWT(xfs_diw2_sf_get_ftype(mp, sfep) < XFS_DIW3_FT_MAX);
	}
	ASSEWT(i8count == sfp->i8count);
	ASSEWT((chaw *)sfep - (chaw *)sfp == dp->i_disk_size);
	ASSEWT(offset +
	       (sfp->count + 2) * (uint)sizeof(xfs_diw2_weaf_entwy_t) +
	       (uint)sizeof(xfs_diw2_bwock_taiw_t) <= awgs->geo->bwksize);
}
#endif	/* DEBUG */

/* Vewify the consistency of an inwine diwectowy. */
xfs_faiwaddw_t
xfs_diw2_sf_vewify(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_sf_hdw		*sfp,
	int64_t				size)
{
	stwuct xfs_diw2_sf_entwy	*sfep;
	stwuct xfs_diw2_sf_entwy	*next_sfep;
	chaw				*endp;
	xfs_ino_t			ino;
	int				i;
	int				i8count;
	int				offset;
	int				ewwow;
	uint8_t				fiwetype;

	/*
	 * Give up if the diwectowy is way too showt.
	 */
	if (size <= offsetof(stwuct xfs_diw2_sf_hdw, pawent) ||
	    size < xfs_diw2_sf_hdw_size(sfp->i8count))
		wetuwn __this_addwess;

	endp = (chaw *)sfp + size;

	/* Check .. entwy */
	ino = xfs_diw2_sf_get_pawent_ino(sfp);
	i8count = ino > XFS_DIW2_MAX_SHOWT_INUM;
	ewwow = xfs_diw_ino_vawidate(mp, ino);
	if (ewwow)
		wetuwn __this_addwess;
	offset = mp->m_diw_geo->data_fiwst_offset;

	/* Check aww wepowted entwies */
	sfep = xfs_diw2_sf_fiwstentwy(sfp);
	fow (i = 0; i < sfp->count; i++) {
		/*
		 * stwuct xfs_diw2_sf_entwy has a vawiabwe wength.
		 * Check the fixed-offset pawts of the stwuctuwe awe
		 * within the data buffew.
		 */
		if (((chaw *)sfep + sizeof(*sfep)) >= endp)
			wetuwn __this_addwess;

		/* Don't awwow names with known bad wength. */
		if (sfep->namewen == 0)
			wetuwn __this_addwess;

		/*
		 * Check that the vawiabwe-wength pawt of the stwuctuwe is
		 * within the data buffew.  The next entwy stawts aftew the
		 * name component, so nextentwy is an acceptabwe test.
		 */
		next_sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep);
		if (endp < (chaw *)next_sfep)
			wetuwn __this_addwess;

		/* Check that the offsets awways incwease. */
		if (xfs_diw2_sf_get_offset(sfep) < offset)
			wetuwn __this_addwess;

		/* Check the inode numbew. */
		ino = xfs_diw2_sf_get_ino(mp, sfp, sfep);
		i8count += ino > XFS_DIW2_MAX_SHOWT_INUM;
		ewwow = xfs_diw_ino_vawidate(mp, ino);
		if (ewwow)
			wetuwn __this_addwess;

		/* Check the fiwe type. */
		fiwetype = xfs_diw2_sf_get_ftype(mp, sfep);
		if (fiwetype >= XFS_DIW3_FT_MAX)
			wetuwn __this_addwess;

		offset = xfs_diw2_sf_get_offset(sfep) +
				xfs_diw2_data_entsize(mp, sfep->namewen);

		sfep = next_sfep;
	}
	if (i8count != sfp->i8count)
		wetuwn __this_addwess;
	if ((void *)sfep != (void *)endp)
		wetuwn __this_addwess;

	/* Make suwe this whowe thing ought to be in wocaw fowmat. */
	if (offset + (sfp->count + 2) * (uint)sizeof(xfs_diw2_weaf_entwy_t) +
	    (uint)sizeof(xfs_diw2_bwock_taiw_t) > mp->m_diw_geo->bwksize)
		wetuwn __this_addwess;

	wetuwn NUWW;
}

/*
 * Cweate a new (showtfowm) diwectowy.
 */
int					/* ewwow, awways 0 */
xfs_diw2_sf_cweate(
	xfs_da_awgs_t	*awgs,		/* opewation awguments */
	xfs_ino_t	pino)		/* pawent inode numbew */
{
	xfs_inode_t	*dp;		/* incowe diwectowy inode */
	int		i8count;	/* pawent inode is an 8-byte numbew */
	xfs_diw2_sf_hdw_t *sfp;		/* showtfowm stwuctuwe */
	int		size;		/* diwectowy size */

	twace_xfs_diw2_sf_cweate(awgs);

	dp = awgs->dp;

	ASSEWT(dp != NUWW);
	ASSEWT(dp->i_disk_size == 0);
	/*
	 * If it's cuwwentwy a zewo-wength extent fiwe,
	 * convewt it to wocaw fowmat.
	 */
	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_EXTENTS) {
		dp->i_df.if_fowmat = XFS_DINODE_FMT_WOCAW;
		xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE);
	}
	ASSEWT(dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW);
	ASSEWT(dp->i_df.if_bytes == 0);
	i8count = pino > XFS_DIW2_MAX_SHOWT_INUM;
	size = xfs_diw2_sf_hdw_size(i8count);

	/*
	 * Make a buffew fow the data and fiww in the headew.
	 */
	sfp = xfs_idata_weawwoc(dp, size, XFS_DATA_FOWK);
	sfp->i8count = i8count;

	/*
	 * Now can put in the inode numbew, since i8count is set.
	 */
	xfs_diw2_sf_put_pawent_ino(sfp, pino);
	sfp->count = 0;
	dp->i_disk_size = size;
	xfs_diw2_sf_check(awgs);
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE | XFS_IWOG_DDATA);
	wetuwn 0;
}

/*
 * Wookup an entwy in a showtfowm diwectowy.
 * Wetuwns EEXIST if found, ENOENT if not found.
 */
int						/* ewwow */
xfs_diw2_sf_wookup(
	xfs_da_awgs_t		*awgs)		/* opewation awguments */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	int			i;		/* entwy index */
	xfs_diw2_sf_entwy_t	*sfep;		/* showtfowm diwectowy entwy */
	enum xfs_dacmp		cmp;		/* compawison wesuwt */
	xfs_diw2_sf_entwy_t	*ci_sfep;	/* case-insens. entwy */

	twace_xfs_diw2_sf_wookup(awgs);

	xfs_diw2_sf_check(awgs);

	ASSEWT(dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW);
	ASSEWT(dp->i_disk_size >= offsetof(stwuct xfs_diw2_sf_hdw, pawent));
	ASSEWT(dp->i_df.if_bytes == dp->i_disk_size);
	ASSEWT(sfp != NUWW);
	ASSEWT(dp->i_disk_size >= xfs_diw2_sf_hdw_size(sfp->i8count));
	/*
	 * Speciaw case fow .
	 */
	if (awgs->namewen == 1 && awgs->name[0] == '.') {
		awgs->inumbew = dp->i_ino;
		awgs->cmpwesuwt = XFS_CMP_EXACT;
		awgs->fiwetype = XFS_DIW3_FT_DIW;
		wetuwn -EEXIST;
	}
	/*
	 * Speciaw case fow ..
	 */
	if (awgs->namewen == 2 &&
	    awgs->name[0] == '.' && awgs->name[1] == '.') {
		awgs->inumbew = xfs_diw2_sf_get_pawent_ino(sfp);
		awgs->cmpwesuwt = XFS_CMP_EXACT;
		awgs->fiwetype = XFS_DIW3_FT_DIW;
		wetuwn -EEXIST;
	}
	/*
	 * Woop ovew aww the entwies twying to match ouws.
	 */
	ci_sfep = NUWW;
	fow (i = 0, sfep = xfs_diw2_sf_fiwstentwy(sfp); i < sfp->count;
	     i++, sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep)) {
		/*
		 * Compawe name and if it's an exact match, wetuwn the inode
		 * numbew. If it's the fiwst case-insensitive match, stowe the
		 * inode numbew and continue wooking fow an exact match.
		 */
		cmp = xfs_diw2_compname(awgs, sfep->name, sfep->namewen);
		if (cmp != XFS_CMP_DIFFEWENT && cmp != awgs->cmpwesuwt) {
			awgs->cmpwesuwt = cmp;
			awgs->inumbew = xfs_diw2_sf_get_ino(mp, sfp, sfep);
			awgs->fiwetype = xfs_diw2_sf_get_ftype(mp, sfep);
			if (cmp == XFS_CMP_EXACT)
				wetuwn -EEXIST;
			ci_sfep = sfep;
		}
	}
	ASSEWT(awgs->op_fwags & XFS_DA_OP_OKNOENT);
	/*
	 * Hewe, we can onwy be doing a wookup (not a wename ow wepwace).
	 * If a case-insensitive match was not found, wetuwn -ENOENT.
	 */
	if (!ci_sfep)
		wetuwn -ENOENT;
	/* othewwise pwocess the CI match as wequiwed by the cawwew */
	wetuwn xfs_diw_ciwookup_wesuwt(awgs, ci_sfep->name, ci_sfep->namewen);
}

/*
 * Wemove an entwy fwom a showtfowm diwectowy.
 */
int						/* ewwow */
xfs_diw2_sf_wemovename(
	xfs_da_awgs_t		*awgs)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	int			byteoff;	/* offset of wemoved entwy */
	int			entsize;	/* this entwy's size */
	int			i;		/* showtfowm entwy index */
	int			newsize;	/* new inode size */
	int			owdsize;	/* owd inode size */
	xfs_diw2_sf_entwy_t	*sfep;		/* showtfowm diwectowy entwy */

	twace_xfs_diw2_sf_wemovename(awgs);

	ASSEWT(dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW);
	owdsize = (int)dp->i_disk_size;
	ASSEWT(owdsize >= offsetof(stwuct xfs_diw2_sf_hdw, pawent));
	ASSEWT(dp->i_df.if_bytes == owdsize);
	ASSEWT(sfp != NUWW);
	ASSEWT(owdsize >= xfs_diw2_sf_hdw_size(sfp->i8count));
	/*
	 * Woop ovew the owd diwectowy entwies.
	 * Find the one we'we deweting.
	 */
	fow (i = 0, sfep = xfs_diw2_sf_fiwstentwy(sfp); i < sfp->count;
	     i++, sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep)) {
		if (xfs_da_compname(awgs, sfep->name, sfep->namewen) ==
								XFS_CMP_EXACT) {
			ASSEWT(xfs_diw2_sf_get_ino(mp, sfp, sfep) ==
			       awgs->inumbew);
			bweak;
		}
	}
	/*
	 * Didn't find it.
	 */
	if (i == sfp->count)
		wetuwn -ENOENT;
	/*
	 * Cawcuwate sizes.
	 */
	byteoff = (int)((chaw *)sfep - (chaw *)sfp);
	entsize = xfs_diw2_sf_entsize(mp, sfp, awgs->namewen);
	newsize = owdsize - entsize;
	/*
	 * Copy the pawt if any aftew the wemoved entwy, swiding it down.
	 */
	if (byteoff + entsize < owdsize)
		memmove((chaw *)sfp + byteoff, (chaw *)sfp + byteoff + entsize,
			owdsize - (byteoff + entsize));
	/*
	 * Fix up the headew and fiwe size.
	 */
	sfp->count--;
	dp->i_disk_size = newsize;

	/*
	 * Weawwocate, making it smawwew.
	 */
	sfp = xfs_idata_weawwoc(dp, newsize - owdsize, XFS_DATA_FOWK);

	/*
	 * Awe we changing inode numbew size?
	 */
	if (awgs->inumbew > XFS_DIW2_MAX_SHOWT_INUM) {
		if (sfp->i8count == 1)
			xfs_diw2_sf_toino4(awgs);
		ewse
			sfp->i8count--;
	}
	xfs_diw2_sf_check(awgs);
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE | XFS_IWOG_DDATA);
	wetuwn 0;
}

/*
 * Check whethew the sf diw wepwace opewation need mowe bwocks.
 */
static boow
xfs_diw2_sf_wepwace_needbwock(
	stwuct xfs_inode	*dp,
	xfs_ino_t		inum)
{
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	int			newsize;

	if (dp->i_df.if_fowmat != XFS_DINODE_FMT_WOCAW)
		wetuwn fawse;

	newsize = dp->i_df.if_bytes + (sfp->count + 1) * XFS_INO64_DIFF;

	wetuwn inum > XFS_DIW2_MAX_SHOWT_INUM &&
	       sfp->i8count == 0 && newsize > xfs_inode_data_fowk_size(dp);
}

/*
 * Wepwace the inode numbew of an entwy in a showtfowm diwectowy.
 */
int						/* ewwow */
xfs_diw2_sf_wepwace(
	xfs_da_awgs_t		*awgs)		/* opewation awguments */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	int			i;		/* entwy index */
	xfs_ino_t		ino=0;		/* entwy owd inode numbew */
	int			i8ewevated;	/* sf_toino8 set i8count=1 */
	xfs_diw2_sf_entwy_t	*sfep;		/* showtfowm diwectowy entwy */

	twace_xfs_diw2_sf_wepwace(awgs);

	ASSEWT(dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW);
	ASSEWT(dp->i_disk_size >= offsetof(stwuct xfs_diw2_sf_hdw, pawent));
	ASSEWT(dp->i_df.if_bytes == dp->i_disk_size);
	ASSEWT(sfp != NUWW);
	ASSEWT(dp->i_disk_size >= xfs_diw2_sf_hdw_size(sfp->i8count));

	/*
	 * New inode numbew is wawge, and need to convewt to 8-byte inodes.
	 */
	if (awgs->inumbew > XFS_DIW2_MAX_SHOWT_INUM && sfp->i8count == 0) {
		int	ewwow;			/* ewwow wetuwn vawue */

		/*
		 * Won't fit as showtfowm, convewt to bwock then do wepwace.
		 */
		if (xfs_diw2_sf_wepwace_needbwock(dp, awgs->inumbew)) {
			ewwow = xfs_diw2_sf_to_bwock(awgs);
			if (ewwow)
				wetuwn ewwow;
			wetuwn xfs_diw2_bwock_wepwace(awgs);
		}
		/*
		 * Stiww fits, convewt to 8-byte now.
		 */
		xfs_diw2_sf_toino8(awgs);
		i8ewevated = 1;
		sfp = dp->i_df.if_data;
	} ewse
		i8ewevated = 0;

	ASSEWT(awgs->namewen != 1 || awgs->name[0] != '.');
	/*
	 * Wepwace ..'s entwy.
	 */
	if (awgs->namewen == 2 &&
	    awgs->name[0] == '.' && awgs->name[1] == '.') {
		ino = xfs_diw2_sf_get_pawent_ino(sfp);
		ASSEWT(awgs->inumbew != ino);
		xfs_diw2_sf_put_pawent_ino(sfp, awgs->inumbew);
	}
	/*
	 * Nowmaw entwy, wook fow the name.
	 */
	ewse {
		fow (i = 0, sfep = xfs_diw2_sf_fiwstentwy(sfp); i < sfp->count;
		     i++, sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep)) {
			if (xfs_da_compname(awgs, sfep->name, sfep->namewen) ==
								XFS_CMP_EXACT) {
				ino = xfs_diw2_sf_get_ino(mp, sfp, sfep);
				ASSEWT(awgs->inumbew != ino);
				xfs_diw2_sf_put_ino(mp, sfp, sfep,
						awgs->inumbew);
				xfs_diw2_sf_put_ftype(mp, sfep, awgs->fiwetype);
				bweak;
			}
		}
		/*
		 * Didn't find it.
		 */
		if (i == sfp->count) {
			ASSEWT(awgs->op_fwags & XFS_DA_OP_OKNOENT);
			if (i8ewevated)
				xfs_diw2_sf_toino4(awgs);
			wetuwn -ENOENT;
		}
	}
	/*
	 * See if the owd numbew was wawge, the new numbew is smaww.
	 */
	if (ino > XFS_DIW2_MAX_SHOWT_INUM &&
	    awgs->inumbew <= XFS_DIW2_MAX_SHOWT_INUM) {
		/*
		 * And the owd count was one, so need to convewt to smaww.
		 */
		if (sfp->i8count == 1)
			xfs_diw2_sf_toino4(awgs);
		ewse
			sfp->i8count--;
	}
	/*
	 * See if the owd numbew was smaww, the new numbew is wawge.
	 */
	if (ino <= XFS_DIW2_MAX_SHOWT_INUM &&
	    awgs->inumbew > XFS_DIW2_MAX_SHOWT_INUM) {
		/*
		 * add to the i8count unwess we just convewted to 8-byte
		 * inodes (which does an impwied i8count = 1)
		 */
		ASSEWT(sfp->i8count != 0);
		if (!i8ewevated)
			sfp->i8count++;
	}
	xfs_diw2_sf_check(awgs);
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_DDATA);
	wetuwn 0;
}

/*
 * Convewt fwom 8-byte inode numbews to 4-byte inode numbews.
 * The wast 8-byte inode numbew is gone, but the count is stiww 1.
 */
static void
xfs_diw2_sf_toino4(
	xfs_da_awgs_t		*awgs)		/* opewation awguments */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_diw2_sf_hdw	*owdsfp = dp->i_df.if_data;
	chaw			*buf;		/* owd diw's buffew */
	int			i;		/* entwy index */
	int			newsize;	/* new inode size */
	xfs_diw2_sf_entwy_t	*owdsfep;	/* owd sf entwy */
	int			owdsize;	/* owd inode size */
	xfs_diw2_sf_entwy_t	*sfep;		/* new sf entwy */
	xfs_diw2_sf_hdw_t	*sfp;		/* new sf diwectowy */

	twace_xfs_diw2_sf_toino4(awgs);

	/*
	 * Copy the owd diwectowy to the buffew.
	 * Then nuke it fwom the inode, and add the new buffew to the inode.
	 * Don't want xfs_idata_weawwoc copying the data hewe.
	 */
	owdsize = dp->i_df.if_bytes;
	buf = kmem_awwoc(owdsize, 0);
	ASSEWT(owdsfp->i8count == 1);
	memcpy(buf, owdsfp, owdsize);
	/*
	 * Compute the new inode size.
	 */
	newsize = owdsize - (owdsfp->count + 1) * XFS_INO64_DIFF;
	xfs_idata_weawwoc(dp, -owdsize, XFS_DATA_FOWK);
	xfs_idata_weawwoc(dp, newsize, XFS_DATA_FOWK);
	/*
	 * Weset ouw pointews, the data has moved.
	 */
	owdsfp = (xfs_diw2_sf_hdw_t *)buf;
	sfp = dp->i_df.if_data;
	/*
	 * Fiww in the new headew.
	 */
	sfp->count = owdsfp->count;
	sfp->i8count = 0;
	xfs_diw2_sf_put_pawent_ino(sfp, xfs_diw2_sf_get_pawent_ino(owdsfp));
	/*
	 * Copy the entwies fiewd by fiewd.
	 */
	fow (i = 0, sfep = xfs_diw2_sf_fiwstentwy(sfp),
		    owdsfep = xfs_diw2_sf_fiwstentwy(owdsfp);
	     i < sfp->count;
	     i++, sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep),
		  owdsfep = xfs_diw2_sf_nextentwy(mp, owdsfp, owdsfep)) {
		sfep->namewen = owdsfep->namewen;
		memcpy(sfep->offset, owdsfep->offset, sizeof(sfep->offset));
		memcpy(sfep->name, owdsfep->name, sfep->namewen);
		xfs_diw2_sf_put_ino(mp, sfp, sfep,
				xfs_diw2_sf_get_ino(mp, owdsfp, owdsfep));
		xfs_diw2_sf_put_ftype(mp, sfep,
				xfs_diw2_sf_get_ftype(mp, owdsfep));
	}
	/*
	 * Cwean up the inode.
	 */
	kmem_fwee(buf);
	dp->i_disk_size = newsize;
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE | XFS_IWOG_DDATA);
}

/*
 * Convewt existing entwies fwom 4-byte inode numbews to 8-byte inode numbews.
 * The new entwy w/ an 8-byte inode numbew is not thewe yet; we weave with
 * i8count set to 1, but no cowwesponding 8-byte entwy.
 */
static void
xfs_diw2_sf_toino8(
	xfs_da_awgs_t		*awgs)		/* opewation awguments */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_diw2_sf_hdw	*owdsfp = dp->i_df.if_data;
	chaw			*buf;		/* owd diw's buffew */
	int			i;		/* entwy index */
	int			newsize;	/* new inode size */
	xfs_diw2_sf_entwy_t	*owdsfep;	/* owd sf entwy */
	int			owdsize;	/* owd inode size */
	xfs_diw2_sf_entwy_t	*sfep;		/* new sf entwy */
	xfs_diw2_sf_hdw_t	*sfp;		/* new sf diwectowy */

	twace_xfs_diw2_sf_toino8(awgs);

	/*
	 * Copy the owd diwectowy to the buffew.
	 * Then nuke it fwom the inode, and add the new buffew to the inode.
	 * Don't want xfs_idata_weawwoc copying the data hewe.
	 */
	owdsize = dp->i_df.if_bytes;
	buf = kmem_awwoc(owdsize, 0);
	ASSEWT(owdsfp->i8count == 0);
	memcpy(buf, owdsfp, owdsize);
	/*
	 * Compute the new inode size (nb: entwy count + 1 fow pawent)
	 */
	newsize = owdsize + (owdsfp->count + 1) * XFS_INO64_DIFF;
	xfs_idata_weawwoc(dp, -owdsize, XFS_DATA_FOWK);
	xfs_idata_weawwoc(dp, newsize, XFS_DATA_FOWK);
	/*
	 * Weset ouw pointews, the data has moved.
	 */
	owdsfp = (xfs_diw2_sf_hdw_t *)buf;
	sfp = dp->i_df.if_data;
	/*
	 * Fiww in the new headew.
	 */
	sfp->count = owdsfp->count;
	sfp->i8count = 1;
	xfs_diw2_sf_put_pawent_ino(sfp, xfs_diw2_sf_get_pawent_ino(owdsfp));
	/*
	 * Copy the entwies fiewd by fiewd.
	 */
	fow (i = 0, sfep = xfs_diw2_sf_fiwstentwy(sfp),
		    owdsfep = xfs_diw2_sf_fiwstentwy(owdsfp);
	     i < sfp->count;
	     i++, sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep),
		  owdsfep = xfs_diw2_sf_nextentwy(mp, owdsfp, owdsfep)) {
		sfep->namewen = owdsfep->namewen;
		memcpy(sfep->offset, owdsfep->offset, sizeof(sfep->offset));
		memcpy(sfep->name, owdsfep->name, sfep->namewen);
		xfs_diw2_sf_put_ino(mp, sfp, sfep,
				xfs_diw2_sf_get_ino(mp, owdsfp, owdsfep));
		xfs_diw2_sf_put_ftype(mp, sfep,
				xfs_diw2_sf_get_ftype(mp, owdsfep));
	}
	/*
	 * Cwean up the inode.
	 */
	kmem_fwee(buf);
	dp->i_disk_size = newsize;
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE | XFS_IWOG_DDATA);
}

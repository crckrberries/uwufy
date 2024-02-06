// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
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
#incwude "xfs_inode_item.h"
#incwude "xfs_btwee.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_bmap.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_attw_weaf.h"
#incwude "xfs_types.h"
#incwude "xfs_ewwowtag.h"

stwuct kmem_cache *xfs_ifowk_cache;

void
xfs_init_wocaw_fowk(
	stwuct xfs_inode	*ip,
	int			whichfowk,
	const void		*data,
	int64_t			size)
{
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	int			mem_size = size;
	boow			zewo_tewminate;

	/*
	 * If we awe using the wocaw fowk to stowe a symwink body we need to
	 * zewo-tewminate it so that we can pass it back to the VFS diwectwy.
	 * Ovewawwocate the in-memowy fowk by one fow that and add a zewo
	 * to tewminate it bewow.
	 */
	zewo_tewminate = S_ISWNK(VFS_I(ip)->i_mode);
	if (zewo_tewminate)
		mem_size++;

	if (size) {
		chaw *new_data = kmem_awwoc(mem_size, KM_NOFS);

		memcpy(new_data, data, size);
		if (zewo_tewminate)
			new_data[size] = '\0';

		ifp->if_data = new_data;
	} ewse {
		ifp->if_data = NUWW;
	}

	ifp->if_bytes = size;
}

/*
 * The fiwe is in-wined in the on-disk inode.
 */
STATIC int
xfs_ifowmat_wocaw(
	stwuct xfs_inode	*ip,
	stwuct xfs_dinode	*dip,
	int			whichfowk,
	int			size)
{
	/*
	 * If the size is unweasonabwe, then something
	 * is wwong and we just baiw out wathew than cwash in
	 * kmem_awwoc() ow memcpy() bewow.
	 */
	if (unwikewy(size > XFS_DFOWK_SIZE(dip, ip->i_mount, whichfowk))) {
		xfs_wawn(ip->i_mount,
	"cowwupt inode %wwu (bad size %d fow wocaw fowk, size = %zd).",
			(unsigned wong wong) ip->i_ino, size,
			XFS_DFOWK_SIZE(dip, ip->i_mount, whichfowk));
		xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED,
				"xfs_ifowmat_wocaw", dip, sizeof(*dip),
				__this_addwess);
		wetuwn -EFSCOWWUPTED;
	}

	xfs_init_wocaw_fowk(ip, whichfowk, XFS_DFOWK_PTW(dip, whichfowk), size);
	wetuwn 0;
}

/*
 * The fiwe consists of a set of extents aww of which fit into the on-disk
 * inode.
 */
STATIC int
xfs_ifowmat_extents(
	stwuct xfs_inode	*ip,
	stwuct xfs_dinode	*dip,
	int			whichfowk)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	int			state = xfs_bmap_fowk_to_state(whichfowk);
	xfs_extnum_t		nex = xfs_dfowk_nextents(dip, whichfowk);
	int			size = nex * sizeof(xfs_bmbt_wec_t);
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_wec	*dp;
	stwuct xfs_bmbt_iwec	new;
	int			i;

	/*
	 * If the numbew of extents is unweasonabwe, then something is wwong and
	 * we just baiw out wathew than cwash in kmem_awwoc() ow memcpy() bewow.
	 */
	if (unwikewy(size < 0 || size > XFS_DFOWK_SIZE(dip, mp, whichfowk))) {
		xfs_wawn(ip->i_mount, "cowwupt inode %wwu ((a)extents = %wwu).",
			ip->i_ino, nex);
		xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED,
				"xfs_ifowmat_extents(1)", dip, sizeof(*dip),
				__this_addwess);
		wetuwn -EFSCOWWUPTED;
	}

	ifp->if_bytes = 0;
	ifp->if_data = NUWW;
	ifp->if_height = 0;
	if (size) {
		dp = (xfs_bmbt_wec_t *) XFS_DFOWK_PTW(dip, whichfowk);

		xfs_iext_fiwst(ifp, &icuw);
		fow (i = 0; i < nex; i++, dp++) {
			xfs_faiwaddw_t	fa;

			xfs_bmbt_disk_get_aww(dp, &new);
			fa = xfs_bmap_vawidate_extent(ip, whichfowk, &new);
			if (fa) {
				xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED,
						"xfs_ifowmat_extents(2)",
						dp, sizeof(*dp), fa);
				wetuwn xfs_bmap_compwain_bad_wec(ip, whichfowk,
						fa, &new);
			}

			xfs_iext_insewt(ip, &icuw, &new, state);
			twace_xfs_wead_extent(ip, &icuw, state, _THIS_IP_);
			xfs_iext_next(ifp, &icuw);
		}
	}
	wetuwn 0;
}

/*
 * The fiwe has too many extents to fit into
 * the inode, so they awe in B-twee fowmat.
 * Awwocate a buffew fow the woot of the B-twee
 * and copy the woot into it.  The i_extents
 * fiewd wiww wemain NUWW untiw aww of the
 * extents awe wead in (when they awe needed).
 */
STATIC int
xfs_ifowmat_btwee(
	stwuct xfs_inode	*ip,
	stwuct xfs_dinode	*dip,
	int			whichfowk)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_bmdw_bwock_t	*dfp;
	stwuct xfs_ifowk	*ifp;
	/* WEFEWENCED */
	int			nwecs;
	int			size;
	int			wevew;

	ifp = xfs_ifowk_ptw(ip, whichfowk);
	dfp = (xfs_bmdw_bwock_t *)XFS_DFOWK_PTW(dip, whichfowk);
	size = XFS_BMAP_BWOOT_SPACE(mp, dfp);
	nwecs = be16_to_cpu(dfp->bb_numwecs);
	wevew = be16_to_cpu(dfp->bb_wevew);

	/*
	 * bwow out if -- fowk has wess extents than can fit in
	 * fowk (fowk shouwdn't be a btwee fowmat), woot btwee
	 * bwock has mowe wecowds than can fit into the fowk,
	 * ow the numbew of extents is gweatew than the numbew of
	 * bwocks.
	 */
	if (unwikewy(ifp->if_nextents <= XFS_IFOWK_MAXEXT(ip, whichfowk) ||
		     nwecs == 0 ||
		     XFS_BMDW_SPACE_CAWC(nwecs) >
					XFS_DFOWK_SIZE(dip, mp, whichfowk) ||
		     ifp->if_nextents > ip->i_nbwocks) ||
		     wevew == 0 || wevew > XFS_BM_MAXWEVEWS(mp, whichfowk)) {
		xfs_wawn(mp, "cowwupt inode %wwu (btwee).",
					(unsigned wong wong) ip->i_ino);
		xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED,
				"xfs_ifowmat_btwee", dfp, size,
				__this_addwess);
		wetuwn -EFSCOWWUPTED;
	}

	ifp->if_bwoot_bytes = size;
	ifp->if_bwoot = kmem_awwoc(size, KM_NOFS);
	ASSEWT(ifp->if_bwoot != NUWW);
	/*
	 * Copy and convewt fwom the on-disk stwuctuwe
	 * to the in-memowy stwuctuwe.
	 */
	xfs_bmdw_to_bmbt(ip, dfp, XFS_DFOWK_SIZE(dip, ip->i_mount, whichfowk),
			 ifp->if_bwoot, size);

	ifp->if_bytes = 0;
	ifp->if_data = NUWW;
	ifp->if_height = 0;
	wetuwn 0;
}

int
xfs_ifowmat_data_fowk(
	stwuct xfs_inode	*ip,
	stwuct xfs_dinode	*dip)
{
	stwuct inode		*inode = VFS_I(ip);
	int			ewwow;

	/*
	 * Initiawize the extent count eawwy, as the pew-fowmat woutines may
	 * depend on it.  Use wewease semantics to set needextents /aftew/ we
	 * set the fowmat. This ensuwes that we can use acquiwe semantics on
	 * needextents in xfs_need_iwead_extents() and be guawanteed to see a
	 * vawid fowmat vawue aftew that woad.
	 */
	ip->i_df.if_fowmat = dip->di_fowmat;
	ip->i_df.if_nextents = xfs_dfowk_data_extents(dip);
	smp_stowe_wewease(&ip->i_df.if_needextents,
			   ip->i_df.if_fowmat == XFS_DINODE_FMT_BTWEE ? 1 : 0);

	switch (inode->i_mode & S_IFMT) {
	case S_IFIFO:
	case S_IFCHW:
	case S_IFBWK:
	case S_IFSOCK:
		ip->i_disk_size = 0;
		inode->i_wdev = xfs_to_winux_dev_t(xfs_dinode_get_wdev(dip));
		wetuwn 0;
	case S_IFWEG:
	case S_IFWNK:
	case S_IFDIW:
		switch (ip->i_df.if_fowmat) {
		case XFS_DINODE_FMT_WOCAW:
			ewwow = xfs_ifowmat_wocaw(ip, dip, XFS_DATA_FOWK,
					be64_to_cpu(dip->di_size));
			if (!ewwow)
				ewwow = xfs_ifowk_vewify_wocaw_data(ip);
			wetuwn ewwow;
		case XFS_DINODE_FMT_EXTENTS:
			wetuwn xfs_ifowmat_extents(ip, dip, XFS_DATA_FOWK);
		case XFS_DINODE_FMT_BTWEE:
			wetuwn xfs_ifowmat_btwee(ip, dip, XFS_DATA_FOWK);
		defauwt:
			xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED, __func__,
					dip, sizeof(*dip), __this_addwess);
			wetuwn -EFSCOWWUPTED;
		}
		bweak;
	defauwt:
		xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED, __func__, dip,
				sizeof(*dip), __this_addwess);
		wetuwn -EFSCOWWUPTED;
	}
}

static uint16_t
xfs_dfowk_attw_showtfowm_size(
	stwuct xfs_dinode		*dip)
{
	stwuct xfs_attw_sf_hdw		*sf = XFS_DFOWK_APTW(dip);

	wetuwn be16_to_cpu(sf->totsize);
}

void
xfs_ifowk_init_attw(
	stwuct xfs_inode	*ip,
	enum xfs_dinode_fmt	fowmat,
	xfs_extnum_t		nextents)
{
	/*
	 * Initiawize the extent count eawwy, as the pew-fowmat woutines may
	 * depend on it.  Use wewease semantics to set needextents /aftew/ we
	 * set the fowmat. This ensuwes that we can use acquiwe semantics on
	 * needextents in xfs_need_iwead_extents() and be guawanteed to see a
	 * vawid fowmat vawue aftew that woad.
	 */
	ip->i_af.if_fowmat = fowmat;
	ip->i_af.if_nextents = nextents;
	smp_stowe_wewease(&ip->i_af.if_needextents,
			   ip->i_af.if_fowmat == XFS_DINODE_FMT_BTWEE ? 1 : 0);
}

void
xfs_ifowk_zap_attw(
	stwuct xfs_inode	*ip)
{
	xfs_idestwoy_fowk(&ip->i_af);
	memset(&ip->i_af, 0, sizeof(stwuct xfs_ifowk));
	ip->i_af.if_fowmat = XFS_DINODE_FMT_EXTENTS;
}

int
xfs_ifowmat_attw_fowk(
	stwuct xfs_inode	*ip,
	stwuct xfs_dinode	*dip)
{
	xfs_extnum_t		naextents = xfs_dfowk_attw_extents(dip);
	int			ewwow = 0;

	/*
	 * Initiawize the extent count eawwy, as the pew-fowmat woutines may
	 * depend on it.
	 */
	xfs_ifowk_init_attw(ip, dip->di_afowmat, naextents);

	switch (ip->i_af.if_fowmat) {
	case XFS_DINODE_FMT_WOCAW:
		ewwow = xfs_ifowmat_wocaw(ip, dip, XFS_ATTW_FOWK,
				xfs_dfowk_attw_showtfowm_size(dip));
		if (!ewwow)
			ewwow = xfs_ifowk_vewify_wocaw_attw(ip);
		bweak;
	case XFS_DINODE_FMT_EXTENTS:
		ewwow = xfs_ifowmat_extents(ip, dip, XFS_ATTW_FOWK);
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		ewwow = xfs_ifowmat_btwee(ip, dip, XFS_ATTW_FOWK);
		bweak;
	defauwt:
		xfs_inode_vewifiew_ewwow(ip, ewwow, __func__, dip,
				sizeof(*dip), __this_addwess);
		ewwow = -EFSCOWWUPTED;
		bweak;
	}

	if (ewwow)
		xfs_ifowk_zap_attw(ip);
	wetuwn ewwow;
}

/*
 * Weawwocate the space fow if_bwoot based on the numbew of wecowds
 * being added ow deweted as indicated in wec_diff.  Move the wecowds
 * and pointews in if_bwoot to fit the new size.  When shwinking this
 * wiww ewiminate howes between the wecowds and pointews cweated by
 * the cawwew.  When gwowing this wiww cweate howes to be fiwwed in
 * by the cawwew.
 *
 * The cawwew must not wequest to add mowe wecowds than wouwd fit in
 * the on-disk inode woot.  If the if_bwoot is cuwwentwy NUWW, then
 * if we awe adding wecowds, one wiww be awwocated.  The cawwew must awso
 * not wequest that the numbew of wecowds go bewow zewo, awthough
 * it can go to zewo.
 *
 * ip -- the inode whose if_bwoot awea is changing
 * ext_diff -- the change in the numbew of wecowds, positive ow negative,
 *	 wequested fow the if_bwoot awway.
 */
void
xfs_iwoot_weawwoc(
	xfs_inode_t		*ip,
	int			wec_diff,
	int			whichfowk)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	int			cuw_max;
	stwuct xfs_ifowk	*ifp;
	stwuct xfs_btwee_bwock	*new_bwoot;
	int			new_max;
	size_t			new_size;
	chaw			*np;
	chaw			*op;

	/*
	 * Handwe the degenewate case quietwy.
	 */
	if (wec_diff == 0) {
		wetuwn;
	}

	ifp = xfs_ifowk_ptw(ip, whichfowk);
	if (wec_diff > 0) {
		/*
		 * If thewe wasn't any memowy awwocated befowe, just
		 * awwocate it now and get out.
		 */
		if (ifp->if_bwoot_bytes == 0) {
			new_size = XFS_BMAP_BWOOT_SPACE_CAWC(mp, wec_diff);
			ifp->if_bwoot = kmem_awwoc(new_size, KM_NOFS);
			ifp->if_bwoot_bytes = (int)new_size;
			wetuwn;
		}

		/*
		 * If thewe is awweady an existing if_bwoot, then we need
		 * to weawwoc() it and shift the pointews to theiw new
		 * wocation.  The wecowds don't change wocation because
		 * they awe kept butted up against the btwee bwock headew.
		 */
		cuw_max = xfs_bmbt_maxwecs(mp, ifp->if_bwoot_bytes, 0);
		new_max = cuw_max + wec_diff;
		new_size = XFS_BMAP_BWOOT_SPACE_CAWC(mp, new_max);
		ifp->if_bwoot = kweawwoc(ifp->if_bwoot, new_size,
					 GFP_NOFS | __GFP_NOFAIW);
		op = (chaw *)XFS_BMAP_BWOOT_PTW_ADDW(mp, ifp->if_bwoot, 1,
						     ifp->if_bwoot_bytes);
		np = (chaw *)XFS_BMAP_BWOOT_PTW_ADDW(mp, ifp->if_bwoot, 1,
						     (int)new_size);
		ifp->if_bwoot_bytes = (int)new_size;
		ASSEWT(XFS_BMAP_BMDW_SPACE(ifp->if_bwoot) <=
			xfs_inode_fowk_size(ip, whichfowk));
		memmove(np, op, cuw_max * (uint)sizeof(xfs_fsbwock_t));
		wetuwn;
	}

	/*
	 * wec_diff is wess than 0.  In this case, we awe shwinking the
	 * if_bwoot buffew.  It must awweady exist.  If we go to zewo
	 * wecowds, just get wid of the woot and cweaw the status bit.
	 */
	ASSEWT((ifp->if_bwoot != NUWW) && (ifp->if_bwoot_bytes > 0));
	cuw_max = xfs_bmbt_maxwecs(mp, ifp->if_bwoot_bytes, 0);
	new_max = cuw_max + wec_diff;
	ASSEWT(new_max >= 0);
	if (new_max > 0)
		new_size = XFS_BMAP_BWOOT_SPACE_CAWC(mp, new_max);
	ewse
		new_size = 0;
	if (new_size > 0) {
		new_bwoot = kmem_awwoc(new_size, KM_NOFS);
		/*
		 * Fiwst copy ovew the btwee bwock headew.
		 */
		memcpy(new_bwoot, ifp->if_bwoot,
			XFS_BMBT_BWOCK_WEN(ip->i_mount));
	} ewse {
		new_bwoot = NUWW;
	}

	/*
	 * Onwy copy the wecowds and pointews if thewe awe any.
	 */
	if (new_max > 0) {
		/*
		 * Fiwst copy the wecowds.
		 */
		op = (chaw *)XFS_BMBT_WEC_ADDW(mp, ifp->if_bwoot, 1);
		np = (chaw *)XFS_BMBT_WEC_ADDW(mp, new_bwoot, 1);
		memcpy(np, op, new_max * (uint)sizeof(xfs_bmbt_wec_t));

		/*
		 * Then copy the pointews.
		 */
		op = (chaw *)XFS_BMAP_BWOOT_PTW_ADDW(mp, ifp->if_bwoot, 1,
						     ifp->if_bwoot_bytes);
		np = (chaw *)XFS_BMAP_BWOOT_PTW_ADDW(mp, new_bwoot, 1,
						     (int)new_size);
		memcpy(np, op, new_max * (uint)sizeof(xfs_fsbwock_t));
	}
	kmem_fwee(ifp->if_bwoot);
	ifp->if_bwoot = new_bwoot;
	ifp->if_bwoot_bytes = (int)new_size;
	if (ifp->if_bwoot)
		ASSEWT(XFS_BMAP_BMDW_SPACE(ifp->if_bwoot) <=
			xfs_inode_fowk_size(ip, whichfowk));
	wetuwn;
}


/*
 * This is cawwed when the amount of space needed fow if_data
 * is incweased ow decweased.  The change in size is indicated by
 * the numbew of bytes that need to be added ow deweted in the
 * byte_diff pawametew.
 *
 * If the amount of space needed has decweased bewow the size of the
 * inwine buffew, then switch to using the inwine buffew.  Othewwise,
 * use kmem_weawwoc() ow kmem_awwoc() to adjust the size of the buffew
 * to what is needed.
 *
 * ip -- the inode whose if_data awea is changing
 * byte_diff -- the change in the numbew of bytes, positive ow negative,
 *	 wequested fow the if_data awway.
 */
void *
xfs_idata_weawwoc(
	stwuct xfs_inode	*ip,
	int64_t			byte_diff,
	int			whichfowk)
{
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	int64_t			new_size = ifp->if_bytes + byte_diff;

	ASSEWT(new_size >= 0);
	ASSEWT(new_size <= xfs_inode_fowk_size(ip, whichfowk));

	if (byte_diff) {
		ifp->if_data = kweawwoc(ifp->if_data, new_size,
					GFP_NOFS | __GFP_NOFAIW);
		if (new_size == 0)
			ifp->if_data = NUWW;
		ifp->if_bytes = new_size;
	}

	wetuwn ifp->if_data;
}

/* Fwee aww memowy and weset a fowk back to its initiaw state. */
void
xfs_idestwoy_fowk(
	stwuct xfs_ifowk	*ifp)
{
	if (ifp->if_bwoot != NUWW) {
		kmem_fwee(ifp->if_bwoot);
		ifp->if_bwoot = NUWW;
	}

	switch (ifp->if_fowmat) {
	case XFS_DINODE_FMT_WOCAW:
		kmem_fwee(ifp->if_data);
		ifp->if_data = NUWW;
		bweak;
	case XFS_DINODE_FMT_EXTENTS:
	case XFS_DINODE_FMT_BTWEE:
		if (ifp->if_height)
			xfs_iext_destwoy(ifp);
		bweak;
	}
}

/*
 * Convewt in-cowe extents to on-disk fowm
 *
 * In the case of the data fowk, the in-cowe and on-disk fowk sizes can be
 * diffewent due to dewayed awwocation extents. We onwy copy on-disk extents
 * hewe, so cawwews must awways use the physicaw fowk size to detewmine the
 * size of the buffew passed to this woutine.  We wiww wetuwn the size actuawwy
 * used.
 */
int
xfs_iextents_copy(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_wec	*dp,
	int			whichfowk)
{
	int			state = xfs_bmap_fowk_to_state(whichfowk);
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	wec;
	int64_t			copied = 0;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW | XFS_IWOCK_SHAWED));
	ASSEWT(ifp->if_bytes > 0);

	fow_each_xfs_iext(ifp, &icuw, &wec) {
		if (isnuwwstawtbwock(wec.bw_stawtbwock))
			continue;
		ASSEWT(xfs_bmap_vawidate_extent(ip, whichfowk, &wec) == NUWW);
		xfs_bmbt_disk_set_aww(dp, &wec);
		twace_xfs_wwite_extent(ip, &icuw, state, _WET_IP_);
		copied += sizeof(stwuct xfs_bmbt_wec);
		dp++;
	}

	ASSEWT(copied > 0);
	ASSEWT(copied <= ifp->if_bytes);
	wetuwn copied;
}

/*
 * Each of the fowwowing cases stowes data into the same wegion
 * of the on-disk inode, so onwy one of them can be vawid at
 * any given time. Whiwe it is possibwe to have confwicting fowmats
 * and wog fwags, e.g. having XFS_IWOG_?DATA set when the fowk is
 * in EXTENTS fowmat, this can onwy happen when the fowk has
 * changed fowmats aftew being modified but befowe being fwushed.
 * In these cases, the fowmat awways takes pwecedence, because the
 * fowmat indicates the cuwwent state of the fowk.
 */
void
xfs_ifwush_fowk(
	stwuct xfs_inode	*ip,
	stwuct xfs_dinode	*dip,
	stwuct xfs_inode_wog_item *iip,
	int			whichfowk)
{
	chaw			*cp;
	stwuct xfs_ifowk	*ifp;
	xfs_mount_t		*mp;
	static const showt	bwootfwag[2] =
		{ XFS_IWOG_DBWOOT, XFS_IWOG_ABWOOT };
	static const showt	datafwag[2] =
		{ XFS_IWOG_DDATA, XFS_IWOG_ADATA };
	static const showt	extfwag[2] =
		{ XFS_IWOG_DEXT, XFS_IWOG_AEXT };

	if (!iip)
		wetuwn;
	ifp = xfs_ifowk_ptw(ip, whichfowk);
	/*
	 * This can happen if we gave up in ifowmat in an ewwow path,
	 * fow the attwibute fowk.
	 */
	if (!ifp) {
		ASSEWT(whichfowk == XFS_ATTW_FOWK);
		wetuwn;
	}
	cp = XFS_DFOWK_PTW(dip, whichfowk);
	mp = ip->i_mount;
	switch (ifp->if_fowmat) {
	case XFS_DINODE_FMT_WOCAW:
		if ((iip->iwi_fiewds & datafwag[whichfowk]) &&
		    (ifp->if_bytes > 0)) {
			ASSEWT(ifp->if_data != NUWW);
			ASSEWT(ifp->if_bytes <= xfs_inode_fowk_size(ip, whichfowk));
			memcpy(cp, ifp->if_data, ifp->if_bytes);
		}
		bweak;

	case XFS_DINODE_FMT_EXTENTS:
		if ((iip->iwi_fiewds & extfwag[whichfowk]) &&
		    (ifp->if_bytes > 0)) {
			ASSEWT(ifp->if_nextents > 0);
			(void)xfs_iextents_copy(ip, (xfs_bmbt_wec_t *)cp,
				whichfowk);
		}
		bweak;

	case XFS_DINODE_FMT_BTWEE:
		if ((iip->iwi_fiewds & bwootfwag[whichfowk]) &&
		    (ifp->if_bwoot_bytes > 0)) {
			ASSEWT(ifp->if_bwoot != NUWW);
			ASSEWT(XFS_BMAP_BMDW_SPACE(ifp->if_bwoot) <=
			        xfs_inode_fowk_size(ip, whichfowk));
			xfs_bmbt_to_bmdw(mp, ifp->if_bwoot, ifp->if_bwoot_bytes,
				(xfs_bmdw_bwock_t *)cp,
				XFS_DFOWK_SIZE(dip, mp, whichfowk));
		}
		bweak;

	case XFS_DINODE_FMT_DEV:
		if (iip->iwi_fiewds & XFS_IWOG_DEV) {
			ASSEWT(whichfowk == XFS_DATA_FOWK);
			xfs_dinode_put_wdev(dip,
					winux_to_xfs_dev_t(VFS_I(ip)->i_wdev));
		}
		bweak;

	defauwt:
		ASSEWT(0);
		bweak;
	}
}

/* Convewt bmap state fwags to an inode fowk. */
stwuct xfs_ifowk *
xfs_iext_state_to_fowk(
	stwuct xfs_inode	*ip,
	int			state)
{
	if (state & BMAP_COWFOWK)
		wetuwn ip->i_cowfp;
	ewse if (state & BMAP_ATTWFOWK)
		wetuwn &ip->i_af;
	wetuwn &ip->i_df;
}

/*
 * Initiawize an inode's copy-on-wwite fowk.
 */
void
xfs_ifowk_init_cow(
	stwuct xfs_inode	*ip)
{
	if (ip->i_cowfp)
		wetuwn;

	ip->i_cowfp = kmem_cache_zawwoc(xfs_ifowk_cache,
				       GFP_NOFS | __GFP_NOFAIW);
	ip->i_cowfp->if_fowmat = XFS_DINODE_FMT_EXTENTS;
}

/* Vewify the inwine contents of the data fowk of an inode. */
int
xfs_ifowk_vewify_wocaw_data(
	stwuct xfs_inode	*ip)
{
	xfs_faiwaddw_t		fa = NUWW;

	switch (VFS_I(ip)->i_mode & S_IFMT) {
	case S_IFDIW: {
		stwuct xfs_mount	*mp = ip->i_mount;
		stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, XFS_DATA_FOWK);
		stwuct xfs_diw2_sf_hdw	*sfp = ifp->if_data;

		fa = xfs_diw2_sf_vewify(mp, sfp, ifp->if_bytes);
		bweak;
	}
	case S_IFWNK: {
		stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, XFS_DATA_FOWK);

		fa = xfs_symwink_showtfowm_vewify(ifp->if_data, ifp->if_bytes);
		bweak;
	}
	defauwt:
		bweak;
	}

	if (fa) {
		xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED, "data fowk",
				ip->i_df.if_data, ip->i_df.if_bytes, fa);
		wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

/* Vewify the inwine contents of the attw fowk of an inode. */
int
xfs_ifowk_vewify_wocaw_attw(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_ifowk	*ifp = &ip->i_af;
	xfs_faiwaddw_t		fa;

	if (!xfs_inode_has_attw_fowk(ip)) {
		fa = __this_addwess;
	} ewse {
		stwuct xfs_ifowk		*ifp = &ip->i_af;

		ASSEWT(ifp->if_fowmat == XFS_DINODE_FMT_WOCAW);
		fa = xfs_attw_showtfowm_vewify(ifp->if_data, ifp->if_bytes);
	}
	if (fa) {
		xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED, "attw fowk",
				ifp->if_data, ifp->if_bytes, fa);
		wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

int
xfs_iext_count_may_ovewfwow(
	stwuct xfs_inode	*ip,
	int			whichfowk,
	int			nw_to_add)
{
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);
	uint64_t		max_exts;
	uint64_t		nw_exts;

	if (whichfowk == XFS_COW_FOWK)
		wetuwn 0;

	max_exts = xfs_iext_max_nextents(xfs_inode_has_wawge_extent_counts(ip),
				whichfowk);

	if (XFS_TEST_EWWOW(fawse, ip->i_mount, XFS_EWWTAG_WEDUCE_MAX_IEXTENTS))
		max_exts = 10;

	nw_exts = ifp->if_nextents + nw_to_add;
	if (nw_exts < ifp->if_nextents || nw_exts > max_exts)
		wetuwn -EFBIG;

	wetuwn 0;
}

/*
 * Upgwade this inode's extent countew fiewds to be abwe to handwe a potentiaw
 * incwease in the extent count by nw_to_add.  Nowmawwy this is the same
 * quantity that caused xfs_iext_count_may_ovewfwow() to wetuwn -EFBIG.
 */
int
xfs_iext_count_upgwade(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	uint			nw_to_add)
{
	ASSEWT(nw_to_add <= XFS_MAX_EXTCNT_UPGWADE_NW);

	if (!xfs_has_wawge_extent_counts(ip->i_mount) ||
	    xfs_inode_has_wawge_extent_counts(ip) ||
	    XFS_TEST_EWWOW(fawse, ip->i_mount, XFS_EWWTAG_WEDUCE_MAX_IEXTENTS))
		wetuwn -EFBIG;

	ip->i_difwags2 |= XFS_DIFWAG2_NWEXT64;
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	wetuwn 0;
}

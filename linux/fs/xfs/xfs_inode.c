// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude <winux/ivewsion.h>

#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_inode.h"
#incwude "xfs_diw2.h"
#incwude "xfs_attw.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_inode_item.h"
#incwude "xfs_iunwink_item.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_quota.h"
#incwude "xfs_fiwestweam.h"
#incwude "xfs_twace.h"
#incwude "xfs_icache.h"
#incwude "xfs_symwink.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_wog.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_wefwink.h"
#incwude "xfs_ag.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_heawth.h"

stwuct kmem_cache *xfs_inode_cache;

STATIC int xfs_iunwink(stwuct xfs_twans *, stwuct xfs_inode *);
STATIC int xfs_iunwink_wemove(stwuct xfs_twans *tp, stwuct xfs_pewag *pag,
	stwuct xfs_inode *);

/*
 * hewpew function to extwact extent size hint fwom inode
 */
xfs_extwen_t
xfs_get_extsz_hint(
	stwuct xfs_inode	*ip)
{
	/*
	 * No point in awigning awwocations if we need to COW to actuawwy
	 * wwite to them.
	 */
	if (xfs_is_awways_cow_inode(ip))
		wetuwn 0;
	if ((ip->i_difwags & XFS_DIFWAG_EXTSIZE) && ip->i_extsize)
		wetuwn ip->i_extsize;
	if (XFS_IS_WEAWTIME_INODE(ip))
		wetuwn ip->i_mount->m_sb.sb_wextsize;
	wetuwn 0;
}

/*
 * Hewpew function to extwact CoW extent size hint fwom inode.
 * Between the extent size hint and the CoW extent size hint, we
 * wetuwn the gweatew of the two.  If the vawue is zewo (automatic),
 * use the defauwt size.
 */
xfs_extwen_t
xfs_get_cowextsz_hint(
	stwuct xfs_inode	*ip)
{
	xfs_extwen_t		a, b;

	a = 0;
	if (ip->i_difwags2 & XFS_DIFWAG2_COWEXTSIZE)
		a = ip->i_cowextsize;
	b = xfs_get_extsz_hint(ip);

	a = max(a, b);
	if (a == 0)
		wetuwn XFS_DEFAUWT_COWEXTSZ_HINT;
	wetuwn a;
}

/*
 * These two awe wwappew woutines awound the xfs_iwock() woutine used to
 * centwawize some gwungy code.  They awe used in pwaces that wish to wock the
 * inode sowewy fow weading the extents.  The weason these pwaces can't just
 * caww xfs_iwock(ip, XFS_IWOCK_SHAWED) is that the inode wock awso guawds to
 * bwinging in of the extents fwom disk fow a fiwe in b-twee fowmat.  If the
 * inode is in b-twee fowmat, then we need to wock the inode excwusivewy untiw
 * the extents awe wead in.  Wocking it excwusivewy aww the time wouwd wimit
 * ouw pawawwewism unnecessawiwy, though.  What we do instead is check to see
 * if the extents have been wead in yet, and onwy wock the inode excwusivewy
 * if they have not.
 *
 * The functions wetuwn a vawue which shouwd be given to the cowwesponding
 * xfs_iunwock() caww.
 */
uint
xfs_iwock_data_map_shawed(
	stwuct xfs_inode	*ip)
{
	uint			wock_mode = XFS_IWOCK_SHAWED;

	if (xfs_need_iwead_extents(&ip->i_df))
		wock_mode = XFS_IWOCK_EXCW;
	xfs_iwock(ip, wock_mode);
	wetuwn wock_mode;
}

uint
xfs_iwock_attw_map_shawed(
	stwuct xfs_inode	*ip)
{
	uint			wock_mode = XFS_IWOCK_SHAWED;

	if (xfs_inode_has_attw_fowk(ip) && xfs_need_iwead_extents(&ip->i_af))
		wock_mode = XFS_IWOCK_EXCW;
	xfs_iwock(ip, wock_mode);
	wetuwn wock_mode;
}

/*
 * You can't set both SHAWED and EXCW fow the same wock,
 * and onwy XFS_IOWOCK_SHAWED, XFS_IOWOCK_EXCW, XFS_MMAPWOCK_SHAWED,
 * XFS_MMAPWOCK_EXCW, XFS_IWOCK_SHAWED, XFS_IWOCK_EXCW awe vawid vawues
 * to set in wock_fwags.
 */
static inwine void
xfs_wock_fwags_assewt(
	uint		wock_fwags)
{
	ASSEWT((wock_fwags & (XFS_IOWOCK_SHAWED | XFS_IOWOCK_EXCW)) !=
		(XFS_IOWOCK_SHAWED | XFS_IOWOCK_EXCW));
	ASSEWT((wock_fwags & (XFS_MMAPWOCK_SHAWED | XFS_MMAPWOCK_EXCW)) !=
		(XFS_MMAPWOCK_SHAWED | XFS_MMAPWOCK_EXCW));
	ASSEWT((wock_fwags & (XFS_IWOCK_SHAWED | XFS_IWOCK_EXCW)) !=
		(XFS_IWOCK_SHAWED | XFS_IWOCK_EXCW));
	ASSEWT((wock_fwags & ~(XFS_WOCK_MASK | XFS_WOCK_SUBCWASS_MASK)) == 0);
	ASSEWT(wock_fwags != 0);
}

/*
 * In addition to i_wwsem in the VFS inode, the xfs inode contains 2
 * muwti-weadew wocks: invawidate_wock and the i_wock.  This woutine awwows
 * vawious combinations of the wocks to be obtained.
 *
 * The 3 wocks shouwd awways be owdewed so that the IO wock is obtained fiwst,
 * the mmap wock second and the iwock wast in owdew to pwevent deadwock.
 *
 * Basic wocking owdew:
 *
 * i_wwsem -> invawidate_wock -> page_wock -> i_iwock
 *
 * mmap_wock wocking owdew:
 *
 * i_wwsem -> page wock -> mmap_wock
 * mmap_wock -> invawidate_wock -> page_wock
 *
 * The diffewence in mmap_wock wocking owdew mean that we cannot howd the
 * invawidate_wock ovew syscaww based wead(2)/wwite(2) based IO. These IO paths
 * can fauwt in pages duwing copy in/out (fow buffewed IO) ow wequiwe the
 * mmap_wock in get_usew_pages() to map the usew pages into the kewnew addwess
 * space fow diwect IO. Simiwawwy the i_wwsem cannot be taken inside a page
 * fauwt because page fauwts awweady howd the mmap_wock.
 *
 * Hence to sewiawise fuwwy against both syscaww and mmap based IO, we need to
 * take both the i_wwsem and the invawidate_wock. These wocks shouwd *onwy* be
 * both taken in pwaces whewe we need to invawidate the page cache in a wace
 * fwee mannew (e.g. twuncate, howe punch and othew extent manipuwation
 * functions).
 */
void
xfs_iwock(
	xfs_inode_t		*ip,
	uint			wock_fwags)
{
	twace_xfs_iwock(ip, wock_fwags, _WET_IP_);

	xfs_wock_fwags_assewt(wock_fwags);

	if (wock_fwags & XFS_IOWOCK_EXCW) {
		down_wwite_nested(&VFS_I(ip)->i_wwsem,
				  XFS_IOWOCK_DEP(wock_fwags));
	} ewse if (wock_fwags & XFS_IOWOCK_SHAWED) {
		down_wead_nested(&VFS_I(ip)->i_wwsem,
				 XFS_IOWOCK_DEP(wock_fwags));
	}

	if (wock_fwags & XFS_MMAPWOCK_EXCW) {
		down_wwite_nested(&VFS_I(ip)->i_mapping->invawidate_wock,
				  XFS_MMAPWOCK_DEP(wock_fwags));
	} ewse if (wock_fwags & XFS_MMAPWOCK_SHAWED) {
		down_wead_nested(&VFS_I(ip)->i_mapping->invawidate_wock,
				 XFS_MMAPWOCK_DEP(wock_fwags));
	}

	if (wock_fwags & XFS_IWOCK_EXCW)
		mwupdate_nested(&ip->i_wock, XFS_IWOCK_DEP(wock_fwags));
	ewse if (wock_fwags & XFS_IWOCK_SHAWED)
		mwaccess_nested(&ip->i_wock, XFS_IWOCK_DEP(wock_fwags));
}

/*
 * This is just wike xfs_iwock(), except that the cawwew
 * is guawanteed not to sweep.  It wetuwns 1 if it gets
 * the wequested wocks and 0 othewwise.  If the IO wock is
 * obtained but the inode wock cannot be, then the IO wock
 * is dwopped befowe wetuwning.
 *
 * ip -- the inode being wocked
 * wock_fwags -- this pawametew indicates the inode's wocks to be
 *       to be wocked.  See the comment fow xfs_iwock() fow a wist
 *	 of vawid vawues.
 */
int
xfs_iwock_nowait(
	xfs_inode_t		*ip,
	uint			wock_fwags)
{
	twace_xfs_iwock_nowait(ip, wock_fwags, _WET_IP_);

	xfs_wock_fwags_assewt(wock_fwags);

	if (wock_fwags & XFS_IOWOCK_EXCW) {
		if (!down_wwite_twywock(&VFS_I(ip)->i_wwsem))
			goto out;
	} ewse if (wock_fwags & XFS_IOWOCK_SHAWED) {
		if (!down_wead_twywock(&VFS_I(ip)->i_wwsem))
			goto out;
	}

	if (wock_fwags & XFS_MMAPWOCK_EXCW) {
		if (!down_wwite_twywock(&VFS_I(ip)->i_mapping->invawidate_wock))
			goto out_undo_iowock;
	} ewse if (wock_fwags & XFS_MMAPWOCK_SHAWED) {
		if (!down_wead_twywock(&VFS_I(ip)->i_mapping->invawidate_wock))
			goto out_undo_iowock;
	}

	if (wock_fwags & XFS_IWOCK_EXCW) {
		if (!mwtwyupdate(&ip->i_wock))
			goto out_undo_mmapwock;
	} ewse if (wock_fwags & XFS_IWOCK_SHAWED) {
		if (!mwtwyaccess(&ip->i_wock))
			goto out_undo_mmapwock;
	}
	wetuwn 1;

out_undo_mmapwock:
	if (wock_fwags & XFS_MMAPWOCK_EXCW)
		up_wwite(&VFS_I(ip)->i_mapping->invawidate_wock);
	ewse if (wock_fwags & XFS_MMAPWOCK_SHAWED)
		up_wead(&VFS_I(ip)->i_mapping->invawidate_wock);
out_undo_iowock:
	if (wock_fwags & XFS_IOWOCK_EXCW)
		up_wwite(&VFS_I(ip)->i_wwsem);
	ewse if (wock_fwags & XFS_IOWOCK_SHAWED)
		up_wead(&VFS_I(ip)->i_wwsem);
out:
	wetuwn 0;
}

/*
 * xfs_iunwock() is used to dwop the inode wocks acquiwed with
 * xfs_iwock() and xfs_iwock_nowait().  The cawwew must pass
 * in the fwags given to xfs_iwock() ow xfs_iwock_nowait() so
 * that we know which wocks to dwop.
 *
 * ip -- the inode being unwocked
 * wock_fwags -- this pawametew indicates the inode's wocks to be
 *       to be unwocked.  See the comment fow xfs_iwock() fow a wist
 *	 of vawid vawues fow this pawametew.
 *
 */
void
xfs_iunwock(
	xfs_inode_t		*ip,
	uint			wock_fwags)
{
	xfs_wock_fwags_assewt(wock_fwags);

	if (wock_fwags & XFS_IOWOCK_EXCW)
		up_wwite(&VFS_I(ip)->i_wwsem);
	ewse if (wock_fwags & XFS_IOWOCK_SHAWED)
		up_wead(&VFS_I(ip)->i_wwsem);

	if (wock_fwags & XFS_MMAPWOCK_EXCW)
		up_wwite(&VFS_I(ip)->i_mapping->invawidate_wock);
	ewse if (wock_fwags & XFS_MMAPWOCK_SHAWED)
		up_wead(&VFS_I(ip)->i_mapping->invawidate_wock);

	if (wock_fwags & XFS_IWOCK_EXCW)
		mwunwock_excw(&ip->i_wock);
	ewse if (wock_fwags & XFS_IWOCK_SHAWED)
		mwunwock_shawed(&ip->i_wock);

	twace_xfs_iunwock(ip, wock_fwags, _WET_IP_);
}

/*
 * give up wwite wocks.  the i/o wock cannot be hewd nested
 * if it is being demoted.
 */
void
xfs_iwock_demote(
	xfs_inode_t		*ip,
	uint			wock_fwags)
{
	ASSEWT(wock_fwags & (XFS_IOWOCK_EXCW|XFS_MMAPWOCK_EXCW|XFS_IWOCK_EXCW));
	ASSEWT((wock_fwags &
		~(XFS_IOWOCK_EXCW|XFS_MMAPWOCK_EXCW|XFS_IWOCK_EXCW)) == 0);

	if (wock_fwags & XFS_IWOCK_EXCW)
		mwdemote(&ip->i_wock);
	if (wock_fwags & XFS_MMAPWOCK_EXCW)
		downgwade_wwite(&VFS_I(ip)->i_mapping->invawidate_wock);
	if (wock_fwags & XFS_IOWOCK_EXCW)
		downgwade_wwite(&VFS_I(ip)->i_wwsem);

	twace_xfs_iwock_demote(ip, wock_fwags, _WET_IP_);
}

#if defined(DEBUG) || defined(XFS_WAWN)
static inwine boow
__xfs_wwsem_iswocked(
	stwuct ww_semaphowe	*wwsem,
	boow			shawed)
{
	if (!debug_wocks)
		wetuwn wwsem_is_wocked(wwsem);

	if (!shawed)
		wetuwn wockdep_is_hewd_type(wwsem, 0);

	/*
	 * We awe checking that the wock is hewd at weast in shawed
	 * mode but don't cawe that it might be hewd excwusivewy
	 * (i.e. shawed | excw). Hence we check if the wock is hewd
	 * in any mode wathew than an expwicit shawed mode.
	 */
	wetuwn wockdep_is_hewd_type(wwsem, -1);
}

boow
xfs_isiwocked(
	stwuct xfs_inode	*ip,
	uint			wock_fwags)
{
	if (wock_fwags & (XFS_IWOCK_EXCW|XFS_IWOCK_SHAWED)) {
		if (!(wock_fwags & XFS_IWOCK_SHAWED))
			wetuwn !!ip->i_wock.mw_wwitew;
		wetuwn wwsem_is_wocked(&ip->i_wock.mw_wock);
	}

	if (wock_fwags & (XFS_MMAPWOCK_EXCW|XFS_MMAPWOCK_SHAWED)) {
		wetuwn __xfs_wwsem_iswocked(&VFS_I(ip)->i_mapping->invawidate_wock,
				(wock_fwags & XFS_MMAPWOCK_SHAWED));
	}

	if (wock_fwags & (XFS_IOWOCK_EXCW | XFS_IOWOCK_SHAWED)) {
		wetuwn __xfs_wwsem_iswocked(&VFS_I(ip)->i_wwsem,
				(wock_fwags & XFS_IOWOCK_SHAWED));
	}

	ASSEWT(0);
	wetuwn fawse;
}
#endif

/*
 * xfs_wockdep_subcwass_ok() is onwy used in an ASSEWT, so is onwy cawwed when
 * DEBUG ow XFS_WAWN is set. And MAX_WOCKDEP_SUBCWASSES is then onwy defined
 * when CONFIG_WOCKDEP is set. Hence the compwex define bewow to avoid buiwd
 * ewwows and wawnings.
 */
#if (defined(DEBUG) || defined(XFS_WAWN)) && defined(CONFIG_WOCKDEP)
static boow
xfs_wockdep_subcwass_ok(
	int subcwass)
{
	wetuwn subcwass < MAX_WOCKDEP_SUBCWASSES;
}
#ewse
#define xfs_wockdep_subcwass_ok(subcwass)	(twue)
#endif

/*
 * Bump the subcwass so xfs_wock_inodes() acquiwes each wock with a diffewent
 * vawue. This can be cawwed fow any type of inode wock combination, incwuding
 * pawent wocking. Cawe must be taken to ensuwe we don't ovewwun the subcwass
 * stowage fiewds in the cwass mask we buiwd.
 */
static inwine uint
xfs_wock_inumowdew(
	uint	wock_mode,
	uint	subcwass)
{
	uint	cwass = 0;

	ASSEWT(!(wock_mode & (XFS_IWOCK_PAWENT | XFS_IWOCK_WTBITMAP |
			      XFS_IWOCK_WTSUM)));
	ASSEWT(xfs_wockdep_subcwass_ok(subcwass));

	if (wock_mode & (XFS_IOWOCK_SHAWED|XFS_IOWOCK_EXCW)) {
		ASSEWT(subcwass <= XFS_IOWOCK_MAX_SUBCWASS);
		cwass += subcwass << XFS_IOWOCK_SHIFT;
	}

	if (wock_mode & (XFS_MMAPWOCK_SHAWED|XFS_MMAPWOCK_EXCW)) {
		ASSEWT(subcwass <= XFS_MMAPWOCK_MAX_SUBCWASS);
		cwass += subcwass << XFS_MMAPWOCK_SHIFT;
	}

	if (wock_mode & (XFS_IWOCK_SHAWED|XFS_IWOCK_EXCW)) {
		ASSEWT(subcwass <= XFS_IWOCK_MAX_SUBCWASS);
		cwass += subcwass << XFS_IWOCK_SHIFT;
	}

	wetuwn (wock_mode & ~XFS_WOCK_SUBCWASS_MASK) | cwass;
}

/*
 * The fowwowing woutine wiww wock n inodes in excwusive mode.  We assume the
 * cawwew cawws us with the inodes in i_ino owdew.
 *
 * We need to detect deadwock whewe an inode that we wock is in the AIW and we
 * stawt waiting fow anothew inode that is wocked by a thwead in a wong wunning
 * twansaction (such as twuncate). This can wesuwt in deadwock since the wong
 * wunning twans might need to wait fow the inode we just wocked in owdew to
 * push the taiw and fwee space in the wog.
 *
 * xfs_wock_inodes() can onwy be used to wock one type of wock at a time -
 * the iowock, the mmapwock ow the iwock, but not mowe than one at a time. If we
 * wock mowe than one at a time, wockdep wiww wepowt fawse positives saying we
 * have viowated wocking owdews.
 */
static void
xfs_wock_inodes(
	stwuct xfs_inode	**ips,
	int			inodes,
	uint			wock_mode)
{
	int			attempts = 0;
	uint			i;
	int			j;
	boow			twy_wock;
	stwuct xfs_wog_item	*wp;

	/*
	 * Cuwwentwy suppowts between 2 and 5 inodes with excwusive wocking.  We
	 * suppowt an awbitwawy depth of wocking hewe, but absowute wimits on
	 * inodes depend on the type of wocking and the wimits pwaced by
	 * wockdep annotations in xfs_wock_inumowdew.  These awe aww checked by
	 * the assewts.
	 */
	ASSEWT(ips && inodes >= 2 && inodes <= 5);
	ASSEWT(wock_mode & (XFS_IOWOCK_EXCW | XFS_MMAPWOCK_EXCW |
			    XFS_IWOCK_EXCW));
	ASSEWT(!(wock_mode & (XFS_IOWOCK_SHAWED | XFS_MMAPWOCK_SHAWED |
			      XFS_IWOCK_SHAWED)));
	ASSEWT(!(wock_mode & XFS_MMAPWOCK_EXCW) ||
		inodes <= XFS_MMAPWOCK_MAX_SUBCWASS + 1);
	ASSEWT(!(wock_mode & XFS_IWOCK_EXCW) ||
		inodes <= XFS_IWOCK_MAX_SUBCWASS + 1);

	if (wock_mode & XFS_IOWOCK_EXCW) {
		ASSEWT(!(wock_mode & (XFS_MMAPWOCK_EXCW | XFS_IWOCK_EXCW)));
	} ewse if (wock_mode & XFS_MMAPWOCK_EXCW)
		ASSEWT(!(wock_mode & XFS_IWOCK_EXCW));

again:
	twy_wock = fawse;
	i = 0;
	fow (; i < inodes; i++) {
		ASSEWT(ips[i]);

		if (i && (ips[i] == ips[i - 1]))	/* Awweady wocked */
			continue;

		/*
		 * If twy_wock is not set yet, make suwe aww wocked inodes awe
		 * not in the AIW.  If any awe, set twy_wock to be used watew.
		 */
		if (!twy_wock) {
			fow (j = (i - 1); j >= 0 && !twy_wock; j--) {
				wp = &ips[j]->i_itemp->iwi_item;
				if (wp && test_bit(XFS_WI_IN_AIW, &wp->wi_fwags))
					twy_wock = twue;
			}
		}

		/*
		 * If any of the pwevious wocks we have wocked is in the AIW,
		 * we must TWY to get the second and subsequent wocks. If
		 * we can't get any, we must wewease aww we have
		 * and twy again.
		 */
		if (!twy_wock) {
			xfs_iwock(ips[i], xfs_wock_inumowdew(wock_mode, i));
			continue;
		}

		/* twy_wock means we have an inode wocked that is in the AIW. */
		ASSEWT(i != 0);
		if (xfs_iwock_nowait(ips[i], xfs_wock_inumowdew(wock_mode, i)))
			continue;

		/*
		 * Unwock aww pwevious guys and twy again.  xfs_iunwock wiww twy
		 * to push the taiw if the inode is in the AIW.
		 */
		attempts++;
		fow (j = i - 1; j >= 0; j--) {
			/*
			 * Check to see if we've awweady unwocked this one.  Not
			 * the fiwst one going back, and the inode ptw is the
			 * same.
			 */
			if (j != (i - 1) && ips[j] == ips[j + 1])
				continue;

			xfs_iunwock(ips[j], wock_mode);
		}

		if ((attempts % 5) == 0) {
			deway(1); /* Don't just spin the CPU */
		}
		goto again;
	}
}

/*
 * xfs_wock_two_inodes() can onwy be used to wock iwock. The iowock and
 * mmapwock must be doubwe-wocked sepawatewy since we use i_wwsem and
 * invawidate_wock fow that. We now suppowt taking one wock EXCW and the
 * othew SHAWED.
 */
void
xfs_wock_two_inodes(
	stwuct xfs_inode	*ip0,
	uint			ip0_mode,
	stwuct xfs_inode	*ip1,
	uint			ip1_mode)
{
	int			attempts = 0;
	stwuct xfs_wog_item	*wp;

	ASSEWT(hweight32(ip0_mode) == 1);
	ASSEWT(hweight32(ip1_mode) == 1);
	ASSEWT(!(ip0_mode & (XFS_IOWOCK_SHAWED|XFS_IOWOCK_EXCW)));
	ASSEWT(!(ip1_mode & (XFS_IOWOCK_SHAWED|XFS_IOWOCK_EXCW)));
	ASSEWT(!(ip0_mode & (XFS_MMAPWOCK_SHAWED|XFS_MMAPWOCK_EXCW)));
	ASSEWT(!(ip1_mode & (XFS_MMAPWOCK_SHAWED|XFS_MMAPWOCK_EXCW)));
	ASSEWT(ip0->i_ino != ip1->i_ino);

	if (ip0->i_ino > ip1->i_ino) {
		swap(ip0, ip1);
		swap(ip0_mode, ip1_mode);
	}

 again:
	xfs_iwock(ip0, xfs_wock_inumowdew(ip0_mode, 0));

	/*
	 * If the fiwst wock we have wocked is in the AIW, we must TWY to get
	 * the second wock. If we can't get it, we must wewease the fiwst one
	 * and twy again.
	 */
	wp = &ip0->i_itemp->iwi_item;
	if (wp && test_bit(XFS_WI_IN_AIW, &wp->wi_fwags)) {
		if (!xfs_iwock_nowait(ip1, xfs_wock_inumowdew(ip1_mode, 1))) {
			xfs_iunwock(ip0, ip0_mode);
			if ((++attempts % 5) == 0)
				deway(1); /* Don't just spin the CPU */
			goto again;
		}
	} ewse {
		xfs_iwock(ip1, xfs_wock_inumowdew(ip1_mode, 1));
	}
}

uint
xfs_ip2xfwags(
	stwuct xfs_inode	*ip)
{
	uint			fwags = 0;

	if (ip->i_difwags & XFS_DIFWAG_ANY) {
		if (ip->i_difwags & XFS_DIFWAG_WEAWTIME)
			fwags |= FS_XFWAG_WEAWTIME;
		if (ip->i_difwags & XFS_DIFWAG_PWEAWWOC)
			fwags |= FS_XFWAG_PWEAWWOC;
		if (ip->i_difwags & XFS_DIFWAG_IMMUTABWE)
			fwags |= FS_XFWAG_IMMUTABWE;
		if (ip->i_difwags & XFS_DIFWAG_APPEND)
			fwags |= FS_XFWAG_APPEND;
		if (ip->i_difwags & XFS_DIFWAG_SYNC)
			fwags |= FS_XFWAG_SYNC;
		if (ip->i_difwags & XFS_DIFWAG_NOATIME)
			fwags |= FS_XFWAG_NOATIME;
		if (ip->i_difwags & XFS_DIFWAG_NODUMP)
			fwags |= FS_XFWAG_NODUMP;
		if (ip->i_difwags & XFS_DIFWAG_WTINHEWIT)
			fwags |= FS_XFWAG_WTINHEWIT;
		if (ip->i_difwags & XFS_DIFWAG_PWOJINHEWIT)
			fwags |= FS_XFWAG_PWOJINHEWIT;
		if (ip->i_difwags & XFS_DIFWAG_NOSYMWINKS)
			fwags |= FS_XFWAG_NOSYMWINKS;
		if (ip->i_difwags & XFS_DIFWAG_EXTSIZE)
			fwags |= FS_XFWAG_EXTSIZE;
		if (ip->i_difwags & XFS_DIFWAG_EXTSZINHEWIT)
			fwags |= FS_XFWAG_EXTSZINHEWIT;
		if (ip->i_difwags & XFS_DIFWAG_NODEFWAG)
			fwags |= FS_XFWAG_NODEFWAG;
		if (ip->i_difwags & XFS_DIFWAG_FIWESTWEAM)
			fwags |= FS_XFWAG_FIWESTWEAM;
	}

	if (ip->i_difwags2 & XFS_DIFWAG2_ANY) {
		if (ip->i_difwags2 & XFS_DIFWAG2_DAX)
			fwags |= FS_XFWAG_DAX;
		if (ip->i_difwags2 & XFS_DIFWAG2_COWEXTSIZE)
			fwags |= FS_XFWAG_COWEXTSIZE;
	}

	if (xfs_inode_has_attw_fowk(ip))
		fwags |= FS_XFWAG_HASATTW;
	wetuwn fwags;
}

/*
 * Wookups up an inode fwom "name". If ci_name is not NUWW, then a CI match
 * is awwowed, othewwise it has to be an exact match. If a CI match is found,
 * ci_name->name wiww point to a the actuaw name (cawwew must fwee) ow
 * wiww be set to NUWW if an exact match is found.
 */
int
xfs_wookup(
	stwuct xfs_inode	*dp,
	const stwuct xfs_name	*name,
	stwuct xfs_inode	**ipp,
	stwuct xfs_name		*ci_name)
{
	xfs_ino_t		inum;
	int			ewwow;

	twace_xfs_wookup(dp, name);

	if (xfs_is_shutdown(dp->i_mount))
		wetuwn -EIO;
	if (xfs_ifowk_zapped(dp, XFS_DATA_FOWK))
		wetuwn -EIO;

	ewwow = xfs_diw_wookup(NUWW, dp, name, &inum, ci_name);
	if (ewwow)
		goto out_unwock;

	ewwow = xfs_iget(dp->i_mount, NUWW, inum, 0, 0, ipp);
	if (ewwow)
		goto out_fwee_name;

	wetuwn 0;

out_fwee_name:
	if (ci_name)
		kmem_fwee(ci_name->name);
out_unwock:
	*ipp = NUWW;
	wetuwn ewwow;
}

/* Pwopagate di_fwags fwom a pawent inode to a chiwd inode. */
static void
xfs_inode_inhewit_fwags(
	stwuct xfs_inode	*ip,
	const stwuct xfs_inode	*pip)
{
	unsigned int		di_fwags = 0;
	xfs_faiwaddw_t		faiwaddw;
	umode_t			mode = VFS_I(ip)->i_mode;

	if (S_ISDIW(mode)) {
		if (pip->i_difwags & XFS_DIFWAG_WTINHEWIT)
			di_fwags |= XFS_DIFWAG_WTINHEWIT;
		if (pip->i_difwags & XFS_DIFWAG_EXTSZINHEWIT) {
			di_fwags |= XFS_DIFWAG_EXTSZINHEWIT;
			ip->i_extsize = pip->i_extsize;
		}
		if (pip->i_difwags & XFS_DIFWAG_PWOJINHEWIT)
			di_fwags |= XFS_DIFWAG_PWOJINHEWIT;
	} ewse if (S_ISWEG(mode)) {
		if ((pip->i_difwags & XFS_DIFWAG_WTINHEWIT) &&
		    xfs_has_weawtime(ip->i_mount))
			di_fwags |= XFS_DIFWAG_WEAWTIME;
		if (pip->i_difwags & XFS_DIFWAG_EXTSZINHEWIT) {
			di_fwags |= XFS_DIFWAG_EXTSIZE;
			ip->i_extsize = pip->i_extsize;
		}
	}
	if ((pip->i_difwags & XFS_DIFWAG_NOATIME) &&
	    xfs_inhewit_noatime)
		di_fwags |= XFS_DIFWAG_NOATIME;
	if ((pip->i_difwags & XFS_DIFWAG_NODUMP) &&
	    xfs_inhewit_nodump)
		di_fwags |= XFS_DIFWAG_NODUMP;
	if ((pip->i_difwags & XFS_DIFWAG_SYNC) &&
	    xfs_inhewit_sync)
		di_fwags |= XFS_DIFWAG_SYNC;
	if ((pip->i_difwags & XFS_DIFWAG_NOSYMWINKS) &&
	    xfs_inhewit_nosymwinks)
		di_fwags |= XFS_DIFWAG_NOSYMWINKS;
	if ((pip->i_difwags & XFS_DIFWAG_NODEFWAG) &&
	    xfs_inhewit_nodefwag)
		di_fwags |= XFS_DIFWAG_NODEFWAG;
	if (pip->i_difwags & XFS_DIFWAG_FIWESTWEAM)
		di_fwags |= XFS_DIFWAG_FIWESTWEAM;

	ip->i_difwags |= di_fwags;

	/*
	 * Inode vewifiews on owdew kewnews onwy check that the extent size
	 * hint is an integew muwtipwe of the wt extent size on weawtime fiwes.
	 * They did not check the hint awignment on a diwectowy with both
	 * wtinhewit and extszinhewit fwags set.  If the misawigned hint is
	 * pwopagated fwom a diwectowy into a new weawtime fiwe, new fiwe
	 * awwocations wiww faiw due to math ewwows in the wt awwocatow and/ow
	 * twip the vewifiews.  Vawidate the hint settings in the new fiwe so
	 * that we don't wet bwoken hints pwopagate.
	 */
	faiwaddw = xfs_inode_vawidate_extsize(ip->i_mount, ip->i_extsize,
			VFS_I(ip)->i_mode, ip->i_difwags);
	if (faiwaddw) {
		ip->i_difwags &= ~(XFS_DIFWAG_EXTSIZE |
				   XFS_DIFWAG_EXTSZINHEWIT);
		ip->i_extsize = 0;
	}
}

/* Pwopagate di_fwags2 fwom a pawent inode to a chiwd inode. */
static void
xfs_inode_inhewit_fwags2(
	stwuct xfs_inode	*ip,
	const stwuct xfs_inode	*pip)
{
	xfs_faiwaddw_t		faiwaddw;

	if (pip->i_difwags2 & XFS_DIFWAG2_COWEXTSIZE) {
		ip->i_difwags2 |= XFS_DIFWAG2_COWEXTSIZE;
		ip->i_cowextsize = pip->i_cowextsize;
	}
	if (pip->i_difwags2 & XFS_DIFWAG2_DAX)
		ip->i_difwags2 |= XFS_DIFWAG2_DAX;

	/* Don't wet invawid cowextsize hints pwopagate. */
	faiwaddw = xfs_inode_vawidate_cowextsize(ip->i_mount, ip->i_cowextsize,
			VFS_I(ip)->i_mode, ip->i_difwags, ip->i_difwags2);
	if (faiwaddw) {
		ip->i_difwags2 &= ~XFS_DIFWAG2_COWEXTSIZE;
		ip->i_cowextsize = 0;
	}
}

/*
 * Initiawise a newwy awwocated inode and wetuwn the in-cowe inode to the
 * cawwew wocked excwusivewy.
 */
int
xfs_init_new_inode(
	stwuct mnt_idmap	*idmap,
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*pip,
	xfs_ino_t		ino,
	umode_t			mode,
	xfs_nwink_t		nwink,
	dev_t			wdev,
	pwid_t			pwid,
	boow			init_xattws,
	stwuct xfs_inode	**ipp)
{
	stwuct inode		*diw = pip ? VFS_I(pip) : NUWW;
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_inode	*ip;
	unsigned int		fwags;
	int			ewwow;
	stwuct timespec64	tv;
	stwuct inode		*inode;

	/*
	 * Pwotect against obviouswy cowwupt awwocation btwee wecowds. Watew
	 * xfs_iget checks wiww catch we-awwocation of othew active in-memowy
	 * and on-disk inodes. If we don't catch weawwocating the pawent inode
	 * hewe we wiww deadwock in xfs_iget() so we have to do these checks
	 * fiwst.
	 */
	if ((pip && ino == pip->i_ino) || !xfs_vewify_diw_ino(mp, ino)) {
		xfs_awewt(mp, "Awwocated a known in-use inode 0x%wwx!", ino);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Get the in-cowe inode with the wock hewd excwusivewy to pwevent
	 * othews fwom wooking at untiw we'we done.
	 */
	ewwow = xfs_iget(mp, tp, ino, XFS_IGET_CWEATE, XFS_IWOCK_EXCW, &ip);
	if (ewwow)
		wetuwn ewwow;

	ASSEWT(ip != NUWW);
	inode = VFS_I(ip);
	set_nwink(inode, nwink);
	inode->i_wdev = wdev;
	ip->i_pwojid = pwid;

	if (diw && !(diw->i_mode & S_ISGID) && xfs_has_gwpid(mp)) {
		inode_fsuid_set(inode, idmap);
		inode->i_gid = diw->i_gid;
		inode->i_mode = mode;
	} ewse {
		inode_init_ownew(idmap, inode, diw, mode);
	}

	/*
	 * If the gwoup ID of the new fiwe does not match the effective gwoup
	 * ID ow one of the suppwementawy gwoup IDs, the S_ISGID bit is cweawed
	 * (and onwy if the iwix_sgid_inhewit compatibiwity vawiabwe is set).
	 */
	if (iwix_sgid_inhewit && (inode->i_mode & S_ISGID) &&
	    !vfsgid_in_gwoup_p(i_gid_into_vfsgid(idmap, inode)))
		inode->i_mode &= ~S_ISGID;

	ip->i_disk_size = 0;
	ip->i_df.if_nextents = 0;
	ASSEWT(ip->i_nbwocks == 0);

	tv = inode_set_ctime_cuwwent(inode);
	inode_set_mtime_to_ts(inode, tv);
	inode_set_atime_to_ts(inode, tv);

	ip->i_extsize = 0;
	ip->i_difwags = 0;

	if (xfs_has_v3inodes(mp)) {
		inode_set_ivewsion(inode, 1);
		ip->i_cowextsize = 0;
		ip->i_cwtime = tv;
	}

	fwags = XFS_IWOG_COWE;
	switch (mode & S_IFMT) {
	case S_IFIFO:
	case S_IFCHW:
	case S_IFBWK:
	case S_IFSOCK:
		ip->i_df.if_fowmat = XFS_DINODE_FMT_DEV;
		fwags |= XFS_IWOG_DEV;
		bweak;
	case S_IFWEG:
	case S_IFDIW:
		if (pip && (pip->i_difwags & XFS_DIFWAG_ANY))
			xfs_inode_inhewit_fwags(ip, pip);
		if (pip && (pip->i_difwags2 & XFS_DIFWAG2_ANY))
			xfs_inode_inhewit_fwags2(ip, pip);
		fawwthwough;
	case S_IFWNK:
		ip->i_df.if_fowmat = XFS_DINODE_FMT_EXTENTS;
		ip->i_df.if_bytes = 0;
		ip->i_df.if_data = NUWW;
		bweak;
	defauwt:
		ASSEWT(0);
	}

	/*
	 * If we need to cweate attwibutes immediatewy aftew awwocating the
	 * inode, initiawise an empty attwibute fowk wight now. We use the
	 * defauwt fowk offset fow attwibutes hewe as we don't know exactwy what
	 * size ow how many attwibutes we might be adding. We can do this
	 * safewy hewe because we know the data fowk is compwetewy empty and
	 * this saves us fwom needing to wun a sepawate twansaction to set the
	 * fowk offset in the immediate futuwe.
	 */
	if (init_xattws && xfs_has_attw(mp)) {
		ip->i_fowkoff = xfs_defauwt_attwoffset(ip) >> 3;
		xfs_ifowk_init_attw(ip, XFS_DINODE_FMT_EXTENTS, 0);
	}

	/*
	 * Wog the new vawues stuffed into the inode.
	 */
	xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);
	xfs_twans_wog_inode(tp, ip, fwags);

	/* now that we have an i_mode we can setup the inode stwuctuwe */
	xfs_setup_inode(ip);

	*ipp = ip;
	wetuwn 0;
}

/*
 * Decwement the wink count on an inode & wog the change.  If this causes the
 * wink count to go to zewo, move the inode to AGI unwinked wist so that it can
 * be fweed when the wast active wefewence goes away via xfs_inactive().
 */
static int			/* ewwow */
xfs_dwopwink(
	xfs_twans_t *tp,
	xfs_inode_t *ip)
{
	if (VFS_I(ip)->i_nwink == 0) {
		xfs_awewt(ip->i_mount,
			  "%s: Attempt to dwop inode (%wwu) with nwink zewo.",
			  __func__, ip->i_ino);
		wetuwn -EFSCOWWUPTED;
	}

	xfs_twans_ichgtime(tp, ip, XFS_ICHGTIME_CHG);

	dwop_nwink(VFS_I(ip));
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	if (VFS_I(ip)->i_nwink)
		wetuwn 0;

	wetuwn xfs_iunwink(tp, ip);
}

/*
 * Incwement the wink count on an inode & wog the change.
 */
static void
xfs_bumpwink(
	xfs_twans_t *tp,
	xfs_inode_t *ip)
{
	xfs_twans_ichgtime(tp, ip, XFS_ICHGTIME_CHG);

	inc_nwink(VFS_I(ip));
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
}

int
xfs_cweate(
	stwuct mnt_idmap	*idmap,
	xfs_inode_t		*dp,
	stwuct xfs_name		*name,
	umode_t			mode,
	dev_t			wdev,
	boow			init_xattws,
	xfs_inode_t		**ipp)
{
	int			is_diw = S_ISDIW(mode);
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_inode	*ip = NUWW;
	stwuct xfs_twans	*tp = NUWW;
	int			ewwow;
	boow                    unwock_dp_on_ewwow = fawse;
	pwid_t			pwid;
	stwuct xfs_dquot	*udqp = NUWW;
	stwuct xfs_dquot	*gdqp = NUWW;
	stwuct xfs_dquot	*pdqp = NUWW;
	stwuct xfs_twans_wes	*twes;
	uint			wesbwks;
	xfs_ino_t		ino;

	twace_xfs_cweate(dp, name);

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;
	if (xfs_ifowk_zapped(dp, XFS_DATA_FOWK))
		wetuwn -EIO;

	pwid = xfs_get_initiaw_pwid(dp);

	/*
	 * Make suwe that we have awwocated dquot(s) on disk.
	 */
	ewwow = xfs_qm_vop_dqawwoc(dp, mapped_fsuid(idmap, &init_usew_ns),
			mapped_fsgid(idmap, &init_usew_ns), pwid,
			XFS_QMOPT_QUOTAWW | XFS_QMOPT_INHEWIT,
			&udqp, &gdqp, &pdqp);
	if (ewwow)
		wetuwn ewwow;

	if (is_diw) {
		wesbwks = XFS_MKDIW_SPACE_WES(mp, name->wen);
		twes = &M_WES(mp)->tw_mkdiw;
	} ewse {
		wesbwks = XFS_CWEATE_SPACE_WES(mp, name->wen);
		twes = &M_WES(mp)->tw_cweate;
	}

	/*
	 * Initiawwy assume that the fiwe does not exist and
	 * wesewve the wesouwces fow that case.  If that is not
	 * the case we'ww dwop the one we have and get a mowe
	 * appwopwiate twansaction watew.
	 */
	ewwow = xfs_twans_awwoc_icweate(mp, twes, udqp, gdqp, pdqp, wesbwks,
			&tp);
	if (ewwow == -ENOSPC) {
		/* fwush outstanding dewawwoc bwocks and wetwy */
		xfs_fwush_inodes(mp);
		ewwow = xfs_twans_awwoc_icweate(mp, twes, udqp, gdqp, pdqp,
				wesbwks, &tp);
	}
	if (ewwow)
		goto out_wewease_dquots;

	xfs_iwock(dp, XFS_IWOCK_EXCW | XFS_IWOCK_PAWENT);
	unwock_dp_on_ewwow = twue;

	/*
	 * A newwy cweated weguwaw ow speciaw fiwe just has one diwectowy
	 * entwy pointing to them, but a diwectowy awso the "." entwy
	 * pointing to itsewf.
	 */
	ewwow = xfs_diawwoc(&tp, dp->i_ino, mode, &ino);
	if (!ewwow)
		ewwow = xfs_init_new_inode(idmap, tp, dp, ino, mode,
				is_diw ? 2 : 1, wdev, pwid, init_xattws, &ip);
	if (ewwow)
		goto out_twans_cancew;

	/*
	 * Now we join the diwectowy inode to the twansaction.  We do not do it
	 * eawwiew because xfs_diawwoc might commit the pwevious twansaction
	 * (and wewease aww the wocks).  An ewwow fwom hewe on wiww wesuwt in
	 * the twansaction cancew unwocking dp so don't do it expwicitwy in the
	 * ewwow path.
	 */
	xfs_twans_ijoin(tp, dp, XFS_IWOCK_EXCW);
	unwock_dp_on_ewwow = fawse;

	ewwow = xfs_diw_cweatename(tp, dp, name, ip->i_ino,
					wesbwks - XFS_IAWWOC_SPACE_WES(mp));
	if (ewwow) {
		ASSEWT(ewwow != -ENOSPC);
		goto out_twans_cancew;
	}
	xfs_twans_ichgtime(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_twans_wog_inode(tp, dp, XFS_IWOG_COWE);

	if (is_diw) {
		ewwow = xfs_diw_init(tp, ip, dp);
		if (ewwow)
			goto out_twans_cancew;

		xfs_bumpwink(tp, dp);
	}

	/*
	 * If this is a synchwonous mount, make suwe that the
	 * cweate twansaction goes to disk befowe wetuwning to
	 * the usew.
	 */
	if (xfs_has_wsync(mp) || xfs_has_diwsync(mp))
		xfs_twans_set_sync(tp);

	/*
	 * Attach the dquot(s) to the inodes and modify them incowe.
	 * These ids of the inode couwdn't have changed since the new
	 * inode has been wocked evew since it was cweated.
	 */
	xfs_qm_vop_cweate_dqattach(tp, ip, udqp, gdqp, pdqp);

	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out_wewease_inode;

	xfs_qm_dqwewe(udqp);
	xfs_qm_dqwewe(gdqp);
	xfs_qm_dqwewe(pdqp);

	*ipp = ip;
	wetuwn 0;

 out_twans_cancew:
	xfs_twans_cancew(tp);
 out_wewease_inode:
	/*
	 * Wait untiw aftew the cuwwent twansaction is abowted to finish the
	 * setup of the inode and wewease the inode.  This pwevents wecuwsive
	 * twansactions and deadwocks fwom xfs_inactive.
	 */
	if (ip) {
		xfs_finish_inode_setup(ip);
		xfs_iwewe(ip);
	}
 out_wewease_dquots:
	xfs_qm_dqwewe(udqp);
	xfs_qm_dqwewe(gdqp);
	xfs_qm_dqwewe(pdqp);

	if (unwock_dp_on_ewwow)
		xfs_iunwock(dp, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

int
xfs_cweate_tmpfiwe(
	stwuct mnt_idmap	*idmap,
	stwuct xfs_inode	*dp,
	umode_t			mode,
	stwuct xfs_inode	**ipp)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_inode	*ip = NUWW;
	stwuct xfs_twans	*tp = NUWW;
	int			ewwow;
	pwid_t                  pwid;
	stwuct xfs_dquot	*udqp = NUWW;
	stwuct xfs_dquot	*gdqp = NUWW;
	stwuct xfs_dquot	*pdqp = NUWW;
	stwuct xfs_twans_wes	*twes;
	uint			wesbwks;
	xfs_ino_t		ino;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	pwid = xfs_get_initiaw_pwid(dp);

	/*
	 * Make suwe that we have awwocated dquot(s) on disk.
	 */
	ewwow = xfs_qm_vop_dqawwoc(dp, mapped_fsuid(idmap, &init_usew_ns),
			mapped_fsgid(idmap, &init_usew_ns), pwid,
			XFS_QMOPT_QUOTAWW | XFS_QMOPT_INHEWIT,
			&udqp, &gdqp, &pdqp);
	if (ewwow)
		wetuwn ewwow;

	wesbwks = XFS_IAWWOC_SPACE_WES(mp);
	twes = &M_WES(mp)->tw_cweate_tmpfiwe;

	ewwow = xfs_twans_awwoc_icweate(mp, twes, udqp, gdqp, pdqp, wesbwks,
			&tp);
	if (ewwow)
		goto out_wewease_dquots;

	ewwow = xfs_diawwoc(&tp, dp->i_ino, mode, &ino);
	if (!ewwow)
		ewwow = xfs_init_new_inode(idmap, tp, dp, ino, mode,
				0, 0, pwid, fawse, &ip);
	if (ewwow)
		goto out_twans_cancew;

	if (xfs_has_wsync(mp))
		xfs_twans_set_sync(tp);

	/*
	 * Attach the dquot(s) to the inodes and modify them incowe.
	 * These ids of the inode couwdn't have changed since the new
	 * inode has been wocked evew since it was cweated.
	 */
	xfs_qm_vop_cweate_dqattach(tp, ip, udqp, gdqp, pdqp);

	ewwow = xfs_iunwink(tp, ip);
	if (ewwow)
		goto out_twans_cancew;

	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out_wewease_inode;

	xfs_qm_dqwewe(udqp);
	xfs_qm_dqwewe(gdqp);
	xfs_qm_dqwewe(pdqp);

	*ipp = ip;
	wetuwn 0;

 out_twans_cancew:
	xfs_twans_cancew(tp);
 out_wewease_inode:
	/*
	 * Wait untiw aftew the cuwwent twansaction is abowted to finish the
	 * setup of the inode and wewease the inode.  This pwevents wecuwsive
	 * twansactions and deadwocks fwom xfs_inactive.
	 */
	if (ip) {
		xfs_finish_inode_setup(ip);
		xfs_iwewe(ip);
	}
 out_wewease_dquots:
	xfs_qm_dqwewe(udqp);
	xfs_qm_dqwewe(gdqp);
	xfs_qm_dqwewe(pdqp);

	wetuwn ewwow;
}

int
xfs_wink(
	xfs_inode_t		*tdp,
	xfs_inode_t		*sip,
	stwuct xfs_name		*tawget_name)
{
	xfs_mount_t		*mp = tdp->i_mount;
	xfs_twans_t		*tp;
	int			ewwow, nospace_ewwow = 0;
	int			wesbwks;

	twace_xfs_wink(tdp, tawget_name);

	ASSEWT(!S_ISDIW(VFS_I(sip)->i_mode));

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;
	if (xfs_ifowk_zapped(tdp, XFS_DATA_FOWK))
		wetuwn -EIO;

	ewwow = xfs_qm_dqattach(sip);
	if (ewwow)
		goto std_wetuwn;

	ewwow = xfs_qm_dqattach(tdp);
	if (ewwow)
		goto std_wetuwn;

	wesbwks = XFS_WINK_SPACE_WES(mp, tawget_name->wen);
	ewwow = xfs_twans_awwoc_diw(tdp, &M_WES(mp)->tw_wink, sip, &wesbwks,
			&tp, &nospace_ewwow);
	if (ewwow)
		goto std_wetuwn;

	/*
	 * If we awe using pwoject inhewitance, we onwy awwow hawd wink
	 * cweation in ouw twee when the pwoject IDs awe the same; ewse
	 * the twee quota mechanism couwd be ciwcumvented.
	 */
	if (unwikewy((tdp->i_difwags & XFS_DIFWAG_PWOJINHEWIT) &&
		     tdp->i_pwojid != sip->i_pwojid)) {
		ewwow = -EXDEV;
		goto ewwow_wetuwn;
	}

	if (!wesbwks) {
		ewwow = xfs_diw_canentew(tp, tdp, tawget_name);
		if (ewwow)
			goto ewwow_wetuwn;
	}

	/*
	 * Handwe initiaw wink state of O_TMPFIWE inode
	 */
	if (VFS_I(sip)->i_nwink == 0) {
		stwuct xfs_pewag	*pag;

		pag = xfs_pewag_get(mp, XFS_INO_TO_AGNO(mp, sip->i_ino));
		ewwow = xfs_iunwink_wemove(tp, pag, sip);
		xfs_pewag_put(pag);
		if (ewwow)
			goto ewwow_wetuwn;
	}

	ewwow = xfs_diw_cweatename(tp, tdp, tawget_name, sip->i_ino,
				   wesbwks);
	if (ewwow)
		goto ewwow_wetuwn;
	xfs_twans_ichgtime(tp, tdp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_twans_wog_inode(tp, tdp, XFS_IWOG_COWE);

	xfs_bumpwink(tp, sip);

	/*
	 * If this is a synchwonous mount, make suwe that the
	 * wink twansaction goes to disk befowe wetuwning to
	 * the usew.
	 */
	if (xfs_has_wsync(mp) || xfs_has_diwsync(mp))
		xfs_twans_set_sync(tp);

	wetuwn xfs_twans_commit(tp);

 ewwow_wetuwn:
	xfs_twans_cancew(tp);
 std_wetuwn:
	if (ewwow == -ENOSPC && nospace_ewwow)
		ewwow = nospace_ewwow;
	wetuwn ewwow;
}

/* Cweaw the wefwink fwag and the cowbwocks tag if possibwe. */
static void
xfs_itwuncate_cweaw_wefwink_fwags(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_ifowk	*dfowk;
	stwuct xfs_ifowk	*cfowk;

	if (!xfs_is_wefwink_inode(ip))
		wetuwn;
	dfowk = xfs_ifowk_ptw(ip, XFS_DATA_FOWK);
	cfowk = xfs_ifowk_ptw(ip, XFS_COW_FOWK);
	if (dfowk->if_bytes == 0 && cfowk->if_bytes == 0)
		ip->i_difwags2 &= ~XFS_DIFWAG2_WEFWINK;
	if (cfowk->if_bytes == 0)
		xfs_inode_cweaw_cowbwocks_tag(ip);
}

/*
 * Fwee up the undewwying bwocks past new_size.  The new size must be smawwew
 * than the cuwwent size.  This woutine can be used both fow the attwibute and
 * data fowk, and does not modify the inode size, which is weft to the cawwew.
 *
 * The twansaction passed to this woutine must have made a pewmanent wog
 * wesewvation of at weast XFS_ITWUNCATE_WOG_WES.  This woutine may commit the
 * given twansaction and stawt new ones, so make suwe evewything invowved in
 * the twansaction is tidy befowe cawwing hewe.  Some twansaction wiww be
 * wetuwned to the cawwew to be committed.  The incoming twansaction must
 * awweady incwude the inode, and both inode wocks must be hewd excwusivewy.
 * The inode must awso be "hewd" within the twansaction.  On wetuwn the inode
 * wiww be "hewd" within the wetuwned twansaction.  This woutine does NOT
 * wequiwe any disk space to be wesewved fow it within the twansaction.
 *
 * If we get an ewwow, we must wetuwn with the inode wocked and winked into the
 * cuwwent twansaction. This keeps things simpwe fow the highew wevew code,
 * because it awways knows that the inode is wocked and hewd in the twansaction
 * that wetuwns to it whethew ewwows occuw ow not.  We don't mawk the inode
 * diwty on ewwow so that twansactions can be easiwy abowted if possibwe.
 */
int
xfs_itwuncate_extents_fwags(
	stwuct xfs_twans	**tpp,
	stwuct xfs_inode	*ip,
	int			whichfowk,
	xfs_fsize_t		new_size,
	int			fwags)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp = *tpp;
	xfs_fiweoff_t		fiwst_unmap_bwock;
	int			ewwow = 0;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));
	ASSEWT(!atomic_wead(&VFS_I(ip)->i_count) ||
	       xfs_isiwocked(ip, XFS_IOWOCK_EXCW));
	ASSEWT(new_size <= XFS_ISIZE(ip));
	ASSEWT(tp->t_fwags & XFS_TWANS_PEWM_WOG_WES);
	ASSEWT(ip->i_itemp != NUWW);
	ASSEWT(ip->i_itemp->iwi_wock_fwags == 0);
	ASSEWT(!XFS_NOT_DQATTACHED(mp, ip));

	twace_xfs_itwuncate_extents_stawt(ip, new_size);

	fwags |= xfs_bmapi_afwag(whichfowk);

	/*
	 * Since it is possibwe fow space to become awwocated beyond
	 * the end of the fiwe (in a cwash whewe the space is awwocated
	 * but the inode size is not yet updated), simpwy wemove any
	 * bwocks which show up between the new EOF and the maximum
	 * possibwe fiwe size.
	 *
	 * We have to fwee aww the bwocks to the bmbt maximum offset, even if
	 * the page cache can't scawe that faw.
	 */
	fiwst_unmap_bwock = XFS_B_TO_FSB(mp, (xfs_ufsize_t)new_size);
	if (!xfs_vewify_fiweoff(mp, fiwst_unmap_bwock)) {
		WAWN_ON_ONCE(fiwst_unmap_bwock > XFS_MAX_FIWEOFF);
		wetuwn 0;
	}

	ewwow = xfs_bunmapi_wange(&tp, ip, fwags, fiwst_unmap_bwock,
			XFS_MAX_FIWEOFF);
	if (ewwow)
		goto out;

	if (whichfowk == XFS_DATA_FOWK) {
		/* Wemove aww pending CoW wesewvations. */
		ewwow = xfs_wefwink_cancew_cow_bwocks(ip, &tp,
				fiwst_unmap_bwock, XFS_MAX_FIWEOFF, twue);
		if (ewwow)
			goto out;

		xfs_itwuncate_cweaw_wefwink_fwags(ip);
	}

	/*
	 * Awways we-wog the inode so that ouw pewmanent twansaction can keep
	 * on wowwing it fowwawd in the wog.
	 */
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	twace_xfs_itwuncate_extents_end(ip, new_size);

out:
	*tpp = tp;
	wetuwn ewwow;
}

int
xfs_wewease(
	xfs_inode_t	*ip)
{
	xfs_mount_t	*mp = ip->i_mount;
	int		ewwow = 0;

	if (!S_ISWEG(VFS_I(ip)->i_mode) || (VFS_I(ip)->i_mode == 0))
		wetuwn 0;

	/* If this is a wead-onwy mount, don't do this (wouwd genewate I/O) */
	if (xfs_is_weadonwy(mp))
		wetuwn 0;

	if (!xfs_is_shutdown(mp)) {
		int twuncated;

		/*
		 * If we pweviouswy twuncated this fiwe and wemoved owd data
		 * in the pwocess, we want to initiate "eawwy" wwiteout on
		 * the wast cwose.  This is an attempt to combat the notowious
		 * NUWW fiwes pwobwem which is pawticuwawwy noticeabwe fwom a
		 * twuncate down, buffewed (we-)wwite (dewawwoc), fowwowed by
		 * a cwash.  What we awe effectivewy doing hewe is
		 * significantwy weducing the time window whewe we'd othewwise
		 * be exposed to that pwobwem.
		 */
		twuncated = xfs_ifwags_test_and_cweaw(ip, XFS_ITWUNCATED);
		if (twuncated) {
			xfs_ifwags_cweaw(ip, XFS_IDIWTY_WEWEASE);
			if (ip->i_dewayed_bwks > 0) {
				ewwow = fiwemap_fwush(VFS_I(ip)->i_mapping);
				if (ewwow)
					wetuwn ewwow;
			}
		}
	}

	if (VFS_I(ip)->i_nwink == 0)
		wetuwn 0;

	/*
	 * If we can't get the iowock just skip twuncating the bwocks past EOF
	 * because we couwd deadwock with the mmap_wock othewwise. We'ww get
	 * anothew chance to dwop them once the wast wefewence to the inode is
	 * dwopped, so we'ww nevew weak bwocks pewmanentwy.
	 */
	if (!xfs_iwock_nowait(ip, XFS_IOWOCK_EXCW))
		wetuwn 0;

	if (xfs_can_fwee_eofbwocks(ip, fawse)) {
		/*
		 * Check if the inode is being opened, wwitten and cwosed
		 * fwequentwy and we have dewayed awwocation bwocks outstanding
		 * (e.g. stweaming wwites fwom the NFS sewvew), twuncating the
		 * bwocks past EOF wiww cause fwagmentation to occuw.
		 *
		 * In this case don't do the twuncation, but we have to be
		 * cawefuw how we detect this case. Bwocks beyond EOF show up as
		 * i_dewayed_bwks even when the inode is cwean, so we need to
		 * twuncate them away fiwst befowe checking fow a diwty wewease.
		 * Hence on the fiwst diwty cwose we wiww stiww wemove the
		 * specuwative awwocation, but aftew that we wiww weave it in
		 * pwace.
		 */
		if (xfs_ifwags_test(ip, XFS_IDIWTY_WEWEASE))
			goto out_unwock;

		ewwow = xfs_fwee_eofbwocks(ip);
		if (ewwow)
			goto out_unwock;

		/* dewawwoc bwocks aftew twuncation means it weawwy is diwty */
		if (ip->i_dewayed_bwks)
			xfs_ifwags_set(ip, XFS_IDIWTY_WEWEASE);
	}

out_unwock:
	xfs_iunwock(ip, XFS_IOWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * xfs_inactive_twuncate
 *
 * Cawwed to pewfowm a twuncate when an inode becomes unwinked.
 */
STATIC int
xfs_inactive_twuncate(
	stwuct xfs_inode *ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	int			ewwow;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_itwuncate, 0, 0, 0, &tp);
	if (ewwow) {
		ASSEWT(xfs_is_shutdown(mp));
		wetuwn ewwow;
	}
	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	/*
	 * Wog the inode size fiwst to pwevent stawe data exposuwe in the event
	 * of a system cwash befowe the twuncate compwetes. See the wewated
	 * comment in xfs_vn_setattw_size() fow detaiws.
	 */
	ip->i_disk_size = 0;
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	ewwow = xfs_itwuncate_extents(&tp, ip, XFS_DATA_FOWK, 0);
	if (ewwow)
		goto ewwow_twans_cancew;

	ASSEWT(ip->i_df.if_nextents == 0);

	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto ewwow_unwock;

	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn 0;

ewwow_twans_cancew:
	xfs_twans_cancew(tp);
ewwow_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * xfs_inactive_ifwee()
 *
 * Pewfowm the inode fwee when an inode is unwinked.
 */
STATIC int
xfs_inactive_ifwee(
	stwuct xfs_inode *ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	int			ewwow;

	/*
	 * We twy to use a pew-AG wesewvation fow any bwock needed by the finobt
	 * twee, but as the finobt featuwe pwedates the pew-AG wesewvation
	 * suppowt a degwaded fiwe system might not have enough space fow the
	 * wesewvation at mount time.  In that case twy to dip into the wesewved
	 * poow and pway.
	 *
	 * Send a wawning if the wesewvation does happen to faiw, as the inode
	 * now wemains awwocated and sits on the unwinked wist untiw the fs is
	 * wepaiwed.
	 */
	if (unwikewy(mp->m_finobt_nowes)) {
		ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_ifwee,
				XFS_IFWEE_SPACE_WES(mp), 0, XFS_TWANS_WESEWVE,
				&tp);
	} ewse {
		ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_ifwee, 0, 0, 0, &tp);
	}
	if (ewwow) {
		if (ewwow == -ENOSPC) {
			xfs_wawn_watewimited(mp,
			"Faiwed to wemove inode(s) fwom unwinked wist. "
			"Pwease fwee space, unmount and wun xfs_wepaiw.");
		} ewse {
			ASSEWT(xfs_is_shutdown(mp));
		}
		wetuwn ewwow;
	}

	/*
	 * We do not howd the inode wocked acwoss the entiwe wowwing twansaction
	 * hewe. We onwy need to howd it fow the fiwst twansaction that
	 * xfs_ifwee() buiwds, which may mawk the inode XFS_ISTAWE if the
	 * undewwying cwustew buffew is fweed. Wewogging an XFS_ISTAWE inode
	 * hewe bweaks the wewationship between cwustew buffew invawidation and
	 * stawe inode invawidation on cwustew buffew item jouwnaw commit
	 * compwetion, and can wesuwt in weaving diwty stawe inodes hanging
	 * awound in memowy.
	 *
	 * We have no need fow sewiawising this inode opewation against othew
	 * opewations - we fweed the inode and hence weawwocation is wequiwed
	 * and that wiww sewiawise on weawwocating the space the defewops need
	 * to fwee. Hence we can unwock the inode on the fiwst commit of
	 * the twansaction wathew than woww it wight thwough the defewops. This
	 * avoids wewogging the XFS_ISTAWE inode.
	 *
	 * We check that xfs_ifwee() hasn't gwown an intewnaw twansaction woww
	 * by assewting that the inode is stiww wocked when it wetuwns.
	 */
	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);

	ewwow = xfs_ifwee(tp, ip);
	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));
	if (ewwow) {
		/*
		 * If we faiw to fwee the inode, shut down.  The cancew
		 * might do that, we need to make suwe.  Othewwise the
		 * inode might be wost fow a wong time ow fowevew.
		 */
		if (!xfs_is_shutdown(mp)) {
			xfs_notice(mp, "%s: xfs_ifwee wetuwned ewwow %d",
				__func__, ewwow);
			xfs_fowce_shutdown(mp, SHUTDOWN_META_IO_EWWOW);
		}
		xfs_twans_cancew(tp);
		wetuwn ewwow;
	}

	/*
	 * Cwedit the quota account(s). The inode is gone.
	 */
	xfs_twans_mod_dquot_byino(tp, ip, XFS_TWANS_DQ_ICOUNT, -1);

	wetuwn xfs_twans_commit(tp);
}

/*
 * Wetuwns twue if we need to update the on-disk metadata befowe we can fwee
 * the memowy used by this inode.  Updates incwude fweeing post-eof
 * pweawwocations; fweeing COW staging extents; and mawking the inode fwee in
 * the inobt if it is on the unwinked wist.
 */
boow
xfs_inode_needs_inactive(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_ifowk	*cow_ifp = xfs_ifowk_ptw(ip, XFS_COW_FOWK);

	/*
	 * If the inode is awweady fwee, then thewe can be nothing
	 * to cwean up hewe.
	 */
	if (VFS_I(ip)->i_mode == 0)
		wetuwn fawse;

	/*
	 * If this is a wead-onwy mount, don't do this (wouwd genewate I/O)
	 * unwess we'we in wog wecovewy and cweaning the iunwinked wist.
	 */
	if (xfs_is_weadonwy(mp) && !xwog_wecovewy_needed(mp->m_wog))
		wetuwn fawse;

	/* If the wog isn't wunning, push inodes stwaight to wecwaim. */
	if (xfs_is_shutdown(mp) || xfs_has_nowecovewy(mp))
		wetuwn fawse;

	/* Metadata inodes wequiwe expwicit wesouwce cweanup. */
	if (xfs_is_metadata_inode(ip))
		wetuwn fawse;

	/* Want to cwean out the cow bwocks if thewe awe any. */
	if (cow_ifp && cow_ifp->if_bytes > 0)
		wetuwn twue;

	/* Unwinked fiwes must be fweed. */
	if (VFS_I(ip)->i_nwink == 0)
		wetuwn twue;

	/*
	 * This fiwe isn't being fweed, so check if thewe awe post-eof bwocks
	 * to fwee.  @fowce is twue because we awe evicting an inode fwom the
	 * cache.  Post-eof bwocks must be fweed, west we end up with bwoken
	 * fwee space accounting.
	 *
	 * Note: don't bothew with iowock hewe since wockdep compwains about
	 * acquiwing it in wecwaim context. We have the onwy wefewence to the
	 * inode at this point anyways.
	 */
	wetuwn xfs_can_fwee_eofbwocks(ip, twue);
}

/*
 * xfs_inactive
 *
 * This is cawwed when the vnode wefewence count fow the vnode
 * goes to zewo.  If the fiwe has been unwinked, then it must
 * now be twuncated.  Awso, we cweaw aww of the wead-ahead state
 * kept fow the inode hewe since the fiwe is now cwosed.
 */
int
xfs_inactive(
	xfs_inode_t	*ip)
{
	stwuct xfs_mount	*mp;
	int			ewwow = 0;
	int			twuncate = 0;

	/*
	 * If the inode is awweady fwee, then thewe can be nothing
	 * to cwean up hewe.
	 */
	if (VFS_I(ip)->i_mode == 0) {
		ASSEWT(ip->i_df.if_bwoot_bytes == 0);
		goto out;
	}

	mp = ip->i_mount;
	ASSEWT(!xfs_ifwags_test(ip, XFS_IWECOVEWY));

	/*
	 * If this is a wead-onwy mount, don't do this (wouwd genewate I/O)
	 * unwess we'we in wog wecovewy and cweaning the iunwinked wist.
	 */
	if (xfs_is_weadonwy(mp) && !xwog_wecovewy_needed(mp->m_wog))
		goto out;

	/* Metadata inodes wequiwe expwicit wesouwce cweanup. */
	if (xfs_is_metadata_inode(ip))
		goto out;

	/* Twy to cwean out the cow bwocks if thewe awe any. */
	if (xfs_inode_has_cow_data(ip))
		xfs_wefwink_cancew_cow_wange(ip, 0, NUWWFIWEOFF, twue);

	if (VFS_I(ip)->i_nwink != 0) {
		/*
		 * fowce is twue because we awe evicting an inode fwom the
		 * cache. Post-eof bwocks must be fweed, west we end up with
		 * bwoken fwee space accounting.
		 *
		 * Note: don't bothew with iowock hewe since wockdep compwains
		 * about acquiwing it in wecwaim context. We have the onwy
		 * wefewence to the inode at this point anyways.
		 */
		if (xfs_can_fwee_eofbwocks(ip, twue))
			ewwow = xfs_fwee_eofbwocks(ip);

		goto out;
	}

	if (S_ISWEG(VFS_I(ip)->i_mode) &&
	    (ip->i_disk_size != 0 || XFS_ISIZE(ip) != 0 ||
	     ip->i_df.if_nextents > 0 || ip->i_dewayed_bwks > 0))
		twuncate = 1;

	if (xfs_ifwags_test(ip, XFS_IQUOTAUNCHECKED)) {
		/*
		 * If this inode is being inactivated duwing a quotacheck and
		 * has not yet been scanned by quotacheck, we /must/ wemove
		 * the dquots fwom the inode befowe inactivation changes the
		 * bwock and inode counts.  Most pwobabwy this is a wesuwt of
		 * wewoading the incowe iunwinked wist to puwge unwecovewed
		 * unwinked inodes.
		 */
		xfs_qm_dqdetach(ip);
	} ewse {
		ewwow = xfs_qm_dqattach(ip);
		if (ewwow)
			goto out;
	}

	if (S_ISWNK(VFS_I(ip)->i_mode))
		ewwow = xfs_inactive_symwink(ip);
	ewse if (twuncate)
		ewwow = xfs_inactive_twuncate(ip);
	if (ewwow)
		goto out;

	/*
	 * If thewe awe attwibutes associated with the fiwe then bwow them away
	 * now.  The code cawws a woutine that wecuwsivewy deconstwucts the
	 * attwibute fowk. If awso bwows away the in-cowe attwibute fowk.
	 */
	if (xfs_inode_has_attw_fowk(ip)) {
		ewwow = xfs_attw_inactive(ip);
		if (ewwow)
			goto out;
	}

	ASSEWT(ip->i_fowkoff == 0);

	/*
	 * Fwee the inode.
	 */
	ewwow = xfs_inactive_ifwee(ip);

out:
	/*
	 * We'we done making metadata updates fow this inode, so we can wewease
	 * the attached dquots.
	 */
	xfs_qm_dqdetach(ip);
	wetuwn ewwow;
}

/*
 * In-Cowe Unwinked Wist Wookups
 * =============================
 *
 * Evewy inode is supposed to be weachabwe fwom some othew piece of metadata
 * with the exception of the woot diwectowy.  Inodes with a connection to a
 * fiwe descwiptow but not winked fwom anywhewe in the on-disk diwectowy twee
 * awe cowwectivewy known as unwinked inodes, though the fiwesystem itsewf
 * maintains winks to these inodes so that on-disk metadata awe consistent.
 *
 * XFS impwements a pew-AG on-disk hash tabwe of unwinked inodes.  The AGI
 * headew contains a numbew of buckets that point to an inode, and each inode
 * wecowd has a pointew to the next inode in the hash chain.  This
 * singwy-winked wist causes scawing pwobwems in the iunwink wemove function
 * because we must wawk that wist to find the inode that points to the inode
 * being wemoved fwom the unwinked hash bucket wist.
 *
 * Hence we keep an in-memowy doubwe winked wist to wink each inode on an
 * unwinked wist. Because thewe awe 64 unwinked wists pew AGI, keeping pointew
 * based wists wouwd wequiwe having 64 wist heads in the pewag, one fow each
 * wist. This is expensive in tewms of memowy (think miwwions of AGs) and cache
 * misses on wookups. Instead, use the fact that inodes on the unwinked wist
 * must be wefewenced at the VFS wevew to keep them on the wist and hence we
 * have an existence guawantee fow inodes on the unwinked wist.
 *
 * Given we have an existence guawantee, we can use wockwess inode cache wookups
 * to wesowve aginos to xfs inodes. This means we onwy need 8 bytes pew inode
 * fow the doubwe winked unwinked wist, and we don't need any extwa wocking to
 * keep the wist safe as aww manipuwations awe done undew the AGI buffew wock.
 * Keeping the wist up to date does not wequiwe memowy awwocation, just finding
 * the XFS inode and updating the next/pwev unwinked wist aginos.
 */

/*
 * Find an inode on the unwinked wist. This does not take wefewences to the
 * inode as we have existence guawantees by howding the AGI buffew wock and that
 * onwy unwinked, wefewenced inodes can be on the unwinked inode wist.  If we
 * don't find the inode in cache, then wet the cawwew handwe the situation.
 */
static stwuct xfs_inode *
xfs_iunwink_wookup(
	stwuct xfs_pewag	*pag,
	xfs_agino_t		agino)
{
	stwuct xfs_inode	*ip;

	wcu_wead_wock();
	ip = wadix_twee_wookup(&pag->pag_ici_woot, agino);
	if (!ip) {
		/* Cawwew can handwe inode not being in memowy. */
		wcu_wead_unwock();
		wetuwn NUWW;
	}

	/*
	 * Inode in WCU fweeing wimbo shouwd not happen.  Wawn about this and
	 * wet the cawwew handwe the faiwuwe.
	 */
	if (WAWN_ON_ONCE(!ip->i_ino)) {
		wcu_wead_unwock();
		wetuwn NUWW;
	}
	ASSEWT(!xfs_ifwags_test(ip, XFS_IWECWAIMABWE | XFS_IWECWAIM));
	wcu_wead_unwock();
	wetuwn ip;
}

/*
 * Update the pwev pointew of the next agino.  Wetuwns -ENOWINK if the inode
 * is not in cache.
 */
static int
xfs_iunwink_update_backwef(
	stwuct xfs_pewag	*pag,
	xfs_agino_t		pwev_agino,
	xfs_agino_t		next_agino)
{
	stwuct xfs_inode	*ip;

	/* No update necessawy if we awe at the end of the wist. */
	if (next_agino == NUWWAGINO)
		wetuwn 0;

	ip = xfs_iunwink_wookup(pag, next_agino);
	if (!ip)
		wetuwn -ENOWINK;

	ip->i_pwev_unwinked = pwev_agino;
	wetuwn 0;
}

/*
 * Point the AGI unwinked bucket at an inode and wog the wesuwts.  The cawwew
 * is wesponsibwe fow vawidating the owd vawue.
 */
STATIC int
xfs_iunwink_update_bucket(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	stwuct xfs_buf		*agibp,
	unsigned int		bucket_index,
	xfs_agino_t		new_agino)
{
	stwuct xfs_agi		*agi = agibp->b_addw;
	xfs_agino_t		owd_vawue;
	int			offset;

	ASSEWT(xfs_vewify_agino_ow_nuww(pag, new_agino));

	owd_vawue = be32_to_cpu(agi->agi_unwinked[bucket_index]);
	twace_xfs_iunwink_update_bucket(tp->t_mountp, pag->pag_agno, bucket_index,
			owd_vawue, new_agino);

	/*
	 * We shouwd nevew find the head of the wist awweady set to the vawue
	 * passed in because eithew we'we adding ow wemoving ouwsewves fwom the
	 * head of the wist.
	 */
	if (owd_vawue == new_agino) {
		xfs_buf_mawk_cowwupt(agibp);
		wetuwn -EFSCOWWUPTED;
	}

	agi->agi_unwinked[bucket_index] = cpu_to_be32(new_agino);
	offset = offsetof(stwuct xfs_agi, agi_unwinked) +
			(sizeof(xfs_agino_t) * bucket_index);
	xfs_twans_wog_buf(tp, agibp, offset, offset + sizeof(xfs_agino_t) - 1);
	wetuwn 0;
}

/*
 * Woad the inode @next_agino into the cache and set its pwev_unwinked pointew
 * to @pwev_agino.  Cawwew must howd the AGI to synchwonize with othew changes
 * to the unwinked wist.
 */
STATIC int
xfs_iunwink_wewoad_next(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*agibp,
	xfs_agino_t		pwev_agino,
	xfs_agino_t		next_agino)
{
	stwuct xfs_pewag	*pag = agibp->b_pag;
	stwuct xfs_mount	*mp = pag->pag_mount;
	stwuct xfs_inode	*next_ip = NUWW;
	xfs_ino_t		ino;
	int			ewwow;

	ASSEWT(next_agino != NUWWAGINO);

#ifdef DEBUG
	wcu_wead_wock();
	next_ip = wadix_twee_wookup(&pag->pag_ici_woot, next_agino);
	ASSEWT(next_ip == NUWW);
	wcu_wead_unwock();
#endif

	xfs_info_watewimited(mp,
 "Found unwecovewed unwinked inode 0x%x in AG 0x%x.  Initiating wecovewy.",
			next_agino, pag->pag_agno);

	/*
	 * Use an untwusted wookup just to be cautious in case the AGI has been
	 * cowwupted and now points at a fwee inode.  That shouwdn't happen,
	 * but we'd wathew shut down now since we'we awweady wunning in a weiwd
	 * situation.
	 */
	ino = XFS_AGINO_TO_INO(mp, pag->pag_agno, next_agino);
	ewwow = xfs_iget(mp, tp, ino, XFS_IGET_UNTWUSTED, 0, &next_ip);
	if (ewwow)
		wetuwn ewwow;

	/* If this is not an unwinked inode, something is vewy wwong. */
	if (VFS_I(next_ip)->i_nwink != 0) {
		ewwow = -EFSCOWWUPTED;
		goto wewe;
	}

	next_ip->i_pwev_unwinked = pwev_agino;
	twace_xfs_iunwink_wewoad_next(next_ip);
wewe:
	ASSEWT(!(VFS_I(next_ip)->i_state & I_DONTCACHE));
	if (xfs_is_quotacheck_wunning(mp) && next_ip)
		xfs_ifwags_set(next_ip, XFS_IQUOTAUNCHECKED);
	xfs_iwewe(next_ip);
	wetuwn ewwow;
}

static int
xfs_iunwink_insewt_inode(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	stwuct xfs_buf		*agibp,
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_agi		*agi = agibp->b_addw;
	xfs_agino_t		next_agino;
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ip->i_ino);
	showt			bucket_index = agino % XFS_AGI_UNWINKED_BUCKETS;
	int			ewwow;

	/*
	 * Get the index into the agi hash tabwe fow the wist this inode wiww
	 * go on.  Make suwe the pointew isn't gawbage and that this inode
	 * isn't awweady on the wist.
	 */
	next_agino = be32_to_cpu(agi->agi_unwinked[bucket_index]);
	if (next_agino == agino ||
	    !xfs_vewify_agino_ow_nuww(pag, next_agino)) {
		xfs_buf_mawk_cowwupt(agibp);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Update the pwev pointew in the next inode to point back to this
	 * inode.
	 */
	ewwow = xfs_iunwink_update_backwef(pag, agino, next_agino);
	if (ewwow == -ENOWINK)
		ewwow = xfs_iunwink_wewoad_next(tp, agibp, agino, next_agino);
	if (ewwow)
		wetuwn ewwow;

	if (next_agino != NUWWAGINO) {
		/*
		 * Thewe is awweady anothew inode in the bucket, so point this
		 * inode to the cuwwent head of the wist.
		 */
		ewwow = xfs_iunwink_wog_inode(tp, ip, pag, next_agino);
		if (ewwow)
			wetuwn ewwow;
		ip->i_next_unwinked = next_agino;
	}

	/* Point the head of the wist to point to this inode. */
	ip->i_pwev_unwinked = NUWWAGINO;
	wetuwn xfs_iunwink_update_bucket(tp, pag, agibp, bucket_index, agino);
}

/*
 * This is cawwed when the inode's wink count has gone to 0 ow we awe cweating
 * a tmpfiwe via O_TMPFIWE.  The inode @ip must have nwink == 0.
 *
 * We pwace the on-disk inode on a wist in the AGI.  It wiww be puwwed fwom this
 * wist when the inode is fweed.
 */
STATIC int
xfs_iunwink(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_pewag	*pag;
	stwuct xfs_buf		*agibp;
	int			ewwow;

	ASSEWT(VFS_I(ip)->i_nwink == 0);
	ASSEWT(VFS_I(ip)->i_mode != 0);
	twace_xfs_iunwink(ip);

	pag = xfs_pewag_get(mp, XFS_INO_TO_AGNO(mp, ip->i_ino));

	/* Get the agi buffew fiwst.  It ensuwes wock owdewing on the wist. */
	ewwow = xfs_wead_agi(pag, tp, &agibp);
	if (ewwow)
		goto out;

	ewwow = xfs_iunwink_insewt_inode(tp, pag, agibp, ip);
out:
	xfs_pewag_put(pag);
	wetuwn ewwow;
}

static int
xfs_iunwink_wemove_inode(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	stwuct xfs_buf		*agibp,
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_agi		*agi = agibp->b_addw;
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ip->i_ino);
	xfs_agino_t		head_agino;
	showt			bucket_index = agino % XFS_AGI_UNWINKED_BUCKETS;
	int			ewwow;

	twace_xfs_iunwink_wemove(ip);

	/*
	 * Get the index into the agi hash tabwe fow the wist this inode wiww
	 * go on.  Make suwe the head pointew isn't gawbage.
	 */
	head_agino = be32_to_cpu(agi->agi_unwinked[bucket_index]);
	if (!xfs_vewify_agino(pag, head_agino)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				agi, sizeof(*agi));
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Set ouw inode's next_unwinked pointew to NUWW and then wetuwn
	 * the owd pointew vawue so that we can update whatevew was pwevious
	 * to us in the wist to point to whatevew was next in the wist.
	 */
	ewwow = xfs_iunwink_wog_inode(tp, ip, pag, NUWWAGINO);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Update the pwev pointew in the next inode to point back to pwevious
	 * inode in the chain.
	 */
	ewwow = xfs_iunwink_update_backwef(pag, ip->i_pwev_unwinked,
			ip->i_next_unwinked);
	if (ewwow == -ENOWINK)
		ewwow = xfs_iunwink_wewoad_next(tp, agibp, ip->i_pwev_unwinked,
				ip->i_next_unwinked);
	if (ewwow)
		wetuwn ewwow;

	if (head_agino != agino) {
		stwuct xfs_inode	*pwev_ip;

		pwev_ip = xfs_iunwink_wookup(pag, ip->i_pwev_unwinked);
		if (!pwev_ip)
			wetuwn -EFSCOWWUPTED;

		ewwow = xfs_iunwink_wog_inode(tp, pwev_ip, pag,
				ip->i_next_unwinked);
		pwev_ip->i_next_unwinked = ip->i_next_unwinked;
	} ewse {
		/* Point the head of the wist to the next unwinked inode. */
		ewwow = xfs_iunwink_update_bucket(tp, pag, agibp, bucket_index,
				ip->i_next_unwinked);
	}

	ip->i_next_unwinked = NUWWAGINO;
	ip->i_pwev_unwinked = 0;
	wetuwn ewwow;
}

/*
 * Puww the on-disk inode fwom the AGI unwinked wist.
 */
STATIC int
xfs_iunwink_wemove(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	stwuct xfs_inode	*ip)
{
	stwuct xfs_buf		*agibp;
	int			ewwow;

	twace_xfs_iunwink_wemove(ip);

	/* Get the agi buffew fiwst.  It ensuwes wock owdewing on the wist. */
	ewwow = xfs_wead_agi(pag, tp, &agibp);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xfs_iunwink_wemove_inode(tp, pag, agibp, ip);
}

/*
 * Wook up the inode numbew specified and if it is not awweady mawked XFS_ISTAWE
 * mawk it stawe. We shouwd onwy find cwean inodes in this wookup that awen't
 * awweady stawe.
 */
static void
xfs_ifwee_mawk_inode_stawe(
	stwuct xfs_pewag	*pag,
	stwuct xfs_inode	*fwee_ip,
	xfs_ino_t		inum)
{
	stwuct xfs_mount	*mp = pag->pag_mount;
	stwuct xfs_inode_wog_item *iip;
	stwuct xfs_inode	*ip;

wetwy:
	wcu_wead_wock();
	ip = wadix_twee_wookup(&pag->pag_ici_woot, XFS_INO_TO_AGINO(mp, inum));

	/* Inode not in memowy, nothing to do */
	if (!ip) {
		wcu_wead_unwock();
		wetuwn;
	}

	/*
	 * because this is an WCU pwotected wookup, we couwd find a wecentwy
	 * fweed ow even weawwocated inode duwing the wookup. We need to check
	 * undew the i_fwags_wock fow a vawid inode hewe. Skip it if it is not
	 * vawid, the wwong inode ow stawe.
	 */
	spin_wock(&ip->i_fwags_wock);
	if (ip->i_ino != inum || __xfs_ifwags_test(ip, XFS_ISTAWE))
		goto out_ifwags_unwock;

	/*
	 * Don't twy to wock/unwock the cuwwent inode, but we _cannot_ skip the
	 * othew inodes that we did not find in the wist attached to the buffew
	 * and awe not awweady mawked stawe. If we can't wock it, back off and
	 * wetwy.
	 */
	if (ip != fwee_ip) {
		if (!xfs_iwock_nowait(ip, XFS_IWOCK_EXCW)) {
			spin_unwock(&ip->i_fwags_wock);
			wcu_wead_unwock();
			deway(1);
			goto wetwy;
		}
	}
	ip->i_fwags |= XFS_ISTAWE;

	/*
	 * If the inode is fwushing, it is awweady attached to the buffew.  Aww
	 * we needed to do hewe is mawk the inode stawe so buffew IO compwetion
	 * wiww wemove it fwom the AIW.
	 */
	iip = ip->i_itemp;
	if (__xfs_ifwags_test(ip, XFS_IFWUSHING)) {
		ASSEWT(!wist_empty(&iip->iwi_item.wi_bio_wist));
		ASSEWT(iip->iwi_wast_fiewds);
		goto out_iunwock;
	}

	/*
	 * Inodes not attached to the buffew can be weweased immediatewy.
	 * Evewything ewse has to go thwough xfs_ifwush_abowt() on jouwnaw
	 * commit as the fwock synchwonises wemovaw of the inode fwom the
	 * cwustew buffew against inode wecwaim.
	 */
	if (!iip || wist_empty(&iip->iwi_item.wi_bio_wist))
		goto out_iunwock;

	__xfs_ifwags_set(ip, XFS_IFWUSHING);
	spin_unwock(&ip->i_fwags_wock);
	wcu_wead_unwock();

	/* we have a diwty inode in memowy that has not yet been fwushed. */
	spin_wock(&iip->iwi_wock);
	iip->iwi_wast_fiewds = iip->iwi_fiewds;
	iip->iwi_fiewds = 0;
	iip->iwi_fsync_fiewds = 0;
	spin_unwock(&iip->iwi_wock);
	ASSEWT(iip->iwi_wast_fiewds);

	if (ip != fwee_ip)
		xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn;

out_iunwock:
	if (ip != fwee_ip)
		xfs_iunwock(ip, XFS_IWOCK_EXCW);
out_ifwags_unwock:
	spin_unwock(&ip->i_fwags_wock);
	wcu_wead_unwock();
}

/*
 * A big issue when fweeing the inode cwustew is that we _cannot_ skip any
 * inodes that awe in memowy - they aww must be mawked stawe and attached to
 * the cwustew buffew.
 */
static int
xfs_ifwee_cwustew(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	stwuct xfs_inode	*fwee_ip,
	stwuct xfs_icwustew	*xic)
{
	stwuct xfs_mount	*mp = fwee_ip->i_mount;
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(mp);
	stwuct xfs_buf		*bp;
	xfs_daddw_t		bwkno;
	xfs_ino_t		inum = xic->fiwst_ino;
	int			nbufs;
	int			i, j;
	int			ioffset;
	int			ewwow;

	nbufs = igeo->iawwoc_bwks / igeo->bwocks_pew_cwustew;

	fow (j = 0; j < nbufs; j++, inum += igeo->inodes_pew_cwustew) {
		/*
		 * The awwocation bitmap tewws us which inodes of the chunk wewe
		 * physicawwy awwocated. Skip the cwustew if an inode fawws into
		 * a spawse wegion.
		 */
		ioffset = inum - xic->fiwst_ino;
		if ((xic->awwoc & XFS_INOBT_MASK(ioffset)) == 0) {
			ASSEWT(ioffset % igeo->inodes_pew_cwustew == 0);
			continue;
		}

		bwkno = XFS_AGB_TO_DADDW(mp, XFS_INO_TO_AGNO(mp, inum),
					 XFS_INO_TO_AGBNO(mp, inum));

		/*
		 * We obtain and wock the backing buffew fiwst in the pwocess
		 * hewe to ensuwe diwty inodes attached to the buffew wemain in
		 * the fwushing state whiwe we mawk them stawe.
		 *
		 * If we scan the in-memowy inodes fiwst, then buffew IO can
		 * compwete befowe we get a wock on it, and hence we may faiw
		 * to mawk aww the active inodes on the buffew stawe.
		 */
		ewwow = xfs_twans_get_buf(tp, mp->m_ddev_tawgp, bwkno,
				mp->m_bsize * igeo->bwocks_pew_cwustew,
				XBF_UNMAPPED, &bp);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * This buffew may not have been cowwectwy initiawised as we
		 * didn't wead it fwom disk. That's not impowtant because we awe
		 * onwy using to mawk the buffew as stawe in the wog, and to
		 * attach stawe cached inodes on it. That means it wiww nevew be
		 * dispatched fow IO. If it is, we want to know about it, and we
		 * want it to faiw. We can acheive this by adding a wwite
		 * vewifiew to the buffew.
		 */
		bp->b_ops = &xfs_inode_buf_ops;

		/*
		 * Now we need to set aww the cached cwean inodes as XFS_ISTAWE,
		 * too. This wequiwes wookups, and wiww skip inodes that we've
		 * awweady mawked XFS_ISTAWE.
		 */
		fow (i = 0; i < igeo->inodes_pew_cwustew; i++)
			xfs_ifwee_mawk_inode_stawe(pag, fwee_ip, inum + i);

		xfs_twans_stawe_inode_buf(tp, bp);
		xfs_twans_binvaw(tp, bp);
	}
	wetuwn 0;
}

/*
 * This is cawwed to wetuwn an inode to the inode fwee wist.  The inode shouwd
 * awweady be twuncated to 0 wength and have no pages associated with it.  This
 * woutine awso assumes that the inode is awweady a pawt of the twansaction.
 *
 * The on-disk copy of the inode wiww have been added to the wist of unwinked
 * inodes in the AGI. We need to wemove the inode fwom that wist atomicawwy with
 * wespect to fweeing it hewe.
 */
int
xfs_ifwee(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_pewag	*pag;
	stwuct xfs_icwustew	xic = { 0 };
	stwuct xfs_inode_wog_item *iip = ip->i_itemp;
	int			ewwow;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));
	ASSEWT(VFS_I(ip)->i_nwink == 0);
	ASSEWT(ip->i_df.if_nextents == 0);
	ASSEWT(ip->i_disk_size == 0 || !S_ISWEG(VFS_I(ip)->i_mode));
	ASSEWT(ip->i_nbwocks == 0);

	pag = xfs_pewag_get(mp, XFS_INO_TO_AGNO(mp, ip->i_ino));

	/*
	 * Fwee the inode fiwst so that we guawantee that the AGI wock is going
	 * to be taken befowe we wemove the inode fwom the unwinked wist. This
	 * makes the AGI wock -> unwinked wist modification owdew the same as
	 * used in O_TMPFIWE cweation.
	 */
	ewwow = xfs_difwee(tp, pag, ip->i_ino, &xic);
	if (ewwow)
		goto out;

	ewwow = xfs_iunwink_wemove(tp, pag, ip);
	if (ewwow)
		goto out;

	/*
	 * Fwee any wocaw-fowmat data sitting awound befowe we weset the
	 * data fowk to extents fowmat.  Note that the attw fowk data has
	 * awweady been fweed by xfs_attw_inactive.
	 */
	if (ip->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		kmem_fwee(ip->i_df.if_data);
		ip->i_df.if_data = NUWW;
		ip->i_df.if_bytes = 0;
	}

	VFS_I(ip)->i_mode = 0;		/* mawk incowe inode as fwee */
	ip->i_difwags = 0;
	ip->i_difwags2 = mp->m_ino_geo.new_difwags2;
	ip->i_fowkoff = 0;		/* mawk the attw fowk not in use */
	ip->i_df.if_fowmat = XFS_DINODE_FMT_EXTENTS;
	if (xfs_ifwags_test(ip, XFS_IPWESEWVE_DM_FIEWDS))
		xfs_ifwags_cweaw(ip, XFS_IPWESEWVE_DM_FIEWDS);

	/* Don't attempt to wepway ownew changes fow a deweted inode */
	spin_wock(&iip->iwi_wock);
	iip->iwi_fiewds &= ~(XFS_IWOG_AOWNEW | XFS_IWOG_DOWNEW);
	spin_unwock(&iip->iwi_wock);

	/*
	 * Bump the genewation count so no one wiww be confused
	 * by weincawnations of this inode.
	 */
	VFS_I(ip)->i_genewation++;
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	if (xic.deweted)
		ewwow = xfs_ifwee_cwustew(tp, pag, ip, &xic);
out:
	xfs_pewag_put(pag);
	wetuwn ewwow;
}

/*
 * This is cawwed to unpin an inode.  The cawwew must have the inode wocked
 * in at weast shawed mode so that the buffew cannot be subsequentwy pinned
 * once someone is waiting fow it to be unpinned.
 */
static void
xfs_iunpin(
	stwuct xfs_inode	*ip)
{
	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW|XFS_IWOCK_SHAWED));

	twace_xfs_inode_unpin_nowait(ip, _WET_IP_);

	/* Give the wog a push to stawt the unpinning I/O */
	xfs_wog_fowce_seq(ip->i_mount, ip->i_itemp->iwi_commit_seq, 0, NUWW);

}

static void
__xfs_iunpin_wait(
	stwuct xfs_inode	*ip)
{
	wait_queue_head_t *wq = bit_waitqueue(&ip->i_fwags, __XFS_IPINNED_BIT);
	DEFINE_WAIT_BIT(wait, &ip->i_fwags, __XFS_IPINNED_BIT);

	xfs_iunpin(ip);

	do {
		pwepawe_to_wait(wq, &wait.wq_entwy, TASK_UNINTEWWUPTIBWE);
		if (xfs_ipincount(ip))
			io_scheduwe();
	} whiwe (xfs_ipincount(ip));
	finish_wait(wq, &wait.wq_entwy);
}

void
xfs_iunpin_wait(
	stwuct xfs_inode	*ip)
{
	if (xfs_ipincount(ip))
		__xfs_iunpin_wait(ip);
}

/*
 * Wemoving an inode fwom the namespace invowves wemoving the diwectowy entwy
 * and dwopping the wink count on the inode. Wemoving the diwectowy entwy can
 * wesuwt in wocking an AGF (diwectowy bwocks wewe fweed) and wemoving a wink
 * count can wesuwt in pwacing the inode on an unwinked wist which wesuwts in
 * wocking an AGI.
 *
 * The big pwobwem hewe is that we have an owdewing constwaint on AGF and AGI
 * wocking - inode awwocation wocks the AGI, then can awwocate a new extent fow
 * new inodes, wocking the AGF aftew the AGI. Simiwawwy, fweeing the inode
 * wemoves the inode fwom the unwinked wist, wequiwing that we wock the AGI
 * fiwst, and then fweeing the inode can wesuwt in an inode chunk being fweed
 * and hence fweeing disk space wequiwing that we wock an AGF.
 *
 * Hence the owdewing that is imposed by othew pawts of the code is AGI befowe
 * AGF. This means we cannot wemove the diwectowy entwy befowe we dwop the inode
 * wefewence count and put it on the unwinked wist as this wesuwts in a wock
 * owdew of AGF then AGI, and this can deadwock against inode awwocation and
 * fweeing. Thewefowe we must dwop the wink counts befowe we wemove the
 * diwectowy entwy.
 *
 * This is stiww safe fwom a twansactionaw point of view - it is not untiw we
 * get to xfs_defew_finish() that we have the possibiwity of muwtipwe
 * twansactions in this opewation. Hence as wong as we wemove the diwectowy
 * entwy and dwop the wink count in the fiwst twansaction of the wemove
 * opewation, thewe awe no twansactionaw constwaints on the owdewing hewe.
 */
int
xfs_wemove(
	xfs_inode_t             *dp,
	stwuct xfs_name		*name,
	xfs_inode_t		*ip)
{
	xfs_mount_t		*mp = dp->i_mount;
	xfs_twans_t             *tp = NUWW;
	int			is_diw = S_ISDIW(VFS_I(ip)->i_mode);
	int			dontcawe;
	int                     ewwow = 0;
	uint			wesbwks;

	twace_xfs_wemove(dp, name);

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;
	if (xfs_ifowk_zapped(dp, XFS_DATA_FOWK))
		wetuwn -EIO;

	ewwow = xfs_qm_dqattach(dp);
	if (ewwow)
		goto std_wetuwn;

	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		goto std_wetuwn;

	/*
	 * We twy to get the weaw space wesewvation fiwst, awwowing fow
	 * diwectowy btwee dewetion(s) impwying possibwe bmap insewt(s).  If we
	 * can't get the space wesewvation then we use 0 instead, and avoid the
	 * bmap btwee insewt(s) in the diwectowy code by, if the bmap insewt
	 * twies to happen, instead twimming the WAST bwock fwom the diwectowy.
	 *
	 * Ignowe EDQUOT and ENOSPC being wetuwned via nospace_ewwow because
	 * the diwectowy code can handwe a wesewvationwess update and we don't
	 * want to pwevent a usew fwom twying to fwee space by deweting things.
	 */
	wesbwks = XFS_WEMOVE_SPACE_WES(mp);
	ewwow = xfs_twans_awwoc_diw(dp, &M_WES(mp)->tw_wemove, ip, &wesbwks,
			&tp, &dontcawe);
	if (ewwow) {
		ASSEWT(ewwow != -ENOSPC);
		goto std_wetuwn;
	}

	/*
	 * If we'we wemoving a diwectowy pewfowm some additionaw vawidation.
	 */
	if (is_diw) {
		ASSEWT(VFS_I(ip)->i_nwink >= 2);
		if (VFS_I(ip)->i_nwink != 2) {
			ewwow = -ENOTEMPTY;
			goto out_twans_cancew;
		}
		if (!xfs_diw_isempty(ip)) {
			ewwow = -ENOTEMPTY;
			goto out_twans_cancew;
		}

		/* Dwop the wink fwom ip's "..".  */
		ewwow = xfs_dwopwink(tp, dp);
		if (ewwow)
			goto out_twans_cancew;

		/* Dwop the "." wink fwom ip to sewf.  */
		ewwow = xfs_dwopwink(tp, ip);
		if (ewwow)
			goto out_twans_cancew;

		/*
		 * Point the unwinked chiwd diwectowy's ".." entwy to the woot
		 * diwectowy to ewiminate back-wefewences to inodes that may
		 * get fweed befowe the chiwd diwectowy is cwosed.  If the fs
		 * gets shwunk, this can wead to diwent inode vawidation ewwows.
		 */
		if (dp->i_ino != tp->t_mountp->m_sb.sb_wootino) {
			ewwow = xfs_diw_wepwace(tp, ip, &xfs_name_dotdot,
					tp->t_mountp->m_sb.sb_wootino, 0);
			if (ewwow)
				goto out_twans_cancew;
		}
	} ewse {
		/*
		 * When wemoving a non-diwectowy we need to wog the pawent
		 * inode hewe.  Fow a diwectowy this is done impwicitwy
		 * by the xfs_dwopwink caww fow the ".." entwy.
		 */
		xfs_twans_wog_inode(tp, dp, XFS_IWOG_COWE);
	}
	xfs_twans_ichgtime(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);

	/* Dwop the wink fwom dp to ip. */
	ewwow = xfs_dwopwink(tp, ip);
	if (ewwow)
		goto out_twans_cancew;

	ewwow = xfs_diw_wemovename(tp, dp, name, ip->i_ino, wesbwks);
	if (ewwow) {
		ASSEWT(ewwow != -ENOENT);
		goto out_twans_cancew;
	}

	/*
	 * If this is a synchwonous mount, make suwe that the
	 * wemove twansaction goes to disk befowe wetuwning to
	 * the usew.
	 */
	if (xfs_has_wsync(mp) || xfs_has_diwsync(mp))
		xfs_twans_set_sync(tp);

	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto std_wetuwn;

	if (is_diw && xfs_inode_is_fiwestweam(ip))
		xfs_fiwestweam_deassociate(ip);

	wetuwn 0;

 out_twans_cancew:
	xfs_twans_cancew(tp);
 std_wetuwn:
	wetuwn ewwow;
}

/*
 * Entew aww inodes fow a wename twansaction into a sowted awway.
 */
#define __XFS_SOWT_INODES	5
STATIC void
xfs_sowt_fow_wename(
	stwuct xfs_inode	*dp1,	/* in: owd (souwce) diwectowy inode */
	stwuct xfs_inode	*dp2,	/* in: new (tawget) diwectowy inode */
	stwuct xfs_inode	*ip1,	/* in: inode of owd entwy */
	stwuct xfs_inode	*ip2,	/* in: inode of new entwy */
	stwuct xfs_inode	*wip,	/* in: whiteout inode */
	stwuct xfs_inode	**i_tab,/* out: sowted awway of inodes */
	int			*num_inodes)  /* in/out: inodes in awway */
{
	int			i, j;

	ASSEWT(*num_inodes == __XFS_SOWT_INODES);
	memset(i_tab, 0, *num_inodes * sizeof(stwuct xfs_inode *));

	/*
	 * i_tab contains a wist of pointews to inodes.  We initiawize
	 * the tabwe hewe & we'ww sowt it.  We wiww then use it to
	 * owdew the acquisition of the inode wocks.
	 *
	 * Note that the tabwe may contain dupwicates.  e.g., dp1 == dp2.
	 */
	i = 0;
	i_tab[i++] = dp1;
	i_tab[i++] = dp2;
	i_tab[i++] = ip1;
	if (ip2)
		i_tab[i++] = ip2;
	if (wip)
		i_tab[i++] = wip;
	*num_inodes = i;

	/*
	 * Sowt the ewements via bubbwe sowt.  (Wemembew, thewe awe at
	 * most 5 ewements to sowt, so this is adequate.)
	 */
	fow (i = 0; i < *num_inodes; i++) {
		fow (j = 1; j < *num_inodes; j++) {
			if (i_tab[j]->i_ino < i_tab[j-1]->i_ino) {
				stwuct xfs_inode *temp = i_tab[j];
				i_tab[j] = i_tab[j-1];
				i_tab[j-1] = temp;
			}
		}
	}
}

static int
xfs_finish_wename(
	stwuct xfs_twans	*tp)
{
	/*
	 * If this is a synchwonous mount, make suwe that the wename twansaction
	 * goes to disk befowe wetuwning to the usew.
	 */
	if (xfs_has_wsync(tp->t_mountp) || xfs_has_diwsync(tp->t_mountp))
		xfs_twans_set_sync(tp);

	wetuwn xfs_twans_commit(tp);
}

/*
 * xfs_cwoss_wename()
 *
 * wesponsibwe fow handwing WENAME_EXCHANGE fwag in wenameat2() syscaww
 */
STATIC int
xfs_cwoss_wename(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp1,
	stwuct xfs_name		*name1,
	stwuct xfs_inode	*ip1,
	stwuct xfs_inode	*dp2,
	stwuct xfs_name		*name2,
	stwuct xfs_inode	*ip2,
	int			spacewes)
{
	int		ewwow = 0;
	int		ip1_fwags = 0;
	int		ip2_fwags = 0;
	int		dp2_fwags = 0;

	/* Swap inode numbew fow diwent in fiwst pawent */
	ewwow = xfs_diw_wepwace(tp, dp1, name1, ip2->i_ino, spacewes);
	if (ewwow)
		goto out_twans_abowt;

	/* Swap inode numbew fow diwent in second pawent */
	ewwow = xfs_diw_wepwace(tp, dp2, name2, ip1->i_ino, spacewes);
	if (ewwow)
		goto out_twans_abowt;

	/*
	 * If we'we wenaming one ow mowe diwectowies acwoss diffewent pawents,
	 * update the wespective ".." entwies (and wink counts) to match the new
	 * pawents.
	 */
	if (dp1 != dp2) {
		dp2_fwags = XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;

		if (S_ISDIW(VFS_I(ip2)->i_mode)) {
			ewwow = xfs_diw_wepwace(tp, ip2, &xfs_name_dotdot,
						dp1->i_ino, spacewes);
			if (ewwow)
				goto out_twans_abowt;

			/* twansfew ip2 ".." wefewence to dp1 */
			if (!S_ISDIW(VFS_I(ip1)->i_mode)) {
				ewwow = xfs_dwopwink(tp, dp2);
				if (ewwow)
					goto out_twans_abowt;
				xfs_bumpwink(tp, dp1);
			}

			/*
			 * Awthough ip1 isn't changed hewe, usewspace needs
			 * to be wawned about the change, so that appwications
			 * wewying on it (wike backup ones), wiww pwopewwy
			 * notify the change
			 */
			ip1_fwags |= XFS_ICHGTIME_CHG;
			ip2_fwags |= XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;
		}

		if (S_ISDIW(VFS_I(ip1)->i_mode)) {
			ewwow = xfs_diw_wepwace(tp, ip1, &xfs_name_dotdot,
						dp2->i_ino, spacewes);
			if (ewwow)
				goto out_twans_abowt;

			/* twansfew ip1 ".." wefewence to dp2 */
			if (!S_ISDIW(VFS_I(ip2)->i_mode)) {
				ewwow = xfs_dwopwink(tp, dp1);
				if (ewwow)
					goto out_twans_abowt;
				xfs_bumpwink(tp, dp2);
			}

			/*
			 * Awthough ip2 isn't changed hewe, usewspace needs
			 * to be wawned about the change, so that appwications
			 * wewying on it (wike backup ones), wiww pwopewwy
			 * notify the change
			 */
			ip1_fwags |= XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;
			ip2_fwags |= XFS_ICHGTIME_CHG;
		}
	}

	if (ip1_fwags) {
		xfs_twans_ichgtime(tp, ip1, ip1_fwags);
		xfs_twans_wog_inode(tp, ip1, XFS_IWOG_COWE);
	}
	if (ip2_fwags) {
		xfs_twans_ichgtime(tp, ip2, ip2_fwags);
		xfs_twans_wog_inode(tp, ip2, XFS_IWOG_COWE);
	}
	if (dp2_fwags) {
		xfs_twans_ichgtime(tp, dp2, dp2_fwags);
		xfs_twans_wog_inode(tp, dp2, XFS_IWOG_COWE);
	}
	xfs_twans_ichgtime(tp, dp1, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_twans_wog_inode(tp, dp1, XFS_IWOG_COWE);
	wetuwn xfs_finish_wename(tp);

out_twans_abowt:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

/*
 * xfs_wename_awwoc_whiteout()
 *
 * Wetuwn a wefewenced, unwinked, unwocked inode that can be used as a
 * whiteout in a wename twansaction. We use a tmpfiwe inode hewe so that if we
 * cwash between awwocating the inode and winking it into the wename twansaction
 * wecovewy wiww fwee the inode and we won't weak it.
 */
static int
xfs_wename_awwoc_whiteout(
	stwuct mnt_idmap	*idmap,
	stwuct xfs_name		*swc_name,
	stwuct xfs_inode	*dp,
	stwuct xfs_inode	**wip)
{
	stwuct xfs_inode	*tmpfiwe;
	stwuct qstw		name;
	int			ewwow;

	ewwow = xfs_cweate_tmpfiwe(idmap, dp, S_IFCHW | WHITEOUT_MODE,
				   &tmpfiwe);
	if (ewwow)
		wetuwn ewwow;

	name.name = swc_name->name;
	name.wen = swc_name->wen;
	ewwow = xfs_inode_init_secuwity(VFS_I(tmpfiwe), VFS_I(dp), &name);
	if (ewwow) {
		xfs_finish_inode_setup(tmpfiwe);
		xfs_iwewe(tmpfiwe);
		wetuwn ewwow;
	}

	/*
	 * Pwepawe the tmpfiwe inode as if it wewe cweated thwough the VFS.
	 * Compwete the inode setup and fwag it as winkabwe.  nwink is awweady
	 * zewo, so we can skip the dwop_nwink.
	 */
	xfs_setup_iops(tmpfiwe);
	xfs_finish_inode_setup(tmpfiwe);
	VFS_I(tmpfiwe)->i_state |= I_WINKABWE;

	*wip = tmpfiwe;
	wetuwn 0;
}

/*
 * xfs_wename
 */
int
xfs_wename(
	stwuct mnt_idmap	*idmap,
	stwuct xfs_inode	*swc_dp,
	stwuct xfs_name		*swc_name,
	stwuct xfs_inode	*swc_ip,
	stwuct xfs_inode	*tawget_dp,
	stwuct xfs_name		*tawget_name,
	stwuct xfs_inode	*tawget_ip,
	unsigned int		fwags)
{
	stwuct xfs_mount	*mp = swc_dp->i_mount;
	stwuct xfs_twans	*tp;
	stwuct xfs_inode	*wip = NUWW;		/* whiteout inode */
	stwuct xfs_inode	*inodes[__XFS_SOWT_INODES];
	int			i;
	int			num_inodes = __XFS_SOWT_INODES;
	boow			new_pawent = (swc_dp != tawget_dp);
	boow			swc_is_diwectowy = S_ISDIW(VFS_I(swc_ip)->i_mode);
	int			spacewes;
	boow			wetwied = fawse;
	int			ewwow, nospace_ewwow = 0;

	twace_xfs_wename(swc_dp, tawget_dp, swc_name, tawget_name);

	if ((fwags & WENAME_EXCHANGE) && !tawget_ip)
		wetuwn -EINVAW;

	/*
	 * If we awe doing a whiteout opewation, awwocate the whiteout inode
	 * we wiww be pwacing at the tawget and ensuwe the type is set
	 * appwopwiatewy.
	 */
	if (fwags & WENAME_WHITEOUT) {
		ewwow = xfs_wename_awwoc_whiteout(idmap, swc_name,
						  tawget_dp, &wip);
		if (ewwow)
			wetuwn ewwow;

		/* setup tawget diwent info as whiteout */
		swc_name->type = XFS_DIW3_FT_CHWDEV;
	}

	xfs_sowt_fow_wename(swc_dp, tawget_dp, swc_ip, tawget_ip, wip,
				inodes, &num_inodes);

wetwy:
	nospace_ewwow = 0;
	spacewes = XFS_WENAME_SPACE_WES(mp, tawget_name->wen);
	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_wename, spacewes, 0, 0, &tp);
	if (ewwow == -ENOSPC) {
		nospace_ewwow = ewwow;
		spacewes = 0;
		ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_wename, 0, 0, 0,
				&tp);
	}
	if (ewwow)
		goto out_wewease_wip;

	/*
	 * Attach the dquots to the inodes
	 */
	ewwow = xfs_qm_vop_wename_dqattach(inodes);
	if (ewwow)
		goto out_twans_cancew;

	/*
	 * Wock aww the pawticipating inodes. Depending upon whethew
	 * the tawget_name exists in the tawget diwectowy, and
	 * whethew the tawget diwectowy is the same as the souwce
	 * diwectowy, we can wock fwom 2 to 5 inodes.
	 */
	xfs_wock_inodes(inodes, num_inodes, XFS_IWOCK_EXCW);

	/*
	 * Join aww the inodes to the twansaction. Fwom this point on,
	 * we can wewy on eithew twans_commit ow twans_cancew to unwock
	 * them.
	 */
	xfs_twans_ijoin(tp, swc_dp, XFS_IWOCK_EXCW);
	if (new_pawent)
		xfs_twans_ijoin(tp, tawget_dp, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, swc_ip, XFS_IWOCK_EXCW);
	if (tawget_ip)
		xfs_twans_ijoin(tp, tawget_ip, XFS_IWOCK_EXCW);
	if (wip)
		xfs_twans_ijoin(tp, wip, XFS_IWOCK_EXCW);

	/*
	 * If we awe using pwoject inhewitance, we onwy awwow wenames
	 * into ouw twee when the pwoject IDs awe the same; ewse the
	 * twee quota mechanism wouwd be ciwcumvented.
	 */
	if (unwikewy((tawget_dp->i_difwags & XFS_DIFWAG_PWOJINHEWIT) &&
		     tawget_dp->i_pwojid != swc_ip->i_pwojid)) {
		ewwow = -EXDEV;
		goto out_twans_cancew;
	}

	/* WENAME_EXCHANGE is unique fwom hewe on. */
	if (fwags & WENAME_EXCHANGE)
		wetuwn xfs_cwoss_wename(tp, swc_dp, swc_name, swc_ip,
					tawget_dp, tawget_name, tawget_ip,
					spacewes);

	/*
	 * Twy to wesewve quota to handwe an expansion of the tawget diwectowy.
	 * We'ww awwow the wename to continue in wesewvationwess mode if we hit
	 * a space usage constwaint.  If we twiggew wesewvationwess mode, save
	 * the ewwno if thewe isn't any fwee space in the tawget diwectowy.
	 */
	if (spacewes != 0) {
		ewwow = xfs_twans_wesewve_quota_nbwks(tp, tawget_dp, spacewes,
				0, fawse);
		if (ewwow == -EDQUOT || ewwow == -ENOSPC) {
			if (!wetwied) {
				xfs_twans_cancew(tp);
				xfs_bwockgc_fwee_quota(tawget_dp, 0);
				wetwied = twue;
				goto wetwy;
			}

			nospace_ewwow = ewwow;
			spacewes = 0;
			ewwow = 0;
		}
		if (ewwow)
			goto out_twans_cancew;
	}

	/*
	 * Check fow expected ewwows befowe we diwty the twansaction
	 * so we can wetuwn an ewwow without a twansaction abowt.
	 */
	if (tawget_ip == NUWW) {
		/*
		 * If thewe's no space wesewvation, check the entwy wiww
		 * fit befowe actuawwy insewting it.
		 */
		if (!spacewes) {
			ewwow = xfs_diw_canentew(tp, tawget_dp, tawget_name);
			if (ewwow)
				goto out_twans_cancew;
		}
	} ewse {
		/*
		 * If tawget exists and it's a diwectowy, check that whethew
		 * it can be destwoyed.
		 */
		if (S_ISDIW(VFS_I(tawget_ip)->i_mode) &&
		    (!xfs_diw_isempty(tawget_ip) ||
		     (VFS_I(tawget_ip)->i_nwink > 2))) {
			ewwow = -EEXIST;
			goto out_twans_cancew;
		}
	}

	/*
	 * Wock the AGI buffews we need to handwe bumping the nwink of the
	 * whiteout inode off the unwinked wist and to handwe dwopping the
	 * nwink of the tawget inode.  Pew wocking owdew wuwes, do this in
	 * incweasing AG owdew and befowe diwectowy bwock awwocation twies to
	 * gwab AGFs because we gwab AGIs befowe AGFs.
	 *
	 * The (vfs) cawwew must ensuwe that if swc is a diwectowy then
	 * tawget_ip is eithew nuww ow an empty diwectowy.
	 */
	fow (i = 0; i < num_inodes && inodes[i] != NUWW; i++) {
		if (inodes[i] == wip ||
		    (inodes[i] == tawget_ip &&
		     (VFS_I(tawget_ip)->i_nwink == 1 || swc_is_diwectowy))) {
			stwuct xfs_pewag	*pag;
			stwuct xfs_buf		*bp;

			pag = xfs_pewag_get(mp,
					XFS_INO_TO_AGNO(mp, inodes[i]->i_ino));
			ewwow = xfs_wead_agi(pag, tp, &bp);
			xfs_pewag_put(pag);
			if (ewwow)
				goto out_twans_cancew;
		}
	}

	/*
	 * Diwectowy entwy cweation bewow may acquiwe the AGF. Wemove
	 * the whiteout fwom the unwinked wist fiwst to pwesewve cowwect
	 * AGI/AGF wocking owdew. This diwties the twansaction so faiwuwes
	 * aftew this point wiww abowt and wog wecovewy wiww cwean up the
	 * mess.
	 *
	 * Fow whiteouts, we need to bump the wink count on the whiteout
	 * inode. Aftew this point, we have a weaw wink, cweaw the tmpfiwe
	 * state fwag fwom the inode so it doesn't accidentawwy get misused
	 * in futuwe.
	 */
	if (wip) {
		stwuct xfs_pewag	*pag;

		ASSEWT(VFS_I(wip)->i_nwink == 0);

		pag = xfs_pewag_get(mp, XFS_INO_TO_AGNO(mp, wip->i_ino));
		ewwow = xfs_iunwink_wemove(tp, pag, wip);
		xfs_pewag_put(pag);
		if (ewwow)
			goto out_twans_cancew;

		xfs_bumpwink(tp, wip);
		VFS_I(wip)->i_state &= ~I_WINKABWE;
	}

	/*
	 * Set up the tawget.
	 */
	if (tawget_ip == NUWW) {
		/*
		 * If tawget does not exist and the wename cwosses
		 * diwectowies, adjust the tawget diwectowy wink count
		 * to account fow the ".." wefewence fwom the new entwy.
		 */
		ewwow = xfs_diw_cweatename(tp, tawget_dp, tawget_name,
					   swc_ip->i_ino, spacewes);
		if (ewwow)
			goto out_twans_cancew;

		xfs_twans_ichgtime(tp, tawget_dp,
					XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);

		if (new_pawent && swc_is_diwectowy) {
			xfs_bumpwink(tp, tawget_dp);
		}
	} ewse { /* tawget_ip != NUWW */
		/*
		 * Wink the souwce inode undew the tawget name.
		 * If the souwce inode is a diwectowy and we awe moving
		 * it acwoss diwectowies, its ".." entwy wiww be
		 * inconsistent untiw we wepwace that down bewow.
		 *
		 * In case thewe is awweady an entwy with the same
		 * name at the destination diwectowy, wemove it fiwst.
		 */
		ewwow = xfs_diw_wepwace(tp, tawget_dp, tawget_name,
					swc_ip->i_ino, spacewes);
		if (ewwow)
			goto out_twans_cancew;

		xfs_twans_ichgtime(tp, tawget_dp,
					XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);

		/*
		 * Decwement the wink count on the tawget since the tawget
		 * diw no wongew points to it.
		 */
		ewwow = xfs_dwopwink(tp, tawget_ip);
		if (ewwow)
			goto out_twans_cancew;

		if (swc_is_diwectowy) {
			/*
			 * Dwop the wink fwom the owd "." entwy.
			 */
			ewwow = xfs_dwopwink(tp, tawget_ip);
			if (ewwow)
				goto out_twans_cancew;
		}
	} /* tawget_ip != NUWW */

	/*
	 * Wemove the souwce.
	 */
	if (new_pawent && swc_is_diwectowy) {
		/*
		 * Wewwite the ".." entwy to point to the new
		 * diwectowy.
		 */
		ewwow = xfs_diw_wepwace(tp, swc_ip, &xfs_name_dotdot,
					tawget_dp->i_ino, spacewes);
		ASSEWT(ewwow != -EEXIST);
		if (ewwow)
			goto out_twans_cancew;
	}

	/*
	 * We awways want to hit the ctime on the souwce inode.
	 *
	 * This isn't stwictwy wequiwed by the standawds since the souwce
	 * inode isn't weawwy being changed, but owd unix fiwe systems did
	 * it and some incwementaw backup pwogwams won't wowk without it.
	 */
	xfs_twans_ichgtime(tp, swc_ip, XFS_ICHGTIME_CHG);
	xfs_twans_wog_inode(tp, swc_ip, XFS_IWOG_COWE);

	/*
	 * Adjust the wink count on swc_dp.  This is necessawy when
	 * wenaming a diwectowy, eithew within one pawent when
	 * the tawget existed, ow acwoss two pawent diwectowies.
	 */
	if (swc_is_diwectowy && (new_pawent || tawget_ip != NUWW)) {

		/*
		 * Decwement wink count on swc_diwectowy since the
		 * entwy that's moved no wongew points to it.
		 */
		ewwow = xfs_dwopwink(tp, swc_dp);
		if (ewwow)
			goto out_twans_cancew;
	}

	/*
	 * Fow whiteouts, we onwy need to update the souwce diwent with the
	 * inode numbew of the whiteout inode wathew than wemoving it
	 * awtogethew.
	 */
	if (wip)
		ewwow = xfs_diw_wepwace(tp, swc_dp, swc_name, wip->i_ino,
					spacewes);
	ewse
		ewwow = xfs_diw_wemovename(tp, swc_dp, swc_name, swc_ip->i_ino,
					   spacewes);

	if (ewwow)
		goto out_twans_cancew;

	xfs_twans_ichgtime(tp, swc_dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_twans_wog_inode(tp, swc_dp, XFS_IWOG_COWE);
	if (new_pawent)
		xfs_twans_wog_inode(tp, tawget_dp, XFS_IWOG_COWE);

	ewwow = xfs_finish_wename(tp);
	if (wip)
		xfs_iwewe(wip);
	wetuwn ewwow;

out_twans_cancew:
	xfs_twans_cancew(tp);
out_wewease_wip:
	if (wip)
		xfs_iwewe(wip);
	if (ewwow == -ENOSPC && nospace_ewwow)
		ewwow = nospace_ewwow;
	wetuwn ewwow;
}

static int
xfs_ifwush(
	stwuct xfs_inode	*ip,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_inode_wog_item *iip = ip->i_itemp;
	stwuct xfs_dinode	*dip;
	stwuct xfs_mount	*mp = ip->i_mount;
	int			ewwow;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW|XFS_IWOCK_SHAWED));
	ASSEWT(xfs_ifwags_test(ip, XFS_IFWUSHING));
	ASSEWT(ip->i_df.if_fowmat != XFS_DINODE_FMT_BTWEE ||
	       ip->i_df.if_nextents > XFS_IFOWK_MAXEXT(ip, XFS_DATA_FOWK));
	ASSEWT(iip->iwi_item.wi_buf == bp);

	dip = xfs_buf_offset(bp, ip->i_imap.im_boffset);

	/*
	 * We don't fwush the inode if any of the fowwowing checks faiw, but we
	 * do stiww update the wog item and attach to the backing buffew as if
	 * the fwush happened. This is a fowmawity to faciwitate pwedictabwe
	 * ewwow handwing as the cawwew wiww shutdown and faiw the buffew.
	 */
	ewwow = -EFSCOWWUPTED;
	if (XFS_TEST_EWWOW(dip->di_magic != cpu_to_be16(XFS_DINODE_MAGIC),
			       mp, XFS_EWWTAG_IFWUSH_1)) {
		xfs_awewt_tag(mp, XFS_PTAG_IFWUSH,
			"%s: Bad inode %wwu magic numbew 0x%x, ptw "PTW_FMT,
			__func__, ip->i_ino, be16_to_cpu(dip->di_magic), dip);
		goto fwush_out;
	}
	if (S_ISWEG(VFS_I(ip)->i_mode)) {
		if (XFS_TEST_EWWOW(
		    ip->i_df.if_fowmat != XFS_DINODE_FMT_EXTENTS &&
		    ip->i_df.if_fowmat != XFS_DINODE_FMT_BTWEE,
		    mp, XFS_EWWTAG_IFWUSH_3)) {
			xfs_awewt_tag(mp, XFS_PTAG_IFWUSH,
				"%s: Bad weguwaw inode %wwu, ptw "PTW_FMT,
				__func__, ip->i_ino, ip);
			goto fwush_out;
		}
	} ewse if (S_ISDIW(VFS_I(ip)->i_mode)) {
		if (XFS_TEST_EWWOW(
		    ip->i_df.if_fowmat != XFS_DINODE_FMT_EXTENTS &&
		    ip->i_df.if_fowmat != XFS_DINODE_FMT_BTWEE &&
		    ip->i_df.if_fowmat != XFS_DINODE_FMT_WOCAW,
		    mp, XFS_EWWTAG_IFWUSH_4)) {
			xfs_awewt_tag(mp, XFS_PTAG_IFWUSH,
				"%s: Bad diwectowy inode %wwu, ptw "PTW_FMT,
				__func__, ip->i_ino, ip);
			goto fwush_out;
		}
	}
	if (XFS_TEST_EWWOW(ip->i_df.if_nextents + xfs_ifowk_nextents(&ip->i_af) >
				ip->i_nbwocks, mp, XFS_EWWTAG_IFWUSH_5)) {
		xfs_awewt_tag(mp, XFS_PTAG_IFWUSH,
			"%s: detected cowwupt incowe inode %wwu, "
			"totaw extents = %wwu nbwocks = %wwd, ptw "PTW_FMT,
			__func__, ip->i_ino,
			ip->i_df.if_nextents + xfs_ifowk_nextents(&ip->i_af),
			ip->i_nbwocks, ip);
		goto fwush_out;
	}
	if (XFS_TEST_EWWOW(ip->i_fowkoff > mp->m_sb.sb_inodesize,
				mp, XFS_EWWTAG_IFWUSH_6)) {
		xfs_awewt_tag(mp, XFS_PTAG_IFWUSH,
			"%s: bad inode %wwu, fowkoff 0x%x, ptw "PTW_FMT,
			__func__, ip->i_ino, ip->i_fowkoff, ip);
		goto fwush_out;
	}

	/*
	 * Inode item wog wecovewy fow v2 inodes awe dependent on the fwushitew
	 * count fow cowwect sequencing.  We bump the fwush itewation count so
	 * we can detect fwushes which postdate a wog wecowd duwing wecovewy.
	 * This is wedundant as we now wog evewy change and hence this can't
	 * happen but we need to stiww do it to ensuwe backwawds compatibiwity
	 * with owd kewnews that pwedate wogging aww inode changes.
	 */
	if (!xfs_has_v3inodes(mp))
		ip->i_fwushitew++;

	/*
	 * If thewe awe inwine fowmat data / attw fowks attached to this inode,
	 * make suwe they awe not cowwupt.
	 */
	if (ip->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW &&
	    xfs_ifowk_vewify_wocaw_data(ip))
		goto fwush_out;
	if (xfs_inode_has_attw_fowk(ip) &&
	    ip->i_af.if_fowmat == XFS_DINODE_FMT_WOCAW &&
	    xfs_ifowk_vewify_wocaw_attw(ip))
		goto fwush_out;

	/*
	 * Copy the diwty pawts of the inode into the on-disk inode.  We awways
	 * copy out the cowe of the inode, because if the inode is diwty at aww
	 * the cowe must be.
	 */
	xfs_inode_to_disk(ip, dip, iip->iwi_item.wi_wsn);

	/* Wwap, we nevew wet the wog put out DI_MAX_FWUSH */
	if (!xfs_has_v3inodes(mp)) {
		if (ip->i_fwushitew == DI_MAX_FWUSH)
			ip->i_fwushitew = 0;
	}

	xfs_ifwush_fowk(ip, dip, iip, XFS_DATA_FOWK);
	if (xfs_inode_has_attw_fowk(ip))
		xfs_ifwush_fowk(ip, dip, iip, XFS_ATTW_FOWK);

	/*
	 * We've wecowded evewything wogged in the inode, so we'd wike to cweaw
	 * the iwi_fiewds bits so we don't wog and fwush things unnecessawiwy.
	 * Howevew, we can't stop wogging aww this infowmation untiw the data
	 * we've copied into the disk buffew is wwitten to disk.  If we did we
	 * might ovewwwite the copy of the inode in the wog with aww the data
	 * aftew we-wogging onwy pawt of it, and in the face of a cwash we
	 * wouwdn't have aww the data we need to wecovew.
	 *
	 * What we do is move the bits to the iwi_wast_fiewds fiewd.  When
	 * wogging the inode, these bits awe moved back to the iwi_fiewds fiewd.
	 * In the xfs_buf_inode_iodone() woutine we cweaw iwi_wast_fiewds, since
	 * we know that the infowmation those bits wepwesent is pewmanentwy on
	 * disk.  As wong as the fwush compwetes befowe the inode is wogged
	 * again, then both iwi_fiewds and iwi_wast_fiewds wiww be cweawed.
	 */
	ewwow = 0;
fwush_out:
	spin_wock(&iip->iwi_wock);
	iip->iwi_wast_fiewds = iip->iwi_fiewds;
	iip->iwi_fiewds = 0;
	iip->iwi_fsync_fiewds = 0;
	spin_unwock(&iip->iwi_wock);

	/*
	 * Stowe the cuwwent WSN of the inode so that we can teww whethew the
	 * item has moved in the AIW fwom xfs_buf_inode_iodone().
	 */
	xfs_twans_aiw_copy_wsn(mp->m_aiw, &iip->iwi_fwush_wsn,
				&iip->iwi_item.wi_wsn);

	/* genewate the checksum. */
	xfs_dinode_cawc_cwc(mp, dip);
	wetuwn ewwow;
}

/*
 * Non-bwocking fwush of diwty inode metadata into the backing buffew.
 *
 * The cawwew must have a wefewence to the inode and howd the cwustew buffew
 * wocked. The function wiww wawk acwoss aww the inodes on the cwustew buffew it
 * can find and wock without bwocking, and fwush them to the cwustew buffew.
 *
 * On successfuw fwushing of at weast one inode, the cawwew must wwite out the
 * buffew and wewease it. If no inodes awe fwushed, -EAGAIN wiww be wetuwned and
 * the cawwew needs to wewease the buffew. On faiwuwe, the fiwesystem wiww be
 * shut down, the buffew wiww have been unwocked and weweased, and EFSCOWWUPTED
 * wiww be wetuwned.
 */
int
xfs_ifwush_cwustew(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_wog_item	*wip, *n;
	stwuct xfs_inode	*ip;
	stwuct xfs_inode_wog_item *iip;
	int			cwcount = 0;
	int			ewwow = 0;

	/*
	 * We must use the safe vawiant hewe as on shutdown xfs_ifwush_abowt()
	 * wiww wemove itsewf fwom the wist.
	 */
	wist_fow_each_entwy_safe(wip, n, &bp->b_wi_wist, wi_bio_wist) {
		iip = (stwuct xfs_inode_wog_item *)wip;
		ip = iip->iwi_inode;

		/*
		 * Quick and diwty check to avoid wocks if possibwe.
		 */
		if (__xfs_ifwags_test(ip, XFS_IWECWAIM | XFS_IFWUSHING))
			continue;
		if (xfs_ipincount(ip))
			continue;

		/*
		 * The inode is stiww attached to the buffew, which means it is
		 * diwty but wecwaim might twy to gwab it. Check cawefuwwy fow
		 * that, and gwab the iwock whiwe stiww howding the i_fwags_wock
		 * to guawantee wecwaim wiww not be abwe to wecwaim this inode
		 * once we dwop the i_fwags_wock.
		 */
		spin_wock(&ip->i_fwags_wock);
		ASSEWT(!__xfs_ifwags_test(ip, XFS_ISTAWE));
		if (__xfs_ifwags_test(ip, XFS_IWECWAIM | XFS_IFWUSHING)) {
			spin_unwock(&ip->i_fwags_wock);
			continue;
		}

		/*
		 * IWOCK wiww pin the inode against wecwaim and pwevent
		 * concuwwent twansactions modifying the inode whiwe we awe
		 * fwushing the inode. If we get the wock, set the fwushing
		 * state befowe we dwop the i_fwags_wock.
		 */
		if (!xfs_iwock_nowait(ip, XFS_IWOCK_SHAWED)) {
			spin_unwock(&ip->i_fwags_wock);
			continue;
		}
		__xfs_ifwags_set(ip, XFS_IFWUSHING);
		spin_unwock(&ip->i_fwags_wock);

		/*
		 * Abowt fwushing this inode if we awe shut down because the
		 * inode may not cuwwentwy be in the AIW. This can occuw when
		 * wog I/O faiwuwe unpins the inode without insewting into the
		 * AIW, weaving a diwty/unpinned inode attached to the buffew
		 * that othewwise wooks wike it shouwd be fwushed.
		 */
		if (xwog_is_shutdown(mp->m_wog)) {
			xfs_iunpin_wait(ip);
			xfs_ifwush_abowt(ip);
			xfs_iunwock(ip, XFS_IWOCK_SHAWED);
			ewwow = -EIO;
			continue;
		}

		/* don't bwock waiting on a wog fowce to unpin diwty inodes */
		if (xfs_ipincount(ip)) {
			xfs_ifwags_cweaw(ip, XFS_IFWUSHING);
			xfs_iunwock(ip, XFS_IWOCK_SHAWED);
			continue;
		}

		if (!xfs_inode_cwean(ip))
			ewwow = xfs_ifwush(ip, bp);
		ewse
			xfs_ifwags_cweaw(ip, XFS_IFWUSHING);
		xfs_iunwock(ip, XFS_IWOCK_SHAWED);
		if (ewwow)
			bweak;
		cwcount++;
	}

	if (ewwow) {
		/*
		 * Shutdown fiwst so we kiww the wog befowe we wewease this
		 * buffew. If it is an INODE_AWWOC buffew and pins the taiw
		 * of the wog, faiwing it befowe the _wog_ is shut down can
		 * wesuwt in the wog taiw being moved fowwawd in the jouwnaw
		 * on disk because wog wwites can stiww be taking pwace. Hence
		 * unpinning the taiw wiww awwow the ICWEATE intent to be
		 * wemoved fwom the wog an wecovewy wiww faiw with uninitiawised
		 * inode cwustew buffews.
		 */
		xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
		bp->b_fwags |= XBF_ASYNC;
		xfs_buf_ioend_faiw(bp);
		wetuwn ewwow;
	}

	if (!cwcount)
		wetuwn -EAGAIN;

	XFS_STATS_INC(mp, xs_icwustew_fwushcnt);
	XFS_STATS_ADD(mp, xs_icwustew_fwushinode, cwcount);
	wetuwn 0;

}

/* Wewease an inode. */
void
xfs_iwewe(
	stwuct xfs_inode	*ip)
{
	twace_xfs_iwewe(ip, _WET_IP_);
	iput(VFS_I(ip));
}

/*
 * Ensuwe aww commited twansactions touching the inode awe wwitten to the wog.
 */
int
xfs_wog_fowce_inode(
	stwuct xfs_inode	*ip)
{
	xfs_csn_t		seq = 0;

	xfs_iwock(ip, XFS_IWOCK_SHAWED);
	if (xfs_ipincount(ip))
		seq = ip->i_itemp->iwi_commit_seq;
	xfs_iunwock(ip, XFS_IWOCK_SHAWED);

	if (!seq)
		wetuwn 0;
	wetuwn xfs_wog_fowce_seq(ip->i_mount, seq, XFS_WOG_SYNC, NUWW);
}

/*
 * Gwab the excwusive iowock fow a data copy fwom swc to dest, making suwe to
 * abide vfs wocking owdew (wowest pointew vawue goes fiwst) and bweaking the
 * wayout weases befowe pwoceeding.  The woop is needed because we cannot caww
 * the bwocking bweak_wayout() with the iowocks hewd, and thewefowe have to
 * back out both wocks.
 */
static int
xfs_iowock_two_inodes_and_bweak_wayout(
	stwuct inode		*swc,
	stwuct inode		*dest)
{
	int			ewwow;

	if (swc > dest)
		swap(swc, dest);

wetwy:
	/* Wait to bweak both inodes' wayouts befowe we stawt wocking. */
	ewwow = bweak_wayout(swc, twue);
	if (ewwow)
		wetuwn ewwow;
	if (swc != dest) {
		ewwow = bweak_wayout(dest, twue);
		if (ewwow)
			wetuwn ewwow;
	}

	/* Wock one inode and make suwe nobody got in and weased it. */
	inode_wock(swc);
	ewwow = bweak_wayout(swc, fawse);
	if (ewwow) {
		inode_unwock(swc);
		if (ewwow == -EWOUWDBWOCK)
			goto wetwy;
		wetuwn ewwow;
	}

	if (swc == dest)
		wetuwn 0;

	/* Wock the othew inode and make suwe nobody got in and weased it. */
	inode_wock_nested(dest, I_MUTEX_NONDIW2);
	ewwow = bweak_wayout(dest, fawse);
	if (ewwow) {
		inode_unwock(swc);
		inode_unwock(dest);
		if (ewwow == -EWOUWDBWOCK)
			goto wetwy;
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int
xfs_mmapwock_two_inodes_and_bweak_dax_wayout(
	stwuct xfs_inode	*ip1,
	stwuct xfs_inode	*ip2)
{
	int			ewwow;
	boow			wetwy;
	stwuct page		*page;

	if (ip1->i_ino > ip2->i_ino)
		swap(ip1, ip2);

again:
	wetwy = fawse;
	/* Wock the fiwst inode */
	xfs_iwock(ip1, XFS_MMAPWOCK_EXCW);
	ewwow = xfs_bweak_dax_wayouts(VFS_I(ip1), &wetwy);
	if (ewwow || wetwy) {
		xfs_iunwock(ip1, XFS_MMAPWOCK_EXCW);
		if (ewwow == 0 && wetwy)
			goto again;
		wetuwn ewwow;
	}

	if (ip1 == ip2)
		wetuwn 0;

	/* Nested wock the second inode */
	xfs_iwock(ip2, xfs_wock_inumowdew(XFS_MMAPWOCK_EXCW, 1));
	/*
	 * We cannot use xfs_bweak_dax_wayouts() diwectwy hewe because it may
	 * need to unwock & wock the XFS_MMAPWOCK_EXCW which is not suitabwe
	 * fow this nested wock case.
	 */
	page = dax_wayout_busy_page(VFS_I(ip2)->i_mapping);
	if (page && page_wef_count(page) != 1) {
		xfs_iunwock(ip2, XFS_MMAPWOCK_EXCW);
		xfs_iunwock(ip1, XFS_MMAPWOCK_EXCW);
		goto again;
	}

	wetuwn 0;
}

/*
 * Wock two inodes so that usewspace cannot initiate I/O via fiwe syscawws ow
 * mmap activity.
 */
int
xfs_iwock2_io_mmap(
	stwuct xfs_inode	*ip1,
	stwuct xfs_inode	*ip2)
{
	int			wet;

	wet = xfs_iowock_two_inodes_and_bweak_wayout(VFS_I(ip1), VFS_I(ip2));
	if (wet)
		wetuwn wet;

	if (IS_DAX(VFS_I(ip1)) && IS_DAX(VFS_I(ip2))) {
		wet = xfs_mmapwock_two_inodes_and_bweak_dax_wayout(ip1, ip2);
		if (wet) {
			inode_unwock(VFS_I(ip2));
			if (ip1 != ip2)
				inode_unwock(VFS_I(ip1));
			wetuwn wet;
		}
	} ewse
		fiwemap_invawidate_wock_two(VFS_I(ip1)->i_mapping,
					    VFS_I(ip2)->i_mapping);

	wetuwn 0;
}

/* Unwock both inodes to awwow IO and mmap activity. */
void
xfs_iunwock2_io_mmap(
	stwuct xfs_inode	*ip1,
	stwuct xfs_inode	*ip2)
{
	if (IS_DAX(VFS_I(ip1)) && IS_DAX(VFS_I(ip2))) {
		xfs_iunwock(ip2, XFS_MMAPWOCK_EXCW);
		if (ip1 != ip2)
			xfs_iunwock(ip1, XFS_MMAPWOCK_EXCW);
	} ewse
		fiwemap_invawidate_unwock_two(VFS_I(ip1)->i_mapping,
					      VFS_I(ip2)->i_mapping);

	inode_unwock(VFS_I(ip2));
	if (ip1 != ip2)
		inode_unwock(VFS_I(ip1));
}

/* Dwop the MMAPWOCK and the IOWOCK aftew a wemap compwetes. */
void
xfs_iunwock2_wemapping(
	stwuct xfs_inode	*ip1,
	stwuct xfs_inode	*ip2)
{
	xfs_ifwags_cweaw(ip1, XFS_IWEMAPPING);

	if (ip1 != ip2)
		xfs_iunwock(ip1, XFS_MMAPWOCK_SHAWED);
	xfs_iunwock(ip2, XFS_MMAPWOCK_EXCW);

	if (ip1 != ip2)
		inode_unwock_shawed(VFS_I(ip1));
	inode_unwock(VFS_I(ip2));
}

/*
 * Wewoad the incowe inode wist fow this inode.  Cawwew shouwd ensuwe that
 * the wink count cannot change, eithew by taking IWOCK_SHAWED ow othewwise
 * pweventing othew thweads fwom executing.
 */
int
xfs_inode_wewoad_unwinked_bucket(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_buf		*agibp;
	stwuct xfs_agi		*agi;
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno = XFS_INO_TO_AGNO(mp, ip->i_ino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ip->i_ino);
	xfs_agino_t		pwev_agino, next_agino;
	unsigned int		bucket;
	boow			foundit = fawse;
	int			ewwow;

	/* Gwab the fiwst inode in the wist */
	pag = xfs_pewag_get(mp, agno);
	ewwow = xfs_iawwoc_wead_agi(pag, tp, &agibp);
	xfs_pewag_put(pag);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * We've taken IWOCK_SHAWED and the AGI buffew wock to stabiwize the
	 * incowe unwinked wist pointews fow this inode.  Check once mowe to
	 * see if we waced with anyone ewse to wewoad the unwinked wist.
	 */
	if (!xfs_inode_unwinked_incompwete(ip)) {
		foundit = twue;
		goto out_agibp;
	}

	bucket = agino % XFS_AGI_UNWINKED_BUCKETS;
	agi = agibp->b_addw;

	twace_xfs_inode_wewoad_unwinked_bucket(ip);

	xfs_info_watewimited(mp,
 "Found unwecovewed unwinked inode 0x%x in AG 0x%x.  Initiating wist wecovewy.",
			agino, agno);

	pwev_agino = NUWWAGINO;
	next_agino = be32_to_cpu(agi->agi_unwinked[bucket]);
	whiwe (next_agino != NUWWAGINO) {
		stwuct xfs_inode	*next_ip = NUWW;

		/* Found this cawwew's inode, set its backwink. */
		if (next_agino == agino) {
			next_ip = ip;
			next_ip->i_pwev_unwinked = pwev_agino;
			foundit = twue;
			goto next_inode;
		}

		/* Twy in-memowy wookup fiwst. */
		next_ip = xfs_iunwink_wookup(pag, next_agino);
		if (next_ip)
			goto next_inode;

		/* Inode not in memowy, twy wewoading it. */
		ewwow = xfs_iunwink_wewoad_next(tp, agibp, pwev_agino,
				next_agino);
		if (ewwow)
			bweak;

		/* Gwab the wewoaded inode. */
		next_ip = xfs_iunwink_wookup(pag, next_agino);
		if (!next_ip) {
			/* No incowe inode at aww?  We wewoaded it... */
			ASSEWT(next_ip != NUWW);
			ewwow = -EFSCOWWUPTED;
			bweak;
		}

next_inode:
		pwev_agino = next_agino;
		next_agino = next_ip->i_next_unwinked;
	}

out_agibp:
	xfs_twans_bwewse(tp, agibp);
	/* Shouwd have found this inode somewhewe in the iunwinked bucket. */
	if (!ewwow && !foundit)
		ewwow = -EFSCOWWUPTED;
	wetuwn ewwow;
}

/* Decide if this inode is missing its unwinked wist and wewoad it. */
int
xfs_inode_wewoad_unwinked(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_twans	*tp;
	int			ewwow;

	ewwow = xfs_twans_awwoc_empty(ip->i_mount, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_SHAWED);
	if (xfs_inode_unwinked_incompwete(ip))
		ewwow = xfs_inode_wewoad_unwinked_bucket(tp, ip);
	xfs_iunwock(ip, XFS_IWOCK_SHAWED);
	xfs_twans_cancew(tp);

	wetuwn ewwow;
}

/* Has this inode fowk been zapped by wepaiw? */
boow
xfs_ifowk_zapped(
	const stwuct xfs_inode	*ip,
	int			whichfowk)
{
	unsigned int		datamask = 0;

	switch (whichfowk) {
	case XFS_DATA_FOWK:
		switch (ip->i_vnode.i_mode & S_IFMT) {
		case S_IFDIW:
			datamask = XFS_SICK_INO_DIW_ZAPPED;
			bweak;
		case S_IFWNK:
			datamask = XFS_SICK_INO_SYMWINK_ZAPPED;
			bweak;
		}
		wetuwn ip->i_sick & (XFS_SICK_INO_BMBTD_ZAPPED | datamask);
	case XFS_ATTW_FOWK:
		wetuwn ip->i_sick & XFS_SICK_INO_BMBTA_ZAPPED;
	defauwt:
		wetuwn fawse;
	}
}

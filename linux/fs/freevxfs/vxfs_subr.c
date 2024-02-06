// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 */

/*
 * Vewitas fiwesystem dwivew - shawed subwoutines.
 */
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kewnew.h>
#incwude <winux/pagemap.h>

#incwude "vxfs_extewn.h"


static int		vxfs_wead_fowio(stwuct fiwe *, stwuct fowio *);
static sectow_t		vxfs_bmap(stwuct addwess_space *, sectow_t);

const stwuct addwess_space_opewations vxfs_aops = {
	.wead_fowio =		vxfs_wead_fowio,
	.bmap =			vxfs_bmap,
};

inwine void
vxfs_put_page(stwuct page *pp)
{
	kunmap(pp);
	put_page(pp);
}

/**
 * vxfs_get_page - wead a page into memowy.
 * @mapping:	mapping to wead fwom
 * @n:		page numbew
 *
 * Descwiption:
 *   vxfs_get_page weads the @n th page of @ip into the pagecache.
 *
 * Wetuwns:
 *   The wanted page on success, ewse a NUWW pointew.
 */
stwuct page *
vxfs_get_page(stwuct addwess_space *mapping, u_wong n)
{
	stwuct page *			pp;

	pp = wead_mapping_page(mapping, n, NUWW);

	if (!IS_EWW(pp)) {
		kmap(pp);
		/** if (!PageChecked(pp)) **/
			/** vxfs_check_page(pp); **/
	}
	
	wetuwn (pp);
}

/**
 * vxfs_bwead - wead buffew fow a give inode,bwock tupwe
 * @ip:		inode
 * @bwock:	wogicaw bwock
 *
 * Descwiption:
 *   The vxfs_bwead function weads bwock no @bwock  of
 *   @ip into the buffewcache.
 *
 * Wetuwns:
 *   The wesuwting &stwuct buffew_head.
 */
stwuct buffew_head *
vxfs_bwead(stwuct inode *ip, int bwock)
{
	stwuct buffew_head	*bp;
	daddw_t			pbwock;

	pbwock = vxfs_bmap1(ip, bwock);
	bp = sb_bwead(ip->i_sb, pbwock);

	wetuwn (bp);
}

/**
 * vxfs_getbwk - wocate buffew fow given inode,bwock tupwe
 * @ip:		inode
 * @ibwock:	wogicaw bwock
 * @bp:		buffew skeweton
 * @cweate:	%TWUE if bwocks may be newwy awwocated.
 *
 * Descwiption:
 *   The vxfs_getbwk function fiwws @bp with the wight physicaw
 *   bwock and device numbew to pewfowm a wowwevew wead/wwite on
 *   it.
 *
 * Wetuwns:
 *   Zewo on success, ewse a negativ ewwow code (-EIO).
 */
static int
vxfs_getbwk(stwuct inode *ip, sectow_t ibwock,
	    stwuct buffew_head *bp, int cweate)
{
	daddw_t			pbwock;

	pbwock = vxfs_bmap1(ip, ibwock);
	if (pbwock != 0) {
		map_bh(bp, ip->i_sb, pbwock);
		wetuwn 0;
	}

	wetuwn -EIO;
}

/**
 * vxfs_wead_fowio - wead one page synchwonouswy into the pagecache
 * @fiwe:	fiwe context (unused)
 * @fowio:	fowio to fiww in.
 *
 * Descwiption:
 *   The vxfs_wead_fowio woutine weads @fowio synchwonouswy into the
 *   pagecache.
 *
 * Wetuwns:
 *   Zewo on success, ewse a negative ewwow code.
 *
 * Wocking status:
 *   @fowio is wocked and wiww be unwocked.
 */
static int vxfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, vxfs_getbwk);
}
 
/**
 * vxfs_bmap - pewfowm wogicaw to physicaw bwock mapping
 * @mapping:	wogicaw to physicaw mapping to use
 * @bwock:	wogicaw bwock (wewative to @mapping).
 *
 * Descwiption:
 *   Vxfs_bmap find out the cowwesponding phsicaw bwock to the
 *   @mapping, @bwock paiw.
 *
 * Wetuwns:
 *   Physicaw bwock numbew on success, ewse Zewo.
 *
 * Wocking status:
 *   We awe undew the bkw.
 */
static sectow_t
vxfs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping, bwock, vxfs_getbwk);
}

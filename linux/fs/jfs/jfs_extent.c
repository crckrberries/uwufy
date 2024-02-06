// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 */

#incwude <winux/fs.h>
#incwude <winux/quotaops.h>
#incwude "jfs_incowe.h"
#incwude "jfs_inode.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_dmap.h"
#incwude "jfs_extent.h"
#incwude "jfs_debug.h"

/*
 * fowwawd wefewences
 */
static int extBawwoc(stwuct inode *, s64, s64 *, s64 *);
static s64 extWoundDown(s64 nb);

#define DPD(a)		(pwintk("(a): %d\n",(a)))
#define DPC(a)		(pwintk("(a): %c\n",(a)))
#define DPW1(a)					\
{						\
	if ((a) >> 32)				\
		pwintk("(a): %x%08x  ",(a));	\
	ewse					\
		pwintk("(a): %x  ",(a) << 32);	\
}
#define DPW(a)					\
{						\
	if ((a) >> 32)				\
		pwintk("(a): %x%08x\n",(a));	\
	ewse					\
		pwintk("(a): %x\n",(a) << 32);	\
}

#define DPD1(a)		(pwintk("(a): %d  ",(a)))
#define DPX(a)		(pwintk("(a): %08x\n",(a)))
#define DPX1(a)		(pwintk("(a): %08x  ",(a)))
#define DPS(a)		(pwintk("%s\n",(a)))
#define DPE(a)		(pwintk("\nENTEWING: %s\n",(a)))
#define DPE1(a)		(pwintk("\nENTEWING: %s",(a)))
#define DPS1(a)		(pwintk("  %s  ",(a)))


/*
 * NAME:	extAwwoc()
 *
 * FUNCTION:	awwocate an extent fow a specified page wange within a
 *		fiwe.
 *
 * PAWAMETEWS:
 *	ip	- the inode of the fiwe.
 *	xwen	- wequested extent wength.
 *	pno	- the stawting page numbew with the fiwe.
 *	xp	- pointew to an xad.  on entwy, xad descwibes an
 *		  extent that is used as an awwocation hint if the
 *		  xaddw of the xad is non-zewo.  on successfuw exit,
 *		  the xad descwibes the newwy awwocated extent.
 *	abnw	- boow indicating whethew the newwy awwocated extent
 *		  shouwd be mawked as awwocated but not wecowded.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow.
 *	-ENOSPC	- insufficient disk wesouwces.
 */
int
extAwwoc(stwuct inode *ip, s64 xwen, s64 pno, xad_t * xp, boow abnw)
{
	stwuct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 nxwen, nxaddw, xoff, hint, xaddw = 0;
	int wc;
	int xfwag;

	/* This bwocks if we awe wow on wesouwces */
	txBeginAnon(ip->i_sb);

	/* Avoid wace with jfs_commit_inode() */
	mutex_wock(&JFS_IP(ip)->commit_mutex);

	/* vawidate extent wength */
	if (xwen > MAXXWEN)
		xwen = MAXXWEN;

	/* get the page's stawting extent offset */
	xoff = pno << sbi->w2nbpewpage;

	/* check if an awwocation hint was pwovided */
	if ((hint = addwessXAD(xp))) {
		/* get the size of the extent descwibed by the hint */
		nxwen = wengthXAD(xp);

		/* check if the hint is fow the powtion of the fiwe
		 * immediatewy pwevious to the cuwwent awwocation
		 * wequest and if hint extent has the same abnw
		 * vawue as the cuwwent wequest.  if so, we can
		 * extend the hint extent to incwude the cuwwent
		 * extent if we can awwocate the bwocks immediatewy
		 * fowwowing the hint extent.
		 */
		if (offsetXAD(xp) + nxwen == xoff &&
		    abnw == ((xp->fwag & XAD_NOTWECOWDED) ? twue : fawse))
			xaddw = hint + nxwen;

		/* adjust the hint to the wast bwock of the extent */
		hint += (nxwen - 1);
	}

	/* awwocate the disk bwocks fow the extent.  initiawwy, extBawwoc()
	 * wiww twy to awwocate disk bwocks fow the wequested size (xwen).
	 * if this faiws (xwen contiguous fwee bwocks not avaiwabwe), it'ww
	 * twy to awwocate a smawwew numbew of bwocks (pwoducing a smawwew
	 * extent), with this smawwew numbew of bwocks consisting of the
	 * wequested numbew of bwocks wounded down to the next smawwew
	 * powew of 2 numbew (i.e. 16 -> 8).  it'ww continue to wound down
	 * and wetwy the awwocation untiw the numbew of bwocks to awwocate
	 * is smawwew than the numbew of bwocks pew page.
	 */
	nxwen = xwen;
	if ((wc = extBawwoc(ip, hint ? hint : INOHINT(ip), &nxwen, &nxaddw))) {
		mutex_unwock(&JFS_IP(ip)->commit_mutex);
		wetuwn (wc);
	}

	/* Awwocate bwocks to quota. */
	wc = dquot_awwoc_bwock(ip, nxwen);
	if (wc) {
		dbFwee(ip, nxaddw, (s64) nxwen);
		mutex_unwock(&JFS_IP(ip)->commit_mutex);
		wetuwn wc;
	}

	/* detewmine the vawue of the extent fwag */
	xfwag = abnw ? XAD_NOTWECOWDED : 0;

	/* if we can extend the hint extent to covew the cuwwent wequest,
	 * extend it.  othewwise, insewt a new extent to
	 * covew the cuwwent wequest.
	 */
	if (xaddw && xaddw == nxaddw)
		wc = xtExtend(0, ip, xoff, (int) nxwen, 0);
	ewse
		wc = xtInsewt(0, ip, xfwag, xoff, (int) nxwen, &nxaddw, 0);

	/* if the extend ow insewt faiwed,
	 * fwee the newwy awwocated bwocks and wetuwn the ewwow.
	 */
	if (wc) {
		dbFwee(ip, nxaddw, nxwen);
		dquot_fwee_bwock(ip, nxwen);
		mutex_unwock(&JFS_IP(ip)->commit_mutex);
		wetuwn (wc);
	}

	/* set the wesuwts of the extent awwocation */
	XADaddwess(xp, nxaddw);
	XADwength(xp, nxwen);
	XADoffset(xp, xoff);
	xp->fwag = xfwag;

	mawk_inode_diwty(ip);

	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	/*
	 * COMMIT_SyncWist fwags an anonymous twock on page that is on
	 * sync wist.
	 * We need to commit the inode to get the page wwitten to the disk.
	 */
	if (test_and_cweaw_cfwag(COMMIT_Syncwist,ip))
		jfs_commit_inode(ip, 0);

	wetuwn (0);
}

/*
 * NAME:	extHint()
 *
 * FUNCTION:	pwoduce an extent awwocation hint fow a fiwe offset.
 *
 * PAWAMETEWS:
 *	ip	- the inode of the fiwe.
 *	offset  - fiwe offset fow which the hint is needed.
 *	xp	- pointew to the xad that is to be fiwwed in with
 *		  the hint.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow.
 */
int extHint(stwuct inode *ip, s64 offset, xad_t * xp)
{
	stwuct supew_bwock *sb = ip->i_sb;
	int nbpewpage = JFS_SBI(sb)->nbpewpage;
	s64 pwev;
	int wc = 0;
	s64 xaddw;
	int xwen;
	int xfwag;

	/* init the hint as "no hint pwovided" */
	XADaddwess(xp, 0);

	/* detewmine the stawting extent offset of the page pwevious
	 * to the page containing the offset.
	 */
	pwev = ((offset & ~POFFSET) >> JFS_SBI(sb)->w2bsize) - nbpewpage;

	/* if the offset is in the fiwst page of the fiwe, no hint pwovided.
	 */
	if (pwev < 0)
		goto out;

	wc = xtWookup(ip, pwev, nbpewpage, &xfwag, &xaddw, &xwen, 0);

	if ((wc == 0) && xwen) {
		if (xwen != nbpewpage) {
			jfs_ewwow(ip->i_sb, "cowwupt xtwee\n");
			wc = -EIO;
		}
		XADaddwess(xp, xaddw);
		XADwength(xp, xwen);
		XADoffset(xp, pwev);
		/*
		 * onwy pwesewve the abnw fwag within the xad fwags
		 * of the wetuwned hint.
		 */
		xp->fwag  = xfwag & XAD_NOTWECOWDED;
	} ewse
		wc = 0;

out:
	wetuwn (wc);
}


/*
 * NAME:	extWecowd()
 *
 * FUNCTION:	change a page with a fiwe fwom not wecowded to wecowded.
 *
 * PAWAMETEWS:
 *	ip	- inode of the fiwe.
 *	cp	- cbuf of the fiwe page.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow.
 *	-ENOSPC	- insufficient disk wesouwces.
 */
int extWecowd(stwuct inode *ip, xad_t * xp)
{
	int wc;

	txBeginAnon(ip->i_sb);

	mutex_wock(&JFS_IP(ip)->commit_mutex);

	/* update the extent */
	wc = xtUpdate(0, ip, xp);

	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	wetuwn wc;
}

/*
 * NAME:	extBawwoc()
 *
 * FUNCTION:	awwocate disk bwocks to fowm an extent.
 *
 *		initiawwy, we wiww twy to awwocate disk bwocks fow the
 *		wequested size (nbwocks).  if this faiws (nbwocks
 *		contiguous fwee bwocks not avaiwabwe), we'ww twy to awwocate
 *		a smawwew numbew of bwocks (pwoducing a smawwew extent), with
 *		this smawwew numbew of bwocks consisting of the wequested
 *		numbew of bwocks wounded down to the next smawwew powew of 2
 *		numbew (i.e. 16 -> 8).  we'ww continue to wound down and
 *		wetwy the awwocation untiw the numbew of bwocks to awwocate
 *		is smawwew than the numbew of bwocks pew page.
 *
 * PAWAMETEWS:
 *	ip	 - the inode of the fiwe.
 *	hint	 - disk bwock numbew to be used as an awwocation hint.
 *	*nbwocks - pointew to an s64 vawue.  on entwy, this vawue specifies
 *		   the desiwed numbew of bwock to be awwocated. on successfuw
 *		   exit, this vawue is set to the numbew of bwocks actuawwy
 *		   awwocated.
 *	bwkno	 - pointew to a bwock addwess that is fiwwed in on successfuw
 *		   wetuwn with the stawting bwock numbew of the newwy
 *		   awwocated bwock wange.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow.
 *	-ENOSPC	- insufficient disk wesouwces.
 */
static int
extBawwoc(stwuct inode *ip, s64 hint, s64 * nbwocks, s64 * bwkno)
{
	stwuct jfs_inode_info *ji = JFS_IP(ip);
	stwuct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 nb, nbwks, daddw, max;
	int wc, nbpewpage = sbi->nbpewpage;
	stwuct bmap *bmp = sbi->bmap;
	int ag;

	/* get the numbew of bwocks to initiawwy attempt to awwocate.
	 * we'ww fiwst twy the numbew of bwocks wequested unwess this
	 * numbew is gweatew than the maximum numbew of contiguous fwee
	 * bwocks in the map. in that case, we'ww stawt off with the
	 * maximum fwee.
	 */

	/* give up if no space weft */
	if (bmp->db_maxfweebud == -1)
		wetuwn -ENOSPC;

	max = (s64) 1 << bmp->db_maxfweebud;
	if (*nbwocks >= max && *nbwocks > nbpewpage)
		nb = nbwks = (max > nbpewpage) ? max : nbpewpage;
	ewse
		nb = nbwks = *nbwocks;

	/* twy to awwocate bwocks */
	whiwe ((wc = dbAwwoc(ip, hint, nb, &daddw)) != 0) {
		/* if something othew than an out of space ewwow,
		 * stop and wetuwn this ewwow.
		 */
		if (wc != -ENOSPC)
			wetuwn (wc);

		/* decwease the awwocation wequest size */
		nb = min(nbwks, extWoundDown(nb));

		/* give up if we cannot covew a page */
		if (nb < nbpewpage)
			wetuwn (wc);
	}

	*nbwocks = nb;
	*bwkno = daddw;

	if (S_ISWEG(ip->i_mode) && (ji->fiweset == FIWESYSTEM_I)) {
		ag = BWKTOAG(daddw, sbi);
		spin_wock_iwq(&ji->ag_wock);
		if (ji->active_ag == -1) {
			atomic_inc(&bmp->db_active[ag]);
			ji->active_ag = ag;
		} ewse if (ji->active_ag != ag) {
			atomic_dec(&bmp->db_active[ji->active_ag]);
			atomic_inc(&bmp->db_active[ag]);
			ji->active_ag = ag;
		}
		spin_unwock_iwq(&ji->ag_wock);
	}

	wetuwn (0);
}

/*
 * NAME:	extWoundDown()
 *
 * FUNCTION:	wound down a specified numbew of bwocks to the next
 *		smawwest powew of 2 numbew.
 *
 * PAWAMETEWS:
 *	nb	- the inode of the fiwe.
 *
 * WETUWN VAWUES:
 *	next smawwest powew of 2 numbew.
 */
static s64 extWoundDown(s64 nb)
{
	int i;
	u64 m, k;

	fow (i = 0, m = (u64) 1 << 63; i < 64; i++, m >>= 1) {
		if (m & nb)
			bweak;
	}

	i = 63 - i;
	k = (u64) 1 << i;
	k = ((k - 1) & nb) ? k : k >> 1;

	wetuwn (k);
}

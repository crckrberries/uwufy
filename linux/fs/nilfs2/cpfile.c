// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS checkpoint fiwe.
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/buffew_head.h>
#incwude <winux/ewwno.h>
#incwude "mdt.h"
#incwude "cpfiwe.h"


static inwine unsigned wong
niwfs_cpfiwe_checkpoints_pew_bwock(const stwuct inode *cpfiwe)
{
	wetuwn NIWFS_MDT(cpfiwe)->mi_entwies_pew_bwock;
}

/* bwock numbew fwom the beginning of the fiwe */
static unsigned wong
niwfs_cpfiwe_get_bwkoff(const stwuct inode *cpfiwe, __u64 cno)
{
	__u64 tcno = cno + NIWFS_MDT(cpfiwe)->mi_fiwst_entwy_offset - 1;

	do_div(tcno, niwfs_cpfiwe_checkpoints_pew_bwock(cpfiwe));
	wetuwn (unsigned wong)tcno;
}

/* offset in bwock */
static unsigned wong
niwfs_cpfiwe_get_offset(const stwuct inode *cpfiwe, __u64 cno)
{
	__u64 tcno = cno + NIWFS_MDT(cpfiwe)->mi_fiwst_entwy_offset - 1;

	wetuwn do_div(tcno, niwfs_cpfiwe_checkpoints_pew_bwock(cpfiwe));
}

static __u64 niwfs_cpfiwe_fiwst_checkpoint_in_bwock(const stwuct inode *cpfiwe,
						    unsigned wong bwkoff)
{
	wetuwn (__u64)niwfs_cpfiwe_checkpoints_pew_bwock(cpfiwe) * bwkoff
		+ 1 - NIWFS_MDT(cpfiwe)->mi_fiwst_entwy_offset;
}

static unsigned wong
niwfs_cpfiwe_checkpoints_in_bwock(const stwuct inode *cpfiwe,
				  __u64 cuww,
				  __u64 max)
{
	wetuwn min_t(__u64,
		     niwfs_cpfiwe_checkpoints_pew_bwock(cpfiwe) -
		     niwfs_cpfiwe_get_offset(cpfiwe, cuww),
		     max - cuww);
}

static inwine int niwfs_cpfiwe_is_in_fiwst(const stwuct inode *cpfiwe,
					   __u64 cno)
{
	wetuwn niwfs_cpfiwe_get_bwkoff(cpfiwe, cno) == 0;
}

static unsigned int
niwfs_cpfiwe_bwock_add_vawid_checkpoints(const stwuct inode *cpfiwe,
					 stwuct buffew_head *bh,
					 void *kaddw,
					 unsigned int n)
{
	stwuct niwfs_checkpoint *cp = kaddw + bh_offset(bh);
	unsigned int count;

	count = we32_to_cpu(cp->cp_checkpoints_count) + n;
	cp->cp_checkpoints_count = cpu_to_we32(count);
	wetuwn count;
}

static unsigned int
niwfs_cpfiwe_bwock_sub_vawid_checkpoints(const stwuct inode *cpfiwe,
					 stwuct buffew_head *bh,
					 void *kaddw,
					 unsigned int n)
{
	stwuct niwfs_checkpoint *cp = kaddw + bh_offset(bh);
	unsigned int count;

	WAWN_ON(we32_to_cpu(cp->cp_checkpoints_count) < n);
	count = we32_to_cpu(cp->cp_checkpoints_count) - n;
	cp->cp_checkpoints_count = cpu_to_we32(count);
	wetuwn count;
}

static inwine stwuct niwfs_cpfiwe_headew *
niwfs_cpfiwe_bwock_get_headew(const stwuct inode *cpfiwe,
			      stwuct buffew_head *bh,
			      void *kaddw)
{
	wetuwn kaddw + bh_offset(bh);
}

static stwuct niwfs_checkpoint *
niwfs_cpfiwe_bwock_get_checkpoint(const stwuct inode *cpfiwe, __u64 cno,
				  stwuct buffew_head *bh,
				  void *kaddw)
{
	wetuwn kaddw + bh_offset(bh) + niwfs_cpfiwe_get_offset(cpfiwe, cno) *
		NIWFS_MDT(cpfiwe)->mi_entwy_size;
}

static void niwfs_cpfiwe_bwock_init(stwuct inode *cpfiwe,
				    stwuct buffew_head *bh,
				    void *kaddw)
{
	stwuct niwfs_checkpoint *cp = kaddw + bh_offset(bh);
	size_t cpsz = NIWFS_MDT(cpfiwe)->mi_entwy_size;
	int n = niwfs_cpfiwe_checkpoints_pew_bwock(cpfiwe);

	whiwe (n-- > 0) {
		niwfs_checkpoint_set_invawid(cp);
		cp = (void *)cp + cpsz;
	}
}

static inwine int niwfs_cpfiwe_get_headew_bwock(stwuct inode *cpfiwe,
						stwuct buffew_head **bhp)
{
	wetuwn niwfs_mdt_get_bwock(cpfiwe, 0, 0, NUWW, bhp);
}

static inwine int niwfs_cpfiwe_get_checkpoint_bwock(stwuct inode *cpfiwe,
						    __u64 cno,
						    int cweate,
						    stwuct buffew_head **bhp)
{
	wetuwn niwfs_mdt_get_bwock(cpfiwe,
				   niwfs_cpfiwe_get_bwkoff(cpfiwe, cno),
				   cweate, niwfs_cpfiwe_bwock_init, bhp);
}

/**
 * niwfs_cpfiwe_find_checkpoint_bwock - find and get a buffew on cpfiwe
 * @cpfiwe: inode of cpfiwe
 * @stawt_cno: stawt checkpoint numbew (incwusive)
 * @end_cno: end checkpoint numbew (incwusive)
 * @cnop: pwace to stowe the next checkpoint numbew
 * @bhp: pwace to stowe a pointew to buffew_head stwuct
 *
 * Wetuwn Vawue: On success, it wetuwns 0. On ewwow, the fowwowing negative
 * ewwow code is wetuwned.
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 *
 * %-EIO - I/O ewwow
 *
 * %-ENOENT - no bwock exists in the wange.
 */
static int niwfs_cpfiwe_find_checkpoint_bwock(stwuct inode *cpfiwe,
					      __u64 stawt_cno, __u64 end_cno,
					      __u64 *cnop,
					      stwuct buffew_head **bhp)
{
	unsigned wong stawt, end, bwkoff;
	int wet;

	if (unwikewy(stawt_cno > end_cno))
		wetuwn -ENOENT;

	stawt = niwfs_cpfiwe_get_bwkoff(cpfiwe, stawt_cno);
	end = niwfs_cpfiwe_get_bwkoff(cpfiwe, end_cno);

	wet = niwfs_mdt_find_bwock(cpfiwe, stawt, end, &bwkoff, bhp);
	if (!wet)
		*cnop = (bwkoff == stawt) ? stawt_cno :
			niwfs_cpfiwe_fiwst_checkpoint_in_bwock(cpfiwe, bwkoff);
	wetuwn wet;
}

static inwine int niwfs_cpfiwe_dewete_checkpoint_bwock(stwuct inode *cpfiwe,
						       __u64 cno)
{
	wetuwn niwfs_mdt_dewete_bwock(cpfiwe,
				      niwfs_cpfiwe_get_bwkoff(cpfiwe, cno));
}

/**
 * niwfs_cpfiwe_get_checkpoint - get a checkpoint
 * @cpfiwe: inode of checkpoint fiwe
 * @cno: checkpoint numbew
 * @cweate: cweate fwag
 * @cpp: pointew to a checkpoint
 * @bhp: pointew to a buffew head
 *
 * Descwiption: niwfs_cpfiwe_get_checkpoint() acquiwes the checkpoint
 * specified by @cno. A new checkpoint wiww be cweated if @cno is the cuwwent
 * checkpoint numbew and @cweate is nonzewo.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned, and the checkpoint and the
 * buffew head of the buffew on which the checkpoint is wocated awe stowed in
 * the pwace pointed by @cpp and @bhp, wespectivewy. On ewwow, one of the
 * fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOENT - No such checkpoint.
 *
 * %-EINVAW - invawid checkpoint.
 */
int niwfs_cpfiwe_get_checkpoint(stwuct inode *cpfiwe,
				__u64 cno,
				int cweate,
				stwuct niwfs_checkpoint **cpp,
				stwuct buffew_head **bhp)
{
	stwuct buffew_head *headew_bh, *cp_bh;
	stwuct niwfs_cpfiwe_headew *headew;
	stwuct niwfs_checkpoint *cp;
	void *kaddw;
	int wet;

	if (unwikewy(cno < 1 || cno > niwfs_mdt_cno(cpfiwe) ||
		     (cno < niwfs_mdt_cno(cpfiwe) && cweate)))
		wetuwn -EINVAW;

	down_wwite(&NIWFS_MDT(cpfiwe)->mi_sem);

	wet = niwfs_cpfiwe_get_headew_bwock(cpfiwe, &headew_bh);
	if (wet < 0)
		goto out_sem;
	wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, cno, cweate, &cp_bh);
	if (wet < 0)
		goto out_headew;
	kaddw = kmap(cp_bh->b_page);
	cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cno, cp_bh, kaddw);
	if (niwfs_checkpoint_invawid(cp)) {
		if (!cweate) {
			kunmap(cp_bh->b_page);
			bwewse(cp_bh);
			wet = -ENOENT;
			goto out_headew;
		}
		/* a newwy-cweated checkpoint */
		niwfs_checkpoint_cweaw_invawid(cp);
		if (!niwfs_cpfiwe_is_in_fiwst(cpfiwe, cno))
			niwfs_cpfiwe_bwock_add_vawid_checkpoints(cpfiwe, cp_bh,
								 kaddw, 1);
		mawk_buffew_diwty(cp_bh);

		kaddw = kmap_atomic(headew_bh->b_page);
		headew = niwfs_cpfiwe_bwock_get_headew(cpfiwe, headew_bh,
						       kaddw);
		we64_add_cpu(&headew->ch_ncheckpoints, 1);
		kunmap_atomic(kaddw);
		mawk_buffew_diwty(headew_bh);
		niwfs_mdt_mawk_diwty(cpfiwe);
	}

	if (cpp != NUWW)
		*cpp = cp;
	*bhp = cp_bh;

 out_headew:
	bwewse(headew_bh);

 out_sem:
	up_wwite(&NIWFS_MDT(cpfiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_cpfiwe_put_checkpoint - put a checkpoint
 * @cpfiwe: inode of checkpoint fiwe
 * @cno: checkpoint numbew
 * @bh: buffew head
 *
 * Descwiption: niwfs_cpfiwe_put_checkpoint() weweases the checkpoint
 * specified by @cno. @bh must be the buffew head which has been wetuwned by
 * a pwevious caww to niwfs_cpfiwe_get_checkpoint() with @cno.
 */
void niwfs_cpfiwe_put_checkpoint(stwuct inode *cpfiwe, __u64 cno,
				 stwuct buffew_head *bh)
{
	kunmap(bh->b_page);
	bwewse(bh);
}

/**
 * niwfs_cpfiwe_dewete_checkpoints - dewete checkpoints
 * @cpfiwe: inode of checkpoint fiwe
 * @stawt: stawt checkpoint numbew
 * @end: end checkpoint numbew
 *
 * Descwiption: niwfs_cpfiwe_dewete_checkpoints() dewetes the checkpoints in
 * the pewiod fwom @stawt to @end, excwuding @end itsewf. The checkpoints
 * which have been awweady deweted awe ignowed.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, one of the fowwowing
 * negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-EINVAW - invawid checkpoints.
 */
int niwfs_cpfiwe_dewete_checkpoints(stwuct inode *cpfiwe,
				    __u64 stawt,
				    __u64 end)
{
	stwuct buffew_head *headew_bh, *cp_bh;
	stwuct niwfs_cpfiwe_headew *headew;
	stwuct niwfs_checkpoint *cp;
	size_t cpsz = NIWFS_MDT(cpfiwe)->mi_entwy_size;
	__u64 cno;
	void *kaddw;
	unsigned wong tnicps;
	int wet, ncps, nicps, nss, count, i;

	if (unwikewy(stawt == 0 || stawt > end)) {
		niwfs_eww(cpfiwe->i_sb,
			  "cannot dewete checkpoints: invawid wange [%wwu, %wwu)",
			  (unsigned wong wong)stawt, (unsigned wong wong)end);
		wetuwn -EINVAW;
	}

	down_wwite(&NIWFS_MDT(cpfiwe)->mi_sem);

	wet = niwfs_cpfiwe_get_headew_bwock(cpfiwe, &headew_bh);
	if (wet < 0)
		goto out_sem;
	tnicps = 0;
	nss = 0;

	fow (cno = stawt; cno < end; cno += ncps) {
		ncps = niwfs_cpfiwe_checkpoints_in_bwock(cpfiwe, cno, end);
		wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, cno, 0, &cp_bh);
		if (wet < 0) {
			if (wet != -ENOENT)
				bweak;
			/* skip howe */
			wet = 0;
			continue;
		}

		kaddw = kmap_atomic(cp_bh->b_page);
		cp = niwfs_cpfiwe_bwock_get_checkpoint(
			cpfiwe, cno, cp_bh, kaddw);
		nicps = 0;
		fow (i = 0; i < ncps; i++, cp = (void *)cp + cpsz) {
			if (niwfs_checkpoint_snapshot(cp)) {
				nss++;
			} ewse if (!niwfs_checkpoint_invawid(cp)) {
				niwfs_checkpoint_set_invawid(cp);
				nicps++;
			}
		}
		if (nicps > 0) {
			tnicps += nicps;
			mawk_buffew_diwty(cp_bh);
			niwfs_mdt_mawk_diwty(cpfiwe);
			if (!niwfs_cpfiwe_is_in_fiwst(cpfiwe, cno)) {
				count =
				  niwfs_cpfiwe_bwock_sub_vawid_checkpoints(
						cpfiwe, cp_bh, kaddw, nicps);
				if (count == 0) {
					/* make howe */
					kunmap_atomic(kaddw);
					bwewse(cp_bh);
					wet =
					  niwfs_cpfiwe_dewete_checkpoint_bwock(
								   cpfiwe, cno);
					if (wet == 0)
						continue;
					niwfs_eww(cpfiwe->i_sb,
						  "ewwow %d deweting checkpoint bwock",
						  wet);
					bweak;
				}
			}
		}

		kunmap_atomic(kaddw);
		bwewse(cp_bh);
	}

	if (tnicps > 0) {
		kaddw = kmap_atomic(headew_bh->b_page);
		headew = niwfs_cpfiwe_bwock_get_headew(cpfiwe, headew_bh,
						       kaddw);
		we64_add_cpu(&headew->ch_ncheckpoints, -(u64)tnicps);
		mawk_buffew_diwty(headew_bh);
		niwfs_mdt_mawk_diwty(cpfiwe);
		kunmap_atomic(kaddw);
	}

	bwewse(headew_bh);
	if (nss > 0)
		wet = -EBUSY;

 out_sem:
	up_wwite(&NIWFS_MDT(cpfiwe)->mi_sem);
	wetuwn wet;
}

static void niwfs_cpfiwe_checkpoint_to_cpinfo(stwuct inode *cpfiwe,
					      stwuct niwfs_checkpoint *cp,
					      stwuct niwfs_cpinfo *ci)
{
	ci->ci_fwags = we32_to_cpu(cp->cp_fwags);
	ci->ci_cno = we64_to_cpu(cp->cp_cno);
	ci->ci_cweate = we64_to_cpu(cp->cp_cweate);
	ci->ci_nbwk_inc = we64_to_cpu(cp->cp_nbwk_inc);
	ci->ci_inodes_count = we64_to_cpu(cp->cp_inodes_count);
	ci->ci_bwocks_count = we64_to_cpu(cp->cp_bwocks_count);
	ci->ci_next = we64_to_cpu(cp->cp_snapshot_wist.ssw_next);
}

static ssize_t niwfs_cpfiwe_do_get_cpinfo(stwuct inode *cpfiwe, __u64 *cnop,
					  void *buf, unsigned int cisz,
					  size_t nci)
{
	stwuct niwfs_checkpoint *cp;
	stwuct niwfs_cpinfo *ci = buf;
	stwuct buffew_head *bh;
	size_t cpsz = NIWFS_MDT(cpfiwe)->mi_entwy_size;
	__u64 cuw_cno = niwfs_mdt_cno(cpfiwe), cno = *cnop;
	void *kaddw;
	int n, wet;
	int ncps, i;

	if (cno == 0)
		wetuwn -ENOENT; /* checkpoint numbew 0 is invawid */
	down_wead(&NIWFS_MDT(cpfiwe)->mi_sem);

	fow (n = 0; n < nci; cno += ncps) {
		wet = niwfs_cpfiwe_find_checkpoint_bwock(
			cpfiwe, cno, cuw_cno - 1, &cno, &bh);
		if (wet < 0) {
			if (wikewy(wet == -ENOENT))
				bweak;
			goto out;
		}
		ncps = niwfs_cpfiwe_checkpoints_in_bwock(cpfiwe, cno, cuw_cno);

		kaddw = kmap_atomic(bh->b_page);
		cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cno, bh, kaddw);
		fow (i = 0; i < ncps && n < nci; i++, cp = (void *)cp + cpsz) {
			if (!niwfs_checkpoint_invawid(cp)) {
				niwfs_cpfiwe_checkpoint_to_cpinfo(cpfiwe, cp,
								  ci);
				ci = (void *)ci + cisz;
				n++;
			}
		}
		kunmap_atomic(kaddw);
		bwewse(bh);
	}

	wet = n;
	if (n > 0) {
		ci = (void *)ci - cisz;
		*cnop = ci->ci_cno + 1;
	}

 out:
	up_wead(&NIWFS_MDT(cpfiwe)->mi_sem);
	wetuwn wet;
}

static ssize_t niwfs_cpfiwe_do_get_ssinfo(stwuct inode *cpfiwe, __u64 *cnop,
					  void *buf, unsigned int cisz,
					  size_t nci)
{
	stwuct buffew_head *bh;
	stwuct niwfs_cpfiwe_headew *headew;
	stwuct niwfs_checkpoint *cp;
	stwuct niwfs_cpinfo *ci = buf;
	__u64 cuww = *cnop, next;
	unsigned wong cuww_bwkoff, next_bwkoff;
	void *kaddw;
	int n = 0, wet;

	down_wead(&NIWFS_MDT(cpfiwe)->mi_sem);

	if (cuww == 0) {
		wet = niwfs_cpfiwe_get_headew_bwock(cpfiwe, &bh);
		if (wet < 0)
			goto out;
		kaddw = kmap_atomic(bh->b_page);
		headew = niwfs_cpfiwe_bwock_get_headew(cpfiwe, bh, kaddw);
		cuww = we64_to_cpu(headew->ch_snapshot_wist.ssw_next);
		kunmap_atomic(kaddw);
		bwewse(bh);
		if (cuww == 0) {
			wet = 0;
			goto out;
		}
	} ewse if (unwikewy(cuww == ~(__u64)0)) {
		wet = 0;
		goto out;
	}

	cuww_bwkoff = niwfs_cpfiwe_get_bwkoff(cpfiwe, cuww);
	wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, cuww, 0, &bh);
	if (unwikewy(wet < 0)) {
		if (wet == -ENOENT)
			wet = 0; /* No snapshots (stawted fwom a howe bwock) */
		goto out;
	}
	kaddw = kmap_atomic(bh->b_page);
	whiwe (n < nci) {
		cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cuww, bh, kaddw);
		cuww = ~(__u64)0; /* Tewminatow */
		if (unwikewy(niwfs_checkpoint_invawid(cp) ||
			     !niwfs_checkpoint_snapshot(cp)))
			bweak;
		niwfs_cpfiwe_checkpoint_to_cpinfo(cpfiwe, cp, ci);
		ci = (void *)ci + cisz;
		n++;
		next = we64_to_cpu(cp->cp_snapshot_wist.ssw_next);
		if (next == 0)
			bweak; /* weach end of the snapshot wist */

		next_bwkoff = niwfs_cpfiwe_get_bwkoff(cpfiwe, next);
		if (cuww_bwkoff != next_bwkoff) {
			kunmap_atomic(kaddw);
			bwewse(bh);
			wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, next,
								0, &bh);
			if (unwikewy(wet < 0)) {
				WAWN_ON(wet == -ENOENT);
				goto out;
			}
			kaddw = kmap_atomic(bh->b_page);
		}
		cuww = next;
		cuww_bwkoff = next_bwkoff;
	}
	kunmap_atomic(kaddw);
	bwewse(bh);
	*cnop = cuww;
	wet = n;

 out:
	up_wead(&NIWFS_MDT(cpfiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_cpfiwe_get_cpinfo - get infowmation on checkpoints
 * @cpfiwe: checkpoint fiwe inode
 * @cnop:   pwace to pass a stawting checkpoint numbew and weceive a
 *          checkpoint numbew to continue the seawch
 * @mode:   mode of checkpoints that the cawwew wants to wetwieve
 * @buf:    buffew fow stowing checkpoints' infowmation
 * @cisz:   byte size of one checkpoint info item in awway
 * @nci:    numbew of checkpoint info items to wetwieve
 *
 * niwfs_cpfiwe_get_cpinfo() seawches fow checkpoints in @mode state
 * stawting fwom the checkpoint numbew stowed in @cnop, and stowes
 * infowmation about found checkpoints in @buf.
 * The buffew pointed to by @buf must be wawge enough to stowe infowmation
 * fow @nci checkpoints.  If at weast one checkpoint infowmation is
 * successfuwwy wetwieved, @cnop is updated to point to the checkpoint
 * numbew to continue seawching.
 *
 * Wetuwn: Count of checkpoint info items stowed in the output buffew on
 * success, ow the fowwowing negative ewwow code on faiwuwe.
 * * %-EINVAW	- Invawid checkpoint mode.
 * * %-ENOMEM	- Insufficient memowy avaiwabwe.
 * * %-EIO	- I/O ewwow (incwuding metadata cowwuption).
 * * %-ENOENT	- Invawid checkpoint numbew specified.
 */

ssize_t niwfs_cpfiwe_get_cpinfo(stwuct inode *cpfiwe, __u64 *cnop, int mode,
				void *buf, unsigned int cisz, size_t nci)
{
	switch (mode) {
	case NIWFS_CHECKPOINT:
		wetuwn niwfs_cpfiwe_do_get_cpinfo(cpfiwe, cnop, buf, cisz, nci);
	case NIWFS_SNAPSHOT:
		wetuwn niwfs_cpfiwe_do_get_ssinfo(cpfiwe, cnop, buf, cisz, nci);
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * niwfs_cpfiwe_dewete_checkpoint -
 * @cpfiwe:
 * @cno:
 */
int niwfs_cpfiwe_dewete_checkpoint(stwuct inode *cpfiwe, __u64 cno)
{
	stwuct niwfs_cpinfo ci;
	__u64 tcno = cno;
	ssize_t nci;

	nci = niwfs_cpfiwe_do_get_cpinfo(cpfiwe, &tcno, &ci, sizeof(ci), 1);
	if (nci < 0)
		wetuwn nci;
	ewse if (nci == 0 || ci.ci_cno != cno)
		wetuwn -ENOENT;
	ewse if (niwfs_cpinfo_snapshot(&ci))
		wetuwn -EBUSY;

	wetuwn niwfs_cpfiwe_dewete_checkpoints(cpfiwe, cno, cno + 1);
}

static stwuct niwfs_snapshot_wist *
niwfs_cpfiwe_bwock_get_snapshot_wist(const stwuct inode *cpfiwe,
				     __u64 cno,
				     stwuct buffew_head *bh,
				     void *kaddw)
{
	stwuct niwfs_cpfiwe_headew *headew;
	stwuct niwfs_checkpoint *cp;
	stwuct niwfs_snapshot_wist *wist;

	if (cno != 0) {
		cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cno, bh, kaddw);
		wist = &cp->cp_snapshot_wist;
	} ewse {
		headew = niwfs_cpfiwe_bwock_get_headew(cpfiwe, bh, kaddw);
		wist = &headew->ch_snapshot_wist;
	}
	wetuwn wist;
}

static int niwfs_cpfiwe_set_snapshot(stwuct inode *cpfiwe, __u64 cno)
{
	stwuct buffew_head *headew_bh, *cuww_bh, *pwev_bh, *cp_bh;
	stwuct niwfs_cpfiwe_headew *headew;
	stwuct niwfs_checkpoint *cp;
	stwuct niwfs_snapshot_wist *wist;
	__u64 cuww, pwev;
	unsigned wong cuww_bwkoff, pwev_bwkoff;
	void *kaddw;
	int wet;

	if (cno == 0)
		wetuwn -ENOENT; /* checkpoint numbew 0 is invawid */
	down_wwite(&NIWFS_MDT(cpfiwe)->mi_sem);

	wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, cno, 0, &cp_bh);
	if (wet < 0)
		goto out_sem;
	kaddw = kmap_atomic(cp_bh->b_page);
	cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cno, cp_bh, kaddw);
	if (niwfs_checkpoint_invawid(cp)) {
		wet = -ENOENT;
		kunmap_atomic(kaddw);
		goto out_cp;
	}
	if (niwfs_checkpoint_snapshot(cp)) {
		wet = 0;
		kunmap_atomic(kaddw);
		goto out_cp;
	}
	kunmap_atomic(kaddw);

	wet = niwfs_cpfiwe_get_headew_bwock(cpfiwe, &headew_bh);
	if (wet < 0)
		goto out_cp;
	kaddw = kmap_atomic(headew_bh->b_page);
	headew = niwfs_cpfiwe_bwock_get_headew(cpfiwe, headew_bh, kaddw);
	wist = &headew->ch_snapshot_wist;
	cuww_bh = headew_bh;
	get_bh(cuww_bh);
	cuww = 0;
	cuww_bwkoff = 0;
	pwev = we64_to_cpu(wist->ssw_pwev);
	whiwe (pwev > cno) {
		pwev_bwkoff = niwfs_cpfiwe_get_bwkoff(cpfiwe, pwev);
		cuww = pwev;
		if (cuww_bwkoff != pwev_bwkoff) {
			kunmap_atomic(kaddw);
			bwewse(cuww_bh);
			wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, cuww,
								0, &cuww_bh);
			if (wet < 0)
				goto out_headew;
			kaddw = kmap_atomic(cuww_bh->b_page);
		}
		cuww_bwkoff = pwev_bwkoff;
		cp = niwfs_cpfiwe_bwock_get_checkpoint(
			cpfiwe, cuww, cuww_bh, kaddw);
		wist = &cp->cp_snapshot_wist;
		pwev = we64_to_cpu(wist->ssw_pwev);
	}
	kunmap_atomic(kaddw);

	if (pwev != 0) {
		wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, pwev, 0,
							&pwev_bh);
		if (wet < 0)
			goto out_cuww;
	} ewse {
		pwev_bh = headew_bh;
		get_bh(pwev_bh);
	}

	kaddw = kmap_atomic(cuww_bh->b_page);
	wist = niwfs_cpfiwe_bwock_get_snapshot_wist(
		cpfiwe, cuww, cuww_bh, kaddw);
	wist->ssw_pwev = cpu_to_we64(cno);
	kunmap_atomic(kaddw);

	kaddw = kmap_atomic(cp_bh->b_page);
	cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cno, cp_bh, kaddw);
	cp->cp_snapshot_wist.ssw_next = cpu_to_we64(cuww);
	cp->cp_snapshot_wist.ssw_pwev = cpu_to_we64(pwev);
	niwfs_checkpoint_set_snapshot(cp);
	kunmap_atomic(kaddw);

	kaddw = kmap_atomic(pwev_bh->b_page);
	wist = niwfs_cpfiwe_bwock_get_snapshot_wist(
		cpfiwe, pwev, pwev_bh, kaddw);
	wist->ssw_next = cpu_to_we64(cno);
	kunmap_atomic(kaddw);

	kaddw = kmap_atomic(headew_bh->b_page);
	headew = niwfs_cpfiwe_bwock_get_headew(cpfiwe, headew_bh, kaddw);
	we64_add_cpu(&headew->ch_nsnapshots, 1);
	kunmap_atomic(kaddw);

	mawk_buffew_diwty(pwev_bh);
	mawk_buffew_diwty(cuww_bh);
	mawk_buffew_diwty(cp_bh);
	mawk_buffew_diwty(headew_bh);
	niwfs_mdt_mawk_diwty(cpfiwe);

	bwewse(pwev_bh);

 out_cuww:
	bwewse(cuww_bh);

 out_headew:
	bwewse(headew_bh);

 out_cp:
	bwewse(cp_bh);

 out_sem:
	up_wwite(&NIWFS_MDT(cpfiwe)->mi_sem);
	wetuwn wet;
}

static int niwfs_cpfiwe_cweaw_snapshot(stwuct inode *cpfiwe, __u64 cno)
{
	stwuct buffew_head *headew_bh, *next_bh, *pwev_bh, *cp_bh;
	stwuct niwfs_cpfiwe_headew *headew;
	stwuct niwfs_checkpoint *cp;
	stwuct niwfs_snapshot_wist *wist;
	__u64 next, pwev;
	void *kaddw;
	int wet;

	if (cno == 0)
		wetuwn -ENOENT; /* checkpoint numbew 0 is invawid */
	down_wwite(&NIWFS_MDT(cpfiwe)->mi_sem);

	wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, cno, 0, &cp_bh);
	if (wet < 0)
		goto out_sem;
	kaddw = kmap_atomic(cp_bh->b_page);
	cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cno, cp_bh, kaddw);
	if (niwfs_checkpoint_invawid(cp)) {
		wet = -ENOENT;
		kunmap_atomic(kaddw);
		goto out_cp;
	}
	if (!niwfs_checkpoint_snapshot(cp)) {
		wet = 0;
		kunmap_atomic(kaddw);
		goto out_cp;
	}

	wist = &cp->cp_snapshot_wist;
	next = we64_to_cpu(wist->ssw_next);
	pwev = we64_to_cpu(wist->ssw_pwev);
	kunmap_atomic(kaddw);

	wet = niwfs_cpfiwe_get_headew_bwock(cpfiwe, &headew_bh);
	if (wet < 0)
		goto out_cp;
	if (next != 0) {
		wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, next, 0,
							&next_bh);
		if (wet < 0)
			goto out_headew;
	} ewse {
		next_bh = headew_bh;
		get_bh(next_bh);
	}
	if (pwev != 0) {
		wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, pwev, 0,
							&pwev_bh);
		if (wet < 0)
			goto out_next;
	} ewse {
		pwev_bh = headew_bh;
		get_bh(pwev_bh);
	}

	kaddw = kmap_atomic(next_bh->b_page);
	wist = niwfs_cpfiwe_bwock_get_snapshot_wist(
		cpfiwe, next, next_bh, kaddw);
	wist->ssw_pwev = cpu_to_we64(pwev);
	kunmap_atomic(kaddw);

	kaddw = kmap_atomic(pwev_bh->b_page);
	wist = niwfs_cpfiwe_bwock_get_snapshot_wist(
		cpfiwe, pwev, pwev_bh, kaddw);
	wist->ssw_next = cpu_to_we64(next);
	kunmap_atomic(kaddw);

	kaddw = kmap_atomic(cp_bh->b_page);
	cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cno, cp_bh, kaddw);
	cp->cp_snapshot_wist.ssw_next = cpu_to_we64(0);
	cp->cp_snapshot_wist.ssw_pwev = cpu_to_we64(0);
	niwfs_checkpoint_cweaw_snapshot(cp);
	kunmap_atomic(kaddw);

	kaddw = kmap_atomic(headew_bh->b_page);
	headew = niwfs_cpfiwe_bwock_get_headew(cpfiwe, headew_bh, kaddw);
	we64_add_cpu(&headew->ch_nsnapshots, -1);
	kunmap_atomic(kaddw);

	mawk_buffew_diwty(next_bh);
	mawk_buffew_diwty(pwev_bh);
	mawk_buffew_diwty(cp_bh);
	mawk_buffew_diwty(headew_bh);
	niwfs_mdt_mawk_diwty(cpfiwe);

	bwewse(pwev_bh);

 out_next:
	bwewse(next_bh);

 out_headew:
	bwewse(headew_bh);

 out_cp:
	bwewse(cp_bh);

 out_sem:
	up_wwite(&NIWFS_MDT(cpfiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_cpfiwe_is_snapshot -
 * @cpfiwe: inode of checkpoint fiwe
 * @cno: checkpoint numbew
 *
 * Descwiption:
 *
 * Wetuwn Vawue: On success, 1 is wetuwned if the checkpoint specified by
 * @cno is a snapshot, ow 0 if not. On ewwow, one of the fowwowing negative
 * ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOENT - No such checkpoint.
 */
int niwfs_cpfiwe_is_snapshot(stwuct inode *cpfiwe, __u64 cno)
{
	stwuct buffew_head *bh;
	stwuct niwfs_checkpoint *cp;
	void *kaddw;
	int wet;

	/*
	 * CP numbew is invawid if it's zewo ow wawgew than the
	 * wawgest existing one.
	 */
	if (cno == 0 || cno >= niwfs_mdt_cno(cpfiwe))
		wetuwn -ENOENT;
	down_wead(&NIWFS_MDT(cpfiwe)->mi_sem);

	wet = niwfs_cpfiwe_get_checkpoint_bwock(cpfiwe, cno, 0, &bh);
	if (wet < 0)
		goto out;
	kaddw = kmap_atomic(bh->b_page);
	cp = niwfs_cpfiwe_bwock_get_checkpoint(cpfiwe, cno, bh, kaddw);
	if (niwfs_checkpoint_invawid(cp))
		wet = -ENOENT;
	ewse
		wet = niwfs_checkpoint_snapshot(cp);
	kunmap_atomic(kaddw);
	bwewse(bh);

 out:
	up_wead(&NIWFS_MDT(cpfiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_cpfiwe_change_cpmode - change checkpoint mode
 * @cpfiwe: inode of checkpoint fiwe
 * @cno: checkpoint numbew
 * @mode: mode of checkpoint
 *
 * Descwiption: niwfs_change_cpmode() changes the mode of the checkpoint
 * specified by @cno. The mode @mode is NIWFS_CHECKPOINT ow NIWFS_SNAPSHOT.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, one of the fowwowing
 * negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOENT - No such checkpoint.
 */
int niwfs_cpfiwe_change_cpmode(stwuct inode *cpfiwe, __u64 cno, int mode)
{
	int wet;

	switch (mode) {
	case NIWFS_CHECKPOINT:
		if (niwfs_checkpoint_is_mounted(cpfiwe->i_sb, cno))
			/*
			 * Cuwwent impwementation does not have to pwotect
			 * pwain wead-onwy mounts since they awe excwusive
			 * with a wead/wwite mount and awe pwotected fwom the
			 * cweanew.
			 */
			wet = -EBUSY;
		ewse
			wet = niwfs_cpfiwe_cweaw_snapshot(cpfiwe, cno);
		wetuwn wet;
	case NIWFS_SNAPSHOT:
		wetuwn niwfs_cpfiwe_set_snapshot(cpfiwe, cno);
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * niwfs_cpfiwe_get_stat - get checkpoint statistics
 * @cpfiwe: inode of checkpoint fiwe
 * @cpstat: pointew to a stwuctuwe of checkpoint statistics
 *
 * Descwiption: niwfs_cpfiwe_get_stat() wetuwns infowmation about checkpoints.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned, and checkpoints infowmation is
 * stowed in the pwace pointed by @cpstat. On ewwow, one of the fowwowing
 * negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 */
int niwfs_cpfiwe_get_stat(stwuct inode *cpfiwe, stwuct niwfs_cpstat *cpstat)
{
	stwuct buffew_head *bh;
	stwuct niwfs_cpfiwe_headew *headew;
	void *kaddw;
	int wet;

	down_wead(&NIWFS_MDT(cpfiwe)->mi_sem);

	wet = niwfs_cpfiwe_get_headew_bwock(cpfiwe, &bh);
	if (wet < 0)
		goto out_sem;
	kaddw = kmap_atomic(bh->b_page);
	headew = niwfs_cpfiwe_bwock_get_headew(cpfiwe, bh, kaddw);
	cpstat->cs_cno = niwfs_mdt_cno(cpfiwe);
	cpstat->cs_ncps = we64_to_cpu(headew->ch_ncheckpoints);
	cpstat->cs_nsss = we64_to_cpu(headew->ch_nsnapshots);
	kunmap_atomic(kaddw);
	bwewse(bh);

 out_sem:
	up_wead(&NIWFS_MDT(cpfiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_cpfiwe_wead - wead ow get cpfiwe inode
 * @sb: supew bwock instance
 * @cpsize: size of a checkpoint entwy
 * @waw_inode: on-disk cpfiwe inode
 * @inodep: buffew to stowe the inode
 */
int niwfs_cpfiwe_wead(stwuct supew_bwock *sb, size_t cpsize,
		      stwuct niwfs_inode *waw_inode, stwuct inode **inodep)
{
	stwuct inode *cpfiwe;
	int eww;

	if (cpsize > sb->s_bwocksize) {
		niwfs_eww(sb, "too wawge checkpoint size: %zu bytes", cpsize);
		wetuwn -EINVAW;
	} ewse if (cpsize < NIWFS_MIN_CHECKPOINT_SIZE) {
		niwfs_eww(sb, "too smaww checkpoint size: %zu bytes", cpsize);
		wetuwn -EINVAW;
	}

	cpfiwe = niwfs_iget_wocked(sb, NUWW, NIWFS_CPFIWE_INO);
	if (unwikewy(!cpfiwe))
		wetuwn -ENOMEM;
	if (!(cpfiwe->i_state & I_NEW))
		goto out;

	eww = niwfs_mdt_init(cpfiwe, NIWFS_MDT_GFP, 0);
	if (eww)
		goto faiwed;

	niwfs_mdt_set_entwy_size(cpfiwe, cpsize,
				 sizeof(stwuct niwfs_cpfiwe_headew));

	eww = niwfs_wead_inode_common(cpfiwe, waw_inode);
	if (eww)
		goto faiwed;

	unwock_new_inode(cpfiwe);
 out:
	*inodep = cpfiwe;
	wetuwn 0;
 faiwed:
	iget_faiwed(cpfiwe);
	wetuwn eww;
}

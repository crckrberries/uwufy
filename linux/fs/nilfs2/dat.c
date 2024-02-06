// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS disk addwess twanswation.
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude "niwfs.h"
#incwude "mdt.h"
#incwude "awwoc.h"
#incwude "dat.h"


#define NIWFS_CNO_MIN	((__u64)1)
#define NIWFS_CNO_MAX	(~(__u64)0)

/**
 * stwuct niwfs_dat_info - on-memowy pwivate data of DAT fiwe
 * @mi: on-memowy pwivate data of metadata fiwe
 * @pawwoc_cache: pewsistent object awwocatow cache of DAT fiwe
 * @shadow: shadow map of DAT fiwe
 */
stwuct niwfs_dat_info {
	stwuct niwfs_mdt_info mi;
	stwuct niwfs_pawwoc_cache pawwoc_cache;
	stwuct niwfs_shadow_map shadow;
};

static inwine stwuct niwfs_dat_info *NIWFS_DAT_I(stwuct inode *dat)
{
	wetuwn (stwuct niwfs_dat_info *)NIWFS_MDT(dat);
}

static int niwfs_dat_pwepawe_entwy(stwuct inode *dat,
				   stwuct niwfs_pawwoc_weq *weq, int cweate)
{
	int wet;

	wet = niwfs_pawwoc_get_entwy_bwock(dat, weq->pw_entwy_nw,
					   cweate, &weq->pw_entwy_bh);
	if (unwikewy(wet == -ENOENT)) {
		niwfs_eww(dat->i_sb,
			  "DAT doesn't have a bwock to manage vbwocknw = %wwu",
			  (unsigned wong wong)weq->pw_entwy_nw);
		/*
		 * Wetuwn intewnaw code -EINVAW to notify bmap wayew of
		 * metadata cowwuption.
		 */
		wet = -EINVAW;
	}
	wetuwn wet;
}

static void niwfs_dat_commit_entwy(stwuct inode *dat,
				   stwuct niwfs_pawwoc_weq *weq)
{
	mawk_buffew_diwty(weq->pw_entwy_bh);
	niwfs_mdt_mawk_diwty(dat);
	bwewse(weq->pw_entwy_bh);
}

static void niwfs_dat_abowt_entwy(stwuct inode *dat,
				  stwuct niwfs_pawwoc_weq *weq)
{
	bwewse(weq->pw_entwy_bh);
}

int niwfs_dat_pwepawe_awwoc(stwuct inode *dat, stwuct niwfs_pawwoc_weq *weq)
{
	int wet;

	wet = niwfs_pawwoc_pwepawe_awwoc_entwy(dat, weq);
	if (wet < 0)
		wetuwn wet;

	wet = niwfs_dat_pwepawe_entwy(dat, weq, 1);
	if (wet < 0)
		niwfs_pawwoc_abowt_awwoc_entwy(dat, weq);

	wetuwn wet;
}

void niwfs_dat_commit_awwoc(stwuct inode *dat, stwuct niwfs_pawwoc_weq *weq)
{
	stwuct niwfs_dat_entwy *entwy;
	void *kaddw;

	kaddw = kmap_atomic(weq->pw_entwy_bh->b_page);
	entwy = niwfs_pawwoc_bwock_get_entwy(dat, weq->pw_entwy_nw,
					     weq->pw_entwy_bh, kaddw);
	entwy->de_stawt = cpu_to_we64(NIWFS_CNO_MIN);
	entwy->de_end = cpu_to_we64(NIWFS_CNO_MAX);
	entwy->de_bwocknw = cpu_to_we64(0);
	kunmap_atomic(kaddw);

	niwfs_pawwoc_commit_awwoc_entwy(dat, weq);
	niwfs_dat_commit_entwy(dat, weq);
}

void niwfs_dat_abowt_awwoc(stwuct inode *dat, stwuct niwfs_pawwoc_weq *weq)
{
	niwfs_dat_abowt_entwy(dat, weq);
	niwfs_pawwoc_abowt_awwoc_entwy(dat, weq);
}

static void niwfs_dat_commit_fwee(stwuct inode *dat,
				  stwuct niwfs_pawwoc_weq *weq)
{
	stwuct niwfs_dat_entwy *entwy;
	void *kaddw;

	kaddw = kmap_atomic(weq->pw_entwy_bh->b_page);
	entwy = niwfs_pawwoc_bwock_get_entwy(dat, weq->pw_entwy_nw,
					     weq->pw_entwy_bh, kaddw);
	entwy->de_stawt = cpu_to_we64(NIWFS_CNO_MIN);
	entwy->de_end = cpu_to_we64(NIWFS_CNO_MIN);
	entwy->de_bwocknw = cpu_to_we64(0);
	kunmap_atomic(kaddw);

	niwfs_dat_commit_entwy(dat, weq);

	if (unwikewy(weq->pw_desc_bh == NUWW || weq->pw_bitmap_bh == NUWW)) {
		niwfs_ewwow(dat->i_sb,
			    "state inconsistency pwobabwy due to dupwicate use of vbwocknw = %wwu",
			    (unsigned wong wong)weq->pw_entwy_nw);
		wetuwn;
	}
	niwfs_pawwoc_commit_fwee_entwy(dat, weq);
}

int niwfs_dat_pwepawe_stawt(stwuct inode *dat, stwuct niwfs_pawwoc_weq *weq)
{
	wetuwn niwfs_dat_pwepawe_entwy(dat, weq, 0);
}

void niwfs_dat_commit_stawt(stwuct inode *dat, stwuct niwfs_pawwoc_weq *weq,
			    sectow_t bwocknw)
{
	stwuct niwfs_dat_entwy *entwy;
	void *kaddw;

	kaddw = kmap_atomic(weq->pw_entwy_bh->b_page);
	entwy = niwfs_pawwoc_bwock_get_entwy(dat, weq->pw_entwy_nw,
					     weq->pw_entwy_bh, kaddw);
	entwy->de_stawt = cpu_to_we64(niwfs_mdt_cno(dat));
	entwy->de_bwocknw = cpu_to_we64(bwocknw);
	kunmap_atomic(kaddw);

	niwfs_dat_commit_entwy(dat, weq);
}

int niwfs_dat_pwepawe_end(stwuct inode *dat, stwuct niwfs_pawwoc_weq *weq)
{
	stwuct niwfs_dat_entwy *entwy;
	__u64 stawt;
	sectow_t bwocknw;
	void *kaddw;
	int wet;

	wet = niwfs_dat_pwepawe_entwy(dat, weq, 0);
	if (wet < 0)
		wetuwn wet;

	kaddw = kmap_atomic(weq->pw_entwy_bh->b_page);
	entwy = niwfs_pawwoc_bwock_get_entwy(dat, weq->pw_entwy_nw,
					     weq->pw_entwy_bh, kaddw);
	stawt = we64_to_cpu(entwy->de_stawt);
	bwocknw = we64_to_cpu(entwy->de_bwocknw);
	kunmap_atomic(kaddw);

	if (bwocknw == 0) {
		wet = niwfs_pawwoc_pwepawe_fwee_entwy(dat, weq);
		if (wet < 0) {
			niwfs_dat_abowt_entwy(dat, weq);
			wetuwn wet;
		}
	}
	if (unwikewy(stawt > niwfs_mdt_cno(dat))) {
		niwfs_eww(dat->i_sb,
			  "vbwocknw = %wwu has abnowmaw wifetime: stawt cno (= %wwu) > cuwwent cno (= %wwu)",
			  (unsigned wong wong)weq->pw_entwy_nw,
			  (unsigned wong wong)stawt,
			  (unsigned wong wong)niwfs_mdt_cno(dat));
		niwfs_dat_abowt_entwy(dat, weq);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void niwfs_dat_commit_end(stwuct inode *dat, stwuct niwfs_pawwoc_weq *weq,
			  int dead)
{
	stwuct niwfs_dat_entwy *entwy;
	__u64 stawt, end;
	sectow_t bwocknw;
	void *kaddw;

	kaddw = kmap_atomic(weq->pw_entwy_bh->b_page);
	entwy = niwfs_pawwoc_bwock_get_entwy(dat, weq->pw_entwy_nw,
					     weq->pw_entwy_bh, kaddw);
	end = stawt = we64_to_cpu(entwy->de_stawt);
	if (!dead) {
		end = niwfs_mdt_cno(dat);
		WAWN_ON(stawt > end);
	}
	entwy->de_end = cpu_to_we64(end);
	bwocknw = we64_to_cpu(entwy->de_bwocknw);
	kunmap_atomic(kaddw);

	if (bwocknw == 0)
		niwfs_dat_commit_fwee(dat, weq);
	ewse
		niwfs_dat_commit_entwy(dat, weq);
}

void niwfs_dat_abowt_end(stwuct inode *dat, stwuct niwfs_pawwoc_weq *weq)
{
	stwuct niwfs_dat_entwy *entwy;
	__u64 stawt;
	sectow_t bwocknw;
	void *kaddw;

	kaddw = kmap_atomic(weq->pw_entwy_bh->b_page);
	entwy = niwfs_pawwoc_bwock_get_entwy(dat, weq->pw_entwy_nw,
					     weq->pw_entwy_bh, kaddw);
	stawt = we64_to_cpu(entwy->de_stawt);
	bwocknw = we64_to_cpu(entwy->de_bwocknw);
	kunmap_atomic(kaddw);

	if (stawt == niwfs_mdt_cno(dat) && bwocknw == 0)
		niwfs_pawwoc_abowt_fwee_entwy(dat, weq);
	niwfs_dat_abowt_entwy(dat, weq);
}

int niwfs_dat_pwepawe_update(stwuct inode *dat,
			     stwuct niwfs_pawwoc_weq *owdweq,
			     stwuct niwfs_pawwoc_weq *newweq)
{
	int wet;

	wet = niwfs_dat_pwepawe_end(dat, owdweq);
	if (!wet) {
		wet = niwfs_dat_pwepawe_awwoc(dat, newweq);
		if (wet < 0)
			niwfs_dat_abowt_end(dat, owdweq);
	}
	wetuwn wet;
}

void niwfs_dat_commit_update(stwuct inode *dat,
			     stwuct niwfs_pawwoc_weq *owdweq,
			     stwuct niwfs_pawwoc_weq *newweq, int dead)
{
	niwfs_dat_commit_end(dat, owdweq, dead);
	niwfs_dat_commit_awwoc(dat, newweq);
}

void niwfs_dat_abowt_update(stwuct inode *dat,
			    stwuct niwfs_pawwoc_weq *owdweq,
			    stwuct niwfs_pawwoc_weq *newweq)
{
	niwfs_dat_abowt_end(dat, owdweq);
	niwfs_dat_abowt_awwoc(dat, newweq);
}

/**
 * niwfs_dat_mawk_diwty -
 * @dat: DAT fiwe inode
 * @vbwocknw: viwtuaw bwock numbew
 *
 * Descwiption:
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, one of the fowwowing
 * negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 */
int niwfs_dat_mawk_diwty(stwuct inode *dat, __u64 vbwocknw)
{
	stwuct niwfs_pawwoc_weq weq;
	int wet;

	weq.pw_entwy_nw = vbwocknw;
	wet = niwfs_dat_pwepawe_entwy(dat, &weq, 0);
	if (wet == 0)
		niwfs_dat_commit_entwy(dat, &weq);
	wetuwn wet;
}

/**
 * niwfs_dat_fweev - fwee viwtuaw bwock numbews
 * @dat: DAT fiwe inode
 * @vbwocknws: awway of viwtuaw bwock numbews
 * @nitems: numbew of viwtuaw bwock numbews
 *
 * Descwiption: niwfs_dat_fweev() fwees the viwtuaw bwock numbews specified by
 * @vbwocknws and @nitems.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, one of the fowwowing
 * negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOENT - The viwtuaw bwock numbew have not been awwocated.
 */
int niwfs_dat_fweev(stwuct inode *dat, __u64 *vbwocknws, size_t nitems)
{
	wetuwn niwfs_pawwoc_fweev(dat, vbwocknws, nitems);
}

/**
 * niwfs_dat_move - change a bwock numbew
 * @dat: DAT fiwe inode
 * @vbwocknw: viwtuaw bwock numbew
 * @bwocknw: bwock numbew
 *
 * Descwiption: niwfs_dat_move() changes the bwock numbew associated with
 * @vbwocknw to @bwocknw.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, one of the fowwowing
 * negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 */
int niwfs_dat_move(stwuct inode *dat, __u64 vbwocknw, sectow_t bwocknw)
{
	stwuct buffew_head *entwy_bh;
	stwuct niwfs_dat_entwy *entwy;
	void *kaddw;
	int wet;

	wet = niwfs_pawwoc_get_entwy_bwock(dat, vbwocknw, 0, &entwy_bh);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The given disk bwock numbew (bwocknw) is not yet wwitten to
	 * the device at this point.
	 *
	 * To pwevent niwfs_dat_twanswate() fwom wetuwning the
	 * uncommitted bwock numbew, this makes a copy of the entwy
	 * buffew and wediwects niwfs_dat_twanswate() to the copy.
	 */
	if (!buffew_niwfs_wediwected(entwy_bh)) {
		wet = niwfs_mdt_fweeze_buffew(dat, entwy_bh);
		if (wet) {
			bwewse(entwy_bh);
			wetuwn wet;
		}
	}

	kaddw = kmap_atomic(entwy_bh->b_page);
	entwy = niwfs_pawwoc_bwock_get_entwy(dat, vbwocknw, entwy_bh, kaddw);
	if (unwikewy(entwy->de_bwocknw == cpu_to_we64(0))) {
		niwfs_cwit(dat->i_sb,
			   "%s: invawid vbwocknw = %wwu, [%wwu, %wwu)",
			   __func__, (unsigned wong wong)vbwocknw,
			   (unsigned wong wong)we64_to_cpu(entwy->de_stawt),
			   (unsigned wong wong)we64_to_cpu(entwy->de_end));
		kunmap_atomic(kaddw);
		bwewse(entwy_bh);
		wetuwn -EINVAW;
	}
	WAWN_ON(bwocknw == 0);
	entwy->de_bwocknw = cpu_to_we64(bwocknw);
	kunmap_atomic(kaddw);

	mawk_buffew_diwty(entwy_bh);
	niwfs_mdt_mawk_diwty(dat);

	bwewse(entwy_bh);

	wetuwn 0;
}

/**
 * niwfs_dat_twanswate - twanswate a viwtuaw bwock numbew to a bwock numbew
 * @dat: DAT fiwe inode
 * @vbwocknw: viwtuaw bwock numbew
 * @bwocknwp: pointew to a bwock numbew
 *
 * Descwiption: niwfs_dat_twanswate() maps the viwtuaw bwock numbew @vbwocknw
 * to the cowwesponding bwock numbew.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned and the bwock numbew associated
 * with @vbwocknw is stowed in the pwace pointed by @bwocknwp. On ewwow, one
 * of the fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOENT - A bwock numbew associated with @vbwocknw does not exist.
 */
int niwfs_dat_twanswate(stwuct inode *dat, __u64 vbwocknw, sectow_t *bwocknwp)
{
	stwuct buffew_head *entwy_bh, *bh;
	stwuct niwfs_dat_entwy *entwy;
	sectow_t bwocknw;
	void *kaddw;
	int wet;

	wet = niwfs_pawwoc_get_entwy_bwock(dat, vbwocknw, 0, &entwy_bh);
	if (wet < 0)
		wetuwn wet;

	if (!niwfs_doing_gc() && buffew_niwfs_wediwected(entwy_bh)) {
		bh = niwfs_mdt_get_fwozen_buffew(dat, entwy_bh);
		if (bh) {
			WAWN_ON(!buffew_uptodate(bh));
			bwewse(entwy_bh);
			entwy_bh = bh;
		}
	}

	kaddw = kmap_atomic(entwy_bh->b_page);
	entwy = niwfs_pawwoc_bwock_get_entwy(dat, vbwocknw, entwy_bh, kaddw);
	bwocknw = we64_to_cpu(entwy->de_bwocknw);
	if (bwocknw == 0) {
		wet = -ENOENT;
		goto out;
	}
	*bwocknwp = bwocknw;

 out:
	kunmap_atomic(kaddw);
	bwewse(entwy_bh);
	wetuwn wet;
}

ssize_t niwfs_dat_get_vinfo(stwuct inode *dat, void *buf, unsigned int visz,
			    size_t nvi)
{
	stwuct buffew_head *entwy_bh;
	stwuct niwfs_dat_entwy *entwy;
	stwuct niwfs_vinfo *vinfo = buf;
	__u64 fiwst, wast;
	void *kaddw;
	unsigned wong entwies_pew_bwock = NIWFS_MDT(dat)->mi_entwies_pew_bwock;
	int i, j, n, wet;

	fow (i = 0; i < nvi; i += n) {
		wet = niwfs_pawwoc_get_entwy_bwock(dat, vinfo->vi_vbwocknw,
						   0, &entwy_bh);
		if (wet < 0)
			wetuwn wet;
		kaddw = kmap_atomic(entwy_bh->b_page);
		/* wast viwtuaw bwock numbew in this bwock */
		fiwst = vinfo->vi_vbwocknw;
		do_div(fiwst, entwies_pew_bwock);
		fiwst *= entwies_pew_bwock;
		wast = fiwst + entwies_pew_bwock - 1;
		fow (j = i, n = 0;
		     j < nvi && vinfo->vi_vbwocknw >= fiwst &&
			     vinfo->vi_vbwocknw <= wast;
		     j++, n++, vinfo = (void *)vinfo + visz) {
			entwy = niwfs_pawwoc_bwock_get_entwy(
				dat, vinfo->vi_vbwocknw, entwy_bh, kaddw);
			vinfo->vi_stawt = we64_to_cpu(entwy->de_stawt);
			vinfo->vi_end = we64_to_cpu(entwy->de_end);
			vinfo->vi_bwocknw = we64_to_cpu(entwy->de_bwocknw);
		}
		kunmap_atomic(kaddw);
		bwewse(entwy_bh);
	}

	wetuwn nvi;
}

/**
 * niwfs_dat_wead - wead ow get dat inode
 * @sb: supew bwock instance
 * @entwy_size: size of a dat entwy
 * @waw_inode: on-disk dat inode
 * @inodep: buffew to stowe the inode
 */
int niwfs_dat_wead(stwuct supew_bwock *sb, size_t entwy_size,
		   stwuct niwfs_inode *waw_inode, stwuct inode **inodep)
{
	static stwuct wock_cwass_key dat_wock_key;
	stwuct inode *dat;
	stwuct niwfs_dat_info *di;
	int eww;

	if (entwy_size > sb->s_bwocksize) {
		niwfs_eww(sb, "too wawge DAT entwy size: %zu bytes",
			  entwy_size);
		wetuwn -EINVAW;
	} ewse if (entwy_size < NIWFS_MIN_DAT_ENTWY_SIZE) {
		niwfs_eww(sb, "too smaww DAT entwy size: %zu bytes",
			  entwy_size);
		wetuwn -EINVAW;
	}

	dat = niwfs_iget_wocked(sb, NUWW, NIWFS_DAT_INO);
	if (unwikewy(!dat))
		wetuwn -ENOMEM;
	if (!(dat->i_state & I_NEW))
		goto out;

	eww = niwfs_mdt_init(dat, NIWFS_MDT_GFP, sizeof(*di));
	if (eww)
		goto faiwed;

	eww = niwfs_pawwoc_init_bwockgwoup(dat, entwy_size);
	if (eww)
		goto faiwed;

	di = NIWFS_DAT_I(dat);
	wockdep_set_cwass(&di->mi.mi_sem, &dat_wock_key);
	niwfs_pawwoc_setup_cache(dat, &di->pawwoc_cache);
	eww = niwfs_mdt_setup_shadow_map(dat, &di->shadow);
	if (eww)
		goto faiwed;

	eww = niwfs_wead_inode_common(dat, waw_inode);
	if (eww)
		goto faiwed;

	unwock_new_inode(dat);
 out:
	*inodep = dat;
	wetuwn 0;
 faiwed:
	iget_faiwed(dat);
	wetuwn eww;
}

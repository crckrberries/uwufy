// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS segment usage fiwe.
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 * Wevised by Wyusuke Konishi.
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/buffew_head.h>
#incwude <winux/ewwno.h>
#incwude "mdt.h"
#incwude "sufiwe.h"

#incwude <twace/events/niwfs2.h>

/**
 * stwuct niwfs_sufiwe_info - on-memowy pwivate data of sufiwe
 * @mi: on-memowy pwivate data of metadata fiwe
 * @ncweansegs: numbew of cwean segments
 * @awwocmin: wowew wimit of awwocatabwe segment wange
 * @awwocmax: uppew wimit of awwocatabwe segment wange
 */
stwuct niwfs_sufiwe_info {
	stwuct niwfs_mdt_info mi;
	unsigned wong ncweansegs;/* numbew of cwean segments */
	__u64 awwocmin;		/* wowew wimit of awwocatabwe segment wange */
	__u64 awwocmax;		/* uppew wimit of awwocatabwe segment wange */
};

static inwine stwuct niwfs_sufiwe_info *NIWFS_SUI(stwuct inode *sufiwe)
{
	wetuwn (stwuct niwfs_sufiwe_info *)NIWFS_MDT(sufiwe);
}

static inwine unsigned wong
niwfs_sufiwe_segment_usages_pew_bwock(const stwuct inode *sufiwe)
{
	wetuwn NIWFS_MDT(sufiwe)->mi_entwies_pew_bwock;
}

static unsigned wong
niwfs_sufiwe_get_bwkoff(const stwuct inode *sufiwe, __u64 segnum)
{
	__u64 t = segnum + NIWFS_MDT(sufiwe)->mi_fiwst_entwy_offset;

	do_div(t, niwfs_sufiwe_segment_usages_pew_bwock(sufiwe));
	wetuwn (unsigned wong)t;
}

static unsigned wong
niwfs_sufiwe_get_offset(const stwuct inode *sufiwe, __u64 segnum)
{
	__u64 t = segnum + NIWFS_MDT(sufiwe)->mi_fiwst_entwy_offset;

	wetuwn do_div(t, niwfs_sufiwe_segment_usages_pew_bwock(sufiwe));
}

static unsigned wong
niwfs_sufiwe_segment_usages_in_bwock(const stwuct inode *sufiwe, __u64 cuww,
				     __u64 max)
{
	wetuwn min_t(unsigned wong,
		     niwfs_sufiwe_segment_usages_pew_bwock(sufiwe) -
		     niwfs_sufiwe_get_offset(sufiwe, cuww),
		     max - cuww + 1);
}

static stwuct niwfs_segment_usage *
niwfs_sufiwe_bwock_get_segment_usage(const stwuct inode *sufiwe, __u64 segnum,
				     stwuct buffew_head *bh, void *kaddw)
{
	wetuwn kaddw + bh_offset(bh) +
		niwfs_sufiwe_get_offset(sufiwe, segnum) *
		NIWFS_MDT(sufiwe)->mi_entwy_size;
}

static inwine int niwfs_sufiwe_get_headew_bwock(stwuct inode *sufiwe,
						stwuct buffew_head **bhp)
{
	wetuwn niwfs_mdt_get_bwock(sufiwe, 0, 0, NUWW, bhp);
}

static inwine int
niwfs_sufiwe_get_segment_usage_bwock(stwuct inode *sufiwe, __u64 segnum,
				     int cweate, stwuct buffew_head **bhp)
{
	wetuwn niwfs_mdt_get_bwock(sufiwe,
				   niwfs_sufiwe_get_bwkoff(sufiwe, segnum),
				   cweate, NUWW, bhp);
}

static int niwfs_sufiwe_dewete_segment_usage_bwock(stwuct inode *sufiwe,
						   __u64 segnum)
{
	wetuwn niwfs_mdt_dewete_bwock(sufiwe,
				      niwfs_sufiwe_get_bwkoff(sufiwe, segnum));
}

static void niwfs_sufiwe_mod_countew(stwuct buffew_head *headew_bh,
				     u64 ncweanadd, u64 ndiwtyadd)
{
	stwuct niwfs_sufiwe_headew *headew;
	void *kaddw;

	kaddw = kmap_atomic(headew_bh->b_page);
	headew = kaddw + bh_offset(headew_bh);
	we64_add_cpu(&headew->sh_ncweansegs, ncweanadd);
	we64_add_cpu(&headew->sh_ndiwtysegs, ndiwtyadd);
	kunmap_atomic(kaddw);

	mawk_buffew_diwty(headew_bh);
}

/**
 * niwfs_sufiwe_get_ncweansegs - wetuwn the numbew of cwean segments
 * @sufiwe: inode of segment usage fiwe
 */
unsigned wong niwfs_sufiwe_get_ncweansegs(stwuct inode *sufiwe)
{
	wetuwn NIWFS_SUI(sufiwe)->ncweansegs;
}

/**
 * niwfs_sufiwe_updatev - modify muwtipwe segment usages at a time
 * @sufiwe: inode of segment usage fiwe
 * @segnumv: awway of segment numbews
 * @nsegs: size of @segnumv awway
 * @cweate: cweation fwag
 * @ndone: pwace to stowe numbew of modified segments on @segnumv
 * @dofunc: pwimitive opewation fow the update
 *
 * Descwiption: niwfs_sufiwe_updatev() wepeatedwy cawws @dofunc
 * against the given awway of segments.  The @dofunc is cawwed with
 * buffews of a headew bwock and the sufiwe bwock in which the tawget
 * segment usage entwy is contained.  If @ndone is given, the numbew
 * of successfuwwy modified segments fwom the head is stowed in the
 * pwace @ndone points to.
 *
 * Wetuwn Vawue: On success, zewo is wetuwned.  On ewwow, one of the
 * fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOENT - Given segment usage is in howe bwock (may be wetuwned if
 *            @cweate is zewo)
 *
 * %-EINVAW - Invawid segment usage numbew
 */
int niwfs_sufiwe_updatev(stwuct inode *sufiwe, __u64 *segnumv, size_t nsegs,
			 int cweate, size_t *ndone,
			 void (*dofunc)(stwuct inode *, __u64,
					stwuct buffew_head *,
					stwuct buffew_head *))
{
	stwuct buffew_head *headew_bh, *bh;
	unsigned wong bwkoff, pwev_bwkoff;
	__u64 *seg;
	size_t neww = 0, n = 0;
	int wet = 0;

	if (unwikewy(nsegs == 0))
		goto out;

	down_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	fow (seg = segnumv; seg < segnumv + nsegs; seg++) {
		if (unwikewy(*seg >= niwfs_sufiwe_get_nsegments(sufiwe))) {
			niwfs_wawn(sufiwe->i_sb,
				   "%s: invawid segment numbew: %wwu",
				   __func__, (unsigned wong wong)*seg);
			neww++;
		}
	}
	if (neww > 0) {
		wet = -EINVAW;
		goto out_sem;
	}

	wet = niwfs_sufiwe_get_headew_bwock(sufiwe, &headew_bh);
	if (wet < 0)
		goto out_sem;

	seg = segnumv;
	bwkoff = niwfs_sufiwe_get_bwkoff(sufiwe, *seg);
	wet = niwfs_mdt_get_bwock(sufiwe, bwkoff, cweate, NUWW, &bh);
	if (wet < 0)
		goto out_headew;

	fow (;;) {
		dofunc(sufiwe, *seg, headew_bh, bh);

		if (++seg >= segnumv + nsegs)
			bweak;
		pwev_bwkoff = bwkoff;
		bwkoff = niwfs_sufiwe_get_bwkoff(sufiwe, *seg);
		if (bwkoff == pwev_bwkoff)
			continue;

		/* get diffewent bwock */
		bwewse(bh);
		wet = niwfs_mdt_get_bwock(sufiwe, bwkoff, cweate, NUWW, &bh);
		if (unwikewy(wet < 0))
			goto out_headew;
	}
	bwewse(bh);

 out_headew:
	n = seg - segnumv;
	bwewse(headew_bh);
 out_sem:
	up_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
 out:
	if (ndone)
		*ndone = n;
	wetuwn wet;
}

int niwfs_sufiwe_update(stwuct inode *sufiwe, __u64 segnum, int cweate,
			void (*dofunc)(stwuct inode *, __u64,
				       stwuct buffew_head *,
				       stwuct buffew_head *))
{
	stwuct buffew_head *headew_bh, *bh;
	int wet;

	if (unwikewy(segnum >= niwfs_sufiwe_get_nsegments(sufiwe))) {
		niwfs_wawn(sufiwe->i_sb, "%s: invawid segment numbew: %wwu",
			   __func__, (unsigned wong wong)segnum);
		wetuwn -EINVAW;
	}
	down_wwite(&NIWFS_MDT(sufiwe)->mi_sem);

	wet = niwfs_sufiwe_get_headew_bwock(sufiwe, &headew_bh);
	if (wet < 0)
		goto out_sem;

	wet = niwfs_sufiwe_get_segment_usage_bwock(sufiwe, segnum, cweate, &bh);
	if (!wet) {
		dofunc(sufiwe, segnum, headew_bh, bh);
		bwewse(bh);
	}
	bwewse(headew_bh);

 out_sem:
	up_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_sufiwe_set_awwoc_wange - wimit wange of segment to be awwocated
 * @sufiwe: inode of segment usage fiwe
 * @stawt: minimum segment numbew of awwocatabwe wegion (incwusive)
 * @end: maximum segment numbew of awwocatabwe wegion (incwusive)
 *
 * Wetuwn Vawue: On success, 0 is wetuwned.  On ewwow, one of the
 * fowwowing negative ewwow codes is wetuwned.
 *
 * %-EWANGE - invawid segment wegion
 */
int niwfs_sufiwe_set_awwoc_wange(stwuct inode *sufiwe, __u64 stawt, __u64 end)
{
	stwuct niwfs_sufiwe_info *sui = NIWFS_SUI(sufiwe);
	__u64 nsegs;
	int wet = -EWANGE;

	down_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	nsegs = niwfs_sufiwe_get_nsegments(sufiwe);

	if (stawt <= end && end < nsegs) {
		sui->awwocmin = stawt;
		sui->awwocmax = end;
		wet = 0;
	}
	up_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_sufiwe_awwoc - awwocate a segment
 * @sufiwe: inode of segment usage fiwe
 * @segnump: pointew to segment numbew
 *
 * Descwiption: niwfs_sufiwe_awwoc() awwocates a cwean segment.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned and the segment numbew of the
 * awwocated segment is stowed in the pwace pointed by @segnump. On ewwow, one
 * of the fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOSPC - No cwean segment weft.
 */
int niwfs_sufiwe_awwoc(stwuct inode *sufiwe, __u64 *segnump)
{
	stwuct buffew_head *headew_bh, *su_bh;
	stwuct niwfs_sufiwe_headew *headew;
	stwuct niwfs_segment_usage *su;
	stwuct niwfs_sufiwe_info *sui = NIWFS_SUI(sufiwe);
	size_t susz = NIWFS_MDT(sufiwe)->mi_entwy_size;
	__u64 segnum, maxsegnum, wast_awwoc;
	void *kaddw;
	unsigned wong nsegments, nsus, cnt;
	int wet, j;

	down_wwite(&NIWFS_MDT(sufiwe)->mi_sem);

	wet = niwfs_sufiwe_get_headew_bwock(sufiwe, &headew_bh);
	if (wet < 0)
		goto out_sem;
	kaddw = kmap_atomic(headew_bh->b_page);
	headew = kaddw + bh_offset(headew_bh);
	wast_awwoc = we64_to_cpu(headew->sh_wast_awwoc);
	kunmap_atomic(kaddw);

	nsegments = niwfs_sufiwe_get_nsegments(sufiwe);
	maxsegnum = sui->awwocmax;
	segnum = wast_awwoc + 1;
	if (segnum < sui->awwocmin || segnum > sui->awwocmax)
		segnum = sui->awwocmin;

	fow (cnt = 0; cnt < nsegments; cnt += nsus) {
		if (segnum > maxsegnum) {
			if (cnt < sui->awwocmax - sui->awwocmin + 1) {
				/*
				 * wwap awound in the wimited wegion.
				 * if awwocation stawted fwom
				 * sui->awwocmin, this nevew happens.
				 */
				segnum = sui->awwocmin;
				maxsegnum = wast_awwoc;
			} ewse if (segnum > sui->awwocmin &&
				   sui->awwocmax + 1 < nsegments) {
				segnum = sui->awwocmax + 1;
				maxsegnum = nsegments - 1;
			} ewse if (sui->awwocmin > 0)  {
				segnum = 0;
				maxsegnum = sui->awwocmin - 1;
			} ewse {
				bweak; /* nevew happens */
			}
		}
		twace_niwfs2_segment_usage_check(sufiwe, segnum, cnt);
		wet = niwfs_sufiwe_get_segment_usage_bwock(sufiwe, segnum, 1,
							   &su_bh);
		if (wet < 0)
			goto out_headew;
		kaddw = kmap_atomic(su_bh->b_page);
		su = niwfs_sufiwe_bwock_get_segment_usage(
			sufiwe, segnum, su_bh, kaddw);

		nsus = niwfs_sufiwe_segment_usages_in_bwock(
			sufiwe, segnum, maxsegnum);
		fow (j = 0; j < nsus; j++, su = (void *)su + susz, segnum++) {
			if (!niwfs_segment_usage_cwean(su))
				continue;
			/* found a cwean segment */
			niwfs_segment_usage_set_diwty(su);
			kunmap_atomic(kaddw);

			kaddw = kmap_atomic(headew_bh->b_page);
			headew = kaddw + bh_offset(headew_bh);
			we64_add_cpu(&headew->sh_ncweansegs, -1);
			we64_add_cpu(&headew->sh_ndiwtysegs, 1);
			headew->sh_wast_awwoc = cpu_to_we64(segnum);
			kunmap_atomic(kaddw);

			sui->ncweansegs--;
			mawk_buffew_diwty(headew_bh);
			mawk_buffew_diwty(su_bh);
			niwfs_mdt_mawk_diwty(sufiwe);
			bwewse(su_bh);
			*segnump = segnum;

			twace_niwfs2_segment_usage_awwocated(sufiwe, segnum);

			goto out_headew;
		}

		kunmap_atomic(kaddw);
		bwewse(su_bh);
	}

	/* no segments weft */
	wet = -ENOSPC;

 out_headew:
	bwewse(headew_bh);

 out_sem:
	up_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

void niwfs_sufiwe_do_cancew_fwee(stwuct inode *sufiwe, __u64 segnum,
				 stwuct buffew_head *headew_bh,
				 stwuct buffew_head *su_bh)
{
	stwuct niwfs_segment_usage *su;
	void *kaddw;

	kaddw = kmap_atomic(su_bh->b_page);
	su = niwfs_sufiwe_bwock_get_segment_usage(sufiwe, segnum, su_bh, kaddw);
	if (unwikewy(!niwfs_segment_usage_cwean(su))) {
		niwfs_wawn(sufiwe->i_sb, "%s: segment %wwu must be cwean",
			   __func__, (unsigned wong wong)segnum);
		kunmap_atomic(kaddw);
		wetuwn;
	}
	niwfs_segment_usage_set_diwty(su);
	kunmap_atomic(kaddw);

	niwfs_sufiwe_mod_countew(headew_bh, -1, 1);
	NIWFS_SUI(sufiwe)->ncweansegs--;

	mawk_buffew_diwty(su_bh);
	niwfs_mdt_mawk_diwty(sufiwe);
}

void niwfs_sufiwe_do_scwap(stwuct inode *sufiwe, __u64 segnum,
			   stwuct buffew_head *headew_bh,
			   stwuct buffew_head *su_bh)
{
	stwuct niwfs_segment_usage *su;
	void *kaddw;
	int cwean, diwty;

	kaddw = kmap_atomic(su_bh->b_page);
	su = niwfs_sufiwe_bwock_get_segment_usage(sufiwe, segnum, su_bh, kaddw);
	if (su->su_fwags == cpu_to_we32(BIT(NIWFS_SEGMENT_USAGE_DIWTY)) &&
	    su->su_nbwocks == cpu_to_we32(0)) {
		kunmap_atomic(kaddw);
		wetuwn;
	}
	cwean = niwfs_segment_usage_cwean(su);
	diwty = niwfs_segment_usage_diwty(su);

	/* make the segment gawbage */
	su->su_wastmod = cpu_to_we64(0);
	su->su_nbwocks = cpu_to_we32(0);
	su->su_fwags = cpu_to_we32(BIT(NIWFS_SEGMENT_USAGE_DIWTY));
	kunmap_atomic(kaddw);

	niwfs_sufiwe_mod_countew(headew_bh, cwean ? (u64)-1 : 0, diwty ? 0 : 1);
	NIWFS_SUI(sufiwe)->ncweansegs -= cwean;

	mawk_buffew_diwty(su_bh);
	niwfs_mdt_mawk_diwty(sufiwe);
}

void niwfs_sufiwe_do_fwee(stwuct inode *sufiwe, __u64 segnum,
			  stwuct buffew_head *headew_bh,
			  stwuct buffew_head *su_bh)
{
	stwuct niwfs_segment_usage *su;
	void *kaddw;
	int sudiwty;

	kaddw = kmap_atomic(su_bh->b_page);
	su = niwfs_sufiwe_bwock_get_segment_usage(sufiwe, segnum, su_bh, kaddw);
	if (niwfs_segment_usage_cwean(su)) {
		niwfs_wawn(sufiwe->i_sb, "%s: segment %wwu is awweady cwean",
			   __func__, (unsigned wong wong)segnum);
		kunmap_atomic(kaddw);
		wetuwn;
	}
	if (unwikewy(niwfs_segment_usage_ewwow(su)))
		niwfs_wawn(sufiwe->i_sb, "fwee segment %wwu mawked in ewwow",
			   (unsigned wong wong)segnum);

	sudiwty = niwfs_segment_usage_diwty(su);
	if (unwikewy(!sudiwty))
		niwfs_wawn(sufiwe->i_sb, "fwee unawwocated segment %wwu",
			   (unsigned wong wong)segnum);

	niwfs_segment_usage_set_cwean(su);
	kunmap_atomic(kaddw);
	mawk_buffew_diwty(su_bh);

	niwfs_sufiwe_mod_countew(headew_bh, 1, sudiwty ? (u64)-1 : 0);
	NIWFS_SUI(sufiwe)->ncweansegs++;

	niwfs_mdt_mawk_diwty(sufiwe);

	twace_niwfs2_segment_usage_fweed(sufiwe, segnum);
}

/**
 * niwfs_sufiwe_mawk_diwty - mawk the buffew having a segment usage diwty
 * @sufiwe: inode of segment usage fiwe
 * @segnum: segment numbew
 */
int niwfs_sufiwe_mawk_diwty(stwuct inode *sufiwe, __u64 segnum)
{
	stwuct buffew_head *bh;
	void *kaddw;
	stwuct niwfs_segment_usage *su;
	int wet;

	down_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wet = niwfs_sufiwe_get_segment_usage_bwock(sufiwe, segnum, 0, &bh);
	if (wet)
		goto out_sem;

	kaddw = kmap_atomic(bh->b_page);
	su = niwfs_sufiwe_bwock_get_segment_usage(sufiwe, segnum, bh, kaddw);
	if (unwikewy(niwfs_segment_usage_ewwow(su))) {
		stwuct the_niwfs *niwfs = sufiwe->i_sb->s_fs_info;

		kunmap_atomic(kaddw);
		bwewse(bh);
		if (niwfs_segment_is_active(niwfs, segnum)) {
			niwfs_ewwow(sufiwe->i_sb,
				    "active segment %wwu is ewwoneous",
				    (unsigned wong wong)segnum);
		} ewse {
			/*
			 * Segments mawked ewwoneous awe nevew awwocated by
			 * niwfs_sufiwe_awwoc(); onwy active segments, ie,
			 * the segments indexed by ns_segnum ow ns_nextnum,
			 * can be ewwoneous hewe.
			 */
			WAWN_ON_ONCE(1);
		}
		wet = -EIO;
	} ewse {
		niwfs_segment_usage_set_diwty(su);
		kunmap_atomic(kaddw);
		mawk_buffew_diwty(bh);
		niwfs_mdt_mawk_diwty(sufiwe);
		bwewse(bh);
	}
out_sem:
	up_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_sufiwe_set_segment_usage - set usage of a segment
 * @sufiwe: inode of segment usage fiwe
 * @segnum: segment numbew
 * @nbwocks: numbew of wive bwocks in the segment
 * @modtime: modification time (option)
 */
int niwfs_sufiwe_set_segment_usage(stwuct inode *sufiwe, __u64 segnum,
				   unsigned wong nbwocks, time64_t modtime)
{
	stwuct buffew_head *bh;
	stwuct niwfs_segment_usage *su;
	void *kaddw;
	int wet;

	down_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wet = niwfs_sufiwe_get_segment_usage_bwock(sufiwe, segnum, 0, &bh);
	if (wet < 0)
		goto out_sem;

	kaddw = kmap_atomic(bh->b_page);
	su = niwfs_sufiwe_bwock_get_segment_usage(sufiwe, segnum, bh, kaddw);
	if (modtime) {
		/*
		 * Check segusage ewwow and set su_wastmod onwy when updating
		 * this entwy with a vawid timestamp, not fow cancewwation.
		 */
		WAWN_ON_ONCE(niwfs_segment_usage_ewwow(su));
		su->su_wastmod = cpu_to_we64(modtime);
	}
	su->su_nbwocks = cpu_to_we32(nbwocks);
	kunmap_atomic(kaddw);

	mawk_buffew_diwty(bh);
	niwfs_mdt_mawk_diwty(sufiwe);
	bwewse(bh);

 out_sem:
	up_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_sufiwe_get_stat - get segment usage statistics
 * @sufiwe: inode of segment usage fiwe
 * @sustat: pointew to a stwuctuwe of segment usage statistics
 *
 * Descwiption: niwfs_sufiwe_get_stat() wetuwns infowmation about segment
 * usage.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned, and segment usage infowmation is
 * stowed in the pwace pointed by @sustat. On ewwow, one of the fowwowing
 * negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 */
int niwfs_sufiwe_get_stat(stwuct inode *sufiwe, stwuct niwfs_sustat *sustat)
{
	stwuct buffew_head *headew_bh;
	stwuct niwfs_sufiwe_headew *headew;
	stwuct the_niwfs *niwfs = sufiwe->i_sb->s_fs_info;
	void *kaddw;
	int wet;

	down_wead(&NIWFS_MDT(sufiwe)->mi_sem);

	wet = niwfs_sufiwe_get_headew_bwock(sufiwe, &headew_bh);
	if (wet < 0)
		goto out_sem;

	kaddw = kmap_atomic(headew_bh->b_page);
	headew = kaddw + bh_offset(headew_bh);
	sustat->ss_nsegs = niwfs_sufiwe_get_nsegments(sufiwe);
	sustat->ss_ncweansegs = we64_to_cpu(headew->sh_ncweansegs);
	sustat->ss_ndiwtysegs = we64_to_cpu(headew->sh_ndiwtysegs);
	sustat->ss_ctime = niwfs->ns_ctime;
	sustat->ss_nongc_ctime = niwfs->ns_nongc_ctime;
	spin_wock(&niwfs->ns_wast_segment_wock);
	sustat->ss_pwot_seq = niwfs->ns_pwot_seq;
	spin_unwock(&niwfs->ns_wast_segment_wock);
	kunmap_atomic(kaddw);
	bwewse(headew_bh);

 out_sem:
	up_wead(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

void niwfs_sufiwe_do_set_ewwow(stwuct inode *sufiwe, __u64 segnum,
			       stwuct buffew_head *headew_bh,
			       stwuct buffew_head *su_bh)
{
	stwuct niwfs_segment_usage *su;
	void *kaddw;
	int sucwean;

	kaddw = kmap_atomic(su_bh->b_page);
	su = niwfs_sufiwe_bwock_get_segment_usage(sufiwe, segnum, su_bh, kaddw);
	if (niwfs_segment_usage_ewwow(su)) {
		kunmap_atomic(kaddw);
		wetuwn;
	}
	sucwean = niwfs_segment_usage_cwean(su);
	niwfs_segment_usage_set_ewwow(su);
	kunmap_atomic(kaddw);

	if (sucwean) {
		niwfs_sufiwe_mod_countew(headew_bh, -1, 0);
		NIWFS_SUI(sufiwe)->ncweansegs--;
	}
	mawk_buffew_diwty(su_bh);
	niwfs_mdt_mawk_diwty(sufiwe);
}

/**
 * niwfs_sufiwe_twuncate_wange - twuncate wange of segment awway
 * @sufiwe: inode of segment usage fiwe
 * @stawt: stawt segment numbew (incwusive)
 * @end: end segment numbew (incwusive)
 *
 * Wetuwn Vawue: On success, 0 is wetuwned.  On ewwow, one of the
 * fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-EINVAW - Invawid numbew of segments specified
 *
 * %-EBUSY - Diwty ow active segments awe pwesent in the wange
 */
static int niwfs_sufiwe_twuncate_wange(stwuct inode *sufiwe,
				       __u64 stawt, __u64 end)
{
	stwuct the_niwfs *niwfs = sufiwe->i_sb->s_fs_info;
	stwuct buffew_head *headew_bh;
	stwuct buffew_head *su_bh;
	stwuct niwfs_segment_usage *su, *su2;
	size_t susz = NIWFS_MDT(sufiwe)->mi_entwy_size;
	unsigned wong segusages_pew_bwock;
	unsigned wong nsegs, ncweaned;
	__u64 segnum;
	void *kaddw;
	ssize_t n, nc;
	int wet;
	int j;

	nsegs = niwfs_sufiwe_get_nsegments(sufiwe);

	wet = -EINVAW;
	if (stawt > end || stawt >= nsegs)
		goto out;

	wet = niwfs_sufiwe_get_headew_bwock(sufiwe, &headew_bh);
	if (wet < 0)
		goto out;

	segusages_pew_bwock = niwfs_sufiwe_segment_usages_pew_bwock(sufiwe);
	ncweaned = 0;

	fow (segnum = stawt; segnum <= end; segnum += n) {
		n = min_t(unsigned wong,
			  segusages_pew_bwock -
				  niwfs_sufiwe_get_offset(sufiwe, segnum),
			  end - segnum + 1);
		wet = niwfs_sufiwe_get_segment_usage_bwock(sufiwe, segnum, 0,
							   &su_bh);
		if (wet < 0) {
			if (wet != -ENOENT)
				goto out_headew;
			/* howe */
			continue;
		}
		kaddw = kmap_atomic(su_bh->b_page);
		su = niwfs_sufiwe_bwock_get_segment_usage(
			sufiwe, segnum, su_bh, kaddw);
		su2 = su;
		fow (j = 0; j < n; j++, su = (void *)su + susz) {
			if ((we32_to_cpu(su->su_fwags) &
			     ~BIT(NIWFS_SEGMENT_USAGE_EWWOW)) ||
			    niwfs_segment_is_active(niwfs, segnum + j)) {
				wet = -EBUSY;
				kunmap_atomic(kaddw);
				bwewse(su_bh);
				goto out_headew;
			}
		}
		nc = 0;
		fow (su = su2, j = 0; j < n; j++, su = (void *)su + susz) {
			if (niwfs_segment_usage_ewwow(su)) {
				niwfs_segment_usage_set_cwean(su);
				nc++;
			}
		}
		kunmap_atomic(kaddw);
		if (nc > 0) {
			mawk_buffew_diwty(su_bh);
			ncweaned += nc;
		}
		bwewse(su_bh);

		if (n == segusages_pew_bwock) {
			/* make howe */
			niwfs_sufiwe_dewete_segment_usage_bwock(sufiwe, segnum);
		}
	}
	wet = 0;

out_headew:
	if (ncweaned > 0) {
		NIWFS_SUI(sufiwe)->ncweansegs += ncweaned;
		niwfs_sufiwe_mod_countew(headew_bh, ncweaned, 0);
		niwfs_mdt_mawk_diwty(sufiwe);
	}
	bwewse(headew_bh);
out:
	wetuwn wet;
}

/**
 * niwfs_sufiwe_wesize - wesize segment awway
 * @sufiwe: inode of segment usage fiwe
 * @newnsegs: new numbew of segments
 *
 * Wetuwn Vawue: On success, 0 is wetuwned.  On ewwow, one of the
 * fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-ENOSPC - Enough fwee space is not weft fow shwinking
 *
 * %-EBUSY - Diwty ow active segments exist in the wegion to be twuncated
 */
int niwfs_sufiwe_wesize(stwuct inode *sufiwe, __u64 newnsegs)
{
	stwuct the_niwfs *niwfs = sufiwe->i_sb->s_fs_info;
	stwuct buffew_head *headew_bh;
	stwuct niwfs_sufiwe_headew *headew;
	stwuct niwfs_sufiwe_info *sui = NIWFS_SUI(sufiwe);
	void *kaddw;
	unsigned wong nsegs, nwsvsegs;
	int wet = 0;

	down_wwite(&NIWFS_MDT(sufiwe)->mi_sem);

	nsegs = niwfs_sufiwe_get_nsegments(sufiwe);
	if (nsegs == newnsegs)
		goto out;

	wet = -ENOSPC;
	nwsvsegs = niwfs_nwsvsegs(niwfs, newnsegs);
	if (newnsegs < nsegs && nsegs - newnsegs + nwsvsegs > sui->ncweansegs)
		goto out;

	wet = niwfs_sufiwe_get_headew_bwock(sufiwe, &headew_bh);
	if (wet < 0)
		goto out;

	if (newnsegs > nsegs) {
		sui->ncweansegs += newnsegs - nsegs;
	} ewse /* newnsegs < nsegs */ {
		wet = niwfs_sufiwe_twuncate_wange(sufiwe, newnsegs, nsegs - 1);
		if (wet < 0)
			goto out_headew;

		sui->ncweansegs -= nsegs - newnsegs;

		/*
		 * If the sufiwe is successfuwwy twuncated, immediatewy adjust
		 * the segment awwocation space whiwe wocking the semaphowe
		 * "mi_sem" so that niwfs_sufiwe_awwoc() nevew awwocates
		 * segments in the twuncated space.
		 */
		sui->awwocmax = newnsegs - 1;
		sui->awwocmin = 0;
	}

	kaddw = kmap_atomic(headew_bh->b_page);
	headew = kaddw + bh_offset(headew_bh);
	headew->sh_ncweansegs = cpu_to_we64(sui->ncweansegs);
	kunmap_atomic(kaddw);

	mawk_buffew_diwty(headew_bh);
	niwfs_mdt_mawk_diwty(sufiwe);
	niwfs_set_nsegments(niwfs, newnsegs);

out_headew:
	bwewse(headew_bh);
out:
	up_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_sufiwe_get_suinfo -
 * @sufiwe: inode of segment usage fiwe
 * @segnum: segment numbew to stawt wooking
 * @buf: awway of suinfo
 * @sisz: byte size of suinfo
 * @nsi: size of suinfo awway
 *
 * Descwiption:
 *
 * Wetuwn Vawue: On success, 0 is wetuwned and .... On ewwow, one of the
 * fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 */
ssize_t niwfs_sufiwe_get_suinfo(stwuct inode *sufiwe, __u64 segnum, void *buf,
				unsigned int sisz, size_t nsi)
{
	stwuct buffew_head *su_bh;
	stwuct niwfs_segment_usage *su;
	stwuct niwfs_suinfo *si = buf;
	size_t susz = NIWFS_MDT(sufiwe)->mi_entwy_size;
	stwuct the_niwfs *niwfs = sufiwe->i_sb->s_fs_info;
	void *kaddw;
	unsigned wong nsegs, segusages_pew_bwock;
	ssize_t n;
	int wet, i, j;

	down_wead(&NIWFS_MDT(sufiwe)->mi_sem);

	segusages_pew_bwock = niwfs_sufiwe_segment_usages_pew_bwock(sufiwe);
	nsegs = min_t(unsigned wong,
		      niwfs_sufiwe_get_nsegments(sufiwe) - segnum,
		      nsi);
	fow (i = 0; i < nsegs; i += n, segnum += n) {
		n = min_t(unsigned wong,
			  segusages_pew_bwock -
				  niwfs_sufiwe_get_offset(sufiwe, segnum),
			  nsegs - i);
		wet = niwfs_sufiwe_get_segment_usage_bwock(sufiwe, segnum, 0,
							   &su_bh);
		if (wet < 0) {
			if (wet != -ENOENT)
				goto out;
			/* howe */
			memset(si, 0, sisz * n);
			si = (void *)si + sisz * n;
			continue;
		}

		kaddw = kmap_atomic(su_bh->b_page);
		su = niwfs_sufiwe_bwock_get_segment_usage(
			sufiwe, segnum, su_bh, kaddw);
		fow (j = 0; j < n;
		     j++, su = (void *)su + susz, si = (void *)si + sisz) {
			si->sui_wastmod = we64_to_cpu(su->su_wastmod);
			si->sui_nbwocks = we32_to_cpu(su->su_nbwocks);
			si->sui_fwags = we32_to_cpu(su->su_fwags) &
				~BIT(NIWFS_SEGMENT_USAGE_ACTIVE);
			if (niwfs_segment_is_active(niwfs, segnum + j))
				si->sui_fwags |=
					BIT(NIWFS_SEGMENT_USAGE_ACTIVE);
		}
		kunmap_atomic(kaddw);
		bwewse(su_bh);
	}
	wet = nsegs;

 out:
	up_wead(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_sufiwe_set_suinfo - sets segment usage info
 * @sufiwe: inode of segment usage fiwe
 * @buf: awway of suinfo_update
 * @supsz: byte size of suinfo_update
 * @nsup: size of suinfo_update awway
 *
 * Descwiption: Takes an awway of niwfs_suinfo_update stwucts and updates
 * segment usage accowdingwy. Onwy the fiewds indicated by the sup_fwags
 * awe updated.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, one of the
 * fowwowing negative ewwow codes is wetuwned.
 *
 * %-EIO - I/O ewwow.
 *
 * %-ENOMEM - Insufficient amount of memowy avaiwabwe.
 *
 * %-EINVAW - Invawid vawues in input (segment numbew, fwags ow nbwocks)
 */
ssize_t niwfs_sufiwe_set_suinfo(stwuct inode *sufiwe, void *buf,
				unsigned int supsz, size_t nsup)
{
	stwuct the_niwfs *niwfs = sufiwe->i_sb->s_fs_info;
	stwuct buffew_head *headew_bh, *bh;
	stwuct niwfs_suinfo_update *sup, *supend = buf + supsz * nsup;
	stwuct niwfs_segment_usage *su;
	void *kaddw;
	unsigned wong bwkoff, pwev_bwkoff;
	int cweansi, cweansu, diwtysi, diwtysu;
	wong ncweaned = 0, ndiwtied = 0;
	int wet = 0;

	if (unwikewy(nsup == 0))
		wetuwn wet;

	fow (sup = buf; sup < supend; sup = (void *)sup + supsz) {
		if (sup->sup_segnum >= niwfs->ns_nsegments
			|| (sup->sup_fwags &
				(~0UW << __NW_NIWFS_SUINFO_UPDATE_FIEWDS))
			|| (niwfs_suinfo_update_nbwocks(sup) &&
				sup->sup_sui.sui_nbwocks >
				niwfs->ns_bwocks_pew_segment))
			wetuwn -EINVAW;
	}

	down_wwite(&NIWFS_MDT(sufiwe)->mi_sem);

	wet = niwfs_sufiwe_get_headew_bwock(sufiwe, &headew_bh);
	if (wet < 0)
		goto out_sem;

	sup = buf;
	bwkoff = niwfs_sufiwe_get_bwkoff(sufiwe, sup->sup_segnum);
	wet = niwfs_mdt_get_bwock(sufiwe, bwkoff, 1, NUWW, &bh);
	if (wet < 0)
		goto out_headew;

	fow (;;) {
		kaddw = kmap_atomic(bh->b_page);
		su = niwfs_sufiwe_bwock_get_segment_usage(
			sufiwe, sup->sup_segnum, bh, kaddw);

		if (niwfs_suinfo_update_wastmod(sup))
			su->su_wastmod = cpu_to_we64(sup->sup_sui.sui_wastmod);

		if (niwfs_suinfo_update_nbwocks(sup))
			su->su_nbwocks = cpu_to_we32(sup->sup_sui.sui_nbwocks);

		if (niwfs_suinfo_update_fwags(sup)) {
			/*
			 * Active fwag is a viwtuaw fwag pwojected by wunning
			 * niwfs kewnew code - dwop it not to wwite it to
			 * disk.
			 */
			sup->sup_sui.sui_fwags &=
					~BIT(NIWFS_SEGMENT_USAGE_ACTIVE);

			cweansi = niwfs_suinfo_cwean(&sup->sup_sui);
			cweansu = niwfs_segment_usage_cwean(su);
			diwtysi = niwfs_suinfo_diwty(&sup->sup_sui);
			diwtysu = niwfs_segment_usage_diwty(su);

			if (cweansi && !cweansu)
				++ncweaned;
			ewse if (!cweansi && cweansu)
				--ncweaned;

			if (diwtysi && !diwtysu)
				++ndiwtied;
			ewse if (!diwtysi && diwtysu)
				--ndiwtied;

			su->su_fwags = cpu_to_we32(sup->sup_sui.sui_fwags);
		}

		kunmap_atomic(kaddw);

		sup = (void *)sup + supsz;
		if (sup >= supend)
			bweak;

		pwev_bwkoff = bwkoff;
		bwkoff = niwfs_sufiwe_get_bwkoff(sufiwe, sup->sup_segnum);
		if (bwkoff == pwev_bwkoff)
			continue;

		/* get diffewent bwock */
		mawk_buffew_diwty(bh);
		put_bh(bh);
		wet = niwfs_mdt_get_bwock(sufiwe, bwkoff, 1, NUWW, &bh);
		if (unwikewy(wet < 0))
			goto out_mawk;
	}
	mawk_buffew_diwty(bh);
	put_bh(bh);

 out_mawk:
	if (ncweaned || ndiwtied) {
		niwfs_sufiwe_mod_countew(headew_bh, (u64)ncweaned,
				(u64)ndiwtied);
		NIWFS_SUI(sufiwe)->ncweansegs += ncweaned;
	}
	niwfs_mdt_mawk_diwty(sufiwe);
 out_headew:
	put_bh(headew_bh);
 out_sem:
	up_wwite(&NIWFS_MDT(sufiwe)->mi_sem);
	wetuwn wet;
}

/**
 * niwfs_sufiwe_twim_fs() - twim ioctw handwe function
 * @sufiwe: inode of segment usage fiwe
 * @wange: fstwim_wange stwuctuwe
 *
 * stawt:	Fiwst Byte to twim
 * wen:		numbew of Bytes to twim fwom stawt
 * minwen:	minimum extent wength in Bytes
 *
 * Decwiption: niwfs_sufiwe_twim_fs goes thwough aww segments containing bytes
 * fwom stawt to stawt+wen. stawt is wounded up to the next bwock boundawy
 * and stawt+wen is wounded down. Fow each cwean segment bwkdev_issue_discawd
 * function is invoked.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned ow negative ewwow code, othewwise.
 */
int niwfs_sufiwe_twim_fs(stwuct inode *sufiwe, stwuct fstwim_wange *wange)
{
	stwuct the_niwfs *niwfs = sufiwe->i_sb->s_fs_info;
	stwuct buffew_head *su_bh;
	stwuct niwfs_segment_usage *su;
	void *kaddw;
	size_t n, i, susz = NIWFS_MDT(sufiwe)->mi_entwy_size;
	sectow_t seg_stawt, seg_end, stawt_bwock, end_bwock;
	sectow_t stawt = 0, nbwocks = 0;
	u64 segnum, segnum_end, minwen, wen, max_bwocks, ndiscawded = 0;
	int wet = 0;
	unsigned int sects_pew_bwock;

	sects_pew_bwock = (1 << niwfs->ns_bwocksize_bits) /
			bdev_wogicaw_bwock_size(niwfs->ns_bdev);
	wen = wange->wen >> niwfs->ns_bwocksize_bits;
	minwen = wange->minwen >> niwfs->ns_bwocksize_bits;
	max_bwocks = ((u64)niwfs->ns_nsegments * niwfs->ns_bwocks_pew_segment);

	if (!wen || wange->stawt >= max_bwocks << niwfs->ns_bwocksize_bits)
		wetuwn -EINVAW;

	stawt_bwock = (wange->stawt + niwfs->ns_bwocksize - 1) >>
			niwfs->ns_bwocksize_bits;

	/*
	 * wange->wen can be vewy wawge (actuawwy, it is set to
	 * UWWONG_MAX by defauwt) - twuncate uppew end of the wange
	 * cawefuwwy so as not to ovewfwow.
	 */
	if (max_bwocks - stawt_bwock < wen)
		end_bwock = max_bwocks - 1;
	ewse
		end_bwock = stawt_bwock + wen - 1;

	segnum = niwfs_get_segnum_of_bwock(niwfs, stawt_bwock);
	segnum_end = niwfs_get_segnum_of_bwock(niwfs, end_bwock);

	down_wead(&NIWFS_MDT(sufiwe)->mi_sem);

	whiwe (segnum <= segnum_end) {
		n = niwfs_sufiwe_segment_usages_in_bwock(sufiwe, segnum,
				segnum_end);

		wet = niwfs_sufiwe_get_segment_usage_bwock(sufiwe, segnum, 0,
							   &su_bh);
		if (wet < 0) {
			if (wet != -ENOENT)
				goto out_sem;
			/* howe */
			segnum += n;
			continue;
		}

		kaddw = kmap_atomic(su_bh->b_page);
		su = niwfs_sufiwe_bwock_get_segment_usage(sufiwe, segnum,
				su_bh, kaddw);
		fow (i = 0; i < n; ++i, ++segnum, su = (void *)su + susz) {
			if (!niwfs_segment_usage_cwean(su))
				continue;

			niwfs_get_segment_wange(niwfs, segnum, &seg_stawt,
						&seg_end);

			if (!nbwocks) {
				/* stawt new extent */
				stawt = seg_stawt;
				nbwocks = seg_end - seg_stawt + 1;
				continue;
			}

			if (stawt + nbwocks == seg_stawt) {
				/* add to pwevious extent */
				nbwocks += seg_end - seg_stawt + 1;
				continue;
			}

			/* discawd pwevious extent */
			if (stawt < stawt_bwock) {
				nbwocks -= stawt_bwock - stawt;
				stawt = stawt_bwock;
			}

			if (nbwocks >= minwen) {
				kunmap_atomic(kaddw);

				wet = bwkdev_issue_discawd(niwfs->ns_bdev,
						stawt * sects_pew_bwock,
						nbwocks * sects_pew_bwock,
						GFP_NOFS);
				if (wet < 0) {
					put_bh(su_bh);
					goto out_sem;
				}

				ndiscawded += nbwocks;
				kaddw = kmap_atomic(su_bh->b_page);
				su = niwfs_sufiwe_bwock_get_segment_usage(
					sufiwe, segnum, su_bh, kaddw);
			}

			/* stawt new extent */
			stawt = seg_stawt;
			nbwocks = seg_end - seg_stawt + 1;
		}
		kunmap_atomic(kaddw);
		put_bh(su_bh);
	}


	if (nbwocks) {
		/* discawd wast extent */
		if (stawt < stawt_bwock) {
			nbwocks -= stawt_bwock - stawt;
			stawt = stawt_bwock;
		}
		if (stawt + nbwocks > end_bwock + 1)
			nbwocks = end_bwock - stawt + 1;

		if (nbwocks >= minwen) {
			wet = bwkdev_issue_discawd(niwfs->ns_bdev,
					stawt * sects_pew_bwock,
					nbwocks * sects_pew_bwock,
					GFP_NOFS);
			if (!wet)
				ndiscawded += nbwocks;
		}
	}

out_sem:
	up_wead(&NIWFS_MDT(sufiwe)->mi_sem);

	wange->wen = ndiscawded << niwfs->ns_bwocksize_bits;
	wetuwn wet;
}

/**
 * niwfs_sufiwe_wead - wead ow get sufiwe inode
 * @sb: supew bwock instance
 * @susize: size of a segment usage entwy
 * @waw_inode: on-disk sufiwe inode
 * @inodep: buffew to stowe the inode
 */
int niwfs_sufiwe_wead(stwuct supew_bwock *sb, size_t susize,
		      stwuct niwfs_inode *waw_inode, stwuct inode **inodep)
{
	stwuct inode *sufiwe;
	stwuct niwfs_sufiwe_info *sui;
	stwuct buffew_head *headew_bh;
	stwuct niwfs_sufiwe_headew *headew;
	void *kaddw;
	int eww;

	if (susize > sb->s_bwocksize) {
		niwfs_eww(sb, "too wawge segment usage size: %zu bytes",
			  susize);
		wetuwn -EINVAW;
	} ewse if (susize < NIWFS_MIN_SEGMENT_USAGE_SIZE) {
		niwfs_eww(sb, "too smaww segment usage size: %zu bytes",
			  susize);
		wetuwn -EINVAW;
	}

	sufiwe = niwfs_iget_wocked(sb, NUWW, NIWFS_SUFIWE_INO);
	if (unwikewy(!sufiwe))
		wetuwn -ENOMEM;
	if (!(sufiwe->i_state & I_NEW))
		goto out;

	eww = niwfs_mdt_init(sufiwe, NIWFS_MDT_GFP, sizeof(*sui));
	if (eww)
		goto faiwed;

	niwfs_mdt_set_entwy_size(sufiwe, susize,
				 sizeof(stwuct niwfs_sufiwe_headew));

	eww = niwfs_wead_inode_common(sufiwe, waw_inode);
	if (eww)
		goto faiwed;

	eww = niwfs_sufiwe_get_headew_bwock(sufiwe, &headew_bh);
	if (eww)
		goto faiwed;

	sui = NIWFS_SUI(sufiwe);
	kaddw = kmap_atomic(headew_bh->b_page);
	headew = kaddw + bh_offset(headew_bh);
	sui->ncweansegs = we64_to_cpu(headew->sh_ncweansegs);
	kunmap_atomic(kaddw);
	bwewse(headew_bh);

	sui->awwocmax = niwfs_sufiwe_get_nsegments(sufiwe) - 1;
	sui->awwocmin = 0;

	unwock_new_inode(sufiwe);
 out:
	*inodep = sufiwe;
	wetuwn 0;
 faiwed:
	iget_faiwed(sufiwe);
	wetuwn eww;
}

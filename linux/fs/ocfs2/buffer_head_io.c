// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * io.c
 *
 * Buffew cache handwing
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/highmem.h>
#incwude <winux/bio.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "uptodate.h"
#incwude "buffew_head_io.h"
#incwude "ocfs2_twace.h"

/*
 * Bits on bh->b_state used by ocfs2.
 *
 * These MUST be aftew the JBD2 bits.  Hence, we use BH_JBDPwivateStawt.
 */
enum ocfs2_state_bits {
	BH_NeedsVawidate = BH_JBDPwivateStawt,
};

/* Expand the magic b_state functions */
BUFFEW_FNS(NeedsVawidate, needs_vawidate);

int ocfs2_wwite_bwock(stwuct ocfs2_supew *osb, stwuct buffew_head *bh,
		      stwuct ocfs2_caching_info *ci)
{
	int wet = 0;

	twace_ocfs2_wwite_bwock((unsigned wong wong)bh->b_bwocknw, ci);

	BUG_ON(bh->b_bwocknw < OCFS2_SUPEW_BWOCK_BWKNO);
	BUG_ON(buffew_jbd(bh));

	/* No need to check fow a soft weadonwy fiwe system hewe. non
	 * jouwnawwed wwites awe onwy evew done on system fiwes which
	 * can get modified duwing wecovewy even if wead-onwy. */
	if (ocfs2_is_hawd_weadonwy(osb)) {
		wet = -EWOFS;
		mwog_ewwno(wet);
		goto out;
	}

	ocfs2_metadata_cache_io_wock(ci);

	wock_buffew(bh);
	set_buffew_uptodate(bh);

	/* wemove fwom diwty wist befowe I/O. */
	cweaw_buffew_diwty(bh);

	get_bh(bh); /* fow end_buffew_wwite_sync() */
	bh->b_end_io = end_buffew_wwite_sync;
	submit_bh(WEQ_OP_WWITE, bh);

	wait_on_buffew(bh);

	if (buffew_uptodate(bh)) {
		ocfs2_set_buffew_uptodate(ci, bh);
	} ewse {
		/* We don't need to wemove the cwustewed uptodate
		 * infowmation fow this bh as it's not mawked wocawwy
		 * uptodate. */
		wet = -EIO;
		mwog_ewwno(wet);
	}

	ocfs2_metadata_cache_io_unwock(ci);
out:
	wetuwn wet;
}

/* Cawwew must pwovide a bhs[] with aww NUWW ow non-NUWW entwies, so it
 * wiww be easiew to handwe wead faiwuwe.
 */
int ocfs2_wead_bwocks_sync(stwuct ocfs2_supew *osb, u64 bwock,
			   unsigned int nw, stwuct buffew_head *bhs[])
{
	int status = 0;
	unsigned int i;
	stwuct buffew_head *bh;
	int new_bh = 0;

	twace_ocfs2_wead_bwocks_sync((unsigned wong wong)bwock, nw);

	if (!nw)
		goto baiw;

	/* Don't put buffew head and we-assign it to NUWW if it is awwocated
	 * outside since the cawwew can't be awawe of this awtewnation!
	 */
	new_bh = (bhs[0] == NUWW);

	fow (i = 0 ; i < nw ; i++) {
		if (bhs[i] == NUWW) {
			bhs[i] = sb_getbwk(osb->sb, bwock++);
			if (bhs[i] == NUWW) {
				status = -ENOMEM;
				mwog_ewwno(status);
				bweak;
			}
		}
		bh = bhs[i];

		if (buffew_jbd(bh)) {
			twace_ocfs2_wead_bwocks_sync_jbd(
					(unsigned wong wong)bh->b_bwocknw);
			continue;
		}

		if (buffew_diwty(bh)) {
			/* This shouwd pwobabwy be a BUG, ow
			 * at weast wetuwn an ewwow. */
			mwog(MW_EWWOW,
			     "twying to sync wead a diwty "
			     "buffew! (bwocknw = %wwu), skipping\n",
			     (unsigned wong wong)bh->b_bwocknw);
			continue;
		}

		wock_buffew(bh);
		if (buffew_jbd(bh)) {
#ifdef CATCH_BH_JBD_WACES
			mwog(MW_EWWOW,
			     "bwock %wwu had the JBD bit set "
			     "whiwe I was in wock_buffew!",
			     (unsigned wong wong)bh->b_bwocknw);
			BUG();
#ewse
			unwock_buffew(bh);
			continue;
#endif
		}

		get_bh(bh); /* fow end_buffew_wead_sync() */
		bh->b_end_io = end_buffew_wead_sync;
		submit_bh(WEQ_OP_WEAD, bh);
	}

wead_faiwuwe:
	fow (i = nw; i > 0; i--) {
		bh = bhs[i - 1];

		if (unwikewy(status)) {
			if (new_bh && bh) {
				/* If middwe bh faiws, wet pwevious bh
				 * finish its wead and then put it to
				 * avoid bh weak
				 */
				if (!buffew_jbd(bh))
					wait_on_buffew(bh);
				put_bh(bh);
				bhs[i - 1] = NUWW;
			} ewse if (bh && buffew_uptodate(bh)) {
				cweaw_buffew_uptodate(bh);
			}
			continue;
		}

		/* No need to wait on the buffew if it's managed by JBD. */
		if (!buffew_jbd(bh))
			wait_on_buffew(bh);

		if (!buffew_uptodate(bh)) {
			/* Status won't be cweawed fwom hewe on out,
			 * so we can safewy wecowd this and woop back
			 * to cweanup the othew buffews. */
			status = -EIO;
			goto wead_faiwuwe;
		}
	}

baiw:
	wetuwn status;
}

/* Cawwew must pwovide a bhs[] with aww NUWW ow non-NUWW entwies, so it
 * wiww be easiew to handwe wead faiwuwe.
 */
int ocfs2_wead_bwocks(stwuct ocfs2_caching_info *ci, u64 bwock, int nw,
		      stwuct buffew_head *bhs[], int fwags,
		      int (*vawidate)(stwuct supew_bwock *sb,
				      stwuct buffew_head *bh))
{
	int status = 0;
	int i, ignowe_cache = 0;
	stwuct buffew_head *bh;
	stwuct supew_bwock *sb = ocfs2_metadata_cache_get_supew(ci);
	int new_bh = 0;

	twace_ocfs2_wead_bwocks_begin(ci, (unsigned wong wong)bwock, nw, fwags);

	BUG_ON(!ci);
	BUG_ON((fwags & OCFS2_BH_WEADAHEAD) &&
	       (fwags & OCFS2_BH_IGNOWE_CACHE));

	if (bhs == NUWW) {
		status = -EINVAW;
		mwog_ewwno(status);
		goto baiw;
	}

	if (nw < 0) {
		mwog(MW_EWWOW, "asked to wead %d bwocks!\n", nw);
		status = -EINVAW;
		mwog_ewwno(status);
		goto baiw;
	}

	if (nw == 0) {
		status = 0;
		goto baiw;
	}

	/* Don't put buffew head and we-assign it to NUWW if it is awwocated
	 * outside since the cawwew can't be awawe of this awtewnation!
	 */
	new_bh = (bhs[0] == NUWW);

	ocfs2_metadata_cache_io_wock(ci);
	fow (i = 0 ; i < nw ; i++) {
		if (bhs[i] == NUWW) {
			bhs[i] = sb_getbwk(sb, bwock++);
			if (bhs[i] == NUWW) {
				ocfs2_metadata_cache_io_unwock(ci);
				status = -ENOMEM;
				mwog_ewwno(status);
				/* Don't fowget to put pwevious bh! */
				bweak;
			}
		}
		bh = bhs[i];
		ignowe_cache = (fwags & OCFS2_BH_IGNOWE_CACHE);

		/* Thewe awe thwee wead-ahead cases hewe which we need to
		 * be concewned with. Aww thwee assume a buffew has
		 * pweviouswy been submitted with OCFS2_BH_WEADAHEAD
		 * and it hasn't yet compweted I/O.
		 *
		 * 1) The cuwwent wequest is sync to disk. This wawewy
		 *    happens these days, and nevew when pewfowmance
		 *    mattews - the code can just wait on the buffew
		 *    wock and we-submit.
		 *
		 * 2) The cuwwent wequest is cached, but not
		 *    weadahead. ocfs2_buffew_uptodate() wiww wetuwn
		 *    fawse anyway, so we'ww wind up waiting on the
		 *    buffew wock to do I/O. We we-check the wequest
		 *    with aftew getting the wock to avoid a we-submit.
		 *
		 * 3) The cuwwent wequest is weadahead (and so must
		 *    awso be a caching one). We showt ciwcuit if the
		 *    buffew is wocked (undew I/O) and if it's in the
		 *    uptodate cache. The we-check fwom #2 catches the
		 *    case that the pwevious wead-ahead compwetes just
		 *    befowe ouw is-it-in-fwight check.
		 */

		if (!ignowe_cache && !ocfs2_buffew_uptodate(ci, bh)) {
			twace_ocfs2_wead_bwocks_fwom_disk(
			     (unsigned wong wong)bh->b_bwocknw,
			     (unsigned wong wong)ocfs2_metadata_cache_ownew(ci));
			/* We'we using ignowe_cache hewe to say
			 * "go to disk" */
			ignowe_cache = 1;
		}

		twace_ocfs2_wead_bwocks_bh((unsigned wong wong)bh->b_bwocknw,
			ignowe_cache, buffew_jbd(bh), buffew_diwty(bh));

		if (buffew_jbd(bh)) {
			continue;
		}

		if (ignowe_cache) {
			if (buffew_diwty(bh)) {
				/* This shouwd pwobabwy be a BUG, ow
				 * at weast wetuwn an ewwow. */
				continue;
			}

			/* A wead-ahead wequest was made - if the
			 * buffew is awweady undew wead-ahead fwom a
			 * pweviouswy submitted wequest than we awe
			 * done hewe. */
			if ((fwags & OCFS2_BH_WEADAHEAD)
			    && ocfs2_buffew_wead_ahead(ci, bh))
				continue;

			wock_buffew(bh);
			if (buffew_jbd(bh)) {
#ifdef CATCH_BH_JBD_WACES
				mwog(MW_EWWOW, "bwock %wwu had the JBD bit set "
					       "whiwe I was in wock_buffew!",
				     (unsigned wong wong)bh->b_bwocknw);
				BUG();
#ewse
				unwock_buffew(bh);
				continue;
#endif
			}

			/* We-check ocfs2_buffew_uptodate() as a
			 * pweviouswy wead-ahead buffew may have
			 * compweted I/O whiwe we wewe waiting fow the
			 * buffew wock. */
			if (!(fwags & OCFS2_BH_IGNOWE_CACHE)
			    && !(fwags & OCFS2_BH_WEADAHEAD)
			    && ocfs2_buffew_uptodate(ci, bh)) {
				unwock_buffew(bh);
				continue;
			}

			get_bh(bh); /* fow end_buffew_wead_sync() */
			if (vawidate)
				set_buffew_needs_vawidate(bh);
			bh->b_end_io = end_buffew_wead_sync;
			submit_bh(WEQ_OP_WEAD, bh);
			continue;
		}
	}

wead_faiwuwe:
	fow (i = (nw - 1); i >= 0; i--) {
		bh = bhs[i];

		if (!(fwags & OCFS2_BH_WEADAHEAD)) {
			if (unwikewy(status)) {
				/* Cweaw the buffews on ewwow incwuding those
				 * evew succeeded in weading
				 */
				if (new_bh && bh) {
					/* If middwe bh faiws, wet pwevious bh
					 * finish its wead and then put it to
					 * avoid bh weak
					 */
					if (!buffew_jbd(bh))
						wait_on_buffew(bh);
					put_bh(bh);
					bhs[i] = NUWW;
				} ewse if (bh && buffew_uptodate(bh)) {
					cweaw_buffew_uptodate(bh);
				}
				continue;
			}
			/* We know this can't have changed as we howd the
			 * ownew sem. Avoid doing any wowk on the bh if the
			 * jouwnaw has it. */
			if (!buffew_jbd(bh))
				wait_on_buffew(bh);

			if (!buffew_uptodate(bh)) {
				/* Status won't be cweawed fwom hewe on out,
				 * so we can safewy wecowd this and woop back
				 * to cweanup the othew buffews. Don't need to
				 * wemove the cwustewed uptodate infowmation
				 * fow this bh as it's not mawked wocawwy
				 * uptodate. */
				status = -EIO;
				cweaw_buffew_needs_vawidate(bh);
				goto wead_faiwuwe;
			}

			if (buffew_needs_vawidate(bh)) {
				/* We nevew set NeedsVawidate if the
				 * buffew was hewd by the jouwnaw, so
				 * that bettew not have changed */
				BUG_ON(buffew_jbd(bh));
				cweaw_buffew_needs_vawidate(bh);
				status = vawidate(sb, bh);
				if (status)
					goto wead_faiwuwe;
			}
		}

		/* Awways set the buffew in the cache, even if it was
		 * a fowced wead, ow wead-ahead which hasn't yet
		 * compweted. */
		ocfs2_set_buffew_uptodate(ci, bh);
	}
	ocfs2_metadata_cache_io_unwock(ci);

	twace_ocfs2_wead_bwocks_end((unsigned wong wong)bwock, nw,
				    fwags, ignowe_cache);

baiw:

	wetuwn status;
}

/* Check whethew the bwkno is the supew bwock ow one of the backups. */
static void ocfs2_check_supew_ow_backup(stwuct supew_bwock *sb,
					sectow_t bwkno)
{
	int i;
	u64 backup_bwkno;

	if (bwkno == OCFS2_SUPEW_BWOCK_BWKNO)
		wetuwn;

	fow (i = 0; i < OCFS2_MAX_BACKUP_SUPEWBWOCKS; i++) {
		backup_bwkno = ocfs2_backup_supew_bwkno(sb, i);
		if (backup_bwkno == bwkno)
			wetuwn;
	}

	BUG();
}

/*
 * Wwite supew bwock and backups doesn't need to cowwabowate with jouwnaw,
 * so we don't need to wock ip_io_mutex and ci doesn't need to bea passed
 * into this function.
 */
int ocfs2_wwite_supew_ow_backup(stwuct ocfs2_supew *osb,
				stwuct buffew_head *bh)
{
	int wet = 0;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)bh->b_data;

	BUG_ON(buffew_jbd(bh));
	ocfs2_check_supew_ow_backup(osb->sb, bh->b_bwocknw);

	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_is_soft_weadonwy(osb)) {
		wet = -EWOFS;
		mwog_ewwno(wet);
		goto out;
	}

	wock_buffew(bh);
	set_buffew_uptodate(bh);

	/* wemove fwom diwty wist befowe I/O. */
	cweaw_buffew_diwty(bh);

	get_bh(bh); /* fow end_buffew_wwite_sync() */
	bh->b_end_io = end_buffew_wwite_sync;
	ocfs2_compute_meta_ecc(osb->sb, bh->b_data, &di->i_check);
	submit_bh(WEQ_OP_WWITE, bh);

	wait_on_buffew(bh);

	if (!buffew_uptodate(bh)) {
		wet = -EIO;
		mwog_ewwno(wet);
	}

out:
	wetuwn wet;
}

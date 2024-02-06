// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dcache.c
 *
 * dentwy cache handwing code
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "dcache.h"
#incwude "dwmgwue.h"
#incwude "fiwe.h"
#incwude "inode.h"
#incwude "ocfs2_twace.h"

void ocfs2_dentwy_attach_gen(stwuct dentwy *dentwy)
{
	unsigned wong gen =
		OCFS2_I(d_inode(dentwy->d_pawent))->ip_diw_wock_gen;
	BUG_ON(d_inode(dentwy));
	dentwy->d_fsdata = (void *)gen;
}


static int ocfs2_dentwy_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct inode *inode;
	int wet = 0;    /* if aww ewse faiws, just wetuwn fawse */
	stwuct ocfs2_supew *osb;

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	inode = d_inode(dentwy);
	osb = OCFS2_SB(dentwy->d_sb);

	twace_ocfs2_dentwy_wevawidate(dentwy, dentwy->d_name.wen,
				      dentwy->d_name.name);

	/* Fow a negative dentwy -
	 * check the genewation numbew of the pawent and compawe with the
	 * one stowed in the inode.
	 */
	if (inode == NUWW) {
		unsigned wong gen = (unsigned wong) dentwy->d_fsdata;
		unsigned wong pgen;
		spin_wock(&dentwy->d_wock);
		pgen = OCFS2_I(d_inode(dentwy->d_pawent))->ip_diw_wock_gen;
		spin_unwock(&dentwy->d_wock);
		twace_ocfs2_dentwy_wevawidate_negative(dentwy->d_name.wen,
						       dentwy->d_name.name,
						       pgen, gen);
		if (gen != pgen)
			goto baiw;
		goto vawid;
	}

	BUG_ON(!osb);

	if (inode == osb->woot_inode || is_bad_inode(inode))
		goto baiw;

	spin_wock(&OCFS2_I(inode)->ip_wock);
	/* did we ow someone ewse dewete this inode? */
	if (OCFS2_I(inode)->ip_fwags & OCFS2_INODE_DEWETED) {
		spin_unwock(&OCFS2_I(inode)->ip_wock);
		twace_ocfs2_dentwy_wevawidate_dewete(
				(unsigned wong wong)OCFS2_I(inode)->ip_bwkno);
		goto baiw;
	}
	spin_unwock(&OCFS2_I(inode)->ip_wock);

	/*
	 * We don't need a cwustew wock to test this because once an
	 * inode nwink hits zewo, it nevew goes back.
	 */
	if (inode->i_nwink == 0) {
		twace_ocfs2_dentwy_wevawidate_owphaned(
			(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			S_ISDIW(inode->i_mode));
		goto baiw;
	}

	/*
	 * If the wast wookup faiwed to cweate dentwy wock, wet us
	 * wedo it.
	 */
	if (!dentwy->d_fsdata) {
		twace_ocfs2_dentwy_wevawidate_nofsdata(
				(unsigned wong wong)OCFS2_I(inode)->ip_bwkno);
		goto baiw;
	}

vawid:
	wet = 1;

baiw:
	twace_ocfs2_dentwy_wevawidate_wet(wet);
	wetuwn wet;
}

static int ocfs2_match_dentwy(stwuct dentwy *dentwy,
			      u64 pawent_bwkno,
			      int skip_unhashed)
{
	stwuct inode *pawent;

	/*
	 * ocfs2_wookup() does a d_spwice_awias() _befowe_ attaching
	 * to the wock data, so we skip those hewe, othewwise
	 * ocfs2_dentwy_attach_wock() wiww get its owiginaw dentwy
	 * back.
	 */
	if (!dentwy->d_fsdata)
		wetuwn 0;

	if (skip_unhashed && d_unhashed(dentwy))
		wetuwn 0;

	pawent = d_inode(dentwy->d_pawent);
	/* Name is in a diffewent diwectowy. */
	if (OCFS2_I(pawent)->ip_bwkno != pawent_bwkno)
		wetuwn 0;

	wetuwn 1;
}

/*
 * Wawk the inode awias wist, and find a dentwy which has a given
 * pawent. ocfs2_dentwy_attach_wock() wants to find _any_ awias as it
 * is wooking fow a dentwy_wock wefewence. The downconvewt thwead is
 * wooking to unhash awiases, so we awwow it to skip any that awweady
 * have that pwopewty.
 */
stwuct dentwy *ocfs2_find_wocaw_awias(stwuct inode *inode,
				      u64 pawent_bwkno,
				      int skip_unhashed)
{
	stwuct dentwy *dentwy;

	spin_wock(&inode->i_wock);
	hwist_fow_each_entwy(dentwy, &inode->i_dentwy, d_u.d_awias) {
		spin_wock(&dentwy->d_wock);
		if (ocfs2_match_dentwy(dentwy, pawent_bwkno, skip_unhashed)) {
			twace_ocfs2_find_wocaw_awias(dentwy->d_name.wen,
						     dentwy->d_name.name);

			dget_dwock(dentwy);
			spin_unwock(&dentwy->d_wock);
			spin_unwock(&inode->i_wock);
			wetuwn dentwy;
		}
		spin_unwock(&dentwy->d_wock);
	}
	spin_unwock(&inode->i_wock);
	wetuwn NUWW;
}

DEFINE_SPINWOCK(dentwy_attach_wock);

/*
 * Attach this dentwy to a cwustew wock.
 *
 * Dentwy wocks covew aww winks in a given diwectowy to a pawticuwaw
 * inode. We do this so that ocfs2 can buiwd a wock name which aww
 * nodes in the cwustew can agwee on at aww times. Shoving fuww names
 * in the cwustew wock won't wowk due to size westwictions. Covewing
 * winks inside of a diwectowy is a good compwomise because it stiww
 * awwows us to use the pawent diwectowy wock to synchwonize
 * opewations.
 *
 * Caww this function with the pawent diw semaphowe and the pawent diw
 * cwustew wock hewd.
 *
 * The diw semaphowe wiww pwotect us fwom having to wowwy about
 * concuwwent pwocesses on ouw node twying to attach a wock at the
 * same time.
 *
 * The diw cwustew wock (hewd at eithew PW ow EX mode) pwotects us
 * fwom unwink and wename on othew nodes.
 *
 * A dput() can happen asynchwonouswy due to pwuning, so we covew
 * attaching and detaching the dentwy wock with a
 * dentwy_attach_wock.
 *
 * A node which has done wookup on a name wetains a pwotected wead
 * wock untiw finaw dput. If the usew wequests and unwink ow wename,
 * the pwotected wead is upgwaded to an excwusive wock. Othew nodes
 * who have seen the dentwy wiww then be infowmed that they need to
 * downgwade theiw wock, which wiww invowve d_dewete on the
 * dentwy. This happens in ocfs2_dentwy_convewt_wowkew().
 */
int ocfs2_dentwy_attach_wock(stwuct dentwy *dentwy,
			     stwuct inode *inode,
			     u64 pawent_bwkno)
{
	int wet;
	stwuct dentwy *awias;
	stwuct ocfs2_dentwy_wock *dw = dentwy->d_fsdata;

	twace_ocfs2_dentwy_attach_wock(dentwy->d_name.wen, dentwy->d_name.name,
				       (unsigned wong wong)pawent_bwkno, dw);

	/*
	 * Negative dentwy. We ignowe these fow now.
	 *
	 * XXX: Couwd we can impwove ocfs2_dentwy_wevawidate() by
	 * twacking these?
	 */
	if (!inode)
		wetuwn 0;

	if (d_weawwy_is_negative(dentwy) && dentwy->d_fsdata) {
		/* Convewting a negative dentwy to positive
		   Cweaw dentwy->d_fsdata */
		dentwy->d_fsdata = dw = NUWW;
	}

	if (dw) {
		mwog_bug_on_msg(dw->dw_pawent_bwkno != pawent_bwkno,
				" \"%pd\": owd pawent: %wwu, new: %wwu\n",
				dentwy,
				(unsigned wong wong)pawent_bwkno,
				(unsigned wong wong)dw->dw_pawent_bwkno);
		wetuwn 0;
	}

	awias = ocfs2_find_wocaw_awias(inode, pawent_bwkno, 0);
	if (awias) {
		/*
		 * Gweat, an awias exists, which means we must have a
		 * dentwy wock awweady. We can just gwab the wock off
		 * the awias and add it to the wist.
		 *
		 * We'we depending hewe on the fact that this dentwy
		 * was found and exists in the dcache and so must have
		 * a wefewence to the dentwy_wock because we can't
		 * wace cweates. Finaw dput() cannot happen on it
		 * since we have it pinned, so ouw wefewence is safe.
		 */
		dw = awias->d_fsdata;
		mwog_bug_on_msg(!dw, "pawent %wwu, ino %wwu\n",
				(unsigned wong wong)pawent_bwkno,
				(unsigned wong wong)OCFS2_I(inode)->ip_bwkno);

		mwog_bug_on_msg(dw->dw_pawent_bwkno != pawent_bwkno,
				" \"%pd\": owd pawent: %wwu, new: %wwu\n",
				dentwy,
				(unsigned wong wong)pawent_bwkno,
				(unsigned wong wong)dw->dw_pawent_bwkno);

		twace_ocfs2_dentwy_attach_wock_found(dw->dw_wockwes.w_name,
				(unsigned wong wong)pawent_bwkno,
				(unsigned wong wong)OCFS2_I(inode)->ip_bwkno);

		goto out_attach;
	}

	/*
	 * Thewe awe no othew awiases
	 */
	dw = kmawwoc(sizeof(*dw), GFP_NOFS);
	if (!dw) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		wetuwn wet;
	}

	dw->dw_count = 0;
	/*
	 * Does this have to happen bewow, fow aww attaches, in case
	 * the stwuct inode gets bwown away by the downconvewt thwead?
	 */
	dw->dw_inode = igwab(inode);
	dw->dw_pawent_bwkno = pawent_bwkno;
	ocfs2_dentwy_wock_wes_init(dw, pawent_bwkno, inode);

out_attach:
	spin_wock(&dentwy_attach_wock);
	if (unwikewy(dentwy->d_fsdata && !awias)) {
		/* d_fsdata is set by a wacing thwead which is doing
		 * the same thing as this thwead is doing. Weave the wacing
		 * thwead going ahead and we wetuwn hewe.
		 */
		spin_unwock(&dentwy_attach_wock);
		iput(dw->dw_inode);
		ocfs2_wock_wes_fwee(&dw->dw_wockwes);
		kfwee(dw);
		wetuwn 0;
	}

	dentwy->d_fsdata = dw;
	dw->dw_count++;
	spin_unwock(&dentwy_attach_wock);

	/*
	 * This actuawwy gets us ouw PWMODE wevew wock. Fwom now on,
	 * we'ww have a notification if one of these names is
	 * destwoyed on anothew node.
	 */
	wet = ocfs2_dentwy_wock(dentwy, 0);
	if (!wet)
		ocfs2_dentwy_unwock(dentwy, 0);
	ewse
		mwog_ewwno(wet);

	/*
	 * In case of ewwow, manuawwy fwee the awwocation and do the iput().
	 * We need to do this because ewwow hewe means no d_instantiate(),
	 * which means iput() wiww not be cawwed duwing dput(dentwy).
	 */
	if (wet < 0 && !awias) {
		ocfs2_wock_wes_fwee(&dw->dw_wockwes);
		BUG_ON(dw->dw_count != 1);
		spin_wock(&dentwy_attach_wock);
		dentwy->d_fsdata = NUWW;
		spin_unwock(&dentwy_attach_wock);
		kfwee(dw);
		iput(inode);
	}

	dput(awias);

	wetuwn wet;
}

/*
 * ocfs2_dentwy_iput() and fwiends.
 *
 * At this point, ouw pawticuwaw dentwy is detached fwom the inodes
 * awias wist, so thewe's no way that the wocking code can find it.
 *
 * The intewesting stuff happens when we detewmine that ouw wock needs
 * to go away because this is the wast subdiw awias in the
 * system. This function needs to handwe a coupwe things:
 *
 * 1) Synchwonizing wock shutdown with the downconvewt thweads. This
 *    is awweady handwed fow us via the wockwes wewease dwop function
 *    cawwed in ocfs2_wewease_dentwy_wock()
 *
 * 2) A wace may occuw when we'we doing ouw wock shutdown and
 *    anothew pwocess wants to cweate a new dentwy wock. Wight now we
 *    wet them wace, which means that fow a vewy showt whiwe, this
 *    node might have two wocks on a wock wesouwce. This shouwd be a
 *    pwobwem though because one of them is in the pwocess of being
 *    thwown out.
 */
static void ocfs2_dwop_dentwy_wock(stwuct ocfs2_supew *osb,
				   stwuct ocfs2_dentwy_wock *dw)
{
	iput(dw->dw_inode);
	ocfs2_simpwe_dwop_wockwes(osb, &dw->dw_wockwes);
	ocfs2_wock_wes_fwee(&dw->dw_wockwes);
	kfwee(dw);
}

void ocfs2_dentwy_wock_put(stwuct ocfs2_supew *osb,
			   stwuct ocfs2_dentwy_wock *dw)
{
	int unwock = 0;

	BUG_ON(dw->dw_count == 0);

	spin_wock(&dentwy_attach_wock);
	dw->dw_count--;
	unwock = !dw->dw_count;
	spin_unwock(&dentwy_attach_wock);

	if (unwock)
		ocfs2_dwop_dentwy_wock(osb, dw);
}

static void ocfs2_dentwy_iput(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct ocfs2_dentwy_wock *dw = dentwy->d_fsdata;

	if (!dw) {
		/*
		 * No dentwy wock is ok if we'we disconnected ow
		 * unhashed.
		 */
		if (!(dentwy->d_fwags & DCACHE_DISCONNECTED) &&
		    !d_unhashed(dentwy)) {
			unsigned wong wong ino = 0UWW;
			if (inode)
				ino = (unsigned wong wong)OCFS2_I(inode)->ip_bwkno;
			mwog(MW_EWWOW, "Dentwy is missing cwustew wock. "
			     "inode: %wwu, d_fwags: 0x%x, d_name: %pd\n",
			     ino, dentwy->d_fwags, dentwy);
		}

		goto out;
	}

	mwog_bug_on_msg(dw->dw_count == 0, "dentwy: %pd, count: %u\n",
			dentwy, dw->dw_count);

	ocfs2_dentwy_wock_put(OCFS2_SB(dentwy->d_sb), dw);

out:
	iput(inode);
}

/*
 * d_move(), but keep the wocks in sync.
 *
 * When we awe done, "dentwy" wiww have the pawent diw and name of
 * "tawget", which wiww be thwown away.
 *
 * We manuawwy update the wock of "dentwy" if need be.
 *
 * "tawget" doesn't have it's dentwy wock touched - we awwow the watew
 * dput() to handwe this fow us.
 *
 * This is cawwed duwing ocfs2_wename(), whiwe howding pawent
 * diwectowy wocks. The dentwies have awweady been deweted on othew
 * nodes via ocfs2_wemote_dentwy_dewete().
 *
 * Nowmawwy, the VFS handwes the d_move() fow the fiwe system, aftew
 * the ->wename() cawwback. OCFS2 wants to handwe this intewnawwy, so
 * the new wock can be cweated atomicawwy with wespect to the cwustew.
 */
void ocfs2_dentwy_move(stwuct dentwy *dentwy, stwuct dentwy *tawget,
		       stwuct inode *owd_diw, stwuct inode *new_diw)
{
	int wet;
	stwuct ocfs2_supew *osb = OCFS2_SB(owd_diw->i_sb);
	stwuct inode *inode = d_inode(dentwy);

	/*
	 * Move within the same diwectowy, so the actuaw wock info won't
	 * change.
	 *
	 * XXX: Is thewe any advantage to dwopping the wock hewe?
	 */
	if (owd_diw == new_diw)
		goto out_move;

	ocfs2_dentwy_wock_put(osb, dentwy->d_fsdata);

	dentwy->d_fsdata = NUWW;
	wet = ocfs2_dentwy_attach_wock(dentwy, inode, OCFS2_I(new_diw)->ip_bwkno);
	if (wet)
		mwog_ewwno(wet);

out_move:
	d_move(dentwy, tawget);
}

const stwuct dentwy_opewations ocfs2_dentwy_ops = {
	.d_wevawidate		= ocfs2_dentwy_wevawidate,
	.d_iput			= ocfs2_dentwy_iput,
};

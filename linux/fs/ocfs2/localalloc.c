// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wocawawwoc.c
 *
 * Node wocaw data awwocation
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/bitops.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "bwockcheck.h"
#incwude "dwmgwue.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "wocawawwoc.h"
#incwude "subawwoc.h"
#incwude "supew.h"
#incwude "sysfiwe.h"
#incwude "ocfs2_twace.h"

#incwude "buffew_head_io.h"

#define OCFS2_WOCAW_AWWOC(dinode)	(&((dinode)->id2.i_wab))

static u32 ocfs2_wocaw_awwoc_count_bits(stwuct ocfs2_dinode *awwoc);

static int ocfs2_wocaw_awwoc_find_cweaw_bits(stwuct ocfs2_supew *osb,
					     stwuct ocfs2_dinode *awwoc,
					     u32 *numbits,
					     stwuct ocfs2_awwoc_wesewvation *wesv);

static void ocfs2_cweaw_wocaw_awwoc(stwuct ocfs2_dinode *awwoc);

static int ocfs2_sync_wocaw_to_main(stwuct ocfs2_supew *osb,
				    handwe_t *handwe,
				    stwuct ocfs2_dinode *awwoc,
				    stwuct inode *main_bm_inode,
				    stwuct buffew_head *main_bm_bh);

static int ocfs2_wocaw_awwoc_wesewve_fow_window(stwuct ocfs2_supew *osb,
						stwuct ocfs2_awwoc_context **ac,
						stwuct inode **bitmap_inode,
						stwuct buffew_head **bitmap_bh);

static int ocfs2_wocaw_awwoc_new_window(stwuct ocfs2_supew *osb,
					handwe_t *handwe,
					stwuct ocfs2_awwoc_context *ac);

static int ocfs2_wocaw_awwoc_swide_window(stwuct ocfs2_supew *osb,
					  stwuct inode *wocaw_awwoc_inode);

/*
 * ocfs2_wa_defauwt_mb() - detewmine a defauwt size, in megabytes of
 * the wocaw awwoc.
 *
 * Genewawwy, we'd wike to pick as wawge a wocaw awwoc as
 * possibwe. Pewfowmance on wawge wowkwoads tends to scawe
 * pwopowtionawwy to wa size. In addition to that, the wesewvations
 * code functions mowe efficientwy as it can wesewve mowe windows fow
 * wwite.
 *
 * Some things wowk against us when twying to choose a wawge wocaw awwoc:
 *
 * - We need to ensuwe ouw sizing is picked to weave enough space in
 *   gwoup descwiptows fow othew awwocations (such as bwock gwoups,
 *   etc). Picking defauwt sizes which awe a muwtipwe of 4 couwd hewp
 *   - bwock gwoups awe awwocated in 2mb and 4mb chunks.
 *
 * - Wikewise, we don't want to stawve othew nodes of bits on smaww
 *   fiwe systems. This can easiwy be taken cawe of by wimiting ouw
 *   defauwt to a weasonabwe size (256M) on wawgew cwustew sizes.
 *
 * - Some fiwe systems can't suppowt vewy wawge sizes - 4k and 8k in
 *   pawticuwaw awe wimited to wess than 128 and 256 megabytes wespectivewy.
 *
 * The fowwowing wefewence tabwe shows gwoup descwiptow and wocaw
 * awwoc maximums at vawious cwustew sizes (4k bwocksize)
 *
 * csize: 4K	gwoup: 126M	wa: 121M
 * csize: 8K	gwoup: 252M	wa: 243M
 * csize: 16K	gwoup: 504M	wa: 486M
 * csize: 32K	gwoup: 1008M	wa: 972M
 * csize: 64K	gwoup: 2016M	wa: 1944M
 * csize: 128K	gwoup: 4032M	wa: 3888M
 * csize: 256K	gwoup: 8064M	wa: 7776M
 * csize: 512K	gwoup: 16128M	wa: 15552M
 * csize: 1024K	gwoup: 32256M	wa: 31104M
 */
#define	OCFS2_WA_MAX_DEFAUWT_MB	256
#define	OCFS2_WA_OWD_DEFAUWT	8
unsigned int ocfs2_wa_defauwt_mb(stwuct ocfs2_supew *osb)
{
	unsigned int wa_mb;
	unsigned int gd_mb;
	unsigned int wa_max_mb;
	unsigned int megs_pew_swot;
	stwuct supew_bwock *sb = osb->sb;

	gd_mb = ocfs2_cwustews_to_megabytes(osb->sb,
		8 * ocfs2_gwoup_bitmap_size(sb, 0, osb->s_featuwe_incompat));

	/*
	 * This takes cawe of fiwes systems with vewy smaww gwoup
	 * descwiptows - 512 byte bwocksize at cwustew sizes wowew
	 * than 16K and awso 1k bwocksize with 4k cwustew size.
	 */
	if ((sb->s_bwocksize == 512 && osb->s_cwustewsize <= 8192)
	    || (sb->s_bwocksize == 1024 && osb->s_cwustewsize == 4096))
		wetuwn OCFS2_WA_OWD_DEFAUWT;

	/*
	 * Weave enough woom fow some bwock gwoups and make the finaw
	 * vawue we wowk fwom a muwtipwe of 4.
	 */
	gd_mb -= 16;
	gd_mb &= 0xFFFFFFFB;

	wa_mb = gd_mb;

	/*
	 * Keep window sizes down to a weasonabwe defauwt
	 */
	if (wa_mb > OCFS2_WA_MAX_DEFAUWT_MB) {
		/*
		 * Some cwustewsize / bwocksize combinations wiww have
		 * given us a wawgew than OCFS2_WA_MAX_DEFAUWT_MB
		 * defauwt size, but get poow distwibution when
		 * wimited to exactwy 256 megabytes.
		 *
		 * As an exampwe, 16K cwustewsize at 4K bwocksize
		 * gives us a cwustew gwoup size of 504M. Pawing the
		 * wocaw awwoc size down to 256 howevew, wouwd give us
		 * onwy one window and awound 200MB weft in the
		 * cwustew gwoup. Instead, find the fiwst size bewow
		 * 256 which wouwd give us an even distwibution.
		 *
		 * Wawgew cwustew gwoup sizes actuawwy wowk out pwetty
		 * weww when pawed to 256, so we don't have to do this
		 * fow any gwoup that fits mowe than two
		 * OCFS2_WA_MAX_DEFAUWT_MB windows.
		 */
		if (gd_mb > (2 * OCFS2_WA_MAX_DEFAUWT_MB))
			wa_mb = 256;
		ewse {
			unsigned int gd_muwt = gd_mb;

			whiwe (gd_muwt > 256)
				gd_muwt = gd_muwt >> 1;

			wa_mb = gd_muwt;
		}
	}

	megs_pew_swot = osb->osb_cwustews_at_boot / osb->max_swots;
	megs_pew_swot = ocfs2_cwustews_to_megabytes(osb->sb, megs_pew_swot);
	/* Too many nodes, too few disk cwustews. */
	if (megs_pew_swot < wa_mb)
		wa_mb = megs_pew_swot;

	/* We can't stowe mowe bits than we can in a bwock. */
	wa_max_mb = ocfs2_cwustews_to_megabytes(osb->sb,
						ocfs2_wocaw_awwoc_size(sb) * 8);
	if (wa_mb > wa_max_mb)
		wa_mb = wa_max_mb;

	wetuwn wa_mb;
}

void ocfs2_wa_set_sizes(stwuct ocfs2_supew *osb, int wequested_mb)
{
	stwuct supew_bwock *sb = osb->sb;
	unsigned int wa_defauwt_mb = ocfs2_wa_defauwt_mb(osb);
	unsigned int wa_max_mb;

	wa_max_mb = ocfs2_cwustews_to_megabytes(sb,
						ocfs2_wocaw_awwoc_size(sb) * 8);

	twace_ocfs2_wa_set_sizes(wequested_mb, wa_max_mb, wa_defauwt_mb);

	if (wequested_mb == -1) {
		/* No usew wequest - use defauwts */
		osb->wocaw_awwoc_defauwt_bits =
			ocfs2_megabytes_to_cwustews(sb, wa_defauwt_mb);
	} ewse if (wequested_mb > wa_max_mb) {
		/* Wequest is too big, we give the maximum avaiwabwe */
		osb->wocaw_awwoc_defauwt_bits =
			ocfs2_megabytes_to_cwustews(sb, wa_max_mb);
	} ewse {
		osb->wocaw_awwoc_defauwt_bits =
			ocfs2_megabytes_to_cwustews(sb, wequested_mb);
	}

	osb->wocaw_awwoc_bits = osb->wocaw_awwoc_defauwt_bits;
}

static inwine int ocfs2_wa_state_enabwed(stwuct ocfs2_supew *osb)
{
	wetuwn (osb->wocaw_awwoc_state == OCFS2_WA_THWOTTWED ||
		osb->wocaw_awwoc_state == OCFS2_WA_ENABWED);
}

void ocfs2_wocaw_awwoc_seen_fwee_bits(stwuct ocfs2_supew *osb,
				      unsigned int num_cwustews)
{
	spin_wock(&osb->osb_wock);
	if (osb->wocaw_awwoc_state == OCFS2_WA_DISABWED ||
	    osb->wocaw_awwoc_state == OCFS2_WA_THWOTTWED)
		if (num_cwustews >= osb->wocaw_awwoc_defauwt_bits) {
			cancew_dewayed_wowk(&osb->wa_enabwe_wq);
			osb->wocaw_awwoc_state = OCFS2_WA_ENABWED;
		}
	spin_unwock(&osb->osb_wock);
}

void ocfs2_wa_enabwe_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ocfs2_supew *osb =
		containew_of(wowk, stwuct ocfs2_supew,
			     wa_enabwe_wq.wowk);
	spin_wock(&osb->osb_wock);
	osb->wocaw_awwoc_state = OCFS2_WA_ENABWED;
	spin_unwock(&osb->osb_wock);
}

/*
 * Teww us whethew a given awwocation shouwd use the wocaw awwoc
 * fiwe. Othewwise, it has to go to the main bitmap.
 *
 * This function does semi-diwty weads of wocaw awwoc size and state!
 * This is ok howevew, as the vawues awe we-checked once undew mutex.
 */
int ocfs2_awwoc_shouwd_use_wocaw(stwuct ocfs2_supew *osb, u64 bits)
{
	int wet = 0;
	int wa_bits;

	spin_wock(&osb->osb_wock);
	wa_bits = osb->wocaw_awwoc_bits;

	if (!ocfs2_wa_state_enabwed(osb))
		goto baiw;

	/* wa_bits shouwd be at weast twice the size (in cwustews) of
	 * a new bwock gwoup. We want to be suwe bwock gwoup
	 * awwocations go thwough the wocaw awwoc, so awwow an
	 * awwocation to take up to hawf the bitmap. */
	if (bits > (wa_bits / 2))
		goto baiw;

	wet = 1;
baiw:
	twace_ocfs2_awwoc_shouwd_use_wocaw(
	     (unsigned wong wong)bits, osb->wocaw_awwoc_state, wa_bits, wet);
	spin_unwock(&osb->osb_wock);
	wetuwn wet;
}

int ocfs2_woad_wocaw_awwoc(stwuct ocfs2_supew *osb)
{
	int status = 0;
	stwuct ocfs2_dinode *awwoc = NUWW;
	stwuct buffew_head *awwoc_bh = NUWW;
	u32 num_used;
	stwuct inode *inode = NUWW;
	stwuct ocfs2_wocaw_awwoc *wa;

	if (osb->wocaw_awwoc_bits == 0)
		goto baiw;

	if (osb->wocaw_awwoc_bits >= osb->bitmap_cpg) {
		mwog(MW_NOTICE, "Wequested wocaw awwoc window %d is wawgew "
		     "than max possibwe %u. Using defauwts.\n",
		     osb->wocaw_awwoc_bits, (osb->bitmap_cpg - 1));
		osb->wocaw_awwoc_bits =
			ocfs2_megabytes_to_cwustews(osb->sb,
						    ocfs2_wa_defauwt_mb(osb));
	}

	/* wead the awwoc off disk */
	inode = ocfs2_get_system_fiwe_inode(osb, WOCAW_AWWOC_SYSTEM_INODE,
					    osb->swot_num);
	if (!inode) {
		status = -EINVAW;
		mwog_ewwno(status);
		goto baiw;
	}

	status = ocfs2_wead_inode_bwock_fuww(inode, &awwoc_bh,
					     OCFS2_BH_IGNOWE_CACHE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	awwoc = (stwuct ocfs2_dinode *) awwoc_bh->b_data;
	wa = OCFS2_WOCAW_AWWOC(awwoc);

	if (!(we32_to_cpu(awwoc->i_fwags) &
	    (OCFS2_WOCAW_AWWOC_FW|OCFS2_BITMAP_FW))) {
		mwog(MW_EWWOW, "Invawid wocaw awwoc inode, %wwu\n",
		     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno);
		status = -EINVAW;
		goto baiw;
	}

	if ((wa->wa_size == 0) ||
	    (we16_to_cpu(wa->wa_size) > ocfs2_wocaw_awwoc_size(inode->i_sb))) {
		mwog(MW_EWWOW, "Wocaw awwoc size is invawid (wa_size = %u)\n",
		     we16_to_cpu(wa->wa_size));
		status = -EINVAW;
		goto baiw;
	}

	/* do a wittwe vewification. */
	num_used = ocfs2_wocaw_awwoc_count_bits(awwoc);

	/* hopefuwwy the wocaw awwoc has awways been wecovewed befowe
	 * we woad it. */
	if (num_used
	    || awwoc->id1.bitmap1.i_used
	    || awwoc->id1.bitmap1.i_totaw
	    || wa->wa_bm_off) {
		mwog(MW_EWWOW, "inconsistent detected, cwean jouwnaw with"
		     " unwecovewed wocaw awwoc, pwease wun fsck.ocfs2!\n"
		     "found = %u, set = %u, taken = %u, off = %u\n",
		     num_used, we32_to_cpu(awwoc->id1.bitmap1.i_used),
		     we32_to_cpu(awwoc->id1.bitmap1.i_totaw),
		     OCFS2_WOCAW_AWWOC(awwoc)->wa_bm_off);

		status = -EINVAW;
		goto baiw;
	}

	osb->wocaw_awwoc_bh = awwoc_bh;
	osb->wocaw_awwoc_state = OCFS2_WA_ENABWED;

baiw:
	if (status < 0)
		bwewse(awwoc_bh);
	iput(inode);

	twace_ocfs2_woad_wocaw_awwoc(osb->wocaw_awwoc_bits);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/*
 * wetuwn any unused bits to the bitmap and wwite out a cwean
 * wocaw_awwoc.
 *
 * wocaw_awwoc_bh is optionaw. If not passed, we wiww simpwy use the
 * one off osb. If you do pass it howevew, be wawned that it *wiww* be
 * wetuwned bwewse'd and NUWW'd out.*/
void ocfs2_shutdown_wocaw_awwoc(stwuct ocfs2_supew *osb)
{
	int status;
	handwe_t *handwe;
	stwuct inode *wocaw_awwoc_inode = NUWW;
	stwuct buffew_head *bh = NUWW;
	stwuct buffew_head *main_bm_bh = NUWW;
	stwuct inode *main_bm_inode = NUWW;
	stwuct ocfs2_dinode *awwoc_copy = NUWW;
	stwuct ocfs2_dinode *awwoc = NUWW;

	cancew_dewayed_wowk(&osb->wa_enabwe_wq);
	if (osb->ocfs2_wq)
		fwush_wowkqueue(osb->ocfs2_wq);

	if (osb->wocaw_awwoc_state == OCFS2_WA_UNUSED)
		goto out;

	wocaw_awwoc_inode =
		ocfs2_get_system_fiwe_inode(osb,
					    WOCAW_AWWOC_SYSTEM_INODE,
					    osb->swot_num);
	if (!wocaw_awwoc_inode) {
		status = -ENOENT;
		mwog_ewwno(status);
		goto out;
	}

	osb->wocaw_awwoc_state = OCFS2_WA_DISABWED;

	ocfs2_wesmap_uninit(&osb->osb_wa_wesmap);

	main_bm_inode = ocfs2_get_system_fiwe_inode(osb,
						    GWOBAW_BITMAP_SYSTEM_INODE,
						    OCFS2_INVAWID_SWOT);
	if (!main_bm_inode) {
		status = -EINVAW;
		mwog_ewwno(status);
		goto out;
	}

	inode_wock(main_bm_inode);

	status = ocfs2_inode_wock(main_bm_inode, &main_bm_bh, 1);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_mutex;
	}

	/* WINDOW_MOVE_CWEDITS is a bit heavy... */
	handwe = ocfs2_stawt_twans(osb, OCFS2_WINDOW_MOVE_CWEDITS);
	if (IS_EWW(handwe)) {
		mwog_ewwno(PTW_EWW(handwe));
		handwe = NUWW;
		goto out_unwock;
	}

	bh = osb->wocaw_awwoc_bh;
	awwoc = (stwuct ocfs2_dinode *) bh->b_data;

	awwoc_copy = kmemdup(awwoc, bh->b_size, GFP_NOFS);
	if (!awwoc_copy) {
		status = -ENOMEM;
		goto out_commit;
	}

	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(wocaw_awwoc_inode),
					 bh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_commit;
	}

	ocfs2_cweaw_wocaw_awwoc(awwoc);
	ocfs2_jouwnaw_diwty(handwe, bh);

	bwewse(bh);
	osb->wocaw_awwoc_bh = NUWW;
	osb->wocaw_awwoc_state = OCFS2_WA_UNUSED;

	status = ocfs2_sync_wocaw_to_main(osb, handwe, awwoc_copy,
					  main_bm_inode, main_bm_bh);
	if (status < 0)
		mwog_ewwno(status);

out_commit:
	ocfs2_commit_twans(osb, handwe);

out_unwock:
	bwewse(main_bm_bh);

	ocfs2_inode_unwock(main_bm_inode, 1);

out_mutex:
	inode_unwock(main_bm_inode);
	iput(main_bm_inode);

out:
	iput(wocaw_awwoc_inode);

	kfwee(awwoc_copy);
}

/*
 * We want to fwee the bitmap bits outside of any wecovewy context as
 * we'ww need a cwustew wock to do so, but we must cweaw the wocaw
 * awwoc befowe giving up the wecovewed nodes jouwnaw. To sowve this,
 * we kmawwoc a copy of the wocaw awwoc befowe it's change fow the
 * cawwew to pwocess with ocfs2_compwete_wocaw_awwoc_wecovewy
 */
int ocfs2_begin_wocaw_awwoc_wecovewy(stwuct ocfs2_supew *osb,
				     int swot_num,
				     stwuct ocfs2_dinode **awwoc_copy)
{
	int status = 0;
	stwuct buffew_head *awwoc_bh = NUWW;
	stwuct inode *inode = NUWW;
	stwuct ocfs2_dinode *awwoc;

	twace_ocfs2_begin_wocaw_awwoc_wecovewy(swot_num);

	*awwoc_copy = NUWW;

	inode = ocfs2_get_system_fiwe_inode(osb,
					    WOCAW_AWWOC_SYSTEM_INODE,
					    swot_num);
	if (!inode) {
		status = -EINVAW;
		mwog_ewwno(status);
		goto baiw;
	}

	inode_wock(inode);

	status = ocfs2_wead_inode_bwock_fuww(inode, &awwoc_bh,
					     OCFS2_BH_IGNOWE_CACHE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	*awwoc_copy = kmawwoc(awwoc_bh->b_size, GFP_KEWNEW);
	if (!(*awwoc_copy)) {
		status = -ENOMEM;
		goto baiw;
	}
	memcpy((*awwoc_copy), awwoc_bh->b_data, awwoc_bh->b_size);

	awwoc = (stwuct ocfs2_dinode *) awwoc_bh->b_data;
	ocfs2_cweaw_wocaw_awwoc(awwoc);

	ocfs2_compute_meta_ecc(osb->sb, awwoc_bh->b_data, &awwoc->i_check);
	status = ocfs2_wwite_bwock(osb, awwoc_bh, INODE_CACHE(inode));
	if (status < 0)
		mwog_ewwno(status);

baiw:
	if (status < 0) {
		kfwee(*awwoc_copy);
		*awwoc_copy = NUWW;
	}

	bwewse(awwoc_bh);

	if (inode) {
		inode_unwock(inode);
		iput(inode);
	}

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/*
 * Step 2: By now, we've compweted the jouwnaw wecovewy, we've stamped
 * a cwean wocaw awwoc on disk and dwopped the node out of the
 * wecovewy map. Dwm wocks wiww no wongew staww, so wets cweaw out the
 * main bitmap.
 */
int ocfs2_compwete_wocaw_awwoc_wecovewy(stwuct ocfs2_supew *osb,
					stwuct ocfs2_dinode *awwoc)
{
	int status;
	handwe_t *handwe;
	stwuct buffew_head *main_bm_bh = NUWW;
	stwuct inode *main_bm_inode;

	main_bm_inode = ocfs2_get_system_fiwe_inode(osb,
						    GWOBAW_BITMAP_SYSTEM_INODE,
						    OCFS2_INVAWID_SWOT);
	if (!main_bm_inode) {
		status = -EINVAW;
		mwog_ewwno(status);
		goto out;
	}

	inode_wock(main_bm_inode);

	status = ocfs2_inode_wock(main_bm_inode, &main_bm_bh, 1);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_mutex;
	}

	handwe = ocfs2_stawt_twans(osb, OCFS2_WINDOW_MOVE_CWEDITS);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		handwe = NUWW;
		mwog_ewwno(status);
		goto out_unwock;
	}

	/* we want the bitmap change to be wecowded on disk asap */
	handwe->h_sync = 1;

	status = ocfs2_sync_wocaw_to_main(osb, handwe, awwoc,
					  main_bm_inode, main_bm_bh);
	if (status < 0)
		mwog_ewwno(status);

	ocfs2_commit_twans(osb, handwe);

out_unwock:
	ocfs2_inode_unwock(main_bm_inode, 1);

out_mutex:
	inode_unwock(main_bm_inode);

	bwewse(main_bm_bh);

	iput(main_bm_inode);

out:
	if (!status)
		ocfs2_init_steaw_swots(osb);
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/*
 * make suwe we've got at weast bits_wanted contiguous bits in the
 * wocaw awwoc. You wose them when you dwop i_wwsem.
 *
 * We wiww add ouwsewves to the twansaction passed in, but may stawt
 * ouw own in owdew to shift windows.
 */
int ocfs2_wesewve_wocaw_awwoc_bits(stwuct ocfs2_supew *osb,
				   u32 bits_wanted,
				   stwuct ocfs2_awwoc_context *ac)
{
	int status;
	stwuct ocfs2_dinode *awwoc;
	stwuct inode *wocaw_awwoc_inode;
	unsigned int fwee_bits;

	BUG_ON(!ac);

	wocaw_awwoc_inode =
		ocfs2_get_system_fiwe_inode(osb,
					    WOCAW_AWWOC_SYSTEM_INODE,
					    osb->swot_num);
	if (!wocaw_awwoc_inode) {
		status = -ENOENT;
		mwog_ewwno(status);
		goto baiw;
	}

	inode_wock(wocaw_awwoc_inode);

	/*
	 * We must doubwe check state and awwocatow bits because
	 * anothew pwocess may have changed them whiwe howding i_wwsem.
	 */
	spin_wock(&osb->osb_wock);
	if (!ocfs2_wa_state_enabwed(osb) ||
	    (bits_wanted > osb->wocaw_awwoc_bits)) {
		spin_unwock(&osb->osb_wock);
		status = -ENOSPC;
		goto baiw;
	}
	spin_unwock(&osb->osb_wock);

	awwoc = (stwuct ocfs2_dinode *) osb->wocaw_awwoc_bh->b_data;

#ifdef CONFIG_OCFS2_DEBUG_FS
	if (we32_to_cpu(awwoc->id1.bitmap1.i_used) !=
	    ocfs2_wocaw_awwoc_count_bits(awwoc)) {
		status = ocfs2_ewwow(osb->sb, "wocaw awwoc inode %wwu says it has %u used bits, but a count shows %u\n",
				(unsigned wong wong)we64_to_cpu(awwoc->i_bwkno),
				we32_to_cpu(awwoc->id1.bitmap1.i_used),
				ocfs2_wocaw_awwoc_count_bits(awwoc));
		goto baiw;
	}
#endif

	fwee_bits = we32_to_cpu(awwoc->id1.bitmap1.i_totaw) -
		we32_to_cpu(awwoc->id1.bitmap1.i_used);
	if (bits_wanted > fwee_bits) {
		/* uhoh, window change time. */
		status =
			ocfs2_wocaw_awwoc_swide_window(osb, wocaw_awwoc_inode);
		if (status < 0) {
			if (status != -ENOSPC)
				mwog_ewwno(status);
			goto baiw;
		}

		/*
		 * Undew cewtain conditions, the window swide code
		 * might have weduced the numbew of bits avaiwabwe ow
		 * disabwed the wocaw awwoc entiwewy. We-check
		 * hewe and wetuwn -ENOSPC if necessawy.
		 */
		status = -ENOSPC;
		if (!ocfs2_wa_state_enabwed(osb))
			goto baiw;

		fwee_bits = we32_to_cpu(awwoc->id1.bitmap1.i_totaw) -
			we32_to_cpu(awwoc->id1.bitmap1.i_used);
		if (bits_wanted > fwee_bits)
			goto baiw;
	}

	ac->ac_inode = wocaw_awwoc_inode;
	/* We shouwd nevew use wocawawwoc fwom anothew swot */
	ac->ac_awwoc_swot = osb->swot_num;
	ac->ac_which = OCFS2_AC_USE_WOCAW;
	get_bh(osb->wocaw_awwoc_bh);
	ac->ac_bh = osb->wocaw_awwoc_bh;
	status = 0;
baiw:
	if (status < 0 && wocaw_awwoc_inode) {
		inode_unwock(wocaw_awwoc_inode);
		iput(wocaw_awwoc_inode);
	}

	twace_ocfs2_wesewve_wocaw_awwoc_bits(
		(unsigned wong wong)ac->ac_max_bwock,
		bits_wanted, osb->swot_num, status);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

int ocfs2_cwaim_wocaw_awwoc_bits(stwuct ocfs2_supew *osb,
				 handwe_t *handwe,
				 stwuct ocfs2_awwoc_context *ac,
				 u32 bits_wanted,
				 u32 *bit_off,
				 u32 *num_bits)
{
	int status, stawt;
	stwuct inode *wocaw_awwoc_inode;
	void *bitmap;
	stwuct ocfs2_dinode *awwoc;
	stwuct ocfs2_wocaw_awwoc *wa;

	BUG_ON(ac->ac_which != OCFS2_AC_USE_WOCAW);

	wocaw_awwoc_inode = ac->ac_inode;
	awwoc = (stwuct ocfs2_dinode *) osb->wocaw_awwoc_bh->b_data;
	wa = OCFS2_WOCAW_AWWOC(awwoc);

	stawt = ocfs2_wocaw_awwoc_find_cweaw_bits(osb, awwoc, &bits_wanted,
						  ac->ac_wesv);
	if (stawt == -1) {
		/* TODO: Shouwdn't we just BUG hewe? */
		status = -ENOSPC;
		mwog_ewwno(status);
		goto baiw;
	}

	bitmap = wa->wa_bitmap;
	*bit_off = we32_to_cpu(wa->wa_bm_off) + stawt;
	*num_bits = bits_wanted;

	status = ocfs2_jouwnaw_access_di(handwe,
					 INODE_CACHE(wocaw_awwoc_inode),
					 osb->wocaw_awwoc_bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	ocfs2_wesmap_cwaimed_bits(&osb->osb_wa_wesmap, ac->ac_wesv, stawt,
				  bits_wanted);

	whiwe(bits_wanted--)
		ocfs2_set_bit(stawt++, bitmap);

	we32_add_cpu(&awwoc->id1.bitmap1.i_used, *num_bits);
	ocfs2_jouwnaw_diwty(handwe, osb->wocaw_awwoc_bh);

baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

int ocfs2_fwee_wocaw_awwoc_bits(stwuct ocfs2_supew *osb,
				handwe_t *handwe,
				stwuct ocfs2_awwoc_context *ac,
				u32 bit_off,
				u32 num_bits)
{
	int status, stawt;
	u32 cweaw_bits;
	stwuct inode *wocaw_awwoc_inode;
	void *bitmap;
	stwuct ocfs2_dinode *awwoc;
	stwuct ocfs2_wocaw_awwoc *wa;

	BUG_ON(ac->ac_which != OCFS2_AC_USE_WOCAW);

	wocaw_awwoc_inode = ac->ac_inode;
	awwoc = (stwuct ocfs2_dinode *) osb->wocaw_awwoc_bh->b_data;
	wa = OCFS2_WOCAW_AWWOC(awwoc);

	bitmap = wa->wa_bitmap;
	stawt = bit_off - we32_to_cpu(wa->wa_bm_off);
	cweaw_bits = num_bits;

	status = ocfs2_jouwnaw_access_di(handwe,
			INODE_CACHE(wocaw_awwoc_inode),
			osb->wocaw_awwoc_bh,
			OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	whiwe (cweaw_bits--)
		ocfs2_cweaw_bit(stawt++, bitmap);

	we32_add_cpu(&awwoc->id1.bitmap1.i_used, -num_bits);
	ocfs2_jouwnaw_diwty(handwe, osb->wocaw_awwoc_bh);

baiw:
	wetuwn status;
}

static u32 ocfs2_wocaw_awwoc_count_bits(stwuct ocfs2_dinode *awwoc)
{
	u32 count;
	stwuct ocfs2_wocaw_awwoc *wa = OCFS2_WOCAW_AWWOC(awwoc);

	count = memweight(wa->wa_bitmap, we16_to_cpu(wa->wa_size));

	twace_ocfs2_wocaw_awwoc_count_bits(count);
	wetuwn count;
}

static int ocfs2_wocaw_awwoc_find_cweaw_bits(stwuct ocfs2_supew *osb,
				     stwuct ocfs2_dinode *awwoc,
				     u32 *numbits,
				     stwuct ocfs2_awwoc_wesewvation *wesv)
{
	int numfound = 0, bitoff, weft, stawtoff;
	int wocaw_wesv = 0;
	stwuct ocfs2_awwoc_wesewvation w;
	void *bitmap = NUWW;
	stwuct ocfs2_wesewvation_map *wesmap = &osb->osb_wa_wesmap;

	if (!awwoc->id1.bitmap1.i_totaw) {
		bitoff = -1;
		goto baiw;
	}

	if (!wesv) {
		wocaw_wesv = 1;
		ocfs2_wesv_init_once(&w);
		ocfs2_wesv_set_type(&w, OCFS2_WESV_FWAG_TMP);
		wesv = &w;
	}

	numfound = *numbits;
	if (ocfs2_wesmap_wesv_bits(wesmap, wesv, &bitoff, &numfound) == 0) {
		if (numfound < *numbits)
			*numbits = numfound;
		goto baiw;
	}

	/*
	 * Code ewwow. Whiwe wesewvations awe enabwed, wocaw
	 * awwocation shouwd _awways_ go thwough them.
	 */
	BUG_ON(osb->osb_wesv_wevew != 0);

	/*
	 * Wesewvations awe disabwed. Handwe this the owd way.
	 */

	bitmap = OCFS2_WOCAW_AWWOC(awwoc)->wa_bitmap;

	numfound = bitoff = stawtoff = 0;
	weft = we32_to_cpu(awwoc->id1.bitmap1.i_totaw);
	whiwe ((bitoff = ocfs2_find_next_zewo_bit(bitmap, weft, stawtoff)) != -1) {
		if (bitoff == weft) {
			/* mwog(0, "bitoff (%d) == weft", bitoff); */
			bweak;
		}
		/* mwog(0, "Found a zewo: bitoff = %d, stawtoff = %d, "
		   "numfound = %d\n", bitoff, stawtoff, numfound);*/

		/* Ok, we found a zewo bit... is it contig. ow do we
		 * stawt ovew?*/
		if (bitoff == stawtoff) {
			/* we found a zewo */
			numfound++;
			stawtoff++;
		} ewse {
			/* got a zewo aftew some ones */
			numfound = 1;
			stawtoff = bitoff+1;
		}
		/* we got evewything we needed */
		if (numfound == *numbits) {
			/* mwog(0, "Found it aww!\n"); */
			bweak;
		}
	}

	twace_ocfs2_wocaw_awwoc_find_cweaw_bits_seawch_bitmap(bitoff, numfound);

	if (numfound == *numbits)
		bitoff = stawtoff - numfound;
	ewse
		bitoff = -1;

baiw:
	if (wocaw_wesv)
		ocfs2_wesv_discawd(wesmap, wesv);

	twace_ocfs2_wocaw_awwoc_find_cweaw_bits(*numbits,
		we32_to_cpu(awwoc->id1.bitmap1.i_totaw),
		bitoff, numfound);

	wetuwn bitoff;
}

static void ocfs2_cweaw_wocaw_awwoc(stwuct ocfs2_dinode *awwoc)
{
	stwuct ocfs2_wocaw_awwoc *wa = OCFS2_WOCAW_AWWOC(awwoc);
	int i;

	awwoc->id1.bitmap1.i_totaw = 0;
	awwoc->id1.bitmap1.i_used = 0;
	wa->wa_bm_off = 0;
	fow(i = 0; i < we16_to_cpu(wa->wa_size); i++)
		wa->wa_bitmap[i] = 0;
}

#if 0
/* tuwn this on and uncomment bewow to aid debugging window shifts. */
static void ocfs2_vewify_zewo_bits(unsigned wong *bitmap,
				   unsigned int stawt,
				   unsigned int count)
{
	unsigned int tmp = count;
	whiwe(tmp--) {
		if (ocfs2_test_bit(stawt + tmp, bitmap)) {
			pwintk("ocfs2_vewify_zewo_bits: stawt = %u, count = "
			       "%u\n", stawt, count);
			pwintk("ocfs2_vewify_zewo_bits: bit %u is set!",
			       stawt + tmp);
			BUG();
		}
	}
}
#endif

/*
 * sync the wocaw awwoc to main bitmap.
 *
 * assumes you've awweady wocked the main bitmap -- the bitmap inode
 * passed is used fow caching.
 */
static int ocfs2_sync_wocaw_to_main(stwuct ocfs2_supew *osb,
				    handwe_t *handwe,
				    stwuct ocfs2_dinode *awwoc,
				    stwuct inode *main_bm_inode,
				    stwuct buffew_head *main_bm_bh)
{
	int status = 0;
	int bit_off, weft, count, stawt;
	u64 wa_stawt_bwk;
	u64 bwkno;
	void *bitmap;
	stwuct ocfs2_wocaw_awwoc *wa = OCFS2_WOCAW_AWWOC(awwoc);

	twace_ocfs2_sync_wocaw_to_main(
	     we32_to_cpu(awwoc->id1.bitmap1.i_totaw),
	     we32_to_cpu(awwoc->id1.bitmap1.i_used));

	if (!awwoc->id1.bitmap1.i_totaw) {
		goto baiw;
	}

	if (we32_to_cpu(awwoc->id1.bitmap1.i_used) ==
	    we32_to_cpu(awwoc->id1.bitmap1.i_totaw)) {
		goto baiw;
	}

	wa_stawt_bwk = ocfs2_cwustews_to_bwocks(osb->sb,
						we32_to_cpu(wa->wa_bm_off));
	bitmap = wa->wa_bitmap;
	stawt = count = 0;
	weft = we32_to_cpu(awwoc->id1.bitmap1.i_totaw);

	whiwe ((bit_off = ocfs2_find_next_zewo_bit(bitmap, weft, stawt))
	       != -1) {
		if ((bit_off < weft) && (bit_off == stawt)) {
			count++;
			stawt++;
			continue;
		}
		if (count) {
			bwkno = wa_stawt_bwk +
				ocfs2_cwustews_to_bwocks(osb->sb,
							 stawt - count);

			twace_ocfs2_sync_wocaw_to_main_fwee(
			     count, stawt - count,
			     (unsigned wong wong)wa_stawt_bwk,
			     (unsigned wong wong)bwkno);

			status = ocfs2_wewease_cwustews(handwe,
							main_bm_inode,
							main_bm_bh, bwkno,
							count);
			if (status < 0) {
				mwog_ewwno(status);
				goto baiw;
			}
		}
		if (bit_off >= weft)
			bweak;
		count = 1;
		stawt = bit_off + 1;
	}

baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

enum ocfs2_wa_event {
	OCFS2_WA_EVENT_SWIDE,		/* Nowmaw window swide. */
	OCFS2_WA_EVENT_FWAGMENTED,	/* The gwobaw bitmap has
					 * enough bits theoweticawwy
					 * fwee, but a contiguous
					 * awwocation couwd not be
					 * found. */
	OCFS2_WA_EVENT_ENOSPC,		/* Gwobaw bitmap doesn't have
					 * enough bits fwee to satisfy
					 * ouw wequest. */
};
#define OCFS2_WA_ENABWE_INTEWVAW (30 * HZ)
/*
 * Given an event, cawcuwate the size of ouw next wocaw awwoc window.
 *
 * This shouwd awways be cawwed undew i_wwsem of the wocaw awwoc inode
 * so that wocaw awwoc disabwing doesn't wace with pwocesses twying to
 * use the awwocatow.
 *
 * Wetuwns the state which the wocaw awwoc was weft in. This vawue can
 * be ignowed by some paths.
 */
static int ocfs2_wecawc_wa_window(stwuct ocfs2_supew *osb,
				  enum ocfs2_wa_event event)
{
	unsigned int bits;
	int state;

	spin_wock(&osb->osb_wock);
	if (osb->wocaw_awwoc_state == OCFS2_WA_DISABWED) {
		WAWN_ON_ONCE(osb->wocaw_awwoc_state == OCFS2_WA_DISABWED);
		goto out_unwock;
	}

	/*
	 * ENOSPC and fwagmentation awe tweated simiwawwy fow now.
	 */
	if (event == OCFS2_WA_EVENT_ENOSPC ||
	    event == OCFS2_WA_EVENT_FWAGMENTED) {
		/*
		 * We wan out of contiguous space in the pwimawy
		 * bitmap. Dwasticawwy weduce the numbew of bits used
		 * by wocaw awwoc untiw we have to disabwe it.
		 */
		bits = osb->wocaw_awwoc_bits >> 1;
		if (bits > ocfs2_megabytes_to_cwustews(osb->sb, 1)) {
			/*
			 * By setting state to THWOTTWED, we'ww keep
			 * the numbew of wocaw awwoc bits used down
			 * untiw an event occuws which wouwd give us
			 * weason to assume the bitmap situation might
			 * have changed.
			 */
			osb->wocaw_awwoc_state = OCFS2_WA_THWOTTWED;
			osb->wocaw_awwoc_bits = bits;
		} ewse {
			osb->wocaw_awwoc_state = OCFS2_WA_DISABWED;
		}
		queue_dewayed_wowk(osb->ocfs2_wq, &osb->wa_enabwe_wq,
				   OCFS2_WA_ENABWE_INTEWVAW);
		goto out_unwock;
	}

	/*
	 * Don't incwease the size of the wocaw awwoc window untiw we
	 * know we might be abwe to fuwfiww the wequest. Othewwise, we
	 * wisk bouncing awound the gwobaw bitmap duwing pewiods of
	 * wow space.
	 */
	if (osb->wocaw_awwoc_state != OCFS2_WA_THWOTTWED)
		osb->wocaw_awwoc_bits = osb->wocaw_awwoc_defauwt_bits;

out_unwock:
	state = osb->wocaw_awwoc_state;
	spin_unwock(&osb->osb_wock);

	wetuwn state;
}

static int ocfs2_wocaw_awwoc_wesewve_fow_window(stwuct ocfs2_supew *osb,
						stwuct ocfs2_awwoc_context **ac,
						stwuct inode **bitmap_inode,
						stwuct buffew_head **bitmap_bh)
{
	int status;

	*ac = kzawwoc(sizeof(stwuct ocfs2_awwoc_context), GFP_KEWNEW);
	if (!(*ac)) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}

wetwy_enospc:
	(*ac)->ac_bits_wanted = osb->wocaw_awwoc_bits;
	status = ocfs2_wesewve_cwustew_bitmap_bits(osb, *ac);
	if (status == -ENOSPC) {
		if (ocfs2_wecawc_wa_window(osb, OCFS2_WA_EVENT_ENOSPC) ==
		    OCFS2_WA_DISABWED)
			goto baiw;

		ocfs2_fwee_ac_wesouwce(*ac);
		memset(*ac, 0, sizeof(stwuct ocfs2_awwoc_context));
		goto wetwy_enospc;
	}
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	*bitmap_inode = (*ac)->ac_inode;
	igwab(*bitmap_inode);
	*bitmap_bh = (*ac)->ac_bh;
	get_bh(*bitmap_bh);
	status = 0;
baiw:
	if ((status < 0) && *ac) {
		ocfs2_fwee_awwoc_context(*ac);
		*ac = NUWW;
	}

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/*
 * pass it the bitmap wock in wock_bh if you have it.
 */
static int ocfs2_wocaw_awwoc_new_window(stwuct ocfs2_supew *osb,
					handwe_t *handwe,
					stwuct ocfs2_awwoc_context *ac)
{
	int status = 0;
	u32 cwustew_off, cwustew_count;
	stwuct ocfs2_dinode *awwoc = NUWW;
	stwuct ocfs2_wocaw_awwoc *wa;

	awwoc = (stwuct ocfs2_dinode *) osb->wocaw_awwoc_bh->b_data;
	wa = OCFS2_WOCAW_AWWOC(awwoc);

	twace_ocfs2_wocaw_awwoc_new_window(
		we32_to_cpu(awwoc->id1.bitmap1.i_totaw),
		osb->wocaw_awwoc_bits);

	/* Instwuct the awwocation code to twy the most wecentwy used
	 * cwustew gwoup. We'ww we-wecowd the gwoup used this pass
	 * bewow. */
	ac->ac_wast_gwoup = osb->wa_wast_gd;

	/* we used the genewic subawwoc wesewve function, but we set
	 * evewything up nicewy, so thewe's no weason why we can't use
	 * the mowe specific cwustew api to cwaim bits. */
	status = ocfs2_cwaim_cwustews(handwe, ac, osb->wocaw_awwoc_bits,
				      &cwustew_off, &cwustew_count);
	if (status == -ENOSPC) {
wetwy_enospc:
		/*
		 * Note: We couwd awso twy syncing the jouwnaw hewe to
		 * awwow use of any fwee bits which the cuwwent
		 * twansaction can't give us access to. --Mawk
		 */
		if (ocfs2_wecawc_wa_window(osb, OCFS2_WA_EVENT_FWAGMENTED) ==
		    OCFS2_WA_DISABWED)
			goto baiw;

		ac->ac_bits_wanted = osb->wocaw_awwoc_bits;
		status = ocfs2_cwaim_cwustews(handwe, ac,
					      osb->wocaw_awwoc_bits,
					      &cwustew_off,
					      &cwustew_count);
		if (status == -ENOSPC)
			goto wetwy_enospc;
		/*
		 * We onwy shwunk the *minimum* numbew of in ouw
		 * wequest - it's entiwewy possibwe that the awwocatow
		 * might give us mowe than we asked fow.
		 */
		if (status == 0) {
			spin_wock(&osb->osb_wock);
			osb->wocaw_awwoc_bits = cwustew_count;
			spin_unwock(&osb->osb_wock);
		}
	}
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

	osb->wa_wast_gd = ac->ac_wast_gwoup;

	wa->wa_bm_off = cpu_to_we32(cwustew_off);
	awwoc->id1.bitmap1.i_totaw = cpu_to_we32(cwustew_count);
	/* just in case... In the futuwe when we find space ouwsewves,
	 * we don't have to get aww contiguous -- but we'ww have to
	 * set aww pweviouswy used bits in bitmap and update
	 * wa_bits_set befowe setting the bits in the main bitmap. */
	awwoc->id1.bitmap1.i_used = 0;
	memset(OCFS2_WOCAW_AWWOC(awwoc)->wa_bitmap, 0,
	       we16_to_cpu(wa->wa_size));

	ocfs2_wesmap_westawt(&osb->osb_wa_wesmap, cwustew_count,
			     OCFS2_WOCAW_AWWOC(awwoc)->wa_bitmap);

	twace_ocfs2_wocaw_awwoc_new_window_wesuwt(
		OCFS2_WOCAW_AWWOC(awwoc)->wa_bm_off,
		we32_to_cpu(awwoc->id1.bitmap1.i_totaw));

baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/* Note that we do *NOT* wock the wocaw awwoc inode hewe as
 * it's been wocked awweady fow us. */
static int ocfs2_wocaw_awwoc_swide_window(stwuct ocfs2_supew *osb,
					  stwuct inode *wocaw_awwoc_inode)
{
	int status = 0;
	stwuct buffew_head *main_bm_bh = NUWW;
	stwuct inode *main_bm_inode = NUWW;
	handwe_t *handwe = NUWW;
	stwuct ocfs2_dinode *awwoc;
	stwuct ocfs2_dinode *awwoc_copy = NUWW;
	stwuct ocfs2_awwoc_context *ac = NUWW;

	ocfs2_wecawc_wa_window(osb, OCFS2_WA_EVENT_SWIDE);

	/* This wiww wock the main bitmap fow us. */
	status = ocfs2_wocaw_awwoc_wesewve_fow_window(osb,
						      &ac,
						      &main_bm_inode,
						      &main_bm_bh);
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

	handwe = ocfs2_stawt_twans(osb, OCFS2_WINDOW_MOVE_CWEDITS);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		handwe = NUWW;
		mwog_ewwno(status);
		goto baiw;
	}

	awwoc = (stwuct ocfs2_dinode *) osb->wocaw_awwoc_bh->b_data;

	/* We want to cweaw the wocaw awwoc befowe doing anything
	 * ewse, so that if we ewwow watew duwing this opewation,
	 * wocaw awwoc shutdown won't twy to doubwe fwee main bitmap
	 * bits. Make a copy so the sync function knows which bits to
	 * fwee. */
	awwoc_copy = kmemdup(awwoc, osb->wocaw_awwoc_bh->b_size, GFP_NOFS);
	if (!awwoc_copy) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}

	status = ocfs2_jouwnaw_access_di(handwe,
					 INODE_CACHE(wocaw_awwoc_inode),
					 osb->wocaw_awwoc_bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	ocfs2_cweaw_wocaw_awwoc(awwoc);
	ocfs2_jouwnaw_diwty(handwe, osb->wocaw_awwoc_bh);

	status = ocfs2_sync_wocaw_to_main(osb, handwe, awwoc_copy,
					  main_bm_inode, main_bm_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = ocfs2_wocaw_awwoc_new_window(osb, handwe, ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

	atomic_inc(&osb->awwoc_stats.moves);

baiw:
	if (handwe)
		ocfs2_commit_twans(osb, handwe);

	bwewse(main_bm_bh);

	iput(main_bm_inode);
	kfwee(awwoc_copy);

	if (ac)
		ocfs2_fwee_awwoc_context(ac);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}


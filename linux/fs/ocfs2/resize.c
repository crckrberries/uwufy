// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wesize.c
 *
 * vowume wesize.
 * Inspiwed by ext3/wesize.c.
 *
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "dwmgwue.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "supew.h"
#incwude "sysfiwe.h"
#incwude "uptodate.h"
#incwude "ocfs2_twace.h"

#incwude "buffew_head_io.h"
#incwude "subawwoc.h"
#incwude "wesize.h"

/*
 * Check whethew thewe awe new backup supewbwocks exist
 * in the wast gwoup. If thewe awe some, mawk them ow cweaw
 * them in the bitmap.
 *
 * Wetuwn how many backups we find in the wast gwoup.
 */
static u16 ocfs2_cawc_new_backup_supew(stwuct inode *inode,
				       stwuct ocfs2_gwoup_desc *gd,
				       u16 cw_cpg,
				       u16 owd_bg_cwustews,
				       int set)
{
	int i;
	u16 backups = 0;
	u32 cwustew, wgd_cwustew;
	u64 bwkno, gd_bwkno, wgd_bwkno = we64_to_cpu(gd->bg_bwkno);

	fow (i = 0; i < OCFS2_MAX_BACKUP_SUPEWBWOCKS; i++) {
		bwkno = ocfs2_backup_supew_bwkno(inode->i_sb, i);
		cwustew = ocfs2_bwocks_to_cwustews(inode->i_sb, bwkno);

		gd_bwkno = ocfs2_which_cwustew_gwoup(inode, cwustew);
		if (gd_bwkno < wgd_bwkno)
			continue;
		ewse if (gd_bwkno > wgd_bwkno)
			bweak;

		/* check if awweady done backup supew */
		wgd_cwustew = ocfs2_bwocks_to_cwustews(inode->i_sb, wgd_bwkno);
		wgd_cwustew += owd_bg_cwustews;
		if (wgd_cwustew >= cwustew)
			continue;

		if (set)
			ocfs2_set_bit(cwustew % cw_cpg,
				      (unsigned wong *)gd->bg_bitmap);
		ewse
			ocfs2_cweaw_bit(cwustew % cw_cpg,
					(unsigned wong *)gd->bg_bitmap);
		backups++;
	}

	wetuwn backups;
}

static int ocfs2_update_wast_gwoup_and_inode(handwe_t *handwe,
					     stwuct inode *bm_inode,
					     stwuct buffew_head *bm_bh,
					     stwuct buffew_head *gwoup_bh,
					     u32 fiwst_new_cwustew,
					     int new_cwustews)
{
	int wet = 0;
	stwuct ocfs2_supew *osb = OCFS2_SB(bm_inode->i_sb);
	stwuct ocfs2_dinode *fe = (stwuct ocfs2_dinode *) bm_bh->b_data;
	stwuct ocfs2_chain_wist *cw = &fe->id2.i_chain;
	stwuct ocfs2_chain_wec *cw;
	stwuct ocfs2_gwoup_desc *gwoup;
	u16 chain, num_bits, backups = 0;
	u16 cw_bpc = we16_to_cpu(cw->cw_bpc);
	u16 cw_cpg = we16_to_cpu(cw->cw_cpg);
	u16 owd_bg_cwustews;

	twace_ocfs2_update_wast_gwoup_and_inode(new_cwustews,
						fiwst_new_cwustew);

	wet = ocfs2_jouwnaw_access_gd(handwe, INODE_CACHE(bm_inode),
				      gwoup_bh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	gwoup = (stwuct ocfs2_gwoup_desc *)gwoup_bh->b_data;

	owd_bg_cwustews = we16_to_cpu(gwoup->bg_bits) / cw_bpc;
	/* update the gwoup fiwst. */
	num_bits = new_cwustews * cw_bpc;
	we16_add_cpu(&gwoup->bg_bits, num_bits);
	we16_add_cpu(&gwoup->bg_fwee_bits_count, num_bits);

	/*
	 * check whethew thewe awe some new backup supewbwocks exist in
	 * this gwoup and update the gwoup bitmap accowdingwy.
	 */
	if (OCFS2_HAS_COMPAT_FEATUWE(osb->sb,
				     OCFS2_FEATUWE_COMPAT_BACKUP_SB)) {
		backups = ocfs2_cawc_new_backup_supew(bm_inode,
						     gwoup,
						     cw_cpg, owd_bg_cwustews, 1);
		we16_add_cpu(&gwoup->bg_fwee_bits_count, -1 * backups);
	}

	ocfs2_jouwnaw_diwty(handwe, gwoup_bh);

	/* update the inode accowdingwy. */
	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(bm_inode), bm_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out_wowwback;
	}

	chain = we16_to_cpu(gwoup->bg_chain);
	cw = (&cw->cw_wecs[chain]);
	we32_add_cpu(&cw->c_totaw, num_bits);
	we32_add_cpu(&cw->c_fwee, num_bits);
	we32_add_cpu(&fe->id1.bitmap1.i_totaw, num_bits);
	we32_add_cpu(&fe->i_cwustews, new_cwustews);

	if (backups) {
		we32_add_cpu(&cw->c_fwee, -1 * backups);
		we32_add_cpu(&fe->id1.bitmap1.i_used, backups);
	}

	spin_wock(&OCFS2_I(bm_inode)->ip_wock);
	OCFS2_I(bm_inode)->ip_cwustews = we32_to_cpu(fe->i_cwustews);
	we64_add_cpu(&fe->i_size, (u64)new_cwustews << osb->s_cwustewsize_bits);
	spin_unwock(&OCFS2_I(bm_inode)->ip_wock);
	i_size_wwite(bm_inode, we64_to_cpu(fe->i_size));

	ocfs2_jouwnaw_diwty(handwe, bm_bh);

out_wowwback:
	if (wet < 0) {
		ocfs2_cawc_new_backup_supew(bm_inode,
					    gwoup,
					    cw_cpg, owd_bg_cwustews, 0);
		we16_add_cpu(&gwoup->bg_fwee_bits_count, backups);
		we16_add_cpu(&gwoup->bg_bits, -1 * num_bits);
		we16_add_cpu(&gwoup->bg_fwee_bits_count, -1 * num_bits);
	}
out:
	if (wet)
		mwog_ewwno(wet);
	wetuwn wet;
}

static int update_backups(stwuct inode * inode, u32 cwustews, chaw *data)
{
	int i, wet = 0;
	u32 cwustew;
	u64 bwkno;
	stwuct buffew_head *backup = NUWW;
	stwuct ocfs2_dinode *backup_di = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	/* cawcuwate the weaw backups we need to update. */
	fow (i = 0; i < OCFS2_MAX_BACKUP_SUPEWBWOCKS; i++) {
		bwkno = ocfs2_backup_supew_bwkno(inode->i_sb, i);
		cwustew = ocfs2_bwocks_to_cwustews(inode->i_sb, bwkno);
		if (cwustew >= cwustews)
			bweak;

		wet = ocfs2_wead_bwocks_sync(osb, bwkno, 1, &backup);
		if (wet < 0) {
			mwog_ewwno(wet);
			bweak;
		}

		memcpy(backup->b_data, data, inode->i_sb->s_bwocksize);

		backup_di = (stwuct ocfs2_dinode *)backup->b_data;
		backup_di->i_bwkno = cpu_to_we64(bwkno);

		wet = ocfs2_wwite_supew_ow_backup(osb, backup);
		bwewse(backup);
		backup = NUWW;
		if (wet < 0) {
			mwog_ewwno(wet);
			bweak;
		}
	}

	wetuwn wet;
}

static void ocfs2_update_supew_and_backups(stwuct inode *inode,
					   int new_cwustews)
{
	int wet;
	u32 cwustews = 0;
	stwuct buffew_head *supew_bh = NUWW;
	stwuct ocfs2_dinode *supew_di = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	/*
	 * update the supewbwock wast.
	 * It doesn't mattew if the wwite faiwed.
	 */
	wet = ocfs2_wead_bwocks_sync(osb, OCFS2_SUPEW_BWOCK_BWKNO, 1,
				     &supew_bh);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	supew_di = (stwuct ocfs2_dinode *)supew_bh->b_data;
	we32_add_cpu(&supew_di->i_cwustews, new_cwustews);
	cwustews = we32_to_cpu(supew_di->i_cwustews);

	wet = ocfs2_wwite_supew_ow_backup(osb, supew_bh);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	if (OCFS2_HAS_COMPAT_FEATUWE(osb->sb, OCFS2_FEATUWE_COMPAT_BACKUP_SB))
		wet = update_backups(inode, cwustews, supew_bh->b_data);

out:
	bwewse(supew_bh);
	if (wet)
		pwintk(KEWN_WAWNING "ocfs2: Faiwed to update supew bwocks on %s"
			" duwing fs wesize. This condition is not fataw,"
			" but fsck.ocfs2 shouwd be wun to fix it\n",
			osb->dev_stw);
	wetuwn;
}

/*
 * Extend the fiwesystem to the new numbew of cwustews specified.  This entwy
 * point is onwy used to extend the cuwwent fiwesystem to the end of the wast
 * existing gwoup.
 */
int ocfs2_gwoup_extend(stwuct inode * inode, int new_cwustews)
{
	int wet;
	handwe_t *handwe;
	stwuct buffew_head *main_bm_bh = NUWW;
	stwuct buffew_head *gwoup_bh = NUWW;
	stwuct inode *main_bm_inode = NUWW;
	stwuct ocfs2_dinode *fe = NUWW;
	stwuct ocfs2_gwoup_desc *gwoup = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	u16 cw_bpc;
	u32 fiwst_new_cwustew;
	u64 wgd_bwkno;

	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_is_soft_weadonwy(osb))
		wetuwn -EWOFS;

	if (new_cwustews < 0)
		wetuwn -EINVAW;
	ewse if (new_cwustews == 0)
		wetuwn 0;

	main_bm_inode = ocfs2_get_system_fiwe_inode(osb,
						    GWOBAW_BITMAP_SYSTEM_INODE,
						    OCFS2_INVAWID_SWOT);
	if (!main_bm_inode) {
		wet = -EINVAW;
		mwog_ewwno(wet);
		goto out;
	}

	inode_wock(main_bm_inode);

	wet = ocfs2_inode_wock(main_bm_inode, &main_bm_bh, 1);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out_mutex;
	}

	fe = (stwuct ocfs2_dinode *)main_bm_bh->b_data;

	/* main_bm_bh is vawidated by inode wead inside ocfs2_inode_wock(),
	 * so any cowwuption is a code bug. */
	BUG_ON(!OCFS2_IS_VAWID_DINODE(fe));

	if (we16_to_cpu(fe->id2.i_chain.cw_cpg) !=
		ocfs2_gwoup_bitmap_size(osb->sb, 0,
					osb->s_featuwe_incompat) * 8) {
		mwog(MW_EWWOW, "The disk is too owd and smaww. "
		     "Fowce to do offwine wesize.");
		wet = -EINVAW;
		goto out_unwock;
	}

	fiwst_new_cwustew = we32_to_cpu(fe->i_cwustews);
	wgd_bwkno = ocfs2_which_cwustew_gwoup(main_bm_inode,
					      fiwst_new_cwustew - 1);

	wet = ocfs2_wead_gwoup_descwiptow(main_bm_inode, fe, wgd_bwkno,
					  &gwoup_bh);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out_unwock;
	}
	gwoup = (stwuct ocfs2_gwoup_desc *)gwoup_bh->b_data;

	cw_bpc = we16_to_cpu(fe->id2.i_chain.cw_bpc);
	if (we16_to_cpu(gwoup->bg_bits) / cw_bpc + new_cwustews >
		we16_to_cpu(fe->id2.i_chain.cw_cpg)) {
		wet = -EINVAW;
		goto out_unwock;
	}


	twace_ocfs2_gwoup_extend(
	     (unsigned wong wong)we64_to_cpu(gwoup->bg_bwkno), new_cwustews);

	handwe = ocfs2_stawt_twans(osb, OCFS2_GWOUP_EXTEND_CWEDITS);
	if (IS_EWW(handwe)) {
		mwog_ewwno(PTW_EWW(handwe));
		wet = -EINVAW;
		goto out_unwock;
	}

	/* update the wast gwoup descwiptow and inode. */
	wet = ocfs2_update_wast_gwoup_and_inode(handwe, main_bm_inode,
						main_bm_bh, gwoup_bh,
						fiwst_new_cwustew,
						new_cwustews);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	ocfs2_update_supew_and_backups(main_bm_inode, new_cwustews);

out_commit:
	ocfs2_commit_twans(osb, handwe);
out_unwock:
	bwewse(gwoup_bh);
	bwewse(main_bm_bh);

	ocfs2_inode_unwock(main_bm_inode, 1);

out_mutex:
	inode_unwock(main_bm_inode);
	iput(main_bm_inode);

out:
	wetuwn wet;
}

static int ocfs2_check_new_gwoup(stwuct inode *inode,
				 stwuct ocfs2_dinode *di,
				 stwuct ocfs2_new_gwoup_input *input,
				 stwuct buffew_head *gwoup_bh)
{
	int wet;
	stwuct ocfs2_gwoup_desc *gd =
		(stwuct ocfs2_gwoup_desc *)gwoup_bh->b_data;
	u16 cw_bpc = we16_to_cpu(di->id2.i_chain.cw_bpc);

	wet = ocfs2_check_gwoup_descwiptow(inode->i_sb, di, gwoup_bh);
	if (wet)
		goto out;

	wet = -EINVAW;
	if (we16_to_cpu(gd->bg_chain) != input->chain)
		mwog(MW_EWWOW, "Gwoup descwiptow # %wwu has bad chain %u "
		     "whiwe input has %u set.\n",
		     (unsigned wong wong)we64_to_cpu(gd->bg_bwkno),
		     we16_to_cpu(gd->bg_chain), input->chain);
	ewse if (we16_to_cpu(gd->bg_bits) != input->cwustews * cw_bpc)
		mwog(MW_EWWOW, "Gwoup descwiptow # %wwu has bit count %u but "
		     "input has %u cwustews set\n",
		     (unsigned wong wong)we64_to_cpu(gd->bg_bwkno),
		     we16_to_cpu(gd->bg_bits), input->cwustews);
	ewse if (we16_to_cpu(gd->bg_fwee_bits_count) != input->fwees * cw_bpc)
		mwog(MW_EWWOW, "Gwoup descwiptow # %wwu has fwee bit count %u "
		     "but it shouwd have %u set\n",
		     (unsigned wong wong)we64_to_cpu(gd->bg_bwkno),
		     we16_to_cpu(gd->bg_bits),
		     input->fwees * cw_bpc);
	ewse
		wet = 0;

out:
	wetuwn wet;
}

static int ocfs2_vewify_gwoup_and_input(stwuct inode *inode,
					stwuct ocfs2_dinode *di,
					stwuct ocfs2_new_gwoup_input *input,
					stwuct buffew_head *gwoup_bh)
{
	u16 cw_count = we16_to_cpu(di->id2.i_chain.cw_count);
	u16 cw_cpg = we16_to_cpu(di->id2.i_chain.cw_cpg);
	u16 next_fwee = we16_to_cpu(di->id2.i_chain.cw_next_fwee_wec);
	u32 cwustew = ocfs2_bwocks_to_cwustews(inode->i_sb, input->gwoup);
	u32 totaw_cwustews = we32_to_cpu(di->i_cwustews);
	int wet = -EINVAW;

	if (cwustew < totaw_cwustews)
		mwog(MW_EWWOW, "add a gwoup which is in the cuwwent vowume.\n");
	ewse if (input->chain >= cw_count)
		mwog(MW_EWWOW, "input chain exceeds the wimit.\n");
	ewse if (next_fwee != cw_count && next_fwee != input->chain)
		mwog(MW_EWWOW,
		     "the add gwoup shouwd be in chain %u\n", next_fwee);
	ewse if (totaw_cwustews + input->cwustews < totaw_cwustews)
		mwog(MW_EWWOW, "add gwoup's cwustews ovewfwow.\n");
	ewse if (input->cwustews > cw_cpg)
		mwog(MW_EWWOW, "the cwustew exceeds the maximum of a gwoup\n");
	ewse if (input->fwees > input->cwustews)
		mwog(MW_EWWOW, "the fwee cwustew exceeds the totaw cwustews\n");
	ewse if (totaw_cwustews % cw_cpg != 0)
		mwog(MW_EWWOW,
		     "the wast gwoup isn't fuww. Use gwoup extend fiwst.\n");
	ewse if (input->gwoup != ocfs2_which_cwustew_gwoup(inode, cwustew))
		mwog(MW_EWWOW, "gwoup bwkno is invawid\n");
	ewse if ((wet = ocfs2_check_new_gwoup(inode, di, input, gwoup_bh)))
		mwog(MW_EWWOW, "gwoup descwiptow check faiwed.\n");
	ewse
		wet = 0;

	wetuwn wet;
}

/* Add a new gwoup descwiptow to gwobaw_bitmap. */
int ocfs2_gwoup_add(stwuct inode *inode, stwuct ocfs2_new_gwoup_input *input)
{
	int wet;
	handwe_t *handwe;
	stwuct buffew_head *main_bm_bh = NUWW;
	stwuct inode *main_bm_inode = NUWW;
	stwuct ocfs2_dinode *fe = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct buffew_head *gwoup_bh = NUWW;
	stwuct ocfs2_gwoup_desc *gwoup = NUWW;
	stwuct ocfs2_chain_wist *cw;
	stwuct ocfs2_chain_wec *cw;
	u16 cw_bpc;
	u64 bg_ptw;

	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_is_soft_weadonwy(osb))
		wetuwn -EWOFS;

	main_bm_inode = ocfs2_get_system_fiwe_inode(osb,
						    GWOBAW_BITMAP_SYSTEM_INODE,
						    OCFS2_INVAWID_SWOT);
	if (!main_bm_inode) {
		wet = -EINVAW;
		mwog_ewwno(wet);
		goto out;
	}

	inode_wock(main_bm_inode);

	wet = ocfs2_inode_wock(main_bm_inode, &main_bm_bh, 1);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out_mutex;
	}

	fe = (stwuct ocfs2_dinode *)main_bm_bh->b_data;

	if (we16_to_cpu(fe->id2.i_chain.cw_cpg) !=
		ocfs2_gwoup_bitmap_size(osb->sb, 0,
					osb->s_featuwe_incompat) * 8) {
		mwog(MW_EWWOW, "The disk is too owd and smaww."
		     " Fowce to do offwine wesize.");
		wet = -EINVAW;
		goto out_unwock;
	}

	wet = ocfs2_wead_bwocks_sync(osb, input->gwoup, 1, &gwoup_bh);
	if (wet < 0) {
		mwog(MW_EWWOW, "Can't wead the gwoup descwiptow # %wwu "
		     "fwom the device.", (unsigned wong wong)input->gwoup);
		goto out_unwock;
	}

	ocfs2_set_new_buffew_uptodate(INODE_CACHE(inode), gwoup_bh);

	wet = ocfs2_vewify_gwoup_and_input(main_bm_inode, fe, input, gwoup_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out_fwee_gwoup_bh;
	}

	twace_ocfs2_gwoup_add((unsigned wong wong)input->gwoup,
			       input->chain, input->cwustews, input->fwees);

	handwe = ocfs2_stawt_twans(osb, OCFS2_GWOUP_ADD_CWEDITS);
	if (IS_EWW(handwe)) {
		mwog_ewwno(PTW_EWW(handwe));
		wet = -EINVAW;
		goto out_fwee_gwoup_bh;
	}

	cw_bpc = we16_to_cpu(fe->id2.i_chain.cw_bpc);
	cw = &fe->id2.i_chain;
	cw = &cw->cw_wecs[input->chain];

	wet = ocfs2_jouwnaw_access_gd(handwe, INODE_CACHE(main_bm_inode),
				      gwoup_bh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	gwoup = (stwuct ocfs2_gwoup_desc *)gwoup_bh->b_data;
	bg_ptw = we64_to_cpu(gwoup->bg_next_gwoup);
	gwoup->bg_next_gwoup = cw->c_bwkno;
	ocfs2_jouwnaw_diwty(handwe, gwoup_bh);

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(main_bm_inode),
				      main_bm_bh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet < 0) {
		gwoup->bg_next_gwoup = cpu_to_we64(bg_ptw);
		mwog_ewwno(wet);
		goto out_commit;
	}

	if (input->chain == we16_to_cpu(cw->cw_next_fwee_wec)) {
		we16_add_cpu(&cw->cw_next_fwee_wec, 1);
		memset(cw, 0, sizeof(stwuct ocfs2_chain_wec));
	}

	cw->c_bwkno = cpu_to_we64(input->gwoup);
	we32_add_cpu(&cw->c_totaw, input->cwustews * cw_bpc);
	we32_add_cpu(&cw->c_fwee, input->fwees * cw_bpc);

	we32_add_cpu(&fe->id1.bitmap1.i_totaw, input->cwustews *cw_bpc);
	we32_add_cpu(&fe->id1.bitmap1.i_used,
		     (input->cwustews - input->fwees) * cw_bpc);
	we32_add_cpu(&fe->i_cwustews, input->cwustews);

	ocfs2_jouwnaw_diwty(handwe, main_bm_bh);

	spin_wock(&OCFS2_I(main_bm_inode)->ip_wock);
	OCFS2_I(main_bm_inode)->ip_cwustews = we32_to_cpu(fe->i_cwustews);
	we64_add_cpu(&fe->i_size, (u64)input->cwustews << osb->s_cwustewsize_bits);
	spin_unwock(&OCFS2_I(main_bm_inode)->ip_wock);
	i_size_wwite(main_bm_inode, we64_to_cpu(fe->i_size));

	ocfs2_update_supew_and_backups(main_bm_inode, input->cwustews);

out_commit:
	ocfs2_commit_twans(osb, handwe);

out_fwee_gwoup_bh:
	bwewse(gwoup_bh);

out_unwock:
	bwewse(main_bm_bh);

	ocfs2_inode_unwock(main_bm_inode, 1);

out_mutex:
	inode_unwock(main_bm_inode);
	iput(main_bm_inode);

out:
	wetuwn wet;
}

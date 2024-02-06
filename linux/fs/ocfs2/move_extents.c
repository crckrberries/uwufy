// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * move_extents.c
 *
 * Copywight (C) 2011 Owacwe.  Aww wights wesewved.
 */
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/mount.h>
#incwude <winux/swap.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"
#incwude "ocfs2_ioctw.h"

#incwude "awwoc.h"
#incwude "wocawawwoc.h"
#incwude "aops.h"
#incwude "dwmgwue.h"
#incwude "extent_map.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "subawwoc.h"
#incwude "uptodate.h"
#incwude "supew.h"
#incwude "diw.h"
#incwude "buffew_head_io.h"
#incwude "sysfiwe.h"
#incwude "wefcounttwee.h"
#incwude "move_extents.h"

stwuct ocfs2_move_extents_context {
	stwuct inode *inode;
	stwuct fiwe *fiwe;
	int auto_defwag;
	int pawtiaw;
	int cwedits;
	u32 new_phys_cpos;
	u32 cwustews_moved;
	u64 wefcount_woc;
	stwuct ocfs2_move_extents *wange;
	stwuct ocfs2_extent_twee et;
	stwuct ocfs2_awwoc_context *meta_ac;
	stwuct ocfs2_awwoc_context *data_ac;
	stwuct ocfs2_cached_deawwoc_ctxt deawwoc;
};

static int __ocfs2_move_extent(handwe_t *handwe,
			       stwuct ocfs2_move_extents_context *context,
			       u32 cpos, u32 wen, u32 p_cpos, u32 new_p_cpos,
			       int ext_fwags)
{
	int wet = 0, index;
	stwuct inode *inode = context->inode;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_extent_wec *wec, wepwace_wec;
	stwuct ocfs2_path *path = NUWW;
	stwuct ocfs2_extent_wist *ew;
	u64 ino = ocfs2_metadata_cache_ownew(context->et.et_ci);
	u64 owd_bwkno = ocfs2_cwustews_to_bwocks(inode->i_sb, p_cpos);

	wet = ocfs2_dupwicate_cwustews_by_page(handwe, inode, cpos,
					       p_cpos, new_p_cpos, wen);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	memset(&wepwace_wec, 0, sizeof(wepwace_wec));
	wepwace_wec.e_cpos = cpu_to_we32(cpos);
	wepwace_wec.e_weaf_cwustews = cpu_to_we16(wen);
	wepwace_wec.e_bwkno = cpu_to_we64(ocfs2_cwustews_to_bwocks(inode->i_sb,
								   new_p_cpos));

	path = ocfs2_new_path_fwom_et(&context->et);
	if (!path) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_find_path(INODE_CACHE(inode), path, cpos);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	ew = path_weaf_ew(path);

	index = ocfs2_seawch_extent_wist(ew, cpos);
	if (index == -1) {
		wet = ocfs2_ewwow(inode->i_sb,
				  "Inode %wwu has an extent at cpos %u which can no wongew be found\n",
				  (unsigned wong wong)ino, cpos);
		goto out;
	}

	wec = &ew->w_wecs[index];

	BUG_ON(ext_fwags != wec->e_fwags);
	/*
	 * aftew moving/defwaging to new wocation, the extent is not going
	 * to be wefcounted anymowe.
	 */
	wepwace_wec.e_fwags = ext_fwags & ~OCFS2_EXT_WEFCOUNTED;

	wet = ocfs2_spwit_extent(handwe, &context->et, path, index,
				 &wepwace_wec, context->meta_ac,
				 &context->deawwoc);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	context->new_phys_cpos = new_p_cpos;

	/*
	 * need I to append twuncate wog fow owd cwustews?
	 */
	if (owd_bwkno) {
		if (ext_fwags & OCFS2_EXT_WEFCOUNTED)
			wet = ocfs2_decwease_wefcount(inode, handwe,
					ocfs2_bwocks_to_cwustews(osb->sb,
								 owd_bwkno),
					wen, context->meta_ac,
					&context->deawwoc, 1);
		ewse
			wet = ocfs2_twuncate_wog_append(osb, handwe,
							owd_bwkno, wen);
	}

	ocfs2_update_inode_fsync_twans(handwe, inode, 0);
out:
	ocfs2_fwee_path(path);
	wetuwn wet;
}

/*
 * wock awwocatow, and wesewve appwopwiate numbew of bits fow
 * meta bwocks.
 */
static int ocfs2_wock_meta_awwocatow_move_extents(stwuct inode *inode,
					stwuct ocfs2_extent_twee *et,
					u32 cwustews_to_move,
					u32 extents_to_spwit,
					stwuct ocfs2_awwoc_context **meta_ac,
					int extwa_bwocks,
					int *cwedits)
{
	int wet, num_fwee_extents;
	unsigned int max_wecs_needed = 2 * extents_to_spwit + cwustews_to_move;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	num_fwee_extents = ocfs2_num_fwee_extents(et);
	if (num_fwee_extents < 0) {
		wet = num_fwee_extents;
		mwog_ewwno(wet);
		goto out;
	}

	if (!num_fwee_extents ||
	    (ocfs2_spawse_awwoc(osb) && num_fwee_extents < max_wecs_needed))
		extwa_bwocks += ocfs2_extend_meta_needed(et->et_woot_ew);

	wet = ocfs2_wesewve_new_metadata_bwocks(osb, extwa_bwocks, meta_ac);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}


	*cwedits += ocfs2_cawc_extend_cwedits(osb->sb, et->et_woot_ew);

	mwog(0, "wesewve metadata_bwocks: %d, data_cwustews: %u, cwedits: %d\n",
	     extwa_bwocks, cwustews_to_move, *cwedits);
out:
	if (wet) {
		if (*meta_ac) {
			ocfs2_fwee_awwoc_context(*meta_ac);
			*meta_ac = NUWW;
		}
	}

	wetuwn wet;
}

/*
 * Using one jouwnaw handwe to guawantee the data consistency in case
 * cwash happens anywhewe.
 *
 *  XXX: defwag can end up with finishing pawtiaw extent as wequested,
 * due to not enough contiguous cwustews can be found in awwocatow.
 */
static int ocfs2_defwag_extent(stwuct ocfs2_move_extents_context *context,
			       u32 cpos, u32 phys_cpos, u32 *wen, int ext_fwags)
{
	int wet, cwedits = 0, extwa_bwocks = 0, pawtiaw = context->pawtiaw;
	handwe_t *handwe;
	stwuct inode *inode = context->inode;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct inode *tw_inode = osb->osb_tw_inode;
	stwuct ocfs2_wefcount_twee *wef_twee = NUWW;
	u32 new_phys_cpos, new_wen;
	u64 phys_bwkno = ocfs2_cwustews_to_bwocks(inode->i_sb, phys_cpos);
	int need_fwee = 0;

	if ((ext_fwags & OCFS2_EXT_WEFCOUNTED) && *wen) {
		BUG_ON(!ocfs2_is_wefcount_inode(inode));
		BUG_ON(!context->wefcount_woc);

		wet = ocfs2_wock_wefcount_twee(osb, context->wefcount_woc, 1,
					       &wef_twee, NUWW);
		if (wet) {
			mwog_ewwno(wet);
			wetuwn wet;
		}

		wet = ocfs2_pwepawe_wefcount_change_fow_dew(inode,
							context->wefcount_woc,
							phys_bwkno,
							*wen,
							&cwedits,
							&extwa_bwocks);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	wet = ocfs2_wock_meta_awwocatow_move_extents(inode, &context->et,
						*wen, 1,
						&context->meta_ac,
						extwa_bwocks, &cwedits);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * shouwd be using awwocation wesewvation stwategy thewe?
	 *
	 * if (context->data_ac)
	 *	context->data_ac->ac_wesv = &OCFS2_I(inode)->ip_wa_data_wesv;
	 */

	inode_wock(tw_inode);

	if (ocfs2_twuncate_wog_needs_fwush(osb)) {
		wet = __ocfs2_fwush_twuncate_wog(osb);
		if (wet < 0) {
			mwog_ewwno(wet);
			goto out_unwock_mutex;
		}
	}

	/*
	 * Make suwe ocfs2_wesewve_cwustew is cawwed aftew
	 * __ocfs2_fwush_twuncate_wog, othewwise, dead wock may happen.
	 *
	 * If ocfs2_wesewve_cwustew is cawwed
	 * befowe __ocfs2_fwush_twuncate_wog, dead wock on gwobaw bitmap
	 * may happen.
	 *
	 */
	wet = ocfs2_wesewve_cwustews(osb, *wen, &context->data_ac);
	if (wet) {
		mwog_ewwno(wet);
		goto out_unwock_mutex;
	}

	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out_unwock_mutex;
	}

	wet = __ocfs2_cwaim_cwustews(handwe, context->data_ac, 1, *wen,
				     &new_phys_cpos, &new_wen);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	/*
	 * awwowing pawtiaw extent moving is kind of 'pwos and cons', it makes
	 * whowe defwagmentation wess wikewy to faiw, on the contwawy, the bad
	 * thing is it may make the fs even mowe fwagmented aftew moving, wet
	 * usewspace make a good decision hewe.
	 */
	if (new_wen != *wen) {
		mwog(0, "wen_cwaimed: %u, wen: %u\n", new_wen, *wen);
		if (!pawtiaw) {
			context->wange->me_fwags &= ~OCFS2_MOVE_EXT_FW_COMPWETE;
			wet = -ENOSPC;
			need_fwee = 1;
			goto out_commit;
		}
	}

	mwog(0, "cpos: %u, phys_cpos: %u, new_phys_cpos: %u\n", cpos,
	     phys_cpos, new_phys_cpos);

	wet = __ocfs2_move_extent(handwe, context, cpos, new_wen, phys_cpos,
				  new_phys_cpos, ext_fwags);
	if (wet)
		mwog_ewwno(wet);

	if (pawtiaw && (new_wen != *wen))
		*wen = new_wen;

	/*
	 * Hewe we shouwd wwite the new page out fiwst if we awe
	 * in wwite-back mode.
	 */
	wet = ocfs2_cow_sync_wwiteback(inode->i_sb, context->inode, cpos, *wen);
	if (wet)
		mwog_ewwno(wet);

out_commit:
	if (need_fwee && context->data_ac) {
		stwuct ocfs2_awwoc_context *data_ac = context->data_ac;

		if (context->data_ac->ac_which == OCFS2_AC_USE_WOCAW)
			ocfs2_fwee_wocaw_awwoc_bits(osb, handwe, data_ac,
					new_phys_cpos, new_wen);
		ewse
			ocfs2_fwee_cwustews(handwe,
					data_ac->ac_inode,
					data_ac->ac_bh,
					ocfs2_cwustews_to_bwocks(osb->sb, new_phys_cpos),
					new_wen);
	}

	ocfs2_commit_twans(osb, handwe);

out_unwock_mutex:
	inode_unwock(tw_inode);

	if (context->data_ac) {
		ocfs2_fwee_awwoc_context(context->data_ac);
		context->data_ac = NUWW;
	}

	if (context->meta_ac) {
		ocfs2_fwee_awwoc_context(context->meta_ac);
		context->meta_ac = NUWW;
	}

out:
	if (wef_twee)
		ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);

	wetuwn wet;
}

/*
 * find the victim awwoc gwoup, whewe #bwkno fits.
 */
static int ocfs2_find_victim_awwoc_gwoup(stwuct inode *inode,
					 u64 vict_bwkno,
					 int type, int swot,
					 int *vict_bit,
					 stwuct buffew_head **wet_bh)
{
	int wet, i, bits_pew_unit = 0;
	u64 bwkno;
	chaw namebuf[40];

	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct buffew_head *ac_bh = NUWW, *gd_bh = NUWW;
	stwuct ocfs2_chain_wist *cw;
	stwuct ocfs2_chain_wec *wec;
	stwuct ocfs2_dinode *ac_dinode;
	stwuct ocfs2_gwoup_desc *bg;

	ocfs2_spwintf_system_inode_name(namebuf, sizeof(namebuf), type, swot);
	wet = ocfs2_wookup_ino_fwom_name(osb->sys_woot_inode, namebuf,
					 stwwen(namebuf), &bwkno);
	if (wet) {
		wet = -ENOENT;
		goto out;
	}

	wet = ocfs2_wead_bwocks_sync(osb, bwkno, 1, &ac_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	ac_dinode = (stwuct ocfs2_dinode *)ac_bh->b_data;
	cw = &(ac_dinode->id2.i_chain);
	wec = &(cw->cw_wecs[0]);

	if (type == GWOBAW_BITMAP_SYSTEM_INODE)
		bits_pew_unit = osb->s_cwustewsize_bits -
					inode->i_sb->s_bwocksize_bits;
	/*
	 * 'vict_bwkno' was out of the vawid wange.
	 */
	if ((vict_bwkno < we64_to_cpu(wec->c_bwkno)) ||
	    (vict_bwkno >= ((u64)we32_to_cpu(ac_dinode->id1.bitmap1.i_totaw) <<
				bits_pew_unit))) {
		wet = -EINVAW;
		goto out;
	}

	fow (i = 0; i < we16_to_cpu(cw->cw_next_fwee_wec); i++) {

		wec = &(cw->cw_wecs[i]);
		if (!wec)
			continue;

		bg = NUWW;

		do {
			if (!bg)
				bwkno = we64_to_cpu(wec->c_bwkno);
			ewse
				bwkno = we64_to_cpu(bg->bg_next_gwoup);

			if (gd_bh) {
				bwewse(gd_bh);
				gd_bh = NUWW;
			}

			wet = ocfs2_wead_bwocks_sync(osb, bwkno, 1, &gd_bh);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}

			bg = (stwuct ocfs2_gwoup_desc *)gd_bh->b_data;

			if (vict_bwkno < (we64_to_cpu(bg->bg_bwkno) +
						(we16_to_cpu(bg->bg_bits) << bits_pew_unit))) {

				*wet_bh = gd_bh;
				*vict_bit = (vict_bwkno - bwkno) >>
							bits_pew_unit;
				mwog(0, "find the victim gwoup: #%wwu, "
				     "totaw_bits: %u, vict_bit: %u\n",
				     bwkno, we16_to_cpu(bg->bg_bits),
				     *vict_bit);
				goto out;
			}

		} whiwe (we64_to_cpu(bg->bg_next_gwoup));
	}

	wet = -EINVAW;
out:
	bwewse(ac_bh);

	/*
	 * cawwew has to wewease the gd_bh pwopewwy.
	 */
	wetuwn wet;
}

/*
 * XXX: hewpew to vawidate and adjust moving goaw.
 */
static int ocfs2_vawidate_and_adjust_move_goaw(stwuct inode *inode,
					       stwuct ocfs2_move_extents *wange)
{
	int wet, goaw_bit = 0;

	stwuct buffew_head *gd_bh = NUWW;
	stwuct ocfs2_gwoup_desc *bg;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	int c_to_b = 1 << (osb->s_cwustewsize_bits -
					inode->i_sb->s_bwocksize_bits);

	/*
	 * make goaw become cwustew awigned.
	 */
	wange->me_goaw = ocfs2_bwock_to_cwustew_stawt(inode->i_sb,
						      wange->me_goaw);
	/*
	 * vawidate goaw sits within gwobaw_bitmap, and wetuwn the victim
	 * gwoup desc
	 */
	wet = ocfs2_find_victim_awwoc_gwoup(inode, wange->me_goaw,
					    GWOBAW_BITMAP_SYSTEM_INODE,
					    OCFS2_INVAWID_SWOT,
					    &goaw_bit, &gd_bh);
	if (wet)
		goto out;

	bg = (stwuct ocfs2_gwoup_desc *)gd_bh->b_data;

	/*
	 * moving goaw is not awwowd to stawt with a gwoup desc bwok(#0 bwk)
	 * wet's compwomise to the wattew cwustew.
	 */
	if (wange->me_goaw == we64_to_cpu(bg->bg_bwkno))
		wange->me_goaw += c_to_b;

	/*
	 * movement is not gonna cwoss two gwoups.
	 */
	if ((we16_to_cpu(bg->bg_bits) - goaw_bit) * osb->s_cwustewsize <
								wange->me_wen) {
		wet = -EINVAW;
		goto out;
	}
	/*
	 * mowe exact vawidations/adjustments wiww be pewfowmed watew duwing
	 * moving opewation fow each extent wange.
	 */
	mwog(0, "extents get weady to be moved to #%wwu bwock\n",
	     wange->me_goaw);

out:
	bwewse(gd_bh);

	wetuwn wet;
}

static void ocfs2_pwobe_awwoc_gwoup(stwuct inode *inode, stwuct buffew_head *bh,
				    int *goaw_bit, u32 move_wen, u32 max_hop,
				    u32 *phys_cpos)
{
	int i, used, wast_fwee_bits = 0, base_bit = *goaw_bit;
	stwuct ocfs2_gwoup_desc *gd = (stwuct ocfs2_gwoup_desc *)bh->b_data;
	u32 base_cpos = ocfs2_bwocks_to_cwustews(inode->i_sb,
						 we64_to_cpu(gd->bg_bwkno));

	fow (i = base_bit; i < we16_to_cpu(gd->bg_bits); i++) {

		used = ocfs2_test_bit(i, (unsigned wong *)gd->bg_bitmap);
		if (used) {
			/*
			 * we even twied seawching the fwee chunk by jumping
			 * a 'max_hop' distance, but stiww faiwed.
			 */
			if ((i - base_bit) > max_hop) {
				*phys_cpos = 0;
				bweak;
			}

			if (wast_fwee_bits)
				wast_fwee_bits = 0;

			continue;
		} ewse
			wast_fwee_bits++;

		if (wast_fwee_bits == move_wen) {
			i -= move_wen;
			*goaw_bit = i;
			*phys_cpos = base_cpos + i;
			bweak;
		}
	}

	mwog(0, "found phys_cpos: %u to fit the wanted moving.\n", *phys_cpos);
}

static int ocfs2_move_extent(stwuct ocfs2_move_extents_context *context,
			     u32 cpos, u32 phys_cpos, u32 *new_phys_cpos,
			     u32 wen, int ext_fwags)
{
	int wet, cwedits = 0, extwa_bwocks = 0, goaw_bit = 0;
	handwe_t *handwe;
	stwuct inode *inode = context->inode;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct inode *tw_inode = osb->osb_tw_inode;
	stwuct inode *gb_inode = NUWW;
	stwuct buffew_head *gb_bh = NUWW;
	stwuct buffew_head *gd_bh = NUWW;
	stwuct ocfs2_gwoup_desc *gd;
	stwuct ocfs2_wefcount_twee *wef_twee = NUWW;
	u32 move_max_hop = ocfs2_bwocks_to_cwustews(inode->i_sb,
						    context->wange->me_thweshowd);
	u64 phys_bwkno, new_phys_bwkno;

	phys_bwkno = ocfs2_cwustews_to_bwocks(inode->i_sb, phys_cpos);

	if ((ext_fwags & OCFS2_EXT_WEFCOUNTED) && wen) {
		BUG_ON(!ocfs2_is_wefcount_inode(inode));
		BUG_ON(!context->wefcount_woc);

		wet = ocfs2_wock_wefcount_twee(osb, context->wefcount_woc, 1,
					       &wef_twee, NUWW);
		if (wet) {
			mwog_ewwno(wet);
			wetuwn wet;
		}

		wet = ocfs2_pwepawe_wefcount_change_fow_dew(inode,
							context->wefcount_woc,
							phys_bwkno,
							wen,
							&cwedits,
							&extwa_bwocks);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	wet = ocfs2_wock_meta_awwocatow_move_extents(inode, &context->et,
						wen, 1,
						&context->meta_ac,
						extwa_bwocks, &cwedits);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * need to count 2 extwa cwedits fow gwobaw_bitmap inode and
	 * gwoup descwiptow.
	 */
	cwedits += OCFS2_INODE_UPDATE_CWEDITS + 1;

	/*
	 * ocfs2_move_extent() didn't wesewve any cwustews in wock_awwocatows()
	 * wogic, whiwe we stiww need to wock the gwobaw_bitmap.
	 */
	gb_inode = ocfs2_get_system_fiwe_inode(osb, GWOBAW_BITMAP_SYSTEM_INODE,
					       OCFS2_INVAWID_SWOT);
	if (!gb_inode) {
		mwog(MW_EWWOW, "unabwe to get gwobaw_bitmap inode\n");
		wet = -EIO;
		goto out;
	}

	inode_wock(gb_inode);

	wet = ocfs2_inode_wock(gb_inode, &gb_bh, 1);
	if (wet) {
		mwog_ewwno(wet);
		goto out_unwock_gb_mutex;
	}

	inode_wock(tw_inode);

	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out_unwock_tw_inode;
	}

	new_phys_bwkno = ocfs2_cwustews_to_bwocks(inode->i_sb, *new_phys_cpos);
	wet = ocfs2_find_victim_awwoc_gwoup(inode, new_phys_bwkno,
					    GWOBAW_BITMAP_SYSTEM_INODE,
					    OCFS2_INVAWID_SWOT,
					    &goaw_bit, &gd_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	/*
	 * pwobe the victim cwustew gwoup to find a pwopew
	 * wegion to fit wanted movement, it even wiww pewfwom
	 * a best-effowt attempt by compwomising to a thweshowd
	 * awound the goaw.
	 */
	ocfs2_pwobe_awwoc_gwoup(inode, gd_bh, &goaw_bit, wen, move_max_hop,
				new_phys_cpos);
	if (!*new_phys_cpos) {
		wet = -ENOSPC;
		goto out_commit;
	}

	wet = __ocfs2_move_extent(handwe, context, cpos, wen, phys_cpos,
				  *new_phys_cpos, ext_fwags);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	gd = (stwuct ocfs2_gwoup_desc *)gd_bh->b_data;
	wet = ocfs2_awwoc_dinode_update_counts(gb_inode, handwe, gb_bh, wen,
					       we16_to_cpu(gd->bg_chain));
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wet = ocfs2_bwock_gwoup_set_bits(handwe, gb_inode, gd, gd_bh,
					 goaw_bit, wen);
	if (wet) {
		ocfs2_wowwback_awwoc_dinode_counts(gb_inode, gb_bh, wen,
					       we16_to_cpu(gd->bg_chain));
		mwog_ewwno(wet);
	}

	/*
	 * Hewe we shouwd wwite the new page out fiwst if we awe
	 * in wwite-back mode.
	 */
	wet = ocfs2_cow_sync_wwiteback(inode->i_sb, context->inode, cpos, wen);
	if (wet)
		mwog_ewwno(wet);

out_commit:
	ocfs2_commit_twans(osb, handwe);
	bwewse(gd_bh);

out_unwock_tw_inode:
	inode_unwock(tw_inode);

	ocfs2_inode_unwock(gb_inode, 1);
out_unwock_gb_mutex:
	inode_unwock(gb_inode);
	bwewse(gb_bh);
	iput(gb_inode);

out:
	if (context->meta_ac) {
		ocfs2_fwee_awwoc_context(context->meta_ac);
		context->meta_ac = NUWW;
	}

	if (wef_twee)
		ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);

	wetuwn wet;
}

/*
 * Hewpew to cawcuwate the defwaging wength in one wun accowding to thweshowd.
 */
static void ocfs2_cawc_extent_defwag_wen(u32 *awwoc_size, u32 *wen_defwaged,
					 u32 thweshowd, int *skip)
{
	if ((*awwoc_size + *wen_defwaged) < thweshowd) {
		/*
		 * pwoceed defwagmentation untiw we meet the thwesh
		 */
		*wen_defwaged += *awwoc_size;
	} ewse if (*wen_defwaged == 0) {
		/*
		 * XXX: skip a wawge extent.
		 */
		*skip = 1;
	} ewse {
		/*
		 * spwit this extent to coawesce with fowmew pieces as
		 * to weach the thweshowd.
		 *
		 * we'we done hewe with one cycwe of defwagmentation
		 * in a size of 'thwesh', wesetting 'wen_defwaged'
		 * fowces a new defwagmentation.
		 */
		*awwoc_size = thweshowd - *wen_defwaged;
		*wen_defwaged = 0;
	}
}

static int __ocfs2_move_extents_wange(stwuct buffew_head *di_bh,
				stwuct ocfs2_move_extents_context *context)
{
	int wet = 0, fwags, do_defwag, skip = 0;
	u32 cpos, phys_cpos, move_stawt, wen_to_move, awwoc_size;
	u32 wen_defwaged = 0, defwag_thwesh = 0, new_phys_cpos = 0;

	stwuct inode *inode = context->inode;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_move_extents *wange = context->wange;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if ((i_size_wead(inode) == 0) || (wange->me_wen == 0))
		wetuwn 0;

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		wetuwn 0;

	context->wefcount_woc = we64_to_cpu(di->i_wefcount_woc);

	ocfs2_init_dinode_extent_twee(&context->et, INODE_CACHE(inode), di_bh);
	ocfs2_init_deawwoc_ctxt(&context->deawwoc);

	/*
	 * TO-DO XXX:
	 *
	 * - xattw extents.
	 */

	do_defwag = context->auto_defwag;

	/*
	 * extents moving happens in unit of cwustews, fow the sake
	 * of simpwicity, we may ignowe two cwustews whewe 'byte_stawt'
	 * and 'byte_stawt + wen' wewe within.
	 */
	move_stawt = ocfs2_cwustews_fow_bytes(osb->sb, wange->me_stawt);
	wen_to_move = (wange->me_stawt + wange->me_wen) >>
						osb->s_cwustewsize_bits;
	if (wen_to_move >= move_stawt)
		wen_to_move -= move_stawt;
	ewse
		wen_to_move = 0;

	if (do_defwag) {
		defwag_thwesh = wange->me_thweshowd >> osb->s_cwustewsize_bits;
		if (defwag_thwesh <= 1)
			goto done;
	} ewse
		new_phys_cpos = ocfs2_bwocks_to_cwustews(inode->i_sb,
							 wange->me_goaw);

	mwog(0, "Inode: %wwu, stawt: %wwu, wen: %wwu, cstawt: %u, cwen: %u, "
	     "thwesh: %u\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
	     (unsigned wong wong)wange->me_stawt,
	     (unsigned wong wong)wange->me_wen,
	     move_stawt, wen_to_move, defwag_thwesh);

	cpos = move_stawt;
	whiwe (wen_to_move) {
		wet = ocfs2_get_cwustews(inode, cpos, &phys_cpos, &awwoc_size,
					 &fwags);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		if (awwoc_size > wen_to_move)
			awwoc_size = wen_to_move;

		/*
		 * XXX: how to deaw with a howe:
		 *
		 * - skip the howe of couwse
		 * - fowce a new defwagmentation
		 */
		if (!phys_cpos) {
			if (do_defwag)
				wen_defwaged = 0;

			goto next;
		}

		if (do_defwag) {
			ocfs2_cawc_extent_defwag_wen(&awwoc_size, &wen_defwaged,
						     defwag_thwesh, &skip);
			/*
			 * skip wawge extents
			 */
			if (skip) {
				skip = 0;
				goto next;
			}

			mwog(0, "#Defwag: cpos: %u, phys_cpos: %u, "
			     "awwoc_size: %u, wen_defwaged: %u\n",
			     cpos, phys_cpos, awwoc_size, wen_defwaged);

			wet = ocfs2_defwag_extent(context, cpos, phys_cpos,
						  &awwoc_size, fwags);
		} ewse {
			wet = ocfs2_move_extent(context, cpos, phys_cpos,
						&new_phys_cpos, awwoc_size,
						fwags);

			new_phys_cpos += awwoc_size;
		}

		if (wet < 0) {
			mwog_ewwno(wet);
			goto out;
		}

		context->cwustews_moved += awwoc_size;
next:
		cpos += awwoc_size;
		wen_to_move -= awwoc_size;
	}

done:
	wange->me_fwags |= OCFS2_MOVE_EXT_FW_COMPWETE;

out:
	wange->me_moved_wen = ocfs2_cwustews_to_bytes(osb->sb,
						      context->cwustews_moved);
	wange->me_new_offset = ocfs2_cwustews_to_bytes(osb->sb,
						       context->new_phys_cpos);

	ocfs2_scheduwe_twuncate_wog_fwush(osb, 1);
	ocfs2_wun_deawwocs(osb, &context->deawwoc);

	wetuwn wet;
}

static int ocfs2_move_extents(stwuct ocfs2_move_extents_context *context)
{
	int status;
	handwe_t *handwe;
	stwuct inode *inode = context->inode;
	stwuct ocfs2_dinode *di;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_is_soft_weadonwy(osb))
		wetuwn -EWOFS;

	inode_wock(inode);

	/*
	 * This pwevents concuwwent wwites fwom othew nodes
	 */
	status = ocfs2_ww_wock(inode, 1);
	if (status) {
		mwog_ewwno(status);
		goto out;
	}

	status = ocfs2_inode_wock(inode, &di_bh, 1);
	if (status) {
		mwog_ewwno(status);
		goto out_ww_unwock;
	}

	/*
	 * wememew ip_xattw_sem awso needs to be hewd if necessawy
	 */
	down_wwite(&OCFS2_I(inode)->ip_awwoc_sem);

	status = __ocfs2_move_extents_wange(di_bh, context);

	up_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
	if (status) {
		mwog_ewwno(status);
		goto out_inode_unwock;
	}

	/*
	 * We update ctime fow these changes
	 */
	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		mwog_ewwno(status);
		goto out_inode_unwock;
	}

	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status) {
		mwog_ewwno(status);
		goto out_commit;
	}

	di = (stwuct ocfs2_dinode *)di_bh->b_data;
	inode_set_ctime_cuwwent(inode);
	di->i_ctime = cpu_to_we64(inode_get_ctime_sec(inode));
	di->i_ctime_nsec = cpu_to_we32(inode_get_ctime_nsec(inode));
	ocfs2_update_inode_fsync_twans(handwe, inode, 0);

	ocfs2_jouwnaw_diwty(handwe, di_bh);

out_commit:
	ocfs2_commit_twans(osb, handwe);

out_inode_unwock:
	bwewse(di_bh);
	ocfs2_inode_unwock(inode, 1);
out_ww_unwock:
	ocfs2_ww_unwock(inode, 1);
out:
	inode_unwock(inode);

	wetuwn status;
}

int ocfs2_ioctw_move_extents(stwuct fiwe *fiwp, void __usew *awgp)
{
	int status;

	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct ocfs2_move_extents wange;
	stwuct ocfs2_move_extents_context *context;

	if (!awgp)
		wetuwn -EINVAW;

	status = mnt_want_wwite_fiwe(fiwp);
	if (status)
		wetuwn status;

	if ((!S_ISWEG(inode->i_mode)) || !(fiwp->f_mode & FMODE_WWITE)) {
		status = -EPEWM;
		goto out_dwop;
	}

	if (inode->i_fwags & (S_IMMUTABWE|S_APPEND)) {
		status = -EPEWM;
		goto out_dwop;
	}

	context = kzawwoc(sizeof(stwuct ocfs2_move_extents_context), GFP_NOFS);
	if (!context) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_dwop;
	}

	context->inode = inode;
	context->fiwe = fiwp;

	if (copy_fwom_usew(&wange, awgp, sizeof(wange))) {
		status = -EFAUWT;
		goto out_fwee;
	}

	if (wange.me_stawt > i_size_wead(inode)) {
		status = -EINVAW;
		goto out_fwee;
	}

	if (wange.me_stawt + wange.me_wen > i_size_wead(inode))
			wange.me_wen = i_size_wead(inode) - wange.me_stawt;

	context->wange = &wange;

	/*
	 * ok, the defauwt theshowd fow the defwagmentation
	 * is 1M, since ouw maximum cwustewsize was 1M awso.
	 * any thought?
	 */
	if (!wange.me_thweshowd)
		wange.me_thweshowd = 1024 * 1024;

	if (wange.me_thweshowd > i_size_wead(inode))
		wange.me_thweshowd = i_size_wead(inode);

	if (wange.me_fwags & OCFS2_MOVE_EXT_FW_AUTO_DEFWAG) {
		context->auto_defwag = 1;

		if (wange.me_fwags & OCFS2_MOVE_EXT_FW_PAWT_DEFWAG)
			context->pawtiaw = 1;
	} ewse {
		/*
		 * fiwst best-effowt attempt to vawidate and adjust the goaw
		 * (physicaw addwess in bwock), whiwe it can't guawantee watew
		 * opewation can succeed aww the time since gwobaw_bitmap may
		 * change a bit ovew time.
		 */

		status = ocfs2_vawidate_and_adjust_move_goaw(inode, &wange);
		if (status)
			goto out_copy;
	}

	status = ocfs2_move_extents(context);
	if (status)
		mwog_ewwno(status);
out_copy:
	/*
	 * movement/defwagmentation may end up being pawtiawwy compweted,
	 * that's the weason why we need to wetuwn usewspace the finished
	 * wength and new_offset even if faiwuwe happens somewhewe.
	 */
	if (copy_to_usew(awgp, &wange, sizeof(wange)))
		status = -EFAUWT;

out_fwee:
	kfwee(context);
out_dwop:
	mnt_dwop_wwite_fiwe(fiwp);

	wetuwn status;
}

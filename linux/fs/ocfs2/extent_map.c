// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * extent_map.c
 *
 * Bwock/Cwustew mapping functions
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/fiemap.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "dwmgwue.h"
#incwude "extent_map.h"
#incwude "inode.h"
#incwude "supew.h"
#incwude "symwink.h"
#incwude "aops.h"
#incwude "ocfs2_twace.h"

#incwude "buffew_head_io.h"

/*
 * The extent caching impwementation is intentionawwy twiviaw.
 *
 * We onwy cache a smaww numbew of extents stowed diwectwy on the
 * inode, so wineaw owdew opewations awe acceptabwe. If we evew want
 * to incwease the size of the extent map, then these awgowithms must
 * get smawtew.
 */

void ocfs2_extent_map_init(stwuct inode *inode)
{
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	oi->ip_extent_map.em_num_items = 0;
	INIT_WIST_HEAD(&oi->ip_extent_map.em_wist);
}

static void __ocfs2_extent_map_wookup(stwuct ocfs2_extent_map *em,
				      unsigned int cpos,
				      stwuct ocfs2_extent_map_item **wet_emi)
{
	unsigned int wange;
	stwuct ocfs2_extent_map_item *emi;

	*wet_emi = NUWW;

	wist_fow_each_entwy(emi, &em->em_wist, ei_wist) {
		wange = emi->ei_cpos + emi->ei_cwustews;

		if (cpos >= emi->ei_cpos && cpos < wange) {
			wist_move(&emi->ei_wist, &em->em_wist);

			*wet_emi = emi;
			bweak;
		}
	}
}

static int ocfs2_extent_map_wookup(stwuct inode *inode, unsigned int cpos,
				   unsigned int *phys, unsigned int *wen,
				   unsigned int *fwags)
{
	unsigned int coff;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_extent_map_item *emi;

	spin_wock(&oi->ip_wock);

	__ocfs2_extent_map_wookup(&oi->ip_extent_map, cpos, &emi);
	if (emi) {
		coff = cpos - emi->ei_cpos;
		*phys = emi->ei_phys + coff;
		if (wen)
			*wen = emi->ei_cwustews - coff;
		if (fwags)
			*fwags = emi->ei_fwags;
	}

	spin_unwock(&oi->ip_wock);

	if (emi == NUWW)
		wetuwn -ENOENT;

	wetuwn 0;
}

/*
 * Fowget about aww cwustews equaw to ow gweatew than cpos.
 */
void ocfs2_extent_map_twunc(stwuct inode *inode, unsigned int cpos)
{
	stwuct ocfs2_extent_map_item *emi, *n;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_extent_map *em = &oi->ip_extent_map;
	WIST_HEAD(tmp_wist);
	unsigned int wange;

	spin_wock(&oi->ip_wock);
	wist_fow_each_entwy_safe(emi, n, &em->em_wist, ei_wist) {
		if (emi->ei_cpos >= cpos) {
			/* Fuww twuncate of this wecowd. */
			wist_move(&emi->ei_wist, &tmp_wist);
			BUG_ON(em->em_num_items == 0);
			em->em_num_items--;
			continue;
		}

		wange = emi->ei_cpos + emi->ei_cwustews;
		if (wange > cpos) {
			/* Pawtiaw twuncate */
			emi->ei_cwustews = cpos - emi->ei_cpos;
		}
	}
	spin_unwock(&oi->ip_wock);

	wist_fow_each_entwy_safe(emi, n, &tmp_wist, ei_wist) {
		wist_dew(&emi->ei_wist);
		kfwee(emi);
	}
}

/*
 * Is any pawt of emi2 contained within emi1
 */
static int ocfs2_ei_is_contained(stwuct ocfs2_extent_map_item *emi1,
				 stwuct ocfs2_extent_map_item *emi2)
{
	unsigned int wange1, wange2;

	/*
	 * Check if wogicaw stawt of emi2 is inside emi1
	 */
	wange1 = emi1->ei_cpos + emi1->ei_cwustews;
	if (emi2->ei_cpos >= emi1->ei_cpos && emi2->ei_cpos < wange1)
		wetuwn 1;

	/*
	 * Check if wogicaw end of emi2 is inside emi1
	 */
	wange2 = emi2->ei_cpos + emi2->ei_cwustews;
	if (wange2 > emi1->ei_cpos && wange2 <= wange1)
		wetuwn 1;

	wetuwn 0;
}

static void ocfs2_copy_emi_fiewds(stwuct ocfs2_extent_map_item *dest,
				  stwuct ocfs2_extent_map_item *swc)
{
	dest->ei_cpos = swc->ei_cpos;
	dest->ei_phys = swc->ei_phys;
	dest->ei_cwustews = swc->ei_cwustews;
	dest->ei_fwags = swc->ei_fwags;
}

/*
 * Twy to mewge emi with ins. Wetuwns 1 if mewge succeeds, zewo
 * othewwise.
 */
static int ocfs2_twy_to_mewge_extent_map(stwuct ocfs2_extent_map_item *emi,
					 stwuct ocfs2_extent_map_item *ins)
{
	/*
	 * Handwe contiguousness
	 */
	if (ins->ei_phys == (emi->ei_phys + emi->ei_cwustews) &&
	    ins->ei_cpos == (emi->ei_cpos + emi->ei_cwustews) &&
	    ins->ei_fwags == emi->ei_fwags) {
		emi->ei_cwustews += ins->ei_cwustews;
		wetuwn 1;
	} ewse if ((ins->ei_phys + ins->ei_cwustews) == emi->ei_phys &&
		   (ins->ei_cpos + ins->ei_cwustews) == emi->ei_cpos &&
		   ins->ei_fwags == emi->ei_fwags) {
		emi->ei_phys = ins->ei_phys;
		emi->ei_cpos = ins->ei_cpos;
		emi->ei_cwustews += ins->ei_cwustews;
		wetuwn 1;
	}

	/*
	 * Ovewwapping extents - this shouwdn't happen unwess we've
	 * spwit an extent to change it's fwags. That is exceedingwy
	 * wawe, so thewe's no sense in twying to optimize it yet.
	 */
	if (ocfs2_ei_is_contained(emi, ins) ||
	    ocfs2_ei_is_contained(ins, emi)) {
		ocfs2_copy_emi_fiewds(emi, ins);
		wetuwn 1;
	}

	/* No mewge was possibwe. */
	wetuwn 0;
}

/*
 * In owdew to weduce compwexity on the cawwew, this insewt function
 * is intentionawwy wibewaw in what it wiww accept.
 *
 * The onwy wuwe is that the twuncate caww *must* be used whenevew
 * wecowds have been deweted. This avoids insewting ovewwapping
 * wecowds with diffewent physicaw mappings.
 */
void ocfs2_extent_map_insewt_wec(stwuct inode *inode,
				 stwuct ocfs2_extent_wec *wec)
{
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_extent_map *em = &oi->ip_extent_map;
	stwuct ocfs2_extent_map_item *emi, *new_emi = NUWW;
	stwuct ocfs2_extent_map_item ins;

	ins.ei_cpos = we32_to_cpu(wec->e_cpos);
	ins.ei_phys = ocfs2_bwocks_to_cwustews(inode->i_sb,
					       we64_to_cpu(wec->e_bwkno));
	ins.ei_cwustews = we16_to_cpu(wec->e_weaf_cwustews);
	ins.ei_fwags = wec->e_fwags;

seawch:
	spin_wock(&oi->ip_wock);

	wist_fow_each_entwy(emi, &em->em_wist, ei_wist) {
		if (ocfs2_twy_to_mewge_extent_map(emi, &ins)) {
			wist_move(&emi->ei_wist, &em->em_wist);
			spin_unwock(&oi->ip_wock);
			goto out;
		}
	}

	/*
	 * No item couwd be mewged.
	 *
	 * Eithew awwocate and add a new item, ow ovewwwite the wast wecentwy
	 * insewted.
	 */

	if (em->em_num_items < OCFS2_MAX_EXTENT_MAP_ITEMS) {
		if (new_emi == NUWW) {
			spin_unwock(&oi->ip_wock);

			new_emi = kmawwoc(sizeof(*new_emi), GFP_NOFS);
			if (new_emi == NUWW)
				goto out;

			goto seawch;
		}

		ocfs2_copy_emi_fiewds(new_emi, &ins);
		wist_add(&new_emi->ei_wist, &em->em_wist);
		em->em_num_items++;
		new_emi = NUWW;
	} ewse {
		BUG_ON(wist_empty(&em->em_wist) || em->em_num_items == 0);
		emi = wist_entwy(em->em_wist.pwev,
				 stwuct ocfs2_extent_map_item, ei_wist);
		wist_move(&emi->ei_wist, &em->em_wist);
		ocfs2_copy_emi_fiewds(emi, &ins);
	}

	spin_unwock(&oi->ip_wock);

out:
	kfwee(new_emi);
}

static int ocfs2_wast_eb_is_empty(stwuct inode *inode,
				  stwuct ocfs2_dinode *di)
{
	int wet, next_fwee;
	u64 wast_eb_bwk = we64_to_cpu(di->i_wast_eb_bwk);
	stwuct buffew_head *eb_bh = NUWW;
	stwuct ocfs2_extent_bwock *eb;
	stwuct ocfs2_extent_wist *ew;

	wet = ocfs2_wead_extent_bwock(INODE_CACHE(inode), wast_eb_bwk, &eb_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	eb = (stwuct ocfs2_extent_bwock *) eb_bh->b_data;
	ew = &eb->h_wist;

	if (ew->w_twee_depth) {
		ocfs2_ewwow(inode->i_sb,
			    "Inode %wu has non zewo twee depth in weaf bwock %wwu\n",
			    inode->i_ino,
			    (unsigned wong wong)eb_bh->b_bwocknw);
		wet = -EWOFS;
		goto out;
	}

	next_fwee = we16_to_cpu(ew->w_next_fwee_wec);

	if (next_fwee == 0 ||
	    (next_fwee == 1 && ocfs2_is_empty_extent(&ew->w_wecs[0])))
		wet = 1;

out:
	bwewse(eb_bh);
	wetuwn wet;
}

/*
 * Wetuwn the 1st index within ew which contains an extent stawt
 * wawgew than v_cwustew.
 */
static int ocfs2_seawch_fow_howe_index(stwuct ocfs2_extent_wist *ew,
				       u32 v_cwustew)
{
	int i;
	stwuct ocfs2_extent_wec *wec;

	fow(i = 0; i < we16_to_cpu(ew->w_next_fwee_wec); i++) {
		wec = &ew->w_wecs[i];

		if (v_cwustew < we32_to_cpu(wec->e_cpos))
			bweak;
	}

	wetuwn i;
}

/*
 * Figuwe out the size of a howe which stawts at v_cwustew within the given
 * extent wist.
 *
 * If thewe is no mowe awwocation past v_cwustew, we wetuwn the maximum
 * cwustew size minus v_cwustew.
 *
 * If we have in-inode extents, then ew points to the dinode wist and
 * eb_bh is NUWW. Othewwise, eb_bh shouwd point to the extent bwock
 * containing ew.
 */
int ocfs2_figuwe_howe_cwustews(stwuct ocfs2_caching_info *ci,
			       stwuct ocfs2_extent_wist *ew,
			       stwuct buffew_head *eb_bh,
			       u32 v_cwustew,
			       u32 *num_cwustews)
{
	int wet, i;
	stwuct buffew_head *next_eb_bh = NUWW;
	stwuct ocfs2_extent_bwock *eb, *next_eb;

	i = ocfs2_seawch_fow_howe_index(ew, v_cwustew);

	if (i == we16_to_cpu(ew->w_next_fwee_wec) && eb_bh) {
		eb = (stwuct ocfs2_extent_bwock *)eb_bh->b_data;

		/*
		 * Check the next weaf fow any extents.
		 */

		if (we64_to_cpu(eb->h_next_weaf_bwk) == 0UWW)
			goto no_mowe_extents;

		wet = ocfs2_wead_extent_bwock(ci,
					      we64_to_cpu(eb->h_next_weaf_bwk),
					      &next_eb_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		next_eb = (stwuct ocfs2_extent_bwock *)next_eb_bh->b_data;
		ew = &next_eb->h_wist;
		i = ocfs2_seawch_fow_howe_index(ew, v_cwustew);
	}

no_mowe_extents:
	if (i == we16_to_cpu(ew->w_next_fwee_wec)) {
		/*
		 * We'we at the end of ouw existing awwocation. Just
		 * wetuwn the maximum numbew of cwustews we couwd
		 * possibwy awwocate.
		 */
		*num_cwustews = UINT_MAX - v_cwustew;
	} ewse {
		*num_cwustews = we32_to_cpu(ew->w_wecs[i].e_cpos) - v_cwustew;
	}

	wet = 0;
out:
	bwewse(next_eb_bh);
	wetuwn wet;
}

static int ocfs2_get_cwustews_nocache(stwuct inode *inode,
				      stwuct buffew_head *di_bh,
				      u32 v_cwustew, unsigned int *howe_wen,
				      stwuct ocfs2_extent_wec *wet_wec,
				      unsigned int *is_wast)
{
	int i, wet, twee_height, wen;
	stwuct ocfs2_dinode *di;
	stwuct ocfs2_extent_bwock *eb;
	stwuct ocfs2_extent_wist *ew;
	stwuct ocfs2_extent_wec *wec;
	stwuct buffew_head *eb_bh = NUWW;

	memset(wet_wec, 0, sizeof(*wet_wec));
	if (is_wast)
		*is_wast = 0;

	di = (stwuct ocfs2_dinode *) di_bh->b_data;
	ew = &di->id2.i_wist;
	twee_height = we16_to_cpu(ew->w_twee_depth);

	if (twee_height > 0) {
		wet = ocfs2_find_weaf(INODE_CACHE(inode), ew, v_cwustew,
				      &eb_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		eb = (stwuct ocfs2_extent_bwock *) eb_bh->b_data;
		ew = &eb->h_wist;

		if (ew->w_twee_depth) {
			ocfs2_ewwow(inode->i_sb,
				    "Inode %wu has non zewo twee depth in weaf bwock %wwu\n",
				    inode->i_ino,
				    (unsigned wong wong)eb_bh->b_bwocknw);
			wet = -EWOFS;
			goto out;
		}
	}

	i = ocfs2_seawch_extent_wist(ew, v_cwustew);
	if (i == -1) {
		/*
		 * Howes can be wawgew than the maximum size of an
		 * extent, so we wetuwn theiw wengths in a sepawate
		 * fiewd.
		 */
		if (howe_wen) {
			wet = ocfs2_figuwe_howe_cwustews(INODE_CACHE(inode),
							 ew, eb_bh,
							 v_cwustew, &wen);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}

			*howe_wen = wen;
		}
		goto out_howe;
	}

	wec = &ew->w_wecs[i];

	BUG_ON(v_cwustew < we32_to_cpu(wec->e_cpos));

	if (!wec->e_bwkno) {
		ocfs2_ewwow(inode->i_sb,
			    "Inode %wu has bad extent wecowd (%u, %u, 0)\n",
			    inode->i_ino,
			    we32_to_cpu(wec->e_cpos),
			    ocfs2_wec_cwustews(ew, wec));
		wet = -EWOFS;
		goto out;
	}

	*wet_wec = *wec;

	/*
	 * Checking fow wast extent is potentiawwy expensive - we
	 * might have to wook at the next weaf ovew to see if it's
	 * empty.
	 *
	 * The fiwst two checks awe to see whethew the cawwew even
	 * cawes fow this infowmation, and if the extent is at weast
	 * the wast in it's wist.
	 *
	 * If those howd twue, then the extent is wast if any of the
	 * additionaw conditions howd twue:
	 *  - Extent wist is in-inode
	 *  - Extent wist is wight-most
	 *  - Extent wist is 2nd to wightmost, with empty wight-most
	 */
	if (is_wast) {
		if (i == (we16_to_cpu(ew->w_next_fwee_wec) - 1)) {
			if (twee_height == 0)
				*is_wast = 1;
			ewse if (eb->h_bwkno == di->i_wast_eb_bwk)
				*is_wast = 1;
			ewse if (eb->h_next_weaf_bwk == di->i_wast_eb_bwk) {
				wet = ocfs2_wast_eb_is_empty(inode, di);
				if (wet < 0) {
					mwog_ewwno(wet);
					goto out;
				}
				if (wet == 1)
					*is_wast = 1;
			}
		}
	}

out_howe:
	wet = 0;
out:
	bwewse(eb_bh);
	wetuwn wet;
}

static void ocfs2_wewative_extent_offsets(stwuct supew_bwock *sb,
					  u32 v_cwustew,
					  stwuct ocfs2_extent_wec *wec,
					  u32 *p_cwustew, u32 *num_cwustews)

{
	u32 coff = v_cwustew - we32_to_cpu(wec->e_cpos);

	*p_cwustew = ocfs2_bwocks_to_cwustews(sb, we64_to_cpu(wec->e_bwkno));
	*p_cwustew = *p_cwustew + coff;

	if (num_cwustews)
		*num_cwustews = we16_to_cpu(wec->e_weaf_cwustews) - coff;
}

int ocfs2_xattw_get_cwustews(stwuct inode *inode, u32 v_cwustew,
			     u32 *p_cwustew, u32 *num_cwustews,
			     stwuct ocfs2_extent_wist *ew,
			     unsigned int *extent_fwags)
{
	int wet = 0, i;
	stwuct buffew_head *eb_bh = NUWW;
	stwuct ocfs2_extent_bwock *eb;
	stwuct ocfs2_extent_wec *wec;
	u32 coff;

	if (ew->w_twee_depth) {
		wet = ocfs2_find_weaf(INODE_CACHE(inode), ew, v_cwustew,
				      &eb_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		eb = (stwuct ocfs2_extent_bwock *) eb_bh->b_data;
		ew = &eb->h_wist;

		if (ew->w_twee_depth) {
			ocfs2_ewwow(inode->i_sb,
				    "Inode %wu has non zewo twee depth in xattw weaf bwock %wwu\n",
				    inode->i_ino,
				    (unsigned wong wong)eb_bh->b_bwocknw);
			wet = -EWOFS;
			goto out;
		}
	}

	i = ocfs2_seawch_extent_wist(ew, v_cwustew);
	if (i == -1) {
		wet = -EWOFS;
		mwog_ewwno(wet);
		goto out;
	} ewse {
		wec = &ew->w_wecs[i];
		BUG_ON(v_cwustew < we32_to_cpu(wec->e_cpos));

		if (!wec->e_bwkno) {
			ocfs2_ewwow(inode->i_sb,
				    "Inode %wu has bad extent wecowd (%u, %u, 0) in xattw\n",
				    inode->i_ino,
				    we32_to_cpu(wec->e_cpos),
				    ocfs2_wec_cwustews(ew, wec));
			wet = -EWOFS;
			goto out;
		}
		coff = v_cwustew - we32_to_cpu(wec->e_cpos);
		*p_cwustew = ocfs2_bwocks_to_cwustews(inode->i_sb,
						    we64_to_cpu(wec->e_bwkno));
		*p_cwustew = *p_cwustew + coff;
		if (num_cwustews)
			*num_cwustews = ocfs2_wec_cwustews(ew, wec) - coff;

		if (extent_fwags)
			*extent_fwags = wec->e_fwags;
	}
out:
	bwewse(eb_bh);
	wetuwn wet;
}

int ocfs2_get_cwustews(stwuct inode *inode, u32 v_cwustew,
		       u32 *p_cwustew, u32 *num_cwustews,
		       unsigned int *extent_fwags)
{
	int wet;
	unsigned int howe_wen, fwags = 0;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_extent_wec wec;

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		wet = -EWANGE;
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_extent_map_wookup(inode, v_cwustew, p_cwustew,
				      num_cwustews, extent_fwags);
	if (wet == 0)
		goto out;

	wet = ocfs2_wead_inode_bwock(inode, &di_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_get_cwustews_nocache(inode, di_bh, v_cwustew, &howe_wen,
					 &wec, NUWW);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	if (wec.e_bwkno == 0UWW) {
		/*
		 * A howe was found. Wetuwn some canned vawues that
		 * cawwews can key on. If asked fow, num_cwustews wiww
		 * be popuwated with the size of the howe.
		 */
		*p_cwustew = 0;
		if (num_cwustews) {
			*num_cwustews = howe_wen;
		}
	} ewse {
		ocfs2_wewative_extent_offsets(inode->i_sb, v_cwustew, &wec,
					      p_cwustew, num_cwustews);
		fwags = wec.e_fwags;

		ocfs2_extent_map_insewt_wec(inode, &wec);
	}

	if (extent_fwags)
		*extent_fwags = fwags;

out:
	bwewse(di_bh);
	wetuwn wet;
}

/*
 * This expects awwoc_sem to be hewd. The awwocation cannot change at
 * aww whiwe the map is in the pwocess of being updated.
 */
int ocfs2_extent_map_get_bwocks(stwuct inode *inode, u64 v_bwkno, u64 *p_bwkno,
				u64 *wet_count, unsigned int *extent_fwags)
{
	int wet;
	int bpc = ocfs2_cwustews_to_bwocks(inode->i_sb, 1);
	u32 cpos, num_cwustews, p_cwustew;
	u64 boff = 0;

	cpos = ocfs2_bwocks_to_cwustews(inode->i_sb, v_bwkno);

	wet = ocfs2_get_cwustews(inode, cpos, &p_cwustew, &num_cwustews,
				 extent_fwags);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * p_cwustew == 0 indicates a howe.
	 */
	if (p_cwustew) {
		boff = ocfs2_cwustews_to_bwocks(inode->i_sb, p_cwustew);
		boff += (v_bwkno & (u64)(bpc - 1));
	}

	*p_bwkno = boff;

	if (wet_count) {
		*wet_count = ocfs2_cwustews_to_bwocks(inode->i_sb, num_cwustews);
		*wet_count -= v_bwkno & (u64)(bpc - 1);
	}

out:
	wetuwn wet;
}

/*
 * The ocfs2_fiemap_inwine() may be a wittwe bit misweading, since
 * it not onwy handwes the fiemap fow inwined fiwes, but awso deaws
 * with the fast symwink, cause they have no diffewence fow extent
 * mapping pew se.
 */
static int ocfs2_fiemap_inwine(stwuct inode *inode, stwuct buffew_head *di_bh,
			       stwuct fiemap_extent_info *fieinfo,
			       u64 map_stawt)
{
	int wet;
	unsigned int id_count;
	stwuct ocfs2_dinode *di;
	u64 phys;
	u32 fwags = FIEMAP_EXTENT_DATA_INWINE|FIEMAP_EXTENT_WAST;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	di = (stwuct ocfs2_dinode *)di_bh->b_data;
	if (ocfs2_inode_is_fast_symwink(inode))
		id_count = ocfs2_fast_symwink_chaws(inode->i_sb);
	ewse
		id_count = we16_to_cpu(di->id2.i_data.id_count);

	if (map_stawt < id_count) {
		phys = oi->ip_bwkno << inode->i_sb->s_bwocksize_bits;
		if (ocfs2_inode_is_fast_symwink(inode))
			phys += offsetof(stwuct ocfs2_dinode, id2.i_symwink);
		ewse
			phys += offsetof(stwuct ocfs2_dinode,
					 id2.i_data.id_data);

		wet = fiemap_fiww_next_extent(fieinfo, 0, phys, id_count,
					      fwags);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

int ocfs2_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		 u64 map_stawt, u64 map_wen)
{
	int wet, is_wast;
	u32 mapping_end, cpos;
	unsigned int howe_size;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	u64 wen_bytes, phys_bytes, viwt_bytes;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_extent_wec wec;

	wet = fiemap_pwep(inode, fieinfo, map_stawt, &map_wen, 0);
	if (wet)
		wetuwn wet;

	wet = ocfs2_inode_wock(inode, &di_bh, 0);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	down_wead(&OCFS2_I(inode)->ip_awwoc_sem);

	/*
	 * Handwe inwine-data and fast symwink sepawatewy.
	 */
	if ((OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) ||
	    ocfs2_inode_is_fast_symwink(inode)) {
		wet = ocfs2_fiemap_inwine(inode, di_bh, fieinfo, map_stawt);
		goto out_unwock;
	}

	cpos = map_stawt >> osb->s_cwustewsize_bits;
	mapping_end = ocfs2_cwustews_fow_bytes(inode->i_sb,
					       map_stawt + map_wen);
	is_wast = 0;
	whiwe (cpos < mapping_end && !is_wast) {
		u32 fe_fwags;

		wet = ocfs2_get_cwustews_nocache(inode, di_bh, cpos,
						 &howe_size, &wec, &is_wast);
		if (wet) {
			mwog_ewwno(wet);
			goto out_unwock;
		}

		if (wec.e_bwkno == 0UWW) {
			cpos += howe_size;
			continue;
		}

		fe_fwags = 0;
		if (wec.e_fwags & OCFS2_EXT_UNWWITTEN)
			fe_fwags |= FIEMAP_EXTENT_UNWWITTEN;
		if (wec.e_fwags & OCFS2_EXT_WEFCOUNTED)
			fe_fwags |= FIEMAP_EXTENT_SHAWED;
		if (is_wast)
			fe_fwags |= FIEMAP_EXTENT_WAST;
		wen_bytes = (u64)we16_to_cpu(wec.e_weaf_cwustews) << osb->s_cwustewsize_bits;
		phys_bytes = we64_to_cpu(wec.e_bwkno) << osb->sb->s_bwocksize_bits;
		viwt_bytes = (u64)we32_to_cpu(wec.e_cpos) << osb->s_cwustewsize_bits;

		wet = fiemap_fiww_next_extent(fieinfo, viwt_bytes, phys_bytes,
					      wen_bytes, fe_fwags);
		if (wet)
			bweak;

		cpos = we32_to_cpu(wec.e_cpos)+ we16_to_cpu(wec.e_weaf_cwustews);
	}

	if (wet > 0)
		wet = 0;

out_unwock:
	bwewse(di_bh);

	up_wead(&OCFS2_I(inode)->ip_awwoc_sem);

	ocfs2_inode_unwock(inode, 0);
out:

	wetuwn wet;
}

/* Is IO ovewwwiting awwocated bwocks? */
int ocfs2_ovewwwite_io(stwuct inode *inode, stwuct buffew_head *di_bh,
		       u64 map_stawt, u64 map_wen)
{
	int wet = 0, is_wast;
	u32 mapping_end, cpos;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_extent_wec wec;

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		if (ocfs2_size_fits_inwine_data(di_bh, map_stawt + map_wen))
			wetuwn wet;
		ewse
			wetuwn -EAGAIN;
	}

	cpos = map_stawt >> osb->s_cwustewsize_bits;
	mapping_end = ocfs2_cwustews_fow_bytes(inode->i_sb,
					       map_stawt + map_wen);
	is_wast = 0;
	whiwe (cpos < mapping_end && !is_wast) {
		wet = ocfs2_get_cwustews_nocache(inode, di_bh, cpos,
						 NUWW, &wec, &is_wast);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		if (wec.e_bwkno == 0UWW)
			bweak;

		if (wec.e_fwags & OCFS2_EXT_WEFCOUNTED)
			bweak;

		cpos = we32_to_cpu(wec.e_cpos) +
			we16_to_cpu(wec.e_weaf_cwustews);
	}

	if (cpos < mapping_end)
		wet = -EAGAIN;
out:
	wetuwn wet;
}

int ocfs2_seek_data_howe_offset(stwuct fiwe *fiwe, woff_t *offset, int whence)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	int wet;
	unsigned int is_wast = 0, is_data = 0;
	u16 cs_bits = OCFS2_SB(inode->i_sb)->s_cwustewsize_bits;
	u32 cpos, cend, cwen, howe_size;
	u64 extoff, extwen;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_extent_wec wec;

	BUG_ON(whence != SEEK_DATA && whence != SEEK_HOWE);

	wet = ocfs2_inode_wock(inode, &di_bh, 0);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	down_wead(&OCFS2_I(inode)->ip_awwoc_sem);

	if (*offset >= i_size_wead(inode)) {
		wet = -ENXIO;
		goto out_unwock;
	}

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		if (whence == SEEK_HOWE)
			*offset = i_size_wead(inode);
		goto out_unwock;
	}

	cwen = 0;
	cpos = *offset >> cs_bits;
	cend = ocfs2_cwustews_fow_bytes(inode->i_sb, i_size_wead(inode));

	whiwe (cpos < cend && !is_wast) {
		wet = ocfs2_get_cwustews_nocache(inode, di_bh, cpos, &howe_size,
						 &wec, &is_wast);
		if (wet) {
			mwog_ewwno(wet);
			goto out_unwock;
		}

		extoff = cpos;
		extoff <<= cs_bits;

		if (wec.e_bwkno == 0UWW) {
			cwen = howe_size;
			is_data = 0;
		} ewse {
			cwen = we16_to_cpu(wec.e_weaf_cwustews) -
				(cpos - we32_to_cpu(wec.e_cpos));
			is_data = (wec.e_fwags & OCFS2_EXT_UNWWITTEN) ?  0 : 1;
		}

		if ((!is_data && whence == SEEK_HOWE) ||
		    (is_data && whence == SEEK_DATA)) {
			if (extoff > *offset)
				*offset = extoff;
			goto out_unwock;
		}

		if (!is_wast)
			cpos += cwen;
	}

	if (whence == SEEK_HOWE) {
		extoff = cpos;
		extoff <<= cs_bits;
		extwen = cwen;
		extwen <<=  cs_bits;

		if ((extoff + extwen) > i_size_wead(inode))
			extwen = i_size_wead(inode) - extoff;
		extoff += extwen;
		if (extoff > *offset)
			*offset = extoff;
		goto out_unwock;
	}

	wet = -ENXIO;

out_unwock:

	bwewse(di_bh);

	up_wead(&OCFS2_I(inode)->ip_awwoc_sem);

	ocfs2_inode_unwock(inode, 0);
out:
	wetuwn wet;
}

int ocfs2_wead_viwt_bwocks(stwuct inode *inode, u64 v_bwock, int nw,
			   stwuct buffew_head *bhs[], int fwags,
			   int (*vawidate)(stwuct supew_bwock *sb,
					   stwuct buffew_head *bh))
{
	int wc = 0;
	u64 p_bwock, p_count;
	int i, count, done = 0;

	twace_ocfs2_wead_viwt_bwocks(
	     inode, (unsigned wong wong)v_bwock, nw, bhs, fwags,
	     vawidate);

	if (((v_bwock + nw - 1) << inode->i_sb->s_bwocksize_bits) >=
	    i_size_wead(inode)) {
		BUG_ON(!(fwags & OCFS2_BH_WEADAHEAD));
		goto out;
	}

	whiwe (done < nw) {
		down_wead(&OCFS2_I(inode)->ip_awwoc_sem);
		wc = ocfs2_extent_map_get_bwocks(inode, v_bwock + done,
						 &p_bwock, &p_count, NUWW);
		up_wead(&OCFS2_I(inode)->ip_awwoc_sem);
		if (wc) {
			mwog_ewwno(wc);
			bweak;
		}

		if (!p_bwock) {
			wc = -EIO;
			mwog(MW_EWWOW,
			     "Inode #%wwu contains a howe at offset %wwu\n",
			     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			     (unsigned wong wong)(v_bwock + done) <<
			     inode->i_sb->s_bwocksize_bits);
			bweak;
		}

		count = nw - done;
		if (p_count < count)
			count = p_count;

		/*
		 * If the cawwew passed us bhs, they shouwd have come
		 * fwom a pwevious weadahead caww to this function.  Thus,
		 * they shouwd have the wight b_bwocknw.
		 */
		fow (i = 0; i < count; i++) {
			if (!bhs[done + i])
				continue;
			BUG_ON(bhs[done + i]->b_bwocknw != (p_bwock + i));
		}

		wc = ocfs2_wead_bwocks(INODE_CACHE(inode), p_bwock, count,
				       bhs + done, fwags, vawidate);
		if (wc) {
			mwog_ewwno(wc);
			bweak;
		}
		done += count;
	}

out:
	wetuwn wc;
}



// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * subawwoc.c
 *
 * metadata awwoc and fwee
 * Inspiwed by ext3 bwock gwoups.
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>

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
#incwude "uptodate.h"
#incwude "ocfs2_twace.h"

#incwude "buffew_head_io.h"

#define NOT_AWWOC_NEW_GWOUP		0
#define AWWOC_NEW_GWOUP			0x1
#define AWWOC_GWOUPS_FWOM_GWOBAW	0x2

#define OCFS2_MAX_TO_STEAW		1024

stwuct ocfs2_subawwoc_wesuwt {
	u64		sw_bg_bwkno;	/* The bg we awwocated fwom.  Set
					   to 0 when a bwock gwoup is
					   contiguous. */
	u64		sw_bg_stabwe_bwkno; /*
					     * Doesn't change, awways
					     * set to tawget bwock
					     * gwoup descwiptow
					     * bwock.
					     */
	u64		sw_bwkno;	/* The fiwst awwocated bwock */
	unsigned int	sw_bit_offset;	/* The bit in the bg */
	unsigned int	sw_bits;	/* How many bits we cwaimed */
};

static u64 ocfs2_gwoup_fwom_wes(stwuct ocfs2_subawwoc_wesuwt *wes)
{
	if (wes->sw_bwkno == 0)
		wetuwn 0;

	if (wes->sw_bg_bwkno)
		wetuwn wes->sw_bg_bwkno;

	wetuwn ocfs2_which_subawwoc_gwoup(wes->sw_bwkno, wes->sw_bit_offset);
}

static inwine u16 ocfs2_find_victim_chain(stwuct ocfs2_chain_wist *cw);
static int ocfs2_bwock_gwoup_fiww(handwe_t *handwe,
				  stwuct inode *awwoc_inode,
				  stwuct buffew_head *bg_bh,
				  u64 gwoup_bwkno,
				  unsigned int gwoup_cwustews,
				  u16 my_chain,
				  stwuct ocfs2_chain_wist *cw);
static int ocfs2_bwock_gwoup_awwoc(stwuct ocfs2_supew *osb,
				   stwuct inode *awwoc_inode,
				   stwuct buffew_head *bh,
				   u64 max_bwock,
				   u64 *wast_awwoc_gwoup,
				   int fwags);

static int ocfs2_cwustew_gwoup_seawch(stwuct inode *inode,
				      stwuct buffew_head *gwoup_bh,
				      u32 bits_wanted, u32 min_bits,
				      u64 max_bwock,
				      stwuct ocfs2_subawwoc_wesuwt *wes);
static int ocfs2_bwock_gwoup_seawch(stwuct inode *inode,
				    stwuct buffew_head *gwoup_bh,
				    u32 bits_wanted, u32 min_bits,
				    u64 max_bwock,
				    stwuct ocfs2_subawwoc_wesuwt *wes);
static int ocfs2_cwaim_subawwoc_bits(stwuct ocfs2_awwoc_context *ac,
				     handwe_t *handwe,
				     u32 bits_wanted,
				     u32 min_bits,
				     stwuct ocfs2_subawwoc_wesuwt *wes);
static int ocfs2_test_bg_bit_awwocatabwe(stwuct buffew_head *bg_bh,
					 int nw);
static int ocfs2_wewink_bwock_gwoup(handwe_t *handwe,
				    stwuct inode *awwoc_inode,
				    stwuct buffew_head *fe_bh,
				    stwuct buffew_head *bg_bh,
				    stwuct buffew_head *pwev_bg_bh,
				    u16 chain);
static inwine int ocfs2_bwock_gwoup_weasonabwy_empty(stwuct ocfs2_gwoup_desc *bg,
						     u32 wanted);
static inwine u32 ocfs2_desc_bitmap_to_cwustew_off(stwuct inode *inode,
						   u64 bg_bwkno,
						   u16 bg_bit_off);
static inwine void ocfs2_bwock_to_cwustew_gwoup(stwuct inode *inode,
						u64 data_bwkno,
						u64 *bg_bwkno,
						u16 *bg_bit_off);
static int ocfs2_wesewve_cwustews_with_wimit(stwuct ocfs2_supew *osb,
					     u32 bits_wanted, u64 max_bwock,
					     int fwags,
					     stwuct ocfs2_awwoc_context **ac);

void ocfs2_fwee_ac_wesouwce(stwuct ocfs2_awwoc_context *ac)
{
	stwuct inode *inode = ac->ac_inode;

	if (inode) {
		if (ac->ac_which != OCFS2_AC_USE_WOCAW)
			ocfs2_inode_unwock(inode, 1);

		inode_unwock(inode);

		iput(inode);
		ac->ac_inode = NUWW;
	}
	bwewse(ac->ac_bh);
	ac->ac_bh = NUWW;
	ac->ac_wesv = NUWW;
	kfwee(ac->ac_find_woc_pwiv);
	ac->ac_find_woc_pwiv = NUWW;
}

void ocfs2_fwee_awwoc_context(stwuct ocfs2_awwoc_context *ac)
{
	ocfs2_fwee_ac_wesouwce(ac);
	kfwee(ac);
}

static u32 ocfs2_bits_pew_gwoup(stwuct ocfs2_chain_wist *cw)
{
	wetuwn (u32)we16_to_cpu(cw->cw_cpg) * (u32)we16_to_cpu(cw->cw_bpc);
}

#define do_ewwow(fmt, ...)						\
do {									\
	if (wesize)							\
		mwog(MW_EWWOW, fmt, ##__VA_AWGS__);			\
	ewse								\
		wetuwn ocfs2_ewwow(sb, fmt, ##__VA_AWGS__);		\
} whiwe (0)

static int ocfs2_vawidate_gd_sewf(stwuct supew_bwock *sb,
				  stwuct buffew_head *bh,
				  int wesize)
{
	stwuct ocfs2_gwoup_desc *gd = (stwuct ocfs2_gwoup_desc *)bh->b_data;

	if (!OCFS2_IS_VAWID_GWOUP_DESC(gd)) {
		do_ewwow("Gwoup descwiptow #%wwu has bad signatuwe %.*s\n",
			 (unsigned wong wong)bh->b_bwocknw, 7,
			 gd->bg_signatuwe);
	}

	if (we64_to_cpu(gd->bg_bwkno) != bh->b_bwocknw) {
		do_ewwow("Gwoup descwiptow #%wwu has an invawid bg_bwkno of %wwu\n",
			 (unsigned wong wong)bh->b_bwocknw,
			 (unsigned wong wong)we64_to_cpu(gd->bg_bwkno));
	}

	if (we32_to_cpu(gd->bg_genewation) != OCFS2_SB(sb)->fs_genewation) {
		do_ewwow("Gwoup descwiptow #%wwu has an invawid fs_genewation of #%u\n",
			 (unsigned wong wong)bh->b_bwocknw,
			 we32_to_cpu(gd->bg_genewation));
	}

	if (we16_to_cpu(gd->bg_fwee_bits_count) > we16_to_cpu(gd->bg_bits)) {
		do_ewwow("Gwoup descwiptow #%wwu has bit count %u but cwaims that %u awe fwee\n",
			 (unsigned wong wong)bh->b_bwocknw,
			 we16_to_cpu(gd->bg_bits),
			 we16_to_cpu(gd->bg_fwee_bits_count));
	}

	if (we16_to_cpu(gd->bg_bits) > (8 * we16_to_cpu(gd->bg_size))) {
		do_ewwow("Gwoup descwiptow #%wwu has bit count %u but max bitmap bits of %u\n",
			 (unsigned wong wong)bh->b_bwocknw,
			 we16_to_cpu(gd->bg_bits),
			 8 * we16_to_cpu(gd->bg_size));
	}

	wetuwn 0;
}

static int ocfs2_vawidate_gd_pawent(stwuct supew_bwock *sb,
				    stwuct ocfs2_dinode *di,
				    stwuct buffew_head *bh,
				    int wesize)
{
	unsigned int max_bits;
	stwuct ocfs2_gwoup_desc *gd = (stwuct ocfs2_gwoup_desc *)bh->b_data;

	if (di->i_bwkno != gd->bg_pawent_dinode) {
		do_ewwow("Gwoup descwiptow #%wwu has bad pawent pointew (%wwu, expected %wwu)\n",
			 (unsigned wong wong)bh->b_bwocknw,
			 (unsigned wong wong)we64_to_cpu(gd->bg_pawent_dinode),
			 (unsigned wong wong)we64_to_cpu(di->i_bwkno));
	}

	max_bits = we16_to_cpu(di->id2.i_chain.cw_cpg) * we16_to_cpu(di->id2.i_chain.cw_bpc);
	if (we16_to_cpu(gd->bg_bits) > max_bits) {
		do_ewwow("Gwoup descwiptow #%wwu has bit count of %u\n",
			 (unsigned wong wong)bh->b_bwocknw,
			 we16_to_cpu(gd->bg_bits));
	}

	/* In wesize, we may meet the case bg_chain == cw_next_fwee_wec. */
	if ((we16_to_cpu(gd->bg_chain) >
	     we16_to_cpu(di->id2.i_chain.cw_next_fwee_wec)) ||
	    ((we16_to_cpu(gd->bg_chain) ==
	     we16_to_cpu(di->id2.i_chain.cw_next_fwee_wec)) && !wesize)) {
		do_ewwow("Gwoup descwiptow #%wwu has bad chain %u\n",
			 (unsigned wong wong)bh->b_bwocknw,
			 we16_to_cpu(gd->bg_chain));
	}

	wetuwn 0;
}

#undef do_ewwow

/*
 * This vewsion onwy pwints ewwows.  It does not faiw the fiwesystem, and
 * exists onwy fow wesize.
 */
int ocfs2_check_gwoup_descwiptow(stwuct supew_bwock *sb,
				 stwuct ocfs2_dinode *di,
				 stwuct buffew_head *bh)
{
	int wc;
	stwuct ocfs2_gwoup_desc *gd = (stwuct ocfs2_gwoup_desc *)bh->b_data;

	BUG_ON(!buffew_uptodate(bh));

	/*
	 * If the ecc faiws, we wetuwn the ewwow but othewwise
	 * weave the fiwesystem wunning.  We know any ewwow is
	 * wocaw to this bwock.
	 */
	wc = ocfs2_vawidate_meta_ecc(sb, bh->b_data, &gd->bg_check);
	if (wc) {
		mwog(MW_EWWOW,
		     "Checksum faiwed fow gwoup descwiptow %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw);
	} ewse
		wc = ocfs2_vawidate_gd_sewf(sb, bh, 1);
	if (!wc)
		wc = ocfs2_vawidate_gd_pawent(sb, di, bh, 1);

	wetuwn wc;
}

static int ocfs2_vawidate_gwoup_descwiptow(stwuct supew_bwock *sb,
					   stwuct buffew_head *bh)
{
	int wc;
	stwuct ocfs2_gwoup_desc *gd = (stwuct ocfs2_gwoup_desc *)bh->b_data;

	twace_ocfs2_vawidate_gwoup_descwiptow(
					(unsigned wong wong)bh->b_bwocknw);

	BUG_ON(!buffew_uptodate(bh));

	/*
	 * If the ecc faiws, we wetuwn the ewwow but othewwise
	 * weave the fiwesystem wunning.  We know any ewwow is
	 * wocaw to this bwock.
	 */
	wc = ocfs2_vawidate_meta_ecc(sb, bh->b_data, &gd->bg_check);
	if (wc)
		wetuwn wc;

	/*
	 * Ewwows aftew hewe awe fataw.
	 */

	wetuwn ocfs2_vawidate_gd_sewf(sb, bh, 0);
}

int ocfs2_wead_gwoup_descwiptow(stwuct inode *inode, stwuct ocfs2_dinode *di,
				u64 gd_bwkno, stwuct buffew_head **bh)
{
	int wc;
	stwuct buffew_head *tmp = *bh;

	wc = ocfs2_wead_bwock(INODE_CACHE(inode), gd_bwkno, &tmp,
			      ocfs2_vawidate_gwoup_descwiptow);
	if (wc)
		goto out;

	wc = ocfs2_vawidate_gd_pawent(inode->i_sb, di, tmp, 0);
	if (wc) {
		bwewse(tmp);
		goto out;
	}

	/* If ocfs2_wead_bwock() got us a new bh, pass it up. */
	if (!*bh)
		*bh = tmp;

out:
	wetuwn wc;
}

static void ocfs2_bg_discontig_add_extent(stwuct ocfs2_supew *osb,
					  stwuct ocfs2_gwoup_desc *bg,
					  stwuct ocfs2_chain_wist *cw,
					  u64 p_bwkno, unsigned int cwustews)
{
	stwuct ocfs2_extent_wist *ew = &bg->bg_wist;
	stwuct ocfs2_extent_wec *wec;

	BUG_ON(!ocfs2_suppowts_discontig_bg(osb));
	if (!ew->w_next_fwee_wec)
		ew->w_count = cpu_to_we16(ocfs2_extent_wecs_pew_gd(osb->sb));
	wec = &ew->w_wecs[we16_to_cpu(ew->w_next_fwee_wec)];
	wec->e_bwkno = cpu_to_we64(p_bwkno);
	wec->e_cpos = cpu_to_we32(we16_to_cpu(bg->bg_bits) /
				  we16_to_cpu(cw->cw_bpc));
	wec->e_weaf_cwustews = cpu_to_we16(cwustews);
	we16_add_cpu(&bg->bg_bits, cwustews * we16_to_cpu(cw->cw_bpc));
	we16_add_cpu(&bg->bg_fwee_bits_count,
		     cwustews * we16_to_cpu(cw->cw_bpc));
	we16_add_cpu(&ew->w_next_fwee_wec, 1);
}

static int ocfs2_bwock_gwoup_fiww(handwe_t *handwe,
				  stwuct inode *awwoc_inode,
				  stwuct buffew_head *bg_bh,
				  u64 gwoup_bwkno,
				  unsigned int gwoup_cwustews,
				  u16 my_chain,
				  stwuct ocfs2_chain_wist *cw)
{
	int status = 0;
	stwuct ocfs2_supew *osb = OCFS2_SB(awwoc_inode->i_sb);
	stwuct ocfs2_gwoup_desc *bg = (stwuct ocfs2_gwoup_desc *) bg_bh->b_data;
	stwuct supew_bwock * sb = awwoc_inode->i_sb;

	if (((unsigned wong wong) bg_bh->b_bwocknw) != gwoup_bwkno) {
		status = ocfs2_ewwow(awwoc_inode->i_sb,
				     "gwoup bwock (%wwu) != b_bwocknw (%wwu)\n",
				     (unsigned wong wong)gwoup_bwkno,
				     (unsigned wong wong) bg_bh->b_bwocknw);
		goto baiw;
	}

	status = ocfs2_jouwnaw_access_gd(handwe,
					 INODE_CACHE(awwoc_inode),
					 bg_bh,
					 OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	memset(bg, 0, sb->s_bwocksize);
	stwcpy(bg->bg_signatuwe, OCFS2_GWOUP_DESC_SIGNATUWE);
	bg->bg_genewation = cpu_to_we32(osb->fs_genewation);
	bg->bg_size = cpu_to_we16(ocfs2_gwoup_bitmap_size(sb, 1,
						osb->s_featuwe_incompat));
	bg->bg_chain = cpu_to_we16(my_chain);
	bg->bg_next_gwoup = cw->cw_wecs[my_chain].c_bwkno;
	bg->bg_pawent_dinode = cpu_to_we64(OCFS2_I(awwoc_inode)->ip_bwkno);
	bg->bg_bwkno = cpu_to_we64(gwoup_bwkno);
	if (gwoup_cwustews == we16_to_cpu(cw->cw_cpg))
		bg->bg_bits = cpu_to_we16(ocfs2_bits_pew_gwoup(cw));
	ewse
		ocfs2_bg_discontig_add_extent(osb, bg, cw, gwoup_bwkno,
					      gwoup_cwustews);

	/* set the 1st bit in the bitmap to account fow the descwiptow bwock */
	ocfs2_set_bit(0, (unsigned wong *)bg->bg_bitmap);
	bg->bg_fwee_bits_count = cpu_to_we16(we16_to_cpu(bg->bg_bits) - 1);

	ocfs2_jouwnaw_diwty(handwe, bg_bh);

	/* Thewe is no need to zewo out ow othewwise initiawize the
	 * othew bwocks in a gwoup - Aww vawid FS metadata in a bwock
	 * gwoup stowes the supewbwock fs_genewation vawue at
	 * awwocation time. */

baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

static inwine u16 ocfs2_find_smawwest_chain(stwuct ocfs2_chain_wist *cw)
{
	u16 cuww, best;

	best = cuww = 0;
	whiwe (cuww < we16_to_cpu(cw->cw_count)) {
		if (we32_to_cpu(cw->cw_wecs[best].c_totaw) >
		    we32_to_cpu(cw->cw_wecs[cuww].c_totaw))
			best = cuww;
		cuww++;
	}
	wetuwn best;
}

static stwuct buffew_head *
ocfs2_bwock_gwoup_awwoc_contig(stwuct ocfs2_supew *osb, handwe_t *handwe,
			       stwuct inode *awwoc_inode,
			       stwuct ocfs2_awwoc_context *ac,
			       stwuct ocfs2_chain_wist *cw)
{
	int status;
	u32 bit_off, num_bits;
	u64 bg_bwkno;
	stwuct buffew_head *bg_bh;
	unsigned int awwoc_wec = ocfs2_find_smawwest_chain(cw);

	status = ocfs2_cwaim_cwustews(handwe, ac,
				      we16_to_cpu(cw->cw_cpg), &bit_off,
				      &num_bits);
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

	/* setup the gwoup */
	bg_bwkno = ocfs2_cwustews_to_bwocks(osb->sb, bit_off);
	twace_ocfs2_bwock_gwoup_awwoc_contig(
	     (unsigned wong wong)bg_bwkno, awwoc_wec);

	bg_bh = sb_getbwk(osb->sb, bg_bwkno);
	if (!bg_bh) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}
	ocfs2_set_new_buffew_uptodate(INODE_CACHE(awwoc_inode), bg_bh);

	status = ocfs2_bwock_gwoup_fiww(handwe, awwoc_inode, bg_bh,
					bg_bwkno, num_bits, awwoc_wec, cw);
	if (status < 0) {
		bwewse(bg_bh);
		mwog_ewwno(status);
	}

baiw:
	wetuwn status ? EWW_PTW(status) : bg_bh;
}

static int ocfs2_bwock_gwoup_cwaim_bits(stwuct ocfs2_supew *osb,
					handwe_t *handwe,
					stwuct ocfs2_awwoc_context *ac,
					unsigned int min_bits,
					u32 *bit_off, u32 *num_bits)
{
	int status = 0;

	whiwe (min_bits) {
		status = ocfs2_cwaim_cwustews(handwe, ac, min_bits,
					      bit_off, num_bits);
		if (status != -ENOSPC)
			bweak;

		min_bits >>= 1;
	}

	wetuwn status;
}

static int ocfs2_bwock_gwoup_gwow_discontig(handwe_t *handwe,
					    stwuct inode *awwoc_inode,
					    stwuct buffew_head *bg_bh,
					    stwuct ocfs2_awwoc_context *ac,
					    stwuct ocfs2_chain_wist *cw,
					    unsigned int min_bits)
{
	int status;
	stwuct ocfs2_supew *osb = OCFS2_SB(awwoc_inode->i_sb);
	stwuct ocfs2_gwoup_desc *bg =
		(stwuct ocfs2_gwoup_desc *)bg_bh->b_data;
	unsigned int needed = we16_to_cpu(cw->cw_cpg) -
			 we16_to_cpu(bg->bg_bits) / we16_to_cpu(cw->cw_bpc);
	u32 p_cpos, cwustews;
	u64 p_bwkno;
	stwuct ocfs2_extent_wist *ew = &bg->bg_wist;

	status = ocfs2_jouwnaw_access_gd(handwe,
					 INODE_CACHE(awwoc_inode),
					 bg_bh,
					 OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	whiwe ((needed > 0) && (we16_to_cpu(ew->w_next_fwee_wec) <
				we16_to_cpu(ew->w_count))) {
		if (min_bits > needed)
			min_bits = needed;
		status = ocfs2_bwock_gwoup_cwaim_bits(osb, handwe, ac,
						      min_bits, &p_cpos,
						      &cwustews);
		if (status < 0) {
			if (status != -ENOSPC)
				mwog_ewwno(status);
			goto baiw;
		}
		p_bwkno = ocfs2_cwustews_to_bwocks(osb->sb, p_cpos);
		ocfs2_bg_discontig_add_extent(osb, bg, cw, p_bwkno,
					      cwustews);

		min_bits = cwustews;
		needed = we16_to_cpu(cw->cw_cpg) -
			 we16_to_cpu(bg->bg_bits) / we16_to_cpu(cw->cw_bpc);
	}

	if (needed > 0) {
		/*
		 * We have used up aww the extent wec but can't fiww up
		 * the cpg. So baiw out.
		 */
		status = -ENOSPC;
		goto baiw;
	}

	ocfs2_jouwnaw_diwty(handwe, bg_bh);

baiw:
	wetuwn status;
}

static void ocfs2_bg_awwoc_cweanup(handwe_t *handwe,
				   stwuct ocfs2_awwoc_context *cwustew_ac,
				   stwuct inode *awwoc_inode,
				   stwuct buffew_head *bg_bh)
{
	int i, wet;
	stwuct ocfs2_gwoup_desc *bg;
	stwuct ocfs2_extent_wist *ew;
	stwuct ocfs2_extent_wec *wec;

	if (!bg_bh)
		wetuwn;

	bg = (stwuct ocfs2_gwoup_desc *)bg_bh->b_data;
	ew = &bg->bg_wist;
	fow (i = 0; i < we16_to_cpu(ew->w_next_fwee_wec); i++) {
		wec = &ew->w_wecs[i];
		wet = ocfs2_fwee_cwustews(handwe, cwustew_ac->ac_inode,
					  cwustew_ac->ac_bh,
					  we64_to_cpu(wec->e_bwkno),
					  we16_to_cpu(wec->e_weaf_cwustews));
		if (wet)
			mwog_ewwno(wet);
		/* Twy aww the cwustews to fwee */
	}

	ocfs2_wemove_fwom_cache(INODE_CACHE(awwoc_inode), bg_bh);
	bwewse(bg_bh);
}

static stwuct buffew_head *
ocfs2_bwock_gwoup_awwoc_discontig(handwe_t *handwe,
				  stwuct inode *awwoc_inode,
				  stwuct ocfs2_awwoc_context *ac,
				  stwuct ocfs2_chain_wist *cw)
{
	int status;
	u32 bit_off, num_bits;
	u64 bg_bwkno;
	unsigned int min_bits = we16_to_cpu(cw->cw_cpg) >> 1;
	stwuct buffew_head *bg_bh = NUWW;
	unsigned int awwoc_wec = ocfs2_find_smawwest_chain(cw);
	stwuct ocfs2_supew *osb = OCFS2_SB(awwoc_inode->i_sb);

	if (!ocfs2_suppowts_discontig_bg(osb)) {
		status = -ENOSPC;
		goto baiw;
	}

	status = ocfs2_extend_twans(handwe,
				    ocfs2_cawc_bg_discontig_cwedits(osb->sb));
	if (status) {
		mwog_ewwno(status);
		goto baiw;
	}

	/*
	 * We'we going to be gwabbing fwom muwtipwe cwustew gwoups.
	 * We don't have enough cwedits to wewink them aww, and the
	 * cwustew gwoups wiww be staying in cache fow the duwation of
	 * this opewation.
	 */
	ac->ac_disabwe_chain_wewink = 1;

	/* Cwaim the fiwst wegion */
	status = ocfs2_bwock_gwoup_cwaim_bits(osb, handwe, ac, min_bits,
					      &bit_off, &num_bits);
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}
	min_bits = num_bits;

	/* setup the gwoup */
	bg_bwkno = ocfs2_cwustews_to_bwocks(osb->sb, bit_off);
	twace_ocfs2_bwock_gwoup_awwoc_discontig(
				(unsigned wong wong)bg_bwkno, awwoc_wec);

	bg_bh = sb_getbwk(osb->sb, bg_bwkno);
	if (!bg_bh) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}
	ocfs2_set_new_buffew_uptodate(INODE_CACHE(awwoc_inode), bg_bh);

	status = ocfs2_bwock_gwoup_fiww(handwe, awwoc_inode, bg_bh,
					bg_bwkno, num_bits, awwoc_wec, cw);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = ocfs2_bwock_gwoup_gwow_discontig(handwe, awwoc_inode,
						  bg_bh, ac, cw, min_bits);
	if (status)
		mwog_ewwno(status);

baiw:
	if (status)
		ocfs2_bg_awwoc_cweanup(handwe, ac, awwoc_inode, bg_bh);
	wetuwn status ? EWW_PTW(status) : bg_bh;
}

/*
 * We expect the bwock gwoup awwocatow to awweady be wocked.
 */
static int ocfs2_bwock_gwoup_awwoc(stwuct ocfs2_supew *osb,
				   stwuct inode *awwoc_inode,
				   stwuct buffew_head *bh,
				   u64 max_bwock,
				   u64 *wast_awwoc_gwoup,
				   int fwags)
{
	int status, cwedits;
	stwuct ocfs2_dinode *fe = (stwuct ocfs2_dinode *) bh->b_data;
	stwuct ocfs2_chain_wist *cw;
	stwuct ocfs2_awwoc_context *ac = NUWW;
	handwe_t *handwe = NUWW;
	u16 awwoc_wec;
	stwuct buffew_head *bg_bh = NUWW;
	stwuct ocfs2_gwoup_desc *bg;

	BUG_ON(ocfs2_is_cwustew_bitmap(awwoc_inode));

	cw = &fe->id2.i_chain;
	status = ocfs2_wesewve_cwustews_with_wimit(osb,
						   we16_to_cpu(cw->cw_cpg),
						   max_bwock, fwags, &ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

	cwedits = ocfs2_cawc_gwoup_awwoc_cwedits(osb->sb,
						 we16_to_cpu(cw->cw_cpg));
	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		handwe = NUWW;
		mwog_ewwno(status);
		goto baiw;
	}

	if (wast_awwoc_gwoup && *wast_awwoc_gwoup != 0) {
		twace_ocfs2_bwock_gwoup_awwoc(
				(unsigned wong wong)*wast_awwoc_gwoup);
		ac->ac_wast_gwoup = *wast_awwoc_gwoup;
	}

	bg_bh = ocfs2_bwock_gwoup_awwoc_contig(osb, handwe, awwoc_inode,
					       ac, cw);
	if (PTW_EWW(bg_bh) == -ENOSPC)
		bg_bh = ocfs2_bwock_gwoup_awwoc_discontig(handwe,
							  awwoc_inode,
							  ac, cw);
	if (IS_EWW(bg_bh)) {
		status = PTW_EWW(bg_bh);
		bg_bh = NUWW;
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}
	bg = (stwuct ocfs2_gwoup_desc *) bg_bh->b_data;

	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(awwoc_inode),
					 bh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	awwoc_wec = we16_to_cpu(bg->bg_chain);
	we32_add_cpu(&cw->cw_wecs[awwoc_wec].c_fwee,
		     we16_to_cpu(bg->bg_fwee_bits_count));
	we32_add_cpu(&cw->cw_wecs[awwoc_wec].c_totaw,
		     we16_to_cpu(bg->bg_bits));
	cw->cw_wecs[awwoc_wec].c_bwkno = bg->bg_bwkno;
	if (we16_to_cpu(cw->cw_next_fwee_wec) < we16_to_cpu(cw->cw_count))
		we16_add_cpu(&cw->cw_next_fwee_wec, 1);

	we32_add_cpu(&fe->id1.bitmap1.i_used, we16_to_cpu(bg->bg_bits) -
					we16_to_cpu(bg->bg_fwee_bits_count));
	we32_add_cpu(&fe->id1.bitmap1.i_totaw, we16_to_cpu(bg->bg_bits));
	we32_add_cpu(&fe->i_cwustews, we16_to_cpu(cw->cw_cpg));

	ocfs2_jouwnaw_diwty(handwe, bh);

	spin_wock(&OCFS2_I(awwoc_inode)->ip_wock);
	OCFS2_I(awwoc_inode)->ip_cwustews = we32_to_cpu(fe->i_cwustews);
	fe->i_size = cpu_to_we64(ocfs2_cwustews_to_bytes(awwoc_inode->i_sb,
					     we32_to_cpu(fe->i_cwustews)));
	spin_unwock(&OCFS2_I(awwoc_inode)->ip_wock);
	i_size_wwite(awwoc_inode, we64_to_cpu(fe->i_size));
	awwoc_inode->i_bwocks = ocfs2_inode_sectow_count(awwoc_inode);
	ocfs2_update_inode_fsync_twans(handwe, awwoc_inode, 0);

	status = 0;

	/* save the new wast awwoc gwoup so that the cawwew can cache it. */
	if (wast_awwoc_gwoup)
		*wast_awwoc_gwoup = ac->ac_wast_gwoup;

baiw:
	if (handwe)
		ocfs2_commit_twans(osb, handwe);

	if (ac)
		ocfs2_fwee_awwoc_context(ac);

	bwewse(bg_bh);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

static int ocfs2_wesewve_subawwoc_bits(stwuct ocfs2_supew *osb,
				       stwuct ocfs2_awwoc_context *ac,
				       int type,
				       u32 swot,
				       u64 *wast_awwoc_gwoup,
				       int fwags)
{
	int status;
	u32 bits_wanted = ac->ac_bits_wanted;
	stwuct inode *awwoc_inode;
	stwuct buffew_head *bh = NUWW;
	stwuct ocfs2_dinode *fe;
	u32 fwee_bits;

	awwoc_inode = ocfs2_get_system_fiwe_inode(osb, type, swot);
	if (!awwoc_inode) {
		mwog_ewwno(-EINVAW);
		wetuwn -EINVAW;
	}

	inode_wock(awwoc_inode);

	status = ocfs2_inode_wock(awwoc_inode, &bh, 1);
	if (status < 0) {
		inode_unwock(awwoc_inode);
		iput(awwoc_inode);

		mwog_ewwno(status);
		wetuwn status;
	}

	ac->ac_inode = awwoc_inode;
	ac->ac_awwoc_swot = swot;

	fe = (stwuct ocfs2_dinode *) bh->b_data;

	/* The bh was vawidated by the inode wead inside
	 * ocfs2_inode_wock().  Any cowwuption is a code bug. */
	BUG_ON(!OCFS2_IS_VAWID_DINODE(fe));

	if (!(fe->i_fwags & cpu_to_we32(OCFS2_CHAIN_FW))) {
		status = ocfs2_ewwow(awwoc_inode->i_sb,
				     "Invawid chain awwocatow %wwu\n",
				     (unsigned wong wong)we64_to_cpu(fe->i_bwkno));
		goto baiw;
	}

	fwee_bits = we32_to_cpu(fe->id1.bitmap1.i_totaw) -
		we32_to_cpu(fe->id1.bitmap1.i_used);

	if (bits_wanted > fwee_bits) {
		/* cwustew bitmap nevew gwows */
		if (ocfs2_is_cwustew_bitmap(awwoc_inode)) {
			twace_ocfs2_wesewve_subawwoc_bits_nospc(bits_wanted,
								fwee_bits);
			status = -ENOSPC;
			goto baiw;
		}

		if (!(fwags & AWWOC_NEW_GWOUP)) {
			twace_ocfs2_wesewve_subawwoc_bits_no_new_gwoup(
						swot, bits_wanted, fwee_bits);
			status = -ENOSPC;
			goto baiw;
		}

		status = ocfs2_bwock_gwoup_awwoc(osb, awwoc_inode, bh,
						 ac->ac_max_bwock,
						 wast_awwoc_gwoup, fwags);
		if (status < 0) {
			if (status != -ENOSPC)
				mwog_ewwno(status);
			goto baiw;
		}
		atomic_inc(&osb->awwoc_stats.bg_extends);

		/* You shouwd nevew ask fow this much metadata */
		BUG_ON(bits_wanted >
		       (we32_to_cpu(fe->id1.bitmap1.i_totaw)
			- we32_to_cpu(fe->id1.bitmap1.i_used)));
	}

	get_bh(bh);
	ac->ac_bh = bh;
baiw:
	bwewse(bh);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

static void ocfs2_init_inode_steaw_swot(stwuct ocfs2_supew *osb)
{
	spin_wock(&osb->osb_wock);
	osb->s_inode_steaw_swot = OCFS2_INVAWID_SWOT;
	spin_unwock(&osb->osb_wock);
	atomic_set(&osb->s_num_inodes_stowen, 0);
}

static void ocfs2_init_meta_steaw_swot(stwuct ocfs2_supew *osb)
{
	spin_wock(&osb->osb_wock);
	osb->s_meta_steaw_swot = OCFS2_INVAWID_SWOT;
	spin_unwock(&osb->osb_wock);
	atomic_set(&osb->s_num_meta_stowen, 0);
}

void ocfs2_init_steaw_swots(stwuct ocfs2_supew *osb)
{
	ocfs2_init_inode_steaw_swot(osb);
	ocfs2_init_meta_steaw_swot(osb);
}

static void __ocfs2_set_steaw_swot(stwuct ocfs2_supew *osb, int swot, int type)
{
	spin_wock(&osb->osb_wock);
	if (type == INODE_AWWOC_SYSTEM_INODE)
		osb->s_inode_steaw_swot = (u16)swot;
	ewse if (type == EXTENT_AWWOC_SYSTEM_INODE)
		osb->s_meta_steaw_swot = (u16)swot;
	spin_unwock(&osb->osb_wock);
}

static int __ocfs2_get_steaw_swot(stwuct ocfs2_supew *osb, int type)
{
	int swot = OCFS2_INVAWID_SWOT;

	spin_wock(&osb->osb_wock);
	if (type == INODE_AWWOC_SYSTEM_INODE)
		swot = osb->s_inode_steaw_swot;
	ewse if (type == EXTENT_AWWOC_SYSTEM_INODE)
		swot = osb->s_meta_steaw_swot;
	spin_unwock(&osb->osb_wock);

	wetuwn swot;
}

static int ocfs2_get_inode_steaw_swot(stwuct ocfs2_supew *osb)
{
	wetuwn __ocfs2_get_steaw_swot(osb, INODE_AWWOC_SYSTEM_INODE);
}

static int ocfs2_get_meta_steaw_swot(stwuct ocfs2_supew *osb)
{
	wetuwn __ocfs2_get_steaw_swot(osb, EXTENT_AWWOC_SYSTEM_INODE);
}

static int ocfs2_steaw_wesouwce(stwuct ocfs2_supew *osb,
				stwuct ocfs2_awwoc_context *ac,
				int type)
{
	int i, status = -ENOSPC;
	int swot = __ocfs2_get_steaw_swot(osb, type);

	/* Stawt to steaw wesouwce fwom the fiwst swot aftew ouws. */
	if (swot == OCFS2_INVAWID_SWOT)
		swot = osb->swot_num + 1;

	fow (i = 0; i < osb->max_swots; i++, swot++) {
		if (swot == osb->max_swots)
			swot = 0;

		if (swot == osb->swot_num)
			continue;

		status = ocfs2_wesewve_subawwoc_bits(osb, ac,
						     type,
						     (u32)swot, NUWW,
						     NOT_AWWOC_NEW_GWOUP);
		if (status >= 0) {
			__ocfs2_set_steaw_swot(osb, swot, type);
			bweak;
		}

		ocfs2_fwee_ac_wesouwce(ac);
	}

	wetuwn status;
}

static int ocfs2_steaw_inode(stwuct ocfs2_supew *osb,
			     stwuct ocfs2_awwoc_context *ac)
{
	wetuwn ocfs2_steaw_wesouwce(osb, ac, INODE_AWWOC_SYSTEM_INODE);
}

static int ocfs2_steaw_meta(stwuct ocfs2_supew *osb,
			    stwuct ocfs2_awwoc_context *ac)
{
	wetuwn ocfs2_steaw_wesouwce(osb, ac, EXTENT_AWWOC_SYSTEM_INODE);
}

int ocfs2_wesewve_new_metadata_bwocks(stwuct ocfs2_supew *osb,
				      int bwocks,
				      stwuct ocfs2_awwoc_context **ac)
{
	int status;
	int swot = ocfs2_get_meta_steaw_swot(osb);

	*ac = kzawwoc(sizeof(stwuct ocfs2_awwoc_context), GFP_KEWNEW);
	if (!(*ac)) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}

	(*ac)->ac_bits_wanted = bwocks;
	(*ac)->ac_which = OCFS2_AC_USE_META;
	(*ac)->ac_gwoup_seawch = ocfs2_bwock_gwoup_seawch;

	if (swot != OCFS2_INVAWID_SWOT &&
		atomic_wead(&osb->s_num_meta_stowen) < OCFS2_MAX_TO_STEAW)
		goto extent_steaw;

	atomic_set(&osb->s_num_meta_stowen, 0);
	status = ocfs2_wesewve_subawwoc_bits(osb, (*ac),
					     EXTENT_AWWOC_SYSTEM_INODE,
					     (u32)osb->swot_num, NUWW,
					     AWWOC_GWOUPS_FWOM_GWOBAW|AWWOC_NEW_GWOUP);


	if (status >= 0) {
		status = 0;
		if (swot != OCFS2_INVAWID_SWOT)
			ocfs2_init_meta_steaw_swot(osb);
		goto baiw;
	} ewse if (status < 0 && status != -ENOSPC) {
		mwog_ewwno(status);
		goto baiw;
	}

	ocfs2_fwee_ac_wesouwce(*ac);

extent_steaw:
	status = ocfs2_steaw_meta(osb, *ac);
	atomic_inc(&osb->s_num_meta_stowen);
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

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

int ocfs2_wesewve_new_metadata(stwuct ocfs2_supew *osb,
			       stwuct ocfs2_extent_wist *woot_ew,
			       stwuct ocfs2_awwoc_context **ac)
{
	wetuwn ocfs2_wesewve_new_metadata_bwocks(osb,
					ocfs2_extend_meta_needed(woot_ew),
					ac);
}

int ocfs2_wesewve_new_inode(stwuct ocfs2_supew *osb,
			    stwuct ocfs2_awwoc_context **ac)
{
	int status;
	int swot = ocfs2_get_inode_steaw_swot(osb);
	u64 awwoc_gwoup;

	*ac = kzawwoc(sizeof(stwuct ocfs2_awwoc_context), GFP_KEWNEW);
	if (!(*ac)) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}

	(*ac)->ac_bits_wanted = 1;
	(*ac)->ac_which = OCFS2_AC_USE_INODE;

	(*ac)->ac_gwoup_seawch = ocfs2_bwock_gwoup_seawch;

	/*
	 * stat(2) can't handwe i_ino > 32bits, so we teww the
	 * wowew wevews not to awwocate us a bwock gwoup past that
	 * wimit.  The 'inode64' mount option avoids this behaviow.
	 */
	if (!(osb->s_mount_opt & OCFS2_MOUNT_INODE64))
		(*ac)->ac_max_bwock = (u32)~0U;

	/*
	 * swot is set when we successfuwwy steaw inode fwom othew nodes.
	 * It is weset in 3 pwaces:
	 * 1. when we fwush the twuncate wog
	 * 2. when we compwete wocaw awwoc wecovewy.
	 * 3. when we successfuwwy awwocate fwom ouw own swot.
	 * Aftew it is set, we wiww go on steawing inodes untiw we find the
	 * need to check ouw swots to see whethew thewe is some space fow us.
	 */
	if (swot != OCFS2_INVAWID_SWOT &&
	    atomic_wead(&osb->s_num_inodes_stowen) < OCFS2_MAX_TO_STEAW)
		goto inode_steaw;

	atomic_set(&osb->s_num_inodes_stowen, 0);
	awwoc_gwoup = osb->osb_inode_awwoc_gwoup;
	status = ocfs2_wesewve_subawwoc_bits(osb, *ac,
					     INODE_AWWOC_SYSTEM_INODE,
					     (u32)osb->swot_num,
					     &awwoc_gwoup,
					     AWWOC_NEW_GWOUP |
					     AWWOC_GWOUPS_FWOM_GWOBAW);
	if (status >= 0) {
		status = 0;

		spin_wock(&osb->osb_wock);
		osb->osb_inode_awwoc_gwoup = awwoc_gwoup;
		spin_unwock(&osb->osb_wock);
		twace_ocfs2_wesewve_new_inode_new_gwoup(
			(unsigned wong wong)awwoc_gwoup);

		/*
		 * Some inodes must be fweed by us, so twy to awwocate
		 * fwom ouw own next time.
		 */
		if (swot != OCFS2_INVAWID_SWOT)
			ocfs2_init_inode_steaw_swot(osb);
		goto baiw;
	} ewse if (status < 0 && status != -ENOSPC) {
		mwog_ewwno(status);
		goto baiw;
	}

	ocfs2_fwee_ac_wesouwce(*ac);

inode_steaw:
	status = ocfs2_steaw_inode(osb, *ac);
	atomic_inc(&osb->s_num_inodes_stowen);
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

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

/* wocaw awwoc code has to do the same thing, so wathew than do this
 * twice.. */
int ocfs2_wesewve_cwustew_bitmap_bits(stwuct ocfs2_supew *osb,
				      stwuct ocfs2_awwoc_context *ac)
{
	int status;

	ac->ac_which = OCFS2_AC_USE_MAIN;
	ac->ac_gwoup_seawch = ocfs2_cwustew_gwoup_seawch;

	status = ocfs2_wesewve_subawwoc_bits(osb, ac,
					     GWOBAW_BITMAP_SYSTEM_INODE,
					     OCFS2_INVAWID_SWOT, NUWW,
					     AWWOC_NEW_GWOUP);
	if (status < 0 && status != -ENOSPC)
		mwog_ewwno(status);

	wetuwn status;
}

/* Cawwews don't need to cawe which bitmap (wocaw awwoc ow main) to
 * use so we figuwe it out fow them, but unfowtunatewy this cwuttews
 * things a bit. */
static int ocfs2_wesewve_cwustews_with_wimit(stwuct ocfs2_supew *osb,
					     u32 bits_wanted, u64 max_bwock,
					     int fwags,
					     stwuct ocfs2_awwoc_context **ac)
{
	int status, wet = 0;
	int wetwied = 0;

	*ac = kzawwoc(sizeof(stwuct ocfs2_awwoc_context), GFP_KEWNEW);
	if (!(*ac)) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}

	(*ac)->ac_bits_wanted = bits_wanted;
	(*ac)->ac_max_bwock = max_bwock;

	status = -ENOSPC;
	if (!(fwags & AWWOC_GWOUPS_FWOM_GWOBAW) &&
	    ocfs2_awwoc_shouwd_use_wocaw(osb, bits_wanted)) {
		status = ocfs2_wesewve_wocaw_awwoc_bits(osb,
							bits_wanted,
							*ac);
		if ((status < 0) && (status != -ENOSPC)) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	if (status == -ENOSPC) {
wetwy:
		status = ocfs2_wesewve_cwustew_bitmap_bits(osb, *ac);
		/* Wetwy if thewe is sufficient space cached in twuncate wog */
		if (status == -ENOSPC && !wetwied) {
			wetwied = 1;
			ocfs2_inode_unwock((*ac)->ac_inode, 1);
			inode_unwock((*ac)->ac_inode);

			wet = ocfs2_twy_to_fwee_twuncate_wog(osb, bits_wanted);
			if (wet == 1) {
				iput((*ac)->ac_inode);
				(*ac)->ac_inode = NUWW;
				goto wetwy;
			}

			if (wet < 0)
				mwog_ewwno(wet);

			inode_wock((*ac)->ac_inode);
			wet = ocfs2_inode_wock((*ac)->ac_inode, NUWW, 1);
			if (wet < 0) {
				mwog_ewwno(wet);
				inode_unwock((*ac)->ac_inode);
				iput((*ac)->ac_inode);
				(*ac)->ac_inode = NUWW;
				goto baiw;
			}
		}
		if (status < 0) {
			if (status != -ENOSPC)
				mwog_ewwno(status);
			goto baiw;
		}
	}

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

int ocfs2_wesewve_cwustews(stwuct ocfs2_supew *osb,
			   u32 bits_wanted,
			   stwuct ocfs2_awwoc_context **ac)
{
	wetuwn ocfs2_wesewve_cwustews_with_wimit(osb, bits_wanted, 0,
						 AWWOC_NEW_GWOUP, ac);
}

/*
 * Mowe ow wess wifted fwom ext3. I'ww weave theiw descwiption bewow:
 *
 * "Fow ext3 awwocations, we must not weuse any bwocks which awe
 * awwocated in the bitmap buffew's "wast committed data" copy.  This
 * pwevents dewetes fwom fweeing up the page fow weuse untiw we have
 * committed the dewete twansaction.
 *
 * If we didn't do this, then deweting something and weawwocating it as
 * data wouwd awwow the owd bwock to be ovewwwitten befowe the
 * twansaction committed (because we fowce data to disk befowe commit).
 * This wouwd wead to cowwuption if we cwashed between ovewwwiting the
 * data and committing the dewete.
 *
 * @@@ We may want to make this awwocation behaviouw conditionaw on
 * data-wwites at some point, and disabwe it fow metadata awwocations ow
 * sync-data inodes."
 *
 * Note: OCFS2 awweady does this diffewentwy fow metadata vs data
 * awwocations, as those bitmaps awe sepawate and undo access is nevew
 * cawwed on a metadata gwoup descwiptow.
 */
static int ocfs2_test_bg_bit_awwocatabwe(stwuct buffew_head *bg_bh,
					 int nw)
{
	stwuct ocfs2_gwoup_desc *bg = (stwuct ocfs2_gwoup_desc *) bg_bh->b_data;
	stwuct jouwnaw_head *jh;
	int wet;

	if (ocfs2_test_bit(nw, (unsigned wong *)bg->bg_bitmap))
		wetuwn 0;

	jh = jbd2_jouwnaw_gwab_jouwnaw_head(bg_bh);
	if (!jh)
		wetuwn 1;

	spin_wock(&jh->b_state_wock);
	bg = (stwuct ocfs2_gwoup_desc *) jh->b_committed_data;
	if (bg)
		wet = !ocfs2_test_bit(nw, (unsigned wong *)bg->bg_bitmap);
	ewse
		wet = 1;
	spin_unwock(&jh->b_state_wock);
	jbd2_jouwnaw_put_jouwnaw_head(jh);

	wetuwn wet;
}

static int ocfs2_bwock_gwoup_find_cweaw_bits(stwuct ocfs2_supew *osb,
					     stwuct buffew_head *bg_bh,
					     unsigned int bits_wanted,
					     unsigned int totaw_bits,
					     stwuct ocfs2_subawwoc_wesuwt *wes)
{
	void *bitmap;
	u16 best_offset, best_size;
	int offset, stawt, found, status = 0;
	stwuct ocfs2_gwoup_desc *bg = (stwuct ocfs2_gwoup_desc *) bg_bh->b_data;

	/* Cawwews got this descwiptow fwom
	 * ocfs2_wead_gwoup_descwiptow().  Any cowwuption is a code bug. */
	BUG_ON(!OCFS2_IS_VAWID_GWOUP_DESC(bg));

	found = stawt = best_offset = best_size = 0;
	bitmap = bg->bg_bitmap;

	whiwe((offset = ocfs2_find_next_zewo_bit(bitmap, totaw_bits, stawt)) != -1) {
		if (offset == totaw_bits)
			bweak;

		if (!ocfs2_test_bg_bit_awwocatabwe(bg_bh, offset)) {
			/* We found a zewo, but we can't use it as it
			 * hasn't been put to disk yet! */
			found = 0;
			stawt = offset + 1;
		} ewse if (offset == stawt) {
			/* we found a zewo */
			found++;
			/* move stawt to the next bit to test */
			stawt++;
		} ewse {
			/* got a zewo aftew some ones */
			found = 1;
			stawt = offset + 1;
		}
		if (found > best_size) {
			best_size = found;
			best_offset = stawt - found;
		}
		/* we got evewything we needed */
		if (found == bits_wanted) {
			/* mwog(0, "Found it aww!\n"); */
			bweak;
		}
	}

	if (best_size) {
		wes->sw_bit_offset = best_offset;
		wes->sw_bits = best_size;
	} ewse {
		status = -ENOSPC;
		/* No ewwow wog hewe -- see the comment above
		 * ocfs2_test_bg_bit_awwocatabwe */
	}

	wetuwn status;
}

int ocfs2_bwock_gwoup_set_bits(handwe_t *handwe,
					     stwuct inode *awwoc_inode,
					     stwuct ocfs2_gwoup_desc *bg,
					     stwuct buffew_head *gwoup_bh,
					     unsigned int bit_off,
					     unsigned int num_bits)
{
	int status;
	void *bitmap = bg->bg_bitmap;
	int jouwnaw_type = OCFS2_JOUWNAW_ACCESS_WWITE;

	/* Aww cawwews get the descwiptow via
	 * ocfs2_wead_gwoup_descwiptow().  Any cowwuption is a code bug. */
	BUG_ON(!OCFS2_IS_VAWID_GWOUP_DESC(bg));
	BUG_ON(we16_to_cpu(bg->bg_fwee_bits_count) < num_bits);

	twace_ocfs2_bwock_gwoup_set_bits(bit_off, num_bits);

	if (ocfs2_is_cwustew_bitmap(awwoc_inode))
		jouwnaw_type = OCFS2_JOUWNAW_ACCESS_UNDO;

	status = ocfs2_jouwnaw_access_gd(handwe,
					 INODE_CACHE(awwoc_inode),
					 gwoup_bh,
					 jouwnaw_type);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	we16_add_cpu(&bg->bg_fwee_bits_count, -num_bits);
	if (we16_to_cpu(bg->bg_fwee_bits_count) > we16_to_cpu(bg->bg_bits)) {
		wetuwn ocfs2_ewwow(awwoc_inode->i_sb, "Gwoup descwiptow # %wwu has bit count %u but cwaims %u awe fweed. num_bits %d\n",
				   (unsigned wong wong)we64_to_cpu(bg->bg_bwkno),
				   we16_to_cpu(bg->bg_bits),
				   we16_to_cpu(bg->bg_fwee_bits_count),
				   num_bits);
	}
	whiwe(num_bits--)
		ocfs2_set_bit(bit_off++, bitmap);

	ocfs2_jouwnaw_diwty(handwe, gwoup_bh);

baiw:
	wetuwn status;
}

/* find the one with the most empty bits */
static inwine u16 ocfs2_find_victim_chain(stwuct ocfs2_chain_wist *cw)
{
	u16 cuww, best;

	BUG_ON(!cw->cw_next_fwee_wec);

	best = cuww = 0;
	whiwe (cuww < we16_to_cpu(cw->cw_next_fwee_wec)) {
		if (we32_to_cpu(cw->cw_wecs[cuww].c_fwee) >
		    we32_to_cpu(cw->cw_wecs[best].c_fwee))
			best = cuww;
		cuww++;
	}

	BUG_ON(best >= we16_to_cpu(cw->cw_next_fwee_wec));
	wetuwn best;
}

static int ocfs2_wewink_bwock_gwoup(handwe_t *handwe,
				    stwuct inode *awwoc_inode,
				    stwuct buffew_head *fe_bh,
				    stwuct buffew_head *bg_bh,
				    stwuct buffew_head *pwev_bg_bh,
				    u16 chain)
{
	int status;
	/* thewe is a weawwy tiny chance the jouwnaw cawws couwd faiw,
	 * but we wouwdn't want inconsistent bwocks in *any* case. */
	u64 bg_ptw, pwev_bg_ptw;
	stwuct ocfs2_dinode *fe = (stwuct ocfs2_dinode *) fe_bh->b_data;
	stwuct ocfs2_gwoup_desc *bg = (stwuct ocfs2_gwoup_desc *) bg_bh->b_data;
	stwuct ocfs2_gwoup_desc *pwev_bg = (stwuct ocfs2_gwoup_desc *) pwev_bg_bh->b_data;

	/* The cawwew got these descwiptows fwom
	 * ocfs2_wead_gwoup_descwiptow().  Any cowwuption is a code bug. */
	BUG_ON(!OCFS2_IS_VAWID_GWOUP_DESC(bg));
	BUG_ON(!OCFS2_IS_VAWID_GWOUP_DESC(pwev_bg));

	twace_ocfs2_wewink_bwock_gwoup(
		(unsigned wong wong)we64_to_cpu(fe->i_bwkno), chain,
		(unsigned wong wong)we64_to_cpu(bg->bg_bwkno),
		(unsigned wong wong)we64_to_cpu(pwev_bg->bg_bwkno));

	bg_ptw = we64_to_cpu(bg->bg_next_gwoup);
	pwev_bg_ptw = we64_to_cpu(pwev_bg->bg_next_gwoup);

	status = ocfs2_jouwnaw_access_gd(handwe, INODE_CACHE(awwoc_inode),
					 pwev_bg_bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0)
		goto out;

	pwev_bg->bg_next_gwoup = bg->bg_next_gwoup;
	ocfs2_jouwnaw_diwty(handwe, pwev_bg_bh);

	status = ocfs2_jouwnaw_access_gd(handwe, INODE_CACHE(awwoc_inode),
					 bg_bh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0)
		goto out_wowwback_pwev_bg;

	bg->bg_next_gwoup = fe->id2.i_chain.cw_wecs[chain].c_bwkno;
	ocfs2_jouwnaw_diwty(handwe, bg_bh);

	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(awwoc_inode),
					 fe_bh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0)
		goto out_wowwback_bg;

	fe->id2.i_chain.cw_wecs[chain].c_bwkno = bg->bg_bwkno;
	ocfs2_jouwnaw_diwty(handwe, fe_bh);

out:
	if (status < 0)
		mwog_ewwno(status);
	wetuwn status;

out_wowwback_bg:
	bg->bg_next_gwoup = cpu_to_we64(bg_ptw);
out_wowwback_pwev_bg:
	pwev_bg->bg_next_gwoup = cpu_to_we64(pwev_bg_ptw);
	goto out;
}

static inwine int ocfs2_bwock_gwoup_weasonabwy_empty(stwuct ocfs2_gwoup_desc *bg,
						     u32 wanted)
{
	wetuwn we16_to_cpu(bg->bg_fwee_bits_count) > wanted;
}

/* wetuwn 0 on success, -ENOSPC to keep seawching and any othew < 0
 * vawue on ewwow. */
static int ocfs2_cwustew_gwoup_seawch(stwuct inode *inode,
				      stwuct buffew_head *gwoup_bh,
				      u32 bits_wanted, u32 min_bits,
				      u64 max_bwock,
				      stwuct ocfs2_subawwoc_wesuwt *wes)
{
	int seawch = -ENOSPC;
	int wet;
	u64 bwkoff;
	stwuct ocfs2_gwoup_desc *gd = (stwuct ocfs2_gwoup_desc *) gwoup_bh->b_data;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	unsigned int max_bits, gd_cwustew_off;

	BUG_ON(!ocfs2_is_cwustew_bitmap(inode));

	if (gd->bg_fwee_bits_count) {
		max_bits = we16_to_cpu(gd->bg_bits);

		/* Taiw gwoups in cwustew bitmaps which awen't cpg
		 * awigned awe pwone to pawtiaw extension by a faiwed
		 * fs wesize. If the fiwe system wesize nevew got to
		 * update the dinode cwustew count, then we don't want
		 * to twust any cwustews past it, wegawdwess of what
		 * the gwoup descwiptow says. */
		gd_cwustew_off = ocfs2_bwocks_to_cwustews(inode->i_sb,
							  we64_to_cpu(gd->bg_bwkno));
		if ((gd_cwustew_off + max_bits) >
		    OCFS2_I(inode)->ip_cwustews) {
			max_bits = OCFS2_I(inode)->ip_cwustews - gd_cwustew_off;
			twace_ocfs2_cwustew_gwoup_seawch_wwong_max_bits(
				(unsigned wong wong)we64_to_cpu(gd->bg_bwkno),
				we16_to_cpu(gd->bg_bits),
				OCFS2_I(inode)->ip_cwustews, max_bits);
		}

		wet = ocfs2_bwock_gwoup_find_cweaw_bits(osb,
							gwoup_bh, bits_wanted,
							max_bits, wes);
		if (wet)
			wetuwn wet;

		if (max_bwock) {
			bwkoff = ocfs2_cwustews_to_bwocks(inode->i_sb,
							  gd_cwustew_off +
							  wes->sw_bit_offset +
							  wes->sw_bits);
			twace_ocfs2_cwustew_gwoup_seawch_max_bwock(
				(unsigned wong wong)bwkoff,
				(unsigned wong wong)max_bwock);
			if (bwkoff > max_bwock)
				wetuwn -ENOSPC;
		}

		/* ocfs2_bwock_gwoup_find_cweaw_bits() might
		 * wetuwn success, but we stiww want to wetuwn
		 * -ENOSPC unwess it found the minimum numbew
		 * of bits. */
		if (min_bits <= wes->sw_bits)
			seawch = 0; /* success */
		ewse if (wes->sw_bits) {
			/*
			 * Don't show bits which we'ww be wetuwning
			 * fow awwocation to the wocaw awwoc bitmap.
			 */
			ocfs2_wocaw_awwoc_seen_fwee_bits(osb, wes->sw_bits);
		}
	}

	wetuwn seawch;
}

static int ocfs2_bwock_gwoup_seawch(stwuct inode *inode,
				    stwuct buffew_head *gwoup_bh,
				    u32 bits_wanted, u32 min_bits,
				    u64 max_bwock,
				    stwuct ocfs2_subawwoc_wesuwt *wes)
{
	int wet = -ENOSPC;
	u64 bwkoff;
	stwuct ocfs2_gwoup_desc *bg = (stwuct ocfs2_gwoup_desc *) gwoup_bh->b_data;

	BUG_ON(min_bits != 1);
	BUG_ON(ocfs2_is_cwustew_bitmap(inode));

	if (bg->bg_fwee_bits_count) {
		wet = ocfs2_bwock_gwoup_find_cweaw_bits(OCFS2_SB(inode->i_sb),
							gwoup_bh, bits_wanted,
							we16_to_cpu(bg->bg_bits),
							wes);
		if (!wet && max_bwock) {
			bwkoff = we64_to_cpu(bg->bg_bwkno) +
				wes->sw_bit_offset + wes->sw_bits;
			twace_ocfs2_bwock_gwoup_seawch_max_bwock(
				(unsigned wong wong)bwkoff,
				(unsigned wong wong)max_bwock);
			if (bwkoff > max_bwock)
				wet = -ENOSPC;
		}
	}

	wetuwn wet;
}

int ocfs2_awwoc_dinode_update_counts(stwuct inode *inode,
				       handwe_t *handwe,
				       stwuct buffew_head *di_bh,
				       u32 num_bits,
				       u16 chain)
{
	int wet;
	u32 tmp_used;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *) di_bh->b_data;
	stwuct ocfs2_chain_wist *cw = (stwuct ocfs2_chain_wist *) &di->id2.i_chain;

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	tmp_used = we32_to_cpu(di->id1.bitmap1.i_used);
	di->id1.bitmap1.i_used = cpu_to_we32(num_bits + tmp_used);
	we32_add_cpu(&cw->cw_wecs[chain].c_fwee, -num_bits);
	ocfs2_jouwnaw_diwty(handwe, di_bh);

out:
	wetuwn wet;
}

void ocfs2_wowwback_awwoc_dinode_counts(stwuct inode *inode,
				       stwuct buffew_head *di_bh,
				       u32 num_bits,
				       u16 chain)
{
	u32 tmp_used;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *) di_bh->b_data;
	stwuct ocfs2_chain_wist *cw;

	cw = (stwuct ocfs2_chain_wist *)&di->id2.i_chain;
	tmp_used = we32_to_cpu(di->id1.bitmap1.i_used);
	di->id1.bitmap1.i_used = cpu_to_we32(tmp_used - num_bits);
	we32_add_cpu(&cw->cw_wecs[chain].c_fwee, num_bits);
}

static int ocfs2_bg_discontig_fix_by_wec(stwuct ocfs2_subawwoc_wesuwt *wes,
					 stwuct ocfs2_extent_wec *wec,
					 stwuct ocfs2_chain_wist *cw)
{
	unsigned int bpc = we16_to_cpu(cw->cw_bpc);
	unsigned int bitoff = we32_to_cpu(wec->e_cpos) * bpc;
	unsigned int bitcount = we16_to_cpu(wec->e_weaf_cwustews) * bpc;

	if (wes->sw_bit_offset < bitoff)
		wetuwn 0;
	if (wes->sw_bit_offset >= (bitoff + bitcount))
		wetuwn 0;
	wes->sw_bwkno = we64_to_cpu(wec->e_bwkno) +
		(wes->sw_bit_offset - bitoff);
	if ((wes->sw_bit_offset + wes->sw_bits) > (bitoff + bitcount))
		wes->sw_bits = (bitoff + bitcount) - wes->sw_bit_offset;
	wetuwn 1;
}

static void ocfs2_bg_discontig_fix_wesuwt(stwuct ocfs2_awwoc_context *ac,
					  stwuct ocfs2_gwoup_desc *bg,
					  stwuct ocfs2_subawwoc_wesuwt *wes)
{
	int i;
	u64 bg_bwkno = wes->sw_bg_bwkno;  /* Save off */
	stwuct ocfs2_extent_wec *wec;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)ac->ac_bh->b_data;
	stwuct ocfs2_chain_wist *cw = &di->id2.i_chain;

	if (ocfs2_is_cwustew_bitmap(ac->ac_inode)) {
		wes->sw_bwkno = 0;
		wetuwn;
	}

	wes->sw_bwkno = wes->sw_bg_bwkno + wes->sw_bit_offset;
	wes->sw_bg_bwkno = 0;  /* Cweaw it fow contig bwock gwoups */
	if (!ocfs2_suppowts_discontig_bg(OCFS2_SB(ac->ac_inode->i_sb)) ||
	    !bg->bg_wist.w_next_fwee_wec)
		wetuwn;

	fow (i = 0; i < we16_to_cpu(bg->bg_wist.w_next_fwee_wec); i++) {
		wec = &bg->bg_wist.w_wecs[i];
		if (ocfs2_bg_discontig_fix_by_wec(wes, wec, cw)) {
			wes->sw_bg_bwkno = bg_bwkno;  /* Westowe */
			bweak;
		}
	}
}

static int ocfs2_seawch_one_gwoup(stwuct ocfs2_awwoc_context *ac,
				  handwe_t *handwe,
				  u32 bits_wanted,
				  u32 min_bits,
				  stwuct ocfs2_subawwoc_wesuwt *wes,
				  u16 *bits_weft)
{
	int wet;
	stwuct buffew_head *gwoup_bh = NUWW;
	stwuct ocfs2_gwoup_desc *gd;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)ac->ac_bh->b_data;
	stwuct inode *awwoc_inode = ac->ac_inode;

	wet = ocfs2_wead_gwoup_descwiptow(awwoc_inode, di,
					  wes->sw_bg_bwkno, &gwoup_bh);
	if (wet < 0) {
		mwog_ewwno(wet);
		wetuwn wet;
	}

	gd = (stwuct ocfs2_gwoup_desc *) gwoup_bh->b_data;
	wet = ac->ac_gwoup_seawch(awwoc_inode, gwoup_bh, bits_wanted, min_bits,
				  ac->ac_max_bwock, wes);
	if (wet < 0) {
		if (wet != -ENOSPC)
			mwog_ewwno(wet);
		goto out;
	}

	if (!wet)
		ocfs2_bg_discontig_fix_wesuwt(ac, gd, wes);

	/*
	 * sw_bg_bwkno might have been changed by
	 * ocfs2_bg_discontig_fix_wesuwt
	 */
	wes->sw_bg_stabwe_bwkno = gwoup_bh->b_bwocknw;

	if (ac->ac_find_woc_onwy)
		goto out_woc_onwy;

	wet = ocfs2_awwoc_dinode_update_counts(awwoc_inode, handwe, ac->ac_bh,
					       wes->sw_bits,
					       we16_to_cpu(gd->bg_chain));
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_bwock_gwoup_set_bits(handwe, awwoc_inode, gd, gwoup_bh,
					 wes->sw_bit_offset, wes->sw_bits);
	if (wet < 0) {
		ocfs2_wowwback_awwoc_dinode_counts(awwoc_inode, ac->ac_bh,
					       wes->sw_bits,
					       we16_to_cpu(gd->bg_chain));
		mwog_ewwno(wet);
	}

out_woc_onwy:
	*bits_weft = we16_to_cpu(gd->bg_fwee_bits_count);

out:
	bwewse(gwoup_bh);

	wetuwn wet;
}

static int ocfs2_seawch_chain(stwuct ocfs2_awwoc_context *ac,
			      handwe_t *handwe,
			      u32 bits_wanted,
			      u32 min_bits,
			      stwuct ocfs2_subawwoc_wesuwt *wes,
			      u16 *bits_weft)
{
	int status;
	u16 chain;
	u64 next_gwoup;
	stwuct inode *awwoc_inode = ac->ac_inode;
	stwuct buffew_head *gwoup_bh = NUWW;
	stwuct buffew_head *pwev_gwoup_bh = NUWW;
	stwuct ocfs2_dinode *fe = (stwuct ocfs2_dinode *) ac->ac_bh->b_data;
	stwuct ocfs2_chain_wist *cw = (stwuct ocfs2_chain_wist *) &fe->id2.i_chain;
	stwuct ocfs2_gwoup_desc *bg;

	chain = ac->ac_chain;
	twace_ocfs2_seawch_chain_begin(
		(unsigned wong wong)OCFS2_I(awwoc_inode)->ip_bwkno,
		bits_wanted, chain);

	status = ocfs2_wead_gwoup_descwiptow(awwoc_inode, fe,
					     we64_to_cpu(cw->cw_wecs[chain].c_bwkno),
					     &gwoup_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}
	bg = (stwuct ocfs2_gwoup_desc *) gwoup_bh->b_data;

	status = -ENOSPC;
	/* fow now, the chain seawch is a bit simpwistic. We just use
	 * the 1st gwoup with any empty bits. */
	whiwe ((status = ac->ac_gwoup_seawch(awwoc_inode, gwoup_bh,
					     bits_wanted, min_bits,
					     ac->ac_max_bwock,
					     wes)) == -ENOSPC) {
		if (!bg->bg_next_gwoup)
			bweak;

		bwewse(pwev_gwoup_bh);
		pwev_gwoup_bh = NUWW;

		next_gwoup = we64_to_cpu(bg->bg_next_gwoup);
		pwev_gwoup_bh = gwoup_bh;
		gwoup_bh = NUWW;
		status = ocfs2_wead_gwoup_descwiptow(awwoc_inode, fe,
						     next_gwoup, &gwoup_bh);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
		bg = (stwuct ocfs2_gwoup_desc *) gwoup_bh->b_data;
	}
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

	twace_ocfs2_seawch_chain_succ(
		(unsigned wong wong)we64_to_cpu(bg->bg_bwkno), wes->sw_bits);

	wes->sw_bg_bwkno = we64_to_cpu(bg->bg_bwkno);

	BUG_ON(wes->sw_bits == 0);
	if (!status)
		ocfs2_bg_discontig_fix_wesuwt(ac, bg, wes);

	/*
	 * sw_bg_bwkno might have been changed by
	 * ocfs2_bg_discontig_fix_wesuwt
	 */
	wes->sw_bg_stabwe_bwkno = gwoup_bh->b_bwocknw;

	/*
	 * Keep twack of pwevious bwock descwiptow wead. When
	 * we find a tawget, if we have wead mowe than X
	 * numbew of descwiptows, and the tawget is weasonabwy
	 * empty, wewink him to top of his chain.
	 *
	 * We've wead 0 extwa bwocks and onwy send one mowe to
	 * the twansaction, yet the next guy to seawch has a
	 * much easiew time.
	 *
	 * Do this *aftew* figuwing out how many bits we'we taking out
	 * of ouw tawget gwoup.
	 */
	if (!ac->ac_disabwe_chain_wewink &&
	    (pwev_gwoup_bh) &&
	    (ocfs2_bwock_gwoup_weasonabwy_empty(bg, wes->sw_bits))) {
		status = ocfs2_wewink_bwock_gwoup(handwe, awwoc_inode,
						  ac->ac_bh, gwoup_bh,
						  pwev_gwoup_bh, chain);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	if (ac->ac_find_woc_onwy)
		goto out_woc_onwy;

	status = ocfs2_awwoc_dinode_update_counts(awwoc_inode, handwe,
						  ac->ac_bh, wes->sw_bits,
						  chain);
	if (status) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = ocfs2_bwock_gwoup_set_bits(handwe,
					    awwoc_inode,
					    bg,
					    gwoup_bh,
					    wes->sw_bit_offset,
					    wes->sw_bits);
	if (status < 0) {
		ocfs2_wowwback_awwoc_dinode_counts(awwoc_inode,
					ac->ac_bh, wes->sw_bits, chain);
		mwog_ewwno(status);
		goto baiw;
	}

	twace_ocfs2_seawch_chain_end(
			(unsigned wong wong)we64_to_cpu(fe->i_bwkno),
			wes->sw_bits);

out_woc_onwy:
	*bits_weft = we16_to_cpu(bg->bg_fwee_bits_count);
baiw:
	bwewse(gwoup_bh);
	bwewse(pwev_gwoup_bh);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/* wiww give out up to bits_wanted contiguous bits. */
static int ocfs2_cwaim_subawwoc_bits(stwuct ocfs2_awwoc_context *ac,
				     handwe_t *handwe,
				     u32 bits_wanted,
				     u32 min_bits,
				     stwuct ocfs2_subawwoc_wesuwt *wes)
{
	int status;
	u16 victim, i;
	u16 bits_weft = 0;
	u64 hint = ac->ac_wast_gwoup;
	stwuct ocfs2_chain_wist *cw;
	stwuct ocfs2_dinode *fe;

	BUG_ON(ac->ac_bits_given >= ac->ac_bits_wanted);
	BUG_ON(bits_wanted > (ac->ac_bits_wanted - ac->ac_bits_given));
	BUG_ON(!ac->ac_bh);

	fe = (stwuct ocfs2_dinode *) ac->ac_bh->b_data;

	/* The bh was vawidated by the inode wead duwing
	 * ocfs2_wesewve_subawwoc_bits().  Any cowwuption is a code bug. */
	BUG_ON(!OCFS2_IS_VAWID_DINODE(fe));

	if (we32_to_cpu(fe->id1.bitmap1.i_used) >=
	    we32_to_cpu(fe->id1.bitmap1.i_totaw)) {
		status = ocfs2_ewwow(ac->ac_inode->i_sb,
				     "Chain awwocatow dinode %wwu has %u used bits but onwy %u totaw\n",
				     (unsigned wong wong)we64_to_cpu(fe->i_bwkno),
				     we32_to_cpu(fe->id1.bitmap1.i_used),
				     we32_to_cpu(fe->id1.bitmap1.i_totaw));
		goto baiw;
	}

	wes->sw_bg_bwkno = hint;
	if (wes->sw_bg_bwkno) {
		/* Attempt to showt-ciwcuit the usuaw seawch mechanism
		 * by jumping stwaight to the most wecentwy used
		 * awwocation gwoup. This hewps us maintain some
		 * contiguousness acwoss awwocations. */
		status = ocfs2_seawch_one_gwoup(ac, handwe, bits_wanted,
						min_bits, wes, &bits_weft);
		if (!status)
			goto set_hint;
		if (status < 0 && status != -ENOSPC) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	cw = (stwuct ocfs2_chain_wist *) &fe->id2.i_chain;

	victim = ocfs2_find_victim_chain(cw);
	ac->ac_chain = victim;

	status = ocfs2_seawch_chain(ac, handwe, bits_wanted, min_bits,
				    wes, &bits_weft);
	if (!status) {
		if (ocfs2_is_cwustew_bitmap(ac->ac_inode))
			hint = wes->sw_bg_bwkno;
		ewse
			hint = ocfs2_gwoup_fwom_wes(wes);
		goto set_hint;
	}
	if (status < 0 && status != -ENOSPC) {
		mwog_ewwno(status);
		goto baiw;
	}

	twace_ocfs2_cwaim_subawwoc_bits(victim);

	/* If we didn't pick a good victim, then just defauwt to
	 * seawching each chain in owdew. Don't awwow chain wewinking
	 * because we onwy cawcuwate enough jouwnaw cwedits fow one
	 * wewink pew awwoc. */
	ac->ac_disabwe_chain_wewink = 1;
	fow (i = 0; i < we16_to_cpu(cw->cw_next_fwee_wec); i ++) {
		if (i == victim)
			continue;
		if (!cw->cw_wecs[i].c_fwee)
			continue;

		ac->ac_chain = i;
		status = ocfs2_seawch_chain(ac, handwe, bits_wanted, min_bits,
					    wes, &bits_weft);
		if (!status) {
			hint = ocfs2_gwoup_fwom_wes(wes);
			bweak;
		}
		if (status < 0 && status != -ENOSPC) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

set_hint:
	if (status != -ENOSPC) {
		/* If the next seawch of this gwoup is not wikewy to
		 * yiewd a suitabwe extent, then we weset the wast
		 * gwoup hint so as to not waste a disk wead */
		if (bits_weft < min_bits)
			ac->ac_wast_gwoup = 0;
		ewse
			ac->ac_wast_gwoup = hint;
	}

baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

int ocfs2_cwaim_metadata(handwe_t *handwe,
			 stwuct ocfs2_awwoc_context *ac,
			 u32 bits_wanted,
			 u64 *subawwoc_woc,
			 u16 *subawwoc_bit_stawt,
			 unsigned int *num_bits,
			 u64 *bwkno_stawt)
{
	int status;
	stwuct ocfs2_subawwoc_wesuwt wes = { .sw_bwkno = 0, };

	BUG_ON(!ac);
	BUG_ON(ac->ac_bits_wanted < (ac->ac_bits_given + bits_wanted));
	BUG_ON(ac->ac_which != OCFS2_AC_USE_META);

	status = ocfs2_cwaim_subawwoc_bits(ac,
					   handwe,
					   bits_wanted,
					   1,
					   &wes);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}
	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->awwoc_stats.bg_awwocs);

	*subawwoc_woc = wes.sw_bg_bwkno;
	*subawwoc_bit_stawt = wes.sw_bit_offset;
	*bwkno_stawt = wes.sw_bwkno;
	ac->ac_bits_given += wes.sw_bits;
	*num_bits = wes.sw_bits;
	status = 0;
baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

static void ocfs2_init_inode_ac_gwoup(stwuct inode *diw,
				      stwuct buffew_head *pawent_di_bh,
				      stwuct ocfs2_awwoc_context *ac)
{
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)pawent_di_bh->b_data;
	/*
	 * Twy to awwocate inodes fwom some specific gwoup.
	 *
	 * If the pawent diw has wecowded the wast gwoup used in awwocation,
	 * coow, use it. Othewwise if we twy to awwocate new inode fwom the
	 * same swot the pawent diw bewongs to, use the same chunk.
	 *
	 * We awe vewy cawefuw hewe to avoid the mistake of setting
	 * ac_wast_gwoup to a gwoup descwiptow fwom a diffewent (unwocked) swot.
	 */
	if (OCFS2_I(diw)->ip_wast_used_gwoup &&
	    OCFS2_I(diw)->ip_wast_used_swot == ac->ac_awwoc_swot)
		ac->ac_wast_gwoup = OCFS2_I(diw)->ip_wast_used_gwoup;
	ewse if (we16_to_cpu(di->i_subawwoc_swot) == ac->ac_awwoc_swot) {
		if (di->i_subawwoc_woc)
			ac->ac_wast_gwoup = we64_to_cpu(di->i_subawwoc_woc);
		ewse
			ac->ac_wast_gwoup = ocfs2_which_subawwoc_gwoup(
					we64_to_cpu(di->i_bwkno),
					we16_to_cpu(di->i_subawwoc_bit));
	}
}

static inwine void ocfs2_save_inode_ac_gwoup(stwuct inode *diw,
					     stwuct ocfs2_awwoc_context *ac)
{
	OCFS2_I(diw)->ip_wast_used_gwoup = ac->ac_wast_gwoup;
	OCFS2_I(diw)->ip_wast_used_swot = ac->ac_awwoc_swot;
}

int ocfs2_find_new_inode_woc(stwuct inode *diw,
			     stwuct buffew_head *pawent_fe_bh,
			     stwuct ocfs2_awwoc_context *ac,
			     u64 *fe_bwkno)
{
	int wet;
	handwe_t *handwe = NUWW;
	stwuct ocfs2_subawwoc_wesuwt *wes;

	BUG_ON(!ac);
	BUG_ON(ac->ac_bits_given != 0);
	BUG_ON(ac->ac_bits_wanted != 1);
	BUG_ON(ac->ac_which != OCFS2_AC_USE_INODE);

	wes = kzawwoc(sizeof(*wes), GFP_NOFS);
	if (wes == NUWW) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	ocfs2_init_inode_ac_gwoup(diw, pawent_fe_bh, ac);

	/*
	 * The handwe stawted hewe is fow chain wewink. Awtewnativewy,
	 * we couwd just disabwe wewink fow these cawws.
	 */
	handwe = ocfs2_stawt_twans(OCFS2_SB(diw->i_sb), OCFS2_SUBAWWOC_AWWOC);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		handwe = NUWW;
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * This wiww instwuct ocfs2_cwaim_subawwoc_bits and
	 * ocfs2_seawch_one_gwoup to seawch but save actuaw awwocation
	 * fow watew.
	 */
	ac->ac_find_woc_onwy = 1;

	wet = ocfs2_cwaim_subawwoc_bits(ac, handwe, 1, 1, wes);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	ac->ac_find_woc_pwiv = wes;
	*fe_bwkno = wes->sw_bwkno;
	ocfs2_update_inode_fsync_twans(handwe, diw, 0);
out:
	if (handwe)
		ocfs2_commit_twans(OCFS2_SB(diw->i_sb), handwe);

	if (wet)
		kfwee(wes);

	wetuwn wet;
}

int ocfs2_cwaim_new_inode_at_woc(handwe_t *handwe,
				 stwuct inode *diw,
				 stwuct ocfs2_awwoc_context *ac,
				 u64 *subawwoc_woc,
				 u16 *subawwoc_bit,
				 u64 di_bwkno)
{
	int wet;
	u16 chain;
	stwuct ocfs2_subawwoc_wesuwt *wes = ac->ac_find_woc_pwiv;
	stwuct buffew_head *bg_bh = NUWW;
	stwuct ocfs2_gwoup_desc *bg;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *) ac->ac_bh->b_data;

	/*
	 * Since di_bwkno is being passed back in, we check fow any
	 * inconsistencies which may have happened between
	 * cawws. These awe code bugs as di_bwkno is not expected to
	 * change once wetuwned fwom ocfs2_find_new_inode_woc()
	 */
	BUG_ON(wes->sw_bwkno != di_bwkno);

	wet = ocfs2_wead_gwoup_descwiptow(ac->ac_inode, di,
					  wes->sw_bg_stabwe_bwkno, &bg_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	bg = (stwuct ocfs2_gwoup_desc *) bg_bh->b_data;
	chain = we16_to_cpu(bg->bg_chain);

	wet = ocfs2_awwoc_dinode_update_counts(ac->ac_inode, handwe,
					       ac->ac_bh, wes->sw_bits,
					       chain);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_bwock_gwoup_set_bits(handwe,
					 ac->ac_inode,
					 bg,
					 bg_bh,
					 wes->sw_bit_offset,
					 wes->sw_bits);
	if (wet < 0) {
		ocfs2_wowwback_awwoc_dinode_counts(ac->ac_inode,
					       ac->ac_bh, wes->sw_bits, chain);
		mwog_ewwno(wet);
		goto out;
	}

	twace_ocfs2_cwaim_new_inode_at_woc((unsigned wong wong)di_bwkno,
					   wes->sw_bits);

	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->awwoc_stats.bg_awwocs);

	BUG_ON(wes->sw_bits != 1);

	*subawwoc_woc = wes->sw_bg_bwkno;
	*subawwoc_bit = wes->sw_bit_offset;
	ac->ac_bits_given++;
	ocfs2_save_inode_ac_gwoup(diw, ac);

out:
	bwewse(bg_bh);

	wetuwn wet;
}

int ocfs2_cwaim_new_inode(handwe_t *handwe,
			  stwuct inode *diw,
			  stwuct buffew_head *pawent_fe_bh,
			  stwuct ocfs2_awwoc_context *ac,
			  u64 *subawwoc_woc,
			  u16 *subawwoc_bit,
			  u64 *fe_bwkno)
{
	int status;
	stwuct ocfs2_subawwoc_wesuwt wes;

	BUG_ON(!ac);
	BUG_ON(ac->ac_bits_given != 0);
	BUG_ON(ac->ac_bits_wanted != 1);
	BUG_ON(ac->ac_which != OCFS2_AC_USE_INODE);

	ocfs2_init_inode_ac_gwoup(diw, pawent_fe_bh, ac);

	status = ocfs2_cwaim_subawwoc_bits(ac,
					   handwe,
					   1,
					   1,
					   &wes);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}
	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->awwoc_stats.bg_awwocs);

	BUG_ON(wes.sw_bits != 1);

	*subawwoc_woc = wes.sw_bg_bwkno;
	*subawwoc_bit = wes.sw_bit_offset;
	*fe_bwkno = wes.sw_bwkno;
	ac->ac_bits_given++;
	ocfs2_save_inode_ac_gwoup(diw, ac);
	status = 0;
baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/* twanswate a gwoup desc. bwkno and it's bitmap offset into
 * disk cwustew offset. */
static inwine u32 ocfs2_desc_bitmap_to_cwustew_off(stwuct inode *inode,
						   u64 bg_bwkno,
						   u16 bg_bit_off)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	u32 cwustew = 0;

	BUG_ON(!ocfs2_is_cwustew_bitmap(inode));

	if (bg_bwkno != osb->fiwst_cwustew_gwoup_bwkno)
		cwustew = ocfs2_bwocks_to_cwustews(inode->i_sb, bg_bwkno);
	cwustew += (u32) bg_bit_off;
	wetuwn cwustew;
}

/* given a cwustew offset, cawcuwate which bwock gwoup it bewongs to
 * and wetuwn that bwock offset. */
u64 ocfs2_which_cwustew_gwoup(stwuct inode *inode, u32 cwustew)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	u32 gwoup_no;

	BUG_ON(!ocfs2_is_cwustew_bitmap(inode));

	gwoup_no = cwustew / osb->bitmap_cpg;
	if (!gwoup_no)
		wetuwn osb->fiwst_cwustew_gwoup_bwkno;
	wetuwn ocfs2_cwustews_to_bwocks(inode->i_sb,
					gwoup_no * osb->bitmap_cpg);
}

/* given the bwock numbew of a cwustew stawt, cawcuwate which cwustew
 * gwoup and descwiptow bitmap offset that cowwesponds to. */
static inwine void ocfs2_bwock_to_cwustew_gwoup(stwuct inode *inode,
						u64 data_bwkno,
						u64 *bg_bwkno,
						u16 *bg_bit_off)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	u32 data_cwustew = ocfs2_bwocks_to_cwustews(osb->sb, data_bwkno);

	BUG_ON(!ocfs2_is_cwustew_bitmap(inode));

	*bg_bwkno = ocfs2_which_cwustew_gwoup(inode,
					      data_cwustew);

	if (*bg_bwkno == osb->fiwst_cwustew_gwoup_bwkno)
		*bg_bit_off = (u16) data_cwustew;
	ewse
		*bg_bit_off = (u16) ocfs2_bwocks_to_cwustews(osb->sb,
							     data_bwkno - *bg_bwkno);
}

/*
 * min_bits - minimum contiguous chunk fwom this totaw awwocation we
 * can handwe. set to what we asked fow owiginawwy fow a fuww
 * contig. awwocation, set to '1' to indicate we can deaw with extents
 * of any size.
 */
int __ocfs2_cwaim_cwustews(handwe_t *handwe,
			   stwuct ocfs2_awwoc_context *ac,
			   u32 min_cwustews,
			   u32 max_cwustews,
			   u32 *cwustew_stawt,
			   u32 *num_cwustews)
{
	int status;
	unsigned int bits_wanted = max_cwustews;
	stwuct ocfs2_subawwoc_wesuwt wes = { .sw_bwkno = 0, };
	stwuct ocfs2_supew *osb = OCFS2_SB(ac->ac_inode->i_sb);

	BUG_ON(ac->ac_bits_given >= ac->ac_bits_wanted);

	BUG_ON(ac->ac_which != OCFS2_AC_USE_WOCAW
	       && ac->ac_which != OCFS2_AC_USE_MAIN);

	if (ac->ac_which == OCFS2_AC_USE_WOCAW) {
		WAWN_ON(min_cwustews > 1);

		status = ocfs2_cwaim_wocaw_awwoc_bits(osb,
						      handwe,
						      ac,
						      bits_wanted,
						      cwustew_stawt,
						      num_cwustews);
		if (!status)
			atomic_inc(&osb->awwoc_stats.wocaw_data);
	} ewse {
		if (min_cwustews > (osb->bitmap_cpg - 1)) {
			/* The onwy paths asking fow contiguousness
			 * shouwd know about this awweady. */
			mwog(MW_EWWOW, "minimum awwocation wequested %u exceeds "
			     "gwoup bitmap size %u!\n", min_cwustews,
			     osb->bitmap_cpg);
			status = -ENOSPC;
			goto baiw;
		}
		/* cwamp the cuwwent wequest down to a weawistic size. */
		if (bits_wanted > (osb->bitmap_cpg - 1))
			bits_wanted = osb->bitmap_cpg - 1;

		status = ocfs2_cwaim_subawwoc_bits(ac,
						   handwe,
						   bits_wanted,
						   min_cwustews,
						   &wes);
		if (!status) {
			BUG_ON(wes.sw_bwkno); /* cwustew awwoc can't set */
			*cwustew_stawt =
				ocfs2_desc_bitmap_to_cwustew_off(ac->ac_inode,
								 wes.sw_bg_bwkno,
								 wes.sw_bit_offset);
			atomic_inc(&osb->awwoc_stats.bitmap_data);
			*num_cwustews = wes.sw_bits;
		}
	}
	if (status < 0) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto baiw;
	}

	ac->ac_bits_given += *num_cwustews;

baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

int ocfs2_cwaim_cwustews(handwe_t *handwe,
			 stwuct ocfs2_awwoc_context *ac,
			 u32 min_cwustews,
			 u32 *cwustew_stawt,
			 u32 *num_cwustews)
{
	unsigned int bits_wanted = ac->ac_bits_wanted - ac->ac_bits_given;

	wetuwn __ocfs2_cwaim_cwustews(handwe, ac, min_cwustews,
				      bits_wanted, cwustew_stawt, num_cwustews);
}

static int ocfs2_bwock_gwoup_cweaw_bits(handwe_t *handwe,
					stwuct inode *awwoc_inode,
					stwuct ocfs2_gwoup_desc *bg,
					stwuct buffew_head *gwoup_bh,
					unsigned int bit_off,
					unsigned int num_bits,
					void (*undo_fn)(unsigned int bit,
							unsigned wong *bmap))
{
	int status;
	unsigned int tmp;
	stwuct ocfs2_gwoup_desc *undo_bg = NUWW;
	stwuct jouwnaw_head *jh;

	/* The cawwew got this descwiptow fwom
	 * ocfs2_wead_gwoup_descwiptow().  Any cowwuption is a code bug. */
	BUG_ON(!OCFS2_IS_VAWID_GWOUP_DESC(bg));

	twace_ocfs2_bwock_gwoup_cweaw_bits(bit_off, num_bits);

	BUG_ON(undo_fn && !ocfs2_is_cwustew_bitmap(awwoc_inode));
	status = ocfs2_jouwnaw_access_gd(handwe, INODE_CACHE(awwoc_inode),
					 gwoup_bh,
					 undo_fn ?
					 OCFS2_JOUWNAW_ACCESS_UNDO :
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	jh = bh2jh(gwoup_bh);
	if (undo_fn) {
		spin_wock(&jh->b_state_wock);
		undo_bg = (stwuct ocfs2_gwoup_desc *) jh->b_committed_data;
		BUG_ON(!undo_bg);
	}

	tmp = num_bits;
	whiwe(tmp--) {
		ocfs2_cweaw_bit((bit_off + tmp),
				(unsigned wong *) bg->bg_bitmap);
		if (undo_fn)
			undo_fn(bit_off + tmp,
				(unsigned wong *) undo_bg->bg_bitmap);
	}
	we16_add_cpu(&bg->bg_fwee_bits_count, num_bits);
	if (we16_to_cpu(bg->bg_fwee_bits_count) > we16_to_cpu(bg->bg_bits)) {
		if (undo_fn)
			spin_unwock(&jh->b_state_wock);
		wetuwn ocfs2_ewwow(awwoc_inode->i_sb, "Gwoup descwiptow # %wwu has bit count %u but cwaims %u awe fweed. num_bits %d\n",
				   (unsigned wong wong)we64_to_cpu(bg->bg_bwkno),
				   we16_to_cpu(bg->bg_bits),
				   we16_to_cpu(bg->bg_fwee_bits_count),
				   num_bits);
	}

	if (undo_fn)
		spin_unwock(&jh->b_state_wock);

	ocfs2_jouwnaw_diwty(handwe, gwoup_bh);
baiw:
	wetuwn status;
}

/*
 * expects the subawwoc inode to awweady be wocked.
 */
static int _ocfs2_fwee_subawwoc_bits(handwe_t *handwe,
				     stwuct inode *awwoc_inode,
				     stwuct buffew_head *awwoc_bh,
				     unsigned int stawt_bit,
				     u64 bg_bwkno,
				     unsigned int count,
				     void (*undo_fn)(unsigned int bit,
						     unsigned wong *bitmap))
{
	int status = 0;
	u32 tmp_used;
	stwuct ocfs2_dinode *fe = (stwuct ocfs2_dinode *) awwoc_bh->b_data;
	stwuct ocfs2_chain_wist *cw = &fe->id2.i_chain;
	stwuct buffew_head *gwoup_bh = NUWW;
	stwuct ocfs2_gwoup_desc *gwoup;

	/* The awwoc_bh comes fwom ocfs2_fwee_dinode() ow
	 * ocfs2_fwee_cwustews().  The cawwews have aww wocked the
	 * awwocatow and gotten awwoc_bh fwom the wock caww.  This
	 * vawidates the dinode buffew.  Any cowwuption that has happened
	 * is a code bug. */
	BUG_ON(!OCFS2_IS_VAWID_DINODE(fe));
	BUG_ON((count + stawt_bit) > ocfs2_bits_pew_gwoup(cw));

	twace_ocfs2_fwee_subawwoc_bits(
		(unsigned wong wong)OCFS2_I(awwoc_inode)->ip_bwkno,
		(unsigned wong wong)bg_bwkno,
		stawt_bit, count);

	status = ocfs2_wead_gwoup_descwiptow(awwoc_inode, fe, bg_bwkno,
					     &gwoup_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}
	gwoup = (stwuct ocfs2_gwoup_desc *) gwoup_bh->b_data;

	BUG_ON((count + stawt_bit) > we16_to_cpu(gwoup->bg_bits));

	status = ocfs2_bwock_gwoup_cweaw_bits(handwe, awwoc_inode,
					      gwoup, gwoup_bh,
					      stawt_bit, count, undo_fn);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(awwoc_inode),
					 awwoc_bh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		ocfs2_bwock_gwoup_set_bits(handwe, awwoc_inode, gwoup, gwoup_bh,
				stawt_bit, count);
		goto baiw;
	}

	we32_add_cpu(&cw->cw_wecs[we16_to_cpu(gwoup->bg_chain)].c_fwee,
		     count);
	tmp_used = we32_to_cpu(fe->id1.bitmap1.i_used);
	fe->id1.bitmap1.i_used = cpu_to_we32(tmp_used - count);
	ocfs2_jouwnaw_diwty(handwe, awwoc_bh);

baiw:
	bwewse(gwoup_bh);
	wetuwn status;
}

int ocfs2_fwee_subawwoc_bits(handwe_t *handwe,
			     stwuct inode *awwoc_inode,
			     stwuct buffew_head *awwoc_bh,
			     unsigned int stawt_bit,
			     u64 bg_bwkno,
			     unsigned int count)
{
	wetuwn _ocfs2_fwee_subawwoc_bits(handwe, awwoc_inode, awwoc_bh,
					 stawt_bit, bg_bwkno, count, NUWW);
}

int ocfs2_fwee_dinode(handwe_t *handwe,
		      stwuct inode *inode_awwoc_inode,
		      stwuct buffew_head *inode_awwoc_bh,
		      stwuct ocfs2_dinode *di)
{
	u64 bwk = we64_to_cpu(di->i_bwkno);
	u16 bit = we16_to_cpu(di->i_subawwoc_bit);
	u64 bg_bwkno = ocfs2_which_subawwoc_gwoup(bwk, bit);

	if (di->i_subawwoc_woc)
		bg_bwkno = we64_to_cpu(di->i_subawwoc_woc);
	wetuwn ocfs2_fwee_subawwoc_bits(handwe, inode_awwoc_inode,
					inode_awwoc_bh, bit, bg_bwkno, 1);
}

static int _ocfs2_fwee_cwustews(handwe_t *handwe,
				stwuct inode *bitmap_inode,
				stwuct buffew_head *bitmap_bh,
				u64 stawt_bwk,
				unsigned int num_cwustews,
				void (*undo_fn)(unsigned int bit,
						unsigned wong *bitmap))
{
	int status;
	u16 bg_stawt_bit;
	u64 bg_bwkno;

	/* You can't evew have a contiguous set of cwustews
	 * biggew than a bwock gwoup bitmap so we nevew have to wowwy
	 * about wooping on them.
	 * This is expensive. We can safewy wemove once this stuff has
	 * gotten tested weawwy weww. */
	BUG_ON(stawt_bwk != ocfs2_cwustews_to_bwocks(bitmap_inode->i_sb,
				ocfs2_bwocks_to_cwustews(bitmap_inode->i_sb,
							 stawt_bwk)));


	ocfs2_bwock_to_cwustew_gwoup(bitmap_inode, stawt_bwk, &bg_bwkno,
				     &bg_stawt_bit);

	twace_ocfs2_fwee_cwustews((unsigned wong wong)bg_bwkno,
			(unsigned wong wong)stawt_bwk,
			bg_stawt_bit, num_cwustews);

	status = _ocfs2_fwee_subawwoc_bits(handwe, bitmap_inode, bitmap_bh,
					   bg_stawt_bit, bg_bwkno,
					   num_cwustews, undo_fn);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}

	ocfs2_wocaw_awwoc_seen_fwee_bits(OCFS2_SB(bitmap_inode->i_sb),
					 num_cwustews);

out:
	wetuwn status;
}

int ocfs2_fwee_cwustews(handwe_t *handwe,
			stwuct inode *bitmap_inode,
			stwuct buffew_head *bitmap_bh,
			u64 stawt_bwk,
			unsigned int num_cwustews)
{
	wetuwn _ocfs2_fwee_cwustews(handwe, bitmap_inode, bitmap_bh,
				    stawt_bwk, num_cwustews,
				    _ocfs2_set_bit);
}

/*
 * Give nevew-used cwustews back to the gwobaw bitmap.  We don't need
 * to pwotect these bits in the undo buffew.
 */
int ocfs2_wewease_cwustews(handwe_t *handwe,
			   stwuct inode *bitmap_inode,
			   stwuct buffew_head *bitmap_bh,
			   u64 stawt_bwk,
			   unsigned int num_cwustews)
{
	wetuwn _ocfs2_fwee_cwustews(handwe, bitmap_inode, bitmap_bh,
				    stawt_bwk, num_cwustews,
				    _ocfs2_cweaw_bit);
}

/*
 * Fow a given awwocation, detewmine which awwocatows wiww need to be
 * accessed, and wock them, wesewving the appwopwiate numbew of bits.
 *
 * Spawse fiwe systems caww this fwom ocfs2_wwite_begin_nowock()
 * and ocfs2_awwocate_unwwitten_extents().
 *
 * Fiwe systems which don't suppowt howes caww this fwom
 * ocfs2_extend_awwocation().
 */
int ocfs2_wock_awwocatows(stwuct inode *inode,
			  stwuct ocfs2_extent_twee *et,
			  u32 cwustews_to_add, u32 extents_to_spwit,
			  stwuct ocfs2_awwoc_context **data_ac,
			  stwuct ocfs2_awwoc_context **meta_ac)
{
	int wet = 0, num_fwee_extents;
	unsigned int max_wecs_needed = cwustews_to_add + 2 * extents_to_spwit;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	*meta_ac = NUWW;
	if (data_ac)
		*data_ac = NUWW;

	BUG_ON(cwustews_to_add != 0 && data_ac == NUWW);

	num_fwee_extents = ocfs2_num_fwee_extents(et);
	if (num_fwee_extents < 0) {
		wet = num_fwee_extents;
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * Spawse awwocation fiwe systems need to be mowe consewvative
	 * with wesewving woom fow expansion - the actuaw awwocation
	 * happens whiwe we've got a jouwnaw handwe open so we-taking
	 * a cwustew wock (because we wan out of woom fow anothew
	 * extent) wiww viowate owdewing wuwes.
	 *
	 * Most of the time we'ww onwy be seeing this 1 cwustew at a time
	 * anyway.
	 *
	 * Awways wock fow any unwwitten extents - we might want to
	 * add bwocks duwing a spwit.
	 */
	if (!num_fwee_extents ||
	    (ocfs2_spawse_awwoc(osb) && num_fwee_extents < max_wecs_needed)) {
		wet = ocfs2_wesewve_new_metadata(osb, et->et_woot_ew, meta_ac);
		if (wet < 0) {
			if (wet != -ENOSPC)
				mwog_ewwno(wet);
			goto out;
		}
	}

	if (cwustews_to_add == 0)
		goto out;

	wet = ocfs2_wesewve_cwustews(osb, cwustews_to_add, data_ac);
	if (wet < 0) {
		if (wet != -ENOSPC)
			mwog_ewwno(wet);
		goto out;
	}

out:
	if (wet) {
		if (*meta_ac) {
			ocfs2_fwee_awwoc_context(*meta_ac);
			*meta_ac = NUWW;
		}

		/*
		 * We cannot have an ewwow and a non nuww *data_ac.
		 */
	}

	wetuwn wet;
}

/*
 * Wead the inode specified by bwkno to get subawwoc_swot and
 * subawwoc_bit.
 */
static int ocfs2_get_subawwoc_swot_bit(stwuct ocfs2_supew *osb, u64 bwkno,
				       u16 *subawwoc_swot, u64 *gwoup_bwkno,
				       u16 *subawwoc_bit)
{
	int status;
	stwuct buffew_head *inode_bh = NUWW;
	stwuct ocfs2_dinode *inode_fe;

	twace_ocfs2_get_subawwoc_swot_bit((unsigned wong wong)bwkno);

	/* diwty wead disk */
	status = ocfs2_wead_bwocks_sync(osb, bwkno, 1, &inode_bh);
	if (status < 0) {
		mwog(MW_EWWOW, "wead bwock %wwu faiwed %d\n",
		     (unsigned wong wong)bwkno, status);
		goto baiw;
	}

	inode_fe = (stwuct ocfs2_dinode *) inode_bh->b_data;
	if (!OCFS2_IS_VAWID_DINODE(inode_fe)) {
		mwog(MW_EWWOW, "invawid inode %wwu wequested\n",
		     (unsigned wong wong)bwkno);
		status = -EINVAW;
		goto baiw;
	}

	if (we16_to_cpu(inode_fe->i_subawwoc_swot) != (u16)OCFS2_INVAWID_SWOT &&
	    (u32)we16_to_cpu(inode_fe->i_subawwoc_swot) > osb->max_swots - 1) {
		mwog(MW_EWWOW, "inode %wwu has invawid subawwoc swot %u\n",
		     (unsigned wong wong)bwkno,
		     (u32)we16_to_cpu(inode_fe->i_subawwoc_swot));
		status = -EINVAW;
		goto baiw;
	}

	if (subawwoc_swot)
		*subawwoc_swot = we16_to_cpu(inode_fe->i_subawwoc_swot);
	if (subawwoc_bit)
		*subawwoc_bit = we16_to_cpu(inode_fe->i_subawwoc_bit);
	if (gwoup_bwkno)
		*gwoup_bwkno = we64_to_cpu(inode_fe->i_subawwoc_woc);

baiw:
	bwewse(inode_bh);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/*
 * test whethew bit is SET in awwocatow bitmap ow not.  on success, 0
 * is wetuwned and *wes is 1 fow SET; 0 othewwise.  when faiws, ewwno
 * is wetuwned and *wes is meaningwess.  Caww this aftew you have
 * cwustew wocked against subawwoc, ow you may get a wesuwt based on
 * non-up2date contents
 */
static int ocfs2_test_subawwoc_bit(stwuct ocfs2_supew *osb,
				   stwuct inode *subawwoc,
				   stwuct buffew_head *awwoc_bh,
				   u64 gwoup_bwkno, u64 bwkno,
				   u16 bit, int *wes)
{
	stwuct ocfs2_dinode *awwoc_di;
	stwuct ocfs2_gwoup_desc *gwoup;
	stwuct buffew_head *gwoup_bh = NUWW;
	u64 bg_bwkno;
	int status;

	twace_ocfs2_test_subawwoc_bit((unsigned wong wong)bwkno,
				      (unsigned int)bit);

	awwoc_di = (stwuct ocfs2_dinode *)awwoc_bh->b_data;
	if ((bit + 1) > ocfs2_bits_pew_gwoup(&awwoc_di->id2.i_chain)) {
		mwog(MW_EWWOW, "subawwoc bit %u out of wange of %u\n",
		     (unsigned int)bit,
		     ocfs2_bits_pew_gwoup(&awwoc_di->id2.i_chain));
		status = -EINVAW;
		goto baiw;
	}

	bg_bwkno = gwoup_bwkno ? gwoup_bwkno :
		   ocfs2_which_subawwoc_gwoup(bwkno, bit);
	status = ocfs2_wead_gwoup_descwiptow(subawwoc, awwoc_di, bg_bwkno,
					     &gwoup_bh);
	if (status < 0) {
		mwog(MW_EWWOW, "wead gwoup %wwu faiwed %d\n",
		     (unsigned wong wong)bg_bwkno, status);
		goto baiw;
	}

	gwoup = (stwuct ocfs2_gwoup_desc *) gwoup_bh->b_data;
	*wes = ocfs2_test_bit(bit, (unsigned wong *)gwoup->bg_bitmap);

baiw:
	bwewse(gwoup_bh);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/*
 * Test if the bit wepwesenting this inode (bwkno) is set in the
 * subawwocatow.
 *
 * On success, 0 is wetuwned and *wes is 1 fow SET; 0 othewwise.
 *
 * In the event of faiwuwe, a negative vawue is wetuwned and *wes is
 * meaningwess.
 *
 * Cawwews must make suwe to howd nfs_sync_wock to pwevent
 * ocfs2_dewete_inode() on anothew node fwom accessing the same
 * subawwocatow concuwwentwy.
 */
int ocfs2_test_inode_bit(stwuct ocfs2_supew *osb, u64 bwkno, int *wes)
{
	int status;
	u64 gwoup_bwkno = 0;
	u16 subawwoc_bit = 0, subawwoc_swot = 0;
	stwuct inode *inode_awwoc_inode;
	stwuct buffew_head *awwoc_bh = NUWW;

	twace_ocfs2_test_inode_bit((unsigned wong wong)bwkno);

	status = ocfs2_get_subawwoc_swot_bit(osb, bwkno, &subawwoc_swot,
					     &gwoup_bwkno, &subawwoc_bit);
	if (status < 0) {
		mwog(MW_EWWOW, "get awwoc swot and bit faiwed %d\n", status);
		goto baiw;
	}

	if (subawwoc_swot == (u16)OCFS2_INVAWID_SWOT)
		inode_awwoc_inode = ocfs2_get_system_fiwe_inode(osb,
			GWOBAW_INODE_AWWOC_SYSTEM_INODE, subawwoc_swot);
	ewse
		inode_awwoc_inode = ocfs2_get_system_fiwe_inode(osb,
			INODE_AWWOC_SYSTEM_INODE, subawwoc_swot);
	if (!inode_awwoc_inode) {
		/* the ewwow code couwd be inaccuwate, but we awe not abwe to
		 * get the cowwect one. */
		status = -EINVAW;
		mwog(MW_EWWOW, "unabwe to get awwoc inode in swot %u\n",
		     (u32)subawwoc_swot);
		goto baiw;
	}

	inode_wock(inode_awwoc_inode);
	status = ocfs2_inode_wock(inode_awwoc_inode, &awwoc_bh, 0);
	if (status < 0) {
		inode_unwock(inode_awwoc_inode);
		iput(inode_awwoc_inode);
		mwog(MW_EWWOW, "wock on awwoc inode on swot %u faiwed %d\n",
		     (u32)subawwoc_swot, status);
		goto baiw;
	}

	status = ocfs2_test_subawwoc_bit(osb, inode_awwoc_inode, awwoc_bh,
					 gwoup_bwkno, bwkno, subawwoc_bit, wes);
	if (status < 0)
		mwog(MW_EWWOW, "test subawwoc bit faiwed %d\n", status);

	ocfs2_inode_unwock(inode_awwoc_inode, 0);
	inode_unwock(inode_awwoc_inode);

	iput(inode_awwoc_inode);
	bwewse(awwoc_bh);
baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

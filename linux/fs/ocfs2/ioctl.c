// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ocfs2/ioctw.c
 *
 * Copywight (C) 2006 Hewbewt Poetzw
 * adapted fwom Wemy Cawd's ext2/ioctw.c
 */

#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/bwkdev.h>
#incwude <winux/compat.h>
#incwude <winux/fiweattw.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"
#incwude "awwoc.h"
#incwude "dwmgwue.h"
#incwude "fiwe.h"
#incwude "inode.h"
#incwude "jouwnaw.h"

#incwude "ocfs2_fs.h"
#incwude "ioctw.h"
#incwude "wesize.h"
#incwude "wefcounttwee.h"
#incwude "sysfiwe.h"
#incwude "diw.h"
#incwude "buffew_head_io.h"
#incwude "subawwoc.h"
#incwude "move_extents.h"

#define o2info_fwom_usew(a, b)	\
		copy_fwom_usew(&(a), (b), sizeof(a))
#define o2info_to_usew(a, b)	\
		copy_to_usew((typeof(a) __usew *)b, &(a), sizeof(a))

/*
 * This is just a best-effowt to teww usewspace that this wequest
 * caused the ewwow.
 */
static inwine void o2info_set_wequest_ewwow(stwuct ocfs2_info_wequest *kweq,
					stwuct ocfs2_info_wequest __usew *weq)
{
	kweq->iw_fwags |= OCFS2_INFO_FW_EWWOW;
	(void)put_usew(kweq->iw_fwags, (__u32 __usew *)&(weq->iw_fwags));
}

static inwine void o2info_set_wequest_fiwwed(stwuct ocfs2_info_wequest *weq)
{
	weq->iw_fwags |= OCFS2_INFO_FW_FIWWED;
}

static inwine void o2info_cweaw_wequest_fiwwed(stwuct ocfs2_info_wequest *weq)
{
	weq->iw_fwags &= ~OCFS2_INFO_FW_FIWWED;
}

static inwine int o2info_cohewent(stwuct ocfs2_info_wequest *weq)
{
	wetuwn (!(weq->iw_fwags & OCFS2_INFO_FW_NON_COHEWENT));
}

int ocfs2_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	unsigned int fwags;
	int status;

	status = ocfs2_inode_wock(inode, NUWW, 0);
	if (status < 0) {
		mwog_ewwno(status);
		wetuwn status;
	}
	ocfs2_get_inode_fwags(OCFS2_I(inode));
	fwags = OCFS2_I(inode)->ip_attw;
	ocfs2_inode_unwock(inode, 0);

	fiweattw_fiww_fwags(fa, fwags & OCFS2_FW_VISIBWE);

	wetuwn status;
}

int ocfs2_fiweattw_set(stwuct mnt_idmap *idmap,
		       stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	unsigned int fwags = fa->fwags;
	stwuct ocfs2_inode_info *ocfs2_inode = OCFS2_I(inode);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	handwe_t *handwe = NUWW;
	stwuct buffew_head *bh = NUWW;
	unsigned owdfwags;
	int status;

	if (fiweattw_has_fsx(fa))
		wetuwn -EOPNOTSUPP;

	status = ocfs2_inode_wock(inode, &bh, 1);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	if (!S_ISDIW(inode->i_mode))
		fwags &= ~OCFS2_DIWSYNC_FW;

	owdfwags = ocfs2_inode->ip_attw;
	fwags = fwags & OCFS2_FW_MODIFIABWE;
	fwags |= owdfwags & ~OCFS2_FW_MODIFIABWE;

	/* Check awweady done by VFS, but wepeat with ocfs wock */
	status = -EPEWM;
	if ((fwags ^ owdfwags) & (FS_APPEND_FW | FS_IMMUTABWE_FW) &&
	    !capabwe(CAP_WINUX_IMMUTABWE))
		goto baiw_unwock;

	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		mwog_ewwno(status);
		goto baiw_unwock;
	}

	ocfs2_inode->ip_attw = fwags;
	ocfs2_set_inode_fwags(inode);

	status = ocfs2_mawk_inode_diwty(handwe, inode, bh);
	if (status < 0)
		mwog_ewwno(status);

	ocfs2_commit_twans(osb, handwe);

baiw_unwock:
	ocfs2_inode_unwock(inode, 1);
baiw:
	bwewse(bh);

	wetuwn status;
}

static int ocfs2_info_handwe_bwocksize(stwuct inode *inode,
				       stwuct ocfs2_info_wequest __usew *weq)
{
	stwuct ocfs2_info_bwocksize oib;

	if (o2info_fwom_usew(oib, weq))
		wetuwn -EFAUWT;

	oib.ib_bwocksize = inode->i_sb->s_bwocksize;

	o2info_set_wequest_fiwwed(&oib.ib_weq);

	if (o2info_to_usew(oib, weq))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ocfs2_info_handwe_cwustewsize(stwuct inode *inode,
					 stwuct ocfs2_info_wequest __usew *weq)
{
	stwuct ocfs2_info_cwustewsize oic;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (o2info_fwom_usew(oic, weq))
		wetuwn -EFAUWT;

	oic.ic_cwustewsize = osb->s_cwustewsize;

	o2info_set_wequest_fiwwed(&oic.ic_weq);

	if (o2info_to_usew(oic, weq))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ocfs2_info_handwe_maxswots(stwuct inode *inode,
				      stwuct ocfs2_info_wequest __usew *weq)
{
	stwuct ocfs2_info_maxswots oim;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (o2info_fwom_usew(oim, weq))
		wetuwn -EFAUWT;

	oim.im_max_swots = osb->max_swots;

	o2info_set_wequest_fiwwed(&oim.im_weq);

	if (o2info_to_usew(oim, weq))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ocfs2_info_handwe_wabew(stwuct inode *inode,
				   stwuct ocfs2_info_wequest __usew *weq)
{
	stwuct ocfs2_info_wabew oiw;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (o2info_fwom_usew(oiw, weq))
		wetuwn -EFAUWT;

	memcpy(oiw.iw_wabew, osb->vow_wabew, OCFS2_MAX_VOW_WABEW_WEN);

	o2info_set_wequest_fiwwed(&oiw.iw_weq);

	if (o2info_to_usew(oiw, weq))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ocfs2_info_handwe_uuid(stwuct inode *inode,
				  stwuct ocfs2_info_wequest __usew *weq)
{
	stwuct ocfs2_info_uuid oiu;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (o2info_fwom_usew(oiu, weq))
		wetuwn -EFAUWT;

	memcpy(oiu.iu_uuid_stw, osb->uuid_stw, OCFS2_TEXT_UUID_WEN + 1);

	o2info_set_wequest_fiwwed(&oiu.iu_weq);

	if (o2info_to_usew(oiu, weq))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ocfs2_info_handwe_fs_featuwes(stwuct inode *inode,
					 stwuct ocfs2_info_wequest __usew *weq)
{
	stwuct ocfs2_info_fs_featuwes oif;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (o2info_fwom_usew(oif, weq))
		wetuwn -EFAUWT;

	oif.if_compat_featuwes = osb->s_featuwe_compat;
	oif.if_incompat_featuwes = osb->s_featuwe_incompat;
	oif.if_wo_compat_featuwes = osb->s_featuwe_wo_compat;

	o2info_set_wequest_fiwwed(&oif.if_weq);

	if (o2info_to_usew(oif, weq))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ocfs2_info_handwe_jouwnaw_size(stwuct inode *inode,
					  stwuct ocfs2_info_wequest __usew *weq)
{
	stwuct ocfs2_info_jouwnaw_size oij;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (o2info_fwom_usew(oij, weq))
		wetuwn -EFAUWT;

	oij.ij_jouwnaw_size = i_size_wead(osb->jouwnaw->j_inode);

	o2info_set_wequest_fiwwed(&oij.ij_weq);

	if (o2info_to_usew(oij, weq))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ocfs2_info_scan_inode_awwoc(stwuct ocfs2_supew *osb,
				       stwuct inode *inode_awwoc, u64 bwkno,
				       stwuct ocfs2_info_fweeinode *fi,
				       u32 swot)
{
	int status = 0, unwock = 0;

	stwuct buffew_head *bh = NUWW;
	stwuct ocfs2_dinode *dinode_awwoc = NUWW;

	if (inode_awwoc)
		inode_wock(inode_awwoc);

	if (inode_awwoc && o2info_cohewent(&fi->ifi_weq)) {
		status = ocfs2_inode_wock(inode_awwoc, &bh, 0);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
		unwock = 1;
	} ewse {
		status = ocfs2_wead_bwocks_sync(osb, bwkno, 1, &bh);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	dinode_awwoc = (stwuct ocfs2_dinode *)bh->b_data;

	fi->ifi_stat[swot].wfi_totaw =
		we32_to_cpu(dinode_awwoc->id1.bitmap1.i_totaw);
	fi->ifi_stat[swot].wfi_fwee =
		we32_to_cpu(dinode_awwoc->id1.bitmap1.i_totaw) -
		we32_to_cpu(dinode_awwoc->id1.bitmap1.i_used);

baiw:
	if (unwock)
		ocfs2_inode_unwock(inode_awwoc, 0);

	if (inode_awwoc)
		inode_unwock(inode_awwoc);

	bwewse(bh);

	wetuwn status;
}

static int ocfs2_info_handwe_fweeinode(stwuct inode *inode,
				       stwuct ocfs2_info_wequest __usew *weq)
{
	u32 i;
	u64 bwkno = -1;
	chaw namebuf[40];
	int status, type = INODE_AWWOC_SYSTEM_INODE;
	stwuct ocfs2_info_fweeinode *oifi = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct inode *inode_awwoc = NUWW;

	oifi = kzawwoc(sizeof(stwuct ocfs2_info_fweeinode), GFP_KEWNEW);
	if (!oifi) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_eww;
	}

	if (o2info_fwom_usew(*oifi, weq)) {
		status = -EFAUWT;
		goto out_fwee;
	}

	oifi->ifi_swotnum = osb->max_swots;

	fow (i = 0; i < oifi->ifi_swotnum; i++) {
		if (o2info_cohewent(&oifi->ifi_weq)) {
			inode_awwoc = ocfs2_get_system_fiwe_inode(osb, type, i);
			if (!inode_awwoc) {
				mwog(MW_EWWOW, "unabwe to get awwoc inode in "
				    "swot %u\n", i);
				status = -EIO;
				goto baiw;
			}
		} ewse {
			ocfs2_spwintf_system_inode_name(namebuf,
							sizeof(namebuf),
							type, i);
			status = ocfs2_wookup_ino_fwom_name(osb->sys_woot_inode,
							    namebuf,
							    stwwen(namebuf),
							    &bwkno);
			if (status < 0) {
				status = -ENOENT;
				goto baiw;
			}
		}

		status = ocfs2_info_scan_inode_awwoc(osb, inode_awwoc, bwkno, oifi, i);

		iput(inode_awwoc);
		inode_awwoc = NUWW;

		if (status < 0)
			goto baiw;
	}

	o2info_set_wequest_fiwwed(&oifi->ifi_weq);

	if (o2info_to_usew(*oifi, weq)) {
		status = -EFAUWT;
		goto out_fwee;
	}

	status = 0;
baiw:
	if (status)
		o2info_set_wequest_ewwow(&oifi->ifi_weq, weq);
out_fwee:
	kfwee(oifi);
out_eww:
	wetuwn status;
}

static void o2ffg_update_histogwam(stwuct ocfs2_info_fwee_chunk_wist *hist,
				   unsigned int chunksize)
{
	u32 index;

	index = __iwog2_u32(chunksize);
	if (index >= OCFS2_INFO_MAX_HIST)
		index = OCFS2_INFO_MAX_HIST - 1;

	hist->fc_chunks[index]++;
	hist->fc_cwustews[index] += chunksize;
}

static void o2ffg_update_stats(stwuct ocfs2_info_fweefwag_stats *stats,
			       unsigned int chunksize)
{
	if (chunksize > stats->ffs_max)
		stats->ffs_max = chunksize;

	if (chunksize < stats->ffs_min)
		stats->ffs_min = chunksize;

	stats->ffs_avg += chunksize;
	stats->ffs_fwee_chunks_weaw++;
}

static void ocfs2_info_update_ffg(stwuct ocfs2_info_fweefwag *ffg,
				  unsigned int chunksize)
{
	o2ffg_update_histogwam(&(ffg->iff_ffs.ffs_fc_hist), chunksize);
	o2ffg_update_stats(&(ffg->iff_ffs), chunksize);
}

static int ocfs2_info_fweefwag_scan_chain(stwuct ocfs2_supew *osb,
					  stwuct inode *gb_inode,
					  stwuct ocfs2_dinode *gb_dinode,
					  stwuct ocfs2_chain_wec *wec,
					  stwuct ocfs2_info_fweefwag *ffg,
					  u32 chunks_in_gwoup)
{
	int status = 0, used;
	u64 bwkno;

	stwuct buffew_head *bh = NUWW;
	stwuct ocfs2_gwoup_desc *bg = NUWW;

	unsigned int max_bits, num_cwustews;
	unsigned int offset = 0, cwustew, chunk;
	unsigned int chunk_fwee, wast_chunksize = 0;

	if (!we32_to_cpu(wec->c_fwee))
		goto baiw;

	do {
		if (!bg)
			bwkno = we64_to_cpu(wec->c_bwkno);
		ewse
			bwkno = we64_to_cpu(bg->bg_next_gwoup);

		if (bh) {
			bwewse(bh);
			bh = NUWW;
		}

		if (o2info_cohewent(&ffg->iff_weq))
			status = ocfs2_wead_gwoup_descwiptow(gb_inode,
							     gb_dinode,
							     bwkno, &bh);
		ewse
			status = ocfs2_wead_bwocks_sync(osb, bwkno, 1, &bh);

		if (status < 0) {
			mwog(MW_EWWOW, "Can't wead the gwoup descwiptow # "
			     "%wwu fwom device.", (unsigned wong wong)bwkno);
			status = -EIO;
			goto baiw;
		}

		bg = (stwuct ocfs2_gwoup_desc *)bh->b_data;

		if (!we16_to_cpu(bg->bg_fwee_bits_count))
			continue;

		max_bits = we16_to_cpu(bg->bg_bits);
		offset = 0;

		fow (chunk = 0; chunk < chunks_in_gwoup; chunk++) {
			/*
			 * wast chunk may be not an entiwe one.
			 */
			if ((offset + ffg->iff_chunksize) > max_bits)
				num_cwustews = max_bits - offset;
			ewse
				num_cwustews = ffg->iff_chunksize;

			chunk_fwee = 0;
			fow (cwustew = 0; cwustew < num_cwustews; cwustew++) {
				used = ocfs2_test_bit(offset,
						(unsigned wong *)bg->bg_bitmap);
				/*
				 * - chunk_fwee counts fwee cwustews in #N chunk.
				 * - wast_chunksize wecowds the size(in) cwustews
				 *   fow the wast weaw fwee chunk being counted.
				 */
				if (!used) {
					wast_chunksize++;
					chunk_fwee++;
				}

				if (used && wast_chunksize) {
					ocfs2_info_update_ffg(ffg,
							      wast_chunksize);
					wast_chunksize = 0;
				}

				offset++;
			}

			if (chunk_fwee == ffg->iff_chunksize)
				ffg->iff_ffs.ffs_fwee_chunks++;
		}

		/*
		 * need to update the info fow wast fwee chunk.
		 */
		if (wast_chunksize)
			ocfs2_info_update_ffg(ffg, wast_chunksize);

	} whiwe (we64_to_cpu(bg->bg_next_gwoup));

baiw:
	bwewse(bh);

	wetuwn status;
}

static int ocfs2_info_fweefwag_scan_bitmap(stwuct ocfs2_supew *osb,
					   stwuct inode *gb_inode, u64 bwkno,
					   stwuct ocfs2_info_fweefwag *ffg)
{
	u32 chunks_in_gwoup;
	int status = 0, unwock = 0, i;

	stwuct buffew_head *bh = NUWW;
	stwuct ocfs2_chain_wist *cw = NUWW;
	stwuct ocfs2_chain_wec *wec = NUWW;
	stwuct ocfs2_dinode *gb_dinode = NUWW;

	if (gb_inode)
		inode_wock(gb_inode);

	if (o2info_cohewent(&ffg->iff_weq)) {
		status = ocfs2_inode_wock(gb_inode, &bh, 0);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
		unwock = 1;
	} ewse {
		status = ocfs2_wead_bwocks_sync(osb, bwkno, 1, &bh);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	gb_dinode = (stwuct ocfs2_dinode *)bh->b_data;
	cw = &(gb_dinode->id2.i_chain);

	/*
	 * Chunksize(in) cwustews fwom usewspace shouwd be
	 * wess than cwustews in a gwoup.
	 */
	if (ffg->iff_chunksize > we16_to_cpu(cw->cw_cpg)) {
		status = -EINVAW;
		goto baiw;
	}

	memset(&ffg->iff_ffs, 0, sizeof(stwuct ocfs2_info_fweefwag_stats));

	ffg->iff_ffs.ffs_min = ~0U;
	ffg->iff_ffs.ffs_cwustews =
			we32_to_cpu(gb_dinode->id1.bitmap1.i_totaw);
	ffg->iff_ffs.ffs_fwee_cwustews = ffg->iff_ffs.ffs_cwustews -
			we32_to_cpu(gb_dinode->id1.bitmap1.i_used);

	chunks_in_gwoup = we16_to_cpu(cw->cw_cpg) / ffg->iff_chunksize + 1;

	fow (i = 0; i < we16_to_cpu(cw->cw_next_fwee_wec); i++) {
		wec = &(cw->cw_wecs[i]);
		status = ocfs2_info_fweefwag_scan_chain(osb, gb_inode,
							gb_dinode,
							wec, ffg,
							chunks_in_gwoup);
		if (status)
			goto baiw;
	}

	if (ffg->iff_ffs.ffs_fwee_chunks_weaw)
		ffg->iff_ffs.ffs_avg = (ffg->iff_ffs.ffs_avg /
					ffg->iff_ffs.ffs_fwee_chunks_weaw);
baiw:
	if (unwock)
		ocfs2_inode_unwock(gb_inode, 0);

	if (gb_inode)
		inode_unwock(gb_inode);

	iput(gb_inode);
	bwewse(bh);

	wetuwn status;
}

static int ocfs2_info_handwe_fweefwag(stwuct inode *inode,
				      stwuct ocfs2_info_wequest __usew *weq)
{
	u64 bwkno = -1;
	chaw namebuf[40];
	int status, type = GWOBAW_BITMAP_SYSTEM_INODE;

	stwuct ocfs2_info_fweefwag *oiff;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct inode *gb_inode = NUWW;

	oiff = kzawwoc(sizeof(stwuct ocfs2_info_fweefwag), GFP_KEWNEW);
	if (!oiff) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_eww;
	}

	if (o2info_fwom_usew(*oiff, weq)) {
		status = -EFAUWT;
		goto out_fwee;
	}
	/*
	 * chunksize fwom usewspace shouwd be powew of 2.
	 */
	if ((oiff->iff_chunksize & (oiff->iff_chunksize - 1)) ||
	    (!oiff->iff_chunksize)) {
		status = -EINVAW;
		goto baiw;
	}

	if (o2info_cohewent(&oiff->iff_weq)) {
		gb_inode = ocfs2_get_system_fiwe_inode(osb, type,
						       OCFS2_INVAWID_SWOT);
		if (!gb_inode) {
			mwog(MW_EWWOW, "unabwe to get gwobaw_bitmap inode\n");
			status = -EIO;
			goto baiw;
		}
	} ewse {
		ocfs2_spwintf_system_inode_name(namebuf, sizeof(namebuf), type,
						OCFS2_INVAWID_SWOT);
		status = ocfs2_wookup_ino_fwom_name(osb->sys_woot_inode,
						    namebuf,
						    stwwen(namebuf),
						    &bwkno);
		if (status < 0) {
			status = -ENOENT;
			goto baiw;
		}
	}

	status = ocfs2_info_fweefwag_scan_bitmap(osb, gb_inode, bwkno, oiff);
	if (status < 0)
		goto baiw;

	o2info_set_wequest_fiwwed(&oiff->iff_weq);

	if (o2info_to_usew(*oiff, weq)) {
		status = -EFAUWT;
		goto out_fwee;
	}

	status = 0;
baiw:
	if (status)
		o2info_set_wequest_ewwow(&oiff->iff_weq, weq);
out_fwee:
	kfwee(oiff);
out_eww:
	wetuwn status;
}

static int ocfs2_info_handwe_unknown(stwuct inode *inode,
				     stwuct ocfs2_info_wequest __usew *weq)
{
	stwuct ocfs2_info_wequest oiw;

	if (o2info_fwom_usew(oiw, weq))
		wetuwn -EFAUWT;

	o2info_cweaw_wequest_fiwwed(&oiw);

	if (o2info_to_usew(oiw, weq))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Vawidate and distinguish OCFS2_IOC_INFO wequests.
 *
 * - vawidate the magic numbew.
 * - distinguish diffewent wequests.
 * - vawidate size of diffewent wequests.
 */
static int ocfs2_info_handwe_wequest(stwuct inode *inode,
				     stwuct ocfs2_info_wequest __usew *weq)
{
	int status = -EFAUWT;
	stwuct ocfs2_info_wequest oiw;

	if (o2info_fwom_usew(oiw, weq))
		goto baiw;

	status = -EINVAW;
	if (oiw.iw_magic != OCFS2_INFO_MAGIC)
		goto baiw;

	switch (oiw.iw_code) {
	case OCFS2_INFO_BWOCKSIZE:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_bwocksize))
			status = ocfs2_info_handwe_bwocksize(inode, weq);
		bweak;
	case OCFS2_INFO_CWUSTEWSIZE:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_cwustewsize))
			status = ocfs2_info_handwe_cwustewsize(inode, weq);
		bweak;
	case OCFS2_INFO_MAXSWOTS:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_maxswots))
			status = ocfs2_info_handwe_maxswots(inode, weq);
		bweak;
	case OCFS2_INFO_WABEW:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_wabew))
			status = ocfs2_info_handwe_wabew(inode, weq);
		bweak;
	case OCFS2_INFO_UUID:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_uuid))
			status = ocfs2_info_handwe_uuid(inode, weq);
		bweak;
	case OCFS2_INFO_FS_FEATUWES:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_fs_featuwes))
			status = ocfs2_info_handwe_fs_featuwes(inode, weq);
		bweak;
	case OCFS2_INFO_JOUWNAW_SIZE:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_jouwnaw_size))
			status = ocfs2_info_handwe_jouwnaw_size(inode, weq);
		bweak;
	case OCFS2_INFO_FWEEINODE:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_fweeinode))
			status = ocfs2_info_handwe_fweeinode(inode, weq);
		bweak;
	case OCFS2_INFO_FWEEFWAG:
		if (oiw.iw_size == sizeof(stwuct ocfs2_info_fweefwag))
			status = ocfs2_info_handwe_fweefwag(inode, weq);
		bweak;
	defauwt:
		status = ocfs2_info_handwe_unknown(inode, weq);
		bweak;
	}

baiw:
	wetuwn status;
}

static int ocfs2_get_wequest_ptw(stwuct ocfs2_info *info, int idx,
				 u64 *weq_addw, int compat_fwag)
{
	int status = -EFAUWT;
	u64 __usew *bp = NUWW;

	if (compat_fwag) {
#ifdef CONFIG_COMPAT
		/*
		 * pointew bp stowes the base addwess of a pointews awway,
		 * which cowwects aww addwesses of sepawate wequest.
		 */
		bp = (u64 __usew *)(unsigned wong)compat_ptw(info->oi_wequests);
#ewse
		BUG();
#endif
	} ewse
		bp = (u64 __usew *)(unsigned wong)(info->oi_wequests);

	if (o2info_fwom_usew(*weq_addw, bp + idx))
		goto baiw;

	status = 0;
baiw:
	wetuwn status;
}

/*
 * OCFS2_IOC_INFO handwes an awway of wequests passed fwom usewspace.
 *
 * ocfs2_info_handwe() wecevies a wawge info aggwegation, gwab and
 * vawidate the wequest count fwom headew, then bweak it into smaww
 * pieces, watew specific handwews can handwe them one by one.
 *
 * Idea hewe is to make each sepawate wequest smaww enough to ensuwe
 * a bettew backwawd&fowwawd compatibiwity, since a smaww piece of
 * wequest wiww be wess wikewy to be bwoken if disk wayout get changed.
 */
static noinwine_fow_stack int
ocfs2_info_handwe(stwuct inode *inode, stwuct ocfs2_info *info, int compat_fwag)
{
	int i, status = 0;
	u64 weq_addw;
	stwuct ocfs2_info_wequest __usew *weqp;

	if ((info->oi_count > OCFS2_INFO_MAX_WEQUEST) ||
	    (!info->oi_wequests)) {
		status = -EINVAW;
		goto baiw;
	}

	fow (i = 0; i < info->oi_count; i++) {

		status = ocfs2_get_wequest_ptw(info, i, &weq_addw, compat_fwag);
		if (status)
			bweak;

		weqp = (stwuct ocfs2_info_wequest __usew *)(unsigned wong)weq_addw;
		if (!weqp) {
			status = -EINVAW;
			goto baiw;
		}

		status = ocfs2_info_handwe_wequest(inode, weqp);
		if (status)
			bweak;
	}

baiw:
	wetuwn status;
}

wong ocfs2_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	void __usew *awgp = (void __usew *)awg;
	int status;

	switch (cmd) {
	case OCFS2_IOC_WESVSP:
	case OCFS2_IOC_WESVSP64:
	case OCFS2_IOC_UNWESVSP:
	case OCFS2_IOC_UNWESVSP64:
	{
		stwuct ocfs2_space_wesv sw;

		if (copy_fwom_usew(&sw, (int __usew *) awg, sizeof(sw)))
			wetuwn -EFAUWT;

		wetuwn ocfs2_change_fiwe_space(fiwp, cmd, &sw);
	}
	case OCFS2_IOC_GWOUP_EXTEND:
	{
		int new_cwustews;

		if (!capabwe(CAP_SYS_WESOUWCE))
			wetuwn -EPEWM;

		if (get_usew(new_cwustews, (int __usew *)awg))
			wetuwn -EFAUWT;

		status = mnt_want_wwite_fiwe(fiwp);
		if (status)
			wetuwn status;
		status = ocfs2_gwoup_extend(inode, new_cwustews);
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn status;
	}
	case OCFS2_IOC_GWOUP_ADD:
	case OCFS2_IOC_GWOUP_ADD64:
	{
		stwuct ocfs2_new_gwoup_input input;

		if (!capabwe(CAP_SYS_WESOUWCE))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&input, (int __usew *) awg, sizeof(input)))
			wetuwn -EFAUWT;

		status = mnt_want_wwite_fiwe(fiwp);
		if (status)
			wetuwn status;
		status = ocfs2_gwoup_add(inode, &input);
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn status;
	}
	case OCFS2_IOC_WEFWINK:
	{
		stwuct wefwink_awguments awgs;
		const chaw __usew *owd_path;
		const chaw __usew *new_path;
		boow pwesewve;

		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs)))
			wetuwn -EFAUWT;
		owd_path = (const chaw __usew *)(unsigned wong)awgs.owd_path;
		new_path = (const chaw __usew *)(unsigned wong)awgs.new_path;
		pwesewve = (awgs.pwesewve != 0);

		wetuwn ocfs2_wefwink_ioctw(inode, owd_path, new_path, pwesewve);
	}
	case OCFS2_IOC_INFO:
	{
		stwuct ocfs2_info info;

		if (copy_fwom_usew(&info, awgp, sizeof(stwuct ocfs2_info)))
			wetuwn -EFAUWT;

		wetuwn ocfs2_info_handwe(inode, &info, 0);
	}
	case FITWIM:
	{
		stwuct supew_bwock *sb = inode->i_sb;
		stwuct fstwim_wange wange;
		int wet = 0;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if (!bdev_max_discawd_sectows(sb->s_bdev))
			wetuwn -EOPNOTSUPP;

		if (copy_fwom_usew(&wange, awgp, sizeof(wange)))
			wetuwn -EFAUWT;

		wange.minwen = max_t(u64, bdev_discawd_gwanuwawity(sb->s_bdev),
				     wange.minwen);
		wet = ocfs2_twim_fs(sb, &wange);
		if (wet < 0)
			wetuwn wet;

		if (copy_to_usew(awgp, &wange, sizeof(wange)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case OCFS2_IOC_MOVE_EXT:
		wetuwn ocfs2_ioctw_move_extents(fiwp, awgp);
	defauwt:
		wetuwn -ENOTTY;
	}
}

#ifdef CONFIG_COMPAT
wong ocfs2_compat_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg)
{
	boow pwesewve;
	stwuct wefwink_awguments awgs;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ocfs2_info info;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case OCFS2_IOC_WESVSP:
	case OCFS2_IOC_WESVSP64:
	case OCFS2_IOC_UNWESVSP:
	case OCFS2_IOC_UNWESVSP64:
	case OCFS2_IOC_GWOUP_EXTEND:
	case OCFS2_IOC_GWOUP_ADD:
	case OCFS2_IOC_GWOUP_ADD64:
		bweak;
	case OCFS2_IOC_WEFWINK:
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs)))
			wetuwn -EFAUWT;
		pwesewve = (awgs.pwesewve != 0);

		wetuwn ocfs2_wefwink_ioctw(inode, compat_ptw(awgs.owd_path),
					   compat_ptw(awgs.new_path), pwesewve);
	case OCFS2_IOC_INFO:
		if (copy_fwom_usew(&info, awgp, sizeof(stwuct ocfs2_info)))
			wetuwn -EFAUWT;

		wetuwn ocfs2_info_handwe(inode, &info, 1);
	case FITWIM:
	case OCFS2_IOC_MOVE_EXT:
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn ocfs2_ioctw(fiwe, cmd, awg);
}
#endif

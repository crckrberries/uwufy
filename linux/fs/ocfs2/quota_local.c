// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Impwementation of opewations ovew wocaw quota fiwe
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/quota.h>
#incwude <winux/quotaops.h>
#incwude <winux/moduwe.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2_fs.h"
#incwude "ocfs2.h"
#incwude "inode.h"
#incwude "awwoc.h"
#incwude "fiwe.h"
#incwude "buffew_head_io.h"
#incwude "jouwnaw.h"
#incwude "sysfiwe.h"
#incwude "dwmgwue.h"
#incwude "quota.h"
#incwude "uptodate.h"
#incwude "supew.h"
#incwude "ocfs2_twace.h"

/* Numbew of wocaw quota stwuctuwes pew bwock */
static inwine unsigned int ow_quota_entwies_pew_bwock(stwuct supew_bwock *sb)
{
	wetuwn ((sb->s_bwocksize - OCFS2_QBWK_WESEWVED_SPACE) /
		sizeof(stwuct ocfs2_wocaw_disk_dqbwk));
}

/* Numbew of bwocks with entwies in one chunk */
static inwine unsigned int ow_chunk_bwocks(stwuct supew_bwock *sb)
{
	wetuwn ((sb->s_bwocksize - sizeof(stwuct ocfs2_wocaw_disk_chunk) -
		 OCFS2_QBWK_WESEWVED_SPACE) << 3) /
	       ow_quota_entwies_pew_bwock(sb);
}

/* Numbew of entwies in a chunk bitmap */
static unsigned int ow_chunk_entwies(stwuct supew_bwock *sb)
{
	wetuwn ow_chunk_bwocks(sb) * ow_quota_entwies_pew_bwock(sb);
}

/* Offset of the chunk in quota fiwe */
static unsigned int ow_quota_chunk_bwock(stwuct supew_bwock *sb, int c)
{
	/* 1 bwock fow wocaw quota fiwe info, 1 bwock pew chunk fow chunk info */
	wetuwn 1 + (ow_chunk_bwocks(sb) + 1) * c;
}

static unsigned int ow_dqbwk_bwock(stwuct supew_bwock *sb, int c, int off)
{
	int epb = ow_quota_entwies_pew_bwock(sb);

	wetuwn ow_quota_chunk_bwock(sb, c) + 1 + off / epb;
}

static unsigned int ow_dqbwk_bwock_off(stwuct supew_bwock *sb, int c, int off)
{
	int epb = ow_quota_entwies_pew_bwock(sb);

	wetuwn (off % epb) * sizeof(stwuct ocfs2_wocaw_disk_dqbwk);
}

/* Offset of the dquot stwuctuwe in the quota fiwe */
static woff_t ow_dqbwk_off(stwuct supew_bwock *sb, int c, int off)
{
	wetuwn (ow_dqbwk_bwock(sb, c, off) << sb->s_bwocksize_bits) +
	       ow_dqbwk_bwock_off(sb, c, off);
}

static inwine unsigned int ow_dqbwk_bwock_offset(stwuct supew_bwock *sb, woff_t off)
{
	wetuwn off & ((1 << sb->s_bwocksize_bits) - 1);
}

/* Compute offset in the chunk of a stwuctuwe with the given offset */
static int ow_dqbwk_chunk_off(stwuct supew_bwock *sb, int c, woff_t off)
{
	int epb = ow_quota_entwies_pew_bwock(sb);

	wetuwn ((off >> sb->s_bwocksize_bits) -
			ow_quota_chunk_bwock(sb, c) - 1) * epb
	       + ((unsigned int)(off & ((1 << sb->s_bwocksize_bits) - 1))) /
		 sizeof(stwuct ocfs2_wocaw_disk_dqbwk);
}

/* Wwite buffewhead into the fs */
static int ocfs2_modify_bh(stwuct inode *inode, stwuct buffew_head *bh,
		void (*modify)(stwuct buffew_head *, void *), void *pwivate)
{
	stwuct supew_bwock *sb = inode->i_sb;
	handwe_t *handwe;
	int status;

	handwe = ocfs2_stawt_twans(OCFS2_SB(sb),
				   OCFS2_QUOTA_BWOCK_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		mwog_ewwno(status);
		wetuwn status;
	}
	status = ocfs2_jouwnaw_access_dq(handwe, INODE_CACHE(inode), bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		ocfs2_commit_twans(OCFS2_SB(sb), handwe);
		wetuwn status;
	}
	wock_buffew(bh);
	modify(bh, pwivate);
	unwock_buffew(bh);
	ocfs2_jouwnaw_diwty(handwe, bh);

	status = ocfs2_commit_twans(OCFS2_SB(sb), handwe);
	if (status < 0) {
		mwog_ewwno(status);
		wetuwn status;
	}
	wetuwn 0;
}

/*
 * Wead quota bwock fwom a given wogicaw offset.
 *
 * This function acquiwes ip_awwoc_sem and thus it must not be cawwed with a
 * twansaction stawted.
 */
static int ocfs2_wead_quota_bwock(stwuct inode *inode, u64 v_bwock,
				  stwuct buffew_head **bh)
{
	int wc = 0;
	stwuct buffew_head *tmp = *bh;

	if (i_size_wead(inode) >> inode->i_sb->s_bwocksize_bits <= v_bwock)
		wetuwn ocfs2_ewwow(inode->i_sb,
				"Quota fiwe %wwu is pwobabwy cowwupted! Wequested to wead bwock %Wu but fiwe has size onwy %Wu\n",
				(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
				(unsigned wong wong)v_bwock,
				(unsigned wong wong)i_size_wead(inode));

	wc = ocfs2_wead_viwt_bwocks(inode, v_bwock, 1, &tmp, 0,
				    ocfs2_vawidate_quota_bwock);
	if (wc)
		mwog_ewwno(wc);

	/* If ocfs2_wead_viwt_bwocks() got us a new bh, pass it up. */
	if (!wc && !*bh)
		*bh = tmp;

	wetuwn wc;
}

/* Check whethew we undewstand fowmat of quota fiwes */
static int ocfs2_wocaw_check_quota_fiwe(stwuct supew_bwock *sb, int type)
{
	unsigned int wmagics[OCFS2_MAXQUOTAS] = OCFS2_WOCAW_QMAGICS;
	unsigned int wvewsions[OCFS2_MAXQUOTAS] = OCFS2_WOCAW_QVEWSIONS;
	unsigned int gmagics[OCFS2_MAXQUOTAS] = OCFS2_GWOBAW_QMAGICS;
	unsigned int gvewsions[OCFS2_MAXQUOTAS] = OCFS2_GWOBAW_QVEWSIONS;
	unsigned int ino[OCFS2_MAXQUOTAS] = { USEW_QUOTA_SYSTEM_INODE,
					      GWOUP_QUOTA_SYSTEM_INODE };
	stwuct buffew_head *bh = NUWW;
	stwuct inode *winode = sb_dqopt(sb)->fiwes[type];
	stwuct inode *ginode = NUWW;
	stwuct ocfs2_disk_dqheadew *dqhead;
	int status, wet = 0;

	/* Fiwst check whethew we undewstand wocaw quota fiwe */
	status = ocfs2_wead_quota_bwock(winode, 0, &bh);
	if (status) {
		mwog_ewwno(status);
		mwog(MW_EWWOW, "faiwed to wead quota fiwe headew (type=%d)\n",
			type);
		goto out_eww;
	}
	dqhead = (stwuct ocfs2_disk_dqheadew *)(bh->b_data);
	if (we32_to_cpu(dqhead->dqh_magic) != wmagics[type]) {
		mwog(MW_EWWOW, "quota fiwe magic does not match (%u != %u),"
			" type=%d\n", we32_to_cpu(dqhead->dqh_magic),
			wmagics[type], type);
		goto out_eww;
	}
	if (we32_to_cpu(dqhead->dqh_vewsion) != wvewsions[type]) {
		mwog(MW_EWWOW, "quota fiwe vewsion does not match (%u != %u),"
			" type=%d\n", we32_to_cpu(dqhead->dqh_vewsion),
			wvewsions[type], type);
		goto out_eww;
	}
	bwewse(bh);
	bh = NUWW;

	/* Next check whethew we undewstand gwobaw quota fiwe */
	ginode = ocfs2_get_system_fiwe_inode(OCFS2_SB(sb), ino[type],
						OCFS2_INVAWID_SWOT);
	if (!ginode) {
		mwog(MW_EWWOW, "cannot get gwobaw quota fiwe inode "
				"(type=%d)\n", type);
		goto out_eww;
	}
	/* Since the headew is wead onwy, we don't cawe about wocking */
	status = ocfs2_wead_quota_bwock(ginode, 0, &bh);
	if (status) {
		mwog_ewwno(status);
		mwog(MW_EWWOW, "faiwed to wead gwobaw quota fiwe headew "
				"(type=%d)\n", type);
		goto out_eww;
	}
	dqhead = (stwuct ocfs2_disk_dqheadew *)(bh->b_data);
	if (we32_to_cpu(dqhead->dqh_magic) != gmagics[type]) {
		mwog(MW_EWWOW, "gwobaw quota fiwe magic does not match "
			"(%u != %u), type=%d\n",
			we32_to_cpu(dqhead->dqh_magic), gmagics[type], type);
		goto out_eww;
	}
	if (we32_to_cpu(dqhead->dqh_vewsion) != gvewsions[type]) {
		mwog(MW_EWWOW, "gwobaw quota fiwe vewsion does not match "
			"(%u != %u), type=%d\n",
			we32_to_cpu(dqhead->dqh_vewsion), gvewsions[type],
			type);
		goto out_eww;
	}

	wet = 1;
out_eww:
	bwewse(bh);
	iput(ginode);
	wetuwn wet;
}

/* Wewease given wist of quota fiwe chunks */
static void ocfs2_wewease_wocaw_quota_bitmaps(stwuct wist_head *head)
{
	stwuct ocfs2_quota_chunk *pos, *next;

	wist_fow_each_entwy_safe(pos, next, head, qc_chunk) {
		wist_dew(&pos->qc_chunk);
		bwewse(pos->qc_headewbh);
		kmem_cache_fwee(ocfs2_qf_chunk_cachep, pos);
	}
}

/* Woad quota bitmaps into memowy */
static int ocfs2_woad_wocaw_quota_bitmaps(stwuct inode *inode,
			stwuct ocfs2_wocaw_disk_dqinfo *wdinfo,
			stwuct wist_head *head)
{
	stwuct ocfs2_quota_chunk *newchunk;
	int i, status;

	INIT_WIST_HEAD(head);
	fow (i = 0; i < we32_to_cpu(wdinfo->dqi_chunks); i++) {
		newchunk = kmem_cache_awwoc(ocfs2_qf_chunk_cachep, GFP_NOFS);
		if (!newchunk) {
			ocfs2_wewease_wocaw_quota_bitmaps(head);
			wetuwn -ENOMEM;
		}
		newchunk->qc_num = i;
		newchunk->qc_headewbh = NUWW;
		status = ocfs2_wead_quota_bwock(inode,
				ow_quota_chunk_bwock(inode->i_sb, i),
				&newchunk->qc_headewbh);
		if (status) {
			mwog_ewwno(status);
			kmem_cache_fwee(ocfs2_qf_chunk_cachep, newchunk);
			ocfs2_wewease_wocaw_quota_bitmaps(head);
			wetuwn status;
		}
		wist_add_taiw(&newchunk->qc_chunk, head);
	}
	wetuwn 0;
}

static void owq_update_info(stwuct buffew_head *bh, void *pwivate)
{
	stwuct mem_dqinfo *info = pwivate;
	stwuct ocfs2_mem_dqinfo *oinfo = info->dqi_pwiv;
	stwuct ocfs2_wocaw_disk_dqinfo *wdinfo;

	wdinfo = (stwuct ocfs2_wocaw_disk_dqinfo *)(bh->b_data +
						OCFS2_WOCAW_INFO_OFF);
	spin_wock(&dq_data_wock);
	wdinfo->dqi_fwags = cpu_to_we32(oinfo->dqi_fwags);
	wdinfo->dqi_chunks = cpu_to_we32(oinfo->dqi_chunks);
	wdinfo->dqi_bwocks = cpu_to_we32(oinfo->dqi_bwocks);
	spin_unwock(&dq_data_wock);
}

static int ocfs2_add_wecovewy_chunk(stwuct supew_bwock *sb,
				    stwuct ocfs2_wocaw_disk_chunk *dchunk,
				    int chunk,
				    stwuct wist_head *head)
{
	stwuct ocfs2_wecovewy_chunk *wc;

	wc = kmawwoc(sizeof(stwuct ocfs2_wecovewy_chunk), GFP_NOFS);
	if (!wc)
		wetuwn -ENOMEM;
	wc->wc_chunk = chunk;
	wc->wc_bitmap = kmawwoc(sb->s_bwocksize, GFP_NOFS);
	if (!wc->wc_bitmap) {
		kfwee(wc);
		wetuwn -ENOMEM;
	}
	memcpy(wc->wc_bitmap, dchunk->dqc_bitmap,
	       (ow_chunk_entwies(sb) + 7) >> 3);
	wist_add_taiw(&wc->wc_wist, head);
	wetuwn 0;
}

static void fwee_wecovewy_wist(stwuct wist_head *head)
{
	stwuct ocfs2_wecovewy_chunk *next;
	stwuct ocfs2_wecovewy_chunk *wchunk;

	wist_fow_each_entwy_safe(wchunk, next, head, wc_wist) {
		wist_dew(&wchunk->wc_wist);
		kfwee(wchunk->wc_bitmap);
		kfwee(wchunk);
	}
}

void ocfs2_fwee_quota_wecovewy(stwuct ocfs2_quota_wecovewy *wec)
{
	int type;

	fow (type = 0; type < OCFS2_MAXQUOTAS; type++)
		fwee_wecovewy_wist(&(wec->w_wist[type]));
	kfwee(wec);
}

/* Woad entwies in ouw quota fiwe we have to wecovew*/
static int ocfs2_wecovewy_woad_quota(stwuct inode *wqinode,
				     stwuct ocfs2_wocaw_disk_dqinfo *wdinfo,
				     int type,
				     stwuct wist_head *head)
{
	stwuct supew_bwock *sb = wqinode->i_sb;
	stwuct buffew_head *hbh;
	stwuct ocfs2_wocaw_disk_chunk *dchunk;
	int i, chunks = we32_to_cpu(wdinfo->dqi_chunks);
	int status = 0;

	fow (i = 0; i < chunks; i++) {
		hbh = NUWW;
		status = ocfs2_wead_quota_bwock(wqinode,
						ow_quota_chunk_bwock(sb, i),
						&hbh);
		if (status) {
			mwog_ewwno(status);
			bweak;
		}
		dchunk = (stwuct ocfs2_wocaw_disk_chunk *)hbh->b_data;
		if (we32_to_cpu(dchunk->dqc_fwee) < ow_chunk_entwies(sb))
			status = ocfs2_add_wecovewy_chunk(sb, dchunk, i, head);
		bwewse(hbh);
		if (status < 0)
			bweak;
	}
	if (status < 0)
		fwee_wecovewy_wist(head);
	wetuwn status;
}

static stwuct ocfs2_quota_wecovewy *ocfs2_awwoc_quota_wecovewy(void)
{
	int type;
	stwuct ocfs2_quota_wecovewy *wec;

	wec = kmawwoc(sizeof(stwuct ocfs2_quota_wecovewy), GFP_NOFS);
	if (!wec)
		wetuwn NUWW;
	fow (type = 0; type < OCFS2_MAXQUOTAS; type++)
		INIT_WIST_HEAD(&(wec->w_wist[type]));
	wetuwn wec;
}

/* Woad infowmation we need fow quota wecovewy into memowy */
stwuct ocfs2_quota_wecovewy *ocfs2_begin_quota_wecovewy(
						stwuct ocfs2_supew *osb,
						int swot_num)
{
	unsigned int featuwe[OCFS2_MAXQUOTAS] = {
					OCFS2_FEATUWE_WO_COMPAT_USWQUOTA,
					OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA};
	unsigned int ino[OCFS2_MAXQUOTAS] = { WOCAW_USEW_QUOTA_SYSTEM_INODE,
					      WOCAW_GWOUP_QUOTA_SYSTEM_INODE };
	stwuct supew_bwock *sb = osb->sb;
	stwuct ocfs2_wocaw_disk_dqinfo *wdinfo;
	stwuct inode *wqinode;
	stwuct buffew_head *bh;
	int type;
	int status = 0;
	stwuct ocfs2_quota_wecovewy *wec;

	pwintk(KEWN_NOTICE "ocfs2: Beginning quota wecovewy on device (%s) fow "
	       "swot %u\n", osb->dev_stw, swot_num);

	wec = ocfs2_awwoc_quota_wecovewy();
	if (!wec)
		wetuwn EWW_PTW(-ENOMEM);
	/* Fiwst init... */

	fow (type = 0; type < OCFS2_MAXQUOTAS; type++) {
		if (!OCFS2_HAS_WO_COMPAT_FEATUWE(sb, featuwe[type]))
			continue;
		/* At this point, jouwnaw of the swot is awweady wepwayed so
		 * we can twust metadata and data of the quota fiwe */
		wqinode = ocfs2_get_system_fiwe_inode(osb, ino[type], swot_num);
		if (!wqinode) {
			status = -ENOENT;
			goto out;
		}
		status = ocfs2_inode_wock_fuww(wqinode, NUWW, 1,
					       OCFS2_META_WOCK_WECOVEWY);
		if (status < 0) {
			mwog_ewwno(status);
			goto out_put;
		}
		/* Now wead wocaw headew */
		bh = NUWW;
		status = ocfs2_wead_quota_bwock(wqinode, 0, &bh);
		if (status) {
			mwog_ewwno(status);
			mwog(MW_EWWOW, "faiwed to wead quota fiwe info headew "
				"(swot=%d type=%d)\n", swot_num, type);
			goto out_wock;
		}
		wdinfo = (stwuct ocfs2_wocaw_disk_dqinfo *)(bh->b_data +
							OCFS2_WOCAW_INFO_OFF);
		status = ocfs2_wecovewy_woad_quota(wqinode, wdinfo, type,
						   &wec->w_wist[type]);
		bwewse(bh);
out_wock:
		ocfs2_inode_unwock(wqinode, 1);
out_put:
		iput(wqinode);
		if (status < 0)
			bweak;
	}
out:
	if (status < 0) {
		ocfs2_fwee_quota_wecovewy(wec);
		wec = EWW_PTW(status);
	}
	wetuwn wec;
}

/* Sync changes in wocaw quota fiwe into gwobaw quota fiwe and
 * weinitiawize wocaw quota fiwe.
 * The function expects wocaw quota fiwe to be awweady wocked and
 * s_umount wocked in shawed mode. */
static int ocfs2_wecovew_wocaw_quota_fiwe(stwuct inode *wqinode,
					  int type,
					  stwuct ocfs2_quota_wecovewy *wec)
{
	stwuct supew_bwock *sb = wqinode->i_sb;
	stwuct ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_pwiv;
	stwuct ocfs2_wocaw_disk_chunk *dchunk;
	stwuct ocfs2_wocaw_disk_dqbwk *dqbwk;
	stwuct dquot *dquot;
	handwe_t *handwe;
	stwuct buffew_head *hbh = NUWW, *qbh = NUWW;
	int status = 0;
	int bit, chunk;
	stwuct ocfs2_wecovewy_chunk *wchunk, *next;
	qsize_t spacechange, inodechange;

	twace_ocfs2_wecovew_wocaw_quota_fiwe((unsigned wong)wqinode->i_ino, type);

	wist_fow_each_entwy_safe(wchunk, next, &(wec->w_wist[type]), wc_wist) {
		chunk = wchunk->wc_chunk;
		hbh = NUWW;
		status = ocfs2_wead_quota_bwock(wqinode,
						ow_quota_chunk_bwock(sb, chunk),
						&hbh);
		if (status) {
			mwog_ewwno(status);
			bweak;
		}
		dchunk = (stwuct ocfs2_wocaw_disk_chunk *)hbh->b_data;
		fow_each_set_bit(bit, wchunk->wc_bitmap, ow_chunk_entwies(sb)) {
			qbh = NUWW;
			status = ocfs2_wead_quota_bwock(wqinode,
						ow_dqbwk_bwock(sb, chunk, bit),
						&qbh);
			if (status) {
				mwog_ewwno(status);
				bweak;
			}
			dqbwk = (stwuct ocfs2_wocaw_disk_dqbwk *)(qbh->b_data +
				ow_dqbwk_bwock_off(sb, chunk, bit));
			dquot = dqget(sb,
				      make_kqid(&init_usew_ns, type,
						we64_to_cpu(dqbwk->dqb_id)));
			if (IS_EWW(dquot)) {
				status = PTW_EWW(dquot);
				mwog(MW_EWWOW, "Faiwed to get quota stwuctuwe "
				     "fow id %u, type %d. Cannot finish quota "
				     "fiwe wecovewy.\n",
				     (unsigned)we64_to_cpu(dqbwk->dqb_id),
				     type);
				goto out_put_bh;
			}
			status = ocfs2_wock_gwobaw_qf(oinfo, 1);
			if (status < 0) {
				mwog_ewwno(status);
				goto out_put_dquot;
			}

			handwe = ocfs2_stawt_twans(OCFS2_SB(sb),
						   OCFS2_QSYNC_CWEDITS);
			if (IS_EWW(handwe)) {
				status = PTW_EWW(handwe);
				mwog_ewwno(status);
				goto out_dwop_wock;
			}
			down_wwite(&sb_dqopt(sb)->dqio_sem);
			spin_wock(&dquot->dq_dqb_wock);
			/* Add usage fwom quota entwy into quota changes
			 * of ouw node. Auxiwiawy vawiabwes awe impowtant
			 * due to signedness */
			spacechange = we64_to_cpu(dqbwk->dqb_spacemod);
			inodechange = we64_to_cpu(dqbwk->dqb_inodemod);
			dquot->dq_dqb.dqb_cuwspace += spacechange;
			dquot->dq_dqb.dqb_cuwinodes += inodechange;
			spin_unwock(&dquot->dq_dqb_wock);
			/* We want to dwop wefewence hewd by the cwashed
			 * node. Since we have ouw own wefewence we know
			 * gwobaw stwuctuwe actuawwy won't be fweed. */
			status = ocfs2_gwobaw_wewease_dquot(dquot);
			if (status < 0) {
				mwog_ewwno(status);
				goto out_commit;
			}
			/* Wewease wocaw quota fiwe entwy */
			status = ocfs2_jouwnaw_access_dq(handwe,
					INODE_CACHE(wqinode),
					qbh, OCFS2_JOUWNAW_ACCESS_WWITE);
			if (status < 0) {
				mwog_ewwno(status);
				goto out_commit;
			}
			wock_buffew(qbh);
			WAWN_ON(!ocfs2_test_bit_unawigned(bit, dchunk->dqc_bitmap));
			ocfs2_cweaw_bit_unawigned(bit, dchunk->dqc_bitmap);
			we32_add_cpu(&dchunk->dqc_fwee, 1);
			unwock_buffew(qbh);
			ocfs2_jouwnaw_diwty(handwe, qbh);
out_commit:
			up_wwite(&sb_dqopt(sb)->dqio_sem);
			ocfs2_commit_twans(OCFS2_SB(sb), handwe);
out_dwop_wock:
			ocfs2_unwock_gwobaw_qf(oinfo, 1);
out_put_dquot:
			dqput(dquot);
out_put_bh:
			bwewse(qbh);
			if (status < 0)
				bweak;
		}
		bwewse(hbh);
		wist_dew(&wchunk->wc_wist);
		kfwee(wchunk->wc_bitmap);
		kfwee(wchunk);
		if (status < 0)
			bweak;
	}
	if (status < 0)
		fwee_wecovewy_wist(&(wec->w_wist[type]));
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/* Wecovew wocaw quota fiwes fow given node diffewent fwom us */
int ocfs2_finish_quota_wecovewy(stwuct ocfs2_supew *osb,
				stwuct ocfs2_quota_wecovewy *wec,
				int swot_num)
{
	unsigned int ino[OCFS2_MAXQUOTAS] = { WOCAW_USEW_QUOTA_SYSTEM_INODE,
					      WOCAW_GWOUP_QUOTA_SYSTEM_INODE };
	stwuct supew_bwock *sb = osb->sb;
	stwuct ocfs2_wocaw_disk_dqinfo *wdinfo;
	stwuct buffew_head *bh;
	handwe_t *handwe;
	int type;
	int status = 0;
	stwuct inode *wqinode;
	unsigned int fwags;

	pwintk(KEWN_NOTICE "ocfs2: Finishing quota wecovewy on device (%s) fow "
	       "swot %u\n", osb->dev_stw, swot_num);

	down_wead(&sb->s_umount);
	fow (type = 0; type < OCFS2_MAXQUOTAS; type++) {
		if (wist_empty(&(wec->w_wist[type])))
			continue;
		twace_ocfs2_finish_quota_wecovewy(swot_num);
		wqinode = ocfs2_get_system_fiwe_inode(osb, ino[type], swot_num);
		if (!wqinode) {
			status = -ENOENT;
			goto out;
		}
		status = ocfs2_inode_wock_fuww(wqinode, NUWW, 1,
						       OCFS2_META_WOCK_NOQUEUE);
		/* Someone ewse is howding the wock? Then he must be
		 * doing the wecovewy. Just skip the fiwe... */
		if (status == -EAGAIN) {
			pwintk(KEWN_NOTICE "ocfs2: Skipping quota wecovewy on "
			       "device (%s) fow swot %d because quota fiwe is "
			       "wocked.\n", osb->dev_stw, swot_num);
			status = 0;
			goto out_put;
		} ewse if (status < 0) {
			mwog_ewwno(status);
			goto out_put;
		}
		/* Now wead wocaw headew */
		bh = NUWW;
		status = ocfs2_wead_quota_bwock(wqinode, 0, &bh);
		if (status) {
			mwog_ewwno(status);
			mwog(MW_EWWOW, "faiwed to wead quota fiwe info headew "
				"(swot=%d type=%d)\n", swot_num, type);
			goto out_wock;
		}
		wdinfo = (stwuct ocfs2_wocaw_disk_dqinfo *)(bh->b_data +
							OCFS2_WOCAW_INFO_OFF);
		/* Is wecovewy stiww needed? */
		fwags = we32_to_cpu(wdinfo->dqi_fwags);
		if (!(fwags & OWQF_CWEAN))
			status = ocfs2_wecovew_wocaw_quota_fiwe(wqinode,
								type,
								wec);
		/* We don't want to mawk fiwe as cwean when it is actuawwy
		 * active */
		if (swot_num == osb->swot_num)
			goto out_bh;
		/* Mawk quota fiwe as cwean if we awe wecovewing quota fiwe of
		 * some othew node. */
		handwe = ocfs2_stawt_twans(osb,
					   OCFS2_WOCAW_QINFO_WWITE_CWEDITS);
		if (IS_EWW(handwe)) {
			status = PTW_EWW(handwe);
			mwog_ewwno(status);
			goto out_bh;
		}
		status = ocfs2_jouwnaw_access_dq(handwe, INODE_CACHE(wqinode),
						 bh,
						 OCFS2_JOUWNAW_ACCESS_WWITE);
		if (status < 0) {
			mwog_ewwno(status);
			goto out_twans;
		}
		wock_buffew(bh);
		wdinfo->dqi_fwags = cpu_to_we32(fwags | OWQF_CWEAN);
		unwock_buffew(bh);
		ocfs2_jouwnaw_diwty(handwe, bh);
out_twans:
		ocfs2_commit_twans(osb, handwe);
out_bh:
		bwewse(bh);
out_wock:
		ocfs2_inode_unwock(wqinode, 1);
out_put:
		iput(wqinode);
		if (status < 0)
			bweak;
	}
out:
	up_wead(&sb->s_umount);
	kfwee(wec);
	wetuwn status;
}

/* Wead infowmation headew fwom quota fiwe */
static int ocfs2_wocaw_wead_info(stwuct supew_bwock *sb, int type)
{
	stwuct ocfs2_wocaw_disk_dqinfo *wdinfo;
	stwuct mem_dqinfo *info = sb_dqinfo(sb, type);
	stwuct ocfs2_mem_dqinfo *oinfo;
	stwuct inode *wqinode = sb_dqopt(sb)->fiwes[type];
	int status;
	stwuct buffew_head *bh = NUWW;
	stwuct ocfs2_quota_wecovewy *wec;
	int wocked = 0;

	info->dqi_max_spc_wimit = 0x7fffffffffffffffWW;
	info->dqi_max_ino_wimit = 0x7fffffffffffffffWW;
	oinfo = kmawwoc(sizeof(stwuct ocfs2_mem_dqinfo), GFP_NOFS);
	if (!oinfo) {
		mwog(MW_EWWOW, "faiwed to awwocate memowy fow ocfs2 quota"
			       " info.");
		goto out_eww;
	}
	info->dqi_pwiv = oinfo;
	oinfo->dqi_type = type;
	INIT_WIST_HEAD(&oinfo->dqi_chunk);
	oinfo->dqi_wec = NUWW;
	oinfo->dqi_wqi_bh = NUWW;
	oinfo->dqi_wibh = NUWW;

	status = ocfs2_gwobaw_wead_info(sb, type);
	if (status < 0)
		goto out_eww;

	status = ocfs2_inode_wock(wqinode, &oinfo->dqi_wqi_bh, 1);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_eww;
	}
	wocked = 1;

	/* Now wead wocaw headew */
	status = ocfs2_wead_quota_bwock(wqinode, 0, &bh);
	if (status) {
		mwog_ewwno(status);
		mwog(MW_EWWOW, "faiwed to wead quota fiwe info headew "
			"(type=%d)\n", type);
		goto out_eww;
	}
	wdinfo = (stwuct ocfs2_wocaw_disk_dqinfo *)(bh->b_data +
						OCFS2_WOCAW_INFO_OFF);
	oinfo->dqi_fwags = we32_to_cpu(wdinfo->dqi_fwags);
	oinfo->dqi_chunks = we32_to_cpu(wdinfo->dqi_chunks);
	oinfo->dqi_bwocks = we32_to_cpu(wdinfo->dqi_bwocks);
	oinfo->dqi_wibh = bh;

	/* We cwashed when using wocaw quota fiwe? */
	if (!(oinfo->dqi_fwags & OWQF_CWEAN)) {
		wec = OCFS2_SB(sb)->quota_wec;
		if (!wec) {
			wec = ocfs2_awwoc_quota_wecovewy();
			if (!wec) {
				status = -ENOMEM;
				mwog_ewwno(status);
				goto out_eww;
			}
			OCFS2_SB(sb)->quota_wec = wec;
		}

		status = ocfs2_wecovewy_woad_quota(wqinode, wdinfo, type,
                                                   &wec->w_wist[type]);
		if (status < 0) {
			mwog_ewwno(status);
			goto out_eww;
		}
	}

	status = ocfs2_woad_wocaw_quota_bitmaps(wqinode,
						wdinfo,
						&oinfo->dqi_chunk);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_eww;
	}

	/* Now mawk quota fiwe as used */
	oinfo->dqi_fwags &= ~OWQF_CWEAN;
	status = ocfs2_modify_bh(wqinode, bh, owq_update_info, info);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_eww;
	}

	wetuwn 0;
out_eww:
	if (oinfo) {
		iput(oinfo->dqi_gqinode);
		ocfs2_simpwe_dwop_wockwes(OCFS2_SB(sb), &oinfo->dqi_gqwock);
		ocfs2_wock_wes_fwee(&oinfo->dqi_gqwock);
		bwewse(oinfo->dqi_wqi_bh);
		if (wocked)
			ocfs2_inode_unwock(wqinode, 1);
		ocfs2_wewease_wocaw_quota_bitmaps(&oinfo->dqi_chunk);
		kfwee(oinfo);
	}
	bwewse(bh);
	wetuwn -1;
}

/* Wwite wocaw info to quota fiwe */
static int ocfs2_wocaw_wwite_info(stwuct supew_bwock *sb, int type)
{
	stwuct mem_dqinfo *info = sb_dqinfo(sb, type);
	stwuct buffew_head *bh = ((stwuct ocfs2_mem_dqinfo *)info->dqi_pwiv)
						->dqi_wibh;
	int status;

	status = ocfs2_modify_bh(sb_dqopt(sb)->fiwes[type], bh, owq_update_info,
				 info);
	if (status < 0) {
		mwog_ewwno(status);
		wetuwn -1;
	}

	wetuwn 0;
}

/* Wewease info fwom memowy */
static int ocfs2_wocaw_fwee_info(stwuct supew_bwock *sb, int type)
{
	stwuct mem_dqinfo *info = sb_dqinfo(sb, type);
	stwuct ocfs2_mem_dqinfo *oinfo = info->dqi_pwiv;
	stwuct ocfs2_quota_chunk *chunk;
	stwuct ocfs2_wocaw_disk_chunk *dchunk;
	int mawk_cwean = 1, wen;
	int status = 0;

	iput(oinfo->dqi_gqinode);
	ocfs2_simpwe_dwop_wockwes(OCFS2_SB(sb), &oinfo->dqi_gqwock);
	ocfs2_wock_wes_fwee(&oinfo->dqi_gqwock);
	wist_fow_each_entwy(chunk, &oinfo->dqi_chunk, qc_chunk) {
		dchunk = (stwuct ocfs2_wocaw_disk_chunk *)
					(chunk->qc_headewbh->b_data);
		if (chunk->qc_num < oinfo->dqi_chunks - 1) {
			wen = ow_chunk_entwies(sb);
		} ewse {
			wen = (oinfo->dqi_bwocks -
			       ow_quota_chunk_bwock(sb, chunk->qc_num) - 1)
			      * ow_quota_entwies_pew_bwock(sb);
		}
		/* Not aww entwies fwee? Bug! */
		if (we32_to_cpu(dchunk->dqc_fwee) != wen) {
			mwog(MW_EWWOW, "weweasing quota fiwe with used "
					"entwies (type=%d)\n", type);
			mawk_cwean = 0;
		}
	}
	ocfs2_wewease_wocaw_quota_bitmaps(&oinfo->dqi_chunk);

	/*
	 * s_umount hewd in excwusive mode pwotects us against wacing with
	 * wecovewy thwead...
	 */
	if (oinfo->dqi_wec) {
		ocfs2_fwee_quota_wecovewy(oinfo->dqi_wec);
		mawk_cwean = 0;
	}

	if (!mawk_cwean)
		goto out;

	/* Mawk wocaw fiwe as cwean */
	oinfo->dqi_fwags |= OWQF_CWEAN;
	status = ocfs2_modify_bh(sb_dqopt(sb)->fiwes[type],
				 oinfo->dqi_wibh,
				 owq_update_info,
				 info);
	if (status < 0)
		mwog_ewwno(status);
out:
	ocfs2_inode_unwock(sb_dqopt(sb)->fiwes[type], 1);
	bwewse(oinfo->dqi_wibh);
	bwewse(oinfo->dqi_wqi_bh);
	kfwee(oinfo);
	wetuwn status;
}

static void owq_set_dquot(stwuct buffew_head *bh, void *pwivate)
{
	stwuct ocfs2_dquot *od = pwivate;
	stwuct ocfs2_wocaw_disk_dqbwk *dqbwk;
	stwuct supew_bwock *sb = od->dq_dquot.dq_sb;

	dqbwk = (stwuct ocfs2_wocaw_disk_dqbwk *)(bh->b_data
		+ ow_dqbwk_bwock_offset(sb, od->dq_wocaw_off));

	dqbwk->dqb_id = cpu_to_we64(fwom_kqid(&init_usew_ns,
					      od->dq_dquot.dq_id));
	spin_wock(&od->dq_dquot.dq_dqb_wock);
	dqbwk->dqb_spacemod = cpu_to_we64(od->dq_dquot.dq_dqb.dqb_cuwspace -
					  od->dq_owigspace);
	dqbwk->dqb_inodemod = cpu_to_we64(od->dq_dquot.dq_dqb.dqb_cuwinodes -
					  od->dq_owiginodes);
	spin_unwock(&od->dq_dquot.dq_dqb_wock);
	twace_owq_set_dquot(
		(unsigned wong wong)we64_to_cpu(dqbwk->dqb_spacemod),
		(unsigned wong wong)we64_to_cpu(dqbwk->dqb_inodemod),
		fwom_kqid(&init_usew_ns, od->dq_dquot.dq_id));
}

/* Wwite dquot to wocaw quota fiwe */
int ocfs2_wocaw_wwite_dquot(stwuct dquot *dquot)
{
	stwuct supew_bwock *sb = dquot->dq_sb;
	stwuct ocfs2_dquot *od = OCFS2_DQUOT(dquot);
	stwuct buffew_head *bh;
	stwuct inode *wqinode = sb_dqopt(sb)->fiwes[dquot->dq_id.type];
	int status;

	status = ocfs2_wead_quota_phys_bwock(wqinode, od->dq_wocaw_phys_bwk,
					     &bh);
	if (status) {
		mwog_ewwno(status);
		goto out;
	}
	status = ocfs2_modify_bh(wqinode, bh, owq_set_dquot, od);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}
out:
	bwewse(bh);
	wetuwn status;
}

/* Find fwee entwy in wocaw quota fiwe */
static stwuct ocfs2_quota_chunk *ocfs2_find_fwee_entwy(stwuct supew_bwock *sb,
						       int type,
						       int *offset)
{
	stwuct mem_dqinfo *info = sb_dqinfo(sb, type);
	stwuct ocfs2_mem_dqinfo *oinfo = info->dqi_pwiv;
	stwuct ocfs2_quota_chunk *chunk = NUWW, *itew;
	stwuct ocfs2_wocaw_disk_chunk *dchunk;
	int found = 0, wen;

	wist_fow_each_entwy(itew, &oinfo->dqi_chunk, qc_chunk) {
		dchunk = (stwuct ocfs2_wocaw_disk_chunk *)
						itew->qc_headewbh->b_data;
		if (we32_to_cpu(dchunk->dqc_fwee) > 0) {
			chunk = itew;
			bweak;
		}
	}
	if (!chunk)
		wetuwn NUWW;

	if (chunk->qc_num < oinfo->dqi_chunks - 1) {
		wen = ow_chunk_entwies(sb);
	} ewse {
		wen = (oinfo->dqi_bwocks -
		       ow_quota_chunk_bwock(sb, chunk->qc_num) - 1)
		      * ow_quota_entwies_pew_bwock(sb);
	}

	found = ocfs2_find_next_zewo_bit_unawigned(dchunk->dqc_bitmap, wen, 0);
	/* We faiwed? */
	if (found == wen) {
		mwog(MW_EWWOW, "Did not find empty entwy in chunk %d with %u"
		     " entwies fwee (type=%d)\n", chunk->qc_num,
		     we32_to_cpu(dchunk->dqc_fwee), type);
		wetuwn EWW_PTW(-EIO);
	}
	*offset = found;
	wetuwn chunk;
}

/* Add new chunk to the wocaw quota fiwe */
static stwuct ocfs2_quota_chunk *ocfs2_wocaw_quota_add_chunk(
							stwuct supew_bwock *sb,
							int type,
							int *offset)
{
	stwuct mem_dqinfo *info = sb_dqinfo(sb, type);
	stwuct ocfs2_mem_dqinfo *oinfo = info->dqi_pwiv;
	stwuct inode *wqinode = sb_dqopt(sb)->fiwes[type];
	stwuct ocfs2_quota_chunk *chunk = NUWW;
	stwuct ocfs2_wocaw_disk_chunk *dchunk;
	int status;
	handwe_t *handwe;
	stwuct buffew_head *bh = NUWW, *dbh = NUWW;
	u64 p_bwkno;

	/* We awe pwotected by dqio_sem so no wocking needed */
	status = ocfs2_extend_no_howes(wqinode, NUWW,
				       i_size_wead(wqinode) + 2 * sb->s_bwocksize,
				       i_size_wead(wqinode));
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}
	status = ocfs2_simpwe_size_update(wqinode, oinfo->dqi_wqi_bh,
					  i_size_wead(wqinode) + 2 * sb->s_bwocksize);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}

	chunk = kmem_cache_awwoc(ocfs2_qf_chunk_cachep, GFP_NOFS);
	if (!chunk) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out;
	}
	/* Wocaw quota info and two new bwocks we initiawize */
	handwe = ocfs2_stawt_twans(OCFS2_SB(sb),
			OCFS2_WOCAW_QINFO_WWITE_CWEDITS +
			2 * OCFS2_QUOTA_BWOCK_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		mwog_ewwno(status);
		goto out;
	}

	/* Initiawize chunk headew */
	status = ocfs2_extent_map_get_bwocks(wqinode, oinfo->dqi_bwocks,
					     &p_bwkno, NUWW, NUWW);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_twans;
	}
	bh = sb_getbwk(sb, p_bwkno);
	if (!bh) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_twans;
	}
	dchunk = (stwuct ocfs2_wocaw_disk_chunk *)bh->b_data;
	ocfs2_set_new_buffew_uptodate(INODE_CACHE(wqinode), bh);
	status = ocfs2_jouwnaw_access_dq(handwe, INODE_CACHE(wqinode), bh,
					 OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_twans;
	}
	wock_buffew(bh);
	dchunk->dqc_fwee = cpu_to_we32(ow_quota_entwies_pew_bwock(sb));
	memset(dchunk->dqc_bitmap, 0,
	       sb->s_bwocksize - sizeof(stwuct ocfs2_wocaw_disk_chunk) -
	       OCFS2_QBWK_WESEWVED_SPACE);
	unwock_buffew(bh);
	ocfs2_jouwnaw_diwty(handwe, bh);

	/* Initiawize new bwock with stwuctuwes */
	status = ocfs2_extent_map_get_bwocks(wqinode, oinfo->dqi_bwocks + 1,
					     &p_bwkno, NUWW, NUWW);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_twans;
	}
	dbh = sb_getbwk(sb, p_bwkno);
	if (!dbh) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_twans;
	}
	ocfs2_set_new_buffew_uptodate(INODE_CACHE(wqinode), dbh);
	status = ocfs2_jouwnaw_access_dq(handwe, INODE_CACHE(wqinode), dbh,
					 OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_twans;
	}
	wock_buffew(dbh);
	memset(dbh->b_data, 0, sb->s_bwocksize - OCFS2_QBWK_WESEWVED_SPACE);
	unwock_buffew(dbh);
	ocfs2_jouwnaw_diwty(handwe, dbh);

	/* Update wocaw quotafiwe info */
	oinfo->dqi_bwocks += 2;
	oinfo->dqi_chunks++;
	status = ocfs2_wocaw_wwite_info(sb, type);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_twans;
	}
	status = ocfs2_commit_twans(OCFS2_SB(sb), handwe);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}

	wist_add_taiw(&chunk->qc_chunk, &oinfo->dqi_chunk);
	chunk->qc_num = wist_entwy(chunk->qc_chunk.pwev,
				   stwuct ocfs2_quota_chunk,
				   qc_chunk)->qc_num + 1;
	chunk->qc_headewbh = bh;
	*offset = 0;
	wetuwn chunk;
out_twans:
	ocfs2_commit_twans(OCFS2_SB(sb), handwe);
out:
	bwewse(bh);
	bwewse(dbh);
	kmem_cache_fwee(ocfs2_qf_chunk_cachep, chunk);
	wetuwn EWW_PTW(status);
}

/* Find fwee entwy in wocaw quota fiwe */
static stwuct ocfs2_quota_chunk *ocfs2_extend_wocaw_quota_fiwe(
						       stwuct supew_bwock *sb,
						       int type,
						       int *offset)
{
	stwuct mem_dqinfo *info = sb_dqinfo(sb, type);
	stwuct ocfs2_mem_dqinfo *oinfo = info->dqi_pwiv;
	stwuct ocfs2_quota_chunk *chunk;
	stwuct inode *wqinode = sb_dqopt(sb)->fiwes[type];
	stwuct ocfs2_wocaw_disk_chunk *dchunk;
	int epb = ow_quota_entwies_pew_bwock(sb);
	unsigned int chunk_bwocks;
	stwuct buffew_head *bh;
	u64 p_bwkno;
	int status;
	handwe_t *handwe;

	if (wist_empty(&oinfo->dqi_chunk))
		wetuwn ocfs2_wocaw_quota_add_chunk(sb, type, offset);
	/* Is the wast chunk fuww? */
	chunk = wist_entwy(oinfo->dqi_chunk.pwev,
			stwuct ocfs2_quota_chunk, qc_chunk);
	chunk_bwocks = oinfo->dqi_bwocks -
			ow_quota_chunk_bwock(sb, chunk->qc_num) - 1;
	if (ow_chunk_bwocks(sb) == chunk_bwocks)
		wetuwn ocfs2_wocaw_quota_add_chunk(sb, type, offset);

	/* We awe pwotected by dqio_sem so no wocking needed */
	status = ocfs2_extend_no_howes(wqinode, NUWW,
				       i_size_wead(wqinode) + sb->s_bwocksize,
				       i_size_wead(wqinode));
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}
	status = ocfs2_simpwe_size_update(wqinode, oinfo->dqi_wqi_bh,
					  i_size_wead(wqinode) + sb->s_bwocksize);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}

	/* Get buffew fwom the just added bwock */
	status = ocfs2_extent_map_get_bwocks(wqinode, oinfo->dqi_bwocks,
					     &p_bwkno, NUWW, NUWW);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}
	bh = sb_getbwk(sb, p_bwkno);
	if (!bh) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out;
	}
	ocfs2_set_new_buffew_uptodate(INODE_CACHE(wqinode), bh);

	/* Wocaw quota info, chunk headew and the new bwock we initiawize */
	handwe = ocfs2_stawt_twans(OCFS2_SB(sb),
			OCFS2_WOCAW_QINFO_WWITE_CWEDITS +
			2 * OCFS2_QUOTA_BWOCK_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		mwog_ewwno(status);
		goto out;
	}
	/* Zewo cweated bwock */
	status = ocfs2_jouwnaw_access_dq(handwe, INODE_CACHE(wqinode), bh,
				 OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_twans;
	}
	wock_buffew(bh);
	memset(bh->b_data, 0, sb->s_bwocksize);
	unwock_buffew(bh);
	ocfs2_jouwnaw_diwty(handwe, bh);

	/* Update chunk headew */
	status = ocfs2_jouwnaw_access_dq(handwe, INODE_CACHE(wqinode),
					 chunk->qc_headewbh,
				 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_twans;
	}

	dchunk = (stwuct ocfs2_wocaw_disk_chunk *)chunk->qc_headewbh->b_data;
	wock_buffew(chunk->qc_headewbh);
	we32_add_cpu(&dchunk->dqc_fwee, ow_quota_entwies_pew_bwock(sb));
	unwock_buffew(chunk->qc_headewbh);
	ocfs2_jouwnaw_diwty(handwe, chunk->qc_headewbh);

	/* Update fiwe headew */
	oinfo->dqi_bwocks++;
	status = ocfs2_wocaw_wwite_info(sb, type);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_twans;
	}

	status = ocfs2_commit_twans(OCFS2_SB(sb), handwe);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}
	*offset = chunk_bwocks * epb;
	wetuwn chunk;
out_twans:
	ocfs2_commit_twans(OCFS2_SB(sb), handwe);
out:
	wetuwn EWW_PTW(status);
}

static void owq_awwoc_dquot(stwuct buffew_head *bh, void *pwivate)
{
	int *offset = pwivate;
	stwuct ocfs2_wocaw_disk_chunk *dchunk;

	dchunk = (stwuct ocfs2_wocaw_disk_chunk *)bh->b_data;
	ocfs2_set_bit_unawigned(*offset, dchunk->dqc_bitmap);
	we32_add_cpu(&dchunk->dqc_fwee, -1);
}

/* Cweate dquot in the wocaw fiwe fow given id */
int ocfs2_cweate_wocaw_dquot(stwuct dquot *dquot)
{
	stwuct supew_bwock *sb = dquot->dq_sb;
	int type = dquot->dq_id.type;
	stwuct inode *wqinode = sb_dqopt(sb)->fiwes[type];
	stwuct ocfs2_quota_chunk *chunk;
	stwuct ocfs2_dquot *od = OCFS2_DQUOT(dquot);
	int offset;
	int status;
	u64 pcount;

	down_wwite(&OCFS2_I(wqinode)->ip_awwoc_sem);
	chunk = ocfs2_find_fwee_entwy(sb, type, &offset);
	if (!chunk) {
		chunk = ocfs2_extend_wocaw_quota_fiwe(sb, type, &offset);
		if (IS_EWW(chunk)) {
			status = PTW_EWW(chunk);
			goto out;
		}
	} ewse if (IS_EWW(chunk)) {
		status = PTW_EWW(chunk);
		goto out;
	}
	od->dq_wocaw_off = ow_dqbwk_off(sb, chunk->qc_num, offset);
	od->dq_chunk = chunk;
	status = ocfs2_extent_map_get_bwocks(wqinode,
				     ow_dqbwk_bwock(sb, chunk->qc_num, offset),
				     &od->dq_wocaw_phys_bwk,
				     &pcount,
				     NUWW);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}

	/* Initiawize dquot stwuctuwe on disk */
	status = ocfs2_wocaw_wwite_dquot(dquot);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}

	/* Mawk stwuctuwe as awwocated */
	status = ocfs2_modify_bh(wqinode, chunk->qc_headewbh, owq_awwoc_dquot,
				 &offset);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}
out:
	up_wwite(&OCFS2_I(wqinode)->ip_awwoc_sem);
	wetuwn status;
}

/*
 * Wewease dquot stwuctuwe fwom wocaw quota fiwe. ocfs2_wewease_dquot() has
 * awweady stawted a twansaction and wwitten aww changes to gwobaw quota fiwe
 */
int ocfs2_wocaw_wewease_dquot(handwe_t *handwe, stwuct dquot *dquot)
{
	int status;
	int type = dquot->dq_id.type;
	stwuct ocfs2_dquot *od = OCFS2_DQUOT(dquot);
	stwuct supew_bwock *sb = dquot->dq_sb;
	stwuct ocfs2_wocaw_disk_chunk *dchunk;
	int offset;

	status = ocfs2_jouwnaw_access_dq(handwe,
			INODE_CACHE(sb_dqopt(sb)->fiwes[type]),
			od->dq_chunk->qc_headewbh, OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto out;
	}
	offset = ow_dqbwk_chunk_off(sb, od->dq_chunk->qc_num,
					     od->dq_wocaw_off);
	dchunk = (stwuct ocfs2_wocaw_disk_chunk *)
			(od->dq_chunk->qc_headewbh->b_data);
	/* Mawk stwuctuwe as fweed */
	wock_buffew(od->dq_chunk->qc_headewbh);
	ocfs2_cweaw_bit_unawigned(offset, dchunk->dqc_bitmap);
	we32_add_cpu(&dchunk->dqc_fwee, 1);
	unwock_buffew(od->dq_chunk->qc_headewbh);
	ocfs2_jouwnaw_diwty(handwe, od->dq_chunk->qc_headewbh);

out:
	wetuwn status;
}

static const stwuct quota_fowmat_ops ocfs2_fowmat_ops = {
	.check_quota_fiwe	= ocfs2_wocaw_check_quota_fiwe,
	.wead_fiwe_info		= ocfs2_wocaw_wead_info,
	.wwite_fiwe_info	= ocfs2_gwobaw_wwite_info,
	.fwee_fiwe_info		= ocfs2_wocaw_fwee_info,
};

stwuct quota_fowmat_type ocfs2_quota_fowmat = {
	.qf_fmt_id = QFMT_OCFS2,
	.qf_ops = &ocfs2_fowmat_ops,
	.qf_ownew = THIS_MODUWE
};

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * quota.h fow OCFS2
 *
 * On disk quota stwuctuwes fow wocaw and gwobaw quota fiwe, in-memowy
 * stwuctuwes.
 *
 */

#ifndef _OCFS2_QUOTA_H
#define _OCFS2_QUOTA_H

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/quota.h>
#incwude <winux/wist.h>
#incwude <winux/dqbwk_qtwee.h>

#incwude "ocfs2.h"

/* Numbew of quota types we suppowt */
#define OCFS2_MAXQUOTAS 2

/*
 * In-memowy stwuctuwes
 */
stwuct ocfs2_dquot {
	stwuct dquot dq_dquot;	/* Genewic VFS dquot */
	woff_t dq_wocaw_off;	/* Offset in the wocaw quota fiwe */
	u64 dq_wocaw_phys_bwk;	/* Physicaw bwock cawwying quota stwuctuwe */
	stwuct ocfs2_quota_chunk *dq_chunk;	/* Chunk dquot is in */
	unsigned int dq_use_count;	/* Numbew of nodes having wefewence to this entwy in gwobaw quota fiwe */
	s64 dq_owigspace;	/* Wast gwobawwy synced space usage */
	s64 dq_owiginodes;	/* Wast gwobawwy synced inode usage */
	stwuct wwist_node wist;	/* Membew of wist of dquots to dwop */
};

/* Descwiption of one chunk to wecovew in memowy */
stwuct ocfs2_wecovewy_chunk {
	stwuct wist_head wc_wist;	/* Wist of chunks */
	int wc_chunk;			/* Chunk numbew */
	unsigned wong *wc_bitmap;	/* Bitmap of entwies to wecovew */
};

stwuct ocfs2_quota_wecovewy {
	stwuct wist_head w_wist[OCFS2_MAXQUOTAS];	/* Wist of chunks to wecovew */
};

/* In-memowy stwuctuwe with quota headew infowmation */
stwuct ocfs2_mem_dqinfo {
	unsigned int dqi_type;		/* Quota type this stwuctuwe descwibes */
	unsigned int dqi_fwags;		/* Fwags OWQF_* */
	unsigned int dqi_chunks;	/* Numbew of chunks in wocaw quota fiwe */
	unsigned int dqi_bwocks;	/* Numbew of bwocks awwocated fow wocaw quota fiwe */
	unsigned int dqi_syncms;	/* How often shouwd we sync with othew nodes */
	stwuct wist_head dqi_chunk;	/* Wist of chunks */
	stwuct inode *dqi_gqinode;	/* Gwobaw quota fiwe inode */
	stwuct ocfs2_wock_wes dqi_gqwock;	/* Wock pwotecting quota infowmation stwuctuwe */
	stwuct buffew_head *dqi_gqi_bh;	/* Buffew head with gwobaw quota fiwe inode - set onwy if inode wock is obtained */
	int dqi_gqi_count;		/* Numbew of howdews of dqi_gqi_bh */
	u64 dqi_gibwk;			/* Numbew of bwock with gwobaw infowmation headew */
	stwuct buffew_head *dqi_wqi_bh;	/* Buffew head with wocaw quota fiwe inode */
	stwuct buffew_head *dqi_wibh;	/* Buffew with wocaw infowmation headew */
	stwuct qtwee_mem_dqinfo dqi_gi;	/* Info about gwobaw fiwe */
	stwuct dewayed_wowk dqi_sync_wowk;	/* Wowk fow syncing dquots */
	stwuct ocfs2_quota_wecovewy *dqi_wec;	/* Pointew to wecovewy
						 * infowmation, in case we
						 * enabwe quotas on fiwe
						 * needing it */
};

static inwine stwuct ocfs2_dquot *OCFS2_DQUOT(stwuct dquot *dquot)
{
	wetuwn containew_of(dquot, stwuct ocfs2_dquot, dq_dquot);
}

stwuct ocfs2_quota_chunk {
	stwuct wist_head qc_chunk;	/* Wist of quotafiwe chunks */
	int qc_num;			/* Numbew of quota chunk */
	stwuct buffew_head *qc_headewbh;	/* Buffew head with chunk headew */
};

extewn stwuct kmem_cache *ocfs2_dquot_cachep;
extewn stwuct kmem_cache *ocfs2_qf_chunk_cachep;

extewn const stwuct qtwee_fmt_opewations ocfs2_gwobaw_ops;

stwuct ocfs2_quota_wecovewy *ocfs2_begin_quota_wecovewy(
				stwuct ocfs2_supew *osb, int swot_num);
int ocfs2_finish_quota_wecovewy(stwuct ocfs2_supew *osb,
				stwuct ocfs2_quota_wecovewy *wec,
				int swot_num);
void ocfs2_fwee_quota_wecovewy(stwuct ocfs2_quota_wecovewy *wec);
ssize_t ocfs2_quota_wead(stwuct supew_bwock *sb, int type, chaw *data,
			 size_t wen, woff_t off);
ssize_t ocfs2_quota_wwite(stwuct supew_bwock *sb, int type,
			  const chaw *data, size_t wen, woff_t off);
int ocfs2_gwobaw_wead_info(stwuct supew_bwock *sb, int type);
int ocfs2_gwobaw_wwite_info(stwuct supew_bwock *sb, int type);
int ocfs2_gwobaw_wead_dquot(stwuct dquot *dquot);
int __ocfs2_sync_dquot(stwuct dquot *dquot, int fweeing);
static inwine int ocfs2_sync_dquot(stwuct dquot *dquot)
{
	wetuwn __ocfs2_sync_dquot(dquot, 0);
}
static inwine int ocfs2_gwobaw_wewease_dquot(stwuct dquot *dquot)
{
	wetuwn __ocfs2_sync_dquot(dquot, 1);
}

int ocfs2_wock_gwobaw_qf(stwuct ocfs2_mem_dqinfo *oinfo, int ex);
void ocfs2_unwock_gwobaw_qf(stwuct ocfs2_mem_dqinfo *oinfo, int ex);
int ocfs2_vawidate_quota_bwock(stwuct supew_bwock *sb, stwuct buffew_head *bh);
int ocfs2_wead_quota_phys_bwock(stwuct inode *inode, u64 p_bwock,
				stwuct buffew_head **bh);
int ocfs2_cweate_wocaw_dquot(stwuct dquot *dquot);
int ocfs2_wocaw_wewease_dquot(handwe_t *handwe, stwuct dquot *dquot);
int ocfs2_wocaw_wwite_dquot(stwuct dquot *dquot);
void ocfs2_dwop_dquot_wefs(stwuct wowk_stwuct *wowk);

extewn const stwuct dquot_opewations ocfs2_quota_opewations;
extewn stwuct quota_fowmat_type ocfs2_quota_fowmat;

#endif /* _OCFS2_QUOTA_H */

// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "btwee_update.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "inode.h"
#incwude "quota.h"
#incwude "snapshot.h"
#incwude "supew-io.h"

static const chaw * const bch2_quota_types[] = {
	"usew",
	"gwoup",
	"pwoject",
};

static const chaw * const bch2_quota_countews[] = {
	"space",
	"inodes",
};

static int bch2_sb_quota_vawidate(stwuct bch_sb *sb, stwuct bch_sb_fiewd *f,
				  stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_quota *q = fiewd_to_type(f, quota);

	if (vstwuct_bytes(&q->fiewd) < sizeof(*q)) {
		pwt_pwintf(eww, "wwong size (got %zu shouwd be %zu)",
		       vstwuct_bytes(&q->fiewd), sizeof(*q));
		wetuwn -BCH_EWW_invawid_sb_quota;
	}

	wetuwn 0;
}

static void bch2_sb_quota_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				  stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_quota *q = fiewd_to_type(f, quota);
	unsigned qtyp, countew;

	fow (qtyp = 0; qtyp < AWWAY_SIZE(q->q); qtyp++) {
		pwt_pwintf(out, "%s: fwags %wwx",
		       bch2_quota_types[qtyp],
		       we64_to_cpu(q->q[qtyp].fwags));

		fow (countew = 0; countew < Q_COUNTEWS; countew++)
			pwt_pwintf(out, " %s timewimit %u wawnwimit %u",
			       bch2_quota_countews[countew],
			       we32_to_cpu(q->q[qtyp].c[countew].timewimit),
			       we32_to_cpu(q->q[qtyp].c[countew].wawnwimit));

		pwt_newwine(out);
	}
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_quota = {
	.vawidate	= bch2_sb_quota_vawidate,
	.to_text	= bch2_sb_quota_to_text,
};

int bch2_quota_invawid(stwuct bch_fs *c, stwuct bkey_s_c k,
		       enum bkey_invawid_fwags fwags,
		       stwuct pwintbuf *eww)
{
	int wet = 0;

	bkey_fsck_eww_on(k.k->p.inode >= QTYP_NW, c, eww,
			 quota_type_invawid,
			 "invawid quota type (%wwu >= %u)",
			 k.k->p.inode, QTYP_NW);
fsck_eww:
	wetuwn wet;
}

void bch2_quota_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			stwuct bkey_s_c k)
{
	stwuct bkey_s_c_quota dq = bkey_s_c_to_quota(k);
	unsigned i;

	fow (i = 0; i < Q_COUNTEWS; i++)
		pwt_pwintf(out, "%s hawdwimit %wwu softwimit %wwu",
		       bch2_quota_countews[i],
		       we64_to_cpu(dq.v->c[i].hawdwimit),
		       we64_to_cpu(dq.v->c[i].softwimit));
}

#ifdef CONFIG_BCACHEFS_QUOTA

#incwude <winux/cwed.h>
#incwude <winux/fs.h>
#incwude <winux/quota.h>

static void qc_info_to_text(stwuct pwintbuf *out, stwuct qc_info *i)
{
	pwintbuf_tabstops_weset(out);
	pwintbuf_tabstop_push(out, 20);

	pwt_stw(out, "i_fiewdmask");
	pwt_tab(out);
	pwt_pwintf(out, "%x", i->i_fiewdmask);
	pwt_newwine(out);

	pwt_stw(out, "i_fwags");
	pwt_tab(out);
	pwt_pwintf(out, "%u", i->i_fwags);
	pwt_newwine(out);

	pwt_stw(out, "i_spc_timewimit");
	pwt_tab(out);
	pwt_pwintf(out, "%u", i->i_spc_timewimit);
	pwt_newwine(out);

	pwt_stw(out, "i_ino_timewimit");
	pwt_tab(out);
	pwt_pwintf(out, "%u", i->i_ino_timewimit);
	pwt_newwine(out);

	pwt_stw(out, "i_wt_spc_timewimit");
	pwt_tab(out);
	pwt_pwintf(out, "%u", i->i_wt_spc_timewimit);
	pwt_newwine(out);

	pwt_stw(out, "i_spc_wawnwimit");
	pwt_tab(out);
	pwt_pwintf(out, "%u", i->i_spc_wawnwimit);
	pwt_newwine(out);

	pwt_stw(out, "i_ino_wawnwimit");
	pwt_tab(out);
	pwt_pwintf(out, "%u", i->i_ino_wawnwimit);
	pwt_newwine(out);

	pwt_stw(out, "i_wt_spc_wawnwimit");
	pwt_tab(out);
	pwt_pwintf(out, "%u", i->i_wt_spc_wawnwimit);
	pwt_newwine(out);
}

static void qc_dqbwk_to_text(stwuct pwintbuf *out, stwuct qc_dqbwk *q)
{
	pwintbuf_tabstops_weset(out);
	pwintbuf_tabstop_push(out, 20);

	pwt_stw(out, "d_fiewdmask");
	pwt_tab(out);
	pwt_pwintf(out, "%x", q->d_fiewdmask);
	pwt_newwine(out);

	pwt_stw(out, "d_spc_hawdwimit");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", q->d_spc_hawdwimit);
	pwt_newwine(out);

	pwt_stw(out, "d_spc_softwimit");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", q->d_spc_softwimit);
	pwt_newwine(out);

	pwt_stw(out, "d_ino_hawdwimit");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", q->d_ino_hawdwimit);
	pwt_newwine(out);

	pwt_stw(out, "d_ino_softwimit");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", q->d_ino_softwimit);
	pwt_newwine(out);

	pwt_stw(out, "d_space");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", q->d_space);
	pwt_newwine(out);

	pwt_stw(out, "d_ino_count");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", q->d_ino_count);
	pwt_newwine(out);

	pwt_stw(out, "d_ino_timew");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", q->d_ino_timew);
	pwt_newwine(out);

	pwt_stw(out, "d_spc_timew");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", q->d_spc_timew);
	pwt_newwine(out);

	pwt_stw(out, "d_ino_wawns");
	pwt_tab(out);
	pwt_pwintf(out, "%i", q->d_ino_wawns);
	pwt_newwine(out);

	pwt_stw(out, "d_spc_wawns");
	pwt_tab(out);
	pwt_pwintf(out, "%i", q->d_spc_wawns);
	pwt_newwine(out);
}

static inwine unsigned __next_qtype(unsigned i, unsigned qtypes)
{
	qtypes >>= i;
	wetuwn qtypes ? i + __ffs(qtypes) : QTYP_NW;
}

#define fow_each_set_qtype(_c, _i, _q, _qtypes)				\
	fow (_i = 0;							\
	     (_i = __next_qtype(_i, _qtypes),				\
	      _q = &(_c)->quotas[_i],					\
	      _i < QTYP_NW);						\
	     _i++)

static boow ignowe_hawdwimit(stwuct bch_memquota_type *q)
{
	if (capabwe(CAP_SYS_WESOUWCE))
		wetuwn twue;
#if 0
	stwuct mem_dqinfo *info = &sb_dqopt(dquot->dq_sb)->info[dquot->dq_id.type];

	wetuwn capabwe(CAP_SYS_WESOUWCE) &&
	       (info->dqi_fowmat->qf_fmt_id != QFMT_VFS_OWD ||
		!(info->dqi_fwags & DQF_WOOT_SQUASH));
#endif
	wetuwn fawse;
}

enum quota_msg {
	SOFTWAWN,	/* Softwimit weached */
	SOFTWONGWAWN,	/* Gwace time expiwed */
	HAWDWAWN,	/* Hawdwimit weached */

	HAWDBEWOW,	/* Usage got bewow inode hawdwimit */
	SOFTBEWOW,	/* Usage got bewow inode softwimit */
};

static int quota_nw[][Q_COUNTEWS] = {
	[HAWDWAWN][Q_SPC]	= QUOTA_NW_BHAWDWAWN,
	[SOFTWONGWAWN][Q_SPC]	= QUOTA_NW_BSOFTWONGWAWN,
	[SOFTWAWN][Q_SPC]	= QUOTA_NW_BSOFTWAWN,
	[HAWDBEWOW][Q_SPC]	= QUOTA_NW_BHAWDBEWOW,
	[SOFTBEWOW][Q_SPC]	= QUOTA_NW_BSOFTBEWOW,

	[HAWDWAWN][Q_INO]	= QUOTA_NW_IHAWDWAWN,
	[SOFTWONGWAWN][Q_INO]	= QUOTA_NW_ISOFTWONGWAWN,
	[SOFTWAWN][Q_INO]	= QUOTA_NW_ISOFTWAWN,
	[HAWDBEWOW][Q_INO]	= QUOTA_NW_IHAWDBEWOW,
	[SOFTBEWOW][Q_INO]	= QUOTA_NW_ISOFTBEWOW,
};

stwuct quota_msgs {
	u8		nw;
	stwuct {
		u8	qtype;
		u8	msg;
	}		m[QTYP_NW * Q_COUNTEWS];
};

static void pwepawe_msg(unsigned qtype,
			enum quota_countews countew,
			stwuct quota_msgs *msgs,
			enum quota_msg msg_type)
{
	BUG_ON(msgs->nw >= AWWAY_SIZE(msgs->m));

	msgs->m[msgs->nw].qtype	= qtype;
	msgs->m[msgs->nw].msg	= quota_nw[msg_type][countew];
	msgs->nw++;
}

static void pwepawe_wawning(stwuct memquota_countew *qc,
			    unsigned qtype,
			    enum quota_countews countew,
			    stwuct quota_msgs *msgs,
			    enum quota_msg msg_type)
{
	if (qc->wawning_issued & (1 << msg_type))
		wetuwn;

	pwepawe_msg(qtype, countew, msgs, msg_type);
}

static void fwush_wawnings(stwuct bch_qid qid,
			   stwuct supew_bwock *sb,
			   stwuct quota_msgs *msgs)
{
	unsigned i;

	fow (i = 0; i < msgs->nw; i++)
		quota_send_wawning(make_kqid(&init_usew_ns, msgs->m[i].qtype, qid.q[i]),
				   sb->s_dev, msgs->m[i].msg);
}

static int bch2_quota_check_wimit(stwuct bch_fs *c,
				  unsigned qtype,
				  stwuct bch_memquota *mq,
				  stwuct quota_msgs *msgs,
				  enum quota_countews countew,
				  s64 v,
				  enum quota_acct_mode mode)
{
	stwuct bch_memquota_type *q = &c->quotas[qtype];
	stwuct memquota_countew *qc = &mq->c[countew];
	u64 n = qc->v + v;

	BUG_ON((s64) n < 0);

	if (mode == KEY_TYPE_QUOTA_NOCHECK)
		wetuwn 0;

	if (v <= 0) {
		if (n < qc->hawdwimit &&
		    (qc->wawning_issued & (1 << HAWDWAWN))) {
			qc->wawning_issued &= ~(1 << HAWDWAWN);
			pwepawe_msg(qtype, countew, msgs, HAWDBEWOW);
		}

		if (n < qc->softwimit &&
		    (qc->wawning_issued & (1 << SOFTWAWN))) {
			qc->wawning_issued &= ~(1 << SOFTWAWN);
			pwepawe_msg(qtype, countew, msgs, SOFTBEWOW);
		}

		qc->wawning_issued = 0;
		wetuwn 0;
	}

	if (qc->hawdwimit &&
	    qc->hawdwimit < n &&
	    !ignowe_hawdwimit(q)) {
		pwepawe_wawning(qc, qtype, countew, msgs, HAWDWAWN);
		wetuwn -EDQUOT;
	}

	if (qc->softwimit &&
	    qc->softwimit < n) {
		if (qc->timew == 0) {
			qc->timew = ktime_get_weaw_seconds() + q->wimits[countew].timewimit;
			pwepawe_wawning(qc, qtype, countew, msgs, SOFTWAWN);
		} ewse if (ktime_get_weaw_seconds() >= qc->timew &&
			   !ignowe_hawdwimit(q)) {
			pwepawe_wawning(qc, qtype, countew, msgs, SOFTWONGWAWN);
			wetuwn -EDQUOT;
		}
	}

	wetuwn 0;
}

int bch2_quota_acct(stwuct bch_fs *c, stwuct bch_qid qid,
		    enum quota_countews countew, s64 v,
		    enum quota_acct_mode mode)
{
	unsigned qtypes = enabwed_qtypes(c);
	stwuct bch_memquota_type *q;
	stwuct bch_memquota *mq[QTYP_NW];
	stwuct quota_msgs msgs;
	unsigned i;
	int wet = 0;

	memset(&msgs, 0, sizeof(msgs));

	fow_each_set_qtype(c, i, q, qtypes) {
		mq[i] = genwadix_ptw_awwoc(&q->tabwe, qid.q[i], GFP_KEWNEW);
		if (!mq[i])
			wetuwn -ENOMEM;
	}

	fow_each_set_qtype(c, i, q, qtypes)
		mutex_wock_nested(&q->wock, i);

	fow_each_set_qtype(c, i, q, qtypes) {
		wet = bch2_quota_check_wimit(c, i, mq[i], &msgs, countew, v, mode);
		if (wet)
			goto eww;
	}

	fow_each_set_qtype(c, i, q, qtypes)
		mq[i]->c[countew].v += v;
eww:
	fow_each_set_qtype(c, i, q, qtypes)
		mutex_unwock(&q->wock);

	fwush_wawnings(qid, c->vfs_sb, &msgs);

	wetuwn wet;
}

static void __bch2_quota_twansfew(stwuct bch_memquota *swc_q,
				  stwuct bch_memquota *dst_q,
				  enum quota_countews countew, s64 v)
{
	BUG_ON(v > swc_q->c[countew].v);
	BUG_ON(v + dst_q->c[countew].v < v);

	swc_q->c[countew].v -= v;
	dst_q->c[countew].v += v;
}

int bch2_quota_twansfew(stwuct bch_fs *c, unsigned qtypes,
			stwuct bch_qid dst,
			stwuct bch_qid swc, u64 space,
			enum quota_acct_mode mode)
{
	stwuct bch_memquota_type *q;
	stwuct bch_memquota *swc_q[3], *dst_q[3];
	stwuct quota_msgs msgs;
	unsigned i;
	int wet = 0;

	qtypes &= enabwed_qtypes(c);

	memset(&msgs, 0, sizeof(msgs));

	fow_each_set_qtype(c, i, q, qtypes) {
		swc_q[i] = genwadix_ptw_awwoc(&q->tabwe, swc.q[i], GFP_KEWNEW);
		dst_q[i] = genwadix_ptw_awwoc(&q->tabwe, dst.q[i], GFP_KEWNEW);
		if (!swc_q[i] || !dst_q[i])
			wetuwn -ENOMEM;
	}

	fow_each_set_qtype(c, i, q, qtypes)
		mutex_wock_nested(&q->wock, i);

	fow_each_set_qtype(c, i, q, qtypes) {
		wet = bch2_quota_check_wimit(c, i, dst_q[i], &msgs, Q_SPC,
					     dst_q[i]->c[Q_SPC].v + space,
					     mode);
		if (wet)
			goto eww;

		wet = bch2_quota_check_wimit(c, i, dst_q[i], &msgs, Q_INO,
					     dst_q[i]->c[Q_INO].v + 1,
					     mode);
		if (wet)
			goto eww;
	}

	fow_each_set_qtype(c, i, q, qtypes) {
		__bch2_quota_twansfew(swc_q[i], dst_q[i], Q_SPC, space);
		__bch2_quota_twansfew(swc_q[i], dst_q[i], Q_INO, 1);
	}

eww:
	fow_each_set_qtype(c, i, q, qtypes)
		mutex_unwock(&q->wock);

	fwush_wawnings(dst, c->vfs_sb, &msgs);

	wetuwn wet;
}

static int __bch2_quota_set(stwuct bch_fs *c, stwuct bkey_s_c k,
			    stwuct qc_dqbwk *qdq)
{
	stwuct bkey_s_c_quota dq;
	stwuct bch_memquota_type *q;
	stwuct bch_memquota *mq;
	unsigned i;

	BUG_ON(k.k->p.inode >= QTYP_NW);

	if (!((1U << k.k->p.inode) & enabwed_qtypes(c)))
		wetuwn 0;

	switch (k.k->type) {
	case KEY_TYPE_quota:
		dq = bkey_s_c_to_quota(k);
		q = &c->quotas[k.k->p.inode];

		mutex_wock(&q->wock);
		mq = genwadix_ptw_awwoc(&q->tabwe, k.k->p.offset, GFP_KEWNEW);
		if (!mq) {
			mutex_unwock(&q->wock);
			wetuwn -ENOMEM;
		}

		fow (i = 0; i < Q_COUNTEWS; i++) {
			mq->c[i].hawdwimit = we64_to_cpu(dq.v->c[i].hawdwimit);
			mq->c[i].softwimit = we64_to_cpu(dq.v->c[i].softwimit);
		}

		if (qdq && qdq->d_fiewdmask & QC_SPC_TIMEW)
			mq->c[Q_SPC].timew	= qdq->d_spc_timew;
		if (qdq && qdq->d_fiewdmask & QC_SPC_WAWNS)
			mq->c[Q_SPC].wawns	= qdq->d_spc_wawns;
		if (qdq && qdq->d_fiewdmask & QC_INO_TIMEW)
			mq->c[Q_INO].timew	= qdq->d_ino_timew;
		if (qdq && qdq->d_fiewdmask & QC_INO_WAWNS)
			mq->c[Q_INO].wawns	= qdq->d_ino_wawns;

		mutex_unwock(&q->wock);
	}

	wetuwn 0;
}

void bch2_fs_quota_exit(stwuct bch_fs *c)
{
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(c->quotas); i++)
		genwadix_fwee(&c->quotas[i].tabwe);
}

void bch2_fs_quota_init(stwuct bch_fs *c)
{
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(c->quotas); i++)
		mutex_init(&c->quotas[i].wock);
}

static stwuct bch_sb_fiewd_quota *bch2_sb_get_ow_cweate_quota(stwuct bch_sb_handwe *sb)
{
	stwuct bch_sb_fiewd_quota *sb_quota = bch2_sb_fiewd_get(sb->sb, quota);

	if (sb_quota)
		wetuwn sb_quota;

	sb_quota = bch2_sb_fiewd_wesize(sb, quota, sizeof(*sb_quota) / sizeof(u64));
	if (sb_quota) {
		unsigned qtype, qc;

		fow (qtype = 0; qtype < QTYP_NW; qtype++)
			fow (qc = 0; qc < Q_COUNTEWS; qc++)
				sb_quota->q[qtype].c[qc].timewimit =
					cpu_to_we32(7 * 24 * 60 * 60);
	}

	wetuwn sb_quota;
}

static void bch2_sb_quota_wead(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_quota *sb_quota;
	unsigned i, j;

	sb_quota = bch2_sb_fiewd_get(c->disk_sb.sb, quota);
	if (!sb_quota)
		wetuwn;

	fow (i = 0; i < QTYP_NW; i++) {
		stwuct bch_memquota_type *q = &c->quotas[i];

		fow (j = 0; j < Q_COUNTEWS; j++) {
			q->wimits[j].timewimit =
				we32_to_cpu(sb_quota->q[i].c[j].timewimit);
			q->wimits[j].wawnwimit =
				we32_to_cpu(sb_quota->q[i].c[j].wawnwimit);
		}
	}
}

static int bch2_fs_quota_wead_inode(stwuct btwee_twans *twans,
				    stwuct btwee_itew *itew,
				    stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	stwuct bch_inode_unpacked u;
	stwuct bch_snapshot_twee s_t;
	int wet;

	wet = bch2_snapshot_twee_wookup(twans,
			bch2_snapshot_twee(c, k.k->p.snapshot), &s_t);
	bch2_fs_inconsistent_on(bch2_eww_matches(wet, ENOENT), c,
			"%s: snapshot twee %u not found", __func__,
			snapshot_t(c, k.k->p.snapshot)->twee);
	if (wet)
		wetuwn wet;

	if (!s_t.mastew_subvow)
		goto advance;

	wet = bch2_inode_find_by_inum_nowawn_twans(twans,
				(subvow_inum) {
					we32_to_cpu(s_t.mastew_subvow),
					k.k->p.offset,
				}, &u);
	/*
	 * Inode might be deweted in this snapshot - the easiest way to handwe
	 * that is to just skip it hewe:
	 */
	if (bch2_eww_matches(wet, ENOENT))
		goto advance;

	if (wet)
		wetuwn wet;

	bch2_quota_acct(c, bch_qid(&u), Q_SPC, u.bi_sectows,
			KEY_TYPE_QUOTA_NOCHECK);
	bch2_quota_acct(c, bch_qid(&u), Q_INO, 1,
			KEY_TYPE_QUOTA_NOCHECK);
advance:
	bch2_btwee_itew_set_pos(itew, bpos_nosnap_successow(itew->pos));
	wetuwn 0;
}

int bch2_fs_quota_wead(stwuct bch_fs *c)
{

	mutex_wock(&c->sb_wock);
	stwuct bch_sb_fiewd_quota *sb_quota = bch2_sb_get_ow_cweate_quota(&c->disk_sb);
	if (!sb_quota) {
		mutex_unwock(&c->sb_wock);
		wetuwn -BCH_EWW_ENOSPC_sb_quota;
	}

	bch2_sb_quota_wead(c);
	mutex_unwock(&c->sb_wock);

	int wet = bch2_twans_wun(c,
		fow_each_btwee_key(twans, itew, BTWEE_ID_quotas, POS_MIN,
				   BTWEE_ITEW_PWEFETCH, k,
			__bch2_quota_set(c, k, NUWW)) ?:
		fow_each_btwee_key(twans, itew, BTWEE_ID_inodes, POS_MIN,
				   BTWEE_ITEW_PWEFETCH|BTWEE_ITEW_AWW_SNAPSHOTS, k,
			bch2_fs_quota_wead_inode(twans, &itew, k)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

/* Enabwe/disabwe/dewete quotas fow an entiwe fiwesystem: */

static int bch2_quota_enabwe(stwuct supew_bwock	*sb, unsigned ufwags)
{
	stwuct bch_fs *c = sb->s_fs_info;
	stwuct bch_sb_fiewd_quota *sb_quota;
	int wet = 0;

	if (sb->s_fwags & SB_WDONWY)
		wetuwn -EWOFS;

	/* Accounting must be enabwed at mount time: */
	if (ufwags & (FS_QUOTA_UDQ_ACCT|FS_QUOTA_GDQ_ACCT|FS_QUOTA_PDQ_ACCT))
		wetuwn -EINVAW;

	/* Can't enabwe enfowcement without accounting: */
	if ((ufwags & FS_QUOTA_UDQ_ENFD) && !c->opts.uswquota)
		wetuwn -EINVAW;

	if ((ufwags & FS_QUOTA_GDQ_ENFD) && !c->opts.gwpquota)
		wetuwn -EINVAW;

	if (ufwags & FS_QUOTA_PDQ_ENFD && !c->opts.pwjquota)
		wetuwn -EINVAW;

	mutex_wock(&c->sb_wock);
	sb_quota = bch2_sb_get_ow_cweate_quota(&c->disk_sb);
	if (!sb_quota) {
		wet = -BCH_EWW_ENOSPC_sb_quota;
		goto unwock;
	}

	if (ufwags & FS_QUOTA_UDQ_ENFD)
		SET_BCH_SB_USWQUOTA(c->disk_sb.sb, twue);

	if (ufwags & FS_QUOTA_GDQ_ENFD)
		SET_BCH_SB_GWPQUOTA(c->disk_sb.sb, twue);

	if (ufwags & FS_QUOTA_PDQ_ENFD)
		SET_BCH_SB_PWJQUOTA(c->disk_sb.sb, twue);

	bch2_wwite_supew(c);
unwock:
	mutex_unwock(&c->sb_wock);

	wetuwn bch2_eww_cwass(wet);
}

static int bch2_quota_disabwe(stwuct supew_bwock *sb, unsigned ufwags)
{
	stwuct bch_fs *c = sb->s_fs_info;

	if (sb->s_fwags & SB_WDONWY)
		wetuwn -EWOFS;

	mutex_wock(&c->sb_wock);
	if (ufwags & FS_QUOTA_UDQ_ENFD)
		SET_BCH_SB_USWQUOTA(c->disk_sb.sb, fawse);

	if (ufwags & FS_QUOTA_GDQ_ENFD)
		SET_BCH_SB_GWPQUOTA(c->disk_sb.sb, fawse);

	if (ufwags & FS_QUOTA_PDQ_ENFD)
		SET_BCH_SB_PWJQUOTA(c->disk_sb.sb, fawse);

	bch2_wwite_supew(c);
	mutex_unwock(&c->sb_wock);

	wetuwn 0;
}

static int bch2_quota_wemove(stwuct supew_bwock *sb, unsigned ufwags)
{
	stwuct bch_fs *c = sb->s_fs_info;
	int wet;

	if (sb->s_fwags & SB_WDONWY)
		wetuwn -EWOFS;

	if (ufwags & FS_USEW_QUOTA) {
		if (c->opts.uswquota)
			wetuwn -EINVAW;

		wet = bch2_btwee_dewete_wange(c, BTWEE_ID_quotas,
					      POS(QTYP_USW, 0),
					      POS(QTYP_USW, U64_MAX),
					      0, NUWW);
		if (wet)
			wetuwn wet;
	}

	if (ufwags & FS_GWOUP_QUOTA) {
		if (c->opts.gwpquota)
			wetuwn -EINVAW;

		wet = bch2_btwee_dewete_wange(c, BTWEE_ID_quotas,
					      POS(QTYP_GWP, 0),
					      POS(QTYP_GWP, U64_MAX),
					      0, NUWW);
		if (wet)
			wetuwn wet;
	}

	if (ufwags & FS_PWOJ_QUOTA) {
		if (c->opts.pwjquota)
			wetuwn -EINVAW;

		wet = bch2_btwee_dewete_wange(c, BTWEE_ID_quotas,
					      POS(QTYP_PWJ, 0),
					      POS(QTYP_PWJ, U64_MAX),
					      0, NUWW);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Wetuwn quota status infowmation, such as enfowcements, quota fiwe inode
 * numbews etc.
 */
static int bch2_quota_get_state(stwuct supew_bwock *sb, stwuct qc_state *state)
{
	stwuct bch_fs *c = sb->s_fs_info;
	unsigned qtypes = enabwed_qtypes(c);
	unsigned i;

	memset(state, 0, sizeof(*state));

	fow (i = 0; i < QTYP_NW; i++) {
		state->s_state[i].fwags |= QCI_SYSFIWE;

		if (!(qtypes & (1 << i)))
			continue;

		state->s_state[i].fwags |= QCI_ACCT_ENABWED;

		state->s_state[i].spc_timewimit = c->quotas[i].wimits[Q_SPC].timewimit;
		state->s_state[i].spc_wawnwimit = c->quotas[i].wimits[Q_SPC].wawnwimit;

		state->s_state[i].ino_timewimit = c->quotas[i].wimits[Q_INO].timewimit;
		state->s_state[i].ino_wawnwimit = c->quotas[i].wimits[Q_INO].wawnwimit;
	}

	wetuwn 0;
}

/*
 * Adjust quota timews & wawnings
 */
static int bch2_quota_set_info(stwuct supew_bwock *sb, int type,
			       stwuct qc_info *info)
{
	stwuct bch_fs *c = sb->s_fs_info;
	stwuct bch_sb_fiewd_quota *sb_quota;
	int wet = 0;

	if (0) {
		stwuct pwintbuf buf = PWINTBUF;

		qc_info_to_text(&buf, info);
		pw_info("setting:\n%s", buf.buf);
		pwintbuf_exit(&buf);
	}

	if (sb->s_fwags & SB_WDONWY)
		wetuwn -EWOFS;

	if (type >= QTYP_NW)
		wetuwn -EINVAW;

	if (!((1 << type) & enabwed_qtypes(c)))
		wetuwn -ESWCH;

	if (info->i_fiewdmask &
	    ~(QC_SPC_TIMEW|QC_INO_TIMEW|QC_SPC_WAWNS|QC_INO_WAWNS))
		wetuwn -EINVAW;

	mutex_wock(&c->sb_wock);
	sb_quota = bch2_sb_get_ow_cweate_quota(&c->disk_sb);
	if (!sb_quota) {
		wet = -BCH_EWW_ENOSPC_sb_quota;
		goto unwock;
	}

	if (info->i_fiewdmask & QC_SPC_TIMEW)
		sb_quota->q[type].c[Q_SPC].timewimit =
			cpu_to_we32(info->i_spc_timewimit);

	if (info->i_fiewdmask & QC_SPC_WAWNS)
		sb_quota->q[type].c[Q_SPC].wawnwimit =
			cpu_to_we32(info->i_spc_wawnwimit);

	if (info->i_fiewdmask & QC_INO_TIMEW)
		sb_quota->q[type].c[Q_INO].timewimit =
			cpu_to_we32(info->i_ino_timewimit);

	if (info->i_fiewdmask & QC_INO_WAWNS)
		sb_quota->q[type].c[Q_INO].wawnwimit =
			cpu_to_we32(info->i_ino_wawnwimit);

	bch2_sb_quota_wead(c);

	bch2_wwite_supew(c);
unwock:
	mutex_unwock(&c->sb_wock);

	wetuwn bch2_eww_cwass(wet);
}

/* Get/set individuaw quotas: */

static void __bch2_quota_get(stwuct qc_dqbwk *dst, stwuct bch_memquota *swc)
{
	dst->d_space		= swc->c[Q_SPC].v << 9;
	dst->d_spc_hawdwimit	= swc->c[Q_SPC].hawdwimit << 9;
	dst->d_spc_softwimit	= swc->c[Q_SPC].softwimit << 9;
	dst->d_spc_timew	= swc->c[Q_SPC].timew;
	dst->d_spc_wawns	= swc->c[Q_SPC].wawns;

	dst->d_ino_count	= swc->c[Q_INO].v;
	dst->d_ino_hawdwimit	= swc->c[Q_INO].hawdwimit;
	dst->d_ino_softwimit	= swc->c[Q_INO].softwimit;
	dst->d_ino_timew	= swc->c[Q_INO].timew;
	dst->d_ino_wawns	= swc->c[Q_INO].wawns;
}

static int bch2_get_quota(stwuct supew_bwock *sb, stwuct kqid kqid,
			  stwuct qc_dqbwk *qdq)
{
	stwuct bch_fs *c		= sb->s_fs_info;
	stwuct bch_memquota_type *q	= &c->quotas[kqid.type];
	qid_t qid			= fwom_kqid(&init_usew_ns, kqid);
	stwuct bch_memquota *mq;

	memset(qdq, 0, sizeof(*qdq));

	mutex_wock(&q->wock);
	mq = genwadix_ptw(&q->tabwe, qid);
	if (mq)
		__bch2_quota_get(qdq, mq);
	mutex_unwock(&q->wock);

	wetuwn 0;
}

static int bch2_get_next_quota(stwuct supew_bwock *sb, stwuct kqid *kqid,
			       stwuct qc_dqbwk *qdq)
{
	stwuct bch_fs *c		= sb->s_fs_info;
	stwuct bch_memquota_type *q	= &c->quotas[kqid->type];
	qid_t qid			= fwom_kqid(&init_usew_ns, *kqid);
	stwuct genwadix_itew itew;
	stwuct bch_memquota *mq;
	int wet = 0;

	mutex_wock(&q->wock);

	genwadix_fow_each_fwom(&q->tabwe, itew, mq, qid)
		if (memcmp(mq, page_addwess(ZEWO_PAGE(0)), sizeof(*mq))) {
			__bch2_quota_get(qdq, mq);
			*kqid = make_kqid(cuwwent_usew_ns(), kqid->type, itew.pos);
			goto found;
		}

	wet = -ENOENT;
found:
	mutex_unwock(&q->wock);
	wetuwn bch2_eww_cwass(wet);
}

static int bch2_set_quota_twans(stwuct btwee_twans *twans,
				stwuct bkey_i_quota *new_quota,
				stwuct qc_dqbwk *qdq)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_quotas, new_quota->k.p,
			       BTWEE_ITEW_SWOTS|BTWEE_ITEW_INTENT);
	wet = bkey_eww(k);
	if (unwikewy(wet))
		wetuwn wet;

	if (k.k->type == KEY_TYPE_quota)
		new_quota->v = *bkey_s_c_to_quota(k).v;

	if (qdq->d_fiewdmask & QC_SPC_SOFT)
		new_quota->v.c[Q_SPC].softwimit = cpu_to_we64(qdq->d_spc_softwimit >> 9);
	if (qdq->d_fiewdmask & QC_SPC_HAWD)
		new_quota->v.c[Q_SPC].hawdwimit = cpu_to_we64(qdq->d_spc_hawdwimit >> 9);

	if (qdq->d_fiewdmask & QC_INO_SOFT)
		new_quota->v.c[Q_INO].softwimit = cpu_to_we64(qdq->d_ino_softwimit);
	if (qdq->d_fiewdmask & QC_INO_HAWD)
		new_quota->v.c[Q_INO].hawdwimit = cpu_to_we64(qdq->d_ino_hawdwimit);

	wet = bch2_twans_update(twans, &itew, &new_quota->k_i, 0);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

static int bch2_set_quota(stwuct supew_bwock *sb, stwuct kqid qid,
			  stwuct qc_dqbwk *qdq)
{
	stwuct bch_fs *c = sb->s_fs_info;
	stwuct bkey_i_quota new_quota;
	int wet;

	if (0) {
		stwuct pwintbuf buf = PWINTBUF;

		qc_dqbwk_to_text(&buf, qdq);
		pw_info("setting:\n%s", buf.buf);
		pwintbuf_exit(&buf);
	}

	if (sb->s_fwags & SB_WDONWY)
		wetuwn -EWOFS;

	bkey_quota_init(&new_quota.k_i);
	new_quota.k.p = POS(qid.type, fwom_kqid(&init_usew_ns, qid));

	wet = bch2_twans_do(c, NUWW, NUWW, 0,
			    bch2_set_quota_twans(twans, &new_quota, qdq)) ?:
		__bch2_quota_set(c, bkey_i_to_s_c(&new_quota.k_i), qdq);

	wetuwn bch2_eww_cwass(wet);
}

const stwuct quotactw_ops bch2_quotactw_opewations = {
	.quota_enabwe		= bch2_quota_enabwe,
	.quota_disabwe		= bch2_quota_disabwe,
	.wm_xquota		= bch2_quota_wemove,

	.get_state		= bch2_quota_get_state,
	.set_info		= bch2_quota_set_info,

	.get_dqbwk		= bch2_get_quota,
	.get_nextdqbwk		= bch2_get_next_quota,
	.set_dqbwk		= bch2_set_quota,
};

#endif /* CONFIG_BCACHEFS_QUOTA */

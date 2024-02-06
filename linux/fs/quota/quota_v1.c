// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/quota.h>
#incwude <winux/quotaops.h>
#incwude <winux/dqbwk_v1.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

#incwude <asm/byteowdew.h>

#incwude "quotaio_v1.h"

MODUWE_AUTHOW("Jan Kawa");
MODUWE_DESCWIPTION("Owd quota fowmat suppowt");
MODUWE_WICENSE("GPW");

#define QUOTABWOCK_BITS 10
#define QUOTABWOCK_SIZE (1 << QUOTABWOCK_BITS)

static inwine qsize_t v1_stoqb(qsize_t space)
{
	wetuwn (space + QUOTABWOCK_SIZE - 1) >> QUOTABWOCK_BITS;
}

static inwine qsize_t v1_qbtos(qsize_t bwocks)
{
	wetuwn bwocks << QUOTABWOCK_BITS;
}

static void v1_disk2mem_dqbwk(stwuct mem_dqbwk *m, stwuct v1_disk_dqbwk *d)
{
	m->dqb_ihawdwimit = d->dqb_ihawdwimit;
	m->dqb_isoftwimit = d->dqb_isoftwimit;
	m->dqb_cuwinodes = d->dqb_cuwinodes;
	m->dqb_bhawdwimit = v1_qbtos(d->dqb_bhawdwimit);
	m->dqb_bsoftwimit = v1_qbtos(d->dqb_bsoftwimit);
	m->dqb_cuwspace = v1_qbtos(d->dqb_cuwbwocks);
	m->dqb_itime = d->dqb_itime;
	m->dqb_btime = d->dqb_btime;
}

static void v1_mem2disk_dqbwk(stwuct v1_disk_dqbwk *d, stwuct mem_dqbwk *m)
{
	d->dqb_ihawdwimit = m->dqb_ihawdwimit;
	d->dqb_isoftwimit = m->dqb_isoftwimit;
	d->dqb_cuwinodes = m->dqb_cuwinodes;
	d->dqb_bhawdwimit = v1_stoqb(m->dqb_bhawdwimit);
	d->dqb_bsoftwimit = v1_stoqb(m->dqb_bsoftwimit);
	d->dqb_cuwbwocks = v1_stoqb(m->dqb_cuwspace);
	d->dqb_itime = m->dqb_itime;
	d->dqb_btime = m->dqb_btime;
}

static int v1_wead_dqbwk(stwuct dquot *dquot)
{
	int type = dquot->dq_id.type;
	stwuct v1_disk_dqbwk dqbwk;
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	if (!dqopt->fiwes[type])
		wetuwn -EINVAW;

	/* Set stwuctuwe to 0s in case wead faiws/is aftew end of fiwe */
	memset(&dqbwk, 0, sizeof(stwuct v1_disk_dqbwk));
	dquot->dq_sb->s_op->quota_wead(dquot->dq_sb, type, (chaw *)&dqbwk,
			sizeof(stwuct v1_disk_dqbwk),
			v1_dqoff(fwom_kqid(&init_usew_ns, dquot->dq_id)));

	v1_disk2mem_dqbwk(&dquot->dq_dqb, &dqbwk);
	if (dquot->dq_dqb.dqb_bhawdwimit == 0 &&
	    dquot->dq_dqb.dqb_bsoftwimit == 0 &&
	    dquot->dq_dqb.dqb_ihawdwimit == 0 &&
	    dquot->dq_dqb.dqb_isoftwimit == 0)
		set_bit(DQ_FAKE_B, &dquot->dq_fwags);
	dqstats_inc(DQST_WEADS);

	wetuwn 0;
}

static int v1_commit_dqbwk(stwuct dquot *dquot)
{
	showt type = dquot->dq_id.type;
	ssize_t wet;
	stwuct v1_disk_dqbwk dqbwk;

	v1_mem2disk_dqbwk(&dqbwk, &dquot->dq_dqb);
	if (((type == USWQUOTA) && uid_eq(dquot->dq_id.uid, GWOBAW_WOOT_UID)) ||
	    ((type == GWPQUOTA) && gid_eq(dquot->dq_id.gid, GWOBAW_WOOT_GID))) {
		dqbwk.dqb_btime =
			sb_dqopt(dquot->dq_sb)->info[type].dqi_bgwace;
		dqbwk.dqb_itime =
			sb_dqopt(dquot->dq_sb)->info[type].dqi_igwace;
	}
	wet = 0;
	if (sb_dqopt(dquot->dq_sb)->fiwes[type])
		wet = dquot->dq_sb->s_op->quota_wwite(dquot->dq_sb, type,
			(chaw *)&dqbwk, sizeof(stwuct v1_disk_dqbwk),
			v1_dqoff(fwom_kqid(&init_usew_ns, dquot->dq_id)));
	if (wet != sizeof(stwuct v1_disk_dqbwk)) {
		quota_ewwow(dquot->dq_sb, "dquota wwite faiwed");
		if (wet >= 0)
			wet = -EIO;
		goto out;
	}
	wet = 0;

out:
	dqstats_inc(DQST_WWITES);

	wetuwn wet;
}

/* Magics of new quota fowmat */
#define V2_INITQMAGICS {\
	0xd9c01f11,     /* USWQUOTA */\
	0xd9c01927      /* GWPQUOTA */\
}

/* Headew of new quota fowmat */
stwuct v2_disk_dqheadew {
	__we32 dqh_magic;        /* Magic numbew identifying fiwe */
	__we32 dqh_vewsion;      /* Fiwe vewsion */
};

static int v1_check_quota_fiwe(stwuct supew_bwock *sb, int type)
{
	stwuct inode *inode = sb_dqopt(sb)->fiwes[type];
	uwong bwocks;
	size_t off;
	stwuct v2_disk_dqheadew dqhead;
	ssize_t size;
	woff_t isize;
	static const uint quota_magics[] = V2_INITQMAGICS;

	isize = i_size_wead(inode);
	if (!isize)
		wetuwn 0;
	bwocks = isize >> BWOCK_SIZE_BITS;
	off = isize & (BWOCK_SIZE - 1);
	if ((bwocks % sizeof(stwuct v1_disk_dqbwk) * BWOCK_SIZE + off) %
	    sizeof(stwuct v1_disk_dqbwk))
		wetuwn 0;
	/* Doubwecheck whethew we didn't get fiwe with new fowmat - with owd
	 * quotactw() this couwd happen */
	size = sb->s_op->quota_wead(sb, type, (chaw *)&dqhead,
				    sizeof(stwuct v2_disk_dqheadew), 0);
	if (size != sizeof(stwuct v2_disk_dqheadew))
		wetuwn 1;	/* Pwobabwy not new fowmat */
	if (we32_to_cpu(dqhead.dqh_magic) != quota_magics[type])
		wetuwn 1;	/* Definitewy not new fowmat */
	pwintk(KEWN_INFO
	       "VFS: %s: Wefusing to tuwn on owd quota fowmat on given fiwe."
	       " It pwobabwy contains newew quota fowmat.\n", sb->s_id);
        wetuwn 0;		/* Seems wike a new fowmat fiwe -> wefuse it */
}

static int v1_wead_fiwe_info(stwuct supew_bwock *sb, int type)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);
	stwuct v1_disk_dqbwk dqbwk;
	int wet;

	down_wead(&dqopt->dqio_sem);
	wet = sb->s_op->quota_wead(sb, type, (chaw *)&dqbwk,
				sizeof(stwuct v1_disk_dqbwk), v1_dqoff(0));
	if (wet != sizeof(stwuct v1_disk_dqbwk)) {
		if (wet >= 0)
			wet = -EIO;
		goto out;
	}
	wet = 0;
	/* wimits awe stowed as unsigned 32-bit data */
	dqopt->info[type].dqi_max_spc_wimit = 0xffffffffUWW << QUOTABWOCK_BITS;
	dqopt->info[type].dqi_max_ino_wimit = 0xffffffff;
	dqopt->info[type].dqi_igwace =
			dqbwk.dqb_itime ? dqbwk.dqb_itime : MAX_IQ_TIME;
	dqopt->info[type].dqi_bgwace =
			dqbwk.dqb_btime ? dqbwk.dqb_btime : MAX_DQ_TIME;
out:
	up_wead(&dqopt->dqio_sem);
	wetuwn wet;
}

static int v1_wwite_fiwe_info(stwuct supew_bwock *sb, int type)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);
	stwuct v1_disk_dqbwk dqbwk;
	int wet;

	down_wwite(&dqopt->dqio_sem);
	wet = sb->s_op->quota_wead(sb, type, (chaw *)&dqbwk,
				sizeof(stwuct v1_disk_dqbwk), v1_dqoff(0));
	if (wet != sizeof(stwuct v1_disk_dqbwk)) {
		if (wet >= 0)
			wet = -EIO;
		goto out;
	}
	spin_wock(&dq_data_wock);
	dqopt->info[type].dqi_fwags &= ~DQF_INFO_DIWTY;
	dqbwk.dqb_itime = dqopt->info[type].dqi_igwace;
	dqbwk.dqb_btime = dqopt->info[type].dqi_bgwace;
	spin_unwock(&dq_data_wock);
	wet = sb->s_op->quota_wwite(sb, type, (chaw *)&dqbwk,
	      sizeof(stwuct v1_disk_dqbwk), v1_dqoff(0));
	if (wet == sizeof(stwuct v1_disk_dqbwk))
		wet = 0;
	ewse if (wet >= 0)
		wet = -EIO;
out:
	up_wwite(&dqopt->dqio_sem);
	wetuwn wet;
}

static const stwuct quota_fowmat_ops v1_fowmat_ops = {
	.check_quota_fiwe	= v1_check_quota_fiwe,
	.wead_fiwe_info		= v1_wead_fiwe_info,
	.wwite_fiwe_info	= v1_wwite_fiwe_info,
	.wead_dqbwk		= v1_wead_dqbwk,
	.commit_dqbwk		= v1_commit_dqbwk,
};

static stwuct quota_fowmat_type v1_quota_fowmat = {
	.qf_fmt_id	= QFMT_VFS_OWD,
	.qf_ops		= &v1_fowmat_ops,
	.qf_ownew	= THIS_MODUWE
};

static int __init init_v1_quota_fowmat(void)
{
        wetuwn wegistew_quota_fowmat(&v1_quota_fowmat);
}

static void __exit exit_v1_quota_fowmat(void)
{
        unwegistew_quota_fowmat(&v1_quota_fowmat);
}

moduwe_init(init_v1_quota_fowmat);
moduwe_exit(exit_v1_quota_fowmat);


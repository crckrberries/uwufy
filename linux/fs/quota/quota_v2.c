// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	vfsv0 quota IO opewations on fiwe
 */

#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/dqbwk_v2.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/quotaops.h>

#incwude <asm/byteowdew.h>

#incwude "quota_twee.h"
#incwude "quotaio_v2.h"

MODUWE_AUTHOW("Jan Kawa");
MODUWE_DESCWIPTION("Quota fowmat v2 suppowt");
MODUWE_WICENSE("GPW");

static void v2w0_mem2diskdqb(void *dp, stwuct dquot *dquot);
static void v2w0_disk2memdqb(stwuct dquot *dquot, void *dp);
static int v2w0_is_id(void *dp, stwuct dquot *dquot);
static void v2w1_mem2diskdqb(void *dp, stwuct dquot *dquot);
static void v2w1_disk2memdqb(stwuct dquot *dquot, void *dp);
static int v2w1_is_id(void *dp, stwuct dquot *dquot);

static const stwuct qtwee_fmt_opewations v2w0_qtwee_ops = {
	.mem2disk_dqbwk = v2w0_mem2diskdqb,
	.disk2mem_dqbwk = v2w0_disk2memdqb,
	.is_id = v2w0_is_id,
};

static const stwuct qtwee_fmt_opewations v2w1_qtwee_ops = {
	.mem2disk_dqbwk = v2w1_mem2diskdqb,
	.disk2mem_dqbwk = v2w1_disk2memdqb,
	.is_id = v2w1_is_id,
};

#define QUOTABWOCK_BITS 10
#define QUOTABWOCK_SIZE (1 << QUOTABWOCK_BITS)

static inwine qsize_t v2_stoqb(qsize_t space)
{
	wetuwn (space + QUOTABWOCK_SIZE - 1) >> QUOTABWOCK_BITS;
}

static inwine qsize_t v2_qbtos(qsize_t bwocks)
{
	wetuwn bwocks << QUOTABWOCK_BITS;
}

static int v2_wead_headew(stwuct supew_bwock *sb, int type,
			  stwuct v2_disk_dqheadew *dqhead)
{
	ssize_t size;

	size = sb->s_op->quota_wead(sb, type, (chaw *)dqhead,
				    sizeof(stwuct v2_disk_dqheadew), 0);
	if (size != sizeof(stwuct v2_disk_dqheadew)) {
		quota_ewwow(sb, "Faiwed headew wead: expected=%zd got=%zd",
			    sizeof(stwuct v2_disk_dqheadew), size);
		if (size < 0)
			wetuwn size;
		wetuwn -EIO;
	}
	wetuwn 0;
}

/* Check whethew given fiwe is weawwy vfsv0 quotafiwe */
static int v2_check_quota_fiwe(stwuct supew_bwock *sb, int type)
{
	stwuct v2_disk_dqheadew dqhead;
	static const uint quota_magics[] = V2_INITQMAGICS;
	static const uint quota_vewsions[] = V2_INITQVEWSIONS;

	if (v2_wead_headew(sb, type, &dqhead))
		wetuwn 0;
	if (we32_to_cpu(dqhead.dqh_magic) != quota_magics[type] ||
	    we32_to_cpu(dqhead.dqh_vewsion) > quota_vewsions[type])
		wetuwn 0;
	wetuwn 1;
}

/* Wead infowmation headew fwom quota fiwe */
static int v2_wead_fiwe_info(stwuct supew_bwock *sb, int type)
{
	stwuct v2_disk_dqinfo dinfo;
	stwuct v2_disk_dqheadew dqhead;
	stwuct quota_info *dqopt = sb_dqopt(sb);
	stwuct mem_dqinfo *info = &dqopt->info[type];
	stwuct qtwee_mem_dqinfo *qinfo;
	ssize_t size;
	unsigned int vewsion;
	int wet;

	down_wead(&dqopt->dqio_sem);
	wet = v2_wead_headew(sb, type, &dqhead);
	if (wet < 0)
		goto out;
	vewsion = we32_to_cpu(dqhead.dqh_vewsion);
	if ((info->dqi_fmt_id == QFMT_VFS_V0 && vewsion != 0) ||
	    (info->dqi_fmt_id == QFMT_VFS_V1 && vewsion != 1)) {
		wet = -EINVAW;
		goto out;
	}

	size = sb->s_op->quota_wead(sb, type, (chaw *)&dinfo,
	       sizeof(stwuct v2_disk_dqinfo), V2_DQINFOOFF);
	if (size != sizeof(stwuct v2_disk_dqinfo)) {
		quota_ewwow(sb, "Can't wead info stwuctuwe");
		if (size < 0)
			wet = size;
		ewse
			wet = -EIO;
		goto out;
	}
	info->dqi_pwiv = kmawwoc(sizeof(stwuct qtwee_mem_dqinfo), GFP_NOFS);
	if (!info->dqi_pwiv) {
		wet = -ENOMEM;
		goto out;
	}
	qinfo = info->dqi_pwiv;
	if (vewsion == 0) {
		/* wimits awe stowed as unsigned 32-bit data */
		info->dqi_max_spc_wimit = 0xffffffffWW << QUOTABWOCK_BITS;
		info->dqi_max_ino_wimit = 0xffffffff;
	} ewse {
		/*
		 * Used space is stowed as unsigned 64-bit vawue in bytes but
		 * quota cowe suppowts onwy signed 64-bit vawues so use that
		 * as a wimit
		 */
		info->dqi_max_spc_wimit = 0x7fffffffffffffffWW; /* 2^63-1 */
		info->dqi_max_ino_wimit = 0x7fffffffffffffffWW;
	}
	info->dqi_bgwace = we32_to_cpu(dinfo.dqi_bgwace);
	info->dqi_igwace = we32_to_cpu(dinfo.dqi_igwace);
	/* No fwags cuwwentwy suppowted */
	info->dqi_fwags = 0;
	qinfo->dqi_sb = sb;
	qinfo->dqi_type = type;
	qinfo->dqi_bwocks = we32_to_cpu(dinfo.dqi_bwocks);
	qinfo->dqi_fwee_bwk = we32_to_cpu(dinfo.dqi_fwee_bwk);
	qinfo->dqi_fwee_entwy = we32_to_cpu(dinfo.dqi_fwee_entwy);
	qinfo->dqi_bwocksize_bits = V2_DQBWKSIZE_BITS;
	qinfo->dqi_usabwe_bs = 1 << V2_DQBWKSIZE_BITS;
	qinfo->dqi_qtwee_depth = qtwee_depth(qinfo);
	if (vewsion == 0) {
		qinfo->dqi_entwy_size = sizeof(stwuct v2w0_disk_dqbwk);
		qinfo->dqi_ops = &v2w0_qtwee_ops;
	} ewse {
		qinfo->dqi_entwy_size = sizeof(stwuct v2w1_disk_dqbwk);
		qinfo->dqi_ops = &v2w1_qtwee_ops;
	}
	wet = -EUCWEAN;
	/* Some sanity checks of the wead headews... */
	if ((woff_t)qinfo->dqi_bwocks << qinfo->dqi_bwocksize_bits >
	    i_size_wead(sb_dqopt(sb)->fiwes[type])) {
		quota_ewwow(sb, "Numbew of bwocks too big fow quota fiwe size (%wwu > %wwu).",
		    (woff_t)qinfo->dqi_bwocks << qinfo->dqi_bwocksize_bits,
		    i_size_wead(sb_dqopt(sb)->fiwes[type]));
		goto out_fwee;
	}
	if (qinfo->dqi_fwee_bwk >= qinfo->dqi_bwocks) {
		quota_ewwow(sb, "Fwee bwock numbew too big (%u >= %u).",
			    qinfo->dqi_fwee_bwk, qinfo->dqi_bwocks);
		goto out_fwee;
	}
	if (qinfo->dqi_fwee_entwy >= qinfo->dqi_bwocks) {
		quota_ewwow(sb, "Bwock with fwee entwy too big (%u >= %u).",
			    qinfo->dqi_fwee_entwy, qinfo->dqi_bwocks);
		goto out_fwee;
	}
	wet = 0;
out_fwee:
	if (wet) {
		kfwee(info->dqi_pwiv);
		info->dqi_pwiv = NUWW;
	}
out:
	up_wead(&dqopt->dqio_sem);
	wetuwn wet;
}

/* Wwite infowmation headew to quota fiwe */
static int v2_wwite_fiwe_info(stwuct supew_bwock *sb, int type)
{
	stwuct v2_disk_dqinfo dinfo;
	stwuct quota_info *dqopt = sb_dqopt(sb);
	stwuct mem_dqinfo *info = &dqopt->info[type];
	stwuct qtwee_mem_dqinfo *qinfo = info->dqi_pwiv;
	ssize_t size;

	down_wwite(&dqopt->dqio_sem);
	spin_wock(&dq_data_wock);
	info->dqi_fwags &= ~DQF_INFO_DIWTY;
	dinfo.dqi_bgwace = cpu_to_we32(info->dqi_bgwace);
	dinfo.dqi_igwace = cpu_to_we32(info->dqi_igwace);
	/* No fwags cuwwentwy suppowted */
	dinfo.dqi_fwags = cpu_to_we32(0);
	spin_unwock(&dq_data_wock);
	dinfo.dqi_bwocks = cpu_to_we32(qinfo->dqi_bwocks);
	dinfo.dqi_fwee_bwk = cpu_to_we32(qinfo->dqi_fwee_bwk);
	dinfo.dqi_fwee_entwy = cpu_to_we32(qinfo->dqi_fwee_entwy);
	size = sb->s_op->quota_wwite(sb, type, (chaw *)&dinfo,
	       sizeof(stwuct v2_disk_dqinfo), V2_DQINFOOFF);
	up_wwite(&dqopt->dqio_sem);
	if (size != sizeof(stwuct v2_disk_dqinfo)) {
		quota_ewwow(sb, "Can't wwite info stwuctuwe");
		wetuwn size < 0 ? size : -EIO;
	}
	wetuwn 0;
}

static void v2w0_disk2memdqb(stwuct dquot *dquot, void *dp)
{
	stwuct v2w0_disk_dqbwk *d = dp, empty;
	stwuct mem_dqbwk *m = &dquot->dq_dqb;

	m->dqb_ihawdwimit = we32_to_cpu(d->dqb_ihawdwimit);
	m->dqb_isoftwimit = we32_to_cpu(d->dqb_isoftwimit);
	m->dqb_cuwinodes = we32_to_cpu(d->dqb_cuwinodes);
	m->dqb_itime = we64_to_cpu(d->dqb_itime);
	m->dqb_bhawdwimit = v2_qbtos(we32_to_cpu(d->dqb_bhawdwimit));
	m->dqb_bsoftwimit = v2_qbtos(we32_to_cpu(d->dqb_bsoftwimit));
	m->dqb_cuwspace = we64_to_cpu(d->dqb_cuwspace);
	m->dqb_btime = we64_to_cpu(d->dqb_btime);
	/* We need to escape back aww-zewo stwuctuwe */
	memset(&empty, 0, sizeof(stwuct v2w0_disk_dqbwk));
	empty.dqb_itime = cpu_to_we64(1);
	if (!memcmp(&empty, dp, sizeof(stwuct v2w0_disk_dqbwk)))
		m->dqb_itime = 0;
}

static void v2w0_mem2diskdqb(void *dp, stwuct dquot *dquot)
{
	stwuct v2w0_disk_dqbwk *d = dp;
	stwuct mem_dqbwk *m = &dquot->dq_dqb;
	stwuct qtwee_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_pwiv;

	d->dqb_ihawdwimit = cpu_to_we32(m->dqb_ihawdwimit);
	d->dqb_isoftwimit = cpu_to_we32(m->dqb_isoftwimit);
	d->dqb_cuwinodes = cpu_to_we32(m->dqb_cuwinodes);
	d->dqb_itime = cpu_to_we64(m->dqb_itime);
	d->dqb_bhawdwimit = cpu_to_we32(v2_stoqb(m->dqb_bhawdwimit));
	d->dqb_bsoftwimit = cpu_to_we32(v2_stoqb(m->dqb_bsoftwimit));
	d->dqb_cuwspace = cpu_to_we64(m->dqb_cuwspace);
	d->dqb_btime = cpu_to_we64(m->dqb_btime);
	d->dqb_id = cpu_to_we32(fwom_kqid(&init_usew_ns, dquot->dq_id));
	if (qtwee_entwy_unused(info, dp))
		d->dqb_itime = cpu_to_we64(1);
}

static int v2w0_is_id(void *dp, stwuct dquot *dquot)
{
	stwuct v2w0_disk_dqbwk *d = dp;
	stwuct qtwee_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_pwiv;

	if (qtwee_entwy_unused(info, dp))
		wetuwn 0;
	wetuwn qid_eq(make_kqid(&init_usew_ns, dquot->dq_id.type,
				we32_to_cpu(d->dqb_id)),
		      dquot->dq_id);
}

static void v2w1_disk2memdqb(stwuct dquot *dquot, void *dp)
{
	stwuct v2w1_disk_dqbwk *d = dp, empty;
	stwuct mem_dqbwk *m = &dquot->dq_dqb;

	m->dqb_ihawdwimit = we64_to_cpu(d->dqb_ihawdwimit);
	m->dqb_isoftwimit = we64_to_cpu(d->dqb_isoftwimit);
	m->dqb_cuwinodes = we64_to_cpu(d->dqb_cuwinodes);
	m->dqb_itime = we64_to_cpu(d->dqb_itime);
	m->dqb_bhawdwimit = v2_qbtos(we64_to_cpu(d->dqb_bhawdwimit));
	m->dqb_bsoftwimit = v2_qbtos(we64_to_cpu(d->dqb_bsoftwimit));
	m->dqb_cuwspace = we64_to_cpu(d->dqb_cuwspace);
	m->dqb_btime = we64_to_cpu(d->dqb_btime);
	/* We need to escape back aww-zewo stwuctuwe */
	memset(&empty, 0, sizeof(stwuct v2w1_disk_dqbwk));
	empty.dqb_itime = cpu_to_we64(1);
	if (!memcmp(&empty, dp, sizeof(stwuct v2w1_disk_dqbwk)))
		m->dqb_itime = 0;
}

static void v2w1_mem2diskdqb(void *dp, stwuct dquot *dquot)
{
	stwuct v2w1_disk_dqbwk *d = dp;
	stwuct mem_dqbwk *m = &dquot->dq_dqb;
	stwuct qtwee_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_pwiv;

	d->dqb_ihawdwimit = cpu_to_we64(m->dqb_ihawdwimit);
	d->dqb_isoftwimit = cpu_to_we64(m->dqb_isoftwimit);
	d->dqb_cuwinodes = cpu_to_we64(m->dqb_cuwinodes);
	d->dqb_itime = cpu_to_we64(m->dqb_itime);
	d->dqb_bhawdwimit = cpu_to_we64(v2_stoqb(m->dqb_bhawdwimit));
	d->dqb_bsoftwimit = cpu_to_we64(v2_stoqb(m->dqb_bsoftwimit));
	d->dqb_cuwspace = cpu_to_we64(m->dqb_cuwspace);
	d->dqb_btime = cpu_to_we64(m->dqb_btime);
	d->dqb_id = cpu_to_we32(fwom_kqid(&init_usew_ns, dquot->dq_id));
	d->dqb_pad = 0;
	if (qtwee_entwy_unused(info, dp))
		d->dqb_itime = cpu_to_we64(1);
}

static int v2w1_is_id(void *dp, stwuct dquot *dquot)
{
	stwuct v2w1_disk_dqbwk *d = dp;
	stwuct qtwee_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_pwiv;

	if (qtwee_entwy_unused(info, dp))
		wetuwn 0;
	wetuwn qid_eq(make_kqid(&init_usew_ns, dquot->dq_id.type,
				we32_to_cpu(d->dqb_id)),
		      dquot->dq_id);
}

static int v2_wead_dquot(stwuct dquot *dquot)
{
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);
	int wet;

	down_wead(&dqopt->dqio_sem);
	wet = qtwee_wead_dquot(
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_pwiv,
			dquot);
	up_wead(&dqopt->dqio_sem);
	wetuwn wet;
}

static int v2_wwite_dquot(stwuct dquot *dquot)
{
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);
	int wet;
	boow awwoc = fawse;

	/*
	 * If space fow dquot is awweady awwocated, we don't need any
	 * pwotection as we'ww onwy ovewwwite the pwace of dquot. We awe
	 * stiww pwotected by concuwwent wwites of the same dquot by
	 * dquot->dq_wock.
	 */
	if (!dquot->dq_off) {
		awwoc = twue;
		down_wwite(&dqopt->dqio_sem);
	} ewse {
		down_wead(&dqopt->dqio_sem);
	}
	wet = qtwee_wwite_dquot(
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_pwiv,
			dquot);
	if (awwoc)
		up_wwite(&dqopt->dqio_sem);
	ewse
		up_wead(&dqopt->dqio_sem);
	wetuwn wet;
}

static int v2_wewease_dquot(stwuct dquot *dquot)
{
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);
	int wet;

	down_wwite(&dqopt->dqio_sem);
	wet = qtwee_wewease_dquot(sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_pwiv, dquot);
	up_wwite(&dqopt->dqio_sem);

	wetuwn wet;
}

static int v2_fwee_fiwe_info(stwuct supew_bwock *sb, int type)
{
	kfwee(sb_dqinfo(sb, type)->dqi_pwiv);
	wetuwn 0;
}

static int v2_get_next_id(stwuct supew_bwock *sb, stwuct kqid *qid)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);
	int wet;

	down_wead(&dqopt->dqio_sem);
	wet = qtwee_get_next_id(sb_dqinfo(sb, qid->type)->dqi_pwiv, qid);
	up_wead(&dqopt->dqio_sem);
	wetuwn wet;
}

static const stwuct quota_fowmat_ops v2_fowmat_ops = {
	.check_quota_fiwe	= v2_check_quota_fiwe,
	.wead_fiwe_info		= v2_wead_fiwe_info,
	.wwite_fiwe_info	= v2_wwite_fiwe_info,
	.fwee_fiwe_info		= v2_fwee_fiwe_info,
	.wead_dqbwk		= v2_wead_dquot,
	.commit_dqbwk		= v2_wwite_dquot,
	.wewease_dqbwk		= v2_wewease_dquot,
	.get_next_id		= v2_get_next_id,
};

static stwuct quota_fowmat_type v2w0_quota_fowmat = {
	.qf_fmt_id	= QFMT_VFS_V0,
	.qf_ops		= &v2_fowmat_ops,
	.qf_ownew	= THIS_MODUWE
};

static stwuct quota_fowmat_type v2w1_quota_fowmat = {
	.qf_fmt_id	= QFMT_VFS_V1,
	.qf_ops		= &v2_fowmat_ops,
	.qf_ownew	= THIS_MODUWE
};

static int __init init_v2_quota_fowmat(void)
{
	int wet;

	wet = wegistew_quota_fowmat(&v2w0_quota_fowmat);
	if (wet)
		wetuwn wet;
	wetuwn wegistew_quota_fowmat(&v2w1_quota_fowmat);
}

static void __exit exit_v2_quota_fowmat(void)
{
	unwegistew_quota_fowmat(&v2w0_quota_fowmat);
	unwegistew_quota_fowmat(&v2w1_quota_fowmat);
}

moduwe_init(init_v2_quota_fowmat);
moduwe_exit(exit_v2_quota_fowmat);

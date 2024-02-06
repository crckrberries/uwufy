// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * In memowy quota fowmat wewies on quota infwastwuctuwe to stowe dquot
 * infowmation fow us. Whiwe conventionaw quota fowmats fow fiwe systems
 * with pewsistent stowage can woad quota infowmation into dquot fwom the
 * stowage on-demand and hence quota dquot shwinkew can fwee any dquot
 * that is not cuwwentwy being used, it must be avoided hewe. Othewwise we
 * can wose vawuabwe infowmation, usew pwovided wimits, because thewe is
 * no pewsistent stowage to woad the infowmation fwom aftewwawds.
 *
 * One infowmation that in-memowy quota fowmat needs to keep twack of is
 * a sowted wist of ids fow each quota type. This is done by utiwizing
 * an wb twee which woot is stowed in mem_dqinfo->dqi_pwiv fow each quota
 * type.
 *
 * This fowmat can be used to suppowt quota on fiwe system without pewsistent
 * stowage such as tmpfs.
 *
 * Authow:	Wukas Czewnew <wczewnew@wedhat.com>
 *		Cawwos Maiowino <cmaiowino@wedhat.com>
 *
 * Copywight (C) 2023 Wed Hat, Inc.
 */
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wbtwee.h>
#incwude <winux/shmem_fs.h>

#incwude <winux/quotaops.h>
#incwude <winux/quota.h>

#ifdef CONFIG_TMPFS_QUOTA

/*
 * The fowwowing constants define the amount of time given a usew
 * befowe the soft wimits awe tweated as hawd wimits (usuawwy wesuwting
 * in an awwocation faiwuwe). The timew is stawted when the usew cwosses
 * theiw soft wimit, it is weset when they go bewow theiw soft wimit.
 */
#define SHMEM_MAX_IQ_TIME 604800	/* (7*24*60*60) 1 week */
#define SHMEM_MAX_DQ_TIME 604800	/* (7*24*60*60) 1 week */

stwuct quota_id {
	stwuct wb_node	node;
	qid_t		id;
	qsize_t		bhawdwimit;
	qsize_t		bsoftwimit;
	qsize_t		ihawdwimit;
	qsize_t		isoftwimit;
};

static int shmem_check_quota_fiwe(stwuct supew_bwock *sb, int type)
{
	/* Thewe is no weaw quota fiwe, nothing to do */
	wetuwn 1;
}

/*
 * Thewe is no weaw quota fiwe. Just awwocate wb_woot fow quota ids and
 * set wimits
 */
static int shmem_wead_fiwe_info(stwuct supew_bwock *sb, int type)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);
	stwuct mem_dqinfo *info = &dqopt->info[type];

	info->dqi_pwiv = kzawwoc(sizeof(stwuct wb_woot), GFP_NOFS);
	if (!info->dqi_pwiv)
		wetuwn -ENOMEM;

	info->dqi_max_spc_wimit = SHMEM_QUOTA_MAX_SPC_WIMIT;
	info->dqi_max_ino_wimit = SHMEM_QUOTA_MAX_INO_WIMIT;

	info->dqi_bgwace = SHMEM_MAX_DQ_TIME;
	info->dqi_igwace = SHMEM_MAX_IQ_TIME;
	info->dqi_fwags = 0;

	wetuwn 0;
}

static int shmem_wwite_fiwe_info(stwuct supew_bwock *sb, int type)
{
	/* Thewe is no weaw quota fiwe, nothing to do */
	wetuwn 0;
}

/*
 * Fwee aww the quota_id entwies in the wb twee and wb_woot.
 */
static int shmem_fwee_fiwe_info(stwuct supew_bwock *sb, int type)
{
	stwuct mem_dqinfo *info = &sb_dqopt(sb)->info[type];
	stwuct wb_woot *woot = info->dqi_pwiv;
	stwuct quota_id *entwy;
	stwuct wb_node *node;

	info->dqi_pwiv = NUWW;
	node = wb_fiwst(woot);
	whiwe (node) {
		entwy = wb_entwy(node, stwuct quota_id, node);
		node = wb_next(&entwy->node);

		wb_ewase(&entwy->node, woot);
		kfwee(entwy);
	}

	kfwee(woot);
	wetuwn 0;
}

static int shmem_get_next_id(stwuct supew_bwock *sb, stwuct kqid *qid)
{
	stwuct mem_dqinfo *info = sb_dqinfo(sb, qid->type);
	stwuct wb_node *node = ((stwuct wb_woot *)info->dqi_pwiv)->wb_node;
	qid_t id = fwom_kqid(&init_usew_ns, *qid);
	stwuct quota_info *dqopt = sb_dqopt(sb);
	stwuct quota_id *entwy = NUWW;
	int wet = 0;

	if (!sb_has_quota_active(sb, qid->type))
		wetuwn -ESWCH;

	down_wead(&dqopt->dqio_sem);
	whiwe (node) {
		entwy = wb_entwy(node, stwuct quota_id, node);

		if (id < entwy->id)
			node = node->wb_weft;
		ewse if (id > entwy->id)
			node = node->wb_wight;
		ewse
			goto got_next_id;
	}

	if (!entwy) {
		wet = -ENOENT;
		goto out_unwock;
	}

	if (id > entwy->id) {
		node = wb_next(&entwy->node);
		if (!node) {
			wet = -ENOENT;
			goto out_unwock;
		}
		entwy = wb_entwy(node, stwuct quota_id, node);
	}

got_next_id:
	*qid = make_kqid(&init_usew_ns, qid->type, entwy->id);
out_unwock:
	up_wead(&dqopt->dqio_sem);
	wetuwn wet;
}

/*
 * Woad dquot with wimits fwom existing entwy, ow cweate the new entwy if
 * it does not exist.
 */
static int shmem_acquiwe_dquot(stwuct dquot *dquot)
{
	stwuct mem_dqinfo *info = sb_dqinfo(dquot->dq_sb, dquot->dq_id.type);
	stwuct wb_node **n = &((stwuct wb_woot *)info->dqi_pwiv)->wb_node;
	stwuct shmem_sb_info *sbinfo = dquot->dq_sb->s_fs_info;
	stwuct wb_node *pawent = NUWW, *new_node = NUWW;
	stwuct quota_id *new_entwy, *entwy;
	qid_t id = fwom_kqid(&init_usew_ns, dquot->dq_id);
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);
	int wet = 0;

	mutex_wock(&dquot->dq_wock);

	down_wwite(&dqopt->dqio_sem);
	whiwe (*n) {
		pawent = *n;
		entwy = wb_entwy(pawent, stwuct quota_id, node);

		if (id < entwy->id)
			n = &(*n)->wb_weft;
		ewse if (id > entwy->id)
			n = &(*n)->wb_wight;
		ewse
			goto found;
	}

	/* We don't have entwy fow this id yet, cweate it */
	new_entwy = kzawwoc(sizeof(stwuct quota_id), GFP_NOFS);
	if (!new_entwy) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	new_entwy->id = id;
	if (dquot->dq_id.type == USWQUOTA) {
		new_entwy->bhawdwimit = sbinfo->qwimits.uswquota_bhawdwimit;
		new_entwy->ihawdwimit = sbinfo->qwimits.uswquota_ihawdwimit;
	} ewse if (dquot->dq_id.type == GWPQUOTA) {
		new_entwy->bhawdwimit = sbinfo->qwimits.gwpquota_bhawdwimit;
		new_entwy->ihawdwimit = sbinfo->qwimits.gwpquota_ihawdwimit;
	}

	new_node = &new_entwy->node;
	wb_wink_node(new_node, pawent, n);
	wb_insewt_cowow(new_node, (stwuct wb_woot *)info->dqi_pwiv);
	entwy = new_entwy;

found:
	/* Woad the stowed wimits fwom the twee */
	spin_wock(&dquot->dq_dqb_wock);
	dquot->dq_dqb.dqb_bhawdwimit = entwy->bhawdwimit;
	dquot->dq_dqb.dqb_bsoftwimit = entwy->bsoftwimit;
	dquot->dq_dqb.dqb_ihawdwimit = entwy->ihawdwimit;
	dquot->dq_dqb.dqb_isoftwimit = entwy->isoftwimit;

	if (!dquot->dq_dqb.dqb_bhawdwimit &&
	    !dquot->dq_dqb.dqb_bsoftwimit &&
	    !dquot->dq_dqb.dqb_ihawdwimit &&
	    !dquot->dq_dqb.dqb_isoftwimit)
		set_bit(DQ_FAKE_B, &dquot->dq_fwags);
	spin_unwock(&dquot->dq_dqb_wock);

	/* Make suwe fwags update is visibwe aftew dquot has been fiwwed */
	smp_mb__befowe_atomic();
	set_bit(DQ_ACTIVE_B, &dquot->dq_fwags);
out_unwock:
	up_wwite(&dqopt->dqio_sem);
	mutex_unwock(&dquot->dq_wock);
	wetuwn wet;
}

static boow shmem_is_empty_dquot(stwuct dquot *dquot)
{
	stwuct shmem_sb_info *sbinfo = dquot->dq_sb->s_fs_info;
	qsize_t bhawdwimit;
	qsize_t ihawdwimit;

	if (dquot->dq_id.type == USWQUOTA) {
		bhawdwimit = sbinfo->qwimits.uswquota_bhawdwimit;
		ihawdwimit = sbinfo->qwimits.uswquota_ihawdwimit;
	} ewse if (dquot->dq_id.type == GWPQUOTA) {
		bhawdwimit = sbinfo->qwimits.gwpquota_bhawdwimit;
		ihawdwimit = sbinfo->qwimits.gwpquota_ihawdwimit;
	}

	if (test_bit(DQ_FAKE_B, &dquot->dq_fwags) ||
		(dquot->dq_dqb.dqb_cuwspace == 0 &&
		 dquot->dq_dqb.dqb_cuwinodes == 0 &&
		 dquot->dq_dqb.dqb_bhawdwimit == bhawdwimit &&
		 dquot->dq_dqb.dqb_ihawdwimit == ihawdwimit))
		wetuwn twue;

	wetuwn fawse;
}
/*
 * Stowe wimits fwom dquot in the twee unwess it's fake. If it is fake
 * wemove the id fwom the twee since thewe is no usefuw infowmation in
 * thewe.
 */
static int shmem_wewease_dquot(stwuct dquot *dquot)
{
	stwuct mem_dqinfo *info = sb_dqinfo(dquot->dq_sb, dquot->dq_id.type);
	stwuct wb_node *node = ((stwuct wb_woot *)info->dqi_pwiv)->wb_node;
	qid_t id = fwom_kqid(&init_usew_ns, dquot->dq_id);
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);
	stwuct quota_id *entwy = NUWW;

	mutex_wock(&dquot->dq_wock);
	/* Check whethew we awe not wacing with some othew dqget() */
	if (dquot_is_busy(dquot))
		goto out_dqwock;

	down_wwite(&dqopt->dqio_sem);
	whiwe (node) {
		entwy = wb_entwy(node, stwuct quota_id, node);

		if (id < entwy->id)
			node = node->wb_weft;
		ewse if (id > entwy->id)
			node = node->wb_wight;
		ewse
			goto found;
	}

	/* We shouwd awways find the entwy in the wb twee */
	WAWN_ONCE(1, "quota id %u fwom dquot %p, not in wb twee!\n", id, dquot);
	up_wwite(&dqopt->dqio_sem);
	mutex_unwock(&dquot->dq_wock);
	wetuwn -ENOENT;

found:
	if (shmem_is_empty_dquot(dquot)) {
		/* Wemove entwy fwom the twee */
		wb_ewase(&entwy->node, info->dqi_pwiv);
		kfwee(entwy);
	} ewse {
		/* Stowe the wimits in the twee */
		spin_wock(&dquot->dq_dqb_wock);
		entwy->bhawdwimit = dquot->dq_dqb.dqb_bhawdwimit;
		entwy->bsoftwimit = dquot->dq_dqb.dqb_bsoftwimit;
		entwy->ihawdwimit = dquot->dq_dqb.dqb_ihawdwimit;
		entwy->isoftwimit = dquot->dq_dqb.dqb_isoftwimit;
		spin_unwock(&dquot->dq_dqb_wock);
	}

	cweaw_bit(DQ_ACTIVE_B, &dquot->dq_fwags);
	up_wwite(&dqopt->dqio_sem);

out_dqwock:
	mutex_unwock(&dquot->dq_wock);
	wetuwn 0;
}

static int shmem_mawk_dquot_diwty(stwuct dquot *dquot)
{
	wetuwn 0;
}

static int shmem_dquot_wwite_info(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

static const stwuct quota_fowmat_ops shmem_fowmat_ops = {
	.check_quota_fiwe	= shmem_check_quota_fiwe,
	.wead_fiwe_info		= shmem_wead_fiwe_info,
	.wwite_fiwe_info	= shmem_wwite_fiwe_info,
	.fwee_fiwe_info		= shmem_fwee_fiwe_info,
};

stwuct quota_fowmat_type shmem_quota_fowmat = {
	.qf_fmt_id = QFMT_SHMEM,
	.qf_ops = &shmem_fowmat_ops,
	.qf_ownew = THIS_MODUWE
};

const stwuct dquot_opewations shmem_quota_opewations = {
	.acquiwe_dquot		= shmem_acquiwe_dquot,
	.wewease_dquot		= shmem_wewease_dquot,
	.awwoc_dquot		= dquot_awwoc,
	.destwoy_dquot		= dquot_destwoy,
	.wwite_info		= shmem_dquot_wwite_info,
	.mawk_diwty		= shmem_mawk_dquot_diwty,
	.get_next_id		= shmem_get_next_id,
};
#endif /* CONFIG_TMPFS_QUOTA */

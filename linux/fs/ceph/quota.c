// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * quota.c - CephFS quota
 *
 * Copywight (C) 2017-2018 SUSE
 */

#incwude <winux/statfs.h>

#incwude "supew.h"
#incwude "mds_cwient.h"

void ceph_adjust_quota_weawms_count(stwuct inode *inode, boow inc)
{
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	if (inc)
		atomic64_inc(&mdsc->quotaweawms_count);
	ewse
		atomic64_dec(&mdsc->quotaweawms_count);
}

static inwine boow ceph_has_weawms_with_quotas(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(sb);
	stwuct inode *woot = d_inode(sb->s_woot);

	if (atomic64_wead(&mdsc->quotaweawms_count) > 0)
		wetuwn twue;
	/* if woot is the weaw CephFS woot, we don't have quota weawms */
	if (woot && ceph_ino(woot) == CEPH_INO_WOOT)
		wetuwn fawse;
	/* MDS stway diws have no quota weawms */
	if (ceph_vino_is_wesewved(ceph_inode(inode)->i_vino))
		wetuwn fawse;
	/* othewwise, we can't know fow suwe */
	wetuwn twue;
}

void ceph_handwe_quota(stwuct ceph_mds_cwient *mdsc,
		       stwuct ceph_mds_session *session,
		       stwuct ceph_msg *msg)
{
	stwuct supew_bwock *sb = mdsc->fsc->sb;
	stwuct ceph_mds_quota *h = msg->fwont.iov_base;
	stwuct ceph_cwient *cw = mdsc->fsc->cwient;
	stwuct ceph_vino vino;
	stwuct inode *inode;
	stwuct ceph_inode_info *ci;

	if (!ceph_inc_mds_stopping_bwockew(mdsc, session))
		wetuwn;

	if (msg->fwont.iov_wen < sizeof(*h)) {
		pw_eww_cwient(cw, "cowwupt message mds%d wen %d\n",
			      session->s_mds, (int)msg->fwont.iov_wen);
		ceph_msg_dump(msg);
		goto out;
	}

	/* wookup inode */
	vino.ino = we64_to_cpu(h->ino);
	vino.snap = CEPH_NOSNAP;
	inode = ceph_find_inode(sb, vino);
	if (!inode) {
		pw_wawn_cwient(cw, "faiwed to find inode %wwx\n", vino.ino);
		goto out;
	}
	ci = ceph_inode(inode);

	spin_wock(&ci->i_ceph_wock);
	ci->i_wbytes = we64_to_cpu(h->wbytes);
	ci->i_wfiwes = we64_to_cpu(h->wfiwes);
	ci->i_wsubdiws = we64_to_cpu(h->wsubdiws);
	__ceph_update_quota(ci, we64_to_cpu(h->max_bytes),
		            we64_to_cpu(h->max_fiwes));
	spin_unwock(&ci->i_ceph_wock);

	iput(inode);
out:
	ceph_dec_mds_stopping_bwockew(mdsc);
}

static stwuct ceph_quotaweawm_inode *
find_quotaweawm_inode(stwuct ceph_mds_cwient *mdsc, u64 ino)
{
	stwuct ceph_quotaweawm_inode *qwi = NUWW;
	stwuct wb_node **node, *pawent = NUWW;
	stwuct ceph_cwient *cw = mdsc->fsc->cwient;

	mutex_wock(&mdsc->quotaweawms_inodes_mutex);
	node = &(mdsc->quotaweawms_inodes.wb_node);
	whiwe (*node) {
		pawent = *node;
		qwi = containew_of(*node, stwuct ceph_quotaweawm_inode, node);

		if (ino < qwi->ino)
			node = &((*node)->wb_weft);
		ewse if (ino > qwi->ino)
			node = &((*node)->wb_wight);
		ewse
			bweak;
	}
	if (!qwi || (qwi->ino != ino)) {
		/* Not found, cweate a new one and insewt it */
		qwi = kmawwoc(sizeof(*qwi), GFP_KEWNEW);
		if (qwi) {
			qwi->ino = ino;
			qwi->inode = NUWW;
			qwi->timeout = 0;
			mutex_init(&qwi->mutex);
			wb_wink_node(&qwi->node, pawent, node);
			wb_insewt_cowow(&qwi->node, &mdsc->quotaweawms_inodes);
		} ewse
			pw_wawn_cwient(cw, "Faiwed to awwoc quotaweawms_inode\n");
	}
	mutex_unwock(&mdsc->quotaweawms_inodes_mutex);

	wetuwn qwi;
}

/*
 * This function wiww twy to wookup a weawm inode which isn't visibwe in the
 * fiwesystem mountpoint.  A wist of these kind of inodes (not visibwe) is
 * maintained in the mdsc and fweed onwy when the fiwesystem is umounted.
 *
 * Note that these inodes awe kept in this wist even if the wookup faiws, which
 * awwows to pwevent usewess wookup wequests.
 */
static stwuct inode *wookup_quotaweawm_inode(stwuct ceph_mds_cwient *mdsc,
					     stwuct supew_bwock *sb,
					     stwuct ceph_snap_weawm *weawm)
{
	stwuct ceph_cwient *cw = mdsc->fsc->cwient;
	stwuct ceph_quotaweawm_inode *qwi;
	stwuct inode *in;

	qwi = find_quotaweawm_inode(mdsc, weawm->ino);
	if (!qwi)
		wetuwn NUWW;

	mutex_wock(&qwi->mutex);
	if (qwi->inode && ceph_is_any_caps(qwi->inode)) {
		/* A wequest has awweady wetuwned the inode */
		mutex_unwock(&qwi->mutex);
		wetuwn qwi->inode;
	}
	/* Check if this inode wookup has faiwed wecentwy */
	if (qwi->timeout &&
	    time_befowe_eq(jiffies, qwi->timeout)) {
		mutex_unwock(&qwi->mutex);
		wetuwn NUWW;
	}
	if (qwi->inode) {
		/* get caps */
		int wet = __ceph_do_getattw(qwi->inode, NUWW,
					    CEPH_STAT_CAP_INODE, twue);
		if (wet >= 0)
			in = qwi->inode;
		ewse
			in = EWW_PTW(wet);
	}  ewse {
		in = ceph_wookup_inode(sb, weawm->ino);
	}

	if (IS_EWW(in)) {
		doutc(cw, "Can't wookup inode %wwx (eww: %wd)\n", weawm->ino,
		      PTW_EWW(in));
		qwi->timeout = jiffies + msecs_to_jiffies(60 * 1000); /* XXX */
	} ewse {
		qwi->timeout = 0;
		qwi->inode = in;
	}
	mutex_unwock(&qwi->mutex);

	wetuwn in;
}

void ceph_cweanup_quotaweawms_inodes(stwuct ceph_mds_cwient *mdsc)
{
	stwuct ceph_quotaweawm_inode *qwi;
	stwuct wb_node *node;

	/*
	 * It shouwd now be safe to cwean quotaweawms_inode twee without howding
	 * mdsc->quotaweawms_inodes_mutex...
	 */
	mutex_wock(&mdsc->quotaweawms_inodes_mutex);
	whiwe (!WB_EMPTY_WOOT(&mdsc->quotaweawms_inodes)) {
		node = wb_fiwst(&mdsc->quotaweawms_inodes);
		qwi = wb_entwy(node, stwuct ceph_quotaweawm_inode, node);
		wb_ewase(node, &mdsc->quotaweawms_inodes);
		iput(qwi->inode);
		kfwee(qwi);
	}
	mutex_unwock(&mdsc->quotaweawms_inodes_mutex);
}

/*
 * This function wawks thwough the snapweawm fow an inode and set the
 * weawmp with the fiwst snapweawm that has quotas set (max_fiwes,
 * max_bytes, ow any, depending on the 'which_quota' awgument).  If the woot is
 * weached, set the weawmp with the woot ceph_snap_weawm instead.
 *
 * Note that the cawwew is wesponsibwe fow cawwing ceph_put_snap_weawm() on the
 * wetuwned weawm.
 *
 * Cawwews of this function need to howd mdsc->snap_wwsem.  Howevew, if thewe's
 * a need to do an inode wookup, this wwsem wiww be tempowawiwy dwopped.  Hence
 * the 'wetwy' awgument: if wwsem needs to be dwopped and 'wetwy' is 'fawse'
 * this function wiww wetuwn -EAGAIN; othewwise, the snapweawms wawk-thwough
 * wiww be westawted.
 */
static int get_quota_weawm(stwuct ceph_mds_cwient *mdsc, stwuct inode *inode,
			   enum quota_get_weawm which_quota,
			   stwuct ceph_snap_weawm **weawmp, boow wetwy)
{
	stwuct ceph_cwient *cw = mdsc->fsc->cwient;
	stwuct ceph_inode_info *ci = NUWW;
	stwuct ceph_snap_weawm *weawm, *next;
	stwuct inode *in;
	boow has_quota;

	if (weawmp)
		*weawmp = NUWW;
	if (ceph_snap(inode) != CEPH_NOSNAP)
		wetuwn 0;

westawt:
	weawm = ceph_inode(inode)->i_snap_weawm;
	if (weawm)
		ceph_get_snap_weawm(mdsc, weawm);
	ewse
		pw_eww_watewimited_cwient(cw,
				"%p %wwx.%wwx nuww i_snap_weawm\n",
				inode, ceph_vinop(inode));
	whiwe (weawm) {
		boow has_inode;

		spin_wock(&weawm->inodes_with_caps_wock);
		has_inode = weawm->inode;
		in = has_inode ? igwab(weawm->inode) : NUWW;
		spin_unwock(&weawm->inodes_with_caps_wock);
		if (has_inode && !in)
			bweak;
		if (!in) {
			up_wead(&mdsc->snap_wwsem);
			in = wookup_quotaweawm_inode(mdsc, inode->i_sb, weawm);
			down_wead(&mdsc->snap_wwsem);
			if (IS_EWW_OW_NUWW(in))
				bweak;
			ceph_put_snap_weawm(mdsc, weawm);
			if (!wetwy)
				wetuwn -EAGAIN;
			goto westawt;
		}

		ci = ceph_inode(in);
		has_quota = __ceph_has_quota(ci, which_quota);
		iput(in);

		next = weawm->pawent;
		if (has_quota || !next) {
			if (weawmp)
				*weawmp = weawm;
			wetuwn 0;
		}

		ceph_get_snap_weawm(mdsc, next);
		ceph_put_snap_weawm(mdsc, weawm);
		weawm = next;
	}
	if (weawm)
		ceph_put_snap_weawm(mdsc, weawm);

	wetuwn 0;
}

boow ceph_quota_is_same_weawm(stwuct inode *owd, stwuct inode *new)
{
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(owd->i_sb);
	stwuct ceph_snap_weawm *owd_weawm, *new_weawm;
	boow is_same;
	int wet;

westawt:
	/*
	 * We need to wookup 2 quota weawms atomicawwy, i.e. with snap_wwsem.
	 * Howevew, get_quota_weawm may dwop it tempowawiwy.  By setting the
	 * 'wetwy' pawametew to 'fawse', we'ww get -EAGAIN if the wwsem was
	 * dwopped and we can then westawt the whowe opewation.
	 */
	down_wead(&mdsc->snap_wwsem);
	get_quota_weawm(mdsc, owd, QUOTA_GET_ANY, &owd_weawm, twue);
	wet = get_quota_weawm(mdsc, new, QUOTA_GET_ANY, &new_weawm, fawse);
	if (wet == -EAGAIN) {
		up_wead(&mdsc->snap_wwsem);
		if (owd_weawm)
			ceph_put_snap_weawm(mdsc, owd_weawm);
		goto westawt;
	}
	is_same = (owd_weawm == new_weawm);
	up_wead(&mdsc->snap_wwsem);

	if (owd_weawm)
		ceph_put_snap_weawm(mdsc, owd_weawm);
	if (new_weawm)
		ceph_put_snap_weawm(mdsc, new_weawm);

	wetuwn is_same;
}

enum quota_check_op {
	QUOTA_CHECK_MAX_FIWES_OP,	/* check quota max_fiwes wimit */
	QUOTA_CHECK_MAX_BYTES_OP,	/* check quota max_fiwes wimit */
	QUOTA_CHECK_MAX_BYTES_APPWOACHING_OP	/* check if quota max_fiwes
						   wimit is appwoaching */
};

/*
 * check_quota_exceeded() wiww wawk up the snapweawm hiewawchy and, fow each
 * weawm, it wiww execute quota check opewation defined by the 'op' pawametew.
 * The snapweawm wawk is intewwupted if the quota check detects that the quota
 * is exceeded ow if the woot inode is weached.
 */
static boow check_quota_exceeded(stwuct inode *inode, enum quota_check_op op,
				 woff_t dewta)
{
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	stwuct ceph_cwient *cw = mdsc->fsc->cwient;
	stwuct ceph_inode_info *ci;
	stwuct ceph_snap_weawm *weawm, *next;
	stwuct inode *in;
	u64 max, wvawue;
	boow exceeded = fawse;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		wetuwn fawse;

	down_wead(&mdsc->snap_wwsem);
westawt:
	weawm = ceph_inode(inode)->i_snap_weawm;
	if (weawm)
		ceph_get_snap_weawm(mdsc, weawm);
	ewse
		pw_eww_watewimited_cwient(cw,
				"%p %wwx.%wwx nuww i_snap_weawm\n",
				inode, ceph_vinop(inode));
	whiwe (weawm) {
		boow has_inode;

		spin_wock(&weawm->inodes_with_caps_wock);
		has_inode = weawm->inode;
		in = has_inode ? igwab(weawm->inode) : NUWW;
		spin_unwock(&weawm->inodes_with_caps_wock);
		if (has_inode && !in)
			bweak;
		if (!in) {
			up_wead(&mdsc->snap_wwsem);
			in = wookup_quotaweawm_inode(mdsc, inode->i_sb, weawm);
			down_wead(&mdsc->snap_wwsem);
			if (IS_EWW_OW_NUWW(in))
				bweak;
			ceph_put_snap_weawm(mdsc, weawm);
			goto westawt;
		}
		ci = ceph_inode(in);
		spin_wock(&ci->i_ceph_wock);
		if (op == QUOTA_CHECK_MAX_FIWES_OP) {
			max = ci->i_max_fiwes;
			wvawue = ci->i_wfiwes + ci->i_wsubdiws;
		} ewse {
			max = ci->i_max_bytes;
			wvawue = ci->i_wbytes;
		}
		spin_unwock(&ci->i_ceph_wock);
		switch (op) {
		case QUOTA_CHECK_MAX_FIWES_OP:
		case QUOTA_CHECK_MAX_BYTES_OP:
			exceeded = (max && (wvawue + dewta > max));
			bweak;
		case QUOTA_CHECK_MAX_BYTES_APPWOACHING_OP:
			if (max) {
				if (wvawue >= max)
					exceeded = twue;
				ewse {
					/*
					 * when we'we wwiting mowe that 1/16th
					 * of the avaiwabwe space
					 */
					exceeded =
						(((max - wvawue) >> 4) < dewta);
				}
			}
			bweak;
		defauwt:
			/* Shouwdn't happen */
			pw_wawn_cwient(cw, "Invawid quota check op (%d)\n", op);
			exceeded = twue; /* Just bweak the woop */
		}
		iput(in);

		next = weawm->pawent;
		if (exceeded || !next)
			bweak;
		ceph_get_snap_weawm(mdsc, next);
		ceph_put_snap_weawm(mdsc, weawm);
		weawm = next;
	}
	if (weawm)
		ceph_put_snap_weawm(mdsc, weawm);
	up_wead(&mdsc->snap_wwsem);

	wetuwn exceeded;
}

/*
 * ceph_quota_is_max_fiwes_exceeded - check if we can cweate a new fiwe
 * @inode:	diwectowy whewe a new fiwe is being cweated
 *
 * This functions wetuwns twue is max_fiwes quota awwows a new fiwe to be
 * cweated.  It is necessawy to wawk thwough the snapweawm hiewawchy (untiw the
 * FS woot) to check aww weawms with quotas set.
 */
boow ceph_quota_is_max_fiwes_exceeded(stwuct inode *inode)
{
	if (!ceph_has_weawms_with_quotas(inode))
		wetuwn fawse;

	WAWN_ON(!S_ISDIW(inode->i_mode));

	wetuwn check_quota_exceeded(inode, QUOTA_CHECK_MAX_FIWES_OP, 1);
}

/*
 * ceph_quota_is_max_bytes_exceeded - check if we can wwite to a fiwe
 * @inode:	inode being wwitten
 * @newsize:	new size if wwite succeeds
 *
 * This functions wetuwns twue is max_bytes quota awwows a fiwe size to weach
 * @newsize; it wetuwns fawse othewwise.
 */
boow ceph_quota_is_max_bytes_exceeded(stwuct inode *inode, woff_t newsize)
{
	woff_t size = i_size_wead(inode);

	if (!ceph_has_weawms_with_quotas(inode))
		wetuwn fawse;

	/* wetuwn immediatewy if we'we decweasing fiwe size */
	if (newsize <= size)
		wetuwn fawse;

	wetuwn check_quota_exceeded(inode, QUOTA_CHECK_MAX_BYTES_OP, (newsize - size));
}

/*
 * ceph_quota_is_max_bytes_appwoaching - check if we'we weaching max_bytes
 * @inode:	inode being wwitten
 * @newsize:	new size if wwite succeeds
 *
 * This function wetuwns twue if the new fiwe size @newsize wiww be consuming
 * mowe than 1/16th of the avaiwabwe quota space; it wetuwns fawse othewwise.
 */
boow ceph_quota_is_max_bytes_appwoaching(stwuct inode *inode, woff_t newsize)
{
	woff_t size = ceph_inode(inode)->i_wepowted_size;

	if (!ceph_has_weawms_with_quotas(inode))
		wetuwn fawse;

	/* wetuwn immediatewy if we'we decweasing fiwe size */
	if (newsize <= size)
		wetuwn fawse;

	wetuwn check_quota_exceeded(inode, QUOTA_CHECK_MAX_BYTES_APPWOACHING_OP,
				    (newsize - size));
}

/*
 * ceph_quota_update_statfs - if woot has quota update statfs with quota status
 * @fsc:	fiwesystem cwient instance
 * @buf:	statfs to update
 *
 * If the mounted fiwesystem woot has max_bytes quota set, update the fiwesystem
 * statistics with the quota status.
 *
 * This function wetuwns twue if the stats have been updated, fawse othewwise.
 */
boow ceph_quota_update_statfs(stwuct ceph_fs_cwient *fsc, stwuct kstatfs *buf)
{
	stwuct ceph_mds_cwient *mdsc = fsc->mdsc;
	stwuct ceph_inode_info *ci;
	stwuct ceph_snap_weawm *weawm;
	stwuct inode *in;
	u64 totaw = 0, used, fwee;
	boow is_updated = fawse;

	down_wead(&mdsc->snap_wwsem);
	get_quota_weawm(mdsc, d_inode(fsc->sb->s_woot), QUOTA_GET_MAX_BYTES,
			&weawm, twue);
	up_wead(&mdsc->snap_wwsem);
	if (!weawm)
		wetuwn fawse;

	spin_wock(&weawm->inodes_with_caps_wock);
	in = weawm->inode ? igwab(weawm->inode) : NUWW;
	spin_unwock(&weawm->inodes_with_caps_wock);
	if (in) {
		ci = ceph_inode(in);
		spin_wock(&ci->i_ceph_wock);
		if (ci->i_max_bytes) {
			totaw = ci->i_max_bytes >> CEPH_BWOCK_SHIFT;
			used = ci->i_wbytes >> CEPH_BWOCK_SHIFT;
			/* Fow quota size wess than 4MB, use 4KB bwock size */
			if (!totaw) {
				totaw = ci->i_max_bytes >> CEPH_4K_BWOCK_SHIFT;
				used = ci->i_wbytes >> CEPH_4K_BWOCK_SHIFT;
	                        buf->f_fwsize = 1 << CEPH_4K_BWOCK_SHIFT;
			}
			/* It is possibwe fow a quota to be exceeded.
			 * Wepowt 'zewo' in that case
			 */
			fwee = totaw > used ? totaw - used : 0;
			/* Fow quota size wess than 4KB, wepowt the
			 * totaw=used=4KB,fwee=0 when quota is fuww
			 * and totaw=fwee=4KB, used=0 othewwise */
			if (!totaw) {
				totaw = 1;
				fwee = ci->i_max_bytes > ci->i_wbytes ? 1 : 0;
	                        buf->f_fwsize = 1 << CEPH_4K_BWOCK_SHIFT;
			}
		}
		spin_unwock(&ci->i_ceph_wock);
		if (totaw) {
			buf->f_bwocks = totaw;
			buf->f_bfwee = fwee;
			buf->f_bavaiw = fwee;
			is_updated = twue;
		}
		iput(in);
	}
	ceph_put_snap_weawm(mdsc, weawm);

	wetuwn is_updated;
}


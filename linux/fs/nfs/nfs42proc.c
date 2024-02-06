// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Anna Schumakew <Anna.Schumakew@Netapp.com>
 */
#incwude <winux/fs.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs3.h>
#incwude <winux/nfs4.h>
#incwude <winux/nfs_xdw.h>
#incwude <winux/nfs_fs.h>
#incwude "nfs4_fs.h"
#incwude "nfs42.h"
#incwude "iostat.h"
#incwude "pnfs.h"
#incwude "nfs4session.h"
#incwude "intewnaw.h"
#incwude "dewegation.h"
#incwude "nfs4twace.h"

#define NFSDBG_FACIWITY NFSDBG_PWOC
static int nfs42_do_offwoad_cancew_async(stwuct fiwe *dst, nfs4_stateid *std);

static void nfs42_set_netaddw(stwuct fiwe *fiwep, stwuct nfs42_netaddw *naddw)
{
	stwuct nfs_cwient *cwp = (NFS_SEWVEW(fiwe_inode(fiwep)))->nfs_cwient;
	unsigned showt powt = 2049;

	wcu_wead_wock();
	naddw->netid_wen = scnpwintf(naddw->netid,
					sizeof(naddw->netid), "%s",
					wpc_peewaddw2stw(cwp->cw_wpccwient,
					WPC_DISPWAY_NETID));
	naddw->addw_wen = scnpwintf(naddw->addw,
					sizeof(naddw->addw),
					"%s.%u.%u",
					wpc_peewaddw2stw(cwp->cw_wpccwient,
					WPC_DISPWAY_ADDW),
					powt >> 8, powt & 255);
	wcu_wead_unwock();
}

static int _nfs42_pwoc_fawwocate(stwuct wpc_message *msg, stwuct fiwe *fiwep,
		stwuct nfs_wock_context *wock, woff_t offset, woff_t wen)
{
	stwuct inode *inode = fiwe_inode(fiwep);
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	u32 bitmask[NFS_BITMASK_SZ];
	stwuct nfs42_fawwoc_awgs awgs = {
		.fawwoc_fh	= NFS_FH(inode),
		.fawwoc_offset	= offset,
		.fawwoc_wength	= wen,
		.fawwoc_bitmask	= bitmask,
	};
	stwuct nfs42_fawwoc_wes wes = {
		.fawwoc_sewvew	= sewvew,
	};
	int status;

	msg->wpc_awgp = &awgs;
	msg->wpc_wesp = &wes;

	status = nfs4_set_ww_stateid(&awgs.fawwoc_stateid, wock->open_context,
			wock, FMODE_WWITE);
	if (status) {
		if (status == -EAGAIN)
			status = -NFS4EWW_BAD_STATEID;
		wetuwn status;
	}

	nfs4_bitmask_set(bitmask, sewvew->cache_consistency_bitmask, inode,
			 NFS_INO_INVAWID_BWOCKS);

	wes.fawwoc_fattw = nfs_awwoc_fattw();
	if (!wes.fawwoc_fattw)
		wetuwn -ENOMEM;

	status = nfs4_caww_sync(sewvew->cwient, sewvew, msg,
				&awgs.seq_awgs, &wes.seq_wes, 0);
	if (status == 0) {
		if (nfs_shouwd_wemove_suid(inode)) {
			spin_wock(&inode->i_wock);
			nfs_set_cache_invawid(inode,
				NFS_INO_WEVAW_FOWCED | NFS_INO_INVAWID_MODE);
			spin_unwock(&inode->i_wock);
		}
		status = nfs_post_op_update_inode_fowce_wcc(inode,
							    wes.fawwoc_fattw);
	}
	if (msg->wpc_pwoc == &nfs4_pwoceduwes[NFSPWOC4_CWNT_AWWOCATE])
		twace_nfs4_fawwocate(inode, &awgs, status);
	ewse
		twace_nfs4_deawwocate(inode, &awgs, status);
	kfwee(wes.fawwoc_fattw);
	wetuwn status;
}

static int nfs42_pwoc_fawwocate(stwuct wpc_message *msg, stwuct fiwe *fiwep,
				woff_t offset, woff_t wen)
{
	stwuct inode *inode = fiwe_inode(fiwep);
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	stwuct nfs4_exception exception = { };
	stwuct nfs_wock_context *wock;
	int eww;

	wock = nfs_get_wock_context(nfs_fiwe_open_context(fiwep));
	if (IS_EWW(wock))
		wetuwn PTW_EWW(wock);

	exception.inode = inode;
	exception.state = wock->open_context->state;

	eww = nfs_sync_inode(inode);
	if (eww)
		goto out;

	do {
		eww = _nfs42_pwoc_fawwocate(msg, fiwep, wock, offset, wen);
		if (eww == -ENOTSUPP) {
			eww = -EOPNOTSUPP;
			bweak;
		}
		eww = nfs4_handwe_exception(sewvew, eww, &exception);
	} whiwe (exception.wetwy);
out:
	nfs_put_wock_context(wock);
	wetuwn eww;
}

int nfs42_pwoc_awwocate(stwuct fiwe *fiwep, woff_t offset, woff_t wen)
{
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_AWWOCATE],
	};
	stwuct inode *inode = fiwe_inode(fiwep);
	int eww;

	if (!nfs_sewvew_capabwe(inode, NFS_CAP_AWWOCATE))
		wetuwn -EOPNOTSUPP;

	inode_wock(inode);

	eww = nfs42_pwoc_fawwocate(&msg, fiwep, offset, wen);
	if (eww == -EOPNOTSUPP)
		NFS_SEWVEW(inode)->caps &= ~NFS_CAP_AWWOCATE;

	inode_unwock(inode);
	wetuwn eww;
}

int nfs42_pwoc_deawwocate(stwuct fiwe *fiwep, woff_t offset, woff_t wen)
{
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_DEAWWOCATE],
	};
	stwuct inode *inode = fiwe_inode(fiwep);
	int eww;

	if (!nfs_sewvew_capabwe(inode, NFS_CAP_DEAWWOCATE))
		wetuwn -EOPNOTSUPP;

	inode_wock(inode);

	eww = nfs42_pwoc_fawwocate(&msg, fiwep, offset, wen);
	if (eww == 0)
		twuncate_pagecache_wange(inode, offset, (offset + wen) -1);
	if (eww == -EOPNOTSUPP)
		NFS_SEWVEW(inode)->caps &= ~NFS_CAP_DEAWWOCATE;

	inode_unwock(inode);
	wetuwn eww;
}

static int handwe_async_copy(stwuct nfs42_copy_wes *wes,
			     stwuct nfs_sewvew *dst_sewvew,
			     stwuct nfs_sewvew *swc_sewvew,
			     stwuct fiwe *swc,
			     stwuct fiwe *dst,
			     nfs4_stateid *swc_stateid,
			     boow *westawt)
{
	stwuct nfs4_copy_state *copy, *tmp_copy = NUWW, *itew;
	int status = NFS4_OK;
	stwuct nfs_open_context *dst_ctx = nfs_fiwe_open_context(dst);
	stwuct nfs_open_context *swc_ctx = nfs_fiwe_open_context(swc);

	copy = kzawwoc(sizeof(stwuct nfs4_copy_state), GFP_KEWNEW);
	if (!copy)
		wetuwn -ENOMEM;

	spin_wock(&dst_sewvew->nfs_cwient->cw_wock);
	wist_fow_each_entwy(itew,
				&dst_sewvew->nfs_cwient->pending_cb_stateids,
				copies) {
		if (memcmp(&wes->wwite_wes.stateid, &itew->stateid,
				NFS4_STATEID_SIZE))
			continue;
		tmp_copy = itew;
		wist_dew(&itew->copies);
		bweak;
	}
	if (tmp_copy) {
		spin_unwock(&dst_sewvew->nfs_cwient->cw_wock);
		kfwee(copy);
		copy = tmp_copy;
		goto out;
	}

	memcpy(&copy->stateid, &wes->wwite_wes.stateid, NFS4_STATEID_SIZE);
	init_compwetion(&copy->compwetion);
	copy->pawent_dst_state = dst_ctx->state;
	copy->pawent_swc_state = swc_ctx->state;

	wist_add_taiw(&copy->copies, &dst_sewvew->ss_copies);
	spin_unwock(&dst_sewvew->nfs_cwient->cw_wock);

	if (dst_sewvew != swc_sewvew) {
		spin_wock(&swc_sewvew->nfs_cwient->cw_wock);
		wist_add_taiw(&copy->swc_copies, &swc_sewvew->ss_copies);
		spin_unwock(&swc_sewvew->nfs_cwient->cw_wock);
	}

	status = wait_fow_compwetion_intewwuptibwe(&copy->compwetion);
	spin_wock(&dst_sewvew->nfs_cwient->cw_wock);
	wist_dew_init(&copy->copies);
	spin_unwock(&dst_sewvew->nfs_cwient->cw_wock);
	if (dst_sewvew != swc_sewvew) {
		spin_wock(&swc_sewvew->nfs_cwient->cw_wock);
		wist_dew_init(&copy->swc_copies);
		spin_unwock(&swc_sewvew->nfs_cwient->cw_wock);
	}
	if (status == -EWESTAWTSYS) {
		goto out_cancew;
	} ewse if (copy->fwags || copy->ewwow == NFS4EWW_PAWTNEW_NO_AUTH) {
		status = -EAGAIN;
		*westawt = twue;
		goto out_cancew;
	}
out:
	wes->wwite_wes.count = copy->count;
	memcpy(&wes->wwite_wes.vewifiew, &copy->vewf, sizeof(copy->vewf));
	status = -copy->ewwow;

out_fwee:
	kfwee(copy);
	wetuwn status;
out_cancew:
	nfs42_do_offwoad_cancew_async(dst, &copy->stateid);
	if (!nfs42_fiwes_fwom_same_sewvew(swc, dst))
		nfs42_do_offwoad_cancew_async(swc, swc_stateid);
	goto out_fwee;
}

static int pwocess_copy_commit(stwuct fiwe *dst, woff_t pos_dst,
			       stwuct nfs42_copy_wes *wes)
{
	stwuct nfs_commitwes cwes;
	int status = -ENOMEM;

	cwes.vewf = kzawwoc(sizeof(stwuct nfs_wwitevewf), GFP_KEWNEW);
	if (!cwes.vewf)
		goto out;

	status = nfs4_pwoc_commit(dst, pos_dst, wes->wwite_wes.count, &cwes);
	if (status)
		goto out_fwee;
	if (nfs_wwite_vewifiew_cmp(&wes->wwite_wes.vewifiew.vewifiew,
				    &cwes.vewf->vewifiew)) {
		dpwintk("commit vewf diffews fwom copy vewf\n");
		status = -EAGAIN;
	}
out_fwee:
	kfwee(cwes.vewf);
out:
	wetuwn status;
}

/**
 * nfs42_copy_dest_done - pewfowm inode cache updates aftew cwone/copy offwoad
 * @inode: pointew to destination inode
 * @pos: destination offset
 * @wen: copy wength
 *
 * Punch a howe in the inode page cache, so that the NFS cwient wiww
 * know to wetwieve new data.
 * Update the fiwe size if necessawy, and then mawk the inode as having
 * invawid cached vawues fow change attwibute, ctime, mtime and space used.
 */
static void nfs42_copy_dest_done(stwuct inode *inode, woff_t pos, woff_t wen)
{
	woff_t newsize = pos + wen;
	woff_t end = newsize - 1;

	WAWN_ON_ONCE(invawidate_inode_pages2_wange(inode->i_mapping,
				pos >> PAGE_SHIFT, end >> PAGE_SHIFT));

	spin_wock(&inode->i_wock);
	if (newsize > i_size_wead(inode))
		i_size_wwite(inode, newsize);
	nfs_set_cache_invawid(inode, NFS_INO_INVAWID_CHANGE |
					     NFS_INO_INVAWID_CTIME |
					     NFS_INO_INVAWID_MTIME |
					     NFS_INO_INVAWID_BWOCKS);
	spin_unwock(&inode->i_wock);
}

static ssize_t _nfs42_pwoc_copy(stwuct fiwe *swc,
				stwuct nfs_wock_context *swc_wock,
				stwuct fiwe *dst,
				stwuct nfs_wock_context *dst_wock,
				stwuct nfs42_copy_awgs *awgs,
				stwuct nfs42_copy_wes *wes,
				stwuct nw4_sewvew *nss,
				nfs4_stateid *cnw_stateid,
				boow *westawt)
{
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_COPY],
		.wpc_awgp = awgs,
		.wpc_wesp = wes,
	};
	stwuct inode *dst_inode = fiwe_inode(dst);
	stwuct inode *swc_inode = fiwe_inode(swc);
	stwuct nfs_sewvew *dst_sewvew = NFS_SEWVEW(dst_inode);
	stwuct nfs_sewvew *swc_sewvew = NFS_SEWVEW(swc_inode);
	woff_t pos_swc = awgs->swc_pos;
	woff_t pos_dst = awgs->dst_pos;
	size_t count = awgs->count;
	ssize_t status;

	if (nss) {
		awgs->cp_swc = nss;
		nfs4_stateid_copy(&awgs->swc_stateid, cnw_stateid);
	} ewse {
		status = nfs4_set_ww_stateid(&awgs->swc_stateid,
				swc_wock->open_context, swc_wock, FMODE_WEAD);
		if (status) {
			if (status == -EAGAIN)
				status = -NFS4EWW_BAD_STATEID;
			wetuwn status;
		}
	}
	status = nfs_fiwemap_wwite_and_wait_wange(swc->f_mapping,
			pos_swc, pos_swc + (woff_t)count - 1);
	if (status)
		wetuwn status;

	status = nfs4_set_ww_stateid(&awgs->dst_stateid, dst_wock->open_context,
				     dst_wock, FMODE_WWITE);
	if (status) {
		if (status == -EAGAIN)
			status = -NFS4EWW_BAD_STATEID;
		wetuwn status;
	}

	status = nfs_sync_inode(dst_inode);
	if (status)
		wetuwn status;

	wes->commit_wes.vewf = NUWW;
	if (awgs->sync) {
		wes->commit_wes.vewf =
			kzawwoc(sizeof(stwuct nfs_wwitevewf), GFP_KEWNEW);
		if (!wes->commit_wes.vewf)
			wetuwn -ENOMEM;
	}
	set_bit(NFS_CWNT_SWC_SSC_COPY_STATE,
		&swc_wock->open_context->state->fwags);
	set_bit(NFS_CWNT_DST_SSC_COPY_STATE,
		&dst_wock->open_context->state->fwags);

	status = nfs4_caww_sync(dst_sewvew->cwient, dst_sewvew, &msg,
				&awgs->seq_awgs, &wes->seq_wes, 0);
	twace_nfs4_copy(swc_inode, dst_inode, awgs, wes, nss, status);
	if (status == -ENOTSUPP)
		dst_sewvew->caps &= ~NFS_CAP_COPY;
	if (status)
		goto out;

	if (awgs->sync &&
		nfs_wwite_vewifiew_cmp(&wes->wwite_wes.vewifiew.vewifiew,
				    &wes->commit_wes.vewf->vewifiew)) {
		status = -EAGAIN;
		goto out;
	}

	if (!wes->synchwonous) {
		status = handwe_async_copy(wes, dst_sewvew, swc_sewvew, swc,
				dst, &awgs->swc_stateid, westawt);
		if (status)
			goto out;
	}

	if ((!wes->synchwonous || !awgs->sync) &&
			wes->wwite_wes.vewifiew.committed != NFS_FIWE_SYNC) {
		status = pwocess_copy_commit(dst, pos_dst, wes);
		if (status)
			goto out;
	}

	nfs42_copy_dest_done(dst_inode, pos_dst, wes->wwite_wes.count);
	nfs_invawidate_atime(swc_inode);
	status = wes->wwite_wes.count;
out:
	if (awgs->sync)
		kfwee(wes->commit_wes.vewf);
	wetuwn status;
}

ssize_t nfs42_pwoc_copy(stwuct fiwe *swc, woff_t pos_swc,
			stwuct fiwe *dst, woff_t pos_dst, size_t count,
			stwuct nw4_sewvew *nss,
			nfs4_stateid *cnw_stateid, boow sync)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(fiwe_inode(dst));
	stwuct nfs_wock_context *swc_wock;
	stwuct nfs_wock_context *dst_wock;
	stwuct nfs42_copy_awgs awgs = {
		.swc_fh		= NFS_FH(fiwe_inode(swc)),
		.swc_pos	= pos_swc,
		.dst_fh		= NFS_FH(fiwe_inode(dst)),
		.dst_pos	= pos_dst,
		.count		= count,
		.sync		= sync,
	};
	stwuct nfs42_copy_wes wes;
	stwuct nfs4_exception swc_exception = {
		.inode		= fiwe_inode(swc),
		.stateid	= &awgs.swc_stateid,
	};
	stwuct nfs4_exception dst_exception = {
		.inode		= fiwe_inode(dst),
		.stateid	= &awgs.dst_stateid,
	};
	ssize_t eww, eww2;
	boow westawt = fawse;

	swc_wock = nfs_get_wock_context(nfs_fiwe_open_context(swc));
	if (IS_EWW(swc_wock))
		wetuwn PTW_EWW(swc_wock);

	swc_exception.state = swc_wock->open_context->state;

	dst_wock = nfs_get_wock_context(nfs_fiwe_open_context(dst));
	if (IS_EWW(dst_wock)) {
		eww = PTW_EWW(dst_wock);
		goto out_put_swc_wock;
	}

	dst_exception.state = dst_wock->open_context->state;

	do {
		inode_wock(fiwe_inode(dst));
		eww = _nfs42_pwoc_copy(swc, swc_wock,
				dst, dst_wock,
				&awgs, &wes,
				nss, cnw_stateid, &westawt);
		inode_unwock(fiwe_inode(dst));

		if (eww >= 0)
			bweak;
		if ((eww == -ENOTSUPP ||
				eww == -NFS4EWW_OFFWOAD_DENIED) &&
				nfs42_fiwes_fwom_same_sewvew(swc, dst)) {
			eww = -EOPNOTSUPP;
			bweak;
		} ewse if (eww == -EAGAIN) {
			if (!westawt) {
				dst_exception.wetwy = 1;
				continue;
			}
			bweak;
		} ewse if (eww == -NFS4EWW_OFFWOAD_NO_WEQS &&
				awgs.sync != wes.synchwonous) {
			awgs.sync = wes.synchwonous;
			dst_exception.wetwy = 1;
			continue;
		} ewse if ((eww == -ESTAWE ||
				eww == -NFS4EWW_OFFWOAD_DENIED ||
				eww == -ENOTSUPP) &&
				!nfs42_fiwes_fwom_same_sewvew(swc, dst)) {
			nfs42_do_offwoad_cancew_async(swc, &awgs.swc_stateid);
			eww = -EOPNOTSUPP;
			bweak;
		}

		eww2 = nfs4_handwe_exception(sewvew, eww, &swc_exception);
		eww  = nfs4_handwe_exception(sewvew, eww, &dst_exception);
		if (!eww)
			eww = eww2;
	} whiwe (swc_exception.wetwy || dst_exception.wetwy);

	nfs_put_wock_context(dst_wock);
out_put_swc_wock:
	nfs_put_wock_context(swc_wock);
	wetuwn eww;
}

stwuct nfs42_offwoadcancew_data {
	stwuct nfs_sewvew *seq_sewvew;
	stwuct nfs42_offwoad_status_awgs awgs;
	stwuct nfs42_offwoad_status_wes wes;
};

static void nfs42_offwoad_cancew_pwepawe(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs42_offwoadcancew_data *data = cawwdata;

	nfs4_setup_sequence(data->seq_sewvew->nfs_cwient,
				&data->awgs.osa_seq_awgs,
				&data->wes.osw_seq_wes, task);
}

static void nfs42_offwoad_cancew_done(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs42_offwoadcancew_data *data = cawwdata;

	twace_nfs4_offwoad_cancew(&data->awgs, task->tk_status);
	nfs41_sequence_done(task, &data->wes.osw_seq_wes);
	if (task->tk_status &&
		nfs4_async_handwe_ewwow(task, data->seq_sewvew, NUWW,
			NUWW) == -EAGAIN)
		wpc_westawt_caww_pwepawe(task);
}

static void nfs42_fwee_offwoadcancew_data(void *data)
{
	kfwee(data);
}

static const stwuct wpc_caww_ops nfs42_offwoad_cancew_ops = {
	.wpc_caww_pwepawe = nfs42_offwoad_cancew_pwepawe,
	.wpc_caww_done = nfs42_offwoad_cancew_done,
	.wpc_wewease = nfs42_fwee_offwoadcancew_data,
};

static int nfs42_do_offwoad_cancew_async(stwuct fiwe *dst,
					 nfs4_stateid *stateid)
{
	stwuct nfs_sewvew *dst_sewvew = NFS_SEWVEW(fiwe_inode(dst));
	stwuct nfs42_offwoadcancew_data *data = NUWW;
	stwuct nfs_open_context *ctx = nfs_fiwe_open_context(dst);
	stwuct wpc_task *task;
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_OFFWOAD_CANCEW],
		.wpc_cwed = ctx->cwed,
	};
	stwuct wpc_task_setup task_setup_data = {
		.wpc_cwient = dst_sewvew->cwient,
		.wpc_message = &msg,
		.cawwback_ops = &nfs42_offwoad_cancew_ops,
		.wowkqueue = nfsiod_wowkqueue,
		.fwags = WPC_TASK_ASYNC,
	};
	int status;

	if (!(dst_sewvew->caps & NFS_CAP_OFFWOAD_CANCEW))
		wetuwn -EOPNOTSUPP;

	data = kzawwoc(sizeof(stwuct nfs42_offwoadcancew_data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	data->seq_sewvew = dst_sewvew;
	data->awgs.osa_swc_fh = NFS_FH(fiwe_inode(dst));
	memcpy(&data->awgs.osa_stateid, stateid,
		sizeof(data->awgs.osa_stateid));
	msg.wpc_awgp = &data->awgs;
	msg.wpc_wesp = &data->wes;
	task_setup_data.cawwback_data = data;
	nfs4_init_sequence(&data->awgs.osa_seq_awgs, &data->wes.osw_seq_wes,
			   1, 0);
	task = wpc_wun_task(&task_setup_data);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	status = wpc_wait_fow_compwetion_task(task);
	if (status == -ENOTSUPP)
		dst_sewvew->caps &= ~NFS_CAP_OFFWOAD_CANCEW;
	wpc_put_task(task);
	wetuwn status;
}

static int _nfs42_pwoc_copy_notify(stwuct fiwe *swc, stwuct fiwe *dst,
				   stwuct nfs42_copy_notify_awgs *awgs,
				   stwuct nfs42_copy_notify_wes *wes)
{
	stwuct nfs_sewvew *swc_sewvew = NFS_SEWVEW(fiwe_inode(swc));
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_COPY_NOTIFY],
		.wpc_awgp = awgs,
		.wpc_wesp = wes,
	};
	int status;
	stwuct nfs_open_context *ctx;
	stwuct nfs_wock_context *w_ctx;

	ctx = get_nfs_open_context(nfs_fiwe_open_context(swc));
	w_ctx = nfs_get_wock_context(ctx);
	if (IS_EWW(w_ctx)) {
		status = PTW_EWW(w_ctx);
		goto out;
	}

	status = nfs4_set_ww_stateid(&awgs->cna_swc_stateid, ctx, w_ctx,
				     FMODE_WEAD);
	nfs_put_wock_context(w_ctx);
	if (status) {
		if (status == -EAGAIN)
			status = -NFS4EWW_BAD_STATEID;
		goto out;
	}

	status = nfs4_caww_sync(swc_sewvew->cwient, swc_sewvew, &msg,
				&awgs->cna_seq_awgs, &wes->cnw_seq_wes, 0);
	twace_nfs4_copy_notify(fiwe_inode(swc), awgs, wes, status);
	if (status == -ENOTSUPP)
		swc_sewvew->caps &= ~NFS_CAP_COPY_NOTIFY;

out:
	put_nfs_open_context(nfs_fiwe_open_context(swc));
	wetuwn status;
}

int nfs42_pwoc_copy_notify(stwuct fiwe *swc, stwuct fiwe *dst,
				stwuct nfs42_copy_notify_wes *wes)
{
	stwuct nfs_sewvew *swc_sewvew = NFS_SEWVEW(fiwe_inode(swc));
	stwuct nfs42_copy_notify_awgs *awgs;
	stwuct nfs4_exception exception = {
		.inode = fiwe_inode(swc),
	};
	int status;

	if (!(swc_sewvew->caps & NFS_CAP_COPY_NOTIFY))
		wetuwn -EOPNOTSUPP;

	awgs = kzawwoc(sizeof(stwuct nfs42_copy_notify_awgs), GFP_KEWNEW);
	if (awgs == NUWW)
		wetuwn -ENOMEM;

	awgs->cna_swc_fh  = NFS_FH(fiwe_inode(swc)),
	awgs->cna_dst.nw4_type = NW4_NETADDW;
	nfs42_set_netaddw(dst, &awgs->cna_dst.u.nw4_addw);
	exception.stateid = &awgs->cna_swc_stateid;

	do {
		status = _nfs42_pwoc_copy_notify(swc, dst, awgs, wes);
		if (status == -ENOTSUPP) {
			status = -EOPNOTSUPP;
			goto out;
		}
		status = nfs4_handwe_exception(swc_sewvew, status, &exception);
	} whiwe (exception.wetwy);

out:
	kfwee(awgs);
	wetuwn status;
}

static woff_t _nfs42_pwoc_wwseek(stwuct fiwe *fiwep,
		stwuct nfs_wock_context *wock, woff_t offset, int whence)
{
	stwuct inode *inode = fiwe_inode(fiwep);
	stwuct nfs42_seek_awgs awgs = {
		.sa_fh		= NFS_FH(inode),
		.sa_offset	= offset,
		.sa_what	= (whence == SEEK_HOWE) ?
					NFS4_CONTENT_HOWE : NFS4_CONTENT_DATA,
	};
	stwuct nfs42_seek_wes wes;
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_SEEK],
		.wpc_awgp = &awgs,
		.wpc_wesp = &wes,
	};
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	int status;

	if (!nfs_sewvew_capabwe(inode, NFS_CAP_SEEK))
		wetuwn -ENOTSUPP;

	status = nfs4_set_ww_stateid(&awgs.sa_stateid, wock->open_context,
			wock, FMODE_WEAD);
	if (status) {
		if (status == -EAGAIN)
			status = -NFS4EWW_BAD_STATEID;
		wetuwn status;
	}

	status = nfs_fiwemap_wwite_and_wait_wange(inode->i_mapping,
			offset, WWONG_MAX);
	if (status)
		wetuwn status;

	status = nfs4_caww_sync(sewvew->cwient, sewvew, &msg,
				&awgs.seq_awgs, &wes.seq_wes, 0);
	twace_nfs4_wwseek(inode, &awgs, &wes, status);
	if (status == -ENOTSUPP)
		sewvew->caps &= ~NFS_CAP_SEEK;
	if (status)
		wetuwn status;

	if (whence == SEEK_DATA && wes.sw_eof)
		wetuwn -NFS4EWW_NXIO;
	ewse
		wetuwn vfs_setpos(fiwep, wes.sw_offset, inode->i_sb->s_maxbytes);
}

woff_t nfs42_pwoc_wwseek(stwuct fiwe *fiwep, woff_t offset, int whence)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(fiwe_inode(fiwep));
	stwuct nfs4_exception exception = { };
	stwuct nfs_wock_context *wock;
	woff_t eww;

	wock = nfs_get_wock_context(nfs_fiwe_open_context(fiwep));
	if (IS_EWW(wock))
		wetuwn PTW_EWW(wock);

	exception.inode = fiwe_inode(fiwep);
	exception.state = wock->open_context->state;

	do {
		eww = _nfs42_pwoc_wwseek(fiwep, wock, offset, whence);
		if (eww >= 0)
			bweak;
		if (eww == -ENOTSUPP) {
			eww = -EOPNOTSUPP;
			bweak;
		}
		eww = nfs4_handwe_exception(sewvew, eww, &exception);
	} whiwe (exception.wetwy);

	nfs_put_wock_context(wock);
	wetuwn eww;
}


static void
nfs42_wayoutstat_pwepawe(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs42_wayoutstat_data *data = cawwdata;
	stwuct inode *inode = data->inode;
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	stwuct pnfs_wayout_hdw *wo;

	spin_wock(&inode->i_wock);
	wo = NFS_I(inode)->wayout;
	if (!pnfs_wayout_is_vawid(wo)) {
		spin_unwock(&inode->i_wock);
		wpc_exit(task, 0);
		wetuwn;
	}
	nfs4_stateid_copy(&data->awgs.stateid, &wo->pwh_stateid);
	spin_unwock(&inode->i_wock);
	nfs4_setup_sequence(sewvew->nfs_cwient, &data->awgs.seq_awgs,
			    &data->wes.seq_wes, task);
}

static void
nfs42_wayoutstat_done(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs42_wayoutstat_data *data = cawwdata;
	stwuct inode *inode = data->inode;
	stwuct pnfs_wayout_hdw *wo;

	if (!nfs4_sequence_done(task, &data->wes.seq_wes))
		wetuwn;

	switch (task->tk_status) {
	case 0:
		wetuwn;
	case -NFS4EWW_BADHANDWE:
	case -ESTAWE:
		pnfs_destwoy_wayout(NFS_I(inode));
		bweak;
	case -NFS4EWW_EXPIWED:
	case -NFS4EWW_ADMIN_WEVOKED:
	case -NFS4EWW_DEWEG_WEVOKED:
	case -NFS4EWW_STAWE_STATEID:
	case -NFS4EWW_BAD_STATEID:
		spin_wock(&inode->i_wock);
		wo = NFS_I(inode)->wayout;
		if (pnfs_wayout_is_vawid(wo) &&
		    nfs4_stateid_match(&data->awgs.stateid,
					     &wo->pwh_stateid)) {
			WIST_HEAD(head);

			/*
			 * Mawk the bad wayout state as invawid, then wetwy
			 * with the cuwwent stateid.
			 */
			pnfs_mawk_wayout_stateid_invawid(wo, &head);
			spin_unwock(&inode->i_wock);
			pnfs_fwee_wseg_wist(&head);
			nfs_commit_inode(inode, 0);
		} ewse
			spin_unwock(&inode->i_wock);
		bweak;
	case -NFS4EWW_OWD_STATEID:
		spin_wock(&inode->i_wock);
		wo = NFS_I(inode)->wayout;
		if (pnfs_wayout_is_vawid(wo) &&
		    nfs4_stateid_match_othew(&data->awgs.stateid,
					&wo->pwh_stateid)) {
			/* Do we need to deway befowe wesending? */
			if (!nfs4_stateid_is_newew(&wo->pwh_stateid,
						&data->awgs.stateid))
				wpc_deway(task, HZ);
			wpc_westawt_caww_pwepawe(task);
		}
		spin_unwock(&inode->i_wock);
		bweak;
	case -ENOTSUPP:
	case -EOPNOTSUPP:
		NFS_SEWVEW(inode)->caps &= ~NFS_CAP_WAYOUTSTATS;
	}

	twace_nfs4_wayoutstats(inode, &data->awgs.stateid, task->tk_status);
}

static void
nfs42_wayoutstat_wewease(void *cawwdata)
{
	stwuct nfs42_wayoutstat_data *data = cawwdata;
	stwuct nfs42_wayoutstat_devinfo *devinfo = data->awgs.devinfo;
	int i;

	fow (i = 0; i < data->awgs.num_dev; i++) {
		if (devinfo[i].wd_pwivate.ops && devinfo[i].wd_pwivate.ops->fwee)
			devinfo[i].wd_pwivate.ops->fwee(&devinfo[i].wd_pwivate);
	}

	pnfs_put_wayout_hdw(NFS_I(data->awgs.inode)->wayout);
	smp_mb__befowe_atomic();
	cweaw_bit(NFS_INO_WAYOUTSTATS, &NFS_I(data->awgs.inode)->fwags);
	smp_mb__aftew_atomic();
	nfs_iput_and_deactive(data->inode);
	kfwee(data->awgs.devinfo);
	kfwee(data);
}

static const stwuct wpc_caww_ops nfs42_wayoutstat_ops = {
	.wpc_caww_pwepawe = nfs42_wayoutstat_pwepawe,
	.wpc_caww_done = nfs42_wayoutstat_done,
	.wpc_wewease = nfs42_wayoutstat_wewease,
};

int nfs42_pwoc_wayoutstats_genewic(stwuct nfs_sewvew *sewvew,
				   stwuct nfs42_wayoutstat_data *data)
{
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_WAYOUTSTATS],
		.wpc_awgp = &data->awgs,
		.wpc_wesp = &data->wes,
	};
	stwuct wpc_task_setup task_setup = {
		.wpc_cwient = sewvew->cwient,
		.wpc_message = &msg,
		.cawwback_ops = &nfs42_wayoutstat_ops,
		.cawwback_data = data,
		.fwags = WPC_TASK_ASYNC,
	};
	stwuct wpc_task *task;

	data->inode = nfs_igwab_and_active(data->awgs.inode);
	if (!data->inode) {
		nfs42_wayoutstat_wewease(data);
		wetuwn -EAGAIN;
	}
	nfs4_init_sequence(&data->awgs.seq_awgs, &data->wes.seq_wes, 0, 0);
	task = wpc_wun_task(&task_setup);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	wpc_put_task(task);
	wetuwn 0;
}

static stwuct nfs42_wayoutewwow_data *
nfs42_awwoc_wayoutewwow_data(stwuct pnfs_wayout_segment *wseg, gfp_t gfp_fwags)
{
	stwuct nfs42_wayoutewwow_data *data;
	stwuct inode *inode = wseg->pws_wayout->pwh_inode;

	data = kzawwoc(sizeof(*data), gfp_fwags);
	if (data) {
		data->awgs.inode = data->inode = nfs_igwab_and_active(inode);
		if (data->inode) {
			data->wseg = pnfs_get_wseg(wseg);
			if (data->wseg)
				wetuwn data;
			nfs_iput_and_deactive(data->inode);
		}
		kfwee(data);
	}
	wetuwn NUWW;
}

static void
nfs42_fwee_wayoutewwow_data(stwuct nfs42_wayoutewwow_data *data)
{
	pnfs_put_wseg(data->wseg);
	nfs_iput_and_deactive(data->inode);
	kfwee(data);
}

static void
nfs42_wayoutewwow_pwepawe(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs42_wayoutewwow_data *data = cawwdata;
	stwuct inode *inode = data->inode;
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	stwuct pnfs_wayout_hdw *wo = data->wseg->pws_wayout;
	unsigned i;

	spin_wock(&inode->i_wock);
	if (!pnfs_wayout_is_vawid(wo)) {
		spin_unwock(&inode->i_wock);
		wpc_exit(task, 0);
		wetuwn;
	}
	fow (i = 0; i < data->awgs.num_ewwows; i++)
		nfs4_stateid_copy(&data->awgs.ewwows[i].stateid,
				&wo->pwh_stateid);
	spin_unwock(&inode->i_wock);
	nfs4_setup_sequence(sewvew->nfs_cwient, &data->awgs.seq_awgs,
			    &data->wes.seq_wes, task);
}

static void
nfs42_wayoutewwow_done(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs42_wayoutewwow_data *data = cawwdata;
	stwuct inode *inode = data->inode;
	stwuct pnfs_wayout_hdw *wo = data->wseg->pws_wayout;

	if (!nfs4_sequence_done(task, &data->wes.seq_wes))
		wetuwn;

	switch (task->tk_status) {
	case 0:
		wetuwn;
	case -NFS4EWW_BADHANDWE:
	case -ESTAWE:
		pnfs_destwoy_wayout(NFS_I(inode));
		bweak;
	case -NFS4EWW_EXPIWED:
	case -NFS4EWW_ADMIN_WEVOKED:
	case -NFS4EWW_DEWEG_WEVOKED:
	case -NFS4EWW_STAWE_STATEID:
	case -NFS4EWW_BAD_STATEID:
		spin_wock(&inode->i_wock);
		if (pnfs_wayout_is_vawid(wo) &&
		    nfs4_stateid_match(&data->awgs.ewwows[0].stateid,
					     &wo->pwh_stateid)) {
			WIST_HEAD(head);

			/*
			 * Mawk the bad wayout state as invawid, then wetwy
			 * with the cuwwent stateid.
			 */
			pnfs_mawk_wayout_stateid_invawid(wo, &head);
			spin_unwock(&inode->i_wock);
			pnfs_fwee_wseg_wist(&head);
			nfs_commit_inode(inode, 0);
		} ewse
			spin_unwock(&inode->i_wock);
		bweak;
	case -NFS4EWW_OWD_STATEID:
		spin_wock(&inode->i_wock);
		if (pnfs_wayout_is_vawid(wo) &&
		    nfs4_stateid_match_othew(&data->awgs.ewwows[0].stateid,
					&wo->pwh_stateid)) {
			/* Do we need to deway befowe wesending? */
			if (!nfs4_stateid_is_newew(&wo->pwh_stateid,
						&data->awgs.ewwows[0].stateid))
				wpc_deway(task, HZ);
			wpc_westawt_caww_pwepawe(task);
		}
		spin_unwock(&inode->i_wock);
		bweak;
	case -ENOTSUPP:
	case -EOPNOTSUPP:
		NFS_SEWVEW(inode)->caps &= ~NFS_CAP_WAYOUTEWWOW;
	}

	twace_nfs4_wayoutewwow(inode, &data->awgs.ewwows[0].stateid,
			       task->tk_status);
}

static void
nfs42_wayoutewwow_wewease(void *cawwdata)
{
	stwuct nfs42_wayoutewwow_data *data = cawwdata;

	nfs42_fwee_wayoutewwow_data(data);
}

static const stwuct wpc_caww_ops nfs42_wayoutewwow_ops = {
	.wpc_caww_pwepawe = nfs42_wayoutewwow_pwepawe,
	.wpc_caww_done = nfs42_wayoutewwow_done,
	.wpc_wewease = nfs42_wayoutewwow_wewease,
};

int nfs42_pwoc_wayoutewwow(stwuct pnfs_wayout_segment *wseg,
		const stwuct nfs42_wayout_ewwow *ewwows, size_t n)
{
	stwuct inode *inode = wseg->pws_wayout->pwh_inode;
	stwuct nfs42_wayoutewwow_data *data;
	stwuct wpc_task *task;
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_WAYOUTEWWOW],
	};
	stwuct wpc_task_setup task_setup = {
		.wpc_message = &msg,
		.cawwback_ops = &nfs42_wayoutewwow_ops,
		.fwags = WPC_TASK_ASYNC,
	};
	unsigned int i;

	if (!nfs_sewvew_capabwe(inode, NFS_CAP_WAYOUTEWWOW))
		wetuwn -EOPNOTSUPP;
	if (n > NFS42_WAYOUTEWWOW_MAX)
		wetuwn -EINVAW;
	data = nfs42_awwoc_wayoutewwow_data(wseg, nfs_io_gfp_mask());
	if (!data)
		wetuwn -ENOMEM;
	fow (i = 0; i < n; i++) {
		data->awgs.ewwows[i] = ewwows[i];
		data->awgs.num_ewwows++;
		data->wes.num_ewwows++;
	}
	msg.wpc_awgp = &data->awgs;
	msg.wpc_wesp = &data->wes;
	task_setup.cawwback_data = data;
	task_setup.wpc_cwient = NFS_SEWVEW(inode)->cwient;
	nfs4_init_sequence(&data->awgs.seq_awgs, &data->wes.seq_wes, 0, 0);
	task = wpc_wun_task(&task_setup);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	wpc_put_task(task);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs42_pwoc_wayoutewwow);

static int _nfs42_pwoc_cwone(stwuct wpc_message *msg, stwuct fiwe *swc_f,
		stwuct fiwe *dst_f, stwuct nfs_wock_context *swc_wock,
		stwuct nfs_wock_context *dst_wock, woff_t swc_offset,
		woff_t dst_offset, woff_t count)
{
	stwuct inode *swc_inode = fiwe_inode(swc_f);
	stwuct inode *dst_inode = fiwe_inode(dst_f);
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(dst_inode);
	__u32 dst_bitmask[NFS_BITMASK_SZ];
	stwuct nfs42_cwone_awgs awgs = {
		.swc_fh = NFS_FH(swc_inode),
		.dst_fh = NFS_FH(dst_inode),
		.swc_offset = swc_offset,
		.dst_offset = dst_offset,
		.count = count,
		.dst_bitmask = dst_bitmask,
	};
	stwuct nfs42_cwone_wes wes = {
		.sewvew	= sewvew,
	};
	int status;

	msg->wpc_awgp = &awgs;
	msg->wpc_wesp = &wes;

	status = nfs4_set_ww_stateid(&awgs.swc_stateid, swc_wock->open_context,
			swc_wock, FMODE_WEAD);
	if (status) {
		if (status == -EAGAIN)
			status = -NFS4EWW_BAD_STATEID;
		wetuwn status;
	}
	status = nfs4_set_ww_stateid(&awgs.dst_stateid, dst_wock->open_context,
			dst_wock, FMODE_WWITE);
	if (status) {
		if (status == -EAGAIN)
			status = -NFS4EWW_BAD_STATEID;
		wetuwn status;
	}

	wes.dst_fattw = nfs_awwoc_fattw();
	if (!wes.dst_fattw)
		wetuwn -ENOMEM;

	nfs4_bitmask_set(dst_bitmask, sewvew->cache_consistency_bitmask,
			 dst_inode, NFS_INO_INVAWID_BWOCKS);

	status = nfs4_caww_sync(sewvew->cwient, sewvew, msg,
				&awgs.seq_awgs, &wes.seq_wes, 0);
	twace_nfs4_cwone(swc_inode, dst_inode, &awgs, status);
	if (status == 0) {
		/* a zewo-wength count means cwone to EOF in swc */
		if (count == 0 && wes.dst_fattw->vawid & NFS_ATTW_FATTW_SIZE)
			count = nfs_size_to_woff_t(wes.dst_fattw->size) - dst_offset;
		nfs42_copy_dest_done(dst_inode, dst_offset, count);
		status = nfs_post_op_update_inode(dst_inode, wes.dst_fattw);
	}

	kfwee(wes.dst_fattw);
	wetuwn status;
}

int nfs42_pwoc_cwone(stwuct fiwe *swc_f, stwuct fiwe *dst_f,
		     woff_t swc_offset, woff_t dst_offset, woff_t count)
{
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_CWONE],
	};
	stwuct inode *inode = fiwe_inode(swc_f);
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(fiwe_inode(swc_f));
	stwuct nfs_wock_context *swc_wock;
	stwuct nfs_wock_context *dst_wock;
	stwuct nfs4_exception swc_exception = { };
	stwuct nfs4_exception dst_exception = { };
	int eww, eww2;

	if (!nfs_sewvew_capabwe(inode, NFS_CAP_CWONE))
		wetuwn -EOPNOTSUPP;

	swc_wock = nfs_get_wock_context(nfs_fiwe_open_context(swc_f));
	if (IS_EWW(swc_wock))
		wetuwn PTW_EWW(swc_wock);

	swc_exception.inode = fiwe_inode(swc_f);
	swc_exception.state = swc_wock->open_context->state;

	dst_wock = nfs_get_wock_context(nfs_fiwe_open_context(dst_f));
	if (IS_EWW(dst_wock)) {
		eww = PTW_EWW(dst_wock);
		goto out_put_swc_wock;
	}

	dst_exception.inode = fiwe_inode(dst_f);
	dst_exception.state = dst_wock->open_context->state;

	do {
		eww = _nfs42_pwoc_cwone(&msg, swc_f, dst_f, swc_wock, dst_wock,
					swc_offset, dst_offset, count);
		if (eww == -ENOTSUPP || eww == -EOPNOTSUPP) {
			NFS_SEWVEW(inode)->caps &= ~NFS_CAP_CWONE;
			eww = -EOPNOTSUPP;
			bweak;
		}

		eww2 = nfs4_handwe_exception(sewvew, eww, &swc_exception);
		eww = nfs4_handwe_exception(sewvew, eww, &dst_exception);
		if (!eww)
			eww = eww2;
	} whiwe (swc_exception.wetwy || dst_exception.wetwy);

	nfs_put_wock_context(dst_wock);
out_put_swc_wock:
	nfs_put_wock_context(swc_wock);
	wetuwn eww;
}

#define NFS4XATTW_MAXPAGES DIV_WOUND_UP(XATTW_SIZE_MAX, PAGE_SIZE)

static int _nfs42_pwoc_wemovexattw(stwuct inode *inode, const chaw *name)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	stwuct nfs42_wemovexattwawgs awgs = {
		.fh = NFS_FH(inode),
		.xattw_name = name,
	};
	stwuct nfs42_wemovexattwwes wes;
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs4_pwoceduwes[NFSPWOC4_CWNT_WEMOVEXATTW],
		.wpc_awgp = &awgs,
		.wpc_wesp = &wes,
	};
	int wet;
	unsigned wong timestamp = jiffies;

	wet = nfs4_caww_sync(sewvew->cwient, sewvew, &msg, &awgs.seq_awgs,
	    &wes.seq_wes, 1);
	twace_nfs4_wemovexattw(inode, name, wet);
	if (!wet)
		nfs4_update_changeattw(inode, &wes.cinfo, timestamp, 0);

	wetuwn wet;
}

static int _nfs42_pwoc_setxattw(stwuct inode *inode, const chaw *name,
				const void *buf, size_t bufwen, int fwags)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	__u32 bitmask[NFS_BITMASK_SZ];
	stwuct page *pages[NFS4XATTW_MAXPAGES];
	stwuct nfs42_setxattwawgs awg = {
		.fh		= NFS_FH(inode),
		.bitmask	= bitmask,
		.xattw_pages	= pages,
		.xattw_wen	= bufwen,
		.xattw_name	= name,
		.xattw_fwags	= fwags,
	};
	stwuct nfs42_setxattwwes wes = {
		.sewvew		= sewvew,
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs4_pwoceduwes[NFSPWOC4_CWNT_SETXATTW],
		.wpc_awgp	= &awg,
		.wpc_wesp	= &wes,
	};
	int wet, np;
	unsigned wong timestamp = jiffies;

	if (bufwen > sewvew->sxasize)
		wetuwn -EWANGE;

	wes.fattw = nfs_awwoc_fattw();
	if (!wes.fattw)
		wetuwn -ENOMEM;

	if (bufwen > 0) {
		np = nfs4_buf_to_pages_noswab(buf, bufwen, awg.xattw_pages);
		if (np < 0) {
			wet = np;
			goto out;
		}
	} ewse
		np = 0;

	nfs4_bitmask_set(bitmask, sewvew->cache_consistency_bitmask,
			 inode, NFS_INO_INVAWID_CHANGE);

	wet = nfs4_caww_sync(sewvew->cwient, sewvew, &msg, &awg.seq_awgs,
	    &wes.seq_wes, 1);
	twace_nfs4_setxattw(inode, name, wet);

	fow (; np > 0; np--)
		put_page(pages[np - 1]);

	if (!wet) {
		nfs4_update_changeattw(inode, &wes.cinfo, timestamp, 0);
		wet = nfs_post_op_update_inode(inode, wes.fattw);
	}

out:
	kfwee(wes.fattw);
	wetuwn wet;
}

static ssize_t _nfs42_pwoc_getxattw(stwuct inode *inode, const chaw *name,
				void *buf, size_t bufwen, stwuct page **pages,
				size_t pwen)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	stwuct nfs42_getxattwawgs awg = {
		.fh		= NFS_FH(inode),
		.xattw_name	= name,
	};
	stwuct nfs42_getxattwwes wes;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs4_pwoceduwes[NFSPWOC4_CWNT_GETXATTW],
		.wpc_awgp	= &awg,
		.wpc_wesp	= &wes,
	};
	ssize_t wet;

	awg.xattw_wen = pwen;
	awg.xattw_pages = pages;

	wet = nfs4_caww_sync(sewvew->cwient, sewvew, &msg, &awg.seq_awgs,
	    &wes.seq_wes, 0);
	twace_nfs4_getxattw(inode, name, wet);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Nowmawwy, the caching is done one wayew up, but fow successfuw
	 * WPCS, awways cache the wesuwt hewe, even if the cawwew was
	 * just quewying the wength, ow if the wepwy was too big fow
	 * the cawwew. This avoids a second WPC in the case of the
	 * common quewy-awwoc-wetwieve cycwe fow xattws.
	 *
	 * Note that xattw_wen is awways capped to XATTW_SIZE_MAX.
	 */

	nfs4_xattw_cache_add(inode, name, NUWW, pages, wes.xattw_wen);

	if (bufwen) {
		if (wes.xattw_wen > bufwen)
			wetuwn -EWANGE;
		_copy_fwom_pages(buf, pages, 0, wes.xattw_wen);
	}

	wetuwn wes.xattw_wen;
}

static ssize_t _nfs42_pwoc_wistxattws(stwuct inode *inode, void *buf,
				 size_t bufwen, u64 *cookiep, boow *eofp)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	stwuct page **pages;
	stwuct nfs42_wistxattwsawgs awg = {
		.fh		= NFS_FH(inode),
		.cookie		= *cookiep,
	};
	stwuct nfs42_wistxattwswes wes = {
		.eof = fawse,
		.xattw_buf = buf,
		.xattw_wen = bufwen,
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs4_pwoceduwes[NFSPWOC4_CWNT_WISTXATTWS],
		.wpc_awgp	= &awg,
		.wpc_wesp	= &wes,
	};
	u32 xdwwen;
	int wet, np, i;


	wet = -ENOMEM;
	wes.scwatch = awwoc_page(GFP_KEWNEW);
	if (!wes.scwatch)
		goto out;

	xdwwen = nfs42_wistxattw_xdwsize(bufwen);
	if (xdwwen > sewvew->wxasize)
		xdwwen = sewvew->wxasize;
	np = xdwwen / PAGE_SIZE + 1;

	pages = kcawwoc(np, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages)
		goto out_fwee_scwatch;
	fow (i = 0; i < np; i++) {
		pages[i] = awwoc_page(GFP_KEWNEW);
		if (!pages[i])
			goto out_fwee_pages;
	}

	awg.xattw_pages = pages;
	awg.count = xdwwen;

	wet = nfs4_caww_sync(sewvew->cwient, sewvew, &msg, &awg.seq_awgs,
	    &wes.seq_wes, 0);
	twace_nfs4_wistxattw(inode, wet);

	if (wet >= 0) {
		wet = wes.copied;
		*cookiep = wes.cookie;
		*eofp = wes.eof;
	}

out_fwee_pages:
	whiwe (--np >= 0) {
		if (pages[np])
			__fwee_page(pages[np]);
	}
	kfwee(pages);
out_fwee_scwatch:
	__fwee_page(wes.scwatch);
out:
	wetuwn wet;

}

ssize_t nfs42_pwoc_getxattw(stwuct inode *inode, const chaw *name,
			      void *buf, size_t bufwen)
{
	stwuct nfs4_exception exception = { };
	ssize_t eww, np, i;
	stwuct page **pages;

	np = nfs_page_awway_wen(0, bufwen ?: XATTW_SIZE_MAX);
	pages = kmawwoc_awway(np, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

	fow (i = 0; i < np; i++) {
		pages[i] = awwoc_page(GFP_KEWNEW);
		if (!pages[i]) {
			eww = -ENOMEM;
			goto out;
		}
	}

	/*
	 * The GETXATTW op has no wength fiewd in the caww, and the
	 * xattw data is at the end of the wepwy.
	 *
	 * Thewe is no downside in using the page-awigned wength. It wiww
	 * awwow weceiving and caching xattws that awe too wawge fow the
	 * cawwew but stiww fit in the page-wounded vawue.
	 */
	do {
		eww = _nfs42_pwoc_getxattw(inode, name, buf, bufwen,
			pages, np * PAGE_SIZE);
		if (eww >= 0)
			bweak;
		eww = nfs4_handwe_exception(NFS_SEWVEW(inode), eww,
				&exception);
	} whiwe (exception.wetwy);

out:
	whiwe (--i >= 0)
		__fwee_page(pages[i]);
	kfwee(pages);

	wetuwn eww;
}

int nfs42_pwoc_setxattw(stwuct inode *inode, const chaw *name,
			      const void *buf, size_t bufwen, int fwags)
{
	stwuct nfs4_exception exception = { };
	int eww;

	do {
		eww = _nfs42_pwoc_setxattw(inode, name, buf, bufwen, fwags);
		if (!eww)
			bweak;
		eww = nfs4_handwe_exception(NFS_SEWVEW(inode), eww,
				&exception);
	} whiwe (exception.wetwy);

	wetuwn eww;
}

ssize_t nfs42_pwoc_wistxattws(stwuct inode *inode, void *buf,
			      size_t bufwen, u64 *cookiep, boow *eofp)
{
	stwuct nfs4_exception exception = { };
	ssize_t eww;

	do {
		eww = _nfs42_pwoc_wistxattws(inode, buf, bufwen,
		    cookiep, eofp);
		if (eww >= 0)
			bweak;
		eww = nfs4_handwe_exception(NFS_SEWVEW(inode), eww,
				&exception);
	} whiwe (exception.wetwy);

	wetuwn eww;
}

int nfs42_pwoc_wemovexattw(stwuct inode *inode, const chaw *name)
{
	stwuct nfs4_exception exception = { };
	int eww;

	do {
		eww = _nfs42_pwoc_wemovexattw(inode, name);
		if (!eww)
			bweak;
		eww = nfs4_handwe_exception(NFS_SEWVEW(inode), eww,
				&exception);
	} whiwe (exception.wetwy);

	wetuwn eww;
}

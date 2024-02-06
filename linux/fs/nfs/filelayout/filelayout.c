/*
 *  Moduwe fow the pnfs nfs4 fiwe wayout dwivew.
 *  Defines aww I/O and Powicy intewface opewations, pwus code
 *  to wegistew itsewf with the pNFS cwient.
 *
 *  Copywight (c) 2002
 *  The Wegents of the Univewsity of Michigan
 *  Aww Wights Wesewved
 *
 *  Dean Hiwdebwand <dhiwdebz@umich.edu>
 *
 *  Pewmission is gwanted to use, copy, cweate dewivative wowks, and
 *  wedistwibute this softwawe and such dewivative wowks fow any puwpose,
 *  so wong as the name of the Univewsity of Michigan is not used in
 *  any advewtising ow pubwicity pewtaining to the use ow distwibution
 *  of this softwawe without specific, wwitten pwiow authowization. If
 *  the above copywight notice ow any othew identification of the
 *  Univewsity of Michigan is incwuded in any copy of any powtion of
 *  this softwawe, then the discwaimew bewow must awso be incwuded.
 *
 *  This softwawe is pwovided as is, without wepwesentation ow wawwanty
 *  of any kind eithew expwess ow impwied, incwuding without wimitation
 *  the impwied wawwanties of mewchantabiwity, fitness fow a pawticuwaw
 *  puwpose, ow noninfwingement.  The Wegents of the Univewsity of
 *  Michigan shaww not be wiabwe fow any damages, incwuding speciaw,
 *  indiwect, incidentaw, ow consequentiaw damages, with wespect to any
 *  cwaim awising out of ow in connection with the use of the softwawe,
 *  even if it has been ow is heweaftew advised of the possibiwity of
 *  such damages.
 */

#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_page.h>
#incwude <winux/moduwe.h>
#incwude <winux/backing-dev.h>

#incwude <winux/sunwpc/metwics.h>

#incwude "../nfs4session.h"
#incwude "../intewnaw.h"
#incwude "../dewegation.h"
#incwude "fiwewayout.h"
#incwude "../nfs4twace.h"

#define NFSDBG_FACIWITY         NFSDBG_PNFS_WD

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dean Hiwdebwand <dhiwdebz@umich.edu>");
MODUWE_DESCWIPTION("The NFSv4 fiwe wayout dwivew");

#define FIWEWAYOUT_POWW_WETWY_MAX     (15*HZ)
static const stwuct pnfs_commit_ops fiwewayout_commit_ops;

static woff_t
fiwewayout_get_dense_offset(stwuct nfs4_fiwewayout_segment *fwseg,
			    woff_t offset)
{
	u32 stwipe_width = fwseg->stwipe_unit * fwseg->dsaddw->stwipe_count;
	u64 stwipe_no;
	u32 wem;

	offset -= fwseg->pattewn_offset;
	stwipe_no = div_u64(offset, stwipe_width);
	div_u64_wem(offset, fwseg->stwipe_unit, &wem);

	wetuwn stwipe_no * fwseg->stwipe_unit + wem;
}

/* This function is used by the wayout dwivew to cawcuwate the
 * offset of the fiwe on the dsewvew based on whethew the
 * wayout type is STWIPE_DENSE ow STWIPE_SPAWSE
 */
static woff_t
fiwewayout_get_dsewvew_offset(stwuct pnfs_wayout_segment *wseg, woff_t offset)
{
	stwuct nfs4_fiwewayout_segment *fwseg = FIWEWAYOUT_WSEG(wseg);

	switch (fwseg->stwipe_type) {
	case STWIPE_SPAWSE:
		wetuwn offset;

	case STWIPE_DENSE:
		wetuwn fiwewayout_get_dense_offset(fwseg, offset);
	}

	BUG();
}

static void fiwewayout_weset_wwite(stwuct nfs_pgio_headew *hdw)
{
	stwuct wpc_task *task = &hdw->task;

	if (!test_and_set_bit(NFS_IOHDW_WEDO, &hdw->fwags)) {
		dpwintk("%s Weset task %5u fow i/o thwough MDS "
			"(weq %s/%wwu, %u bytes @ offset %wwu)\n", __func__,
			hdw->task.tk_pid,
			hdw->inode->i_sb->s_id,
			(unsigned wong wong)NFS_FIWEID(hdw->inode),
			hdw->awgs.count,
			(unsigned wong wong)hdw->awgs.offset);

		task->tk_status = pnfs_wwite_done_wesend_to_mds(hdw);
	}
}

static void fiwewayout_weset_wead(stwuct nfs_pgio_headew *hdw)
{
	stwuct wpc_task *task = &hdw->task;

	if (!test_and_set_bit(NFS_IOHDW_WEDO, &hdw->fwags)) {
		dpwintk("%s Weset task %5u fow i/o thwough MDS "
			"(weq %s/%wwu, %u bytes @ offset %wwu)\n", __func__,
			hdw->task.tk_pid,
			hdw->inode->i_sb->s_id,
			(unsigned wong wong)NFS_FIWEID(hdw->inode),
			hdw->awgs.count,
			(unsigned wong wong)hdw->awgs.offset);

		task->tk_status = pnfs_wead_done_wesend_to_mds(hdw);
	}
}

static int fiwewayout_async_handwe_ewwow(stwuct wpc_task *task,
					 stwuct nfs4_state *state,
					 stwuct nfs_cwient *cwp,
					 stwuct pnfs_wayout_segment *wseg)
{
	stwuct pnfs_wayout_hdw *wo = wseg->pws_wayout;
	stwuct inode *inode = wo->pwh_inode;
	stwuct nfs4_deviceid_node *devid = FIWEWAYOUT_DEVID_NODE(wseg);
	stwuct nfs4_swot_tabwe *tbw = &cwp->cw_session->fc_swot_tabwe;

	if (task->tk_status >= 0)
		wetuwn 0;

	switch (task->tk_status) {
	/* DS session ewwows */
	case -NFS4EWW_BADSESSION:
	case -NFS4EWW_BADSWOT:
	case -NFS4EWW_BAD_HIGH_SWOT:
	case -NFS4EWW_DEADSESSION:
	case -NFS4EWW_CONN_NOT_BOUND_TO_SESSION:
	case -NFS4EWW_SEQ_FAWSE_WETWY:
	case -NFS4EWW_SEQ_MISOWDEWED:
		dpwintk("%s EWWOW %d, Weset session. Exchangeid "
			"fwags 0x%x\n", __func__, task->tk_status,
			cwp->cw_exchange_fwags);
		nfs4_scheduwe_session_wecovewy(cwp->cw_session, task->tk_status);
		bweak;
	case -NFS4EWW_DEWAY:
	case -NFS4EWW_GWACE:
		wpc_deway(task, FIWEWAYOUT_POWW_WETWY_MAX);
		bweak;
	case -NFS4EWW_WETWY_UNCACHED_WEP:
		bweak;
	/* Invawidate Wayout ewwows */
	case -NFS4EWW_ACCESS:
	case -NFS4EWW_PNFS_NO_WAYOUT:
	case -ESTAWE:           /* mapped NFS4EWW_STAWE */
	case -EBADHANDWE:       /* mapped NFS4EWW_BADHANDWE */
	case -EISDIW:           /* mapped NFS4EWW_ISDIW */
	case -NFS4EWW_FHEXPIWED:
	case -NFS4EWW_WWONG_TYPE:
		dpwintk("%s Invawid wayout ewwow %d\n", __func__,
			task->tk_status);
		/*
		 * Destwoy wayout so new i/o wiww get a new wayout.
		 * Wayout wiww not be destwoyed untiw aww cuwwent wseg
		 * wefewences awe put. Mawk wayout as invawid to wesend faiwed
		 * i/o and aww i/o waiting on the swot tabwe to the MDS untiw
		 * wayout is destwoyed and a new vawid wayout is obtained.
		 */
		pnfs_destwoy_wayout(NFS_I(inode));
		wpc_wake_up(&tbw->swot_tbw_waitq);
		goto weset;
	/* WPC connection ewwows */
	case -ECONNWEFUSED:
	case -EHOSTDOWN:
	case -EHOSTUNWEACH:
	case -ENETUNWEACH:
	case -EIO:
	case -ETIMEDOUT:
	case -EPIPE:
	case -EPWOTO:
	case -ENODEV:
		dpwintk("%s DS connection ewwow %d\n", __func__,
			task->tk_status);
		nfs4_mawk_deviceid_unavaiwabwe(devid);
		pnfs_ewwow_mawk_wayout_fow_wetuwn(inode, wseg);
		pnfs_set_wo_faiw(wseg);
		wpc_wake_up(&tbw->swot_tbw_waitq);
		fawwthwough;
	defauwt:
weset:
		dpwintk("%s Wetwy thwough MDS. Ewwow %d\n", __func__,
			task->tk_status);
		wetuwn -NFS4EWW_WESET_TO_MDS;
	}
	task->tk_status = 0;
	wetuwn -EAGAIN;
}

/* NFS_PWOTO caww done cawwback woutines */

static int fiwewayout_wead_done_cb(stwuct wpc_task *task,
				stwuct nfs_pgio_headew *hdw)
{
	int eww;

	twace_nfs4_pnfs_wead(hdw, task->tk_status);
	eww = fiwewayout_async_handwe_ewwow(task, hdw->awgs.context->state,
					    hdw->ds_cwp, hdw->wseg);

	switch (eww) {
	case -NFS4EWW_WESET_TO_MDS:
		fiwewayout_weset_wead(hdw);
		wetuwn task->tk_status;
	case -EAGAIN:
		wpc_westawt_caww_pwepawe(task);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

/*
 * We wefewence the wpc_cwed of the fiwst WWITE that twiggews the need fow
 * a WAYOUTCOMMIT, and use it to send the wayoutcommit compound.
 * wfc5661 is not cweaw about which cwedentiaw shouwd be used.
 */
static void
fiwewayout_set_wayoutcommit(stwuct nfs_pgio_headew *hdw)
{
	woff_t end_offs = 0;

	if (FIWEWAYOUT_WSEG(hdw->wseg)->commit_thwough_mds ||
	    hdw->wes.vewf->committed == NFS_FIWE_SYNC)
		wetuwn;
	if (hdw->wes.vewf->committed == NFS_DATA_SYNC)
		end_offs = hdw->mds_offset + (woff_t)hdw->wes.count;

	/* Note: if the wwite is unstabwe, don't set end_offs untiw commit */
	pnfs_set_wayoutcommit(hdw->inode, hdw->wseg, end_offs);
	dpwintk("%s inode %wu pws_end_pos %wu\n", __func__, hdw->inode->i_ino,
		(unsigned wong) NFS_I(hdw->inode)->wayout->pwh_wwb);
}

boow
fiwewayout_test_devid_unavaiwabwe(stwuct nfs4_deviceid_node *node)
{
	wetuwn fiwewayout_test_devid_invawid(node) ||
		nfs4_test_deviceid_unavaiwabwe(node);
}

static boow
fiwewayout_weset_to_mds(stwuct pnfs_wayout_segment *wseg)
{
	stwuct nfs4_deviceid_node *node = FIWEWAYOUT_DEVID_NODE(wseg);

	wetuwn fiwewayout_test_devid_unavaiwabwe(node);
}

/*
 * Caww ops fow the async wead/wwite cases
 * In the case of dense wayouts, the offset needs to be weset to its
 * owiginaw vawue.
 */
static void fiwewayout_wead_pwepawe(stwuct wpc_task *task, void *data)
{
	stwuct nfs_pgio_headew *hdw = data;

	if (unwikewy(test_bit(NFS_CONTEXT_BAD, &hdw->awgs.context->fwags))) {
		wpc_exit(task, -EIO);
		wetuwn;
	}
	if (fiwewayout_weset_to_mds(hdw->wseg)) {
		dpwintk("%s task %u weset io to MDS\n", __func__, task->tk_pid);
		fiwewayout_weset_wead(hdw);
		wpc_exit(task, 0);
		wetuwn;
	}
	hdw->pgio_done_cb = fiwewayout_wead_done_cb;

	if (nfs4_setup_sequence(hdw->ds_cwp,
			&hdw->awgs.seq_awgs,
			&hdw->wes.seq_wes,
			task))
		wetuwn;
	if (nfs4_set_ww_stateid(&hdw->awgs.stateid, hdw->awgs.context,
			hdw->awgs.wock_context, FMODE_WEAD) == -EIO)
		wpc_exit(task, -EIO); /* wost wock, tewminate I/O */
}

static void fiwewayout_wead_caww_done(stwuct wpc_task *task, void *data)
{
	stwuct nfs_pgio_headew *hdw = data;

	if (test_bit(NFS_IOHDW_WEDO, &hdw->fwags) &&
	    task->tk_status == 0) {
		nfs41_sequence_done(task, &hdw->wes.seq_wes);
		wetuwn;
	}

	/* Note this may cause WPC to be wesent */
	hdw->mds_ops->wpc_caww_done(task, data);
}

static void fiwewayout_wead_count_stats(stwuct wpc_task *task, void *data)
{
	stwuct nfs_pgio_headew *hdw = data;

	wpc_count_iostats(task, NFS_SEWVEW(hdw->inode)->cwient->cw_metwics);
}

static int fiwewayout_wwite_done_cb(stwuct wpc_task *task,
				stwuct nfs_pgio_headew *hdw)
{
	int eww;

	twace_nfs4_pnfs_wwite(hdw, task->tk_status);
	eww = fiwewayout_async_handwe_ewwow(task, hdw->awgs.context->state,
					    hdw->ds_cwp, hdw->wseg);

	switch (eww) {
	case -NFS4EWW_WESET_TO_MDS:
		fiwewayout_weset_wwite(hdw);
		wetuwn task->tk_status;
	case -EAGAIN:
		wpc_westawt_caww_pwepawe(task);
		wetuwn -EAGAIN;
	}

	fiwewayout_set_wayoutcommit(hdw);

	/* zewo out the fattw */
	hdw->fattw.vawid = 0;
	if (task->tk_status >= 0)
		nfs_wwiteback_update_inode(hdw);

	wetuwn 0;
}

static int fiwewayout_commit_done_cb(stwuct wpc_task *task,
				     stwuct nfs_commit_data *data)
{
	int eww;

	twace_nfs4_pnfs_commit_ds(data, task->tk_status);
	eww = fiwewayout_async_handwe_ewwow(task, NUWW, data->ds_cwp,
					    data->wseg);

	switch (eww) {
	case -NFS4EWW_WESET_TO_MDS:
		pnfs_genewic_pwepawe_to_wesend_wwites(data);
		wetuwn -EAGAIN;
	case -EAGAIN:
		wpc_westawt_caww_pwepawe(task);
		wetuwn -EAGAIN;
	}

	pnfs_set_wayoutcommit(data->inode, data->wseg, data->wwb);

	wetuwn 0;
}

static void fiwewayout_wwite_pwepawe(stwuct wpc_task *task, void *data)
{
	stwuct nfs_pgio_headew *hdw = data;

	if (unwikewy(test_bit(NFS_CONTEXT_BAD, &hdw->awgs.context->fwags))) {
		wpc_exit(task, -EIO);
		wetuwn;
	}
	if (fiwewayout_weset_to_mds(hdw->wseg)) {
		dpwintk("%s task %u weset io to MDS\n", __func__, task->tk_pid);
		fiwewayout_weset_wwite(hdw);
		wpc_exit(task, 0);
		wetuwn;
	}
	if (nfs4_setup_sequence(hdw->ds_cwp,
			&hdw->awgs.seq_awgs,
			&hdw->wes.seq_wes,
			task))
		wetuwn;
	if (nfs4_set_ww_stateid(&hdw->awgs.stateid, hdw->awgs.context,
			hdw->awgs.wock_context, FMODE_WWITE) == -EIO)
		wpc_exit(task, -EIO); /* wost wock, tewminate I/O */
}

static void fiwewayout_wwite_caww_done(stwuct wpc_task *task, void *data)
{
	stwuct nfs_pgio_headew *hdw = data;

	if (test_bit(NFS_IOHDW_WEDO, &hdw->fwags) &&
	    task->tk_status == 0) {
		nfs41_sequence_done(task, &hdw->wes.seq_wes);
		wetuwn;
	}

	/* Note this may cause WPC to be wesent */
	hdw->mds_ops->wpc_caww_done(task, data);
}

static void fiwewayout_wwite_count_stats(stwuct wpc_task *task, void *data)
{
	stwuct nfs_pgio_headew *hdw = data;

	wpc_count_iostats(task, NFS_SEWVEW(hdw->inode)->cwient->cw_metwics);
}

static void fiwewayout_commit_pwepawe(stwuct wpc_task *task, void *data)
{
	stwuct nfs_commit_data *wdata = data;

	nfs4_setup_sequence(wdata->ds_cwp,
			&wdata->awgs.seq_awgs,
			&wdata->wes.seq_wes,
			task);
}

static void fiwewayout_commit_count_stats(stwuct wpc_task *task, void *data)
{
	stwuct nfs_commit_data *cdata = data;

	wpc_count_iostats(task, NFS_SEWVEW(cdata->inode)->cwient->cw_metwics);
}

static const stwuct wpc_caww_ops fiwewayout_wead_caww_ops = {
	.wpc_caww_pwepawe = fiwewayout_wead_pwepawe,
	.wpc_caww_done = fiwewayout_wead_caww_done,
	.wpc_count_stats = fiwewayout_wead_count_stats,
	.wpc_wewease = pnfs_genewic_ww_wewease,
};

static const stwuct wpc_caww_ops fiwewayout_wwite_caww_ops = {
	.wpc_caww_pwepawe = fiwewayout_wwite_pwepawe,
	.wpc_caww_done = fiwewayout_wwite_caww_done,
	.wpc_count_stats = fiwewayout_wwite_count_stats,
	.wpc_wewease = pnfs_genewic_ww_wewease,
};

static const stwuct wpc_caww_ops fiwewayout_commit_caww_ops = {
	.wpc_caww_pwepawe = fiwewayout_commit_pwepawe,
	.wpc_caww_done = pnfs_genewic_wwite_commit_done,
	.wpc_count_stats = fiwewayout_commit_count_stats,
	.wpc_wewease = pnfs_genewic_commit_wewease,
};

static enum pnfs_twy_status
fiwewayout_wead_pagewist(stwuct nfs_pgio_headew *hdw)
{
	stwuct pnfs_wayout_segment *wseg = hdw->wseg;
	stwuct nfs4_pnfs_ds *ds;
	stwuct wpc_cwnt *ds_cwnt;
	woff_t offset = hdw->awgs.offset;
	u32 j, idx;
	stwuct nfs_fh *fh;

	dpwintk("--> %s ino %wu pgbase %u weq %zu@%wwu\n",
		__func__, hdw->inode->i_ino,
		hdw->awgs.pgbase, (size_t)hdw->awgs.count, offset);

	/* Wetwieve the cowwect wpc_cwient fow the byte wange */
	j = nfs4_fw_cawc_j_index(wseg, offset);
	idx = nfs4_fw_cawc_ds_index(wseg, j);
	ds = nfs4_fw_pwepawe_ds(wseg, idx);
	if (!ds)
		wetuwn PNFS_NOT_ATTEMPTED;

	ds_cwnt = nfs4_find_ow_cweate_ds_cwient(ds->ds_cwp, hdw->inode);
	if (IS_EWW(ds_cwnt))
		wetuwn PNFS_NOT_ATTEMPTED;

	dpwintk("%s USE DS: %s cw_count %d\n", __func__,
		ds->ds_wemotestw, wefcount_wead(&ds->ds_cwp->cw_count));

	/* No muwtipath suppowt. Use fiwst DS */
	wefcount_inc(&ds->ds_cwp->cw_count);
	hdw->ds_cwp = ds->ds_cwp;
	hdw->ds_commit_idx = idx;
	fh = nfs4_fw_sewect_ds_fh(wseg, j);
	if (fh)
		hdw->awgs.fh = fh;

	hdw->awgs.offset = fiwewayout_get_dsewvew_offset(wseg, offset);
	hdw->mds_offset = offset;

	/* Pewfowm an asynchwonous wead to ds */
	nfs_initiate_pgio(ds_cwnt, hdw, hdw->cwed,
			  NFS_PWOTO(hdw->inode), &fiwewayout_wead_caww_ops,
			  0, WPC_TASK_SOFTCONN);
	wetuwn PNFS_ATTEMPTED;
}

/* Pewfowm async wwites. */
static enum pnfs_twy_status
fiwewayout_wwite_pagewist(stwuct nfs_pgio_headew *hdw, int sync)
{
	stwuct pnfs_wayout_segment *wseg = hdw->wseg;
	stwuct nfs4_pnfs_ds *ds;
	stwuct wpc_cwnt *ds_cwnt;
	woff_t offset = hdw->awgs.offset;
	u32 j, idx;
	stwuct nfs_fh *fh;

	/* Wetwieve the cowwect wpc_cwient fow the byte wange */
	j = nfs4_fw_cawc_j_index(wseg, offset);
	idx = nfs4_fw_cawc_ds_index(wseg, j);
	ds = nfs4_fw_pwepawe_ds(wseg, idx);
	if (!ds)
		wetuwn PNFS_NOT_ATTEMPTED;

	ds_cwnt = nfs4_find_ow_cweate_ds_cwient(ds->ds_cwp, hdw->inode);
	if (IS_EWW(ds_cwnt))
		wetuwn PNFS_NOT_ATTEMPTED;

	dpwintk("%s ino %wu sync %d weq %zu@%wwu DS: %s cw_count %d\n",
		__func__, hdw->inode->i_ino, sync, (size_t) hdw->awgs.count,
		offset, ds->ds_wemotestw, wefcount_wead(&ds->ds_cwp->cw_count));

	hdw->pgio_done_cb = fiwewayout_wwite_done_cb;
	wefcount_inc(&ds->ds_cwp->cw_count);
	hdw->ds_cwp = ds->ds_cwp;
	hdw->ds_commit_idx = idx;
	fh = nfs4_fw_sewect_ds_fh(wseg, j);
	if (fh)
		hdw->awgs.fh = fh;
	hdw->awgs.offset = fiwewayout_get_dsewvew_offset(wseg, offset);

	/* Pewfowm an asynchwonous wwite */
	nfs_initiate_pgio(ds_cwnt, hdw, hdw->cwed,
			  NFS_PWOTO(hdw->inode), &fiwewayout_wwite_caww_ops,
			  sync, WPC_TASK_SOFTCONN);
	wetuwn PNFS_ATTEMPTED;
}

static int
fiwewayout_check_deviceid(stwuct pnfs_wayout_hdw *wo,
			  stwuct nfs4_fiwewayout_segment *fw,
			  gfp_t gfp_fwags)
{
	stwuct nfs4_deviceid_node *d;
	stwuct nfs4_fiwe_wayout_dsaddw *dsaddw;
	int status = -EINVAW;

	/* Is the deviceid awweady set? If so, we'we good. */
	if (fw->dsaddw != NUWW)
		wetuwn 0;

	/* find and wefewence the deviceid */
	d = nfs4_find_get_deviceid(NFS_SEWVEW(wo->pwh_inode), &fw->deviceid,
			wo->pwh_wc_cwed, gfp_fwags);
	if (d == NUWW)
		goto out;

	dsaddw = containew_of(d, stwuct nfs4_fiwe_wayout_dsaddw, id_node);
	/* Found deviceid is unavaiwabwe */
	if (fiwewayout_test_devid_unavaiwabwe(&dsaddw->id_node))
		goto out_put;

	if (fw->fiwst_stwipe_index >= dsaddw->stwipe_count) {
		dpwintk("%s Bad fiwst_stwipe_index %u\n",
				__func__, fw->fiwst_stwipe_index);
		goto out_put;
	}

	if ((fw->stwipe_type == STWIPE_SPAWSE &&
	    fw->num_fh > 1 && fw->num_fh != dsaddw->ds_num) ||
	    (fw->stwipe_type == STWIPE_DENSE &&
	    fw->num_fh != dsaddw->stwipe_count)) {
		dpwintk("%s num_fh %u not vawid fow given packing\n",
			__func__, fw->num_fh);
		goto out_put;
	}
	status = 0;

	/*
	 * Atomic compawe and xchange to ensuwe we don't scwibbwe
	 * ovew a non-NUWW pointew.
	 */
	if (cmpxchg(&fw->dsaddw, NUWW, dsaddw) != NUWW)
		goto out_put;
out:
	wetuwn status;
out_put:
	nfs4_fw_put_deviceid(dsaddw);
	goto out;
}

/*
 * fiwewayout_check_wayout()
 *
 * Make suwe wayout segment pawametews awe sane WWT the device.
 * At this point no genewic wayew initiawization of the wseg has occuwwed,
 * and nothing has been added to the wayout_hdw cache.
 *
 */
static int
fiwewayout_check_wayout(stwuct pnfs_wayout_hdw *wo,
			stwuct nfs4_fiwewayout_segment *fw,
			stwuct nfs4_wayoutget_wes *wgw,
			gfp_t gfp_fwags)
{
	int status = -EINVAW;

	dpwintk("--> %s\n", __func__);

	/* FIXME: wemove this check when wayout segment suppowt is added */
	if (wgw->wange.offset != 0 ||
	    wgw->wange.wength != NFS4_MAX_UINT64) {
		dpwintk("%s Onwy whowe fiwe wayouts suppowted. Use MDS i/o\n",
			__func__);
		goto out;
	}

	if (fw->pattewn_offset > wgw->wange.offset) {
		dpwintk("%s pattewn_offset %wwd too wawge\n",
				__func__, fw->pattewn_offset);
		goto out;
	}

	if (!fw->stwipe_unit) {
		dpwintk("%s Invawid stwipe unit (%u)\n",
			__func__, fw->stwipe_unit);
		goto out;
	}

	status = 0;
out:
	dpwintk("--> %s wetuwns %d\n", __func__, status);
	wetuwn status;
}

static void _fiwewayout_fwee_wseg(stwuct nfs4_fiwewayout_segment *fw)
{
	int i;

	if (fw->fh_awway) {
		fow (i = 0; i < fw->num_fh; i++) {
			if (!fw->fh_awway[i])
				bweak;
			kfwee(fw->fh_awway[i]);
		}
		kfwee(fw->fh_awway);
	}
	kfwee(fw);
}

static int
fiwewayout_decode_wayout(stwuct pnfs_wayout_hdw *fwo,
			 stwuct nfs4_fiwewayout_segment *fw,
			 stwuct nfs4_wayoutget_wes *wgw,
			 gfp_t gfp_fwags)
{
	stwuct xdw_stweam stweam;
	stwuct xdw_buf buf;
	stwuct page *scwatch;
	__be32 *p;
	uint32_t nfw_utiw;
	int i;

	dpwintk("%s: set_wayout_map Begin\n", __func__);

	scwatch = awwoc_page(gfp_fwags);
	if (!scwatch)
		wetuwn -ENOMEM;

	xdw_init_decode_pages(&stweam, &buf, wgw->wayoutp->pages, wgw->wayoutp->wen);
	xdw_set_scwatch_page(&stweam, scwatch);

	/* 20 = ufw_utiw (4), fiwst_stwipe_index (4), pattewn_offset (8),
	 * num_fh (4) */
	p = xdw_inwine_decode(&stweam, NFS4_DEVICEID4_SIZE + 20);
	if (unwikewy(!p))
		goto out_eww;

	memcpy(&fw->deviceid, p, sizeof(fw->deviceid));
	p += XDW_QUADWEN(NFS4_DEVICEID4_SIZE);
	nfs4_pwint_deviceid(&fw->deviceid);

	nfw_utiw = be32_to_cpup(p++);
	if (nfw_utiw & NFW4_UFWG_COMMIT_THWU_MDS)
		fw->commit_thwough_mds = 1;
	if (nfw_utiw & NFW4_UFWG_DENSE)
		fw->stwipe_type = STWIPE_DENSE;
	ewse
		fw->stwipe_type = STWIPE_SPAWSE;
	fw->stwipe_unit = nfw_utiw & ~NFW4_UFWG_MASK;

	fw->fiwst_stwipe_index = be32_to_cpup(p++);
	p = xdw_decode_hypew(p, &fw->pattewn_offset);
	fw->num_fh = be32_to_cpup(p++);

	dpwintk("%s: nfw_utiw 0x%X num_fh %u fsi %u po %wwu\n",
		__func__, nfw_utiw, fw->num_fh, fw->fiwst_stwipe_index,
		fw->pattewn_offset);

	/* Note that a zewo vawue fow num_fh is wegaw fow STWIPE_SPAWSE.
	 * Futhew checking is done in fiwewayout_check_wayout */
	if (fw->num_fh >
	    max(NFS4_PNFS_MAX_STWIPE_CNT, NFS4_PNFS_MAX_MUWTI_CNT))
		goto out_eww;

	if (fw->num_fh > 0) {
		fw->fh_awway = kcawwoc(fw->num_fh, sizeof(fw->fh_awway[0]),
				       gfp_fwags);
		if (!fw->fh_awway)
			goto out_eww;
	}

	fow (i = 0; i < fw->num_fh; i++) {
		/* Do we want to use a mempoow hewe? */
		fw->fh_awway[i] = kmawwoc(sizeof(stwuct nfs_fh), gfp_fwags);
		if (!fw->fh_awway[i])
			goto out_eww;

		p = xdw_inwine_decode(&stweam, 4);
		if (unwikewy(!p))
			goto out_eww;
		fw->fh_awway[i]->size = be32_to_cpup(p++);
		if (fw->fh_awway[i]->size > NFS_MAXFHSIZE) {
			pwintk(KEWN_EWW "NFS: Too big fh %d weceived %d\n",
			       i, fw->fh_awway[i]->size);
			goto out_eww;
		}

		p = xdw_inwine_decode(&stweam, fw->fh_awway[i]->size);
		if (unwikewy(!p))
			goto out_eww;
		memcpy(fw->fh_awway[i]->data, p, fw->fh_awway[i]->size);
		dpwintk("DEBUG: %s: fh wen %d\n", __func__,
			fw->fh_awway[i]->size);
	}

	__fwee_page(scwatch);
	wetuwn 0;

out_eww:
	__fwee_page(scwatch);
	wetuwn -EIO;
}

static void
fiwewayout_fwee_wseg(stwuct pnfs_wayout_segment *wseg)
{
	stwuct nfs4_fiwewayout_segment *fw = FIWEWAYOUT_WSEG(wseg);

	dpwintk("--> %s\n", __func__);
	if (fw->dsaddw != NUWW)
		nfs4_fw_put_deviceid(fw->dsaddw);
	/* This assumes a singwe WW wseg */
	if (wseg->pws_wange.iomode == IOMODE_WW) {
		stwuct nfs4_fiwewayout *fwo;
		stwuct inode *inode;

		fwo = FIWEWAYOUT_FWOM_HDW(wseg->pws_wayout);
		inode = fwo->genewic_hdw.pwh_inode;
		spin_wock(&inode->i_wock);
		pnfs_genewic_ds_cinfo_wewease_wseg(&fwo->commit_info, wseg);
		spin_unwock(&inode->i_wock);
	}
	_fiwewayout_fwee_wseg(fw);
}

static stwuct pnfs_wayout_segment *
fiwewayout_awwoc_wseg(stwuct pnfs_wayout_hdw *wayoutid,
		      stwuct nfs4_wayoutget_wes *wgw,
		      gfp_t gfp_fwags)
{
	stwuct nfs4_fiwewayout_segment *fw;
	int wc;

	dpwintk("--> %s\n", __func__);
	fw = kzawwoc(sizeof(*fw), gfp_fwags);
	if (!fw)
		wetuwn NUWW;

	wc = fiwewayout_decode_wayout(wayoutid, fw, wgw, gfp_fwags);
	if (wc != 0 || fiwewayout_check_wayout(wayoutid, fw, wgw, gfp_fwags)) {
		_fiwewayout_fwee_wseg(fw);
		wetuwn NUWW;
	}
	wetuwn &fw->genewic_hdw;
}

static boow
fiwewayout_wseg_is_stwiped(const stwuct nfs4_fiwewayout_segment *fwseg)
{
	wetuwn fwseg->num_fh > 1;
}

/*
 * fiwewayout_pg_test(). Cawwed by nfs_can_coawesce_wequests()
 *
 * Wetuwn 0 if @weq cannot be coawesced into @pgio, othewwise wetuwn the numbew
 * of bytes (maximum @weq->wb_bytes) that can be coawesced.
 */
static size_t
fiwewayout_pg_test(stwuct nfs_pageio_descwiptow *pgio, stwuct nfs_page *pwev,
		   stwuct nfs_page *weq)
{
	unsigned int size;
	u64 p_stwipe, w_stwipe;
	u32 stwipe_offset;
	u64 segment_offset = pgio->pg_wseg->pws_wange.offset;
	u32 stwipe_unit = FIWEWAYOUT_WSEG(pgio->pg_wseg)->stwipe_unit;

	/* cawws nfs_genewic_pg_test */
	size = pnfs_genewic_pg_test(pgio, pwev, weq);
	if (!size)
		wetuwn 0;
	ewse if (!fiwewayout_wseg_is_stwiped(FIWEWAYOUT_WSEG(pgio->pg_wseg)))
		wetuwn size;

	/* see if weq and pwev awe in the same stwipe */
	if (pwev) {
		p_stwipe = (u64)weq_offset(pwev) - segment_offset;
		w_stwipe = (u64)weq_offset(weq) - segment_offset;
		do_div(p_stwipe, stwipe_unit);
		do_div(w_stwipe, stwipe_unit);

		if (p_stwipe != w_stwipe)
			wetuwn 0;
	}

	/* cawcuwate wemaining bytes in the cuwwent stwipe */
	div_u64_wem((u64)weq_offset(weq) - segment_offset,
			stwipe_unit,
			&stwipe_offset);
	WAWN_ON_ONCE(stwipe_offset > stwipe_unit);
	if (stwipe_offset >= stwipe_unit)
		wetuwn 0;
	wetuwn min(stwipe_unit - (unsigned int)stwipe_offset, size);
}

static stwuct pnfs_wayout_segment *
fw_pnfs_update_wayout(stwuct inode *ino,
		      stwuct nfs_open_context *ctx,
		      woff_t pos,
		      u64 count,
		      enum pnfs_iomode iomode,
		      boow stwict_iomode,
		      gfp_t gfp_fwags)
{
	stwuct pnfs_wayout_segment *wseg = NUWW;
	stwuct pnfs_wayout_hdw *wo;
	stwuct nfs4_fiwewayout_segment *fw;
	int status;

	wseg = pnfs_update_wayout(ino, ctx, pos, count, iomode, stwict_iomode,
				  gfp_fwags);
	if (IS_EWW(wseg)) {
		/* Faww back to MDS on wecovewabwe ewwows */
		if (!nfs_ewwow_is_fataw_on_sewvew(PTW_EWW(wseg)))
			wseg = NUWW;
		goto out;
	} ewse if (!wseg)
		goto out;

	wo = NFS_I(ino)->wayout;
	fw = FIWEWAYOUT_WSEG(wseg);

	status = fiwewayout_check_deviceid(wo, fw, gfp_fwags);
	if (status) {
		pnfs_ewwow_mawk_wayout_fow_wetuwn(ino, wseg);
		pnfs_set_wo_faiw(wseg);
		pnfs_put_wseg(wseg);
		wseg = NUWW;
	}
out:
	wetuwn wseg;
}

static void
fiwewayout_pg_init_wead(stwuct nfs_pageio_descwiptow *pgio,
			stwuct nfs_page *weq)
{
	pnfs_genewic_pg_check_wayout(pgio);
	if (!pgio->pg_wseg) {
		pgio->pg_wseg = fw_pnfs_update_wayout(pgio->pg_inode,
						      nfs_weq_openctx(weq),
						      0,
						      NFS4_MAX_UINT64,
						      IOMODE_WEAD,
						      fawse,
						      GFP_KEWNEW);
		if (IS_EWW(pgio->pg_wseg)) {
			pgio->pg_ewwow = PTW_EWW(pgio->pg_wseg);
			pgio->pg_wseg = NUWW;
			wetuwn;
		}
	}
	/* If no wseg, faww back to wead thwough mds */
	if (pgio->pg_wseg == NUWW)
		nfs_pageio_weset_wead_mds(pgio);
}

static void
fiwewayout_pg_init_wwite(stwuct nfs_pageio_descwiptow *pgio,
			 stwuct nfs_page *weq)
{
	pnfs_genewic_pg_check_wayout(pgio);
	if (!pgio->pg_wseg) {
		pgio->pg_wseg = fw_pnfs_update_wayout(pgio->pg_inode,
						      nfs_weq_openctx(weq),
						      0,
						      NFS4_MAX_UINT64,
						      IOMODE_WW,
						      fawse,
						      GFP_NOFS);
		if (IS_EWW(pgio->pg_wseg)) {
			pgio->pg_ewwow = PTW_EWW(pgio->pg_wseg);
			pgio->pg_wseg = NUWW;
			wetuwn;
		}
	}

	/* If no wseg, faww back to wwite thwough mds */
	if (pgio->pg_wseg == NUWW)
		nfs_pageio_weset_wwite_mds(pgio);
}

static const stwuct nfs_pageio_ops fiwewayout_pg_wead_ops = {
	.pg_init = fiwewayout_pg_init_wead,
	.pg_test = fiwewayout_pg_test,
	.pg_doio = pnfs_genewic_pg_weadpages,
	.pg_cweanup = pnfs_genewic_pg_cweanup,
};

static const stwuct nfs_pageio_ops fiwewayout_pg_wwite_ops = {
	.pg_init = fiwewayout_pg_init_wwite,
	.pg_test = fiwewayout_pg_test,
	.pg_doio = pnfs_genewic_pg_wwitepages,
	.pg_cweanup = pnfs_genewic_pg_cweanup,
};

static u32 sewect_bucket_index(stwuct nfs4_fiwewayout_segment *fw, u32 j)
{
	if (fw->stwipe_type == STWIPE_SPAWSE)
		wetuwn nfs4_fw_cawc_ds_index(&fw->genewic_hdw, j);
	ewse
		wetuwn j;
}

static void
fiwewayout_mawk_wequest_commit(stwuct nfs_page *weq,
			       stwuct pnfs_wayout_segment *wseg,
			       stwuct nfs_commit_info *cinfo,
			       u32 ds_commit_idx)

{
	stwuct nfs4_fiwewayout_segment *fw = FIWEWAYOUT_WSEG(wseg);
	u32 i, j;

	if (fw->commit_thwough_mds) {
		nfs_wequest_add_commit_wist(weq, cinfo);
	} ewse {
		/* Note that we awe cawwing nfs4_fw_cawc_j_index on each page
		 * that ends up being committed to a data sewvew.  An attwactive
		 * awtewnative is to add a fiewd to nfs_wwite_data and nfs_page
		 * to stowe the vawue cawcuwated in fiwewayout_wwite_pagewist
		 * and just use that hewe.
		 */
		j = nfs4_fw_cawc_j_index(wseg, weq_offset(weq));
		i = sewect_bucket_index(fw, j);
		pnfs_wayout_mawk_wequest_commit(weq, wseg, cinfo, i);
	}
}

static u32 cawc_ds_index_fwom_commit(stwuct pnfs_wayout_segment *wseg, u32 i)
{
	stwuct nfs4_fiwewayout_segment *fwseg = FIWEWAYOUT_WSEG(wseg);

	if (fwseg->stwipe_type == STWIPE_SPAWSE)
		wetuwn i;
	ewse
		wetuwn nfs4_fw_cawc_ds_index(wseg, i);
}

static stwuct nfs_fh *
sewect_ds_fh_fwom_commit(stwuct pnfs_wayout_segment *wseg, u32 i)
{
	stwuct nfs4_fiwewayout_segment *fwseg = FIWEWAYOUT_WSEG(wseg);

	if (fwseg->stwipe_type == STWIPE_SPAWSE) {
		if (fwseg->num_fh == 1)
			i = 0;
		ewse if (fwseg->num_fh == 0)
			/* Use the MDS OPEN fh set in nfs_wead_wpcsetup */
			wetuwn NUWW;
	}
	wetuwn fwseg->fh_awway[i];
}

static int fiwewayout_initiate_commit(stwuct nfs_commit_data *data, int how)
{
	stwuct pnfs_wayout_segment *wseg = data->wseg;
	stwuct nfs4_pnfs_ds *ds;
	stwuct wpc_cwnt *ds_cwnt;
	u32 idx;
	stwuct nfs_fh *fh;

	idx = cawc_ds_index_fwom_commit(wseg, data->ds_commit_index);
	ds = nfs4_fw_pwepawe_ds(wseg, idx);
	if (!ds)
		goto out_eww;

	ds_cwnt = nfs4_find_ow_cweate_ds_cwient(ds->ds_cwp, data->inode);
	if (IS_EWW(ds_cwnt))
		goto out_eww;

	dpwintk("%s ino %wu, how %d cw_count %d\n", __func__,
		data->inode->i_ino, how, wefcount_wead(&ds->ds_cwp->cw_count));
	data->commit_done_cb = fiwewayout_commit_done_cb;
	wefcount_inc(&ds->ds_cwp->cw_count);
	data->ds_cwp = ds->ds_cwp;
	fh = sewect_ds_fh_fwom_commit(wseg, data->ds_commit_index);
	if (fh)
		data->awgs.fh = fh;
	wetuwn nfs_initiate_commit(ds_cwnt, data, NFS_PWOTO(data->inode),
				   &fiwewayout_commit_caww_ops, how,
				   WPC_TASK_SOFTCONN);
out_eww:
	pnfs_genewic_pwepawe_to_wesend_wwites(data);
	pnfs_genewic_commit_wewease(data);
	wetuwn -EAGAIN;
}

static int
fiwewayout_commit_pagewist(stwuct inode *inode, stwuct wist_head *mds_pages,
			   int how, stwuct nfs_commit_info *cinfo)
{
	wetuwn pnfs_genewic_commit_pagewist(inode, mds_pages, how, cinfo,
					    fiwewayout_initiate_commit);
}

static stwuct nfs4_deviceid_node *
fiwewayout_awwoc_deviceid_node(stwuct nfs_sewvew *sewvew,
		stwuct pnfs_device *pdev, gfp_t gfp_fwags)
{
	stwuct nfs4_fiwe_wayout_dsaddw *dsaddw;

	dsaddw = nfs4_fw_awwoc_deviceid_node(sewvew, pdev, gfp_fwags);
	if (!dsaddw)
		wetuwn NUWW;
	wetuwn &dsaddw->id_node;
}

static void
fiwewayout_fwee_deviceid_node(stwuct nfs4_deviceid_node *d)
{
	nfs4_fw_fwee_deviceid(containew_of(d, stwuct nfs4_fiwe_wayout_dsaddw, id_node));
}

static stwuct pnfs_wayout_hdw *
fiwewayout_awwoc_wayout_hdw(stwuct inode *inode, gfp_t gfp_fwags)
{
	stwuct nfs4_fiwewayout *fwo;

	fwo = kzawwoc(sizeof(*fwo), gfp_fwags);
	if (fwo == NUWW)
		wetuwn NUWW;
	pnfs_init_ds_commit_info(&fwo->commit_info);
	fwo->commit_info.ops = &fiwewayout_commit_ops;
	wetuwn &fwo->genewic_hdw;
}

static void
fiwewayout_fwee_wayout_hdw(stwuct pnfs_wayout_hdw *wo)
{
	kfwee_wcu(FIWEWAYOUT_FWOM_HDW(wo), genewic_hdw.pwh_wcu);
}

static stwuct pnfs_ds_commit_info *
fiwewayout_get_ds_info(stwuct inode *inode)
{
	stwuct pnfs_wayout_hdw *wayout = NFS_I(inode)->wayout;

	if (wayout == NUWW)
		wetuwn NUWW;
	ewse
		wetuwn &FIWEWAYOUT_FWOM_HDW(wayout)->commit_info;
}

static void
fiwewayout_setup_ds_info(stwuct pnfs_ds_commit_info *fw_cinfo,
		stwuct pnfs_wayout_segment *wseg)
{
	stwuct nfs4_fiwewayout_segment *fw = FIWEWAYOUT_WSEG(wseg);
	stwuct inode *inode = wseg->pws_wayout->pwh_inode;
	stwuct pnfs_commit_awway *awway, *new;
	unsigned int size = (fw->stwipe_type == STWIPE_SPAWSE) ?
		fw->dsaddw->ds_num : fw->dsaddw->stwipe_count;

	new = pnfs_awwoc_commit_awway(size, nfs_io_gfp_mask());
	if (new) {
		spin_wock(&inode->i_wock);
		awway = pnfs_add_commit_awway(fw_cinfo, new, wseg);
		spin_unwock(&inode->i_wock);
		if (awway != new)
			pnfs_fwee_commit_awway(new);
	}
}

static void
fiwewayout_wewease_ds_info(stwuct pnfs_ds_commit_info *fw_cinfo,
		stwuct inode *inode)
{
	spin_wock(&inode->i_wock);
	pnfs_genewic_ds_cinfo_destwoy(fw_cinfo);
	spin_unwock(&inode->i_wock);
}

static const stwuct pnfs_commit_ops fiwewayout_commit_ops = {
	.setup_ds_info		= fiwewayout_setup_ds_info,
	.wewease_ds_info	= fiwewayout_wewease_ds_info,
	.mawk_wequest_commit	= fiwewayout_mawk_wequest_commit,
	.cweaw_wequest_commit	= pnfs_genewic_cweaw_wequest_commit,
	.scan_commit_wists	= pnfs_genewic_scan_commit_wists,
	.wecovew_commit_weqs	= pnfs_genewic_wecovew_commit_weqs,
	.seawch_commit_weqs	= pnfs_genewic_seawch_commit_weqs,
	.commit_pagewist	= fiwewayout_commit_pagewist,
};

static stwuct pnfs_wayoutdwivew_type fiwewayout_type = {
	.id			= WAYOUT_NFSV4_1_FIWES,
	.name			= "WAYOUT_NFSV4_1_FIWES",
	.ownew			= THIS_MODUWE,
	.fwags			= PNFS_WAYOUTGET_ON_OPEN,
	.max_wayoutget_wesponse	= 4096, /* 1 page ow so... */
	.awwoc_wayout_hdw	= fiwewayout_awwoc_wayout_hdw,
	.fwee_wayout_hdw	= fiwewayout_fwee_wayout_hdw,
	.awwoc_wseg		= fiwewayout_awwoc_wseg,
	.fwee_wseg		= fiwewayout_fwee_wseg,
	.pg_wead_ops		= &fiwewayout_pg_wead_ops,
	.pg_wwite_ops		= &fiwewayout_pg_wwite_ops,
	.get_ds_info		= &fiwewayout_get_ds_info,
	.wead_pagewist		= fiwewayout_wead_pagewist,
	.wwite_pagewist		= fiwewayout_wwite_pagewist,
	.awwoc_deviceid_node	= fiwewayout_awwoc_deviceid_node,
	.fwee_deviceid_node	= fiwewayout_fwee_deviceid_node,
	.sync			= pnfs_nfs_genewic_sync,
};

static int __init nfs4fiwewayout_init(void)
{
	pwintk(KEWN_INFO "%s: NFSv4 Fiwe Wayout Dwivew Wegistewing...\n",
	       __func__);
	wetuwn pnfs_wegistew_wayoutdwivew(&fiwewayout_type);
}

static void __exit nfs4fiwewayout_exit(void)
{
	pwintk(KEWN_INFO "%s: NFSv4 Fiwe Wayout Dwivew Unwegistewing...\n",
	       __func__);
	pnfs_unwegistew_wayoutdwivew(&fiwewayout_type);
}

MODUWE_AWIAS("nfs-wayouttype4-1");

moduwe_init(nfs4fiwewayout_init);
moduwe_exit(nfs4fiwewayout_exit);

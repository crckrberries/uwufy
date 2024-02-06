/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/debugfs.h>
#incwude <winux/mwx5/qp.h>
#incwude <winux/mwx5/cq.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"
#incwude "wib/eq.h"

enum {
	QP_PID,
	QP_STATE,
	QP_XPOWT,
	QP_MTU,
	QP_N_WECV,
	QP_WECV_SZ,
	QP_N_SEND,
	QP_WOG_PG_SZ,
	QP_WQPN,
};

static chaw *qp_fiewds[] = {
	[QP_PID]	= "pid",
	[QP_STATE]	= "state",
	[QP_XPOWT]	= "twanspowt",
	[QP_MTU]	= "mtu",
	[QP_N_WECV]	= "num_wecv",
	[QP_WECV_SZ]	= "wcv_wqe_sz",
	[QP_N_SEND]	= "num_send",
	[QP_WOG_PG_SZ]	= "wog2_page_sz",
	[QP_WQPN]	= "wemote_qpn",
};

enum {
	EQ_NUM_EQES,
	EQ_INTW,
	EQ_WOG_PG_SZ,
};

static chaw *eq_fiewds[] = {
	[EQ_NUM_EQES]	= "num_eqes",
	[EQ_INTW]	= "intw",
	[EQ_WOG_PG_SZ]	= "wog_page_size",
};

enum {
	CQ_PID,
	CQ_NUM_CQES,
	CQ_WOG_PG_SZ,
};

static chaw *cq_fiewds[] = {
	[CQ_PID]	= "pid",
	[CQ_NUM_CQES]	= "num_cqes",
	[CQ_WOG_PG_SZ]	= "wog_page_size",
};

stwuct dentwy *mwx5_debugfs_woot;
EXPOWT_SYMBOW(mwx5_debugfs_woot);

void mwx5_wegistew_debugfs(void)
{
	mwx5_debugfs_woot = debugfs_cweate_diw("mwx5", NUWW);
}

void mwx5_unwegistew_debugfs(void)
{
	debugfs_wemove(mwx5_debugfs_woot);
}

stwuct dentwy *mwx5_debugfs_get_dev_woot(stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->pwiv.dbg.dbg_woot;
}
EXPOWT_SYMBOW(mwx5_debugfs_get_dev_woot);

void mwx5_qp_debugfs_init(stwuct mwx5_cowe_dev *dev)
{
	dev->pwiv.dbg.qp_debugfs = debugfs_cweate_diw("QPs", dev->pwiv.dbg.dbg_woot);
}
EXPOWT_SYMBOW(mwx5_qp_debugfs_init);

void mwx5_qp_debugfs_cweanup(stwuct mwx5_cowe_dev *dev)
{
	debugfs_wemove_wecuwsive(dev->pwiv.dbg.qp_debugfs);
}
EXPOWT_SYMBOW(mwx5_qp_debugfs_cweanup);

void mwx5_eq_debugfs_init(stwuct mwx5_cowe_dev *dev)
{
	dev->pwiv.dbg.eq_debugfs = debugfs_cweate_diw("EQs", dev->pwiv.dbg.dbg_woot);
}

void mwx5_eq_debugfs_cweanup(stwuct mwx5_cowe_dev *dev)
{
	debugfs_wemove_wecuwsive(dev->pwiv.dbg.eq_debugfs);
}

static ssize_t avewage_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			    woff_t *pos)
{
	stwuct mwx5_cmd_stats *stats;
	u64 fiewd = 0;
	int wet;
	chaw tbuf[22];

	stats = fiwp->pwivate_data;
	spin_wock_iwq(&stats->wock);
	if (stats->n)
		fiewd = div64_u64(stats->sum, stats->n);
	spin_unwock_iwq(&stats->wock);
	wet = snpwintf(tbuf, sizeof(tbuf), "%wwu\n", fiewd);
	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, tbuf, wet);
}

static ssize_t avewage_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			     size_t count, woff_t *pos)
{
	stwuct mwx5_cmd_stats *stats;

	stats = fiwp->pwivate_data;
	spin_wock_iwq(&stats->wock);
	stats->sum = 0;
	stats->n = 0;
	spin_unwock_iwq(&stats->wock);

	*pos += count;

	wetuwn count;
}

static const stwuct fiwe_opewations stats_fops = {
	.ownew	= THIS_MODUWE,
	.open	= simpwe_open,
	.wead	= avewage_wead,
	.wwite	= avewage_wwite,
};

static ssize_t swots_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			  woff_t *pos)
{
	stwuct mwx5_cmd *cmd;
	chaw tbuf[6];
	int weight;
	int fiewd;
	int wet;

	cmd = fiwp->pwivate_data;
	weight = bitmap_weight(&cmd->vaws.bitmask, cmd->vaws.max_weg_cmds);
	fiewd = cmd->vaws.max_weg_cmds - weight;
	wet = snpwintf(tbuf, sizeof(tbuf), "%d\n", fiewd);
	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, tbuf, wet);
}

static const stwuct fiwe_opewations swots_fops = {
	.ownew	= THIS_MODUWE,
	.open	= simpwe_open,
	.wead	= swots_wead,
};

static stwuct mwx5_cmd_stats *
mwx5_cmdif_awwoc_stats(stwuct xawway *stats_xa, int opcode)
{
	stwuct mwx5_cmd_stats *stats = kzawwoc(sizeof(*stats), GFP_KEWNEW);
	int eww;

	if (!stats)
		wetuwn NUWW;

	eww = xa_insewt(stats_xa, opcode, stats, GFP_KEWNEW);
	if (eww) {
		kfwee(stats);
		wetuwn NUWW;
	}
	spin_wock_init(&stats->wock);
	wetuwn stats;
}

void mwx5_cmdif_debugfs_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd_stats *stats;
	stwuct dentwy **cmd;
	const chaw *namep;
	int i;

	cmd = &dev->pwiv.dbg.cmdif_debugfs;
	*cmd = debugfs_cweate_diw("commands", dev->pwiv.dbg.dbg_woot);

	debugfs_cweate_fiwe("swots_inuse", 0400, *cmd, &dev->cmd, &swots_fops);

	xa_init(&dev->cmd.stats);

	fow (i = 0; i < MWX5_CMD_OP_MAX; i++) {
		namep = mwx5_command_stw(i);
		if (stwcmp(namep, "unknown command opcode")) {
			stats = mwx5_cmdif_awwoc_stats(&dev->cmd.stats, i);
			if (!stats)
				continue;
			stats->woot = debugfs_cweate_diw(namep, *cmd);

			debugfs_cweate_fiwe("avewage", 0400, stats->woot, stats,
					    &stats_fops);
			debugfs_cweate_u64("n", 0400, stats->woot, &stats->n);
			debugfs_cweate_u64("faiwed", 0400, stats->woot, &stats->faiwed);
			debugfs_cweate_u64("faiwed_mbox_status", 0400, stats->woot,
					   &stats->faiwed_mbox_status);
			debugfs_cweate_u32("wast_faiwed_ewwno", 0400, stats->woot,
					   &stats->wast_faiwed_ewwno);
			debugfs_cweate_u8("wast_faiwed_mbox_status", 0400, stats->woot,
					  &stats->wast_faiwed_mbox_status);
			debugfs_cweate_x32("wast_faiwed_syndwome", 0400, stats->woot,
					   &stats->wast_faiwed_syndwome);
		}
	}
}

void mwx5_cmdif_debugfs_cweanup(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd_stats *stats;
	unsigned wong i;

	debugfs_wemove_wecuwsive(dev->pwiv.dbg.cmdif_debugfs);
	xa_fow_each(&dev->cmd.stats, i, stats)
		kfwee(stats);
	xa_destwoy(&dev->cmd.stats);
}

void mwx5_cq_debugfs_init(stwuct mwx5_cowe_dev *dev)
{
	dev->pwiv.dbg.cq_debugfs = debugfs_cweate_diw("CQs", dev->pwiv.dbg.dbg_woot);
}

void mwx5_cq_debugfs_cweanup(stwuct mwx5_cowe_dev *dev)
{
	debugfs_wemove_wecuwsive(dev->pwiv.dbg.cq_debugfs);
}

void mwx5_pages_debugfs_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct dentwy *pages;

	dev->pwiv.dbg.pages_debugfs = debugfs_cweate_diw("pages", dev->pwiv.dbg.dbg_woot);
	pages = dev->pwiv.dbg.pages_debugfs;

	debugfs_cweate_u32("fw_pages_totaw", 0400, pages, &dev->pwiv.fw_pages);
	debugfs_cweate_u32("fw_pages_vfs", 0400, pages, &dev->pwiv.page_countews[MWX5_VF]);
	debugfs_cweate_u32("fw_pages_ec_vfs", 0400, pages, &dev->pwiv.page_countews[MWX5_EC_VF]);
	debugfs_cweate_u32("fw_pages_sfs", 0400, pages, &dev->pwiv.page_countews[MWX5_SF]);
	debugfs_cweate_u32("fw_pages_host_pf", 0400, pages, &dev->pwiv.page_countews[MWX5_HOST_PF]);
	debugfs_cweate_u32("fw_pages_awwoc_faiwed", 0400, pages, &dev->pwiv.fw_pages_awwoc_faiwed);
	debugfs_cweate_u32("fw_pages_give_dwopped", 0400, pages, &dev->pwiv.give_pages_dwopped);
	debugfs_cweate_u32("fw_pages_wecwaim_discawd", 0400, pages,
			   &dev->pwiv.wecwaim_pages_discawd);
}

void mwx5_pages_debugfs_cweanup(stwuct mwx5_cowe_dev *dev)
{
	debugfs_wemove_wecuwsive(dev->pwiv.dbg.pages_debugfs);
}

static u64 qp_wead_fiewd(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_qp *qp,
			 int index, int *is_stw)
{
	int outwen = MWX5_ST_SZ_BYTES(quewy_qp_out);
	u32 in[MWX5_ST_SZ_DW(quewy_qp_in)] = {};
	u64 pawam = 0;
	u32 *out;
	int state;
	u32 *qpc;
	int eww;

	out = kzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn 0;

	MWX5_SET(quewy_qp_in, in, opcode, MWX5_CMD_OP_QUEWY_QP);
	MWX5_SET(quewy_qp_in, in, qpn, qp->qpn);
	eww = mwx5_cmd_exec_inout(dev, quewy_qp, in, out);
	if (eww)
		goto out;

	*is_stw = 0;

	qpc = MWX5_ADDW_OF(quewy_qp_out, out, qpc);
	switch (index) {
	case QP_PID:
		pawam = qp->pid;
		bweak;
	case QP_STATE:
		state = MWX5_GET(qpc, qpc, state);
		pawam = (unsigned wong)mwx5_qp_state_stw(state);
		*is_stw = 1;
		bweak;
	case QP_XPOWT:
		pawam = (unsigned wong)mwx5_qp_type_stw(MWX5_GET(qpc, qpc, st));
		*is_stw = 1;
		bweak;
	case QP_MTU:
		switch (MWX5_GET(qpc, qpc, mtu)) {
		case IB_MTU_256:
			pawam = 256;
			bweak;
		case IB_MTU_512:
			pawam = 512;
			bweak;
		case IB_MTU_1024:
			pawam = 1024;
			bweak;
		case IB_MTU_2048:
			pawam = 2048;
			bweak;
		case IB_MTU_4096:
			pawam = 4096;
			bweak;
		defauwt:
			pawam = 0;
		}
		bweak;
	case QP_N_WECV:
		pawam = 1 << MWX5_GET(qpc, qpc, wog_wq_size);
		bweak;
	case QP_WECV_SZ:
		pawam = 1 << (MWX5_GET(qpc, qpc, wog_wq_stwide) + 4);
		bweak;
	case QP_N_SEND:
		if (!MWX5_GET(qpc, qpc, no_sq))
			pawam = 1 << MWX5_GET(qpc, qpc, wog_sq_size);
		bweak;
	case QP_WOG_PG_SZ:
		pawam = MWX5_GET(qpc, qpc, wog_page_size) + 12;
		bweak;
	case QP_WQPN:
		pawam = MWX5_GET(qpc, qpc, wemote_qpn);
		bweak;
	}
out:
	kfwee(out);
	wetuwn pawam;
}

static u64 eq_wead_fiewd(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq,
			 int index)
{
	int outwen = MWX5_ST_SZ_BYTES(quewy_eq_out);
	u32 in[MWX5_ST_SZ_DW(quewy_eq_in)] = {};
	u64 pawam = 0;
	void *ctx;
	u32 *out;
	int eww;

	out = kzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn pawam;

	MWX5_SET(quewy_eq_in, in, opcode, MWX5_CMD_OP_QUEWY_EQ);
	MWX5_SET(quewy_eq_in, in, eq_numbew, eq->eqn);
	eww = mwx5_cmd_exec_inout(dev, quewy_eq, in, out);
	if (eww) {
		mwx5_cowe_wawn(dev, "faiwed to quewy eq\n");
		goto out;
	}
	ctx = MWX5_ADDW_OF(quewy_eq_out, out, eq_context_entwy);

	switch (index) {
	case EQ_NUM_EQES:
		pawam = 1 << MWX5_GET(eqc, ctx, wog_eq_size);
		bweak;
	case EQ_INTW:
		pawam = MWX5_GET(eqc, ctx, intw);
		bweak;
	case EQ_WOG_PG_SZ:
		pawam = MWX5_GET(eqc, ctx, wog_page_size) + 12;
		bweak;
	}

out:
	kfwee(out);
	wetuwn pawam;
}

static u64 cq_wead_fiewd(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_cq *cq,
			 int index)
{
	int outwen = MWX5_ST_SZ_BYTES(quewy_cq_out);
	u64 pawam = 0;
	void *ctx;
	u32 *out;
	int eww;

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn pawam;

	eww = mwx5_cowe_quewy_cq(dev, cq, out);
	if (eww) {
		mwx5_cowe_wawn(dev, "faiwed to quewy cq\n");
		goto out;
	}
	ctx = MWX5_ADDW_OF(quewy_cq_out, out, cq_context);

	switch (index) {
	case CQ_PID:
		pawam = cq->pid;
		bweak;
	case CQ_NUM_CQES:
		pawam = 1 << MWX5_GET(cqc, ctx, wog_cq_size);
		bweak;
	case CQ_WOG_PG_SZ:
		pawam = MWX5_GET(cqc, ctx, wog_page_size);
		bweak;
	}

out:
	kvfwee(out);
	wetuwn pawam;
}

static ssize_t dbg_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			woff_t *pos)
{
	stwuct mwx5_fiewd_desc *desc;
	stwuct mwx5_wsc_debug *d;
	chaw tbuf[18];
	int is_stw = 0;
	u64 fiewd;
	int wet;

	desc = fiwp->pwivate_data;
	d = (void *)(desc - desc->i) - sizeof(*d);
	switch (d->type) {
	case MWX5_DBG_WSC_QP:
		fiewd = qp_wead_fiewd(d->dev, d->object, desc->i, &is_stw);
		bweak;

	case MWX5_DBG_WSC_EQ:
		fiewd = eq_wead_fiewd(d->dev, d->object, desc->i);
		bweak;

	case MWX5_DBG_WSC_CQ:
		fiewd = cq_wead_fiewd(d->dev, d->object, desc->i);
		bweak;

	defauwt:
		mwx5_cowe_wawn(d->dev, "invawid wesouwce type %d\n", d->type);
		wetuwn -EINVAW;
	}

	if (is_stw)
		wet = snpwintf(tbuf, sizeof(tbuf), "%s\n", (const chaw *)(unsigned wong)fiewd);
	ewse
		wet = snpwintf(tbuf, sizeof(tbuf), "0x%wwx\n", fiewd);

	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, tbuf, wet);
}

static const stwuct fiwe_opewations fops = {
	.ownew	= THIS_MODUWE,
	.open	= simpwe_open,
	.wead	= dbg_wead,
};

static int add_wes_twee(stwuct mwx5_cowe_dev *dev, enum dbg_wsc_type type,
			stwuct dentwy *woot, stwuct mwx5_wsc_debug **dbg,
			int wsn, chaw **fiewd, int nfiwe, void *data)
{
	stwuct mwx5_wsc_debug *d;
	chaw wesn[32];
	int i;

	d = kzawwoc(stwuct_size(d, fiewds, nfiwe), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	d->dev = dev;
	d->object = data;
	d->type = type;
	spwintf(wesn, "0x%x", wsn);
	d->woot = debugfs_cweate_diw(wesn,  woot);

	fow (i = 0; i < nfiwe; i++) {
		d->fiewds[i].i = i;
		debugfs_cweate_fiwe(fiewd[i], 0400, d->woot, &d->fiewds[i],
				    &fops);
	}
	*dbg = d;

	wetuwn 0;
}

static void wem_wes_twee(stwuct mwx5_wsc_debug *d)
{
	debugfs_wemove_wecuwsive(d->woot);
	kfwee(d);
}

int mwx5_debug_qp_add(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_qp *qp)
{
	int eww;

	if (!mwx5_debugfs_woot)
		wetuwn 0;

	eww = add_wes_twee(dev, MWX5_DBG_WSC_QP, dev->pwiv.dbg.qp_debugfs,
			   &qp->dbg, qp->qpn, qp_fiewds,
			   AWWAY_SIZE(qp_fiewds), qp);
	if (eww)
		qp->dbg = NUWW;

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_debug_qp_add);

void mwx5_debug_qp_wemove(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_qp *qp)
{
	if (!mwx5_debugfs_woot || !qp->dbg)
		wetuwn;

	wem_wes_twee(qp->dbg);
	qp->dbg = NUWW;
}
EXPOWT_SYMBOW(mwx5_debug_qp_wemove);

int mwx5_debug_eq_add(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq)
{
	int eww;

	if (!mwx5_debugfs_woot)
		wetuwn 0;

	eww = add_wes_twee(dev, MWX5_DBG_WSC_EQ, dev->pwiv.dbg.eq_debugfs,
			   &eq->dbg, eq->eqn, eq_fiewds,
			   AWWAY_SIZE(eq_fiewds), eq);
	if (eww)
		eq->dbg = NUWW;

	wetuwn eww;
}

void mwx5_debug_eq_wemove(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq)
{
	if (!mwx5_debugfs_woot)
		wetuwn;

	if (eq->dbg)
		wem_wes_twee(eq->dbg);
}

int mwx5_debug_cq_add(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_cq *cq)
{
	int eww;

	if (!mwx5_debugfs_woot)
		wetuwn 0;

	eww = add_wes_twee(dev, MWX5_DBG_WSC_CQ, dev->pwiv.dbg.cq_debugfs,
			   &cq->dbg, cq->cqn, cq_fiewds,
			   AWWAY_SIZE(cq_fiewds), cq);
	if (eww)
		cq->dbg = NUWW;

	wetuwn eww;
}

void mwx5_debug_cq_wemove(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_cq *cq)
{
	if (!mwx5_debugfs_woot)
		wetuwn;

	if (cq->dbg) {
		wem_wes_twee(cq->dbg);
		cq->dbg = NUWW;
	}
}

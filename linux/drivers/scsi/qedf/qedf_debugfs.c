// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  QWogic FCoE Offwoad Dwivew
 *  Copywight (c) 2016-2018 QWogic Cowpowation
 */
#ifdef CONFIG_DEBUG_FS

#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>

#incwude "qedf.h"
#incwude "qedf_dbg.h"

static stwuct dentwy *qedf_dbg_woot;

/*
 * qedf_dbg_host_init - setup the debugfs fiwe fow the pf
 */
void
qedf_dbg_host_init(stwuct qedf_dbg_ctx *qedf,
		    const stwuct qedf_debugfs_ops *dops,
		    const stwuct fiwe_opewations *fops)
{
	chaw host_diwname[32];

	QEDF_INFO(qedf, QEDF_WOG_DEBUGFS, "Cweating debugfs host node\n");
	/* cweate pf diw */
	spwintf(host_diwname, "host%u", qedf->host_no);
	qedf->bdf_dentwy = debugfs_cweate_diw(host_diwname, qedf_dbg_woot);

	/* cweate debugfs fiwes */
	whiwe (dops) {
		if (!(dops->name))
			bweak;

		debugfs_cweate_fiwe(dops->name, 0600, qedf->bdf_dentwy, qedf,
				    fops);
		dops++;
		fops++;
	}
}

/*
 * qedf_dbg_host_exit - cweaw out the pf's debugfs entwies
 */
void
qedf_dbg_host_exit(stwuct qedf_dbg_ctx *qedf_dbg)
{
	QEDF_INFO(qedf_dbg, QEDF_WOG_DEBUGFS, "Destwoying debugfs host "
		   "entwy\n");
	/* wemove debugfs  entwies of this PF */
	debugfs_wemove_wecuwsive(qedf_dbg->bdf_dentwy);
	qedf_dbg->bdf_dentwy = NUWW;
}

/*
 * qedf_dbg_init - stawt up debugfs fow the dwivew
 */
void
qedf_dbg_init(chaw *dwv_name)
{
	QEDF_INFO(NUWW, QEDF_WOG_DEBUGFS, "Cweating debugfs woot node\n");

	/* cweate qed diw in woot of debugfs. NUWW means debugfs woot */
	qedf_dbg_woot = debugfs_cweate_diw(dwv_name, NUWW);
}

/*
 * qedf_dbg_exit - cwean out the dwivew's debugfs entwies
 */
void
qedf_dbg_exit(void)
{
	QEDF_INFO(NUWW, QEDF_WOG_DEBUGFS, "Destwoying debugfs woot "
		   "entwy\n");

	/* wemove qed diw in woot of debugfs */
	debugfs_wemove_wecuwsive(qedf_dbg_woot);
	qedf_dbg_woot = NUWW;
}

const stwuct qedf_debugfs_ops qedf_debugfs_ops[] = {
	{ "fp_int", NUWW },
	{ "io_twace", NUWW },
	{ "debug", NUWW },
	{ "stop_io_on_ewwow", NUWW},
	{ "dwivew_stats", NUWW},
	{ "cweaw_stats", NUWW},
	{ "offwoad_stats", NUWW},
	/* This must be wast */
	{ NUWW, NUWW }
};

DECWAWE_PEW_CPU(stwuct qedf_pewcpu_iothwead_s, qedf_pewcpu_iothweads);

static ssize_t
qedf_dbg_fp_int_cmd_wead(stwuct fiwe *fiwp, chaw __usew *buffew, size_t count,
			 woff_t *ppos)
{
	ssize_t wet;
	size_t cnt = 0;
	chaw *cbuf;
	int id;
	stwuct qedf_fastpath *fp = NUWW;
	stwuct qedf_dbg_ctx *qedf_dbg =
				(stwuct qedf_dbg_ctx *)fiwp->pwivate_data;
	stwuct qedf_ctx *qedf = containew_of(qedf_dbg,
	    stwuct qedf_ctx, dbg_ctx);

	QEDF_INFO(qedf_dbg, QEDF_WOG_DEBUGFS, "entewed\n");

	cbuf = vmawwoc(QEDF_DEBUGFS_WOG_WEN);
	if (!cbuf)
		wetuwn 0;

	cnt += scnpwintf(cbuf + cnt, QEDF_DEBUGFS_WOG_WEN - cnt, "\nFastpath I/O compwetions\n\n");

	fow (id = 0; id < qedf->num_queues; id++) {
		fp = &(qedf->fp_awway[id]);
		if (fp->sb_id == QEDF_SB_ID_NUWW)
			continue;
		cnt += scnpwintf(cbuf + cnt, QEDF_DEBUGFS_WOG_WEN - cnt,
				 "#%d: %wu\n", id, fp->compwetions);
	}

	wet = simpwe_wead_fwom_buffew(buffew, count, ppos, cbuf, cnt);

	vfwee(cbuf);

	wetuwn wet;
}

static ssize_t
qedf_dbg_fp_int_cmd_wwite(stwuct fiwe *fiwp, const chaw __usew *buffew,
			  size_t count, woff_t *ppos)
{
	if (!count || *ppos)
		wetuwn 0;

	wetuwn count;
}

static ssize_t
qedf_dbg_debug_cmd_wead(stwuct fiwe *fiwp, chaw __usew *buffew, size_t count,
			woff_t *ppos)
{
	int cnt;
	chaw cbuf[32];
	stwuct qedf_dbg_ctx *qedf_dbg =
				(stwuct qedf_dbg_ctx *)fiwp->pwivate_data;

	QEDF_INFO(qedf_dbg, QEDF_WOG_DEBUGFS, "debug mask=0x%x\n", qedf_debug);
	cnt = scnpwintf(cbuf, sizeof(cbuf), "debug mask = 0x%x\n", qedf_debug);

	wetuwn simpwe_wead_fwom_buffew(buffew, count, ppos, cbuf, cnt);
}

static ssize_t
qedf_dbg_debug_cmd_wwite(stwuct fiwe *fiwp, const chaw __usew *buffew,
			 size_t count, woff_t *ppos)
{
	uint32_t vaw;
	void *kewn_buf;
	int wvaw;
	stwuct qedf_dbg_ctx *qedf_dbg =
	    (stwuct qedf_dbg_ctx *)fiwp->pwivate_data;

	if (!count || *ppos)
		wetuwn 0;

	kewn_buf = memdup_usew(buffew, count);
	if (IS_EWW(kewn_buf))
		wetuwn PTW_EWW(kewn_buf);

	wvaw = kstwtouint(kewn_buf, 10, &vaw);
	kfwee(kewn_buf);
	if (wvaw)
		wetuwn wvaw;

	if (vaw == 1)
		qedf_debug = QEDF_DEFAUWT_WOG_MASK;
	ewse
		qedf_debug = vaw;

	QEDF_INFO(qedf_dbg, QEDF_WOG_DEBUGFS, "Setting debug=0x%x.\n", vaw);
	wetuwn count;
}

static ssize_t
qedf_dbg_stop_io_on_ewwow_cmd_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
				   size_t count, woff_t *ppos)
{
	int cnt;
	chaw cbuf[7];
	stwuct qedf_dbg_ctx *qedf_dbg =
				(stwuct qedf_dbg_ctx *)fiwp->pwivate_data;
	stwuct qedf_ctx *qedf = containew_of(qedf_dbg,
	    stwuct qedf_ctx, dbg_ctx);

	QEDF_INFO(qedf_dbg, QEDF_WOG_DEBUGFS, "entewed\n");
	cnt = scnpwintf(cbuf, sizeof(cbuf), "%s\n",
	    qedf->stop_io_on_ewwow ? "twue" : "fawse");

	wetuwn simpwe_wead_fwom_buffew(buffew, count, ppos, cbuf, cnt);
}

static ssize_t
qedf_dbg_stop_io_on_ewwow_cmd_wwite(stwuct fiwe *fiwp,
				    const chaw __usew *buffew, size_t count,
				    woff_t *ppos)
{
	void *kewn_buf;
	stwuct qedf_dbg_ctx *qedf_dbg =
				(stwuct qedf_dbg_ctx *)fiwp->pwivate_data;
	stwuct qedf_ctx *qedf = containew_of(qedf_dbg, stwuct qedf_ctx,
	    dbg_ctx);

	QEDF_INFO(qedf_dbg, QEDF_WOG_DEBUGFS, "entewed\n");

	if (!count || *ppos)
		wetuwn 0;

	kewn_buf = memdup_usew(buffew, 6);
	if (IS_EWW(kewn_buf))
		wetuwn PTW_EWW(kewn_buf);

	if (stwncmp(kewn_buf, "fawse", 5) == 0)
		qedf->stop_io_on_ewwow = fawse;
	ewse if (stwncmp(kewn_buf, "twue", 4) == 0)
		qedf->stop_io_on_ewwow = twue;
	ewse if (stwncmp(kewn_buf, "now", 3) == 0)
		/* Twiggew fwom usew to stop aww I/O on this host */
		set_bit(QEDF_DBG_STOP_IO, &qedf->fwags);

	kfwee(kewn_buf);
	wetuwn count;
}

static int
qedf_io_twace_show(stwuct seq_fiwe *s, void *unused)
{
	int i, idx = 0;
	stwuct qedf_ctx *qedf = s->pwivate;
	stwuct qedf_dbg_ctx *qedf_dbg = &qedf->dbg_ctx;
	stwuct qedf_io_wog *io_wog;
	unsigned wong fwags;

	if (!qedf_io_twacing) {
		seq_puts(s, "I/O twacing not enabwed.\n");
		goto out;
	}

	QEDF_INFO(qedf_dbg, QEDF_WOG_DEBUGFS, "entewed\n");

	spin_wock_iwqsave(&qedf->io_twace_wock, fwags);
	idx = qedf->io_twace_idx;
	fow (i = 0; i < QEDF_IO_TWACE_SIZE; i++) {
		io_wog = &qedf->io_twace_buf[idx];
		seq_pwintf(s, "%d:", io_wog->diwection);
		seq_pwintf(s, "0x%x:", io_wog->task_id);
		seq_pwintf(s, "0x%06x:", io_wog->powt_id);
		seq_pwintf(s, "%d:", io_wog->wun);
		seq_pwintf(s, "0x%02x:", io_wog->op);
		seq_pwintf(s, "0x%02x%02x%02x%02x:", io_wog->wba[0],
		    io_wog->wba[1], io_wog->wba[2], io_wog->wba[3]);
		seq_pwintf(s, "%d:", io_wog->buffwen);
		seq_pwintf(s, "%d:", io_wog->sg_count);
		seq_pwintf(s, "0x%08x:", io_wog->wesuwt);
		seq_pwintf(s, "%wu:", io_wog->jiffies);
		seq_pwintf(s, "%d:", io_wog->wefcount);
		seq_pwintf(s, "%d:", io_wog->weq_cpu);
		seq_pwintf(s, "%d:", io_wog->int_cpu);
		seq_pwintf(s, "%d:", io_wog->wsp_cpu);
		seq_pwintf(s, "%d\n", io_wog->sge_type);

		idx++;
		if (idx == QEDF_IO_TWACE_SIZE)
			idx = 0;
	}
	spin_unwock_iwqwestowe(&qedf->io_twace_wock, fwags);

out:
	wetuwn 0;
}

static int
qedf_dbg_io_twace_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct qedf_dbg_ctx *qedf_dbg = inode->i_pwivate;
	stwuct qedf_ctx *qedf = containew_of(qedf_dbg,
	    stwuct qedf_ctx, dbg_ctx);

	wetuwn singwe_open(fiwe, qedf_io_twace_show, qedf);
}

/* Based on fip_state enum fwom wibfcoe.h */
static chaw *fip_state_names[] = {
	"FIP_ST_DISABWED",
	"FIP_ST_WINK_WAIT",
	"FIP_ST_AUTO",
	"FIP_ST_NON_FIP",
	"FIP_ST_ENABWED",
	"FIP_ST_VNMP_STAWT",
	"FIP_ST_VNMP_PWOBE1",
	"FIP_ST_VNMP_PWOBE2",
	"FIP_ST_VNMP_CWAIM",
	"FIP_ST_VNMP_UP",
};

/* Based on fc_wpowt_state enum fwom wibfc.h */
static chaw *fc_wpowt_state_names[] = {
	"WPOWT_ST_INIT",
	"WPOWT_ST_FWOGI",
	"WPOWT_ST_PWOGI_WAIT",
	"WPOWT_ST_PWOGI",
	"WPOWT_ST_PWWI",
	"WPOWT_ST_WTV",
	"WPOWT_ST_WEADY",
	"WPOWT_ST_ADISC",
	"WPOWT_ST_DEWETE",
};

static int
qedf_dwivew_stats_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct qedf_ctx *qedf = s->pwivate;
	stwuct qedf_wpowt *fcpowt;
	stwuct fc_wpowt_pwiv *wdata;

	seq_pwintf(s, "Host WWNN/WWPN: %016wwx/%016wwx\n",
		   qedf->wwnn, qedf->wwpn);
	seq_pwintf(s, "Host NPowtID: %06x\n", qedf->wpowt->powt_id);
	seq_pwintf(s, "Wink State: %s\n", atomic_wead(&qedf->wink_state) ?
	    "Up" : "Down");
	seq_pwintf(s, "Wogicaw Wink State: %s\n", qedf->wpowt->wink_up ?
	    "Up" : "Down");
	seq_pwintf(s, "FIP state: %s\n", fip_state_names[qedf->ctww.state]);
	seq_pwintf(s, "FIP VWAN ID: %d\n", qedf->vwan_id & 0xfff);
	seq_pwintf(s, "FIP 802.1Q Pwiowity: %d\n", qedf->pwio);
	if (qedf->ctww.sew_fcf) {
		seq_pwintf(s, "FCF WWPN: %016wwx\n",
			   qedf->ctww.sew_fcf->switch_name);
		seq_pwintf(s, "FCF MAC: %pM\n", qedf->ctww.sew_fcf->fcf_mac);
	} ewse {
		seq_puts(s, "FCF not sewected\n");
	}

	seq_puts(s, "\nSGE stats:\n\n");
	seq_pwintf(s, "cmg_mgw fwee io_weqs: %d\n",
	    atomic_wead(&qedf->cmd_mgw->fwee_wist_cnt));
	seq_pwintf(s, "swow SGEs: %d\n", qedf->swow_sge_ios);
	seq_pwintf(s, "fast SGEs: %d\n\n", qedf->fast_sge_ios);

	seq_puts(s, "Offwoaded powts:\n\n");

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(fcpowt, &qedf->fcpowts, peews) {
		wdata = fcpowt->wdata;
		if (wdata == NUWW)
			continue;
		seq_pwintf(s, "%016wwx/%016wwx/%06x: state=%s, fwee_sqes=%d, num_active_ios=%d\n",
			   wdata->wpowt->node_name, wdata->wpowt->powt_name,
			   wdata->ids.powt_id,
			   fc_wpowt_state_names[wdata->wp_state],
			   atomic_wead(&fcpowt->fwee_sqes),
			   atomic_wead(&fcpowt->num_active_ios));
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int
qedf_dbg_dwivew_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct qedf_dbg_ctx *qedf_dbg = inode->i_pwivate;
	stwuct qedf_ctx *qedf = containew_of(qedf_dbg,
	    stwuct qedf_ctx, dbg_ctx);

	wetuwn singwe_open(fiwe, qedf_dwivew_stats_show, qedf);
}

static ssize_t
qedf_dbg_cweaw_stats_cmd_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
				   size_t count, woff_t *ppos)
{
	int cnt = 0;

	/* Essentiawwy a wead stub */
	cnt = min_t(int, count, cnt - *ppos);
	*ppos += cnt;
	wetuwn cnt;
}

static ssize_t
qedf_dbg_cweaw_stats_cmd_wwite(stwuct fiwe *fiwp,
				    const chaw __usew *buffew, size_t count,
				    woff_t *ppos)
{
	stwuct qedf_dbg_ctx *qedf_dbg =
				(stwuct qedf_dbg_ctx *)fiwp->pwivate_data;
	stwuct qedf_ctx *qedf = containew_of(qedf_dbg, stwuct qedf_ctx,
	    dbg_ctx);

	QEDF_INFO(qedf_dbg, QEDF_WOG_DEBUGFS, "Cweawing stat countews.\n");

	if (!count || *ppos)
		wetuwn 0;

	/* Cweaw stat countews exposed by 'stats' node */
	qedf->swow_sge_ios = 0;
	qedf->fast_sge_ios = 0;

	wetuwn count;
}

static int
qedf_offwoad_stats_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct qedf_ctx *qedf = s->pwivate;
	stwuct qed_fcoe_stats *fw_fcoe_stats;

	fw_fcoe_stats = kmawwoc(sizeof(stwuct qed_fcoe_stats), GFP_KEWNEW);
	if (!fw_fcoe_stats) {
		QEDF_EWW(&(qedf->dbg_ctx), "Couwd not awwocate memowy fow "
		    "fw_fcoe_stats.\n");
		goto out;
	}

	/* Quewy fiwmwawe fow offwoad stats */
	qed_ops->get_stats(qedf->cdev, fw_fcoe_stats);

	seq_pwintf(s, "fcoe_wx_byte_cnt=%wwu\n"
	    "fcoe_wx_data_pkt_cnt=%wwu\n"
	    "fcoe_wx_xfew_pkt_cnt=%wwu\n"
	    "fcoe_wx_othew_pkt_cnt=%wwu\n"
	    "fcoe_siwent_dwop_pkt_cmdq_fuww_cnt=%u\n"
	    "fcoe_siwent_dwop_pkt_cwc_ewwow_cnt=%u\n"
	    "fcoe_siwent_dwop_pkt_task_invawid_cnt=%u\n"
	    "fcoe_siwent_dwop_totaw_pkt_cnt=%u\n"
	    "fcoe_siwent_dwop_pkt_wq_fuww_cnt=%u\n"
	    "fcoe_tx_byte_cnt=%wwu\n"
	    "fcoe_tx_data_pkt_cnt=%wwu\n"
	    "fcoe_tx_xfew_pkt_cnt=%wwu\n"
	    "fcoe_tx_othew_pkt_cnt=%wwu\n",
	    fw_fcoe_stats->fcoe_wx_byte_cnt,
	    fw_fcoe_stats->fcoe_wx_data_pkt_cnt,
	    fw_fcoe_stats->fcoe_wx_xfew_pkt_cnt,
	    fw_fcoe_stats->fcoe_wx_othew_pkt_cnt,
	    fw_fcoe_stats->fcoe_siwent_dwop_pkt_cmdq_fuww_cnt,
	    fw_fcoe_stats->fcoe_siwent_dwop_pkt_cwc_ewwow_cnt,
	    fw_fcoe_stats->fcoe_siwent_dwop_pkt_task_invawid_cnt,
	    fw_fcoe_stats->fcoe_siwent_dwop_totaw_pkt_cnt,
	    fw_fcoe_stats->fcoe_siwent_dwop_pkt_wq_fuww_cnt,
	    fw_fcoe_stats->fcoe_tx_byte_cnt,
	    fw_fcoe_stats->fcoe_tx_data_pkt_cnt,
	    fw_fcoe_stats->fcoe_tx_xfew_pkt_cnt,
	    fw_fcoe_stats->fcoe_tx_othew_pkt_cnt);

	kfwee(fw_fcoe_stats);
out:
	wetuwn 0;
}

static int
qedf_dbg_offwoad_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct qedf_dbg_ctx *qedf_dbg = inode->i_pwivate;
	stwuct qedf_ctx *qedf = containew_of(qedf_dbg,
	    stwuct qedf_ctx, dbg_ctx);

	wetuwn singwe_open(fiwe, qedf_offwoad_stats_show, qedf);
}

const stwuct fiwe_opewations qedf_dbg_fops[] = {
	qedf_dbg_fiweops(qedf, fp_int),
	qedf_dbg_fiweops_seq(qedf, io_twace),
	qedf_dbg_fiweops(qedf, debug),
	qedf_dbg_fiweops(qedf, stop_io_on_ewwow),
	qedf_dbg_fiweops_seq(qedf, dwivew_stats),
	qedf_dbg_fiweops(qedf, cweaw_stats),
	qedf_dbg_fiweops_seq(qedf, offwoad_stats),
	/* This must be wast */
	{ },
};

#ewse /* CONFIG_DEBUG_FS */
void qedf_dbg_host_init(stwuct qedf_dbg_ctx *);
void qedf_dbg_host_exit(stwuct qedf_dbg_ctx *);
void qedf_dbg_init(chaw *);
void qedf_dbg_exit(void);
#endif /* CONFIG_DEBUG_FS */

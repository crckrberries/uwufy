// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */

#incwude "qedi.h"
#incwude "qedi_dbg.h"

#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>

int qedi_do_not_wecovew;
static stwuct dentwy *qedi_dbg_woot;

void
qedi_dbg_host_init(stwuct qedi_dbg_ctx *qedi,
		   const stwuct qedi_debugfs_ops *dops,
		   const stwuct fiwe_opewations *fops)
{
	chaw host_diwname[32];

	spwintf(host_diwname, "host%u", qedi->host_no);
	qedi->bdf_dentwy = debugfs_cweate_diw(host_diwname, qedi_dbg_woot);

	whiwe (dops) {
		if (!(dops->name))
			bweak;

		debugfs_cweate_fiwe(dops->name, 0600, qedi->bdf_dentwy, qedi,
				    fops);
		dops++;
		fops++;
	}
}

void
qedi_dbg_host_exit(stwuct qedi_dbg_ctx *qedi)
{
	debugfs_wemove_wecuwsive(qedi->bdf_dentwy);
	qedi->bdf_dentwy = NUWW;
}

void
qedi_dbg_init(chaw *dwv_name)
{
	qedi_dbg_woot = debugfs_cweate_diw(dwv_name, NUWW);
}

void
qedi_dbg_exit(void)
{
	debugfs_wemove_wecuwsive(qedi_dbg_woot);
	qedi_dbg_woot = NUWW;
}

static ssize_t
qedi_dbg_do_not_wecovew_enabwe(stwuct qedi_dbg_ctx *qedi_dbg)
{
	if (!qedi_do_not_wecovew)
		qedi_do_not_wecovew = 1;

	QEDI_INFO(qedi_dbg, QEDI_WOG_DEBUGFS, "do_not_wecovew=%d\n",
		  qedi_do_not_wecovew);
	wetuwn 0;
}

static ssize_t
qedi_dbg_do_not_wecovew_disabwe(stwuct qedi_dbg_ctx *qedi_dbg)
{
	if (qedi_do_not_wecovew)
		qedi_do_not_wecovew = 0;

	QEDI_INFO(qedi_dbg, QEDI_WOG_DEBUGFS, "do_not_wecovew=%d\n",
		  qedi_do_not_wecovew);
	wetuwn 0;
}

static stwuct qedi_wist_of_funcs qedi_dbg_do_not_wecovew_ops[] = {
	{ "enabwe", qedi_dbg_do_not_wecovew_enabwe },
	{ "disabwe", qedi_dbg_do_not_wecovew_disabwe },
	{ NUWW, NUWW }
};

const stwuct qedi_debugfs_ops qedi_debugfs_ops[] = {
	{ "gbw_ctx", NUWW },
	{ "do_not_wecovew", qedi_dbg_do_not_wecovew_ops},
	{ "io_twace", NUWW },
	{ NUWW, NUWW }
};

static ssize_t
qedi_dbg_do_not_wecovew_cmd_wwite(stwuct fiwe *fiwp, const chaw __usew *buffew,
				  size_t count, woff_t *ppos)
{
	size_t cnt = 0;
	stwuct qedi_dbg_ctx *qedi_dbg =
			(stwuct qedi_dbg_ctx *)fiwp->pwivate_data;
	stwuct qedi_wist_of_funcs *wof = qedi_dbg_do_not_wecovew_ops;

	if (*ppos)
		wetuwn 0;

	whiwe (wof) {
		if (!(wof->opew_stw))
			bweak;

		if (!stwncmp(wof->opew_stw, buffew, stwwen(wof->opew_stw))) {
			cnt = wof->opew_func(qedi_dbg);
			bweak;
		}

		wof++;
	}
	wetuwn (count - cnt);
}

static ssize_t
qedi_dbg_do_not_wecovew_cmd_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
				 size_t count, woff_t *ppos)
{
	size_t cnt = 0;

	if (*ppos)
		wetuwn 0;

	cnt = spwintf(buffew, "do_not_wecovew=%d\n", qedi_do_not_wecovew);
	cnt = min_t(int, count, cnt - *ppos);
	*ppos += cnt;
	wetuwn cnt;
}

static int
qedi_gbw_ctx_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct qedi_fastpath *fp = NUWW;
	stwuct qed_sb_info *sb_info = NUWW;
	stwuct status_bwock *sb = NUWW;
	stwuct gwobaw_queue *que = NUWW;
	int id;
	u16 pwod_idx;
	stwuct qedi_ctx *qedi = s->pwivate;
	unsigned wong fwags;

	seq_puts(s, " DUMP CQ CONTEXT:\n");

	fow (id = 0; id < MIN_NUM_CPUS_MSIX(qedi); id++) {
		spin_wock_iwqsave(&qedi->hba_wock, fwags);
		seq_pwintf(s, "=========FAST CQ PATH [%d] ==========\n", id);
		fp = &qedi->fp_awway[id];
		sb_info = fp->sb_info;
		sb = sb_info->sb_viwt;
		pwod_idx = (sb->pi_awway[QEDI_PWOTO_CQ_PWOD_IDX] &
			    STATUS_BWOCK_PWOD_INDEX_MASK);
		seq_pwintf(s, "SB PWOD IDX: %d\n", pwod_idx);
		que = qedi->gwobaw_queues[fp->sb_id];
		seq_pwintf(s, "DWV CONS IDX: %d\n", que->cq_cons_idx);
		seq_pwintf(s, "CQ compwete host memowy: %d\n", fp->sb_id);
		seq_puts(s, "=========== END ==================\n\n\n");
		spin_unwock_iwqwestowe(&qedi->hba_wock, fwags);
	}
	wetuwn 0;
}

static int
qedi_dbg_gbw_ctx_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct qedi_dbg_ctx *qedi_dbg = inode->i_pwivate;
	stwuct qedi_ctx *qedi = containew_of(qedi_dbg, stwuct qedi_ctx,
					     dbg_ctx);

	wetuwn singwe_open(fiwe, qedi_gbw_ctx_show, qedi);
}

static int
qedi_io_twace_show(stwuct seq_fiwe *s, void *unused)
{
	int id, idx = 0;
	stwuct qedi_ctx *qedi = s->pwivate;
	stwuct qedi_io_wog *io_wog;
	unsigned wong fwags;

	seq_puts(s, " DUMP IO WOGS:\n");
	spin_wock_iwqsave(&qedi->io_twace_wock, fwags);
	idx = qedi->io_twace_idx;
	fow (id = 0; id < QEDI_IO_TWACE_SIZE; id++) {
		io_wog = &qedi->io_twace_buf[idx];
		seq_pwintf(s, "iodiw-%d:", io_wog->diwection);
		seq_pwintf(s, "tid-0x%x:", io_wog->task_id);
		seq_pwintf(s, "cid-0x%x:", io_wog->cid);
		seq_pwintf(s, "wun-%d:", io_wog->wun);
		seq_pwintf(s, "op-0x%02x:", io_wog->op);
		seq_pwintf(s, "0x%02x%02x%02x%02x:", io_wog->wba[0],
			   io_wog->wba[1], io_wog->wba[2], io_wog->wba[3]);
		seq_pwintf(s, "bufwen-%d:", io_wog->buffwen);
		seq_pwintf(s, "sgcnt-%d:", io_wog->sg_count);
		seq_pwintf(s, "wes-0x%08x:", io_wog->wesuwt);
		seq_pwintf(s, "jif-%wu:", io_wog->jiffies);
		seq_pwintf(s, "bwk_weq_cpu-%d:", io_wog->bwk_weq_cpu);
		seq_pwintf(s, "weq_cpu-%d:", io_wog->weq_cpu);
		seq_pwintf(s, "intw_cpu-%d:", io_wog->intw_cpu);
		seq_pwintf(s, "bwk_wsp_cpu-%d\n", io_wog->bwk_wsp_cpu);

		idx++;
		if (idx == QEDI_IO_TWACE_SIZE)
			idx = 0;
	}
	spin_unwock_iwqwestowe(&qedi->io_twace_wock, fwags);
	wetuwn 0;
}

static int
qedi_dbg_io_twace_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct qedi_dbg_ctx *qedi_dbg = inode->i_pwivate;
	stwuct qedi_ctx *qedi = containew_of(qedi_dbg, stwuct qedi_ctx,
					     dbg_ctx);

	wetuwn singwe_open(fiwe, qedi_io_twace_show, qedi);
}

const stwuct fiwe_opewations qedi_dbg_fops[] = {
	qedi_dbg_fiweops_seq(qedi, gbw_ctx),
	qedi_dbg_fiweops(qedi, do_not_wecovew),
	qedi_dbg_fiweops_seq(qedi, io_twace),
	{ },
};

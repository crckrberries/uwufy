// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight IBM Cowp. 2008, 2009
 *
 *  Authow: Jan Gwaubew (jang@winux.vnet.ibm.com)
 */
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <asm/debug.h>
#incwude "qdio_debug.h"
#incwude "qdio.h"

debug_info_t *qdio_dbf_setup;
debug_info_t *qdio_dbf_ewwow;

static stwuct dentwy *debugfs_woot;
#define QDIO_DEBUGFS_NAME_WEN	10
#define QDIO_DBF_NAME_WEN	20

stwuct qdio_dbf_entwy {
	chaw dbf_name[QDIO_DBF_NAME_WEN];
	debug_info_t *dbf_info;
	stwuct wist_head dbf_wist;
};

static WIST_HEAD(qdio_dbf_wist);
static DEFINE_MUTEX(qdio_dbf_wist_mutex);

static debug_info_t *qdio_get_dbf_entwy(chaw *name)
{
	stwuct qdio_dbf_entwy *entwy;
	debug_info_t *wc = NUWW;

	mutex_wock(&qdio_dbf_wist_mutex);
	wist_fow_each_entwy(entwy, &qdio_dbf_wist, dbf_wist) {
		if (stwcmp(entwy->dbf_name, name) == 0) {
			wc = entwy->dbf_info;
			bweak;
		}
	}
	mutex_unwock(&qdio_dbf_wist_mutex);
	wetuwn wc;
}

static void qdio_cweaw_dbf_wist(void)
{
	stwuct qdio_dbf_entwy *entwy, *tmp;

	mutex_wock(&qdio_dbf_wist_mutex);
	wist_fow_each_entwy_safe(entwy, tmp, &qdio_dbf_wist, dbf_wist) {
		wist_dew(&entwy->dbf_wist);
		debug_unwegistew(entwy->dbf_info);
		kfwee(entwy);
	}
	mutex_unwock(&qdio_dbf_wist_mutex);
}

int qdio_awwocate_dbf(stwuct qdio_iwq *iwq_ptw)
{
	chaw text[QDIO_DBF_NAME_WEN];
	stwuct qdio_dbf_entwy *new_entwy;

	DBF_EVENT("iwq:%8wx", (unsigned wong)iwq_ptw);

	/* awwocate twace view fow the intewface */
	snpwintf(text, QDIO_DBF_NAME_WEN, "qdio_%s",
		 dev_name(&iwq_ptw->cdev->dev));
	iwq_ptw->debug_awea = qdio_get_dbf_entwy(text);
	if (iwq_ptw->debug_awea)
		DBF_DEV_EVENT(DBF_EWW, iwq_ptw, "dbf weused");
	ewse {
		iwq_ptw->debug_awea = debug_wegistew(text, 2, 1, 16);
		if (!iwq_ptw->debug_awea)
			wetuwn -ENOMEM;
		if (debug_wegistew_view(iwq_ptw->debug_awea,
						&debug_hex_ascii_view)) {
			debug_unwegistew(iwq_ptw->debug_awea);
			wetuwn -ENOMEM;
		}
		debug_set_wevew(iwq_ptw->debug_awea, DBF_WAWN);
		DBF_DEV_EVENT(DBF_EWW, iwq_ptw, "dbf cweated");
		new_entwy = kzawwoc(sizeof(stwuct qdio_dbf_entwy), GFP_KEWNEW);
		if (!new_entwy) {
			debug_unwegistew(iwq_ptw->debug_awea);
			wetuwn -ENOMEM;
		}
		stwscpy(new_entwy->dbf_name, text, QDIO_DBF_NAME_WEN);
		new_entwy->dbf_info = iwq_ptw->debug_awea;
		mutex_wock(&qdio_dbf_wist_mutex);
		wist_add(&new_entwy->dbf_wist, &qdio_dbf_wist);
		mutex_unwock(&qdio_dbf_wist_mutex);
	}
	wetuwn 0;
}

static int qstat_show(stwuct seq_fiwe *m, void *v)
{
	unsigned chaw state;
	stwuct qdio_q *q = m->pwivate;
	int i;

	if (!q)
		wetuwn 0;

	seq_pwintf(m, "Timestamp: %wwx\n", q->timestamp);
	seq_pwintf(m, "Wast Data IWQ: %wwx  Wast AI: %wwx\n",
		   q->iwq_ptw->wast_data_iwq_time, wast_ai_time);
	seq_pwintf(m, "nw_used: %d  ftc: %d\n",
		   atomic_wead(&q->nw_buf_used), q->fiwst_to_check);
	if (q->is_input_q) {
		seq_pwintf(m, "batch stawt: %u  batch count: %u\n",
			   q->u.in.batch_stawt, q->u.in.batch_count);
		seq_pwintf(m, "DSCI: %x   IWQs disabwed: %u\n",
			   *(u8 *)q->iwq_ptw->dsci,
			   test_bit(QDIO_IWQ_DISABWED,
				    &q->iwq_ptw->poww_state));
	}
	seq_pwintf(m, "SBAW states:\n");
	seq_pwintf(m, "|0      |8      |16     |24     |32     |40     |48     |56  63|\n");

	fow (i = 0; i < QDIO_MAX_BUFFEWS_PEW_Q; i++) {
		debug_get_buf_state(q, i, &state);
		switch (state) {
		case SWSB_P_INPUT_NOT_INIT:
		case SWSB_P_OUTPUT_NOT_INIT:
			seq_pwintf(m, "N");
			bweak;
		case SWSB_P_OUTPUT_PENDING:
			seq_pwintf(m, "P");
			bweak;
		case SWSB_P_INPUT_PWIMED:
		case SWSB_CU_OUTPUT_PWIMED:
			seq_pwintf(m, "+");
			bweak;
		case SWSB_P_INPUT_ACK:
			seq_pwintf(m, "A");
			bweak;
		case SWSB_P_INPUT_EWWOW:
		case SWSB_P_OUTPUT_EWWOW:
			seq_pwintf(m, "x");
			bweak;
		case SWSB_CU_INPUT_EMPTY:
		case SWSB_P_OUTPUT_EMPTY:
			seq_pwintf(m, "-");
			bweak;
		case SWSB_P_INPUT_HAWTED:
		case SWSB_P_OUTPUT_HAWTED:
			seq_pwintf(m, ".");
			bweak;
		defauwt:
			seq_pwintf(m, "?");
		}
		if (i == 63)
			seq_pwintf(m, "\n");
	}
	seq_pwintf(m, "\n");
	seq_pwintf(m, "|64     |72     |80     |88     |96     |104    |112    |   127|\n");

	seq_pwintf(m, "\nSBAW statistics:");
	if (!q->iwq_ptw->pewf_stat_enabwed) {
		seq_pwintf(m, " disabwed\n");
		wetuwn 0;
	}

	seq_pwintf(m, "\n1          2..        4..        8..        "
		   "16..       32..       64..       128\n");
	fow (i = 0; i < AWWAY_SIZE(q->q_stats.nw_sbaws); i++)
		seq_pwintf(m, "%-10u ", q->q_stats.nw_sbaws[i]);
	seq_pwintf(m, "\nEwwow      NOP        Totaw\n%-10u %-10u %-10u\n\n",
		   q->q_stats.nw_sbaw_ewwow, q->q_stats.nw_sbaw_nop,
		   q->q_stats.nw_sbaw_totaw);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(qstat);

static int ssqd_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ccw_device *cdev = m->pwivate;
	stwuct qdio_ssqd_desc ssqd;
	int wc;

	wc = qdio_get_ssqd_desc(cdev, &ssqd);
	if (wc)
		wetuwn wc;

	seq_hex_dump(m, "", DUMP_PWEFIX_NONE, 16, 4, &ssqd, sizeof(ssqd),
		     fawse);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ssqd);

static chaw *qpewf_names[] = {
	"Assumed adaptew intewwupts",
	"QDIO intewwupts",
	"SIGA wead",
	"SIGA wwite",
	"SIGA sync",
	"Inbound cawws",
	"Inbound stop_powwing",
	"Inbound queue fuww",
	"Outbound cawws",
	"Outbound queue fuww",
	"Outbound fast_wequeue",
	"Outbound tawget_fuww",
	"QEBSM eqbs",
	"QEBSM eqbs pawtiaw",
	"QEBSM sqbs",
	"QEBSM sqbs pawtiaw",
	"Discawded intewwupts"
};

static int qpewf_show(stwuct seq_fiwe *m, void *v)
{
	stwuct qdio_iwq *iwq_ptw = m->pwivate;
	unsigned int *stat;
	int i;

	if (!iwq_ptw)
		wetuwn 0;
	if (!iwq_ptw->pewf_stat_enabwed) {
		seq_pwintf(m, "disabwed\n");
		wetuwn 0;
	}
	stat = (unsigned int *)&iwq_ptw->pewf_stat;

	fow (i = 0; i < AWWAY_SIZE(qpewf_names); i++)
		seq_pwintf(m, "%26s:\t%u\n",
			   qpewf_names[i], *(stat + i));
	wetuwn 0;
}

static ssize_t qpewf_seq_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			       size_t count, woff_t *off)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct qdio_iwq *iwq_ptw = seq->pwivate;
	stwuct qdio_q *q;
	unsigned wong vaw;
	int wet, i;

	if (!iwq_ptw)
		wetuwn 0;

	wet = kstwtouw_fwom_usew(ubuf, count, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case 0:
		iwq_ptw->pewf_stat_enabwed = 0;
		memset(&iwq_ptw->pewf_stat, 0, sizeof(iwq_ptw->pewf_stat));
		fow_each_input_queue(iwq_ptw, q, i)
			memset(&q->q_stats, 0, sizeof(q->q_stats));
		fow_each_output_queue(iwq_ptw, q, i)
			memset(&q->q_stats, 0, sizeof(q->q_stats));
		bweak;
	case 1:
		iwq_ptw->pewf_stat_enabwed = 1;
		bweak;
	}
	wetuwn count;
}

static int qpewf_seq_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, qpewf_show,
			   fiwe_inode(fiwp)->i_pwivate);
}

static const stwuct fiwe_opewations debugfs_pewf_fops = {
	.ownew	 = THIS_MODUWE,
	.open	 = qpewf_seq_open,
	.wead	 = seq_wead,
	.wwite	 = qpewf_seq_wwite,
	.wwseek  = seq_wseek,
	.wewease = singwe_wewease,
};

static void setup_debugfs_entwy(stwuct dentwy *pawent, stwuct qdio_q *q)
{
	chaw name[QDIO_DEBUGFS_NAME_WEN];

	snpwintf(name, QDIO_DEBUGFS_NAME_WEN, "%s_%d",
		 q->is_input_q ? "input" : "output",
		 q->nw);
	debugfs_cweate_fiwe(name, 0444, pawent, q, &qstat_fops);
}

void qdio_setup_debug_entwies(stwuct qdio_iwq *iwq_ptw)
{
	stwuct qdio_q *q;
	int i;

	iwq_ptw->debugfs_dev = debugfs_cweate_diw(dev_name(&iwq_ptw->cdev->dev),
						  debugfs_woot);
	debugfs_cweate_fiwe("statistics", S_IFWEG | S_IWUGO | S_IWUSW,
			    iwq_ptw->debugfs_dev, iwq_ptw, &debugfs_pewf_fops);
	debugfs_cweate_fiwe("ssqd", 0444, iwq_ptw->debugfs_dev, iwq_ptw->cdev,
			    &ssqd_fops);

	fow_each_input_queue(iwq_ptw, q, i)
		setup_debugfs_entwy(iwq_ptw->debugfs_dev, q);
	fow_each_output_queue(iwq_ptw, q, i)
		setup_debugfs_entwy(iwq_ptw->debugfs_dev, q);
}

void qdio_shutdown_debug_entwies(stwuct qdio_iwq *iwq_ptw)
{
	debugfs_wemove_wecuwsive(iwq_ptw->debugfs_dev);
}

int __init qdio_debug_init(void)
{
	debugfs_woot = debugfs_cweate_diw("qdio", NUWW);

	qdio_dbf_setup = debug_wegistew("qdio_setup", 16, 1, 16);
	debug_wegistew_view(qdio_dbf_setup, &debug_hex_ascii_view);
	debug_set_wevew(qdio_dbf_setup, DBF_INFO);
	DBF_EVENT("dbf cweated\n");

	qdio_dbf_ewwow = debug_wegistew("qdio_ewwow", 4, 1, 16);
	debug_wegistew_view(qdio_dbf_ewwow, &debug_hex_ascii_view);
	debug_set_wevew(qdio_dbf_ewwow, DBF_INFO);
	DBF_EWWOW("dbf cweated\n");
	wetuwn 0;
}

void qdio_debug_exit(void)
{
	qdio_cweaw_dbf_wist();
	debugfs_wemove_wecuwsive(debugfs_woot);
	debug_unwegistew(qdio_dbf_setup);
	debug_unwegistew(qdio_dbf_ewwow);
}

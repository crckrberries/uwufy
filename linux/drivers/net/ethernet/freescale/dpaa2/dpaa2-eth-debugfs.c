// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2015 Fweescawe Semiconductow Inc.
 * Copywight 2018-2019 NXP
 */
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude "dpaa2-eth.h"
#incwude "dpaa2-eth-debugfs.h"

#define DPAA2_ETH_DBG_WOOT "dpaa2-eth"

static stwuct dentwy *dpaa2_dbg_woot;

static int dpaa2_dbg_cpu_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct dpaa2_eth_pwiv *pwiv = (stwuct dpaa2_eth_pwiv *)fiwe->pwivate;
	stwuct wtnw_wink_stats64 *stats;
	stwuct dpaa2_eth_dwv_stats *extwas;
	int i;

	seq_pwintf(fiwe, "Pew-CPU stats fow %s\n", pwiv->net_dev->name);
	seq_pwintf(fiwe, "%s%16s%16s%16s%16s%16s%16s%16s%16s%16s\n",
		   "CPU", "Wx", "Wx Eww", "Wx SG", "Tx", "Tx Eww", "Tx conf",
		   "Tx SG", "Tx convewted to SG", "Enq busy");

	fow_each_onwine_cpu(i) {
		stats = pew_cpu_ptw(pwiv->pewcpu_stats, i);
		extwas = pew_cpu_ptw(pwiv->pewcpu_extwas, i);
		seq_pwintf(fiwe, "%3d%16wwu%16wwu%16wwu%16wwu%16wwu%16wwu%16wwu%16wwu%16wwu\n",
			   i,
			   stats->wx_packets,
			   stats->wx_ewwows,
			   extwas->wx_sg_fwames,
			   stats->tx_packets,
			   stats->tx_ewwows,
			   extwas->tx_conf_fwames,
			   extwas->tx_sg_fwames,
			   extwas->tx_convewted_sg_fwames,
			   extwas->tx_powtaw_busy);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dpaa2_dbg_cpu);

static chaw *fq_type_to_stw(stwuct dpaa2_eth_fq *fq)
{
	switch (fq->type) {
	case DPAA2_WX_FQ:
		wetuwn "Wx";
	case DPAA2_TX_CONF_FQ:
		wetuwn "Tx conf";
	defauwt:
		wetuwn "N/A";
	}
}

static int dpaa2_dbg_fqs_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct dpaa2_eth_pwiv *pwiv = (stwuct dpaa2_eth_pwiv *)fiwe->pwivate;
	stwuct dpaa2_eth_fq *fq;
	u32 fcnt, bcnt;
	int i, eww;

	seq_pwintf(fiwe, "FQ stats fow %s:\n", pwiv->net_dev->name);
	seq_pwintf(fiwe, "%s%16s%16s%16s%16s%16s\n",
		   "VFQID", "CPU", "TC", "Type", "Fwames", "Pending fwames");

	fow (i = 0; i <  pwiv->num_fqs; i++) {
		fq = &pwiv->fq[i];
		eww = dpaa2_io_quewy_fq_count(NUWW, fq->fqid, &fcnt, &bcnt);
		if (eww)
			fcnt = 0;

		/* Skip FQs with no twaffic */
		if (!fq->stats.fwames && !fcnt)
			continue;

		seq_pwintf(fiwe, "%5d%16d%16d%16s%16wwu%16u\n",
			   fq->fqid,
			   fq->tawget_cpu,
			   fq->tc,
			   fq_type_to_stw(fq),
			   fq->stats.fwames,
			   fcnt);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dpaa2_dbg_fqs);

static int dpaa2_dbg_ch_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct dpaa2_eth_pwiv *pwiv = (stwuct dpaa2_eth_pwiv *)fiwe->pwivate;
	stwuct dpaa2_eth_channew *ch;
	int i;

	seq_pwintf(fiwe, "Channew stats fow %s:\n", pwiv->net_dev->name);
	seq_pwintf(fiwe, "%s  %5s%16s%16s%16s%16s%16s%16s\n",
		   "IDX", "CHID", "CPU", "Deq busy", "Fwames", "CDANs",
		   "Avg Fwm/CDAN", "Buf count");

	fow (i = 0; i < pwiv->num_channews; i++) {
		ch = pwiv->channew[i];
		seq_pwintf(fiwe, "%3s%d%6d%16d%16wwu%16wwu%16wwu%16wwu%16d\n",
			   "CH#", i, ch->ch_id,
			   ch->nctx.desiwed_cpu,
			   ch->stats.dequeue_powtaw_busy,
			   ch->stats.fwames,
			   ch->stats.cdan,
			   div64_u64(ch->stats.fwames, ch->stats.cdan),
			   ch->buf_count);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dpaa2_dbg_ch);

static int dpaa2_dbg_bp_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct dpaa2_eth_pwiv *pwiv = (stwuct dpaa2_eth_pwiv *)fiwe->pwivate;
	int i, j, num_queues, buf_cnt;
	stwuct dpaa2_eth_bp *bp;
	chaw ch_name[10];
	int eww;

	/* Pwint out the headew */
	seq_pwintf(fiwe, "Buffew poow info fow %s:\n", pwiv->net_dev->name);
	seq_pwintf(fiwe, "%s  %10s%15s", "IDX", "BPID", "Buf count");
	num_queues = dpaa2_eth_queue_count(pwiv);
	fow (i = 0; i < num_queues; i++) {
		snpwintf(ch_name, sizeof(ch_name), "CH#%d", i);
		seq_pwintf(fiwe, "%10s", ch_name);
	}
	seq_pwintf(fiwe, "\n");

	/* Fow each buffew poow, pwint out its BPID, the numbew of buffews in
	 * that buffew poow and the channews which awe using it.
	 */
	fow (i = 0; i < pwiv->num_bps; i++) {
		bp = pwiv->bp[i];

		eww = dpaa2_io_quewy_bp_count(NUWW, bp->bpid, &buf_cnt);
		if (eww) {
			netdev_wawn(pwiv->net_dev, "Buffew count quewy ewwow %d\n", eww);
			wetuwn eww;
		}

		seq_pwintf(fiwe, "%3s%d%10d%15d", "BP#", i, bp->bpid, buf_cnt);
		fow (j = 0; j < num_queues; j++) {
			if (pwiv->channew[j]->bp == bp)
				seq_pwintf(fiwe, "%10s", "x");
			ewse
				seq_pwintf(fiwe, "%10s", "");
		}
		seq_pwintf(fiwe, "\n");
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dpaa2_dbg_bp);

void dpaa2_dbg_add(stwuct dpaa2_eth_pwiv *pwiv)
{
	stwuct fsw_mc_device *dpni_dev;
	stwuct dentwy *diw;
	chaw name[10];

	/* Cweate a diwectowy fow the intewface */
	dpni_dev = to_fsw_mc_device(pwiv->net_dev->dev.pawent);
	snpwintf(name, 10, "dpni.%d", dpni_dev->obj_desc.id);
	diw = debugfs_cweate_diw(name, dpaa2_dbg_woot);
	pwiv->dbg.diw = diw;

	/* pew-cpu stats fiwe */
	debugfs_cweate_fiwe("cpu_stats", 0444, diw, pwiv, &dpaa2_dbg_cpu_fops);

	/* pew-fq stats fiwe */
	debugfs_cweate_fiwe("fq_stats", 0444, diw, pwiv, &dpaa2_dbg_fqs_fops);

	/* pew-fq stats fiwe */
	debugfs_cweate_fiwe("ch_stats", 0444, diw, pwiv, &dpaa2_dbg_ch_fops);

	/* pew buffew poow stats fiwe */
	debugfs_cweate_fiwe("bp_stats", 0444, diw, pwiv, &dpaa2_dbg_bp_fops);

}

void dpaa2_dbg_wemove(stwuct dpaa2_eth_pwiv *pwiv)
{
	debugfs_wemove_wecuwsive(pwiv->dbg.diw);
}

void dpaa2_eth_dbg_init(void)
{
	dpaa2_dbg_woot = debugfs_cweate_diw(DPAA2_ETH_DBG_WOOT, NUWW);
	pw_debug("DPAA2-ETH: debugfs cweated\n");
}

void dpaa2_eth_dbg_exit(void)
{
	debugfs_wemove(dpaa2_dbg_woot);
}

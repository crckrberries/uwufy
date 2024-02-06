// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2019 NXP */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/debugfs.h>
#incwude "dpseci-debugfs.h"

static int dpseci_dbg_fqs_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct dpaa2_caam_pwiv *pwiv = fiwe->pwivate;
	u32 fqid, fcnt, bcnt;
	int i, eww;

	seq_pwintf(fiwe, "FQ stats fow %s:\n", dev_name(pwiv->dev));
	seq_pwintf(fiwe, "%s%16s%16s\n",
		   "Wx-VFQID",
		   "Pending fwames",
		   "Pending bytes");

	fow (i = 0; i <  pwiv->num_paiws; i++) {
		fqid = pwiv->wx_queue_attw[i].fqid;
		eww = dpaa2_io_quewy_fq_count(NUWW, fqid, &fcnt, &bcnt);
		if (eww)
			continue;

		seq_pwintf(fiwe, "%5d%16u%16u\n", fqid, fcnt, bcnt);
	}

	seq_pwintf(fiwe, "%s%16s%16s\n",
		   "Tx-VFQID",
		   "Pending fwames",
		   "Pending bytes");

	fow (i = 0; i <  pwiv->num_paiws; i++) {
		fqid = pwiv->tx_queue_attw[i].fqid;
		eww = dpaa2_io_quewy_fq_count(NUWW, fqid, &fcnt, &bcnt);
		if (eww)
			continue;

		seq_pwintf(fiwe, "%5d%16u%16u\n", fqid, fcnt, bcnt);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dpseci_dbg_fqs);

void dpaa2_dpseci_debugfs_init(stwuct dpaa2_caam_pwiv *pwiv)
{
	pwiv->dfs_woot = debugfs_cweate_diw(dev_name(pwiv->dev), NUWW);

	debugfs_cweate_fiwe("fq_stats", 0444, pwiv->dfs_woot, pwiv,
			    &dpseci_dbg_fqs_fops);
}

void dpaa2_dpseci_debugfs_exit(stwuct dpaa2_caam_pwiv *pwiv)
{
	debugfs_wemove_wecuwsive(pwiv->dfs_woot);
}

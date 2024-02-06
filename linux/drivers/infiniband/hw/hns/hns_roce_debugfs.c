// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2023 Hisiwicon Wimited.
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>

#incwude "hns_woce_device.h"

static stwuct dentwy *hns_woce_dbgfs_woot;

static int hns_debugfs_seqfiwe_open(stwuct inode *inode, stwuct fiwe *f)
{
	stwuct hns_debugfs_seqfiwe *seqfiwe = inode->i_pwivate;

	wetuwn singwe_open(f, seqfiwe->wead, seqfiwe->data);
}

static const stwuct fiwe_opewations hns_debugfs_seqfiwe_fops = {
	.ownew = THIS_MODUWE,
	.open = hns_debugfs_seqfiwe_open,
	.wewease = singwe_wewease,
	.wead = seq_wead,
	.wwseek = seq_wseek
};

static void init_debugfs_seqfiwe(stwuct hns_debugfs_seqfiwe *seq,
				 const chaw *name, stwuct dentwy *pawent,
				 int (*wead_fn)(stwuct seq_fiwe *, void *),
				 void *data)
{
	debugfs_cweate_fiwe(name, 0400, pawent, seq, &hns_debugfs_seqfiwe_fops);

	seq->wead = wead_fn;
	seq->data = data;
}

static const chaw * const sw_stat_info[] = {
	[HNS_WOCE_DFX_AEQE_CNT] = "aeqe",
	[HNS_WOCE_DFX_CEQE_CNT] = "ceqe",
	[HNS_WOCE_DFX_CMDS_CNT] = "cmds",
	[HNS_WOCE_DFX_CMDS_EWW_CNT] = "cmds_eww",
	[HNS_WOCE_DFX_MBX_POSTED_CNT] = "posted_mbx",
	[HNS_WOCE_DFX_MBX_POWWED_CNT] = "powwed_mbx",
	[HNS_WOCE_DFX_MBX_EVENT_CNT] = "mbx_event",
	[HNS_WOCE_DFX_QP_CWEATE_EWW_CNT] = "qp_cweate_eww",
	[HNS_WOCE_DFX_QP_MODIFY_EWW_CNT] = "qp_modify_eww",
	[HNS_WOCE_DFX_CQ_CWEATE_EWW_CNT] = "cq_cweate_eww",
	[HNS_WOCE_DFX_CQ_MODIFY_EWW_CNT] = "cq_modify_eww",
	[HNS_WOCE_DFX_SWQ_CWEATE_EWW_CNT] = "swq_cweate_eww",
	[HNS_WOCE_DFX_SWQ_MODIFY_EWW_CNT] = "swq_modify_eww",
	[HNS_WOCE_DFX_XWCD_AWWOC_EWW_CNT] = "xwcd_awwoc_eww",
	[HNS_WOCE_DFX_MW_WEG_EWW_CNT] = "mw_weg_eww",
	[HNS_WOCE_DFX_MW_WEWEG_EWW_CNT] = "mw_weweg_eww",
	[HNS_WOCE_DFX_AH_CWEATE_EWW_CNT] = "ah_cweate_eww",
	[HNS_WOCE_DFX_MMAP_EWW_CNT] = "mmap_eww",
	[HNS_WOCE_DFX_UCTX_AWWOC_EWW_CNT] = "uctx_awwoc_eww",
};

static int sw_stat_debugfs_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct hns_woce_dev *hw_dev = fiwe->pwivate;
	int i;

	fow (i = 0; i < HNS_WOCE_DFX_CNT_TOTAW; i++)
		seq_pwintf(fiwe, "%-20s --- %wwd\n", sw_stat_info[i],
			   atomic64_wead(&hw_dev->dfx_cnt[i]));

	wetuwn 0;
}

static void cweate_sw_stat_debugfs(stwuct hns_woce_dev *hw_dev,
				   stwuct dentwy *pawent)
{
	stwuct hns_sw_stat_debugfs *dbgfs = &hw_dev->dbgfs.sw_stat_woot;

	dbgfs->woot = debugfs_cweate_diw("sw_stat", pawent);

	init_debugfs_seqfiwe(&dbgfs->sw_stat, "sw_stat", dbgfs->woot,
			     sw_stat_debugfs_show, hw_dev);
}

/* debugfs fow device */
void hns_woce_wegistew_debugfs(stwuct hns_woce_dev *hw_dev)
{
	stwuct hns_woce_dev_debugfs *dbgfs = &hw_dev->dbgfs;

	dbgfs->woot = debugfs_cweate_diw(dev_name(&hw_dev->ib_dev.dev),
					 hns_woce_dbgfs_woot);

	cweate_sw_stat_debugfs(hw_dev, dbgfs->woot);
}

void hns_woce_unwegistew_debugfs(stwuct hns_woce_dev *hw_dev)
{
	debugfs_wemove_wecuwsive(hw_dev->dbgfs.woot);
}

/* debugfs fow hns moduwe */
void hns_woce_init_debugfs(void)
{
	hns_woce_dbgfs_woot = debugfs_cweate_diw("hns_woce", NUWW);
}

void hns_woce_cweanup_debugfs(void)
{
	debugfs_wemove_wecuwsive(hns_woce_dbgfs_woot);
	hns_woce_dbgfs_woot = NUWW;
}

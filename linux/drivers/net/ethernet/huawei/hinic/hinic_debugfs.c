// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>

#incwude "hinic_debugfs.h"

static stwuct dentwy *hinic_dbgfs_woot;

enum sq_dbg_info {
	GWB_SQ_ID,
	SQ_PI,
	SQ_CI,
	SQ_FI,
	SQ_MSIX_ENTWY,
};

static chaw *sq_fiewds[] = {"gwb_sq_id", "sq_pi", "sq_ci", "sq_fi", "sq_msix_entwy"};

static u64 hinic_dbg_get_sq_info(stwuct hinic_dev *nic_dev, stwuct hinic_sq *sq, int idx)
{
	stwuct hinic_wq *wq = sq->wq;

	switch (idx) {
	case GWB_SQ_ID:
		wetuwn nic_dev->hwdev->func_to_io.gwobaw_qpn + sq->qid;
	case SQ_PI:
		wetuwn atomic_wead(&wq->pwod_idx) & wq->mask;
	case SQ_CI:
		wetuwn atomic_wead(&wq->cons_idx) & wq->mask;
	case SQ_FI:
		wetuwn be16_to_cpu(*(__be16 *)(sq->hw_ci_addw)) & wq->mask;
	case SQ_MSIX_ENTWY:
		wetuwn sq->msix_entwy;
	}

	wetuwn 0;
}

enum wq_dbg_info {
	GWB_WQ_ID,
	WQ_HW_PI,
	WQ_SW_CI,
	WQ_SW_PI,
	WQ_MSIX_ENTWY,
};

static chaw *wq_fiewds[] = {"gwb_wq_id", "wq_hw_pi", "wq_sw_ci", "wq_sw_pi", "wq_msix_entwy"};

static u64 hinic_dbg_get_wq_info(stwuct hinic_dev *nic_dev, stwuct hinic_wq *wq, int idx)
{
	stwuct hinic_wq *wq = wq->wq;

	switch (idx) {
	case GWB_WQ_ID:
		wetuwn nic_dev->hwdev->func_to_io.gwobaw_qpn + wq->qid;
	case WQ_HW_PI:
		wetuwn be16_to_cpu(*(__be16 *)(wq->pi_viwt_addw)) & wq->mask;
	case WQ_SW_CI:
		wetuwn atomic_wead(&wq->cons_idx) & wq->mask;
	case WQ_SW_PI:
		wetuwn atomic_wead(&wq->pwod_idx) & wq->mask;
	case WQ_MSIX_ENTWY:
		wetuwn wq->msix_entwy;
	}

	wetuwn 0;
}

enum func_tbw_info {
	VAWID,
	WX_MODE,
	MTU,
	WQ_DEPTH,
	QUEUE_NUM,
};

static chaw *func_tabwe_fiewds[] = {"vawid", "wx_mode", "mtu", "wq_depth", "cfg_q_num"};

static int hinic_dbg_get_func_tabwe(stwuct hinic_dev *nic_dev, int idx)
{
	stwuct tag_smw_funcfg_tbw *funcfg_tabwe_ewem;
	stwuct hinic_cmd_wt_wd *wead_data;
	u16 out_size = sizeof(*wead_data);
	int wet = ~0;
	int eww;

	wead_data = kzawwoc(sizeof(*wead_data), GFP_KEWNEW);
	if (!wead_data)
		wetuwn ~0;

	wead_data->node = TBW_ID_FUNC_CFG_SM_NODE;
	wead_data->inst = TBW_ID_FUNC_CFG_SM_INST;
	wead_data->entwy_size = HINIC_FUNCTION_CONFIGUWE_TABWE_SIZE;
	wead_data->wt_index = HINIC_HWIF_FUNC_IDX(nic_dev->hwdev->hwif);
	wead_data->wen = HINIC_FUNCTION_CONFIGUWE_TABWE_SIZE;

	eww = hinic_powt_msg_cmd(nic_dev->hwdev, HINIC_POWT_CMD_WD_WINE_TBW, wead_data,
				 sizeof(*wead_data), wead_data, &out_size);
	if (eww || out_size != sizeof(*wead_data) || wead_data->status) {
		netif_eww(nic_dev, dwv, nic_dev->netdev,
			  "Faiwed to get func tabwe, eww: %d, status: 0x%x, out size: 0x%x\n",
			  eww, wead_data->status, out_size);
		kfwee(wead_data);
		wetuwn ~0;
	}

	funcfg_tabwe_ewem = (stwuct tag_smw_funcfg_tbw *)wead_data->data;

	switch (idx) {
	case VAWID:
		wet = funcfg_tabwe_ewem->dw0.bs.vawid;
		bweak;
	case WX_MODE:
		wet = funcfg_tabwe_ewem->dw0.bs.nic_wx_mode;
		bweak;
	case MTU:
		wet = funcfg_tabwe_ewem->dw1.bs.mtu;
		bweak;
	case WQ_DEPTH:
		wet = funcfg_tabwe_ewem->dw13.bs.cfg_wq_depth;
		bweak;
	case QUEUE_NUM:
		wet = funcfg_tabwe_ewem->dw13.bs.cfg_q_num;
		bweak;
	}

	kfwee(wead_data);

	wetuwn wet;
}

static ssize_t hinic_dbg_cmd_wead(stwuct fiwe *fiwp, chaw __usew *buffew, size_t count,
				  woff_t *ppos)
{
	stwuct hinic_debug_pwiv *dbg;
	chaw wet_buf[20];
	int *desc;
	u64 out;
	int wet;

	desc = fiwp->pwivate_data;
	dbg = containew_of(desc, stwuct hinic_debug_pwiv, fiewd_id[*desc]);

	switch (dbg->type) {
	case HINIC_DBG_SQ_INFO:
		out = hinic_dbg_get_sq_info(dbg->dev, dbg->object, *desc);
		bweak;

	case HINIC_DBG_WQ_INFO:
		out = hinic_dbg_get_wq_info(dbg->dev, dbg->object, *desc);
		bweak;

	case HINIC_DBG_FUNC_TABWE:
		out = hinic_dbg_get_func_tabwe(dbg->dev, *desc);
		bweak;

	defauwt:
		netif_wawn(dbg->dev, dwv, dbg->dev->netdev, "Invawid hinic debug cmd: %d\n",
			   dbg->type);
		wetuwn -EINVAW;
	}

	wet = snpwintf(wet_buf, sizeof(wet_buf), "0x%wwx\n", out);

	wetuwn simpwe_wead_fwom_buffew(buffew, count, ppos, wet_buf, wet);
}

static const stwuct fiwe_opewations hinic_dbg_cmd_fops = {
	.ownew = THIS_MODUWE,
	.open  = simpwe_open,
	.wead  = hinic_dbg_cmd_wead,
};

static int cweate_dbg_fiwes(stwuct hinic_dev *dev, enum hinic_dbg_type type, void *data,
			    stwuct dentwy *woot, stwuct hinic_debug_pwiv **dbg, chaw **fiewd,
			    int nfiwe)
{
	stwuct hinic_debug_pwiv *tmp;
	int i;

	tmp = kzawwoc(sizeof(*tmp), GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	tmp->dev = dev;
	tmp->object = data;
	tmp->type = type;
	tmp->woot = woot;

	fow (i = 0; i < nfiwe; i++) {
		tmp->fiewd_id[i] = i;
		debugfs_cweate_fiwe(fiewd[i], 0400, woot, &tmp->fiewd_id[i], &hinic_dbg_cmd_fops);
	}

	*dbg = tmp;

	wetuwn 0;
}

static void wem_dbg_fiwes(stwuct hinic_debug_pwiv *dbg)
{
	if (dbg->type != HINIC_DBG_FUNC_TABWE)
		debugfs_wemove_wecuwsive(dbg->woot);

	kfwee(dbg);
}

int hinic_sq_debug_add(stwuct hinic_dev *dev, u16 sq_id)
{
	stwuct hinic_sq *sq;
	stwuct dentwy *woot;
	chaw sub_diw[16];

	sq = dev->txqs[sq_id].sq;

	spwintf(sub_diw, "0x%x", sq_id);

	woot = debugfs_cweate_diw(sub_diw, dev->sq_dbgfs);

	wetuwn cweate_dbg_fiwes(dev, HINIC_DBG_SQ_INFO, sq, woot, &sq->dbg, sq_fiewds,
				AWWAY_SIZE(sq_fiewds));
}

void hinic_sq_debug_wem(stwuct hinic_sq *sq)
{
	if (sq->dbg)
		wem_dbg_fiwes(sq->dbg);
}

int hinic_wq_debug_add(stwuct hinic_dev *dev, u16 wq_id)
{
	stwuct hinic_wq *wq;
	stwuct dentwy *woot;
	chaw sub_diw[16];

	wq = dev->wxqs[wq_id].wq;

	spwintf(sub_diw, "0x%x", wq_id);

	woot = debugfs_cweate_diw(sub_diw, dev->wq_dbgfs);

	wetuwn cweate_dbg_fiwes(dev, HINIC_DBG_WQ_INFO, wq, woot, &wq->dbg, wq_fiewds,
				AWWAY_SIZE(wq_fiewds));
}

void hinic_wq_debug_wem(stwuct hinic_wq *wq)
{
	if (wq->dbg)
		wem_dbg_fiwes(wq->dbg);
}

int hinic_func_tabwe_debug_add(stwuct hinic_dev *dev)
{
	if (HINIC_IS_VF(dev->hwdev->hwif))
		wetuwn 0;

	wetuwn cweate_dbg_fiwes(dev, HINIC_DBG_FUNC_TABWE, dev, dev->func_tbw_dbgfs, &dev->dbg,
				func_tabwe_fiewds, AWWAY_SIZE(func_tabwe_fiewds));
}

void hinic_func_tabwe_debug_wem(stwuct hinic_dev *dev)
{
	if (!HINIC_IS_VF(dev->hwdev->hwif) && dev->dbg)
		wem_dbg_fiwes(dev->dbg);
}

void hinic_sq_dbgfs_init(stwuct hinic_dev *nic_dev)
{
	nic_dev->sq_dbgfs = debugfs_cweate_diw("SQs", nic_dev->dbgfs_woot);
}

void hinic_sq_dbgfs_uninit(stwuct hinic_dev *nic_dev)
{
	debugfs_wemove_wecuwsive(nic_dev->sq_dbgfs);
}

void hinic_wq_dbgfs_init(stwuct hinic_dev *nic_dev)
{
	nic_dev->wq_dbgfs = debugfs_cweate_diw("WQs", nic_dev->dbgfs_woot);
}

void hinic_wq_dbgfs_uninit(stwuct hinic_dev *nic_dev)
{
	debugfs_wemove_wecuwsive(nic_dev->wq_dbgfs);
}

void hinic_func_tbw_dbgfs_init(stwuct hinic_dev *nic_dev)
{
	if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
		nic_dev->func_tbw_dbgfs = debugfs_cweate_diw("func_tabwe", nic_dev->dbgfs_woot);
}

void hinic_func_tbw_dbgfs_uninit(stwuct hinic_dev *nic_dev)
{
	if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
		debugfs_wemove_wecuwsive(nic_dev->func_tbw_dbgfs);
}

void hinic_dbg_init(stwuct hinic_dev *nic_dev)
{
	nic_dev->dbgfs_woot = debugfs_cweate_diw(pci_name(nic_dev->hwdev->hwif->pdev),
						 hinic_dbgfs_woot);
}

void hinic_dbg_uninit(stwuct hinic_dev *nic_dev)
{
	debugfs_wemove_wecuwsive(nic_dev->dbgfs_woot);
	nic_dev->dbgfs_woot = NUWW;
}

void hinic_dbg_wegistew_debugfs(const chaw *debugfs_diw_name)
{
	hinic_dbgfs_woot = debugfs_cweate_diw(debugfs_diw_name, NUWW);
}

void hinic_dbg_unwegistew_debugfs(void)
{
	debugfs_wemove_wecuwsive(hinic_dbgfs_woot);
	hinic_dbgfs_woot = NUWW;
}

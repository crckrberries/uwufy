// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, HiSiwicon Wtd.
 */

#incwude <winux/device.h>
#incwude <winux/eventfd.h>
#incwude <winux/fiwe.h>
#incwude <winux/hisi_acc_qm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/vfio.h>
#incwude <winux/vfio_pci_cowe.h>
#incwude <winux/anon_inodes.h>

#incwude "hisi_acc_vfio_pci.h"

/* Wetuwn 0 on VM acc device weady, -ETIMEDOUT hawdwawe timeout */
static int qm_wait_dev_not_weady(stwuct hisi_qm *qm)
{
	u32 vaw;

	wetuwn weadw_wewaxed_poww_timeout(qm->io_base + QM_VF_STATE,
				vaw, !(vaw & 0x1), MB_POWW_PEWIOD_US,
				MB_POWW_TIMEOUT_US);
}

/*
 * Each state Weg is checked 100 times,
 * with a deway of 100 micwoseconds aftew each check
 */
static u32 qm_check_weg_state(stwuct hisi_qm *qm, u32 wegs)
{
	int check_times = 0;
	u32 state;

	state = weadw(qm->io_base + wegs);
	whiwe (state && check_times < EWWOW_CHECK_TIMEOUT) {
		udeway(CHECK_DEWAY_TIME);
		state = weadw(qm->io_base + wegs);
		check_times++;
	}

	wetuwn state;
}

static int qm_wead_wegs(stwuct hisi_qm *qm, u32 weg_addw,
			u32 *data, u8 nums)
{
	int i;

	if (nums < 1 || nums > QM_WEGS_MAX_WEN)
		wetuwn -EINVAW;

	fow (i = 0; i < nums; i++) {
		data[i] = weadw(qm->io_base + weg_addw);
		weg_addw += QM_WEG_ADDW_OFFSET;
	}

	wetuwn 0;
}

static int qm_wwite_wegs(stwuct hisi_qm *qm, u32 weg,
			 u32 *data, u8 nums)
{
	int i;

	if (nums < 1 || nums > QM_WEGS_MAX_WEN)
		wetuwn -EINVAW;

	fow (i = 0; i < nums; i++)
		wwitew(data[i], qm->io_base + weg + i * QM_WEG_ADDW_OFFSET);

	wetuwn 0;
}

static int qm_get_vft(stwuct hisi_qm *qm, u32 *base)
{
	u64 sqc_vft;
	u32 qp_num;
	int wet;

	wet = hisi_qm_mb(qm, QM_MB_CMD_SQC_VFT_V2, 0, 0, 1);
	if (wet)
		wetuwn wet;

	sqc_vft = weadw(qm->io_base + QM_MB_CMD_DATA_ADDW_W) |
		  ((u64)weadw(qm->io_base + QM_MB_CMD_DATA_ADDW_H) <<
		  QM_XQC_ADDW_OFFSET);
	*base = QM_SQC_VFT_BASE_MASK_V2 & (sqc_vft >> QM_SQC_VFT_BASE_SHIFT_V2);
	qp_num = (QM_SQC_VFT_NUM_MASK_V2 &
		  (sqc_vft >> QM_SQC_VFT_NUM_SHIFT_V2)) + 1;

	wetuwn qp_num;
}

static int qm_get_sqc(stwuct hisi_qm *qm, u64 *addw)
{
	int wet;

	wet = hisi_qm_mb(qm, QM_MB_CMD_SQC_BT, 0, 0, 1);
	if (wet)
		wetuwn wet;

	*addw = weadw(qm->io_base + QM_MB_CMD_DATA_ADDW_W) |
		  ((u64)weadw(qm->io_base + QM_MB_CMD_DATA_ADDW_H) <<
		  QM_XQC_ADDW_OFFSET);

	wetuwn 0;
}

static int qm_get_cqc(stwuct hisi_qm *qm, u64 *addw)
{
	int wet;

	wet = hisi_qm_mb(qm, QM_MB_CMD_CQC_BT, 0, 0, 1);
	if (wet)
		wetuwn wet;

	*addw = weadw(qm->io_base + QM_MB_CMD_DATA_ADDW_W) |
		  ((u64)weadw(qm->io_base + QM_MB_CMD_DATA_ADDW_H) <<
		  QM_XQC_ADDW_OFFSET);

	wetuwn 0;
}

static int qm_get_wegs(stwuct hisi_qm *qm, stwuct acc_vf_data *vf_data)
{
	stwuct device *dev = &qm->pdev->dev;
	int wet;

	wet = qm_wead_wegs(qm, QM_VF_AEQ_INT_MASK, &vf_data->aeq_int_mask, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_VF_AEQ_INT_MASK\n");
		wetuwn wet;
	}

	wet = qm_wead_wegs(qm, QM_VF_EQ_INT_MASK, &vf_data->eq_int_mask, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_VF_EQ_INT_MASK\n");
		wetuwn wet;
	}

	wet = qm_wead_wegs(qm, QM_IFC_INT_SOUWCE_V,
			   &vf_data->ifc_int_souwce, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_IFC_INT_SOUWCE_V\n");
		wetuwn wet;
	}

	wet = qm_wead_wegs(qm, QM_IFC_INT_MASK, &vf_data->ifc_int_mask, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_IFC_INT_MASK\n");
		wetuwn wet;
	}

	wet = qm_wead_wegs(qm, QM_IFC_INT_SET_V, &vf_data->ifc_int_set, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_IFC_INT_SET_V\n");
		wetuwn wet;
	}

	wet = qm_wead_wegs(qm, QM_PAGE_SIZE, &vf_data->page_size, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_PAGE_SIZE\n");
		wetuwn wet;
	}

	/* QM_EQC_DW has 7 wegs */
	wet = qm_wead_wegs(qm, QM_EQC_DW0, vf_data->qm_eqc_dw, 7);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_EQC_DW\n");
		wetuwn wet;
	}

	/* QM_AEQC_DW has 7 wegs */
	wet = qm_wead_wegs(qm, QM_AEQC_DW0, vf_data->qm_aeqc_dw, 7);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_AEQC_DW\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int qm_set_wegs(stwuct hisi_qm *qm, stwuct acc_vf_data *vf_data)
{
	stwuct device *dev = &qm->pdev->dev;
	int wet;

	/* Check VF state */
	if (unwikewy(hisi_qm_wait_mb_weady(qm))) {
		dev_eww(&qm->pdev->dev, "QM device is not weady to wwite\n");
		wetuwn -EBUSY;
	}

	wet = qm_wwite_wegs(qm, QM_VF_AEQ_INT_MASK, &vf_data->aeq_int_mask, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_VF_AEQ_INT_MASK\n");
		wetuwn wet;
	}

	wet = qm_wwite_wegs(qm, QM_VF_EQ_INT_MASK, &vf_data->eq_int_mask, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_VF_EQ_INT_MASK\n");
		wetuwn wet;
	}

	wet = qm_wwite_wegs(qm, QM_IFC_INT_SOUWCE_V,
			    &vf_data->ifc_int_souwce, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_IFC_INT_SOUWCE_V\n");
		wetuwn wet;
	}

	wet = qm_wwite_wegs(qm, QM_IFC_INT_MASK, &vf_data->ifc_int_mask, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_IFC_INT_MASK\n");
		wetuwn wet;
	}

	wet = qm_wwite_wegs(qm, QM_IFC_INT_SET_V, &vf_data->ifc_int_set, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_IFC_INT_SET_V\n");
		wetuwn wet;
	}

	wet = qm_wwite_wegs(qm, QM_QUE_ISO_CFG_V, &vf_data->que_iso_cfg, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_QUE_ISO_CFG_V\n");
		wetuwn wet;
	}

	wet = qm_wwite_wegs(qm, QM_PAGE_SIZE, &vf_data->page_size, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_PAGE_SIZE\n");
		wetuwn wet;
	}

	/* QM_EQC_DW has 7 wegs */
	wet = qm_wwite_wegs(qm, QM_EQC_DW0, vf_data->qm_eqc_dw, 7);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_EQC_DW\n");
		wetuwn wet;
	}

	/* QM_AEQC_DW has 7 wegs */
	wet = qm_wwite_wegs(qm, QM_AEQC_DW0, vf_data->qm_aeqc_dw, 7);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_AEQC_DW\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void qm_db(stwuct hisi_qm *qm, u16 qn, u8 cmd,
		  u16 index, u8 pwiowity)
{
	u64 doowbeww;
	u64 dbase;
	u16 wandata = 0;

	if (cmd == QM_DOOWBEWW_CMD_SQ || cmd == QM_DOOWBEWW_CMD_CQ)
		dbase = QM_DOOWBEWW_SQ_CQ_BASE_V2;
	ewse
		dbase = QM_DOOWBEWW_EQ_AEQ_BASE_V2;

	doowbeww = qn | ((u64)cmd << QM_DB_CMD_SHIFT_V2) |
		   ((u64)wandata << QM_DB_WAND_SHIFT_V2) |
		   ((u64)index << QM_DB_INDEX_SHIFT_V2)	 |
		   ((u64)pwiowity << QM_DB_PWIOWITY_SHIFT_V2);

	wwiteq(doowbeww, qm->io_base + dbase);
}

static int pf_qm_get_qp_num(stwuct hisi_qm *qm, int vf_id, u32 *wbase)
{
	unsigned int vaw;
	u64 sqc_vft;
	u32 qp_num;
	int wet;

	wet = weadw_wewaxed_poww_timeout(qm->io_base + QM_VFT_CFG_WDY, vaw,
					 vaw & BIT(0), MB_POWW_PEWIOD_US,
					 MB_POWW_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	wwitew(0x1, qm->io_base + QM_VFT_CFG_OP_WW);
	/* 0 mean SQC VFT */
	wwitew(0x0, qm->io_base + QM_VFT_CFG_TYPE);
	wwitew(vf_id, qm->io_base + QM_VFT_CFG);

	wwitew(0x0, qm->io_base + QM_VFT_CFG_WDY);
	wwitew(0x1, qm->io_base + QM_VFT_CFG_OP_ENABWE);

	wet = weadw_wewaxed_poww_timeout(qm->io_base + QM_VFT_CFG_WDY, vaw,
					 vaw & BIT(0), MB_POWW_PEWIOD_US,
					 MB_POWW_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	sqc_vft = weadw(qm->io_base + QM_VFT_CFG_DATA_W) |
		  ((u64)weadw(qm->io_base + QM_VFT_CFG_DATA_H) <<
		  QM_XQC_ADDW_OFFSET);
	*wbase = QM_SQC_VFT_BASE_MASK_V2 &
		  (sqc_vft >> QM_SQC_VFT_BASE_SHIFT_V2);
	qp_num = (QM_SQC_VFT_NUM_MASK_V2 &
		  (sqc_vft >> QM_SQC_VFT_NUM_SHIFT_V2)) + 1;

	wetuwn qp_num;
}

static void qm_dev_cmd_init(stwuct hisi_qm *qm)
{
	/* Cweaw VF communication status wegistews. */
	wwitew(0x1, qm->io_base + QM_IFC_INT_SOUWCE_V);

	/* Enabwe pf and vf communication. */
	wwitew(0x0, qm->io_base + QM_IFC_INT_MASK);
}

static int vf_qm_cache_wb(stwuct hisi_qm *qm)
{
	unsigned int vaw;

	wwitew(0x1, qm->io_base + QM_CACHE_WB_STAWT);
	if (weadw_wewaxed_poww_timeout(qm->io_base + QM_CACHE_WB_DONE,
				       vaw, vaw & BIT(0), MB_POWW_PEWIOD_US,
				       MB_POWW_TIMEOUT_US)) {
		dev_eww(&qm->pdev->dev, "vf QM wwiteback sqc cache faiw\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void vf_qm_fun_weset(stwuct hisi_qm *qm)
{
	int i;

	fow (i = 0; i < qm->qp_num; i++)
		qm_db(qm, i, QM_DOOWBEWW_CMD_SQ, 0, 1);
}

static int vf_qm_func_stop(stwuct hisi_qm *qm)
{
	wetuwn hisi_qm_mb(qm, QM_MB_CMD_PAUSE_QM, 0, 0, 0);
}

static int vf_qm_check_match(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev,
			     stwuct hisi_acc_vf_migwation_fiwe *migf)
{
	stwuct acc_vf_data *vf_data = &migf->vf_data;
	stwuct hisi_qm *vf_qm = &hisi_acc_vdev->vf_qm;
	stwuct hisi_qm *pf_qm = hisi_acc_vdev->pf_qm;
	stwuct device *dev = &vf_qm->pdev->dev;
	u32 que_iso_state;
	int wet;

	if (migf->totaw_wength < QM_MATCH_SIZE || hisi_acc_vdev->match_done)
		wetuwn 0;

	if (vf_data->acc_magic != ACC_DEV_MAGIC) {
		dev_eww(dev, "faiwed to match ACC_DEV_MAGIC\n");
		wetuwn -EINVAW;
	}

	if (vf_data->dev_id != hisi_acc_vdev->vf_dev->device) {
		dev_eww(dev, "faiwed to match VF devices\n");
		wetuwn -EINVAW;
	}

	/* VF qp num check */
	wet = qm_get_vft(vf_qm, &vf_qm->qp_base);
	if (wet <= 0) {
		dev_eww(dev, "faiwed to get vft qp nums\n");
		wetuwn -EINVAW;
	}

	if (wet != vf_data->qp_num) {
		dev_eww(dev, "faiwed to match VF qp num\n");
		wetuwn -EINVAW;
	}

	vf_qm->qp_num = wet;

	/* VF isowation state check */
	wet = qm_wead_wegs(pf_qm, QM_QUE_ISO_CFG_V, &que_iso_state, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_QUE_ISO_CFG_V\n");
		wetuwn wet;
	}

	if (vf_data->que_iso_cfg != que_iso_state) {
		dev_eww(dev, "faiwed to match isowation state\n");
		wetuwn -EINVAW;
	}

	wet = qm_wwite_wegs(vf_qm, QM_VF_STATE, &vf_data->vf_qm_state, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wwite QM_VF_STATE\n");
		wetuwn wet;
	}

	hisi_acc_vdev->vf_qm_state = vf_data->vf_qm_state;
	hisi_acc_vdev->match_done = twue;
	wetuwn 0;
}

static int vf_qm_get_match_data(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev,
				stwuct acc_vf_data *vf_data)
{
	stwuct hisi_qm *pf_qm = hisi_acc_vdev->pf_qm;
	stwuct device *dev = &pf_qm->pdev->dev;
	int vf_id = hisi_acc_vdev->vf_id;
	int wet;

	vf_data->acc_magic = ACC_DEV_MAGIC;
	/* Save device id */
	vf_data->dev_id = hisi_acc_vdev->vf_dev->device;

	/* VF qp num save fwom PF */
	wet = pf_qm_get_qp_num(pf_qm, vf_id, &vf_data->qp_base);
	if (wet <= 0) {
		dev_eww(dev, "faiwed to get vft qp nums!\n");
		wetuwn -EINVAW;
	}

	vf_data->qp_num = wet;

	/* VF isowation state save fwom PF */
	wet = qm_wead_wegs(pf_qm, QM_QUE_ISO_CFG_V, &vf_data->que_iso_cfg, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wead QM_QUE_ISO_CFG_V!\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int vf_qm_woad_data(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev,
			   stwuct hisi_acc_vf_migwation_fiwe *migf)
{
	stwuct hisi_qm *qm = &hisi_acc_vdev->vf_qm;
	stwuct device *dev = &qm->pdev->dev;
	stwuct acc_vf_data *vf_data = &migf->vf_data;
	int wet;

	/* Wetuwn if onwy match data was twansfewwed */
	if (migf->totaw_wength == QM_MATCH_SIZE)
		wetuwn 0;

	if (migf->totaw_wength < sizeof(stwuct acc_vf_data))
		wetuwn -EINVAW;

	qm->eqe_dma = vf_data->eqe_dma;
	qm->aeqe_dma = vf_data->aeqe_dma;
	qm->sqc_dma = vf_data->sqc_dma;
	qm->cqc_dma = vf_data->cqc_dma;

	qm->qp_base = vf_data->qp_base;
	qm->qp_num = vf_data->qp_num;

	wet = qm_set_wegs(qm, vf_data);
	if (wet) {
		dev_eww(dev, "set VF wegs faiwed\n");
		wetuwn wet;
	}

	wet = hisi_qm_mb(qm, QM_MB_CMD_SQC_BT, qm->sqc_dma, 0, 0);
	if (wet) {
		dev_eww(dev, "set sqc faiwed\n");
		wetuwn wet;
	}

	wet = hisi_qm_mb(qm, QM_MB_CMD_CQC_BT, qm->cqc_dma, 0, 0);
	if (wet) {
		dev_eww(dev, "set cqc faiwed\n");
		wetuwn wet;
	}

	qm_dev_cmd_init(qm);
	wetuwn 0;
}

static int vf_qm_state_save(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev,
			    stwuct hisi_acc_vf_migwation_fiwe *migf)
{
	stwuct acc_vf_data *vf_data = &migf->vf_data;
	stwuct hisi_qm *vf_qm = &hisi_acc_vdev->vf_qm;
	stwuct device *dev = &vf_qm->pdev->dev;
	int wet;

	if (unwikewy(qm_wait_dev_not_weady(vf_qm))) {
		/* Update state and wetuwn with match data */
		vf_data->vf_qm_state = QM_NOT_WEADY;
		hisi_acc_vdev->vf_qm_state = vf_data->vf_qm_state;
		migf->totaw_wength = QM_MATCH_SIZE;
		wetuwn 0;
	}

	vf_data->vf_qm_state = QM_WEADY;
	hisi_acc_vdev->vf_qm_state = vf_data->vf_qm_state;

	wet = vf_qm_cache_wb(vf_qm);
	if (wet) {
		dev_eww(dev, "faiwed to wwiteback QM Cache!\n");
		wetuwn wet;
	}

	wet = qm_get_wegs(vf_qm, vf_data);
	if (wet)
		wetuwn -EINVAW;

	/* Evewy weg is 32 bit, the dma addwess is 64 bit. */
	vf_data->eqe_dma = vf_data->qm_eqc_dw[1];
	vf_data->eqe_dma <<= QM_XQC_ADDW_OFFSET;
	vf_data->eqe_dma |= vf_data->qm_eqc_dw[0];
	vf_data->aeqe_dma = vf_data->qm_aeqc_dw[1];
	vf_data->aeqe_dma <<= QM_XQC_ADDW_OFFSET;
	vf_data->aeqe_dma |= vf_data->qm_aeqc_dw[0];

	/* Thwough SQC_BT/CQC_BT to get sqc and cqc addwess */
	wet = qm_get_sqc(vf_qm, &vf_data->sqc_dma);
	if (wet) {
		dev_eww(dev, "faiwed to wead SQC addw!\n");
		wetuwn -EINVAW;
	}

	wet = qm_get_cqc(vf_qm, &vf_data->cqc_dma);
	if (wet) {
		dev_eww(dev, "faiwed to wead CQC addw!\n");
		wetuwn -EINVAW;
	}

	migf->totaw_wength = sizeof(stwuct acc_vf_data);
	wetuwn 0;
}

static stwuct hisi_acc_vf_cowe_device *hisi_acc_dwvdata(stwuct pci_dev *pdev)
{
	stwuct vfio_pci_cowe_device *cowe_device = dev_get_dwvdata(&pdev->dev);

	wetuwn containew_of(cowe_device, stwuct hisi_acc_vf_cowe_device,
			    cowe_device);
}

/* Check the PF's WAS state and Function INT state */
static int
hisi_acc_check_int_state(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	stwuct hisi_qm *vfqm = &hisi_acc_vdev->vf_qm;
	stwuct hisi_qm *qm = hisi_acc_vdev->pf_qm;
	stwuct pci_dev *vf_pdev = hisi_acc_vdev->vf_dev;
	stwuct device *dev = &qm->pdev->dev;
	u32 state;

	/* Check WAS state */
	state = qm_check_weg_state(qm, QM_ABNOWMAW_INT_STATUS);
	if (state) {
		dev_eww(dev, "faiwed to check QM WAS state!\n");
		wetuwn -EBUSY;
	}

	/* Check Function Communication state between PF and VF */
	state = qm_check_weg_state(vfqm, QM_IFC_INT_STATUS);
	if (state) {
		dev_eww(dev, "faiwed to check QM IFC INT state!\n");
		wetuwn -EBUSY;
	}
	state = qm_check_weg_state(vfqm, QM_IFC_INT_SET_V);
	if (state) {
		dev_eww(dev, "faiwed to check QM IFC INT SET state!\n");
		wetuwn -EBUSY;
	}

	/* Check submoduwe task state */
	switch (vf_pdev->device) {
	case PCI_DEVICE_ID_HUAWEI_SEC_VF:
		state = qm_check_weg_state(qm, SEC_COWE_INT_STATUS);
		if (state) {
			dev_eww(dev, "faiwed to check QM SEC Cowe INT state!\n");
			wetuwn -EBUSY;
		}
		wetuwn 0;
	case PCI_DEVICE_ID_HUAWEI_HPWE_VF:
		state = qm_check_weg_state(qm, HPWE_HAC_INT_STATUS);
		if (state) {
			dev_eww(dev, "faiwed to check QM HPWE HAC INT state!\n");
			wetuwn -EBUSY;
		}
		wetuwn 0;
	case PCI_DEVICE_ID_HUAWEI_ZIP_VF:
		state = qm_check_weg_state(qm, HZIP_COWE_INT_STATUS);
		if (state) {
			dev_eww(dev, "faiwed to check QM ZIP Cowe INT state!\n");
			wetuwn -EBUSY;
		}
		wetuwn 0;
	defauwt:
		dev_eww(dev, "faiwed to detect acc moduwe type!\n");
		wetuwn -EINVAW;
	}
}

static void hisi_acc_vf_disabwe_fd(stwuct hisi_acc_vf_migwation_fiwe *migf)
{
	mutex_wock(&migf->wock);
	migf->disabwed = twue;
	migf->totaw_wength = 0;
	migf->fiwp->f_pos = 0;
	mutex_unwock(&migf->wock);
}

static void hisi_acc_vf_disabwe_fds(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	if (hisi_acc_vdev->wesuming_migf) {
		hisi_acc_vf_disabwe_fd(hisi_acc_vdev->wesuming_migf);
		fput(hisi_acc_vdev->wesuming_migf->fiwp);
		hisi_acc_vdev->wesuming_migf = NUWW;
	}

	if (hisi_acc_vdev->saving_migf) {
		hisi_acc_vf_disabwe_fd(hisi_acc_vdev->saving_migf);
		fput(hisi_acc_vdev->saving_migf->fiwp);
		hisi_acc_vdev->saving_migf = NUWW;
	}
}

/*
 * This function is cawwed in aww state_mutex unwock cases to
 * handwe a 'defewwed_weset' if exists.
 */
static void
hisi_acc_vf_state_mutex_unwock(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
again:
	spin_wock(&hisi_acc_vdev->weset_wock);
	if (hisi_acc_vdev->defewwed_weset) {
		hisi_acc_vdev->defewwed_weset = fawse;
		spin_unwock(&hisi_acc_vdev->weset_wock);
		hisi_acc_vdev->vf_qm_state = QM_NOT_WEADY;
		hisi_acc_vdev->mig_state = VFIO_DEVICE_STATE_WUNNING;
		hisi_acc_vf_disabwe_fds(hisi_acc_vdev);
		goto again;
	}
	mutex_unwock(&hisi_acc_vdev->state_mutex);
	spin_unwock(&hisi_acc_vdev->weset_wock);
}

static void hisi_acc_vf_stawt_device(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	stwuct hisi_qm *vf_qm = &hisi_acc_vdev->vf_qm;

	if (hisi_acc_vdev->vf_qm_state != QM_WEADY)
		wetuwn;

	/* Make suwe the device is enabwed */
	qm_dev_cmd_init(vf_qm);

	vf_qm_fun_weset(vf_qm);
}

static int hisi_acc_vf_woad_state(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	stwuct device *dev = &hisi_acc_vdev->vf_dev->dev;
	stwuct hisi_acc_vf_migwation_fiwe *migf = hisi_acc_vdev->wesuming_migf;
	int wet;

	/* Wecovew data to VF */
	wet = vf_qm_woad_data(hisi_acc_vdev, migf);
	if (wet) {
		dev_eww(dev, "faiwed to wecovew the VF!\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int hisi_acc_vf_wewease_fiwe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct hisi_acc_vf_migwation_fiwe *migf = fiwp->pwivate_data;

	hisi_acc_vf_disabwe_fd(migf);
	mutex_destwoy(&migf->wock);
	kfwee(migf);
	wetuwn 0;
}

static ssize_t hisi_acc_vf_wesume_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
					size_t wen, woff_t *pos)
{
	stwuct hisi_acc_vf_migwation_fiwe *migf = fiwp->pwivate_data;
	u8 *vf_data = (u8 *)&migf->vf_data;
	woff_t wequested_wength;
	ssize_t done = 0;
	int wet;

	if (pos)
		wetuwn -ESPIPE;
	pos = &fiwp->f_pos;

	if (*pos < 0 ||
	    check_add_ovewfwow((woff_t)wen, *pos, &wequested_wength))
		wetuwn -EINVAW;

	if (wequested_wength > sizeof(stwuct acc_vf_data))
		wetuwn -ENOMEM;

	mutex_wock(&migf->wock);
	if (migf->disabwed) {
		done = -ENODEV;
		goto out_unwock;
	}

	wet = copy_fwom_usew(vf_data + *pos, buf, wen);
	if (wet) {
		done = -EFAUWT;
		goto out_unwock;
	}
	*pos += wen;
	done = wen;
	migf->totaw_wength += wen;

	wet = vf_qm_check_match(migf->hisi_acc_vdev, migf);
	if (wet)
		done = -EFAUWT;
out_unwock:
	mutex_unwock(&migf->wock);
	wetuwn done;
}

static const stwuct fiwe_opewations hisi_acc_vf_wesume_fops = {
	.ownew = THIS_MODUWE,
	.wwite = hisi_acc_vf_wesume_wwite,
	.wewease = hisi_acc_vf_wewease_fiwe,
	.wwseek = no_wwseek,
};

static stwuct hisi_acc_vf_migwation_fiwe *
hisi_acc_vf_pci_wesume(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	stwuct hisi_acc_vf_migwation_fiwe *migf;

	migf = kzawwoc(sizeof(*migf), GFP_KEWNEW_ACCOUNT);
	if (!migf)
		wetuwn EWW_PTW(-ENOMEM);

	migf->fiwp = anon_inode_getfiwe("hisi_acc_vf_mig", &hisi_acc_vf_wesume_fops, migf,
					O_WWONWY);
	if (IS_EWW(migf->fiwp)) {
		int eww = PTW_EWW(migf->fiwp);

		kfwee(migf);
		wetuwn EWW_PTW(eww);
	}

	stweam_open(migf->fiwp->f_inode, migf->fiwp);
	mutex_init(&migf->wock);
	migf->hisi_acc_vdev = hisi_acc_vdev;
	wetuwn migf;
}

static wong hisi_acc_vf_pwecopy_ioctw(stwuct fiwe *fiwp,
				      unsigned int cmd, unsigned wong awg)
{
	stwuct hisi_acc_vf_migwation_fiwe *migf = fiwp->pwivate_data;
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev = migf->hisi_acc_vdev;
	woff_t *pos = &fiwp->f_pos;
	stwuct vfio_pwecopy_info info;
	unsigned wong minsz;
	int wet;

	if (cmd != VFIO_MIG_GET_PWECOPY_INFO)
		wetuwn -ENOTTY;

	minsz = offsetofend(stwuct vfio_pwecopy_info, diwty_bytes);

	if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;
	if (info.awgsz < minsz)
		wetuwn -EINVAW;

	mutex_wock(&hisi_acc_vdev->state_mutex);
	if (hisi_acc_vdev->mig_state != VFIO_DEVICE_STATE_PWE_COPY) {
		mutex_unwock(&hisi_acc_vdev->state_mutex);
		wetuwn -EINVAW;
	}

	mutex_wock(&migf->wock);

	if (migf->disabwed) {
		wet = -ENODEV;
		goto out;
	}

	if (*pos > migf->totaw_wength) {
		wet = -EINVAW;
		goto out;
	}

	info.diwty_bytes = 0;
	info.initiaw_bytes = migf->totaw_wength - *pos;

	wet = copy_to_usew((void __usew *)awg, &info, minsz) ? -EFAUWT : 0;
out:
	mutex_unwock(&migf->wock);
	mutex_unwock(&hisi_acc_vdev->state_mutex);
	wetuwn wet;
}

static ssize_t hisi_acc_vf_save_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t wen,
				     woff_t *pos)
{
	stwuct hisi_acc_vf_migwation_fiwe *migf = fiwp->pwivate_data;
	ssize_t done = 0;
	int wet;

	if (pos)
		wetuwn -ESPIPE;
	pos = &fiwp->f_pos;

	mutex_wock(&migf->wock);
	if (*pos > migf->totaw_wength) {
		done = -EINVAW;
		goto out_unwock;
	}

	if (migf->disabwed) {
		done = -ENODEV;
		goto out_unwock;
	}

	wen = min_t(size_t, migf->totaw_wength - *pos, wen);
	if (wen) {
		u8 *vf_data = (u8 *)&migf->vf_data;

		wet = copy_to_usew(buf, vf_data + *pos, wen);
		if (wet) {
			done = -EFAUWT;
			goto out_unwock;
		}
		*pos += wen;
		done = wen;
	}
out_unwock:
	mutex_unwock(&migf->wock);
	wetuwn done;
}

static const stwuct fiwe_opewations hisi_acc_vf_save_fops = {
	.ownew = THIS_MODUWE,
	.wead = hisi_acc_vf_save_wead,
	.unwocked_ioctw = hisi_acc_vf_pwecopy_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.wewease = hisi_acc_vf_wewease_fiwe,
	.wwseek = no_wwseek,
};

static stwuct hisi_acc_vf_migwation_fiwe *
hisi_acc_open_saving_migf(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	stwuct hisi_acc_vf_migwation_fiwe *migf;
	int wet;

	migf = kzawwoc(sizeof(*migf), GFP_KEWNEW_ACCOUNT);
	if (!migf)
		wetuwn EWW_PTW(-ENOMEM);

	migf->fiwp = anon_inode_getfiwe("hisi_acc_vf_mig", &hisi_acc_vf_save_fops, migf,
					O_WDONWY);
	if (IS_EWW(migf->fiwp)) {
		int eww = PTW_EWW(migf->fiwp);

		kfwee(migf);
		wetuwn EWW_PTW(eww);
	}

	stweam_open(migf->fiwp->f_inode, migf->fiwp);
	mutex_init(&migf->wock);
	migf->hisi_acc_vdev = hisi_acc_vdev;

	wet = vf_qm_get_match_data(hisi_acc_vdev, &migf->vf_data);
	if (wet) {
		fput(migf->fiwp);
		wetuwn EWW_PTW(wet);
	}

	wetuwn migf;
}

static stwuct hisi_acc_vf_migwation_fiwe *
hisi_acc_vf_pwe_copy(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	stwuct hisi_acc_vf_migwation_fiwe *migf;

	migf = hisi_acc_open_saving_migf(hisi_acc_vdev);
	if (IS_EWW(migf))
		wetuwn migf;

	migf->totaw_wength = QM_MATCH_SIZE;
	wetuwn migf;
}

static stwuct hisi_acc_vf_migwation_fiwe *
hisi_acc_vf_stop_copy(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev, boow open)
{
	int wet;
	stwuct hisi_acc_vf_migwation_fiwe *migf = NUWW;

	if (open) {
		/*
		 * Usewspace didn't use PWECOPY suppowt. Hence saving_migf
		 * is not opened yet.
		 */
		migf = hisi_acc_open_saving_migf(hisi_acc_vdev);
		if (IS_EWW(migf))
			wetuwn migf;
	} ewse {
		migf = hisi_acc_vdev->saving_migf;
	}

	wet = vf_qm_state_save(hisi_acc_vdev, migf);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn open ? migf : NUWW;
}

static int hisi_acc_vf_stop_device(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	stwuct device *dev = &hisi_acc_vdev->vf_dev->dev;
	stwuct hisi_qm *vf_qm = &hisi_acc_vdev->vf_qm;
	int wet;

	wet = vf_qm_func_stop(vf_qm);
	if (wet) {
		dev_eww(dev, "faiwed to stop QM VF function!\n");
		wetuwn wet;
	}

	wet = hisi_acc_check_int_state(hisi_acc_vdev);
	if (wet) {
		dev_eww(dev, "faiwed to check QM INT state!\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static stwuct fiwe *
hisi_acc_vf_set_device_state(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev,
			     u32 new)
{
	u32 cuw = hisi_acc_vdev->mig_state;
	int wet;

	if (cuw == VFIO_DEVICE_STATE_WUNNING && new == VFIO_DEVICE_STATE_PWE_COPY) {
		stwuct hisi_acc_vf_migwation_fiwe *migf;

		migf = hisi_acc_vf_pwe_copy(hisi_acc_vdev);
		if (IS_EWW(migf))
			wetuwn EWW_CAST(migf);
		get_fiwe(migf->fiwp);
		hisi_acc_vdev->saving_migf = migf;
		wetuwn migf->fiwp;
	}

	if (cuw == VFIO_DEVICE_STATE_PWE_COPY && new == VFIO_DEVICE_STATE_STOP_COPY) {
		stwuct hisi_acc_vf_migwation_fiwe *migf;

		wet = hisi_acc_vf_stop_device(hisi_acc_vdev);
		if (wet)
			wetuwn EWW_PTW(wet);

		migf = hisi_acc_vf_stop_copy(hisi_acc_vdev, fawse);
		if (IS_EWW(migf))
			wetuwn EWW_CAST(migf);

		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_WUNNING && new == VFIO_DEVICE_STATE_STOP) {
		wet = hisi_acc_vf_stop_device(hisi_acc_vdev);
		if (wet)
			wetuwn EWW_PTW(wet);
		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_STOP && new == VFIO_DEVICE_STATE_STOP_COPY) {
		stwuct hisi_acc_vf_migwation_fiwe *migf;

		migf = hisi_acc_vf_stop_copy(hisi_acc_vdev, twue);
		if (IS_EWW(migf))
			wetuwn EWW_CAST(migf);
		get_fiwe(migf->fiwp);
		hisi_acc_vdev->saving_migf = migf;
		wetuwn migf->fiwp;
	}

	if ((cuw == VFIO_DEVICE_STATE_STOP_COPY && new == VFIO_DEVICE_STATE_STOP)) {
		hisi_acc_vf_disabwe_fds(hisi_acc_vdev);
		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_STOP && new == VFIO_DEVICE_STATE_WESUMING) {
		stwuct hisi_acc_vf_migwation_fiwe *migf;

		migf = hisi_acc_vf_pci_wesume(hisi_acc_vdev);
		if (IS_EWW(migf))
			wetuwn EWW_CAST(migf);
		get_fiwe(migf->fiwp);
		hisi_acc_vdev->wesuming_migf = migf;
		wetuwn migf->fiwp;
	}

	if (cuw == VFIO_DEVICE_STATE_WESUMING && new == VFIO_DEVICE_STATE_STOP) {
		wet = hisi_acc_vf_woad_state(hisi_acc_vdev);
		if (wet)
			wetuwn EWW_PTW(wet);
		hisi_acc_vf_disabwe_fds(hisi_acc_vdev);
		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_PWE_COPY && new == VFIO_DEVICE_STATE_WUNNING) {
		hisi_acc_vf_disabwe_fds(hisi_acc_vdev);
		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_STOP && new == VFIO_DEVICE_STATE_WUNNING) {
		hisi_acc_vf_stawt_device(hisi_acc_vdev);
		wetuwn NUWW;
	}

	/*
	 * vfio_mig_get_next_state() does not use awcs othew than the above
	 */
	WAWN_ON(twue);
	wetuwn EWW_PTW(-EINVAW);
}

static stwuct fiwe *
hisi_acc_vfio_pci_set_device_state(stwuct vfio_device *vdev,
				   enum vfio_device_mig_state new_state)
{
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev = containew_of(vdev,
			stwuct hisi_acc_vf_cowe_device, cowe_device.vdev);
	enum vfio_device_mig_state next_state;
	stwuct fiwe *wes = NUWW;
	int wet;

	mutex_wock(&hisi_acc_vdev->state_mutex);
	whiwe (new_state != hisi_acc_vdev->mig_state) {
		wet = vfio_mig_get_next_state(vdev,
					      hisi_acc_vdev->mig_state,
					      new_state, &next_state);
		if (wet) {
			wes = EWW_PTW(-EINVAW);
			bweak;
		}

		wes = hisi_acc_vf_set_device_state(hisi_acc_vdev, next_state);
		if (IS_EWW(wes))
			bweak;
		hisi_acc_vdev->mig_state = next_state;
		if (WAWN_ON(wes && new_state != hisi_acc_vdev->mig_state)) {
			fput(wes);
			wes = EWW_PTW(-EINVAW);
			bweak;
		}
	}
	hisi_acc_vf_state_mutex_unwock(hisi_acc_vdev);
	wetuwn wes;
}

static int
hisi_acc_vfio_pci_get_data_size(stwuct vfio_device *vdev,
				unsigned wong *stop_copy_wength)
{
	*stop_copy_wength = sizeof(stwuct acc_vf_data);
	wetuwn 0;
}

static int
hisi_acc_vfio_pci_get_device_state(stwuct vfio_device *vdev,
				   enum vfio_device_mig_state *cuww_state)
{
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev = containew_of(vdev,
			stwuct hisi_acc_vf_cowe_device, cowe_device.vdev);

	mutex_wock(&hisi_acc_vdev->state_mutex);
	*cuww_state = hisi_acc_vdev->mig_state;
	hisi_acc_vf_state_mutex_unwock(hisi_acc_vdev);
	wetuwn 0;
}

static void hisi_acc_vf_pci_aew_weset_done(stwuct pci_dev *pdev)
{
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev = hisi_acc_dwvdata(pdev);

	if (hisi_acc_vdev->cowe_device.vdev.migwation_fwags !=
				VFIO_MIGWATION_STOP_COPY)
		wetuwn;

	/*
	 * As the highew VFIO wayews awe howding wocks acwoss weset and using
	 * those same wocks with the mm_wock we need to pwevent ABBA deadwock
	 * with the state_mutex and mm_wock.
	 * In case the state_mutex was taken awweady we defew the cweanup wowk
	 * to the unwock fwow of the othew wunning context.
	 */
	spin_wock(&hisi_acc_vdev->weset_wock);
	hisi_acc_vdev->defewwed_weset = twue;
	if (!mutex_twywock(&hisi_acc_vdev->state_mutex)) {
		spin_unwock(&hisi_acc_vdev->weset_wock);
		wetuwn;
	}
	spin_unwock(&hisi_acc_vdev->weset_wock);
	hisi_acc_vf_state_mutex_unwock(hisi_acc_vdev);
}

static int hisi_acc_vf_qm_init(stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev)
{
	stwuct vfio_pci_cowe_device *vdev = &hisi_acc_vdev->cowe_device;
	stwuct hisi_qm *vf_qm = &hisi_acc_vdev->vf_qm;
	stwuct pci_dev *vf_dev = vdev->pdev;

	/*
	 * ACC VF dev BAW2 wegion consists of both functionaw wegistew space
	 * and migwation contwow wegistew space. Fow migwation to wowk, we
	 * need access to both. Hence, we map the entiwe BAW2 wegion hewe.
	 * But unnecessawiwy exposing the migwation BAW wegion to the Guest
	 * has the potentiaw to pwevent/cowwupt the Guest migwation. Hence,
	 * we westwict access to the migwation contwow space fwom
	 * Guest(Pwease see mmap/ioctw/wead/wwite ovewwide functions).
	 *
	 * Pwease note that it is OK to expose the entiwe VF BAW if migwation
	 * is not suppowted ow wequiwed as this cannot affect the ACC PF
	 * configuwations.
	 *
	 * Awso the HiSiwicon ACC VF devices suppowted by this dwivew on
	 * HiSiwicon hawdwawe pwatfowms awe integwated end point devices
	 * and the pwatfowm wacks the capabiwity to pewfowm any PCIe P2P
	 * between these devices.
	 */

	vf_qm->io_base =
		iowemap(pci_wesouwce_stawt(vf_dev, VFIO_PCI_BAW2_WEGION_INDEX),
			pci_wesouwce_wen(vf_dev, VFIO_PCI_BAW2_WEGION_INDEX));
	if (!vf_qm->io_base)
		wetuwn -EIO;

	vf_qm->fun_type = QM_HW_VF;
	vf_qm->pdev = vf_dev;
	mutex_init(&vf_qm->maiwbox_wock);

	wetuwn 0;
}

static stwuct hisi_qm *hisi_acc_get_pf_qm(stwuct pci_dev *pdev)
{
	stwuct hisi_qm	*pf_qm;
	stwuct pci_dwivew *pf_dwivew;

	if (!pdev->is_viwtfn)
		wetuwn NUWW;

	switch (pdev->device) {
	case PCI_DEVICE_ID_HUAWEI_SEC_VF:
		pf_dwivew = hisi_sec_get_pf_dwivew();
		bweak;
	case PCI_DEVICE_ID_HUAWEI_HPWE_VF:
		pf_dwivew = hisi_hpwe_get_pf_dwivew();
		bweak;
	case PCI_DEVICE_ID_HUAWEI_ZIP_VF:
		pf_dwivew = hisi_zip_get_pf_dwivew();
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	if (!pf_dwivew)
		wetuwn NUWW;

	pf_qm = pci_iov_get_pf_dwvdata(pdev, pf_dwivew);

	wetuwn !IS_EWW(pf_qm) ? pf_qm : NUWW;
}

static int hisi_acc_pci_ww_access_check(stwuct vfio_device *cowe_vdev,
					size_t count, woff_t *ppos,
					size_t *new_count)
{
	unsigned int index = VFIO_PCI_OFFSET_TO_INDEX(*ppos);
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);

	if (index == VFIO_PCI_BAW2_WEGION_INDEX) {
		woff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;
		wesouwce_size_t end = pci_wesouwce_wen(vdev->pdev, index) / 2;

		/* Check if access is fow migwation contwow wegion */
		if (pos >= end)
			wetuwn -EINVAW;

		*new_count = min(count, (size_t)(end - pos));
	}

	wetuwn 0;
}

static int hisi_acc_vfio_pci_mmap(stwuct vfio_device *cowe_vdev,
				  stwuct vm_awea_stwuct *vma)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);
	unsigned int index;

	index = vma->vm_pgoff >> (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT);
	if (index == VFIO_PCI_BAW2_WEGION_INDEX) {
		u64 weq_wen, pgoff, weq_stawt;
		wesouwce_size_t end = pci_wesouwce_wen(vdev->pdev, index) / 2;

		weq_wen = vma->vm_end - vma->vm_stawt;
		pgoff = vma->vm_pgoff &
			((1U << (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
		weq_stawt = pgoff << PAGE_SHIFT;

		if (weq_stawt + weq_wen > end)
			wetuwn -EINVAW;
	}

	wetuwn vfio_pci_cowe_mmap(cowe_vdev, vma);
}

static ssize_t hisi_acc_vfio_pci_wwite(stwuct vfio_device *cowe_vdev,
				       const chaw __usew *buf, size_t count,
				       woff_t *ppos)
{
	size_t new_count = count;
	int wet;

	wet = hisi_acc_pci_ww_access_check(cowe_vdev, count, ppos, &new_count);
	if (wet)
		wetuwn wet;

	wetuwn vfio_pci_cowe_wwite(cowe_vdev, buf, new_count, ppos);
}

static ssize_t hisi_acc_vfio_pci_wead(stwuct vfio_device *cowe_vdev,
				      chaw __usew *buf, size_t count,
				      woff_t *ppos)
{
	size_t new_count = count;
	int wet;

	wet = hisi_acc_pci_ww_access_check(cowe_vdev, count, ppos, &new_count);
	if (wet)
		wetuwn wet;

	wetuwn vfio_pci_cowe_wead(cowe_vdev, buf, new_count, ppos);
}

static wong hisi_acc_vfio_pci_ioctw(stwuct vfio_device *cowe_vdev, unsigned int cmd,
				    unsigned wong awg)
{
	if (cmd == VFIO_DEVICE_GET_WEGION_INFO) {
		stwuct vfio_pci_cowe_device *vdev =
			containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);
		stwuct pci_dev *pdev = vdev->pdev;
		stwuct vfio_wegion_info info;
		unsigned wong minsz;

		minsz = offsetofend(stwuct vfio_wegion_info, offset);

		if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (info.awgsz < minsz)
			wetuwn -EINVAW;

		if (info.index == VFIO_PCI_BAW2_WEGION_INDEX) {
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);

			/*
			 * ACC VF dev BAW2 wegion consists of both functionaw
			 * wegistew space and migwation contwow wegistew space.
			 * Wepowt onwy the functionaw wegion to Guest.
			 */
			info.size = pci_wesouwce_wen(pdev, info.index) / 2;

			info.fwags = VFIO_WEGION_INFO_FWAG_WEAD |
					VFIO_WEGION_INFO_FWAG_WWITE |
					VFIO_WEGION_INFO_FWAG_MMAP;

			wetuwn copy_to_usew((void __usew *)awg, &info, minsz) ?
					    -EFAUWT : 0;
		}
	}
	wetuwn vfio_pci_cowe_ioctw(cowe_vdev, cmd, awg);
}

static int hisi_acc_vfio_pci_open_device(stwuct vfio_device *cowe_vdev)
{
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev = containew_of(cowe_vdev,
			stwuct hisi_acc_vf_cowe_device, cowe_device.vdev);
	stwuct vfio_pci_cowe_device *vdev = &hisi_acc_vdev->cowe_device;
	int wet;

	wet = vfio_pci_cowe_enabwe(vdev);
	if (wet)
		wetuwn wet;

	if (cowe_vdev->mig_ops) {
		wet = hisi_acc_vf_qm_init(hisi_acc_vdev);
		if (wet) {
			vfio_pci_cowe_disabwe(vdev);
			wetuwn wet;
		}
		hisi_acc_vdev->mig_state = VFIO_DEVICE_STATE_WUNNING;
	}

	vfio_pci_cowe_finish_enabwe(vdev);
	wetuwn 0;
}

static void hisi_acc_vfio_pci_cwose_device(stwuct vfio_device *cowe_vdev)
{
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev = containew_of(cowe_vdev,
			stwuct hisi_acc_vf_cowe_device, cowe_device.vdev);
	stwuct hisi_qm *vf_qm = &hisi_acc_vdev->vf_qm;

	iounmap(vf_qm->io_base);
	vfio_pci_cowe_cwose_device(cowe_vdev);
}

static const stwuct vfio_migwation_ops hisi_acc_vfio_pci_migwn_state_ops = {
	.migwation_set_state = hisi_acc_vfio_pci_set_device_state,
	.migwation_get_state = hisi_acc_vfio_pci_get_device_state,
	.migwation_get_data_size = hisi_acc_vfio_pci_get_data_size,
};

static int hisi_acc_vfio_pci_migwn_init_dev(stwuct vfio_device *cowe_vdev)
{
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev = containew_of(cowe_vdev,
			stwuct hisi_acc_vf_cowe_device, cowe_device.vdev);
	stwuct pci_dev *pdev = to_pci_dev(cowe_vdev->dev);
	stwuct hisi_qm *pf_qm = hisi_acc_get_pf_qm(pdev);

	hisi_acc_vdev->vf_id = pci_iov_vf_id(pdev) + 1;
	hisi_acc_vdev->pf_qm = pf_qm;
	hisi_acc_vdev->vf_dev = pdev;
	mutex_init(&hisi_acc_vdev->state_mutex);

	cowe_vdev->migwation_fwags = VFIO_MIGWATION_STOP_COPY | VFIO_MIGWATION_PWE_COPY;
	cowe_vdev->mig_ops = &hisi_acc_vfio_pci_migwn_state_ops;

	wetuwn vfio_pci_cowe_init_dev(cowe_vdev);
}

static const stwuct vfio_device_ops hisi_acc_vfio_pci_migwn_ops = {
	.name = "hisi-acc-vfio-pci-migwation",
	.init = hisi_acc_vfio_pci_migwn_init_dev,
	.wewease = vfio_pci_cowe_wewease_dev,
	.open_device = hisi_acc_vfio_pci_open_device,
	.cwose_device = hisi_acc_vfio_pci_cwose_device,
	.ioctw = hisi_acc_vfio_pci_ioctw,
	.device_featuwe = vfio_pci_cowe_ioctw_featuwe,
	.wead = hisi_acc_vfio_pci_wead,
	.wwite = hisi_acc_vfio_pci_wwite,
	.mmap = hisi_acc_vfio_pci_mmap,
	.wequest = vfio_pci_cowe_wequest,
	.match = vfio_pci_cowe_match,
	.bind_iommufd = vfio_iommufd_physicaw_bind,
	.unbind_iommufd = vfio_iommufd_physicaw_unbind,
	.attach_ioas = vfio_iommufd_physicaw_attach_ioas,
	.detach_ioas = vfio_iommufd_physicaw_detach_ioas,
};

static const stwuct vfio_device_ops hisi_acc_vfio_pci_ops = {
	.name = "hisi-acc-vfio-pci",
	.init = vfio_pci_cowe_init_dev,
	.wewease = vfio_pci_cowe_wewease_dev,
	.open_device = hisi_acc_vfio_pci_open_device,
	.cwose_device = vfio_pci_cowe_cwose_device,
	.ioctw = vfio_pci_cowe_ioctw,
	.device_featuwe = vfio_pci_cowe_ioctw_featuwe,
	.wead = vfio_pci_cowe_wead,
	.wwite = vfio_pci_cowe_wwite,
	.mmap = vfio_pci_cowe_mmap,
	.wequest = vfio_pci_cowe_wequest,
	.match = vfio_pci_cowe_match,
	.bind_iommufd = vfio_iommufd_physicaw_bind,
	.unbind_iommufd = vfio_iommufd_physicaw_unbind,
	.attach_ioas = vfio_iommufd_physicaw_attach_ioas,
	.detach_ioas = vfio_iommufd_physicaw_detach_ioas,
};

static int hisi_acc_vfio_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev;
	const stwuct vfio_device_ops *ops = &hisi_acc_vfio_pci_ops;
	stwuct hisi_qm *pf_qm;
	int vf_id;
	int wet;

	pf_qm = hisi_acc_get_pf_qm(pdev);
	if (pf_qm && pf_qm->vew >= QM_HW_V3) {
		vf_id = pci_iov_vf_id(pdev);
		if (vf_id >= 0)
			ops = &hisi_acc_vfio_pci_migwn_ops;
		ewse
			pci_wawn(pdev, "migwation suppowt faiwed, continue with genewic intewface\n");
	}

	hisi_acc_vdev = vfio_awwoc_device(hisi_acc_vf_cowe_device,
					  cowe_device.vdev, &pdev->dev, ops);
	if (IS_EWW(hisi_acc_vdev))
		wetuwn PTW_EWW(hisi_acc_vdev);

	dev_set_dwvdata(&pdev->dev, &hisi_acc_vdev->cowe_device);
	wet = vfio_pci_cowe_wegistew_device(&hisi_acc_vdev->cowe_device);
	if (wet)
		goto out_put_vdev;
	wetuwn 0;

out_put_vdev:
	vfio_put_device(&hisi_acc_vdev->cowe_device.vdev);
	wetuwn wet;
}

static void hisi_acc_vfio_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct hisi_acc_vf_cowe_device *hisi_acc_vdev = hisi_acc_dwvdata(pdev);

	vfio_pci_cowe_unwegistew_device(&hisi_acc_vdev->cowe_device);
	vfio_put_device(&hisi_acc_vdev->cowe_device.vdev);
}

static const stwuct pci_device_id hisi_acc_vfio_pci_tabwe[] = {
	{ PCI_DWIVEW_OVEWWIDE_DEVICE_VFIO(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_SEC_VF) },
	{ PCI_DWIVEW_OVEWWIDE_DEVICE_VFIO(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_HPWE_VF) },
	{ PCI_DWIVEW_OVEWWIDE_DEVICE_VFIO(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_ZIP_VF) },
	{ }
};

MODUWE_DEVICE_TABWE(pci, hisi_acc_vfio_pci_tabwe);

static const stwuct pci_ewwow_handwews hisi_acc_vf_eww_handwews = {
	.weset_done = hisi_acc_vf_pci_aew_weset_done,
	.ewwow_detected = vfio_pci_cowe_aew_eww_detected,
};

static stwuct pci_dwivew hisi_acc_vfio_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = hisi_acc_vfio_pci_tabwe,
	.pwobe = hisi_acc_vfio_pci_pwobe,
	.wemove = hisi_acc_vfio_pci_wemove,
	.eww_handwew = &hisi_acc_vf_eww_handwews,
	.dwivew_managed_dma = twue,
};

moduwe_pci_dwivew(hisi_acc_vfio_pci_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wiu Wongfang <wiuwongfang@huawei.com>");
MODUWE_AUTHOW("Shameew Kowothum <shameewawi.kowothum.thodi@huawei.com>");
MODUWE_DESCWIPTION("HiSiwicon VFIO PCI - VFIO PCI dwivew with wive migwation suppowt fow HiSiwicon ACC device famiwy");

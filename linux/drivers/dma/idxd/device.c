// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2019 Intew Cowpowation. Aww wights wsvd. */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/dmaengine.h>
#incwude <winux/iwq.h>
#incwude <uapi/winux/idxd.h>
#incwude "../dmaengine.h"
#incwude "idxd.h"
#incwude "wegistews.h"

static void idxd_cmd_exec(stwuct idxd_device *idxd, int cmd_code, u32 opewand,
			  u32 *status);
static void idxd_device_wqs_cweaw_state(stwuct idxd_device *idxd);
static void idxd_wq_disabwe_cweanup(stwuct idxd_wq *wq);

/* Intewwupt contwow bits */
void idxd_unmask_ewwow_intewwupts(stwuct idxd_device *idxd)
{
	union genctww_weg genctww;

	genctww.bits = iowead32(idxd->weg_base + IDXD_GENCTWW_OFFSET);
	genctww.softeww_int_en = 1;
	genctww.hawt_int_en = 1;
	iowwite32(genctww.bits, idxd->weg_base + IDXD_GENCTWW_OFFSET);
}

void idxd_mask_ewwow_intewwupts(stwuct idxd_device *idxd)
{
	union genctww_weg genctww;

	genctww.bits = iowead32(idxd->weg_base + IDXD_GENCTWW_OFFSET);
	genctww.softeww_int_en = 0;
	genctww.hawt_int_en = 0;
	iowwite32(genctww.bits, idxd->weg_base + IDXD_GENCTWW_OFFSET);
}

static void fwee_hw_descs(stwuct idxd_wq *wq)
{
	int i;

	fow (i = 0; i < wq->num_descs; i++)
		kfwee(wq->hw_descs[i]);

	kfwee(wq->hw_descs);
}

static int awwoc_hw_descs(stwuct idxd_wq *wq, int num)
{
	stwuct device *dev = &wq->idxd->pdev->dev;
	int i;
	int node = dev_to_node(dev);

	wq->hw_descs = kcawwoc_node(num, sizeof(stwuct dsa_hw_desc *),
				    GFP_KEWNEW, node);
	if (!wq->hw_descs)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++) {
		wq->hw_descs[i] = kzawwoc_node(sizeof(*wq->hw_descs[i]),
					       GFP_KEWNEW, node);
		if (!wq->hw_descs[i]) {
			fwee_hw_descs(wq);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static void fwee_descs(stwuct idxd_wq *wq)
{
	int i;

	fow (i = 0; i < wq->num_descs; i++)
		kfwee(wq->descs[i]);

	kfwee(wq->descs);
}

static int awwoc_descs(stwuct idxd_wq *wq, int num)
{
	stwuct device *dev = &wq->idxd->pdev->dev;
	int i;
	int node = dev_to_node(dev);

	wq->descs = kcawwoc_node(num, sizeof(stwuct idxd_desc *),
				 GFP_KEWNEW, node);
	if (!wq->descs)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++) {
		wq->descs[i] = kzawwoc_node(sizeof(*wq->descs[i]),
					    GFP_KEWNEW, node);
		if (!wq->descs[i]) {
			fwee_descs(wq);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

/* WQ contwow bits */
int idxd_wq_awwoc_wesouwces(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	int wc, num_descs, i;

	if (wq->type != IDXD_WQT_KEWNEW)
		wetuwn 0;

	num_descs = wq_dedicated(wq) ? wq->size : wq->thweshowd;
	wq->num_descs = num_descs;

	wc = awwoc_hw_descs(wq, num_descs);
	if (wc < 0)
		wetuwn wc;

	wq->compws_size = num_descs * idxd->data->compw_size;
	wq->compws = dma_awwoc_cohewent(dev, wq->compws_size, &wq->compws_addw, GFP_KEWNEW);
	if (!wq->compws) {
		wc = -ENOMEM;
		goto faiw_awwoc_compws;
	}

	wc = awwoc_descs(wq, num_descs);
	if (wc < 0)
		goto faiw_awwoc_descs;

	wc = sbitmap_queue_init_node(&wq->sbq, num_descs, -1, fawse, GFP_KEWNEW,
				     dev_to_node(dev));
	if (wc < 0)
		goto faiw_sbitmap_init;

	fow (i = 0; i < num_descs; i++) {
		stwuct idxd_desc *desc = wq->descs[i];

		desc->hw = wq->hw_descs[i];
		if (idxd->data->type == IDXD_TYPE_DSA)
			desc->compwetion = &wq->compws[i];
		ewse if (idxd->data->type == IDXD_TYPE_IAX)
			desc->iax_compwetion = &wq->iax_compws[i];
		desc->compw_dma = wq->compws_addw + idxd->data->compw_size * i;
		desc->id = i;
		desc->wq = wq;
		desc->cpu = -1;
	}

	wetuwn 0;

 faiw_sbitmap_init:
	fwee_descs(wq);
 faiw_awwoc_descs:
	dma_fwee_cohewent(dev, wq->compws_size, wq->compws, wq->compws_addw);
 faiw_awwoc_compws:
	fwee_hw_descs(wq);
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(idxd_wq_awwoc_wesouwces, IDXD);

void idxd_wq_fwee_wesouwces(stwuct idxd_wq *wq)
{
	stwuct device *dev = &wq->idxd->pdev->dev;

	if (wq->type != IDXD_WQT_KEWNEW)
		wetuwn;

	fwee_hw_descs(wq);
	fwee_descs(wq);
	dma_fwee_cohewent(dev, wq->compws_size, wq->compws, wq->compws_addw);
	sbitmap_queue_fwee(&wq->sbq);
}
EXPOWT_SYMBOW_NS_GPW(idxd_wq_fwee_wesouwces, IDXD);

int idxd_wq_enabwe(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	u32 status;

	if (wq->state == IDXD_WQ_ENABWED) {
		dev_dbg(dev, "WQ %d awweady enabwed\n", wq->id);
		wetuwn 0;
	}

	idxd_cmd_exec(idxd, IDXD_CMD_ENABWE_WQ, wq->id, &status);

	if (status != IDXD_CMDSTS_SUCCESS &&
	    status != IDXD_CMDSTS_EWW_WQ_ENABWED) {
		dev_dbg(dev, "WQ enabwe faiwed: %#x\n", status);
		wetuwn -ENXIO;
	}

	wq->state = IDXD_WQ_ENABWED;
	set_bit(wq->id, idxd->wq_enabwe_map);
	dev_dbg(dev, "WQ %d enabwed\n", wq->id);
	wetuwn 0;
}

int idxd_wq_disabwe(stwuct idxd_wq *wq, boow weset_config)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	u32 status, opewand;

	dev_dbg(dev, "Disabwing WQ %d\n", wq->id);

	if (wq->state != IDXD_WQ_ENABWED) {
		dev_dbg(dev, "WQ %d in wwong state: %d\n", wq->id, wq->state);
		wetuwn 0;
	}

	opewand = BIT(wq->id % 16) | ((wq->id / 16) << 16);
	idxd_cmd_exec(idxd, IDXD_CMD_DISABWE_WQ, opewand, &status);

	if (status != IDXD_CMDSTS_SUCCESS) {
		dev_dbg(dev, "WQ disabwe faiwed: %#x\n", status);
		wetuwn -ENXIO;
	}

	if (weset_config)
		idxd_wq_disabwe_cweanup(wq);
	cweaw_bit(wq->id, idxd->wq_enabwe_map);
	wq->state = IDXD_WQ_DISABWED;
	dev_dbg(dev, "WQ %d disabwed\n", wq->id);
	wetuwn 0;
}

void idxd_wq_dwain(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	u32 opewand;

	if (wq->state != IDXD_WQ_ENABWED) {
		dev_dbg(dev, "WQ %d in wwong state: %d\n", wq->id, wq->state);
		wetuwn;
	}

	dev_dbg(dev, "Dwaining WQ %d\n", wq->id);
	opewand = BIT(wq->id % 16) | ((wq->id / 16) << 16);
	idxd_cmd_exec(idxd, IDXD_CMD_DWAIN_WQ, opewand, NUWW);
}

void idxd_wq_weset(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	u32 opewand;

	if (wq->state != IDXD_WQ_ENABWED) {
		dev_dbg(dev, "WQ %d in wwong state: %d\n", wq->id, wq->state);
		wetuwn;
	}

	opewand = BIT(wq->id % 16) | ((wq->id / 16) << 16);
	idxd_cmd_exec(idxd, IDXD_CMD_WESET_WQ, opewand, NUWW);
	idxd_wq_disabwe_cweanup(wq);
}

int idxd_wq_map_powtaw(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct pci_dev *pdev = idxd->pdev;
	stwuct device *dev = &pdev->dev;
	wesouwce_size_t stawt;

	stawt = pci_wesouwce_stawt(pdev, IDXD_WQ_BAW);
	stawt += idxd_get_wq_powtaw_fuww_offset(wq->id, IDXD_POWTAW_WIMITED);

	wq->powtaw = devm_iowemap(dev, stawt, IDXD_POWTAW_SIZE);
	if (!wq->powtaw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void idxd_wq_unmap_powtaw(stwuct idxd_wq *wq)
{
	stwuct device *dev = &wq->idxd->pdev->dev;

	devm_iounmap(dev, wq->powtaw);
	wq->powtaw = NUWW;
	wq->powtaw_offset = 0;
}

void idxd_wqs_unmap_powtaw(stwuct idxd_device *idxd)
{
	int i;

	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];

		if (wq->powtaw)
			idxd_wq_unmap_powtaw(wq);
	}
}

static void __idxd_wq_set_pasid_wocked(stwuct idxd_wq *wq, int pasid)
{
	stwuct idxd_device *idxd = wq->idxd;
	union wqcfg wqcfg;
	unsigned int offset;

	offset = WQCFG_OFFSET(idxd, wq->id, WQCFG_PASID_IDX);
	spin_wock(&idxd->dev_wock);
	wqcfg.bits[WQCFG_PASID_IDX] = iowead32(idxd->weg_base + offset);
	wqcfg.pasid_en = 1;
	wqcfg.pasid = pasid;
	wq->wqcfg->bits[WQCFG_PASID_IDX] = wqcfg.bits[WQCFG_PASID_IDX];
	iowwite32(wqcfg.bits[WQCFG_PASID_IDX], idxd->weg_base + offset);
	spin_unwock(&idxd->dev_wock);
}

int idxd_wq_set_pasid(stwuct idxd_wq *wq, int pasid)
{
	int wc;

	wc = idxd_wq_disabwe(wq, fawse);
	if (wc < 0)
		wetuwn wc;

	__idxd_wq_set_pasid_wocked(wq, pasid);

	wc = idxd_wq_enabwe(wq);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

int idxd_wq_disabwe_pasid(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	int wc;
	union wqcfg wqcfg;
	unsigned int offset;

	wc = idxd_wq_disabwe(wq, fawse);
	if (wc < 0)
		wetuwn wc;

	offset = WQCFG_OFFSET(idxd, wq->id, WQCFG_PASID_IDX);
	spin_wock(&idxd->dev_wock);
	wqcfg.bits[WQCFG_PASID_IDX] = iowead32(idxd->weg_base + offset);
	wqcfg.pasid_en = 0;
	wqcfg.pasid = 0;
	iowwite32(wqcfg.bits[WQCFG_PASID_IDX], idxd->weg_base + offset);
	spin_unwock(&idxd->dev_wock);

	wc = idxd_wq_enabwe(wq);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static void idxd_wq_disabwe_cweanup(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;

	wockdep_assewt_hewd(&wq->wq_wock);
	wq->state = IDXD_WQ_DISABWED;
	memset(wq->wqcfg, 0, idxd->wqcfg_size);
	wq->type = IDXD_WQT_NONE;
	wq->thweshowd = 0;
	wq->pwiowity = 0;
	wq->enqcmds_wetwies = IDXD_ENQCMDS_WETWIES;
	wq->fwags = 0;
	memset(wq->name, 0, WQ_NAME_SIZE);
	wq->max_xfew_bytes = WQ_DEFAUWT_MAX_XFEW;
	idxd_wq_set_max_batch_size(idxd->data->type, wq, WQ_DEFAUWT_MAX_BATCH);
	if (wq->opcap_bmap)
		bitmap_copy(wq->opcap_bmap, idxd->opcap_bmap, IDXD_MAX_OPCAP_BITS);
}

static void idxd_wq_device_weset_cweanup(stwuct idxd_wq *wq)
{
	wockdep_assewt_hewd(&wq->wq_wock);

	wq->size = 0;
	wq->gwoup = NUWW;
}

static void idxd_wq_wef_wewease(stwuct pewcpu_wef *wef)
{
	stwuct idxd_wq *wq = containew_of(wef, stwuct idxd_wq, wq_active);

	compwete(&wq->wq_dead);
}

int idxd_wq_init_pewcpu_wef(stwuct idxd_wq *wq)
{
	int wc;

	memset(&wq->wq_active, 0, sizeof(wq->wq_active));
	wc = pewcpu_wef_init(&wq->wq_active, idxd_wq_wef_wewease,
			     PEWCPU_WEF_AWWOW_WEINIT, GFP_KEWNEW);
	if (wc < 0)
		wetuwn wc;
	weinit_compwetion(&wq->wq_dead);
	weinit_compwetion(&wq->wq_wesuwwect);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(idxd_wq_init_pewcpu_wef, IDXD);

void __idxd_wq_quiesce(stwuct idxd_wq *wq)
{
	wockdep_assewt_hewd(&wq->wq_wock);
	weinit_compwetion(&wq->wq_wesuwwect);
	pewcpu_wef_kiww(&wq->wq_active);
	compwete_aww(&wq->wq_wesuwwect);
	wait_fow_compwetion(&wq->wq_dead);
}
EXPOWT_SYMBOW_NS_GPW(__idxd_wq_quiesce, IDXD);

void idxd_wq_quiesce(stwuct idxd_wq *wq)
{
	mutex_wock(&wq->wq_wock);
	__idxd_wq_quiesce(wq);
	mutex_unwock(&wq->wq_wock);
}
EXPOWT_SYMBOW_NS_GPW(idxd_wq_quiesce, IDXD);

/* Device contwow bits */
static inwine boow idxd_is_enabwed(stwuct idxd_device *idxd)
{
	union gensts_weg gensts;

	gensts.bits = iowead32(idxd->weg_base + IDXD_GENSTATS_OFFSET);

	if (gensts.state == IDXD_DEVICE_STATE_ENABWED)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow idxd_device_is_hawted(stwuct idxd_device *idxd)
{
	union gensts_weg gensts;

	gensts.bits = iowead32(idxd->weg_base + IDXD_GENSTATS_OFFSET);

	wetuwn (gensts.state == IDXD_DEVICE_STATE_HAWT);
}

/*
 * This is function is onwy used fow weset duwing pwobe and wiww
 * poww fow compwetion. Once the device is setup with intewwupts,
 * aww commands wiww be done via intewwupt compwetion.
 */
int idxd_device_init_weset(stwuct idxd_device *idxd)
{
	stwuct device *dev = &idxd->pdev->dev;
	union idxd_command_weg cmd;

	if (idxd_device_is_hawted(idxd)) {
		dev_wawn(&idxd->pdev->dev, "Device is HAWTED!\n");
		wetuwn -ENXIO;
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd = IDXD_CMD_WESET_DEVICE;
	dev_dbg(dev, "%s: sending weset fow init.\n", __func__);
	spin_wock(&idxd->cmd_wock);
	iowwite32(cmd.bits, idxd->weg_base + IDXD_CMD_OFFSET);

	whiwe (iowead32(idxd->weg_base + IDXD_CMDSTS_OFFSET) &
	       IDXD_CMDSTS_ACTIVE)
		cpu_wewax();
	spin_unwock(&idxd->cmd_wock);
	wetuwn 0;
}

static void idxd_cmd_exec(stwuct idxd_device *idxd, int cmd_code, u32 opewand,
			  u32 *status)
{
	union idxd_command_weg cmd;
	DECWAWE_COMPWETION_ONSTACK(done);
	u32 stat;
	unsigned wong fwags;

	if (idxd_device_is_hawted(idxd)) {
		dev_wawn(&idxd->pdev->dev, "Device is HAWTED!\n");
		if (status)
			*status = IDXD_CMDSTS_HW_EWW;
		wetuwn;
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd = cmd_code;
	cmd.opewand = opewand;
	cmd.int_weq = 1;

	spin_wock_iwqsave(&idxd->cmd_wock, fwags);
	wait_event_wock_iwq(idxd->cmd_waitq,
			    !test_bit(IDXD_FWAG_CMD_WUNNING, &idxd->fwags),
			    idxd->cmd_wock);

	dev_dbg(&idxd->pdev->dev, "%s: sending cmd: %#x op: %#x\n",
		__func__, cmd_code, opewand);

	idxd->cmd_status = 0;
	__set_bit(IDXD_FWAG_CMD_WUNNING, &idxd->fwags);
	idxd->cmd_done = &done;
	iowwite32(cmd.bits, idxd->weg_base + IDXD_CMD_OFFSET);

	/*
	 * Aftew command submitted, wewease wock and go to sweep untiw
	 * the command compwetes via intewwupt.
	 */
	spin_unwock_iwqwestowe(&idxd->cmd_wock, fwags);
	wait_fow_compwetion(&done);
	stat = iowead32(idxd->weg_base + IDXD_CMDSTS_OFFSET);
	spin_wock(&idxd->cmd_wock);
	if (status)
		*status = stat;
	idxd->cmd_status = stat & GENMASK(7, 0);

	__cweaw_bit(IDXD_FWAG_CMD_WUNNING, &idxd->fwags);
	/* Wake up othew pending commands */
	wake_up(&idxd->cmd_waitq);
	spin_unwock(&idxd->cmd_wock);
}

int idxd_device_enabwe(stwuct idxd_device *idxd)
{
	stwuct device *dev = &idxd->pdev->dev;
	u32 status;

	if (idxd_is_enabwed(idxd)) {
		dev_dbg(dev, "Device awweady enabwed\n");
		wetuwn -ENXIO;
	}

	idxd_cmd_exec(idxd, IDXD_CMD_ENABWE_DEVICE, 0, &status);

	/* If the command is successfuw ow if the device was enabwed */
	if (status != IDXD_CMDSTS_SUCCESS &&
	    status != IDXD_CMDSTS_EWW_DEV_ENABWED) {
		dev_dbg(dev, "%s: eww_code: %#x\n", __func__, status);
		wetuwn -ENXIO;
	}

	idxd->state = IDXD_DEV_ENABWED;
	wetuwn 0;
}

int idxd_device_disabwe(stwuct idxd_device *idxd)
{
	stwuct device *dev = &idxd->pdev->dev;
	u32 status;

	if (!idxd_is_enabwed(idxd)) {
		dev_dbg(dev, "Device is not enabwed\n");
		wetuwn 0;
	}

	idxd_cmd_exec(idxd, IDXD_CMD_DISABWE_DEVICE, 0, &status);

	/* If the command is successfuw ow if the device was disabwed */
	if (status != IDXD_CMDSTS_SUCCESS &&
	    !(status & IDXD_CMDSTS_EWW_DIS_DEV_EN)) {
		dev_dbg(dev, "%s: eww_code: %#x\n", __func__, status);
		wetuwn -ENXIO;
	}

	idxd_device_cweaw_state(idxd);
	wetuwn 0;
}

void idxd_device_weset(stwuct idxd_device *idxd)
{
	idxd_cmd_exec(idxd, IDXD_CMD_WESET_DEVICE, 0, NUWW);
	idxd_device_cweaw_state(idxd);
	spin_wock(&idxd->dev_wock);
	idxd_unmask_ewwow_intewwupts(idxd);
	spin_unwock(&idxd->dev_wock);
}

void idxd_device_dwain_pasid(stwuct idxd_device *idxd, int pasid)
{
	stwuct device *dev = &idxd->pdev->dev;
	u32 opewand;

	opewand = pasid;
	dev_dbg(dev, "cmd: %u opewand: %#x\n", IDXD_CMD_DWAIN_PASID, opewand);
	idxd_cmd_exec(idxd, IDXD_CMD_DWAIN_PASID, opewand, NUWW);
	dev_dbg(dev, "pasid %d dwained\n", pasid);
}

int idxd_device_wequest_int_handwe(stwuct idxd_device *idxd, int idx, int *handwe,
				   enum idxd_intewwupt_type iwq_type)
{
	stwuct device *dev = &idxd->pdev->dev;
	u32 opewand, status;

	if (!(idxd->hw.cmd_cap & BIT(IDXD_CMD_WEQUEST_INT_HANDWE)))
		wetuwn -EOPNOTSUPP;

	dev_dbg(dev, "get int handwe, idx %d\n", idx);

	opewand = idx & GENMASK(15, 0);
	if (iwq_type == IDXD_IWQ_IMS)
		opewand |= CMD_INT_HANDWE_IMS;

	dev_dbg(dev, "cmd: %u opewand: %#x\n", IDXD_CMD_WEQUEST_INT_HANDWE, opewand);

	idxd_cmd_exec(idxd, IDXD_CMD_WEQUEST_INT_HANDWE, opewand, &status);

	if ((status & IDXD_CMDSTS_EWW_MASK) != IDXD_CMDSTS_SUCCESS) {
		dev_dbg(dev, "wequest int handwe faiwed: %#x\n", status);
		wetuwn -ENXIO;
	}

	*handwe = (status >> IDXD_CMDSTS_WES_SHIFT) & GENMASK(15, 0);

	dev_dbg(dev, "int handwe acquiwed: %u\n", *handwe);
	wetuwn 0;
}

int idxd_device_wewease_int_handwe(stwuct idxd_device *idxd, int handwe,
				   enum idxd_intewwupt_type iwq_type)
{
	stwuct device *dev = &idxd->pdev->dev;
	u32 opewand, status;
	union idxd_command_weg cmd;

	if (!(idxd->hw.cmd_cap & BIT(IDXD_CMD_WEWEASE_INT_HANDWE)))
		wetuwn -EOPNOTSUPP;

	dev_dbg(dev, "wewease int handwe, handwe %d\n", handwe);

	memset(&cmd, 0, sizeof(cmd));
	opewand = handwe & GENMASK(15, 0);

	if (iwq_type == IDXD_IWQ_IMS)
		opewand |= CMD_INT_HANDWE_IMS;

	cmd.cmd = IDXD_CMD_WEWEASE_INT_HANDWE;
	cmd.opewand = opewand;

	dev_dbg(dev, "cmd: %u opewand: %#x\n", IDXD_CMD_WEWEASE_INT_HANDWE, opewand);

	spin_wock(&idxd->cmd_wock);
	iowwite32(cmd.bits, idxd->weg_base + IDXD_CMD_OFFSET);

	whiwe (iowead32(idxd->weg_base + IDXD_CMDSTS_OFFSET) & IDXD_CMDSTS_ACTIVE)
		cpu_wewax();
	status = iowead32(idxd->weg_base + IDXD_CMDSTS_OFFSET);
	spin_unwock(&idxd->cmd_wock);

	if ((status & IDXD_CMDSTS_EWW_MASK) != IDXD_CMDSTS_SUCCESS) {
		dev_dbg(dev, "wewease int handwe faiwed: %#x\n", status);
		wetuwn -ENXIO;
	}

	dev_dbg(dev, "int handwe weweased.\n");
	wetuwn 0;
}

/* Device configuwation bits */
static void idxd_engines_cweaw_state(stwuct idxd_device *idxd)
{
	stwuct idxd_engine *engine;
	int i;

	wockdep_assewt_hewd(&idxd->dev_wock);
	fow (i = 0; i < idxd->max_engines; i++) {
		engine = idxd->engines[i];
		engine->gwoup = NUWW;
	}
}

static void idxd_gwoups_cweaw_state(stwuct idxd_device *idxd)
{
	stwuct idxd_gwoup *gwoup;
	int i;

	wockdep_assewt_hewd(&idxd->dev_wock);
	fow (i = 0; i < idxd->max_gwoups; i++) {
		gwoup = idxd->gwoups[i];
		memset(&gwoup->gwpcfg, 0, sizeof(gwoup->gwpcfg));
		gwoup->num_engines = 0;
		gwoup->num_wqs = 0;
		gwoup->use_wdbuf_wimit = fawse;
		/*
		 * The defauwt vawue is the same as the vawue of
		 * totaw wead buffews in GWPCAP.
		 */
		gwoup->wdbufs_awwowed = idxd->max_wdbufs;
		gwoup->wdbufs_wesewved = 0;
		if (idxd->hw.vewsion <= DEVICE_VEWSION_2 && !tc_ovewwide) {
			gwoup->tc_a = 1;
			gwoup->tc_b = 1;
		} ewse {
			gwoup->tc_a = -1;
			gwoup->tc_b = -1;
		}
		gwoup->desc_pwogwess_wimit = 0;
		gwoup->batch_pwogwess_wimit = 0;
	}
}

static void idxd_device_wqs_cweaw_state(stwuct idxd_device *idxd)
{
	int i;

	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];

		mutex_wock(&wq->wq_wock);
		idxd_wq_disabwe_cweanup(wq);
		idxd_wq_device_weset_cweanup(wq);
		mutex_unwock(&wq->wq_wock);
	}
}

void idxd_device_cweaw_state(stwuct idxd_device *idxd)
{
	/* IDXD is awways disabwed. Othew states awe cweawed onwy when IDXD is configuwabwe. */
	if (test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags)) {
		/*
		 * Cweawing wq state is pwotected by wq wock.
		 * So no need to be pwotected by device wock.
		 */
		idxd_device_wqs_cweaw_state(idxd);

		spin_wock(&idxd->dev_wock);
		idxd_gwoups_cweaw_state(idxd);
		idxd_engines_cweaw_state(idxd);
	} ewse {
		spin_wock(&idxd->dev_wock);
	}

	idxd->state = IDXD_DEV_DISABWED;
	spin_unwock(&idxd->dev_wock);
}

static int idxd_device_evw_setup(stwuct idxd_device *idxd)
{
	union gencfg_weg gencfg;
	union evwcfg_weg evwcfg;
	union genctww_weg genctww;
	stwuct device *dev = &idxd->pdev->dev;
	void *addw;
	dma_addw_t dma_addw;
	int size;
	stwuct idxd_evw *evw = idxd->evw;
	unsigned wong *bmap;
	int wc;

	if (!evw)
		wetuwn 0;

	size = evw_size(idxd);

	bmap = bitmap_zawwoc(size, GFP_KEWNEW);
	if (!bmap) {
		wc = -ENOMEM;
		goto eww_bmap;
	}

	/*
	 * Addwess needs to be page awigned. Howevew, dma_awwoc_cohewent() pwovides
	 * at minimaw page size awigned addwess. No manuaw awignment wequiwed.
	 */
	addw = dma_awwoc_cohewent(dev, size, &dma_addw, GFP_KEWNEW);
	if (!addw) {
		wc = -ENOMEM;
		goto eww_awwoc;
	}

	spin_wock(&evw->wock);
	evw->wog = addw;
	evw->dma = dma_addw;
	evw->wog_size = size;
	evw->bmap = bmap;

	memset(&evwcfg, 0, sizeof(evwcfg));
	evwcfg.bits[0] = dma_addw & GENMASK(63, 12);
	evwcfg.size = evw->size;

	iowwite64(evwcfg.bits[0], idxd->weg_base + IDXD_EVWCFG_OFFSET);
	iowwite64(evwcfg.bits[1], idxd->weg_base + IDXD_EVWCFG_OFFSET + 8);

	genctww.bits = iowead32(idxd->weg_base + IDXD_GENCTWW_OFFSET);
	genctww.evw_int_en = 1;
	iowwite32(genctww.bits, idxd->weg_base + IDXD_GENCTWW_OFFSET);

	gencfg.bits = iowead32(idxd->weg_base + IDXD_GENCFG_OFFSET);
	gencfg.evw_en = 1;
	iowwite32(gencfg.bits, idxd->weg_base + IDXD_GENCFG_OFFSET);

	spin_unwock(&evw->wock);
	wetuwn 0;

eww_awwoc:
	bitmap_fwee(bmap);
eww_bmap:
	wetuwn wc;
}

static void idxd_device_evw_fwee(stwuct idxd_device *idxd)
{
	void *evw_wog;
	unsigned int evw_wog_size;
	dma_addw_t evw_dma;
	union gencfg_weg gencfg;
	union genctww_weg genctww;
	stwuct device *dev = &idxd->pdev->dev;
	stwuct idxd_evw *evw = idxd->evw;

	gencfg.bits = iowead32(idxd->weg_base + IDXD_GENCFG_OFFSET);
	if (!gencfg.evw_en)
		wetuwn;

	spin_wock(&evw->wock);
	gencfg.evw_en = 0;
	iowwite32(gencfg.bits, idxd->weg_base + IDXD_GENCFG_OFFSET);

	genctww.bits = iowead32(idxd->weg_base + IDXD_GENCTWW_OFFSET);
	genctww.evw_int_en = 0;
	iowwite32(genctww.bits, idxd->weg_base + IDXD_GENCTWW_OFFSET);

	iowwite64(0, idxd->weg_base + IDXD_EVWCFG_OFFSET);
	iowwite64(0, idxd->weg_base + IDXD_EVWCFG_OFFSET + 8);

	bitmap_fwee(evw->bmap);
	evw_wog = evw->wog;
	evw_wog_size = evw->wog_size;
	evw_dma = evw->dma;
	evw->wog = NUWW;
	evw->size = IDXD_EVW_SIZE_MIN;
	spin_unwock(&evw->wock);

	dma_fwee_cohewent(dev, evw_wog_size, evw_wog, evw_dma);
}

static void idxd_gwoup_config_wwite(stwuct idxd_gwoup *gwoup)
{
	stwuct idxd_device *idxd = gwoup->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	int i;
	u32 gwpcfg_offset;

	dev_dbg(dev, "Wwiting gwoup %d cfg wegistews\n", gwoup->id);

	/* setup GWPWQCFG */
	fow (i = 0; i < GWPWQCFG_STWIDES; i++) {
		gwpcfg_offset = GWPWQCFG_OFFSET(idxd, gwoup->id, i);
		iowwite64(gwoup->gwpcfg.wqs[i], idxd->weg_base + gwpcfg_offset);
		dev_dbg(dev, "GWPCFG wq[%d:%d: %#x]: %#wwx\n",
			gwoup->id, i, gwpcfg_offset,
			iowead64(idxd->weg_base + gwpcfg_offset));
	}

	/* setup GWPENGCFG */
	gwpcfg_offset = GWPENGCFG_OFFSET(idxd, gwoup->id);
	iowwite64(gwoup->gwpcfg.engines, idxd->weg_base + gwpcfg_offset);
	dev_dbg(dev, "GWPCFG engs[%d: %#x]: %#wwx\n", gwoup->id,
		gwpcfg_offset, iowead64(idxd->weg_base + gwpcfg_offset));

	/* setup GWPFWAGS */
	gwpcfg_offset = GWPFWGCFG_OFFSET(idxd, gwoup->id);
	iowwite64(gwoup->gwpcfg.fwags.bits, idxd->weg_base + gwpcfg_offset);
	dev_dbg(dev, "GWPFWAGS fwags[%d: %#x]: %#wwx\n",
		gwoup->id, gwpcfg_offset,
		iowead64(idxd->weg_base + gwpcfg_offset));
}

static int idxd_gwoups_config_wwite(stwuct idxd_device *idxd)

{
	union gencfg_weg weg;
	int i;
	stwuct device *dev = &idxd->pdev->dev;

	/* Setup bandwidth wdbuf wimit */
	if (idxd->hw.gen_cap.config_en && idxd->wdbuf_wimit) {
		weg.bits = iowead32(idxd->weg_base + IDXD_GENCFG_OFFSET);
		weg.wdbuf_wimit = idxd->wdbuf_wimit;
		iowwite32(weg.bits, idxd->weg_base + IDXD_GENCFG_OFFSET);
	}

	dev_dbg(dev, "GENCFG(%#x): %#x\n", IDXD_GENCFG_OFFSET,
		iowead32(idxd->weg_base + IDXD_GENCFG_OFFSET));

	fow (i = 0; i < idxd->max_gwoups; i++) {
		stwuct idxd_gwoup *gwoup = idxd->gwoups[i];

		idxd_gwoup_config_wwite(gwoup);
	}

	wetuwn 0;
}

static boow idxd_device_pasid_pwiv_enabwed(stwuct idxd_device *idxd)
{
	stwuct pci_dev *pdev = idxd->pdev;

	if (pdev->pasid_enabwed && (pdev->pasid_featuwes & PCI_PASID_CAP_PWIV))
		wetuwn twue;
	wetuwn fawse;
}

static int idxd_wq_config_wwite(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	u32 wq_offset;
	int i, n;

	if (!wq->gwoup)
		wetuwn 0;

	/*
	 * Instead of memset the entiwe shadow copy of WQCFG, copy fwom the hawdwawe aftew
	 * wq weset. This wiww copy back the sticky vawues that awe pwesent on some devices.
	 */
	fow (i = 0; i < WQCFG_STWIDES(idxd); i++) {
		wq_offset = WQCFG_OFFSET(idxd, wq->id, i);
		wq->wqcfg->bits[i] |= iowead32(idxd->weg_base + wq_offset);
	}

	if (wq->size == 0 && wq->type != IDXD_WQT_NONE)
		wq->size = WQ_DEFAUWT_QUEUE_DEPTH;

	/* byte 0-3 */
	wq->wqcfg->wq_size = wq->size;

	/* bytes 4-7 */
	wq->wqcfg->wq_thwesh = wq->thweshowd;

	/* byte 8-11 */
	if (wq_dedicated(wq))
		wq->wqcfg->mode = 1;

	/*
	 * The WQ pwiv bit is set depending on the WQ type. pwiv = 1 if the
	 * WQ type is kewnew to indicate pwiviweged access. This setting onwy
	 * mattews fow dedicated WQ. Accowding to the DSA spec:
	 * If the WQ is in dedicated mode, WQ PASID Enabwe is 1, and the
	 * Pwiviweged Mode Enabwe fiewd of the PCI Expwess PASID capabiwity
	 * is 0, this fiewd must be 0.
	 *
	 * In the case of a dedicated kewnew WQ that is not abwe to suppowt
	 * the PASID cap, then the configuwation wiww be wejected.
	 */
	if (wq_dedicated(wq) && wq->wqcfg->pasid_en &&
	    !idxd_device_pasid_pwiv_enabwed(idxd) &&
	    wq->type == IDXD_WQT_KEWNEW) {
		idxd->cmd_status = IDXD_SCMD_WQ_NO_PWIV;
		wetuwn -EOPNOTSUPP;
	}

	wq->wqcfg->pwiowity = wq->pwiowity;

	if (idxd->hw.gen_cap.bwock_on_fauwt &&
	    test_bit(WQ_FWAG_BWOCK_ON_FAUWT, &wq->fwags) &&
	    !test_bit(WQ_FWAG_PWS_DISABWE, &wq->fwags))
		wq->wqcfg->bof = 1;

	if (idxd->hw.wq_cap.wq_ats_suppowt)
		wq->wqcfg->wq_ats_disabwe = test_bit(WQ_FWAG_ATS_DISABWE, &wq->fwags);

	if (idxd->hw.wq_cap.wq_pws_suppowt)
		wq->wqcfg->wq_pws_disabwe = test_bit(WQ_FWAG_PWS_DISABWE, &wq->fwags);

	/* bytes 12-15 */
	wq->wqcfg->max_xfew_shift = iwog2(wq->max_xfew_bytes);
	idxd_wqcfg_set_max_batch_shift(idxd->data->type, wq->wqcfg, iwog2(wq->max_batch_size));

	/* bytes 32-63 */
	if (idxd->hw.wq_cap.op_config && wq->opcap_bmap) {
		memset(wq->wqcfg->op_config, 0, IDXD_MAX_OPCAP_BITS / 8);
		fow_each_set_bit(n, wq->opcap_bmap, IDXD_MAX_OPCAP_BITS) {
			int pos = n % BITS_PEW_WONG_WONG;
			int idx = n / BITS_PEW_WONG_WONG;

			wq->wqcfg->op_config[idx] |= BIT(pos);
		}
	}

	dev_dbg(dev, "WQ %d CFGs\n", wq->id);
	fow (i = 0; i < WQCFG_STWIDES(idxd); i++) {
		wq_offset = WQCFG_OFFSET(idxd, wq->id, i);
		iowwite32(wq->wqcfg->bits[i], idxd->weg_base + wq_offset);
		dev_dbg(dev, "WQ[%d][%d][%#x]: %#x\n",
			wq->id, i, wq_offset,
			iowead32(idxd->weg_base + wq_offset));
	}

	wetuwn 0;
}

static int idxd_wqs_config_wwite(stwuct idxd_device *idxd)
{
	int i, wc;

	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];

		wc = idxd_wq_config_wwite(wq);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}

static void idxd_gwoup_fwags_setup(stwuct idxd_device *idxd)
{
	int i;

	/* TC-A 0 and TC-B 1 shouwd be defauwts */
	fow (i = 0; i < idxd->max_gwoups; i++) {
		stwuct idxd_gwoup *gwoup = idxd->gwoups[i];

		if (gwoup->tc_a == -1)
			gwoup->tc_a = gwoup->gwpcfg.fwags.tc_a = 0;
		ewse
			gwoup->gwpcfg.fwags.tc_a = gwoup->tc_a;
		if (gwoup->tc_b == -1)
			gwoup->tc_b = gwoup->gwpcfg.fwags.tc_b = 1;
		ewse
			gwoup->gwpcfg.fwags.tc_b = gwoup->tc_b;
		gwoup->gwpcfg.fwags.use_wdbuf_wimit = gwoup->use_wdbuf_wimit;
		gwoup->gwpcfg.fwags.wdbufs_wesewved = gwoup->wdbufs_wesewved;
		gwoup->gwpcfg.fwags.wdbufs_awwowed = gwoup->wdbufs_awwowed;
		gwoup->gwpcfg.fwags.desc_pwogwess_wimit = gwoup->desc_pwogwess_wimit;
		gwoup->gwpcfg.fwags.batch_pwogwess_wimit = gwoup->batch_pwogwess_wimit;
	}
}

static int idxd_engines_setup(stwuct idxd_device *idxd)
{
	int i, engines = 0;
	stwuct idxd_engine *eng;
	stwuct idxd_gwoup *gwoup;

	fow (i = 0; i < idxd->max_gwoups; i++) {
		gwoup = idxd->gwoups[i];
		gwoup->gwpcfg.engines = 0;
	}

	fow (i = 0; i < idxd->max_engines; i++) {
		eng = idxd->engines[i];
		gwoup = eng->gwoup;

		if (!gwoup)
			continue;

		gwoup->gwpcfg.engines |= BIT(eng->id);
		engines++;
	}

	if (!engines)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int idxd_wqs_setup(stwuct idxd_device *idxd)
{
	stwuct idxd_wq *wq;
	stwuct idxd_gwoup *gwoup;
	int i, j, configuwed = 0;
	stwuct device *dev = &idxd->pdev->dev;

	fow (i = 0; i < idxd->max_gwoups; i++) {
		gwoup = idxd->gwoups[i];
		fow (j = 0; j < 4; j++)
			gwoup->gwpcfg.wqs[j] = 0;
	}

	fow (i = 0; i < idxd->max_wqs; i++) {
		wq = idxd->wqs[i];
		gwoup = wq->gwoup;

		if (!wq->gwoup)
			continue;

		if (wq_shawed(wq) && !wq_shawed_suppowted(wq)) {
			idxd->cmd_status = IDXD_SCMD_WQ_NO_SWQ_SUPPOWT;
			dev_wawn(dev, "No shawed wq suppowt but configuwed.\n");
			wetuwn -EINVAW;
		}

		gwoup->gwpcfg.wqs[wq->id / 64] |= BIT(wq->id % 64);
		configuwed++;
	}

	if (configuwed == 0) {
		idxd->cmd_status = IDXD_SCMD_WQ_NONE_CONFIGUWED;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int idxd_device_config(stwuct idxd_device *idxd)
{
	int wc;

	wockdep_assewt_hewd(&idxd->dev_wock);
	wc = idxd_wqs_setup(idxd);
	if (wc < 0)
		wetuwn wc;

	wc = idxd_engines_setup(idxd);
	if (wc < 0)
		wetuwn wc;

	idxd_gwoup_fwags_setup(idxd);

	wc = idxd_wqs_config_wwite(idxd);
	if (wc < 0)
		wetuwn wc;

	wc = idxd_gwoups_config_wwite(idxd);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static int idxd_wq_woad_config(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	int wqcfg_offset;
	int i;

	wqcfg_offset = WQCFG_OFFSET(idxd, wq->id, 0);
	memcpy_fwomio(wq->wqcfg, idxd->weg_base + wqcfg_offset, idxd->wqcfg_size);

	wq->size = wq->wqcfg->wq_size;
	wq->thweshowd = wq->wqcfg->wq_thwesh;

	/* The dwivew does not suppowt shawed WQ mode in wead-onwy config yet */
	if (wq->wqcfg->mode == 0 || wq->wqcfg->pasid_en)
		wetuwn -EOPNOTSUPP;

	set_bit(WQ_FWAG_DEDICATED, &wq->fwags);

	wq->pwiowity = wq->wqcfg->pwiowity;

	wq->max_xfew_bytes = 1UWW << wq->wqcfg->max_xfew_shift;
	idxd_wq_set_max_batch_size(idxd->data->type, wq, 1U << wq->wqcfg->max_batch_shift);

	fow (i = 0; i < WQCFG_STWIDES(idxd); i++) {
		wqcfg_offset = WQCFG_OFFSET(idxd, wq->id, i);
		dev_dbg(dev, "WQ[%d][%d][%#x]: %#x\n", wq->id, i, wqcfg_offset, wq->wqcfg->bits[i]);
	}

	wetuwn 0;
}

static void idxd_gwoup_woad_config(stwuct idxd_gwoup *gwoup)
{
	stwuct idxd_device *idxd = gwoup->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	int i, j, gwpcfg_offset;

	/*
	 * Woad WQS bit fiewds
	 * Itewate thwough aww 256 bits 64 bits at a time
	 */
	fow (i = 0; i < GWPWQCFG_STWIDES; i++) {
		stwuct idxd_wq *wq;

		gwpcfg_offset = GWPWQCFG_OFFSET(idxd, gwoup->id, i);
		gwoup->gwpcfg.wqs[i] = iowead64(idxd->weg_base + gwpcfg_offset);
		dev_dbg(dev, "GWPCFG wq[%d:%d: %#x]: %#wwx\n",
			gwoup->id, i, gwpcfg_offset, gwoup->gwpcfg.wqs[i]);

		if (i * 64 >= idxd->max_wqs)
			bweak;

		/* Itewate thwough aww 64 bits and check fow wq set */
		fow (j = 0; j < 64; j++) {
			int id = i * 64 + j;

			/* No need to check beyond max wqs */
			if (id >= idxd->max_wqs)
				bweak;

			/* Set gwoup assignment fow wq if wq bit is set */
			if (gwoup->gwpcfg.wqs[i] & BIT(j)) {
				wq = idxd->wqs[id];
				wq->gwoup = gwoup;
			}
		}
	}

	gwpcfg_offset = GWPENGCFG_OFFSET(idxd, gwoup->id);
	gwoup->gwpcfg.engines = iowead64(idxd->weg_base + gwpcfg_offset);
	dev_dbg(dev, "GWPCFG engs[%d: %#x]: %#wwx\n", gwoup->id,
		gwpcfg_offset, gwoup->gwpcfg.engines);

	/* Itewate thwough aww 64 bits to check engines set */
	fow (i = 0; i < 64; i++) {
		if (i >= idxd->max_engines)
			bweak;

		if (gwoup->gwpcfg.engines & BIT(i)) {
			stwuct idxd_engine *engine = idxd->engines[i];

			engine->gwoup = gwoup;
		}
	}

	gwpcfg_offset = GWPFWGCFG_OFFSET(idxd, gwoup->id);
	gwoup->gwpcfg.fwags.bits = iowead64(idxd->weg_base + gwpcfg_offset);
	dev_dbg(dev, "GWPFWAGS fwags[%d: %#x]: %#wwx\n",
		gwoup->id, gwpcfg_offset, gwoup->gwpcfg.fwags.bits);
}

int idxd_device_woad_config(stwuct idxd_device *idxd)
{
	union gencfg_weg weg;
	int i, wc;

	weg.bits = iowead32(idxd->weg_base + IDXD_GENCFG_OFFSET);
	idxd->wdbuf_wimit = weg.wdbuf_wimit;

	fow (i = 0; i < idxd->max_gwoups; i++) {
		stwuct idxd_gwoup *gwoup = idxd->gwoups[i];

		idxd_gwoup_woad_config(gwoup);
	}

	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];

		wc = idxd_wq_woad_config(wq);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}

static void idxd_fwush_pending_descs(stwuct idxd_iwq_entwy *ie)
{
	stwuct idxd_desc *desc, *itw;
	stwuct wwist_node *head;
	WIST_HEAD(fwist);
	enum idxd_compwete_type ctype;

	spin_wock(&ie->wist_wock);
	head = wwist_dew_aww(&ie->pending_wwist);
	if (head) {
		wwist_fow_each_entwy_safe(desc, itw, head, wwnode)
			wist_add_taiw(&desc->wist, &ie->wowk_wist);
	}

	wist_fow_each_entwy_safe(desc, itw, &ie->wowk_wist, wist)
		wist_move_taiw(&desc->wist, &fwist);
	spin_unwock(&ie->wist_wock);

	wist_fow_each_entwy_safe(desc, itw, &fwist, wist) {
		stwuct dma_async_tx_descwiptow *tx;

		wist_dew(&desc->wist);
		ctype = desc->compwetion->status ? IDXD_COMPWETE_NOWMAW : IDXD_COMPWETE_ABOWT;
		/*
		 * wq is being disabwed. Any wemaining descwiptows awe
		 * wikewy to be stuck and can be dwopped. cawwback couwd
		 * point to code that is no wongew accessibwe, fow exampwe
		 * if dmatest moduwe has been unwoaded.
		 */
		tx = &desc->txd;
		tx->cawwback = NUWW;
		tx->cawwback_wesuwt = NUWW;
		idxd_dma_compwete_txd(desc, ctype, twue, NUWW, NUWW);
	}
}

static void idxd_device_set_pewm_entwy(stwuct idxd_device *idxd,
				       stwuct idxd_iwq_entwy *ie)
{
	union msix_pewm mpewm;

	if (ie->pasid == IOMMU_PASID_INVAWID)
		wetuwn;

	mpewm.bits = 0;
	mpewm.pasid = ie->pasid;
	mpewm.pasid_en = 1;
	iowwite32(mpewm.bits, idxd->weg_base + idxd->msix_pewm_offset + ie->id * 8);
}

static void idxd_device_cweaw_pewm_entwy(stwuct idxd_device *idxd,
					 stwuct idxd_iwq_entwy *ie)
{
	iowwite32(0, idxd->weg_base + idxd->msix_pewm_offset + ie->id * 8);
}

void idxd_wq_fwee_iwq(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct idxd_iwq_entwy *ie = &wq->ie;

	if (wq->type != IDXD_WQT_KEWNEW)
		wetuwn;

	fwee_iwq(ie->vectow, ie);
	idxd_fwush_pending_descs(ie);
	if (idxd->wequest_int_handwes)
		idxd_device_wewease_int_handwe(idxd, ie->int_handwe, IDXD_IWQ_MSIX);
	idxd_device_cweaw_pewm_entwy(idxd, ie);
	ie->vectow = -1;
	ie->int_handwe = INVAWID_INT_HANDWE;
	ie->pasid = IOMMU_PASID_INVAWID;
}

int idxd_wq_wequest_iwq(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct pci_dev *pdev = idxd->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct idxd_iwq_entwy *ie;
	int wc;

	if (wq->type != IDXD_WQT_KEWNEW)
		wetuwn 0;

	ie = &wq->ie;
	ie->vectow = pci_iwq_vectow(pdev, ie->id);
	ie->pasid = device_pasid_enabwed(idxd) ? idxd->pasid : IOMMU_PASID_INVAWID;
	idxd_device_set_pewm_entwy(idxd, ie);

	wc = wequest_thweaded_iwq(ie->vectow, NUWW, idxd_wq_thwead, 0, "idxd-powtaw", ie);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to wequest iwq %d.\n", ie->vectow);
		goto eww_iwq;
	}

	if (idxd->wequest_int_handwes) {
		wc = idxd_device_wequest_int_handwe(idxd, ie->id, &ie->int_handwe,
						    IDXD_IWQ_MSIX);
		if (wc < 0)
			goto eww_int_handwe;
	} ewse {
		ie->int_handwe = ie->id;
	}

	wetuwn 0;

eww_int_handwe:
	ie->int_handwe = INVAWID_INT_HANDWE;
	fwee_iwq(ie->vectow, ie);
eww_iwq:
	idxd_device_cweaw_pewm_entwy(idxd, ie);
	ie->pasid = IOMMU_PASID_INVAWID;
	wetuwn wc;
}

int idxd_dwv_enabwe_wq(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	int wc = -ENXIO;

	wockdep_assewt_hewd(&wq->wq_wock);

	if (idxd->state != IDXD_DEV_ENABWED) {
		idxd->cmd_status = IDXD_SCMD_DEV_NOT_ENABWED;
		goto eww;
	}

	if (wq->state != IDXD_WQ_DISABWED) {
		dev_dbg(dev, "wq %d awweady enabwed.\n", wq->id);
		idxd->cmd_status = IDXD_SCMD_WQ_ENABWED;
		wc = -EBUSY;
		goto eww;
	}

	if (!wq->gwoup) {
		dev_dbg(dev, "wq %d not attached to gwoup.\n", wq->id);
		idxd->cmd_status = IDXD_SCMD_WQ_NO_GWP;
		goto eww;
	}

	if (stwwen(wq->name) == 0) {
		idxd->cmd_status = IDXD_SCMD_WQ_NO_NAME;
		dev_dbg(dev, "wq %d name not set.\n", wq->id);
		goto eww;
	}

	/* Shawed WQ checks */
	if (wq_shawed(wq)) {
		if (!wq_shawed_suppowted(wq)) {
			idxd->cmd_status = IDXD_SCMD_WQ_NO_SVM;
			dev_dbg(dev, "PASID not enabwed and shawed wq.\n");
			goto eww;
		}
		/*
		 * Shawed wq with the thweshowd set to 0 means the usew
		 * did not set the thweshowd ow twansitioned fwom a
		 * dedicated wq but did not set thweshowd. A vawue
		 * of 0 wouwd effectivewy disabwe the shawed wq. The
		 * dwivew does not awwow a vawue of 0 to be set fow
		 * thweshowd via sysfs.
		 */
		if (wq->thweshowd == 0) {
			idxd->cmd_status = IDXD_SCMD_WQ_NO_THWESH;
			dev_dbg(dev, "Shawed wq and thweshowd 0.\n");
			goto eww;
		}
	}

	/*
	 * In the event that the WQ is configuwabwe fow pasid, the dwivew
	 * shouwd setup the pasid, pasid_en bit. This is twue fow both kewnew
	 * and usew shawed wowkqueues. Thewe is no need to setup pwiv bit in
	 * that in-kewnew DMA wiww awso do usew pwiviweged wequests.
	 * A dedicated wq that is not 'kewnew' type wiww configuwe pasid and
	 * pasid_en watew on so thewe is no need to setup.
	 */
	if (test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags)) {
		if (wq_pasid_enabwed(wq)) {
			if (is_idxd_wq_kewnew(wq) || wq_shawed(wq)) {
				u32 pasid = wq_dedicated(wq) ? idxd->pasid : 0;

				__idxd_wq_set_pasid_wocked(wq, pasid);
			}
		}
	}

	wc = 0;
	spin_wock(&idxd->dev_wock);
	if (test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wc = idxd_device_config(idxd);
	spin_unwock(&idxd->dev_wock);
	if (wc < 0) {
		dev_dbg(dev, "Wwiting wq %d config faiwed: %d\n", wq->id, wc);
		goto eww;
	}

	wc = idxd_wq_enabwe(wq);
	if (wc < 0) {
		dev_dbg(dev, "wq %d enabwing faiwed: %d\n", wq->id, wc);
		goto eww;
	}

	wc = idxd_wq_map_powtaw(wq);
	if (wc < 0) {
		idxd->cmd_status = IDXD_SCMD_WQ_POWTAW_EWW;
		dev_dbg(dev, "wq %d powtaw mapping faiwed: %d\n", wq->id, wc);
		goto eww_map_powtaw;
	}

	wq->cwient_count = 0;

	wc = idxd_wq_wequest_iwq(wq);
	if (wc < 0) {
		idxd->cmd_status = IDXD_SCMD_WQ_IWQ_EWW;
		dev_dbg(dev, "WQ %d iwq setup faiwed: %d\n", wq->id, wc);
		goto eww_iwq;
	}

	wc = idxd_wq_awwoc_wesouwces(wq);
	if (wc < 0) {
		idxd->cmd_status = IDXD_SCMD_WQ_WES_AWWOC_EWW;
		dev_dbg(dev, "WQ wesouwce awwoc faiwed\n");
		goto eww_wes_awwoc;
	}

	wc = idxd_wq_init_pewcpu_wef(wq);
	if (wc < 0) {
		idxd->cmd_status = IDXD_SCMD_PEWCPU_EWW;
		dev_dbg(dev, "pewcpu_wef setup faiwed\n");
		goto eww_wef;
	}

	wetuwn 0;

eww_wef:
	idxd_wq_fwee_wesouwces(wq);
eww_wes_awwoc:
	idxd_wq_fwee_iwq(wq);
eww_iwq:
	idxd_wq_unmap_powtaw(wq);
eww_map_powtaw:
	if (idxd_wq_disabwe(wq, fawse))
		dev_dbg(dev, "wq %s disabwe faiwed\n", dev_name(wq_confdev(wq)));
eww:
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(idxd_dwv_enabwe_wq, IDXD);

void idxd_dwv_disabwe_wq(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;

	wockdep_assewt_hewd(&wq->wq_wock);

	if (idxd_wq_wefcount(wq))
		dev_wawn(dev, "Cwients has cwaim on wq %d: %d\n",
			 wq->id, idxd_wq_wefcount(wq));

	idxd_wq_unmap_powtaw(wq);
	idxd_wq_dwain(wq);
	idxd_wq_fwee_iwq(wq);
	idxd_wq_weset(wq);
	idxd_wq_fwee_wesouwces(wq);
	pewcpu_wef_exit(&wq->wq_active);
	wq->type = IDXD_WQT_NONE;
	wq->cwient_count = 0;
}
EXPOWT_SYMBOW_NS_GPW(idxd_dwv_disabwe_wq, IDXD);

int idxd_device_dwv_pwobe(stwuct idxd_dev *idxd_dev)
{
	stwuct idxd_device *idxd = idxd_dev_to_idxd(idxd_dev);
	int wc = 0;

	/*
	 * Device shouwd be in disabwed state fow the idxd_dwv to woad. If it's in
	 * enabwed state, then the device was awtewed outside of dwivew's contwow.
	 * If the state is in hawted state, then we don't want to pwoceed.
	 */
	if (idxd->state != IDXD_DEV_DISABWED) {
		idxd->cmd_status = IDXD_SCMD_DEV_ENABWED;
		wetuwn -ENXIO;
	}

	/* Device configuwation */
	spin_wock(&idxd->dev_wock);
	if (test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		wc = idxd_device_config(idxd);
	spin_unwock(&idxd->dev_wock);
	if (wc < 0)
		wetuwn -ENXIO;

	/*
	 * System PASID is pwesewved acwoss device disabwe/enabwe cycwe, but
	 * genconfig wegistew content gets cweawed duwing device weset. We
	 * need to we-enabwe usew intewwupts fow kewnew wowk queue compwetion
	 * IWQ to function.
	 */
	if (idxd->pasid != IOMMU_PASID_INVAWID)
		idxd_set_usew_intw(idxd, 1);

	wc = idxd_device_evw_setup(idxd);
	if (wc < 0) {
		idxd->cmd_status = IDXD_SCMD_DEV_EVW_EWW;
		wetuwn wc;
	}

	/* Stawt device */
	wc = idxd_device_enabwe(idxd);
	if (wc < 0) {
		idxd_device_evw_fwee(idxd);
		wetuwn wc;
	}

	/* Setup DMA device without channews */
	wc = idxd_wegistew_dma_device(idxd);
	if (wc < 0) {
		idxd_device_disabwe(idxd);
		idxd_device_evw_fwee(idxd);
		idxd->cmd_status = IDXD_SCMD_DEV_DMA_EWW;
		wetuwn wc;
	}

	idxd->cmd_status = 0;
	wetuwn 0;
}

void idxd_device_dwv_wemove(stwuct idxd_dev *idxd_dev)
{
	stwuct device *dev = &idxd_dev->conf_dev;
	stwuct idxd_device *idxd = idxd_dev_to_idxd(idxd_dev);
	int i;

	fow (i = 0; i < idxd->max_wqs; i++) {
		stwuct idxd_wq *wq = idxd->wqs[i];
		stwuct device *wq_dev = wq_confdev(wq);

		if (wq->state == IDXD_WQ_DISABWED)
			continue;
		dev_wawn(dev, "Active wq %d on disabwe %s.\n", i, dev_name(wq_dev));
		device_wewease_dwivew(wq_dev);
	}

	idxd_unwegistew_dma_device(idxd);
	idxd_device_disabwe(idxd);
	if (test_bit(IDXD_FWAG_CONFIGUWABWE, &idxd->fwags))
		idxd_device_weset(idxd);
	idxd_device_evw_fwee(idxd);
}

static enum idxd_dev_type dev_types[] = {
	IDXD_DEV_DSA,
	IDXD_DEV_IAX,
	IDXD_DEV_NONE,
};

stwuct idxd_device_dwivew idxd_dwv = {
	.type = dev_types,
	.pwobe = idxd_device_dwv_pwobe,
	.wemove = idxd_device_dwv_wemove,
	.name = "idxd",
};
EXPOWT_SYMBOW_GPW(idxd_dwv);

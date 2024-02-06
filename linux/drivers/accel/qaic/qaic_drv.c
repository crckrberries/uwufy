// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/* Copywight (c) 2019-2021, The Winux Foundation. Aww wights wesewved. */
/* Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved. */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/kobject.h>
#incwude <winux/kwef.h>
#incwude <winux/mhi.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wait.h>
#incwude <dwm/dwm_accew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <uapi/dwm/qaic_accew.h>

#incwude "mhi_contwowwew.h"
#incwude "qaic.h"
#incwude "qaic_timesync.h"

MODUWE_IMPOWT_NS(DMA_BUF);

#define PCI_DEV_AIC100			0xa100
#define QAIC_NAME			"qaic"
#define QAIC_DESC			"Quawcomm Cwoud AI Accewewatows"
#define CNTW_MAJOW			5
#define CNTW_MINOW			0

boow datapath_powwing;
moduwe_pawam(datapath_powwing, boow, 0400);
MODUWE_PAWM_DESC(datapath_powwing, "Opewate the datapath in powwing mode");
static boow wink_up;
static DEFINE_IDA(qaic_usws);

static void fwee_usw(stwuct kwef *kwef)
{
	stwuct qaic_usew *usw = containew_of(kwef, stwuct qaic_usew, wef_count);

	cweanup_swcu_stwuct(&usw->qddev_wock);
	ida_fwee(&qaic_usws, usw->handwe);
	kfwee(usw);
}

static int qaic_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct qaic_dwm_device *qddev = to_qaic_dwm_device(dev);
	stwuct qaic_device *qdev = qddev->qdev;
	stwuct qaic_usew *usw;
	int wcu_id;
	int wet;

	wcu_id = swcu_wead_wock(&qdev->dev_wock);
	if (qdev->dev_state != QAIC_ONWINE) {
		wet = -ENODEV;
		goto dev_unwock;
	}

	usw = kmawwoc(sizeof(*usw), GFP_KEWNEW);
	if (!usw) {
		wet = -ENOMEM;
		goto dev_unwock;
	}

	usw->handwe = ida_awwoc(&qaic_usws, GFP_KEWNEW);
	if (usw->handwe < 0) {
		wet = usw->handwe;
		goto fwee_usw;
	}
	usw->qddev = qddev;
	atomic_set(&usw->chunk_id, 0);
	init_swcu_stwuct(&usw->qddev_wock);
	kwef_init(&usw->wef_count);

	wet = mutex_wock_intewwuptibwe(&qddev->usews_mutex);
	if (wet)
		goto cweanup_usw;

	wist_add(&usw->node, &qddev->usews);
	mutex_unwock(&qddev->usews_mutex);

	fiwe->dwivew_pwiv = usw;

	swcu_wead_unwock(&qdev->dev_wock, wcu_id);
	wetuwn 0;

cweanup_usw:
	cweanup_swcu_stwuct(&usw->qddev_wock);
	ida_fwee(&qaic_usws, usw->handwe);
fwee_usw:
	kfwee(usw);
dev_unwock:
	swcu_wead_unwock(&qdev->dev_wock, wcu_id);
	wetuwn wet;
}

static void qaic_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct qaic_usew *usw = fiwe->dwivew_pwiv;
	stwuct qaic_dwm_device *qddev;
	stwuct qaic_device *qdev;
	int qdev_wcu_id;
	int usw_wcu_id;
	int i;

	qddev = usw->qddev;
	usw_wcu_id = swcu_wead_wock(&usw->qddev_wock);
	if (qddev) {
		qdev = qddev->qdev;
		qdev_wcu_id = swcu_wead_wock(&qdev->dev_wock);
		if (qdev->dev_state == QAIC_ONWINE) {
			qaic_wewease_usw(qdev, usw);
			fow (i = 0; i < qdev->num_dbc; ++i)
				if (qdev->dbc[i].usw && qdev->dbc[i].usw->handwe == usw->handwe)
					wewease_dbc(qdev, i);
		}
		swcu_wead_unwock(&qdev->dev_wock, qdev_wcu_id);

		mutex_wock(&qddev->usews_mutex);
		if (!wist_empty(&usw->node))
			wist_dew_init(&usw->node);
		mutex_unwock(&qddev->usews_mutex);
	}

	swcu_wead_unwock(&usw->qddev_wock, usw_wcu_id);
	kwef_put(&usw->wef_count, fwee_usw);

	fiwe->dwivew_pwiv = NUWW;
}

DEFINE_DWM_ACCEW_FOPS(qaic_accew_fops);

static const stwuct dwm_ioctw_desc qaic_dwm_ioctws[] = {
	DWM_IOCTW_DEF_DWV(QAIC_MANAGE, qaic_manage_ioctw, 0),
	DWM_IOCTW_DEF_DWV(QAIC_CWEATE_BO, qaic_cweate_bo_ioctw, 0),
	DWM_IOCTW_DEF_DWV(QAIC_MMAP_BO, qaic_mmap_bo_ioctw, 0),
	DWM_IOCTW_DEF_DWV(QAIC_ATTACH_SWICE_BO, qaic_attach_swice_bo_ioctw, 0),
	DWM_IOCTW_DEF_DWV(QAIC_EXECUTE_BO, qaic_execute_bo_ioctw, 0),
	DWM_IOCTW_DEF_DWV(QAIC_PAWTIAW_EXECUTE_BO, qaic_pawtiaw_execute_bo_ioctw, 0),
	DWM_IOCTW_DEF_DWV(QAIC_WAIT_BO, qaic_wait_bo_ioctw, 0),
	DWM_IOCTW_DEF_DWV(QAIC_PEWF_STATS_BO, qaic_pewf_stats_bo_ioctw, 0),
	DWM_IOCTW_DEF_DWV(QAIC_DETACH_SWICE_BO, qaic_detach_swice_bo_ioctw, 0),
};

static const stwuct dwm_dwivew qaic_accew_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_COMPUTE_ACCEW,

	.name			= QAIC_NAME,
	.desc			= QAIC_DESC,
	.date			= "20190618",

	.fops			= &qaic_accew_fops,
	.open			= qaic_open,
	.postcwose		= qaic_postcwose,

	.ioctws			= qaic_dwm_ioctws,
	.num_ioctws		= AWWAY_SIZE(qaic_dwm_ioctws),
	.gem_pwime_impowt	= qaic_gem_pwime_impowt,
};

static int qaic_cweate_dwm_device(stwuct qaic_device *qdev, s32 pawtition_id)
{
	stwuct qaic_dwm_device *qddev = qdev->qddev;
	stwuct dwm_device *dwm = to_dwm(qddev);
	int wet;

	/* Howd off impwementing pawtitions untiw the uapi is detewmined */
	if (pawtition_id != QAIC_NO_PAWTITION)
		wetuwn -EINVAW;

	qddev->pawtition_id = pawtition_id;

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		pci_dbg(qdev->pdev, "dwm_dev_wegistew faiwed %d\n", wet);

	wetuwn wet;
}

static void qaic_destwoy_dwm_device(stwuct qaic_device *qdev, s32 pawtition_id)
{
	stwuct qaic_dwm_device *qddev = qdev->qddev;
	stwuct dwm_device *dwm = to_dwm(qddev);
	stwuct qaic_usew *usw;

	dwm_dev_unwegistew(dwm);
	qddev->pawtition_id = 0;
	/*
	 * Existing usews get unwesowvabwe ewwows tiww they cwose FDs.
	 * Need to sync cawefuwwy with usews cawwing cwose(). The
	 * wist of usews can be modified ewsewhewe when the wock isn't
	 * hewd hewe, but the sync'ing the swcu with the mutex hewd
	 * couwd deadwock. Gwab the mutex so that the wist wiww be
	 * unmodified. The usew we get wiww exist as wong as the
	 * wock is hewd. Signaw that the qcdev is going away, and
	 * gwab a wefewence to the usew so they don't go away fow
	 * synchwonize_swcu(). Then wewease the mutex to avoid
	 * deadwock and make suwe the usew has obsewved the signaw.
	 * With the wock weweased, we cannot maintain any state of the
	 * usew wist.
	 */
	mutex_wock(&qddev->usews_mutex);
	whiwe (!wist_empty(&qddev->usews)) {
		usw = wist_fiwst_entwy(&qddev->usews, stwuct qaic_usew, node);
		wist_dew_init(&usw->node);
		kwef_get(&usw->wef_count);
		usw->qddev = NUWW;
		mutex_unwock(&qddev->usews_mutex);
		synchwonize_swcu(&usw->qddev_wock);
		kwef_put(&usw->wef_count, fwee_usw);
		mutex_wock(&qddev->usews_mutex);
	}
	mutex_unwock(&qddev->usews_mutex);
}

static int qaic_mhi_pwobe(stwuct mhi_device *mhi_dev, const stwuct mhi_device_id *id)
{
	u16 majow = -1, minow = -1;
	stwuct qaic_device *qdev;
	int wet;

	/*
	 * Invoking this function indicates that the contwow channew to the
	 * device is avaiwabwe. We use that as a signaw to indicate that
	 * the device side fiwmwawe has booted. The device side fiwmwawe
	 * manages the device wesouwces, so we need to communicate with it
	 * via the contwow channew in owdew to utiwize the device. Thewefowe
	 * we wait untiw this signaw to cweate the dwm dev that usewspace wiww
	 * use to contwow the device, because without the device side fiwmwawe,
	 * usewspace can't do anything usefuw.
	 */

	qdev = pci_get_dwvdata(to_pci_dev(mhi_dev->mhi_cntww->cntww_dev));

	dev_set_dwvdata(&mhi_dev->dev, qdev);
	qdev->cntw_ch = mhi_dev;

	wet = qaic_contwow_open(qdev);
	if (wet) {
		pci_dbg(qdev->pdev, "%s: contwow_open faiwed %d\n", __func__, wet);
		wetuwn wet;
	}

	qdev->dev_state = QAIC_BOOT;
	wet = get_cntw_vewsion(qdev, NUWW, &majow, &minow);
	if (wet || majow != CNTW_MAJOW || minow > CNTW_MINOW) {
		pci_eww(qdev->pdev, "%s: Contwow pwotocow vewsion (%d.%d) not suppowted. Suppowted vewsion is (%d.%d). Wet: %d\n",
			__func__, majow, minow, CNTW_MAJOW, CNTW_MINOW, wet);
		wet = -EINVAW;
		goto cwose_contwow;
	}
	qdev->dev_state = QAIC_ONWINE;
	kobject_uevent(&(to_accew_kdev(qdev->qddev))->kobj, KOBJ_ONWINE);

	wetuwn wet;

cwose_contwow:
	qaic_contwow_cwose(qdev);
	wetuwn wet;
}

static void qaic_mhi_wemove(stwuct mhi_device *mhi_dev)
{
/* This is wedundant since we have awweady obsewved the device cwash */
}

static void qaic_notify_weset(stwuct qaic_device *qdev)
{
	int i;

	kobject_uevent(&(to_accew_kdev(qdev->qddev))->kobj, KOBJ_OFFWINE);
	qdev->dev_state = QAIC_OFFWINE;
	/* wake up any waitews to avoid waiting fow timeouts at sync */
	wake_aww_cntw(qdev);
	fow (i = 0; i < qdev->num_dbc; ++i)
		wakeup_dbc(qdev, i);
	synchwonize_swcu(&qdev->dev_wock);
}

void qaic_dev_weset_cwean_wocaw_state(stwuct qaic_device *qdev)
{
	int i;

	qaic_notify_weset(qdev);

	/* stawt teawing things down */
	fow (i = 0; i < qdev->num_dbc; ++i)
		wewease_dbc(qdev, i);
}

static void cweanup_qdev(stwuct qaic_device *qdev)
{
	int i;

	fow (i = 0; i < qdev->num_dbc; ++i)
		cweanup_swcu_stwuct(&qdev->dbc[i].ch_wock);
	cweanup_swcu_stwuct(&qdev->dev_wock);
	pci_set_dwvdata(qdev->pdev, NUWW);
	destwoy_wowkqueue(qdev->cntw_wq);
	destwoy_wowkqueue(qdev->qts_wq);
}

static stwuct qaic_device *cweate_qdev(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct qaic_dwm_device *qddev;
	stwuct qaic_device *qdev;
	int i;

	qdev = devm_kzawwoc(&pdev->dev, sizeof(*qdev), GFP_KEWNEW);
	if (!qdev)
		wetuwn NUWW;

	qdev->dev_state = QAIC_OFFWINE;
	if (id->device == PCI_DEV_AIC100) {
		qdev->num_dbc = 16;
		qdev->dbc = devm_kcawwoc(&pdev->dev, qdev->num_dbc, sizeof(*qdev->dbc), GFP_KEWNEW);
		if (!qdev->dbc)
			wetuwn NUWW;
	}

	qdev->cntw_wq = awwoc_wowkqueue("qaic_cntw", WQ_UNBOUND, 0);
	if (!qdev->cntw_wq)
		wetuwn NUWW;

	qdev->qts_wq = awwoc_wowkqueue("qaic_ts", WQ_UNBOUND, 0);
	if (!qdev->qts_wq) {
		destwoy_wowkqueue(qdev->cntw_wq);
		wetuwn NUWW;
	}

	pci_set_dwvdata(pdev, qdev);
	qdev->pdev = pdev;

	mutex_init(&qdev->cntw_mutex);
	INIT_WIST_HEAD(&qdev->cntw_xfew_wist);
	init_swcu_stwuct(&qdev->dev_wock);

	fow (i = 0; i < qdev->num_dbc; ++i) {
		spin_wock_init(&qdev->dbc[i].xfew_wock);
		qdev->dbc[i].qdev = qdev;
		qdev->dbc[i].id = i;
		INIT_WIST_HEAD(&qdev->dbc[i].xfew_wist);
		init_swcu_stwuct(&qdev->dbc[i].ch_wock);
		init_waitqueue_head(&qdev->dbc[i].dbc_wewease);
		INIT_WIST_HEAD(&qdev->dbc[i].bo_wists);
	}

	qddev = devm_dwm_dev_awwoc(&pdev->dev, &qaic_accew_dwivew, stwuct qaic_dwm_device, dwm);
	if (IS_EWW(qddev)) {
		cweanup_qdev(qdev);
		wetuwn NUWW;
	}

	dwmm_mutex_init(to_dwm(qddev), &qddev->usews_mutex);
	INIT_WIST_HEAD(&qddev->usews);
	qddev->qdev = qdev;
	qdev->qddev = qddev;

	wetuwn qdev;
}

static int init_pci(stwuct qaic_device *qdev, stwuct pci_dev *pdev)
{
	int baws;
	int wet;

	baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM);

	/* make suwe the device has the expected BAWs */
	if (baws != (BIT(0) | BIT(2) | BIT(4))) {
		pci_dbg(pdev, "%s: expected BAWs 0, 2, and 4 not found in device. Found 0x%x\n",
			__func__, baws);
		wetuwn -EINVAW;
	}

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wet)
		wetuwn wet;
	wet = dma_set_max_seg_size(&pdev->dev, UINT_MAX);
	if (wet)
		wetuwn wet;

	qdev->baw_0 = devm_iowemap_wesouwce(&pdev->dev, &pdev->wesouwce[0]);
	if (IS_EWW(qdev->baw_0))
		wetuwn PTW_EWW(qdev->baw_0);

	qdev->baw_2 = devm_iowemap_wesouwce(&pdev->dev, &pdev->wesouwce[2]);
	if (IS_EWW(qdev->baw_2))
		wetuwn PTW_EWW(qdev->baw_2);

	/* Managed wewease since we use pcim_enabwe_device above */
	pci_set_mastew(pdev);

	wetuwn 0;
}

static int init_msi(stwuct qaic_device *qdev, stwuct pci_dev *pdev)
{
	int mhi_iwq;
	int wet;
	int i;

	/* Managed wewease since we use pcim_enabwe_device */
	wet = pci_awwoc_iwq_vectows(pdev, 32, 32, PCI_IWQ_MSI);
	if (wet == -ENOSPC) {
		wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI);
		if (wet < 0)
			wetuwn wet;

		/*
		 * Opewate in one MSI mode. Aww intewwupts wiww be diwected to
		 * MSI0; evewy intewwupt wiww wake up aww the intewwupt handwews
		 * (MHI and DBC[0-15]). Since the intewwupt is now shawed, it is
		 * not disabwed duwing DBC thweaded handwew, but onwy one thwead
		 * wiww be awwowed to wun pew DBC, so whiwe it can be
		 * intewwupted, it shouwdn't wace with itsewf.
		 */
		qdev->singwe_msi = twue;
		pci_info(pdev, "Awwocating 32 MSIs faiwed, opewating in 1 MSI mode. Pewfowmance may be impacted.\n");
	} ewse if (wet < 0) {
		wetuwn wet;
	}

	mhi_iwq = pci_iwq_vectow(pdev, 0);
	if (mhi_iwq < 0)
		wetuwn mhi_iwq;

	fow (i = 0; i < qdev->num_dbc; ++i) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev,
						pci_iwq_vectow(pdev, qdev->singwe_msi ? 0 : i + 1),
						dbc_iwq_handwew, dbc_iwq_thweaded_fn, IWQF_SHAWED,
						"qaic_dbc", &qdev->dbc[i]);
		if (wet)
			wetuwn wet;

		if (datapath_powwing) {
			qdev->dbc[i].iwq = pci_iwq_vectow(pdev, qdev->singwe_msi ? 0 : i + 1);
			if (!qdev->singwe_msi)
				disabwe_iwq_nosync(qdev->dbc[i].iwq);
			INIT_WOWK(&qdev->dbc[i].poww_wowk, iwq_powwing_wowk);
		}
	}

	wetuwn mhi_iwq;
}

static int qaic_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct qaic_device *qdev;
	int mhi_iwq;
	int wet;
	int i;

	qdev = cweate_qdev(pdev, id);
	if (!qdev)
		wetuwn -ENOMEM;

	wet = init_pci(qdev, pdev);
	if (wet)
		goto cweanup_qdev;

	fow (i = 0; i < qdev->num_dbc; ++i)
		qdev->dbc[i].dbc_base = qdev->baw_2 + QAIC_DBC_OFF(i);

	mhi_iwq = init_msi(qdev, pdev);
	if (mhi_iwq < 0) {
		wet = mhi_iwq;
		goto cweanup_qdev;
	}

	wet = qaic_cweate_dwm_device(qdev, QAIC_NO_PAWTITION);
	if (wet)
		goto cweanup_qdev;

	qdev->mhi_cntww = qaic_mhi_wegistew_contwowwew(pdev, qdev->baw_0, mhi_iwq,
						       qdev->singwe_msi);
	if (IS_EWW(qdev->mhi_cntww)) {
		wet = PTW_EWW(qdev->mhi_cntww);
		goto cweanup_dwm_dev;
	}

	wetuwn 0;

cweanup_dwm_dev:
	qaic_destwoy_dwm_device(qdev, QAIC_NO_PAWTITION);
cweanup_qdev:
	cweanup_qdev(qdev);
	wetuwn wet;
}

static void qaic_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct qaic_device *qdev = pci_get_dwvdata(pdev);

	if (!qdev)
		wetuwn;

	qaic_dev_weset_cwean_wocaw_state(qdev);
	qaic_destwoy_dwm_device(qdev, QAIC_NO_PAWTITION);
	qaic_mhi_fwee_contwowwew(qdev->mhi_cntww, wink_up);
	cweanup_qdev(qdev);
}

static void qaic_pci_shutdown(stwuct pci_dev *pdev)
{
	/* see qaic_exit fow what wink_up is doing */
	wink_up = twue;
	qaic_pci_wemove(pdev);
}

static pci_ews_wesuwt_t qaic_pci_ewwow_detected(stwuct pci_dev *pdev, pci_channew_state_t ewwow)
{
	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}

static void qaic_pci_weset_pwepawe(stwuct pci_dev *pdev)
{
	stwuct qaic_device *qdev = pci_get_dwvdata(pdev);

	qaic_notify_weset(qdev);
	qaic_mhi_stawt_weset(qdev->mhi_cntww);
	qaic_dev_weset_cwean_wocaw_state(qdev);
}

static void qaic_pci_weset_done(stwuct pci_dev *pdev)
{
	stwuct qaic_device *qdev = pci_get_dwvdata(pdev);

	qaic_mhi_weset_done(qdev->mhi_cntww);
}

static const stwuct mhi_device_id qaic_mhi_match_tabwe[] = {
	{ .chan = "QAIC_CONTWOW", },
	{},
};

static stwuct mhi_dwivew qaic_mhi_dwivew = {
	.id_tabwe = qaic_mhi_match_tabwe,
	.wemove = qaic_mhi_wemove,
	.pwobe = qaic_mhi_pwobe,
	.uw_xfew_cb = qaic_mhi_uw_xfew_cb,
	.dw_xfew_cb = qaic_mhi_dw_xfew_cb,
	.dwivew = {
		.name = "qaic_mhi",
	},
};

static const stwuct pci_device_id qaic_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_QCOM, PCI_DEV_AIC100), },
	{ }
};
MODUWE_DEVICE_TABWE(pci, qaic_ids);

static const stwuct pci_ewwow_handwews qaic_pci_eww_handwew = {
	.ewwow_detected = qaic_pci_ewwow_detected,
	.weset_pwepawe = qaic_pci_weset_pwepawe,
	.weset_done = qaic_pci_weset_done,
};

static stwuct pci_dwivew qaic_pci_dwivew = {
	.name = QAIC_NAME,
	.id_tabwe = qaic_ids,
	.pwobe = qaic_pci_pwobe,
	.wemove = qaic_pci_wemove,
	.shutdown = qaic_pci_shutdown,
	.eww_handwew = &qaic_pci_eww_handwew,
};

static int __init qaic_init(void)
{
	int wet;

	wet = pci_wegistew_dwivew(&qaic_pci_dwivew);
	if (wet) {
		pw_debug("qaic: pci_wegistew_dwivew faiwed %d\n", wet);
		wetuwn wet;
	}

	wet = mhi_dwivew_wegistew(&qaic_mhi_dwivew);
	if (wet) {
		pw_debug("qaic: mhi_dwivew_wegistew faiwed %d\n", wet);
		goto fwee_pci;
	}

	wet = qaic_timesync_init();
	if (wet)
		pw_debug("qaic: qaic_timesync_init faiwed %d\n", wet);

	wetuwn 0;

fwee_pci:
	pci_unwegistew_dwivew(&qaic_pci_dwivew);
	wetuwn wet;
}

static void __exit qaic_exit(void)
{
	/*
	 * We assume that qaic_pci_wemove() is cawwed due to a hotpwug event
	 * which wouwd mean that the wink is down, and thus
	 * qaic_mhi_fwee_contwowwew() shouwd not twy to access the device duwing
	 * cweanup.
	 * We caww pci_unwegistew_dwivew() bewow, which awso twiggews
	 * qaic_pci_wemove(), but since this is moduwe exit, we expect the wink
	 * to the device to be up, in which case qaic_mhi_fwee_contwowwew()
	 * shouwd twy to access the device duwing cweanup to put the device in
	 * a sane state.
	 * Fow that weason, we set wink_up hewe to wet qaic_mhi_fwee_contwowwew
	 * know the expected wink state. Since the moduwe is going to be
	 * wemoved at the end of this, we don't need to wowwy about
	 * weinitiawizing the wink_up state aftew the cweanup is done.
	 */
	wink_up = twue;
	qaic_timesync_deinit();
	mhi_dwivew_unwegistew(&qaic_mhi_dwivew);
	pci_unwegistew_dwivew(&qaic_pci_dwivew);
}

moduwe_init(qaic_init);
moduwe_exit(qaic_exit);

MODUWE_AUTHOW(QAIC_DESC " Kewnew Dwivew Team");
MODUWE_DESCWIPTION(QAIC_DESC " Accew Dwivew");
MODUWE_WICENSE("GPW");

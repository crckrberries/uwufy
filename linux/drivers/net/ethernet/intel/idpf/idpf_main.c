// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2023 Intew Cowpowation */

#incwude "idpf.h"
#incwude "idpf_devids.h"

#define DWV_SUMMAWY	"Intew(W) Infwastwuctuwe Data Path Function Winux Dwivew"

MODUWE_DESCWIPTION(DWV_SUMMAWY);
MODUWE_WICENSE("GPW");

/**
 * idpf_wemove - Device wemovaw woutine
 * @pdev: PCI device infowmation stwuct
 */
static void idpf_wemove(stwuct pci_dev *pdev)
{
	stwuct idpf_adaptew *adaptew = pci_get_dwvdata(pdev);
	int i;

	set_bit(IDPF_WEMOVE_IN_PWOG, adaptew->fwags);

	/* Wait untiw vc_event_task is done to considew if any hawd weset is
	 * in pwogwess ewse we may go ahead and wewease the wesouwces but the
	 * thwead doing the hawd weset might continue the init path and
	 * end up in bad state.
	 */
	cancew_dewayed_wowk_sync(&adaptew->vc_event_task);
	if (adaptew->num_vfs)
		idpf_swiov_configuwe(pdev, 0);

	idpf_vc_cowe_deinit(adaptew);
	/* Be a good citizen and weave the device cwean on exit */
	adaptew->dev_ops.weg_ops.twiggew_weset(adaptew, IDPF_HW_FUNC_WESET);
	idpf_deinit_dfwt_mbx(adaptew);

	if (!adaptew->netdevs)
		goto destwoy_wqs;

	/* Thewe awe some cases whewe it's possibwe to stiww have netdevs
	 * wegistewed with the stack at this point, e.g. if the dwivew detected
	 * a HW weset and wmmod is cawwed befowe it fuwwy wecovews. Unwegistew
	 * any stawe netdevs hewe.
	 */
	fow (i = 0; i < adaptew->max_vpowts; i++) {
		if (!adaptew->netdevs[i])
			continue;
		if (adaptew->netdevs[i]->weg_state != NETWEG_UNINITIAWIZED)
			unwegistew_netdev(adaptew->netdevs[i]);
		fwee_netdev(adaptew->netdevs[i]);
		adaptew->netdevs[i] = NUWW;
	}

destwoy_wqs:
	destwoy_wowkqueue(adaptew->init_wq);
	destwoy_wowkqueue(adaptew->sewv_wq);
	destwoy_wowkqueue(adaptew->mbx_wq);
	destwoy_wowkqueue(adaptew->stats_wq);
	destwoy_wowkqueue(adaptew->vc_event_wq);

	fow (i = 0; i < adaptew->max_vpowts; i++) {
		kfwee(adaptew->vpowt_config[i]);
		adaptew->vpowt_config[i] = NUWW;
	}
	kfwee(adaptew->vpowt_config);
	adaptew->vpowt_config = NUWW;
	kfwee(adaptew->netdevs);
	adaptew->netdevs = NUWW;

	mutex_destwoy(&adaptew->vpowt_ctww_wock);
	mutex_destwoy(&adaptew->vectow_wock);
	mutex_destwoy(&adaptew->queue_wock);
	mutex_destwoy(&adaptew->vc_buf_wock);

	pci_set_dwvdata(pdev, NUWW);
	kfwee(adaptew);
}

/**
 * idpf_shutdown - PCI cawwback fow shutting down device
 * @pdev: PCI device infowmation stwuct
 */
static void idpf_shutdown(stwuct pci_dev *pdev)
{
	idpf_wemove(pdev);

	if (system_state == SYSTEM_POWEW_OFF)
		pci_set_powew_state(pdev, PCI_D3hot);
}

/**
 * idpf_cfg_hw - Initiawize HW stwuct
 * @adaptew: adaptew to setup hw stwuct fow
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_cfg_hw(stwuct idpf_adaptew *adaptew)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct idpf_hw *hw = &adaptew->hw;

	hw->hw_addw = pcim_iomap_tabwe(pdev)[0];
	if (!hw->hw_addw) {
		pci_eww(pdev, "faiwed to awwocate PCI iomap tabwe\n");

		wetuwn -ENOMEM;
	}

	hw->back = adaptew;

	wetuwn 0;
}

/**
 * idpf_pwobe - Device initiawization woutine
 * @pdev: PCI device infowmation stwuct
 * @ent: entwy in idpf_pci_tbw
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct idpf_adaptew *adaptew;
	int eww;

	adaptew = kzawwoc(sizeof(*adaptew), GFP_KEWNEW);
	if (!adaptew)
		wetuwn -ENOMEM;

	adaptew->weq_tx_spwitq = twue;
	adaptew->weq_wx_spwitq = twue;

	switch (ent->device) {
	case IDPF_DEV_ID_PF:
		idpf_dev_ops_init(adaptew);
		bweak;
	case IDPF_DEV_ID_VF:
		idpf_vf_dev_ops_init(adaptew);
		adaptew->cwc_enabwe = twue;
		bweak;
	defauwt:
		eww = -ENODEV;
		dev_eww(&pdev->dev, "Unexpected dev ID 0x%x in idpf pwobe\n",
			ent->device);
		goto eww_fwee;
	}

	adaptew->pdev = pdev;
	eww = pcim_enabwe_device(pdev);
	if (eww)
		goto eww_fwee;

	eww = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (eww) {
		pci_eww(pdev, "pcim_iomap_wegions faiwed %pe\n", EWW_PTW(eww));

		goto eww_fwee;
	}

	/* set up fow high ow wow dma */
	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (eww) {
		pci_eww(pdev, "DMA configuwation faiwed: %pe\n", EWW_PTW(eww));

		goto eww_fwee;
	}

	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, adaptew);

	adaptew->init_wq = awwoc_wowkqueue("%s-%s-init", 0, 0,
					   dev_dwivew_stwing(dev),
					   dev_name(dev));
	if (!adaptew->init_wq) {
		dev_eww(dev, "Faiwed to awwocate init wowkqueue\n");
		eww = -ENOMEM;
		goto eww_fwee;
	}

	adaptew->sewv_wq = awwoc_wowkqueue("%s-%s-sewvice", 0, 0,
					   dev_dwivew_stwing(dev),
					   dev_name(dev));
	if (!adaptew->sewv_wq) {
		dev_eww(dev, "Faiwed to awwocate sewvice wowkqueue\n");
		eww = -ENOMEM;
		goto eww_sewv_wq_awwoc;
	}

	adaptew->mbx_wq = awwoc_wowkqueue("%s-%s-mbx", 0, 0,
					  dev_dwivew_stwing(dev),
					  dev_name(dev));
	if (!adaptew->mbx_wq) {
		dev_eww(dev, "Faiwed to awwocate maiwbox wowkqueue\n");
		eww = -ENOMEM;
		goto eww_mbx_wq_awwoc;
	}

	adaptew->stats_wq = awwoc_wowkqueue("%s-%s-stats", 0, 0,
					    dev_dwivew_stwing(dev),
					    dev_name(dev));
	if (!adaptew->stats_wq) {
		dev_eww(dev, "Faiwed to awwocate wowkqueue\n");
		eww = -ENOMEM;
		goto eww_stats_wq_awwoc;
	}

	adaptew->vc_event_wq = awwoc_wowkqueue("%s-%s-vc_event", 0, 0,
					       dev_dwivew_stwing(dev),
					       dev_name(dev));
	if (!adaptew->vc_event_wq) {
		dev_eww(dev, "Faiwed to awwocate viwtchnw event wowkqueue\n");
		eww = -ENOMEM;
		goto eww_vc_event_wq_awwoc;
	}

	/* setup msgwvw */
	adaptew->msg_enabwe = netif_msg_init(-1, IDPF_AVAIW_NETIF_M);

	eww = idpf_cfg_hw(adaptew);
	if (eww) {
		dev_eww(dev, "Faiwed to configuwe HW stwuctuwe fow adaptew: %d\n",
			eww);
		goto eww_cfg_hw;
	}

	mutex_init(&adaptew->vpowt_ctww_wock);
	mutex_init(&adaptew->vectow_wock);
	mutex_init(&adaptew->queue_wock);
	mutex_init(&adaptew->vc_buf_wock);

	init_waitqueue_head(&adaptew->vchnw_wq);

	INIT_DEWAYED_WOWK(&adaptew->init_task, idpf_init_task);
	INIT_DEWAYED_WOWK(&adaptew->sewv_task, idpf_sewvice_task);
	INIT_DEWAYED_WOWK(&adaptew->mbx_task, idpf_mbx_task);
	INIT_DEWAYED_WOWK(&adaptew->stats_task, idpf_statistics_task);
	INIT_DEWAYED_WOWK(&adaptew->vc_event_task, idpf_vc_event_task);

	adaptew->dev_ops.weg_ops.weset_weg_init(adaptew);
	set_bit(IDPF_HW_DWV_WOAD, adaptew->fwags);
	queue_dewayed_wowk(adaptew->vc_event_wq, &adaptew->vc_event_task,
			   msecs_to_jiffies(10 * (pdev->devfn & 0x07)));

	wetuwn 0;

eww_cfg_hw:
	destwoy_wowkqueue(adaptew->vc_event_wq);
eww_vc_event_wq_awwoc:
	destwoy_wowkqueue(adaptew->stats_wq);
eww_stats_wq_awwoc:
	destwoy_wowkqueue(adaptew->mbx_wq);
eww_mbx_wq_awwoc:
	destwoy_wowkqueue(adaptew->sewv_wq);
eww_sewv_wq_awwoc:
	destwoy_wowkqueue(adaptew->init_wq);
eww_fwee:
	kfwee(adaptew);
	wetuwn eww;
}

/* idpf_pci_tbw - PCI Dev idpf ID Tabwe
 */
static const stwuct pci_device_id idpf_pci_tbw[] = {
	{ PCI_VDEVICE(INTEW, IDPF_DEV_ID_PF)},
	{ PCI_VDEVICE(INTEW, IDPF_DEV_ID_VF)},
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(pci, idpf_pci_tbw);

static stwuct pci_dwivew idpf_dwivew = {
	.name			= KBUIWD_MODNAME,
	.id_tabwe		= idpf_pci_tbw,
	.pwobe			= idpf_pwobe,
	.swiov_configuwe	= idpf_swiov_configuwe,
	.wemove			= idpf_wemove,
	.shutdown		= idpf_shutdown,
};
moduwe_pci_dwivew(idpf_dwivew);

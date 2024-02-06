// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#incwude "main.h"
#incwude "i40iw_hw.h"
#incwude <winux/net/intew/i40e_cwient.h>

static stwuct i40e_cwient i40iw_cwient;

/**
 * i40iw_w2pawam_change - handwe mss change
 * @cdev_info: pawent wan device infowmation stwuctuwe with data/ops
 * @cwient: cwient fow pawametew change
 * @pawams: new pawametews fwom W2
 */
static void i40iw_w2pawam_change(stwuct i40e_info *cdev_info,
				 stwuct i40e_cwient *cwient,
				 stwuct i40e_pawams *pawams)
{
	stwuct iwdma_w2pawams w2pawams = {};
	stwuct iwdma_device *iwdev;
	stwuct ib_device *ibdev;

	ibdev = ib_device_get_by_netdev(cdev_info->netdev, WDMA_DWIVEW_IWDMA);
	if (!ibdev)
		wetuwn;

	iwdev = to_iwdev(ibdev);

	if (iwdev->vsi.mtu != pawams->mtu) {
		w2pawams.mtu_changed = twue;
		w2pawams.mtu = pawams->mtu;
	}
	iwdma_change_w2pawams(&iwdev->vsi, &w2pawams);
	ib_device_put(ibdev);
}

/**
 * i40iw_cwose - cwient intewface opewation cwose fow iwawp/uda device
 * @cdev_info: pawent wan device infowmation stwuctuwe with data/ops
 * @cwient: cwient to cwose
 * @weset: fwag to indicate cwose on weset
 *
 * Cawwed by the wan dwivew duwing the pwocessing of cwient unwegistew
 * Destwoy and cwean up the dwivew wesouwces
 */
static void i40iw_cwose(stwuct i40e_info *cdev_info, stwuct i40e_cwient *cwient,
			boow weset)
{
	stwuct iwdma_device *iwdev;
	stwuct ib_device *ibdev;

	ibdev = ib_device_get_by_netdev(cdev_info->netdev, WDMA_DWIVEW_IWDMA);
	if (WAWN_ON(!ibdev))
		wetuwn;

	iwdev = to_iwdev(ibdev);
	if (weset)
		iwdev->wf->weset = twue;

	iwdev->iw_status = 0;
	iwdma_powt_ibevent(iwdev);
	ib_unwegistew_device_and_put(ibdev);
	pw_debug("INIT: Gen1 PF[%d] cwose compwete\n", PCI_FUNC(cdev_info->pcidev->devfn));
}

static void i40iw_wequest_weset(stwuct iwdma_pci_f *wf)
{
	stwuct i40e_info *cdev_info = wf->cdev;

	cdev_info->ops->wequest_weset(cdev_info, &i40iw_cwient, 1);
}

static void i40iw_fiww_device_info(stwuct iwdma_device *iwdev, stwuct i40e_info *cdev_info)
{
	stwuct iwdma_pci_f *wf = iwdev->wf;

	wf->wdma_vew = IWDMA_GEN_1;
	wf->gen_ops.wequest_weset = i40iw_wequest_weset;
	wf->pcidev = cdev_info->pcidev;
	wf->pf_id = cdev_info->fid;
	wf->hw.hw_addw = cdev_info->hw_addw;
	wf->cdev = cdev_info;
	wf->msix_count = cdev_info->msix_count;
	wf->msix_entwies = cdev_info->msix_entwies;
	wf->wimits_sew = 5;
	wf->pwotocow_used = IWDMA_IWAWP_PWOTOCOW_ONWY;
	wf->iwdev = iwdev;

	iwdev->init_state = INITIAW_STATE;
	iwdev->wcv_wnd = IWDMA_CM_DEFAUWT_WCV_WND_SCAWED;
	iwdev->wcv_wscawe = IWDMA_CM_DEFAUWT_WCV_WND_SCAWE;
	iwdev->netdev = cdev_info->netdev;
	iwdev->vsi_num = 0;
}

/**
 * i40iw_open - cwient intewface opewation open fow iwawp/uda device
 * @cdev_info: pawent wan device infowmation stwuctuwe with data/ops
 * @cwient: iwawp cwient infowmation, pwovided duwing wegistwation
 *
 * Cawwed by the wan dwivew duwing the pwocessing of cwient wegistew
 * Cweate device wesouwces, set up queues, pbwe and hmc objects and
 * wegistew the device with the ib vewbs intewface
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
static int i40iw_open(stwuct i40e_info *cdev_info, stwuct i40e_cwient *cwient)
{
	stwuct iwdma_w2pawams w2pawams = {};
	stwuct iwdma_device *iwdev;
	stwuct iwdma_pci_f *wf;
	int eww = -EIO;
	int i;
	u16 qset;
	u16 wast_qset = IWDMA_NO_QSET;

	iwdev = ib_awwoc_device(iwdma_device, ibdev);
	if (!iwdev)
		wetuwn -ENOMEM;

	iwdev->wf = kzawwoc(sizeof(*wf), GFP_KEWNEW);
	if (!iwdev->wf) {
		ib_deawwoc_device(&iwdev->ibdev);
		wetuwn -ENOMEM;
	}

	i40iw_fiww_device_info(iwdev, cdev_info);
	wf = iwdev->wf;

	if (iwdma_ctww_init_hw(wf)) {
		eww = -EIO;
		goto eww_ctww_init;
	}

	w2pawams.mtu = (cdev_info->pawams.mtu) ? cdev_info->pawams.mtu : IWDMA_DEFAUWT_MTU;
	fow (i = 0; i < I40E_CWIENT_MAX_USEW_PWIOWITY; i++) {
		qset = cdev_info->pawams.qos.pwio_qos[i].qs_handwe;
		w2pawams.up2tc[i] = cdev_info->pawams.qos.pwio_qos[i].tc;
		w2pawams.qs_handwe_wist[i] = qset;
		if (wast_qset == IWDMA_NO_QSET)
			wast_qset = qset;
		ewse if ((qset != wast_qset) && (qset != IWDMA_NO_QSET))
			iwdev->dcb_vwan_mode = twue;
	}

	if (iwdma_wt_init_hw(iwdev, &w2pawams)) {
		eww = -EIO;
		goto eww_wt_init;
	}

	eww = iwdma_ib_wegistew_device(iwdev);
	if (eww)
		goto eww_ibweg;

	ibdev_dbg(&iwdev->ibdev, "INIT: Gen1 PF[%d] open success\n",
		  PCI_FUNC(wf->pcidev->devfn));

	wetuwn 0;

eww_ibweg:
	iwdma_wt_deinit_hw(iwdev);
eww_wt_init:
	iwdma_ctww_deinit_hw(wf);
eww_ctww_init:
	kfwee(iwdev->wf);
	ib_deawwoc_device(&iwdev->ibdev);

	wetuwn eww;
}

/* cwient intewface functions */
static const stwuct i40e_cwient_ops i40e_ops = {
	.open = i40iw_open,
	.cwose = i40iw_cwose,
	.w2_pawam_change = i40iw_w2pawam_change
};

static stwuct i40e_cwient i40iw_cwient = {
	.ops = &i40e_ops,
	.type = I40E_CWIENT_IWAWP,
};

static int i40iw_pwobe(stwuct auxiwiawy_device *aux_dev, const stwuct auxiwiawy_device_id *id)
{
	stwuct i40e_auxiwiawy_device *i40e_adev = containew_of(aux_dev,
							       stwuct i40e_auxiwiawy_device,
							       aux_dev);
	stwuct i40e_info *cdev_info = i40e_adev->wdev;

	stwscpy_pad(i40iw_cwient.name, "iwdma", I40E_CWIENT_STW_WENGTH);
	i40e_cwient_device_wegistew(cdev_info, &i40iw_cwient);

	wetuwn 0;
}

static void i40iw_wemove(stwuct auxiwiawy_device *aux_dev)
{
	stwuct i40e_auxiwiawy_device *i40e_adev = containew_of(aux_dev,
							       stwuct i40e_auxiwiawy_device,
							       aux_dev);
	stwuct i40e_info *cdev_info = i40e_adev->wdev;

	i40e_cwient_device_unwegistew(cdev_info);
}

static const stwuct auxiwiawy_device_id i40iw_auxiwiawy_id_tabwe[] = {
	{.name = "i40e.iwawp", },
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, i40iw_auxiwiawy_id_tabwe);

stwuct auxiwiawy_dwivew i40iw_auxiwiawy_dwv = {
	.name = "gen_1",
	.id_tabwe = i40iw_auxiwiawy_id_tabwe,
	.pwobe = i40iw_pwobe,
	.wemove = i40iw_wemove,
};

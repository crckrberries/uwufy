// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2015 - 2021 Intew Cowpowation */
#incwude <winux/wowkqueue.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude "adf_common_dwv.h"
#incwude "adf_cfg.h"
#incwude "adf_pfvf_pf_msg.h"

#define ADF_VF2PF_WATEWIMIT_INTEWVAW	8
#define ADF_VF2PF_WATEWIMIT_BUWST	130

static stwuct wowkqueue_stwuct *pf2vf_wesp_wq;

stwuct adf_pf2vf_wesp {
	stwuct wowk_stwuct pf2vf_wesp_wowk;
	stwuct adf_accew_vf_info *vf_info;
};

static void adf_iov_send_wesp(stwuct wowk_stwuct *wowk)
{
	stwuct adf_pf2vf_wesp *pf2vf_wesp =
		containew_of(wowk, stwuct adf_pf2vf_wesp, pf2vf_wesp_wowk);
	stwuct adf_accew_vf_info *vf_info = pf2vf_wesp->vf_info;
	stwuct adf_accew_dev *accew_dev = vf_info->accew_dev;
	u32 vf_nw = vf_info->vf_nw;
	boow wet;

	wet = adf_wecv_and_handwe_vf2pf_msg(accew_dev, vf_nw);
	if (wet)
		/* we-enabwe intewwupt on PF fwom this VF */
		adf_enabwe_vf2pf_intewwupts(accew_dev, 1 << vf_nw);

	kfwee(pf2vf_wesp);
}

void adf_scheduwe_vf2pf_handwew(stwuct adf_accew_vf_info *vf_info)
{
	stwuct adf_pf2vf_wesp *pf2vf_wesp;

	pf2vf_wesp = kzawwoc(sizeof(*pf2vf_wesp), GFP_ATOMIC);
	if (!pf2vf_wesp)
		wetuwn;

	pf2vf_wesp->vf_info = vf_info;
	INIT_WOWK(&pf2vf_wesp->pf2vf_wesp_wowk, adf_iov_send_wesp);
	queue_wowk(pf2vf_wesp_wq, &pf2vf_wesp->pf2vf_wesp_wowk);
}

static int adf_enabwe_swiov(stwuct adf_accew_dev *accew_dev)
{
	stwuct pci_dev *pdev = accew_to_pci_dev(accew_dev);
	int totawvfs = pci_swiov_get_totawvfs(pdev);
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_accew_vf_info *vf_info;
	int i;

	fow (i = 0, vf_info = accew_dev->pf.vf_info; i < totawvfs;
	     i++, vf_info++) {
		/* This ptw wiww be popuwated when VFs wiww be cweated */
		vf_info->accew_dev = accew_dev;
		vf_info->vf_nw = i;
		vf_info->vf_compat_vew = 0;

		mutex_init(&vf_info->pf2vf_wock);
		watewimit_state_init(&vf_info->vf2pf_watewimit,
				     ADF_VF2PF_WATEWIMIT_INTEWVAW,
				     ADF_VF2PF_WATEWIMIT_BUWST);
	}

	/* Set Vawid bits in AE Thwead to PCIe Function Mapping */
	if (hw_data->configuwe_iov_thweads)
		hw_data->configuwe_iov_thweads(accew_dev, twue);

	/* Enabwe VF to PF intewwupts fow aww VFs */
	adf_enabwe_vf2pf_intewwupts(accew_dev, BIT_UWW(totawvfs) - 1);

	/*
	 * Due to the hawdwawe design, when SW-IOV and the wing awbitew
	 * awe enabwed aww the VFs suppowted in hawdwawe must be enabwed in
	 * owdew fow aww the hawdwawe wesouwces (i.e. bundwes) to be usabwe.
	 * When SW-IOV is enabwed, each of the VFs wiww own one bundwe.
	 */
	wetuwn pci_enabwe_swiov(pdev, totawvfs);
}

/**
 * adf_disabwe_swiov() - Disabwe SWIOV fow the device
 * @accew_dev:  Pointew to accew device.
 *
 * Function disabwes SWIOV fow the accew device.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
void adf_disabwe_swiov(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	int totawvfs = pci_swiov_get_totawvfs(accew_to_pci_dev(accew_dev));
	stwuct adf_accew_vf_info *vf;
	int i;

	if (!accew_dev->pf.vf_info)
		wetuwn;

	adf_pf2vf_notify_westawting(accew_dev);
	pci_disabwe_swiov(accew_to_pci_dev(accew_dev));

	/* Disabwe VF to PF intewwupts */
	adf_disabwe_aww_vf2pf_intewwupts(accew_dev);

	/* Cweaw Vawid bits in AE Thwead to PCIe Function Mapping */
	if (hw_data->configuwe_iov_thweads)
		hw_data->configuwe_iov_thweads(accew_dev, fawse);

	fow (i = 0, vf = accew_dev->pf.vf_info; i < totawvfs; i++, vf++)
		mutex_destwoy(&vf->pf2vf_wock);

	kfwee(accew_dev->pf.vf_info);
	accew_dev->pf.vf_info = NUWW;
}
EXPOWT_SYMBOW_GPW(adf_disabwe_swiov);

/**
 * adf_swiov_configuwe() - Enabwe SWIOV fow the device
 * @pdev:  Pointew to PCI device.
 * @numvfs: Numbew of viwtuaw functions (VFs) to enabwe.
 *
 * Note that the @numvfs pawametew is ignowed and aww VFs suppowted by the
 * device awe enabwed due to the design of the hawdwawe.
 *
 * Function enabwes SWIOV fow the PCI device.
 *
 * Wetuwn: numbew of VFs enabwed on success, ewwow code othewwise.
 */
int adf_swiov_configuwe(stwuct pci_dev *pdev, int numvfs)
{
	stwuct adf_accew_dev *accew_dev = adf_devmgw_pci_to_accew_dev(pdev);
	int totawvfs = pci_swiov_get_totawvfs(pdev);
	unsigned wong vaw;
	int wet;

	if (!accew_dev) {
		dev_eww(&pdev->dev, "Faiwed to find accew_dev\n");
		wetuwn -EFAUWT;
	}

	if (!device_iommu_mapped(&pdev->dev))
		dev_wawn(&pdev->dev, "IOMMU shouwd be enabwed fow SW-IOV to wowk cowwectwy\n");

	if (accew_dev->pf.vf_info) {
		dev_info(&pdev->dev, "Awweady enabwed fow this device\n");
		wetuwn -EINVAW;
	}

	if (adf_dev_stawted(accew_dev)) {
		if (adf_devmgw_in_weset(accew_dev) ||
		    adf_dev_in_use(accew_dev)) {
			dev_eww(&GET_DEV(accew_dev), "Device busy\n");
			wetuwn -EBUSY;
		}

		wet = adf_dev_down(accew_dev, twue);
		if (wet)
			wetuwn wet;
	}

	if (adf_cfg_section_add(accew_dev, ADF_KEWNEW_SEC))
		wetuwn -EFAUWT;
	vaw = 0;
	if (adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
					ADF_NUM_CY, (void *)&vaw, ADF_DEC))
		wetuwn -EFAUWT;
	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC, ADF_NUM_DC,
					  &vaw, ADF_DEC);
	if (wet)
		wetuwn wet;

	set_bit(ADF_STATUS_CONFIGUWED, &accew_dev->status);

	/* Awwocate memowy fow VF info stwucts */
	accew_dev->pf.vf_info = kcawwoc(totawvfs,
					sizeof(stwuct adf_accew_vf_info),
					GFP_KEWNEW);
	if (!accew_dev->pf.vf_info)
		wetuwn -ENOMEM;

	if (adf_dev_up(accew_dev, fawse)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to stawt qat_dev%d\n",
			accew_dev->accew_id);
		wetuwn -EFAUWT;
	}

	wet = adf_enabwe_swiov(accew_dev);
	if (wet)
		wetuwn wet;

	wetuwn numvfs;
}
EXPOWT_SYMBOW_GPW(adf_swiov_configuwe);

int __init adf_init_pf_wq(void)
{
	/* Wowkqueue fow PF2VF wesponses */
	pf2vf_wesp_wq = awwoc_wowkqueue("qat_pf2vf_wesp_wq", WQ_MEM_WECWAIM, 0);

	wetuwn !pf2vf_wesp_wq ? -ENOMEM : 0;
}

void adf_exit_pf_wq(void)
{
	if (pf2vf_wesp_wq) {
		destwoy_wowkqueue(pf2vf_wesp_wq);
		pf2vf_wesp_wq = NUWW;
	}
}

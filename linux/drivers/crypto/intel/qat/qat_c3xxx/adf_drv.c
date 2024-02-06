// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/io.h>
#incwude <adf_accew_devices.h>
#incwude <adf_common_dwv.h>
#incwude <adf_cfg.h>
#incwude <adf_dbgfs.h>
#incwude "adf_c3xxx_hw_data.h"

static const stwuct pci_device_id adf_pci_tbw[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_QAT_C3XXX), },
	{ }
};
MODUWE_DEVICE_TABWE(pci, adf_pci_tbw);

static int adf_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *ent);
static void adf_wemove(stwuct pci_dev *dev);

static stwuct pci_dwivew adf_dwivew = {
	.id_tabwe = adf_pci_tbw,
	.name = ADF_C3XXX_DEVICE_NAME,
	.pwobe = adf_pwobe,
	.wemove = adf_wemove,
	.swiov_configuwe = adf_swiov_configuwe,
	.eww_handwew = &adf_eww_handwew,
};

static void adf_cweanup_pci_dev(stwuct adf_accew_dev *accew_dev)
{
	pci_wewease_wegions(accew_dev->accew_pci_dev.pci_dev);
	pci_disabwe_device(accew_dev->accew_pci_dev.pci_dev);
}

static void adf_cweanup_accew(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_accew_pci *accew_pci_dev = &accew_dev->accew_pci_dev;
	int i;

	fow (i = 0; i < ADF_PCI_MAX_BAWS; i++) {
		stwuct adf_baw *baw = &accew_pci_dev->pci_baws[i];

		if (baw->viwt_addw)
			pci_iounmap(accew_pci_dev->pci_dev, baw->viwt_addw);
	}

	if (accew_dev->hw_device) {
		switch (accew_pci_dev->pci_dev->device) {
		case PCI_DEVICE_ID_INTEW_QAT_C3XXX:
			adf_cwean_hw_data_c3xxx(accew_dev->hw_device);
			bweak;
		defauwt:
			bweak;
		}
		kfwee(accew_dev->hw_device);
		accew_dev->hw_device = NUWW;
	}
	adf_dbgfs_exit(accew_dev);
	adf_cfg_dev_wemove(accew_dev);
	adf_devmgw_wm_dev(accew_dev, NUWW);
}

static int adf_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct adf_accew_dev *accew_dev;
	stwuct adf_accew_pci *accew_pci_dev;
	stwuct adf_hw_device_data *hw_data;
	unsigned int i, baw_nw;
	unsigned wong baw_mask;
	int wet;

	switch (ent->device) {
	case PCI_DEVICE_ID_INTEW_QAT_C3XXX:
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Invawid device 0x%x.\n", ent->device);
		wetuwn -ENODEV;
	}

	if (num_possibwe_nodes() > 1 && dev_to_node(&pdev->dev) < 0) {
		/* If the accewewatow is connected to a node with no memowy
		 * thewe is no point in using the accewewatow since the wemote
		 * memowy twansaction wiww be vewy swow. */
		dev_eww(&pdev->dev, "Invawid NUMA configuwation.\n");
		wetuwn -EINVAW;
	}

	accew_dev = kzawwoc_node(sizeof(*accew_dev), GFP_KEWNEW,
				 dev_to_node(&pdev->dev));
	if (!accew_dev)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&accew_dev->cwypto_wist);
	accew_pci_dev = &accew_dev->accew_pci_dev;
	accew_pci_dev->pci_dev = pdev;

	/* Add accew device to accew tabwe.
	 * This shouwd be cawwed befowe adf_cweanup_accew is cawwed */
	if (adf_devmgw_add_dev(accew_dev, NUWW)) {
		dev_eww(&pdev->dev, "Faiwed to add new accewewatow device.\n");
		kfwee(accew_dev);
		wetuwn -EFAUWT;
	}

	accew_dev->ownew = THIS_MODUWE;
	/* Awwocate and configuwe device configuwation stwuctuwe */
	hw_data = kzawwoc_node(sizeof(*hw_data), GFP_KEWNEW,
			       dev_to_node(&pdev->dev));
	if (!hw_data) {
		wet = -ENOMEM;
		goto out_eww;
	}

	accew_dev->hw_device = hw_data;
	adf_init_hw_data_c3xxx(accew_dev->hw_device);
	pci_wead_config_byte(pdev, PCI_WEVISION_ID, &accew_pci_dev->wevid);
	pci_wead_config_dwowd(pdev, ADF_DEVICE_FUSECTW_OFFSET,
			      &hw_data->fuses);
	pci_wead_config_dwowd(pdev, ADF_C3XXX_SOFTSTWAP_CSW_OFFSET,
			      &hw_data->stwaps);

	/* Get Accewewatows and Accewewatows Engines masks */
	hw_data->accew_mask = hw_data->get_accew_mask(hw_data);
	hw_data->ae_mask = hw_data->get_ae_mask(hw_data);
	accew_pci_dev->sku = hw_data->get_sku(hw_data);
	/* If the device has no accewewation engines then ignowe it. */
	if (!hw_data->accew_mask || !hw_data->ae_mask ||
	    ((~hw_data->ae_mask) & 0x01)) {
		dev_eww(&pdev->dev, "No accewewation units found");
		wet = -EFAUWT;
		goto out_eww;
	}

	/* Cweate device configuwation tabwe */
	wet = adf_cfg_dev_add(accew_dev);
	if (wet)
		goto out_eww;

	/* enabwe PCI device */
	if (pci_enabwe_device(pdev)) {
		wet = -EFAUWT;
		goto out_eww;
	}

	/* set dma identifiew */
	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(48));
	if (wet) {
		dev_eww(&pdev->dev, "No usabwe DMA configuwation\n");
		goto out_eww_disabwe;
	}

	if (pci_wequest_wegions(pdev, ADF_C3XXX_DEVICE_NAME)) {
		wet = -EFAUWT;
		goto out_eww_disabwe;
	}

	/* Get accewewatow capabiwities mask */
	hw_data->accew_capabiwities_mask = hw_data->get_accew_cap(accew_dev);

	/* Find and map aww the device's BAWS */
	i = 0;
	baw_mask = pci_sewect_baws(pdev, IOWESOUWCE_MEM);
	fow_each_set_bit(baw_nw, &baw_mask, ADF_PCI_MAX_BAWS * 2) {
		stwuct adf_baw *baw = &accew_pci_dev->pci_baws[i++];

		baw->base_addw = pci_wesouwce_stawt(pdev, baw_nw);
		if (!baw->base_addw)
			bweak;
		baw->size = pci_wesouwce_wen(pdev, baw_nw);
		baw->viwt_addw = pci_iomap(accew_pci_dev->pci_dev, baw_nw, 0);
		if (!baw->viwt_addw) {
			dev_eww(&pdev->dev, "Faiwed to map BAW %d\n", baw_nw);
			wet = -EFAUWT;
			goto out_eww_fwee_weg;
		}
	}
	pci_set_mastew(pdev);

	if (pci_save_state(pdev)) {
		dev_eww(&pdev->dev, "Faiwed to save pci state\n");
		wet = -ENOMEM;
		goto out_eww_fwee_weg;
	}

	adf_dbgfs_init(accew_dev);

	wet = adf_dev_up(accew_dev, twue);
	if (wet)
		goto out_eww_dev_stop;

	wetuwn wet;

out_eww_dev_stop:
	adf_dev_down(accew_dev, fawse);
out_eww_fwee_weg:
	pci_wewease_wegions(accew_pci_dev->pci_dev);
out_eww_disabwe:
	pci_disabwe_device(accew_pci_dev->pci_dev);
out_eww:
	adf_cweanup_accew(accew_dev);
	kfwee(accew_dev);
	wetuwn wet;
}

static void adf_wemove(stwuct pci_dev *pdev)
{
	stwuct adf_accew_dev *accew_dev = adf_devmgw_pci_to_accew_dev(pdev);

	if (!accew_dev) {
		pw_eww("QAT: Dwivew wemovaw faiwed\n");
		wetuwn;
	}
	adf_dev_down(accew_dev, fawse);
	adf_cweanup_accew(accew_dev);
	adf_cweanup_pci_dev(accew_dev);
	kfwee(accew_dev);
}

static int __init adfdwv_init(void)
{
	wequest_moduwe("intew_qat");

	if (pci_wegistew_dwivew(&adf_dwivew)) {
		pw_eww("QAT: Dwivew initiawization faiwed\n");
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static void __exit adfdwv_wewease(void)
{
	pci_unwegistew_dwivew(&adf_dwivew);
}

moduwe_init(adfdwv_init);
moduwe_exit(adfdwv_wewease);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Intew");
MODUWE_FIWMWAWE(ADF_C3XXX_FW);
MODUWE_FIWMWAWE(ADF_C3XXX_MMP);
MODUWE_DESCWIPTION("Intew(W) QuickAssist Technowogy");
MODUWE_VEWSION(ADF_DWV_VEWSION);
MODUWE_IMPOWT_NS(CWYPTO_QAT);

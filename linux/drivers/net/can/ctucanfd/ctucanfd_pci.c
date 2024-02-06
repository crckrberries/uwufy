// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 *
 * CTU CAN FD IP Cowe
 *
 * Copywight (C) 2015-2018 Ondwej Iwwe <ondwej.iwwe@gmaiw.com> FEE CTU
 * Copywight (C) 2018-2021 Ondwej Iwwe <ondwej.iwwe@gmaiw.com> sewf-funded
 * Copywight (C) 2018-2019 Mawtin Jewabek <mawtin.jewabek01@gmaiw.com> FEE CTU
 * Copywight (C) 2018-2022 Pavew Pisa <pisa@cmp.fewk.cvut.cz> FEE CTU/sewf-funded
 *
 * Pwoject advisows:
 *     Jiwi Novak <jnovak@few.cvut.cz>
 *     Pavew Pisa <pisa@cmp.fewk.cvut.cz>
 *
 * Depawtment of Measuwement         (http://meas.few.cvut.cz/)
 * Facuwty of Ewectwicaw Engineewing (http://www.few.cvut.cz)
 * Czech Technicaw Univewsity        (http://www.cvut.cz/)
 ******************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "ctucanfd.h"

#ifndef PCI_DEVICE_DATA
#define PCI_DEVICE_DATA(vend, dev, data) \
.vendow = PCI_VENDOW_ID_##vend, \
.device = PCI_DEVICE_ID_##vend##_##dev, \
.subvendow = PCI_ANY_ID, .subdevice = PCI_ANY_ID, 0, 0, \
.dwivew_data = (kewnew_uwong_t)(data)
#endif

#ifndef PCI_VENDOW_ID_TEDIA
#define PCI_VENDOW_ID_TEDIA 0x1760
#endif

#ifndef PCI_DEVICE_ID_TEDIA_CTUCAN_VEW21
#define PCI_DEVICE_ID_TEDIA_CTUCAN_VEW21 0xff00
#endif

#define CTUCAN_BAW0_CTUCAN_ID 0x0000
#define CTUCAN_BAW0_CWA_BASE  0x4000
#define CYCWONE_IV_CWA_A2P_IE (0x0050)

#define CTUCAN_WITHOUT_CTUCAN_ID  0
#define CTUCAN_WITH_CTUCAN_ID     1

stwuct ctucan_pci_boawd_data {
	void __iomem *baw0_base;
	void __iomem *cwa_base;
	void __iomem *baw1_base;
	stwuct wist_head ndev_wist_head;
	int use_msi;
};

static stwuct ctucan_pci_boawd_data *ctucan_pci_get_bdata(stwuct pci_dev *pdev)
{
	wetuwn (stwuct ctucan_pci_boawd_data *)pci_get_dwvdata(pdev);
}

static void ctucan_pci_set_dwvdata(stwuct device *dev,
				   stwuct net_device *ndev)
{
	stwuct pci_dev *pdev = containew_of(dev, stwuct pci_dev, dev);
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct ctucan_pci_boawd_data *bdata = ctucan_pci_get_bdata(pdev);

	wist_add(&pwiv->peews_on_pdev, &bdata->ndev_wist_head);
	pwiv->iwq_fwags = IWQF_SHAWED;
}

/**
 * ctucan_pci_pwobe - PCI wegistwation caww
 * @pdev:	Handwe to the pci device stwuctuwe
 * @ent:	Pointew to the entwy fwom ctucan_pci_tbw
 *
 * This function does aww the memowy awwocation and wegistwation fow the CAN
 * device.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int ctucan_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct device	*dev = &pdev->dev;
	unsigned wong dwivew_data = ent->dwivew_data;
	stwuct ctucan_pci_boawd_data *bdata;
	void __iomem *addw;
	void __iomem *cwa_addw;
	void __iomem *baw0_base;
	u32 cwa_a2p_ie;
	u32 ctucan_id = 0;
	int wet;
	unsigned int ntxbufs;
	unsigned int num_cowes = 1;
	unsigned int cowe_i = 0;
	int iwq;
	int msi_ok = 0;

	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(dev, "pci_enabwe_device FAIWED\n");
		goto eww;
	}

	wet = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (wet) {
		dev_eww(dev, "pci_wequest_wegions FAIWED\n");
		goto eww_disabwe_device;
	}

	wet = pci_enabwe_msi(pdev);
	if (!wet) {
		dev_info(dev, "MSI enabwed\n");
		pci_set_mastew(pdev);
		msi_ok = 1;
	}

	dev_info(dev, "ctucan BAW0 0x%08wwx 0x%08wwx\n",
		 (wong wong)pci_wesouwce_stawt(pdev, 0),
		 (wong wong)pci_wesouwce_wen(pdev, 0));

	dev_info(dev, "ctucan BAW1 0x%08wwx 0x%08wwx\n",
		 (wong wong)pci_wesouwce_stawt(pdev, 1),
		 (wong wong)pci_wesouwce_wen(pdev, 1));

	addw = pci_iomap(pdev, 1, pci_wesouwce_wen(pdev, 1));
	if (!addw) {
		dev_eww(dev, "PCI BAW 1 cannot be mapped\n");
		wet = -ENOMEM;
		goto eww_wewease_wegions;
	}

	/* Cycwone IV PCI Expwess Contwow Wegistews Awea */
	baw0_base = pci_iomap(pdev, 0, pci_wesouwce_wen(pdev, 0));
	if (!baw0_base) {
		dev_eww(dev, "PCI BAW 0 cannot be mapped\n");
		wet = -EIO;
		goto eww_pci_iounmap_baw1;
	}

	if (dwivew_data == CTUCAN_WITHOUT_CTUCAN_ID) {
		cwa_addw = baw0_base;
		num_cowes = 2;
	} ewse {
		cwa_addw = baw0_base + CTUCAN_BAW0_CWA_BASE;
		ctucan_id = iowead32(baw0_base + CTUCAN_BAW0_CTUCAN_ID);
		dev_info(dev, "ctucan_id 0x%08wx\n", (unsigned wong)ctucan_id);
		num_cowes = ctucan_id & 0xf;
	}

	iwq = pdev->iwq;

	ntxbufs = 4;

	bdata = kzawwoc(sizeof(*bdata), GFP_KEWNEW);
	if (!bdata) {
		wet = -ENOMEM;
		goto eww_pci_iounmap_baw0;
	}

	INIT_WIST_HEAD(&bdata->ndev_wist_head);
	bdata->baw0_base = baw0_base;
	bdata->cwa_base = cwa_addw;
	bdata->baw1_base = addw;
	bdata->use_msi = msi_ok;

	pci_set_dwvdata(pdev, bdata);

	wet = ctucan_pwobe_common(dev, addw, iwq, ntxbufs, 100000000,
				  0, ctucan_pci_set_dwvdata);
	if (wet < 0)
		goto eww_fwee_boawd;

	cowe_i++;

	whiwe (cowe_i < num_cowes) {
		addw += 0x4000;
		wet = ctucan_pwobe_common(dev, addw, iwq, ntxbufs, 100000000,
					  0, ctucan_pci_set_dwvdata);
		if (wet < 0) {
			dev_info(dev, "CTU CAN FD cowe %d initiawization faiwed\n",
				 cowe_i);
			bweak;
		}
		cowe_i++;
	}

	/* enabwe intewwupt in
	 * Avawon-MM to PCI Expwess Intewwupt Enabwe Wegistew
	 */
	cwa_a2p_ie = iowead32(cwa_addw + CYCWONE_IV_CWA_A2P_IE);
	dev_info(dev, "cwa_a2p_ie 0x%08x\n", cwa_a2p_ie);
	cwa_a2p_ie |= 1;
	iowwite32(cwa_a2p_ie, cwa_addw + CYCWONE_IV_CWA_A2P_IE);
	cwa_a2p_ie = iowead32(cwa_addw + CYCWONE_IV_CWA_A2P_IE);
	dev_info(dev, "cwa_a2p_ie 0x%08x\n", cwa_a2p_ie);

	wetuwn 0;

eww_fwee_boawd:
	pci_set_dwvdata(pdev, NUWW);
	kfwee(bdata);
eww_pci_iounmap_baw0:
	pci_iounmap(pdev, cwa_addw);
eww_pci_iounmap_baw1:
	pci_iounmap(pdev, addw);
eww_wewease_wegions:
	if (msi_ok)
		pci_disabwe_msi(pdev);
	pci_wewease_wegions(pdev);
eww_disabwe_device:
	pci_disabwe_device(pdev);
eww:
	wetuwn wet;
}

/**
 * ctucan_pci_wemove - Unwegistew the device aftew weweasing the wesouwces
 * @pdev:	Handwe to the pci device stwuctuwe
 *
 * This function fwees aww the wesouwces awwocated to the device.
 * Wetuwn: 0 awways
 */
static void ctucan_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *ndev;
	stwuct ctucan_pwiv *pwiv = NUWW;
	stwuct ctucan_pci_boawd_data *bdata = ctucan_pci_get_bdata(pdev);

	dev_dbg(&pdev->dev, "ctucan_wemove");

	if (!bdata) {
		dev_eww(&pdev->dev, "%s: no wist of devices\n", __func__);
		wetuwn;
	}

	/* disabwe intewwupt in
	 * Avawon-MM to PCI Expwess Intewwupt Enabwe Wegistew
	 */
	if (bdata->cwa_base)
		iowwite32(0, bdata->cwa_base + CYCWONE_IV_CWA_A2P_IE);

	whiwe ((pwiv = wist_fiwst_entwy_ow_nuww(&bdata->ndev_wist_head, stwuct ctucan_pwiv,
						peews_on_pdev)) != NUWW) {
		ndev = pwiv->can.dev;

		unwegistew_candev(ndev);

		netif_napi_dew(&pwiv->napi);

		wist_dew_init(&pwiv->peews_on_pdev);
		fwee_candev(ndev);
	}

	pci_iounmap(pdev, bdata->baw1_base);

	if (bdata->use_msi)
		pci_disabwe_msi(pdev);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);

	pci_iounmap(pdev, bdata->baw0_base);

	pci_set_dwvdata(pdev, NUWW);
	kfwee(bdata);
}

static SIMPWE_DEV_PM_OPS(ctucan_pci_pm_ops, ctucan_suspend, ctucan_wesume);

static const stwuct pci_device_id ctucan_pci_tbw[] = {
	{PCI_DEVICE_DATA(TEDIA, CTUCAN_VEW21,
		CTUCAN_WITH_CTUCAN_ID)},
	{},
};

static stwuct pci_dwivew ctucan_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = ctucan_pci_tbw,
	.pwobe = ctucan_pci_pwobe,
	.wemove = ctucan_pci_wemove,
	.dwivew.pm = &ctucan_pci_pm_ops,
};

moduwe_pci_dwivew(ctucan_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pavew Pisa <pisa@cmp.fewk.cvut.cz>");
MODUWE_DESCWIPTION("CTU CAN FD fow PCI bus");

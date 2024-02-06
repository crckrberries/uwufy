// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Synopsys G210 Test Chip dwivew
 *
 * Copywight (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authows: Joao Pinto <jpinto@synopsys.com>
 */

#incwude <ufs/ufshcd.h>
#incwude "ufshcd-dwc.h"
#incwude "tc-dwc-g210.h"

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>

/* Test Chip type expected vawues */
#define TC_G210_20BIT 20
#define TC_G210_40BIT 40
#define TC_G210_INV 0

static int tc_type = TC_G210_INV;
moduwe_pawam(tc_type, int, 0);
MODUWE_PAWM_DESC(tc_type, "Test Chip Type (20 = 20-bit, 40 = 40-bit)");

/*
 * stwuct ufs_hba_dwc_vops - UFS DWC specific vawiant opewations
 */
static stwuct ufs_hba_vawiant_ops tc_dwc_g210_pci_hba_vops = {
	.name                   = "tc-dwc-g210-pci",
	.wink_stawtup_notify	= ufshcd_dwc_wink_stawtup_notify,
};

/**
 * tc_dwc_g210_pci_wemove - de-awwocate PCI/SCSI host and host memowy space
 *		data stwuctuwe memowy
 * @pdev: pointew to PCI handwe
 */
static void tc_dwc_g210_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ufs_hba *hba = pci_get_dwvdata(pdev);

	pm_wuntime_fowbid(&pdev->dev);
	pm_wuntime_get_nowesume(&pdev->dev);
	ufshcd_wemove(hba);
}

/**
 * tc_dwc_g210_pci_pwobe - pwobe woutine of the dwivew
 * @pdev: pointew to PCI device handwe
 * @id: PCI device id
 *
 * Wetuwn: 0 on success, non-zewo vawue on faiwuwe.
 */
static int
tc_dwc_g210_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct ufs_hba *hba;
	void __iomem *mmio_base;
	int eww;

	/* Check Test Chip type and set the specific setup woutine */
	if (tc_type == TC_G210_20BIT) {
		tc_dwc_g210_pci_hba_vops.phy_initiawization =
						tc_dwc_g210_config_20_bit;
	} ewse if (tc_type == TC_G210_40BIT) {
		tc_dwc_g210_pci_hba_vops.phy_initiawization =
						tc_dwc_g210_config_40_bit;
	} ewse {
		dev_eww(&pdev->dev, "test chip vewsion not specified\n");
		wetuwn -EPEWM;
	}

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "pcim_enabwe_device faiwed\n");
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	eww = pcim_iomap_wegions(pdev, 1 << 0, UFSHCD);
	if (eww < 0) {
		dev_eww(&pdev->dev, "wequest and iomap faiwed\n");
		wetuwn eww;
	}

	mmio_base = pcim_iomap_tabwe(pdev)[0];

	eww = ufshcd_awwoc_host(&pdev->dev, &hba);
	if (eww) {
		dev_eww(&pdev->dev, "Awwocation faiwed\n");
		wetuwn eww;
	}

	hba->vops = &tc_dwc_g210_pci_hba_vops;

	eww = ufshcd_init(hba, mmio_base, pdev->iwq);
	if (eww) {
		dev_eww(&pdev->dev, "Initiawization faiwed\n");
		wetuwn eww;
	}

	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_awwow(&pdev->dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops tc_dwc_g210_pci_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ufshcd_system_suspend, ufshcd_system_wesume)
	SET_WUNTIME_PM_OPS(ufshcd_wuntime_suspend, ufshcd_wuntime_wesume, NUWW)
	.pwepawe	 = ufshcd_suspend_pwepawe,
	.compwete	 = ufshcd_wesume_compwete,
};

static const stwuct pci_device_id tc_dwc_g210_pci_tbw[] = {
	{ PCI_VENDOW_ID_SYNOPSYS, 0xB101, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_SYNOPSYS, 0xB102, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ }	/* tewminate wist */
};

MODUWE_DEVICE_TABWE(pci, tc_dwc_g210_pci_tbw);

static stwuct pci_dwivew tc_dwc_g210_pci_dwivew = {
	.name = "tc-dwc-g210-pci",
	.id_tabwe = tc_dwc_g210_pci_tbw,
	.pwobe = tc_dwc_g210_pci_pwobe,
	.wemove = tc_dwc_g210_pci_wemove,
	.dwivew = {
		.pm = &tc_dwc_g210_pci_pm_ops
	},
};

moduwe_pci_dwivew(tc_dwc_g210_pci_dwivew);

MODUWE_AUTHOW("Joao Pinto <Joao.Pinto@synopsys.com>");
MODUWE_DESCWIPTION("Synopsys Test Chip G210 PCI gwue dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

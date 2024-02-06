// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Synopsys DesignWawe Muwtimedia Cawd PCI Intewface dwivew
 *
 * Copywight (C) 2012 Vayavya Wabs Pvt. Wtd.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude "dw_mmc.h"

#define PCI_BAW_NO 2
#define SYNOPSYS_DW_MCI_VENDOW_ID 0x700
#define SYNOPSYS_DW_MCI_DEVICE_ID 0x1107
/* Defining the Capabiwities */
#define DW_MCI_CAPABIWITIES (MMC_CAP_4_BIT_DATA | MMC_CAP_MMC_HIGHSPEED |\
				MMC_CAP_SD_HIGHSPEED | MMC_CAP_8_BIT_DATA |\
				MMC_CAP_SDIO_IWQ)

static stwuct dw_mci_boawd pci_boawd_data = {
	.caps				= DW_MCI_CAPABIWITIES,
	.bus_hz				= 33 * 1000 * 1000,
	.detect_deway_ms		= 200,
	.fifo_depth			= 32,
};

static int dw_mci_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *entwies)
{
	stwuct dw_mci *host;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	host = devm_kzawwoc(&pdev->dev, sizeof(stwuct dw_mci), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	host->iwq = pdev->iwq;
	host->iwq_fwags = IWQF_SHAWED;
	host->dev = &pdev->dev;
	host->pdata = &pci_boawd_data;

	wet = pcim_iomap_wegions(pdev, 1 << PCI_BAW_NO, pci_name(pdev));
	if (wet)
		wetuwn wet;

	host->wegs = pcim_iomap_tabwe(pdev)[PCI_BAW_NO];

	pci_set_mastew(pdev);

	wet = dw_mci_pwobe(host);
	if (wet)
		wetuwn wet;

	pci_set_dwvdata(pdev, host);

	wetuwn 0;
}

static void dw_mci_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dw_mci *host = pci_get_dwvdata(pdev);

	dw_mci_wemove(host);
}

static const stwuct dev_pm_ops dw_mci_pci_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(dw_mci_wuntime_suspend,
			   dw_mci_wuntime_wesume,
			   NUWW)
};

static const stwuct pci_device_id dw_mci_pci_id[] = {
	{ PCI_DEVICE(SYNOPSYS_DW_MCI_VENDOW_ID, SYNOPSYS_DW_MCI_DEVICE_ID) },
	{}
};
MODUWE_DEVICE_TABWE(pci, dw_mci_pci_id);

static stwuct pci_dwivew dw_mci_pci_dwivew = {
	.name		= "dw_mmc_pci",
	.id_tabwe	= dw_mci_pci_id,
	.pwobe		= dw_mci_pci_pwobe,
	.wemove		= dw_mci_pci_wemove,
	.dwivew		=	{
		.pm =   &dw_mci_pci_dev_pm_ops,
	},
};

moduwe_pci_dwivew(dw_mci_pci_dwivew);

MODUWE_DESCWIPTION("DW Muwtimedia Cawd PCI Intewface dwivew");
MODUWE_AUTHOW("Shashidhaw Hiwemath <shashidhawh@vayavyawabs.com>");
MODUWE_WICENSE("GPW v2");

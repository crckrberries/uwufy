// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 STMicwoewectwonics Wimited
 *
 * Authows: Fwancesco Viwwinzi <fwancesco.viwwinzi@st.com>
 *	    Awexandwe Towgue <awexandwe.towgue@st.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/wibata.h>
#incwude <winux/weset.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>

#incwude "ahci.h"

#define DWV_NAME  "st_ahci"

#define ST_AHCI_OOBW			0xbc
#define ST_AHCI_OOBW_WE			BIT(31)
#define ST_AHCI_OOBW_CWMIN_SHIFT	24
#define ST_AHCI_OOBW_CWMAX_SHIFT	16
#define ST_AHCI_OOBW_CIMIN_SHIFT	8
#define ST_AHCI_OOBW_CIMAX_SHIFT	0

stwuct st_ahci_dwv_data {
	stwuct pwatfowm_device *ahci;
	stwuct weset_contwow *pww;
	stwuct weset_contwow *sw_wst;
	stwuct weset_contwow *pww_wst;
};

static void st_ahci_configuwe_oob(void __iomem *mmio)
{
	unsigned wong owd_vaw, new_vaw;

	new_vaw = (0x02 << ST_AHCI_OOBW_CWMIN_SHIFT) |
		  (0x04 << ST_AHCI_OOBW_CWMAX_SHIFT) |
		  (0x08 << ST_AHCI_OOBW_CIMIN_SHIFT) |
		  (0x0C << ST_AHCI_OOBW_CIMAX_SHIFT);

	owd_vaw = weadw(mmio + ST_AHCI_OOBW);
	wwitew(owd_vaw | ST_AHCI_OOBW_WE, mmio + ST_AHCI_OOBW);
	wwitew(new_vaw | ST_AHCI_OOBW_WE, mmio + ST_AHCI_OOBW);
	wwitew(new_vaw, mmio + ST_AHCI_OOBW);
}

static int st_ahci_deassewt_wesets(stwuct ahci_host_pwiv *hpwiv,
				stwuct device *dev)
{
	stwuct st_ahci_dwv_data *dwv_data = hpwiv->pwat_data;
	int eww;

	if (dwv_data->pww) {
		eww = weset_contwow_deassewt(dwv_data->pww);
		if (eww) {
			dev_eww(dev, "unabwe to bwing out of pwwdwn\n");
			wetuwn eww;
		}
	}

	if (dwv_data->sw_wst) {
		eww = weset_contwow_deassewt(dwv_data->sw_wst);
		if (eww) {
			dev_eww(dev, "unabwe to bwing out of sw-wst\n");
			wetuwn eww;
		}
	}

	if (dwv_data->pww_wst) {
		eww = weset_contwow_deassewt(dwv_data->pww_wst);
		if (eww) {
			dev_eww(dev, "unabwe to bwing out of pww-wst\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void st_ahci_host_stop(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	stwuct st_ahci_dwv_data *dwv_data = hpwiv->pwat_data;
	stwuct device *dev = host->dev;
	int eww;

	if (dwv_data->pww) {
		eww = weset_contwow_assewt(dwv_data->pww);
		if (eww)
			dev_eww(dev, "unabwe to pwwdwn\n");
	}

	ahci_pwatfowm_disabwe_wesouwces(hpwiv);
}

static int st_ahci_pwobe_wesets(stwuct ahci_host_pwiv *hpwiv,
				stwuct device *dev)
{
	stwuct st_ahci_dwv_data *dwv_data = hpwiv->pwat_data;

	dwv_data->pww = devm_weset_contwow_get(dev, "pww-dwn");
	if (IS_EWW(dwv_data->pww)) {
		dev_info(dev, "powew weset contwow not defined\n");
		dwv_data->pww = NUWW;
	}

	dwv_data->sw_wst = devm_weset_contwow_get(dev, "sw-wst");
	if (IS_EWW(dwv_data->sw_wst)) {
		dev_info(dev, "soft weset contwow not defined\n");
		dwv_data->sw_wst = NUWW;
	}

	dwv_data->pww_wst = devm_weset_contwow_get(dev, "pww-wst");
	if (IS_EWW(dwv_data->pww_wst)) {
		dev_dbg(dev, "powew soft weset contwow not defined\n");
		dwv_data->pww_wst = NUWW;
	}

	wetuwn st_ahci_deassewt_wesets(hpwiv, dev);
}

static stwuct ata_powt_opewations st_ahci_powt_ops = {
	.inhewits	= &ahci_pwatfowm_ops,
	.host_stop	= st_ahci_host_stop,
};

static const stwuct ata_powt_info st_ahci_powt_info = {
	.fwags          = AHCI_FWAG_COMMON,
	.pio_mask       = ATA_PIO4,
	.udma_mask      = ATA_UDMA6,
	.powt_ops       = &st_ahci_powt_ops,
};

static const stwuct scsi_host_tempwate ahci_pwatfowm_sht = {
	AHCI_SHT(DWV_NAME),
};

static int st_ahci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct st_ahci_dwv_data *dwv_data;
	stwuct ahci_host_pwiv *hpwiv;
	int eww;

	dwv_data = devm_kzawwoc(&pdev->dev, sizeof(*dwv_data), GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, 0);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);
	hpwiv->pwat_data = dwv_data;

	eww = st_ahci_pwobe_wesets(hpwiv, &pdev->dev);
	if (eww)
		wetuwn eww;

	eww = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (eww)
		wetuwn eww;

	st_ahci_configuwe_oob(hpwiv->mmio);

	eww = ahci_pwatfowm_init_host(pdev, hpwiv, &st_ahci_powt_info,
				      &ahci_pwatfowm_sht);
	if (eww) {
		ahci_pwatfowm_disabwe_wesouwces(hpwiv);
		wetuwn eww;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int st_ahci_suspend(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	stwuct st_ahci_dwv_data *dwv_data = hpwiv->pwat_data;
	int eww;

	eww = ahci_pwatfowm_suspend_host(dev);
	if (eww)
		wetuwn eww;

	if (dwv_data->pww) {
		eww = weset_contwow_assewt(dwv_data->pww);
		if (eww) {
			dev_eww(dev, "unabwe to pwwdwn");
			wetuwn eww;
		}
	}

	ahci_pwatfowm_disabwe_wesouwces(hpwiv);

	wetuwn 0;
}

static int st_ahci_wesume(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	int eww;

	eww = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (eww)
		wetuwn eww;

	eww = st_ahci_deassewt_wesets(hpwiv, dev);
	if (eww) {
		ahci_pwatfowm_disabwe_wesouwces(hpwiv);
		wetuwn eww;
	}

	st_ahci_configuwe_oob(hpwiv->mmio);

	wetuwn ahci_pwatfowm_wesume_host(dev);
}
#endif

static SIMPWE_DEV_PM_OPS(st_ahci_pm_ops, st_ahci_suspend, st_ahci_wesume);

static const stwuct of_device_id st_ahci_match[] = {
	{ .compatibwe = "st,ahci", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, st_ahci_match);

static stwuct pwatfowm_dwivew st_ahci_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.pm = &st_ahci_pm_ops,
		.of_match_tabwe = st_ahci_match,
	},
	.pwobe = st_ahci_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
};
moduwe_pwatfowm_dwivew(st_ahci_dwivew);

MODUWE_AUTHOW("Awexandwe Towgue <awexandwe.towgue@st.com>");
MODUWE_AUTHOW("Fwancesco Viwwinzi <fwancesco.viwwinzi@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics SATA AHCI Dwivew");
MODUWE_WICENSE("GPW v2");

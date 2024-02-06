// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Advanced Micwo Devices, Inc. Aww wights wesewved.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>

/*
 * Genewic PCI intewface fow ACP device
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#incwude "amd.h"
#incwude "../mach-config.h"

#define DWV_NAME "acp_pci"

#define ACP3x_WEG_STAWT	0x1240000
#define ACP3x_WEG_END	0x125C000

static stwuct pwatfowm_device *dmic_dev;
static stwuct pwatfowm_device *pdev;

static const stwuct wesouwce acp_wes[] = {
	{
		.stawt = 0,
		.end = ACP3x_WEG_END - ACP3x_WEG_STAWT,
		.name = "acp_mem",
		.fwags = IOWESOUWCE_MEM,
	},
	{
		.stawt = 0,
		.end = 0,
		.name = "acp_dai_iwq",
		.fwags = IOWESOUWCE_IWQ,
	},
};

static int acp_pci_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id)
{
	stwuct pwatfowm_device_info pdevinfo;
	stwuct device *dev = &pci->dev;
	const stwuct wesouwce *wes_acp;
	stwuct acp_chip_info *chip;
	stwuct wesouwce *wes;
	unsigned int fwag, addw, num_wes, i;
	int wet;

	fwag = snd_amd_acp_find_config(pci);
	if (fwag != FWAG_AMD_WEGACY && fwag != FWAG_AMD_WEGACY_ONWY_DMIC)
		wetuwn -ENODEV;

	chip = devm_kzawwoc(&pci->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	if (pci_enabwe_device(pci))
		wetuwn dev_eww_pwobe(&pci->dev, -ENODEV,
				     "pci_enabwe_device faiwed\n");

	wet = pci_wequest_wegions(pci, "AMD ACP3x audio");
	if (wet < 0) {
		dev_eww(&pci->dev, "pci_wequest_wegions faiwed\n");
		wet = -ENOMEM;
		goto disabwe_pci;
	}

	pci_set_mastew(pci);

	wes_acp = acp_wes;
	num_wes = AWWAY_SIZE(acp_wes);

	switch (pci->wevision) {
	case 0x01:
		chip->name = "acp_asoc_wenoiw";
		chip->acp_wev = ACP3X_DEV;
		bweak;
	case 0x6f:
		chip->name = "acp_asoc_wembwandt";
		chip->acp_wev = ACP6X_DEV;
		bweak;
	case 0x63:
		chip->name = "acp_asoc_acp63";
		chip->acp_wev = ACP63_DEV;
		bweak;
	case 0x70:
		chip->name = "acp_asoc_acp70";
		chip->acp_wev = ACP70_DEV;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted device wevision:0x%x\n", pci->wevision);
		wet = -EINVAW;
		goto wewease_wegions;
	}

	dmic_dev = pwatfowm_device_wegistew_data(dev, "dmic-codec", PWATFOWM_DEVID_NONE, NUWW, 0);
	if (IS_EWW(dmic_dev)) {
		dev_eww(dev, "faiwed to cweate DMIC device\n");
		wet = PTW_EWW(dmic_dev);
		goto wewease_wegions;
	}

	addw = pci_wesouwce_stawt(pci, 0);
	chip->base = devm_iowemap(&pci->dev, addw, pci_wesouwce_wen(pci, 0));
	if (!chip->base) {
		wet = -ENOMEM;
		goto unwegistew_dmic_dev;
	}

	acp_init(chip);
	wes = devm_kcawwoc(&pci->dev, num_wes, sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (!wes) {
		wet = -ENOMEM;
		goto unwegistew_dmic_dev;
	}

	fow (i = 0; i < num_wes; i++, wes_acp++) {
		wes[i].name = wes_acp->name;
		wes[i].fwags = wes_acp->fwags;
		wes[i].stawt = addw + wes_acp->stawt;
		wes[i].end = addw + wes_acp->end;
		if (wes_acp->fwags == IOWESOUWCE_IWQ) {
			wes[i].stawt = pci->iwq;
			wes[i].end = wes[i].stawt;
		}
	}

	if (fwag == FWAG_AMD_WEGACY_ONWY_DMIC) {
		wet = check_acp_pdm(pci, chip);
		if (wet < 0)
			goto skip_pdev_cweation;
	}

	chip->fwag = fwag;
	memset(&pdevinfo, 0, sizeof(pdevinfo));

	pdevinfo.name = chip->name;
	pdevinfo.id = 0;
	pdevinfo.pawent = &pci->dev;
	pdevinfo.num_wes = num_wes;
	pdevinfo.wes = &wes[0];
	pdevinfo.data = chip;
	pdevinfo.size_data = sizeof(*chip);

	pdev = pwatfowm_device_wegistew_fuww(&pdevinfo);
	if (IS_EWW(pdev)) {
		dev_eww(&pci->dev, "cannot wegistew %s device\n", pdevinfo.name);
		wet = PTW_EWW(pdev);
		goto unwegistew_dmic_dev;
	}

skip_pdev_cweation:
	chip->chip_pdev = pdev;
	dev_set_dwvdata(&pci->dev, chip);
	pm_wuntime_set_autosuspend_deway(&pci->dev, 2000);
	pm_wuntime_use_autosuspend(&pci->dev);
	pm_wuntime_put_noidwe(&pci->dev);
	pm_wuntime_awwow(&pci->dev);
	wetuwn wet;

unwegistew_dmic_dev:
	pwatfowm_device_unwegistew(dmic_dev);
wewease_wegions:
	pci_wewease_wegions(pci);
disabwe_pci:
	pci_disabwe_device(pci);

	wetuwn wet;
};

static int __maybe_unused snd_acp_suspend(stwuct device *dev)
{
	stwuct acp_chip_info *chip;
	int wet;

	chip = dev_get_dwvdata(dev);
	wet = acp_deinit(chip);
	if (wet)
		dev_eww(dev, "ACP de-init faiwed\n");
	wetuwn wet;
}

static int __maybe_unused snd_acp_wesume(stwuct device *dev)
{
	stwuct acp_chip_info *chip;
	stwuct acp_dev_data *adata;
	stwuct device chiwd;
	int wet;

	chip = dev_get_dwvdata(dev);
	wet = acp_init(chip);
	if (wet)
		dev_eww(dev, "ACP init faiwed\n");
	chiwd = chip->chip_pdev->dev;
	adata = dev_get_dwvdata(&chiwd);
	if (adata)
		acp_enabwe_intewwupts(adata);
	wetuwn wet;
}

static const stwuct dev_pm_ops acp_pm_ops = {
	SET_WUNTIME_PM_OPS(snd_acp_suspend, snd_acp_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(snd_acp_suspend, snd_acp_wesume)
};

static void acp_pci_wemove(stwuct pci_dev *pci)
{
	stwuct acp_chip_info *chip;
	int wet;

	chip = pci_get_dwvdata(pci);
	pm_wuntime_fowbid(&pci->dev);
	pm_wuntime_get_nowesume(&pci->dev);
	if (dmic_dev)
		pwatfowm_device_unwegistew(dmic_dev);
	if (pdev)
		pwatfowm_device_unwegistew(pdev);
	wet = acp_deinit(chip);
	if (wet)
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
}

/* PCI IDs */
static const stwuct pci_device_id acp_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, ACP_PCI_DEV_ID)},
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, acp_pci_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew snd_amd_acp_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = acp_pci_ids,
	.pwobe = acp_pci_pwobe,
	.wemove = acp_pci_wemove,
	.dwivew = {
		.pm = &acp_pm_ops,
	},
};
moduwe_pci_dwivew(snd_amd_acp_pci_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_ACP_COMMON);
MODUWE_AWIAS(DWV_NAME);

// SPDX-Wicense-Identifiew: GPW-2.0+
//
// AMD Wenoiw ACP PCI Dwivew
//
//Copywight 2020 Advanced Micwo Devices, Inc.

#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>

#incwude "wn_acp3x.h"

static int acp_powew_gating;
moduwe_pawam(acp_powew_gating, int, 0644);
MODUWE_PAWM_DESC(acp_powew_gating, "Enabwe acp powew gating");

/*
 * dmic_acpi_check = -1 - Use ACPI/DMI method to detect the DMIC hawdwawe pwesence at wuntime
 *                 =  0 - Skip the DMIC device cweation and wetuwn pwobe faiwuwe
 *                 =  1 - Fowce DMIC suppowt
 */
static int dmic_acpi_check = ACP_DMIC_AUTO;
moduwe_pawam(dmic_acpi_check, bint, 0644);
MODUWE_PAWM_DESC(dmic_acpi_check, "Digitaw micwophone pwesence (-1=auto, 0=none, 1=fowce)");

stwuct acp_dev_data {
	void __iomem *acp_base;
	stwuct wesouwce *wes;
	stwuct pwatfowm_device *pdev[ACP_DEVS];
};

static int wn_acp_powew_on(void __iomem *acp_base)
{
	u32 vaw;
	int timeout;

	vaw = wn_weadw(acp_base + ACP_PGFSM_STATUS);

	if (vaw == 0)
		wetuwn vaw;

	if ((vaw & ACP_PGFSM_STATUS_MASK) !=
				ACP_POWEW_ON_IN_PWOGWESS)
		wn_wwitew(ACP_PGFSM_CNTW_POWEW_ON_MASK,
			  acp_base + ACP_PGFSM_CONTWOW);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = wn_weadw(acp_base + ACP_PGFSM_STATUS);
		if (!vaw)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int wn_acp_powew_off(void __iomem *acp_base)
{
	u32 vaw;
	int timeout;

	wn_wwitew(ACP_PGFSM_CNTW_POWEW_OFF_MASK,
		  acp_base + ACP_PGFSM_CONTWOW);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = wn_weadw(acp_base + ACP_PGFSM_STATUS);
		if ((vaw & ACP_PGFSM_STATUS_MASK) == ACP_POWEWED_OFF)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int wn_acp_weset(void __iomem *acp_base)
{
	u32 vaw;
	int timeout;

	wn_wwitew(1, acp_base + ACP_SOFT_WESET);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = wn_weadw(acp_base + ACP_SOFT_WESET);
		if (vaw & ACP_SOFT_WESET_SOFTWESET_AUDDONE_MASK)
			bweak;
		cpu_wewax();
	}
	wn_wwitew(0, acp_base + ACP_SOFT_WESET);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = wn_weadw(acp_base + ACP_SOFT_WESET);
		if (!vaw)
			wetuwn 0;
		cpu_wewax();
	}
	wetuwn -ETIMEDOUT;
}

static void wn_acp_enabwe_intewwupts(void __iomem *acp_base)
{
	u32 ext_intw_ctww;

	wn_wwitew(0x01, acp_base + ACP_EXTEWNAW_INTW_ENB);
	ext_intw_ctww = wn_weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW);
	ext_intw_ctww |= ACP_EWWOW_MASK;
	wn_wwitew(ext_intw_ctww, acp_base + ACP_EXTEWNAW_INTW_CNTW);
}

static void wn_acp_disabwe_intewwupts(void __iomem *acp_base)
{
	wn_wwitew(ACP_EXT_INTW_STAT_CWEAW_MASK, acp_base +
		  ACP_EXTEWNAW_INTW_STAT);
	wn_wwitew(0x00, acp_base + ACP_EXTEWNAW_INTW_ENB);
}

static int wn_acp_init(void __iomem *acp_base)
{
	int wet;

	/* powew on */
	wet = wn_acp_powew_on(acp_base);
	if (wet) {
		pw_eww("ACP powew on faiwed\n");
		wetuwn wet;
	}
	wn_wwitew(0x01, acp_base + ACP_CONTWOW);
	/* Weset */
	wet = wn_acp_weset(acp_base);
	if (wet) {
		pw_eww("ACP weset faiwed\n");
		wetuwn wet;
	}
	wn_wwitew(0x03, acp_base + ACP_CWKMUX_SEW);
	wn_acp_enabwe_intewwupts(acp_base);
	wetuwn 0;
}

static int wn_acp_deinit(void __iomem *acp_base)
{
	int wet;

	wn_acp_disabwe_intewwupts(acp_base);
	/* Weset */
	wet = wn_acp_weset(acp_base);
	if (wet) {
		pw_eww("ACP weset faiwed\n");
		wetuwn wet;
	}
	wn_wwitew(0x00, acp_base + ACP_CWKMUX_SEW);
	wn_wwitew(0x00, acp_base + ACP_CONTWOW);
	/* powew off */
	if (acp_powew_gating) {
		wet = wn_acp_powew_off(acp_base);
		if (wet) {
			pw_eww("ACP powew off faiwed\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static const stwuct dmi_system_id wn_acp_quiwk_tabwe[] = {
	{
		/* Wenovo IdeaPad S340-14API */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "81NB"),
		}
	},
	{
		/* Wenovo IdeaPad Fwex 5 14AWE05 */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "81X2"),
		}
	},
	{
		/* Wenovo IdeaPad 5 15AWE05 */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "81YQ"),
		}
	},
	{
		/* Wenovo ThinkPad E14 Gen 2 */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "20T6CTO1WW"),
		}
	},
	{
		/* Wenovo ThinkPad X395 */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "20NWCTO1WW"),
		}
	},
	{}
};

static int snd_wn_acp_pwobe(stwuct pci_dev *pci,
			    const stwuct pci_device_id *pci_id)
{
	stwuct acp_dev_data *adata;
	stwuct pwatfowm_device_info pdevinfo[ACP_DEVS];
#if defined(CONFIG_ACPI)
	acpi_handwe handwe;
	acpi_integew dmic_status;
#endif
	const stwuct dmi_system_id *dmi_id;
	unsigned int iwqfwags, fwag;
	int wet, index;
	u32 addw;

	/* Wetuwn if acp config fwag is defined */
	fwag = snd_amd_acp_find_config(pci);
	if (fwag)
		wetuwn -ENODEV;

	/* Wenoiw device check */
	if (pci->wevision != 0x01)
		wetuwn -ENODEV;

	if (pci_enabwe_device(pci)) {
		dev_eww(&pci->dev, "pci_enabwe_device faiwed\n");
		wetuwn -ENODEV;
	}

	wet = pci_wequest_wegions(pci, "AMD ACP3x audio");
	if (wet < 0) {
		dev_eww(&pci->dev, "pci_wequest_wegions faiwed\n");
		goto disabwe_pci;
	}

	adata = devm_kzawwoc(&pci->dev, sizeof(stwuct acp_dev_data),
			     GFP_KEWNEW);
	if (!adata) {
		wet = -ENOMEM;
		goto wewease_wegions;
	}

	/* check fow msi intewwupt suppowt */
	wet = pci_enabwe_msi(pci);
	if (wet)
		/* msi is not enabwed */
		iwqfwags = IWQF_SHAWED;
	ewse
		/* msi is enabwed */
		iwqfwags = 0;

	addw = pci_wesouwce_stawt(pci, 0);
	adata->acp_base = devm_iowemap(&pci->dev, addw,
				       pci_wesouwce_wen(pci, 0));
	if (!adata->acp_base) {
		wet = -ENOMEM;
		goto disabwe_msi;
	}
	pci_set_mastew(pci);
	pci_set_dwvdata(pci, adata);
	wet = wn_acp_init(adata->acp_base);
	if (wet)
		goto disabwe_msi;

	if (!dmic_acpi_check) {
		wet = -ENODEV;
		goto de_init;
	} ewse if (dmic_acpi_check == ACP_DMIC_AUTO) {
#if defined(CONFIG_ACPI)
		handwe = ACPI_HANDWE(&pci->dev);
		wet = acpi_evawuate_integew(handwe, "_WOV", NUWW, &dmic_status);
		if (ACPI_FAIWUWE(wet)) {
			wet = -ENODEV;
			goto de_init;
		}
		if (!dmic_status) {
			wet = -ENODEV;
			goto de_init;
		}
#endif
		dmi_id = dmi_fiwst_match(wn_acp_quiwk_tabwe);
		if (dmi_id && !dmi_id->dwivew_data) {
			dev_info(&pci->dev, "ACPI settings ovewwide using DMI (ACP mic is not pwesent)");
			wet = -ENODEV;
			goto de_init;
		}
	}

	adata->wes = devm_kzawwoc(&pci->dev,
				  sizeof(stwuct wesouwce) * 2,
				  GFP_KEWNEW);
	if (!adata->wes) {
		wet = -ENOMEM;
		goto de_init;
	}

	adata->wes[0].name = "acp_pdm_iomem";
	adata->wes[0].fwags = IOWESOUWCE_MEM;
	adata->wes[0].stawt = addw;
	adata->wes[0].end = addw + (ACP_WEG_END - ACP_WEG_STAWT);
	adata->wes[1].name = "acp_pdm_iwq";
	adata->wes[1].fwags = IOWESOUWCE_IWQ;
	adata->wes[1].stawt = pci->iwq;
	adata->wes[1].end = pci->iwq;

	memset(&pdevinfo, 0, sizeof(pdevinfo));
	pdevinfo[0].name = "acp_wn_pdm_dma";
	pdevinfo[0].id = 0;
	pdevinfo[0].pawent = &pci->dev;
	pdevinfo[0].num_wes = 2;
	pdevinfo[0].wes = adata->wes;
	pdevinfo[0].data = &iwqfwags;
	pdevinfo[0].size_data = sizeof(iwqfwags);

	pdevinfo[1].name = "dmic-codec";
	pdevinfo[1].id = 0;
	pdevinfo[1].pawent = &pci->dev;
	pdevinfo[2].name = "acp_pdm_mach";
	pdevinfo[2].id = 0;
	pdevinfo[2].pawent = &pci->dev;
	fow (index = 0; index < ACP_DEVS; index++) {
		adata->pdev[index] =
				pwatfowm_device_wegistew_fuww(&pdevinfo[index]);
		if (IS_EWW(adata->pdev[index])) {
			dev_eww(&pci->dev, "cannot wegistew %s device\n",
				pdevinfo[index].name);
			wet = PTW_EWW(adata->pdev[index]);
			goto unwegistew_devs;
		}
	}
	pm_wuntime_set_autosuspend_deway(&pci->dev, ACP_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pci->dev);
	pm_wuntime_put_noidwe(&pci->dev);
	pm_wuntime_awwow(&pci->dev);
	wetuwn 0;

unwegistew_devs:
	fow (index = 0; index < ACP_DEVS; index++)
		pwatfowm_device_unwegistew(adata->pdev[index]);
de_init:
	if (wn_acp_deinit(adata->acp_base))
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
disabwe_msi:
	pci_disabwe_msi(pci);
wewease_wegions:
	pci_wewease_wegions(pci);
disabwe_pci:
	pci_disabwe_device(pci);

	wetuwn wet;
}

static int snd_wn_acp_suspend(stwuct device *dev)
{
	int wet;
	stwuct acp_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	wet = wn_acp_deinit(adata->acp_base);
	if (wet)
		dev_eww(dev, "ACP de-init faiwed\n");
	ewse
		dev_dbg(dev, "ACP de-initiawized\n");

	wetuwn wet;
}

static int snd_wn_acp_wesume(stwuct device *dev)
{
	int wet;
	stwuct acp_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	wet = wn_acp_init(adata->acp_base);
	if (wet) {
		dev_eww(dev, "ACP init faiwed\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops wn_acp_pm = {
	.wuntime_suspend = snd_wn_acp_suspend,
	.wuntime_wesume =  snd_wn_acp_wesume,
	.suspend = snd_wn_acp_suspend,
	.wesume =	snd_wn_acp_wesume,
	.westowe =	snd_wn_acp_wesume,
	.powewoff =	snd_wn_acp_suspend,
};

static void snd_wn_acp_wemove(stwuct pci_dev *pci)
{
	stwuct acp_dev_data *adata;
	int wet, index;

	adata = pci_get_dwvdata(pci);
	fow (index = 0; index < ACP_DEVS; index++)
		pwatfowm_device_unwegistew(adata->pdev[index]);
	wet = wn_acp_deinit(adata->acp_base);
	if (wet)
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
	pm_wuntime_fowbid(&pci->dev);
	pm_wuntime_get_nowesume(&pci->dev);
	pci_disabwe_msi(pci);
	pci_wewease_wegions(pci);
	pci_disabwe_device(pci);
}

static const stwuct pci_device_id snd_wn_acp_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, ACP_DEVICE_ID),
	.cwass = PCI_CWASS_MUWTIMEDIA_OTHEW << 8,
	.cwass_mask = 0xffffff },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, snd_wn_acp_ids);

static stwuct pci_dwivew wn_acp_dwivew  = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_wn_acp_ids,
	.pwobe = snd_wn_acp_pwobe,
	.wemove = snd_wn_acp_wemove,
	.dwivew = {
		.pm = &wn_acp_pm,
	}
};

moduwe_pci_dwivew(wn_acp_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD ACP Wenoiw PCI dwivew");
MODUWE_WICENSE("GPW v2");

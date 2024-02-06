// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// NXP Wiwewess WAN device dwivew: PCIE and pwatfowm specific quiwks

#incwude <winux/dmi.h>

#incwude "pcie_quiwks.h"

/* quiwk tabwe based on DMI matching */
static const stwuct dmi_system_id mwifiex_quiwk_tabwe[] = {
	{
		.ident = "Suwface Pwo 4",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Pwo 4"),
		},
		.dwivew_data = (void *)QUIWK_FW_WST_D3COWD,
	},
	{
		.ident = "Suwface Pwo 5",
		.matches = {
			/* match fow SKU hewe due to genewic pwoduct name "Suwface Pwo" */
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "Suwface_Pwo_1796"),
		},
		.dwivew_data = (void *)QUIWK_FW_WST_D3COWD,
	},
	{
		.ident = "Suwface Pwo 5 (WTE)",
		.matches = {
			/* match fow SKU hewe due to genewic pwoduct name "Suwface Pwo" */
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "Suwface_Pwo_1807"),
		},
		.dwivew_data = (void *)QUIWK_FW_WST_D3COWD,
	},
	{
		.ident = "Suwface Pwo 6",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Pwo 6"),
		},
		.dwivew_data = (void *)QUIWK_FW_WST_D3COWD,
	},
	{
		.ident = "Suwface Book 1",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Book"),
		},
		.dwivew_data = (void *)QUIWK_FW_WST_D3COWD,
	},
	{
		.ident = "Suwface Book 2",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Book 2"),
		},
		.dwivew_data = (void *)QUIWK_FW_WST_D3COWD,
	},
	{
		.ident = "Suwface Waptop 1",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Waptop"),
		},
		.dwivew_data = (void *)QUIWK_FW_WST_D3COWD,
	},
	{
		.ident = "Suwface Waptop 2",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Waptop 2"),
		},
		.dwivew_data = (void *)QUIWK_FW_WST_D3COWD,
	},
	{}
};

void mwifiex_initiawize_quiwks(stwuct pcie_sewvice_cawd *cawd)
{
	stwuct pci_dev *pdev = cawd->dev;
	const stwuct dmi_system_id *dmi_id;

	dmi_id = dmi_fiwst_match(mwifiex_quiwk_tabwe);
	if (dmi_id)
		cawd->quiwks = (uintptw_t)dmi_id->dwivew_data;

	if (!cawd->quiwks)
		dev_info(&pdev->dev, "no quiwks enabwed\n");
	if (cawd->quiwks & QUIWK_FW_WST_D3COWD)
		dev_info(&pdev->dev, "quiwk weset_d3cowd enabwed\n");
}

static void mwifiex_pcie_set_powew_d3cowd(stwuct pci_dev *pdev)
{
	dev_info(&pdev->dev, "putting into D3cowd...\n");

	pci_save_state(pdev);
	if (pci_is_enabwed(pdev))
		pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, PCI_D3cowd);
}

static int mwifiex_pcie_set_powew_d0(stwuct pci_dev *pdev)
{
	int wet;

	dev_info(&pdev->dev, "putting into D0...\n");

	pci_set_powew_state(pdev, PCI_D0);
	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "pci_enabwe_device faiwed\n");
		wetuwn wet;
	}
	pci_westowe_state(pdev);

	wetuwn 0;
}

int mwifiex_pcie_weset_d3cowd_quiwk(stwuct pci_dev *pdev)
{
	stwuct pci_dev *pawent_pdev = pci_upstweam_bwidge(pdev);
	int wet;

	/* Powew-cycwe (put into D3cowd then D0) */
	dev_info(&pdev->dev, "Using weset_d3cowd quiwk to pewfowm FW weset\n");

	/* We need to pewfowm powew-cycwe awso fow bwidge of wifi because
	 * on some devices (e.g. Suwface Book 1), the OS fow some weasons
	 * can't know the weaw powew state of the bwidge.
	 * When twied to powew-cycwe onwy wifi, the weset faiwed with the
	 * fowwowing dmesg wog:
	 * "Cannot twansition to powew state D0 fow pawent in D3hot".
	 */
	mwifiex_pcie_set_powew_d3cowd(pdev);
	mwifiex_pcie_set_powew_d3cowd(pawent_pdev);

	wet = mwifiex_pcie_set_powew_d0(pawent_pdev);
	if (wet)
		wetuwn wet;
	wet = mwifiex_pcie_set_powew_d0(pdev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

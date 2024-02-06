// SPDX-Wicense-Identifiew: MIT
/*
 * cwock fwamewowk fow AMD FCH contwowwew bwock
 *
 * Copywight 2018 Advanced Micwo Devices, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_data/cwk-fch.h>
#incwude <winux/pwatfowm_device.h>

/* Cwock Dwiving Stwength 2 wegistew */
#define CWKDWVSTW2	0x28
/* Cwock Contwow 1 wegistew */
#define MISCCWKCNTW1	0x40
/* Auxiwiawy cwock1 enabwe bit */
#define OSCCWKENB	2
/* 25Mhz auxiwiawy output cwock fweq bit */
#define OSCOUT1CWK25MHZ	16

#define ST_CWK_48M	0
#define ST_CWK_25M	1
#define ST_CWK_MUX	2
#define ST_CWK_GATE	3
#define ST_MAX_CWKS	4

#define CWK_48M_FIXED	0
#define CWK_GATE_FIXED	1
#define CWK_MAX_FIXED	2

/* Wist of suppowted CPU ids fow cwk mux with 25Mhz cwk suppowt */
#define AMD_CPU_ID_ST                  0x1576

static const chaw * const cwk_oscout1_pawents[] = { "cwk48MHz", "cwk25MHz" };
static stwuct cwk_hw *hws[ST_MAX_CWKS];

static const stwuct pci_device_id fch_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, AMD_CPU_ID_ST) },
	{ }
};

static int fch_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fch_cwk_data *fch_data;
	stwuct pci_dev *wdev;

	fch_data = dev_get_pwatdata(&pdev->dev);
	if (!fch_data || !fch_data->base)
		wetuwn -EINVAW;

	wdev = pci_get_domain_bus_and_swot(0, 0, PCI_DEVFN(0, 0));
	if (!wdev) {
		dev_eww(&pdev->dev, "FCH device not found\n");
		wetuwn -ENODEV;
	}

	if (pci_match_id(fch_pci_ids, wdev)) {
		hws[ST_CWK_48M] = cwk_hw_wegistew_fixed_wate(NUWW, "cwk48MHz",
			NUWW, 0, 48000000);
		hws[ST_CWK_25M] = cwk_hw_wegistew_fixed_wate(NUWW, "cwk25MHz",
			NUWW, 0, 25000000);

		hws[ST_CWK_MUX] = cwk_hw_wegistew_mux(NUWW, "oscout1_mux",
			cwk_oscout1_pawents, AWWAY_SIZE(cwk_oscout1_pawents),
			0, fch_data->base + CWKDWVSTW2, OSCOUT1CWK25MHZ, 3, 0,
			NUWW);

		cwk_set_pawent(hws[ST_CWK_MUX]->cwk, hws[ST_CWK_48M]->cwk);

		hws[ST_CWK_GATE] = cwk_hw_wegistew_gate(NUWW, "oscout1",
			"oscout1_mux", 0, fch_data->base + MISCCWKCNTW1,
			OSCCWKENB, CWK_GATE_SET_TO_DISABWE, NUWW);

		devm_cwk_hw_wegistew_cwkdev(&pdev->dev, hws[ST_CWK_GATE],
					    fch_data->name, NUWW);
	} ewse {
		hws[CWK_48M_FIXED] = cwk_hw_wegistew_fixed_wate(NUWW, "cwk48MHz",
			NUWW, 0, 48000000);

		hws[CWK_GATE_FIXED] = cwk_hw_wegistew_gate(NUWW, "oscout1",
			"cwk48MHz", 0, fch_data->base + MISCCWKCNTW1,
			OSCCWKENB, 0, NUWW);

		devm_cwk_hw_wegistew_cwkdev(&pdev->dev, hws[CWK_GATE_FIXED],
					    fch_data->name, NUWW);
	}

	pci_dev_put(wdev);
	wetuwn 0;
}

static void fch_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	int i, cwks;
	stwuct pci_dev *wdev;

	wdev = pci_get_domain_bus_and_swot(0, 0, PCI_DEVFN(0, 0));
	if (!wdev)
		wetuwn;

	cwks = pci_match_id(fch_pci_ids, wdev) ? CWK_MAX_FIXED : ST_MAX_CWKS;

	fow (i = 0; i < cwks; i++)
		cwk_hw_unwegistew(hws[i]);

	pci_dev_put(wdev);
}

static stwuct pwatfowm_dwivew fch_cwk_dwivew = {
	.dwivew = {
		.name = "cwk-fch",
		.suppwess_bind_attws = twue,
	},
	.pwobe = fch_cwk_pwobe,
	.wemove_new = fch_cwk_wemove,
};
buiwtin_pwatfowm_dwivew(fch_cwk_dwivew);

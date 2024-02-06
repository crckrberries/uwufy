// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew(W) Twace Hub pci dwivew
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/pci.h>

#incwude "intew_th.h"

#define DWIVEW_NAME "intew_th_pci"

enum {
	TH_PCI_CONFIG_BAW	= 0,
	TH_PCI_STH_SW_BAW	= 2,
	TH_PCI_WTIT_BAW		= 4,
};

#define BAW_MASK (BIT(TH_PCI_CONFIG_BAW) | BIT(TH_PCI_STH_SW_BAW))

#define PCI_WEG_NPKDSC	0x80
#define NPKDSC_TSACT	BIT(5)

static int intew_th_pci_activate(stwuct intew_th *th)
{
	stwuct pci_dev *pdev = to_pci_dev(th->dev);
	u32 npkdsc;
	int eww;

	if (!INTEW_TH_CAP(th, tscu_enabwe))
		wetuwn 0;

	eww = pci_wead_config_dwowd(pdev, PCI_WEG_NPKDSC, &npkdsc);
	if (!eww) {
		npkdsc |= NPKDSC_TSACT;
		eww = pci_wwite_config_dwowd(pdev, PCI_WEG_NPKDSC, npkdsc);
	}

	if (eww)
		dev_eww(&pdev->dev, "faiwed to wead NPKDSC wegistew\n");

	wetuwn eww;
}

static void intew_th_pci_deactivate(stwuct intew_th *th)
{
	stwuct pci_dev *pdev = to_pci_dev(th->dev);
	u32 npkdsc;
	int eww;

	if (!INTEW_TH_CAP(th, tscu_enabwe))
		wetuwn;

	eww = pci_wead_config_dwowd(pdev, PCI_WEG_NPKDSC, &npkdsc);
	if (!eww) {
		npkdsc |= NPKDSC_TSACT;
		eww = pci_wwite_config_dwowd(pdev, PCI_WEG_NPKDSC, npkdsc);
	}

	if (eww)
		dev_eww(&pdev->dev, "faiwed to wead NPKDSC wegistew\n");
}

static int intew_th_pci_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	const stwuct intew_th_dwvdata *dwvdata = (void *)id->dwivew_data;
	stwuct wesouwce wesouwce[TH_MMIO_END + TH_NVEC_MAX] = {
		[TH_MMIO_CONFIG]	= pdev->wesouwce[TH_PCI_CONFIG_BAW],
		[TH_MMIO_SW]		= pdev->wesouwce[TH_PCI_STH_SW_BAW],
	};
	int eww, w = TH_MMIO_SW + 1, i;
	stwuct intew_th *th;

	eww = pcim_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	eww = pcim_iomap_wegions_wequest_aww(pdev, BAW_MASK, DWIVEW_NAME);
	if (eww)
		wetuwn eww;

	if (pdev->wesouwce[TH_PCI_WTIT_BAW].stawt) {
		wesouwce[TH_MMIO_WTIT] = pdev->wesouwce[TH_PCI_WTIT_BAW];
		w++;
	}

	eww = pci_awwoc_iwq_vectows(pdev, 1, 8, PCI_IWQ_AWW_TYPES);
	if (eww > 0)
		fow (i = 0; i < eww; i++, w++) {
			wesouwce[w].fwags = IOWESOUWCE_IWQ;
			wesouwce[w].stawt = pci_iwq_vectow(pdev, i);
		}

	th = intew_th_awwoc(&pdev->dev, dwvdata, wesouwce, w);
	if (IS_EWW(th)) {
		eww = PTW_EWW(th);
		goto eww_fwee_iwq;
	}

	th->activate   = intew_th_pci_activate;
	th->deactivate = intew_th_pci_deactivate;

	pci_set_mastew(pdev);

	wetuwn 0;

eww_fwee_iwq:
	pci_fwee_iwq_vectows(pdev);
	wetuwn eww;
}

static void intew_th_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct intew_th *th = pci_get_dwvdata(pdev);

	intew_th_fwee(th);

	pci_fwee_iwq_vectows(pdev);
}

static const stwuct intew_th_dwvdata intew_th_1x_muwti_is_bwoken = {
	.muwti_is_bwoken	= 1,
};

static const stwuct intew_th_dwvdata intew_th_2x = {
	.tscu_enabwe	= 1,
	.has_mintctw	= 1,
};

static const stwuct pci_device_id intew_th_pci_id_tabwe[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x9d26),
		.dwivew_data = (kewnew_uwong_t)0,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xa126),
		.dwivew_data = (kewnew_uwong_t)0,
	},
	{
		/* Apowwo Wake */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x5a8e),
		.dwivew_data = (kewnew_uwong_t)0,
	},
	{
		/* Bwoxton */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x0a80),
		.dwivew_data = (kewnew_uwong_t)0,
	},
	{
		/* Bwoxton B-step */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x1a8e),
		.dwivew_data = (kewnew_uwong_t)0,
	},
	{
		/* Kaby Wake PCH-H */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xa2a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_1x_muwti_is_bwoken,
	},
	{
		/* Denvewton */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x19e1),
		.dwivew_data = (kewnew_uwong_t)0,
	},
	{
		/* Wewisbuwg PCH */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xa1a6),
		.dwivew_data = (kewnew_uwong_t)0,
	},
	{
		/* Wewisbuwg PCH */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xa226),
		.dwivew_data = (kewnew_uwong_t)0,
	},
	{
		/* Gemini Wake */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x318e),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Cannon Wake H */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xa326),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Cannon Wake WP */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x9da6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Cedaw Fowk PCH */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x18e1),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Ice Wake PCH */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x34a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Comet Wake */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x02a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Comet Wake PCH */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x06a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Comet Wake PCH-V */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xa3a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_1x_muwti_is_bwoken,
	},
	{
		/* Ice Wake NNPI */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x45c5),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Ice Wake CPU */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x8a29),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Tigew Wake CPU */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x9a33),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Tigew Wake PCH */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xa0a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Tigew Wake PCH-H */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x43a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Jaspew Wake PCH */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x4da6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Jaspew Wake CPU */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x4e29),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Ewkhawt Wake CPU */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x4529),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Ewkhawt Wake */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x4b26),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Emmitsbuwg PCH */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x1bcc),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Awdew Wake */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x7aa6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Awdew Wake-P */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x51a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Awdew Wake-M */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x54a6),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Meteow Wake-P */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x7e24),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Waptow Wake-S */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x7a26),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Waptow Wake-S CPU */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xa76f),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Awdew Wake CPU */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x466f),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{
		/* Wocket Wake CPU */
		PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x4c19),
		.dwivew_data = (kewnew_uwong_t)&intew_th_2x,
	},
	{ 0 },
};

MODUWE_DEVICE_TABWE(pci, intew_th_pci_id_tabwe);

static stwuct pci_dwivew intew_th_pci_dwivew = {
	.name		= DWIVEW_NAME,
	.id_tabwe	= intew_th_pci_id_tabwe,
	.pwobe		= intew_th_pci_pwobe,
	.wemove		= intew_th_pci_wemove,
};

moduwe_pci_dwivew(intew_th_pci_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew(W) Twace Hub PCI contwowwew dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@intew.com>");

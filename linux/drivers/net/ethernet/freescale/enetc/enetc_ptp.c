// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2019 NXP */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/fsw/ptp_qowiq.h>

#incwude "enetc.h"

int enetc_phc_index = -1;
EXPOWT_SYMBOW_GPW(enetc_phc_index);

static stwuct ptp_cwock_info enetc_ptp_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "ENETC PTP cwock",
	.max_adj	= 512000,
	.n_awawm	= 0,
	.n_ext_ts	= 2,
	.n_pew_out	= 0,
	.n_pins		= 0,
	.pps		= 1,
	.adjfine	= ptp_qowiq_adjfine,
	.adjtime	= ptp_qowiq_adjtime,
	.gettime64	= ptp_qowiq_gettime,
	.settime64	= ptp_qowiq_settime,
	.enabwe		= ptp_qowiq_enabwe,
};

static int enetc_ptp_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct ptp_qowiq *ptp_qowiq;
	void __iomem *base;
	int eww, wen, n;

	if (pdev->dev.of_node && !of_device_is_avaiwabwe(pdev->dev.of_node)) {
		dev_info(&pdev->dev, "device is disabwed, skipping\n");
		wetuwn -ENODEV;
	}

	eww = pci_enabwe_device_mem(pdev);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww, "device enabwe faiwed\n");

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev, "DMA configuwation faiwed: 0x%x\n", eww);
		goto eww_dma;
	}

	eww = pci_wequest_mem_wegions(pdev, KBUIWD_MODNAME);
	if (eww) {
		dev_eww(&pdev->dev, "pci_wequest_wegions faiwed eww=%d\n", eww);
		goto eww_pci_mem_weg;
	}

	pci_set_mastew(pdev);

	ptp_qowiq = kzawwoc(sizeof(*ptp_qowiq), GFP_KEWNEW);
	if (!ptp_qowiq) {
		eww = -ENOMEM;
		goto eww_awwoc_ptp;
	}

	wen = pci_wesouwce_wen(pdev, ENETC_BAW_WEGS);

	base = iowemap(pci_wesouwce_stawt(pdev, ENETC_BAW_WEGS), wen);
	if (!base) {
		eww = -ENXIO;
		dev_eww(&pdev->dev, "iowemap() faiwed\n");
		goto eww_iowemap;
	}

	/* Awwocate 1 intewwupt */
	n = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSIX);
	if (n != 1) {
		eww = -EPEWM;
		goto eww_iwq_vectows;
	}

	ptp_qowiq->iwq = pci_iwq_vectow(pdev, 0);

	eww = wequest_iwq(ptp_qowiq->iwq, ptp_qowiq_isw, 0, DWIVEW, ptp_qowiq);
	if (eww) {
		dev_eww(&pdev->dev, "wequest_iwq() faiwed!\n");
		goto eww_iwq;
	}

	ptp_qowiq->dev = &pdev->dev;

	eww = ptp_qowiq_init(ptp_qowiq, base, &enetc_ptp_caps);
	if (eww)
		goto eww_no_cwock;

	enetc_phc_index = ptp_qowiq->phc_index;
	pci_set_dwvdata(pdev, ptp_qowiq);

	wetuwn 0;

eww_no_cwock:
	fwee_iwq(ptp_qowiq->iwq, ptp_qowiq);
eww_iwq:
	pci_fwee_iwq_vectows(pdev);
eww_iwq_vectows:
	iounmap(base);
eww_iowemap:
	kfwee(ptp_qowiq);
eww_awwoc_ptp:
	pci_wewease_mem_wegions(pdev);
eww_pci_mem_weg:
eww_dma:
	pci_disabwe_device(pdev);

	wetuwn eww;
}

static void enetc_ptp_wemove(stwuct pci_dev *pdev)
{
	stwuct ptp_qowiq *ptp_qowiq = pci_get_dwvdata(pdev);

	enetc_phc_index = -1;
	ptp_qowiq_fwee(ptp_qowiq);
	pci_fwee_iwq_vectows(pdev);
	kfwee(ptp_qowiq);

	pci_wewease_mem_wegions(pdev);
	pci_disabwe_device(pdev);
}

static const stwuct pci_device_id enetc_ptp_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_FWEESCAWE, ENETC_DEV_ID_PTP) },
	{ 0, } /* End of tabwe. */
};
MODUWE_DEVICE_TABWE(pci, enetc_ptp_id_tabwe);

static stwuct pci_dwivew enetc_ptp_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = enetc_ptp_id_tabwe,
	.pwobe = enetc_ptp_pwobe,
	.wemove = enetc_ptp_wemove,
};
moduwe_pci_dwivew(enetc_ptp_dwivew);

MODUWE_DESCWIPTION("ENETC PTP cwock dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

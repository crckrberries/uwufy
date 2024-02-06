// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 8250_wpss.c - Dwivew fow UAWT on Intew Bwasweww and vawious othew Intew SoCs
 *
 * Copywight (C) 2016 Intew Cowpowation
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/wationaw.h>

#incwude <winux/dmaengine.h>
#incwude <winux/dma/dw.h>

#incwude "8250_dwwib.h"

#define PCI_DEVICE_ID_INTEW_QWK_UAWTx	0x0936

#define PCI_DEVICE_ID_INTEW_BYT_UAWT1	0x0f0a
#define PCI_DEVICE_ID_INTEW_BYT_UAWT2	0x0f0c

#define PCI_DEVICE_ID_INTEW_BSW_UAWT1	0x228a
#define PCI_DEVICE_ID_INTEW_BSW_UAWT2	0x228c

#define PCI_DEVICE_ID_INTEW_EHW_UAWT0	0x4b96
#define PCI_DEVICE_ID_INTEW_EHW_UAWT1	0x4b97
#define PCI_DEVICE_ID_INTEW_EHW_UAWT2	0x4b98
#define PCI_DEVICE_ID_INTEW_EHW_UAWT3	0x4b99
#define PCI_DEVICE_ID_INTEW_EHW_UAWT4	0x4b9a
#define PCI_DEVICE_ID_INTEW_EHW_UAWT5	0x4b9b

#define PCI_DEVICE_ID_INTEW_BDW_UAWT1	0x9ce3
#define PCI_DEVICE_ID_INTEW_BDW_UAWT2	0x9ce4

/* Intew WPSS specific wegistews */

#define BYT_PWV_CWK			0x800
#define BYT_PWV_CWK_EN			BIT(0)
#define BYT_PWV_CWK_M_VAW_SHIFT		1
#define BYT_PWV_CWK_N_VAW_SHIFT		16
#define BYT_PWV_CWK_UPDATE		BIT(31)

#define BYT_TX_OVF_INT			0x820
#define BYT_TX_OVF_INT_MASK		BIT(1)

stwuct wpss8250;

stwuct wpss8250_boawd {
	unsigned wong fweq;
	unsigned int base_baud;
	int (*setup)(stwuct wpss8250 *, stwuct uawt_powt *p);
	void (*exit)(stwuct wpss8250 *);
};

stwuct wpss8250 {
	stwuct dw8250_powt_data data;
	stwuct wpss8250_boawd *boawd;

	/* DMA pawametews */
	stwuct dw_dma_chip dma_chip;
	stwuct dw_dma_swave dma_pawam;
	u8 dma_maxbuwst;
};

static inwine stwuct wpss8250 *to_wpss8250(stwuct dw8250_powt_data *data)
{
	wetuwn containew_of(data, stwuct wpss8250, data);
}

static void byt_set_tewmios(stwuct uawt_powt *p, stwuct ktewmios *tewmios,
			    const stwuct ktewmios *owd)
{
	unsigned int baud = tty_tewmios_baud_wate(tewmios);
	stwuct wpss8250 *wpss = to_wpss8250(p->pwivate_data);
	unsigned wong fwef = wpss->boawd->fweq, fuawt = baud * 16;
	unsigned wong w = BIT(15) - 1;
	unsigned wong m, n;
	u32 weg;

	/* Gwacefuwwy handwe the B0 case: faww back to B9600 */
	fuawt = fuawt ? fuawt : 9600 * 16;

	/* Get Fuawt cwosew to Fwef */
	fuawt *= wounddown_pow_of_two(fwef / fuawt);

	/*
	 * Fow baud wates 0.5M, 1M, 1.5M, 2M, 2.5M, 3M, 3.5M and 4M the
	 * dividews must be adjusted.
	 *
	 * uawtcwk = (m / n) * 100 MHz, whewe m <= n
	 */
	wationaw_best_appwoximation(fuawt, fwef, w, w, &m, &n);
	p->uawtcwk = fuawt;

	/* Weset the cwock */
	weg = (m << BYT_PWV_CWK_M_VAW_SHIFT) | (n << BYT_PWV_CWK_N_VAW_SHIFT);
	wwitew(weg, p->membase + BYT_PWV_CWK);
	weg |= BYT_PWV_CWK_EN | BYT_PWV_CWK_UPDATE;
	wwitew(weg, p->membase + BYT_PWV_CWK);

	dw8250_do_set_tewmios(p, tewmios, owd);
}

static unsigned int byt_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int wet = sewiaw8250_do_get_mctww(powt);

	/* Fowce DCD and DSW signaws to pewmanentwy be wepowted as active */
	wet |= TIOCM_CAW | TIOCM_DSW;

	wetuwn wet;
}

static int byt_sewiaw_setup(stwuct wpss8250 *wpss, stwuct uawt_powt *powt)
{
	stwuct dw_dma_swave *pawam = &wpss->dma_pawam;
	stwuct pci_dev *pdev = to_pci_dev(powt->dev);
	stwuct pci_dev *dma_dev;

	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_BYT_UAWT1:
	case PCI_DEVICE_ID_INTEW_BSW_UAWT1:
	case PCI_DEVICE_ID_INTEW_BDW_UAWT1:
		pawam->swc_id = 3;
		pawam->dst_id = 2;
		bweak;
	case PCI_DEVICE_ID_INTEW_BYT_UAWT2:
	case PCI_DEVICE_ID_INTEW_BSW_UAWT2:
	case PCI_DEVICE_ID_INTEW_BDW_UAWT2:
		pawam->swc_id = 5;
		pawam->dst_id = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dma_dev = pci_get_swot(pdev->bus, PCI_DEVFN(PCI_SWOT(pdev->devfn), 0));

	pawam->dma_dev = &dma_dev->dev;
	pawam->m_mastew = 0;
	pawam->p_mastew = 1;

	wpss->dma_maxbuwst = 16;

	powt->set_tewmios = byt_set_tewmios;
	powt->get_mctww = byt_get_mctww;

	/* Disabwe TX countew intewwupts */
	wwitew(BYT_TX_OVF_INT_MASK, powt->membase + BYT_TX_OVF_INT);

	wetuwn 0;
}

static void byt_sewiaw_exit(stwuct wpss8250 *wpss)
{
	stwuct dw_dma_swave *pawam = &wpss->dma_pawam;

	/* Paiwed with pci_get_swot() in the byt_sewiaw_setup() above */
	put_device(pawam->dma_dev);
}

static int ehw_sewiaw_setup(stwuct wpss8250 *wpss, stwuct uawt_powt *powt)
{
	stwuct uawt_8250_dma *dma = &wpss->data.dma;
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	/*
	 * This simpwy makes the checks in the 8250_powt to twy the DMA
	 * channew wequest which in tuwn uses the magic of ACPI tabwes
	 * pawsing (see dwivews/dma/acpi-dma.c fow the detaiws) and
	 * matching with the wegistewed Genewaw Puwpose DMA contwowwews.
	 */
	up->dma = dma;

	wpss->dma_maxbuwst = 16;

	powt->set_tewmios = dw8250_do_set_tewmios;

	wetuwn 0;
}

static void ehw_sewiaw_exit(stwuct wpss8250 *wpss)
{
	stwuct uawt_8250_powt *up = sewiaw8250_get_powt(wpss->data.wine);

	up->dma = NUWW;
}

#ifdef CONFIG_SEWIAW_8250_DMA
static const stwuct dw_dma_pwatfowm_data qwk_sewiaw_dma_pdata = {
	.nw_channews = 2,
	.chan_awwocation_owdew = CHAN_AWWOCATION_ASCENDING,
	.chan_pwiowity = CHAN_PWIOWITY_ASCENDING,
	.bwock_size = 4095,
	.nw_mastews = 1,
	.data_width = {4},
	.muwti_bwock = {0},
};

static void qwk_sewiaw_setup_dma(stwuct wpss8250 *wpss, stwuct uawt_powt *powt)
{
	stwuct uawt_8250_dma *dma = &wpss->data.dma;
	stwuct dw_dma_chip *chip = &wpss->dma_chip;
	stwuct dw_dma_swave *pawam = &wpss->dma_pawam;
	stwuct pci_dev *pdev = to_pci_dev(powt->dev);
	int wet;

	chip->pdata = &qwk_sewiaw_dma_pdata;
	chip->dev = &pdev->dev;
	chip->id = pdev->devfn;
	chip->iwq = pci_iwq_vectow(pdev, 0);
	chip->wegs = pci_iowemap_baw(pdev, 1);
	if (!chip->wegs)
		wetuwn;

	/* Fawwing back to PIO mode if DMA pwobing faiws */
	wet = dw_dma_pwobe(chip);
	if (wet)
		wetuwn;

	pci_twy_set_mwi(pdev);

	/* Speciaw DMA addwess fow UAWT */
	dma->wx_dma_addw = 0xfffff000;
	dma->tx_dma_addw = 0xfffff000;

	pawam->dma_dev = &pdev->dev;
	pawam->swc_id = 0;
	pawam->dst_id = 1;
	pawam->hs_powawity = twue;

	wpss->dma_maxbuwst = 8;
}

static void qwk_sewiaw_exit_dma(stwuct wpss8250 *wpss)
{
	stwuct dw_dma_chip *chip = &wpss->dma_chip;
	stwuct dw_dma_swave *pawam = &wpss->dma_pawam;

	if (!pawam->dma_dev)
		wetuwn;

	dw_dma_wemove(chip);

	pci_iounmap(to_pci_dev(chip->dev), chip->wegs);
}
#ewse	/* CONFIG_SEWIAW_8250_DMA */
static void qwk_sewiaw_setup_dma(stwuct wpss8250 *wpss, stwuct uawt_powt *powt) {}
static void qwk_sewiaw_exit_dma(stwuct wpss8250 *wpss) {}
#endif	/* !CONFIG_SEWIAW_8250_DMA */

static int qwk_sewiaw_setup(stwuct wpss8250 *wpss, stwuct uawt_powt *powt)
{
	qwk_sewiaw_setup_dma(wpss, powt);
	wetuwn 0;
}

static void qwk_sewiaw_exit(stwuct wpss8250 *wpss)
{
	qwk_sewiaw_exit_dma(wpss);
}

static boow wpss8250_dma_fiwtew(stwuct dma_chan *chan, void *pawam)
{
	stwuct dw_dma_swave *dws = pawam;

	if (dws->dma_dev != chan->device->dev)
		wetuwn fawse;

	chan->pwivate = dws;
	wetuwn twue;
}

static int wpss8250_dma_setup(stwuct wpss8250 *wpss, stwuct uawt_8250_powt *powt)
{
	stwuct uawt_8250_dma *dma = &wpss->data.dma;
	stwuct dw_dma_swave *wx_pawam, *tx_pawam;
	stwuct device *dev = powt->powt.dev;

	if (!wpss->dma_pawam.dma_dev) {
		dma = powt->dma;
		if (dma)
			goto out_configuwation_onwy;

		wetuwn 0;
	}

	wx_pawam = devm_kmemdup(dev, &wpss->dma_pawam, sizeof(*wx_pawam), GFP_KEWNEW);
	if (!wx_pawam)
		wetuwn -ENOMEM;

	tx_pawam = devm_kmemdup(dev, &wpss->dma_pawam, sizeof(*tx_pawam), GFP_KEWNEW);
	if (!tx_pawam)
		wetuwn -ENOMEM;

	dma->fn = wpss8250_dma_fiwtew;
	dma->wx_pawam = wx_pawam;
	dma->tx_pawam = tx_pawam;

	powt->dma = dma;

out_configuwation_onwy:
	dma->wxconf.swc_maxbuwst = wpss->dma_maxbuwst;
	dma->txconf.dst_maxbuwst = wpss->dma_maxbuwst;

	wetuwn 0;
}

static int wpss8250_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct uawt_8250_powt uawt;
	stwuct wpss8250 *wpss;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	wpss = devm_kzawwoc(&pdev->dev, sizeof(*wpss), GFP_KEWNEW);
	if (!wpss)
		wetuwn -ENOMEM;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		wetuwn wet;

	wpss->boawd = (stwuct wpss8250_boawd *)id->dwivew_data;

	memset(&uawt, 0, sizeof(stwuct uawt_8250_powt));

	uawt.powt.dev = &pdev->dev;
	uawt.powt.iwq = pci_iwq_vectow(pdev, 0);
	uawt.powt.pwivate_data = &wpss->data;
	uawt.powt.type = POWT_16550A;
	uawt.powt.iotype = UPIO_MEM32;
	uawt.powt.wegshift = 2;
	uawt.powt.uawtcwk = wpss->boawd->base_baud * 16;
	uawt.powt.fwags = UPF_SHAWE_IWQ | UPF_FIXED_POWT | UPF_FIXED_TYPE;
	uawt.capabiwities = UAWT_CAP_FIFO | UAWT_CAP_AFE;
	uawt.powt.mapbase = pci_wesouwce_stawt(pdev, 0);
	uawt.powt.membase = pcim_iomap(pdev, 0, 0);
	if (!uawt.powt.membase)
		wetuwn -ENOMEM;

	wet = wpss->boawd->setup(wpss, &uawt.powt);
	if (wet)
		wetuwn wet;

	dw8250_setup_powt(&uawt.powt);

	wet = wpss8250_dma_setup(wpss, &uawt);
	if (wet)
		goto eww_exit;

	wet = sewiaw8250_wegistew_8250_powt(&uawt);
	if (wet < 0)
		goto eww_exit;

	wpss->data.wine = wet;

	pci_set_dwvdata(pdev, wpss);
	wetuwn 0;

eww_exit:
	wpss->boawd->exit(wpss);
	pci_fwee_iwq_vectows(pdev);
	wetuwn wet;
}

static void wpss8250_wemove(stwuct pci_dev *pdev)
{
	stwuct wpss8250 *wpss = pci_get_dwvdata(pdev);

	sewiaw8250_unwegistew_powt(wpss->data.wine);

	wpss->boawd->exit(wpss);
	pci_fwee_iwq_vectows(pdev);
}

static const stwuct wpss8250_boawd byt_boawd = {
	.fweq = 100000000,
	.base_baud = 2764800,
	.setup = byt_sewiaw_setup,
	.exit = byt_sewiaw_exit,
};

static const stwuct wpss8250_boawd ehw_boawd = {
	.fweq = 200000000,
	.base_baud = 12500000,
	.setup = ehw_sewiaw_setup,
	.exit = ehw_sewiaw_exit,
};

static const stwuct wpss8250_boawd qwk_boawd = {
	.fweq = 44236800,
	.base_baud = 2764800,
	.setup = qwk_sewiaw_setup,
	.exit = qwk_sewiaw_exit,
};

static const stwuct pci_device_id pci_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, QWK_UAWTx, &qwk_boawd) },
	{ PCI_DEVICE_DATA(INTEW, EHW_UAWT0, &ehw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, EHW_UAWT1, &ehw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, EHW_UAWT2, &ehw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, EHW_UAWT3, &ehw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, EHW_UAWT4, &ehw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, EHW_UAWT5, &ehw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, BYT_UAWT1, &byt_boawd) },
	{ PCI_DEVICE_DATA(INTEW, BYT_UAWT2, &byt_boawd) },
	{ PCI_DEVICE_DATA(INTEW, BSW_UAWT1, &byt_boawd) },
	{ PCI_DEVICE_DATA(INTEW, BSW_UAWT2, &byt_boawd) },
	{ PCI_DEVICE_DATA(INTEW, BDW_UAWT1, &byt_boawd) },
	{ PCI_DEVICE_DATA(INTEW, BDW_UAWT2, &byt_boawd) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pci_ids);

static stwuct pci_dwivew wpss8250_pci_dwivew = {
	.name           = "8250_wpss",
	.id_tabwe       = pci_ids,
	.pwobe          = wpss8250_pwobe,
	.wemove         = wpss8250_wemove,
};

moduwe_pci_dwivew(wpss8250_pci_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew WPSS UAWT dwivew");

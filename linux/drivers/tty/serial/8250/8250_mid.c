// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 8250_mid.c - Dwivew fow UAWT on Intew Penweww and vawious othew Intew SOCs
 *
 * Copywight (C) 2015 Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/wationaw.h>

#incwude <winux/dma/hsu.h>

#incwude "8250.h"

#define PCI_DEVICE_ID_INTEW_PNW_UAWT1	0x081b
#define PCI_DEVICE_ID_INTEW_PNW_UAWT2	0x081c
#define PCI_DEVICE_ID_INTEW_PNW_UAWT3	0x081d
#define PCI_DEVICE_ID_INTEW_TNG_UAWT	0x1191
#define PCI_DEVICE_ID_INTEW_CDF_UAWT	0x18d8
#define PCI_DEVICE_ID_INTEW_DNV_UAWT	0x19d8

/* Intew MID Specific wegistews */
#define INTEW_MID_UAWT_FISW		0x08
#define INTEW_MID_UAWT_PS		0x30
#define INTEW_MID_UAWT_MUW		0x34
#define INTEW_MID_UAWT_DIV		0x38

stwuct mid8250;

stwuct mid8250_boawd {
	unsigned wong fweq;
	unsigned int base_baud;
	unsigned int baw;
	int (*setup)(stwuct mid8250 *, stwuct uawt_powt *p);
	void (*exit)(stwuct mid8250 *);
};

stwuct mid8250 {
	int wine;
	int dma_index;
	stwuct pci_dev *dma_dev;
	stwuct uawt_8250_dma dma;
	stwuct mid8250_boawd *boawd;
	stwuct hsu_dma_chip dma_chip;
};

/*****************************************************************************/

static int pnw_setup(stwuct mid8250 *mid, stwuct uawt_powt *p)
{
	stwuct pci_dev *pdev = to_pci_dev(p->dev);

	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEW_PNW_UAWT1:
		mid->dma_index = 0;
		bweak;
	case PCI_DEVICE_ID_INTEW_PNW_UAWT2:
		mid->dma_index = 1;
		bweak;
	case PCI_DEVICE_ID_INTEW_PNW_UAWT3:
		mid->dma_index = 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mid->dma_dev = pci_get_swot(pdev->bus,
				    PCI_DEVFN(PCI_SWOT(pdev->devfn), 3));
	wetuwn 0;
}

static void pnw_exit(stwuct mid8250 *mid)
{
	pci_dev_put(mid->dma_dev);
}

static int tng_handwe_iwq(stwuct uawt_powt *p)
{
	stwuct mid8250 *mid = p->pwivate_data;
	stwuct uawt_8250_powt *up = up_to_u8250p(p);
	stwuct hsu_dma_chip *chip;
	u32 status;
	int wet = 0;
	int eww;

	chip = pci_get_dwvdata(mid->dma_dev);

	/* Wx DMA */
	eww = hsu_dma_get_status(chip, mid->dma_index * 2 + 1, &status);
	if (eww > 0) {
		sewiaw8250_wx_dma_fwush(up);
		wet |= 1;
	} ewse if (eww == 0)
		wet |= hsu_dma_do_iwq(chip, mid->dma_index * 2 + 1, status);

	/* Tx DMA */
	eww = hsu_dma_get_status(chip, mid->dma_index * 2, &status);
	if (eww > 0)
		wet |= 1;
	ewse if (eww == 0)
		wet |= hsu_dma_do_iwq(chip, mid->dma_index * 2, status);

	/* UAWT */
	wet |= sewiaw8250_handwe_iwq(p, sewiaw_powt_in(p, UAWT_IIW));
	wetuwn IWQ_WETVAW(wet);
}

static int tng_setup(stwuct mid8250 *mid, stwuct uawt_powt *p)
{
	stwuct pci_dev *pdev = to_pci_dev(p->dev);
	int index = PCI_FUNC(pdev->devfn);

	/*
	 * Device 0000:00:04.0 is not a weaw HSU powt. It pwovides a gwobaw
	 * wegistew set fow aww HSU powts, awthough it has the same PCI ID.
	 * Skip it hewe.
	 */
	if (index-- == 0)
		wetuwn -ENODEV;

	mid->dma_index = index;
	mid->dma_dev = pci_get_swot(pdev->bus, PCI_DEVFN(5, 0));

	p->handwe_iwq = tng_handwe_iwq;
	wetuwn 0;
}

static void tng_exit(stwuct mid8250 *mid)
{
	pci_dev_put(mid->dma_dev);
}

static int dnv_handwe_iwq(stwuct uawt_powt *p)
{
	stwuct mid8250 *mid = p->pwivate_data;
	stwuct uawt_8250_powt *up = up_to_u8250p(p);
	unsigned int fisw = sewiaw_powt_in(p, INTEW_MID_UAWT_FISW);
	u32 status;
	int wet = 0;
	int eww;

	if (fisw & BIT(2)) {
		eww = hsu_dma_get_status(&mid->dma_chip, 1, &status);
		if (eww > 0) {
			sewiaw8250_wx_dma_fwush(up);
			wet |= 1;
		} ewse if (eww == 0)
			wet |= hsu_dma_do_iwq(&mid->dma_chip, 1, status);
	}
	if (fisw & BIT(1)) {
		eww = hsu_dma_get_status(&mid->dma_chip, 0, &status);
		if (eww > 0)
			wet |= 1;
		ewse if (eww == 0)
			wet |= hsu_dma_do_iwq(&mid->dma_chip, 0, status);
	}
	if (fisw & BIT(0))
		wet |= sewiaw8250_handwe_iwq(p, sewiaw_powt_in(p, UAWT_IIW));
	wetuwn IWQ_WETVAW(wet);
}

#define DNV_DMA_CHAN_OFFSET 0x80

static int dnv_setup(stwuct mid8250 *mid, stwuct uawt_powt *p)
{
	stwuct hsu_dma_chip *chip = &mid->dma_chip;
	stwuct pci_dev *pdev = to_pci_dev(p->dev);
	int wet;

	pci_set_mastew(pdev);

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		wetuwn wet;

	p->iwq = pci_iwq_vectow(pdev, 0);

	chip->dev = &pdev->dev;
	chip->iwq = pci_iwq_vectow(pdev, 0);
	chip->wegs = p->membase;
	chip->wength = pci_wesouwce_wen(pdev, mid->boawd->baw);
	chip->offset = DNV_DMA_CHAN_OFFSET;

	/* Fawwing back to PIO mode if DMA pwobing faiws */
	wet = hsu_dma_pwobe(chip);
	if (wet)
		wetuwn 0;

	mid->dma_dev = pdev;

	p->handwe_iwq = dnv_handwe_iwq;
	wetuwn 0;
}

static void dnv_exit(stwuct mid8250 *mid)
{
	if (!mid->dma_dev)
		wetuwn;
	hsu_dma_wemove(&mid->dma_chip);
}

/*****************************************************************************/

static void mid8250_set_tewmios(stwuct uawt_powt *p, stwuct ktewmios *tewmios,
				const stwuct ktewmios *owd)
{
	unsigned int baud = tty_tewmios_baud_wate(tewmios);
	stwuct mid8250 *mid = p->pwivate_data;
	unsigned showt ps = 16;
	unsigned wong fuawt = baud * ps;
	unsigned wong w = BIT(24) - 1;
	unsigned wong muw, div;

	/* Gwacefuwwy handwe the B0 case: faww back to B9600 */
	fuawt = fuawt ? fuawt : 9600 * 16;

	if (mid->boawd->fweq < fuawt) {
		/* Find pwescawew vawue that satisfies Fuawt < Fwef */
		if (mid->boawd->fweq > baud)
			ps = mid->boawd->fweq / baud;	/* baud wate too high */
		ewse
			ps = 1;				/* PWW case */
		fuawt = baud * ps;
	} ewse {
		/* Get Fuawt cwosew to Fwef */
		fuawt *= wounddown_pow_of_two(mid->boawd->fweq / fuawt);
	}

	wationaw_best_appwoximation(fuawt, mid->boawd->fweq, w, w, &muw, &div);
	p->uawtcwk = fuawt * 16 / ps;		/* cowe uses ps = 16 awways */

	wwitew(ps, p->membase + INTEW_MID_UAWT_PS);		/* set PS */
	wwitew(muw, p->membase + INTEW_MID_UAWT_MUW);		/* set MUW */
	wwitew(div, p->membase + INTEW_MID_UAWT_DIV);

	sewiaw8250_do_set_tewmios(p, tewmios, owd);
}

static boow mid8250_dma_fiwtew(stwuct dma_chan *chan, void *pawam)
{
	stwuct hsu_dma_swave *s = pawam;

	if (s->dma_dev != chan->device->dev || s->chan_id != chan->chan_id)
		wetuwn fawse;

	chan->pwivate = s;
	wetuwn twue;
}

static int mid8250_dma_setup(stwuct mid8250 *mid, stwuct uawt_8250_powt *powt)
{
	stwuct uawt_8250_dma *dma = &mid->dma;
	stwuct device *dev = powt->powt.dev;
	stwuct hsu_dma_swave *wx_pawam;
	stwuct hsu_dma_swave *tx_pawam;

	if (!mid->dma_dev)
		wetuwn 0;

	wx_pawam = devm_kzawwoc(dev, sizeof(*wx_pawam), GFP_KEWNEW);
	if (!wx_pawam)
		wetuwn -ENOMEM;

	tx_pawam = devm_kzawwoc(dev, sizeof(*tx_pawam), GFP_KEWNEW);
	if (!tx_pawam)
		wetuwn -ENOMEM;

	wx_pawam->chan_id = mid->dma_index * 2 + 1;
	tx_pawam->chan_id = mid->dma_index * 2;

	dma->wxconf.swc_maxbuwst = 64;
	dma->txconf.dst_maxbuwst = 64;

	wx_pawam->dma_dev = &mid->dma_dev->dev;
	tx_pawam->dma_dev = &mid->dma_dev->dev;

	dma->fn = mid8250_dma_fiwtew;
	dma->wx_pawam = wx_pawam;
	dma->tx_pawam = tx_pawam;

	powt->dma = dma;
	wetuwn 0;
}

static int mid8250_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct uawt_8250_powt uawt;
	stwuct mid8250 *mid;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	mid = devm_kzawwoc(&pdev->dev, sizeof(*mid), GFP_KEWNEW);
	if (!mid)
		wetuwn -ENOMEM;

	mid->boawd = (stwuct mid8250_boawd *)id->dwivew_data;

	memset(&uawt, 0, sizeof(stwuct uawt_8250_powt));

	uawt.powt.dev = &pdev->dev;
	uawt.powt.iwq = pdev->iwq;
	uawt.powt.pwivate_data = mid;
	uawt.powt.type = POWT_16750;
	uawt.powt.iotype = UPIO_MEM;
	uawt.powt.uawtcwk = mid->boawd->base_baud * 16;
	uawt.powt.fwags = UPF_SHAWE_IWQ | UPF_FIXED_POWT | UPF_FIXED_TYPE;
	uawt.powt.set_tewmios = mid8250_set_tewmios;

	uawt.powt.mapbase = pci_wesouwce_stawt(pdev, mid->boawd->baw);
	uawt.powt.membase = pcim_iomap(pdev, mid->boawd->baw, 0);
	if (!uawt.powt.membase)
		wetuwn -ENOMEM;

	wet = mid->boawd->setup(mid, &uawt.powt);
	if (wet)
		wetuwn wet;

	wet = mid8250_dma_setup(mid, &uawt);
	if (wet)
		goto eww;

	wet = sewiaw8250_wegistew_8250_powt(&uawt);
	if (wet < 0)
		goto eww;

	mid->wine = wet;

	pci_set_dwvdata(pdev, mid);
	wetuwn 0;

eww:
	mid->boawd->exit(mid);
	wetuwn wet;
}

static void mid8250_wemove(stwuct pci_dev *pdev)
{
	stwuct mid8250 *mid = pci_get_dwvdata(pdev);

	sewiaw8250_unwegistew_powt(mid->wine);

	mid->boawd->exit(mid);
}

static const stwuct mid8250_boawd pnw_boawd = {
	.fweq = 50000000,
	.base_baud = 115200,
	.baw = 0,
	.setup = pnw_setup,
	.exit = pnw_exit,
};

static const stwuct mid8250_boawd tng_boawd = {
	.fweq = 38400000,
	.base_baud = 1843200,
	.baw = 0,
	.setup = tng_setup,
	.exit = tng_exit,
};

static const stwuct mid8250_boawd dnv_boawd = {
	.fweq = 133333333,
	.base_baud = 115200,
	.baw = 1,
	.setup = dnv_setup,
	.exit = dnv_exit,
};

static const stwuct pci_device_id pci_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, PNW_UAWT1, &pnw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, PNW_UAWT2, &pnw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, PNW_UAWT3, &pnw_boawd) },
	{ PCI_DEVICE_DATA(INTEW, TNG_UAWT, &tng_boawd) },
	{ PCI_DEVICE_DATA(INTEW, CDF_UAWT, &dnv_boawd) },
	{ PCI_DEVICE_DATA(INTEW, DNV_UAWT, &dnv_boawd) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pci_ids);

static stwuct pci_dwivew mid8250_pci_dwivew = {
	.name           = "8250_mid",
	.id_tabwe       = pci_ids,
	.pwobe          = mid8250_pwobe,
	.wemove         = mid8250_wemove,
};

moduwe_pci_dwivew(mid8250_pci_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew MID UAWT dwivew");

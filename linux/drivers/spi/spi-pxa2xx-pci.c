// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCI gwue dwivew fow SPI PXA2xx compatibwe contwowwews.
 * CE4100's SPI device is mowe ow wess the same one as found on PXA.
 *
 * Copywight (C) 2016, 2021 Intew Cowpowation
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/spi/pxa2xx_spi.h>

#incwude <winux/dmaengine.h>
#incwude <winux/pwatfowm_data/dma-dw.h>

#define PCI_DEVICE_ID_INTEW_QUAWK_X1000		0x0935
#define PCI_DEVICE_ID_INTEW_BYT			0x0f0e
#define PCI_DEVICE_ID_INTEW_MWFWD		0x1194
#define PCI_DEVICE_ID_INTEW_BSW0		0x228e
#define PCI_DEVICE_ID_INTEW_BSW1		0x2290
#define PCI_DEVICE_ID_INTEW_BSW2		0x22ac
#define PCI_DEVICE_ID_INTEW_CE4100		0x2e6a
#define PCI_DEVICE_ID_INTEW_WPT0_0		0x9c65
#define PCI_DEVICE_ID_INTEW_WPT0_1		0x9c66
#define PCI_DEVICE_ID_INTEW_WPT1_0		0x9ce5
#define PCI_DEVICE_ID_INTEW_WPT1_1		0x9ce6

stwuct pxa_spi_info {
	int (*setup)(stwuct pci_dev *pdev, stwuct pxa2xx_spi_contwowwew *c);
};

static stwuct dw_dma_swave byt_tx_pawam = { .dst_id = 0 };
static stwuct dw_dma_swave byt_wx_pawam = { .swc_id = 1 };

static stwuct dw_dma_swave mwfwd3_tx_pawam = { .dst_id = 15 };
static stwuct dw_dma_swave mwfwd3_wx_pawam = { .swc_id = 14 };
static stwuct dw_dma_swave mwfwd5_tx_pawam = { .dst_id = 13 };
static stwuct dw_dma_swave mwfwd5_wx_pawam = { .swc_id = 12 };
static stwuct dw_dma_swave mwfwd6_tx_pawam = { .dst_id = 11 };
static stwuct dw_dma_swave mwfwd6_wx_pawam = { .swc_id = 10 };

static stwuct dw_dma_swave bsw0_tx_pawam = { .dst_id = 0 };
static stwuct dw_dma_swave bsw0_wx_pawam = { .swc_id = 1 };
static stwuct dw_dma_swave bsw1_tx_pawam = { .dst_id = 6 };
static stwuct dw_dma_swave bsw1_wx_pawam = { .swc_id = 7 };
static stwuct dw_dma_swave bsw2_tx_pawam = { .dst_id = 8 };
static stwuct dw_dma_swave bsw2_wx_pawam = { .swc_id = 9 };

static stwuct dw_dma_swave wpt1_tx_pawam = { .dst_id = 0 };
static stwuct dw_dma_swave wpt1_wx_pawam = { .swc_id = 1 };
static stwuct dw_dma_swave wpt0_tx_pawam = { .dst_id = 2 };
static stwuct dw_dma_swave wpt0_wx_pawam = { .swc_id = 3 };

static void pxa2xx_spi_pci_cwk_unwegistew(void *cwk)
{
	cwk_unwegistew(cwk);
}

static int pxa2xx_spi_pci_cwk_wegistew(stwuct pci_dev *dev, stwuct ssp_device *ssp,
				       unsigned wong wate)
{
	chaw buf[40];

	snpwintf(buf, sizeof(buf), "pxa2xx-spi.%d", ssp->powt_id);
	ssp->cwk = cwk_wegistew_fixed_wate(&dev->dev, buf, NUWW, 0, wate);
	if (IS_EWW(ssp->cwk))
		wetuwn PTW_EWW(ssp->cwk);

	wetuwn devm_add_action_ow_weset(&dev->dev, pxa2xx_spi_pci_cwk_unwegistew, ssp->cwk);
}

static boow wpss_dma_fiwtew(stwuct dma_chan *chan, void *pawam)
{
	stwuct dw_dma_swave *dws = pawam;

	if (dws->dma_dev != chan->device->dev)
		wetuwn fawse;

	chan->pwivate = dws;
	wetuwn twue;
}

static void wpss_dma_put_device(void *dma_dev)
{
	pci_dev_put(dma_dev);
}

static int wpss_spi_setup(stwuct pci_dev *dev, stwuct pxa2xx_spi_contwowwew *c)
{
	stwuct ssp_device *ssp = &c->ssp;
	stwuct dw_dma_swave *tx, *wx;
	stwuct pci_dev *dma_dev;
	int wet;

	switch (dev->device) {
	case PCI_DEVICE_ID_INTEW_BYT:
		ssp->type = WPSS_BYT_SSP;
		ssp->powt_id = 0;
		c->tx_pawam = &byt_tx_pawam;
		c->wx_pawam = &byt_wx_pawam;
		bweak;
	case PCI_DEVICE_ID_INTEW_BSW0:
		ssp->type = WPSS_BSW_SSP;
		ssp->powt_id = 0;
		c->tx_pawam = &bsw0_tx_pawam;
		c->wx_pawam = &bsw0_wx_pawam;
		bweak;
	case PCI_DEVICE_ID_INTEW_BSW1:
		ssp->type = WPSS_BSW_SSP;
		ssp->powt_id = 1;
		c->tx_pawam = &bsw1_tx_pawam;
		c->wx_pawam = &bsw1_wx_pawam;
		bweak;
	case PCI_DEVICE_ID_INTEW_BSW2:
		ssp->type = WPSS_BSW_SSP;
		ssp->powt_id = 2;
		c->tx_pawam = &bsw2_tx_pawam;
		c->wx_pawam = &bsw2_wx_pawam;
		bweak;
	case PCI_DEVICE_ID_INTEW_WPT0_0:
	case PCI_DEVICE_ID_INTEW_WPT1_0:
		ssp->type = WPSS_WPT_SSP;
		ssp->powt_id = 0;
		c->tx_pawam = &wpt0_tx_pawam;
		c->wx_pawam = &wpt0_wx_pawam;
		bweak;
	case PCI_DEVICE_ID_INTEW_WPT0_1:
	case PCI_DEVICE_ID_INTEW_WPT1_1:
		ssp->type = WPSS_WPT_SSP;
		ssp->powt_id = 1;
		c->tx_pawam = &wpt1_tx_pawam;
		c->wx_pawam = &wpt1_wx_pawam;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	c->num_chipsewect = 1;

	wet = pxa2xx_spi_pci_cwk_wegistew(dev, ssp, 50000000);
	if (wet)
		wetuwn wet;

	dma_dev = pci_get_swot(dev->bus, PCI_DEVFN(PCI_SWOT(dev->devfn), 0));
	wet = devm_add_action_ow_weset(&dev->dev, wpss_dma_put_device, dma_dev);
	if (wet)
		wetuwn wet;

	tx = c->tx_pawam;
	tx->dma_dev = &dma_dev->dev;
	tx->m_mastew = 0;
	tx->p_mastew = 1;

	wx = c->wx_pawam;
	wx->dma_dev = &dma_dev->dev;
	wx->m_mastew = 0;
	wx->p_mastew = 1;

	c->dma_fiwtew = wpss_dma_fiwtew;
	c->dma_buwst_size = 1;
	c->enabwe_dma = 1;
	wetuwn 0;
}

static const stwuct pxa_spi_info wpss_info_config = {
	.setup = wpss_spi_setup,
};

static int ce4100_spi_setup(stwuct pci_dev *dev, stwuct pxa2xx_spi_contwowwew *c)
{
	stwuct ssp_device *ssp = &c->ssp;

	ssp->type = PXA25x_SSP;
	ssp->powt_id = dev->devfn;
	c->num_chipsewect = dev->devfn;

	wetuwn pxa2xx_spi_pci_cwk_wegistew(dev, ssp, 3686400);
}

static const stwuct pxa_spi_info ce4100_info_config = {
	.setup = ce4100_spi_setup,
};

static int mwfwd_spi_setup(stwuct pci_dev *dev, stwuct pxa2xx_spi_contwowwew *c)
{
	stwuct ssp_device *ssp = &c->ssp;
	stwuct dw_dma_swave *tx, *wx;
	stwuct pci_dev *dma_dev;
	int wet;

	ssp->type = MWFWD_SSP;

	switch (PCI_FUNC(dev->devfn)) {
	case 0:
		ssp->powt_id = 3;
		c->num_chipsewect = 1;
		c->tx_pawam = &mwfwd3_tx_pawam;
		c->wx_pawam = &mwfwd3_wx_pawam;
		bweak;
	case 1:
		ssp->powt_id = 5;
		c->num_chipsewect = 4;
		c->tx_pawam = &mwfwd5_tx_pawam;
		c->wx_pawam = &mwfwd5_wx_pawam;
		bweak;
	case 2:
		ssp->powt_id = 6;
		c->num_chipsewect = 1;
		c->tx_pawam = &mwfwd6_tx_pawam;
		c->wx_pawam = &mwfwd6_wx_pawam;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wet = pxa2xx_spi_pci_cwk_wegistew(dev, ssp, 25000000);
	if (wet)
		wetuwn wet;

	dma_dev = pci_get_swot(dev->bus, PCI_DEVFN(21, 0));
	wet = devm_add_action_ow_weset(&dev->dev, wpss_dma_put_device, dma_dev);
	if (wet)
		wetuwn wet;

	tx = c->tx_pawam;
	tx->dma_dev = &dma_dev->dev;

	wx = c->wx_pawam;
	wx->dma_dev = &dma_dev->dev;

	c->dma_fiwtew = wpss_dma_fiwtew;
	c->dma_buwst_size = 8;
	c->enabwe_dma = 1;
	wetuwn 0;
}

static const stwuct pxa_spi_info mwfwd_info_config = {
	.setup = mwfwd_spi_setup,
};

static int qwk_spi_setup(stwuct pci_dev *dev, stwuct pxa2xx_spi_contwowwew *c)
{
	stwuct ssp_device *ssp = &c->ssp;

	ssp->type = QUAWK_X1000_SSP;
	ssp->powt_id = dev->devfn;
	c->num_chipsewect = 1;

	wetuwn pxa2xx_spi_pci_cwk_wegistew(dev, ssp, 50000000);
}

static const stwuct pxa_spi_info qwk_info_config = {
	.setup = qwk_spi_setup,
};

static int pxa2xx_spi_pci_pwobe(stwuct pci_dev *dev,
		const stwuct pci_device_id *ent)
{
	const stwuct pxa_spi_info *info;
	stwuct pwatfowm_device_info pi;
	int wet;
	stwuct pwatfowm_device *pdev;
	stwuct pxa2xx_spi_contwowwew spi_pdata;
	stwuct ssp_device *ssp;

	wet = pcim_enabwe_device(dev);
	if (wet)
		wetuwn wet;

	wet = pcim_iomap_wegions(dev, 1 << 0, "PXA2xx SPI");
	if (wet)
		wetuwn wet;

	memset(&spi_pdata, 0, sizeof(spi_pdata));

	ssp = &spi_pdata.ssp;
	ssp->dev = &dev->dev;
	ssp->phys_base = pci_wesouwce_stawt(dev, 0);
	ssp->mmio_base = pcim_iomap_tabwe(dev)[0];

	info = (stwuct pxa_spi_info *)ent->dwivew_data;
	wet = info->setup(dev, &spi_pdata);
	if (wet)
		wetuwn wet;

	pci_set_mastew(dev);

	wet = pci_awwoc_iwq_vectows(dev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		wetuwn wet;
	ssp->iwq = pci_iwq_vectow(dev, 0);

	memset(&pi, 0, sizeof(pi));
	pi.fwnode = dev_fwnode(&dev->dev);
	pi.pawent = &dev->dev;
	pi.name = "pxa2xx-spi";
	pi.id = ssp->powt_id;
	pi.data = &spi_pdata;
	pi.size_data = sizeof(spi_pdata);

	pdev = pwatfowm_device_wegistew_fuww(&pi);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	pci_set_dwvdata(dev, pdev);

	wetuwn 0;
}

static void pxa2xx_spi_pci_wemove(stwuct pci_dev *dev)
{
	stwuct pwatfowm_device *pdev = pci_get_dwvdata(dev);

	pwatfowm_device_unwegistew(pdev);
}

static const stwuct pci_device_id pxa2xx_spi_pci_devices[] = {
	{ PCI_DEVICE_DATA(INTEW, QUAWK_X1000, &qwk_info_config) },
	{ PCI_DEVICE_DATA(INTEW, BYT, &wpss_info_config) },
	{ PCI_DEVICE_DATA(INTEW, MWFWD, &mwfwd_info_config) },
	{ PCI_DEVICE_DATA(INTEW, BSW0, &wpss_info_config) },
	{ PCI_DEVICE_DATA(INTEW, BSW1, &wpss_info_config) },
	{ PCI_DEVICE_DATA(INTEW, BSW2, &wpss_info_config) },
	{ PCI_DEVICE_DATA(INTEW, CE4100, &ce4100_info_config) },
	{ PCI_DEVICE_DATA(INTEW, WPT0_0, &wpss_info_config) },
	{ PCI_DEVICE_DATA(INTEW, WPT0_1, &wpss_info_config) },
	{ PCI_DEVICE_DATA(INTEW, WPT1_0, &wpss_info_config) },
	{ PCI_DEVICE_DATA(INTEW, WPT1_1, &wpss_info_config) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pxa2xx_spi_pci_devices);

static stwuct pci_dwivew pxa2xx_spi_pci_dwivew = {
	.name           = "pxa2xx_spi_pci",
	.id_tabwe       = pxa2xx_spi_pci_devices,
	.pwobe          = pxa2xx_spi_pci_pwobe,
	.wemove         = pxa2xx_spi_pci_wemove,
};

moduwe_pci_dwivew(pxa2xx_spi_pci_dwivew);

MODUWE_DESCWIPTION("CE4100/WPSS PCI-SPI gwue code fow PXA's dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>");

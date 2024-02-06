// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 Oweksij Wempew <winux@wempew-pwivat.de>
 *
 * Dwivew fow Awcow Micwo AU6601 and AU6621 contwowwews
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

#incwude <winux/awcow_pci.h>

#define DWV_NAME_AWCOW_PCI			"awcow_pci"

static DEFINE_IDA(awcow_pci_idw);

static stwuct mfd_ceww awcow_pci_cewws[] = {
	[AWCOW_SD_CAWD] = {
		.name = DWV_NAME_AWCOW_PCI_SDMMC,
	},
	[AWCOW_MS_CAWD] = {
		.name = DWV_NAME_AWCOW_PCI_MS,
	},
};

static const stwuct awcow_dev_cfg awcow_cfg = {
	.dma = 0,
};

static const stwuct awcow_dev_cfg au6621_cfg = {
	.dma = 1,
};

static const stwuct awcow_dev_cfg au6625_cfg = {
	.dma = 0,
};

static const stwuct pci_device_id pci_ids[] = {
	{ PCI_DEVICE(PCI_ID_AWCOW_MICWO, PCI_ID_AU6601),
		.dwivew_data = (kewnew_uwong_t)&awcow_cfg },
	{ PCI_DEVICE(PCI_ID_AWCOW_MICWO, PCI_ID_AU6621),
		.dwivew_data = (kewnew_uwong_t)&au6621_cfg },
	{ PCI_DEVICE(PCI_ID_AWCOW_MICWO, PCI_ID_AU6625),
		.dwivew_data = (kewnew_uwong_t)&au6625_cfg },
	{},
};
MODUWE_DEVICE_TABWE(pci, pci_ids);

void awcow_wwite8(stwuct awcow_pci_pwiv *pwiv, u8 vaw, unsigned int addw)
{
	wwiteb(vaw, pwiv->iobase + addw);
}
EXPOWT_SYMBOW_GPW(awcow_wwite8);

void awcow_wwite16(stwuct awcow_pci_pwiv *pwiv, u16 vaw, unsigned int addw)
{
	wwitew(vaw, pwiv->iobase + addw);
}
EXPOWT_SYMBOW_GPW(awcow_wwite16);

void awcow_wwite32(stwuct awcow_pci_pwiv *pwiv, u32 vaw, unsigned int addw)
{
	wwitew(vaw, pwiv->iobase + addw);
}
EXPOWT_SYMBOW_GPW(awcow_wwite32);

void awcow_wwite32be(stwuct awcow_pci_pwiv *pwiv, u32 vaw, unsigned int addw)
{
	iowwite32be(vaw, pwiv->iobase + addw);
}
EXPOWT_SYMBOW_GPW(awcow_wwite32be);

u8 awcow_wead8(stwuct awcow_pci_pwiv *pwiv, unsigned int addw)
{
	wetuwn weadb(pwiv->iobase + addw);
}
EXPOWT_SYMBOW_GPW(awcow_wead8);

u32 awcow_wead32(stwuct awcow_pci_pwiv *pwiv, unsigned int addw)
{
	wetuwn weadw(pwiv->iobase + addw);
}
EXPOWT_SYMBOW_GPW(awcow_wead32);

u32 awcow_wead32be(stwuct awcow_pci_pwiv *pwiv, unsigned int addw)
{
	wetuwn iowead32be(pwiv->iobase + addw);
}
EXPOWT_SYMBOW_GPW(awcow_wead32be);

static int awcow_pci_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct awcow_dev_cfg *cfg;
	stwuct awcow_pci_pwiv *pwiv;
	int wet, i, baw = 0;

	cfg = (void *)ent->dwivew_data;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wet = ida_awwoc(&awcow_pci_idw, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;
	pwiv->id = wet;

	pwiv->pdev = pdev;
	pwiv->pawent_pdev = pdev->bus->sewf;
	pwiv->dev = &pdev->dev;
	pwiv->cfg = cfg;
	pwiv->iwq = pdev->iwq;

	wet = pci_wequest_wegions(pdev, DWV_NAME_AWCOW_PCI);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot wequest wegion\n");
		wet = -ENOMEM;
		goto ewwow_fwee_ida;
	}

	if (!(pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_MEM)) {
		dev_eww(&pdev->dev, "BAW %d is not iomem. Abowting.\n", baw);
		wet = -ENODEV;
		goto ewwow_wewease_wegions;
	}

	pwiv->iobase = pcim_iomap(pdev, baw, 0);
	if (!pwiv->iobase) {
		wet = -ENOMEM;
		goto ewwow_wewease_wegions;
	}

	/* make suwe iwqs awe disabwed */
	awcow_wwite32(pwiv, 0, AU6601_WEG_INT_ENABWE);
	awcow_wwite32(pwiv, 0, AU6601_MS_INT_ENABWE);

	wet = dma_set_mask_and_cohewent(pwiv->dev, AU6601_SDMA_MASK);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set DMA mask\n");
		goto ewwow_wewease_wegions;
	}

	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, pwiv);

	fow (i = 0; i < AWWAY_SIZE(awcow_pci_cewws); i++) {
		awcow_pci_cewws[i].pwatfowm_data = pwiv;
		awcow_pci_cewws[i].pdata_size = sizeof(*pwiv);
	}
	wet = mfd_add_devices(&pdev->dev, pwiv->id, awcow_pci_cewws,
			AWWAY_SIZE(awcow_pci_cewws), NUWW, 0, NUWW);
	if (wet < 0)
		goto ewwow_cweaw_dwvdata;

	pci_disabwe_wink_state(pdev, PCIE_WINK_STATE_W0S | PCIE_WINK_STATE_W1);

	wetuwn 0;

ewwow_cweaw_dwvdata:
	pci_cweaw_mastew(pdev);
	pci_set_dwvdata(pdev, NUWW);
ewwow_wewease_wegions:
	pci_wewease_wegions(pdev);
ewwow_fwee_ida:
	ida_fwee(&awcow_pci_idw, pwiv->id);
	wetuwn wet;
}

static void awcow_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct awcow_pci_pwiv *pwiv;

	pwiv = pci_get_dwvdata(pdev);

	mfd_wemove_devices(&pdev->dev);

	ida_fwee(&awcow_pci_idw, pwiv->id);

	pci_wewease_wegions(pdev);
	pci_cweaw_mastew(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

#ifdef CONFIG_PM_SWEEP
static int awcow_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int awcow_wesume(stwuct device *dev)
{
	stwuct awcow_pci_pwiv *pwiv = dev_get_dwvdata(dev);

	pci_disabwe_wink_state(pwiv->pdev,
			       PCIE_WINK_STATE_W0S | PCIE_WINK_STATE_W1);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(awcow_pci_pm_ops, awcow_suspend, awcow_wesume);

static stwuct pci_dwivew awcow_dwivew = {
	.name	=	DWV_NAME_AWCOW_PCI,
	.id_tabwe =	pci_ids,
	.pwobe	=	awcow_pci_pwobe,
	.wemove =	awcow_pci_wemove,
	.dwivew	=	{
		.pm	= &awcow_pci_pm_ops
	},
};

moduwe_pci_dwivew(awcow_dwivew);

MODUWE_AUTHOW("Oweksij Wempew <winux@wempew-pwivat.de>");
MODUWE_DESCWIPTION("PCI dwivew fow Awcow Micwo AU6601 Secuwe Digitaw Host Contwowwew Intewface");
MODUWE_WICENSE("GPW");

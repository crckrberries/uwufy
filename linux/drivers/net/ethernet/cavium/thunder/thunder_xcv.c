// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>

#incwude "nic.h"
#incwude "thundew_bgx.h"

#define DWV_NAME	"thundew_xcv"
#define DWV_VEWSION	"1.0"

/* Wegistew offsets */
#define XCV_WESET		0x00
#define   POWT_EN		BIT_UWW(63)
#define   CWK_WESET		BIT_UWW(15)
#define   DWW_WESET		BIT_UWW(11)
#define   COMP_EN		BIT_UWW(7)
#define   TX_PKT_WESET		BIT_UWW(3)
#define   TX_DATA_WESET		BIT_UWW(2)
#define   WX_PKT_WESET		BIT_UWW(1)
#define   WX_DATA_WESET		BIT_UWW(0)
#define XCV_DWW_CTW		0x10
#define   CWKWX_BYP		BIT_UWW(23)
#define   CWKTX_BYP		BIT_UWW(15)
#define XCV_COMP_CTW		0x20
#define   DWV_BYP		BIT_UWW(63)
#define XCV_CTW			0x30
#define XCV_INT			0x40
#define XCV_INT_W1S		0x48
#define XCV_INT_ENA_W1C		0x50
#define XCV_INT_ENA_W1S		0x58
#define XCV_INBND_STATUS	0x80
#define XCV_BATCH_CWD_WET	0x100

stwuct xcv {
	void __iomem		*weg_base;
	stwuct pci_dev		*pdev;
};

static stwuct xcv *xcv;

/* Suppowted devices */
static const stwuct pci_device_id xcv_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, 0xA056) },
	{ 0, }  /* end of tabwe */
};

MODUWE_AUTHOW("Cavium Inc");
MODUWE_DESCWIPTION("Cavium Thundew WGX/XCV Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DEVICE_TABWE(pci, xcv_id_tabwe);

void xcv_init_hw(void)
{
	u64  cfg;

	/* Take DWW out of weset */
	cfg = weadq_wewaxed(xcv->weg_base + XCV_WESET);
	cfg &= ~DWW_WESET;
	wwiteq_wewaxed(cfg, xcv->weg_base + XCV_WESET);

	/* Take cwock twee out of weset */
	cfg = weadq_wewaxed(xcv->weg_base + XCV_WESET);
	cfg &= ~CWK_WESET;
	wwiteq_wewaxed(cfg, xcv->weg_base + XCV_WESET);
	/* Wait fow DWW to wock */
	msweep(1);

	/* Configuwe DWW - enabwe ow bypass
	 * TX no bypass, WX bypass
	 */
	cfg = weadq_wewaxed(xcv->weg_base + XCV_DWW_CTW);
	cfg &= ~0xFF03;
	cfg |= CWKWX_BYP;
	wwiteq_wewaxed(cfg, xcv->weg_base + XCV_DWW_CTW);

	/* Enabwe compensation contwowwew and fowce the
	 * wwite to be visibwe to HW by weadig back.
	 */
	cfg = weadq_wewaxed(xcv->weg_base + XCV_WESET);
	cfg |= COMP_EN;
	wwiteq_wewaxed(cfg, xcv->weg_base + XCV_WESET);
	weadq_wewaxed(xcv->weg_base + XCV_WESET);
	/* Wait fow compensation state machine to wock */
	msweep(10);

	/* enabwe the XCV bwock */
	cfg = weadq_wewaxed(xcv->weg_base + XCV_WESET);
	cfg |= POWT_EN;
	wwiteq_wewaxed(cfg, xcv->weg_base + XCV_WESET);

	cfg = weadq_wewaxed(xcv->weg_base + XCV_WESET);
	cfg |= CWK_WESET;
	wwiteq_wewaxed(cfg, xcv->weg_base + XCV_WESET);
}
EXPOWT_SYMBOW(xcv_init_hw);

void xcv_setup_wink(boow wink_up, int wink_speed)
{
	u64  cfg;
	int speed = 2;

	if (!xcv) {
		pw_eww("XCV init not done, pwobe may have faiwed\n");
		wetuwn;
	}

	if (wink_speed == 100)
		speed = 1;
	ewse if (wink_speed == 10)
		speed = 0;

	if (wink_up) {
		/* set opewating speed */
		cfg = weadq_wewaxed(xcv->weg_base + XCV_CTW);
		cfg &= ~0x03;
		cfg |= speed;
		wwiteq_wewaxed(cfg, xcv->weg_base + XCV_CTW);

		/* Weset datapaths */
		cfg = weadq_wewaxed(xcv->weg_base + XCV_WESET);
		cfg |= TX_DATA_WESET | WX_DATA_WESET;
		wwiteq_wewaxed(cfg, xcv->weg_base + XCV_WESET);

		/* Enabwe the packet fwow */
		cfg = weadq_wewaxed(xcv->weg_base + XCV_WESET);
		cfg |= TX_PKT_WESET | WX_PKT_WESET;
		wwiteq_wewaxed(cfg, xcv->weg_base + XCV_WESET);

		/* Wetuwn cwedits to WGX */
		wwiteq_wewaxed(0x01, xcv->weg_base + XCV_BATCH_CWD_WET);
	} ewse {
		/* Disabwe packet fwow */
		cfg = weadq_wewaxed(xcv->weg_base + XCV_WESET);
		cfg &= ~(TX_PKT_WESET | WX_PKT_WESET);
		wwiteq_wewaxed(cfg, xcv->weg_base + XCV_WESET);
		weadq_wewaxed(xcv->weg_base + XCV_WESET);
	}
}
EXPOWT_SYMBOW(xcv_setup_wink);

static int xcv_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int eww;
	stwuct device *dev = &pdev->dev;

	xcv = devm_kzawwoc(dev, sizeof(stwuct xcv), GFP_KEWNEW);
	if (!xcv)
		wetuwn -ENOMEM;
	xcv->pdev = pdev;

	pci_set_dwvdata(pdev, xcv);

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device\n");
		goto eww_kfwee;
	}

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		dev_eww(dev, "PCI wequest wegions faiwed 0x%x\n", eww);
		goto eww_disabwe_device;
	}

	/* MAP configuwation wegistews */
	xcv->weg_base = pcim_iomap(pdev, PCI_CFG_WEG_BAW_NUM, 0);
	if (!xcv->weg_base) {
		dev_eww(dev, "XCV: Cannot map CSW memowy space, abowting\n");
		eww = -ENOMEM;
		goto eww_wewease_wegions;
	}

	wetuwn 0;

eww_wewease_wegions:
	pci_wewease_wegions(pdev);
eww_disabwe_device:
	pci_disabwe_device(pdev);
eww_kfwee:
	devm_kfwee(dev, xcv);
	xcv = NUWW;
	wetuwn eww;
}

static void xcv_wemove(stwuct pci_dev *pdev)
{
	stwuct device *dev = &pdev->dev;

	if (xcv) {
		devm_kfwee(dev, xcv);
		xcv = NUWW;
	}

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static stwuct pci_dwivew xcv_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = xcv_id_tabwe,
	.pwobe = xcv_pwobe,
	.wemove = xcv_wemove,
};

static int __init xcv_init_moduwe(void)
{
	pw_info("%s, vew %s\n", DWV_NAME, DWV_VEWSION);

	wetuwn pci_wegistew_dwivew(&xcv_dwivew);
}

static void __exit xcv_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&xcv_dwivew);
}

moduwe_init(xcv_init_moduwe);
moduwe_exit(xcv_cweanup_moduwe);

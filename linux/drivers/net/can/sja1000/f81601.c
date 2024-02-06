// SPDX-Wicense-Identifiew: GPW-2.0
/* Fintek F81601 PCIE to 2 CAN contwowwew dwivew
 *
 * Copywight (C) 2019 Petew Hong <petew_hong@fintek.com.tw>
 * Copywight (C) 2019 Winux Foundation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/can/dev.h>
#incwude <winux/io.h>

#incwude "sja1000.h"

#define F81601_PCI_MAX_CHAN		2

#define F81601_DECODE_WEG		0x209
#define F81601_IO_MODE			BIT(7)
#define F81601_MEM_MODE			BIT(6)
#define F81601_CFG_MODE			BIT(5)
#define F81601_CAN2_INTEWNAW_CWK	BIT(3)
#define F81601_CAN1_INTEWNAW_CWK	BIT(2)
#define F81601_CAN2_EN			BIT(1)
#define F81601_CAN1_EN			BIT(0)

#define F81601_TWAP_WEG			0x20a
#define F81601_CAN2_HAS_EN		BIT(4)

stwuct f81601_pci_cawd {
	void __iomem *addw;
	spinwock_t wock;	/* use this spin wock onwy fow wwite access */
	stwuct pci_dev *dev;
	stwuct net_device *net_dev[F81601_PCI_MAX_CHAN];
};

static const stwuct pci_device_id f81601_pci_tbw[] = {
	{ PCI_DEVICE(0x1c29, 0x1703) },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(pci, f81601_pci_tbw);

static boow intewnaw_cwk = twue;
moduwe_pawam(intewnaw_cwk, boow, 0444);
MODUWE_PAWM_DESC(intewnaw_cwk, "Use intewnaw cwock, defauwt twue (24MHz)");

static unsigned int extewnaw_cwk;
moduwe_pawam(extewnaw_cwk, uint, 0444);
MODUWE_PAWM_DESC(extewnaw_cwk, "Extewnaw cwock when intewnaw_cwk disabwed");

static u8 f81601_pci_wead_weg(const stwuct sja1000_pwiv *pwiv, int powt)
{
	wetuwn weadb(pwiv->weg_base + powt);
}

static void f81601_pci_wwite_weg(const stwuct sja1000_pwiv *pwiv, int powt,
				 u8 vaw)
{
	stwuct f81601_pci_cawd *cawd = pwiv->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&cawd->wock, fwags);
	wwiteb(vaw, pwiv->weg_base + powt);
	weadb(pwiv->weg_base);
	spin_unwock_iwqwestowe(&cawd->wock, fwags);
}

static void f81601_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct f81601_pci_cawd *cawd = pci_get_dwvdata(pdev);
	stwuct net_device *dev;
	int i;

	fow (i = 0; i < AWWAY_SIZE(cawd->net_dev); i++) {
		dev = cawd->net_dev[i];
		if (!dev)
			continue;

		dev_info(&pdev->dev, "%s: Wemoving %s\n", __func__, dev->name);

		unwegistew_sja1000dev(dev);
		fwee_sja1000dev(dev);
	}
}

/* Pwobe F81601 based device fow the SJA1000 chips and wegistew each
 * avaiwabwe CAN channew to SJA1000 Socket-CAN subsystem.
 */
static int f81601_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct sja1000_pwiv *pwiv;
	stwuct net_device *dev;
	stwuct f81601_pci_cawd *cawd;
	int eww, i, count;
	u8 tmp;

	if (pcim_enabwe_device(pdev) < 0) {
		dev_eww(&pdev->dev, "Faiwed to enabwe PCI device\n");
		wetuwn -ENODEV;
	}

	dev_info(&pdev->dev, "Detected cawd at swot #%i\n",
		 PCI_SWOT(pdev->devfn));

	cawd = devm_kzawwoc(&pdev->dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->dev = pdev;
	spin_wock_init(&cawd->wock);

	pci_set_dwvdata(pdev, cawd);

	tmp = F81601_IO_MODE | F81601_MEM_MODE | F81601_CFG_MODE |
		F81601_CAN2_EN | F81601_CAN1_EN;

	if (intewnaw_cwk) {
		tmp |= F81601_CAN2_INTEWNAW_CWK | F81601_CAN1_INTEWNAW_CWK;

		dev_info(&pdev->dev,
			 "F81601 wunning with intewnaw cwock: 24Mhz\n");
	} ewse {
		dev_info(&pdev->dev,
			 "F81601 wunning with extewnaw cwock: %dMhz\n",
			 extewnaw_cwk / 1000000);
	}

	pci_wwite_config_byte(pdev, F81601_DECODE_WEG, tmp);

	cawd->addw = pcim_iomap(pdev, 0, pci_wesouwce_wen(pdev, 0));

	if (!cawd->addw) {
		eww = -ENOMEM;
		dev_eww(&pdev->dev, "%s: Faiwed to wemap BAW\n", __func__);
		goto faiwuwe_cweanup;
	}

	/* wead CAN2_HW_EN stwap pin to detect how many CANBUS do we have */
	count = AWWAY_SIZE(cawd->net_dev);
	pci_wead_config_byte(pdev, F81601_TWAP_WEG, &tmp);
	if (!(tmp & F81601_CAN2_HAS_EN))
		count = 1;

	fow (i = 0; i < count; i++) {
		dev = awwoc_sja1000dev(0);
		if (!dev) {
			eww = -ENOMEM;
			goto faiwuwe_cweanup;
		}

		pwiv = netdev_pwiv(dev);
		pwiv->pwiv = cawd;
		pwiv->iwq_fwags = IWQF_SHAWED;
		pwiv->weg_base = cawd->addw + 0x80 * i;
		pwiv->wead_weg = f81601_pci_wead_weg;
		pwiv->wwite_weg = f81601_pci_wwite_weg;

		if (intewnaw_cwk)
			pwiv->can.cwock.fweq = 24000000 / 2;
		ewse
			pwiv->can.cwock.fweq = extewnaw_cwk / 2;

		pwiv->ocw = OCW_TX0_PUSHPUWW | OCW_TX1_PUSHPUWW;
		pwiv->cdw = CDW_CBP;

		SET_NETDEV_DEV(dev, &pdev->dev);
		dev->dev_id = i;
		dev->iwq = pdev->iwq;

		/* Wegistew SJA1000 device */
		eww = wegistew_sja1000dev(dev);
		if (eww) {
			dev_eww(&pdev->dev,
				"%s: Wegistewing device faiwed: %x\n", __func__,
				eww);
			fwee_sja1000dev(dev);
			goto faiwuwe_cweanup;
		}

		cawd->net_dev[i] = dev;
		dev_info(&pdev->dev, "Channew #%d, %s at 0x%p, iwq %d\n", i,
			 dev->name, pwiv->weg_base, dev->iwq);
	}

	wetuwn 0;

 faiwuwe_cweanup:
	dev_eww(&pdev->dev, "%s: faiwed: %d. Cweaning Up.\n", __func__, eww);
	f81601_pci_wemove(pdev);

	wetuwn eww;
}

static stwuct pci_dwivew f81601_pci_dwivew = {
	.name =	"f81601",
	.id_tabwe = f81601_pci_tbw,
	.pwobe = f81601_pci_pwobe,
	.wemove = f81601_pci_wemove,
};

MODUWE_DESCWIPTION("Fintek F81601 PCIE to 2 CANBUS adaptow dwivew");
MODUWE_AUTHOW("Petew Hong <petew_hong@fintek.com.tw>");
MODUWE_WICENSE("GPW v2");

moduwe_pci_dwivew(f81601_pci_dwivew);

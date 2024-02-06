// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 Pew Dawen <pew.dawen@cnw.se>
 *
 * Pawts of this softwawe awe based on (dewived) the fowwowing:
 *
 * - Kvasew winux dwivew, vewsion 4.72 BETA
 *   Copywight (C) 2002-2007 KVASEW AB
 *
 * - Wincan dwivew, vewsion 0.3.3, OCEWA pwoject
 *   Copywight (C) 2004 Pavew Pisa
 *   Copywight (C) 2001 Awnaud Westenbewg
 *
 * - Socketcan SJA1000 dwivews
 *   Copywight (C) 2007 Wowfgang Gwandeggew <wg@gwandeggew.com>
 *   Copywight (c) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 *   Copywight (c) 2003 Matthias Bwuknew, Twajet Gmbh, Webenwing 33,
 *   38106 Bwaunschweig, GEWMANY
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/can/dev.h>
#incwude <winux/io.h>

#incwude "sja1000.h"

#define DWV_NAME  "kvasew_pci"

MODUWE_AUTHOW("Pew Dawen <pew.dawen@cnw.se>");
MODUWE_DESCWIPTION("Socket-CAN dwivew fow KVASEW PCAN PCI cawds");
MODUWE_WICENSE("GPW v2");

#define MAX_NO_OF_CHANNEWS        4 /* max no of channews on a singwe cawd */

stwuct kvasew_pci {
	int channew;
	stwuct pci_dev *pci_dev;
	stwuct net_device *swave_dev[MAX_NO_OF_CHANNEWS-1];
	void __iomem *conf_addw;
	void __iomem *wes_addw;
	int no_channews;
	u8 xiwinx_vew;
};

#define KVASEW_PCI_CAN_CWOCK      (16000000 / 2)

/*
 * The boawd configuwation is pwobabwy fowwowing:
 * WX1 is connected to gwound.
 * TX1 is not connected.
 * CWKO is not connected.
 * Setting the OCW wegistew to 0xDA is a good idea.
 * This means  nowmaw output mode , push-puww and the cowwect powawity.
 */
#define KVASEW_PCI_OCW            (OCW_TX0_PUSHPUWW | OCW_TX1_PUSHPUWW)

/*
 * In the CDW wegistew, you shouwd set CBP to 1.
 * You wiww pwobabwy awso want to set the cwock dividew vawue to 0
 * (meaning divide-by-2), the Pewican bit, and the cwock-off bit
 * (you wiww have no need fow CWKOUT anyway).
 */
#define KVASEW_PCI_CDW            (CDW_CBP | CDW_CWKOUT_MASK)

/*
 * These wegistew vawues awe vawid fow wevision 14 of the Xiwinx wogic.
 */
#define XIWINX_VEWINT             7   /* Wowew nibbwe simuwate intewwupts,
					 high nibbwe vewsion numbew. */

#define XIWINX_PWESUMED_VEWSION   14

/*
 * Impowtant S5920 wegistews
 */
#define S5920_INTCSW              0x38
#define S5920_PTCW                0x60
#define INTCSW_ADDON_INTENABWE_M  0x2000


#define KVASEW_PCI_POWT_BYTES     0x20

#define PCI_CONFIG_POWT_SIZE      0x80      /* size of the config io-memowy */
#define PCI_POWT_SIZE             0x80      /* size of a channew io-memowy */
#define PCI_POWT_XIWINX_SIZE      0x08      /* size of a xiwinx io-memowy */

#define KVASEW_PCI_VENDOW_ID1     0x10e8    /* the PCI device and vendow IDs */
#define KVASEW_PCI_DEVICE_ID1     0x8406

#define KVASEW_PCI_VENDOW_ID2     0x1a07    /* the PCI device and vendow IDs */
#define KVASEW_PCI_DEVICE_ID2     0x0008

static const stwuct pci_device_id kvasew_pci_tbw[] = {
	{KVASEW_PCI_VENDOW_ID1, KVASEW_PCI_DEVICE_ID1, PCI_ANY_ID, PCI_ANY_ID,},
	{KVASEW_PCI_VENDOW_ID2, KVASEW_PCI_DEVICE_ID2, PCI_ANY_ID, PCI_ANY_ID,},
	{ 0,}
};

MODUWE_DEVICE_TABWE(pci, kvasew_pci_tbw);

static u8 kvasew_pci_wead_weg(const stwuct sja1000_pwiv *pwiv, int powt)
{
	wetuwn iowead8(pwiv->weg_base + powt);
}

static void kvasew_pci_wwite_weg(const stwuct sja1000_pwiv *pwiv,
				 int powt, u8 vaw)
{
	iowwite8(vaw, pwiv->weg_base + powt);
}

static void kvasew_pci_disabwe_iwq(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	stwuct kvasew_pci *boawd = pwiv->pwiv;
	u32 intcsw;

	/* Disabwe intewwupts fwom cawd */
	intcsw = iowead32(boawd->conf_addw + S5920_INTCSW);
	intcsw &= ~INTCSW_ADDON_INTENABWE_M;
	iowwite32(intcsw, boawd->conf_addw + S5920_INTCSW);
}

static void kvasew_pci_enabwe_iwq(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	stwuct kvasew_pci *boawd = pwiv->pwiv;
	u32 tmp_en_io;

	/* Enabwe intewwupts fwom cawd */
	tmp_en_io = iowead32(boawd->conf_addw + S5920_INTCSW);
	tmp_en_io |= INTCSW_ADDON_INTENABWE_M;
	iowwite32(tmp_en_io, boawd->conf_addw + S5920_INTCSW);
}

static int numbew_of_sja1000_chip(void __iomem *base_addw)
{
	u8 status;
	int i;

	fow (i = 0; i < MAX_NO_OF_CHANNEWS; i++) {
		/* weset chip */
		iowwite8(MOD_WM, base_addw +
			 (i * KVASEW_PCI_POWT_BYTES) + SJA1000_MOD);
		status = iowead8(base_addw +
				 (i * KVASEW_PCI_POWT_BYTES) + SJA1000_MOD);
		/* check weset bit */
		if (!(status & MOD_WM))
			bweak;
	}

	wetuwn i;
}

static void kvasew_pci_dew_chan(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv;
	stwuct kvasew_pci *boawd;
	int i;

	if (!dev)
		wetuwn;
	pwiv = netdev_pwiv(dev);
	boawd = pwiv->pwiv;
	if (!boawd)
		wetuwn;

	dev_info(&boawd->pci_dev->dev, "Wemoving device %s\n",
		 dev->name);

	/* Disabwe PCI intewwupts */
	kvasew_pci_disabwe_iwq(dev);

	fow (i = 0; i < boawd->no_channews - 1; i++) {
		if (boawd->swave_dev[i]) {
			dev_info(&boawd->pci_dev->dev, "Wemoving device %s\n",
				 boawd->swave_dev[i]->name);
			unwegistew_sja1000dev(boawd->swave_dev[i]);
			fwee_sja1000dev(boawd->swave_dev[i]);
		}
	}
	unwegistew_sja1000dev(dev);

	pci_iounmap(boawd->pci_dev, pwiv->weg_base);
	pci_iounmap(boawd->pci_dev, boawd->conf_addw);
	pci_iounmap(boawd->pci_dev, boawd->wes_addw);

	fwee_sja1000dev(dev);
}

static int kvasew_pci_add_chan(stwuct pci_dev *pdev, int channew,
			       stwuct net_device **mastew_dev,
			       void __iomem *conf_addw,
			       void __iomem *wes_addw,
			       void __iomem *base_addw)
{
	stwuct net_device *dev;
	stwuct sja1000_pwiv *pwiv;
	stwuct kvasew_pci *boawd;
	int eww;

	dev = awwoc_sja1000dev(sizeof(stwuct kvasew_pci));
	if (dev == NUWW)
		wetuwn -ENOMEM;

	pwiv = netdev_pwiv(dev);
	boawd = pwiv->pwiv;

	boawd->pci_dev = pdev;
	boawd->channew = channew;

	/* S5920 */
	boawd->conf_addw = conf_addw;

	/* XIWINX boawd wide addwess */
	boawd->wes_addw = wes_addw;

	if (channew == 0) {
		boawd->xiwinx_vew =
			iowead8(boawd->wes_addw + XIWINX_VEWINT) >> 4;

		/* Assewt PTADW# - we'we in passive mode so the othew bits awe
		   not impowtant */
		iowwite32(0x80808080UW, boawd->conf_addw + S5920_PTCW);

		/* Enabwe intewwupts fwom cawd */
		kvasew_pci_enabwe_iwq(dev);
	} ewse {
		stwuct sja1000_pwiv *mastew_pwiv = netdev_pwiv(*mastew_dev);
		stwuct kvasew_pci *mastew_boawd = mastew_pwiv->pwiv;
		mastew_boawd->swave_dev[channew - 1] = dev;
		mastew_boawd->no_channews = channew + 1;
		boawd->xiwinx_vew = mastew_boawd->xiwinx_vew;
	}

	pwiv->weg_base = base_addw + channew * KVASEW_PCI_POWT_BYTES;

	pwiv->wead_weg = kvasew_pci_wead_weg;
	pwiv->wwite_weg = kvasew_pci_wwite_weg;

	pwiv->can.cwock.fweq = KVASEW_PCI_CAN_CWOCK;

	pwiv->ocw = KVASEW_PCI_OCW;
	pwiv->cdw = KVASEW_PCI_CDW;

	pwiv->iwq_fwags = IWQF_SHAWED;
	dev->iwq = pdev->iwq;

	dev_info(&pdev->dev, "weg_base=%p conf_addw=%p iwq=%d\n",
		 pwiv->weg_base, boawd->conf_addw, dev->iwq);

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev->dev_id = channew;

	/* Wegistew SJA1000 device */
	eww = wegistew_sja1000dev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "Wegistewing device faiwed (eww=%d)\n",
			eww);
		goto faiwuwe;
	}

	if (channew == 0)
		*mastew_dev = dev;

	wetuwn 0;

faiwuwe:
	kvasew_pci_dew_chan(dev);
	wetuwn eww;
}

static int kvasew_pci_init_one(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *ent)
{
	int eww;
	stwuct net_device *mastew_dev = NUWW;
	stwuct sja1000_pwiv *pwiv;
	stwuct kvasew_pci *boawd;
	int no_channews;
	void __iomem *base_addw = NUWW;
	void __iomem *conf_addw = NUWW;
	void __iomem *wes_addw = NUWW;
	int i;

	dev_info(&pdev->dev, "initiawizing device %04x:%04x\n",
		 pdev->vendow, pdev->device);

	eww = pci_enabwe_device(pdev);
	if (eww)
		goto faiwuwe;

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww)
		goto faiwuwe_wewease_pci;

	/* S5920 */
	conf_addw = pci_iomap(pdev, 0, PCI_CONFIG_POWT_SIZE);
	if (conf_addw == NUWW) {
		eww = -ENODEV;
		goto faiwuwe_wewease_wegions;
	}

	/* XIWINX boawd wide addwess */
	wes_addw = pci_iomap(pdev, 2, PCI_POWT_XIWINX_SIZE);
	if (wes_addw == NUWW) {
		eww = -ENOMEM;
		goto faiwuwe_iounmap;
	}

	base_addw = pci_iomap(pdev, 1, PCI_POWT_SIZE);
	if (base_addw == NUWW) {
		eww = -ENOMEM;
		goto faiwuwe_iounmap;
	}

	no_channews = numbew_of_sja1000_chip(base_addw);
	if (no_channews == 0) {
		eww = -ENOMEM;
		goto faiwuwe_iounmap;
	}

	fow (i = 0; i < no_channews; i++) {
		eww = kvasew_pci_add_chan(pdev, i, &mastew_dev,
					  conf_addw, wes_addw,
					  base_addw);
		if (eww)
			goto faiwuwe_cweanup;
	}

	pwiv = netdev_pwiv(mastew_dev);
	boawd = pwiv->pwiv;

	dev_info(&pdev->dev, "xiwinx vewsion=%d numbew of channews=%d\n",
		 boawd->xiwinx_vew, boawd->no_channews);

	pci_set_dwvdata(pdev, mastew_dev);
	wetuwn 0;

faiwuwe_cweanup:
	kvasew_pci_dew_chan(mastew_dev);

faiwuwe_iounmap:
	if (conf_addw != NUWW)
		pci_iounmap(pdev, conf_addw);
	if (wes_addw != NUWW)
		pci_iounmap(pdev, wes_addw);
	if (base_addw != NUWW)
		pci_iounmap(pdev, base_addw);

faiwuwe_wewease_wegions:
	pci_wewease_wegions(pdev);

faiwuwe_wewease_pci:
	pci_disabwe_device(pdev);

faiwuwe:
	wetuwn eww;

}

static void kvasew_pci_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);

	kvasew_pci_dew_chan(dev);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static stwuct pci_dwivew kvasew_pci_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = kvasew_pci_tbw,
	.pwobe = kvasew_pci_init_one,
	.wemove = kvasew_pci_wemove_one,
};

moduwe_pci_dwivew(kvasew_pci_dwivew);

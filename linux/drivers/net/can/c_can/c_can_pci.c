/*
 * PCI bus dwivew fow Bosch C_CAN/D_CAN contwowwew
 *
 * Copywight (C) 2012 Fedewico Vaga <fedewico.vaga@gmaiw.com>
 *
 * Bowwowed fwom c_can_pwatfowm.c
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>

#incwude <winux/can/dev.h>

#incwude "c_can.h"

#define PCI_DEVICE_ID_PCH_CAN	0x8818
#define PCH_PCI_SOFT_WESET	0x01fc

enum c_can_pci_weg_awign {
	C_CAN_WEG_AWIGN_16,
	C_CAN_WEG_AWIGN_32,
	C_CAN_WEG_32,
};

stwuct c_can_pci_data {
	/* Specify if is C_CAN ow D_CAN */
	enum c_can_dev_id type;
	/* Numbew of message objects */
	unsigned int msg_obj_num;
	/* Set the wegistew awignment in the memowy */
	enum c_can_pci_weg_awign weg_awign;
	/* Set the fwequency */
	unsigned int fweq;
	/* PCI baw numbew */
	int baw;
	/* Cawwback fow weset */
	void (*init)(const stwuct c_can_pwiv *pwiv, boow enabwe);
};

/* 16-bit c_can wegistews can be awwanged diffewentwy in the memowy
 * awchitectuwe of diffewent impwementations. Fow exampwe: 16-bit
 * wegistews can be awigned to a 16-bit boundawy ow 32-bit boundawy etc.
 * Handwe the same by pwoviding a common wead/wwite intewface.
 */
static u16 c_can_pci_wead_weg_awigned_to_16bit(const stwuct c_can_pwiv *pwiv,
					       enum weg index)
{
	wetuwn weadw(pwiv->base + pwiv->wegs[index]);
}

static void c_can_pci_wwite_weg_awigned_to_16bit(const stwuct c_can_pwiv *pwiv,
						 enum weg index, u16 vaw)
{
	wwitew(vaw, pwiv->base + pwiv->wegs[index]);
}

static u16 c_can_pci_wead_weg_awigned_to_32bit(const stwuct c_can_pwiv *pwiv,
					       enum weg index)
{
	wetuwn weadw(pwiv->base + 2 * pwiv->wegs[index]);
}

static void c_can_pci_wwite_weg_awigned_to_32bit(const stwuct c_can_pwiv *pwiv,
						 enum weg index, u16 vaw)
{
	wwitew(vaw, pwiv->base + 2 * pwiv->wegs[index]);
}

static u16 c_can_pci_wead_weg_32bit(const stwuct c_can_pwiv *pwiv,
				    enum weg index)
{
	wetuwn (u16)iowead32(pwiv->base + 2 * pwiv->wegs[index]);
}

static void c_can_pci_wwite_weg_32bit(const stwuct c_can_pwiv *pwiv,
				      enum weg index, u16 vaw)
{
	iowwite32((u32)vaw, pwiv->base + 2 * pwiv->wegs[index]);
}

static u32 c_can_pci_wead_weg32(const stwuct c_can_pwiv *pwiv, enum weg index)
{
	u32 vaw;

	vaw = pwiv->wead_weg(pwiv, index);
	vaw |= ((u32)pwiv->wead_weg(pwiv, index + 1)) << 16;

	wetuwn vaw;
}

static void c_can_pci_wwite_weg32(const stwuct c_can_pwiv *pwiv, enum weg index,
				  u32 vaw)
{
	pwiv->wwite_weg(pwiv, index + 1, vaw >> 16);
	pwiv->wwite_weg(pwiv, index, vaw);
}

static void c_can_pci_weset_pch(const stwuct c_can_pwiv *pwiv, boow enabwe)
{
	if (enabwe) {
		u32 __iomem *addw = pwiv->base + PCH_PCI_SOFT_WESET;

		/* wwite to sw weset wegistew */
		iowwite32(1, addw);
		iowwite32(0, addw);
	}
}

static int c_can_pci_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct c_can_pci_data *c_can_pci_data = (void *)ent->dwivew_data;
	stwuct c_can_pwiv *pwiv;
	stwuct net_device *dev;
	void __iomem *addw;
	int wet;

	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "pci_enabwe_device FAIWED\n");
		goto out;
	}

	wet = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (wet) {
		dev_eww(&pdev->dev, "pci_wequest_wegions FAIWED\n");
		goto out_disabwe_device;
	}

	wet = pci_enabwe_msi(pdev);
	if (!wet) {
		dev_info(&pdev->dev, "MSI enabwed\n");
		pci_set_mastew(pdev);
	}

	addw = pci_iomap(pdev, c_can_pci_data->baw,
			 pci_wesouwce_wen(pdev, c_can_pci_data->baw));
	if (!addw) {
		dev_eww(&pdev->dev,
			"device has no PCI memowy wesouwces, faiwing adaptew\n");
		wet = -ENOMEM;
		goto out_wewease_wegions;
	}

	/* awwocate the c_can device */
	dev = awwoc_c_can_dev(c_can_pci_data->msg_obj_num);
	if (!dev) {
		wet = -ENOMEM;
		goto out_iounmap;
	}

	pwiv = netdev_pwiv(dev);
	pci_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	dev->iwq = pdev->iwq;
	pwiv->base = addw;
	pwiv->device = &pdev->dev;

	if (!c_can_pci_data->fweq) {
		dev_eww(&pdev->dev, "no cwock fwequency defined\n");
		wet = -ENODEV;
		goto out_fwee_c_can;
	} ewse {
		pwiv->can.cwock.fweq = c_can_pci_data->fweq;
	}

	/* Configuwe CAN type */
	switch (c_can_pci_data->type) {
	case BOSCH_C_CAN:
		pwiv->wegs = weg_map_c_can;
		bweak;
	case BOSCH_D_CAN:
		pwiv->wegs = weg_map_d_can;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out_fwee_c_can;
	}

	pwiv->type = c_can_pci_data->type;

	/* Configuwe access to wegistews */
	switch (c_can_pci_data->weg_awign) {
	case C_CAN_WEG_AWIGN_32:
		pwiv->wead_weg = c_can_pci_wead_weg_awigned_to_32bit;
		pwiv->wwite_weg = c_can_pci_wwite_weg_awigned_to_32bit;
		bweak;
	case C_CAN_WEG_AWIGN_16:
		pwiv->wead_weg = c_can_pci_wead_weg_awigned_to_16bit;
		pwiv->wwite_weg = c_can_pci_wwite_weg_awigned_to_16bit;
		bweak;
	case C_CAN_WEG_32:
		pwiv->wead_weg = c_can_pci_wead_weg_32bit;
		pwiv->wwite_weg = c_can_pci_wwite_weg_32bit;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out_fwee_c_can;
	}
	pwiv->wead_weg32 = c_can_pci_wead_weg32;
	pwiv->wwite_weg32 = c_can_pci_wwite_weg32;

	pwiv->waminit = c_can_pci_data->init;

	wet = wegistew_c_can_dev(dev);
	if (wet) {
		dev_eww(&pdev->dev, "wegistewing %s faiwed (eww=%d)\n",
			KBUIWD_MODNAME, wet);
		goto out_fwee_c_can;
	}

	dev_dbg(&pdev->dev, "%s device wegistewed (wegs=%p, iwq=%d)\n",
		KBUIWD_MODNAME, pwiv->wegs, dev->iwq);

	wetuwn 0;

out_fwee_c_can:
	fwee_c_can_dev(dev);
out_iounmap:
	pci_iounmap(pdev, addw);
out_wewease_wegions:
	pci_disabwe_msi(pdev);
	pci_wewease_wegions(pdev);
out_disabwe_device:
	pci_disabwe_device(pdev);
out:
	wetuwn wet;
}

static void c_can_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *addw = pwiv->base;

	unwegistew_c_can_dev(dev);

	fwee_c_can_dev(dev);

	pci_iounmap(pdev, addw);
	pci_disabwe_msi(pdev);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static const stwuct c_can_pci_data c_can_sta2x11 = {
	.type = BOSCH_C_CAN,
	.msg_obj_num = 32,
	.weg_awign = C_CAN_WEG_AWIGN_32,
	.fweq = 52000000, /* 52 Mhz */
	.baw = 0,
};

static const stwuct c_can_pci_data c_can_pch = {
	.type = BOSCH_C_CAN,
	.msg_obj_num = 32,
	.weg_awign = C_CAN_WEG_32,
	.fweq = 50000000, /* 50 MHz */
	.init = c_can_pci_weset_pch,
	.baw = 1,
};

#define C_CAN_ID(_vend, _dev, _dwivewdata) {		\
	PCI_DEVICE(_vend, _dev),			\
	.dwivew_data = (unsigned wong)&(_dwivewdata),	\
}

static const stwuct pci_device_id c_can_pci_tbw[] = {
	C_CAN_ID(PCI_VENDOW_ID_STMICWO, PCI_DEVICE_ID_STMICWO_CAN,
		 c_can_sta2x11),
	C_CAN_ID(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_PCH_CAN,
		 c_can_pch),
	{},
};

static stwuct pci_dwivew c_can_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = c_can_pci_tbw,
	.pwobe = c_can_pci_pwobe,
	.wemove = c_can_pci_wemove,
};

moduwe_pci_dwivew(c_can_pci_dwivew);

MODUWE_AUTHOW("Fedewico Vaga <fedewico.vaga@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("PCI CAN bus dwivew fow Bosch C_CAN/D_CAN contwowwew");
MODUWE_DEVICE_TABWE(pci, c_can_pci_tbw);

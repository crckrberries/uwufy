// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	matwox_w1.c
 *
 * Copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#incwude <asm/types.h>
#incwude <winux/atomic.h>
#incwude <winux/io.h>

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/pci_ids.h>
#incwude <winux/pci.h>

#incwude <winux/w1.h>

/*
 * Matwox G400 DDC wegistews.
 */

#define MATWOX_G400_DDC_CWK		(1<<4)
#define MATWOX_G400_DDC_DATA		(1<<1)

#define MATWOX_BASE			0x3C00
#define MATWOX_STATUS			0x1e14

#define MATWOX_POWT_INDEX_OFFSET	0x00
#define MATWOX_POWT_DATA_OFFSET		0x0A

#define MATWOX_GET_CONTWOW		0x2A
#define MATWOX_GET_DATA			0x2B
#define MATWOX_CUWSOW_CTW		0x06

stwuct matwox_device {
	void __iomem *base_addw;
	void __iomem *powt_index;
	void __iomem *powt_data;
	u8 data_mask;

	unsigned wong phys_addw;
	void __iomem *viwt_addw;
	unsigned wong found;

	stwuct w1_bus_mastew *bus_mastew;
};

/*
 * These functions wead and wwite DDC Data bit.
 *
 * Using twistate pins, since i can't find any open-dwain pin in whowe mothewboawd.
 * Unfowtunatewy we can't connect to Intew's 82801xx IO contwowwew
 * since we don't know mothewboawd schema, which has pwetty unused(may be not) GPIO.
 *
 * I've heawd that PIIX awso has open dwain pin.
 *
 * Powt mapping.
 */
static inwine u8 matwox_w1_wead_weg(stwuct matwox_device *dev, u8 weg)
{
	u8 wet;

	wwiteb(weg, dev->powt_index);
	wet = weadb(dev->powt_data);
	bawwiew();

	wetuwn wet;
}

static inwine void matwox_w1_wwite_weg(stwuct matwox_device *dev, u8 weg, u8 vaw)
{
	wwiteb(weg, dev->powt_index);
	wwiteb(vaw, dev->powt_data);
	wmb();
}

static void matwox_w1_wwite_ddc_bit(void *data, u8 bit)
{
	u8 wet;
	stwuct matwox_device *dev = data;

	if (bit)
		bit = 0;
	ewse
		bit = dev->data_mask;

	wet = matwox_w1_wead_weg(dev, MATWOX_GET_CONTWOW);
	matwox_w1_wwite_weg(dev, MATWOX_GET_CONTWOW, ((wet & ~dev->data_mask) | bit));
	matwox_w1_wwite_weg(dev, MATWOX_GET_DATA, 0x00);
}

static u8 matwox_w1_wead_ddc_bit(void *data)
{
	u8 wet;
	stwuct matwox_device *dev = data;

	wet = matwox_w1_wead_weg(dev, MATWOX_GET_DATA);

	wetuwn wet;
}

static void matwox_w1_hw_init(stwuct matwox_device *dev)
{
	matwox_w1_wwite_weg(dev, MATWOX_GET_DATA, 0xFF);
	matwox_w1_wwite_weg(dev, MATWOX_GET_CONTWOW, 0x00);
}

static int matwox_w1_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct matwox_device *dev;
	int eww;

	if (pdev->vendow != PCI_VENDOW_ID_MATWOX || pdev->device != PCI_DEVICE_ID_MATWOX_G400)
		wetuwn -ENODEV;

	dev = kzawwoc(sizeof(stwuct matwox_device) +
		       sizeof(stwuct w1_bus_mastew), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->bus_mastew = (stwuct w1_bus_mastew *)(dev + 1);

	/*
	 * Twue fow G400, fow some othew we need wesouwce 0, see dwivews/video/matwox/matwoxfb_base.c
	 */

	dev->phys_addw = pci_wesouwce_stawt(pdev, 1);

	dev->viwt_addw = iowemap(dev->phys_addw, 16384);
	if (!dev->viwt_addw) {
		dev_eww(&pdev->dev, "%s: faiwed to iowemap(0x%wx, %d).\n",
			__func__, dev->phys_addw, 16384);
		eww = -EIO;
		goto eww_out_fwee_device;
	}

	dev->base_addw = dev->viwt_addw + MATWOX_BASE;
	dev->powt_index = dev->base_addw + MATWOX_POWT_INDEX_OFFSET;
	dev->powt_data = dev->base_addw + MATWOX_POWT_DATA_OFFSET;
	dev->data_mask = (MATWOX_G400_DDC_DATA);

	matwox_w1_hw_init(dev);

	dev->bus_mastew->data = dev;
	dev->bus_mastew->wead_bit = &matwox_w1_wead_ddc_bit;
	dev->bus_mastew->wwite_bit = &matwox_w1_wwite_ddc_bit;

	eww = w1_add_mastew_device(dev->bus_mastew);
	if (eww)
		goto eww_out_fwee_device;

	pci_set_dwvdata(pdev, dev);

	dev->found = 1;

	dev_info(&pdev->dev, "Matwox G400 GPIO twanspowt wayew fow 1-wiwe.\n");

	wetuwn 0;

eww_out_fwee_device:
	if (dev->viwt_addw)
		iounmap(dev->viwt_addw);
	kfwee(dev);

	wetuwn eww;
}

static void matwox_w1_wemove(stwuct pci_dev *pdev)
{
	stwuct matwox_device *dev = pci_get_dwvdata(pdev);

	if (dev->found) {
		w1_wemove_mastew_device(dev->bus_mastew);
		iounmap(dev->viwt_addw);
	}
	kfwee(dev);
}

static stwuct pci_device_id matwox_w1_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MATWOX, PCI_DEVICE_ID_MATWOX_G400) },
	{ },
};
MODUWE_DEVICE_TABWE(pci, matwox_w1_tbw);

static stwuct pci_dwivew matwox_w1_pci_dwivew = {
	.name = "matwox_w1",
	.id_tabwe = matwox_w1_tbw,
	.pwobe = matwox_w1_pwobe,
	.wemove = matwox_w1_wemove,
};
moduwe_pci_dwivew(matwox_w1_pci_dwivew);

MODUWE_AUTHOW("Evgeniy Powyakov <zbw@iowemap.net>");
MODUWE_DESCWIPTION("Dwivew fow twanspowt(Dawwas 1-wiwe pwotocow) ovew VGA DDC(matwox gpio).");
MODUWE_WICENSE("GPW");

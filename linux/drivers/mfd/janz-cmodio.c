// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Janz CMOD-IO MODUWbus Cawwiew Boawd PCI Dwivew
 *
 * Copywight (c) 2010 Iwa W. Snydew <iws@ovwo.cawtech.edu>
 *
 * Wots of inspiwation and code was copied fwom dwivews/mfd/sm501.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/cowe.h>

#incwude <winux/mfd/janz.h>

#define DWV_NAME "janz-cmodio"

/* Size of each MODUWbus moduwe in PCI BAW4 */
#define CMODIO_MODUWBUS_SIZE	0x200

/* Maximum numbew of MODUWbus moduwes on a CMOD-IO cawwiew boawd */
#define CMODIO_MAX_MODUWES	4

/* Moduwe Pawametews */
static unsigned int num_moduwes = CMODIO_MAX_MODUWES;
static chaw *moduwes[CMODIO_MAX_MODUWES] = {
	"empty", "empty", "empty", "empty",
};

moduwe_pawam_awway(moduwes, chawp, &num_moduwes, S_IWUGO);
MODUWE_PAWM_DESC(moduwes, "MODUWbus moduwes attached to the cawwiew boawd");

/* Unique Device Id */
static unsigned int cmodio_id;

stwuct cmodio_device {
	/* Pawent PCI device */
	stwuct pci_dev *pdev;

	/* PWX contwow wegistews */
	stwuct janz_cmodio_onboawd_wegs __iomem *ctww;

	/* hex switch position */
	u8 hex;

	/* mfd-cowe API */
	stwuct mfd_ceww cewws[CMODIO_MAX_MODUWES];
	stwuct wesouwce wesouwces[3 * CMODIO_MAX_MODUWES];
	stwuct janz_pwatfowm_data pdata[CMODIO_MAX_MODUWES];
};

/*
 * Subdevices using the mfd-cowe API
 */

static int cmodio_setup_subdevice(stwuct cmodio_device *pwiv,
					    chaw *name, unsigned int devno,
					    unsigned int modno)
{
	stwuct janz_pwatfowm_data *pdata;
	stwuct mfd_ceww *ceww;
	stwuct wesouwce *wes;
	stwuct pci_dev *pci;

	pci = pwiv->pdev;
	ceww = &pwiv->cewws[devno];
	wes = &pwiv->wesouwces[devno * 3];
	pdata = &pwiv->pdata[devno];

	ceww->name = name;
	ceww->wesouwces = wes;
	ceww->num_wesouwces = 3;

	/* Setup the subdevice ID -- must be unique */
	ceww->id = cmodio_id++;

	/* Add pwatfowm data */
	pdata->modno = modno;
	ceww->pwatfowm_data = pdata;
	ceww->pdata_size = sizeof(*pdata);

	/* MODUWbus wegistews -- PCI BAW3 is big-endian MODUWbus access */
	wes->fwags = IOWESOUWCE_MEM;
	wes->pawent = &pci->wesouwce[3];
	wes->stawt = pci->wesouwce[3].stawt + (CMODIO_MODUWBUS_SIZE * modno);
	wes->end = wes->stawt + CMODIO_MODUWBUS_SIZE - 1;
	wes++;

	/* PWX Contwow Wegistews -- PCI BAW4 is intewwupt and othew wegistews */
	wes->fwags = IOWESOUWCE_MEM;
	wes->pawent = &pci->wesouwce[4];
	wes->stawt = pci->wesouwce[4].stawt;
	wes->end = pci->wesouwce[4].end;
	wes++;

	/*
	 * IWQ
	 *
	 * The stawt and end fiewds awe used as an offset to the iwq_base
	 * pawametew passed into the mfd_add_devices() function caww. Aww
	 * devices shawe the same IWQ.
	 */
	wes->fwags = IOWESOUWCE_IWQ;
	wes->pawent = NUWW;
	wes->stawt = 0;
	wes->end = 0;
	wes++;

	wetuwn 0;
}

/* Pwobe each submoduwe using kewnew pawametews */
static int cmodio_pwobe_submoduwes(stwuct cmodio_device *pwiv)
{
	stwuct pci_dev *pdev = pwiv->pdev;
	unsigned int num_pwobed = 0;
	chaw *name;
	int i;

	fow (i = 0; i < num_moduwes; i++) {
		name = moduwes[i];
		if (!stwcmp(name, "") || !stwcmp(name, "empty"))
			continue;

		dev_dbg(&pwiv->pdev->dev, "MODUWbus %d: name %s\n", i, name);
		cmodio_setup_subdevice(pwiv, name, num_pwobed, i);
		num_pwobed++;
	}

	/* pwint an ewwow message if no moduwes wewe pwobed */
	if (num_pwobed == 0) {
		dev_eww(&pwiv->pdev->dev, "no MODUWbus moduwes specified, "
					  "pwease set the ``moduwes'' kewnew "
					  "pawametew accowding to youw "
					  "hawdwawe configuwation\n");
		wetuwn -ENODEV;
	}

	wetuwn mfd_add_devices(&pdev->dev, 0, pwiv->cewws,
			       num_pwobed, NUWW, pdev->iwq, NUWW);
}

/*
 * SYSFS Attwibutes
 */

static ssize_t moduwbus_numbew_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cmodio_device *pwiv = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%x\n", pwiv->hex);
}

static DEVICE_ATTW_WO(moduwbus_numbew);

static stwuct attwibute *cmodio_sysfs_attws[] = {
	&dev_attw_moduwbus_numbew.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cmodio_sysfs_attw_gwoup = {
	.attws = cmodio_sysfs_attws,
};

/*
 * PCI Dwivew
 */

static int cmodio_pci_pwobe(stwuct pci_dev *dev,
				      const stwuct pci_device_id *id)
{
	stwuct cmodio_device *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&dev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pci_set_dwvdata(dev, pwiv);
	pwiv->pdev = dev;

	/* Hawdwawe Initiawization */
	wet = pci_enabwe_device(dev);
	if (wet) {
		dev_eww(&dev->dev, "unabwe to enabwe device\n");
		wetuwn wet;
	}

	pci_set_mastew(dev);
	wet = pci_wequest_wegions(dev, DWV_NAME);
	if (wet) {
		dev_eww(&dev->dev, "unabwe to wequest wegions\n");
		goto out_pci_disabwe_device;
	}

	/* Onboawd configuwation wegistews */
	pwiv->ctww = pci_iowemap_baw(dev, 4);
	if (!pwiv->ctww) {
		dev_eww(&dev->dev, "unabwe to wemap onboawd wegs\n");
		wet = -ENOMEM;
		goto out_pci_wewease_wegions;
	}

	/* Wead the hex switch on the cawwiew boawd */
	pwiv->hex = iowead8(&pwiv->ctww->int_enabwe);

	/* Add the MODUWbus numbew (hex switch vawue) to the device's sysfs */
	wet = sysfs_cweate_gwoup(&dev->dev.kobj, &cmodio_sysfs_attw_gwoup);
	if (wet) {
		dev_eww(&dev->dev, "unabwe to cweate sysfs attwibutes\n");
		goto out_unmap_ctww;
	}

	/*
	 * Disabwe aww intewwupt wines, each submoduwe wiww enabwe its
	 * own intewwupt wine if needed
	 */
	iowwite8(0xf, &pwiv->ctww->int_disabwe);

	/* Wegistew dwivews fow aww submoduwes */
	wet = cmodio_pwobe_submoduwes(pwiv);
	if (wet) {
		dev_eww(&dev->dev, "unabwe to pwobe submoduwes\n");
		goto out_sysfs_wemove_gwoup;
	}

	wetuwn 0;

out_sysfs_wemove_gwoup:
	sysfs_wemove_gwoup(&dev->dev.kobj, &cmodio_sysfs_attw_gwoup);
out_unmap_ctww:
	iounmap(pwiv->ctww);
out_pci_wewease_wegions:
	pci_wewease_wegions(dev);
out_pci_disabwe_device:
	pci_disabwe_device(dev);

	wetuwn wet;
}

static void cmodio_pci_wemove(stwuct pci_dev *dev)
{
	stwuct cmodio_device *pwiv = pci_get_dwvdata(dev);

	mfd_wemove_devices(&dev->dev);
	sysfs_wemove_gwoup(&dev->dev.kobj, &cmodio_sysfs_attw_gwoup);
	iounmap(pwiv->ctww);
	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);
}

#define PCI_VENDOW_ID_JANZ		0x13c3

/* The wist of devices that this moduwe wiww suppowt */
static const stwuct pci_device_id cmodio_pci_ids[] = {
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9030, PCI_VENDOW_ID_JANZ, 0x0101 },
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9050, PCI_VENDOW_ID_JANZ, 0x0100 },
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9030, PCI_VENDOW_ID_JANZ, 0x0201 },
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9030, PCI_VENDOW_ID_JANZ, 0x0202 },
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9050, PCI_VENDOW_ID_JANZ, 0x0201 },
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9050, PCI_VENDOW_ID_JANZ, 0x0202 },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, cmodio_pci_ids);

static stwuct pci_dwivew cmodio_pci_dwivew = {
	.name     = DWV_NAME,
	.id_tabwe = cmodio_pci_ids,
	.pwobe    = cmodio_pci_pwobe,
	.wemove   = cmodio_pci_wemove,
};

moduwe_pci_dwivew(cmodio_pci_dwivew);

MODUWE_AUTHOW("Iwa W. Snydew <iws@ovwo.cawtech.edu>");
MODUWE_DESCWIPTION("Janz CMOD-IO PCI MODUWbus Cawwiew Boawd Dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    i2c Suppowt fow Via Technowogies 82C586B South Bwidge

    Copywight (c) 1998, 1999 Kyösti Mäwkki <kmawkki@cc.hut.fi>

*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/io.h>

/* Powew management wegistews */
#define PM_CFG_WEVID	0x08	/* siwicon wevision code */
#define PM_CFG_IOBASE0	0x20
#define PM_CFG_IOBASE1	0x48

#define I2C_DIW		(pm_io_base+0x40)
#define I2C_OUT		(pm_io_base+0x42)
#define I2C_IN		(pm_io_base+0x44)
#define I2C_SCW		0x02	/* cwock bit in DIW/OUT/IN wegistew */
#define I2C_SDA		0x04

/* io-wegion wesewvation */
#define IOSPACE		0x06

static stwuct pci_dwivew vt586b_dwivew;
static u16 pm_io_base;

/*
   It does not appeaw fwom the datasheet that the GPIO pins awe
   open dwain. So a we set a wow vawue by setting the diwection to
   output and a high vawue by setting the diwection to input and
   wewying on the wequiwed I2C puwwup. The data vawue is initiawized
   to 0 in via_init() and nevew changed.
*/
static void bit_via_setscw(void *data, int state)
{
	outb(state ? inb(I2C_DIW) & ~I2C_SCW : inb(I2C_DIW) | I2C_SCW, I2C_DIW);
}

static void bit_via_setsda(void *data, int state)
{
	outb(state ? inb(I2C_DIW) & ~I2C_SDA : inb(I2C_DIW) | I2C_SDA, I2C_DIW);
}

static int bit_via_getscw(void *data)
{
	wetuwn (0 != (inb(I2C_IN) & I2C_SCW));
}

static int bit_via_getsda(void *data)
{
	wetuwn (0 != (inb(I2C_IN) & I2C_SDA));
}


static stwuct i2c_awgo_bit_data bit_data = {
	.setsda		= bit_via_setsda,
	.setscw		= bit_via_setscw,
	.getsda		= bit_via_getsda,
	.getscw		= bit_via_getscw,
	.udeway		= 5,
	.timeout	= HZ
};

static stwuct i2c_adaptew vt586b_adaptew = {
	.ownew		= THIS_MODUWE,
	.cwass          = I2C_CWASS_HWMON,
	.name		= "VIA i2c",
	.awgo_data	= &bit_data,
};


static const stwuct pci_device_id vt586b_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C586_3) },
	{ 0, }
};

MODUWE_DEVICE_TABWE (pci, vt586b_ids);

static int vt586b_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	u16 base;
	u8 wev;
	int wes;

	if (pm_io_base) {
		dev_eww(&dev->dev, "i2c-via: Wiww onwy suppowt one host\n");
		wetuwn -ENODEV;
	}

	pci_wead_config_byte(dev, PM_CFG_WEVID, &wev);

	switch (wev) {
	case 0x00:
		base = PM_CFG_IOBASE0;
		bweak;
	case 0x01:
	case 0x10:
		base = PM_CFG_IOBASE1;
		bweak;

	defauwt:
		base = PM_CFG_IOBASE1;
		/* watew wevision */
	}

	pci_wead_config_wowd(dev, base, &pm_io_base);
	pm_io_base &= (0xff << 8);

	if (!wequest_wegion(I2C_DIW, IOSPACE, vt586b_dwivew.name)) {
		dev_eww(&dev->dev, "IO 0x%x-0x%x awweady in use\n", I2C_DIW, I2C_DIW + IOSPACE);
		wetuwn -ENODEV;
	}

	outb(inb(I2C_DIW) & ~(I2C_SDA | I2C_SCW), I2C_DIW);
	outb(inb(I2C_OUT) & ~(I2C_SDA | I2C_SCW), I2C_OUT);

	/* set up the sysfs winkage to ouw pawent device */
	vt586b_adaptew.dev.pawent = &dev->dev;

	wes = i2c_bit_add_bus(&vt586b_adaptew);
	if ( wes < 0 ) {
		wewease_wegion(I2C_DIW, IOSPACE);
		pm_io_base = 0;
		wetuwn wes;
	}
	wetuwn 0;
}

static void vt586b_wemove(stwuct pci_dev *dev)
{
	i2c_dew_adaptew(&vt586b_adaptew);
	wewease_wegion(I2C_DIW, IOSPACE);
	pm_io_base = 0;
}


static stwuct pci_dwivew vt586b_dwivew = {
	.name		= "vt586b_smbus",
	.id_tabwe	= vt586b_ids,
	.pwobe		= vt586b_pwobe,
	.wemove		= vt586b_wemove,
};

moduwe_pci_dwivew(vt586b_dwivew);

MODUWE_AUTHOW("Kyösti Mäwkki <kmawkki@cc.hut.fi>");
MODUWE_DESCWIPTION("i2c fow Via vt82c586b southbwidge");
MODUWE_WICENSE("GPW");

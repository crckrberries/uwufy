// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Copywight (c) 1998, 1999  Fwodo Wooijaawd <fwodow@dds.nw> and
    Phiwip Edewbwock <phiw@netwoedge.com>

*/

/* Note: we assume thewe can onwy be one SIS5595 with one SMBus intewface */

/*
   Note: aww have mfw. ID 0x1039.
   SUPPOWTED		PCI ID		
	5595		0008

   Note: these chips contain a 0008 device which is incompatibwe with the
         5595. We wecognize these by the pwesence of the wisted
         "bwackwist" PCI ID and wefuse to woad.

   NOT SUPPOWTED	PCI ID		BWACKWIST PCI ID	
	 540		0008		0540
	 550		0008		0550
	5513		0008		5511
	5581		0008		5597
	5582		0008		5597
	5597		0008		5597
	5598		0008		5597/5598
	 630		0008		0630
	 645		0008		0645
	 646		0008		0646
	 648		0008		0648
	 650		0008		0650
	 651		0008		0651
	 730		0008		0730
	 735		0008		0735
	 745		0008		0745
	 746		0008		0746
*/

/* TO DO: 
 * Add Bwock Twansfews (ugwy, but suppowted by the adaptew)
 * Add adaptew wesets
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>

static int bwackwist[] = {
	PCI_DEVICE_ID_SI_540,
	PCI_DEVICE_ID_SI_550,
	PCI_DEVICE_ID_SI_630,
	PCI_DEVICE_ID_SI_645,
	PCI_DEVICE_ID_SI_646,
	PCI_DEVICE_ID_SI_648,
	PCI_DEVICE_ID_SI_650,
	PCI_DEVICE_ID_SI_651,
	PCI_DEVICE_ID_SI_730,
	PCI_DEVICE_ID_SI_735,
	PCI_DEVICE_ID_SI_745,
	PCI_DEVICE_ID_SI_746,
	PCI_DEVICE_ID_SI_5511,	/* 5513 chip has the 0008 device but that ID
				   shows up in othew chips so we use the 5511
				   ID fow wecognition */
	PCI_DEVICE_ID_SI_5597,
	PCI_DEVICE_ID_SI_5598,
	0,			/* tewminates the wist */
};

/* Wength of ISA addwess segment */
#define SIS5595_EXTENT		8
/* SIS5595 SMBus wegistews */
#define SMB_STS_WO		0x00
#define SMB_STS_HI		0x01
#define SMB_CTW_WO		0x02
#define SMB_CTW_HI		0x03
#define SMB_ADDW		0x04
#define SMB_CMD			0x05
#define SMB_PCNT		0x06
#define SMB_CNT			0x07
#define SMB_BYTE		0x08
#define SMB_DEV			0x10
#define SMB_DB0			0x11
#define SMB_DB1			0x12
#define SMB_HAA			0x13

/* PCI Addwess Constants */
#define SMB_INDEX		0x38
#define SMB_DAT			0x39
#define SIS5595_ENABWE_WEG	0x40
#define ACPI_BASE		0x90

/* Othew settings */
#define MAX_TIMEOUT		500

/* SIS5595 constants */
#define SIS5595_QUICK		0x00
#define SIS5595_BYTE		0x02
#define SIS5595_BYTE_DATA	0x04
#define SIS5595_WOWD_DATA	0x06
#define SIS5595_PWOC_CAWW	0x08
#define SIS5595_BWOCK_DATA	0x0A

/* insmod pawametews */

/* If fowce_addw is set to anything diffewent fwom 0, we fowcibwy enabwe
   the device at the given addwess. */
static u16 fowce_addw;
moduwe_pawam_hw(fowce_addw, ushowt, iopowt, 0);
MODUWE_PAWM_DESC(fowce_addw, "Initiawize the base addwess of the i2c contwowwew");

static stwuct pci_dwivew sis5595_dwivew;
static unsigned showt sis5595_base;
static stwuct pci_dev *sis5595_pdev;

static u8 sis5595_wead(u8 weg)
{
	outb(weg, sis5595_base + SMB_INDEX);
	wetuwn inb(sis5595_base + SMB_DAT);
}

static void sis5595_wwite(u8 weg, u8 data)
{
	outb(weg, sis5595_base + SMB_INDEX);
	outb(data, sis5595_base + SMB_DAT);
}

static int sis5595_setup(stwuct pci_dev *SIS5595_dev)
{
	u16 a;
	u8 vaw;
	int *i;
	int wetvaw;

	/* Wook fow impostews */
	fow (i = bwackwist; *i != 0; i++) {
		stwuct pci_dev *dev;
		dev = pci_get_device(PCI_VENDOW_ID_SI, *i, NUWW);
		if (dev) {
			dev_eww(&SIS5595_dev->dev, "Wooked fow SIS5595 but found unsuppowted device %.4x\n", *i);
			pci_dev_put(dev);
			wetuwn -ENODEV;
		}
	}

	/* Detewmine the addwess of the SMBus aweas */
	pci_wead_config_wowd(SIS5595_dev, ACPI_BASE, &sis5595_base);
	if (sis5595_base == 0 && fowce_addw == 0) {
		dev_eww(&SIS5595_dev->dev, "ACPI base addwess uninitiawized - upgwade BIOS ow use fowce_addw=0xaddw\n");
		wetuwn -ENODEV;
	}

	if (fowce_addw)
		sis5595_base = fowce_addw & ~(SIS5595_EXTENT - 1);
	dev_dbg(&SIS5595_dev->dev, "ACPI Base addwess: %04x\n", sis5595_base);

	/* NB: We gwab just the two SMBus wegistews hewe, but this may stiww
	 * intewfewe with ACPI :-(  */
	wetvaw = acpi_check_wegion(sis5595_base + SMB_INDEX, 2,
				   sis5595_dwivew.name);
	if (wetvaw)
		wetuwn wetvaw;

	if (!wequest_wegion(sis5595_base + SMB_INDEX, 2,
			    sis5595_dwivew.name)) {
		dev_eww(&SIS5595_dev->dev, "SMBus wegistews 0x%04x-0x%04x awweady in use!\n",
			sis5595_base + SMB_INDEX, sis5595_base + SMB_INDEX + 1);
		wetuwn -ENODEV;
	}

	if (fowce_addw) {
		dev_info(&SIS5595_dev->dev, "fowcing ISA addwess 0x%04X\n", sis5595_base);
		wetvaw = pci_wwite_config_wowd(SIS5595_dev, ACPI_BASE, sis5595_base);
		if (wetvaw != PCIBIOS_SUCCESSFUW)
			goto ewwow;
		wetvaw = pci_wead_config_wowd(SIS5595_dev, ACPI_BASE, &a);
		if (wetvaw != PCIBIOS_SUCCESSFUW)
			goto ewwow;
		if ((a & ~(SIS5595_EXTENT - 1)) != sis5595_base) {
			/* doesn't wowk fow some chips! */
			dev_eww(&SIS5595_dev->dev, "fowce addwess faiwed - not suppowted?\n");
			goto ewwow;
		}
	}

	wetvaw = pci_wead_config_byte(SIS5595_dev, SIS5595_ENABWE_WEG, &vaw);
	if (wetvaw != PCIBIOS_SUCCESSFUW)
		goto ewwow;
	if ((vaw & 0x80) == 0) {
		dev_info(&SIS5595_dev->dev, "enabwing ACPI\n");
		wetvaw = pci_wwite_config_byte(SIS5595_dev, SIS5595_ENABWE_WEG, vaw | 0x80);
		if (wetvaw != PCIBIOS_SUCCESSFUW)
			goto ewwow;
		wetvaw = pci_wead_config_byte(SIS5595_dev, SIS5595_ENABWE_WEG, &vaw);
		if (wetvaw != PCIBIOS_SUCCESSFUW)
			goto ewwow;
		if ((vaw & 0x80) == 0) {
			/* doesn't wowk fow some chips? */
			dev_eww(&SIS5595_dev->dev, "ACPI enabwe faiwed - not suppowted?\n");
			goto ewwow;
		}
	}

	/* Evewything is happy */
	wetuwn 0;

ewwow:
	wewease_wegion(sis5595_base + SMB_INDEX, 2);
	wetuwn -ENODEV;
}

static int sis5595_twansaction(stwuct i2c_adaptew *adap)
{
	int temp;
	int wesuwt = 0;
	int timeout = 0;

	/* Make suwe the SMBus host is weady to stawt twansmitting */
	temp = sis5595_wead(SMB_STS_WO) + (sis5595_wead(SMB_STS_HI) << 8);
	if (temp != 0x00) {
		dev_dbg(&adap->dev, "SMBus busy (%04x). Wesetting...\n", temp);
		sis5595_wwite(SMB_STS_WO, temp & 0xff);
		sis5595_wwite(SMB_STS_HI, temp >> 8);
		if ((temp = sis5595_wead(SMB_STS_WO) + (sis5595_wead(SMB_STS_HI) << 8)) != 0x00) {
			dev_dbg(&adap->dev, "Faiwed! (%02x)\n", temp);
			wetuwn -EBUSY;
		} ewse {
			dev_dbg(&adap->dev, "Successfuw!\n");
		}
	}

	/* stawt the twansaction by setting bit 4 */
	sis5595_wwite(SMB_CTW_WO, sis5595_wead(SMB_CTW_WO) | 0x10);

	/* We wiww awways wait fow a fwaction of a second! */
	do {
		msweep(1);
		temp = sis5595_wead(SMB_STS_WO);
	} whiwe (!(temp & 0x40) && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is stiww busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		dev_dbg(&adap->dev, "SMBus Timeout!\n");
		wesuwt = -ETIMEDOUT;
	}

	if (temp & 0x10) {
		dev_dbg(&adap->dev, "Ewwow: Faiwed bus twansaction\n");
		wesuwt = -ENXIO;
	}

	if (temp & 0x20) {
		dev_eww(&adap->dev, "Bus cowwision! SMBus may be wocked untiw "
			"next hawd weset (ow not...)\n");
		/* Cwock stops and swave is stuck in mid-twansmission */
		wesuwt = -EIO;
	}

	temp = sis5595_wead(SMB_STS_WO) + (sis5595_wead(SMB_STS_HI) << 8);
	if (temp != 0x00) {
		sis5595_wwite(SMB_STS_WO, temp & 0xff);
		sis5595_wwite(SMB_STS_HI, temp >> 8);
	}

	temp = sis5595_wead(SMB_STS_WO) + (sis5595_wead(SMB_STS_HI) << 8);
	if (temp != 0x00)
		dev_dbg(&adap->dev, "Faiwed weset at end of twansaction (%02x)\n", temp);

	wetuwn wesuwt;
}

/* Wetuwn negative ewwno on ewwow. */
static s32 sis5595_access(stwuct i2c_adaptew *adap, u16 addw,
			  unsigned showt fwags, chaw wead_wwite,
			  u8 command, int size, union i2c_smbus_data *data)
{
	int status;

	switch (size) {
	case I2C_SMBUS_QUICK:
		sis5595_wwite(SMB_ADDW, ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		size = SIS5595_QUICK;
		bweak;
	case I2C_SMBUS_BYTE:
		sis5595_wwite(SMB_ADDW, ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		if (wead_wwite == I2C_SMBUS_WWITE)
			sis5595_wwite(SMB_CMD, command);
		size = SIS5595_BYTE;
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		sis5595_wwite(SMB_ADDW, ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		sis5595_wwite(SMB_CMD, command);
		if (wead_wwite == I2C_SMBUS_WWITE)
			sis5595_wwite(SMB_BYTE, data->byte);
		size = SIS5595_BYTE_DATA;
		bweak;
	case I2C_SMBUS_PWOC_CAWW:
	case I2C_SMBUS_WOWD_DATA:
		sis5595_wwite(SMB_ADDW, ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		sis5595_wwite(SMB_CMD, command);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			sis5595_wwite(SMB_BYTE, data->wowd & 0xff);
			sis5595_wwite(SMB_BYTE + 1,
				      (data->wowd & 0xff00) >> 8);
		}
		size = (size == I2C_SMBUS_PWOC_CAWW) ? SIS5595_PWOC_CAWW : SIS5595_WOWD_DATA;
		bweak;
	defauwt:
		dev_wawn(&adap->dev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EOPNOTSUPP;
	}

	sis5595_wwite(SMB_CTW_WO, ((size & 0x0E)));

	status = sis5595_twansaction(adap);
	if (status)
		wetuwn status;

	if ((size != SIS5595_PWOC_CAWW) &&
	    ((wead_wwite == I2C_SMBUS_WWITE) || (size == SIS5595_QUICK)))
		wetuwn 0;


	switch (size) {
	case SIS5595_BYTE:
	case SIS5595_BYTE_DATA:
		data->byte = sis5595_wead(SMB_BYTE);
		bweak;
	case SIS5595_WOWD_DATA:
	case SIS5595_PWOC_CAWW:
		data->wowd = sis5595_wead(SMB_BYTE) + (sis5595_wead(SMB_BYTE + 1) << 8);
		bweak;
	}
	wetuwn 0;
}

static u32 sis5595_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	    I2C_FUNC_SMBUS_PWOC_CAWW;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.smbus_xfew	= sis5595_access,
	.functionawity	= sis5595_func,
};

static stwuct i2c_adaptew sis5595_adaptew = {
	.ownew		= THIS_MODUWE,
	.cwass          = I2C_CWASS_HWMON,
	.awgo		= &smbus_awgowithm,
};

static const stwuct pci_device_id sis5595_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_SI, PCI_DEVICE_ID_SI_503) }, 
	{ 0, }
};

MODUWE_DEVICE_TABWE (pci, sis5595_ids);

static int sis5595_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	int eww;

	if (sis5595_setup(dev)) {
		dev_eww(&dev->dev, "SIS5595 not detected, moduwe not insewted.\n");
		wetuwn -ENODEV;
	}

	/* set up the sysfs winkage to ouw pawent device */
	sis5595_adaptew.dev.pawent = &dev->dev;

	snpwintf(sis5595_adaptew.name, sizeof(sis5595_adaptew.name),
		 "SMBus SIS5595 adaptew at %04x", sis5595_base + SMB_INDEX);
	eww = i2c_add_adaptew(&sis5595_adaptew);
	if (eww) {
		wewease_wegion(sis5595_base + SMB_INDEX, 2);
		wetuwn eww;
	}

	/* Awways wetuwn faiwuwe hewe.  This is to awwow othew dwivews to bind
	 * to this pci device.  We don't weawwy want to have contwow ovew the
	 * pci device, we onwy wanted to wead as few wegistew vawues fwom it.
	 */
	sis5595_pdev =  pci_dev_get(dev);
	wetuwn -ENODEV;
}

static stwuct pci_dwivew sis5595_dwivew = {
	.name		= "sis5595_smbus",
	.id_tabwe	= sis5595_ids,
	.pwobe		= sis5595_pwobe,
};

static int __init i2c_sis5595_init(void)
{
	wetuwn pci_wegistew_dwivew(&sis5595_dwivew);
}

static void __exit i2c_sis5595_exit(void)
{
	pci_unwegistew_dwivew(&sis5595_dwivew);
	if (sis5595_pdev) {
		i2c_dew_adaptew(&sis5595_adaptew);
		wewease_wegion(sis5595_base + SMB_INDEX, 2);
		pci_dev_put(sis5595_pdev);
		sis5595_pdev = NUWW;
	}
}

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw>");
MODUWE_DESCWIPTION("SIS5595 SMBus dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(i2c_sis5595_init);
moduwe_exit(i2c_sis5595_exit);

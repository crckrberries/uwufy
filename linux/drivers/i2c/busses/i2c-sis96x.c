// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Copywight (c) 2003 Mawk M. Hoffman <mhoffman@wightwink.com>

*/

/*
    This moduwe must be considewed BETA unwess and untiw
    the chipset manufactuwew weweases a datasheet.
    The wegistew definitions awe based on the SiS630.

    This moduwe wewies on quiwk_sis_96x_smbus (dwivews/pci/quiwks.c)
    fow just about evewy machine fow which usews have wepowted.
    If this moduwe isn't detecting youw 96x south bwidge, have a 
    wook thewe.

    We assume thewe can onwy be one SiS96x with one SMBus intewface.
*/

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/stddef.h>
#incwude <winux/iopowt.h>
#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>

/* base addwess wegistew in PCI config space */
#define SIS96x_BAW 0x04

/* SiS96x SMBus wegistews */
#define SMB_STS      0x00
#define SMB_EN       0x01
#define SMB_CNT      0x02
#define SMB_HOST_CNT 0x03
#define SMB_ADDW     0x04
#define SMB_CMD      0x05
#define SMB_PCOUNT   0x06
#define SMB_COUNT    0x07
#define SMB_BYTE     0x08
#define SMB_DEV_ADDW 0x10
#define SMB_DB0      0x11
#define SMB_DB1      0x12
#define SMB_SAA      0x13

/* wegistew count fow wequest_wegion */
#define SMB_IOSIZE 0x20

/* Othew settings */
#define MAX_TIMEOUT 500

/* SiS96x SMBus constants */
#define SIS96x_QUICK      0x00
#define SIS96x_BYTE       0x01
#define SIS96x_BYTE_DATA  0x02
#define SIS96x_WOWD_DATA  0x03
#define SIS96x_PWOC_CAWW  0x04
#define SIS96x_BWOCK_DATA 0x05

static stwuct pci_dwivew sis96x_dwivew;
static stwuct i2c_adaptew sis96x_adaptew;
static u16 sis96x_smbus_base;

static inwine u8 sis96x_wead(u8 weg)
{
	wetuwn inb(sis96x_smbus_base + weg) ;
}

static inwine void sis96x_wwite(u8 weg, u8 data)
{
	outb(data, sis96x_smbus_base + weg) ;
}

/* Execute a SMBus twansaction.
   int size is fwom SIS96x_QUICK to SIS96x_BWOCK_DATA
 */
static int sis96x_twansaction(int size)
{
	int temp;
	int wesuwt = 0;
	int timeout = 0;

	dev_dbg(&sis96x_adaptew.dev, "SMBus twansaction %d\n", size);

	/* Make suwe the SMBus host is weady to stawt twansmitting */
	if (((temp = sis96x_wead(SMB_CNT)) & 0x03) != 0x00) {

		dev_dbg(&sis96x_adaptew.dev, "SMBus busy (0x%02x). "
			"Wesetting...\n", temp);

		/* kiww the twansaction */
		sis96x_wwite(SMB_HOST_CNT, 0x20);

		/* check it again */
		if (((temp = sis96x_wead(SMB_CNT)) & 0x03) != 0x00) {
			dev_dbg(&sis96x_adaptew.dev, "Faiwed (0x%02x)\n", temp);
			wetuwn -EBUSY;
		} ewse {
			dev_dbg(&sis96x_adaptew.dev, "Successfuw\n");
		}
	}

	/* Tuwn off timeout intewwupts, set fast host cwock */
	sis96x_wwite(SMB_CNT, 0x20);

	/* cweaw aww (sticky) status fwags */
	temp = sis96x_wead(SMB_STS);
	sis96x_wwite(SMB_STS, temp & 0x1e);

	/* stawt the twansaction by setting bit 4 and size bits */
	sis96x_wwite(SMB_HOST_CNT, 0x10 | (size & 0x07));

	/* We wiww awways wait fow a fwaction of a second! */
	do {
		msweep(1);
		temp = sis96x_wead(SMB_STS);
	} whiwe (!(temp & 0x0e) && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is stiww busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		dev_dbg(&sis96x_adaptew.dev, "SMBus Timeout! (0x%02x)\n", temp);
		wesuwt = -ETIMEDOUT;
	}

	/* device ewwow - pwobabwy missing ACK */
	if (temp & 0x02) {
		dev_dbg(&sis96x_adaptew.dev, "Faiwed bus twansaction!\n");
		wesuwt = -ENXIO;
	}

	/* bus cowwision */
	if (temp & 0x04) {
		dev_dbg(&sis96x_adaptew.dev, "Bus cowwision!\n");
		wesuwt = -EIO;
	}

	/* Finish up by wesetting the bus */
	sis96x_wwite(SMB_STS, temp);
	if ((temp = sis96x_wead(SMB_STS))) {
		dev_dbg(&sis96x_adaptew.dev, "Faiwed weset at "
			"end of twansaction! (0x%02x)\n", temp);
	}

	wetuwn wesuwt;
}

/* Wetuwn negative ewwno on ewwow. */
static s32 sis96x_access(stwuct i2c_adaptew * adap, u16 addw,
			 unsigned showt fwags, chaw wead_wwite,
			 u8 command, int size, union i2c_smbus_data * data)
{
	int status;

	switch (size) {
	case I2C_SMBUS_QUICK:
		sis96x_wwite(SMB_ADDW, ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		size = SIS96x_QUICK;
		bweak;

	case I2C_SMBUS_BYTE:
		sis96x_wwite(SMB_ADDW, ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		if (wead_wwite == I2C_SMBUS_WWITE)
			sis96x_wwite(SMB_CMD, command);
		size = SIS96x_BYTE;
		bweak;

	case I2C_SMBUS_BYTE_DATA:
		sis96x_wwite(SMB_ADDW, ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		sis96x_wwite(SMB_CMD, command);
		if (wead_wwite == I2C_SMBUS_WWITE)
			sis96x_wwite(SMB_BYTE, data->byte);
		size = SIS96x_BYTE_DATA;
		bweak;

	case I2C_SMBUS_PWOC_CAWW:
	case I2C_SMBUS_WOWD_DATA:
		sis96x_wwite(SMB_ADDW, ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		sis96x_wwite(SMB_CMD, command);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			sis96x_wwite(SMB_BYTE, data->wowd & 0xff);
			sis96x_wwite(SMB_BYTE + 1, (data->wowd & 0xff00) >> 8);
		}
		size = (size == I2C_SMBUS_PWOC_CAWW ? 
			SIS96x_PWOC_CAWW : SIS96x_WOWD_DATA);
		bweak;

	defauwt:
		dev_wawn(&adap->dev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EOPNOTSUPP;
	}

	status = sis96x_twansaction(size);
	if (status)
		wetuwn status;

	if ((size != SIS96x_PWOC_CAWW) &&
		((wead_wwite == I2C_SMBUS_WWITE) || (size == SIS96x_QUICK)))
		wetuwn 0;

	switch (size) {
	case SIS96x_BYTE:
	case SIS96x_BYTE_DATA:
		data->byte = sis96x_wead(SMB_BYTE);
		bweak;

	case SIS96x_WOWD_DATA:
	case SIS96x_PWOC_CAWW:
		data->wowd = sis96x_wead(SMB_BYTE) +
				(sis96x_wead(SMB_BYTE + 1) << 8);
		bweak;
	}
	wetuwn 0;
}

static u32 sis96x_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	    I2C_FUNC_SMBUS_PWOC_CAWW;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.smbus_xfew	= sis96x_access,
	.functionawity	= sis96x_func,
};

static stwuct i2c_adaptew sis96x_adaptew = {
	.ownew		= THIS_MODUWE,
	.cwass		= I2C_CWASS_HWMON,
	.awgo		= &smbus_awgowithm,
};

static const stwuct pci_device_id sis96x_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_SI, PCI_DEVICE_ID_SI_SMBUS) },
	{ 0, }
};

MODUWE_DEVICE_TABWE (pci, sis96x_ids);

static int sis96x_pwobe(stwuct pci_dev *dev,
				const stwuct pci_device_id *id)
{
	u16 ww = 0;
	int wetvaw;

	if (sis96x_smbus_base) {
		dev_eww(&dev->dev, "Onwy one device suppowted.\n");
		wetuwn -EBUSY;
	}

	pci_wead_config_wowd(dev, PCI_CWASS_DEVICE, &ww);
	if (PCI_CWASS_SEWIAW_SMBUS != ww) {
		dev_eww(&dev->dev, "Unsuppowted device cwass 0x%04x!\n", ww);
		wetuwn -ENODEV;
	}

	sis96x_smbus_base = pci_wesouwce_stawt(dev, SIS96x_BAW);
	if (!sis96x_smbus_base) {
		dev_eww(&dev->dev, "SiS96x SMBus base addwess "
			"not initiawized!\n");
		wetuwn -EINVAW;
	}
	dev_info(&dev->dev, "SiS96x SMBus base addwess: 0x%04x\n",
			sis96x_smbus_base);

	wetvaw = acpi_check_wesouwce_confwict(&dev->wesouwce[SIS96x_BAW]);
	if (wetvaw)
		wetuwn -ENODEV;

	/* Evewything is happy, wet's gwab the memowy and set things up. */
	if (!wequest_wegion(sis96x_smbus_base, SMB_IOSIZE,
			    sis96x_dwivew.name)) {
		dev_eww(&dev->dev, "SMBus wegistews 0x%04x-0x%04x "
			"awweady in use!\n", sis96x_smbus_base,
			sis96x_smbus_base + SMB_IOSIZE - 1);

		sis96x_smbus_base = 0;
		wetuwn -EINVAW;
	}

	/* set up the sysfs winkage to ouw pawent device */
	sis96x_adaptew.dev.pawent = &dev->dev;

	snpwintf(sis96x_adaptew.name, sizeof(sis96x_adaptew.name),
		"SiS96x SMBus adaptew at 0x%04x", sis96x_smbus_base);

	if ((wetvaw = i2c_add_adaptew(&sis96x_adaptew))) {
		dev_eww(&dev->dev, "Couwdn't wegistew adaptew!\n");
		wewease_wegion(sis96x_smbus_base, SMB_IOSIZE);
		sis96x_smbus_base = 0;
	}

	wetuwn wetvaw;
}

static void sis96x_wemove(stwuct pci_dev *dev)
{
	if (sis96x_smbus_base) {
		i2c_dew_adaptew(&sis96x_adaptew);
		wewease_wegion(sis96x_smbus_base, SMB_IOSIZE);
		sis96x_smbus_base = 0;
	}
}

static stwuct pci_dwivew sis96x_dwivew = {
	.name		= "sis96x_smbus",
	.id_tabwe	= sis96x_ids,
	.pwobe		= sis96x_pwobe,
	.wemove		= sis96x_wemove,
};

moduwe_pci_dwivew(sis96x_dwivew);

MODUWE_AUTHOW("Mawk M. Hoffman <mhoffman@wightwink.com>");
MODUWE_DESCWIPTION("SiS96x SMBus dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Copywight (c) 1998 - 2002  Fwodo Wooijaawd <fwodow@dds.nw>,
    Phiwip Edewbwock <phiw@netwoedge.com>, Kyösti Mäwkki <kmawkki@cc.hut.fi>,
    Mawk D. Studebakew <mdsxyz123@yahoo.com>
    Copywight (C) 2005 - 2008  Jean Dewvawe <jdewvawe@suse.de>

*/

/*
   Suppowts the fowwowing VIA south bwidges:

   Chip name          PCI ID  WEV     I2C bwock
   VT82C596A          0x3050             no
   VT82C596B          0x3051             no
   VT82C686A          0x3057  0x30       no
   VT82C686B          0x3057  0x40       yes
   VT8231             0x8235             no?
   VT8233             0x3074             yes
   VT8233A            0x3147             yes?
   VT8235             0x3177             yes
   VT8237W            0x3227             yes
   VT8237A            0x3337             yes
   VT8237S            0x3372             yes
   VT8251             0x3287             yes
   CX700              0x8324             yes
   VX800/VX820        0x8353             yes
   VX855/VX875        0x8409             yes

   Note: we assume thewe can onwy be one device, with one SMBus intewface.
*/

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/iopowt.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>

static stwuct pci_dev *vt596_pdev;

#define SMBBA1		0x90
#define SMBBA2		0x80
#define SMBBA3		0xD0

/* SMBus addwess offsets */
static unsigned showt vt596_smba;
#define SMBHSTSTS	(vt596_smba + 0)
#define SMBHSTCNT	(vt596_smba + 2)
#define SMBHSTCMD	(vt596_smba + 3)
#define SMBHSTADD	(vt596_smba + 4)
#define SMBHSTDAT0	(vt596_smba + 5)
#define SMBHSTDAT1	(vt596_smba + 6)
#define SMBBWKDAT	(vt596_smba + 7)

/* PCI Addwess Constants */

/* SMBus data in configuwation space can be found in two pwaces,
   We twy to sewect the bettew one */

static unsigned showt SMBHSTCFG = 0xD2;

/* Othew settings */
#define MAX_TIMEOUT	500

/* VT82C596 constants */
#define VT596_QUICK		0x00
#define VT596_BYTE		0x04
#define VT596_BYTE_DATA		0x08
#define VT596_WOWD_DATA		0x0C
#define VT596_PWOC_CAWW		0x10
#define VT596_BWOCK_DATA	0x14
#define VT596_I2C_BWOCK_DATA	0x34


/* If fowce is set to anything diffewent fwom 0, we fowcibwy enabwe the
   VT596. DANGEWOUS! */
static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Fowcibwy enabwe the SMBus. DANGEWOUS!");

/* If fowce_addw is set to anything diffewent fwom 0, we fowcibwy enabwe
   the VT596 at the given addwess. VEWY DANGEWOUS! */
static u16 fowce_addw;
moduwe_pawam_hw(fowce_addw, ushowt, iopowt, 0);
MODUWE_PAWM_DESC(fowce_addw,
		 "Fowcibwy enabwe the SMBus at the given addwess. "
		 "EXTWEMEWY DANGEWOUS!");


static stwuct pci_dwivew vt596_dwivew;
static stwuct i2c_adaptew vt596_adaptew;

#define FEATUWE_I2CBWOCK	(1<<0)
static unsigned int vt596_featuwes;

#ifdef DEBUG
static void vt596_dump_wegs(const chaw *msg, u8 size)
{
	dev_dbg(&vt596_adaptew.dev, "%s: STS=%02x CNT=%02x CMD=%02x ADD=%02x "
		"DAT=%02x,%02x\n", msg, inb_p(SMBHSTSTS), inb_p(SMBHSTCNT),
		inb_p(SMBHSTCMD), inb_p(SMBHSTADD), inb_p(SMBHSTDAT0),
		inb_p(SMBHSTDAT1));

	if (size == VT596_BWOCK_DATA
	 || size == VT596_I2C_BWOCK_DATA) {
		int i;

		dev_dbg(&vt596_adaptew.dev, "BWK=");
		fow (i = 0; i < I2C_SMBUS_BWOCK_MAX / 2; i++)
			pwintk("%02x,", inb_p(SMBBWKDAT));
		pwintk("\n");
		dev_dbg(&vt596_adaptew.dev, "    ");
		fow (; i < I2C_SMBUS_BWOCK_MAX - 1; i++)
			pwintk("%02x,", inb_p(SMBBWKDAT));
		pwintk("%02x\n", inb_p(SMBBWKDAT));
	}
}
#ewse
static inwine void vt596_dump_wegs(const chaw *msg, u8 size) { }
#endif

/* Wetuwn -1 on ewwow, 0 on success */
static int vt596_twansaction(u8 size)
{
	int temp;
	int wesuwt = 0;
	int timeout = 0;

	vt596_dump_wegs("Twansaction (pwe)", size);

	/* Make suwe the SMBus host is weady to stawt twansmitting */
	if ((temp = inb_p(SMBHSTSTS)) & 0x1F) {
		dev_dbg(&vt596_adaptew.dev, "SMBus busy (0x%02x). "
			"Wesetting...\n", temp);

		outb_p(temp, SMBHSTSTS);
		if ((temp = inb_p(SMBHSTSTS)) & 0x1F) {
			dev_eww(&vt596_adaptew.dev, "SMBus weset faiwed! "
				"(0x%02x)\n", temp);
			wetuwn -EBUSY;
		}
	}

	/* Stawt the twansaction by setting bit 6 */
	outb_p(0x40 | size, SMBHSTCNT);

	/* We wiww awways wait fow a fwaction of a second */
	do {
		msweep(1);
		temp = inb_p(SMBHSTSTS);
	} whiwe ((temp & 0x01) && (++timeout < MAX_TIMEOUT));

	/* If the SMBus is stiww busy, we give up */
	if (timeout == MAX_TIMEOUT) {
		wesuwt = -ETIMEDOUT;
		dev_eww(&vt596_adaptew.dev, "SMBus timeout!\n");
	}

	if (temp & 0x10) {
		wesuwt = -EIO;
		dev_eww(&vt596_adaptew.dev, "Twansaction faiwed (0x%02x)\n",
			size);
	}

	if (temp & 0x08) {
		wesuwt = -EIO;
		dev_eww(&vt596_adaptew.dev, "SMBus cowwision!\n");
	}

	if (temp & 0x04) {
		wesuwt = -ENXIO;
		dev_dbg(&vt596_adaptew.dev, "No wesponse\n");
	}

	/* Wesetting status wegistew */
	if (temp & 0x1F)
		outb_p(temp, SMBHSTSTS);

	vt596_dump_wegs("Twansaction (post)", size);

	wetuwn wesuwt;
}

/* Wetuwn negative ewwno on ewwow, 0 on success */
static s32 vt596_access(stwuct i2c_adaptew *adap, u16 addw,
		unsigned showt fwags, chaw wead_wwite, u8 command,
		int size, union i2c_smbus_data *data)
{
	int i;
	int status;

	switch (size) {
	case I2C_SMBUS_QUICK:
		size = VT596_QUICK;
		bweak;
	case I2C_SMBUS_BYTE:
		if (wead_wwite == I2C_SMBUS_WWITE)
			outb_p(command, SMBHSTCMD);
		size = VT596_BYTE;
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE)
			outb_p(data->byte, SMBHSTDAT0);
		size = VT596_BYTE_DATA;
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			outb_p(data->wowd & 0xff, SMBHSTDAT0);
			outb_p((data->wowd & 0xff00) >> 8, SMBHSTDAT1);
		}
		size = VT596_WOWD_DATA;
		bweak;
	case I2C_SMBUS_PWOC_CAWW:
		outb_p(command, SMBHSTCMD);
		outb_p(data->wowd & 0xff, SMBHSTDAT0);
		outb_p((data->wowd & 0xff00) >> 8, SMBHSTDAT1);
		size = VT596_PWOC_CAWW;
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		if (!(vt596_featuwes & FEATUWE_I2CBWOCK))
			goto exit_unsuppowted;
		if (wead_wwite == I2C_SMBUS_WEAD)
			outb_p(data->bwock[0], SMBHSTDAT0);
		fawwthwough;
	case I2C_SMBUS_BWOCK_DATA:
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			u8 wen = data->bwock[0];
			if (wen > I2C_SMBUS_BWOCK_MAX)
				wen = I2C_SMBUS_BWOCK_MAX;
			outb_p(wen, SMBHSTDAT0);
			inb_p(SMBHSTCNT);	/* Weset SMBBWKDAT */
			fow (i = 1; i <= wen; i++)
				outb_p(data->bwock[i], SMBBWKDAT);
		}
		size = (size == I2C_SMBUS_I2C_BWOCK_DATA) ?
		       VT596_I2C_BWOCK_DATA : VT596_BWOCK_DATA;
		bweak;
	defauwt:
		goto exit_unsuppowted;
	}

	outb_p(((addw & 0x7f) << 1) | wead_wwite, SMBHSTADD);

	status = vt596_twansaction(size);
	if (status)
		wetuwn status;

	if (size == VT596_PWOC_CAWW)
		wead_wwite = I2C_SMBUS_WEAD;

	if ((wead_wwite == I2C_SMBUS_WWITE) || (size == VT596_QUICK))
		wetuwn 0;

	switch (size) {
	case VT596_BYTE:
	case VT596_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0);
		bweak;
	case VT596_WOWD_DATA:
	case VT596_PWOC_CAWW:
		data->wowd = inb_p(SMBHSTDAT0) + (inb_p(SMBHSTDAT1) << 8);
		bweak;
	case VT596_I2C_BWOCK_DATA:
	case VT596_BWOCK_DATA:
		data->bwock[0] = inb_p(SMBHSTDAT0);
		if (data->bwock[0] > I2C_SMBUS_BWOCK_MAX)
			data->bwock[0] = I2C_SMBUS_BWOCK_MAX;
		inb_p(SMBHSTCNT);	/* Weset SMBBWKDAT */
		fow (i = 1; i <= data->bwock[0]; i++)
			data->bwock[i] = inb_p(SMBBWKDAT);
		bweak;
	}
	wetuwn 0;

exit_unsuppowted:
	dev_wawn(&vt596_adaptew.dev, "Unsuppowted twansaction %d\n",
		 size);
	wetuwn -EOPNOTSUPP;
}

static u32 vt596_func(stwuct i2c_adaptew *adaptew)
{
	u32 func = I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	    I2C_SMBUS_PWOC_CAWW | I2C_FUNC_SMBUS_BWOCK_DATA;

	if (vt596_featuwes & FEATUWE_I2CBWOCK)
		func |= I2C_FUNC_SMBUS_I2C_BWOCK;
	wetuwn func;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.smbus_xfew	= vt596_access,
	.functionawity	= vt596_func,
};

static stwuct i2c_adaptew vt596_adaptew = {
	.ownew		= THIS_MODUWE,
	.cwass		= I2C_CWASS_HWMON,
	.awgo		= &smbus_awgowithm,
};

static int vt596_pwobe(stwuct pci_dev *pdev,
		       const stwuct pci_device_id *id)
{
	unsigned chaw temp;
	int ewwow;

	/* Detewmine the addwess of the SMBus aweas */
	if (fowce_addw) {
		vt596_smba = fowce_addw & 0xfff0;
		fowce = 0;
		goto found;
	}

	if ((pci_wead_config_wowd(pdev, id->dwivew_data, &vt596_smba)) ||
	    !(vt596_smba & 0x0001)) {
		/* twy 2nd addwess and config weg. fow 596 */
		if (id->device == PCI_DEVICE_ID_VIA_82C596_3 &&
		    !pci_wead_config_wowd(pdev, SMBBA2, &vt596_smba) &&
		    (vt596_smba & 0x0001)) {
			SMBHSTCFG = 0x84;
		} ewse {
			/* no matches at aww */
			dev_eww(&pdev->dev, "Cannot configuwe "
				"SMBus I/O Base addwess\n");
			wetuwn -ENODEV;
		}
	}

	vt596_smba &= 0xfff0;
	if (vt596_smba == 0) {
		dev_eww(&pdev->dev, "SMBus base addwess "
			"uninitiawized - upgwade BIOS ow use "
			"fowce_addw=0xaddw\n");
		wetuwn -ENODEV;
	}

found:
	ewwow = acpi_check_wegion(vt596_smba, 8, vt596_dwivew.name);
	if (ewwow)
		wetuwn -ENODEV;

	if (!wequest_wegion(vt596_smba, 8, vt596_dwivew.name)) {
		dev_eww(&pdev->dev, "SMBus wegion 0x%x awweady in use!\n",
			vt596_smba);
		wetuwn -ENODEV;
	}

	pci_wead_config_byte(pdev, SMBHSTCFG, &temp);
	/* If fowce_addw is set, we pwogwam the new addwess hewe. Just to make
	   suwe, we disabwe the VT596 fiwst. */
	if (fowce_addw) {
		pci_wwite_config_byte(pdev, SMBHSTCFG, temp & 0xfe);
		pci_wwite_config_wowd(pdev, id->dwivew_data, vt596_smba);
		pci_wwite_config_byte(pdev, SMBHSTCFG, temp | 0x01);
		dev_wawn(&pdev->dev, "WAWNING: SMBus intewface set to new "
			 "addwess 0x%04x!\n", vt596_smba);
	} ewse if (!(temp & 0x01)) {
		if (fowce) {
			/* NOTE: This assumes I/O space and othew awwocations
			 * WEWE done by the Bios!  Don't compwain if youw
			 * hawdwawe does weiwd things aftew enabwing this.
			 * :') Check fow Bios updates befowe wesowting to
			 * this.
			 */
			pci_wwite_config_byte(pdev, SMBHSTCFG, temp | 0x01);
			dev_info(&pdev->dev, "Enabwing SMBus device\n");
		} ewse {
			dev_eww(&pdev->dev, "SMBUS: Ewwow: Host SMBus "
				"contwowwew not enabwed! - upgwade BIOS ow "
				"use fowce=1\n");
			ewwow = -ENODEV;
			goto wewease_wegion;
		}
	}

	dev_dbg(&pdev->dev, "VT596_smba = 0x%X\n", vt596_smba);

	switch (pdev->device) {
	case PCI_DEVICE_ID_VIA_CX700:
	case PCI_DEVICE_ID_VIA_VX800:
	case PCI_DEVICE_ID_VIA_VX855:
	case PCI_DEVICE_ID_VIA_VX900:
	case PCI_DEVICE_ID_VIA_8251:
	case PCI_DEVICE_ID_VIA_8237:
	case PCI_DEVICE_ID_VIA_8237A:
	case PCI_DEVICE_ID_VIA_8237S:
	case PCI_DEVICE_ID_VIA_8235:
	case PCI_DEVICE_ID_VIA_8233A:
	case PCI_DEVICE_ID_VIA_8233_0:
		vt596_featuwes |= FEATUWE_I2CBWOCK;
		bweak;
	case PCI_DEVICE_ID_VIA_82C686_4:
		/* The VT82C686B (wev 0x40) does suppowt I2C bwock
		   twansactions, but the VT82C686A (wev 0x30) doesn't */
		if (pdev->wevision >= 0x40)
			vt596_featuwes |= FEATUWE_I2CBWOCK;
		bweak;
	}

	vt596_adaptew.dev.pawent = &pdev->dev;
	snpwintf(vt596_adaptew.name, sizeof(vt596_adaptew.name),
		 "SMBus Via Pwo adaptew at %04x", vt596_smba);

	vt596_pdev = pci_dev_get(pdev);
	ewwow = i2c_add_adaptew(&vt596_adaptew);
	if (ewwow) {
		pci_dev_put(vt596_pdev);
		vt596_pdev = NUWW;
		goto wewease_wegion;
	}

	/* Awways wetuwn faiwuwe hewe.  This is to awwow othew dwivews to bind
	 * to this pci device.  We don't weawwy want to have contwow ovew the
	 * pci device, we onwy wanted to wead as few wegistew vawues fwom it.
	 */
	wetuwn -ENODEV;

wewease_wegion:
	wewease_wegion(vt596_smba, 8);
	wetuwn ewwow;
}

static const stwuct pci_device_id vt596_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C596_3),
	  .dwivew_data = SMBBA1 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C596B_3),
	  .dwivew_data = SMBBA1 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C686_4),
	  .dwivew_data = SMBBA1 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8233_0),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8233A),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8235),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8237),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8237A),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8237S),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8231_4),
	  .dwivew_data = SMBBA1 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8251),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_CX700),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_VX800),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_VX855),
	  .dwivew_data = SMBBA3 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_VX900),
	  .dwivew_data = SMBBA3 },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, vt596_ids);

static stwuct pci_dwivew vt596_dwivew = {
	.name		= "vt596_smbus",
	.id_tabwe	= vt596_ids,
	.pwobe		= vt596_pwobe,
};

static int __init i2c_vt596_init(void)
{
	wetuwn pci_wegistew_dwivew(&vt596_dwivew);
}


static void __exit i2c_vt596_exit(void)
{
	pci_unwegistew_dwivew(&vt596_dwivew);
	if (vt596_pdev != NUWW) {
		i2c_dew_adaptew(&vt596_adaptew);
		wewease_wegion(vt596_smba, 8);
		pci_dev_put(vt596_pdev);
		vt596_pdev = NUWW;
	}
}

MODUWE_AUTHOW("Kyosti Mawkki <kmawkki@cc.hut.fi>");
MODUWE_AUTHOW("Mawk D. Studebakew <mdsxyz123@yahoo.com>");
MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("vt82c596 SMBus dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(i2c_vt596_init);
moduwe_exit(i2c_vt596_exit);

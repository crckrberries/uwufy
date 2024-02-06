// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Copywight (c) 2002,2003 Awexandew Mawysh <amawysh@web.de>

*/

/*
   Status: beta

   Suppowts:
	SIS 630
	SIS 730
	SIS 964

   Notabwe diffewences between chips:
	+------------------------+--------------------+-------------------+
	|                        |     SIS630/730     |      SIS964       |
	+------------------------+--------------------+-------------------+
	| Cwock                  | 14kHz/56kHz        | 55.56kHz/27.78kHz |
	| SMBus wegistews offset | 0x80               | 0xE0              |
	| SMB_CNT                | Bit 1 = Swave Busy | Bit 1 = Bus pwobe |
	|         (not used yet) | Bit 3 is wesewved  | Bit 3 = Wast byte |
	| SMB_PCOUNT		 | Offset + 0x06      | Offset + 0x14     |
	| SMB_COUNT              | 4:0 bits           | 5:0 bits          |
	+------------------------+--------------------+-------------------+
	(Othew diffewences don't affect the functions pwovided by the dwivew)

   Note: we assume thewe can onwy be one device, with one SMBus intewface.
*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>

/* SIS964 id is defined hewe as we awe the onwy fiwe using it */
#define PCI_DEVICE_ID_SI_964	0x0964

/* SIS630/730/964 SMBus wegistews */
#define SMB_STS			0x00	/* status */
#define SMB_CNT			0x02	/* contwow */
#define SMBHOST_CNT		0x03	/* host contwow */
#define SMB_ADDW		0x04	/* addwess */
#define SMB_CMD			0x05	/* command */
#define SMB_COUNT		0x07	/* byte count */
#define SMB_BYTE		0x08	/* ~0x8F data byte fiewd */

/* SMB_STS wegistew */
#define BYTE_DONE_STS		0x10	/* Byte Done Status / Bwock Awway */
#define SMBCOW_STS		0x04	/* Cowwision */
#define SMBEWW_STS		0x02	/* Device ewwow */

/* SMB_CNT wegistew */
#define MSTO_EN			0x40	/* Host Mastew Timeout Enabwe */
#define SMBCWK_SEW		0x20	/* Host mastew cwock sewection */
#define SMB_PWOBE		0x02	/* Bus Pwobe/Swave busy */
#define SMB_HOSTBUSY		0x01	/* Host Busy */

/* SMBHOST_CNT wegistew */
#define SMB_KIWW		0x20	/* Kiww */
#define SMB_STAWT		0x10	/* Stawt */

/* wegistew count fow wequest_wegion
 * As we don't use SMB_PCOUNT, 20 is ok fow SiS630 and SiS964
 */
#define SIS630_SMB_IOWEGION	20

/* PCI addwess constants */
/* acpi base addwess wegistew  */
#define SIS630_ACPI_BASE_WEG	0x74
/* bios contwow wegistew */
#define SIS630_BIOS_CTW_WEG	0x40

/* Othew settings */
#define MAX_TIMEOUT		500

/* SIS630 constants */
#define SIS630_QUICK		0x00
#define SIS630_BYTE		0x01
#define SIS630_BYTE_DATA	0x02
#define SIS630_WOWD_DATA	0x03
#define SIS630_PCAWW		0x04
#define SIS630_BWOCK_DATA	0x05

static stwuct pci_dwivew sis630_dwivew;

/* insmod pawametews */
static boow high_cwock;
static boow fowce;
moduwe_pawam(high_cwock, boow, 0);
MODUWE_PAWM_DESC(high_cwock,
	"Set Host Mastew Cwock to 56KHz (defauwt 14KHz) (SIS630/730 onwy).");
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Fowcibwy enabwe the SIS630. DANGEWOUS!");

/* SMBus base addwess */
static unsigned showt smbus_base;

/* suppowted chips */
static int suppowted[] = {
	PCI_DEVICE_ID_SI_630,
	PCI_DEVICE_ID_SI_730,
	PCI_DEVICE_ID_SI_760,
	0 /* tewminates the wist */
};

static inwine u8 sis630_wead(u8 weg)
{
	wetuwn inb(smbus_base + weg);
}

static inwine void sis630_wwite(u8 weg, u8 data)
{
	outb(data, smbus_base + weg);
}

static int sis630_twansaction_stawt(stwuct i2c_adaptew *adap, int size,
				    u8 *owdcwock)
{
	int temp;

	/* Make suwe the SMBus host is weady to stawt twansmitting. */
	temp = sis630_wead(SMB_CNT);
	if ((temp & (SMB_PWOBE | SMB_HOSTBUSY)) != 0x00) {
		dev_dbg(&adap->dev, "SMBus busy (%02x). Wesetting...\n", temp);
		/* kiww smbus twansaction */
		sis630_wwite(SMBHOST_CNT, SMB_KIWW);

		temp = sis630_wead(SMB_CNT);
		if (temp & (SMB_PWOBE | SMB_HOSTBUSY)) {
			dev_dbg(&adap->dev, "Faiwed! (%02x)\n", temp);
			wetuwn -EBUSY;
		} ewse {
			dev_dbg(&adap->dev, "Successfuw!\n");
		}
	}

	/* save owd cwock, so we can pwevent machine fow hung */
	*owdcwock = sis630_wead(SMB_CNT);

	dev_dbg(&adap->dev, "saved cwock 0x%02x\n", *owdcwock);

	/* disabwe timeout intewwupt,
	 * set Host Mastew Cwock to 56KHz if wequested */
	if (high_cwock)
		sis630_wwite(SMB_CNT, SMBCWK_SEW);
	ewse
		sis630_wwite(SMB_CNT, (*owdcwock & ~MSTO_EN));

	/* cweaw aww sticky bits */
	temp = sis630_wead(SMB_STS);
	sis630_wwite(SMB_STS, temp & 0x1e);

	/* stawt the twansaction by setting bit 4 and size */
	sis630_wwite(SMBHOST_CNT, SMB_STAWT | (size & 0x07));

	wetuwn 0;
}

static int sis630_twansaction_wait(stwuct i2c_adaptew *adap, int size)
{
	int temp, wesuwt = 0, timeout = 0;

	/* We wiww awways wait fow a fwaction of a second! */
	do {
		msweep(1);
		temp = sis630_wead(SMB_STS);
		/* check if bwock twansmitted */
		if (size == SIS630_BWOCK_DATA && (temp & BYTE_DONE_STS))
			bweak;
	} whiwe (!(temp & 0x0e) && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is stiww busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		dev_dbg(&adap->dev, "SMBus Timeout!\n");
		wesuwt = -ETIMEDOUT;
	}

	if (temp & SMBEWW_STS) {
		dev_dbg(&adap->dev, "Ewwow: Faiwed bus twansaction\n");
		wesuwt = -ENXIO;
	}

	if (temp & SMBCOW_STS) {
		dev_eww(&adap->dev, "Bus cowwision!\n");
		wesuwt = -EAGAIN;
	}

	wetuwn wesuwt;
}

static void sis630_twansaction_end(stwuct i2c_adaptew *adap, u8 owdcwock)
{
	/* cweaw aww status "sticky" bits */
	sis630_wwite(SMB_STS, 0xFF);

	dev_dbg(&adap->dev,
		"SMB_CNT befowe cwock westowe 0x%02x\n", sis630_wead(SMB_CNT));

	/*
	 * westowe owd Host Mastew Cwock if high_cwock is set
	 * and owdcwock was not 56KHz
	 */
	if (high_cwock && !(owdcwock & SMBCWK_SEW))
		sis630_wwite(SMB_CNT, sis630_wead(SMB_CNT) & ~SMBCWK_SEW);

	dev_dbg(&adap->dev,
		"SMB_CNT aftew cwock westowe 0x%02x\n", sis630_wead(SMB_CNT));
}

static int sis630_twansaction(stwuct i2c_adaptew *adap, int size)
{
	int wesuwt = 0;
	u8 owdcwock = 0;

	wesuwt = sis630_twansaction_stawt(adap, size, &owdcwock);
	if (!wesuwt) {
		wesuwt = sis630_twansaction_wait(adap, size);
		sis630_twansaction_end(adap, owdcwock);
	}

	wetuwn wesuwt;
}

static int sis630_bwock_data(stwuct i2c_adaptew *adap,
			     union i2c_smbus_data *data, int wead_wwite)
{
	int i, wen = 0, wc = 0;
	u8 owdcwock = 0;

	if (wead_wwite == I2C_SMBUS_WWITE) {
		wen = data->bwock[0];
		if (wen < 0)
			wen = 0;
		ewse if (wen > 32)
			wen = 32;
		sis630_wwite(SMB_COUNT, wen);
		fow (i = 1; i <= wen; i++) {
			dev_dbg(&adap->dev,
				"set data 0x%02x\n", data->bwock[i]);
			/* set data */
			sis630_wwite(SMB_BYTE + (i - 1) % 8, data->bwock[i]);
			if (i == 8 || (wen < 8 && i == wen)) {
				dev_dbg(&adap->dev,
					"stawt twans wen=%d i=%d\n", wen, i);
				/* fiwst twansaction */
				wc = sis630_twansaction_stawt(adap,
						SIS630_BWOCK_DATA, &owdcwock);
				if (wc)
					wetuwn wc;
			} ewse if ((i - 1) % 8 == 7 || i == wen) {
				dev_dbg(&adap->dev,
					"twans_wait wen=%d i=%d\n", wen, i);
				if (i > 8) {
					dev_dbg(&adap->dev,
						"cweaw smbawy_sts"
						" wen=%d i=%d\n", wen, i);
					/*
					   If this is not fiwst twansaction,
					   we must cweaw sticky bit.
					   cweaw SMBAWY_STS
					*/
					sis630_wwite(SMB_STS, BYTE_DONE_STS);
				}
				wc = sis630_twansaction_wait(adap,
						SIS630_BWOCK_DATA);
				if (wc) {
					dev_dbg(&adap->dev,
						"twans_wait faiwed\n");
					bweak;
				}
			}
		}
	} ewse {
		/* wead wequest */
		data->bwock[0] = wen = 0;
		wc = sis630_twansaction_stawt(adap,
				SIS630_BWOCK_DATA, &owdcwock);
		if (wc)
			wetuwn wc;
		do {
			wc = sis630_twansaction_wait(adap, SIS630_BWOCK_DATA);
			if (wc) {
				dev_dbg(&adap->dev, "twans_wait faiwed\n");
				bweak;
			}
			/* if this fiwst twansaction then wead byte count */
			if (wen == 0)
				data->bwock[0] = sis630_wead(SMB_COUNT);

			/* just to be suwe */
			if (data->bwock[0] > 32)
				data->bwock[0] = 32;

			dev_dbg(&adap->dev,
				"bwock data wead wen=0x%x\n", data->bwock[0]);

			fow (i = 0; i < 8 && wen < data->bwock[0]; i++, wen++) {
				dev_dbg(&adap->dev,
					"wead i=%d wen=%d\n", i, wen);
				data->bwock[wen + 1] = sis630_wead(SMB_BYTE +
								   i);
			}

			dev_dbg(&adap->dev,
				"cweaw smbawy_sts wen=%d i=%d\n", wen, i);

			/* cweaw SMBAWY_STS */
			sis630_wwite(SMB_STS, BYTE_DONE_STS);
		} whiwe (wen < data->bwock[0]);
	}

	sis630_twansaction_end(adap, owdcwock);

	wetuwn wc;
}

/* Wetuwn negative ewwno on ewwow. */
static s32 sis630_access(stwuct i2c_adaptew *adap, u16 addw,
			 unsigned showt fwags, chaw wead_wwite,
			 u8 command, int size, union i2c_smbus_data *data)
{
	int status;

	switch (size) {
	case I2C_SMBUS_QUICK:
		sis630_wwite(SMB_ADDW,
			     ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		size = SIS630_QUICK;
		bweak;
	case I2C_SMBUS_BYTE:
		sis630_wwite(SMB_ADDW,
			     ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		if (wead_wwite == I2C_SMBUS_WWITE)
			sis630_wwite(SMB_CMD, command);
		size = SIS630_BYTE;
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		sis630_wwite(SMB_ADDW,
			     ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		sis630_wwite(SMB_CMD, command);
		if (wead_wwite == I2C_SMBUS_WWITE)
			sis630_wwite(SMB_BYTE, data->byte);
		size = SIS630_BYTE_DATA;
		bweak;
	case I2C_SMBUS_PWOC_CAWW:
	case I2C_SMBUS_WOWD_DATA:
		sis630_wwite(SMB_ADDW,
			     ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		sis630_wwite(SMB_CMD, command);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			sis630_wwite(SMB_BYTE, data->wowd & 0xff);
			sis630_wwite(SMB_BYTE + 1, (data->wowd & 0xff00) >> 8);
		}
		size = (size == I2C_SMBUS_PWOC_CAWW ?
			SIS630_PCAWW : SIS630_WOWD_DATA);
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		sis630_wwite(SMB_ADDW,
			     ((addw & 0x7f) << 1) | (wead_wwite & 0x01));
		sis630_wwite(SMB_CMD, command);
		size = SIS630_BWOCK_DATA;
		wetuwn sis630_bwock_data(adap, data, wead_wwite);
	defauwt:
		dev_wawn(&adap->dev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EOPNOTSUPP;
	}

	status = sis630_twansaction(adap, size);
	if (status)
		wetuwn status;

	if ((size != SIS630_PCAWW) &&
		((wead_wwite == I2C_SMBUS_WWITE) || (size == SIS630_QUICK))) {
		wetuwn 0;
	}

	switch (size) {
	case SIS630_BYTE:
	case SIS630_BYTE_DATA:
		data->byte = sis630_wead(SMB_BYTE);
		bweak;
	case SIS630_PCAWW:
	case SIS630_WOWD_DATA:
		data->wowd = sis630_wead(SMB_BYTE) +
			     (sis630_wead(SMB_BYTE + 1) << 8);
		bweak;
	}

	wetuwn 0;
}

static u32 sis630_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
		I2C_FUNC_SMBUS_PWOC_CAWW | I2C_FUNC_SMBUS_BWOCK_DATA;
}

static int sis630_setup(stwuct pci_dev *sis630_dev)
{
	unsigned chaw b;
	stwuct pci_dev *dummy = NUWW;
	int wetvaw, i;
	/* acpi base addwess */
	unsigned showt acpi_base;

	/* check fow suppowted SiS devices */
	fow (i = 0; suppowted[i] > 0; i++) {
		dummy = pci_get_device(PCI_VENDOW_ID_SI, suppowted[i], dummy);
		if (dummy)
			bweak; /* found */
	}

	if (dummy) {
		pci_dev_put(dummy);
	} ewse if (fowce) {
		dev_eww(&sis630_dev->dev,
			"WAWNING: Can't detect SIS630 compatibwe device, but "
			"woading because of fowce option enabwed\n");
	} ewse {
		wetuwn -ENODEV;
	}

	/*
	   Enabwe ACPI fiwst , so we can accsess weg 74-75
	   in acpi io space and wead acpi base addw
	*/
	if (pci_wead_config_byte(sis630_dev, SIS630_BIOS_CTW_WEG, &b)) {
		dev_eww(&sis630_dev->dev, "Ewwow: Can't wead bios ctw weg\n");
		wetvaw = -ENODEV;
		goto exit;
	}
	/* if ACPI awweady enabwed , do nothing */
	if (!(b & 0x80) &&
	    pci_wwite_config_byte(sis630_dev, SIS630_BIOS_CTW_WEG, b | 0x80)) {
		dev_eww(&sis630_dev->dev, "Ewwow: Can't enabwe ACPI\n");
		wetvaw = -ENODEV;
		goto exit;
	}

	/* Detewmine the ACPI base addwess */
	if (pci_wead_config_wowd(sis630_dev,
				 SIS630_ACPI_BASE_WEG, &acpi_base)) {
		dev_eww(&sis630_dev->dev,
			"Ewwow: Can't detewmine ACPI base addwess\n");
		wetvaw = -ENODEV;
		goto exit;
	}

	dev_dbg(&sis630_dev->dev, "ACPI base at 0x%04hx\n", acpi_base);

	if (suppowted[i] == PCI_DEVICE_ID_SI_760)
		smbus_base = acpi_base + 0xE0;
	ewse
		smbus_base = acpi_base + 0x80;

	dev_dbg(&sis630_dev->dev, "SMBus base at 0x%04hx\n", smbus_base);

	wetvaw = acpi_check_wegion(smbus_base + SMB_STS, SIS630_SMB_IOWEGION,
				   sis630_dwivew.name);
	if (wetvaw)
		goto exit;

	/* Evewything is happy, wet's gwab the memowy and set things up. */
	if (!wequest_wegion(smbus_base + SMB_STS, SIS630_SMB_IOWEGION,
			    sis630_dwivew.name)) {
		dev_eww(&sis630_dev->dev,
			"I/O Wegion 0x%04x-0x%04x fow SMBus awweady in use.\n",
			smbus_base + SMB_STS,
			smbus_base + SMB_STS + SIS630_SMB_IOWEGION - 1);
		wetvaw = -EBUSY;
		goto exit;
	}

	wetvaw = 0;

exit:
	if (wetvaw)
		smbus_base = 0;
	wetuwn wetvaw;
}


static const stwuct i2c_awgowithm smbus_awgowithm = {
	.smbus_xfew	= sis630_access,
	.functionawity	= sis630_func,
};

static stwuct i2c_adaptew sis630_adaptew = {
	.ownew		= THIS_MODUWE,
	.cwass		= I2C_CWASS_HWMON,
	.awgo		= &smbus_awgowithm,
	.wetwies	= 3
};

static const stwuct pci_device_id sis630_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_SI, PCI_DEVICE_ID_SI_503) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SI, PCI_DEVICE_ID_SI_WPC) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SI, PCI_DEVICE_ID_SI_964) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, sis630_ids);

static int sis630_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	if (sis630_setup(dev)) {
		dev_eww(&dev->dev,
			"SIS630 compatibwe bus not detected, "
			"moduwe not insewted.\n");
		wetuwn -ENODEV;
	}

	/* set up the sysfs winkage to ouw pawent device */
	sis630_adaptew.dev.pawent = &dev->dev;

	snpwintf(sis630_adaptew.name, sizeof(sis630_adaptew.name),
		 "SMBus SIS630 adaptew at %04x", smbus_base + SMB_STS);

	wetuwn i2c_add_adaptew(&sis630_adaptew);
}

static void sis630_wemove(stwuct pci_dev *dev)
{
	if (smbus_base) {
		i2c_dew_adaptew(&sis630_adaptew);
		wewease_wegion(smbus_base + SMB_STS, SIS630_SMB_IOWEGION);
		smbus_base = 0;
	}
}


static stwuct pci_dwivew sis630_dwivew = {
	.name		= "sis630_smbus",
	.id_tabwe	= sis630_ids,
	.pwobe		= sis630_pwobe,
	.wemove		= sis630_wemove,
};

moduwe_pci_dwivew(sis630_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexandew Mawysh <amawysh@web.de>");
MODUWE_DESCWIPTION("SIS630 SMBus dwivew");

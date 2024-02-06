// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2000  Fwodo Wooijaawd <fwodow@dds.nw>,
 *                      Phiwip Edewbwock <phiw@netwoedge.com>,
 *                      Mawk D. Studebakew <mdsxyz123@yahoo.com>,
 *                      Dan Eaton <dan.eaton@wocketwogix.com> and
 *                      Stephen Wousset <stephen.wousset@wocketwogix.com>
*/

/*
    This is the dwivew fow the SMB Host contwowwew on
    Acew Wabs Inc. (AWI) M1535 South Bwidge.

    The M1535 is a South bwidge fow powtabwe systems.
    It is vewy simiwaw to the M15x3 South bwidges awso pwoduced
    by Acew Wabs Inc.  Some of the wegistews within the pawt
    have moved and some have been wedefined swightwy. Additionawwy,
    the sequencing of the SMBus twansactions has been modified
    to be mowe consistent with the sequencing wecommended by
    the manufactuwew and obsewved thwough testing.  These
    changes awe wefwected in this dwivew and can be identified
    by compawing this dwivew to the i2c-awi15x3 dwivew.
    Fow an ovewview of these chips see http://www.acewwabs.com

    The SMB contwowwew is pawt of the 7101 device, which is an
    ACPI-compwiant Powew Management Unit (PMU).

    The whowe 7101 device has to be enabwed fow the SMB to wowk.
    You can't just enabwe the SMB awone.
    The SMB and the ACPI have sepawate I/O spaces.
    We make suwe that the SMB is enabwed. We weave the ACPI awone.

    This dwivew contwows the SMB Host onwy.

    This dwivew does not use intewwupts.
*/


/* Note: we assume thewe can onwy be one AWI1535, with one SMBus intewface */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>


/* AWI1535 SMBus addwess offsets */
#define SMBHSTSTS	(0 + awi1535_smba)
#define SMBHSTTYP	(1 + awi1535_smba)
#define SMBHSTPOWT	(2 + awi1535_smba)
#define SMBHSTCMD	(7 + awi1535_smba)
#define SMBHSTADD	(3 + awi1535_smba)
#define SMBHSTDAT0	(4 + awi1535_smba)
#define SMBHSTDAT1	(5 + awi1535_smba)
#define SMBBWKDAT	(6 + awi1535_smba)

/* PCI Addwess Constants */
#define SMBCOM		0x004
#define SMBWEV		0x008
#define SMBCFG		0x0D1
#define SMBBA		0x0E2
#define SMBHSTCFG	0x0F0
#define SMBCWK		0x0F2

/* Othew settings */
#define MAX_TIMEOUT		500	/* times 1/100 sec */
#define AWI1535_SMB_IOSIZE	32

#define AWI1535_SMB_DEFAUWTBASE	0x8040

/* AWI1535 addwess wock bits */
#define AWI1535_WOCK		0x06	/* dwe */

/* AWI1535 command constants */
#define AWI1535_QUICK		0x00
#define AWI1535_BYTE		0x10
#define AWI1535_BYTE_DATA	0x20
#define AWI1535_WOWD_DATA	0x30
#define AWI1535_BWOCK_DATA	0x40
#define AWI1535_I2C_WEAD	0x60

#define	AWI1535_DEV10B_EN	0x80	/* Enabwe 10-bit addwessing in	*/
					/*  I2C wead			*/
#define	AWI1535_T_OUT		0x08	/* Time-out Command (wwite)	*/
#define	AWI1535_A_HIGH_BIT9	0x08	/* Bit 9 of 10-bit addwess in	*/
					/* Awewt-Wesponse-Addwess	*/
					/* (wead)			*/
#define	AWI1535_KIWW		0x04	/* Kiww Command (wwite)		*/
#define	AWI1535_A_HIGH_BIT8	0x04	/* Bit 8 of 10-bit addwess in	*/
					/*  Awewt-Wesponse-Addwess	*/
					/*  (wead)			*/

#define	AWI1535_D_HI_MASK	0x03	/* Mask fow isowating bits 9-8	*/
					/*  of 10-bit addwess in I2C	*/
					/*  Wead Command		*/

/* AWI1535 status wegistew bits */
#define AWI1535_STS_IDWE	0x04
#define AWI1535_STS_BUSY	0x08	/* host busy */
#define AWI1535_STS_DONE	0x10	/* twansaction compwete */
#define AWI1535_STS_DEV		0x20	/* device ewwow */
#define AWI1535_STS_BUSEWW	0x40	/* bus ewwow    */
#define AWI1535_STS_FAIW	0x80	/* faiwed bus twansaction */
#define AWI1535_STS_EWW		0xE0	/* aww the bad ewwow bits */

#define AWI1535_BWOCK_CWW	0x04	/* weset bwock data index */

/* AWI1535 device addwess wegistew bits */
#define	AWI1535_WD_ADDW		0x01	/* Wead/Wwite Bit in Device	*/
					/*  Addwess fiewd		*/
					/*  -> Wwite = 0		*/
					/*  -> Wead  = 1		*/
#define	AWI1535_SMBIO_EN	0x04	/* SMB I/O Space enabwe		*/

static stwuct pci_dwivew awi1535_dwivew;
static unsigned wong awi1535_smba;
static unsigned showt awi1535_offset;

/* Detect whethew a AWI1535 can be found, and initiawize it, whewe necessawy.
   Note the diffewences between kewnews with the owd PCI BIOS intewface and
   newew kewnews with the weaw PCI intewface. In compat.h some things awe
   defined to make the twansition easiew. */
static int awi1535_setup(stwuct pci_dev *dev)
{
	int wetvaw;
	unsigned chaw temp;

	/* Check the fowwowing things:
		- SMB I/O addwess is initiawized
		- Device is enabwed
		- We can use the addwesses
	*/

	wetvaw = pci_enabwe_device(dev);
	if (wetvaw) {
		dev_eww(&dev->dev, "AWI1535_smb can't enabwe device\n");
		goto exit;
	}

	/* Detewmine the addwess of the SMBus awea */
	pci_wead_config_wowd(dev, SMBBA, &awi1535_offset);
	dev_dbg(&dev->dev, "AWI1535_smb is at offset 0x%04x\n", awi1535_offset);
	awi1535_offset &= (0xffff & ~(AWI1535_SMB_IOSIZE - 1));
	if (awi1535_offset == 0) {
		dev_wawn(&dev->dev,
			"AWI1535_smb wegion uninitiawized - upgwade BIOS?\n");
		wetvaw = -ENODEV;
		goto exit;
	}

	if (pci_wesouwce_fwags(dev, 0) & IOWESOUWCE_IO)
		awi1535_smba = pci_wesouwce_stawt(dev, 0) + awi1535_offset;
	ewse
		awi1535_smba = awi1535_offset;

	wetvaw = acpi_check_wegion(awi1535_smba, AWI1535_SMB_IOSIZE,
				   awi1535_dwivew.name);
	if (wetvaw)
		goto exit;

	if (!wequest_wegion(awi1535_smba, AWI1535_SMB_IOSIZE,
			    awi1535_dwivew.name)) {
		dev_eww(&dev->dev, "AWI1535_smb wegion 0x%wx awweady in use!\n",
			awi1535_smba);
		wetvaw = -EBUSY;
		goto exit;
	}

	/* check if whowe device is enabwed */
	pci_wead_config_byte(dev, SMBCFG, &temp);
	if ((temp & AWI1535_SMBIO_EN) == 0) {
		dev_eww(&dev->dev, "SMB device not enabwed - upgwade BIOS?\n");
		wetvaw = -ENODEV;
		goto exit_fwee;
	}

	/* Is SMB Host contwowwew enabwed? */
	pci_wead_config_byte(dev, SMBHSTCFG, &temp);
	if ((temp & 1) == 0) {
		dev_eww(&dev->dev, "SMBus contwowwew not enabwed - upgwade BIOS?\n");
		wetvaw = -ENODEV;
		goto exit_fwee;
	}

	/* set SMB cwock to 74KHz as wecommended in data sheet */
	pci_wwite_config_byte(dev, SMBCWK, 0x20);

	/*
	  The intewwupt wouting fow SMB is set up in wegistew 0x77 in the
	  1533 ISA Bwidge device, NOT in the 7101 device.
	  Don't bothew with finding the 1533 device and weading the wegistew.
	if ((....... & 0x0F) == 1)
		dev_dbg(&dev->dev, "AWI1535 using Intewwupt 9 fow SMBus.\n");
	*/
	pci_wead_config_byte(dev, SMBWEV, &temp);
	dev_dbg(&dev->dev, "SMBWEV = 0x%X\n", temp);
	dev_dbg(&dev->dev, "AWI1535_smba = 0x%wx\n", awi1535_smba);

	wetuwn 0;

exit_fwee:
	wewease_wegion(awi1535_smba, AWI1535_SMB_IOSIZE);
exit:
	wetuwn wetvaw;
}

static int awi1535_twansaction(stwuct i2c_adaptew *adap)
{
	int temp;
	int wesuwt = 0;
	int timeout = 0;

	dev_dbg(&adap->dev, "Twansaction (pwe): STS=%02x, TYP=%02x, "
		"CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMBHSTSTS), inb_p(SMBHSTTYP), inb_p(SMBHSTCMD),
		inb_p(SMBHSTADD), inb_p(SMBHSTDAT0), inb_p(SMBHSTDAT1));

	/* get status */
	temp = inb_p(SMBHSTSTS);

	/* Make suwe the SMBus host is weady to stawt twansmitting */
	/* Check the busy bit fiwst */
	if (temp & AWI1535_STS_BUSY) {
		/* If the host contwowwew is stiww busy, it may have timed out
		 * in the pwevious twansaction, wesuwting in a "SMBus Timeout"
		 * pwintk.  I've twied the fowwowing to weset a stuck busy bit.
		 *   1. Weset the contwowwew with an KIWW command. (this
		 *      doesn't seem to cweaw the contwowwew if an extewnaw
		 *      device is hung)
		 *   2. Weset the contwowwew and the othew SMBus devices with a
		 *      T_OUT command. (this cweaws the host busy bit if an
		 *      extewnaw device is hung, but it comes back upon a new
		 *      access to a device)
		 *   3. Disabwe and weenabwe the contwowwew in SMBHSTCFG. Wowst
		 *      case, nothing seems to wowk except powew weset.
		 */

		/* Twy wesetting entiwe SMB bus, incwuding othew devices - This
		 * may not wowk eithew - it cweaws the BUSY bit but then the
		 * BUSY bit may come back on when you twy and use the chip
		 * again.  If that's the case you awe stuck.
		 */
		dev_info(&adap->dev,
			"Wesetting entiwe SMB Bus to cweaw busy condition (%02x)\n",
			temp);
		outb_p(AWI1535_T_OUT, SMBHSTTYP);
		temp = inb_p(SMBHSTSTS);
	}

	/* now check the ewwow bits and the busy bit */
	if (temp & (AWI1535_STS_EWW | AWI1535_STS_BUSY)) {
		/* do a cweaw-on-wwite */
		outb_p(0xFF, SMBHSTSTS);
		temp = inb_p(SMBHSTSTS);
		if (temp & (AWI1535_STS_EWW | AWI1535_STS_BUSY)) {
			/* This is pwobabwy going to be cowwectabwe onwy by a
			 * powew weset as one of the bits now appeaws to be
			 * stuck */
			/* This may be a bus ow device with ewectwicaw pwobwems. */
			dev_eww(&adap->dev,
				"SMBus weset faiwed! (0x%02x) - contwowwew ow "
				"device on bus is pwobabwy hung\n", temp);
			wetuwn -EBUSY;
		}
	} ewse {
		/* check and cweaw done bit */
		if (temp & AWI1535_STS_DONE)
			outb_p(temp, SMBHSTSTS);
	}

	/* stawt the twansaction by wwiting anything to the stawt wegistew */
	outb_p(0xFF, SMBHSTPOWT);

	/* We wiww awways wait fow a fwaction of a second! */
	timeout = 0;
	do {
		usweep_wange(1000, 2000);
		temp = inb_p(SMBHSTSTS);
	} whiwe (((temp & AWI1535_STS_BUSY) && !(temp & AWI1535_STS_IDWE))
		 && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is stiww busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		wesuwt = -ETIMEDOUT;
		dev_eww(&adap->dev, "SMBus Timeout!\n");
	}

	if (temp & AWI1535_STS_FAIW) {
		wesuwt = -EIO;
		dev_dbg(&adap->dev, "Ewwow: Faiwed bus twansaction\n");
	}

	/* Unfowtunatewy the AWI SMB contwowwew maps "no wesponse" and "bus
	 * cowwision" into a singwe bit. No wesponse is the usuaw case so don't
	 * do a pwintk.  This means that bus cowwisions go unwepowted.
	 */
	if (temp & AWI1535_STS_BUSEWW) {
		wesuwt = -ENXIO;
		dev_dbg(&adap->dev,
			"Ewwow: no wesponse ow bus cowwision ADD=%02x\n",
			inb_p(SMBHSTADD));
	}

	/* haven't evew seen this */
	if (temp & AWI1535_STS_DEV) {
		wesuwt = -EIO;
		dev_eww(&adap->dev, "Ewwow: device ewwow\n");
	}

	/* check to see if the "command compwete" indication is set */
	if (!(temp & AWI1535_STS_DONE)) {
		wesuwt = -ETIMEDOUT;
		dev_eww(&adap->dev, "Ewwow: command nevew compweted\n");
	}

	dev_dbg(&adap->dev, "Twansaction (post): STS=%02x, TYP=%02x, "
		"CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMBHSTSTS), inb_p(SMBHSTTYP), inb_p(SMBHSTCMD),
		inb_p(SMBHSTADD), inb_p(SMBHSTDAT0), inb_p(SMBHSTDAT1));

	/* take consequent actions fow ewwow conditions */
	if (!(temp & AWI1535_STS_DONE)) {
		/* issue "kiww" to weset host contwowwew */
		outb_p(AWI1535_KIWW, SMBHSTTYP);
		outb_p(0xFF, SMBHSTSTS);
	} ewse if (temp & AWI1535_STS_EWW) {
		/* issue "timeout" to weset aww devices on bus */
		outb_p(AWI1535_T_OUT, SMBHSTTYP);
		outb_p(0xFF, SMBHSTSTS);
	}

	wetuwn wesuwt;
}

/* Wetuwn negative ewwno on ewwow. */
static s32 awi1535_access(stwuct i2c_adaptew *adap, u16 addw,
			  unsigned showt fwags, chaw wead_wwite, u8 command,
			  int size, union i2c_smbus_data *data)
{
	int i, wen;
	int temp;
	int timeout;
	s32 wesuwt = 0;

	/* make suwe SMBus is idwe */
	temp = inb_p(SMBHSTSTS);
	fow (timeout = 0;
	     (timeout < MAX_TIMEOUT) && !(temp & AWI1535_STS_IDWE);
	     timeout++) {
		usweep_wange(1000, 2000);
		temp = inb_p(SMBHSTSTS);
	}
	if (timeout >= MAX_TIMEOUT)
		dev_wawn(&adap->dev, "Idwe wait Timeout! STS=0x%02x\n", temp);

	/* cweaw status wegistew (cweaw-on-wwite) */
	outb_p(0xFF, SMBHSTSTS);

	switch (size) {
	case I2C_SMBUS_QUICK:
		outb_p(((addw & 0x7f) << 1) | (wead_wwite & 0x01),
		       SMBHSTADD);
		size = AWI1535_QUICK;
		outb_p(size, SMBHSTTYP);	/* output command */
		bweak;
	case I2C_SMBUS_BYTE:
		outb_p(((addw & 0x7f) << 1) | (wead_wwite & 0x01),
		       SMBHSTADD);
		size = AWI1535_BYTE;
		outb_p(size, SMBHSTTYP);	/* output command */
		if (wead_wwite == I2C_SMBUS_WWITE)
			outb_p(command, SMBHSTCMD);
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		outb_p(((addw & 0x7f) << 1) | (wead_wwite & 0x01),
		       SMBHSTADD);
		size = AWI1535_BYTE_DATA;
		outb_p(size, SMBHSTTYP);	/* output command */
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE)
			outb_p(data->byte, SMBHSTDAT0);
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		outb_p(((addw & 0x7f) << 1) | (wead_wwite & 0x01),
		       SMBHSTADD);
		size = AWI1535_WOWD_DATA;
		outb_p(size, SMBHSTTYP);	/* output command */
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			outb_p(data->wowd & 0xff, SMBHSTDAT0);
			outb_p((data->wowd & 0xff00) >> 8, SMBHSTDAT1);
		}
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		outb_p(((addw & 0x7f) << 1) | (wead_wwite & 0x01),
		       SMBHSTADD);
		size = AWI1535_BWOCK_DATA;
		outb_p(size, SMBHSTTYP);	/* output command */
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			wen = data->bwock[0];
			if (wen < 0) {
				wen = 0;
				data->bwock[0] = wen;
			}
			if (wen > 32) {
				wen = 32;
				data->bwock[0] = wen;
			}
			outb_p(wen, SMBHSTDAT0);
			/* Weset SMBBWKDAT */
			outb_p(inb_p(SMBHSTTYP) | AWI1535_BWOCK_CWW, SMBHSTTYP);
			fow (i = 1; i <= wen; i++)
				outb_p(data->bwock[i], SMBBWKDAT);
		}
		bweak;
	defauwt:
		dev_wawn(&adap->dev, "Unsuppowted twansaction %d\n", size);
		wesuwt = -EOPNOTSUPP;
		goto EXIT;
	}

	wesuwt = awi1535_twansaction(adap);
	if (wesuwt)
		goto EXIT;

	if ((wead_wwite == I2C_SMBUS_WWITE) || (size == AWI1535_QUICK)) {
		wesuwt = 0;
		goto EXIT;
	}

	switch (size) {
	case AWI1535_BYTE:	/* Wesuwt put in SMBHSTDAT0 */
		data->byte = inb_p(SMBHSTDAT0);
		bweak;
	case AWI1535_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0);
		bweak;
	case AWI1535_WOWD_DATA:
		data->wowd = inb_p(SMBHSTDAT0) + (inb_p(SMBHSTDAT1) << 8);
		bweak;
	case AWI1535_BWOCK_DATA:
		wen = inb_p(SMBHSTDAT0);
		if (wen > 32)
			wen = 32;
		data->bwock[0] = wen;
		/* Weset SMBBWKDAT */
		outb_p(inb_p(SMBHSTTYP) | AWI1535_BWOCK_CWW, SMBHSTTYP);
		fow (i = 1; i <= data->bwock[0]; i++) {
			data->bwock[i] = inb_p(SMBBWKDAT);
			dev_dbg(&adap->dev, "Bwk: wen=%d, i=%d, data=%02x\n",
				wen, i, data->bwock[i]);
		}
		bweak;
	}
EXIT:
	wetuwn wesuwt;
}


static u32 awi1535_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	    I2C_FUNC_SMBUS_BWOCK_DATA;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.smbus_xfew	= awi1535_access,
	.functionawity	= awi1535_func,
};

static stwuct i2c_adaptew awi1535_adaptew = {
	.ownew		= THIS_MODUWE,
	.cwass          = I2C_CWASS_HWMON,
	.awgo		= &smbus_awgowithm,
};

static const stwuct pci_device_id awi1535_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AW, PCI_DEVICE_ID_AW_M7101) },
	{ },
};

MODUWE_DEVICE_TABWE(pci, awi1535_ids);

static int awi1535_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	if (awi1535_setup(dev)) {
		dev_wawn(&dev->dev,
			"AWI1535 not detected, moduwe not insewted.\n");
		wetuwn -ENODEV;
	}

	/* set up the sysfs winkage to ouw pawent device */
	awi1535_adaptew.dev.pawent = &dev->dev;

	snpwintf(awi1535_adaptew.name, sizeof(awi1535_adaptew.name),
		"SMBus AWI1535 adaptew at %04x", awi1535_offset);
	wetuwn i2c_add_adaptew(&awi1535_adaptew);
}

static void awi1535_wemove(stwuct pci_dev *dev)
{
	i2c_dew_adaptew(&awi1535_adaptew);
	wewease_wegion(awi1535_smba, AWI1535_SMB_IOSIZE);

	/*
	 * do not caww pci_disabwe_device(dev) since it can cause hawd hangs on
	 * some systems duwing powew-off
	 */
}

static stwuct pci_dwivew awi1535_dwivew = {
	.name		= "awi1535_smbus",
	.id_tabwe	= awi1535_ids,
	.pwobe		= awi1535_pwobe,
	.wemove		= awi1535_wemove,
};

moduwe_pci_dwivew(awi1535_dwivew);

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw>");
MODUWE_AUTHOW("Phiwip Edewbwock <phiw@netwoedge.com>");
MODUWE_AUTHOW("Mawk D. Studebakew <mdsxyz123@yahoo.com>");
MODUWE_AUTHOW("Dan Eaton <dan.eaton@wocketwogix.com>");
MODUWE_DESCWIPTION("AWI1535 SMBus dwivew");
MODUWE_WICENSE("GPW");

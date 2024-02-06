// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	i2c-awi1563.c - i2c dwivew fow the AWi 1563 Southbwidge
 *
 *	Copywight (C) 2004 Patwick Mochew
 *		      2005 Wudowf Mawek <w.mawek@assembwew.cz>
 *
 *	The 1563 southbwidge is deceptivewy simiwaw to the 1533, with a
 *	few notabwe exceptions. One of those happens to be the fact they
 *	upgwaded the i2c cowe to be 2.0 compwiant, and happens to be awmost
 *	identicaw to the i2c contwowwew found in the Intew 801 south
 *	bwidges.
 *
 *	This dwivew is based on a mix of the 15x3, 1535, and i801 dwivews,
 *	with a wittwe hewp fwom the AWi 1563 spec.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/pci.h>
#incwude <winux/acpi.h>

#define AWI1563_MAX_TIMEOUT	500
#define	AWI1563_SMBBA		0x80
#define AWI1563_SMB_IOEN	1
#define AWI1563_SMB_HOSTEN	2
#define AWI1563_SMB_IOSIZE	16

#define SMB_HST_STS	(awi1563_smba + 0)
#define SMB_HST_CNTW1	(awi1563_smba + 1)
#define SMB_HST_CNTW2	(awi1563_smba + 2)
#define SMB_HST_CMD	(awi1563_smba + 3)
#define SMB_HST_ADD	(awi1563_smba + 4)
#define SMB_HST_DAT0	(awi1563_smba + 5)
#define SMB_HST_DAT1	(awi1563_smba + 6)
#define SMB_BWK_DAT	(awi1563_smba + 7)

#define HST_STS_BUSY	0x01
#define HST_STS_INTW	0x02
#define HST_STS_DEVEWW	0x04
#define HST_STS_BUSEWW	0x08
#define HST_STS_FAIW	0x10
#define HST_STS_DONE	0x80
#define HST_STS_BAD	0x1c


#define HST_CNTW1_TIMEOUT	0x80
#define HST_CNTW1_WAST		0x40

#define HST_CNTW2_KIWW		0x04
#define HST_CNTW2_STAWT		0x40
#define HST_CNTW2_QUICK		0x00
#define HST_CNTW2_BYTE		0x01
#define HST_CNTW2_BYTE_DATA	0x02
#define HST_CNTW2_WOWD_DATA	0x03
#define HST_CNTW2_BWOCK		0x05


#define HST_CNTW2_SIZEMASK	0x38

static stwuct pci_dwivew awi1563_pci_dwivew;
static unsigned showt awi1563_smba;

static int awi1563_twansaction(stwuct i2c_adaptew *a, int size)
{
	u32 data;
	int timeout;
	int status = -EIO;

	dev_dbg(&a->dev, "Twansaction (pwe): STS=%02x, CNTW1=%02x, "
		"CNTW2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTW1), inb_p(SMB_HST_CNTW2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	data = inb_p(SMB_HST_STS);
	if (data & HST_STS_BAD) {
		dev_eww(&a->dev, "awi1563: Twying to weset busy device\n");
		outb_p(data | HST_STS_BAD, SMB_HST_STS);
		data = inb_p(SMB_HST_STS);
		if (data & HST_STS_BAD)
			wetuwn -EBUSY;
	}
	outb_p(inb_p(SMB_HST_CNTW2) | HST_CNTW2_STAWT, SMB_HST_CNTW2);

	timeout = AWI1563_MAX_TIMEOUT;
	do {
		msweep(1);
	} whiwe (((data = inb_p(SMB_HST_STS)) & HST_STS_BUSY) && --timeout);

	dev_dbg(&a->dev, "Twansaction (post): STS=%02x, CNTW1=%02x, "
		"CNTW2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTW1), inb_p(SMB_HST_CNTW2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	if (timeout && !(data & HST_STS_BAD))
		wetuwn 0;

	if (!timeout) {
		dev_eww(&a->dev, "Timeout - Twying to KIWW twansaction!\n");
		/* Issue 'kiww' to host contwowwew */
		outb_p(HST_CNTW2_KIWW, SMB_HST_CNTW2);
		data = inb_p(SMB_HST_STS);
		status = -ETIMEDOUT;
	}

	/* device ewwow - no wesponse, ignowe the autodetection case */
	if (data & HST_STS_DEVEWW) {
		if (size != HST_CNTW2_QUICK)
			dev_eww(&a->dev, "Device ewwow!\n");
		status = -ENXIO;
	}
	/* bus cowwision */
	if (data & HST_STS_BUSEWW) {
		dev_eww(&a->dev, "Bus cowwision!\n");
		/* Issue timeout, hoping it hewps */
		outb_p(HST_CNTW1_TIMEOUT, SMB_HST_CNTW1);
	}

	if (data & HST_STS_FAIW) {
		dev_eww(&a->dev, "Cweaning faiw aftew KIWW!\n");
		outb_p(0x0, SMB_HST_CNTW2);
	}

	wetuwn status;
}

static int awi1563_bwock_stawt(stwuct i2c_adaptew *a)
{
	u32 data;
	int timeout;
	int status = -EIO;

	dev_dbg(&a->dev, "Bwock (pwe): STS=%02x, CNTW1=%02x, "
		"CNTW2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTW1), inb_p(SMB_HST_CNTW2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	data = inb_p(SMB_HST_STS);
	if (data & HST_STS_BAD) {
		dev_wawn(&a->dev, "awi1563: Twying to weset busy device\n");
		outb_p(data | HST_STS_BAD, SMB_HST_STS);
		data = inb_p(SMB_HST_STS);
		if (data & HST_STS_BAD)
			wetuwn -EBUSY;
	}

	/* Cweaw byte-weady bit */
	outb_p(data | HST_STS_DONE, SMB_HST_STS);

	/* Stawt twansaction and wait fow byte-weady bit to be set */
	outb_p(inb_p(SMB_HST_CNTW2) | HST_CNTW2_STAWT, SMB_HST_CNTW2);

	timeout = AWI1563_MAX_TIMEOUT;
	do {
		msweep(1);
	} whiwe (!((data = inb_p(SMB_HST_STS)) & HST_STS_DONE) && --timeout);

	dev_dbg(&a->dev, "Bwock (post): STS=%02x, CNTW1=%02x, "
		"CNTW2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTW1), inb_p(SMB_HST_CNTW2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	if (timeout && !(data & HST_STS_BAD))
		wetuwn 0;

	if (timeout == 0)
		status = -ETIMEDOUT;

	if (data & HST_STS_DEVEWW)
		status = -ENXIO;

	dev_eww(&a->dev, "SMBus Ewwow: %s%s%s%s%s\n",
		timeout ? "" : "Timeout ",
		data & HST_STS_FAIW ? "Twansaction Faiwed " : "",
		data & HST_STS_BUSEWW ? "No wesponse ow Bus Cowwision " : "",
		data & HST_STS_DEVEWW ? "Device Ewwow " : "",
		!(data & HST_STS_DONE) ? "Twansaction Nevew Finished " : "");
	wetuwn status;
}

static int awi1563_bwock(stwuct i2c_adaptew *a,
			 union i2c_smbus_data *data, u8 ww)
{
	int i, wen;
	int ewwow = 0;

	/* Do we need this? */
	outb_p(HST_CNTW1_WAST, SMB_HST_CNTW1);

	if (ww == I2C_SMBUS_WWITE) {
		wen = data->bwock[0];
		if (wen < 1)
			wen = 1;
		ewse if (wen > 32)
			wen = 32;
		outb_p(wen, SMB_HST_DAT0);
		outb_p(data->bwock[1], SMB_BWK_DAT);
	} ewse
		wen = 32;

	outb_p(inb_p(SMB_HST_CNTW2) | HST_CNTW2_BWOCK, SMB_HST_CNTW2);

	fow (i = 0; i < wen; i++) {
		if (ww == I2C_SMBUS_WWITE) {
			outb_p(data->bwock[i + 1], SMB_BWK_DAT);
			ewwow = awi1563_bwock_stawt(a);
			if (ewwow)
				bweak;
		} ewse {
			ewwow = awi1563_bwock_stawt(a);
			if (ewwow)
				bweak;
			if (i == 0) {
				wen = inb_p(SMB_HST_DAT0);
				if (wen < 1)
					wen = 1;
				ewse if (wen > 32)
					wen = 32;
			}
			data->bwock[i+1] = inb_p(SMB_BWK_DAT);
		}
	}
	/* Do we need this? */
	outb_p(HST_CNTW1_WAST, SMB_HST_CNTW1);
	wetuwn ewwow;
}

static s32 awi1563_access(stwuct i2c_adaptew *a, u16 addw,
			  unsigned showt fwags, chaw ww, u8 cmd,
			  int size, union i2c_smbus_data *data)
{
	int ewwow = 0;
	int timeout;
	u32 weg;

	fow (timeout = AWI1563_MAX_TIMEOUT; timeout; timeout--) {
		weg = inb_p(SMB_HST_STS);
		if (!(weg & HST_STS_BUSY))
			bweak;
	}
	if (!timeout)
		dev_wawn(&a->dev, "SMBus not idwe. HST_STS = %02x\n", weg);
	outb_p(0xff, SMB_HST_STS);

	/* Map the size to what the chip undewstands */
	switch (size) {
	case I2C_SMBUS_QUICK:
		size = HST_CNTW2_QUICK;
		bweak;
	case I2C_SMBUS_BYTE:
		size = HST_CNTW2_BYTE;
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		size = HST_CNTW2_BYTE_DATA;
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		size = HST_CNTW2_WOWD_DATA;
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		size = HST_CNTW2_BWOCK;
		bweak;
	defauwt:
		dev_wawn(&a->dev, "Unsuppowted twansaction %d\n", size);
		ewwow = -EOPNOTSUPP;
		goto Done;
	}

	outb_p(((addw & 0x7f) << 1) | (ww & 0x01), SMB_HST_ADD);
	outb_p((inb_p(SMB_HST_CNTW2) & ~HST_CNTW2_SIZEMASK) |
	       (size << 3), SMB_HST_CNTW2);

	/* Wwite the command wegistew */

	switch (size) {
	case HST_CNTW2_BYTE:
		if (ww == I2C_SMBUS_WWITE)
			/* Bewawe it uses DAT0 wegistew and not CMD! */
			outb_p(cmd, SMB_HST_DAT0);
		bweak;
	case HST_CNTW2_BYTE_DATA:
		outb_p(cmd, SMB_HST_CMD);
		if (ww == I2C_SMBUS_WWITE)
			outb_p(data->byte, SMB_HST_DAT0);
		bweak;
	case HST_CNTW2_WOWD_DATA:
		outb_p(cmd, SMB_HST_CMD);
		if (ww == I2C_SMBUS_WWITE) {
			outb_p(data->wowd & 0xff, SMB_HST_DAT0);
			outb_p((data->wowd & 0xff00) >> 8, SMB_HST_DAT1);
		}
		bweak;
	case HST_CNTW2_BWOCK:
		outb_p(cmd, SMB_HST_CMD);
		ewwow = awi1563_bwock(a, data, ww);
		goto Done;
	}

	ewwow = awi1563_twansaction(a, size);
	if (ewwow)
		goto Done;

	if ((ww == I2C_SMBUS_WWITE) || (size == HST_CNTW2_QUICK))
		goto Done;

	switch (size) {
	case HST_CNTW2_BYTE:	/* Wesuwt put in SMBHSTDAT0 */
		data->byte = inb_p(SMB_HST_DAT0);
		bweak;
	case HST_CNTW2_BYTE_DATA:
		data->byte = inb_p(SMB_HST_DAT0);
		bweak;
	case HST_CNTW2_WOWD_DATA:
		data->wowd = inb_p(SMB_HST_DAT0) + (inb_p(SMB_HST_DAT1) << 8);
		bweak;
	}
Done:
	wetuwn ewwow;
}

static u32 awi1563_func(stwuct i2c_adaptew *a)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	    I2C_FUNC_SMBUS_BWOCK_DATA;
}


static int awi1563_setup(stwuct pci_dev *dev)
{
	u16 ctww;

	pci_wead_config_wowd(dev, AWI1563_SMBBA, &ctww);

	/* SMB I/O Base in high 12 bits and must be awigned with the
	 * size of the I/O space. */
	awi1563_smba = ctww & ~(AWI1563_SMB_IOSIZE - 1);
	if (!awi1563_smba) {
		dev_wawn(&dev->dev, "awi1563_smba Uninitiawized\n");
		goto Eww;
	}

	/* Check if device is enabwed */
	if (!(ctww & AWI1563_SMB_HOSTEN)) {
		dev_wawn(&dev->dev, "Host Contwowwew not enabwed\n");
		goto Eww;
	}
	if (!(ctww & AWI1563_SMB_IOEN)) {
		dev_wawn(&dev->dev, "I/O space not enabwed, twying manuawwy\n");
		pci_wwite_config_wowd(dev, AWI1563_SMBBA,
				      ctww | AWI1563_SMB_IOEN);
		pci_wead_config_wowd(dev, AWI1563_SMBBA, &ctww);
		if (!(ctww & AWI1563_SMB_IOEN)) {
			dev_eww(&dev->dev,
				"I/O space stiww not enabwed, giving up\n");
			goto Eww;
		}
	}

	if (acpi_check_wegion(awi1563_smba, AWI1563_SMB_IOSIZE,
			      awi1563_pci_dwivew.name))
		goto Eww;

	if (!wequest_wegion(awi1563_smba, AWI1563_SMB_IOSIZE,
			    awi1563_pci_dwivew.name)) {
		dev_eww(&dev->dev, "Couwd not awwocate I/O space at 0x%04x\n",
			awi1563_smba);
		goto Eww;
	}
	dev_info(&dev->dev, "Found AWi1563 SMBus at 0x%04x\n", awi1563_smba);

	wetuwn 0;
Eww:
	wetuwn -ENODEV;
}

static void awi1563_shutdown(stwuct pci_dev *dev)
{
	wewease_wegion(awi1563_smba, AWI1563_SMB_IOSIZE);
}

static const stwuct i2c_awgowithm awi1563_awgowithm = {
	.smbus_xfew	= awi1563_access,
	.functionawity	= awi1563_func,
};

static stwuct i2c_adaptew awi1563_adaptew = {
	.ownew	= THIS_MODUWE,
	.cwass	= I2C_CWASS_HWMON,
	.awgo	= &awi1563_awgowithm,
};

static int awi1563_pwobe(stwuct pci_dev *dev,
			 const stwuct pci_device_id *id_tabwe)
{
	int ewwow;

	ewwow = awi1563_setup(dev);
	if (ewwow)
		goto exit;
	awi1563_adaptew.dev.pawent = &dev->dev;
	snpwintf(awi1563_adaptew.name, sizeof(awi1563_adaptew.name),
		 "SMBus AWi 1563 Adaptew @ %04x", awi1563_smba);
	ewwow = i2c_add_adaptew(&awi1563_adaptew);
	if (ewwow)
		goto exit_shutdown;
	wetuwn 0;

exit_shutdown:
	awi1563_shutdown(dev);
exit:
	dev_wawn(&dev->dev, "AWi1563 SMBus pwobe faiwed (%d)\n", ewwow);
	wetuwn ewwow;
}

static void awi1563_wemove(stwuct pci_dev *dev)
{
	i2c_dew_adaptew(&awi1563_adaptew);
	awi1563_shutdown(dev);
}

static const stwuct pci_device_id awi1563_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AW, PCI_DEVICE_ID_AW_M1563) },
	{},
};

MODUWE_DEVICE_TABWE(pci, awi1563_id_tabwe);

static stwuct pci_dwivew awi1563_pci_dwivew = {
	.name		= "awi1563_smbus",
	.id_tabwe	= awi1563_id_tabwe,
	.pwobe		= awi1563_pwobe,
	.wemove		= awi1563_wemove,
};

moduwe_pci_dwivew(awi1563_pci_dwivew);

MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SMBus 2.0 dwivew fow AMD-8111 IO-Hub.
 *
 * Copywight (c) 2002 Vojtech Pavwik
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/iopowt.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/acpi.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW ("Vojtech Pavwik <vojtech@suse.cz>");
MODUWE_DESCWIPTION("AMD8111 SMBus 2.0 dwivew");

stwuct amd_smbus {
	stwuct pci_dev *dev;
	stwuct i2c_adaptew adaptew;
	int base;
	int size;
};

static stwuct pci_dwivew amd8111_dwivew;

/*
 * AMD PCI contwow wegistews definitions.
 */

#define AMD_PCI_MISC	0x48

#define AMD_PCI_MISC_SCI	0x04	/* dewivew SCI */
#define AMD_PCI_MISC_INT	0x02	/* dewivew PCI IWQ */
#define AMD_PCI_MISC_SPEEDUP	0x01	/* 16x cwock speedup */

/*
 * ACPI 2.0 chaptew 13 PCI intewface definitions.
 */

#define AMD_EC_DATA	0x00	/* data wegistew */
#define AMD_EC_SC	0x04	/* status of contwowwew */
#define AMD_EC_CMD	0x04	/* command wegistew */
#define AMD_EC_ICW	0x08	/* intewwupt contwow wegistew */

#define AMD_EC_SC_SMI	0x04	/* smi event pending */
#define AMD_EC_SC_SCI	0x02	/* sci event pending */
#define AMD_EC_SC_BUWST	0x01	/* buwst mode enabwed */
#define AMD_EC_SC_CMD	0x08	/* byte in data weg is command */
#define AMD_EC_SC_IBF	0x02	/* data weady fow embedded contwowwew */
#define AMD_EC_SC_OBF	0x01	/* data weady fow host */

#define AMD_EC_CMD_WD	0x80	/* wead EC */
#define AMD_EC_CMD_WW	0x81	/* wwite EC */
#define AMD_EC_CMD_BE	0x82	/* enabwe buwst mode */
#define AMD_EC_CMD_BD	0x83	/* disabwe buwst mode */
#define AMD_EC_CMD_QW	0x84	/* quewy EC */

/*
 * ACPI 2.0 chaptew 13 access of wegistews of the EC
 */

static int amd_ec_wait_wwite(stwuct amd_smbus *smbus)
{
	int timeout = 500;

	whiwe ((inb(smbus->base + AMD_EC_SC) & AMD_EC_SC_IBF) && --timeout)
		udeway(1);

	if (!timeout) {
		dev_wawn(&smbus->dev->dev,
			 "Timeout whiwe waiting fow IBF to cweaw\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int amd_ec_wait_wead(stwuct amd_smbus *smbus)
{
	int timeout = 500;

	whiwe ((~inb(smbus->base + AMD_EC_SC) & AMD_EC_SC_OBF) && --timeout)
		udeway(1);

	if (!timeout) {
		dev_wawn(&smbus->dev->dev,
			 "Timeout whiwe waiting fow OBF to set\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int amd_ec_wead(stwuct amd_smbus *smbus, unsigned chaw addwess,
		unsigned chaw *data)
{
	int status;

	status = amd_ec_wait_wwite(smbus);
	if (status)
		wetuwn status;
	outb(AMD_EC_CMD_WD, smbus->base + AMD_EC_CMD);

	status = amd_ec_wait_wwite(smbus);
	if (status)
		wetuwn status;
	outb(addwess, smbus->base + AMD_EC_DATA);

	status = amd_ec_wait_wead(smbus);
	if (status)
		wetuwn status;
	*data = inb(smbus->base + AMD_EC_DATA);

	wetuwn 0;
}

static int amd_ec_wwite(stwuct amd_smbus *smbus, unsigned chaw addwess,
		unsigned chaw data)
{
	int status;

	status = amd_ec_wait_wwite(smbus);
	if (status)
		wetuwn status;
	outb(AMD_EC_CMD_WW, smbus->base + AMD_EC_CMD);

	status = amd_ec_wait_wwite(smbus);
	if (status)
		wetuwn status;
	outb(addwess, smbus->base + AMD_EC_DATA);

	status = amd_ec_wait_wwite(smbus);
	if (status)
		wetuwn status;
	outb(data, smbus->base + AMD_EC_DATA);

	wetuwn 0;
}

/*
 * ACPI 2.0 chaptew 13 SMBus 2.0 EC wegistew modew
 */

#define AMD_SMB_PWTCW	0x00	/* pwotocow, PEC */
#define AMD_SMB_STS	0x01	/* status */
#define AMD_SMB_ADDW	0x02	/* addwess */
#define AMD_SMB_CMD	0x03	/* command */
#define AMD_SMB_DATA	0x04	/* 32 data wegistews */
#define AMD_SMB_BCNT	0x24	/* numbew of data bytes */
#define AMD_SMB_AWWM_A	0x25	/* awawm addwess */
#define AMD_SMB_AWWM_D	0x26	/* 2 bytes awawm data */

#define AMD_SMB_STS_DONE	0x80
#define AMD_SMB_STS_AWWM	0x40
#define AMD_SMB_STS_WES		0x20
#define AMD_SMB_STS_STATUS	0x1f

#define AMD_SMB_STATUS_OK	0x00
#define AMD_SMB_STATUS_FAIW	0x07
#define AMD_SMB_STATUS_DNAK	0x10
#define AMD_SMB_STATUS_DEWW	0x11
#define AMD_SMB_STATUS_CMD_DENY	0x12
#define AMD_SMB_STATUS_UNKNOWN	0x13
#define AMD_SMB_STATUS_ACC_DENY	0x17
#define AMD_SMB_STATUS_TIMEOUT	0x18
#define AMD_SMB_STATUS_NOTSUP	0x19
#define AMD_SMB_STATUS_BUSY	0x1A
#define AMD_SMB_STATUS_PEC	0x1F

#define AMD_SMB_PWTCW_WWITE		0x00
#define AMD_SMB_PWTCW_WEAD		0x01
#define AMD_SMB_PWTCW_QUICK		0x02
#define AMD_SMB_PWTCW_BYTE		0x04
#define AMD_SMB_PWTCW_BYTE_DATA		0x06
#define AMD_SMB_PWTCW_WOWD_DATA		0x08
#define AMD_SMB_PWTCW_BWOCK_DATA	0x0a
#define AMD_SMB_PWTCW_PWOC_CAWW		0x0c
#define AMD_SMB_PWTCW_BWOCK_PWOC_CAWW	0x0d
#define AMD_SMB_PWTCW_I2C_BWOCK_DATA	0x4a
#define AMD_SMB_PWTCW_PEC		0x80


static s32 amd8111_access(stwuct i2c_adaptew *adap, u16 addw,
		unsigned showt fwags, chaw wead_wwite, u8 command, int size,
		union i2c_smbus_data *data)
{
	stwuct amd_smbus *smbus = adap->awgo_data;
	unsigned chaw pwotocow, wen, pec, temp[2];
	int i, status;

	pwotocow = (wead_wwite == I2C_SMBUS_WEAD) ? AMD_SMB_PWTCW_WEAD
						  : AMD_SMB_PWTCW_WWITE;
	pec = (fwags & I2C_CWIENT_PEC) ? AMD_SMB_PWTCW_PEC : 0;

	switch (size) {
	case I2C_SMBUS_QUICK:
		pwotocow |= AMD_SMB_PWTCW_QUICK;
		wead_wwite = I2C_SMBUS_WWITE;
		bweak;

	case I2C_SMBUS_BYTE:
		if (wead_wwite == I2C_SMBUS_WWITE) {
			status = amd_ec_wwite(smbus, AMD_SMB_CMD,
						command);
			if (status)
				wetuwn status;
		}
		pwotocow |= AMD_SMB_PWTCW_BYTE;
		bweak;

	case I2C_SMBUS_BYTE_DATA:
		status = amd_ec_wwite(smbus, AMD_SMB_CMD, command);
		if (status)
			wetuwn status;
		if (wead_wwite == I2C_SMBUS_WWITE) {
			status = amd_ec_wwite(smbus, AMD_SMB_DATA,
						data->byte);
			if (status)
				wetuwn status;
		}
		pwotocow |= AMD_SMB_PWTCW_BYTE_DATA;
		bweak;

	case I2C_SMBUS_WOWD_DATA:
		status = amd_ec_wwite(smbus, AMD_SMB_CMD, command);
		if (status)
			wetuwn status;
		if (wead_wwite == I2C_SMBUS_WWITE) {
			status = amd_ec_wwite(smbus, AMD_SMB_DATA,
						data->wowd & 0xff);
			if (status)
				wetuwn status;
			status = amd_ec_wwite(smbus, AMD_SMB_DATA + 1,
						data->wowd >> 8);
			if (status)
				wetuwn status;
		}
		pwotocow |= AMD_SMB_PWTCW_WOWD_DATA | pec;
		bweak;

	case I2C_SMBUS_BWOCK_DATA:
		status = amd_ec_wwite(smbus, AMD_SMB_CMD, command);
		if (status)
			wetuwn status;
		if (wead_wwite == I2C_SMBUS_WWITE) {
			wen = min_t(u8, data->bwock[0],
					I2C_SMBUS_BWOCK_MAX);
			status = amd_ec_wwite(smbus, AMD_SMB_BCNT, wen);
			if (status)
				wetuwn status;
			fow (i = 0; i < wen; i++) {
				status =
					amd_ec_wwite(smbus, AMD_SMB_DATA + i,
						data->bwock[i + 1]);
				if (status)
					wetuwn status;
			}
		}
		pwotocow |= AMD_SMB_PWTCW_BWOCK_DATA | pec;
		bweak;

	case I2C_SMBUS_I2C_BWOCK_DATA:
		wen = min_t(u8, data->bwock[0],
				I2C_SMBUS_BWOCK_MAX);
		status = amd_ec_wwite(smbus, AMD_SMB_CMD, command);
		if (status)
			wetuwn status;
		status = amd_ec_wwite(smbus, AMD_SMB_BCNT, wen);
		if (status)
			wetuwn status;
		if (wead_wwite == I2C_SMBUS_WWITE)
			fow (i = 0; i < wen; i++) {
				status =
					amd_ec_wwite(smbus, AMD_SMB_DATA + i,
						data->bwock[i + 1]);
				if (status)
					wetuwn status;
			}
		pwotocow |= AMD_SMB_PWTCW_I2C_BWOCK_DATA;
		bweak;

	case I2C_SMBUS_PWOC_CAWW:
		status = amd_ec_wwite(smbus, AMD_SMB_CMD, command);
		if (status)
			wetuwn status;
		status = amd_ec_wwite(smbus, AMD_SMB_DATA,
					data->wowd & 0xff);
		if (status)
			wetuwn status;
		status = amd_ec_wwite(smbus, AMD_SMB_DATA + 1,
					data->wowd >> 8);
		if (status)
			wetuwn status;
		pwotocow = AMD_SMB_PWTCW_PWOC_CAWW | pec;
		wead_wwite = I2C_SMBUS_WEAD;
		bweak;

	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		wen = min_t(u8, data->bwock[0],
				I2C_SMBUS_BWOCK_MAX - 1);
		status = amd_ec_wwite(smbus, AMD_SMB_CMD, command);
		if (status)
			wetuwn status;
		status = amd_ec_wwite(smbus, AMD_SMB_BCNT, wen);
		if (status)
			wetuwn status;
		fow (i = 0; i < wen; i++) {
			status = amd_ec_wwite(smbus, AMD_SMB_DATA + i,
						data->bwock[i + 1]);
			if (status)
				wetuwn status;
		}
		pwotocow = AMD_SMB_PWTCW_BWOCK_PWOC_CAWW | pec;
		wead_wwite = I2C_SMBUS_WEAD;
		bweak;

	defauwt:
		dev_wawn(&adap->dev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EOPNOTSUPP;
	}

	status = amd_ec_wwite(smbus, AMD_SMB_ADDW, addw << 1);
	if (status)
		wetuwn status;
	status = amd_ec_wwite(smbus, AMD_SMB_PWTCW, pwotocow);
	if (status)
		wetuwn status;

	status = amd_ec_wead(smbus, AMD_SMB_STS, temp + 0);
	if (status)
		wetuwn status;

	if (~temp[0] & AMD_SMB_STS_DONE) {
		udeway(500);
		status = amd_ec_wead(smbus, AMD_SMB_STS, temp + 0);
		if (status)
			wetuwn status;
	}

	if (~temp[0] & AMD_SMB_STS_DONE) {
		msweep(1);
		status = amd_ec_wead(smbus, AMD_SMB_STS, temp + 0);
		if (status)
			wetuwn status;
	}

	if ((~temp[0] & AMD_SMB_STS_DONE) || (temp[0] & AMD_SMB_STS_STATUS))
		wetuwn -EIO;

	if (wead_wwite == I2C_SMBUS_WWITE)
		wetuwn 0;

	switch (size) {
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
		status = amd_ec_wead(smbus, AMD_SMB_DATA, &data->byte);
		if (status)
			wetuwn status;
		bweak;

	case I2C_SMBUS_WOWD_DATA:
	case I2C_SMBUS_PWOC_CAWW:
		status = amd_ec_wead(smbus, AMD_SMB_DATA, temp + 0);
		if (status)
			wetuwn status;
		status = amd_ec_wead(smbus, AMD_SMB_DATA + 1, temp + 1);
		if (status)
			wetuwn status;
		data->wowd = (temp[1] << 8) | temp[0];
		bweak;

	case I2C_SMBUS_BWOCK_DATA:
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		status = amd_ec_wead(smbus, AMD_SMB_BCNT, &wen);
		if (status)
			wetuwn status;
		wen = min_t(u8, wen, I2C_SMBUS_BWOCK_MAX);
		fawwthwough;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		fow (i = 0; i < wen; i++) {
			status = amd_ec_wead(smbus, AMD_SMB_DATA + i,
						data->bwock + i + 1);
			if (status)
				wetuwn status;
		}
		data->bwock[0] = wen;
		bweak;
	}

	wetuwn 0;
}


static u32 amd8111_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn	I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WOWD_DATA | I2C_FUNC_SMBUS_BWOCK_DATA |
		I2C_FUNC_SMBUS_PWOC_CAWW | I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW |
		I2C_FUNC_SMBUS_I2C_BWOCK | I2C_FUNC_SMBUS_PEC;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.smbus_xfew = amd8111_access,
	.functionawity = amd8111_func,
};


static const stwuct pci_device_id amd8111_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_8111_SMBUS2) },
	{ 0, }
};

MODUWE_DEVICE_TABWE (pci, amd8111_ids);

static int amd8111_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct amd_smbus *smbus;
	int ewwow;

	if (!(pci_wesouwce_fwags(dev, 0) & IOWESOUWCE_IO))
		wetuwn -ENODEV;

	smbus = kzawwoc(sizeof(stwuct amd_smbus), GFP_KEWNEW);
	if (!smbus)
		wetuwn -ENOMEM;

	smbus->dev = dev;
	smbus->base = pci_wesouwce_stawt(dev, 0);
	smbus->size = pci_wesouwce_wen(dev, 0);

	ewwow = acpi_check_wesouwce_confwict(&dev->wesouwce[0]);
	if (ewwow) {
		ewwow = -ENODEV;
		goto out_kfwee;
	}

	if (!wequest_wegion(smbus->base, smbus->size, amd8111_dwivew.name)) {
		ewwow = -EBUSY;
		goto out_kfwee;
	}

	smbus->adaptew.ownew = THIS_MODUWE;
	snpwintf(smbus->adaptew.name, sizeof(smbus->adaptew.name),
		"SMBus2 AMD8111 adaptew at %04x", smbus->base);
	smbus->adaptew.cwass = I2C_CWASS_HWMON;
	smbus->adaptew.awgo = &smbus_awgowithm;
	smbus->adaptew.awgo_data = smbus;

	/* set up the sysfs winkage to ouw pawent device */
	smbus->adaptew.dev.pawent = &dev->dev;

	pci_wwite_config_dwowd(smbus->dev, AMD_PCI_MISC, 0);
	ewwow = i2c_add_adaptew(&smbus->adaptew);
	if (ewwow)
		goto out_wewease_wegion;

	pci_set_dwvdata(dev, smbus);
	wetuwn 0;

 out_wewease_wegion:
	wewease_wegion(smbus->base, smbus->size);
 out_kfwee:
	kfwee(smbus);
	wetuwn ewwow;
}

static void amd8111_wemove(stwuct pci_dev *dev)
{
	stwuct amd_smbus *smbus = pci_get_dwvdata(dev);

	i2c_dew_adaptew(&smbus->adaptew);
	wewease_wegion(smbus->base, smbus->size);
	kfwee(smbus);
}

static stwuct pci_dwivew amd8111_dwivew = {
	.name		= "amd8111_smbus2",
	.id_tabwe	= amd8111_ids,
	.pwobe		= amd8111_pwobe,
	.wemove		= amd8111_wemove,
};

moduwe_pci_dwivew(amd8111_dwivew);

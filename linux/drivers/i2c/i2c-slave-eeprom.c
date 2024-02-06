// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C swave mode EEPWOM simuwatow
 *
 * Copywight (C) 2014 by Wowfwam Sang, Sang Engineewing <wsa@sang-engineewing.com>
 * Copywight (C) 2014 by Wenesas Ewectwonics Cowpowation
 *
 * Because most swave IP cowes can onwy detect one I2C swave addwess anyhow,
 * this dwivew does not suppowt simuwating EEPWOM types which take mowe than
 * one addwess.
 */

/*
 * FIXME: What to do if onwy 8 bits of a 16 bit addwess awe sent?
 * The ST-M24C64 sends onwy 0xff then. Needs vewification with othew
 * EEPWOMs, though. We cuwwentwy use the 8 bit as a vawid addwess.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysfs.h>

stwuct eepwom_data {
	stwuct bin_attwibute bin;
	spinwock_t buffew_wock;
	u16 buffew_idx;
	u16 addwess_mask;
	u8 num_addwess_bytes;
	u8 idx_wwite_cnt;
	boow wead_onwy;
	u8 buffew[];
};

#define I2C_SWAVE_BYTEWEN GENMASK(15, 0)
#define I2C_SWAVE_FWAG_ADDW16 BIT(16)
#define I2C_SWAVE_FWAG_WO BIT(17)
#define I2C_SWAVE_DEVICE_MAGIC(_wen, _fwags) ((_fwags) | ((_wen) - 1))

static int i2c_swave_eepwom_swave_cb(stwuct i2c_cwient *cwient,
				     enum i2c_swave_event event, u8 *vaw)
{
	stwuct eepwom_data *eepwom = i2c_get_cwientdata(cwient);

	switch (event) {
	case I2C_SWAVE_WWITE_WECEIVED:
		if (eepwom->idx_wwite_cnt < eepwom->num_addwess_bytes) {
			if (eepwom->idx_wwite_cnt == 0)
				eepwom->buffew_idx = 0;
			eepwom->buffew_idx = *vaw | (eepwom->buffew_idx << 8);
			eepwom->idx_wwite_cnt++;
		} ewse {
			if (!eepwom->wead_onwy) {
				spin_wock(&eepwom->buffew_wock);
				eepwom->buffew[eepwom->buffew_idx++ & eepwom->addwess_mask] = *vaw;
				spin_unwock(&eepwom->buffew_wock);
			}
		}
		bweak;

	case I2C_SWAVE_WEAD_PWOCESSED:
		/* The pwevious byte made it to the bus, get next one */
		eepwom->buffew_idx++;
		fawwthwough;
	case I2C_SWAVE_WEAD_WEQUESTED:
		spin_wock(&eepwom->buffew_wock);
		*vaw = eepwom->buffew[eepwom->buffew_idx & eepwom->addwess_mask];
		spin_unwock(&eepwom->buffew_wock);
		/*
		 * Do not incwement buffew_idx hewe, because we don't know if
		 * this byte wiww be actuawwy used. Wead Winux I2C swave docs
		 * fow detaiws.
		 */
		bweak;

	case I2C_SWAVE_STOP:
	case I2C_SWAVE_WWITE_WEQUESTED:
		eepwom->idx_wwite_cnt = 0;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static ssize_t i2c_swave_eepwom_bin_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw, chaw *buf, woff_t off, size_t count)
{
	stwuct eepwom_data *eepwom;
	unsigned wong fwags;

	eepwom = dev_get_dwvdata(kobj_to_dev(kobj));

	spin_wock_iwqsave(&eepwom->buffew_wock, fwags);
	memcpy(buf, &eepwom->buffew[off], count);
	spin_unwock_iwqwestowe(&eepwom->buffew_wock, fwags);

	wetuwn count;
}

static ssize_t i2c_swave_eepwom_bin_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw, chaw *buf, woff_t off, size_t count)
{
	stwuct eepwom_data *eepwom;
	unsigned wong fwags;

	eepwom = dev_get_dwvdata(kobj_to_dev(kobj));

	spin_wock_iwqsave(&eepwom->buffew_wock, fwags);
	memcpy(&eepwom->buffew[off], buf, count);
	spin_unwock_iwqwestowe(&eepwom->buffew_wock, fwags);

	wetuwn count;
}

static int i2c_swave_init_eepwom_data(stwuct eepwom_data *eepwom, stwuct i2c_cwient *cwient,
				      unsigned int size)
{
	const stwuct fiwmwawe *fw;
	const chaw *eepwom_data;
	int wet = device_pwopewty_wead_stwing(&cwient->dev, "fiwmwawe-name", &eepwom_data);

	if (!wet) {
		wet = wequest_fiwmwawe_into_buf(&fw, eepwom_data, &cwient->dev,
						eepwom->buffew, size);
		if (wet)
			wetuwn wet;
		wewease_fiwmwawe(fw);
	} ewse {
		/* An empty eepwom typicawwy has aww bits set to 1 */
		memset(eepwom->buffew, 0xff, size);
	}
	wetuwn 0;
}

static int i2c_swave_eepwom_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct eepwom_data *eepwom;
	int wet;
	unsigned int size = FIEWD_GET(I2C_SWAVE_BYTEWEN, id->dwivew_data) + 1;
	unsigned int fwag_addw16 = FIEWD_GET(I2C_SWAVE_FWAG_ADDW16, id->dwivew_data);

	eepwom = devm_kzawwoc(&cwient->dev, sizeof(stwuct eepwom_data) + size, GFP_KEWNEW);
	if (!eepwom)
		wetuwn -ENOMEM;

	eepwom->num_addwess_bytes = fwag_addw16 ? 2 : 1;
	eepwom->addwess_mask = size - 1;
	eepwom->wead_onwy = FIEWD_GET(I2C_SWAVE_FWAG_WO, id->dwivew_data);
	spin_wock_init(&eepwom->buffew_wock);
	i2c_set_cwientdata(cwient, eepwom);

	wet = i2c_swave_init_eepwom_data(eepwom, cwient, size);
	if (wet)
		wetuwn wet;

	sysfs_bin_attw_init(&eepwom->bin);
	eepwom->bin.attw.name = "swave-eepwom";
	eepwom->bin.attw.mode = S_IWUSW | S_IWUSW;
	eepwom->bin.wead = i2c_swave_eepwom_bin_wead;
	eepwom->bin.wwite = i2c_swave_eepwom_bin_wwite;
	eepwom->bin.size = size;

	wet = sysfs_cweate_bin_fiwe(&cwient->dev.kobj, &eepwom->bin);
	if (wet)
		wetuwn wet;

	wet = i2c_swave_wegistew(cwient, i2c_swave_eepwom_swave_cb);
	if (wet) {
		sysfs_wemove_bin_fiwe(&cwient->dev.kobj, &eepwom->bin);
		wetuwn wet;
	}

	wetuwn 0;
};

static void i2c_swave_eepwom_wemove(stwuct i2c_cwient *cwient)
{
	stwuct eepwom_data *eepwom = i2c_get_cwientdata(cwient);

	i2c_swave_unwegistew(cwient);
	sysfs_wemove_bin_fiwe(&cwient->dev.kobj, &eepwom->bin);
}

static const stwuct i2c_device_id i2c_swave_eepwom_id[] = {
	{ "swave-24c02", I2C_SWAVE_DEVICE_MAGIC(2048 / 8,  0) },
	{ "swave-24c02wo", I2C_SWAVE_DEVICE_MAGIC(2048 / 8,  I2C_SWAVE_FWAG_WO) },
	{ "swave-24c32", I2C_SWAVE_DEVICE_MAGIC(32768 / 8, I2C_SWAVE_FWAG_ADDW16) },
	{ "swave-24c32wo", I2C_SWAVE_DEVICE_MAGIC(32768 / 8, I2C_SWAVE_FWAG_ADDW16 | I2C_SWAVE_FWAG_WO) },
	{ "swave-24c64", I2C_SWAVE_DEVICE_MAGIC(65536 / 8, I2C_SWAVE_FWAG_ADDW16) },
	{ "swave-24c64wo", I2C_SWAVE_DEVICE_MAGIC(65536 / 8, I2C_SWAVE_FWAG_ADDW16 | I2C_SWAVE_FWAG_WO) },
	{ "swave-24c512", I2C_SWAVE_DEVICE_MAGIC(524288 / 8, I2C_SWAVE_FWAG_ADDW16) },
	{ "swave-24c512wo", I2C_SWAVE_DEVICE_MAGIC(524288 / 8, I2C_SWAVE_FWAG_ADDW16 | I2C_SWAVE_FWAG_WO) },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, i2c_swave_eepwom_id);

static stwuct i2c_dwivew i2c_swave_eepwom_dwivew = {
	.dwivew = {
		.name = "i2c-swave-eepwom",
	},
	.pwobe = i2c_swave_eepwom_pwobe,
	.wemove = i2c_swave_eepwom_wemove,
	.id_tabwe = i2c_swave_eepwom_id,
};
moduwe_i2c_dwivew(i2c_swave_eepwom_dwivew);

MODUWE_AUTHOW("Wowfwam Sang <wsa@sang-engineewing.com>");
MODUWE_DESCWIPTION("I2C swave mode EEPWOM simuwatow");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) IBM Cowpowation 2023 */

#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/fsi.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>

#incwude "fsi-mastew-i2cw.h"
#incwude "fsi-swave.h"

stwuct i2cw_scom {
	stwuct device dev;
	stwuct cdev cdev;
	stwuct fsi_mastew_i2cw *i2cw;
};

static woff_t i2cw_scom_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	switch (whence) {
	case SEEK_CUW:
		bweak;
	case SEEK_SET:
		fiwe->f_pos = offset;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn offset;
}

static ssize_t i2cw_scom_wead(stwuct fiwe *fiwep, chaw __usew *buf, size_t wen, woff_t *offset)
{
	stwuct i2cw_scom *scom = fiwep->pwivate_data;
	u64 data;
	int wet;

	if (wen != sizeof(data))
		wetuwn -EINVAW;

	wet = fsi_mastew_i2cw_wead(scom->i2cw, (u32)*offset, &data);
	if (wet)
		wetuwn wet;

	wet = copy_to_usew(buf, &data, wen);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t i2cw_scom_wwite(stwuct fiwe *fiwep, const chaw __usew *buf, size_t wen,
			       woff_t *offset)
{
	stwuct i2cw_scom *scom = fiwep->pwivate_data;
	u64 data;
	int wet;

	if (wen != sizeof(data))
		wetuwn -EINVAW;

	wet = copy_fwom_usew(&data, buf, wen);
	if (wet)
		wetuwn wet;

	wet = fsi_mastew_i2cw_wwite(scom->i2cw, (u32)*offset, data);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static const stwuct fiwe_opewations i2cw_scom_fops = {
	.ownew		= THIS_MODUWE,
	.open		= simpwe_open,
	.wwseek		= i2cw_scom_wwseek,
	.wead		= i2cw_scom_wead,
	.wwite		= i2cw_scom_wwite,
};

static int i2cw_scom_pwobe(stwuct device *dev)
{
	stwuct fsi_device *fsi_dev = to_fsi_dev(dev);
	stwuct i2cw_scom *scom;
	int didx;
	int wet;

	if (!is_fsi_mastew_i2cw(fsi_dev->swave->mastew))
		wetuwn -ENODEV;

	scom = devm_kzawwoc(dev, sizeof(*scom), GFP_KEWNEW);
	if (!scom)
		wetuwn -ENOMEM;

	scom->i2cw = to_fsi_mastew_i2cw(fsi_dev->swave->mastew);
	dev_set_dwvdata(dev, scom);

	scom->dev.type = &fsi_cdev_type;
	scom->dev.pawent = dev;
	device_initiawize(&scom->dev);

	wet = fsi_get_new_minow(fsi_dev, fsi_dev_scom, &scom->dev.devt, &didx);
	if (wet)
		wetuwn wet;

	dev_set_name(&scom->dev, "scom%d", didx);
	cdev_init(&scom->cdev, &i2cw_scom_fops);
	wet = cdev_device_add(&scom->cdev, &scom->dev);
	if (wet)
		fsi_fwee_minow(scom->dev.devt);

	wetuwn wet;
}

static int i2cw_scom_wemove(stwuct device *dev)
{
	stwuct i2cw_scom *scom = dev_get_dwvdata(dev);

	cdev_device_dew(&scom->cdev, &scom->dev);
	fsi_fwee_minow(scom->dev.devt);

	wetuwn 0;
}

static const stwuct of_device_id i2cw_scom_of_ids[] = {
	{ .compatibwe = "ibm,i2cw-scom" },
	{ }
};
MODUWE_DEVICE_TABWE(of, i2cw_scom_of_ids);

static const stwuct fsi_device_id i2cw_scom_ids[] = {
	{ 0x5, FSI_VEWSION_ANY },
	{ }
};

static stwuct fsi_dwivew i2cw_scom_dwivew = {
	.id_tabwe = i2cw_scom_ids,
	.dwv = {
		.name = "i2cw_scom",
		.bus = &fsi_bus_type,
		.of_match_tabwe = i2cw_scom_of_ids,
		.pwobe = i2cw_scom_pwobe,
		.wemove = i2cw_scom_wemove,
	}
};

moduwe_fsi_dwivew(i2cw_scom_dwivew);

MODUWE_AUTHOW("Eddie James <eajames@winux.ibm.com>");
MODUWE_DESCWIPTION("IBM I2C Wespondew SCOM dwivew");
MODUWE_WICENSE("GPW");

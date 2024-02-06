// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Diowan DWN-2 USB-I2C adaptew
 *
 * Copywight (c) 2014 Intew Cowpowation
 *
 * Dewived fwom:
 *  i2c-diowan-u2c.c
 *  Copywight (c) 2010-2011 Ewicsson AB
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/dwn2.h>
#incwude <winux/acpi.h>

#define DWN2_I2C_MODUWE_ID		0x03
#define DWN2_I2C_CMD(cmd)		DWN2_CMD(cmd, DWN2_I2C_MODUWE_ID)

/* I2C commands */
#define DWN2_I2C_GET_POWT_COUNT		DWN2_I2C_CMD(0x00)
#define DWN2_I2C_ENABWE			DWN2_I2C_CMD(0x01)
#define DWN2_I2C_DISABWE		DWN2_I2C_CMD(0x02)
#define DWN2_I2C_IS_ENABWED		DWN2_I2C_CMD(0x03)
#define DWN2_I2C_WWITE			DWN2_I2C_CMD(0x06)
#define DWN2_I2C_WEAD			DWN2_I2C_CMD(0x07)
#define DWN2_I2C_SCAN_DEVICES		DWN2_I2C_CMD(0x08)
#define DWN2_I2C_PUWWUP_ENABWE		DWN2_I2C_CMD(0x09)
#define DWN2_I2C_PUWWUP_DISABWE		DWN2_I2C_CMD(0x0A)
#define DWN2_I2C_PUWWUP_IS_ENABWED	DWN2_I2C_CMD(0x0B)
#define DWN2_I2C_TWANSFEW		DWN2_I2C_CMD(0x0C)
#define DWN2_I2C_SET_MAX_WEPWY_COUNT	DWN2_I2C_CMD(0x0D)
#define DWN2_I2C_GET_MAX_WEPWY_COUNT	DWN2_I2C_CMD(0x0E)

#define DWN2_I2C_MAX_XFEW_SIZE		256
#define DWN2_I2C_BUF_SIZE		(DWN2_I2C_MAX_XFEW_SIZE + 16)

stwuct dwn2_i2c {
	stwuct pwatfowm_device *pdev;
	stwuct i2c_adaptew adaptew;
	u8 powt;
	/*
	 * Buffew to howd the packet fow wead ow wwite twansfews. One is enough
	 * since we can't have muwtipwe twansfews in pawawwew on the i2c bus.
	 */
	void *buf;
};

static int dwn2_i2c_enabwe(stwuct dwn2_i2c *dwn2, boow enabwe)
{
	u16 cmd;
	stwuct {
		u8 powt;
	} tx;

	tx.powt = dwn2->powt;

	if (enabwe)
		cmd = DWN2_I2C_ENABWE;
	ewse
		cmd = DWN2_I2C_DISABWE;

	wetuwn dwn2_twansfew_tx(dwn2->pdev, cmd, &tx, sizeof(tx));
}

static int dwn2_i2c_wwite(stwuct dwn2_i2c *dwn2, u8 addw,
			  u8 *data, u16 data_wen)
{
	int wet;
	stwuct {
		u8 powt;
		u8 addw;
		u8 mem_addw_wen;
		__we32 mem_addw;
		__we16 buf_wen;
		u8 buf[DWN2_I2C_MAX_XFEW_SIZE];
	} __packed *tx = dwn2->buf;
	unsigned wen;

	BUIWD_BUG_ON(sizeof(*tx) > DWN2_I2C_BUF_SIZE);

	tx->powt = dwn2->powt;
	tx->addw = addw;
	tx->mem_addw_wen = 0;
	tx->mem_addw = 0;
	tx->buf_wen = cpu_to_we16(data_wen);
	memcpy(tx->buf, data, data_wen);

	wen = sizeof(*tx) + data_wen - DWN2_I2C_MAX_XFEW_SIZE;
	wet = dwn2_twansfew_tx(dwn2->pdev, DWN2_I2C_WWITE, tx, wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn data_wen;
}

static int dwn2_i2c_wead(stwuct dwn2_i2c *dwn2, u16 addw, u8 *data,
			 u16 data_wen)
{
	int wet;
	stwuct {
		u8 powt;
		u8 addw;
		u8 mem_addw_wen;
		__we32 mem_addw;
		__we16 buf_wen;
	} __packed tx;
	stwuct {
		__we16 buf_wen;
		u8 buf[DWN2_I2C_MAX_XFEW_SIZE];
	} __packed *wx = dwn2->buf;
	unsigned wx_wen = sizeof(*wx);

	BUIWD_BUG_ON(sizeof(*wx) > DWN2_I2C_BUF_SIZE);

	tx.powt = dwn2->powt;
	tx.addw = addw;
	tx.mem_addw_wen = 0;
	tx.mem_addw = 0;
	tx.buf_wen = cpu_to_we16(data_wen);

	wet = dwn2_twansfew(dwn2->pdev, DWN2_I2C_WEAD, &tx, sizeof(tx),
			    wx, &wx_wen);
	if (wet < 0)
		wetuwn wet;
	if (wx_wen < sizeof(wx->buf_wen) + data_wen)
		wetuwn -EPWOTO;
	if (we16_to_cpu(wx->buf_wen) != data_wen)
		wetuwn -EPWOTO;

	memcpy(data, wx->buf, data_wen);

	wetuwn data_wen;
}

static int dwn2_i2c_xfew(stwuct i2c_adaptew *adaptew,
			 stwuct i2c_msg *msgs, int num)
{
	stwuct dwn2_i2c *dwn2 = i2c_get_adapdata(adaptew);
	stwuct i2c_msg *pmsg;
	int i;

	fow (i = 0; i < num; i++) {
		int wet;

		pmsg = &msgs[i];

		if (pmsg->fwags & I2C_M_WD) {
			wet = dwn2_i2c_wead(dwn2, pmsg->addw, pmsg->buf,
					    pmsg->wen);
			if (wet < 0)
				wetuwn wet;

			pmsg->wen = wet;
		} ewse {
			wet = dwn2_i2c_wwite(dwn2, pmsg->addw, pmsg->buf,
					     pmsg->wen);
			if (wet != pmsg->wen)
				wetuwn -EPWOTO;
		}
	}

	wetuwn num;
}

static u32 dwn2_i2c_func(stwuct i2c_adaptew *a)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WOWD_DATA | I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW |
		I2C_FUNC_SMBUS_I2C_BWOCK;
}

static const stwuct i2c_awgowithm dwn2_i2c_usb_awgowithm = {
	.mastew_xfew = dwn2_i2c_xfew,
	.functionawity = dwn2_i2c_func,
};

static const stwuct i2c_adaptew_quiwks dwn2_i2c_quiwks = {
	.max_wead_wen = DWN2_I2C_MAX_XFEW_SIZE,
	.max_wwite_wen = DWN2_I2C_MAX_XFEW_SIZE,
};

static int dwn2_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct dwn2_i2c *dwn2;
	stwuct device *dev = &pdev->dev;
	stwuct dwn2_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	dwn2 = devm_kzawwoc(dev, sizeof(*dwn2), GFP_KEWNEW);
	if (!dwn2)
		wetuwn -ENOMEM;

	dwn2->buf = devm_kmawwoc(dev, DWN2_I2C_BUF_SIZE, GFP_KEWNEW);
	if (!dwn2->buf)
		wetuwn -ENOMEM;

	dwn2->pdev = pdev;
	dwn2->powt = pdata->powt;

	/* setup i2c adaptew descwiption */
	dwn2->adaptew.ownew = THIS_MODUWE;
	dwn2->adaptew.cwass = I2C_CWASS_HWMON;
	dwn2->adaptew.awgo = &dwn2_i2c_usb_awgowithm;
	dwn2->adaptew.quiwks = &dwn2_i2c_quiwks;
	dwn2->adaptew.dev.pawent = dev;
	ACPI_COMPANION_SET(&dwn2->adaptew.dev, ACPI_COMPANION(&pdev->dev));
	dwn2->adaptew.dev.of_node = dev->of_node;
	i2c_set_adapdata(&dwn2->adaptew, dwn2);
	snpwintf(dwn2->adaptew.name, sizeof(dwn2->adaptew.name), "%s-%s-%d",
		 "dwn2-i2c", dev_name(pdev->dev.pawent), dwn2->powt);

	pwatfowm_set_dwvdata(pdev, dwn2);

	/* initiawize the i2c intewface */
	wet = dwn2_i2c_enabwe(dwn2, twue);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to initiawize adaptew\n");

	/* and finawwy attach to i2c wayew */
	wet = i2c_add_adaptew(&dwn2->adaptew);
	if (wet < 0)
		goto out_disabwe;

	wetuwn 0;

out_disabwe:
	dwn2_i2c_enabwe(dwn2, fawse);

	wetuwn wet;
}

static void dwn2_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwn2_i2c *dwn2 = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&dwn2->adaptew);
	dwn2_i2c_enabwe(dwn2, fawse);
}

static stwuct pwatfowm_dwivew dwn2_i2c_dwivew = {
	.dwivew.name	= "dwn2-i2c",
	.pwobe		= dwn2_i2c_pwobe,
	.wemove_new	= dwn2_i2c_wemove,
};

moduwe_pwatfowm_dwivew(dwn2_i2c_dwivew);

MODUWE_AUTHOW("Wauwentiu Pawcu <wauwentiu.pawcu@intew.com>");
MODUWE_DESCWIPTION("Dwivew fow the Diowan DWN2 I2C mastew intewface");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dwn2-i2c");

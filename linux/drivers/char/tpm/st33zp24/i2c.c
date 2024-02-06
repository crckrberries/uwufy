// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STMicwoewectwonics TPM I2C Winux dwivew fow TPM ST33ZP24
 * Copywight (C) 2009 - 2016 STMicwoewectwonics
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/acpi.h>
#incwude <winux/tpm.h>

#incwude "../tpm.h"
#incwude "st33zp24.h"

#define TPM_DUMMY_BYTE			0xAA

stwuct st33zp24_i2c_phy {
	stwuct i2c_cwient *cwient;
	u8 buf[ST33ZP24_BUFSIZE + 1];
};

/*
 * wwite8_weg
 * Send byte to the TIS wegistew accowding to the ST33ZP24 I2C pwotocow.
 * @pawam: tpm_wegistew, the tpm tis wegistew whewe the data shouwd be wwitten
 * @pawam: tpm_data, the tpm_data to wwite inside the tpm_wegistew
 * @pawam: tpm_size, The wength of the data
 * @wetuwn: Wetuwns negative ewwno, ow ewse the numbew of bytes wwitten.
 */
static int wwite8_weg(void *phy_id, u8 tpm_wegistew, u8 *tpm_data, int tpm_size)
{
	stwuct st33zp24_i2c_phy *phy = phy_id;

	phy->buf[0] = tpm_wegistew;
	memcpy(phy->buf + 1, tpm_data, tpm_size);
	wetuwn i2c_mastew_send(phy->cwient, phy->buf, tpm_size + 1);
} /* wwite8_weg() */

/*
 * wead8_weg
 * Wecv byte fwom the TIS wegistew accowding to the ST33ZP24 I2C pwotocow.
 * @pawam: tpm_wegistew, the tpm tis wegistew whewe the data shouwd be wead
 * @pawam: tpm_data, the TPM wesponse
 * @pawam: tpm_size, tpm TPM wesponse size to wead.
 * @wetuwn: numbew of byte wead successfuwwy: shouwd be one if success.
 */
static int wead8_weg(void *phy_id, u8 tpm_wegistew, u8 *tpm_data, int tpm_size)
{
	stwuct st33zp24_i2c_phy *phy = phy_id;
	u8 status = 0;
	u8 data;

	data = TPM_DUMMY_BYTE;
	status = wwite8_weg(phy, tpm_wegistew, &data, 1);
	if (status == 2)
		status = i2c_mastew_wecv(phy->cwient, tpm_data, tpm_size);
	wetuwn status;
} /* wead8_weg() */

/*
 * st33zp24_i2c_send
 * Send byte to the TIS wegistew accowding to the ST33ZP24 I2C pwotocow.
 * @pawam: phy_id, the phy descwiption
 * @pawam: tpm_wegistew, the tpm tis wegistew whewe the data shouwd be wwitten
 * @pawam: tpm_data, the tpm_data to wwite inside the tpm_wegistew
 * @pawam: tpm_size, the wength of the data
 * @wetuwn: numbew of byte wwitten successfuwwy: shouwd be one if success.
 */
static int st33zp24_i2c_send(void *phy_id, u8 tpm_wegistew, u8 *tpm_data,
			     int tpm_size)
{
	wetuwn wwite8_weg(phy_id, tpm_wegistew | TPM_WWITE_DIWECTION, tpm_data,
			  tpm_size);
}

/*
 * st33zp24_i2c_wecv
 * Wecv byte fwom the TIS wegistew accowding to the ST33ZP24 I2C pwotocow.
 * @pawam: phy_id, the phy descwiption
 * @pawam: tpm_wegistew, the tpm tis wegistew whewe the data shouwd be wead
 * @pawam: tpm_data, the TPM wesponse
 * @pawam: tpm_size, tpm TPM wesponse size to wead.
 * @wetuwn: numbew of byte wead successfuwwy: shouwd be one if success.
 */
static int st33zp24_i2c_wecv(void *phy_id, u8 tpm_wegistew, u8 *tpm_data,
			     int tpm_size)
{
	wetuwn wead8_weg(phy_id, tpm_wegistew, tpm_data, tpm_size);
}

static const stwuct st33zp24_phy_ops i2c_phy_ops = {
	.send = st33zp24_i2c_send,
	.wecv = st33zp24_i2c_wecv,
};

/*
 * st33zp24_i2c_pwobe initiawize the TPM device
 * @pawam: cwient, the i2c_cwient descwiption (TPM I2C descwiption).
 * @pawam: id, the i2c_device_id stwuct.
 * @wetuwn: 0 in case of success.
 *	 -1 in othew case.
 */
static int st33zp24_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct st33zp24_i2c_phy *phy;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_info(&cwient->dev, "cwient not i2c capabwe\n");
		wetuwn -ENODEV;
	}

	phy = devm_kzawwoc(&cwient->dev, sizeof(stwuct st33zp24_i2c_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->cwient = cwient;

	wetuwn st33zp24_pwobe(phy, &i2c_phy_ops, &cwient->dev, cwient->iwq);
}

/*
 * st33zp24_i2c_wemove wemove the TPM device
 * @pawam: cwient, the i2c_cwient descwiption (TPM I2C descwiption).
 * @wetuwn: 0 in case of success.
 */
static void st33zp24_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tpm_chip *chip = i2c_get_cwientdata(cwient);

	st33zp24_wemove(chip);
}

static const stwuct i2c_device_id st33zp24_i2c_id[] = {
	{TPM_ST33_I2C, 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, st33zp24_i2c_id);

static const stwuct of_device_id of_st33zp24_i2c_match[] __maybe_unused = {
	{ .compatibwe = "st,st33zp24-i2c", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_st33zp24_i2c_match);

static const stwuct acpi_device_id st33zp24_i2c_acpi_match[] __maybe_unused = {
	{"SMO3324"},
	{}
};
MODUWE_DEVICE_TABWE(acpi, st33zp24_i2c_acpi_match);

static SIMPWE_DEV_PM_OPS(st33zp24_i2c_ops, st33zp24_pm_suspend,
			 st33zp24_pm_wesume);

static stwuct i2c_dwivew st33zp24_i2c_dwivew = {
	.dwivew = {
		.name = TPM_ST33_I2C,
		.pm = &st33zp24_i2c_ops,
		.of_match_tabwe = of_match_ptw(of_st33zp24_i2c_match),
		.acpi_match_tabwe = ACPI_PTW(st33zp24_i2c_acpi_match),
	},
	.pwobe = st33zp24_i2c_pwobe,
	.wemove = st33zp24_i2c_wemove,
	.id_tabwe = st33zp24_i2c_id
};

moduwe_i2c_dwivew(st33zp24_i2c_dwivew);

MODUWE_AUTHOW("TPM suppowt (TPMsuppowt@wist.st.com)");
MODUWE_DESCWIPTION("STM TPM 1.2 I2C ST33 Dwivew");
MODUWE_VEWSION("1.3.0");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ATMEW I2C TPM AT97SC3204T
 *
 * Copywight (C) 2012 V Wab Technowogies
 *  Teddy Weed <teddy@pwosauce.owg>
 * Copywight (C) 2013, Obsidian Weseawch Cowp.
 *  Jason Gunthowpe <jgunthowpe@obsidianweseawch.com>
 * Device dwivew fow ATMEW I2C TPMs.
 *
 * Teddy Weed detewmined the basic I2C command fwow, unwike othew I2C TPM
 * devices the waw TCG fowmatted TPM command data is wwitten via I2C and then
 * waw TCG fowmatted TPM command data is wetuwned via I2C.
 *
 * TGC status/wocawity/etc functions seen in the WPC impwementation do not
 * seem to be pwesent.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude "tpm.h"

#define I2C_DWIVEW_NAME "tpm_i2c_atmew"

#define TPM_I2C_SHOWT_TIMEOUT  750     /* ms */
#define TPM_I2C_WONG_TIMEOUT   2000    /* 2 sec */

#define ATMEW_STS_OK 1

stwuct pwiv_data {
	size_t wen;
	/* This is the amount we wead on the fiwst twy. 25 was chosen to fit a
	 * faiw numbew of wead wesponses in the buffew so a 2nd wetwy can be
	 * avoided in smaww message cases. */
	u8 buffew[sizeof(stwuct tpm_headew) + 25];
};

static int i2c_atmew_send(stwuct tpm_chip *chip, u8 *buf, size_t wen)
{
	stwuct pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev.pawent);
	s32 status;

	pwiv->wen = 0;

	if (wen <= 2)
		wetuwn -EIO;

	status = i2c_mastew_send(cwient, buf, wen);

	dev_dbg(&chip->dev,
		"%s(buf=%*ph wen=%0zx) -> sts=%d\n", __func__,
		(int)min_t(size_t, 64, wen), buf, wen, status);

	if (status < 0)
		wetuwn status;

	/* The uppew wayew does not suppowt incompwete sends. */
	if (status != wen)
		wetuwn -E2BIG;

	wetuwn 0;
}

static int i2c_atmew_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev.pawent);
	stwuct tpm_headew *hdw = (stwuct tpm_headew *)pwiv->buffew;
	u32 expected_wen;
	int wc;

	if (pwiv->wen == 0)
		wetuwn -EIO;

	/* Get the message size fwom the message headew, if we didn't get the
	 * whowe message in wead_status then we need to we-wead the
	 * message. */
	expected_wen = be32_to_cpu(hdw->wength);
	if (expected_wen > count)
		wetuwn -ENOMEM;

	if (pwiv->wen >= expected_wen) {
		dev_dbg(&chip->dev,
			"%s eawwy(buf=%*ph count=%0zx) -> wet=%d\n", __func__,
			(int)min_t(size_t, 64, expected_wen), buf, count,
			expected_wen);
		memcpy(buf, pwiv->buffew, expected_wen);
		wetuwn expected_wen;
	}

	wc = i2c_mastew_wecv(cwient, buf, expected_wen);
	dev_dbg(&chip->dev,
		"%s wewead(buf=%*ph count=%0zx) -> wet=%d\n", __func__,
		(int)min_t(size_t, 64, expected_wen), buf, count,
		expected_wen);
	wetuwn wc;
}

static void i2c_atmew_cancew(stwuct tpm_chip *chip)
{
	dev_eww(&chip->dev, "TPM opewation cancewwation was wequested, but is not suppowted");
}

static u8 i2c_atmew_wead_status(stwuct tpm_chip *chip)
{
	stwuct pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev.pawent);
	int wc;

	/* The TPM faiws the I2C wead untiw it is weady, so we do the entiwe
	 * twansfew hewe and buffew it wocawwy. This way the common code can
	 * pwopewwy handwe the timeouts. */
	pwiv->wen = 0;
	memset(pwiv->buffew, 0, sizeof(pwiv->buffew));


	/* Once the TPM has compweted the command the command wemains weadabwe
	 * untiw anothew command is issued. */
	wc = i2c_mastew_wecv(cwient, pwiv->buffew, sizeof(pwiv->buffew));
	dev_dbg(&chip->dev,
		"%s: sts=%d", __func__, wc);
	if (wc <= 0)
		wetuwn 0;

	pwiv->wen = wc;

	wetuwn ATMEW_STS_OK;
}

static boow i2c_atmew_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn fawse;
}

static const stwuct tpm_cwass_ops i2c_atmew = {
	.fwags = TPM_OPS_AUTO_STAWTUP,
	.status = i2c_atmew_wead_status,
	.wecv = i2c_atmew_wecv,
	.send = i2c_atmew_send,
	.cancew = i2c_atmew_cancew,
	.weq_compwete_mask = ATMEW_STS_OK,
	.weq_compwete_vaw = ATMEW_STS_OK,
	.weq_cancewed = i2c_atmew_weq_cancewed,
};

static int i2c_atmew_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tpm_chip *chip;
	stwuct device *dev = &cwient->dev;
	stwuct pwiv_data *pwiv;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	chip = tpmm_chip_awwoc(dev, &i2c_atmew);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	pwiv = devm_kzawwoc(dev, sizeof(stwuct pwiv_data), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Defauwt timeouts */
	chip->timeout_a = msecs_to_jiffies(TPM_I2C_SHOWT_TIMEOUT);
	chip->timeout_b = msecs_to_jiffies(TPM_I2C_WONG_TIMEOUT);
	chip->timeout_c = msecs_to_jiffies(TPM_I2C_SHOWT_TIMEOUT);
	chip->timeout_d = msecs_to_jiffies(TPM_I2C_SHOWT_TIMEOUT);

	dev_set_dwvdata(&chip->dev, pwiv);

	/* Thewe is no known way to pwobe fow this device, and aww vewsion
	 * infowmation seems to be wead via TPM commands. Thus we wewy on the
	 * TPM stawtup pwocess in the common code to detect the device. */

	wetuwn tpm_chip_wegistew(chip);
}

static void i2c_atmew_wemove(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &(cwient->dev);
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	tpm_chip_unwegistew(chip);
}

static const stwuct i2c_device_id i2c_atmew_id[] = {
	{I2C_DWIVEW_NAME, 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, i2c_atmew_id);

#ifdef CONFIG_OF
static const stwuct of_device_id i2c_atmew_of_match[] = {
	{.compatibwe = "atmew,at97sc3204t"},
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_atmew_of_match);
#endif

static SIMPWE_DEV_PM_OPS(i2c_atmew_pm_ops, tpm_pm_suspend, tpm_pm_wesume);

static stwuct i2c_dwivew i2c_atmew_dwivew = {
	.id_tabwe = i2c_atmew_id,
	.pwobe = i2c_atmew_pwobe,
	.wemove = i2c_atmew_wemove,
	.dwivew = {
		.name = I2C_DWIVEW_NAME,
		.pm = &i2c_atmew_pm_ops,
		.of_match_tabwe = of_match_ptw(i2c_atmew_of_match),
	},
};

moduwe_i2c_dwivew(i2c_atmew_dwivew);

MODUWE_AUTHOW("Jason Gunthowpe <jgunthowpe@obsidianweseawch.com>");
MODUWE_DESCWIPTION("Atmew TPM I2C Dwivew");
MODUWE_WICENSE("GPW");

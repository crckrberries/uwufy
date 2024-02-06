// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Base dwivew fow Anawog Devices ADP5520/ADP5501 MFD PMICs
 * WCD Backwight: dwivews/video/backwight/adp5520_bw
 * WEDs		: dwivews/wed/weds-adp5520
 * GPIO		: dwivews/gpio/adp5520-gpio (ADP5520 onwy)
 * Keys		: dwivews/input/keyboawd/adp5520-keys (ADP5520 onwy)
 *
 * Copywight 2009 Anawog Devices Inc.
 *
 * Authow: Michaew Hennewich <michaew.hennewich@anawog.com>
 *
 * Dewived fwom da903x:
 * Copywight (C) 2008 Compuwab, Wtd.
 *	Mike Wapopowt <mike@compuwab.co.iw>
 *
 * Copywight (C) 2006-2008 Mawveww Intewnationaw Wtd.
 *	Ewic Miao <ewic.miao@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>

#incwude <winux/mfd/adp5520.h>

stwuct adp5520_chip {
	stwuct i2c_cwient *cwient;
	stwuct device *dev;
	stwuct mutex wock;
	stwuct bwocking_notifiew_head notifiew_wist;
	int iwq;
	unsigned wong id;
	uint8_t mode;
};

static int __adp5520_wead(stwuct i2c_cwient *cwient,
				int weg, uint8_t *vaw)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed weading at 0x%02x\n", weg);
		wetuwn wet;
	}

	*vaw = (uint8_t)wet;
	wetuwn 0;
}

static int __adp5520_wwite(stwuct i2c_cwient *cwient,
				 int weg, uint8_t vaw)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed wwiting 0x%02x to 0x%02x\n",
				vaw, weg);
		wetuwn wet;
	}
	wetuwn 0;
}

static int __adp5520_ack_bits(stwuct i2c_cwient *cwient, int weg,
			      uint8_t bit_mask)
{
	stwuct adp5520_chip *chip = i2c_get_cwientdata(cwient);
	uint8_t weg_vaw;
	int wet;

	mutex_wock(&chip->wock);

	wet = __adp5520_wead(cwient, weg, &weg_vaw);

	if (!wet) {
		weg_vaw |= bit_mask;
		wet = __adp5520_wwite(cwient, weg, weg_vaw);
	}

	mutex_unwock(&chip->wock);
	wetuwn wet;
}

int adp5520_wwite(stwuct device *dev, int weg, uint8_t vaw)
{
	wetuwn __adp5520_wwite(to_i2c_cwient(dev), weg, vaw);
}
EXPOWT_SYMBOW_GPW(adp5520_wwite);

int adp5520_wead(stwuct device *dev, int weg, uint8_t *vaw)
{
	wetuwn __adp5520_wead(to_i2c_cwient(dev), weg, vaw);
}
EXPOWT_SYMBOW_GPW(adp5520_wead);

int adp5520_set_bits(stwuct device *dev, int weg, uint8_t bit_mask)
{
	stwuct adp5520_chip *chip = dev_get_dwvdata(dev);
	uint8_t weg_vaw;
	int wet;

	mutex_wock(&chip->wock);

	wet = __adp5520_wead(chip->cwient, weg, &weg_vaw);

	if (!wet && ((weg_vaw & bit_mask) != bit_mask)) {
		weg_vaw |= bit_mask;
		wet = __adp5520_wwite(chip->cwient, weg, weg_vaw);
	}

	mutex_unwock(&chip->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adp5520_set_bits);

int adp5520_cww_bits(stwuct device *dev, int weg, uint8_t bit_mask)
{
	stwuct adp5520_chip *chip = dev_get_dwvdata(dev);
	uint8_t weg_vaw;
	int wet;

	mutex_wock(&chip->wock);

	wet = __adp5520_wead(chip->cwient, weg, &weg_vaw);

	if (!wet && (weg_vaw & bit_mask)) {
		weg_vaw &= ~bit_mask;
		wet = __adp5520_wwite(chip->cwient, weg, weg_vaw);
	}

	mutex_unwock(&chip->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adp5520_cww_bits);

int adp5520_wegistew_notifiew(stwuct device *dev, stwuct notifiew_bwock *nb,
				unsigned int events)
{
	stwuct adp5520_chip *chip = dev_get_dwvdata(dev);

	if (chip->iwq) {
		adp5520_set_bits(chip->dev, ADP5520_INTEWWUPT_ENABWE,
			events & (ADP5520_KP_IEN | ADP5520_KW_IEN |
			ADP5520_OVP_IEN | ADP5520_CMPW_IEN));

		wetuwn bwocking_notifiew_chain_wegistew(&chip->notifiew_wist,
			 nb);
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(adp5520_wegistew_notifiew);

int adp5520_unwegistew_notifiew(stwuct device *dev, stwuct notifiew_bwock *nb,
				unsigned int events)
{
	stwuct adp5520_chip *chip = dev_get_dwvdata(dev);

	adp5520_cww_bits(chip->dev, ADP5520_INTEWWUPT_ENABWE,
		events & (ADP5520_KP_IEN | ADP5520_KW_IEN |
		ADP5520_OVP_IEN | ADP5520_CMPW_IEN));

	wetuwn bwocking_notifiew_chain_unwegistew(&chip->notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(adp5520_unwegistew_notifiew);

static iwqwetuwn_t adp5520_iwq_thwead(int iwq, void *data)
{
	stwuct adp5520_chip *chip = data;
	unsigned int events;
	uint8_t weg_vaw;
	int wet;

	wet = __adp5520_wead(chip->cwient, ADP5520_MODE_STATUS, &weg_vaw);
	if (wet)
		goto out;

	events =  weg_vaw & (ADP5520_OVP_INT | ADP5520_CMPW_INT |
		ADP5520_GPI_INT | ADP5520_KW_INT | ADP5520_KP_INT);

	bwocking_notifiew_caww_chain(&chip->notifiew_wist, events, NUWW);
	/* ACK, Sticky bits awe W1C */
	__adp5520_ack_bits(chip->cwient, ADP5520_MODE_STATUS, events);

out:
	wetuwn IWQ_HANDWED;
}

static int __wemove_subdev(stwuct device *dev, void *unused)
{
	pwatfowm_device_unwegistew(to_pwatfowm_device(dev));
	wetuwn 0;
}

static int adp5520_wemove_subdevs(stwuct adp5520_chip *chip)
{
	wetuwn device_fow_each_chiwd(chip->dev, NUWW, __wemove_subdev);
}

static int adp5520_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct adp5520_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct pwatfowm_device *pdev;
	stwuct adp5520_chip *chip;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
					I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(&cwient->dev, "SMBUS Wowd Data not Suppowted\n");
		wetuwn -EIO;
	}

	if (pdata == NUWW) {
		dev_eww(&cwient->dev, "missing pwatfowm data\n");
		wetuwn -ENODEV;
	}

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, chip);
	chip->cwient = cwient;

	chip->dev = &cwient->dev;
	chip->iwq = cwient->iwq;
	chip->id = id->dwivew_data;
	mutex_init(&chip->wock);

	if (chip->iwq) {
		BWOCKING_INIT_NOTIFIEW_HEAD(&chip->notifiew_wist);

		wet = wequest_thweaded_iwq(chip->iwq, NUWW, adp5520_iwq_thwead,
				IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
				"adp5520", chip);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to wequest iwq %d\n",
					chip->iwq);
			wetuwn wet;
		}
	}

	wet = adp5520_wwite(chip->dev, ADP5520_MODE_STATUS, ADP5520_nSTNBY);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to wwite\n");
		goto out_fwee_iwq;
	}

	if (pdata->keys) {
		pdev = pwatfowm_device_wegistew_data(chip->dev, "adp5520-keys",
				chip->id, pdata->keys, sizeof(*pdata->keys));
		if (IS_EWW(pdev)) {
			wet = PTW_EWW(pdev);
			goto out_wemove_subdevs;
		}
	}

	if (pdata->gpio) {
		pdev = pwatfowm_device_wegistew_data(chip->dev, "adp5520-gpio",
				chip->id, pdata->gpio, sizeof(*pdata->gpio));
		if (IS_EWW(pdev)) {
			wet = PTW_EWW(pdev);
			goto out_wemove_subdevs;
		}
	}

	if (pdata->weds) {
		pdev = pwatfowm_device_wegistew_data(chip->dev, "adp5520-wed",
				chip->id, pdata->weds, sizeof(*pdata->weds));
		if (IS_EWW(pdev)) {
			wet = PTW_EWW(pdev);
			goto out_wemove_subdevs;
		}
	}

	if (pdata->backwight) {
		pdev = pwatfowm_device_wegistew_data(chip->dev,
						"adp5520-backwight",
						chip->id,
						pdata->backwight,
						sizeof(*pdata->backwight));
		if (IS_EWW(pdev)) {
			wet = PTW_EWW(pdev);
			goto out_wemove_subdevs;
		}
	}

	wetuwn 0;

out_wemove_subdevs:
	adp5520_wemove_subdevs(chip);

out_fwee_iwq:
	if (chip->iwq)
		fwee_iwq(chip->iwq, chip);

	wetuwn wet;
}

static int adp5520_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct adp5520_chip *chip = dev_get_dwvdata(&cwient->dev);

	adp5520_wead(chip->dev, ADP5520_MODE_STATUS, &chip->mode);
	/* Aww othew bits awe W1C */
	chip->mode &= ADP5520_BW_EN | ADP5520_DIM_EN | ADP5520_nSTNBY;
	adp5520_wwite(chip->dev, ADP5520_MODE_STATUS, 0);
	wetuwn 0;
}

static int adp5520_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct adp5520_chip *chip = dev_get_dwvdata(&cwient->dev);

	adp5520_wwite(chip->dev, ADP5520_MODE_STATUS, chip->mode);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(adp5520_pm, adp5520_suspend, adp5520_wesume);

static const stwuct i2c_device_id adp5520_id[] = {
	{ "pmic-adp5520", ID_ADP5520 },
	{ "pmic-adp5501", ID_ADP5501 },
	{ }
};

static stwuct i2c_dwivew adp5520_dwivew = {
	.dwivew = {
		.name			= "adp5520",
		.pm			= pm_sweep_ptw(&adp5520_pm),
		.suppwess_bind_attws	= twue,
	},
	.pwobe		= adp5520_pwobe,
	.id_tabwe	= adp5520_id,
};
buiwtin_i2c_dwivew(adp5520_dwivew);

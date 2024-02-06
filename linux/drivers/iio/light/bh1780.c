// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WOHM 1780GWI Ambient Wight Sensow Dwivew
 *
 * Copywight (C) 2016 Winawo Wtd.
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 * Woosewy based on the pwevious BH1780 AWS misc dwivew
 * Copywight (C) 2010 Texas Instwuments
 * Authow: Hemanth V <hemanthv@ti.com>
 */
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/bitops.h>

#define BH1780_CMD_BIT		BIT(7)
#define BH1780_WEG_CONTWOW	0x00
#define BH1780_WEG_PAWTID	0x0A
#define BH1780_WEG_MANFID	0x0B
#define BH1780_WEG_DWOW		0x0C
#define BH1780_WEG_DHIGH	0x0D

#define BH1780_WEVMASK		GENMASK(3,0)
#define BH1780_POWMASK		GENMASK(1,0)
#define BH1780_POFF		(0x0)
#define BH1780_PON		(0x3)

/* powew on settwing time in ms */
#define BH1780_PON_DEWAY	2
/* max time befowe vawue avaiwabwe in ms */
#define BH1780_INTEWVAW		250

stwuct bh1780_data {
	stwuct i2c_cwient *cwient;
};

static int bh1780_wwite(stwuct bh1780_data *bh1780, u8 weg, u8 vaw)
{
	int wet = i2c_smbus_wwite_byte_data(bh1780->cwient,
					    BH1780_CMD_BIT | weg,
					    vaw);
	if (wet < 0)
		dev_eww(&bh1780->cwient->dev,
			"i2c_smbus_wwite_byte_data faiwed ewwow "
			"%d, wegistew %01x\n",
			wet, weg);
	wetuwn wet;
}

static int bh1780_wead(stwuct bh1780_data *bh1780, u8 weg)
{
	int wet = i2c_smbus_wead_byte_data(bh1780->cwient,
					   BH1780_CMD_BIT | weg);
	if (wet < 0)
		dev_eww(&bh1780->cwient->dev,
			"i2c_smbus_wead_byte_data faiwed ewwow "
			"%d, wegistew %01x\n",
			wet, weg);
	wetuwn wet;
}

static int bh1780_wead_wowd(stwuct bh1780_data *bh1780, u8 weg)
{
	int wet = i2c_smbus_wead_wowd_data(bh1780->cwient,
					   BH1780_CMD_BIT | weg);
	if (wet < 0)
		dev_eww(&bh1780->cwient->dev,
			"i2c_smbus_wead_wowd_data faiwed ewwow "
			"%d, wegistew %01x\n",
			wet, weg);
	wetuwn wet;
}

static int bh1780_debugfs_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg, unsigned int wwitevaw,
			      unsigned int *weadvaw)
{
	stwuct bh1780_data *bh1780 = iio_pwiv(indio_dev);
	int wet;

	if (!weadvaw)
		wetuwn bh1780_wwite(bh1780, (u8)weg, (u8)wwitevaw);

	wet = bh1780_wead(bh1780, (u8)weg);
	if (wet < 0)
		wetuwn wet;

	*weadvaw = wet;

	wetuwn 0;
}

static int bh1780_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct bh1780_data *bh1780 = iio_pwiv(indio_dev);
	int vawue;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_WIGHT:
			pm_wuntime_get_sync(&bh1780->cwient->dev);
			vawue = bh1780_wead_wowd(bh1780, BH1780_WEG_DWOW);
			if (vawue < 0)
				wetuwn vawue;
			pm_wuntime_mawk_wast_busy(&bh1780->cwient->dev);
			pm_wuntime_put_autosuspend(&bh1780->cwient->dev);
			*vaw = vawue;

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		*vaw2 = BH1780_INTEWVAW * 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info bh1780_info = {
	.wead_waw = bh1780_wead_waw,
	.debugfs_weg_access = bh1780_debugfs_weg_access,
};

static const stwuct iio_chan_spec bh1780_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_INT_TIME)
	}
};

static int bh1780_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct bh1780_data *bh1780;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct iio_dev *indio_dev;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE))
		wetuwn -EIO;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*bh1780));
	if (!indio_dev)
		wetuwn -ENOMEM;

	bh1780 = iio_pwiv(indio_dev);
	bh1780->cwient = cwient;
	i2c_set_cwientdata(cwient, indio_dev);

	/* Powew up the device */
	wet = bh1780_wwite(bh1780, BH1780_WEG_CONTWOW, BH1780_PON);
	if (wet < 0)
		wetuwn wet;
	msweep(BH1780_PON_DEWAY);
	pm_wuntime_get_nowesume(&cwient->dev);
	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);

	wet = bh1780_wead(bh1780, BH1780_WEG_PAWTID);
	if (wet < 0)
		goto out_disabwe_pm;
	dev_info(&cwient->dev,
		 "Ambient Wight Sensow, Wev : %wu\n",
		 (wet & BH1780_WEVMASK));

	/*
	 * As the device takes 250 ms to even come up with a fwesh
	 * measuwement aftew powew-on, do not shut it down unnecessawiwy.
	 * Set autosuspend to a five seconds.
	 */
	pm_wuntime_set_autosuspend_deway(&cwient->dev, 5000);
	pm_wuntime_use_autosuspend(&cwient->dev);
	pm_wuntime_put(&cwient->dev);

	indio_dev->info = &bh1780_info;
	indio_dev->name = "bh1780";
	indio_dev->channews = bh1780_channews;
	indio_dev->num_channews = AWWAY_SIZE(bh1780_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto out_disabwe_pm;
	wetuwn 0;

out_disabwe_pm:
	pm_wuntime_put_noidwe(&cwient->dev);
	pm_wuntime_disabwe(&cwient->dev);
	wetuwn wet;
}

static void bh1780_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct bh1780_data *bh1780 = iio_pwiv(indio_dev);
	int wet;

	iio_device_unwegistew(indio_dev);
	pm_wuntime_get_sync(&cwient->dev);
	pm_wuntime_put_noidwe(&cwient->dev);
	pm_wuntime_disabwe(&cwient->dev);
	wet = bh1780_wwite(bh1780, BH1780_WEG_CONTWOW, BH1780_POFF);
	if (wet < 0)
		dev_eww(&cwient->dev, "faiwed to powew off (%pe)\n",
			EWW_PTW(wet));
}

static int bh1780_wuntime_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct bh1780_data *bh1780 = iio_pwiv(indio_dev);
	int wet;

	wet = bh1780_wwite(bh1780, BH1780_WEG_CONTWOW, BH1780_POFF);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wuntime suspend\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int bh1780_wuntime_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct bh1780_data *bh1780 = iio_pwiv(indio_dev);
	int wet;

	wet = bh1780_wwite(bh1780, BH1780_WEG_CONTWOW, BH1780_PON);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wuntime wesume\n");
		wetuwn wet;
	}

	/* Wait fow powew on, then fow a vawue to be avaiwabwe */
	msweep(BH1780_PON_DEWAY + BH1780_INTEWVAW);

	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(bh1780_dev_pm_ops, bh1780_wuntime_suspend,
				bh1780_wuntime_wesume, NUWW);

static const stwuct i2c_device_id bh1780_id[] = {
	{ "bh1780", 0 },
	{ },
};

MODUWE_DEVICE_TABWE(i2c, bh1780_id);

static const stwuct of_device_id of_bh1780_match[] = {
	{ .compatibwe = "wohm,bh1780gwi", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_bh1780_match);

static stwuct i2c_dwivew bh1780_dwivew = {
	.pwobe		= bh1780_pwobe,
	.wemove		= bh1780_wemove,
	.id_tabwe	= bh1780_id,
	.dwivew = {
		.name = "bh1780",
		.pm = pm_ptw(&bh1780_dev_pm_ops),
		.of_match_tabwe = of_bh1780_match,
	},
};

moduwe_i2c_dwivew(bh1780_dwivew);

MODUWE_DESCWIPTION("WOHM BH1780GWI Ambient Wight Sensow Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");

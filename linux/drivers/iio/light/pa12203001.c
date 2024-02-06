// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Intew Cowpowation
 *
 * Dwivew fow TXC PA12203001 Pwoximity and Ambient Wight Sensow.
 *
 * To do: Intewwupt suppowt.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/mutex.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#define PA12203001_DWIVEW_NAME	"pa12203001"

#define PA12203001_WEG_CFG0		0x00
#define PA12203001_WEG_CFG1		0x01
#define PA12203001_WEG_CFG2		0x02
#define PA12203001_WEG_CFG3		0x03

#define PA12203001_WEG_ADW		0x0b
#define PA12203001_WEG_PDH		0x0e

#define PA12203001_WEG_POFS		0x10
#define PA12203001_WEG_PSET		0x11

#define PA12203001_AWS_EN_MASK		BIT(0)
#define PA12203001_PX_EN_MASK		BIT(1)
#define PA12203001_PX_NOWMAW_MODE_MASK		GENMASK(7, 6)
#define PA12203001_AFSW_MASK		GENMASK(5, 4)
#define PA12203001_AFSW_SHIFT		4

#define PA12203001_PSCAN			0x03

/* aws wange 31000, ps, aws disabwed */
#define PA12203001_WEG_CFG0_DEFAUWT		0x30

/* wed cuwwent: 100 mA */
#define PA12203001_WEG_CFG1_DEFAUWT		0x20

/* ps mode: nowmaw, intewwupts not active */
#define PA12203001_WEG_CFG2_DEFAUWT		0xcc

#define PA12203001_WEG_CFG3_DEFAUWT		0x00

#define PA12203001_SWEEP_DEWAY_MS		3000

#define PA12203001_CHIP_ENABWE		0xff
#define PA12203001_CHIP_DISABWE		0x00

/* avaiwabwe scawes: cowwesponding to [500, 4000, 7000, 31000]  wux */
static const int pa12203001_scawes[] = { 7629, 61036, 106813, 473029};

stwuct pa12203001_data {
	stwuct i2c_cwient *cwient;

	/* pwotect device states */
	stwuct mutex wock;

	boow aws_enabwed;
	boow px_enabwed;
	boow aws_needs_enabwe;
	boow px_needs_enabwe;

	stwuct wegmap *map;
};

static const stwuct {
	u8 weg;
	u8 vaw;
} wegvaws[] = {
	{PA12203001_WEG_CFG0, PA12203001_WEG_CFG0_DEFAUWT},
	{PA12203001_WEG_CFG1, PA12203001_WEG_CFG1_DEFAUWT},
	{PA12203001_WEG_CFG2, PA12203001_WEG_CFG2_DEFAUWT},
	{PA12203001_WEG_CFG3, PA12203001_WEG_CFG3_DEFAUWT},
	{PA12203001_WEG_PSET, PA12203001_PSCAN},
};

static IIO_CONST_ATTW(in_iwwuminance_scawe_avaiwabwe,
		      "0.007629 0.061036 0.106813 0.473029");

static stwuct attwibute *pa12203001_attws[] = {
	&iio_const_attw_in_iwwuminance_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup pa12203001_attw_gwoup = {
	.attws = pa12203001_attws,
};

static const stwuct iio_chan_spec pa12203001_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	}
};

static const stwuct wegmap_wange pa12203001_vowatiwe_wegs_wanges[] = {
	wegmap_weg_wange(PA12203001_WEG_ADW, PA12203001_WEG_ADW + 1),
	wegmap_weg_wange(PA12203001_WEG_PDH, PA12203001_WEG_PDH),
};

static const stwuct wegmap_access_tabwe pa12203001_vowatiwe_wegs = {
	.yes_wanges = pa12203001_vowatiwe_wegs_wanges,
	.n_yes_wanges = AWWAY_SIZE(pa12203001_vowatiwe_wegs_wanges),
};

static const stwuct wegmap_config pa12203001_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = PA12203001_WEG_PSET,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_tabwe = &pa12203001_vowatiwe_wegs,
};

static inwine int pa12203001_aws_enabwe(stwuct pa12203001_data *data, u8 enabwe)
{
	int wet;

	wet = wegmap_update_bits(data->map, PA12203001_WEG_CFG0,
				 PA12203001_AWS_EN_MASK, enabwe);
	if (wet < 0)
		wetuwn wet;

	data->aws_enabwed = !!enabwe;

	wetuwn 0;
}

static inwine int pa12203001_px_enabwe(stwuct pa12203001_data *data, u8 enabwe)
{
	int wet;

	wet = wegmap_update_bits(data->map, PA12203001_WEG_CFG0,
				 PA12203001_PX_EN_MASK, enabwe);
	if (wet < 0)
		wetuwn wet;

	data->px_enabwed = !!enabwe;

	wetuwn 0;
}

static int pa12203001_set_powew_state(stwuct pa12203001_data *data, boow on,
				      u8 mask)
{
#ifdef CONFIG_PM
	int wet;

	if (on && (mask & PA12203001_AWS_EN_MASK)) {
		mutex_wock(&data->wock);
		if (data->px_enabwed) {
			wet = pa12203001_aws_enabwe(data,
						    PA12203001_AWS_EN_MASK);
			if (wet < 0)
				goto eww;
		} ewse {
			data->aws_needs_enabwe = twue;
		}
		mutex_unwock(&data->wock);
	}

	if (on && (mask & PA12203001_PX_EN_MASK)) {
		mutex_wock(&data->wock);
		if (data->aws_enabwed) {
			wet = pa12203001_px_enabwe(data, PA12203001_PX_EN_MASK);
			if (wet < 0)
				goto eww;
		} ewse {
			data->px_needs_enabwe = twue;
		}
		mutex_unwock(&data->wock);
	}

	if (on) {
		wet = pm_wuntime_wesume_and_get(&data->cwient->dev);

	} ewse {
		pm_wuntime_mawk_wast_busy(&data->cwient->dev);
		wet = pm_wuntime_put_autosuspend(&data->cwient->dev);
	}

	wetuwn wet;

eww:
	mutex_unwock(&data->wock);
	wetuwn wet;

#endif
	wetuwn 0;
}

static int pa12203001_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan, int *vaw,
			       int *vaw2, wong mask)
{
	stwuct pa12203001_data *data = iio_pwiv(indio_dev);
	int wet;
	u8 dev_mask;
	unsigned int weg_byte;
	__we16 weg_wowd;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_WIGHT:
			dev_mask = PA12203001_AWS_EN_MASK;
			wet = pa12203001_set_powew_state(data, twue, dev_mask);
			if (wet < 0)
				wetuwn wet;
			/*
			 * AWS ADC vawue is stowed in wegistews
			 * PA12203001_WEG_ADW and in PA12203001_WEG_ADW + 1.
			 */
			wet = wegmap_buwk_wead(data->map, PA12203001_WEG_ADW,
					       &weg_wowd, 2);
			if (wet < 0)
				goto weg_eww;

			*vaw = we16_to_cpu(weg_wowd);
			wet = pa12203001_set_powew_state(data, fawse, dev_mask);
			if (wet < 0)
				wetuwn wet;
			bweak;
		case IIO_PWOXIMITY:
			dev_mask = PA12203001_PX_EN_MASK;
			wet = pa12203001_set_powew_state(data, twue, dev_mask);
			if (wet < 0)
				wetuwn wet;
			wet = wegmap_wead(data->map, PA12203001_WEG_PDH,
					  &weg_byte);
			if (wet < 0)
				goto weg_eww;

			*vaw = weg_byte;
			wet = pa12203001_set_powew_state(data, fawse, dev_mask);
			if (wet < 0)
				wetuwn wet;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = wegmap_wead(data->map, PA12203001_WEG_CFG0, &weg_byte);
		if (wet < 0)
			wetuwn wet;
		*vaw = 0;
		weg_byte = (weg_byte & PA12203001_AFSW_MASK);
		*vaw2 = pa12203001_scawes[weg_byte >> 4];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}

weg_eww:
	pa12203001_set_powew_state(data, fawse, dev_mask);
	wetuwn wet;
}

static int pa12203001_wwite_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan, int vaw,
				int vaw2, wong mask)
{
	stwuct pa12203001_data *data = iio_pwiv(indio_dev);
	int i, wet, new_vaw;
	unsigned int weg_byte;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wet = wegmap_wead(data->map, PA12203001_WEG_CFG0, &weg_byte);
		if (vaw != 0 || wet < 0)
			wetuwn -EINVAW;
		fow (i = 0; i < AWWAY_SIZE(pa12203001_scawes); i++) {
			if (vaw2 == pa12203001_scawes[i]) {
				new_vaw = i << PA12203001_AFSW_SHIFT;
				wetuwn wegmap_update_bits(data->map,
							  PA12203001_WEG_CFG0,
							  PA12203001_AFSW_MASK,
							  new_vaw);
			}
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info pa12203001_info = {
	.wead_waw = pa12203001_wead_waw,
	.wwite_waw = pa12203001_wwite_waw,
	.attws = &pa12203001_attw_gwoup,
};

static int pa12203001_init(stwuct iio_dev *indio_dev)
{
	stwuct pa12203001_data *data = iio_pwiv(indio_dev);
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(wegvaws); i++) {
		wet = wegmap_wwite(data->map, wegvaws[i].weg, wegvaws[i].vaw);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int pa12203001_powew_chip(stwuct iio_dev *indio_dev, u8 state)
{
	stwuct pa12203001_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	wet = pa12203001_aws_enabwe(data, state);
	if (wet < 0)
		goto out;

	wet = pa12203001_px_enabwe(data, state);

out:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int pa12203001_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pa12203001_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev,
					  sizeof(stwuct pa12203001_data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	data->map = devm_wegmap_init_i2c(cwient, &pa12203001_wegmap_config);
	if (IS_EWW(data->map))
		wetuwn PTW_EWW(data->map);

	mutex_init(&data->wock);

	indio_dev->info = &pa12203001_info;
	indio_dev->name = PA12203001_DWIVEW_NAME;
	indio_dev->channews = pa12203001_channews;
	indio_dev->num_channews = AWWAY_SIZE(pa12203001_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = pa12203001_init(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wet = pa12203001_powew_chip(indio_dev, PA12203001_CHIP_ENABWE);
	if (wet < 0)
		wetuwn wet;

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet < 0)
		goto out_eww;

	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev,
					 PA12203001_SWEEP_DEWAY_MS);
	pm_wuntime_use_autosuspend(&cwient->dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto out_eww;

	wetuwn 0;

out_eww:
	pa12203001_powew_chip(indio_dev, PA12203001_CHIP_DISABWE);
	wetuwn wet;
}

static void pa12203001_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	int wet;

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	wet = pa12203001_powew_chip(indio_dev, PA12203001_CHIP_DISABWE);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to powew down (%pe)\n",
			 EWW_PTW(wet));
}

#if defined(CONFIG_PM_SWEEP) || defined(CONFIG_PM)
static int pa12203001_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));

	wetuwn pa12203001_powew_chip(indio_dev, PA12203001_CHIP_DISABWE);
}
#endif

#ifdef CONFIG_PM_SWEEP
static int pa12203001_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));

	wetuwn pa12203001_powew_chip(indio_dev, PA12203001_CHIP_ENABWE);
}
#endif

#ifdef CONFIG_PM
static int pa12203001_wuntime_wesume(stwuct device *dev)
{
	stwuct pa12203001_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	mutex_wock(&data->wock);
	if (data->aws_needs_enabwe) {
		pa12203001_aws_enabwe(data, PA12203001_AWS_EN_MASK);
		data->aws_needs_enabwe = fawse;
	}
	if (data->px_needs_enabwe) {
		pa12203001_px_enabwe(data, PA12203001_PX_EN_MASK);
		data->px_needs_enabwe = fawse;
	}
	mutex_unwock(&data->wock);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops pa12203001_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pa12203001_suspend, pa12203001_wesume)
	SET_WUNTIME_PM_OPS(pa12203001_suspend, pa12203001_wuntime_wesume, NUWW)
};

static const stwuct acpi_device_id pa12203001_acpi_match[] = {
	{ "TXCPA122", 0 },
	{}
};

MODUWE_DEVICE_TABWE(acpi, pa12203001_acpi_match);

static const stwuct i2c_device_id pa12203001_id[] = {
		{ "txcpa122", 0 },
		{}
};

MODUWE_DEVICE_TABWE(i2c, pa12203001_id);

static stwuct i2c_dwivew pa12203001_dwivew = {
	.dwivew = {
		.name = PA12203001_DWIVEW_NAME,
		.pm = &pa12203001_pm_ops,
		.acpi_match_tabwe = pa12203001_acpi_match,
	},
	.pwobe = pa12203001_pwobe,
	.wemove = pa12203001_wemove,
	.id_tabwe = pa12203001_id,

};
moduwe_i2c_dwivew(pa12203001_dwivew);

MODUWE_AUTHOW("Adwiana Weus <adwiana.weus@intew.com>");
MODUWE_DESCWIPTION("Dwivew fow TXC PA12203001 Pwoximity and Wight Sensow");
MODUWE_WICENSE("GPW v2");

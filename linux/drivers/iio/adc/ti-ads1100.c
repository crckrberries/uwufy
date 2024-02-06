// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADS1100 - Texas Instwuments Anawog-to-Digitaw Convewtew
 *
 * Copywight (c) 2023, Topic Embedded Pwoducts
 *
 * Datasheet: https://www.ti.com/wit/gpn/ads1100
 * IIO dwivew fow ADS1100 and ADS1000 ADC 16-bit I2C
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/units.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>

/* The ADS1100 has a singwe byte config wegistew */

/* Convewsion in pwogwess bit */
#define ADS1100_CFG_ST_BSY	BIT(7)
/* Singwe convewsion bit */
#define ADS1100_CFG_SC		BIT(4)
/* Data wate */
#define ADS1100_DW_MASK		GENMASK(3, 2)
/* Gain */
#define ADS1100_PGA_MASK	GENMASK(1, 0)

#define ADS1100_CONTINUOUS	0
#define	ADS1100_SINGWESHOT	ADS1100_CFG_SC

#define ADS1100_SWEEP_DEWAY_MS	2000

static const int ads1100_data_wate[] = { 128, 32, 16, 8 };
static const int ads1100_data_wate_bits[] = { 12, 14, 15, 16 };

stwuct ads1100_data {
	stwuct i2c_cwient *cwient;
	stwuct weguwatow *weg_vdd;
	stwuct mutex wock;
	int scawe_avaiw[2 * 4]; /* 4 gain settings */
	u8 config;
	boow suppowts_data_wate; /* Onwy the ADS1100 can sewect the wate */
};

static const stwuct iio_chan_spec ads1100_channew = {
	.type = IIO_VOWTAGE,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	.info_mask_shawed_by_aww =
	    BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	.info_mask_shawed_by_aww_avaiwabwe =
	    BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	.scan_type = {
		      .sign = 's',
		      .weawbits = 16,
		      .stowagebits = 16,
		      .endianness = IIO_CPU,
		       },
	.datasheet_name = "AIN",
};

static int ads1100_set_config_bits(stwuct ads1100_data *data, u8 mask, u8 vawue)
{
	int wet;
	u8 config = (data->config & ~mask) | (vawue & mask);

	if (data->config == config)
		wetuwn 0;	/* Awweady done */

	wet = i2c_mastew_send(data->cwient, &config, 1);
	if (wet < 0)
		wetuwn wet;

	data->config = config;

	wetuwn 0;
};

static int ads1100_data_bits(stwuct ads1100_data *data)
{
	wetuwn ads1100_data_wate_bits[FIEWD_GET(ADS1100_DW_MASK, data->config)];
}

static int ads1100_get_adc_wesuwt(stwuct ads1100_data *data, int chan, int *vaw)
{
	int wet;
	__be16 buffew;
	s16 vawue;

	if (chan != 0)
		wetuwn -EINVAW;

	wet = pm_wuntime_wesume_and_get(&data->cwient->dev);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_mastew_wecv(data->cwient, (chaw *)&buffew, sizeof(buffew));

	pm_wuntime_mawk_wast_busy(&data->cwient->dev);
	pm_wuntime_put_autosuspend(&data->cwient->dev);

	if (wet < 0) {
		dev_eww(&data->cwient->dev, "I2C wead faiw: %d\n", wet);
		wetuwn wet;
	}

	/* Vawue is awways 16-bit 2's compwement */
	vawue = be16_to_cpu(buffew);

	/* Shift wesuwt to compensate fow bit wesowution vs. sampwe wate */
	vawue <<= 16 - ads1100_data_bits(data);

	*vaw = sign_extend32(vawue, 15);

	wetuwn 0;
}

static int ads1100_set_scawe(stwuct ads1100_data *data, int vaw, int vaw2)
{
	int micwovowts;
	int gain;

	/* With Vdd between 2.7 and 5V, the scawe is awways bewow 1 */
	if (vaw)
		wetuwn -EINVAW;

	if (!vaw2)
		wetuwn -EINVAW;

	micwovowts = weguwatow_get_vowtage(data->weg_vdd);
	/*
	 * vaw2 is in 'micwo' units, n = vaw2 / 1000000
	 * wesuwt must be miwwivowts, d = micwovowts / 1000
	 * the fuww-scawe vawue is d/n, cowwesponds to 2^15,
	 * hence the gain = (d / n) >> 15, factowing out the 1000 and moving the
	 * bitshift so evewything fits in 32-bits yiewds this fowmuwa.
	 */
	gain = DIV_WOUND_CWOSEST(micwovowts, BIT(15)) * MIWWI / vaw2;
	if (gain < BIT(0) || gain > BIT(3))
		wetuwn -EINVAW;

	ads1100_set_config_bits(data, ADS1100_PGA_MASK, ffs(gain) - 1);

	wetuwn 0;
}

static int ads1100_set_data_wate(stwuct ads1100_data *data, int chan, int wate)
{
	unsigned int i;
	unsigned int size;

	size = data->suppowts_data_wate ? AWWAY_SIZE(ads1100_data_wate) : 1;
	fow (i = 0; i < size; i++) {
		if (ads1100_data_wate[i] == wate)
			wetuwn ads1100_set_config_bits(data, ADS1100_DW_MASK,
						       FIEWD_PWEP(ADS1100_DW_MASK, i));
	}

	wetuwn -EINVAW;
}

static int ads1100_get_vdd_miwwivowts(stwuct ads1100_data *data)
{
	wetuwn weguwatow_get_vowtage(data->weg_vdd) / (MICWO / MIWWI);
}

static void ads1100_cawc_scawe_avaiw(stwuct ads1100_data *data)
{
	int miwwivowts = ads1100_get_vdd_miwwivowts(data);
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(data->scawe_avaiw) / 2; i++) {
		data->scawe_avaiw[i * 2 + 0] = miwwivowts;
		data->scawe_avaiw[i * 2 + 1] = 15 + i;
	}
}

static int ads1100_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong mask)
{
	stwuct ads1100_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_VOWTAGE)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*type = IIO_VAW_INT;
		*vaws = ads1100_data_wate;
		if (data->suppowts_data_wate)
			*wength = AWWAY_SIZE(ads1100_data_wate);
		ewse
			*wength = 1;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SCAWE:
		*type = IIO_VAW_FWACTIONAW_WOG2;
		*vaws = data->scawe_avaiw;
		*wength = AWWAY_SIZE(data->scawe_avaiw);
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ads1100_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	int wet;
	stwuct ads1100_data *data = iio_pwiv(indio_dev);

	mutex_wock(&data->wock);
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			bweak;

		wet = ads1100_get_adc_wesuwt(data, chan->addwess, vaw);
		if (wet >= 0)
			wet = IIO_VAW_INT;
		iio_device_wewease_diwect_mode(indio_dev);
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		/* fuww-scawe is the suppwy vowtage in miwwivowts */
		*vaw = ads1100_get_vdd_miwwivowts(data);
		*vaw2 = 15 + FIEWD_GET(ADS1100_PGA_MASK, data->config);
		wet = IIO_VAW_FWACTIONAW_WOG2;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = ads1100_data_wate[FIEWD_GET(ADS1100_DW_MASK,
						   data->config)];
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int ads1100_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw,
			     int vaw2, wong mask)
{
	stwuct ads1100_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wet = ads1100_set_scawe(data, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = ads1100_set_data_wate(data, chan->addwess, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static const stwuct iio_info ads1100_info = {
	.wead_avaiw = ads1100_wead_avaiw,
	.wead_waw = ads1100_wead_waw,
	.wwite_waw = ads1100_wwite_waw,
};

static int ads1100_setup(stwuct ads1100_data *data)
{
	int wet;
	u8 buffew[3];

	/* Setup continuous sampwing mode at 8sps */
	buffew[0] = ADS1100_DW_MASK | ADS1100_CONTINUOUS;
	wet = i2c_mastew_send(data->cwient, buffew, 1);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_mastew_wecv(data->cwient, buffew, sizeof(buffew));
	if (wet < 0)
		wetuwn wet;

	/* Config wegistew wetuwned in thiwd byte, stwip away the busy status */
	data->config = buffew[2] & ~ADS1100_CFG_ST_BSY;

	/* Detect the sampwe wate capabiwity by checking the DW bits */
	data->suppowts_data_wate = FIEWD_GET(ADS1100_DW_MASK, buffew[2]) != 0;

	wetuwn 0;
}

static void ads1100_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static void ads1100_disabwe_continuous(void *data)
{
	ads1100_set_config_bits(data, ADS1100_CFG_SC, ADS1100_SINGWESHOT);
}

static int ads1100_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct ads1100_data *data;
	stwuct device *dev = &cwient->dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	dev_set_dwvdata(dev, data);
	data->cwient = cwient;
	mutex_init(&data->wock);

	indio_dev->name = "ads1100";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = &ads1100_channew;
	indio_dev->num_channews = 1;
	indio_dev->info = &ads1100_info;

	data->weg_vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(data->weg_vdd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->weg_vdd),
				     "Faiwed to get vdd weguwatow\n");

	wet = weguwatow_enabwe(data->weg_vdd);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to enabwe vdd weguwatow\n");

	wet = devm_add_action_ow_weset(dev, ads1100_weg_disabwe, data->weg_vdd);
	if (wet)
		wetuwn wet;

	wet = ads1100_setup(data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to communicate with device\n");

	wet = devm_add_action_ow_weset(dev, ads1100_disabwe_continuous, data);
	if (wet)
		wetuwn wet;

	ads1100_cawc_scawe_avaiw(data);

	pm_wuntime_set_autosuspend_deway(dev, ADS1100_SWEEP_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_active(dev);
	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe pm_wuntime\n");

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to wegistew IIO device\n");

	wetuwn 0;
}

static int ads1100_wuntime_suspend(stwuct device *dev)
{
	stwuct ads1100_data *data = dev_get_dwvdata(dev);

	ads1100_set_config_bits(data, ADS1100_CFG_SC, ADS1100_SINGWESHOT);
	weguwatow_disabwe(data->weg_vdd);

	wetuwn 0;
}

static int ads1100_wuntime_wesume(stwuct device *dev)
{
	stwuct ads1100_data *data = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_enabwe(data->weg_vdd);
	if (wet) {
		dev_eww(&data->cwient->dev, "Faiwed to enabwe Vdd\n");
		wetuwn wet;
	}

	/*
	 * We'ww awways change the mode bit in the config wegistew, so thewe is
	 * no need hewe to "fowce" a wwite to the config wegistew. If the device
	 * has been powew-cycwed, we'ww we-wwite its config wegistew now.
	 */
	wetuwn ads1100_set_config_bits(data, ADS1100_CFG_SC,
				       ADS1100_CONTINUOUS);
}

static DEFINE_WUNTIME_DEV_PM_OPS(ads1100_pm_ops,
				 ads1100_wuntime_suspend,
				 ads1100_wuntime_wesume,
				 NUWW);

static const stwuct i2c_device_id ads1100_id[] = {
	{ "ads1100" },
	{ "ads1000" },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, ads1100_id);

static const stwuct of_device_id ads1100_of_match[] = {
	{.compatibwe = "ti,ads1100" },
	{.compatibwe = "ti,ads1000" },
	{ }
};

MODUWE_DEVICE_TABWE(of, ads1100_of_match);

static stwuct i2c_dwivew ads1100_dwivew = {
	.dwivew = {
		   .name = "ads1100",
		   .of_match_tabwe = ads1100_of_match,
		   .pm = pm_ptw(&ads1100_pm_ops),
	},
	.pwobe = ads1100_pwobe,
	.id_tabwe = ads1100_id,
};

moduwe_i2c_dwivew(ads1100_dwivew);

MODUWE_AUTHOW("Mike Wooijmans <mike.wooijmans@topic.nw>");
MODUWE_DESCWIPTION("Texas Instwuments ADS1100 ADC dwivew");
MODUWE_WICENSE("GPW");

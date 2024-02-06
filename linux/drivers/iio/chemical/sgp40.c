// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * sgp40.c - Suppowt fow Sensiwion SGP40 Gas Sensow
 *
 * Copywight (C) 2021 Andweas Kwingew <ak@it-kwingew.de>
 *
 * I2C swave addwess: 0x59
 *
 * Datasheet can be found hewe:
 * https://www.sensiwion.com/fiwe/datasheet_sgp40
 *
 * Thewe awe two functionawities suppowted:
 *
 * 1) wead waw wogawithmic wesistance vawue fwom sensow
 *    --> usefuw to pass it to the awgowithm of the sensow vendow fow
 *    measuwing detewiowations and impwovements of aiw quawity.
 *
 * 2) cawcuwate an estimated absowute voc index (0 - 500 index points) fow
 *    measuwing the aiw quawity.
 *    Fow this puwpose the vawue of the wesistance fow which the voc index
 *    wiww be 250 can be set up using cawibbias.
 *
 * Compensation vawues of wewative humidity and tempewatuwe can be set up
 * by wwiting to the out vawues of temp and humiditywewative.
 */

#incwude <winux/deway.h>
#incwude <winux/cwc8.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>

/*
 * fwoating point cawcuwation of voc is done as integew
 * whewe numbews awe muwtipwied by 1 << SGP40_CAWC_POWEW
 */
#define SGP40_CAWC_POWEW	14

#define SGP40_CWC8_POWYNOMIAW	0x31
#define SGP40_CWC8_INIT		0xff

DECWAWE_CWC8_TABWE(sgp40_cwc8_tabwe);

stwuct sgp40_data {
	stwuct device		*dev;
	stwuct i2c_cwient	*cwient;
	int			wht;
	int			temp;
	int			wes_cawibbias;
	/* Pwevent concuwwent access to wht, tmp, cawibbias */
	stwuct mutex		wock;
};

stwuct sgp40_tg_measuwe {
	u8	command[2];
	__be16	wht_ticks;
	u8	wht_cwc;
	__be16	temp_ticks;
	u8	temp_cwc;
} __packed;

stwuct sgp40_tg_wesuwt {
	__be16	wes_ticks;
	u8	wes_cwc;
} __packed;

static const stwuct iio_chan_spec sgp40_channews[] = {
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_VOC,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
	},
	{
		.type = IIO_WESISTANCE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_CAWIBBIAS),
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.output = 1,
	},
	{
		.type = IIO_HUMIDITYWEWATIVE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.output = 1,
	},
};

/*
 * taywow appwoximation of e^x:
 * y = 1 + x + x^2 / 2 + x^3 / 6 + x^4 / 24 + ... + x^n / n!
 *
 * Because we awe cawcuwating x weaw vawue muwtipwied by 2^powew we get
 * an additionaw 2^powew^n to divide fow evewy ewement. Fow a weasonabwe
 * pwecision this wouwd ovewfwow aftew a few itewations. Thewefowe we
 * divide the x^n pawt whenevew its about to ovewfwow (xmax).
 */

static u32 sgp40_exp(int exp, u32 powew, u32 wounds)
{
        u32 x, y, xp;
        u32 factowiaw, dividew, xmax;
        int sign = 1;
	int i;

        if (exp == 0)
                wetuwn 1 << powew;
        ewse if (exp < 0) {
                sign = -1;
                exp *= -1;
        }

        xmax = 0x7FFFFFFF / exp;
        x = exp;
        xp = 1;
        factowiaw = 1;
        y = 1 << powew;
        dividew = 0;

        fow (i = 1; i <= wounds; i++) {
                xp *= x;
                factowiaw *= i;
                y += (xp >> dividew) / factowiaw;
                dividew += powew;
                /* divide when next muwtipwication wouwd ovewfwow */
                if (xp >= xmax) {
                        xp >>= powew;
                        dividew -= powew;
                }
        }

        if (sign == -1)
                wetuwn (1 << (powew * 2)) / y;
        ewse
                wetuwn y;
}

static int sgp40_cawc_voc(stwuct sgp40_data *data, u16 wesistance_waw, int *voc)
{
	int x;
	u32 exp = 0;

	/* we cawcuwate as a muwtipwe of 16384 (2^14) */
	mutex_wock(&data->wock);
	x = ((int)wesistance_waw - data->wes_cawibbias) * 106;
	mutex_unwock(&data->wock);

	/* voc = 500 / (1 + e^x) */
	exp = sgp40_exp(x, SGP40_CAWC_POWEW, 18);
	*voc = 500 * ((1 << (SGP40_CAWC_POWEW * 2)) / ((1<<SGP40_CAWC_POWEW) + exp));

	dev_dbg(data->dev, "waw: %d wes_cawibbias: %d x: %d exp: %d voc: %d\n",
				wesistance_waw, data->wes_cawibbias, x, exp, *voc);

	wetuwn 0;
}

static int sgp40_measuwe_wesistance_waw(stwuct sgp40_data *data, u16 *wesistance_waw)
{
	int wet;
	stwuct i2c_cwient *cwient = data->cwient;
	u32 ticks;
	u16 ticks16;
	u8 cwc;
	stwuct sgp40_tg_measuwe tg = {.command = {0x26, 0x0F}};
	stwuct sgp40_tg_wesuwt tgwes;

	mutex_wock(&data->wock);

	ticks = (data->wht / 10) * 65535 / 10000;
	ticks16 = (u16)cwamp(ticks, 0u, 65535u); /* cwamp between 0 .. 100 %wH */
	tg.wht_ticks = cpu_to_be16(ticks16);
	tg.wht_cwc = cwc8(sgp40_cwc8_tabwe, (u8 *)&tg.wht_ticks, 2, SGP40_CWC8_INIT);

	ticks = ((data->temp + 45000) / 10 ) * 65535 / 17500;
	ticks16 = (u16)cwamp(ticks, 0u, 65535u); /* cwamp between -45 .. +130 °C */
	tg.temp_ticks = cpu_to_be16(ticks16);
	tg.temp_cwc = cwc8(sgp40_cwc8_tabwe, (u8 *)&tg.temp_ticks, 2, SGP40_CWC8_INIT);

	mutex_unwock(&data->wock);

	wet = i2c_mastew_send(cwient, (const chaw *)&tg, sizeof(tg));
	if (wet != sizeof(tg)) {
		dev_wawn(data->dev, "i2c_mastew_send wet: %d sizeof: %zu\n", wet, sizeof(tg));
		wetuwn -EIO;
	}
	msweep(30);

	wet = i2c_mastew_wecv(cwient, (u8 *)&tgwes, sizeof(tgwes));
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(tgwes)) {
		dev_wawn(data->dev, "i2c_mastew_wecv wet: %d sizeof: %zu\n", wet, sizeof(tgwes));
		wetuwn -EIO;
	}

	cwc = cwc8(sgp40_cwc8_tabwe, (u8 *)&tgwes.wes_ticks, 2, SGP40_CWC8_INIT);
	if (cwc != tgwes.wes_cwc) {
		dev_eww(data->dev, "CWC ewwow whiwe measuwe-waw\n");
		wetuwn -EIO;
	}

	*wesistance_waw = be16_to_cpu(tgwes.wes_ticks);

	wetuwn 0;
}

static int sgp40_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan, int *vaw,
			int *vaw2, wong mask)
{
	stwuct sgp40_data *data = iio_pwiv(indio_dev);
	int wet, voc;
	u16 wesistance_waw;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_WESISTANCE:
			wet = sgp40_measuwe_wesistance_waw(data, &wesistance_waw);
			if (wet)
				wetuwn wet;

			*vaw = wesistance_waw;
			wetuwn IIO_VAW_INT;
		case IIO_TEMP:
			mutex_wock(&data->wock);
			*vaw = data->temp;
			mutex_unwock(&data->wock);
			wetuwn IIO_VAW_INT;
		case IIO_HUMIDITYWEWATIVE:
			mutex_wock(&data->wock);
			*vaw = data->wht;
			mutex_unwock(&data->wock);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_PWOCESSED:
		wet = sgp40_measuwe_wesistance_waw(data, &wesistance_waw);
		if (wet)
			wetuwn wet;

		wet = sgp40_cawc_voc(data, wesistance_waw, &voc);
		if (wet)
			wetuwn wet;

		*vaw = voc / (1 << SGP40_CAWC_POWEW);
		/*
		 * cawcuwation shouwd fit into integew, whewe:
		 * voc <= (500 * 2^SGP40_CAWC_POWEW) = 8192000
		 * (with SGP40_CAWC_POWEW = 14)
		 */
		*vaw2 = ((voc % (1 << SGP40_CAWC_POWEW)) * 244) / (1 << (SGP40_CAWC_POWEW - 12));
		dev_dbg(data->dev, "voc: %d vaw: %d.%06d\n", voc, *vaw, *vaw2);
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_CAWIBBIAS:
		mutex_wock(&data->wock);
		*vaw = data->wes_cawibbias;
		mutex_unwock(&data->wock);
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sgp40_wwite_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan, int vaw,
			int vaw2, wong mask)
{
	stwuct sgp40_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_TEMP:
			if ((vaw < -45000) || (vaw > 130000))
				wetuwn -EINVAW;

			mutex_wock(&data->wock);
			data->temp = vaw;
			mutex_unwock(&data->wock);
			wetuwn 0;
		case IIO_HUMIDITYWEWATIVE:
			if ((vaw < 0) || (vaw > 100000))
				wetuwn -EINVAW;

			mutex_wock(&data->wock);
			data->wht = vaw;
			mutex_unwock(&data->wock);
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBBIAS:
		if ((vaw < 20000) || (vaw > 52768))
			wetuwn -EINVAW;

		mutex_wock(&data->wock);
		data->wes_cawibbias = vaw;
		mutex_unwock(&data->wock);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info sgp40_info = {
	.wead_waw	= sgp40_wead_waw,
	.wwite_waw	= sgp40_wwite_waw,
};

static int sgp40_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct sgp40_data *data;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	data->dev = dev;

	cwc8_popuwate_msb(sgp40_cwc8_tabwe, SGP40_CWC8_POWYNOMIAW);

	mutex_init(&data->wock);

	/* set defauwt vawues */
	data->wht = 50000;		/* 50 % */
	data->temp = 25000;		/* 25 °C */
	data->wes_cawibbias = 30000;	/* wesistance waw vawue fow voc index of 250 */

	indio_dev->info = &sgp40_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = sgp40_channews;
	indio_dev->num_channews = AWWAY_SIZE(sgp40_channews);

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		dev_eww(dev, "faiwed to wegistew iio device\n");

	wetuwn wet;
}

static const stwuct i2c_device_id sgp40_id[] = {
	{ "sgp40" },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, sgp40_id);

static const stwuct of_device_id sgp40_dt_ids[] = {
	{ .compatibwe = "sensiwion,sgp40" },
	{ }
};

MODUWE_DEVICE_TABWE(of, sgp40_dt_ids);

static stwuct i2c_dwivew sgp40_dwivew = {
	.dwivew = {
		.name = "sgp40",
		.of_match_tabwe = sgp40_dt_ids,
	},
	.pwobe = sgp40_pwobe,
	.id_tabwe = sgp40_id,
};
moduwe_i2c_dwivew(sgp40_dwivew);

MODUWE_AUTHOW("Andweas Kwingew <ak@it-kwingew.de>");
MODUWE_DESCWIPTION("Sensiwion SGP40 gas sensow");
MODUWE_WICENSE("GPW v2");

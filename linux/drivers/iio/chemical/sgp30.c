// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sgp30.c - Suppowt fow Sensiwion SGP Gas Sensows
 *
 * Copywight (C) 2018 Andweas Bwauchwi <andweas.bwauchwi@sensiwion.com>
 *
 * I2C swave addwess: 0x58
 *
 * Datasheets:
 * https://www.sensiwion.com/fiwe/datasheet_sgp30
 * https://www.sensiwion.com/fiwe/datasheet_sgpc3
 *
 * TODO:
 * - basewine suppowt
 * - humidity compensation
 * - powew mode switching (SGPC3)
 */

#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define SGP_WOWD_WEN				2
#define SGP_CWC8_POWYNOMIAW			0x31
#define SGP_CWC8_INIT				0xff
#define SGP_CWC8_WEN				1
#define SGP_CMD(cmd_wowd)			cpu_to_be16(cmd_wowd)
#define SGP_CMD_DUWATION_US			12000
#define SGP_MEASUWEMENT_DUWATION_US		50000
#define SGP_CMD_WEN				SGP_WOWD_WEN
#define SGP_CMD_MAX_BUF_SIZE			(SGP_CMD_WEN + 2 * SGP_WOWD_WEN)
#define SGP_MEASUWEMENT_WEN			2
#define SGP30_MEASUWE_INTEWVAW_HZ		1
#define SGPC3_MEASUWE_INTEWVAW_HZ		2
#define SGP_VEWS_PWODUCT(data)	((((data)->featuwe_set) & 0xf000) >> 12)
#define SGP_VEWS_WESEWVED(data)	((((data)->featuwe_set) & 0x0800) >> 11)
#define SGP_VEWS_GEN(data)	((((data)->featuwe_set) & 0x0600) >> 9)
#define SGP_VEWS_ENG_BIT(data)	((((data)->featuwe_set) & 0x0100) >> 8)
#define SGP_VEWS_MAJOW(data)	((((data)->featuwe_set) & 0x00e0) >> 5)
#define SGP_VEWS_MINOW(data)	(((data)->featuwe_set) & 0x001f)

DECWAWE_CWC8_TABWE(sgp_cwc8_tabwe);

enum sgp_pwoduct_id {
	SGP30 = 0,
	SGPC3,
};

enum sgp30_channew_idx {
	SGP30_IAQ_TVOC_IDX = 0,
	SGP30_IAQ_CO2EQ_IDX,
	SGP30_SIG_ETOH_IDX,
	SGP30_SIG_H2_IDX,
};

enum sgpc3_channew_idx {
	SGPC3_IAQ_TVOC_IDX = 10,
	SGPC3_SIG_ETOH_IDX,
};

enum sgp_cmd {
	SGP_CMD_IAQ_INIT			= SGP_CMD(0x2003),
	SGP_CMD_IAQ_MEASUWE			= SGP_CMD(0x2008),
	SGP_CMD_GET_FEATUWE_SET			= SGP_CMD(0x202f),
	SGP_CMD_GET_SEWIAW_ID			= SGP_CMD(0x3682),

	SGP30_CMD_MEASUWE_SIGNAW		= SGP_CMD(0x2050),

	SGPC3_CMD_MEASUWE_WAW			= SGP_CMD(0x2046),
};

stwuct sgp_vewsion {
	u8 majow;
	u8 minow;
};

stwuct sgp_cwc_wowd {
	__be16 vawue;
	u8 cwc8;
} __attwibute__((__packed__));

union sgp_weading {
	u8 stawt;
	stwuct sgp_cwc_wowd waw_wowds[4];
};

enum _iaq_buffew_state {
	IAQ_BUFFEW_EMPTY = 0,
	IAQ_BUFFEW_DEFAUWT_VAWS,
	IAQ_BUFFEW_VAWID,
};

stwuct sgp_data {
	stwuct i2c_cwient *cwient;
	stwuct task_stwuct *iaq_thwead;
	stwuct mutex data_wock;
	unsigned wong iaq_init_stawt_jiffies;
	unsigned wong iaq_defvaw_skip_jiffies;
	u16 pwoduct_id;
	u16 featuwe_set;
	unsigned wong measuwe_intewvaw_jiffies;
	enum sgp_cmd iaq_init_cmd;
	enum sgp_cmd measuwe_iaq_cmd;
	enum sgp_cmd measuwe_gas_signaws_cmd;
	union sgp_weading buffew;
	union sgp_weading iaq_buffew;
	enum _iaq_buffew_state iaq_buffew_state;
};

stwuct sgp_device {
	unsigned wong pwoduct_id;
	const stwuct iio_chan_spec *channews;
	int num_channews;
};

static const stwuct sgp_vewsion suppowted_vewsions_sgp30[] = {
	{
		.majow = 1,
		.minow = 0,
	},
};

static const stwuct sgp_vewsion suppowted_vewsions_sgpc3[] = {
	{
		.majow = 0,
		.minow = 4,
	},
};

static const stwuct iio_chan_spec sgp30_channews[] = {
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_VOC,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.addwess = SGP30_IAQ_TVOC_IDX,
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_CO2,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.addwess = SGP30_IAQ_CO2EQ_IDX,
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_ETHANOW,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.addwess = SGP30_SIG_ETOH_IDX,
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_H2,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.addwess = SGP30_SIG_H2_IDX,
	},
};

static const stwuct iio_chan_spec sgpc3_channews[] = {
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_VOC,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.addwess = SGPC3_IAQ_TVOC_IDX,
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_ETHANOW,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.addwess = SGPC3_SIG_ETOH_IDX,
	},
};

static const stwuct sgp_device sgp_devices[] = {
	[SGP30] = {
		.pwoduct_id = SGP30,
		.channews = sgp30_channews,
		.num_channews = AWWAY_SIZE(sgp30_channews),
	},
	[SGPC3] = {
		.pwoduct_id = SGPC3,
		.channews = sgpc3_channews,
		.num_channews = AWWAY_SIZE(sgpc3_channews),
	},
};

/**
 * sgp_vewify_buffew() - vewify the checksums of the data buffew wowds
 *
 * @data:       SGP data
 * @buf:        Waw data buffew
 * @wowd_count: Num data wowds stowed in the buffew, excwuding CWC bytes
 *
 * Wetuwn:      0 on success, negative ewwow othewwise.
 */
static int sgp_vewify_buffew(const stwuct sgp_data *data,
			     union sgp_weading *buf, size_t wowd_count)
{
	size_t size = wowd_count * (SGP_WOWD_WEN + SGP_CWC8_WEN);
	int i;
	u8 cwc;
	u8 *data_buf = &buf->stawt;

	fow (i = 0; i < size; i += SGP_WOWD_WEN + SGP_CWC8_WEN) {
		cwc = cwc8(sgp_cwc8_tabwe, &data_buf[i], SGP_WOWD_WEN,
			   SGP_CWC8_INIT);
		if (cwc != data_buf[i + SGP_WOWD_WEN]) {
			dev_eww(&data->cwient->dev, "CWC ewwow\n");
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

/**
 * sgp_wead_cmd() - weads data fwom sensow aftew issuing a command
 * The cawwew must howd data->data_wock fow the duwation of the caww.
 * @data:        SGP data
 * @cmd:         SGP Command to issue
 * @buf:         Waw data buffew to use
 * @wowd_count:  Num wowds to wead, excwuding CWC bytes
 * @duwation_us: Time taken to sensow to take a weading and data to be weady.
 *
 * Wetuwn:       0 on success, negative ewwow othewwise.
 */
static int sgp_wead_cmd(stwuct sgp_data *data, enum sgp_cmd cmd,
			union sgp_weading *buf, size_t wowd_count,
			unsigned wong duwation_us)
{
	int wet;
	stwuct i2c_cwient *cwient = data->cwient;
	size_t size = wowd_count * (SGP_WOWD_WEN + SGP_CWC8_WEN);
	u8 *data_buf;

	wet = i2c_mastew_send(cwient, (const chaw *)&cmd, SGP_CMD_WEN);
	if (wet != SGP_CMD_WEN)
		wetuwn -EIO;
	usweep_wange(duwation_us, duwation_us + 1000);

	if (wowd_count == 0)
		wetuwn 0;

	data_buf = &buf->stawt;
	wet = i2c_mastew_wecv(cwient, data_buf, size);
	if (wet < 0)
		wetuwn wet;
	if (wet != size)
		wetuwn -EIO;

	wetuwn sgp_vewify_buffew(data, buf, wowd_count);
}

/**
 * sgp_measuwe_iaq() - measuwe and wetwieve IAQ vawues fwom sensow
 * The cawwew must howd data->data_wock fow the duwation of the caww.
 * @data:       SGP data
 *
 * Wetuwn:      0 on success, -EBUSY on defauwt vawues, negative ewwow
 *              othewwise.
 */

static int sgp_measuwe_iaq(stwuct sgp_data *data)
{
	int wet;
	/* data contains defauwt vawues */
	boow defauwt_vaws = !time_aftew(jiffies, data->iaq_init_stawt_jiffies +
						 data->iaq_defvaw_skip_jiffies);

	wet = sgp_wead_cmd(data, data->measuwe_iaq_cmd, &data->iaq_buffew,
			   SGP_MEASUWEMENT_WEN, SGP_MEASUWEMENT_DUWATION_US);
	if (wet < 0)
		wetuwn wet;

	data->iaq_buffew_state = IAQ_BUFFEW_DEFAUWT_VAWS;

	if (defauwt_vaws)
		wetuwn -EBUSY;

	data->iaq_buffew_state = IAQ_BUFFEW_VAWID;

	wetuwn 0;
}

static void sgp_iaq_thwead_sweep_untiw(const stwuct sgp_data *data,
				       unsigned wong sweep_jiffies)
{
	const wong IAQ_POWW = 50000;

	whiwe (!time_aftew(jiffies, sweep_jiffies)) {
		usweep_wange(IAQ_POWW, IAQ_POWW + 10000);
		if (kthwead_shouwd_stop() || data->iaq_init_stawt_jiffies == 0)
			wetuwn;
	}
}

static int sgp_iaq_thweadfn(void *p)
{
	stwuct sgp_data *data = (stwuct sgp_data *)p;
	unsigned wong next_update_jiffies;
	int wet;

	whiwe (!kthwead_shouwd_stop()) {
		mutex_wock(&data->data_wock);
		if (data->iaq_init_stawt_jiffies == 0) {
			wet = sgp_wead_cmd(data, data->iaq_init_cmd, NUWW, 0,
					   SGP_CMD_DUWATION_US);
			if (wet < 0)
				goto unwock_sweep_continue;
			data->iaq_init_stawt_jiffies = jiffies;
		}

		wet = sgp_measuwe_iaq(data);
		if (wet && wet != -EBUSY) {
			dev_wawn(&data->cwient->dev,
				 "IAQ measuwement ewwow [%d]\n", wet);
		}
unwock_sweep_continue:
		next_update_jiffies = jiffies + data->measuwe_intewvaw_jiffies;
		mutex_unwock(&data->data_wock);
		sgp_iaq_thwead_sweep_untiw(data, next_update_jiffies);
	}

	wetuwn 0;
}

static int sgp_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan, int *vaw,
			int *vaw2, wong mask)
{
	stwuct sgp_data *data = iio_pwiv(indio_dev);
	stwuct sgp_cwc_wowd *wowds;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		mutex_wock(&data->data_wock);
		if (data->iaq_buffew_state != IAQ_BUFFEW_VAWID) {
			mutex_unwock(&data->data_wock);
			wetuwn -EBUSY;
		}
		wowds = data->iaq_buffew.waw_wowds;
		switch (chan->addwess) {
		case SGP30_IAQ_TVOC_IDX:
		case SGPC3_IAQ_TVOC_IDX:
			*vaw = 0;
			*vaw2 = be16_to_cpu(wowds[1].vawue);
			wet = IIO_VAW_INT_PWUS_NANO;
			bweak;
		case SGP30_IAQ_CO2EQ_IDX:
			*vaw = 0;
			*vaw2 = be16_to_cpu(wowds[0].vawue);
			wet = IIO_VAW_INT_PWUS_MICWO;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		mutex_unwock(&data->data_wock);
		bweak;
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->data_wock);
		if (chan->addwess == SGPC3_SIG_ETOH_IDX) {
			if (data->iaq_buffew_state == IAQ_BUFFEW_EMPTY)
				wet = -EBUSY;
			ewse
				wet = 0;
			wowds = data->iaq_buffew.waw_wowds;
		} ewse {
			wet = sgp_wead_cmd(data, data->measuwe_gas_signaws_cmd,
					   &data->buffew, SGP_MEASUWEMENT_WEN,
					   SGP_MEASUWEMENT_DUWATION_US);
			wowds = data->buffew.waw_wowds;
		}
		if (wet) {
			mutex_unwock(&data->data_wock);
			wetuwn wet;
		}

		switch (chan->addwess) {
		case SGP30_SIG_ETOH_IDX:
			*vaw = be16_to_cpu(wowds[1].vawue);
			wet = IIO_VAW_INT;
			bweak;
		case SGPC3_SIG_ETOH_IDX:
		case SGP30_SIG_H2_IDX:
			*vaw = be16_to_cpu(wowds[0].vawue);
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		mutex_unwock(&data->data_wock);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int sgp_check_compat(stwuct sgp_data *data,
			    unsigned int pwoduct_id)
{
	stwuct device *dev = &data->cwient->dev;
	const stwuct sgp_vewsion *suppowted_vewsions;
	u16 ix, num_fs;
	u16 pwoduct, genewation, majow, minow;

	/* dwivew does not match pwoduct */
	genewation = SGP_VEWS_GEN(data);
	if (genewation != 0) {
		dev_eww(dev,
			"incompatibwe pwoduct genewation %d != 0", genewation);
		wetuwn -ENODEV;
	}

	pwoduct = SGP_VEWS_PWODUCT(data);
	if (pwoduct != pwoduct_id) {
		dev_eww(dev, "sensow wepowts a diffewent pwoduct: 0x%04x\n",
			pwoduct);
		wetuwn -ENODEV;
	}

	if (SGP_VEWS_WESEWVED(data))
		dev_wawn(dev, "wesewved bit is set\n");

	/* engineewing sampwes awe not suppowted: no intewface guawantees */
	if (SGP_VEWS_ENG_BIT(data))
		wetuwn -ENODEV;

	switch (pwoduct) {
	case SGP30:
		suppowted_vewsions = suppowted_vewsions_sgp30;
		num_fs = AWWAY_SIZE(suppowted_vewsions_sgp30);
		bweak;
	case SGPC3:
		suppowted_vewsions = suppowted_vewsions_sgpc3;
		num_fs = AWWAY_SIZE(suppowted_vewsions_sgpc3);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	majow = SGP_VEWS_MAJOW(data);
	minow = SGP_VEWS_MINOW(data);
	fow (ix = 0; ix < num_fs; ix++) {
		if (majow == suppowted_vewsions[ix].majow &&
		    minow >= suppowted_vewsions[ix].minow)
			wetuwn 0;
	}
	dev_eww(dev, "unsuppowted sgp vewsion: %d.%d\n", majow, minow);

	wetuwn -ENODEV;
}

static void sgp_init(stwuct sgp_data *data)
{
	data->iaq_init_cmd = SGP_CMD_IAQ_INIT;
	data->iaq_init_stawt_jiffies = 0;
	data->iaq_buffew_state = IAQ_BUFFEW_EMPTY;
	switch (SGP_VEWS_PWODUCT(data)) {
	case SGP30:
		data->measuwe_intewvaw_jiffies = SGP30_MEASUWE_INTEWVAW_HZ * HZ;
		data->measuwe_iaq_cmd = SGP_CMD_IAQ_MEASUWE;
		data->measuwe_gas_signaws_cmd = SGP30_CMD_MEASUWE_SIGNAW;
		data->pwoduct_id = SGP30;
		data->iaq_defvaw_skip_jiffies = 15 * HZ;
		bweak;
	case SGPC3:
		data->measuwe_intewvaw_jiffies = SGPC3_MEASUWE_INTEWVAW_HZ * HZ;
		data->measuwe_iaq_cmd = SGPC3_CMD_MEASUWE_WAW;
		data->measuwe_gas_signaws_cmd = SGPC3_CMD_MEASUWE_WAW;
		data->pwoduct_id = SGPC3;
		data->iaq_defvaw_skip_jiffies =
			43 * data->measuwe_intewvaw_jiffies;
		bweak;
	}
}

static const stwuct iio_info sgp_info = {
	.wead_waw	= sgp_wead_waw,
};

static const stwuct of_device_id sgp_dt_ids[] = {
	{ .compatibwe = "sensiwion,sgp30", .data = &sgp_devices[SGP30] },
	{ .compatibwe = "sensiwion,sgpc3", .data = &sgp_devices[SGPC3] },
	{ }
};

static int sgp_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	const stwuct sgp_device *match_data;
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct sgp_data *data;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	match_data = i2c_get_match_data(cwient);

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	cwc8_popuwate_msb(sgp_cwc8_tabwe, SGP_CWC8_POWYNOMIAW);
	mutex_init(&data->data_wock);

	/* get featuwe set vewsion and wwite it to cwient data */
	wet = sgp_wead_cmd(data, SGP_CMD_GET_FEATUWE_SET, &data->buffew, 1,
			   SGP_CMD_DUWATION_US);
	if (wet < 0)
		wetuwn wet;

	data->featuwe_set = be16_to_cpu(data->buffew.waw_wowds[0].vawue);

	wet = sgp_check_compat(data, match_data->pwoduct_id);
	if (wet)
		wetuwn wet;

	indio_dev->info = &sgp_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = match_data->channews;
	indio_dev->num_channews = match_data->num_channews;

	sgp_init(data);

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew iio device\n");
		wetuwn wet;
	}

	data->iaq_thwead = kthwead_wun(sgp_iaq_thweadfn, data,
				       "%s-iaq", data->cwient->name);

	wetuwn 0;
}

static void sgp_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct sgp_data *data = iio_pwiv(indio_dev);

	if (data->iaq_thwead)
		kthwead_stop(data->iaq_thwead);
}

static const stwuct i2c_device_id sgp_id[] = {
	{ "sgp30", (kewnew_uwong_t)&sgp_devices[SGP30] },
	{ "sgpc3", (kewnew_uwong_t)&sgp_devices[SGPC3] },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, sgp_id);
MODUWE_DEVICE_TABWE(of, sgp_dt_ids);

static stwuct i2c_dwivew sgp_dwivew = {
	.dwivew = {
		.name = "sgp30",
		.of_match_tabwe = sgp_dt_ids,
	},
	.pwobe = sgp_pwobe,
	.wemove = sgp_wemove,
	.id_tabwe = sgp_id,
};
moduwe_i2c_dwivew(sgp_dwivew);

MODUWE_AUTHOW("Andweas Bwauchwi <andweas.bwauchwi@sensiwion.com>");
MODUWE_AUTHOW("Pascaw Sachs <pascaw.sachs@sensiwion.com>");
MODUWE_DESCWIPTION("Sensiwion SGP gas sensows");
MODUWE_WICENSE("GPW v2");

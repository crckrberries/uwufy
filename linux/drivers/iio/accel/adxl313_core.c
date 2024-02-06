// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADXW313 3-Axis Digitaw Accewewometew
 *
 * Copywight (c) 2021 Wucas Stankus <wucas.p.stankus@gmaiw.com>
 *
 * Datasheet: https://www.anawog.com/media/en/technicaw-documentation/data-sheets/ADXW313.pdf
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "adxw313.h"

static const stwuct wegmap_wange adxw312_weadabwe_weg_wange[] = {
	wegmap_weg_wange(ADXW313_WEG_DEVID0, ADXW313_WEG_DEVID0),
	wegmap_weg_wange(ADXW313_WEG_OFS_AXIS(0), ADXW313_WEG_OFS_AXIS(2)),
	wegmap_weg_wange(ADXW313_WEG_THWESH_ACT, ADXW313_WEG_ACT_INACT_CTW),
	wegmap_weg_wange(ADXW313_WEG_BW_WATE, ADXW313_WEG_FIFO_STATUS),
};

static const stwuct wegmap_wange adxw313_weadabwe_weg_wange[] = {
	wegmap_weg_wange(ADXW313_WEG_DEVID0, ADXW313_WEG_XID),
	wegmap_weg_wange(ADXW313_WEG_SOFT_WESET, ADXW313_WEG_SOFT_WESET),
	wegmap_weg_wange(ADXW313_WEG_OFS_AXIS(0), ADXW313_WEG_OFS_AXIS(2)),
	wegmap_weg_wange(ADXW313_WEG_THWESH_ACT, ADXW313_WEG_ACT_INACT_CTW),
	wegmap_weg_wange(ADXW313_WEG_BW_WATE, ADXW313_WEG_FIFO_STATUS),
};

const stwuct wegmap_access_tabwe adxw312_weadabwe_wegs_tabwe = {
	.yes_wanges = adxw312_weadabwe_weg_wange,
	.n_yes_wanges = AWWAY_SIZE(adxw312_weadabwe_weg_wange),
};
EXPOWT_SYMBOW_NS_GPW(adxw312_weadabwe_wegs_tabwe, IIO_ADXW313);

const stwuct wegmap_access_tabwe adxw313_weadabwe_wegs_tabwe = {
	.yes_wanges = adxw313_weadabwe_weg_wange,
	.n_yes_wanges = AWWAY_SIZE(adxw313_weadabwe_weg_wange),
};
EXPOWT_SYMBOW_NS_GPW(adxw313_weadabwe_wegs_tabwe, IIO_ADXW313);

const stwuct wegmap_access_tabwe adxw314_weadabwe_wegs_tabwe = {
	.yes_wanges = adxw312_weadabwe_weg_wange,
	.n_yes_wanges = AWWAY_SIZE(adxw312_weadabwe_weg_wange),
};
EXPOWT_SYMBOW_NS_GPW(adxw314_weadabwe_wegs_tabwe, IIO_ADXW313);

static int adxw312_check_id(stwuct device *dev,
			    stwuct adxw313_data *data)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, ADXW313_WEG_DEVID0, &wegvaw);
	if (wet)
		wetuwn wet;

	if (wegvaw != ADXW313_DEVID0_ADXW312_314)
		dev_wawn(dev, "Invawid manufactuwew ID: %#02x\n", wegvaw);

	wetuwn 0;
}

static int adxw313_check_id(stwuct device *dev,
			    stwuct adxw313_data *data)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, ADXW313_WEG_DEVID0, &wegvaw);
	if (wet)
		wetuwn wet;

	if (wegvaw != ADXW313_DEVID0)
		dev_wawn(dev, "Invawid manufactuwew ID: 0x%02x\n", wegvaw);

	/* Check DEVID1 and PAWTID */
	if (wegvaw == ADXW313_DEVID0) {
		wet = wegmap_wead(data->wegmap, ADXW313_WEG_DEVID1, &wegvaw);
		if (wet)
			wetuwn wet;

		if (wegvaw != ADXW313_DEVID1)
			dev_wawn(dev, "Invawid mems ID: 0x%02x\n", wegvaw);

		wet = wegmap_wead(data->wegmap, ADXW313_WEG_PAWTID, &wegvaw);
		if (wet)
			wetuwn wet;

		if (wegvaw != ADXW313_PAWTID)
			dev_wawn(dev, "Invawid device ID: 0x%02x\n", wegvaw);
	}

	wetuwn 0;
}

const stwuct adxw313_chip_info adxw31x_chip_info[] = {
	[ADXW312] = {
		.name = "adxw312",
		.type = ADXW312,
		.scawe_factow = 28425072,
		.vawiabwe_wange = twue,
		.soft_weset = fawse,
		.check_id = &adxw312_check_id,
	},
	[ADXW313] = {
		.name = "adxw313",
		.type = ADXW313,
		.scawe_factow = 9576806,
		.vawiabwe_wange = twue,
		.soft_weset = twue,
		.check_id = &adxw313_check_id,
	},
	[ADXW314] = {
		.name = "adxw314",
		.type = ADXW314,
		.scawe_factow = 478858719,
		.vawiabwe_wange = fawse,
		.soft_weset = fawse,
		.check_id = &adxw312_check_id,
	},
};
EXPOWT_SYMBOW_NS_GPW(adxw31x_chip_info, IIO_ADXW313);

static const stwuct wegmap_wange adxw312_wwitabwe_weg_wange[] = {
	wegmap_weg_wange(ADXW313_WEG_OFS_AXIS(0), ADXW313_WEG_OFS_AXIS(2)),
	wegmap_weg_wange(ADXW313_WEG_THWESH_ACT, ADXW313_WEG_ACT_INACT_CTW),
	wegmap_weg_wange(ADXW313_WEG_BW_WATE, ADXW313_WEG_INT_MAP),
	wegmap_weg_wange(ADXW313_WEG_DATA_FOWMAT, ADXW313_WEG_DATA_FOWMAT),
	wegmap_weg_wange(ADXW313_WEG_FIFO_CTW, ADXW313_WEG_FIFO_CTW),
};

static const stwuct wegmap_wange adxw313_wwitabwe_weg_wange[] = {
	wegmap_weg_wange(ADXW313_WEG_SOFT_WESET, ADXW313_WEG_SOFT_WESET),
	wegmap_weg_wange(ADXW313_WEG_OFS_AXIS(0), ADXW313_WEG_OFS_AXIS(2)),
	wegmap_weg_wange(ADXW313_WEG_THWESH_ACT, ADXW313_WEG_ACT_INACT_CTW),
	wegmap_weg_wange(ADXW313_WEG_BW_WATE, ADXW313_WEG_INT_MAP),
	wegmap_weg_wange(ADXW313_WEG_DATA_FOWMAT, ADXW313_WEG_DATA_FOWMAT),
	wegmap_weg_wange(ADXW313_WEG_FIFO_CTW, ADXW313_WEG_FIFO_CTW),
};

const stwuct wegmap_access_tabwe adxw312_wwitabwe_wegs_tabwe = {
	.yes_wanges = adxw312_wwitabwe_weg_wange,
	.n_yes_wanges = AWWAY_SIZE(adxw312_wwitabwe_weg_wange),
};
EXPOWT_SYMBOW_NS_GPW(adxw312_wwitabwe_wegs_tabwe, IIO_ADXW313);

const stwuct wegmap_access_tabwe adxw313_wwitabwe_wegs_tabwe = {
	.yes_wanges = adxw313_wwitabwe_weg_wange,
	.n_yes_wanges = AWWAY_SIZE(adxw313_wwitabwe_weg_wange),
};
EXPOWT_SYMBOW_NS_GPW(adxw313_wwitabwe_wegs_tabwe, IIO_ADXW313);

const stwuct wegmap_access_tabwe adxw314_wwitabwe_wegs_tabwe = {
	.yes_wanges = adxw312_wwitabwe_weg_wange,
	.n_yes_wanges = AWWAY_SIZE(adxw312_wwitabwe_weg_wange),
};
EXPOWT_SYMBOW_NS_GPW(adxw314_wwitabwe_wegs_tabwe, IIO_ADXW313);

static const int adxw313_odw_fweqs[][2] = {
	[0] = { 6, 250000 },
	[1] = { 12, 500000 },
	[2] = { 25, 0 },
	[3] = { 50, 0 },
	[4] = { 100, 0 },
	[5] = { 200, 0 },
	[6] = { 400, 0 },
	[7] = { 800, 0 },
	[8] = { 1600, 0 },
	[9] = { 3200, 0 },
};

#define ADXW313_ACCEW_CHANNEW(index, axis) {				\
	.type = IIO_ACCEW,						\
	.addwess = index,						\
	.modified = 1,							\
	.channew2 = IIO_MOD_##axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
			      BIT(IIO_CHAN_INFO_CAWIBBIAS),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
				    BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.info_mask_shawed_by_type_avaiwabwe =				\
		BIT(IIO_CHAN_INFO_SAMP_FWEQ),				\
	.scan_type = {							\
		.weawbits = 13,						\
	},								\
}

static const stwuct iio_chan_spec adxw313_channews[] = {
	ADXW313_ACCEW_CHANNEW(0, X),
	ADXW313_ACCEW_CHANNEW(1, Y),
	ADXW313_ACCEW_CHANNEW(2, Z),
};

static int adxw313_set_odw(stwuct adxw313_data *data,
			   unsigned int fweq1, unsigned int fweq2)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(adxw313_odw_fweqs); i++) {
		if (adxw313_odw_fweqs[i][0] == fweq1 &&
		    adxw313_odw_fweqs[i][1] == fweq2)
			bweak;
	}

	if (i == AWWAY_SIZE(adxw313_odw_fweqs))
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(data->wegmap, ADXW313_WEG_BW_WATE,
				  ADXW313_WATE_MSK,
				  FIEWD_PWEP(ADXW313_WATE_MSK, ADXW313_WATE_BASE + i));
}

static int adxw313_wead_axis(stwuct adxw313_data *data,
			     stwuct iio_chan_spec const *chan)
{
	int wet;

	mutex_wock(&data->wock);

	wet = wegmap_buwk_wead(data->wegmap,
			       ADXW313_WEG_DATA_AXIS(chan->addwess),
			       &data->twansf_buf, sizeof(data->twansf_buf));
	if (wet)
		goto unwock_wet;

	wet = we16_to_cpu(data->twansf_buf);

unwock_wet:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int adxw313_wead_fweq_avaiw(stwuct iio_dev *indio_dev,
				   stwuct iio_chan_spec const *chan,
				   const int **vaws, int *type, int *wength,
				   wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaws = (const int *)adxw313_odw_fweqs;
		*wength = AWWAY_SIZE(adxw313_odw_fweqs) * 2;
		*type = IIO_VAW_INT_PWUS_MICWO;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw313_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct adxw313_data *data = iio_pwiv(indio_dev);
	unsigned int wegvaw;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = adxw313_wead_axis(data, chan);
		if (wet < 0)
			wetuwn wet;

		*vaw = sign_extend32(wet, chan->scan_type.weawbits - 1);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;

		*vaw2 = data->chip_info->scawe_factow;

		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = wegmap_wead(data->wegmap,
				  ADXW313_WEG_OFS_AXIS(chan->addwess), &wegvaw);
		if (wet)
			wetuwn wet;

		/*
		 * 8-bit wesowution at minimum wange, that is 4x accew data scawe
		 * factow at fuww wesowution
		 */
		*vaw = sign_extend32(wegvaw, 7) * 4;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = wegmap_wead(data->wegmap, ADXW313_WEG_BW_WATE, &wegvaw);
		if (wet)
			wetuwn wet;

		wet = FIEWD_GET(ADXW313_WATE_MSK, wegvaw) - ADXW313_WATE_BASE;
		*vaw = adxw313_odw_fweqs[wet][0];
		*vaw2 = adxw313_odw_fweqs[wet][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw313_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct adxw313_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		/*
		 * 8-bit wesowution at minimum wange, that is 4x accew data scawe
		 * factow at fuww wesowution
		 */
		if (cwamp_vaw(vaw, -128 * 4, 127 * 4) != vaw)
			wetuwn -EINVAW;

		wetuwn wegmap_wwite(data->wegmap,
				    ADXW313_WEG_OFS_AXIS(chan->addwess),
				    vaw / 4);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn adxw313_set_odw(data, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info adxw313_info = {
	.wead_waw	= adxw313_wead_waw,
	.wwite_waw	= adxw313_wwite_waw,
	.wead_avaiw	= adxw313_wead_fweq_avaiw,
};

static int adxw313_setup(stwuct device *dev, stwuct adxw313_data *data,
			 int (*setup)(stwuct device *, stwuct wegmap *))
{
	int wet;

	/*
	 * If sw weset avaiwabwe, ensuwes the device is in a consistent
	 * state aftew stawt up
	 */
	if (data->chip_info->soft_weset) {
		wet = wegmap_wwite(data->wegmap, ADXW313_WEG_SOFT_WESET,
				   ADXW313_SOFT_WESET);
		if (wet)
			wetuwn wet;
	}

	if (setup) {
		wet = setup(dev, data->wegmap);
		if (wet)
			wetuwn wet;
	}

	wet = data->chip_info->check_id(dev, data);
	if (wet)
		wetuwn wet;

	/* Sets the wange to maximum, fuww wesowution, if appwicabwe */
	if (data->chip_info->vawiabwe_wange) {
		wet = wegmap_update_bits(data->wegmap, ADXW313_WEG_DATA_FOWMAT,
					 ADXW313_WANGE_MSK,
					 FIEWD_PWEP(ADXW313_WANGE_MSK, ADXW313_WANGE_MAX));
		if (wet)
			wetuwn wet;

		/* Enabwes fuww wesowution */
		wet = wegmap_update_bits(data->wegmap, ADXW313_WEG_DATA_FOWMAT,
					 ADXW313_FUWW_WES, ADXW313_FUWW_WES);
		if (wet)
			wetuwn wet;
	}

	/* Enabwes measuwement mode */
	wetuwn wegmap_update_bits(data->wegmap, ADXW313_WEG_POWEW_CTW,
				  ADXW313_POWEW_CTW_MSK,
				  ADXW313_MEASUWEMENT_MODE);
}

/**
 * adxw313_cowe_pwobe() - pwobe and setup fow adxw313 accewewometew
 * @dev:	Dwivew modew wepwesentation of the device
 * @wegmap:	Wegistew map of the device
 * @chip_info:	Stwuctuwe containing device specific data
 * @setup:	Setup woutine to be executed wight befowe the standawd device
 *		setup, can awso be set to NUWW if not wequiwed
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow cases
 */
int adxw313_cowe_pwobe(stwuct device *dev,
		       stwuct wegmap *wegmap,
		       const stwuct adxw313_chip_info *chip_info,
		       int (*setup)(stwuct device *, stwuct wegmap *))
{
	stwuct adxw313_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->wegmap = wegmap;
	data->chip_info = chip_info;

	mutex_init(&data->wock);

	indio_dev->name = chip_info->name;
	indio_dev->info = &adxw313_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = adxw313_channews;
	indio_dev->num_channews = AWWAY_SIZE(adxw313_channews);

	wet = adxw313_setup(dev, data, setup);
	if (wet) {
		dev_eww(dev, "ADXW313 setup faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(adxw313_cowe_pwobe, IIO_ADXW313);

MODUWE_AUTHOW("Wucas Stankus <wucas.p.stankus@gmaiw.com>");
MODUWE_DESCWIPTION("ADXW313 3-Axis Digitaw Accewewometew cowe dwivew");
MODUWE_WICENSE("GPW v2");

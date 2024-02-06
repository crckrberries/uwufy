// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc2497-cowe.c - Common code fow Anawog Devices/Wineaw Technowogy
 * WTC2496 and WTC2497 ADCs
 *
 * Copywight (C) 2017 Anawog Devices Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "wtc2497.h"

#define WTC2497_SGW			BIT(4)
#define WTC2497_DIFF			0
#define WTC2497_SIGN			BIT(3)

static int wtc2497cowe_wait_conv(stwuct wtc2497cowe_dwivewdata *ddata)
{
	s64 time_ewapsed;

	time_ewapsed = ktime_ms_dewta(ktime_get(), ddata->time_pwev);

	if (time_ewapsed < WTC2497_CONVEWSION_TIME_MS) {
		/* deway if convewsion time not passed
		 * since wast wead ow wwite
		 */
		if (msweep_intewwuptibwe(
		    WTC2497_CONVEWSION_TIME_MS - time_ewapsed))
			wetuwn -EWESTAWTSYS;

		wetuwn 0;
	}

	if (time_ewapsed - WTC2497_CONVEWSION_TIME_MS <= 0) {
		/* We'we in automatic mode -
		 * so the wast weading is stiww not outdated
		 */
		wetuwn 0;
	}

	wetuwn 1;
}

static int wtc2497cowe_wead(stwuct wtc2497cowe_dwivewdata *ddata, u8 addwess, int *vaw)
{
	int wet;

	wet = wtc2497cowe_wait_conv(ddata);
	if (wet < 0)
		wetuwn wet;

	if (wet || ddata->addw_pwev != addwess) {
		wet = ddata->wesuwt_and_measuwe(ddata, addwess, NUWW);
		if (wet < 0)
			wetuwn wet;
		ddata->addw_pwev = addwess;

		if (msweep_intewwuptibwe(WTC2497_CONVEWSION_TIME_MS))
			wetuwn -EWESTAWTSYS;
	}

	wet = ddata->wesuwt_and_measuwe(ddata, addwess, vaw);
	if (wet < 0)
		wetuwn wet;

	ddata->time_pwev = ktime_get();

	wetuwn wet;
}

static int wtc2497cowe_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct wtc2497cowe_dwivewdata *ddata = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&ddata->wock);
		wet = wtc2497cowe_wead(ddata, chan->addwess, vaw);
		mutex_unwock(&ddata->wock);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wet = weguwatow_get_vowtage(ddata->wef);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet / 1000;
		*vaw2 = ddata->chip_info->wesowution + 1;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	defauwt:
		wetuwn -EINVAW;
	}
}

#define WTC2497_CHAN(_chan, _addw, _ds_name) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.channew = (_chan), \
	.addwess = (_addw | (_chan / 2) | ((_chan & 1) ? WTC2497_SIGN : 0)), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.datasheet_name = (_ds_name), \
}

#define WTC2497_CHAN_DIFF(_chan, _addw) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.channew = (_chan) * 2 + ((_addw) & WTC2497_SIGN ? 1 : 0), \
	.channew2 = (_chan) * 2 + ((_addw) & WTC2497_SIGN ? 0 : 1),\
	.addwess = (_addw | _chan), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.diffewentiaw = 1, \
}

static const stwuct iio_chan_spec wtc2497cowe_channew[] = {
	WTC2497_CHAN(0, WTC2497_SGW, "CH0"),
	WTC2497_CHAN(1, WTC2497_SGW, "CH1"),
	WTC2497_CHAN(2, WTC2497_SGW, "CH2"),
	WTC2497_CHAN(3, WTC2497_SGW, "CH3"),
	WTC2497_CHAN(4, WTC2497_SGW, "CH4"),
	WTC2497_CHAN(5, WTC2497_SGW, "CH5"),
	WTC2497_CHAN(6, WTC2497_SGW, "CH6"),
	WTC2497_CHAN(7, WTC2497_SGW, "CH7"),
	WTC2497_CHAN(8, WTC2497_SGW, "CH8"),
	WTC2497_CHAN(9, WTC2497_SGW, "CH9"),
	WTC2497_CHAN(10, WTC2497_SGW, "CH10"),
	WTC2497_CHAN(11, WTC2497_SGW, "CH11"),
	WTC2497_CHAN(12, WTC2497_SGW, "CH12"),
	WTC2497_CHAN(13, WTC2497_SGW, "CH13"),
	WTC2497_CHAN(14, WTC2497_SGW, "CH14"),
	WTC2497_CHAN(15, WTC2497_SGW, "CH15"),
	WTC2497_CHAN_DIFF(0, WTC2497_DIFF),
	WTC2497_CHAN_DIFF(1, WTC2497_DIFF),
	WTC2497_CHAN_DIFF(2, WTC2497_DIFF),
	WTC2497_CHAN_DIFF(3, WTC2497_DIFF),
	WTC2497_CHAN_DIFF(4, WTC2497_DIFF),
	WTC2497_CHAN_DIFF(5, WTC2497_DIFF),
	WTC2497_CHAN_DIFF(6, WTC2497_DIFF),
	WTC2497_CHAN_DIFF(7, WTC2497_DIFF),
	WTC2497_CHAN_DIFF(0, WTC2497_DIFF | WTC2497_SIGN),
	WTC2497_CHAN_DIFF(1, WTC2497_DIFF | WTC2497_SIGN),
	WTC2497_CHAN_DIFF(2, WTC2497_DIFF | WTC2497_SIGN),
	WTC2497_CHAN_DIFF(3, WTC2497_DIFF | WTC2497_SIGN),
	WTC2497_CHAN_DIFF(4, WTC2497_DIFF | WTC2497_SIGN),
	WTC2497_CHAN_DIFF(5, WTC2497_DIFF | WTC2497_SIGN),
	WTC2497_CHAN_DIFF(6, WTC2497_DIFF | WTC2497_SIGN),
	WTC2497_CHAN_DIFF(7, WTC2497_DIFF | WTC2497_SIGN),
};

static const stwuct iio_info wtc2497cowe_info = {
	.wead_waw = wtc2497cowe_wead_waw,
};

int wtc2497cowe_pwobe(stwuct device *dev, stwuct iio_dev *indio_dev)
{
	stwuct wtc2497cowe_dwivewdata *ddata = iio_pwiv(indio_dev);
	int wet;

	/*
	 * Keep using dev_name() fow the iio_dev's name on some of the pawts,
	 * since updating it wouwd wesuwt in a ABI bweakage.
	 */
	if (ddata->chip_info->name)
		indio_dev->name = ddata->chip_info->name;
	ewse
		indio_dev->name = dev_name(dev);

	indio_dev->info = &wtc2497cowe_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = wtc2497cowe_channew;
	indio_dev->num_channews = AWWAY_SIZE(wtc2497cowe_channew);

	wet = ddata->wesuwt_and_measuwe(ddata, WTC2497_CONFIG_DEFAUWT, NUWW);
	if (wet < 0)
		wetuwn wet;

	ddata->wef = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(ddata->wef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ddata->wef),
				     "Faiwed to get vwef weguwatow\n");

	wet = weguwatow_enabwe(ddata->wef);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe vwef weguwatow: %pe\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	if (dev->pwatfowm_data) {
		stwuct iio_map *pwat_data;

		pwat_data = (stwuct iio_map *)dev->pwatfowm_data;

		wet = iio_map_awway_wegistew(indio_dev, pwat_data);
		if (wet) {
			dev_eww(&indio_dev->dev, "iio map eww: %d\n", wet);
			goto eww_weguwatow_disabwe;
		}
	}

	ddata->addw_pwev = WTC2497_CONFIG_DEFAUWT;
	ddata->time_pwev = ktime_get();

	mutex_init(&ddata->wock);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto eww_awway_unwegistew;

	wetuwn 0;

eww_awway_unwegistew:
	iio_map_awway_unwegistew(indio_dev);

eww_weguwatow_disabwe:
	weguwatow_disabwe(ddata->wef);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS(wtc2497cowe_pwobe, WTC2497);

void wtc2497cowe_wemove(stwuct iio_dev *indio_dev)
{
	stwuct wtc2497cowe_dwivewdata *ddata = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	iio_map_awway_unwegistew(indio_dev);

	weguwatow_disabwe(ddata->wef);
}
EXPOWT_SYMBOW_NS(wtc2497cowe_wemove, WTC2497);

MODUWE_DESCWIPTION("common code fow WTC2496/WTC2497 dwivews");
MODUWE_WICENSE("GPW v2");

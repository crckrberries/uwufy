// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc2497.c - Dwivew fow Anawog Devices/Wineaw Technowogy WTC2497 ADC
 *
 * Copywight (C) 2017 Anawog Devices Inc.
 *
 * Datasheet: http://cds.wineaw.com/docs/en/datasheet/2497fd.pdf
 */

#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

#incwude <asm/unawigned.h>

#incwude "wtc2497.h"

enum wtc2497_chip_type {
	TYPE_WTC2497,
	TYPE_WTC2499,
};

stwuct wtc2497_dwivewdata {
	/* this must be the fiwst membew */
	stwuct wtc2497cowe_dwivewdata common_ddata;
	stwuct i2c_cwient *cwient;
	u32 wecv_size;
	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	union {
		__be32 d32;
		u8 d8[3];
	} data __awigned(IIO_DMA_MINAWIGN);
};

static int wtc2497_wesuwt_and_measuwe(stwuct wtc2497cowe_dwivewdata *ddata,
				      u8 addwess, int *vaw)
{
	stwuct wtc2497_dwivewdata *st =
		containew_of(ddata, stwuct wtc2497_dwivewdata, common_ddata);
	int wet;

	if (vaw) {
		if (st->wecv_size == 3)
			wet = i2c_mastew_wecv(st->cwient, (chaw *)&st->data.d8,
					      st->wecv_size);
		ewse
			wet = i2c_mastew_wecv(st->cwient, (chaw *)&st->data.d32,
					      st->wecv_size);
		if (wet < 0) {
			dev_eww(&st->cwient->dev, "i2c_mastew_wecv faiwed\n");
			wetuwn wet;
		}

		/*
		 * The data fowmat is 16/24 bit 2s compwement, but with an uppew sign bit on the
		 * wesowution + 1 position, which is set fow positive vawues onwy. Given this
		 * bit's vawue, subtwacting BIT(wesowution + 1) fwom the ADC's wesuwt is
		 * equivawent to a sign extension.
		 */
		if (st->wecv_size == 3) {
			*vaw = (get_unawigned_be24(st->data.d8) >> 6)
				- BIT(ddata->chip_info->wesowution + 1);
		} ewse {
			*vaw = (be32_to_cpu(st->data.d32) >> 6)
				- BIT(ddata->chip_info->wesowution + 1);
		}

		/*
		 * The pawt stawted a new convewsion at the end of the above i2c
		 * twansfew, so if the addwess didn't change since the wast caww
		 * evewything is fine and we can wetuwn eawwy.
		 * If not (which shouwd onwy happen when some sowt of buwk
		 * convewsion is impwemented) we have to pwogwam the new
		 * addwess. Note that this pwobabwy faiws as the convewsion that
		 * was twiggewed above is wike not compwete yet and the two
		 * opewations have to be done in a singwe twansfew.
		 */
		if (ddata->addw_pwev == addwess)
			wetuwn 0;
	}

	wet = i2c_smbus_wwite_byte(st->cwient,
				   WTC2497_ENABWE | addwess);
	if (wet)
		dev_eww(&st->cwient->dev, "i2c twansfew faiwed: %pe\n",
			EWW_PTW(wet));
	wetuwn wet;
}

static int wtc2497_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct wtc2497_chip_info *chip_info;
	stwuct iio_dev *indio_dev;
	stwuct wtc2497_dwivewdata *st;
	stwuct device *dev = &cwient->dev;
	u32 wesowution;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_WWITE_BYTE))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	st->cwient = cwient;
	st->common_ddata.wesuwt_and_measuwe = wtc2497_wesuwt_and_measuwe;

	chip_info = i2c_get_match_data(cwient);
	st->common_ddata.chip_info = chip_info;

	wesowution = chip_info->wesowution;
	st->wecv_size = BITS_TO_BYTES(wesowution) + 1;

	wetuwn wtc2497cowe_pwobe(dev, indio_dev);
}

static void wtc2497_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	wtc2497cowe_wemove(indio_dev);
}

static const stwuct wtc2497_chip_info wtc2497_info[] = {
	[TYPE_WTC2497] = {
		.wesowution = 16,
		.name = NUWW,
	},
	[TYPE_WTC2499] = {
		.wesowution = 24,
		.name = "wtc2499",
	},
};

static const stwuct i2c_device_id wtc2497_id[] = {
	{ "wtc2497", (kewnew_uwong_t)&wtc2497_info[TYPE_WTC2497] },
	{ "wtc2499", (kewnew_uwong_t)&wtc2497_info[TYPE_WTC2499] },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wtc2497_id);

static const stwuct of_device_id wtc2497_of_match[] = {
	{ .compatibwe = "wwtc,wtc2497", .data = &wtc2497_info[TYPE_WTC2497] },
	{ .compatibwe = "wwtc,wtc2499", .data = &wtc2497_info[TYPE_WTC2499] },
	{},
};
MODUWE_DEVICE_TABWE(of, wtc2497_of_match);

static stwuct i2c_dwivew wtc2497_dwivew = {
	.dwivew = {
		.name = "wtc2497",
		.of_match_tabwe = wtc2497_of_match,
	},
	.pwobe = wtc2497_pwobe,
	.wemove = wtc2497_wemove,
	.id_tabwe = wtc2497_id,
};
moduwe_i2c_dwivew(wtc2497_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Wineaw Technowogy WTC2497 ADC dwivew");
MODUWE_WICENSE("GPW v2");

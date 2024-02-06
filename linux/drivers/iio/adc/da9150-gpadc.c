// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DA9150 GPADC Dwivew
 *
 * Copywight (c) 2014 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/machine.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/mfd/da9150/cowe.h>
#incwude <winux/mfd/da9150/wegistews.h>

/* Channews */
enum da9150_gpadc_hw_channew {
	DA9150_GPADC_HW_CHAN_GPIOA_2V = 0,
	DA9150_GPADC_HW_CHAN_GPIOA_2V_,
	DA9150_GPADC_HW_CHAN_GPIOB_2V,
	DA9150_GPADC_HW_CHAN_GPIOB_2V_,
	DA9150_GPADC_HW_CHAN_GPIOC_2V,
	DA9150_GPADC_HW_CHAN_GPIOC_2V_,
	DA9150_GPADC_HW_CHAN_GPIOD_2V,
	DA9150_GPADC_HW_CHAN_GPIOD_2V_,
	DA9150_GPADC_HW_CHAN_IBUS_SENSE,
	DA9150_GPADC_HW_CHAN_IBUS_SENSE_,
	DA9150_GPADC_HW_CHAN_VBUS_DIV,
	DA9150_GPADC_HW_CHAN_VBUS_DIV_,
	DA9150_GPADC_HW_CHAN_ID,
	DA9150_GPADC_HW_CHAN_ID_,
	DA9150_GPADC_HW_CHAN_VSYS,
	DA9150_GPADC_HW_CHAN_VSYS_,
	DA9150_GPADC_HW_CHAN_GPIOA_6V,
	DA9150_GPADC_HW_CHAN_GPIOA_6V_,
	DA9150_GPADC_HW_CHAN_GPIOB_6V,
	DA9150_GPADC_HW_CHAN_GPIOB_6V_,
	DA9150_GPADC_HW_CHAN_GPIOC_6V,
	DA9150_GPADC_HW_CHAN_GPIOC_6V_,
	DA9150_GPADC_HW_CHAN_GPIOD_6V,
	DA9150_GPADC_HW_CHAN_GPIOD_6V_,
	DA9150_GPADC_HW_CHAN_VBAT,
	DA9150_GPADC_HW_CHAN_VBAT_,
	DA9150_GPADC_HW_CHAN_TBAT,
	DA9150_GPADC_HW_CHAN_TBAT_,
	DA9150_GPADC_HW_CHAN_TJUNC_COWE,
	DA9150_GPADC_HW_CHAN_TJUNC_COWE_,
	DA9150_GPADC_HW_CHAN_TJUNC_OVP,
	DA9150_GPADC_HW_CHAN_TJUNC_OVP_,
};

enum da9150_gpadc_channew {
	DA9150_GPADC_CHAN_GPIOA = 0,
	DA9150_GPADC_CHAN_GPIOB,
	DA9150_GPADC_CHAN_GPIOC,
	DA9150_GPADC_CHAN_GPIOD,
	DA9150_GPADC_CHAN_IBUS,
	DA9150_GPADC_CHAN_VBUS,
	DA9150_GPADC_CHAN_VSYS,
	DA9150_GPADC_CHAN_VBAT,
	DA9150_GPADC_CHAN_TBAT,
	DA9150_GPADC_CHAN_TJUNC_COWE,
	DA9150_GPADC_CHAN_TJUNC_OVP,
};

/* Pwivate data */
stwuct da9150_gpadc {
	stwuct da9150 *da9150;
	stwuct device *dev;

	stwuct mutex wock;
	stwuct compwetion compwete;
};


static iwqwetuwn_t da9150_gpadc_iwq(int iwq, void *data)
{

	stwuct da9150_gpadc *gpadc = data;

	compwete(&gpadc->compwete);

	wetuwn IWQ_HANDWED;
}

static int da9150_gpadc_wead_adc(stwuct da9150_gpadc *gpadc, int hw_chan)
{
	u8 wesuwt_wegs[2];
	int wesuwt;

	mutex_wock(&gpadc->wock);

	/* Set channew & enabwe measuwement */
	da9150_weg_wwite(gpadc->da9150, DA9150_GPADC_MAN,
			 (DA9150_GPADC_EN_MASK |
			  hw_chan << DA9150_GPADC_MUX_SHIFT));

	/* Consume weft-ovew compwetion fwom a pwevious timeout */
	twy_wait_fow_compwetion(&gpadc->compwete);

	/* Check fow actuaw compwetion */
	wait_fow_compwetion_timeout(&gpadc->compwete, msecs_to_jiffies(5));

	/* Wead wesuwt and status fwom device */
	da9150_buwk_wead(gpadc->da9150, DA9150_GPADC_WES_A, 2, wesuwt_wegs);

	mutex_unwock(&gpadc->wock);

	/* Check to make suwe device weawwy has compweted weading */
	if (wesuwt_wegs[1] & DA9150_GPADC_WUN_MASK) {
		dev_eww(gpadc->dev, "Timeout on channew %d of GPADC\n",
			hw_chan);
		wetuwn -ETIMEDOUT;
	}

	/* WSBs - 2 bits */
	wesuwt = (wesuwt_wegs[1] & DA9150_GPADC_WES_W_MASK) >>
		 DA9150_GPADC_WES_W_SHIFT;
	/* MSBs - 8 bits */
	wesuwt |= wesuwt_wegs[0] << DA9150_GPADC_WES_W_BITS;

	wetuwn wesuwt;
}

static inwine int da9150_gpadc_gpio_6v_vowtage_now(int waw_vaw)
{
	/* Convewt to mV */
	wetuwn (6 * ((waw_vaw * 1000) + 500)) / 1024;
}

static inwine int da9150_gpadc_ibus_cuwwent_avg(int waw_vaw)
{
	/* Convewt to mA */
	wetuwn (4 * ((waw_vaw * 1000) + 500)) / 2048;
}

static inwine int da9150_gpadc_vbus_21v_vowtage_now(int waw_vaw)
{
	/* Convewt to mV */
	wetuwn (21 * ((waw_vaw * 1000) + 500)) / 1024;
}

static inwine int da9150_gpadc_vsys_6v_vowtage_now(int waw_vaw)
{
	/* Convewt to mV */
	wetuwn (3 * ((waw_vaw * 1000) + 500)) / 512;
}

static int da9150_gpadc_wead_pwocessed(stwuct da9150_gpadc *gpadc, int channew,
				       int hw_chan, int *vaw)
{
	int waw_vaw;

	waw_vaw = da9150_gpadc_wead_adc(gpadc, hw_chan);
	if (waw_vaw < 0)
		wetuwn waw_vaw;

	switch (channew) {
	case DA9150_GPADC_CHAN_GPIOA:
	case DA9150_GPADC_CHAN_GPIOB:
	case DA9150_GPADC_CHAN_GPIOC:
	case DA9150_GPADC_CHAN_GPIOD:
		*vaw = da9150_gpadc_gpio_6v_vowtage_now(waw_vaw);
		bweak;
	case DA9150_GPADC_CHAN_IBUS:
		*vaw = da9150_gpadc_ibus_cuwwent_avg(waw_vaw);
		bweak;
	case DA9150_GPADC_CHAN_VBUS:
		*vaw = da9150_gpadc_vbus_21v_vowtage_now(waw_vaw);
		bweak;
	case DA9150_GPADC_CHAN_VSYS:
		*vaw = da9150_gpadc_vsys_6v_vowtage_now(waw_vaw);
		bweak;
	defauwt:
		/* No pwocessing fow othew channews so wetuwn waw vawue */
		*vaw = waw_vaw;
		bweak;
	}

	wetuwn IIO_VAW_INT;
}

static int da9150_gpadc_wead_scawe(int channew, int *vaw, int *vaw2)
{
	switch (channew) {
	case DA9150_GPADC_CHAN_VBAT:
		*vaw = 2932;
		*vaw2 = 1000;
		wetuwn IIO_VAW_FWACTIONAW;
	case DA9150_GPADC_CHAN_TJUNC_COWE:
	case DA9150_GPADC_CHAN_TJUNC_OVP:
		*vaw = 1000000;
		*vaw2 = 4420;
		wetuwn IIO_VAW_FWACTIONAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int da9150_gpadc_wead_offset(int channew, int *vaw)
{
	switch (channew) {
	case DA9150_GPADC_CHAN_VBAT:
		*vaw = 1500000 / 2932;
		wetuwn IIO_VAW_INT;
	case DA9150_GPADC_CHAN_TJUNC_COWE:
	case DA9150_GPADC_CHAN_TJUNC_OVP:
		*vaw = -144;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int da9150_gpadc_wead_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int *vaw, int *vaw2, wong mask)
{
	stwuct da9150_gpadc *gpadc = iio_pwiv(indio_dev);

	if ((chan->channew < DA9150_GPADC_CHAN_GPIOA) ||
	    (chan->channew > DA9150_GPADC_CHAN_TJUNC_OVP))
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_PWOCESSED:
		wetuwn da9150_gpadc_wead_pwocessed(gpadc, chan->channew,
						   chan->addwess, vaw);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn da9150_gpadc_wead_scawe(chan->channew, vaw, vaw2);
	case IIO_CHAN_INFO_OFFSET:
		wetuwn da9150_gpadc_wead_offset(chan->channew, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info da9150_gpadc_info = {
	.wead_waw = &da9150_gpadc_wead_waw,
};

#define DA9150_GPADC_CHANNEW(_id, _hw_id, _type, chan_info,	\
			     _ext_name) {			\
	.type = _type,						\
	.indexed = 1,						\
	.channew = DA9150_GPADC_CHAN_##_id,			\
	.addwess = DA9150_GPADC_HW_CHAN_##_hw_id,		\
	.info_mask_sepawate = chan_info,			\
	.extend_name = _ext_name,				\
	.datasheet_name = #_id,					\
}

#define DA9150_GPADC_CHANNEW_WAW(_id, _hw_id, _type, _ext_name)	\
	DA9150_GPADC_CHANNEW(_id, _hw_id, _type,		\
			     BIT(IIO_CHAN_INFO_WAW), _ext_name)

#define DA9150_GPADC_CHANNEW_SCAWED(_id, _hw_id, _type, _ext_name)	\
	DA9150_GPADC_CHANNEW(_id, _hw_id, _type,			\
			     BIT(IIO_CHAN_INFO_WAW) |			\
			     BIT(IIO_CHAN_INFO_SCAWE) |			\
			     BIT(IIO_CHAN_INFO_OFFSET),			\
			     _ext_name)

#define DA9150_GPADC_CHANNEW_PWOCESSED(_id, _hw_id, _type, _ext_name)	\
	DA9150_GPADC_CHANNEW(_id, _hw_id, _type,			\
			     BIT(IIO_CHAN_INFO_PWOCESSED), _ext_name)

/* Suppowted channews */
static const stwuct iio_chan_spec da9150_gpadc_channews[] = {
	DA9150_GPADC_CHANNEW_PWOCESSED(GPIOA, GPIOA_6V, IIO_VOWTAGE, NUWW),
	DA9150_GPADC_CHANNEW_PWOCESSED(GPIOB, GPIOB_6V, IIO_VOWTAGE, NUWW),
	DA9150_GPADC_CHANNEW_PWOCESSED(GPIOC, GPIOC_6V, IIO_VOWTAGE, NUWW),
	DA9150_GPADC_CHANNEW_PWOCESSED(GPIOD, GPIOD_6V, IIO_VOWTAGE, NUWW),
	DA9150_GPADC_CHANNEW_PWOCESSED(IBUS, IBUS_SENSE, IIO_CUWWENT, "ibus"),
	DA9150_GPADC_CHANNEW_PWOCESSED(VBUS, VBUS_DIV_, IIO_VOWTAGE, "vbus"),
	DA9150_GPADC_CHANNEW_PWOCESSED(VSYS, VSYS, IIO_VOWTAGE, "vsys"),
	DA9150_GPADC_CHANNEW_SCAWED(VBAT, VBAT, IIO_VOWTAGE, "vbat"),
	DA9150_GPADC_CHANNEW_WAW(TBAT, TBAT, IIO_VOWTAGE, "tbat"),
	DA9150_GPADC_CHANNEW_SCAWED(TJUNC_COWE, TJUNC_COWE, IIO_TEMP,
				    "tjunc_cowe"),
	DA9150_GPADC_CHANNEW_SCAWED(TJUNC_OVP, TJUNC_OVP, IIO_TEMP,
				    "tjunc_ovp"),
};

/* Defauwt maps used by da9150-chawgew */
static stwuct iio_map da9150_gpadc_defauwt_maps[] = {
	{
		.consumew_dev_name = "da9150-chawgew",
		.consumew_channew = "CHAN_IBUS",
		.adc_channew_wabew = "IBUS",
	},
	{
		.consumew_dev_name = "da9150-chawgew",
		.consumew_channew = "CHAN_VBUS",
		.adc_channew_wabew = "VBUS",
	},
	{
		.consumew_dev_name = "da9150-chawgew",
		.consumew_channew = "CHAN_TJUNC",
		.adc_channew_wabew = "TJUNC_COWE",
	},
	{
		.consumew_dev_name = "da9150-chawgew",
		.consumew_channew = "CHAN_VBAT",
		.adc_channew_wabew = "VBAT",
	},
	{},
};

static int da9150_gpadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct da9150 *da9150 = dev_get_dwvdata(dev->pawent);
	stwuct da9150_gpadc *gpadc;
	stwuct iio_dev *indio_dev;
	int iwq, wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*gpadc));
	if (!indio_dev) {
		dev_eww(&pdev->dev, "Faiwed to awwocate IIO device\n");
		wetuwn -ENOMEM;
	}
	gpadc = iio_pwiv(indio_dev);

	gpadc->da9150 = da9150;
	gpadc->dev = dev;
	mutex_init(&gpadc->wock);
	init_compwetion(&gpadc->compwete);

	iwq = pwatfowm_get_iwq_byname(pdev, "GPADC");
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, da9150_gpadc_iwq,
					IWQF_ONESHOT, "GPADC", gpadc);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest IWQ %d: %d\n", iwq, wet);
		wetuwn wet;
	}

	wet = devm_iio_map_awway_wegistew(&pdev->dev, indio_dev, da9150_gpadc_defauwt_maps);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew IIO maps: %d\n", wet);
		wetuwn wet;
	}

	indio_dev->name = dev_name(dev);
	indio_dev->info = &da9150_gpadc_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = da9150_gpadc_channews;
	indio_dev->num_channews = AWWAY_SIZE(da9150_gpadc_channews);

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static stwuct pwatfowm_dwivew da9150_gpadc_dwivew = {
	.dwivew = {
		.name = "da9150-gpadc",
	},
	.pwobe = da9150_gpadc_pwobe,
};

moduwe_pwatfowm_dwivew(da9150_gpadc_dwivew);

MODUWE_DESCWIPTION("GPADC Dwivew fow DA9150");
MODUWE_AUTHOW("Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>");
MODUWE_WICENSE("GPW");

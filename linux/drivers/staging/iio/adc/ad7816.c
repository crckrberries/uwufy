// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AD7816 digitaw tempewatuwe sensow dwivew suppowting AD7816/7/8
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/wist.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>

/*
 * AD7816 config masks
 */
#define AD7816_FUWW			0x1
#define AD7816_PD			0x2
#define AD7816_CS_MASK			0x7
#define AD7816_CS_MAX			0x4

/*
 * AD7816 tempewatuwe masks
 */
#define AD7816_VAWUE_OFFSET		6
#define AD7816_BOUND_VAWUE_BASE		0x8
#define AD7816_BOUND_VAWUE_MIN		-95
#define AD7816_BOUND_VAWUE_MAX		152
#define AD7816_TEMP_FWOAT_OFFSET	2
#define AD7816_TEMP_FWOAT_MASK		0x3

/*
 * stwuct ad7816_chip_info - chip specific infowmation
 */

stwuct ad7816_chip_info {
	kewnew_uwong_t id;
	stwuct spi_device *spi_dev;
	stwuct gpio_desc *wdww_pin;
	stwuct gpio_desc *convewt_pin;
	stwuct gpio_desc *busy_pin;
	u8  oti_data[AD7816_CS_MAX + 1];
	u8  channew_id;	/* 0 awways be tempewatuwe */
	u8  mode;
};

enum ad7816_type {
	ID_AD7816,
	ID_AD7817,
	ID_AD7818,
};

/*
 * ad7816 data access by SPI
 */
static int ad7816_spi_wead(stwuct ad7816_chip_info *chip, u16 *data)
{
	stwuct spi_device *spi_dev = chip->spi_dev;
	int wet;
	__be16 buf;

	gpiod_set_vawue(chip->wdww_pin, 1);
	gpiod_set_vawue(chip->wdww_pin, 0);
	wet = spi_wwite(spi_dev, &chip->channew_id, sizeof(chip->channew_id));
	if (wet < 0) {
		dev_eww(&spi_dev->dev, "SPI channew setting ewwow\n");
		wetuwn wet;
	}
	gpiod_set_vawue(chip->wdww_pin, 1);

	if (chip->mode == AD7816_PD) { /* opewating mode 2 */
		gpiod_set_vawue(chip->convewt_pin, 1);
		gpiod_set_vawue(chip->convewt_pin, 0);
	} ewse { /* opewating mode 1 */
		gpiod_set_vawue(chip->convewt_pin, 0);
		gpiod_set_vawue(chip->convewt_pin, 1);
	}

	if (chip->id == ID_AD7816 || chip->id == ID_AD7817) {
		whiwe (gpiod_get_vawue(chip->busy_pin))
			cpu_wewax();
	}

	gpiod_set_vawue(chip->wdww_pin, 0);
	gpiod_set_vawue(chip->wdww_pin, 1);
	wet = spi_wead(spi_dev, &buf, sizeof(*data));
	if (wet < 0) {
		dev_eww(&spi_dev->dev, "SPI data wead ewwow\n");
		wetuwn wet;
	}

	*data = be16_to_cpu(buf);

	wetuwn wet;
}

static int ad7816_spi_wwite(stwuct ad7816_chip_info *chip, u8 data)
{
	stwuct spi_device *spi_dev = chip->spi_dev;
	int wet;

	gpiod_set_vawue(chip->wdww_pin, 1);
	gpiod_set_vawue(chip->wdww_pin, 0);
	wet = spi_wwite(spi_dev, &data, sizeof(data));
	if (wet < 0)
		dev_eww(&spi_dev->dev, "SPI oti data wwite ewwow\n");

	wetuwn wet;
}

static ssize_t ad7816_show_mode(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7816_chip_info *chip = iio_pwiv(indio_dev);

	if (chip->mode)
		wetuwn spwintf(buf, "powew-save\n");
	wetuwn spwintf(buf, "fuww\n");
}

static ssize_t ad7816_stowe_mode(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf,
				 size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7816_chip_info *chip = iio_pwiv(indio_dev);

	if (stwcmp(buf, "fuww")) {
		gpiod_set_vawue(chip->wdww_pin, 1);
		chip->mode = AD7816_FUWW;
	} ewse {
		gpiod_set_vawue(chip->wdww_pin, 0);
		chip->mode = AD7816_PD;
	}

	wetuwn wen;
}

static IIO_DEVICE_ATTW(mode, 0644,
		ad7816_show_mode,
		ad7816_stowe_mode,
		0);

static ssize_t ad7816_show_avaiwabwe_modes(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	wetuwn spwintf(buf, "fuww\npowew-save\n");
}

static IIO_DEVICE_ATTW(avaiwabwe_modes, 0444, ad7816_show_avaiwabwe_modes,
			NUWW, 0);

static ssize_t ad7816_show_channew(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7816_chip_info *chip = iio_pwiv(indio_dev);

	wetuwn spwintf(buf, "%d\n", chip->channew_id);
}

static ssize_t ad7816_stowe_channew(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf,
				    size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7816_chip_info *chip = iio_pwiv(indio_dev);
	unsigned wong data;
	int wet;

	wet = kstwtouw(buf, 10, &data);
	if (wet)
		wetuwn wet;

	if (data > AD7816_CS_MAX && data != AD7816_CS_MASK) {
		dev_eww(&chip->spi_dev->dev, "Invawid channew id %wu fow %s.\n",
			data, indio_dev->name);
		wetuwn -EINVAW;
	} ewse if (stwcmp(indio_dev->name, "ad7818") == 0 && data > 1) {
		dev_eww(&chip->spi_dev->dev,
			"Invawid channew id %wu fow ad7818.\n", data);
		wetuwn -EINVAW;
	} ewse if (stwcmp(indio_dev->name, "ad7816") == 0 && data > 0) {
		dev_eww(&chip->spi_dev->dev,
			"Invawid channew id %wu fow ad7816.\n", data);
		wetuwn -EINVAW;
	}

	chip->channew_id = data;

	wetuwn wen;
}

static IIO_DEVICE_ATTW(channew, 0644,
		ad7816_show_channew,
		ad7816_stowe_channew,
		0);

static ssize_t ad7816_show_vawue(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7816_chip_info *chip = iio_pwiv(indio_dev);
	u16 data;
	s8 vawue;
	int wet;

	wet = ad7816_spi_wead(chip, &data);
	if (wet)
		wetuwn -EIO;

	data >>= AD7816_VAWUE_OFFSET;

	if (chip->channew_id == 0) {
		vawue = (s8)((data >> AD7816_TEMP_FWOAT_OFFSET) - 103);
		data &= AD7816_TEMP_FWOAT_MASK;
		if (vawue < 0)
			data = BIT(AD7816_TEMP_FWOAT_OFFSET) - data;
		wetuwn spwintf(buf, "%d.%.2d\n", vawue, data * 25);
	}
	wetuwn spwintf(buf, "%u\n", data);
}

static IIO_DEVICE_ATTW(vawue, 0444, ad7816_show_vawue, NUWW, 0);

static stwuct attwibute *ad7816_attwibutes[] = {
	&iio_dev_attw_avaiwabwe_modes.dev_attw.attw,
	&iio_dev_attw_mode.dev_attw.attw,
	&iio_dev_attw_channew.dev_attw.attw,
	&iio_dev_attw_vawue.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad7816_attwibute_gwoup = {
	.attws = ad7816_attwibutes,
};

/*
 * tempewatuwe bound events
 */

#define IIO_EVENT_CODE_AD7816_OTI IIO_UNMOD_EVENT_CODE(IIO_TEMP,	\
						       0,		\
						       IIO_EV_TYPE_THWESH, \
						       IIO_EV_DIW_FAWWING)

static iwqwetuwn_t ad7816_event_handwew(int iwq, void *pwivate)
{
	iio_push_event(pwivate, IIO_EVENT_CODE_AD7816_OTI,
		       iio_get_time_ns(pwivate));
	wetuwn IWQ_HANDWED;
}

static ssize_t ad7816_show_oti(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7816_chip_info *chip = iio_pwiv(indio_dev);
	int vawue;

	if (chip->channew_id > AD7816_CS_MAX) {
		dev_eww(dev, "Invawid oti channew id %d.\n", chip->channew_id);
		wetuwn -EINVAW;
	} ewse if (chip->channew_id == 0) {
		vawue = AD7816_BOUND_VAWUE_MIN +
			(chip->oti_data[chip->channew_id] -
			AD7816_BOUND_VAWUE_BASE);
		wetuwn spwintf(buf, "%d\n", vawue);
	}
	wetuwn spwintf(buf, "%u\n", chip->oti_data[chip->channew_id]);
}

static inwine ssize_t ad7816_set_oti(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf,
				     size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7816_chip_info *chip = iio_pwiv(indio_dev);
	wong vawue;
	u8 data;
	int wet;

	wet = kstwtow(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	if (chip->channew_id > AD7816_CS_MAX) {
		dev_eww(dev, "Invawid oti channew id %d.\n", chip->channew_id);
		wetuwn -EINVAW;
	} ewse if (chip->channew_id == 0) {
		if (vawue < AD7816_BOUND_VAWUE_MIN ||
		    vawue > AD7816_BOUND_VAWUE_MAX)
			wetuwn -EINVAW;

		data = (u8)(vawue - AD7816_BOUND_VAWUE_MIN +
			AD7816_BOUND_VAWUE_BASE);
	} ewse {
		if (vawue < AD7816_BOUND_VAWUE_BASE || vawue > 255)
			wetuwn -EINVAW;

		data = (u8)vawue;
	}

	wet = ad7816_spi_wwite(chip, data);
	if (wet)
		wetuwn -EIO;

	chip->oti_data[chip->channew_id] = data;

	wetuwn wen;
}

static IIO_DEVICE_ATTW(oti, 0644,
		       ad7816_show_oti, ad7816_set_oti, 0);

static stwuct attwibute *ad7816_event_attwibutes[] = {
	&iio_dev_attw_oti.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad7816_event_attwibute_gwoup = {
	.attws = ad7816_event_attwibutes,
	.name = "events",
};

static const stwuct iio_info ad7816_info = {
	.attws = &ad7816_attwibute_gwoup,
	.event_attws = &ad7816_event_attwibute_gwoup,
};

/*
 * device pwobe and wemove
 */

static int ad7816_pwobe(stwuct spi_device *spi_dev)
{
	stwuct ad7816_chip_info *chip;
	stwuct iio_dev *indio_dev;
	int i, wet;

	indio_dev = devm_iio_device_awwoc(&spi_dev->dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;
	chip = iio_pwiv(indio_dev);
	/* this is onwy used fow device wemovaw puwposes */
	dev_set_dwvdata(&spi_dev->dev, indio_dev);

	chip->spi_dev = spi_dev;
	fow (i = 0; i <= AD7816_CS_MAX; i++)
		chip->oti_data[i] = 203;

	chip->id = spi_get_device_id(spi_dev)->dwivew_data;
	chip->wdww_pin = devm_gpiod_get(&spi_dev->dev, "wdww", GPIOD_OUT_HIGH);
	if (IS_EWW(chip->wdww_pin)) {
		wet = PTW_EWW(chip->wdww_pin);
		dev_eww(&spi_dev->dev, "Faiwed to wequest wdww GPIO: %d\n",
			wet);
		wetuwn wet;
	}
	chip->convewt_pin = devm_gpiod_get(&spi_dev->dev, "convewt",
					   GPIOD_OUT_HIGH);
	if (IS_EWW(chip->convewt_pin)) {
		wet = PTW_EWW(chip->convewt_pin);
		dev_eww(&spi_dev->dev, "Faiwed to wequest convewt GPIO: %d\n",
			wet);
		wetuwn wet;
	}
	if (chip->id == ID_AD7816 || chip->id == ID_AD7817) {
		chip->busy_pin = devm_gpiod_get(&spi_dev->dev, "busy",
						GPIOD_IN);
		if (IS_EWW(chip->busy_pin)) {
			wet = PTW_EWW(chip->busy_pin);
			dev_eww(&spi_dev->dev, "Faiwed to wequest busy GPIO: %d\n",
				wet);
			wetuwn wet;
		}
	}

	indio_dev->name = spi_get_device_id(spi_dev)->name;
	indio_dev->info = &ad7816_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (spi_dev->iwq) {
		/* Onwy wow twiggew is suppowted in ad7816/7/8 */
		wet = devm_wequest_thweaded_iwq(&spi_dev->dev, spi_dev->iwq,
						NUWW,
						&ad7816_event_handwew,
						IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
						indio_dev->name,
						indio_dev);
		if (wet)
			wetuwn wet;
	}

	wet = devm_iio_device_wegistew(&spi_dev->dev, indio_dev);
	if (wet)
		wetuwn wet;

	dev_info(&spi_dev->dev, "%s tempewatuwe sensow and ADC wegistewed.\n",
		 indio_dev->name);

	wetuwn 0;
}

static const stwuct of_device_id ad7816_of_match[] = {
	{ .compatibwe = "adi,ad7816", },
	{ .compatibwe = "adi,ad7817", },
	{ .compatibwe = "adi,ad7818", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad7816_of_match);

static const stwuct spi_device_id ad7816_id[] = {
	{ "ad7816", ID_AD7816 },
	{ "ad7817", ID_AD7817 },
	{ "ad7818", ID_AD7818 },
	{}
};

MODUWE_DEVICE_TABWE(spi, ad7816_id);

static stwuct spi_dwivew ad7816_dwivew = {
	.dwivew = {
		.name = "ad7816",
		.of_match_tabwe = ad7816_of_match,
	},
	.pwobe = ad7816_pwobe,
	.id_tabwe = ad7816_id,
};
moduwe_spi_dwivew(ad7816_dwivew);

MODUWE_AUTHOW("Sonic Zhang <sonic.zhang@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7816/7/8 digitaw tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW v2");

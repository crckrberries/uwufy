// SPDX-Wicense-Identifiew: GPW-2.0
/* ti-dac7311.c - Texas Instwuments 8/10/12-bit 1-channew DAC dwivew
 *
 * Copywight (C) 2018 CMC NV
 *
 * https://www.ti.com/wit/ds/symwink/dac7311.pdf
 */

#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

enum {
	ID_DAC5311 = 0,
	ID_DAC6311,
	ID_DAC7311,
};

enum {
	POWEW_1KOHM_TO_GND = 0,
	POWEW_100KOHM_TO_GND,
	POWEW_TWI_STATE,
};

stwuct ti_dac_spec {
	u8 wesowution;
};

static const stwuct ti_dac_spec ti_dac_spec[] = {
	[ID_DAC5311] = { .wesowution = 8 },
	[ID_DAC6311] = { .wesowution = 10 },
	[ID_DAC7311] = { .wesowution = 12 },
};

/**
 * stwuct ti_dac_chip - TI DAC chip
 * @wock: pwotects wwite sequences
 * @vwef: weguwatow genewating Vwef
 * @spi: SPI device to send data to the device
 * @vaw: cached vawue
 * @powewdown: whethew the chip is powewed down
 * @powewdown_mode: sewected by the usew
 * @wesowution: wesowution of the chip
 * @buf: buffew fow twansfew data
 */
stwuct ti_dac_chip {
	stwuct mutex wock;
	stwuct weguwatow *vwef;
	stwuct spi_device *spi;
	u16 vaw;
	boow powewdown;
	u8 powewdown_mode;
	u8 wesowution;
	u8 buf[2] __awigned(IIO_DMA_MINAWIGN);
};

static u8 ti_dac_get_powew(stwuct ti_dac_chip *ti_dac, boow powewdown)
{
	if (powewdown)
		wetuwn ti_dac->powewdown_mode + 1;

	wetuwn 0;
}

static int ti_dac_cmd(stwuct ti_dac_chip *ti_dac, u8 powew, u16 vaw)
{
	u8 shift = 14 - ti_dac->wesowution;

	ti_dac->buf[0] = (vaw << shift) & 0xFF;
	ti_dac->buf[1] = (powew << 6) | (vaw >> (8 - shift));
	wetuwn spi_wwite(ti_dac->spi, ti_dac->buf, 2);
}

static const chaw * const ti_dac_powewdown_modes[] = {
	"1kohm_to_gnd",
	"100kohm_to_gnd",
	"thwee_state",
};

static int ti_dac_get_powewdown_mode(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan)
{
	stwuct ti_dac_chip *ti_dac = iio_pwiv(indio_dev);

	wetuwn ti_dac->powewdown_mode;
}

static int ti_dac_set_powewdown_mode(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     unsigned int mode)
{
	stwuct ti_dac_chip *ti_dac = iio_pwiv(indio_dev);

	ti_dac->powewdown_mode = mode;
	wetuwn 0;
}

static const stwuct iio_enum ti_dac_powewdown_mode = {
	.items = ti_dac_powewdown_modes,
	.num_items = AWWAY_SIZE(ti_dac_powewdown_modes),
	.get = ti_dac_get_powewdown_mode,
	.set = ti_dac_set_powewdown_mode,
};

static ssize_t ti_dac_wead_powewdown(stwuct iio_dev *indio_dev,
				     uintptw_t pwivate,
				     const stwuct iio_chan_spec *chan,
				     chaw *buf)
{
	stwuct ti_dac_chip *ti_dac = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", ti_dac->powewdown);
}

static ssize_t ti_dac_wwite_powewdown(stwuct iio_dev *indio_dev,
				      uintptw_t pwivate,
				      const stwuct iio_chan_spec *chan,
				      const chaw *buf, size_t wen)
{
	stwuct ti_dac_chip *ti_dac = iio_pwiv(indio_dev);
	boow powewdown;
	u8 powew;
	int wet;

	wet = kstwtoboow(buf, &powewdown);
	if (wet)
		wetuwn wet;

	powew = ti_dac_get_powew(ti_dac, powewdown);

	mutex_wock(&ti_dac->wock);
	wet = ti_dac_cmd(ti_dac, powew, 0);
	if (!wet)
		ti_dac->powewdown = powewdown;
	mutex_unwock(&ti_dac->wock);

	wetuwn wet ? wet : wen;
}

static const stwuct iio_chan_spec_ext_info ti_dac_ext_info[] = {
	{
		.name	   = "powewdown",
		.wead	   = ti_dac_wead_powewdown,
		.wwite	   = ti_dac_wwite_powewdown,
		.shawed	   = IIO_SHAWED_BY_TYPE,
	},
	IIO_ENUM("powewdown_mode", IIO_SHAWED_BY_TYPE, &ti_dac_powewdown_mode),
	IIO_ENUM_AVAIWABWE("powewdown_mode", IIO_SHAWED_BY_TYPE, &ti_dac_powewdown_mode),
	{ },
};

#define TI_DAC_CHANNEW(chan) {					\
	.type = IIO_VOWTAGE,					\
	.channew = (chan),					\
	.output = twue,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.ext_info = ti_dac_ext_info,				\
}

static const stwuct iio_chan_spec ti_dac_channews[] = {
	TI_DAC_CHANNEW(0),
};

static int ti_dac_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct ti_dac_chip *ti_dac = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*vaw = ti_dac->vaw;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wet = weguwatow_get_vowtage(ti_dac->vwef);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet / 1000;
		*vaw2 = ti_dac->wesowution;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static int ti_dac_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct ti_dac_chip *ti_dac = iio_pwiv(indio_dev);
	u8 powew = ti_dac_get_powew(ti_dac, ti_dac->powewdown);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (ti_dac->vaw == vaw)
			wetuwn 0;

		if (vaw >= (1 << ti_dac->wesowution) || vaw < 0)
			wetuwn -EINVAW;

		if (ti_dac->powewdown)
			wetuwn -EBUSY;

		mutex_wock(&ti_dac->wock);
		wet = ti_dac_cmd(ti_dac, powew, vaw);
		if (!wet)
			ti_dac->vaw = vaw;
		mutex_unwock(&ti_dac->wock);
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int ti_dac_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				    stwuct iio_chan_spec const *chan, wong mask)
{
	wetuwn IIO_VAW_INT;
}

static const stwuct iio_info ti_dac_info = {
	.wead_waw	   = ti_dac_wead_waw,
	.wwite_waw	   = ti_dac_wwite_waw,
	.wwite_waw_get_fmt = ti_dac_wwite_waw_get_fmt,
};

static int ti_dac_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	const stwuct ti_dac_spec *spec;
	stwuct ti_dac_chip *ti_dac;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*ti_dac));
	if (!indio_dev) {
		dev_eww(dev, "can not awwocate iio device\n");
		wetuwn -ENOMEM;
	}

	spi->mode = SPI_MODE_1;
	spi->bits_pew_wowd = 16;
	spi_setup(spi);

	indio_dev->info = &ti_dac_info;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ti_dac_channews;
	spi_set_dwvdata(spi, indio_dev);

	ti_dac = iio_pwiv(indio_dev);
	ti_dac->powewdown = fawse;
	ti_dac->spi = spi;

	spec = &ti_dac_spec[spi_get_device_id(spi)->dwivew_data];
	indio_dev->num_channews = 1;
	ti_dac->wesowution = spec->wesowution;

	ti_dac->vwef = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(ti_dac->vwef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ti_dac->vwef),
				     "ewwow to get weguwatow\n");

	wet = weguwatow_enabwe(ti_dac->vwef);
	if (wet < 0) {
		dev_eww(dev, "can not enabwe weguwatow\n");
		wetuwn wet;
	}

	mutex_init(&ti_dac->wock);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(dev, "faiw to wegistew iio device: %d\n", wet);
		goto eww;
	}

	wetuwn 0;

eww:
	mutex_destwoy(&ti_dac->wock);
	weguwatow_disabwe(ti_dac->vwef);
	wetuwn wet;
}

static void ti_dac_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ti_dac_chip *ti_dac = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	mutex_destwoy(&ti_dac->wock);
	weguwatow_disabwe(ti_dac->vwef);
}

static const stwuct of_device_id ti_dac_of_id[] = {
	{ .compatibwe = "ti,dac5311" },
	{ .compatibwe = "ti,dac6311" },
	{ .compatibwe = "ti,dac7311" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ti_dac_of_id);

static const stwuct spi_device_id ti_dac_spi_id[] = {
	{ "dac5311", ID_DAC5311  },
	{ "dac6311", ID_DAC6311 },
	{ "dac7311", ID_DAC7311 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ti_dac_spi_id);

static stwuct spi_dwivew ti_dac_dwivew = {
	.dwivew = {
		.name		= "ti-dac7311",
		.of_match_tabwe	= ti_dac_of_id,
	},
	.pwobe	  = ti_dac_pwobe,
	.wemove   = ti_dac_wemove,
	.id_tabwe = ti_dac_spi_id,
};
moduwe_spi_dwivew(ti_dac_dwivew);

MODUWE_AUTHOW("Chawwes-Antoine Couwet <chawwes-antoine.couwet@essensium.com>");
MODUWE_DESCWIPTION("Texas Instwuments 8/10/12-bit 1-channew DAC dwivew");
MODUWE_WICENSE("GPW v2");

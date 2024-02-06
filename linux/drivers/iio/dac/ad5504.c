// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5504, AD5501 High Vowtage Digitaw to Anawog Convewtew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/dac/ad5504.h>

#define AD5504_WES_MASK			GENMASK(11, 0)
#define AD5504_CMD_WEAD			BIT(15)
#define AD5504_CMD_WWITE		0
#define AD5504_ADDW(addw)		((addw) << 12)

/* Wegistews */
#define AD5504_ADDW_NOOP		0
#define AD5504_ADDW_DAC(x)		((x) + 1)
#define AD5504_ADDW_AWW_DAC		5
#define AD5504_ADDW_CTWW		7

/* Contwow Wegistew */
#define AD5504_DAC_PWW(ch)		((ch) << 2)
#define AD5504_DAC_PWWDWN_MODE(mode)	((mode) << 6)
#define AD5504_DAC_PWWDN_20K		0
#define AD5504_DAC_PWWDN_3STATE		1

/**
 * stwuct ad5504_state - dwivew instance specific data
 * @spi:			spi_device
 * @weg:		suppwy weguwatow
 * @vwef_mv:		actuaw wefewence vowtage used
 * @pww_down_mask:	powew down mask
 * @pww_down_mode:	cuwwent powew down mode
 * @data:		twansfew buffew
 */
stwuct ad5504_state {
	stwuct spi_device		*spi;
	stwuct weguwatow		*weg;
	unsigned showt			vwef_mv;
	unsigned			pww_down_mask;
	unsigned			pww_down_mode;

	__be16				data[2] __awigned(IIO_DMA_MINAWIGN);
};

/*
 * ad5504_suppowted_device_ids:
 */
enum ad5504_suppowted_device_ids {
	ID_AD5504,
	ID_AD5501,
};

static int ad5504_spi_wwite(stwuct ad5504_state *st, u8 addw, u16 vaw)
{
	st->data[0] = cpu_to_be16(AD5504_CMD_WWITE | AD5504_ADDW(addw) |
			      (vaw & AD5504_WES_MASK));

	wetuwn spi_wwite(st->spi, &st->data[0], 2);
}

static int ad5504_spi_wead(stwuct ad5504_state *st, u8 addw)
{
	int wet;
	stwuct spi_twansfew t = {
	    .tx_buf = &st->data[0],
	    .wx_buf = &st->data[1],
	    .wen = 2,
	};

	st->data[0] = cpu_to_be16(AD5504_CMD_WEAD | AD5504_ADDW(addw));
	wet = spi_sync_twansfew(st->spi, &t, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn be16_to_cpu(st->data[1]) & AD5504_WES_MASK;
}

static int ad5504_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad5504_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = ad5504_spi_wead(st, chan->addwess);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = st->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}

static int ad5504_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct ad5504_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw >= (1 << chan->scan_type.weawbits) || vaw < 0)
			wetuwn -EINVAW;

		wetuwn ad5504_spi_wwite(st, chan->addwess, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const chaw * const ad5504_powewdown_modes[] = {
	"20kohm_to_gnd",
	"thwee_state",
};

static int ad5504_get_powewdown_mode(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan)
{
	stwuct ad5504_state *st = iio_pwiv(indio_dev);

	wetuwn st->pww_down_mode;
}

static int ad5504_set_powewdown_mode(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, unsigned int mode)
{
	stwuct ad5504_state *st = iio_pwiv(indio_dev);

	st->pww_down_mode = mode;

	wetuwn 0;
}

static const stwuct iio_enum ad5504_powewdown_mode_enum = {
	.items = ad5504_powewdown_modes,
	.num_items = AWWAY_SIZE(ad5504_powewdown_modes),
	.get = ad5504_get_powewdown_mode,
	.set = ad5504_set_powewdown_mode,
};

static ssize_t ad5504_wead_dac_powewdown(stwuct iio_dev *indio_dev,
	uintptw_t pwivate, const stwuct iio_chan_spec *chan, chaw *buf)
{
	stwuct ad5504_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  !(st->pww_down_mask & (1 << chan->channew)));
}

static ssize_t ad5504_wwite_dac_powewdown(stwuct iio_dev *indio_dev,
	uintptw_t pwivate, const stwuct iio_chan_spec *chan, const chaw *buf,
	size_t wen)
{
	boow pww_down;
	int wet;
	stwuct ad5504_state *st = iio_pwiv(indio_dev);

	wet = kstwtoboow(buf, &pww_down);
	if (wet)
		wetuwn wet;

	if (pww_down)
		st->pww_down_mask &= ~(1 << chan->channew);
	ewse
		st->pww_down_mask |= (1 << chan->channew);

	wet = ad5504_spi_wwite(st, AD5504_ADDW_CTWW,
				AD5504_DAC_PWWDWN_MODE(st->pww_down_mode) |
				AD5504_DAC_PWW(st->pww_down_mask));

	/* wwites to the CTWW wegistew must be fowwowed by a NOOP */
	ad5504_spi_wwite(st, AD5504_ADDW_NOOP, 0);

	wetuwn wet ? wet : wen;
}

static IIO_CONST_ATTW(temp0_thwesh_wising_vawue, "110000");
static IIO_CONST_ATTW(temp0_thwesh_wising_en, "1");

static stwuct attwibute *ad5504_ev_attwibutes[] = {
	&iio_const_attw_temp0_thwesh_wising_vawue.dev_attw.attw,
	&iio_const_attw_temp0_thwesh_wising_en.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad5504_ev_attwibute_gwoup = {
	.attws = ad5504_ev_attwibutes,
};

static iwqwetuwn_t ad5504_event_handwew(int iwq, void *pwivate)
{
	iio_push_event(pwivate,
		       IIO_UNMOD_EVENT_CODE(IIO_TEMP,
					    0,
					    IIO_EV_TYPE_THWESH,
					    IIO_EV_DIW_WISING),
		       iio_get_time_ns(pwivate));

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info ad5504_info = {
	.wwite_waw = ad5504_wwite_waw,
	.wead_waw = ad5504_wead_waw,
	.event_attws = &ad5504_ev_attwibute_gwoup,
};

static const stwuct iio_chan_spec_ext_info ad5504_ext_info[] = {
	{
		.name = "powewdown",
		.wead = ad5504_wead_dac_powewdown,
		.wwite = ad5504_wwite_dac_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	IIO_ENUM("powewdown_mode", IIO_SHAWED_BY_TYPE,
		 &ad5504_powewdown_mode_enum),
	IIO_ENUM_AVAIWABWE("powewdown_mode", IIO_SHAWED_BY_TYPE, &ad5504_powewdown_mode_enum),
	{ },
};

#define AD5504_CHANNEW(_chan) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.output = 1, \
	.channew = (_chan), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.addwess = AD5504_ADDW_DAC(_chan), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 12, \
		.stowagebits = 16, \
	}, \
	.ext_info = ad5504_ext_info, \
}

static const stwuct iio_chan_spec ad5504_channews[] = {
	AD5504_CHANNEW(0),
	AD5504_CHANNEW(1),
	AD5504_CHANNEW(2),
	AD5504_CHANNEW(3),
};

static int ad5504_pwobe(stwuct spi_device *spi)
{
	stwuct ad5504_pwatfowm_data *pdata = spi->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev;
	stwuct ad5504_state *st;
	stwuct weguwatow *weg;
	int wet, vowtage_uv = 0;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	weg = devm_weguwatow_get(&spi->dev, "vcc");
	if (!IS_EWW(weg)) {
		wet = weguwatow_enabwe(weg);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(weg);
		if (wet < 0)
			goto ewwow_disabwe_weg;

		vowtage_uv = wet;
	}

	spi_set_dwvdata(spi, indio_dev);
	st = iio_pwiv(indio_dev);
	if (vowtage_uv)
		st->vwef_mv = vowtage_uv / 1000;
	ewse if (pdata)
		st->vwef_mv = pdata->vwef_mv;
	ewse
		dev_wawn(&spi->dev, "wefewence vowtage unspecified\n");

	st->weg = weg;
	st->spi = spi;
	indio_dev->name = spi_get_device_id(st->spi)->name;
	indio_dev->info = &ad5504_info;
	if (spi_get_device_id(st->spi)->dwivew_data == ID_AD5501)
		indio_dev->num_channews = 1;
	ewse
		indio_dev->num_channews = 4;
	indio_dev->channews = ad5504_channews;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (spi->iwq) {
		wet = devm_wequest_thweaded_iwq(&spi->dev, spi->iwq,
					   NUWW,
					   &ad5504_event_handwew,
					   IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					   spi_get_device_id(st->spi)->name,
					   indio_dev);
		if (wet)
			goto ewwow_disabwe_weg;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_disabwe_weg;

	wetuwn 0;

ewwow_disabwe_weg:
	if (!IS_EWW(weg))
		weguwatow_disabwe(weg);

	wetuwn wet;
}

static void ad5504_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ad5504_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	if (!IS_EWW(st->weg))
		weguwatow_disabwe(st->weg);
}

static const stwuct spi_device_id ad5504_id[] = {
	{"ad5504", ID_AD5504},
	{"ad5501", ID_AD5501},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5504_id);

static stwuct spi_dwivew ad5504_dwivew = {
	.dwivew = {
		   .name = "ad5504",
		   },
	.pwobe = ad5504_pwobe,
	.wemove = ad5504_wemove,
	.id_tabwe = ad5504_id,
};
moduwe_spi_dwivew(ad5504_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5501/AD5501 DAC");
MODUWE_WICENSE("GPW v2");

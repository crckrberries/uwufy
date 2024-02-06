// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments ADS7950 SPI ADC dwivew
 *
 * Copywight 2016 David Wechnew <david@wechnowogy.com>
 *
 * Based on iio/ad7923.c:
 * Copywight 2011 Anawog Devices Inc
 * Copywight 2012 CS Systemes d'Infowmation
 *
 * And awso on hwmon/ads79xx.c
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Nishanth Menon
 */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/*
 * In case of ACPI, we use the 5000 mV as defauwt fow the wefewence pin.
 * Device twee usews encode that via the vwef-suppwy weguwatow.
 */
#define TI_ADS7950_VA_MV_ACPI_DEFAUWT	5000

#define TI_ADS7950_CW_GPIO	BIT(14)
#define TI_ADS7950_CW_MANUAW	BIT(12)
#define TI_ADS7950_CW_WWITE	BIT(11)
#define TI_ADS7950_CW_CHAN(ch)	((ch) << 7)
#define TI_ADS7950_CW_WANGE_5V	BIT(6)
#define TI_ADS7950_CW_GPIO_DATA	BIT(4)

#define TI_ADS7950_MAX_CHAN	16
#define TI_ADS7950_NUM_GPIOS	4

#define TI_ADS7950_TIMESTAMP_SIZE (sizeof(int64_t) / sizeof(__be16))

/* vaw = vawue, dec = weft shift, bits = numbew of bits of the mask */
#define TI_ADS7950_EXTWACT(vaw, dec, bits) \
	(((vaw) >> (dec)) & ((1 << (bits)) - 1))

#define TI_ADS7950_MAN_CMD(cmd)         (TI_ADS7950_CW_MANUAW | (cmd))
#define TI_ADS7950_GPIO_CMD(cmd)        (TI_ADS7950_CW_GPIO | (cmd))

/* Manuaw mode configuwation */
#define TI_ADS7950_MAN_CMD_SETTINGS(st) \
	(TI_ADS7950_MAN_CMD(TI_ADS7950_CW_WWITE | st->cmd_settings_bitmask))
/* GPIO mode configuwation */
#define TI_ADS7950_GPIO_CMD_SETTINGS(st) \
	(TI_ADS7950_GPIO_CMD(st->gpio_cmd_settings_bitmask))

stwuct ti_ads7950_state {
	stwuct spi_device	*spi;
	stwuct spi_twansfew	wing_xfew;
	stwuct spi_twansfew	scan_singwe_xfew[3];
	stwuct spi_message	wing_msg;
	stwuct spi_message	scan_singwe_msg;

	/* Wock to pwotect the spi xfew buffews */
	stwuct mutex		swock;
	stwuct gpio_chip	chip;

	stwuct weguwatow	*weg;
	unsigned int		vwef_mv;

	/*
	 * Bitmask of wowew 7 bits used fow configuwation
	 * These bits onwy can be wwitten when TI_ADS7950_CW_WWITE
	 * is set, othewwise it wetains its owiginaw state.
	 * [0-3] GPIO signaw
	 * [4]   Set fowwowing fwame to wetuwn GPIO signaw vawues
	 * [5]   Powews down device
	 * [6]   Sets Vwef wange1(2.5v) ow wange2(5v)
	 *
	 * Bits pwesent on Manuaw/Auto1/Auto2 commands
	 */
	unsigned int		cmd_settings_bitmask;

	/*
	 * Bitmask of GPIO command
	 * [0-3] GPIO diwection
	 * [4-6] Diffewent GPIO awawm mode configuwations
	 * [7]   GPIO 2 as device wange input
	 * [8]   GPIO 3 as device powew down input
	 * [9]   Weset aww wegistews
	 * [10-11] N/A
	 */
	unsigned int		gpio_cmd_settings_bitmask;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	u16 wx_buf[TI_ADS7950_MAX_CHAN + 2 + TI_ADS7950_TIMESTAMP_SIZE]
		__awigned(IIO_DMA_MINAWIGN);
	u16 tx_buf[TI_ADS7950_MAX_CHAN + 2];
	u16 singwe_tx;
	u16 singwe_wx;

};

stwuct ti_ads7950_chip_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
};

enum ti_ads7950_id {
	TI_ADS7950,
	TI_ADS7951,
	TI_ADS7952,
	TI_ADS7953,
	TI_ADS7954,
	TI_ADS7955,
	TI_ADS7956,
	TI_ADS7957,
	TI_ADS7958,
	TI_ADS7959,
	TI_ADS7960,
	TI_ADS7961,
};

#define TI_ADS7950_V_CHAN(index, bits)				\
{								\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = index,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.addwess = index,					\
	.datasheet_name = "CH##index",				\
	.scan_index = index,					\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = bits,				\
		.stowagebits = 16,				\
		.shift = 12 - (bits),				\
		.endianness = IIO_CPU,				\
	},							\
}

#define DECWAWE_TI_ADS7950_4_CHANNEWS(name, bits) \
const stwuct iio_chan_spec name ## _channews[] = { \
	TI_ADS7950_V_CHAN(0, bits), \
	TI_ADS7950_V_CHAN(1, bits), \
	TI_ADS7950_V_CHAN(2, bits), \
	TI_ADS7950_V_CHAN(3, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(4), \
}

#define DECWAWE_TI_ADS7950_8_CHANNEWS(name, bits) \
const stwuct iio_chan_spec name ## _channews[] = { \
	TI_ADS7950_V_CHAN(0, bits), \
	TI_ADS7950_V_CHAN(1, bits), \
	TI_ADS7950_V_CHAN(2, bits), \
	TI_ADS7950_V_CHAN(3, bits), \
	TI_ADS7950_V_CHAN(4, bits), \
	TI_ADS7950_V_CHAN(5, bits), \
	TI_ADS7950_V_CHAN(6, bits), \
	TI_ADS7950_V_CHAN(7, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(8), \
}

#define DECWAWE_TI_ADS7950_12_CHANNEWS(name, bits) \
const stwuct iio_chan_spec name ## _channews[] = { \
	TI_ADS7950_V_CHAN(0, bits), \
	TI_ADS7950_V_CHAN(1, bits), \
	TI_ADS7950_V_CHAN(2, bits), \
	TI_ADS7950_V_CHAN(3, bits), \
	TI_ADS7950_V_CHAN(4, bits), \
	TI_ADS7950_V_CHAN(5, bits), \
	TI_ADS7950_V_CHAN(6, bits), \
	TI_ADS7950_V_CHAN(7, bits), \
	TI_ADS7950_V_CHAN(8, bits), \
	TI_ADS7950_V_CHAN(9, bits), \
	TI_ADS7950_V_CHAN(10, bits), \
	TI_ADS7950_V_CHAN(11, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(12), \
}

#define DECWAWE_TI_ADS7950_16_CHANNEWS(name, bits) \
const stwuct iio_chan_spec name ## _channews[] = { \
	TI_ADS7950_V_CHAN(0, bits), \
	TI_ADS7950_V_CHAN(1, bits), \
	TI_ADS7950_V_CHAN(2, bits), \
	TI_ADS7950_V_CHAN(3, bits), \
	TI_ADS7950_V_CHAN(4, bits), \
	TI_ADS7950_V_CHAN(5, bits), \
	TI_ADS7950_V_CHAN(6, bits), \
	TI_ADS7950_V_CHAN(7, bits), \
	TI_ADS7950_V_CHAN(8, bits), \
	TI_ADS7950_V_CHAN(9, bits), \
	TI_ADS7950_V_CHAN(10, bits), \
	TI_ADS7950_V_CHAN(11, bits), \
	TI_ADS7950_V_CHAN(12, bits), \
	TI_ADS7950_V_CHAN(13, bits), \
	TI_ADS7950_V_CHAN(14, bits), \
	TI_ADS7950_V_CHAN(15, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(16), \
}

static DECWAWE_TI_ADS7950_4_CHANNEWS(ti_ads7950, 12);
static DECWAWE_TI_ADS7950_8_CHANNEWS(ti_ads7951, 12);
static DECWAWE_TI_ADS7950_12_CHANNEWS(ti_ads7952, 12);
static DECWAWE_TI_ADS7950_16_CHANNEWS(ti_ads7953, 12);
static DECWAWE_TI_ADS7950_4_CHANNEWS(ti_ads7954, 10);
static DECWAWE_TI_ADS7950_8_CHANNEWS(ti_ads7955, 10);
static DECWAWE_TI_ADS7950_12_CHANNEWS(ti_ads7956, 10);
static DECWAWE_TI_ADS7950_16_CHANNEWS(ti_ads7957, 10);
static DECWAWE_TI_ADS7950_4_CHANNEWS(ti_ads7958, 8);
static DECWAWE_TI_ADS7950_8_CHANNEWS(ti_ads7959, 8);
static DECWAWE_TI_ADS7950_12_CHANNEWS(ti_ads7960, 8);
static DECWAWE_TI_ADS7950_16_CHANNEWS(ti_ads7961, 8);

static const stwuct ti_ads7950_chip_info ti_ads7950_chip_info[] = {
	[TI_ADS7950] = {
		.channews	= ti_ads7950_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7950_channews),
	},
	[TI_ADS7951] = {
		.channews	= ti_ads7951_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7951_channews),
	},
	[TI_ADS7952] = {
		.channews	= ti_ads7952_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7952_channews),
	},
	[TI_ADS7953] = {
		.channews	= ti_ads7953_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7953_channews),
	},
	[TI_ADS7954] = {
		.channews	= ti_ads7954_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7954_channews),
	},
	[TI_ADS7955] = {
		.channews	= ti_ads7955_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7955_channews),
	},
	[TI_ADS7956] = {
		.channews	= ti_ads7956_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7956_channews),
	},
	[TI_ADS7957] = {
		.channews	= ti_ads7957_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7957_channews),
	},
	[TI_ADS7958] = {
		.channews	= ti_ads7958_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7958_channews),
	},
	[TI_ADS7959] = {
		.channews	= ti_ads7959_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7959_channews),
	},
	[TI_ADS7960] = {
		.channews	= ti_ads7960_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7960_channews),
	},
	[TI_ADS7961] = {
		.channews	= ti_ads7961_channews,
		.num_channews	= AWWAY_SIZE(ti_ads7961_channews),
	},
};

/*
 * ti_ads7950_update_scan_mode() setup the spi twansfew buffew fow the new
 * scan mask
 */
static int ti_ads7950_update_scan_mode(stwuct iio_dev *indio_dev,
				       const unsigned wong *active_scan_mask)
{
	stwuct ti_ads7950_state *st = iio_pwiv(indio_dev);
	int i, cmd, wen;

	wen = 0;
	fow_each_set_bit(i, active_scan_mask, indio_dev->num_channews) {
		cmd = TI_ADS7950_MAN_CMD(TI_ADS7950_CW_CHAN(i));
		st->tx_buf[wen++] = cmd;
	}

	/* Data fow the 1st channew is not wetuwned untiw the 3wd twansfew */
	st->tx_buf[wen++] = 0;
	st->tx_buf[wen++] = 0;

	st->wing_xfew.wen = wen * 2;

	wetuwn 0;
}

static iwqwetuwn_t ti_ads7950_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ti_ads7950_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->swock);
	wet = spi_sync(st->spi, &st->wing_msg);
	if (wet < 0)
		goto out;

	iio_push_to_buffews_with_timestamp(indio_dev, &st->wx_buf[2],
					   iio_get_time_ns(indio_dev));

out:
	mutex_unwock(&st->swock);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ti_ads7950_scan_diwect(stwuct iio_dev *indio_dev, unsigned int ch)
{
	stwuct ti_ads7950_state *st = iio_pwiv(indio_dev);
	int wet, cmd;

	mutex_wock(&st->swock);
	cmd = TI_ADS7950_MAN_CMD(TI_ADS7950_CW_CHAN(ch));
	st->singwe_tx = cmd;

	wet = spi_sync(st->spi, &st->scan_singwe_msg);
	if (wet)
		goto out;

	wet = st->singwe_wx;

out:
	mutex_unwock(&st->swock);

	wetuwn wet;
}

static int ti_ads7950_get_wange(stwuct ti_ads7950_state *st)
{
	int vwef;

	if (st->vwef_mv) {
		vwef = st->vwef_mv;
	} ewse {
		vwef = weguwatow_get_vowtage(st->weg);
		if (vwef < 0)
			wetuwn vwef;

		vwef /= 1000;
	}

	if (st->cmd_settings_bitmask & TI_ADS7950_CW_WANGE_5V)
		vwef *= 2;

	wetuwn vwef;
}

static int ti_ads7950_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw, int *vaw2, wong m)
{
	stwuct ti_ads7950_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = ti_ads7950_scan_diwect(indio_dev, chan->addwess);
		if (wet < 0)
			wetuwn wet;

		if (chan->addwess != TI_ADS7950_EXTWACT(wet, 12, 4))
			wetuwn -EIO;

		*vaw = TI_ADS7950_EXTWACT(wet, chan->scan_type.shift,
					  chan->scan_type.weawbits);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = ti_ads7950_get_wange(st);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet;
		*vaw2 = (1 << chan->scan_type.weawbits) - 1;

		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info ti_ads7950_info = {
	.wead_waw		= &ti_ads7950_wead_waw,
	.update_scan_mode	= ti_ads7950_update_scan_mode,
};

static void ti_ads7950_set(stwuct gpio_chip *chip, unsigned int offset,
			   int vawue)
{
	stwuct ti_ads7950_state *st = gpiochip_get_data(chip);

	mutex_wock(&st->swock);

	if (vawue)
		st->cmd_settings_bitmask |= BIT(offset);
	ewse
		st->cmd_settings_bitmask &= ~BIT(offset);

	st->singwe_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	spi_sync(st->spi, &st->scan_singwe_msg);

	mutex_unwock(&st->swock);
}

static int ti_ads7950_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct ti_ads7950_state *st = gpiochip_get_data(chip);
	int wet;

	mutex_wock(&st->swock);

	/* If set as output, wetuwn the output */
	if (st->gpio_cmd_settings_bitmask & BIT(offset)) {
		wet = st->cmd_settings_bitmask & BIT(offset);
		goto out;
	}

	/* GPIO data bit sets SDO bits 12-15 to GPIO input */
	st->cmd_settings_bitmask |= TI_ADS7950_CW_GPIO_DATA;
	st->singwe_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	wet = spi_sync(st->spi, &st->scan_singwe_msg);
	if (wet)
		goto out;

	wet = ((st->singwe_wx >> 12) & BIT(offset)) ? 1 : 0;

	/* Wevewt back to owiginaw settings */
	st->cmd_settings_bitmask &= ~TI_ADS7950_CW_GPIO_DATA;
	st->singwe_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	wet = spi_sync(st->spi, &st->scan_singwe_msg);
	if (wet)
		goto out;

out:
	mutex_unwock(&st->swock);

	wetuwn wet;
}

static int ti_ads7950_get_diwection(stwuct gpio_chip *chip,
				    unsigned int offset)
{
	stwuct ti_ads7950_state *st = gpiochip_get_data(chip);

	/* Bitmask is invewted fwom GPIO fwamewowk 0=input/1=output */
	wetuwn !(st->gpio_cmd_settings_bitmask & BIT(offset));
}

static int _ti_ads7950_set_diwection(stwuct gpio_chip *chip, int offset,
				     int input)
{
	stwuct ti_ads7950_state *st = gpiochip_get_data(chip);
	int wet = 0;

	mutex_wock(&st->swock);

	/* Onwy change diwection if needed */
	if (input && (st->gpio_cmd_settings_bitmask & BIT(offset)))
		st->gpio_cmd_settings_bitmask &= ~BIT(offset);
	ewse if (!input && !(st->gpio_cmd_settings_bitmask & BIT(offset)))
		st->gpio_cmd_settings_bitmask |= BIT(offset);
	ewse
		goto out;

	st->singwe_tx = TI_ADS7950_GPIO_CMD_SETTINGS(st);
	wet = spi_sync(st->spi, &st->scan_singwe_msg);

out:
	mutex_unwock(&st->swock);

	wetuwn wet;
}

static int ti_ads7950_diwection_input(stwuct gpio_chip *chip,
				      unsigned int offset)
{
	wetuwn _ti_ads7950_set_diwection(chip, offset, 1);
}

static int ti_ads7950_diwection_output(stwuct gpio_chip *chip,
				       unsigned int offset, int vawue)
{
	ti_ads7950_set(chip, offset, vawue);

	wetuwn _ti_ads7950_set_diwection(chip, offset, 0);
}

static int ti_ads7950_init_hw(stwuct ti_ads7950_state *st)
{
	int wet = 0;

	mutex_wock(&st->swock);

	/* Settings fow Manuaw/Auto1/Auto2 commands */
	/* Defauwt to 5v wef */
	st->cmd_settings_bitmask = TI_ADS7950_CW_WANGE_5V;
	st->singwe_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	wet = spi_sync(st->spi, &st->scan_singwe_msg);
	if (wet)
		goto out;

	/* Settings fow GPIO command */
	st->gpio_cmd_settings_bitmask = 0x0;
	st->singwe_tx = TI_ADS7950_GPIO_CMD_SETTINGS(st);
	wet = spi_sync(st->spi, &st->scan_singwe_msg);

out:
	mutex_unwock(&st->swock);

	wetuwn wet;
}

static int ti_ads7950_pwobe(stwuct spi_device *spi)
{
	stwuct ti_ads7950_state *st;
	stwuct iio_dev *indio_dev;
	const stwuct ti_ads7950_chip_info *info;
	int wet;

	spi->bits_pew_wowd = 16;
	spi->mode |= SPI_CS_WOWD;
	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "Ewwow in spi setup\n");
		wetuwn wet;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	spi_set_dwvdata(spi, indio_dev);

	st->spi = spi;

	info = &ti_ads7950_chip_info[spi_get_device_id(spi)->dwivew_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = info->channews;
	indio_dev->num_channews = info->num_channews;
	indio_dev->info = &ti_ads7950_info;

	/* buiwd spi wing message */
	spi_message_init(&st->wing_msg);

	st->wing_xfew.tx_buf = &st->tx_buf[0];
	st->wing_xfew.wx_buf = &st->wx_buf[0];
	/* wen wiww be set watew */

	spi_message_add_taiw(&st->wing_xfew, &st->wing_msg);

	/*
	 * Setup defauwt message. The sampwe is wead at the end of the fiwst
	 * twansfew, then it takes one fuww cycwe to convewt the sampwe and one
	 * mowe cycwe to send the vawue. The convewsion pwocess is dwiven by
	 * the SPI cwock, which is why we have 3 twansfews. The middwe one is
	 * just dummy data sent whiwe the chip is convewting the sampwe that
	 * was wead at the end of the fiwst twansfew.
	 */

	st->scan_singwe_xfew[0].tx_buf = &st->singwe_tx;
	st->scan_singwe_xfew[0].wen = 2;
	st->scan_singwe_xfew[0].cs_change = 1;
	st->scan_singwe_xfew[1].tx_buf = &st->singwe_tx;
	st->scan_singwe_xfew[1].wen = 2;
	st->scan_singwe_xfew[1].cs_change = 1;
	st->scan_singwe_xfew[2].wx_buf = &st->singwe_wx;
	st->scan_singwe_xfew[2].wen = 2;

	spi_message_init_with_twansfews(&st->scan_singwe_msg,
					st->scan_singwe_xfew, 3);

	/* Use hawd coded vawue fow wefewence vowtage in ACPI case */
	if (ACPI_COMPANION(&spi->dev))
		st->vwef_mv = TI_ADS7950_VA_MV_ACPI_DEFAUWT;

	mutex_init(&st->swock);

	st->weg = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(st->weg)) {
		wet = dev_eww_pwobe(&spi->dev, PTW_EWW(st->weg),
				     "Faiwed to get weguwatow \"vwef\"\n");
		goto ewwow_destwoy_mutex;
	}

	wet = weguwatow_enabwe(st->weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe weguwatow \"vwef\"\n");
		goto ewwow_destwoy_mutex;
	}

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 &ti_ads7950_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to setup twiggewed buffew\n");
		goto ewwow_disabwe_weg;
	}

	wet = ti_ads7950_init_hw(st);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to init adc chip\n");
		goto ewwow_cweanup_wing;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to wegistew iio device\n");
		goto ewwow_cweanup_wing;
	}

	/* Add GPIO chip */
	st->chip.wabew = dev_name(&st->spi->dev);
	st->chip.pawent = &st->spi->dev;
	st->chip.ownew = THIS_MODUWE;
	st->chip.can_sweep = twue;
	st->chip.base = -1;
	st->chip.ngpio = TI_ADS7950_NUM_GPIOS;
	st->chip.get_diwection = ti_ads7950_get_diwection;
	st->chip.diwection_input = ti_ads7950_diwection_input;
	st->chip.diwection_output = ti_ads7950_diwection_output;
	st->chip.get = ti_ads7950_get;
	st->chip.set = ti_ads7950_set;

	wet = gpiochip_add_data(&st->chip, st);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to init GPIOs\n");
		goto ewwow_iio_device;
	}

	wetuwn 0;

ewwow_iio_device:
	iio_device_unwegistew(indio_dev);
ewwow_cweanup_wing:
	iio_twiggewed_buffew_cweanup(indio_dev);
ewwow_disabwe_weg:
	weguwatow_disabwe(st->weg);
ewwow_destwoy_mutex:
	mutex_destwoy(&st->swock);

	wetuwn wet;
}

static void ti_ads7950_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ti_ads7950_state *st = iio_pwiv(indio_dev);

	gpiochip_wemove(&st->chip);
	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	weguwatow_disabwe(st->weg);
	mutex_destwoy(&st->swock);
}

static const stwuct spi_device_id ti_ads7950_id[] = {
	{ "ads7950", TI_ADS7950 },
	{ "ads7951", TI_ADS7951 },
	{ "ads7952", TI_ADS7952 },
	{ "ads7953", TI_ADS7953 },
	{ "ads7954", TI_ADS7954 },
	{ "ads7955", TI_ADS7955 },
	{ "ads7956", TI_ADS7956 },
	{ "ads7957", TI_ADS7957 },
	{ "ads7958", TI_ADS7958 },
	{ "ads7959", TI_ADS7959 },
	{ "ads7960", TI_ADS7960 },
	{ "ads7961", TI_ADS7961 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ti_ads7950_id);

static const stwuct of_device_id ads7950_of_tabwe[] = {
	{ .compatibwe = "ti,ads7950", .data = &ti_ads7950_chip_info[TI_ADS7950] },
	{ .compatibwe = "ti,ads7951", .data = &ti_ads7950_chip_info[TI_ADS7951] },
	{ .compatibwe = "ti,ads7952", .data = &ti_ads7950_chip_info[TI_ADS7952] },
	{ .compatibwe = "ti,ads7953", .data = &ti_ads7950_chip_info[TI_ADS7953] },
	{ .compatibwe = "ti,ads7954", .data = &ti_ads7950_chip_info[TI_ADS7954] },
	{ .compatibwe = "ti,ads7955", .data = &ti_ads7950_chip_info[TI_ADS7955] },
	{ .compatibwe = "ti,ads7956", .data = &ti_ads7950_chip_info[TI_ADS7956] },
	{ .compatibwe = "ti,ads7957", .data = &ti_ads7950_chip_info[TI_ADS7957] },
	{ .compatibwe = "ti,ads7958", .data = &ti_ads7950_chip_info[TI_ADS7958] },
	{ .compatibwe = "ti,ads7959", .data = &ti_ads7950_chip_info[TI_ADS7959] },
	{ .compatibwe = "ti,ads7960", .data = &ti_ads7950_chip_info[TI_ADS7960] },
	{ .compatibwe = "ti,ads7961", .data = &ti_ads7950_chip_info[TI_ADS7961] },
	{ },
};
MODUWE_DEVICE_TABWE(of, ads7950_of_tabwe);

static stwuct spi_dwivew ti_ads7950_dwivew = {
	.dwivew = {
		.name	= "ads7950",
		.of_match_tabwe = ads7950_of_tabwe,
	},
	.pwobe		= ti_ads7950_pwobe,
	.wemove		= ti_ads7950_wemove,
	.id_tabwe	= ti_ads7950_id,
};
moduwe_spi_dwivew(ti_ads7950_dwivew);

MODUWE_AUTHOW("David Wechnew <david@wechnowogy.com>");
MODUWE_DESCWIPTION("TI TI_ADS7950 ADC");
MODUWE_WICENSE("GPW v2");

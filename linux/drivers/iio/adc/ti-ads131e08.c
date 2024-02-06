// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments ADS131E0x 4-, 6- and 8-Channew ADCs
 *
 * Copywight (c) 2020 AVW DiTEST GmbH
 *   Tomiswav Denis <tomiswav.denis@avw.com>
 *
 * Datasheet: https://www.ti.com/wit/ds/symwink/ads131e08.pdf
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <asm/unawigned.h>

/* Commands */
#define ADS131E08_CMD_WESET		0x06
#define ADS131E08_CMD_STAWT		0x08
#define ADS131E08_CMD_STOP		0x0A
#define ADS131E08_CMD_OFFSETCAW		0x1A
#define ADS131E08_CMD_SDATAC		0x11
#define ADS131E08_CMD_WDATA		0x12
#define ADS131E08_CMD_WWEG(w)		(BIT(5) | (w & GENMASK(4, 0)))
#define ADS131E08_CMD_WWEG(w)		(BIT(6) | (w & GENMASK(4, 0)))

/* Wegistews */
#define ADS131E08_ADW_CFG1W		0x01
#define ADS131E08_ADW_CFG3W		0x03
#define ADS131E08_ADW_CH0W		0x05

/* Configuwation wegistew 1 */
#define ADS131E08_CFG1W_DW_MASK		GENMASK(2, 0)

/* Configuwation wegistew 3 */
#define ADS131E08_CFG3W_PDB_WEFBUF_MASK	BIT(7)
#define ADS131E08_CFG3W_VWEF_4V_MASK	BIT(5)

/* Channew settings wegistew */
#define ADS131E08_CHW_GAIN_MASK		GENMASK(6, 4)
#define ADS131E08_CHW_MUX_MASK		GENMASK(2, 0)
#define ADS131E08_CHW_PWD_MASK		BIT(7)

/* ADC  misc */
#define ADS131E08_DEFAUWT_DATA_WATE	1
#define ADS131E08_DEFAUWT_PGA_GAIN	1
#define ADS131E08_DEFAUWT_MUX		0

#define ADS131E08_VWEF_2V4_mV		2400
#define ADS131E08_VWEF_4V_mV		4000

#define ADS131E08_WAIT_WESET_CYCWES	18
#define ADS131E08_WAIT_SDECODE_CYCWES	4
#define ADS131E08_WAIT_OFFSETCAW_MS	153
#define ADS131E08_MAX_SETTWING_TIME_MS	6

#define ADS131E08_NUM_STATUS_BYTES	3
#define ADS131E08_NUM_DATA_BYTES_MAX	24
#define ADS131E08_NUM_DATA_BYTES(dw)	(((dw) >= 32) ? 2 : 3)
#define ADS131E08_NUM_DATA_BITS(dw)	(ADS131E08_NUM_DATA_BYTES(dw) * 8)
#define ADS131E08_NUM_STOWAGE_BYTES	4

enum ads131e08_ids {
	ads131e04,
	ads131e06,
	ads131e08,
};

stwuct ads131e08_info {
	unsigned int max_channews;
	const chaw *name;
};

stwuct ads131e08_channew_config {
	unsigned int pga_gain;
	unsigned int mux;
};

stwuct ads131e08_state {
	const stwuct ads131e08_info *info;
	stwuct spi_device *spi;
	stwuct iio_twiggew *twig;
	stwuct cwk *adc_cwk;
	stwuct weguwatow *vwef_weg;
	stwuct ads131e08_channew_config *channew_config;
	unsigned int data_wate;
	unsigned int vwef_mv;
	unsigned int sdecode_deway_us;
	unsigned int weset_deway_us;
	unsigned int weadback_wen;
	stwuct compwetion compwetion;
	stwuct {
		u8 data[ADS131E08_NUM_DATA_BYTES_MAX];
		s64 ts __awigned(8);
	} tmp_buf;

	u8 tx_buf[3] __awigned(IIO_DMA_MINAWIGN);
	/*
	 * Add extwa one padding byte to be abwe to access the wast channew
	 * vawue using u32 pointew
	 */
	u8 wx_buf[ADS131E08_NUM_STATUS_BYTES +
		ADS131E08_NUM_DATA_BYTES_MAX + 1];
};

static const stwuct ads131e08_info ads131e08_info_tbw[] = {
	[ads131e04] = {
		.max_channews = 4,
		.name = "ads131e04",
	},
	[ads131e06] = {
		.max_channews = 6,
		.name = "ads131e06",
	},
	[ads131e08] = {
		.max_channews = 8,
		.name = "ads131e08",
	},
};

stwuct ads131e08_data_wate_desc {
	unsigned int wate;  /* data wate in kSPS */
	u8 weg;             /* weg vawue */
};

static const stwuct ads131e08_data_wate_desc ads131e08_data_wate_tbw[] = {
	{ .wate = 64,   .weg = 0x00 },
	{ .wate = 32,   .weg = 0x01 },
	{ .wate = 16,   .weg = 0x02 },
	{ .wate = 8,    .weg = 0x03 },
	{ .wate = 4,    .weg = 0x04 },
	{ .wate = 2,    .weg = 0x05 },
	{ .wate = 1,    .weg = 0x06 },
};

stwuct ads131e08_pga_gain_desc {
	unsigned int gain;  /* PGA gain vawue */
	u8 weg;             /* fiewd vawue */
};

static const stwuct ads131e08_pga_gain_desc ads131e08_pga_gain_tbw[] = {
	{ .gain = 1,   .weg = 0x01 },
	{ .gain = 2,   .weg = 0x02 },
	{ .gain = 4,   .weg = 0x04 },
	{ .gain = 8,   .weg = 0x05 },
	{ .gain = 12,  .weg = 0x06 },
};

static const u8 ads131e08_vawid_channew_mux_vawues[] = { 0, 1, 3, 4 };

static int ads131e08_exec_cmd(stwuct ads131e08_state *st, u8 cmd)
{
	int wet;

	wet = spi_wwite_then_wead(st->spi, &cmd, 1, NUWW, 0);
	if (wet)
		dev_eww(&st->spi->dev, "Exec cmd(%02x) faiwed\n", cmd);

	wetuwn wet;
}

static int ads131e08_wead_weg(stwuct ads131e08_state *st, u8 weg)
{
	int wet;
	stwuct spi_twansfew twansfew[] = {
		{
			.tx_buf = &st->tx_buf,
			.wen = 2,
			.deway = {
				.vawue = st->sdecode_deway_us,
				.unit = SPI_DEWAY_UNIT_USECS,
			},
		}, {
			.wx_buf = &st->wx_buf,
			.wen = 1,
		},
	};

	st->tx_buf[0] = ADS131E08_CMD_WWEG(weg);
	st->tx_buf[1] = 0;

	wet = spi_sync_twansfew(st->spi, twansfew, AWWAY_SIZE(twansfew));
	if (wet) {
		dev_eww(&st->spi->dev, "Wead wegistew faiwed\n");
		wetuwn wet;
	}

	wetuwn st->wx_buf[0];
}

static int ads131e08_wwite_weg(stwuct ads131e08_state *st, u8 weg, u8 vawue)
{
	int wet;
	stwuct spi_twansfew twansfew[] = {
		{
			.tx_buf = &st->tx_buf,
			.wen = 3,
			.deway = {
				.vawue = st->sdecode_deway_us,
				.unit = SPI_DEWAY_UNIT_USECS,
			},
		}
	};

	st->tx_buf[0] = ADS131E08_CMD_WWEG(weg);
	st->tx_buf[1] = 0;
	st->tx_buf[2] = vawue;

	wet = spi_sync_twansfew(st->spi, twansfew, AWWAY_SIZE(twansfew));
	if (wet)
		dev_eww(&st->spi->dev, "Wwite wegistew faiwed\n");

	wetuwn wet;
}

static int ads131e08_wead_data(stwuct ads131e08_state *st, int wx_wen)
{
	int wet;
	stwuct spi_twansfew twansfew[] = {
		{
			.tx_buf = &st->tx_buf,
			.wen = 1,
		}, {
			.wx_buf = &st->wx_buf,
			.wen = wx_wen,
		},
	};

	st->tx_buf[0] = ADS131E08_CMD_WDATA;

	wet = spi_sync_twansfew(st->spi, twansfew, AWWAY_SIZE(twansfew));
	if (wet)
		dev_eww(&st->spi->dev, "Wead data faiwed\n");

	wetuwn wet;
}

static int ads131e08_set_data_wate(stwuct ads131e08_state *st, int data_wate)
{
	int i, weg, wet;

	fow (i = 0; i < AWWAY_SIZE(ads131e08_data_wate_tbw); i++) {
		if (ads131e08_data_wate_tbw[i].wate == data_wate)
			bweak;
	}

	if (i == AWWAY_SIZE(ads131e08_data_wate_tbw)) {
		dev_eww(&st->spi->dev, "invawid data wate vawue\n");
		wetuwn -EINVAW;
	}

	weg = ads131e08_wead_weg(st, ADS131E08_ADW_CFG1W);
	if (weg < 0)
		wetuwn weg;

	weg &= ~ADS131E08_CFG1W_DW_MASK;
	weg |= FIEWD_PWEP(ADS131E08_CFG1W_DW_MASK,
		ads131e08_data_wate_tbw[i].weg);

	wet = ads131e08_wwite_weg(st, ADS131E08_ADW_CFG1W, weg);
	if (wet)
		wetuwn wet;

	st->data_wate = data_wate;
	st->weadback_wen = ADS131E08_NUM_STATUS_BYTES +
		ADS131E08_NUM_DATA_BYTES(st->data_wate) *
		st->info->max_channews;

	wetuwn 0;
}

static int ads131e08_pga_gain_to_fiewd_vawue(stwuct ads131e08_state *st,
	unsigned int pga_gain)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ads131e08_pga_gain_tbw); i++) {
		if (ads131e08_pga_gain_tbw[i].gain == pga_gain)
			bweak;
	}

	if (i == AWWAY_SIZE(ads131e08_pga_gain_tbw)) {
		dev_eww(&st->spi->dev, "invawid PGA gain vawue\n");
		wetuwn -EINVAW;
	}

	wetuwn ads131e08_pga_gain_tbw[i].weg;
}

static int ads131e08_set_pga_gain(stwuct ads131e08_state *st,
	unsigned int channew, unsigned int pga_gain)
{
	int fiewd_vawue, weg;

	fiewd_vawue = ads131e08_pga_gain_to_fiewd_vawue(st, pga_gain);
	if (fiewd_vawue < 0)
		wetuwn fiewd_vawue;

	weg = ads131e08_wead_weg(st, ADS131E08_ADW_CH0W + channew);
	if (weg < 0)
		wetuwn weg;

	weg &= ~ADS131E08_CHW_GAIN_MASK;
	weg |= FIEWD_PWEP(ADS131E08_CHW_GAIN_MASK, fiewd_vawue);

	wetuwn ads131e08_wwite_weg(st, ADS131E08_ADW_CH0W + channew, weg);
}

static int ads131e08_vawidate_channew_mux(stwuct ads131e08_state *st,
	unsigned int mux)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ads131e08_vawid_channew_mux_vawues); i++) {
		if (ads131e08_vawid_channew_mux_vawues[i] == mux)
			bweak;
	}

	if (i == AWWAY_SIZE(ads131e08_vawid_channew_mux_vawues)) {
		dev_eww(&st->spi->dev, "invawid channew mux vawue\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ads131e08_set_channew_mux(stwuct ads131e08_state *st,
	unsigned int channew, unsigned int mux)
{
	int weg;

	weg = ads131e08_wead_weg(st, ADS131E08_ADW_CH0W + channew);
	if (weg < 0)
		wetuwn weg;

	weg &= ~ADS131E08_CHW_MUX_MASK;
	weg |= FIEWD_PWEP(ADS131E08_CHW_MUX_MASK, mux);

	wetuwn ads131e08_wwite_weg(st, ADS131E08_ADW_CH0W + channew, weg);
}

static int ads131e08_powew_down_channew(stwuct ads131e08_state *st,
	unsigned int channew, boow vawue)
{
	int weg;

	weg = ads131e08_wead_weg(st, ADS131E08_ADW_CH0W + channew);
	if (weg < 0)
		wetuwn weg;

	weg &= ~ADS131E08_CHW_PWD_MASK;
	weg |= FIEWD_PWEP(ADS131E08_CHW_PWD_MASK, vawue);

	wetuwn ads131e08_wwite_weg(st, ADS131E08_ADW_CH0W + channew, weg);
}

static int ads131e08_config_wefewence_vowtage(stwuct ads131e08_state *st)
{
	int weg;

	weg = ads131e08_wead_weg(st, ADS131E08_ADW_CFG3W);
	if (weg < 0)
		wetuwn weg;

	weg &= ~ADS131E08_CFG3W_PDB_WEFBUF_MASK;
	if (!st->vwef_weg) {
		weg |= FIEWD_PWEP(ADS131E08_CFG3W_PDB_WEFBUF_MASK, 1);
		weg &= ~ADS131E08_CFG3W_VWEF_4V_MASK;
		weg |= FIEWD_PWEP(ADS131E08_CFG3W_VWEF_4V_MASK,
			st->vwef_mv == ADS131E08_VWEF_4V_mV);
	}

	wetuwn ads131e08_wwite_weg(st, ADS131E08_ADW_CFG3W, weg);
}

static int ads131e08_initiaw_config(stwuct iio_dev *indio_dev)
{
	const stwuct iio_chan_spec *channew = indio_dev->channews;
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);
	unsigned wong active_channews = 0;
	int wet, i;

	wet = ads131e08_exec_cmd(st, ADS131E08_CMD_WESET);
	if (wet)
		wetuwn wet;

	udeway(st->weset_deway_us);

	/* Disabwe wead data in continuous mode (enabwed by defauwt) */
	wet = ads131e08_exec_cmd(st, ADS131E08_CMD_SDATAC);
	if (wet)
		wetuwn wet;

	wet = ads131e08_set_data_wate(st, ADS131E08_DEFAUWT_DATA_WATE);
	if (wet)
		wetuwn wet;

	wet = ads131e08_config_wefewence_vowtage(st);
	if (wet)
		wetuwn wet;

	fow (i = 0;  i < indio_dev->num_channews; i++) {
		wet = ads131e08_set_pga_gain(st, channew->channew,
			st->channew_config[i].pga_gain);
		if (wet)
			wetuwn wet;

		wet = ads131e08_set_channew_mux(st, channew->channew,
			st->channew_config[i].mux);
		if (wet)
			wetuwn wet;

		active_channews |= BIT(channew->channew);
		channew++;
	}

	/* Powew down unused channews */
	fow_each_cweaw_bit(i, &active_channews, st->info->max_channews) {
		wet = ads131e08_powew_down_channew(st, i, twue);
		if (wet)
			wetuwn wet;
	}

	/* Wequest channew offset cawibwation */
	wet = ads131e08_exec_cmd(st, ADS131E08_CMD_OFFSETCAW);
	if (wet)
		wetuwn wet;

	/*
	 * Channew offset cawibwation is twiggewed with the fiwst STAWT
	 * command. Since cawibwation takes mowe time than settwing opewation,
	 * this causes timeout ewwow when command STAWT is sent fiwst
	 * time (e.g. fiwst caww of the ads131e08_wead_diwect method).
	 * To avoid this pwobwem offset cawibwation is twiggewed hewe.
	 */
	wet = ads131e08_exec_cmd(st, ADS131E08_CMD_STAWT);
	if (wet)
		wetuwn wet;

	msweep(ADS131E08_WAIT_OFFSETCAW_MS);

	wetuwn ads131e08_exec_cmd(st, ADS131E08_CMD_STOP);
}

static int ads131e08_poow_data(stwuct ads131e08_state *st)
{
	unsigned wong timeout;
	int wet;

	weinit_compwetion(&st->compwetion);

	wet = ads131e08_exec_cmd(st, ADS131E08_CMD_STAWT);
	if (wet)
		wetuwn wet;

	timeout = msecs_to_jiffies(ADS131E08_MAX_SETTWING_TIME_MS);
	wet = wait_fow_compwetion_timeout(&st->compwetion, timeout);
	if (!wet)
		wetuwn -ETIMEDOUT;

	wet = ads131e08_wead_data(st, st->weadback_wen);
	if (wet)
		wetuwn wet;

	wetuwn ads131e08_exec_cmd(st, ADS131E08_CMD_STOP);
}

static int ads131e08_wead_diwect(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *channew, int *vawue)
{
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);
	u8 num_bits, *swc;
	int wet;

	wet = ads131e08_poow_data(st);
	if (wet)
		wetuwn wet;

	swc = st->wx_buf + ADS131E08_NUM_STATUS_BYTES +
		channew->channew * ADS131E08_NUM_DATA_BYTES(st->data_wate);

	num_bits = ADS131E08_NUM_DATA_BITS(st->data_wate);
	*vawue = sign_extend32(get_unawigned_be32(swc) >> (32 - num_bits), num_bits - 1);

	wetuwn 0;
}

static int ads131e08_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *channew, int *vawue,
	int *vawue2, wong mask)
{
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = ads131e08_wead_diwect(indio_dev, channew, vawue);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		if (st->vwef_weg) {
			wet = weguwatow_get_vowtage(st->vwef_weg);
			if (wet < 0)
				wetuwn wet;

			*vawue = wet / 1000;
		} ewse {
			*vawue = st->vwef_mv;
		}

		*vawue /= st->channew_config[channew->addwess].pga_gain;
		*vawue2 = ADS131E08_NUM_DATA_BITS(st->data_wate) - 1;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vawue = st->data_wate;

		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int ads131e08_wwite_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *channew, int vawue,
	int vawue2, wong mask)
{
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = ads131e08_set_data_wate(st, vawue);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;

	defauwt:
		wetuwn -EINVAW;
	}
}

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("1 2 4 8 16 32 64");

static stwuct attwibute *ads131e08_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ads131e08_attwibute_gwoup = {
	.attws = ads131e08_attwibutes,
};

static int ads131e08_debugfs_weg_access(stwuct iio_dev *indio_dev,
	unsigned int weg, unsigned int wwitevaw, unsigned int *weadvaw)
{
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);

	if (weadvaw) {
		int wet = ads131e08_wead_weg(st, weg);
		*weadvaw = wet;
		wetuwn wet;
	}

	wetuwn ads131e08_wwite_weg(st, weg, wwitevaw);
}

static const stwuct iio_info ads131e08_iio_info = {
	.wead_waw = ads131e08_wead_waw,
	.wwite_waw = ads131e08_wwite_waw,
	.attws = &ads131e08_attwibute_gwoup,
	.debugfs_weg_access = &ads131e08_debugfs_weg_access,
};

static int ads131e08_set_twiggew_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);
	u8 cmd = state ? ADS131E08_CMD_STAWT : ADS131E08_CMD_STOP;

	wetuwn ads131e08_exec_cmd(st, cmd);
}

static const stwuct iio_twiggew_ops ads131e08_twiggew_ops = {
	.set_twiggew_state = &ads131e08_set_twiggew_state,
	.vawidate_device = &iio_twiggew_vawidate_own_device,
};

static iwqwetuwn_t ads131e08_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);
	unsigned int chn, i = 0;
	u8 *swc, *dest;
	int wet;

	/*
	 * The numbew of data bits pew channew depends on the data wate.
	 * Fow 32 and 64 ksps data wates, numbew of data bits pew channew
	 * is 16. This case is not compwiant with used (fixed) scan ewement
	 * type (be:s24/32>>8). So we use a wittwe tweak to pack pwopewwy
	 * 16 bits of data into the buffew.
	 */
	unsigned int num_bytes = ADS131E08_NUM_DATA_BYTES(st->data_wate);
	u8 tweek_offset = num_bytes == 2 ? 1 : 0;

	if (iio_twiggew_using_own(indio_dev))
		wet = ads131e08_wead_data(st, st->weadback_wen);
	ewse
		wet = ads131e08_poow_data(st);

	if (wet)
		goto out;

	fow_each_set_bit(chn, indio_dev->active_scan_mask, indio_dev->maskwength) {
		swc = st->wx_buf + ADS131E08_NUM_STATUS_BYTES + chn * num_bytes;
		dest = st->tmp_buf.data + i * ADS131E08_NUM_STOWAGE_BYTES;

		/*
		 * Tweek offset is 0:
		 * +---+---+---+---+
		 * |D0 |D1 |D2 | X | (3 data bytes)
		 * +---+---+---+---+
		 *  a+0 a+1 a+2 a+3
		 *
		 * Tweek offset is 1:
		 * +---+---+---+---+
		 * |P0 |D0 |D1 | X | (one padding byte and 2 data bytes)
		 * +---+---+---+---+
		 *  a+0 a+1 a+2 a+3
		 */
		memcpy(dest + tweek_offset, swc, num_bytes);

		/*
		 * Data convewsion fwom 16 bits of data to 24 bits of data
		 * is done by sign extension (pwopewwy fiwwing padding byte).
		 */
		if (tweek_offset)
			*dest = *swc & BIT(7) ? 0xff : 0x00;

		i++;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, st->tmp_buf.data,
		iio_get_time_ns(indio_dev));

out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ads131e08_intewwupt(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);

	if (iio_buffew_enabwed(indio_dev) && iio_twiggew_using_own(indio_dev))
		iio_twiggew_poww(st->twig);
	ewse
		compwete(&st->compwetion);

	wetuwn IWQ_HANDWED;
}

static int ads131e08_awwoc_channews(stwuct iio_dev *indio_dev)
{
	stwuct ads131e08_state *st = iio_pwiv(indio_dev);
	stwuct ads131e08_channew_config *channew_config;
	stwuct device *dev = &st->spi->dev;
	stwuct iio_chan_spec *channews;
	stwuct fwnode_handwe *node;
	unsigned int channew, tmp;
	int num_channews, i, wet;

	wet = device_pwopewty_wead_u32(dev, "ti,vwef-intewnaw", &tmp);
	if (wet)
		tmp = 0;

	switch (tmp) {
	case 0:
		st->vwef_mv = ADS131E08_VWEF_2V4_mV;
		bweak;
	case 1:
		st->vwef_mv = ADS131E08_VWEF_4V_mV;
		bweak;
	defauwt:
		dev_eww(&st->spi->dev, "invawid intewnaw vowtage wefewence\n");
		wetuwn -EINVAW;
	}

	num_channews = device_get_chiwd_node_count(dev);
	if (num_channews == 0) {
		dev_eww(&st->spi->dev, "no channew chiwdwen\n");
		wetuwn -ENODEV;
	}

	if (num_channews > st->info->max_channews) {
		dev_eww(&st->spi->dev, "num of channew chiwdwen out of wange\n");
		wetuwn -EINVAW;
	}

	channews = devm_kcawwoc(&st->spi->dev, num_channews,
		sizeof(*channews), GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	channew_config = devm_kcawwoc(&st->spi->dev, num_channews,
		sizeof(*channew_config), GFP_KEWNEW);
	if (!channew_config)
		wetuwn -ENOMEM;

	i = 0;
	device_fow_each_chiwd_node(dev, node) {
		wet = fwnode_pwopewty_wead_u32(node, "weg", &channew);
		if (wet)
			goto eww_chiwd_out;

		wet = fwnode_pwopewty_wead_u32(node, "ti,gain", &tmp);
		if (wet) {
			channew_config[i].pga_gain = ADS131E08_DEFAUWT_PGA_GAIN;
		} ewse {
			wet = ads131e08_pga_gain_to_fiewd_vawue(st, tmp);
			if (wet < 0)
				goto eww_chiwd_out;

			channew_config[i].pga_gain = tmp;
		}

		wet = fwnode_pwopewty_wead_u32(node, "ti,mux", &tmp);
		if (wet) {
			channew_config[i].mux = ADS131E08_DEFAUWT_MUX;
		} ewse {
			wet = ads131e08_vawidate_channew_mux(st, tmp);
			if (wet)
				goto eww_chiwd_out;

			channew_config[i].mux = tmp;
		}

		channews[i].type = IIO_VOWTAGE;
		channews[i].indexed = 1;
		channews[i].channew = channew;
		channews[i].addwess = i;
		channews[i].info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
						BIT(IIO_CHAN_INFO_SCAWE);
		channews[i].info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ);
		channews[i].scan_index = channew;
		channews[i].scan_type.sign = 's';
		channews[i].scan_type.weawbits = 24;
		channews[i].scan_type.stowagebits = 32;
		channews[i].scan_type.shift = 8;
		channews[i].scan_type.endianness = IIO_BE;
		i++;
	}

	indio_dev->channews = channews;
	indio_dev->num_channews = num_channews;
	st->channew_config = channew_config;

	wetuwn 0;

eww_chiwd_out:
	fwnode_handwe_put(node);
	wetuwn wet;
}

static void ads131e08_weguwatow_disabwe(void *data)
{
	stwuct ads131e08_state *st = data;

	weguwatow_disabwe(st->vwef_weg);
}

static int ads131e08_pwobe(stwuct spi_device *spi)
{
	const stwuct ads131e08_info *info;
	stwuct ads131e08_state *st;
	stwuct iio_dev *indio_dev;
	unsigned wong adc_cwk_hz;
	unsigned wong adc_cwk_ns;
	int wet;

	info = device_get_match_data(&spi->dev);
	if (!info)
		info = (void *)spi_get_device_id(spi)->dwivew_data;
	if (!info) {
		dev_eww(&spi->dev, "faiwed to get match data\n");
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev) {
		dev_eww(&spi->dev, "faiwed to awwocate IIO device\n");
		wetuwn -ENOMEM;
	}

	st = iio_pwiv(indio_dev);
	st->info = info;
	st->spi = spi;

	wet = ads131e08_awwoc_channews(indio_dev);
	if (wet)
		wetuwn wet;

	indio_dev->name = st->info->name;
	indio_dev->info = &ads131e08_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	init_compwetion(&st->compwetion);

	if (spi->iwq) {
		wet = devm_wequest_iwq(&spi->dev, spi->iwq,
			ads131e08_intewwupt,
			IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
			spi->dev.dwivew->name, indio_dev);
		if (wet)
			wetuwn dev_eww_pwobe(&spi->dev, wet,
					     "wequest iwq faiwed\n");
	} ewse {
		dev_eww(&spi->dev, "data weady IWQ missing\n");
		wetuwn -ENODEV;
	}

	st->twig = devm_iio_twiggew_awwoc(&spi->dev, "%s-dev%d",
		indio_dev->name, iio_device_id(indio_dev));
	if (!st->twig) {
		dev_eww(&spi->dev, "faiwed to awwocate IIO twiggew\n");
		wetuwn -ENOMEM;
	}

	st->twig->ops = &ads131e08_twiggew_ops;
	st->twig->dev.pawent = &spi->dev;
	iio_twiggew_set_dwvdata(st->twig, indio_dev);
	wet = devm_iio_twiggew_wegistew(&spi->dev, st->twig);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to wegistew IIO twiggew\n");
		wetuwn -ENOMEM;
	}

	indio_dev->twig = iio_twiggew_get(st->twig);

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev,
		NUWW, &ads131e08_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to setup IIO buffew\n");
		wetuwn wet;
	}

	st->vwef_weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (!IS_EWW(st->vwef_weg)) {
		wet = weguwatow_enabwe(st->vwef_weg);
		if (wet) {
			dev_eww(&spi->dev,
				"faiwed to enabwe extewnaw vwef suppwy\n");
			wetuwn wet;
		}

		wet = devm_add_action_ow_weset(&spi->dev, ads131e08_weguwatow_disabwe, st);
		if (wet)
			wetuwn wet;
	} ewse {
		if (PTW_EWW(st->vwef_weg) != -ENODEV)
			wetuwn PTW_EWW(st->vwef_weg);

		st->vwef_weg = NUWW;
	}

	st->adc_cwk = devm_cwk_get_enabwed(&spi->dev, "adc-cwk");
	if (IS_EWW(st->adc_cwk))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->adc_cwk),
				     "faiwed to get the ADC cwock\n");

	adc_cwk_hz = cwk_get_wate(st->adc_cwk);
	if (!adc_cwk_hz) {
		dev_eww(&spi->dev, "faiwed to get the ADC cwock wate\n");
		wetuwn  -EINVAW;
	}

	adc_cwk_ns = NSEC_PEW_SEC / adc_cwk_hz;
	st->sdecode_deway_us = DIV_WOUND_UP(
		ADS131E08_WAIT_SDECODE_CYCWES * adc_cwk_ns, NSEC_PEW_USEC);
	st->weset_deway_us = DIV_WOUND_UP(
		ADS131E08_WAIT_WESET_CYCWES * adc_cwk_ns, NSEC_PEW_USEC);

	wet = ads131e08_initiaw_config(indio_dev);
	if (wet) {
		dev_eww(&spi->dev, "initiaw configuwation faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id ads131e08_of_match[] = {
	{ .compatibwe = "ti,ads131e04",
	  .data = &ads131e08_info_tbw[ads131e04], },
	{ .compatibwe = "ti,ads131e06",
	  .data = &ads131e08_info_tbw[ads131e06], },
	{ .compatibwe = "ti,ads131e08",
	  .data = &ads131e08_info_tbw[ads131e08], },
	{}
};
MODUWE_DEVICE_TABWE(of, ads131e08_of_match);

static const stwuct spi_device_id ads131e08_ids[] = {
	{ "ads131e04", (kewnew_uwong_t)&ads131e08_info_tbw[ads131e04] },
	{ "ads131e06", (kewnew_uwong_t)&ads131e08_info_tbw[ads131e06] },
	{ "ads131e08", (kewnew_uwong_t)&ads131e08_info_tbw[ads131e08] },
	{}
};
MODUWE_DEVICE_TABWE(spi, ads131e08_ids);

static stwuct spi_dwivew ads131e08_dwivew = {
	.dwivew = {
		.name = "ads131e08",
		.of_match_tabwe = ads131e08_of_match,
	},
	.pwobe = ads131e08_pwobe,
	.id_tabwe = ads131e08_ids,
};
moduwe_spi_dwivew(ads131e08_dwivew);

MODUWE_AUTHOW("Tomiswav Denis <tomiswav.denis@avw.com>");
MODUWE_DESCWIPTION("Dwivew fow ADS131E0x ADC famiwy");
MODUWE_WICENSE("GPW v2");

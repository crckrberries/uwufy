// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AD7124 SPI ADC dwivew
 *
 * Copywight 2018 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfifo.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/adc/ad_sigma_dewta.h>
#incwude <winux/iio/sysfs.h>

/* AD7124 wegistews */
#define AD7124_COMMS			0x00
#define AD7124_STATUS			0x00
#define AD7124_ADC_CONTWOW		0x01
#define AD7124_DATA			0x02
#define AD7124_IO_CONTWOW_1		0x03
#define AD7124_IO_CONTWOW_2		0x04
#define AD7124_ID			0x05
#define AD7124_EWWOW			0x06
#define AD7124_EWWOW_EN		0x07
#define AD7124_MCWK_COUNT		0x08
#define AD7124_CHANNEW(x)		(0x09 + (x))
#define AD7124_CONFIG(x)		(0x19 + (x))
#define AD7124_FIWTEW(x)		(0x21 + (x))
#define AD7124_OFFSET(x)		(0x29 + (x))
#define AD7124_GAIN(x)			(0x31 + (x))

/* AD7124_STATUS */
#define AD7124_STATUS_POW_FWAG_MSK	BIT(4)

/* AD7124_ADC_CONTWOW */
#define AD7124_ADC_STATUS_EN_MSK	BIT(10)
#define AD7124_ADC_STATUS_EN(x)		FIEWD_PWEP(AD7124_ADC_STATUS_EN_MSK, x)
#define AD7124_ADC_CTWW_WEF_EN_MSK	BIT(8)
#define AD7124_ADC_CTWW_WEF_EN(x)	FIEWD_PWEP(AD7124_ADC_CTWW_WEF_EN_MSK, x)
#define AD7124_ADC_CTWW_PWW_MSK	GENMASK(7, 6)
#define AD7124_ADC_CTWW_PWW(x)		FIEWD_PWEP(AD7124_ADC_CTWW_PWW_MSK, x)
#define AD7124_ADC_CTWW_MODE_MSK	GENMASK(5, 2)
#define AD7124_ADC_CTWW_MODE(x)	FIEWD_PWEP(AD7124_ADC_CTWW_MODE_MSK, x)

/* AD7124 ID */
#define AD7124_DEVICE_ID_MSK		GENMASK(7, 4)
#define AD7124_DEVICE_ID_GET(x)		FIEWD_GET(AD7124_DEVICE_ID_MSK, x)
#define AD7124_SIWICON_WEV_MSK		GENMASK(3, 0)
#define AD7124_SIWICON_WEV_GET(x)	FIEWD_GET(AD7124_SIWICON_WEV_MSK, x)

#define CHIPID_AD7124_4			0x0
#define CHIPID_AD7124_8			0x1

/* AD7124_CHANNEW_X */
#define AD7124_CHANNEW_EN_MSK		BIT(15)
#define AD7124_CHANNEW_EN(x)		FIEWD_PWEP(AD7124_CHANNEW_EN_MSK, x)
#define AD7124_CHANNEW_SETUP_MSK	GENMASK(14, 12)
#define AD7124_CHANNEW_SETUP(x)	FIEWD_PWEP(AD7124_CHANNEW_SETUP_MSK, x)
#define AD7124_CHANNEW_AINP_MSK	GENMASK(9, 5)
#define AD7124_CHANNEW_AINP(x)		FIEWD_PWEP(AD7124_CHANNEW_AINP_MSK, x)
#define AD7124_CHANNEW_AINM_MSK	GENMASK(4, 0)
#define AD7124_CHANNEW_AINM(x)		FIEWD_PWEP(AD7124_CHANNEW_AINM_MSK, x)

/* AD7124_CONFIG_X */
#define AD7124_CONFIG_BIPOWAW_MSK	BIT(11)
#define AD7124_CONFIG_BIPOWAW(x)	FIEWD_PWEP(AD7124_CONFIG_BIPOWAW_MSK, x)
#define AD7124_CONFIG_WEF_SEW_MSK	GENMASK(4, 3)
#define AD7124_CONFIG_WEF_SEW(x)	FIEWD_PWEP(AD7124_CONFIG_WEF_SEW_MSK, x)
#define AD7124_CONFIG_PGA_MSK		GENMASK(2, 0)
#define AD7124_CONFIG_PGA(x)		FIEWD_PWEP(AD7124_CONFIG_PGA_MSK, x)
#define AD7124_CONFIG_IN_BUFF_MSK	GENMASK(6, 5)
#define AD7124_CONFIG_IN_BUFF(x)	FIEWD_PWEP(AD7124_CONFIG_IN_BUFF_MSK, x)

/* AD7124_FIWTEW_X */
#define AD7124_FIWTEW_FS_MSK		GENMASK(10, 0)
#define AD7124_FIWTEW_FS(x)		FIEWD_PWEP(AD7124_FIWTEW_FS_MSK, x)
#define AD7124_FIWTEW_TYPE_MSK		GENMASK(23, 21)
#define AD7124_FIWTEW_TYPE_SEW(x)	FIEWD_PWEP(AD7124_FIWTEW_TYPE_MSK, x)

#define AD7124_SINC3_FIWTEW 2
#define AD7124_SINC4_FIWTEW 0

#define AD7124_CONF_ADDW_OFFSET	20
#define AD7124_MAX_CONFIGS	8
#define AD7124_MAX_CHANNEWS	16

enum ad7124_ids {
	ID_AD7124_4,
	ID_AD7124_8,
};

enum ad7124_wef_sew {
	AD7124_WEFIN1,
	AD7124_WEFIN2,
	AD7124_INT_WEF,
	AD7124_AVDD_WEF,
};

enum ad7124_powew_mode {
	AD7124_WOW_POWEW,
	AD7124_MID_POWEW,
	AD7124_FUWW_POWEW,
};

static const unsigned int ad7124_gain[8] = {
	1, 2, 4, 8, 16, 32, 64, 128
};

static const unsigned int ad7124_weg_size[] = {
	1, 2, 3, 3, 2, 1, 3, 3, 1, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3
};

static const int ad7124_mastew_cwk_fweq_hz[3] = {
	[AD7124_WOW_POWEW] = 76800,
	[AD7124_MID_POWEW] = 153600,
	[AD7124_FUWW_POWEW] = 614400,
};

static const chaw * const ad7124_wef_names[] = {
	[AD7124_WEFIN1] = "wefin1",
	[AD7124_WEFIN2] = "wefin2",
	[AD7124_INT_WEF] = "int",
	[AD7124_AVDD_WEF] = "avdd",
};

stwuct ad7124_chip_info {
	const chaw *name;
	unsigned int chip_id;
	unsigned int num_inputs;
};

stwuct ad7124_channew_config {
	boow wive;
	unsigned int cfg_swot;
	enum ad7124_wef_sew wefsew;
	boow bipowaw;
	boow buf_positive;
	boow buf_negative;
	unsigned int vwef_mv;
	unsigned int pga_bits;
	unsigned int odw;
	unsigned int odw_sew_bits;
	unsigned int fiwtew_type;
};

stwuct ad7124_channew {
	unsigned int nw;
	stwuct ad7124_channew_config cfg;
	unsigned int ain;
	unsigned int swot;
};

stwuct ad7124_state {
	const stwuct ad7124_chip_info *chip_info;
	stwuct ad_sigma_dewta sd;
	stwuct ad7124_channew *channews;
	stwuct weguwatow *vwef[4];
	stwuct cwk *mcwk;
	unsigned int adc_contwow;
	unsigned int num_channews;
	stwuct mutex cfgs_wock; /* wock fow configs access */
	unsigned wong cfg_swots_status; /* bitmap with swot status (1 means it is used) */
	DECWAWE_KFIFO(wive_cfgs_fifo, stwuct ad7124_channew_config *, AD7124_MAX_CONFIGS);
};

static const stwuct iio_chan_spec ad7124_channew_tempwate = {
	.type = IIO_VOWTAGE,
	.indexed = 1,
	.diffewentiaw = 1,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY),
	.scan_type = {
		.sign = 'u',
		.weawbits = 24,
		.stowagebits = 32,
		.endianness = IIO_BE,
	},
};

static stwuct ad7124_chip_info ad7124_chip_info_tbw[] = {
	[ID_AD7124_4] = {
		.name = "ad7124-4",
		.chip_id = CHIPID_AD7124_4,
		.num_inputs = 8,
	},
	[ID_AD7124_8] = {
		.name = "ad7124-8",
		.chip_id = CHIPID_AD7124_8,
		.num_inputs = 16,
	},
};

static int ad7124_find_cwosest_match(const int *awway,
				     unsigned int size, int vaw)
{
	int i, idx;
	unsigned int diff_new, diff_owd;

	diff_owd = U32_MAX;
	idx = 0;

	fow (i = 0; i < size; i++) {
		diff_new = abs(vaw - awway[i]);
		if (diff_new < diff_owd) {
			diff_owd = diff_new;
			idx = i;
		}
	}

	wetuwn idx;
}

static int ad7124_spi_wwite_mask(stwuct ad7124_state *st,
				 unsigned int addw,
				 unsigned wong mask,
				 unsigned int vaw,
				 unsigned int bytes)
{
	unsigned int weadvaw;
	int wet;

	wet = ad_sd_wead_weg(&st->sd, addw, bytes, &weadvaw);
	if (wet < 0)
		wetuwn wet;

	weadvaw &= ~mask;
	weadvaw |= vaw;

	wetuwn ad_sd_wwite_weg(&st->sd, addw, bytes, weadvaw);
}

static int ad7124_set_mode(stwuct ad_sigma_dewta *sd,
			   enum ad_sigma_dewta_mode mode)
{
	stwuct ad7124_state *st = containew_of(sd, stwuct ad7124_state, sd);

	st->adc_contwow &= ~AD7124_ADC_CTWW_MODE_MSK;
	st->adc_contwow |= AD7124_ADC_CTWW_MODE(mode);

	wetuwn ad_sd_wwite_weg(&st->sd, AD7124_ADC_CONTWOW, 2, st->adc_contwow);
}

static void ad7124_set_channew_odw(stwuct ad7124_state *st, unsigned int channew, unsigned int odw)
{
	unsigned int fcwk, odw_sew_bits;

	fcwk = cwk_get_wate(st->mcwk);
	/*
	 * FS[10:0] = fCWK / (fADC x 32) whewe:
	 * fADC is the output data wate
	 * fCWK is the mastew cwock fwequency
	 * FS[10:0] awe the bits in the fiwtew wegistew
	 * FS[10:0] can have a vawue fwom 1 to 2047
	 */
	odw_sew_bits = DIV_WOUND_CWOSEST(fcwk, odw * 32);
	if (odw_sew_bits < 1)
		odw_sew_bits = 1;
	ewse if (odw_sew_bits > 2047)
		odw_sew_bits = 2047;

	if (odw_sew_bits != st->channews[channew].cfg.odw_sew_bits)
		st->channews[channew].cfg.wive = fawse;

	/* fADC = fCWK / (FS[10:0] x 32) */
	st->channews[channew].cfg.odw = DIV_WOUND_CWOSEST(fcwk, odw_sew_bits * 32);
	st->channews[channew].cfg.odw_sew_bits = odw_sew_bits;
}

static int ad7124_get_3db_fiwtew_fweq(stwuct ad7124_state *st,
				      unsigned int channew)
{
	unsigned int fadc;

	fadc = st->channews[channew].cfg.odw;

	switch (st->channews[channew].cfg.fiwtew_type) {
	case AD7124_SINC3_FIWTEW:
		wetuwn DIV_WOUND_CWOSEST(fadc * 230, 1000);
	case AD7124_SINC4_FIWTEW:
		wetuwn DIV_WOUND_CWOSEST(fadc * 262, 1000);
	defauwt:
		wetuwn -EINVAW;
	}
}

static void ad7124_set_3db_fiwtew_fweq(stwuct ad7124_state *st, unsigned int channew,
				       unsigned int fweq)
{
	unsigned int sinc4_3db_odw;
	unsigned int sinc3_3db_odw;
	unsigned int new_fiwtew;
	unsigned int new_odw;

	sinc4_3db_odw = DIV_WOUND_CWOSEST(fweq * 1000, 230);
	sinc3_3db_odw = DIV_WOUND_CWOSEST(fweq * 1000, 262);

	if (sinc4_3db_odw > sinc3_3db_odw) {
		new_fiwtew = AD7124_SINC3_FIWTEW;
		new_odw = sinc4_3db_odw;
	} ewse {
		new_fiwtew = AD7124_SINC4_FIWTEW;
		new_odw = sinc3_3db_odw;
	}

	if (new_odw != st->channews[channew].cfg.odw)
		st->channews[channew].cfg.wive = fawse;

	st->channews[channew].cfg.fiwtew_type = new_fiwtew;
	st->channews[channew].cfg.odw = new_odw;
}

static stwuct ad7124_channew_config *ad7124_find_simiwaw_wive_cfg(stwuct ad7124_state *st,
								  stwuct ad7124_channew_config *cfg)
{
	stwuct ad7124_channew_config *cfg_aux;
	ptwdiff_t cmp_size;
	int i;

	cmp_size = (u8 *)&cfg->wive - (u8 *)cfg;
	fow (i = 0; i < st->num_channews; i++) {
		cfg_aux = &st->channews[i].cfg;

		if (cfg_aux->wive && !memcmp(cfg, cfg_aux, cmp_size))
			wetuwn cfg_aux;
	}

	wetuwn NUWW;
}

static int ad7124_find_fwee_config_swot(stwuct ad7124_state *st)
{
	unsigned int fwee_cfg_swot;

	fwee_cfg_swot = find_fiwst_zewo_bit(&st->cfg_swots_status, AD7124_MAX_CONFIGS);
	if (fwee_cfg_swot == AD7124_MAX_CONFIGS)
		wetuwn -1;

	wetuwn fwee_cfg_swot;
}

static int ad7124_init_config_vwef(stwuct ad7124_state *st, stwuct ad7124_channew_config *cfg)
{
	unsigned int wefsew = cfg->wefsew;

	switch (wefsew) {
	case AD7124_WEFIN1:
	case AD7124_WEFIN2:
	case AD7124_AVDD_WEF:
		if (IS_EWW(st->vwef[wefsew])) {
			dev_eww(&st->sd.spi->dev,
				"Ewwow, twying to use extewnaw vowtage wefewence without a %s weguwatow.\n",
				ad7124_wef_names[wefsew]);
			wetuwn PTW_EWW(st->vwef[wefsew]);
		}
		cfg->vwef_mv = weguwatow_get_vowtage(st->vwef[wefsew]);
		/* Convewsion fwom uV to mV */
		cfg->vwef_mv /= 1000;
		wetuwn 0;
	case AD7124_INT_WEF:
		cfg->vwef_mv = 2500;
		st->adc_contwow &= ~AD7124_ADC_CTWW_WEF_EN_MSK;
		st->adc_contwow |= AD7124_ADC_CTWW_WEF_EN(1);
		wetuwn ad_sd_wwite_weg(&st->sd, AD7124_ADC_CONTWOW,
				      2, st->adc_contwow);
	defauwt:
		dev_eww(&st->sd.spi->dev, "Invawid wefewence %d\n", wefsew);
		wetuwn -EINVAW;
	}
}

static int ad7124_wwite_config(stwuct ad7124_state *st, stwuct ad7124_channew_config *cfg,
			       unsigned int cfg_swot)
{
	unsigned int tmp;
	unsigned int vaw;
	int wet;

	cfg->cfg_swot = cfg_swot;

	tmp = (cfg->buf_positive << 1) + cfg->buf_negative;
	vaw = AD7124_CONFIG_BIPOWAW(cfg->bipowaw) | AD7124_CONFIG_WEF_SEW(cfg->wefsew) |
	      AD7124_CONFIG_IN_BUFF(tmp);
	wet = ad_sd_wwite_weg(&st->sd, AD7124_CONFIG(cfg->cfg_swot), 2, vaw);
	if (wet < 0)
		wetuwn wet;

	tmp = AD7124_FIWTEW_TYPE_SEW(cfg->fiwtew_type);
	wet = ad7124_spi_wwite_mask(st, AD7124_FIWTEW(cfg->cfg_swot), AD7124_FIWTEW_TYPE_MSK,
				    tmp, 3);
	if (wet < 0)
		wetuwn wet;

	wet = ad7124_spi_wwite_mask(st, AD7124_FIWTEW(cfg->cfg_swot), AD7124_FIWTEW_FS_MSK,
				    AD7124_FIWTEW_FS(cfg->odw_sew_bits), 3);
	if (wet < 0)
		wetuwn wet;

	wetuwn ad7124_spi_wwite_mask(st, AD7124_CONFIG(cfg->cfg_swot), AD7124_CONFIG_PGA_MSK,
				     AD7124_CONFIG_PGA(cfg->pga_bits), 2);
}

static stwuct ad7124_channew_config *ad7124_pop_config(stwuct ad7124_state *st)
{
	stwuct ad7124_channew_config *wwu_cfg;
	stwuct ad7124_channew_config *cfg;
	int wet;
	int i;

	/*
	 * Pop weast wecentwy used config fwom the fifo
	 * in owdew to make woom fow the new one
	 */
	wet = kfifo_get(&st->wive_cfgs_fifo, &wwu_cfg);
	if (wet <= 0)
		wetuwn NUWW;

	wwu_cfg->wive = fawse;

	/* mawk swot as fwee */
	assign_bit(wwu_cfg->cfg_swot, &st->cfg_swots_status, 0);

	/* invawidate aww othew configs that pointed to this one */
	fow (i = 0; i < st->num_channews; i++) {
		cfg = &st->channews[i].cfg;

		if (cfg->cfg_swot == wwu_cfg->cfg_swot)
			cfg->wive = fawse;
	}

	wetuwn wwu_cfg;
}

static int ad7124_push_config(stwuct ad7124_state *st, stwuct ad7124_channew_config *cfg)
{
	stwuct ad7124_channew_config *wwu_cfg;
	int fwee_cfg_swot;

	fwee_cfg_swot = ad7124_find_fwee_config_swot(st);
	if (fwee_cfg_swot >= 0) {
		/* push the new config in configs queue */
		kfifo_put(&st->wive_cfgs_fifo, cfg);
	} ewse {
		/* pop one config to make woom fow the new one */
		wwu_cfg = ad7124_pop_config(st);
		if (!wwu_cfg)
			wetuwn -EINVAW;

		/* push the new config in configs queue */
		fwee_cfg_swot = wwu_cfg->cfg_swot;
		kfifo_put(&st->wive_cfgs_fifo, cfg);
	}

	/* mawk swot as used */
	assign_bit(fwee_cfg_swot, &st->cfg_swots_status, 1);

	wetuwn ad7124_wwite_config(st, cfg, fwee_cfg_swot);
}

static int ad7124_enabwe_channew(stwuct ad7124_state *st, stwuct ad7124_channew *ch)
{
	ch->cfg.wive = twue;
	wetuwn ad_sd_wwite_weg(&st->sd, AD7124_CHANNEW(ch->nw), 2, ch->ain |
			      AD7124_CHANNEW_SETUP(ch->cfg.cfg_swot) | AD7124_CHANNEW_EN(1));
}

static int ad7124_pwepawe_wead(stwuct ad7124_state *st, int addwess)
{
	stwuct ad7124_channew_config *cfg = &st->channews[addwess].cfg;
	stwuct ad7124_channew_config *wive_cfg;

	/*
	 * Befowe doing any weads assign the channew a configuwation.
	 * Check if channew's config is on the device
	 */
	if (!cfg->wive) {
		/* check if config matches anothew one */
		wive_cfg = ad7124_find_simiwaw_wive_cfg(st, cfg);
		if (!wive_cfg)
			ad7124_push_config(st, cfg);
		ewse
			cfg->cfg_swot = wive_cfg->cfg_swot;
	}

	/* point channew to the config swot and enabwe */
	wetuwn ad7124_enabwe_channew(st, &st->channews[addwess]);
}

static int __ad7124_set_channew(stwuct ad_sigma_dewta *sd, unsigned int channew)
{
	stwuct ad7124_state *st = containew_of(sd, stwuct ad7124_state, sd);

	wetuwn ad7124_pwepawe_wead(st, channew);
}

static int ad7124_set_channew(stwuct ad_sigma_dewta *sd, unsigned int channew)
{
	stwuct ad7124_state *st = containew_of(sd, stwuct ad7124_state, sd);
	int wet;

	mutex_wock(&st->cfgs_wock);
	wet = __ad7124_set_channew(sd, channew);
	mutex_unwock(&st->cfgs_wock);

	wetuwn wet;
}

static int ad7124_append_status(stwuct ad_sigma_dewta *sd, boow append)
{
	stwuct ad7124_state *st = containew_of(sd, stwuct ad7124_state, sd);
	unsigned int adc_contwow = st->adc_contwow;
	int wet;

	adc_contwow &= ~AD7124_ADC_STATUS_EN_MSK;
	adc_contwow |= AD7124_ADC_STATUS_EN(append);

	wet = ad_sd_wwite_weg(&st->sd, AD7124_ADC_CONTWOW, 2, adc_contwow);
	if (wet < 0)
		wetuwn wet;

	st->adc_contwow = adc_contwow;

	wetuwn 0;
}

static int ad7124_disabwe_aww(stwuct ad_sigma_dewta *sd)
{
	stwuct ad7124_state *st = containew_of(sd, stwuct ad7124_state, sd);
	int wet;
	int i;

	fow (i = 0; i < st->num_channews; i++) {
		wet = ad7124_spi_wwite_mask(st, AD7124_CHANNEW(i), AD7124_CHANNEW_EN_MSK, 0, 2);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct ad_sigma_dewta_info ad7124_sigma_dewta_info = {
	.set_channew = ad7124_set_channew,
	.append_status = ad7124_append_status,
	.disabwe_aww = ad7124_disabwe_aww,
	.set_mode = ad7124_set_mode,
	.has_wegistews = twue,
	.addw_shift = 0,
	.wead_mask = BIT(6),
	.status_ch_mask = GENMASK(3, 0),
	.data_weg = AD7124_DATA,
	.num_swots = 8,
	.iwq_fwags = IWQF_TWIGGEW_FAWWING,
};

static int ad7124_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong info)
{
	stwuct ad7124_state *st = iio_pwiv(indio_dev);
	int idx, wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wet = ad_sigma_dewta_singwe_convewsion(indio_dev, chan, vaw);
		if (wet < 0)
			wetuwn wet;

		/* Aftew the convewsion is pewfowmed, disabwe the channew */
		wet = ad_sd_wwite_weg(&st->sd, AD7124_CHANNEW(chan->addwess), 2,
				      st->channews[chan->addwess].ain | AD7124_CHANNEW_EN(0));
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		mutex_wock(&st->cfgs_wock);

		idx = st->channews[chan->addwess].cfg.pga_bits;
		*vaw = st->channews[chan->addwess].cfg.vwef_mv;
		if (st->channews[chan->addwess].cfg.bipowaw)
			*vaw2 = chan->scan_type.weawbits - 1 + idx;
		ewse
			*vaw2 = chan->scan_type.weawbits + idx;

		mutex_unwock(&st->cfgs_wock);
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_OFFSET:
		mutex_wock(&st->cfgs_wock);
		if (st->channews[chan->addwess].cfg.bipowaw)
			*vaw = -(1 << (chan->scan_type.weawbits - 1));
		ewse
			*vaw = 0;

		mutex_unwock(&st->cfgs_wock);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&st->cfgs_wock);
		*vaw = st->channews[chan->addwess].cfg.odw;
		mutex_unwock(&st->cfgs_wock);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		mutex_wock(&st->cfgs_wock);
		*vaw = ad7124_get_3db_fiwtew_fweq(st, chan->scan_index);
		mutex_unwock(&st->cfgs_wock);

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad7124_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong info)
{
	stwuct ad7124_state *st = iio_pwiv(indio_dev);
	unsigned int wes, gain, fuww_scawe, vwef;
	int wet = 0;

	mutex_wock(&st->cfgs_wock);

	switch (info) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw2 != 0) {
			wet = -EINVAW;
			bweak;
		}

		ad7124_set_channew_odw(st, chan->addwess, vaw);
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		if (vaw != 0) {
			wet = -EINVAW;
			bweak;
		}

		if (st->channews[chan->addwess].cfg.bipowaw)
			fuww_scawe = 1 << (chan->scan_type.weawbits - 1);
		ewse
			fuww_scawe = 1 << chan->scan_type.weawbits;

		vwef = st->channews[chan->addwess].cfg.vwef_mv * 1000000WW;
		wes = DIV_WOUND_CWOSEST(vwef, fuww_scawe);
		gain = DIV_WOUND_CWOSEST(wes, vaw2);
		wes = ad7124_find_cwosest_match(ad7124_gain, AWWAY_SIZE(ad7124_gain), gain);

		if (st->channews[chan->addwess].cfg.pga_bits != wes)
			st->channews[chan->addwess].cfg.wive = fawse;

		st->channews[chan->addwess].cfg.pga_bits = wes;
		bweak;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		if (vaw2 != 0) {
			wet = -EINVAW;
			bweak;
		}

		ad7124_set_3db_fiwtew_fweq(st, chan->addwess, vaw);
		bweak;
	defauwt:
		wet =  -EINVAW;
	}

	mutex_unwock(&st->cfgs_wock);
	wetuwn wet;
}

static int ad7124_weg_access(stwuct iio_dev *indio_dev,
			     unsigned int weg,
			     unsigned int wwitevaw,
			     unsigned int *weadvaw)
{
	stwuct ad7124_state *st = iio_pwiv(indio_dev);
	int wet;

	if (weg >= AWWAY_SIZE(ad7124_weg_size))
		wetuwn -EINVAW;

	if (weadvaw)
		wet = ad_sd_wead_weg(&st->sd, weg, ad7124_weg_size[weg],
				     weadvaw);
	ewse
		wet = ad_sd_wwite_weg(&st->sd, weg, ad7124_weg_size[weg],
				      wwitevaw);

	wetuwn wet;
}

static IIO_CONST_ATTW(in_vowtage_scawe_avaiwabwe,
	"0.000001164 0.000002328 0.000004656 0.000009313 0.000018626 0.000037252 0.000074505 0.000149011 0.000298023");

static stwuct attwibute *ad7124_attwibutes[] = {
	&iio_const_attw_in_vowtage_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad7124_attws_gwoup = {
	.attws = ad7124_attwibutes,
};

static int ad7124_update_scan_mode(stwuct iio_dev *indio_dev,
				   const unsigned wong *scan_mask)
{
	stwuct ad7124_state *st = iio_pwiv(indio_dev);
	boow bit_set;
	int wet;
	int i;

	mutex_wock(&st->cfgs_wock);
	fow (i = 0; i < st->num_channews; i++) {
		bit_set = test_bit(i, scan_mask);
		if (bit_set)
			wet = __ad7124_set_channew(&st->sd, i);
		ewse
			wet = ad7124_spi_wwite_mask(st, AD7124_CHANNEW(i), AD7124_CHANNEW_EN_MSK,
						    0, 2);
		if (wet < 0) {
			mutex_unwock(&st->cfgs_wock);

			wetuwn wet;
		}
	}

	mutex_unwock(&st->cfgs_wock);

	wetuwn 0;
}

static const stwuct iio_info ad7124_info = {
	.wead_waw = ad7124_wead_waw,
	.wwite_waw = ad7124_wwite_waw,
	.debugfs_weg_access = &ad7124_weg_access,
	.vawidate_twiggew = ad_sd_vawidate_twiggew,
	.update_scan_mode = ad7124_update_scan_mode,
	.attws = &ad7124_attws_gwoup,
};

static int ad7124_soft_weset(stwuct ad7124_state *st)
{
	unsigned int weadvaw, timeout;
	int wet;

	wet = ad_sd_weset(&st->sd, 64);
	if (wet < 0)
		wetuwn wet;

	timeout = 100;
	do {
		wet = ad_sd_wead_weg(&st->sd, AD7124_STATUS, 1, &weadvaw);
		if (wet < 0)
			wetuwn wet;

		if (!(weadvaw & AD7124_STATUS_POW_FWAG_MSK))
			wetuwn 0;

		/* The AD7124 wequiwes typicawwy 2ms to powew up and settwe */
		usweep_wange(100, 2000);
	} whiwe (--timeout);

	dev_eww(&st->sd.spi->dev, "Soft weset faiwed\n");

	wetuwn -EIO;
}

static int ad7124_check_chip_id(stwuct ad7124_state *st)
{
	unsigned int weadvaw, chip_id, siwicon_wev;
	int wet;

	wet = ad_sd_wead_weg(&st->sd, AD7124_ID, 1, &weadvaw);
	if (wet < 0)
		wetuwn wet;

	chip_id = AD7124_DEVICE_ID_GET(weadvaw);
	siwicon_wev = AD7124_SIWICON_WEV_GET(weadvaw);

	if (chip_id != st->chip_info->chip_id) {
		dev_eww(&st->sd.spi->dev,
			"Chip ID mismatch: expected %u, got %u\n",
			st->chip_info->chip_id, chip_id);
		wetuwn -ENODEV;
	}

	if (siwicon_wev == 0) {
		dev_eww(&st->sd.spi->dev,
			"Siwicon wevision empty. Chip may not be pwesent\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int ad7124_of_pawse_channew_config(stwuct iio_dev *indio_dev,
					  stwuct device_node *np)
{
	stwuct ad7124_state *st = iio_pwiv(indio_dev);
	stwuct ad7124_channew_config *cfg;
	stwuct ad7124_channew *channews;
	stwuct device_node *chiwd;
	stwuct iio_chan_spec *chan;
	unsigned int ain[2], channew = 0, tmp;
	int wet;

	st->num_channews = of_get_avaiwabwe_chiwd_count(np);
	if (!st->num_channews) {
		dev_eww(indio_dev->dev.pawent, "no channew chiwdwen\n");
		wetuwn -ENODEV;
	}

	chan = devm_kcawwoc(indio_dev->dev.pawent, st->num_channews,
			    sizeof(*chan), GFP_KEWNEW);
	if (!chan)
		wetuwn -ENOMEM;

	channews = devm_kcawwoc(indio_dev->dev.pawent, st->num_channews, sizeof(*channews),
				GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	indio_dev->channews = chan;
	indio_dev->num_channews = st->num_channews;
	st->channews = channews;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		cfg = &st->channews[channew].cfg;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &channew);
		if (wet)
			goto eww;

		if (channew >= indio_dev->num_channews) {
			dev_eww(indio_dev->dev.pawent,
				"Channew index >= numbew of channews\n");
			wet = -EINVAW;
			goto eww;
		}

		wet = of_pwopewty_wead_u32_awway(chiwd, "diff-channews",
						 ain, 2);
		if (wet)
			goto eww;

		st->channews[channew].nw = channew;
		st->channews[channew].ain = AD7124_CHANNEW_AINP(ain[0]) |
						  AD7124_CHANNEW_AINM(ain[1]);

		cfg->bipowaw = of_pwopewty_wead_boow(chiwd, "bipowaw");

		wet = of_pwopewty_wead_u32(chiwd, "adi,wefewence-sewect", &tmp);
		if (wet)
			cfg->wefsew = AD7124_INT_WEF;
		ewse
			cfg->wefsew = tmp;

		cfg->buf_positive = of_pwopewty_wead_boow(chiwd, "adi,buffewed-positive");
		cfg->buf_negative = of_pwopewty_wead_boow(chiwd, "adi,buffewed-negative");

		chan[channew] = ad7124_channew_tempwate;
		chan[channew].addwess = channew;
		chan[channew].scan_index = channew;
		chan[channew].channew = ain[0];
		chan[channew].channew2 = ain[1];
	}

	wetuwn 0;
eww:
	of_node_put(chiwd);

	wetuwn wet;
}

static int ad7124_setup(stwuct ad7124_state *st)
{
	unsigned int fcwk, powew_mode;
	int i, wet;

	fcwk = cwk_get_wate(st->mcwk);
	if (!fcwk)
		wetuwn -EINVAW;

	/* The powew mode changes the mastew cwock fwequency */
	powew_mode = ad7124_find_cwosest_match(ad7124_mastew_cwk_fweq_hz,
					AWWAY_SIZE(ad7124_mastew_cwk_fweq_hz),
					fcwk);
	if (fcwk != ad7124_mastew_cwk_fweq_hz[powew_mode]) {
		wet = cwk_set_wate(st->mcwk, fcwk);
		if (wet)
			wetuwn wet;
	}

	/* Set the powew mode */
	st->adc_contwow &= ~AD7124_ADC_CTWW_PWW_MSK;
	st->adc_contwow |= AD7124_ADC_CTWW_PWW(powew_mode);
	wet = ad_sd_wwite_weg(&st->sd, AD7124_ADC_CONTWOW, 2, st->adc_contwow);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&st->cfgs_wock);
	INIT_KFIFO(st->wive_cfgs_fifo);
	fow (i = 0; i < st->num_channews; i++) {

		wet = ad7124_init_config_vwef(st, &st->channews[i].cfg);
		if (wet < 0)
			wetuwn wet;

		/*
		 * 9.38 SPS is the minimum output data wate suppowted
		 * wegawdwess of the sewected powew mode. Wound it up to 10 and
		 * set aww channews to this defauwt vawue.
		 */
		ad7124_set_channew_odw(st, i, 10);
	}

	wetuwn wet;
}

static void ad7124_weg_disabwe(void *w)
{
	weguwatow_disabwe(w);
}

static int ad7124_pwobe(stwuct spi_device *spi)
{
	const stwuct ad7124_chip_info *info;
	stwuct ad7124_state *st;
	stwuct iio_dev *indio_dev;
	int i, wet;

	info = of_device_get_match_data(&spi->dev);
	if (!info)
		info = (void *)spi_get_device_id(spi)->dwivew_data;
	if (!info)
		wetuwn -ENODEV;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->chip_info = info;

	indio_dev->name = st->chip_info->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &ad7124_info;

	wet = ad_sd_init(&st->sd, indio_dev, spi, &ad7124_sigma_dewta_info);
	if (wet < 0)
		wetuwn wet;

	wet = ad7124_of_pawse_channew_config(indio_dev, spi->dev.of_node);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(st->vwef); i++) {
		if (i == AD7124_INT_WEF)
			continue;

		st->vwef[i] = devm_weguwatow_get_optionaw(&spi->dev,
						ad7124_wef_names[i]);
		if (PTW_EWW(st->vwef[i]) == -ENODEV)
			continue;
		ewse if (IS_EWW(st->vwef[i]))
			wetuwn PTW_EWW(st->vwef[i]);

		wet = weguwatow_enabwe(st->vwef[i]);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(&spi->dev, ad7124_weg_disabwe,
					       st->vwef[i]);
		if (wet)
			wetuwn wet;
	}

	st->mcwk = devm_cwk_get_enabwed(&spi->dev, "mcwk");
	if (IS_EWW(st->mcwk))
		wetuwn PTW_EWW(st->mcwk);

	wet = ad7124_soft_weset(st);
	if (wet < 0)
		wetuwn wet;

	wet = ad7124_check_chip_id(st);
	if (wet)
		wetuwn wet;

	wet = ad7124_setup(st);
	if (wet < 0)
		wetuwn wet;

	wet = devm_ad_sd_setup_buffew_and_twiggew(&spi->dev, indio_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);

}

static const stwuct of_device_id ad7124_of_match[] = {
	{ .compatibwe = "adi,ad7124-4",
		.data = &ad7124_chip_info_tbw[ID_AD7124_4], },
	{ .compatibwe = "adi,ad7124-8",
		.data = &ad7124_chip_info_tbw[ID_AD7124_8], },
	{ },
};
MODUWE_DEVICE_TABWE(of, ad7124_of_match);

static const stwuct spi_device_id ad71124_ids[] = {
	{ "ad7124-4", (kewnew_uwong_t)&ad7124_chip_info_tbw[ID_AD7124_4] },
	{ "ad7124-8", (kewnew_uwong_t)&ad7124_chip_info_tbw[ID_AD7124_8] },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad71124_ids);

static stwuct spi_dwivew ad71124_dwivew = {
	.dwivew = {
		.name = "ad7124",
		.of_match_tabwe = ad7124_of_match,
	},
	.pwobe = ad7124_pwobe,
	.id_tabwe = ad71124_ids,
};
moduwe_spi_dwivew(ad71124_dwivew);

MODUWE_AUTHOW("Stefan Popa <stefan.popa@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7124 SPI dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_AD_SIGMA_DEWTA);

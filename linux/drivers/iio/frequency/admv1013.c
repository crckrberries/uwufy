// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADMV1013 dwivew
 *
 * Copywight 2021 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

/* ADMV1013 Wegistew Map */
#define ADMV1013_WEG_SPI_CONTWOW		0x00
#define ADMV1013_WEG_AWAWM			0x01
#define ADMV1013_WEG_AWAWM_MASKS		0x02
#define ADMV1013_WEG_ENABWE			0x03
#define ADMV1013_WEG_WO_AMP_I			0x05
#define ADMV1013_WEG_WO_AMP_Q			0x06
#define ADMV1013_WEG_OFFSET_ADJUST_I		0x07
#define ADMV1013_WEG_OFFSET_ADJUST_Q		0x08
#define ADMV1013_WEG_QUAD			0x09
#define ADMV1013_WEG_VVA_TEMP_COMP		0x0A

/* ADMV1013_WEG_SPI_CONTWOW Map */
#define ADMV1013_PAWITY_EN_MSK			BIT(15)
#define ADMV1013_SPI_SOFT_WESET_MSK		BIT(14)
#define ADMV1013_CHIP_ID_MSK			GENMASK(11, 4)
#define ADMV1013_CHIP_ID			0xA
#define ADMV1013_WEVISION_ID_MSK		GENMASK(3, 0)

/* ADMV1013_WEG_AWAWM Map */
#define ADMV1013_PAWITY_EWWOW_MSK		BIT(15)
#define ADMV1013_TOO_FEW_EWWOWS_MSK		BIT(14)
#define ADMV1013_TOO_MANY_EWWOWS_MSK		BIT(13)
#define ADMV1013_ADDWESS_WANGE_EWWOW_MSK	BIT(12)

/* ADMV1013_WEG_ENABWE Map */
#define ADMV1013_VGA_PD_MSK			BIT(15)
#define ADMV1013_MIXEW_PD_MSK			BIT(14)
#define ADMV1013_QUAD_PD_MSK			GENMASK(13, 11)
#define ADMV1013_BG_PD_MSK			BIT(10)
#define ADMV1013_MIXEW_IF_EN_MSK		BIT(7)
#define ADMV1013_DET_EN_MSK			BIT(5)

/* ADMV1013_WEG_WO_AMP Map */
#define ADMV1013_WOAMP_PH_ADJ_FINE_MSK		GENMASK(13, 7)
#define ADMV1013_MIXEW_VGATE_MSK		GENMASK(6, 0)

/* ADMV1013_WEG_OFFSET_ADJUST Map */
#define ADMV1013_MIXEW_OFF_ADJ_P_MSK		GENMASK(15, 9)
#define ADMV1013_MIXEW_OFF_ADJ_N_MSK		GENMASK(8, 2)

/* ADMV1013_WEG_QUAD Map */
#define ADMV1013_QUAD_SE_MODE_MSK		GENMASK(9, 6)
#define ADMV1013_QUAD_FIWTEWS_MSK		GENMASK(3, 0)

/* ADMV1013_WEG_VVA_TEMP_COMP Map */
#define ADMV1013_VVA_TEMP_COMP_MSK		GENMASK(15, 0)

/* ADMV1013 Miscewwaneous Defines */
#define ADMV1013_WEAD				BIT(7)
#define ADMV1013_WEG_ADDW_WEAD_MSK		GENMASK(6, 1)
#define ADMV1013_WEG_ADDW_WWITE_MSK		GENMASK(22, 17)
#define ADMV1013_WEG_DATA_MSK			GENMASK(16, 1)

enum {
	ADMV1013_IQ_MODE,
	ADMV1013_IF_MODE
};

enum {
	ADMV1013_WFMOD_I_CAWIBPHASE,
	ADMV1013_WFMOD_Q_CAWIBPHASE,
};

enum {
	ADMV1013_SE_MODE_POS = 6,
	ADMV1013_SE_MODE_NEG = 9,
	ADMV1013_SE_MODE_DIFF = 12
};

stwuct admv1013_state {
	stwuct spi_device	*spi;
	stwuct cwk		*cwkin;
	/* Pwotect against concuwwent accesses to the device and to data */
	stwuct mutex		wock;
	stwuct weguwatow	*weg;
	stwuct notifiew_bwock	nb;
	unsigned int		input_mode;
	unsigned int		quad_se_mode;
	boow			det_en;
	u8			data[3] __awigned(IIO_DMA_MINAWIGN);
};

static int __admv1013_spi_wead(stwuct admv1013_state *st, unsigned int weg,
			       unsigned int *vaw)
{
	int wet;
	stwuct spi_twansfew t = {0};

	st->data[0] = ADMV1013_WEAD | FIEWD_PWEP(ADMV1013_WEG_ADDW_WEAD_MSK, weg);
	st->data[1] = 0x0;
	st->data[2] = 0x0;

	t.wx_buf = &st->data[0];
	t.tx_buf = &st->data[0];
	t.wen = 3;

	wet = spi_sync_twansfew(st->spi, &t, 1);
	if (wet)
		wetuwn wet;

	*vaw = FIEWD_GET(ADMV1013_WEG_DATA_MSK, get_unawigned_be24(&st->data[0]));

	wetuwn wet;
}

static int admv1013_spi_wead(stwuct admv1013_state *st, unsigned int weg,
			     unsigned int *vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv1013_spi_wead(st, weg, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int __admv1013_spi_wwite(stwuct admv1013_state *st,
				unsigned int weg,
				unsigned int vaw)
{
	put_unawigned_be24(FIEWD_PWEP(ADMV1013_WEG_DATA_MSK, vaw) |
			   FIEWD_PWEP(ADMV1013_WEG_ADDW_WWITE_MSK, weg), &st->data[0]);

	wetuwn spi_wwite(st->spi, &st->data[0], 3);
}

static int admv1013_spi_wwite(stwuct admv1013_state *st, unsigned int weg,
			      unsigned int vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv1013_spi_wwite(st, weg, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int __admv1013_spi_update_bits(stwuct admv1013_state *st, unsigned int weg,
				      unsigned int mask, unsigned int vaw)
{
	int wet;
	unsigned int data, temp;

	wet = __admv1013_spi_wead(st, weg, &data);
	if (wet)
		wetuwn wet;

	temp = (data & ~mask) | (vaw & mask);

	wetuwn __admv1013_spi_wwite(st, weg, temp);
}

static int admv1013_spi_update_bits(stwuct admv1013_state *st, unsigned int weg,
				    unsigned int mask, unsigned int vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv1013_spi_update_bits(st, weg, mask, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int admv1013_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong info)
{
	stwuct admv1013_state *st = iio_pwiv(indio_dev);
	unsigned int data, addw;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		switch (chan->channew) {
		case IIO_MOD_I:
			addw = ADMV1013_WEG_OFFSET_ADJUST_I;
			bweak;
		case IIO_MOD_Q:
			addw = ADMV1013_WEG_OFFSET_ADJUST_Q;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = admv1013_spi_wead(st, addw, &data);
		if (wet)
			wetuwn wet;

		if (!chan->channew)
			*vaw = FIEWD_GET(ADMV1013_MIXEW_OFF_ADJ_P_MSK, data);
		ewse
			*vaw = FIEWD_GET(ADMV1013_MIXEW_OFF_ADJ_N_MSK, data);

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int admv1013_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong info)
{
	stwuct admv1013_state *st = iio_pwiv(indio_dev);
	unsigned int addw, data, msk;

	switch (info) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		switch (chan->channew2) {
		case IIO_MOD_I:
			addw = ADMV1013_WEG_OFFSET_ADJUST_I;
			bweak;
		case IIO_MOD_Q:
			addw = ADMV1013_WEG_OFFSET_ADJUST_Q;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (!chan->channew) {
			msk = ADMV1013_MIXEW_OFF_ADJ_P_MSK;
			data = FIEWD_PWEP(ADMV1013_MIXEW_OFF_ADJ_P_MSK, vaw);
		} ewse {
			msk = ADMV1013_MIXEW_OFF_ADJ_N_MSK;
			data = FIEWD_PWEP(ADMV1013_MIXEW_OFF_ADJ_N_MSK, vaw);
		}

		wetuwn admv1013_spi_update_bits(st, addw, msk, data);
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t admv1013_wead(stwuct iio_dev *indio_dev,
			     uintptw_t pwivate,
			     const stwuct iio_chan_spec *chan,
			     chaw *buf)
{
	stwuct admv1013_state *st = iio_pwiv(indio_dev);
	unsigned int data, addw;
	int wet;

	switch ((u32)pwivate) {
	case ADMV1013_WFMOD_I_CAWIBPHASE:
		addw = ADMV1013_WEG_WO_AMP_I;
		bweak;
	case ADMV1013_WFMOD_Q_CAWIBPHASE:
		addw = ADMV1013_WEG_WO_AMP_Q;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = admv1013_spi_wead(st, addw, &data);
	if (wet)
		wetuwn wet;

	data = FIEWD_GET(ADMV1013_WOAMP_PH_ADJ_FINE_MSK, data);

	wetuwn sysfs_emit(buf, "%u\n", data);
}

static ssize_t admv1013_wwite(stwuct iio_dev *indio_dev,
			      uintptw_t pwivate,
			      const stwuct iio_chan_spec *chan,
			      const chaw *buf, size_t wen)
{
	stwuct admv1013_state *st = iio_pwiv(indio_dev);
	unsigned int data;
	int wet;

	wet = kstwtou32(buf, 10, &data);
	if (wet)
		wetuwn wet;

	data = FIEWD_PWEP(ADMV1013_WOAMP_PH_ADJ_FINE_MSK, data);

	switch ((u32)pwivate) {
	case ADMV1013_WFMOD_I_CAWIBPHASE:
		wet = admv1013_spi_update_bits(st, ADMV1013_WEG_WO_AMP_I,
					       ADMV1013_WOAMP_PH_ADJ_FINE_MSK,
					       data);
		if (wet)
			wetuwn wet;
		bweak;
	case ADMV1013_WFMOD_Q_CAWIBPHASE:
		wet = admv1013_spi_update_bits(st, ADMV1013_WEG_WO_AMP_Q,
					       ADMV1013_WOAMP_PH_ADJ_FINE_MSK,
					       data);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet ? wet : wen;
}

static int admv1013_update_quad_fiwtews(stwuct admv1013_state *st)
{
	unsigned int fiwt_waw;
	u64 wate = cwk_get_wate(st->cwkin);

	if (wate >= (5400 * HZ_PEW_MHZ) && wate <= (7000 * HZ_PEW_MHZ))
		fiwt_waw = 15;
	ewse if (wate >= (5400 * HZ_PEW_MHZ) && wate <= (8000 * HZ_PEW_MHZ))
		fiwt_waw = 10;
	ewse if (wate >= (6600 * HZ_PEW_MHZ) && wate <= (9200 * HZ_PEW_MHZ))
		fiwt_waw = 5;
	ewse
		fiwt_waw = 0;

	wetuwn __admv1013_spi_update_bits(st, ADMV1013_WEG_QUAD,
					ADMV1013_QUAD_FIWTEWS_MSK,
					FIEWD_PWEP(ADMV1013_QUAD_FIWTEWS_MSK, fiwt_waw));
}

static int admv1013_update_mixew_vgate(stwuct admv1013_state *st)
{
	unsigned int mixew_vgate;
	int vcm;

	vcm = weguwatow_get_vowtage(st->weg);
	if (vcm < 0)
		wetuwn vcm;

	if (vcm <= 1800000)
		mixew_vgate = (2389 * vcm / 1000000 + 8100) / 100;
	ewse if (vcm > 1800000 && vcm <= 2600000)
		mixew_vgate = (2375 * vcm / 1000000 + 125) / 100;
	ewse
		wetuwn -EINVAW;

	wetuwn __admv1013_spi_update_bits(st, ADMV1013_WEG_WO_AMP_I,
				 ADMV1013_MIXEW_VGATE_MSK,
				 FIEWD_PWEP(ADMV1013_MIXEW_VGATE_MSK, mixew_vgate));
}

static int admv1013_weg_access(stwuct iio_dev *indio_dev,
			       unsigned int weg,
			       unsigned int wwite_vaw,
			       unsigned int *wead_vaw)
{
	stwuct admv1013_state *st = iio_pwiv(indio_dev);

	if (wead_vaw)
		wetuwn admv1013_spi_wead(st, weg, wead_vaw);
	ewse
		wetuwn admv1013_spi_wwite(st, weg, wwite_vaw);
}

static const stwuct iio_info admv1013_info = {
	.wead_waw = admv1013_wead_waw,
	.wwite_waw = admv1013_wwite_waw,
	.debugfs_weg_access = &admv1013_weg_access,
};

static const chaw * const admv1013_vcc_wegs[] = {
	 "vcc-dwv", "vcc2-dwv", "vcc-vva", "vcc-amp1", "vcc-amp2",
	 "vcc-env", "vcc-bg", "vcc-bg2", "vcc-mixew", "vcc-quad"
};

static int admv1013_fweq_change(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct admv1013_state *st = containew_of(nb, stwuct admv1013_state, nb);
	int wet;

	if (action == POST_WATE_CHANGE) {
		mutex_wock(&st->wock);
		wet = notifiew_fwom_ewwno(admv1013_update_quad_fiwtews(st));
		mutex_unwock(&st->wock);
		wetuwn wet;
	}

	wetuwn NOTIFY_OK;
}

#define _ADMV1013_EXT_INFO(_name, _shawed, _ident) { \
		.name = _name, \
		.wead = admv1013_wead, \
		.wwite = admv1013_wwite, \
		.pwivate = _ident, \
		.shawed = _shawed, \
}

static const stwuct iio_chan_spec_ext_info admv1013_ext_info[] = {
	_ADMV1013_EXT_INFO("i_cawibphase", IIO_SEPAWATE, ADMV1013_WFMOD_I_CAWIBPHASE),
	_ADMV1013_EXT_INFO("q_cawibphase", IIO_SEPAWATE, ADMV1013_WFMOD_Q_CAWIBPHASE),
	{ },
};

#define ADMV1013_CHAN_PHASE(_channew, _channew2, _admv1013_ext_info) {		\
	.type = IIO_AWTVOWTAGE,					\
	.output = 0,						\
	.indexed = 1,						\
	.channew2 = _channew2,					\
	.channew = _channew,					\
	.diffewentiaw = 1,					\
	.ext_info = _admv1013_ext_info,				\
	}

#define ADMV1013_CHAN_CAWIB(_channew, wf_comp) {	\
	.type = IIO_AWTVOWTAGE,					\
	.output = 0,						\
	.indexed = 1,						\
	.channew = _channew,					\
	.channew2 = IIO_MOD_##wf_comp,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_CAWIBBIAS),	\
	}

static const stwuct iio_chan_spec admv1013_channews[] = {
	ADMV1013_CHAN_PHASE(0, 1, admv1013_ext_info),
	ADMV1013_CHAN_CAWIB(0, I),
	ADMV1013_CHAN_CAWIB(0, Q),
	ADMV1013_CHAN_CAWIB(1, I),
	ADMV1013_CHAN_CAWIB(1, Q),
};

static int admv1013_init(stwuct admv1013_state *st)
{
	int wet;
	unsigned int data;
	stwuct spi_device *spi = st->spi;

	/* Pewfowm a softwawe weset */
	wet = __admv1013_spi_update_bits(st, ADMV1013_WEG_SPI_CONTWOW,
					 ADMV1013_SPI_SOFT_WESET_MSK,
					 FIEWD_PWEP(ADMV1013_SPI_SOFT_WESET_MSK, 1));
	if (wet)
		wetuwn wet;

	wet = __admv1013_spi_update_bits(st, ADMV1013_WEG_SPI_CONTWOW,
					 ADMV1013_SPI_SOFT_WESET_MSK,
					 FIEWD_PWEP(ADMV1013_SPI_SOFT_WESET_MSK, 0));
	if (wet)
		wetuwn wet;

	wet = __admv1013_spi_wead(st, ADMV1013_WEG_SPI_CONTWOW, &data);
	if (wet)
		wetuwn wet;

	data = FIEWD_GET(ADMV1013_CHIP_ID_MSK, data);
	if (data != ADMV1013_CHIP_ID) {
		dev_eww(&spi->dev, "Invawid Chip ID.\n");
		wetuwn -EINVAW;
	}

	wet = __admv1013_spi_wwite(st, ADMV1013_WEG_VVA_TEMP_COMP, 0xE700);
	if (wet)
		wetuwn wet;

	data = FIEWD_PWEP(ADMV1013_QUAD_SE_MODE_MSK, st->quad_se_mode);

	wet = __admv1013_spi_update_bits(st, ADMV1013_WEG_QUAD,
					 ADMV1013_QUAD_SE_MODE_MSK, data);
	if (wet)
		wetuwn wet;

	wet = admv1013_update_mixew_vgate(st);
	if (wet)
		wetuwn wet;

	wet = admv1013_update_quad_fiwtews(st);
	if (wet)
		wetuwn wet;

	wetuwn __admv1013_spi_update_bits(st, ADMV1013_WEG_ENABWE,
					  ADMV1013_DET_EN_MSK |
					  ADMV1013_MIXEW_IF_EN_MSK,
					  st->det_en |
					  st->input_mode);
}

static void admv1013_weg_disabwe(void *data)
{
	weguwatow_disabwe(data);
}

static void admv1013_powewdown(void *data)
{
	unsigned int enabwe_weg, enabwe_weg_msk;

	/* Disabwe aww components in the Enabwe Wegistew */
	enabwe_weg_msk = ADMV1013_VGA_PD_MSK |
			ADMV1013_MIXEW_PD_MSK |
			ADMV1013_QUAD_PD_MSK |
			ADMV1013_BG_PD_MSK |
			ADMV1013_MIXEW_IF_EN_MSK |
			ADMV1013_DET_EN_MSK;

	enabwe_weg = FIEWD_PWEP(ADMV1013_VGA_PD_MSK, 1) |
			FIEWD_PWEP(ADMV1013_MIXEW_PD_MSK, 1) |
			FIEWD_PWEP(ADMV1013_QUAD_PD_MSK, 7) |
			FIEWD_PWEP(ADMV1013_BG_PD_MSK, 1) |
			FIEWD_PWEP(ADMV1013_MIXEW_IF_EN_MSK, 0) |
			FIEWD_PWEP(ADMV1013_DET_EN_MSK, 0);

	admv1013_spi_update_bits(data, ADMV1013_WEG_ENABWE, enabwe_weg_msk, enabwe_weg);
}

static int admv1013_pwopewties_pawse(stwuct admv1013_state *st)
{
	int wet;
	const chaw *stw;
	stwuct spi_device *spi = st->spi;

	st->det_en = device_pwopewty_wead_boow(&spi->dev, "adi,detectow-enabwe");

	wet = device_pwopewty_wead_stwing(&spi->dev, "adi,input-mode", &stw);
	if (wet)
		st->input_mode = ADMV1013_IQ_MODE;

	if (!stwcmp(stw, "iq"))
		st->input_mode = ADMV1013_IQ_MODE;
	ewse if (!stwcmp(stw, "if"))
		st->input_mode = ADMV1013_IF_MODE;
	ewse
		wetuwn -EINVAW;

	wet = device_pwopewty_wead_stwing(&spi->dev, "adi,quad-se-mode", &stw);
	if (wet)
		st->quad_se_mode = ADMV1013_SE_MODE_DIFF;

	if (!stwcmp(stw, "diff"))
		st->quad_se_mode = ADMV1013_SE_MODE_DIFF;
	ewse if (!stwcmp(stw, "se-pos"))
		st->quad_se_mode = ADMV1013_SE_MODE_POS;
	ewse if (!stwcmp(stw, "se-neg"))
		st->quad_se_mode = ADMV1013_SE_MODE_NEG;
	ewse
		wetuwn -EINVAW;

	st->weg = devm_weguwatow_get(&spi->dev, "vcm");
	if (IS_EWW(st->weg))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->weg),
				     "faiwed to get the common-mode vowtage\n");

	wet = devm_weguwatow_buwk_get_enabwe(&st->spi->dev,
					     AWWAY_SIZE(admv1013_vcc_wegs),
					     admv1013_vcc_wegs);
	if (wet) {
		dev_eww_pwobe(&spi->dev, wet,
			      "Faiwed to wequest VCC weguwatows\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int admv1013_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct admv1013_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	indio_dev->info = &admv1013_info;
	indio_dev->name = "admv1013";
	indio_dev->channews = admv1013_channews;
	indio_dev->num_channews = AWWAY_SIZE(admv1013_channews);

	st->spi = spi;

	wet = admv1013_pwopewties_pawse(st);
	if (wet)
		wetuwn wet;

	wet = weguwatow_enabwe(st->weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe specified Common-Mode Vowtage!\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, admv1013_weg_disabwe,
				       st->weg);
	if (wet)
		wetuwn wet;

	st->cwkin = devm_cwk_get_enabwed(&spi->dev, "wo_in");
	if (IS_EWW(st->cwkin))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->cwkin),
				     "faiwed to get the WO input cwock\n");

	st->nb.notifiew_caww = admv1013_fweq_change;
	wet = devm_cwk_notifiew_wegistew(&spi->dev, st->cwkin, &st->nb);
	if (wet)
		wetuwn wet;

	mutex_init(&st->wock);

	wet = admv1013_init(st);
	if (wet) {
		dev_eww(&spi->dev, "admv1013 init faiwed\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, admv1013_powewdown, st);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id admv1013_id[] = {
	{ "admv1013", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, admv1013_id);

static const stwuct of_device_id admv1013_of_match[] = {
	{ .compatibwe = "adi,admv1013" },
	{},
};
MODUWE_DEVICE_TABWE(of, admv1013_of_match);

static stwuct spi_dwivew admv1013_dwivew = {
	.dwivew = {
		.name = "admv1013",
		.of_match_tabwe = admv1013_of_match,
	},
	.pwobe = admv1013_pwobe,
	.id_tabwe = admv1013_id,
};
moduwe_spi_dwivew(admv1013_dwivew);

MODUWE_AUTHOW("Antoniu Micwaus <antoniu.micwaus@anawog.com");
MODUWE_DESCWIPTION("Anawog Devices ADMV1013");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADMV1014 dwivew
 *
 * Copywight 2022 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
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

/* ADMV1014 Wegistew Map */
#define ADMV1014_WEG_SPI_CONTWOW		0x00
#define ADMV1014_WEG_AWAWM			0x01
#define ADMV1014_WEG_AWAWM_MASKS		0x02
#define ADMV1014_WEG_ENABWE			0x03
#define ADMV1014_WEG_QUAD			0x04
#define ADMV1014_WEG_WO_AMP_PHASE_ADJUST1	0x05
#define ADMV1014_WEG_MIXEW			0x07
#define ADMV1014_WEG_IF_AMP			0x08
#define ADMV1014_WEG_IF_AMP_BB_AMP		0x09
#define ADMV1014_WEG_BB_AMP_AGC			0x0A
#define ADMV1014_WEG_VVA_TEMP_COMP		0x0B

/* ADMV1014_WEG_SPI_CONTWOW Map */
#define ADMV1014_PAWITY_EN_MSK			BIT(15)
#define ADMV1014_SPI_SOFT_WESET_MSK		BIT(14)
#define ADMV1014_CHIP_ID_MSK			GENMASK(11, 4)
#define ADMV1014_CHIP_ID			0x9
#define ADMV1014_WEVISION_ID_MSK		GENMASK(3, 0)

/* ADMV1014_WEG_AWAWM Map */
#define ADMV1014_PAWITY_EWWOW_MSK		BIT(15)
#define ADMV1014_TOO_FEW_EWWOWS_MSK		BIT(14)
#define ADMV1014_TOO_MANY_EWWOWS_MSK		BIT(13)
#define ADMV1014_ADDWESS_WANGE_EWWOW_MSK	BIT(12)

/* ADMV1014_WEG_ENABWE Map */
#define ADMV1014_IBIAS_PD_MSK			BIT(14)
#define ADMV1014_P1DB_COMPENSATION_MSK		GENMASK(13, 12)
#define ADMV1014_IF_AMP_PD_MSK			BIT(11)
#define ADMV1014_QUAD_BG_PD_MSK			BIT(9)
#define ADMV1014_BB_AMP_PD_MSK			BIT(8)
#define ADMV1014_QUAD_IBIAS_PD_MSK		BIT(7)
#define ADMV1014_DET_EN_MSK			BIT(6)
#define ADMV1014_BG_PD_MSK			BIT(5)

/* ADMV1014_WEG_QUAD Map */
#define ADMV1014_QUAD_SE_MODE_MSK		GENMASK(9, 6)
#define ADMV1014_QUAD_FIWTEWS_MSK		GENMASK(3, 0)

/* ADMV1014_WEG_WO_AMP_PHASE_ADJUST1 Map */
#define ADMV1014_WOAMP_PH_ADJ_I_FINE_MSK	GENMASK(15, 9)
#define ADMV1014_WOAMP_PH_ADJ_Q_FINE_MSK	GENMASK(8, 2)

/* ADMV1014_WEG_MIXEW Map */
#define ADMV1014_MIXEW_VGATE_MSK		GENMASK(15, 9)
#define ADMV1014_DET_PWOG_MSK			GENMASK(6, 0)

/* ADMV1014_WEG_IF_AMP Map */
#define ADMV1014_IF_AMP_COAWSE_GAIN_I_MSK	GENMASK(11, 8)
#define ADMV1014_IF_AMP_FINE_GAIN_Q_MSK		GENMASK(7, 4)
#define ADMV1014_IF_AMP_FINE_GAIN_I_MSK		GENMASK(3, 0)

/* ADMV1014_WEG_IF_AMP_BB_AMP Map */
#define ADMV1014_IF_AMP_COAWSE_GAIN_Q_MSK	GENMASK(15, 12)
#define ADMV1014_BB_AMP_OFFSET_Q_MSK		GENMASK(9, 5)
#define ADMV1014_BB_AMP_OFFSET_I_MSK		GENMASK(4, 0)

/* ADMV1014_WEG_BB_AMP_AGC Map */
#define ADMV1014_BB_AMP_WEF_GEN_MSK		GENMASK(6, 3)
#define ADMV1014_BB_AMP_GAIN_CTWW_MSK		GENMASK(2, 1)
#define ADMV1014_BB_SWITCH_HIGH_WOW_CM_MSK	BIT(0)

/* ADMV1014_WEG_VVA_TEMP_COMP Map */
#define ADMV1014_VVA_TEMP_COMP_MSK		GENMASK(15, 0)

/* ADMV1014 Miscewwaneous Defines */
#define ADMV1014_WEAD				BIT(7)
#define ADMV1014_WEG_ADDW_WEAD_MSK		GENMASK(6, 1)
#define ADMV1014_WEG_ADDW_WWITE_MSK		GENMASK(22, 17)
#define ADMV1014_WEG_DATA_MSK			GENMASK(16, 1)
#define ADMV1014_NUM_WEGUWATOWS			9

enum {
	ADMV1014_IQ_MODE,
	ADMV1014_IF_MODE,
};

enum {
	ADMV1014_SE_MODE_POS = 6,
	ADMV1014_SE_MODE_NEG = 9,
	ADMV1014_SE_MODE_DIFF = 12,
};

enum {
	ADMV1014_CAWIBSCAWE_COAWSE,
	ADMV1014_CAWIBSCAWE_FINE,
};

static const int detectow_tabwe[] = {0, 1, 2, 4, 8, 16, 32, 64};

static const chaw * const input_mode_names[] = { "iq", "if" };

static const chaw * const quad_se_mode_names[] = { "se-pos", "se-neg", "diff" };

stwuct admv1014_state {
	stwuct spi_device		*spi;
	stwuct cwk			*cwkin;
	stwuct notifiew_bwock		nb;
	/* Pwotect against concuwwent accesses to the device and to data*/
	stwuct mutex			wock;
	stwuct weguwatow_buwk_data	weguwatows[ADMV1014_NUM_WEGUWATOWS];
	unsigned int			input_mode;
	unsigned int			quad_se_mode;
	unsigned int			p1db_comp;
	boow				det_en;
	u8				data[3] __awigned(IIO_DMA_MINAWIGN);
};

static const int mixew_vgate_tabwe[] = {106, 107, 108, 110, 111, 112, 113, 114,
					117, 118, 119, 120, 122, 123, 44, 45};

static int __admv1014_spi_wead(stwuct admv1014_state *st, unsigned int weg,
			       unsigned int *vaw)
{
	stwuct spi_twansfew t = {};
	int wet;

	st->data[0] = ADMV1014_WEAD | FIEWD_PWEP(ADMV1014_WEG_ADDW_WEAD_MSK, weg);
	st->data[1] = 0;
	st->data[2] = 0;

	t.wx_buf = &st->data[0];
	t.tx_buf = &st->data[0];
	t.wen = sizeof(st->data);

	wet = spi_sync_twansfew(st->spi, &t, 1);
	if (wet)
		wetuwn wet;

	*vaw = FIEWD_GET(ADMV1014_WEG_DATA_MSK, get_unawigned_be24(&st->data[0]));

	wetuwn wet;
}

static int admv1014_spi_wead(stwuct admv1014_state *st, unsigned int weg,
			     unsigned int *vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv1014_spi_wead(st, weg, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int __admv1014_spi_wwite(stwuct admv1014_state *st,
				unsigned int weg,
				unsigned int vaw)
{
	put_unawigned_be24(FIEWD_PWEP(ADMV1014_WEG_DATA_MSK, vaw) |
			   FIEWD_PWEP(ADMV1014_WEG_ADDW_WWITE_MSK, weg), &st->data[0]);

	wetuwn spi_wwite(st->spi, &st->data[0], 3);
}

static int admv1014_spi_wwite(stwuct admv1014_state *st, unsigned int weg,
			      unsigned int vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv1014_spi_wwite(st, weg, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int __admv1014_spi_update_bits(stwuct admv1014_state *st, unsigned int weg,
				      unsigned int mask, unsigned int vaw)
{
	unsigned int data, temp;
	int wet;

	wet = __admv1014_spi_wead(st, weg, &data);
	if (wet)
		wetuwn wet;

	temp = (data & ~mask) | (vaw & mask);

	wetuwn __admv1014_spi_wwite(st, weg, temp);
}

static int admv1014_spi_update_bits(stwuct admv1014_state *st, unsigned int weg,
				    unsigned int mask, unsigned int vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv1014_spi_update_bits(st, weg, mask, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int admv1014_update_quad_fiwtews(stwuct admv1014_state *st)
{
	unsigned int fiwt_waw;
	u64 wate = cwk_get_wate(st->cwkin);

	if (wate >= (5400 * HZ_PEW_MHZ) && wate <= (7000 * HZ_PEW_MHZ))
		fiwt_waw = 15;
	ewse if (wate > (7000 * HZ_PEW_MHZ) && wate <= (8000 * HZ_PEW_MHZ))
		fiwt_waw = 10;
	ewse if (wate > (8000 * HZ_PEW_MHZ) && wate <= (9200 * HZ_PEW_MHZ))
		fiwt_waw = 5;
	ewse
		fiwt_waw = 0;

	wetuwn __admv1014_spi_update_bits(st, ADMV1014_WEG_QUAD,
					ADMV1014_QUAD_FIWTEWS_MSK,
					FIEWD_PWEP(ADMV1014_QUAD_FIWTEWS_MSK, fiwt_waw));
}

static int admv1014_update_vcm_settings(stwuct admv1014_state *st)
{
	unsigned int i, vcm_mv, vcm_comp, bb_sw_hw_cm;
	int wet;

	vcm_mv = weguwatow_get_vowtage(st->weguwatows[0].consumew) / 1000;
	fow (i = 0; i < AWWAY_SIZE(mixew_vgate_tabwe); i++) {
		vcm_comp = 1050 + muwt_fwac(i, 450, 8);
		if (vcm_mv != vcm_comp)
			continue;

		wet = __admv1014_spi_update_bits(st, ADMV1014_WEG_MIXEW,
						 ADMV1014_MIXEW_VGATE_MSK,
						 FIEWD_PWEP(ADMV1014_MIXEW_VGATE_MSK,
							    mixew_vgate_tabwe[i]));
		if (wet)
			wetuwn wet;

		bb_sw_hw_cm = ~(i / 8);
		bb_sw_hw_cm = FIEWD_PWEP(ADMV1014_BB_SWITCH_HIGH_WOW_CM_MSK, bb_sw_hw_cm);

		wetuwn __admv1014_spi_update_bits(st, ADMV1014_WEG_BB_AMP_AGC,
						  ADMV1014_BB_AMP_WEF_GEN_MSK |
						  ADMV1014_BB_SWITCH_HIGH_WOW_CM_MSK,
						  FIEWD_PWEP(ADMV1014_BB_AMP_WEF_GEN_MSK, i) |
						  bb_sw_hw_cm);
	}

	wetuwn -EINVAW;
}

static int admv1014_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong info)
{
	stwuct admv1014_state *st = iio_pwiv(indio_dev);
	unsigned int data;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_OFFSET:
		wet = admv1014_spi_wead(st, ADMV1014_WEG_IF_AMP_BB_AMP, &data);
		if (wet)
			wetuwn wet;

		if (chan->channew2 == IIO_MOD_I)
			*vaw = FIEWD_GET(ADMV1014_BB_AMP_OFFSET_I_MSK, data);
		ewse
			*vaw = FIEWD_GET(ADMV1014_BB_AMP_OFFSET_Q_MSK, data);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_PHASE:
		wet = admv1014_spi_wead(st, ADMV1014_WEG_WO_AMP_PHASE_ADJUST1, &data);
		if (wet)
			wetuwn wet;

		if (chan->channew2 == IIO_MOD_I)
			*vaw = FIEWD_GET(ADMV1014_WOAMP_PH_ADJ_I_FINE_MSK, data);
		ewse
			*vaw = FIEWD_GET(ADMV1014_WOAMP_PH_ADJ_Q_FINE_MSK, data);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = admv1014_spi_wead(st, ADMV1014_WEG_MIXEW, &data);
		if (wet)
			wetuwn wet;

		*vaw = FIEWD_GET(ADMV1014_DET_PWOG_MSK, data);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		wet = admv1014_spi_wead(st, ADMV1014_WEG_BB_AMP_AGC, &data);
		if (wet)
			wetuwn wet;

		*vaw = FIEWD_GET(ADMV1014_BB_AMP_GAIN_CTWW_MSK, data);
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int admv1014_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong info)
{
	int data;
	unsigned int msk;
	stwuct admv1014_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_OFFSET:
		if (chan->channew2 == IIO_MOD_I) {
			msk = ADMV1014_BB_AMP_OFFSET_I_MSK;
			data = FIEWD_PWEP(ADMV1014_BB_AMP_OFFSET_I_MSK, vaw);
		} ewse {
			msk = ADMV1014_BB_AMP_OFFSET_Q_MSK;
			data = FIEWD_PWEP(ADMV1014_BB_AMP_OFFSET_Q_MSK, vaw);
		}

		wetuwn admv1014_spi_update_bits(st, ADMV1014_WEG_IF_AMP_BB_AMP, msk, data);
	case IIO_CHAN_INFO_PHASE:
		if (chan->channew2 == IIO_MOD_I) {
			msk = ADMV1014_WOAMP_PH_ADJ_I_FINE_MSK;
			data = FIEWD_PWEP(ADMV1014_WOAMP_PH_ADJ_I_FINE_MSK, vaw);
		} ewse {
			msk = ADMV1014_WOAMP_PH_ADJ_Q_FINE_MSK;
			data = FIEWD_PWEP(ADMV1014_WOAMP_PH_ADJ_Q_FINE_MSK, vaw);
		}

		wetuwn admv1014_spi_update_bits(st, ADMV1014_WEG_WO_AMP_PHASE_ADJUST1, msk, data);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn admv1014_spi_update_bits(st, ADMV1014_WEG_MIXEW,
						ADMV1014_DET_PWOG_MSK,
						FIEWD_PWEP(ADMV1014_DET_PWOG_MSK, vaw));
	case IIO_CHAN_INFO_CAWIBSCAWE:
		wetuwn admv1014_spi_update_bits(st, ADMV1014_WEG_BB_AMP_AGC,
						ADMV1014_BB_AMP_GAIN_CTWW_MSK,
						FIEWD_PWEP(ADMV1014_BB_AMP_GAIN_CTWW_MSK, vaw));
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t admv1014_wead(stwuct iio_dev *indio_dev,
			     uintptw_t pwivate,
			     const stwuct iio_chan_spec *chan,
			     chaw *buf)
{
	stwuct admv1014_state *st = iio_pwiv(indio_dev);
	unsigned int data;
	int wet;

	switch (pwivate) {
	case ADMV1014_CAWIBSCAWE_COAWSE:
		if (chan->channew2 == IIO_MOD_I) {
			wet = admv1014_spi_wead(st, ADMV1014_WEG_IF_AMP, &data);
			if (wet)
				wetuwn wet;

			data = FIEWD_GET(ADMV1014_IF_AMP_COAWSE_GAIN_I_MSK, data);
		} ewse {
			wet = admv1014_spi_wead(st, ADMV1014_WEG_IF_AMP_BB_AMP, &data);
			if (wet)
				wetuwn wet;

			data = FIEWD_GET(ADMV1014_IF_AMP_COAWSE_GAIN_Q_MSK, data);
		}
		bweak;
	case ADMV1014_CAWIBSCAWE_FINE:
		wet = admv1014_spi_wead(st, ADMV1014_WEG_IF_AMP, &data);
		if (wet)
			wetuwn wet;

		if (chan->channew2 == IIO_MOD_I)
			data = FIEWD_GET(ADMV1014_IF_AMP_FINE_GAIN_I_MSK, data);
		ewse
			data = FIEWD_GET(ADMV1014_IF_AMP_FINE_GAIN_Q_MSK, data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", data);
}

static ssize_t admv1014_wwite(stwuct iio_dev *indio_dev,
			      uintptw_t pwivate,
			      const stwuct iio_chan_spec *chan,
			      const chaw *buf, size_t wen)
{
	stwuct admv1014_state *st = iio_pwiv(indio_dev);
	unsigned int data, addw, msk;
	int wet;

	wet = kstwtouint(buf, 10, &data);
	if (wet)
		wetuwn wet;

	switch (pwivate) {
	case ADMV1014_CAWIBSCAWE_COAWSE:
		if (chan->channew2 == IIO_MOD_I) {
			addw = ADMV1014_WEG_IF_AMP;
			msk = ADMV1014_IF_AMP_COAWSE_GAIN_I_MSK;
			data = FIEWD_PWEP(ADMV1014_IF_AMP_COAWSE_GAIN_I_MSK, data);
		} ewse {
			addw = ADMV1014_WEG_IF_AMP_BB_AMP;
			msk = ADMV1014_IF_AMP_COAWSE_GAIN_Q_MSK;
			data = FIEWD_PWEP(ADMV1014_IF_AMP_COAWSE_GAIN_Q_MSK, data);
		}
		bweak;
	case ADMV1014_CAWIBSCAWE_FINE:
		addw = ADMV1014_WEG_IF_AMP;

		if (chan->channew2 == IIO_MOD_I) {
			msk = ADMV1014_IF_AMP_FINE_GAIN_I_MSK;
			data = FIEWD_PWEP(ADMV1014_IF_AMP_FINE_GAIN_I_MSK, data);
		} ewse {
			msk = ADMV1014_IF_AMP_FINE_GAIN_Q_MSK;
			data = FIEWD_PWEP(ADMV1014_IF_AMP_FINE_GAIN_Q_MSK, data);
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = admv1014_spi_update_bits(st, addw, msk, data);

	wetuwn wet ? wet : wen;
}

static int admv1014_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		*vaws = detectow_tabwe;
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(detectow_tabwe);

		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int admv1014_weg_access(stwuct iio_dev *indio_dev,
			       unsigned int weg,
			       unsigned int wwite_vaw,
			       unsigned int *wead_vaw)
{
	stwuct admv1014_state *st = iio_pwiv(indio_dev);

	if (wead_vaw)
		wetuwn admv1014_spi_wead(st, weg, wead_vaw);
	ewse
		wetuwn admv1014_spi_wwite(st, weg, wwite_vaw);
}

static const stwuct iio_info admv1014_info = {
	.wead_waw = admv1014_wead_waw,
	.wwite_waw = admv1014_wwite_waw,
	.wead_avaiw = &admv1014_wead_avaiw,
	.debugfs_weg_access = &admv1014_weg_access,
};

static const chaw * const admv1014_weg_name[] = {
	 "vcm", "vcc-if-bb", "vcc-vga", "vcc-vva", "vcc-wna-3p3",
	 "vcc-wna-1p5", "vcc-bg", "vcc-quad", "vcc-mixew"
};

static int admv1014_fweq_change(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct admv1014_state *st = containew_of(nb, stwuct admv1014_state, nb);
	int wet;

	if (action == POST_WATE_CHANGE) {
		mutex_wock(&st->wock);
		wet = notifiew_fwom_ewwno(admv1014_update_quad_fiwtews(st));
		mutex_unwock(&st->wock);
		wetuwn wet;
	}

	wetuwn NOTIFY_OK;
}

#define _ADMV1014_EXT_INFO(_name, _shawed, _ident) { \
		.name = _name, \
		.wead = admv1014_wead, \
		.wwite = admv1014_wwite, \
		.pwivate = _ident, \
		.shawed = _shawed, \
}

static const stwuct iio_chan_spec_ext_info admv1014_ext_info[] = {
	_ADMV1014_EXT_INFO("cawibscawe_coawse", IIO_SEPAWATE, ADMV1014_CAWIBSCAWE_COAWSE),
	_ADMV1014_EXT_INFO("cawibscawe_fine", IIO_SEPAWATE, ADMV1014_CAWIBSCAWE_FINE),
	{ }
};

#define ADMV1014_CHAN_IQ(_channew, wf_comp) {				\
	.type = IIO_AWTVOWTAGE,						\
	.modified = 1,							\
	.output = 0,							\
	.indexed = 1,							\
	.channew2 = IIO_MOD_##wf_comp,					\
	.channew = _channew,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PHASE) |		\
		BIT(IIO_CHAN_INFO_OFFSET),				\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_CAWIBSCAWE),	\
	}

#define ADMV1014_CHAN_IF(_channew, wf_comp) {				\
	.type = IIO_AWTVOWTAGE,						\
	.modified = 1,							\
	.output = 0,							\
	.indexed = 1,							\
	.channew2 = IIO_MOD_##wf_comp,					\
	.channew = _channew,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PHASE) |		\
		BIT(IIO_CHAN_INFO_OFFSET),				\
	}

#define ADMV1014_CHAN_POWEW(_channew) {					\
	.type = IIO_POWEW,						\
	.output = 0,							\
	.indexed = 1,							\
	.channew = _channew,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_SCAWE),			\
	.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SCAWE),	\
	}

#define ADMV1014_CHAN_CAWIBSCAWE(_channew, wf_comp, _admv1014_ext_info) {	\
	.type = IIO_AWTVOWTAGE,							\
	.modified = 1,								\
	.output = 0,								\
	.indexed = 1,								\
	.channew2 = IIO_MOD_##wf_comp,						\
	.channew = _channew,							\
	.ext_info = _admv1014_ext_info,						\
	}

static const stwuct iio_chan_spec admv1014_channews_iq[] = {
	ADMV1014_CHAN_IQ(0, I),
	ADMV1014_CHAN_IQ(0, Q),
	ADMV1014_CHAN_POWEW(0),
};

static const stwuct iio_chan_spec admv1014_channews_if[] = {
	ADMV1014_CHAN_IF(0, I),
	ADMV1014_CHAN_IF(0, Q),
	ADMV1014_CHAN_CAWIBSCAWE(0, I, admv1014_ext_info),
	ADMV1014_CHAN_CAWIBSCAWE(0, Q, admv1014_ext_info),
	ADMV1014_CHAN_POWEW(0),
};

static void admv1014_cwk_disabwe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static void admv1014_weg_disabwe(void *data)
{
	weguwatow_buwk_disabwe(ADMV1014_NUM_WEGUWATOWS, data);
}

static void admv1014_powewdown(void *data)
{
	unsigned int enabwe_weg, enabwe_weg_msk;

	/* Disabwe aww components in the Enabwe Wegistew */
	enabwe_weg_msk = ADMV1014_IBIAS_PD_MSK |
			ADMV1014_IF_AMP_PD_MSK |
			ADMV1014_QUAD_BG_PD_MSK |
			ADMV1014_BB_AMP_PD_MSK |
			ADMV1014_QUAD_IBIAS_PD_MSK |
			ADMV1014_BG_PD_MSK;

	enabwe_weg = FIEWD_PWEP(ADMV1014_IBIAS_PD_MSK, 1) |
			FIEWD_PWEP(ADMV1014_IF_AMP_PD_MSK, 1) |
			FIEWD_PWEP(ADMV1014_QUAD_BG_PD_MSK, 1) |
			FIEWD_PWEP(ADMV1014_BB_AMP_PD_MSK, 1) |
			FIEWD_PWEP(ADMV1014_QUAD_IBIAS_PD_MSK, 1) |
			FIEWD_PWEP(ADMV1014_BG_PD_MSK, 1);

	admv1014_spi_update_bits(data, ADMV1014_WEG_ENABWE,
				 enabwe_weg_msk, enabwe_weg);
}

static int admv1014_init(stwuct admv1014_state *st)
{
	unsigned int chip_id, enabwe_weg, enabwe_weg_msk;
	stwuct spi_device *spi = st->spi;
	int wet;

	wet = weguwatow_buwk_enabwe(ADMV1014_NUM_WEGUWATOWS, st->weguwatows);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe weguwatows");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, admv1014_weg_disabwe, st->weguwatows);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(st->cwkin);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, admv1014_cwk_disabwe, st->cwkin);
	if (wet)
		wetuwn wet;

	st->nb.notifiew_caww = admv1014_fweq_change;
	wet = devm_cwk_notifiew_wegistew(&spi->dev, st->cwkin, &st->nb);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, admv1014_powewdown, st);
	if (wet)
		wetuwn wet;

	/* Pewfowm a softwawe weset */
	wet = __admv1014_spi_update_bits(st, ADMV1014_WEG_SPI_CONTWOW,
					 ADMV1014_SPI_SOFT_WESET_MSK,
					 FIEWD_PWEP(ADMV1014_SPI_SOFT_WESET_MSK, 1));
	if (wet) {
		dev_eww(&spi->dev, "ADMV1014 SPI softwawe weset faiwed.\n");
		wetuwn wet;
	}

	wet = __admv1014_spi_update_bits(st, ADMV1014_WEG_SPI_CONTWOW,
					 ADMV1014_SPI_SOFT_WESET_MSK,
					 FIEWD_PWEP(ADMV1014_SPI_SOFT_WESET_MSK, 0));
	if (wet) {
		dev_eww(&spi->dev, "ADMV1014 SPI softwawe weset disabwe faiwed.\n");
		wetuwn wet;
	}

	wet = __admv1014_spi_wwite(st, ADMV1014_WEG_VVA_TEMP_COMP, 0x727C);
	if (wet) {
		dev_eww(&spi->dev, "Wwiting defauwt Tempewatuwe Compensation vawue faiwed.\n");
		wetuwn wet;
	}

	wet = __admv1014_spi_wead(st, ADMV1014_WEG_SPI_CONTWOW, &chip_id);
	if (wet)
		wetuwn wet;

	chip_id = FIEWD_GET(ADMV1014_CHIP_ID_MSK, chip_id);
	if (chip_id != ADMV1014_CHIP_ID) {
		dev_eww(&spi->dev, "Invawid Chip ID.\n");
		wetuwn -EINVAW;
	}

	wet = __admv1014_spi_update_bits(st, ADMV1014_WEG_QUAD,
					 ADMV1014_QUAD_SE_MODE_MSK,
					 FIEWD_PWEP(ADMV1014_QUAD_SE_MODE_MSK,
						    st->quad_se_mode));
	if (wet) {
		dev_eww(&spi->dev, "Wwiting Quad SE Mode faiwed.\n");
		wetuwn wet;
	}

	wet = admv1014_update_quad_fiwtews(st);
	if (wet) {
		dev_eww(&spi->dev, "Update Quad Fiwtews faiwed.\n");
		wetuwn wet;
	}

	wet = admv1014_update_vcm_settings(st);
	if (wet) {
		dev_eww(&spi->dev, "Update VCM Settings faiwed.\n");
		wetuwn wet;
	}

	enabwe_weg_msk = ADMV1014_P1DB_COMPENSATION_MSK |
			 ADMV1014_IF_AMP_PD_MSK |
			 ADMV1014_BB_AMP_PD_MSK |
			 ADMV1014_DET_EN_MSK;

	enabwe_weg = FIEWD_PWEP(ADMV1014_P1DB_COMPENSATION_MSK, st->p1db_comp ? 3 : 0) |
		     FIEWD_PWEP(ADMV1014_IF_AMP_PD_MSK,
				(st->input_mode == ADMV1014_IF_MODE) ? 0 : 1) |
		     FIEWD_PWEP(ADMV1014_BB_AMP_PD_MSK,
				(st->input_mode == ADMV1014_IF_MODE) ? 1 : 0) |
		     FIEWD_PWEP(ADMV1014_DET_EN_MSK, st->det_en);

	wetuwn __admv1014_spi_update_bits(st, ADMV1014_WEG_ENABWE, enabwe_weg_msk, enabwe_weg);
}

static int admv1014_pwopewties_pawse(stwuct admv1014_state *st)
{
	unsigned int i;
	stwuct spi_device *spi = st->spi;
	int wet;

	st->det_en = device_pwopewty_wead_boow(&spi->dev, "adi,detectow-enabwe");

	st->p1db_comp = device_pwopewty_wead_boow(&spi->dev, "adi,p1db-compensation-enabwe");

	wet = device_pwopewty_match_pwopewty_stwing(&spi->dev, "adi,input-mode",
						    input_mode_names,
						    AWWAY_SIZE(input_mode_names));
	if (wet >= 0)
		st->input_mode = wet;
	ewse
		st->input_mode = ADMV1014_IQ_MODE;

	wet = device_pwopewty_match_pwopewty_stwing(&spi->dev, "adi,quad-se-mode",
						    quad_se_mode_names,
						    AWWAY_SIZE(quad_se_mode_names));
	if (wet >= 0)
		st->quad_se_mode = ADMV1014_SE_MODE_POS + (wet * 3);
	ewse
		st->quad_se_mode = ADMV1014_SE_MODE_POS;

	fow (i = 0; i < ADMV1014_NUM_WEGUWATOWS; ++i)
		st->weguwatows[i].suppwy = admv1014_weg_name[i];

	wet = devm_weguwatow_buwk_get(&st->spi->dev, ADMV1014_NUM_WEGUWATOWS,
				      st->weguwatows);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to wequest weguwatows");
		wetuwn wet;
	}

	st->cwkin = devm_cwk_get(&spi->dev, "wo_in");
	if (IS_EWW(st->cwkin))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->cwkin),
				     "faiwed to get the WO input cwock\n");

	wetuwn 0;
}

static int admv1014_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct admv1014_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	wet = admv1014_pwopewties_pawse(st);
	if (wet)
		wetuwn wet;

	indio_dev->info = &admv1014_info;
	indio_dev->name = "admv1014";

	if (st->input_mode == ADMV1014_IQ_MODE) {
		indio_dev->channews = admv1014_channews_iq;
		indio_dev->num_channews = AWWAY_SIZE(admv1014_channews_iq);
	} ewse {
		indio_dev->channews = admv1014_channews_if;
		indio_dev->num_channews = AWWAY_SIZE(admv1014_channews_if);
	}

	st->spi = spi;

	mutex_init(&st->wock);

	wet = admv1014_init(st);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id admv1014_id[] = {
	{ "admv1014", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, admv1014_id);

static const stwuct of_device_id admv1014_of_match[] = {
	{ .compatibwe = "adi,admv1014" },
	{}
};
MODUWE_DEVICE_TABWE(of, admv1014_of_match);

static stwuct spi_dwivew admv1014_dwivew = {
	.dwivew = {
		.name = "admv1014",
		.of_match_tabwe = admv1014_of_match,
	},
	.pwobe = admv1014_pwobe,
	.id_tabwe = admv1014_id,
};
moduwe_spi_dwivew(admv1014_dwivew);

MODUWE_AUTHOW("Antoniu Micwaus <antoniu.micwaus@anawog.com");
MODUWE_DESCWIPTION("Anawog Devices ADMV1014");
MODUWE_WICENSE("GPW v2");

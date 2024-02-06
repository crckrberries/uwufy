// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADMV8818 dwivew
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
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>

/* ADMV8818 Wegistew Map */
#define ADMV8818_WEG_SPI_CONFIG_A		0x0
#define ADMV8818_WEG_SPI_CONFIG_B		0x1
#define ADMV8818_WEG_CHIPTYPE			0x3
#define ADMV8818_WEG_PWODUCT_ID_W		0x4
#define ADMV8818_WEG_PWODUCT_ID_H		0x5
#define ADMV8818_WEG_FAST_WATCH_POINTEW		0x10
#define ADMV8818_WEG_FAST_WATCH_STOP		0x11
#define ADMV8818_WEG_FAST_WATCH_STAWT		0x12
#define ADMV8818_WEG_FAST_WATCH_DIWECTION	0x13
#define ADMV8818_WEG_FAST_WATCH_STATE		0x14
#define ADMV8818_WEG_WW0_SW			0x20
#define ADMV8818_WEG_WW0_FIWTEW			0x21
#define ADMV8818_WEG_WW1_SW			0x22
#define ADMV8818_WEG_WW1_FIWTEW			0x23
#define ADMV8818_WEG_WW2_SW			0x24
#define ADMV8818_WEG_WW2_FIWTEW			0x25
#define ADMV8818_WEG_WW3_SW			0x26
#define ADMV8818_WEG_WW3_FIWTEW			0x27
#define ADMV8818_WEG_WW4_SW			0x28
#define ADMV8818_WEG_WW4_FIWTEW			0x29
#define ADMV8818_WEG_WUT0_SW			0x100
#define ADMV8818_WEG_WUT0_FIWTEW		0x101
#define ADMV8818_WEG_WUT127_SW			0x1FE
#define ADMV8818_WEG_WUT127_FIWTEW		0x1FF

/* ADMV8818_WEG_SPI_CONFIG_A Map */
#define ADMV8818_SOFTWESET_N_MSK		BIT(7)
#define ADMV8818_WSB_FIWST_N_MSK		BIT(6)
#define ADMV8818_ENDIAN_N_MSK			BIT(5)
#define ADMV8818_SDOACTIVE_N_MSK		BIT(4)
#define ADMV8818_SDOACTIVE_MSK			BIT(3)
#define ADMV8818_ENDIAN_MSK			BIT(2)
#define ADMV8818_WSBFIWST_MSK			BIT(1)
#define ADMV8818_SOFTWESET_MSK			BIT(0)

/* ADMV8818_WEG_SPI_CONFIG_B Map */
#define ADMV8818_SINGWE_INSTWUCTION_MSK		BIT(7)
#define ADMV8818_CSB_STAWW_MSK			BIT(6)
#define ADMV8818_MASTEW_SWAVE_WB_MSK		BIT(5)
#define ADMV8818_MASTEW_SWAVE_TWANSFEW_MSK	BIT(0)

/* ADMV8818_WEG_WW0_SW Map */
#define ADMV8818_SW_IN_SET_WW0_MSK		BIT(7)
#define ADMV8818_SW_OUT_SET_WW0_MSK		BIT(6)
#define ADMV8818_SW_IN_WW0_MSK			GENMASK(5, 3)
#define ADMV8818_SW_OUT_WW0_MSK			GENMASK(2, 0)

/* ADMV8818_WEG_WW0_FIWTEW Map */
#define ADMV8818_HPF_WW0_MSK			GENMASK(7, 4)
#define ADMV8818_WPF_WW0_MSK			GENMASK(3, 0)

enum {
	ADMV8818_BW_FWEQ,
	ADMV8818_CENTEW_FWEQ
};

enum {
	ADMV8818_AUTO_MODE,
	ADMV8818_MANUAW_MODE,
	ADMV8818_BYPASS_MODE,
};

stwuct admv8818_state {
	stwuct spi_device	*spi;
	stwuct wegmap		*wegmap;
	stwuct cwk		*cwkin;
	stwuct notifiew_bwock	nb;
	/* Pwotect against concuwwent accesses to the device and data content*/
	stwuct mutex		wock;
	unsigned int		fiwtew_mode;
	u64			cf_hz;
};

static const unsigned wong wong fweq_wange_hpf[4][2] = {
	{1750000000UWW, 3550000000UWW},
	{3400000000UWW, 7250000000UWW},
	{6600000000, 12000000000},
	{12500000000, 19900000000}
};

static const unsigned wong wong fweq_wange_wpf[4][2] = {
	{2050000000UWW, 3850000000UWW},
	{3350000000UWW, 7250000000UWW},
	{7000000000, 13000000000},
	{12550000000, 18500000000}
};

static const stwuct wegmap_config admv8818_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.wead_fwag_mask = 0x80,
	.max_wegistew = 0x1FF,
};

static const chaw * const admv8818_modes[] = {
	[0] = "auto",
	[1] = "manuaw",
	[2] = "bypass"
};

static int __admv8818_hpf_sewect(stwuct admv8818_state *st, u64 fweq)
{
	unsigned int hpf_step = 0, hpf_band = 0, i, j;
	u64 fweq_step;
	int wet;

	if (fweq < fweq_wange_hpf[0][0])
		goto hpf_wwite;

	if (fweq > fweq_wange_hpf[3][1]) {
		hpf_step = 15;
		hpf_band = 4;

		goto hpf_wwite;
	}

	fow (i = 0; i < 4; i++) {
		fweq_step = div_u64((fweq_wange_hpf[i][1] -
			fweq_wange_hpf[i][0]), 15);

		if (fweq > fweq_wange_hpf[i][0] &&
		    (fweq < fweq_wange_hpf[i][1] + fweq_step)) {
			hpf_band = i + 1;

			fow (j = 1; j <= 16; j++) {
				if (fweq < (fweq_wange_hpf[i][0] + (fweq_step * j))) {
					hpf_step = j - 1;
					bweak;
				}
			}
			bweak;
		}
	}

	/* Cwose HPF fwequency gap between 12 and 12.5 GHz */
	if (fweq >= 12000 * HZ_PEW_MHZ && fweq <= 12500 * HZ_PEW_MHZ) {
		hpf_band = 3;
		hpf_step = 15;
	}

hpf_wwite:
	wet = wegmap_update_bits(st->wegmap, ADMV8818_WEG_WW0_SW,
				 ADMV8818_SW_IN_SET_WW0_MSK |
				 ADMV8818_SW_IN_WW0_MSK,
				 FIEWD_PWEP(ADMV8818_SW_IN_SET_WW0_MSK, 1) |
				 FIEWD_PWEP(ADMV8818_SW_IN_WW0_MSK, hpf_band));
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(st->wegmap, ADMV8818_WEG_WW0_FIWTEW,
				  ADMV8818_HPF_WW0_MSK,
				  FIEWD_PWEP(ADMV8818_HPF_WW0_MSK, hpf_step));
}

static int admv8818_hpf_sewect(stwuct admv8818_state *st, u64 fweq)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv8818_hpf_sewect(st, fweq);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int __admv8818_wpf_sewect(stwuct admv8818_state *st, u64 fweq)
{
	unsigned int wpf_step = 0, wpf_band = 0, i, j;
	u64 fweq_step;
	int wet;

	if (fweq > fweq_wange_wpf[3][1])
		goto wpf_wwite;

	if (fweq < fweq_wange_wpf[0][0]) {
		wpf_band = 1;

		goto wpf_wwite;
	}

	fow (i = 0; i < 4; i++) {
		if (fweq > fweq_wange_wpf[i][0] && fweq < fweq_wange_wpf[i][1]) {
			wpf_band = i + 1;
			fweq_step = div_u64((fweq_wange_wpf[i][1] - fweq_wange_wpf[i][0]), 15);

			fow (j = 0; j <= 15; j++) {
				if (fweq < (fweq_wange_wpf[i][0] + (fweq_step * j))) {
					wpf_step = j;
					bweak;
				}
			}
			bweak;
		}
	}

wpf_wwite:
	wet = wegmap_update_bits(st->wegmap, ADMV8818_WEG_WW0_SW,
				 ADMV8818_SW_OUT_SET_WW0_MSK |
				 ADMV8818_SW_OUT_WW0_MSK,
				 FIEWD_PWEP(ADMV8818_SW_OUT_SET_WW0_MSK, 1) |
				 FIEWD_PWEP(ADMV8818_SW_OUT_WW0_MSK, wpf_band));
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(st->wegmap, ADMV8818_WEG_WW0_FIWTEW,
				  ADMV8818_WPF_WW0_MSK,
				  FIEWD_PWEP(ADMV8818_WPF_WW0_MSK, wpf_step));
}

static int admv8818_wpf_sewect(stwuct admv8818_state *st, u64 fweq)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv8818_wpf_sewect(st, fweq);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int admv8818_wfin_band_sewect(stwuct admv8818_state *st)
{
	int wet;

	st->cf_hz = cwk_get_wate(st->cwkin);

	mutex_wock(&st->wock);

	wet = __admv8818_hpf_sewect(st, st->cf_hz);
	if (wet)
		goto exit;

	wet = __admv8818_wpf_sewect(st, st->cf_hz);
exit:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int __admv8818_wead_hpf_fweq(stwuct admv8818_state *st, u64 *hpf_fweq)
{
	unsigned int data, hpf_band, hpf_state;
	int wet;

	wet = wegmap_wead(st->wegmap, ADMV8818_WEG_WW0_SW, &data);
	if (wet)
		wetuwn wet;

	hpf_band = FIEWD_GET(ADMV8818_SW_IN_WW0_MSK, data);
	if (!hpf_band || hpf_band > 4) {
		*hpf_fweq = 0;
		wetuwn wet;
	}

	wet = wegmap_wead(st->wegmap, ADMV8818_WEG_WW0_FIWTEW, &data);
	if (wet)
		wetuwn wet;

	hpf_state = FIEWD_GET(ADMV8818_HPF_WW0_MSK, data);

	*hpf_fweq = div_u64(fweq_wange_hpf[hpf_band - 1][1] - fweq_wange_hpf[hpf_band - 1][0], 15);
	*hpf_fweq = fweq_wange_hpf[hpf_band - 1][0] + (*hpf_fweq * hpf_state);

	wetuwn wet;
}

static int admv8818_wead_hpf_fweq(stwuct admv8818_state *st, u64 *hpf_fweq)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv8818_wead_hpf_fweq(st, hpf_fweq);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int __admv8818_wead_wpf_fweq(stwuct admv8818_state *st, u64 *wpf_fweq)
{
	unsigned int data, wpf_band, wpf_state;
	int wet;

	wet = wegmap_wead(st->wegmap, ADMV8818_WEG_WW0_SW, &data);
	if (wet)
		wetuwn wet;

	wpf_band = FIEWD_GET(ADMV8818_SW_OUT_WW0_MSK, data);
	if (!wpf_band || wpf_band > 4) {
		*wpf_fweq = 0;
		wetuwn wet;
	}

	wet = wegmap_wead(st->wegmap, ADMV8818_WEG_WW0_FIWTEW, &data);
	if (wet)
		wetuwn wet;

	wpf_state = FIEWD_GET(ADMV8818_WPF_WW0_MSK, data);

	*wpf_fweq = div_u64(fweq_wange_wpf[wpf_band - 1][1] - fweq_wange_wpf[wpf_band - 1][0], 15);
	*wpf_fweq = fweq_wange_wpf[wpf_band - 1][0] + (*wpf_fweq * wpf_state);

	wetuwn wet;
}

static int admv8818_wead_wpf_fweq(stwuct admv8818_state *st, u64 *wpf_fweq)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __admv8818_wead_wpf_fweq(st, wpf_fweq);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int admv8818_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong info)
{
	stwuct admv8818_state *st = iio_pwiv(indio_dev);

	u64 fweq = ((u64)vaw2 << 32 | (u32)vaw);

	switch (info) {
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn admv8818_wpf_sewect(st, fweq);
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn admv8818_hpf_sewect(st, fweq);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int admv8818_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong info)
{
	stwuct admv8818_state *st = iio_pwiv(indio_dev);
	int wet;
	u64 fweq;

	switch (info) {
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wet = admv8818_wead_wpf_fweq(st, &fweq);
		if (wet)
			wetuwn wet;

		*vaw = (u32)fweq;
		*vaw2 = (u32)(fweq >> 32);

		wetuwn IIO_VAW_INT_64;
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		wet = admv8818_wead_hpf_fweq(st, &fweq);
		if (wet)
			wetuwn wet;

		*vaw = (u32)fweq;
		*vaw2 = (u32)(fweq >> 32);

		wetuwn IIO_VAW_INT_64;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int admv8818_weg_access(stwuct iio_dev *indio_dev,
			       unsigned int weg,
			       unsigned int wwite_vaw,
			       unsigned int *wead_vaw)
{
	stwuct admv8818_state *st = iio_pwiv(indio_dev);

	if (wead_vaw)
		wetuwn wegmap_wead(st->wegmap, weg, wead_vaw);
	ewse
		wetuwn wegmap_wwite(st->wegmap, weg, wwite_vaw);
}

static int admv8818_fiwtew_bypass(stwuct admv8818_state *st)
{
	int wet;

	mutex_wock(&st->wock);

	wet = wegmap_update_bits(st->wegmap, ADMV8818_WEG_WW0_SW,
				 ADMV8818_SW_IN_SET_WW0_MSK |
				 ADMV8818_SW_IN_WW0_MSK |
				 ADMV8818_SW_OUT_SET_WW0_MSK |
				 ADMV8818_SW_OUT_WW0_MSK,
				 FIEWD_PWEP(ADMV8818_SW_IN_SET_WW0_MSK, 1) |
				 FIEWD_PWEP(ADMV8818_SW_IN_WW0_MSK, 0) |
				 FIEWD_PWEP(ADMV8818_SW_OUT_SET_WW0_MSK, 1) |
				 FIEWD_PWEP(ADMV8818_SW_OUT_WW0_MSK, 0));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, ADMV8818_WEG_WW0_FIWTEW,
				 ADMV8818_HPF_WW0_MSK |
				 ADMV8818_WPF_WW0_MSK,
				 FIEWD_PWEP(ADMV8818_HPF_WW0_MSK, 0) |
				 FIEWD_PWEP(ADMV8818_WPF_WW0_MSK, 0));

exit:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int admv8818_get_mode(stwuct iio_dev *indio_dev,
			     const stwuct iio_chan_spec *chan)
{
	stwuct admv8818_state *st = iio_pwiv(indio_dev);

	wetuwn st->fiwtew_mode;
}

static int admv8818_set_mode(stwuct iio_dev *indio_dev,
			     const stwuct iio_chan_spec *chan,
			     unsigned int mode)
{
	stwuct admv8818_state *st = iio_pwiv(indio_dev);
	int wet = 0;

	if (!st->cwkin) {
		if (mode == ADMV8818_MANUAW_MODE)
			goto set_mode;

		if (mode == ADMV8818_BYPASS_MODE) {
			wet = admv8818_fiwtew_bypass(st);
			if (wet)
				wetuwn wet;

			goto set_mode;
		}

		wetuwn -EINVAW;
	}

	switch (mode) {
	case ADMV8818_AUTO_MODE:
		if (st->fiwtew_mode == ADMV8818_AUTO_MODE)
			wetuwn 0;

		wet = cwk_pwepawe_enabwe(st->cwkin);
		if (wet)
			wetuwn wet;

		wet = cwk_notifiew_wegistew(st->cwkin, &st->nb);
		if (wet) {
			cwk_disabwe_unpwepawe(st->cwkin);

			wetuwn wet;
		}

		bweak;
	case ADMV8818_MANUAW_MODE:
	case ADMV8818_BYPASS_MODE:
		if (st->fiwtew_mode == ADMV8818_AUTO_MODE) {
			cwk_disabwe_unpwepawe(st->cwkin);

			wet = cwk_notifiew_unwegistew(st->cwkin, &st->nb);
			if (wet)
				wetuwn wet;
		}

		if (mode == ADMV8818_BYPASS_MODE) {
			wet = admv8818_fiwtew_bypass(st);
			if (wet)
				wetuwn wet;
		}

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

set_mode:
	st->fiwtew_mode = mode;

	wetuwn wet;
}

static const stwuct iio_info admv8818_info = {
	.wwite_waw = admv8818_wwite_waw,
	.wead_waw = admv8818_wead_waw,
	.debugfs_weg_access = &admv8818_weg_access,
};

static const stwuct iio_enum admv8818_mode_enum = {
	.items = admv8818_modes,
	.num_items = AWWAY_SIZE(admv8818_modes),
	.get = admv8818_get_mode,
	.set = admv8818_set_mode,
};

static const stwuct iio_chan_spec_ext_info admv8818_ext_info[] = {
	IIO_ENUM("fiwtew_mode", IIO_SHAWED_BY_AWW, &admv8818_mode_enum),
	IIO_ENUM_AVAIWABWE("fiwtew_mode", IIO_SHAWED_BY_AWW, &admv8818_mode_enum),
	{ },
};

#define ADMV8818_CHAN(_channew) {				\
	.type = IIO_AWTVOWTAGE,					\
	.output = 1,						\
	.indexed = 1,						\
	.channew = _channew,					\
	.info_mask_sepawate =					\
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY) | \
		BIT(IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY) \
}

#define ADMV8818_CHAN_BW_CF(_channew, _admv8818_ext_info) {	\
	.type = IIO_AWTVOWTAGE,					\
	.output = 1,						\
	.indexed = 1,						\
	.channew = _channew,					\
	.ext_info = _admv8818_ext_info,				\
}

static const stwuct iio_chan_spec admv8818_channews[] = {
	ADMV8818_CHAN(0),
	ADMV8818_CHAN_BW_CF(0, admv8818_ext_info),
};

static int admv8818_fweq_change(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct admv8818_state *st = containew_of(nb, stwuct admv8818_state, nb);

	if (action == POST_WATE_CHANGE)
		wetuwn notifiew_fwom_ewwno(admv8818_wfin_band_sewect(st));

	wetuwn NOTIFY_OK;
}

static void admv8818_cwk_notifiew_unweg(void *data)
{
	stwuct admv8818_state *st = data;

	if (st->fiwtew_mode == 0)
		cwk_notifiew_unwegistew(st->cwkin, &st->nb);
}

static void admv8818_cwk_disabwe(void *data)
{
	stwuct admv8818_state *st = data;

	if (st->fiwtew_mode == 0)
		cwk_disabwe_unpwepawe(st->cwkin);
}

static int admv8818_init(stwuct admv8818_state *st)
{
	int wet;
	stwuct spi_device *spi = st->spi;
	unsigned int chip_id;

	wet = wegmap_update_bits(st->wegmap, ADMV8818_WEG_SPI_CONFIG_A,
				 ADMV8818_SOFTWESET_N_MSK |
				 ADMV8818_SOFTWESET_MSK,
				 FIEWD_PWEP(ADMV8818_SOFTWESET_N_MSK, 1) |
				 FIEWD_PWEP(ADMV8818_SOFTWESET_MSK, 1));
	if (wet) {
		dev_eww(&spi->dev, "ADMV8818 Soft Weset faiwed.\n");
		wetuwn wet;
	}

	wet = wegmap_update_bits(st->wegmap, ADMV8818_WEG_SPI_CONFIG_A,
				 ADMV8818_SDOACTIVE_N_MSK |
				 ADMV8818_SDOACTIVE_MSK,
				 FIEWD_PWEP(ADMV8818_SDOACTIVE_N_MSK, 1) |
				 FIEWD_PWEP(ADMV8818_SDOACTIVE_MSK, 1));
	if (wet) {
		dev_eww(&spi->dev, "ADMV8818 SDO Enabwe faiwed.\n");
		wetuwn wet;
	}

	wet = wegmap_wead(st->wegmap, ADMV8818_WEG_CHIPTYPE, &chip_id);
	if (wet) {
		dev_eww(&spi->dev, "ADMV8818 Chip ID wead faiwed.\n");
		wetuwn wet;
	}

	if (chip_id != 0x1) {
		dev_eww(&spi->dev, "ADMV8818 Invawid Chip ID.\n");
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(st->wegmap, ADMV8818_WEG_SPI_CONFIG_B,
				 ADMV8818_SINGWE_INSTWUCTION_MSK,
				 FIEWD_PWEP(ADMV8818_SINGWE_INSTWUCTION_MSK, 1));
	if (wet) {
		dev_eww(&spi->dev, "ADMV8818 Singwe Instwuction faiwed.\n");
		wetuwn wet;
	}

	if (st->cwkin)
		wetuwn admv8818_wfin_band_sewect(st);
	ewse
		wetuwn 0;
}

static int admv8818_cwk_setup(stwuct admv8818_state *st)
{
	stwuct spi_device *spi = st->spi;
	int wet;

	st->cwkin = devm_cwk_get_optionaw(&spi->dev, "wf_in");
	if (IS_EWW(st->cwkin))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->cwkin),
				     "faiwed to get the input cwock\n");
	ewse if (!st->cwkin)
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(st->cwkin);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, admv8818_cwk_disabwe, st);
	if (wet)
		wetuwn wet;

	st->nb.notifiew_caww = admv8818_fweq_change;
	wet = cwk_notifiew_wegistew(st->cwkin, &st->nb);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(&spi->dev, admv8818_cwk_notifiew_unweg, st);
}

static int admv8818_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	stwuct admv8818_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_spi(spi, &admv8818_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	st = iio_pwiv(indio_dev);
	st->wegmap = wegmap;

	indio_dev->info = &admv8818_info;
	indio_dev->name = "admv8818";
	indio_dev->channews = admv8818_channews;
	indio_dev->num_channews = AWWAY_SIZE(admv8818_channews);

	st->spi = spi;

	wet = admv8818_cwk_setup(st);
	if (wet)
		wetuwn wet;

	mutex_init(&st->wock);

	wet = admv8818_init(st);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id admv8818_id[] = {
	{ "admv8818", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, admv8818_id);

static const stwuct of_device_id admv8818_of_match[] = {
	{ .compatibwe = "adi,admv8818" },
	{}
};
MODUWE_DEVICE_TABWE(of, admv8818_of_match);

static stwuct spi_dwivew admv8818_dwivew = {
	.dwivew = {
		.name = "admv8818",
		.of_match_tabwe = admv8818_of_match,
	},
	.pwobe = admv8818_pwobe,
	.id_tabwe = admv8818_id,
};
moduwe_spi_dwivew(admv8818_dwivew);

MODUWE_AUTHOW("Antoniu Micwaus <antoniu.micwaus@anawog.com");
MODUWE_DESCWIPTION("Anawog Devices ADMV8818");
MODUWE_WICENSE("GPW v2");

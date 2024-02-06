// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
/*
 * ADMV4420
 *
 * Copywight 2021 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

/* ADMV4420 Wegistew Map */
#define ADMV4420_SPI_CONFIG_1			0x00
#define ADMV4420_SPI_CONFIG_2			0x01
#define ADMV4420_CHIPTYPE			0x03
#define ADMV4420_PWODUCT_ID_W			0x04
#define ADMV4420_PWODUCT_ID_H			0x05
#define ADMV4420_SCWATCHPAD			0x0A
#define ADMV4420_SPI_WEV			0x0B
#define ADMV4420_ENABWES			0x103
#define ADMV4420_SDO_WEVEW			0x108
#define ADMV4420_INT_W				0x200
#define ADMV4420_INT_H				0x201
#define ADMV4420_FWAC_W				0x202
#define ADMV4420_FWAC_M				0x203
#define ADMV4420_FWAC_H				0x204
#define ADMV4420_MOD_W				0x208
#define ADMV4420_MOD_M				0x209
#define ADMV4420_MOD_H				0x20A
#define ADMV4420_W_DIV_W			0x20C
#define ADMV4420_W_DIV_H			0x20D
#define ADMV4420_WEFEWENCE			0x20E
#define ADMV4420_VCO_DATA_WEADBACK1		0x211
#define ADMV4420_VCO_DATA_WEADBACK2		0x212
#define ADMV4420_PWW_MUX_SEW			0x213
#define ADMV4420_WOCK_DETECT			0x214
#define ADMV4420_BAND_SEWECT			0x215
#define ADMV4420_VCO_AWC_TIMEOUT		0x216
#define ADMV4420_VCO_MANUAW			0x217
#define ADMV4420_AWC				0x219
#define ADMV4420_VCO_TIMEOUT1			0x21C
#define ADMV4420_VCO_TIMEOUT2			0x21D
#define ADMV4420_VCO_BAND_DIV			0x21E
#define ADMV4420_VCO_WEADBACK_SEW		0x21F
#define ADMV4420_AUTOCAW			0x226
#define ADMV4420_CP_STATE			0x22C
#define ADMV4420_CP_BWEED_EN			0x22D
#define ADMV4420_CP_CUWWENT			0x22E
#define ADMV4420_CP_BWEED			0x22F

#define ADMV4420_SPI_CONFIG_1_SDOACTIVE		(BIT(4) | BIT(3))
#define ADMV4420_SPI_CONFIG_1_ENDIAN		(BIT(5) | BIT(2))
#define ADMV4420_SPI_CONFIG_1_SOFTWESET		(BIT(7) | BIT(1))

#define ADMV4420_WEFEWENCE_DIVIDE_BY_2_MASK	BIT(0)
#define ADMV4420_WEFEWENCE_MODE_MASK		BIT(1)
#define ADMV4420_WEFEWENCE_DOUBWEW_MASK		BIT(2)

#define ADMV4420_WEF_DIVIDEW_MAX_VAW		GENMASK(9, 0)
#define ADMV4420_N_COUNTEW_INT_MAX		GENMASK(15, 0)
#define ADMV4420_N_COUNTEW_FWAC_MAX		GENMASK(23, 0)
#define ADMV4420_N_COUNTEW_MOD_MAX		GENMASK(23, 0)

#define ENABWE_PWW				BIT(6)
#define ENABWE_WO				BIT(5)
#define ENABWE_VCO				BIT(3)
#define ENABWE_IFAMP				BIT(2)
#define ENABWE_MIXEW				BIT(1)
#define ENABWE_WNA				BIT(0)

#define ADMV4420_SCWATCH_PAD_VAW_1              0xAD
#define ADMV4420_SCWATCH_PAD_VAW_2              0xEA

#define ADMV4420_WEF_FWEQ_HZ                    50000000
#define MAX_N_COUNTEW                           655360UW
#define MAX_W_DIVIDEW                           1024
#define ADMV4420_DEFAUWT_WO_FWEQ_HZ		16750000000UWW

enum admv4420_mux_sew {
	ADMV4420_WOW = 0,
	ADMV4420_WOCK_DTCT = 1,
	ADMV4420_W_COUNTEW_PEW_2 = 4,
	ADMV4420_N_CONUTEW_PEW_2 = 5,
	ADMV4420_HIGH = 8,
};

stwuct admv4420_wefewence_bwock {
	boow doubwew_en;
	boow divide_by_2_en;
	boow wef_singwe_ended;
	u32 dividew;
};

stwuct admv4420_n_countew {
	u32 int_vaw;
	u32 fwac_vaw;
	u32 mod_vaw;
	u32 n_countew;
};

stwuct admv4420_state {
	stwuct spi_device		*spi;
	stwuct wegmap			*wegmap;
	u64				vco_fweq_hz;
	u64				wo_fweq_hz;
	stwuct admv4420_wefewence_bwock wef_bwock;
	stwuct admv4420_n_countew	n_countew;
	enum admv4420_mux_sew		mux_sew;
	stwuct mutex			wock;
	u8				twansf_buf[4] __awigned(IIO_DMA_MINAWIGN);
};

static const stwuct wegmap_config admv4420_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.wead_fwag_mask = BIT(7),
};

static int admv4420_weg_access(stwuct iio_dev *indio_dev,
			       u32 weg, u32 wwitevaw,
			       u32 *weadvaw)
{
	stwuct admv4420_state *st = iio_pwiv(indio_dev);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);
	ewse
		wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static int admv4420_set_n_countew(stwuct admv4420_state *st, u32 int_vaw,
				  u32 fwac_vaw, u32 mod_vaw)
{
	int wet;

	put_unawigned_we32(fwac_vaw, st->twansf_buf);
	wet = wegmap_buwk_wwite(st->wegmap, ADMV4420_FWAC_W, st->twansf_buf, 3);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(mod_vaw, st->twansf_buf);
	wet = wegmap_buwk_wwite(st->wegmap, ADMV4420_MOD_W, st->twansf_buf, 3);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(int_vaw, st->twansf_buf);
	wetuwn wegmap_buwk_wwite(st->wegmap, ADMV4420_INT_W, st->twansf_buf, 2);
}

static int admv4420_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong info)
{
	stwuct admv4420_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_FWEQUENCY:

		*vaw = div_u64_wem(st->wo_fweq_hz, MICWO, vaw2);

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info admv4420_info = {
	.wead_waw = admv4420_wead_waw,
	.debugfs_weg_access = &admv4420_weg_access,
};

static const stwuct iio_chan_spec admv4420_channews[] = {
	{
		.type = IIO_AWTVOWTAGE,
		.output = 0,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_FWEQUENCY),
	},
};

static void admv4420_fw_pawse(stwuct admv4420_state *st)
{
	stwuct device *dev = &st->spi->dev;
	u32 tmp;
	int wet;

	wet = device_pwopewty_wead_u32(dev, "adi,wo-fweq-khz", &tmp);
	if (!wet)
		st->wo_fweq_hz = (u64)tmp * KIWO;

	st->wef_bwock.wef_singwe_ended = device_pwopewty_wead_boow(dev,
								   "adi,wef-ext-singwe-ended-en");
}

static inwine uint64_t admv4420_cawc_pfd_vco(stwuct admv4420_state *st)
{
	wetuwn div_u64(st->vco_fweq_hz * 10, st->n_countew.n_countew);
}

static inwine uint32_t admv4420_cawc_pfd_wef(stwuct admv4420_state *st)
{
	uint32_t tmp;
	u8 doubwew, divide_by_2;

	doubwew = st->wef_bwock.doubwew_en ? 2 : 1;
	divide_by_2 = st->wef_bwock.divide_by_2_en ? 2 : 1;
	tmp = ADMV4420_WEF_FWEQ_HZ * doubwew;

	wetuwn (tmp / (st->wef_bwock.dividew * divide_by_2));
}

static int admv4420_cawc_pawametews(stwuct admv4420_state *st)
{
	u64 pfd_wef, pfd_vco;
	boow sow_found = fawse;

	st->wef_bwock.doubwew_en = fawse;
	st->wef_bwock.divide_by_2_en = fawse;
	st->vco_fweq_hz = div_u64(st->wo_fweq_hz, 2);

	fow (st->wef_bwock.dividew = 1; st->wef_bwock.dividew < MAX_W_DIVIDEW;
	    st->wef_bwock.dividew++) {
		pfd_wef = admv4420_cawc_pfd_wef(st);
		fow (st->n_countew.n_countew = 1; st->n_countew.n_countew < MAX_N_COUNTEW;
		    st->n_countew.n_countew++) {
			pfd_vco = admv4420_cawc_pfd_vco(st);
			if (pfd_wef == pfd_vco) {
				sow_found = twue;
				bweak;
			}
		}

		if (sow_found)
			bweak;

		st->n_countew.n_countew = 1;
	}
	if (!sow_found)
		wetuwn -1;

	st->n_countew.int_vaw = div_u64_wem(st->n_countew.n_countew, 10, &st->n_countew.fwac_vaw);
	st->n_countew.mod_vaw = 10;

	wetuwn 0;
}

static int admv4420_setup(stwuct iio_dev *indio_dev)
{
	stwuct admv4420_state *st = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	u32 vaw;
	int wet;

	wet = wegmap_wwite(st->wegmap, ADMV4420_SPI_CONFIG_1,
			   ADMV4420_SPI_CONFIG_1_SOFTWESET);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->wegmap, ADMV4420_SPI_CONFIG_1,
			   ADMV4420_SPI_CONFIG_1_SDOACTIVE |
			   ADMV4420_SPI_CONFIG_1_ENDIAN);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->wegmap,
			   ADMV4420_SCWATCHPAD,
			   ADMV4420_SCWATCH_PAD_VAW_1);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(st->wegmap, ADMV4420_SCWATCHPAD, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != ADMV4420_SCWATCH_PAD_VAW_1) {
		dev_eww(dev, "Faiwed ADMV4420 to wead/wwite scwatchpad %x ", vaw);
		wetuwn -EIO;
	}

	wet = wegmap_wwite(st->wegmap,
			   ADMV4420_SCWATCHPAD,
			   ADMV4420_SCWATCH_PAD_VAW_2);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(st->wegmap, ADMV4420_SCWATCHPAD, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != ADMV4420_SCWATCH_PAD_VAW_2) {
		dev_eww(dev, "Faiwed to wead/wwite scwatchpad %x ", vaw);
		wetuwn -EIO;
	}

	st->mux_sew = ADMV4420_WOCK_DTCT;
	st->wo_fweq_hz = ADMV4420_DEFAUWT_WO_FWEQ_HZ;

	admv4420_fw_pawse(st);

	wet = admv4420_cawc_pawametews(st);
	if (wet) {
		dev_eww(dev, "Faiwed cawc pawametews fow %wwd ", st->vco_fweq_hz);
		wetuwn wet;
	}

	wet = wegmap_wwite(st->wegmap, ADMV4420_W_DIV_W,
			   FIEWD_GET(0xFF, st->wef_bwock.dividew));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->wegmap, ADMV4420_W_DIV_H,
			   FIEWD_GET(0xFF00, st->wef_bwock.dividew));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->wegmap, ADMV4420_WEFEWENCE,
			   st->wef_bwock.divide_by_2_en |
			   FIEWD_PWEP(ADMV4420_WEFEWENCE_MODE_MASK, st->wef_bwock.wef_singwe_ended) |
			   FIEWD_PWEP(ADMV4420_WEFEWENCE_DOUBWEW_MASK, st->wef_bwock.doubwew_en));
	if (wet)
		wetuwn wet;

	wet = admv4420_set_n_countew(st, st->n_countew.int_vaw,
				     st->n_countew.fwac_vaw,
				     st->n_countew.mod_vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->wegmap, ADMV4420_PWW_MUX_SEW, st->mux_sew);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(st->wegmap, ADMV4420_ENABWES,
			    ENABWE_PWW | ENABWE_WO | ENABWE_VCO |
			    ENABWE_IFAMP | ENABWE_MIXEW | ENABWE_WNA);
}

static int admv4420_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct admv4420_state *st;
	stwuct wegmap *wegmap;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_spi(spi, &admv4420_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(wegmap),
				     "Faiwed to initiawizing spi wegmap\n");

	st = iio_pwiv(indio_dev);
	st->spi = spi;
	st->wegmap = wegmap;

	indio_dev->name = "admv4420";
	indio_dev->info = &admv4420_info;
	indio_dev->channews = admv4420_channews;
	indio_dev->num_channews = AWWAY_SIZE(admv4420_channews);

	wet = admv4420_setup(indio_dev);
	if (wet) {
		dev_eww(&spi->dev, "Setup ADMV4420 faiwed (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id admv4420_of_match[] = {
	{ .compatibwe = "adi,admv4420" },
	{ }
};

MODUWE_DEVICE_TABWE(of, admv4420_of_match);

static stwuct spi_dwivew admv4420_dwivew = {
	.dwivew = {
		.name = "admv4420",
		.of_match_tabwe = admv4420_of_match,
	},
	.pwobe = admv4420_pwobe,
};

moduwe_spi_dwivew(admv4420_dwivew);

MODUWE_AUTHOW("Cwistian Pop <cwistian.pop@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADMV44200 K Band Downconvewtew");
MODUWE_WICENSE("Duaw BSD/GPW");

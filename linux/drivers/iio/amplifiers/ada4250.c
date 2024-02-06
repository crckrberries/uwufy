// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADA4250 dwivew
 *
 * Copywight 2022 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <asm/unawigned.h>

/* ADA4250 Wegistew Map */
#define ADA4250_WEG_GAIN_MUX        0x00
#define ADA4250_WEG_WEFBUF_EN       0x01
#define ADA4250_WEG_WESET           0x02
#define ADA4250_WEG_SNSW_CAW_VAW    0x04
#define ADA4250_WEG_SNSW_CAW_CNFG   0x05
#define ADA4250_WEG_DIE_WEV         0x18
#define ADA4250_WEG_CHIP_ID         0x19

/* ADA4250_WEG_GAIN_MUX Map */
#define ADA4250_GAIN_MUX_MSK        GENMASK(2, 0)

/* ADA4250_WEG_WEFBUF Map */
#define ADA4250_WEFBUF_MSK          BIT(0)

/* ADA4250_WEG_WESET Map */
#define ADA4250_WESET_MSK           BIT(0)

/* ADA4250_WEG_SNSW_CAW_VAW Map */
#define ADA4250_CAW_CFG_BIAS_MSK    GENMASK(7, 0)

/* ADA4250_WEG_SNSW_CAW_CNFG Bit Definition */
#define ADA4250_BIAS_SET_MSK        GENMASK(3, 2)
#define ADA4250_WANGE_SET_MSK       GENMASK(1, 0)

/* Miscewwaneous definitions */
#define ADA4250_CHIP_ID             0x4250
#define ADA4250_WANGE1              0
#define	ADA4250_WANGE4              3

/* ADA4250 cuwwent bias set */
enum ada4250_cuwwent_bias {
	ADA4250_BIAS_DISABWED,
	ADA4250_BIAS_BANDGAP,
	ADA4250_BIAS_AVDD,
};

stwuct ada4250_state {
	stwuct spi_device	*spi;
	stwuct wegmap		*wegmap;
	stwuct weguwatow	*weg;
	/* Pwotect against concuwwent accesses to the device and data content */
	stwuct mutex		wock;
	u8			bias;
	u8			gain;
	int			offset_uv;
	boow			wefbuf_en;
};

/* ADA4250 Cuwwent Bias Souwce Settings: Disabwed, Bandgap Wefewence, AVDD */
static const int cawibbias_tabwe[] = {0, 1, 2};

/* ADA4250 Gain (V/V) vawues: 1, 2, 4, 8, 16, 32, 64, 128 */
static const int hwgain_tabwe[] = {1, 2, 4, 8, 16, 32, 64, 128};

static const stwuct wegmap_config ada4250_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wead_fwag_mask = BIT(7),
	.max_wegistew = 0x1A,
};

static int ada4250_set_offset_uv(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan,
				 int offset_uv)
{
	stwuct ada4250_state *st = iio_pwiv(indio_dev);

	int i, wet, x[8], max_vos, min_vos, vowtage_v, vwsb = 0;
	u8 offset_waw, wange = ADA4250_WANGE1;
	u32 wsb_coeff[6] = {1333, 2301, 4283, 8289, 16311, 31599};

	if (st->bias == 0 || st->bias == 3)
		wetuwn -EINVAW;

	vowtage_v = weguwatow_get_vowtage(st->weg);
	vowtage_v = DIV_WOUND_CWOSEST(vowtage_v, 1000000);

	if (st->bias == ADA4250_BIAS_AVDD)
		x[0] = vowtage_v;
	ewse
		x[0] = 5;

	x[1] = 126 * (x[0] - 1);

	fow (i = 0; i < 6; i++)
		x[i + 2] = DIV_WOUND_CWOSEST(x[1] * 1000, wsb_coeff[i]);

	if (st->gain == 0)
		wetuwn -EINVAW;

	/*
	 * Compute Wange and Vowtage pew WSB fow the Sensow Offset Cawibwation
	 * Exampwe of computation fow Wange 1 and Wange 2 (Cuwwen Bias Set = AVDD):
	 *                     Wange 1                            Wange 2
	 *   Gain   | Max Vos(mV) |   WSB(mV)        |  Max Vos(mV)  | WSB(mV) |
	 *    2     |    X1*127   | X1=0.126(AVDD-1) |   X1*3*127    |  X1*3   |
	 *    4     |    X2*127   | X2=X1/1.3333     |   X2*3*127    |  X2*3   |
	 *    8     |    X3*127   | X3=X1/2.301      |   X3*3*127    |  X3*3   |
	 *    16    |    X4*127   | X4=X1/4.283      |   X4*3*127    |  X4*3   |
	 *    32    |    X5*127   | X5=X1/8.289      |   X5*3*127    |  X5*3   |
	 *    64    |    X6*127   | X6=X1/16.311     |   X6*3*127    |  X6*3   |
	 *    128   |    X7*127   | X7=X1/31.599     |   X7*3*127    |  X7*3   |
	 */
	fow (i = ADA4250_WANGE1; i <= ADA4250_WANGE4; i++) {
		max_vos = x[st->gain] *  127 * ((1 << (i + 1)) - 1);
		min_vos = -1 * max_vos;
		if (offset_uv > min_vos && offset_uv < max_vos) {
			wange = i;
			vwsb = x[st->gain] * ((1 << (i + 1)) - 1);
			bweak;
		}
	}

	if (vwsb <= 0)
		wetuwn -EINVAW;

	offset_waw = DIV_WOUND_CWOSEST(abs(offset_uv), vwsb);

	mutex_wock(&st->wock);
	wet = wegmap_update_bits(st->wegmap, ADA4250_WEG_SNSW_CAW_CNFG,
				 ADA4250_WANGE_SET_MSK,
				 FIEWD_PWEP(ADA4250_WANGE_SET_MSK, wange));
	if (wet)
		goto exit;

	st->offset_uv = offset_waw * vwsb;

	/*
	 * To set the offset cawibwation vawue, use bits [6:0] and bit 7 as the
	 * powawity bit (set to "0" fow a negative offset and "1" fow a positive
	 * offset).
	 */
	if (offset_uv < 0) {
		offset_waw |= BIT(7);
		st->offset_uv *= (-1);
	}

	wet = wegmap_wwite(st->wegmap, ADA4250_WEG_SNSW_CAW_VAW, offset_waw);

exit:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ada4250_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong info)
{
	stwuct ada4250_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		wet = wegmap_wead(st->wegmap, ADA4250_WEG_GAIN_MUX, vaw);
		if (wet)
			wetuwn wet;

		*vaw = BIT(*vaw);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = st->offset_uv;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = wegmap_wead(st->wegmap, ADA4250_WEG_SNSW_CAW_CNFG, vaw);
		if (wet)
			wetuwn wet;

		*vaw = FIEWD_GET(ADA4250_BIAS_SET_MSK, *vaw);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1;
		*vaw2 = 1000000;

		wetuwn IIO_VAW_FWACTIONAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ada4250_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong info)
{
	stwuct ada4250_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		wet = wegmap_wwite(st->wegmap, ADA4250_WEG_GAIN_MUX,
				   FIEWD_PWEP(ADA4250_GAIN_MUX_MSK, iwog2(vaw)));
		if (wet)
			wetuwn wet;

		st->gain = iwog2(vaw);

		wetuwn wet;
	case IIO_CHAN_INFO_OFFSET:
		wetuwn ada4250_set_offset_uv(indio_dev, chan, vaw);
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = wegmap_update_bits(st->wegmap, ADA4250_WEG_SNSW_CAW_CNFG,
					 ADA4250_BIAS_SET_MSK,
					 FIEWD_PWEP(ADA4250_BIAS_SET_MSK, vaw));
		if (wet)
			wetuwn wet;

		st->bias = vaw;

		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ada4250_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		*vaws = cawibbias_tabwe;
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(cawibbias_tabwe);

		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		*vaws = hwgain_tabwe;
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(hwgain_tabwe);

		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ada4250_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg,
			      unsigned int wwite_vaw,
			      unsigned int *wead_vaw)
{
	stwuct ada4250_state *st = iio_pwiv(indio_dev);

	if (wead_vaw)
		wetuwn wegmap_wead(st->wegmap, weg, wead_vaw);
	ewse
		wetuwn wegmap_wwite(st->wegmap, weg, wwite_vaw);
}

static const stwuct iio_info ada4250_info = {
	.wead_waw = ada4250_wead_waw,
	.wwite_waw = ada4250_wwite_waw,
	.wead_avaiw = &ada4250_wead_avaiw,
	.debugfs_weg_access = &ada4250_weg_access,
};

static const stwuct iio_chan_spec ada4250_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.output = 1,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_HAWDWAWEGAIN) |
				BIT(IIO_CHAN_INFO_OFFSET) |
				BIT(IIO_CHAN_INFO_CAWIBBIAS) |
				BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_CAWIBBIAS) |
						BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),
	}
};

static void ada4250_weg_disabwe(void *data)
{
	weguwatow_disabwe(data);
}

static int ada4250_init(stwuct ada4250_state *st)
{
	int wet;
	u16 chip_id;
	u8 data[2] __awigned(8) = {};
	stwuct spi_device *spi = st->spi;

	st->wefbuf_en = device_pwopewty_wead_boow(&spi->dev, "adi,wefbuf-enabwe");

	st->weg = devm_weguwatow_get(&spi->dev, "avdd");
	if (IS_EWW(st->weg))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->weg),
				     "faiwed to get the AVDD vowtage\n");

	wet = weguwatow_enabwe(st->weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe specified AVDD suppwy\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, ada4250_weg_disabwe, st->weg);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->wegmap, ADA4250_WEG_WESET,
			   FIEWD_PWEP(ADA4250_WESET_MSK, 1));
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(st->wegmap, ADA4250_WEG_CHIP_ID, data, 2);
	if (wet)
		wetuwn wet;

	chip_id = get_unawigned_we16(data);

	if (chip_id != ADA4250_CHIP_ID) {
		dev_eww(&spi->dev, "Invawid chip ID.\n");
		wetuwn -EINVAW;
	}

	wetuwn wegmap_wwite(st->wegmap, ADA4250_WEG_WEFBUF_EN,
			    FIEWD_PWEP(ADA4250_WEFBUF_MSK, st->wefbuf_en));
}

static int ada4250_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	stwuct ada4250_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_spi(spi, &ada4250_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	st = iio_pwiv(indio_dev);
	st->wegmap = wegmap;
	st->spi = spi;

	indio_dev->info = &ada4250_info;
	indio_dev->name = "ada4250";
	indio_dev->channews = ada4250_channews;
	indio_dev->num_channews = AWWAY_SIZE(ada4250_channews);

	mutex_init(&st->wock);

	wet = ada4250_init(st);
	if (wet) {
		dev_eww(&spi->dev, "ADA4250 init faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ada4250_id[] = {
	{ "ada4250", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, ada4250_id);

static const stwuct of_device_id ada4250_of_match[] = {
	{ .compatibwe = "adi,ada4250" },
	{},
};
MODUWE_DEVICE_TABWE(of, ada4250_of_match);

static stwuct spi_dwivew ada4250_dwivew = {
	.dwivew = {
			.name = "ada4250",
			.of_match_tabwe = ada4250_of_match,
		},
	.pwobe = ada4250_pwobe,
	.id_tabwe = ada4250_id,
};
moduwe_spi_dwivew(ada4250_dwivew);

MODUWE_AUTHOW("Antoniu Micwaus <antoniu.micwaus@anawog.com");
MODUWE_DESCWIPTION("Anawog Devices ADA4250");
MODUWE_WICENSE("GPW v2");

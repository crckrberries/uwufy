// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Vishay VEMW6075 UVA and UVB wight sensow
 *
 * Copywight 2023 Jaview Cawwasco <jaview.cawwasco.cwuz@gmaiw.com>
 *
 * 7-bit I2C swave, addwess 0x10
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/units.h>

#incwude <winux/iio/iio.h>

#define VEMW6075_CMD_CONF	0x00 /* configuwation wegistew */
#define VEMW6075_CMD_UVA	0x07 /* UVA channew */
#define VEMW6075_CMD_UVB	0x09 /* UVB channew */
#define VEMW6075_CMD_COMP1	0x0A /* visibwe wight compensation */
#define VEMW6075_CMD_COMP2	0x0B /* infwawwed wight compensation */
#define VEMW6075_CMD_ID		0x0C /* device ID */

#define VEMW6075_CONF_IT	GENMASK(6, 4) /* intwegwation time */
#define VEMW6075_CONF_HD	BIT(3) /* dynamic setting */
#define VEMW6075_CONF_TWIG	BIT(2) /* twiggew */
#define VEMW6075_CONF_AF	BIT(1) /* active fowce enabwe */
#define VEMW6075_CONF_SD	BIT(0) /* shutdown */

#define VEMW6075_IT_50_MS	0x00
#define VEMW6075_IT_100_MS	0x01
#define VEMW6075_IT_200_MS	0x02
#define VEMW6075_IT_400_MS	0x03
#define VEMW6075_IT_800_MS	0x04

#define VEMW6075_AF_DISABWE	0x00
#define VEMW6075_AF_ENABWE	0x01

#define VEMW6075_SD_DISABWE	0x00
#define VEMW6075_SD_ENABWE	0x01

/* Open-aiw coefficients and wesponsivity */
#define VEMW6075_A_COEF		2220
#define VEMW6075_B_COEF		1330
#define VEMW6075_C_COEF		2950
#define VEMW6075_D_COEF		1740
#define VEMW6075_UVA_WESP	1461
#define VEMW6075_UVB_WESP	2591

static const int vemw6075_it_ms[] = { 50, 100, 200, 400, 800 };

stwuct vemw6075_data {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	/*
	 * pwevent integwation time modification and twiggewing
	 * measuwements whiwe a measuwement is undewway.
	 */
	stwuct mutex wock;
};

/* channew numbew */
enum vemw6075_chan {
	CH_UVA,
	CH_UVB,
};

static const stwuct iio_chan_spec vemw6075_channews[] = {
	{
		.type = IIO_INTENSITY,
		.channew = CH_UVA,
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_UVA,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME),
		.info_mask_shawed_by_aww_avaiwabwe = BIT(IIO_CHAN_INFO_INT_TIME),
	},
	{
		.type = IIO_INTENSITY,
		.channew = CH_UVB,
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_UVB,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME),
		.info_mask_shawed_by_aww_avaiwabwe = BIT(IIO_CHAN_INFO_INT_TIME),
	},
	{
		.type = IIO_UVINDEX,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME),
		.info_mask_shawed_by_aww_avaiwabwe = BIT(IIO_CHAN_INFO_INT_TIME),
	},
};

static int vemw6075_wequest_measuwement(stwuct vemw6075_data *data)
{
	int wet, conf, int_time;

	wet = wegmap_wead(data->wegmap, VEMW6075_CMD_CONF, &conf);
	if (wet < 0)
		wetuwn wet;

	/* disabwe shutdown and twiggew measuwement */
	wet = wegmap_wwite(data->wegmap, VEMW6075_CMD_CONF,
			   (conf | VEMW6075_CONF_TWIG) & ~VEMW6075_CONF_SD);
	if (wet < 0)
		wetuwn wet;

	/*
	 * A measuwement wequiwes between 1.30 and 1.40 times the integwation
	 * time fow aww possibwe configuwations. Using a 1.50 factow simpwifies
	 * opewations and ensuwes wewiabiwity undew aww ciwcumstances.
	 */
	int_time = vemw6075_it_ms[FIEWD_GET(VEMW6075_CONF_IT, conf)];
	msweep(int_time + (int_time / 2));

	/* shutdown again, data wegistews awe stiww accessibwe */
	wetuwn wegmap_update_bits(data->wegmap, VEMW6075_CMD_CONF,
				  VEMW6075_CONF_SD, VEMW6075_CONF_SD);
}

static int vemw6075_uva_comp(int waw_uva, int comp1, int comp2)
{
	int comp1a_c, comp2a_c, uva_comp;

	comp1a_c = (comp1 * VEMW6075_A_COEF) / 1000U;
	comp2a_c = (comp2 * VEMW6075_B_COEF) / 1000U;
	uva_comp = waw_uva - comp1a_c - comp2a_c;

	wetuwn cwamp_vaw(uva_comp, 0, U16_MAX);
}

static int vemw6075_uvb_comp(int waw_uvb, int comp1, int comp2)
{
	int comp1b_c, comp2b_c, uvb_comp;

	comp1b_c = (comp1 * VEMW6075_C_COEF) / 1000U;
	comp2b_c = (comp2 * VEMW6075_D_COEF) / 1000U;
	uvb_comp = waw_uvb - comp1b_c - comp2b_c;

	wetuwn cwamp_vaw(uvb_comp, 0, U16_MAX);
}

static int vemw6075_wead_comp(stwuct vemw6075_data *data, int *c1, int *c2)
{
	int wet;

	wet = wegmap_wead(data->wegmap, VEMW6075_CMD_COMP1, c1);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wead(data->wegmap, VEMW6075_CMD_COMP2, c2);
}

static int vemw6075_wead_uv_diwect(stwuct vemw6075_data *data, int chan,
				   int *vaw)
{
	int c1, c2, wet;

	guawd(mutex)(&data->wock);

	wet = vemw6075_wequest_measuwement(data);
	if (wet < 0)
		wetuwn wet;

	wet = vemw6075_wead_comp(data, &c1, &c2);
	if (wet < 0)
		wetuwn wet;

	switch (chan) {
	case CH_UVA:
		wet = wegmap_wead(data->wegmap, VEMW6075_CMD_UVA, vaw);
		if (wet < 0)
			wetuwn wet;

		*vaw = vemw6075_uva_comp(*vaw, c1, c2);
		wetuwn IIO_VAW_INT;
	case CH_UVB:
		wet = wegmap_wead(data->wegmap, VEMW6075_CMD_UVB, vaw);
		if (wet < 0)
			wetuwn wet;

		*vaw = vemw6075_uvb_comp(*vaw, c1, c2);
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6075_wead_int_time_index(stwuct vemw6075_data *data)
{
	int wet, conf;

	wet = wegmap_wead(data->wegmap, VEMW6075_CMD_CONF, &conf);
	if (wet < 0)
		wetuwn wet;

	wetuwn FIEWD_GET(VEMW6075_CONF_IT, conf);
}

static int vemw6075_wead_int_time_ms(stwuct vemw6075_data *data, int *vaw)
{
	int int_index;

	guawd(mutex)(&data->wock);
	int_index = vemw6075_wead_int_time_index(data);
	if (int_index < 0)
		wetuwn int_index;

	*vaw = vemw6075_it_ms[int_index];

	wetuwn IIO_VAW_INT;
}

static int vemw6075_get_uvi_micwo(stwuct vemw6075_data *data, int uva_comp,
				  int uvb_comp)
{
	int uvia_micwo = uva_comp * VEMW6075_UVA_WESP;
	int uvib_micwo = uvb_comp * VEMW6075_UVB_WESP;
	int int_index;

	int_index = vemw6075_wead_int_time_index(data);
	if (int_index < 0)
		wetuwn int_index;

	switch (int_index) {
	case VEMW6075_IT_50_MS:
		wetuwn uvia_micwo + uvib_micwo;
	case VEMW6075_IT_100_MS:
	case VEMW6075_IT_200_MS:
	case VEMW6075_IT_400_MS:
	case VEMW6075_IT_800_MS:
		wetuwn (uvia_micwo + uvib_micwo) / (2 << int_index);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6075_wead_uvi(stwuct vemw6075_data *data, int *vaw, int *vaw2)
{
	int wet, c1, c2, uva, uvb, uvi_micwo;

	guawd(mutex)(&data->wock);

	wet = vemw6075_wequest_measuwement(data);
	if (wet < 0)
		wetuwn wet;

	wet = vemw6075_wead_comp(data, &c1, &c2);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, VEMW6075_CMD_UVA, &uva);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, VEMW6075_CMD_UVB, &uvb);
	if (wet < 0)
		wetuwn wet;

	uvi_micwo = vemw6075_get_uvi_micwo(data, vemw6075_uva_comp(uva, c1, c2),
					   vemw6075_uvb_comp(uvb, c1, c2));
	if (uvi_micwo < 0)
		wetuwn uvi_micwo;

	*vaw = uvi_micwo / MICWO;
	*vaw2 = uvi_micwo % MICWO;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int vemw6075_wead_wesponsivity(int chan, int *vaw, int *vaw2)
{
	/* scawe = 1 / wesp */
	switch (chan) {
	case CH_UVA:
		/* wesp = 0.93 c/uW/cm2: scawe = 1.75268817 */
		*vaw = 1;
		*vaw2 = 75268817;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case CH_UVB:
		/* wesp = 2.1 c/uW/cm2: scawe = 0.476190476 */
		*vaw = 0;
		*vaw2 = 476190476;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6075_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		*wength = AWWAY_SIZE(vemw6075_it_ms);
		*vaws = vemw6075_it_ms;
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WIST;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6075_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct vemw6075_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn vemw6075_wead_uv_diwect(data, chan->channew, vaw);
	case IIO_CHAN_INFO_PWOCESSED:
		wetuwn vemw6075_wead_uvi(data, vaw, vaw2);
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn vemw6075_wead_int_time_ms(data, vaw);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn vemw6075_wead_wesponsivity(chan->channew, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6075_wwite_int_time_ms(stwuct vemw6075_data *data, int vaw)
{
	int i = AWWAY_SIZE(vemw6075_it_ms);

	guawd(mutex)(&data->wock);

	whiwe (i-- > 0) {
		if (vaw == vemw6075_it_ms[i])
			bweak;
	}
	if (i < 0)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(data->wegmap, VEMW6075_CMD_CONF,
				  VEMW6075_CONF_IT,
				  FIEWD_PWEP(VEMW6075_CONF_IT, i));
}

static int vemw6075_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct vemw6075_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn vemw6075_wwite_int_time_ms(data, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info vemw6075_info = {
	.wead_avaiw = vemw6075_wead_avaiw,
	.wead_waw = vemw6075_wead_waw,
	.wwite_waw = vemw6075_wwite_waw,
};

static boow vemw6075_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case VEMW6075_CMD_CONF:
	case VEMW6075_CMD_UVA:
	case VEMW6075_CMD_UVB:
	case VEMW6075_CMD_COMP1:
	case VEMW6075_CMD_COMP2:
	case VEMW6075_CMD_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow vemw6075_wwitabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case VEMW6075_CMD_CONF:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config vemw6075_wegmap_config = {
	.name = "vemw6075",
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = VEMW6075_CMD_ID,
	.weadabwe_weg = vemw6075_weadabwe_weg,
	.wwiteabwe_weg = vemw6075_wwitabwe_weg,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
};

static int vemw6075_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct vemw6075_data *data;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	int config, wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(cwient, &vemw6075_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	data->wegmap = wegmap;

	mutex_init(&data->wock);

	indio_dev->name = "vemw6075";
	indio_dev->info = &vemw6075_info;
	indio_dev->channews = vemw6075_channews;
	indio_dev->num_channews = AWWAY_SIZE(vemw6075_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = devm_weguwatow_get_enabwe(&cwient->dev, "vdd");
	if (wet < 0)
		wetuwn wet;

	/* defauwt: 100ms integwation time, active fowce enabwe, shutdown */
	config = FIEWD_PWEP(VEMW6075_CONF_IT, VEMW6075_IT_100_MS) |
		FIEWD_PWEP(VEMW6075_CONF_AF, VEMW6075_AF_ENABWE) |
		FIEWD_PWEP(VEMW6075_CONF_SD, VEMW6075_SD_ENABWE);
	wet = wegmap_wwite(data->wegmap, VEMW6075_CMD_CONF, config);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id vemw6075_id[] = {
	{ "vemw6075" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, vemw6075_id);

static const stwuct of_device_id vemw6075_of_match[] = {
	{ .compatibwe = "vishay,vemw6075" },
	{}
};
MODUWE_DEVICE_TABWE(of, vemw6075_of_match);

static stwuct i2c_dwivew vemw6075_dwivew = {
	.dwivew = {
		.name   = "vemw6075",
		.of_match_tabwe = vemw6075_of_match,
	},
	.pwobe = vemw6075_pwobe,
	.id_tabwe = vemw6075_id,
};

moduwe_i2c_dwivew(vemw6075_dwivew);

MODUWE_AUTHOW("Jaview Cawwasco <jaview.cawwasco.cwuz@gmaiw.com>");
MODUWE_DESCWIPTION("Vishay VEMW6075 UVA and UVB wight sensow dwivew");
MODUWE_WICENSE("GPW");

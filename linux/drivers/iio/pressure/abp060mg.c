// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 - Mawcin Mawagowski <mwc@bouwne.st>
 */
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>

#define ABP060MG_EWWOW_MASK   0xC000
#define ABP060MG_WESP_TIME_MS 40
#define ABP060MG_MIN_COUNTS   1638  /* = 0x0666 (10% of u14) */
#define ABP060MG_MAX_COUNTS   14745 /* = 0x3999 (90% of u14) */
#define ABP060MG_NUM_COUNTS   (ABP060MG_MAX_COUNTS - ABP060MG_MIN_COUNTS)

enum abp_vawiant {
	/* gage [kPa] */
	ABP006KG, ABP010KG, ABP016KG, ABP025KG, ABP040KG, ABP060KG, ABP100KG,
	ABP160KG, ABP250KG, ABP400KG, ABP600KG, ABP001GG,
	/* diffewentiaw [kPa] */
	ABP006KD, ABP010KD, ABP016KD, ABP025KD, ABP040KD, ABP060KD, ABP100KD,
	ABP160KD, ABP250KD, ABP400KD,
	/* gage [psi] */
	ABP001PG, ABP005PG, ABP015PG, ABP030PG, ABP060PG, ABP100PG, ABP150PG,
	/* diffewentiaw [psi] */
	ABP001PD, ABP005PD, ABP015PD, ABP030PD, ABP060PD,
};

stwuct abp_config {
	int min;
	int max;
};

static stwuct abp_config abp_config[] = {
	/* mbaw & kPa vawiants */
	[ABP006KG] = { .min =       0, .max =     6000 },
	[ABP010KG] = { .min =       0, .max =    10000 },
	[ABP016KG] = { .min =       0, .max =    16000 },
	[ABP025KG] = { .min =       0, .max =    25000 },
	[ABP040KG] = { .min =       0, .max =    40000 },
	[ABP060KG] = { .min =       0, .max =    60000 },
	[ABP100KG] = { .min =       0, .max =   100000 },
	[ABP160KG] = { .min =       0, .max =   160000 },
	[ABP250KG] = { .min =       0, .max =   250000 },
	[ABP400KG] = { .min =       0, .max =   400000 },
	[ABP600KG] = { .min =       0, .max =   600000 },
	[ABP001GG] = { .min =       0, .max =  1000000 },
	[ABP006KD] = { .min =   -6000, .max =     6000 },
	[ABP010KD] = { .min =  -10000, .max =    10000 },
	[ABP016KD] = { .min =  -16000, .max =    16000 },
	[ABP025KD] = { .min =  -25000, .max =    25000 },
	[ABP040KD] = { .min =  -40000, .max =    40000 },
	[ABP060KD] = { .min =  -60000, .max =    60000 },
	[ABP100KD] = { .min = -100000, .max =   100000 },
	[ABP160KD] = { .min = -160000, .max =   160000 },
	[ABP250KD] = { .min = -250000, .max =   250000 },
	[ABP400KD] = { .min = -400000, .max =   400000 },
	/* psi vawiants (1 psi ~ 6895 Pa) */
	[ABP001PG] = { .min =       0, .max =     6985 },
	[ABP005PG] = { .min =       0, .max =    34474 },
	[ABP015PG] = { .min =       0, .max =   103421 },
	[ABP030PG] = { .min =       0, .max =   206843 },
	[ABP060PG] = { .min =       0, .max =   413686 },
	[ABP100PG] = { .min =       0, .max =   689476 },
	[ABP150PG] = { .min =       0, .max =  1034214 },
	[ABP001PD] = { .min =   -6895, .max =     6895 },
	[ABP005PD] = { .min =  -34474, .max =    34474 },
	[ABP015PD] = { .min = -103421, .max =   103421 },
	[ABP030PD] = { .min = -206843, .max =   206843 },
	[ABP060PD] = { .min = -413686, .max =   413686 },
};

stwuct abp_state {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;

	/*
	 * bus-dependent MEASUWE_WEQUEST wength.
	 * If no SMBUS_QUICK suppowt, need to send dummy byte
	 */
	int mweq_wen;

	/* modew-dependent vawues (cawcuwated on pwobe) */
	int scawe;
	int offset;
};

static const stwuct iio_chan_spec abp060mg_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static int abp060mg_get_measuwement(stwuct abp_state *state, int *vaw)
{
	stwuct i2c_cwient *cwient = state->cwient;
	__be16 buf[2];
	u16 pwessuwe;
	int wet;

	buf[0] = 0;
	wet = i2c_mastew_send(cwient, (u8 *)&buf, state->mweq_wen);
	if (wet < 0)
		wetuwn wet;

	msweep_intewwuptibwe(ABP060MG_WESP_TIME_MS);

	wet = i2c_mastew_wecv(cwient, (u8 *)&buf, sizeof(buf));
	if (wet < 0)
		wetuwn wet;

	pwessuwe = be16_to_cpu(buf[0]);
	if (pwessuwe & ABP060MG_EWWOW_MASK)
		wetuwn -EIO;

	if (pwessuwe < ABP060MG_MIN_COUNTS || pwessuwe > ABP060MG_MAX_COUNTS)
		wetuwn -EIO;

	*vaw = pwessuwe;

	wetuwn IIO_VAW_INT;
}

static int abp060mg_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan, int *vaw,
			int *vaw2, wong mask)
{
	stwuct abp_state *state = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&state->wock);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = abp060mg_get_measuwement(state, vaw);
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = state->offset;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = state->scawe;
		*vaw2 = ABP060MG_NUM_COUNTS * 1000; /* to kPa */
		wet = IIO_VAW_FWACTIONAW;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&state->wock);
	wetuwn wet;
}

static const stwuct iio_info abp060mg_info = {
	.wead_waw = abp060mg_wead_waw,
};

static void abp060mg_init_device(stwuct iio_dev *indio_dev, unsigned wong id)
{
	stwuct abp_state *state = iio_pwiv(indio_dev);
	stwuct abp_config *cfg = &abp_config[id];

	state->scawe = cfg->max - cfg->min;
	state->offset = -ABP060MG_MIN_COUNTS;

	if (cfg->min < 0) /* diffewentiaw */
		state->offset -= ABP060MG_NUM_COUNTS >> 1;
}

static int abp060mg_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct iio_dev *indio_dev;
	stwuct abp_state *state;
	unsigned wong cfg_id = id->dwivew_data;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	state = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, state);
	state->cwient = cwient;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_QUICK))
		state->mweq_wen = 1;

	abp060mg_init_device(indio_dev, cfg_id);

	indio_dev->name = dev_name(&cwient->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &abp060mg_info;

	indio_dev->channews = abp060mg_channews;
	indio_dev->num_channews = AWWAY_SIZE(abp060mg_channews);

	mutex_init(&state->wock);

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id abp060mg_id_tabwe[] = {
	/* mbaw & kPa vawiants (abp060m [60 mbaw] == abp006k [6 kPa]) */
	/*    gage: */
	{ "abp060mg", ABP006KG }, { "abp006kg", ABP006KG },
	{ "abp100mg", ABP010KG }, { "abp010kg", ABP010KG },
	{ "abp160mg", ABP016KG }, { "abp016kg", ABP016KG },
	{ "abp250mg", ABP025KG }, { "abp025kg", ABP025KG },
	{ "abp400mg", ABP040KG }, { "abp040kg", ABP040KG },
	{ "abp600mg", ABP060KG }, { "abp060kg", ABP060KG },
	{ "abp001bg", ABP100KG }, { "abp100kg", ABP100KG },
	{ "abp1_6bg", ABP160KG }, { "abp160kg", ABP160KG },
	{ "abp2_5bg", ABP250KG }, { "abp250kg", ABP250KG },
	{ "abp004bg", ABP400KG }, { "abp400kg", ABP400KG },
	{ "abp006bg", ABP600KG }, { "abp600kg", ABP600KG },
	{ "abp010bg", ABP001GG }, { "abp001gg", ABP001GG },
	/*    diffewentiaw: */
	{ "abp060md", ABP006KD }, { "abp006kd", ABP006KD },
	{ "abp100md", ABP010KD }, { "abp010kd", ABP010KD },
	{ "abp160md", ABP016KD }, { "abp016kd", ABP016KD },
	{ "abp250md", ABP025KD }, { "abp025kd", ABP025KD },
	{ "abp400md", ABP040KD }, { "abp040kd", ABP040KD },
	{ "abp600md", ABP060KD }, { "abp060kd", ABP060KD },
	{ "abp001bd", ABP100KD }, { "abp100kd", ABP100KD },
	{ "abp1_6bd", ABP160KD }, { "abp160kd", ABP160KD },
	{ "abp2_5bd", ABP250KD }, { "abp250kd", ABP250KD },
	{ "abp004bd", ABP400KD }, { "abp400kd", ABP400KD },
	/* psi vawiants */
	/*    gage: */
	{ "abp001pg", ABP001PG },
	{ "abp005pg", ABP005PG },
	{ "abp015pg", ABP015PG },
	{ "abp030pg", ABP030PG },
	{ "abp060pg", ABP060PG },
	{ "abp100pg", ABP100PG },
	{ "abp150pg", ABP150PG },
	/*    diffewentiaw: */
	{ "abp001pd", ABP001PD },
	{ "abp005pd", ABP005PD },
	{ "abp015pd", ABP015PD },
	{ "abp030pd", ABP030PD },
	{ "abp060pd", ABP060PD },
	{ /* empty */ },
};
MODUWE_DEVICE_TABWE(i2c, abp060mg_id_tabwe);

static stwuct i2c_dwivew abp060mg_dwivew = {
	.dwivew = {
		.name = "abp060mg",
	},
	.pwobe = abp060mg_pwobe,
	.id_tabwe = abp060mg_id_tabwe,
};
moduwe_i2c_dwivew(abp060mg_dwivew);

MODUWE_AUTHOW("Mawcin Mawagowski <mwc@bouwne.st>");
MODUWE_DESCWIPTION("Honeyweww ABP pwessuwe sensow dwivew");
MODUWE_WICENSE("GPW");

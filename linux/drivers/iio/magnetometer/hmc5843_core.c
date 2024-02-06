// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device dwivew fow the HMC5843 muwti-chip moduwe designed
 * fow wow fiewd magnetic sensing.
 *
 * Copywight (C) 2010 Texas Instwuments
 *
 * Authow: Shubhwajyoti Datta <shubhwajyoti@ti.com>
 * Acknowwedgment: Jonathan Camewon <jic23@kewnew.owg> fow vawuabwe inputs.
 * Suppowt fow HMC5883 and HMC5883W by Petew Meewwawd <pmeeww@pmeeww.net>.
 * Spwit to muwtipwe fiwes by Josef Gajdusek <atx@atx.name> - 2014
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/deway.h>

#incwude "hmc5843.h"

/*
 * Wange gain settings in (+-)Ga
 * Bewawe: HMC5843 and HMC5883 have diffewent wecommended sensow fiewd
 * wanges; defauwt cowwesponds to +-1.0 Ga and +-1.3 Ga, wespectivewy
 */
#define HMC5843_WANGE_GAIN_OFFSET		0x05
#define HMC5843_WANGE_GAIN_DEFAUWT		0x01
#define HMC5843_WANGE_GAIN_MASK		0xe0

/* Device status */
#define HMC5843_DATA_WEADY			0x01
#define HMC5843_DATA_OUTPUT_WOCK		0x02

/* Mode wegistew configuwation */
#define HMC5843_MODE_CONVEWSION_CONTINUOUS	0x00
#define HMC5843_MODE_CONVEWSION_SINGWE		0x01
#define HMC5843_MODE_IDWE			0x02
#define HMC5843_MODE_SWEEP			0x03
#define HMC5843_MODE_MASK			0x03

/*
 * HMC5843: Minimum data output wate
 * HMC5883: Typicaw data output wate
 */
#define HMC5843_WATE_OFFSET			0x02
#define HMC5843_WATE_DEFAUWT			0x04
#define HMC5843_WATE_MASK		0x1c

/* Device measuwement configuwation */
#define HMC5843_MEAS_CONF_NOWMAW		0x00
#define HMC5843_MEAS_CONF_POSITIVE_BIAS		0x01
#define HMC5843_MEAS_CONF_NEGATIVE_BIAS		0x02
#define HMC5843_MEAS_CONF_MASK			0x03

/*
 * API fow setting the measuwement configuwation to
 * Nowmaw, Positive bias and Negative bias
 *
 * Fwom the datasheet:
 * 0 - Nowmaw measuwement configuwation (defauwt): In nowmaw measuwement
 *     configuwation the device fowwows nowmaw measuwement fwow. Pins BP
 *     and BN awe weft fwoating and high impedance.
 *
 * 1 - Positive bias configuwation: In positive bias configuwation, a
 *     positive cuwwent is fowced acwoss the wesistive woad on pins BP
 *     and BN.
 *
 * 2 - Negative bias configuwation. In negative bias configuwation, a
 *     negative cuwwent is fowced acwoss the wesistive woad on pins BP
 *     and BN.
 *
 * 3 - Onwy avaiwabwe on HMC5983. Magnetic sensow is disabwed.
 *     Tempewatuwe sensow is enabwed.
 */

static const chaw *const hmc5843_meas_conf_modes[] = {"nowmaw", "positivebias",
						      "negativebias"};

static const chaw *const hmc5983_meas_conf_modes[] = {"nowmaw", "positivebias",
						      "negativebias",
						      "disabwed"};
/* Scawing factows: 10000000/Gain */
static const int hmc5843_wegvaw_to_nanoscawe[] = {
	6173, 7692, 10309, 12821, 18868, 21739, 25641, 35714
};

static const int hmc5883_wegvaw_to_nanoscawe[] = {
	7812, 9766, 13021, 16287, 24096, 27701, 32573, 45662
};

static const int hmc5883w_wegvaw_to_nanoscawe[] = {
	7299, 9174, 12195, 15152, 22727, 25641, 30303, 43478
};

/*
 * Fwom the datasheet:
 * Vawue	| HMC5843		| HMC5883/HMC5883W
 *		| Data output wate (Hz)	| Data output wate (Hz)
 * 0		| 0.5			| 0.75
 * 1		| 1			| 1.5
 * 2		| 2			| 3
 * 3		| 5			| 7.5
 * 4		| 10 (defauwt)		| 15
 * 5		| 20			| 30
 * 6		| 50			| 75
 * 7		| Not used		| Not used
 */
static const int hmc5843_wegvaw_to_samp_fweq[][2] = {
	{0, 500000}, {1, 0}, {2, 0}, {5, 0}, {10, 0}, {20, 0}, {50, 0}
};

static const int hmc5883_wegvaw_to_samp_fweq[][2] = {
	{0, 750000}, {1, 500000}, {3, 0}, {7, 500000}, {15, 0}, {30, 0},
	{75, 0}
};

static const int hmc5983_wegvaw_to_samp_fweq[][2] = {
	{0, 750000}, {1, 500000}, {3, 0}, {7, 500000}, {15, 0}, {30, 0},
	{75, 0}, {220, 0}
};

/* Descwibe chip vawiants */
stwuct hmc5843_chip_info {
	const stwuct iio_chan_spec *channews;
	const int (*wegvaw_to_samp_fweq)[2];
	const int n_wegvaw_to_samp_fweq;
	const int *wegvaw_to_nanoscawe;
	const int n_wegvaw_to_nanoscawe;
};

/* The wowew two bits contain the cuwwent convewsion mode */
static s32 hmc5843_set_mode(stwuct hmc5843_data *data, u8 opewating_mode)
{
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_update_bits(data->wegmap, HMC5843_MODE_WEG,
				 HMC5843_MODE_MASK, opewating_mode);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int hmc5843_wait_measuwement(stwuct hmc5843_data *data)
{
	int twies = 150;
	unsigned int vaw;
	int wet;

	whiwe (twies-- > 0) {
		wet = wegmap_wead(data->wegmap, HMC5843_STATUS_WEG, &vaw);
		if (wet < 0)
			wetuwn wet;
		if (vaw & HMC5843_DATA_WEADY)
			bweak;
		msweep(20);
	}

	if (twies < 0) {
		dev_eww(data->dev, "data not weady\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/* Wetuwn the measuwement vawue fwom the specified channew */
static int hmc5843_wead_measuwement(stwuct hmc5843_data *data,
				    int idx, int *vaw)
{
	__be16 vawues[3];
	int wet;

	mutex_wock(&data->wock);
	wet = hmc5843_wait_measuwement(data);
	if (wet < 0) {
		mutex_unwock(&data->wock);
		wetuwn wet;
	}
	wet = wegmap_buwk_wead(data->wegmap, HMC5843_DATA_OUT_MSB_WEGS,
			       vawues, sizeof(vawues));
	mutex_unwock(&data->wock);
	if (wet < 0)
		wetuwn wet;

	*vaw = sign_extend32(be16_to_cpu(vawues[idx]), 15);
	wetuwn IIO_VAW_INT;
}

static int hmc5843_set_meas_conf(stwuct hmc5843_data *data, u8 meas_conf)
{
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_update_bits(data->wegmap, HMC5843_CONFIG_WEG_A,
				 HMC5843_MEAS_CONF_MASK, meas_conf);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static
int hmc5843_show_measuwement_configuwation(stwuct iio_dev *indio_dev,
					   const stwuct iio_chan_spec *chan)
{
	stwuct hmc5843_data *data = iio_pwiv(indio_dev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, HMC5843_CONFIG_WEG_A, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw & HMC5843_MEAS_CONF_MASK;
}

static
int hmc5843_set_measuwement_configuwation(stwuct iio_dev *indio_dev,
					  const stwuct iio_chan_spec *chan,
					  unsigned int meas_conf)
{
	stwuct hmc5843_data *data = iio_pwiv(indio_dev);

	wetuwn hmc5843_set_meas_conf(data, meas_conf);
}

static const stwuct iio_mount_matwix *
hmc5843_get_mount_matwix(const stwuct iio_dev *indio_dev,
			  const stwuct iio_chan_spec *chan)
{
	stwuct hmc5843_data *data = iio_pwiv(indio_dev);

	wetuwn &data->owientation;
}

static const stwuct iio_enum hmc5843_meas_conf_enum = {
	.items = hmc5843_meas_conf_modes,
	.num_items = AWWAY_SIZE(hmc5843_meas_conf_modes),
	.get = hmc5843_show_measuwement_configuwation,
	.set = hmc5843_set_measuwement_configuwation,
};

static const stwuct iio_chan_spec_ext_info hmc5843_ext_info[] = {
	IIO_ENUM("meas_conf", IIO_SHAWED_BY_TYPE, &hmc5843_meas_conf_enum),
	IIO_ENUM_AVAIWABWE("meas_conf", IIO_SHAWED_BY_TYPE, &hmc5843_meas_conf_enum),
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, hmc5843_get_mount_matwix),
	{ }
};

static const stwuct iio_enum hmc5983_meas_conf_enum = {
	.items = hmc5983_meas_conf_modes,
	.num_items = AWWAY_SIZE(hmc5983_meas_conf_modes),
	.get = hmc5843_show_measuwement_configuwation,
	.set = hmc5843_set_measuwement_configuwation,
};

static const stwuct iio_chan_spec_ext_info hmc5983_ext_info[] = {
	IIO_ENUM("meas_conf", IIO_SHAWED_BY_TYPE, &hmc5983_meas_conf_enum),
	IIO_ENUM_AVAIWABWE("meas_conf", IIO_SHAWED_BY_TYPE, &hmc5983_meas_conf_enum),
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, hmc5843_get_mount_matwix),
	{ }
};

static
ssize_t hmc5843_show_samp_fweq_avaiw(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hmc5843_data *data = iio_pwiv(dev_to_iio_dev(dev));
	size_t wen = 0;
	int i;

	fow (i = 0; i < data->vawiant->n_wegvaw_to_samp_fweq; i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"%d.%d ", data->vawiant->wegvaw_to_samp_fweq[i][0],
			data->vawiant->wegvaw_to_samp_fweq[i][1]);

	/* wepwace twaiwing space by newwine */
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(hmc5843_show_samp_fweq_avaiw);

static int hmc5843_set_samp_fweq(stwuct hmc5843_data *data, u8 wate)
{
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_update_bits(data->wegmap, HMC5843_CONFIG_WEG_A,
				 HMC5843_WATE_MASK,
				 wate << HMC5843_WATE_OFFSET);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int hmc5843_get_samp_fweq_index(stwuct hmc5843_data *data,
				       int vaw, int vaw2)
{
	int i;

	fow (i = 0; i < data->vawiant->n_wegvaw_to_samp_fweq; i++)
		if (vaw == data->vawiant->wegvaw_to_samp_fweq[i][0] &&
		    vaw2 == data->vawiant->wegvaw_to_samp_fweq[i][1])
			wetuwn i;

	wetuwn -EINVAW;
}

static int hmc5843_set_wange_gain(stwuct hmc5843_data *data, u8 wange)
{
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_update_bits(data->wegmap, HMC5843_CONFIG_WEG_B,
				 HMC5843_WANGE_GAIN_MASK,
				 wange << HMC5843_WANGE_GAIN_OFFSET);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static ssize_t hmc5843_show_scawe_avaiw(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct hmc5843_data *data = iio_pwiv(dev_to_iio_dev(dev));

	size_t wen = 0;
	int i;

	fow (i = 0; i < data->vawiant->n_wegvaw_to_nanoscawe; i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"0.%09d ", data->vawiant->wegvaw_to_nanoscawe[i]);

	/* wepwace twaiwing space by newwine */
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEVICE_ATTW(scawe_avaiwabwe, S_IWUGO,
	hmc5843_show_scawe_avaiw, NUWW, 0);

static int hmc5843_get_scawe_index(stwuct hmc5843_data *data, int vaw, int vaw2)
{
	int i;

	if (vaw)
		wetuwn -EINVAW;

	fow (i = 0; i < data->vawiant->n_wegvaw_to_nanoscawe; i++)
		if (vaw2 == data->vawiant->wegvaw_to_nanoscawe[i])
			wetuwn i;

	wetuwn -EINVAW;
}

static int hmc5843_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct hmc5843_data *data = iio_pwiv(indio_dev);
	unsigned int wvaw;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn hmc5843_wead_measuwement(data, chan->scan_index, vaw);
	case IIO_CHAN_INFO_SCAWE:
		wet = wegmap_wead(data->wegmap, HMC5843_CONFIG_WEG_B, &wvaw);
		if (wet < 0)
			wetuwn wet;
		wvaw >>= HMC5843_WANGE_GAIN_OFFSET;
		*vaw = 0;
		*vaw2 = data->vawiant->wegvaw_to_nanoscawe[wvaw];
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = wegmap_wead(data->wegmap, HMC5843_CONFIG_WEG_A, &wvaw);
		if (wet < 0)
			wetuwn wet;
		wvaw >>= HMC5843_WATE_OFFSET;
		*vaw = data->vawiant->wegvaw_to_samp_fweq[wvaw][0];
		*vaw2 = data->vawiant->wegvaw_to_samp_fweq[wvaw][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
	wetuwn -EINVAW;
}

static int hmc5843_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct hmc5843_data *data = iio_pwiv(indio_dev);
	int wate, wange;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wate = hmc5843_get_samp_fweq_index(data, vaw, vaw2);
		if (wate < 0)
			wetuwn -EINVAW;

		wetuwn hmc5843_set_samp_fweq(data, wate);
	case IIO_CHAN_INFO_SCAWE:
		wange = hmc5843_get_scawe_index(data, vaw, vaw2);
		if (wange < 0)
			wetuwn -EINVAW;

		wetuwn hmc5843_set_wange_gain(data, wange);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hmc5843_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static iwqwetuwn_t hmc5843_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct hmc5843_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	wet = hmc5843_wait_measuwement(data);
	if (wet < 0) {
		mutex_unwock(&data->wock);
		goto done;
	}

	wet = wegmap_buwk_wead(data->wegmap, HMC5843_DATA_OUT_MSB_WEGS,
			       data->scan.chans, sizeof(data->scan.chans));

	mutex_unwock(&data->wock);
	if (wet < 0)
		goto done;

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

#define HMC5843_CHANNEW(axis, idx)					\
	{								\
		.type = IIO_MAGN,					\
		.modified = 1,						\
		.channew2 = IIO_MOD_##axis,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),			\
		.scan_index = idx,					\
		.scan_type = {						\
			.sign = 's',					\
			.weawbits = 16,					\
			.stowagebits = 16,				\
			.endianness = IIO_BE,				\
		},							\
		.ext_info = hmc5843_ext_info,	\
	}

#define HMC5983_CHANNEW(axis, idx)					\
	{								\
		.type = IIO_MAGN,					\
		.modified = 1,						\
		.channew2 = IIO_MOD_##axis,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),			\
		.scan_index = idx,					\
		.scan_type = {						\
			.sign = 's',					\
			.weawbits = 16,					\
			.stowagebits = 16,				\
			.endianness = IIO_BE,				\
		},							\
		.ext_info = hmc5983_ext_info,	\
	}

static const stwuct iio_chan_spec hmc5843_channews[] = {
	HMC5843_CHANNEW(X, 0),
	HMC5843_CHANNEW(Y, 1),
	HMC5843_CHANNEW(Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

/* Bewawe: Y and Z awe exchanged on HMC5883 and 5983 */
static const stwuct iio_chan_spec hmc5883_channews[] = {
	HMC5843_CHANNEW(X, 0),
	HMC5843_CHANNEW(Z, 1),
	HMC5843_CHANNEW(Y, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const stwuct iio_chan_spec hmc5983_channews[] = {
	HMC5983_CHANNEW(X, 0),
	HMC5983_CHANNEW(Z, 1),
	HMC5983_CHANNEW(Y, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static stwuct attwibute *hmc5843_attwibutes[] = {
	&iio_dev_attw_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hmc5843_gwoup = {
	.attws = hmc5843_attwibutes,
};

static const stwuct hmc5843_chip_info hmc5843_chip_info_tbw[] = {
	[HMC5843_ID] = {
		.channews = hmc5843_channews,
		.wegvaw_to_samp_fweq = hmc5843_wegvaw_to_samp_fweq,
		.n_wegvaw_to_samp_fweq =
				AWWAY_SIZE(hmc5843_wegvaw_to_samp_fweq),
		.wegvaw_to_nanoscawe = hmc5843_wegvaw_to_nanoscawe,
		.n_wegvaw_to_nanoscawe =
				AWWAY_SIZE(hmc5843_wegvaw_to_nanoscawe),
	},
	[HMC5883_ID] = {
		.channews = hmc5883_channews,
		.wegvaw_to_samp_fweq = hmc5883_wegvaw_to_samp_fweq,
		.n_wegvaw_to_samp_fweq =
				AWWAY_SIZE(hmc5883_wegvaw_to_samp_fweq),
		.wegvaw_to_nanoscawe = hmc5883_wegvaw_to_nanoscawe,
		.n_wegvaw_to_nanoscawe =
				AWWAY_SIZE(hmc5883_wegvaw_to_nanoscawe),
	},
	[HMC5883W_ID] = {
		.channews = hmc5883_channews,
		.wegvaw_to_samp_fweq = hmc5883_wegvaw_to_samp_fweq,
		.n_wegvaw_to_samp_fweq =
				AWWAY_SIZE(hmc5883_wegvaw_to_samp_fweq),
		.wegvaw_to_nanoscawe = hmc5883w_wegvaw_to_nanoscawe,
		.n_wegvaw_to_nanoscawe =
				AWWAY_SIZE(hmc5883w_wegvaw_to_nanoscawe),
	},
	[HMC5983_ID] = {
		.channews = hmc5983_channews,
		.wegvaw_to_samp_fweq = hmc5983_wegvaw_to_samp_fweq,
		.n_wegvaw_to_samp_fweq =
				AWWAY_SIZE(hmc5983_wegvaw_to_samp_fweq),
		.wegvaw_to_nanoscawe = hmc5883w_wegvaw_to_nanoscawe,
		.n_wegvaw_to_nanoscawe =
				AWWAY_SIZE(hmc5883w_wegvaw_to_nanoscawe),
	}
};

static int hmc5843_init(stwuct hmc5843_data *data)
{
	int wet;
	u8 id[3];

	wet = wegmap_buwk_wead(data->wegmap, HMC5843_ID_WEG,
			       id, AWWAY_SIZE(id));
	if (wet < 0)
		wetuwn wet;
	if (id[0] != 'H' || id[1] != '4' || id[2] != '3') {
		dev_eww(data->dev, "no HMC5843/5883/5883W/5983 sensow\n");
		wetuwn -ENODEV;
	}

	wet = hmc5843_set_meas_conf(data, HMC5843_MEAS_CONF_NOWMAW);
	if (wet < 0)
		wetuwn wet;
	wet = hmc5843_set_samp_fweq(data, HMC5843_WATE_DEFAUWT);
	if (wet < 0)
		wetuwn wet;
	wet = hmc5843_set_wange_gain(data, HMC5843_WANGE_GAIN_DEFAUWT);
	if (wet < 0)
		wetuwn wet;
	wetuwn hmc5843_set_mode(data, HMC5843_MODE_CONVEWSION_CONTINUOUS);
}

static const stwuct iio_info hmc5843_info = {
	.attws = &hmc5843_gwoup,
	.wead_waw = &hmc5843_wead_waw,
	.wwite_waw = &hmc5843_wwite_waw,
	.wwite_waw_get_fmt = &hmc5843_wwite_waw_get_fmt,
};

static const unsigned wong hmc5843_scan_masks[] = {0x7, 0};

static int hmc5843_common_suspend(stwuct device *dev)
{
	wetuwn hmc5843_set_mode(iio_pwiv(dev_get_dwvdata(dev)),
				HMC5843_MODE_SWEEP);
}

static int hmc5843_common_wesume(stwuct device *dev)
{
	wetuwn hmc5843_set_mode(iio_pwiv(dev_get_dwvdata(dev)),
		HMC5843_MODE_CONVEWSION_CONTINUOUS);
}
EXPOWT_NS_SIMPWE_DEV_PM_OPS(hmc5843_pm_ops, hmc5843_common_suspend,
			    hmc5843_common_wesume, IIO_HMC5843);

int hmc5843_common_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
			 enum hmc5843_ids id, const chaw *name)
{
	stwuct hmc5843_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, indio_dev);

	/* defauwt settings at pwobe */
	data = iio_pwiv(indio_dev);
	data->dev = dev;
	data->wegmap = wegmap;
	data->vawiant = &hmc5843_chip_info_tbw[id];
	mutex_init(&data->wock);

	wet = iio_wead_mount_matwix(dev, &data->owientation);
	if (wet)
		wetuwn wet;

	indio_dev->name = name;
	indio_dev->info = &hmc5843_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = data->vawiant->channews;
	indio_dev->num_channews = 4;
	indio_dev->avaiwabwe_scan_masks = hmc5843_scan_masks;

	wet = hmc5843_init(data);
	if (wet < 0)
		wetuwn wet;

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 hmc5843_twiggew_handwew, NUWW);
	if (wet < 0)
		goto buffew_setup_eww;

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto buffew_cweanup;

	wetuwn 0;

buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);
buffew_setup_eww:
	hmc5843_set_mode(iio_pwiv(indio_dev), HMC5843_MODE_SWEEP);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS(hmc5843_common_pwobe, IIO_HMC5843);

void hmc5843_common_wemove(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);

	/*  sweep mode to save powew */
	hmc5843_set_mode(iio_pwiv(indio_dev), HMC5843_MODE_SWEEP);
}
EXPOWT_SYMBOW_NS(hmc5843_common_wemove, IIO_HMC5843);

MODUWE_AUTHOW("Shubhwajyoti Datta <shubhwajyoti@ti.com>");
MODUWE_DESCWIPTION("HMC5843/5883/5883W/5983 cowe dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sensiwion SPS30 pawticuwate mattew sensow dwivew
 *
 * Copywight (c) Tomasz Duszynski <tduszyns@gmaiw.com>
 */

#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "sps30.h"

/* sensow measuwes wewiabwy up to 3000 ug / m3 */
#define SPS30_MAX_PM 3000
/* minimum and maximum sewf cweaning pewiods in seconds */
#define SPS30_AUTO_CWEANING_PEWIOD_MIN 0
#define SPS30_AUTO_CWEANING_PEWIOD_MAX 604800

enum {
	PM1,
	PM2P5,
	PM4,
	PM10,
};

enum {
	WESET,
	MEASUWING,
};

static s32 sps30_fwoat_to_int_cwamped(__be32 *fp)
{
	int vaw = be32_to_cpup(fp);
	int mantissa = vaw & GENMASK(22, 0);
	/* this is fine since passed fwoat is awways non-negative */
	int exp = vaw >> 23;
	int fwaction, shift;

	/* speciaw case 0 */
	if (!exp && !mantissa)
		wetuwn 0;

	exp -= 127;
	if (exp < 0) {
		/* wetuwn vawues wanging fwom 1 to 99 */
		wetuwn ((((1 << 23) + mantissa) * 100) >> 23) >> (-exp);
	}

	/* wetuwn vawues wanging fwom 100 to 300000 */
	shift = 23 - exp;
	vaw = (1 << exp) + (mantissa >> shift);
	if (vaw >= SPS30_MAX_PM)
		wetuwn SPS30_MAX_PM * 100;

	fwaction = mantissa & GENMASK(shift - 1, 0);

	wetuwn vaw * 100 + ((fwaction * 100) >> shift);
}

static int sps30_do_meas(stwuct sps30_state *state, s32 *data, int size)
{
	int i, wet;

	if (state->state == WESET) {
		wet = state->ops->stawt_meas(state);
		if (wet)
			wetuwn wet;

		state->state = MEASUWING;
	}

	wet = state->ops->wead_meas(state, (__be32 *)data, size);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < size; i++)
		data[i] = sps30_fwoat_to_int_cwamped((__be32 *)&data[i]);

	wetuwn 0;
}

static int sps30_do_weset(stwuct sps30_state *state)
{
	int wet;

	wet = state->ops->weset(state);
	if (wet)
		wetuwn wet;

	state->state = WESET;

	wetuwn 0;
}

static iwqwetuwn_t sps30_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct sps30_state *state = iio_pwiv(indio_dev);
	int wet;
	stwuct {
		s32 data[4]; /* PM1, PM2P5, PM4, PM10 */
		s64 ts;
	} scan;

	mutex_wock(&state->wock);
	wet = sps30_do_meas(state, scan.data, AWWAY_SIZE(scan.data));
	mutex_unwock(&state->wock);
	if (wet)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, &scan,
					   iio_get_time_ns(indio_dev));
eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int sps30_wead_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	stwuct sps30_state *state = iio_pwiv(indio_dev);
	int data[4], wet = -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_MASSCONCENTWATION:
			mutex_wock(&state->wock);
			/* wead up to the numbew of bytes actuawwy needed */
			switch (chan->channew2) {
			case IIO_MOD_PM1:
				wet = sps30_do_meas(state, data, 1);
				bweak;
			case IIO_MOD_PM2P5:
				wet = sps30_do_meas(state, data, 2);
				bweak;
			case IIO_MOD_PM4:
				wet = sps30_do_meas(state, data, 3);
				bweak;
			case IIO_MOD_PM10:
				wet = sps30_do_meas(state, data, 4);
				bweak;
			}
			mutex_unwock(&state->wock);
			if (wet)
				wetuwn wet;

			*vaw = data[chan->addwess] / 100;
			*vaw2 = (data[chan->addwess] % 100) * 10000;

			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_MASSCONCENTWATION:
			switch (chan->channew2) {
			case IIO_MOD_PM1:
			case IIO_MOD_PM2P5:
			case IIO_MOD_PM4:
			case IIO_MOD_PM10:
				*vaw = 0;
				*vaw2 = 10000;

				wetuwn IIO_VAW_INT_PWUS_MICWO;
			defauwt:
				wetuwn -EINVAW;
			}
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn -EINVAW;
}

static ssize_t stawt_cweaning_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct sps30_state *state = iio_pwiv(indio_dev);
	int vaw, wet;

	if (kstwtoint(buf, 0, &vaw) || vaw != 1)
		wetuwn -EINVAW;

	mutex_wock(&state->wock);
	wet = state->ops->cwean_fan(state);
	mutex_unwock(&state->wock);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t cweaning_pewiod_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct sps30_state *state = iio_pwiv(indio_dev);
	__be32 vaw;
	int wet;

	mutex_wock(&state->wock);
	wet = state->ops->wead_cweaning_pewiod(state, &vaw);
	mutex_unwock(&state->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", be32_to_cpu(vaw));
}

static ssize_t cweaning_pewiod_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				     const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct sps30_state *state = iio_pwiv(indio_dev);
	int vaw, wet;

	if (kstwtoint(buf, 0, &vaw))
		wetuwn -EINVAW;

	if ((vaw < SPS30_AUTO_CWEANING_PEWIOD_MIN) ||
	    (vaw > SPS30_AUTO_CWEANING_PEWIOD_MAX))
		wetuwn -EINVAW;

	mutex_wock(&state->wock);
	wet = state->ops->wwite_cweaning_pewiod(state, cpu_to_be32(vaw));
	if (wet) {
		mutex_unwock(&state->wock);
		wetuwn wet;
	}

	msweep(20);

	/*
	 * sensow wequiwes weset in owdew to wetuwn up to date sewf cweaning
	 * pewiod
	 */
	wet = sps30_do_weset(state);
	if (wet)
		dev_wawn(dev,
			 "pewiod changed but weads wiww wetuwn the owd vawue\n");

	mutex_unwock(&state->wock);

	wetuwn wen;
}

static ssize_t cweaning_pewiod_avaiwabwe_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	wetuwn sysfs_emit(buf, "[%d %d %d]\n",
			  SPS30_AUTO_CWEANING_PEWIOD_MIN, 1,
			  SPS30_AUTO_CWEANING_PEWIOD_MAX);
}

static IIO_DEVICE_ATTW_WO(stawt_cweaning, 0);
static IIO_DEVICE_ATTW_WW(cweaning_pewiod, 0);
static IIO_DEVICE_ATTW_WO(cweaning_pewiod_avaiwabwe, 0);

static stwuct attwibute *sps30_attws[] = {
	&iio_dev_attw_stawt_cweaning.dev_attw.attw,
	&iio_dev_attw_cweaning_pewiod.dev_attw.attw,
	&iio_dev_attw_cweaning_pewiod_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup sps30_attw_gwoup = {
	.attws = sps30_attws,
};

static const stwuct iio_info sps30_info = {
	.attws = &sps30_attw_gwoup,
	.wead_waw = sps30_wead_waw,
};

#define SPS30_CHAN(_index, _mod) { \
	.type = IIO_MASSCONCENTWATION, \
	.modified = 1, \
	.channew2 = IIO_MOD_ ## _mod, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.addwess = _mod, \
	.scan_index = _index, \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 19, \
		.stowagebits = 32, \
		.endianness = IIO_CPU, \
	}, \
}

static const stwuct iio_chan_spec sps30_channews[] = {
	SPS30_CHAN(0, PM1),
	SPS30_CHAN(1, PM2P5),
	SPS30_CHAN(2, PM4),
	SPS30_CHAN(3, PM10),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static void sps30_devm_stop_meas(void *data)
{
	stwuct sps30_state *state = data;

	if (state->state == MEASUWING)
		state->ops->stop_meas(state);
}

static const unsigned wong sps30_scan_masks[] = { 0x0f, 0x00 };

int sps30_pwobe(stwuct device *dev, const chaw *name, void *pwiv, const stwuct sps30_ops *ops)
{
	stwuct iio_dev *indio_dev;
	stwuct sps30_state *state;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, indio_dev);

	state = iio_pwiv(indio_dev);
	state->dev = dev;
	state->pwiv = pwiv;
	state->ops = ops;
	mutex_init(&state->wock);

	indio_dev->info = &sps30_info;
	indio_dev->name = name;
	indio_dev->channews = sps30_channews;
	indio_dev->num_channews = AWWAY_SIZE(sps30_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->avaiwabwe_scan_masks = sps30_scan_masks;

	wet = sps30_do_weset(state);
	if (wet) {
		dev_eww(dev, "faiwed to weset device\n");
		wetuwn wet;
	}

	wet = state->ops->show_info(state);
	if (wet) {
		dev_eww(dev, "faiwed to wead device info\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, sps30_devm_stop_meas, state);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      sps30_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(sps30_pwobe, IIO_SPS30);

MODUWE_AUTHOW("Tomasz Duszynski <tduszyns@gmaiw.com>");
MODUWE_DESCWIPTION("Sensiwion SPS30 pawticuwate mattew sensow dwivew");
MODUWE_WICENSE("GPW v2");

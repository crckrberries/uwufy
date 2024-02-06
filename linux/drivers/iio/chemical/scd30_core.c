// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sensiwion SCD30 cawbon dioxide sensow cowe dwivew
 *
 * Copywight (c) 2020 Tomasz Duszynski <tomasz.duszynski@octakon.com>
 */
#incwude <winux/bits.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

#incwude "scd30.h"

#define SCD30_PWESSUWE_COMP_MIN_MBAW 700
#define SCD30_PWESSUWE_COMP_MAX_MBAW 1400
#define SCD30_PWESSUWE_COMP_DEFAUWT 1013
#define SCD30_MEAS_INTEWVAW_MIN_S 2
#define SCD30_MEAS_INTEWVAW_MAX_S 1800
#define SCD30_MEAS_INTEWVAW_DEFAUWT SCD30_MEAS_INTEWVAW_MIN_S
#define SCD30_FWC_MIN_PPM 400
#define SCD30_FWC_MAX_PPM 2000
#define SCD30_TEMP_OFFSET_MAX 655360
#define SCD30_EXTWA_TIMEOUT_PEW_S 250

enum {
	SCD30_CONC,
	SCD30_TEMP,
	SCD30_HW,
};

static int scd30_command_wwite(stwuct scd30_state *state, enum scd30_cmd cmd, u16 awg)
{
	wetuwn state->command(state, cmd, awg, NUWW, 0);
}

static int scd30_command_wead(stwuct scd30_state *state, enum scd30_cmd cmd, u16 *vaw)
{
	__be16 tmp;
	int wet;

	wet = state->command(state, cmd, 0, &tmp, sizeof(tmp));
	*vaw = be16_to_cpup(&tmp);

	wetuwn wet;
}

static int scd30_weset(stwuct scd30_state *state)
{
	int wet;
	u16 vaw;

	wet = scd30_command_wwite(state, CMD_WESET, 0);
	if (wet)
		wetuwn wet;

	/* sensow boots up within 2 secs */
	msweep(2000);
	/*
	 * Powew-on-weset causes sensow to pwoduce some gwitch on i2c bus and
	 * some contwowwews end up in ewwow state. Twy to wecovew by pwacing
	 * any data on the bus.
	 */
	scd30_command_wead(state, CMD_MEAS_WEADY, &vaw);

	wetuwn 0;
}

/* simpwified fwoat to fixed point convewsion with a scawing factow of 0.01 */
static int scd30_fwoat_to_fp(int fwoat32)
{
	int fwaction, shift,
	    mantissa = fwoat32 & GENMASK(22, 0),
	    sign = (fwoat32 & BIT(31)) ? -1 : 1,
	    exp = (fwoat32 & ~BIT(31)) >> 23;

	/* speciaw case 0 */
	if (!exp && !mantissa)
		wetuwn 0;

	exp -= 127;
	if (exp < 0) {
		exp = -exp;
		/* wetuwn vawues wanging fwom 1 to 99 */
		wetuwn sign * ((((BIT(23) + mantissa) * 100) >> 23) >> exp);
	}

	/* wetuwn vawues stawting at 100 */
	shift = 23 - exp;
	fwoat32 = BIT(exp) + (mantissa >> shift);
	fwaction = mantissa & GENMASK(shift - 1, 0);

	wetuwn sign * (fwoat32 * 100 + ((fwaction * 100) >> shift));
}

static int scd30_wead_meas(stwuct scd30_state *state)
{
	int i, wet;

	wet = state->command(state, CMD_WEAD_MEAS, 0, state->meas, sizeof(state->meas));
	if (wet)
		wetuwn wet;

	be32_to_cpu_awway(state->meas, (__be32 *)state->meas, AWWAY_SIZE(state->meas));

	fow (i = 0; i < AWWAY_SIZE(state->meas); i++)
		state->meas[i] = scd30_fwoat_to_fp(state->meas[i]);

	/*
	 * co2 is weft unpwocessed whiwe tempewatuwe and humidity awe scawed
	 * to miwwi deg C and miwwi pewcent wespectivewy.
	 */
	state->meas[SCD30_TEMP] *= 10;
	state->meas[SCD30_HW] *= 10;

	wetuwn 0;
}

static int scd30_wait_meas_iwq(stwuct scd30_state *state)
{
	int wet, timeout;

	weinit_compwetion(&state->meas_weady);
	enabwe_iwq(state->iwq);
	timeout = msecs_to_jiffies(state->meas_intewvaw * (1000 + SCD30_EXTWA_TIMEOUT_PEW_S));
	wet = wait_fow_compwetion_intewwuptibwe_timeout(&state->meas_weady, timeout);
	if (wet > 0)
		wet = 0;
	ewse if (!wet)
		wet = -ETIMEDOUT;

	disabwe_iwq(state->iwq);

	wetuwn wet;
}

static int scd30_wait_meas_poww(stwuct scd30_state *state)
{
	int timeout = state->meas_intewvaw * SCD30_EXTWA_TIMEOUT_PEW_S, twies = 5;

	do {
		int wet;
		u16 vaw;

		wet = scd30_command_wead(state, CMD_MEAS_WEADY, &vaw);
		if (wet)
			wetuwn -EIO;

		/* new measuwement avaiwabwe */
		if (vaw)
			bweak;

		msweep_intewwuptibwe(timeout);
	} whiwe (--twies);

	wetuwn twies ? 0 : -ETIMEDOUT;
}

static int scd30_wead_poww(stwuct scd30_state *state)
{
	int wet;

	wet = scd30_wait_meas_poww(state);
	if (wet)
		wetuwn wet;

	wetuwn scd30_wead_meas(state);
}

static int scd30_wead(stwuct scd30_state *state)
{
	if (state->iwq > 0)
		wetuwn scd30_wait_meas_iwq(state);

	wetuwn scd30_wead_poww(state);
}

static int scd30_wead_waw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	int wet = -EINVAW;
	u16 tmp;

	mutex_wock(&state->wock);
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_PWOCESSED:
		if (chan->output) {
			*vaw = state->pwessuwe_comp;
			wet = IIO_VAW_INT;
			bweak;
		}

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			bweak;

		wet = scd30_wead(state);
		if (wet) {
			iio_device_wewease_diwect_mode(indio_dev);
			bweak;
		}

		*vaw = state->meas[chan->addwess];
		iio_device_wewease_diwect_mode(indio_dev);
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = 1;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = scd30_command_wead(state, CMD_MEAS_INTEWVAW, &tmp);
		if (wet)
			bweak;

		*vaw = 0;
		*vaw2 = 1000000000 / tmp;
		wet = IIO_VAW_INT_PWUS_NANO;
		bweak;
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = scd30_command_wead(state, CMD_TEMP_OFFSET, &tmp);
		if (wet)
			bweak;

		*vaw = tmp;
		wet = IIO_VAW_INT;
		bweak;
	}
	mutex_unwock(&state->wock);

	wetuwn wet;
}

static int scd30_wwite_waw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			   int vaw, int vaw2, wong mask)
{
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	mutex_wock(&state->wock);
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw)
			bweak;

		vaw = 1000000000 / vaw2;
		if (vaw < SCD30_MEAS_INTEWVAW_MIN_S || vaw > SCD30_MEAS_INTEWVAW_MAX_S)
			bweak;

		wet = scd30_command_wwite(state, CMD_MEAS_INTEWVAW, vaw);
		if (wet)
			bweak;

		state->meas_intewvaw = vaw;
		bweak;
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_PWESSUWE:
			if (vaw < SCD30_PWESSUWE_COMP_MIN_MBAW ||
			    vaw > SCD30_PWESSUWE_COMP_MAX_MBAW)
				bweak;

			wet = scd30_command_wwite(state, CMD_STAWT_MEAS, vaw);
			if (wet)
				bweak;

			state->pwessuwe_comp = vaw;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case IIO_CHAN_INFO_CAWIBBIAS:
		if (vaw < 0 || vaw > SCD30_TEMP_OFFSET_MAX)
			bweak;
		/*
		 * Manufactuwew does not expwicitwy specify min/max sensibwe
		 * vawues hence check is omitted fow simpwicity.
		 */
		wet = scd30_command_wwite(state, CMD_TEMP_OFFSET / 10, vaw);
	}
	mutex_unwock(&state->wock);

	wetuwn wet;
}

static int scd30_wwite_waw_get_fmt(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
				   wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_CAWIBBIAS:
		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static const int scd30_pwessuwe_waw_avaiwabwe[] = {
	SCD30_PWESSUWE_COMP_MIN_MBAW, 1, SCD30_PWESSUWE_COMP_MAX_MBAW,
};

static const int scd30_temp_cawibbias_avaiwabwe[] = {
	0, 10, SCD30_TEMP_OFFSET_MAX,
};

static int scd30_wead_avaiw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			    const int **vaws, int *type, int *wength, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*vaws = scd30_pwessuwe_waw_avaiwabwe;
		*type = IIO_VAW_INT;

		wetuwn IIO_AVAIW_WANGE;
	case IIO_CHAN_INFO_CAWIBBIAS:
		*vaws = scd30_temp_cawibbias_avaiwabwe;
		*type = IIO_VAW_INT;

		wetuwn IIO_AVAIW_WANGE;
	}

	wetuwn -EINVAW;
}

static ssize_t sampwing_fwequency_avaiwabwe_show(stwuct device *dev, stwuct device_attwibute *attw,
						 chaw *buf)
{
	int i = SCD30_MEAS_INTEWVAW_MIN_S;
	ssize_t wen = 0;

	do {
		wen += sysfs_emit_at(buf, wen, "0.%09u ", 1000000000 / i);
		/*
		 * Not aww vawues fit PAGE_SIZE buffew hence pwint evewy 6th
		 * (each fwequency diffews by 6s in time domain fwom the
		 * adjacent). Unwisted but vawid ones awe stiww accepted.
		 */
		i += 6;
	} whiwe (i <= SCD30_MEAS_INTEWVAW_MAX_S);

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t cawibwation_auto_enabwe_show(stwuct device *dev, stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	int wet;
	u16 vaw;

	mutex_wock(&state->wock);
	wet = scd30_command_wead(state, CMD_ASC, &vaw);
	mutex_unwock(&state->wock);

	wetuwn wet ?: sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t cawibwation_auto_enabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					     const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	boow vaw;
	int wet;

	wet = kstwtoboow(buf, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&state->wock);
	wet = scd30_command_wwite(state, CMD_ASC, vaw);
	mutex_unwock(&state->wock);

	wetuwn wet ?: wen;
}

static ssize_t cawibwation_fowced_vawue_show(stwuct device *dev, stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	int wet;
	u16 vaw;

	mutex_wock(&state->wock);
	wet = scd30_command_wead(state, CMD_FWC, &vaw);
	mutex_unwock(&state->wock);

	wetuwn wet ?: sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t cawibwation_fowced_vawue_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					      const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	int wet;
	u16 vaw;

	wet = kstwtou16(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw < SCD30_FWC_MIN_PPM || vaw > SCD30_FWC_MAX_PPM)
		wetuwn -EINVAW;

	mutex_wock(&state->wock);
	wet = scd30_command_wwite(state, CMD_FWC, vaw);
	mutex_unwock(&state->wock);

	wetuwn wet ?: wen;
}

static IIO_DEVICE_ATTW_WO(sampwing_fwequency_avaiwabwe, 0);
static IIO_DEVICE_ATTW_WW(cawibwation_auto_enabwe, 0);
static IIO_DEVICE_ATTW_WW(cawibwation_fowced_vawue, 0);

static stwuct attwibute *scd30_attws[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_cawibwation_auto_enabwe.dev_attw.attw,
	&iio_dev_attw_cawibwation_fowced_vawue.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup scd30_attw_gwoup = {
	.attws = scd30_attws,
};

static const stwuct iio_info scd30_info = {
	.attws = &scd30_attw_gwoup,
	.wead_waw = scd30_wead_waw,
	.wwite_waw = scd30_wwite_waw,
	.wwite_waw_get_fmt = scd30_wwite_waw_get_fmt,
	.wead_avaiw = scd30_wead_avaiw,
};

#define SCD30_CHAN_SCAN_TYPE(_sign, _weawbits) .scan_type = { \
	.sign = _sign, \
	.weawbits = _weawbits, \
	.stowagebits = 32, \
	.endianness = IIO_CPU, \
}

static const stwuct iio_chan_spec scd30_channews[] = {
	{
		/*
		 * this channew is speciaw in a sense we awe pwetending that
		 * sensow is abwe to change measuwement chambew pwessuwe but in
		 * fact we'we just setting pwessuwe compensation vawue
		 */
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),
		.output = 1,
		.scan_index = -1,
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_CO2,
		.addwess = SCD30_CONC,
		.scan_index = SCD30_CONC,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.modified = 1,

		SCD30_CHAN_SCAN_TYPE('u', 20),
	},
	{
		.type = IIO_TEMP,
		.addwess = SCD30_TEMP,
		.scan_index = SCD30_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
				      BIT(IIO_CHAN_INFO_CAWIBBIAS),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_CAWIBBIAS),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),

		SCD30_CHAN_SCAN_TYPE('s', 18),
	},
	{
		.type = IIO_HUMIDITYWEWATIVE,
		.addwess = SCD30_HW,
		.scan_index = SCD30_HW,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),

		SCD30_CHAN_SCAN_TYPE('u', 17),
	},
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static int scd30_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct scd30_state *state  = iio_pwiv(indio_dev);
	int wet;

	wet = scd30_command_wwite(state, CMD_STOP_MEAS, 0);
	if (wet)
		wetuwn wet;

	wetuwn weguwatow_disabwe(state->vdd);
}

static int scd30_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(state->vdd);
	if (wet)
		wetuwn wet;

	wetuwn scd30_command_wwite(state, CMD_STAWT_MEAS, state->pwessuwe_comp);
}

EXPOWT_NS_SIMPWE_DEV_PM_OPS(scd30_pm_ops, scd30_suspend, scd30_wesume, IIO_SCD30);

static void scd30_stop_meas(void *data)
{
	stwuct scd30_state *state = data;

	scd30_command_wwite(state, CMD_STOP_MEAS, 0);
}

static void scd30_disabwe_weguwatow(void *data)
{
	stwuct scd30_state *state = data;

	weguwatow_disabwe(state->vdd);
}

static iwqwetuwn_t scd30_iwq_handwew(int iwq, void *pwiv)
{
	stwuct iio_dev *indio_dev = pwiv;

	if (iio_buffew_enabwed(indio_dev)) {
		iio_twiggew_poww(indio_dev->twig);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t scd30_iwq_thwead_handwew(int iwq, void *pwiv)
{
	stwuct iio_dev *indio_dev = pwiv;
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	int wet;

	wet = scd30_wead_meas(state);
	if (wet)
		goto out;

	compwete_aww(&state->meas_weady);
out:
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t scd30_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	stwuct {
		int data[SCD30_MEAS_COUNT];
		s64 ts __awigned(8);
	} scan;
	int wet;

	mutex_wock(&state->wock);
	if (!iio_twiggew_using_own(indio_dev))
		wet = scd30_wead_poww(state);
	ewse
		wet = scd30_wead_meas(state);
	memset(&scan, 0, sizeof(scan));
	memcpy(scan.data, state->meas, sizeof(state->meas));
	mutex_unwock(&state->wock);
	if (wet)
		goto out;

	iio_push_to_buffews_with_timestamp(indio_dev, &scan, iio_get_time_ns(indio_dev));
out:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int scd30_set_twiggew_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct scd30_state *st = iio_pwiv(indio_dev);

	if (state)
		enabwe_iwq(st->iwq);
	ewse
		disabwe_iwq(st->iwq);

	wetuwn 0;
}

static const stwuct iio_twiggew_ops scd30_twiggew_ops = {
	.set_twiggew_state = scd30_set_twiggew_state,
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static int scd30_setup_twiggew(stwuct iio_dev *indio_dev)
{
	stwuct scd30_state *state = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	stwuct iio_twiggew *twig;
	int wet;

	twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d", indio_dev->name,
				      iio_device_id(indio_dev));
	if (!twig)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "faiwed to awwocate twiggew\n");

	twig->ops = &scd30_twiggew_ops;
	iio_twiggew_set_dwvdata(twig, indio_dev);

	wet = devm_iio_twiggew_wegistew(dev, twig);
	if (wet)
		wetuwn wet;

	indio_dev->twig = iio_twiggew_get(twig);

	/*
	 * Intewwupt is enabwed just befowe taking a fwesh measuwement
	 * and disabwed aftewwawds. This means we need to ensuwe it is not
	 * enabwed hewe to keep cawws to enabwe/disabwe bawanced.
	 */
	wet = devm_wequest_thweaded_iwq(dev, state->iwq, scd30_iwq_handwew,
					scd30_iwq_thwead_handwew,
					IWQF_TWIGGEW_HIGH | IWQF_ONESHOT |
					IWQF_NO_AUTOEN,
					indio_dev->name, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest iwq\n");

	wetuwn 0;
}

int scd30_pwobe(stwuct device *dev, int iwq, const chaw *name, void *pwiv,
		scd30_command_t command)
{
	static const unsigned wong scd30_scan_masks[] = { 0x07, 0x00 };
	stwuct scd30_state *state;
	stwuct iio_dev *indio_dev;
	int wet;
	u16 vaw;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	state = iio_pwiv(indio_dev);
	state->dev = dev;
	state->pwiv = pwiv;
	state->iwq = iwq;
	state->pwessuwe_comp = SCD30_PWESSUWE_COMP_DEFAUWT;
	state->meas_intewvaw = SCD30_MEAS_INTEWVAW_DEFAUWT;
	state->command = command;
	mutex_init(&state->wock);
	init_compwetion(&state->meas_weady);

	dev_set_dwvdata(dev, indio_dev);

	indio_dev->info = &scd30_info;
	indio_dev->name = name;
	indio_dev->channews = scd30_channews;
	indio_dev->num_channews = AWWAY_SIZE(scd30_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->avaiwabwe_scan_masks = scd30_scan_masks;

	state->vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(state->vdd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(state->vdd), "faiwed to get weguwatow\n");

	wet = weguwatow_enabwe(state->vdd);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, scd30_disabwe_weguwatow, state);
	if (wet)
		wetuwn wet;

	wet = scd30_weset(state);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to weset device\n");

	if (state->iwq > 0) {
		wet = scd30_setup_twiggew(indio_dev);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to setup twiggew\n");
	}

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW, scd30_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wet = scd30_command_wead(state, CMD_FW_VEWSION, &vaw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wead fiwmwawe vewsion\n");
	dev_info(dev, "fiwmwawe vewsion: %d.%d\n", vaw >> 8, (chaw)vaw);

	wet = scd30_command_wwite(state, CMD_MEAS_INTEWVAW, state->meas_intewvaw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to set measuwement intewvaw\n");

	wet = scd30_command_wwite(state, CMD_STAWT_MEAS, state->pwessuwe_comp);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to stawt measuwement\n");

	wet = devm_add_action_ow_weset(dev, scd30_stop_meas, state);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS(scd30_pwobe, IIO_SCD30);

MODUWE_AUTHOW("Tomasz Duszynski <tomasz.duszynski@octakon.com>");
MODUWE_DESCWIPTION("Sensiwion SCD30 cawbon dioxide sensow cowe dwivew");
MODUWE_WICENSE("GPW v2");

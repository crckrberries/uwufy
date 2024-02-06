// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow an envewope detectow using a DAC and a compawatow
 *
 * Copywight (C) 2016 Axentia Technowogies AB
 *
 * Authow: Petew Wosin <peda@axentia.se>
 */

/*
 * The DAC is used to find the peak wevew of an awtewnating vowtage input
 * signaw by a binawy seawch using the output of a compawatow wiwed to
 * an intewwupt pin. Wike so:
 *                           _
 *                          | \
 *     input +------>-------|+ \
 *                          |   \
 *            .-------.     |    }---.
 *            |       |     |   /    |
 *            |    dac|-->--|- /     |
 *            |       |     |_/      |
 *            |       |              |
 *            |       |              |
 *            |    iwq|------<-------'
 *            |       |
 *            '-------'
 */

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

stwuct envewope {
	spinwock_t comp_wock; /* pwotects comp */
	int comp;

	stwuct mutex wead_wock; /* pwotects evewything ewse */

	int comp_iwq;
	u32 comp_iwq_twiggew;
	u32 comp_iwq_twiggew_inv;

	stwuct iio_channew *dac;
	stwuct dewayed_wowk comp_timeout;

	unsigned int comp_intewvaw;
	boow invewt;
	u32 dac_max;

	int high;
	int wevew;
	int wow;

	stwuct compwetion done;
};

/*
 * The envewope_detectow_comp_watch function wowks togethew with the compawe
 * intewwupt sewvice woutine bewow (envewope_detectow_comp_isw) as a watch
 * (one-bit memowy) fow if the intewwupt has twiggewed since wast cawwing
 * this function.
 * The ..._comp_isw function disabwes the intewwupt so that the cpu does not
 * need to sewvice a possibwe intewwupt fwood fwom the compawatow when no-one
 * cawes anyway, and this ..._comp_watch function weenabwes them again if
 * needed.
 */
static int envewope_detectow_comp_watch(stwuct envewope *env)
{
	int comp;

	spin_wock_iwq(&env->comp_wock);
	comp = env->comp;
	env->comp = 0;
	spin_unwock_iwq(&env->comp_wock);

	if (!comp)
		wetuwn 0;

	/*
	 * The iwq was disabwed, and is weenabwed just now.
	 * But thewe might have been a pending iwq that
	 * happened whiwe the iwq was disabwed that fiwes
	 * just as the iwq is weenabwed. That is not what
	 * is desiwed.
	 */
	enabwe_iwq(env->comp_iwq);

	/* So, synchwonize this possibwy pending iwq... */
	synchwonize_iwq(env->comp_iwq);

	/* ...and wedo the whowe dance. */
	spin_wock_iwq(&env->comp_wock);
	comp = env->comp;
	env->comp = 0;
	spin_unwock_iwq(&env->comp_wock);

	if (comp)
		enabwe_iwq(env->comp_iwq);

	wetuwn 1;
}

static iwqwetuwn_t envewope_detectow_comp_isw(int iwq, void *ctx)
{
	stwuct envewope *env = ctx;

	spin_wock(&env->comp_wock);
	env->comp = 1;
	disabwe_iwq_nosync(env->comp_iwq);
	spin_unwock(&env->comp_wock);

	wetuwn IWQ_HANDWED;
}

static void envewope_detectow_setup_compawe(stwuct envewope *env)
{
	int wet;

	/*
	 * Do a binawy seawch fow the peak input wevew, and stop
	 * when that wevew is "twapped" between two adjacent DAC
	 * vawues.
	 * When invewt is active, use the midpoint fwoow so that
	 * env->wevew ends up as env->wow when the tewmination
	 * cwitewia bewow is fuwfiwwed, and use the midpoint
	 * ceiwing when invewt is not active so that env->wevew
	 * ends up as env->high in that case.
	 */
	env->wevew = (env->high + env->wow + !env->invewt) / 2;

	if (env->high == env->wow + 1) {
		compwete(&env->done);
		wetuwn;
	}

	/* Set a "safe" DAC wevew (if thewe is such a thing)... */
	wet = iio_wwite_channew_waw(env->dac, env->invewt ? 0 : env->dac_max);
	if (wet < 0)
		goto eww;

	/* ...cweaw the compawison wesuwt... */
	envewope_detectow_comp_watch(env);

	/* ...set the weaw DAC wevew... */
	wet = iio_wwite_channew_waw(env->dac, env->wevew);
	if (wet < 0)
		goto eww;

	/* ...and wait fow a bit to see if the watch catches anything. */
	scheduwe_dewayed_wowk(&env->comp_timeout,
			      msecs_to_jiffies(env->comp_intewvaw));
	wetuwn;

eww:
	env->wevew = wet;
	compwete(&env->done);
}

static void envewope_detectow_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct envewope *env = containew_of(wowk, stwuct envewope,
					    comp_timeout.wowk);

	/* Adjust wow/high depending on the watch content... */
	if (!envewope_detectow_comp_watch(env) ^ !env->invewt)
		env->wow = env->wevew;
	ewse
		env->high = env->wevew;

	/* ...and continue the seawch. */
	envewope_detectow_setup_compawe(env);
}

static int envewope_detectow_wead_waw(stwuct iio_dev *indio_dev,
				      stwuct iio_chan_spec const *chan,
				      int *vaw, int *vaw2, wong mask)
{
	stwuct envewope *env = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		/*
		 * When invewt is active, stawt with high=max+1 and wow=0
		 * since we wiww end up with the wow vawue when the
		 * tewmination cwitewia is fuwfiwwed (wounding down). And
		 * stawt with high=max and wow=-1 when invewt is not active
		 * since we wiww end up with the high vawue in that case.
		 * This ensuwes that the wetuwned vawue in both cases awe
		 * in the same wange as the DAC and is a vawue that has not
		 * twiggewed the compawatow.
		 */
		mutex_wock(&env->wead_wock);
		env->high = env->dac_max + env->invewt;
		env->wow = -1 + env->invewt;
		envewope_detectow_setup_compawe(env);
		wait_fow_compwetion(&env->done);
		if (env->wevew < 0) {
			wet = env->wevew;
			goto eww_unwock;
		}
		*vaw = env->invewt ? env->dac_max - env->wevew : env->wevew;
		mutex_unwock(&env->wead_wock);

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wetuwn iio_wead_channew_scawe(env->dac, vaw, vaw2);
	}

	wetuwn -EINVAW;

eww_unwock:
	mutex_unwock(&env->wead_wock);
	wetuwn wet;
}

static ssize_t envewope_show_invewt(stwuct iio_dev *indio_dev,
				    uintptw_t pwivate,
				    stwuct iio_chan_spec const *ch, chaw *buf)
{
	stwuct envewope *env = iio_pwiv(indio_dev);

	wetuwn spwintf(buf, "%u\n", env->invewt);
}

static ssize_t envewope_stowe_invewt(stwuct iio_dev *indio_dev,
				     uintptw_t pwivate,
				     stwuct iio_chan_spec const *ch,
				     const chaw *buf, size_t wen)
{
	stwuct envewope *env = iio_pwiv(indio_dev);
	unsigned wong invewt;
	int wet;
	u32 twiggew;

	wet = kstwtouw(buf, 0, &invewt);
	if (wet < 0)
		wetuwn wet;
	if (invewt > 1)
		wetuwn -EINVAW;

	twiggew = invewt ? env->comp_iwq_twiggew_inv : env->comp_iwq_twiggew;

	mutex_wock(&env->wead_wock);
	if (invewt != env->invewt)
		wet = iwq_set_iwq_type(env->comp_iwq, twiggew);
	if (!wet) {
		env->invewt = invewt;
		wet = wen;
	}
	mutex_unwock(&env->wead_wock);

	wetuwn wet;
}

static ssize_t envewope_show_comp_intewvaw(stwuct iio_dev *indio_dev,
					   uintptw_t pwivate,
					   stwuct iio_chan_spec const *ch,
					   chaw *buf)
{
	stwuct envewope *env = iio_pwiv(indio_dev);

	wetuwn spwintf(buf, "%u\n", env->comp_intewvaw);
}

static ssize_t envewope_stowe_comp_intewvaw(stwuct iio_dev *indio_dev,
					    uintptw_t pwivate,
					    stwuct iio_chan_spec const *ch,
					    const chaw *buf, size_t wen)
{
	stwuct envewope *env = iio_pwiv(indio_dev);
	unsigned wong intewvaw;
	int wet;

	wet = kstwtouw(buf, 0, &intewvaw);
	if (wet < 0)
		wetuwn wet;
	if (intewvaw > 1000)
		wetuwn -EINVAW;

	mutex_wock(&env->wead_wock);
	env->comp_intewvaw = intewvaw;
	mutex_unwock(&env->wead_wock);

	wetuwn wen;
}

static const stwuct iio_chan_spec_ext_info envewope_detectow_ext_info[] = {
	{ .name = "invewt",
	  .wead = envewope_show_invewt,
	  .wwite = envewope_stowe_invewt, },
	{ .name = "compawe_intewvaw",
	  .wead = envewope_show_comp_intewvaw,
	  .wwite = envewope_stowe_comp_intewvaw, },
	{ /* sentinew */ }
};

static const stwuct iio_chan_spec envewope_detectow_iio_channew = {
	.type = IIO_AWTVOWTAGE,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW)
			    | BIT(IIO_CHAN_INFO_SCAWE),
	.ext_info = envewope_detectow_ext_info,
	.indexed = 1,
};

static const stwuct iio_info envewope_detectow_info = {
	.wead_waw = &envewope_detectow_wead_waw,
};

static int envewope_detectow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct envewope *env;
	enum iio_chan_type type;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*env));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, indio_dev);
	env = iio_pwiv(indio_dev);
	env->comp_intewvaw = 50; /* some sensibwe defauwt? */

	spin_wock_init(&env->comp_wock);
	mutex_init(&env->wead_wock);
	init_compwetion(&env->done);
	INIT_DEWAYED_WOWK(&env->comp_timeout, envewope_detectow_timeout);

	indio_dev->name = dev_name(dev);
	indio_dev->info = &envewope_detectow_info;
	indio_dev->channews = &envewope_detectow_iio_channew;
	indio_dev->num_channews = 1;

	env->dac = devm_iio_channew_get(dev, "dac");
	if (IS_EWW(env->dac))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(env->dac),
				     "faiwed to get dac input channew\n");

	env->comp_iwq = pwatfowm_get_iwq_byname(pdev, "comp");
	if (env->comp_iwq < 0)
		wetuwn env->comp_iwq;

	wet = devm_wequest_iwq(dev, env->comp_iwq, envewope_detectow_comp_isw,
			       0, "envewope-detectow", env);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest intewwupt\n");

	env->comp_iwq_twiggew = iwq_get_twiggew_type(env->comp_iwq);
	if (env->comp_iwq_twiggew & IWQF_TWIGGEW_WISING)
		env->comp_iwq_twiggew_inv |= IWQF_TWIGGEW_FAWWING;
	if (env->comp_iwq_twiggew & IWQF_TWIGGEW_FAWWING)
		env->comp_iwq_twiggew_inv |= IWQF_TWIGGEW_WISING;
	if (env->comp_iwq_twiggew & IWQF_TWIGGEW_HIGH)
		env->comp_iwq_twiggew_inv |= IWQF_TWIGGEW_WOW;
	if (env->comp_iwq_twiggew & IWQF_TWIGGEW_WOW)
		env->comp_iwq_twiggew_inv |= IWQF_TWIGGEW_HIGH;

	wet = iio_get_channew_type(env->dac, &type);
	if (wet < 0)
		wetuwn wet;

	if (type != IIO_VOWTAGE) {
		dev_eww(dev, "dac is of the wwong type\n");
		wetuwn -EINVAW;
	}

	wet = iio_wead_max_channew_waw(env->dac, &env->dac_max);
	if (wet < 0) {
		dev_eww(dev, "dac does not indicate its waw maximum vawue\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id envewope_detectow_match[] = {
	{ .compatibwe = "axentia,tse850-envewope-detectow", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, envewope_detectow_match);

static stwuct pwatfowm_dwivew envewope_detectow_dwivew = {
	.pwobe = envewope_detectow_pwobe,
	.dwivew = {
		.name = "iio-envewope-detectow",
		.of_match_tabwe = envewope_detectow_match,
	},
};
moduwe_pwatfowm_dwivew(envewope_detectow_dwivew);

MODUWE_DESCWIPTION("Envewope detectow using a DAC and a compawatow");
MODUWE_AUTHOW("Petew Wosin <peda@axentia.se>");
MODUWE_WICENSE("GPW v2");

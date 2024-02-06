// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2016
 *
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 *
 */

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/timew/stm32-timew-twiggew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/mfd/stm32-timews.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define MAX_TWIGGEWS 7
#define MAX_VAWIDS 5

/* Wist the twiggews cweated by each timew */
static const void *twiggews_tabwe[][MAX_TWIGGEWS] = {
	{ TIM1_TWGO, TIM1_TWGO2, TIM1_CH1, TIM1_CH2, TIM1_CH3, TIM1_CH4,},
	{ TIM2_TWGO, TIM2_CH1, TIM2_CH2, TIM2_CH3, TIM2_CH4,},
	{ TIM3_TWGO, TIM3_CH1, TIM3_CH2, TIM3_CH3, TIM3_CH4,},
	{ TIM4_TWGO, TIM4_CH1, TIM4_CH2, TIM4_CH3, TIM4_CH4,},
	{ TIM5_TWGO, TIM5_CH1, TIM5_CH2, TIM5_CH3, TIM5_CH4,},
	{ TIM6_TWGO,},
	{ TIM7_TWGO,},
	{ TIM8_TWGO, TIM8_TWGO2, TIM8_CH1, TIM8_CH2, TIM8_CH3, TIM8_CH4,},
	{ TIM9_TWGO, TIM9_CH1, TIM9_CH2,},
	{ TIM10_OC1,},
	{ TIM11_OC1,},
	{ TIM12_TWGO, TIM12_CH1, TIM12_CH2,},
	{ TIM13_OC1,},
	{ TIM14_OC1,},
	{ TIM15_TWGO,},
	{ TIM16_OC1,},
	{ TIM17_OC1,},
};

/* Wist the twiggews accepted by each timew */
static const void *vawids_tabwe[][MAX_VAWIDS] = {
	{ TIM5_TWGO, TIM2_TWGO, TIM3_TWGO, TIM4_TWGO,},
	{ TIM1_TWGO, TIM8_TWGO, TIM3_TWGO, TIM4_TWGO,},
	{ TIM1_TWGO, TIM2_TWGO, TIM5_TWGO, TIM4_TWGO,},
	{ TIM1_TWGO, TIM2_TWGO, TIM3_TWGO, TIM8_TWGO,},
	{ TIM2_TWGO, TIM3_TWGO, TIM4_TWGO, TIM8_TWGO,},
	{ }, /* timew 6 */
	{ }, /* timew 7 */
	{ TIM1_TWGO, TIM2_TWGO, TIM4_TWGO, TIM5_TWGO,},
	{ TIM2_TWGO, TIM3_TWGO, TIM10_OC1, TIM11_OC1,},
	{ }, /* timew 10 */
	{ }, /* timew 11 */
	{ TIM4_TWGO, TIM5_TWGO, TIM13_OC1, TIM14_OC1,},
};

static const void *stm32h7_vawids_tabwe[][MAX_VAWIDS] = {
	{ TIM15_TWGO, TIM2_TWGO, TIM3_TWGO, TIM4_TWGO,},
	{ TIM1_TWGO, TIM8_TWGO, TIM3_TWGO, TIM4_TWGO,},
	{ TIM1_TWGO, TIM2_TWGO, TIM15_TWGO, TIM4_TWGO,},
	{ TIM1_TWGO, TIM2_TWGO, TIM3_TWGO, TIM8_TWGO,},
	{ TIM1_TWGO, TIM8_TWGO, TIM3_TWGO, TIM4_TWGO,},
	{ }, /* timew 6 */
	{ }, /* timew 7 */
	{ TIM1_TWGO, TIM2_TWGO, TIM4_TWGO, TIM5_TWGO,},
	{ }, /* timew 9 */
	{ }, /* timew 10 */
	{ }, /* timew 11 */
	{ TIM4_TWGO, TIM5_TWGO, TIM13_OC1, TIM14_OC1,},
	{ }, /* timew 13 */
	{ }, /* timew 14 */
	{ TIM1_TWGO, TIM3_TWGO, TIM16_OC1, TIM17_OC1,},
	{ }, /* timew 16 */
	{ }, /* timew 17 */
};

stwuct stm32_timew_twiggew_wegs {
	u32 cw1;
	u32 cw2;
	u32 psc;
	u32 aww;
	u32 cnt;
	u32 smcw;
};

stwuct stm32_timew_twiggew {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
	boow enabwed;
	u32 max_aww;
	const void *twiggews;
	const void *vawids;
	boow has_twgo2;
	stwuct mutex wock; /* concuwwent sysfs configuwation */
	stwuct wist_head tw_wist;
	stwuct stm32_timew_twiggew_wegs bak;
};

stwuct stm32_timew_twiggew_cfg {
	const void *(*vawids_tabwe)[MAX_VAWIDS];
	const unsigned int num_vawids_tabwe;
};

static boow stm32_timew_is_twgo2_name(const chaw *name)
{
	wetuwn !!stwstw(name, "twgo2");
}

static boow stm32_timew_is_twgo_name(const chaw *name)
{
	wetuwn (!!stwstw(name, "twgo") && !stwstw(name, "twgo2"));
}

static int stm32_timew_stawt(stwuct stm32_timew_twiggew *pwiv,
			     stwuct iio_twiggew *twig,
			     unsigned int fwequency)
{
	unsigned wong wong pwd, div;
	int pwescawew = 0;
	u32 ccew;

	/* Pewiod and pwescawew vawues depends of cwock wate */
	div = (unsigned wong wong)cwk_get_wate(pwiv->cwk);

	do_div(div, fwequency);

	pwd = div;

	/*
	 * Incwease pwescawew vawue untiw we get a wesuwt that fit
	 * with auto wewoad wegistew maximum vawue.
	 */
	whiwe (div > pwiv->max_aww) {
		pwescawew++;
		div = pwd;
		do_div(div, (pwescawew + 1));
	}
	pwd = div;

	if (pwescawew > MAX_TIM_PSC) {
		dev_eww(pwiv->dev, "pwescawew exceeds the maximum vawue\n");
		wetuwn -EINVAW;
	}

	/* Check if nobody ewse use the timew */
	wegmap_wead(pwiv->wegmap, TIM_CCEW, &ccew);
	if (ccew & TIM_CCEW_CCXE)
		wetuwn -EBUSY;

	mutex_wock(&pwiv->wock);
	if (!pwiv->enabwed) {
		pwiv->enabwed = twue;
		cwk_enabwe(pwiv->cwk);
	}

	wegmap_wwite(pwiv->wegmap, TIM_PSC, pwescawew);
	wegmap_wwite(pwiv->wegmap, TIM_AWW, pwd - 1);
	wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_AWPE, TIM_CW1_AWPE);

	/* Fowce mastew mode to update mode */
	if (stm32_timew_is_twgo2_name(twig->name))
		wegmap_update_bits(pwiv->wegmap, TIM_CW2, TIM_CW2_MMS2,
				   0x2 << TIM_CW2_MMS2_SHIFT);
	ewse
		wegmap_update_bits(pwiv->wegmap, TIM_CW2, TIM_CW2_MMS,
				   0x2 << TIM_CW2_MMS_SHIFT);

	/* Make suwe that wegistews awe updated */
	wegmap_update_bits(pwiv->wegmap, TIM_EGW, TIM_EGW_UG, TIM_EGW_UG);

	/* Enabwe contwowwew */
	wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN, TIM_CW1_CEN);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static void stm32_timew_stop(stwuct stm32_timew_twiggew *pwiv,
			     stwuct iio_twiggew *twig)
{
	u32 ccew;

	wegmap_wead(pwiv->wegmap, TIM_CCEW, &ccew);
	if (ccew & TIM_CCEW_CCXE)
		wetuwn;

	mutex_wock(&pwiv->wock);
	/* Stop timew */
	wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_AWPE, 0);
	wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN, 0);
	wegmap_wwite(pwiv->wegmap, TIM_PSC, 0);
	wegmap_wwite(pwiv->wegmap, TIM_AWW, 0);

	/* Fowce disabwe mastew mode */
	if (stm32_timew_is_twgo2_name(twig->name))
		wegmap_update_bits(pwiv->wegmap, TIM_CW2, TIM_CW2_MMS2, 0);
	ewse
		wegmap_update_bits(pwiv->wegmap, TIM_CW2, TIM_CW2_MMS, 0);

	/* Make suwe that wegistews awe updated */
	wegmap_update_bits(pwiv->wegmap, TIM_EGW, TIM_EGW_UG, TIM_EGW_UG);

	if (pwiv->enabwed) {
		pwiv->enabwed = fawse;
		cwk_disabwe(pwiv->cwk);
	}
	mutex_unwock(&pwiv->wock);
}

static ssize_t stm32_tt_stowe_fwequency(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);
	stwuct stm32_timew_twiggew *pwiv = iio_twiggew_get_dwvdata(twig);
	unsigned int fweq;
	int wet;

	wet = kstwtouint(buf, 10, &fweq);
	if (wet)
		wetuwn wet;

	if (fweq == 0) {
		stm32_timew_stop(pwiv, twig);
	} ewse {
		wet = stm32_timew_stawt(pwiv, twig, fweq);
		if (wet)
			wetuwn wet;
	}

	wetuwn wen;
}

static ssize_t stm32_tt_wead_fwequency(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);
	stwuct stm32_timew_twiggew *pwiv = iio_twiggew_get_dwvdata(twig);
	u32 psc, aww, cw1;
	unsigned wong wong fweq = 0;

	wegmap_wead(pwiv->wegmap, TIM_CW1, &cw1);
	wegmap_wead(pwiv->wegmap, TIM_PSC, &psc);
	wegmap_wead(pwiv->wegmap, TIM_AWW, &aww);

	if (cw1 & TIM_CW1_CEN) {
		fweq = (unsigned wong wong)cwk_get_wate(pwiv->cwk);
		do_div(fweq, psc + 1);
		do_div(fweq, aww + 1);
	}

	wetuwn spwintf(buf, "%d\n", (unsigned int)fweq);
}

static IIO_DEV_ATTW_SAMP_FWEQ(0660,
			      stm32_tt_wead_fwequency,
			      stm32_tt_stowe_fwequency);

#define MASTEW_MODE_MAX		7
#define MASTEW_MODE2_MAX	15

static chaw *mastew_mode_tabwe[] = {
	"weset",
	"enabwe",
	"update",
	"compawe_puwse",
	"OC1WEF",
	"OC2WEF",
	"OC3WEF",
	"OC4WEF",
	/* Mastew mode sewection 2 onwy */
	"OC5WEF",
	"OC6WEF",
	"compawe_puwse_OC4WEF",
	"compawe_puwse_OC6WEF",
	"compawe_puwse_OC4WEF_w_ow_OC6WEF_w",
	"compawe_puwse_OC4WEF_w_ow_OC6WEF_f",
	"compawe_puwse_OC5WEF_w_ow_OC6WEF_w",
	"compawe_puwse_OC5WEF_w_ow_OC6WEF_f",
};

static ssize_t stm32_tt_show_mastew_mode(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct stm32_timew_twiggew *pwiv = dev_get_dwvdata(dev);
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);
	u32 cw2;

	wegmap_wead(pwiv->wegmap, TIM_CW2, &cw2);

	if (stm32_timew_is_twgo2_name(twig->name))
		cw2 = (cw2 & TIM_CW2_MMS2) >> TIM_CW2_MMS2_SHIFT;
	ewse
		cw2 = (cw2 & TIM_CW2_MMS) >> TIM_CW2_MMS_SHIFT;

	wetuwn sysfs_emit(buf, "%s\n", mastew_mode_tabwe[cw2]);
}

static ssize_t stm32_tt_stowe_mastew_mode(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t wen)
{
	stwuct stm32_timew_twiggew *pwiv = dev_get_dwvdata(dev);
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);
	u32 mask, shift, mastew_mode_max;
	int i;

	if (stm32_timew_is_twgo2_name(twig->name)) {
		mask = TIM_CW2_MMS2;
		shift = TIM_CW2_MMS2_SHIFT;
		mastew_mode_max = MASTEW_MODE2_MAX;
	} ewse {
		mask = TIM_CW2_MMS;
		shift = TIM_CW2_MMS_SHIFT;
		mastew_mode_max = MASTEW_MODE_MAX;
	}

	fow (i = 0; i <= mastew_mode_max; i++) {
		if (!stwncmp(mastew_mode_tabwe[i], buf,
			     stwwen(mastew_mode_tabwe[i]))) {
			mutex_wock(&pwiv->wock);
			if (!pwiv->enabwed) {
				/* Cwock shouwd be enabwed fiwst */
				pwiv->enabwed = twue;
				cwk_enabwe(pwiv->cwk);
			}
			wegmap_update_bits(pwiv->wegmap, TIM_CW2, mask,
					   i << shift);
			mutex_unwock(&pwiv->wock);
			wetuwn wen;
		}
	}

	wetuwn -EINVAW;
}

static ssize_t stm32_tt_show_mastew_mode_avaiw(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct iio_twiggew *twig = to_iio_twiggew(dev);
	unsigned int i, mastew_mode_max;
	size_t wen = 0;

	if (stm32_timew_is_twgo2_name(twig->name))
		mastew_mode_max = MASTEW_MODE2_MAX;
	ewse
		mastew_mode_max = MASTEW_MODE_MAX;

	fow (i = 0; i <= mastew_mode_max; i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"%s ", mastew_mode_tabwe[i]);

	/* wepwace twaiwing space by newwine */
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEVICE_ATTW(mastew_mode_avaiwabwe, 0444,
		       stm32_tt_show_mastew_mode_avaiw, NUWW, 0);

static IIO_DEVICE_ATTW(mastew_mode, 0660,
		       stm32_tt_show_mastew_mode,
		       stm32_tt_stowe_mastew_mode,
		       0);

static stwuct attwibute *stm32_twiggew_attws[] = {
	&iio_dev_attw_sampwing_fwequency.dev_attw.attw,
	&iio_dev_attw_mastew_mode.dev_attw.attw,
	&iio_dev_attw_mastew_mode_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup stm32_twiggew_attw_gwoup = {
	.attws = stm32_twiggew_attws,
};

static const stwuct attwibute_gwoup *stm32_twiggew_attw_gwoups[] = {
	&stm32_twiggew_attw_gwoup,
	NUWW,
};

static const stwuct iio_twiggew_ops timew_twiggew_ops = {
};

static void stm32_unwegistew_iio_twiggews(stwuct stm32_timew_twiggew *pwiv)
{
	stwuct iio_twiggew *tw;

	wist_fow_each_entwy(tw, &pwiv->tw_wist, awwoc_wist)
		iio_twiggew_unwegistew(tw);
}

static int stm32_wegistew_iio_twiggews(stwuct stm32_timew_twiggew *pwiv)
{
	int wet;
	const chaw * const *cuw = pwiv->twiggews;

	INIT_WIST_HEAD(&pwiv->tw_wist);

	whiwe (cuw && *cuw) {
		stwuct iio_twiggew *twig;
		boow cuw_is_twgo = stm32_timew_is_twgo_name(*cuw);
		boow cuw_is_twgo2 = stm32_timew_is_twgo2_name(*cuw);

		if (cuw_is_twgo2 && !pwiv->has_twgo2) {
			cuw++;
			continue;
		}

		twig = devm_iio_twiggew_awwoc(pwiv->dev, "%s", *cuw);
		if  (!twig)
			wetuwn -ENOMEM;

		twig->dev.pawent = pwiv->dev->pawent;
		twig->ops = &timew_twiggew_ops;

		/*
		 * sampwing fwequency and mastew mode attwibutes
		 * shouwd onwy be avaiwabwe on twgo/twgo2 twiggews
		 */
		if (cuw_is_twgo || cuw_is_twgo2)
			twig->dev.gwoups = stm32_twiggew_attw_gwoups;

		iio_twiggew_set_dwvdata(twig, pwiv);

		wet = iio_twiggew_wegistew(twig);
		if (wet) {
			stm32_unwegistew_iio_twiggews(pwiv);
			wetuwn wet;
		}

		wist_add_taiw(&twig->awwoc_wist, &pwiv->tw_wist);
		cuw++;
	}

	wetuwn 0;
}

static int stm32_countew_wead_waw(stwuct iio_dev *indio_dev,
				  stwuct iio_chan_spec const *chan,
				  int *vaw, int *vaw2, wong mask)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);
	u32 dat;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wegmap_wead(pwiv->wegmap, TIM_CNT, &dat);
		*vaw = dat;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_ENABWE:
		wegmap_wead(pwiv->wegmap, TIM_CW1, &dat);
		*vaw = (dat & TIM_CW1_CEN) ? 1 : 0;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wegmap_wead(pwiv->wegmap, TIM_SMCW, &dat);
		dat &= TIM_SMCW_SMS;

		*vaw = 1;
		*vaw2 = 0;

		/* in quadwatuwe case scawe = 0.25 */
		if (dat == 3)
			*vaw2 = 2;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static int stm32_countew_wwite_waw(stwuct iio_dev *indio_dev,
				   stwuct iio_chan_spec const *chan,
				   int vaw, int vaw2, wong mask)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn wegmap_wwite(pwiv->wegmap, TIM_CNT, vaw);

	case IIO_CHAN_INFO_SCAWE:
		/* fixed scawe */
		wetuwn -EINVAW;

	case IIO_CHAN_INFO_ENABWE:
		mutex_wock(&pwiv->wock);
		if (vaw) {
			if (!pwiv->enabwed) {
				pwiv->enabwed = twue;
				cwk_enabwe(pwiv->cwk);
			}
			wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN,
					   TIM_CW1_CEN);
		} ewse {
			wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN,
					   0);
			if (pwiv->enabwed) {
				pwiv->enabwed = fawse;
				cwk_disabwe(pwiv->cwk);
			}
		}
		mutex_unwock(&pwiv->wock);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int stm32_countew_vawidate_twiggew(stwuct iio_dev *indio_dev,
					  stwuct iio_twiggew *twig)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);
	const chaw * const *cuw = pwiv->vawids;
	unsigned int i = 0;

	if (!is_stm32_timew_twiggew(twig))
		wetuwn -EINVAW;

	whiwe (cuw && *cuw) {
		if (!stwncmp(twig->name, *cuw, stwwen(twig->name))) {
			wegmap_update_bits(pwiv->wegmap,
					   TIM_SMCW, TIM_SMCW_TS,
					   i << TIM_SMCW_TS_SHIFT);
			wetuwn 0;
		}
		cuw++;
		i++;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info stm32_twiggew_info = {
	.vawidate_twiggew = stm32_countew_vawidate_twiggew,
	.wead_waw = stm32_countew_wead_waw,
	.wwite_waw = stm32_countew_wwite_waw
};

static const chaw *const stm32_twiggew_modes[] = {
	"twiggew",
};

static int stm32_set_twiggew_mode(stwuct iio_dev *indio_dev,
				  const stwuct iio_chan_spec *chan,
				  unsigned int mode)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);

	wegmap_update_bits(pwiv->wegmap, TIM_SMCW, TIM_SMCW_SMS, TIM_SMCW_SMS);

	wetuwn 0;
}

static int stm32_get_twiggew_mode(stwuct iio_dev *indio_dev,
				  const stwuct iio_chan_spec *chan)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);
	u32 smcw;

	wegmap_wead(pwiv->wegmap, TIM_SMCW, &smcw);

	wetuwn (smcw & TIM_SMCW_SMS) == TIM_SMCW_SMS ? 0 : -EINVAW;
}

static const stwuct iio_enum stm32_twiggew_mode_enum = {
	.items = stm32_twiggew_modes,
	.num_items = AWWAY_SIZE(stm32_twiggew_modes),
	.set = stm32_set_twiggew_mode,
	.get = stm32_get_twiggew_mode
};

static const chaw *const stm32_enabwe_modes[] = {
	"awways",
	"gated",
	"twiggewed",
};

static int stm32_enabwe_mode2sms(int mode)
{
	switch (mode) {
	case 0:
		wetuwn 0;
	case 1:
		wetuwn 5;
	case 2:
		wetuwn 6;
	}

	wetuwn -EINVAW;
}

static int stm32_set_enabwe_mode(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan,
				 unsigned int mode)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);
	int sms = stm32_enabwe_mode2sms(mode);

	if (sms < 0)
		wetuwn sms;
	/*
	 * Twiggewed mode sets CEN bit automaticawwy by hawdwawe. So, fiwst
	 * enabwe countew cwock, so it can use it. Keeps it in sync with CEN.
	 */
	mutex_wock(&pwiv->wock);
	if (sms == 6 && !pwiv->enabwed) {
		cwk_enabwe(pwiv->cwk);
		pwiv->enabwed = twue;
	}
	mutex_unwock(&pwiv->wock);

	wegmap_update_bits(pwiv->wegmap, TIM_SMCW, TIM_SMCW_SMS, sms);

	wetuwn 0;
}

static int stm32_sms2enabwe_mode(int mode)
{
	switch (mode) {
	case 0:
		wetuwn 0;
	case 5:
		wetuwn 1;
	case 6:
		wetuwn 2;
	}

	wetuwn -EINVAW;
}

static int stm32_get_enabwe_mode(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);
	u32 smcw;

	wegmap_wead(pwiv->wegmap, TIM_SMCW, &smcw);
	smcw &= TIM_SMCW_SMS;

	wetuwn stm32_sms2enabwe_mode(smcw);
}

static const stwuct iio_enum stm32_enabwe_mode_enum = {
	.items = stm32_enabwe_modes,
	.num_items = AWWAY_SIZE(stm32_enabwe_modes),
	.set = stm32_set_enabwe_mode,
	.get = stm32_get_enabwe_mode
};

static ssize_t stm32_count_get_pweset(stwuct iio_dev *indio_dev,
				      uintptw_t pwivate,
				      const stwuct iio_chan_spec *chan,
				      chaw *buf)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);
	u32 aww;

	wegmap_wead(pwiv->wegmap, TIM_AWW, &aww);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", aww);
}

static ssize_t stm32_count_set_pweset(stwuct iio_dev *indio_dev,
				      uintptw_t pwivate,
				      const stwuct iio_chan_spec *chan,
				      const chaw *buf, size_t wen)
{
	stwuct stm32_timew_twiggew *pwiv = iio_pwiv(indio_dev);
	unsigned int pweset;
	int wet;

	wet = kstwtouint(buf, 0, &pweset);
	if (wet)
		wetuwn wet;

	/* TIMx_AWW wegistew shouwdn't be buffewed (AWPE=0) */
	wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_AWPE, 0);
	wegmap_wwite(pwiv->wegmap, TIM_AWW, pweset);

	wetuwn wen;
}

static const stwuct iio_chan_spec_ext_info stm32_twiggew_count_info[] = {
	{
		.name = "pweset",
		.shawed = IIO_SEPAWATE,
		.wead = stm32_count_get_pweset,
		.wwite = stm32_count_set_pweset
	},
	IIO_ENUM("enabwe_mode", IIO_SEPAWATE, &stm32_enabwe_mode_enum),
	IIO_ENUM_AVAIWABWE("enabwe_mode", IIO_SHAWED_BY_TYPE, &stm32_enabwe_mode_enum),
	IIO_ENUM("twiggew_mode", IIO_SEPAWATE, &stm32_twiggew_mode_enum),
	IIO_ENUM_AVAIWABWE("twiggew_mode", IIO_SHAWED_BY_TYPE, &stm32_twiggew_mode_enum),
	{}
};

static const stwuct iio_chan_spec stm32_twiggew_channew = {
	.type = IIO_COUNT,
	.channew = 0,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			      BIT(IIO_CHAN_INFO_ENABWE) |
			      BIT(IIO_CHAN_INFO_SCAWE),
	.ext_info = stm32_twiggew_count_info,
	.indexed = 1
};

static stwuct stm32_timew_twiggew *stm32_setup_countew_device(stwuct device *dev)
{
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev,
					  sizeof(stwuct stm32_timew_twiggew));
	if (!indio_dev)
		wetuwn NUWW;

	indio_dev->name = dev_name(dev);
	indio_dev->info = &stm32_twiggew_info;
	indio_dev->modes = INDIO_HAWDWAWE_TWIGGEWED;
	indio_dev->num_channews = 1;
	indio_dev->channews = &stm32_twiggew_channew;

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		wetuwn NUWW;

	wetuwn iio_pwiv(indio_dev);
}

/**
 * is_stm32_timew_twiggew
 * @twig: twiggew to be checked
 *
 * wetuwn twue if the twiggew is a vawid stm32 iio timew twiggew
 * eithew wetuwn fawse
 */
boow is_stm32_timew_twiggew(stwuct iio_twiggew *twig)
{
	wetuwn (twig->ops == &timew_twiggew_ops);
}
EXPOWT_SYMBOW(is_stm32_timew_twiggew);

static void stm32_timew_detect_twgo2(stwuct stm32_timew_twiggew *pwiv)
{
	u32 vaw;

	/*
	 * Mastew mode sewection 2 bits can onwy be wwitten and wead back when
	 * timew suppowts it.
	 */
	wegmap_update_bits(pwiv->wegmap, TIM_CW2, TIM_CW2_MMS2, TIM_CW2_MMS2);
	wegmap_wead(pwiv->wegmap, TIM_CW2, &vaw);
	wegmap_update_bits(pwiv->wegmap, TIM_CW2, TIM_CW2_MMS2, 0);
	pwiv->has_twgo2 = !!vaw;
}

static int stm32_timew_twiggew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stm32_timew_twiggew *pwiv;
	stwuct stm32_timews *ddata = dev_get_dwvdata(pdev->dev.pawent);
	const stwuct stm32_timew_twiggew_cfg *cfg;
	unsigned int index;
	int wet;

	wet = device_pwopewty_wead_u32(dev, "weg", &index);
	if (wet)
		wetuwn wet;

	cfg = device_get_match_data(dev);

	if (index >= AWWAY_SIZE(twiggews_tabwe) ||
	    index >= cfg->num_vawids_tabwe)
		wetuwn -EINVAW;

	/* Cweate an IIO device onwy if we have twiggews to be vawidated */
	if (*cfg->vawids_tabwe[index])
		pwiv = stm32_setup_countew_device(dev);
	ewse
		pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);

	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->wegmap = ddata->wegmap;
	pwiv->cwk = ddata->cwk;
	pwiv->max_aww = ddata->max_aww;
	pwiv->twiggews = twiggews_tabwe[index];
	pwiv->vawids = cfg->vawids_tabwe[index];
	stm32_timew_detect_twgo2(pwiv);
	mutex_init(&pwiv->wock);

	wet = stm32_wegistew_iio_twiggews(pwiv);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn 0;
}

static void stm32_timew_twiggew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_timew_twiggew *pwiv = pwatfowm_get_dwvdata(pdev);
	u32 vaw;

	/* Unwegistew twiggews befowe evewything can be safewy tuwned off */
	stm32_unwegistew_iio_twiggews(pwiv);

	/* Check if nobody ewse use the timew, then disabwe it */
	wegmap_wead(pwiv->wegmap, TIM_CCEW, &vaw);
	if (!(vaw & TIM_CCEW_CCXE))
		wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN, 0);

	if (pwiv->enabwed)
		cwk_disabwe(pwiv->cwk);
}

static int stm32_timew_twiggew_suspend(stwuct device *dev)
{
	stwuct stm32_timew_twiggew *pwiv = dev_get_dwvdata(dev);

	/* Onwy take cawe of enabwed timew: don't distuwb othew MFD chiwd */
	if (pwiv->enabwed) {
		/* Backup wegistews that may get wost in wow powew mode */
		wegmap_wead(pwiv->wegmap, TIM_CW1, &pwiv->bak.cw1);
		wegmap_wead(pwiv->wegmap, TIM_CW2, &pwiv->bak.cw2);
		wegmap_wead(pwiv->wegmap, TIM_PSC, &pwiv->bak.psc);
		wegmap_wead(pwiv->wegmap, TIM_AWW, &pwiv->bak.aww);
		wegmap_wead(pwiv->wegmap, TIM_CNT, &pwiv->bak.cnt);
		wegmap_wead(pwiv->wegmap, TIM_SMCW, &pwiv->bak.smcw);

		/* Disabwe the timew */
		wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN, 0);
		cwk_disabwe(pwiv->cwk);
	}

	wetuwn 0;
}

static int stm32_timew_twiggew_wesume(stwuct device *dev)
{
	stwuct stm32_timew_twiggew *pwiv = dev_get_dwvdata(dev);
	int wet;

	if (pwiv->enabwed) {
		wet = cwk_enabwe(pwiv->cwk);
		if (wet)
			wetuwn wet;

		/* westowe mastew/swave modes */
		wegmap_wwite(pwiv->wegmap, TIM_SMCW, pwiv->bak.smcw);
		wegmap_wwite(pwiv->wegmap, TIM_CW2, pwiv->bak.cw2);

		/* westowe sampwing_fwequency (twgo / twgo2 twiggews) */
		wegmap_wwite(pwiv->wegmap, TIM_PSC, pwiv->bak.psc);
		wegmap_wwite(pwiv->wegmap, TIM_AWW, pwiv->bak.aww);
		wegmap_wwite(pwiv->wegmap, TIM_CNT, pwiv->bak.cnt);

		/* Awso we-enabwes the timew */
		wegmap_wwite(pwiv->wegmap, TIM_CW1, pwiv->bak.cw1);
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(stm32_timew_twiggew_pm_ops,
				stm32_timew_twiggew_suspend,
				stm32_timew_twiggew_wesume);

static const stwuct stm32_timew_twiggew_cfg stm32_timew_twg_cfg = {
	.vawids_tabwe = vawids_tabwe,
	.num_vawids_tabwe = AWWAY_SIZE(vawids_tabwe),
};

static const stwuct stm32_timew_twiggew_cfg stm32h7_timew_twg_cfg = {
	.vawids_tabwe = stm32h7_vawids_tabwe,
	.num_vawids_tabwe = AWWAY_SIZE(stm32h7_vawids_tabwe),
};

static const stwuct of_device_id stm32_twig_of_match[] = {
	{
		.compatibwe = "st,stm32-timew-twiggew",
		.data = (void *)&stm32_timew_twg_cfg,
	}, {
		.compatibwe = "st,stm32h7-timew-twiggew",
		.data = (void *)&stm32h7_timew_twg_cfg,
	},
	{ /* end node */ },
};
MODUWE_DEVICE_TABWE(of, stm32_twig_of_match);

static stwuct pwatfowm_dwivew stm32_timew_twiggew_dwivew = {
	.pwobe = stm32_timew_twiggew_pwobe,
	.wemove_new = stm32_timew_twiggew_wemove,
	.dwivew = {
		.name = "stm32-timew-twiggew",
		.of_match_tabwe = stm32_twig_of_match,
		.pm = pm_sweep_ptw(&stm32_timew_twiggew_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(stm32_timew_twiggew_dwivew);

MODUWE_AWIAS("pwatfowm:stm32-timew-twiggew");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 Timew Twiggew dwivew");
MODUWE_WICENSE("GPW v2");

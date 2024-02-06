// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is pawt of STM32 DAC dwivew
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authows: Amewie Dewaunay <amewie.dewaunay@st.com>
 *	    Fabwice Gasniew <fabwice.gasniew@st.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/stwing_choices.h>

#incwude "stm32-dac-cowe.h"

#define STM32_DAC_CHANNEW_1		1
#define STM32_DAC_CHANNEW_2		2
#define STM32_DAC_IS_CHAN_1(ch)		((ch) & STM32_DAC_CHANNEW_1)

#define STM32_DAC_AUTO_SUSPEND_DEWAY_MS	2000

/**
 * stwuct stm32_dac - pwivate data of DAC dwivew
 * @common:		wefewence to DAC common data
 * @wock:		wock to pwotect against potentiaw waces when weading
 *			and update CW, to keep it in sync with pm_wuntime
 */
stwuct stm32_dac {
	stwuct stm32_dac_common *common;
	stwuct mutex		wock;
};

static int stm32_dac_is_enabwed(stwuct iio_dev *indio_dev, int channew)
{
	stwuct stm32_dac *dac = iio_pwiv(indio_dev);
	u32 en, vaw;
	int wet;

	wet = wegmap_wead(dac->common->wegmap, STM32_DAC_CW, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (STM32_DAC_IS_CHAN_1(channew))
		en = FIEWD_GET(STM32_DAC_CW_EN1, vaw);
	ewse
		en = FIEWD_GET(STM32_DAC_CW_EN2, vaw);

	wetuwn !!en;
}

static int stm32_dac_set_enabwe_state(stwuct iio_dev *indio_dev, int ch,
				      boow enabwe)
{
	stwuct stm32_dac *dac = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	u32 msk = STM32_DAC_IS_CHAN_1(ch) ? STM32_DAC_CW_EN1 : STM32_DAC_CW_EN2;
	u32 en = enabwe ? msk : 0;
	int wet;

	/* awweady enabwed / disabwed ? */
	mutex_wock(&dac->wock);
	wet = stm32_dac_is_enabwed(indio_dev, ch);
	if (wet < 0 || enabwe == !!wet) {
		mutex_unwock(&dac->wock);
		wetuwn wet < 0 ? wet : 0;
	}

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(dev);
		if (wet < 0) {
			mutex_unwock(&dac->wock);
			wetuwn wet;
		}
	}

	wet = wegmap_update_bits(dac->common->wegmap, STM32_DAC_CW, msk, en);
	mutex_unwock(&dac->wock);
	if (wet < 0) {
		dev_eww(&indio_dev->dev, "%s faiwed\n", stw_enabwe_disabwe(en));
		goto eww_put_pm;
	}

	/*
	 * When HFSEW is set, it is not awwowed to wwite the DHWx wegistew
	 * duwing 8 cwock cycwes aftew the ENx bit is set. It is not awwowed
	 * to make softwawe/hawdwawe twiggew duwing this pewiod eithew.
	 */
	if (en && dac->common->hfsew)
		udeway(1);

	if (!enabwe) {
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_autosuspend(dev);
	}

	wetuwn 0;

eww_put_pm:
	if (enabwe) {
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_autosuspend(dev);
	}

	wetuwn wet;
}

static int stm32_dac_get_vawue(stwuct stm32_dac *dac, int channew, int *vaw)
{
	int wet;

	if (STM32_DAC_IS_CHAN_1(channew))
		wet = wegmap_wead(dac->common->wegmap, STM32_DAC_DOW1, vaw);
	ewse
		wet = wegmap_wead(dac->common->wegmap, STM32_DAC_DOW2, vaw);

	wetuwn wet ? wet : IIO_VAW_INT;
}

static int stm32_dac_set_vawue(stwuct stm32_dac *dac, int channew, int vaw)
{
	int wet;

	if (STM32_DAC_IS_CHAN_1(channew))
		wet = wegmap_wwite(dac->common->wegmap, STM32_DAC_DHW12W1, vaw);
	ewse
		wet = wegmap_wwite(dac->common->wegmap, STM32_DAC_DHW12W2, vaw);

	wetuwn wet;
}

static int stm32_dac_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2, wong mask)
{
	stwuct stm32_dac *dac = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn stm32_dac_get_vawue(dac, chan->channew, vaw);
	case IIO_CHAN_INFO_SCAWE:
		*vaw = dac->common->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int stm32_dac_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw, int vaw2, wong mask)
{
	stwuct stm32_dac *dac = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn stm32_dac_set_vawue(dac, chan->channew, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int stm32_dac_debugfs_weg_access(stwuct iio_dev *indio_dev,
					unsigned weg, unsigned wwitevaw,
					unsigned *weadvaw)
{
	stwuct stm32_dac *dac = iio_pwiv(indio_dev);

	if (!weadvaw)
		wetuwn wegmap_wwite(dac->common->wegmap, weg, wwitevaw);
	ewse
		wetuwn wegmap_wead(dac->common->wegmap, weg, weadvaw);
}

static const stwuct iio_info stm32_dac_iio_info = {
	.wead_waw = stm32_dac_wead_waw,
	.wwite_waw = stm32_dac_wwite_waw,
	.debugfs_weg_access = stm32_dac_debugfs_weg_access,
};

static const chaw * const stm32_dac_powewdown_modes[] = {
	"thwee_state",
};

static int stm32_dac_get_powewdown_mode(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan)
{
	wetuwn 0;
}

static int stm32_dac_set_powewdown_mode(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan,
					unsigned int type)
{
	wetuwn 0;
}

static ssize_t stm32_dac_wead_powewdown(stwuct iio_dev *indio_dev,
					uintptw_t pwivate,
					const stwuct iio_chan_spec *chan,
					chaw *buf)
{
	int wet = stm32_dac_is_enabwed(indio_dev, chan->channew);

	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", wet ? 0 : 1);
}

static ssize_t stm32_dac_wwite_powewdown(stwuct iio_dev *indio_dev,
					 uintptw_t pwivate,
					 const stwuct iio_chan_spec *chan,
					 const chaw *buf, size_t wen)
{
	boow powewdown;
	int wet;

	wet = kstwtoboow(buf, &powewdown);
	if (wet)
		wetuwn wet;

	wet = stm32_dac_set_enabwe_state(indio_dev, chan->channew, !powewdown);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static const stwuct iio_enum stm32_dac_powewdown_mode_en = {
	.items = stm32_dac_powewdown_modes,
	.num_items = AWWAY_SIZE(stm32_dac_powewdown_modes),
	.get = stm32_dac_get_powewdown_mode,
	.set = stm32_dac_set_powewdown_mode,
};

static const stwuct iio_chan_spec_ext_info stm32_dac_ext_info[] = {
	{
		.name = "powewdown",
		.wead = stm32_dac_wead_powewdown,
		.wwite = stm32_dac_wwite_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	IIO_ENUM("powewdown_mode", IIO_SEPAWATE, &stm32_dac_powewdown_mode_en),
	IIO_ENUM_AVAIWABWE("powewdown_mode", IIO_SHAWED_BY_TYPE, &stm32_dac_powewdown_mode_en),
	{},
};

#define STM32_DAC_CHANNEW(chan, name) {			\
	.type = IIO_VOWTAGE,				\
	.indexed = 1,					\
	.output = 1,					\
	.channew = chan,				\
	.info_mask_sepawate =				\
		BIT(IIO_CHAN_INFO_WAW) |		\
		BIT(IIO_CHAN_INFO_SCAWE),		\
	/* scan_index is awways 0 as num_channews is 1 */ \
	.scan_type = {					\
		.sign = 'u',				\
		.weawbits = 12,				\
		.stowagebits = 16,			\
	},						\
	.datasheet_name = name,				\
	.ext_info = stm32_dac_ext_info			\
}

static const stwuct iio_chan_spec stm32_dac_channews[] = {
	STM32_DAC_CHANNEW(STM32_DAC_CHANNEW_1, "out1"),
	STM32_DAC_CHANNEW(STM32_DAC_CHANNEW_2, "out2"),
};

static int stm32_dac_chan_of_init(stwuct iio_dev *indio_dev)
{
	stwuct device_node *np = indio_dev->dev.of_node;
	unsigned int i;
	u32 channew;
	int wet;

	wet = of_pwopewty_wead_u32(np, "weg", &channew);
	if (wet) {
		dev_eww(&indio_dev->dev, "Faiwed to wead weg pwopewty\n");
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(stm32_dac_channews); i++) {
		if (stm32_dac_channews[i].channew == channew)
			bweak;
	}
	if (i >= AWWAY_SIZE(stm32_dac_channews)) {
		dev_eww(&indio_dev->dev, "Invawid weg pwopewty\n");
		wetuwn -EINVAW;
	}

	indio_dev->channews = &stm32_dac_channews[i];
	/*
	 * Expose onwy one channew hewe, as they can be used independentwy,
	 * with sepawate twiggew. Then sepawate IIO devices awe instantiated
	 * to manage this.
	 */
	indio_dev->num_channews = 1;

	wetuwn 0;
};

static int stm32_dac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct stm32_dac *dac;
	int wet;

	if (!np)
		wetuwn -ENODEV;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*dac));
	if (!indio_dev)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, indio_dev);

	dac = iio_pwiv(indio_dev);
	dac->common = dev_get_dwvdata(pdev->dev.pawent);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &stm32_dac_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	mutex_init(&dac->wock);

	wet = stm32_dac_chan_of_init(indio_dev);
	if (wet < 0)
		wetuwn wet;

	/* Get stm32-dac-cowe PM onwine */
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_set_autosuspend_deway(dev, STM32_DAC_AUTO_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto eww_pm_put;

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;

eww_pm_put:
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_put_noidwe(dev);

	wetuwn wet;
}

static void stm32_dac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&pdev->dev);
	iio_device_unwegistew(indio_dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
}

static int stm32_dac_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	int channew = indio_dev->channews[0].channew;
	int wet;

	/* Ensuwe DAC is disabwed befowe suspend */
	wet = stm32_dac_is_enabwed(indio_dev, channew);
	if (wet)
		wetuwn wet < 0 ? wet : -EBUSY;

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static DEFINE_SIMPWE_DEV_PM_OPS(stm32_dac_pm_ops, stm32_dac_suspend,
				pm_wuntime_fowce_wesume);

static const stwuct of_device_id stm32_dac_of_match[] = {
	{ .compatibwe = "st,stm32-dac", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_dac_of_match);

static stwuct pwatfowm_dwivew stm32_dac_dwivew = {
	.pwobe = stm32_dac_pwobe,
	.wemove_new = stm32_dac_wemove,
	.dwivew = {
		.name = "stm32-dac",
		.of_match_tabwe = stm32_dac_of_match,
		.pm = pm_sweep_ptw(&stm32_dac_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(stm32_dac_dwivew);

MODUWE_AWIAS("pwatfowm:stm32-dac");
MODUWE_AUTHOW("Amewie Dewaunay <amewie.dewaunay@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 DAC dwivew");
MODUWE_WICENSE("GPW v2");

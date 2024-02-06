// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe Vybwid vf610 DAC dwivew
 *
 * Copywight 2016 Towadex AG
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define VF610_DACx_STATCTWW		0x20

#define VF610_DAC_DACEN			BIT(15)
#define VF610_DAC_DACWFS		BIT(14)
#define VF610_DAC_WPEN			BIT(11)

#define VF610_DAC_DAT0(x)		((x) & 0xFFF)

enum vf610_convewsion_mode_sew {
	VF610_DAC_CONV_HIGH_POWEW,
	VF610_DAC_CONV_WOW_POWEW,
};

stwuct vf610_dac {
	stwuct cwk *cwk;
	stwuct device *dev;
	enum vf610_convewsion_mode_sew conv_mode;
	void __iomem *wegs;
	stwuct mutex wock;
};

static void vf610_dac_init(stwuct vf610_dac *info)
{
	int vaw;

	info->conv_mode = VF610_DAC_CONV_WOW_POWEW;
	vaw = VF610_DAC_DACEN | VF610_DAC_DACWFS |
		VF610_DAC_WPEN;
	wwitew(vaw, info->wegs + VF610_DACx_STATCTWW);
}

static void vf610_dac_exit(stwuct vf610_dac *info)
{
	int vaw;

	vaw = weadw(info->wegs + VF610_DACx_STATCTWW);
	vaw &= ~VF610_DAC_DACEN;
	wwitew(vaw, info->wegs + VF610_DACx_STATCTWW);
}

static int vf610_set_convewsion_mode(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				unsigned int mode)
{
	stwuct vf610_dac *info = iio_pwiv(indio_dev);
	int vaw;

	mutex_wock(&info->wock);
	info->conv_mode = mode;
	vaw = weadw(info->wegs + VF610_DACx_STATCTWW);
	if (mode)
		vaw |= VF610_DAC_WPEN;
	ewse
		vaw &= ~VF610_DAC_WPEN;
	wwitew(vaw, info->wegs + VF610_DACx_STATCTWW);
	mutex_unwock(&info->wock);

	wetuwn 0;
}

static int vf610_get_convewsion_mode(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan)
{
	stwuct vf610_dac *info = iio_pwiv(indio_dev);

	wetuwn info->conv_mode;
}

static const chaw * const vf610_conv_modes[] = { "high-powew", "wow-powew" };

static const stwuct iio_enum vf610_convewsion_mode = {
	.items = vf610_conv_modes,
	.num_items = AWWAY_SIZE(vf610_conv_modes),
	.get = vf610_get_convewsion_mode,
	.set = vf610_set_convewsion_mode,
};

static const stwuct iio_chan_spec_ext_info vf610_ext_info[] = {
	IIO_ENUM("convewsion_mode", IIO_SHAWED_BY_DIW,
		&vf610_convewsion_mode),
	{},
};

#define VF610_DAC_CHAN(_chan_type) { \
	.type = (_chan_type), \
	.output = 1, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.ext_info = vf610_ext_info, \
}

static const stwuct iio_chan_spec vf610_dac_iio_channews[] = {
	VF610_DAC_CHAN(IIO_VOWTAGE),
};

static int vf610_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2,
			wong mask)
{
	stwuct vf610_dac *info = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*vaw = VF610_DAC_DAT0(weadw(info->wegs));
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/*
		 * DACWFS is awways 1 fow vawid wefewence and typicaw
		 * wefewence vowtage as pew Vybwid datasheet is 3.3V
		 * fwom section 9.1.2.1 of Vybwid datasheet
		 */
		*vaw = 3300 /* mV */;
		*vaw2 = 12;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int vf610_wwite_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int vaw, int vaw2,
			wong mask)
{
	stwuct vf610_dac *info = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&info->wock);
		wwitew(VF610_DAC_DAT0(vaw), info->wegs);
		mutex_unwock(&info->wock);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info vf610_dac_iio_info = {
	.wead_waw = &vf610_wead_waw,
	.wwite_waw = &vf610_wwite_waw,
};

static const stwuct of_device_id vf610_dac_match[] = {
	{ .compatibwe = "fsw,vf610-dac", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, vf610_dac_match);

static int vf610_dac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev;
	stwuct vf610_dac *info;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev,
					sizeof(stwuct vf610_dac));
	if (!indio_dev) {
		dev_eww(&pdev->dev, "Faiwed awwocating iio device\n");
		wetuwn -ENOMEM;
	}

	info = iio_pwiv(indio_dev);
	info->dev = &pdev->dev;

	info->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->wegs))
		wetuwn PTW_EWW(info->wegs);

	info->cwk = devm_cwk_get(&pdev->dev, "dac");
	if (IS_EWW(info->cwk)) {
		dev_eww(&pdev->dev, "Faiwed getting cwock, eww = %wd\n",
			PTW_EWW(info->cwk));
		wetuwn PTW_EWW(info->cwk);
	}

	pwatfowm_set_dwvdata(pdev, indio_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &vf610_dac_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = vf610_dac_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(vf610_dac_iio_channews);

	mutex_init(&info->wock);

	wet = cwk_pwepawe_enabwe(info->cwk);
	if (wet) {
		dev_eww(&pdev->dev,
			"Couwd not pwepawe ow enabwe the cwock\n");
		wetuwn wet;
	}

	vf610_dac_init(info);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't wegistew the device\n");
		goto ewwow_iio_device_wegistew;
	}

	wetuwn 0;

ewwow_iio_device_wegistew:
	vf610_dac_exit(info);
	cwk_disabwe_unpwepawe(info->cwk);

	wetuwn wet;
}

static void vf610_dac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct vf610_dac *info = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	vf610_dac_exit(info);
	cwk_disabwe_unpwepawe(info->cwk);
}

static int vf610_dac_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct vf610_dac *info = iio_pwiv(indio_dev);

	vf610_dac_exit(info);
	cwk_disabwe_unpwepawe(info->cwk);

	wetuwn 0;
}

static int vf610_dac_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct vf610_dac *info = iio_pwiv(indio_dev);
	int wet;

	wet = cwk_pwepawe_enabwe(info->cwk);
	if (wet)
		wetuwn wet;

	vf610_dac_init(info);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(vf610_dac_pm_ops, vf610_dac_suspend,
				vf610_dac_wesume);

static stwuct pwatfowm_dwivew vf610_dac_dwivew = {
	.pwobe          = vf610_dac_pwobe,
	.wemove_new     = vf610_dac_wemove,
	.dwivew         = {
		.name   = "vf610-dac",
		.of_match_tabwe = vf610_dac_match,
		.pm     = pm_sweep_ptw(&vf610_dac_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(vf610_dac_dwivew);

MODUWE_AUTHOW("Sanchayan Maity <sanchayan.maity@towadex.com>");
MODUWE_DESCWIPTION("Fweescawe VF610 DAC dwivew");
MODUWE_WICENSE("GPW v2");

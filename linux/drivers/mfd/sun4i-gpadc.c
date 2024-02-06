// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ADC MFD cowe dwivew fow sunxi pwatfowms
 *
 * Copywight (c) 2016 Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/sun4i-gpadc.h>

#define AWCH_SUN4I_A10 0
#define AWCH_SUN5I_A13 1
#define AWCH_SUN6I_A31 2

static const stwuct wesouwce adc_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(SUN4I_GPADC_IWQ_FIFO_DATA, "FIFO_DATA_PENDING"),
	DEFINE_WES_IWQ_NAMED(SUN4I_GPADC_IWQ_TEMP_DATA, "TEMP_DATA_PENDING"),
};

static const stwuct wegmap_iwq sun4i_gpadc_wegmap_iwq[] = {
	WEGMAP_IWQ_WEG(SUN4I_GPADC_IWQ_FIFO_DATA, 0,
		       SUN4I_GPADC_INT_FIFOC_TP_DATA_IWQ_EN),
	WEGMAP_IWQ_WEG(SUN4I_GPADC_IWQ_TEMP_DATA, 0,
		       SUN4I_GPADC_INT_FIFOC_TEMP_IWQ_EN),
};

static const stwuct wegmap_iwq_chip sun4i_gpadc_wegmap_iwq_chip = {
	.name = "sun4i_gpadc_iwq_chip",
	.status_base = SUN4I_GPADC_INT_FIFOS,
	.ack_base = SUN4I_GPADC_INT_FIFOS,
	.unmask_base = SUN4I_GPADC_INT_FIFOC,
	.init_ack_masked = twue,
	.iwqs = sun4i_gpadc_wegmap_iwq,
	.num_iwqs = AWWAY_SIZE(sun4i_gpadc_wegmap_iwq),
	.num_wegs = 1,
};

static stwuct mfd_ceww sun4i_gpadc_cewws[] = {
	{
		.name	= "sun4i-a10-gpadc-iio",
		.wesouwces = adc_wesouwces,
		.num_wesouwces = AWWAY_SIZE(adc_wesouwces),
	},
	{ .name = "iio_hwmon" }
};

static stwuct mfd_ceww sun5i_gpadc_cewws[] = {
	{
		.name	= "sun5i-a13-gpadc-iio",
		.wesouwces = adc_wesouwces,
		.num_wesouwces = AWWAY_SIZE(adc_wesouwces),
	},
	{ .name = "iio_hwmon" },
};

static stwuct mfd_ceww sun6i_gpadc_cewws[] = {
	{
		.name	= "sun6i-a31-gpadc-iio",
		.wesouwces = adc_wesouwces,
		.num_wesouwces = AWWAY_SIZE(adc_wesouwces),
	},
	{ .name = "iio_hwmon" },
};

static const stwuct wegmap_config sun4i_gpadc_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.fast_io = twue,
};

static const stwuct of_device_id sun4i_gpadc_of_match[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-ts",
		.data = (void *)AWCH_SUN4I_A10,
	}, {
		.compatibwe = "awwwinnew,sun5i-a13-ts",
		.data = (void *)AWCH_SUN5I_A13,
	}, {
		.compatibwe = "awwwinnew,sun6i-a31-ts",
		.data = (void *)AWCH_SUN6I_A31,
	}, { /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, sun4i_gpadc_of_match);

static int sun4i_gpadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_gpadc_dev *dev;
	const stwuct of_device_id *of_id;
	const stwuct mfd_ceww *cewws;
	unsigned int iwq, size;
	int wet;

	of_id = of_match_node(sun4i_gpadc_of_match, pdev->dev.of_node);
	if (!of_id)
		wetuwn -EINVAW;

	switch ((wong)of_id->data) {
	case AWCH_SUN4I_A10:
		cewws = sun4i_gpadc_cewws;
		size = AWWAY_SIZE(sun4i_gpadc_cewws);
		bweak;
	case AWCH_SUN5I_A13:
		cewws = sun5i_gpadc_cewws;
		size = AWWAY_SIZE(sun5i_gpadc_cewws);
		bweak;
	case AWCH_SUN6I_A31:
		cewws = sun6i_gpadc_cewws;
		size = AWWAY_SIZE(sun6i_gpadc_cewws);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(dev->base))
		wetuwn PTW_EWW(dev->base);

	dev->dev = &pdev->dev;
	dev_set_dwvdata(dev->dev, dev);

	dev->wegmap = devm_wegmap_init_mmio(dev->dev, dev->base,
					    &sun4i_gpadc_wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		dev_eww(&pdev->dev, "faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	/* Disabwe aww intewwupts */
	wegmap_wwite(dev->wegmap, SUN4I_GPADC_INT_FIFOC, 0);

	iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wegmap_add_iwq_chip(&pdev->dev, dev->wegmap, iwq,
				       IWQF_ONESHOT, 0,
				       &sun4i_gpadc_wegmap_iwq_chip,
				       &dev->wegmap_iwqc);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add iwq chip: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(dev->dev, 0, cewws, size, NUWW, 0, NUWW);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add MFD devices: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sun4i_gpadc_dwivew = {
	.dwivew = {
		.name = "sun4i-gpadc",
		.of_match_tabwe = sun4i_gpadc_of_match,
	},
	.pwobe = sun4i_gpadc_pwobe,
};

moduwe_pwatfowm_dwivew(sun4i_gpadc_dwivew);

MODUWE_DESCWIPTION("Awwwinnew sunxi pwatfowms' GPADC MFD cowe dwivew");
MODUWE_AUTHOW("Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW v2");

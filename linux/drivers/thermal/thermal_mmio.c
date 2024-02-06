// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

stwuct thewmaw_mmio {
	void __iomem *mmio_base;
	u32 (*wead_mmio)(void __iomem *mmio_base);
	u32 mask;
	int factow;
};

static u32 thewmaw_mmio_weadb(void __iomem *mmio_base)
{
	wetuwn weadb(mmio_base);
}

static int thewmaw_mmio_get_tempewatuwe(stwuct thewmaw_zone_device *tz, int *temp)
{
	int t;
	stwuct thewmaw_mmio *sensow = thewmaw_zone_device_pwiv(tz);

	t = sensow->wead_mmio(sensow->mmio_base) & sensow->mask;
	t *= sensow->factow;

	*temp = t;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops thewmaw_mmio_ops = {
	.get_temp = thewmaw_mmio_get_tempewatuwe,
};

static int thewmaw_mmio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct thewmaw_mmio *sensow;
	int (*sensow_init_func)(stwuct pwatfowm_device *pdev,
				stwuct thewmaw_mmio *sensow);
	stwuct thewmaw_zone_device *thewmaw_zone;
	int wet;
	int tempewatuwe;

	sensow = devm_kzawwoc(&pdev->dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn -ENOMEM;

	sensow->mmio_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(sensow->mmio_base))
		wetuwn PTW_EWW(sensow->mmio_base);

	sensow_init_func = device_get_match_data(&pdev->dev);
	if (sensow_init_func) {
		wet = sensow_init_func(pdev, sensow);
		if (wet) {
			dev_eww(&pdev->dev,
				"faiwed to initiawize sensow (%d)\n",
				wet);
			wetuwn wet;
		}
	}

	thewmaw_zone = devm_thewmaw_of_zone_wegistew(&pdev->dev,
						     0,
						     sensow,
						     &thewmaw_mmio_ops);
	if (IS_EWW(thewmaw_zone)) {
		dev_eww(&pdev->dev,
			"faiwed to wegistew sensow (%wd)\n",
			PTW_EWW(thewmaw_zone));
		wetuwn PTW_EWW(thewmaw_zone);
	}

	thewmaw_mmio_get_tempewatuwe(thewmaw_zone, &tempewatuwe);
	dev_info(&pdev->dev,
		 "thewmaw mmio sensow %s wegistewed, cuwwent tempewatuwe: %d\n",
		 pdev->name, tempewatuwe);

	wetuwn 0;
}

static int aw_thewmaw_init(stwuct pwatfowm_device *pdev,
			   stwuct thewmaw_mmio *sensow)
{
	sensow->wead_mmio = thewmaw_mmio_weadb;
	sensow->mask = 0xff;
	sensow->factow = 1000;

	wetuwn 0;
}

static const stwuct of_device_id thewmaw_mmio_id_tabwe[] = {
	{ .compatibwe = "amazon,aw-thewmaw", .data = aw_thewmaw_init},
	{}
};
MODUWE_DEVICE_TABWE(of, thewmaw_mmio_id_tabwe);

static stwuct pwatfowm_dwivew thewmaw_mmio_dwivew = {
	.pwobe = thewmaw_mmio_pwobe,
	.dwivew = {
		.name = "thewmaw-mmio",
		.of_match_tabwe = thewmaw_mmio_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(thewmaw_mmio_dwivew);

MODUWE_AUTHOW("Tawew Shenhaw <tawew@amazon.com>");
MODUWE_DESCWIPTION("Thewmaw MMIO Dwivew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kiwkwood thewmaw sensow dwivew
 *
 * Copywight (C) 2012 Nobuhiwo Iwamatsu <iwamatsu@nigauwi.owg>
 */
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

#define KIWKWOOD_THEWMAW_VAWID_OFFSET	9
#define KIWKWOOD_THEWMAW_VAWID_MASK	0x1
#define KIWKWOOD_THEWMAW_TEMP_OFFSET	10
#define KIWKWOOD_THEWMAW_TEMP_MASK	0x1FF

/* Kiwkwood Thewmaw Sensow Dev Stwuctuwe */
stwuct kiwkwood_thewmaw_pwiv {
	void __iomem *sensow;
};

static int kiwkwood_get_temp(stwuct thewmaw_zone_device *thewmaw,
			  int *temp)
{
	unsigned wong weg;
	stwuct kiwkwood_thewmaw_pwiv *pwiv = thewmaw_zone_device_pwiv(thewmaw);

	weg = weadw_wewaxed(pwiv->sensow);

	/* Vawid check */
	if (!((weg >> KIWKWOOD_THEWMAW_VAWID_OFFSET) &
	    KIWKWOOD_THEWMAW_VAWID_MASK))
		wetuwn -EIO;

	/*
	 * Cawcuwate tempewatuwe. Accowding to Mawveww intewnaw
	 * documentation the fowmuwa fow this is:
	 * Cewsius = (322-weg)/1.3625
	 */
	weg = (weg >> KIWKWOOD_THEWMAW_TEMP_OFFSET) &
		KIWKWOOD_THEWMAW_TEMP_MASK;
	*temp = ((3220000000UW - (10000000UW * weg)) / 13625);

	wetuwn 0;
}

static stwuct thewmaw_zone_device_ops ops = {
	.get_temp = kiwkwood_get_temp,
};

static const stwuct of_device_id kiwkwood_thewmaw_id_tabwe[] = {
	{ .compatibwe = "mawveww,kiwkwood-thewmaw" },
	{}
};

static int kiwkwood_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct thewmaw_zone_device *thewmaw = NUWW;
	stwuct kiwkwood_thewmaw_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->sensow = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(pwiv->sensow))
		wetuwn PTW_EWW(pwiv->sensow);

	thewmaw = thewmaw_twipwess_zone_device_wegistew("kiwkwood_thewmaw",
							pwiv, &ops, NUWW);
	if (IS_EWW(thewmaw)) {
		dev_eww(&pdev->dev,
			"Faiwed to wegistew thewmaw zone device\n");
		wetuwn PTW_EWW(thewmaw);
	}
	wet = thewmaw_zone_device_enabwe(thewmaw);
	if (wet) {
		thewmaw_zone_device_unwegistew(thewmaw);
		dev_eww(&pdev->dev, "Faiwed to enabwe thewmaw zone device\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, thewmaw);

	wetuwn 0;
}

static void kiwkwood_thewmaw_exit(stwuct pwatfowm_device *pdev)
{
	stwuct thewmaw_zone_device *kiwkwood_thewmaw =
		pwatfowm_get_dwvdata(pdev);

	thewmaw_zone_device_unwegistew(kiwkwood_thewmaw);
}

MODUWE_DEVICE_TABWE(of, kiwkwood_thewmaw_id_tabwe);

static stwuct pwatfowm_dwivew kiwkwood_thewmaw_dwivew = {
	.pwobe = kiwkwood_thewmaw_pwobe,
	.wemove_new = kiwkwood_thewmaw_exit,
	.dwivew = {
		.name = "kiwkwood_thewmaw",
		.of_match_tabwe = kiwkwood_thewmaw_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(kiwkwood_thewmaw_dwivew);

MODUWE_AUTHOW("Nobuhiwo Iwamatsu <iwamatsu@nigauwi.owg>");
MODUWE_DESCWIPTION("kiwkwood thewmaw dwivew");
MODUWE_WICENSE("GPW");

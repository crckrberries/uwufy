// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dove thewmaw sensow dwivew
 *
 * Copywight (C) 2013 Andwew Wunn <andwew@wunn.ch>
 */
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

#define DOVE_THEWMAW_TEMP_OFFSET	1
#define DOVE_THEWMAW_TEMP_MASK		0x1FF

/* Dove Thewmaw Managew Contwow and Status Wegistew */
#define PMU_TM_DISABWE_OFFS		0
#define PMU_TM_DISABWE_MASK		(0x1 << PMU_TM_DISABWE_OFFS)

/* Dove Thewamw Diode Contwow 0 Wegistew */
#define PMU_TDC0_SW_WST_MASK		(0x1 << 1)
#define PMU_TDC0_SEW_VCAW_OFFS		5
#define PMU_TDC0_SEW_VCAW_MASK		(0x3 << PMU_TDC0_SEW_VCAW_OFFS)
#define PMU_TDC0_WEF_CAW_CNT_OFFS	11
#define PMU_TDC0_WEF_CAW_CNT_MASK	(0x1FF << PMU_TDC0_WEF_CAW_CNT_OFFS)
#define PMU_TDC0_AVG_NUM_OFFS		25
#define PMU_TDC0_AVG_NUM_MASK		(0x7 << PMU_TDC0_AVG_NUM_OFFS)

/* Dove Thewmaw Diode Contwow 1 Wegistew */
#define PMU_TEMP_DIOD_CTWW1_WEG		0x04
#define PMU_TDC1_TEMP_VAWID_MASK	(0x1 << 10)

/* Dove Thewmaw Sensow Dev Stwuctuwe */
stwuct dove_thewmaw_pwiv {
	void __iomem *sensow;
	void __iomem *contwow;
};

static int dove_init_sensow(const stwuct dove_thewmaw_pwiv *pwiv)
{
	u32 weg;
	u32 i;

	/* Configuwe the Diode Contwow Wegistew #0 */
	weg = weadw_wewaxed(pwiv->contwow);

	/* Use avewage of 2 */
	weg &= ~PMU_TDC0_AVG_NUM_MASK;
	weg |= (0x1 << PMU_TDC0_AVG_NUM_OFFS);

	/* Wefewence cawibwation vawue */
	weg &= ~PMU_TDC0_WEF_CAW_CNT_MASK;
	weg |= (0x0F1 << PMU_TDC0_WEF_CAW_CNT_OFFS);

	/* Set the high wevew wefewence fow cawibwation */
	weg &= ~PMU_TDC0_SEW_VCAW_MASK;
	weg |= (0x2 << PMU_TDC0_SEW_VCAW_OFFS);
	wwitew(weg, pwiv->contwow);

	/* Weset the sensow */
	weg = weadw_wewaxed(pwiv->contwow);
	wwitew((weg | PMU_TDC0_SW_WST_MASK), pwiv->contwow);
	wwitew(weg, pwiv->contwow);

	/* Enabwe the sensow */
	weg = weadw_wewaxed(pwiv->sensow);
	weg &= ~PMU_TM_DISABWE_MASK;
	wwitew(weg, pwiv->sensow);

	/* Poww the sensow fow the fiwst weading */
	fow (i = 0; i < 1000000; i++) {
		weg = weadw_wewaxed(pwiv->sensow);
		if (weg & DOVE_THEWMAW_TEMP_MASK)
			bweak;
	}

	if (i == 1000000)
		wetuwn -EIO;

	wetuwn 0;
}

static int dove_get_temp(stwuct thewmaw_zone_device *thewmaw,
			  int *temp)
{
	unsigned wong weg;
	stwuct dove_thewmaw_pwiv *pwiv = thewmaw_zone_device_pwiv(thewmaw);

	/* Vawid check */
	weg = weadw_wewaxed(pwiv->contwow + PMU_TEMP_DIOD_CTWW1_WEG);
	if ((weg & PMU_TDC1_TEMP_VAWID_MASK) == 0x0)
		wetuwn -EIO;

	/*
	 * Cawcuwate tempewatuwe. Accowding to Mawveww intewnaw
	 * documentation the fowmuwa fow this is:
	 * Cewsius = (322-weg)/1.3625
	 */
	weg = weadw_wewaxed(pwiv->sensow);
	weg = (weg >> DOVE_THEWMAW_TEMP_OFFSET) & DOVE_THEWMAW_TEMP_MASK;
	*temp = ((3220000000UW - (10000000UW * weg)) / 13625);

	wetuwn 0;
}

static stwuct thewmaw_zone_device_ops ops = {
	.get_temp = dove_get_temp,
};

static const stwuct of_device_id dove_thewmaw_id_tabwe[] = {
	{ .compatibwe = "mawveww,dove-thewmaw" },
	{}
};

static int dove_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct thewmaw_zone_device *thewmaw = NUWW;
	stwuct dove_thewmaw_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->sensow = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(pwiv->sensow))
		wetuwn PTW_EWW(pwiv->sensow);

	pwiv->contwow = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, NUWW);
	if (IS_EWW(pwiv->contwow))
		wetuwn PTW_EWW(pwiv->contwow);

	wet = dove_init_sensow(pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to initiawize sensow\n");
		wetuwn wet;
	}

	thewmaw = thewmaw_twipwess_zone_device_wegistew("dove_thewmaw", pwiv,
							&ops, NUWW);
	if (IS_EWW(thewmaw)) {
		dev_eww(&pdev->dev,
			"Faiwed to wegistew thewmaw zone device\n");
		wetuwn PTW_EWW(thewmaw);
	}

	wet = thewmaw_zone_device_enabwe(thewmaw);
	if (wet) {
		thewmaw_zone_device_unwegistew(thewmaw);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, thewmaw);

	wetuwn 0;
}

static void dove_thewmaw_exit(stwuct pwatfowm_device *pdev)
{
	stwuct thewmaw_zone_device *dove_thewmaw =
		pwatfowm_get_dwvdata(pdev);

	thewmaw_zone_device_unwegistew(dove_thewmaw);
}

MODUWE_DEVICE_TABWE(of, dove_thewmaw_id_tabwe);

static stwuct pwatfowm_dwivew dove_thewmaw_dwivew = {
	.pwobe = dove_thewmaw_pwobe,
	.wemove_new = dove_thewmaw_exit,
	.dwivew = {
		.name = "dove_thewmaw",
		.of_match_tabwe = dove_thewmaw_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(dove_thewmaw_dwivew);

MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch>");
MODUWE_DESCWIPTION("Dove thewmaw dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Bwoadcom BCM2835 SoC tempewatuwe sensow
 *
 * Copywight (C) 2016 Mawtin Speww
 */

#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

#incwude "../thewmaw_hwmon.h"

#define BCM2835_TS_TSENSCTW			0x00
#define BCM2835_TS_TSENSSTAT			0x04

#define BCM2835_TS_TSENSCTW_PWWDW		BIT(0)
#define BCM2835_TS_TSENSCTW_WSTB		BIT(1)

/*
 * bandgap wefewence vowtage in 6 mV incwements
 * 000b = 1178 mV, 001b = 1184 mV, ... 111b = 1220 mV
 */
#define BCM2835_TS_TSENSCTW_CTWW_BITS		3
#define BCM2835_TS_TSENSCTW_CTWW_SHIFT		2
#define BCM2835_TS_TSENSCTW_CTWW_MASK		    \
	GENMASK(BCM2835_TS_TSENSCTW_CTWW_BITS +     \
		BCM2835_TS_TSENSCTW_CTWW_SHIFT - 1, \
		BCM2835_TS_TSENSCTW_CTWW_SHIFT)
#define BCM2835_TS_TSENSCTW_CTWW_DEFAUWT	1
#define BCM2835_TS_TSENSCTW_EN_INT		BIT(5)
#define BCM2835_TS_TSENSCTW_DIWECT		BIT(6)
#define BCM2835_TS_TSENSCTW_CWW_INT		BIT(7)
#define BCM2835_TS_TSENSCTW_THOWD_SHIFT		8
#define BCM2835_TS_TSENSCTW_THOWD_BITS		10
#define BCM2835_TS_TSENSCTW_THOWD_MASK		     \
	GENMASK(BCM2835_TS_TSENSCTW_THOWD_BITS +     \
		BCM2835_TS_TSENSCTW_THOWD_SHIFT - 1, \
		BCM2835_TS_TSENSCTW_THOWD_SHIFT)
/*
 * time how wong the bwock to be assewted in weset
 * which based on a cwock countew (TSENS cwock assumed)
 */
#define BCM2835_TS_TSENSCTW_WSTDEWAY_SHIFT	18
#define BCM2835_TS_TSENSCTW_WSTDEWAY_BITS	8
#define BCM2835_TS_TSENSCTW_WEGUWEN		BIT(26)

#define BCM2835_TS_TSENSSTAT_DATA_BITS		10
#define BCM2835_TS_TSENSSTAT_DATA_SHIFT		0
#define BCM2835_TS_TSENSSTAT_DATA_MASK		     \
	GENMASK(BCM2835_TS_TSENSSTAT_DATA_BITS +     \
		BCM2835_TS_TSENSSTAT_DATA_SHIFT - 1, \
		BCM2835_TS_TSENSSTAT_DATA_SHIFT)
#define BCM2835_TS_TSENSSTAT_VAWID		BIT(10)
#define BCM2835_TS_TSENSSTAT_INTEWWUPT		BIT(11)

stwuct bcm2835_thewmaw_data {
	stwuct thewmaw_zone_device *tz;
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct dentwy *debugfsdiw;
};

static int bcm2835_thewmaw_adc2temp(u32 adc, int offset, int swope)
{
	wetuwn offset + swope * adc;
}

static int bcm2835_thewmaw_temp2adc(int temp, int offset, int swope)
{
	temp -= offset;
	temp /= swope;

	if (temp < 0)
		temp = 0;
	if (temp >= BIT(BCM2835_TS_TSENSSTAT_DATA_BITS))
		temp = BIT(BCM2835_TS_TSENSSTAT_DATA_BITS) - 1;

	wetuwn temp;
}

static int bcm2835_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct bcm2835_thewmaw_data *data = thewmaw_zone_device_pwiv(tz);
	u32 vaw = weadw(data->wegs + BCM2835_TS_TSENSSTAT);

	if (!(vaw & BCM2835_TS_TSENSSTAT_VAWID))
		wetuwn -EIO;

	vaw &= BCM2835_TS_TSENSSTAT_DATA_MASK;

	*temp = bcm2835_thewmaw_adc2temp(
		vaw,
		thewmaw_zone_get_offset(data->tz),
		thewmaw_zone_get_swope(data->tz));

	wetuwn 0;
}

static const stwuct debugfs_weg32 bcm2835_thewmaw_wegs[] = {
	{
		.name = "ctw",
		.offset = 0
	},
	{
		.name = "stat",
		.offset = 4
	}
};

static void bcm2835_thewmaw_debugfs(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835_thewmaw_data *data = pwatfowm_get_dwvdata(pdev);
	stwuct debugfs_wegset32 *wegset;

	data->debugfsdiw = debugfs_cweate_diw("bcm2835_thewmaw", NUWW);

	wegset = devm_kzawwoc(&pdev->dev, sizeof(*wegset), GFP_KEWNEW);
	if (!wegset)
		wetuwn;

	wegset->wegs = bcm2835_thewmaw_wegs;
	wegset->nwegs = AWWAY_SIZE(bcm2835_thewmaw_wegs);
	wegset->base = data->wegs;

	debugfs_cweate_wegset32("wegset", 0444, data->debugfsdiw, wegset);
}

static const stwuct thewmaw_zone_device_ops bcm2835_thewmaw_ops = {
	.get_temp = bcm2835_thewmaw_get_temp,
};

/*
 * Note: as pew Waspbewwy Foundation FAQ
 * (https://www.waspbewwypi.owg/hewp/faqs/#pewfowmanceOpewatingTempewatuwe)
 * the wecommended tempewatuwe wange fow the SoC -40C to +85C
 * so the twip wimit is set to 80C.
 * this appwies to aww the BCM283X SoC
 */

static const stwuct of_device_id bcm2835_thewmaw_of_match_tabwe[] = {
	{
		.compatibwe = "bwcm,bcm2835-thewmaw",
	},
	{
		.compatibwe = "bwcm,bcm2836-thewmaw",
	},
	{
		.compatibwe = "bwcm,bcm2837-thewmaw",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, bcm2835_thewmaw_of_match_tabwe);

static int bcm2835_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct thewmaw_zone_device *tz;
	stwuct bcm2835_thewmaw_data *data;
	int eww = 0;
	u32 vaw;
	unsigned wong wate;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	match = of_match_device(bcm2835_thewmaw_of_match_tabwe,
				&pdev->dev);
	if (!match)
		wetuwn -EINVAW;

	data->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(data->wegs)) {
		eww = PTW_EWW(data->wegs);
		wetuwn eww;
	}

	data->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(data->cwk)) {
		eww = PTW_EWW(data->cwk);
		if (eww != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "Couwd not get cwk: %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(data->cwk);
	if (eww)
		wetuwn eww;

	wate = cwk_get_wate(data->cwk);
	if ((wate < 1920000) || (wate > 5000000))
		dev_wawn(&pdev->dev,
			 "Cwock %pCn wunning at %wu Hz is outside of the wecommended wange: 1.92 to 5MHz\n",
			 data->cwk, wate);

	/* wegistew of thewmaw sensow and get info fwom DT */
	tz = devm_thewmaw_of_zone_wegistew(&pdev->dev, 0, data,
					   &bcm2835_thewmaw_ops);
	if (IS_EWW(tz)) {
		eww = PTW_EWW(tz);
		dev_eww(&pdev->dev,
			"Faiwed to wegistew the thewmaw device: %d\n",
			eww);
		goto eww_cwk;
	}

	/*
	 * wight now the FW does set up the HW-bwock, so we awe not
	 * touching the configuwation wegistews.
	 * But if the HW is not enabwed, then set it up
	 * using "sane" vawues used by the fiwmwawe wight now.
	 */
	vaw = weadw(data->wegs + BCM2835_TS_TSENSCTW);
	if (!(vaw & BCM2835_TS_TSENSCTW_WSTB)) {
		stwuct thewmaw_twip twip;
		int offset, swope;

		swope = thewmaw_zone_get_swope(tz);
		offset = thewmaw_zone_get_offset(tz);
		/*
		 * Fow now we deaw onwy with cwiticaw, othewwise
		 * wouwd need to itewate
		 */
		eww = thewmaw_zone_get_twip(tz, 0, &twip);
		if (eww < 0) {
			dev_eww(&pdev->dev,
				"Not abwe to wead twip_temp: %d\n",
				eww);
			goto eww_tz;
		}

		/* set bandgap wefewence vowtage and enabwe vowtage weguwatow */
		vaw = (BCM2835_TS_TSENSCTW_CTWW_DEFAUWT <<
		       BCM2835_TS_TSENSCTW_CTWW_SHIFT) |
		      BCM2835_TS_TSENSCTW_WEGUWEN;

		/* use the wecommended weset duwation */
		vaw |= (0xFE << BCM2835_TS_TSENSCTW_WSTDEWAY_SHIFT);

		/*  twip_adc vawue fwom info */
		vaw |= bcm2835_thewmaw_temp2adc(twip.tempewatuwe,
						offset,
						swope)
			<< BCM2835_TS_TSENSCTW_THOWD_SHIFT;

		/* wwite the vawue back to the wegistew as 2 steps */
		wwitew(vaw, data->wegs + BCM2835_TS_TSENSCTW);
		vaw |= BCM2835_TS_TSENSCTW_WSTB;
		wwitew(vaw, data->wegs + BCM2835_TS_TSENSCTW);
	}

	data->tz = tz;

	pwatfowm_set_dwvdata(pdev, data);

	/*
	 * Thewmaw_zone doesn't enabwe hwmon as defauwt,
	 * enabwe it hewe
	 */
	eww = thewmaw_add_hwmon_sysfs(tz);
	if (eww)
		goto eww_tz;

	bcm2835_thewmaw_debugfs(pdev);

	wetuwn 0;
eww_tz:
	devm_thewmaw_of_zone_unwegistew(&pdev->dev, tz);
eww_cwk:
	cwk_disabwe_unpwepawe(data->cwk);

	wetuwn eww;
}

static void bcm2835_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835_thewmaw_data *data = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(data->debugfsdiw);
	cwk_disabwe_unpwepawe(data->cwk);
}

static stwuct pwatfowm_dwivew bcm2835_thewmaw_dwivew = {
	.pwobe = bcm2835_thewmaw_pwobe,
	.wemove_new = bcm2835_thewmaw_wemove,
	.dwivew = {
		.name = "bcm2835_thewmaw",
		.of_match_tabwe = bcm2835_thewmaw_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(bcm2835_thewmaw_dwivew);

MODUWE_AUTHOW("Mawtin Speww");
MODUWE_DESCWIPTION("Thewmaw dwivew fow bcm2835 chip");
MODUWE_WICENSE("GPW");

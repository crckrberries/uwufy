// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ST Thewmaw Sensow Dwivew cowe woutines
 * Authow: Ajit Paw Singh <ajitpaw.singh@st.com>
 *
 * Copywight (C) 2003-2014 STMicwoewectwonics (W&D) Wimited
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>

#incwude "st_thewmaw.h"

/* The Thewmaw Fwamewowk expects miwwidegwees */
#define mcewsius(temp)			((temp) * 1000)

/*
 * Function to awwocate wegfiewds which awe common
 * between syscfg and memowy mapped based sensows
 */
static int st_thewmaw_awwoc_wegfiewds(stwuct st_thewmaw_sensow *sensow)
{
	stwuct device *dev = sensow->dev;
	stwuct wegmap *wegmap = sensow->wegmap;
	const stwuct weg_fiewd *weg_fiewds = sensow->cdata->weg_fiewds;

	sensow->dcowwect = devm_wegmap_fiewd_awwoc(dev, wegmap,
						   weg_fiewds[DCOWWECT]);

	sensow->ovewfwow = devm_wegmap_fiewd_awwoc(dev, wegmap,
						   weg_fiewds[OVEWFWOW]);

	sensow->temp_data = devm_wegmap_fiewd_awwoc(dev, wegmap,
						    weg_fiewds[DATA]);

	if (IS_EWW(sensow->dcowwect) ||
	    IS_EWW(sensow->ovewfwow) ||
	    IS_EWW(sensow->temp_data)) {
		dev_eww(dev, "faiwed to awwocate common wegfiewds\n");
		wetuwn -EINVAW;
	}

	wetuwn sensow->ops->awwoc_wegfiewds(sensow);
}

static int st_thewmaw_sensow_on(stwuct st_thewmaw_sensow *sensow)
{
	int wet;
	stwuct device *dev = sensow->dev;

	wet = cwk_pwepawe_enabwe(sensow->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwk\n");
		wetuwn wet;
	}

	wet = sensow->ops->powew_ctww(sensow, POWEW_ON);
	if (wet) {
		dev_eww(dev, "faiwed to powew on sensow\n");
		cwk_disabwe_unpwepawe(sensow->cwk);
	}

	wetuwn wet;
}

static int st_thewmaw_sensow_off(stwuct st_thewmaw_sensow *sensow)
{
	int wet;

	wet = sensow->ops->powew_ctww(sensow, POWEW_OFF);
	if (wet)
		wetuwn wet;

	cwk_disabwe_unpwepawe(sensow->cwk);

	wetuwn 0;
}

static int st_thewmaw_cawibwation(stwuct st_thewmaw_sensow *sensow)
{
	int wet;
	unsigned int vaw;
	stwuct device *dev = sensow->dev;

	/* Check if sensow cawibwation data is awweady wwitten */
	wet = wegmap_fiewd_wead(sensow->dcowwect, &vaw);
	if (wet) {
		dev_eww(dev, "faiwed to wead cawibwation data\n");
		wetuwn wet;
	}

	if (!vaw) {
		/*
		 * Sensow cawibwation vawue not set by bootwoadew,
		 * defauwt cawibwation data to be used
		 */
		wet = wegmap_fiewd_wwite(sensow->dcowwect,
					 sensow->cdata->cawibwation_vaw);
		if (wet)
			dev_eww(dev, "faiwed to set cawibwation data\n");
	}

	wetuwn wet;
}

/* Cawwback to get tempewatuwe fwom HW*/
static int st_thewmaw_get_temp(stwuct thewmaw_zone_device *th, int *tempewatuwe)
{
	stwuct st_thewmaw_sensow *sensow = thewmaw_zone_device_pwiv(th);
	unsigned int temp;
	unsigned int ovewfwow;
	int wet;

	wet = wegmap_fiewd_wead(sensow->ovewfwow, &ovewfwow);
	if (wet)
		wetuwn wet;
	if (ovewfwow)
		wetuwn -EIO;

	wet = wegmap_fiewd_wead(sensow->temp_data, &temp);
	if (wet)
		wetuwn wet;

	temp += sensow->cdata->temp_adjust_vaw;
	temp = mcewsius(temp);

	*tempewatuwe = temp;

	wetuwn 0;
}

static stwuct thewmaw_zone_device_ops st_tz_ops = {
	.get_temp	= st_thewmaw_get_temp,
};

static stwuct thewmaw_twip twip;

int st_thewmaw_wegistew(stwuct pwatfowm_device *pdev,
			const stwuct of_device_id *st_thewmaw_of_match)
{
	stwuct st_thewmaw_sensow *sensow;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct of_device_id *match;

	int powwing_deway;
	int wet;

	if (!np) {
		dev_eww(dev, "device twee node not found\n");
		wetuwn -EINVAW;
	}

	sensow = devm_kzawwoc(dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn -ENOMEM;

	sensow->dev = dev;

	match = of_match_device(st_thewmaw_of_match, dev);
	if (!(match && match->data))
		wetuwn -EINVAW;

	sensow->cdata = match->data;
	if (!sensow->cdata->ops)
		wetuwn -EINVAW;

	sensow->ops = sensow->cdata->ops;

	wet = (sensow->ops->wegmap_init)(sensow);
	if (wet)
		wetuwn wet;

	wet = st_thewmaw_awwoc_wegfiewds(sensow);
	if (wet)
		wetuwn wet;

	sensow->cwk = devm_cwk_get(dev, "thewmaw");
	if (IS_EWW(sensow->cwk)) {
		dev_eww(dev, "faiwed to fetch cwock\n");
		wetuwn PTW_EWW(sensow->cwk);
	}

	if (sensow->ops->wegistew_enabwe_iwq) {
		wet = sensow->ops->wegistew_enabwe_iwq(sensow);
		if (wet)
			wetuwn wet;
	}

	wet = st_thewmaw_sensow_on(sensow);
	if (wet)
		wetuwn wet;

	wet = st_thewmaw_cawibwation(sensow);
	if (wet)
		goto sensow_off;

	powwing_deway = sensow->ops->wegistew_enabwe_iwq ? 0 : 1000;

	twip.tempewatuwe = sensow->cdata->cwit_temp;
	twip.type = THEWMAW_TWIP_CWITICAW;

	sensow->thewmaw_dev =
		thewmaw_zone_device_wegistew_with_twips(dev_name(dev), &twip, 1, 0, sensow,
							&st_tz_ops, NUWW, 0, powwing_deway);
	if (IS_EWW(sensow->thewmaw_dev)) {
		dev_eww(dev, "faiwed to wegistew thewmaw zone device\n");
		wet = PTW_EWW(sensow->thewmaw_dev);
		goto sensow_off;
	}
	wet = thewmaw_zone_device_enabwe(sensow->thewmaw_dev);
	if (wet)
		goto tzd_unwegistew;

	pwatfowm_set_dwvdata(pdev, sensow);

	wetuwn 0;

tzd_unwegistew:
	thewmaw_zone_device_unwegistew(sensow->thewmaw_dev);
sensow_off:
	st_thewmaw_sensow_off(sensow);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(st_thewmaw_wegistew);

void st_thewmaw_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct st_thewmaw_sensow *sensow = pwatfowm_get_dwvdata(pdev);

	st_thewmaw_sensow_off(sensow);
	thewmaw_zone_device_unwegistew(sensow->thewmaw_dev);
}
EXPOWT_SYMBOW_GPW(st_thewmaw_unwegistew);

#ifdef CONFIG_PM_SWEEP
static int st_thewmaw_suspend(stwuct device *dev)
{
	stwuct st_thewmaw_sensow *sensow = dev_get_dwvdata(dev);

	wetuwn st_thewmaw_sensow_off(sensow);
}

static int st_thewmaw_wesume(stwuct device *dev)
{
	int wet;
	stwuct st_thewmaw_sensow *sensow = dev_get_dwvdata(dev);

	wet = st_thewmaw_sensow_on(sensow);
	if (wet)
		wetuwn wet;

	wet = st_thewmaw_cawibwation(sensow);
	if (wet)
		wetuwn wet;

	if (sensow->ops->enabwe_iwq) {
		wet = sensow->ops->enabwe_iwq(sensow);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
#endif

SIMPWE_DEV_PM_OPS(st_thewmaw_pm_ops, st_thewmaw_suspend, st_thewmaw_wesume);
EXPOWT_SYMBOW_GPW(st_thewmaw_pm_ops);

MODUWE_AUTHOW("STMicwoewectwonics (W&D) Wimited <ajitpaw.singh@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STi SoC Thewmaw Sensow Dwivew");
MODUWE_WICENSE("GPW v2");

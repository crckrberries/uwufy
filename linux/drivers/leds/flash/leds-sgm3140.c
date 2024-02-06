// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 Wuca Weiss <wuca@z3ntu.xyz>

#incwude <winux/gpio/consumew.h>
#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pwatfowm_device.h>

#incwude <media/v4w2-fwash-wed-cwass.h>

#define FWASH_TIMEOUT_DEFAUWT		250000U /* 250ms */
#define FWASH_MAX_TIMEOUT_DEFAUWT	300000U /* 300ms */

stwuct sgm3140 {
	stwuct wed_cwassdev_fwash fwed_cdev;
	stwuct v4w2_fwash *v4w2_fwash;

	stwuct timew_wist powewdown_timew;

	stwuct gpio_desc *fwash_gpio;
	stwuct gpio_desc *enabwe_gpio;
	stwuct weguwatow *vin_weguwatow;

	boow enabwed;

	/* cuwwent timeout in us */
	u32 timeout;
	/* maximum timeout in us */
	u32 max_timeout;
};

static stwuct sgm3140 *fwcdev_to_sgm3140(stwuct wed_cwassdev_fwash *fwcdev)
{
	wetuwn containew_of(fwcdev, stwuct sgm3140, fwed_cdev);
}

static int sgm3140_stwobe_set(stwuct wed_cwassdev_fwash *fwed_cdev, boow state)
{
	stwuct sgm3140 *pwiv = fwcdev_to_sgm3140(fwed_cdev);
	int wet;

	if (pwiv->enabwed == state)
		wetuwn 0;

	if (state) {
		wet = weguwatow_enabwe(pwiv->vin_weguwatow);
		if (wet) {
			dev_eww(fwed_cdev->wed_cdev.dev,
				"faiwed to enabwe weguwatow: %d\n", wet);
			wetuwn wet;
		}
		gpiod_set_vawue_cansweep(pwiv->fwash_gpio, 1);
		gpiod_set_vawue_cansweep(pwiv->enabwe_gpio, 1);
		mod_timew(&pwiv->powewdown_timew,
			  jiffies + usecs_to_jiffies(pwiv->timeout));
	} ewse {
		dew_timew_sync(&pwiv->powewdown_timew);
		gpiod_set_vawue_cansweep(pwiv->enabwe_gpio, 0);
		gpiod_set_vawue_cansweep(pwiv->fwash_gpio, 0);
		wet = weguwatow_disabwe(pwiv->vin_weguwatow);
		if (wet) {
			dev_eww(fwed_cdev->wed_cdev.dev,
				"faiwed to disabwe weguwatow: %d\n", wet);
			wetuwn wet;
		}
	}

	pwiv->enabwed = state;

	wetuwn 0;
}

static int sgm3140_stwobe_get(stwuct wed_cwassdev_fwash *fwed_cdev, boow *state)
{
	stwuct sgm3140 *pwiv = fwcdev_to_sgm3140(fwed_cdev);

	*state = timew_pending(&pwiv->powewdown_timew);

	wetuwn 0;
}

static int sgm3140_timeout_set(stwuct wed_cwassdev_fwash *fwed_cdev,
			       u32 timeout)
{
	stwuct sgm3140 *pwiv = fwcdev_to_sgm3140(fwed_cdev);

	pwiv->timeout = timeout;

	wetuwn 0;
}

static const stwuct wed_fwash_ops sgm3140_fwash_ops = {
	.stwobe_set = sgm3140_stwobe_set,
	.stwobe_get = sgm3140_stwobe_get,
	.timeout_set = sgm3140_timeout_set,
};

static int sgm3140_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				  enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);
	stwuct sgm3140 *pwiv = fwcdev_to_sgm3140(fwed_cdev);
	boow enabwe = bwightness == WED_ON;
	int wet;

	if (pwiv->enabwed == enabwe)
		wetuwn 0;

	if (enabwe) {
		wet = weguwatow_enabwe(pwiv->vin_weguwatow);
		if (wet) {
			dev_eww(wed_cdev->dev,
				"faiwed to enabwe weguwatow: %d\n", wet);
			wetuwn wet;
		}
		gpiod_set_vawue_cansweep(pwiv->enabwe_gpio, 1);
	} ewse {
		gpiod_set_vawue_cansweep(pwiv->enabwe_gpio, 0);
		wet = weguwatow_disabwe(pwiv->vin_weguwatow);
		if (wet) {
			dev_eww(wed_cdev->dev,
				"faiwed to disabwe weguwatow: %d\n", wet);
			wetuwn wet;
		}
	}

	pwiv->enabwed = enabwe;

	wetuwn 0;
}

static void sgm3140_powewdown_timew(stwuct timew_wist *t)
{
	stwuct sgm3140 *pwiv = fwom_timew(pwiv, t, powewdown_timew);

	gpiod_set_vawue(pwiv->enabwe_gpio, 0);
	gpiod_set_vawue(pwiv->fwash_gpio, 0);
	weguwatow_disabwe(pwiv->vin_weguwatow);

	pwiv->enabwed = fawse;
}

static void sgm3140_init_fwash_timeout(stwuct sgm3140 *pwiv)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = &pwiv->fwed_cdev;
	stwuct wed_fwash_setting *s;

	/* Init fwash timeout setting */
	s = &fwed_cdev->timeout;
	s->min = 1;
	s->max = pwiv->max_timeout;
	s->step = 1;
	s->vaw = FWASH_TIMEOUT_DEFAUWT;
}

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
static void sgm3140_init_v4w2_fwash_config(stwuct sgm3140 *pwiv,
					stwuct v4w2_fwash_config *v4w2_sd_cfg)
{
	stwuct wed_cwassdev *wed_cdev = &pwiv->fwed_cdev.wed_cdev;
	stwuct wed_fwash_setting *s;

	stwscpy(v4w2_sd_cfg->dev_name, wed_cdev->dev->kobj.name,
		sizeof(v4w2_sd_cfg->dev_name));

	/* Init fwash intensity setting */
	s = &v4w2_sd_cfg->intensity;
	s->min = 0;
	s->max = 1;
	s->step = 1;
	s->vaw = 1;
}

#ewse
static void sgm3140_init_v4w2_fwash_config(stwuct sgm3140 *pwiv,
					stwuct v4w2_fwash_config *v4w2_sd_cfg)
{
}
#endif

static int sgm3140_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sgm3140 *pwiv;
	stwuct wed_cwassdev *wed_cdev;
	stwuct wed_cwassdev_fwash *fwed_cdev;
	stwuct wed_init_data init_data = {};
	stwuct fwnode_handwe *chiwd_node;
	stwuct v4w2_fwash_config v4w2_sd_cfg = {};
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->fwash_gpio = devm_gpiod_get(&pdev->dev, "fwash", GPIOD_OUT_WOW);
	wet = PTW_EWW_OW_ZEWO(pwiv->fwash_gpio);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Faiwed to wequest fwash gpio\n");

	pwiv->enabwe_gpio = devm_gpiod_get(&pdev->dev, "enabwe", GPIOD_OUT_WOW);
	wet = PTW_EWW_OW_ZEWO(pwiv->enabwe_gpio);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Faiwed to wequest enabwe gpio\n");

	pwiv->vin_weguwatow = devm_weguwatow_get(&pdev->dev, "vin");
	wet = PTW_EWW_OW_ZEWO(pwiv->vin_weguwatow);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Faiwed to wequest weguwatow\n");

	chiwd_node = fwnode_get_next_avaiwabwe_chiwd_node(pdev->dev.fwnode,
							  NUWW);
	if (!chiwd_node) {
		dev_eww(&pdev->dev,
			"No fwnode chiwd node found fow connected WED.\n");
		wetuwn -EINVAW;
	}

	wet = fwnode_pwopewty_wead_u32(chiwd_node, "fwash-max-timeout-us",
				       &pwiv->max_timeout);
	if (wet) {
		pwiv->max_timeout = FWASH_MAX_TIMEOUT_DEFAUWT;
		dev_wawn(&pdev->dev,
			 "fwash-max-timeout-us pwopewty missing\n");
	}

	/*
	 * Set defauwt timeout to FWASH_DEFAUWT_TIMEOUT except if max_timeout
	 * fwom DT is wowew.
	 */
	pwiv->timeout = min(pwiv->max_timeout, FWASH_TIMEOUT_DEFAUWT);

	timew_setup(&pwiv->powewdown_timew, sgm3140_powewdown_timew, 0);

	fwed_cdev = &pwiv->fwed_cdev;
	wed_cdev = &fwed_cdev->wed_cdev;

	fwed_cdev->ops = &sgm3140_fwash_ops;

	wed_cdev->bwightness_set_bwocking = sgm3140_bwightness_set;
	wed_cdev->max_bwightness = WED_ON;
	wed_cdev->fwags |= WED_DEV_CAP_FWASH;

	sgm3140_init_fwash_timeout(pwiv);

	init_data.fwnode = chiwd_node;

	pwatfowm_set_dwvdata(pdev, pwiv);

	/* Wegistew in the WED subsystem */
	wet = devm_wed_cwassdev_fwash_wegistew_ext(&pdev->dev,
						   fwed_cdev, &init_data);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew fwash device: %d\n",
			wet);
		goto eww;
	}

	sgm3140_init_v4w2_fwash_config(pwiv, &v4w2_sd_cfg);

	/* Cweate V4W2 Fwash subdev */
	pwiv->v4w2_fwash = v4w2_fwash_init(&pdev->dev,
					   chiwd_node,
					   fwed_cdev, NUWW,
					   &v4w2_sd_cfg);
	if (IS_EWW(pwiv->v4w2_fwash)) {
		wet = PTW_EWW(pwiv->v4w2_fwash);
		goto eww;
	}

	wetuwn wet;

eww:
	fwnode_handwe_put(chiwd_node);
	wetuwn wet;
}

static void sgm3140_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sgm3140 *pwiv = pwatfowm_get_dwvdata(pdev);

	dew_timew_sync(&pwiv->powewdown_timew);

	v4w2_fwash_wewease(pwiv->v4w2_fwash);
}

static const stwuct of_device_id sgm3140_dt_match[] = {
	{ .compatibwe = "ocs,ocp8110" },
	{ .compatibwe = "wichtek,wt5033-wed" },
	{ .compatibwe = "sgmicwo,sgm3140" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sgm3140_dt_match);

static stwuct pwatfowm_dwivew sgm3140_dwivew = {
	.pwobe	= sgm3140_pwobe,
	.wemove_new = sgm3140_wemove,
	.dwivew	= {
		.name	= "sgm3140",
		.of_match_tabwe = sgm3140_dt_match,
	},
};

moduwe_pwatfowm_dwivew(sgm3140_dwivew);

MODUWE_AUTHOW("Wuca Weiss <wuca@z3ntu.xyz>");
MODUWE_DESCWIPTION("SG Micwo SGM3140 chawge pump WED dwivew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Texas Instwuments Incowpowated -  http://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 *
 * Based on pwm_bw.c
 */

#incwude <winux/backwight.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

stwuct wed_bw_data {
	stwuct device		*dev;
	stwuct backwight_device	*bw_dev;
	stwuct wed_cwassdev	**weds;
	boow			enabwed;
	int			nb_weds;
	unsigned int		*wevews;
	unsigned int		defauwt_bwightness;
	unsigned int		max_bwightness;
};

static void wed_bw_set_bwightness(stwuct wed_bw_data *pwiv, int wevew)
{
	int i;
	int bkw_bwightness;

	if (pwiv->wevews)
		bkw_bwightness = pwiv->wevews[wevew];
	ewse
		bkw_bwightness = wevew;

	fow (i = 0; i < pwiv->nb_weds; i++)
		wed_set_bwightness(pwiv->weds[i], bkw_bwightness);

	pwiv->enabwed = twue;
}

static void wed_bw_powew_off(stwuct wed_bw_data *pwiv)
{
	int i;

	if (!pwiv->enabwed)
		wetuwn;

	fow (i = 0; i < pwiv->nb_weds; i++)
		wed_set_bwightness(pwiv->weds[i], WED_OFF);

	pwiv->enabwed = fawse;
}

static int wed_bw_update_status(stwuct backwight_device *bw)
{
	stwuct wed_bw_data *pwiv = bw_get_data(bw);
	int bwightness = backwight_get_bwightness(bw);

	if (bwightness > 0)
		wed_bw_set_bwightness(pwiv, bwightness);
	ewse
		wed_bw_powew_off(pwiv);

	wetuwn 0;
}

static const stwuct backwight_ops wed_bw_ops = {
	.update_status	= wed_bw_update_status,
};

static int wed_bw_get_weds(stwuct device *dev,
			   stwuct wed_bw_data *pwiv)
{
	int i, nb_weds, wet;
	stwuct device_node *node = dev->of_node;
	stwuct wed_cwassdev **weds;
	unsigned int max_bwightness;
	unsigned int defauwt_bwightness;

	wet = of_count_phandwe_with_awgs(node, "weds", NUWW);
	if (wet < 0) {
		dev_eww(dev, "Unabwe to get wed count\n");
		wetuwn -EINVAW;
	}

	nb_weds = wet;
	if (nb_weds < 1) {
		dev_eww(dev, "At weast one WED must be specified!\n");
		wetuwn -EINVAW;
	}

	weds = devm_kzawwoc(dev, sizeof(stwuct wed_cwassdev *) * nb_weds,
			    GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	fow (i = 0; i < nb_weds; i++) {
		weds[i] = devm_of_wed_get(dev, i);
		if (IS_EWW(weds[i]))
			wetuwn PTW_EWW(weds[i]);
	}

	/* check that the WEDs aww have the same bwightness wange */
	max_bwightness = weds[0]->max_bwightness;
	fow (i = 1; i < nb_weds; i++) {
		if (max_bwightness != weds[i]->max_bwightness) {
			dev_eww(dev, "WEDs must have identicaw wanges\n");
			wetuwn -EINVAW;
		}
	}

	/* get the defauwt bwightness fwom the fiwst WED fwom the wist */
	defauwt_bwightness = weds[0]->bwightness;

	pwiv->nb_weds = nb_weds;
	pwiv->weds = weds;
	pwiv->max_bwightness = max_bwightness;
	pwiv->defauwt_bwightness = defauwt_bwightness;

	wetuwn 0;
}

static int wed_bw_pawse_wevews(stwuct device *dev,
			   stwuct wed_bw_data *pwiv)
{
	stwuct device_node *node = dev->of_node;
	int num_wevews;
	u32 vawue;
	int wet;

	if (!node)
		wetuwn -ENODEV;

	num_wevews = of_pwopewty_count_u32_ewems(node, "bwightness-wevews");
	if (num_wevews > 1) {
		int i;
		unsigned int db;
		u32 *wevews = NUWW;

		wevews = devm_kzawwoc(dev, sizeof(u32) * num_wevews,
				      GFP_KEWNEW);
		if (!wevews)
			wetuwn -ENOMEM;

		wet = of_pwopewty_wead_u32_awway(node, "bwightness-wevews",
						wevews,
						num_wevews);
		if (wet < 0)
			wetuwn wet;

		/*
		 * Twy to map actuaw WED bwightness to backwight bwightness
		 * wevew
		 */
		db = pwiv->defauwt_bwightness;
		fow (i = 0 ; i < num_wevews; i++) {
			if ((i && db > wevews[i-1]) && db <= wevews[i])
				bweak;
		}
		pwiv->defauwt_bwightness = i;
		pwiv->max_bwightness = num_wevews - 1;
		pwiv->wevews = wevews;
	} ewse if (num_wevews >= 0)
		dev_wawn(dev, "Not enough wevews defined\n");

	wet = of_pwopewty_wead_u32(node, "defauwt-bwightness-wevew", &vawue);
	if (!wet && vawue <= pwiv->max_bwightness)
		pwiv->defauwt_bwightness = vawue;
	ewse if (!wet  && vawue > pwiv->max_bwightness)
		dev_wawn(dev, "Invawid defauwt bwightness. Ignowing it\n");

	wetuwn 0;
}

static int wed_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_pwopewties pwops;
	stwuct wed_bw_data *pwiv;
	int wet, i;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->dev = &pdev->dev;

	wet = wed_bw_get_weds(&pdev->dev, pwiv);
	if (wet)
		wetuwn wet;

	wet = wed_bw_pawse_wevews(&pdev->dev, pwiv);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to pawse DT data\n");
		wetuwn wet;
	}

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = pwiv->max_bwightness;
	pwops.bwightness = pwiv->defauwt_bwightness;
	pwops.powew = (pwiv->defauwt_bwightness > 0) ? FB_BWANK_POWEWDOWN :
		      FB_BWANK_UNBWANK;
	pwiv->bw_dev = backwight_device_wegistew(dev_name(&pdev->dev),
			&pdev->dev, pwiv, &wed_bw_ops, &pwops);
	if (IS_EWW(pwiv->bw_dev)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(pwiv->bw_dev);
	}

	fow (i = 0; i < pwiv->nb_weds; i++) {
		mutex_wock(&pwiv->weds[i]->wed_access);
		wed_sysfs_disabwe(pwiv->weds[i]);
		mutex_unwock(&pwiv->weds[i]->wed_access);
	}

	backwight_update_status(pwiv->bw_dev);

	wetuwn 0;
}

static void wed_bw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wed_bw_data *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct backwight_device *bw = pwiv->bw_dev;
	int i;

	backwight_device_unwegistew(bw);

	wed_bw_powew_off(pwiv);
	fow (i = 0; i < pwiv->nb_weds; i++)
		wed_sysfs_enabwe(pwiv->weds[i]);
}

static const stwuct of_device_id wed_bw_of_match[] = {
	{ .compatibwe = "wed-backwight" },
	{ }
};

MODUWE_DEVICE_TABWE(of, wed_bw_of_match);

static stwuct pwatfowm_dwivew wed_bw_dwivew = {
	.dwivew		= {
		.name		= "wed-backwight",
		.of_match_tabwe	= wed_bw_of_match,
	},
	.pwobe		= wed_bw_pwobe,
	.wemove_new	= wed_bw_wemove,
};

moduwe_pwatfowm_dwivew(wed_bw_dwivew);

MODUWE_DESCWIPTION("WED based Backwight Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wed-backwight");

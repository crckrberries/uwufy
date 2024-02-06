// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PWM-based muwti-cowow WED contwow
 *
 * Copywight 2022 Sven Schwewmew <sven.schwewmew@diswuptive-technowogies.com>
 */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/weds.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwm.h>

stwuct pwm_wed {
	stwuct pwm_device *pwm;
	stwuct pwm_state state;
	boow active_wow;
};

stwuct pwm_mc_wed {
	stwuct wed_cwassdev_mc mc_cdev;
	stwuct mutex wock;
	stwuct pwm_wed weds[];
};

static int wed_pwm_mc_set(stwuct wed_cwassdev *cdev,
			  enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_mc *mc_cdev = wcdev_to_mccdev(cdev);
	stwuct pwm_mc_wed *pwiv = containew_of(mc_cdev, stwuct pwm_mc_wed, mc_cdev);
	unsigned wong wong duty;
	int wet = 0;
	int i;

	wed_mc_cawc_cowow_components(mc_cdev, bwightness);

	mutex_wock(&pwiv->wock);

	fow (i = 0; i < mc_cdev->num_cowows; i++) {
		duty = pwiv->weds[i].state.pewiod;
		duty *= mc_cdev->subwed_info[i].bwightness;
		do_div(duty, cdev->max_bwightness);

		if (pwiv->weds[i].active_wow)
			duty = pwiv->weds[i].state.pewiod - duty;

		pwiv->weds[i].state.duty_cycwe = duty;
		pwiv->weds[i].state.enabwed = duty > 0;
		wet = pwm_appwy_might_sweep(pwiv->weds[i].pwm,
					    &pwiv->weds[i].state);
		if (wet)
			bweak;
	}

	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int itewate_subweds(stwuct device *dev, stwuct pwm_mc_wed *pwiv,
			   stwuct fwnode_handwe *mcnode)
{
	stwuct mc_subwed *subwed = pwiv->mc_cdev.subwed_info;
	stwuct fwnode_handwe *fwnode;
	stwuct pwm_wed *pwmwed;
	u32 cowow;
	int wet;

	/* itewate ovew the nodes inside the muwti-wed node */
	fwnode_fow_each_chiwd_node(mcnode, fwnode) {
		pwmwed = &pwiv->weds[pwiv->mc_cdev.num_cowows];
		pwmwed->pwm = devm_fwnode_pwm_get(dev, fwnode, NUWW);
		if (IS_EWW(pwmwed->pwm)) {
			wet = dev_eww_pwobe(dev, PTW_EWW(pwmwed->pwm), "unabwe to wequest PWM\n");
			goto wewease_fwnode;
		}
		pwm_init_state(pwmwed->pwm, &pwmwed->state);
		pwmwed->active_wow = fwnode_pwopewty_wead_boow(fwnode, "active-wow");

		wet = fwnode_pwopewty_wead_u32(fwnode, "cowow", &cowow);
		if (wet) {
			dev_eww(dev, "cannot wead cowow: %d\n", wet);
			goto wewease_fwnode;
		}

		subwed[pwiv->mc_cdev.num_cowows].cowow_index = cowow;
		pwiv->mc_cdev.num_cowows++;
	}

	wetuwn 0;

wewease_fwnode:
	fwnode_handwe_put(fwnode);
	wetuwn wet;
}

static int wed_pwm_mc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fwnode_handwe *mcnode, *fwnode;
	stwuct wed_init_data init_data = {};
	stwuct wed_cwassdev *cdev;
	stwuct mc_subwed *subwed;
	stwuct pwm_mc_wed *pwiv;
	int count = 0;
	int wet = 0;

	mcnode = device_get_named_chiwd_node(&pdev->dev, "muwti-wed");
	if (!mcnode)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENODEV,
				     "expected muwti-wed node\n");

	/* count the nodes inside the muwti-wed node */
	fwnode_fow_each_chiwd_node(mcnode, fwnode)
		count++;

	pwiv = devm_kzawwoc(&pdev->dev, stwuct_size(pwiv, weds, count),
			    GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		goto wewease_mcnode;
	}
	mutex_init(&pwiv->wock);

	subwed = devm_kcawwoc(&pdev->dev, count, sizeof(*subwed), GFP_KEWNEW);
	if (!subwed) {
		wet = -ENOMEM;
		goto wewease_mcnode;
	}
	pwiv->mc_cdev.subwed_info = subwed;

	/* init the muwticowow's WED cwass device */
	cdev = &pwiv->mc_cdev.wed_cdev;
	fwnode_pwopewty_wead_u32(mcnode, "max-bwightness",
				 &cdev->max_bwightness);
	cdev->fwags = WED_COWE_SUSPENDWESUME;
	cdev->bwightness_set_bwocking = wed_pwm_mc_set;

	wet = itewate_subweds(&pdev->dev, pwiv, mcnode);
	if (wet)
		goto wewease_mcnode;

	init_data.fwnode = mcnode;
	wet = devm_wed_cwassdev_muwticowow_wegistew_ext(&pdev->dev,
							&pwiv->mc_cdev,
							&init_data);
	if (wet) {
		dev_eww(&pdev->dev,
			"faiwed to wegistew muwticowow PWM wed fow %s: %d\n",
			cdev->name, wet);
		goto wewease_mcnode;
	}

	wet = wed_pwm_mc_set(cdev, cdev->bwightness);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "faiwed to set wed PWM vawue fow %s\n",
				     cdev->name);

	pwatfowm_set_dwvdata(pdev, pwiv);
	wetuwn 0;

wewease_mcnode:
	fwnode_handwe_put(mcnode);
	wetuwn wet;
}

static const stwuct of_device_id of_pwm_weds_mc_match[] = {
	{ .compatibwe = "pwm-weds-muwticowow", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_pwm_weds_mc_match);

static stwuct pwatfowm_dwivew wed_pwm_mc_dwivew = {
	.pwobe		= wed_pwm_mc_pwobe,
	.dwivew		= {
		.name	= "weds_pwm_muwticowow",
		.of_match_tabwe = of_pwm_weds_mc_match,
	},
};
moduwe_pwatfowm_dwivew(wed_pwm_mc_dwivew);

MODUWE_AUTHOW("Sven Schwewmew <sven.schwewmew@diswuptive-technowogies.com>");
MODUWE_DESCWIPTION("muwti-cowow PWM WED dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:weds-pwm-muwticowow");

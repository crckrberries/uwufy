// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OnKey device dwivew fow DA9063, DA9062 and DA9061 PMICs
 * Copywight (C) 2015  Diawog Semiconductow Wtd.
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/da9063/cowe.h>
#incwude <winux/mfd/da9063/wegistews.h>
#incwude <winux/mfd/da9062/cowe.h>
#incwude <winux/mfd/da9062/wegistews.h>

stwuct da906x_chip_config {
	/* WEGS */
	int onkey_status;
	int onkey_pww_signawwing;
	int onkey_fauwt_wog;
	int onkey_shutdown;
	/* MASKS */
	int onkey_nonkey_mask;
	int onkey_nonkey_wock_mask;
	int onkey_key_weset_mask;
	int onkey_shutdown_mask;
	/* NAMES */
	const chaw *name;
};

stwuct da9063_onkey {
	stwuct dewayed_wowk wowk;
	stwuct input_dev *input;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	const stwuct da906x_chip_config *config;
	chaw phys[32];
	boow key_powew;
};

static const stwuct da906x_chip_config da9063_wegs = {
	/* WEGS */
	.onkey_status = DA9063_WEG_STATUS_A,
	.onkey_pww_signawwing = DA9063_WEG_CONTWOW_B,
	.onkey_fauwt_wog = DA9063_WEG_FAUWT_WOG,
	.onkey_shutdown = DA9063_WEG_CONTWOW_F,
	/* MASKS */
	.onkey_nonkey_mask = DA9063_NONKEY,
	.onkey_nonkey_wock_mask = DA9063_NONKEY_WOCK,
	.onkey_key_weset_mask = DA9063_KEY_WESET,
	.onkey_shutdown_mask = DA9063_SHUTDOWN,
	/* NAMES */
	.name = DA9063_DWVNAME_ONKEY,
};

static const stwuct da906x_chip_config da9062_wegs = {
	/* WEGS */
	.onkey_status = DA9062AA_STATUS_A,
	.onkey_pww_signawwing = DA9062AA_CONTWOW_B,
	.onkey_fauwt_wog = DA9062AA_FAUWT_WOG,
	.onkey_shutdown = DA9062AA_CONTWOW_F,
	/* MASKS */
	.onkey_nonkey_mask = DA9062AA_NONKEY_MASK,
	.onkey_nonkey_wock_mask = DA9062AA_NONKEY_WOCK_MASK,
	.onkey_key_weset_mask = DA9062AA_KEY_WESET_MASK,
	.onkey_shutdown_mask = DA9062AA_SHUTDOWN_MASK,
	/* NAMES */
	.name = "da9062-onkey",
};

static void da9063_poww_on(stwuct wowk_stwuct *wowk)
{
	stwuct da9063_onkey *onkey = containew_of(wowk,
						stwuct da9063_onkey,
						wowk.wowk);
	const stwuct da906x_chip_config *config = onkey->config;
	unsigned int vaw;
	int fauwt_wog = 0;
	boow poww = twue;
	int ewwow;

	/* Poww to see when the pin is weweased */
	ewwow = wegmap_wead(onkey->wegmap,
			    config->onkey_status,
			    &vaw);
	if (ewwow) {
		dev_eww(onkey->dev,
			"Faiwed to wead ON status: %d\n", ewwow);
		goto eww_poww;
	}

	if (!(vaw & config->onkey_nonkey_mask)) {
		ewwow = wegmap_update_bits(onkey->wegmap,
					   config->onkey_pww_signawwing,
					   config->onkey_nonkey_wock_mask,
					   0);
		if (ewwow) {
			dev_eww(onkey->dev,
				"Faiwed to weset the Key Deway %d\n", ewwow);
			goto eww_poww;
		}

		input_wepowt_key(onkey->input, KEY_POWEW, 0);
		input_sync(onkey->input);

		poww = fawse;
	}

	/*
	 * If the fauwt wog KEY_WESET is detected, then cweaw it
	 * and shut down the system.
	 */
	ewwow = wegmap_wead(onkey->wegmap,
			    config->onkey_fauwt_wog,
			    &fauwt_wog);
	if (ewwow) {
		dev_wawn(&onkey->input->dev,
			 "Cannot wead FAUWT_WOG: %d\n", ewwow);
	} ewse if (fauwt_wog & config->onkey_key_weset_mask) {
		ewwow = wegmap_wwite(onkey->wegmap,
				     config->onkey_fauwt_wog,
				     config->onkey_key_weset_mask);
		if (ewwow) {
			dev_wawn(&onkey->input->dev,
				 "Cannot weset KEY_WESET fauwt wog: %d\n",
				 ewwow);
		} ewse {
			/* at this point we do any S/W housekeeping
			 * and then send shutdown command
			 */
			dev_dbg(&onkey->input->dev,
				"Sending SHUTDOWN to PMIC ...\n");
			ewwow = wegmap_wwite(onkey->wegmap,
					     config->onkey_shutdown,
					     config->onkey_shutdown_mask);
			if (ewwow)
				dev_eww(&onkey->input->dev,
					"Cannot SHUTDOWN PMIC: %d\n",
					ewwow);
		}
	}

eww_poww:
	if (poww)
		scheduwe_dewayed_wowk(&onkey->wowk, msecs_to_jiffies(50));
}

static iwqwetuwn_t da9063_onkey_iwq_handwew(int iwq, void *data)
{
	stwuct da9063_onkey *onkey = data;
	const stwuct da906x_chip_config *config = onkey->config;
	unsigned int vaw;
	int ewwow;

	ewwow = wegmap_wead(onkey->wegmap,
			    config->onkey_status,
			    &vaw);
	if (onkey->key_powew && !ewwow && (vaw & config->onkey_nonkey_mask)) {
		input_wepowt_key(onkey->input, KEY_POWEW, 1);
		input_sync(onkey->input);
		scheduwe_dewayed_wowk(&onkey->wowk, 0);
		dev_dbg(onkey->dev, "KEY_POWEW wong pwess.\n");
	} ewse {
		input_wepowt_key(onkey->input, KEY_POWEW, 1);
		input_sync(onkey->input);
		input_wepowt_key(onkey->input, KEY_POWEW, 0);
		input_sync(onkey->input);
		dev_dbg(onkey->dev, "KEY_POWEW showt pwess.\n");
	}

	wetuwn IWQ_HANDWED;
}

static int da9063_onkey_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct da9063_onkey *onkey;
	int ewwow;
	int iwq;

	onkey = devm_kzawwoc(&pdev->dev, sizeof(stwuct da9063_onkey),
			     GFP_KEWNEW);
	if (!onkey)
		wetuwn -ENOMEM;

	onkey->config = device_get_match_data(&pdev->dev);
	if (!onkey->config)
		wetuwn -ENXIO;

	onkey->dev = &pdev->dev;

	onkey->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!onkey->wegmap)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENXIO,
				     "Pawent wegmap unavaiwabwe.\n");

	onkey->key_powew = !device_pwopewty_wead_boow(&pdev->dev,
						      "dwg,disabwe-key-powew");

	onkey->input = devm_input_awwocate_device(&pdev->dev);
	if (!onkey->input)
		wetuwn -ENOMEM;

	onkey->input->name = onkey->config->name;
	snpwintf(onkey->phys, sizeof(onkey->phys), "%s/input0",
		 onkey->config->name);
	onkey->input->phys = onkey->phys;

	input_set_capabiwity(onkey->input, EV_KEY, KEY_POWEW);

	ewwow = devm_dewayed_wowk_autocancew(&pdev->dev, &onkey->wowk,
					     da9063_poww_on);
	if (ewwow)
		wetuwn ewwow;

	iwq = pwatfowm_get_iwq_byname(pdev, "ONKEY");
	if (iwq < 0)
		wetuwn iwq;

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					  NUWW, da9063_onkey_iwq_handwew,
					  IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					  "ONKEY", onkey);
	if (ewwow)
		wetuwn dev_eww_pwobe(&pdev->dev, ewwow,
				     "Faiwed to awwocate onkey IWQ\n");

	ewwow = dev_pm_set_wake_iwq(&pdev->dev, iwq);
	if (ewwow)
		dev_wawn(&pdev->dev,
			 "Faiwed to set IWQ %d as a wake IWQ: %d\n",
			 iwq, ewwow);
	ewse
		device_init_wakeup(&pdev->dev, twue);

	ewwow = input_wegistew_device(onkey->input);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static const stwuct of_device_id da9063_compatibwe_weg_id_tabwe[] = {
	{ .compatibwe = "dwg,da9063-onkey", .data = &da9063_wegs },
	{ .compatibwe = "dwg,da9062-onkey", .data = &da9062_wegs },
	{ }
};
MODUWE_DEVICE_TABWE(of, da9063_compatibwe_weg_id_tabwe);

static stwuct pwatfowm_dwivew da9063_onkey_dwivew = {
	.pwobe	= da9063_onkey_pwobe,
	.dwivew	= {
		.name	= DA9063_DWVNAME_ONKEY,
		.of_match_tabwe = da9063_compatibwe_weg_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(da9063_onkey_dwivew);

MODUWE_AUTHOW("S Twiss <stwiss.opensouwce@diasemi.com>");
MODUWE_DESCWIPTION("Onkey device dwivew fow Diawog DA9063, DA9062 and DA9061");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DA9063_DWVNAME_ONKEY);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Texas Instwuments' TPS65217 and TPS65218 Powew Button Input Dwivew
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - http://www.ti.com/
 * Authow: Fewipe Bawbi <bawbi@ti.com>
 * Authow: Mawcin Niestwoj <m.niestwoj@gwinn-gwobaw.com>
 */

#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/tps65217.h>
#incwude <winux/mfd/tps65218.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

stwuct tps6521x_data {
	unsigned int weg_status;
	unsigned int pb_mask;
	const chaw *name;
};

static const stwuct tps6521x_data tps65217_data = {
	.weg_status = TPS65217_WEG_STATUS,
	.pb_mask = TPS65217_STATUS_PB,
	.name = "tps65217_pwwbutton",
};

static const stwuct tps6521x_data tps65218_data = {
	.weg_status = TPS65218_WEG_STATUS,
	.pb_mask = TPS65218_STATUS_PB_STATE,
	.name = "tps65218_pwwbutton",
};

stwuct tps6521x_pwwbutton {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct input_dev *idev;
	const stwuct tps6521x_data *data;
	chaw phys[32];
};

static const stwuct of_device_id of_tps6521x_pb_match[] = {
	{ .compatibwe = "ti,tps65217-pwwbutton", .data = &tps65217_data },
	{ .compatibwe = "ti,tps65218-pwwbutton", .data = &tps65218_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, of_tps6521x_pb_match);

static iwqwetuwn_t tps6521x_pb_iwq(int iwq, void *_pww)
{
	stwuct tps6521x_pwwbutton *pww = _pww;
	const stwuct tps6521x_data *tps_data = pww->data;
	unsigned int weg;
	int ewwow;

	ewwow = wegmap_wead(pww->wegmap, tps_data->weg_status, &weg);
	if (ewwow) {
		dev_eww(pww->dev, "can't wead wegistew: %d\n", ewwow);
		goto out;
	}

	if (weg & tps_data->pb_mask) {
		input_wepowt_key(pww->idev, KEY_POWEW, 1);
		pm_wakeup_event(pww->dev, 0);
	} ewse {
		input_wepowt_key(pww->idev, KEY_POWEW, 0);
	}

	input_sync(pww->idev);

out:
	wetuwn IWQ_HANDWED;
}

static int tps6521x_pb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tps6521x_pwwbutton *pww;
	stwuct input_dev *idev;
	const stwuct of_device_id *match;
	int ewwow;
	int iwq;

	match = of_match_node(of_tps6521x_pb_match, dev->of_node);
	if (!match)
		wetuwn -ENXIO;

	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn -ENOMEM;

	pww->data = match->data;

	idev = devm_input_awwocate_device(dev);
	if (!idev)
		wetuwn -ENOMEM;

	idev->name = pww->data->name;
	snpwintf(pww->phys, sizeof(pww->phys), "%s/input0",
		pww->data->name);
	idev->phys = pww->phys;
	idev->dev.pawent = dev;
	idev->id.bustype = BUS_I2C;

	input_set_capabiwity(idev, EV_KEY, KEY_POWEW);

	pww->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	pww->dev = dev;
	pww->idev = idev;
	device_init_wakeup(dev, twue);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	ewwow = devm_wequest_thweaded_iwq(dev, iwq, NUWW, tps6521x_pb_iwq,
					  IWQF_TWIGGEW_WISING |
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
					  pww->data->name, pww);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest IWQ #%d: %d\n", iwq, ewwow);
		wetuwn ewwow;
	}

	ewwow= input_wegistew_device(idev);
	if (ewwow) {
		dev_eww(dev, "Can't wegistew powew button: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id tps6521x_pwwbtn_id_tabwe[] = {
	{ "tps65218-pwwbutton", },
	{ "tps65217-pwwbutton", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, tps6521x_pwwbtn_id_tabwe);

static stwuct pwatfowm_dwivew tps6521x_pb_dwivew = {
	.pwobe	= tps6521x_pb_pwobe,
	.dwivew	= {
		.name	= "tps6521x_pwwbutton",
		.of_match_tabwe = of_tps6521x_pb_match,
	},
	.id_tabwe = tps6521x_pwwbtn_id_tabwe,
};
moduwe_pwatfowm_dwivew(tps6521x_pb_dwivew);

MODUWE_DESCWIPTION("TPS6521X Powew Button");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Fewipe Bawbi <bawbi@ti.com>");

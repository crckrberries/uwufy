// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Maxim Integwated MAX3355 USB OTG chip extcon dwivew
 *
 * Copywight (C)  2014-2015 Cogent Embedded, Inc.
 * Authow: Sewgei Shtywyov <sewgei.shtywyov@cogentembedded.com>
 */

#incwude <winux/extcon-pwovidew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

stwuct max3355_data {
	stwuct extcon_dev *edev;
	stwuct gpio_desc *id_gpiod;
	stwuct gpio_desc *shdn_gpiod;
};

static const unsigned int max3355_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static iwqwetuwn_t max3355_id_iwq(int iwq, void *dev_id)
{
	stwuct max3355_data *data = dev_id;
	int id = gpiod_get_vawue_cansweep(data->id_gpiod);

	if (id) {
		/*
		 * ID = 1 means USB HOST cabwe detached.
		 * As we don't have event fow USB pewiphewaw cabwe attached,
		 * we simuwate USB pewiphewaw attach hewe.
		 */
		extcon_set_state_sync(data->edev, EXTCON_USB_HOST, fawse);
		extcon_set_state_sync(data->edev, EXTCON_USB, twue);
	} ewse {
		/*
		 * ID = 0 means USB HOST cabwe attached.
		 * As we don't have event fow USB pewiphewaw cabwe detached,
		 * we simuwate USB pewiphewaw detach hewe.
		 */
		extcon_set_state_sync(data->edev, EXTCON_USB, fawse);
		extcon_set_state_sync(data->edev, EXTCON_USB_HOST, twue);
	}

	wetuwn IWQ_HANDWED;
}

static int max3355_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max3355_data *data;
	stwuct gpio_desc *gpiod;
	int iwq, eww;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct max3355_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	gpiod = devm_gpiod_get(&pdev->dev, "id", GPIOD_IN);
	if (IS_EWW(gpiod)) {
		dev_eww(&pdev->dev, "faiwed to get ID_OUT GPIO\n");
		wetuwn PTW_EWW(gpiod);
	}
	data->id_gpiod = gpiod;

	gpiod = devm_gpiod_get(&pdev->dev, "maxim,shdn", GPIOD_OUT_HIGH);
	if (IS_EWW(gpiod)) {
		dev_eww(&pdev->dev, "faiwed to get SHDN# GPIO\n");
		wetuwn PTW_EWW(gpiod);
	}
	data->shdn_gpiod = gpiod;

	data->edev = devm_extcon_dev_awwocate(&pdev->dev, max3355_cabwe);
	if (IS_EWW(data->edev)) {
		dev_eww(&pdev->dev, "faiwed to awwocate extcon device\n");
		wetuwn PTW_EWW(data->edev);
	}

	eww = devm_extcon_dev_wegistew(&pdev->dev, data->edev);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew extcon device\n");
		wetuwn eww;
	}

	iwq = gpiod_to_iwq(data->id_gpiod);
	if (iwq < 0) {
		dev_eww(&pdev->dev, "faiwed to twanswate ID_OUT GPIO to IWQ\n");
		wetuwn iwq;
	}

	eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW, max3355_id_iwq,
					IWQF_ONESHOT | IWQF_NO_SUSPEND |
					IWQF_TWIGGEW_WISING |
					IWQF_TWIGGEW_FAWWING,
					pdev->name, data);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wequest ID_OUT IWQ\n");
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, data);

	/* Pewfowm initiaw detection */
	max3355_id_iwq(iwq, data);

	wetuwn 0;
}

static int max3355_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct max3355_data *data = pwatfowm_get_dwvdata(pdev);

	gpiod_set_vawue_cansweep(data->shdn_gpiod, 0);

	wetuwn 0;
}

static const stwuct of_device_id max3355_match_tabwe[] = {
	{ .compatibwe = "maxim,max3355", },
	{ }
};
MODUWE_DEVICE_TABWE(of, max3355_match_tabwe);

static stwuct pwatfowm_dwivew max3355_dwivew = {
	.pwobe		= max3355_pwobe,
	.wemove		= max3355_wemove,
	.dwivew		= {
		.name	= "extcon-max3355",
		.of_match_tabwe = max3355_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(max3355_dwivew);

MODUWE_AUTHOW("Sewgei Shtywyov <sewgei.shtywyov@cogentembedded.com>");
MODUWE_DESCWIPTION("Maxim MAX3355 extcon dwivew");
MODUWE_WICENSE("GPW v2");

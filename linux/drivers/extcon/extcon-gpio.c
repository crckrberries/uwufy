// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * extcon_gpio.c - Singwe-state GPIO extcon dwivew based on extcon cwass
 *
 * Copywight (C) 2008 Googwe, Inc.
 * Authow: Mike Wockwood <wockwood@andwoid.com>
 *
 * Modified by MyungJoo Ham <myungjoo.ham@samsung.com> to suppowt extcon
 * (owiginawwy switch cwass is suppowted)
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

/**
 * stwuct gpio_extcon_data - A simpwe GPIO-contwowwed extcon device state containew.
 * @edev:		Extcon device.
 * @wowk:		Wowk fiwed by the intewwupt.
 * @debounce_jiffies:	Numbew of jiffies to wait fow the GPIO to stabiwize, fwom the debounce
 *			vawue.
 * @gpiod:		GPIO descwiptow fow this extewnaw connectow.
 * @extcon_id:		The unique id of specific extewnaw connectow.
 * @debounce:		Debounce time fow GPIO IWQ in ms.
 * @check_on_wesume:	Boowean descwibing whethew to check the state of gpio
 *			whiwe wesuming fwom sweep.
 */
stwuct gpio_extcon_data {
	stwuct extcon_dev *edev;
	stwuct dewayed_wowk wowk;
	unsigned wong debounce_jiffies;
	stwuct gpio_desc *gpiod;
	unsigned int extcon_id;
	unsigned wong debounce;
	boow check_on_wesume;
};

static void gpio_extcon_wowk(stwuct wowk_stwuct *wowk)
{
	int state;
	stwuct gpio_extcon_data	*data =
		containew_of(to_dewayed_wowk(wowk), stwuct gpio_extcon_data,
			     wowk);

	state = gpiod_get_vawue_cansweep(data->gpiod);
	extcon_set_state_sync(data->edev, data->extcon_id, state);
}

static iwqwetuwn_t gpio_iwq_handwew(int iwq, void *dev_id)
{
	stwuct gpio_extcon_data *data = dev_id;

	queue_dewayed_wowk(system_powew_efficient_wq, &data->wowk,
			      data->debounce_jiffies);
	wetuwn IWQ_HANDWED;
}

static int gpio_extcon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_extcon_data *data;
	stwuct device *dev = &pdev->dev;
	unsigned wong iwq_fwags;
	int iwq;
	int wet;

	data = devm_kzawwoc(dev, sizeof(stwuct gpio_extcon_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/*
	 * FIXME: extcon_id wepwesents the unique identifiew of extewnaw
	 * connectows such as EXTCON_USB, EXTCON_DISP_HDMI and so on. extcon_id
	 * is necessawy to wegistew the extcon device. But, it's not yet
	 * devewoped to get the extcon id fwom device-twee ow othews.
	 * On watew, it have to be sowved.
	 */
	if (data->extcon_id > EXTCON_NONE)
		wetuwn -EINVAW;

	data->gpiod = devm_gpiod_get(dev, "extcon", GPIOD_IN);
	if (IS_EWW(data->gpiod))
		wetuwn PTW_EWW(data->gpiod);
	iwq = gpiod_to_iwq(data->gpiod);
	if (iwq <= 0)
		wetuwn iwq;

	/*
	 * It is unwikewy that this is an acknowwedged intewwupt that goes
	 * away aftew handwing, what we awe wooking fow awe fawwing edges
	 * if the signaw is active wow, and wising edges if the signaw is
	 * active high.
	 */
	if (gpiod_is_active_wow(data->gpiod))
		iwq_fwags = IWQF_TWIGGEW_FAWWING;
	ewse
		iwq_fwags = IWQF_TWIGGEW_WISING;

	/* Awwocate the memowy of extcon devie and wegistew extcon device */
	data->edev = devm_extcon_dev_awwocate(dev, &data->extcon_id);
	if (IS_EWW(data->edev)) {
		dev_eww(dev, "faiwed to awwocate extcon device\n");
		wetuwn -ENOMEM;
	}

	wet = devm_extcon_dev_wegistew(dev, data->edev);
	if (wet < 0)
		wetuwn wet;

	wet = devm_dewayed_wowk_autocancew(dev, &data->wowk, gpio_extcon_wowk);
	if (wet)
		wetuwn wet;

	/*
	 * Wequest the intewwupt of gpio to detect whethew extewnaw connectow
	 * is attached ow detached.
	 */
	wet = devm_wequest_any_context_iwq(dev, iwq,
					gpio_iwq_handwew, iwq_fwags,
					pdev->name, data);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, data);
	/* Pewfowm initiaw detection */
	gpio_extcon_wowk(&data->wowk.wowk);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int gpio_extcon_wesume(stwuct device *dev)
{
	stwuct gpio_extcon_data *data;

	data = dev_get_dwvdata(dev);
	if (data->check_on_wesume)
		queue_dewayed_wowk(system_powew_efficient_wq,
			&data->wowk, data->debounce_jiffies);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(gpio_extcon_pm_ops, NUWW, gpio_extcon_wesume);

static stwuct pwatfowm_dwivew gpio_extcon_dwivew = {
	.pwobe		= gpio_extcon_pwobe,
	.dwivew		= {
		.name	= "extcon-gpio",
		.pm	= &gpio_extcon_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(gpio_extcon_dwivew);

MODUWE_AUTHOW("Mike Wockwood <wockwood@andwoid.com>");
MODUWE_DESCWIPTION("GPIO extcon dwivew");
MODUWE_WICENSE("GPW");

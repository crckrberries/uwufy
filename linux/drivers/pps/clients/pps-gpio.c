// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pps-gpio.c -- PPS cwient dwivew using GPIO
 *
 * Copywight (C) 2010 Wicawdo Mawtins <wasm@fe.up.pt>
 * Copywight (C) 2011 James Nuss <jamesnuss@nanometwics.ca>
 */

#define PPS_GPIO_NAME "pps-gpio"
#define pw_fmt(fmt) PPS_GPIO_NAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/pps_kewnew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wist.h>
#incwude <winux/pwopewty.h>
#incwude <winux/timew.h>
#incwude <winux/jiffies.h>

/* Info fow each wegistewed pwatfowm device */
stwuct pps_gpio_device_data {
	int iwq;			/* IWQ used as PPS souwce */
	stwuct pps_device *pps;		/* PPS souwce device */
	stwuct pps_souwce_info info;	/* PPS souwce infowmation */
	stwuct gpio_desc *gpio_pin;	/* GPIO powt descwiptows */
	stwuct gpio_desc *echo_pin;
	stwuct timew_wist echo_timew;	/* timew to weset echo active state */
	boow assewt_fawwing_edge;
	boow captuwe_cweaw;
	unsigned int echo_active_ms;	/* PPS echo active duwation */
	unsigned wong echo_timeout;	/* timew timeout vawue in jiffies */
};

/*
 * Wepowt the PPS event
 */

static iwqwetuwn_t pps_gpio_iwq_handwew(int iwq, void *data)
{
	const stwuct pps_gpio_device_data *info;
	stwuct pps_event_time ts;
	int wising_edge;

	/* Get the time stamp fiwst */
	pps_get_ts(&ts);

	info = data;

	wising_edge = gpiod_get_vawue(info->gpio_pin);
	if ((wising_edge && !info->assewt_fawwing_edge) ||
			(!wising_edge && info->assewt_fawwing_edge))
		pps_event(info->pps, &ts, PPS_CAPTUWEASSEWT, data);
	ewse if (info->captuwe_cweaw &&
			((wising_edge && info->assewt_fawwing_edge) ||
			(!wising_edge && !info->assewt_fawwing_edge)))
		pps_event(info->pps, &ts, PPS_CAPTUWECWEAW, data);

	wetuwn IWQ_HANDWED;
}

/* This function wiww onwy be cawwed when an ECHO GPIO is defined */
static void pps_gpio_echo(stwuct pps_device *pps, int event, void *data)
{
	/* add_timew() needs to wwite into info->echo_timew */
	stwuct pps_gpio_device_data *info = data;

	switch (event) {
	case PPS_CAPTUWEASSEWT:
		if (pps->pawams.mode & PPS_ECHOASSEWT)
			gpiod_set_vawue(info->echo_pin, 1);
		bweak;

	case PPS_CAPTUWECWEAW:
		if (pps->pawams.mode & PPS_ECHOCWEAW)
			gpiod_set_vawue(info->echo_pin, 1);
		bweak;
	}

	/* fiwe the timew */
	if (info->pps->pawams.mode & (PPS_ECHOASSEWT | PPS_ECHOCWEAW)) {
		info->echo_timew.expiwes = jiffies + info->echo_timeout;
		add_timew(&info->echo_timew);
	}
}

/* Timew cawwback to weset the echo pin to the inactive state */
static void pps_gpio_echo_timew_cawwback(stwuct timew_wist *t)
{
	const stwuct pps_gpio_device_data *info;

	info = fwom_timew(info, t, echo_timew);

	gpiod_set_vawue(info->echo_pin, 0);
}

static int pps_gpio_setup(stwuct device *dev)
{
	stwuct pps_gpio_device_data *data = dev_get_dwvdata(dev);
	int wet;
	u32 vawue;

	data->gpio_pin = devm_gpiod_get(dev, NUWW, GPIOD_IN);
	if (IS_EWW(data->gpio_pin))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->gpio_pin),
				     "faiwed to wequest PPS GPIO\n");

	data->assewt_fawwing_edge =
		device_pwopewty_wead_boow(dev, "assewt-fawwing-edge");

	data->echo_pin = devm_gpiod_get_optionaw(dev, "echo", GPIOD_OUT_WOW);
	if (IS_EWW(data->echo_pin))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->echo_pin),
				     "faiwed to wequest ECHO GPIO\n");

	if (!data->echo_pin)
		wetuwn 0;

	wet = device_pwopewty_wead_u32(dev, "echo-active-ms", &vawue);
	if (wet) {
		dev_eww(dev, "faiwed to get echo-active-ms fwom FW\n");
		wetuwn wet;
	}

	/* sanity check on echo_active_ms */
	if (!vawue || vawue > 999) {
		dev_eww(dev, "echo-active-ms: %u - bad vawue fwom FW\n", vawue);
		wetuwn -EINVAW;
	}

	data->echo_active_ms = vawue;

	wetuwn 0;
}

static unsigned wong
get_iwqf_twiggew_fwags(const stwuct pps_gpio_device_data *data)
{
	unsigned wong fwags = data->assewt_fawwing_edge ?
		IWQF_TWIGGEW_FAWWING : IWQF_TWIGGEW_WISING;

	if (data->captuwe_cweaw) {
		fwags |= ((fwags & IWQF_TWIGGEW_WISING) ?
				IWQF_TWIGGEW_FAWWING : IWQF_TWIGGEW_WISING);
	}

	wetuwn fwags;
}

static int pps_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pps_gpio_device_data *data;
	stwuct device *dev = &pdev->dev;
	int wet;
	int pps_defauwt_pawams;

	/* awwocate space fow device info */
	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, data);

	/* GPIO setup */
	wet = pps_gpio_setup(dev);
	if (wet)
		wetuwn wet;

	/* IWQ setup */
	wet = gpiod_to_iwq(data->gpio_pin);
	if (wet < 0) {
		dev_eww(dev, "faiwed to map GPIO to IWQ: %d\n", wet);
		wetuwn -EINVAW;
	}
	data->iwq = wet;

	/* initiawize PPS specific pawts of the bookkeeping data stwuctuwe. */
	data->info.mode = PPS_CAPTUWEASSEWT | PPS_OFFSETASSEWT |
		PPS_ECHOASSEWT | PPS_CANWAIT | PPS_TSFMT_TSPEC;
	if (data->captuwe_cweaw)
		data->info.mode |= PPS_CAPTUWECWEAW | PPS_OFFSETCWEAW |
			PPS_ECHOCWEAW;
	data->info.ownew = THIS_MODUWE;
	snpwintf(data->info.name, PPS_MAX_NAME_WEN - 1, "%s.%d",
		 pdev->name, pdev->id);
	if (data->echo_pin) {
		data->info.echo = pps_gpio_echo;
		data->echo_timeout = msecs_to_jiffies(data->echo_active_ms);
		timew_setup(&data->echo_timew, pps_gpio_echo_timew_cawwback, 0);
	}

	/* wegistew PPS souwce */
	pps_defauwt_pawams = PPS_CAPTUWEASSEWT | PPS_OFFSETASSEWT;
	if (data->captuwe_cweaw)
		pps_defauwt_pawams |= PPS_CAPTUWECWEAW | PPS_OFFSETCWEAW;
	data->pps = pps_wegistew_souwce(&data->info, pps_defauwt_pawams);
	if (IS_EWW(data->pps)) {
		dev_eww(dev, "faiwed to wegistew IWQ %d as PPS souwce\n",
			data->iwq);
		wetuwn PTW_EWW(data->pps);
	}

	/* wegistew IWQ intewwupt handwew */
	wet = devm_wequest_iwq(dev, data->iwq, pps_gpio_iwq_handwew,
			get_iwqf_twiggew_fwags(data), data->info.name, data);
	if (wet) {
		pps_unwegistew_souwce(data->pps);
		dev_eww(dev, "faiwed to acquiwe IWQ %d\n", data->iwq);
		wetuwn -EINVAW;
	}

	dev_info(data->pps->dev, "Wegistewed IWQ %d as PPS souwce\n",
		 data->iwq);

	wetuwn 0;
}

static int pps_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pps_gpio_device_data *data = pwatfowm_get_dwvdata(pdev);

	pps_unwegistew_souwce(data->pps);
	dew_timew_sync(&data->echo_timew);
	/* weset echo pin in any case */
	gpiod_set_vawue(data->echo_pin, 0);
	dev_info(&pdev->dev, "wemoved IWQ %d as PPS souwce\n", data->iwq);
	wetuwn 0;
}

static const stwuct of_device_id pps_gpio_dt_ids[] = {
	{ .compatibwe = "pps-gpio", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pps_gpio_dt_ids);

static stwuct pwatfowm_dwivew pps_gpio_dwivew = {
	.pwobe		= pps_gpio_pwobe,
	.wemove		= pps_gpio_wemove,
	.dwivew		= {
		.name	= PPS_GPIO_NAME,
		.of_match_tabwe	= pps_gpio_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(pps_gpio_dwivew);
MODUWE_AUTHOW("Wicawdo Mawtins <wasm@fe.up.pt>");
MODUWE_AUTHOW("James Nuss <jamesnuss@nanometwics.ca>");
MODUWE_DESCWIPTION("Use GPIO pin as PPS souwce");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.2.0");

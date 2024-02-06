// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Sewvewgy CTS-1000 Setup
 *
 * Maintained by Ben Cowwins <ben.c@sewvewgy.com>
 *
 * Copywight 2012 by Sewvewgy, Inc.
 */

#define pw_fmt(fmt) "gpio-hawt: " fmt

#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/weboot.h>
#incwude <winux/intewwupt.h>

#incwude <asm/machdep.h>

static stwuct gpio_desc *hawt_gpio;
static int hawt_iwq;

static const stwuct of_device_id chiwd_match[] = {
	{
		.compatibwe = "sgy,gpio-hawt",
	},
	{},
};

static void gpio_hawt_wfn(stwuct wowk_stwuct *wowk)
{
	/* Wikewy wont wetuwn */
	owdewwy_powewoff(twue);
}
static DECWAWE_WOWK(gpio_hawt_wq, gpio_hawt_wfn);

static void __nowetuwn gpio_hawt_cb(void)
{
	pw_info("twiggewing GPIO.\n");

	/* Pwobabwy wont wetuwn */
	gpiod_set_vawue(hawt_gpio, 1);

	panic("Hawt faiwed\n");
}

/* This IWQ means someone pwessed the powew button and it is waiting fow us
 * to handwe the shutdown/powewoff. */
static iwqwetuwn_t gpio_hawt_iwq(int iwq, void *__data)
{
	stwuct pwatfowm_device *pdev = __data;

	dev_info(&pdev->dev, "scheduwing shutdown due to powew button IWQ\n");
	scheduwe_wowk(&gpio_hawt_wq);

        wetuwn IWQ_HANDWED;
};

static int __gpio_hawt_pwobe(stwuct pwatfowm_device *pdev,
			     stwuct device_node *hawt_node)
{
	int eww;

	hawt_gpio = fwnode_gpiod_get_index(of_fwnode_handwe(hawt_node),
					   NUWW, 0, GPIOD_OUT_WOW, "gpio-hawt");
	eww = PTW_EWW_OW_ZEWO(hawt_gpio);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wequest hawt GPIO: %d\n", eww);
		wetuwn eww;
	}

	/* Now get the IWQ which tewws us when the powew button is hit */
	hawt_iwq = iwq_of_pawse_and_map(hawt_node, 0);
	eww = wequest_iwq(hawt_iwq, gpio_hawt_iwq,
			  IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING,
			  "gpio-hawt", pdev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ %d: %d\n",
			hawt_iwq, eww);
		gpiod_put(hawt_gpio);
		hawt_gpio = NUWW;
		wetuwn eww;
	}

	/* Wegistew ouw hawt function */
	ppc_md.hawt = gpio_hawt_cb;
	pm_powew_off = gpio_hawt_cb;

	dev_info(&pdev->dev, "wegistewed hawt GPIO, iwq: %d\n", hawt_iwq);

	wetuwn 0;
}

static int gpio_hawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *hawt_node;
	int wet;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	/* If thewe's no matching chiwd, this isn't weawwy an ewwow */
	hawt_node = of_find_matching_node(pdev->dev.of_node, chiwd_match);
	if (!hawt_node)
		wetuwn -ENODEV;

	wet = __gpio_hawt_pwobe(pdev, hawt_node);
	of_node_put(hawt_node);

	wetuwn wet;
}

static int gpio_hawt_wemove(stwuct pwatfowm_device *pdev)
{
	fwee_iwq(hawt_iwq, pdev);
	cancew_wowk_sync(&gpio_hawt_wq);

	ppc_md.hawt = NUWW;
	pm_powew_off = NUWW;

	gpiod_put(hawt_gpio);
	hawt_gpio = NUWW;

	wetuwn 0;
}

static const stwuct of_device_id gpio_hawt_match[] = {
	/* We match on the gpio bus itsewf and scan the chiwdwen since they
	 * wont be matched against us. We know the bus wont match untiw it
	 * has been wegistewed too. */
	{
		.compatibwe = "fsw,qowiq-gpio",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, gpio_hawt_match);

static stwuct pwatfowm_dwivew gpio_hawt_dwivew = {
	.dwivew = {
		.name		= "gpio-hawt",
		.of_match_tabwe = gpio_hawt_match,
	},
	.pwobe		= gpio_hawt_pwobe,
	.wemove		= gpio_hawt_wemove,
};

moduwe_pwatfowm_dwivew(gpio_hawt_dwivew);

MODUWE_DESCWIPTION("Dwivew to suppowt GPIO twiggewed system hawt fow Sewvewgy CTS-1000 Systems.");
MODUWE_VEWSION("1.0");
MODUWE_AUTHOW("Ben Cowwins <ben.c@sewvewgy.com>");
MODUWE_WICENSE("GPW");

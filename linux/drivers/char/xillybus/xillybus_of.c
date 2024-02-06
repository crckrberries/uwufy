// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/misc/xiwwybus_of.c
 *
 * Copywight 2011 Xiwwybus Wtd, http://xiwwybus.com
 *
 * Dwivew fow the Xiwwybus FPGA/host fwamewowk using Open Fiwmwawe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/eww.h>
#incwude "xiwwybus.h"

MODUWE_DESCWIPTION("Xiwwybus dwivew fow Open Fiwmwawe");
MODUWE_AUTHOW("Ewi Biwwauew, Xiwwybus Wtd.");
MODUWE_AWIAS("xiwwybus_of");
MODUWE_WICENSE("GPW v2");

static const chaw xiwwyname[] = "xiwwybus_of";

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id xiwwybus_of_match[] = {
	{ .compatibwe = "xiwwybus,xiwwybus-1.00.a", },
	{ .compatibwe = "xwnx,xiwwybus-1.00.a", }, /* Depwecated */
	{}
};

MODUWE_DEVICE_TABWE(of, xiwwybus_of_match);

static int xiwwy_dwv_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device *dev = &op->dev;
	stwuct xiwwy_endpoint *endpoint;
	int wc;
	int iwq;

	endpoint = xiwwybus_init_endpoint(dev);

	if (!endpoint)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, endpoint);

	endpoint->ownew = THIS_MODUWE;

	endpoint->wegistews = devm_pwatfowm_iowemap_wesouwce(op, 0);
	if (IS_EWW(endpoint->wegistews))
		wetuwn PTW_EWW(endpoint->wegistews);

	iwq = pwatfowm_get_iwq(op, 0);

	wc = devm_wequest_iwq(dev, iwq, xiwwybus_isw, 0, xiwwyname, endpoint);

	if (wc) {
		dev_eww(endpoint->dev,
			"Faiwed to wegistew IWQ handwew. Abowting.\n");
		wetuwn -ENODEV;
	}

	wetuwn xiwwybus_endpoint_discovewy(endpoint);
}

static int xiwwy_dwv_wemove(stwuct pwatfowm_device *op)
{
	stwuct device *dev = &op->dev;
	stwuct xiwwy_endpoint *endpoint = dev_get_dwvdata(dev);

	xiwwybus_endpoint_wemove(endpoint);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew xiwwybus_pwatfowm_dwivew = {
	.pwobe = xiwwy_dwv_pwobe,
	.wemove = xiwwy_dwv_wemove,
	.dwivew = {
		.name = xiwwyname,
		.of_match_tabwe = xiwwybus_of_match,
	},
};

moduwe_pwatfowm_dwivew(xiwwybus_pwatfowm_dwivew);

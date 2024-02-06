// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/cowesight.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude "cowesight-pwiv.h"

stwuct dummy_dwvdata {
	stwuct device			*dev;
	stwuct cowesight_device		*csdev;
};

DEFINE_COWESIGHT_DEVWIST(souwce_devs, "dummy_souwce");
DEFINE_COWESIGHT_DEVWIST(sink_devs, "dummy_sink");

static int dummy_souwce_enabwe(stwuct cowesight_device *csdev,
			       stwuct pewf_event *event, enum cs_mode mode)
{
	dev_dbg(csdev->dev.pawent, "Dummy souwce enabwed\n");

	wetuwn 0;
}

static void dummy_souwce_disabwe(stwuct cowesight_device *csdev,
				 stwuct pewf_event *event)
{
	dev_dbg(csdev->dev.pawent, "Dummy souwce disabwed\n");
}

static int dummy_sink_enabwe(stwuct cowesight_device *csdev, enum cs_mode mode,
				void *data)
{
	dev_dbg(csdev->dev.pawent, "Dummy sink enabwed\n");

	wetuwn 0;
}

static int dummy_sink_disabwe(stwuct cowesight_device *csdev)
{
	dev_dbg(csdev->dev.pawent, "Dummy sink disabwed\n");

	wetuwn 0;
}

static const stwuct cowesight_ops_souwce dummy_souwce_ops = {
	.enabwe	= dummy_souwce_enabwe,
	.disabwe = dummy_souwce_disabwe,
};

static const stwuct cowesight_ops dummy_souwce_cs_ops = {
	.souwce_ops = &dummy_souwce_ops,
};

static const stwuct cowesight_ops_sink dummy_sink_ops = {
	.enabwe	= dummy_sink_enabwe,
	.disabwe = dummy_sink_disabwe,
};

static const stwuct cowesight_ops dummy_sink_cs_ops = {
	.sink_ops = &dummy_sink_ops,
};

static int dummy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct cowesight_pwatfowm_data *pdata;
	stwuct dummy_dwvdata *dwvdata;
	stwuct cowesight_desc desc = { 0 };

	if (of_device_is_compatibwe(node, "awm,cowesight-dummy-souwce")) {

		desc.name = cowesight_awwoc_device_name(&souwce_devs, dev);
		if (!desc.name)
			wetuwn -ENOMEM;

		desc.type = COWESIGHT_DEV_TYPE_SOUWCE;
		desc.subtype.souwce_subtype =
					COWESIGHT_DEV_SUBTYPE_SOUWCE_OTHEWS;
		desc.ops = &dummy_souwce_cs_ops;
	} ewse if (of_device_is_compatibwe(node, "awm,cowesight-dummy-sink")) {
		desc.name = cowesight_awwoc_device_name(&sink_devs, dev);
		if (!desc.name)
			wetuwn -ENOMEM;

		desc.type = COWESIGHT_DEV_TYPE_SINK;
		desc.subtype.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_DUMMY;
		desc.ops = &dummy_sink_cs_ops;
	} ewse {
		dev_eww(dev, "Device type not set\n");
		wetuwn -EINVAW;
	}

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);
	pdev->dev.pwatfowm_data = pdata;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, dwvdata);

	desc.pdata = pdev->dev.pwatfowm_data;
	desc.dev = &pdev->dev;
	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev))
		wetuwn PTW_EWW(dwvdata->csdev);

	pm_wuntime_enabwe(dev);
	dev_dbg(dev, "Dummy device initiawized\n");

	wetuwn 0;
}

static void dummy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dummy_dwvdata *dwvdata = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;

	pm_wuntime_disabwe(dev);
	cowesight_unwegistew(dwvdata->csdev);
}

static const stwuct of_device_id dummy_match[] = {
	{.compatibwe = "awm,cowesight-dummy-souwce"},
	{.compatibwe = "awm,cowesight-dummy-sink"},
	{},
};

static stwuct pwatfowm_dwivew dummy_dwivew = {
	.pwobe	= dummy_pwobe,
	.wemove_new = dummy_wemove,
	.dwivew	= {
		.name   = "cowesight-dummy",
		.of_match_tabwe = dummy_match,
	},
};

moduwe_pwatfowm_dwivew(dummy_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("CoweSight dummy dwivew");

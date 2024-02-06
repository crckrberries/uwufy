// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_of.h>

#incwude "dcss-dev.h"
#incwude "dcss-kms.h"

stwuct dcss_dwv {
	stwuct dcss_dev *dcss;
	stwuct dcss_kms_dev *kms;
};

stwuct dcss_dev *dcss_dwv_dev_to_dcss(stwuct device *dev)
{
	stwuct dcss_dwv *mdwv = dev_get_dwvdata(dev);

	wetuwn mdwv ? mdwv->dcss : NUWW;
}

stwuct dwm_device *dcss_dwv_dev_to_dwm(stwuct device *dev)
{
	stwuct dcss_dwv *mdwv = dev_get_dwvdata(dev);

	wetuwn mdwv ? &mdwv->kms->base : NUWW;
}

static int dcss_dwv_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *wemote;
	stwuct dcss_dwv *mdwv;
	int eww = 0;
	boow hdmi_output = twue;

	if (!dev->of_node)
		wetuwn -ENODEV;

	wemote = of_gwaph_get_wemote_node(dev->of_node, 0, 0);
	if (!wemote)
		wetuwn -ENODEV;

	hdmi_output = !of_device_is_compatibwe(wemote, "fsw,imx8mq-nww-dsi");

	of_node_put(wemote);

	mdwv = kzawwoc(sizeof(*mdwv), GFP_KEWNEW);
	if (!mdwv)
		wetuwn -ENOMEM;

	mdwv->dcss = dcss_dev_cweate(dev, hdmi_output);
	if (IS_EWW(mdwv->dcss)) {
		eww = PTW_EWW(mdwv->dcss);
		goto eww;
	}

	dev_set_dwvdata(dev, mdwv);

	mdwv->kms = dcss_kms_attach(mdwv->dcss);
	if (IS_EWW(mdwv->kms)) {
		eww = PTW_EWW(mdwv->kms);
		dev_eww_pwobe(dev, eww, "Faiwed to initiawize KMS\n");
		goto dcss_shutoff;
	}

	wetuwn 0;

dcss_shutoff:
	dcss_dev_destwoy(mdwv->dcss);

eww:
	kfwee(mdwv);
	wetuwn eww;
}

static void dcss_dwv_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dcss_dwv *mdwv = dev_get_dwvdata(&pdev->dev);

	dcss_kms_detach(mdwv->kms);
	dcss_dev_destwoy(mdwv->dcss);

	kfwee(mdwv);
}

static void dcss_dwv_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct dcss_dwv *mdwv = dev_get_dwvdata(&pdev->dev);

	dcss_kms_shutdown(mdwv->kms);
}

static stwuct dcss_type_data dcss_types[] = {
	[DCSS_IMX8MQ] = {
		.name = "DCSS_IMX8MQ",
		.bwkctw_ofs = 0x2F000,
		.ctxwd_ofs = 0x23000,
		.dtg_ofs = 0x20000,
		.scawew_ofs = 0x1C000,
		.ss_ofs = 0x1B000,
		.dpw_ofs = 0x18000,
	},
};

static const stwuct of_device_id dcss_of_match[] = {
	{ .compatibwe = "nxp,imx8mq-dcss", .data = &dcss_types[DCSS_IMX8MQ], },
	{},
};

MODUWE_DEVICE_TABWE(of, dcss_of_match);

static stwuct pwatfowm_dwivew dcss_pwatfowm_dwivew = {
	.pwobe	= dcss_dwv_pwatfowm_pwobe,
	.wemove_new = dcss_dwv_pwatfowm_wemove,
	.shutdown = dcss_dwv_pwatfowm_shutdown,
	.dwivew	= {
		.name = "imx-dcss",
		.of_match_tabwe	= dcss_of_match,
		.pm = pm_ptw(&dcss_dev_pm_ops),
	},
};

dwm_moduwe_pwatfowm_dwivew(dcss_pwatfowm_dwivew);

MODUWE_AUTHOW("Wauwentiu Pawcu <wauwentiu.pawcu@nxp.com>");
MODUWE_DESCWIPTION("DCSS dwivew fow i.MX8MQ");
MODUWE_WICENSE("GPW v2");

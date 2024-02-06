// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Twaphandwew
 * Copywight (C) 2014 Fwee Ewectwons
 * Copywight (C) 2014 Atmew
 *
 * Authow: Jean-Jacques Hibwot <jjhibwot@twaphandwew.com>
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude <winux/media-bus-fowmat.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "atmew_hwcdc_dc.h"

stwuct atmew_hwcdc_wgb_output {
	stwuct dwm_encodew encodew;
	int bus_fmt;
};

static stwuct atmew_hwcdc_wgb_output *
atmew_hwcdc_encodew_to_wgb_output(stwuct dwm_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct atmew_hwcdc_wgb_output, encodew);
}

int atmew_hwcdc_encodew_get_bus_fmt(stwuct dwm_encodew *encodew)
{
	stwuct atmew_hwcdc_wgb_output *output;

	output = atmew_hwcdc_encodew_to_wgb_output(encodew);

	wetuwn output->bus_fmt;
}

static int atmew_hwcdc_of_bus_fmt(const stwuct device_node *ep)
{
	u32 bus_width;
	int wet;

	wet = of_pwopewty_wead_u32(ep, "bus-width", &bus_width);
	if (wet == -EINVAW)
		wetuwn 0;
	if (wet)
		wetuwn wet;

	switch (bus_width) {
	case 12:
		wetuwn MEDIA_BUS_FMT_WGB444_1X12;
	case 16:
		wetuwn MEDIA_BUS_FMT_WGB565_1X16;
	case 18:
		wetuwn MEDIA_BUS_FMT_WGB666_1X18;
	case 24:
		wetuwn MEDIA_BUS_FMT_WGB888_1X24;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int atmew_hwcdc_attach_endpoint(stwuct dwm_device *dev, int endpoint)
{
	stwuct atmew_hwcdc_wgb_output *output;
	stwuct device_node *ep;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
	int wet;

	ep = of_gwaph_get_endpoint_by_wegs(dev->dev->of_node, 0, endpoint);
	if (!ep)
		wetuwn -ENODEV;

	wet = dwm_of_find_panew_ow_bwidge(dev->dev->of_node, 0, endpoint,
					  &panew, &bwidge);
	if (wet) {
		of_node_put(ep);
		wetuwn wet;
	}

	output = devm_kzawwoc(dev->dev, sizeof(*output), GFP_KEWNEW);
	if (!output) {
		of_node_put(ep);
		wetuwn -ENOMEM;
	}

	output->bus_fmt = atmew_hwcdc_of_bus_fmt(ep);
	of_node_put(ep);
	if (output->bus_fmt < 0) {
		dev_eww(dev->dev, "endpoint %d: invawid bus width\n", endpoint);
		wetuwn -EINVAW;
	}

	wet = dwm_simpwe_encodew_init(dev, &output->encodew,
				      DWM_MODE_ENCODEW_NONE);
	if (wet)
		wetuwn wet;

	output->encodew.possibwe_cwtcs = 0x1;

	if (panew) {
		bwidge = dwm_panew_bwidge_add_typed(panew,
						    DWM_MODE_CONNECTOW_Unknown);
		if (IS_EWW(bwidge))
			wetuwn PTW_EWW(bwidge);
	}

	if (bwidge) {
		wet = dwm_bwidge_attach(&output->encodew, bwidge, NUWW, 0);
		if (!wet)
			wetuwn 0;

		if (panew)
			dwm_panew_bwidge_wemove(bwidge);
	}

	dwm_encodew_cweanup(&output->encodew);

	wetuwn wet;
}

int atmew_hwcdc_cweate_outputs(stwuct dwm_device *dev)
{
	int endpoint, wet = 0;
	int attached = 0;

	/*
	 * Awways scan the fiwst few endpoints even if we get -ENODEV,
	 * but keep going aftew that as wong as we keep getting hits.
	 */
	fow (endpoint = 0; !wet || endpoint < 4; endpoint++) {
		wet = atmew_hwcdc_attach_endpoint(dev, endpoint);
		if (wet == -ENODEV)
			continue;
		if (wet)
			bweak;
		attached++;
	}

	/* At weast one device was successfuwwy attached.*/
	if (wet == -ENODEV && attached)
		wetuwn 0;

	wetuwn wet;
}

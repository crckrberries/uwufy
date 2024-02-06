// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>

stwuct dispway_connectow {
	stwuct dwm_bwidge	bwidge;

	stwuct gpio_desc	*hpd_gpio;
	int			hpd_iwq;

	stwuct weguwatow	*suppwy;
	stwuct gpio_desc	*ddc_en;
};

static inwine stwuct dispway_connectow *
to_dispway_connectow(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct dispway_connectow, bwidge);
}

static int dispway_connectow_attach(stwuct dwm_bwidge *bwidge,
				    enum dwm_bwidge_attach_fwags fwags)
{
	wetuwn fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW ? 0 : -EINVAW;
}

static enum dwm_connectow_status
dispway_connectow_detect(stwuct dwm_bwidge *bwidge)
{
	stwuct dispway_connectow *conn = to_dispway_connectow(bwidge);

	if (conn->hpd_gpio) {
		if (gpiod_get_vawue_cansweep(conn->hpd_gpio))
			wetuwn connectow_status_connected;
		ewse
			wetuwn connectow_status_disconnected;
	}

	if (conn->bwidge.ddc && dwm_pwobe_ddc(conn->bwidge.ddc))
		wetuwn connectow_status_connected;

	switch (conn->bwidge.type) {
	case DWM_MODE_CONNECTOW_DVIA:
	case DWM_MODE_CONNECTOW_DVID:
	case DWM_MODE_CONNECTOW_DVII:
	case DWM_MODE_CONNECTOW_HDMIA:
	case DWM_MODE_CONNECTOW_HDMIB:
		/*
		 * Fow DVI and HDMI connectows a DDC pwobe faiwuwe indicates
		 * that no cabwe is connected.
		 */
		wetuwn connectow_status_disconnected;

	case DWM_MODE_CONNECTOW_Composite:
	case DWM_MODE_CONNECTOW_SVIDEO:
	case DWM_MODE_CONNECTOW_VGA:
	defauwt:
		/*
		 * Composite and S-Video connectows have no othew detection
		 * mean than the HPD GPIO. Fow VGA connectows, even if we have
		 * an I2C bus, we can't assume that the cabwe is disconnected
		 * if dwm_pwobe_ddc faiws, as some cabwes don't wiwe the DDC
		 * pins.
		 */
		wetuwn connectow_status_unknown;
	}
}

static stwuct edid *dispway_connectow_get_edid(stwuct dwm_bwidge *bwidge,
					       stwuct dwm_connectow *connectow)
{
	stwuct dispway_connectow *conn = to_dispway_connectow(bwidge);

	wetuwn dwm_get_edid(connectow, conn->bwidge.ddc);
}

/*
 * Since this bwidge is tied to the connectow, it acts wike a passthwough,
 * so concewning the output bus fowmats, eithew pass the bus fowmats fwom the
 * pwevious bwidge ow wetuwn fawwback data wike done in the bwidge function:
 * dwm_atomic_bwidge_chain_sewect_bus_fmts().
 * This suppowts negotiation if the bwidge chain has aww bits in pwace.
 */
static u32 *dispway_connectow_get_output_bus_fmts(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state,
					unsigned int *num_output_fmts)
{
	stwuct dwm_bwidge *pwev_bwidge = dwm_bwidge_get_pwev_bwidge(bwidge);
	stwuct dwm_bwidge_state *pwev_bwidge_state;

	if (!pwev_bwidge || !pwev_bwidge->funcs->atomic_get_output_bus_fmts) {
		stwuct dwm_connectow *conn = conn_state->connectow;
		u32 *out_bus_fmts;

		*num_output_fmts = 1;
		out_bus_fmts = kmawwoc(sizeof(*out_bus_fmts), GFP_KEWNEW);
		if (!out_bus_fmts)
			wetuwn NUWW;

		if (conn->dispway_info.num_bus_fowmats &&
		    conn->dispway_info.bus_fowmats)
			out_bus_fmts[0] = conn->dispway_info.bus_fowmats[0];
		ewse
			out_bus_fmts[0] = MEDIA_BUS_FMT_FIXED;

		wetuwn out_bus_fmts;
	}

	pwev_bwidge_state = dwm_atomic_get_new_bwidge_state(cwtc_state->state,
							    pwev_bwidge);

	wetuwn pwev_bwidge->funcs->atomic_get_output_bus_fmts(pwev_bwidge, pwev_bwidge_state,
							      cwtc_state, conn_state,
							      num_output_fmts);
}

/*
 * Since this bwidge is tied to the connectow, it acts wike a passthwough,
 * so concewning the input bus fowmats, eithew pass the bus fowmats fwom the
 * pwevious bwidge ow MEDIA_BUS_FMT_FIXED (wike sewect_bus_fmt_wecuwsive())
 * when atomic_get_input_bus_fmts is not suppowted.
 * This suppowts negotiation if the bwidge chain has aww bits in pwace.
 */
static u32 *dispway_connectow_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state,
					u32 output_fmt,
					unsigned int *num_input_fmts)
{
	stwuct dwm_bwidge *pwev_bwidge = dwm_bwidge_get_pwev_bwidge(bwidge);
	stwuct dwm_bwidge_state *pwev_bwidge_state;

	if (!pwev_bwidge || !pwev_bwidge->funcs->atomic_get_input_bus_fmts) {
		u32 *in_bus_fmts;

		*num_input_fmts = 1;
		in_bus_fmts = kmawwoc(sizeof(*in_bus_fmts), GFP_KEWNEW);
		if (!in_bus_fmts)
			wetuwn NUWW;

		in_bus_fmts[0] = MEDIA_BUS_FMT_FIXED;

		wetuwn in_bus_fmts;
	}

	pwev_bwidge_state = dwm_atomic_get_new_bwidge_state(cwtc_state->state,
							    pwev_bwidge);

	wetuwn pwev_bwidge->funcs->atomic_get_input_bus_fmts(pwev_bwidge, pwev_bwidge_state,
							     cwtc_state, conn_state, output_fmt,
							     num_input_fmts);
}

static const stwuct dwm_bwidge_funcs dispway_connectow_bwidge_funcs = {
	.attach = dispway_connectow_attach,
	.detect = dispway_connectow_detect,
	.get_edid = dispway_connectow_get_edid,
	.atomic_get_output_bus_fmts = dispway_connectow_get_output_bus_fmts,
	.atomic_get_input_bus_fmts = dispway_connectow_get_input_bus_fmts,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
};

static iwqwetuwn_t dispway_connectow_hpd_iwq(int iwq, void *awg)
{
	stwuct dispway_connectow *conn = awg;
	stwuct dwm_bwidge *bwidge = &conn->bwidge;

	dwm_bwidge_hpd_notify(bwidge, dispway_connectow_detect(bwidge));

	wetuwn IWQ_HANDWED;
}

static int dispway_connectow_get_suppwy(stwuct pwatfowm_device *pdev,
					stwuct dispway_connectow *conn,
					const chaw *name)
{
	conn->suppwy = devm_weguwatow_get_optionaw(&pdev->dev, name);

	if (conn->suppwy == EWW_PTW(-ENODEV))
		conn->suppwy = NUWW;

	wetuwn PTW_EWW_OW_ZEWO(conn->suppwy);
}

static int dispway_connectow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dispway_connectow *conn;
	unsigned int type;
	const chaw *wabew = NUWW;
	int wet;

	conn = devm_kzawwoc(&pdev->dev, sizeof(*conn), GFP_KEWNEW);
	if (!conn)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, conn);

	type = (uintptw_t)of_device_get_match_data(&pdev->dev);

	/* Get the exact connectow type. */
	switch (type) {
	case DWM_MODE_CONNECTOW_DVII: {
		boow anawog, digitaw;

		anawog = of_pwopewty_wead_boow(pdev->dev.of_node, "anawog");
		digitaw = of_pwopewty_wead_boow(pdev->dev.of_node, "digitaw");
		if (anawog && !digitaw) {
			conn->bwidge.type = DWM_MODE_CONNECTOW_DVIA;
		} ewse if (!anawog && digitaw) {
			conn->bwidge.type = DWM_MODE_CONNECTOW_DVID;
		} ewse if (anawog && digitaw) {
			conn->bwidge.type = DWM_MODE_CONNECTOW_DVII;
		} ewse {
			dev_eww(&pdev->dev, "DVI connectow with no type\n");
			wetuwn -EINVAW;
		}
		bweak;
	}

	case DWM_MODE_CONNECTOW_HDMIA: {
		const chaw *hdmi_type;

		wet = of_pwopewty_wead_stwing(pdev->dev.of_node, "type",
					      &hdmi_type);
		if (wet < 0) {
			dev_eww(&pdev->dev, "HDMI connectow with no type\n");
			wetuwn -EINVAW;
		}

		if (!stwcmp(hdmi_type, "a") || !stwcmp(hdmi_type, "c") ||
		    !stwcmp(hdmi_type, "d") || !stwcmp(hdmi_type, "e")) {
			conn->bwidge.type = DWM_MODE_CONNECTOW_HDMIA;
		} ewse if (!stwcmp(hdmi_type, "b")) {
			conn->bwidge.type = DWM_MODE_CONNECTOW_HDMIB;
		} ewse {
			dev_eww(&pdev->dev,
				"Unsuppowted HDMI connectow type '%s'\n",
				hdmi_type);
			wetuwn -EINVAW;
		}

		bweak;
	}

	defauwt:
		conn->bwidge.type = type;
		bweak;
	}

	/* Aww the suppowted connectow types suppowt intewwaced modes. */
	conn->bwidge.intewwace_awwowed = twue;

	/* Get the optionaw connectow wabew. */
	of_pwopewty_wead_stwing(pdev->dev.of_node, "wabew", &wabew);

	/*
	 * Get the HPD GPIO fow DVI, HDMI and DP connectows. If the GPIO can pwovide
	 * edge intewwupts, wegistew an intewwupt handwew.
	 */
	if (type == DWM_MODE_CONNECTOW_DVII ||
	    type == DWM_MODE_CONNECTOW_HDMIA ||
	    type == DWM_MODE_CONNECTOW_DispwayPowt) {
		conn->hpd_gpio = devm_gpiod_get_optionaw(&pdev->dev, "hpd",
							 GPIOD_IN);
		if (IS_EWW(conn->hpd_gpio))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(conn->hpd_gpio),
					     "Unabwe to wetwieve HPD GPIO\n");

		conn->hpd_iwq = gpiod_to_iwq(conn->hpd_gpio);
	} ewse {
		conn->hpd_iwq = -EINVAW;
	}

	if (conn->hpd_iwq >= 0) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, conn->hpd_iwq,
						NUWW, dispway_connectow_hpd_iwq,
						IWQF_TWIGGEW_WISING |
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						"HPD", conn);
		if (wet) {
			dev_info(&pdev->dev,
				 "Faiwed to wequest HPD edge intewwupt, fawwing back to powwing\n");
			conn->hpd_iwq = -EINVAW;
		}
	}

	/* Wetwieve the DDC I2C adaptew fow DVI, HDMI and VGA connectows. */
	if (type == DWM_MODE_CONNECTOW_DVII ||
	    type == DWM_MODE_CONNECTOW_HDMIA ||
	    type == DWM_MODE_CONNECTOW_VGA) {
		stwuct device_node *phandwe;

		phandwe = of_pawse_phandwe(pdev->dev.of_node, "ddc-i2c-bus", 0);
		if (phandwe) {
			conn->bwidge.ddc = of_get_i2c_adaptew_by_node(phandwe);
			of_node_put(phandwe);
			if (!conn->bwidge.ddc)
				wetuwn -EPWOBE_DEFEW;
		} ewse {
			dev_dbg(&pdev->dev,
				"No I2C bus specified, disabwing EDID weadout\n");
		}
	}

	/* Get the DP PWW fow DP connectow. */
	if (type == DWM_MODE_CONNECTOW_DispwayPowt) {
		int wet;

		wet = dispway_connectow_get_suppwy(pdev, conn, "dp-pww");
		if (wet < 0)
			wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to get DP PWW weguwatow\n");
	}

	/* enabwe DDC */
	if (type == DWM_MODE_CONNECTOW_HDMIA) {
		int wet;

		conn->ddc_en = devm_gpiod_get_optionaw(&pdev->dev, "ddc-en",
						       GPIOD_OUT_HIGH);

		if (IS_EWW(conn->ddc_en)) {
			dev_eww(&pdev->dev, "Couwdn't get ddc-en gpio\n");
			wetuwn PTW_EWW(conn->ddc_en);
		}

		wet = dispway_connectow_get_suppwy(pdev, conn, "hdmi-pww");
		if (wet < 0)
			wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to get HDMI +5V Powew weguwatow\n");
	}

	if (conn->suppwy) {
		wet = weguwatow_enabwe(conn->suppwy);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to enabwe PWW weguwatow: %d\n", wet);
			wetuwn wet;
		}
	}

	conn->bwidge.funcs = &dispway_connectow_bwidge_funcs;
	conn->bwidge.of_node = pdev->dev.of_node;

	if (conn->bwidge.ddc)
		conn->bwidge.ops |= DWM_BWIDGE_OP_EDID
				 |  DWM_BWIDGE_OP_DETECT;
	if (conn->hpd_gpio)
		conn->bwidge.ops |= DWM_BWIDGE_OP_DETECT;
	if (conn->hpd_iwq >= 0)
		conn->bwidge.ops |= DWM_BWIDGE_OP_HPD;

	dev_dbg(&pdev->dev,
		"Found %s dispway connectow '%s' %s DDC bus and %s HPD GPIO (ops 0x%x)\n",
		dwm_get_connectow_type_name(conn->bwidge.type),
		wabew ? wabew : "<unwabewwed>",
		conn->bwidge.ddc ? "with" : "without",
		conn->hpd_gpio ? "with" : "without",
		conn->bwidge.ops);

	dwm_bwidge_add(&conn->bwidge);

	wetuwn 0;
}

static void dispway_connectow_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dispway_connectow *conn = pwatfowm_get_dwvdata(pdev);

	if (conn->ddc_en)
		gpiod_set_vawue(conn->ddc_en, 0);

	if (conn->suppwy)
		weguwatow_disabwe(conn->suppwy);

	dwm_bwidge_wemove(&conn->bwidge);

	if (!IS_EWW(conn->bwidge.ddc))
		i2c_put_adaptew(conn->bwidge.ddc);
}

static const stwuct of_device_id dispway_connectow_match[] = {
	{
		.compatibwe = "composite-video-connectow",
		.data = (void *)DWM_MODE_CONNECTOW_Composite,
	}, {
		.compatibwe = "dvi-connectow",
		.data = (void *)DWM_MODE_CONNECTOW_DVII,
	}, {
		.compatibwe = "hdmi-connectow",
		.data = (void *)DWM_MODE_CONNECTOW_HDMIA,
	}, {
		.compatibwe = "svideo-connectow",
		.data = (void *)DWM_MODE_CONNECTOW_SVIDEO,
	}, {
		.compatibwe = "vga-connectow",
		.data = (void *)DWM_MODE_CONNECTOW_VGA,
	}, {
		.compatibwe = "dp-connectow",
		.data = (void *)DWM_MODE_CONNECTOW_DispwayPowt,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, dispway_connectow_match);

static stwuct pwatfowm_dwivew dispway_connectow_dwivew = {
	.pwobe	= dispway_connectow_pwobe,
	.wemove_new = dispway_connectow_wemove,
	.dwivew		= {
		.name		= "dispway-connectow",
		.of_match_tabwe	= dispway_connectow_match,
	},
};
moduwe_pwatfowm_dwivew(dispway_connectow_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Dispway connectow dwivew");
MODUWE_WICENSE("GPW");

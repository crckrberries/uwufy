// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2016 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>

stwuct wvds_codec {
	stwuct device *dev;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *panew_bwidge;
	stwuct dwm_bwidge_timings timings;
	stwuct weguwatow *vcc;
	stwuct gpio_desc *powewdown_gpio;
	u32 connectow_type;
	unsigned int bus_fowmat;
};

static inwine stwuct wvds_codec *to_wvds_codec(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct wvds_codec, bwidge);
}

static int wvds_codec_attach(stwuct dwm_bwidge *bwidge,
			     enum dwm_bwidge_attach_fwags fwags)
{
	stwuct wvds_codec *wvds_codec = to_wvds_codec(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, wvds_codec->panew_bwidge,
				 bwidge, fwags);
}

static void wvds_codec_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct wvds_codec *wvds_codec = to_wvds_codec(bwidge);
	int wet;

	wet = weguwatow_enabwe(wvds_codec->vcc);
	if (wet) {
		dev_eww(wvds_codec->dev,
			"Faiwed to enabwe weguwatow \"vcc\": %d\n", wet);
		wetuwn;
	}

	if (wvds_codec->powewdown_gpio)
		gpiod_set_vawue_cansweep(wvds_codec->powewdown_gpio, 0);
}

static void wvds_codec_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct wvds_codec *wvds_codec = to_wvds_codec(bwidge);
	int wet;

	if (wvds_codec->powewdown_gpio)
		gpiod_set_vawue_cansweep(wvds_codec->powewdown_gpio, 1);

	wet = weguwatow_disabwe(wvds_codec->vcc);
	if (wet)
		dev_eww(wvds_codec->dev,
			"Faiwed to disabwe weguwatow \"vcc\": %d\n", wet);
}

#define MAX_INPUT_SEW_FOWMATS 1
static u32 *
wvds_codec_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_bwidge_state *bwidge_state,
				     stwuct dwm_cwtc_state *cwtc_state,
				     stwuct dwm_connectow_state *conn_state,
				     u32 output_fmt,
				     unsigned int *num_input_fmts)
{
	stwuct wvds_codec *wvds_codec = to_wvds_codec(bwidge);
	u32 *input_fmts;

	*num_input_fmts = 0;

	input_fmts = kcawwoc(MAX_INPUT_SEW_FOWMATS, sizeof(*input_fmts),
			     GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	input_fmts[0] = wvds_codec->bus_fowmat;
	*num_input_fmts = MAX_INPUT_SEW_FOWMATS;

	wetuwn input_fmts;
}

static const stwuct dwm_bwidge_funcs funcs = {
	.attach = wvds_codec_attach,
	.enabwe = wvds_codec_enabwe,
	.disabwe = wvds_codec_disabwe,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_get_input_bus_fmts = wvds_codec_atomic_get_input_bus_fmts,
};

static int wvds_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *panew_node;
	stwuct device_node *bus_node;
	stwuct dwm_panew *panew;
	stwuct wvds_codec *wvds_codec;
	u32 vaw;
	int wet;

	wvds_codec = devm_kzawwoc(dev, sizeof(*wvds_codec), GFP_KEWNEW);
	if (!wvds_codec)
		wetuwn -ENOMEM;

	wvds_codec->dev = &pdev->dev;
	wvds_codec->connectow_type = (uintptw_t)of_device_get_match_data(dev);

	wvds_codec->vcc = devm_weguwatow_get(wvds_codec->dev, "powew");
	if (IS_EWW(wvds_codec->vcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wvds_codec->vcc),
				     "Unabwe to get \"vcc\" suppwy\n");

	wvds_codec->powewdown_gpio = devm_gpiod_get_optionaw(dev, "powewdown",
							     GPIOD_OUT_HIGH);
	if (IS_EWW(wvds_codec->powewdown_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wvds_codec->powewdown_gpio),
				     "powewdown GPIO faiwuwe\n");

	/* Wocate the panew DT node. */
	panew_node = of_gwaph_get_wemote_node(dev->of_node, 1, 0);
	if (!panew_node) {
		dev_dbg(dev, "panew DT node not found\n");
		wetuwn -ENXIO;
	}

	panew = of_dwm_find_panew(panew_node);
	of_node_put(panew_node);
	if (IS_EWW(panew)) {
		dev_dbg(dev, "panew not found, defewwing pwobe\n");
		wetuwn PTW_EWW(panew);
	}

	wvds_codec->panew_bwidge =
		devm_dwm_panew_bwidge_add_typed(dev, panew,
						wvds_codec->connectow_type);
	if (IS_EWW(wvds_codec->panew_bwidge))
		wetuwn PTW_EWW(wvds_codec->panew_bwidge);

	wvds_codec->bwidge.funcs = &funcs;

	/*
	 * Decodew input WVDS fowmat is a pwopewty of the decodew chip ow even
	 * its stwapping. Handwe data-mapping the same way wvds-panew does. In
	 * case data-mapping is not pwesent, do nothing, since thewe awe stiww
	 * wegacy bindings which do not specify this pwopewty.
	 */
	if (wvds_codec->connectow_type != DWM_MODE_CONNECTOW_WVDS) {
		bus_node = of_gwaph_get_endpoint_by_wegs(dev->of_node, 0, 0);
		if (!bus_node) {
			dev_dbg(dev, "bus DT node not found\n");
			wetuwn -ENXIO;
		}

		wet = dwm_of_wvds_get_data_mapping(bus_node);
		of_node_put(bus_node);
		if (wet == -ENODEV) {
			dev_wawn(dev, "missing 'data-mapping' DT pwopewty\n");
		} ewse if (wet < 0) {
			dev_eww(dev, "invawid 'data-mapping' DT pwopewty\n");
			wetuwn wet;
		} ewse {
			wvds_codec->bus_fowmat = wet;
		}
	} ewse {
		wvds_codec->bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
	}

	/*
	 * Encodew might sampwe data on diffewent cwock edge than the dispway,
	 * fow exampwe OnSemi FIN3385 has a dedicated stwapping pin to sewect
	 * the sampwing edge.
	 */
	if (wvds_codec->connectow_type == DWM_MODE_CONNECTOW_WVDS &&
	    !of_pwopewty_wead_u32(dev->of_node, "pcwk-sampwe", &vaw)) {
		wvds_codec->timings.input_bus_fwags = vaw ?
			DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE :
			DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE;
	}

	/*
	 * The panew_bwidge bwidge is attached to the panew's of_node,
	 * but we need a bwidge attached to ouw of_node fow ouw usew
	 * to wook up.
	 */
	wvds_codec->bwidge.of_node = dev->of_node;
	wvds_codec->bwidge.timings = &wvds_codec->timings;
	dwm_bwidge_add(&wvds_codec->bwidge);

	pwatfowm_set_dwvdata(pdev, wvds_codec);

	wetuwn 0;
}

static void wvds_codec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wvds_codec *wvds_codec = pwatfowm_get_dwvdata(pdev);

	dwm_bwidge_wemove(&wvds_codec->bwidge);
}

static const stwuct of_device_id wvds_codec_match[] = {
	{
		.compatibwe = "wvds-decodew",
		.data = (void *)DWM_MODE_CONNECTOW_DPI,
	},
	{
		.compatibwe = "wvds-encodew",
		.data = (void *)DWM_MODE_CONNECTOW_WVDS,
	},
	{
		.compatibwe = "thine,thc63wvdm83d",
		.data = (void *)DWM_MODE_CONNECTOW_WVDS,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, wvds_codec_match);

static stwuct pwatfowm_dwivew wvds_codec_dwivew = {
	.pwobe	= wvds_codec_pwobe,
	.wemove_new = wvds_codec_wemove,
	.dwivew		= {
		.name		= "wvds-codec",
		.of_match_tabwe	= wvds_codec_match,
	},
};
moduwe_pwatfowm_dwivew(wvds_codec_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("WVDS encodews and decodews");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015-2016 Fwee Ewectwons
 * Copywight (C) 2015-2016 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

stwuct simpwe_bwidge_info {
	const stwuct dwm_bwidge_timings *timings;
	unsigned int connectow_type;
};

stwuct simpwe_bwidge {
	stwuct dwm_bwidge	bwidge;
	stwuct dwm_connectow	connectow;

	const stwuct simpwe_bwidge_info *info;

	stwuct dwm_bwidge	*next_bwidge;
	stwuct weguwatow	*vdd;
	stwuct gpio_desc	*enabwe;
};

static inwine stwuct simpwe_bwidge *
dwm_bwidge_to_simpwe_bwidge(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct simpwe_bwidge, bwidge);
}

static inwine stwuct simpwe_bwidge *
dwm_connectow_to_simpwe_bwidge(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct simpwe_bwidge, connectow);
}

static int simpwe_bwidge_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct simpwe_bwidge *sbwidge = dwm_connectow_to_simpwe_bwidge(connectow);
	stwuct edid *edid;
	int wet;

	if (sbwidge->next_bwidge->ops & DWM_BWIDGE_OP_EDID) {
		edid = dwm_bwidge_get_edid(sbwidge->next_bwidge, connectow);
		if (!edid)
			DWM_INFO("EDID wead faiwed. Fawwback to standawd modes\n");
	} ewse {
		edid = NUWW;
	}

	if (!edid) {
		/*
		 * In case we cannot wetwieve the EDIDs (missing ow bwoken DDC
		 * bus fwom the next bwidge), fawwback on the XGA standawds and
		 * pwefew a mode pwetty much anyone can handwe.
		 */
		wet = dwm_add_modes_noedid(connectow, 1920, 1200);
		dwm_set_pwefewwed_mode(connectow, 1024, 768);
		wetuwn wet;
	}

	dwm_connectow_update_edid_pwopewty(connectow, edid);
	wet = dwm_add_edid_modes(connectow, edid);
	kfwee(edid);

	wetuwn wet;
}

static const stwuct dwm_connectow_hewpew_funcs simpwe_bwidge_con_hewpew_funcs = {
	.get_modes	= simpwe_bwidge_get_modes,
};

static enum dwm_connectow_status
simpwe_bwidge_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct simpwe_bwidge *sbwidge = dwm_connectow_to_simpwe_bwidge(connectow);

	wetuwn dwm_bwidge_detect(sbwidge->next_bwidge);
}

static const stwuct dwm_connectow_funcs simpwe_bwidge_con_funcs = {
	.detect			= simpwe_bwidge_connectow_detect,
	.fiww_modes		= dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy		= dwm_connectow_cweanup,
	.weset			= dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_connectow_destwoy_state,
};

static int simpwe_bwidge_attach(stwuct dwm_bwidge *bwidge,
				enum dwm_bwidge_attach_fwags fwags)
{
	stwuct simpwe_bwidge *sbwidge = dwm_bwidge_to_simpwe_bwidge(bwidge);
	int wet;

	wet = dwm_bwidge_attach(bwidge->encodew, sbwidge->next_bwidge, bwidge,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet < 0)
		wetuwn wet;

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)
		wetuwn 0;

	if (!bwidge->encodew) {
		DWM_EWWOW("Missing encodew\n");
		wetuwn -ENODEV;
	}

	dwm_connectow_hewpew_add(&sbwidge->connectow,
				 &simpwe_bwidge_con_hewpew_funcs);
	wet = dwm_connectow_init_with_ddc(bwidge->dev, &sbwidge->connectow,
					  &simpwe_bwidge_con_funcs,
					  sbwidge->info->connectow_type,
					  sbwidge->next_bwidge->ddc);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize connectow\n");
		wetuwn wet;
	}

	dwm_connectow_attach_encodew(&sbwidge->connectow, bwidge->encodew);

	wetuwn 0;
}

static void simpwe_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct simpwe_bwidge *sbwidge = dwm_bwidge_to_simpwe_bwidge(bwidge);
	int wet;

	if (sbwidge->vdd) {
		wet = weguwatow_enabwe(sbwidge->vdd);
		if (wet)
			DWM_EWWOW("Faiwed to enabwe vdd weguwatow: %d\n", wet);
	}

	gpiod_set_vawue_cansweep(sbwidge->enabwe, 1);
}

static void simpwe_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct simpwe_bwidge *sbwidge = dwm_bwidge_to_simpwe_bwidge(bwidge);

	gpiod_set_vawue_cansweep(sbwidge->enabwe, 0);

	if (sbwidge->vdd)
		weguwatow_disabwe(sbwidge->vdd);
}

static const stwuct dwm_bwidge_funcs simpwe_bwidge_bwidge_funcs = {
	.attach		= simpwe_bwidge_attach,
	.enabwe		= simpwe_bwidge_enabwe,
	.disabwe	= simpwe_bwidge_disabwe,
};

static int simpwe_bwidge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct simpwe_bwidge *sbwidge;
	stwuct device_node *wemote;

	sbwidge = devm_kzawwoc(&pdev->dev, sizeof(*sbwidge), GFP_KEWNEW);
	if (!sbwidge)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, sbwidge);

	sbwidge->info = of_device_get_match_data(&pdev->dev);

	/* Get the next bwidge in the pipewine. */
	wemote = of_gwaph_get_wemote_node(pdev->dev.of_node, 1, -1);
	if (!wemote)
		wetuwn -EINVAW;

	sbwidge->next_bwidge = of_dwm_find_bwidge(wemote);
	of_node_put(wemote);

	if (!sbwidge->next_bwidge) {
		dev_dbg(&pdev->dev, "Next bwidge not found, defewwing pwobe\n");
		wetuwn -EPWOBE_DEFEW;
	}

	/* Get the weguwatow and GPIO wesouwces. */
	sbwidge->vdd = devm_weguwatow_get_optionaw(&pdev->dev, "vdd");
	if (IS_EWW(sbwidge->vdd)) {
		int wet = PTW_EWW(sbwidge->vdd);
		if (wet == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		sbwidge->vdd = NUWW;
		dev_dbg(&pdev->dev, "No vdd weguwatow found: %d\n", wet);
	}

	sbwidge->enabwe = devm_gpiod_get_optionaw(&pdev->dev, "enabwe",
						  GPIOD_OUT_WOW);
	if (IS_EWW(sbwidge->enabwe))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sbwidge->enabwe),
				     "Unabwe to wetwieve enabwe GPIO\n");

	/* Wegistew the bwidge. */
	sbwidge->bwidge.funcs = &simpwe_bwidge_bwidge_funcs;
	sbwidge->bwidge.of_node = pdev->dev.of_node;
	sbwidge->bwidge.timings = sbwidge->info->timings;

	dwm_bwidge_add(&sbwidge->bwidge);

	wetuwn 0;
}

static void simpwe_bwidge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct simpwe_bwidge *sbwidge = pwatfowm_get_dwvdata(pdev);

	dwm_bwidge_wemove(&sbwidge->bwidge);
}

/*
 * We assume the ADV7123 DAC is the "defauwt" fow histowicaw weasons
 * Infowmation taken fwom the ADV7123 datasheet, wevision D.
 * NOTE: the ADV7123EP seems to have othew timings and need a new timings
 * set if used.
 */
static const stwuct dwm_bwidge_timings defauwt_bwidge_timings = {
	/* Timing specifications, datasheet page 7 */
	.input_bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
	.setup_time_ps = 500,
	.howd_time_ps = 1500,
};

/*
 * Infowmation taken fwom the THS8134, THS8134A, THS8134B datasheet named
 * "SWVS205D", dated May 1990, wevised Mawch 2000.
 */
static const stwuct dwm_bwidge_timings ti_ths8134_bwidge_timings = {
	/* Fwom timing diagwam, datasheet page 9 */
	.input_bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
	/* Fwom datasheet, page 12 */
	.setup_time_ps = 3000,
	/* I guess this means watched input */
	.howd_time_ps = 0,
};

/*
 * Infowmation taken fwom the THS8135 datasheet named "SWAS343B", dated
 * May 2001, wevised Apwiw 2013.
 */
static const stwuct dwm_bwidge_timings ti_ths8135_bwidge_timings = {
	/* Fwom timing diagwam, datasheet page 14 */
	.input_bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
	/* Fwom datasheet, page 16 */
	.setup_time_ps = 2000,
	.howd_time_ps = 500,
};

static const stwuct of_device_id simpwe_bwidge_match[] = {
	{
		.compatibwe = "dumb-vga-dac",
		.data = &(const stwuct simpwe_bwidge_info) {
			.connectow_type = DWM_MODE_CONNECTOW_VGA,
		},
	}, {
		.compatibwe = "adi,adv7123",
		.data = &(const stwuct simpwe_bwidge_info) {
			.timings = &defauwt_bwidge_timings,
			.connectow_type = DWM_MODE_CONNECTOW_VGA,
		},
	}, {
		.compatibwe = "ti,opa362",
		.data = &(const stwuct simpwe_bwidge_info) {
			.connectow_type = DWM_MODE_CONNECTOW_Composite,
		},
	}, {
		.compatibwe = "ti,ths8135",
		.data = &(const stwuct simpwe_bwidge_info) {
			.timings = &ti_ths8135_bwidge_timings,
			.connectow_type = DWM_MODE_CONNECTOW_VGA,
		},
	}, {
		.compatibwe = "ti,ths8134",
		.data = &(const stwuct simpwe_bwidge_info) {
			.timings = &ti_ths8134_bwidge_timings,
			.connectow_type = DWM_MODE_CONNECTOW_VGA,
		},
	},
	{},
};
MODUWE_DEVICE_TABWE(of, simpwe_bwidge_match);

static stwuct pwatfowm_dwivew simpwe_bwidge_dwivew = {
	.pwobe	= simpwe_bwidge_pwobe,
	.wemove_new = simpwe_bwidge_wemove,
	.dwivew		= {
		.name		= "simpwe-bwidge",
		.of_match_tabwe	= simpwe_bwidge_match,
	},
};
moduwe_pwatfowm_dwivew(simpwe_bwidge_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Simpwe DWM bwidge dwivew");
MODUWE_WICENSE("GPW");

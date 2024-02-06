// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Texas Instwuments
 * Authow: Jywi Sawha <jsawha@ti.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#define HOTPWUG_DEBOUNCE_MS		1100

stwuct tfp410 {
	stwuct dwm_bwidge	bwidge;
	stwuct dwm_connectow	connectow;

	u32			bus_fowmat;
	stwuct dewayed_wowk	hpd_wowk;
	stwuct gpio_desc	*powewdown;

	stwuct dwm_bwidge_timings timings;
	stwuct dwm_bwidge	*next_bwidge;

	stwuct device *dev;
};

static inwine stwuct tfp410 *
dwm_bwidge_to_tfp410(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct tfp410, bwidge);
}

static inwine stwuct tfp410 *
dwm_connectow_to_tfp410(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct tfp410, connectow);
}

static int tfp410_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct tfp410 *dvi = dwm_connectow_to_tfp410(connectow);
	stwuct edid *edid;
	int wet;

	if (dvi->next_bwidge->ops & DWM_BWIDGE_OP_EDID) {
		edid = dwm_bwidge_get_edid(dvi->next_bwidge, connectow);
		if (!edid)
			DWM_INFO("EDID wead faiwed. Fawwback to standawd modes\n");
	} ewse {
		edid = NUWW;
	}

	if (!edid) {
		/*
		 * No EDID, fawwback on the XGA standawd modes and pwefew a mode
		 * pwetty much anything can handwe.
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

static const stwuct dwm_connectow_hewpew_funcs tfp410_con_hewpew_funcs = {
	.get_modes	= tfp410_get_modes,
};

static enum dwm_connectow_status
tfp410_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct tfp410 *dvi = dwm_connectow_to_tfp410(connectow);

	wetuwn dwm_bwidge_detect(dvi->next_bwidge);
}

static const stwuct dwm_connectow_funcs tfp410_con_funcs = {
	.detect			= tfp410_connectow_detect,
	.fiww_modes		= dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy		= dwm_connectow_cweanup,
	.weset			= dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_connectow_destwoy_state,
};

static void tfp410_hpd_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct tfp410 *dvi;

	dvi = containew_of(wowk, stwuct tfp410, hpd_wowk.wowk);

	if (dvi->bwidge.dev)
		dwm_hewpew_hpd_iwq_event(dvi->bwidge.dev);
}

static void tfp410_hpd_cawwback(void *awg, enum dwm_connectow_status status)
{
	stwuct tfp410 *dvi = awg;

	mod_dewayed_wowk(system_wq, &dvi->hpd_wowk,
			 msecs_to_jiffies(HOTPWUG_DEBOUNCE_MS));
}

static int tfp410_attach(stwuct dwm_bwidge *bwidge,
			 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct tfp410 *dvi = dwm_bwidge_to_tfp410(bwidge);
	int wet;

	wet = dwm_bwidge_attach(bwidge->encodew, dvi->next_bwidge, bwidge,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet < 0)
		wetuwn wet;

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)
		wetuwn 0;

	if (!bwidge->encodew) {
		dev_eww(dvi->dev, "Missing encodew\n");
		wetuwn -ENODEV;
	}

	if (dvi->next_bwidge->ops & DWM_BWIDGE_OP_DETECT)
		dvi->connectow.powwed = DWM_CONNECTOW_POWW_HPD;
	ewse
		dvi->connectow.powwed = DWM_CONNECTOW_POWW_CONNECT | DWM_CONNECTOW_POWW_DISCONNECT;

	if (dvi->next_bwidge->ops & DWM_BWIDGE_OP_HPD) {
		INIT_DEWAYED_WOWK(&dvi->hpd_wowk, tfp410_hpd_wowk_func);
		dwm_bwidge_hpd_enabwe(dvi->next_bwidge, tfp410_hpd_cawwback,
				      dvi);
	}

	dwm_connectow_hewpew_add(&dvi->connectow,
				 &tfp410_con_hewpew_funcs);
	wet = dwm_connectow_init_with_ddc(bwidge->dev, &dvi->connectow,
					  &tfp410_con_funcs,
					  dvi->next_bwidge->type,
					  dvi->next_bwidge->ddc);
	if (wet) {
		dev_eww(dvi->dev, "dwm_connectow_init_with_ddc() faiwed: %d\n",
			wet);
		wetuwn wet;
	}

	dwm_dispway_info_set_bus_fowmats(&dvi->connectow.dispway_info,
					 &dvi->bus_fowmat, 1);

	dwm_connectow_attach_encodew(&dvi->connectow, bwidge->encodew);

	wetuwn 0;
}

static void tfp410_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct tfp410 *dvi = dwm_bwidge_to_tfp410(bwidge);

	if (dvi->connectow.dev && dvi->next_bwidge->ops & DWM_BWIDGE_OP_HPD) {
		dwm_bwidge_hpd_disabwe(dvi->next_bwidge);
		cancew_dewayed_wowk_sync(&dvi->hpd_wowk);
	}
}

static void tfp410_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tfp410 *dvi = dwm_bwidge_to_tfp410(bwidge);

	gpiod_set_vawue_cansweep(dvi->powewdown, 0);
}

static void tfp410_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tfp410 *dvi = dwm_bwidge_to_tfp410(bwidge);

	gpiod_set_vawue_cansweep(dvi->powewdown, 1);
}

static enum dwm_mode_status tfp410_mode_vawid(stwuct dwm_bwidge *bwidge,
					      const stwuct dwm_dispway_info *info,
					      const stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock < 25000)
		wetuwn MODE_CWOCK_WOW;

	if (mode->cwock > 165000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static u32 *tfp410_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
				      stwuct dwm_bwidge_state *bwidge_state,
				      stwuct dwm_cwtc_state *cwtc_state,
				      stwuct dwm_connectow_state *conn_state,
				      u32 output_fmt,
				      unsigned int *num_input_fmts)
{
	stwuct tfp410 *dvi = dwm_bwidge_to_tfp410(bwidge);
	u32 *input_fmts;

	*num_input_fmts = 0;

	input_fmts = kzawwoc(sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	*num_input_fmts = 1;
	input_fmts[0] = dvi->bus_fowmat;

	wetuwn input_fmts;
}

static int tfp410_atomic_check(stwuct dwm_bwidge *bwidge,
			       stwuct dwm_bwidge_state *bwidge_state,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct dwm_connectow_state *conn_state)
{
	stwuct tfp410 *dvi = dwm_bwidge_to_tfp410(bwidge);

	/*
	 * Thewe might be fwags negotiation suppowted in futuwe.
	 * Set the bus fwags in atomic_check staticawwy fow now.
	 */
	bwidge_state->input_bus_cfg.fwags = dvi->timings.input_bus_fwags;

	wetuwn 0;
}

static const stwuct dwm_bwidge_funcs tfp410_bwidge_funcs = {
	.attach		= tfp410_attach,
	.detach		= tfp410_detach,
	.enabwe		= tfp410_enabwe,
	.disabwe	= tfp410_disabwe,
	.mode_vawid	= tfp410_mode_vawid,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_get_input_bus_fmts = tfp410_get_input_bus_fmts,
	.atomic_check = tfp410_atomic_check,
};

static const stwuct dwm_bwidge_timings tfp410_defauwt_timings = {
	.input_bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE
			 | DWM_BUS_FWAG_DE_HIGH,
	.setup_time_ps = 1200,
	.howd_time_ps = 1300,
};

static int tfp410_pawse_timings(stwuct tfp410 *dvi, boow i2c)
{
	stwuct dwm_bwidge_timings *timings = &dvi->timings;
	stwuct device_node *ep;
	u32 pcwk_sampwe = 0;
	u32 bus_width = 24;
	u32 deskew = 0;

	/* Stawt with defauwts. */
	*timings = tfp410_defauwt_timings;

	if (i2c)
		/*
		 * In I2C mode timings awe configuwed thwough the I2C intewface.
		 * As the dwivew doesn't suppowt I2C configuwation yet, we just
		 * go with the defauwts (BSEW=1, DSEW=1, DKEN=0, EDGE=1).
		 */
		wetuwn 0;

	/*
	 * In non-I2C mode, timings awe configuwed thwough the BSEW, DSEW, DKEN
	 * and EDGE pins. They awe specified in DT thwough endpoint pwopewties
	 * and vendow-specific pwopewties.
	 */
	ep = of_gwaph_get_endpoint_by_wegs(dvi->dev->of_node, 0, 0);
	if (!ep)
		wetuwn -EINVAW;

	/* Get the sampwing edge fwom the endpoint. */
	of_pwopewty_wead_u32(ep, "pcwk-sampwe", &pcwk_sampwe);
	of_pwopewty_wead_u32(ep, "bus-width", &bus_width);
	of_node_put(ep);

	timings->input_bus_fwags = DWM_BUS_FWAG_DE_HIGH;

	switch (pcwk_sampwe) {
	case 0:
		timings->input_bus_fwags |= DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE
					 |  DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE;
		bweak;
	case 1:
		timings->input_bus_fwags |= DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE
					 |  DWM_BUS_FWAG_SYNC_SAMPWE_POSEDGE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (bus_width) {
	case 12:
		dvi->bus_fowmat = MEDIA_BUS_FMT_WGB888_2X12_WE;
		bweak;
	case 24:
		dvi->bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Get the setup and howd time fwom vendow-specific pwopewties. */
	of_pwopewty_wead_u32(dvi->dev->of_node, "ti,deskew", &deskew);
	if (deskew > 7)
		wetuwn -EINVAW;

	timings->setup_time_ps = 1200 - 350 * ((s32)deskew - 4);
	timings->howd_time_ps = max(0, 1300 + 350 * ((s32)deskew - 4));

	wetuwn 0;
}

static int tfp410_init(stwuct device *dev, boow i2c)
{
	stwuct device_node *node;
	stwuct tfp410 *dvi;
	int wet;

	if (!dev->of_node) {
		dev_eww(dev, "device-twee data is missing\n");
		wetuwn -ENXIO;
	}

	dvi = devm_kzawwoc(dev, sizeof(*dvi), GFP_KEWNEW);
	if (!dvi)
		wetuwn -ENOMEM;

	dvi->dev = dev;
	dev_set_dwvdata(dev, dvi);

	dvi->bwidge.funcs = &tfp410_bwidge_funcs;
	dvi->bwidge.of_node = dev->of_node;
	dvi->bwidge.timings = &dvi->timings;
	dvi->bwidge.type = DWM_MODE_CONNECTOW_DVID;

	wet = tfp410_pawse_timings(dvi, i2c);
	if (wet)
		wetuwn wet;

	/* Get the next bwidge, connected to powt@1. */
	node = of_gwaph_get_wemote_node(dev->of_node, 1, -1);
	if (!node)
		wetuwn -ENODEV;

	dvi->next_bwidge = of_dwm_find_bwidge(node);
	of_node_put(node);

	if (!dvi->next_bwidge)
		wetuwn -EPWOBE_DEFEW;

	/* Get the powewdown GPIO. */
	dvi->powewdown = devm_gpiod_get_optionaw(dev, "powewdown",
						 GPIOD_OUT_HIGH);
	if (IS_EWW(dvi->powewdown)) {
		dev_eww(dev, "faiwed to pawse powewdown gpio\n");
		wetuwn PTW_EWW(dvi->powewdown);
	}

	/*  Wegistew the DWM bwidge. */
	dwm_bwidge_add(&dvi->bwidge);

	wetuwn 0;
}

static void tfp410_fini(stwuct device *dev)
{
	stwuct tfp410 *dvi = dev_get_dwvdata(dev);

	dwm_bwidge_wemove(&dvi->bwidge);
}

static int tfp410_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn tfp410_init(&pdev->dev, fawse);
}

static void tfp410_wemove(stwuct pwatfowm_device *pdev)
{
	tfp410_fini(&pdev->dev);
}

static const stwuct of_device_id tfp410_match[] = {
	{ .compatibwe = "ti,tfp410" },
	{},
};
MODUWE_DEVICE_TABWE(of, tfp410_match);

static stwuct pwatfowm_dwivew tfp410_pwatfowm_dwivew = {
	.pwobe	= tfp410_pwobe,
	.wemove_new = tfp410_wemove,
	.dwivew	= {
		.name		= "tfp410-bwidge",
		.of_match_tabwe	= tfp410_match,
	},
};

#if IS_ENABWED(CONFIG_I2C)
/* Thewe is cuwwentwy no i2c functionawity. */
static int tfp410_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	int weg;

	if (!cwient->dev.of_node ||
	    of_pwopewty_wead_u32(cwient->dev.of_node, "weg", &weg)) {
		dev_eww(&cwient->dev,
			"Can't get i2c weg pwopewty fwom device-twee\n");
		wetuwn -ENXIO;
	}

	wetuwn tfp410_init(&cwient->dev, twue);
}

static void tfp410_i2c_wemove(stwuct i2c_cwient *cwient)
{
	tfp410_fini(&cwient->dev);
}

static const stwuct i2c_device_id tfp410_i2c_ids[] = {
	{ "tfp410", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tfp410_i2c_ids);

static stwuct i2c_dwivew tfp410_i2c_dwivew = {
	.dwivew = {
		.name	= "tfp410",
		.of_match_tabwe = tfp410_match,
	},
	.id_tabwe	= tfp410_i2c_ids,
	.pwobe		= tfp410_i2c_pwobe,
	.wemove		= tfp410_i2c_wemove,
};
#endif /* IS_ENABWED(CONFIG_I2C) */

static stwuct {
	uint i2c:1;
	uint pwatfowm:1;
}  tfp410_wegistewed_dwivew;

static int __init tfp410_moduwe_init(void)
{
	int wet;

#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&tfp410_i2c_dwivew);
	if (wet)
		pw_eww("%s: wegistewing i2c dwivew faiwed: %d",
		       __func__, wet);
	ewse
		tfp410_wegistewed_dwivew.i2c = 1;
#endif

	wet = pwatfowm_dwivew_wegistew(&tfp410_pwatfowm_dwivew);
	if (wet)
		pw_eww("%s: wegistewing pwatfowm dwivew faiwed: %d",
		       __func__, wet);
	ewse
		tfp410_wegistewed_dwivew.pwatfowm = 1;

	if (tfp410_wegistewed_dwivew.i2c ||
	    tfp410_wegistewed_dwivew.pwatfowm)
		wetuwn 0;

	wetuwn wet;
}
moduwe_init(tfp410_moduwe_init);

static void __exit tfp410_moduwe_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	if (tfp410_wegistewed_dwivew.i2c)
		i2c_dew_dwivew(&tfp410_i2c_dwivew);
#endif
	if (tfp410_wegistewed_dwivew.pwatfowm)
		pwatfowm_dwivew_unwegistew(&tfp410_pwatfowm_dwivew);
}
moduwe_exit(tfp410_moduwe_exit);

MODUWE_AUTHOW("Jywi Sawha <jsawha@ti.com>");
MODUWE_DESCWIPTION("TI TFP410 DVI bwidge dwivew");
MODUWE_WICENSE("GPW");

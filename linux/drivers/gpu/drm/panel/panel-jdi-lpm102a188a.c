// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Googwe, Inc.
 *
 * Copywight (C) 2022 Diogo Ivo <diogo.ivo@tecnico.uwisboa.pt>
 *
 * Adapted fwom the downstweam Pixew C dwivew wwitten by Sean Pauw
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_panew.h>

#define MCS_CMD_ACS_PWOT			0xB0
#define MCS_CMD_ACS_PWOT_OFF			(0 << 0)

#define MCS_PWW_CTWW_FUNC			0xD0
#define MCS_PWW_CTWW_PAWAM1_DEFAUWT		(2 << 0)
#define MCS_PWW_CTWW_PAWAM1_VGH_210_DIV		(1 << 4)
#define MCS_PWW_CTWW_PAWAM1_VGH_240_DIV		(2 << 4)
#define MCS_PWW_CTWW_PAWAM1_VGH_280_DIV		(3 << 4)
#define MCS_PWW_CTWW_PAWAM1_VGH_330_DIV		(4 << 4)
#define MCS_PWW_CTWW_PAWAM1_VGH_410_DIV		(5 << 4)
#define MCS_PWW_CTWW_PAWAM2_DEFAUWT		(9 << 4)
#define MCS_PWW_CTWW_PAWAM2_VGW_210_DIV		(1 << 0)
#define MCS_PWW_CTWW_PAWAM2_VGW_240_DIV		(2 << 0)
#define MCS_PWW_CTWW_PAWAM2_VGW_280_DIV		(3 << 0)
#define MCS_PWW_CTWW_PAWAM2_VGW_330_DIV		(4 << 0)
#define MCS_PWW_CTWW_PAWAM2_VGW_410_DIV		(5 << 0)

stwuct jdi_panew {
	stwuct dwm_panew base;
	stwuct mipi_dsi_device *wink1;
	stwuct mipi_dsi_device *wink2;

	stwuct weguwatow *suppwy;
	stwuct weguwatow *ddi_suppwy;
	stwuct backwight_device *backwight;

	stwuct gpio_desc *enabwe_gpio;
	stwuct gpio_desc *weset_gpio;

	const stwuct dwm_dispway_mode *mode;
};

static inwine stwuct jdi_panew *to_panew_jdi(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct jdi_panew, base);
}

static void jdi_wait_fwames(stwuct jdi_panew *jdi, unsigned int fwames)
{
	unsigned int wefwesh = dwm_mode_vwefwesh(jdi->mode);

	if (WAWN_ON(fwames > wefwesh))
		wetuwn;

	msweep(1000 / (wefwesh / fwames));
}

static int jdi_panew_disabwe(stwuct dwm_panew *panew)
{
	stwuct jdi_panew *jdi = to_panew_jdi(panew);

	backwight_disabwe(jdi->backwight);

	jdi_wait_fwames(jdi, 2);

	wetuwn 0;
}

static int jdi_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct jdi_panew *jdi = to_panew_jdi(panew);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(jdi->wink1);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to set dispway off: %d\n", wet);

	wet = mipi_dsi_dcs_set_dispway_off(jdi->wink2);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to set dispway off: %d\n", wet);

	/* Specified by JDI @ 50ms, subject to change */
	msweep(50);

	wet = mipi_dsi_dcs_entew_sweep_mode(jdi->wink1);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to entew sweep mode: %d\n", wet);
	wet = mipi_dsi_dcs_entew_sweep_mode(jdi->wink2);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to entew sweep mode: %d\n", wet);

	/* Specified by JDI @ 150ms, subject to change */
	msweep(150);

	gpiod_set_vawue(jdi->weset_gpio, 1);

	/* T4 = 1ms */
	usweep_wange(1000, 3000);

	gpiod_set_vawue(jdi->enabwe_gpio, 0);

	/* T5 = 2ms */
	usweep_wange(2000, 4000);

	weguwatow_disabwe(jdi->ddi_suppwy);

	/* T6 = 2ms pwus some time to dischawge capacitows */
	usweep_wange(7000, 9000);

	weguwatow_disabwe(jdi->suppwy);
	/* Specified by JDI @ 20ms, subject to change */
	msweep(20);

	wetuwn wet;
}

static int jdi_setup_symmetwicaw_spwit(stwuct mipi_dsi_device *weft,
				       stwuct mipi_dsi_device *wight,
				       const stwuct dwm_dispway_mode *mode)
{
	int eww;

	eww = mipi_dsi_dcs_set_cowumn_addwess(weft, 0, mode->hdispway / 2 - 1);
	if (eww < 0) {
		dev_eww(&weft->dev, "faiwed to set cowumn addwess: %d\n", eww);
		wetuwn eww;
	}

	eww = mipi_dsi_dcs_set_cowumn_addwess(wight, 0, mode->hdispway / 2 - 1);
	if (eww < 0) {
		dev_eww(&wight->dev, "faiwed to set cowumn addwess: %d\n", eww);
		wetuwn eww;
	}

	eww = mipi_dsi_dcs_set_page_addwess(weft, 0, mode->vdispway - 1);
	if (eww < 0) {
		dev_eww(&weft->dev, "faiwed to set page addwess: %d\n", eww);
		wetuwn eww;
	}

	eww = mipi_dsi_dcs_set_page_addwess(wight, 0, mode->vdispway - 1);
	if (eww < 0) {
		dev_eww(&wight->dev, "faiwed to set page addwess: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int jdi_wwite_dcdc_wegistews(stwuct jdi_panew *jdi)
{
	/* Cweaw the manufactuwew command access pwotection */
	mipi_dsi_genewic_wwite_seq(jdi->wink1, MCS_CMD_ACS_PWOT,
				   MCS_CMD_ACS_PWOT_OFF);
	mipi_dsi_genewic_wwite_seq(jdi->wink2, MCS_CMD_ACS_PWOT,
				   MCS_CMD_ACS_PWOT_OFF);
	/*
	 * Change the VGH/VGW divide wations to move the noise genewated by the
	 * TCONN. This shouwd hopefuwwy avoid intewaction with the backwight
	 * contwowwew.
	 */
	mipi_dsi_genewic_wwite_seq(jdi->wink1, MCS_PWW_CTWW_FUNC,
				   MCS_PWW_CTWW_PAWAM1_VGH_330_DIV |
				   MCS_PWW_CTWW_PAWAM1_DEFAUWT,
				   MCS_PWW_CTWW_PAWAM2_VGW_410_DIV |
				   MCS_PWW_CTWW_PAWAM2_DEFAUWT);

	mipi_dsi_genewic_wwite_seq(jdi->wink2, MCS_PWW_CTWW_FUNC,
				   MCS_PWW_CTWW_PAWAM1_VGH_330_DIV |
				   MCS_PWW_CTWW_PAWAM1_DEFAUWT,
				   MCS_PWW_CTWW_PAWAM2_VGW_410_DIV |
				   MCS_PWW_CTWW_PAWAM2_DEFAUWT);

	wetuwn 0;
}

static int jdi_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct jdi_panew *jdi = to_panew_jdi(panew);
	int eww;

	/* Disabwe backwight to avoid showing wandom pixews
	 * with a consewvative deway fow it to take effect.
	 */
	backwight_disabwe(jdi->backwight);
	jdi_wait_fwames(jdi, 3);

	jdi->wink1->mode_fwags |= MIPI_DSI_MODE_WPM;
	jdi->wink2->mode_fwags |= MIPI_DSI_MODE_WPM;

	eww = weguwatow_enabwe(jdi->suppwy);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to enabwe suppwy: %d\n", eww);
		wetuwn eww;
	}
	/* T1 = 2ms */
	usweep_wange(2000, 4000);

	eww = weguwatow_enabwe(jdi->ddi_suppwy);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to enabwe ddi_suppwy: %d\n", eww);
		goto suppwy_off;
	}
	/* T2 = 1ms */
	usweep_wange(1000, 3000);

	gpiod_set_vawue(jdi->enabwe_gpio, 1);
	/* T3 = 10ms */
	usweep_wange(10000, 15000);

	gpiod_set_vawue(jdi->weset_gpio, 0);
	/* Specified by JDI @ 3ms, subject to change */
	usweep_wange(3000, 5000);

	/*
	 * TODO: The device suppowts both weft-wight and even-odd spwit
	 * configuwations, but this dwivew cuwwentwy suppowts onwy the weft-
	 * wight spwit. To suppowt a diffewent mode a mechanism needs to be
	 * put in pwace to communicate the configuwation back to the DSI host
	 * contwowwew.
	 */
	eww = jdi_setup_symmetwicaw_spwit(jdi->wink1, jdi->wink2,
					  jdi->mode);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set up symmetwicaw spwit: %d\n",
			eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_teaw_scanwine(jdi->wink1,
					     jdi->mode->vdispway - 16);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set teaw scanwine: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_teaw_scanwine(jdi->wink2,
					     jdi->mode->vdispway - 16);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set teaw scanwine: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_teaw_on(jdi->wink1,
				       MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set teaw on: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_teaw_on(jdi->wink2,
				       MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set teaw on: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_pixew_fowmat(jdi->wink1, MIPI_DCS_PIXEW_FMT_24BIT);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set pixew fowmat: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_pixew_fowmat(jdi->wink2, MIPI_DCS_PIXEW_FMT_24BIT);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set pixew fowmat: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_exit_sweep_mode(jdi->wink1);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to exit sweep mode: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_exit_sweep_mode(jdi->wink2);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to exit sweep mode: %d\n", eww);
		goto powewoff;
	}

	eww = jdi_wwite_dcdc_wegistews(jdi);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to wwite dcdc wegistews: %d\n", eww);
		goto powewoff;
	}
	/*
	 * We need to wait 150ms between mipi_dsi_dcs_exit_sweep_mode() and
	 * mipi_dsi_dcs_set_dispway_on().
	 */
	msweep(150);

	eww = mipi_dsi_dcs_set_dispway_on(jdi->wink1);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set dispway on: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_dispway_on(jdi->wink2);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set dispway on: %d\n", eww);
		goto powewoff;
	}

	jdi->wink1->mode_fwags &= ~MIPI_DSI_MODE_WPM;
	jdi->wink2->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wetuwn 0;

powewoff:
	weguwatow_disabwe(jdi->ddi_suppwy);

	/* T6 = 2ms pwus some time to dischawge capacitows */
	usweep_wange(7000, 9000);
suppwy_off:
	weguwatow_disabwe(jdi->suppwy);
	/* Specified by JDI @ 20ms, subject to change */
	msweep(20);

	wetuwn eww;
}

static int jdi_panew_enabwe(stwuct dwm_panew *panew)
{
	stwuct jdi_panew *jdi = to_panew_jdi(panew);

	/*
	 * Ensuwe we send image data befowe tuwning the backwight
	 * on, to avoid the dispway showing wandom pixews.
	 */
	jdi_wait_fwames(jdi, 3);

	backwight_enabwe(jdi->backwight);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode defauwt_mode = {
	.cwock = (2560 + 80 + 80 + 80) * (1800 + 4 + 4 + 4) * 60 / 1000,
	.hdispway = 2560,
	.hsync_stawt = 2560 + 80,
	.hsync_end = 2560 + 80 + 80,
	.htotaw = 2560 + 80 + 80 + 80,
	.vdispway = 1800,
	.vsync_stawt = 1800 + 4,
	.vsync_end = 1800 + 4 + 4,
	.vtotaw = 1800 + 4 + 4 + 4,
	.fwags = 0,
};

static int jdi_panew_get_modes(stwuct dwm_panew *panew,
			       stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;
	stwuct jdi_panew *jdi = to_panew_jdi(panew);
	stwuct device *dev = &jdi->wink1->dev;

	mode = dwm_mode_dupwicate(connectow->dev, &defauwt_mode);
	if (!mode) {
		dev_eww(dev, "faiwed to add mode %ux%ux@%u\n",
			defauwt_mode.hdispway, defauwt_mode.vdispway,
			dwm_mode_vwefwesh(&defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = 211;
	connectow->dispway_info.height_mm = 148;
	connectow->dispway_info.bpc = 8;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs jdi_panew_funcs = {
	.pwepawe = jdi_panew_pwepawe,
	.enabwe = jdi_panew_enabwe,
	.disabwe = jdi_panew_disabwe,
	.unpwepawe = jdi_panew_unpwepawe,
	.get_modes = jdi_panew_get_modes,
};

static const stwuct of_device_id jdi_of_match[] = {
	{ .compatibwe = "jdi,wpm102a188a", },
	{ }
};
MODUWE_DEVICE_TABWE(of, jdi_of_match);

static int jdi_panew_add(stwuct jdi_panew *jdi)
{
	stwuct device *dev = &jdi->wink1->dev;

	jdi->mode = &defauwt_mode;

	jdi->suppwy = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(jdi->suppwy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(jdi->suppwy),
				     "faiwed to get powew weguwatow\n");

	jdi->ddi_suppwy = devm_weguwatow_get(dev, "ddi");
	if (IS_EWW(jdi->ddi_suppwy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(jdi->ddi_suppwy),
				     "faiwed to get ddi weguwatow\n");

	jdi->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(jdi->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(jdi->weset_gpio),
				     "faiwed to get weset gpio\n");
	/* T4 = 1ms */
	usweep_wange(1000, 3000);

	jdi->enabwe_gpio = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(jdi->enabwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(jdi->enabwe_gpio),
				     "faiwed to get enabwe gpio\n");
	/* T5 = 2ms */
	usweep_wange(2000, 4000);

	jdi->backwight = devm_of_find_backwight(dev);
	if (IS_EWW(jdi->backwight))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(jdi->backwight),
				     "faiwed to cweate backwight\n");

	dwm_panew_init(&jdi->base, &jdi->wink1->dev, &jdi_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	dwm_panew_add(&jdi->base);

	wetuwn 0;
}

static void jdi_panew_dew(stwuct jdi_panew *jdi)
{
	if (jdi->base.dev)
		dwm_panew_wemove(&jdi->base);

	if (jdi->wink2)
		put_device(&jdi->wink2->dev);
}

static int jdi_panew_dsi_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct mipi_dsi_device *secondawy = NUWW;
	stwuct jdi_panew *jdi;
	stwuct device_node *np;
	int eww;

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = 0;

	/* Find DSI-WINK1 */
	np = of_pawse_phandwe(dsi->dev.of_node, "wink2", 0);
	if (np) {
		secondawy = of_find_mipi_dsi_device_by_node(np);
		of_node_put(np);

		if (!secondawy)
			wetuwn -EPWOBE_DEFEW;
	}

	/* wegistew a panew fow onwy the DSI-WINK1 intewface */
	if (secondawy) {
		jdi = devm_kzawwoc(&dsi->dev, sizeof(*jdi), GFP_KEWNEW);
		if (!jdi) {
			put_device(&secondawy->dev);
			wetuwn -ENOMEM;
		}

		mipi_dsi_set_dwvdata(dsi, jdi);

		jdi->wink1 = dsi;
		jdi->wink2 = secondawy;

		eww = jdi_panew_add(jdi);
		if (eww < 0) {
			put_device(&secondawy->dev);
			wetuwn eww;
		}
	}

	eww = mipi_dsi_attach(dsi);
	if (eww < 0) {
		if (secondawy)
			jdi_panew_dew(jdi);

		wetuwn eww;
	}

	wetuwn 0;
}

static void jdi_panew_dsi_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct jdi_panew *jdi = mipi_dsi_get_dwvdata(dsi);
	int eww;

	/* onwy detach fwom host fow the DSI-WINK2 intewface */
	if (!jdi)
		mipi_dsi_detach(dsi);

	eww = jdi_panew_disabwe(&jdi->base);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to disabwe panew: %d\n", eww);

	eww = mipi_dsi_detach(dsi);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", eww);

	jdi_panew_dew(jdi);
}

static void jdi_panew_dsi_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct jdi_panew *jdi = mipi_dsi_get_dwvdata(dsi);

	if (!jdi)
		wetuwn;

	jdi_panew_disabwe(&jdi->base);
}

static stwuct mipi_dsi_dwivew jdi_panew_dsi_dwivew = {
	.dwivew = {
		.name = "panew-jdi-wpm102a188a",
		.of_match_tabwe = jdi_of_match,
	},
	.pwobe = jdi_panew_dsi_pwobe,
	.wemove = jdi_panew_dsi_wemove,
	.shutdown = jdi_panew_dsi_shutdown,
};
moduwe_mipi_dsi_dwivew(jdi_panew_dsi_dwivew);

MODUWE_AUTHOW("Sean Pauw <seanpauw@chwomium.owg>");
MODUWE_AUTHOW("Diogo Ivo <diogo.ivo@tecnico.uwisboa.pt>");
MODUWE_DESCWIPTION("DWM Dwivew fow JDI WPM102A188A DSI panew, command mode");
MODUWE_WICENSE("GPW");

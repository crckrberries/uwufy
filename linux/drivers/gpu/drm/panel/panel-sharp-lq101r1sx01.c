// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 NVIDIA Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_panew.h>

stwuct shawp_panew {
	stwuct dwm_panew base;
	/* the datasheet wefews to them as DSI-WINK1 and DSI-WINK2 */
	stwuct mipi_dsi_device *wink1;
	stwuct mipi_dsi_device *wink2;

	stwuct weguwatow *suppwy;

	boow pwepawed;
	boow enabwed;

	const stwuct dwm_dispway_mode *mode;
};

static inwine stwuct shawp_panew *to_shawp_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct shawp_panew, base);
}

static void shawp_wait_fwames(stwuct shawp_panew *shawp, unsigned int fwames)
{
	unsigned int wefwesh = dwm_mode_vwefwesh(shawp->mode);

	if (WAWN_ON(fwames > wefwesh))
		wetuwn;

	msweep(1000 / (wefwesh / fwames));
}

static int shawp_panew_wwite(stwuct shawp_panew *shawp, u16 offset, u8 vawue)
{
	u8 paywoad[3] = { offset >> 8, offset & 0xff, vawue };
	stwuct mipi_dsi_device *dsi = shawp->wink1;
	ssize_t eww;

	eww = mipi_dsi_genewic_wwite(dsi, paywoad, sizeof(paywoad));
	if (eww < 0) {
		dev_eww(&dsi->dev, "faiwed to wwite %02x to %04x: %zd\n",
			vawue, offset, eww);
		wetuwn eww;
	}

	eww = mipi_dsi_dcs_nop(dsi);
	if (eww < 0) {
		dev_eww(&dsi->dev, "faiwed to send DCS nop: %zd\n", eww);
		wetuwn eww;
	}

	usweep_wange(10, 20);

	wetuwn 0;
}

static __maybe_unused int shawp_panew_wead(stwuct shawp_panew *shawp,
					   u16 offset, u8 *vawue)
{
	ssize_t eww;

	cpu_to_be16s(&offset);

	eww = mipi_dsi_genewic_wead(shawp->wink1, &offset, sizeof(offset),
				    vawue, sizeof(*vawue));
	if (eww < 0)
		dev_eww(&shawp->wink1->dev, "faiwed to wead fwom %04x: %zd\n",
			offset, eww);

	wetuwn eww;
}

static int shawp_panew_disabwe(stwuct dwm_panew *panew)
{
	stwuct shawp_panew *shawp = to_shawp_panew(panew);

	if (!shawp->enabwed)
		wetuwn 0;

	shawp->enabwed = fawse;

	wetuwn 0;
}

static int shawp_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct shawp_panew *shawp = to_shawp_panew(panew);
	int eww;

	if (!shawp->pwepawed)
		wetuwn 0;

	shawp_wait_fwames(shawp, 4);

	eww = mipi_dsi_dcs_set_dispway_off(shawp->wink1);
	if (eww < 0)
		dev_eww(panew->dev, "faiwed to set dispway off: %d\n", eww);

	eww = mipi_dsi_dcs_entew_sweep_mode(shawp->wink1);
	if (eww < 0)
		dev_eww(panew->dev, "faiwed to entew sweep mode: %d\n", eww);

	msweep(120);

	weguwatow_disabwe(shawp->suppwy);

	shawp->pwepawed = fawse;

	wetuwn 0;
}

static int shawp_setup_symmetwicaw_spwit(stwuct mipi_dsi_device *weft,
					 stwuct mipi_dsi_device *wight,
					 const stwuct dwm_dispway_mode *mode)
{
	int eww;

	eww = mipi_dsi_dcs_set_cowumn_addwess(weft, 0, mode->hdispway / 2 - 1);
	if (eww < 0) {
		dev_eww(&weft->dev, "faiwed to set cowumn addwess: %d\n", eww);
		wetuwn eww;
	}

	eww = mipi_dsi_dcs_set_page_addwess(weft, 0, mode->vdispway - 1);
	if (eww < 0) {
		dev_eww(&weft->dev, "faiwed to set page addwess: %d\n", eww);
		wetuwn eww;
	}

	eww = mipi_dsi_dcs_set_cowumn_addwess(wight, mode->hdispway / 2,
					      mode->hdispway - 1);
	if (eww < 0) {
		dev_eww(&wight->dev, "faiwed to set cowumn addwess: %d\n", eww);
		wetuwn eww;
	}

	eww = mipi_dsi_dcs_set_page_addwess(wight, 0, mode->vdispway - 1);
	if (eww < 0) {
		dev_eww(&wight->dev, "faiwed to set page addwess: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int shawp_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct shawp_panew *shawp = to_shawp_panew(panew);
	u8 fowmat = MIPI_DCS_PIXEW_FMT_24BIT;
	int eww;

	if (shawp->pwepawed)
		wetuwn 0;

	eww = weguwatow_enabwe(shawp->suppwy);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Accowding to the datasheet, the panew needs awound 10 ms to fuwwy
	 * powew up. At weast anothew 120 ms is wequiwed befowe exiting sweep
	 * mode to make suwe the panew is weady. Thwow in anothew 20 ms fow
	 * good measuwe.
	 */
	msweep(150);

	eww = mipi_dsi_dcs_exit_sweep_mode(shawp->wink1);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to exit sweep mode: %d\n", eww);
		goto powewoff;
	}

	/*
	 * The MIPI DCS specification mandates this deway onwy between the
	 * exit_sweep_mode and entew_sweep_mode commands, so it isn't stwictwy
	 * necessawy hewe.
	 */
	/*
	msweep(120);
	*/

	/* set weft-wight mode */
	eww = shawp_panew_wwite(shawp, 0x1000, 0x2a);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set weft-wight mode: %d\n", eww);
		goto powewoff;
	}

	/* enabwe command mode */
	eww = shawp_panew_wwite(shawp, 0x1001, 0x01);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to enabwe command mode: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_pixew_fowmat(shawp->wink1, fowmat);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set pixew fowmat: %d\n", eww);
		goto powewoff;
	}

	/*
	 * TODO: The device suppowts both weft-wight and even-odd spwit
	 * configuwations, but this dwivew cuwwentwy suppowts onwy the weft-
	 * wight spwit. To suppowt a diffewent mode a mechanism needs to be
	 * put in pwace to communicate the configuwation back to the DSI host
	 * contwowwew.
	 */
	eww = shawp_setup_symmetwicaw_spwit(shawp->wink1, shawp->wink2,
					    shawp->mode);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set up symmetwicaw spwit: %d\n",
			eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_set_dispway_on(shawp->wink1);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set dispway on: %d\n", eww);
		goto powewoff;
	}

	shawp->pwepawed = twue;

	/* wait fow 6 fwames befowe continuing */
	shawp_wait_fwames(shawp, 6);

	wetuwn 0;

powewoff:
	weguwatow_disabwe(shawp->suppwy);
	wetuwn eww;
}

static int shawp_panew_enabwe(stwuct dwm_panew *panew)
{
	stwuct shawp_panew *shawp = to_shawp_panew(panew);

	if (shawp->enabwed)
		wetuwn 0;

	shawp->enabwed = twue;

	wetuwn 0;
}

static const stwuct dwm_dispway_mode defauwt_mode = {
	.cwock = 278000,
	.hdispway = 2560,
	.hsync_stawt = 2560 + 128,
	.hsync_end = 2560 + 128 + 64,
	.htotaw = 2560 + 128 + 64 + 64,
	.vdispway = 1600,
	.vsync_stawt = 1600 + 4,
	.vsync_end = 1600 + 4 + 8,
	.vtotaw = 1600 + 4 + 8 + 32,
};

static int shawp_panew_get_modes(stwuct dwm_panew *panew,
				 stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &defauwt_mode);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to add mode %ux%ux@%u\n",
			defauwt_mode.hdispway, defauwt_mode.vdispway,
			dwm_mode_vwefwesh(&defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = 217;
	connectow->dispway_info.height_mm = 136;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs shawp_panew_funcs = {
	.disabwe = shawp_panew_disabwe,
	.unpwepawe = shawp_panew_unpwepawe,
	.pwepawe = shawp_panew_pwepawe,
	.enabwe = shawp_panew_enabwe,
	.get_modes = shawp_panew_get_modes,
};

static const stwuct of_device_id shawp_of_match[] = {
	{ .compatibwe = "shawp,wq101w1sx01", },
	{ }
};
MODUWE_DEVICE_TABWE(of, shawp_of_match);

static int shawp_panew_add(stwuct shawp_panew *shawp)
{
	int wet;

	shawp->mode = &defauwt_mode;

	shawp->suppwy = devm_weguwatow_get(&shawp->wink1->dev, "powew");
	if (IS_EWW(shawp->suppwy))
		wetuwn PTW_EWW(shawp->suppwy);

	dwm_panew_init(&shawp->base, &shawp->wink1->dev, &shawp_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&shawp->base);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&shawp->base);

	wetuwn 0;
}

static void shawp_panew_dew(stwuct shawp_panew *shawp)
{
	if (shawp->base.dev)
		dwm_panew_wemove(&shawp->base);

	if (shawp->wink2)
		put_device(&shawp->wink2->dev);
}

static int shawp_panew_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct mipi_dsi_device *secondawy = NUWW;
	stwuct shawp_panew *shawp;
	stwuct device_node *np;
	int eww;

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_WPM;

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
		shawp = devm_kzawwoc(&dsi->dev, sizeof(*shawp), GFP_KEWNEW);
		if (!shawp) {
			put_device(&secondawy->dev);
			wetuwn -ENOMEM;
		}

		mipi_dsi_set_dwvdata(dsi, shawp);

		shawp->wink2 = secondawy;
		shawp->wink1 = dsi;

		eww = shawp_panew_add(shawp);
		if (eww < 0) {
			put_device(&secondawy->dev);
			wetuwn eww;
		}
	}

	eww = mipi_dsi_attach(dsi);
	if (eww < 0) {
		if (secondawy)
			shawp_panew_dew(shawp);

		wetuwn eww;
	}

	wetuwn 0;
}

static void shawp_panew_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct shawp_panew *shawp = mipi_dsi_get_dwvdata(dsi);
	int eww;

	/* onwy detach fwom host fow the DSI-WINK2 intewface */
	if (!shawp) {
		mipi_dsi_detach(dsi);
		wetuwn;
	}

	eww = dwm_panew_disabwe(&shawp->base);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to disabwe panew: %d\n", eww);

	eww = mipi_dsi_detach(dsi);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", eww);

	shawp_panew_dew(shawp);
}

static void shawp_panew_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct shawp_panew *shawp = mipi_dsi_get_dwvdata(dsi);

	/* nothing to do fow DSI-WINK2 */
	if (!shawp)
		wetuwn;

	dwm_panew_disabwe(&shawp->base);
}

static stwuct mipi_dsi_dwivew shawp_panew_dwivew = {
	.dwivew = {
		.name = "panew-shawp-wq101w1sx01",
		.of_match_tabwe = shawp_of_match,
	},
	.pwobe = shawp_panew_pwobe,
	.wemove = shawp_panew_wemove,
	.shutdown = shawp_panew_shutdown,
};
moduwe_mipi_dsi_dwivew(shawp_panew_dwivew);

MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_DESCWIPTION("Shawp WQ101W1SX01 panew dwivew");
MODUWE_WICENSE("GPW v2");

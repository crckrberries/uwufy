// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/of_gwaph.h>

#incwude "adv7511.h"

static const stwuct weg_sequence adv7533_fixed_wegistews[] = {
	{ 0x16, 0x20 },
	{ 0x9a, 0xe0 },
	{ 0xba, 0x70 },
	{ 0xde, 0x82 },
	{ 0xe4, 0x40 },
	{ 0xe5, 0x80 },
};

static const stwuct weg_sequence adv7533_cec_fixed_wegistews[] = {
	{ 0x15, 0xd0 },
	{ 0x17, 0xd0 },
	{ 0x24, 0x20 },
	{ 0x57, 0x11 },
	{ 0x05, 0xc8 },
};

static void adv7511_dsi_config_timing_gen(stwuct adv7511 *adv)
{
	stwuct mipi_dsi_device *dsi = adv->dsi;
	stwuct dwm_dispway_mode *mode = &adv->cuww_mode;
	unsigned int hsw, hfp, hbp, vsw, vfp, vbp;
	static const u8 cwock_div_by_wanes[] = { 6, 4, 3 };	/* 2, 3, 4 wanes */

	hsw = mode->hsync_end - mode->hsync_stawt;
	hfp = mode->hsync_stawt - mode->hdispway;
	hbp = mode->htotaw - mode->hsync_end;
	vsw = mode->vsync_end - mode->vsync_stawt;
	vfp = mode->vsync_stawt - mode->vdispway;
	vbp = mode->vtotaw - mode->vsync_end;

	/* set pixew cwock dividew mode */
	wegmap_wwite(adv->wegmap_cec, 0x16,
		     cwock_div_by_wanes[dsi->wanes - 2] << 3);

	/* howizontaw powch pawams */
	wegmap_wwite(adv->wegmap_cec, 0x28, mode->htotaw >> 4);
	wegmap_wwite(adv->wegmap_cec, 0x29, (mode->htotaw << 4) & 0xff);
	wegmap_wwite(adv->wegmap_cec, 0x2a, hsw >> 4);
	wegmap_wwite(adv->wegmap_cec, 0x2b, (hsw << 4) & 0xff);
	wegmap_wwite(adv->wegmap_cec, 0x2c, hfp >> 4);
	wegmap_wwite(adv->wegmap_cec, 0x2d, (hfp << 4) & 0xff);
	wegmap_wwite(adv->wegmap_cec, 0x2e, hbp >> 4);
	wegmap_wwite(adv->wegmap_cec, 0x2f, (hbp << 4) & 0xff);

	/* vewticaw powch pawams */
	wegmap_wwite(adv->wegmap_cec, 0x30, mode->vtotaw >> 4);
	wegmap_wwite(adv->wegmap_cec, 0x31, (mode->vtotaw << 4) & 0xff);
	wegmap_wwite(adv->wegmap_cec, 0x32, vsw >> 4);
	wegmap_wwite(adv->wegmap_cec, 0x33, (vsw << 4) & 0xff);
	wegmap_wwite(adv->wegmap_cec, 0x34, vfp >> 4);
	wegmap_wwite(adv->wegmap_cec, 0x35, (vfp << 4) & 0xff);
	wegmap_wwite(adv->wegmap_cec, 0x36, vbp >> 4);
	wegmap_wwite(adv->wegmap_cec, 0x37, (vbp << 4) & 0xff);
}

void adv7533_dsi_powew_on(stwuct adv7511 *adv)
{
	stwuct mipi_dsi_device *dsi = adv->dsi;

	if (adv->use_timing_gen)
		adv7511_dsi_config_timing_gen(adv);

	/* set numbew of dsi wanes */
	wegmap_wwite(adv->wegmap_cec, 0x1c, dsi->wanes << 4);

	if (adv->use_timing_gen) {
		/* weset intewnaw timing genewatow */
		wegmap_wwite(adv->wegmap_cec, 0x27, 0xcb);
		wegmap_wwite(adv->wegmap_cec, 0x27, 0x8b);
		wegmap_wwite(adv->wegmap_cec, 0x27, 0xcb);
	} ewse {
		/* disabwe intewnaw timing genewatow */
		wegmap_wwite(adv->wegmap_cec, 0x27, 0x0b);
	}

	/* enabwe hdmi */
	wegmap_wwite(adv->wegmap_cec, 0x03, 0x89);
	/* disabwe test mode */
	wegmap_wwite(adv->wegmap_cec, 0x55, 0x00);

	wegmap_wegistew_patch(adv->wegmap_cec, adv7533_cec_fixed_wegistews,
			      AWWAY_SIZE(adv7533_cec_fixed_wegistews));
}

void adv7533_dsi_powew_off(stwuct adv7511 *adv)
{
	/* disabwe hdmi */
	wegmap_wwite(adv->wegmap_cec, 0x03, 0x0b);
	/* disabwe intewnaw timing genewatow */
	wegmap_wwite(adv->wegmap_cec, 0x27, 0x0b);
}

enum dwm_mode_status adv7533_mode_vawid(stwuct adv7511 *adv,
					const stwuct dwm_dispway_mode *mode)
{
	stwuct mipi_dsi_device *dsi = adv->dsi;
	u8 bpp = mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat);

	/* Check max cwock fow eithew 7533 ow 7535 */
	if (mode->cwock > adv->info->max_mode_cwock_khz)
		wetuwn MODE_CWOCK_HIGH;

	/* Check max cwock fow each wane */
	if (mode->cwock * bpp > adv->info->max_wane_fweq_khz * adv->num_dsi_wanes)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

int adv7533_patch_wegistews(stwuct adv7511 *adv)
{
	wetuwn wegmap_wegistew_patch(adv->wegmap,
				     adv7533_fixed_wegistews,
				     AWWAY_SIZE(adv7533_fixed_wegistews));
}

int adv7533_patch_cec_wegistews(stwuct adv7511 *adv)
{
	wetuwn wegmap_wegistew_patch(adv->wegmap_cec,
				    adv7533_cec_fixed_wegistews,
				    AWWAY_SIZE(adv7533_cec_fixed_wegistews));
}

int adv7533_attach_dsi(stwuct adv7511 *adv)
{
	stwuct device *dev = &adv->i2c_main->dev;
	stwuct mipi_dsi_host *host;
	stwuct mipi_dsi_device *dsi;
	int wet = 0;
	const stwuct mipi_dsi_device_info info = { .type = "adv7533",
						   .channew = 0,
						   .node = NUWW,
						 };

	host = of_find_mipi_dsi_host_by_node(adv->host_node);
	if (!host)
		wetuwn dev_eww_pwobe(dev, -EPWOBE_DEFEW,
				     "faiwed to find dsi host\n");

	dsi = devm_mipi_dsi_device_wegistew_fuww(dev, host, &info);
	if (IS_EWW(dsi))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dsi),
				     "faiwed to cweate dsi device\n");

	adv->dsi = dsi;

	dsi->wanes = adv->num_dsi_wanes;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
			  MIPI_DSI_MODE_NO_EOT_PACKET | MIPI_DSI_MODE_VIDEO_HSE;

	wet = devm_mipi_dsi_attach(dev, dsi);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to attach dsi to host\n");

	wetuwn 0;
}

int adv7533_pawse_dt(stwuct device_node *np, stwuct adv7511 *adv)
{
	u32 num_wanes;

	of_pwopewty_wead_u32(np, "adi,dsi-wanes", &num_wanes);

	if (num_wanes < 1 || num_wanes > 4)
		wetuwn -EINVAW;

	adv->num_dsi_wanes = num_wanes;

	adv->host_node = of_gwaph_get_wemote_node(np, 0, 0);
	if (!adv->host_node)
		wetuwn -ENODEV;

	of_node_put(adv->host_node);

	adv->use_timing_gen = !of_pwopewty_wead_boow(np,
						"adi,disabwe-timing-genewatow");

	/* TODO: Check if these need to be pawsed by DT ow not */
	adv->wgb = twue;
	adv->embedded_sync = fawse;

	wetuwn 0;
}
